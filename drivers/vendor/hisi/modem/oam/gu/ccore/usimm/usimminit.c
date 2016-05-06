/************************************************************************
  Copyright    : 2015-2017, Huawei Tech. Co., Ltd.
  File name    : UsimmInit.c
  Author       : zhuli 00100318
  Version      : V800R001
  Date         : 2015-3-7
  Description  : 该C文件给出了---卡初始化模块实现
  Function List:
  History      :
 ************************************************************************/

#include "vos_Id.h"
#include "usimminit.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "siappstk.h"
#include "NvIdList.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "errorlog.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "CasNvInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_INIT_C
/*lint +e960*/

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
/* USIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aUSIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitUsimGlobal,         USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitUsimADF,            USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimECC,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimEFLI,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimATT,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimMFile,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimMFile2,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimFinish,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimOPFile,         USIMM_FUNC_AVAILABLE}
};

/* CSIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aCSIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitCsimGlobal,         USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitCsimADF,            USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimECC,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimMFile,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitStoreEsnMeid,       USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimMFile2,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimEFMecrp,        USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimEF3gpd,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimFinish,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimOPFile,         USIMM_FUNC_AVAILABLE}
};

/* CSIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aVIACSIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitCsimGlobal,         USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitCsimADF,            USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitVIACsimFinish,      USIMM_FUNC_AVAILABLE},
};

/* ISIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aISIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitIsimGlobal,         USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitIsimADF,            USIMM_FUNC_AVAILABLE},  /*位置需要固定*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimMFile,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimFinish,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimOPFile,         USIMM_FUNC_AVAILABLE}
};

/* UICC卡应用初始化列表 */
USIMM_INITAPPLIST_STRU g_aUICCInitProcTbl[] =
{
    {g_aUSIMInitProcFuncTbl,            ARRAYSIZE(g_aUSIMInitProcFuncTbl)},
    {g_aISIMInitProcFuncTbl,            ARRAYSIZE(g_aISIMInitProcFuncTbl)},
    {g_aCSIMInitProcFuncTbl,            ARRAYSIZE(g_aCSIMInitProcFuncTbl)}
};

/* UICC卡上电初始化过程函数列表 */
USIMM_COMM_CARD_INIT_FUNC g_aUICCCommInitProcFuncTbl[] =
{
    {USIMM_UICC_InitGlobalVar,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCardTypeByATR,      USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InsertCommFileToPool,   USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_ProfileDownload,        USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_DecodeEFDIR,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_DecodeATRStep2,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_SortAppSN,              USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_ActiveADFAll,           USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitCardApps,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_CheckCSIM,              USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimSimuState,      USIMM_FUNC_AVAILABLE}
};

/* SIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aSIMInitProcFuncTbl[] =
{
    {USIMM_ICC_InitSimGlobal,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimADF,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPINInfo,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InsertCommFileToPool,    USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimECC,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimEFLP,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimATT,              USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPhase,               USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimSST,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitTerminalProfile,     USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimFBDN,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimMFile,            USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimMFile2,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimFinish,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimOPFile,           USIMM_FUNC_AVAILABLE}
};

/* UIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aUIMInitProcFuncTbl[] =
{
    {USIMM_ICC_InitUimGlobal,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimADF,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPINInfo,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InsertCommFileToPool,    USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimECC,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimRuimId,           USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPhase,               USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitCST,                 USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitTerminalProfile,     USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimFdnBdn,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimMFile,            USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitStoreEsnMeid,        USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimMFile2,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimEFMecrp,          USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimEF3gpd,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimFinish,           USIMM_FUNC_AVAILABLE}
};

/* UIM卡初始化列表 */
USIMM_INITAPPLIST_FUNC g_aVIAUIMInitProcFuncTbl[] =
{
    {USIMM_ICC_InitUimGlobal,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimADF,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPINInfo,             USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimFinish,           USIMM_FUNC_AVAILABLE}
};

/* ICC卡应用初始化列表 */
USIMM_INITAPPLIST_STRU g_aICCInitProcTbl[] =
{
    {g_aSIMInitProcFuncTbl,             ARRAYSIZE(g_aSIMInitProcFuncTbl)},
    {VOS_NULL_PTR,                      0},
    {g_aUIMInitProcFuncTbl,             ARRAYSIZE(g_aUIMInitProcFuncTbl)}
};

/* ICC卡上电初始化过程函数列表 */
USIMM_COMM_CARD_INIT_FUNC g_aICCCommInitProcFuncTbl[] =
{
    {USIMM_ICC_InitGlobalVar,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitCardTypeByATR,       USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitAppOrder,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitCardApps,           USIMM_FUNC_AVAILABLE}
};

/* 控制应用初始化结构 */
USIMM_INITAPPSCTRL_STRU                 g_astUSIMMInitAppCtrl[USIMM_CARDAPP_BUTT];

/*****************************************************************************
函 数 名  :USIMM_COMM_ClearInitCtrlGlobal
功能描述  :完成卡初始化的全局变量的初始化
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ClearInitCtrlGlobal(VOS_VOID)
{
    VOS_UINT32                  i;

    /*lint -e534*/
    VOS_MemSet(g_astUSIMMInitAppCtrl, 0, sizeof(g_astUSIMMInitAppCtrl));
    /*lint +e534*/

    for(i=0; i < ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        g_astUSIMMInitAppCtrl[i].enAppType          = USIMM_UNLIMIT_APP_BUTT;
        g_astUSIMMInitAppCtrl[i].ucChannelNo        = VOS_NULL_BYTE;
        g_astUSIMMInitAppCtrl[i].enAppInitResult    = USIMM_INITAPPS_BUTT;
        g_astUSIMMInitAppCtrl[i].enAppStepResult    = USIMM_INITSTEPS_BUTT;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_ResetInitGlobal
功能描述  :完成初始化的全局变量在重启的时候需要清空的变量
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ResetInitGlobal(VOS_VOID)
{
    VOS_UINT32                  i;

    for(i=0; i<ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        g_astUSIMMInitAppCtrl[i].ucChannelNo        = VOS_NULL_BYTE;

        g_astUSIMMInitAppCtrl[i].enAppStepResult    = USIMM_INITSTEPS_BUTT;

        g_astUSIMMInitAppCtrl[i].ucCurStep          = VOS_NULL;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_ClearAppInfoGlobal
功能描述  :完成卡初始化的APP Info全局变量的初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ClearAppInfoGlobal(VOS_VOID)
{
    VOS_UINT32                          i;

    /*lint -e534*/
    VOS_MemSet(g_astUSIMMCardAppInfo, 0, sizeof(g_astUSIMMCardAppInfo));
    VOS_MemSet(g_astUSIMMInitAIDInfo, 0, sizeof(g_astUSIMMInitAIDInfo));
    /*lint +e534*/

    for(i=0; i<USIMM_CHANNEL_NUMBER_MAX; i++)
    {
        g_astUSIMMCardAppInfo[i].enAppType      = USIMM_UNLIMIT_APP_BUTT;

        g_astUSIMMCardAppInfo[i].enAppService   = USIMM_CARD_SERVIC_ABSENT;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_ResetInitListStatus
功能描述  :完成卡初始化的全局变量的初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ResetInitListStatus(VOS_VOID)
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType;
    USIMM_CARDAPP_ENUM_UINT32               enAppType;
    VOS_UINT32                              ulAppNum;
    VOS_UINT32                              i;
    USIMM_INITAPPLIST_FUNC                 *pstListItem;

    /* 恢复UICC公共初始化列表状态 */
    for (i = 0; i < ARRAYSIZE(g_aUICCCommInitProcFuncTbl); i++)
    {
        g_aUICCCommInitProcFuncTbl[i].enStatus = USIMM_FUNC_AVAILABLE;
    }

    /* 恢复ICC公共初始化列表状态 */
    for (i = 0; i < ARRAYSIZE(g_aICCCommInitProcFuncTbl); i++)
    {
        g_aICCCommInitProcFuncTbl[i].enStatus = USIMM_FUNC_AVAILABLE;
    }

    /* 恢复应用初始化列表状态 */
    for (enCardType = USIMM_PHYCARD_TYPE_ICC; enCardType <= USIMM_PHYCARD_TYPE_UICC; enCardType++)
    {
        for (enAppType = USIMM_GUTL_APP; enAppType < USIMM_CARDAPP_BUTT; enAppType++)
        {
            ulAppNum    = USIMM_COMM_GetAppInitNum(enCardType, enAppType);
            pstListItem = USIMM_COMM_GetAppInitList(enCardType, enAppType);

            for (i = 0; i < ulAppNum; i++)
            {
                pstListItem[i].enStatus = USIMM_FUNC_AVAILABLE;
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitCommFuncTble
功能描述  :完成卡初始化的全局变量列表的上电初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_InitCommFuncTble(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    g_aUICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aCSIMInitProcFuncTbl;
    g_aUICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aCSIMInitProcFuncTbl);

    g_aICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aUIMInitProcFuncTbl;
    g_aICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aUIMInitProcFuncTbl);

    return;

#else
    if (VOS_TRUE == USIMM_IsCLEnable()) /*拼片功能打开*/
    {
        g_aUICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aVIACSIMInitProcFuncTbl;
        g_aUICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aVIACSIMInitProcFuncTbl);

        g_aICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aVIAUIMInitProcFuncTbl;
        g_aICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aVIAUIMInitProcFuncTbl);
    }
    else
    {
        g_aUICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aCSIMInitProcFuncTbl;
        g_aUICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aCSIMInitProcFuncTbl);

        g_aICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aUIMInitProcFuncTbl;
        g_aICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aUIMInitProcFuncTbl);
    }

    return;
#endif

}

/*****************************************************************************
函 数 名  :USIMM_COMM_ResetPIN1Global
功能描述  :完成卡PIN初始化的全局变量的初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ResetPIN1Global(VOS_VOID)
{
    VOS_UINT32          i;

    for (i = 0; i < ARRAYSIZE(g_astUSIMMAppPIN1Info); i++)
    {
        if (g_astUSIMMAppPIN1Info[i].ucPINLen != 0)
        {
            continue;
        }

        g_astUSIMMAppPIN1Info[i].enPinEnable    = USIMM_PIN_ENABLE_BUTT;
        g_astUSIMMAppPIN1Info[i].enPinVerified  = USIMM_PIN_VERIY_BUTT;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_GetAppInitList
功能描述  :获取多应用卡的函数列表
输入参数  :enCardType
           enAppType
输出参数  :无
返 回 值  :USIMM_INITAPPLIST_FUNC*
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITAPPLIST_FUNC* USIMM_COMM_GetAppInitList(
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType,
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        return g_aUICCInitProcTbl[enAppType].pFuncList;
    }

    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        return g_aICCInitProcTbl[enAppType].pFuncList;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_GetAppInitNum
功能描述  :获取多应用卡初始化函数个数
输入参数  :enCardType
           enAppType
输出参数  :无
返 回 值  :list num
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_COMM_GetAppInitNum(
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType,
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        return g_aUICCInitProcTbl[enAppType].ulListNum;
    }

    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        return g_aICCInitProcTbl[enAppType].ulListNum;
    }

    return 0;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_IsGcfSim
功能描述  :通过ATR数据判断当前是否为GCF卡
输入参数  :pucATR   ATR输入数据指针
           ulATRLen ATR输入数据长度
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_COMM_IsGcfSim(
    VOS_UINT8                          *pucATR,
    VOS_UINT32                          ulATRLen
)
{
    VOS_UINT8                           aucAtrStub[2] = {0x3B, 0x00};
    OM_SIM_ATR_FLAG_STRU                stFlag;

    stFlag.ulSimAtrFlag = VOS_FALSE;

    /* 以下代码是GCF测试桩，仅NV项打开时并且ATR为3B 00时才需要，认为当前是SIM卡 */
    if (VOS_OK != NV_Read(en_NV_Item_Sim_ATR_Flag, &stFlag, sizeof(stFlag)))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == stFlag.ulSimAtrFlag)
    {
        return VOS_FALSE;
    }

    if (ulATRLen != sizeof(aucAtrStub))
    {
        return VOS_FALSE;
    }

    /*lint -e534*/
    if (VOS_OK == VOS_MemCmp(pucATR, aucAtrStub, sizeof(aucAtrStub)))
    {
        return VOS_TRUE;
    /*lint +e534*/
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_DecodeATR
功能描述  :解析ATR数据
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月13日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_COMM_DecodeATR(VOS_VOID)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulATRLen     = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN] = {0};
    VOS_UINT32                          ulHistoryLen;
    SCI_ATRINFO_S                       stSCIATRInfo;

    lSCIResult = mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATR, &stSCIATRInfo);

    if ((USIMM_SCI_SUCCESS != lSCIResult) || (ulATRLen > sizeof(aucATR)))
    {
        USIMM_ERROR_LOG("USIMM_COMM_DecodeATR:USIMMSCIGetATR get ATR Error");

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    if (VOS_OK != USIMM_DecideTMode(&stSCIATRInfo))
    {
        USIMM_ERROR_LOG("USIMM_COMM_DecodeATR:USIMM_DecideTMode Error");

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    USIMM_SciDataHook(ulATRLen, aucATR);

    /* 判断是否为GCF测试使用的SIM卡 */
    if (VOS_TRUE == USIMM_COMM_IsGcfSim(aucATR, ulATRLen))
    {
        USIMM_CCB_SetTestCardType(USIMM_TEST_TYPE_GCF_SIM);

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulHistoryLen = aucATR[USIMM_ATR_T0_OFFSET] & 0x0F;  /*获取ATR历史字节长度*/

    if (ulATRLen < (ulHistoryLen + 1))
    {
        USIMM_ERROR_LOG("USIMM_COMM_DecodeATR:USIM ATR Length Error");
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_GetMainAppType
功能描述  :完成卡初始化的主APP
输入参数  :无
输出参数  :无
返 回 值  :主通道index
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_CARDAPP_ENUM_UINT32 USIMM_COMM_GetMainAppType(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < USIMM_CARDAPP_BUTT; i++)
    {
        /* 找到主通道*/
        if (0 == USIMM_CCB_GetAppChNO(i))
        {
            return i;
        }
    }

    USIMM_ERROR_LOG("USIMM_COMM_GetMainAppType: No main application.");

    return USIMM_CARDAPP_BUTT;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_GetTerminalProfile
功能描述  :读取nv项当前终端参数设置
输入参数  :pstProfileContent
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_GetTerminalProfile(
    USIMM_STK_CFG_STRU                 *pstProfileContent
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUsimProfile[] = STK_USIM_PROFILE_DEFAULT;
    VOS_UINT8                           aucSimProfile[]  = STK_SIM_PROFILE_DEFAULT;

    /*读取NV项判断当前的SAT状态*/
    ulResult = NV_Read(en_NV_Item_TerminalProfile_Set, pstProfileContent, sizeof(USIMM_STK_CFG_STRU));

    if (NV_OK == ulResult)/*读取失败按照默认下发*/
    {
        return;
    }

    USIMM_WARNING_LOG("USIMM_COMM_GetTerminalProfile: NV_Read Failed");

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stUsimProfile.aucProfile, aucUsimProfile, sizeof(aucUsimProfile));
        /*lint +e534*/

        pstProfileContent->stUsimProfile.ucProfileLen = sizeof(aucUsimProfile);
    }
    else if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stSimProfile.aucProfile, aucSimProfile, sizeof(aucSimProfile));
        /*lint +e534*/

        pstProfileContent->stSimProfile.ucProfileLen = sizeof(aucSimProfile);
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_COMM_GetTerminalProfile: Card Type Failed");
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_InitPINApp
功能描述  :完成卡PIN初始化的主控函数
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_COMM_InitPINApp(VOS_VOID)
{
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRlst;

    enInitRlst = USIMM_COMM_InitCardApps();

    if (USIMM_COMM_INIT_RESET == enInitRlst)
    {
        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            enInitRlst = USIMM_UICC_InitCard();
        }
        else if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            enInitRlst = USIMM_ICC_InitCard();
        }
        else
        {
            USIMM_ERROR_LOG("USIMM_COMM_InitPINApp: Card Type Failed");
        }
    }

    if (USIMM_COMM_INIT_SUCC != enInitRlst)
    {
        USIMM_ERROR_LOG("USIMM_COMM_InitPINApp: Card Init Failed");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_InitCard
功能描述  :完成卡初始化的主控函数
输入参数  :pstMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_COMM_InitCard(
    USIMM_MsgBlock                     *pstMsg
)
{
    USIMM_COMMINIT_RST_ENUM_UINT32      enCommRslt;

    /* UICC卡初始化成功 */
    enCommRslt = USIMM_UICC_InitCard();

    /* UICC卡初始化成功 */
    if (USIMM_COMM_INIT_SUCC == enCommRslt)
    {
        USIMM_CCB_SetMainAppType(USIMM_COMM_GetMainAppType());

        return VOS_OK;
    }

    /* 卡不能使用 */
    if (USIMM_COMM_INIT_FATAL_FAIL == enCommRslt)
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

        USIMM_WARNING_LOG("USIMM_COMM_InitCard: Init card fail during UICC procedure.");

        return VOS_ERR;
    }

    USIMM_WARNING_LOG("USIMM_COMM_InitCard: Switch to ICC card.");

    USIMM_ResetGlobalVar();

    /* ICC卡初始化 */
    if (USIMM_COMM_INIT_SUCC == USIMM_ICC_InitCard())
    {
        USIMM_CCB_SetMainAppType(USIMM_COMM_GetMainAppType());

        return VOS_OK;
    }

    USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

    USIMM_WARNING_LOG("USIMM_COMM_InitCard: Init card fail during ICC procedure.");

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : USIMM_COMM_InitCardApps
功能描述  : 初始化当前卡的应用列表
输入参数  : 无
输出参数  : 无
返 回 值  : USIMM_COMMINIT_RST_ENUM_UINT32
修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_COMM_InitCardApps(VOS_VOID)
{
    VOS_UINT32                          ulAppNum;
    VOS_UINT32                          i;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enStepResult;
    USIMM_INITAPPS_RST_ENUM_UINT32      enAppResult;
    VOS_UINT32                          ulSuccessNum;

    ulAppNum = USIMM_COMM_GetAppInitFuncs();

    if (0 == ulAppNum)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulSuccessNum = 0;

    for (i = 0; i < ulAppNum; i++)
    {
        if ((USIMM_INITAPPS_FAIL == g_astUSIMMInitAppCtrl[i].enAppInitResult)
            ||(VOS_NULL_PTR == g_astUSIMMInitAppCtrl[i].pfList))
        {
            USIMM_WARNING_LOG("USIMM_COMM_InitCardApps: Jump Over a APP");

            continue;
        }

        if (USIMM_INITSTEPS_SUCCESS == g_astUSIMMInitAppCtrl[i].enAppStepResult)
        {
            (VOS_VOID)USIMM_COMM_InitAppState(g_astUSIMMInitAppCtrl[i].ucChannelNo);

            ulSuccessNum++;

            continue;
        }

        enStepResult = USIMM_INITSTEPS_SUCCESS;

        if (VOS_NULL_BYTE == g_astUSIMMInitAppCtrl[i].ucChannelNo)
        {
            if (ulSuccessNum != 0)
            {
                enStepResult = UISMM_UICC_InitCardOpenChannel(&g_astUSIMMInitAppCtrl[i]);
            }
            else
            {
                g_astUSIMMInitAppCtrl[i].ucChannelNo = 0;
            }
        }

        if (USIMM_INITSTEPS_SUCCESS == enStepResult)
        {
            enStepResult = USIMM_COMM_InitAppList(&g_astUSIMMInitAppCtrl[i]);
        }
        else
        {
            USIMM_WARNING_LOG("USIMM_COMM_InitCardApps: Open Channel is Fail");
        }

        g_astUSIMMInitAppCtrl[i].ucInitTimes++;

        enAppResult = USIMM_COMM_CheckInitStepResult(enStepResult, &g_astUSIMMInitAppCtrl[i]);

        g_astUSIMMInitAppCtrl[i].enAppInitResult = enAppResult;

        g_astUSIMMInitAppCtrl[i].enAppStepResult = enStepResult;

        if (USIMM_INITAPPS_SUCCESS == enAppResult)
        {
            ulSuccessNum++;
        }
        else
        {
            USIMM_COMM_ResetInitGlobal();

            /* 如果只有一个应用返回APP 初始化失败，切到ICC初始化 */
            if ((1 == ulAppNum)
             && (USIMM_INITAPPS_FAIL == enAppResult))
            {
                break;
            }
            else
            {
                return USIMM_COMM_INIT_RESET;
            }
        }
    }

    if (0 == ulSuccessNum)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  : USIMM_COMM_GetAppInitFuncs
功能描述  : 获取当前App初始化的函数
输入参数  : 无
输出参数  : 无
返 回 值  : 无
修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_COMM_GetAppInitFuncs(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        /* 找到空余位置 */
        if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[i].enAppType)
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
函 数 名  : USIMM_InitAppList
功能描述  : 执行当前需要初始化应用的某一个列表的具体内容
输入参数  : pstInitList: 当前应用的初始化列表内容
输出参数  : 无
返 回 值  : USIMM_INITSTEPS_RST_ENUM_UINT32
修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_InitAppList(
    USIMM_INITAPPSCTRL_STRU            *pstInitList
)
{
    VOS_UINT32                          i;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enResult;
    USIMM_INITAPPLIST_FUNC              *pStepList;

    pStepList = pstInitList->pfList;

    enResult = USIMM_INITSTEPS_SUCCESS;

    for (i = pstInitList->ucCurStep; i < pstInitList->ucInitListNum; i++)
    {
        if (pStepList[i].enStatus != USIMM_FUNC_AVAILABLE)
        {
            continue;
        }

        enResult = pStepList[i].pProcFun(pstInitList->ucChannelNo);

        if (USIMM_INITSTEPS_REMOVE == enResult)
        {
            pStepList[i].enStatus = USIMM_FUNC_UNAVAILABLE;
        }
        else if ((USIMM_INITSTEPS_SUSPEND == enResult)
              || (USIMM_INITSTEPS_FAIL == enResult))
        {
            break;
        }
        else if (USIMM_INITSTEPS_FAIL_REMOVE == enResult)
        {
            pStepList[i].enStatus = USIMM_FUNC_UNAVAILABLE;

            enResult = USIMM_INITSTEPS_FAIL;

            break;
        }
        else
        {
            continue;
        }
    }

    pstInitList->ucCurStep = (VOS_UINT8)i;

    return enResult;
}

/*****************************************************************************
函 数 名  : USIMM_CheckInitStepResult
功能描述  : 检查应用返回的结果
输入参数  : enResult: 输入初始化的过程的结果
            pstInitList: 应用初始化的控制信息
输出参数  : 无
返 回 值  : USIMM_INITAPPS_RST_ENUM_UINT32
修订记录  :
1. 日    期   : 2015-3-15
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITAPPS_RST_ENUM_UINT32 USIMM_COMM_CheckInitStepResult(
    USIMM_INITSTEPS_RST_ENUM_UINT32         enResult,
    USIMM_INITAPPSCTRL_STRU                *pstInitList
)
{
    switch (enResult)
    {
        case USIMM_INITSTEPS_SUCCESS:
            pstInitList->ucCurStep   = 0;
            pstInitList->ucInitTimes = 0;
            return USIMM_INITAPPS_SUCCESS;

        case USIMM_INITSTEPS_SUSPEND:
            pstInitList->ucInitTimes = 0;
            return USIMM_INITAPPS_SUCCESS;

        case USIMM_INITSTEPS_FAIL:
        case USIMM_INITSTEPS_FAIL_REMOVE:
            pstInitList->ucCurStep   = 0;

            if (pstInitList->ucInitTimes >= USIMM_INITAPPS_TIMES_MAX)
            {
                return USIMM_INITAPPS_FAIL;
            }
            else
            {
                return USIMM_INITAPPS_RESET;
            }

        default:
            return USIMM_INITAPPS_SUCCESS;
    }
}

/*****************************************************************************
函 数 名  :USIMM_COMM_AutoVerifyPIN
功能描述  :自动验证PIN
输入参数  :pstPIN1Info -- 当前PIN Info
输出参数  :pstPIN1Info -- 当前PIN Info
返 回 值  : VOS_OK/VOS_ERR
修订记录  :
1. 日    期    : 2015-3-10
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_AutoVerifyPIN(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_COMM_CARD_APP_INFO_STRU      *pstAppInfo;
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    VOS_UINT8                           ucPIN1No;

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    ucPIN1No = (VOS_UINT8)pstAppInfo->stPinInfo.enPinKeyRef;

    if ((ucPIN1No < 1)||(ucPIN1No > 8))
    {
        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByRef(ucPIN1No);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    if (VOS_NULL == pstPIN1Info->ucPINLen)  /*当前PIN码无效，需要上报卡状态*/
    {
        return USIMM_INITSTEPS_SUCCESS;
    }

    if ( (USIMM_PIN_ENABLED == pstPIN1Info->enPinEnable)
        &&(USIMM_PIN_NEED == pstPIN1Info->enPinVerified) )
    {
        USIMM_NORMAL_LOG("USIMM_COMM_AutoVerifyPIN: Need Verify The Pin");

        /* 成功校验过PIN码，则自动校验PIN码 */
        ulResult = USIMM_SendVerifyPinApdu(ucChannelNo,
                                           USIMM_PINCMD_VERIFY,
                                           pstPIN1Info->ucPINRefNum,
                                           pstPIN1Info->aucPin,
                                           &stRspData);

        if (VOS_OK != ulResult)/*检查结果*/
        {
            USIMM_ERROR_LOG("USIMM_COMM_AutoVerifyPIN: USIMM_PINVerify_APDU Error");

            return USIMM_INITSTEPS_FAIL;
        }

        pstPIN1Info->enPinVerified = USIMM_PIN_NONEED;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  : USIMM_COMM_InitAppState
功能描述  : 判断当前的应用状态
输入参数  : ucChannelNo 逻辑通道号
输出参数  : 无
返 回 值  : USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_InitAppState(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CARD_SERVIC_ENUM_UINT32       enProCardService;
    USIMM_COMM_CARD_APP_INFO_STRU      *pstAppInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    VOS_UINT8                           ucPIN1No;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enResult;

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    enProCardService = pstAppInfo->enAppService;    /*保存当前的卡状态*/

    ucPIN1No = (VOS_UINT8)pstAppInfo->stPinInfo.enPinKeyRef;

    if ((ucPIN1No < 1)||(ucPIN1No > 8))
    {
        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByRef(ucPIN1No);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    /*根据密码状态判断卡状态*/
    if (USIMM_PUK_BLOCK == pstPIN1Info->enPinVerified)/*判断PUK BLOCK状态*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: PUK is Block");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PUK;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_UNAVAILABLE;

        enResult                            = USIMM_INITSTEPS_SUSPEND;
    }
    else if(USIMM_PUK_NEED == pstPIN1Info->enPinVerified)/*判断PUK状态*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PUK Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PUK;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_SIM_PUK;

        enResult                            = USIMM_INITSTEPS_SUSPEND;
    }
    else if(USIMM_PIN_NEED == pstPIN1Info->enPinVerified) /*再判断当前PIN1状态*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PIN Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PIN;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_SIM_PIN;

        enResult                            = USIMM_INITSTEPS_SUSPEND;
    }
    else if(USIMM_PUK_NEED == pstAppInfo->stPinInfo.stPin2Info.enPinVerified)   /*再判断PUK2状态*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PUK2 Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PUK2;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_AVAILABLE;

        enResult                            = USIMM_INITSTEPS_SUCCESS;
    }
    else  /*再判断PIN2状态*/                                                                                  /*最后默认需要PIN2*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PIN2 Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PIN2;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_AVAILABLE;

        enResult                            = USIMM_INITSTEPS_SUCCESS;
    }

    if (enProCardService != pstAppInfo->enAppService )
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card State is Changed, Need Report the Card State");

        USIMM_CCB_SetAppStateChange(pstAppInfo->enAppType, USIMM_CARD_STATE_CHANGED);
    }

    return enResult;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_InitPINState
功能描述  :初始应用当前的PIN变量
输入参数  :pstPINInfo -- PIN信息
输出参数  :pstPINInfo -- PIN信息
返 回 值  :无

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_InitPINState(
    USIMM_APP_PIN_INFO_STRU            *pstPINInfo
)
{
    pstPINInfo->enPinVerified = USIMM_PIN_NONEED;

    if(USIMM_PIN_ENABLED == pstPINInfo->enPinEnable)
    {
        if (0 != pstPINInfo->ucPinRemainTime)
        {
            USIMM_NORMAL_LOG("USIMM_COMM_InitPINState: Set USIMM_PIN_NEED");

            pstPINInfo->enPinVerified = USIMM_PIN_NEED;
        }
    }

    if (0 == pstPINInfo->ucPinRemainTime)
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitPINState: Set USIMM_PUK_NEED");

        pstPINInfo->enPinVerified = USIMM_PUK_NEED;
    }

    if (0 == pstPINInfo->ucPukRemainTime)
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitPINState: Set USIMM_PUK_BLOCK");

        pstPINInfo->enPinVerified = USIMM_PUK_BLOCK;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_SaveDFPinInfo
功能描述  :保存应用ADF PIN码信息
输入参数  :enAppType 应用类型
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : ganlan
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_SaveDFPinInfo(
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    USIMM_DFFCP_ST                     *pstDFInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;

    pstDFInfo = USIMM_CCB_GetCurDFInfo(enAppType);

    if (VOS_NULL_PTR == pstDFInfo)
    {
        USIMM_ERROR_LOG("USIMM_COMM_SaveDFPinInfo: The DFInfo is Error");

        return;
    }

    /* 保存PIN1使用的KeyReference */
    USIMM_CCB_GetPINInfo(enAppType)->enPinKeyRef = pstDFInfo->ucPIN1RefNum;

    pstPin1Info = USIMM_CCB_GetPIN1InfoByRef(pstDFInfo->ucPIN1RefNum);

    if (VOS_NULL_PTR == pstPin1Info)
    {
        USIMM_ERROR_LOG("USIMM_COMM_SaveDFPinInfo: The pstPin1Info is Error");

        return;
    }

    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if (VOS_NULL_PTR == pstPin2Info)
    {
        USIMM_ERROR_LOG("USIMM_COMM_SaveDFPinInfo: The pstPin2Info is Error");

        return;
    }

    /* ICC的PIN码剩余信息存放在DF文件中 */
    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        pstPin1Info->ucPinRemainTime = pstDFInfo->stPINInfo.ucPin1RemainTime;  /* PIN1码剩余次数      */
        pstPin2Info->ucPinRemainTime = pstDFInfo->stPINInfo.ucPin2RemainTime;  /* PIN2码剩余次数      */
        pstPin1Info->ucPukRemainTime = pstDFInfo->stPINInfo.ucPuk1RemainTime;  /* PUK1码剩余次数     */
        pstPin2Info->ucPukRemainTime = pstDFInfo->stPINInfo.ucPuk2RemainTime;  /* PUK2码剩余次数     */
    }

    pstPin1Info->enPinEnable     = pstDFInfo->stPINInfo.enPin1Enable;           /* PIN1激活状态        */
    pstPin2Info->enPinEnable     = pstDFInfo->stPINInfo.enPin2Enable;           /* PIN2激活状态        */
    pstPin1Info->ucPINRefNum     = pstDFInfo->ucPIN1RefNum;
    pstPin2Info->ucPINRefNum     = pstDFInfo->ucPIN2RefNum;

    return;
}

/*****************************************************************************
函 数 名  : USIMM_COMM_StoreAppSN
功能描述  : 链路层判断当前处理命令类型
输入参数  : enAppType 应用类型
输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2015-3-10
   作    者   : ganlan
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_COMM_StoreAppSN(
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    VOS_UINT32                              i;

    /* 参数检测 */
    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        return;
    }

    /* UE不支持IMS则不初始化ISIM应用 */
#if (FEATURE_OFF == FEATURE_IMS)
    if (USIMM_IMS_APP == enAppType)
    {
        return;
    }
#endif

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
    /* UE不支持CDMA则不初始化CSIM或UIM应用 */
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
        if (USIMM_CDMA_APP == enAppType)
        {
            return;
        }
#endif
    }

    for (i = 0; i < ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        /* 已经有保存 */
        if (enAppType == g_astUSIMMInitAppCtrl[i].enAppType)
        {
            return;
        }

        /* 找到空余位置 */
        if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[i].enAppType)
        {
            g_astUSIMMInitAppCtrl[i].enAppType     = enAppType;
            g_astUSIMMInitAppCtrl[i].pfList        = USIMM_COMM_GetAppInitList(USIMM_CCB_GetCardType(),enAppType);
            g_astUSIMMInitAppCtrl[i].ucInitListNum = (VOS_UINT8)USIMM_COMM_GetAppInitNum(USIMM_CCB_GetCardType(),enAppType);

            return;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_IsAndroidPhone
功能描述  :初始USIM卡全局变量
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : ganlan
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_COMM_IsAndroidPhone(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU stSysAppCfg;

    /* 默认配置对接MP */
    stSysAppCfg.usSysAppConfigType = SYSTEM_APP_MP;

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stSysAppCfg, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_COMM_IsAndroidPhone: Read en_NV_Item_System_APP_Config Failed");
    }

    if (SYSTEM_APP_ANDROID == stSysAppCfg.usSysAppConfigType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  :USIMM_COMM_GetMecrpValue
功能描述  :获取NV中的定制值
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : 祝锂
   修改内容   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_COMM_GetMecrpValue(
    VOS_UINT8                           *pucSCM,
    VOS_UINT8                           *pucMOBP)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    CAS_1X_NVIM_CAPA_INFO_STRU          stNVInfo;

    if (NV_OK != NV_Read(en_NV_Item_CAS_1X_NVIM_CAPA_INFO, &stNVInfo, sizeof(CAS_1X_NVIM_CAPA_INFO_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_COMM_GetMecrpValue: NV_Read is Fail");

        return VOS_ERR;
    }

    *pucMOBP = stNVInfo.ucMobPRev;

    *pucSCM = (VOS_UINT8)(USIMM_CDMA_DEFAULT_SCM | (((VOS_UINT32)(stNVInfo.enSlottedClass))<< 5)
                        |(((VOS_UINT32)(stNVInfo.enSupportMeid)) << 4)
                        |(((VOS_UINT32)(stNVInfo.enTransMode))   << 2));
#endif

    return VOS_OK;
}


/*****************************************************************************
函 数 名  :USIMM_COMM_InitOPFile
功能描述  :初始USIM卡全局变量
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_InitOPFile(VOS_VOID)
{
    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        USIMM_UICC_ReadUsimOPFile();
    }
    else if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        USIMM_ICC_ReadSimOPFile();
    }
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitStoreEsnMeid
功能描述  :初始CSIM卡过程中MANAGE ESN MEID
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitStoreEsnMeid(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    USIMM_FEATURE_CFG_STRU              stUsimmFeatureCfg;
    USIMM_APDU_RSP_STRU                 stRspData = {0};
    VOS_UINT8                           aucEsnMeid[USIMM_STORE_ESNMEID_MAX];

    USIMM_NORMAL_LOG("USIMM_UICC_InitStoreEsnMeid: Step is Begin");

    (VOS_VOID)VOS_MemSet(&g_stStoreEsnMeidStatus, 0, sizeof(USIMM_STORE_ESN_MEID_STATUS_STRU));

    (VOS_VOID)VOS_MemSet(&stUsimmFeatureCfg, 0, sizeof(USIMM_FEATURE_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config, &stUsimmFeatureCfg, sizeof(USIMM_FEATURE_CFG_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitStoreEsnMeid: NV_Read en_NV_Item_USIMM_WRITE_MEID_PESN_TAG Failed");

        stUsimmFeatureCfg.unCfg.stFeatureCfg.bMeidPesnAPWriteEnable = VOS_FALSE;
    }

    if (VOS_TRUE == stUsimmFeatureCfg.unCfg.stFeatureCfg.bMeidPesnAPWriteEnable)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitStoreEsnMeid: Meid no need write to card");

        /* 产品线定制不需在卡初始化存卡则直接返回 */
        return USIMM_INITSTEPS_SUCCESS;
    }

    if (NV_OK != NV_Read(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitStoreEsnMeid: NV_Read en_NV_Item_MEID Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    aucEsnMeid[0] = MEID_NV_DATA_LEN_NEW;

    (VOS_VOID)VOS_MemCpy(aucEsnMeid + 1, stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

    ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_MEID_P1,
                                          ucChannelNo,
                                          aucEsnMeid,
                                          &stRspData);

    if (VOS_OK == ulResult)
    {
        g_stStoreEsnMeidStatus.ucStoreEsnMeidResult = stRspData.aucRsp[0];

        g_stStoreEsnMeidStatus.ucIsStoreEsnMeid     = VOS_TRUE;

        USIMM_NORMAL_LOG("USIMM_UICC_InitStoreEsnMeid: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    if (NV_OK != NV_Read(en_NV_Item_PESN, &stPEsn, sizeof(stPEsn)))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitStoreEsnMeid: NV_Read en_NV_Item_PESN Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    aucEsnMeid[0] = PESN_NV_DATA_LEN;

    (VOS_VOID)VOS_MemCpy(aucEsnMeid + 1, stPEsn.aucPEsn, PESN_NV_DATA_LEN);

    ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_ESN_P1,
                                          ucChannelNo,
                                          aucEsnMeid,
                                          &stRspData);

    if (VOS_OK == ulResult)
    {
        g_stStoreEsnMeidStatus.ucStoreEsnMeidResult = stRspData.aucRsp[0];

        g_stStoreEsnMeidStatus.ucIsStoreEsnMeid  = VOS_TRUE;

        USIMM_NORMAL_LOG("USIMM_UICC_InitStoreEsnMeid: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_ERROR_LOG("USIMM_UICC_InitStoreEsnMeid: Command Send error");

    /* 将此步骤移除，不重启卡 */
    return USIMM_INITSTEPS_REMOVE;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_DecodeAppAid
功能描述  :根据文件内容解析出应用AID
输入参数  :pucdata
     　    usFileLen
           ucRecordLen
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeAppAid(
    VOS_UINT8                          *pucdata,
    VOS_UINT16                          usFileLen,
    VOS_UINT8                           ucRecordLen
)
{
    USIMM_COMMINIT_RST_ENUM_UINT32      enResult;
    VOS_UINT32                          i;
    VOS_UINT32                          ulAidLen;
    VOS_UINT8                           aucUsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x02};
    VOS_UINT8                           aucIsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x04};
    VOS_UINT8                           aucCsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x03,0x43,0x10,0x02};
    USIMM_CARDAPP_ENUM_UINT32           enAppType = USIMM_UNLIMIT_APP_BUTT;

    enResult = USIMM_COMM_INIT_NORMAL_FAIL;

    for (i = 0; i < usFileLen; i += ucRecordLen)
    {
        if ((APP_TMP_TAG != pucdata[i + APP_TMP_TAG_OFFSET])
         || (APP_IND_TAG != pucdata[i + APP_IND_TAG_OFFSET]))    /*判断内容合法性*/
        {
            USIMM_WARNING_LOG("USIMM_UICC_DecodeAppAid: EFDIR Content not Right");/*打印错误*/

            continue;
        }

        ulAidLen = (pucdata[i + APP_AID_LEN_OFFSET] > USIMM_AID_LEN_MAX)?USIMM_AID_LEN_MAX:pucdata[i + APP_AID_LEN_OFFSET];

        /* 只要匹配到A0000000871002就认为找到了USIM的AID */
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucUsimRidAppCode, sizeof(aucUsimRidAppCode)))
        {
            enAppType = USIMM_GUTL_APP;
        /*lint +e534*/

            enResult = USIMM_COMM_INIT_SUCC;
        }

        /* 只要匹配到A0000000871004就认为找到了ISIM的AID,目前ISIM还不能单独支持 */
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucIsimRidAppCode, sizeof(aucIsimRidAppCode)))
        {
            enAppType = USIMM_IMS_APP;
        /*lint +e534*/

            enResult = USIMM_COMM_INIT_SUCC;
        }

        /* 只要匹配到A0000003431002就认为找到了CSIM的AID */
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucCsimRidAppCode, sizeof(aucCsimRidAppCode)))
        {
            enAppType = USIMM_CDMA_APP;
        /*lint +e534*/

            enResult = USIMM_COMM_INIT_SUCC;
        }

        USIMM_COMM_StoreAppSN(enAppType);

        /*保存相关信息*/
        USIMM_CCB_SetAIDByApp(enAppType, ulAidLen, &pucdata[i + APP_AID_VALUE_OFFSET]);

        enAppType = USIMM_UNLIMIT_APP_BUTT;
    }

    return enResult;
}

/*****************************************************************************
函 数 名  : USIMM_UICC_DecodeEFDIR
功能描述  : 解析EFDIR内容
输入参数  : 无
输出参数  : 无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月3日
    作    者   : g00256031
    修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeEFDIR(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                          *pucdata;
    USIMM_EFFCP_ST                     *pstCurEFInfo;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt = USIMM_COMM_INIT_FATAL_FAIL;

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_DIR_ID);

    if (VOS_OK != ulResult)/*选择文件*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: EFDIR could not Found");/*打印错误*/

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    pstCurEFInfo = USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO);

    if (VOS_NULL_PTR == pstCurEFInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: USIMM_CCB_GetCurEFInfo Error");/*打印错误*/

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    pucdata = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstCurEFInfo->usFileLen);

    if (VOS_NULL_PTR == pucdata)   /*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: VOS_MemAlloc Error");/*打印错误*/

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    if (USIMM_EFSTRUCTURE_FIXED == pstCurEFInfo->enFileType)
    {
        if (USIMM_SW_OK != USIMM_SendReadRecordApdu(USIMM_APDU_BASECHANNEL,
                                                    pstCurEFInfo->ucRecordNum,
                                                    pstCurEFInfo->ucRecordLen,
                                                    USIMM_READ_ALLRECORD,
                                                    pucdata))      /*读取记录内容*/
        {
            USIMM_INFO_LOG("USIMM_UICC_DecodeEFDIR: USIMM_ReadLFFile Error");
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: EFDIR File Type Error");/*打印错误*/

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucdata);
        /*lint +e534*/

        return USIMM_COMM_INIT_NORMAL_FAIL;                                              /*按照102.221 13.1 节不支持二进制格式文件*/
    }

    /* 根据文件内容解析出应用AID　*/
    enInitRslt = USIMM_UICC_DecodeAppAid(pucdata,
                                         pstCurEFInfo->usFileLen,
                                         pstCurEFInfo->ucRecordLen);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucdata);
    /*lint +e534*/

    /* 如果一个有效的AID都没有找到返回错误，切到SIM卡继续初始化 */
    if (USIMM_COMM_INIT_SUCC != enInitRslt)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    return USIMM_UICC_CUIMCheck();
}

/*****************************************************************************
函 数 名  : USIMM_UICC_CUIMCheck
功能描述  : 中电信或全网通版本检查函数
输入参数  : 无
输出参数  : 无
返 回 值  : USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年6月6日
    作    者   : h00300778
    修改内容   : Creat
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_CUIMCheck(VOS_VOID)
{
    USIMM_AID_INFO_STRU                *pstAidInfo;

    /* 如果是电信版本，CSIM+USIM时按有卡初始化，单USIM上报无卡，单CSIM时上报有卡 */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck)
    {
        pstAidInfo = USIMM_CCB_GetAIDByApp(USIMM_CDMA_APP);

        if (VOS_NULL_PTR == pstAidInfo)
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }

        if (VOS_NULL == pstAidInfo->ulAIDLen)
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_DecodeATRStep2
功能描述  :ATR解析第二步　
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32
修订记录  :

1. 日    期   : 2015年3月13日
    作    者   : g00256031
    修改内容   : Creat
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeATRStep2(VOS_VOID)
{
    VOS_UINT32                          ulATRLen                  = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN] = {0};
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulDataOffset;
    VOS_UINT32                          ulHistoryLen;
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    SCI_ATRINFO_S                       stSCIATRInfo;

    lSCIResult = mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATR, &stSCIATRInfo);

    if ((USIMM_SCI_SUCCESS != lSCIResult)
        || (ulATRLen > sizeof(aucATR)))
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeATRStep2:USIMMSCIGetATR get ATR Error");

        return USIMM_COMM_INIT_SUCC;
    }

    USIMM_SciDataHook(ulATRLen, aucATR);

    /* 获取ATR历史字节长度 */
    ulHistoryLen    = aucATR[USIMM_ATR_T0_OFFSET] & 0x0F;

    /* 获取ATR历史字节的起始位置 */
    if ((ulATRLen < ulHistoryLen) || (VOS_NULL == ulHistoryLen))
    {
        return USIMM_COMM_INIT_SUCC;
    }

    ulOffset        = ulATRLen - ulHistoryLen;

    /* 3G卡的历史字节 */
    if (CTLV_IND_TAG == aucATR[ulOffset])
    {
        ulOffset++; /* 指向后面的的一个Tag */

        if (ulOffset >= sizeof(aucATR))
        {
            return USIMM_COMM_INIT_SUCC;
        }

        ulHistoryLen--;

        /*解析卡能力字节*/
        ulResult = USIMM_FindTagInCTLV(&aucATR[ulOffset], CARD_CPB_TAG, ulHistoryLen);

        if (USIMM_TAGNOTFOUND != ulResult)
        {
            if (ulResult > ulHistoryLen)
            {
                return USIMM_COMM_INIT_SUCC;
            }

            ulDataOffset = ulResult + ulOffset;

            if (ulDataOffset >= sizeof(aucATR))
            {
                return USIMM_COMM_INIT_SUCC;
            }

            gstUSIMMBaseInfo.enSupportPath = USIMM_GetBitFromBuf(&aucATR[ulDataOffset], 6, sizeof(VOS_UINT8));

            gstUSIMMBaseInfo.enSupportSFI  = USIMM_GetBitFromBuf(&aucATR[ulDataOffset], 3, sizeof(VOS_UINT8));

            if (CARD_CPB3_TAG == aucATR[ulDataOffset-1])
            {
                if ((ulDataOffset + 1) >= sizeof(aucATR))
                {
                    return USIMM_COMM_INIT_SUCC;
                }

                gstUSIMMBaseInfo.enSupportChannel = (((aucATR[ulDataOffset+1]&0x10) != 0)?USIMM_SUPPORT_CHANNEL:USIMM_NOTSUPPORT_CHANNEL);
            }
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/********************************************************************
函 数 名  :USIMM_UICC_InitGlobalVar
功能描述  :UICC卡全局变量初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年03月13日
   作    者   : g00256031
   修改内容   : Creat
********************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitGlobalVar(VOS_VOID)
{
    USIMM_COMM_ResetPIN1Global();

    USIMM_PoolDelAll(); /*避免内存重复添加，先释放相关内存*/

    gstUSIMMBaseInfo.ucCLA      = USIMM_USIM_CLA;

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCardTypeByATR
功能描述  :复位卡初始化ATR
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年03月13日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitCardTypeByATR(VOS_VOID)
{
    VOS_UINT32                          ulErrlogNumber;
    OAM_MNTN_NO_SIM_CARD_EVENT_STRU     stNoSimCard;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt        = USIMM_COMM_INIT_FATAL_FAIL;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;
    VOS_UINT32                          ulResult          = VOS_ERR;

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCardTypeByATR: Reset Card is Failed");

        /* 因为双开双待所以高16位记录pid,低16位记录原来的id */
        ulErrlogNumber = WUEPS_PID_USIM;
        ulErrlogNumber <<= 16;
        ulErrlogNumber |= MNTN_OAM_NO_SIM_CARD_EVENT;

        if(VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber, (void *)&stNoSimCard, sizeof(OAM_MNTN_NO_SIM_CARD_EVENT_STRU)))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCardTypeByATR: Fail to record no SIM card in Errorlog file");
        }

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    enInitRslt = USIMM_COMM_DecodeATR(); /*判断卡类型*/

    if (USIMM_COMM_INIT_SUCC == enInitRslt)
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_UICC);
    }

    return enInitRslt;                  /*初始化第一步完成*/
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InsertCommFileToPool
功能描述  :将公共文件放入缓冲池
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g0256031
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InsertCommFileToPool(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);   /* 保正 MF 可以选到 */

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_MF_ID);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InsertCommFileToPool: Select MF is Failed");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulResult = USIMM_UsimVoltageSwitch(USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->ucCharaByte,
                                       &g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InsertCommFileToPool: Voltage Switch is Failed");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    USIMM_UsimTerminalCapability();

    /*初始化当前MF下的文件*/
    for (i = 0; i < USIMM_INITFIRST_FILENUM; i++)
    {
        ulResult = USIMM_InsertFileToPool(USIMM_UNLIMIT_AUTO, gausInitFileOne[i]);

        if (VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_WARNING_LOG("USIMM_UICC_InsertCommFileToPool: Select File under MF is Failed");
        }
    }

    USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_UICC);

    USIMM_INFO_LOG("USIMM_UICC_InsertCommFileToPool: Init Card File First Step 1 Finished");

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_ProfileDownload
功能描述  :UICC卡终端能力参数下发
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015-3-10
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_ProfileDownload(VOS_VOID)
{
    USIMM_STK_CFG_STRU                  stProfileContent;

    USIMM_COMM_GetTerminalProfile(&stProfileContent);

    if (VOS_OK != USIMM_SendTermimalProfileDownloadApdu(stProfileContent.stUsimProfile.ucProfileLen,
                                             stProfileContent.stUsimProfile.aucProfile))
    {
         USIMM_ERROR_LOG("USIMM_UICC_ProfileDownload: USIMM_SendTermimalProfileDownloadApdu Error");

        return USIMM_COMM_INIT_REMOVE_RESET;
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCard
功能描述  :完成UICC卡初始化的主控函数
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitCard(VOS_VOID)
{
    VOS_UINT32                          ulStep;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt = USIMM_COMM_INIT_FATAL_FAIL;

    /* UICC卡初始化 */
    for (ulStep = 0; ulStep < ARRAYSIZE(g_aUICCCommInitProcFuncTbl); ulStep++)
    {
        if (USIMM_FUNC_UNAVAILABLE == g_aUICCCommInitProcFuncTbl[ulStep].enStatus)
        {
            enInitRslt  = USIMM_COMM_INIT_NORMAL_FAIL;

            continue;
        }

        enInitRslt = g_aUICCCommInitProcFuncTbl[ulStep].pProcFun();

        /* 初始化失败直接返回 */
        if (USIMM_COMM_INIT_FATAL_FAIL == enInitRslt)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCard: USIMM_COMM_INIT_FATAL_FAIL");

            break;
        }

        /* 需要重启后再次初始化 */
        if (USIMM_COMM_INIT_RESET == enInitRslt)
        {
            ulStep = VOS_NULL_DWORD;

            continue;
        }

        if (USIMM_COMM_INIT_REMOVE_RESET == enInitRslt)
        {
            g_aUICCCommInitProcFuncTbl[ulStep].enStatus = USIMM_FUNC_UNAVAILABLE;
            ulStep = VOS_NULL_DWORD;

            continue;
        }

        /* 需要切换到ICC卡初始化 */
        if (USIMM_COMM_INIT_NORMAL_FAIL == enInitRslt)
        {
            break;
        }
    }

    return enInitRslt;
}

/*****************************************************************************
函 数 名  : USIMM_UICC_SortAppSN
功能描述  : 将应用的初始化序列排序
输入参数  : 无
输出参数  : 无
返 回 值  : USIMM_COMMINIT_RST_ENUM_UINT32
调用函数  : 无

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g00256031
   修改内容   : Creat
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_SortAppSN(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    USIMM_APP_PRIORITY_CONFIG_STRU      stPrioCfg;
    USIMM_INITAPPSCTRL_STRU             stAppCtrlItem;

    if (NV_OK != NV_Read(en_NV_Item_Usim_App_Priority_Cfg,
                         (VOS_VOID*)&stPrioCfg, sizeof(stPrioCfg)))
    {
        return USIMM_COMM_INIT_SUCC;
    }

    /* 通过NV项值对g_astUICCAppArray进行排序 */
    for (i = stPrioCfg.ucAppNum; i > 0; i--)
    {
        for (j = 0; j < ARRAYSIZE(g_astUSIMMInitAppCtrl); j++)
        {
            /* 找到空余位置 */
            if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[j].enAppType)
            {
                break;
            }

            /* 找到相同则提到最前面 */
            if (stPrioCfg.aenAppList[i - 1] == g_astUSIMMInitAppCtrl[j].enAppType)
            {
                stAppCtrlItem = g_astUSIMMInitAppCtrl[j];
                /*lint -e534*/
                VOS_MemMove(&g_astUSIMMInitAppCtrl[1], &g_astUSIMMInitAppCtrl[0], j*sizeof(g_astUSIMMInitAppCtrl[j]));
                /*lint +e534*/
                g_astUSIMMInitAppCtrl[0] = stAppCtrlItem;
            }
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_CheckCSIM
功能描述  :检查CSIM的状态
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年10月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_CheckCSIM(VOS_VOID)
{
    USIMM_CARD_SERVIC_ENUM_UINT32                enCsimStatus;

    enCsimStatus = USIMM_CCB_GetAppService(USIMM_CDMA_APP);

    if ((VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck)
        &&(USIMM_CARD_SERVIC_ABSENT == enCsimStatus))
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_ActiveADFAll
功能描述  :初始化之后根据NV控制打开所有逻辑通道并激活AID,失败返回错误
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年10月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_ActiveADFAll(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    USIMM_AID_INFO_STRU                *pstAIDInfo;

    USIMM_INFO_LOG("USIMM_UICC_ActiveADFAll: Step is Begin");

    if (VOS_TRUE != g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulADFActiveAll)
    {
        USIMM_INFO_LOG("USIMM_UICC_ActiveADFAll: Feature is Off, Step is Over");

        return USIMM_COMM_INIT_SUCC;
    }

    /*从逻辑通道1开始*/
    for (i=1; i<ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        /* 找到空余位置 */
        if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[i].enAppType)
        {
            ulResult = VOS_OK;

            break;
        }

        ulResult = UISMM_UICC_InitCardOpenChannel(&g_astUSIMMInitAppCtrl[i]);

        if (USIMM_INITSTEPS_SUCCESS != ulResult)
        {
            ulResult = VOS_ERR;

            USIMM_ERROR_LOG("USIMM_UICC_ActiveADFAll: UISMM_UICC_InitCardOpenChannel Error");

            break;
        }

        pstAIDInfo = USIMM_CCB_GetAIDByApp(g_astUSIMMInitAppCtrl[i].enAppType);

        if (VOS_NULL_PTR == pstAIDInfo)
        {
            USIMM_ERROR_LOG("USIMM_UICC_ActiveADFAll: AID Len Error");

            ulResult = VOS_ERR;

            break;
        }

        ulResult = USIMM_SelectAIDFile(g_astUSIMMInitAppCtrl[i].ucChannelNo,
                                       USIMM_SELECT_RETURN_FCP_TEMPLATE,
                                       pstAIDInfo,
                                       &stApduRsp);

        if (USIMM_SW_OK != ulResult)
        {
            ulResult = VOS_ERR;

            USIMM_ERROR_LOG("USIMM_UICC_ActiveADFAll: USIMM_SelectAIDFile Error");

            break;
        }
    }

    if (VOS_OK != ulResult)
    {
        USIMM_COMM_ResetInitGlobal();

        g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulADFActiveAll = VOS_FALSE;

        USIMM_INFO_LOG("USIMM_UICC_ActiveADFAll: Find some error, Feature is Off, Step is Remove");

        return USIMM_COMM_INIT_REMOVE_RESET;
    }
    else
    {
        USIMM_INFO_LOG("USIMM_UICC_ActiveADFAll: Success, Step is Over");

        return USIMM_COMM_INIT_SUCC;
    }
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitADFInfo
功能描述  :初始化之后UICC的选择ADF的通用函数
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年10月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_UICC_InitADFInfo(
    VOS_UINT8                           ucChannelNo,
    USIMM_CARDAPP_ENUM_UINT32           enAppType
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucADF[] = {0x7F, 0xFF};
    USIMM_APDU_RSP_STRU                 stApduRsp;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_AID_INFO_STRU                 *pstAIDInfo;
    USIMM_CURFILEINFO_ST                *pstCurFileInfo;

    pstAIDInfo = USIMM_CCB_GetAIDByApp(enAppType);

    if (VOS_NULL_PTR == pstAIDInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitADFInfo: AID Len Error");

        return VOS_ERR;
    }

    pstCurFileInfo = USIMM_CCB_GetCurFileInfo(enAppType);

    if (VOS_NULL_PTR == pstCurFileInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitADFInfo: USIMM_CCB_GetCurFileInfo Error");

        return VOS_ERR;
    }

    if ((VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulADFActiveAll)
        &&(0 != ucChannelNo))
    {
        stApduHead.ucChannel    = ucChannelNo;
        stApduHead.ucINS        = CMD_INS_SELECT;
        stApduHead.ucP1         = USIMM_SELECT_BY_FILE_ID;
        stApduHead.ucP2         = USIMM_SELECT_RETURN_FCP_TEMPLATE;
        stApduHead.ucP3         = (VOS_UINT8)sizeof(aucADF);

        stApduData.ulDataLen    = sizeof(aucADF);
        stApduData.pucData      = aucADF;

        /*保存FCP返回的数据长度和内容，如果失败，会自动清空为0*/
        ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                        &stApduHead,
                                        &stApduData,
                                        &stApduRsp);    
    }
    else
    {
        ulResult = USIMM_SelectAIDFile(ucChannelNo,
                                       USIMM_SELECT_RETURN_FCP_TEMPLATE,
                                       pstAIDInfo,
                                       &stApduRsp);
	}

    if(USIMM_SW_OK == ulResult) /*判断AID选择结果*/
    {
        USIMM_ClearCurEFInfo(pstCurFileInfo);/*选中DF文件后，上次选中的EF文件置为无效值*/

        USIMM_NORMAL_LOG("USIMM_UICC_InitADFInfo: Select AID is Success");

        ulResult = USIMM_DecodeDFFcp(USIMM_PHYCARD_TYPE_UICC, &stApduRsp, pstCurFileInfo);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitADFInfo: Select File Error");/*打印错误*/

        ulResult = VOS_ERR;
    }

    if (USIMM_SW_OK == ulResult)
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitIsimSimuState
功能描述  :初始ISIM的模拟状态
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : g00256031
    修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitIsimSimuState(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_USIMSUPIMS_STRU               stUsimSupIms;

    if (USIMM_CARD_SERVIC_ABSENT != USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_CCB_SetUsimSimulateIsimStatus(VOS_FALSE);

        return USIMM_COMM_INIT_SUCC;
    }

    /* 通过NV判断usim是否支持IMS,默认支持 */
    ulResult = NV_Read(en_NV_Item_Usim_Support_Ims, &stUsimSupIms, sizeof(USIMM_USIMSUPIMS_STRU));

    if ((NV_OK == ulResult)
     && (PS_USIM_SERVICE_AVAILIABLE == stUsimSupIms.ulUsimSupImsEnable))/*读取失败按照默认下发*/
    {
        USIMM_CCB_SetUsimSimulateIsimStatus(VOS_TRUE);
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  : UISMM_UICC_InitCardOpenChannel
功能描述  : 打开逻辑通道，并且在初始化的变量中记录结果
输入参数  : pstInitList:应用初始化控制参数
输出参数  : 无
返 回 值  : USIMM_INITAPPS_RST_ENUM_UINT32
修订记录  :
1. 日    期   : 2015-3-18
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 UISMM_UICC_InitCardOpenChannel(
    USIMM_INITAPPSCTRL_STRU            *pstInitList
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelNo;

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        pstInitList->ucChannelNo = 0;

        return USIMM_INITSTEPS_SUCCESS;
    }

    /* 下发manage打开逻辑通道,打开通道的时候在基本逻辑通道上，因此P2参数为0,P3参数填1，期望带回一个字节的channelID */
    ulResult = USIMM_SendOpenChannelApdu(&ucChannelNo);

    if (ulResult != USIMM_SW_OK)
    {
        USIMM_ERROR_LOG("UISMM_UICC_InitCardOpenChannel: USIMM_CheckSW Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    pstInitList->ucChannelNo = ucChannelNo;

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitPINRemainTime
功能描述  :获取当前的PIN剩余次数
输入参数  :ucPINNo   :当前PIN的索引号
输出参数  :pucPINTime:PIN剩余次数
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_VerifyPIN_APDU
修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UICC_InitPINRemainTime(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPINNo,
    VOS_UINT8                          *pucPINTime
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;

    if (VOS_NULL_PTR == pucPINTime)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINRemainTime: Input Para Error");

        return VOS_ERR;
    }

    ulResult = USIMM_SendVerifyPinApdu(ucChannelID, CMD_INS_VERIFY, ucPINNo, VOS_NULL_PTR, &stRspData);

    if ((USIMM_SW_PIN_BLOCK != ulResult)&&(USIMM_SW_CMD_REMAINTIME != ulResult))/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINRemainTime: USIMM_PINVerify_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == stRspData.ucSW1)
    {
        *pucPINTime = stRspData.ucSW2&0x0F;
    }
    else
    {
        *pucPINTime = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitPUKRemainTime
功能描述  :获取当前的PUK的剩余次数
输入参数  :ucPINNo :PUK对应的PIN的索引号
输出参数  :pucPUKTime: PUK剩余次数
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UICC_InitPUKRemainTime(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPINNo,
    VOS_UINT8                          *pucPUKTime
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;

    if (VOS_NULL_PTR == pucPUKTime)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPUKRemainTime: Input Para Error");

        return VOS_ERR;
    }

    ulResult = USIMM_SendUnblockPinApdu(ucChannelID, ucPINNo, VOS_NULL_PTR, VOS_NULL_PTR, &stRspData);

	if ((USIMM_SW_ERR == ulResult)||(USIMM_SW_SENDCMD_ERROR == ulResult))/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPUKRemainTime: USIMM_UnblockPIN_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == stRspData.ucSW1)
    {
        *pucPUKTime = stRspData.ucSW2&0x0F;
    }
    else
    {
        *pucPUKTime = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimGlobal
功能描述  :初始USIM卡全局变量
输入参数  :ucChannelNo
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(ucChannelNo, USIMM_GUTL_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimADF
功能描述  :初始USIM卡ADF
输入参数  :ucChannelNo
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimADF: Step is Begin");

    ulResult = USIMM_UICC_InitADFInfo(ucChannelNo, USIMM_GUTL_APP);

    if (VOS_OK == ulResult)
    {
        USIMM_CCB_GetCurFileInfo(USIMM_GUTL_APP)->usCurDFID = ADF;

        USIMM_COMM_SaveDFPinInfo(USIMM_GUTL_APP);

        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimADF: Decode AID is Success");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimADF: Select AID is Error");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitPINTime
功能描述  :初始USIM卡PIN的剩余次数
输入参数  :ucChannelNo:通道号
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitPINTime(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_COMM_CARD_APP_INFO_STRU      *pstAppInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPIN2Info;
    VOS_UINT8                           ucPIN1No;
    VOS_UINT8                           ucPIN2No;

    USIMM_NORMAL_LOG("USIMM_UICC_InitPINTime: Step is Begin");

    /*初始化pIN1的相关信息*/
    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: App Info is NULL");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    ucPIN1No = (VOS_UINT8)pstAppInfo->stPinInfo.enPinKeyRef;

    /*检查PIN1的合法范围*/
    if ((ucPIN1No < 1)||(ucPIN1No > 8))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: PIN Ref Info is Wrong");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByRef(ucPIN1No);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PIN Info is Fail");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    /*获取PIN1的剩余次数*/
    if (VOS_OK != USIMM_UICC_InitPINRemainTime(ucChannelNo, ucPIN1No, &pstPIN1Info->ucPinRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PIN1 Times is Wrong");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    /*获取PUK1的剩余次数*/
    if (VOS_OK != USIMM_UICC_InitPUKRemainTime(ucChannelNo, ucPIN1No, &pstPIN1Info->ucPukRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PUK1 Times is Wrong");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    /*获取PIN2的信息*/
    pstPIN2Info = &pstAppInfo->stPinInfo.stPin2Info;

    ucPIN2No = pstPIN2Info->ucPINRefNum;

    /*获取PIN2的范围*/
    if ((ucPIN2No < 0x81)||(ucPIN2No > 0x88))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: PIN2 Ref Info is Wrong");/*打印错误*/

        pstPIN2Info->ucPinRemainTime = 0;

        pstPIN2Info->ucPukRemainTime = 0;

        return USIMM_INITSTEPS_SUCCESS;
    }

    /*获取PIN2的剩余次数*/
    if (VOS_OK != USIMM_UICC_InitPINRemainTime(ucChannelNo, ucPIN2No, &pstPIN2Info->ucPinRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PIN2 Times is Wrong");/*打印错误*/

        pstPIN2Info->ucPinRemainTime = 0;

        return USIMM_INITSTEPS_SUCCESS;
    }

    /*获取PUk2的剩余次数*/
    if (VOS_OK != USIMM_UICC_InitPUKRemainTime(ucChannelNo, ucPIN2No, &pstPIN2Info->ucPukRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PUK2 Times is Wrong");/*打印错误*/

        pstPIN2Info->ucPukRemainTime = 0;

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_COMM_InitPINState(pstPIN1Info);

    USIMM_COMM_InitPINState(pstPIN2Info);

    USIMM_NORMAL_LOG("USIMM_UICC_InitPINTime: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimECC
功能描述  :初始USIM卡ECC信息
输入参数  :ucChannelNo 逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimECC(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimECC: Step is Begin");

    ulResult = USIMM_InitUsimEccFile();

    if (VOS_OK == ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimECC: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_ERROR_LOG("USIMM_UICC_InitUsimECC: Step is Fail");

    return USIMM_INITSTEPS_REMOVE;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimEFLI
功能描述  :初始USIM卡文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimEFLI(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           *pucData;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimEFLI: Step is Begin");

    ulResult = USIMM_GetDefTFMem(USIMM_GUTL_APP, USIMM_USIM_EFLI_ID, &usDataLen, &pucData);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimEFLI: Step is Fail");

        return USIMM_INITSTEPS_REMOVE;
    }
    else
    {
        (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, pucData);

        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimEFLI: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimATT
功能描述  :初始USIM卡ATT定制步骤
输入参数  :ucChannelNo   逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimATT(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimATT: Step is Begin");

    /* ATT定制过程，失败了也不处理，继续初始化 */
    /* 仅当是USIM时选择AID，确保可以选中6FD2文件 */
    USIMM_AttUpdataSupportTable(ucChannelNo);

    /* 判断AT&T定制是否打开 */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimATT: Step is no need");

        return USIMM_INITSTEPS_SUCCESS;
    }

    for (i = 0;i < ARRAYSIZE(g_aulAttUsimInitFile); i++ )
    {
        (VOS_VOID)USIMM_InsertFileToPool(USIMM_GUTL_APP, g_aulAttUsimInitFile[i]);
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimATT: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimFBDNStatus
功能描述  :初始化USIM卡当前的FDN/BDN状态　
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_InitUsimFBDNStatus(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucData;
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus;
    USIMM_BDNSTATUS_ENUM_UINT32         enBDNStatus;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Step is Begin");

    ulResult = USIMM_GetTFByDefFID(USIMM_GUTL_APP, USIMM_USIM_EFEST_ID, sizeof(ucData), &ucData);

    if(VOS_OK == ulResult) /*该文件的存在不是必须的*/
    {
        /*判断内容初始化对应的全局变量*/
        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_FDN))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Set FDN by File Data");

            enFDNStatus = (ucData&0x01)?USIMM_FDNSTATUS_ON:USIMM_FDNSTATUS_OFF;

            USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, enFDNStatus);
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: FDN Service is OFF");

            USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, USIMM_FDNSTATUS_OFF);
        }

        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_BDN))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Set BDN by File Data");

            enBDNStatus = (ucData&0x02)?USIMM_BDNSTATUS_ON:USIMM_BDNSTATUS_OFF;

            USIMM_CCB_SetAppBDN(USIMM_GUTL_APP, enBDNStatus);
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: BDN Service is OFF");

            USIMM_CCB_SetAppBDN(USIMM_GUTL_APP, USIMM_BDNSTATUS_OFF);
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimFBDNStatus: Get EF EST Error");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Step is Over");

    return ;
}

/*****************************************************************************
函 数 名  : USIMM_UICC_InitUsimMFile
功能描述  : 初始USIM卡必选文件，失败会引起应用不可用
输入参数  : ucChannelNO  逻辑通道号
输出参数  : 无
返 回 值  : USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    VOS_UINT16                          ausUsimInitMFile[] = {USIMM_USIM_EFIMSI_ID,
                                                              USIMM_USIM_EFAD_ID};

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile: Step is Begin");

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;

    ulResult = USIMM_InsertFileToPool(USIMM_GUTL_APP, USIMM_USIM_EFUST_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimMFile: Read EFUST File Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_UICC_InitUsimFBDNStatus();

    for(i = 0;i < ARRAYSIZE(ausUsimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausUsimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitUsimMFile:Read Mandatory File Failed");

            return USIMM_INITSTEPS_FAIL;
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimMFile2
功能描述  :初始USIM卡其他必选文件，失败可以跳过
输入参数  :ucChannelNo   逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausUsimInitMFile[] = {USIMM_USIM_EFNETPAR_ID,
                                                              USIMM_USIM_EFHPPLMN_ID,
                                                              USIMM_USIM_EFLOCI_ID,
                                                              USIMM_USIM_EFACC_ID,
                                                              USIMM_USIM_EFPSLOCI_ID,
                                                              USIMM_USIM_EFKEYS_ID,
                                                              USIMM_USIM_EFKEYSPS_ID,
                                                              USIMM_USIM_EFFPLMN_ID,
                                                              USIMM_USIM_EFSTART_HFN_ID,
                                                              USIMM_USIM_EFTHRESHOL_ID};

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile2: Step is Begin");

    for(i = 0;i < ARRAYSIZE(ausUsimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausUsimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitUsimMFile2:Read Mandatory File Failed");

            continue;
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimFinish
功能描述  :初始USIM卡结束
输入参数  : ucChannelNo
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFinish: Step is Begin");

    if (USIMM_SW_OK != USIMM_SendStatusApdu(ucChannelNo,
                                        USIMM_STATUS_CURAPP_INITIALIZED,
                                        USIMM_STATUS_NO_DATA_RETURNED,
                                        0x00))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimFinish: USIMM_Status_APDU is Fail");
    }

    USIMM_SetAccFileAccess();

	USIMM_SetImsiFile();

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_ReadUsimOPFile
功能描述  :初始USIM卡可选文件
输入参数  :无
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_ReadUsimOPFile(VOS_VOID)
{
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimOPFile: Step is Begin");

    for (i =  0; i < ARRAYSIZE(gastUsimInitOFile); i++)
    {
        if (UICC_SVR_NONE != gastUsimInitOFile[i].ulService)
        {
            if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(gastUsimInitOFile[i].ulService))
            {
                continue;
            }
        }

        if (VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, gastUsimInitOFile[i].enDefFileID))
        {
            USIMM_WARNING_LOG("USIMM_UICC_ReadUsimOPFile: Read Optional File Failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_ReadUsimOPFile: Step is OK");

    return;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitUsimOPFile
功能描述  :初始USIM卡可选文件
输入参数  :ucChannelNo    逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimOPFile: Step is Begin");

    if (VOS_FALSE == USIMM_COMM_IsAndroidPhone())
    {
        /*lint -e534*/
        USIMM_SendInitCardMsg(WUEPS_PID_USIM, USIMM_INITCONTINUE_REQ);
        /*lint +e534*/
    }
    else
    {
        USIMM_UICC_ReadUsimOPFile();
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimOPFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimGlobal
功能描述  :初始CSIM卡全局变量
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(ucChannelNo, USIMM_CDMA_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimADF
功能描述  :初始CSIM卡应用信息
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimADF: Step is Begin");

    ulResult = USIMM_UICC_InitADFInfo(ucChannelNo, USIMM_CDMA_APP);

    if (VOS_OK == ulResult)
    {
        USIMM_CCB_GetCurFileInfo(USIMM_CDMA_APP)->usCurDFID = ADF;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucCharaByte = USIMM_CCB_GetCurDFInfo(USIMM_CDMA_APP)->ucCharaByte;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucSupCmd    = USIMM_CCB_GetCurDFInfo(USIMM_CDMA_APP)->ucSupCmd;

        USIMM_COMM_SaveDFPinInfo(USIMM_CDMA_APP);

        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimADF: Decode AID is Success");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCsimADF: Select AID is Error");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }
}

/*****************************************************************************
函 数 名  :UICC_InitCUIMEccFile
功能描述  :完成卡初始化类型判断函数
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2014年7月1日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_InitCUIMEccFile(VOS_VOID)
{
    VOS_UINT16              usDataLen;
    VOS_UINT8               *pucData;

    if (VOS_OK != USIMM_GetDefTFMem(USIMM_CDMA_APP, USIMM_CSIM_EFECC_ID, &usDataLen, &pucData))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCUIMEccFile:USIMM_UICC_InitCUIMTFileContent err");

        return ;
    }

    /* 上报当前的Ecc号码内容 */
    USIMM_XeccNumberInd(usDataLen, pucData);

    if (VOS_NULL_PTR != pucData)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucData);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimECC
功能描述  :初始CSIM卡紧急呼叫号码
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimECC(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimECC: Step is Begin");

    USIMM_UICC_InitCUIMEccFile();

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimECC: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :UICC_InitCSIMEstFile
功能描述  :完成卡初始化类型判断函数
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2014年7月1日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_InitCSIMEstFile(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucData;
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus;

    USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: Step is Begin");

    ulResult = USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFEST_ID);

    if(VOS_OK == ulResult) /*该文件的存在不是必须的*/
    {
        ulResult = USIMM_PoolReadOneFile(EF_CSIM_EST, sizeof(ucData), &ucData, USIMM_CDMA_APP);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCSIMEstFile: Get EF EST Error");
            return;
        }

        /*判断内容初始化对应的全局变量*/
        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(CSIM_SVR_FDN))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: Set FDN by File Data");

            enFDNStatus = (ucData&0x01)?USIMM_FDNSTATUS_ON:USIMM_FDNSTATUS_OFF;

            USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, enFDNStatus);
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: FDN Service is OFF");

            USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, USIMM_FDNSTATUS_OFF);
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCSIMEstFile: USIMM_InsertFileToPool EF EST Error");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: Step is Over");

    return ;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimFDNStatus
功能描述  :初始化CSIM卡当前的FDN/BDN状态　
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_InitCsimFDNStatus(VOS_VOID)
{
    VOS_UINT16                          ausCsimFdnFile[] = {USIMM_CSIM_EFIMSIM_ID,
                                                            USIMM_CSIM_EFIMSIT_ID,
                                                            USIMM_CSIM_EFTMSI_ID };
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    for (i=0; i<ARRAYSIZE(ausCsimFdnFile); i++)
    {
        /*Selct IMSI_M, IMSI_T, TMSI*/
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, ausCsimFdnFile[i]);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCsimFDNStatus: One Mandory file is absent");

            continue;
        }

        if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCsimFDNStatus: One file is deactive");
        }
    }

    return ;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimMFile
功能描述  :初始USIM卡必选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile: Step is Begin");

    /*Read EF AD*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFAD_ID);

    /*Save EF CST*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFCSIMST_ID);

    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFIMSIM_ID);

    /*Read EF EST*/
    USIMM_UICC_InitCSIMEstFile();

    USIMM_UICC_InitCsimFDNStatus();

    /*Read UIMID*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFRUIMID_ID);

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimMFile2
功能描述  :初始CSIM卡其他必选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausCsimInitMFile[] = {USIMM_CSIM_EFUSGIND_ID,
                                                              USIMM_CSIM_EFSP_ID,
                                                              USIMM_CSIM_EFIMSIT_ID,
                                                              USIMM_CSIM_EFACCOLC_ID,
                                                              /*USIMM_CSIM_EFPRL_ID,
                                                              USIMM_CSIM_EFEPRL_ID,*/
                                                              USIMM_CSIM_EFMAXPRL_ID,
                                                              USIMM_CSIM_EFTMSI_ID,
                                                              };
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile2: Step is Begin");

    for(i = 0;i < ARRAYSIZE(ausCsimInitMFile); i++ )
    {
        if (VOS_OK != USIMM_InsertFileToPool(USIMM_CDMA_APP,ausCsimInitMFile[i]))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile2: File read failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimEFMecrp
功能描述  :初始UIM卡过程中个更新文件EF MECRP
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimEFMecrp(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUpdate[3] = {0};

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP,
                                           USIMM_NEED_FCP,
                                           USIMM_CSIM_EFMECRP_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Select File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_COMM_GetMecrpValue(&aucUpdate[0], &aucUpdate[1]);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: USIMM_COMM_GetMecrpValue is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_SendUpdateBinaryApdu(ucChannelNo, sizeof(aucUpdate), aucUpdate);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Update is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimEF3gpd
功能描述  :初始CSIM卡过程中个更新文件EF ME3GPDOOPC
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimEF3gpd(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulSIPStatus;
    VOS_UINT32                          ulMIPStatus;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucFileData;

    ulSIPStatus = USIMM_IsServiceAvailable(CSIM_SVR_3GPD_SIP);

    ulMIPStatus = USIMM_IsServiceAvailable(CSIM_SVR_3GPD_MIP);

    if (  (PS_USIM_SERVICE_NOT_AVAILIABLE == ulSIPStatus)
        &&(PS_USIM_SERVICE_NOT_AVAILIABLE == ulMIPStatus))
    {
        USIMM_WARNING_LOG("USIMM_UICC_InitCsimEF3gpd: Service is Close");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP,
                                           USIMM_NEED_FCP,
                                           USIMM_CSIM_EFME3GPDOPC_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEF3gpd: Select File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ucFileData = (VOS_UINT8)(USIMM_CDMA_3GPD_SIMPLEIP);

    ulResult = USIMM_SendUpdateBinaryApdu(ucChannelNo, sizeof(ucFileData), &ucFileData);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEF3gpd: Update File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimFinish
功能描述  :初始USIM卡初始化完成
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimFinish: Step is Begin");

    if (USIMM_SW_OK != USIMM_SendStatusApdu(ucChannelNo,
                                            USIMM_STATUS_CURAPP_INITIALIZED,
                                            USIMM_STATUS_NO_DATA_RETURNED,
                                            0x00))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCsimFinish: USIMM_Status_APDU is Fail");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitVIACsimFinish
功能描述  :初始拼片CSIM卡初始化完成
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitVIACsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitVIACsimFinish: Step is Begin");

    USIMM_NORMAL_LOG("USIMM_UICC_InitVIACsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitCsimOPFile
功能描述  :初始USIM卡可选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitIsimGlobal
功能描述  :初始ISIM卡全局变量
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月27日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(ucChannelNo, USIMM_IMS_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitIsimADF
功能描述  :初始CSIM卡应用信息
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月27日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimADF: Step is Begin");

    ulResult = USIMM_UICC_InitADFInfo(ucChannelNo, USIMM_IMS_APP);

    if (VOS_OK == ulResult)
    {
        USIMM_CCB_GetCurFileInfo(USIMM_IMS_APP)->usCurDFID = ADF;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucCharaByte = USIMM_CCB_GetCurDFInfo(USIMM_IMS_APP)->ucCharaByte;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucSupCmd    = USIMM_CCB_GetCurDFInfo(USIMM_IMS_APP)->ucSupCmd;

        USIMM_COMM_SaveDFPinInfo(USIMM_IMS_APP);

        USIMM_NORMAL_LOG("USIMM_UICC_InitIsimADF: Decode AID is Success");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitIsimADF: Select AID is Error");/*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitIsimMFile
功能描述  :初始ISIM卡必选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月27日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    /*ISIM卡需要初始化读取缓存的Mandatory文件ID*/
    VOS_UINT16                          ausIsimInitMFile[] = {USIMM_ISIM_EFAD_ID,
                                                              USIMM_ISIM_EFIMPI_ID,
                                                              USIMM_ISIM_EFIMPU_ID,
                                                              USIMM_ISIM_EFDOMAIN_ID,
                                                              USIMM_ISIM_EFIST_ID};
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimMFile: Step is Begin");

    for(i = 0;i < ARRAYSIZE(ausIsimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_IMS_APP, ausIsimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitIsimMFile:Read Mandatory File Failed");

            continue;
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitIsimFinish
功能描述  :初始ISIM卡初始化完成
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月27日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimFinish: Step is Begin");

    if (USIMM_SW_OK != USIMM_SendStatusApdu(ucChannelNo,
                                            USIMM_STATUS_CURAPP_INITIALIZED,
                                            USIMM_STATUS_NO_DATA_RETURNED,
                                            0x00))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitIsimFinish: USIMM_Status_APDU is Fail");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_UICC_InitIsimOPFile
功能描述  :初始ISIM卡可选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月27日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
#if 0
    VOS_UINT32                          i;
    VOS_UINT32                          ulFirstService;
    VOS_UINT32                          ulSecondService;
    VOS_UINT8                           ucCheck;

    /*ISIM卡需要初始化读取缓存的Optional文件ID*/
    USIMM_OPFILE_ISIM_LIST_STRU         astIsimInitOFile[] = {\
    {USIMM_ISIM_EFPCSCF_ID,    ISIM_SVR_PCSCF_ADDR, (VOS_UINT16)ISIM_SVR_IMS_PCSCF, (VOS_UINT16)USIMM_ISIM_SERVICE_OR},
    {USIMM_ISIM_EFGBAP_ID,     ISIM_SVR_GBA,        (VOS_UINT16)ISIM_SVR_GBA,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFGBANL_ID,    ISIM_SVR_GBA,        (VOS_UINT16)ISIM_SVR_GBA,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFNAFKCA_ID,   ISIM_SVR_GBA,        (VOS_UINT16)ISIM_SVR_LOCAL_GBA, (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMS_ID,      ISIM_SVR_SMS,        (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMSS_ID,     ISIM_SVR_SMS,        (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMSR_ID,     ISIM_SVR_SMSR,       (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMSP_ID,     ISIM_SVR_SOI,        (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFUICCIARI_ID, ISIM_SVR_UICC_IMS,   (VOS_UINT16)ISIM_SVR_UICC_IMS,  (VOS_UINT16)USIMM_ISIM_SERVICE_AND}};

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimOPFile: Step is Begin");

    for (i =  0; i < ARRAYSIZE(astIsimInitOFile); i++)
    {
        ulFirstService  = USIMM_IsServiceAvailable(astIsimInitOFile[i].ulFService);
        ulSecondService = USIMM_IsServiceAvailable(astIsimInitOFile[i].usSService);

        /*当前的ISIM需要两个服务位其中一个满足*/
        if (USIMM_ISIM_SERVICE_OR == astIsimInitOFile[i].enCheckType)
        {
            if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulFirstService)
             && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulSecondService))
            {
                ucCheck = VOS_NO;
            }
            else
            {
                ucCheck = VOS_YES;
            }
        }
        else /*当前ISIM需要两个服务位都满足*/
        {
            if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulFirstService)
             || (PS_USIM_SERVICE_NOT_AVAILIABLE == ulSecondService))
            {
                ucCheck = VOS_NO;
            }
            else
            {
                ucCheck = VOS_YES;
            }
        }

        if (VOS_YES != ucCheck)
        {
            continue;
        }

        /* 选择文件 */
        if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_IMS_APP, USIMM_NEED_FCP, astIsimInitOFile[i].enDefFileId))
        {
            USIMM_WARNING_LOG("USIMM_UICC_InitIsimOPFile: USIMM_SelectFile Failed");
        }

    }
#endif
    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimOPFile: USIMM Init Card File Third is Finished");

    return USIMM_INITSTEPS_SUCCESS;
}

/********************************************************************
函 数 名  :USIMM_ICC_InitGlobalVar
功能描述  :初始化ICC全局变量
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMM_INIT_SUCC
修订记录  :
1. 日    期   : 2015年03月13日
   作    者   : g00256031
   修改内容   : Creat
********************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitGlobalVar(VOS_VOID)
{
    USIMM_COMM_ResetPIN1Global();

    USIMM_PoolDelAll(); /*避免内存重复添加，先释放相关内存*/

    gstUSIMMBaseInfo.ucCLA              = USIMM_SIM_CLA;
    gstUSIMMBaseInfo.enSupportPath      = USIMM_NOTSUPPORT_PATH;
    gstUSIMMBaseInfo.enSupportSFI       = USIMM_NOTSUPPORT_SFI;
    gstUSIMMBaseInfo.enSupportChannel   = USIMM_NOTSUPPORT_CHANNEL;

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitCardTypeByATR
功能描述  :复位卡，并解析ATR数据
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitCardTypeByATR(VOS_VOID)
{
    VOS_UINT32                          ulResult          = VOS_ERR;
    VOS_UINT32                          ulErrlogNumber;
    OAM_MNTN_NO_SIM_CARD_EVENT_STRU     stNoSimCard;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;
    USIMM_CURFILEINFO_ST               *pstCurFile;

    if (USIMM_TEST_TYPE_GCF_SIM == USIMM_CCB_GetTestCardType())
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_ICC);

        pstCurFile = USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO);

        /* 默认从7F20开始选择文件 */
        pstCurFile->usCurDFID      = MF;
        pstCurFile->usCurEFID      = USIMM_NULL_ID;
        pstCurFile->usCurDFFcpLen  = VOS_NULL;
        pstCurFile->usFilePathLen  = 1;
        pstCurFile->ausFilePath[0] = MF;

        return USIMM_COMM_INIT_SUCC;
    }

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitCardTypeByATR: Reset Card is Failed");

        /* 因为双开双待所以高16位记录pid,低16位记录原来的id */
        ulErrlogNumber = WUEPS_PID_USIM;
        ulErrlogNumber <<= 16;
        ulErrlogNumber |= MNTN_OAM_NO_SIM_CARD_EVENT;

        if(VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber, (void *)&stNoSimCard, sizeof(OAM_MNTN_NO_SIM_CARD_EVENT_STRU)))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitCardTypeByATR: Fail to record no SIM card in Errorlog file");
        }

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    ulResult = USIMM_COMM_DecodeATR(); /*判断卡类型*/

    if(USIMM_COMM_INIT_SUCC == ulResult)
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_ICC);
    }

    return ulResult;                                 /*初始化第一步完成*/
}

/*****************************************************************************
函 数 名  :USIMM_ICC_CheckCLStep
功能描述  :C+L选择检查2G卡是否可用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ICC_CheckCLStep(
    USIMM_CARDAPP_ENUM_UINT32          *penCardApp
)
{
    VOS_UINT32                          ulCDMAResult = VOS_OK;
    VOS_UINT32                          ulGsmResult = VOS_OK;

    /* 分别选择7F20和7F25，判断是否支持GSM或CDMA,之后重启 */
    ulCDMAResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_CDMA_ID);

    if (USIMM_SW_OK == ulCDMAResult)
    {
        USIMM_CCB_SetAIDByApp(USIMM_CDMA_APP, VOS_StrLen(USIMM_CDMA_STR), (VOS_UINT8 *)USIMM_CDMA_STR);
    }

    ulGsmResult  = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_GSM_ID);

    if (USIMM_SW_OK == ulGsmResult)
    {
        USIMM_CCB_SetAIDByApp(USIMM_GUTL_APP, VOS_StrLen(USIMM_GSM_STR), (VOS_UINT8 *)USIMM_GSM_STR);
    }

    /* 电信要求检查卡的CDMA能力 */
    if ((VOS_OK != ulCDMAResult)
     && (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck))
    {
        USIMM_WARNING_LOG("USIMM_ICC_CheckCLStep: Select Card 7F25 is Failed");     /*打印错误*/

        return VOS_ERR;
    }

    /* 国际卡需要判断UIM/SIM初始化哪一个 */
    if ((VOS_OK == ulCDMAResult)
     && (VOS_OK == ulGsmResult))
    {
        if (USIMM_NV_CDMA_APP == USIMM_GetPreferApp())
        {
            *penCardApp = USIMM_CDMA_APP;
        }
        else
        {
            *penCardApp = USIMM_GUTL_APP;
        }

        return VOS_OK;
    }

    if (VOS_OK == ulCDMAResult)
    {
        *penCardApp = USIMM_CDMA_APP;
    }
    else if (VOS_OK == ulGsmResult)
    {
        *penCardApp = USIMM_GUTL_APP;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitAppOrder
功能描述  :确定ICC卡应用初始化类型
输入参数  :无
输出参数  :无
返 回 值  :USIMM_COMMINIT_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitAppOrder(VOS_VOID)
{
    USIMM_CARDAPP_ENUM_UINT32           enCardApp;

    USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_ICC);

    /* 如果是GCF测试卡时，只初始化GSM APP */
    if (USIMM_TEST_TYPE_GCF_SIM == USIMM_CCB_GetTestCardType())
    {
        if (USIMM_NV_CDMA_APP == USIMM_GetPreferApp())
        {
            USIMM_COMM_StoreAppSN(USIMM_CDMA_APP);

            USIMM_CCB_SetAIDByApp(USIMM_CDMA_APP, VOS_StrLen(USIMM_CDMA_STR), (VOS_UINT8 *)USIMM_CDMA_STR);
       }
        else
        {
            USIMM_COMM_StoreAppSN(USIMM_GUTL_APP);

            USIMM_CCB_SetAIDByApp(USIMM_GUTL_APP, VOS_StrLen(USIMM_GSM_STR), (VOS_UINT8 *)USIMM_GSM_STR);
        }

        return USIMM_COMM_INIT_SUCC;
    }

    /* 根据BALONG+VIA拼片使能状态判断初始化顺序 */
    if (VOS_OK == USIMM_ICC_CheckCLStep(&enCardApp))
    {
        USIMM_COMM_StoreAppSN(enCardApp);

        return USIMM_COMM_INIT_REMOVE_RESET;
    }

    return USIMM_COMM_INIT_FATAL_FAIL;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InsertCommFileToPool
功能描述  :将公共文件放到POOL中
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2015年3月13日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InsertCommFileToPool(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    /* 保证MF可以选到 */
    USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_MF_ID);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InsertCommFileToPool: Select MF is Failed");

        /*卡当前不可用*/
        return USIMM_INITSTEPS_FAIL;
    }

    /* 初始化当前MF下的文件到文件池中，类型为GUTL */
    for(i=0; i<USIMM_INITFIRST_FILENUM; i++)
    {
        if (USIMM_ICCID_ID == gausInitFileOne[i])
        {
            ulResult = USIMM_InsertFileToPool(USIMM_UNLIMIT_AUTO, gausInitFileOne[i]);
        }
        else
        {
            ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NO_NEED_FCP, gausInitFileOne[i]);
        }

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_WARNING_LOG("USIMM_ICC_InsertCommFileToPool: Select File under MF is Failed");
        }
    }

    USIMM_INFO_LOG("USIMM_ICC_InsertCommFileToPool: Init Card File First Step 1 Finished");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitCard
功能描述  :完成卡初始化的主控函数
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年2月26日
   作    者   : g00256031
   修改内容   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitCard(VOS_VOID)
{
    VOS_UINT32                          ulStep;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt = USIMM_COMM_INIT_FATAL_FAIL;

    /* ICC卡初始化 */
    for (ulStep = 0; ulStep < ARRAYSIZE(g_aICCCommInitProcFuncTbl); ulStep++)
    {
        if (USIMM_FUNC_UNAVAILABLE == g_aICCCommInitProcFuncTbl[ulStep].enStatus)
        {
            continue;
        }

        enInitRslt = g_aICCCommInitProcFuncTbl[ulStep].pProcFun();

        /* 初始化失败直接返回 */
        if ((USIMM_COMM_INIT_NORMAL_FAIL == enInitRslt)
         || (USIMM_COMM_INIT_FATAL_FAIL == enInitRslt))
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }

        /* 需要重启后再次初始化 */
        if (USIMM_COMM_INIT_RESET == enInitRslt)
        {
            ulStep = VOS_NULL_DWORD;

            continue;
        }

        if (USIMM_COMM_INIT_REMOVE_RESET == enInitRslt)
        {
            g_aICCCommInitProcFuncTbl[ulStep].enStatus = USIMM_FUNC_UNAVAILABLE;

            ulStep = VOS_NULL_DWORD;

            continue;
        }
    }

    return enInitRslt;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimGlobal
功能描述  :初始USIM卡全局变量
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(0, USIMM_GUTL_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimADF
功能描述  :初始USIM卡的DFGAM
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimADF: Select SIM Card DFGSM is Failed");     /*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_SaveDFPinInfo(USIMM_GUTL_APP);

    if (0x10 == (USIMM_CCB_GetCurDFInfo(USIMM_GUTL_APP)->ucCharaByte & 0x70)) /*SIM卡根据文件特性字节切换电压*/
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: SIM Card Need Change the Voltage.");

        /*g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag = VOS_TRUE;*/

        /*卡复位失败按照无卡处理*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitSimADF:SIM Card Change the Voltage Failed.");

            return USIMM_INITSTEPS_FAIL;      /*不需要后续的判断处理*/
        }

        /* 电压未切换直接返回 */
        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: No Need to Reset, Step is OK");

            return USIMM_INITSTEPS_SUCCESS;
        }

        USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);   /* 保正 DF 可以选到 */

        ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_ID);

        /* 电压切换后再选择一次DFGSM */
        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitSimADF: Select MF is Failed");

            return USIMM_INITSTEPS_FAIL;      /*不需要后续的判断处理*/
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitPINInfo
功能描述  :初始USIM卡PIN信息
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitPINInfo(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPIN2Info;
    USIMM_CARDAPP_ENUM_UINT32           enCardApp;

    USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is Begin");

    enCardApp   = USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_UNLIMIT_APP_BUTT == enCardApp)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: USIMM_CCB_GetAppTypeByCH is Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByApp(enCardApp);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: USIMM_CCB_GetPIN1InfoByApp is Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN2Info = USIMM_CCB_GetPIN2InfoByApp(enCardApp);

    if (VOS_NULL_PTR == pstPIN2Info)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: USIMM_CCB_GetPIN2InfoByApp is Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_InitPINState(pstPIN1Info);

    USIMM_COMM_InitPINState(pstPIN2Info);

    USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimECC
功能描述  :初始SIM卡ECC
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimECC(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32          ulResult;

    USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is Begin");

    ulResult = USIMM_InitSimEccFile(ucChannelNo);

    if (VOS_OK == ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: Step is Fail");

        return USIMM_INITSTEPS_REMOVE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimEFLP
功能描述  :初始USIM卡文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimEFLP(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32          ulResult;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimEFLP: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFLP_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSimEFLP: Step is Fail");

        return USIMM_INITSTEPS_REMOVE;
    }
    else
    {
        //USIMM_InitSimCardFileMap();

        USIMM_NORMAL_LOG("USIMM_ICC_InitSimEFLP: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimATT
功能描述  :初始SIM卡ATT定制步骤
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimATT(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimATT: Step is Begin");

    /* 判断AT&T定制是否打开 */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitSimATT: Step is Jump out");

        return USIMM_INITSTEPS_SUCCESS;
    }

    for (i = 0;i < ARRAYSIZE(g_aulAttSimInitFile); i++ )
    {
        (VOS_VOID)USIMM_InsertFileToPool(USIMM_GUTL_APP, g_aulAttSimInitFile[i]);
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimATT: Step is End");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitPhase
功能描述  :初始USIM卡Phase信息
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitPhase(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT8                           ucData;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    USIMM_NORMAL_LOG("USIMM_ICC_InitPhase: Step is Begin");

    enAppType = USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPhase: USIMM_CCB_GetAppTypeByCH Error");

        return USIMM_INITSTEPS_FAIL;
    }

    /* EFphase文件的默认值为2以便后续的FDNBDN过程可以继续走下去 */
    USIMM_CCB_SetSimPhase(enAppType, USIMM_SIM_PHASE_TWO);

    /* 判断结果和文件状态 */
    if (VOS_OK != USIMM_GetTFByDefFID(enAppType, USIMM_GSM_EFPHASE_ID, sizeof(ucData), &ucData))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPhase:Read EFPHASE Failed");

        return USIMM_INITSTEPS_REMOVE;
    }

    /* 保存当前SIM卡PHASE */
    USIMM_CCB_SetSimPhase(enAppType, ucData);

    USIMM_NORMAL_LOG("USIMM_ICC_InitPhase: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimSST
功能描述  :初始SIM卡SST
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimSST(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitPhase: Step is Begin");

    if (VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, USIMM_GSM_EFSST_ID))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSST:Read EFSST File Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSST:Read EFSST File OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitTerminalProfile
功能描述  :初始USIM卡TerminalProfile
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitTerminalProfile(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_STK_CFG_STRU                  stProfileContent;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    USIMM_NORMAL_LOG("USIMM_ICC_InitTerminalProfile: Step is Begin");

    enAppType = USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitTerminalProfile: USIMM_CCB_GetAppTypeByCH Error");

        return USIMM_INITSTEPS_FAIL;
    }

    if (USIMM_CCB_GetSimPhase(enAppType) < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitTerminalProfile: SIM Not Support SAT, Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    /*读取NV项判断当前的SAT状态*/
    USIMM_COMM_GetTerminalProfile(&stProfileContent);

    ulResult = USIMM_SendTermimalProfileDownloadApdu(stProfileContent.stSimProfile.ucProfileLen,
                                                     stProfileContent.stSimProfile.aucProfile);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitTerminalProfile: USIMM_SendTermimalProfileDownloadApdu Error");

        return USIMM_INITSTEPS_FAIL_REMOVE;
    }

    /* ATT定制过程，失败了也不处理，继续初始化 */
    USIMM_AttUpdataSupportTable(ucChannelNo);

    USIMM_NORMAL_LOG("USIMM_ICC_InitTerminalProfile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimFBDN
功能描述  :初始SIM卡FDN/BDN状态
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimFBDN(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_EFSTATUS_ENUM_UINT8           imsiState = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8           lociState = USIMM_EFSTATUS_ACTIVE;
    USIMM_BDNSTATUS_ENUM_UINT32         enBdnStatus;
    USIMM_FDNSTATUS_ENUM_UINT32         enFdnStatus;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFBDN: Step is Begin");

    /* PHASE1的SIM卡不需要处理BDN FDN过程，只有 PHASE2 PHASE2+的卡才需要 */
    if (USIMM_CCB_GetSimPhase(USIMM_GUTL_APP) < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimFBDN: SIM Not Support SAT");

        return USIMM_INITSTEPS_SUCCESS;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFIMSI_ID);

    if (VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSimFBDN: USIMM_SelectFileByDefFileId(EFIMSI) Error");

        return USIMM_INITSTEPS_FAIL;
    }

    imsiState = USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus;

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFLOCI_ID);

    if (VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSimFBDN: USIMM_SelectFileByDefFileId(EFLOCI) Error");

        return USIMM_INITSTEPS_FAIL;
    }

    lociState = USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus;

    /* IMSI和LOCI不同时无效时，单板执行不受约束操作 */
    if ((USIMM_EFSTATUS_DEACTIVE != imsiState) || (USIMM_EFSTATUS_DEACTIVE != lociState))
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimFBDN: EFIMIS or EFLOCI File status fail");
    }

    /* BDN能力请求 */
    USIMM_BdnCapabilityRequest(&enBdnStatus);

    USIMM_CCB_SetAppBDN(USIMM_GUTL_APP, enBdnStatus);

    /* FDN能力请求 */
    USIMM_FdnCapabilityRequest(&enFdnStatus);

    USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, enFdnStatus);

    if (VOS_OK != USIMM_SimFDNBDNProcess())
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimFBDN: USIMM_SimFDNBDNProcess is Fail");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFBDN: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimMFile
功能描述  :初始SIM卡必选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausSimInitMFile[] = {USIMM_GSM_EFIMSI_ID, USIMM_GSM_EFAD_ID};

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile: Step is Begin");

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;

    for(i = 0;i < ARRAYSIZE(ausSimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausSimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitSimMFile:Read Mandatory File Failed");

            return USIMM_INITSTEPS_FAIL;
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimMFile2
功能描述  :初始SIM卡必选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausSimInitMFile[] = {USIMM_GSM_EFACC_ID,
                                                             USIMM_GSM_EFHPLMN_ID,
                                                             USIMM_GSM_EFLOCI_ID,
                                                             USIMM_GSM_EFKC_ID,
                                                             USIMM_GSM_EFBCCH_ID,
                                                             USIMM_GSM_EFFPLMN_ID};

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile2: Step is Begin");

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;

    for(i = 0;i < ARRAYSIZE(ausSimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausSimInitMFile[i]))
        {
            USIMM_ERROR_LOG("v:Read Mandatory File Failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimFinish
功能描述  :初始SIM卡完成
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFinish: Step is Begin");

    USIMM_SetAccFileAccess();

	USIMM_SetImsiFile();

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFinish: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_ReadSimOPFile
功能描述  :初始USIM卡可选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ICC_ReadSimOPFile(VOS_VOID)
{
    VOS_UINT32                      i;

    for (i = 0; i < ARRAYSIZE(gastSimInitOFile); i++)
    {
        if (UICC_SVR_NONE != gastSimInitOFile[i].ulService)
        {
            if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(gastSimInitOFile[i].ulService))
            {
                continue;
            }
        }

        if (VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, gastSimInitOFile[i].enDefFileID))
        {
            USIMM_WARNING_LOG("USIMM_ICC_InitSimOPFile: Read Optional File Failed");
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitSimOPFile
功能描述  :初始SIM卡可选文件
输入参数  :ucChannelNo  逻辑通道号
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitSimOPFile: Step is Begin");

    if (VOS_FALSE == USIMM_COMM_IsAndroidPhone())
    {
        /*lint -e534*/
        USIMM_SendInitCardMsg(WUEPS_PID_USIM, USIMM_INITCONTINUE_REQ);
        /*lint +e534*/
    }
    else
    {
        USIMM_ICC_ReadSimOPFile();
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimOPFile: Step is Begin");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimGlobal
功能描述  :初始UIM卡全局变量
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(0, USIMM_CDMA_APP);

    return USIMM_INITSTEPS_SUCCESS;
}


/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimADF
功能描述  :初始UIM卡的ADF
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_FAIL/USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitUimADF: Select SIM Card DFGSM is Failed");     /*打印错误*/

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_SaveDFPinInfo(USIMM_CDMA_APP);

    if (0x10 == (USIMM_CCB_GetCurDFInfo(USIMM_CDMA_APP)->ucCharaByte & 0x70)) /*SIM卡根据文件特性字节切换电压*/
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: SIM Card Need Change the Voltage.");

        /*卡复位失败按照无卡处理*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitUimADF:SIM Card Change the Voltage Failed.");

            return USIMM_INITSTEPS_FAIL;      /*不需要后续的判断处理*/
        }

        /* 电压未切换直接返回 */
        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: No change VCC Step is OK");

            return USIMM_INITSTEPS_SUCCESS;
        }

        USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);   /* 保正 DF 可以选到 */

        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
        /* 电压切换后再选择一次DFCDMA */
        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitUimADF: Select MF is Failed");

            return USIMM_INITSTEPS_FAIL;      /*不需要后续的判断处理*/
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}


/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimRuimId
功能描述  :UIM卡初始化RUIMID
输入参数  :无
输出参数  :无
返 回 值  :USIMM_INITSTEPS_RST_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimRuimId(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT8                           aucRuimId[8];


    USIMM_NORMAL_LOG("USIMM_ICC_InitUimRuimId: Step is Begin");

    if (USIMM_SW_OK != USIMM_GetTFByDefFID(USIMM_CDMA_APP, USIMM_CDMA_EFRUIMID_ID, sizeof(aucRuimId), aucRuimId))/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimRuimId:USIMM_SendReadBinaryApdu error");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimRuimId: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimECC
功能描述  :UIM卡初始化紧急呼叫号码
输入参数  :无
输出参数  :ucChannelNo:Channel Number
返 回 值  :USIMM_INITSTEPS_REMOVE/USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimECC(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT8                          *pData;
    VOS_UINT32                          ulResult;
    USIMM_EFFCP_ST                     *pstCurEFInfo;

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimECC: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFECC_ID);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_SELECT_FAIL;

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_XeccNumberInd(VOS_NULL, VOS_NULL_PTR);

        return USIMM_INITSTEPS_REMOVE;
    }

    pstCurEFInfo = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP);

    if (VOS_NULL_PTR == pstCurEFInfo)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:USIMM_CCB_GetCurEFInfo error");

        return USIMM_INITSTEPS_REMOVE;
    }

    if (USIMM_EFSTRUCTURE_TRANSPARENT != pstCurEFInfo->enFileType)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_TYPE_ERR;

        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:ECC FILE TYPE error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_XeccNumberInd(VOS_NULL, VOS_NULL_PTR);

        return USIMM_INITSTEPS_REMOVE;
    }

    pData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,
                                      DYNAMIC_MEM_PT,
                                      pstCurEFInfo->usFileLen);/*分配数据存储空间*/

    if (VOS_NULL_PTR == pData)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:VOS_MemAlloc error");

        return USIMM_INITSTEPS_SUCCESS;
    }

    ulResult = USIMM_SendReadBinaryApdu(ucChannelNo,
                                        VOS_NULL,
                                        pstCurEFInfo->usFileLen,
                                        pData);

    if (USIMM_SW_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_READ_FAIL;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:USIMM_SendReadBinaryApdu error");

        /* 读取文件失败认为ECC文件不存在，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_XeccNumberInd(VOS_NULL, VOS_NULL_PTR);

        return USIMM_INITSTEPS_SUCCESS;
    }

    /* 上报当前的Ecc号码内容 */
    USIMM_XeccNumberInd(pstCurEFInfo->usFileLen, pData);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pData);
    /*lint +e534*/

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimECC: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitCST
功能描述  :初始化UIM卡Cdma Service Table
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitCST(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitCST: Step is Begin");

    /* 初始化失败也不返回错误，继续初始化过程 */
    if (VOS_OK != USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFCST_ID))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitCST:Read EFCST File Failed");
    }
    else
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitSST:Read EFCST File OK");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitCST: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}


/*****************************************************************************
函 数 名  :USIMM_ICC_InitTerminalProfile
功能描述  :初始USIM卡的FdnBdn
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimFdnBdn(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitUimFdnBdn: Step is Begin");

    if (VOS_OK != USIMM_ICC_InitUimFdnStatus())
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnBdn: USIMM_ICC_InitUimFdnStatus Error");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimFdnBdn: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_InitUimFDNBDNStatus
功能描述  :初始化UIM卡当前的FDN/BDN状态　
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ICC_InitUimFdnStatus(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_EFSTATUS_ENUM_UINT8           enImsimState    = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8           enImsitState    = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8           enTmsiState     = USIMM_EFSTATUS_ACTIVE;
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus     = USIMM_FDNSTATUS_OFF;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    /*lint -e534*/
    VOS_MemSet(&stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));
    /*lint +e534*/

    /* 只有 PHASE2/PHASE2+的卡才需要 */
    if (USIMM_CCB_GetSimPhase(USIMM_CDMA_APP) < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitUimFdnStatus: SIM Not Support SAT");

        return VOS_OK;
    }

    /* 初始化IMSIM的状态 */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIM_ID);

    if (VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnStatus: USIMM_SelectFileByDefFileId(EF_CUIM_IMSIM) Error");

        return VOS_ERR;
    }

    enImsimState = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus;

    /* 初始化IMSIT的状态 */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIT_ID);

    if (VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnStatus: USIMM_SelectFileByDefFileId(EF_CUIM_IMSIT) Error");

        return VOS_ERR;
    }

    enImsitState = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus;

    /* 初始化TMSI的状态 */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFTMSI_ID);

    if (VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnStatus: USIMM_SelectFileByDefFileId(EF_CUIM_IMSIT) Error");

        return VOS_ERR;
    }

    enTmsiState = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus;

    /* IMSI和LOCI不同时无效时，单板执行不受约束操作 */
    if ((USIMM_EFSTATUS_DEACTIVE != enImsimState)
     || (USIMM_EFSTATUS_DEACTIVE != enImsitState)
     || (USIMM_EFSTATUS_DEACTIVE != enTmsiState))
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitUimFdnStatus: File status Error");
    }

    /* UIM卡没有BDN功能 */
    USIMM_CCB_SetAppBDN(USIMM_CDMA_APP, USIMM_BDNSTATUS_OFF);

    /* FDN能力请求 */
    USIMM_ICC_FdnCapabilityRequest(&enFDNStatus);

    USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, enFDNStatus);

    return USIMM_ICC_UimFdnProcess();
}

/*****************************************************************************
函 数 名  :USIMM_ICC_FdnCapabilityRequest
功能描述  :初始化UIM卡FDN能力请求　
输入参数  :无
输出参数  :USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus
返 回 值  :无

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_ICC_FdnCapabilityRequest(
    USIMM_FDNSTATUS_ENUM_UINT32        *pulFdnStatus
)
{
    VOS_UINT32                          ulResult;

    /* 若FDN状态在CST文件中未allocated and activated,FDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(UIM_SVR_FDN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_OFF;

        USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_OFF");

        return;
    }

    /* 若ADN状态在CST文件中未allocated and activated,FDN激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(UIM_SVR_ADN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_ON");

        return;
    }

    /* ADN文件不存在,FDN激活 */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_TELE_EFADN_ID);

    if (VOS_OK != ulResult)
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_ON");
    }
    else
    {
        /* ADN文件无效,FDN激活 */
        if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
        {
            *pulFdnStatus = USIMM_FDNSTATUS_ON;

            USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_ON");
        }
        /* ADN文件有效,FDN未激活 */
        else
        {
            *pulFdnStatus = USIMM_FDNSTATUS_OFF;

            USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_OFF");
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_UimFdnProcess
功能描述  :完成UIM卡的FDN功能开启后的初始化中相关文件有效的过程　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ICC_UimFdnProcess(VOS_VOID)
{

    /* 恢复IMSIM文件 */
    if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIM_ID))
    {
        USIMM_ERROR_LOG("USIMM_ICC_UimFdnProcess: USIMM_SelectFileByDefFileId(EFIMSIM) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
        /*lint +e534*/
    }

    /* 恢复IMSIT文件 */
    if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIT_ID))/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_UimFdnProcess: USIMM_SelectFileByDefFileId(EFIMSIT) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
        /*lint +e534*/
    }

    /* 恢复TMSI文件 */
    if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFTMSI_ID))/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_UimFdnProcess: USIMM_SelectFileByDefFileId(EFTMSI) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
        /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimMFile
功能描述  :初始UIM卡M类型的文件
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile: Step is Begin");

    /*Read EF AD*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFAD_ID);

    /*Read EF Revision*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFREVISION_ID);

    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFIMSIM_ID);

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimMFile2
功能描述  :初始UIM卡M2类型的文件
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          aucFileList[] = {USIMM_CDMA_EFUSGIND_ID,
                                                         USIMM_CDMA_EFSP_ID,
                                                         USIMM_CDMA_EFIMSIM_ID,
                                                         USIMM_CDMA_EFIMSIT_ID,
                                                         USIMM_CDMA_EFACCOLC_ID,
                                                         /*USIMM_CDMA_EFPRL_ID,
                                                         USIMM_CDMA_EFEPRL_ID,*/
                                                         USIMM_CDMA_EFTMSI_ID};

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile2: Step is Begin");

    for (i=0; i<ARRAYSIZE(aucFileList); i++)
    {
        if(VOS_OK == USIMM_InsertFileToPool(USIMM_CDMA_APP, aucFileList[i]))
        {
            USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile2: File read failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimEFMecrp
功能描述  :初始UIM卡过程中个更新文件EF MECRP
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimEFMecrp(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUpdate[3] = {0};

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP,
                                           USIMM_NEED_FCP,
                                           USIMM_CDMA_EFMECRP_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Select File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_COMM_GetMecrpValue(&aucUpdate[0], &aucUpdate[1]);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: USIMM_COMM_GetMecrpValue is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_SendUpdateBinaryApdu(ucChannelNo, sizeof(aucUpdate), aucUpdate);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Update is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimEF3gpd
功能描述  :初始UIM卡过程中个更新文件EF ME3GPDOOPC
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimEF3gpd(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulSIPStatus;
    VOS_UINT32                          ulMIPStatus;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucFileData;

    ulSIPStatus = USIMM_IsServiceAvailable(UIM_SVR_3GPD_SIP);

    ulMIPStatus = USIMM_IsServiceAvailable(UIM_SVR_3GPD_MIP);

    if (  (PS_USIM_SERVICE_NOT_AVAILIABLE == ulSIPStatus)
        &&(PS_USIM_SERVICE_NOT_AVAILIABLE == ulMIPStatus))
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitCsimEF3gpd: Service is Close");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP,
                                           USIMM_NEED_FCP,
                                           USIMM_CDMA_EFME3GPDOPC_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitCsimEF3gpd: Select File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ucFileData = (VOS_UINT8)(USIMM_CDMA_3GPD_SIMPLEIP);

    ulResult = USIMM_SendUpdateBinaryApdu(ucChannelNo, sizeof(ucFileData), &ucFileData);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitCsimEF3gpd: Update File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitUimFinish
功能描述  :初始UIM卡过程结束
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年3月10日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitUimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
函 数 名  :USIMM_ICC_InitStoreEsnMeid
功能描述  :初始UIM卡过程中MANAGE ESN MEID
输入参数  :ucChannelNo:Channel Number
输出参数  :无
返 回 值  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

修订记录  :
1. 日    期   : 2015年8月28日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitStoreEsnMeid(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulSvcStatus;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    USIMM_FEATURE_CFG_STRU              stUsimmFeatureCfg;
    USIMM_APDU_RSP_STRU                 stRspData = {0};
    VOS_UINT8                           aucEsnMeid[USIMM_STORE_ESNMEID_MAX];

    USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Step is Begin");

    (VOS_VOID)VOS_MemSet(&g_stStoreEsnMeidStatus, 0, sizeof(USIMM_STORE_ESN_MEID_STATUS_STRU));

    (VOS_VOID)VOS_MemSet(&stUsimmFeatureCfg, 0, sizeof(USIMM_FEATURE_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config, &stUsimmFeatureCfg, sizeof(USIMM_FEATURE_CFG_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: NV_Read en_NV_Item_USIMM_WRITE_MEID_PESN_TAG Failed");

        /* 读NV失败走原有存卡流程 */
        stUsimmFeatureCfg.unCfg.stFeatureCfg.bMeidPesnAPWriteEnable = VOS_FALSE;
    }

    if (VOS_TRUE == stUsimmFeatureCfg.unCfg.stFeatureCfg.bMeidPesnAPWriteEnable)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Meid no need write to card");

        /* 产品线定制不需在卡初始化存卡则直接返回 */
        return USIMM_INITSTEPS_SUCCESS;
    }

    if (NV_OK != NV_Read(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: NV_Read en_NV_Item_MEID Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    ulSvcStatus = USIMM_IsServiceAvailable(UIM_SVR_MEID);

    if (PS_USIM_SERVICE_AVAILIABLE == ulSvcStatus)
    {
        aucEsnMeid[0] = MEID_NV_DATA_LEN_NEW;

        (VOS_VOID)VOS_MemCpy(aucEsnMeid + 1, stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

        ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_MEID_P1,
                                              ucChannelNo,
                                              aucEsnMeid,
                                              &stRspData);

        if (VOS_OK == ulResult)
        {
            g_stStoreEsnMeidStatus.ucStoreEsnMeidResult = stRspData.aucRsp[0];

            g_stStoreEsnMeidStatus.ucIsStoreEsnMeid  = VOS_TRUE;

            USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Step is OK");

            return USIMM_INITSTEPS_SUCCESS;
        }
    }

    if (NV_OK != NV_Read(en_NV_Item_PESN, &stPEsn, sizeof(stPEsn)))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: NV_Read en_NV_Item_PESN Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    aucEsnMeid[0] = PESN_NV_DATA_LEN;

    (VOS_VOID)VOS_MemCpy(aucEsnMeid + 1, stPEsn.aucPEsn, PESN_NV_DATA_LEN);

    ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_ESN_P1,
                                          ucChannelNo,
                                          aucEsnMeid,
                                          &stRspData);

    if (VOS_OK == ulResult)
    {
        g_stStoreEsnMeidStatus.ucStoreEsnMeidResult = stRspData.aucRsp[0];

        g_stStoreEsnMeidStatus.ucIsStoreEsnMeid  = VOS_TRUE;

        USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: Command Send error");

    /* 将此步骤移除，不重启卡 */
    return USIMM_INITSTEPS_REMOVE;
}

/*****************************************************************************
函 数 名  : USIMM_GetAppInitList
功能描述  : 实现了卡重启相关操作
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetAppInitList(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_INITAPPLIST_FUNC            **ppstFuncList,
    VOS_UINT8                          *pucListNum
)
{
    if (USIMM_GUTL_APP == enAppType)
    {
        if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aSIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aSIMInitProcFuncTbl);
        }
        else if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aUSIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aUSIMInitProcFuncTbl);
        }
        else
        {
            return VOS_ERR;
        }
    }
    else if (USIMM_CDMA_APP == enAppType)
    {
        if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aUIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aUIMInitProcFuncTbl);
        }
        else if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aCSIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aCSIMInitProcFuncTbl);
        }
        else
        {
            return VOS_ERR;
        }
    }
    else if (USIMM_IMS_APP == enAppType)
    {
        *ppstFuncList   = g_aISIMInitProcFuncTbl;
        *pucListNum     = ARRAYSIZE(g_aISIMInitProcFuncTbl);
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_INIT_GetUiccCommInitFuncNum
功能描述  :获取Comm 初始化的函数个数
输入参数  :
输出参数  :无
返 回 值  :函数个数
调用函数  :

修订记录  :
1. 日    期   : 2015年4月10日
   作    者   : C00299064
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_INIT_GetUiccCommInitFuncNum(VOS_VOID)
{
    return ARRAYSIZE(g_aUICCCommInitProcFuncTbl);
}

/*****************************************************************************
函 数 名  :USIMM_INIT_GetUiccCommInitFunc
功能描述  :获取Comm 初始化的函数个数
输入参数  :
输出参数  :无
返 回 值  :函数个数
调用函数  :

修订记录  :
1. 日    期   : 2015年4月10日
   作    者   : C00299064
   修改内容   : Creat
*****************************************************************************/
USIMM_COMM_CARD_INIT_FUNC* USIMM_INIT_GetUiccCommInitFunc(VOS_VOID)
{
    return g_aUICCCommInitProcFuncTbl;
}

/*****************************************************************************
函 数 名  :USIMM_INIT_GetFuncStatus
功能描述  :获取初始化函数的执行结果
输入参数  :
输出参数  :无
返 回 值  :函数的执行结果
调用函数  :

修订记录  :
1. 日    期   : 2015年4月16日
   作    者   : C00299064
   修改内容   : Creat
*****************************************************************************/
USIMM_INITAPPLIST_FUNC*  USIMM_GetInitFunsByAppType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    PFAPPSETPINITPROC                   pInitFunc
)
{
    USIMM_INITAPPLIST_FUNC             *pInitFuncList = VOS_NULL_PTR;
    VOS_UINT8                           ucInitFuncNum = 0;
    VOS_UINT8                           ucIndex       = 0;

    if (VOS_ERR == USIMM_GetAppInitList(enAppType, &pInitFuncList, &ucInitFuncNum))
    {
        USIMM_WARNING_LOG("USIMM_INIT_GetFuncStatus:USIMM_RefreshGetAppInitList error");

        return VOS_NULL_PTR;
    }

    for (ucIndex = 0; ucIndex < ucInitFuncNum; ucIndex++)
    {
        if (pInitFuncList[ucIndex].pProcFun == pInitFunc)
        {
            return &pInitFuncList[ucIndex];
        }
    }

    return VOS_NULL_PTR;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif
