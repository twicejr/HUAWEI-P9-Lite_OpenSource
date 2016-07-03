

#ifndef      _IPV6CP_TYPE_H_
#define      _IPV6CP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/*说明 目前该结构必须同v4保持一致，因为目前的删除函数使用的是同一个*/
typedef struct tagPppIpV6cpInfo
{
    PPPINFO_S *pstPppInfo ;               /* PPP控制块指针 */
    UCHAR * pucIpv6cpMsg;
    PPPFSM_S  stFsm;                     /* IPv6CP协议状态机 */
    PPP_IPV6CP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_IPV6CP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_IPV6CP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_IPV6CP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
    VOS_UINT32 ulIpv6cpLen;
    UCHAR ucUsedFlag;                    /*IPv6CP控制块使用标记,1占用；0，未占用*/
    UCHAR ucIpv6cpInfoRev[3];            /*保留字段*/
} PPPIPV6CPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPCP_TYPE_H_ */






