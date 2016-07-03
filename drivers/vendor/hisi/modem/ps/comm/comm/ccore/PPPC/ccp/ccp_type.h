

#ifdef		__cplusplus
extern		"C"{
#endif

#ifndef _CCP_TYPE_H_
#define _CCP_TYPE_H__
/********************************************************************/

/********************************************************************/
typedef struct tagPppCcpInfo
{
    PPPINFO_S *pstPppInfo ;            /* PPP控制块指针 */
    PPP_CCP_options_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_CCP_options_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_CCP_options_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_CCP_options_S stAllowOptions;  /* 允许与对方协商的我的选项 */
    PPPFSM_S  stFsm;                   /* CCP协议状态机 */
    HTIMER     ulCcpTimeoutID;          /* CCP协商超时定时器 */

    VOS_UINT32     ulTimeOutTime;
    UCHAR  ucPppCompType;           /* 1：MPPC，2：LZS0，3：LZS1*/
    UCHAR  ucUsed;               /*ccp控制块占用标记*/
    UCHAR  ucPppCcpInfoRev[2];     /*保留字段*/


} PPP_CCP_INFO_S ;
/********************************************************************/

#endif /*_CCP_TYPE_H_*/

#ifdef		__cplusplus
}
#endif
