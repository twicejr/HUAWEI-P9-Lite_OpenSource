/******************************************************************************

			  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名   : drv_mailbox_debug.h
版 本 号   : 初稿
作	  者   : 莫南 00176101
生成日期   : 2012年9月24日
最近修改   :
功能描述   : mailbox 各平台平台系统调试模块公共头文件
函数列表   :

修改历史   :
1.日	期	 : 2012年12月31日
作	  者   : 莫南 00176101
修改内容   : 创建文件

******************************************************************************/
#ifndef _DRV_MAILBOX_DEBUG_H_
#define _DRV_MAILBOX_DEBUG_H_

/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "drv_mailbox_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*邮箱数据传输和处理时间限制*/
#define MAILBOX_MAIL_TRANS_TIME_LIMIT				(3000)		 /* 跨核邮箱消息最长滞留时间(value/32 ms) */
#define MAILBOX_MAIL_DEAL_TIME_LIMIT				(2000)		 /* 跨核邮箱消息最长回调处理时间(value/32 ms) */
#define MAILBOX_MAIL_SCHE_TIME_LIMIT				(2000)		 /* 跨核邮箱消息最长任务调度等待时间(value/32 ms) */

/*记录最近的几次错打印个数*/
#define MAILBOX_ERRO_ARRAY_NUM						(5)

#define MAILBOX_LOG_NONE				(-1)
#define MAILBOX_LOG_CRITICAL			(0)
#define MAILBOX_LOG_ERROR				(1)
#define MAILBOX_LOG_WARNING 			(2)
#define MAILBOX_LOG_INFO				(3)

#define MAILBOX_SHOW_ALL				(0x001) /*显示所有通道详细信息*/
#define MAILBOX_SHOW_CLEAR				(0x010) /*显示通道信息后清除信息*/

/*邮箱通道剩余空间的最大值*/
#define MAILBOX_QUEUE_LEFT_INVALID					(0xffffffff)

/*邮箱时间戳的最大slice*/
#define MAILBOX_MAX_SLICE							(0xffffffff)
#define mailbox_get_slice_diff(s,e) 				(((e) >= (s))?((e) - (s)) : ((MAILBOX_MAX_SLICE - (s)) + (e)))

/*邮箱调试打印接口*/
#if (MAILBOX_LOG_LEVEL == MAILBOX_LOG_NONE)
#define mailbox_logerro_p0(ErrorId)                 (unsigned int)(ErrorId)

#define mailbox_logerro_p1(ErrorId, Param)          (unsigned int)(ErrorId)

#define mailbox_logerro_p2(ErrorId, Param1,Param2)  (unsigned int)(ErrorId)

#else
#define mailbox_logerro_p0(ErrorId)                 mailbox_log_erro((unsigned int)ErrorId, (unsigned int)0,(unsigned int)0,\
                                                    (unsigned int)_MAILBOX_LINE_, (char*)_MAILBOX_FILE_)

#define mailbox_logerro_p1(ErrorId, Param)          mailbox_log_erro((unsigned int)ErrorId, (unsigned long)Param,(unsigned long)0, \
                                                    (unsigned int)_MAILBOX_LINE_, (char*)_MAILBOX_FILE_)

#define mailbox_logerro_p2(ErrorId, Param1,Param2)  mailbox_log_erro((unsigned int)ErrorId, (unsigned long)Param1,Param2, \
                                                    (unsigned int)_MAILBOX_LINE_, (char*)_MAILBOX_FILE_)
#endif

/*致命错误开始*/ /*需要复位系统的错误:邮箱内部错误*/
#define    MAILBOX_CRIT_RET_START								0x80000001
#define    MAILBOX_CRIT_GUT_INVALID_USER_MAIL_HANDLE			0x80000002
#define    MAILBOX_CRIT_GUT_INIT_CHANNEL_POOL_TOO_SMALL 		0x80000003
#define    MAILBOX_CRIT_GUT_INIT_USER_POOL_TOO_SMALL			0x80000004
#define    MAILBOX_CRIT_GUT_MUTEX_LOCK_FAILED					0x80000005
#define    MAILBOX_CRIT_GUT_MUTEX_UNLOCK_FAILED 				0x80000006
#define    MAILBOX_CRIT_GUT_MSG_CHECK_FAIL						0x80000007
#define    MAILBOX_CRIT_GUT_RECEIVE_MAIL						0x80000008
#define    MAILBOX_CRIT_GUT_READ_MAIL							0x80000009
#define    MAILBOX_CRIT_GUT_MEMORY_CONFIG						0x8000000a
#define    MAILBOX_CRIT_PORT_CONFIG 							0x80000010 /*某个核的通道配置错误*/
#define    MAILBOX_CRIT_RET_END 								0x800000ff /*致命错误结束*/


/*****************************************************************************
  邮箱错误号定义
*****************************************************************************/
/*可宽恕错误开始*/ /*不需要复位系统的错误:邮箱外部接口调用错误*/
#define    MAILBOX_ERR_RET_START								0x80000100
#define    MAILBOX_ERR_GUT_INVALID_CPU_LINK 					0x80000101
#define    MAILBOX_ERR_GUT_INVALID_SRC_CPU						0x80000102
#define    MAILBOX_ERR_GUT_INVALID_TARGET_CPU					0x80000103
#define    MAILBOX_ERR_GUT_INVALID_CHANNEL_ID					0x80000104
#define    MAILBOX_ERR_GUT_INVALID_CARRIER_ID					0x80000105
#define    MAILBOX_ERR_GUT_REQUEST_CHANNEL						0x80000106
#define    MAILBOX_ERR_GUT_RELEASE_CHANNEL						0x80000107
#define    MAILBOX_ERR_GUT_TIMESTAMP_CHECK_FAIL 				0x80000108
#define    MAILBOX_ERR_GUT_WRITE_EXCEED_MAX_SIZE				0x80000109
#define    MAILBOX_ERR_GUT_ALREADY_INIT 						0x8000010a
#define    MAILBOX_ERR_GUT_SEND_MAIL_IN_INT_CONTEXT 			0x8000010b
#define    MAILBOX_ERR_GUT_USER_BUFFER_SIZE_TOO_SMALL			0x8000010c
#define    MAILBOX_ERR_GUT_INPUT_PARAMETER						0x8000010d
#define    MAILBOX_ERR_GUT_NOT_INIT 							0x8000010e
#define    MAILBOX_ERR_GUT_MAILBOX_SEQNUM_CHECK_FAIL			0x8000010f
#define    MAILBOX_ERR_GUT_MAILBOX_RECEIVE_FULL 				0x80000110
#define    MAILBOX_ERR_GUT_INIT_PLATFORM						0x80000112
#define    MAILBOX_ERR_GUT_MAILBOX_NULL_PARAM					0x80000113
#define    MAILBOX_ERR_GUT_CREATE_BOX							0x80000114
#define    MAILBOX_ERR_GUT_MUTEX_CREATE_FAILED					0x80000115
#define    MAILBOX_ERR_GUT_READ_CALLBACK_NOT_FIND				0x80000116
#define    MAILBOX_ERR_GUT_INVALID_USER_ID						0x80000117
#define    MAILBOX_ERR_GUT_INIT_CHANNEL_POOL_TOO_LARGE			0x80000118
#define    MAILBOX_ERR_GUT_INIT_USER_POOL_TOO_LARGE 			0x80000119
#define    MAILBOX_ERR_GUT_CALCULATE_SPACE						0x8000011a
#define    MAILBOX_ERR_GUT_INIT_CORESHARE_MEM					0x8000011b

#define    MAILBOX_ERR_VXWORKS_TASK_CREATE						0x80000140
#define    MAILBOX_ERR_VXWORKS_CALLBACK_NOT_FIND				0x80000141
#define    MAILBOX_ERR_VXWORKS_CALLBACK_ERRO					0x80000142
#define    MAILBOX_ERR_VXWORKS_MAIL_TASK_NOT_FIND				0x80000143
#define    MAILBOX_ERR_VXWORKS_MAIL_INT_NOT_FIND				0x80000144
#define    MAILBOX_ERR_VXWORKS_CHANNEL_NOT_FIND 				0x80000145
#define    MAILBOX_ERR_VXWORKS_ALLOC_MEMORY 					0x80000146

#define    MAILBOX_ERR_MCU_CHANNEL_NOT_FIND 					0x80000160
#define    MAILBOX_ERR_MCU_ZOS_MSG_ALLOC_FAIL					0x80000161
#define    MAILBOX_ERR_MCU_ZOS_MSG_SEND_FAIL					0x80000162
#define    MAILBOX_ERR_MCU_ZOS_PID_NOT_FIND 					0x80000163
#define    MAILBOX_ERR_MCU_ZOS_CBFUNC_NULL						0x80000164

#define    MAILBOX_ERR_LINUX_TASK_CREATE						0x80000180
#define    MAILBOX_ERR_LINUX_CALLBACK_NOT_FIND					0x80000181
#define    MAILBOX_ERR_LINUX_CALLBACK_ERRO						0x80000182
#define    MAILBOX_ERR_LINUX_MAIL_TASK_NOT_FIND 				0x80000183
#define    MAILBOX_ERR_LINUX_MAIL_INT_NOT_FIND					0x80000184
#define    MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND					0x80000185
#define    MAILBOX_ERR_LINUX_ALLOC_MEMORY						0x80000186

#define    MAILBOX_ERR_RET_END									0x800001ff /*可宽恕错误结束*/

/*告警信息开始*/
#define    MAILBOX_WARNING_RET_START							0x80000200
#define    MAILBOX_WARNING_USER_CALLBACK_ALREADY_EXIST			0x80000201
#define    MAILBOX_WARNING_TRANSPORT_TIME_OUT					0x80000202
#define    MAILBOX_WARNING_RECEIVE_TIME_OUT 					0x80000203
#define    MAILBOX_WARNING_SCHE_TIME_OUT						0x80000204
#define    MAILBOX_WARNING_RET_END								0x800002ff /*告警信息结束*/

/*通知信息开始*/
#define    MAILBOX_INFO_RET_START								0x80000300
#define    MAILBOX_INFO_RECEIVE_FIRST_MAIL						0x80000301
#define    MAILBOX_INFO_SEND_FIRST_MAIL 						0x80000302
#define    MAILBOX_INFO_RET_END 								0x800003ff /*通知信息结束*/

/*板侧测试的消息头保护字*/
#define MAILBOX_BOARDST_USER_PROTECT1				(0x18273645)

#define MAILBOX_MCU_TEST_BUFF_SIZE					256

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
 实 体 名  : tm_mb_cb
 功能描述  : 板侧测试的测试数据消息头结构
*****************************************************************************/
struct  mb_st_msg
{
    unsigned int protect;                       /*消息保护字 MAILBOX_BOARDST_USER_PROTECT1*/
    unsigned int length;                        /*测试的消息长度*/
    unsigned int back_code;              /*用于返回消息内容的通道号*/
    unsigned int test_id;                        /*测试过程消息号: TM_MAILBOX_TEST_ID_E定义*/
};

/*****************************************************************************
  5 消息定义
*****************************************************************************/

/*****************************************************************************
 实 体 名  : MAILBOX_BOARDST_TEST_ID_E
 功能描述  : 板侧测试的测试功能消息ID
*****************************************************************************/
enum MAILBOX_BOARDST_TEST_ID_E 
{
    MAILBOX_BOARDST_ID_LOOP_SEND,                /*回环测试的发送*/
    MAILBOX_BOARDST_ID_LOOP_BACK,                /*回环测试的接收数据后返回*/
    MAILBOX_BOARDST_ID_LOOP_FINISH               /*回环测试结束*/
};

/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 实 体 名  : struct mb_log
 功能描述  : 错误码记录结构体
*****************************************************************************/
struct mb_log
{
    unsigned int erro_num;
    unsigned long param1;
    unsigned long param2;
    unsigned int line;
    const char*   file;
};

/****************************************************************************
  邮箱通道传送use id 轨迹数据结构
****************************************************************************/
typedef struct
{
    unsigned int               send_slice;         /*发送的时间戳*/
    unsigned int               recv_slice;         /*接收的时间戳*/
    unsigned long               mail_addr;         /*邮件数据地址*/
    unsigned short              use_id;
    unsigned short              reserved;
}MAILBOX_TRACK_STRU;

/*****************************************************************************
  此邮箱通道的可维可测信息
*****************************************************************************/
struct mb_slice
{
    unsigned int               total;       /*邮件累计传递时间,计算从一个点发送到另外一个响应点的时间*/
    unsigned int               start;       /*保存单次统计的发送点时间*/
    unsigned int               max;         /*邮件最大传递时间，计算从一个点发送到另外一个响应点的时间**/
    unsigned int               code;       /*邮件最大传递使用号*/
    unsigned int               overflow;    /*处理总时间计数是否溢出*/
};

struct mb_mntn
{
    unsigned int               peak_traffic_left;       /*通道剩余空间的最低值，用于统计邮箱数据峰值*/

    struct mb_slice             trans;                   /*统计邮件传递时间，从发送核发送，到接接收核调用回调之前*/   
    struct mb_slice             deal;                    /*统计邮件处理时间，统计用户的邮件处理时长*/   
    struct mb_slice             sche;                    /*统计邮件任务调度等待时间，统计从中断到任务调度的时间*/   
  
    /*以下是邮件发送(接收)轨迹记录*/
    unsigned int               track_prob;             /*指向TrackArray中下一次记录*/
    MAILBOX_TRACK_STRU          track_array[MAILBOX_RECORD_USEID_NUM];/*记录最近处理的MAILBOX_LATEST_USEID_NUM个use id 传送信息*/
    struct mb_buff             *mbuff;                  
};

/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  9 全局变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern MAILBOX_EXTERN int mailbox_log_erro(
                unsigned int   err_no,
                unsigned long   param1,
                unsigned long   param2,
                unsigned int   line_no,
                char*           file_name);

MAILBOX_EXTERN void mailbox_record_send(
                struct mb_mntn* mntn,                
                unsigned int mailcode, 
                unsigned int time_stamp,
                unsigned long mail_addr);


MAILBOX_EXTERN void mailbox_record_transport(
                struct mb_mntn* mntn, 
                unsigned int mailcode, 
                unsigned int write_slice,
                unsigned int read_slice,
                unsigned long mail_addr);


MAILBOX_EXTERN void mailbox_record_receive(
                struct mb_mntn* mntn,                
                unsigned int mailcode, 
                unsigned int slice_start);

MAILBOX_EXTERN int mailbox_show(
                unsigned int    channel,
                unsigned int    show_all);

MAILBOX_EXTERN void mailbox_record_sche_send(void *priv);

MAILBOX_EXTERN void mailbox_record_sche_recv(void *priv);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif	/*_DRV_MAILBOX_DEBUG_H_*/

