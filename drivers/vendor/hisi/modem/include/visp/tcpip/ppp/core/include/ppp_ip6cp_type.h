/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             ppp_ip6cp_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2003-07-20
 *        Author: Syed Ajim Hussain
 *   Description: The File Contains all Data Structures of IPv6CP Protocol. 
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME                DESCRIPTION
 *  2003-07-20      Syed Ajim Hussain   Create
 *  2004-07-01      YiAn                Modified for VISP
 *  2006-03-31      ZhuKun              Adjust for D00661
 *  2006-04-21      ZhuKun              Adjust for D00875
 *  2006-05-11      luyao               为支持ARM CPU字节对齐特性，修改结构。
 *
 *************************************************************************/

#ifndef _IP6CP_TYPE_H_
#define _IP6CP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* IP6CP协商选项 */
#define IP6CP_CI_INTERFACEID_TYPE     1  /*IPv6 Interface Identifier */
#define IP6CP_CI_COMPPROTOCOL         2  /*IPv6 Compression Protocol*/

/* IP6CP协商选项长度 */
#define IP6CP_CILEN_VOID                2
#define IP6CP_CILEN_INTERFACEID         10  /* the length of interface identifier options */
#define IP6CP_CILEN_COMPPROTOCOL        4   /* min length for compression protocol opt. */

#define IP6CP_INTERID_ISZERO(InterfaceID) \
( ((InterfaceID)[0]== 0x00) && \
  ((InterfaceID)[1]== 0x00) && \
  ((InterfaceID)[2]== 0x00) && \
  ((InterfaceID)[3]== 0x00) && \
  ((InterfaceID)[4]== 0x00) && \
  ((InterfaceID)[5]== 0x00) && \
  ((InterfaceID)[6]== 0x00) && \
  ((InterfaceID)[7]== 0x00) )


#define IP6CP_INTERFACE_EQUAL(myInterfaceID,hisInterfaceID) \
( (myInterfaceID[0]==hisInterfaceID[0]) && \
  (myInterfaceID[1]==hisInterfaceID[1]) && \
  (myInterfaceID[2]==hisInterfaceID[2]) && \
  (myInterfaceID[3]==hisInterfaceID[3]) && \
  (myInterfaceID[4]==hisInterfaceID[4]) && \
  (myInterfaceID[5]==hisInterfaceID[5]) && \
  (myInterfaceID[6]==hisInterfaceID[6]) && \
  (myInterfaceID[7]==hisInterfaceID[7]) )

#define IPV6CP_INTF_ID_TYPE_MANUAL   0x02 
#define IPV6CP_INTF_ID_TYPE_AUTO     0x01 

typedef struct tagPppIp6cpInfo
{
    PPPINFO_S *pstPppInfo;              /* PPP控制块指针 */
    PPPFSM_S  stFsm;                    /* IP6CP协议状态机 */
    ULONG     ulInterfaceIDChanged;     /* 1  -> Automatic , 2  Manual Configuration */ 
    BOOL_T    bIsNakSentforEmptyID;
    UCHAR     ucPadding[2];
    PPP_IP6CP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_IP6CP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_IP6CP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_IP6CP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} PPPIP6CPINFO_S;

typedef struct  tagIPv6Addr_Flag
{
    UCHAR   ucflag;              /* 1->Auto , 2->Manual */
    UCHAR   szIPv6Addr[LEN_16];
}IPV6_ADDR_FLAG_S; 

/* 接口函数 */
VOID PPP_IP6CP_Init(PPPINFO_S *, UCHAR *);
VOID PPP_IP6CP_ReceiveEventFromCore (VOID *, ULONG , UCHAR *);
VOID PPP_IP6CP_ReceivePacket (VOID *, UCHAR*, UCHAR*, ULONG);

/* 回调函数 */
VOID PPP_IP6CP_resetci(PPPFSM_S *f);
USHORT PPP_IP6CP_cilen(PPPFSM_S *);
VOID PPP_IP6CP_addci(PPPFSM_S *, UCHAR *);
USHORT PPP_IP6CP_ackci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_IP6CP_nakci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_IP6CP_rejci(PPPFSM_S *, UCHAR *, ULONG);
UCHAR PPP_IP6CP_reqci(PPPFSM_S *, UCHAR *, ULONG *);
VOID PPP_IP6CP_up(PPPFSM_S *);
VOID PPP_IP6CP_down(PPPFSM_S *);
VOID PPP_IP6CP_finished(PPPFSM_S *);
VOID PPP_IP6CP_starting(PPPFSM_S *);
/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: IP6CP定时器传入接口索引指针 */
VOID PPP_IP6CP_FSM_TimeOut(VOID *pIfIndex);
VOID PPP_IP6CP_Ncp_Reset(VOID *pIfIndex);

#ifdef __cplusplus
}
#endif

#endif      /* end of _IP6CP_TYPE_H_ */

