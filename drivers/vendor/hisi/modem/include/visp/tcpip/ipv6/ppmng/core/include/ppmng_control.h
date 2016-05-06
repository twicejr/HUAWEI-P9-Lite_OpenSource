/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_control.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: Input and Output Control Packet options of the IPv6 Stack
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/
#ifndef _IP6_PPMNGCTRL_H
#define _IP6_PPMNGCTRL_H

#ifdef __cplusplus
extern "C"{
#endif


#define MERGE_RECVOPT(new, old, type) \
    if ((new)->type) \
    {\
        if ((old)->type)\
        {\
            MBUF_Destroy((old)->type);\
        }\
        (old)->type = (new)->type;\
            (new)->type = NULL; \
    }


/*
 * 下面的宏用于将选项结构中的MBUF链接起来
 * opt : 选项结构的指针
 * type : 处理的选项
 * p : 目前MBUF链上最后一个MBUF的指针的指针
 */
#define LINK_RECVOPTS(opt, type, p) \
    if((opt)->type) \
    { \
        if(*p) \
        { \
            MBUF_ASSIGN_PTR_NEXT_MBUF((*p), (opt)->type); \
            p = &opt->type;\
        } \
        else \
        { \
            *(p) = (opt)->type;\
        }\
    }


#define PKTOPT_EXTHDRCPY(type) \
    { \
        ULONG ulHlen = IP6_GET_HDRLEN (pstOpts->type);\
            if (0 != ulHlen)\
            {\
                pstPktOpts->type = TCPIP_Malloc(g_stPPModInfo.ulModID | SID_IP6_CREATOPTION, ulHlen);\
                if (NULL == pstPktOpts->type)\
                {\
                    goto bad;\
                }\
                (VOID)TCPIP_Mem_Copy (pstPktOpts->type, ulHlen, pstOpts->type, ulHlen);\
            }\
    }

#define PP_SET_STICKY       1
#define PP_NO_MSG           0

#define IN6PLOOKUP_WILDCARD                 1
#define IN6PLOOKUP_SETLOCAL                 2

/* Packet I/O Control Options. */
#define INDEX_IF_VOID               0X00000000


#define IN6ADDR_ANY \
{{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}

#ifndef PRCO_GETOPT
#define PRCO_GETOPT     0
#endif

#ifndef PRCO_SETOPT
#define PRCO_SETOPT     1
#endif

#ifndef IP6_DEFAULT_TCLASS
/* TODO: Need to define a proper Value */
#define IP6_DEFAULT_TCLASS       0x0
#endif

#define     NO_USE(var)     (VOID)(var)

/* Function Prototypes. */
VOID IP6_PP_Update_RecvOpt(IP6_RECVPKTOPTS_S *pOldOpts, IP6_RECVPKTOPTS_S *pNewOpts);
VOID IP6_PP_Reset_RcvOpt(IP6_RECVPKTOPTS_S *pstOpts, LONG lOptName);
VOID IP6_PP_SaveControl(UINTPTR ulIn6Pcb, IP6_S *pstIp6, MBUF_S **ppstMBuf,
                           IP6_RECVPKTOPTS_S *pstOpt, IP6_RECVPKTOPTS_S **ppstPrevOpt);
VOID IP6_PP_InitPktOptions(IP6_PKTOPTS_S *pOpt);
VOID IP6_PP_ClearPktOpts(IP6_PKTOPTS_S *pOpt, LONG lOptName);
LONG IP6_PP_SetPktOption(UINTPTR pSocket, LONG lOptName, UCHAR *pucOptData, LONG lLen, 
        IP6_PKTOPTS_S *pstOpt, LONG lPriv, LONG lSticky, LONG lCmsg);
LONG IP6_PP_SetPktOptions(UINTPTR pSocket, MBUF_S *pMBuf, IP6_PKTOPTS_S *pOpt, 
                              ULONG priv, ULONG needcopy);
LONG IP6_PP_PcbOpt(UINTPTR pSocket, LONG lOptName, UCHAR *pucOptData,    LONG lLen,
        IP6_PKTOPTS_S **ppstPktOpt, LONG lPriv);
VOID IP6_PP_FreePcbOpts(IP6_PKTOPTS_S *pOpt);
LONG IP6_PP_SetMOptions(LONG lOptName, IP6_MOPTIONS_S **ppstIpMopP, MBUF_S *pstMBuf);
LONG IP6_PP_GetMOptions(LONG lOptName, IP6_MOPTIONS_S *pstIpMopP, MBUF_S **ppstMBuf);
VOID IP6_PP_FreeMOptions(IP6_MOPTIONS_S *pstIpMo);
ULONG IP6_PP_Set_INPCB_InputOptions (UINTPTR ulIn6Pcb, LONG lOptValue, ULONG ulIn6pflags);
LONG IP6_PP_Get_INPCB_OuputOptions (UINTPTR ulIn6Pcb, MBUF_S **ppstMBuf, ULONG ulIn6Flags);
LONG IP6_PP_CtlOutput (LONG lOper, UINTPTR ulSocket, LONG lLevel, LONG lOptName, MBUF_S **ppMBuf);
IP6_PKTOPTS_S *IP6_PP_CopyPktOpts (IP6_PKTOPTS_S *pstOpts);
ULONG IP6_PP_ExtHdrLen (IP6_PKTOPTS_S *pstPktOpts);
/* END: Function Prototypes. */

#ifdef __cplusplus
extern "C"{
#endif

#endif 

