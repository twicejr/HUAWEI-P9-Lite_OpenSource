



#ifndef _NVIM_INTERFACE_H
#define _NVIM_INTERFACE_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"

#if defined(DMT)

#include "vos.h"
#include "NvIdList.h"
#include "SysNv.h"
#include "nvim_comminterface.h"

#pragma pack(4)

enum NV_RESUME_ITEM    /*comm*/
{
    NV_MANUFACTURE_ITEM = 0,
    NV_USER_ITEM,
    NV_SECURE_ITEM,
    NV_ITEM_BUTT
};
typedef VOS_UINT32 NV_RESUME_ITEM_ENUM_UINT32;

VOS_UINT32 NV_WriteExMemory(MODEM_ID_ENUM_UINT16 enModemID, VOS_UINT16 usID, VOS_VOID *pItem, VOS_UINT32 ulLength);
VOS_UINT32 NV_ReadEx(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_ReadPartEx(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_UINT32 ulOffset,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_WriteEx(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_WritePartEx(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_UINT32 ulOffset,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_Flush(VOS_VOID);
VOS_UINT32 NV_GetLength(VOS_UINT16 usID, VOS_UINT32 *pulLength);
VOS_UINT32 NV_Get16BitLength(VOS_UINT16 usID, VOS_UINT16 *pusLength);
VOS_UINT32 NV_Backup(VOS_VOID);
VOS_UINT32 NV_RestoreManufactureExt(VOS_VOID);
VOS_UINT32 NV_RestoreAll(VOS_VOID);
VOS_UINT32 NV_RestoreManufactureDefault(VOS_VOID);
VOS_UINT32 NV_QueryRestoreResult(VOS_VOID);
VOS_UINT32 NV_SpecialNvIdBackup(VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_GetResumeNvIdNum(NV_RESUME_ITEM_ENUM_UINT32 enNvItem);
VOS_UINT32 NV_GetResumeNvIdList(NV_RESUME_ITEM_ENUM_UINT32 enNvItem, VOS_UINT16 *pusNvList, VOS_UINT32 ulNvNum);
VOS_UINT32 NV_GetNVIdListNum(VOS_VOID);
VOS_UINT32 NV_GetNVIdList(NV_LIST_INFO_STRU *pstNvIdList);
VOS_UINT32 NV_BackupCheck(VOS_VOID);
VOS_UINT32 NV_SwitchCarrier(VOS_CHAR *pcCarrierName,VOS_UINT32 ulCarrierNameLen,VOS_BOOL *pbIsSwitchImage);

/*LTE NV STRUB START */
VOS_UINT32 NVM_RevertFNV(VOS_VOID);

VOS_UINT32 NVM_BackUpFNV(VOS_VOID);
/*LTE NV STRUB end */

#if defined (INSTANCE_1)
#define NV_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_1,(usID),(pItem),(ulLength))

#define NV_ReadPart(usID,ulOffset,pItem,ulLength)   NV_ReadPartEx(MODEM_ID_1,(usID),(ulOffset),(pItem),(ulLength))

#define NV_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_1,(usID),(pItem),(ulLength))

#define NV_WritePart(usID,ulOffset,pItem,ulLength)  NV_WritePartEx(MODEM_ID_1,(usID),(ulOffset),(pItem),(ulLength))
#else
#define NV_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_0,(usID),(pItem),(ulLength))

#define NV_ReadPart(usID,ulOffset,pItem,ulLength)   NV_ReadPartEx(MODEM_ID_0,(usID),(ulOffset),(pItem),(ulLength))

#define NV_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_0,(usID),(pItem),(ulLength))

#define NV_WritePart(usID,ulOffset,pItem,ulLength)  NV_WritePartEx(MODEM_ID_0,(usID),(ulOffset),(pItem),(ulLength))
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#else
#include "mdrv_nvim.h"
#include "mdrv_nvim_comm.h"
#include "vos.h"
#include "NvIdList.h"
#include "SysNv.h"
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

