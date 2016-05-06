#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>

#include <linux/pid_namespace.h>
#include "../rasbase/rasbase.h"
#include "../rasbase/rasproc.h"
struct RasMemory {
	struct RasMemory* next;
	unsigned long len;
};

struct RasMemArgs {
	pid_t pid;
	unsigned long gap;
	unsigned long clear;
	unsigned long restore;
	unsigned long long total;
	unsigned long long block;
	unsigned char fragment;	//true or false, flag for memory fragment
};

struct RasMemEle {
	struct RasMemArgs args;
	struct RasMemEle* prev;
	struct RasMemEle* next;
	struct RasMemory* tail;
	struct task_struct* tsk;
	struct RasMemory head;
	
	void* tchhandle;
	unsigned long tch;
	unsigned long idx;
	unsigned long long len;
	int dtor;
	rwlock_t rwk;
};

struct RasMem 
{
	struct RasMemEle eles[16];
	struct RasMemEle* ele;
	struct RasProc* proc;
	rwlock_t rmrw; // for ele.prev/ele.next
};

static int rasmemargs_set(struct RasMemArgs* rma, char* prm)
{
	if(0 == prm)
	{
		return 0;
	}
	rasbase_set(rma, pid, prm);
	rasbase_set(rma, gap, prm);
	rasbase_set(rma, clear, prm);
	rasbase_set(rma, block, prm);
	rasbase_set(rma, total, prm);
	rasbase_set(rma, restore, prm);
	rasbase_set(rma, fragment, prm);
	ras_retn(-EINVAL);
}

static inline struct task_struct* rasmemele_task(struct RasMemEle* ele)
{
	struct pid_namespace *ns = current->nsproxy->pid_ns;
	struct pid* pd = find_pid_ns(ele->args.pid, ns);
	struct task_struct* tsk; 
	rcu_read_lock();
	tsk = pid_task(pd, PIDTYPE_PID);
	rcu_read_unlock();
	return tsk;
}

#define RAS_WINRIVER RNC-GPU
#if 0
#define rasmemele_add(mm, pages)
#else
#ifdef RAS_WINRIVER
#define rasmemele_add(mm, pages) add_mm_counter(mm, MM_ANONPAGES, pages)
#else
#define rasmemele_add(mm, pages) add_mm_counter(mm, anon_rss, pages)
#endif
#endif
static inline void rasmemele_addmm(struct mm_struct* mm,
	struct RasMemEle* ele, long block)
{
	long pages = block >> PAGE_SHIFT;
	struct task_struct* tsk = (struct task_struct*)ele->tchhandle;
        task_lock(tsk);
	mm->total_vm += pages;
	//mm->hiwater_rss += pages;
	rasmemele_add(mm, pages);
	task_unlock(tsk);
}

static inline void rasmemele_decmm(struct mm_struct* mm, 
	struct RasMemEle* ele, long block)
{
	long pages = ele->tch >> PAGE_SHIFT;
	struct task_struct* tsk = (struct task_struct*)ele->tchhandle;
	if(mm->total_vm > pages)
	{
		task_lock(tsk);
		mm->total_vm -= pages;
		//mm->hiwater_rss -= pages;
		rasmemele_add(mm, -pages);
		task_unlock(tsk);
	}
}

static inline int rasmemele_touch(struct RasMemEle* ele, unsigned long block,
	void (*mmupdate)(struct mm_struct*, struct RasMemEle*,long))
{
	struct mm_struct* mm;
	struct task_struct* tsk; 
	ras_retn_if(!ele->args.pid, 0);
	
	tsk = rasmemele_task(ele);
	ras_retn_if(0 == tsk, -ESRCH);
	write_lock(&ele->rwk);
	if(0 == ele->tchhandle)
	{
		ele->tchhandle = tsk;
	}
	write_unlock(&ele->rwk);
	ras_retn_if(tsk != ele->tchhandle, -EFAULT);
	
	mm = get_task_mm(ele->tchhandle);
	ras_retn_if(0 == mm, -EINVAL);
	
	write_lock(&ele->rwk);
	mmupdate(mm, ele, block);
	write_unlock(&ele->rwk);
	mmput(mm);  // for get_task_mm match
	return 0;
}


static void rasmemele_dtor(struct RasMemEle* ele)
{
	write_lock(&ele->rwk);
	if(0 == ele->dtor)
	{
		write_unlock(&ele->rwk);
		return;
	}
	ele->dtor = 0;
	
	if(0 != ele->tsk)
	{
		write_unlock(&ele->rwk);
		kthread_stop(ele->tsk);
		write_lock(&ele->rwk);
	}
	
	while(0 != ele->tsk)
	{
		write_unlock(&ele->rwk);
		ras_sleep(RASTICK);
		write_lock(&ele->rwk);
	}
	
	ele->tail = ele->head.next;
	while(0 != ele->tail)
	{
		ele->head.next = ele->tail->next;
		ras_free(ele->tail);
		ele->tail = ele->head.next;
	}
	
	write_unlock(&ele->rwk);
	rasmemele_touch(ele, 0, rasmemele_decmm);
	write_lock(&ele->rwk);
	
	ele->tail = &ele->head;
	ele->tch = 0;
	ele->len = 0;
	ele->tchhandle = 0;
	ele->args.total = 0;
	write_unlock(&ele->rwk);
}

static void rasmem_append(struct RasMem* mem, struct RasMemEle* ele)
{
	write_lock(&mem->rmrw);
	if(0 == mem->ele) {
		mem->ele = ele;
		ele->prev = ele;
		ele->next = ele;
	} else {
		ele->next = mem->ele;
		ele->prev = mem->ele->prev;
		mem->ele->prev = ele;
		ele->prev->next = ele;
	}
	write_unlock(&mem->rmrw);
}

static void rasmem_remove(struct RasMem* mem, struct RasMemEle* ele)
{
	write_lock(&mem->rmrw);
	if(0 == mem->ele) {
		// nothing
	} else if(ele == mem->ele) {
		mem->ele = ele->next;
		if(ele == mem->ele)
		{
			mem->ele = 0;
		}
		ele->next = ele;
		ele->prev = ele;
	} else {
		ele->next->prev = ele->prev;
		ele->prev->next = ele->next;
		ele->next = ele;
		ele->prev = ele;
	}
	write_unlock(&mem->rmrw);
}

static int rasmem_restore(struct RasMem* mem, struct RasMemArgs* args)
{
	struct RasMemEle* ele = 0;
	int i, len = ARRAY_SIZE(mem->eles);
	for(i = 0; i < len; i++)
	{
		ele = &mem->eles[i];
		if(args->restore == ele->idx)
		{
			rasmemele_dtor(ele);
			rasmem_remove(mem, ele);
			return 0;
		}
	}
	ras_retn(-ENXIO);
}

static int rasmem_clear(struct RasMem* mem, struct RasMemArgs* args)
{
	struct RasMemEle* ele = 0;
	int i, len = ARRAY_SIZE(mem->eles);
	for(i = 0; i < len; i++)
	{
		ele = &mem->eles[i];
		if((ele->args.gap == args->gap) &&
			(ele->args.total == args->total) &&
			(ele->args.block == args->block) &&
			(ele->args.pid == args->pid))
		{
			rasmemele_dtor(ele);
			rasmem_remove(mem, ele);
			return 0;
		}
	}
	ras_retn(-ENXIO);
}

static int rasmemele_set(struct RasMemEle* ele, struct RasMemArgs* args)
{
	static unsigned long idx = 1;
	if(0 == ele->args.total)
	{
		memcpy(&ele->args, args, sizeof(struct RasMemArgs));
                if(idx == 0) idx++;
                ele->idx = idx++; // TODO for loop back
		ele->len = 0;
		return 0;
	}
	return -EEXIST;
}


static inline int rasmemele_malloc(struct RasMemEle* ele, unsigned long block)
{
	struct RasMemory* rm = 0;
	unsigned long size_min = sizeof(struct RasMemory);
    block = block < size_min ? size_min: block;
	ras_retn_iferr(ras_malloc((void**)&rm, block));
	rm->len = block;
	ele->len += block;
	write_lock(&ele->rwk);
	ele->tail->next = rm;
	ele->tail = rm;
	write_unlock(&ele->rwk);	
	return 0;
}

static inline int rasmemele_step(struct RasMemEle* ele)
{
	static int block = 1 << PAGE_SHIFT;
	unsigned long len = ele->args.block;
	while(len > block)
	{
		ras_retn_iferr(rasmemele_malloc(ele, block));
		len -= block;
	}
	ras_retn(rasmemele_malloc(ele, len));
}

static int fragment_create(struct RasMemEle* ele)
{
	unsigned long block = 0;
	struct RasMemory *pre  =0;
	struct RasMemory *next=0;
	struct RasMemory *temp=0;
	
	write_lock(&ele->rwk);
	pre = ele->head.next;
	while(0 != pre)
	{
		next = pre->next;
		if(0 == next ) break;
		temp = next->next;
		block += next->len;
		ras_free(next);
		pre->next = temp;
		pre = temp;
	}
	write_unlock(&ele->rwk);
	
	rasmemele_touch(ele, block, rasmemele_decmm);
	write_lock(&ele->rwk);
	ele->args.total -= block;
	write_unlock(&ele->rwk);
	return 0;
}

static int rasmemele_func(void* data)
{
	unsigned long len;
	struct RasMemEle* ele = data;
	while(!kthread_should_stop())
	{
		len = ele->len;
		rasmemele_step(ele);
		
		if(ele->len > len && 0 == rasmemele_touch(ele, ele->len - len, rasmemele_addmm)) {
			ele->tch += (ele->len - len);
		}
		
		if(ele->len >= ele->args.total) {
			if(ele->args.fragment)  fragment_create(ele);
			break;
		}
		if(ele->args.gap) {
			ras_sleep(ele->args.gap);
		} else if(len == ele->len) {
			//malloc 0, delay and retry
			ras_sleep(RASTICK);
		}
	}
	write_lock(&ele->rwk);
	ele->tsk = 0;
	write_unlock(&ele->rwk);
	return 0;
}

static int rasmemele_start(struct RasMemEle* ele)
{
	char name[64];
	ele->dtor = 1;
	snprintf(name, sizeof(name), "rasmem%lu", ele->idx);
	ele->tsk = kthread_create(rasmemele_func, ele, name);
	ras_retn_if(IS_ERR(ele->tsk), PTR_ERR(ele->tsk));	
	wake_up_process(ele->tsk);
	return 0;

}

static int rasmem_add(struct RasMem* mem, struct RasMemArgs* args)
{
	struct RasMemEle* ele = 0;
	int i, ret, len = ARRAY_SIZE(mem->eles);
	
	for(i = 0; i < len; i++)
	{
		ele = &mem->eles[i];
		write_lock(&ele->rwk);
		ret = rasmemele_set(ele, args);
		write_unlock(&ele->rwk);
		if(0 != ret) 
		{
			continue;
		}	
		ras_retn_iferr(rasmemele_start(ele));
		rasmem_append(mem, ele);
		return 0;
	}
	ras_retn(-EMFILE);
}
static int rasmem_main(void* mem, int argc, char* args[])
{
	struct RasMemArgs rma;
	int i;
	memset(&rma, 0, sizeof(rma));
	for(i = 0; i < argc; i++)
	{
		ras_retn_iferr(rasmemargs_set(&rma, args[i]));
	}
	if(rma.restore) 
	{
		ras_retn(rasmem_restore(mem, &rma));
	}
	if(rma.clear)
	{
		ras_retn(rasmem_clear(mem, &rma));
	}
	ras_retn_if(0 == rma.total, -EINVAL);
	if(0 == rma.block || rma.block > rma.total) 
	{
		rma.block = rma.total;
	}
	ras_retn(rasmem_add(mem, &rma));
}

static int rasmem_ctor(struct RasMem* mem)
{
	struct RasMemEle* ele;
	int i, len = ARRAY_SIZE(mem->eles);
	memset(mem, 0, sizeof(struct RasMem));
	rwlock_init(&mem->rmrw);

	for(i = 0; i < len; i++)
	{
		ele = &mem->eles[i];
		rwlock_init(&ele->rwk);
		ele->prev = ele;
		ele->next = ele;
		ele->tail = &ele->head;
		memset(&ele->head, 0, sizeof(struct RasMemory));
	}

	return 0;
}

static void rasmem_dtor(struct RasMem* mem)
{
	int i, len = ARRAY_SIZE(mem->eles);
	for(i = 0; i < len; i++)
	{
		rasmemele_dtor(&mem->eles[i]);
	}

}

static int proc_ops_show(rmem)(struct seq_file *m, void *v)
{

	static const char* rasfmt = 
		"%5lu total=%llu/%llu block=%llu gap=%lums pid=%d\n";
	char buf[256];
	struct RasMemEle* ele;
	struct RasMem* mem = m->private;

	int i, len = ARRAY_SIZE(mem->eles);
	for(i = 0; i < len; i++)
	{
		ele = &mem->eles[i];
		read_lock(&ele->rwk);
		if(0 != ele->args.total)
		{
			snprintf(buf, sizeof(buf), rasfmt, ele->idx, 
				ele->len, ele->args.total, ele->args.block, 
				ele->args.gap, ele->args.pid);
			seq_printf(m, "%s", buf);
		}
		read_unlock(&ele->rwk);
	}

	return 0;
}

static int proc_ops_open(rmem)(struct inode *inode, struct file *file)
{
	return single_open(file, proc_ops_show(rmem), PDE_DATA(inode));
}

static ssize_t proc_ops_write(rmem)(struct file *filp, 
	const char __user *bff, size_t count, loff_t *data)
{
	char buf_cmd[256];
	if(unlikely(count >= sizeof(buf_cmd)))    return -ENOMEM;
	
        memset(buf_cmd , 0, sizeof(buf_cmd));
	ras_retn_iferr(copy_from_user(buf_cmd, bff, count));
	ras_retn_iferr(ras_args(buf_cmd, count, rasmem_main, PDE_DATA(FILE_NODE(filp))));
	return count;
}

#define MODULE_NAME "rmem"
static struct RasMem gRasMem;
proc_ops_define(rmem);
static int rasmem_init(void)
{
	ras_debugset(1);
	ras_retn_iferr(ras_check());
	ras_retn_iferr(rasmem_ctor(&gRasMem));
	ras_retn_iferr(proc_init(MODULE_NAME,  &proc_ops_name(rmem), &gRasMem));
	return 0;
}

static void rasmem_exit(void)
{
	rasmem_dtor(&gRasMem);
	proc_exit(MODULE_NAME);
}

module_init(rasmem_init);
module_exit(rasmem_exit);
MODULE_VERSION("v1.3.1506");
MODULE_LICENSE("GPL");
// MODULE_DESCRIPTION("Corporate Reliability Dept");

