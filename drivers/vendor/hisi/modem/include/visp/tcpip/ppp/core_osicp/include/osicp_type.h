/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_type.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description:  PPP的OSICP协议模块自有数据结构       
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/


#ifndef      _OSICP_TYPE_H_
#define      _OSICP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */



typedef struct tagPppOsicpInfo
{
    PPPINFO_S *pstPppInfo ;             /* PPP控制块指针 */
    PPPFSM_S  stFsm;                    /* OSICP协议状态机 */
    PPP_OSICP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_OSICP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_OSICP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_OSICP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} PPPOSICPINFO_S ;

typedef struct tagOSICP_ModInfo
{
    ULONG ulMID_OSICP;          /*模块ID*/
}OSICP_MOD_INFO_S;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _OSICP_TYPE_H_ */



