/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgSendSms.h
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月21日
  最近修改   :
  功能描述   : MSG发送给SMS模块的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月21日
    作    者   : 周君 40661
    修改内容   : 创建文件

******************************************************************************/
#ifndef __MNMSGSENDSMS_H__
#define __MNMSGSENDSMS_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgApi.h"
#include  "MnMsgSmCommProc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 接口函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsRpDataReq
 功能描述  : 发送Rp-Data数据到NAS层的SMS模块
 输入参数  : enSendDomain:Rp-Data的发送域
             pSendMsg:发送数据的内容,具体为协议24011中RP-Data的内容
             ucSendLen:pucSendMsg的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月10日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈     
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpDataReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    const VOS_UINT8                     *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);

/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsCpAckReq
 功能描述  : 发送CP-ACK数据到NAS层的SMS模块
 输入参数  : enSendDomain:Rp-Data的发送域
             pucSendMsg:发送数据的内容,具体为协议24011中RP-Data的内容
             ucSendLen:pucSendMsg的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID MN_MSG_SendSmsCpAckReq(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsRpReportReq
 功能描述  : 发送Rp-Report数据到NAS层的SMS模块
 输入参数  : pSendMsg:发送数据的内容,具体为协议24011中RP-ACK或RP-ERROR的内容
             ucSendLen:发送数据的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月3日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈    
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpReportReq(
    const VOS_UINT8                     *pucSendMsg,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType    
);

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SendSmsSmmaReq
 功能描述  : 发送SMMA消息到NAS层的SMS模块
 输入参数  : enSendDomain:Rp-Data的发送域
             pSendMsg:发送数据的内容,具体为协议24011中RP-Data的内容
             ucSendLen:pucSendMsg的长度
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月3日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈     
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsSmmaReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */


/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRpData
 功能描述  : 根据24011中Rp-Data的结构构造一条Rp-Data的字节流
 输入参数  : stRpData:24011中Rp-Data的结构
 输出参数  : pucRpduContent:Rp-Data的字节流的内容
             pucRpduLen:Rp-Data的字节流的长度
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpData(
    const MN_MSG_RP_DATA_STRU           *pstRpData,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRpAck
 功能描述  : 根据24011中Rp-ACK的结构构造一条Rp-ACK的字节流
 输入参数  : pstRpAck:24011中Rp-ACK的结构
 输出参数  : pucRpduContent:Rp-ACK的字节流的内容
             pucRpduLen:Rp-ACK的字节流的长度
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpAck(
    const MN_MSG_RP_ACK_STRU            *pstRpAck,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);

/*****************************************************************************
 函 数 名  : MN_MSG_EncodeRpErr
 功能描述  : 根据24011中Rp-Error的结构构造一条Rp-Error的字节流
 输入参数  : pstRpErr:24011中Rp-Error的结构
 输出参数  : pucRpduContent:Rp-Error的字节流的内容
             pucRpduLen:Rp-Error的字节流的长度
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpErr(
    const MN_MSG_RP_ERR_STRU            *pstRpErr,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __MNMSGSENDSMS_H__ */

