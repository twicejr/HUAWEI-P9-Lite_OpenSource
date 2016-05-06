#include "../rasbase/rasbase.h"
#include "../rasbase/rasprobe.h"
#include "../rasbase/rasproc.h"
#include <linux/kernel.h>
#include <linux/bio.h>
#include <linux/genhd.h>
#include <linux/module.h>
#include <linux/blk_types.h>
#include <linux/blkdev.h>
#include <linux/delay.h>
#include <linux/random.h>

enum fault_type
{
    FAULT_NONE=0,
    FAULT_R_FAILED,  /*read failed,care or no care address,or failed till write*/
    FAULT_W_FAILED,  /*write failed, care or no care address*/    
    FAULT_R_DELAY, /*read delay, care or no care address*/
    FAULT_W_DELAY,   /*write delay, care or no care address*/   
    FAULT_R_LOST,
    FAULT_W_LOST
};

struct fault_ops
{
    const char *name;
    enum  fault_type type;
};

// the stubs is the indexs of probe_manager, start from 1 not 0.
static struct fault_ops fault_ops_array[]=
{
    {.name="r_failed",        .type=FAULT_R_FAILED},
    {.name="w_failed",        .type=FAULT_W_FAILED},  
       
    {.name="r_delay",         .type=FAULT_R_DELAY},
    {.name="w_delay",         .type=FAULT_W_DELAY},
     
    {.name="r_lost",       .type=FAULT_R_LOST},
    {.name="w_lost",       .type=FAULT_W_LOST},
    
};

//bio failed
struct bio_stub {
    bio_end_io_t		*bi_end_io;
    void			    *bi_private;
    unsigned int		 bi_size;
};

struct fault_queue_disk
{
    int res;
    struct gendisk  *gendisk;
    make_request_fn *make_request_fn;
};

/*fault impl*/
struct fault_impl
{
    enum  fault_type type;
    pid_t pid;
    long block;    
    long time;// timeout or delay
    char dir[BDEVNAME_SIZE];
    char disk[BDEVNAME_SIZE];
    //internal para
    long percent;
    long major;
    long minor;
    long match;
    struct fault_queue_disk queue_disk;
};
#define FAULT_MAX 32
struct  fault_list
{
    struct fault_impl impl[FAULT_MAX];    
    struct fault_queue_disk arr_queue_disk[FAULT_MAX];
    rwlock_t rwk;
};

static struct fault_list fault_injected; //record the faults which was injected.

static int fault_restore(struct fault_impl *fault)
{
    int i = 0;
    struct request_queue *q = NULL;
    
    //delay must restore gendisk queue request_fn
    if (fault->type <= FAULT_W_DELAY || fault->type >= FAULT_R_DELAY)
    {
        for(i = 0; i < ARRAY_SIZE(fault_injected.arr_queue_disk); i++)
        {
            if(!fault_injected.arr_queue_disk[i].gendisk) continue;
            if(fault_injected.arr_queue_disk[i].gendisk != fault->queue_disk.gendisk) continue;
            //restore when disk no used,then restore
            fault_injected.arr_queue_disk[i].res--;

            if(fault_injected.arr_queue_disk[i].res) continue;
            
            q = fault_injected.arr_queue_disk[i].gendisk->queue;
            q->make_request_fn = fault_injected.arr_queue_disk[i].make_request_fn;                
            fault_injected.arr_queue_disk[i].gendisk = NULL;
            fault_injected.arr_queue_disk[i].make_request_fn = NULL;
        }
    }
    memset(fault, 0, sizeof(struct fault_impl));
    return 0;
}

static int fault_restore_all(void)
{
    int i = 0;
    int ret = 0;    
    
    write_lock(&fault_injected.rwk);
    for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++)
    {
        ret |= fault_restore(&fault_injected.impl[i]);
    }  
    write_unlock(&fault_injected.rwk);
    return ret;
}

static struct fault_ops* get_fault_ops(enum fault_type type)
{
    int i = 0;
    for(i = 0; i < ARRAY_SIZE(fault_ops_array); i++)
    {
        if(fault_ops_array[i].type == type)
            return &fault_ops_array[i]; 
    }
    return NULL;
}

static const char* type2name(enum fault_type type)
{
    struct fault_ops *ops = get_fault_ops(type);	
    if(!ops) return "fault_unknow";
	return ops->name;
}

static enum fault_type name2type(const char *name)
{
    int i = 0;
    for(i = 0; i < ARRAY_SIZE(fault_ops_array); i++)
    {
        if(strcmp(name, fault_ops_array[i].name)==0)
            return fault_ops_array[i].type;
    }
    return FAULT_NONE;
}

static int rasio_args_set(struct fault_impl* fault_args, char* prm)
{
    if(0 == prm) return 0;
    rasbase_set_func(fault_args, type, prm,name2type);
    rasbase_set(fault_args, pid, prm);
    rasbase_set(fault_args, time, prm);
    rasbase_set(fault_args, block, prm);
    rasbase_set(fault_args, percent, prm);
    rasbase_cset(fault_args, disk,prm);
    rasbase_cset(fault_args, dir,prm);
    rasbase_set(fault_args, major,prm);
    rasbase_set(fault_args, minor,prm);
    return 0;
}

static int rasio_args_parse(struct fault_impl *fault_args, int args, char *argv[])
{
    int i;
    for(i = 0; i< args; i++)
    {
        ras_retn_iferr(rasio_args_set(fault_args, argv[i]));
    }
    
    ras_retn_if((fault_args->type == FAULT_NONE), -EINVAL);   
    if(fault_args->percent == 0) fault_args->percent = 100;
    return 0;
}

//Conver args to faults, then inject and manage them.
static struct fault_impl* args2fault(int args, char *argv[])
{
    int i;
    struct fault_impl *fault_cur = NULL;    
    struct fault_impl fault_args;
    memset(&fault_args, 0, sizeof(fault_args));
    
    //1. check the args    
    if(args < 1) return NULL;
    if(rasio_args_parse(&fault_args, args, argv)) return NULL;
    if((fault_args.type <= FAULT_W_DELAY && fault_args.type >= FAULT_R_DELAY) && (fault_args.time == 0)) return NULL;

    //2. manage the faults
    write_lock(&fault_injected.rwk);
    for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++)
    {
        if(fault_cur == NULL && fault_injected.impl[i].type == FAULT_NONE)
        {
            fault_cur = &fault_injected.impl[i]; 
        }
        //check fault exist, check type/pdi/disk
        if(fault_injected.impl[i].type == fault_args.type 
            && ((fault_injected.impl[i].pid == fault_args.pid) || (fault_args.pid == 0 || fault_injected.impl[i].pid == 0))
            && ((0 == strcmp(fault_args.disk, fault_injected.impl[i].disk))))
        {
            //fault alread exist. 
            if ((fault_args.type >= FAULT_R_DELAY && fault_args.type <= FAULT_W_DELAY) 
                && (fault_injected.impl[i].pid == fault_args.pid && (0 == strcmp(fault_args.disk, fault_injected.impl[i].disk))))
            {
                fault_cur = &fault_injected.impl[i];
                fault_args.queue_disk.gendisk = fault_cur->queue_disk.gendisk;
                fault_args.queue_disk.make_request_fn = fault_cur->queue_disk.make_request_fn;
            }
            else
            {
                fault_cur = NULL;
                break;
            }
        }        
    }
    
    //3. got it and inject it.
    if(fault_cur)
        memcpy(fault_cur,&fault_args,sizeof(struct fault_impl));
    write_unlock(&fault_injected.rwk);
    return fault_cur;
}

struct fault_impl* fault_include(enum fault_type type, pid_t pid)
{
	int i =0;
	struct fault_impl *fault = NULL;
    
	read_lock(&fault_injected.rwk);
	for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++)
    {
		if((fault_injected.impl[i].type == type) && ((fault_injected.impl[i].pid == pid) || (fault_injected.impl[i].pid == 0)))
        {
			fault = &fault_injected.impl[i];
			break;
		}
	}
	read_unlock(&fault_injected.rwk);
    
	return fault;
}

static int fault_restore_one(int args,char *argv[])
{
    int i=0,find = 0;
    struct fault_impl fault_args;
    
    //1. check the args
    memset(&fault_args, 0, sizeof(fault_args));
    ras_retn_if((args < 2) , -EINVAL);    
    ras_retn_if(rasio_args_parse(&fault_args, args, argv), -EINVAL);

    //2. manage the faults
    write_lock(&fault_injected.rwk);
    for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++)
    {        
        if(fault_injected.impl[i].type == fault_args.type 
            && ((fault_injected.impl[i].pid == fault_args.pid) || (fault_args.pid == 0 || fault_injected.impl[i].pid == 0))
            && ((0 == strcmp(fault_args.disk, fault_injected.impl[i].disk))))
        {            
            fault_restore(&fault_injected.impl[i]);
            find = 1;
        }        
    }
    write_unlock(&fault_injected.rwk);

    ras_retn_if((!find), -EINVAL);
    return 0;
}

static struct fault_impl * rasio_check_fault_match(struct bio *bio, enum fault_type mode, bool isRw)
{
    struct fault_impl *fault = fault_include(mode, current->pid);
    int random_val = 0;
    char buf[BDEVNAME_SIZE];

    if(!fault) return NULL;
    if(!isRw)  return NULL;
    
    // match disk_name,
    bdevname(bio->bi_bdev, buf);
    if((0 != strcmp(buf,fault->disk)) && (0 != strcmp(bio->bi_bdev->bd_disk->disk_name,buf))) return NULL;
    
    random_val = prandom_u32();
    if(fault->percent <= random_val % 100) return NULL;
    return fault;
}

static void rasio_io_fail(struct bio *bio, int error)
{
	struct bio_stub *b = bio->bi_private;    
	
    bio->bi_private = b->bi_private;
    bio->bi_end_io = b->bi_end_io;
    bio->bi_size =  b->bi_size;
	kfree(b);
	bio_io_error(bio);
    return;
}

static int rasprobe_handler_entry(generic_make_request_checks)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
    struct bio     *bio    = NULL;
    struct bio_stub *b      = NULL;
    struct RasRegs *rr     = NULL;
    struct fault_impl  *fault = NULL;
    unsigned long  bio_rw  = 0;
    
    rasprobe_entry(ri,regs);
    rr = (struct RasRegs *)ri->data;
    bio = (struct bio*)rr->args[0];
    
    if(!bio) return 0;
    bio_rw = bio_data_dir(bio);   
   
    if ((fault = rasio_check_fault_match(bio, FAULT_R_FAILED, (bio_rw == READ))) || 
    (fault = rasio_check_fault_match(bio, FAULT_W_FAILED, (bio_rw == WRITE))))
    {
        fault->match++;
        b = kmalloc(sizeof(struct bio_stub), GFP_NOIO);        
		b->bi_private = bio->bi_private;
		b->bi_end_io  = bio->bi_end_io;
        b->bi_size    =  bio->bi_size;
        
        bio->bi_private = b;
        bio->bi_end_io  = rasio_io_fail;
        bio->bi_size    = UINT_MAX;
    }
    return  0;
}

static int rasprobe_handler(generic_make_request_checks)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
    //.io lost
    struct RasRegs    *rr    = (struct RasRegs *)ri->data;
    struct bio        *bio   = (struct bio *)rr->args[0];
    struct fault_impl  *fault = NULL;
    unsigned long     bio_rw = 0;
    
    if(!bio) return 0;
    bio_rw = bio_data_dir(bio);
    
    if ((fault = rasio_check_fault_match(bio, FAULT_R_LOST, (bio_rw == READ))) 
        || (fault = rasio_check_fault_match(bio, FAULT_W_LOST, (bio_rw == WRITE))))
    {
        if(regs_return_value(regs))
        {
            fault->match++;
            rasprobe_seturn(regs, 0);
        }
    }    
    return 0;
}

void rasio_make_request_fn(struct request_queue *q, struct bio *bio)
{
    struct fault_impl  *fault = NULL;
    int i,find = 0;
    make_request_fn *request_fn;
    //find fault,and get delay    
    if (!(fault = rasio_check_fault_match(bio, FAULT_R_DELAY,(bio_data_dir(bio) == READ))) 
        && !(fault = rasio_check_fault_match(bio, FAULT_W_DELAY, (bio_data_dir(bio) == WRITE))))
    {
        write_lock(&fault_injected.rwk);
        for(i = 0; i < ARRAY_SIZE(fault_injected.arr_queue_disk); i++)
        {
            if(fault_injected.arr_queue_disk[i].gendisk == bio->bi_bdev->bd_disk)
            {
                fault_injected.arr_queue_disk[i].make_request_fn(q,bio);
                find=1;
                break;
            }
        }
        write_unlock(&fault_injected.rwk);
        if(!find)
            ras_warn("rasio_make_request_fn can't find fault");
        return;
    }
    
    //check if fn is null return
    if(!fault->queue_disk.make_request_fn)
    {
        ras_warn("rasio_make_request_fn can't find fn");
        return;
    }
    request_fn = fault->queue_disk.make_request_fn;
    if(fault->time != 0)
    {
        fault->match++;
        ras_sleep(fault->time);
    }
    request_fn(q,bio);
    return;
}

int rasio_delay(struct fault_impl *fault)
{
    struct gendisk *disk;
    int ipart,i,n=-1;
    struct request_queue *q;
    
    ras_retn_if((fault->queue_disk.gendisk), 0);
    /*1.find gendisk*/
    disk = get_gendisk(MKDEV(fault->major, fault->minor), &ipart);
    if(!disk) 
    {
        ras_fail("can't find disk");
        return -EINVAL;
    }
    
    /*2.instead request fn*/
    write_lock(&fault_injected.rwk);
    for(i = 0; i < ARRAY_SIZE(fault_injected.arr_queue_disk); i++)
    {
        if(fault_injected.arr_queue_disk[i].gendisk == disk)
        {
            fault_injected.arr_queue_disk[i].res++;
            
            fault->queue_disk.gendisk=disk;            
            fault->queue_disk.make_request_fn = fault_injected.arr_queue_disk[i].make_request_fn;
            n = FAULT_MAX;/*find*/
            break;
        }
        if((!fault_injected.arr_queue_disk[i].gendisk) && n < 0)
        {
            n = i;
        }
    }
    if(n < FAULT_MAX && n > -1)
    {
        fault_injected.arr_queue_disk[n].gendisk = disk;
        q = disk->queue;
        fault->queue_disk.gendisk=disk;
        fault->queue_disk.make_request_fn = q->make_request_fn;        
        
        fault_injected.arr_queue_disk[n].make_request_fn = q->make_request_fn;        
        q->make_request_fn = rasio_make_request_fn;
        fault_injected.arr_queue_disk[n].res= 1;        
    }       
    write_unlock(&fault_injected.rwk);
    return 0;
}

static int cmd_main(void* data, int argc, char* args[])
{
    struct fault_impl *fault;    
    
    ras_retn_if(0 == args[0] , -EINVAL);
    if(args[0] == NULL) return -EINVAL;
    
    //1. clean
    ras_retn_if((strcmp(args[0], "clean") == 0),fault_restore_all());
    //1.1 restore
    ras_retn_if((strcmp(args[0],"restore") == 0),fault_restore_one(argc, args));
    
    //2. inject 
    fault = args2fault(argc, args);    
    ras_retn_if((!fault), -EINVAL);
    if(fault->type <= FAULT_W_DELAY && fault->type >= FAULT_R_DELAY)
        return rasio_delay(fault);    
    return 0;
}

static int proc_ops_show(rio)(struct seq_file *m, void *v)
{
    int i = 0;
    char buf[256]={0};
    struct fault_impl *impl = NULL;
    //   seq_printf(m, "SD-Tester!\n");

    write_lock(&fault_injected.rwk);
    for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++)
    {
        impl = &fault_injected.impl[i];
        if(impl->type == FAULT_NONE)
            continue;
        if(impl->type <FAULT_R_DELAY || impl->type > FAULT_W_DELAY)
            snprintf(buf, sizeof(buf), "%d %s %s %s %d,    match(%ld)\n", i, 
            type2name(impl->type),impl->dir,impl->disk,impl->pid,impl->match);
        else
            snprintf(buf, sizeof(buf), "%d %s %s %s %d,%ld(ms)    match(%ld)\n", i, 
            type2name(impl->type),impl->dir,impl->disk,impl->pid,impl->time,impl->match);
        seq_printf(m, "%s", buf);
    }

    write_unlock(&fault_injected.rwk);
    return 0;
}

static int proc_ops_open(rio)(struct inode *inode, struct file *file)
{    
    return single_open(file, proc_ops_show(rio), NULL);
}

static ssize_t proc_ops_write(rio)(struct file *filp,  
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

#define MODULE_NAME "rIO"
proc_ops_define(rio);
rasprobe_entry_exit_define(generic_make_request_checks);
static struct rasprobe* probes[]=
{
    &rasprobe_name(generic_make_request_checks),
};

static int tool_init(void)  
{
    ras_debugset(1);
    ras_retn_iferr(ras_check());
    ras_retn_iferr(register_rasprobes(probes, ARRAY_SIZE(probes)));
    
    memset(&fault_injected, 0, sizeof(struct fault_list));
    rwlock_init(&fault_injected.rwk);
    ras_retn_iferr(proc_init(MODULE_NAME,  &proc_ops_name(rio), &fault_injected));    
    return 0;
}

static void tool_exit(void)
{
    proc_exit(MODULE_NAME);
    unregister_rasprobes(probes, ARRAY_SIZE(probes));
    fault_restore_all();
}

module_init(tool_init);
module_exit(tool_exit);
MODULE_DESCRIPTION("IO faults inject.");
MODULE_LICENSE("GPL");
MODULE_VERSION("V001R001C151-1.0");
