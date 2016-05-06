
#ifndef _ATDEVICECMD_H_
#define _ATDEVICECMD_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "v_typdef.h"
#include "ATCmdProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*生产使用的加密结构*/

/* WIFI KEY字符串长度，与NVIM模块Ipcom_parameters_handle.h文件的 NV_WLKEY_LEN 保持一致 */
#define AT_NV_WLKEY_LEN                 (27)

/* 鉴权模式字符串长度，与NVIM模块Ipcom_parameters_handle.h文件的 NV_WLAUTHMODE_LEN 保持一致 */
#define AT_NV_WLAUTHMODE_LEN            (16)

/* 加密模式字符串长度，与NVIM模块Ipcom_parameters_handle.h文件的 NV_ENCRYPTIONMODES_LEN 保持一致 */
#define AT_NV_ENCRYPTIONMODES_LEN       (5)

/* WPA的密码字符串长度，与NVIM模块Ipcom_parameters_handle.h文件的 NV_WLWPAPSK_LEN 保持一致 */
#define AT_NV_WLWPAPSK_LEN              (65)

/* NV项50012的数据结构nv_wifisec_type WIFI KEY后面的数据长度 */
#define AT_NV_WIFISEC_OTHERDATA_LEN     (72)

/* 单板侧支持的WIFI KEY个数 */
#define AT_WIWEP_CARD_WIFI_KEY_TOTAL    (4)

/* 工位侧支持的WIFI KEY个数 */
#define AT_WIWEP_TOOLS_WIFI_KEY_TOTAL   (16)

/* PHYNUM命令物理号类型MAC的物理号长度 */
#define AT_PHYNUM_MAC_LEN               (12)

/* PHYNUM命令物理号类型MAC的物理号与^WIFIGLOBAL命令匹配需要增加的冒号个数 */
#define AT_PHYNUM_MAC_COLON_NUM         (5)

#define AT_TSELRF_PATH_TOTAL            (4)

#define AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS   (2)                             /* MAC地址中冒号之间的字符个数*/


#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
#define AT_TDS_SCALIB_STR (VOS_UINT8 *)"(\"CACHE\",\"USE\",\"SAVE\",\"GET\",\"READ\",\"INI\",\"BEGIN\",\"END\",\"SET\",\"\"),(\"APCOFFSETFLAG\",\"APCOFFSET\",\"APC\",\"APCFREQ\",\"AGC\",\"AGCFREQ\",\"\"),(1,5,6),(@pram)"
#define AT_TDS_SCALIB_TEST_STR "(CACHE,USE,SAVE,GET,READ,INI,BEGIN,END,SET),(APCOFFSETFLAG,APCOFFSET,APC,APCFREQ,AGC,AGCFREQ),(1,5,6),(DATA)"
#endif

#define BAND_WIDTH_NUMS 6

#define UIMID_DATA_LEN                              (4)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : AT_TBAT_OPERATION_TYPE_ENUM
 结构说明  : ^TBAT的测试项目
             AT_TBAT_BATTERY_ANALOG_VOLTAGE         电池模拟电压
             AT_TBAT_BATTERY_DIGITAL_VOLTAGE        电池数字电压
             AT_TBAT_BATTERY_VOLUME                 电池电量
  1.日    期   : 2012年01月02日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
enum AT_TBAT_OPERATION_TYPE_ENUM
{
    AT_TBAT_BATTERY_ANALOG_VOLTAGE      = 0,
    AT_TBAT_BATTERY_DIGITAL_VOLTAGE     = 1,
    AT_TBAT_BATTERY_VOLUME              = 2,
    AT_TBAT_OPERATION_TYPE_BUTT
};
typedef VOS_UINT32  AT_TBAT_OPERATION_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_TBAT_OPERATION_DIRECTION_ENUM
 结构说明  : ^TBAT的测试方向
            AT_TBAT_READ_FROM_UUT   从单板侧(UUT)读取
            AT_TBAT_SET_TO_UUT      设置到单板侧(UUT)
  1.日    期   : 2012年01月02日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
enum AT_TBAT_OPERATION_DIRECTION_ENUM
{
    AT_TBAT_READ_FROM_UUT,
    AT_TBAT_SET_TO_UUT,
    AT_TBAT_OPERATION_DIRECTION_BUTT
};
typedef VOS_UINT32  AT_TBAT_OPERATION_DIRECTION_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_TSELRF_PATH_ENUM
 结构说明  : ^TSELRF的射频通路编号
             AT_TSELRF_PATH_GSM       GSM通路（包括EDGE/GPRS/EGSM等的全集）
             AT_TSELRF_PATH_WCDMA_PRI WCDMA主集
             AT_TSELRF_PATH_WCDMA_DIV WCDMA分集
             AT_TSELRF_PATH_WIFI      WiFi通路
  1.日    期   : 2012年01月02日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
enum AT_TSELRF_PATH_ENUM
{
    AT_TSELRF_PATH_GSM                  = 1,
    AT_TSELRF_PATH_WCDMA_PRI            = 2,
    AT_TSELRF_PATH_WCDMA_DIV            = 3,
    AT_TSELRF_PATH_TD					= 6,
    AT_TSELRF_PATH_WIFI                 = 7,
    AT_TSELRF_PATH_BUTT
};
typedef VOS_UINT32  AT_TSELRF_PATH_ENUM_UINT32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/* 由于 g_stATDislogPwd 中的 DIAG口的状态要放入备份NV列表; 而密码不用备份
   故将 g_stATDislogPwd 中的密码废弃, 仅使用其中的 DIAG 口状态;
   重新定义NV项用来保存密码  */
extern VOS_INT8                         g_acATOpwordPwd[AT_OPWORD_PWD_LEN+1];


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : AT_TBAT_BATTERY_ADC_INFO_STRU
 结构说明  : ^TBAT命令设置电池校准参数的数据结构

  1.日    期   : 2012年01月02日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMinAdc;
    VOS_UINT16                          usMaxAdc;
}AT_TBAT_BATTERY_ADC_INFO_STRU;

/*****************************************************************************
 结构名    : AT_WIFISEC_WIWEP_INFO_STRU
 结构说明  : WIWEP命令操作对象: WIFI KEY的数据结构
             ucwlKeys的内容为字符类型，以字符串结束符'\0'作为数据结束
  1.日    期   : 2012年01月02日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucwlKeys[AT_NV_WLKEY_LEN];
}AT_WIFISEC_WIWEP_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 AT_SetTbatPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryTbatPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetPstandbyPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetWiwepPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryWiwepPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestWiwepPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetCmdlenPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryCmdlenPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_UpdateMacPara(
    VOS_UINT8                           aucMac[],
    VOS_UINT16                          usMacLength
);

VOS_UINT32 AT_SetTmodeAutoPowerOff(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetTseLrfPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryTseLrfPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[]);

VOS_UINT32 AT_ExistSpecificPort(VOS_UINT8 ucPortType);

VOS_UINT32 AT_OpenDiagPort(VOS_VOID);
VOS_UINT32 AT_CloseDiagPort(VOS_VOID);
VOS_UINT32 AT_CheckSetPortRight(
    VOS_UINT8                           aucOldRewindPortStyle[],
    VOS_UINT8                           aucNewRewindPortStyle[]
);

VOS_UINT32 AT_TestHsicCmdPara(VOS_UINT8 ucIndex);

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 At_TestTdsScalibPara(VOS_UINT8 ucIndex);
#endif

VOS_UINT32 AT_TestSimlockUnlockPara( VOS_UINT8 ucIndex );

VOS_UINT32 AT_SetNVReadPara(VOS_UINT8 ucClientId);
VOS_UINT32 AT_SetNVWritePara(VOS_UINT8 ucClientId);

VOS_UINT32 AT_QryFPllStatusPara(VOS_UINT8 ucIndex);
VOS_VOID At_RfPllStatusCnfProc(PHY_AT_RF_PLL_STATUS_CNF_STRU *pstMsg);

VOS_UINT32 AT_QryFpowdetTPara(VOS_UINT8 ucIndex);
VOS_VOID At_RfFpowdetTCnfProc(PHY_AT_POWER_DET_CNF_STRU *pstMsg);

VOS_UINT32 AT_NVWRGetParaInfo( AT_PARSE_PARA_TYPE_STRU * pstPara, VOS_UINT8 * pu8Data, VOS_UINT32 * pulLen);


VOS_UINT32 AT_SetNvwrSecCtrlPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaNvwrSecCtrlSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_QryNvwrSecCtrlPara(VOS_UINT8 ucIndex);
VOS_BOOL AT_IsNVWRAllowedNvId(VOS_UINT16 usNvId);

extern VOS_UINT32 AT_AsciiToHex(
    VOS_UINT8                          *pucSrc,
    VOS_UINT8                          *pucDst
);

extern VOS_UINT32 AT_AsciiToHexCode_Revers(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDst
);

extern VOS_UINT32 AT_Hex2Ascii_Revers(
    VOS_UINT8                           aucHex[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 AT_SetMeidPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryMeidPara(VOS_UINT8 ucIndex);
#endif

extern VOS_UINT32 AT_SetMipiWrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetMipiRdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSSIWrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSSIRdPara(VOS_UINT8 ucIndex);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtDeviceCmd.h */
