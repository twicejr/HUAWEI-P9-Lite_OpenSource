#ifndef __RECOVERY_MISC_H_
#define __RECOVERY_MISC_H_

#define MISC_LOG_INFO(fmt,args...) do { hwlog_info(fmt, ## args); } while (0)
#define MISC_LOG_ERR(fmt,args...) do { hwlog_err(fmt, ## args); } while (0)
#define MISC_LOG_DEBUG(fmt,args...) do { hwlog_debug(fmt, ## args);} while(0)

typedef struct {
	char command[32];
	char status[32];
	char recovery[1024];
} misc_message_type;

#define MISC_BOOT_RECOVERY_STR  "boot-recovery"
#define MISC_NODE_PATH "/dev/block/platform/hi_mci.0/by-name/misc"


#endif
