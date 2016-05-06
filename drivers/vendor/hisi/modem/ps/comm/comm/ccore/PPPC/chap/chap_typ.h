/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : chap_typ.h
  版 本 号   : 初稿
  作    者   : luofang
  生成日期   : 2012年11月8日
  最近修改   :
  功能描述   : PPP模块定义Chap协议结构体
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年11月8日
    作    者   : luofang
    修改内容   : 创建文件

******************************************************************************/



#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_CHAP == VRP_YES )

#ifndef      _CHAP_TYPE_H_
#define      _CHAP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* CHAP 控制块数据结构定义 */
typedef struct tagPppChapInfo 
{
    PPPINFO_S *pstPppInfo ;         /*PPP控制块指针*/    
    VOID *pstAAAAuthReqMsg;    
    HTIMER ulRespTimeoutID;            /* 传送Response超时定时器*/    
    HTIMER ulChalTimeoutID;            /* 传送Challenge超时定时器*/

    VOS_UINT32 ulWaitAuthRspTimeout;             /* 等待AAA鉴权响应超时时间 */
    VOS_UINT32 ulAuthMaxTransmits;				/* 验证请求最大传送次数 */    
    VOS_UINT32 ulRespTransmits;	        /* 已传送Response次数 */
    VOS_UINT32 ulChalTransmits;	        /* 已传送Challenge 次数 */
    VOS_UINT32 ulChalInterval;		        /* 再次验证对端的时间间隔 */
    VOS_UINT32 ulTimeOutTime;		        /* 超时时间 */
    VOS_UINT32 ulMaxTransmits;		        /* 最大传送次数 */
    VOS_UINT32 ulWaitLnsAuthTimeOut;

    VOS_UINT16 usAuthClientFailureTimes;/* Client端验证失败计数器*/
    VOS_UINT16 usAuthServerFailureTimes;/* Server端验证失败定时器*/    
    UCHAR ucClientState;		    /* Client 状态*/
    UCHAR ucRespLen;		        /* Response 长度 */
    UCHAR ucRespId;			        /* Response ID*/
    UCHAR ucRespType;		        /* 产生Response 的哈希算法类型*/

    
    UCHAR ucServerState;		    /* Server 状态 */
    UCHAR ucChalLen;			    /* Challenge 长度*/
    UCHAR ucChalId;			        /* Challenge ID*/
    UCHAR ucChalType;		        /* 产生Challenge的哈希算法类型 */
    UCHAR ucUsed;                   /*CHAP控制块使用标记*/
    UCHAR ucAuthTransmits;					/* 传送验证请求的次数 */    
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2];
                                        /* 主机名*/

    UCHAR szChallenge[CHAP_MAX_CHALLENGE_LENGTH]; 
    UCHAR szHostPwd[PPP_MAXUSERPWDLEN + 2];
                                    /*口令*/
    UCHAR szResponse[CHAP_MAX_RESPONSE_LENGTH + 2];  
                                    /* 送出的Response 字符串*/
    UCHAR ucPppChapInfoRev[4];     /*保留字段*/


} PPPCHAPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _CHAP_TYPE_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_CHAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

