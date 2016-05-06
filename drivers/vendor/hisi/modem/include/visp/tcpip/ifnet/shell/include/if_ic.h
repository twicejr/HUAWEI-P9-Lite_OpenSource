/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_IC.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/11/03 
 *        Author: Zhouxiaoniu
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/11/03      Zhouxiaoniu     Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2006-05-10  lu yao(60000758)    为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/

#ifndef _IF_IC_H_
#define _IF_IC_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* 输出信息的类型宏定义 */
#define IC_INFO_LOG             1
#define IC_INFO_TRAP            2
#define IC_INFO_DEBUG           3
#define IC_INFO_HIDE            0x8

#define IC_INFOMODU_MASK        0xFFFF0000 /*ULONG的高16位bit31~bit16为模块号*/
#define IC_INFOTYPE_MASK        0x00007000 /*ULONG的bit15~bit12为信息类型*/
#define IC_INFONO_MASK          0x00000FFF /*ULONG的低12位(bit11~bit0)为本类信息在本模块的内部编号*/

/*信息ID宏定义*/
#define IC_INFOID_DEF(mid, infotype, infoidx) ( (mid) | ( (infotype) << 12 ) | (infoidx) )

/*从信息ID获取信息来自的模块号*/
#define IC_INFOMODU(InfoID) ( (InfoID) & IC_INFOMODU_MASK )  

/*从信息ID获取其信息类型*/
#define IC_INFOTYPE(InfoID) ( ((InfoID) & IC_INFOTYPE_MASK) >> 12)  

/*从信息ID获取信息在模块内的编号*/
#define IC_INFONO(InfoID)  ( (InfoID) & IC_INFONO_MASK) 

/*************************************************************************
*                                                                        *
*                  日志提示信息ID定义                                    *
*                                                                        *
**************************************************************************/
enum{
    IF_INFO_ID_LINKPROTO_UPDOWN = 1,
    IF_INFO_ID_LINKLCPPROTO_UPDOWN,
    IF_INFO_ID_LINKMUXCPPROTO_UPDOWN,
    IF_INFO_ID_LINKLACPPROTO_UPDOWN,  /* Trunk LACP */
    IF_INFO_ID_LINKOSICPPROTO_UPDOWN, /* OSICP */
    IF_INFO_ID_MAX
} ;
/* Modified by f54882, 使用tcpip_id.h中定义的MID, 2008/1/18 */
/* 协议状态信息 */
#define IFNET_LOGID_LINKPROTO_UPDOWN            IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKPROTO_UPDOWN)
#define IFNET_LOGID_LINKLCPPROTO_UPDOWN         IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKLCPPROTO_UPDOWN)
#define IFNET_LOGID_LINKMUXCPPROTO_UPDOWN       IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKMUXCPPROTO_UPDOWN)
#define IFNET_LOGID_LINKLACPPROTO_UPDOWN        IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKLACPPROTO_UPDOWN)
#define IFNET_LOGID_LINKOSICPPROTO_UPDOWN       IC_INFOID_DEF(MID_COMP_IFNET, IC_INFO_LOG, IF_INFO_ID_LINKOSICPPROTO_UPDOWN)

/*************************************************************************
*                                                                        *
*                    定义参数格式                                        *
*                                                                        *
**************************************************************************/
#define MSG_FMT_NONE            1                 /* 没有参数 */
#define MSG_FMT_ONEZERO         2                 /* one string */
#define MSG_FMT_TWOZERO         3                 /* two string */
#define MSG_FMT_ONEONE          4                 /* one string, one ULONG */
#define MSG_FMT_TWOONE          5                 /* two string, one ULONG */
#define MSG_FMT_THREETWO        6                 /* three string, two ULONG */
#define MSG_FMT_ZEROONE         7                 /* one ULONG */
#define MSG_FMT_ZEROTWO         8                 /* two ULONG */


#ifndef  _CLI_PUB_H
enum
{
    LANGUAGE_ENGLISH,
    LANGUAGE_CHINESE,
    LANGUAGE_RUSSIAN,
    LANGUAGE_MAX
};

typedef struct tagInformation
{
    ULONG ulInfoID;
    CHAR * szInfo[LANGUAGE_MAX];
} VRP_INFORMATION;
#endif

#define SECTION_NAME_LEN        80

#define   EXEC_DISPLAY_STOP         1  /* added by ljw */
#define   EXEC_DISPLAY_CONTINUE     0  /* added by ljw */

/* 函数声明 */
ULONG IF_SendInfoToIC(ULONG , CHAR** , ULONG ,ULONG , ULONG);

#ifdef  __cplusplus
}
#endif

#endif  /* end of _IF_IC_H_ */

