/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MmaAppLocal.c
  Author       : ---
  Version      : V200R002
  Date         : 2005-09-10
  Description  : 该C文件给出了MMA模块的本地实现
                        1、流程处理类的，直接调用原TAF_status模块
                        2、查询类的，将准备好的数据从全局变量中提取，
                        并做成数据包，调用TAF_ParaQeryReport()函数上报。

  Function List:
  History      :

  1.日    期   : 2009年09月24日
    作    者   : s46746
    修改内容   : 问题单号：AT2D14697，所卡功能激活，锁卡号段全部为默认值时，
                 不应该需要锁卡密码
  2.日    期   : 2009年09月24日
    作    者   : s46746
    修改内容   : 问题单号：AT2D14722，卡已经被锁定后，使用有效SIM卡仍然提示设备非法
  3.日    期   : 2009年09月25日
    作    者   : x00115505
    修改内容   : 问题单号：AT2D14748,无卡时查询系统信息，返回结果错误
  4.日    期   : 2009年10月3日
    作    者   : s46746
    修改内容   : 问题单号：AT2D14936,Location Status Event 发送的时机和码流不正确
  5.日    期   : 2009年10月3日
    作    者   : h44270
    修改内容   : 问题单号：AT2D14891,锁卡在NV项未激活时，判定不正确
  6.日    期   : 2009年10月27日
    作    者   : s46746
    修改内容   : 问题单号：AT2D15219,锁卡功能开启，插入需要解锁码的开启PIN码的SIM卡，
                 解锁PIN码后，后台不弹出解锁框
  7.日    期   : 2009年10月28日
    作    者   : x00115505
    修改内容   : 问题单号：AT2D15171,AT+COPS第四个注册上3G网络LED绿灯单闪一段时间
                 后再改变回蓝灯单闪
  8.日    期   : 2009年11月3日
    作    者   : l00130025,h44270
    修改内容   : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo
                 卡状态返回
  9.日    期   : 2010年1月23日
    作    者   : s46746
    修改内容   : 问题单号:AT2D16443, 增加对NV模块定义长度与MMA结构体定义长度不一
                 致的保护
 10.日    期   : 2010年2月3日
    作    者   : s46746
    修改内容   : AT2D16583,增加CPOL命令对列表进行修改功能
 11.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
 12.日    期   : 2010年3月3日
    作    者   : s46746
    修改内容   : AT2D17131,CGATT在CS ONLY下不能设置
 13.日    期   : 2010年3月12日
    作    者   : zhoujun /z40661
    修改内容   : Vos_TaskDelay清理
 14.日    期   : 2010年04月22日
    作    者   : x00115505
    修改内容   : 问题单号AT2D17652,NV读写冗余操作处理
 15.日    期   : 2010年4月27日
    作    者   : zhoujun /z40661
    修改内容   : 问题单AT2D18882修改
 16.日    期   : 2010年06月13日
    作    者   : f62575
    修改内容   : 问题单号：DTS2010061300180, 局部变量pucAsciiStr初始化使用越界
 17.日    期   : 2010年07月10日
    作    者   : h44270
    修改内容   : 问题单号：DTS2010071000587, 局部变量pucAsciiStr初始化使用越界
   1.日    期   : 2010年07月19日
    作    者   : s62952
    修改内容   : AT2D19187，飞行模式低功耗修改合入
 19.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting
************************************************************************/



/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#define TAF_NEED_TAF_TAFM_LOCAL_INC 1


/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
#include "MnComm.h"
#include "Nasrrcinterface.h"
#include "UsimPsInterface.h"
#include "UsimPsApi.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "rfa.h"
/*#include "LightLED.h"
 */
#include "mdrv.h"

#include "NasMmlLib.h"
#include "siappstk.h"

#include "MmaAppLocal.h"
#include "NasComm.h"
#include "NVIM_Interface.h"

#include "ScInterface.h"

/*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
#include "MnErrorCode.h"
/*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

#include "TafApsComFunc.h"
#include "GasNvInterface.h"

#if ( FEATURE_ON == FEATURE_LTE )
#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif


#ifdef NAS_STUB
#include "usimmbase.h"
#endif
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
#include "TafMmaProcNvim.h"
#include "TafMmaMain.h"
#include "TafMmaPreProcAct.h"
#include "TafMmaMntn.h"
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */


#if ( FEATURE_ON == FEATURE_LTE )
#include "gen_msg.h"
#include "msp_errno.h"
#include "v_lib.h"
#include "msp_nvim.h"
#endif

#if (VOS_WIN32 == VOS_OS_VER)
/*Added by  z59430 for PC回放,2010-1-6,begin*/
#include "nvim_fileoperateinterface.h"
/*Added by  z59430 for PC回放,2010-1-6,end*/
#endif

#include "TafApsProcNvim.h"

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
#include "TafSdcCtx.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
#include "TafMmaNetworkNameTbl.h"

#include "NasUsimmApi.h"

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#include "TafStdlib.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/* Added by l00208543 for V9R1 STK升级, 2013-7-22, begin */
#include "Taf_Status.h"
/* Added by l00208543 for V9R1 STK升级, 2013-7-22, end */

/* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "MtcMmaInterface.h"
#endif
/* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#include "TafMmaSndTaf.h"
#include "TafMmaSndInternalMsg.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
#include "TafMmaSndApp.h"
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */

/* Added by s00261364 for V3R360_eCall项目, 2014-4-17, begin */
#include "TafMmaProcUsim.h"
/* Added by s00261364 for V3R360_eCall项目, 2014-4-17, end */

#include "TafMmaInterface.h"

#include "TafMmaSndMscc.h"
#include "TafLog.h"

#include "UsimPsInterface.h"

#include "TafMmaComFunc.h"
/* added by wx270776 for OM融合, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM融合, 2014-08-21, end */
#include "NasDynLoadApi.h"


#include "TafMmaSndMtc.h"
#include "TafMmaFsmPhoneMode.h"

#if (FEATURE_ON == FEATURE_BASTET)
#include "MmaBastetInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-16, end */
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MMA_APPLOCAL_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
/* Modified by wx270776 for OM融合, 2015-7-17, begin */
VOS_UINT8                 g_ucMmaOmConnectFlg = VOS_FALSE;                      /* 是否已与PC工具连接, VOS_TRUE: 已连接; VOS_FALSE: 未连接.
                                                                                   默认未连接 */
VOS_UINT8                 g_ucMmaOmPcRecurEnableFlg  = VOS_FALSE;               /* 当前PC工具是否使能了NAS的PC回放消息的发送, VOS_TRUE: 使能; VOS_FASLE: 未使能
                                                                                   默认使能PC回放 */
/* Modified by wx270776 for OM融合, 2015-7-17, end */
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */


VOS_UINT32                g_ucUsimHotOutFlag;
VOS_UINT32                g_ucUsimHotInFlag;
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
/* USIM卡热插拔的可维可测计数 */
VOS_UINT32                       g_ulUsimHotOutCount = 0;
VOS_UINT32                       g_ulUsimHotInCount  = 0;
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-16, end */

/*APS模块USIM相关初始化函数*/
extern TAF_UINT32   At_HexAlpha2AsciiString(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
extern VOS_VOID     SHPA_ActivateHw(VOS_VOID);
extern VOS_VOID     SHPA_DeactivateHw(VOS_VOID);



/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

/* Added by m00217266 for 底软接口归一, 2014-9-5, begin */
/* 这两个接口由第三方提供*.o文件，此处声明下 */
extern int VerifySL(char* UnlockCode, char* Key);
/* Added by m00217266 for 底软接口归一, 2014-9-5, end */


/*****************************************************************************
   2 全局变量定义和宏
****************************************************************************/
#define MMA_REPORT_HEAD                 8 /*TAF_MSG_HEADER + QUERY_TYPE + INFO_LEN*/
#define MMA_PARA_LEN_POSITION           4
#define MMA_PH_PIN_TI                   2
#define MN_MMA_MAX_UPLMN_NUM            (100)
/* Added by 傅映君/f62575 for E5宏开关打开后编译问题 从V3R1版本移植, 2011/11/15, begin */
#define MMA_PLMN_ID_LEN                 (6)
/* Added by 傅映君/f62575 for E5宏开关打开后编译问题, 2011/11/15, end */


TAF_MMA_GLOBAL_VALUE_ST                 gstMmaValue;
MMA_UE_FORB_BAND_ST                     gstMmaForbBand;
MMA_TIMER_ST                            g_MmaSimTimer[TAF_SIM_TIMER_NUM];
MMA_TI_TABLE                            gastMmaTiTab[MMA_MAX_TI];
MMA_INTERNAL_TIMER_ST                   gstMmaInternalTimer;

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

VOS_UINT8                               g_aucMmaImei[TAF_PH_IMEI_LEN-1]={0};
extern STATUS_CONTEXT_STRU              g_StatusContext;
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */
/* 删除gstMmaInitialTimer */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */
VOS_BOOL                                f_bGetRecRange = VOS_FALSE;

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU g_stMmsStkLocStaSysInfo;
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

MMA_TIMER_ST                            g_MmaTimerforPcReplay;

MMA_TIMER_ST                            g_stPhPhResetTimer;

MMA_TIMER_ST                            g_stPhPinOperTimer;


MMA_TIMER_ST                            g_stPowerDownDelayTimer;

MMA_TIMER_ST                            g_stNetScanProtectTimer;
MMA_TIMER_ST                            g_stAbortNetScanProtectTimer;

/* 记录PIN当前操作结果  */
TAF_PH_PIN_CNF_STRU                     g_stPhPinCnf;
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */

MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8  g_ucMmaDeactSimWhenPoweroff;
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

MMA_CIPHER_INFO_STRU                    g_stMmaCipherInfo = {0};

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */

/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
ENUM_SYSTEM_APP_CONFIG_TYPE_U16         g_usMmaAppConfigSupportType = SYSTEM_APP_BUTT;
/* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


MMA_GET_REC_INFO_STRU                   f_stRecInfo;

NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST g_MmaNewValue;

#define MMA_PIN_HANDLE_TIME             25000
#define MMA_GET_FILE_TIME               21000
#define MMA_START_INITIAL_TIME          5000
#define MMA_INTERNAL_TIME               1000


#define MMA_PIN_LEN_MAX                 8
#define MMA_PIN_LEN_MIN                 4
#define MMA_TI_USED                     1

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
#define MMA_WRITE_NVIM_INDEX            0x1
#define MMA_READ_NVIM_INDEX             0x1
#define MMA_DE_ATTACH_NULL              0x0
#define MMA_WCDMA_BAND_TYPE_MAX         0x3
#define MMA_BAND_TYPE_NULL              0x0

/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

#define MMA_RSCP_MAX                    (-60)
#define MMA_ECNO_MAX                    (0)

/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
#define MMA_RSSI_INVALID                (99)

/* 两秒 */
#define MMA_INVALID_RSCP_SEC_MAX        (2)

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */
 MMA_ME_PERSONALISATION_STATUS_STRU      g_stMmaMePersonalisationStatus;

MMA_MODIFY_PLMN_INFO_STRU               f_stMmaPlmnInfo;
/* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
/* 记录上一次向WAS查询 RSCP 和 ECNO 的有效值 */
VOS_INT16                               g_sLastRscp = MMA_RSCP_MIN;
VOS_INT16                               g_sLastEcNo = MMA_ECNO_MIN;

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

#define PROTOCOL_STACK_VERSION "V300R001C01B050"

VOS_UINT8                               g_ucMnPhRoamStatus = TAF_PH_INFO_NONE_ROMAING;  /* 记录漫游状态(上报给应用) */



/* 版本号以环境变量传入的为准 */
#ifdef EV_PS_VERSION
    #undef PROTOCOL_STACK_VERSION
    #define PROTOCOL_STACK_VERSION EV_PS_VERSION
#endif




TAF_PH_BAND_NAME_STRU gastMmaSyscfgBandStr[] =
{
    {TAF_PH_BAND_GSM_850     ,      "GSM850"   },
    {TAF_PH_BAND_GSM_900     ,      "GSM900"   },
    {TAF_PH_BAND_GSM_DCS_1800,      "GSM1800"  },
    {TAF_PH_BAND_GSM_PCS_1900,      "GSM1900"  },
    {TAF_PH_BAND_WCDMA_VI_800,      "WCDMA800" },
    {TAF_PH_BAND_WCDMA_V_850,       "WCDMA850" },
    {TAF_PH_BAND_WCDMA_VIII_900,    "WCDMA900" },
    {TAF_PH_BAND_WCDMA_XI_1500,     "WCDMA1500"},
    {TAF_PH_BAND_WCDMA_IV_1700,     "AWS"},
    {TAF_PH_BAND_WCDMA_IX_1700,     "WCDMA1700"},
    {TAF_PH_BAND_WCDMA_III_1800,    "WCDMA1800"},
    {TAF_PH_BAND_WCDMA_II_PCS_1900, "WCDMA1900"},
    {TAF_PH_BAND_WCDMA_I_IMT_2100,  "WCDMA2100"},
    {TAF_PH_BAND_WCDMA_VII_2600,    "WCDMA2600"}

};





/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/
VOS_INT32 MMA_Bcd2Int (VOS_UINT8 ucChar)
{
    return ((ucChar>>4) + ((ucChar&0x0f)*10));
}

/*****************************************************************************
 函 数 名  : MN_PH_IsPlmnValid
 功能描述  : 判断PLMNID是否合法
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月9日
    作    者   : luojian id:107747
    修改内容   : 新生成函数，A32D13994
*****************************************************************************/
VOS_BOOL MN_PH_IsPlmnValid(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT32                          i;

    for (i=0; i<3; i++)
    {
        if ((((pstPlmnId->Mcc >> (i*4)) & 0x0F) > 9)
         || ((((pstPlmnId->Mnc >> (i*4)) & 0x0F) > 9) && (i != 2 ))
         || ((((pstPlmnId->Mnc >> (i*4)) & 0x0F) > 9) && (((pstPlmnId->Mnc >> (i*4)) & 0x0F) != 0x0F)))
        {
            /* PLMN ID无效 */
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : MN_PH_GetUpdateFileForPrefPlmn
 功能描述  : 根据Pref PLMN的操作,确定当前要更新的文件
 输出参数  : 需要更新的USIM文件
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月11日
    作    者   : l00130025
    修改内容   : 新生成函数，
*****************************************************************************/
VOS_UINT16 MN_PH_GetUpdateFileForPrefPlmn(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
)
{
    VOS_UINT16                          usUpdateFile;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType       = TAF_SDC_GetSimType();
    usUpdateFile    = 0;

    if (MN_PH_PREF_PLMN_UPLMN == enPrefPLMNType)
    {
        if (VOS_TRUE == MN_PH_IsUsingPlmnSel())
        {
            usUpdateFile = USIMM_GSM_EFPLMNSEL_ID;
        }
        else
        {
            if (TAF_SDC_SIM_TYPE_USIM == enSimType)
            {/* 3G USIM */
                usUpdateFile = USIMM_USIM_EFPLMNWACT_ID;
            }
            else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
            {/* 2G SIM */
                usUpdateFile = USIMM_GSM_EFPLMNWACT_ID;
            }
            else
            {
                usUpdateFile = USIMM_DEF_FILEID_BUTT;
            }
        }
    }
    else if (MN_PH_PREF_PLMN_OPLMN == enPrefPLMNType)
    {
        if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFOPLMNWACT_ID;
        }
        else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFOPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else
    {
        if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFHPLMNwACT_ID;
        }
        else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFHPLMNACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    return usUpdateFile;
}


/**********************************************************
 Function:       MMA_DbProc
 Description:    处理APP/AT参数设置查询类消息
 Calls:          Taf_MsgProc
 Data Accessed:
 Data Updated:
 Input:          pMsg - DOPRA消息
 Output:
 Return:
 Others:         2005-9-9
 修改历史      :
  1.日    期   : 2006年10月25日
    作    者   : h44270
    修改内容   : 问题单号：A32D06630
  2.日    期   : 2010年8月4日
    作    者   : 傅映君/f62575
    修改内容   : AT装备归一化
  3.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : V7R1 phase II支持syscfgex命令修改
  4.日    期   : 2011年10月05日
    作    者   : c00173809
    修改内容   : AT融合项目，
  5.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 增加ACINFO信息的查询请求处理
  6.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
  7.日    期   : 2013年06月08日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:不用的函数删除
  8.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  9.日    期   : 2014年01月15日
    作    者   : f62575
    修改内容   : DTS2014011301359: 增加对+CPOL查询命令的请求消息处理
  10.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
  11.日    期   : 2014年12月2日
     作    者   : g00261581
     修改内容   : 1x下新增at命令处理
**********************************************************/
VOS_UINT32 MMA_DbProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    /*消息类型*/
    usMsgType = pstRcvMsg->usMsgName;

    /*ClientId*/
    usClientId = pstRcvMsg->clientId;
    ucOpId     = pstRcvMsg->opId;

    if (usClientId >= TAF_MAX_CLIENT_OF_ONE_PROC)
    {
        TAF_LOG(WUEPS_PID_MMA, 0, PS_LOG_LEVEL_ERROR,
            "MMA_TafMsgProc:ERROR:Client ID is out of range!");

        return VOS_TRUE;
    }

    switch((TAF_MSG_TYPE)usMsgType)
    {


        case TAF_MSG_MMA_USIM_INFO:
            MMA_QryUsimInfo(usClientId,ucOpId, (TAF_PH_QRY_USIM_INFO_STRU *)pstRcvMsg->aucContent);
            break;
        case TAF_MSG_MMA_CPNN_INFO:
            MMA_CPnnQuery(usClientId, ucOpId, (TAF_PH_ICC_TYPE*)pstRcvMsg->aucContent);
            break;


        default:
            Taf_ParaSetResult(usClientId,ucOpId, TAF_ERR_CMD_TYPE_ERROR, (TAF_PARA_TYPE)usMsgType, VOS_NULL_PTR);
            MMA_ERRORLOG1("MMA_DbProc:ERROR:ERROR DB PROC INDEX:", usMsgType);
    }

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}



/*****************************************************************************
 函 数 名  : MN_MMA_GetOnlyGURatOrder
 功能描述  : 从当前接入优先级中提取GU模接入优先级的信息
 输入参数  : pstAllRatOrder，所有模接入优先级信息
 输出参数  : pstGURatOrder - GU模接入优先级信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : W00167002
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID MN_MMA_GetOnlyGURatOrder(
    TAF_MMA_RAT_ORDER_STRU             *pstAllRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstGURatOrder
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucIndex;

    ucIndex         = 0;

    /* 获取GU模信息 */
    for (i = 0; i < pstAllRatOrder->ucRatOrderNum; i++)
    {
        if ( (TAF_MMA_RAT_WCDMA == pstAllRatOrder->aenRatOrder[i])
          || (TAF_MMA_RAT_GSM   == pstAllRatOrder->aenRatOrder[i]) )
        {
            pstGURatOrder->aenRatOrder[ucIndex] = pstAllRatOrder->aenRatOrder[i];
            ucIndex++;
        }
    }

    pstGURatOrder->ucRatOrderNum          = ucIndex;
    pstGURatOrder->aenRatOrder[ucIndex]   = TAF_MMA_RAT_BUTT;
    return;
}

/*****************************************************************************
函 数 名  : MN_MMA_GetCpamGURatPrio
功能描述  : 从当前接入信息中提取GU模接入优先级信息
输入参数  : pstAllRatOrder - 所有模接入优先级信息
输出参数  : pucPlmnPrio    - GU模接入优先级信息
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : W00167002
   修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID MN_MMA_GetCpamGURatPrio(
   MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8     *pucPlmnPrio,
   TAF_MMA_RAT_ORDER_STRU              *pstAllRatOrder
)
{
    TAF_MMA_RAT_ORDER_STRU              stGURatOrder;

    /* 从接入信息中取得GU模的信息 */
    MN_MMA_GetOnlyGURatOrder(pstAllRatOrder, &stGURatOrder);

    /* 没有GU模信息时，默认为W优先 */
    if ( 0 == stGURatOrder.ucRatOrderNum )
    {
        *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
        return;
    }

    /* 将当前GU模信息转换为CPAM的接入优先级信息格式 */
    switch ( stGURatOrder.aenRatOrder[0] )
    {
        case TAF_MMA_RAT_WCDMA:
            *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
            break;

        case TAF_MMA_RAT_GSM :
            *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_GSM;
            break;

        default:
            MN_ERR_LOG("MN_MMA_GetGUPlmnPrio,ERROR:RAT WRONG!");
            *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : MN_MMA_GetCpamGUAccessRat
功能描述  : 从当前接入信息中提取GU模接入技术信息
输入参数  : pstAllRatOrder - 所有模接入优先级信息
输出参数  : penAccessMode  - GU模接入技术信息
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : W00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年12月26日
   作    者   : s46746
   修改内容   : DSDA GUNAS C CORE项目，如果不支持GU，接入模式填写为无效值
*****************************************************************************/
VOS_VOID MN_MMA_GetCpamGUAccessRat(
   MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     *penAccessMode,
   TAF_MMA_RAT_ORDER_STRU              *pstAllRatOrder
)
{
    TAF_MMA_RAT_ORDER_STRU              stGURatOrder;

    /* 从接入信息中取得GU模的信息 */
    MN_MMA_GetOnlyGURatOrder(pstAllRatOrder, &stGURatOrder);

    if ( 0 == stGURatOrder.ucRatOrderNum)
    {
        /* 没有GU模，默认接入技术为双模都支持 */
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_BUTT;
    }
    else if (VOS_TRUE == MN_MMA_IsGOnlyMode(&stGURatOrder))
    {
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_GSM;;
    }
    else if (VOS_TRUE == MN_MMA_IsWOnlyMode(&stGURatOrder))
    {
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_WCDMA;
    }
    else
    {
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_WCDMA_GSM;
    }

    return;
}



/*****************************************************************************
 函 数 名  : MMA_GetCpolPara
 功能描述  : 从AT保存全局变量中获得CPOL命令各参数
 输入参数  : 无
 输出参数  : TAF_UINT32           *pulIndex
             TAF_PLMN_ID_STRU     *pstPlmnId
             AT_COPS_FORMAT_TYPE  *pTmpFormat
             TAF_BOOL             *pbOperExist
             TAF_BOOL             *pbFormat
             TAF_BOOL             *pbAccessExist
 返 回 值  : TAF_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : c00173809
    修改内容   : 新生成函数


*****************************************************************************/
VOS_VOID MMA_GetCpolPara(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmn,
    VOS_UINT32                         *pulIndex,
    TAF_PLMN_ID_STRU                   *pstPlmnId,
    AT_COPS_FORMAT_TYPE                *pTmpFormat,
    VOS_BOOL                           *pbOperExist,
    VOS_BOOL                           *pbFormat
)
{
    /* 设置<index> */
    if ( 0 != pstPrefPlmn->usIndexLen )
    {
        *pulIndex = pstPrefPlmn->usIndex;
    }

    /* 设置<format> */
    if ( 0 != pstPrefPlmn->usFormatLen )
    {
        *pTmpFormat = (AT_COPS_FORMAT_TYPE)pstPrefPlmn->usFormat;
    }
    else
    {
        *pTmpFormat = AT_COPS_LONG_ALPH_TYPE;
        *pbFormat   = TAF_FALSE;
    }

    PS_MEM_SET(pstPlmnId,(VOS_CHAR)0xFF,sizeof(TAF_PLMN_ID_STRU));
    /* 设置<oper> */
    if ( 0 != pstPrefPlmn->usOperNameLen )
    {
        /* 转化用户输入PLMN字符为PLMN ID */
        if( VOS_TRUE != MMA_FormatPlmnStr2PlmnId(pstPlmnId,
                                                 pstPrefPlmn->usFormat,
                                                 pstPrefPlmn->usOperNameLen,
                                                 pstPrefPlmn->ucOperName) )
        {
            *pbOperExist = TAF_FALSE;
        }
    }
    else
    {
        *pbOperExist = TAF_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MMA_SetCpolOperType
 功能描述  : 获取CPOL命令操作类型
 输入参数  : 无
 输出参数  : TAF_PH_PREF_PLMN_OPERATE_STRU *pstPrefPlmn
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : c00173809
    修改内容   : 新生成函数


*****************************************************************************/
VOS_UINT16 MMA_SetCpolOperType(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmnParam,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt)
{
    VOS_UINT32                          ulIndex;
    TAF_PLMN_ID_STRU                    stPlmnId;
    AT_COPS_FORMAT_TYPE                 TmpFormat;
    VOS_BOOL                            bOperExist;
    VOS_BOOL                            bFormat;

    ulIndex      = MMA_INVALID_INDEX;
    TmpFormat    = AT_COPS_LONG_ALPH_TYPE;
    bOperExist   = TAF_TRUE;
    bFormat      = TAF_TRUE;

    MMA_GetCpolPara(pstPrefPlmnParam,&ulIndex,&stPlmnId,&TmpFormat,&bOperExist,&bFormat);

    /* <index>存在,但<oper>不存在，则默认为删除此条记录 */
    if ((MMA_INVALID_INDEX != ulIndex) && (TAF_FALSE == bOperExist))
    {
        pstPrefPlmnOpt->enPrefPlmnOperType = MN_PH_PrefPLMN_DEL_ONE;
        pstPrefPlmnOpt->ulIndex            = ulIndex;
    }
    else if ((MMA_INVALID_INDEX == ulIndex)
          && (TAF_TRUE == bOperExist)
          && (TAF_TRUE == bFormat) )
    {
        /* <oper>存在,但<index>不存在，则默认为增加一条记录 */
        pstPrefPlmnOpt->enPrefPlmnOperType = MN_PH_PrefPLMN_ADD_ONE;
        PS_MEM_CPY(&pstPrefPlmnOpt->stPlmn,&stPlmnId,sizeof(stPlmnId));
    }
    else if ((MMA_INVALID_INDEX != ulIndex)
          && (TAF_TRUE == bOperExist)
          && (TAF_TRUE == bFormat) )
    {
        /* <oper>存在,<index>存在，则认为修改一条记录 */
        pstPrefPlmnOpt->enPrefPlmnOperType = MN_PH_PrefPLMN_MODIFY_ONE;
        pstPrefPlmnOpt->ulIndex            = ulIndex;
        PS_MEM_CPY(&pstPrefPlmnOpt->stPlmn,&stPlmnId,sizeof(stPlmnId));
    }
    else
    {
        return TAF_ERR_PARA_ERROR;
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : MMA_CheckAccessExist
 功能描述  : 检查GSM_ACT,GSM_COMPRESS_ACT,UTRAN_ACT这三个参数是否合法
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月28日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV 支持L的cpol命令修改
  3.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持LTE判断

*****************************************************************************/
VOS_UINT16 MMA_CheckAccessExist(
    TAF_PH_SET_PREFPLMN_STRU             *pstPrefPlmnParam,
    TAF_MMC_USIM_RAT                     *pusRat
)
{
    VOS_BOOL                            bPlmnSelFlg;

#if(FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulPlatformSuppLteFlg;
#endif
    VOS_UINT32                          ulAtParaRatValid;

    *pusRat     = TAF_MMC_USIM_NO_RAT;
    bPlmnSelFlg = VOS_FALSE;

    if (MN_PH_PREF_PLMN_UPLMN == pstPrefPlmnParam->enPrefPlmnType)
    {
        bPlmnSelFlg = MN_PH_IsUsingPlmnSel();
    }

    if ((3 == pstPrefPlmnParam->ucAtParaIndex)
     && (VOS_TRUE == bPlmnSelFlg))
    {
        /* 当前Uplmn为PlmnSel时，不需要输入接入技术,该标识在MMA中处理*/
        *pusRat = TAF_MMC_USIM_UTRN_GSM_RAT;
        return VOS_TRUE;
    }

#if(FEATURE_ON == FEATURE_LTE)
    ulPlatformSuppLteFlg = TAF_SDC_IsPlatformSupportLte();

    /* 当参数个数为7时，LTE宏打开始终认为有效 */
    if (7 == pstPrefPlmnParam->ucAtParaIndex)
    {
        ulAtParaRatValid = VOS_TRUE;
    }
    /* 当参数个数为6时，LTE宏打开平台不支持LTE时才有效 */
    else if ((6 == pstPrefPlmnParam->ucAtParaIndex)
          && (VOS_FALSE == ulPlatformSuppLteFlg))
    {
        ulAtParaRatValid = VOS_TRUE;
    }
    else
    {
        ulAtParaRatValid = VOS_FALSE;
    }
#else
    /* 当LTE宏关闭，参数个数为6才认为有效 */
    if (6 == pstPrefPlmnParam->ucAtParaIndex)
    {
        ulAtParaRatValid = VOS_TRUE;
    }
    else
    {
        ulAtParaRatValid = VOS_FALSE;
    }
#endif

    if (VOS_FALSE == ulAtParaRatValid)
    {
        return VOS_FALSE;
    }

    if (1 == pstPrefPlmnParam->usGsmRat)
    {
        *pusRat = TAF_MMC_USIM_GSM_RAT;
    }

    if (1 == pstPrefPlmnParam->usGsmCompactRat)
    {
        *pusRat |= TAF_MMC_USIM_GSM_COMPACT_RAT;
    }

    if (1 == pstPrefPlmnParam->usUtrn)
    {
        *pusRat |= TAF_MMC_USIM_UTRN_RAT;
    }

#if(FEATURE_ON == FEATURE_LTE)
    if ((VOS_TRUE == pstPrefPlmnParam->usEutrn)
     && (VOS_TRUE == ulPlatformSuppLteFlg))
    {
        *pusRat |= TAF_MMC_USIM_E_UTRN_RAT;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMA_CheckCpolParas
 功能描述  : 对CPOL命令参数进行检查
 输入参数  : TAF_PH_PREF_PLMN_OPERATE_STRU *pstPrefPlmn
 输出参数  : 无
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2011年12月28日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV 支持L的cpol命令修改

*****************************************************************************/
VOS_UINT16 MMA_CheckCpolPara(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmnParam,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt)
{
    VOS_UINT16                          usRet;

    usRet = MMA_SetCpolOperType(pstPrefPlmnParam,pstPrefPlmnOpt);

    if (VOS_TRUE != usRet)
    {
        return usRet;
    }

    if ((MN_PH_PrefPLMN_ADD_ONE == pstPrefPlmnOpt->enPrefPlmnOperType)
     || (MN_PH_PrefPLMN_MODIFY_ONE == pstPrefPlmnOpt->enPrefPlmnOperType))
    {
        /* 增加或修改时,将用户设置接入技术修改为USIM的格式 */
        usRet = MMA_CheckAccessExist(pstPrefPlmnParam,&pstPrefPlmnOpt->usRat);
        if (VOS_TRUE != usRet)
        {
            return usRet;
        }
    }
    else
    {
        if ((0 != pstPrefPlmnParam->usGsmRatLen)
         || (0 != pstPrefPlmnParam->usGsmCompactRatLen)
#if(FEATURE_ON == FEATURE_LTE)
         || (0 != pstPrefPlmnParam->usEutrnLen)
#endif
         || (0 != pstPrefPlmnParam->usUtrnLen))
        {
            return TAF_ERR_PARA_ERROR;
        }
    }

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : Mma_VerifyPhonePersSuccEvent
 功能描述  : AP-Modem形态下，解锁或unblock成功后上报事件
 输入参数  : enVerifySimlockRsltOrig 解锁前的状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月12日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_VOID    Mma_VerifyPhonePersSuccEvent(SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRsltOrig)
{
    TAF_PHONE_EVENT_INFO_STRU *         pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("Mma_VerifyPhonePersSuccEvent:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /*调用TAF事件上报函数,上报PIN事件*/
    pstPhoneEvent->OP_Pin             = VOS_TRUE;
    pstPhoneEvent->PhoneEvent         = TAF_PH_EVT_OP_PIN_CNF;

    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OK;

    switch (enVerifySimlockRsltOrig)
    {
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNET_PIN;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
           break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNET_PUK;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_UNBLOCK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNETSUB_PIN;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNETSUB_PUK;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_UNBLOCK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
            pstPhoneEvent->PinCnf.PinType = TAF_PHSP_PIN;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            pstPhoneEvent->PinCnf.PinType = TAF_PHSP_PUK;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_UNBLOCK;
            break;
        default:
            /* 异常取值 */
            pstPhoneEvent->PinCnf.PinType = TAF_SIM_NON;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
            break;
    }

    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}


/*****************************************************************************
 函 数 名  : MMA_SetCPinForApModemWhenLocked
 功能描述  : AP-Modem形态下，锁网状态下的解锁/UNBLOCK处理
 输入参数  : MN_PH_SET_CPIN_REQ_STRU            *pstSetCPinReq,
             VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月25日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目新增函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年8月15日
    作    者   : w00242748
    修改内容   : 接口调整
  4.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_VOID MMA_SetCPinForApModemWhenLocked(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MN_PH_SET_CPIN_REQ_STRU            *pstSetCPinReq
)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRslt;
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRsltOrig;
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucTi;
    MODEM_ID_ENUM_UINT16                enModemId;


    enVerifySimlockRslt     = SC_VERIFY_SIMLOCK_RESULT_BUTT;
    enVerifySimlockRsltOrig = SC_VERIFY_SIMLOCK_RESULT_BUTT;

    /* 将ASCII字符的密码("0"~"9"的ASCII字符)转换为数字密码(0~9的数字) */
    for (ulLoop = 0; ulLoop < pstSetCPinReq->usPara0Len; ulLoop++)
    {
        if( ('0' <= *(pstSetCPinReq->aucPara0 + ulLoop) )
         && ('9' >= *(pstSetCPinReq->aucPara0 + ulLoop) ))
        {
            *(pstSetCPinReq->aucPara0 + ulLoop) -= '0';
        }
        else
        {
            MMA_HandleEventError(usClientId,
                                 ucOpId,
                                 TAF_ERR_PARA_ERROR,
                                 TAF_PH_EVT_OP_PIN_CNF );
            return;
        }
    }

    /* 先获取到解锁前的锁卡状态，用户后续返回解锁/UNBLOCK 成功事件时，填写PinType使用 */
    enModemId  = VOS_GetModemIDFromPid(WUEPS_PID_MMA);
    enScResult = SC_PERS_VerifySimLock(&enVerifySimlockRsltOrig, enModemId);

    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        MMA_HandleEventError(usClientId,
                             ucOpId,
                             TAF_ERR_UNSPECIFIED_ERROR,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }

    /* 调用SC接口进行解锁或UNBLOCK */
    enScResult = SC_PERS_UnLock(pstSetCPinReq->aucPara0, (VOS_UINT8)pstSetCPinReq->usPara0Len, &enVerifySimlockRslt, enModemId);


    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        if ( SC_ERROR_CODE_UNLOCK_KEY_INCORRECT == enScResult)
        {
            MMA_HandleEventError(usClientId,
                                 ucOpId,
                                 TAF_ERR_SIM_INCORRECT_PASSWORD,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        else
        {
            MMA_HandleEventError(usClientId,
                                 ucOpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        return;
    }

    /*填入对PIN操作的全局变量供返回函数查询，存储CLIENTID*/
    /*记录当前clientId与OpId*/
    if (MMA_SUCCESS != MMA_TiAlloc(TAF_MMA, usClientId, ucOpId, TAF_PH_EVT_OP_PIN_CNF, &ucTi))
    {   /*Ti分配失败*/
        MMA_WARNINGLOG("MMA_SetCPinForApModemWhenLocked():WARNING:ALLOC TI FAILED!");
        /*错误处理*/
        MMA_HandleEventError(usClientId, ucOpId, TAF_ERR_TI_ALLOC_FAIL, TAF_PH_EVT_OP_PIN_CNF);
        return;
    }

    /* 向AT发送解锁或UNBLOCK成功事件 */
    Mma_VerifyPhonePersSuccEvent(enVerifySimlockRsltOrig);

    /* 如果解锁后处于ready态，则构造卡状态变化上报，并将锁卡状态设置为已经解锁 */
    if (SC_VERIFY_SIMLOCK_RESULT_READY == enVerifySimlockRslt)
    {
        /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-15, begin */
        /* 解锁卡后触发锁网锁卡状态变化指示消息 */
        TAF_MMA_SndSimlocakStatusChangeInd();
        /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-15, end */

        g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_LOCK_IS_VERIFY;
    }

    return;
}


/**********************************************************
 函 数 名  : MMA_SetCPin
 功能描述  : 处理设置PIN码消息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月3日
    作    者   : c00173809
    修改内容   : AT 融合项目,AT^CPIN改成异步消息通信
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2012年04月16日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目修改
  4.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  5.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*************************************************************/
VOS_UINT32 MMA_SetCPin(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_PIN_DATA_STRU                stPinData;
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;
    MN_PH_SET_CPIN_REQ_STRU            *pstSetCPinReq;
    VOS_UINT32                          i;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MN_APP_REQ_MSG_STRU                *pRcvMsg;
    VOS_UINT16                          ClientId;
    VOS_UINT8                           OpId;

    pRcvMsg         = (MN_APP_REQ_MSG_STRU*)pstMsg;
    ClientId        = pRcvMsg->clientId;
    OpId            = pRcvMsg->opId;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */



    PS_MEM_SET(&stPinData, (VOS_CHAR)0xFF, sizeof(stPinData));

    pstSetCPinReq = (MN_PH_SET_CPIN_REQ_STRU*)pRcvMsg->aucContent;

    if (TAF_PH_ME_SIM_LOCK == MMA_GetMeLockStatus())
    {
        /* 若上层应用为AP-Modem，则走AP-Modem的处理分支，否则走MBB的处理分支 */
        if (SYSTEM_APP_ANDROID == g_usMmaAppConfigSupportType)
        {
            MMA_SetCPinForApModemWhenLocked(ClientId, OpId, pstSetCPinReq);
        }
        else
        {
            /* 初始化 */
            PS_MEM_SET(&stMePersonalisationData,0x00,sizeof(stMePersonalisationData));

            /* 设置<pin> */
            if (0 != pstSetCPinReq->usPara0Len)
            {
                PS_MEM_CPY((VOS_VOID*)stMePersonalisationData.aucOldPwd,
                           (VOS_VOID*)pstSetCPinReq->aucPara0,
                           pstSetCPinReq->usPara0Len);
            }

            /* 设置<newpin> */
            if (0 != pstSetCPinReq->usPara1Len)
            {
                PS_MEM_CPY((VOS_VOID*)stMePersonalisationData.aucNewPwd,
                           (VOS_VOID*)pstSetCPinReq->aucPara1,
                           pstSetCPinReq->usPara1Len);
            }

            /* 设置CmdType */
            stMePersonalisationData.MePersonalType  = TAF_SIM_PERSONALISATION;
            stMePersonalisationData.CmdType         = TAF_ME_PERSONALISATION_VERIFY;

            /* 执行命令操作 */
            MMA_MePersonalisationHandle(ClientId, OpId,stMePersonalisationData);
        }
    }
    else
    {
        /* 初始化 */
        SI_PB_MemSet(sizeof(stPinData), 0xFF,(VOS_UINT8 *)&stPinData);

        /* 设置<pin> */
        if(0 != pstSetCPinReq->usPara0Len)
        {
            if (TAF_PH_PINCODELENMAX < pstSetCPinReq->usPara0Len)
            {
                MMA_HandleEventError(ClientId,
                                     OpId,
                                     TAF_ERR_PARA_ERROR,
                                     TAF_PH_EVT_OP_PIN_CNF );

                /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
                return VOS_TRUE;
                /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
            }

            for(i=0; i<pstSetCPinReq->usPara0Len; i++)
            {
                if((pstSetCPinReq->aucPara0[i] > '9' )||(pstSetCPinReq->aucPara0[i] < '0'))
                {
                    MMA_HandleEventError(ClientId,
                                         OpId,
                                         TAF_ERR_PARA_ERROR,
                                         TAF_PH_EVT_OP_PIN_CNF );

                    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
                    return VOS_TRUE;
                    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
                }
            }

            PS_MEM_CPY((VOS_VOID*)stPinData.aucOldPin,(VOS_VOID*)pstSetCPinReq->aucPara0,pstSetCPinReq->usPara0Len);
        }

        /* 设置<newpin> */
        if (0 != pstSetCPinReq->usPara1Len)
        {
            for (i=0; i<pstSetCPinReq->usPara1Len; i++)
            {
                if ((pstSetCPinReq->aucPara1[i] > '9' )||(pstSetCPinReq->aucPara1[i] < '0'))
                {
                    MMA_HandleEventError(ClientId,
                                         OpId,
                                         TAF_ERR_PARA_ERROR,
                                         TAF_PH_EVT_OP_PIN_CNF );

                    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
                    return VOS_TRUE;
                    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
                }
            }

            PS_MEM_CPY((VOS_VOID*)stPinData.aucNewPin,(VOS_VOID*)pstSetCPinReq->aucPara1,pstSetCPinReq->usPara1Len);
        }

        /* 设置CmdType */
        if (0 == pstSetCPinReq->usPara1Len)
        {
            stPinData.PinType = TAF_SIM_PIN;
            stPinData.CmdType = TAF_PIN_VERIFY;
        }
        else
        {
            stPinData.PinType = TAF_SIM_PUK;
            stPinData.CmdType = TAF_PIN_UNBLOCK;
        }

        /* 执行命令操作 */
        MMA_PinHandle(ClientId, OpId,stPinData);
    }

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

}


/*****************************************************************************
 Prototype      : At_DigitString2Hex
 Description    : 完成数字型字符串转16进制数功能
 Input          : nptr --- 字符串
 Output         :
 Return Value   : AT_SUCCESS --- 成功
                  AT_FAILURE --- 失败
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2011-04-29
    Author      : h44270
    Modification: Created function, added for DTS2011042602815，增加功能函数
*****************************************************************************/
VOS_UINT32 MMA_DigitString2Hex(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn)
{
    TAF_UINT32 c     = 0;         /* current Char */
    TAF_UINT32 total = 0;         /* current total */
    TAF_UINT8 Length = 0;         /* current Length */
    /*lint -e961*/
    c = (TAF_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else
        {
            return VOS_FALSE;
        }

        if(total > 0x0FFFFFFF)              /* 发生反转 */
        {
            return VOS_FALSE;
        }
        else
        {
            total = (total << 4) + c;              /* accumulate digit */
            c = (TAF_UINT32)(TAF_UINT8)*nptr++;    /* get next Char */
        }
    }
    /*lint +e961*/
    *pRtn = total;   /* return result, negated if necessary */
    return VOS_TRUE;
}

/**********************************************************
 函 数 名  : MMA_FormatPlmnStr2PlmnId
 功能描述  : 转化用户输入PLMN字符为PLMN ID
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月15日
    作    者   : c00173809
    修改内容   : AT 融合项目
  2.日    期   : 2014年7月7号
    作    者   : z00234330
    修改内容   : coverity清理
*************************************************************/
VOS_UINT32 MMA_FormatPlmnStr2PlmnId(
    TAF_PLMN_ID_STRU                   *pPlmn,
    VOS_UINT32                          usFormat,
    VOS_UINT16                          usOprNameLen,
    VOS_CHAR                           *pucOprName
)
{
    TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU AtOperName;

    PS_MEM_SET(&AtOperName,0x00,sizeof(AtOperName));
    /* 根据ucType，获取PLMN */
    switch(usFormat)
    {
    case AT_COPS_LONG_ALPH_TYPE:    /* long format alphanumeric */
        (VOS_VOID)VOS_StrCpy((VOS_CHAR*)AtOperName.OperName.aucOperatorNameLong,
                   (VOS_CHAR*)pucOprName);
        AtOperName.ListOp = TAF_PH_OPER_NAME_LONGNAME2OTERS;

        if(MMA_SUCCESS == Taf_PhoneGetOperNameInfo(&AtOperName))
        {
            pPlmn->Mnc = AtOperName.OperName.PlmnId.Mnc;

            pPlmn->Mcc = AtOperName.OperName.PlmnId.Mcc;
        }
        else
        {
            return VOS_FALSE;
        }
        break;

    case AT_COPS_SHORT_ALPH_TYPE:   /* short format alphanumeric */
        (VOS_VOID)VOS_StrCpy((VOS_CHAR*)AtOperName.OperName.aucOperatorNameShort,
                   (VOS_CHAR*)pucOprName);
        AtOperName.ListOp = TAF_PH_OPER_NAME_SHORTNAME2OTHERS;

        if(MMA_SUCCESS == Taf_PhoneGetOperNameInfo(&AtOperName))
        {
            pPlmn->Mnc = AtOperName.OperName.PlmnId.Mnc;

            pPlmn->Mcc = AtOperName.OperName.PlmnId.Mcc;
        }
        else
        {
            return VOS_FALSE;
        }
        break;

    default:  /* numeric */
        if(VOS_FALSE == MMA_DigitString2Hex((TAF_UINT8*)pucOprName,3,&pPlmn->Mcc))
        {
            return VOS_FALSE;
        }
        /* Mnc */
        if(VOS_FALSE == MMA_DigitString2Hex((TAF_UINT8*)&pucOprName[3],usOprNameLen-3,&pPlmn->Mnc))
        {
            return VOS_FALSE;
        }

        pPlmn->Mcc |= 0xFFFFF000;
        pPlmn->Mnc |= (0xFFFFFFFF << ((usOprNameLen-3)*4));

        break;
    }
    return VOS_TRUE;
}

/**********************************************************
 函 数 名  : TAF_MMA_QryEonsUcs2
 功能描述  : 查询ucs2编码的运营商名称
 输入参数  : usClientId - client ID
             ucOpId     - Operation ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月28日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*************************************************************/
VOS_VOID TAF_MMA_QryEonsUcs2(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                          stMmPlmnInfo;
    VOS_UINT8                                               ucIndex;
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperNameInfo = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                                    stPlmnId;
    TAF_SDC_PLMN_ID_STRU                                   *pstAppServicePlmnId = VOS_NULL_PTR;
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU                        stEonsUcs2PlmnName;

    pstEnhancedOperNameInfo = TAF_SDC_GetEnhancedOperatorNameInfo();
    pstAppServicePlmnId     = TAF_SDC_GetAppServicePlmnId();
    PS_MEM_SET(&stPlmnId, 0, sizeof(stPlmnId));

    /*获取当前PLMN中所带的运营商信息*/
    PS_MEM_SET(&stMmPlmnInfo, 0, sizeof(stMmPlmnInfo));
    PS_MEM_SET(&stEonsUcs2PlmnName, 0, sizeof(stEonsUcs2PlmnName));

    if (VOS_FALSE == TAF_IsNormalSrvStatus())
    {
        stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
        stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
        PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
        PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
        TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
        return;
    }

    stPlmnId.ulMcc = pstAppServicePlmnId->ulMcc;
    stPlmnId.ulMnc = pstAppServicePlmnId->ulMnc;

    for (ucIndex = 0; ucIndex < pstEnhancedOperNameInfo->stOperNameTypePrio.ucOperNamePrioNum; ucIndex++)
    {
        /* 从PNN中获取运营商名称*/
        if (TAF_SDC_OPER_NAME_TYPE_PNN == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            /* 从PNN中获取运营商名称成功，则直接返回*/
            if (VOS_TRUE == TAF_MMA_GetPnnNetWorkName(&stPlmnId, &stMmPlmnInfo, TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2))
            {
                stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
                stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
                PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
                PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
                TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
                return;
            }
        }

        /* 从CPHS中获取运营商名称,CPHS不存在UCS2编码*/
        if (TAF_SDC_OPER_NAME_TYPE_CPHS == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            continue;
        }

        /* 从MM INFO中获取运营商名称*/
        if (TAF_SDC_OPER_NAME_TYPE_MMINFO == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            /* 从MM INFO中获取运营商名称成功，则直接返回*/
            if (VOS_TRUE == TAF_MMA_GetMmInfoNetWorkName(&stPlmnId, &stMmPlmnInfo, TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2))
            {
                stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
                stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
                PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
                PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
                TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
                return;
            }
        }

        /* 从SPN中获取运营商名称*/
        if (TAF_SDC_OPER_NAME_TYPE_SPN == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            /* 从SPN中获取运营商名称成功，则直接返回*/
            if (VOS_TRUE == TAF_MMA_GetSpnNetWorkName(&stPlmnId, &stMmPlmnInfo, TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2))
            {
                stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
                stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
                PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
                PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
                TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);

                return;
            }
        }
    }


    /*使用数据上报函数将数据传至AT*/
    stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
    stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
    PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
    PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));

    TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
    return;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_TranslateOperatorName2UCS2
 功能描述  : 运营商名称转换成UCS-2编码
 输入参数  : 无
 输出参数  : pucSrcNtwkName   //原始数据
             pucDstNtwkName   //解码后的数据
             pucSrcNtwkName   //目的数据缓冲区长度
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2013年01月12日
    作    者   : l65478
    修改内容   : DTS2012011201289
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  4.日    期   : 2013年10月11日
    作    者   : z00161729
    修改内容  : DTS2013071808373:TQE告警清理

*****************************************************************************/
 VOS_UINT8 TAF_MMA_TranslateOperatorName2UCS2(
    TAF_SDC_OPERATOR_NAME_STRU  *pstSrcNtwkName,
    VOS_CHAR                    *pucDstNtwkName,
    VOS_UINT8                    ucDstLen
)
 {
    VOS_UINT8                           ucCodScheme;
    VOS_UINT8                           uc7BitCharNum;
    VOS_UINT8                          *pucTmpNtwkName;
    VOS_UINT8                          *pTmpDstName;
    VOS_UINT8                           ucTmpDecodeLen;
    VOS_UINT8                           ucDecodeLen;
    VOS_UINT8                           i;

    VOS_UINT32                          ulRslt;

    ucDecodeLen = 0;

    /* pucSrcNtwkName中的编码参考24.008 MM INFORMATION
       第一个字节是长度,第二个字节是编码类型,后面的是编码后的网络名称 */
    if (0 == pstSrcNtwkName->ucLength)
    {
        return ucDecodeLen;
    }

    ucCodScheme     = pstSrcNtwkName->bitCoding;

    uc7BitCharNum   = (VOS_UINT8)(((pstSrcNtwkName->ucLength) * 8) / 7);
    pucTmpNtwkName    = &pstSrcNtwkName->aucOperatorName[0];

    ucTmpDecodeLen = uc7BitCharNum;
    if (0 != (((pstSrcNtwkName->ucLength) * 8) % 7))
    {
        ucTmpDecodeLen += 1;
    }

    pTmpDstName = PS_MEM_ALLOC(WUEPS_PID_MMC, ucTmpDecodeLen);
    if (VOS_NULL_PTR == pTmpDstName)
    {
        return ucDecodeLen;
    }

    /* 如果是7 BIT编码,转换成UCS-2 */
    if (0 == ucCodScheme)
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        ulRslt = TAF_STD_UnPack7Bit(pucTmpNtwkName, uc7BitCharNum, 0,(VOS_UINT8*)pTmpDstName);

        if (VOS_OK != ulRslt)
        {
            MMA_WARNINGLOG("TAF_MMA_TranslateNtwkName2Str: TAF_STD_UnPack7Bit Err.");
        }
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

        /* 解码后的数据转换成UCS-2 */
        for (i = 0; i < ucTmpDecodeLen; i++)
        {
            if ((i * 2) < ucDstLen)
            {
                /*lint -e961*/
                *(pucDstNtwkName+i*2) = 0;
                *(pucDstNtwkName+(i*2 + 1)) = (VOS_CHAR)(pTmpDstName[i]);
                /*lint +e961*/
            }
            else
            {
                break;
            }
        }
        ucDecodeLen = (VOS_UINT8)((i - 1)*2);
    }
    else if (1 == ucCodScheme)
    {
        ucDecodeLen = pstSrcNtwkName->ucLength;
        if (ucDecodeLen > ucDstLen)
        {
            PS_MEM_CPY(pucDstNtwkName, pucTmpNtwkName, ucDstLen);
            ucDecodeLen = ucDstLen;
        }
        else
        {
            PS_MEM_CPY(pucDstNtwkName, pucTmpNtwkName, ucDecodeLen);
        }
    }
    else
    {
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pTmpDstName);

    return ucDecodeLen;
 }


/**********************************************************
 函 数 名  : TAF_MMA_ReportEonsUcs2Rsp
 功能描述  : 回复EONSUCS2的查询
 输入参数  : TAF_ERROR_CODE_ENUM_UINT32          usErrorCode
             TAF_MMA_EONS_UCS2_PLMN_NAME_STRU    *pstEonsUcs2PlmnName
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月12日
    作    者   : c00318887
    修改内容   : 新增函数
*************************************************************/
VOS_VOID TAF_MMA_ReportEonsUcs2Rsp(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstEonsUcs2PlmnName
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    if ( TAF_ERR_NO_ERROR != enErrorCode )
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_EONS_UCS2_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndEonsUcs2Rsp(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                enRslt,
                                enErrorCode,
                                pstEonsUcs2PlmnName);

        /* 清除CTX中内容  */
        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReportEonsUcs2Rsp:ERROR");
    }

    return;

}



/**********************************************************
 函 数 名  : Taf_PhoneProc
 功能描述  : TAF处理APP/AT 电话管理命令函数
 输入参数  : ucMsgType - PS呼叫消息类型
             ClientId - APP/AT客户端标识
             OpId - 操作标识
             usIeMask - 消息中Ie存在的标记位
             pMsg - 编码缓冲区指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年2月23日
    作    者   : liuyang id:48197
    修改内容   : ARM获取内存内容需要从4字节对齐的位置起始，问题单号:A32D02119

  2.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 增加判断回调函数指针是否为空,问题单号:A32D02143

  3.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02382
  4.日    期   : 2011年10月4日
    作    者   : c00173809
    修改内容   : AT融合项目
  5.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  6.日    期   : 2012年9月19日
    作    者   : s00217060
    修改内容   : for V7R1C50_At_Abort
  7.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  8.日    期   : 2015年3月4日
    作    者   : b00269685
    修改内容   : list search 改为分段上报
**********************************************************/
VOS_UINT32 MMA_PhoneProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent= VOS_NULL_PTR;
    VOS_UINT8                           ucError = TAF_ERR_NO_ERROR;
    VOS_UINT8                          *pucTmp  = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpAddr;
    /*增加电话处理过程变量*/
    TAF_PH_PIN_DATA_STRU                stPinData;
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalData;
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          ClientId;
    VOS_UINT8                           OpId;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg= VOS_NULL_PTR;

    PS_MEM_SET(&stPinData, 0, sizeof(TAF_PH_PIN_DATA_STRU));
    PS_MEM_SET(&stMePersonalData, 0, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    usMsgType   = pstRcvMsg->usMsgName;
    ClientId    = pstRcvMsg->clientId;
    OpId        = pstRcvMsg->opId;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_PhoneProc():ERROR:ALLOC MEMORY FAIL!");

        return VOS_TRUE;
    }

    pucTmp = &(pstRcvMsg->aucContent[0]);
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

    switch(usMsgType)
    {


        case TAF_MSG_MMA_OP_PIN_REQ:
            ulTmpAddr = (VOS_UINT32)pucTmp;
            MMA_MEM_CPY((VOS_UINT8 *)&stPinData, (VOS_UINT8 *)ulTmpAddr, sizeof(TAF_PH_PIN_DATA_STRU));
            MMA_PinHandle(ClientId, OpId,stPinData);
            break;
        case TAF_MSG_MMA_ME_PERSONAL_REQ:
            ulTmpAddr = (VOS_UINT32)pucTmp;
            MMA_MEM_CPY((VOS_UINT8 *)&stMePersonalData, (VOS_UINT8 *)ulTmpAddr, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));
            MMA_MePersonalisationHandle(ClientId, OpId,stMePersonalData);
            break;



        /* Deleted by w00167002 for L-C互操作项目, 2014-2-17, begin */
        /* Deleted by w00167002 for L-C互操作项目, 2014-2-17, end */


        default:

            ucError = TAF_ERR_CMD_TYPE_ERROR;
            break;
    }
    if (TAF_ERR_NO_ERROR != ucError)
    {
        Taf_InitEventInfoOP(pstPhoneEvent);
        pstPhoneEvent->OP_PhoneError      = 1;
        pstPhoneEvent->PhoneEvent         = TAF_PH_EVT_ERR;
        pstPhoneEvent->ClientId           = ClientId;
        pstPhoneEvent->OpId               = OpId;
        pstPhoneEvent->PhoneError         = ucError;

        /* 调用电话管理上报函数 */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*TAF_MMA_PnnListMemProtectTimerExpired*/

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvDelayPowerDownTimerExpired
 功能描述  : E5调用底软下电接口时，将TASKDELAY修改为定时器处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : w00167002
    修改内容   : DTS2013092100149:新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_RcvDelayPowerDownTimerExpired(VOS_VOID)
{
    /* 调用API接口进行下电关机 */
    mdrv_sysboot_poweroff();
}

/**********************************************************
 Function:       MMA_TimeExpired
 Description:    MMA定时器超时函数处理
 Calls:          TAFM
 Data Accessed:
 Data Updated:
 Input:          pMsg - 定时器超时消息指针
 Output:
 Return:
 Others:

  1.日    期   : 2006年3月2日
    作    者   : liuyang id:48197
    修改内容   : 增加内部定时器超时处理

  2.日    期   : 2010年3月12日
    作    者   : zhoujun /z40661
    修改内容   : VOS_TaskDelay清理

  3.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : AT&T&DCM:增加定时器的处理
  4.日    期   : 2013年9月5日
    作    者   : l00208543
    修改内容   : DTS2013090309526
  5.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  6.日    期   : 2015年2月26日
    作    者   : b00269685
    修改内容   : 新增读取 pnn和opl文件的定时器
**********************************************************/
VOS_UINT32 MMA_TimeExpired(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    REL_TIMER_MSG                      *pMsg;

    pMsg = (REL_TIMER_MSG*)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

    switch(pMsg->ulPara)
    {
        case TAF_USIM_OPPIN:
            MMA_OpPinExpired();
            break;



        case MMA_INTERNAL_TIMER_ID :
            MMA_ExpiredInternalTimer();
            break;
        case MMA_TIMER_FOR_PC_REPLAY :
            /* 输出回放消息 */
#ifndef __PS_WIN32_RECUR__

            /* 已与PC工具连接, 且PC工具侧使能了NAS PC回放消息的发送 */
            if ( (VOS_TRUE == g_ucMmaOmConnectFlg)
              && (VOS_TRUE == g_ucMmaOmPcRecurEnableFlg) )
            {
                NAS_MMA_SndOutsideContextData();
            }

#endif
            break;
        case TI_MN_PH_RESET:
            MN_PH_ResetTimerOutProc();
            break;
        case TI_MN_PH_PIN_OPER:
            MN_PH_PinOperTimerOutProc();
            break;



        case TI_TAF_MMA_DELAY_POWER_DOWN:
            TAF_MMA_RcvDelayPowerDownTimerExpired();
            break;


        case TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU:
            TAF_MMA_NetworkSelectionMenuCtrlTimerExpired();
            break;

        case TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING:
            TAF_MMA_RatBalancingCtrlTimerExpired();
            break;

        case TI_TAF_MMA_NET_SCAN_TIMER:
            TAF_MMA_NetScanTimerExpired();
            break;

        case TI_TAF_MMA_ABORT_NET_SCAN_TIMER:
            TAF_MMA_AbortNetScanTimerExpired();
            break;

        default:
            Sta_TimeoutProc(pMsg);
            break;
    }
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsEventNeedRpt
 功能描述  : 呼叫过程中的事件是否需要上报
 输入参数  : pEvent - 事件类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要上报；
             VOS_TRUE:需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2013年8月15日
    作    者   : l00208543
    修改内容   : 新增AT^REJINFO的控制分支
  3.日    期   : 2013年10月09日
    作    者   : l00208543
    修改内容   : DTS2013100904573

  4.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 拆分主动上报的判断
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsEventNeedRpt(
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
)
{
    VOS_UINT32                          ulResult;

    ulResult                = VOS_TRUE;

    switch (pEvent->PhoneEvent)
    {


        /* 卡状态上报 */
        case TAF_PH_EVT_USIM_INFO_IND:

            ulResult = TAF_MMA_IsSimStaChangeNeedRpt();

            break;

        default:
            ulResult = VOS_TRUE;
    }

    return ulResult;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/*lint -e429 -e830*/

/**********************************************************
 Function:       Taf_PhoneEvent
 Description:    TAF向APP发送PHONE事件函数
 Calls:          STATUS module
 Data Accessed:
 Data Updated:
 Input:          pEvent - 上报事件
 Output:
 Return:
 Others:

  1.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 上报事件未填充ClientId与OpID，问题单号:A32D02202
  2.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D02382
  3.日    期   : 2007年09月30日
    作    者   : Z100318
    修改内容   : 问题单号:A32D12964
  4.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  5.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : AT&T&DCM:增加TAF_PH_EVT_NSM_STATUS_IND事件
  6.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 增加ACINFO主动上报事件
  7.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
  8.日    期   : 2013年8月1日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:开关机的模式设置回复在状态机中处理
  8.日    期   : 2015年3月5日
    作    者   : b00269685
    修改内容   : 列表搜改为分段上报
**********************************************************/
VOS_VOID  Taf_PhoneEvent (TAF_PHONE_EVENT_INFO_STRU  *pEvent)
{

    VOS_UINT8 ucTi;
    VOS_UINT16 ClientId;
    VOS_UINT8 AppOpId;
    TAF_PHONE_EVENT PhoneEvent;

    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(pEvent->aucCurcRptCfg, pstCurcRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    PS_MEM_CPY(pEvent->aucUnsolicitedRptCfg, pstUnsolicitedRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    ucTi = pEvent->OpId;
    switch(pEvent->PhoneEvent)
    {
        case TAF_PH_EVT_SERVICE_STATUS_IND:
        /*新增的注册状态、信号质量、电池电量属于广播消息，*/
        case TAF_PH_EVT_PLMN_LIST_IND:
        case TAF_PH_EVT_POWER_STA_IND:
        case MN_PH_EVT_SIMLOCKED_IND:
        case MN_PH_EVT_ROAMING_IND:
        case TAF_PH_EVT_NSM_STATUS_IND:
        /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
            AppOpId = MMA_OP_ID_INTERNAL;
            ClientId = MMA_CLIENTID_BROADCAST;
            break;
         case TAF_PH_EVT_OP_PINREMAIN_CNF :
            ucTi = MMA_PH_PIN_TI;
            if (TAF_SUCCESS != MMA_GetIdByTi(TAF_MMA, ucTi, &ClientId, &AppOpId,&PhoneEvent))
            {
                MMA_WARNINGLOG("Taf_PhoneEvent():WARNING:Invoke Taf_GetIdByTi failed.");
                return;
            }
            break;


        /*PIN操作的结构已经填充完成，考虑到PIN的某些操作,更改密码等会与其他事件
        并发，不使用PHONE EVENT事件结构体内包含了ClientId和OpId*/
        case TAF_PH_EVT_OP_PIN_CNF :
            ucTi = MMA_PH_PIN_TI;
            if (TAF_SUCCESS != MMA_GetIdByTi(TAF_MMA, ucTi, &ClientId, &AppOpId,&PhoneEvent))
            {
                MMA_WARNINGLOG("Taf_PhoneEvent():WARNING:Invoke Taf_GetIdByTi failed.");
                return;
            }
            break;
        /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */

        /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */
        /*TAF_PH_EVT_STOP_CNF, TAF_PH_EVT_START_CNF事件
        会走此分支, 此类事件没有具体参数*/
        default:
            if (ucTi > TAF_MAX_STATUS_TI)
            {   /*不是APP主动发起，直接返回*/
                return;
            }
            /*通过Ti获取ClientId,CallId*/
            if (TAF_SUCCESS != MMA_GetIdByTi(TAF_MMA, ucTi, &ClientId, &AppOpId,&PhoneEvent))
            {
                MMA_WARNINGLOG("Taf_PhoneEvent():WARNING:Invoke Taf_GetIdByTi failed.");
                return;
            }
            break;
    }

    pEvent->ClientId  = ClientId;
    pEvent->OpId      = AppOpId;

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pEvent->ClientId,(VOS_UINT8*)pEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    return;
}
/*lint +e429 +e830*/

/* MMA_DefPhClassType函数不再使用，删除 */


/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtSubPnnList
 功能描述  : 根据AT下发的分批查询参数分批次给AT发送PNN LIST
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月05日
    作    者   : l00208543
    修改内容   : DTS2013090309526 新生成函数
  2.日    期   : 2015年2月17日
    作    者   : b00269685
    修改内容   : at&t修改
*****************************************************************************/
VOS_VOID TAF_MMA_SndAtSubPnnList(
    VOS_UINT32                   ulSndNum,
    TAF_SDC_PNN_FILE_INFO_STRU  *pstPnnFileInfo
)
{
    TAF_PH_USIM_PNN_CNF_STRU           *pstPNN = VOS_NULL_PTR;
    VOS_UINT16                          usCurrIndex;
    VOS_UINT16                          i;

    i           = 0;
    usCurrIndex = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex;

    pstPNN = (TAF_PH_USIM_PNN_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
              sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulSndNum));

    if(VOS_NULL_PTR == pstPNN)
    {
        MMA_ReportParaQueryError(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);


        return;
    }

    MMA_MEM_SET(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulSndNum));

    pstPNN->TotalRecordNum            = ulSndNum;
    pstPNN->usPnnCurrIndex            = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex;
    pstPNN->Icctype                   = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.Icctype;

    for (i = 0; i < ulSndNum; i++)
    {
        pstPNN->PNNRecord[i].stOperNameShort.ucLength  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.ucLength;    /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameShort.bitExt    = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitExt;      /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameShort.bitCoding = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitCoding;   /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameShort.bitAddCi  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitAddCi;    /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameShort.bitSpare  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitSpare;    /* [false alarm]:通过动态申请内存的结果  */

        PS_MEM_CPY(pstPNN->PNNRecord[i].stOperNameShort.aucOperatorName,
                   pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.aucOperatorName,
                   TAF_SDC_MAX_OPER_NAME_NUM);

        pstPNN->PNNRecord[i].stOperNameLong.ucLength  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.ucLength;      /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameLong.bitExt    = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitExt;        /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameLong.bitCoding = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitCoding;     /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameLong.bitAddCi  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitAddCi;      /* [false alarm]:通过动态申请内存的结果  */
        pstPNN->PNNRecord[i].stOperNameLong.bitSpare  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitSpare;      /* [false alarm]:通过动态申请内存的结果  */

        PS_MEM_CPY(pstPNN->PNNRecord[i].stOperNameLong.aucOperatorName,
                   pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.aucOperatorName,
                   TAF_SDC_MAX_OPER_NAME_NUM);

        pstPNN->PNNRecord[i].ucPlmnAdditionalInfoLen = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].ucPlmnAdditionalInfoLen;           /* [false alarm]:通过动态申请内存的结果  */

        PS_MEM_CPY(pstPNN->PNNRecord[i].aucPlmnAdditionalInfo,
                   pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].aucPlmnAdditionalInfo,
                   TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN);
    }

    MMA_ParaQueryReport(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                        TAF_PH_PNN_PARA, TAF_ERR_NO_ERROR, pstPNN);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPNN);

}


/* TAF_MMA_ClearcPnnListQryCtrInfo */
/* TAF_MMA_PnnListMemProtectTimerProc */

/*****************************************************************************
 函 数 名  : TAF_MMA_AtQryPnnProc
 功能描述  : at^pnn=?处理
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : b00269685
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_AtTestPnnProc()
{
    TAF_SDC_PNN_FILE_INFO_STRU         *pstUsimPnnFileInfo = VOS_NULL_PTR;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstSimPnnFileInfo  = VOS_NULL_PTR;
    TAF_PH_QRY_USIM_RANGE_INFO_STRU     stQryRangeInfo;

    PS_MEM_SET(&stQryRangeInfo, 0, sizeof(stQryRangeInfo));

    pstUsimPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    pstSimPnnFileInfo  = TAF_SDC_GetSimPnnFileInfo();

    if (0 != pstUsimPnnFileInfo->ulPnnRecordNum)
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_TRUE;
        stQryRangeInfo.stUsimInfo.Icctype       = TAF_PH_ICC_USIM;
        stQryRangeInfo.stUsimInfo.ulTotalRecNum = pstUsimPnnFileInfo->ulPnnRecordNum;
        stQryRangeInfo.stUsimInfo.ulRecordLen   = pstUsimPnnFileInfo->ulPnnEfLen;
    }
    else
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_FALSE;
    }

    if (0 != pstSimPnnFileInfo->ulPnnRecordNum)
    {
        stQryRangeInfo.stSimInfo.bFileExist     = VOS_TRUE;
        stQryRangeInfo.stSimInfo.Icctype        = TAF_PH_ICC_SIM;
        stQryRangeInfo.stSimInfo.ulTotalRecNum  = pstSimPnnFileInfo->ulPnnRecordNum;
        stQryRangeInfo.stSimInfo.ulRecordLen    = pstSimPnnFileInfo->ulPnnEfLen;
    }
    else
    {
        stQryRangeInfo.stSimInfo.bFileExist    = VOS_FALSE;
    }

    MMA_ParaQueryReport(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId, TAF_PH_PNN_RANGE_PARA, TAF_ERR_NO_ERROR, &stQryRangeInfo);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_AtTestOplProc
 功能描述  : at^opl=?处理
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月2日
    作    者   : b00269685
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_AtTestOplProc()
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstUsimOplFileInfo = VOS_NULL_PTR;
    TAF_SDC_OPL_FILE_INFO_STRU         *pstSimOplFileInfo  = VOS_NULL_PTR;
    TAF_PH_QRY_USIM_RANGE_INFO_STRU     stQryRangeInfo;

    PS_MEM_SET(&stQryRangeInfo, 0, sizeof(stQryRangeInfo));

    pstUsimOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
    pstSimOplFileInfo  = TAF_SDC_GetSimOplFileInfo();

    if (0 != pstUsimOplFileInfo->ulOplRecordNum)
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_TRUE;
        stQryRangeInfo.stUsimInfo.Icctype       = TAF_PH_ICC_USIM;
        stQryRangeInfo.stUsimInfo.ulTotalRecNum = pstUsimOplFileInfo->ulOplRecordNum;
        stQryRangeInfo.stUsimInfo.ulRecordLen   = pstUsimOplFileInfo->ulOplEfLen;
    }
    else
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_FALSE;
    }

    if (0 != pstSimOplFileInfo->ulOplRecordNum)
    {
        stQryRangeInfo.stSimInfo.bFileExist     = VOS_TRUE;
        stQryRangeInfo.stSimInfo.Icctype        = TAF_PH_ICC_SIM;
        stQryRangeInfo.stSimInfo.ulTotalRecNum  = pstSimOplFileInfo->ulOplRecordNum;
        stQryRangeInfo.stSimInfo.ulRecordLen    = pstSimOplFileInfo->ulOplEfLen;
    }
    else
    {
        stQryRangeInfo.stSimInfo.bFileExist    = VOS_FALSE;
    }

    MMA_ParaQueryReport(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId, TAF_PH_OPL_RANGE_PARA, TAF_ERR_NO_ERROR, &stQryRangeInfo);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_AtQryPnnProc
 功能描述  : 根据AT下发的分批查询参数分批次给AT发送PNN LIST
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月05日
    作    者   : l00208543
    修改内容   : DTS2013090309526 新生成函数
  2.日    期   : 2015年2月17日
    作    者   : b00269685
    修改内容   : at&t phaseII修改
*****************************************************************************/
VOS_VOID TAF_MMA_AtQryPnnProc(TAF_PH_QRY_USIM_INFO_STRU *pstInfo)
{
    VOS_UINT32                          ulSndNum; /* 本次发送的Pnn数目 */
    VOS_UINT16                          usUnSentNum;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;

    ulSndNum               = 0;
    usUnSentNum            = 0;

    if (TAF_PH_ICC_SIM == pstInfo->Icctype)
    {
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }
    else if (TAF_PH_ICC_USIM == pstInfo->Icctype)
    {
        pstPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    }
    else
    {
        MMA_ReportParaQueryError(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);

        return;
    }

    if ((0 == pstPnnFileInfo->ulPnnRecordNum)
     || (pstPnnFileInfo->ulPnnRecordNum < pstInfo->ulRecNum))
    {
        MMA_ReportParaQueryError(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);

        return;
    }

    /* 如果不是要求读取PNN列表，则上报单个记录 */
    if (0 != pstInfo->ulRecNum)
    {
        gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex = (VOS_UINT16)pstInfo->ulRecNum - 1;

        ulSndNum = 1;
        TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);

        return;
    }

    gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex = pstInfo->stPnnQryIndex.usPnnCurrIndex;
    gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usReadNum   = pstInfo->stPnnQryIndex.usPnnNum;
    gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.Icctype     = pstInfo->Icctype;

    if (0 == pstPnnFileInfo->ulPnnRecordNum)
    {
        MMA_WARNINGLOG("TAF_MMA_AtQryPnnListProc():The PNN LIST is empty!");

        TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);
        return;
    }

    /* 如果要求读取的index大于等于PNN的总数目，认为是最后一次上报，上报一个空列表，并停止保护定时器 */
    if (gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex >= (VOS_UINT16)pstPnnFileInfo->ulPnnRecordNum)
    {
        MMA_WARNINGLOG("TAF_MMA_AtQryPnnListProc():There is no unsent pnn in the list!");

        ulSndNum               = 0;
        TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);


        return;
    }

    /* 如果PNN LIST总数目减去AT下发的INDEX大于等于AT要求读取的数目，则上报AT要求读取的数目 */
    usUnSentNum = (VOS_UINT16)pstPnnFileInfo->ulPnnRecordNum - gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex;

    if (usUnSentNum >= gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usReadNum)
    {
        ulSndNum = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usReadNum;
    }
    else
    {
        ulSndNum               = usUnSentNum;
    }

    TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);

}

/*****************************************************************************
 函 数 名  : TAF_MMA_AtQryOplProc
 功能描述  : 给at发送opl
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月17日
    作    者   : b00269685
    修改内容   : 新增函数
  2.日    期   : 2015年10月08日
    作    者   : zwx247453
    修改内容   : 清除Coverity告警
*****************************************************************************/
VOS_VOID TAF_MMA_AtQryOplProc(TAF_PH_QRY_USIM_INFO_STRU *pstInfo)
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    TAF_PH_USIM_OPL_CNF_STRU           *pstOPL;
    VOS_UINT8                           ucSimType;
    VOS_UINT32                          ulBeginIndex;
    VOS_UINT32                          i;

    ucSimType = 0;
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if (TAF_PH_ICC_SIM == pstInfo->Icctype)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
    }
    else if (TAF_PH_ICC_USIM == pstInfo->Icctype)
    {
        pstOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
    }
    else
    {
        MMA_ReportParaQueryError(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);

        return;
    }

    if ((0 == pstOplFileInfo->ulOplRecordNum)
     || (pstOplFileInfo->ulOplRecordNum < pstInfo->ulRecNum))
    {
        MMA_ReportParaQueryError(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);

        return;
    }

    pstOPL = (TAF_PH_USIM_OPL_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_MMA, DYNAMIC_MEM_PT,
                                sizeof(TAF_PH_USIM_OPL_CNF_STRU) + (sizeof(TAF_PH_USIM_OPL_RECORD) * pstOplFileInfo->ulOplRecordNum));

    if(VOS_NULL_PTR == pstOPL)
    {
        MMA_ReportParaQueryError(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);

        return;
    }

    MMA_MEM_SET(pstOPL, 0, sizeof(TAF_PH_USIM_OPL_CNF_STRU) + (sizeof(TAF_PH_USIM_OPL_RECORD) * pstOplFileInfo->ulOplRecordNum));

    pstOPL->CardType  = ucSimType;
    pstOPL->cWildCard = TAF_SDC_GetPlmnCompareWildCard();

    if (0 != pstInfo->ulRecNum)
    {
        /* 指定索引上报 */
        ulBeginIndex           = pstInfo->ulRecNum - 1;
        pstOPL->TotalRecordNum = 1;

        /* 转化为上报的格式 */
        pstOPL->OPLRecord[0].PLMN[0]  =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMcc & 0xFF;
        pstOPL->OPLRecord[0].PLMN[1]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMcc & 0xFF00) >> 8;
        pstOPL->OPLRecord[0].PLMN[2]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMcc & 0xFF0000) >> 16;
        pstOPL->OPLRecord[0].PLMN[3]  =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMnc & 0xFF;
        pstOPL->OPLRecord[0].PLMN[4]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMnc & 0xFF00) >> 8;
        pstOPL->OPLRecord[0].PLMN[5]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMnc & 0xFF0000) >> 16;
        pstOPL->OPLRecord[0].PlmnLen  =  6;
        if ((pstOPL->OPLRecord[0].PLMN[5] >= 0xA)
         && (pstOPL->OPLRecord[0].PLMN[5] <= 0xF))
        {
            pstOPL->OPLRecord[0].PLMN[5] = 0xF;
            pstOPL->OPLRecord[0].PlmnLen = 5;
        }
        pstOPL->OPLRecord[0].LACLow   =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].usLacRangeLow;
        pstOPL->OPLRecord[0].LACHigh  =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].usLacRangeHigh;
        pstOPL->OPLRecord[0].PNNIndex =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].usPnnIndex;

        MMA_ParaQueryReport(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                        TAF_PH_OPL_PARA, TAF_ERR_NO_ERROR, pstOPL);

        PS_MEM_FREE(WUEPS_PID_MMA, pstOPL);

        return;

    }

    /* 全部上报 */
    ulBeginIndex           = 0;
    pstOPL->TotalRecordNum = pstOplFileInfo->ulOplRecordNum;

    for (i = ulBeginIndex; i < pstOPL->TotalRecordNum; i++)
    {
        /* 转化为上报的格式 */
        pstOPL->OPLRecord[i].PLMN[0]  =  pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMcc & 0xFF;                 /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PLMN[1]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMcc & 0xFF00) >> 8;        /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PLMN[2]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMcc & 0xFF0000) >> 16;     /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PLMN[3]  =  pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMnc & 0xFF;                 /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PLMN[4]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMnc & 0xFF00) >> 8;        /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PLMN[5]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMnc & 0xFF0000) >> 16;     /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PlmnLen  =  6;                                                                         /* [false alarm]:通过动态申请内存的结果  */
        if ((pstOPL->OPLRecord[i].PLMN[5] >= 0xA)
         && (pstOPL->OPLRecord[i].PLMN[5] <= 0xF))
        {
            pstOPL->OPLRecord[i].PLMN[5] = 0xF;                                                                     /* [false alarm]:通过动态申请内存的结果  */
            pstOPL->OPLRecord[i].PlmnLen = 5;                                                                       /* [false alarm]:通过动态申请内存的结果  */
        }
        pstOPL->OPLRecord[i].LACLow   =  pstOplFileInfo->astOplRecordInfo[i].usLacRangeLow;                         /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].LACHigh  =  pstOplFileInfo->astOplRecordInfo[i].usLacRangeHigh;                        /* [false alarm]:通过动态申请内存的结果  */
        pstOPL->OPLRecord[i].PNNIndex =  pstOplFileInfo->astOplRecordInfo[i].usPnnIndex;                            /* [false alarm]:通过动态申请内存的结果  */
    }

    MMA_ParaQueryReport(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                    TAF_PH_OPL_PARA, TAF_ERR_NO_ERROR, pstOPL);

    PS_MEM_FREE(WUEPS_PID_MMA, pstOPL);

    return;
}


/* TAF_MMA_IsNeedSndGetUsimPnnFileReq */

/*****************************************************************************
 函 数 名  : TAF_MMA_IsTestCmdTypeOfUsimFile
 功能描述  : 根据记录数判断是否是USIM卡测试类型的AT命令(AT^pnn=?)
 输出参数  : TAF_PH_QRY_USIM_INFO_STRU             *pstInfo
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月6日
    作    者   : c00318887
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsTestCmdTypeOfUsimFile(
        TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    if (TAF_PH_INVALID_USIM_REC == pstInfo->ulRecNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : MMA_QryUsimInfo
 功能描述  : USIM的相关信息查询,包括PNN,OPL等信息
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年03月04日
    作    者   : H59254
    修改内容   : creat function
  2.日    期  : 2012年12月26日
    作    者  : 张鹏 id:00214637
    修改内容  : USIM对外接口函数变更的处理 ，
                Client ID 到 PID的转换处理 ，入参封装成结构体。
  3.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE 和usim接口调整修改
  5.日    期   : 2013年9月05日
    作    者   : l00208543
    修改内容   : DTS2013090309526，对AT读取PNN LIST和OPL LIST做分批处理，第一次请求时调用卡模块接口
                 读取PNN/OPL信息，以后的请求使用第一次请求时卡返回的结果
  6.日    期   : 2013年10月09日
    作    者   : l65478
    修改内容   : DTS2013100804956:OPL不存在,PNN存在时,PNN无法查询
  7.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口
  8.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
  9.日    期   : 2015年2月25日
    作    者   : b00269685
    修改内容   : at&t支持eons修改
*****************************************************************************/
VOS_VOID MMA_QryUsimInfo(
    VOS_UINT16        ClientId,
    VOS_UINT8         OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSimStatus;
    VOS_UINT32                          ulFileExist;
    TAF_PARA_TYPE                       enRptQryType;


    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_QryUsimInfo():WARNING:USIM is not Ready!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_PNN_PARA);
        return;
    }

    /*判断卡状态*/
    ulRet = MMA_PhoneGetUsimStatus(&ucSimStatus );
    if ( (ulRet           != MMA_SUCCESS )
       ||(MMA_USIM_ABSENT == ucSimStatus)
       )
    {
        MMA_WARNINGLOG("MMA_QryUsimInfo():WARNING:USIM is Error or Absent!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                                 TAF_PH_PNN_PARA);
        return;
    }

    if (TAF_PH_PNN_FILE == pstInfo->enEfId)
    {

        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        ulFileExist = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_NTWRK_NAME);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

        enRptQryType = TAF_PH_PNN_PARA;
    }
    else
    {

       /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
       ulFileExist = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_LIST);
       /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

       enRptQryType = TAF_PH_OPL_PARA;
    }

    if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulFileExist)
    {
        if (VOS_TRUE == MMA_IsNeedToDisplayCPHSOperNameStr())
        {
            /*使用CPHS文件的 SIM卡 PNN上报其6f14的值，Opl返回OK,与后台配合以满足CPHS的显示要求*/
            if (TAF_PH_PNN_FILE == pstInfo->enEfId)
            {
                MMA_ReportPNNParaFromCPHSOperNameStr(ClientId, OpId);
            }
            else
            {
                MMA_ReportOPLParaForCPHSDisplay(ClientId, OpId);
            }
        }
        else
        {
            MMA_WARNINGLOG("MMA_QryUsimInfo():WARNING:file not exist!");
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_FILE_NOT_EXIST,
                                     enRptQryType);
        }
        return;
    }

    /* 使用全局变量中存的内容上报 */
    switch (pstInfo->enEfId)
    {
        case TAF_PH_PNN_FILE:
            gstMmaValue.stPNN.ClientId = ClientId;
            gstMmaValue.stPNN.OpId     = OpId;

            if (VOS_TRUE == TAF_MMA_IsTestCmdTypeOfUsimFile(pstInfo))
            {
                /* at^pnn=?处理 */
                TAF_MMA_AtTestPnnProc();
            }
            else
            {
                TAF_MMA_AtQryPnnProc(pstInfo);
            }

            break;

        case TAF_PH_OPL_FILE:
            gstMmaValue.stOPL.ClientId = ClientId;
            gstMmaValue.stOPL.OpId     = OpId;

            if (VOS_TRUE == TAF_MMA_IsTestCmdTypeOfUsimFile(pstInfo))
            {
                /* at^opl=?处理 */
                TAF_MMA_AtTestOplProc();
            }
            else
            {
                TAF_MMA_AtQryOplProc(pstInfo);
            }

            break;

        default:
            MMA_WARNINGLOG("MMA_QryUsimInfo():efid not support");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MMA_CPnnQuery
 功能描述  : 当前注册PNN文件内容、记录数和记录长度查询
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年09月12日
    作    者   : l00130025
    修改内容   : 问题单AT2D14435,^CPNN命令的实现
  2.日    期   : 2009年11月12日
    作    者   : l00130025
    修改内容   : 问题单AT2D15416,OPL或Pnn文件不存在时，返回ERROR
  3.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，
                 Client ID 到 PID的转换处理 ，入参封装成结构体。
  4.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  5.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  6.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE 和usim接口调整修改
  5.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口
  6.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
  7.日    期   : 2015年2月26日
    作    者   : b00269685
    修改内容   : at&t修改
*****************************************************************************/
VOS_VOID MMA_CPnnQuery(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PH_ICC_TYPE                    *pIccType
)
{
    VOS_UINT32                      ulRet;
    VOS_UINT8                       ucSimStatus;
    VOS_UINT32                      ulPnnExistFlg;
    VOS_UINT32                      ulOplExistFlg;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_PnnQuery():WARNING:USIM is not Ready!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_CPNN_PARA);
        return;
    }

    /*判断卡状态*/
    ulRet = MMA_PhoneGetUsimStatus(&ucSimStatus );
    if ( (ulRet           != MMA_SUCCESS )
       ||(MMA_USIM_ABSENT == ucSimStatus)
       )
    {
        MMA_WARNINGLOG("MMA_PnnQuery():WARNING:USIM is Error or Absent!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                                 TAF_PH_CPNN_PARA);
        return;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsServiceStatus) )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_CPNN_PARA);
        return;
    }
    else
    {
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
        ulPnnExistFlg = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_NTWRK_NAME);
        ulOplExistFlg = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_LIST);
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

        if ( (PS_USIM_SERVICE_NOT_AVAILIABLE == ulPnnExistFlg)
            || (PS_USIM_SERVICE_NOT_AVAILIABLE == ulOplExistFlg) )
        {
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_UNSPECIFIED_ERROR,
                                     TAF_PH_CPNN_PARA);
            return;
        }

        MMA_CPnnReport(*pIccType, ClientId, OpId);

        return;
    }
}

/*MMA_GetPlmnIdxInOplList*/



/*****************************************************************************
 函 数 名  : MMA_CPnnReport
 功能描述  : 上报当前注册PLMN对应的PNN内容
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年09月12日
    作    者   : l00130025
    修改内容   : 问题单AT2D14435,^CPNN命令的实现
  2.日    期   : 2009年11月12日
    作    者   : l00130025
    修改内容   : 问题单AT2D15416,在Vplmn上且无法找到对应PNN时^CPNN查询应返回ERROR
  3.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2014年3月21日
    作    者   : z00161729
    修改内容   : DTS2014032105704:国内TDS丢网瞬间找回原小区ps迁移modem1后不再回迁modem0
  5.日    期   : 2015年2月25日
    作    者   : b00269685
    修改内容   : at&t修改
*****************************************************************************/
VOS_VOID MMA_CPnnReport(
    TAF_PH_ICC_TYPE                     ucIccType,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;
    TAF_PH_USIM_PNN_CNF_STRU           *pstPNN         = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamFlag;
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmInfoPlmnName;
    VOS_UINT32                          ulPnnIndex;

    if (TAF_PH_ICC_SIM == ucIccType)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }
    else if (TAF_PH_ICC_USIM == ucIccType)
    {
        pstOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
        pstPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    }
    else
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;
    }

    pstPNN   = (TAF_PH_USIM_PNN_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_MMA, DYNAMIC_MEM_PT,
                                                        sizeof(TAF_PH_USIM_PNN_CNF_STRU));
    if (VOS_NULL_PTR == pstPNN)
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;
    }

    PS_MEM_SET(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU));
    PS_MEM_SET(&stMmInfoPlmnName, 0, sizeof(stMmInfoPlmnName));

    pstPNN->TotalRecordNum = 0;
    ucRoamFlag             = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());

    /* OPL和PNN文件记录个数为0返回失败 */
    if ((0 == pstPnnFileInfo->ulPnnRecordNum)
     && (0 == pstOplFileInfo->ulOplRecordNum))
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;
    }

    /* OPL文件记录为0，PNN文件记录不为0且驻留hplmn上，返回PNN文件第一条记录对应的运营商名称 */
    if ((0 == pstOplFileInfo->ulOplRecordNum)
     && (TAF_PH_NO_ROAM == ucRoamFlag))
    {
        ulPnnIndex = 1;
    }
    else
    {
        /* OPL和PNN文件记录都不为0 */
        ulPnnIndex = TAF_MMA_GetPlmnPnnIndexInOplFile(TAF_SDC_GetAppServicePlmnId(), pstOplFileInfo);
    }

    /* 从OPL中获取的PNN index非法，最大支持100个，返回失败 */
    if ((ulPnnIndex < TAF_SDC_VALID_PNN_LOW_INDEX)
     || (ulPnnIndex > TAF_SDC_PNN_MAX_RECORD_NUM))
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;

    }

    pstPNN->TotalRecordNum= 1;
    pstPNN->PNNRecord[0].stOperNameLong.bitExt     = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitExt;
    pstPNN->PNNRecord[0].stOperNameLong.bitCoding  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitCoding;
    pstPNN->PNNRecord[0].stOperNameLong.bitAddCi   = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitAddCi;
    pstPNN->PNNRecord[0].stOperNameLong.bitSpare   = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitSpare;
    pstPNN->PNNRecord[0].stOperNameLong.ucLength   = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.ucLength;
    PS_MEM_CPY(pstPNN->PNNRecord[0].stOperNameLong.aucOperatorName, pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.aucOperatorName, TAF_SDC_MAX_OPER_NAME_NUM);

    pstPNN->PNNRecord[0].stOperNameShort.bitExt    = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitExt;
    pstPNN->PNNRecord[0].stOperNameShort.bitCoding = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitCoding;
    pstPNN->PNNRecord[0].stOperNameShort.bitAddCi  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitAddCi;
    pstPNN->PNNRecord[0].stOperNameShort.bitSpare  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitSpare;
    pstPNN->PNNRecord[0].stOperNameShort.ucLength  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.ucLength;

    PS_MEM_CPY(pstPNN->PNNRecord[0].stOperNameShort.aucOperatorName, pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.aucOperatorName, TAF_SDC_MAX_OPER_NAME_NUM);

    pstPNN->PNNRecord[0].ucPlmnAdditionalInfoLen = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].ucPlmnAdditionalInfoLen;
    PS_MEM_CPY(pstPNN->PNNRecord[0].aucPlmnAdditionalInfo, pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].aucPlmnAdditionalInfo, TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN);

    MMA_ParaQueryReport(usClientId, ucOpId,
                        TAF_PH_CPNN_PARA, TAF_ERR_NO_ERROR, pstPNN);

    return;
}

/*****************************************************************************
 函 数 名  : Mma_LoadDefault
 功能描述  :
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月25日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2013年4月4日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
  4.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  5.日    期   : 2014年8月1日
    作    者   : b00269685
    修改内容   : NV项拆分
*****************************************************************************/
VOS_VOID Mma_LoadDefault(VOS_VOID)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stSetBand;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulAutoSwitchOnFlg;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

    /*set default value:+CGCLASS*/
    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = TAF_PH_MS_CLASS_A;
    ulLength    = 0;

    gstMmaValue.stSetMsClass.NewMsClassType = stMsClass.ucMsClass;
    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);

    if (NV_OK != NV_Write(en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:Write NV:MsClass FAIL!");
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    stPlmnSelMode.usSelPlmnMode = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */
    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulLength);

    if (NV_OK != NV_Write (en_NV_Item_SelPlmn_Mode, &stPlmnSelMode, ulLength))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:Write NV:SelPlmn_Mode, FAIL!");
    }


    stSetBand.unGsmBand.BitBand.BandGsm850 = 1;
    stSetBand.unGsmBand.BitBand.BandGsmP900 = 1;
    stSetBand.unGsmBand.BitBand.BandGsmR900 = 1;
    stSetBand.unGsmBand.BitBand.BandGsmE900 = 1;
    stSetBand.unGsmBand.BitBand.BandGsm1800 = 1;
    stSetBand.unGsmBand.BitBand.BandGsm1900 = 1;

    stSetBand.unWcdmaBand.BitBand.BandWCDMA_I_2100 = 1;
    stSetBand.unWcdmaBand.BitBand.BandWCDMA_II_1900 = 1;
    stSetBand.unWcdmaBand.BitBand.BandWCDMA_V_850 = 1;

    PS_MEM_SET(stSetBand.aucReserved1, 0, sizeof(stSetBand.aucReserved1));
    PS_MEM_SET(stSetBand.aucReserved2, 0, sizeof(stSetBand.aucReserved2));

    /* 更新频段NV */
    if (NV_OK != NV_Write(en_NV_Item_Support_Freqbands,
                          &(stSetBand),
                          sizeof(TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU)))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:NVIM_Write en_NV_Item_Support_Freqbands failed");
    }

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    ulAutoSwitchOnFlg = MMA_RF_AUTO_TEST_DISABLE;
    (VOS_VOID)NV_GetLength(en_NV_Item_RF_Auto_Test_Flag, &ulLength);

    if (NV_OK != NV_Write(en_NV_Item_RF_Auto_Test_Flag,
            (VOS_VOID*)(&ulAutoSwitchOnFlg),
            ulLength))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:NVIM_Write en_NV_Item_Support_Freqbands failed");
    }

    TAF_MMA_SetAutoSwitchOnFlg(ulAutoSwitchOnFlg);
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
}

/* Deleted by wx270776 for OM融合, 2015-7-17, begin */

/* Deleted by wx270776 for OM融合, 2015-7-17, end */


/*****************************************************************************
 函 数 名  : MMA_WriteGobalValue2Nvim
 功能描述  : 负责将需要记录的全局数据写入NVIM中
 输出参数  : const NV_ITEM_TYPE_ENUM enNVItemType, 类型号
             VOS_VOID *pData,                      参数缓冲区
             VOS_UINT16 usDataLen,                 数据长度
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月17日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02382
  3.日    期   : 2009年5月20日
    作    者   : h44270
    修改内容   : 问题单号：AT2D11987,修改NV项头文件，将PS/SYS/RF的NV项拆分出来，以便于维护
*****************************************************************************/
VOS_UINT32 MMA_WriteValue2Nvim(const NV_ID_ENUM_U16 enNVItemType,
                               VOS_VOID *pData, VOS_UINT16 usDataLen)
{
    VOS_UINT8* pNvTemp;
    VOS_UINT8* pDataTemp;
    VOS_UINT16 i;

    i = 0;
    pDataTemp = (VOS_UINT8*)pData;

    pNvTemp = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMA, usDataLen);

    if (VOS_NULL_PTR == pNvTemp)
    {
        MMA_ERRORLOG("MMA_WriteValue2Nvim:ERROR:ALLOC MEMORY FAIL.");
        return MMA_ERROR;
    }

    PS_MEM_SET(pNvTemp, 0, usDataLen);

    if ( NV_OK == NV_Read(enNVItemType, pNvTemp, usDataLen) )
    {
        for ( i = 0 ; i < usDataLen ; i++ )
        {
            if ( *(pDataTemp + i) != *(pNvTemp + i))
            {
                break;
            }
        }
    }

    MMC_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pNvTemp);

    if ( i == usDataLen )
    {
        MMA_INFOLOG("MMA_WriteValue2Nvim():The content to write is same as NV's");
        return MMA_SUCCESS;
    }

    if (NV_OK !=  NV_Write(enNVItemType, pData, usDataLen))
    {
         MMA_WARNINGLOG("MMA_WriteValue2Nvim():WARNING:Invoke NVIM Write function falied");
         return MMA_ERROR;
    }

    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : MMA_SyncMsClassTypeGolbalValue
 功能描述  : 更新全局变量gstMmaValue中有关手机类型的参数
 输入参数  : TAF_PH_MS_CLASS_TYPE MsClass
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月24日
    作    者   : liuyang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_UpdateMsClassTypeGolbalValue(TAF_PH_MS_CLASS_TYPE MsClass)
{
    /*更改设置参数标志位，同步全局参数*/
    gstMmaValue.pg_StatusContext->ucModeService             = MsClass;
    gstMmaValue.stSetMsClass.MsClassType                    = MsClass;
    gstMmaValue.stSetMsClass.NewMsClassType                 = MsClass;
    return;
}


/*****************************************************************************
 函 数 名  : MMA_ImsiToImsiStr
 功能描述  : 将全局变量的Imsi转换成字串形式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期  : 2009年7月3日
   作    者  : h44270
   修改内容  : creat function
 2.日    期   : 2013年4月1日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID MMA_ImsiToImsiStr(VOS_CHAR  *pcImsi)
{
    VOS_UINT32                          i;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    for (i = 1; i <9; i++)
    {
        /*lint -e961*/
        if (1 == i)
        {
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        else
        {
            *pcImsi++ = (pucImsi[i] & 0x0f) + 0x30;
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        /*lint +e961*/
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
}


/*****************************************************************************
 函 数 名  : MMA_GetCardLockCfgData
 功能描述  : 获取配置参数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 返回       :无
 修改历史      :
 1.日    期  : 2009年7月3日
   作    者  : h44270
   修改内容  : creat function
 2.日    期  : 2009年11月3日
   作    者  : l00130025,h44270
   修改内容  : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo卡状态返回
 3.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 4.日    期   : 2013年11月04日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_UINT32 MMA_GetCardLockCfgData(VOS_VOID)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU          stSimLockPlmnInfo;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU             stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;
    VOS_UINT32                                  ulResult;


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));
    PS_MEM_SET(&stCardLockStatus,  0x00, sizeof(stCardLockStatus));
    PS_MEM_SET(&stSimLockMaxTimes, 0x00, sizeof(stSimLockMaxTimes));

    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       (VOS_UINT32)(sizeof(stCardLockStatus)));
    if (NV_OK != ulResult)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "MMA_GetCardLockCfgData:WARNING: Not read sim lock status");
        return VOS_ERR;
    }
    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                       &stSimLockMaxTimes,
                       sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
        g_MmaNewValue.stSimLockMaxTimes.ulStatus = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        g_MmaNewValue.stSimLockMaxTimes = stSimLockMaxTimes;
    }

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockPlmnInfo.ulStatus = VOS_FALSE;
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
        PS_MEM_SET(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange, (VOS_CHAR)0xaa,
                       sizeof(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange));
    }
    else
    {
        g_MmaNewValue.stSimLockPlmnInfo = stSimLockPlmnInfo;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : Taf_GetSimLockStatus
 功能描述  : 当前Cardlock功能是否使能,支持AT^SIMLOCK使能状态查询命令,
             当en_NV_Item_CardlockStatus状态不等于永久解锁，
             且en_NV_Item_CustomizeSimLockPlmnInfo中Plmn信息,有效时返回1,代表激活,
             其他情况下返回0,非激活;
 输入参数  : VOS_BOOL *pbActiveFlg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月10日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 Taf_GetSimLockStatus(VOS_BOOL *pbActiveFlg)
{

    TAF_CUSTOM_CARDLOCK_STATUS_STRU             stCardLockStatus;
    VOS_UINT32                                  ulResult;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       (VOS_UINT32)(sizeof(stCardLockStatus)));

    if (NV_OK != ulResult)
    {
        MN_WARN_LOG("Taf_GetSimLockStatus:WARNING:  read sim lock status fail");
        return VOS_ERR;
    }

    if ((VOS_TRUE == MMA_IsSimLockPlmnInfoValid())
     && (NV_ITEM_ACTIVE == stCardLockStatus.ulStatus)
     && (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE != stCardLockStatus.enCardlockStatus))
    {
        *pbActiveFlg = VOS_TRUE;
    }
    else
    {
        *pbActiveFlg = VOS_FALSE;

    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : MMA_IsImsiLocked
 功能描述  : 判定当前的SIM卡是否非法
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 返回       :0  legal;
              1  illegal;
 修改历史      :
 1.日    期  : 2009年7月3日
   作    者  : h44270
   修改内容  : creat function
 2.日    期   : 2009年10月3日
   作    者   : h44270
   修改内容   : 问题单号：AT2D14891,锁卡在NV项未激活时，判定不正确
 3.日    期   : 2013年4月1日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_UINT32 MMA_IsImsiIllegal(VOS_VOID)
{
    VOS_UINT32                          i,j;
    VOS_UINT32                          ulRslt = VOS_FALSE;
    VOS_UINT8                           aucTmpImsi[20];
    VOS_INT                             CmpRslt1,CmpRslt2;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */


    if (VOS_FALSE == g_MmaNewValue.stSimLockPlmnInfo.ulStatus)
    {
        return VOS_FALSE;
    }

    /* 判定当前的IMSI是否和NV项的匹配 */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (0xAA == g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[0])
        {
            continue;
        }

        (VOS_VOID)VOS_MemSet(aucTmpImsi, 0x00, 20);
        for (j=0; j < 8; j++)
        {
            /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
            if (j < 7)
            {
                aucTmpImsi[j] = (VOS_UINT8)((pucImsi[j + 1] & 0xf0) + ((pucImsi[j + 2]) & 0x0f));
            }
            else
            {
                aucTmpImsi[j] = (VOS_UINT8)((pucImsi[j + 1] & 0xf0) + 0x0f);
            }
            /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

            if ((0x0f == (g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[j] & 0x0f))
             && (0xff != g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[j]))
            {
                aucTmpImsi[j] = (VOS_UINT8)((aucTmpImsi[j] & 0xf0) + 0x0f);
                j++;
                break;
            }


            if (0xff == g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[j])
            {
                break;
            }

        }

        CmpRslt1 = VOS_MemCmp(aucTmpImsi,
                              g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                              j);

        CmpRslt2 = VOS_MemCmp(aucTmpImsi,
                              g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                              j);

        if ((CmpRslt1>=0) && (CmpRslt2<=0))
        {
            ulRslt = VOS_FALSE;
            break;
        }
        else
        {
            ulRslt = VOS_TRUE;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MMA_IsEygptVdfImsiIllegal
 功能描述  : 埃及VDF定制的37组SIMLOCK
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月8日
    作    者   : h44270
    修改内容   : 创建函数
  2.日    期   : 2011年08月02日
    作    者   : f00179208
    修改内容   : 问题单:DTS2011080102535,【正向质量】memset的参数填写错误
*****************************************************************************/
VOS_UINT32 MMA_IsEygptVdfImsiIllegal()
{
    VOS_UINT32                          i;
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pacEygptVdf[]={"50503", "60202", "26202",
                                                        "20205", "21670", "27201",
                                                        "22210", "20404", "53001",
                                                        "26801", "21401", "23415",
                                                        "27801", "22601", "27602",
                                                        "54201", "23003", "20601",
                                                        "65501", "20810", "23201",
                                                        "24008", "21910", "23801",
                                                        "27403", "24405", "29340",
                                                        "41902", "42602", "28001",
                                                        "24802", "27001", "45406",
                                                        "52503", "28401", "23211",
                                                        "24421"};

    MMA_ImsiToImsiStr(acTmpImsi);
    for (i = 0; i < 37; i++)
    {
        if (0 == VOS_MemCmp(acTmpImsi, pacEygptVdf[i], 5))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMA_IsNorwayNetcomImsiIllegal
 功能描述  : 挪威Netcomm的SIMLOCK
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月8日
    作    者   : h44270
    修改内容   : 创建函数
  2.日    期   : 2011年08月02日
    作    者   : f00179208
    修改内容   : 问题单:DTS2011080102535,【正向质量】memset的参数填写错误
*****************************************************************************/
VOS_UINT32 MMA_IsNorwayNetcomImsiIllegal()
{
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcNorwayNetcomImsi = "24202";

    /*根据NETCOM的需求IMSI range: 24202xy ,Where x = 0-9 and y = 0-3,或者xy = 59,86我们只要判断
    IMSI的网络号和国家号为24202,并且y的范围为0-3就可以了,因为
    x的范围是0-9,即任意范围,所以不用判断.
    */
    MMA_ImsiToImsiStr(acTmpImsi);

    if (0 == VOS_MemCmp(acTmpImsi, pcNorwayNetcomImsi, 5))
    {
        if (((acTmpImsi[5] == 0x35) && (acTmpImsi[6] == 0x39) )
         || ((acTmpImsi[5] == 0x38) && (acTmpImsi[6] == 0x36) ) )
        {
            return VOS_FALSE;
        }

        if ((acTmpImsi[6] >= 0x30) && (acTmpImsi[6] <= 0x33))
        {
            return VOS_FALSE;
        }

    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : MMA_IsMexicoTelcelIllegal
 功能描述  : 墨西哥TELCEL的永久锁卡号段334020
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月8日
    作    者   : h44270
    修改内容   : 创建函数
  2.日    期   : 2011年08月02日
    作    者   : f00179208
    修改内容   : 问题单:DTS2011080102535,【正向质量】memset的参数填写错误
*****************************************************************************/
VOS_UINT32 MMA_IsMexicoTelcelIllegal()
{
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcMexicoTelcelImsi="334020";

    /* 墨西哥telce PLMN ID 334020 */
    MMA_ImsiToImsiStr(acTmpImsi);
    if (0 == VOS_MemCmp(acTmpImsi, pcMexicoTelcelImsi, 6))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMA_IsDominicaTelcelIllegal
 功能描述  : 多米尼加TELCEL的永久锁卡号段37002，33870，42502
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月8日
    作    者   : h44270
    修改内容   : 创建函数
  2.日    期   : 2011年08月02日
    作    者   : f00179208
    修改内容   : 问题单:DTS2011080102535,【正向质量】memset的参数填写错误
*****************************************************************************/
VOS_UINT32 MMA_IsDominicaTelcelIllegal()
{
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcDominicaTelcelImsi1="37002";
    VOS_CHAR                            *pcDominicaTelcelImsi2="42502";
    VOS_CHAR                            *pcDominicaTelcelImsi3="338070";
    VOS_INT32                           iImsiCmpRslt1,iImsiCmpRslt2,iImsiCmpRslt3;

    /*dominica permanet SIM Lock 37002, 42502, 338070*/
    MMA_ImsiToImsiStr(acTmpImsi);
    iImsiCmpRslt1 = VOS_MemCmp(acTmpImsi, pcDominicaTelcelImsi1, 5);
    iImsiCmpRslt2 = VOS_MemCmp(acTmpImsi, pcDominicaTelcelImsi2, 5);
    iImsiCmpRslt3 = VOS_MemCmp(acTmpImsi, pcDominicaTelcelImsi3, 6);
    if ((0 == iImsiCmpRslt1)
      ||(0 == iImsiCmpRslt2)
      ||(0 == iImsiCmpRslt3))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : Mma_VerifyPhonePersonalization
 功能描述  : AP-Modem形态下，判定当前的SIM卡是否被锁
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
             0  SIM卡未锁定;
             1  SIM卡被锁定;
 调用函数  :
 被调函数  :

 修改历史  :
 1.日    期   : 2012年04月07日
   作    者   : L47619
   修改内容   : AP-Modem锁网锁卡项目新增函数
 2.日    期   : 2013年8月15日
   作    者   : w00242748
   修改内容   : 接口调整
*****************************************************************************/
VOS_UINT32 Mma_VerifyPhonePersonalization(VOS_VOID)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockResult;
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId  = VOS_GetModemIDFromPid(WUEPS_PID_MMA);
    enScResult = SC_PERS_VerifySimLock(&enVerifySimlockResult, enModemId);

    /* 调用SC接口进行锁卡校验，若函数执行失败，则按照SIM卡被锁定处理 */
    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        return VOS_TRUE;
    }

    /* 根据校验结果返回SIM卡是否被锁 */
    switch (enVerifySimlockResult)
    {
        case SC_VERIFY_SIMLOCK_RESULT_READY:
            ulResult = VOS_FALSE;
            break;

        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            ulResult = VOS_TRUE;
            break;

        default:
            /* 无效值，按照SIM卡被锁进行处理 */
            ulResult = VOS_TRUE;
            break;
    }

    return ulResult;
}


/*****************************************************************************
 函 数 名  : Mma_IsImsiLocked
 功能描述  : 判定当前的SIM卡是否被锁(根据IMSI)
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 返回       :0  IMSI not locked;
              1  IMSI locked;
 修改历史      :
  1.日    期  : 2009年7月3日
    作    者  : h44270
    修改内容  : 问题单AT2D12366
  2.日    期  : 2009年11月3日
    作    者  : l00130025,h44270
    修改内容  : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo卡状态返回
  4.日    期   : 2011年08月02日
    作    者   : f00179208
    修改内容   : 问题单:DTS2011080102535,【正向质量】memset的参数填写错误
  5.日    期   : 2012年02月3日
    作    者   : f62575
    修改内容   : B050 SIMLOCK命令的硬加密改制功能:
                 纠正了一处错误：永久锁卡NV项激活时，写NV项en_NV_Item_CardlockStatus失败，返回状态为锁卡
  6.日    期   : 2012年2月21日
    作    者   : w00199382
    修改内容   : B060项目增加将simlockNv写到备份区的操作
  7.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  8.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_BOOL Mma_IsImsiLocked(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    MMA_CUSTOM_CARDLOCK_OPERATOR_STRU   stCardLockOp;
    MMA_CUSTOM_CARDLOCK_PERM_STRU       stCardPerm;
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcLabImsi1="00101";
    VOS_CHAR                            *pcLabImsi2="00102";
    VOS_CHAR                            *pcLabImsi3="00201";
    VOS_INT32                           iImsiCmpRslt1,iImsiCmpRslt2,iImsiCmpRslt3;
    VOS_UINT32                          ulChkRslt;
    VOS_UINT32                          ulLength;

    ulLength        = 0;
    stCardLockOp.ucStatus           = VOS_FALSE;
    stCardLockOp.enCardLockOperator = MMA_CUSTOM_CARDLOCK_BUTT;

    stCardPerm.ucStatus             = VOS_FALSE;
    stCardPerm.ucCardLockPerm       = VOS_FALSE;

    /*当IMSI的值为00101,00102,00201时，不进行锁卡判定*/
    (VOS_VOID)VOS_MemSet(acTmpImsi, 16, 0);
    MMA_ImsiToImsiStr(acTmpImsi);

    iImsiCmpRslt1 = VOS_MemCmp(acTmpImsi, pcLabImsi1, 5);
    iImsiCmpRslt2 = VOS_MemCmp(acTmpImsi, pcLabImsi2, 5);
    iImsiCmpRslt3 = VOS_MemCmp(acTmpImsi, pcLabImsi3, 5);

    if ((0 == iImsiCmpRslt1)
      ||(0 == iImsiCmpRslt2)
      ||(0 == iImsiCmpRslt3))
    {
        return VOS_FALSE;
    }

    /*
    根据产品线的要求，如果CardLock这个NV项读取失败，则认为应该是卡被锁定，
    剩余次数为0(这种情况很少出现)
    */
    if (VOS_OK!= MMA_GetCardLockCfgData())
    {
        g_MmaNewValue.stCardLockStatus.ulStatus = VOS_TRUE;
        g_MmaNewValue.stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_LOCKED;
        g_MmaNewValue.stCardLockStatus.ulRemainUnlockTimes = 0;
        return VOS_TRUE;
    }


    if (VOS_TRUE != g_MmaNewValue.stCardLockStatus.ulStatus)
    {
        return VOS_FALSE;
    }

    (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_CARDLOCK_OPERATOR_EXT, &ulLength);

    ulResult = NV_Read(en_NV_Item_HUAWEI_CARDLOCK_OPERATOR_EXT,
                       &stCardLockOp,
                       ulLength);
    if (NV_OK != ulResult)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mma_IsImsiLocked:WARNING: Read en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT Err");
        return VOS_FALSE;
    }

    if (VOS_TRUE == stCardLockOp.ucStatus)
    {
        switch (stCardLockOp.enCardLockOperator)
        {
            case MMA_CUSTOM_CARDLOCK_EGYPT_VDF:
                ulChkRslt = MMA_IsEygptVdfImsiIllegal();
                break;

            case MMA_CUSTOM_CARDLOCK_NORWAY_NETCOM:
                ulChkRslt = MMA_IsNorwayNetcomImsiIllegal();
                break;

            case MMA_CUSTOM_CARDLOCK_MEXICO_TELCEL:
                ulChkRslt = MMA_IsMexicoTelcelIllegal();
                break;

            case MMA_CUSTOM_CARDLOCK_DOMINICA_TELCEL:
                ulChkRslt = MMA_IsDominicaTelcelIllegal();
                break;

            default:
                ulChkRslt = MMA_IsImsiIllegal();
                break;
        }

        if (VOS_TRUE == ulChkRslt)
        {
            /*如果永久锁卡选项激活，则将卡置为永久锁定状态*/
            (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT, &ulLength);

            ulResult = NV_Read(en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT,
                               &stCardPerm,
                               ulLength);
            if ((NV_OK == ulResult)
              &&(VOS_TRUE == stCardPerm.ucStatus)
              &&(VOS_TRUE == stCardPerm.ucCardLockPerm))
            {
                g_MmaNewValue.stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_LOCKED;
                ulResult = NV_Write(en_NV_Item_CardlockStatus,
                                    &g_MmaNewValue.stCardLockStatus,
                                    sizeof(g_MmaNewValue.stCardLockStatus));
                if (NV_OK != ulResult)
                {
                     MMA_ERRORLOG("Mma_IsImsiLocked:ERROR:write en_NV_Item_Me_Personalisation_Active_Flag Fail.");
                     return VOS_TRUE;
                }

                /*lint -e774*/
                ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                                &g_MmaNewValue.stCardLockStatus,
                                                sizeof(g_MmaNewValue.stCardLockStatus));

                if (NV_OK != ulResult)
                {
                    MMA_ERRORLOG("Mma_IsImsiLocked:ERROR:write special en_NV_Item_CardlockStatus Fail.");
                    return VOS_TRUE;
                }
                /*lint +e774*/

            }
            else
            {
                /*如果之前已经解锁了，根据cardlock的要求，不再要求校验*/
                /*如果用户在任意一次输入正确之后，密码将会被永久性清除，
                用户可以任意使用该数据卡，即使更换了另一张非指定卡，
                这时也不再需要重新输入密码。*/
                if (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == g_MmaNewValue.stCardLockStatus.enCardlockStatus )
                {
                    return VOS_FALSE;
                }
            }

        }
    }
    else
    {
        /*如果之前已经解锁了，根据cardlock的要求，不再要求校验*/
        /*如果用户在任意一次输入正确之后，密码将会被永久性清除，
        用户可以任意使用该数据卡，即使更换了另一张非指定卡，
        这时也不再需要重新输入密码。*/
        if (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == g_MmaNewValue.stCardLockStatus.enCardlockStatus )
        {
            return VOS_FALSE;
        }
        ulChkRslt = MMA_IsImsiIllegal();
    }

    return ulChkRslt;


}

/*<==A32D06630*/

/*****************************************************************************
 函 数 名  : MMA_CheckMePersonalisationStatus
 功能描述  : 检查当前是否处于Me Personnalisation状态，如果是的话，对标志位进行置位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月5日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年04月07日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目修改
*****************************************************************************/
VOS_UINT32 MMA_CheckMePersonalisationStatus()
{
    VOS_UINT32 ulResult = VOS_FALSE;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim status is ROMSIM!");
        return VOS_FALSE;
    }

    /*如果是虚拟sim卡，则不进行锁网锁卡校验*/
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Is virtual sim!");
        return VOS_FALSE;
    }

    if (g_stMmaMePersonalisationStatus.SimLockStatus == MMA_SIM_IS_UNLOCK)
    {
        /* 判断是哪种上层应用，从而根据形态分别进行AP-Modem和非AP-Modem的锁网锁卡校验 */
        if (SYSTEM_APP_ANDROID == g_usMmaAppConfigSupportType)
        {
            /* AP-Modem模式下，获取当前是否锁卡 */
            ulResult = Mma_VerifyPhonePersonalization();
        }
        else
        {
            ulResult = Mma_IsImsiLocked();
        }

        if (VOS_FALSE == ulResult)
        {
            g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_LOCK_IS_VERIFY;
            MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim is not locked!");
        }
        else
        {
            g_stMmaMePersonalisationStatus.SimLockStatus = (VOS_UINT8)ulResult;
            MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim is locked!");
        }

    }
    else if (g_stMmaMePersonalisationStatus.SimLockStatus == MMA_SIM_IS_LOCK)
    {
        MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim is locked!");
        return VOS_TRUE;
    }
    else
    {

    }

    return ulResult;

}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : MMA_CheckCsimMePersonalisationStatus
 功能描述  : 检查Csim应用当前是否处于Me Personnalisation状态，如果是的话，对标志位进行置位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:
             VOS_TRUE: 成功
             VOS_FALSE:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : h00313353
    修改内容   : CDMA锁网锁卡
*****************************************************************************/
VOS_UINT32 MMA_CheckCsimMePersonalisationStatus(
    VOS_VOID
)
{
    VOS_UINT32                          ulResult;

    ulResult                            = VOS_FALSE;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        MMA_INFOLOG("MMA_CheckCsimMePersonalisationStatus Info:Usim status is ROMSIM!");
        return VOS_FALSE;
    }

    /*如果是虚拟sim卡，则不进行锁网锁卡校验*/
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        MMA_INFOLOG("MMA_CheckCsimMePersonalisationStatus Info:Is virtual sim!");
        return VOS_FALSE;
    }

    if (SYSTEM_APP_ANDROID != g_usMmaAppConfigSupportType)
    {
        MMA_INFOLOG("MMA_CheckCsimMePersonalisationStatus Info:!= SYSTEM_APP_ANDROID");
        return VOS_FALSE;
    }

    if (MMA_SIM_IS_UNLOCK == g_stMmaMePersonalisationStatus.SimLockStatus)
    {
        /* 判断是哪种上层应用，从而根据形态分别进行AP-Modem和非AP-Modem的锁网锁卡校验 */
        /* AP-Modem模式下，获取当前是否锁卡 */
        ulResult = Mma_VerifyPhonePersonalization();

        if (VOS_FALSE == ulResult)
        {
            g_stMmaMePersonalisationStatus.SimLockStatus = (VOS_UINT8)MMA_SIM_LOCK_IS_VERIFY;
            MMA_INFOLOG("MMA_CheckCsimMePersonalisationStatus Info:Csim is not locked!");
        }
        else
        {
            g_stMmaMePersonalisationStatus.SimLockStatus = (VOS_UINT8)ulResult;
            MMA_INFOLOG("MMA_CheckCsimMePersonalisationStatus Info:Csim is locked!");
        }

    }
    else if (g_stMmaMePersonalisationStatus.SimLockStatus == (VOS_UINT8)MMA_SIM_IS_LOCK)
    {
        MMA_INFOLOG("MMA_CheckCsimMePersonalisationStatus Info:Csim is locked!");
        return VOS_TRUE;
    }
    else
    {

    }

    return ulResult;

}
#endif

/*****************************************************************************
 函 数 名  : MMA_PhoneStopEventReport
 功能描述  : 终端停止，通过操作结果回调函数上报返回结果
 输入参数  : VOS_UINT16  ClientId  客户端程序调用id
             VOS_UINT8    OpId             操作ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年11月28日
    作    者   : x51137
    修改内容   : Init
  2.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  3.日    期   : 2015年4月8日
    作    者   : b00269685
    修改内容   : 删除plmn list op
*****************************************************************************/
VOS_VOID MMA_PhoneStopEventReport ( VOS_UINT16 usClientID, VOS_UINT32 ulOpID, VOS_UINT32 ulEventType )
{
    TAF_PHONE_EVENT_INFO_STRU   *pEvent;

    pEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pEvent)
    {
        MMA_ERRORLOG("MMA_PhoneStopEventReport:ERROR:ALLOC MEMORY ERROR!");
        return;
    }
    PS_MEM_SET(pEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /* 清除结构变量标志 */
    pEvent->OP_CsServiceStatus    = 0;
    pEvent->OP_PhoneError         = 0;
    pEvent->OP_PlmnReselMode      = 0;
    pEvent->OP_PsServiceStatus    = 0;
    pEvent->OP_RegPlmn            = 0;
    pEvent->OP_Spare              = 0;
    /*增加上报事件选项初始化*/
    pEvent->OP_CurRegSta          = 0;
    pEvent->OP_Rssi               = 0;
    pEvent->OP_BatteryPower       = 0;
    pEvent->OP_Pin                = 0;

    /* 填写上报事件参数 */
    /* 必填参数 */
    pEvent->ClientId = usClientID;
    pEvent->OpId = (VOS_UINT8)ulOpID;         /*写入ulOpId*/
    pEvent->PhoneEvent = (TAF_PHONE_EVENT)ulEventType;

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pEvent->ClientId,(VOS_UINT8*)pEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pEvent);

    return;
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


/*****************************************************************************
 函 数 名  : MMA_PhonePlmnList
 功能描述  : 可用PLMN搜索，通过操作结果回调函数上报返回结果
 输入参数  : VOS_UINT16 ClientId     客户端程序调用id
             VOS_UINT8     OpId                        操作ID
             TAF_AVAIL_PLMN_LIST_TYPE    ListType  可用PLMN列表获得操作
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005-08-25
   作    者   :  liuyang
   修改内容   :  V100R001版本已经实现具体过程，当前只是将TAFM的功能合并入其中
 2.日    期   : 2009年4月6日
   作    者   : l00130025
   修改内容   : 新增函数，问题单AT2D10720/AT2D10806，增加搜网时usim状态的检查
 3.日    期   : 2014年01月26日
   作    者   : s00261364
   修改内容   : L-C互操作项目， 增加C+L模式异常保护
 4.日    期   : 2015年3月5日
   作    者   : B00269685
   修改内容   : 列表搜上报修改
*****************************************************************************/
VOS_VOID  MMA_PhonePlmnList()
{
    VOS_UINT8  ucError = TAF_ERR_NO_ERROR;

    ucError = MMA_CheckUsimStatusForPlmnSel();
    if(TAF_ERR_NO_ERROR != ucError)
    {
        MMA_WARNINGLOG("MMA_PhonePlmnList():WARNING:UsimStatus Error!");
        /*错误处理*/
        TAF_MMA_PlmnListErrorReport(ucError);
        return;
    }


    /* Added by s00261364 for L-C互操作项目, 2014-1-27, begin */

    /* 如果是C+L模式，此时是AT触发了plmn list搜网 ，则回复失败,进行保护  */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        return;
    }
    /* Added by s00261364 for L-C互操作项目, 2014-1-27, end */

    /* 调用Status程序启动可用PLMN搜索*/
    (VOS_VOID)Sta_PlmnList();

    return;
}

/* delete MMA_PlmnListAbort*/

/*****************************************************************************
 函 数 名  : MMA_PhonePlmnUserSel
 功能描述  :  指定PLMN选择，通过操作结果回调函数上报返回结果
 输入参数  : VOS_UINT16   ClientId  客户端程序调用id
             VOS_UINT8            OpId                操作ID
             TAF_PLMN_ID_ST  Plmn     指定PLMN id
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    作    者   : liuyang
    修改内容   : V100R001版本已经实现具体过程，当前只是将TAFM分配TI的功能合并入其中

  2.日    期   : 2006年2月23日
    作    者   : liuyang id:48197
    修改内容   : ARM获取内存内容需要从4字节对齐的位置起始，问题单号:A32D02119
  3.日    期   : 2008年09月02日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05430,修改TAF_PH_EVT_PLMN_USER_SEL和TAF_PH_EVT_PLMN_RESEL事件上报
  4.日    期   : 2008年12月01日
    作    者   : l65478
    修改内容   : 问题单号:2D07035，在手动模式不带介入技术时应该根据当前的优先级进行选择，而不应该直接设置为GSM优先
  5.日    期   : 2009年01月20日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D08490,单模,另一模式的优先级的默认手动搜网处理
  6.日    期   : 2009年4月6日
    作    者   : l00130025
    修改内容   : 新增函数，问题单AT2D10720/AT2D10806，增加搜网时usim状态的检查
  7.日    期   : 2009年4月9日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D10825/AT2D10887,Efust的定制需求，Efust禁掉GSM/SMS后相关服务被禁止
  8.日    期   : 2010年12月13日
    作    者   : z00161729
    修改内容  : 问题单号DTS2010121002174:指定搜网未指定接入技术时，MMA按用户设置优先级选择接入技术如W优先就指定搜W的plmn，而标杆是按avaliable plmn
                  list排序优先级选择接入技术，G的指定plmn优先级排在前面就指定搜G的，W的指定plmn优先级排在前面就指定搜W的。如果avaliable plmn
                  list中没有用户指定搜的plmn则按用户设置优先级选择接入技术。
  9.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : V7R1 phase II支持syscfgex命令修改
 10.日    期   : 2011年10月18日
    作    者   : s46746
    修改内容   : V7R1 PhaseII,支持L模指定搜网
 11.日    期   : 2015年3月25日
    作    者   : f00279542
    修改内容   : CDMA Iteration 11 重构修改
  12.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID MMA_PhonePlmnUserSel (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PLMN_ID_STRU                    Plmn,
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPhRat,
    TAF_PLMN_RESEL_MODE_TYPE            ReselMode
)
{
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPrioSelRat;

    enPrioSelRat = MN_MMA_GetUserPlmnSelPrioRat(enPhRat, Plmn);

    Sta_PlmnSelect(OpId, Plmn, enPrioSelRat, ReselMode);


    return;
}


/*****************************************************************************
 函 数 名  : MMA_HandleEventError
 功能描述  : 对电话事件的错误值上报
 输入参数  : VOS_UINT8 ucError
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月8日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 增加判断回调函数指针是否为空,问题单号:A32D02143

  3.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02382
  4.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  5.日    期   : 2011年11月5日
    作    者   : o00132663
    修改内容   : AT融合项目，TAF PH EVENT拆分
*****************************************************************************/
VOS_VOID MMA_HandleEventError(VOS_UINT16   ClientId,
                              VOS_UINT8          OpId,
                              VOS_UINT8       ucError,
                              TAF_PHONE_EVENT PhEvent)
{
    TAF_PHONE_EVENT_INFO_STRU *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_HandleEventError:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    if (TAF_ERR_NO_ERROR != ucError)
    {
        /*初始化所有事件选项*/
        MMA_InitEventInfoOP(pstPhoneEvent);
        /*将错误上报事件置1*/
        pstPhoneEvent->OP_PhoneError = VOS_TRUE;

        pstPhoneEvent->PhoneEvent    = PhEvent;
        pstPhoneEvent->ClientId      = ClientId;
        pstPhoneEvent->OpId          = OpId;
        pstPhoneEvent->PhoneError    = ucError;

        /*清除当前Ti全局变量中对应的记录*/
        MMA_CleanTiVar(ClientId, OpId);

        /* 调用电话管理上报函数 */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    }
    PS_MEM_FREE(WUEPS_PID_MMA,pstPhoneEvent);
    return;
}


/*****************************************************************************
函 数 名  : MMA_PhoneGetImsi
 功能描述  : +CIMI - 获取IMSI，该值应从USIM中获得，再取值之前
             应判断USIM状态，若USIM无效，须设置全局变量。
 输入参数  : VOS_UINT16           ClientId
             VOS_UINT8                  OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 获取IMSI内容，长度填充错误，问题单号:A32D02186
  3.日    期 : 2007-08-16
    作    者 : l60022475
    修改内容 : 问题单号:A32D12696
  4.日    期   : 2007年09月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  5.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
VOS_VOID MMA_PhoneGetImsi(VOS_UINT16           ClientId,
                          VOS_UINT8                  OpId)
{
    TAF_UINT16                          usErrorCode;
    TAF_PH_IMSI_STRU                    stImsiTmp;
    VOS_UINT8                          *pPara = VOS_NULL_PTR;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    /*查询USIM状态*/
    if ( MMA_ERROR == MMA_PhoneUsimReady(ClientId, OpId, TAF_PH_IMSI_ID_PARA) )
    {
        MMA_WARNINGLOG("MMA_PhoneGetImsi():WARNING:NO USIM");
        return;
    }

    switch ( MMA_CheckPin1SatusSimple() )
    {
        case MMA_ENABLE_PIN1_NONEED:
        case MMA_NONEED_PIN1:
            usErrorCode = TAF_ERR_NO_ERROR;
            break;
        case MMA_NEED_PIN1:
            usErrorCode = TAF_ERR_NEED_PIN1;
            break;
        case MMA_NEED_PUK1:
            usErrorCode = TAF_ERR_NEED_PUK1;
            break;
        case MMA_PUK1_REMAINS_ZERO:
            usErrorCode = TAF_ERR_USIM_SIM_INVALIDATION;
            break;
        case MMA_PIN1_STATUS_FAIL:
            usErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
        default:
            usErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }
    if ( TAF_ERR_NO_ERROR != usErrorCode )
    {
        /*错误处理*/
        MMA_ReportParaQueryError(ClientId, OpId,
                                 usErrorCode,
                                 TAF_PH_IMSI_ID_PARA);
        return;
    }

    ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(pucImsi);

    if (USIMM_API_SUCCESS != ulGetCardImsiRslt)
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_ERROR,
                                 TAF_PH_IMSI_ID_PARA);

        if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录获取卡IMSI异常log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, pucImsi);
#endif
        }

        return;
    }


    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    if (pucImsi[0]>8)
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_ERROR,
                                 TAF_PH_IMSI_ID_PARA);
        return;
    }
    MMA_ImsiBcd2Ascii(  (VOS_UINT8)(pucImsi[0] * 2),
                      &pucImsi[1],
                        stImsiTmp.aucImsi
                     );

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    pPara = (VOS_UINT8 *)stImsiTmp.aucImsi;
    /*使用数据上报函数将数据传至TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_IMSI_ID_PARA, TAF_ERR_NO_ERROR,pPara);
    return;
}

/*****************************************************************************
 函 数 名  : MMA_PhoneUsimReady
 功能描述  : 获取当前USIM状态
 输入参数  : TAF_PARA_TYPE    QueryType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年10月10日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，内部使用的clientid使用宏替代
  3.日    期   : 2007年09月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  4.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32 MMA_PhoneUsimReady( VOS_UINT16           ClientId,
                               VOS_UINT8                  OpId,
                               TAF_PARA_TYPE     QueryType )
{
    VOS_UINT8               ucUsimStatus;


    ucUsimStatus = USIMM_CARD_SERVIC_ABSENT;

    /*获取当前USIM状态*/
    if  ( MMA_SUCCESS != MMA_GetUsimStatusFromUsim(&ucUsimStatus, VOS_NULL_PTR))
    {
        MMA_WARNINGLOG("MMA_PhoneUsimReady():WORNING:Invoke Taf_UsimmGetStatus fail.");
        /*CLIENTID为无效值时,其余都有有效*/
        if ( MMA_CLIENTID_NONE != ClientId )
        {
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_SIM_BUSY,
                                     QueryType);
        }
        return MMA_ERROR;
    }

    /*当调用USIMAPI的值不为0,则表示有错误*/
    if ( USIMM_CARD_SERVIC_ABSENT == ucUsimStatus )
    {
        /*打印消息*/
        MMA_NORMAILLOG("MMA_PhoneUsimReady():NORMAL:USIM status is Not Ready.");
        /*生成错误数据包,*/
        /*CLIENTID为无效值时,其余都有有效*/
        if ( MMA_CLIENTID_NONE != ClientId )
        {
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                                     QueryType);
        }
        /*返回获取数据无效*/
        return MMA_ERROR;
    }

    return MMA_SUCCESS;
}


/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
/* Deleted by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-16, end */


/* Added by l00208543 for V9R1 STK升级, 2013-07-12, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SndStkLocationInfoInd
 功能描述  : 当系统消息发生变化或服务状态发生改变时，发送消息通知STK
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : l00208543
    修改内容   : 新增函数
  2.日    期  : 2013年09月04日
    作    者  : f62575
    修改内容  : DTS2013102807445:LT STK FEATURE，新增enUtranMode
  3.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID TAF_MMA_SndStkLocationInfoInd (VOS_VOID)
{
    NAS_STK_LOCATION_INFO_IND_STRU     *pstMsg        = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    TAF_SDC_PLMN_ID_STRU               *pstTempPlmnID = VOS_NULL_PTR;

    /* 如果支持SVLTE但是该modem不支持CS域，则直接退出，不向STK发送该消息 */
    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
       if (VOS_TRUE != TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
       {
           return;
       }
    }

    /* 申请内存 */
    ulLength = sizeof(NAS_STK_LOCATION_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_LOCATION_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MMA_SndStkLocationInfoInd: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stSysInfo), 0, sizeof(NAS_STK_SYS_INFO_STRU));

    PS_MEM_SET(&(pstMsg->stServiceStatus), 0, sizeof(NAS_STK_SERVICE_STATUS_INFO_STRU));

    /* 填写新消息内容 */
    pstMsg->ulMsgName            = ID_NAS_STK_LOCATION_INFO_IND;

    pstMsg->ulReceiverPid        = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstMsg->stSysInfo.enRat      = TAF_MMA_ConvertMmaRatToStkRat(TAF_SDC_GetSysMode());

    pstMsg->stSysInfo.ulCellId   = TAF_SDC_GetCurrCampCellId();

    pstMsg->stSysInfo.usLac      = TAF_SDC_GetCurrCampLac();

    pstTempPlmnID                = TAF_SDC_GetCurrCampPlmnId();
    pstMsg->stSysInfo.stPlmn.Mcc = pstTempPlmnID->ulMcc;
    pstMsg->stSysInfo.stPlmn.Mnc = pstTempPlmnID->ulMnc;

    pstMsg->stSysInfo.enUtranMode = NAS_STK_UTRAN_MODE_BUTT;
    if (TAF_MMA_RAT_WCDMA == pstMsg->stSysInfo.enRat)
    {
        pstMsg->stSysInfo.enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
    }

    pstMsg->stServiceStatus.enCsServiceStatus = TAF_SDC_GetCsServiceStatus();

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_SndStkLocationInfoInd: PS_SEND_MSG ERROR");
    }

    return;

}
/* Added by l00208543 for V9R1 STK升级, 2013-07-12, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_IsLaiChange
 功能描述  : 检查cell ID是否发生改变
 输入参数  :

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- cell发生改变
             VOS_FALSE -- cell未发生改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCellChange(MSCC_MMA_3GPP_SYS_INFO_IND_STRU *pstCurrSysInfo)
{
    TAF_SDC_PLMN_ID_STRU               *pstOldPlmnId = VOS_NULL_PTR;
    VOS_UINT16                          stOldLac;
    VOS_UINT8                           stOldRac;
    VOS_UINT32                          stOldCellId;

    pstOldPlmnId = TAF_SDC_GetCurrCampPlmnId();
    stOldLac     = TAF_SDC_GetCurrCampLac();
    stOldRac     = TAF_SDC_GetCurrCampRac();
    stOldCellId  = TAF_SDC_GetCurrCampCellId();

    if ((pstOldPlmnId->ulMcc != pstCurrSysInfo->stPlmnId.ulMcc)
     || (pstOldPlmnId->ulMnc != pstCurrSysInfo->stPlmnId.ulMnc)
     || (stOldLac            != pstCurrSysInfo->usLac)
     || (stOldRac            != pstCurrSysInfo->ucRac)
     || (stOldCellId         != pstCurrSysInfo->stCellId.aulCellId[0]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsAppNetworkInfoCellChange
 功能描述  : 判断AppNetworkInfo和NetworkInfo小区信息是否变化
 输入参数  : AppNetworkInfo中的小区信息

 输出参数  :
 返 回 值  : 小区信息是否发生变化
 调用函数  :
 被调函数  :

 修改历史    :
1.日    期   : 2015年02月11日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsAppNetworkInfoCellChange(
    TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstAppServPlmnInfo
)
{
    TAF_SDC_PLMN_ID_STRU               *pstOldPlmnId = VOS_NULL_PTR;
    VOS_UINT16                          usOldLac;
    VOS_UINT8                           ucOldRac;
    VOS_UINT32                          ulOldCellId;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enOldSysSubMode;

    TAF_SDC_PLMN_ID_STRU               *pstAppPlmnId = VOS_NULL_PTR;
    VOS_UINT16                          usAppLac;
    VOS_UINT8                           ucAppLac;
    VOS_UINT32                          ulAppCellId;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enAppSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enAppSysSubMode;

    pstOldPlmnId = TAF_SDC_GetCurrCampPlmnId();
    usOldLac     = TAF_SDC_GetCurrCampLac();
    ucOldRac     = TAF_SDC_GetCurrCampRac();
    ulOldCellId  = TAF_SDC_GetCurrCampCellId();
    enOldSysMode = TAF_SDC_GetSysMode();
    enOldSysSubMode = TAF_SDC_GetSysSubMode();

    pstAppPlmnId = &(pstAppServPlmnInfo->stServicePlmnId);
    usAppLac     = pstAppServPlmnInfo->usServiceLac;
    ucAppLac     = pstAppServPlmnInfo->ucServiceRac;
    ulAppCellId  = pstAppServPlmnInfo->ulServiceCellId;

    enAppSysMode = TAF_SDC_GetAppSysMode();
    enAppSysSubMode = TAF_SDC_GetAppSysSubMode();

    if ((pstOldPlmnId->ulMcc != pstAppPlmnId->ulMcc)
     || (pstOldPlmnId->ulMnc != pstAppPlmnId->ulMnc)
     || (usOldLac            != usAppLac)
     || (ucOldRac            != ucAppLac)
     || (ulOldCellId         != ulAppCellId)
     || (enOldSysMode        != enAppSysMode)
     || (enOldSysSubMode     != enAppSysSubMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcMsccSysInfoInNormalService
 功能描述  : 正常服务状态下接收到MSCC sysinfo的额外处理
 输入参数  : ulCellChangeFlg

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : s00246516
    修改内容   : 新生成函数

  2.日    期   : 2014年7月21日
    作    者   : w00167002
    修改内容   : DTS2014070713229:L下注册成功小区改变，检测CREG/CGREG设置为2时候，需要
                 进行上报
  3.日    期   : 2014年8月22日
    作    者   : w00242748
    修改内容   : DTS2014082204531:CREG/CGREG设置成1后，小区改变不上报
  4.日    期   : 2014年11月25日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
VOS_VOID TAF_MMA_ProcMsccSysInfoInNormalService(
    VOS_UINT32                          ulCellChangeFlg
)
{

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    if ((VOS_TRUE == NAS_MMA_CellIdChangeForStkLocSta())
     || (TAF_REPORT_SRVSTA_NORMAL_SERVICE != g_stMmsStkLocStaSysInfo.enServiceStatus))
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    {
        NAS_MMA_ReportLociStatus();
    }


    /* 收到系统消息时不上报CREG和CGREG/CEREG，根据注册结果来上报 */

    return;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

/*****************************************************************************
 函 数 名  : TAF_MMA_IsCGIInfoChanged
 功能描述  : 判断MMA中的驻留的CGI信息(cell id、rat、lac、plmn id)是否发生改变
 输入参数  : pstOldCampInfo---收到系统消息更新前SDC中的驻留PLMN信息
             pstNewCampInfo---收到系统消息更新后SDC中的驻留PLMN信息

 输出参数  : 无
 返 回 值  : VOS_TRUE, 驻留PLMN信息发生改变
             VOS_FALSE,驻留PLMN信息未发生改变

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月10日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年8月15日
   作    者   : s00217060
   修改内容   : DTS2014080700822:LTE驻留的小区是FDD还是TDD发生变化
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCGIInfoChanged(
    TAF_SDC_SYS_INFO_STRU              *pstOldSysInfo,
    TAF_SDC_SYS_INFO_STRU              *pstNewSysInfo
)
{
    /* 新老Plmn或 lac,cellid,access type或系统子模式是否有变化 */
    if ((pstOldSysInfo->st3gppSysInfo.stPlmnId.ulMcc  != pstNewSysInfo->st3gppSysInfo.stPlmnId.ulMcc)
     || (pstOldSysInfo->st3gppSysInfo.stPlmnId.ulMnc  != pstNewSysInfo->st3gppSysInfo.stPlmnId.ulMnc)
     || (pstOldSysInfo->enSysMode       != pstNewSysInfo->enSysMode)
     || (pstOldSysInfo->st3gppSysInfo.usLac           != pstNewSysInfo->st3gppSysInfo.usLac)
     || (pstOldSysInfo->st3gppSysInfo.ulCellId        != pstNewSysInfo->st3gppSysInfo.ulCellId)
     || (pstOldSysInfo->st3gppSysInfo.ucRoamFlag      != pstNewSysInfo->st3gppSysInfo.ucRoamFlag)
     || (pstOldSysInfo->st3gppSysInfo.enLmmAccessType != pstNewSysInfo->st3gppSysInfo.enLmmAccessType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcGUL3gppMsccSysInfoInd
 功能描述  : 处理GUL模式下系统消息上报
 输入参数  : MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified:将MMA收到系统消息的函数，拆成GUL和CL模式的两部分

*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppMsccSysInfoIndInGulMode(
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo
)
{
    VOS_UINT32                                              ulCellChangeFlg;
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsServiceStauts;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsServiceStatus;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                                              ulIsClInterWorkFlg;
#endif

    /* Modified by w00167002 for L-C互操作项目, 2014-2-19, begin */
#if ( (FEATURE_ON == FEATURE_IMS) || (FEATURE_ON == FEATURE_CL_INTERWORK) )

    TAF_SDC_SYS_INFO_STRU                                   stOldSysInfo;
    TAF_SDC_SYS_INFO_STRU                                  *pstCurSysInfo     = VOS_NULL_PTR;

    /* Modified by w00167002 for L-C互操作项目, 2014-2-19, end */

    PS_MEM_SET(&stOldSysInfo, 0, sizeof(TAF_SDC_SYS_INFO_STRU));

    pstCurSysInfo = TAF_SDC_GetSysInfo();

    PS_MEM_CPY(&stOldSysInfo, pstCurSysInfo, sizeof(TAF_SDC_SYS_INFO_STRU));

#endif

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    ulIsClInterWorkFlg = TAF_MMA_IsPowerOnCLInterWork();
#endif


    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    enCsServiceStauts  = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus  = TAF_SDC_GetPsServiceStatus();

    /* 如果有no rf标志，则直接不处理 */
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return;
    }
#endif

    TAF_MMA_PlmnIdReport((TAF_PLMN_ID_STRU*)&(pstMsccSysInfo->stPlmnId));

    /* 检查是否需要上报^MODE */
    Mma_ModeChgReport((TAF_SDC_SYS_MODE_ENUM_UINT8)pstMsccSysInfo->enCurNetWork, pstMsccSysInfo->ucSysSubMode);

    /* 只有小区ID改变时，才能更新RAT类型。此类型是用来SYSINFO查询时使用 */
    TAF_SDC_SetSysMode(pstMsccSysInfo->enCurNetWork);
    TAF_SDC_SetSysSubMode(pstMsccSysInfo->ucSysSubMode);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, begin */
    TAF_SDC_SetRoamFlag(pstMsccSysInfo->ucRoamFlag);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-16, end */

    ulCellChangeFlg = TAF_MMA_IsCellChange(pstMsccSysInfo);

    TAF_SDC_SetCsAttachAllowFlg(pstMsccSysInfo->ucCsAttachAllowFlag);
    TAF_SDC_SetPsAttachAllowFlg(pstMsccSysInfo->ucPsAttachAllowFlag);

    /*更新当前全局变量中的PLMN*/
    TAF_SDC_SetCurrCampPlmnId((TAF_SDC_PLMN_ID_STRU *)&pstMsccSysInfo->stPlmnId);
    TAF_SDC_SetCurrCampLac(pstMsccSysInfo->usLac);
    TAF_SDC_SetCurrCampRac(pstMsccSysInfo->ucRac);
    TAF_SDC_SetCurrCampCellId(pstMsccSysInfo->stCellId.aulCellId[0]);

    TAF_SDC_SetCurrLmmAccessType(pstMsccSysInfo->enLmmAccessType);

    TAF_SDC_SetAppLteArfcn(pstMsccSysInfo->ulArfcn);

    /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_MMA_SndMtcSysInfo(pstMsccSysInfo->ucIsFobbiddenPlmnFlag,
                          pstMsccSysInfo->ucPsSupportFlg);
#endif
    /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */

    /* Added by b00269685 for L-C互操作项目, 2014-2-14, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)

    /* 驻留时判断CGI信息发生改变时通知CMMCA模块 */
    if ( (VOS_TRUE == TAF_MMA_IsCGIInfoChanged(&stOldSysInfo, TAF_SDC_GetSysInfo()))
      && (VOS_TRUE == ulIsClInterWorkFlg) )
    {
        TAF_MMA_SndCmmcaSysInfoInd(pstMsccSysInfo->stPlmnId.ulMcc,
                          pstMsccSysInfo->stPlmnId.ulMnc,
                          pstMsccSysInfo->ulArfcn,
                          pstMsccSysInfo->enPrioClass);
    }
#endif
    /* Added by b00269685 for L-C互操作项目, 2014-2-14, end */

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if ( SYSTEM_APP_WEBUI == pstMiscellaneousCfgInfo->usAppConfigSupportFlg)
    {
        /* 判断是否需要对应用的漫游状态进行更新 */
        MN_PH_AppRoamStatusRpt();
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */



    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus)
     || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStauts))
    {
        TAF_MMA_ProcMsccSysInfoInNormalService(ulCellChangeFlg);
    }

    /* Added by l00208543 for V9R1 STK升级, 2013-07-12, begin */
    TAF_MMA_SndStkLocationInfoInd();
    /* Added by l00208543 for V9R1 STK升级, 2013-07-12, end */

    /* 当前在L模，则通知AT模块当前的接入技术 */
    if (NAS_MML_NET_RAT_TYPE_LTE == pstMsccSysInfo->enCurNetWork)
    {
        /*在L下不使用该全局变量记录接入禁止情况，清空成非接入禁止
        回到GU下时如果接入禁止发生改变MSCC会重新上报*/
        TAF_MMA_InitCellAcInfo();
    }

    /* 对AppServPlmnInfo更新的处理:这个函数里可能会更新APP里的信息，如果后面要用到APP的信息，请注意时序 */
    TAF_MMA_ProcAppServPlmnInfo_SysInfoInd(pstMsccSysInfo);


#if (FEATURE_ON == FEATURE_BASTET)
    if(VOS_TRUE == TAF_SDC_GetBastetSupportFlag())
    {
        TAF_MMA_SndBastetRatModeInd(TAF_SDC_GetSysMode(), NAS_UTRANCTRL_GetCurrUtranMode());
    }
#endif
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_FALSE == TAF_SDC_GetImsSupportFlag())
    {
        return;
    }

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
    /* 接入技术变化时通知SPM,触发SPM处理缓存 */
    if (TAF_SDC_GetSysMode() != stOldSysInfo.enSysMode)
    {
        TAF_MMA_SndSpmRatChangeNotify();
    }
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

#endif
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcCL3gppMsccSysInfoInd
 功能描述  : 处理GUL模式下系统消息上报
 输入参数  : MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : 将MMA收到系统消息的函数，拆成GUL和CL模式的两部分

  2.日    期   : 2015年11月19日
    作    者   : Y00213812
    修改内容   : 在收到系统消息的时候暂时不上报mode变化
*****************************************************************************/
VOS_UINT32 TAF_MMA_Proc3gppMsccSysInfoIndInClMode(
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo
)
{


    /* 服务状态延时可维可测 */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return VOS_TRUE;
    }

    TAF_SDC_SetRoamFlag(pstMsccSysInfo->ucRoamFlag);



    TAF_MMA_PlmnIdReport((TAF_PLMN_ID_STRU*)&(pstMsccSysInfo->stPlmnId));

    /* TO DO: 目前就增加以上这些消息，后续如果还需要增加上报的话，继续添加 */


    /*更新当前全局变量中的PLMN*/
    TAF_SDC_SetCurrCampPlmnId((TAF_SDC_PLMN_ID_STRU *)&pstMsccSysInfo->stPlmnId);

    TAF_SDC_SetCurrCampLac(pstMsccSysInfo->usLac);

    TAF_SDC_SetCurrCampRac(pstMsccSysInfo->ucRac);

    TAF_SDC_SetCurrCampCellId(pstMsccSysInfo->stCellId.aulCellId[0]);

    TAF_SDC_SetCurrLmmAccessType(pstMsccSysInfo->enLmmAccessType);


    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Rcv3gppMsccSysInfoInd
 功能描述  : 收到MSCC传上来的注册信息改变消息分发处理
 输入参数  : MSCC_MMA_3GPP_SYS_INFO_IND_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月18日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年3月4日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02354，增加PLMN上报信息与全局变量的更新

  3.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02382

  4.日    期   : 2006年4月13日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D03051
  5.日    期   : 2006年11月30日
    作    者   : luojian id:60022475
    修改内容   : B公司需求,问题单号：A32D07696
  6. 日    期   : 2009年07月07日
     作    者   : h44270
     修改内容   : 问题单号：AT2D12792，不能显示EGPRS小区信息
  7. 日    期   : 2010年11月10日
     作    者   : z00161729
     修改内容   : 问题单号：DTS2010111002152:creg=2或cgreg=2时上报的注册状态不对
  8. 日    期   : 2011年01月7日
     作    者   : s46746
     修改内容   : 问题单号:DTS2011010403819,网络模式I接收到接入层系统消息会进行Loci文件写操作，
                  连接态如果支持location status event，接入层上报系统消息也会向卡发送此事件
  9.日    期   : 2011年12月17日
    作    者   : w00167002
    修改内容   : DTS2011121304492:GU下正常驻留后，指定搜到L下，L下COPS查询显示
                  仍然为GU下驻留的网络，因为MMA收到系统消息后，判断当前为LTE
                  模，则没有更新当前的网络等信息。
  10.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  11.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  12.日    期   : 2013年4月2日
     作    者   : z00161729
     修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  13.日    期   : 2013年7月13日
     作    者   : l00208543
     修改内容   : 调用TAF_MMA_UpdateStkSysInfo向STK发送系统消息更新
  14.日    期   : 2013年08月19日
     作    者   : l00198894
     修改内容   : V9R1 干扰控制项目，给MTC上报接入模式
  15.日    期   : 2012年07月15日
     作    者   : w00176964
     修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  16.日    期   : 2013年09月24日
     作    者   : s00217060
     修改内容   : VoLTE_PhaseII项目，服务状态改变时通知SPM
  17.日    期   : 2013年10月10日
     作    者   : w00176964
     修改内容   : VoLTE_PhaseII项目:通知IMSA模块CGI和roaming信息
  18.日    期   : 2013年11月25日
     作    者   : z00161729
     修改内容   : SVLTE优化G-TL ps切换性能修改
  19.日    期   : 2014年01月17日
     作    者   : l00198894
     修改内容   : V9R1C53 C+L 离网重选项目
  20.日    期   : 2014年2月18日
     作    者   : y00245242
     修改内容   : 问题单号dts2014021501200, CGREG/CREG主动上报命令无法上报
  21.日    期   : 2014年2月20日
     作    者   : z00161729
     修改内容   : DTS2014022100125:单待驻留g的网络，切双待后tl无网络限制驻留g的网络，
                  available超时做list搜网构造搜网列表把last rplmn rat排在最前面导致g
                  排在第一个无法回l或tds的网络
  22.日    期   : 2014年2月14日
     作    者   : b00269685
     修改内容   : L-C互操作项目:CGI改变上报系统消息

  23.日    期   : 2014年6月16日
     作    者   : w00167002
     修改内容   : DSDS III:在NO RF状态，收到系统消息，直接不处理
  24.日    期   : 2014年8月14日
     作    者   : s00217060
     修改内容   : DTS2014080700822:更新LTE驻留的小区是FDD还是TDD
  25.日    期   : 2015年01月28日
     作    者   : y00245242
     修改内容   : iteration 9开发，下移IMSA接口到MSCC模块
  26.日    期   : 2015年5月26日
     作    者   : w00242748
     修改内容   : CDMA Iteration 15 modified:将MMA收到系统消息的函数，拆成GUL和CL模式的两部分
*****************************************************************************/
VOS_UINT32 TAF_MMA_Rcv3gppMsccSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo = VOS_NULL_PTR;

    pstMsccSysInfo = (MSCC_MMA_3GPP_SYS_INFO_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_MMA_Proc3gppMsccSysInfoIndInClMode(pstMsccSysInfo);
    }
    else
#endif
    {
        TAF_MMA_Proc3gppMsccSysInfoIndInGulMode(pstMsccSysInfo);
    }

    return VOS_TRUE;
}

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */


/*****************************************************************************
 函 数 名  : MMA_GetRssiLevelFromValue
 功能描述  : 从当前DB值获取AT要求的等级值
             0       等于0或小于 -113 dBm
             1                -111 dBm
             2... 56          -109...  0
             99     未知或不可测

 输入参数  : VOS_INT32      lRssiValue
             VOS_UINT8      *pucRssiLevel
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月24日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2008年11月26日
    作    者   : o00132663
    修改内容   : AT2D06789, 增加^RSSI主动上报
      RSSI等级转化
      0      等于或小于 113 dBm
      1      111 dBm
      2...30     109...  53 dBm
      31     等于或大于 51 dBm
      99     未知或不可测
*****************************************************************************/
VOS_VOID MMA_GetRssiLevelFromValue( VOS_INT32      lRssiValue, VOS_UINT8    *pucRssiLevel )
{
    if (lRssiValue >= -51)
    {
        *pucRssiLevel = 31;
    }
    else if (lRssiValue <= MMA_RSSI_LOWER_LIMIT)
    {
        *pucRssiLevel = TAF_PH_RSSIZERO;
    }
    else
    {
        *pucRssiLevel = (VOS_UINT8)(((VOS_UINT32)(lRssiValue - MMA_RSSI_LOWER_LIMIT )) >> 1);
    }

    return;
}


/*****************************************************************************
 函 数 名  : MMA_InitEventInfoOP
 功能描述  : 初始化事件信息的选项参数，建议用宏实现，暂时用函数实现
 输入参数  : TAF_PHONE_EVENT_INFO_STRU *pEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月19日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02382
  3.日    期   : 2007年09月30日
    作    者   : Z100318
    修改内容   : 问题单号:A32D12964
  4.日    期   : 2007年12月12日
    作    者   : W00176964
    修改内容   : 增加小区禁止接入信息OP项
  5.日    期   : 2015年4月8日
    作    者   : b00269685
    修改内容   : 删除plmn list op
*****************************************************************************/
VOS_VOID MMA_InitEventInfoOP(TAF_PHONE_EVENT_INFO_STRU *pstEvent)
{
    /*填充所有选项为0*/
    pstEvent->OP_BatteryPower    = VOS_FALSE;
    pstEvent->OP_CsServiceStatus = VOS_FALSE;
    pstEvent->OP_CurRegSta       = VOS_FALSE;
    pstEvent->OP_PhoneError      = VOS_FALSE;
    pstEvent->OP_PlmnReselMode   = VOS_FALSE;
    pstEvent->OP_PsServiceStatus = VOS_FALSE;
    pstEvent->OP_RegPlmn         = VOS_FALSE;
    pstEvent->OP_Rssi            = VOS_FALSE;
    pstEvent->OP_OperMode        = VOS_FALSE;
    pstEvent->OP_Pin             = VOS_FALSE;
    pstEvent->OP_Spare           = VOS_FALSE;
    pstEvent->OP_PinRemain       = VOS_FALSE;
    pstEvent->OP_Mode            = VOS_FALSE;
    pstEvent->OP_Srvst           = VOS_FALSE;
    pstEvent->OP_UsimRestrictAccess = VOS_FALSE;
    pstEvent->OP_UsimPNN         = VOS_FALSE;
    pstEvent->OP_UsimOPL         = VOS_FALSE;

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    pstEvent->Op_CellAcInfo      = VOS_FALSE;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */
    pstEvent->OP_PsInitRslt     = VOS_FALSE;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */
    return;
}
/*****************************************************************************
 函 数 名  : MMA_PhonePinRemainTimeReport
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月30日
    作    者   : liuyang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_PhonePinRemainTimeReport(const TAF_PH_PIN_TIMECNF_STRU * pstPinCnf)
{
    TAF_PHONE_EVENT_INFO_STRU *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_PhonePinRemainTimeReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /*参数有效性判断*/
    if ( VOS_NULL_PTR == pstPinCnf)
    {
        MMA_WARNINGLOG("MMA_PinDataReport():WARNING:pPinCnf is NULL PTR!.");
        MMA_HandleEventError(gstMmaValue.stOpPinData.ClientId,
                             gstMmaValue.stOpPinData.OpId,
                             TAF_ERR_NULL_PTR,
                             TAF_PH_EVT_OP_PINREMAIN_CNF);
        PS_MEM_FREE(WUEPS_PID_MMA,pstPhoneEvent);
        return;
    }

    MMA_InitEventInfoOP(pstPhoneEvent);

    pstPhoneEvent->OP_PinRemain    = VOS_TRUE;
    pstPhoneEvent->PinRemainCnf    = *pstPinCnf;
    pstPhoneEvent->PhoneEvent      = TAF_PH_EVT_OP_PINREMAIN_CNF;
    Taf_PhoneEvent(pstPhoneEvent);
    PS_MEM_FREE(WUEPS_PID_MMA,pstPhoneEvent);
}
/*****************************************************************************
 函 数 名  : TAF_MMA_GetRegStateInfo
 功能描述  : 获取当前最新的工作状态，并将其填入给定的结构中
 输入参数  : TAF_PH_REG_STA_ST *pstCurRegInf  注册状态上报数据结构
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月16日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年3月4日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02354，增加PLMN信息填充
  3.日    期   : 2006年9月28日
    作    者   : s46746
    修改内容   : 查询注册状态时，小区信息错误
  4.日    期   : 2011年12月25日
    作    者   : s46746
    修改内容   : 查询注册状态时，位置区信息错误
  5.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
   7.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
                 上报的注册状态为AppNetworkInfo中的注册状态
*****************************************************************************/
VOS_VOID TAF_MMA_GetRegStateInfo( TAF_PH_REG_STATE_STRU *pstCurRegInf )
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_PLMN_ID_STRU                   *pstPlmnId = VOS_NULL_PTR;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;

    /*获取MM层注册状态*/
    enCsRegStatus          = TAF_SDC_GetAppCsRegStatus();

    if (TAF_SDC_REG_STATUS_BUTT == enCsRegStatus)
    {
        enCsRegStatus = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    }

    pstCurRegInf->RegState   = (TAF_PH_REG_STATE_TYPE)enCsRegStatus;

    /*获取PS注册状态*/
    enPsRegStatus              = TAF_SDC_GetAppPsRegStatus();

    if (TAF_SDC_REG_STATUS_BUTT == enPsRegStatus)
    {
        enPsRegStatus = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    }

    pstCurRegInf->ucPsRegState  = (TAF_PH_REG_STATE_TYPE)enPsRegStatus;

    /*获取当前PLMN*/
    pstPlmnId          = (TAF_PLMN_ID_STRU *)TAF_SDC_GetAppServicePlmnId();
    pstCurRegInf->Plmn = *pstPlmnId;

    /*获取当前CI*/
    pstCurRegInf->CellId.aulCellId[0] = TAF_SDC_GetAppCampCellId();
    pstCurRegInf->CellId.ucCellNum = 1;

    /*获取当前LAC*/
    pstCurRegInf->usLac  = TAF_SDC_GetAppCampLac();

    /*获取当前RAC*/
    pstCurRegInf->ucRac     = TAF_SDC_GetAppCampRac();


    /* 将MMC上报的系统子模式转为+CREG/+CGREG命令参数[ACT]中协议规定的接入技术值 */
    NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(TAF_SDC_GetAppSysSubMode(), &(pstCurRegInf->ucAct));

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    return;
}



/* Added by s00246516 for L-C互操作项目, 2014-3-31, Begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_GetPidFromClientId
 功能描述  : 通过clientid 获取对应的pid
 输入参数  : MN_CLIENT_ID_T usClientId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月31日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPidFromClientId(
    MN_CLIENT_ID_T                      usClientId
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;

    enClientIdType = MN_GetClientIdType(usClientId);

    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        return WUEPS_PID_AT;
    }
    else if (CMMCA_CLIENT_ID == usClientId)
    {
        return WUEPS_PID_CMMCA;
    }
    else
    {
        return MN_GetPidFromClientId(usClientId);
    }
}
/* Added by s00246516 for L-C互操作项目, 2014-3-31, End */

/*****************************************************************************
 函 数 名  : MMA_PhModeQuery
 功能描述  : 操作模式查询命令
 输入参数  : VOS_UINT16           ClientId
             VOS_UINT8            OpId,
             TAF_PH_OP_MODE_STRU *pstPhMode  电话功能设置
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年3月17日
    作    者   : luojian 107747
    修改内容   : 新生成函数
  2.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  3.日    期   : 2014年2月14日
    作    者   : w00167002
    修改内容   : L-C互操作项目:开关机函数调整
  4.日    期   : 2014年4月3日
    作    者   : s00261364
    修改内容   : V3R360_eCall项目:开关机调整
*****************************************************************************/
VOS_VOID MMA_PhModeReport(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PH_OP_MODE_CNF_STRU             stPhMode,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    /* Modified by s00261364 for V3R360_eCall项目, 2014-4-2, begin */
    /* Modified by w00167002 for L-C互操作项目, 2014-2-15, begin */
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrlInfo;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRcvPid;

    enRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    if ( TAF_ERR_NO_ERROR != enErrorCode )
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    /* 当前为CMMCA_CLIENT_ID，则上报给CMMCA模块,如果为INTERNAL_CLIENT_ID_SPM，则上报改TAF模块*/
    if ( (CMMCA_CLIENT_ID        == ClientId)
      || (INTERNAL_CLIENT_ID_SPM == ClientId) )
    {
        if (CMMCA_CLIENT_ID == ClientId)
        {
            ulModuleId = WUEPS_PID_CMMCA;
        }
        else
        {
            ulModuleId = WUEPS_PID_TAF;
        }

        TAF_MMA_BuildMmaCtrlInfo(ulModuleId, ClientId, OpId, &stCtrlInfo);
        TAF_MMA_SndPhoneModeSetCnf(&stCtrlInfo,
                                   stPhMode.PhMode,
                                   enRslt,
                                   enErrorCode);
        return ;
    }
    /* Modified by w00167002 for L-C互操作项目, 2014-2-15, end */
    /* 初始化事件上报 */

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_PhModeReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* 操作模式项置 */
    pstPhoneEvent->OP_OperMode = 1;
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_IND;

    /* 如果有错误填写错误码 */
    if ( TAF_ERR_NO_ERROR != enErrorCode )
    {
        pstPhoneEvent->OP_PhoneError = 1;
        pstPhoneEvent->PhoneError = enErrorCode;
        MMA_INFOLOG1("MMA_PhModeReport():INFO:Report Error code:",(VOS_INT32)enErrorCode);
    }

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    /* 填写上报事件OperMode结构*/
    pstPhoneEvent->OperMode = stPhMode;
    pstPhoneEvent->OpId     = OpId;

    if ( ( TAF_PH_CMD_SET == stPhMode.CmdType )
      && ( TAF_ERR_NO_ERROR == enErrorCode ) )
    {
        /* 设置成功事件广播 */
        pstPhoneEvent->ClientId = MMA_CLIENTID_BROADCAST;
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));
    }

    /* Modified by w00167002 for L-C互操作项目, 2014-2-24, begin */
    /* 设置结果上报 */
    if ( TAF_PH_CMD_SET == stPhMode.CmdType )
    {
        /* 当前为CMMCA模式，则上报给CMMCA模块 */
        ulRcvPid = TAF_MMA_GetPidFromClientId(ClientId);

        if ((WUEPS_PID_AT == ulRcvPid)
         || (WUEPS_PID_CMMCA == ulRcvPid))
        {
            TAF_MMA_BuildMmaCtrlInfo(ulRcvPid, ClientId, OpId, &stCtrlInfo);
            TAF_MMA_SndPhoneModeSetCnf(&stCtrlInfo,
                                       stPhMode.PhMode,
                                       enRslt,
                                       enErrorCode);
        }
        else if (VOS_PID_BUTT != ulRcvPid)
        {
            pstPhoneEvent->ClientId   = ClientId;
            pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_CNF;

            MN_PH_SendMsg(ClientId, (VOS_UINT8*)pstPhoneEvent, sizeof(TAF_PHONE_EVENT_INFO_STRU));
        }
        else
        {
        }

        PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

        return;
    }

    /* 查询事件上报调用客户端 */
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_CNF;
    pstPhoneEvent->ClientId   = ClientId;
    /* Modified by w00167002 for L-C互操作项目, 2014-2-24, end */

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, begin */
/* 函数MMA_PhModeQuery MMA_PhModeHandle MMA_PhModeSet移动位置 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, end */

/*****************************************************************************
 函 数 名  : MMA_ChangeSrv2Class
 功能描述  : 支持的服务域转换为CLASS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月21日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SrvDomain宏定义转为枚举类型
*****************************************************************************/
VOS_VOID MMA_ChangeSrv2Class(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     enSrvDomain,
    TAF_PH_MS_CLASS_TYPE                 *pucMsClass
)
{
    switch(enSrvDomain)
    {
        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
            *pucMsClass = TAF_PH_MS_CLASS_A;
            break;
        case TAF_MMA_SERVICE_DOMAIN_PS:
            *pucMsClass = TAF_PH_MS_CLASS_CG;
            break;
        case TAF_MMA_SERVICE_DOMAIN_ANY:
        case TAF_MMA_SERVICE_DOMAIN_CS:
            *pucMsClass = TAF_PH_MS_CLASS_CC;
            break;
        default:
            *pucMsClass = TAF_PH_MS_CLASS_NULL;
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : MMA_ChangeClass2Srv
 功能描述  :
 输入参数  : TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain
             TAF_PH_MS_CLASS_TYPE    *pucMsClass
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年5月28日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2012年4月23日
    作    者   : w00166186
    修改内容   : DTS2012033104746,关机状态设置服务域为ANY不生效
  3.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SrvDomain转为枚举类型
*****************************************************************************/
VOS_VOID MMA_ChangeClass2Srv(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8  *pucSrvDomain,
    TAF_PH_MS_CLASS_TYPE                ucMsClass
)
{
    switch(ucMsClass)
    {
        case TAF_PH_MS_CLASS_A:
        case TAF_PH_MS_CLASS_B:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_CS_PS;
            break;
        case TAF_PH_MS_CLASS_CG:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_PS;
            break;
        case TAF_PH_MS_CLASS_CC:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_CS;
            break;
        case TAF_PH_MS_CLASS_ANY:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_ANY;
            break;
        default:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_NULL;
            break;
    }
    return;
}


/*****************************************************************************
 函 数 名  :TAF_MMA_IsUserSettedRatOrderChanged
 功能描述  :判断用户设置syscfg的接入模式优先级与原设置是否发生了改变
 输入参数  :pstUserSettedRatOrder     - 用户设置的syscfg接入模式优先级
            pstOrigUserSettedRatOrder - 原syscfg设置的接入模式优先级
 输出参数  :无
 返 回 值  :VOS_TRUE  - 用户设置syscfg的接入模式优先级与原设置发生改变
            VOS_FALSE - 用户设置syscfg的接入模式优先级与原设置未发生改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSettedRatOrderChanged(
    TAF_MMA_RAT_ORDER_STRU             *pstUserSettedRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstOrigUserSettedRatOrder
)
{
    VOS_UINT32                          i;

    /* 个数不等 */
    if (pstUserSettedRatOrder->ucRatOrderNum != pstOrigUserSettedRatOrder->ucRatOrderNum)
    {
        return VOS_TRUE;
    }

    /* 比较优先级技术是否完全相等 */
    for (i = 0; i < pstUserSettedRatOrder->ucRatOrderNum; i++)
    {
        if (pstUserSettedRatOrder->aenRatOrder[i] != pstOrigUserSettedRatOrder->aenRatOrder[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  :TAF_MMA_IsUserSettedLBandChanged
 功能描述  :判断用户设置syscfg的L频段参数与原设置是否发生了改变
 输入参数  :pstLBand     - 用户设置的syscfg L频段
            pstOrigLBand - 原syscfg 设置的L频段
 输出参数  :无
 返 回 值  :VOS_TRUE  - 用户设置syscfg的L频段与原设置发生改变
            VOS_FALSE - 用户设置syscfg的L频段与原设置未发生改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期    : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSettedLBandChanged(
    TAF_USER_SET_PREF_BAND64            *pstLBand,
    TAF_USER_SET_PREF_BAND64            *pstOrigLBand

)
{
    /* 若LTE的频段指示为非TAF_PH_BAND_NO_CHANGE */
    if ( (TAF_PH_BAND_NO_CHANGE != pstLBand->ulBandLow)
      || (0                     != pstLBand->ulBandHigh) )
    {
        if ( (pstLBand->ulBandLow != pstOrigLBand->ulBandLow)
          || (pstLBand->ulBandHigh != pstOrigLBand->ulBandHigh) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :MN_MMA_IsGUDualMode
 功能描述  :判断是否支持GW双模
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE - 支持GU双模
            VOS_FALSE - 不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 MN_MMA_IsGUDualMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    VOS_UINT8                           isWModeExist;
    VOS_UINT8                           isGModeExist;
    VOS_UINT32                          i;

    isWModeExist = VOS_FALSE;
    isGModeExist = VOS_FALSE;

    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[i])
        {
            isGModeExist = VOS_TRUE;
        }
        else if(TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[i])
        {
            isWModeExist = VOS_TRUE;
        }
        else
        {
        }
    }

    if ((VOS_TRUE == isGModeExist) && (VOS_TRUE == isWModeExist))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :MN_MMA_IsGOnlyMode
 功能描述  :判断当前接入模式是否为G only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为G单模
            VOS_FALSE - 当前不为G单模
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 MN_MMA_IsGOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    if ((1 == pstRatOrder->ucRatOrderNum)
     && (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[0]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :MN_MMA_IsWOnlyMode
 功能描述  :判断当前接入模式是否为W only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为W单模
            VOS_FALSE - 当前不为W单模
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 MN_MMA_IsWOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    if ((1 == pstRatOrder->ucRatOrderNum)
     && (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[0]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  :MN_MMA_IsLOnlyMode
 功能描述  :判断当前接入模式是否为L only
 输入参数  :pstRatOrder - 接入模式和优先级信息
 输出参数  :无
 返 回 值  :VOS_TRUE  - 当前为L单模
            VOS_FALSE - 当前不为L单模
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 MN_MMA_IsLOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    if ((1 == pstRatOrder->ucRatOrderNum)
     && (TAF_MMA_RAT_LTE == pstRatOrder->aenRatOrder[0]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif

/*****************************************************************************
 函 数 名  :MN_MMA_Convert64BitBandTo32Bit
 功能描述  :将64位频段转换为32位频段,目前GU支持的频段只有WCDMA900(0x2000000000000) 和
            WCDMA1700(0x4000000000000)是超过32位需要做特殊处理的
 输入参数  :pstBand  - 64位频段信息
 输出参数  :pulBand - 转换后32位频段信息
 返 回 值  :无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月13日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2015年4月8日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID MN_MMA_Convert64BitBandTo32Bit(
    TAF_USER_SET_PREF_BAND64           *pstBand,
    VOS_UINT32                         *pulBand
)
{
    /* 只有WCDMA900和WCDMA1700两个频段超过32位需要进行转换,
       转换原则:WCDMA900从0x2000000000000转换为0x00020000
                WCDMA1700从0x4000000000000转换为0x00040000
       原GU低于32位的频段不存在0x00020000和0x00040000的值 */
    if ((0 != pstBand->ulBandHigh)
     || ( TAF_PH_BAND_ANY != pstBand->ulBandLow))
    {
        *pulBand = pstBand->ulBandHigh |
                        (pstBand->ulBandLow & ~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);
    }
    else
    {
        *pulBand = pstBand->ulBandLow;
    }

    return;
}

    /* Move this function in SYS CFG state machine */

/*****************************************************************************
 函 数 名  : MN_MMA_ConvertGUFrequencyBand
 功能描述  : 将用户设置的GU频段转换为频点形式
 输入参数  : 无
 输出参数  : pulPrefBand  - 转换为频点后的GU频段
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID MN_MMA_ConvertGUFrequencyBand(
    VOS_UINT32                         *pulPrefBand
)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU *pstUserSettedBand   = VOS_NULL_PTR;
    VOS_UINT32                          ulUserSettedPrefBand;

    pstUserSettedBand    = TAF_MMA_GetSyscfgUserSetBandAddr();
    ulUserSettedPrefBand = *pulPrefBand;

    switch ( ulUserSettedPrefBand )
    {
        /* 用户设置的GU频段为不改变 */
        case TAF_PH_BAND_NO_CHANGE:
            *pulPrefBand     = pstUserSettedBand->uUserSetGuBand.ulPrefBand;
            break;

        /* 用户设置的GU频段为任何频段 */
        case TAF_PH_BAND_ANY:
            *pulPrefBand     &= TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
            break;

        default:
            *pulPrefBand     = ulUserSettedPrefBand;
            break;
    }

    /* 过滤无效频段 */
    *pulPrefBand &= TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertLteFrequencyBand
 功能描述  : 将用户设置的LTE频段转换为频点形式
 输入参数  : 无
 输出参数  : pstLBand  - 转换为频点后的LTE频段
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertLteFrequencyBand(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSettedBand   = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64            stLBand;

    stLBand            = *pstLBand;
    pstUserSettedBand  = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* 用户设置的LTE频段为任何频段 */
    if ((MN_MMA_LTE_HIGH_BAND_ANY == stLBand.ulBandHigh)
     && (MN_MMA_LTE_LOW_BAND_ANY == stLBand.ulBandLow))
    {
        *pstLBand = TAF_MMA_GetUeSupportBandAddr()->stUeSupportLteBand;
    }

    /* 用户设置的LTE频段为不改变 */
    else if((TAF_PH_BAND_NO_CHANGE == stLBand.ulBandLow)
         && (0 == stLBand.ulBandHigh))
    {
        *pstLBand = pstUserSettedBand->stUserSetLteBand;
    }
    else
    {
        *pstLBand = stLBand;
    }

    /* 过滤无效频段 */
    pstUeSupportLteBand   = TAF_MMA_GetUeSupportLteBandAddr();
    pstLBand->ulBandLow  &= pstUeSupportLteBand->ulBandLow;
    pstLBand->ulBandHigh &= pstUeSupportLteBand->ulBandHigh;

    return;
}
#endif

/*****************************************************************************
 函 数 名  : MN_MMA_IsUserSettedBandValid
 功能描述  : 检查syscfg设置中模式和频段是否匹配
 输入参数  : pstSysCfgPara - syscfgex设置的参数
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 匹配返回成功
             VOS_FALSE - 不匹配返回失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年6月29日
    作    者   : w00176964
    修改内容   : DTS2012062300040:单板设置为W ONLY,SYSCFGEX设置L的无效频段,AT应该返回ERROR
  3.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
*****************************************************************************/

/* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
VOS_UINT32  MN_MMA_IsUserSettedBandValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */
{
    TAF_MMA_USER_BAND_SET_UN            uGuBand;
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
#endif
    TAF_MMA_UE_BAND_CAPA_ST            *pstUeBandCap = VOS_NULL_PTR;

    /* 将GU频段 pstSysCfgPara->stGuBand 64位转换为32位的 */
    MN_MMA_Convert64BitBandTo32Bit(&pstSysCfgPara->stGuBand, &uGuBand.ulPrefBand);

    MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

#if (FEATURE_ON == FEATURE_LTE)
    /* 获取用户设置的LBand */
    TAF_MMA_ConvertLteFrequencyBand(&pstSysCfgPara->stLBand);
#endif

    pstUeBandCap = TAF_MMA_GetUeSupportBandAddr();

    /* 单模或多模时,用户设置的GU和L的频段必须要与当前UE支持的GU和L的频段有重叠频段
       否则禁止用户设置频段下去;当UE支持的GU或L的频段无效时,不检查用户设置的频段 */
    if ((0 == (uGuBand.ulPrefBand & pstUeBandCap->ulUeGSptBand))
     && (0 != pstUeBandCap->ulUeGSptBand))
    {
        return VOS_FALSE;
    }

    if ((0 == (uGuBand.ulPrefBand & pstUeBandCap->ulUeWSptBand))
     && (0 != pstUeBandCap->ulUeWSptBand))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    if ((0 == (pstSysCfgPara->stLBand.ulBandLow & pstUeSupportLteBand->ulBandLow))
     && (0 == (pstSysCfgPara->stLBand.ulBandHigh & pstUeSupportLteBand->ulBandHigh))
     && ((0 != pstUeSupportLteBand->ulBandLow)
      || (0 != pstUeSupportLteBand->ulBandHigh)))
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SetSyscfg_PowerOffStatus
 功能描述  : 关机状态syscfg设置的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口

  3.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_SetSyscfg_PowerOffStatus(
    TAF_MMA_SYS_CFG_REQ_STRU           *pstSysCfgReq
)
{
            /* 更新NV */
    TAF_MMA_UpdateSysCfgPara(&(pstSysCfgReq->stSysCfgPara));

    /* 上报设置结果 */
    TAF_MMA_SndSysCfgSetCnf(&(pstSysCfgReq->stCtrl), TAF_ERR_NO_ERROR);

    TAF_MMA_SndRatModInd_PhoneMode();

    return;

}

/* move these function in SYS CFG state machine */


/* delete this function */

/*****************************************************************************
 函 数 名  : MMA_SwitchUserSetBand2UESupportBand
 功能描述  : 用户设置频带参数转换为UE支持的频带参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月17日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2012年2月18日
    作    者   : w00181244
    修改内容   : DTS2012020802332，添加W BAND XI的处理
  3.日    期   : 2012年3月5日
    作    者   : w00176964
    修改内容   : DTS2012121802573:增加对BAND19的支持
  4.日    期   : 2015年4月13日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID MMA_SwitchUserSetBand2UESupportBand
(
  TAF_MMA_USER_BAND_SET_UN              uUserSetBand,
  TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU    *pstUeBand
)
{

    TAF_MMA_USER_PREF_BAND_STRU        *pstUserBitBand  = VOS_NULL_PTR;
    TAF_MMA_GSM_PREF_BAND_STRU         *pstGsmBitBand   = VOS_NULL_PTR;
    TAF_MMA_WCDMA_PREF_BAND_STRU       *pstWcdmaBitBand = VOS_NULL_PTR;
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand  = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    pstUserBitBand = &(uUserSetBand.BitBand);
    pstGsmBitBand = &(pstUeBand->unGsmBand.BitBand);
    pstWcdmaBitBand = &(pstUeBand->unWcdmaBand.BitBand);

    PS_MEM_SET(pstGsmBitBand,0,sizeof(TAF_MMA_GSM_PREF_BAND_STRU));
    PS_MEM_SET(pstWcdmaBitBand,0,sizeof(TAF_MMA_WCDMA_PREF_BAND_STRU));

    if (TAF_PH_BAND_NO_CHANGE == uUserSetBand.ulPrefBand)
    {
        pstUeBand->unGsmBand.ulBand   = pstUserSetBand->uUserSetUeFormatGuBand.unGsmBand.ulBand;
        pstUeBand->unWcdmaBand.ulBand = pstUserSetBand->uUserSetUeFormatGuBand.unWcdmaBand.ulBand;

        MMA_NORMAILLOG("MMA_SwitchUserSetBand2UESupportBand:INFO:BAND NO CHANGE.");
        return;
    }

    if (TAF_PH_BAND_ANY == uUserSetBand.ulPrefBand)
    {
        uUserSetBand.ulPrefBand = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
    }

    /* 过滤无效频段 */
    uUserSetBand.ulPrefBand  &= (TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand);

    pstGsmBitBand->BandGsm850 = pstUserBitBand->BandGsm850;
    pstGsmBitBand->BandGsm1800 = pstUserBitBand->BandGsmDcs1800;
    pstGsmBitBand->BandGsmE900 = pstUserBitBand->BandGsmEgsm900;
    pstGsmBitBand->BandGsm1900 = pstUserBitBand->BandGsmPcs1900;
    pstGsmBitBand->BandGsmP900 = pstUserBitBand->BandGsmPgsm900;
    pstGsmBitBand->BandGsmR900 = pstUserBitBand->BandGsmRgsm900;
    pstGsmBitBand->BandGsm850 = pstUserBitBand->BandGsm850;

    pstWcdmaBitBand->BandWCDMA_I_2100 = pstUserBitBand->BandWcdma_I_Imt2k1;
    pstWcdmaBitBand->BandWCDMA_II_1900 = pstUserBitBand->BandWcdma_II_PCS_1900;
    pstWcdmaBitBand->BandWCDMA_III_1800 = pstUserBitBand->BandWcdma_III_1800;
    pstWcdmaBitBand->BandWCDMA_IV_1700 = pstUserBitBand->BandWcdma_IV_1700;
    pstWcdmaBitBand->BandWCDMA_V_850 = pstUserBitBand->BandWcdma_V_850;
    pstWcdmaBitBand->BandWCDMA_VI_800 = pstUserBitBand->BandWcdma_VI_800;
    pstWcdmaBitBand->BandWCDMA_VII_2600 = pstUserBitBand->BandWcdma_VII_2600;
    pstWcdmaBitBand->BandWCDMA_VIII_900 = pstUserBitBand->BandWcdma_VIII_900;
    pstWcdmaBitBand->BandWCDMA_IX_J1700 = pstUserBitBand->BandWcdma_IX_1700;

    pstWcdmaBitBand->BandWCDMA_XIX_850 = pstUserBitBand->BandWCDMA_XIX_850;
    pstWcdmaBitBand->BandWCDMA_XI_1500  = pstUserBitBand->BandWcdma_XI_1500;

    MMA_INFOLOG1("MMA_SwitchUserSetBand2UESupportBand:INFO:GSM band:",
                 (VOS_INT32)pstUeBand->unGsmBand.ulBand);
    MMA_INFOLOG1("MMA_SwitchUserSetBand2UESupportBand:INFO:WCDMA band:",
                 (VOS_INT32)pstUeBand->unWcdmaBand.ulBand);

    return;
}

/*****************************************************************************
 函 数 名  : MMA_SwitchUESupportBand2UserSetBand
 功能描述  : UE支持频带转换为用户设置频带
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年4月17日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2012年2月18日
    作    者   : w00181244
    修改内容   : DTS2012020802332，添加W BAND XI的处理
  3.日    期   : 2012年3月5日
    作    者   : w00176964
    修改内容   : DTS2012121802573:增加对BAND19的支持
  4.日    期   : 2015年4月13日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID MMA_SwitchUESupportBand2UserSetBand
(
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeBand,
    TAF_MMA_USER_BAND_SET_UN           *puUserSetBand
)
{
    TAF_MMA_USER_PREF_BAND_STRU         *pstUserBitBand  = VOS_NULL_PTR;
    TAF_MMA_GSM_PREF_BAND_STRU          *pstGsmBitBand   = VOS_NULL_PTR;
    TAF_MMA_WCDMA_PREF_BAND_STRU        *pstWcdmaBitBand = VOS_NULL_PTR;

    PS_MEM_SET(puUserSetBand, 0, sizeof(TAF_MMA_USER_BAND_SET_UN));
    pstUserBitBand                      = &(puUserSetBand->BitBand);
    pstGsmBitBand                       = &(stUeBand.unGsmBand.BitBand);
    pstWcdmaBitBand                     = &(stUeBand.unWcdmaBand.BitBand);

    pstUserBitBand->BandGsmDcs1800        = pstGsmBitBand->BandGsm1800;
    pstUserBitBand->BandGsmPcs1900        = pstGsmBitBand->BandGsm1900;
    pstUserBitBand->BandGsm850            = pstGsmBitBand->BandGsm850;
    pstUserBitBand->BandGsmEgsm900        = pstGsmBitBand->BandGsmE900;
    pstUserBitBand->BandGsmPgsm900        = pstGsmBitBand->BandGsmP900;
    pstUserBitBand->BandGsmRgsm900        = pstGsmBitBand->BandGsmR900;
    pstUserBitBand->BandWcdma_I_Imt2k1    = pstWcdmaBitBand->BandWCDMA_I_2100;
    pstUserBitBand->BandWcdma_II_PCS_1900 = pstWcdmaBitBand->BandWCDMA_II_1900;
    pstUserBitBand->BandWcdma_III_1800    = pstWcdmaBitBand->BandWCDMA_III_1800;
    pstUserBitBand->BandWcdma_IV_1700     = pstWcdmaBitBand->BandWCDMA_IV_1700;
    pstUserBitBand->BandWcdma_V_850       = pstWcdmaBitBand->BandWCDMA_V_850;
    pstUserBitBand->BandWcdma_VI_800      = pstWcdmaBitBand->BandWCDMA_VI_800;
    pstUserBitBand->BandWcdma_VII_2600    = pstWcdmaBitBand->BandWCDMA_VII_2600;
    pstUserBitBand->BandWcdma_VIII_900    = pstWcdmaBitBand->BandWCDMA_VIII_900;
    pstUserBitBand->BandWcdma_IX_1700     = pstWcdmaBitBand->BandWCDMA_IX_J1700;
    pstUserBitBand->BandWcdma_XI_1500     = pstWcdmaBitBand->BandWCDMA_XI_1500;

    pstUserBitBand->BandWCDMA_XIX_850     = pstWcdmaBitBand->BandWCDMA_XIX_850;
    MMA_INFOLOG1("MMA_SwitchUESupportBand2UserSetBand:INFO:band:",
                 (VOS_INT32)puUserSetBand->ulPrefBand);
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateRatPriorityToNvim
 功能描述  : 更新RAT优先级到NVIM以及上次的用户设置
 输入参数  : pstCurrRatOrder -- 当前用户设置的Rat优先级顺序

 输出参数  : pstLastRatOrder -- 上次用户设置的Rat优先级顺序
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateRatPriorityToNvim(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRatOrder
)
{
    VOS_UINT32                         ulRatOrderChangedFlg;
    TAF_PH_NVIM_RAT_ORDER_STRU          stRatPrioList;


    ulRatOrderChangedFlg = VOS_FALSE;

    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(pstCurrRatOrder,
                                                               TAF_MMA_GetRatPrioListAddr());
    if (VOS_TRUE == ulRatOrderChangedFlg)
    {
        PS_MEM_SET(&stRatPrioList, 0, sizeof(TAF_PH_NVIM_RAT_ORDER_STRU));

        PS_MEM_CPY(&stRatPrioList, pstCurrRatOrder, sizeof(TAF_PH_NVIM_RAT_ORDER_STRU));

        /* 更新当前的RAT orde全局变量 */
        PS_MEM_CPY(pstLastRatOrder, pstCurrRatOrder, sizeof(TAF_MMA_RAT_ORDER_STRU));

        /* 更新当前的RAT orde到SDC */
        TAF_SDC_SetMsPrioRatList((TAF_SDC_RAT_PRIO_STRU *)pstCurrRatOrder);

        /* 更新接入技术,接入优先级NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_RAT_PRIO_LIST,
                                               &stRatPrioList,
                                               sizeof(stRatPrioList)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateRatpriorityToNvim: Write en_NV_Item_RAT_PRIO_LIST failed");
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateLteBandToNvim
 功能描述  : 更新LTE band到NVIM以及本地全局变量
 输入参数  : pstCurrLteBand -- 当前用户设置的LTE band

 输出参数  : pstLastLteBand -- 上次用户设置的LTE band
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateLteBandToNvim(
    TAF_USER_SET_PREF_BAND64           *pstCurrLteBand,
    TAF_USER_SET_PREF_BAND64           *pstLastLteBand
)
{

    VOS_UINT32                          ulLBandChangedFlg;

    ulLBandChangedFlg = TAF_MMA_IsUserSettedLBandChanged(pstCurrLteBand,
                                                         TAF_MMA_GetUserSetLteBandAddr());
    if (VOS_TRUE == ulLBandChangedFlg)
    {

        /* 更新用户设置的L频段的NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_USER_SET_LTEBANDS,
                                               pstCurrLteBand,
                                               sizeof(TAF_USER_SET_PREF_BAND64)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteBandToNvim: Write en_NV_Item_USER_SET_LTEBANDS failed");
        }

        /* 更新band到全局变量 */
        pstLastLteBand->ulBandHigh = pstCurrLteBand->ulBandHigh;
        pstLastLteBand->ulBandLow  = pstCurrLteBand->ulBandLow;
    }
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateGuBandToNvim
 功能描述  : 更新GU band到NVIM中
 输入参数  : pstCurrGuBand -- 当前用户设置的GU band

 输出参数  :  pstLastGuBand -- 上次的用户设置的GU band
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateGuBandToNvim(
    TAF_USER_SET_PREF_BAND64           *pstCurrGuBand,
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstLastUserBand
)
{
    VOS_UINT32                          ulBand;
    TAF_MMA_USER_BAND_SET_UN            unUserSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stSetBand;

    MN_MMA_Convert64BitBandTo32Bit(pstCurrGuBand, &ulBand);

    if (TAF_PH_BAND_NO_CHANGE != ulBand)
    {
        MN_MMA_ConvertGUFrequencyBand(&ulBand);

        unUserSetBand.ulPrefBand = ulBand;

        PS_MEM_SET(&stSetBand, 0, sizeof(TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU));

        MMA_SwitchUserSetBand2UESupportBand(unUserSetBand, &stSetBand);

        /* 更新用户设置频段的NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_User_Set_Freqbands,
                                               pstCurrGuBand,
                                               sizeof(TAF_USER_SET_PREF_BAND64)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateGuBandToNvim: Write en_NV_Item_User_Set_Freqbands failed");
        }

        /* 更新频段NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_Support_Freqbands,
                                               &(stSetBand),
                                               sizeof(stSetBand.unGsmBand)+sizeof(stSetBand.unWcdmaBand)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateGuBandToNvim: Write en_NV_Item_Support_Freqbands failed");
        }

        /* 更新GU band到全局变量 */
        pstLastUserBand->uUserSetGuBand.ulPrefBand                 = unUserSetBand.ulPrefBand ;

        pstLastUserBand->uUserSetUeFormatGuBand.unGsmBand.ulBand   = stSetBand.unGsmBand.ulBand;

        pstLastUserBand->uUserSetUeFormatGuBand.unWcdmaBand.ulBand = stSetBand.unWcdmaBand.ulBand;

        pstLastUserBand->stOrigUserSetGuBand.ulBandLow             = pstCurrGuBand->ulBandLow;

        pstLastUserBand->stOrigUserSetGuBand.ulBandHigh            = pstCurrGuBand->ulBandHigh;
    }

}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateRoamToNvim
 功能描述  : 更新漫游到NVIM中
 输入参数  : enCurrRoam -- 当前用户的漫游值

 输出参数  : penLastRoam -- 上次用户的设置的漫游值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateRoamToNvim(
    TAF_MMA_ROAM_MODE_ENUM_UINT8       enCurrRoam,
    TAF_MMA_ROAM_MODE_ENUM_UINT8      *penLastRoam
)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enLastRoam;
    VOS_UINT8                           ucRoamParaChange;

    ucRoamParaChange = VOS_FALSE;

    PS_MEM_SET(&stRoamFeature, 0x00, sizeof(NAS_NVIM_ROAM_CFG_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_Roam_Capa, &stRoamFeature, sizeof(stRoamFeature)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateRoamToNvim: Read en_NV_Item_Roam_Capa Nvim failed");
    }

    enLastRoam = TAF_MMA_GetSyscfgUserSetRoamValue();

    if (NAS_MSCC_PIF_ROAM_FEATURE_OFF == stRoamFeature.ucRoamFeatureFlg)
    {
        if ((enLastRoam                                 != enCurrRoam)
         && (TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON != enCurrRoam))
        {
            ucRoamParaChange = VOS_TRUE;
        }
    }
    else
    {
        if ((enLastRoam            != enCurrRoam)
         && (TAF_MMA_ROAM_UNCHANGE != enCurrRoam))
        {
            ucRoamParaChange = VOS_TRUE;
        }
    }

    if (VOS_TRUE == ucRoamParaChange)
    {
        /* 更新漫游支持项全局参数 */
        stRoamFeature.ucRoamCapability = enCurrRoam;

        /* 更新漫游支持项NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_Roam_Capa,
                                               &stRoamFeature,
                                               TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateRoamToNvim: Write en_NV_Item_Support_Freqbands failed");
        }

        *penLastRoam = enCurrRoam;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateMsClassToNvim
 功能描述  : 更新MS class类型到NVIM
 输入参数  : enSrvDomain -- 服务域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateMsClassToNvim(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     enCurrSrvDomain,
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8    *penLastSrvDomain
)
{
    TAF_PH_MS_CLASS_TYPE                ucClass;

    if (TAF_MMA_SERVICE_DOMAIN_NOCHANGE != enCurrSrvDomain)
    {
        /* 更新服务域全局参数 */
        MMA_ChangeSrv2Class(enCurrSrvDomain, &ucClass);

        /* 更新服务域NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_MMA_MsClass,
                                               &(enCurrSrvDomain),
                                                sizeof(TAF_PH_MS_CLASS_TYPE)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateMsClassToNvim: Write en_NV_Item_MMA_MsClass failed");
        }

        /* 更新全局变量 */
        gstMmaValue.stSetMsClass.NewMsClassType     = ucClass;
        gstMmaValue.stSetMsClass.MsClassType        = ucClass;
        gstMmaValue.pg_StatusContext->ucModeService = ucClass;

        *penLastSrvDomain                           = enCurrSrvDomain;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateAccessModeToNvim
 功能描述  : 更新接入模式
 输入参数  : pstCurrSysCfg -- 当前用户设置的系统配置参数

 输出参数  : penLastPrioRat -- 上次的RAT优先级
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
  2.日    期   : 2015年10月08日
    作    者   : zwx247453
    修改内容   : 清除Coverity告警
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAccessModeToNvim(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurrSysCfg,
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8  *penLastPrioRat
)
{
    VOS_UINT16                          i;
    NAS_MMA_NVIM_ACCESS_MODE_STRU       stAccessMode;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulRatOrderChangedFlg;

    ulLength = 0;
    ulRatOrderChangedFlg = VOS_FALSE;

    /* 不支持L模时需要写入 */
    for ( i = 0 ; i < pstCurrSysCfg->stRatOrder.ucRatOrderNum; i++ )
    {
        if ( TAF_MMA_RAT_LTE == pstCurrSysCfg->stRatOrder.aenRatOrder[i])
        {
            return;
        }
    }

    PS_MEM_SET(&stAccessMode, 0x00, sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);

    if (ulLength > sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                         &stAccessMode,
                         ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateAccessModeToNvim: Read TAF_MMA_UpdateAccessModeToNvim failed");

        return;
    }

    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(&(pstCurrSysCfg->stRatOrder),
                                                               TAF_MMA_GetRatPrioListAddr());
    /* NVIM中第二个字节表示接入优先级 */
    if (((stAccessMode.aucAccessMode[1]  != pstCurrSysCfg->enUserPrio)
      && (TAF_MMA_USER_SET_PRIO_NOCHANGE != pstCurrSysCfg->enUserPrio))
     || (VOS_TRUE                        == ulRatOrderChangedFlg))
    {
        /* 需要更新NVIM项 */
        if (1 == pstCurrSysCfg->stRatOrder.ucRatOrderNum)
        {
            if (TAF_MMA_RAT_GSM == pstCurrSysCfg->stRatOrder.aenRatOrder[0])
            {
                stAccessMode.aucAccessMode[0] = TAF_PH_USER_SET_RAT_GSM;
            }
            else
            {
                stAccessMode.aucAccessMode[0] = TAF_PH_USER_SET_RAT_WCDMA;
            }
        }
        else
        {
            stAccessMode.aucAccessMode[0] = TAF_PH_USER_SET_RAT_WCDMA_GSM;
        }

        if ( TAF_MMA_USER_SET_PRIO_NOCHANGE != pstCurrSysCfg->enUserPrio)
        {
            stAccessMode.aucAccessMode[1] = pstCurrSysCfg->enUserPrio;
            *penLastPrioRat               = pstCurrSysCfg->enUserPrio;
        }

        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_MMA_AccessMode,
                                               &stAccessMode,
                                               (VOS_UINT16)ulLength))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateAccessModeToNvim: Write en_NV_Item_MMA_AccessMode failed");
        }
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateSysCfgPara
 功能描述  : 更新用户的系统配置参数到NV与本地变量
 输入参数  : pstCurrSysCfg -- 当前用户设置系统配置参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSysCfgPara(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurrSysCfg
)
{
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     *pstLastSyscfgSet = VOS_NULL_PTR;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    /* update RAT priority to NV */
    TAF_MMA_UpdateRatPriorityToNvim(&(pstCurrSysCfg->stRatOrder), &(pstLastSyscfgSet->stRatPrioList));

#if (FEATURE_ON == FEATURE_LTE)
    /* update LTE to NV */
    TAF_MMA_UpdateLteBandToNvim(&(pstCurrSysCfg->stLBand), &(pstLastSyscfgSet->stUserSetBand.stUserSetLteBand));
#endif

    TAF_MMA_UpdateGuBandToNvim(&(pstCurrSysCfg->stGuBand), &(pstLastSyscfgSet->stUserSetBand));

    TAF_MMA_UpdateRoamToNvim(pstCurrSysCfg->enRoam, &pstLastSyscfgSet->enRoam);

    TAF_MMA_UpdateMsClassToNvim(pstCurrSysCfg->enSrvDomain, &pstLastSyscfgSet->enSrvDomain);

    TAF_MMA_UpdateAccessModeToNvim(pstCurrSysCfg, &(pstLastSyscfgSet->enPrioRat));
}

/*****************************************************************************
 函 数 名  : VOS_UINT32  MMA_IsGsmFordidened()
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月9日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D10825/AT2D10887,Efust的定制需求，Efust禁掉GSM/SMS后相关服务被禁止
  2.日    期   : 2009年8月15日
    作    者   : l00130025
    修改内容   : Efust的定制只针对USIM卡,SIM卡不做限制
  3.日    期   : 2012年5月24日
    作    者   : l60609
    修改内容   : 单板不支持GSM时，用户设置了G模，只要测量G模就会复位
  4.日    期   : 2012年12月27日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE:平台配置为GSM Only但USIM卡禁止GSM接入，删除对USIM卡禁止GSM接入的判断

*****************************************************************************/
VOS_UINT32  MMA_IsGsmForbidden()
{
    VOS_UINT32   ulGsmFordidenFlg = VOS_FALSE;
    VOS_UINT32   ulEfustGsmAccess = 1;
    VOS_UINT32   ulEfustGsmSecContext = 1;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        return VOS_FALSE;
    }

    /* 删除对USIM卡禁止GSM接入的判断 */

    /* 判断G模支持的频段，如果UE不支持G模，认为G模被禁止 */
    if (0 == TAF_MMA_GetUeSupportBandAddr()->ulUeGSptBand)
    {
        ulGsmFordidenFlg = VOS_TRUE;
    }

    MMA_INFOLOG1("MMA_IsGsmForbidden: ucForbidReg2GNetWork = ",(VOS_INT32)gstMmaValue.stEfustServiceCfg.ucForbidReg2GNetWork);
    MMA_INFOLOG1("MMA_IsGsmForbidden: ulEfustGsmAccess = ",(VOS_INT32)ulEfustGsmAccess);
    MMA_INFOLOG1("MMA_IsGsmForbidden: ulEfustGsmSecContext = ",(VOS_INT32)ulEfustGsmSecContext);

    return ulGsmFordidenFlg;
}


/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
/* MMA_SndMsccSysCfgReq函数移至MmaSndMscc.c中 */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

/* Added by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertDetachTypeToMscc
 功能描述  : 将detach type转换为MSCC的类型
 输入参数  : enDetachType     - MMA的detach类型
 输出参数  : pulMsccDetachType - MSCC的detach类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertDetachTypeToMscc(
    TAF_MMA_DETACH_TYPE_ENUM_UINT8           enDetachType,
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32    *pulMsccDetachType
)
{
    switch(enDetachType)
    {
        case TAF_MMA_DETACH_TYPE_GPRS:
            *pulMsccDetachType = NAS_MSCC_PIF_DETACH_TYPE_GPRS;
            break;

        case TAF_MMA_DETACH_TYPE_IMSI:
            *pulMsccDetachType = NAS_MSCC_PIF_DETACH_TYPE_IMSI;
            break;

        case TAF_MMA_DETACH_TYPE_GPRS_IMSI:
            *pulMsccDetachType = NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI;
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertAttachTypeToMscc
 功能描述  : 将attach type转换为MSCC的类型
 输入参数  : enMmaAttachType     - MMA的attach类型
 输出参数  : pulMsccAttachType - MSCC的attach类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertAttachTypeToMscc(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enMmaAttachType,
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32    *pulMsccAttachType
)
{
    switch(enMmaAttachType)
    {
        case TAF_MMA_ATTACH_TYPE_GPRS:
            *pulMsccAttachType = NAS_MSCC_PIF_ATTACH_TYPE_GPRS;
            break;

        case TAF_MMA_ATTACH_TYPE_IMSI:
            *pulMsccAttachType = NAS_MSCC_PIF_ATTACH_TYPE_IMSI;
            break;

        case TAF_MMA_ATTACH_TYPE_GPRS_IMSI:
            *pulMsccAttachType = NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI;
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}

/* Added by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-17, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertPlmnPriorityClass
 功能描述  : 将MSCC的PlmnPriorityClass转换为APP的类型
 输入参数  : enPrioClass        - mscc报给MMA的PlmnPriorityClass类型
 输出参数  : penDestPrioClass   - MMA报给APP的的PlmnPriorityClass类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertPlmnPriorityClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enPrioClass,
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8                 *penDestPrioClass
)
{
    switch(enPrioClass)
    {
        case NAS_MSCC_PIF_PLMN_PRIORITY_HOME:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_HOME;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_PREF:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_PREF;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_ANY:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_ANY;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_BUTT:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_BUTT;
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ConvertPlmnPriorityClass ERROR!!!");
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_BUTT;

            return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertCardType
 功能描述  : 将USIM的卡类型转换为MMA格式，供给APP使用
 输入参数  : enCardType        - USIM上报的卡类型
 输出参数  : penDestCardType   - MMA报给APP的的卡类型
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月17日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2014年7月17日
    作    者   : Y00213812
    修改内容   : 增加CDMA卡类型的转换
*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertCardType(
    USIMM_CARD_TYPE_ENUM_UINT32                             enCardType,
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32                    *penDestCardType
)
{
    switch(enCardType)
    {
        case USIMM_CARD_SIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_SIM;
            break;

        case USIMM_CARD_USIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_USIM;
            break;

        case USIMM_CARD_ROM_SIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_ROM_SIM;
            break;

        case USIMM_CARD_ISIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_ISIM;
            break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case USIMM_CARD_UIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_UIM;
            break;

        case USIMM_CARD_CSIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_CSIM;
            break;
#endif
        case USIMM_CARD_NOCARD:
            *penDestCardType = TAF_MMA_USIMM_CARD_NOCARD;
            break;

        default:
            *penDestCardType = TAF_MMA_USIMM_CARD_TYPE_BUTT;
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertCardStatus
 功能描述  : 将USIM的卡状态转换为MMA格式，供给APP使用
 输入参数  : enCardStatus        - USIM上报的卡状态
 输出参数  : penDestCardStatus   - MMA报给APP的卡状态
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus,
    TAF_MMA_CARD_STATUS_ENUM_UINT8     *penDestCardStatus
)
{
    switch(enCardStatus)
    {
        case USIMM_CARD_SERVIC_AVAILABLE:
            *penDestCardStatus = TAF_MMA_CARD_STATUS_AVAILABLE;
            break;

        default:
            *penDestCardStatus = TAF_MMA_CARD_STATUS_NOT_AVAILABLE;
            break;
    }

    return VOS_TRUE;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-17, end */

/* Added by b00269685 for L-C互操作项目, 2014-2-21, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertServiceStatus
 功能描述  : 将手机服务状态转换为MMA格式，供给APP使用
 输入参数  : enServiceStatus        -
 输出参数  : penDestServiceStatus   -
 返 回 值  : VOS_TRUE               - 转换成功
             VOS_FALSE              - 转换异常
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月21日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2014年4月29日
    作    者   : s00261364
    修改内容   : ecall项目修改:删除no imsi

*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enServiceStatus,
    TAF_PHONE_SERVICE_STATUS                               *penDestServiceStatus
)
{
    switch(enServiceStatus)
    {
        case TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_NORMAL_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_LIMITED_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE;
            break;

        /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-29, begin */

        /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-29, end */
        case TAF_SDC_SERVICE_STATUS_NO_SERVICE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_NO_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_NO_CHANGE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_LIMITED_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_DEEP_SLEEP:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_DEEP_SLEEP;
            break;

        default:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_NO_SERVICE;

            return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by b00269685 for L-C互操作项目, 2014-2-21, end */



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : MN_MMA_GetSupportedUserLteBand
 功能描述  : 获取当前产品支持的用户设置的LTE频段信息
 输入参数  : 无
 输出参数  : pstLBand - 当前用户设置的LTE的频段与产品支持的LTE的频段的交集
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : W00167002
    修改内容   : 新生成函数

  2.日    期   : 2015年4月13日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID MN_MMA_GetSupportedUserLteBand(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_USER_SET_PREF_BAND64           *pstUserSetLteBand   = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;

    /* 取得当前用户设置的LTE的频段 */
    pstUserSetLteBand   = TAF_MMA_GetUserSetLteBandAddr();

    /* 取得当前产品支持的LTE的频段 */
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    /* 获取当前产品支持的用户设置的LTE频段信息 */
    pstLBand->ulBandLow  = (pstUserSetLteBand->ulBandLow) & (pstUeSupportLteBand->ulBandLow);
    pstLBand->ulBandHigh = (pstUserSetLteBand->ulBandHigh) & (pstUeSupportLteBand->ulBandHigh);

}

#endif


/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */

/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */




/* Deleted by w00167002 for L-C互操作项目, 2014-2-19, begin */
/* MMA_PhSysCfgHandle */
/* Deleted by w00167002 for L-C互操作项目, 2014-2-19, end */

#if ( FEATURE_ON == FEATURE_LTE )
/*****************************************************************************
 函 数 名  : MN_APS_TransMsgToL4a
 功能描述  :
 输入参数  : VOS_UINT32                          MsgId
             VOS_VOID                           *pData
             VOS_UINT32                          uLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月13日
    作    者   : C00184452
    修改内容   : 新生成函数
  2.日    期   : 2013年09月04日
    作    者   : c64416
    修改内容   : 适配L4A优化

*****************************************************************************/
 VOS_UINT32 TAF_MMA_SendL4aMsg(
    VOS_UINT32                          MsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          uLen
)
{
    /* Modified by c64416 for L4A优化, 2013-09-04, Begin   */
    VOS_UINT32                          ulRet       = VOS_OK;
    MsgBlock                           *pMsgBlock   = NULL;

    pMsgBlock = (MsgBlock*)PS_ALLOC_MSG(WUEPS_PID_MMA, (uLen - VOS_MSG_HEAD_LENGTH));
    if(NULL == pMsgBlock)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemCpy((VOS_UINT8*)pMsgBlock, (VOS_UINT8*)pData, uLen);

    /* 封装VOS消息 */
    pMsgBlock->ulReceiverPid = MSP_L4_L4A_PID;
    pMsgBlock->ulSenderPid = WUEPS_PID_MMA;

    ulRet = PS_SEND_MSG(WUEPS_PID_MMA, pMsgBlock);
    if(VOS_OK != ulRet)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_SendL4aMsg:ERROR: Fail to send message!");
    }
    /* Modified by c64416 for L4A优化, 2013-09-04, Begin   */

    return ulRet;
}


#endif




/*****************************************************************************
 函 数 名  : MMA_GetPhCellRscp
 功能描述  : MMA_GetPhCellRscp
 输入参数  : VOS_UINT16          ClientId
             VOS_UINT8                 OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  2.日    期   : 2007年12月28日
    作    者   : l00107747
    修改内容   : 根据问题单号A32D13986
  3.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
  4.日    期   : 2014年11月28日
    作    者   : w00281933
    修改内容   : 服务状态显示优化，
  5.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化,全局变量stAppNetworkInfo结构名字修改

*****************************************************************************/
VOS_VOID MMA_GetPhCellRscp (VOS_UINT16          ClientId,
                           VOS_UINT8                 OpId)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    TAF_PH_CELL_RSSI_STRU               stMmaRssiTmp;
    VOS_UINT8                           ucRscpLevelTmp;

    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx =                                 TAF_SDC_GetSdcCtx();
    /*支持上报一个小区*/
    stMmaRssiTmp.CellNum = 1;
    stMmaRssiTmp.CellDlFreq = pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellDlFreq;

    if (TAF_SDC_SYS_MODE_GSM == TAF_SDC_GetAppSysMode())
    {
        MMA_GetRssiLevelFromValue(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue,
                                      &ucRscpLevelTmp);
        stMmaRssiTmp.CellRscp[0].CellRSCP = ucRscpLevelTmp;
    }
    else
    {
        MMA_GetRssiLevelFromValue(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue,
                                      &ucRscpLevelTmp);
        stMmaRssiTmp.CellRscp[0].CellRSCP = ucRscpLevelTmp;
    }

    stMmaRssiTmp.CellRscp[0].CellId = TAF_SDC_GetCurrCampCellId();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

    /*使用数据上报函数将数据传至TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_CELL_RSCP_VALUE_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)&stMmaRssiTmp);

    return;
}

/*****************************************************************************
FunctionName: MMA_GetPhUeRfPower
Description : Get the RSCP/Frequency/cellid of cells
Input       :ClientId       Client ID
            :OpId           Operation ID
Output      :
Return      :
  1.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  2.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2014年11月28日
    作    者   : w00281933
    修改内容   : 服务状态显示优化Phase I
  4.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID MMA_GetPhUeRfPowerFreq(VOS_UINT16          ClientId,
                            VOS_UINT8           OpId)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    TAF_PH_UE_RFPOWER_FREQ_STRU         stUeRfPowerFreq;

    /*频点、RF信息保存移至SDC*/
    stUeRfPowerFreq.CellUlFreq = (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellUlFreq);
    stUeRfPowerFreq.UeRfPower = (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.sUeRfPower);


    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

    /*使用数据上报函数将数据传至TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_UE_RFPOWER_FREQ_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)&stUeRfPowerFreq);

    return;
}

/* MMA_PhoneRssiInd移到预处理函数中 */

/*****************************************************************************
 函 数 名  : MMA_ConvertPhonePinType
 功能描述  : AP-Modem形态下，根据当前从USIMM获取的pin type，并结合锁网锁卡状态，
             返回实际的Pin type
 输入参数  : penPinType 作为输入参数时，传入通过USIMM_GetPinStatus获取到的pin type
 输出参数  : penPinType 作为输出参数时，输出结合了锁网锁卡状态得到的pin type
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目新增函数
  2.日    期   : 2013年8月15日
    作    者   : w00242748
    修改内容   : 接口调整
*****************************************************************************/
VOS_UINT32 MMA_ConvertPhonePinType(TAF_PH_PIN_TYPE *penPinType)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enSimLockResult;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId  = VOS_GetModemIDFromPid(WUEPS_PID_MMA);
    /* 进行锁卡校验，若校验函数返回失败，则按照当前锁在PH_NET_PIN来进行异常处理 */
    if (SC_ERROR_CODE_NO_ERROR != SC_PERS_VerifySimLock(&enSimLockResult, enModemId))
    {
        *penPinType = TAF_PHNET_PIN;
        return VOS_OK;
    }

    ulResult = VOS_OK;
    switch (enSimLockResult)
    {
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
            *penPinType = TAF_PHNET_PIN;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
            *penPinType = TAF_PHNET_PUK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
            *penPinType = TAF_PHNETSUB_PIN;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
            *penPinType = TAF_PHNETSUB_PUK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
            *penPinType = TAF_PHSP_PIN;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            *penPinType = TAF_PHSP_PUK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_READY:
            /* SIM卡未被锁定，则返回锁网锁卡校验通过 */
            break;
        default:
            /* 异常，则返回锁卡校验失败 */
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


/*****************************************************************************
 函 数 名  : MMA_PinQueryHandle
 功能描述  : +CPIN?/^CPIN?/^CPIN2?查询命令的处理
 输入参数  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
             TAF_PH_PIN_CMD_TYPE                 ucPinCmdType,
 输出参数  : TAF_PH_PIN_CNF_STRU                *pstPinCnf
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月23日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目新增函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_VOID MMA_PinQueryHandle(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PH_PIN_CMD_TYPE                 ucPinCmdType,
    TAF_PH_PIN_CNF_STRU                *pstPinCnf
)
{
    VOS_UINT32                          ulResult;
    TAF_PH_ME_LOCK_STATUS               ucLockStatus;

    /*若是查询PIN状态，走此分支，通过调用usim提供的查询API返回*/
    pstPinCnf->OpPinResult = (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(pstPinCnf->PinType),
                                                            &(pstPinCnf->QueryResult.UsimmEnableFlg),
                                                            &(pstPinCnf->QueryResult.UsimmNeedType),
                                                            &(pstPinCnf->ucRemain));
    (VOS_VOID)NAS_USIMMAPI_GetPinRemainTime((USIMM_PIN_REMAIN_STRU *)(&(pstPinCnf->RemainTime)));


    ucLockStatus = MMA_GetMeLockStatus();

    /* 若上层应用为AP-Modem，且SIM卡状态为READY(非TAF_SIM_PIN或TAF_SIM_PUK)，且为AT^CPIN或AT+CPIN查询，则需增加当前锁卡状态的判断逻辑 */
    if ( (SYSTEM_APP_ANDROID == g_usMmaAppConfigSupportType)
      && (TAF_PIN_QUERY == ucPinCmdType)
      && (TAF_PH_ME_SIM_LOCK == ucLockStatus) )
    {
        /* 若从USIMM获取的卡状态为PIN或PUK状态，则直接返回，不进行锁卡校验 */
        if ((TAF_SIM_PIN != pstPinCnf->PinType) && (TAF_SIM_PUK != pstPinCnf->PinType))
        {
            ulResult = MMA_ConvertPhonePinType(&(pstPinCnf->PinType));
            /* 出错，+CPIN命令返回ERROR */
            if(VOS_OK != ulResult)
            {
                MMA_HandleEventError(usClientId, ucOpId, TAF_ERR_AT_ERROR, TAF_PH_EVT_OP_PIN_CNF);
                return;
            }
        }
    }

    /*查询API直接返回需要的值，调用上报函数上报*/
    MMA_PinDataReport( pstPinCnf );

    return;
}

/*****************************************************************************
 函 数 名  :  MMA_PinHandle
 功能描述  : 通过传递的结构体变量，获取、
             校验、修改PIN或PUK的值，
             返回用统一的函数
             从USIM返回函数未实现。
             消息通过
             void Api_UsimPinHandleCnf(VOS_UINT8 ucClientId, VOS_UINT8 ucCmdType, VOS_UINT8 ucPINType,\
              VOS_UINT8 ucResult, VOS_UINT8 ucRemaid);
              返回至上层消息处理，
 输入参数  : VOS_UINT16   ClientId
             VOS_UINT8          OpId
             TAF_PIN_DATA_ST stPinData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D02383，增加PIN操作与查询有效性判断
  3.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，使用宏替代了原来的数字
  4.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02412，增加操作USIM函数返回值判断
  5.日    期   : 2006年8月8日
    作    者   : liuyang id:48197
    修改内容   : A32D05246,在SIM卡状态下应该判断SST文件确保可以发起DISABLE操作
  6.日    期   : 2007年09月30日
    作    者   : Z100318
    修改内容   : 问题单号:A32D12964
  7.日    期   : 2011年1月10日
    作    者   : 傅映君/f62575
    修改内容   : DTS2010010400036 组合AT命令AT+CPMS="SM";+CMGL=4无响应
  8.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  9.日    期   : 2012年04月16日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目修改
  10.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
 11.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 .
 12.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
 13.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口

 14.日    期   : 2014年1月13日
    作    者   : z00234330
    修改内容  : dts2013112601036:pin码和sim卡初始化比较慢时，sim卡初始化完成后少上报simst，导致界面显示错误"

 15.日    期   : 2014年1月28日
    作    者   : z00234330
    修改内容  : dts2014012803736:锁卡时,pin信息上报不正确

 16.日    期   : 2014年2月24日
    作    者   : z00234330,
    修改内容   : dts2014022402558,sim卡invalid时，需要区分是本地invalid还是sim卡回复的invalid

  17.日    期   : 2014年5月27日
    作    者   : z00234330,sim卡初始化未完成时,需要上报at busy。
    修改内容   : dts2014022804180
*****************************************************************************/
VOS_VOID MMA_PinHandle (VOS_UINT16 ClientId, VOS_UINT8 OpId,
                        TAF_PH_PIN_DATA_STRU stPinData)
{
    TAF_PH_PIN_CNF_STRU stPinTmp;
    TAF_PH_PIN_TIMECNF_STRU stPinRemainTime;
    VOS_UINT8           ucTi;
    VOS_UINT32          ulRet;
    VOS_UINT8           ucError = TAF_ERR_NO_ERROR;
    VOS_UINT32          ulResult;
    VOS_UINT8           ucSimType;

    TAF_SDC_USIM_STATUS_ENUM_UINT8  enSimStatus;

    enSimStatus                     = TAF_SDC_GetSimStatus();

    stPinTmp.CmdType  = stPinData.CmdType;
    stPinTmp.PinType  = stPinData.PinType;
    stPinTmp.ucRemain = MMA_PIN_REMAINS_UNINIT;

    /*增加PIN码有效性判断*/

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == enSimStatus)
    {
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:sim busy!");
        MMA_HandleEventError(ClientId,
                             OpId,
                             TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }

    if ((TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSimStatus)
     || (TAF_SDC_USIM_STATUS_BUTT == enSimStatus))
        /* add by j00174725 for Coverity, 2013-7-25,(之前没有这个判断) begin */
    {
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:sim busy!");
        MMA_HandleEventError(ClientId,
                             OpId,
                             TAF_ERR_SIM_BUSY,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }


    if ( MMA_SUCCESS != Mma_CheckPin(stPinData))
    {
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:INPUT PIN is Error!");
        MMA_HandleEventError(ClientId,
                             OpId,
                             TAF_ERR_PARA_ERROR,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#else
    /*获取当前USIM状态*/
    if ( MMA_SUCCESS != MMA_PhoneUsimReady(MMA_CLIENTID_NONE, MMA_OP_ID_INTERNAL, TAF_TELE_PARA_BUTT))
    {
        /*打印消息*/
        MMA_WARNINGLOG("MMA_PinHandle():WARNING: usim NOT ready!");
        /*生成错误数据包*/
        /*返回获取数据无效*/
        /*返回操作失败*/
        if ((TAF_PIN_VERIFY == stPinTmp.CmdType)
         || (TAF_PIN_UNBLOCK == stPinTmp.CmdType))
        {
            MMA_HandleEventError(ClientId,
                                 OpId,
                                 TAF_ERR_CMD_TYPE_ERROR,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        else
        {
            MMA_HandleEventError(ClientId,
                                 OpId,
                                 TAF_ERR_SIM_FAIL,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        return;
    }
#endif

    if ( TAF_PIN_DISABLE == stPinTmp.CmdType )
    {
        ulRet = MMA_PhoneGetUsimType( &ucSimType );
        if ( (MMA_SUCCESS       == ulRet  )
           &&(MMA_USIM_TYPE_SIM == ucSimType)
           )
        {
            /*检查SST文件判断是否可以DISABLE*/
            /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
            ulResult = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_CHV1_DISABLE);
            /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

            if (VOS_TRUE != ulResult)
            {
                /*打印消息*/
                MMA_WARNINGLOG("MMA_PinHandle():WARNING: GET SST FAIL, OR Service not allowed!");
                ucError = TAF_ERR_UNSPECIFIED_ERROR;
            }
        }
        else if ( MMA_SUCCESS       != ulRet )
        {
            /*打印消息*/
            MMA_WARNINGLOG("MMA_PinHandle():WARNING: Get uicc Tpye Fail!");
            ucError = TAF_ERR_UNSPECIFIED_ERROR;
        }
        else
        {
            MMA_NORMAILLOG("MMA_PinHandle():NORMAL: Usim return no error!");
        }
        if ( TAF_ERR_NO_ERROR != ucError )
        {
            MMA_HandleEventError(ClientId,
                                 OpId,
                                 ucError,
                                 TAF_PH_EVT_OP_PIN_CNF );
            return;
        }
    }

    /*填入对PIN操作的全局变量供返回函数查询，存储CLIENTID*/
    /*记录当前clientId与OpId*/
    if (MMA_SUCCESS != MMA_TiAlloc(TAF_MMA, ClientId, OpId, TAF_PH_EVT_OP_PIN_CNF, &ucTi))
    {   /*Ti分配失败*/
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:ALLOC TI FAILED!");
        /*错误处理*/
        MMA_HandleEventError(ClientId, OpId, TAF_ERR_TI_ALLOC_FAIL, TAF_PH_EVT_OP_PIN_CNF);
        return;
    }
    gstMmaValue.stOpPinData.ClientId        = ClientId;
    gstMmaValue.stOpPinData.OpId            = OpId;
    gstMmaValue.stOpPinData.stMmaPinData    = stPinData;

    if ((TAF_PIN_QUERY == stPinData.CmdType) || (TAF_PIN2_QUERY == stPinData.CmdType))
    {
        MMA_PinQueryHandle(ClientId, OpId, stPinData.CmdType, &stPinTmp);
    }
    else if(TAF_PIN_RemainTime == stPinData.CmdType)
    {
        stPinRemainTime.CmdType = TAF_PIN_RemainTime;

        stPinRemainTime.PinType = USIMM_PIN;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPIN1Remain));    /* Read PIN1 remain time */

        stPinRemainTime.PinType = USIMM_PUK;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPUK1Remain));    /* Read PUK1 remain time */

        stPinRemainTime.PinType = USIMM_PIN2;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPIN2Remain));    /* Read PUK1 remain time */

        stPinRemainTime.PinType = USIMM_PUK2;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPUK2Remain));    /* Read PUK1 remain time */

        MMA_PhonePinRemainTimeReport( &stPinRemainTime );
    }
    else
    {
        /*对USIM操作实现*/
        /*启动定时器*/
        if( VOS_OK != NAS_StartRelTimer( &(g_MmaSimTimer[0].MmaHTimer),
                                         WUEPS_PID_MMA,
                                         MMA_PIN_HANDLE_TIME,
                                         TAF_MMA,
                                         TAF_USIM_OPPIN,
                                         VOS_RELTIMER_NOLOOP ) )
        {
            MMA_ERRORLOG("MMA_PinHandle():ERROR:Start Timer Error!");
            /*返回操作失败*/
            /*错误处理*/
            MMA_HandleEventError(ClientId, OpId, TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_EVT_OP_PIN_CNF);
            g_MmaSimTimer[0].ucTimerStatus     = MMA_TIMER_ERROR;
            return;
        }
        g_MmaSimTimer[0].ucTimerStatus         = MMA_TIMER_RUN;

        /*查询系统当前需要验证的PIN码类型,输入参数除了PIN类型以外其它参数无意义*/
        (VOS_VOID)NAS_USIMMAPI_GetPinStatus(&(stPinData.PinType),
                              &stPinTmp.QueryResult.UsimmEnableFlg,
                              &stPinTmp.QueryResult.UsimmNeedType,
                              &stPinTmp.ucRemain);
        /*调用USIM提供的操作，对PIN进行操作*/

        if(USIMM_API_SUCCESS != NAS_USIMMAPI_PinReq(WUEPS_PID_MMA,
                                            stPinData.CmdType,
                                            stPinData.PinType,
                                            stPinData.aucOldPin,
                                            stPinData.aucNewPin))

        {
            MMA_WARNINGLOG("MMA_PinHandle():WARNING:Invoke USIMM Function Fail!");
            /*停止定时器*/

            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA, TAF_USIM_OPPIN, &(g_MmaSimTimer[0].MmaHTimer)))
            {
                MMA_WARNINGLOG("MMA_PinHandle():WARNING:NAS_StopRelTimer failed!");
            }

            /*设置停止定时器标志*/
            g_MmaSimTimer[0].ucTimerStatus    = MMA_TIMER_STOP;
            /*上报错误*/
            MMA_HandleEventError(ClientId, OpId, TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_EVT_OP_PIN_CNF);
            MMA_WARNINGLOG("MMA_PinHandle():WARNING:invoke USIM Api Fail!");

            return;
        }

    }
    return;
}
/*****************************************************************************
 函 数 名  : MMA_VerifyOperatorLockPwd
 功能描述  : 解锁卡的密码是通过IMEI根据算法(MD5)生成密码字符串
             产品线提供密码生成方案，只需进行校验即可
 输入参数  : VOS_UINT8 *pucPwd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月15日
    作    者   : luojian 107747
    修改内容   : 新生成函数
  2.日    期   : 2009年01月19日
    作    者   : h44270
    修改内容   : 问题单AT2D08460
  3.日    期   : 2012年02月01日
    作    者   : l00171473
    修改内容   : 问题单DTS2012013000257
  4.日    期   : 2014年09月05日
    作    者   : m00217266
    修改内容   : 底软接口归一项目，VerifySIMLock该接口由第三方提供，在文件头部声明，此处直接调用
*****************************************************************************/
VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd)
{
    VOS_UINT8   aucTmpImei[TAF_PH_IMEI_LEN];

    PS_MEM_CPY(aucTmpImei, g_aucMmaImei, TAF_PH_IMEI_LEN-1);

    aucTmpImei[TAF_PH_IMEI_LEN -1] = 0;


    /* Modified by l00171473 for DTS2012013000257 SIMLOCK算法版本更新为2.0相关, 2012-01-29, Begin */
    if (VOS_FALSE == VerifySL((char *)pucPwd, (char *)aucTmpImei))
    {
        return VOS_ERR;
    }
    /* Modified by l00171473 for DTS2012013000257 SIMLOCK算法版本更新为2.0相关, 2012-01-29, End */

    return VOS_OK;


}
/*****************************************************************************
 函 数 名  : MMA_MePersonalCnfReport
 功能描述  : 安全命令相关上报公共处理
 输入参数  : VOS_UINT8 *pucPwd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月15日
    作    者   : luojian 107747
    修改内容   : 新生成函数
  2.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
*****************************************************************************/
VOS_VOID MMA_MePersonalCnfReport(VOS_UINT16                        ClientId,
                                VOS_UINT8                         OpId,
                                TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf)
{
    TAF_PHONE_EVENT_INFO_STRU   *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_MePersonalCnfReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    pstPhoneEvent->ClientId = ClientId;
    pstPhoneEvent->OpId = OpId;
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_ME_PERSONALISATION_CNF;

    pstPhoneEvent->MePersonalisation = stMePersonalCnf;

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}
/*****************************************************************************
 函 数 名  : MMA_MePersonliationSet
 功能描述  : 通过传递的结构体变量，获取、
             校验、修改PIN或PUK的值，
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
             TAF_ME_PERSONALISATION_DATA_STRU   stPinData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
  2. 日    期   : 2009年08月03日
     作    者   : h44270
     修改内容   : 问题单号：AT2D13476，对机要数据写操作需要鉴权，而现在的鉴权算法与产品线要求有出入，需要与产品线保持要求一致
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_UINT32 MMA_CheckMePersonalisationPwd(TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    VOS_UINT8       aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    VOS_UINT32      ulRslt;
    VOS_UINT16      usDataLen = TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX;


    PS_MEM_SET(aucPwd, 0x00, sizeof(aucPwd));

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            ulRslt = NV_Read(en_NV_Item_Sim_Personalisation_Pwd,
                             aucPwd,
                             usDataLen);

            if (NV_OK != ulRslt)
            {
                return TAF_PH_ME_PERSONALISATION_ERROR;
            }
            PS_MEM_CPY(g_MmaNewValue.aucPwd, aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

            ulRslt = (VOS_UINT32)VOS_MemCmp(stMePersonalData.aucOldPwd,
                                aucPwd,
                                TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
            if (VOS_OK != ulRslt)
            {
                return TAF_PH_ME_PERSONALISATION_WRONG_PWD;
            }
            break;
        case TAF_OPERATOR_PERSONALISATION:
            if (VOS_OK != MMA_VerifyOperatorLockPwd(stMePersonalData.aucOldPwd))
            {
                return TAF_PH_ME_PERSONALISATION_WRONG_PWD;
            }
            break;
        default:
            return TAF_PH_ME_PERSONALISATION_WRONG_PARA;
    }

    return TAF_PH_ME_PERSONALISATION_OK;
}



/*****************************************************************************
 函 数 名  : MMA_MePersonliationSet
 功能描述  : 设置ME PERSONALISATION操作。
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
             TAF_ME_PERSONALISATION_DATA_STRU   stPinData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MMA_MePersonlisationSet(VOS_UINT16 ClientId,
                                VOS_UINT8 OpId,
                                TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf;
    VOS_UINT32          ulResult;
    TAF_UINT8           aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*检查密码是否正确*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);


            /*密码正确，则设置当前的IMSI String*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                aucSimPersonalisationStr[0] = (VOS_UINT8)stMePersonalData.unMePersonalisationSet.SimPersionalisationStr.DataLen;
                (VOS_VOID)VOS_MemCpy(aucSimPersonalisationStr + 1,
                           stMePersonalData.unMePersonalisationSet.SimPersionalisationStr.aucSimPersonalisationStr,
                           aucSimPersonalisationStr[0]);

                ulResult = NV_Write(en_NV_Item_Sim_Personalisation_Imsi_Str,
                                    aucSimPersonalisationStr,
                                    aucSimPersonalisationStr[0] + 1);

                if (NV_OK != ulResult)
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}
/*****************************************************************************
函 数 名  : TAF_UsimmStatusCardUnlocked
功能描述  : 卡状态上报函数
输入参数  : 来源Id
输出参数  : 添加一条命令到命令队列
返 回 值  : void
调用函数  : 外部接口
被调函数  :
  1.日    期  : 2009年11月3日
    作    者  : l00130025,h44270
    修改内容  : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo卡状态返回
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2012年01月05日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM 上报消息结构体修改
  5.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
VOS_VOID TAF_UsimmStatusCardUnlocked()
{
    VOS_UINT8                           ucUsimStatus;
    VOS_UINT8                           ucUsimType;
    USIMM_CARDSTATUS_IND_STRU          *pUsimMsg = VOS_NULL_PTR;


    ucUsimStatus = USIMM_CARD_SERVIC_BUTT;
    ucUsimType   = USIMM_CARD_NOCARD;
    (VOS_VOID)MMA_GetUsimStatusFromUsim(&ucUsimStatus,&ucUsimType);

    if (USIMM_CARD_SERVIC_AVAILABLE != ucUsimStatus)
    {
        return;
    }
    pUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)PS_ALLOC_MSG(MAPS_PIH_PID, sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pUsimMsg)
    {
        return;
    }

    MMA_MEM_SET(pUsimMsg,0x00,sizeof(USIMM_CARDSTATUS_IND_STRU));

    pUsimMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;

    pUsimMsg->ulSenderPid     = MAPS_PIH_PID;

    pUsimMsg->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pUsimMsg->ulReceiverPid                 = WUEPS_PID_MMA;
    /* pUsimMsg->ucIMSILen                     = USIMM_EF_IMSI_LEN; */
    pUsimMsg->stUsimSimInfo.enCardService   = ucUsimStatus;
    pUsimMsg->stUsimSimInfo.enCardType      = ucUsimType;
    pUsimMsg->ulMsgName                     = USIMM_CARDSTATUS_IND;
    


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_USIM, pUsimMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_USIM, "TAF_UsimmStatusCardUnlocked():WARNING:SEND MSG FIAL");
    }

    return;
}

/*****************************************************************************
 函 数 名  : MMA_NetworkPersonlisationVerify
 功能描述  : 锁网密码校验处理
 输入参数  : TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年3月15日
    作    者   : luojian 107747
    修改内容   : 新生成函数
  2.日    期  : 2009年11月3日
    作    者  : l00130025,h44270
    修改内容  : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo卡状态返回
  3.日    期   : 2012年02月3日
    作    者   : f62575
    修改内容   : B050 SIMLOCK命令的硬加密改制功能:
                 密码校验通过后补充下述流程：
                 使用FLASH文件中的密码更新所开状态
                 备份写en_NV_Item_CardlockStatusNV项
  4.日    期   : 2012年2月21日
    作    者   : w00199382
    修改内容   : B060项目增加将simlockNv写到备份区的操作
  5.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32   MMA_OperatorPersonlisationVerify(
TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRemainTimes;
    VOS_UINT8                           ucLockStatus;

    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;


    PS_MEM_SET(&stSimLockMaxTimes, 0x00, sizeof(stSimLockMaxTimes));
    PS_MEM_SET(&stCardLockStatus,  0x00, sizeof(stCardLockStatus));

    /* 获取当前锁卡状态和剩余次数 */
    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       sizeof(stCardLockStatus));
    if (NV_OK != ulResult)
    {
        MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:ERROR:Read en_NV_Item_CardlockStatus Fail.");
        return TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
    }
    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                      &stSimLockMaxTimes,
                      sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockMaxTimes.ulStatus = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        if (VOS_FALSE == stSimLockMaxTimes.ulStatus)
        {
            g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        }
        else
        {
            g_MmaNewValue.stSimLockMaxTimes = stSimLockMaxTimes;
        }
    }

    if (VOS_FALSE == stCardLockStatus.ulStatus)
    {
        MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:ERROR:Status no correct.");
        return TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
    }

    ucLockStatus = (VOS_UINT8)stCardLockStatus.enCardlockStatus;
    ucRemainTimes  = (VOS_UINT8)stCardLockStatus.ulRemainUnlockTimes;

    /* 已经处于永久锁定状态不允许校验  */

    if (( ( TAF_OPERATOR_UNLOCK_TIMES_MIN == ucRemainTimes )
           &&( TAF_OPERATOR_LOCK_LOCKED == ucLockStatus))
          ||(TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == ucLockStatus) )
    {
        ulResult = TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
        MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:card locked already.");
    }
    else
    {
        /* 检查密码是否正确 */
        ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);

        /* 密码正确 */
        if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
        {
            MMA_INFOLOG("MMA_OperatorPersonlisationVerify:INFO:MMA_CheckMePersonalisationPwd Return OK.");
            /* g_stMmaMePersonalisationStatus 数据更新后移 */

            /* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-15, begin */

            /* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-15, end */

            /* 一旦校验通过，将永久解除锁卡状态  */
            stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
            stCardLockStatus.ulRemainUnlockTimes = stSimLockMaxTimes.ulLockMaxTimes;

            ulResult = NV_Write(en_NV_Item_CardlockStatus,
                                &stCardLockStatus,
                                sizeof(stCardLockStatus));
            if (NV_OK != ulResult)
            {
                MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:ERROR:write en_NV_Item_CardlockStatus Fail.");
                return TAF_PH_ME_PERSONALISATION_ERROR;
            }

            /*nv写成功时才对其备份*/
            /*lint -e774*/
            ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                           &stCardLockStatus,
                                           sizeof(stCardLockStatus));
            if (NV_OK != ulResult)
            {
                MMA_WARNINGLOG("MMA_OperatorPersonlisationVerify: WARNING:write Special en_NV_Item_CardlockStatus Fail.");
                return TAF_PH_ME_PERSONALISATION_ERROR;
            }
            /*lint +e774*/

            /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-15, begin */
            /* 解锁卡后触发锁网锁卡状态变化指示消息 */
            TAF_MMA_SndSimlocakStatusChangeInd();
            /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-15, end */

            /* 解除锁卡状态 */
            g_stMmaMePersonalisationStatus.SimLockStatus
                                 = MMA_SIM_LOCK_IS_VERIFY;

            g_stMmaMePersonalisationStatus.stCardLockInfo.RemainTimes
                                 = stSimLockMaxTimes.ulLockMaxTimes;

            ulResult = TAF_PH_ME_PERSONALISATION_OK;
        }
        else if (TAF_PH_ME_PERSONALISATION_WRONG_PWD == ulResult)
        {
            MMA_WARNINGLOG("MMA_OperatorPersonlisationVerify:WARNING:MMA_CheckMePersonalisationPwd Return error.");
            stCardLockStatus.ulRemainUnlockTimes--;
            g_stMmaMePersonalisationStatus.stCardLockInfo.RemainTimes
                                    = ucRemainTimes;

            if (TAF_OPERATOR_UNLOCK_TIMES_MIN == stCardLockStatus.ulRemainUnlockTimes)
            {
                stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_LOCKED;
            }

            /* 更新RemainTimes和锁定状态到NV中 */
            ulResult = NV_Write(en_NV_Item_CardlockStatus,
                         &stCardLockStatus,
                         sizeof(stCardLockStatus));
            if (NV_WRITE_SECURE_FAIL == ulResult)
            {
                /* 如果解锁失败，恢复原来的值 */
                g_stMmaMePersonalisationStatus.stCardLockInfo.RemainTimes++;
            }



            if (NV_OK == ulResult)
            {
                /*nv写成功时才对其备份*/
                /*lint -e774*/
                ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                               &stCardLockStatus,
                                               sizeof(stCardLockStatus));
                if (NV_OK != ulResult)
                {
                    MMA_WARNINGLOG("MMA_OperatorPersonlisationVerify: WARNING:write en_NV_Item_CardlockStatus Fail.");
                }
                /*lint +e774*/
            }


            ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
        }
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MMA_MePersonalCnfReport
 功能描述  : 安全命令密码校验处理
 输入参数  : TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年3月15日
    作    者   : luojian 107747
    修改内容   : 新生成函数
  2.日    期   : 2009年11月3日
    作    者   : l00130025,h44270
    修改内容   : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo卡状态返回
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MMA_MePersonlisationVerify(VOS_UINT16   ClientId,
                                   VOS_UINT8    OpId,
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    ulResult = MMA_GetMeLockStatus();

    if (TAF_PH_ME_SIM_LOCK == ulResult)
    {
        switch(stMePersonalData.MePersonalType)
        {
            case TAF_SIM_PERSONALISATION:
                /* 检查密码是否正确 */
                ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);
                /* 密码正确，则设置当前的IMSI String */
                if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
                {
                    /* 解除锁卡状态 */
                    g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_LOCK_IS_VERIFY;
                }
                break;
            case TAF_OPERATOR_PERSONALISATION:
                ulResult = MMA_OperatorPersonlisationVerify( stMePersonalData );
                break;
            default:
                ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
                break;
        }
    }
    else if (TAF_PH_ME_NO_SIM == ulResult)
    {
        if ( TAF_OPERATOR_PERSONALISATION == stMePersonalData.MePersonalType )
        {
            ulResult = MMA_OperatorPersonlisationVerify( stMePersonalData );
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_NO_SIM;
        }
    }
    else
    {
        ulResult = TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
    }
    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}


/*****************************************************************************
 函 数 名  : MMA_MePersonliationPwdChange
 功能描述  : 修改ME PERSONALISATION各种类型对应的密码
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
             TAF_ME_PERSONALISATION_DATA_STRU   stPinData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MMA_MePersonlisationPwdChange(VOS_UINT16   ClientId,
                                      VOS_UINT8    OpId,
                                      TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf;
    VOS_UINT32          ulResult;


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));


    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*检查密码是否正确*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);


            /*密码正确，则设置新的密码*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                ulResult = NV_Write(en_NV_Item_Sim_Personalisation_Pwd,
                                    stMePersonalData.aucNewPwd,
                                    TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

                if (NV_OK != ulResult)
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}

/*****************************************************************************
 函 数 名  : MMA_MePersonliationActive
 功能描述  : 激活ME PERSONALISATION
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
             TAF_ME_PERSONALISATION_DATA_STRU   stPinData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID MMA_MePersonlisationActive(VOS_UINT16   ClientId,
                                   VOS_UINT8    OpId,
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;
    NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU   stMePersonActFlag;
    VOS_UINT16                          usDataLen = TAF_MAX_IMSI_LEN + 1;
    VOS_UINT32                          ulNvLength;
    TAF_UINT8                           aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];

    PS_MEM_SET(&stMePersonalCnf,         0x00, sizeof(stMePersonalCnf));
    PS_MEM_SET(aucSimPersonalisationStr, 0x00, sizeof(aucSimPersonalisationStr));
    stMePersonActFlag.usMePersonalActFlag = TAF_ME_PERSONALISATION_ACTIVE_STATUS;
    ulNvLength = 0;

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*检查密码是否正确*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);
            if (TAF_PH_ME_PERSONALISATION_OK != ulResult)
            {
                break;
            }

            /*检查当前是否有设定的字串，字串为0时，不能激活*/
            ulResult = NV_Read(en_NV_Item_Sim_Personalisation_Imsi_Str,
                               aucSimPersonalisationStr,
                               usDataLen);
            if (NV_OK != ulResult)
            {
                ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                break;
            }
            else
            {
                if (0 == aucSimPersonalisationStr[0])
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                    break;
                }
            }

            /*设置激活状态*/
            (VOS_VOID)NV_GetLength(en_NV_Item_Me_Personalisation_Active_Flag, &ulNvLength);
            ulResult = NV_Write(en_NV_Item_Me_Personalisation_Active_Flag,
                                &stMePersonActFlag,
                                ulNvLength);
            if (NV_OK != ulResult)
            {
                ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);
}

/*****************************************************************************
 函 数 名  : MMA_MePersonliationDeactive
 功能描述  : 去激活ME PERSONALISATION
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
             TAF_ME_PERSONALISATION_DATA_STRU   stMePersonalData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID MMA_MePersonlisationDeactive(VOS_UINT16   ClientId,
                                     VOS_UINT8    OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;
    NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU   stMePersonActFlag;

    stMePersonActFlag.usMePersonalActFlag = TAF_ME_PERSONALISATION_DEACTIVE_STATUS;


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*检查密码是否正确*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);

            /*密码正确，去激活锁卡功能*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                ulResult = NV_Write(en_NV_Item_Me_Personalisation_Active_Flag,
                                    &stMePersonActFlag,
                                    sizeof(NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU));
                if (NV_OK != ulResult)
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);
}

/*****************************************************************************
 函 数 名  : MMA_MePersonlisationRetrieve
 功能描述  :
 输入参数  : VOS_UINT16   ClientId
             VOS_UINT8    OpId
             TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月30日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MMA_MePersonlisationRetrieve(VOS_UINT16   ClientId,
                                     VOS_UINT8    OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult = TAF_PH_ME_PERSONALISATION_OK;
    VOS_UINT16                          usDataLen = TAF_MAX_IMSI_LEN + 1;
    TAF_UINT8                           aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];


    PS_MEM_SET(&stMePersonalCnf,         0x00, sizeof(stMePersonalCnf));
    PS_MEM_SET(aucSimPersonalisationStr, 0x00, sizeof(aucSimPersonalisationStr));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*检查密码是否正确*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);

            /*密码正确，读取锁卡的字串*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                ulResult = NV_Read(en_NV_Item_Sim_Personalisation_Imsi_Str,
                                   aucSimPersonalisationStr,
                                   usDataLen);
                if (NV_OK != ulResult)
                {
                    if (ulResult == NV_ID_NOT_EXIST)
                    {
                        stMePersonalCnf.unReportContent.SimPersionalisationStr.DataLen = 0;
                        ulResult = TAF_PH_ME_PERSONALISATION_OK;
                    }
                    else
                    {
                        ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                    }
                }
                else
                {
                    stMePersonalCnf.unReportContent.SimPersionalisationStr.DataLen = aucSimPersonalisationStr[0];
                    (VOS_VOID)VOS_MemCpy(stMePersonalCnf.unReportContent.SimPersionalisationStr.aucSimPersonalisationStr,
                               aucSimPersonalisationStr + 1,
                               aucSimPersonalisationStr[0]
                               );
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}

/*****************************************************************************
 函 数 名  : MMA_IsSimLockPlmnInfoValid
 功能描述  : 当前NV项en_NV_Item_CustomizeSimLockPlmnInfo中PLMN信息是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年7月9日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_BOOL MMA_IsSimLockPlmnInfoValid(VOS_VOID)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    if (NV_OK != NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == stSimLockPlmnInfo.ulStatus)
    {
        return VOS_FALSE;
    }

    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (0xAA == stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[0])
        {
            continue;
        }

        break;
    }

    /* 如果每一项的PLMN都不是有效的，那么返回没有有效的PLMN信息 */
    if (TAF_MAX_SIM_LOCK_RANGE_NUM == i)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMA_GetCardLockInfo
 功能描述  : 获取 NV项中 CardLock的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_OP_ME_PERSONALISATION_RESULT
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009-10-28
    作    者   : l00130025
    修改内容   : 问题单号:AT2D15210,获取CardLockinfo
  2.日    期   : 2009年11月3日
    作    者   : l00130025,h44270
    修改内容   : 问题单号：AT2D15369/AT2D15244,CardLock异常处理和解锁后Sysinfo卡状态返回
  2.日    期   : 2010年7月19日
    作    者   : h44270
    修改内容   : 问题单号：DTS20100710000587,无卡时上报与标杆不一致
  3.日    期   : 2012年02月3日
    作    者   : f62575
    修改内容   : B050 SIMLOCK命令的硬加密改制功能: 解锁成功后，更新剩余解锁次数为最大值
  4.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 MMA_GetCardLockInfo(TAF_OPERATOR_LOCK_INFO_STRU *pstOperatorLockInfo)
{

    VOS_UINT32                          ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_OPERATOR_LOCK_INFO_STRU         *pstCardLockInfo;
    VOS_UINT8                           ucSimStatus;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    if (VOS_NULL_PTR == pstOperatorLockInfo)
    {
        return ulResult;
    }

    ulResult = TAF_PH_ME_PERSONALISATION_OK;
    pstCardLockInfo = &(g_stMmaMePersonalisationStatus.stCardLockInfo);

    if (NV_OK == NV_Read(en_NV_Item_CardlockStatus,
                            &stCardLockStatus,sizeof(stCardLockStatus)))
    {

        if (VOS_TRUE != stCardLockStatus.ulStatus)
        {
            /*更新运营商锁状态*/
            pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
        }
        else
        {
            /*更新运营商锁状态*/
            pstCardLockInfo->OperatorLockStatus= stCardLockStatus.enCardlockStatus;

            if (MMA_SIM_LOCK_IS_VERIFY == g_stMmaMePersonalisationStatus.SimLockStatus)
            {
                pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
            }
        }

        /* 更新剩余次数 */
        if (TAF_OPERATOR_LOCK_LOCKED == pstCardLockInfo->OperatorLockStatus)
        {
            pstCardLockInfo->RemainTimes = 0;
        }
        else if (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == pstCardLockInfo->OperatorLockStatus)
        {
            pstCardLockInfo->RemainTimes = g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes;
        }
        else
        {
            pstCardLockInfo->RemainTimes = stCardLockStatus.ulRemainUnlockTimes;
        }


    }
    else
    {
        pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_LOCKED;
        pstCardLockInfo->RemainTimes = 0;
    }

    /* 如果当前无卡，并且NV项en_NV_Item_CustomizeSimLockPlmnInfo中的
       PLMN无效的时候 */
    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
    if ((VOS_FALSE == MMA_IsSimLockPlmnInfoValid())
      &&(MMA_USIM_ABSENT == ucSimStatus))
    {
        pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
    }

    /*目前其他的数据卡在使用^cardlock这个命令时，上报的
      operator没有使用，所以在这里，把长度置0*/
    pstCardLockInfo->OperatorLen = 0;

    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    PS_MEM_CPY(pstOperatorLockInfo,
                   pstCardLockInfo,
                       sizeof(TAF_OPERATOR_LOCK_INFO_STRU));

    return ulResult;

}



/*****************************************************************************
 函 数 名  : MMA_MePersonlisationQuery
 功能描述  : 安全命令查询
 输入参数  : TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年3月15日
    作    者   : luojian 107747
    修改内容   : 新生成函数
  2.日    期   : 2009-08-25
    作    者   : h44270
    修改内容   : 问题单号:AT2D14070, MP对接的时候，激活锁卡功能以后，使用^CardLock命令和^sysinfo命令，上报的内容不正确
  3.日    期   : 2009-10-28
    作    者   : l00130025
    修改内容   : 问题单号:AT2D15210,Pin码开启时返回CardLock NV项中的值
  4.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  5.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
  7.日    期   : 2013年5月6日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
VOS_VOID MMA_MePersonlisationQuery(VOS_UINT16   ClientId,
                                  VOS_UINT8    OpId,
                                  TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;
    NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU   stMePersonActFlag;
    VOS_UINT16                          usDataLen = 2;
    VOS_UINT8                           ucSimStatus;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */


    stMePersonActFlag.usMePersonalActFlag = VOS_FALSE;

    PS_MEM_SET(&stMePersonalCnf,0,sizeof(TAF_PH_ME_PERSONLISATION_CNF_STRU));
    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);

    if (MMA_USIM_PRESENT != ucSimStatus)
    {
        if (MMA_USIM_ABSENT == ucSimStatus)
        {
            ulResult = MMA_GetCardLockInfo(&(stMePersonalCnf.unReportContent.OperatorLockInfo));
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_NO_SIM;
        }
    }
    else if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
    }
    else if (MMA_NONEED_PIN1 != MMA_CheckPin1SatusSimple())
    {
        ulResult = MMA_GetCardLockInfo(&(stMePersonalCnf.unReportContent.OperatorLockInfo));
    }
    else
    {
        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(pucImsi);

        if (USIMM_API_SUCCESS == ulGetCardImsiRslt)
        {
            (VOS_VOID)MMA_CheckMePersonalisationStatus();

            switch(stMePersonalData.MePersonalType)
            {
                /* this case is  used for clck query  */
                case TAF_SIM_PERSONALISATION:
                    ulResult = NV_Read(en_NV_Item_Me_Personalisation_Active_Flag,
                                       &stMePersonActFlag,
                                       usDataLen);
                    if (NV_OK != ulResult)
                    {
                        ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                        break;
                    }
                    g_MmaNewValue.usSimMePersonalisationActFlag = stMePersonActFlag.usMePersonalActFlag;

                    ulResult = TAF_PH_ME_PERSONALISATION_OK;
                    stMePersonalCnf.ActiveStatus = (VOS_UINT8)(stMePersonActFlag.usMePersonalActFlag);
                    break;
                case TAF_OPERATOR_PERSONALISATION:
                    ulResult = MMA_GetCardLockInfo(&(stMePersonalCnf.unReportContent.OperatorLockInfo));
                    break;
                default:
                    ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
                    break;
            }
        }
        else
        {
            if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
            {

#if (FEATURE_ON == FEATURE_PTM)
                /* 记录获取卡IMSI异常log */
                TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, pucImsi);
#endif
            }
            ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
        }
    }
    stMePersonalCnf.OpRslt              = (VOS_UINT8)ulResult;
    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);
}

/*****************************************************************************
 函 数 名  :  MMA_MePersonalisationHandle
 功能描述  : 通过传递的结构体变量，获取、
             校验、修改PIN或PUK的值，
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
             TAF_ME_PERSONALISATION_DATA_STRU   stPinData      PIN操作数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MMA_MePersonalisationHandle(VOS_UINT16 ClientId,
                                     VOS_UINT8 OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{


    switch (stMePersonalData.CmdType)
    {
        case  TAF_ME_PERSONALISATION_SET:
            MMA_MePersonlisationSet(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_VERIFY:
            MMA_MePersonlisationVerify(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_PWD_CHANGE:
            MMA_MePersonlisationPwdChange(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_ACTIVE:
            MMA_MePersonlisationActive(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_DEACTIVE:
            MMA_MePersonlisationDeactive(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_RETRIEVE:
            MMA_MePersonlisationRetrieve(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_QUERY:
            MMA_MePersonlisationQuery(ClientId, OpId, stMePersonalData);
            break;

        default:
            break;
    }


    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : MMA_GetCsimLockStatus
 功能描述  : 获取CSIM锁卡状态查询
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2015年12月22日
    作    者   : h00313353
    修改内容   : Sim Lock Status
*****************************************************************************/
VOS_UINT8 MMA_GetCsimMeLockStatus(
    VOS_VOID
)
{
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus;

    pucImsi         = TAF_SDC_GetCsimImsi();
    enCsimStatus    = TAF_SDC_GetCsimStatus();

    if ((TAF_SDC_USIM_STATUS_NO_PRESENT == enCsimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PIN    == enCsimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK    == enCsimStatus))
    {
        return TAF_PH_ME_NO_SIM;
    }

    if (pucImsi[0] >= TAF_SDC_MAX_IMSI_LEN)
    {
        return TAF_PH_ME_NO_SIM;
    }

    if (TAF_PH_ME_SIM_UNLOCK == g_stMmaMePersonalisationStatus.SimLockStatus)
    {
        (VOS_VOID)MMA_CheckCsimMePersonalisationStatus();
    }

    return g_stMmaMePersonalisationStatus.SimLockStatus;
}

/*****************************************************************************
 函 数 名  : MMA_GetCsimStatus
 功能描述  : 获取CSIM状态
 输入参数  : ulCsimStaChg:Csim卡状态是否发生改变标记
 输出参数  : 无
 返 回 值  : VOS_UINT8: Csim卡状态类型
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2015年12月22日
    作    者   : h00313353
    修改内容   : Sim Lock Status
*****************************************************************************/
VOS_UINT8 MMA_GetCsimStatus(
    VOS_UINT32                          ulCsimStaChg
)
{
    VOS_BOOL                            bCsSimStaus;
    VOS_BOOL                            bPsSimStaus;
    VOS_UINT8                           ucMeLockStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSdcSimStatus;
    VOS_UINT8                           ucCurPhMode;

    /* 快速开机时返回ROMSIM */
    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        return TAF_PH_USIM_ROMSIM;
    }

    enSdcSimStatus = TAF_SDC_GetCsimStatus();
    ucMeLockStatus = MMA_GetCsimMeLockStatus();

    /* 如果当前需要校验PIN码或卡处于锁定状态或卡不可用，则卡状态为无效状态 */
    if ((VOS_TRUE                    == g_ucUsimHotInFlag)
     || (TAF_SDC_USIM_STATUS_SIM_PIN == enSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == enSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID == enSdcSimStatus)
     || (MMA_SIM_IS_LOCK             == ucMeLockStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSdcSimStatus))
    {
        return TAF_PH_USIM_STATUS_UNAVAIL;
    }

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == enSdcSimStatus)
    {
        return TAF_PH_USIM_NON;
    }

    ucCurPhMode = (VOS_UINT8)TAF_SDC_GetCurPhoneMode();

    /* 关机状态或开机过程中或卡状态发生变化使用SDC中的卡状态上报 */
    if ((TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
     || (TAF_PH_MODE_FULL       != ucCurPhMode)
     || (VOS_TRUE               == ulCsimStaChg))
    {
        return enSdcSimStatus;
    }

    /* 通过SDC 接口获取CS/PS的卡是否无效信息, */
    bCsSimStaus = TAF_SDC_GetSimCsRegStatus();
    bPsSimStaus = TAF_SDC_GetSimPsRegStatus();
    if ((VOS_FALSE == bCsSimStaus)
     && (VOS_FALSE == bPsSimStaus))
    {
        return TAF_PH_USIM_STATUS_CSPS_UNVAIL;
    }

    if (VOS_FALSE == bCsSimStaus)
    {
        return TAF_PH_USIM_STATUS_CS_UNVAIL;
    }

    if (VOS_FALSE == bPsSimStaus)
    {
        return TAF_PH_USIM_STATUS_PS_UNVAIL;
    }

    return TAF_PH_USIM_STATUS_AVAIL;
}
#endif

/*****************************************************************************
 函 数 名  : MMA_GetMeLockStatus
 功能描述  : 锁卡状态查询
 输入参数  : VOS_UINT16                         ClientId
             VOS_UINT8                          OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月4日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
  4.日    期   : 2013年7月30日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目:g_ucMsccMsccNeedPin1全局变量删除,使用SDC中的SIM卡状态代替
*****************************************************************************/
VOS_UINT8 MMA_GetMeLockStatus(VOS_VOID)
{
    VOS_UINT8                          ucSimStatus;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    VOS_UINT8                           ucSdcSimStatus;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
    if (MMA_USIM_PRESENT != ucSimStatus)
    {
        return TAF_PH_ME_NO_SIM;
    }

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    ucSdcSimStatus = TAF_SDC_GetUsimStatus();

    if ((TAF_SDC_USIM_STATUS_SIM_PIN == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == ucSdcSimStatus))
    {
        return TAF_PH_ME_NO_SIM;
    }
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */

    /* 如果当前没有获取到IMSI,重新获取一次 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    if (pucImsi[0] > 8)
    {
        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(pucImsi);

        if (USIMM_API_SUCCESS == ulGetCardImsiRslt)
        {
            /* 检查是否锁卡 */
            (VOS_VOID)MMA_CheckMePersonalisationStatus();
        }
        else
        {
            if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
            {

#if (FEATURE_ON == FEATURE_PTM)
                /* 记录获取卡IMSI异常log */
                TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, pucImsi);
#endif
            }

            return TAF_PH_ME_NO_SIM;
        }
    }
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    if (g_stMmaMePersonalisationStatus.SimLockStatus == 1)
    {
        return TAF_PH_ME_SIM_LOCK;
    }
    return TAF_PH_ME_SIM_UNLOCK;
}

/*****************************************************************************
 函 数 名  : MMA_OpPinExpired
 功能描述  : PIN 超时处理函数，返回PIN 超时结果给上层AT
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月1日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，使用宏替代了原有的常数

  3.日    期   : 2006年3月20日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02602
*****************************************************************************/
VOS_VOID MMA_OpPinExpired(VOS_VOID)
{
    /*超时消息有效性判断*/
    if ( MMA_TIMER_RUN != g_MmaSimTimer[0].ucTimerStatus  )
    {
        MMA_WARNINGLOG("MMA_OpPinExpired():WARNING:OP PIN TIMER is not running!");
        return;
    }
    MMA_WARNINGLOG("MMA_OpPinExpired():WARNING:OP PIN TIMER OUT!");
    /*设置停止定时器标志*/
    g_MmaSimTimer[0].ucTimerStatus           = MMA_TIMER_STOP;
    /*清除使用标志*/
    gastMmaTiTab[MMA_PH_PIN_TI].ucUsed       = MMA_TI_UNUSED;
    /*错误处理*/
    MMA_HandleEventError(gastMmaTiTab[MMA_PH_PIN_TI].ClientId, gastMmaTiTab[MMA_PH_PIN_TI].Id, TAF_ERR_TIME_OUT, TAF_PH_EVT_OP_PIN_CNF);
    return;
}

/* 删除 MMA_SendPINOk函数 ，该函数没有地方调用 */

/*****************************************************************************
 函 数 名  : MN_PH_PinOper
 功能描述  : 非查询PIN操作处理
 输入参数  : VOS_VOID
 输出参数  : pstPinInfo  : sim卡返回PIN操作相关结果
 返 回 值  : VOS_UINT32:VOS_OK:  可以上报
                        VOS_ERR: 需等定时器超时后才能上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月12日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
  3.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : DTS2013071900570:SVLTE特性开启时候，MODEM1解pin后，MODEM0收到
                卡状态为AVAILABLE时候，没有发起重启。原因在于:
                当前解PIN码之前，SDC中维护的卡状态为TAF_SDC_USIM_STATUS_VALID，
                MODEM在收到解PIN的RSP消息时候，才会将SDC的卡状态重新设置为TAF_SDC_USIM_STATUS_UNVALID
                ，这样再收到USIM上报的卡状态为AVAILABLE时候，会发起重启。
                修改为SDC存储SIM卡的原始状态，MODEM在收到解PIN的RSP消息时候,
                不需重新设置SIM状态为TAF_SDC_USIM_STATUS_UNVALID。MODEM的重启
                由SIM卡状态的变迁来决定。如:卡状态由SIM_PIN--->AVAIALBLE,则触发
                重启动。
  4.日    期   : 2013年7月30日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目:g_ucMsccMsccNeedPin1全局变量删除,使用SDC中的SIM卡状态代替
*****************************************************************************/
VOS_UINT32 MN_PH_PinOper(
    const TAF_PH_PIN_CNF_STRU           *pstPinInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucMmaImsi[9];
    VOS_UINT32                          ulPin1;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    VOS_UINT8                           ucSdcSimStatus;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    ucSdcSimStatus  = (VOS_UINT8)TAF_SDC_GetSimStatus();
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */

    /* 获取当前是否能获取到IMSI,能获取到则不用启动定时器 */
    ulPin1 = MMA_Pin1Noneed();

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    if ((VOS_TRUE == MMA_OpPin1Success(pstPinInfo))
     && (VOS_TRUE == ulPin1)
     && ((TAF_SDC_USIM_STATUS_SIM_PIN == ucSdcSimStatus)
      || (TAF_SDC_USIM_STATUS_SIM_PUK == ucSdcSimStatus)))
    {

        /* 关机状态下解PIN,不能把MMA状态置为开机状态 */
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */

        /*A32D11538==>需要输入PIN码时,MMA模块初始化时认为有卡*/

        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(aucMmaImsi);

        if (USIMM_API_SUCCESS == ulGetCardImsiRslt)
        {
            MMA_INFOLOG("MN_PH_PinOper():Info :USIMM_GetCardIMSI OK!");
            return VOS_OK;
        }

        /* 获取IMSI失败 */
        if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录获取卡IMSI异常log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, aucMmaImsi);
#endif
        }

        /* PIN OK后USIM需要初始化，需要延时以保证读取IMSI正常 */
        g_stPhPhResetTimer.ulTimerId = TI_MN_PH_PIN_OPER;

        ulRet = NAS_StartRelTimer( &g_stPhPhResetTimer.MmaHTimer,
                                     WUEPS_PID_MMA,
                                     TI_MN_PH_PIN_OPER_LENGTH,
                                     TAF_MMA,
                                     TI_MN_PH_PIN_OPER,
                                     VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRet)
        {
            MMA_ERRORLOG("MN_PH_PinOper():ERROR:Start TI_MN_PH_PIN_OPER Timer Error!");
        }
        else
        {
            g_stPhPhResetTimer.ucTimerStatus = MMA_TIMER_RUN;
        }
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MMA_PinDataReport
 功能描述  : 将USIM传入的关于PIN操作的确认信息打包，
             发送至MUX
 输入参数  : const TAF_PH_PIN_CNF_STRU *pstPinCnf  收到PIN数据包
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月1日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，增加OP初始化

  3.日    期   : 2006年3月14日
    作    者   : liuyang id:48197
    修改内容   : 增加内部启动过程流程,问题单号:A32D02500

  4.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02382
  5.日    期   : 2006年3月21日
    作    者   : liuyang id: 48197
    修改内容   : 问题单号：A32D02602
  6.日    期   : 2008年7月28日
    作    者   : luojian id:107747
    修改内容   : 问题单号：AT2D04707/AT2D04722
  7.日    期   : 2008年12月15日
    作    者   : h44270
    修改内容   : 问题单号：AT2D07140
  8.日    期   : 2010年3月12日
    作    者   : zhoujun /z40661
    修改内容   : VOS_TaskDelay清理
  9.日    期   : 2010年12月22日
    作    者   : w00166186
    修改内容   : PUK校验失败后上报有误
 10.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  11.日    期   : 2012年04月16日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目修改
  12.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID MMA_PinDataReport( const TAF_PH_PIN_CNF_STRU *pstPinCnf)
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;
    VOS_UINT32                          ulRet;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_InitAtMsgReq:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /*参数有效性判断*/
    if ( VOS_NULL_PTR == pstPinCnf)
    {
        MMA_WARNINGLOG("MMA_PinDataReport():WARNING:pPinCnf is NULL PTR!.");
        MMA_HandleEventError(gstMmaValue.stOpPinData.ClientId,
                             gstMmaValue.stOpPinData.OpId,
                             TAF_ERR_NULL_PTR,
                             TAF_PH_EVT_OP_PIN_CNF);
        PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
        return;
    }
    MMA_InitEventInfoOP(pstPhoneEvent);
    /*调用TAF事件上报函数,上报PIN事件*/
    pstPhoneEvent->OP_Pin                    = VOS_TRUE;
    pstPhoneEvent->PinCnf                    = *pstPinCnf;
    pstPhoneEvent->PhoneEvent                = TAF_PH_EVT_OP_PIN_CNF;

    /*非查询状态下，要停止定时器*/
    if ( (TAF_PIN_QUERY != pstPinCnf->CmdType)
     && (TAF_PIN2_QUERY != pstPinCnf->CmdType) )
    {
        /*停止定时器*/
        if ( MMA_TIMER_RUN == g_MmaSimTimer[0].ucTimerStatus )
        {
            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA, TAF_USIM_OPPIN, &(g_MmaSimTimer[0].MmaHTimer)))
            {
                MMA_WARNINGLOG("MMA_PinDataReport():WARNING:NAS_StopRelTimer failed!");
            }

            /*设置停止定时器标志*/
            g_MmaSimTimer[0].ucTimerStatus    = MMA_TIMER_STOP;
        }
        switch ( pstPinCnf->OpPinResult )
        {
            case USIMM_SIM_PIN_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PIN1;
                break;
            case USIMM_SIM_PIN2_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PIN2;
                break;
            case USIMM_SIM_PUK_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PUK1;
                break;
            case USIMM_SIM_PUK2_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PUK2;
                break;
            case USIMM_INCORRECT_PASSWORD:
                if ((TAF_SIM_PUK == pstPhoneEvent->PinCnf.PinType) && (0 == pstPhoneEvent->PinCnf.RemainTime.ucPuk1RemainTime))
                {
                    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_SIM_FAIL;
                }
                else
                {
                    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_INCORRECT_PASSWORD;
                }
                break;
            case USIMM_OPERATION_NOT_ALLOW:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OPERATION_NOT_ALLOW;
                break;
            case USIMM_SIM_FAILURE:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_SIM_FAIL;
                break;
            case USIMM_API_SUCCESS:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OK;
                break;
            default:
                MMA_WARNINGLOG1("MMA_PinDataReport():WARNING:WRONG PIN RESULT is", pstPhoneEvent->PinCnf.OpPinResult);
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_PIN_ERROR;
                break;
        }
    }

    ulRet = VOS_OK;

    if ( ((TAF_PIN_QUERY != pstPinCnf->CmdType) && (TAF_PIN2_QUERY != pstPinCnf->CmdType))
      && (TAF_PH_OP_PIN_OK == pstPhoneEvent->PinCnf.OpPinResult))
    {
        ulRet = MN_PH_PinOper(pstPinCnf);
    }

    /*获取当前是否能上报,如果需要启动定时器则需等定时器超时后才能上报 */
    if ( VOS_OK == ulRet)
    {
        Taf_PhoneEvent(pstPhoneEvent);
    }
    else
    {
        PS_MEM_CPY(&g_stPhPinCnf,&pstPhoneEvent->PinCnf,sizeof(g_stPhPinCnf));
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return;
}

/* MMA_PhoneGetNetworkNameFromUsim */

/*MMA_PhoneGetNetworkName*/



/*****************************************************************************
 函 数 名  : TAF_MMA_GetPlmnPnnIndexInOplFile
 功能描述  : 从OPL中查找指定plmn对应的PNN Index
 输入参数  : pstPlmnId - 网络ID
             pstOplFileInfo - opl文件内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPlmnPnnIndexInOplFile(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId,
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usAppCampLac;
    VOS_CHAR                            cWildCard;

    usAppCampLac    = TAF_SDC_GetAppCampLac();
    cWildCard       = TAF_SDC_GetPlmnCompareWildCard();

    for (ulIndex = 0; ulIndex < pstOplFileInfo->ulOplRecordNum; ulIndex++)
    {
        /* 不支持plmn通配符比较 */
        if (0 == cWildCard)
        {
            if (VOS_FALSE == TAF_SDC_CompareBcchPlmnwithSimPlmn(pstPlmnId, &pstOplFileInfo->astOplRecordInfo[ulIndex].stPlmnId))
            {
                continue;
            }
        }
        else
        {
            if (VOS_FALSE == TAF_SDC_CompareBcchPlmnwithSimPlmn_WithWildcard(pstPlmnId, &pstOplFileInfo->astOplRecordInfo[ulIndex].stPlmnId, cWildCard))
            {
                continue;
            }
        }

        if ((TAF_SDC_VALID_LAC_RANGE_LOW == pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeLow)
         && (TAF_SDC_VALID_LAC_RANGE_HIGH == pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeHigh))
        {
            return pstOplFileInfo->astOplRecordInfo[ulIndex].usPnnIndex;
        }

        if ((usAppCampLac >= pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeLow)
         && (usAppCampLac <= pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeHigh))
        {
            return pstOplFileInfo->astOplRecordInfo[ulIndex].usPnnIndex;
        }
    }

    return TAF_SDC_INVALID_PNN_INDEX;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Get7BitNetworkNameStr
 功能描述  : 把7bit编码的网络名称转换为字符串
 输入参数  : pstNetworkLongName  - 7bit编码的长名
             pstNetworkShortName - 7bit编码的短名
 输出参数  : pstOperatorName    - 转换为字符串后的长短名信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_Get7BitNetworkNameStr(
    TAF_SDC_OPERATOR_NAME_STRU         *pstNetworkLongName,
    TAF_SDC_OPERATOR_NAME_STRU         *pstNetworkShortName,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU     *pstOperatorName
)
{
    VOS_UINT32                                              ulRet;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    stMmcName;
    VOS_UINT8                                               ucNetworkNameValidFlag;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType;

    ucNetworkNameValidFlag = VOS_FALSE;
    PS_MEM_SET(&stMmcName, 0, sizeof(stMmcName));
    enCopsFormatType       = TAF_SDC_GetCopsFormatType();

    ulRet = TAF_MMA_TranslateNtwkName2Str(pstNetworkLongName,
                                          (VOS_CHAR *)stMmcName.aucOperatorNameLong,
                                          TAF_PH_OPER_NAME_LONG);
    if ((TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType)
      && (VOS_TRUE == ulRet))
    {
        PS_MEM_CPY(pstOperatorName->aucLongName,
                   stMmcName.aucOperatorNameLong,
                   sizeof(pstOperatorName->aucLongName));
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    ulRet = TAF_MMA_TranslateNtwkName2Str(pstNetworkShortName,
                                          (VOS_CHAR *)stMmcName.aucOperatorNameShort,
                                          TAF_PH_OPER_NAME_SHORT);

    if ((TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType)
     && (VOS_TRUE == ulRet))
    {
        PS_MEM_CPY(pstOperatorName->aucShortName,
                   stMmcName.aucOperatorNameShort,
                   sizeof(pstOperatorName->aucShortName));
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if (VOS_TRUE == ucNetworkNameValidFlag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetUcs2NetworkName
 功能描述  : 获取UCS2编码的网络运营商名称
 输入参数  : pstIeNtwkLongName  - 运营商长名
             pstIeNtwkShortName - 运营商短名
             enNetNameCodeScheme - 运营商名称编码方式
 输出参数  : pstOperatorName    - UCS2编码的 长短名信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetUcs2NetworkName(
    TAF_SDC_OPERATOR_NAME_STRU                             *pstIeNtwkLongName,
    TAF_SDC_OPERATOR_NAME_STRU                             *pstIeNtwkShortName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName
)
{
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmPlmnInfo;
    VOS_UINT8                           ucNetworkNameValidFlag;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 enCopsFormatType;

    PS_MEM_SET(&stMmPlmnInfo, 0, sizeof(TAF_MMA_MM_INFO_PLMN_NAME_STRU));

    enCopsFormatType       = TAF_SDC_GetCopsFormatType();
    ucNetworkNameValidFlag = VOS_FALSE;

    pstOperatorName->ucLongNameLen = TAF_MMA_TranslateOperatorName2UCS2(pstIeNtwkLongName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucLongName),
                                                         TAF_PH_OPER_NAME_LONG);

    if ((((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
       && (TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType))
      || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
     && (0 != pstOperatorName->ucLongNameLen))
    {
        PS_MEM_CPY(pstOperatorName->aucLongName,
                   stMmPlmnInfo.aucLongName,
                   pstOperatorName->ucLongNameLen);

        ucNetworkNameValidFlag = VOS_TRUE;
    }

    pstOperatorName->ucShortNameLen = TAF_MMA_TranslateOperatorName2UCS2(pstIeNtwkShortName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucShortName),
                                                        TAF_PH_OPER_NAME_SHORT);

    if ((((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
       && (TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType))
      || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
     && (0 != pstOperatorName->ucShortNameLen))
    {
        PS_MEM_CPY(pstOperatorName->aucShortName,
                   stMmPlmnInfo.aucShortName,
                   pstOperatorName->ucShortNameLen);

        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if (VOS_TRUE == ucNetworkNameValidFlag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPnnNetWorkName
 功能描述  : 从PNN中获取网络运营商名称
 输入参数  : pstPlmnId           - plmn id
             enNetNameCodeScheme - 编码方式
 输出参数  : pstOperatorName     - 运营商名称信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPnnNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstPlmnName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    TAF_PH_ROAM_STA                     ucIsRoamFlag;
    VOS_UINT32                          ulPnnIndex;
    VOS_UINT32                          ulRet;
    TAF_SDC_FILE_TYPE_ENUM_UINT8        enValidOplFileType;
    TAF_SDC_FILE_TYPE_ENUM_UINT8        enValidPnnFileType;

    enValidOplFileType = TAF_SDC_GetOplFileType();
    enValidPnnFileType = TAF_SDC_GetPnnFileType();

    ucIsRoamFlag       = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());

    /* 不支持PNN返回失败 */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_PNN))
    {
        return VOS_FALSE;
    }

    /* pnn和opl文件类型不一致,且opl记录个数不为空，返回失败 */
    if ((enValidPnnFileType != enValidOplFileType)
     && (enValidOplFileType != TAF_SDC_FILE_TYPE_BUTT))
    {
        return VOS_FALSE;
    }

    /* OPL和PNN文件记录个数为0返回失败 */
    if ((TAF_SDC_FILE_TYPE_BUTT == enValidPnnFileType)
     && (TAF_SDC_FILE_TYPE_BUTT == enValidOplFileType))
    {
        return VOS_FALSE;
    }

    pstOplFileInfo     = TAF_SDC_GetUsimOplFileInfo();
    pstPnnFileInfo     = TAF_SDC_GetUsimPnnFileInfo();

    if (TAF_SDC_FILE_TYPE_SIM == enValidPnnFileType)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }


    /* OPL文件记录为0，PNN文件记录不为0且驻留hplmn上，返回PNN文件第一条记录对应的运营商名称 */
    if ((0 == pstOplFileInfo->ulOplRecordNum)
     && (TAF_PH_NO_ROAM == ucIsRoamFlag))
    {
        ulPnnIndex = 1;
    }
    else
    {
        /* OPL和PNN文件记录都不为0 */
        ulPnnIndex = TAF_MMA_GetPlmnPnnIndexInOplFile(pstPlmnId, pstOplFileInfo);
    }

    /* 从OPL中获取的PNN index非法，最大支持100个，返回失败 */
    if ((ulPnnIndex < TAF_SDC_VALID_PNN_LOW_INDEX)
     || (ulPnnIndex > TAF_SDC_PNN_MAX_RECORD_NUM))
    {
        return VOS_FALSE;
    }

    /* 从OPL中获取的PNN index合法,从PNN中获取7 bit编码的运营商名称 */
    if (TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT == enNetNameCodeScheme)
    {
        ulRet = TAF_MMA_Get7BitNetworkNameStr(&pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong,
                                 &pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort,
                                 pstPlmnName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }


    /* 从OPL中获取的PNN index合法,从PNN中获取UCS2编码的运营商名称 */
    if ((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
     || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
    {
        ulRet = TAF_MMA_GetUcs2NetworkName(&pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong,
                        &pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort,
                        enNetNameCodeScheme,
                        pstPlmnName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetCphsNetWorkName
 功能描述  : 从CPHS中获取网络运营商名称
 输入参数  : enNetNameCodeScheme - 编码方式
 输出参数  : pstOperatorName     - 运营商名称信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetCphsNetWorkName(
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_CPHS_FILE_INFO_STRU        *pstCphsFileInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    TAF_PH_ROAM_STA                     ucIsRoamFlag;

    ucIsRoamFlag    = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());
    pstCphsFileInfo = TAF_SDC_GetChpsFileInfo();

    /* 不支持CPHS返回失败 */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_CPHS))
    {
        return VOS_FALSE;
    }

    /* 卡文件不存在或文件长度为0返回失败 */
    if (0 == pstCphsFileInfo->stCPHSOperName.ucLength)
    {
        return VOS_FALSE;
    }

    /* 驻留在hplmn才使用cphs信息 */
    if (TAF_PH_ROAMING == ucIsRoamFlag)
    {
        return VOS_FALSE;
    }

    if (TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT == enNetNameCodeScheme)
    {
        ulRet = TAF_MMA_Get7BitNetworkNameStr(&pstCphsFileInfo->stCPHSOperName,
                                              &pstCphsFileInfo->stCPHSOperName,
                                              pstOperatorName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }
    }

    /* CPHS不存在UCS2编码，返回失败 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetMmInfoNetWorkName
 功能描述  : 从MM INFO中获取网络运营商名称
 输入参数  : pstPlmnId           - plmn id
             enNetNameCodeScheme - 编码方式
 输出参数  : pstOperatorName     - 运营商名称信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetMmInfoNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_MM_INFO_STRU               *pstMmInfo           = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstMmInfo           = TAF_SDC_GetMmInfo();

    /* 不支持MM INFO返回失败 */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_MMINFO))
    {
        return VOS_FALSE;
    }

    /* 当前驻留网络与收到MM INFO的网络不相同返回失败 */
    if (VOS_FALSE == TAF_SDC_CompareBcchPlmnwithSimPlmn(pstPlmnId, &pstMmInfo->stOperatorPlmnId))
    {
        return VOS_FALSE;
    }

    if (TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT == enNetNameCodeScheme)
    {
        ulRet = TAF_MMA_Get7BitNetworkNameStr(&pstMmInfo->stOperatorNameLong,
                                              &pstMmInfo->stOperatorNameShort,
                                              pstOperatorName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    if ((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
     || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
    {
        ulRet = TAF_MMA_GetUcs2NetworkName(&pstMmInfo->stOperatorNameLong,
                                           &pstMmInfo->stOperatorNameShort,
                                           enNetNameCodeScheme,
                                           pstOperatorName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetSpnNetWorkName
 功能描述  : 从SPN中获取网络运营商名称
 输入参数  : pstPlmnId - plmn id
             enNetNameCodeScheme - 网络名称编码方式
 输出参数  : pstOperatorName - 运营商名称信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetSpnNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_SPN_FILE_INFO_STRU         *pstUsimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_SPN_FILE_INFO_STRU         *pstSimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_SPDI_FILE_INFO_STRU        *pstSpdiFileInfo = VOS_NULL_PTR;
    TAF_PH_ROAM_STA                     ucIsRoamFlag;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SPN_FILE_INFO_STRU          stSpnFileInfo;
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmPlmnInfo;

    enSysMode           = TAF_SDC_GetAppSysMode();
    pstUsimSpnFileInfo  = TAF_SDC_GetUsimSpnFileInfo();
    pstSimSpnFileInfo   = TAF_SDC_GetSimSpnFileInfo();
    pstSpdiFileInfo     = TAF_SDC_GetSpdiFileInfo();
    ucIsRoamFlag        = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());
    PS_MEM_SET(&stSpnFileInfo, 0, sizeof(stSpnFileInfo));
    PS_MEM_SET(&stMmPlmnInfo, 0, sizeof(stMmPlmnInfo));

    /* 不支持SPN返回失败 */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_SPN))
    {
        return VOS_FALSE;
    }

    /* 当前驻留网络不是HPLMN或不在EFSPDI文件记录的PLMN列表中，返回失败 */
    if ((VOS_FALSE == TAF_SDC_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId, pstSpdiFileInfo->ucServiceProviderPlmnNum, pstSpdiFileInfo->astSeriveProviderPlmn))
     && (TAF_PH_ROAMING == ucIsRoamFlag))
    {
        return VOS_FALSE;
    }

    /* 31102协议描述:
    b1=0: display of registered PLMN name not required when registered PLMN is either HPLMN or a PLMN in the service provider PLMN list (see EFSPDI).
    B1=1: display of registered PLMN name required when registered PLMN is either HPLMN or a PLMN in the service provider PLMN list(see EFSPDI).
    B2=0: display of the service provider name is required when registered PLMN is neither HPLMN nor a PLMN in the service provider PLMN list(see EFSPDI).
    B2=1: display of the service provider name is not required when registered PLMN is neither HPLMN nor a PLMN in the service provider PLMN list(see EFSPDI).*/
    /* 驻留w或l，如果usim spn文件长度为0或显示模式不对返回失败 */
    if ((TAF_SDC_SYS_MODE_WCDMA == enSysMode)
     || (TAF_SDC_SYS_MODE_LTE == enSysMode))
    {
        if ((0 == pstUsimSpnFileInfo->stSpnOperName.ucLength)
         || (0 != (pstUsimSpnFileInfo->ucDispRplmnMode & 0x02)))
        {
            return VOS_FALSE;
        }

        stSpnFileInfo = *pstUsimSpnFileInfo;
    }

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        if ((0 == pstSimSpnFileInfo->stSpnOperName.ucLength)
         || (0 != (pstSimSpnFileInfo->ucDispRplmnMode & 0x02)))
        {
            return VOS_FALSE;
        }

        stSpnFileInfo = *pstSimSpnFileInfo;
    }

    if (TAF_PH_GSM_7BIT_DEFAULT == enNetNameCodeScheme)
    {
        /* UCS2编码返回失败 */
        if (TAF_PH_RAW_MODE == stSpnFileInfo.stSpnOperName.bitCoding)
        {
            return VOS_FALSE;
        }

        pstOperatorName->ucLongNameLen = stSpnFileInfo.stSpnOperName.ucLength;

        if (pstOperatorName->ucLongNameLen > TAF_PH_OPER_NAME_LONG)
        {
            pstOperatorName->ucLongNameLen = TAF_PH_OPER_NAME_LONG;
        }

        PS_MEM_CPY(pstOperatorName->aucLongName, stSpnFileInfo.stSpnOperName.aucOperatorName, pstOperatorName->ucLongNameLen);

        pstOperatorName->ucShortNameLen = stSpnFileInfo.stSpnOperName.ucLength;

        if (pstOperatorName->ucShortNameLen > TAF_PH_OPER_NAME_SHORT)
        {
            pstOperatorName->ucShortNameLen = TAF_PH_OPER_NAME_SHORT;
        }

        PS_MEM_CPY(pstOperatorName->aucShortName, stSpnFileInfo.stSpnOperName.aucOperatorName, pstOperatorName->ucShortNameLen);

        return VOS_TRUE;
    }

    if ((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
     || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
    {
        pstOperatorName->ucLongNameLen = TAF_MMA_TranslateOperatorName2UCS2(&stSpnFileInfo.stSpnOperName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucLongName),
                                                         TAF_PH_OPER_NAME_LONG);

        if (0 != pstOperatorName->ucLongNameLen)
        {
            PS_MEM_CPY(pstOperatorName->aucLongName,
                       stMmPlmnInfo.aucLongName,
                       pstOperatorName->ucLongNameLen);

        }

        pstOperatorName->ucShortNameLen = TAF_MMA_TranslateOperatorName2UCS2(&stSpnFileInfo.stSpnOperName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucShortName),
                                                        TAF_PH_OPER_NAME_SHORT);

        if (0 != pstOperatorName->ucShortNameLen)
        {
            PS_MEM_CPY(pstOperatorName->aucShortName,
                       stMmPlmnInfo.aucShortName,
                       pstOperatorName->ucShortNameLen);

        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetNvimNetWorkName
 功能描述  : 从NVIM中获取网络运营商名称
 输入参数  : 无
 输出参数  : pstOperatorName - 运营商名称信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetNvimNetWorkName(
    TAF_PH_NETWORKNAME_STRU            *pstOperatorName
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNetworkNameValidFlag;
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU *pstCustomOperNameInfo = VOS_NULL_PTR;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 enCopsFormatType;

    enCopsFormatType       = TAF_SDC_GetCopsFormatType();
    pstCustomOperNameInfo  = TAF_SDC_GetCustomOperNameInfo();
    ucNetworkNameValidFlag = VOS_FALSE;

    /* 从NV项中查询PLMN ID对应的运营商名称*/
    for (ucIndex = 0; ucIndex < TAF_NVIM_STORED_OPER_NAME_NUM; ucIndex++)
    {
        if (VOS_TRUE == TAF_SDC_CompareBcchPlmnwithSimPlmn((TAF_SDC_PLMN_ID_STRU *)&pstOperatorName->Name.PlmnId, &pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorPlmnId))
        {
            if ((TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType)
             && ('\0' != pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameLong.aucOperatorName[0]))
            {
                PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameLong, pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameLong.aucOperatorName, NV_ITEM_OPER_NAME_LONG);
                ucNetworkNameValidFlag = VOS_TRUE;
            }

            if((TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType)
              && ('\0' != pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameShort.aucOperatorName[0]))
            {
                PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameShort, pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameShort.aucOperatorName,NV_ITEM_OPER_NAME_SHORT);
                ucNetworkNameValidFlag = VOS_TRUE;
            }

            if (VOS_TRUE == ucNetworkNameValidFlag)
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetStoredInternalNetWorkName
 功能描述  : 从gastNetworkNameTbl全局变量中获取网络运营商名称
 输入参数  : 无
 输出参数  : pstOperatorName - 运营商名称信息
 返 回 值  : VOS_TRUE  - 获取成功
             VOS_FALSE - 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetStoredInternalNetWorkName(
    TAF_PH_NETWORKNAME_STRU            *pstOperatorName
)
{
    TAF_PH_OPERATOR_NAME_STRU           stOperName;
    VOS_UINT8                           ucNetworkNameValidFlag;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 enCopsFormatType;

    stOperName.PlmnId      = pstOperatorName->Name.PlmnId;
    enCopsFormatType       = TAF_SDC_GetCopsFormatType();
    ucNetworkNameValidFlag = VOS_FALSE;
    PS_MEM_CPY(stOperName.aucOperatorNameLong, pstOperatorName->Name.aucOperatorNameLong, sizeof(stOperName.aucOperatorNameLong));
    PS_MEM_CPY(stOperName.aucOperatorNameShort, pstOperatorName->Name.aucOperatorNameShort, sizeof(stOperName.aucOperatorNameShort));

    if (MMA_FAILURE == MMA_PhoneFindNtwkNameByPlmnId(&stOperName))
    {
        return VOS_FALSE;
    }

    if ((TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType)
      && ('\0' != stOperName.aucOperatorNameLong[0]))
    {
        PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameLong, stOperName.aucOperatorNameLong, TAF_PH_OPER_NAME_LONG);
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if((TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType)
    && ('\0' != stOperName.aucOperatorNameShort[0]))
    {
        PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameShort, stOperName.aucOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if (VOS_TRUE == ucNetworkNameValidFlag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* delete TAF_MMA_GetCopsNetWorkName */



/* 删除MMA_PhoneGetCellRoam */

/*****************************************************************************
 函 数 名  : Taf_PhoneGetNetworkNameForListPlmn
 功能描述  : 获取SPN
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月18日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2009年10月12日
    作    者   : l00130025
    修改内容   : 问题单号: AT2D15082,list搜网时,只显示运营商列表的中的值
*****************************************************************************/
TAF_UINT32 Taf_PhoneGetNetworkNameForListPlmn(TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName)
{
    VOS_UINT32                ulRet = MMA_FAILURE;

    pstOperName->OperName.aucOperatorNameLong[0]  = '\0';
    pstOperName->OperName.aucOperatorNameShort[0] = '\0';

    if ((0 == pstOperName->OperName.PlmnId.Mcc) && (0 == pstOperName->OperName.PlmnId.Mnc))
    {
        return ulRet;
    }

    /* 从运营商列表中查询PLMNID对应的名称 */
    ulRet = MMA_PhoneFindNtwkNameByPlmnId(&(pstOperName->OperName));

    return ulRet;
}


/* 删除MMA_PhoneGetRoamSta */


/*****************************************************************************
 函 数 名  : MMA_PhoneGetDomain
 功能描述  : 获取系统网络域状态
 输入参数  : VOS_UINT16  ClientId
             VOS_UINT8         OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    作    者   : liuyang
    修改内容   :V200R001 新生成函数
  2.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
*****************************************************************************/
VOS_VOID MMA_PhoneGetDomain(VOS_UINT16  ClientId,  VOS_UINT8  OpId)
{
    TAF_PH_DOMAIN_FLAG       PhDomain;

    /*从status中获取当前域状态*/
    PhDomain = gstMmaValue.pg_StatusContext->ucDomainFlag;

    /*使用数据上报函数将数据传至TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_DOMAIN_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)&PhDomain);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMA_MntnTraceGetUsimStatus
 功能描述  : 可维可测钩包: 输出MMA_GetUsimStatus函数中的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月14日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年07月09日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012061209698,增加USIM卡热插拔可维可测信息
  3.日    期   : 2013年4月4日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_UINT32 NAS_MMA_MntnTraceGetUsimStatus(
    VOS_UINT8                           ucUsimStatus,
    VOS_UINT8                           ucMeLockStatus
)
{
    NAS_MMA_MNTN_GET_USIM_STATUS_STRU   *pstSendMsg;
    NAS_MMA_USIM_STATUS_INFO_STRT       *pstUsimStatusInfo;

    pstSendMsg = (NAS_MMA_MNTN_GET_USIM_STATUS_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_MNTN_GET_USIM_STATUS_STRU));

    if ( VOS_NULL_PTR == pstSendMsg )
    {
        MMA_ERRORLOG("NAS_MMA_MntnTraceGetUsimStatus:ERROR: Alloc Memory Fail.");
        return MMA_ERROR;
    }

    pstUsimStatusInfo = &pstSendMsg->stStatusInfo;

    pstUsimStatusInfo->ulUsimHotInFlg           = g_ucUsimHotInFlag;
    pstUsimStatusInfo->ulUsimHotOutFlg          = g_ucUsimHotOutFlag;

    pstUsimStatusInfo->ulUsimHotInCount         = g_ulUsimHotInCount;
    pstUsimStatusInfo->ulUsimHotOutCount        = g_ulUsimHotOutCount;

    pstUsimStatusInfo->ucUsimStatusFromUsim     = ucUsimStatus;
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-30, end */
    pstUsimStatusInfo->ucMeLockStatus           = ucMeLockStatus;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    pstUsimStatusInfo->ucMmaGlobalUsimStatus    = (VOS_UINT8)TAF_SDC_GetSimStatus();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    pstSendMsg->ulReceiverPid                   = WUEPS_PID_MMA;
    pstSendMsg->ulSenderPid                     = WUEPS_PID_MMA;
    pstSendMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstSendMsg->ulLength                        = sizeof(NAS_MMA_USIM_STATUS_INFO_STRT) + 4;
    pstSendMsg->ulMsgID                         = ID_NAS_MMA_MNTN_GET_USIM_STATUS;

    DIAG_TraceReport(pstSendMsg);
    PS_FREE_MSG(WUEPS_PID_MMA, pstSendMsg);

    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Mm_GetUsimStatus
 功能描述  : 获取USIM的状态
 输入参数  : ulUsimStaChg--卡状态是否改变标记
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年11月07日
    作    者   : x51137
    修改内容   :V200R001 新生成函数
  2.日    期   : 2008年12月24日
    作    者   : h44270
    修改内容   :AT2D07802,PUK解锁命令at^cpin="11111111","1234"执行后,错误上报SIM卡状态
  3.日    期   : 2009-08-25
    作    者   : h44270
    修改内容   : 问题单号:AT2D14070, MP对接的时候，激活锁卡功能以后，使用^CardLock命令和^sysinfo命令，上报的内容不正确
  3.日    期   : 2010-12-24
    作    者   : w00166186
    修改内容   : 问题单号:DTS2010121004198, USIM初始化失败后，向WEB UI的上报有误
  4.日    期   : 2011年04月14日
    作    者   : 欧阳飞
    修改内容   : DTS2011041202700,在PS域卡无效后，状态又迁到受限服务，导致应用查询SYSINFO
                 时显示卡有效。
  5.日    期   : 2012年04月10日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012041003283, USMI热插拔特性
  6.日    期   : 2012年05月04日
    作    者   : l65478
    修改内容   : 问题单号:DTS2012031202846, PIN码解锁后先上报卡无效又上报卡有效
  7.日    期   : 2012年06月14日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012061209698, 添加可维可测信息
  8.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  9.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  10.日    期   : 2013年4月2日
     作    者   : z00161729
     修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  11.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
  12.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
 13.日    期   : 2013年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目:NV读取到全局变量中以及删除g_ucMsccMsccNeedPin1
                 全局变量使用SDC的sim卡状态-SIM卡状态不再查询,直接从SDC中获取
                 保留使用API向MSCC查询CS/PS卡无效的状态逻辑,后续统一维护到SDC中

 14.日    期   : 2014年2月27日
    作    者   : z00234330
    修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用

*****************************************************************************/
VOS_UINT8 MMA_GetUsimStatus(
    VOS_UINT32                          ulUsimStaChg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-30, begin */
    VOS_BOOL                            bCsSimStaus;
    VOS_BOOL                            bPsSimStaus;
    VOS_UINT8                           ucMeLockStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSdcSimStatus;
    VOS_UINT8                           ucCurPhMode;

    /* 快速开机时返回ROMSIM */
    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        return TAF_PH_USIM_ROMSIM;
    }

    enSdcSimStatus = TAF_SDC_GetUsimStatus();
    ucMeLockStatus = MMA_GetMeLockStatus();

    /* 如果当前需要校验PIN码或卡处于锁定状态或卡不可用，则卡状态为无效状态 */
    if ((VOS_TRUE                    == g_ucUsimHotInFlag)
     || (TAF_SDC_USIM_STATUS_SIM_PIN == enSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == enSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID == enSdcSimStatus)
     || (MMA_SIM_IS_LOCK             == ucMeLockStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSdcSimStatus))
    {
        return TAF_PH_USIM_STATUS_UNAVAIL;
    }

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == enSdcSimStatus)
    {
        return TAF_PH_USIM_NON;
    }

    ucCurPhMode = TAF_SDC_GetCurPhoneMode();

    /* 关机状态或开机过程中或卡状态发生变化使用SDC中的卡状态上报 */
    if ((TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
     || (TAF_PH_MODE_FULL       != ucCurPhMode)
     || (VOS_TRUE               == ulUsimStaChg))
    {
        return enSdcSimStatus;
    }

    /* 通过SDC 接口获取CS/PS的卡是否无效信息, */
    bCsSimStaus = TAF_SDC_GetSimCsRegStatus();
    bPsSimStaus = TAF_SDC_GetSimPsRegStatus();
    if ((VOS_FALSE == bCsSimStaus)
     && (VOS_FALSE == bPsSimStaus))
    {
        return TAF_PH_USIM_STATUS_CSPS_UNVAIL;
    }

    if (VOS_FALSE == bCsSimStaus)
    {
        return TAF_PH_USIM_STATUS_CS_UNVAIL;
    }

    if (VOS_FALSE == bPsSimStaus)
    {
        return TAF_PH_USIM_STATUS_PS_UNVAIL;
    }

    return TAF_PH_USIM_STATUS_AVAIL;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : MN_PH_ConvertSysSubModeToAtFormat_FDD
 功能描述  : 将MSCC上报的系统子模式转换为AT格式的
 输入参数  : enSrcSysSubMode:需要转换的系统子模式
 输出参数  : penDestSysSubMode:转换后的系统子模式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat_FDD(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    switch (enSrcSysSubMode)
    {
        case TAF_SYS_SUBMODE_NONE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_NONE_RAT;
            break;

        case TAF_SYS_SUBMODE_GSM:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GSM_RAT;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GPRS_RAT;
            break;

        case TAF_SYS_SUBMODE_EDGE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EDGE_RAT;
            break;

        case TAF_SYS_SUBMODE_WCDMA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_WCDMA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSDPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSUPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_MIMO:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_LTE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_LTE_RAT;
            break;

        case TAF_SYS_SUBMODE_CDMA_1X:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_CDMA20001X_RAT;
            break;

        case TAF_SYS_SUBMODE_EVDO_REL_0:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDOREL0_RAT;
            break;

        case TAF_SYS_SUBMODE_EVDO_REL_A:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT;
            break;

        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_0:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDOREL0_RAT;
            break;

        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_A:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELA_RAT;
            break;


        case TAF_SYS_SUBMODE_EHRPD:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EHRPD_RAT;
            break;

        default:

            /* 异常打印 */
            MN_INFO_LOG("MN_PH_ConvertSysSubModeToAtFormat: invalid sub sys mode!");
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_BUTT_RAT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_PH_ConvertSysSubModeToAtFormat_TDD
 功能描述  : 将MSCC上报的系统子模式转换为AT格式的
 输入参数  : enSrcSysSubMode:需要转换的系统子模式
 输出参数  : penDestSysSubMode:转换后的系统子模式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat_TDD(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    switch (enSrcSysSubMode)
    {
        case TAF_SYS_SUBMODE_NONE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_NONE_RAT;
            break;

        case TAF_SYS_SUBMODE_GSM:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GSM_RAT;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GPRS_RAT;
            break;

        case TAF_SYS_SUBMODE_EDGE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EDGE_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSDPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSUPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSPA_RAT;
            break;

        case TAF_SYS_SUBMODE_TD_SCDMA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TDCDMA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_MIMO:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_LTE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_LTE_RAT;
            break;


        case TAF_SYS_SUBMODE_CDMA_1X:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_CDMA20001X_RAT;
            break;

        case TAF_SYS_SUBMODE_EVDO_REL_0:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDOREL0_RAT;
            break;

        case TAF_SYS_SUBMODE_EVDO_REL_A:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT;
            break;

        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_0:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDOREL0_RAT;
            break;

        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_A:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELA_RAT;
            break;

        case TAF_SYS_SUBMODE_EHRPD:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EHRPD_RAT;
            break;

        default:

            /* 异常打印 */
            MN_INFO_LOG("MN_PH_ConvertSysSubModeToAtFormat: invalid sub sys mode!");
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_BUTT_RAT;
            break;
    }

   return;
}




/*****************************************************************************
 函 数 名  : MN_PH_ConvertSysSubModeToAtFormat
 功能描述  : 将MSCC上报的系统子模式转换为AT格式的
 输入参数  : enSrcSysSubMode:需要转换的系统子模式
 输出参数  : penDestSysSubMode:转换后的系统子模式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年05月10日
    作    者   : w00166186
    修改内容   : DTS2012050800513:WAS 上报系统子模式为44时，SYSINFO显示错误

  3.日    期   : 2012年06月01日
    作    者   : z40661
    修改内容  : DTS2012053006110:显示DC-HSPA+
  4.日    期   : 2012年08月09日
    作    者   : s00217060
    修改内容  : for V7R1C50_GUTL_PhaseII修改
*****************************************************************************/
VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        MN_PH_ConvertSysSubModeToAtFormat_FDD(enSrcSysSubMode, penDestSysSubMode);
    }
    else
    {
        MN_PH_ConvertSysSubModeToAtFormat_TDD(enSrcSysSubMode, penDestSysSubMode);
    }

   return;
}


/*****************************************************************************
 函 数 名  : MN_PH_GetSysInfoRoamStatus
 功能描述  : 获取SYSINFOEX中是否漫游特性
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整

  3.日    期   : 2014年2月27日
    作    者   : z00234330
    修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
  4.日    期   : 2014年04月15日
    作    者   : s00217060
    修改内容   : DTS2014041005456:sysinfoex显示漫游状态错误
  5.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
*****************************************************************************/
VOS_VOID  MN_PH_GetSysInfoRoamStatus(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
)
{
    TAF_PH_ROAM_STA                     enRoamSta;

    enRoamSta = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());

    /* 成功注册到HOME PLMN时显示非漫游，成功注册到漫游网络时显示漫游，限制服务时显示未知 */
    if (TAF_PH_NO_ROAM == enRoamSta)
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_NONE_ROMAING;
    }
    else if (TAF_PH_ROAMING == enRoamSta)
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROMAING;
    }
    else
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROAM_UNKNOW;
    }
}


/*****************************************************************************
 函 数 名  : MN_PH_GetSysInfoSrvStatus
 功能描述  : 获取当前Srv Status相关值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,修改ulTimMaxFlg的取值，使用VOS_TRUE,VOS_FALSE
  3.日    期   : 2012年04月29日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012042901072,L模下，目前不需要判断信号强度

  4.日    期   : 2012年5月26日
    作    者   : z40661
    修改内容   : DTS2012050803419,判断信号强度过小时,需要在信号强度发生变化时,主动上报一次服务状态

  5.日    期   : 2012年6月5日
    作    者   : z40661
    修改内容   : 与终端产品线达成一致，删除sysinfo此处信号门限的判断
  6.日    期   : 2013年4月4日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  7.日    期   : 2013年09月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  8.日    期   : 2013年11月7日
    作    者   : w00167002
    修改内容   : DTS2013110510774:在手机形态，无卡开机，任意小区搜索失败超过10次，
                 后任意小区搜索成功，AT^SYSINFOEX查询当前的服务状态为不上报深睡4，
                 上层APP无法确认当前是否可以提供有限制服务，修改为:如果当前是ADROID
                 后台，如果驻留了,则上报1，无服务则上报0，处在深睡状态的无服务则上报4.
  9.日    期   : 2014年2月27日
    作    者   : z00234330
    修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
               卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
               at^cpin命令查询的会不正确。

*****************************************************************************/
VOS_VOID  MN_PH_GetSysInfoSrvStatus(
    TAF_PH_SYSINFO_STRU                *pstSysInfo,
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    /* SimStatus作为入参传递，用于区分CL模式和GU两种场景 */
    /* CL模式使用Csim卡状态进行判断，GU使用USIM卡状态进行判断 */

    if ( (VOS_TRUE           == gstMmaValue.pg_StatusContext->ulTimMaxFlg)
      && (SYSTEM_APP_ANDROID != g_usMmaAppConfigSupportType) )
    {

        pstSysInfo->ucSrvStatus = TAF_PH_INFO_DEEP_SLEEP;
        pstSysInfo->ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    if ((TAF_SDC_USIM_STATUS_NO_PRESENT == enSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID == enSimStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSimStatus))
    {
        pstSysInfo->ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
    /* 上电不开机时查询sysinfo或sysinfoex,初始化值为BUTT,AT手册中没有这个值,做一下转换 */
    if (TAF_SDC_SERVICE_DOMAIN_BUTT == pstSysInfo->ucSrvDomain)
    {
        pstSysInfo->ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    if (TAF_SDC_REPORT_SRVSTA_BUTT == pstSysInfo->ucSrvStatus)
    {
        pstSysInfo->ucSrvStatus = TAF_PH_INFO_NO_SERV;
    }
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */
}

/*****************************************************************************
 函 数 名  : MN_PH_GetSysInfoSysModeEx
 功能描述  : 获取当前系统模式和子模式
 输入参数  : none
 输出参数  : pstSysInfo:填充系统模式和子模式
 返 回 值  : none
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月7日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

  2.日    期   : 2011年12月1日
    作    者   : w00176964
    修改内容   : V7R1 PHASEIV 调整
  3.日    期   : 2012年05月03日
    作    者   : w00166186
    修改内容   : DTS2012042603797,软关机状态下，SYSINFOEX上报系统子模式为无效值
                 导致后台显示错误
  4.日    期   : 2012年8月8日
    作    者   : s00217060
    修改内容   : for V7R1C50_GUTL_PhaseII,TD-SCDMA模式下，SYSINFOEX上报系统模式为TD-SCDMA
  5.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
*****************************************************************************/
VOS_VOID  MN_PH_GetSysInfoSysModeEx(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
)
{
    TAF_SYS_SUBMODE_ENUM_UINT8          enSubMode;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */

    /* 有注册状态和服务状态的延迟上报，要取AppNetworkInfo的信息 */
    switch(TAF_SDC_GetAppSysMode())
    {
        case TAF_SDC_SYS_MODE_CDMA_1X:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_CDMA_RAT;

            enSubMode = TAF_SDC_GetAppSysSubMode();
            break;

        case TAF_SDC_SYS_MODE_EVDO:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_EVDO_RAT;

            enSubMode = TAF_SDC_GetAppSysSubMode();

            break;

        case TAF_SDC_SYS_MODE_HYBRID:
            pstSysInfo->ucSysMode    = MN_PH_SYS_MODE_EX_HYBRID_RAT;

            enSubMode = TAF_SDC_GetAppSysSubMode();
            break;

        case TAF_SDC_SYS_MODE_GSM:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_GSM_RAT;
            enSubMode = TAF_SDC_GetAppSysSubMode();
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_WCDMA_RAT;

                /*W下，^SYSINFO查询的系统子模式是数传态下系统子模式 */
                enSubMode = Sta_GetSysSubMode_W(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                            gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            else
            {
                pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_TDCDMA_RAT;

                /*TD下，^SYSINFO查询的系统子模式是数传态下系统子模式 */
                enSubMode = Sta_GetSysSubMode_Td(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                            gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            break;

        case TAF_SDC_SYS_MODE_LTE:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_LTE_RAT;
            enSubMode  = TAF_SDC_GetAppSysSubMode();
            break;

        case TAF_SDC_SYS_MODE_SVLTE:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_SVLTE_RAT;
            enSubMode  = TAF_SDC_GetAppSysSubMode();
            break;

        default:
            pstSysInfo->ucSysMode    = MN_PH_SYS_MODE_EX_NONE_RAT;

            enSubMode                = TAF_SYS_SUBMODE_NONE;
            break;
    }
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    /* 将系统子模式进行转换 */
    MN_PH_ConvertSysSubModeToAtFormat(enSubMode, &(pstSysInfo->ucSysSubMode));


    return;
}

/*****************************************************************************
 函 数 名  : MMA_GetSysInfoSysMode
 功能描述  : Get Sysinfo Mode Info
 输入参数  : TAF_PH_SYSINFO_STRU                 *pstSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MMA_GetSysInfoSysMode(
    TAF_PH_SYSINFO_STRU                *pstSysInfo
)
{
    switch (TAF_SDC_GetAppSysMode())
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstSysInfo->ucSysMode    = TAF_PH_INFO_GSM_RAT;
            pstSysInfo->ucSysSubMode = TAF_SDC_GetAppSysSubMode();
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                pstSysInfo->ucSysMode = TAF_PH_INFO_WCDMA_RAT;

                /* W下，^SYSINFO查询的系统子模式是数传态下系统子模式 */
                pstSysInfo->ucSysSubMode = Sta_GetSysSubMode_W(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                               gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            else
            {
                pstSysInfo->ucSysMode = TAF_PH_INFO_TD_SCDMA_RAT;

                /* TD下，^SYSINFO查询的系统子模式是数传态下系统子模式 */
                pstSysInfo->ucSysSubMode = Sta_GetSysSubMode_Td(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                                gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            break;

#if(FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
            /*  SYSINFO是GU使用的命令，在L下时，按W显示 */
            pstSysInfo->ucSysMode    = TAF_PH_INFO_WCDMA_RAT;
            pstSysInfo->ucSysSubMode = TAF_SYS_SUBMODE_WCDMA;

            break;
#endif

         default:
            pstSysInfo->ucSysMode    = TAF_PH_INFO_NONE_RAT;
            pstSysInfo->ucSysSubMode = TAF_SYS_SUBMODE_NONE;
            break;
    }
}

/*****************************************************************************
 函 数 名  : MN_PH_AppRoamStatusRpt
 功能描述  :
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月17日
    作    者   : lijun 00171473
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:删除FEATURE_E5宏
  3.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,修改ulTimMaxFlg的取值，使用VOS_TRUE,VOS_FALSE
  4.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID MN_PH_AppRoamStatusRpt( VOS_VOID )
{
    TAF_PH_SYSINFO_STRU                 sys_info;
    VOS_INT32                           lInvalidRssi;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    VOS_INT32                           lRssiValue;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    sys_info.ucSrvStatus = TAF_SDC_GetServiceStatus();
    sys_info.ucSrvDomain = TAF_SDC_GetServiceDomain();
    enSysMode            = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        lInvalidRssi = MMA_UTRA_RSSI_INVALID;
    }
    else
    {
        lInvalidRssi = MMA_UTRA_RSCP_INVALID;
    }

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        lRssiValue = gstMmaValue.stCerssiValue.aRssi[0].u.stGCellSignInfo.sRssiValue;
    }
    else
    {
        lRssiValue = gstMmaValue.stCerssiValue.aRssi[0].u.stWCellSignInfo.sRscpValue;
    }

    if(lInvalidRssi >= lRssiValue)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        sys_info.ucSrvStatus = TAF_REPORT_SRVSTA_NO_SERVICE;
        sys_info.ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }


    if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg )
    {
        sys_info.ucSrvStatus = TAF_PH_INFO_DEEP_SLEEP;
        sys_info.ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    if ( TAF_PH_INFO_NOMRL_SERV != sys_info.ucSrvStatus )
    {
        /* 服务无效 不做漫游判断 */
        MN_INFO_LOG("MN_PH_AppRoamStatusRpt: service is not normal services");
        return;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if ( TAF_PH_ROAMING == MMA_IsRoam(TAF_SDC_GetRoamFlag()) )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        sys_info.ucRoamStatus = TAF_PH_INFO_ROMAING;
    }
    else
    {
        sys_info.ucRoamStatus = TAF_PH_INFO_NONE_ROMAING;
    }

    if ( sys_info.ucRoamStatus != g_ucMnPhRoamStatus )
    {
        g_ucMnPhRoamStatus = sys_info.ucRoamStatus;
        MN_PH_RoamingRpt( g_ucMnPhRoamStatus );
    }

}

/*****************************************************************************
 函 数 名  : MN_PH_GetRssilvForCsqlvlExt
 功能描述  : 获取CSQLVLEXT查询命令的信号格数
 输入参数  : VOS_UINT8   ucRssiValue    信号强度：3G下为RSCP，2G下是RSSI
              VOS_UINT8      ucCurRaForSysInfo 接入技术
 输出参数  : MN_PH_CSQLVLEXT_RSSILV_ENUM_UINT8 *pucRssil 信号格数
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月14日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_PH_GetRssilvForCsqlvlExt (
    VOS_INT32                           lRssiValue,
    VOS_UINT8                           ucCurRaForSysInfo,
    MN_PH_CSQLVLEXT_RSSILV_ENUM_UINT8  *pucRssilv
)
{
    VOS_UINT32                          ulAbsRssiValue;
    VOS_UINT32                          aulGsmRssi[MN_PH_CSQLVLEXT_RSSILV_BUTT] = {105, 90, 84, 82, 80, 76};
    VOS_UINT32                          aulWcdmaRscp[MN_PH_CSQLVLEXT_RSSILV_BUTT] = {105, 102, 96, 94, 92, 88};
    VOS_UINT32                         *pulRssiConvertRule;

    /* 取绝对值 */
    ulAbsRssiValue = (VOS_UINT32)(-lRssiValue);

    if (TAF_PH_RA_GSM == ucCurRaForSysInfo)
    {
        pulRssiConvertRule = aulGsmRssi;
    }
    else
    {
        pulRssiConvertRule = aulWcdmaRscp;
    }

    /* 根据SRS中描述的信号强度对应关系获取到信号强度格数 */
    if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_5])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_99; /* 5格 */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_4])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_80; /* 4格 */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_3])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_60; /* 3格 */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_2])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_40; /* 2格 */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_1])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_20; /* 1格 */
    }
    else
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_0;  /* 0格 */
    }

    return;
}


/*****************************************************************************
FunctionName: MMA_GetPhIccType
Description : Get the ICC Type
Input       : ClientId          Identifier of Client
              OpId              Operation ID
Output      :
Return      :
  1.日    期   : 2006年12月7日
    作    者   : H59254
    修改内容   : 问题单号：A32D07836
  2.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  4.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/

VOS_VOID MMA_GetPhIccType(VOS_UINT16 ClientId,VOS_UINT8 OpId)

{
    TAF_PH_UICC_TYPE stIcc_Type;
    VOS_UINT8 ucSimType;
    VOS_UINT8 usPinType;


    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
    if(TAF_PH_USIM_ROMSIM == MMA_GetUsimStatus(VOS_FALSE))
    {
        stIcc_Type.MmaIccType = TAF_PH_ICC_UNKNOW;
    }
    else
    {
        (VOS_VOID)MMA_PhoneGetUsimType(&ucSimType);

        if(MMA_USIM_TYPE_USIM == ucSimType)
        {
            stIcc_Type.MmaIccType = TAF_PH_ICC_USIM;
        }
        else if(MMA_USIM_TYPE_SIM == ucSimType)
        {
            stIcc_Type.MmaIccType = TAF_PH_ICC_SIM;
        }
        else
        {
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

    usPinType = USIMM_PIN;

    (VOS_VOID)NAS_USIMMAPI_GetPinStatus(&usPinType, &stIcc_Type.MmaIccPinStatus, &stIcc_Type.MmaIccPinVerifyStatus, &stIcc_Type.ucRemainTimes);

    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_ICC_TYPE_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)(&stIcc_Type));
    return;
}


/*****************************************************************************
FunctionName: MMA_GetPhIccType
Description : Get the ICC Type
Input       : ClientId          Identifier of Client
              OpId              Operation ID
Output      :
Return      :
  1.日    期   : 2006年12月7日
    作    者   : H59254
    修改内容   : 问题单号：A32D07836
  2.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  3.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_VOID MMA_GetPhIccStatus(VOS_UINT16 ClientId,VOS_UINT8 OpId)
{
    TAF_USIM_STATUS                     ICC_STATE;
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
    ICC_STATE                           = MMA_GetUsimStatus(VOS_FALSE);
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_ICC_STATUS_PARA,TAF_ERR_NO_ERROR, &ICC_STATE);
    return;
}

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtIccStatusInd
 功能描述  : 向AT上报卡状态指示(SIMST)
 输入参数  : ucSimStatus---SIM卡状态
             ucSimLockStatus--SIM卡锁卡状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年7月18日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID TAF_MMA_SndAtIccStatusInd(
    VOS_UINT8                           ucSimStatus,
    VOS_UINT8                           ucSimLockStatus
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("TAF_MMA_SndAtIccStatusInd:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* 初始化电话上报事件 */
    MMA_InitEventInfoOP(pstPhoneEvent);

    /* 填写事件类型为卡状态信息指示:TAF_PH_EVT_USIM_INFO_IND*/
    pstPhoneEvent->PhoneEvent             = TAF_PH_EVT_USIM_INFO_IND;

    /* 填写事件客户端类型为广播事件 */
    pstPhoneEvent->ClientId               = MMA_CLIENTID_BROADCAST;
    pstPhoneEvent->OpId                   = MMA_OP_ID_INTERNAL;

    /* 填写上报的卡状态和锁定状态 */
    pstPhoneEvent->SimStatus              = ucSimStatus;
    pstPhoneEvent->MeLockStatus           = ucSimLockStatus;

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
    return;
}

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

/*****************************************************************************
 函 数 名  : MMA_QueryProc
 功能描述  : 负责将查询类功能的分发，主要是AT新增功能
 输入参数  : VOS_UINT16 ClientId,
             VOS_UINT8        OpId,
             VOS_UINT16        usIeMask,信息标签的掩码
             VOS_UINT8         *pMsg,   接受到的信息包
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月2日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2010年8月4日
    作    者   : 傅映君/f62575
    修改内容   : AT装备归一化
  3.日    期   : 2011年10月17日
    作    者   : f62575
    修改内容   : AT Project
  4.日    期   : 2012年02月3日
    作    者   : f62575
    修改内容   : B050 SIMLOCK命令的硬加密改制功能: 增加SIMLOCK锁卡状态查询功能
  5.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : DTS2013010809507网络名称上报错误
  6.日    期   : 2013年4月16日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  7.日    期   : 2013年6月11日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:新增^usersrvstate查询消息的处理
  8.日    期   : 2014年04月15日
    作    者   : s00217060
    修改内容   : DTS2014041005456:删除cellroam查询的处理和TAF_PH_ROAM_STATUS_PARA查询的处理
  9.日    期   : 2015年2月27日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_VOID MMA_QueryProc(VOS_UINT16 ClientId,
                       VOS_UINT8        OpId,
                       VOS_UINT8     *pMsg)
{
    TAF_PARA_TYPE ParaQuery;

    ParaQuery = (TAF_PARA_TYPE)(*pMsg);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
    if(  (ParaQuery > (TAF_PH_PRODUCT_NAME_PARA + 1))
       ||(ParaQuery < TAF_PH_MS_CLASS_PARA)
      )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */
    {
          MMA_WARNINGLOG("MMA_QueryProc():WARNING:Receive Error ParaQuery");
          MMA_ReportParaQueryError(ClientId, OpId,
                                   TAF_ERR_CAPABILITY_ERROR,
                                   ParaQuery);
          return;
    }

    /*根据查询类型值，分发调用函数*/
    switch ( ParaQuery)
    {

        /*获取IMSI*/
        case TAF_PH_IMSI_ID_PARA:
            MMA_PhoneGetImsi(ClientId, OpId);
            break;



        /*==>A32D06630*/
        case TAF_PH_CELL_RSCP_VALUE_PARA:   /*Get cell RCSP & Cell Info*/
            MMA_GetPhCellRscp(ClientId, OpId);
            break;

        case TAF_PH_UE_RFPOWER_FREQ_PARA:   /*Get UE's RF power and uplink frequency*/
            MMA_GetPhUeRfPowerFreq(ClientId, OpId);
            break;
        /*<==A32D06630*/





        /* 删除MMA_PhoneGetRoamSta */

        /*获取域状态*/
        case TAF_PH_DOMAIN_PARA :
            MMA_PhoneGetDomain(ClientId,OpId);
            break;

        /* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
        /* case TAF_PH_WHOLE_DATA */
        /* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */

        /*获取手机产品名称*/
        case TAF_PH_PRODUCT_NAME_PARA:
            MMA_PhoneGetProductName(ClientId, OpId);
            break;

        /* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
        /* case TAF_PH_IDENTIFICATION_INFO_PARA */
        /* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */



        case TAF_PH_ICC_ID:
            MMA_PhoneGetIccId(ClientId, OpId);
            break;


        case TAF_PH_ICC_TYPE_PARA:  /*Get the UICC type*/
            MMA_GetPhIccType(ClientId, OpId);
            break;
        case TAF_PH_ICC_STATUS_PARA:    /*Get the UICC state*/
            MMA_GetPhIccStatus(ClientId, OpId);
            break;


        case TAF_PH_SIMLOCK_VALUE_PARA:
            TAF_MMA_RcvSimLockQry(ClientId, OpId);
            break;







        default:
            MMA_WARNINGLOG("MMA_QueryProc():WARNING:No funcation fit the case");
            break;
    }
    return;
}



/*****************************************************************************
 函 数 名  : MMA_PhoneGetProductName
 功能描述  : 获取手机产品名称
 输入参数  : VOS_UINT16     ClientId
             VOS_UINT8            OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月22日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
*****************************************************************************/
VOS_VOID MMA_PhoneGetProductName( VOS_UINT16     ClientId, VOS_UINT8    OpId )
{
    VOS_UINT8     ucParalen;
    VOS_VOID      *pPara;

    /*发送数据准备*/
    /*获取域状态信息长度*/
    ucParalen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)(gstMmaValue.stMeInfo.ProductName.aucProductName)) + 1;
    if ( ucParalen > TAF_PH_PRODUCT_NAME_LEN)
    {
        gstMmaValue.stMeInfo.ProductName.aucProductName[TAF_PH_PRODUCT_NAME_LEN] = '\0';
        /*增加一个warning打印*/
        MMA_WARNINGLOG("MMA_PhoneGetProductName():WARNING:Length of Product is too Long!");
    }

    pPara = (VOS_VOID*)gstMmaValue.stMeInfo.ProductName.aucProductName;
    /*使用数据上报函数将数据传至TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_PRODUCT_NAME_PARA,TAF_ERR_NO_ERROR, pPara);

    return;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
/*MMA_PhoneGetIdentificationInfo()
  MMA_PhoneGetRevisionIdentification()
  MMA_PhoneGetWholeInfo()
  MMA_FillWholeInfo()*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */


/*****************************************************************************
 函 数 名  : MMA_IsRoam
 功能描述  : 当前漫游状态判断
 输入参数  : STATUS_CONTEXT_STRU *pStatus Status中全局结构,存储了当前的状态
 输出参数  : 无
 返 回 值  : TAF_PH_ROAM_STA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月5日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2008年8月18日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05086，修改CurPlmnId.Mnc,用于CGREG的状态上报
  3.日    期   : 2011年05月06日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2011050300290,UE驻留在EPLMN上，非HPLMN，NAS认为处于漫游状态，
                 查询注册状态为漫游
  4.日    期   : 2011年11月21日
    作    者   : o00132663
    修改内容   : 问题单号:DTS2011111900352,AT融合项目
  5.日    期   : 2012年8月22日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题:比较三位Mnc
  6.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  7.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  8.日    期   : 2014年04月15日
    作    者   : s00217060
    修改内容   : DTS2014041005456:sysinfoex显示漫游状态错误
  9.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 服务状态优化Phase II
*****************************************************************************/
TAF_PH_ROAM_STA MMA_IsRoam(
    VOS_UINT8                           ucRoamFlg
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;

    enCsRegStatus  = TAF_SDC_GetAppCsRegStatus();
    enPsRegStatus  = TAF_SDC_GetAppPsRegStatus();

    /* 至少一个域注册成功并且非漫游时 */
    if ( (VOS_FALSE                            == ucRoamFlg)
      && ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enCsRegStatus)
       || (TAF_SDC_REG_REGISTERED_HOME_NETWORK == enPsRegStatus)) )
    {
        return TAF_PH_NO_ROAM;
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
    /* 至少一个域注册成功并且漫游时 */
    if ( (VOS_TRUE                     == ucRoamFlg)
      && ((TAF_SDC_REG_REGISTERED_ROAM == enCsRegStatus)
       || (TAF_SDC_REG_REGISTERED_ROAM == enPsRegStatus)) )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        return TAF_PH_ROAMING;
    }
    else
    {
        return TAF_PH_ROAM_UNKNOW;
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

}

/*****************************************************************************
 函 数 名  : MMA_ReportParaQueryError
 功能描述  : 查询参数出错上报函数
 输入参数  : VOS_UINT16       ClientId
             VOS_UINT8              OpId
             VOS_UINT8           ucErrorType   错误类型
             TAF_PARA_TYPE ParaType      查询参数的类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月18日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 增加判断回调函数指针是否为空,问题单号:A32D02143
  3.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  4.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
*****************************************************************************/
VOS_VOID MMA_ReportParaQueryError( VOS_UINT16       ClientId,
                                   VOS_UINT8              OpId,
                                   VOS_UINT16           usErrorCode,
                                   TAF_PARA_TYPE ParaType)
{
    if (TAF_ERR_NO_ERROR != usErrorCode)
    {
        MMA_WARNINGLOG1("MMA_ReportParaQueryError():WARNING:Para query falied, Error Code = %d", usErrorCode);

        /*调用APP参数查询失败上报函数*/
        MN_QRYPARA_SendMsg(ClientId, OpId, ParaType,usErrorCode, TAF_NULL_PTR);

    }
    return;
}

/*****************************************************************************
 函 数 名  : MMA_ParaQueryReport
 功能描述  : 参数查询结果上报
 输入参数  : VOS_UINT16                  ClientId
             VOS_UINT8                         OpId
             TAF_PARA_TYPE Query      Type      要上报的查询参数
             VOS_UINT8                     *pucPara   要传送的数据缓冲区的启示地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月30日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 增加判断回调函数指针是否为空,问题单号:A32D02143
  3.日    期   : 2007年9月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D12931,查询API接口增加错误码上报
  4.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
*****************************************************************************/
/*lint -e429*/
VOS_VOID MMA_ParaQueryReport(VOS_UINT16            ClientId,
                              VOS_UINT8                   OpId,
                              TAF_PARA_TYPE      QueryType,
                              VOS_UINT16         usErrorCode,
                              VOS_VOID                 *pucPara)
{
    /*调用APP查询参数上报函数*/
    MN_QRYPARA_SendMsg(ClientId, OpId, QueryType,usErrorCode, pucPara);

    return;
}
/*lint +e429*/

/**********************************************************
 Function:     MMA_TiAlloc
 Description:  STATUS ，分配子
               模块所需要的TI值，并将ClientId、Id与TI的对
               应关系记录在TI表中
 Calls:
 Data Accessed:
 Data Updated:
 Input:        ucModule－子模块类型：TAF_STATUS,
               ClientId－APP、AT标识
               Id－ APP、AT操作标识
 Output:       pucTi－分配的TI值
 Return:       MMA_SUCCESS－成功
               MMA_FAILURE－失败
 Others:

  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，使用宏替代了原有的Ti
  2.日    期   : 2008年11月10日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D06622，添加SYSCFG状态下的Ti分配
  3.日    期   : 2012年11月24日
    作    者   : z60575
    修改内容   : DTS2012112003432，飞行模式问题修改
**********************************************************/
VOS_UINT32  MMA_TiAlloc(VOS_UINT8        ucModule,
                        VOS_UINT16    ClientId,
                        VOS_UINT8           Id,
                        TAF_PHONE_EVENT  PhoneEvt,
                        VOS_UINT8       *pucTi)
{

    if (VOS_NULL_PTR == pucTi)
    {
        MMA_WARNINGLOG("MMA_TiAlloc():WARNING:pucTi is NULL PTR!");
        return MMA_FAILURE;
    }
    switch (ucModule)
    {
        case TAF_MMA:
            if ( TAF_PH_EVT_OP_PIN_CNF == PhoneEvt )
            {
                if ( MMA_TI_USED == gastMmaTiTab[MMA_PH_PIN_TI].ucUsed)
                {
                    return MMA_FAILURE;
                }
                gastMmaTiTab[MMA_PH_PIN_TI].ClientId          = ClientId;
                gastMmaTiTab[MMA_PH_PIN_TI].Id                = Id;
                gastMmaTiTab[MMA_PH_PIN_TI].PhoneEvent        = PhoneEvt;
                gastMmaTiTab[MMA_PH_PIN_TI].ucUsed            = MMA_TI_USED;
                return TAF_SUCCESS;
            }
            switch (gstMmaValue.pg_StatusContext->ulFsmState)
            {
                case STA_FSM_NULL:
                case STA_FSM_ENABLE:
                case STA_FSM_RESTART:
                case STA_FSM_STOP :
                    /*TI分配成功*/
                    gastMmaTiTab[0].ClientId          = ClientId;
                    gastMmaTiTab[0].Id                = Id;
                    gastMmaTiTab[0].PhoneEvent        = PhoneEvt;
                    gastMmaTiTab[0].ucUsed            = MMA_TI_USED;
                    *pucTi = 0;
                    return MMA_SUCCESS;

                case STA_FSM_PLMN_LIST:
                case STA_FSM_PLMN_RESEL:
                case STA_FSM_PLMN_SEL:
                    /*TI分配成功*/
                    gastMmaTiTab[1].ClientId          = ClientId;
                    gastMmaTiTab[1].Id                = Id;
                    gastMmaTiTab[1].PhoneEvent        = PhoneEvt;
                    gastMmaTiTab[1].ucUsed            = MMA_TI_USED;
                    *pucTi = 1;
                    return MMA_SUCCESS;
                default:
                    MMA_WARNINGLOG("MMA_TiAlloc():WARNING:Error in Status FSM!");
                    return MMA_FAILURE;
            }
       default:
            /*增加打印信息*/
            MMA_WARNINGLOG("MMA_TiAlloc():WARNING:Error input Module Name!");
            return MMA_FAILURE;
    }
}




/**********************************************************
 Function:     MMA_GetIdByTi
 Description:  从TI记录表中用TI获取关联的ClientId和Id
 Calls:
 Data Accessed:
 Data Updated:
 Input:        ucModule－子模块类型：TAF_STATUS,
               Ti－TI值
 Output:       pClientId－APP、AT标识
               pId－ APP、AT操作标识
 Return:       MMA_SUCCESS－成功
               MMA_FAILURE－失败
 Others:

  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，使用宏定义替换原有的常数
**********************************************************/
VOS_UINT32  MMA_GetIdByTi (VOS_UINT8         ucModule,
                           VOS_UINT8         ucTi,
                           VOS_UINT16    *pClientId,
                           VOS_UINT8           *pId,
                           TAF_PHONE_EVENT  *PhoneEvt)
{
    /*参数判别有效性*/
    if ( (VOS_NULL_PTR == pClientId) || (VOS_NULL_PTR == pId) )
    {
        MMA_WARNINGLOG("MMA_GetIdByTi():WARNING:pClientId & pId are NULL PTR!!");
        return MMA_FAILURE;
    }
    switch (ucModule)
    {
        case TAF_MMA:
            /*Ti=2专门用于PIN操作*/
            if ( MMA_PH_PIN_TI == ucTi )
            {
                *pClientId = gastMmaTiTab[MMA_PH_PIN_TI].ClientId;
                *pId       = gastMmaTiTab[MMA_PH_PIN_TI].Id;
                *PhoneEvt  = gastMmaTiTab[MMA_PH_PIN_TI].PhoneEvent;
                /*清除使用标志*/
                /*gastMmaTiTab[MMA_PH_PIN_TI].ucUsed   = 0;
                gastMmaTiTab[MMA_PH_PIN_TI].ClientId = 0;
                gastMmaTiTab[MMA_PH_PIN_TI].Id       = 0;*/
                gastMmaTiTab[MMA_PH_PIN_TI].ucUsed   = MMA_TI_UNUSED;
                gastMmaTiTab[MMA_PH_PIN_TI].ClientId = MMA_CLIENTID_NONE;
                gastMmaTiTab[MMA_PH_PIN_TI].Id       = MMA_OP_ID_INTERNAL;
                return MMA_SUCCESS;
            }
            if (ucTi > TAF_MAX_STATUS_TI)
            {   /*TI有效范围是0-1*/
                MMA_WARNINGLOG("MMA_GetIdByTi():WARNNING:TI is out of MAX");
                return MMA_FAILURE;
            }
            /* 不需要判断g_TafPhoneTiTab[ucTi].ucUsed,因为分配时没有使用*/
            *pClientId = gastMmaTiTab[ucTi].ClientId;
            *pId       = gastMmaTiTab[ucTi].Id;
            *PhoneEvt  = gastMmaTiTab[ucTi].PhoneEvent;
            /*清除使用标志*/
            /*gastMmaTiTab[ucTi].ucUsed   = 0;
            gastMmaTiTab[ucTi].ClientId = 0;
            gastMmaTiTab[ucTi].Id       = 0;*/
            gastMmaTiTab[ucTi].ucUsed   = MMA_TI_UNUSED;
            gastMmaTiTab[ucTi].ClientId = MMA_CLIENTID_NONE;
            gastMmaTiTab[ucTi].Id       = MMA_OP_ID_INTERNAL;
            return MMA_SUCCESS;
        default:
            /*需增加打印信息*/
            MMA_WARNINGLOG("MMA_GetIdByTi():WARNING:Error input Module Name!");
            return MMA_FAILURE;
    }
}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* MMA_InitUsimInfo删除 */
/* MMA_UpdateBandNvRefForbBand放到TafMmaProcNvim文件中 */
/* MMA_UpdateForbBandStatusToNV放到TafMmaProcNvim文件中 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* TAF_MMA_InitOrigMeInfo移动位置 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */



/*****************************************************************************
 函 数 名  : MN_MMA_SetDefaultRatPrioList
 功能描述  : 按默认优先级保存gsm/wcdma/LTE优先级
 输入参数  : 无
 输出参数  : pstRatPrioList - 接入优先级信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，根据平台接入技术能力设置默认值
  3.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID MN_MMA_SetDefaultRatPrioList(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT8                           i;
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulGsmForbiddenFlg;
#endif

    i = 0;

#if (FEATURE_ON == FEATURE_LTE)
    /* 平台接入技术支持LTE时才能设置支持LTE */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_LTE;
        i ++;
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 平台接入技术支持UTRAN时才能设置支持1X */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupport1x())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_1X;
        i ++;
    }

    if (VOS_TRUE == TAF_SDC_IsPlatformSupportHrpd())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_HRPD;
        i ++;
    }
#else
    /* 平台接入技术支持UTRAN时才能设置支持WCDMA */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportUtran())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_WCDMA;
        i ++;
    }

    /* 平台接入技术支持GSM而且硬件支持GSM频段时才能设置支持GSM */
    ulGsmForbiddenFlg = MMA_IsGsmForbidden();
    if ((VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
     && (VOS_FALSE == ulGsmForbiddenFlg))
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_GSM;
        i ++;
    }
#endif

    pstRatPrioList->ucRatOrderNum  = i;

    /* 其它赋值为BUTT */
    for (; i < TAF_PH_MAX_GUL_RAT_NUM; i ++)
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_BUTT;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadNvimRatPrioList
 功能描述  : 从NV en_NV_Item_RAT_PRIO_LIST中获取当前的接入模式设置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，从NV读取用户设置的接入技术列表，并作有效性检查
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  3.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID TAF_MMA_ReadNvimRatPrioList(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          k;
    TAF_PH_NVIM_RAT_ORDER_STRU          stRatPrioList;
    VOS_UINT32                          ulLength;

    ulLength        = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_RAT_PRIO_LIST, &ulLength);
    if (ulLength > sizeof(TAF_PH_NVIM_RAT_ORDER_STRU))
    {
        return;
    }

    PS_MEM_SET(&stRatPrioList, 0X0, ulLength);

    /* 从NV中获取接入技术优先级 */
    if (NV_OK != NV_Read (en_NV_Item_RAT_PRIO_LIST, &stRatPrioList,
                         ulLength))
    {
        MN_MMA_SetDefaultRatPrioList(pstRatPrioList);

        return;
    }

    PS_MEM_CPY(pstRatPrioList, &stRatPrioList, ulLength);

    /* 检查NV数据有效性 */
    for ( i = 0 ; i < pstRatPrioList->ucRatOrderNum; i++ )
    {
        /* 判断是否存在无效的接入技术 */
        if (pstRatPrioList->aenRatOrder[i] >= TAF_MMA_RAT_BUTT)
        {
            MN_MMA_SetDefaultRatPrioList(pstRatPrioList);

            return;
        }

        /* 判断是否存在重复的接入技术 */
        for (k = i + 1 ; k < pstRatPrioList->ucRatOrderNum; k++ )
        {
            if (pstRatPrioList->aenRatOrder[i] == pstRatPrioList->aenRatOrder[k])
            {
                MN_MMA_SetDefaultRatPrioList(pstRatPrioList);

                return;
            }
        }
    }

    /* 删除平台不支持的接入技术 */
    TAF_MMA_DelPlatformUnsupportedRat(pstRatPrioList);

    /* 如果所有接入技术平台都不支持，使用平台默认值 */
    if (0 == pstRatPrioList->ucRatOrderNum)
    {
        MN_MMA_SetDefaultRatPrioList(pstRatPrioList);
    }
    else
    {
        /* 其它赋值为BUTT */
        for (i = pstRatPrioList->ucRatOrderNum; i < TAF_PH_MAX_GUL_RAT_NUM; i ++)
        {
            pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_BUTT;
        }
    }

    return;
}



/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */
/* 删除 MMA_InitMeInfo */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */


/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* TAF_MMA_InitRssiValue移动位置 */
/* MMA_InitGobalValue删除 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */


/*****************************************************************************
 函 数 名  : MMA_InitCm
 功能描述  : 初始化函数，用于软关机时清除CM层其它模块资源，并进行初始化
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月9日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2007年1月30日
    作    者   : L47619
    修改内容   : Modify for A32D08529
  3.日    期   : 2007年8月29日
    作    者   : l60022475
    修改内容   : Modify for A32D12744
  4.日    期   : 2013年4月27日
    作    者   : z60575
    修改内容   : Modify for DTS2013041103232
  5.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 为eCall feature修改
*****************************************************************************/
VOS_VOID    MMA_InitCm(VOS_VOID)
{

#ifndef __PS_WIN32_RECUR__
    TAF_MMA_SndPowerIndMsg();
#else
    Aps_PowerOff();
#endif

    NAS_RabmPowerOff();

    Sm_PowerOff();

    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
    /* 删除该处函数调用，CALL模块收到power off指示消息后调用 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    MN_MSG_PowerOff();

    NAS_CC_PowerOff();

    SMS_Poweroff();

    SSA_PowerOff();

    Ss_Init();

    Tc_TaskInit();

}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* 删除MMA_Init1 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */

/* MMA_ReadSimCPHSOperNameStr */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

/*****************************************************************************
 函 数 名  : MMA_IsNeedToDisplayCPHSOperNameStr
 功能描述  : 是否使用支持CPHS格式的Sim卡中的Operator Name string进行运营商名称显示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年01月10日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2015年2月28日
    作    者   : b00269685
    修改内容   : at&t eons支持修改
*****************************************************************************/
VOS_BOOL   MMA_IsNeedToDisplayCPHSOperNameStr(VOS_VOID)
{
    TAF_SDC_SPN_FILE_INFO_STRU         *pstUsimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_CPHS_FILE_INFO_STRU        *pstCphsFileInfo    = VOS_NULL_PTR;
    VOS_BOOL                            bRptFlg;

    bRptFlg = VOS_FALSE;

    pstUsimSpnFileInfo = TAF_SDC_GetUsimSpnFileInfo();
    pstCphsFileInfo    = TAF_SDC_GetChpsFileInfo();

    /* CPHS文件有效，且SPN无效时，上报^PNN,^OPL */
    if (0 != pstCphsFileInfo->stCPHSOperName.ucLength)
    {
        if (0 == pstUsimSpnFileInfo->stSpnOperName.ucLength)
        {
            bRptFlg = VOS_TRUE;
        }
    }

    return bRptFlg;
}

/*****************************************************************************
 函 数 名  : MMA_ReportOPLParaForCPHSDisplay
 功能描述  : 为显示CPHS SIM卡的6f14 OperNameStr,需要在Sim卡上时OPL也返回OK
 输入参数  : clientId,OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年01月09日
    作    者   : l00130025
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID   MMA_ReportOPLParaForCPHSDisplay(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{
    TAF_PH_USIM_OPL_CNF_STRU            *pstOPL;

    pstOPL   = (TAF_PH_USIM_OPL_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                            sizeof(TAF_PH_USIM_OPL_CNF_STRU));

    if(VOS_NULL_PTR == pstOPL)
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);
        return;
    }

    MMA_MEM_SET(pstOPL, 0, sizeof(TAF_PH_USIM_OPL_CNF_STRU));

    MMA_ParaQueryReport(ClientId, OpId,
                        TAF_PH_OPL_PARA, TAF_ERR_NO_ERROR, pstOPL);

    PS_MEM_FREE(WUEPS_PID_MMA, pstOPL);

    return;

}

/* MMA_CovertCPHSOperNameStrToPNNFormat */

/*****************************************************************************
 函 数 名  : MMA_ReportPNNParaFromCPHSOperNameStr
 功能描述  : 将CPHS SIM卡的6f14 OperNameStr文件转换为PNN格式上报
 输入参数  : clientId,OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年01月09日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2015年2月26日
    作    者   : b00269685
    修改内容   : at&t修改
*****************************************************************************/
VOS_VOID   MMA_ReportPNNParaFromCPHSOperNameStr(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{

    TAF_PH_USIM_PNN_CNF_STRU            *pstPNN          = VOS_NULL_PTR;
    TAF_SDC_CPHS_FILE_INFO_STRU         *pstChpsFileInfo = VOS_NULL_PTR;

    pstChpsFileInfo = TAF_SDC_GetChpsFileInfo();

    pstPNN   = (TAF_PH_USIM_PNN_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                               sizeof(TAF_PH_USIM_PNN_CNF_STRU));

    if(VOS_NULL_PTR == pstPNN)
    {
        MMA_ReportParaQueryError(ClientId, OpId,TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);
        return;
    }

    PS_MEM_SET(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU));

    PS_MEM_CPY(pstPNN->PNNRecord[0].stOperNameLong.aucOperatorName, pstChpsFileInfo->stCPHSOperName.aucOperatorName, TAF_SDC_MAX_OPER_LONG_NAME_LEN);

    pstPNN->TotalRecordNum = 1;
    MMA_ParaQueryReport(ClientId, OpId,
                                TAF_PH_PNN_PARA, TAF_ERR_NO_ERROR, pstPNN);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPNN);
    return;
}

/* MMA_ReadCPHSOperNameStrFileCnf */
/* MMA_ReadCPHSOperNameStrFileExpired */
/* MMA_ReadSpnFileExpired */
/* MMA_ReadSpnFileCnf */



/*****************************************************************************
 函 数 名  : Taf_PhoneGetOperNameInfo
 功能描述  : 从PLMN或长名字或短名字获取运营商剩余两项消息
             PLMN都是BCD码，aucPlmnId[0] = 0000MCC3,
                            aucPlmnId[1] = MCC2MCC1,
                            aucPlmnId[2] = 0000MNC3,
                            aucPlmnId[3] = MNC2MNC1,
             长名字是16位字符串
             短名字是8位字符串
 输入参数  : TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年10月4日
    作    者   : liuyang
    修改内容   : 新生成函数

  2.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02412
  3.日    期   : 2006年10月25日
    作    者   : h44270
    修改内容   : 问题单号：A32D06630
  4.日    期   : 2009年10月12日
    作    者   : l00130025
    修改内容   : 问题单号: AT2D15082,当前plmn变为BCD格式,导致MMA_IsRoam判断失败
  5.日    期   : 2011年02月18日
    作    者   : w00166186
    修改内容   : DTS2010122404937 TME 网络长短名指定搜网处理不合理
  6.日    期   : 2011年07月30日
    作    者   : c00173809
    修改内容   : DTS2011072702612 注册到2G网络后，后台没有显示"Movistar"，标杆正常显示
  7.日    期   : 2012年11月17日
    作    者   : l65478
    修改内容   : DTS2012111508506 long或SHORT存在一种时,应该返回成功
  8.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  9.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  10.日    期   : 2015年2月28日
     作    者   : z00161729
     修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 Taf_PhoneGetOperNameInfo( TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName )
{
    TAF_PH_OPERATOR_NAME_STRU stOperNameTmp;
    VOS_UINT32                ulRet = MMA_FAILURE;
    TAF_UCHAR                 aucSpnName[TAF_PH_OPER_NAME_LONG];

    /*参数有效性判断*/
    if ( VOS_NULL_PTR == pstOperName )
    {
        MMA_WARNINGLOG("Taf_PhoneGetOperNameInfo():WARNING:NULL PTR");
        return ulRet;
    }

    stOperNameTmp = pstOperName->OperName;
    MMA_INFOLOG1("Taf_PhoneGetOperNameInfo():stOperNameTmp.Mcc =",(VOS_INT32)stOperNameTmp.PlmnId.Mcc);
    MMA_INFOLOG1("Taf_PhoneGetOperNameInfo():stOperNameTmp.Mnc =",(VOS_INT32)stOperNameTmp.PlmnId.Mnc);

    PS_MEM_SET(aucSpnName,0x00,TAF_PH_OPER_NAME_LONG);

    /*利用已提供的信息,获取存在NVIM中剩余的运营商姓名*/
    switch ( pstOperName->ListOp )
    {
        /*通过PLMN获得长名字和短名字*/
        case TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME :
            break;

        /*通过短名字获取对应的长名字和PLMN*/
        case TAF_PH_OPER_NAME_SHORTNAME2OTHERS :
            ulRet = MMA_PhoneGetOperInfoByShortNameFromOperTbl(&stOperNameTmp);
            if (MMA_SUCCESS == ulRet)
            {
                pstOperName->OperName = stOperNameTmp;
            }
            break;

        /*通过长名字获取对应的短名字和PLMN*/
        case TAF_PH_OPER_NAME_LONGNAME2OTERS :
            ulRet = MMA_PhoneGetOperInfoByLongNameFromOperTbl(&stOperNameTmp);
            if (MMA_SUCCESS == ulRet)
            {
                pstOperName->OperName = stOperNameTmp;
            }
            break;

        default:
            MMA_WARNINGLOG("Taf_PhoneGetOperNameInfo():WARNING:error ListOp");
            break;
    }
    return ulRet;
}


/*****************************************************************************
 函 数 名  : MMA_PhoneFindNtwkNameByPlmnId
 功能描述  : 通过PLMN获取运营商名字,在本地运营商列表中查找
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pstOperName
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年07月11日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2009年08月24日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D13988,运营商列表需要更新
  3.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  4.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
*****************************************************************************/
VOS_UINT32 MMA_PhoneFindNtwkNameByPlmnId( TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{

    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i = 0;
    VOS_BOOL                            bFound = VOS_FALSE;
    VOS_BOOL                            bContinueSearch = VOS_TRUE;
    TAF_PH_OPERATOR_NAME_TBL_STRU       *pstNetworkNameTbl = VOS_NULL_PTR;

    TAF_PLMN_ID_STRU tmpPlmnId = pstOperName->PlmnId;

    MMA_INFOLOG1("orig MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mcc =",(VOS_INT32)tmpPlmnId.Mcc);
    MMA_INFOLOG1("orig MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mnc =",(VOS_INT32)tmpPlmnId.Mnc);

    tmpPlmnId.Mcc &= 0x0fff;
    tmpPlmnId.Mnc &= 0x0fff;

    if( 0x0F == ((0x0f00 & tmpPlmnId.Mnc) >> 8))
    {
        tmpPlmnId.Mnc &= 0x00ff;
    }
    MMA_INFOLOG1("MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mcc =",(VOS_INT32)tmpPlmnId.Mcc);
    MMA_INFOLOG1("MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mnc =",(VOS_INT32)tmpPlmnId.Mnc);

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();


    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        pstOperName->aucOperatorNameLong[0]  = '\0';
        pstOperName->aucOperatorNameShort[0] = '\0';

        return MMA_FAILURE;
    }

    while(( VOS_TRUE == bContinueSearch )&&(i < usTotalNtwkNum))
    {
        if(tmpPlmnId.Mcc == pstNetworkNameTbl->PlmnId.Mcc)
        {
            if(tmpPlmnId.Mnc == pstNetworkNameTbl->PlmnId.Mnc)
            {
                bFound = VOS_TRUE;
                bContinueSearch = VOS_FALSE;

                (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameLong,
                        pstNetworkNameTbl->pStrOperatorNameLong,TAF_PH_OPER_NAME_LONG);
                (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameShort,
                        pstNetworkNameTbl->pStrOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
            }
            else if (tmpPlmnId.Mnc < pstNetworkNameTbl->PlmnId.Mnc)
            {
                bContinueSearch = VOS_FALSE;
            }
            else
            {
            }
        }
        else if(tmpPlmnId.Mcc < pstNetworkNameTbl->PlmnId.Mcc)
        {
            bContinueSearch = VOS_FALSE;
        }
        else
        {
        }

        pstNetworkNameTbl ++;

        ++ i;

    }

    if(VOS_FALSE == bFound)
    {
        pstOperName->aucOperatorNameLong[0]  = '\0';
        pstOperName->aucOperatorNameShort[0] = '\0';
        return MMA_FAILURE;
    }

    return MMA_SUCCESS;
}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* 获取长短名的NV未使用，相应的函数删除 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */


/*****************************************************************************
 函 数 名  : NAS_MMA_PlmnInCurUserSrchList
 功能描述  : 判断PLMNID是否在上次用户列表搜索的结果中
 输入参数  : TAF_PLMN_ID_STRU *pstPlmnId
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月18日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL NAS_MMA_PlmnInCurUserSrchList(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT32                          i;
    TAF_PLMN_ID_STRU                    stPlmnId;

    for (i = 0; i < g_StatusContext.PlmnList.ucPlmnNum; i++)
    {
        stPlmnId = g_StatusContext.PlmnList.Plmn[i];
        MMA_PlmnId2Bcd(&stPlmnId);

        stPlmnId.Mcc &= 0x0fff;
        stPlmnId.Mnc &= 0x0fff;

        if (0x0F == ((0x0f00 & stPlmnId.Mnc) >> 8))
        {
            stPlmnId.Mnc &= 0x00ff;
        }

        if ((stPlmnId.Mcc == pstPlmnId->Mcc)
         && (stPlmnId.Mnc == pstPlmnId->Mnc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : MMA_PhoneGetOperInfoByLongNameFromOperTbl
 功能描述  : 通过运营商长名字获取PLMNID和短名字
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pOperName
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年08月15日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2009年08月24日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D13988,运营商列表需要更新
  3.日    期   : 2011年02月18日
    作    者   : w00166186
    修改内容   : DTS2010122404937 TME 网络长短名指定搜网处理不合理
  4.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  5.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
  6.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
VOS_UINT32 MMA_PhoneGetOperInfoByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i;
    VOS_BOOL                            bFlag;
    TAF_PH_OPERATOR_NAME_STRU           stDestPhOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    bFlag = VOS_FALSE;
    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    PS_MEM_SET(&stDestPhOperName, 0, sizeof(stDestPhOperName));


    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        pstOperName->aucOperatorNameShort[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;

        return MMA_FAILURE;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameLong),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameLong),
                          TAF_PH_OPER_NAME_LONG) )
        {
            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            pstOperName->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperName->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameShort,
                    pstNetworkNameTbl->pStrOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
            MMA_NORMAILLOG("the specified PLMN found in gastNetworkNameTbl!");


            if (VOS_FALSE == bFlag)
            {
                stDestPhOperName = *pstOperName;
                bFlag            = VOS_TRUE;
            }

            if (VOS_TRUE == NAS_MMA_PlmnInCurUserSrchList(&pstOperName->PlmnId))
            {
                stDestPhOperName = *pstOperName;
                break;
            }

        }

        pstNetworkNameTbl ++;
    }

    if (VOS_FALSE != bFlag)
    {
        (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameShort,
                stDestPhOperName.aucOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
        pstOperName->PlmnId = stDestPhOperName.PlmnId;

        if ( pstOperName->PlmnId.Mnc < 0x100)
        {
            pstOperName->PlmnId.Mnc <<= 4;
            pstOperName->PlmnId.Mnc |= 0xF;
        }

        return MMA_SUCCESS;
    }
    else
    {
        MMA_NORMAILLOG("the specified PLMN not found in gastNetworkNameTbl!");
        pstOperName->aucOperatorNameShort[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;
        return MMA_FAILURE;
    }

}
/*****************************************************************************
 函 数 名  : MMA_PhoneGetOperInfoByShortNameFromOperTbl
 功能描述  : 通过短名字获取PLMNID和长名字
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pOperName
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年08月15日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2009年08月24日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D13988,运营商列表需要更新
  3.日    期   : 2011年02月18日
    作    者   : w00166186
    修改内容   : TME 网络名指定搜网处理不合理
  4.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  5.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
  6.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
VOS_UINT32 MMA_PhoneGetOperInfoByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i ;
    VOS_BOOL                            bFlag;
    TAF_PH_OPERATOR_NAME_STRU           stDestPhOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    bFlag = VOS_FALSE;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    PS_MEM_SET(&stDestPhOperName, 0, sizeof(stDestPhOperName));



    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        pstOperName->aucOperatorNameLong[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;

        return MMA_FAILURE;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameShort),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameShort),
                          TAF_PH_OPER_NAME_SHORT) )
        {
            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            pstOperName->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperName->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameLong,
                    pstNetworkNameTbl->pStrOperatorNameLong,TAF_PH_OPER_NAME_LONG);
            MMA_NORMAILLOG("the specified PLMN found in gastNetworkNameTbl!");


            if (VOS_FALSE == bFlag)
            {
                stDestPhOperName = *pstOperName;
                bFlag            = VOS_TRUE;
            }

            if (VOS_TRUE == NAS_MMA_PlmnInCurUserSrchList(&pstOperName->PlmnId))
            {
                stDestPhOperName = *pstOperName;
                break;
            }
        }

        pstNetworkNameTbl ++;

    }

    if (VOS_FALSE != bFlag)
    {

        (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameLong,
                stDestPhOperName.aucOperatorNameLong,TAF_PH_OPER_NAME_LONG);

        pstOperName->PlmnId              = stDestPhOperName.PlmnId;

        if ( pstOperName->PlmnId.Mnc < 0x100)
        {
            pstOperName->PlmnId.Mnc <<= 4;
            pstOperName->PlmnId.Mnc |= 0xF;
        }

        return MMA_SUCCESS;
    }
    else
    {
        MMA_NORMAILLOG("the specified PLMN not found in gastNetworkNameTbl!");
        pstOperName->aucOperatorNameLong[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;
        return MMA_FAILURE;
    }
}


/*****************************************************************************
 函 数 名  : MMA_PhoneGetAllOperNumByLongNameFromOperTbl
 功能描述  : 获取所有具有相同的长名字的运营商信息个数
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pOperName
             VOS_UINT8 *pucMaxMncLen
 输出参数  : 无
 返 回 值  : VOS_UINT32 ulTotalOperNum 所有具有相同的长名字的运营商信息个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年09月04日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
*****************************************************************************/
VOS_UINT32 MMA_PhoneGetAllOperNumByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName,
                                                                                 VOS_UINT8 *pucMaxMncLen)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT32                          ulTotalOperNum = 0;
    VOS_UINT16                          i = 0;
    VOS_UINT8                           ucCurMncLen;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    *pucMaxMncLen = 0;


    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return ulTotalOperNum;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameLong),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameLong),
                          TAF_PH_OPER_NAME_LONG) )
        {
            /* 累加OPER个数 */
            ulTotalOperNum++;

            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            if ( pstNetworkNameTbl->PlmnId.Mnc < 0x100)
            {
                ucCurMncLen = 5;
            }
            else
            {
                ucCurMncLen = 6;
            }

            if (*pucMaxMncLen < ucCurMncLen)
            {
                *pucMaxMncLen = ucCurMncLen;
            }

        }

        pstNetworkNameTbl ++;
    }

    return ulTotalOperNum;

}


/*****************************************************************************
 函 数 名  : MMA_PhoneGetAllOperNumByShortNameFromOperTbl
 功能描述  : 获取所有具有相同的短名字的运营商信息个数
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pOperName
             VOS_UINT8 *pucMaxMncLen
 输出参数  : 无
 返 回 值  : VOS_UINT32 ulTotalOperNum  所有具有相同的短名字的运营商信息个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年09月04日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
*****************************************************************************/
VOS_UINT32 MMA_PhoneGetAllOperNumByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName,
                                                                                 VOS_UINT8 *pucMaxMncLen)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT32                          ulTotalOperNum = 0;
    VOS_UINT16                          i = 0;
    VOS_UINT8                           ucCurMncLen;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    *pucMaxMncLen = 0;


    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return ulTotalOperNum;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameShort),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameShort),
                          TAF_PH_OPER_NAME_SHORT) )
        {
            /* 累加OPER个数 */
            ulTotalOperNum++;

            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            if ( pstNetworkNameTbl->PlmnId.Mnc < 0x100)
            {
                ucCurMncLen = 5;
            }
            else
            {
                ucCurMncLen = 6;
            }

            if (*pucMaxMncLen < ucCurMncLen)
            {
                *pucMaxMncLen = ucCurMncLen;
            }

        }

        pstNetworkNameTbl ++;
    }

    return ulTotalOperNum;

}

/*****************************************************************************
 函 数 名  : MMA_PhoneGetAllOperInfoByLongNameFromOperTbl
 功能描述  : 通过运营商长名字获取所有PLMNID和短名字
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName
             TAF_PH_OPERATOR_NAME_STRU   *pstOperName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年09月04日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
*****************************************************************************/
VOS_VOID MMA_PhoneGetAllOperInfoByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
                                                                                TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i = 0;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperResult = pstOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();


    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOrigOperName->aucOperatorNameLong),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameLong),
                          TAF_PH_OPER_NAME_LONG) )
        {
            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            pstOperResult->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperResult->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameShort,
                        pstNetworkNameTbl->pStrOperatorNameShort,
                        TAF_PH_OPER_NAME_SHORT);

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameLong,
                        pstNetworkNameTbl->pStrOperatorNameLong,
                        TAF_PH_OPER_NAME_LONG);

            pstOperResult++;
        }

        pstNetworkNameTbl ++;
    }

    return;
}


/*****************************************************************************
 函 数 名  : MMA_PhoneGetAllOperInfoByShortNameFromOperTbl
 功能描述  : 通过短名字获取所有PLMNID和长名字
 输入参数  : TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName
             TAF_PH_OPERATOR_NAME_STRU   *pstOperName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年09月04日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年11月1日
    作    者   : w00167002
    修改内容   : DTS2012102905571:DCM定制需求，如果当前NV配置不显示本地的全球
                  运行商列表信息,则直接返回.
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令
*****************************************************************************/
VOS_VOID MMA_PhoneGetAllOperInfoByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
                                                                                TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i = 0;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperResult = pstOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();


    /* 如果当前NV配置不显示本地的全球运行商列表信息,则直接返回 */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOrigOperName->aucOperatorNameShort),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameShort),
                          TAF_PH_OPER_NAME_SHORT) )
        {
            /* the current short operator name is equal to the specified one
             * copy PLMN ID & long operator name into output parameter and return back
             */
            pstOperResult->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperResult->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameShort,
                        pstNetworkNameTbl->pStrOperatorNameShort,
                        TAF_PH_OPER_NAME_SHORT);

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameLong,
                        pstNetworkNameTbl->pStrOperatorNameLong,
                        TAF_PH_OPER_NAME_LONG);

            pstOperResult++;
        }

        pstNetworkNameTbl ++;

    }

    return;
}



/*****************************************************************************
 Prototype    : MMA_InitAtMsgReq
 Description  : 启动主动上报AT消息功能
 Input        : TAF_START_INFO_IND_STRU        stAtMsgReq
 Output       : None
 Return Value : VOS_VOID
 Calls        :
 Called By    :

  History        :
  1.Date         : 2005/11/6
    Author       : liuyang, id:48197
    Modification : Created function

  2.日    期   : 2006年2月24日
    作    者   : liuyang id:48197
    修改内容   : 增加判断回调函数指针是否为空,问题单号:A32D02143

  3.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  4.日    期   : 2013年3月26日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  5.日    期   : 2014年11月28日
    作    者   : w00281933
    修改内容   : 服务状态显示优化Phase I
*****************************************************************************/
VOS_VOID MMA_InitAtMsgReq( VOS_UINT16   ClientId,
                             VOS_UINT8          OpId,
                             TAF_START_INFO_IND_STRU   stAtMsgReq)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-26, begin */
    VOS_UINT32                   ulRet = MMA_ERROR;
    TAF_PHONE_EVENT_INFO_STRU   *pstPhoneEvent;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-10, begin */
    VOS_UINT32                   ulRptCmdStatus;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-10, end */

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-10, begin */
    /* 更新CERSSI对应的SDC全局变量 */
    if (0 == stAtMsgReq.ucSignThreshold)
    {
        ulRptCmdStatus = VOS_FALSE;
    }
    else
    {
        ulRptCmdStatus = VOS_TRUE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CERSSI, ulRptCmdStatus);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-10, end */

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_InitAtMsgReq:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    if ( (stAtMsgReq.ucActionType > TAF_START_EVENT_INFO_STOP)
       ||(stAtMsgReq.ucRrcMsgType > ( TAF_EVENT_INFO_CELL_BLER
                                     |TAF_EVENT_INFO_CELL_ID
                                     |TAF_EVENT_INFO_CELL_SIGN
                                    )
         )
       )
    {
        MMA_HandleEventError(ClientId, OpId, TAF_ERR_PARA_ERROR, TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP);
        MMA_WARNINGLOG("MMA_InitAtMsgReq():WARNING:Error Para");
        PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
        return;
    }
    else
    {
        ulRet = TAF_MMA_SndMsccSignalReportReq(stAtMsgReq.ucActionType, stAtMsgReq.ucRrcMsgType,
                          stAtMsgReq.ucSignThreshold, stAtMsgReq.ucMinRptTimerInterval);

    }

    /*上报设置结果*/
    if ( MMA_SUCCESS == ulRet)
    {
        pstPhoneEvent->ClientId              = ClientId;
        pstPhoneEvent->OpId                  = OpId;
        pstPhoneEvent->OP_PhoneError         = TAF_PARA_OK;
        pstPhoneEvent->PhoneEvent            = TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP;
        Taf_InitEventInfoOP(pstPhoneEvent);

        /* 调用电话管理上报函数 */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));
    }
    else
    {
        MMA_HandleEventError(ClientId, OpId, TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP);
    }
    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-26, end */

    return;
}

/*****************************************************************************
 函 数 名  : MMA_CleanTiVar
 功能描述  : 清除gastMmaTiTab全局变量对应的值，默认值为0，该函数没有返回值，
             操作成功的有效性由调用者保证
 输入参数  : VOS_UINT16            ClientId
             VOS_UINT8                   OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

  2.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02371，使用宏替换原有的数字
*****************************************************************************/
VOS_VOID MMA_CleanTiVar(VOS_UINT16            ClientId,
                        VOS_UINT8                   OpId     )
{
    VOS_UINT32 ulI = 0;

    for ( ulI = 0; ulI < MMA_MAX_TI ; ulI++ )
    {
        if ( (TAF_USED == gastMmaTiTab[ulI].ucUsed  )
           &&(ClientId == gastMmaTiTab[ulI].ClientId)
           &&(OpId     == gastMmaTiTab[ulI].Id      )
           )
        {
            /*清除当前使用标志*/
            gastMmaTiTab[ulI].ucUsed    = MMA_TI_UNUSED;
            gastMmaTiTab[ulI].ClientId  = MMA_CLIENTID_NONE;
            gastMmaTiTab[ulI].Id        = MMA_OP_ID_INTERNAL;
            break;
        }
    }
    return;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
/*****************************************************************************
 函 数 名  : MMA_BcdNumToAsciiNum
 功能描述  : BCD码转位ASCII码，代码来自SSA
 输入参数  : VOS_UINT8 *pucAsciiNum
             VOS_UINT8 *pucBcdNum
             VOS_UINT8 ucBcdNumLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月9日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum, VOS_UINT8 ucBcdNumLen)
{
    VOS_UINT8       ucTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ucTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ucTmp)) >> 4) & 0x0f);   /*high four bits*/
        if(ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x57;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if(0xf == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x57;
            pucAsciiNum++;
        }
    }
    *pucAsciiNum = '\0';
    return;
}

/*****************************************************************************
 函 数 名  : MMA_ImsiBcd2Ascii
 功能描述  : 转换IMSI格式，将BCD码转为字符串
 输入参数  : VOS_UINT8 ucLen   --BCD码长度
             VOS_UINT8 *pucNum --BCD码存放的位置
             VOS_UINT8 *pucAsciiStr  --字符串写入位置
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月9日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2010年06月13日
    作    者   : f62575
    修改内容   : 问题单号：DTS2010061300180, 局部变量pucAsciiStr初始化使用越界
*****************************************************************************/
VOS_VOID MMA_ImsiBcd2Ascii(VOS_UINT8 ucLen, VOS_UINT8 *pucNum, VOS_UINT8 *pucAsciiStr)
{
    VOS_UINT32 ulI = 0;
    VOS_UINT8   ucTmp;
    /*有效性判断*/
    if ( (VOS_NULL_PTR == pucNum)
       ||(VOS_NULL_PTR == pucAsciiStr)
       ||(           0 == ucLen )
       )
    {
        MMA_WARNINGLOG("MMA_ImsiBcd2Ascii():WARNING:NULL PTR");
        return;
    }

    /*国际移动用户识别码*/
    /*清空存放字符串的缓冲区*/
    for ( ulI = 0; ulI < (VOS_UINT32)ucLen; ulI++ )
    {
        pucAsciiStr[ulI] = 0;
    }
    ucTmp = (*pucNum >> 4) & 0x0f;
    /*取出第一位*/
    MMA_BcdNumToAsciiNum(pucAsciiStr, &ucTmp, 1);
    /*进行Bcd到Ascii的转换*/
    MMA_BcdNumToAsciiNum(pucAsciiStr + 1, pucNum + 1, (ucLen - 1)/2);
    return;
}

/*****************************************************************************
 函 数 名  : MMA_ImeiBcd2Ascii
 功能描述  : 转化IMEI编码为字符串形式
 输入参数  : VOS_UINT8 ucLen   --BCD码长度
             VOS_UINT8 *pucNum --BCD码存放的位置
             VOS_UINT8 *pucAsciiStr  --字符串写入位置
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月9日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_ImeiBcd2Ascii(VOS_UINT8 ucLen, VOS_UINT8 *pucNum, VOS_UINT8 *pucAsciiStr)
{
    VOS_UINT32 ulI = 0;
    if ( (VOS_NULL_PTR == pucNum)
       ||(VOS_NULL_PTR == pucAsciiStr)
       ||(           0 == ucLen )
       )
    {
        MMA_WARNINGLOG("MMA_ImsiBcd2Ascii():WARNING:NULL PTR");
        return;
    }
    /*国际移动设备识别码*/
    for ( ulI = 0; ulI < ucLen ; ulI++ )
    {
        *(pucAsciiStr + ulI) = *(pucNum + ulI) + 0x30;
    }
    pucAsciiStr[ulI] = '\0';
    return;
}

/*****************************************************************************
 函 数 名  : MMA_ImeiBcd2Ascii
 功能描述  : 转化IMEI编码为BCD形式
 输入参数  : VOS_UINT8 *pucBcdNum --BCD码存放的位置
             VOS_UINT8 *pucAsciiNum  --字符串
 输出参数  : 无
 返 回 值  : VOS_UINT32 --传入为空指针或长度为0时，返回错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年10月25日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MMA_ImeiAsciiToBcd(VOS_UINT8 *pucAsciiNum, VOS_UINT8 ucAsciiNumLen, VOS_UINT8 *pucBcdNum)
{
    VOS_UINT32 ulI = 0;
    if ( (VOS_NULL_PTR == pucAsciiNum)
       ||(VOS_NULL_PTR == pucBcdNum)
       ||(           0 == ucAsciiNumLen )
       )
    {
        MMA_WARNINGLOG("MMA_ImeiAsciiToBcd():WARNING:NULL PTR");
        return MMA_FAILURE;
    }
    /*国际移动设备识别码*/
    for ( ulI = 0; ulI < ucAsciiNumLen ; ulI++ )
    {
        *(pucBcdNum + ulI) = *(pucAsciiNum + ulI) - 0x30;
    }

    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Taf_GetCurrentAttachStatus(过时)
 功能描述  : 获取当前CS附着结果,由g_StatusContext全局变量中的服务状态获得，
 输入参数  : TAF_PH_CS_STATUS    *pCsResult
             TAF_PH_PS_STATUS    *pPsResult
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月30日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2015年4月17日
    作    者   : h00313353
    修改内容   : SysCfg Reconsitution
*****************************************************************************/
VOS_VOID Taf_GetCurrentAttachStatus(
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    *penCsResult,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    *penPsResult
)
{

    /*只有当当前服务状态为正常服务或限制服务状态才被认为成功附着，其余状态都
      为未附着*/
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if  ( TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        *penCsResult = TAF_MMA_ATTACH_STATUS_ATTACHED;
    }
    else
    {
        *penCsResult = TAF_MMA_ATTACH_STATUS_DETACHED;
    }
    if  (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetPsServiceStatus())
    {
        *penPsResult = TAF_MMA_ATTACH_STATUS_ATTACHED;
    }
    else
    {
        *penPsResult = TAF_MMA_ATTACH_STATUS_DETACHED;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

/*****************************************************************************
 函 数 名  : MMA_PlmnId2Bcd
 功能描述  : 将原PLMNid转化为BCD格式记录
             例如:MCC为460,MNC为01时,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        ---->
             pstPlmnId->Mnc = 0x0f0100      pstPlmnId->Mnc = 0x00000f01
 输入参数  : TAF_PLMN_ID_STRU *pstPlmnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月20日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

  2.日    期   : 2006年2月23日
    作    者   : liuyang id:48197
    修改内容   : 根据与Wcdma的接口修改传入的PLMN顺序,问题单号:A32D02119
*****************************************************************************/
VOS_VOID MMA_PlmnId2Bcd(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT32  ulTmp;
    VOS_UINT8   aucTmp[4];

    ulTmp           = pstPlmnId->Mcc;
    pstPlmnId->Mcc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }
    pstPlmnId->Mcc = ((VOS_UINT32)aucTmp[0] << 8)
                    |((VOS_UINT32)aucTmp[1] << 4)
                    | aucTmp[2];

    ulTmp           = pstPlmnId->Mnc;
    pstPlmnId->Mnc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }

    /*pstPlmnId->Mnc = ((VOS_UINT32)aucTmp[0] << 8)
                    |((VOS_UINT32)aucTmp[1] << 4)
                    | aucTmp[2];*/
    if(0xf == aucTmp[2])
    {
        pstPlmnId->Mnc = ((VOS_UINT32)aucTmp[0] << 4)
                        |((VOS_UINT32)aucTmp[1] )
                        |0xf00;
    }
    else
    {
        pstPlmnId->Mnc = ((VOS_UINT32)aucTmp[0] << 8)
                    |((VOS_UINT32)aucTmp[1] << 4)
                    | aucTmp[2];
    }
    return;
}


/*****************************************************************************
 函 数 名  : MMA_PlmnId2NasStyle
 功能描述  : 将原PLMNid转化为NAS内部使用格式记录
             例如:MCC为460,MNC为01时,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        <----
             pstPlmnId->Mnc = 0x000100      pstPlmnId->Mnc = 0x00000001
 输入参数  : TAF_PLMN_ID_STRU *pstPlmnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月20日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

  2.日    期   : 2006年2月23日
    作    者   : liuyang id:48197
    修改内容   : 根据与Wcdma的接口修改传入的PLMN顺序,问题单号:A32D02119

*****************************************************************************/
VOS_VOID MMA_PlmnId2NasStyle(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT8   aucTmp[4];
    VOS_UINT32  ulTmp;

    ulTmp           = pstPlmnId->Mcc;
    pstPlmnId->Mcc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    pstPlmnId->Mcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    ulTmp           = pstPlmnId->Mnc;
    pstPlmnId->Mnc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    /*pstPlmnId->Mnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);*/
    if(0xf == aucTmp[2])
    {
        pstPlmnId->Mnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->Mnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }
    return;
}

/* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-13, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_IsUsimCardStatusChanged
 功能描述  : 判断USIM卡状态与当前SDC中存储的卡状态是否发生了改变
 输入参数  : VOS_UINT32  ulUsimSta
 输出参数  : 无
 返 回 值  : TRUE --Usim status change
             FALSE--Usim status not change
 修改历史      :
  1.日    期   : 2007年07月21日
    作    者   : l60022475
    修改内容   : A32D12535
  2.日    期   : 2013年4月4日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : DTS2013071900570:SVLTE特性开启时候，MODEM1解pin后，MODEM0收到
                卡状态为AVAILABLE时候，没有发起重启。原因在于:
                当前解PIN码之前，SDC中维护的卡状态为TAF_SDC_USIM_STATUS_VALID，
                MODEM在收到解PIN的RSP消息时候，才会将SDC的卡状态重新设置为TAF_SDC_USIM_STATUS_UNVALID
                ，这样再收到USIM上报的卡状态为AVAILABLE时候，会发起重启。
                修改为SDC存储SIM卡的原始状态，MODEM在收到解PIN的RSP消息时候,
                不需重新设置SIM状态为TAF_SDC_USIM_STATUS_UNVALID。MODEM的重启
                由SIM卡状态的变迁来决定。如:卡状态由SIM_PIN--->AVAIALBLE,则触发
                重启动。
  4.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM接口调整，改为判断Usim卡状态是否改变
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUsimCardStatusChanged(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus
)
{
     /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    VOS_UINT32                          ulChangeFlg;

    enSimStatus     = TAF_SDC_GetUsimStatus();

    /* 默认USIM状态没有改变 */
    ulChangeFlg = VOS_FALSE;

    switch ( enCardStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
        case USIMM_CARD_SERVIC_UNAVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_AVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_SIM_PIN :
        case USIMM_CARD_SERVIC_SIM_PUK :
        case USIMM_CARD_SERVIC_NET_LCOK :
        case USIMM_CARD_SERVICE_IMSI_LOCK :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(enSimStatus);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMA, "MMA_IsUsimStatusChange:WARNING INVALID SIM STATUS!");
            break;
    }

    return ulChangeFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsCsimCardStatusChanged
 功能描述  : 判断Csim卡状态是否发生改变
 输入参数  : VOS_UINT32 ulCardStatus: 最新的卡状态
 输出参数  : 无
 返 回 值  : TRUE -- 状态发生改变
             FALSE-- 状态未发生改变
 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCsimCardStatusChanged(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus
)
{
     /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    VOS_UINT32                          ulChangeFlg;

    enSimStatus     = TAF_SDC_GetCsimStatus();

    /* 默认USIM状态没有改变 */
    ulChangeFlg = VOS_FALSE;

    switch ( enCardStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
        case USIMM_CARD_SERVIC_UNAVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_AVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_SIM_PIN :
        case USIMM_CARD_SERVIC_SIM_PUK :
        case USIMM_CARD_SERVIC_NET_LCOK :
        case USIMM_CARD_SERVICE_IMSI_LOCK :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(enSimStatus);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMA, "MMA_IsUsimStatusChange:WARNING INVALID SIM STATUS!");
            break;
    }

    return ulChangeFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsCardStatusChanged
 功能描述  : 判断卡状态是否发生改变
 输入参数  : USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg: 卡状态消息
 输出参数  : 无
 返 回 值  : TRUE -- 发生改变
             FALSE-- 未发生改变
 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCardStatusChanged(
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg
)
{
    VOS_UINT32                          ulIsUsimStatusChanged;
    VOS_UINT32                          ulIsCsimStatusChanged;

    ulIsUsimStatusChanged = TAF_MMA_IsUsimCardStatusChanged(pstUsimMsg->stUsimSimInfo.enCardService);
    ulIsCsimStatusChanged = TAF_MMA_IsCsimCardStatusChanged(pstUsimMsg->stCsimUimInfo.enCardService);

    return (VOS_UINT32)(ulIsUsimStatusChanged || ulIsCsimStatusChanged);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsImsiChanged
 功能描述  : 判断IMSI与SDC中的相比是否发生了改变(USIMM)
 输入参数  : pstUsimMsg--卡状态改变消息
 输出参数  : 无
 返 回 值  : TRUE --imsi change
             FALSE--imsi not change
 修改历史      :
  1.日    期   : 2013年07月13日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年04月28日
    作    者   : s00246516
    修改内容   : 双IMSI切换时,MMA概率不触发关机和开机操作
  3.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsImsiChanged(
    USIMM_CARD_STATUS_STRU            *pstUsimMsg,
    VOS_UINT8                         *pstImsi
)
{
    VOS_UINT8                          *pucSdcImsi = VOS_NULL_PTR;
    if (USIMM_CARD_SERVIC_AVAILABLE != pstUsimMsg->enCardService)
    {
        return VOS_FALSE;
    }

    pucSdcImsi = TAF_SDC_GetLastSimImsi();

    if (0 != VOS_MemCmp(pucSdcImsi, pstImsi, NAS_MAX_IMSI_LENGTH))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-13, end */

/* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */

/* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

/*****************************************************************************
 函 数 名  : MMA_ForwardOmMaintainInfoInd
 功能描述  : 转发OM的SDT连接指示到指定PID
 输入参数  : VOS_UINT32 ulReceiverPid   消息接收模块PID
             ulMsgName: 消息ID
             ucOmConnectFlg: PC 工具连接状态
             ucOmPcRecurEnableFlg: PC 回放消息使能标志
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 修改历史      :
  1.日    期   : 2010年2月11日
    作    者   : f62575
    修改内容   : 转发SDT连接指示到指定PID

  2.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : DTS2012041805606
*****************************************************************************/
VOS_VOID MMA_ForwardOmMaintainInfoInd(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT8                           ucOmConnectFlg,
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    MMCM_OM_MAINTAIN_INFO_IND_STRU     *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* 消息发送内存申请 */
    pstSndMsg = (MMCM_OM_MAINTAIN_INFO_IND_STRU*)PS_ALLOC_MSG(
                                           WUEPS_PID_MMA,
                                           sizeof(MMCM_OM_MAINTAIN_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
               "MMA_ForwardOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid          = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid        = ulReceiverPid;
    pstSndMsg->ulLength             = sizeof(MMCM_OM_MAINTAIN_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH;

    pstSndMsg->ulMsgName            = ulMsgName;

    pstSndMsg->ucOmConnectFlg       = ucOmConnectFlg;
    pstSndMsg->ucOmPcRecurEnableFlg = ucOmPcRecurEnableFlg;
    pstSndMsg->aucRsv2[0]           = 0;
    pstSndMsg->aucRsv2[1]           = 0;


    /* 消息发送 */
    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if( VOS_OK != ulRst)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "MMA_ForwardOmMaintainInfoInd:ERROR: Fail to send message!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MMA_SndAtOmMaintainInfoInd
 功能描述  : 转发OM的SDT连接指示到ATS
 输入参数  :
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 修改历史      :
  1.日    期   : 2010年2月11日
    作    者   : f62575
    修改内容   : 转发SDT连接指示到指定PID

  2.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : DTS2012041805606
*****************************************************************************/
VOS_VOID MMA_SndAtOmMaintainInfoInd(
    VOS_UINT8                           ucOmConnectFlg,
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    ATMMA_OM_MAINTAIN_INFO_IND_STRU    *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;


    /* 消息发送内存申请 */
    pstSndMsg = (ATMMA_OM_MAINTAIN_INFO_IND_STRU*)PS_ALLOC_MSG(
                                           WUEPS_PID_MMA,
                                           sizeof(ATMMA_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
               "MMA_SndAtOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid          = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid        = WUEPS_PID_AT;
    pstSndMsg->ulLength             = sizeof(ATMMA_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSndMsg->ulMsgName            = ID_TAF_MMA_OM_MAINTAIN_INFO_IND;

    pstSndMsg->ucOmConnectFlg       = ucOmConnectFlg;
    pstSndMsg->ucOmPcRecurEnableFlg = ucOmPcRecurEnableFlg;
    pstSndMsg->aucRsv2[0]           = 0;
    pstSndMsg->aucRsv2[1]           = 0;

    /* 消息发送 */
    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if( VOS_OK != ulRst)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "MMA_SndAtOmMaintainInfoInd:ERROR: Fail to send message!");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : MMA_PhoneGetUsim
 功能描述  : 获取当前USIM状态
 输入参数  : VOS_UINT8 *pucSimStatus
 输出参数  : 无
 返 回 值  : VOS_UINT32 0:获取状态成功
                        1:获取状态失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2005年10月10日
    作    者   : liuyang
    修改内容   : 新生成函数
  2.日    期   : 2011年12月17日
    作    者   : l00130025
    修改内容   : DTS2011121307739,有Pin码或Puk码时，卡状态上报错误
  3.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2012年8月10日
    作    者   : z40661
    修改内容   : DTS2012091600503, 有PIN码时开机失败
  15.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
 16.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
VOS_UINT32 MMA_PhoneGetUsimStatus( VOS_UINT8 *pucSimStatus )
{
    VOS_UINT8               ucUsimStatus;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    /*获取当前USIM状态*/
    /*当调用USIMAPI的值不为0,则表示有错误*/

    ucUsimStatus = USIMM_CARD_SERVIC_ABSENT;

    if( MMA_SUCCESS != MMA_GetUsimStatusFromUsim(&ucUsimStatus, VOS_NULL_PTR) )
    {
        MMA_WARNINGLOG("MMA_PhoneGetUsimStatus():WORNING:Invoke Taf_UsimmGetStatus fail.");
        *pucSimStatus = MMA_USIM_NOREADY;
        return MMA_ERROR;
    }

    /*获取当前USIM状态*/
    if(USIMM_CARD_SERVIC_ABSENT == ucUsimStatus)
    {
        *pucSimStatus = MMA_USIM_ABSENT;

        MMA_NORMAILLOG("MMA_PhoneGetUsimStatus():USIM is not present!");
    }
    else
    {
        *pucSimStatus = MMA_USIM_PRESENT;

        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(gstMmaValue.stUsimInfo.UsimStatus.aucImsi);

        if (USIMM_API_SUCCESS != ulGetCardImsiRslt)
        {
            MMA_NORMAILLOG("MMA_PhoneGetUsimStatus():USIMM_GetCardIMSI failed!");

            if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
            {

#if (FEATURE_ON == FEATURE_PTM)
                /* 记录获取卡IMSI异常log */
                TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, gstMmaValue.stUsimInfo.UsimStatus.aucImsi);
#endif
            }

        }

        MMA_NORMAILLOG("MMA_PhoneGetUsimStatus():USIM is present!");

    }

    return MMA_SUCCESS;
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

/*****************************************************************************
 函 数 名  : MMA_CheckPin1SatusSimple
 功能描述  : 由于开机无法获取全部PIN状态，只查询PIN1状态，
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年2月23日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2007年02月09日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号A32D08488
  3.日    期   : 2008年12月24日
    作    者   : h44270
    修改内容   : 根据问题单号AT2D07796
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
*****************************************************************************/
VOS_UINT32 MMA_CheckPin1SatusSimple(VOS_VOID)
{
    TAF_PH_PIN_CNF_STRU  stPinTmp;

    stPinTmp.PinType     = TAF_SIM_PIN;
    /*查询是否需要PIN1码*/
    stPinTmp.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinTmp.PinType),
                                                   &(stPinTmp.QueryResult.UsimmEnableFlg),
                                                   &(stPinTmp.QueryResult.UsimmNeedType),
                                                   &(stPinTmp.ucRemain));

    if( stPinTmp.OpPinResult != TAF_PH_OP_PIN_OK )
    {
        MMA_WARNINGLOG("MMA_CheckPin1SatusSimple():WARNING:QUERY PIN Status Fail!");
        return MMA_PIN1_STATUS_FAIL;
    }
    else
    {
        if ( USIMM_PIN_NEED == stPinTmp.QueryResult.UsimmNeedType )
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NEED!");
            return MMA_NEED_PIN1;
        }
        else if( USIMM_PUK_NEED == stPinTmp.QueryResult.UsimmNeedType )
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NEED!");
            return MMA_NEED_PUK1;
        }
        else if( USIMM_PUK_BLOCK == stPinTmp.QueryResult.UsimmNeedType )
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NEED!");
            return MMA_PUK1_REMAINS_ZERO;
        }
        else
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NO NEED!");
            return MMA_NONEED_PIN1;
        }
    }
}

/*****************************************************************************
 函 数 名  : MMA_StartInternalTimer
 功能描述  : 启动内部定时器用于延时
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月2日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

  2.日    期   : 2006年3月15日
    作    者   : liuyang id:48197
    修改内容   : 增加启动定时器状态判断
*****************************************************************************/
VOS_UINT32 MMA_StartInternalTimer(VOS_UINT32    ulTimes,
                                  VOS_UINT32    ulOpType,
                                  VOS_UINT16 ClientId,
                                  VOS_UINT8        OpId)
{
    VOS_UINT32 ulRet;

    if ( ulTimes < 1)
    {
        MMA_WARNINGLOG("MMA_StartInternalTimer():WARNING:TIMES IS ZERO, NO DELAY");
        return MMA_ERROR;
    }
    if ( MMA_INTERNAL_OP_NONE  == ulOpType)
    {
        MMA_WARNINGLOG("MMA_StartInternalTimer():WARNING:OP TYPE NONE, NO DELAY");
        return MMA_ERROR;
    }
    if( gstMmaInternalTimer.stTimer.ucTimerStatus != MMA_TIMER_STOP)
    {
        MMA_WARNINGLOG("MMA_StartInternalTimer():WARNING:TIMER HAS ALREADY START");
        return MMA_ERROR;
    }
    gstMmaInternalTimer.ulTimes                       = ulTimes;
    gstMmaInternalTimer.ulOpType                      = ulOpType;
    gstMmaInternalTimer.ClientId                      = ClientId;
    gstMmaInternalTimer.OpId                          = OpId;
    /*启动定时器*/
    ulRet =  NAS_StartRelTimer(  &(gstMmaInternalTimer.stTimer.MmaHTimer),
                                 WUEPS_PID_MMA,
                                 MMA_INTERNAL_TIME,
                                 TAF_MMA,
                                 MMA_INTERNAL_TIMER_ID,
                                 VOS_RELTIMER_NOLOOP );
    if( ulRet != VOS_OK )
    {
        MMA_ERRORLOG("MMA_StartInternalTimer():ERROR:Start Timer Error!");
        /*返回操作失败*/
        gstMmaInternalTimer.stTimer.ucTimerStatus     = MMA_TIMER_ERROR;
        return MMA_ERROR;
    }
    gstMmaInternalTimer.stTimer.ucTimerStatus         = MMA_TIMER_RUN;

    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : MMA_ExpiredInternalTimer
 功能描述  : MMA新增内部定时器处理函数
 输入参数  : REL_TIMER_MSG * pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月2日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2007年07月24日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号A32D12535
  3.日    期   : 2009年09月12日
    作    者   : l00130025
    修改内容   : 问题单AT2D14435,^CPNN命令的实现
  4.日    期   : 2012年04月19日
    作    者   : w00166186
    修改内容   : 问题单号:DTS2012041402670,HPLMN MNC长度为3时显示不正确
  5.日    期   : 2013年6月14日
    作    者   : z60575
    修改内容   : share_image合入
  6.日    期   : 2013年8月30日
    作    者   : w00167002
    修改内容   : DTS2013082903145:双卡模式，设置PIN码后，用户解PIN后流程出错。
                  修改为:开机TAF的PID初始化时，设置SDC中当前卡的状态该为BUTT.
                  USIM模块给NAS上报卡状态则更新SDC中维护的卡状态。如果开机USIM
                  不上报卡状态，则设置当前卡状态为TAF_SDC_USIM_STATUS_UNVALID。
  7.日    期   : 2013年07月15日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目
  8.日    期   : 2015年2月26日
    作    者   : b00269685
    修改内容   : at&t修改
*****************************************************************************/
VOS_VOID MMA_ExpiredInternalTimer(VOS_VOID)
{
    TAF_MMA_GET_HPLMN_STRU             *pstHplmnInfo = VOS_NULL_PTR;

    pstHplmnInfo = TAF_MMA_GetHplmnInfo();

    if ( MMA_TIMER_RUN != gstMmaInternalTimer.stTimer.ucTimerStatus )
    {
        MMA_WARNINGLOG("MMA_ExpiredInternalTimer():WARNING:It's not wait for this Timer!");
        return;
    }
    /*设置定时器状态标志*/
    gstMmaInternalTimer.stTimer.ucTimerStatus = MMA_TIMER_STOP;
    switch ( gstMmaInternalTimer.ulOpType )
    {
        /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

        /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


        case MMA_GET_USIM_ICC_ID:
            if ( gstMmaInternalTimer.ulTimes < MMA_WAIT_GET_USIM_ICC_ID_MAX_TIMES )
            {
                if (  MMA_SUCCESS == MMA_StartInternalTimer(gstMmaInternalTimer.ulTimes+1,
                                                            MMA_GET_USIM_ICC_ID,
                                                            gstMmaInternalTimer.ClientId,
                                                            gstMmaInternalTimer.OpId))
                {
                    MMA_NORMAILLOG("MMA_ExpiredInternalTimer():NORMAL:Continue to get ICC ID Ready");
                    return;
                }
                else
                {
                    MMA_WARNINGLOG("MMA_ExpiredInternalTimer():WARNING:START INTERNAL TIMER FAIL for ICC ID Ready");
                    /*调用超时处理函数*/
                    MMA_GetUsimIccIdExpired();
                }
            }
            else
            {
                /*调用超时处理函数*/
                MMA_GetUsimIccIdExpired();
            }
            break;


        case MMA_GET_USIM_EHPLMN_AND_MNC_LEN_OP:
            MMA_WARNINGLOG("MMA_ExpiredInternalTimer():WARNING:START INTERNAL TIMER FAIL for HPLMN MNC LEN");

            TAF_MMA_SndApHplmnCnf(TAF_ERR_AT_ERROR,
                                  &(pstHplmnInfo->stCtrl),
                                  VOS_NULL_PTR);

            pstHplmnInfo->enWaitSimFileCnfFlg = TAF_MMA_READ_USIM_FILE_FLG_NULL;

            break;

        default:
            MMA_WARNINGLOG("MMA_ExpiredInternalTimer:WARNING:NONE Op Type fit the Timer");
            break;
    }
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, begin */
    /*清除当前内部定时器全局标志*/
    TAF_MMA_InitInternalTimer();
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-15, end */

    return;
}


/*****************************************************************************
 函 数 名  : Mma_CheckPin
 功能描述  : 检查PIN码有效性
 输入参数  : TAF_PH_PIN_DATA_STRU stPinData
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2006年3月16日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02412
  3.日    期   : 2007年09月30日
    作    者   : Z100318
    修改内容   : 问题单号:A32D12964
  4.日    期   : 2012年04月21日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目修改
*****************************************************************************/
VOS_UINT32 Mma_CheckPin(TAF_PH_PIN_DATA_STRU stPinData)
{
    VOS_UINT32                          ulTemp;
    if ( MMA_SUCCESS != Mma_CheckPinCmdType(stPinData.CmdType))
    {
        MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN cmd Type error!");
        return MMA_ERROR;
    }
    if ( MMA_SUCCESS != Mma_CheckPinTypes(stPinData.PinType))
    {
        MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN TYPES ERROR!");
        return MMA_ERROR;
    }
    /*只有CHANGE与UNBLOCK的 时候才会使用NEWPIN，其余命令只需使用OLDPIN，
    查询命令时不关心PIN*/
    switch ( stPinData.CmdType )
    {
        case TAF_PIN_UNBLOCK:
        case TAF_PIN_CHANGE:
            ulTemp = Mma_CheckPinAvail(stPinData.aucOldPin);
            if ( (MMA_SUCCESS != Mma_CheckPinAvail(stPinData.aucNewPin))
               ||(MMA_SUCCESS != ulTemp)
               )
            {
                MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN is Error");
                return MMA_ERROR;
            }
            return MMA_SUCCESS;
        case TAF_PIN_VERIFY:
        case TAF_PIN_DISABLE:
        case TAF_PIN_ENABLE:
        /*case TAF_PIN_UNBLOCK:*/
            return Mma_CheckPinAvail(stPinData.aucOldPin);
        case TAF_PIN_QUERY:
        case TAF_PIN_RemainTime:
        case TAF_PIN2_QUERY:
            return MMA_SUCCESS;
        default:
            MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN cmd Type error in switch");
            return MMA_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : Mma_CheckPinTypes
 功能描述  : 校验PIN类型
 输入参数  : TAF_PH_PIN_TYPE PinTypes
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Mma_CheckPinTypes(TAF_PH_PIN_TYPE PinTypes)
{
    switch ( PinTypes)
    {
        case TAF_SIM_PIN:
        case TAF_SIM_PUK:
        case TAF_SIM_PIN2:
        case TAF_SIM_PUK2:
        case TAF_SIM_NON:
            return MMA_SUCCESS;
        default:
            MMA_WARNINGLOG("Mma_CheckPinTypes():WARNING:UNSUPPORT Pin Types");
            return MMA_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : Mma_CheckPinCmdType
 功能描述  : 检查PIN命令类型
 输入参数  : TAF_PH_PIN_CMD_TYPE PinCmdType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2007年09月30日
    作    者   : Z100318
    修改内容   : 问题单号:A32D12964
  3.日    期   : 2012年04月21日
    作    者   : L47619
    修改内容   : AP-Modem锁网锁卡项目修改
*****************************************************************************/
VOS_UINT32 Mma_CheckPinCmdType(TAF_PH_PIN_CMD_TYPE PinCmdType)
{
    VOS_UINT32 ulRet;

    switch ( PinCmdType)
    {
        case TAF_PIN_VERIFY:
        case TAF_PIN_CHANGE:
        case TAF_PIN_DISABLE:
        case TAF_PIN_ENABLE:
        case TAF_PIN_UNBLOCK:
        case TAF_PIN_QUERY:
        case TAF_PIN_RemainTime:
        case TAF_PIN2_QUERY:
            ulRet = MMA_SUCCESS;
            break;
        default:
            MMA_WARNINGLOG("Mma_CheckPinCmdType():WARNING:UNKNOW PIN CMD TYPE");
            ulRet = MMA_ERROR;
            break;
    }
    return ulRet;
}

/*****************************************************************************
 函 数 名  : Mma_CheckPinLength
 功能描述  : Pin长度判断
 输入参数  : VOS_UINT8 *pucPin
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Mma_CheckPinLength(VOS_UINT8 *pucPin)
{
    if ( VOS_NULL_PTR == pucPin)
    {
        MMA_WARNINGLOG("Mma_CheckPinLength():WARNING:PIN is NULL PTR");
        return MMA_ERROR;
    }
/*
    ulTemp = VOS_StrLen((VOS_INT8 *)pucPin);
    if ( (ulTemp > MMA_PIN_LEN_MAX)
       ||(ulTemp < MMA_PIN_LEN_MIN)
       )
    {
        MMA_WARNINGLOG("Mma_CheckPinLength():WARNING:PIN LENGTH is Error");
        return MMA_ERROR;
    }
 */
    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Mma_CheckPinValue
 功能描述  : 检查PIN值有效性
 输入参数  : VOS_UINT8 *pucPin
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Mma_CheckPinValue(VOS_UINT8 *pucPin)
{
    if ( VOS_NULL_PTR == pucPin)
    {
        MMA_WARNINGLOG("Mma_CheckPinValue():WARNING:PIN is NULL PTR");
        return MMA_ERROR;
    }
/*
    for ( ulI = 0; ulI < VOS_StrLen((VOS_INT8 *)pucPin) ; ulI++ )
    {
        if ( (pucPin[ulI] >'9' )
           ||(pucPin[ulI] <'0')
           )
        {
            MMA_WARNINGLOG("Mma_CheckPinValue():WARNING:PIN Value is Error");
            return MMA_ERROR;
        }
    }
*/
    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Mma_CheckPinAvail
 功能描述  : 检查PIN有效性
 输入参数  : VOS_UINT8 *pucPin
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月8日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Mma_CheckPinAvail(VOS_UINT8 *pucPin)
{
    if ( MMA_SUCCESS != Mma_CheckPinLength(pucPin) )
    {
        MMA_WARNINGLOG("Mma_CheckPinAvail():WARNING:PIN Length is Error");
        return MMA_ERROR;
    }
    else
    {
        if ( MMA_SUCCESS != Mma_CheckPinValue(pucPin))
        {
            MMA_WARNINGLOG("Mma_CheckPinAvail():WARNING:PIN Value is Error");
            return MMA_ERROR;
        }
    }
    return MMA_SUCCESS;
}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* MMA_InitTi位置移动 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
/* NAS_MMA_RestoreContextData函数位置移动 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, end */

/*****************************************************************************
 函 数 名  : NAS_MMA_SndOutsideContextData
 功能描述  : 把MMA外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年01月03日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2009年09月05日
    作    者   : 欧阳飞 00132663
    修改内容   : AT2D14282, 增加版本信息输出。
  3.日    期   : 2013年4月1日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID NAS_MMA_SndOutsideContextData()
{
    NAS_MMA_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                               *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    pSndMsgCB = (NAS_MMA_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MMA_ERRORLOG("NAS_MMA_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    (VOS_VOID)VOS_StrNCpy(pstOutsideCtx->acVersionBuffer, PROTOCOL_STACK_VERSION, VER_MAX_LENGTH);
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    pstOutsideCtx->ucSimType = g_MmaNewValue.ucSimType;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    PS_MEM_CPY(pstOutsideCtx->pc_g_aucMmaImsi, pucImsi, 9);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    PS_MEM_CPY(pstOutsideCtx->pc_g_aucMmaImei, g_aucMmaImei, TAF_PH_IMEI_LEN-1);

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    PS_MEM_CPY(&pstOutsideCtx->pc_g_StatusContext, &g_StatusContext, sizeof(STATUS_CONTEXT_STRU));

    PS_MEM_CPY(&pstOutsideCtx->pc_gstMmaValue, &gstMmaValue, sizeof(TAF_MMA_GLOBAL_VALUE_ST));
    PS_MEM_CPY(&pstOutsideCtx->pc_g_stMmaMePersonalisationStatus, &g_stMmaMePersonalisationStatus, sizeof(MMA_ME_PERSONALISATION_STATUS_STRU));
    PS_MEM_CPY(pstOutsideCtx->pc_gastMmaTiTab, gastMmaTiTab, MMA_MAX_TI*sizeof(MMA_TI_TABLE));

    PS_MEM_CPY(&pstOutsideCtx->pc_gstMmaInternalTimer, &gstMmaInternalTimer, sizeof(MMA_INTERNAL_TIMER_ST));
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */
    PS_MEM_CPY(pstOutsideCtx->pc_g_MmaSimTimer, g_MmaSimTimer, TAF_SIM_TIMER_NUM*sizeof(MMA_TIMER_ST));

    pSndMsgCB->ulReceiverPid = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->usMsgID       = EVT_NAS_MMA_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_MMA, pSndMsgCB);

    return;
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
/* NAS_MMA_RestoreFixedContextData函数位置移动 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, end */


/*****************************************************************************
 函 数 名  : NAS_MMA_SndOutsideFixedContextData
 功能描述  : 把MMA外部固定变量上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年05月11日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2009年09月1日
    作    者   : 欧阳飞 00132663
    修改内容   : AT2D14178,增加输出全局变量:gstMmaBandCapa
  3.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : V7R1 phase II支持syscfgex命令修改
  4.日    期   : 2011年6月28日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号: DTS2011040204531,删除en_NV_Item_Ps_Delay_Flag
  5.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_MMA_SndOutsideFixedContextData()
{
    NAS_MMA_FIXED_CONTEXT_MSG_ST                   *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MMA_FIXED_PART_CONTEXT_ST                  *pstOutsideCtx;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU            *pstLastSyscfgSet = VOS_NULL_PTR;
    TAF_MMA_RAT_ORDER_STRU                         *pstAllRatOrder      = VOS_NULL_PTR;
    MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8                 enCpamPlmnPrio;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8                 enAccessMode;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    pucImsi          = TAF_SDC_GetSimImsi();

    pSndMsgCB = (NAS_MMA_FIXED_CONTEXT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_FIXED_CONTEXT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MMA_ERRORLOG("NAS_MMA_SndOutsideFixedContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stFixedOutsideCtx;

    /* version 0 part variable */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    PS_MEM_CPY(pstOutsideCtx->aucMmaImsi, pucImsi, 9);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    pstOutsideCtx->aucSimType = g_MmaNewValue.ucSimType;

    pstOutsideCtx->ulPrefBand = pstLastSyscfgSet->stUserSetBand.uUserSetGuBand.ulPrefBand;
    pstOutsideCtx->Band = pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand;
    pstOutsideCtx->ulQuickStartFlg = gstMmaValue.ulQuickStartFlg;
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    pstOutsideCtx->stEfustServiceCfg = gstMmaValue.stEfustServiceCfg;

    PS_MEM_CPY(pstOutsideCtx->aucImeiBcd, g_MmaNewValue.aucImeiBcd, TAF_PH_IMEI_LEN+1);
    pstAllRatOrder = TAF_MMA_GetRatPrioListAddr();

    MN_MMA_GetCpamGURatPrio(&enCpamPlmnPrio, pstAllRatOrder);
    MN_MMA_GetCpamGUAccessRat(&enAccessMode, pstAllRatOrder);

    /* 根据gstMmaValue.stRatPrioList给pstOutsideCtx->AccessMode和pstOutsideCtx->PlmnPrio赋值 */
    pstOutsideCtx->enAccessMode   = enAccessMode;
    pstOutsideCtx->PlmnPrio       = enCpamPlmnPrio + TAF_PLMN_PRIO_DIST_BTWN_CPAM_SYSCFG;

    pstOutsideCtx->MsClassType = gstMmaValue.stSetMsClass.MsClassType;
    pstOutsideCtx->enRoam = pstLastSyscfgSet->enRoam;
    pstOutsideCtx->ucRoamFeatureStatus = gstMmaValue.ucRoamFeatureStatus;

    pstOutsideCtx->stMeInfo = gstMmaValue.stMeInfo;

    pstOutsideCtx->stSimLockPlmnInfo = g_MmaNewValue.stSimLockPlmnInfo;
    pstOutsideCtx->stCardLockStatus = g_MmaNewValue.stCardLockStatus;
    pstOutsideCtx->stSimLockMaxTimes = g_MmaNewValue.stSimLockMaxTimes;

    PS_MEM_CPY(pstOutsideCtx->aucPwd, g_MmaNewValue.aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX+1);
    pstOutsideCtx->usSimMePersonalisationActFlag = g_MmaNewValue.usSimMePersonalisationActFlag;
    PS_MEM_CPY(pstOutsideCtx->aucSimPersonalisationStr, g_MmaNewValue.aucSimPersonalisationStr, TAF_MAX_IMSI_LEN+1);

    /* version 1 part variable */
    PS_MEM_CPY(&pstOutsideCtx->gstMmaBandCapa,
               TAF_MMA_GetUeSupportBandAddr(),
               sizeof(TAF_MMA_UE_BAND_CAPA_ST));

    pstOutsideCtx->ulVersion = 1;

    pSndMsgCB->ulReceiverPid = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_MMA_FIXED_PART_CONTEXT_ST) + 4;
    pSndMsgCB->usMsgID       = EVT_NAS_MMA_FIXED_PART_CONTEXT;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_MMA, pSndMsgCB);

    return;
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

/*****************************************************************************
 函 数 名  : MMA_OpPinSuccess
 功能描述  : 操作PIN是否成功
 输入参数  : TAF_PH_PIN_CNF_STRU *pstPinCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月14日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2007年02月09日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号A32D08488
*****************************************************************************/
VOS_UINT32 MMA_OpPin1Success(const TAF_PH_PIN_CNF_STRU *pstPinCnf)
{


    if ( (TAF_SIM_PIN != pstPinCnf->PinType) && (TAF_SIM_PUK != pstPinCnf->PinType) )
    {
        return VOS_FALSE;
    }

    if ( TAF_PH_OP_PIN_OK != pstPinCnf->OpPinResult )
    {
       return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMA_Pin1Noneed
 功能描述  : 判断是否需要PIN1
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月14日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MMA_Pin1Noneed()
{
    VOS_UINT32 ulRet;
    /*检查PIN状态*/
    ulRet = MMA_CheckPin1SatusSimple();
    /*PIN使能*/
    if ( MMA_NONEED_PIN1 != ulRet )
    {
        MMA_NORMAILLOG("MMA_Pin1Noneed():NORMAL:NEED PIN");
        return VOS_FALSE;
    }
    else
    {
        MMA_NORMAILLOG("MMA_Pin1Noneed():NORMAL:NO NEED PIN");
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : MMA_CheckUsimStatus
 功能描述  : 检查USIM状态是否启动,PIN状态是否可用
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年3月15日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MMA_CheckUsimStatus()
{
    VOS_UINT8   ucUsimStatus;
    VOS_UINT32  ulRet;

    ulRet = MMA_PhoneGetUsimStatus(&ucUsimStatus);
    if ( (MMA_SUCCESS != ulRet )
       ||((  (ucUsimStatus != MMA_USIM_ABSENT)
              &&(ucUsimStatus != MMA_USIM_PRESENT)
             )
         )
       )
    {
        /*USIM初始化未完成，启动定时器等待*/
        /*MMA_StartInitialTimer();*/
        MMA_WARNINGLOG("MMA_CheckUsimStatus():WARNING:USIM IS NOT READY");
        return MMA_ERROR;
    }
    else
    {
        if ( MMA_USIM_PRESENT == ucUsimStatus)
        {
            /*PIN使能*/
            ulRet = MMA_CheckPin1SatusSimple();
            if (MMA_PIN1_STATUS_FAIL == ulRet)
            {
                MMA_NORMAILLOG("MMA_CheckUsimStatus():NORMAL:PIN1 STATUS NOT READY");
                return MMA_ERROR;
            }
            else if ( MMA_NEED_PIN1 == ulRet )
            {
                MMA_NORMAILLOG("MMA_CheckUsimStatus():NORMAL:PIN1 NEED");
                return MMA_NORMAL;
            }
            else
            {
                MMA_NORMAILLOG("MMA_CheckUsimStatus():NORMAL:PIN1 NO NEED");
            }
        }
        return MMA_SUCCESS;
    }
}
/*****************************************************************************
 函 数 名  : MMA_GetCurMsClass
 功能描述  : 获取当前手机类型
 输出参数  : 无
 返 回 值  : TAF_PH_MS_CLASS_TYPE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年4月12日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
TAF_PH_MS_CLASS_TYPE MMA_GetCurMsClass()
{
    TAF_PH_MS_CLASS_TYPE                Result;
    VOS_UINT32                          ulDataLen;
    NAS_NVIM_MS_CLASS_STRU              stMsClass;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();
    ulDataLen = 0;

    if (  (TAF_PH_MS_CLASS_A == gstMmaValue.pg_StatusContext->ucModeService)
        &&(TAF_SDC_SYS_MODE_GSM     == enSysMode)
       )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        return TAF_PH_MS_CLASS_B;
    }

    if (TAF_PH_MS_CLASS_NULL == gstMmaValue.pg_StatusContext->ucModeService )
    {

        PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));

        (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulDataLen);

        if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass ,
                             &stMsClass,
                             ulDataLen))
        {
            MMA_WARNINGLOG("MMA_GetCurMsClass():WARNING:Read from NVIM MSClass Fail");
            Result = TAF_PH_MS_CLASS_A;/*TAF_PH_MS_CLASS_CC TAF_PH_MS_CLASS_CG*/
        }
        else
        {
            Result = stMsClass.ucMsClass;
        }
    }
    else
    {
        Result = gstMmaValue.pg_StatusContext->ucModeService;
    }
    return Result;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除MMA_TranslateIntIntoBitInRegStates */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */


/*****************************************************************************
 函 数 名  : MMA_ClearCurRegOp
 功能描述  : 清空注册状态结构中所有的OP项
 输入参数  : TAF_PH_REG_STATE_STRU  *pstCurRegSta
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年4月13日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_ClearCurRegOp(TAF_PH_REG_STATE_STRU  *pstCurRegSta)
{
    pstCurRegSta->OP_CsRegState = VOS_FALSE;
    pstCurRegSta->OP_PsRegState = VOS_FALSE;
    pstCurRegSta->OP_ucAct      = VOS_FALSE;
    pstCurRegSta->OP_Lac        = VOS_FALSE;
    pstCurRegSta->OP_Plmn       = VOS_FALSE;
    pstCurRegSta->OP_Rac        = VOS_FALSE;
    pstCurRegSta->OP_CellId     = VOS_FALSE;
    pstCurRegSta->OP_Spare      = VOS_FALSE;
    return;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */


/*****************************************************************************
 函 数 名  : MMA_PhoneGetUsimType
 功能描述  : 获取usim类型
 输入参数  : VOS_UINT8 *pucSimType
             MMA_USIM_TYPE_SIM       0
             MMA_USIM_TYPE_USIM      1
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年4月15日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
VOS_UINT32 MMA_PhoneGetUsimType( VOS_UINT8 *pucSimType )
{
    VOS_UINT8               ucUsimType;


    ucUsimType = USIMM_CARD_NOCARD;

#ifndef __PS_WIN32_RECUR__
    /*获取当前USIM状态*/
    /*当调用USIMAPI的值不为0,则表示有错误*/
    if  ( MMA_SUCCESS != MMA_GetUsimStatusFromUsim(VOS_NULL_PTR, &ucUsimType) )
    {
        *pucSimType = USIMM_CARD_NOCARD;

        MMA_WARNINGLOG("MMA_PhoneGetUsimType():WORNING:Invoke Taf_UsimmGetStatus fail.");
        return MMA_ERROR;
    }
    if ( USIMM_CARD_SIM == ucUsimType )
    {
        *pucSimType = MMA_USIM_TYPE_SIM;
    }
    else
    {
        *pucSimType = MMA_USIM_TYPE_USIM;
    }

    g_MmaNewValue.ucSimType = *pucSimType;

#else
    *pucSimType = g_MmaNewValue.ucSimType;

#endif

    return MMA_SUCCESS;
}


/*****************************************************************************
 函 数 名  : MMA_StopInternalTimer
 功能描述  : 停止内部定时器,复位内部定时器全局变量
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年6月6日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  3.日    期   : 2013年07月15日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目
*****************************************************************************/
VOS_VOID MMA_StopInternalTimer()
{
    VOS_UINT32 ulRet;
    if ( gstMmaInternalTimer.stTimer.ucTimerStatus != MMA_TIMER_RUN )
    {
        MMA_WARNINGLOG("MMA_StopInternalTimer():WARNING:INTERNAL TIMER IS NOT RUNNING");
    }


    ulRet = NAS_StopRelTimer(WUEPS_PID_MMA, MMA_INTERNAL_TIMER_ID,
                            &(gstMmaInternalTimer.stTimer.MmaHTimer));


    if ( VOS_OK != ulRet )
    {
        MMA_WARNINGLOG("MMA_StopInternalTimer():WARNING:Nas_StopRelTimer failed");
    }
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
    TAF_MMA_InitInternalTimer();
    /* Modified by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */
    return;
}


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


/*****************************************************************************
 函 数 名  : MMA_TurnOffForFlightMode
 功能描述  : 飞行模式中，关掉不用组件，以降低功耗
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年07月19日
    作    者   : sunshaohua
    修改内容   : 新生成函数
  2.日    期   : 2010年11月13日
    作    者   : z40661
    修改内容   : DTS2012111305323
  3.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目(删除SHPA_DeactivateHw函数)

  4.日    期   : 2013年10月29日
    作    者   : z00234330
    修改内容   : 低功耗接口合入,dts2013102911530
*****************************************************************************/
VOS_VOID MMA_TurnOffForFlightMode( VOS_VOID )
{
    /*Make DSP into Halt mode, and close DSP PLL, BBP PLL, power off BBP, RF */

    OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMA));

    TAF_MMA_SndDrxTimerInfo(VOS_TRUE);
    return;
}


/*****************************************************************************
 函 数 名  : MMA_TurnOnForFlightMode
 功能描述  : 离开飞行模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年07月19日
    作    者   : sunshaohua
    修改内容   : 新生成函数

  2.日    期   : 2012年4月24日
    作    者   : z40661
    修改内容   : for V7R1 Lower Power
  3.日    期   : 2013年3月25日
    作    者   : z60575
    修改内容   : DTS2013032501170，低功耗合入
  4.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目底软接口修改
  5.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_VOID MMA_TurnOnForFlightMode()
{
    /* 禁止底层睡眠 */
    /* V9R1/V3R3上NAS不再投PS票，删除LTE特性宏控制 */
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-13, begin */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*MMA_TurnOnForFlightMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK\n");
    }
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-13, end */
    /* Modidied by z60575 for V9R1 LowPower, 2013-3-7, end */
    return;
}
/*****************************************************************************
 函 数 名  : MN_PH_IsUsingPlmnSel
 功能描述  : 当前UPlmn是否PlmnSel,该函数用于UPLMN查询显示
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月11日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  3.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口

*****************************************************************************/
VOS_BOOL MN_PH_IsUsingPlmnSel(VOS_VOID)
{
    VOS_BOOL                            bPlmnSelFlg;
    VOS_UINT8                           ucSimType;

    bPlmnSelFlg = VOS_FALSE;
    ucSimType   = MMA_USIM_TYPE_USIM;

    /*User controlled PLMN Selector with Access Technology*/
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE
                    == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_UPLMN_SEL_WACT))
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */
    {
        (VOS_VOID)MMA_PhoneGetUsimType(&ucSimType);

        if (MMA_USIM_TYPE_SIM == ucSimType)
        {
            /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
            if (PS_USIM_SERVICE_AVAILIABLE
                        == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_SELECTOR))
            /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

            {
                bPlmnSelFlg = VOS_TRUE;
            }
        }

    }

    return bPlmnSelFlg;

}




/*****************************************************************************
 函 数 名  : MN_MMA_FillUPlmnFile
 功能描述  : 按USIM卡格式填充优先级列表文件内容
 输入参数  : VOS_UINT16                  usUpdateFile
             VOS_UINT8                  *pucEfFile
             TAF_USER_PLMN_LIST_STRU    *pstUPlmnInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月3日
    作    者   : sunxibo
    修改内容   : 新生成函数
  2.日    期    : 2013年11月26日
    作    者    : s00190137
    修改内容    : 将最大支持设置的OPLMN扩展到256个
*****************************************************************************/
VOS_VOID MN_MMA_FillUPlmnFile(
    VOS_UINT16                  usUpdateFile,
    VOS_UINT8                  *pucEfFile,
    TAF_USER_PLMN_LIST_STRU    *pstUPlmnInfo
)
{
    VOS_UINT8  ucRecordLen;
    VOS_UINT16 i;
    VOS_UINT16 usRatMode;

    if (USIMM_GSM_EFPLMNSEL_ID == usUpdateFile)
    {
        ucRecordLen = 3;
    }
    else
    {
        ucRecordLen = 5;
    }

    for (i = 0; i < pstUPlmnInfo->usPlmnNum; i++)
    {
        pucEfFile[i*ucRecordLen]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mcc >> 4));
        pucEfFile[i*ucRecordLen] <<= 4;
        pucEfFile[i*ucRecordLen] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mcc >> 8));

        pucEfFile[(i*ucRecordLen)+1]  = (VOS_UINT8)(0x0f & pstUPlmnInfo->Plmn[i].Mcc);
        if (0xF0 == (0xf0 & (pstUPlmnInfo->Plmn[i].Mnc >>4)))
        {
            pucEfFile[(i*ucRecordLen)+1] |= (VOS_UINT8)(0xf0 & (pstUPlmnInfo->Plmn[i].Mnc >>4));

            pucEfFile[(i*ucRecordLen)+2]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc));
            pucEfFile[(i*ucRecordLen)+2] <<= 4;
            pucEfFile[(i*ucRecordLen)+2] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc >>4));
        }
        else
        {
            pucEfFile[(i*ucRecordLen)+1] |= (VOS_UINT8)(0xf0 & (pstUPlmnInfo->Plmn[i].Mnc <<4));

            pucEfFile[(i*ucRecordLen)+2]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc >>4));
            pucEfFile[(i*ucRecordLen)+2] <<= 4;
            pucEfFile[(i*ucRecordLen)+2] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc >>8));
        }

        if (5 == ucRecordLen)
        {
            usRatMode = pstUPlmnInfo->PlmnRat[i];
            pucEfFile[(i*ucRecordLen)+3] = (VOS_UINT8)(usRatMode >> 8);
            pucEfFile[(i*ucRecordLen)+4] = (VOS_UINT8)(usRatMode & 0xFF);
        }
    }

    return;
}



/*****************************************************************************
 函 数 名  : MMA_GetProductionVersion
 功能描述  : 得到产品信息
 输入参数  : 保存信息的地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年1月13日
    作    者   : 孙少华
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MMA_GetProductionVersion(VOS_CHAR *pcDest)
{
    (VOS_VOID)VOS_StrNCpy(pcDest, (VOS_CHAR *)gstMmaValue.stMeInfo.SoftVersion.aucRevisionId,
        TAF_MAX_REVISION_ID_LEN+1);
}

/*****************************************************************************
 函 数 名  : MMA_GetProductionID
 功能描述  : 得到产品ID信息
 输入参数  : 保存信息的地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月23日
    作    者   : 黎客来 l00130025
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID Taf_GetProductionID(VOS_CHAR *pcDest)
{
    (VOS_VOID)VOS_StrNCpy(pcDest, (VOS_CHAR *)gstMmaValue.stMeInfo.ModelId.aucModelId,
        TAF_MAX_MODEL_ID_LEN+1);
}

/*****************************************************************************
 函 数 名  : MMA_WriteVersion
 功能描述  : 将PS版本信息注册到底软
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年1月13日
    作    者   : 孙少华
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MMA_WriteVersion(VOS_VOID)
{
    VOS_UINT32                 ulRslt;
    VOS_CHAR                   acVersionBuffer[VER_MAX_LENGTH]  = {0};

    (VOS_VOID)VOS_StrNCpy(acVersionBuffer, PROTOCOL_STACK_VERSION, VER_MAX_LENGTH);

    ulRslt = (VOS_UINT32)mdrv_ver_memberctrl((signed char *)acVersionBuffer,
                    VER_MAX_LENGTH, VER_PS, VERIONWRITEMODE); /* 写入协议栈版本信息 */
    if( VOS_OK != ulRslt )
    {
        MMA_WARNINGLOG("MMA_WriteVersion():WARNING:Write PS Version Info fail.");
    }
}


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
/* 函数WuepsMmaPidInit移动位置 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, end */


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, begin */
/* 函数Mma_TimeOutProc删除 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, end */


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
/* 删除Mma_MsgProc函数，移到新文件中 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, end */

/* 删除 MMA_UsimAccessCnfMsgProc接口函数，因为 PS_USIM_GENERIC_ACCESS_CNF 不会上报 MMA 模块处理 */

/*****************************************************************************
 函 数 名  : MMA_USIMMaxRecordNumCnfProc
 功能描述  : MMA最大记录号回复处理
 输入参数  : USIMM_QUERYFILE_CNF_STRU * pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年06月03日
    作    者   : 梁金广
    修改内容   : 新生成函数
  2.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  3.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
  4.日    期   : 2015年2月26日
    作    者   : b00269685
    修改内容   : at&t支持eons修改
*****************************************************************************/
VOS_UINT32 MMA_USIMMaxRecordNumCnfProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{



    MMA_StopInternalTimer();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MMA_UsimPINOperateMsgProc
 功能描述  : MMA PIN处理回复处理
 输入参数  : USIMM_PINHANDLE_CNF_STRU * pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年06月03日
    作    者   : 梁金广
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  4.日    期   : 2014年07月07日
    作    者   : z00234330
    修改内容   : coverity清理
  5.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/

VOS_UINT32 MMA_UsimPINOperateMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    USIMM_PINHANDLE_CNF_STRU           *pstUsimPinMsg;
    TAF_PH_PIN_CNF_STRU                 stPinTmp;

    pstUsimPinMsg = (USIMM_PINHANDLE_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stPinTmp, 0x00, sizeof(stPinTmp));

    stPinTmp.CmdType      = (VOS_UINT8)pstUsimPinMsg->enCmdType;
    stPinTmp.OpPinResult  = (VOS_UINT8)pstUsimPinMsg->stCmdResult.ulResult;
    stPinTmp.PinType      = (VOS_UINT8)pstUsimPinMsg->enPinType;
    (VOS_VOID)NAS_USIMMAPI_GetPinRemainTime((USIMM_PIN_REMAIN_STRU *)(&(stPinTmp.RemainTime)));
    MMA_PinDataReport((const TAF_PH_PIN_CNF_STRU *)&(stPinTmp));

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/* MMA_UsimGetPNNFileRspForCPNN */
/* MMA_UsimGetOPLFileRspForCPNN */
/* MMA_ProcRecRange */
/* MMA_UsimGetSimSpnInfo */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
/* TAF_MMA_UsimGetFileRspPnnMsgProc */



/* MMA_UsimGetFileRspMsgProc */


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-12, end */

/* TAF_MMA_UsimRefreshIndAllFileChangedMsgProc */
/* MMA_USIMRefreshFileProc */
/* TAF_MMA_UsimRefreshIndFileListChangedMsgProc */
/* MMA_USIMRefreshFileProc */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

/*****************************************************************************
 函 数 名  : MMA_ProcHotInOutUsimStatusInd
 功能描述  : MMA接收卡状态指示消息后的处理
 输入参数  : USIMM_HOTINOUT_IND_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年07月09日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012061209698,增加热插拔保护以及可维可测信息
  3.日    期   : 2013年06月05日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  4.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*****************************************************************************/
VOS_UINT32 MMA_ProcHotInOutUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCardStatus;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */
    VOS_UINT8                           ucSimLockStatus;
    USIMM_HOTINOUT_IND_STRU            *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_HOTINOUT_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 获取锁卡状态 */
        if (MMA_SIM_IS_LOCK == MMA_GetCsimMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }
    else
#endif
    {
        /* 获取锁卡状态 */
        if (MMA_SIM_IS_LOCK == MMA_GetMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

    ucCardStatus                        = USIMM_CARD_SERVIC_BUTT;

    /* 热拨出 */
    if (SIM_CARD_OUT == pstUsimMsg->ulCardInOutStatus)
    {
        /* USIM卡热拔出卡状态上报255 */
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */
        TAF_MMA_SndAtIccStatusInd(TAF_PH_USIM_NON, ucSimLockStatus);
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

        /* 将USIM热拔出的标识置为TRUE */
        g_ucUsimHotOutFlag = VOS_TRUE;

        g_ucUsimHotInFlag  = VOS_FALSE;

        /* 收到热拔出事件，计数加1 */
        g_ulUsimHotOutCount++;
    }
    /* 热插入 */
    else if (SIM_CARD_IN == pstUsimMsg->ulCardInOutStatus)
    {
        g_ucUsimHotOutFlag = VOS_FALSE;

        (VOS_VOID)NAS_USIMMAPI_GetCardType(&ucCardStatus, VOS_NULL_PTR);

        /* 只有在卡被拔出的情况，收到卡插入才有效 */
        if (USIMM_CARD_SERVIC_ABSENT == ucCardStatus)
        {
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */
            TAF_MMA_SndAtIccStatusInd(TAF_PH_USIM_STATUS_UNAVAIL, ucSimLockStatus);
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

            /* 将USIM热插入的标识置为TRUE */
            g_ucUsimHotInFlag  = VOS_TRUE;
        }

        /* 收到热插入事件，计数加1 */
        g_ulUsimHotInCount++;
    }
    else
    {
        /* for pclint */
    }

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
/*****************************************************************************
 函 数 名  : MMA_UsimRestrictedAccessCnfMsgProc
 功能描述  : MMA上报通用的卡操作命令的结果
 输入参数  : TAF_USIM_RESTRICTED_ACCESS_CNF_STRU* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年03月03日
    作    者   : h59254
    修改内容   : 新生成函数
  2.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  4.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 MMA_UsimRestrictedAccessCnfMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent;

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    USIMM_RACCESS_CNF_STRU             *pMsg;

    pMsg = (USIMM_RACCESS_CNF_STRU *)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_UsimRestrictedAccessCnfMsgProc:ERROR:ALLOC MEMORY FAIL.");

        /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
        return VOS_TRUE;
        /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if ((MMA_SUCCESS == (pMsg->stCmdResult.ulResult))
     && (USIMM_SW_SENDCMD_ERROR != pMsg->stCmdResult.ulErrorCode))
    {

        pstPhoneEvent->PhoneEvent = TAF_PH_EVT_RESTRICTED_ACCESS_CNF;
        pstPhoneEvent->OpId = 0;
        pstPhoneEvent->ClientId = (VOS_UINT16)pMsg->stCmdResult.ulSendPara;
        pstPhoneEvent->OP_UsimRestrictAccess = 1;
        pstPhoneEvent->RestrictedAccess.ucLen = (VOS_UINT8)pMsg->usLen;
        pstPhoneEvent->RestrictedAccess.ucSW1 = pMsg->ucSW1;
        pstPhoneEvent->RestrictedAccess.ucSW2 = pMsg->ucSW2;
        PS_MEM_CPY(pstPhoneEvent->RestrictedAccess.aucContent,
                  pMsg->aucContent,
                  pMsg->usLen);
    }
    else
    {
        pstPhoneEvent->PhoneEvent    = TAF_PH_EVT_ERR;
        pstPhoneEvent->ClientId      = (VOS_UINT16)pMsg->stCmdResult.ulSendPara;
        pstPhoneEvent->OP_PhoneError = 1;
        pstPhoneEvent->PhoneError    = TAF_ERR_SIM_FAIL;
    }

    /* 调用电话管理上报函数 */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}


/*****************************************************************************
 函 数 名  : MMA_UsimRestrictedAccessCommandProc
 功能描述  : MMA处理受限制卡操作命令
 输入参数  : *pucContent - 发给卡的命令内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年03月03日
    作    者   : h59254
    修改内容   : 新生成函数
  2.日    期   : 2011年10月19日
    作    者   : f00179208
    修改内容   : AT移植项目,CallBack的清理
  3.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 .
  4.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*****************************************************************************/
VOS_UINT32 MMA_UsimRestrictedAccessCommandProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent   = VOS_NULL_PTR;
    USIMM_RACCESS_REQ_STRU             *pstCommand      = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    pstCommand  = (USIMM_RACCESS_REQ_STRU *)pstRcvMsg->aucContent;
    usClientId  = pstRcvMsg->clientId;
    ucOpId      = pstRcvMsg->opId;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_UsimRestrictedAccessCommandProc:ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    ulRslt = NAS_USIMMAPI_RestrictedAccessReq(WUEPS_PID_MMA,
                                              usClientId,
                                              pstCommand);

    if (TAF_ERR_NO_ERROR != ulRslt)
    {

        pstPhoneEvent->OP_PhoneError      = 1;
        pstPhoneEvent->PhoneEvent         = TAF_PH_EVT_ERR;
        pstPhoneEvent->ClientId           = usClientId;
        pstPhoneEvent->OpId               = ucOpId;
        pstPhoneEvent->PhoneError         = TAF_ERR_SIM_BUSY;

        /* 调用电话管理上报函数 */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return VOS_TRUE;

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, begin */
/* MMA_TafMsgProc 函数删除 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-9, end */

/* END:   Added by liuyang id:48197, 2006/8/9   PN:优化MMA*/


/*****************************************************************************
 函 数 名  : MMA_PhoneGetIccId
 功能描述  : 获取uisimICCID内容
 输入参数  : VOS_UINT16           ClientId
             VOS_UINT8            OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年8月23日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数
  2.日    期  : 2012年12月26日
    作    者  : 张鹏 id:00214637
    修改内容  : USIM对外接口函数变更的处理 ，
                Client ID 到 PID的转换处理 ，入参封装成结构体。
  3.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID  MMA_PhoneGetIccId(VOS_UINT16           ClientId,
                            VOS_UINT8            OpId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));

    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_PhoneGetIccId():WARNING:USIM is not Ready!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_ICC_ID);
        return;
    }

    /*启动定时器*/
    if(MMA_SUCCESS != MMA_StartInternalTimer(1,
                                             MMA_GET_USIM_ICC_ID,
                                             ClientId,
                                             OpId))
    {
        MMA_WARNINGLOG("MMA_PhoneGetIccId():WARNING:Unknow Error!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_ICC_ID);
        return;
    }
    /*读卡*/
    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                    USIMM_UNLIMIT_AUTO,
                                    USIMM_ICCID_ID,
                                    0);

    if( USIMM_API_SUCCESS != NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA,
                                              0,
                                              &stGetFileInfo))
    {
        MMA_WARNINGLOG("MMA_PhoneGetIccId():WARNING:get File Error!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_ICC_ID);

        /*停止定时器*/
        MMA_StopInternalTimer();
        return;
    }
    gstMmaValue.stGetIccId.ClientId = ClientId;
    gstMmaValue.stGetIccId.OpId     = OpId;
    return;
}


/* MMA_GetUsimIccIdFileInd */

/*****************************************************************************
 函 数 名  : TAF_MMA_GetIccIdInfo
 功能描述  : 获取icc id信息
 输出参数  : 无
 返 回 值  : MMA_GET_ICC_ID_ST
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月16日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
MMA_GET_ICC_ID_ST *TAF_MMA_GetIccIdInfo(VOS_VOID)
{
    return &gstMmaValue.stGetIccId;
}

/* 移到TafMmaCtx.c中*/


/*****************************************************************************
 函 数 名  : MMA_GetUsimIccIdExpired
 功能描述  : 等待USIM上报结果超时
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年8月23日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_GetUsimIccIdExpired(VOS_VOID)
{
    /*获取ICCID操作失败*/
    MMA_WARNINGLOG("MMA_GetUsimIccIdExpired():WARNING:GET USIM ICC ID, Fail");

    MMA_ReportParaQueryError(gstMmaInternalTimer.ClientId,
                             gstMmaInternalTimer.OpId,
                             TAF_ERR_UNSPECIFIED_ERROR,
                             TAF_PH_ICC_ID);

    return;
}


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

/*VOS_VOID  Taf_GetSpnName(VOS_UINT8*  aucSpnName,VOS_UINT32 ulMaxLen)*/
/*TAF_UINT32  Taf_DefGetSPN(TAF_UINT8 ucSpnType, TAF_PH_USIM_SPN_STRU   *pstAtSPNRslt)*/



/*****************************************************************************
 函 数 名  : Taf_IsWBandSupported
 功能描述  : 判断某个W频段UE是否支持
 输入参数  : bandNo
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月26日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2012年06月13日
    作    者   : f62575
    修改内容   : DTS2012061303100，解决^FCHAN命令不支持UMTS BAND11问题

*****************************************************************************/
VOS_BOOL Taf_IsWBandSupported(VOS_UINT16 usBandNo)
{
    VOS_UINT16    usBandMask;

    /*目前只支持W只能设置支持到Band11*/
    /*lint -e701*/
    if ((TAF_DEVICE_AT_MAX_W_BAND_NUM < usBandNo)||(0 == usBandNo))

    {
        return VOS_FALSE;
    }
    /* W Rf support
    -------------------------------------------------------------------------------
          bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
                                                         bit11     bit10    bit9
    -------------------------------------------------------------------------------
    WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
            spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
   */
    usBandMask = (VOS_UINT16)(0x0001 << (usBandNo-1));
    /*lint +e701*/

    if (usBandMask & TAF_MMA_GetUeSupportBandAddr()->unWRFSptBand.ulBand)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}
/*****************************************************************************
 函 数 名  : TAF_SetPrefPlmnType
 功能描述  :
 输入参数  : MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
 输出参数  : NONE
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年8月19日
    作    者   : z40661
    修改内容   : 新增函数，增加 AT+CPLS 命令支持
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  3.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口

*****************************************************************************/
TAF_UINT32  TAF_SetPrefPlmnType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
)
{
    VOS_UINT32                          ulRet;

    if (enPrefPlmnType > MN_PH_PREF_PLMN_HPLMN)
    {
        return TAF_PARA_TYPE_NOT_SUPPORT;
    }

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    if (MN_PH_PREF_PLMN_UPLMN == enPrefPlmnType)
    {
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_UPLMN_SEL_WACT);

        if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulRet)
        {
            ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_SELECTOR);
        }
    }
    else if (MN_PH_PREF_PLMN_OPLMN == enPrefPlmnType)
    {
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_SEL_WACT);
    }
    else
    {
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_HPLMN_WACT);
    }
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */


    if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulRet)
    {
        return TAF_PARA_TYPE_NOT_SUPPORT;
    }

    return TAF_PARA_OK;
}

/*****************************************************************************
 函 数 名  : Taf_SyscfgBand2Str
 功能描述  : 将对应的频段转换为字符串
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月18日
    作    者   : l00130025
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID  Taf_SyscfgBand2Str(VOS_UINT32 band,TAF_CHAR* strBand)
{

    VOS_UINT32 i,ulLen;
    VOS_UINT32 ulBandStrLen = 0;
    TAF_CHAR* strSep = "/";

    ulBandStrLen = 0;
    ulLen = sizeof(gastMmaSyscfgBandStr)/sizeof(gastMmaSyscfgBandStr[0]);

    MMA_INFOLOG1("Taf_SyscfgBand2Str:band = \r\n", (VOS_INT)band);

    for (i = 0; i < ulLen; i++)
    {
        if(0 != (band & gastMmaSyscfgBandStr[i].BandMask))
        {
            (VOS_VOID)VOS_StrCpy(strBand + ulBandStrLen, gastMmaSyscfgBandStr[i].BandStr);

            ulBandStrLen += VOS_StrLen(gastMmaSyscfgBandStr[i].BandStr);

            (VOS_VOID)VOS_StrCpy(strBand + ulBandStrLen, strSep);

            ulBandStrLen += VOS_StrLen(strSep);

            if(ulBandStrLen >= (TAF_PH_SYSCFG_GROUP_BAND_LEN/2))
            {
                MMA_ERRORLOG("Taf_SyscfgBand2Str(): ERROR :strBand too long ");
                break;
            }
        }
    }

    if (ulBandStrLen > 0)
    {
        strBand[ulBandStrLen-1] = '\0';
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_GetSyscfgBandGroupStr
 功能描述  : 获取SYSCFG支持的频段组合
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月18日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2009-09-07
    作    者   : l00130025
    修改内容   : 问题单号: AT2D14224/AT2D14259,AT^SYSCFG按终端AT手册支持W900和W1700的设置
*****************************************************************************/

VOS_VOID  Taf_GetSyscfgBandGroupStr(TAF_PH_SYSCFG_BAND_STR* pstSysCfgBandStr)
{
    /*
    获取支持的频段项 gstMmaBandCapa.ulAllUeBand
    与Group1相与得到Band1,与Group2相与得到Band2,非空时再根据组合项来显示对应的Str
    */

    VOS_UINT32 bandGroup1,bandGroup2,bandAll,bandNeedTransferTo64Bit;
    TAF_CHAR*  BandStr1;
    TAF_CHAR*  BandStr2;

    TAF_CHAR* strSysCfgBandGroup = pstSysCfgBandStr->strSysCfgBandGroup;

    BandStr1 = (TAF_CHAR*)PS_MEM_ALLOC(WUEPS_PID_MMA, (TAF_PH_SYSCFG_GROUP_BAND_LEN/2));

    if (VOS_NULL_PTR == BandStr1)
    {
        return;
    }

    BandStr2 = (TAF_CHAR*)PS_MEM_ALLOC(WUEPS_PID_MMA, (TAF_PH_SYSCFG_GROUP_BAND_LEN/2));

    if (VOS_NULL_PTR == BandStr2)
    {
        PS_MEM_FREE(WUEPS_PID_MMA,BandStr1);
        return;
    }

    PS_MEM_SET(BandStr1,0,(TAF_PH_SYSCFG_GROUP_BAND_LEN/2));
    PS_MEM_SET(BandStr2,0,(TAF_PH_SYSCFG_GROUP_BAND_LEN/2));


    bandAll = TAF_PH_BAND_ANY;
    bandGroup1 = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand & TAF_PH_BAND_GROUP1_FOR_SYSCFG;
    bandGroup2 = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand & TAF_PH_BAND_GROUP2_FOR_SYSCFG;
    bandNeedTransferTo64Bit = bandGroup1 & TAF_PH_BAND_NEED_CHANGE_TO_64BIT;


    if ((0 == bandGroup1)&&(0 == bandGroup2))
    {
        (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"All bands\"))",bandAll);
    }
    else if ((0 != bandGroup1) && (0 != bandGroup2))
    {
        Taf_SyscfgBand2Str(bandGroup1,BandStr1);
        Taf_SyscfgBand2Str(bandGroup2,BandStr2);
        if (0 != bandNeedTransferTo64Bit )
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x%08x,\"%s\"),(%x,\"%s\"),(%x,\"All bands\"))",
                        bandNeedTransferTo64Bit,(bandGroup1 & ~bandNeedTransferTo64Bit),BandStr1,bandGroup2,BandStr2,bandAll);
        }
        else
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"%s\"),(%x,\"%s\"),(%x,\"All bands\"))",
                        bandGroup1,BandStr1,bandGroup2,BandStr2,bandAll);
        }
    }
    else if  (0 != bandGroup1)
    {
        Taf_SyscfgBand2Str(bandGroup1,BandStr1);
        if (0 != bandNeedTransferTo64Bit )
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x%08x,\"%s\"),(%x,\"All bands\"))",
                                     bandNeedTransferTo64Bit,(bandGroup1 & ~bandNeedTransferTo64Bit),BandStr1,bandAll);
        }
        else
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"%s\"),(%x,\"All bands\"))",
                                     bandGroup1 ,BandStr1,bandAll);
        }

    }
    else
    {
        Taf_SyscfgBand2Str(bandGroup2,BandStr2);
        (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"%s\"),(%x,\"All bands\"))",
                                          bandGroup2,BandStr2,bandAll);

    }

    PS_MEM_FREE(WUEPS_PID_MMA,BandStr1);
    PS_MEM_FREE(WUEPS_PID_MMA,BandStr2);

    return;
}

/* MN_MMA_GetSyscfgExLteBandGroupStr */


/*****************************************************************************
 函 数 名  : TAF_TimeCmp
 功能描述  : ulEndTick 和 ulStartTick 间的时间差小于ulCmpSec 返回 TRUE,
             否则返回FALSE
 输入参数  : VOS_UINT32                          ulStartTick
             VOS_UINT32                          ulEndTick
             VOS_UINT32                          ulCmpSec
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月14日
    作    者   : lijun 00171473
    修改内容   : 新生成函数
  2.日    期   : 2013年03月07日
    作    者   : f00179208
    修改内容   : timer由递减转换为递增
*****************************************************************************/
VOS_UINT32  TAF_TimeCmp(
    VOS_UINT32                          ulStartTick,
    VOS_UINT32                          ulEndTick,
    VOS_UINT32                          ulCmpSec
)
{
    VOS_UINT32                          ulCostSec;

    /* 时间戳是由0开始递增，所以当前的时间戳应该大于上次。另在时间戳
       到0xFFFFFFFF时会重置到0，所以else分支处理这种情况 */
    if (ulEndTick >= ulStartTick)
    {
        ulCostSec = (ulEndTick - ulStartTick)/(32*1024);
    }
    else
    {
        /*lint -e961*/
        ulCostSec = (0xFFFFFFFF - ulStartTick + ulEndTick)/(32*1024);
        /*lint +e961*/
    }

    if ( ulCostSec <= ulCmpSec )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

/*****************************************************************************
 函 数 名  : Taf_QueryCSNR
 功能描述  :
 输入参数  : VOS_INT16        *psCpichRscp
             VOS_INT16 *psCpichEcNo
 输出参数  :
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年11月14日
    作    者   : ouyang fei 00132663
    修改内容   : 新增函数，问题单AT2D07071，增加 GAS对AT^CSNR命令的支持。
  2.日    期   : 2009年05月23日
    作    者   : ouyang fei 00132663
    修改内容   : 问题单AT2D12067，G模下AT^CSNR?返回值超过实际支持范围。
  3.日    期   : 2009年09月05日
    作    者   : ouyang fei 00132663
    修改内容   : 问题单AT2D14269，G模下AT^CSNR?返回值永远为最小值。
  2.日    期   : 2010年12月14日
    作    者   : lijun 00171473
    修改内容   : DTS2010121101304, 解决列表搜完成后总是出现几秒圈外的问题

  4.日    期   : 2012年2月18日
    作    者   : z40661
    修改内容   : GTL分支时，不能直接调用WAS的接口

  5.日    期   : 2012年7月14日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseI:在FEATURE_UE_MODE_TDS和FEATURE_UE_MODE_W特性
                  宏都打开的时候，需要确认当前的UTRAN模式为WCDMA时候，调用WRR提供
                  的API函数。
  6.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  7.日    期   : 2014年11月28日
    作    者   : w00281933
    修改内容   : 服务状态显示优化Phase I
  8.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
TAF_UINT32  Taf_QueryCSNR(TAF_INT16 *psCpichRscp,TAF_INT16 *psCpichEcNo)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_UINT32                          ulRslt;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRadioMode;        /*手机接入模式查询*/
    static VOS_UINT32                   ulFirstInvalidTick = 0;
    VOS_UINT32                          ulTmpTick;

    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrentUtranMode;
    WAS_QueryCSNR                       pfWasQueryCsnr;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == TAF_SDC_GetAppServiceStatus())
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        /*获取当前网络模式*/
        enRadioMode = TAF_SDC_GetAppSysMode();
        if (TAF_SDC_SYS_MODE_WCDMA == enRadioMode)
        {/* WCDMA */
            /* Added by z40661 for GTL Project，2012-02-18,  Begin*/

            /* 取得当前的UTRAN模式 */
            enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

            if ( NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrentUtranMode )
            {
                pfWasQueryCsnr = TAF_GetWasQueryCsnrAddr();

                if (VOS_NULL_PTR == pfWasQueryCsnr)
                {
                    *psCpichRscp = RRC_NAS_MEASURE_INVALID_VALUE;
                    *psCpichEcNo = MMA_RSCP_MIN;
                    ulRslt = TAF_FAILURE;
                }
                else
                {
                    ulRslt = pfWasQueryCsnr(psCpichRscp,psCpichEcNo);
                }
            }
            else
            {
                *psCpichRscp = RRC_NAS_MEASURE_INVALID_VALUE;
                *psCpichEcNo = MMA_RSCP_MIN;
                ulRslt = TAF_FAILURE;
            }
            /* Added by z40661 for GTL Project，2012-02-18,  end*/

            /* 针对用户发起列表搜后，UE在回RPLMN过程中查询RSCP，此时WAS由于正在搜网，
               返回了一个无效值，导致后台显示无信号，特做如下特殊处理:
               如果UE处于正常服务状态，但WAS返回的信号为无效值，两秒内再查询均使用上次
               的有效值。超过两秒仍然返回无效值，则认为可能搜网异常，返回最小值 */

            if (RRC_NAS_MEASURE_INVALID_VALUE == *psCpichRscp)
            {
                ulTmpTick = VOS_GetSlice();

                if ( 0 == ulFirstInvalidTick )
                {
                    /* 记录刚开始无效信号的 tick, 返回保存的信号值 */
                    ulFirstInvalidTick = ulTmpTick;
                    *psCpichRscp = g_sLastRscp;
                    *psCpichEcNo = g_sLastEcNo;
                }
                else if( TAF_TimeCmp(ulFirstInvalidTick, ulTmpTick, MMA_INVALID_RSCP_SEC_MAX ) )
                {
                    /* 2 秒内出现无效信号, 返回保存的信号值 */
                    *psCpichRscp = g_sLastRscp;
                    *psCpichEcNo = g_sLastEcNo;
                }
                else
                {
                    /* 超过2 秒, 返回最小值 */
                    *psCpichRscp = MMA_RSCP_MIN;
                    *psCpichEcNo = MMA_ECNO_MIN;
                }
            }
            else
            {
                /* 正常值则保存 */
                g_sLastRscp = *psCpichRscp;
                g_sLastEcNo = *psCpichEcNo;
                ulFirstInvalidTick = 0;
            }
        }
        else
        {/* GSM */
            *psCpichRscp = MMA_RSCP_MIN;
            *psCpichEcNo = MMA_ECNO_MIN;

            ulRslt = TAF_SUCCESS;
        }
    }
    else
    {   /* 非正常服务状态 */
        *psCpichRscp = MMA_RSCP_MIN;
        *psCpichEcNo = MMA_ECNO_MIN;

        ulRslt = TAF_SUCCESS;

        /* 无服务的时候初始化其为最小值 */
        g_sLastRscp = MMA_RSCP_MIN;
        g_sLastEcNo = MMA_ECNO_MIN;
    }


    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    if(*psCpichRscp > MMA_RSCP_MAX)
    {
        *psCpichRscp = MMA_RSCP_MAX;
    }

    if(*psCpichRscp < MMA_RSCP_MIN)
    {
        *psCpichRscp = MMA_RSCP_MIN;
    }

    if(*psCpichEcNo > MMA_ECNO_MAX)
    {
        *psCpichEcNo = MMA_ECNO_MAX;
    }

    if(*psCpichEcNo < MMA_ECNO_MIN)
    {
        *psCpichEcNo = MMA_ECNO_MIN;
    }

    return ulRslt;
}



/* Taf_DefGetCardMode */

/*****************************************************************************
 函 数 名  : TAF_GetUsimStatus
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年07月28日
    作    者   : ouyang fei 00132663
    修改内容   : 新增函数，问题单AT2D13330，获取卡 PIN状态

*****************************************************************************/
TAF_UINT32 TAF_GetUsimStatus(TAF_VOID)
{
    return MMA_CheckUsimStatusForPlmnSel();
}


/*****************************************************************************
 函 数 名  : MMA_GetUsimStatusFromUsim
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年03月02日
    作    者   : x00115505
    修改内容   : 新增函数
  2.日    期   : 2013年06月05日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
  3.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : DTS2013071900570:SVLTE特性开启时候，MODEM1解pin后，MODEM0收到
                卡状态为AVAILABLE时候，没有发起重启。原因在于:
                当前解PIN码之前，SDC中维护的卡状态为TAF_SDC_USIM_STATUS_VALID，
                MODEM在收到解PIN的RSP消息时候，才会将SDC的卡状态重新设置为TAF_SDC_USIM_STATUS_UNVALID
                ，这样再收到USIM上报的卡状态为AVAILABLE时候，会发起重启。
                修改为SDC存储SIM卡的原始状态，MODEM在收到解PIN的RSP消息时候,
                不需重新设置SIM状态为TAF_SDC_USIM_STATUS_UNVALID。MODEM的重启
                由SIM卡状态的变迁来决定。如:卡状态由SIM_PIN--->AVAIALBLE,则触发
                重启动。
                修改函数返回值。
   4.日    期   : 2013年9月27日
     作    者   : w00167002
     修改内容   : DTS2013092100149:删除C核TASKDELAY处理，在V9低功耗时，会导致
                   TASKDELAY后未被唤醒，导致AT消息没有回复。
                   修改:NAS_USIMMAPI_GetCardIMSI获取不到IMSI时候，默认为卡不存在。
*****************************************************************************/
VOS_UINT32 MMA_GetUsimStatusFromUsim(VOS_UINT8 *pucCardStatus,
                                                   VOS_UINT8 *pucCardType)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucImsi[9] = {0};
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    ulResult = NAS_USIMMAPI_GetCardType(pucCardStatus, pucCardType) ;

    if ((VOS_NULL_PTR == pucCardStatus)
     || (USIMM_CARD_SERVIC_AVAILABLE != *pucCardStatus))
    {
        return ulResult;
    }


    /* 跟靳妮确认，如果当前卡状态为USIMM_CARD_SERVIC_AVAILABLE，则一定读完了IMSI卡文件 */
    ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(aucImsi);

    if (USIMM_API_SUCCESS != ulGetCardImsiRslt)
    {
        if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录获取卡IMSI异常log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, aucImsi);
#endif
        }

        return ulResult;
    }

    /* 如果IMSI长度非法，则按照无卡处理，注TAF_SDC_MAX_IMSI_LEN长度是包含长度信息的 */
    if (aucImsi[0] >= TAF_SDC_MAX_IMSI_LEN)
    {
        *pucCardStatus = USIMM_CARD_SERVIC_ABSENT;
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : MMA_CheckUsimStatusForPlmnSel
 功能描述  :
 输入参数  :
 输出参数  : TAF_UINT8    pucCardMode
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月6日
    作    者   : l00130025
    修改内容   : 新增函数，问题单AT2D10720/AT2D10806，增加搜网时usim状态的检查
  2.日    期   : 2010年11月16日
    作    者   : 欧阳飞
    修改内容   : DTS2010111503638，如果卡不存在，上报错误卡不存在而不是SIM
                 FAILURE
*****************************************************************************/
VOS_UINT8 MMA_CheckUsimStatusForPlmnSel()
{
    VOS_UINT8                           ucSimStatus = MMA_USIM_ABSENT;
    VOS_UINT8                           ucError    = TAF_ERR_NO_ERROR;

    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
    if ( MMA_USIM_PRESENT == ucSimStatus )
    {
        /*需要输入PIN码*/
        switch ( MMA_CheckPin1SatusSimple() )
        {
            case MMA_ENABLE_PIN1_NONEED:
            case MMA_NONEED_PIN1:
                ucError = TAF_ERR_NO_ERROR;
                break;
            case MMA_NEED_PIN1:
                ucError = TAF_ERR_NEED_PIN1;
                break;
            case MMA_NEED_PUK1:
                ucError = TAF_ERR_NEED_PUK1;
                break;
            case MMA_PIN1_STATUS_FAIL:
                ucError = TAF_ERR_SIM_FAIL;
                break;
            default:
                ucError = TAF_ERR_UNSPECIFIED_ERROR;
                MMA_WARNINGLOG("MMA_CheckUsimStatusForPlmnSel():WARNING:MEET MYSTERIOUS THING!");
                break;
        }
    }
    else
    {
        ucError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;
    }
    return ucError;
}

/*****************************************************************************
 函 数 名  : MMA_GetCurrentPhoneMode
 功能描述  : 提供给电源管理，获得当前的电话模式，在进入FTM模式时不能进行电源管理
 输入参数  :
 输出参数  : NA
 返 回 值  : TAF_UINT8    PhMode 电话模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年5月4日
    作    者   : l65478
    修改内容   : created for AT2D11662
  2.日    期   : 2011年04月14日
    作    者   : h44270
    修改内容   : 根据问题单号,DTS2011041106101,操作模式设置时间不正确，产线查询有误
*****************************************************************************/
VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    return TAF_SDC_GetCurPhoneMode();
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
}
/*****************************************************************************
 函 数 名  : MMA_ClearEplmnFromNV
 功能描述  : 清除EPLMN
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年08月01日
    作    者   : l65478
    修改内容   : 新生成函数

  2.日    期   : 2013年7月8日
    作    者   : w00167002
    修改内容   : DTS2013070506409:没有清除EPLMN
*****************************************************************************/
VOS_VOID MMA_ClearEplmnFromNV(VOS_VOID)
{
    NVIM_EQUIVALENT_PLMN_LIST_STRU *pEquivPlmn;
    VOS_UINT16    usTemLen;

    usTemLen = sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU);
    pEquivPlmn = (NVIM_EQUIVALENT_PLMN_LIST_STRU *)MMC_MEM_ALLOC(
                            VOS_MEMPOOL_INDEX_NAS,
                            usTemLen,
                            WUEPS_MEM_NO_WAIT);                             /* 申请内存                                 */
    if (VOS_NULL_PTR == pEquivPlmn)
    {
        TAF_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "MMC_ClearEplmn:ERROR: Memory Alloc Error");
        return;                                                             /* 返回                                     */
    }


    if (NV_OK == NV_Read(en_NV_Item_EquivalentPlmn, pEquivPlmn, usTemLen))
    {
        if ( 0 == pEquivPlmn->ucCount )
        {
            MMC_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pEquivPlmn);
            MMA_INFOLOG("MMA_ClearEplmnFromNV():The content to write is same as NV's");

            return;
        }
    }


    /* 初始化EPLMN的个数 */
    PS_MEM_SET(pEquivPlmn, 0, usTemLen);

    if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                          pEquivPlmn,
                          sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
    {
        TAF_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "MMC_ClearEplmn:WARNING: en_NV_Item_EquivalentPlmn Error");
    }
    MMC_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pEquivPlmn);

    return;
}

/*****************************************************************************
 函 数 名  : Taf_GetSysInfoForSTK
 功能描述  :
 输入参数  :
 输出参数  : TAF_UINT8    pucCardMode
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月12日
    作    者   : h44270
    修改内容   : 新增函数,对stk功能的支持
  2.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,STK中没有对应DeepSleep状态的处理，需要修改为NO_SERVICE
  3.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  5.日    期   : 2013年8月01日
    作    者   : l00208543
    修改内容   : V9R1 STK升级,把区域限制服务转换为限制服务，全局变量的服务状态只保持三种，NO SERVICE & NORMAL SERVICE & LIMITED SERVICE
*****************************************************************************/
VOS_VOID  Taf_GetSysInfoForSTK(TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU *pstSysInfo)
{
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    pstSysInfo->stPlmn = *(TAF_SDC_GetCurrCampPlmnId());

    pstSysInfo->ulCellId            = TAF_SDC_GetCurrCampCellId();

    pstSysInfo->enServiceStatus     = TAF_MMA_GetSrvTypeForStk();
    pstSysInfo->enSysMode = TAF_SDC_GetSysMode();
    pstSysInfo->usLac     = TAF_SDC_GetCurrCampLac();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    return;
}


/* Deleted by l00208543 for V9R1 STK升级, 2013-7-12, begin */
/* Deleted by l00208543 for V9R1 STK升级, 2013-7-12, end */

/*****************************************************************************
 函 数 名  : TAF_IsNormalSrvStatus
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : TAF_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月24日
    作    者   : h44270
    修改内容   : 新增函数,对CPN功能的支持
  2.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
TAF_BOOL TAF_IsNormalSrvStatus(VOS_VOID)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsServiceStatus )
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsServiceStatus) )
    {
        return VOS_FALSE;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    return VOS_TRUE;
}

#if (VOS_WIN32 == VOS_OS_VER)
/*Added by  z59430 for PC回放,2010-1-6,begin*/
/*****************************************************************************
 函 数 名  : NAS_MMA_SndNVData
 功能描述  : 将ps相关的nv发送给OM，以便回放使用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月6日
    作    者   : 赵鹏 59430
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMA_SndNVData(VOS_VOID)
{
    /* Absolute Path for Operating NV file */
    extern const VOS_CHAR g_aucNvFolderPath[]; /* NV Folder path */

    const VOS_CHAR aucNvimCtrlFile[]   = "NvimCtrl.bin";
    const VOS_CHAR aucNvimAuthFile[]   = "NvimAuth.bin";
    const VOS_CHAR aucSYSNVTableFile[] = "SYSNVTable.bin";
    const VOS_CHAR aucPSNVTableFile[]  = "PSNVTable.bin";
    const VOS_CHAR aucRFNVTableFile[]  = "RFNVTable.bin";
    const VOS_CHAR aucCODECNVTableFile[]  = "CODECNVTable.bin";
    const VOS_CHAR aucCFDNVTableFile[]  = "CFDNVTable.bin";

    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucNvimCtrlFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucNvimAuthFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucSYSNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucPSNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucRFNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucCODECNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucCFDNVTableFile);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMA_SndNVFileData
 功能描述  : 将指定NV法送给OM
 输入参数  : aucFileName NV文件名称
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月6日
    作    者   : 赵鹏 59430
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMA_SndNVFileData(const VOS_CHAR * aucNVFolder ,const VOS_CHAR * aucFileName)
{
    VOS_CHAR                                   *paucNvFilePath = VOS_NULL_PTR;
    VOS_UINT32                                  ulNvFilePathLen;
    FILE *                                      fp = VOS_NULL_PTR;
    VOS_UINT32                                  ulFileSize;
    VOS_UINT32                                  ulReadSize;
    VOS_UINT32                                  ulReadCount;
    VOS_UINT32                                  ulReadTotaldSize;
    VOS_UINT32                                  ulPacketLen;
    NAS_MMA_NV_MSG_ST                          *pNvMsgCB     = VOS_NULL_PTR;



#if (VOS_OS_VER == VOS_VXWORKS)
    ulNvFilePathLen = VOS_StrLen((VOS_CHAR *)aucNVFolder) + VOS_StrLen("/") + VOS_StrLen((VOS_CHAR *)aucFileName);
    paucNvFilePath = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_MMA, ulNvFilePathLen + 1);

    if ( VOS_NULL_PTR == paucNvFilePath )
    {
        MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: Alloc Memory Fail.");
        return MMA_ERROR;
    }

    (VOS_VOID)VOS_sprintf(paucNvFilePath , "%s/%s" , aucNVFolder , aucFileName);
#elif( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )
    ulNvFilePathLen = VOS_StrLen((VOS_CHAR *)aucNVFolder) + VOS_StrLen((VOS_CHAR *)aucFileName);
    paucNvFilePath = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_MMA, ulNvFilePathLen + 1);

    if ( VOS_NULL_PTR == paucNvFilePath )
    {
        MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: Alloc Memory Fail.");
        return MMA_ERROR;
    }

    (VOS_VOID)VOS_sprintf(paucNvFilePath , "%s" , aucFileName);
#endif


    /*以只读的方式打开文件*/
    fp = NV_File_Open((VOS_CHAR*)paucNvFilePath, NV_FILE_OPEN_MODE_R);

    /*如果读取NV file 长度失败*/
    if ( VOS_NULL_PTR == fp )
    {
        PS_MEM_FREE(WUEPS_PID_MMA, paucNvFilePath);
        return MMA_ERROR;
    }

    /*获取文件长度*/
    NV_File_Seek(fp, 0, NV_FILE_SEEK_END);
    ulFileSize = (VOS_UINT32)NV_File_Tell(fp);

    /* 临时处理，由于PS NV文件超过0xFFFF,OM发送数据的的长度类型未UNSIGNED SHORT类型，所以无法发送 */
    if (ulFileSize > 0xe000 )
    {
        ulPacketLen = 0xe000;
    }
    else
    {
        ulPacketLen = ulFileSize;
    }

    /* 指向文件开头 */
    NV_File_Seek(fp, 0, NV_FILE_SEEK_SET);

    /*读取NV file 长度成功*/
    pNvMsgCB = (NAS_MMA_NV_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_NV_MSG_ST) + ulPacketLen);
    if ( VOS_NULL_PTR == pNvMsgCB )
    {
        MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: Alloc Memory Fail.");

        NV_File_Close(fp);

        PS_MEM_FREE(WUEPS_PID_MMA, paucNvFilePath);
        paucNvFilePath = VOS_NULL_PTR;

        return MMA_ERROR;
    }

    /*构建消息头部*/
    pNvMsgCB->ulReceiverPid   = WUEPS_PID_MMA;
    pNvMsgCB->ulSenderPid     = WUEPS_PID_MMA;
    pNvMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pNvMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pNvMsgCB->ulLength        = sizeof(NAS_MMA_NV_CONTEXT_ST) + 4 + ulPacketLen;
    pNvMsgCB->usMsgID         = EVT_NAS_MMA_NV_CONTEXT;

    /*NV文件名*/
    (VOS_VOID)VOS_StrCpy((VOS_CHAR *)pNvMsgCB->stNVCtxt.auNvFileName , (VOS_CHAR *)aucFileName);

    /*文件长度*/
    pNvMsgCB->stNVCtxt.ulNvFileLen = ulFileSize;
    pNvMsgCB->stNVCtxt.ulPacketLen = ulPacketLen;

    /*读取文件内容*/
    ulReadCount = 0;
    ulReadSize = 0;
    ulReadTotaldSize = 0;
    do
    {
        if( ( ulPacketLen - ulReadTotaldSize ) >= 4096)
        {
            ulReadSize = 4096;

        }
        else
        {
            ulReadSize = ulPacketLen - ulReadTotaldSize ;

        }

        ulReadCount = (VOS_UINT32)NV_File_Read(
                              (VOS_CHAR*)(pNvMsgCB->stNVCtxt.auNvFileData + ulReadTotaldSize),
                              ulReadSize ,
                              1,
                              fp);

        if (ulReadSize != ulReadCount)
        {
            MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: NV_File_Read Fail.");
            break;
        }

        ulReadTotaldSize += ulReadSize;

    }while(ulReadTotaldSize < ulPacketLen);

    /*如果读文件成功*/
    if(ulReadTotaldSize == ulPacketLen)
    {
        /*发送消息*/
        DIAG_TraceReport(pNvMsgCB);
    }

    if ( ulFileSize > ulPacketLen)
    {
        /* 临时处理，文件太大，OM发送不了，OM数据长度类型为UNSIGNED SHORT，所以该处拆分两个报发送 */
        ulPacketLen = ulFileSize - 0xe000;
        /*构建消息头部*/
        pNvMsgCB->ulReceiverPid   = WUEPS_PID_MMA;
        pNvMsgCB->ulSenderPid     = WUEPS_PID_MMA;
        pNvMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pNvMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pNvMsgCB->ulLength        = sizeof(NAS_MMA_NV_CONTEXT_ST) + 4 + ulPacketLen;
        pNvMsgCB->usMsgID         = EVT_NAS_MMA_NV_CONTEXT;

        /*NV文件名*/
        (VOS_VOID)VOS_StrCpy((VOS_CHAR *)pNvMsgCB->stNVCtxt.auNvFileName , (VOS_CHAR *)aucFileName);

        /*文件长度*/
        pNvMsgCB->stNVCtxt.ulNvFileLen = ulFileSize;
        pNvMsgCB->stNVCtxt.ulPacketLen = ulPacketLen;

        /*读取文件内容*/
        ulReadCount = 0;
        ulReadSize = 0;
        ulReadTotaldSize = 0;
        do
        {
            if( ( ulPacketLen - ulReadTotaldSize ) >= 4096)
            {
                ulReadSize = 4096;
            }
            else
            {
                ulReadSize = ulPacketLen - ulReadTotaldSize ;
            }

            ulReadCount = (VOS_UINT32)NV_File_Read(
                                    (VOS_CHAR*)(pNvMsgCB->stNVCtxt.auNvFileData + ulReadTotaldSize),
                                                ulReadSize ,
                                                1,
                                                fp);

            if (ulReadSize != ulReadCount)
            {
                MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: NV_File_Read Fail.");
                break;
            }

            ulReadTotaldSize += ulReadSize;

        }while(ulReadTotaldSize < ulPacketLen);

        /*如果读文件成功*/
        if(ulReadTotaldSize == ulPacketLen)
        {
            /*发送消息*/
            DIAG_TraceReport(pNvMsgCB);
        }
    }

    /*关闭文件*/
    NV_File_Close(fp);

    /*释放内存*/
    PS_MEM_FREE(WUEPS_PID_MMA, paucNvFilePath);
    paucNvFilePath = VOS_NULL_PTR;
    PS_FREE_MSG(WUEPS_PID_MMA, pNvMsgCB);
    pNvMsgCB = VOS_NULL_PTR;

    return MMA_SUCCESS;
}

/*Added by  z59430 for PC回放,2010-1-6,end*/
#endif

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */


/*****************************************************************************
 函 数 名  : MN_PH_ResetTimerOutProc
 功能描述  : 重启定时器超时后调用底层函数进行重启
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月12日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

  2.日    期   : 2012年2月24日
    作    者   : h00135900
    修改内容   : 问题单号: DTS2012022404449, V7R1版本AT+CFUN=6无法重启
  3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:NAS只调用VOS_FlowReboot
                    由DRV屏蔽BSP_OM_SoftReboot接口
  4.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MN_PH_ResetTimerOutProc( VOS_VOID  )
{
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_StopRelTimer(WUEPS_PID_MMA, TI_MN_PH_RESET, &g_stPhPhResetTimer.MmaHTimer);
    if (VOS_OK != ulRslt)
    {
        MMA_ERRORLOG("MN_PH_ResetTimerOutProc:ERROR:NAS_StopRelTimer failed.");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    /* 使用此接口，防止AT命令触发复位生成dump文件 */
    mdrv_sysboot_shutdown(DRV_SHUTDOWN_RESET);

}

/*****************************************************************************
 函 数 名  : MN_PH_PinOperTimerOutProc
 功能描述  : 操作PIN成功后,启动定时器超时后通知MMA重启
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月12日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID MN_PH_PinOperTimerOutProc( VOS_VOID )
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    VOS_UINT32                          ulRslt;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                              sizeof(TAF_PHONE_EVENT_INFO_STRU));
    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MN_PH_PinOperTimerOutProc:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    ulRslt = NAS_StopRelTimer(WUEPS_PID_MMA, TI_MN_PH_PIN_OPER, &g_stPhPinOperTimer.MmaHTimer);
    if (VOS_OK != ulRslt)
    {
        MMA_ERRORLOG("MN_PH_PinOperTimerOutProc:ERROR:NAS_StopRelTimer FAIL.");
    }
    g_stPhPhResetTimer.ucTimerStatus = MMA_TIMER_STOP;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    MMA_InitEventInfoOP(pstPhoneEvent);

    /*调用TAF事件上报函数,上报PIN事件*/
    pstPhoneEvent->OP_Pin                    = VOS_TRUE;
    pstPhoneEvent->PhoneEvent                = TAF_PH_EVT_OP_PIN_CNF;
    PS_MEM_CPY(&pstPhoneEvent->PinCnf,&g_stPhPinCnf,sizeof(g_stPhPinCnf));
    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OK;

    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    /* MMA_SendPINOk(); */
}

/*****************************************************************************
 函 数 名  : NAS_GetRegisterState
 功能描述  : NAS提供给OM点灯任务查询当前注册状态的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_OM_REGISTER_STATE_ENUM_UINT8 - 当前注册状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月3日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年2月20日
    作    者   : z40661
    修改内容   : 增加L模的点灯方案
  3.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  5.日    期   : 2014年12月17日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
  6.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
NAS_OM_REGISTER_STATE_ENUM_UINT8 NAS_GetRegisterState(VOS_VOID)
{
    NAS_OM_REGISTER_STATE_ENUM_UINT8    ucRegisterState;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetAppSysMode();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    ucRegisterState = NAS_OM_REGISTER_STATE_BUTT;

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    {
        ucRegisterState = NAS_OM_REGISTER_STATE_POWEROFF;
    }
    else
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
        if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == TAF_SDC_GetAppServiceStatus())
        {
            if (TAF_SDC_SYS_MODE_GSM == enSysMode)
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_REGISTER_2G;
            }
            else if (TAF_SDC_SYS_MODE_WCDMA == enSysMode)
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_REGISTER_3G;
            }
            else if (TAF_SDC_SYS_MODE_LTE == enSysMode)
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_REGISTER_4G;
            }
            else
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_NOT_REGISTER;
            }
        }
        else
        {
            ucRegisterState = NAS_OM_REGISTER_STATE_NOT_REGISTER;
        }
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    }

    return ucRegisterState;
}

/*****************************************************************************
 函 数 名  : NAS_GetServiceType
 功能描述  : NAS提供给OM点灯任务查询当前业务状态的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_OM_SERVICE_TYPE_ENUM_UINT8 - 当前进行的业务类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月3日
    作    者   : o00132663
    修改内容   : 新生成函数
  1.日    期   : 2010年8月14日
    作    者   : w00166186
    修改内容   :

  3.日    期   : 2012年2月20日
    作    者   : z40661
    修改内容   : V7R1的点灯方案

  4.日    期   : 2012年6月1日
    作    者   : z40661
    修改内容   : DTS2012053006110,上报DC-HSPA+
  5.日    期   : 2013年01月05日
    作    者   : l00167671
    修改内容   : DTS2012010200069,修改点灯的判断条件
  6.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  7.日    期   : 2014年12月17日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
NAS_OM_SERVICE_TYPE_ENUM_UINT8   NAS_GetServiceType(VOS_VOID)
{
    NAS_OM_SERVICE_TYPE_ENUM_UINT8  ucServiceType;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8     enSysMode;

    enSysMode = TAF_SDC_GetAppSysMode();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    ucServiceType = NAS_OM_SERVICE_TYPE_BUTT;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        if (TAF_APS_USER_CONN_EXIST == TAF_APS_GetUserConnStatus())
        {
            /* 当前在G下 */
            ucServiceType = NAS_OM_SERVICE_TYPE_GSM;
        }
        else
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
        }
    }
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    else if (TAF_SDC_SYS_MODE_WCDMA == enSysMode)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        if (TAF_APS_USER_CONN_EXIST == TAF_APS_GetUserConnStatus())
        {
            /* 当前在W下 */
            switch (g_StatusContext.ucDataTranMode)
            {
                case STA_DATA_TRANSFER_R99_ONLY:
                    ucServiceType = NAS_OM_SERVICE_TYPE_WCDMA;
                    break;
                case STA_DATA_TRANSFER_HSDPA:
                case STA_DATA_TRANSFER_HSUPA:
                case STA_DATA_TRANSFER_HSDPA_AND_HSUPA:
                case STA_DATA_TRANSFER_HSPA_PLUS:
                case STA_DATA_TRANSFER_DC_HSPA_PLUS:
                case STA_DATA_TRANSFER_DC_MIMO:
                    ucServiceType = NAS_OM_SERVICE_TYPE_HSPA;
                    break;
                default:
                    ucServiceType = NAS_OM_SERVICE_TYPE_WCDMA;
                    break;
            }
        }
        else
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
        }
    }
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    else if (TAF_SDC_SYS_MODE_LTE == enSysMode)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        if ( STA_DATA_TRANSFER_LTE_DATA == g_StatusContext.ucDataTranMode )
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_LTE;
        }
        else
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
        }
    }
    else
    {
        ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
    }


    /* Modified by z40661 for V7R1 点灯 , 2012-02-20, end */

    return ucServiceType;
}


/*****************************************************************************
 函 数 名  : NAS_MMA_TransferSysSubMode2ActForAtCmdCreg
 功能描述  : 将MMC上报的系统子模式转为AT命令CREG/CGREG中的ACT参数对应的接入
             技术值
 输入参数  : VOS_UINT8                      ucSysSubMode : 系统子模式
 输出参数  : TAF_PH_ACCESS_TECH_ENUM_UINT8  *pucAct      : 接入技术
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月12日
    作    者   : 欧阳飞
    修改内容   : 新生成函数

  2.日    期   : 2010年7月29日
    作    者   : 欧阳飞
    修改内容   : DTS2010072900978，当上报的为无效值后，转换的值也为无效值，+CREG/+CGREG
                 不上报可选参数ACT
  3.日    期   : 2011年12月20日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIV修改

  4.日    期   : 2012年6月1日
    作    者   : z40661
    修改内容   : DTS2012053006110,上报DC-HSPA+
*****************************************************************************/
VOS_VOID NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(
    VOS_UINT8                           ucSysSubMode,
    TAF_PH_ACCESS_TECH_ENUM_UINT8      *pucAct
)
{
    switch (ucSysSubMode)
    {
        case TAF_SYS_SUBMODE_GSM:
            *pucAct = TAF_PH_ACCESS_TECH_GSM;
            break;
        case TAF_SYS_SUBMODE_GPRS:
            *pucAct = TAF_PH_ACCESS_TECH_GSM;
            break;
        case TAF_SYS_SUBMODE_EDGE:
            *pucAct = TAF_PH_ACCESS_TECH_EGPRS;
            break;
        case TAF_SYS_SUBMODE_WCDMA:
            *pucAct = TAF_PH_ACCESS_TECH_UTRAN;
            break;
        case TAF_SYS_SUBMODE_HSDPA:
            *pucAct = TAF_PH_ACCESS_TECH_HSDPA;
            break;
        case TAF_SYS_SUBMODE_HSUPA:
            *pucAct = TAF_PH_ACCESS_TECH_HSUPA;
            break;
        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            *pucAct = TAF_PH_ACCESS_TECH_HSDPA_HSUPA;
            break;

        /* 27007协议10.1.20:
          <AcT>: a numeric parameter that indicates the access technology of the serving cell
          0   GSM
          1   GSM Compact
          2   UTRAN
          3   GSM w/EGPRS (see NOTE 2)
          4   UTRAN w/HSDPA (see NOTE 3)
          5   UTRAN w/HSUPA (see NOTE 3)
          6   UTRAN w/HSDPA and HSUPA (see NOTE 3)
          7   E-UTRAN
          NOTE 2: 3GPP TS 44.060 [71] specifies the System Information messages which give the information about whether the serving cell supports EGPRS.
          NOTE 3: 3GPP TS 25.331 [74] specifies the System Information blocks which give the information about whether the serving cell supports HSDPA or HSUPA.
          协议未对HSPA+做明确说明，目前按6UTRAN w/HSDPA and HSUPA上报
        */

        case TAF_SYS_SUBMODE_HSPA_PLUS:
        case TAF_SYS_SUBMODE_DC_HSPA_PLUS:
        case TAF_SYS_SUBMODE_DC_MIMO:
            *pucAct = TAF_PH_ACCESS_TECH_HSDPA_HSUPA;
            break;

        case TAF_SYS_SUBMODE_LTE:
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
            break;

        default:
            *pucAct = TAF_PH_ACCESS_TECH_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMA_CellIdChangeForStkLocSta
 功能描述  : 判断当前小区与上次STK location status事件的小区id是否有改变
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月6日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_BOOL NAS_MMA_CellIdChangeForStkLocSta()
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId;
    VOS_UINT32                          ulCellId;
    VOS_UINT16                          usLac;

    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();
    usLac     = TAF_SDC_GetCurrCampLac();
    ulCellId  = TAF_SDC_GetCurrCampCellId();

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    if ((g_stMmsStkLocStaSysInfo.stPlmn.ulMcc != pstPlmnId->ulMcc)
     || (g_stMmsStkLocStaSysInfo.stPlmn.ulMnc != pstPlmnId->ulMnc)
     || (g_stMmsStkLocStaSysInfo.usLac != usLac)
     || (g_stMmsStkLocStaSysInfo.ulCellId != ulCellId))
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    {
       return VOS_TRUE;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    return VOS_FALSE;
}

/* Added by l00208543 for V9R1 STK升级, 2013-07-12, begin */

/*****************************************************************************
 函 数 名  : NAS_MMA_ConvertSdcServStaToStkServSta
 功能描述  : 将TAF层的service status type转换成上报给STK的service status type
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : l00208543
    修改内容   : 新增函数

  2.日    期   : 2016年1月8日
    作    者   : w00167002
    修改内容   : DTS2016010807981:国外-->国内，开机搜网无服务，导致通知USIM卡模块
                 为BUTT,usim当成LIMIT SERVICE 处理，这样给STK发送的位置信息为无效
                 的PLMN/LAC信息，导致未触发IMSI切换到国内卡。
*****************************************************************************/
NAS_STK_SERVICE_STATUS_ENUM_UINT8 NAS_MMA_ConvertSdcServStaToStkServSta(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enSdcSrvSta
)
{
    switch (enSdcSrvSta)
    {
        case TAF_SDC_REPORT_SRVSTA_BUTT:
        case TAF_SDC_REPORT_SRVSTA_NO_SERVICE:
             return NAS_STK_SERVICE_STATUS_NO_SERVICE;

        case TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE:
             return NAS_STK_SERVICE_STATUS_LIMITED_SERVICE;

        case TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE:
             return NAS_STK_SERVICE_STATUS_NORMAL_SERVICE;

        case TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE:
             return NAS_STK_SERVICE_STATUS_LIMITED_SERVICE_REGION;

        case TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP:
             return NAS_STK_SERVICE_STATUS_DEEP_SLEEP;

        default:
            MN_ERR_LOG("NAS_MMA_ConvertSdcServStaToStkServSta: The input is invalid");
            return NAS_STK_SERVICE_STATUS_BUTT;
    }

}



/*****************************************************************************
 函 数 名  : NAS_MMA_SndStkLociStatusEvent
 功能描述  : 上报STK LociStatusEvent事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : l00208543
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID NAS_MMA_SndStkLociStatusEvent(VOS_VOID)
{
    NAS_STK_LOC_STATUS_EVENT_STRU      *pstMsg        = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    TAF_SDC_PLMN_ID_STRU               *pstTempPlmnID = VOS_NULL_PTR;

    /* 申请内存 */
    ulLength = sizeof(NAS_STK_LOC_STATUS_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_LOC_STATUS_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MMA_UpdateStkLociStatusEvent: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stLocStatusEvent), 0, sizeof(NAS_STK_LOC_STATUS_EVENT_INFO_STRU));

    /* 填写新消息内容 */
    pstMsg->ulMsgId                            = ID_NAS_STK_LOC_STATUS_EVENT;

    pstMsg->ulReceiverPid                      = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstTempPlmnID                              = TAF_SDC_GetCurrCampPlmnId();
    pstMsg->stLocStatusEvent.stPlmn.Mcc        = pstTempPlmnID->ulMcc;
    pstMsg->stLocStatusEvent.stPlmn.Mnc        = pstTempPlmnID->ulMnc;

    pstMsg->stLocStatusEvent.enRat             = TAF_SDC_GetSysMode();

    pstMsg->stLocStatusEvent.enServiceStatus   = NAS_MMA_ConvertSdcServStaToStkServSta(TAF_SDC_GetServiceStatus());

    pstMsg->stLocStatusEvent.ulCellId          = TAF_SDC_GetCurrCampCellId();

    pstMsg->stLocStatusEvent.usLac             = TAF_SDC_GetCurrCampLac();

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_UpdateStkLociStatusEvent: PS_SEND_MSG ERROR");
    }

    return;

}
/* Added by l00208543 for V9R1 STK升级, 2013-07-12, end */


/*****************************************************************************
 函 数 名  : NAS_MMA_ReportLociStatus
 功能描述  : 通知SIM location status event
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月4日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2011年01月7日
    作    者   : s46746
    修改内容   : 问题单号:DTS2011010403819,网络模式I接收到接入层系统消息会进行Loci文件写操作，
                 连接态如果支持location status event，接入层上报系统消息也会向卡发送此事件
  3.日    期   : 2012年10月19日
    作    者   : s46746
    修改内容   : DTS2012101902505,开机搜网无服务时，报一次Location status event事件
  4.日    期   : 2013年6月4日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  5.日    期   : 2013年7月13日
    作    者   : l00208543
    修改内容   : 改变与STK交互方式，改为发送消息通知STK不再允许STK调用NAS的API

*****************************************************************************/
VOS_VOID NAS_MMA_ReportLociStatus(VOS_VOID)
{
    /* 由于SVLTE下两个Modem都更新没有必要，和移动确认过，只需要CS 所在Modem更新即可。
       MMA在调用前判断下，SVLTE形态下，如果没有CS域能力，就不调用。*/
    if (VOS_TRUE == TAF_MMA_IsNeedSndStkEvt())
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_LOCATION_STATUS_EVENT, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
#ifndef __PS_WIN32_RECUR__
        /* Deleted by l00208543 for V9R1 STK升级, 2013-7-12, begin */
        /* Deleted by l00208543 for V9R1 STK升级, 2013-7-12, end */

        /* Added by l00208543 for V9R1 STK升级, 2013-07-12, begin */
        NAS_MMA_SndStkLociStatusEvent();
        /* Added by l00208543 for V9R1 STK升级, 2013-07-12, end */

        Taf_GetSysInfoForSTK(&g_stMmsStkLocStaSysInfo);

        gstMmaValue.pg_StatusContext->ucIsReportedLocStatus = VOS_TRUE;
#endif
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_PH_QryApHplmn
 功能描述  : 返回sim的MCC和MNC
 输入参数  : 无
 输出参数  :
             VOS_UINT32         *pulMcc,
             VOS_UINT32         *pulMnc
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月4日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年05月06日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2011050300290,UE驻留在EPLMN上，非HPLMN，NAS认为处于漫游状态，
                 查询注册状态为漫游
  3.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_UINT32 MN_PH_QryApHplmn(
    VOS_UINT32                          *pulMcc,
    VOS_UINT32                          *pulMnc
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    if (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus)
    {
        MN_WARN_LOG("MN_PH_QryApHplmn:ERROR:SIM LOCKED.");
        return VOS_ERR;
    }

    ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(pucImsi);

    /* 获取MMC的HPlmn */
    if (USIMM_API_SUCCESS != ulGetCardImsiRslt)
    {
        MN_ERR_LOG("MN_PH_QryApHplmn:ERROR:GET IMSI FAIL.");

        if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录获取卡IMSI异常log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, pucImsi);
#endif
        }

        return VOS_ERR;
    }

    *pulMcc = 0;
    *pulMnc = 0;

    *pulMcc |= (pucImsi[1] & 0xF0) >> 4;
    *pulMcc |= (pucImsi[2] & 0x0F) << 8;
    *pulMcc |= (pucImsi[2] & 0xF0) << 12;
    *pulMnc |= (pucImsi[3] & 0x0F);
    *pulMnc |= (pucImsi[3] & 0xF0) << 4;
    *pulMnc |= (pucImsi[4] & 0x0F) << 16;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : MN_PH_QryAnQuery
 功能描述  : 获取rscp, usEcio, rssi,信号格数,小区ID信息
 输入参数  : 无
 输出参数  : VOS_INT16  *pusCpichRscp
             VOS_INT16  *pusCpichEcNo
             VOS_INT32  *plRssi,
             VOS_UINT32 *pulCellId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月7日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2010年12月14日
    作    者   : lijun 00171473
    修改内容   : DTS2010121101304, 解决列表搜完成后总是出现几秒圈外的问题
  3.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
  5.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
  6.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_UINT32 MN_PH_QryAnQuery(
    VOS_INT16                           *psCpichRscp,
    VOS_INT16                           *psCpichEcNo,
    VOS_UINT8                           *pucRssi,
    VOS_UINT32                          *pulCellId
)
{
    VOS_UINT32                          ulResult;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    VOS_INT32                           lRssiValue;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    /* 调用Taf_QueryCSNR来获取rscp, ecio的值 */
    ulResult =  Taf_QueryCSNR(psCpichRscp,psCpichEcNo);
    if(TAF_SUCCESS != ulResult)
    {
        return VOS_ERR;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if (TAF_SDC_SYS_MODE_GSM == TAF_SDC_GetAppSysMode())
    {
        lRssiValue = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue;
    }
    else
    {
        lRssiValue = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue;
    }

    MMA_GetRssiLevelFromValue(lRssiValue, pucRssi);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    /* 无服务状态时，将RSSI置为不可测99 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    if ( TAF_REPORT_SRVSTA_NO_SERVICE == TAF_SDC_GetAppServiceStatus() )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
    {
        *pucRssi = MMA_RSSI_INVALID;
    }

    /* 调用函数Api_MmaGetParaFromMscc获取mscc中的当前驻留的CellId的值 */
    *pulCellId  = TAF_SDC_GetAppCampCellId();

    /* 上报数据转换:将 Rscp、Ecio显示为非负值，若Rscp、Ecio为-145，-32，或者rssi为99，则转换为0 */
    if ( ((MMA_RSCP_MIN == (*psCpichRscp)) && (MMA_ECNO_MIN == (*psCpichEcNo)))
      || (MMA_RSSI_INVALID == (*pucRssi)) )
    {
        (*psCpichRscp) = 0;
        (*psCpichEcNo) = 0;
        (*pulCellId)   = 0xFFFFFFFF;
    }


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MMA_OutputUsimInfo
 功能描述  : 获取NAS相关的SIM卡信息
 输入参数  : 无
 输出参数  : NAS_MNTN_USIM_INFO_STRU          *pstUsimInfo NAS相关的SIM卡信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月4日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
*****************************************************************************/
VOS_VOID NAS_MMA_OutputUsimInfo(NAS_MNTN_USIM_INFO_STRU *pstUsimInfo)
{
    VOS_UINT32                          ulRet;
    NAS_MML_PLMN_ID_STRU                stRplmn;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    stRplmn.ulMcc = MMA_INVALID_MCC;
    stRplmn.ulMnc = MMA_INVALID_MNC;

    ulRet = NAS_USIMMAPI_GetCardType(&pstUsimInfo->ucCardStatus,
                              &pstUsimInfo->ucCardType);

    if (USIMM_API_SUCCESS != ulRet)
    {
        MN_WARN_LOG("NAS_MMA_OutputUsimInfo: Fail to get (U)SIM information.");
        return;
    }

    /* 快速开机或无卡无其他信息需要获取，直接返回 */
    if ((USIMM_CARD_ROM_SIM       == pstUsimInfo->ucCardType)
     || (USIMM_CARD_SERVIC_ABSENT == pstUsimInfo->ucCardStatus))
    {
        return;
    }

    /* 获取卡的PIN码启动状态
    #define TAF_ERR_NO_ERROR                   (0)  成功
    #define TAF_ERR_NEED_PIN1                 (18)  需要输入PIN1码
    #define TAF_ERR_NEED_PUK1                 (19)  需要输入PUK1
    #define TAF_ERR_SIM_FAIL                  (24)  SIM卡操作失败
    #define TAF_ERR_UNSPECIFIED_ERROR         (50)  其他错误类型
    */
    pstUsimInfo->ucPinStatus = MMA_CheckUsimStatusForPlmnSel();

    if (TAF_ERR_NO_ERROR == pstUsimInfo->ucPinStatus)
    {
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
        PS_MEM_CPY(pstUsimInfo->aucImsi, pucImsi, NAS_MNTN_IMSI_LENGTH_IN_USIM);
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
        if (VOS_TRUE != NAS_MML_GetGURPlmn(&stRplmn))
        {
            MN_WARN_LOG("NAS_MMA_OutputUsimInfo(): Warning:NAS_MML_GetGURPlmn failed.");
        }
        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

        pstUsimInfo->stRplmn.ulMcc = stRplmn.ulMcc;
        pstUsimInfo->stRplmn.ulMnc = stRplmn.ulMnc;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMA_OutputPlmnSrchBand
 功能描述  : 尝试搜网频段导出到异常事件记录
 输入参数  : 无
 输出参数  : VOS_UINT32 *pulBand    尝试搜网频段
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月9日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMA_OutputPlmnSrchBand(VOS_UINT32 *pulBand)
{
    /* BAND设置：gstMmaValue.uUserSetBand */
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstLastSyscfgSet = VOS_NULL_PTR;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    *pulBand = pstLastSyscfgSet->stUserSetBand.uUserSetGuBand.ulPrefBand;
    return;
}


/*****************************************************************************
 函 数 名  : MN_PH_SimLockedRpt
 功能描述  : SIM LOCKed上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月8日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目

*****************************************************************************/
VOS_VOID MN_PH_SimLockedRpt( VOS_VOID  )
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                        sizeof(TAF_PHONE_EVENT_INFO_STRU));
    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MN_ERR_LOG("MN_PH_PinOperTimerOutProc:ERROR:ALLOC MEMORY FAIL.");
        return ;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    MMA_InitEventInfoOP(pstPhoneEvent);

    /*调用TAF事件上报函数,上报锁卡事件*/
    pstPhoneEvent->PhoneEvent                = MN_PH_EVT_SIMLOCKED_IND;
    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}

VOS_UINT8 APP_MN_PH_AppQryPhMode (VOS_VOID)
{
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    return TAF_SDC_GetCurPhoneMode();
    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
}
/*****************************************************************************
 函 数 名  : MN_PH_RoamingRpt
 功能描述  : 主动上报漫游状态给应用
 输入参数  : ucTmpRoamStatus  漫游状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月16日
    作    者   : lijun 00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_PH_RoamingRpt( VOS_UINT8 ucTmpRoamStatus )
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                        sizeof(TAF_PHONE_EVENT_INFO_STRU));
    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MN_ERR_LOG("MN_PH_RoamingRpt:ERROR:ALLOC MEMORY FAIL.");
        return ;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    MMA_InitEventInfoOP(pstPhoneEvent);

    /*调用TAF事件上报函数,上报锁卡事件*/
    pstPhoneEvent->PhoneEvent                = MN_PH_EVT_ROAMING_IND;
    pstPhoneEvent->ucRoamStatus              = ucTmpRoamStatus;
    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

/* Deleted by w00167002 for L-C互操作项目, 2014-2-13, begin */
/* Deleted by w00167002 for L-C互操作项目, 2014-2-13, end */



/*****************************************************************************
 函 数 名  :NAS_MMA_GetPhoneMode
 功能描述  :获取当前操作模式
 输入参数  :无
 输出参数  :无
 返 回 值  :当前操作模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月1日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_UINT8 NAS_MMA_GetPhoneMode(VOS_VOID)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    return TAF_SDC_GetCurPhoneMode();
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMA_GetServiceDomain
 功能描述  : 获取当前服务域
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月1日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 MN_MMA_GetServiceDomain(VOS_VOID)
{
    return TAF_MMA_GetLastSyscfgSetAddr()->enSrvDomain;
}


/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
/* MMA_SndTafMsccPlmnSrchReq() 移至MmaSndMscc.c中*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */


/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

/*****************************************************************************
 函 数 名  : MN_MMA_GetRoamingBrokerFlg
 功能描述  : 获取RoamBroker的使能与否的标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 MN_MMA_GetRoamingBrokerFlg(VOS_VOID)
{
    return gstMmaValue.ucRoamBrokerSwitch;
}

/*****************************************************************************
 函 数 名  : MN_MMA_IsSpecRatSupported
 功能描述  : 判断指定接入技术是否支持
 输入参数  : enSpecRat:指定的接入技术
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
             VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月18日
   作    者   : s46746
   修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 MN_MMA_IsSpecRatSupported(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enSpecRat
)
{
    VOS_UINT32                          i;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList     = TAF_MMA_GetRatPrioListAddr();

    /* 如果GSM禁止接入,则认为不支持GSM */
    if ((VOS_TRUE == MMA_IsGsmForbidden())
     && (TAF_MMA_RAT_GSM == enSpecRat))
    {
        return VOS_FALSE;
    }

    /* 指定的接入技术是否在当前用户设置的RAT列表中 */
    for (i = 0 ; i < pstRatPrioList->ucRatOrderNum; i++)
    {
        if ((enSpecRat == pstRatPrioList->aenRatOrder[i])
         && (enSpecRat < TAF_MMA_RAT_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : MN_MMA_IsSpecRatInRatList
 功能描述  : 判断指定接入技术是否在RatList中
 输入参数  : enSpecRat:指定的接入技术
              pstRatPrioList 接入技术List
 输出参数  : 无
 返 回 值  : VOS_TRUE:  指定的接入技术在Ratlist中
              VOS_FALSE: 指定的接入技术不在Ratlist中
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 MN_MMA_IsSpecRatInRatList(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enSpecRat,
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT32                          i;

    /* 指定的接入技术是否在pstRatPrioList中 */
    for (i = 0 ; i < pstRatPrioList->ucRatOrderNum; i++)
    {
        if ((enSpecRat == pstRatPrioList->aenRatOrder[i])
         && (enSpecRat < TAF_MMA_RAT_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : MN_MMA_GetUserPlmnSelPrioRat
 功能描述  : 指定搜网时获取优先搜索的接入技术
 输入参数  : enPhRat:用户指定的接入技术
             pstPlmn:用户指定的网络ID
 输出参数  : 无
 返 回 值  : TAF_MMA_RAT_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月18日
   作    者   : s46746
   修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
TAF_MMA_RAT_TYPE_ENUM_UINT8 MN_MMA_GetUserPlmnSelPrioRat(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enPhRat,
    TAF_PLMN_ID_STRU                    stPlmn
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    TAF_MMA_RAT_ORDER_STRU              stRatPrioList;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList     = TAF_MMA_GetRatPrioListAddr();

    /* 如果用户指定的接入技术当前支持,则优先搜索用户指定的接入技术 */
    if (VOS_TRUE == MN_MMA_IsSpecRatSupported(enPhRat))
    {
        return enPhRat;
    }

    stRatPrioList.ucRatOrderNum = 0x0;

    /* 从MMA上报的PLMN列表中查找指定的网络,如果找到，将对应的接入技术保存 */
    for (i = 0; i < g_StatusContext.PlmnList.ucPlmnNum; i++)
    {
        /* 比较用户指定的网络与列表中保存的网络,由于用户是直接从上报的列表中选择的网络,因此可以直接比较 */
        if ((stPlmn.Mcc == g_StatusContext.PlmnList.Plmn[i].Mcc)
         && (stPlmn.Mnc == g_StatusContext.PlmnList.Plmn[i].Mnc))
        {
            stRatPrioList.aenRatOrder[stRatPrioList.ucRatOrderNum] =
                g_StatusContext.PlmnList.PlmnInfo[i].RaMode;

            stRatPrioList.ucRatOrderNum++;
        }

        /* 保护越界 */
        if (stRatPrioList.ucRatOrderNum >= TAF_PH_MAX_GUL_RAT_NUM)
        {
            break;
        }
    }

    /* 用户指定的接入技术当前不支持,如果列表中包含用户指定的网络,则返回存在接入技术中最高优先级的接入技术 */
    for (i = 0; i < pstRatPrioList->ucRatOrderNum; i++)
    {
        for (j = 0; j < stRatPrioList.ucRatOrderNum; j++)
        {
            if (pstRatPrioList->aenRatOrder[i] == stRatPrioList.aenRatOrder[j])
            {
                return pstRatPrioList->aenRatOrder[i];
            }
        }
    }

    if ((VOS_TRUE == MMA_IsGsmForbidden())
     && (TAF_MMA_RAT_GSM == pstRatPrioList->aenRatOrder[0]))
    {
        /* 用户指定的接入技术当前不支持,而且列表中也没有用户指定的网络,
           最高优先级为GSM而且当前GSM接入禁止,此时不可能为GSM单模(SYSCFG会保证),
           返回次高优先级接入技术 */
        return pstRatPrioList->aenRatOrder[1];
    }

    /* 用户指定的接入技术当前不支持,而且列表中也没有用户指定的网络,
       返回用户设置的最优先接入技术 */
    return pstRatPrioList->aenRatOrder[0];
}


/*****************************************************************************
 函 数 名  : MMA_ProcHplmnQryReq
 功能描述  : MMA处理HomePlmn查询函数
 输入参数  : VOS_UINT16 ClientId,
             VOS_UINT8  OpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年04月19日
    作    者   : w00166186
    修改内容   : 问题单号:DTS2012041402670,HPLMN MNC长度为3时显示不正确
  3.日    期  : 2012年12月26日
    作    者  : 张鹏 id:00214637
    修改内容  : USIM对外接口函数变更的处理 ，
                Client ID 到 PID的转换处理 ，入参封装成结构体。
   4.日    期   : 2013年6月3日
     作    者   : z00161729
     修改内容   : SVLTE 和usim接口调整修改
   5.日    期   : 2015年2月6日
     作    者   : h00313353
     修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 MMA_ProcHplmnQryReq(
    TAF_MMA_CTRL_STRU                  *pstCtrl
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSimStatus;
    TAF_MMA_GET_HPLMN_STRU             *pstHplmnInfo    = VOS_NULL_PTR;

    pstHplmnInfo= TAF_MMA_GetHplmnInfo();

    PS_MEM_CPY(&(pstHplmnInfo->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    if(MMA_TIMER_RUN == gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_ProcHplmnQryReq():WARNING:TIMER is running!");
        return TAF_ERR_AT_ERROR;
    }

    /*判断卡状态*/
    ulRet = MMA_PhoneGetUsimStatus(&ucSimStatus);

    if ((MMA_SUCCESS != ulRet)
     || (MMA_USIM_ABSENT == ucSimStatus))
    {
        MMA_WARNINGLOG("MMA_ProcHplmnQryReq():WARNING:USIM is Error or Absent!");
        return TAF_ERR_SIM_FAIL;
    }

    /* SIM LOCK时回复失败 */
    if (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus)
    {
        MMA_WARNINGLOG("MMA_ProcHplmnQryReq():WARNING:Sim locked!");
        return TAF_ERR_SIM_LOCK;
    }

    /*启动定时器*/
    if(MMA_SUCCESS != MMA_StartInternalTimer(1, MMA_GET_USIM_EHPLMN_AND_MNC_LEN_OP, pstCtrl->usClientId, pstCtrl->ucOpId))
    {
        MMA_WARNINGLOG("MMA_ProcHplmnQryReq():WARNING:Failed to start internal timer!");
        return TAF_ERR_AT_ERROR;
    }

    ulRet = TAF_MMA_ReadHplmnMncLenAndEhplmn();

    if (TAF_ERR_NO_ERROR != ulRet)
    {
        /*停止定时器*/
        MMA_StopInternalTimer();
        return ulRet;
    }

    return TAF_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReadHplmnMncLenAndEhplmn
 功能描述  : 从sim卡中读取Hplmn Mcc Len以及Ehplmn
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_ReadHplmnMncLenAndEhplmn(VOS_VOID)
{
    TAF_MMA_GET_HPLMN_STRU                                 *pstHplmnInfo    = VOS_NULL_PTR;
    NAS_USIMM_GETFILE_INFO_STRU                             stGetFileInfo;
    VOS_UINT16                                              usFileId;
    TAF_SDC_SIM_TYPE_ENUM_UINT8                             enSimType;

    pstHplmnInfo                        = TAF_MMA_GetHplmnInfo();
    enSimType                           = TAF_SDC_GetSimType();
    usFileId                            = USIMM_DEF_FILEID_BUTT;
    pstHplmnInfo->enWaitSimFileCnfFlg   = TAF_MMA_READ_USIM_FILE_FLG_NULL;

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));

    /* 读卡文件6FAD:获取MNC LENGTH  */
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {   /* 3G USIM */
        usFileId = USIMM_USIM_EFAD_ID;

        /* 记录在等6FAD的回复 */
        pstHplmnInfo->enWaitSimFileCnfFlg |= TAF_MMA_READ_USIM_EFAD_FILE_ID_FLG;
    }
    else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
    {   /* 2G SIM */
        usFileId = USIMM_GSM_EFAD_ID;

        /* 记录在等6FAD的回复 */
        pstHplmnInfo->enWaitSimFileCnfFlg |= TAF_MMA_READ_SIM_EFAD_FILE_ID_FLG;
    }
    else
    {
        MMA_WARNINGLOG("TAF_MMA_ReadHplmnMncLenAndEhplmn():WARNING:invalid sim type!");
        return TAF_ERR_USIM_SIM_INVALIDATION;
    }

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo, USIMM_GUTL_APP, usFileId, 0);

    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA, 0, &stGetFileInfo))
    {
        MMA_WARNINGLOG("TAF_MMA_ReadHplmnMncLenAndEhplmn():WARNING:get File Error!");

        /* 清除标志 */
        pstHplmnInfo->enWaitSimFileCnfFlg   = TAF_MMA_READ_USIM_FILE_FLG_NULL;

        return TAF_ERR_AT_ERROR;
    }

    /* 读卡文件6FD9:获取EHPLMN列表  */
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        /* 3G USIM */
        usFileId = USIMM_USIM_EFEHPLMN_ID;

        /* 记录在等6FD9的回复 */
        pstHplmnInfo->enWaitSimFileCnfFlg |= TAF_MMA_READ_USIM_EFEHPLMN_FILE_ID_FLG;
    }
    else if(TAF_SDC_SIM_TYPE_SIM == enSimType)
    {
        /* 2G SIM */
        usFileId = USIMM_ATTGSM_EFACTINGHPLMN_ID;

        /* 记录在等4F34的回复 */
        pstHplmnInfo->enWaitSimFileCnfFlg |= TAF_MMA_READ_ATTGSM_EFACTINGHPLMN_FILE_ID_FLG;
    }
    else
    {
        MMA_WARNINGLOG("TAF_MMA_ReadHplmnMncLenAndEhplmn():WARNING:invalid sim type!");
        return TAF_ERR_USIM_SIM_INVALIDATION;
    }

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo, USIMM_GUTL_APP, usFileId, 0);

    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA, 0, &stGetFileInfo))
    {
        MMA_WARNINGLOG("TAF_MMA_ReadHplmnMncLenAndEhplmn():WARNING:get File Error!");

        /* 清除标志 */
        pstHplmnInfo->enWaitSimFileCnfFlg   = TAF_MMA_READ_USIM_FILE_FLG_NULL;

        return TAF_ERR_AT_ERROR;
    }

    return TAF_ERR_NO_ERROR;
}


/*****************************************************************************
 Prototype      : At_String2Hex
 Description    : 完成字符串转16进制数功能
 Input          : nptr --- 字符串
 Output         :
 Return Value   : AT_SUCCESS --- 成功
                  AT_FAILURE --- 失败
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.日    期 : 2007-03-27
    作    者 : h59254
    修改内容 : 问题单号:A32D09820(PC-Lint修改)
*****************************************************************************/
TAF_UINT32 MMA_String2Hex(VOS_UINT8 *nptr,VOS_UINT16 usLen,VOS_UINT32 *pRtn)
{
    VOS_UINT32 c     = 0;         /* current Char */
    VOS_UINT32 total = 0;         /* current total */
    VOS_UINT8 Length = 0;         /* current Length */

    /*lint -e961*/
    c = (VOS_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else if( (c  >= 'a') && (c  <= 'f') )
        {
            c  = (c  - 'a') + 10;
        }
        else if( (c  >= 'A') && (c  <= 'F') )
        {
            c  = (c  - 'A') + 10;
        }
        else
        {
            return VOS_ERR;
        }

        if(total > 0x0FFFFFFF)              /* 发生反转 */
        {
            return VOS_ERR;
        }
        else
        {
            total = (total << 4) + c;              /* accumulate digit */
            c = (TAF_UINT32)(TAF_UINT8)*nptr++;    /* get next Char */
        }
    }
    /*lint +e961*/
    *pRtn = total;   /* return result, negated if necessary */
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MMA_CrpnQuery_GetPlmnNum
 功能描述  : 根据PLMN类型获取满足条件的PLMN个数
 输入参数  : VOS_UINT16 ClientId,
             VOS_UINT8  OpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月5日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MMA_CrpnQuery_GetPlmnNum(
    TAF_PH_OPERATOR_NAME_STRU          *pstOrigOperName,
    TAF_MMA_CRPN_QRY_PARA_STRU         *pstMnMmaCrpnQry,
    VOS_UINT8                          *pucMaxMncLen,
    VOS_UINT32                         *pulTotalNum
)
{
    VOS_UINT8                           ucMaxMncLen;
    VOS_UINT32                          ulTotalNum;

    if (0 == pstMnMmaCrpnQry->ucPlmnType)
    {
        PS_MEM_CPY(pstOrigOperName->aucOperatorNameLong, pstMnMmaCrpnQry->aucPlmnName, pstMnMmaCrpnQry->usPlmnNameLen);
        pstOrigOperName->aucOperatorNameLong[pstMnMmaCrpnQry->usPlmnNameLen] = 0;
        ulTotalNum = MMA_PhoneGetAllOperNumByLongNameFromOperTbl(pstOrigOperName, &ucMaxMncLen);
    }
    else if(1 == pstMnMmaCrpnQry->ucPlmnType)
    {
        PS_MEM_CPY(pstOrigOperName->aucOperatorNameShort, pstMnMmaCrpnQry->aucPlmnName, pstMnMmaCrpnQry->usPlmnNameLen);
        pstOrigOperName->aucOperatorNameShort[pstMnMmaCrpnQry->usPlmnNameLen] = 0;
        ulTotalNum = MMA_PhoneGetAllOperNumByShortNameFromOperTbl(pstOrigOperName, &ucMaxMncLen);
    }
    else
    {
        /*一个PLMN ID只对应于一个PLMN INFO*/
        ulTotalNum = 1;
        ucMaxMncLen = (VOS_UINT8)pstMnMmaCrpnQry->usPlmnNameLen;
    }

    *pucMaxMncLen = ucMaxMncLen;
    *pulTotalNum  = ulTotalNum;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsMncLenVaild
 功能描述  : 判断mnc长度是否合法
 输入参数  : ucMncLen - mnc长度
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 合法
             VOS_FALSE :不合法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : z00161729
    修改内容   : 降圈复杂度

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsMncLenVaild(
    VOS_UINT8                           ucMncLen
)
{
    if ((5 != ucMncLen)
     && (6 != ucMncLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}




/* MN_MMA_GetBandInfo */

/* delete MMA_PhCrpnQueryRsp */



/*lint -e429 -e830*/

/*****************************************************************************
 函 数 名  : Taf_InitEventInfoOP
 功能描述  : 初始化事件信息的选项参数，建议用宏实现，暂时用函数实现
 输入参数  : TAF_PHONE_EVENT_INFO_STRU *pEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月19日
    作    者   : liuyang
    修改内容   : 新生成函数
 2.日    期   : 2011年11月8日
   作    者   : c00173809
   修改内容   : AT融合项目，PHONE事件增加了选项，所以对增加的选项进行初始化。
  3.日    期   : 2015年4月8日
    作    者   : b00269685
    修改内容   : 删除plmn list op

*****************************************************************************/
VOS_VOID Taf_InitEventInfoOP(TAF_PHONE_EVENT_INFO_STRU *pstEvent)
{

    /*填充所有选项为0*/
    pstEvent->OP_RegPlmn            = 0;
    pstEvent->OP_CsServiceStatus    = 0;
    pstEvent->OP_PsServiceStatus    = 0;
    pstEvent->OP_PlmnReselMode      = 0;
    pstEvent->OP_PhoneError         = 0;
    pstEvent->OP_CurRegSta          = 0;
    pstEvent->OP_Rssi               = 0;
    pstEvent->OP_BatteryPower       = 0;
    pstEvent->OP_Pin                = 0;
    pstEvent->OP_UsimAccessData     = 0;
    pstEvent->OP_PinRemain          = 0;
    pstEvent->OP_MeLockStatus       = 0;
    pstEvent->OP_MePersonalisation  = 0;
    pstEvent->OP_OperMode           = 0;
    pstEvent->OP_SpnInfo            = 0;
    pstEvent->OP_Mode               = 0;
    pstEvent->OP_Srvst              = 0;
    pstEvent->OP_UsimRestrictAccess = 0;
    pstEvent->OP_UsimPNN            = 0;
    pstEvent->OP_SysCfg             = 0;
    pstEvent->OP_UsimOPL            = 0;
    pstEvent->OP_Spare              = 0;

    return;
}
/*lint +e429 +e830*/




/*****************************************************************************
 函 数 名  : TAF_MMA_IsSimLockPlmnInfoValid
 功能描述  : 当前NV项en_NV_Item_CustomizeSimLockPlmnInfo中PLMN信息是否有效
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : w00181244
    修改内容   : 新生成函数
  2.日    期   : 2012年2月4日
    作    者   : F62575
    修改内容   : AT_IsSimLockPlmnInfoValid命名变更为DRVAGENT_IsSimLockPlmnInfoValid
                 从AtCmdMsgProc.c文件移动到TafDrvAgentMsgproc.c
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_BOOL TAF_MMA_IsSimLockPlmnInfoValid(VOS_VOID)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;

    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    if (NV_OK != NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == stSimLockPlmnInfo.ulStatus)
    {
        return VOS_FALSE;
    }

    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (0xAA == stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[0])
        {
            continue;
        }

        break;
    }

    /* 如果每一项的PLMN都不是有效的，那么返回没有有效的PLMN信息 */
    if (TAF_MAX_SIM_LOCK_RANGE_NUM == i)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvSimLockQry
 功能描述  : 获取SIMLOCK状态
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月03日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2012年12月22日
    作    者   : z00220246
    修改内容   : DSDA Phase II,根据SenderPid获得上报的ClientId

*****************************************************************************/
VOS_VOID TAF_MMA_RcvSimLockQry(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    VOS_UINT32                          ulRet;
    AT_MMA_SIMLOCK_STATUS_STRU         *pstEvent;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    pstEvent = (AT_MMA_SIMLOCK_STATUS_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(AT_MMA_SIMLOCK_STATUS_STRU));
    if (VOS_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("TAF_MMA_RcvSimLockQry: read sim lock status fail");
        return;
    }

    pstEvent->ulReceiverPid          = WUEPS_PID_AT;
    pstEvent->ulMsgName              = ID_TAF_MMA_SIMLOCK_STAUS_QUERY_CNF;
    pstEvent->stAtAppCtrl.usClientId = MN_GetRealClientId(ClientId, WUEPS_PID_MMA);
    pstEvent->stAtAppCtrl.ucOpId     = OpId;

    ulRet = NV_Read(en_NV_Item_CardlockStatus,
                    &stCardLockStatus,
                    (VOS_UINT32)(sizeof(stCardLockStatus)));
    if (NV_OK != ulRet)
    {
        pstEvent->bSimlockEnableFlg = VOS_TRUE;
    }
    else
    {
        if ((VOS_TRUE == TAF_MMA_IsSimLockPlmnInfoValid())
         && (NV_ITEM_ACTIVE == stCardLockStatus.ulStatus)
         && (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE != stCardLockStatus.enCardlockStatus))
        {
            pstEvent->bSimlockEnableFlg = VOS_TRUE;
        }
        else
        {
            pstEvent->bSimlockEnableFlg = VOS_FALSE;
        }
    }

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMA, pstEvent);
    if( VOS_OK != ulRet)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvSimLockQry: Send Msg Error");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateSimlockStatus
 功能描述  : 根据密码解锁结果更新锁卡状态NV文件
 输入参数  : VOS_BOOL bUnlockOK 锁卡状态
                VOS_TRUE        解锁成功
                VOS_FALSE       解锁失败
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月03日
    作    者   : f62575
    修改内容   : 新生成函数 B050 移植SIMLOCK改制功能到V3R2
                 参考At_UpdateSimlockStatusToUnlock实现
  2.日    期   : 2012年2月21日
    作    者   : w00199382
    修改内容   : B060项目增加将simlockNv写到备份区的操作
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSimlockStatus(VOS_BOOL bUnlockOK)
{

    VOS_UINT32                          ulResult;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;


    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;

    /* 获取当前最大解锁次数 */
    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                      &stSimLockMaxTimes,
                      sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus: Fail to read en_NV_Item_CustomizeSimLockMaxTimes.");
        stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        if (NV_ITEM_DEACTIVE == stSimLockMaxTimes.ulStatus)
        {
            stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        }
    }

    /* 获取NV项en_NV_Item_CardlockStatus中的锁卡数据 */
    if (NV_OK != NV_Read(en_NV_Item_CardlockStatus, &stCardLockStatus, sizeof(stCardLockStatus)))
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus: Not read sim lock status");
        stCardLockStatus.ulRemainUnlockTimes = 0;
    }

    if (VOS_TRUE == bUnlockOK)
    {
        /* Simlock校验通过，将永久解除锁卡状态  */
        stCardLockStatus.ulStatus            = NV_ITEM_ACTIVE;
        stCardLockStatus.enCardlockStatus    = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
        stCardLockStatus.ulRemainUnlockTimes = stSimLockMaxTimes.ulLockMaxTimes;
    }
    else
    {
        stCardLockStatus.ulStatus            = NV_ITEM_ACTIVE;
        stCardLockStatus.enCardlockStatus    = TAF_OPERATOR_LOCK_LOCKED;
    }

    ulResult = NV_Write(en_NV_Item_CardlockStatus,
                        &stCardLockStatus,
                        sizeof(stCardLockStatus));
    if (NV_OK != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus: write en_NV_Item_CardlockStatus Fail.");
        return;
    }

    /*lint -e774*/
    ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                    &stCardLockStatus,
                                    sizeof(stCardLockStatus));
    if (NV_OK != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus:ERROR:write special en_NV_Item_CardlockStatus Fail.");
        return;
    }
    /*lint +e774*/


    return;

}


/*****************************************************************************
 函 数 名  : MMA_SaveWCipherInfo
 功能描述  : 将MMC发来的Cipher信息保存到全局变量
             (D_MMC_UMTS_CIPHER_INFO_IND)
 输入参数  : const MMC_UMTS_CIPHER_INFO_IND_STRU* pstCipherInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*****************************************************************************/
VOS_UINT32 MMA_SaveWCipherInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;

    pstCipherInfoInd = (MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU*)pstMsg;

    /* 将MSCC发来的Cipher信息保存到全局变量 */
    g_stMmaCipherInfo.enCipherAlgorForCSDomain = pstCipherInfoInd->ucCipherAlgorForCSDomain;
    g_stMmaCipherInfo.enCipherAlgorForPSDomain = pstCipherInfoInd->ucCipherAlgorForPSDomain;

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmaGCipherInfoInd
 功能描述  : 将MSCC发来的Cipher信息保存到全局变量
             (D_MSCC_GPRS_CIPHER_INFO_IND)
 输入参数  : const MSCC_GPRS_CIPHER_INFO_IND_STRU* pstCipherInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*****************************************************************************/
VOS_UINT32 MMA_SaveGCipherInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;
    pstCipherInfoInd = (MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU*)pstMsg;

    /* 将MSCC发来的Cipher信息保存到全局变量 */
    g_stMmaCipherInfo.ucGprsCipher             = pstCipherInfoInd->ucGprsCipher;
    g_stMmaCipherInfo.ucGprsCipherAlg          = pstCipherInfoInd->ucGprsCipherAlg;

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : MMA_QryCipherInfo
 功能描述  : 处理AT发来的Cipher信息查询请求
             (TAF_MSG_MMA_CIPHER_INFO)
 输入参数  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
             MN_MMA_CIPHER_QRY_REQ_STRU         *pstInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年12月22日
    作    者   : z00220246
    修改内容   : DSDA Phase II,根据SenderPid获得上报的ClientId
  3.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID MMA_QryCipherInfo(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    VOS_UINT8                           ucCipherInfo;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRadioMode;

    /* 初始化参数 */
    ucCipherInfo    = MMA_UMTS_UEA0;

    /*获取当前接入技术, 调用API*/
    enRadioMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_GSM == enRadioMode)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        /* 获取G模下的PS域加密信息 */
        if (VOS_TRUE == g_stMmaCipherInfo.ucGprsCipher)
        {
            ucCipherInfo = g_stMmaCipherInfo.ucGprsCipherAlg;
        }
        else
        {
            ucCipherInfo = MMA_UMTS_UEA0;
        }
    }
    else
    {
        /* 获取W模下的PS域加密信息 */
        switch(g_stMmaCipherInfo.enCipherAlgorForPSDomain)
        {
            case MMA_CIPHER_ALGOR_UEA0:
                ucCipherInfo = MMA_UMTS_UEA0;
                break;
            case MMA_CIPHER_ALGOR_UEA1:
                ucCipherInfo = MMA_UMTS_UEA1;
                break;
            case MMA_CIPHER_ALGOR_UEA2:
                ucCipherInfo = MMA_UMTS_UEA2;
                break;
            default:
                ucCipherInfo = MMA_UMTS_UEA0;
                break;
        }
    }

    TAF_MMA_SndCipherQryCnf(usClientId, ucOpId, ucCipherInfo, VOS_OK);

    return;
}

/*****************************************************************************
 函 数 名  : MN_PH_QryLocinfo
 功能描述  : 获取mcc, mnc, lac,rac,CellId
 输入参数  : 无
 输出参数  :    VOS_UINT32                          *pulMcc,
                 VOS_UINT32                          *pulMnc,
                 VOS_UINT16                          *pusLac,
                 VOS_UINT8                            *pucRac,
                 VOS_UINT32                          *pulCellId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2011年8月26日
  作    者   : q00180979
  修改内容   : 新生成函数
2.日    期   : 2013年4月2日
  作    者   : z00161729
  修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
3.日    期   : 2014年11月29日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseI项目修改
4.日    期   : 2015年02月11日
  作    者   : l00305157
  修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_UINT32 MN_PH_QryLocinfo (
    VOS_UINT32                         *pulMcc,
    VOS_UINT32                         *pulMnc,
    VOS_UINT16                         *pusLac,
    VOS_UINT8                          *pucRac,
    VOS_UINT32                         *pulCellId
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_SDC_PLMN_ID_STRU                *pstPlmnId = VOS_NULL_PTR;

    if ( TAF_REPORT_SRVSTA_NO_SERVICE == TAF_SDC_GetAppServiceStatus() )
    {
        /* 无服务状态时的处理*/
        (*pulMcc)       = 0;
        (*pulMnc)       = 0;
        (*pusLac)       = 0;
        (*pucRac)       = 0;
        (*pulCellId)    = 0;

        return VOS_OK;
    }

    /* 获取当前网络的PLMN、LAC、RAC、CellId值 */
    pstPlmnId            = TAF_SDC_GetAppServicePlmnId();
    *pulMcc              = pstPlmnId->ulMcc;
    *pulMnc              = pstPlmnId->ulMnc;
    *pusLac              = TAF_SDC_GetAppCampLac();
    *pucRac              = TAF_SDC_GetAppCampRac();
    *pulCellId           = TAF_SDC_GetAppCampCellId();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetUsimHplmnMncLenFileInd
 功能描述  : 收到USIM HPLMN MNC长度
 输出参数  : pUsimTafMsg
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年8月13日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  3.日    期   : 2015年02月05日
    作    者   : h00313353
    修改内容   : 卡接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_GetUsimHplmnMncLenFileInd(USIMM_READFILE_CNF_STRU *pUsimTafMsg)
{
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU     stHplmnWithMncLen;
    TAF_MMA_GET_HPLMN_STRU             *pstHplmnInfo = VOS_NULL_PTR;

    pstHplmnInfo = TAF_MMA_GetHplmnInfo();

    PS_MEM_SET(&stHplmnWithMncLen, 0X00, sizeof(TAF_MMA_HPLMN_WITH_MNC_LEN_STRU));

    if (TAF_MMA_READ_USIM_FILE_FLG_NULL == pstHplmnInfo->enWaitSimFileCnfFlg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetUsimHplmnMncLenFileInd: enWaitSimFileCnfFlg is null");

        return;
    }

    /* 清除等待标志 */
    pstHplmnInfo->enWaitSimFileCnfFlg &= ~TAF_MMA_READ_USIM_EFAD_FILE_ID_FLG;
    pstHplmnInfo->enWaitSimFileCnfFlg &= ~TAF_MMA_READ_SIM_EFAD_FILE_ID_FLG;

    /* 卡长度无效 */
    if ( pUsimTafMsg->usEfLen <= 3 )
    {
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-25, begin */
        stHplmnWithMncLen.ucHplmnMncLen = MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI;
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-25, end */
    }
    else
    {
        /* 获取MNC长度 */
        if (( MN_MMA_MNC_LENGTH_TWO_BYTES_IN_IMSI == (pUsimTafMsg->aucEf[MN_MMA_MNC_LENGTH_INDICATOR_POSITION-1] & MN_MMA_OCTET_LOW_FOUR_BITS) )
         || ( MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI == (pUsimTafMsg->aucEf[MN_MMA_MNC_LENGTH_INDICATOR_POSITION-1] & MN_MMA_OCTET_LOW_FOUR_BITS) ))
        {
            stHplmnWithMncLen.ucHplmnMncLen = pUsimTafMsg->aucEf[MN_MMA_MNC_LENGTH_INDICATOR_POSITION-1] & MN_MMA_OCTET_LOW_FOUR_BITS;
        }
        else
        {
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
            stHplmnWithMncLen.ucHplmnMncLen = MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI;
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
        }
    }

    /* 记录MNC长度到全局变量中 */
    pstHplmnInfo->ucHplmnMncLen = stHplmnWithMncLen.ucHplmnMncLen;

    /* 还未收齐卡文件回复,继续等待 */
    if (TAF_MMA_READ_USIM_FILE_FLG_NULL != pstHplmnInfo->enWaitSimFileCnfFlg)
    {
        return;
    }

    /* 收齐卡文件回复之后，给AT回复查询结果 */
    TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf();

    /*停止定时器*/
    MMA_StopInternalTimer();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetUsimEHplmnFileInd
 功能描述  : MMA收到USIMM_USIM_EFEHPLMN_ID消息的处理
 输入参数  : USIMM_READFILE_CNF_STRU *pUsimTafMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年12月2日
    作    者   : s00217060
    修改内容   : DTS2015070103821：coverity

*****************************************************************************/
VOS_VOID TAF_MMA_GetUsimEHplmnFileInd(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulEHplmnNum;
    TAF_SDC_PLMN_ID_STRU                stNasPlmn;
    TAF_SDC_SIM_FORMAT_PLMN_ID          astSimPlmn[TAF_SDC_MAX_EHPLMN_NUM];
    TAF_MMA_GET_HPLMN_STRU             *pstHplmnInfo = VOS_NULL_PTR;

    pstHplmnInfo = TAF_MMA_GetHplmnInfo();

    if (TAF_MMA_READ_USIM_FILE_FLG_NULL == pstHplmnInfo->enWaitSimFileCnfFlg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetUsimEHplmnFileInd: enWaitSimFileCnfFlg is null");

        return;
    }

    /* 清除等待标志 */
    pstHplmnInfo->enWaitSimFileCnfFlg   &= ~TAF_MMA_READ_USIM_EFEHPLMN_FILE_ID_FLG;
    pstHplmnInfo->ulEHplmnNum           = 0;
    ulEHplmnNum                         = 0;

    PS_MEM_SET(astSimPlmn, 0xFF, TAF_SDC_MAX_EHPLMN_NUM * sizeof(TAF_SDC_SIM_FORMAT_PLMN_ID));

    /* 从卡文件中取出SIM格式的EHPLMN列表个数 */
    ulEHplmnNum = (VOS_UINT32) (pUsimTafMsg->usEfLen / TAF_SDC_SIM_FORMAT_PLMN_LEN);

    if (ulEHplmnNum > TAF_SDC_MAX_EHPLMN_NUM)
    {
        ulEHplmnNum = TAF_SDC_MAX_EHPLMN_NUM;
    }

    /* 从卡文件中取出SIM格式的EHPLMN列表，转换成NAS格式的,保存到全局变量中 */
    for (i = 0; i < ulEHplmnNum; i++)
    {
        PS_MEM_CPY(astSimPlmn[i].aucSimPlmn,
                   pUsimTafMsg->aucEf + (TAF_SDC_SIM_FORMAT_PLMN_LEN * i),
                   TAF_SDC_SIM_FORMAT_PLMN_LEN);

        PS_MEM_SET(&stNasPlmn, 0xFF, sizeof(TAF_SDC_PLMN_ID_STRU));

        TAF_SDC_ConvertSimPlmnToNasPLMN(&astSimPlmn[i], &stNasPlmn);

        if (VOS_TRUE == TAF_SDC_IsPlmnIdValid(&stNasPlmn))
        {
            pstHplmnInfo->astEHplmnList[pstHplmnInfo->ulEHplmnNum]  = stNasPlmn;
            pstHplmnInfo->ulEHplmnNum++;
        }
    }

    /* 还未收齐卡文件回复,继续等待 */
    if (TAF_MMA_READ_USIM_FILE_FLG_NULL != pstHplmnInfo->enWaitSimFileCnfFlg)
    {
        return;
    }

    /* 收齐卡文件回复之后，给AT回复查询结果 */
    TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf();

    /*停止定时器*/
    MMA_StopInternalTimer();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf
 功能描述  : 收齐卡文件回复后给AT回复HPLMN查询结果
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf(VOS_VOID)
{
    VOS_UINT8                                              *pucImsi = VOS_NULL_PTR;
    TAF_MMA_GET_HPLMN_STRU                                 *pstHplmnInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo;
    TAF_MMA_EHPLMN_INFO_STRU                                stEHplmnInfo;
    VOS_UINT8                                               ucUserCfgEhplmnListNum;
    TAF_SDC_PLMN_ID_STRU                                    astUserCfgEhPlmnList[TAF_SDC_MAX_EHPLMN_NUM];
    VOS_UINT32                                              i;

    pucImsi      = TAF_SDC_GetSimImsi();
    pstHplmnInfo = TAF_MMA_GetHplmnInfo();

    PS_MEM_SET(&stEHplmnInfo, 0, sizeof(TAF_MMA_EHPLMN_INFO_STRU));

    /* 读取NV en_NV_Item_User_Cfg_Ehplmn_Info */
    pstNvimCfgExtEhplmnInfo = (NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                            sizeof(NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgExtEhplmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf: Alloc mem fail!");
        return;
    }

    TAF_MMA_ReadUserCfgExtEhplmnInfoNvim(pstNvimCfgExtEhplmnInfo);


    /* 取得用户NV中配置的EHplmn信息，用户配置的EHplmn信息高于SIM卡中的EHPLMN */
    TAF_MMA_GetValidUserCfgEhplmnInfo( pstHplmnInfo->ucHplmnMncLen,
                                       pucImsi,
                                       &ucUserCfgEhplmnListNum,
                                       astUserCfgEhPlmnList,
                                       pstNvimCfgExtEhplmnInfo );


    /* 把卡中的EHplmn信息追加到NV中配置的EHplmn信息后面 */
    for (i = 0; i < pstHplmnInfo->ulEHplmnNum; i++)
    {
        if (VOS_FALSE == TAF_SDC_IsBcchPlmnIdInDestSimPlmnList(&(pstHplmnInfo->astEHplmnList[i]), ucUserCfgEhplmnListNum, astUserCfgEhPlmnList))
        {
            astUserCfgEhPlmnList[ucUserCfgEhplmnListNum].ulMcc  = pstHplmnInfo->astEHplmnList[i].ulMcc;
            astUserCfgEhPlmnList[ucUserCfgEhplmnListNum].ulMnc  = pstHplmnInfo->astEHplmnList[i].ulMnc;
            ucUserCfgEhplmnListNum++;
        }

        /* 列表加满时退出 */
        if (ucUserCfgEhplmnListNum >= TAF_SDC_MAX_EHPLMN_NUM)
        {
            break;
        }
    }


    /* NV和卡中均无EHPLMN信息时，使用IMSI推导出来的HPLMN */
    if (0 == ucUserCfgEhplmnListNum)
    {
        ucUserCfgEhplmnListNum      = 1;
        astUserCfgEhPlmnList[0]     = TAF_SDC_GetImsiHomePlmn(pucImsi, pstHplmnInfo->ucHplmnMncLen);
    }


    /* EHPLMN相关消息 */
    stEHplmnInfo.ucHplmnMncLen  = pstHplmnInfo->ucHplmnMncLen;
    stEHplmnInfo.ulEHplmnNum    = ucUserCfgEhplmnListNum;
    PS_MEM_CPY(stEHplmnInfo.aucImsi, pucImsi, TAF_SDC_MAX_IMSI_LEN);
    PS_MEM_CPY(stEHplmnInfo.astEHplmnList, astUserCfgEhPlmnList, ucUserCfgEhplmnListNum * sizeof(TAF_SDC_PLMN_ID_STRU));

    /* 将plmn转换成BCD格式 */
    for (i = 0; i < ucUserCfgEhplmnListNum; i++)
    {
        MMA_PlmnId2Bcd(&(stEHplmnInfo.astEHplmnList[i]));
    }

    TAF_MMA_SndApHplmnCnf(TAF_ERR_NO_ERROR, &(pstHplmnInfo->stCtrl), &stEHplmnInfo);

    /* 释放动态内存 */
    PS_MEM_FREE(WUEPS_PID_MMA, pstNvimCfgExtEhplmnInfo);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetSimActingHplmnFileInd
 功能描述  : 读取Sim卡的Acting Hplmn
 输入参数  : USIMM_READFILE_CNF_STRU            *pUsimTafMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetSimActingHplmnFileInd(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    TAF_MMA_GET_HPLMN_STRU             *pstHplmnInfo = VOS_NULL_PTR;
    TAF_SDC_SIM_FORMAT_PLMN_ID          stSimPlmn;
    TAF_SDC_PLMN_ID_STRU                stNasPlmn;

    pstHplmnInfo = TAF_MMA_GetHplmnInfo();

    if (TAF_MMA_READ_USIM_FILE_FLG_NULL == pstHplmnInfo->enWaitSimFileCnfFlg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetSimActingHplmnFileInd: enWaitSimFileCnfFlg is null");

        return;
    }

    /* 清除等待标志 */
    pstHplmnInfo->enWaitSimFileCnfFlg   &= ~TAF_MMA_READ_ATTGSM_EFACTINGHPLMN_FILE_ID_FLG;
    pstHplmnInfo->ulEHplmnNum           = 0;

    PS_MEM_SET(&stNasPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    if (VOS_OK == pUsimTafMsg->stCmdResult.ulResult)
    {
        if (pUsimTafMsg->usEfLen >= TAF_SDC_SIM_FORMAT_PLMN_LEN)
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, pUsimTafMsg->aucEf, TAF_SDC_SIM_FORMAT_PLMN_LEN);
            TAF_SDC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stNasPlmn);

            if (VOS_TRUE == TAF_SDC_IsPlmnIdValid(&stNasPlmn))
            {
                pstHplmnInfo->astEHplmnList[pstHplmnInfo->ulEHplmnNum]  = stNasPlmn;
                pstHplmnInfo->ulEHplmnNum++;

                return;
            }
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "TAF_MMA_GetSimActingHplmnFileInd:WARNING: The length of USIM_READ_FILE_CNF is invalid.");
        }
    }
    else
    {
        /* ACTING-HPLMN读取失败或无效，USIMM_USIM_EFAD_ID文件可能还未读取完成，MNC LEN不准确，
           收齐文件回复后TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf中EHPLMN使用IMSI推导出来的 */
        pstHplmnInfo->ulEHplmnNum = 0;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "TAF_MMA_GetSimActingHplmnFileInd:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    /* 还未收齐卡文件回复,继续等待 */
    if (TAF_MMA_READ_USIM_FILE_FLG_NULL != pstHplmnInfo->enWaitSimFileCnfFlg)
    {
        return;
    }

    /* 收齐卡文件回复之后，给AT回复查询结果 */
    TAF_MMA_SndAtHplmnQryCnf_RcvUsimFileCnf();

    /*停止定时器*/
    MMA_StopInternalTimer();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_TransferRatMode
 功能描述  : 将4F36文件的PLMN MODE值转换成MMA的接入技术列表
 输入参数  : TAF_MMA_RAT_MODE_ENUM_U8            enRatMode
             TAF_MMA_RAT_ORDER_STRU              *pstRatModeOrder
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台是否支持接入技术过滤
  3.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID TAF_MMA_TransferRatMode(
    TAF_MMA_RAT_MODE_ENUM_U8            enRatMode,
    TAF_MMA_RAT_ORDER_STRU             *pstRatModeOrder
)
{
    switch(enRatMode)
    {
        case TAF_MMA_RAT_MODE_ENUM_DAUL_MODE:
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_GSM;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
            break;

        case TAF_MMA_RAT_MODE_ENUM_2G_ONLY:
            pstRatModeOrder->ucRatOrderNum  = 1;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_GSM;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_BUTT;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
            break;

        case TAF_MMA_RAT_MODE_ENUM_3G_ONLY:
            pstRatModeOrder->ucRatOrderNum  = 1;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_BUTT;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_MMA_RAT_MODE_ENUM_TRI_MODE:
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GUL_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_GSM;
            break;

        case TAF_MMA_RAT_MODE_ENUM_LTE_ONLY:
            pstRatModeOrder->ucRatOrderNum  = 1;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_BUTT;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;

            break;
#endif

        default:
#if (FEATURE_ON == FEATURE_LTE)
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GUL_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_GSM;
#else
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_GSM;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
#endif
            break;
    }

    /* 删除平台不支持的接入技术 */
    TAF_MMA_DelPlatformUnsupportedRat(pstRatModeOrder);

    /* 如果所有接入技术平台都不支持，使用平台默认值 */
    if (0 == pstRatModeOrder->ucRatOrderNum)
    {
        MN_MMA_SetDefaultRatPrioList(pstRatModeOrder);
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_ReadRatModeFile
 功能描述  : 读4F36文件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月14日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_ReadRatModeFile(VOS_VOID)
{
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucSimType;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;


    ulEfLen   = 0;
    ucSimType = USIMM_CARD_NOCARD;

    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* 接入技术平衡控制功能未使能 */
    if (VOS_TRUE != TAF_MMA_GetRatBalancingEnableFlg())
    {
        return;
    }

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if (USIMM_CARD_USIM == ucSimType)
    {
        ulResult = NAS_USIMMAPI_GetCachedFile(USIMM_ATTUSIM_EFRATMODE_ID, &ulEfLen, &pucEf, USIMM_GUTL_APP);

        /* 读文件失败 */
        if (USIMM_API_SUCCESS != ulResult)
        {
            /* 使用默认值 */
            MN_MMA_SetDefaultRatPrioList(pstRatPrioList);
        }
        /* 读文件成功 */
        else
        {
            TAF_MMA_SndOmGetCacheFile(USIMM_ATTUSIM_EFRATMODE_ID, ulEfLen, pucEf);

            if (ulEfLen < TAF_MMA_RAT_MODE_FILE_LEN)
            {
                /* 使用默认值 */
                MN_MMA_SetDefaultRatPrioList(pstRatPrioList);
            }
            else
            {
                TAF_MMA_TransferRatMode(pucEf[0], pstRatPrioList);
            }
        }
    }
    else
    {
        /* 非USIM卡，直接设置成DUAL MODE*/
        TAF_MMA_TransferRatMode(TAF_MMA_RAT_MODE_ENUM_DAUL_MODE, pstRatPrioList);
    }

    /* 更新gstMmaValue.pg_StatusContext.stRatPrioList全局变量 */
    PS_MEM_CPY(&gstMmaValue.pg_StatusContext->stRatPrioList, pstRatPrioList, sizeof(TAF_MMA_RAT_ORDER_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetPlmnSelectionMode
 功能描述  : 更新搜网模式
 输入参数  : VOS_UINT8 ucPlmnSelMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetPlmnSelectionMode(VOS_UINT8 ucPlmnSelMode)
{
    g_StatusContext.ucPlmnSelMode = ucPlmnSelMode;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPlmnSelectionMode
 功能描述  : 获取搜网模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetPlmnSelectionMode(VOS_VOID)
{
    return g_StatusContext.ucPlmnSelMode;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetNetworkSelectionMenuEnableFlg
 功能描述  : 更新网络选择菜单控制标识
 输入参数  : VOS_UINT8 ucEnableFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetNetworkSelectionMenuEnableFlg(VOS_UINT8 ucEnableFlg)
{
    g_StatusContext.stNetSelMenuCtx.ucNetSelMenuFlg = ucEnableFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetNetworkSelectionMenuEnableFlg
 功能描述  : 获取选择菜单控制标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetNetworkSelectionMenuEnableFlg(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.ucNetSelMenuFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetPlmnMode_Refresh
 功能描述  : 更新plmn mode，用于保存6F15文件的plmn mode位
 输入参数  : TAF_MMA_PLMN_MODE_ENUM_UINT8 enPlmnMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetPlmnMode_Refresh(TAF_MMA_PLMN_MODE_ENUM_UINT8 enPlmnMode)
{
    g_StatusContext.stNetSelMenuCtx.enPlmnMode = enPlmnMode;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPlmnMode_Refresh
 功能描述  : 获取plmn mode
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_PLMN_MODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_PLMN_MODE_ENUM_UINT8 TAF_MMA_GetPlmnMode_Refresh(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.enPlmnMode;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetAutoPlmnSelUser
 功能描述  : 更新自动搜网的用户
 输入参数  : TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser)
{
    g_StatusContext.stNetSelMenuCtx.enAutoPlmnSelUser = enAutoPlmnSelUser;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetAutoPlmnSelUser
 功能描述  : 获取自动搜网的用户
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 TAF_MMA_GetAutoPlmnSelUser(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.enAutoPlmnSelUser;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetTiTryingPeriodNetSelMenuStatus
 功能描述  : 获取定时器TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU的状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetTiTryingPeriodNetSelMenuStatus(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.ucTimerStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetTiTryingPeriodNetSelMenuStatus
 功能描述  : 更新定时器获取定时器TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU的状态的状态
 输入参数  : VOS_UINT8 ucStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(VOS_UINT8 ucStatus)
{
    g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.ucTimerStatus = ucStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetRatBalancingEnableFlg
 功能描述  : 更新接入技术平衡控制标识
 输入参数  : VOS_UINT8 ucEnableFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetRatBalancingEnableFlg(VOS_UINT8 ucEnableFlg)
{
    g_StatusContext.stRatBalancingCtx.ucRatBalancingFlg = ucEnableFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetRatBalancingEnableFlg
 功能描述  : 获取接入技术平衡控制标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetRatBalancingEnableFlg(VOS_VOID)
{
    return g_StatusContext.stRatBalancingCtx.ucRatBalancingFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetRatMode_Refresh
 功能描述  : 更新rat mode，用于保存4F36文件的rat mode位
 输入参数  : TAF_MMA_RAT_MODE_ENUM_U8 enRatMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetRatMode_Refresh(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode)
{
    g_StatusContext.stRatBalancingCtx.enRatMode = enRatMode;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetRatMode_Refresh
 功能描述  : 获取rat mode
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_RAT_MODE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_RAT_MODE_ENUM_U8 TAF_MMA_GetRatMode_Refresh(VOS_VOID)
{
    return g_StatusContext.stRatBalancingCtx.enRatMode;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetTiTryingPeriodRatBalancingStatus
 功能描述  : 获取定时器TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING的状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetTiTryingPeriodRatBalancingStatus(VOS_VOID)
{
    return g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.ucTimerStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetTiTryingPeriodRatBalancingStatus
 功能描述  : 更新定时器获取定时器TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING的状态的状态
 输入参数  : VOS_UINT8 ucStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetTiTryingPeriodRatBalancingStatus(VOS_UINT8 ucStatus)
{
    g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.ucTimerStatus = ucStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile
 功能描述  : 从6F15文件获取PLMN MODE位
 输入参数  : VOS_UINT16                          usEfLen
             VOS_UINT8                          *pucEf
             TAF_MMA_PLMN_MODE_ENUM_UINT8       *penPlmnMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf,
    TAF_MMA_PLMN_MODE_ENUM_UINT8       *penPlmnMode
)
{
    VOS_UINT16                          usIndex;
    VOS_UINT16                          usIndexMax;

    /* 6F15文件格式
    |Byte
    |---|---|---|---|--------|-------|--------|
    |1  |2  |3  |4  |.. .. ..| X-1   | X      |
    |---|---|---|---|--------|-------|--------|
    |A1 |B1 |A2 |B2 |.. .. ..| A(X/2)| B(X/2) |
    |---|---|---|---|--------|-------|--------|

    Byte A   Byte B
    <hex>    <----------------------------------------binary--------------------------------------->

    |--------|-----------|------|-----|--------|-------|------|------|----------|----------|
    |Service |           |      |     |        |       |      |      |          |          |
    |Group   |           |      |     |        |       |      |      |          |          |
    |Code    | Service   | Bit8 | Bit7| Bit6   | Bit5  | Bit4 | Bit3 | Bit2     | Bit1     |
    |--------|-----------|------|-----|--------|-------|------|------|----------|----------|
    |C0      | ValueAdded| PLMN | VPS | SM/MO  | SM/MO | Fax  | Data | Reserved | Language |
    |        | Services  | MODE |     | PAGING | EMAIL |      |      |          |          |
    |--------|-----------|------|-----|--------|-------|------|------|----------|----------|

    A*和B*为一个组合，A*表示service group，B*的每个bit表示一个service
    plmn mode位: A*为C0，B*的Bit8
    */

    usIndexMax = usEfLen;

    /* 文件长度不为偶数，即最后一个GROUP只有A*没有B*，所以不需要匹配最后一个A* */
    if (0 != (usEfLen % TAF_MMA_GROUP_LEN_IN_CUSTOMER_SERVICE_PROFILE_FILE))
    {
        usIndexMax = usEfLen - 1;
        MMA_WARNINGLOG("TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile: file content is invalid");
    }

    /* 查找PLMN MODE位 */
    for (usIndex = 0; usIndex < usIndexMax; usIndex = (usIndex + TAF_MMA_GROUP_LEN_IN_CUSTOMER_SERVICE_PROFILE_FILE))
    {
        if (TAF_MMA_SERVICE_GROUP_CODE_IN_CUSTOMER_SERVICE_PROFILE_FILE == pucEf[usIndex])
        {
            /* Bit8表示PLMN MODE*/
            *penPlmnMode
                = (pucEf[usIndex + 1] & TAF_MMA_PLMN_MODE_IN_SERVICE_GROUP_CODE) >> TAF_MMA_PLMN_MODE_OFFSET_IN_SERVICE_GROUP_CODE;

            break;
        }
    }

    /* PLMN MODE位不存在，返回VOS_ERR */
    if (usIndex >= usIndexMax)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvCustomerServiceProfileFile_PreProc
 功能描述  : 6F15文件预处理
 输入参数  : VOS_UINT16                          usEfLen
             VOS_UINT8                          *pucEf
 输出参数  : 无
 返 回 值  : VOS_TRUE  预处理结束后不需要进一步处理
             VOS_FALSE 预处理结束后需要进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCustomerServiceProfileFile_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    TAF_MMA_PLMN_MODE_ENUM_UINT8        enPlmnMode;

    /* 网络选择菜单控制功能未使能，返回VOS_TRUE */
    if (VOS_FALSE == TAF_MMA_GetNetworkSelectionMenuEnableFlg())
    {
        MMA_WARNINGLOG("TAF_MMA_RcvCustomerServiceProfileFile_PreProc: NV is deactive");
        return VOS_TRUE;
    }

    /* 未获取PLMN MODE位，返回VOS_TRUE */
    if (VOS_OK != TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile(usEfLen, pucEf, &enPlmnMode))
    {
        MMA_ERRORLOG("TAF_MMA_RcvCustomerServiceProfileFile_PreProc: No Plmn Mode");
        return VOS_TRUE;
    }

    /* 调用TAF_MMA_ReportPlmnModeEvent上报TAF_PH_EVT_NSM_STATUS_IND事件 */
    TAF_MMA_ReportPlmnModeEvent(enPlmnMode);

    /* 调用TAF_MMA_SetPlmnMode_Refresh 保存PLMN MODE */
    TAF_MMA_SetPlmnMode_Refresh(enPlmnMode);

    /* PLMN MODE 位1，返回VOS_TRUE */
    if (TAF_MMA_PLMN_MODE_ENUM_ENABLE == enPlmnMode)
    {
        return VOS_TRUE;
    }

    /* 当前已经是自动搜网，直接返回 VOS_TRUE*/
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO== TAF_MMA_GetPlmnSelectionMode())
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
    {
        return VOS_TRUE;
    }

    /* TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU定时器正在运行，直接返回VOS_TRUE */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodNetSelMenuStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcCustomerServiceProfileFile
 功能描述  : 处理6F15文件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcCustomerServiceProfileFile(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    if ((STA_FSM_STOP == g_StatusContext.ulFsmState)
     || (STA_FSM_NULL == g_StatusContext.ulFsmState))
    {
        /* 关机或NULL状态不处理 */
        MMA_NORMAILLOG("TAF_MMA_ProcCustomerServiceProfileFile(): Start Timer Fail");
    }
    else if (STA_FSM_ENABLE == g_StatusContext.ulFsmState)
    {
        /* 发起自动搜网请求 */
        TAF_MMA_SndAutoPlmnReselect_Refresh();

        /* 记录为Refresh触发的自动搜网 */
        TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH);
    }
    else
    {
        /* 启动TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU定时器 */
        ulResult = NAS_StartRelTimer(&(g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.MmaHTimer),
                                     WUEPS_PID_MMA,
                                     TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU_LEN,
                                     TAF_MMA,
                                     TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU,
                                     VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulResult)
        {
            MMA_ERRORLOG("TAF_MMA_ProcCustomerServiceProfileFile(): Start Timer Fail");
        }
        else
        {
            TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(MMA_TIMER_RUN);
        }
    }

    return;
}

/* TAF_MMA_RcvCustomerServiceProfileFile */

/*****************************************************************************
 函 数 名  : TAF_MMA_NetworkSelectionMenuCtrlTimerExpired
 功能描述  : 定时器TI_TAF_MMA_NETWORK_SELECTION_MENU_CTLR超时处理函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_NetworkSelectionMenuCtrlTimerExpired(VOS_VOID)
{
    /* 更新定时器状态 */
    TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(MMA_TIMER_STOP);

    /* 如果在定时器运行过程中，又触发了REFRESH，需要判断最后一次REFRESH是否需要发起自动搜网 */
    if (TAF_MMA_PLMN_MODE_ENUM_DISABLE != TAF_MMA_GetPlmnMode_Refresh())
    {
        return;
    }

    /* 当前已经是自动搜网 ，返回 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO == TAF_MMA_GetPlmnSelectionMode())
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
    {
        return;
    }

    /* 处理6F15文件 */
    TAF_MMA_ProcCustomerServiceProfileFile();

    return;
}

/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcRatMode_EnableStatus
 功能描述  : Enable状态，处理4F36文件
 输入参数  : TAF_MMA_RAT_MODE_ENUM_U8 ucRatMode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年9月27日
    作    者   : l60609
    修改内容   : DTS2012092508922：频道信息应该与上单板支持的频段
  3.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
  4.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SysCfg SrvDomain宏定义转为枚举
*****************************************************************************/
VOS_VOID TAF_MMA_ProcRatMode_EnableStatus(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode)
{
    TAF_MMA_RAT_ORDER_STRU              stCurRatModeOrder;

    /* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfg;
    /* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pLastSyscfgSet = VOS_NULL_PTR;
    /* Added by L60609 for DTS2012092508922，2012-09-25,  Begin*/
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
#endif
    /* Added by L60609 for DTS2012092508922，2012-09-25,  End*/

    /* 将4F36文件的PLMN MODE值转换成MMA的接入技术列表 */
    TAF_MMA_TransferRatMode(enRatMode, &stCurRatModeOrder);

    /* 从MN_MMA_GetRatPrioListAddr中获取接入技术之外的参数 */
    pLastSyscfgSet     = TAF_MMA_GetLastSyscfgSetAddr();

    /* Deleted by w00167002 for L-C互操作项目, 2014-2-13, begin */
    /* Deleted by w00167002 for L-C互操作项目, 2014-2-13, end */

    stSysCfg.enRoam      = pLastSyscfgSet->enRoam;
    stSysCfg.enSrvDomain = pLastSyscfgSet->enSrvDomain;
    stSysCfg.stGuBand    = pLastSyscfgSet->stUserSetBand.stOrigUserSetGuBand;
#if(FEATURE_ON == FEATURE_LTE)
    stSysCfg.stLBand     = pLastSyscfgSet->stUserSetBand.stUserSetLteBand;
#endif

    /* Added by L60609 for DTS2012092508922，2012-09-25,  Begin*/
    stSysCfg.stGuBand.ulBandLow  &= TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
#if(FEATURE_ON == FEATURE_LTE)
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();
    stSysCfg.stLBand.ulBandHigh &= pstUeSupportLteBand->ulBandHigh;
    stSysCfg.stLBand.ulBandLow  &= pstUeSupportLteBand->ulBandLow;
#endif
    /* Added by L60609 for DTS2012092508922，2012-09-25,  End*/

    if (VOS_TRUE == MN_MMA_IsSpecRatSupported(TAF_MMA_RAT_LTE))
    {
        stSysCfg.enUserPrio = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    }
    else
    {
        stSysCfg.enUserPrio = TAF_MMA_USER_SET_PRIO_AUTO;
    }

    /* 根据refresh的接入技术更新接入技术 */
    stSysCfg.stRatOrder  = stCurRatModeOrder;


    TAF_MMA_SndInterSysCfgSetReq(&stSysCfg);

#if 0
    /* 调用MMA_PhSysCfgSetCmdCheck获取参数 */
    MMA_PhSysCfgSetCmdCheck(&stSysCfg, &usSetFlg, &ucAttachType, &ucDetachType);

    /* 调用MN_MMA_SetSyscfg_EnableStatus发送SYSCFG请求  */
    MN_MMA_SetSyscfg_EnableStatus(&stSysCfg, TAF_MMA_SYSCFG_USER_USIM_REFRESH);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcRatMode
 功能描述  : 处理Refresh的4F36文件
 输入参数  : TAF_MMA_RAT_MODE_ENUM_U8 enRatMode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcRatMode(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode)
{
    if ((STA_FSM_STOP == g_StatusContext.ulFsmState)
     || (STA_FSM_NULL == g_StatusContext.ulFsmState))
    {
        /* 关机或NULL状态不处理 */
        MMA_NORMAILLOG("TAF_MMA_RcvRatModeFileRefresh(): Start Timer Fail");
    }
    else if (STA_FSM_ENABLE == g_StatusContext.ulFsmState)
    {
        /* 发起SYSCFG请求 */
        TAF_MMA_ProcRatMode_EnableStatus(enRatMode);
    }
    else
    {
        /* 启动TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器 */

        TAF_MMA_StartTimer(TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING, TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING_LEN);

            TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_RUN);
        }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_CheckRatModePara
 功能描述  : 检查4F36文件的接入技术是否有效
 输入参数  : TAF_MMA_RAT_ORDER_STRU              *pstCurRatModeOrder
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月2日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  4.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 TAF_MMA_CheckRatModePara(
    TAF_MMA_RAT_ORDER_STRU             *pstCurRatModeOrder
)
{
    VOS_UINT8                           ucCardType;
    VOS_UINT32                          ulGForbbidenFlag;


    ucCardType = USIMM_CARD_NOCARD;

    ulGForbbidenFlag = MN_MMA_IsGOnlyMode(pstCurRatModeOrder);

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType) ;

#if (FEATURE_ON == FEATURE_LTE)

    /* 如果是SIM卡，当设置成L单模时不处理 */
    if (VOS_TRUE == MN_MMA_IsLOnlyMode(pstCurRatModeOrder))
    {
        if (USIMM_CARD_SIM == ucCardType)
        {
            MMA_ERRORLOG("TAF_MMA_CheckRatModePara_PreProc: L ONLY & SIM CARD!");
            return VOS_TRUE;
        }
    }
#endif

    /* 如果UE不支持GSM，当设置成G单模时，返回失败; */
    if (VOS_TRUE == MMA_IsGsmForbidden())
    {
        if (VOS_TRUE == ulGForbbidenFlag)
        {
            MMA_ERRORLOG("TAF_MMA_CheckRatModePara_PreProc: G ONLY & FORBIDDEN!");
            return VOS_TRUE;
        }
    }

    /* SIM卡并且G模禁止，当前接入技术为GL或者LG，返回失败 */
    if ((USIMM_CARD_SIM == ucCardType)
     && (VOS_TRUE == ulGForbbidenFlag)
     && ((TAF_PH_MAX_GUL_RAT_NUM - 1) == pstCurRatModeOrder->ucRatOrderNum))
    {
        if ((TAF_MMA_RAT_LTE == pstCurRatModeOrder->aenRatOrder[0])
         && (TAF_MMA_RAT_GSM == pstCurRatModeOrder->aenRatOrder[1]))
        {
            return VOS_TRUE;
        }

        if ((TAF_MMA_RAT_GSM == pstCurRatModeOrder->aenRatOrder[0])
         && (TAF_MMA_RAT_LTE == pstCurRatModeOrder->aenRatOrder[1]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvRatModeFileRefresh_PreProc
 功能描述  : 4F36文件预处理
 输入参数  : VOS_UINT16                          usEfLen
             VOS_UINT8                          *pucEf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月19日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2014年2月18日
    作    者   : w00167002
    修改内容   : L-C互操作项目:在CL模式时候，不处理卡状态的刷新，触发SYSCFG设置
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvRatModeFileRefresh_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    TAF_MMA_RAT_ORDER_STRU              stCurRatModeOrder;
    VOS_UINT32                          ulRatOrderChangedFlg;
    TAF_MMA_RAT_ORDER_STRU             *pstLastRatPrioList = VOS_NULL_PTR;

    /* Added by w00167002 for L-C互操作项目, 2014-2-18, begin */

    /* 如果当期为CL 模式，则直接返回 */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        return VOS_TRUE;
    }
    /* Added by w00167002 for L-C互操作项目, 2014-2-18, end */

    /* 接入技术平衡控制功能未使能，直接返回 */
    if (VOS_FALSE == TAF_MMA_GetRatBalancingEnableFlg())
    {
        return VOS_TRUE;
    }

    /* 该文件内容只有一个byte */
    if (usEfLen < TAF_MMA_RAT_MODE_FILE_LEN)
    {
        return VOS_TRUE;
    }

    /* 将4F36文件的PLMN MODE值转换成MMA的接入技术列表 */
    TAF_MMA_TransferRatMode(pucEf[0], &stCurRatModeOrder);

    /* 接入技术检查*/
    if (VOS_TRUE == TAF_MMA_CheckRatModePara(&stCurRatModeOrder))
    {
        return VOS_TRUE;
    }

    /* 保存refresh的接入技术 */
    TAF_MMA_SetRatMode_Refresh(pucEf[0]);

    /* TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器正在运行，返回 */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodRatBalancingStatus())
    {
        return VOS_TRUE;
    }

    pstLastRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* 与MN_MMA_GetRatPrioListAddr中的接入技术比较，不改变，直接返回*/
    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(&stCurRatModeOrder,
                                                              pstLastRatPrioList);

    /* 接入技术不改变 */
    if (VOS_FALSE == ulRatOrderChangedFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvRatModeFileRefresh
 功能描述  : 收到4F36文件refresh
 输入参数  : VOS_UINT16                          usEfLen
             VOS_UINT8                          *pucEf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月14日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_RcvRatModeFileRefresh(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    /* 预处理结束，不需要进一步处理 */
    if (VOS_TRUE == TAF_MMA_RcvRatModeFileRefresh_PreProc(usEfLen, pucEf))
    {
        return;
    }

    /* 处理4F36文件 */
    TAF_MMA_ProcRatMode(pucEf[0]);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetIccIdChangedFlg
 功能描述  : 判断当前IccId是否发生变化
 输入参数  : VOS_UINT8                                ucIsCardRefresh,
             NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月27日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetIccIdChangedFlg(
    VOS_UINT8                                ucIsCardRefresh,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus
)
{
    VOS_UINT8                          *pucEf           = VOS_NULL_PTR;
    VOS_UINT32                          ulEfLen;
    TAF_SDC_ICCID_INFO_STRU            *pstIccIdInfo    = VOS_NULL_PTR;

    pstIccIdInfo                        = TAF_SDC_GetIccIdInfo();

    ulEfLen                             = 0;

    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT != enCsimStatus)
    {
        /* 读取IccId */
        if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCachedFile(USIMM_ICCID_ID, &ulEfLen, &pucEf, USIMM_UNLIMIT_AUTO))
        {
            if ((ulEfLen        <= TAF_SDC_ICC_ID_MAX_NUM)
             && (0              != ulEfLen)
             && (VOS_NULL_PTR   != pucEf))
            {
                if ((0          == PS_MEM_CMP(pucEf, pstIccIdInfo->aucIccId, ulEfLen))
                 && (ulEfLen    == pstIccIdInfo->ucLen))
                {
                    return ucIsCardRefresh;
                }

                TAF_SDC_SetIccIdInfo((VOS_UINT8)ulEfLen, pucEf);

                return VOS_TRUE;
            }
        }
    }

    if (VOS_TRUE    == TAF_MMA_IsValidIccId())
    {
        /* 刷新为无卡状态 */
        TAF_MMA_InitSdcIccId();

        return VOS_TRUE;
    }

    return ucIsCardRefresh;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RatBalancingCtrlTimerExpired
 功能描述  : 定时器TI_TAF_MMA_RAT_BALANCING_CTLR超时处理函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_RatBalancingCtrlTimerExpired(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU             *pstLastRatPrioList = VOS_NULL_PTR;
    TAF_MMA_RAT_ORDER_STRU              stCurRatModeOrder;
    VOS_UINT32                          ulRatOrderChangedFlg;

    /* 更新定时器状态 */
    TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_STOP);

    pstLastRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* 将4F36文件的PLMN MODE值转换成MMA的接入技术列表 */
    TAF_MMA_TransferRatMode(TAF_MMA_GetRatMode_Refresh(), &stCurRatModeOrder);

    /* 与MN_MMA_GetRatPrioListAddr中的接入技术比较，不改变，直接返回*/
    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(&stCurRatModeOrder,
                                                              pstLastRatPrioList);

    /* 参数改变，需要处理4F36文件 */
    if (VOS_TRUE == ulRatOrderChangedFlg)
    {
        TAF_MMA_ProcRatMode(TAF_MMA_GetRatMode_Refresh());
    }

    return;
}


/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnIdReport
 功能描述  : 向AT上报PLMN ID
 输入参数  : pstPlmn
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月11日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整

*****************************************************************************/
VOS_VOID TAF_MMA_PlmnIdReport(
    TAF_PLMN_ID_STRU                   *pstPlmn
)
{
    TAF_MMA_PLMN_CHANGE_IND_STRU       *pstPlmnChangeInd = VOS_NULL_PTR;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl = VOS_NULL_PTR;

    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */


    /* plmn没有改变，不上报 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if ((pstPlmn->Mcc == pstPlmnId->ulMcc)
     && (pstPlmn->Mnc == pstPlmnId->ulMnc))
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        return;
    }

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    if ( VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_PLMN))
    {
        return;
    }

    /* 申请变量 */
    pstPlmnChangeInd = (TAF_MMA_PLMN_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMA,
                                                        sizeof(TAF_MMA_PLMN_CHANGE_IND_STRU));
    if (VOS_NULL_PTR == pstPlmnChangeInd)
    {
        MMA_ERRORLOG("TAF_MMA_PlmnIdReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    /* 初始化变量 */
    PS_MEM_SET((VOS_CHAR *)pstPlmnChangeInd + VOS_MSG_HEAD_LENGTH,
            0x00,
            (sizeof(TAF_MMA_PLMN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /* 填充上报事件 */
    pstPlmnChangeInd->MsgHeader.ulMsgName              = ID_TAF_MMA_PLMN_CHANGE_IND;
    pstPlmnChangeInd->stCurPlmn.Mcc                    = pstPlmn->Mcc;
    pstPlmnChangeInd->stCurPlmn.Mnc                    = pstPlmn->Mnc;
    pstPlmnChangeInd->usClientId                       = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstPlmnChangeInd->ucOpId                           = MMA_OP_ID_INTERNAL;
    pstPlmnChangeInd->MsgHeader.ulReceiverPid          = WUEPS_PID_AT;

    MMA_PlmnId2Bcd(&(pstPlmnChangeInd->stCurPlmn));

    /* 事件上报 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPlmnChangeInd);

    return;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_SndOmGetCacheFile
 功能描述  : TAF调用USIMM_GetCachedFile接口，勾消息
 输入参数  : VOS_UINT32                          ulFileId
             VOS_UINT32                          ulFileLen
             VOS_UINT8                          *pucFileContent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
)
{
    TAF_MMA_GET_CACHE_FILE_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(TAF_MMA_GET_CACHE_FILE_STRU) + ulFileLen;

    pstMsg = (TAF_MMA_GET_CACHE_FILE_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        MMA_ERRORLOG("TAF_MMA_SndOmMsccTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = ulFileId;

    pstMsg->ulFileLen                   = ulFileLen;

    PS_MEM_CPY(pstMsg->aucFileContent, pucFileContent, ulFileLen);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndOmLocationStatus
 功能描述  : TAF调用USIMM_GetCachedFile接口，勾消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SndOmLocationStatus(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstMsg = VOS_NULL_PTR;

    pstMsg = (MSG_HEADER_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(MSG_HEADER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MMA_ERRORLOG("TAF_MMA_SndOmLocationStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->ulLength        = 4;
    pstMsg->ulMsgName       = 0x9999;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndDrxTimerInfo
 功能描述  : 发送DRX周期定时器的可维可测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月9日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_MMA_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus )
{
    TAF_MMA_DRX_TIMER_STAUTS_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(TAF_MMA_DRX_TIMER_STAUTS_STRU)  ;

    pstMsg = (TAF_MMA_DRX_TIMER_STAUTS_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "TAF_MMA_SndDrxTimerInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = 0x8888;
    PS_MEM_SET(pstMsg->aucReserve,0x00,sizeof(pstMsg->aucReserve));
    pstMsg->ucDrxTimerStatus            = ucDrxTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsPlatformSupportSpecUserRat
 功能描述  : 判断用户设置的RAT类型，平台能力是否支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
              VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsPlatformSupportSpecUserRat(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enUserRat
)
{
    VOS_UINT32                          ulPlatformSuppFlg;
    VOS_UINT32                          ulGsmForbiddenFlg;

    ulPlatformSuppFlg = VOS_TRUE;

    switch (enUserRat)

    {
        case TAF_MMA_RAT_GSM:
            /* 对于GSM接入技术，还需要判断GSM硬件频段是否支持 */
            ulGsmForbiddenFlg = MMA_IsGsmForbidden();

            if ((VOS_FALSE == TAF_SDC_IsPlatformSupportGsm())
             || (VOS_TRUE == ulGsmForbiddenFlg))
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

        case TAF_MMA_RAT_WCDMA:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupportUtran())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_MMA_RAT_LTE:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupportLte())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_MMA_RAT_1X:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupport1x())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

        case TAF_MMA_RAT_HRPD:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupportHrpd())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

#endif


        default :
            MMA_WARNINGLOG("TAF_MMA_IsPlatformSupportSpecUserRat:WARNING:invalid rat.");

            /* 无效接入技术默认不支持 */
            ulPlatformSuppFlg = VOS_FALSE;
            break;
    }

    return ulPlatformSuppFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_DelPlatformUnsupportedRat
 功能描述  : 删除Rat list中平台接入技术能力不支持的Rat
 输入参数  : 无
 输出参数  : pstRatPrioList - 接入优先级信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
  3.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID TAF_MMA_DelPlatformUnsupportedRat(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulPlatformSuppFlg;

    i = 0;

    if (pstRatPrioList->ucRatOrderNum > TAF_PH_MAX_GUL_RAT_NUM)
    {
        pstRatPrioList->ucRatOrderNum = TAF_PH_MAX_GUL_RAT_NUM;
    }

    /* 将pstRatPrioList中支持接入技术进行遍历，检查平台接入技术能力是否支持 */
    while (i < pstRatPrioList->ucRatOrderNum)
    {
        ulPlatformSuppFlg = TAF_MMA_IsPlatformSupportSpecUserRat(pstRatPrioList->aenRatOrder[i]);

        /* 如果不支持，需要删除，如果支持，继续检查下一个 */
        if (VOS_FALSE == ulPlatformSuppFlg)
        {
            pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_BUTT;
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstRatPrioList->aenRatOrder[i]),
                        &(pstRatPrioList->aenRatOrder[i+1]),
                        (TAF_PH_MAX_GUL_RAT_NUM-i-1));
            /*lint +e961*/
            pstRatPrioList->ucRatOrderNum --;
        }
        else
        {
            i ++;
        }
    }

    return;
}

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */


/*****************************************************************************
 函 数 名  : TAF_MMA_FillCopnOperNameList
 功能描述  : 填写+COPN结果上报消息的运营商名称列表
 输入参数  : VOS_UINT32                          ulFromIndex
             VOS_UINT16                          usPlmnNum
             TAF_MMA_COPN_INFO_QUERY_CNF_STRU   *pstCopnQryCnf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，支持+COPN命令

*****************************************************************************/
VOS_VOID TAF_MMA_FillCopnOperNameList(
    VOS_UINT32                          ulFromIndex,
    VOS_UINT16                          usPlmnNum,
    TAF_MMA_COPN_INFO_QRY_CNF_STRU     *pstCopnQryCnf
)
{
    VOS_UINT32                          ulLoop;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperNameList   = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    /*
       填写gastNetworkNameTbl中从ulFromIndex开始的usPlmnNum运营商信息到
       +COPN结果上报消息的运营商名称列表
    */
    pstCopnQryCnf->usPlmnNum      = usPlmnNum;

    pstNetworkNameTbl             = TAF_MMA_GetNetworkNameTblAddr();
    pstNetworkNameTbl            +=  ulFromIndex;

    pstOperNameList               = (TAF_PH_OPERATOR_NAME_STRU *)pstCopnQryCnf->aucContent;

    for (ulLoop = 0; ulLoop < usPlmnNum; ulLoop++)
    {
        /*
        将运营商的信息拷贝到+COPN上报消息中: 数字类型的PLMN，运营商长名
        为提高接口的可扩展性，运营商短名也在消息中发送
        */
        pstOperNameList->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
        pstOperNameList->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

        /* 运营商的MNC长度不为3时，将第三位设置为F */
        if (TAF_MMA_PLMN_MNC_TWO_BYTES == pstNetworkNameTbl->ucMncLength)
        {
            pstOperNameList->PlmnId.Mnc |= TAF_MMA_PLMN_MNC_DIGIT3_MASK;
        }

        (VOS_VOID)VOS_StrNCpy(pstOperNameList->aucOperatorNameShort,
                   pstNetworkNameTbl->pStrOperatorNameShort,
                   TAF_PH_OPER_NAME_SHORT);

        (VOS_VOID)VOS_StrNCpy(pstOperNameList->aucOperatorNameLong,
                   pstNetworkNameTbl->pStrOperatorNameLong,
                   TAF_PH_OPER_NAME_LONG);

        pstNetworkNameTbl ++;
        pstOperNameList ++;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SaveCellAcInfo
 功能描述  : 将MSCC发来的小区接入禁止信息保存到全局变量
 输入参数  : const MSCC_MMA_AC_INFO_CHANGE_IND_STRU* pstAcInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_SaveCellAcInfo(
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoInd
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_ACCESS_RESTRICTION_STRU     stAcRestriction;

    PS_MEM_SET(&stAcRestriction, 0, sizeof(stAcRestriction));

    stAcRestriction.enCellAcType              = pstAcInfoInd->enCellAcType;
    stAcRestriction.ucRestrictPagingRsp       = pstAcInfoInd->ucRestrictPagingRsp;
    stAcRestriction.ucRestrictRegister        = pstAcInfoInd->ucRestrictRegister;

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstAcInfoInd->enCnDomainId)
    {
        TAF_SDC_SetCsAcRestriction(&stAcRestriction);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstAcInfoInd->enCnDomainId)
    {
        TAF_SDC_SetPsAcRestriction(&stAcRestriction);
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_SaveCellAcInfo:ERROR:Unexpected src domain.");
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    return;
}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* TAF_MMA_InitCellAcInfo移动位置 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccAcInfoChangeInd
 功能描述  : MMA收到MSCC D_MSCC_AC_INFO_CHANGE_IND消息的处理
 输入参数  : MSCC_MMA_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2015/03/23
    作    者   : K00902809
    修改内容   : This function is isolated from common event handlers.
                 Previous:
                            Retrieves the data and sends to AT as event.
                 Present:
                            Created new structure TAF_MMA_AC_INFO_CHANGE_IND_STRU
                            Retreives the data and sends as MMA to AT message.

  4.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg系统重构
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccAcInfoChangeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd = VOS_NULL_PTR;
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU   *pstRcvAcInfoChangeInd = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl     = VOS_NULL_PTR;

    pstCurcRptCtrl = TAF_SDC_GetCurcRptCtrl();

    pstRcvAcInfoChangeInd = (MSCC_MMA_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    TAF_MMA_SaveCellAcInfo(pstRcvAcInfoChangeInd);

    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_ACINFO))
    {
        return VOS_TRUE;
    }

    pstAcInfoChangeInd = (TAF_MMA_AC_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_MMA,
                                                            sizeof(TAF_MMA_AC_INFO_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstAcInfoChangeInd)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET( ((VOS_UINT8 *)pstAcInfoChangeInd + VOS_MSG_HEAD_LENGTH), 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH) );


    pstAcInfoChangeInd->ulReceiverPid                       = WUEPS_PID_AT;
    pstAcInfoChangeInd->ulMsgName                           = ID_TAF_MMA_AC_INFO_CHANGE_IND;
    pstAcInfoChangeInd->ucOpId                              = MMA_OP_ID_INTERNAL;
    pstAcInfoChangeInd->usClientId                          = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);

    pstAcInfoChangeInd->stCellAcInfo.enCellAcType           = pstRcvAcInfoChangeInd->enCellAcType;
    pstAcInfoChangeInd->stCellAcInfo.ucRestrictPagingRsp    = pstRcvAcInfoChangeInd->ucRestrictPagingRsp;
    pstAcInfoChangeInd->stCellAcInfo.ucRestrictRegister     = pstRcvAcInfoChangeInd->ucRestrictRegister;

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstRcvAcInfoChangeInd->enCnDomainId)
    {
        pstAcInfoChangeInd->stCellAcInfo.enSrvDomain  = TAF_MMA_SERVICE_DOMAIN_CS;
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstRcvAcInfoChangeInd->enCnDomainId)
    {
        pstAcInfoChangeInd->stCellAcInfo.enSrvDomain  = TAF_MMA_SERVICE_DOMAIN_PS;
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_RcvMsccAcInfoChangeInd:ERROR:Unexpected srv domain.");
    }

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAcInfoChangeInd);

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_IsModeChangeNeedRpt
 功能描述  : 判断模式变化时，是否需要上报给AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持
              VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsModeChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg             = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_MODE);

    ulChkUnsolicitedRptFlg      = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_MODE);

    /* CURC和^mode都设置为主动上报打开时，才需要上报 */
    if ( (VOS_FALSE == ulChkCurcRptFlg)
     ||  (VOS_FALSE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsServStaChangeNeedRpt
 功能描述  : 判断服务状态变化时，是否需要上报AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
             VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsServStatusChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg                 = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_SRVST);

    ulChkUnsolicitedRptFlg          = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_SRVST);

    /* CURC和^srvst都设置为主动上报打开时，才需要上报 */
    if ( (VOS_FALSE == ulChkCurcRptFlg)
     ||  (VOS_FALSE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsRssiChangeNeedRpt
 功能描述  : 判断RSSI变化时，是否需要上报AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
              VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2014年11月28日
    作    者   : w00281933
    修改内容   : 服务状态显示优化Phase I
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsRssiChangeNeedRpt(VOS_VOID)
{
    VOS_UINT32                              ulChkRssiCurcFlg;
    VOS_UINT32                              ulChkRssiUnsolicitedFlg;
    VOS_UINT32                              ulChkCerssiCurcFlg;
    VOS_UINT32                              ulChkCerssiUnsolicitedFlg;
    VOS_UINT32                              ulChkAnlevelCurcFlg;
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkRssiCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_RSSI);

    ulChkRssiUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_RSSI);

    ulChkCerssiCurcFlg          = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CERSSI);

    ulChkCerssiUnsolicitedFlg   = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CERSSI);

    ulChkAnlevelCurcFlg          = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_ANLEVEL);

    /* RSSI需要上报 */
    if ( (VOS_TRUE == ulChkRssiCurcFlg)
      && (VOS_TRUE == ulChkRssiUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* CERSSI需要上报 */
    if ( (VOS_TRUE == ulChkCerssiCurcFlg)
      && (VOS_TRUE == ulChkCerssiUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* ANLEVEL需要上报 */
    if (VOS_TRUE == ulChkAnlevelCurcFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsTimeChangeNeedRpt
 功能描述  : 判断time变化时，是否需要上报AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
              VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2015年11月17日
    作    者   : h00360002
    修改内容   : 增加CTZE上报命令
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsTimeChangeNeedRpt(VOS_VOID)
{
    VOS_UINT32                              ulChkTimeCurcFlg;
    VOS_UINT32                              ulChkTimeUnsolicitedFlg;
    VOS_UINT32                              ulChkCtzvCurcFlg;
    VOS_UINT32                              ulChkCtzvUnsolicitedFlg;
    VOS_UINT32                              ulChkCtzeCurcFlg;
    VOS_UINT32                              ulChkCtzeUnsolicitedFlg;
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkTimeCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_TIME);

    ulChkTimeUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_TIME);

    ulChkCtzvCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CTZV);

    ulChkCtzvUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CTZV);

    ulChkCtzeCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CTZE);

    ulChkCtzeUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CTZE);

    /* TIME需要上报 */
    if ( (VOS_TRUE == ulChkTimeCurcFlg)
      && (VOS_TRUE == ulChkTimeUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* CTZV需要上报 */
    if ( (VOS_TRUE == ulChkCtzvCurcFlg)
      && (VOS_TRUE == ulChkCtzvUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* CTZE需要上报 */
    if ( (VOS_TRUE == ulChkCtzeCurcFlg)
      && (VOS_TRUE == ulChkCtzeUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsSimStaChangeNeedRpt
 功能描述  : 判断RSSI变化时，是否需要上报AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
              VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsSimStaChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg                 = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_SIMST);

    ulChkUnsolicitedRptFlg          = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_SIMST);

    /* simst需要上报 */
    if ( (VOS_TRUE == ulChkCurcRptFlg)
      && (VOS_TRUE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsRegRejChangeNeedRpt
 功能描述  : 判断是否需要主动上报Rej Info
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsRegRejChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl   = TAF_SDC_GetCurcRptCtrl();

    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_REJINFO))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsPlmnSelectInfoNeedRpt
 功能描述  : 判断是否上报Plmn Selection结果
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsPlmnSelectInfoNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl   = TAF_SDC_GetCurcRptCtrl();

    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_PLMNSELEINFO))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsRegStatusChangeNeedRpt
 功能描述  : 判断CREG/CEREG/CGREG变化时，是否需要上报AT
 输入参数  : pEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
             VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核新增函数

  2.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 消息接口变更
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsRegStatusChangeNeedRpt(
    TAF_PH_REG_STATE_STRU                  *pstRegState
)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    /* creg 需要上报 */
    if ( (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CREG))
      && (VOS_TRUE == pstRegState->OP_CsRegState) )
    {
        return VOS_TRUE;
    }

    /* cgreg 需要上报 */
    if ( (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CGREG))
      && (VOS_TRUE == pstRegState->OP_PsRegState) )
    {
        return VOS_TRUE;
    }

    /* cereg 需要上报 */
    if ( (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CEREG))
      && (VOS_TRUE == pstRegState->OP_PsRegState) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-9, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_GetRegDomain
 功能描述  : 开机时获取允许注册的服务域
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ue的ms mode
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核新增函数
  2.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8 TAF_MMA_GetRegDomain(VOS_VOID)
{
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enAllowedRegDomain;
    VOS_UINT8                                               ucAutoAttachFlg;
    NAS_NVIM_AUTOATTACH_STRU                            stAutoattachFlag;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stAutoattachFlag, 0x00, sizeof(NAS_NVIM_AUTOATTACH_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);
    if (NV_OK == NV_Read(en_NV_Item_Autoattach,
                         (VOS_VOID*)(&stAutoattachFlag),
                         ulLength))
    {
        if (NV_ITEM_ACTIVE == stAutoattachFlag.usAutoattachFlag)
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
        }
        else
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_DISABLE;
        }
    }
    else
    {
        ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
    }

    switch (g_StatusContext.ucModeService)
    {
        case TAF_PH_MS_CLASS_A:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS;

            if (MMA_AUTO_ATTACH_DISABLE == ucAutoAttachFlg)
            {
                 enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS;
            }
            break;

        case TAF_PH_MS_CLASS_CG:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS;

            if (MMA_AUTO_ATTACH_DISABLE == ucAutoAttachFlg)
            {
                enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL;
            }
            break;

        case TAF_PH_MS_CLASS_CC:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS;
            break;

        case TAF_PH_MS_CLASS_NULL:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL;
            break;

        default:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL;
            break;
    }

    return enAllowedRegDomain;
}
/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-9, end */
/*****************************************************************************
 函 数 名  : TAF_MMA_HexAlpha2AsciiString
 功能描述  : 转换网络名称编码格式
 输入参数  : VOS_UINT8 ulDestLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : L65478
    修改内容   : 新生成函数

*****************************************************************************/

 VOS_UINT32 TAF_MMA_HexAlpha2AsciiString(
    VOS_UINT32                      ulDestLength,
    VOS_UINT8                      *pucDst,
    VOS_UINT8                      *pucSrc,
    VOS_UINT16                      usSrcLen)
 {
    VOS_UINT16                     usLen;
    VOS_UINT16                     usChkLen;
    VOS_UINT8                     *pWrite = VOS_NULL_PTR;
    VOS_UINT8                     *pRead = VOS_NULL_PTR;
    VOS_UINT8                      ucHigh;
    VOS_UINT8                      ucLow;

    usLen       = 0;
    usChkLen    = 0;
    pWrite      = pucDst;
    pRead       = pucSrc;
    ucHigh      = 0;
    ucLow       = 0;

    if((2 * usSrcLen)>= ulDestLength)
    {
        TAF_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_HexAlpha2AsciiString too long");
        return 0;
    }
    /*lint -e961*/
    if(0 != usSrcLen)
    {
        /* 扫完整个字串 */
        while( usChkLen++ < usSrcLen )
        {
            ucHigh = 0x0F & (*pRead >> 4);
            ucLow = 0x0F & *pRead;

            usLen += 2;    /* 记录长度 */

            if(0x09 >= ucHigh)   /* 0-9 */
            {
                *pWrite++ = ucHigh + 0x30;
            }
            else if(0x0A <= ucHigh)    /* A-F */
            {
                *pWrite++ = ucHigh + 0x37;
            }
            else
            {
            }

            if(0x09 >= ucLow)   /* 0-9 */
            {
                *pWrite++ = ucLow + 0x30;
            }
            else if(0x0A <= ucLow)    /* A-F */
            {
                *pWrite++ = ucLow + 0x37;
            }
            else
            {
            }

             /* 下一个字符 */
            pRead++;
        }

    }
    /*lint +e961*/
    return usLen;
 }

/**********************************************************
 函 数 名  : TAF_MMA_DefaultAlphaToAscii
 功能描述  : 把默认字符转换成ASCII
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE : 转换成功
             VSO_FALSE: 转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年02月22日
    作    者   : l65478
    修改内容   : 新增函数
*************************************************************/
VOS_VOID TAF_MMA_DefaultAlphaToAscii(
    VOS_UINT8                          *pucDefAlpha,
    VOS_UINT8                           ucDefAlphaLen,
    VOS_UINT8                          *pucAsciiChar
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucPos;
    VOS_UINT16                          usDecode;

    for (ucLoop = 0; ucLoop < ucDefAlphaLen; ucLoop++)
    {
        ucPos           = 0x7f & pucDefAlpha[ucLoop];
        usDecode        = f_ausMnAsciiSfxDefAlpha[ucPos];
        /* 参考标杆:在单字节不能表示时,使用?进行代替 */
        if (usDecode > 0x00ff)
        {
            *pucAsciiChar = '?';
        }
        else
        {
            *pucAsciiChar = (VOS_UINT8)usDecode;
        }

        pucAsciiChar++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_TranslateNtwkName2Str
 功能描述  : 转换网络名称
 输入参数  : VOS_UINT8 *pIeNtwkName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : L65478
    修改内容   : 新生成函数
  2.日    期   : 2013年01月12日
    作    者   : l65478
    修改内容   : DTS2012011201289
  3.日    期   : 2013年02月28日
    作    者   : L65478
    修改内容   : DTS2013022200280:特殊字符显示错误
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  5.日    期   : 2013年10月11日
    作    者   : z00161729
    修改内容   : DTS2013071808373:TQE告警清理
  6.日    期   : 2015年01月07日
    作    者   : l00198894
    修改内容   : DTS2014102103988: ^MMPLMNINFO命令显示异常
  7.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_TranslateNtwkName2Str(
    TAF_SDC_OPERATOR_NAME_STRU      *pstIeNtwkName,
    VOS_CHAR                        *pucNtwkName,
    VOS_UINT32                       ulLen
)
{
    VOS_UINT8                       ucIeLen;
    VOS_UINT8                       ucCodScheme;
    VOS_UINT8                       uc7BitCharNum;
    VOS_UINT8                      *pTmpNtwkName;
    VOS_UINT8                      *pucDecodeNwName;
    VOS_UINT8                       ucSpareBit;

    VOS_UINT32                      ulRslt;

    /*lint -e961*/
    ucIeLen         = pstIeNtwkName->ucLength;
    /*lint +e961*/
    ucCodScheme     = pstIeNtwkName->bitCoding;
    /* 填充BIT */
    ucSpareBit      = pstIeNtwkName->bitSpare;
    pTmpNtwkName    = &pstIeNtwkName->aucOperatorName[0];

    if (0 == ucIeLen)
    {
        return VOS_FALSE;
    }

    if (ulLen == 0)
    {
        return VOS_FALSE;
    }

    if (0 == ucCodScheme)
    {
        /* 7Bit编码解析 */
        uc7BitCharNum   = (VOS_UINT8)(((ucIeLen) * 8) / 7);
        if (uc7BitCharNum < ulLen)
        {
            pucDecodeNwName = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMA, ulLen);
            if (VOS_NULL_PTR == pucDecodeNwName)
            {
                TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "TAF_MMA_TranslateNtwkName2Str: Alloc memory fail.");
                return VOS_FALSE;
            }

            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            ulRslt = TAF_STD_UnPack7Bit(pTmpNtwkName, uc7BitCharNum, 0, pucDecodeNwName);

            if (VOS_OK != ulRslt)
            {
                MMA_WARNINGLOG("TAF_MMA_TranslateNtwkName2Str: TAF_STD_UnPack7Bit Err.");
            }
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

            /* 有7个填充BIT,最后一个字节解码后的数据无效，需要把数据长度减1 */
            if ((ucSpareBit == 7) && (uc7BitCharNum > 0))
            {
                uc7BitCharNum -= 1;
            }
            TAF_MMA_DefaultAlphaToAscii(pucDecodeNwName, uc7BitCharNum, (VOS_UINT8 *)pucNtwkName);

            MMA_FREE_MEM(pucDecodeNwName);
            return VOS_TRUE;
        }
    }

    /* 为了方便应用对接，此处不再支持其他编码类型 */
    return VOS_FALSE;

}







/* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */

/* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

/* TAF_MMA_ReadSpnFile */



/*****************************************************************************
 函 数 名  : TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent
 功能描述  : 当前卡状态为USIMM_CARD_SERVIC_ABSENT，检测卡状态是否发生改变
 输入参数  : enPreSimStatus  -- 先前的卡状态
 输出参数  : 无
 返 回 值  : VOS_TRUE        -- 卡状态发生改变
              VOS_FALSE       -- 卡状态没有发生改变
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2014年2月27日
    作    者   : z00234330
    修改内容   : dts2014022402558,sim被puk锁定时,usim模块上报的invalid,usim没有上报
                卡状态在位时,sdc默认为卡invalid,这两种情况需要区分一下,否则使用
                at^cpin命令查询的会不正确。

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
)
{
    switch ( enPreSimStatus )
    {
        /* 当前SDC中卡状态是有效的，则不认为需要重启 */
        case TAF_SDC_USIM_STATUS_NO_PRESENT :
        case TAF_SDC_USIM_STATUS_SIM_PIN :
        case TAF_SDC_USIM_STATUS_SIM_PUK :
        case TAF_SDC_USIM_STATUS_NET_LCOK :
        case TAF_SDC_USIM_STATUS_IMSI_LCOK :
        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            return VOS_FALSE;

        /* 否则都需要重启 */
        default:
            return VOS_TRUE;
    }

}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable
 功能描述  : 当前卡状态为USIMM_CARD_SERVIC_ABSENT，检测卡状态是否发生改变
 输入参数  : enPreSimStatus  -- 先前的卡状态
 输出参数  : 无
 返 回 值  : VOS_TRUE        -- 卡状态发生改变
              VOS_FALSE       -- 卡状态没有发生改变
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
)
{
    switch ( enPreSimStatus )
    {
        /* 当前SDC中卡状态是有效的，则不认为需要重启 */
        case TAF_SDC_USIM_STATUS_VALID :
        case TAF_SDC_USIM_STATUS_CS_UNVALID :
        case TAF_SDC_USIM_STATUS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_ROMSIM :

            return VOS_FALSE;

        /* 否则都需要重启 */
        default:
            return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin
 功能描述  : 当前卡状态为USIMM_CARD_SERVIC_ABSENT，检测卡状态是否发生改变
 输入参数  : enPreSimStatus  -- 先前的卡状态
 输出参数  : 无
 返 回 值  : VOS_TRUE        -- 卡状态发生改变
              VOS_FALSE       -- 卡状态没有发生改变
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2013年8月30日
    作    者   : w00167002
    修改内容   : DTS2013082903145:双卡模式，设置PIN码后，用户解PIN后流程出错。
                  修改为:开机TAF的PID初始化时，设置SDC中当前卡的状态该为BUTT.
                  USIM模块给NAS上报卡状态则更新SDC中维护的卡状态。如果开机USIM
                  不上报卡状态，则设置当前卡状态为TAF_SDC_USIM_STATUS_UNVALID。

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
)
{
    switch ( enPreSimStatus )
    {
        /* 当前SDC中卡状态是有效的则认为改变，需要重启 */
        case TAF_SDC_USIM_STATUS_VALID :
        case TAF_SDC_USIM_STATUS_CS_UNVALID :
        case TAF_SDC_USIM_STATUS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_ROMSIM :

        case TAF_SDC_USIM_STATUS_BUTT:

            return VOS_TRUE;

        /* 否则都不需要重启 */
        default:
            return VOS_FALSE;
    }

}
/* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertMmaRatModeToMtc
 功能描述  : 将MMA的接入模式转换成MTC的接入模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
MTC_RATMODE_ENUM_UINT8 TAF_MMA_ConvertRatTypeToMtc(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType
)
{
    switch (enRatType)
    {
        case TAF_MMA_RAT_GSM:
            return MTC_RATMODE_GSM;

        case TAF_MMA_RAT_WCDMA:
            return MTC_RATMODE_WCDMA;

        case TAF_MMA_RAT_LTE:
            return MTC_RATMODE_LTE;

        case TAF_MMA_RAT_1X:
            return MTC_RATMODE_1X;

        case TAF_MMA_RAT_HRPD:
            return MTC_RATMODE_HRPD;

        default:
            return MTC_RATMODE_BUTT;
    }
}
#endif
/* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 函 数 名  : TAF_MMA_SetSimLockStatus
 功能描述  : 设置sim lock status
 输入参数  : ucSimLockStatus - sim lock状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MMA_SetSimLockStatus(VOS_UINT8 ucSimLockStatus)
{
    g_stMmaMePersonalisationStatus.SimLockStatus = ucSimLockStatus;

}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccEOPlmnSetCnf
 功能描述  : MMA模块收到MSCC模块发送的ID_MSCC_MMA_EOPLMN_SET_CNF
 输入参数  : MSCC_MMA_EOPLMN_SET_CNF_STRU         *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : s00190137
    修改内容   : 新生成函数
  2.日    期   : 2015年03月24日
    作    者   : K00902809
    修改内容   : Added structure TAF_MMA_EOPLMN_SET_CNF_STRU

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccEOPlmnSetCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_EOPLMN_SET_CNF_STRU        *pstEOPlmnSetCnf = VOS_NULL_PTR;
    MSCC_MMA_EOPLMN_SET_CNF_STRU       *pstMsccMsg      = VOS_NULL_PTR;

    pstMsccMsg   = (MSCC_MMA_EOPLMN_SET_CNF_STRU *)pstMsg;

    pstEOPlmnSetCnf = (TAF_MMA_EOPLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_EOPLMN_SET_CNF_STRU));

    if (VOS_NULL_PTR == pstEOPlmnSetCnf)
    {
        MN_ERR_LOG("TAF_MMA_RcvMsccEOPlmnSetCnf: Alloc Msg Failed!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstEOPlmnSetCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstEOPlmnSetCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstEOPlmnSetCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstEOPlmnSetCnf->ulResult               = pstMsccMsg->ulResult;
    pstEOPlmnSetCnf->usClientId             = MN_GetRealClientId(gstMmaValue.stEOPlmnSet.usClientId, WUEPS_PID_MMA);
    pstEOPlmnSetCnf->ucOpId                 = gstMmaValue.stEOPlmnSet.ucOpId;

    /* 填充消息头 */
    pstEOPlmnSetCnf->ulMsgName              = ID_TAF_MMA_EOPLMN_SET_CNF;

    PS_SEND_MSG(WUEPS_PID_MMA, pstEOPlmnSetCnf);

    return VOS_TRUE;
}


/* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-13, begin */

/*****************************************************************************
 函 数 名  : TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK
 功能描述  : 对DRV模块的DRV_PWRCTRL_SLEEPVOTE_UNLOCK进行封装。
 输入参数  : enPwcClientId:睡眠投票的client ID
 输出参数  : 无
 返 回 值  : PWC_PARA_INVALID
             PWC_SUCCESS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年5月29日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID  TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(
    PWC_CLIENT_ID_E                     enPwcClientId
)
{
   VOS_UINT32                           ulRslt;
   PWC_CLIENT_ID_E                      enClientId;

#if defined(INSTANCE_1)
    switch (enPwcClientId)
    {
        case PWRCTRL_SLEEP_NAS:
            enClientId = PWRCTRL_SLEEP_NAS_1;
            break;

        case PWRCTRL_SLEEP_FTM:
            enClientId = PWRCTRL_SLEEP_FTM_1;
            break;

        default:
            enClientId = enPwcClientId;
            break;
    }
#elif defined (INSTANCE_2)
    switch (enPwcClientId)
    {
        case PWRCTRL_SLEEP_NAS:
            enClientId = PWRCTRL_SLEEP_NAS_2;
            break;

        case PWRCTRL_SLEEP_FTM:
            enClientId = PWRCTRL_SLEEP_FTM_2;
            break;

        default:
            enClientId = enPwcClientId;
            break;
    }
#else
    enClientId = enPwcClientId;
#endif

    ulRslt = mdrv_pm_wake_unlock(enClientId);

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK:enClientId = %d\n", enClientId);
    }


    TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(ulRslt, enClientId);
}



/*****************************************************************************
 函 数 名  : TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK
 功能描述  : 对DRV模块的DRV_PWRCTRL_SLEEPVOTE_LOCK进行封装。
 输入参数  : enPwcClientId:睡眠投票的client ID
 输出参数  : 无
 返 回 值  : PWC_PARA_INVALID
             PWC_SUCCESS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年5月29日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID  TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(
    PWC_CLIENT_ID_E                     enPwcClientId
)
{
   VOS_UINT32                           ulRslt;
   PWC_CLIENT_ID_E                      enClientId;

#if defined(INSTANCE_1)

    switch (enPwcClientId)
    {
        case PWRCTRL_SLEEP_NAS:
            enClientId = PWRCTRL_SLEEP_NAS_1;
            break;

        case PWRCTRL_SLEEP_FTM:
            enClientId = PWRCTRL_SLEEP_FTM_1;
            break;

        default:
            enClientId = enPwcClientId;
            break;
    }
#elif defined (INSTANCE_2)
        switch (enPwcClientId)
        {
            case PWRCTRL_SLEEP_NAS:
                enClientId = PWRCTRL_SLEEP_NAS_2;
                break;

            case PWRCTRL_SLEEP_FTM:
                enClientId = PWRCTRL_SLEEP_FTM_2;
                break;

            default:
                enClientId = enPwcClientId;
                break;
        }
#else
    enClientId = enPwcClientId;
#endif

    ulRslt = mdrv_pm_wake_lock(enClientId);

    TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(ulRslt, enClientId);


    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK:enClientId = %d\n", enClientId);
    }

}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateSimRegStatus
 功能描述  : 更新SIM卡的reg状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月20日
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0和1
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSimRegStatus(VOS_VOID)
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    VOS_UINT32                          ulOldUsimValidStatus;
    VOS_UINT32                          ulNewUsimValidStatus;

    ulOldUsimValidStatus = TAF_SDC_IsUsimStausValid();
#endif

    enSimStatus = TAF_SDC_GetSimStatus();

    if ((TAF_SDC_USIM_STATUS_VALID  == enSimStatus)
     || (TAF_SDC_USIM_STATUS_ROMSIM == enSimStatus))
    {
        TAF_SDC_SetSimCsRegStatus(VOS_TRUE);
        TAF_SDC_SetSimPsRegStatus(VOS_TRUE);
    }
    else
    {
        TAF_SDC_SetSimCsRegStatus(VOS_FALSE);
        TAF_SDC_SetSimPsRegStatus(VOS_FALSE);
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    ulNewUsimValidStatus = TAF_SDC_IsUsimStausValid();

    /* 如果cs ps卡状态发生改变需要通知mtc */
    if (ulOldUsimValidStatus != ulNewUsimValidStatus)
    {
        TAF_MMA_SndMtcRegStatusInd((VOS_UINT8)ulNewUsimValidStatus);
    }
#endif

    return;
}

/* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-13, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_ReportSrvStatus
 功能描述  : MMA Report Service Status
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月31日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReportSrvStatus(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enSrvStatus;

    /* 判断是否需要主动上报服务状态 */
    if (VOS_FALSE == TAF_MMA_IsServStatusChangeNeedRpt())
    {
        return;
    }

    enSrvStatus = TAF_SDC_GetServiceStatus();

    TAF_MMA_SndSrvStatusInd(enSrvStatus);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_StartNetScanProtectTimer
 功能描述  : 启动NetScan请求保护定时器
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月23日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_StartNetScanProtectTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_OK;

    /* 定时器不在运行，则开启定时器 */
    if (MMA_TIMER_RUN != g_stNetScanProtectTimer.ucTimerStatus)
    {
        ulRet = NAS_StartRelTimer(&g_stNetScanProtectTimer.MmaHTimer,
                                  WUEPS_PID_MMA,
                                  TI_TAF_MMA_NET_SCAN_TIMER_LEN,
                                  TAF_MMA,
                                  TI_TAF_MMA_NET_SCAN_TIMER,
                                  VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_NetScanProtectTimerProc():ERROR:Start TI_TAF_MMA_PNN_LIST_MEM_PROTECT_TIMER Timer Error!");
        }
        else
        {
            g_stNetScanProtectTimer.ucTimerStatus = MMA_TIMER_RUN;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_StopNetScanProtectTimer
 功能描述  : 停止NetScan请求保护定时器
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月23日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_StopNetScanProtectTimer(VOS_VOID)
{
    /* 定时器不处于停止状态，则停止定时器 */
    if ( MMA_TIMER_RUN == g_stNetScanProtectTimer.ucTimerStatus )
    {
        (VOS_VOID)NAS_StopRelTimer(WUEPS_PID_MMA,
                                 TI_TAF_MMA_NET_SCAN_TIMER,
                                 &(g_stNetScanProtectTimer.MmaHTimer));
        /*设置停止定时器标志*/
        g_stNetScanProtectTimer.ucTimerStatus = MMA_TIMER_STOP;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_StartAbortNetScanProtectTimer
 功能描述  : 开启ABORT NetScan请求保护定时器
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : 成功启动则返回VOS_OK;
             否则返回失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月05日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_StartAbortNetScanProtectTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_OK;

    /* 开启定时器 */
    if (MMA_TIMER_RUN != g_stAbortNetScanProtectTimer.ucTimerStatus)
    {
        ulRet = NAS_StartRelTimer(&g_stAbortNetScanProtectTimer.MmaHTimer,
                                  WUEPS_PID_MMA,
                                  TI_TAF_MMA_ABORT_NET_SCAN_TIMER_LEN,
                                  TAF_MMA,
                                  TI_TAF_MMA_ABORT_NET_SCAN_TIMER,
                                  VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_AbortNetScanProtectTimerProc():ERROR:Start TI_TAF_MMA_ABORT_NET_SCAN_TIMER Timer Error!");
        }
        else
        {
            g_stAbortNetScanProtectTimer.ucTimerStatus = MMA_TIMER_RUN;
        }
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_StopAbortNetScanProtectTimer
 功能描述  : 停止ABORT NetScan请求保护定时器
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月05日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_StopAbortNetScanProtectTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_OK;

    /* 如果该定时器处于运行状态，则停止 */
    if ( MMA_TIMER_RUN == g_stAbortNetScanProtectTimer.ucTimerStatus )
    {
        ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                 TI_TAF_MMA_ABORT_NET_SCAN_TIMER,
                                 &(g_stAbortNetScanProtectTimer.MmaHTimer));
        if (VOS_OK != ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_AbortNetScanProtectTimerProc():WARNING:NAS_StopRelTimer failed");
        }

        /*设置停止定时器标志*/
        g_stAbortNetScanProtectTimer.ucTimerStatus = MMA_TIMER_STOP;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_NetScanTimerExpired
 功能描述  : 定时器TI_TAF_MMA_NET_SCAN_TIMER超时处理函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_NetScanTimerExpired(VOS_VOID)
{
    TAF_MMA_StopNetScanProtectTimer();

    /* 给MSCC发送停止扫描请求 */
    TAF_MMA_SndMsccAbortNetScanMsgReq();

    (VOS_VOID)TAF_MMA_StartAbortNetScanProtectTimer();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_AbortNetScanTimerExpired
 功能描述  : 定时器TI_TAF_MMA_ABORT_NET_SCAN_TIMER超时处理函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年03月25日
    作    者   : K00902809
    修改内容   : Sending cnf message to AT instead of using MN_PH_SendMsg

*****************************************************************************/
VOS_VOID TAF_MMA_AbortNetScanTimerExpired(VOS_VOID)
{
    TAF_MMA_NET_SCAN_RESULT_ENUM_UINT8  enResult;
    TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf = VOS_NULL_PTR;;

    enResult               = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    enCause                = TAF_MMA_NET_SCAN_CAUSE_TIMER_EXPIRED;

    pstNetScanCnf = (TAF_MMA_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_NET_SCAN_CNF_STRU));
    if (VOS_NULL_PTR == pstNetScanCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstNetScanCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    TAF_MMA_StopAbortNetScanProtectTimer();

    /* 填充消息头 */
    pstNetScanCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstNetScanCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstNetScanCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulMsgName              = ID_TAF_MMA_NET_SCAN_CNF;

    pstNetScanCnf->usClientId             = gstMmaValue.stNetScan.usClientId;
    pstNetScanCnf->ucOpId                 = gstMmaValue.stNetScan.ucOpId;
    pstNetScanCnf->enResult               = enResult;
    pstNetScanCnf->enCause                = enCause;

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstNetScanCnf);

    return;
}



#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertRatModeToMtc
 功能描述  : 将接入技术转换为mtc类型
 输入参数  : enSysMode   - 系统模式
             enUtranMode - utran模式
 输出参数  : pucRatMode  - 转换后mtc接入模式类型
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月22日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertRatModeToMtc(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode,
    MTC_RATMODE_ENUM_UINT8             *pucRatMode
)
{
    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            *pucRatMode = MTC_RATMODE_GSM;
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
            {
                *pucRatMode = MTC_RATMODE_WCDMA;
            }
            else
            {
                *pucRatMode = MTC_RATMODE_TDS;
            }
            break;

        case TAF_SDC_SYS_MODE_LTE:
            *pucRatMode = MTC_RATMODE_LTE;
            break;
        default:
            *pucRatMode = MTC_RATMODE_BUTT;
            break;
    }

    return;
}

#endif

/* Added by w00167002 for L-C互操作项目, 2014-2-17, begin */

/*****************************************************************************
 函 数 名  : TAF_MMA_BuildMmaCtrlInfo
 功能描述  : 构建MMA的消息标识CTRL信息
 输入参数  : VOS_UINT32                          ulModuleId,
             VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
 输出参数  : pstCtrlInfo  - 构建的目标信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_BuildMmaCtrlInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CTRL_STRU                  *pstCtrlInfo
)
{
    pstCtrlInfo->ulModuleId = ulModuleId;
    pstCtrlInfo->usClientId = usClientId;
    pstCtrlInfo->ucOpId     = ucOpId;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsPowerOnCLInterWork
 功能描述  : MMA判断当前是否是开机后的CL互操作模式
 输入参数  : 无
 输出参数  : VOS_TRUE       - 是开机后的CL互操作模式
             VOS_FALSE      - 是非开机后的CL互操作模式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsPowerOnCLInterWork(VOS_VOID)
{
    /* 当前NV配置为非CL互操作模式 */
    if (VOS_FALSE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        return VOS_FALSE;
    }


    /* 模式设置状态机在运行,则返回VOS_TRUE */
    if (TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
    {
        return VOS_TRUE;
    }

    /* 模式状态机不在运行且当前不为开机模式，则返回VOS_FALSE */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        return VOS_FALSE;
    }

    /* 当前为开机模式，则返回VOS_TRUE */
    return VOS_TRUE;
}

/* Added by w00167002 for L-C互操作项目, 2014-2-17, end */

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-27, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : MMA_MTC_ConvertCardStatus
 功能描述  : 将USIM的卡状态转换为MTC格式
 输入参数  : enCardStatus        - USIM上报的卡状态
 输出参数  : penDestCardStatus   - MMA报给MTC的卡状态
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月03日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MMA_MTC_ConvertCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32           enCardStatus,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16  *penDestCardStatus
)
{
    switch(enCardStatus)
    {
        case USIMM_CARD_SERVIC_ABSENT:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
            break;

        case USIMM_CARD_SERVIC_UNAVAILABLE:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_UNAVAILABLE;
            break;

        case USIMM_CARD_SERVIC_SIM_PIN:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_SIM_PIN;
            break;

        case USIMM_CARD_SERVIC_SIM_PUK:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_SIM_PUK;
            break;

        case USIMM_CARD_SERVIC_NET_LCOK:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_NET_LCOK;
            break;

        case USIMM_CARD_SERVICE_IMSI_LOCK:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_IMSI_LCOK;
            break;

        case USIMM_CARD_SERVIC_AVAILABLE:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_AVAILABLE;
            break;

        default:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
            break;
    }

    return VOS_TRUE;
}
#endif
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-27, End */

#if (FEATURE_ON == FEATURE_BASTET)
/*****************************************************************************
 函 数 名  : TAF_MMA_SndBastetRatModeInd
 功能描述  : MMA模块通知Bastet模块当前系统接入模式
 输入参数  : enSysMode--网络制式
            enUtranMode--TDD或者FDD模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : z00128442
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndBastetRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8  enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    MMA_BASTET_RAT_MODE_IND_STRU       *pstRatMode = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstRatMode = (MMA_BASTET_RAT_MODE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_BASTET_RAT_MODE_IND_STRU));
    if( VOS_NULL_PTR == pstRatMode )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetRatModeInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRatMode + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_BASTET_RAT_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstRatMode->stMsgHeader.ulReceiverPid   = UEPS_PID_BASTET;
    pstRatMode->stMsgHeader.ulMsgName       = ID_MMA_BASTET_RAT_MODE_IND;

    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstRatMode->enRatMode = BST_RATMODE_GSM;
            break;
        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
            {
                pstRatMode->enRatMode = BST_RATMODE_WCDMA;
            }
            else
            {
                pstRatMode->enRatMode = BST_RATMODE_TDS;
            }
            break;
        case TAF_SDC_SYS_MODE_LTE:
            pstRatMode->enRatMode = BST_RATMODE_LTE;
            break;
        default:
            pstRatMode->enRatMode = BST_RATMODE_BUTT;
            break;
    }

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstRatMode);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetRatModeInd: Send Msg Failed!");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndBastetCsServiceInd
 功能描述  : MMA模块通Bastet模块当前CS连接状态
 输入参数  : bCSConnected   PS_TRUE  存在CS连接， PS_FALSE 不存在CS连接
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : z00128442
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndBastetCsServiceInd(PS_BOOL_ENUM_UINT8 bCSConnected)
{
    MMA_BASTET_CS_SERVICE_IND_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstMsg = (MMA_BASTET_CS_SERVICE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_BASTET_CS_SERVICE_IND_STRU));
    if( VOS_NULL_PTR == pstMsg )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetCsServiceInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_BASTET_CS_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_BASTET;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMA_BASTET_CS_SERVICE_IND;
    pstMsg->bCSConnected                = bCSConnected;

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetCsServiceInd: Send Msg Failed!");
    }

    return;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndBastetServiceStatusInd
 功能描述  : MMA模块通Bastet模块当前服务状态
 输入参数  : bInservice   VOS_TRUE  有服务， VOS_FALSE没  有服务
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : z00128442
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndBastetServiceStatusInd(VOS_VOID)
{
    MMA_BASTET_SERVICE_STATUS_IND_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;


    pstMsg = (MMA_BASTET_SERVICE_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_BASTET_SERVICE_STATUS_IND_STRU));
    if( VOS_NULL_PTR == pstMsg )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetServiceStatusInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_BASTET_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_BASTET;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMA_BASTET_SERVICE_STATUE_IND;

    if(NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        pstMsg->bCsInservice            = PS_TRUE;
    }
    else
    {
        pstMsg->bCsInservice            = PS_FALSE;
    }


    if(NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetPsServiceStatus())
    {
        pstMsg->bPsInservice            = PS_TRUE;
    }
    else
    {
        pstMsg->bPsInservice            = PS_FALSE;
    }
    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetServiceStatusInd: Send Msg Failed!");
    }

    return;

}

#endif


#if (FEATURE_LTE == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_MMA_GetRssiLevelFromLteRssi
 功能描述  : 将LTE下的RSSI参数转换成等级表示的信号强度
 输入参数  : enCardStatus        - USIM上报的卡状态
 输出参数  : penDestCardStatus   - MMA报给MTC的卡状态
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月05日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetRssiLevelFromLteRssi(
    VOS_INT16                           usLteRssi,
    VOS_UINT8                          *pucRssiLevel
)
{
    /* 与atSetCsqCnfSameProc处理相同 */
    if(TAF_PH_RSSIUNKNOW == usLteRssi)
    {
        *pucRssiLevel =  TAF_PH_RSSIUNKNOW;
    }
    else if(usLteRssi >= TAF_PH_RSSI_HIGH)
    {
        *pucRssiLevel = TAF_PH_CSQ_RSSI_HIGH;
    }
    else if(usLteRssi <= TAF_PH_RSSI_LOW)
    {
        *pucRssiLevel = TAF_PH_CSQ_RSSI_LOW;
    }
    else
    {
        *pucRssiLevel = (VOS_UINT8)((usLteRssi -TAF_PH_RSSI_LOW) / 2);
    }

    return;
}
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_MMA_QueryCdma1xSysInfo
 功能描述  : CDMA 1X网络环境下^sysinfo命令查询上报
 输入参数  : TAF_MMA_CTRL_STRU                  *pstCtrl,
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : g00261581
    修改内容   : 新生成函数
  2.日    期   : 2015年3月28日
    作    者   : g00261581
    修改内容   : 消息接口重构
  3.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 修改
*****************************************************************************/
VOS_VOID TAF_MMA_QueryClSysInfo(
    TAF_PH_SYSINFO_STRU                *pstSysInfo
)
{
    VOS_UINT32                          ulPinStatus;

    ulPinStatus = MMA_CheckPin1SatusSimple();
    /* 获取系统Mode SubMode */


    MN_PH_GetSysInfoSysModeEx(pstSysInfo);


    /* 获取漫游标志 */
    if (TAF_SDC_SYS_ROAMING_STATUS_OFF == TAF_SDC_GetApp1xRoamingFlag())
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_NONE_ROMAING;
    }
    else
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROMAING;

    }

    pstSysInfo->ucSrvStatus  = TAF_SDC_GetAppServiceStatus();

    pstSysInfo->ucSrvDomain  = TAF_SDC_GetAppServiceDomain();

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetCsimStatus())
    {
        MMA_WARNINGLOG("TAF_MMA_QueryClSysInfo: Csim Status Absent!");
    }

    MN_PH_GetSysInfoSrvStatus(pstSysInfo, TAF_SDC_GetCsimStatus());

    /* 需要PIN码时漫游状态显示为未知 */
    if (MMA_NONEED_PIN1 != ulPinStatus)
    {
        pstSysInfo->ucSrvDomain  = TAF_PH_INFO_NO_DOMAIN;
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROAM_UNKNOW;
    }

    if (MMA_SIM_IS_LOCK == MMA_GetCsimMeLockStatus())
    {
        pstSysInfo->ucSimLockStatus = VOS_TRUE;
    }
    else
    {
        pstSysInfo->ucSimLockStatus = VOS_FALSE;
    }

    if (MMA_PUK1_REMAINS_ZERO == ulPinStatus)
    {
        pstSysInfo->ucSimStatus = TAF_PH_USIM_STATUS_UNAVAIL;
    }
    else
    {
        pstSysInfo->ucSimStatus = MMA_GetCsimStatus(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Report1xCregStatus
 功能描述  : 1X模式下注册状态上报，1x只上报CS域注册状态，ap侧收到后，会自动转为CS+PS
 输入参数  : NAS_MSCC_PIF_REG_STATE_ENUM_UINT8        enRegState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   : g00261581
    修改内容   : 新生成函数
  2.日    期   : 2015年2月11日
    作    者   : w00208541
    修改内容   : CDMA Iteration 8 删掉一行无效代码
  3.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 修改
*****************************************************************************/
VOS_VOID TAF_MMA_Report1xCregStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
)
{
    TAF_PH_REG_STATE_STRU               stRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppNetCsRegStatus;

    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    /* CS域状态变化后，才会上报Creg AT命令 */
    if (enRegState == TAF_SDC_GetCsRegStatus())
    {
        return;
    }

    TAF_SDC_SetCsRegStatus(enRegState);

    stRegStatus.OP_CsRegState = VOS_TRUE;
    stRegStatus.OP_ucAct      = VOS_TRUE;
    stRegStatus.RegState      = enRegState;
    stRegStatus.ucAct         = TAF_PH_ACCESS_TECH_CDMA_1X;

    enNetCsRegStatus    = TAF_SDC_GetCsRegStatus();
    enAppNetCsRegStatus = TAF_SDC_GetAppCsRegStatus();

    /*比较stNetworkInfo和stAppNetworkInfo中CS注册信息是否一致，不一致需要上报*/
    if (enNetCsRegStatus != enAppNetCsRegStatus)
    {
        /*判断是否需要延迟上报*/
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportCsRegStatusInClMode())
        {
            /* CS注册状态需要上报，并且需要延时 */

            /* AT命令延时上报，勾包 */
            TAF_MMA_LogDelayReportInfo(TAF_MMA_LOG_DELAY_RPT_CREG);

            /* 延时上报定时器启动，此处如果定时器已经启动，不需要重新启动,此函数中有判断  */
            TAF_MMA_StartTimer(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
                                (TAF_MMA_GetCLDelayReptSrvStatusTimerLen()));
        }
        else /* CS注册状态需要上报，但不需要延时 */
        {
            /* 服务状态不允许停止定时器，此时服务状态变化方向:有服务-->无服务或有服务，需要延时上报,
               暂时不上报CS域注册状态，等定时器超时后再一起上报,保持一致 */
            if (VOS_TRUE == TAF_MMA_IsNeedDelayReportServiceStatusInClMode())
            {
                return;
            }

            /*无注册->有注册,或home、roam变更，立即上报*/
            if (VOS_TRUE == TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
            {
                TAF_MMA_SndRegStatusInd(&stRegStatus);
            }

            /* 更新CS域注册状态到APP */
            TAF_SDC_SetAppCsRegStatus(TAF_SDC_GetCsRegStatus());

            TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }
    }
    else
    {
        /* 服务状态不允许停止定时器，此时服务状态变化方向:有服务-->无服务或有服务，需要延时上报,
            暂时不上报CS域注册状态，等定时器超时后再一起上报,保持一致 */
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportServiceStatusInClMode())
        {
            return;
        }

        /*有注册变为无注册，延迟上报定时器启动时，又变回有注册的情况*/
        TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    }

    return;
}

/*****************************************************************************
Function Name   :   TAF_MMA_UpdateHrpdServiceStatusAndDomain
Description     :   update service domain and status
Input parameters:   enCsServiceStatus ----- cs service status
Outout parameters:
Return Value    :   None

Modify History  :
1)  Date           : 2015-02-16
    Author         : w00208541
    Modify content : Create
2)  Date           : 2015-10-14
    Author         : j00354216
    Modify content : CDMA Iteration 18修改
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateHrpdServiceStatusAndDomain(
    TAF_SDC_SYS_MODE_ENUM_UINT8                 enSysMode,
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32    enHrpdSrvSta
)
{
    /* update ps servcie status*/
    if (MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE == enHrpdSrvSta)
    {
        TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE);
    }
    else
    {
        TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_NO_SERVICE);
    }

    /* update servcie domain */
    TAF_MMA_UpdateServiceDomainInClMode(enSysMode);

    /*  CS域和PS域服务状态，只要有一个是由服务，总服务状态就是有服务 */
    TAF_MMA_UpdateReportService();

}

/*****************************************************************************
Function Name   :   TAF_MMA_Report1xServiceState
Description     :   update service domain and status
Input parameters:   None

Outout parameters:  None
Return Value    :   None

Modify History  :
  1.日    期   : 2015年2月16日
    作    者   : w00208541
    修改内容   : 新增
  2.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 修改,函数名修改，体现是1x的服务状态上报，与hrpd区分
*****************************************************************************/
VOS_VOID TAF_MMA_Report1xServiceState(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNetSrvStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppNetSrvStatus;

    enNetSrvStatus    = TAF_SDC_GetServiceStatus();
    enAppNetSrvStatus = TAF_SDC_GetAppServiceStatus();

    /*比较stNetworkInfo与stAppNetworkInfo服务状态是否一致，不一致需要上报*/
    if (enNetSrvStatus != enAppNetSrvStatus)
    {
        /*判断是否需要延迟上报*/
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportServiceStatusInClMode())
        {
            /* 需要上报服务状态，并且需要延时上报的场景 */

            /* AT命令延时上报，勾包 */
            TAF_MMA_LogDelayReportInfo(TAF_MMA_LOG_DELAY_RPT_SRVST);

            /* 延时上报定时器启动，此处如果定时器已经启动，不需要重新启动,此函数中有判断  */
            TAF_MMA_StartTimer(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
                                (TAF_MMA_GetCLDelayReptSrvStatusTimerLen()));
        }
        else /* 服务状态需要上报 但不需要延时上报 */
        {
            /* CS域注册状态不允许停止定时器，此时服务状态变化方向:已注册-->未注册，需要延时上报,
                暂时不上报服务，等定时器超时后再一起上报,保持一致 */
            if (VOS_TRUE == TAF_MMA_IsNeedDelayReportCsRegStatusInClMode())
            {
                return;
            }

            /* 上报总服务状态 */
            TAF_MMA_ReportSrvStatus();
            /* 更新服务状态到APP */
            TAF_SDC_SetAppServiceStatus(TAF_SDC_GetServiceStatus());

            /* 停止CS域定时器 */
            TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);

        }
    }
    else  /* 不需要上报服务状态的场景，停CS域延时上报定时器 */
    {
        /* CS域注册状态不允许停止定时器，此时服务状态变化方向:已注册-->未注册，需要延时上报,
           暂时不上报服务，等定时器超时后再一起上报,保持一致 */
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportCsRegStatusInClMode())
        {
            return;
        }

        /*有服务变为无服务，延迟上报定时器启动时，又变回有服务的情况*/
        TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    }

    return;
}

/*****************************************************************************
Function Name   :   TAF_MMA_ReportHrpdAndLteServiceState
Description     :   根据LTE或hRPD的服务状态变化，更新总服务状态，并检查是否需要延时上报
Input parameters:   None
Outout parameters:  None
Return Value    :   None

Modify History  :
  1.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 新增，体现是hrpd服务状态上报，与1x的区分
*****************************************************************************/
VOS_VOID TAF_MMA_ReportHrpdAndLteServiceState(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNetSrvStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppNetSrvStatus;

    enNetSrvStatus    = TAF_SDC_GetServiceStatus();
    enAppNetSrvStatus = TAF_SDC_GetAppServiceStatus();

    /*比较stNetworkInfo与stAppNetworkInfo服务状态是否一致，不一致需要上报*/
    if (enNetSrvStatus != enAppNetSrvStatus)
    {
        /*判断是否需要延迟上报*/
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportServiceStatusInClMode())
        {
            /* 需要上报服务状态，并且需要延时上报的场景 */

            /* AT命令延时上报，勾包 */
            TAF_MMA_LogDelayReportInfo(TAF_MMA_LOG_DELAY_RPT_SRVST);

            /* 延时上报定时器启动，此处如果定时器已经启动，不需要重新启动,此函数中有判断  */
            TAF_MMA_StartTimer(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
                                    (TAF_MMA_GetCLDelayReptSrvStatusTimerLen()));
        }
        else /* 服务状态需要上报 但不需要延时上报 */
        {
            /* PS域注册状态不允许停止定时器，此时服务状态变化方向:已注册-->未注册，需要延时上报,
                暂时不上报服务，等定时器超时后再一起上报,保持一致 */
            if (VOS_TRUE == TAF_MMA_IsNeedDelayReportPsRegStatusInClMode())
            {
                return;
            }

            /* 上报总服务状态 */
            TAF_MMA_ReportSrvStatus();
            /* 更新服务状态到APP */
            TAF_SDC_SetAppServiceStatus(TAF_SDC_GetServiceStatus());

            /* 停止PS域延时上报定时器 */
            TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }
    }
    else  /* 不需要上报服务状态的场景，尝试停止PS域定时器 */
    {
        /* PS域注册状态不允许停止定时器，此时服务状态变化方向:已注册-->未注册，需要延时上报,
          暂时不上报服务，等定时器超时后再一起上报,保持一致 */
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportPsRegStatusInClMode())
        {
            return;
        }

        TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Updates1xServiceStatusAndDomain
 功能描述  : 更新服务状态、域状态
 输入参数  : enCsServiceStatus ----- cs服务状态
             enSysMode         ----- 系统模式
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月2日
    作    者   : g00261581
    修改内容   : 新生成函数
  2.日    期   : 2015年2月11日
    作    者   : w00208541
    修改内容   : CDMA Iteration 8 规一化1x 和 hrpd
  3.日    期   : 2015年10月14日
    作    者   : l00324781
    修改内容   : CDMA Iteration 18
*****************************************************************************/
VOS_VOID TAF_MMA_Update1xServiceStatusAndDomain(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus,
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    /* update cs servcie status*/
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
    {
        TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE);
    }
    else if(TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus)
    {
        TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_NO_SERVICE);
    }

    /* update servcie domain */
    TAF_MMA_UpdateServiceDomainInClMode(enSysMode);


    /* 总服务状态更新，从TAF_MMA_ReportCdmaServiceStateBasedOn1x中挪入此处 */
    /* process new SrvSta */
    TAF_MMA_UpdateReportService();

}



/*****************************************************************************
 函 数 名  : TAF_MMA_ReportCSid
 功能描述  : CDMA 1X网络环境下^CSID命令查询上报
 输入参数  : VOS_UINT16                          usSid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_ReportCSid(
    VOS_INT32                          lSid
)
{
    TAF_MMA_CSID_IND_STRU              *pstCSidInd;

    pstCSidInd = (TAF_MMA_CSID_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_CSID_IND_STRU));
    if (VOS_NULL_PTR == pstCSidInd)
    {
        MMA_ERRORLOG("TAF_MMA_ReportCSidNid: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCSidInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CSID_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    TAF_MMA_CFG_MSG_HDR(pstCSidInd,
                        WUEPS_PID_AT,
                        ID_TAF_MMA_CSID_IND);
    pstCSidInd->stCtrl.usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstCSidInd->stCtrl.ucOpId        = MMA_OP_ID_INTERNAL;
    pstCSidInd->lSid                 = lSid;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCSidInd);

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_Report1xEmcCallBack
 功能描述  : mma 上报给APP callback模式
 输入参数  : ulIsInCallBack 是否处于emc callback模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_Report1xEmcCallBack(
    VOS_UINT32                          ulIsInCallBack
)
{
    TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU  *pstEmcCallBack;

    pstEmcCallBack = (TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU));
    if (VOS_NULL_PTR == pstEmcCallBack)
    {
        MMA_ERRORLOG("TAF_MMA_Report1xEmcCallBack: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstEmcCallBack + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    TAF_MMA_CFG_MSG_HDR(pstEmcCallBack,
                        WUEPS_PID_AT,
                        ID_TAF_MMA_1X_EMC_CALL_BACK_NTF);
    pstEmcCallBack->stCtrl.usClientId               = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstEmcCallBack->stCtrl.ucOpId                   = MMA_OP_ID_INTERNAL;
    pstEmcCallBack->ulIsInCallBack                  = ulIsInCallBack;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstEmcCallBack);

    return;
}


VOS_VOID TAF_MMA_ConvertSysSubModeToActForAtCmdCgreg(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode,
    TAF_PH_ACCESS_TECH_ENUM_UINT8      *pucAct
)
{
    switch (enSysSubMode)
    {
        case TAF_SYS_SUBMODE_EVDO_REL_A:
        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_A:
            *pucAct = TAF_PH_ACCESS_TECH_EVDO;
            break;

        default:
            *pucAct = TAF_PH_ACCESS_TECH_BUTT;
            break;
    }

}

VOS_VOID TAF_MMA_ReportPsRegStatusInClMode(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetPsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppNetPsRegStatus;

    if (enRegState == TAF_SDC_GetPsRegStatus())
    {
        /* no change no report */
        return;
    }

    /* set report values */
    TAF_SDC_SetPsRegStatus(enRegState);

    enNetPsRegStatus    = TAF_SDC_GetPsRegStatus();
    enAppNetPsRegStatus = TAF_SDC_GetAppPsRegStatus();

    /*比较stNetworkInfo和stAppNetworkInfo中PS注册信息是否一致，不一致需要上报*/
    if (enNetPsRegStatus != enAppNetPsRegStatus)
    {
        /*判断是否需要延迟上报*/
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportPsRegStatusInClMode())
        {
            /* AT命令延时上报，勾包 */
            TAF_MMA_LogDelayReportInfo(TAF_MMA_LOG_DELAY_RPT_CGREG);

            /* 延时上报定时器启动，此处如果定时器已经启动，不需要重新启动,此函数中有判断  */
            TAF_MMA_StartTimer(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
                                    (TAF_MMA_GetCLDelayReptSrvStatusTimerLen()));
        }
        else /* PS域注册状态需要上报 但不需要延时上报 */
        {
            /* 服务状态不允许停止定时器，此时服务状态变化方向:有服务-->无服务或有服务，需要延时上报,
                暂时不上报PS域注册状态，等定时器超时后再一起上报,保持一致 */
            if (VOS_TRUE == TAF_MMA_IsNeedDelayReportServiceStatusInClMode())
            {
                return;
            }
            /*无注册->有注册,立即上报*/
            /* PS域注册状态上报 */
            TAF_MMA_SndPsRegStatusInClMode();

            /* 更新PS域注册状态到APP */
            TAF_SDC_SetAppPsRegStatus(TAF_SDC_GetPsRegStatus());

            /* 停止PS域定时器 */
            TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }
    }
    else
    {
        /* 服务状态不允许停止定时器，此时服务状态变化方向:有服务-->无服务或有服务，需要延时上报,
           暂时不上报PS域注册状态，等定时器超时后再一起上报,保持一致 */
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportServiceStatusInClMode())
        {
            return;
        }

        /*有注册变为无注册，延迟上报定时器启动时，又变回有注册的情况*/
        TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsSidChangeNeedRpt
 功能描述  : 判断SID 变化时，是否需要上报AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
             VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsSidChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg                 = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CSID);

    ulChkUnsolicitedRptFlg          = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSID);

    /* CURC和^CSID都设置为主动上报打开时，才需要上报 */
    if ( (VOS_FALSE == ulChkCurcRptFlg)
     ||  (VOS_FALSE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsClocinfoChangeNeedRpt
 功能描述  : 判断SID NID或BSID 变化时，是否需要上报AT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要上报
             VOS_FALSE:不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月8日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsClocinfoChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg                 = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CLOCINFO);

    ulChkUnsolicitedRptFlg          = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CLOCINFO);

    /* CURC和^CLOCINFO都设置为主动上报打开时，才需要上报 */
    if ( (VOS_FALSE == ulChkCurcRptFlg)
     ||  (VOS_FALSE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReportClocinfo
 功能描述  : CDMA 网络的地址信息发生变化时，上报变化后的CDMA 网络的地址信息
 输入参数  : TAF_MMA_CLOCINFO_PARA_STRU     *pstClocinfo  CDMA 网络的地址信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月28日
    作    者   : l00359089
    修改内容   : 新生成函数 FOR DTS2015120703071
*****************************************************************************/
VOS_VOID TAF_MMA_ReportClocinfo(
    TAF_MMA_CLOCINFO_PARA_STRU     *pstClocinfoPara
)
{
    TAF_MMA_CLOCINFO_IND_STRU          *pstClocinfoInd = VOS_NULL_PTR;

    pstClocinfoInd = (TAF_MMA_CLOCINFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                               sizeof(TAF_MMA_CLOCINFO_IND_STRU));
    if (VOS_NULL_PTR == pstClocinfoInd)
    {
        MMA_ERRORLOG("TAF_MMA_ReportClocinfo: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstClocinfoInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CLOCINFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstClocinfoInd->ulSenderPid         = WUEPS_PID_MMA;
    pstClocinfoInd->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstClocinfoInd->ulReceiverPid       = WUEPS_PID_AT;
    pstClocinfoInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstClocinfoInd->ulLength            = sizeof(TAF_MMA_CLOCINFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstClocinfoInd->enMsgId             = ID_TAF_MMA_CLOCINFO_IND;

    pstClocinfoInd->stCtrl.usClientId   = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_MMA);
    pstClocinfoInd->stCtrl.ucOpId       = MMA_OP_ID_INTERNAL;
    PS_MEM_CPY(&pstClocinfoInd->stClocinfoPara, pstClocinfoPara, sizeof(TAF_MMA_CLOCINFO_PARA_STRU));

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_MMA, pstClocinfoInd);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPrefPlmnParaType
 功能描述  : 获取plmn类型
 输入参数  : MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
 输出参数  : 无
 返 回 值  : MMC_MMA_PARA_TYPE_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月09日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
MMC_MMA_PARA_TYPE_ENUM TAF_MMA_GetPrefPlmnParaType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
)
{
    if (MN_PH_PREF_PLMN_UPLMN == enPrefPLMNType)
    {
        if (VOS_TRUE == MN_PH_IsUsingPlmnSel())
        {
            return EN_MMC_PLMNSEL_INFO;
        }
        else
        {
            return EN_MMC_UPLMN_INFO;
        }
    }
    else if (MN_PH_PREF_PLMN_OPLMN == enPrefPLMNType)
    {
        return EN_MMC_OPLMN_INFO;
    }
    else
    {
        return EN_MMC_HPLMN_INFO;
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


