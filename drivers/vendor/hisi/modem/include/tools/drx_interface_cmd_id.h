#ifndef _HSO_DRX_INTERFACE_CMD__
#define _HSO_DRX_INTERFACE_CMD__
/*
  注意:
	使用字符串上报时:只支持CHAR_T 定义的数组,不支持char[] string 等类型
*/

typedef char                   CHAR_T;
typedef u32                    VOS_UINT32;

//睡眠状态结构
#define MAX_LOCK_LEN 32


//接口ID
#define DIAG_CMD_DRX_BSP_SLEEP_IND                        	(0x5220)					//低功耗可维可测上报IND
#define DIAG_CMD_DRX_CHIP_TEMP_IND                        	(0x5221)					//低功耗可维芯片温度上报IND
#define DIAG_CMD_DRX_BATTERIES_TEMP_IND                     (0x5222)					//低功耗可维电池温度上报IND



//

typedef struct 
{
    CHAR_T name[MAX_LOCK_LEN]; 
    VOS_UINT32	status;
} LOCK_STATUS;

typedef struct 
{
    LOCK_STATUS lock_lookup[MAX_LOCK_LEN];
} DIAG_CMD_DRX_SLEEP_STRU;

// DIAG_CMD_DRX_CHIP_TEMP_IND 低功耗可维芯片温度上报结构体
typedef struct 
{
    s16 tem;
	s16 reserved;
}DIAG_CMD_DRX_CHIP_TEMP_STRU;

// DIAG_CMD_DRX_BATTERIES_TEMP_IND 低功耗可维电池温度上报结构体
typedef struct 
{
    s16 tem;
	s16 reserved;
}DIAG_CMD_DRX_BATTERIES_TEMP_STRU;

#endif