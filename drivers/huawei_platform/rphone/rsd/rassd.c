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

typedef enum __fault_type{
	FAULT_NA=-1,
	FAULT_INIT,
	FAULT_READ,
	FAULT_WRITE,
	FAULT_READONLY,
}fault_type;

typedef struct __fault_conf{
	const char *name;
	fault_type type;
}fault_conf;

static const fault_conf fault_confs[]={
	{.name="init", .type=FAULT_INIT, },
	{.name="read", .type=FAULT_READ, },
	{.name="write", .type=FAULT_WRITE,},
	{.name="readonly", .type=FAULT_READONLY, },
};

typedef struct __fault{
	fault_type type;
	int delay;
	int cmd;
	int bit; 
	int byte;
	int offset_bit;
	int offset_byte;
}fault;

#define FAULT_MAX 32
typedef struct  __fault_injected
{
	rwlock_t rwk;
	fault faults[FAULT_MAX];
}fault_injected;

struct sd_work {
	struct delayed_work w; 
	struct mmc_request *mrq;
	void (*done_orig)(struct mmc_request *);
};

static fault_injected fault_list;	//record the faults which was injected.
static struct workqueue_struct* wq = NULL;
static struct kmem_cache *sd_work_cache = NULL;
static unsigned int read_delay = 0;
static unsigned int write_delay = 0;

static fault* getfault(fault_type type)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_list.faults); i++)
	{
		if_then_retn(fault_list.faults[i].type == type, (fault*)&fault_list.faults[i]);
	}
	return NULL;
}

static const char* type2name(fault_type type)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_confs); i++)
	{
		if_then_retn(fault_confs[i].type == type, fault_confs[i].name);
	}
	return "fault_unknow";
}

static fault_type name2type(const char *name)
{
	int i = 0;
	for(i = 0; i<ARRAY_SIZE(fault_confs); i++)
	{
		if_then_retn(strcmp(name, fault_confs[i].name)==0, fault_confs[i].type);
	}
	return FAULT_NA;
}
void init_fault(fault* fault_temp)
{
	fault_temp->type = -1;
	fault_temp->delay= -1;
	fault_temp->cmd  = -1;
	fault_temp->bit  = -1;
	fault_temp->byte = -1;
	fault_temp->offset_byte=-1;
	fault_temp->offset_bit=-1;
}

void init_fault_all(void){
	int i = 0;
	for( i = 0; i < ARRAY_SIZE(fault_list.faults); i++)
	{
		init_fault(&fault_list.faults[i]);
	}
}

static int args_set(fault* fault_temp, char* prm)
{
    if(0 == prm) return 0;
    rasbase_set_func(fault_temp, type, prm,name2type);
    rasbase_set(fault_temp, cmd, prm);
    rasbase_set(fault_temp, offset_bit, prm);
	rasbase_set(fault_temp, offset_byte, prm);
    rasbase_set(fault_temp, bit, prm);
	rasbase_set(fault_temp, byte, prm);
    rasbase_set(fault_temp, delay, prm); 
    ras_retn(-EINVAL);
}

#define CHECK_RANGE_BIT(bit) (bit == 0 || bit == 1)
#define CHECK_RANGE_BYTE(byte) (byte >= 0 && byte <= 0xFF)
static int check_fault(fault *fault_temp)
{
	ras_retn_if((fault_temp->type ==FAULT_NA && fault_temp->cmd == -1), -EINVAL);	//no fault
	ras_retn_if((fault_temp->type !=FAULT_NA && fault_temp->cmd != -1), -EINVAL);	//fault  conflict
	if(fault_temp->cmd != -1){
		if(fault_temp->offset_bit < 0 && fault_temp->offset_byte < 0) return -EINVAL;
		if(fault_temp->offset_bit  >= 0 && !CHECK_RANGE_BIT(fault_temp->bit)) return -EINVAL;
		if(fault_temp->offset_byte >= 0 && !CHECK_RANGE_BYTE(fault_temp->byte)) return -EINVAL;
	}
	return 0;
}

static int fill_fault(fault *fault_temp)
{
	int i = 0;
	fault *fault_pos = NULL;
	ras_retn_iferr(check_fault(fault_temp));
	for( i = 0; i < ARRAY_SIZE(fault_list.faults); i++)
	{
		if(fault_list.faults[i].type == FAULT_NA && fault_list.faults[i].cmd == -1 && fault_pos == NULL){
			fault_pos = &fault_list.faults[i];
			continue;
		}
		//Error: init/read/write/readonly
		if(fault_temp->type != FAULT_NA){
			if(fault_list.faults[i].type == fault_temp->type){
				fault_pos = &fault_list.faults[i];
				break;
			}
		}
		//Error: sd commands
		else if(fault_list.faults[i].cmd == fault_temp->cmd){
			if(( fault_list.faults[i].offset_bit == fault_temp->offset_bit && fault_temp->offset_bit >= 0)\
			|| (fault_list.faults[i].offset_byte == fault_temp->offset_byte&&fault_temp->offset_byte >= 0)){
				fault_pos = &fault_list.faults[i];
				break;
			}
		}
	}
	if(fault_pos != NULL ){
		memcpy(fault_pos, fault_temp, sizeof(fault));
		return 0;
	}
	return -EINVAL;
}

//Convert arguments to faults, then inject and inject them.
static int args2fault(int args, char *argv[])
{
	int i = 0;
	fault fault_current;
	//covert args to fault
	init_fault(&fault_current);

	for(i=0; i<args; i++){
		ras_retn_iferr(args_set(&fault_current, argv[i]));
	}
	//fill the faults
	ras_retn_iferr(fill_fault(&fault_current));
	if(fault_current.type == FAULT_READ )  read_delay  = fault_current.delay;
	if(fault_current.type == FAULT_WRITE ) write_delay = fault_current.delay;
	return 0;
}

static int rasprobe_handler(mmc_sd_get_cid)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	if( getfault(FAULT_INIT) && regs_return_value(regs)==0 ){  
		rasprobe_seturn(regs, -EINVAL);	
	}
	return 0;
}

#ifdef CONFIG_MMC_DW
static int rasprobe_handler(dw_mci_get_ro)(struct rasprobe_instance *ri, struct pt_regs *regs) 
#else
static int rasprobe_handler(sdhci_check_ro)(struct rasprobe_instance *ri, struct pt_regs *regs)
#endif
{
       if( getfault(FAULT_READONLY) && regs_return_value(regs)==0 ){
            rasprobe_seturn(regs, 1);
       }
       return 0;
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
	delay = data->flags & MMC_DATA_READ ? read_delay:write_delay;
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
	delay = data->flags & MMC_DATA_READ ? read_delay:write_delay;
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

void ras_clr_bit(u8 *pos, u8 offset){
	
	*pos &= ~(1<<offset);
}

void ras_set_bit(u8 *pos, u8 offset){
	*pos |= (1<<offset);
}

int buf_byte_inject(u32 *pos, u32 len, int offset, int byte){
	u8 *temp = (u8*)pos;
	if(offset <0 && offset >= len ) return -1;
	temp += offset;
	*temp= (u8)byte;
	return 0;
}

int buf_bit_inject(u32 *pos, u32 len, int offset, char bit){
	u8 *temp = (u8*)pos;
	int byte_pos = offset/8;
	int bit_pos =  offset%8;
	if(offset <0 && offset >= len ) return -1;
	temp += byte_pos;
	(bit == 0) ? ras_clr_bit(temp, bit_pos):ras_set_bit( temp, bit_pos);
	return 0;
}
static int is_record = 0;
void cmd_record(struct mmc_command *cmd){
	if(!is_record) return;
	printk("sd_cmd:%2d ", cmd->opcode);
	printk("response:%08X %08X %08X %08X\n", cmd->resp[0],cmd->resp[1],cmd->resp[2],cmd->resp[3]);
}

int cmd_inject(const char * name, struct mmc_command *cmd){
	int i = 0;
	fault *fault_temp = NULL;
	if(cmd == 0) return -1;
	if(strcmp("mmc1", name) != 0) return -1;
	for( i = 0; i < ARRAY_SIZE(fault_list.faults); i++){
		fault_temp = &fault_list.faults[i];
		if(fault_temp->cmd == cmd->opcode){
			buf_byte_inject(cmd->resp, 4*sizeof(u32), fault_temp->offset_byte, fault_temp->byte);
			buf_bit_inject(cmd->resp, 8*4*sizeof(u32), fault_temp->offset_bit, fault_temp->bit);
		}
	}
	cmd_record(cmd);
	return 0;
}

static int rasprobe_handler_entry(mmc_request_done)(struct rasprobe_instance *ri, struct pt_regs *regs)
{
	struct mmc_host *host   = NULL;
        struct mmc_request *mrq = NULL;
        struct mmc_command *cmd = NULL;
        struct mmc_data *data   = NULL;
        fault *fault_temp = NULL;
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
	//do cmd inject,
	cmd_inject(mmc_hostname(host), cmd);
	if (!host->card || !mmc_card_sd(host->card)) return 0;	
	if (!data || !cmd || cmd->error || data->error) return 0;
	read = data->flags & MMC_DATA_READ;
	write= data->flags & MMC_DATA_WRITE;
	
	if( (  read  && (fault_temp = getfault(FAULT_READ) ) ) \
	||  (  write && (fault_temp = getfault(FAULT_WRITE)) ) ){
		if(fault_temp->delay > 0){	//delay
			if(done_fun == mrq->done)
				mrq->done = replace_done; 
			else if(data_done_fun == mrq->done)
				mrq->done = replace_data_done; 
		}
		else{	//error
			data->error = data_errors[prandom_u32() % ARRAY_SIZE(data_errors)];
			data->bytes_xfered = (prandom_u32() % (data->bytes_xfered >> 9)) << 9;
		}
	}	
	return 0;
}

rasprobe_define(mmc_sd_get_cid);
#ifdef CONFIG_MMC_DW
rasprobe_define(dw_mci_get_ro);
#else
rasprobe_define(sdhci_check_ro);
#endif

rasprobe_entry_define(mmc_request_done);
static struct rasprobe* probes[]={
	&rasprobe_name(mmc_sd_get_cid),
	#ifdef CONFIG_MMC_DW
	&rasprobe_name(dw_mci_get_ro),
	#else
	&rasprobe_name(sdhci_check_ro),
	#endif
	&rasprobe_name(mmc_request_done),
};

static int cmd_main(void* data, int argc, char* args[])
{    	
	ras_retn_if(0 == argc , -EINVAL);
	if(strcmp(args[0], "record") == 0) {
		is_record = 1;
		return 0;
	}
	if(strcmp(args[0], "unrecord") == 0) {
		is_record = 0;
		return 0;
	}
	
	ras_retn_if(0 != args2fault(argc, args) , -EINVAL);
	return 0;
}

static int proc_ops_show(rSd)(struct seq_file *m, void *v)
{
	int i = 0;
	fault *fault_temp = NULL;
//	write_lock(&fault_injected.rwk);
	for(i = 0; i < ARRAY_SIZE(fault_list.faults); i++){
		fault_temp = &fault_list.faults[i];
		if(fault_temp->type == FAULT_NA && fault_temp->cmd == 0)
			continue;
		if(fault_temp->type != FAULT_NA){
			seq_printf(m, "%2d\t type=%s ", i,type2name(fault_temp->type));
			if(fault_temp->delay > 0)
				seq_printf(m, "delay=%d(ms) ", fault_temp->delay );
			
			seq_printf(m,"\n");
		}
		if(fault_temp->cmd != -1){
			seq_printf(m, "%2d cmd=%2d ", i,fault_temp->cmd);
			if(fault_temp->offset_byte >0)
				seq_printf(m, "offset_byte=%d byte=0x%X ", fault_temp->offset_byte, fault_temp->byte);
			if(fault_temp->offset_bit >0)
				seq_printf(m, "offset_bit=%d bit=%d ", fault_temp->offset_bit, fault_temp->bit);
			
			seq_printf(m,"\n");
		}	
	}
//	write_unlock(&fault_injected.rwk);
	return 0;
}

static int proc_ops_open(rSd)(struct inode *inode, struct file *file)
{
	return single_open(file, proc_ops_show(rSd), NULL);
}

static ssize_t proc_ops_write(rSd)(struct file *filp, 
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

#define MODULE_NAME "rSd"
proc_ops_define(rSd);
static int tool_init(void)  
{
	//1. initialize memory
	ras_debugset(1);
	ras_retn_iferr(ras_check());
	init_fault_all();
	rwlock_init(&fault_list.rwk);
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
	ras_retn_iferr(proc_init(MODULE_NAME,  &proc_ops_name(rSd), &fault_list));
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
	init_fault_all();
}

module_init(tool_init);  
module_exit(tool_exit);  
MODULE_DESCRIPTION("SD faults inject.");  
MODULE_LICENSE("GPL"); 
MODULE_VERSION("V001R001C151-1.0");
