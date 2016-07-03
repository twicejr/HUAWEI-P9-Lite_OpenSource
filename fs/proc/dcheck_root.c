#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/cred.h>
#include <linux/mm.h>
#include <linux/utsname.h>
#include <linux/mman.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/prctl.h>
#include <linux/highuid.h>
#include <linux/fs.h>
#include <linux/perf_event.h>
#include <linux/resource.h>
#include <linux/kernel.h>
#include <linux/kexec.h>
#include <linux/capability.h>
#include <linux/device.h>
#include <linux/key.h>
#include <linux/times.h>
#include <linux/posix-timers.h>
#include <linux/security.h>
#include <linux/suspend.h>
#include <linux/tty.h>
#include <linux/signal.h>
#include <linux/cn_proc.h>
#include <linux/getcpu.h>
#include <linux/task_io_accounting_ops.h>
#include <linux/seccomp.h>
#include <linux/cpu.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/fs_struct.h>
#include <linux/gfp.h>
#include <linux/syscore_ops.h>
#include <linux/version.h>
#include <linux/ctype.h>
#include <linux/compat.h>
#include <linux/syscalls.h>
#include <linux/user_namespace.h>
#include <linux/kmsg_dump.h>
#include <generated/utsrelease.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/unistd.h>
#include <linux/sched.h>
#include <linux/printk.h>
#include <linux/kmod.h>
#include <linux/stat.h>

#include <check_root.h>

extern struct checkroot_ref_cnt checkroot_ref;

#define root_log_filepath "/log/dcrt"
#define NA "NA"

static struct action_table act_table[] = 
{   
    {ACT_SETUID_NM,   WRT_SETUID},
    {ACT_SETGID_NM,   WRT_SETGID},
    {ACT_SETRESUID_NM,WRT_SETRESUID},
    {ACT_SETRESGID_NM,WRT_SETRESGID},
    {ACT_SBL1_NM,     WRT_SBL1},
    {ACT_ABOOT_NM,    WRT_ABOOT},
    {ACT_FTBT2_NM,    WRT_FTBT2},
    {ACT_BOOT_NM,     WRT_BOOT},
    {ACT_RECOVERY_NM, WRT_RECOVERY},
    {ACT_SYSTEM_NM,   WRT_SYSTEM},
    {ACT_MODEM_NM,    WRT_MODEM},
    {ACT_MODEM_FW_NM, WRT_MODEM_FW},    
    {ACT_CUST_NM,     WRT_CUST},
};



/*Must set  hwcwrt_work.action_type before use.*/
static int is_recorded(int action_type)
{

    if(checkroot_ref.drt_status & (1 <<action_type))
    {
        //printk(">>>>>>>>>>>>>>is_recorded:action=%d<<<<<<<<<<<<<<<<<\n", action_type);
        return 1;
    }
    else
    {
        return 0;
    }
 
}
static int get_ro_secure(void)
{
    int ro_secue = 0;
    int ret = 0;
    mm_segment_t old_fs;
    char buf_line[LOG_LINE_LEN];
    struct file *filp = NULL;
    loff_t pos=0;
    int i = 0;
    
    filp = filp_open(DEFAULT_PROP_FILE, O_RDONLY, 0644);
    if(NULL == filp){
        printk(KERN_WARNING "DEFAULT_PROP_FILE OPEN FAIL!\n");
        ro_secue = 1;        
        return ro_secue;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);

    while( (filp->f_inode->i_size-LOG_LINE_LEN*i) > 0 ){
        memset(buf_line, 0, LOG_LINE_LEN);
        ret = filp->f_op->read(filp, buf_line, LOG_LINE_LEN, &pos);
        if(strstr(buf_line,"ro.secure=1")){
            ro_secue = 1;
            break;
        }
        i++;
    }
    set_fs(old_fs);
    filp_close(filp,NULL);
    return ro_secue;
}
static int umh_exec_ckrt( void )
{
    
    int ret = 0;
    mm_segment_t old_fs;
    char* chrt_sys = "/system/bin/check_root";
    char* chrt_boot = "/sbin/check_root";
    char *argvs[] = { chrt_sys, NULL };
    char *argvb[] = { chrt_boot, NULL };
    char **argv = NULL;
    static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/bin:/system/sbin:/system/bin",
        NULL 
    };
    
    int fds = 0;
    int fdb = 0;   
    printk(KERN_WARNING "umh_exec_ckrt+\n");
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    fds = sys_open(chrt_sys, O_RDONLY, 0);
    fdb = sys_open(chrt_boot, O_RDONLY, 0);
    set_fs(old_fs);

    if(fds >= 0){
        argv = argvs;
        sys_close(fds);
    }else if(fdb >= 0){
        argv = argvb;
        sys_close(fdb);
        
    }else{
        printk(KERN_WARNING ">>>>>>>check_root fds = %d. <<<<<<<\n" , fds);
        printk(KERN_WARNING ">>>>>>>check_root fdb = %d. <<<<<<<\n", fdb);
        printk(KERN_WARNING ">>>>>>>check_root Not Found. <<<<<<<\n");
        return -1;
    }
    
    ret = call_usermodehelper( argv[0], argv, envp, UMH_WAIT_PROC);        
    if (ret != 0){
       printk(KERN_WARNING ">>>>>>>Error in call to usermodehelper:argvs=%s ret = %d <<<<<<<\n", argv[0],ret);
       return ret;
    }
    
    printk(KERN_WARNING "umh_exec_ckrt-\n");
    
    return 0;
}  

static char* get_exec_filep(struct task_struct* task, char*buf,int buf_len)
{
    char* ppath_str = NULL;
    if(NULL == task || NULL == buf){
        printk(KERN_ERR "get_exec_filep:task=%p,buf=%p\n", task,buf);
        return NULL;
    }
    
    if( NULL != task->mm && NULL != task->mm->exe_file ){
        ppath_str = d_path(&(task->mm->exe_file->f_path), buf, buf_len);
    }
    if (IS_ERR(ppath_str)) {
        return TOO_LONG_CONST_STR;
    } else{
        return ppath_str;
    }
}
static char* get_process_list(pid_t pid_nr)
{
    int i =0;
    struct pid* pidd = NULL;
    struct task_struct* task0=NULL;
    struct task_struct* task_tmp=NULL;
    char* process_list_str = NULL;
    int plist_buf_len = TASK_COMM_LEN*TASK_LIST_LEN*2;//com and pid buf len
    char* ppath = NULL;
    char* ppath_str = NULL;

    pidd = find_get_pid(pid_nr);
    if(IS_ERR(pidd)){
        printk(KERN_ERR "get_process_list %p\n", pidd);
        return NULL;
    }

    task0 = pid_task(pidd, PIDTYPE_PID);
    if(NULL == task0){
        printk(KERN_ERR ">>>>>>>>>>>>>>>>>>>task0=NULL<<<<<<\n");
        return NULL;
    }

    process_list_str = (char*)kmalloc(plist_buf_len, GFP_KERNEL);
    if(NULL == process_list_str){
        printk(KERN_ERR ">>>>>>>>>>>>>>>>>>>process_list_str=NULL:%p<<<<<<\n", process_list_str);
        return NULL;
    }    

    ppath = (char*)kmalloc(LOG_LINE_LEN, GFP_KERNEL);
    if(NULL == ppath){
        printk(KERN_ERR ">>>>>>>>>>>>>>>>>>>ppath=NULL:%p<<<<<<\n", ppath);
        return NULL;
    }    

    memset(process_list_str, 0, plist_buf_len);
    memset(ppath, 0, LOG_LINE_LEN);

    ppath_str =  get_exec_filep(task0,ppath,LOG_LINE_LEN);
    snprintf(process_list_str,TASK_COMM_LEN*4,"<%d>(%s:%s)",task0->pid,task0->comm,ppath_str);
    task_tmp = task0;
    for(i=0; i<TASK_LIST_LEN-1; i++)
    {
        memset(ppath, 0, LOG_LINE_LEN);
        task_tmp = task_tmp->real_parent;
        if( NULL == task_tmp ){
            printk(KERN_ERR ">>>>>>>>>>>>>>>>>>>task_tmp=NULL:%d<<<<<<\n", i);
            break;
        }
        ppath_str =  get_exec_filep(task_tmp,ppath,LOG_LINE_LEN);
        snprintf(process_list_str+strlen(process_list_str),TASK_COMM_LEN*4,",<%d>(%s:%s)",task_tmp->pid,task_tmp->comm,ppath_str);
    }
    kfree(ppath);    
    return process_list_str;
    
}



static char* build_log_buf(struct cwrt_work_t*hwcwrt_work)
{
    char *log_buf = NULL;
    struct rtc_time tm_android;
    struct timeval  tv_android;
    char *process_str = NULL;

    if(NULL == hwcwrt_work){
        return NULL;
    }
    log_buf = (char *)kmalloc(LOG_LINE_LEN, GFP_KERNEL);
    if(NULL == log_buf){
        printk(KERN_ERR "build_log_buf kmalloc fail.\n");
        return NULL;
    }

    memset(log_buf,0,LOG_LINE_LEN);
    
    do_gettimeofday(&tv_android);
    tv_android.tv_sec -= sys_tz.tz_minuteswest*60;
    rtc_time_to_tm(tv_android.tv_sec, &tm_android);

    process_str = get_process_list(hwcwrt_work->pid);
    snprintf(log_buf,LOG_LINE_LEN,"%d-%02d-%02d %02d:%02d:%02d,%s,%s,%s\n",
                          tm_android.tm_year + 1900, 
                          tm_android.tm_mon + 1, 
                          tm_android.tm_mday,
                          tm_android.tm_hour, 
                          tm_android.tm_min, 
                          tm_android.tm_sec,
                          act_table[hwcwrt_work->action_type].act_name,
                          hwcwrt_work->dev_name,
                          (NULL!=process_str)?process_str:"null");

    if(NULL!=process_str){
        kfree(process_str);
        process_str=NULL;
    }
    printk(KERN_WARNING "%s\n",log_buf);
    return log_buf;
}

static int wirte_user_file(struct cwrt_work_t* hwcwrt_work)
{
    struct file *filp;
    char* log_buf = NULL;
    mm_segment_t old_fs;
    
    int ret = 0;
    if(NULL == hwcwrt_work){
        return -1;
    }
    printk(KERN_WARNING "wirte_user_file+\n");
    filp = filp_open(root_log_filepath, O_RDWR|O_APPEND|O_CREAT, 0644);

    if(IS_ERR(filp))
    {
        printk(KERN_ERR "filp_open:%s fail.\n",root_log_filepath);
        return -2;
    }

    log_buf=build_log_buf(hwcwrt_work);
    if(NULL == log_buf){
         filp_close(filp,NULL);
         return -3;
    }
    old_fs = get_fs();
    set_fs(get_ds());
    ret = filp->f_op->write(filp,log_buf,strlen(log_buf),&filp->f_pos);
    set_fs(old_fs);

    filp_close(filp,NULL);
    if(NULL != log_buf){
        kfree(log_buf);
        log_buf=NULL;
    }
    printk(KERN_WARNING "wirte_user_file-\n");
    return 0;    
}

static void notice_to_apr(void)
{
    printk(KERN_WARNING "notice_to_apr+\n");
    if(checkroot_ref.ro_sec){
        printk(KERN_WARNING ">>>dcheck_root:notice_to_apr<<<\n");
    }else{
        printk(KERN_WARNING ">>>dcheck_root:no need notice_to_apr<<<\n");
    }
    printk(KERN_WARNING "notice_to_apr-\n");
    return;
    
}
static int need_drt_check(enum mian_action m_action, enum action sub_action_type)
{
    int widvine_is_locked = 0;
    int is_normal_boot = 0;
    int is_normal_swtype=0;
    //for qcom
    //static const char *normal_swtype_str = "androidboot.huawei_swtype=normal";
    //static const char *widvine_locked_str = "androidboot.widvine_state=locked";
    //for hisi
    static const char *normal_swtype_str = "androidboot.swtype=normal";
    static const char *widvine_locked_str = "userlock=locked";

    static const char *recovery_mode_str= "enter_recovery=1";  

    if((m_action==MAIN_SETUID)&&((sub_action_type > WRT_SETRESGID) || (sub_action_type < WRT_SETUID)))
    {
        return 0;
    }
    
    if((m_action==MAIN_WRT_BD)&&((sub_action_type >= WRT_UNKNOWN) || (sub_action_type < WRT_SBL1)))
    {
        return 0;
    }
    
    //if find locked string is locked
    if(strstr(saved_command_line,widvine_locked_str)!=NULL){
        widvine_is_locked = 1;
    }
    
    //if find normal is normal sw
    if(strstr(saved_command_line,normal_swtype_str)!=NULL){
        is_normal_swtype = 1;
    }    

    //if not find recovery is normal
    if(strstr(saved_command_line,recovery_mode_str)==NULL){
        is_normal_boot = 1;
    }

    
    if(is_normal_boot 
        && widvine_is_locked && is_normal_swtype 
        && (!is_recorded(sub_action_type)))
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

static void wrt_log_func(struct work_struct* work)
{
    struct cwrt_work_t* hwcwrt_work = NULL;
    printk(KERN_WARNING "wrt_log_func+\n");
    if(NULL == work){
        return;
    }
    hwcwrt_work = container_of(work, struct cwrt_work_t, cwrt_work);
    if(NULL == hwcwrt_work){
        printk(KERN_ERR "hwcwrt_work==NULL\n");
        return;
    }
    mutex_lock(&(checkroot_ref.drt_mutex));
    printk(KERN_WARNING "hwcwrt_work.action_type:%d,devname:%s\n",
                         hwcwrt_work->action_type, hwcwrt_work->dev_name);
    checkroot_ref.drt_status |= (1 << hwcwrt_work->action_type);
    wirte_user_file(hwcwrt_work);
    umh_exec_ckrt();
    notice_to_apr();
    mutex_unlock(&(checkroot_ref.drt_mutex));
    kfree(hwcwrt_work);
    hwcwrt_work = NULL;
    printk(KERN_WARNING "wrt_log_func-\n");
    return ;
}
enum action get_setuid_action(int act_flag)
{
    
    if (act_flag & CHECKROOT_SETUID_FLAG) {
       return WRT_SETUID;
	}
	if (act_flag & CHECKROOT_SETGID_FLAG) {
        return WRT_SETGID;
	}
	if (act_flag & CHECKROOT_SETRESUID_FLAG) {
       return WRT_SETRESUID;
	}
	if (act_flag & CHECKROOT_SETRESGID_FLAG) {
        return  WRT_SETRESGID;
	}
    return WRT_UNKNOWN;
}


enum action get_wrt_atction(struct bio *bio)
{
    int i=0;
	struct hd_struct *part = NULL;
    
	if (unlikely(!bio || !bio->bi_bdev ||
			!bio->bi_bdev->bd_part ||
			!bio->bi_bdev->bd_part->info ||
			!bio->bi_bdev->bd_part->info->volname[0]))
		return WRT_UNKNOWN;
    part = bio->bi_bdev->bd_part;
	if (part->info && part->info->volname[0]){
        for(i=WRT_SBL1; i < WRT_UNKNOWN;i++){
            if((strlen(act_table[i].act_name) == strlen(part->info->volname)) &&
                (0 == strncmp(act_table[i].act_name, part->info->volname, strlen(act_table[i].act_name))))
            {   
                return act_table[i].act;
            }
        }
    }
    return WRT_UNKNOWN;
}

void check_wrt(int rw, struct bio *bio)
{
    struct cwrt_work_t*  hwcwrt_work = NULL;
    enum action action_type_tmp = WRT_UNKNOWN;
    
    action_type_tmp = get_wrt_atction(bio);
    if((rw & WRITE )&&(action_type_tmp < WRT_UNKNOWN)&& need_drt_check(MAIN_WRT_BD,action_type_tmp))
    {
        hwcwrt_work = (struct cwrt_work_t*)kmalloc(sizeof(struct cwrt_work_t),GFP_ATOMIC);
        if(NULL == hwcwrt_work){
            printk(KERN_ERR ">>>>>>>>>>>>>>check_wrt:malloc:GFP_ATOMIC:FAIL<<<<<<<<<<<<<<<<<\n");
            return;
        }
        memset(hwcwrt_work,0,sizeof(struct cwrt_work_t));
        bdevname(bio->bi_bdev, hwcwrt_work->dev_name);
        hwcwrt_work->action_type = action_type_tmp;
        hwcwrt_work->pid= task_pid_nr(current);
        INIT_WORK(&(hwcwrt_work->cwrt_work),wrt_log_func);
        schedule_work(&(hwcwrt_work->cwrt_work));
    }
    return;
}



void check_setuid(int act_flag)
{
    struct cwrt_work_t*  hwcwrt_work = NULL;
    enum action action_type_tmp = WRT_UNKNOWN;

    action_type_tmp = get_setuid_action(act_flag);
    
    if(need_drt_check(MAIN_SETUID,action_type_tmp))
    {
        hwcwrt_work = (struct cwrt_work_t *)kmalloc(sizeof(struct cwrt_work_t),GFP_ATOMIC);
        if(NULL == hwcwrt_work){
            printk(KERN_ERR ">>>>>>>>>>>>>>check_setuid:malloc:GFP_ATOMIC:FAIL<<<<<<<<<<<<<<<<<\n");
            return;
        }
        memset(hwcwrt_work,0,sizeof(struct cwrt_work_t));
        strncpy(hwcwrt_work->dev_name, NA,strlen(NA));
        hwcwrt_work->action_type = action_type_tmp;        
        hwcwrt_work->pid= task_pid_nr(current);
        INIT_WORK(&(hwcwrt_work->cwrt_work),wrt_log_func);
        schedule_work(&(hwcwrt_work->cwrt_work));
    }
}

static int __init dcheckroot_init(void)
{
    checkroot_ref.ro_sec = get_ro_secure();
    mutex_init(&(checkroot_ref.drt_mutex));
	return 0;
}
late_initcall(dcheckroot_init);

