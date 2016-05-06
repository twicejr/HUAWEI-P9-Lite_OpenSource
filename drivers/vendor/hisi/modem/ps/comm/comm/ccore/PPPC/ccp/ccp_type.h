/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ccp_type.h
  版 本 号   : 初稿
  作    者   : luofang
  生成日期   : 2012年11月8日
  最近修改   :
  功能描述   :    PPP模块定义CCP协议结构体
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年11月8日
    作    者   : luofang
    修改内容   : 创建文件

******************************************************************************/

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

    VOS_UINT32     ulTimeOutTime;           /* CCP协商超时时间 */
    UCHAR  ucPppCompType;           /* 1：MPPC，2：LZS0，3：LZS1*/
    UCHAR  ucUsed;               /*ccp控制块占用标记*/
    UCHAR  ucPppCcpInfoRev[2];     /*保留字段*/


} PPP_CCP_INFO_S ;
/********************************************************************/

#endif /*_CCP_TYPE_H_*/

#ifdef		__cplusplus
}
#endif
