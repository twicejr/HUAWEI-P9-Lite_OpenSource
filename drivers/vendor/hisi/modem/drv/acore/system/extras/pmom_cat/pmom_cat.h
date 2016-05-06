#ifndef  __PMOM_CAT_H__
#define  __PMOM_CAT_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

#ifndef s8
typedef signed char s8;
#endif
#ifndef u8
typedef unsigned char u8;
#endif
#ifndef s16
typedef signed short s16;
#endif
#ifndef u16
typedef unsigned short u16;
#endif
#ifndef s32
typedef signed int s32;
#endif
#ifndef u32
typedef unsigned int u32;
#endif
#ifndef s64
typedef signed long long s64;
#endif
#ifndef u64
typedef unsigned long long u64;
#endif


typedef enum
{
    T_STRING =0,
    T_BINARY,
    T_MAX
}ENCODE_TYPE;

#define DEFAULT_LOG_ROTATE_SIZE_KBYTES 16
#define DEFAULT_MAX_ROTATED_LOGS 4
#define CAT_BUFSIZ (4096)
#define CCORECAT_FILE    "/dev/log/ccore"
#define DEFAULT_LOG_FILE_PATH "/data/android_logs/ccorecat-log"
#define DEFAULT_MAX_COMPRESSED_FILES 5

#define BUG_REPORT_MODE 0775
#define DIR_OWN "root:system"
#define FILE_OWN "root:system"
#define MAX_CMD 256
#define DIR_MODE 0775
#define FILE_MODE 0664
#define MKDIR_ERR -1
#define MKDIR_OK  0
#define MAX_INPUT_PARA_LENGTH           (256)

#define PMOM_OK               (int)(0)
#define PMOM_ERR              (int)(-1)
#define PMOM_PARSE_STR_BUFSIZ (CAT_BUFSIZ)

struct pmom_cat_control
{
	char raw_buf[CAT_BUFSIZ];
	char str_buf[PMOM_PARSE_STR_BUFSIZ];
	unsigned int str_wr;
    char timebuf[32];
};




/*
 * 模块魔数，以ascii码值表示的u32整型数据，注意:
 * 1) 是小端字节序
 * 2) 修改或者增加enum PM_OM_MOD_ID定义的时候，需要同步修改枚举
 */
enum PM_OM_MAGIC
{
	/* 各模块对应魔数 */
	PM_OM_MAGIC_PMA  = 0x20414D50, /* 0-PMA  : PM ACORE  */
	PM_OM_MAGIC_PMC  = 0x20434D50, /* 1-PMC  : PM CCORE  */
	PM_OM_MAGIC_PMM  = 0x204D4D50, /* 2-PMM  : PM MCORE  */
	PM_OM_MAGIC_DPM  = 0x204D5044, /* 3-DPM  : DPM */
	PM_OM_MAGIC_ABB  = 0x20424241, /* 4-ABB  : ABB */
	PM_OM_MAGIC_BBP  = 0x20504242, /* 5-BBP  : BBP */
	PM_OM_MAGIC_DSP  = 0x20505344, /* 6-DSP  : DSP */
	PM_OM_MAGIC_PMU  = 0x20554D50, /* 7-PMU  : PMU */
	PM_OM_MAGIC_WAKE = 0x454B4157, /* 8-WAKE : WAKELOCK */
	PM_OM_MAGIC_CPUF = 0x46555043, /* 9-CPUF : CPUFREQ */
	PM_OM_MAGIC_CCLK = 0x4B4C4343, /*10-CCLK : CLK CCORE */
	PM_OM_MAGIC_REGU = 0x55474552, /*11-REG  : REGULATOR */
	PM_OM_MAGIC_ACLK = 0x4B4C4341, /*12-ACLK : CLK ACORE */
	PM_OM_MAGIC_AIPC = 0x43504941, /*13-AIPC : IPC ACORE */
	PM_OM_MAGIC_CIPC = 0x43504943, /*14-CIPC : IPC CCORE */
	PM_OM_MAGIC_AIPF = 0x46504941, /*15-AIPF : IPF ACORE */
	PM_OM_MAGIC_CIPF = 0x46504943, /*16-CIPF : IPF CCORE */
	PM_OM_MAGIC_AOSA = 0x41534F41, /*17-AOSA : OSA ACORE */
	PM_OM_MAGIC_COSA = 0x41534F43, /*18-COSA : OSA CCORE */
	PM_OM_MAGIC_CMSP = 0x50534D43, /*19-CMSP : MSP CCORE */
	PM_OM_MAGIC_NVA  = 0x2041564E, /*20-NVA : NV */
	PM_OM_MAGIC_NVC  = 0x2043564E, /*21-NVC : NV */
	PM_OM_MAGIC_ADPPOWER  = 0x50504441,/*22-ADPP: ADPPOWER*/
	PM_OM_MAGIC_AICC = 0x43434941, /*23-AICC: ICC ACORE */
	PM_OM_MAGIC_CICC = 0x43434943, /*24-CICC: ICC CCORE  */
	PM_OM_MAGIC_ARFILE=0x45494652, /*25-FILE: RFILE ACORE*/
	PM_OM_MAGIC_PMLG = 0x474C4D50, /*26-PMLG: LOG FILE  */
	PM_OM_MAGIC_TCXO = 0x4F584354, /*27-TCXO: CCORE  */
	/* pm om内部使用魔数 */
	PM_OM_MAGIC_PMDP = 0x50444D50, /* PMDP: DUMP FILE */
	PM_OM_MAGIC_PLOF = 0x464F4C50, /* PLOF: PM LOG OVERFLOW  */
};

struct pm_om_log_header
{
	u32 magic;
	u32 sn;
	u32 typeid;
	u32 timestamp;
	u32 length;
};


#ifdef __cplusplus
}
#endif

#endif   /* __PMOM_CAT_H__ */

