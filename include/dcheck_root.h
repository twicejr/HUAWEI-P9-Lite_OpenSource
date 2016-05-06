#ifndef _DCHECK_ROOT_H_
#define _DCHECK_ROOT_H_

/* comment this for force stop DCHECK_ROOT */
#define DCHECK_ROOT_FORCE


#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/genhd.h>
#include <linux/mutex.h>
#include <linux/dcache.h>


#define TASK_LIST_LEN 5
#define LOG_LINE_LEN  256

#define TOO_LONG_CONST_STR        "TOO_LONG"    
#define DEFAULT_PROP_FILE         "/default.prop"    
//define action name
#define ACT_SETUID_NM        "setuid"    
#define ACT_SETGID_NM        "setgid"    
#define ACT_SETRESUID_NM     "setresuid"    
#define ACT_SETRESGID_NM     "setresgid"    
#define ACT_SBL1_NM          "sbl1"        //used by QCOM  
#define ACT_ABOOT_NM         "aboot"       //used by QCOM
#define ACT_FTBT2_NM         "fastboot"    //used by HISI
#define ACT_BOOT_NM          "boot"
#define ACT_RECOVERY_NM      "recovery"  
#define ACT_SYSTEM_NM        "system"
#define ACT_MODEM_NM         "modem"       //used by QCOM
#define ACT_MODEM_FW_NM      "modem_fw"    //used by HISI
#define ACT_CUST_NM          "cust"

//define mian action type
enum mian_action
{
    MAIN_SETUID,
    MAIN_WRT_BD
};


//define sub action type
enum action
{
   WRT_SETUID,
   WRT_SETGID,
   WRT_SETRESUID,
   WRT_SETRESGID,
   WRT_SBL1,    
   WRT_ABOOT,   
   WRT_FTBT2,
   WRT_BOOT,
   WRT_RECOVERY,  
   WRT_SYSTEM,
   WRT_MODEM,
   WRT_MODEM_FW,   
   WRT_CUST,
   WRT_UNKNOWN
};




struct action_table{
    char act_name[PARTITION_META_INFO_VOLNAMELTH];
    enum action act;
};

struct cwrt_work_t {
    char dev_name[BDEVNAME_SIZE];
	pid_t pid;
	enum action action_type;//current action
	struct work_struct cwrt_work;
};

void check_wrt(int rw, struct bio *bio);
void check_setuid(int act_flag);
#endif


