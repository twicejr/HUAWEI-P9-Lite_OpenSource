


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






