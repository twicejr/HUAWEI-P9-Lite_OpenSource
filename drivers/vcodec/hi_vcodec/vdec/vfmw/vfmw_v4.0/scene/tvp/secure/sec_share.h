
#ifndef __VFMW_SEC_SHARE_H__
#define __VFMW_SEC_SHARE_H__

#include "vfmw.h"

// Interface of SEC Share
SINT32 SEC_ShareZone_Init(UINT32 Share);
VOID   SEC_ShareZone_Exit(VOID);
SINT32 SEC_EventReport(SINT32 ChanID, SINT32 Type, VOID* pArgs, UINT32 Len);
SINT32 SEC_ReadRawStream(SINT32 InstID, STREAM_DATA_S *pRawPacket);
SINT32 SEC_ReleaseRawStream(SINT32 InstID, STREAM_DATA_S *pRawPacket);
SINT32 SEC_ControlAdjust(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs);
SINT32 SEC_ControlConverse(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs);
SINT32 SEC_Buffer_Handler(SINT32 ChanID, SINT32 Type, VOID *pArgs);
SINT32 SEC_ReadProc(SINT8 *Page, SINT32 Count);
SINT32 SEC_WriteProc(UINT32 Option, SINT32 Value);

#endif

