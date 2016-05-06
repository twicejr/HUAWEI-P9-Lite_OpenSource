

#ifndef __CSDDEBUG_H__
#define __CSDDEBUG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
/* Added by l60609 for AP适配项目 ，2012-08-30 Begin */
#include "product_config.h"
/* Added by l60609 for AP适配项目 ，2012-08-30 End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : CSD_UL_STATUS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSD统计量
  1.日    期   : 2012年1月20日
    作    者   : w00199382
    修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    /*CSD上行统计信息*/
    VOS_UINT32                          ulULRecvPktNum;                         /*CSD上行收到的包数目*/
    VOS_UINT32                          ulULSaveBuffPktNum;                     /*CSD上行缓存包的数目*/
    VOS_UINT32                          ulULEnQueFail;                          /*CSD入队失败的次数*/
    VOS_UINT32                          ulULSendPktNum;                         /*CSD发送上行缓存包的数目*/
    VOS_UINT32                          ulULQueNullNum;                         /*CSD发送上行数据时从队列中获取到空指针包数目*/
    VOS_UINT32                          ulULZcToImmFailNum;                     /*CSD发送上行数据sk_buffer头转换到IMM头失败的包数目*/
    VOS_UINT32                          ulULInsertDiccFailNum;                  /*CSD发送上行数据插入DICC通道失败的包数目*/

    /*CSD下行统计信息*/
    VOS_UINT32                          ulDLRecvPktNum;                         /*CSD下行收到的包数目*/
    VOS_UINT32                          ulDLSendPktNum;                         /*CSD下行发送到驱动的包数目*/
    VOS_UINT32                          ulDLSendFailNum;                        /*CSD下行发送失败包的数目*/

}CSD_UL_STATUS_INFO_STRU;

/*****************************************************************************
  8 全局变量声明
*****************************************************************************/
extern CSD_UL_STATUS_INFO_STRU          g_stCsdStatusInfo;

/*****************************************************************************
  10 宏定义
*****************************************************************************/

/*CSD上行统计信息*/
#define CSD_DBG_UL_RECV_PKT_NUM(n)      (g_stCsdStatusInfo.ulULRecvPktNum       += (n))
#define CSD_DBG_UL_SAVE_BUFF_PKT_NUM(n) (g_stCsdStatusInfo.ulULSaveBuffPktNum   += (n))
#define CSD_DBG_UL_ENQUE_FAIL_NUM(n)    (g_stCsdStatusInfo.ulULEnQueFail        += (n))
#define CSD_DBG_UL_SEND_PKT_NUM(n)      (g_stCsdStatusInfo.ulULSendPktNum       += (n))
#define CSD_DBG_UL_QUENULL_NUM(n)       (g_stCsdStatusInfo.ulULQueNullNum       += (n))
#define CSD_DBG_UL_ZCTOIMM_FAIL_NUM(n)  (g_stCsdStatusInfo.ulULZcToImmFailNum   += (n))
#define CSD_DBG_UL_INSERT_FAIL_NUM(n)   (g_stCsdStatusInfo.ulULInsertDiccFailNum += (n))

/*CSD下行统计信息*/
#define CSD_DBG_DL_RECV_PKT_NUM(n)      (g_stCsdStatusInfo.ulDLRecvPktNum       += (n))
#define CSD_DBG_DL_SEND_PKT_NUM(n)      (g_stCsdStatusInfo.ulDLSendPktNum       += (n))
#define CSD_DBG_DL_SEND_FAIL_NUM(n)     (g_stCsdStatusInfo.ulDLSendFailNum      += (n))



#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CsdDebug.h */
