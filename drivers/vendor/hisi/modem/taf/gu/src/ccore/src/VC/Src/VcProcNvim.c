
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "VcCtx.h"
#include "VcProcNvim.h"
#include "NVIM_Interface.h"
#include "VcComm.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "VcMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_VC_PROC_NIVM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*****************************************************************************
   4 函数实现
*****************************************************************************/


VOS_VOID  APP_VC_ReadPcVoiceSupportNvim( VOS_VOID )
{
    APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU                  stPcVoiceSupportFlag;
    APP_VC_MS_CFG_INFO_STRU                                *pstMsCfgInfo;
    VOS_UINT32                                              ulLength;

    pstMsCfgInfo                        = APP_VC_GetCustomCfgInfo();

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_PCVOICE_Support_Flg, &ulLength);
    if (ulLength > sizeof(stPcVoiceSupportFlag))
    {
        return;
    }
    stPcVoiceSupportFlag.usPcVoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;

    if (NV_OK != NV_Read(en_NV_Item_PCVOICE_Support_Flg, &stPcVoiceSupportFlag, ulLength))
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;
        VC_WARN_LOG("APP_VC_ReadAlsSupportNvim: NV Read en_NV_Item_PCVOICE_Support_Flg Fail" );
        return;
    }

    if ( (APP_VC_NV_ITEM_ACTIVE != stPcVoiceSupportFlag.usPcVoiceSupportFlag)
       &&(APP_VC_NV_ITEM_DEACTIVE != stPcVoiceSupportFlag.usPcVoiceSupportFlag))
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = APP_VC_NV_ITEM_DEACTIVE;
    }
    else
    {
        pstMsCfgInfo->usVcPcvoiceSupportFlag = stPcVoiceSupportFlag.usPcVoiceSupportFlag;
    }

    return;
}


VOS_VOID APP_VC_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_PCVOICE_Support_Flg */
    APP_VC_ReadPcVoiceSupportNvim();
    return;
}

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



