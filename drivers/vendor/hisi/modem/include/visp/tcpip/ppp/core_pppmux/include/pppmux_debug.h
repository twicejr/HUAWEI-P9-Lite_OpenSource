/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_debug.h
*
*  Project Code: VISPV100R005
*   Module Name:   
*  Date Created: 2006-5-12
*        Author: ZhouTong(43740)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-05-12  ZhouTong(43740)  Create
*
*******************************************************************************/

#ifndef _PPPMUX_DEBUG_H_
#define _PPPMUX_DEBUG_H_

#ifdef  __cplusplus
extern "C"{
#endif

VOID PPPMUX_Debug_SubFrame(PPPINFO_S* pstPppInfo, ULONG ulSubFrameLen, 
                           ULONG ulPacketLen, UCHAR ucPFF, UCHAR ucLXT, 
                           USHORT usProtocol, UCHAR ucIsInPacket);
VOID PPPMUX_Debug_MuxFrame(PPPINFO_S* pstPppInfo, ULONG ulFrameLen, 
                           ULONG ulPayLoadLen, ULONG ulSubFrameCount, 
                           UCHAR ucIsInPacket);
VOID PPPMUX_Debug_Error(PPPINFO_S* pstPppInfo, CHAR* pszString);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _PPPMUX_DEBUG_H_ */

