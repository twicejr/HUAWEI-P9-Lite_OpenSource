

#ifndef      _LCP_TYPE_H_
#define      _LCP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */



typedef struct tagPppLcpInfo
{
    PPPINFO_S *pstPppInfo ;           /* PPP控制块指针 */
    PPPFSM_S  stFsm;                  /* LCP协议状态机 */
    PPP_LCP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_LCP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_LCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_LCP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */

    
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    UCHAR ucUsedFlag:1;               /* lcp控制块使用标记，0:未使用；1:已占用*/
    UCHAR bReqSendAck:1;              /* lcp状态机处于open态收到终端request直接回复ack不触发重协商标记,0:尚未收到request 1:已经收到 */
    UCHAR bRevbit:6;
#else
    UCHAR bRevbit:6;
    UCHAR bReqSendAck:1;              /* lcp状态机处于open态收到终端request直接回复ack不触发重协商标记,0:尚未收到request 1:已经收到 */
    UCHAR ucUsedFlag:1;               /* lcp控制块使用标记，0:未使用；1:已占用*/
#endif
    UCHAR ucPppLcpInfoRev[7];          /*保留字段*/
} PPPLCPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _LCP_TYPE_H_ */





