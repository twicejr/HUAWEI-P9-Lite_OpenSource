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
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>
#include <linux/blkdev.h>
#include <linux/random.h>
#define MSEC(time) (time*HZ/1000)

#define  if_then(con, work) if(con) work
#define  if_then_retn(con, work) if(con) return work
#define  if_then_else(con, work, work_else) if(con) work; else work_else
#define  if_then_else_retn(con, work) if(con) return work; else return work_else

enum fault_type 
{
        FAULT_NONE=0,
        FAULT_READ_FAILED,
        FAULT_WRITE_FAILED,
        FAULT_READ_DELAY,
        FAULT_WRITE_DELAY,
		FAULT_READ_DELAY_NONBLOCK,
        FAULT_WRITE_DELAY_NONBLOCK,
};

struct fault_ops 
{
	const char *name;	
	enum  fault_type type;
};
static const struct fault_ops fault_ops_list[]=
{
	{.name="r_failed", .type=FAULT_READ_FAILED, },
	{.name="w_failed", .type=FAULT_WRITE_FAILED,},
	{.name="r_delay",  .type=FAULT_READ_DELAY,  },
	{.name="w_delay",  .type=FAULT_WRITE_DELAY, },
	{.name="r_delay_noblk",  .type=FAULT_READ_DELAY_NONBLOCK,  },
	{.name="w_delay_noblk",  .type=FAULT_WRITE_DELAY_NONBLOCK, },
};

struct fault_impl
{
	unsigned int delay;
	enum  fault_type type;
};
#define FAULT_MAX 32
struct  fault_list
{
	rwlock_t rwk;
	struct fault_impl impl[FAULT_MAX];
};

struct sd_work {
	struct delayed_work w; 
	struct mmc_request *mrq;
	void (*done_orig)(struct mmc_request *);
};

static struct fault_list fault_injected;	//record the faults which was injected.
static struct workqueue_struct* wq = NULL;
static struct kmem_cache *sd_work_cache = NULL;
static unsigned int read_delay_noblk = 0;
static unsigned int write_delay_noblk = 0;

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

//Convert arguments to faults, then inject and inject them.
static struct fault_impl* args2fault(int args, char *argv[])
{
	int i = 0;
	long long delay = 0;
	struct fault_impl *fault = NULL;
	enum fault_type type = FAULT_NONE;
	//1. check the commands arg[0]: the fault mode name  arg[1]:some other configuration of the fault
	if_then_retn( (type = name2type(argv[0]) ) == FAULT_NONE, NULL);
	if( type >= FAULT_READ_DELAY && args >=2  ){ 
		ras_atoll(&delay, argv[1], strlen(argv[1]), 0);
		if_then_retn( delay <= 0, NULL);
	}
	//2. manage the faults
	read_lock(&fault_injected.rwk);
	for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++)
	{
		if(fault == NULL && fault_injected.impl[i].type == FAULT_NONE)
			fault = & fault_injected.impl[i];
		
		if(fault_injected.impl[i].type == type)	//fault already exist.
		{
			if(type >= FAULT_READ_DELAY && type <= FAULT_WRITE_DELAY_NONBLOCK ){
				fault = & fault_injected.impl[i];
			}
			else{
				fault = NULL;	//do nothing
			}
			break;
		}
	}
	read_unlock(&fault_injected.rwk);
	//3. inject
	if(NULL == fault) return NULL;
	write_lock(&fault_injected.rwk);
	fault->type = type;
	fault->delay= delay;
	if(type == FAULT_WRITE_DELAY_NONBLOCK) write_delay_noblk = delay;
	if(type == FAULT_READ_DELAY_NONBLOCK)  read_delay_noblk = delay;
	write_unlock(&fault_injected.rwk);
	return fault;
}

struct fault_impl* fault_include(enum fault_type type){
	int i =0;
	struct fault_impl *fault = NULL;
	//read_lock(&fault_injected.rwk);
	for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++){
		if(fault_injected.impl[i].type == type){
			fault = &fault_injected.impl[i];
			break;
		}
	}
	//read_unlock(&fault_injected.rwk);
	return fault;
}

#include <asm/delay.h>
void delay_block(unsigned long long ms){
	while(ms){
		if(ms >= 10){
			udelay(10000);
			ms -= 10;
		}
		else{
			udelay(ms*1000);
			ms = 0;
		}
	}
}

typedef void (*replace_fun)(struct mmc_request *mrq);
static replace_fun done_fun = NULL;
static replace_fun data_done_fun = NULL;
void sd_work_handler(struct work_struct* w)
{
	struct sd_work *wk = (struct sd_work *)w;
	wk->mrq->done = wk->done_orig;
	wk->mrq->done(wk->mrq);
	kmem_cache_free(sd_work_cache,wk);
}

void replace_done(struct mmc_request *mrq)
{
	struct sd_work *sd_work;
	struct mmc_data *data = mrq->data;
	unsigned long delay = 0;
	delay = data->flags & MMC_DATA_READ ? read_delay_noblk:write_delay_noblk;
	sd_work = kmem_cache_alloc(sd_work_cache, GFP_ATOMIC);
	if(!sd_work) {
		mrq->done(mrq);
		return ;
	}
	INIT_DELAYED_WORK(&sd_work->w, sd_work_handler);
	sd_work->mrq  = mrq;
	sd_work->done_orig = done_fun;
	queue_delayed_work(wq, &sd_work->w, MSEC(delay));
}

void replace_data_done(struct mmc_request *mrq)
{
	struct sd_work *sd_work;
	struct mmc_data *data = mrq->data;
	unsigned long delay = 0;
	delay = data->flags & MMC_DATA_READ ? read_delay_noblk:write_delay_noblk;
	sd_work = kmem_cache_alloc(sd_work_cache, GFP_ATOMIC);
	if(!sd_work) {
		mrq->done(mrq);
		return ;
	}
	INIT_DELAYED_WORK(&sd_work->w, sd_work_handler);
	sd_work->mrq  = mrq;
	sd_work->done_orig = data_done_fun;
	queue_delayed_work(wq, &sd_work->w, MSEC(delay));
}

static int rasprobe_handler_entry(mmc_request_done)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	struct mmc_host *host   = NULL;
	struct mmc_request *mrq = NULL;
	struct mmc_command *cmd = NULL;
	struct mmc_data *data   = NULL;
	struct fault_impl *fault= NULL;
	struct RasRegs *rr = NULL;
	int read,write;
	static const int data_errors[] = {
		-ETIMEDOUT,
		-EILSEQ,
		-EIO,
	};
	rasprobe_entry(ri,regs);
	rr = (struct RasRegs *)ri->data;
	host= (struct mmc_host *)rr->args[0];
	mrq = (struct mmc_request *)rr->args[1];
	cmd = mrq->cmd;
	data= mrq->data;
	if (!host->card || mmc_card_sd(host->card)) return 0;	
	if (!data || !cmd || cmd->error || data->error) return 0;
	read = data->flags & MMC_DATA_READ;
	write= data->flags & MMC_DATA_WRITE;
	//read or write failed.
	if( (  read  && (fault = fault_include(FAULT_READ_FAILED) ) ) \
	||  (  write && (fault = fault_include(FAULT_WRITE_FAILED)) ) )
	{
		data->error = data_errors[prandom_u32() % ARRAY_SIZE(data_errors)];
		data->bytes_xfered = (prandom_u32() % (data->bytes_xfered >> 9)) << 9;
		return 0;
	}
	//read or write delay (blocked).
	if( ( read  && (fault = fault_include(FAULT_READ_DELAY) ) ) \
	||  ( write && (fault = fault_include(FAULT_WRITE_DELAY)) ) )
	{
		delay_block(fault->delay);
		return 0;
	}
	//read or write delay (unblocked).
	if( ( read  && (fault = fault_include(FAULT_READ_DELAY_NONBLOCK) ) ) \
	||  ( write && (fault = fault_include(FAULT_WRITE_DELAY_NONBLOCK)) ) )
	{
		if(done_fun == mrq->done)
			mrq->done = replace_done; 
		else if(data_done_fun == mrq->done)
			mrq->done = replace_data_done; 
	}
	return 0;
}

rasprobe_entry_define(mmc_request_done);
static struct rasprobe* probes[]={
	&rasprobe_name(mmc_request_done),
};

static int cmd_main(void* data, int argc, char* args[])
{    	
	ras_retn_if(0 == argc , -EINVAL);
	ras_retn_if(NULL==args2fault(argc, args) , -EINVAL);
	return 0;
}

static int proc_ops_show(rEmmc)(struct seq_file *m, void *v)
{
	int i = 0;
	struct fault_impl *impl = NULL;
//	write_lock(&fault_injected.rwk);
	for(i = 0; i < ARRAY_SIZE(fault_injected.impl); i++){
		impl = &fault_injected.impl[i];
		if(impl->type == FAULT_NONE)
			continue;
		if(impl->delay)
			seq_printf(m, "%2d\t%s\t%d(ms)\n", i, type2name(impl->type),impl->delay );	
		else
			seq_printf(m, "%2d\t%s\n", i, type2name(impl->type));
	}
//	write_unlock(&fault_injected.rwk);
	return 0;
}

static int proc_ops_open(rEmmc)(struct inode *inode, struct file *file)
{
	return single_open(file, proc_ops_show(rEmmc), NULL);
}

static ssize_t proc_ops_write(rEmmc)(struct file *filp, 
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

#define MODULE_NAME "rEmmc"
proc_ops_define(rEmmc);
static int tool_init(void)  
{
	//1. initialize memory
	ras_debugset(1);
	ras_retn_iferr(ras_check());
	memset(&fault_injected, 0, sizeof(struct fault_list));
	rwlock_init(&fault_injected.rwk);
	//2. initialize delay workqueue
	done_fun = (replace_fun)kallsyms_lookup_name("mmc_wait_done");
	data_done_fun = (replace_fun)kallsyms_lookup_name("mmc_wait_data_done");
	ras_retn_if(!done_fun || !data_done_fun, -EINVAL);
	wq = create_singlethread_workqueue("sd_fit_workqueue"); 
	ras_retn_if(!wq, -EINVAL);
	sd_work_cache = kmem_cache_create("sd_fit_work", sizeof(struct sd_work), 0, SLAB_HWCACHE_ALIGN|SLAB_PANIC, NULL);
	if(!sd_work_cache)	{
		destroy_workqueue(wq);
		return -EINVAL;
	}
	//3. initialize probes and interface
	ras_retn_iferr(register_rasprobes(probes, ARRAY_SIZE(probes)));
	ras_retn_iferr(proc_init(MODULE_NAME,  &proc_ops_name(rEmmc), &fault_injected));
	return 0;
}
static void tool_exit(void)  
{  
	//1.destroy interface and probes
	proc_exit(MODULE_NAME);
	unregister_rasprobes(probes, ARRAY_SIZE(probes));
	//2.destroy the workqueue and clean memory
	flush_workqueue(wq);
	destroy_workqueue(wq);
	kmem_cache_destroy(sd_work_cache);
	memset(&fault_injected, 0, sizeof(struct fault_list));
}

module_init(tool_init);  
module_exit(tool_exit);  
MODULE_DESCRIPTION("SD faults inject.");  
MODULE_LICENSE("GPL"); 
MODULE_VERSION("V001R001C151-1.0");
