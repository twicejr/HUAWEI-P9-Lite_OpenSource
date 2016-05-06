/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ipcp_typ.h
  版 本 号   : 初稿
  作    者   : luofang
  生成日期   : 2012年11月8日
  最近修改   :
  功能描述   : PPP模块IPCP协议定义结构体
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年11月8日
    作    者   : luofang
    修改内容   : 创建文件

******************************************************************************/


#ifndef      _IPCP_TYPE_H_
#define      _IPCP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */


typedef struct tagPppIpcpInfo
{
	PPPINFO_S *pstPppInfo ;           /* PPP控制块指针 */
    UCHAR * pucIpv4cpMsg;             /* IPCP控制块中保存协商缓存消息 */    
	PPPFSM_S  stFsm;                  /* IPCP协议状态机 */
	PPP_IPCP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
	PPP_IPCP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
	PPP_IPCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
	PPP_IPCP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
    VOS_UINT32 ulIpv4cpLen;
    UCHAR ucUsedFlag;                  /*IPCP控制块使用标记*/
    UCHAR ucPppIpcpInfoRev[3];                  /*保留字段*/
} PPPIPCPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPCP_TYPE_H_ */






