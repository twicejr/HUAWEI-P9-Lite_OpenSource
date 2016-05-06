/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hi6xxx_tele_mntn.h
  版 本 号   : 初稿
  作    者   : hi6xxx_tele_mntn.h
  生成日期   : 2014年11月22日
  最近修改   :
  功能描述   : bsp_tele_mntn.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月22日
    作    者   : hi6xxx_tele_mntn.h
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __HI6XXX_TELE_MNTN_H__
#define __HI6XXX_TELE_MNTN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*

说明:

extern int DRV_TELE_MNTN_WRITE_LOG(
            TELE_MNTN_TYPE_ID type_id,
            unsigned int len,
            void *data);

def type_id 与  最大len长度 data解析类型 的对应关系:

    TELE_MNTN_DEF_STR 对应的data解析类型 和 最大len长度:
            U8 tmp[64]
            len = 64 Bytes

    TELE_MNTN_DEF_U8 对应的data解析类型 和 最大len长度:
            struct
            {
                U8 tmp0;
                U8 tmp1;
                U8 tmp2;
                U8 tmp3;
                U8 tmp4;
                U8 tmp5;
                U8 tmp6;
                U8 tmp7;
            }
            len = 8 Bytes

    TELE_MNTN_DEF_U16 对应的data解析类型 和 最大len长度:
            struct
            {
                U16 tmp0;
                U16 tmp1;
                U16 tmp2;
                U16 tmp3;
                U16 tmp4;
                U16 tmp5;
                U16 tmp6;
                U16 tmp7;
            }
            len = 16 Bytes

    TELE_MNTN_DEF_U32 对应的data解析类型 和 最大len长度:
            struct
            {
                U32 tmp0;
                U32 tmp1;
                U32 tmp2;
                U32 tmp3;
                U32 tmp4;
                U32 tmp5;
                U32 tmp6;
                U32 tmp7;
            }
            len = 32 Bytes

    TELE_MNTN_DEF_U64 对应的data解析类型 和 最大len长度:
            struct
            {
                U64 tmp0;
                U64 tmp1;
                U64 tmp2;
                U64 tmp3;
            }
            len = 32 Bytes

*/
typedef enum
{
    TELE_MNTN_TYPE_RESERVED = -1,
    /*其他用途，保留*/
    TELE_MNTN_NVME_WAKEUP_ACPU = 0,
    TELE_MNTN_NVME_LOGCAT,

    /*默认type_id 对应固定的数据解析类型和默认的数据最大长度，
    工具已默认的数据解析类型解析，多模块可重复使用*/
    TELE_MNTN_DEF_STR = 5,    /*见说明*/
    TELE_MNTN_DEF_U8,         /*见说明*/
    TELE_MNTN_DEF_U16,        /*见说明*/
    TELE_MNTN_DEF_U32,        /*见说明*/
    TELE_MNTN_DEF_U64,        /*见说明*/

    /*各模块自定义type_id 对应的数据解析类型和数据长度由各模块自己定义的结构体决定，
    如果没有结构体定义，工具以码流方式解析*/
    TELE_MNTN_SLEEPWAKE_CCPU = 15,
    TELE_MNTN_NOTSLEEPREASON_CCPU,
    TELE_MNTN_SLEEPWAKE_MCU,
    TELE_MNTN_NOTSLEEPREASON_MCU,
    TELE_MNTN_PUPD_CCPU,
    TELE_MNTN_WFIFAIL_CCPU,  /*20*/
    TELE_MNTN_PUPD_ACPU,
    TELE_MNTN_WFIFAIL_ACPU,
    TELE_MNTN_PUPD_HIFI,
    TELE_MNTN_WFIFAIL_HIFI,
    TELE_MNTN_CPUIDLE,  /*25*/
    TELE_MNTN_VOTE_CCPU,
    TELE_MNTN_VOTE_MCU,
    TELE_MNTN_ICC_WAKE_ACPU,
    TELE_MNTN_ICC_WAKE_CCPU,
    TELE_MNTN_IPC_MCU,  /*30*/
    TELE_MNTN_DFS_DDR,
    TELE_MNTN_PLI_DDR,
    TELE_MNTN_MAXFREQ_REQ_DDR,
    TELE_MNTN_MINFREQ_REQ_DDR,
    TELE_MNTN_QOS_DDR_MCU,  /*35*/
    TELE_MNTN_QOS_DDR_CCPU,
    TELE_MNTN_QOS_DDR_ACPU,
    TELE_MNTN_DFS_CCPU,
    TELE_MNTN_PLI_CCPU,
    TELE_MNTN_QOS_CCPU,  /*40*/
    TELE_MNTN_DFS_ACPU,
    TELE_MNTN_DRX,
    TELE_MNTN_PLI_ACPU,
    TELE_MNTN_SR_ACPU,
	TELE_MNTN_DFS_GPU,

    TELE_MNTN_OSA = 50,

    TELE_MNTN_REG_DUMP = 63,
    TELE_MNTN_TYPE_BUTT
}TELE_MNTN_TYPE_ID;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


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
extern int tele_mntn_write_log(TELE_MNTN_TYPE_ID type_id, unsigned int len, void *data);











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hi6xxx_tele_mntn.h */
