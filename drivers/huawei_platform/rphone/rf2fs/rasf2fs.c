#include "../rasbase/rasbase.h"
#include "../rasbase/rasprobe.h"
#include "../rasbase/rasproc.h"
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/kallsyms.h> 
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/genhd.h>
#include <linux/statfs.h>
#include <linux/module.h> 
#include <linux/mount.h>
#include <linux/path.h>
#include <linux/blk_types.h>
#include <linux/blkdev.h>
#include <linux/f2fs_fs.h>
#include "fs/f2fs/f2fs.h"

#define  if_then(con, work) if(con) work
#define  if_then_retn(con, work) if(con) return work
#define  if_then_else(con, work, work_else) if(con) work; else work_else
#define  if_then_else_retn(con, work) if(con) return work; else return work_else
enum fault_type 
{
    FAULT_NONE=0,
    FAULT_ALL_0,
    FAULT_ALL_1,
    FAULT_GAP_0,
    FAULT_GAP_1,
    FAULT_ALL_INVERS,
    FAULT_GAP_INVERS,
};

enum fault_area
{
    FAULT_AREA_SB0,
    FAULT_AREA_SB1,
    FAULT_AREA_CP0,
    FAULT_AREA_CP1,
    FAULT_AREA_SIT,
    FAULT_AREA_NAT,
    FAULT_AREA_SSA,
    FAULT_AREA_MAX,
};

struct fault_ops 
{
	const char *name;	
	enum fault_type type;
};
static const struct fault_ops fault_ops_list[]=
{
	{.name="all_0",      .type=FAULT_ALL_0,  },
	{.name="all_1",      .type=FAULT_ALL_1, },
    {.name="gap_0",      .type=FAULT_GAP_0,  },
	{.name="gap_1",      .type=FAULT_GAP_1, },
    {.name="all_invers", .type=FAULT_ALL_INVERS, },
	{.name="gap_invers", .type=FAULT_GAP_INVERS, },
};
struct fault_area_ops
{
	const char *name;	
	enum  fault_area type;
};
static const struct fault_area_ops fault_area_ops_list[]=
{
    {.name="sb0",      .type=FAULT_AREA_SB0},
    {.name="sb1",     .type=FAULT_AREA_SB1},
    {.name="cp0",      .type=FAULT_AREA_CP0},
    {.name="cp1",      .type=FAULT_AREA_CP1},
    {.name="sit",      .type=FAULT_AREA_SIT},
    {.name="nat",      .type=FAULT_AREA_NAT},
    {.name="ssa",      .type=FAULT_AREA_SSA},
};

struct fault_impl
{
    unsigned int     start;
    unsigned int     end;
	unsigned int     size;
    unsigned int     offset;
	enum fault_type  type;
    enum fault_area  area;
    unsigned int match;
    char disk[BDEVNAME_SIZE];
};
struct f2fs_area_page
{
    unsigned int page_start;
    unsigned int page_num;
};

struct fault_area_node
{
    struct list_head st_list;
    struct fault_impl fault;
};

#define FAULT_MAX 32
struct  fault_list
{
	rwlock_t rwk;
    struct list_head area_list[FAULT_AREA_MAX];
    struct f2fs_area_page area_page[2][FAULT_AREA_MAX];//sb0,sb1
};
static struct fault_list fault_injected;	//record the faults which was injected.

static struct fault_ops* get_fault_ops(enum fault_type type)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_ops_list); i++)
	{
		if_then_retn(fault_ops_list[i].type == type, (struct fault_ops*)&fault_ops_list[i]);
	}
	return NULL;
}

static const char* type2name(enum fault_type type)
{
	struct fault_ops *ops = get_fault_ops(type);
	return (ops) ? ops->name:"fault_unknow";
}

static enum fault_type name2type(const char *name)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_ops_list); i++)
	{
		if_then_retn(strcmp(name, fault_ops_list[i].name)==0, fault_ops_list[i].type);
	}
	return FAULT_NONE;
}

static const char* area2name(enum fault_area type)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_area_ops_list); i++)
	{
		if_then_retn(fault_area_ops_list[i].type == type, fault_area_ops_list[i].name);
	}
	return "fault_unknow";
}

static enum fault_area name2area(const char *name)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_area_ops_list); i++)
	{
		if_then_retn(strcmp(name, fault_area_ops_list[i].name)==0, fault_area_ops_list[i].type);
	}
	return FAULT_AREA_MAX;
}

static int rasf2fs_args_set(struct fault_impl* fault_args, char* prm)
{
    if(0 == prm) return 0;
    rasbase_set_func(fault_args, type, prm,name2type);
    rasbase_set_func(fault_args, area,prm, name2area);
    rasbase_set(fault_args, size, prm);
    rasbase_set(fault_args, offset, prm);
    rasbase_set(fault_args, start, prm);
    rasbase_set(fault_args, end, prm);
    rasbase_cset(fault_args, disk,prm);    
    return 0;
}

static int rasf2fs_parse_args(int args, char *argv[], struct fault_impl *fault)
{
    int i;
    if_then_retn(args<4, -EINVAL);
    for(i = 0; i< args; i++)
    {
        ras_retn_iferr(rasf2fs_args_set(fault, argv[i]));
    }
    //1. check the commands arg[0]: the fault mode name  arg[1]:some other configuration of the fault
    ras_retn_if((fault->type == FAULT_NONE), -EINVAL);
    ras_retn_if(fault->area == FAULT_AREA_MAX, -EINVAL);
    if_then_retn((fault->offset + fault->size > F2FS_BLKSIZE), -EINVAL);
    ras_retn_if(((fault->area==FAULT_AREA_SB0 || fault->area==FAULT_AREA_SB1) && *(fault->disk) == 0),-EINVAL);
    if((fault->area==FAULT_AREA_SB0 || fault->area==FAULT_AREA_SB1))
        fault->start = 0;
    if(fault->area > FAULT_AREA_SB1)
    {
        if(!fault->end)
            fault->end=fault->start;
        if_then_retn((fault->start > fault->end), -EINVAL);
    }
    return 0;
}

static int check_conflict_record_offset(struct fault_impl *fault)
{
    struct list_head *area_list_head = &(fault_injected.area_list[fault->area]);
    struct list_head *pos, *next;
    struct fault_area_node *area_node;

    //insert by order
    list_for_each_safe(pos, next, area_list_head) {
        //if match retrun -ENVIAL
        area_node=list_entry(pos,struct fault_area_node, st_list);        
        if_then_retn((fault->offset + fault->size > F2FS_BLKSIZE), -EINVAL);
    }
    
    area_node = kmalloc(sizeof(struct fault_area_node), 0);
    if_then_retn(!area_node, -EINVAL);
    memcpy(&(area_node->fault), fault,sizeof(struct fault_impl));
    INIT_LIST_HEAD(&(area_node->st_list));    
    list_add_tail(&(area_node->st_list), area_list_head);    
    return 0;
}

//Convert arguments to faults, then inject and inject them.
static int args2fault(int args, char *argv[])
{
    int inject = 0;
    struct fault_impl fault_args;
    memset(&fault_args, 0, sizeof(struct fault_impl));

    //1. parse args into fault
    if_then_retn(rasf2fs_parse_args(args,argv,&fault_args), -EINVAL);
	
	//2. manage the faults
	write_lock(&fault_injected.rwk);
	inject = check_conflict_record_offset(&fault_args);
	write_unlock(&fault_injected.rwk);
    return inject;
}

//inject
static int rasf2fs_inject_byte(struct fault_impl *fault, char *buf, unsigned int length)
{
    int i;
    ras_retn_if(fault->offset+fault->size > length, -EINVAL);   
    
    if(fault->type == FAULT_ALL_0)
        memset(buf+fault->offset, 0x0, fault->size);
    else if(fault->type == FAULT_ALL_1)
        memset(buf+fault->offset, 0xff, fault->size);
    else
    {
        for(i=0; i<fault->size; i++)
        {
            switch(fault->type)
            {
                case FAULT_GAP_0:
                {
                    *(buf+fault->offset+i) &=0xAA;
                    break;
                }
                case FAULT_GAP_1:
                {
                    *(buf+fault->offset+i) |=0xAA;
                    break;
                }
                case FAULT_ALL_INVERS:
                {
                    *(buf+fault->offset+i)=~(*(buf+fault->offset+i));
                    break;
                }
                case FAULT_GAP_INVERS:
                {
                    *(buf+fault->offset+i)=(~(*(buf+fault->offset+i)) &0xAA);
                    break;
                }
                default:
                {
                    ras_fail("unsupport fault type\n");
                    return -EINVAL;
                }
            }
        }
    }
    fault->match++;
    return 0;
}

static int rasf2fs_inject_buffer(struct block_device *bdev,char *buf,unsigned int index, unsigned int length, enum fault_area area_type)
{
    struct list_head *pos,*next;
    struct list_head *area_list_head=&fault_injected.area_list[area_type];
    struct fault_area_node *area_node;
    char disk_name[BDEVNAME_SIZE];
    
    if(bdev)
        bdevname(bdev,disk_name);    
    //not find fault
    ras_retn_if(list_empty(area_list_head), 0);
    
    list_for_each_safe(pos, next, area_list_head) {       
        area_node=list_entry(pos, struct fault_area_node, st_list);
        if(area_node->fault.start > index || area_node->fault.end < index) continue;

        if(bdev && 0 != strcmp(disk_name,area_node->fault.disk)) continue;
        //match area_type,inject        
        if(rasf2fs_inject_byte(&(area_node->fault), buf, length))  continue;
    }
    return 0;
}

static int rasf2fs_get_area_index(struct f2fs_sb_info *sbi, block_t disk_index, enum fault_area *area_type, block_t *relative_index, unsigned int *size)
{
    struct f2fs_super_block * super = sbi->raw_super;
    __le32 cp_blkaddr = super->cp_blkaddr;
    __le32 nat_blkaddr = super->nat_blkaddr;
    __le32 sit_blkaddr = super->sit_blkaddr;
    __le32 ssa_blkaddr = super->ssa_blkaddr;

    __le32 cp_blocks = super->segment_count_ckpt << super->log_blocks_per_seg;
    __le32 nat_blocks = super->segment_count_nat << super->log_blocks_per_seg;
    __le32 sit_blocks = super->segment_count_sit << super->log_blocks_per_seg;
    __le32 ssa_blocks = super->segment_count_ssa << super->log_blocks_per_seg;
    __le32 offset = 0;
    __le32 relative_block_offset = 0;
    
    //cp1 
    if (disk_index >= cp_blkaddr && disk_index < cp_blkaddr + (cp_blocks >> 1))
    { 
        relative_block_offset = disk_index - cp_blkaddr;
        *area_type = FAULT_AREA_CP0;
        *size= F2FS_BLKSIZE;
    } else if (disk_index >= cp_blkaddr + (cp_blocks >> 1)  && disk_index < cp_blkaddr + cp_blocks) { //cp2
        relative_block_offset = disk_index - (cp_blocks >> 1) - cp_blkaddr;
        *area_type = FAULT_AREA_CP1;
        *size= F2FS_BLKSIZE;
    } else if (disk_index >= nat_blkaddr && disk_index < nat_blkaddr + nat_blocks) { //nat
        relative_block_offset = (disk_index - nat_blkaddr)
            >> super->log_blocks_per_seg >> 1 ;
        relative_block_offset <<= super->log_blocks_per_seg;
        relative_block_offset += (disk_index - nat_blkaddr) & 
            ((1 << sbi->log_blocks_per_seg) - 1);
        
        *area_type = FAULT_AREA_NAT;
        *size= sizeof(struct f2fs_nat_block);
        
    } else if (disk_index >= sit_blkaddr && disk_index < sit_blkaddr + sit_blocks) { //sit
        offset = (disk_index < sit_blkaddr + (sit_blocks >> 1)) ? 0 : (sit_blocks) >> 1; 
        relative_block_offset = disk_index - sit_blkaddr - offset;
        *area_type= FAULT_AREA_SIT;
        *size = sizeof(struct f2fs_sit_block);
    } else if (disk_index >= ssa_blkaddr && disk_index < ssa_blkaddr + ssa_blocks) { //ssa
        relative_block_offset = disk_index - ssa_blkaddr;
        *area_type = FAULT_AREA_SSA;
        *size = sizeof(struct f2fs_summary_block);
    }
    else {
        printk("rasf2fs_get_area_index:can't find area by block=%d\n",(int)disk_index);
        return -EINVAL;
    }
    
    *relative_index = relative_block_offset;
    return 0;
}

static int rasprobe_handler(get_meta_page)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	struct RasRegs *rd = (struct RasRegs *)ri->data;
	struct f2fs_sb_info *sbi = rd->args[0];
	block_t disk_index = (block_t)(u64)rd->args[1];
    block_t relative_index=0;
    enum fault_area area_type;
    struct page * ret_page = (struct page *)regs_return_value(regs);
    char *buf;
    unsigned int size;
    
    if(!ret_page) return 0;
	buf = (char *)page_address(ret_page);
    if(!buf) return 0;
    
    //get area and relative index
    if (rasf2fs_get_area_index(sbi, disk_index, &area_type, &relative_index, &size))
        return 0;
    rasf2fs_inject_buffer(NULL,buf,relative_index,F2FS_BLKSIZE,area_type);
	return 0;
}

static void rasf2fs_record_area_page(struct f2fs_super_block *super, enum fault_area sb_type)
{
    __le32 cp_blkaddr = super->cp_blkaddr;
    __le32 nat_blkaddr = super->nat_blkaddr;
    __le32 sit_blkaddr = super->sit_blkaddr;
    __le32 ssa_blkaddr = super->ssa_blkaddr;

    __le32 cp_blocks = super->segment_count_ckpt << super->log_blocks_per_seg;
    __le32 nat_blocks = super->segment_count_nat << super->log_blocks_per_seg;
    __le32 sit_blocks = super->segment_count_sit << super->log_blocks_per_seg;
    __le32 ssa_blocks = super->segment_count_ssa << super->log_blocks_per_seg;
    
    fault_injected.area_page[sb_type][FAULT_AREA_SB0].page_start=0;
    fault_injected.area_page[sb_type][FAULT_AREA_SB0].page_num=1;
    fault_injected.area_page[sb_type][FAULT_AREA_SB1].page_start=1;
    fault_injected.area_page[sb_type][FAULT_AREA_SB1].page_num=1;

    fault_injected.area_page[sb_type][FAULT_AREA_CP0].page_start=cp_blkaddr;
    fault_injected.area_page[sb_type][FAULT_AREA_CP0].page_num=(cp_blocks >> 1);
    
    fault_injected.area_page[sb_type][FAULT_AREA_CP1].page_start=cp_blkaddr + (cp_blocks >> 1);
    fault_injected.area_page[sb_type][FAULT_AREA_CP1].page_num=cp_blocks-(cp_blocks >> 1);

    fault_injected.area_page[sb_type][FAULT_AREA_SIT].page_start=sit_blkaddr;
    fault_injected.area_page[sb_type][FAULT_AREA_SIT].page_num=sit_blocks;
    
    fault_injected.area_page[sb_type][FAULT_AREA_NAT].page_start=nat_blkaddr;
    fault_injected.area_page[sb_type][FAULT_AREA_NAT].page_num=nat_blocks;

    fault_injected.area_page[sb_type][FAULT_AREA_SSA].page_start=ssa_blkaddr;
    fault_injected.area_page[sb_type][FAULT_AREA_SSA].page_num=ssa_blocks;
    return;
}    

static int rasprobe_handler(__bread)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
    char *f2fs_super;
	struct RasRegs *rd = (struct RasRegs *)ri->data;    
    struct block_device *bdev = rd->args[0];
	sector_t block = (sector_t)(u64)rd->args[1];
    unsigned int size = (unsigned int)(u64)rd->args[2];    
    struct buffer_head *bh = (struct buffer_head *)regs_return_value(regs);    
    enum fault_area area_type=(block ? FAULT_AREA_SB1 : FAULT_AREA_SB0);
    if(bh)
    {
        f2fs_super = (char *)(bh)->b_data + F2FS_SUPER_OFFSET;
        rasf2fs_record_area_page((struct f2fs_super_block*)f2fs_super, area_type);
        rasf2fs_inject_buffer(bdev, f2fs_super,0,size-F2FS_SUPER_OFFSET,area_type);               
    }  
	return 0;
}

rasprobe_define(__bread);
rasprobe_define(get_meta_page);
static struct rasprobe* probes[]={
	&rasprobe_name(get_meta_page),
	&rasprobe_name(__bread),
};
	
static int cmd_main(void* data, int argc, char* args[])
{    	
	ras_retn_if(0 == argc , -EINVAL);
	ras_retn_if(args2fault(argc, args) , -EINVAL);
	return 0;
}

static int proc_ops_show(rF2fs)(struct seq_file *m, void *v)
{
    int i=0,j=0;
    struct list_head *area_list_head;
    struct list_head *pos,*next;
    struct fault_area_node *area_node;
    for(j=0;j<2;j++)
    {
        seq_printf(m, "sb%d\tpage_start\tpage_num\n",j);
        for(i=0;i<FAULT_AREA_MAX;i++)
            seq_printf(m,"%s\t%5d\t\t%5d\n",
            area2name(i),fault_injected.area_page[j][i].page_start,
            fault_injected.area_page[j][i].page_num);
    }
    
    seq_printf(m,"inject fault:\n");
    j=0;
    for(i=0;i<FAULT_AREA_MAX;i++)
    {
        area_list_head = &(fault_injected.area_list[i]);
        if(list_empty(area_list_head))   continue;
        list_for_each_safe(pos, next, area_list_head) {
            area_node=list_entry(pos, struct fault_area_node, st_list);
            if(i>FAULT_AREA_SB1)
                seq_printf(m, "%3d type=%10s area=%s start=%7d end=%7d offset=%4d size=%4d <%d done>\n",            
                j,type2name(area_node->fault.type),area2name(i),area_node->fault.start,area_node->fault.end,area_node->fault.offset,area_node->fault.size,area_node->fault.match);
            else
                seq_printf(m, "%3d type=%10s area=%s disk=%20s offset=%4d size=%4d <%d done>\n",
                j,type2name(area_node->fault.type),area2name(i),area_node->fault.disk,area_node->fault.offset,area_node->fault.size,area_node->fault.match);
            j++;
        }
    }	
//    seq_printf(m, "%s", buf);
	return 0;
}

static int proc_ops_open(rF2fs)(struct inode *inode, struct file *file)
{
	return single_open(file, proc_ops_show(rF2fs), NULL);
}

static ssize_t proc_ops_write(rF2fs)(struct file *filp, 
	const char __user *bff, size_t count, loff_t *data)
{
	char buf_cmd[256];
	if(unlikely(count >= sizeof(buf_cmd)))    
		return -ENOMEM;
	memset(buf_cmd , 0, sizeof(buf_cmd));
	ras_retn_iferr(copy_from_user(buf_cmd, bff, count));
	ras_retn_iferr(ras_args(buf_cmd, count, cmd_main, NULL));
	return count;
}

#define MODULE_NAME "rF2fs"
proc_ops_define(rF2fs);
static int debug = 1;
module_param(debug,int,S_IRUGO); 
static int tool_init(void)
{
    int i=0;
    //1. initialize memory
    ras_debugset(debug);
    ras_retn_iferr(ras_check());
    memset(&fault_injected, 0, sizeof(struct fault_list));
    rwlock_init(&fault_injected.rwk);
    //1.initialize list
    for(i=0;i<FAULT_AREA_MAX;i++)
        INIT_LIST_HEAD(&fault_injected.area_list[i]);
    //3. initialize probes and interface
    ras_retn_iferr(register_rasprobes(probes, ARRAY_SIZE(probes)));
    ras_retn_iferr(proc_init(MODULE_NAME,  &proc_ops_name(rF2fs), &fault_injected));
    return 0;
}

static void tool_exit(void)  
{
    int i;
    struct list_head *area_list_head;
    struct list_head *pos,*next;
    struct fault_area_node *st_offset;
    //1.destroy interface and probes
    proc_exit(MODULE_NAME);
    unregister_rasprobes(probes, ARRAY_SIZE(probes));
    for(i=0;i<FAULT_AREA_MAX;i++)
    {
        area_list_head = &(fault_injected.area_list[i]);
        if(list_empty(area_list_head)) continue;
        list_for_each_safe(pos, next, area_list_head) {
            st_offset=list_entry(pos, struct fault_area_node, st_list);
            list_del_init(pos);
            kfree(st_offset);
        }
    }
}

module_init(tool_init);  
module_exit(tool_exit);  
MODULE_DESCRIPTION("F2FS faults inject.");  
MODULE_LICENSE("GPL"); 
MODULE_VERSION("V001R001C151-1.0");
