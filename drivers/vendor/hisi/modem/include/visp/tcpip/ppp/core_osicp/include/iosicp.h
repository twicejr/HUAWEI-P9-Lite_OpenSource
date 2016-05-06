/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              iosicp.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description: Defines All interface of the OSICP Component
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/


#ifndef _IOSICP_H_
#define _IOSICP_H_

#ifdef __cplusplus
extern "C" {
#endif


DECLARE_INTERFACE (IIF_OSICP_ComIntFUN)
{
    IUNKNOWN_METHODS
        
    METHOD_(VOID, pfPPP_OSICP_Init)(PPPINFO_S* pstPppInfo);
    METHOD_(VOID, pfPPP_OSICP_ReceiveEventFromCore)(VOID *pstMuxcpInfo, ULONG ulCmd, char *pPara);
    METHOD_(VOID, pfPPP_OSICP_ReceivePacket)(VOID *pstMuxcpInfo, UCHAR *pucHead, UCHAR *pucPacket, ULONG ulLen);
    METHOD_(ULONG, pfPPP_OSICP_UpResetCi)(PPPINFO_S *pstPppInfo);
};

DECLARE_INTERFACE (IIF_OSICP_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfOSICP_Init_Com)(const COM_ID_INFO_S * pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfOSICP_Active_Com)(VOID);
    METHOD_(ULONG, pfOSICP_SetModuleInfo)(OSICP_MOD_INFO_S * pstMInfo);
    
};
 

DECLARE_INTERFACE (IIF_OSICP_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagOSICP_IntObj
{
    struct IIF_OSICP_ComIntFUN    *pCompIntFUN;
    struct IIF_OSICP_ComIntCFG    *pCompIntCFG;
    struct IIF_OSICP_ComIntSSA    *pCompIntSSA;
}OSICP_INT_OBJ_S;

#ifdef __cplusplus
}
#endif
#endif
