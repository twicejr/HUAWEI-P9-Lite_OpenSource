#include "../rasbase/rasbase.h"
#include "../rasbase/rasprobe.h"
#include "../rasbase/rasproc.h"
#include <linux/kernel.h>
#include <linux/kallsyms.h> 
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/genhd.h>
#include <linux/statfs.h>
#include <linux/module.h> 
#include <linux/mount.h>
#include <linux/path.h>

#define FILE_NODE(file) file->f_dentry->d_inode

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)

#define MNT_PARENT(mnt)  (mnt->mnt_parent)
#define MNT_POINT(mnt)   (mnt->mnt_mountpoint)
#define PDE_DATA(node)   (PDE(node)->data)
#else
#include "proc/internal.h"
#include "mount.h" 
#define MNT_PARENT(mnt)  (&real_mount(mnt)->mnt_parent->mnt)
#define MNT_POINT(mnt)   (real_mount(mnt)->mnt_mountpoint)

#endif

enum ChfilType {
	CHFILETYPE_DEADLOCK = 3,
	CHFILETYPE_UNREAD,
	CHFILETYPE_UNWRITE,
	CHFILETYPE_UNRW,
	CHFILETYPE_UNRM,
	CHFILETYPE_FULL,
	CHFILETYPE_ZERO,
	CHFILETYPE_BROKEN,
	CHFILETYPE_UNRENAME,
};

struct ChfilImpl
{
	struct file* flp;
	struct dentry* den;
	long long size;
	enum ChfilType ct;
};

struct Chfil {
	struct ChfilImpl impl[16];
	struct RasProc* proc;
	rwlock_t rwk;
};

static inline int chfilimpl_equalsb(struct ChfilImpl* ci, struct super_block *sb)
{
	return ci->den->d_sb == sb;
}
static inline int chfilimpl_equal(struct ChfilImpl* ci, struct dentry* den)
{
	return ci->den == den;
}

static inline int chfilimpl_includentry(struct ChfilImpl* ci, struct dentry* den)
{
	while(den && (den != den->d_parent))
	{
		ras_retn_if(chfilimpl_equal(ci, den), 1);
		den = den->d_parent;
	}
	ras_retn(chfilimpl_equal(ci, den));
}

static inline int _chfil_fill(struct Chfil* chf, 
	 long long size, struct file* flp, 
	struct dentry* den, int ct)
{
	struct ChfilImpl* ci = 0;
	int i, len = ARRAY_SIZE(chf->impl);
	for(i = 0; i < len; i++)
	{
		if(chfilimpl_equal(&chf->impl[i], den))	{
			fput(chf->impl[i].flp);
			ci = &chf->impl[i];
			break;
		} else if(0 == ci && 0 == chf->impl[i].flp) {
			ci = &chf->impl[i];
		}
	}
	
	if(0 != ci)
	{
		ci->flp = flp;
		ci->den = den;
		ci->size = size;
		ci->ct = ct;
		return 0;
	}
	ras_retn(-ENOMEM);
}
static int chfil_get(char* name, struct file** ppflp, struct dentry** ppden)
{
	struct dentry* den;
	struct file* flp = filp_open(name, O_RDONLY, 0);
	ras_retn_if(IS_ERR(flp), PTR_ERR(flp));
	den = flp->f_dentry;
	if(S_ISBLK(den->d_inode->i_mode))
	{
		struct super_block* sb;
		struct block_device* bdev = lookup_bdev(name);
		if(IS_ERR(bdev))
		{
			fput(flp);
			ras_retn(PTR_ERR(bdev));
		}
		if(0 == (sb = get_super(bdev)))
		{
			ras_retn(-EIO);
		}
		den = sb->s_root;
	}
	*ppflp = flp;
	*ppden = den;
//	printk("%s = %p, sb = %p\n", name, flp, flp->f_dentry->d_sb);
	return 0;
}
static int chfil_fill(struct Chfil* chf, char* name,  long long size, int ct)
{
	int ret = -EINVAL;
	struct dentry* den = 0;
	struct file* flp = 0;
	ras_retn_iferr(chfil_get(name, &flp, &den));

	if(0 != den) 
	{
		write_lock(&chf->rwk);
		ret = _chfil_fill(chf, size, flp, den, ct);
		write_unlock(&chf->rwk);
	}
	if(0 != ret)
	{
		fput(flp);
	}
	ras_retn(ret);
}

static inline int chfilimpl_dtor(struct ChfilImpl* impl)
{
	ras_retn_if(0 == impl->flp, -EINVAL);
	fput(impl->flp);
	memset(impl, 0, sizeof(struct ChfilImpl));
	return 0;
}

static inline int _chfil_restore(struct Chfil* chf, struct file* flp, struct dentry* den)
{
	int i, len = ARRAY_SIZE(chf->impl);
	for(i = 0; i < len; i++)
	{
		if(chfilimpl_equal(&chf->impl[i], den))
		{
			ras_retn(chfilimpl_dtor(&chf->impl[i]));
		}
	}
	ras_retn(-ENOENT);
}

static int _chfil_cancel(struct Chfil* chf, long long ll)
{
	if(ll >= ARRAY_SIZE(chf->impl))
	{
		ras_retn(-EINVAL);
	}
	ras_retn(chfilimpl_dtor(&chf->impl[ll]));
}

static int chfil_cancel(struct Chfil* chf, char* name)
{
	int ret;
	long long ll = 0;
	ras_retn_iferr(ras_atoll(&ll, name, strlen(name), 0));
	write_lock(&chf->rwk);
	ret = _chfil_cancel(chf, ll);
	write_unlock(&chf->rwk);
	ras_retn(ret);
}

static int chfil_restore(struct Chfil* chf, char* name)
{
	int ret;
	struct dentry* den = 0;
	struct file* flp = 0;
	ras_retn_iferr(chfil_get(name, &flp, &den));
	write_lock(&chf->rwk);
	ret = _chfil_restore(chf, flp, den);
	write_unlock(&chf->rwk);
	fput(flp);
	ras_retn(ret);
}

static struct {
	const int len;
	const char* op;
	enum ChfilType ct;
	int ret;
	int val;
} chfil_ops[] = {
	{.len=8, .op="deadlock", .ret=EDEADLK, .val=0, .ct=CHFILETYPE_DEADLOCK},
	{.len=6, .op="unread",   .ret=EACCES,  .val=0, .ct=CHFILETYPE_UNREAD},
	{.len=7, .op="unwrite",  .ret=EACCES,  .val=0, .ct=CHFILETYPE_UNWRITE},
	{.len=4, .op="unrw",     .ret=EACCES,  .val=0, .ct=CHFILETYPE_UNRW},
	{.len=4, .op="unrm",     .ret=EACCES,  .val=0, .ct=CHFILETYPE_UNRM},
	{.len=4, .op="full",     .ret=ENOSPC,  .val=0,.ct=CHFILETYPE_FULL},
	{.len=6, .op="broken",   .ret=0,  .val=0, .ct=CHFILETYPE_BROKEN},
	{.len=4, .op="zero",     .ret=0,  .val=0, .ct=CHFILETYPE_ZERO},
	{.len=4, .op="unrn",     .ret=EACCES,  .val=0, .ct=CHFILETYPE_UNRENAME},
};

static int chfilimpl_geturn(const struct ChfilImpl* impl)
{
	int i, len = ARRAY_SIZE(chfil_ops);
	for(i = 0; i < len; i++)
	{
		if(impl->ct == chfil_ops[i].ct)
		{
			return -chfil_ops[i].ret;
		}
	}
	return 0;
}

static inline int chfil_addsize(struct Chfil* chf, char* cmd, int len, char* name)
{
	long long size = 0;
	ras_retn_iferr(ras_atoll(&size, cmd, len, 0));
	ras_retn(chfil_fill(chf, name, size, 0));
}

static struct Chfil chfil;

static struct ChfilImpl* get_includentry(struct dentry* den)
{
	int i;
	struct ChfilImpl* ret = NULL;
	int len = ARRAY_SIZE(chfil.impl);
	read_lock(&chfil.rwk);
	for(i = 0; i < len; i++)
	{
		if(chfilimpl_includentry(&chfil.impl[i], den)) 
		{
			ret = &chfil.impl[i];
			break;
		}
	}
	read_unlock(&chfil.rwk);
	return ret;
}

static int chfil_includentry(struct dentry* den, 
	int (*op)(void*, const struct ChfilImpl*), void* data)
{
	int i;
	int ret = 0;
	int len = ARRAY_SIZE(chfil.impl);
	read_lock(&chfil.rwk);
	for(i = 0; i < len; i++)
	{
		if(0 == chfil.impl[i].den || 0 == chfil.impl[i].ct)
		{
			continue;
		}
		if(chfilimpl_includentry(&chfil.impl[i], den) && 
			0 != (ret = op(data, &chfil.impl[i])))
		{
			break;
		}
	}
	read_unlock(&chfil.rwk);
	return ret;
}
#define ULLMAX ((unsigned long long)(-1))
//incease the used size of block
static unsigned long long chfil_injected_sb_add(struct super_block *sb)
{
	int i, len;
	unsigned long long ret = 0;
	read_lock(&chfil.rwk);
	for(i = 0, len = ARRAY_SIZE(chfil.impl); i < len; i++)
	{
		if(0 == chfil.impl[i].den || !chfilimpl_equalsb(&chfil.impl[i], sb))
		{
			continue;
		}
		if(CHFILETYPE_FULL == chfil.impl[i].ct)	{
			ret = ULLMAX;
			break;
		}	
		if( chfil.impl[i].size <= 0 ||chfil.impl[i].ct != 0 ) continue;
		if(ULLMAX - ret > chfil.impl[i].size) {
			ret += chfil.impl[i].size;
		} else {
			ret = ULLMAX;
			break;
		}
	}
	read_unlock(&chfil.rwk);
	return ret;
}

//reduce the total size of block
static unsigned long long chfil_injected_sb_sub(struct super_block *sb)
{
	int i, len;
	unsigned long long ret = 0;
	unsigned long long size=0;
	read_lock(&chfil.rwk);
	for(i = 0, len = ARRAY_SIZE(chfil.impl); i < len; i++)
	{
		if(0 == chfil.impl[i].den || !chfilimpl_equalsb(&chfil.impl[i], sb))
		{
			continue;
		}
		if( chfil.impl[i].size >= 0 ||chfil.impl[i].ct != 0)	continue;
		size = 0 - chfil.impl[i].size;	//abs
		if(ULLMAX - ret > size) {
			ret += size;
		} else {
			ret = ULLMAX;
			break;
		}
	}
	read_unlock(&chfil.rwk);
	return ret;
}


static struct ChfilImpl* chfil_injected_dentry(struct dentry *den)
{
	int i, len;
	struct ChfilImpl* ret = 0;
	read_lock(&chfil.rwk);
	for(i = 0, len = ARRAY_SIZE(chfil.impl); i < len; i++)
	{
		if(0 == chfil.impl[i].flp)
		{
			continue;
		}
		if(chfilimpl_equal(&chfil.impl[i], den))
		{
			ret = &chfil.impl[i];
			break;
		}
	}
	read_unlock(&chfil.rwk);
	return ret;
}

static unsigned long long get_block_free_size(struct super_block *sb )
{
        struct kstatfs fs_state;      
	if(sb == 0) return 0;
	memset(&fs_state, 0, sizeof(struct kstatfs));
	
	if(sb->s_op->statfs(sb->s_root, &fs_state) != 0) return -1;

	return (unsigned long long)(fs_state.f_bfree*fs_state.f_bsize);
}


static int rasprobe_handler(vfs_statfs)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	struct RasRegs *rd = (struct RasRegs *)ri->data;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
	struct super_block* sb = ((struct dentry*)rd->args[0])->d_sb;
#else
	struct super_block* sb = ((struct path*)rd->args[0])->dentry->d_sb;
#endif
	
	unsigned long long blks = 0;
	unsigned long long size_free =0; 
	unsigned long long size_add = chfil_injected_sb_add(sb);	
	unsigned long long size_sub = chfil_injected_sb_sub(sb);
	struct kstatfs *kst = rd->args[1];
	if(0 == kst) return 0;
	if(size_add == 0 && size_sub ==0) return 0;
	size_free = get_block_free_size(sb);

	//1. reduce the total size of block 
	if(size_sub < size_free)
	{
		blks = ras_div(size_sub+1, kst->f_bsize);
                kst->f_bfree -= blks;  
                kst->f_bavail -= blks;
	    	kst->f_blocks-=blks;
	}
	else
	{
		kst->f_bfree = 0;
                kst->f_bavail = 0; 
		blks = ras_div(size_free+1, kst->f_bsize);
		kst->f_blocks-=blks;
	}
	size_free -= size_sub;
	if(size_free == 0) return 0;

	//2. increase the total size of block  
	if(size_add < size_free)
	{
		blks = ras_div(size_add+1, kst->f_bsize);
                kst->f_bfree -= blks;  
                kst->f_bavail -= blks;
	}
	else
	{
		kst->f_bfree = 0;
                kst->f_bavail = 0; 
	}
	
	return 0;
}

static int rasprobe_handler(vfs_getattr)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
        struct kstat  *kst = NULL;
        struct dentry *den = NULL;
        struct ChfilImpl* impl = NULL;
	struct RasRegs *rd = (struct RasRegs *)ri->data;
        unsigned long long size_free =0; 
	#if LINUX_VERSION_CODE > KERNEL_VERSION(3,10,0)	
	struct path *pth = (struct path*)rd->args[0];
	den = pth->dentry;
	kst = rd->args[1];
	#else
	den = (struct dentry*)rd->args[1];
	kst = rd->args[2];
	#endif
	if(0 == kst) return 0;
	impl = chfil_injected_dentry(den);
	if(impl) 	
	{
		if(impl->size > 0)
		{
			size_free = get_block_free_size(den->d_sb);
			size_free = impl->size < size_free ? impl->size: size_free;
			kst->blocks += 1 + ras_div(impl->size, kst->blksize);
			kst->size += impl->size;
		}
		else if(impl->ct == 0 && impl->size ==0)
		{	
			kst->blocks = ras_div(impl->size, kst->blksize);
			kst->size = impl->size;
		}
		return 0;
	}
	impl = get_includentry( den);
	if(impl)
	{
		 if(impl->ct == 0 && impl->size ==0)
		{
			kst->blocks = ras_div(impl->size, kst->blksize);
			kst->size = impl->size;
		}
	}
	return 0;
}

static int chfil_security_path_unlink(void* data, const struct ChfilImpl* impl)
{
	if(CHFILETYPE_UNRM == impl->ct)
	{
		ras_retn(chfilimpl_geturn(impl));
	} 
	return 0; 
}
static int rasprobe_handler(security_inode_unlink)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	if(0 == regs_return_value(regs))
	{
		int ret;
		struct RasRegs *rr = (struct RasRegs *)ri->data;
		struct dentry* den = rr->args[1];
		if(0 != (ret = chfil_includentry(den, chfil_security_path_unlink, rr)))
		{
			rasprobe_seturn(regs, ret);
		}
	}
	return 0;
}
static int rasprobe_handler(security_inode_rmdir)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	return rasprobe_handler(security_inode_unlink)(ri, regs);
}
static int chfil_security_inode_create(void* data, const struct ChfilImpl* impl)
{
	if((CHFILETYPE_UNWRITE == impl->ct) || (CHFILETYPE_UNRW == impl->ct))
	{
		ras_retn(chfilimpl_geturn(impl));
	} 
	return 0; 
}
static int rasprobe_handler(security_inode_create)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	if(0 == regs_return_value(regs))
	{
		int ret;
		struct RasRegs *rr = (struct RasRegs *)ri->data;
		struct dentry* den = rr->args[1];
		if(0 != (ret = chfil_includentry(den, chfil_security_inode_create, 0)))
		{
			rasprobe_seturn(regs, ret);
		}
	}
	return 0;
}
static int rasprobe_handler(security_inode_mkdir)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	return rasprobe_handler(security_inode_create)(ri, regs);
}

static int chfil_rw_verify_area(void* data, const struct ChfilImpl *impl)
{
	int rw = (long)data;
	if((impl->ct == CHFILETYPE_UNREAD && WRITE == rw) || 
		(impl->ct == CHFILETYPE_UNWRITE && READ == rw)||
		(impl->ct == CHFILETYPE_FULL && READ == rw)||
		(impl->ct == CHFILETYPE_UNRM )||
		(impl->ct == CHFILETYPE_UNRENAME ))
	{
		return 0;
	}
	return chfilimpl_geturn(impl);
}
static int rasprobe_handler(rw_verify_area)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	struct RasRegs *rd = (void*)ri->data;
	if(regs_return_value(regs) >= 0) {
		struct file* flp = (struct file*)rd->args[1];
		int ret = 0;
		if(0 == flp)
		{
			return 0;
		}
		if(0 != (ret = chfil_includentry(flp->f_dentry, 
			chfil_rw_verify_area, rd->args[0]))) {
			rasprobe_seturn(regs, ret);
		} else if(WRITE == (long)rd->args[0]) {
			struct super_block* sb = flp->f_dentry->d_sb;
			unsigned long long size_add = chfil_injected_sb_add(sb);
			unsigned long long size_sub = chfil_injected_sb_sub(sb);
			unsigned long long size = (ULLMAX - size_add < size_sub) ?ULLMAX: size_add+size_sub;
			if (0 != size && sb->s_op->statfs)
			{
				struct kstatfs buf;
				memset(&buf, 0, sizeof(buf));
				if(0 == sb->s_op->statfs(sb->s_root, &buf) && 
					size >= buf.f_bfree * buf.f_bsize)
				{
					rasprobe_seturn(regs, -ENOSPC);
				}
			}
		}
		else if(READ == (long)rd->args[0]) {
			struct ChfilImpl* impl = NULL;
			impl = get_includentry(flp->f_dentry);
			if(impl != 0 && 0 == impl->size && 0==impl->ct){
				rasprobe_seturn(regs, 0);
			}
		}
	}
	return 0;
}

static int chfil_security_path_rename(void* data, const struct ChfilImpl* impl)
{
	if(CHFILETYPE_UNRENAME== impl->ct)
	{
		ras_retn(chfilimpl_geturn(impl));
	} 
	return 0; 
}

static int rasprobe_handler(security_inode_rename)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	if(0 == regs_return_value(regs))
	{
		int ret;
		struct RasRegs *rr = (struct RasRegs *)ri->data;
		struct dentry* den = rr->args[1];
		if(0 != (ret = chfil_includentry(den, chfil_security_path_rename, rr)))
		{
			rasprobe_seturn(regs, ret);
		}
	}
	return 0;
}

static int rasprobe_handler(vfs_read)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	struct ChfilImpl* impl = NULL;
	struct RasRegs *rd = (void*)ri->data;
	struct file* fp = (struct file*)rd->args[0];
	char __user *buf_user = (char __user *)rd->args[1];
	int ret = regs_return_value(regs);
	if(ret <= 0)	return 0;
	if(0 == fp) return 0;
	
	//impl = chfil_injected_dentry(fp->f_dentry);
	impl = get_includentry(fp->f_dentry);
	if(impl == NULL)	
	{
	        return 0;
	}
	if(CHFILETYPE_BROKEN == impl->ct)
	{
		ras_retn_if(clear_user(buf_user , ras_div(ret, 2)), 0);
	}	
	else if( CHFILETYPE_ZERO == impl->ct)
	{
		ras_retn_if(clear_user(buf_user , ret), 0);
	}
	return 0;
}

void show_name(struct seq_file *m, struct vfsmount* mnt, struct dentry* den)
{
	if(0 == den || 0 == mnt)	return;
    	if(den == den->d_parent)
    	{
		if(mnt != MNT_PARENT(mnt))
		{
	        	show_name(m, MNT_PARENT(mnt),MNT_POINT(mnt));
		}
		return;
    	}
	show_name(m, mnt, den->d_parent);
    	seq_printf(m, "/%s", den->d_name.name);
}

#include <linux/security.h>
static int inline chfile_check(void)
{
	struct inode *dir;
	struct dentry *den = 0; 
	int mode = 0;
	struct kstatfs * kfs = 0;
	struct kstat *ks = 0;
	struct file *f = 0;
	loff_t *ppos = 0;
	size_t count = 0;
	struct path* pth = 0;
	struct vfsmount *mnt = 0;
	security_inode_mkdir(dir, den, mode);
	security_inode_create(dir, den, mode);
	security_inode_rmdir(dir, den);
	security_inode_unlink(dir, den);
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
	vfs_statfs(den, kfs);
#else
{
	vfs_statfs(pth, kfs);
}
#endif
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,10,0)	
	vfs_getattr(pth, ks);
	mnt = 0;
#else
	vfs_getattr(mnt, den, ks);
#endif
	rw_verify_area(mode, f, ppos,  count);

	return 0;
}

rasprobe_define(security_inode_create);
rasprobe_define(security_inode_rmdir);
rasprobe_define(security_inode_unlink);
rasprobe_define(security_inode_mkdir);
rasprobe_define(vfs_statfs);
rasprobe_define(vfs_getattr);
rasprobe_define(rw_verify_area);
rasprobe_define(vfs_read);
rasprobe_define(security_inode_rename);
static struct rasprobe* probes[]={
	&rasprobe_name(security_inode_create),
	&rasprobe_name(security_inode_rmdir),
	&rasprobe_name(security_inode_unlink),
	&rasprobe_name(security_inode_mkdir),
	&rasprobe_name(vfs_statfs),
	&rasprobe_name(vfs_getattr),
	&rasprobe_name(rw_verify_area), // cover all write function
	&rasprobe_name(vfs_read),
	&rasprobe_name(security_inode_rename),
};

static int cmd_main(void* data, int argc, char* args[])
{       
	int i, len, cnt;
	char* cmd;
	char* name;
	struct Chfil* chf = data;
	ras_retn_if(2 > argc, -EINVAL);
	cmd = args[0];
	name = args[1];
	ras_retn_if(0 == cmd || 0 == name, -EINVAL);
	len = strlen(cmd);
	for(i = 0, cnt=ARRAY_SIZE(chfil_ops); i < cnt; i++)
	{
		ras_retn_if((chfil_ops[i].len == len) && (0 == strncmp(chfil_ops[i].op, cmd, len)),
			chfil_fill(chf, name, chfil_ops[i].val, chfil_ops[i].ct));
	}
	ras_retn_if((6 == len) && (0 == strncmp("cancel", cmd, len)),
		chfil_cancel(chf, name));
	ras_retn_if((7 == len) && (0 == strncmp("restore", cmd, len)), 
		chfil_restore(chf, name));
	ras_retn(chfil_addsize(chf, cmd, len, name));
	
}
int miss_show(struct rasprobe **rps, int num,struct seq_file *m)
{
	int i, ret;
	char buf[128];
	if (num <= 0)
	{
		return -EINVAL;
	}
	for (i = 0; i < num; i++) {
		snprintf(buf, sizeof(buf), "%d\t%d\t", i, rps[i]->nmissed);
		seq_printf(m, "%s\n", buf);
	}
	return ret;
}
static int proc_ops_show(rfile)(struct seq_file *m, void *v)
{
	char buf[128];
	struct ChfilImpl* impl = NULL;
	struct Chfil* chf = m->private;
	int i, len = ARRAY_SIZE(chf->impl);
	int j, olen = ARRAY_SIZE(chfil_ops);

	read_lock(&chf->rwk);
	for(i = 0; i < len; i++)
	{
		impl = &chf->impl[i];
		if(0 == impl->flp)
			continue;
		for(j = 0; j < olen; j++)
		{
			if(impl->ct == chfil_ops[j].ct)
			{
				snprintf(buf, sizeof(buf), "%d\t%s\t", i, chfil_ops[j].op);
				seq_printf(m, "%s", buf);
				j = -1;
				break;
			}
		}
		if(-1 != j)
		{
			snprintf(buf, sizeof(buf), "%d\t%lld\t", i, impl->size);			
			//snprintf(buf, sizeof(buf), "%d\t%llu\t0X%08X\t", i, impl->size,(int)impl->den);			
			seq_printf(m, "%s", buf);
		}
		show_name(m, impl->flp->f_path.mnt, impl->flp->f_dentry);
		seq_printf(m, "\n");
	}
	read_unlock(&chf->rwk);
//	miss_show(probes, ARRAY_SIZE(probes), m);
	return 0;
}

static int proc_ops_open(rfile)(struct inode *inode, struct file *file)
{
	return single_open(file, proc_ops_show(rfile), PDE_DATA(inode));
}

static ssize_t proc_ops_write(rfile)(struct file *filp, 
	const char __user *bff, size_t count, loff_t *data)
{
	char buf_cmd[256];
	if(unlikely(count >= sizeof(buf_cmd)))    return -ENOMEM;
	
        memset(buf_cmd , 0, sizeof(buf_cmd));
	ras_retn_iferr(copy_from_user(buf_cmd, bff, count));
	ras_retn_iferr(ras_args(buf_cmd, count, cmd_main, PDE_DATA(FILE_NODE(filp))));
	return count;
}

#define MODULE_NAME "rfile"
proc_ops_define(rfile);
static int rfile_init(void)  
{
	ras_debugset(1);
	ras_retn_iferr(ras_check());
	memset(&chfil, 0, sizeof(chfil));
	rwlock_init(&chfil.rwk);
	rasprobe_name(vfs_read).maxactive=100;	
	ras_retn_iferr(register_rasprobes(probes, ARRAY_SIZE(probes)));
	ras_retn_iferr(proc_init(MODULE_NAME,  &proc_ops_name(rfile), &chfil));
	return 0;
}
static void rfile_exit(void)  
{  
	int i, len;
	proc_exit(MODULE_NAME);
   	unregister_rasprobes(probes, ARRAY_SIZE(probes));
	write_lock(&chfil.rwk);
	for(i = 0, len = ARRAY_SIZE(chfil.impl); i < len; i++)
	{
		chfilimpl_dtor(&chfil.impl[i]);
	}
	write_unlock(&chfil.rwk);
	return;
}

module_init(rfile_init);  
module_exit(rfile_exit);  
MODULE_DESCRIPTION("Change the file system of linux.");  
MODULE_LICENSE("GPL"); 
MODULE_VERSION("v1.4.1512");
