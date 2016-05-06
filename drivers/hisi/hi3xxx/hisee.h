#ifndef	__HISEE_H
#define	__HISEE_H

#ifndef ERROR
#define ERROR   -1
#endif

#ifndef OK
#define OK   0
#endif

#define CONFIG_HISEE_TEST

#define ALIGN_UP_4KB(x)     ((x + 0xFFF)&(~0xFFF))

#define HISEE_FN_DOWNLOAD               0xc5000020
#define HISEE_TEST_FN_DOWNLOAD          0xc5000040

#define HISEE_LOG_BUFFER_SIZE           0x8000

#define HISEE_LPM3_CMD IPC_CMD(OBJ_LPM3, OBJ_AP, CMD_SETTING, 0)

#define BYPASS_SPACE_CHAR(hisee_cmd,offset,count) \
    while (1) { \
        if (0x20 != hisee_cmd[offset]) {    \
            break;  \
        }   \
        if (offset >= CMD_MAX_SIZE) {   \
            pr_err("hisee_cmd is bad.\n");  \
		    count = -EINVAL;    \
		    return count;   \
        }   \
        offset++;   \
    }

#define COS_PARTITION_ID        0x1
#define APP_TABLE_ID            0x2

typedef enum {
    SMC_DOWNLOAD_SLODER = 0,
    SMC_DOWNLOAD_OTP,
    SMC_DOWNLOAD_COS,
    SMC_DOWNLOAD_PATCH,
    SMC_DOWNLOAD_END = 0x10,
    SMC_SET_DOWNLOAD,
    SMC_RESET_HISEE,
    SMC_EXIT_LOOP_BYPASS_SEC,
    SMC_EXIT_LOOP_NO_TRANSFER_ENC,
    SMC_EXIT_LOOP_TRANSFER_ENC,
    SMC_READ_COS_PARTITION,
    SMC_TRANSFER_LOG_INFO,
#if defined (CONFIG_HISEE_TEST)
    SMC_DOWNLOAD_TEST0 = 0x20,
    SMC_DOWNLOAD_TEST1,
    SMC_DOWNLOAD_TEST2,
#endif
    SMC_READ_REG,
    SMC_WRITE_REG,
    SMC_SET_EMMC_BUG_FLAG,
    SMC_WRITE_KEY,
    SMC_RUN_FUNCTION,
    SMC_END,
}se_smc_cmd;

typedef enum {
    SE_CMD_ACK_NULL = 0x55,
    SE_CMD_ACK_OK = 0xA3,
    SE_CMD_ACK_ERROR = 0xF7,
} se_cmd_ack;

typedef struct {
    struct device dev;
    unsigned int *buffer;
    unsigned long phy;
    unsigned int size;
}hisee_work_struct;

typedef struct {
    unsigned int ack;
    unsigned int magic;
    unsigned int size;
    unsigned int offset;
}hisee_log_header;

#if defined (CONFIG_HISEE_TEST)
/* test for hisee */
#define CMD_MAX_SIZE            128
#define TEST_SUCCESS_FILE       "/data/hisee_test/test_success.txt"
#define TEST_FAIL_FILE          "/data/hisee_test/test_fail.txt"
#define TEST_RESULT_FILE        "/data/hisee_test/test_result.img"

#define TEST_RUNNING                0xFFFFFFFF
#define TEST_SUCCESS                0xAA5555AA
#define TEST_FAIL                   0x55AAAA55

#define TEST_RESULT_SIZE_DEFAULT    0x40000
typedef enum {
    TEST_PRINT = 0,
    TEST_SECENG,
    TEST_BUTTOM
} e_test_type;

typedef enum {
    SE_ACK_AP_FAULT_INIT = 0,
    SE_ACK_AP_FAULT_MAILBOX_INSE,
    SE_ACK_AP_FAULT_OS_MAIL_PUT,
    SE_ACK_AP_POWERUP_INSE_SUCCESS,
    SE_ACK_AP_POWERUP_INSE_FAIL,
    SE_ACK_AP_BOTTOM
} se_ack_ap;

typedef struct {
    unsigned int status;
    unsigned int phy;
    unsigned int size;
}hisee_test_header;

#endif

static int hisee_open(struct inode *inode, struct file *file);
static ssize_t hisee_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos);
#if defined (CONFIG_HISEE_TEST)
static int __init  hisee_create_test_file(void);
static ssize_t hisee_test_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos);
#endif

#endif
