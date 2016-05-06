/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : UsimmBase.h
  Author      : zhuli 00100318
  Version     : V100R002
  Date        : 2008-5-15
  Description : 该头文件定义了---
  History     :
  1.Date:2008-07-02
     Author: m00128685
     Modification:Modify the definition of enum

************************************************************************/

#ifndef __USIMM_BASE_H__
#define __USIMM_BASE_H__

#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "UsimmApi.h"
#include "UsimPsInterface.h"
#include "usimmapdu.h"
#include "omnvinterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "OamXmlComm.h"
#include "omerrorlog.h"
#include "pamom.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_VSIM == FEATURE_ON)

#define USIMM_VSIM_TYPE_STR         "TYPE"
#define USIMM_VSIM_USIM_STR         "USIM"
#define USIMM_VSIM_SIM_STR          "SIM"
#define USIMM_VSIM_AUTH_STR         "ALGORITHM"
#define USIMM_VSIM_AUTH_3G_STR      "MILENAGE"
#define USIMM_VSIM_AUTH_2GV1_STR    "COMP128V1"
#define USIMM_VSIM_AUTH_2GV2_STR    "COMP128V2"
#define USIMM_VSIM_AUTH_2GV3_STR    "COMP128V3"
#define USIMM_VSIM_KI_STR           "EFKI"
#define USIMM_VSIM_OPC_STR          "EFOPC"
#define USIMM_VSIM_VERIFY_HASH_STR  "VERIFYHASH"
#define USIMM_VSIM_NAME_STR         "NAME"
#define USIMM_VSIM_HASH_LEN         (32)

#endif

/*fid优先级*/
#define MAPS_USIMM_FID_PRIORITY         VOS_PRIORITY_P1

//快速开机的始能
#define USIMM_OPENSPEEDENABLE           0x01000101
#define USIMM_OPENSPEEDDISABLE          0x00000000

/*Ecc类型*/
#define ECC_USIM                        1
#define ECC_SIM                         0

/*ATR tag*/
#define CTLV_IND_TAG                    0x80
#define CARD_SVR_TAG                    0x30
#define CARD_CPB_TAG                    0x70
#define CARD_CPB3_TAG                   0x73

/*EFDIR tag*/
#define APP_TMP_TAG                     0x61
#define APP_IND_TAG                     0x4F

#define APP_TMP_TAG_OFFSET              (0)
#define APP_IND_TAG_OFFSET              (2)
#define APP_AID_LEN_OFFSET              (3)
#define APP_AID_VALUE_OFFSET            (4)


#define USIMM_RID_LEN                   (5)
#define USIMM_APP_CODE_LEN              (2)

/*fcp tag*/
#define USIMM_FCP_TAG                   0x62
#define USIMM_FCP_FILE_DES_TAG          0x82
#define USIMM_FCP_FID_TAG               0x83
#define USIMM_FCP_NAME_TAG              0x84
#define USIMM_FCP_PRIVITE_TAG           0xA5
#define USIMM_FCP_CHARA_TAG             0x80
#define USIMM_FCP_SA_CF_TAG             0x8C
#define USIMM_FCP_SA_EF_TAG             0xAB
#define USIMM_FCP_SA_REF_TAG            0x8B
#define USIMM_FCP_PIN_TO_TAG            0xC6
#define USIMM_FCP_FILESIZE_TAG          0x80
#define USIMM_FCP_SFI_TAG               0x88
#define USIMM_FCP_PRO_INFO_TAG          0xA5
#define USIMM_FCP_LCSI_TAG              0x8A
#define USIMM_FCP_TOTAL_SIZE_TAG        0x81
#define USIMM_FCP_PINMAP_TAG            0x90
#define USIMM_FCP_PINRER_TAG            0x83
#define USIMM_FCP_PINQUALIFER_TAG       0x95
#define USIMM_FCP_SUPSYSCMD_TAG         0x87

/*文件池最大文件数目*/
#define USIMM_POOL_MAX_NUM              (64)

/*二进制文件池最大文件空间*/
#define USIMM_MAX_FILE_SIZE             (0x2400)

/*初始化文件数定义,分为不受PIN保护的，和受PIN保护的Mandatory和Optional文件*/
#define USIMM_INITFIRST_FILENUM        2
#define USIMM_INITSIM_OFILENUM         12
#define USIMM_INITUSIM_OFILENUM        14

/* Optional文件初始化最大文件个数 */
#define USIMM_INIT_OFILE_MUX_NUM       (16)

/* ATT定制文件初始化文件列表长度 */
#define USIMM_USIM_ATT_INITFILE_NUM     2
#define USIMM_SIM_ATT_INITFILE_NUM      1

//文件关系的值定义
#define USIMM_SIMDFGSMGDF_MAX           2
#define USIMM_SIMDFTELGDF_MAX           1
#define USIMM_SIMDFCONTENT_MAX          2

#define USIMM_USIMADFGDF_MAX            4
#define USIMM_USIMADFTELGDF_MAX         2
#define USIMM_USIMDFCONTENT_MAX         3

/*判断卡复位状态的循环次数*/
#define USIMM_GET_SCISTATUS_MAX         300

/*复位卡操作类型*/
#define USIMM_RESET_CARD                0
#define USIMM_CHANGE_VCC                1

/*SCI操作结果定义*/
#define USIMM_SCI_SUCCESS               0
#define USIMM_SCI_NONEED_CHANGEVCC      1

/*读取全部文件内容*/
#define USIMM_READ_ALL_FILE_CONTENT     0

/*保护性复位事件*/
#define USIMM_PROTECT_RESET             0xFF

#define USIMM_PROTECT_MAX_NUM           (3)

/*当前记录文件最大个数，结构体中使用需要4字节对齐*/
#define USIMM_LOG_FILE_MAX_NUM          (4)

/*当前记录文件最大姓名，结构体中使用需要4字节对齐*/
#define USIMM_LOG_FILE_NAME_LEN         (0x10)

#define USIMM_LOG_DATA_TAG              (0x5A)

#define USIMM_LOG_START_TAG             (0x5555AAAA)

/*当前记录的数据区域的大小*/
#define USIMM_LOG_DATA_MAX_LEN          (8*1024)
#define USIMM_EXCLOG_DATA_MAX_LEN       (4*1024)

/* ATT定制Support Table的长度 */
#define USIMM_ATT_SUPPORT_TABLE_MAX     (16)
#define USIMM_ATT_SUPPORT_TABLE_MIN     (8)

/* ATT定制Support Table字节偏移量 */
#define USIMM_ATT_SCAN_CTRL_OFFSET          (0)
#define USIMM_ATT_NETWORK_SELECTION_OFFSET  (1)
#define USIMM_ATT_ACTING_HPLMN              (2)
#define USIMM_ATT_3G_SUPPORT                (3)
#define USIMM_ATT_RAT_BALANCING             (4)
#define USIMM_ATT_BIP_SUPPORT               (5)
#define USIMM_ATT_LTE_SUPPORT               (6)
#define USIMM_ATT_CSG_SUPPORT               (7)

/* ATT定制Support Table中LTE特性 */
#define USIMM_ATT_LTE_DATA_ONLY             (0x01)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB       (0x02)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB_IMS   (0x03)


#define USIMM_ENVELOPE_PPDOWN                (0xD1)
#define USIMM_ENVELOPE_CBDOWN                (0xD2)

/* ATR信息 */
#define USIMM_ATR_MAX_LEN                   (80)
#define USIMM_ATR_T0_OFFSET                 (1)

/* Session ID最大值 */
#define USIMM_SESSION_ID_MAX                (0x7fffffff)

/* 通道号最大值 */
#define USIMM_CHANNEL_INVALID_NUM           (0xffffffff)

/* UICC基本通道号 */
#define USIMM_BASE_CHANNEL_NUM              (0)

#define USIMM_RAND_SEED_MAX                 (0xffffffff)

/* 尝试发送选择文件APDU的最大次数 */
#define USIMM_SELECT_MAX_TIME               (3)

#define USIMM_SIM_SELECT_P2_PARA            (0x00)

#define USIMM_2G_AUTH_SRES_LEN              (4)
#define USIMM_2G_AUTH_KC_LEN                (8)

/* 鉴权数据中使用的TAG标示 */
#define USIMM_GBA_AUTH_TAG                  (0xDD)
#define USIMM_NAF_AUTH_TAG                  (0xDE)
#define USIMM_AUTH_SUCCESS_TAG              (0xDB)
#define USIMM_AUTH_SYNC_FAIL_TAG            (0xDC)


/* 鉴权模式定义，对应APDU中的P2参数 */
#define USIMM_SIM_2G_AUTH_MODE              (0x00)
#define USIMM_USIM_2G_AUTH_MODE             (0x80)
#define USIMM_USIM_3G_AUTH_MODE             (0x81)
#define USIMM_USIM_GBA_AUTH_MODE            (0x84)
#define USIMM_ISIM_AKA_AUTH_MODE            (0x81)
#define USIMM_ISIM_HTTP_AUTH_MODE           (0x82)
#define USIMM_ISIM_GBA_NAF_AUTH_MODE        (0x84)

/* 获得输入文件类型 */
#define USIMM_FILE_TYPE(usFileId)           (VOS_UINT8)((usFileId>>0x08)&0x00FF)

/* 判断输入文件是否为DF文件 */
#define USIMM_IS_DF_FILE(usFileId) \
        (USIMM_DF_FILE == (((usFileId)>>0x0C)&0x01))

#define USIMM_FILE_PATH_MAX_LEN         100

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )
#define USIMM_LOG_PATH                  "Sim1"
#define USIMM_LOGCTRL_FILE              "Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          USIMM_LOG_PATH

#define USIMM_UNITARY_LOGCTRL_FILE      USIMM_LOGCTRL_FILE

#elif (( VOS_VXWORKS == VOS_OS_VER ) || ( VOS_RTOSCK == VOS_OS_VER ))
#if defined (INSTANCE_1)    /*SIM card 1*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim1"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim1"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim1/usimmlogctrl.bin"

#elif defined (INSTANCE_2)   /*SIM card 2*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim2"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim2/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim2"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim2/usimmlogctrl.bin"
#else                       /*SIM Card 0*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim0"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim0/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim0"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim0/usimmlogctrl.bin"

#endif /* end of INSTANCE_1*/
#endif /* end of VOS_WIN32*/


#define USIMM_MNC_TWO_BYTES_LEN        (2)             /* MNC长度为2 */
#define USIMM_MNC_THREE_BYTES_LEN      (3)             /* MNC长度为3 */
#define USIMM_AD_MNC_LEN_POS           (3)             /* AD文件中MNC长度字段所在位置 */
#define USIMM_IMSI_MAX_LEN             (8)             /* IMSI中指示长度的最大值 */

#define USIMM_BIT_NUM_IN_BYTE          (8)             /* 一个字节中包含的bit数 */
#define USIMM_MNC_MCC_FIG_NUM          (3)             /* MNC,MCC数字个数，MNC数字不足3个时，补0 */
#define USIMM_ISIMEFTOUSIMEF_TBL_SIZE  (5)             /* ISIM文件到USIM文件转换表大小 */

#define USIMM_ISIM_FILE_TAG            (0x80)

#define USIMM_AUTH_XRES_LEN             (8)     /* 3G鉴权的返回数据     */
#define USIMM_AUTH_RES_LEN              (4)     /* 2G鉴权的返回数据     */
#define USIMM_AUTH_CK_LEN               (16)    /* 3G鉴权的CK           */
#define USIMM_AUTH_IK_LEN               (16)    /* 3G鉴权的IK           */
#define USIMM_AUTH_KC_LEN               (8)     /* 2G鉴权的Kc           */
#define USIMM_AUTH_KI_LEN               (16)    /* 鉴权的KI             */
#define USIMM_AUTH_OPC_LEN              (16)    /* 鉴权的OPC            */

#define USIMM_VSIM_SECUR_MAX_LEN        (32)    /* vSIM里面机密数据长度 */

#define USIMM_VSIM_SIM_KEY_HASH_LEN     (96)    /* IMSI+KI+OPC加密长度  */


#if (FEATURE_VSIM == FEATURE_ON)
#define USIMM_VSIM_IS_FILE_ATTR_VALID(index)      ( (USIMM_MANDATORY_FILE         == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                  ||((USIMM_USIM_MANDATORY_FILE  == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_PHYCARD_TYPE_UICC   == USIMM_CCB_GetCardType())) \
                                                  ||((USIMM_SIM_MANDATORY_FILE   == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_PHYCARD_TYPE_ICC    == USIMM_CCB_GetCardType())) )
#endif

#define USIMM_HUK_BITS                  (128)

#define USIMM_HUK_LEN                   (0x10)

#define USIMM_EF_CST_MAX_LEN            (12)

#define USIMM_INITAPPS_TIMES_MAX        (3)

#define USIMM_CHANNEL_NUMBER_MAX        (20)

#define USIMM_PIN_NUMBER_MAX            (8)

#define USIMM_CDMA_DEFAULT_SCM          (8)

#define EFICCID                                 (0x2FE2)

/* ATT自定义文件ID */
#define EFACTINGHPLMN                           (0x4F34)
#define EFRATMODE                               (0x4F36)
#define EFTERMINALSUPPORTTABLE                  (0x6FD2)

/*PB 文件ID定义 */
#define EFPSC                                   (0x4F22)
#define EFCC                                    (0x4F23)
#define EFPUID                                  (0x4F24)

/* ISIM 文件ID定义 参考31.103 */
#define EFISIMIMPI                              (0x6F02)
#define EFISIMDOMAIN                            (0x6F03)
#define EFISIMIMPU                              (0x6F04)
#define EFISIMAD                                (0x6FAD)
#define EFISIMIST                               (0x6F07)
#define EFISIMPCSCF                             (0x6F09)
#define EFISIMGBABP                             (0x6FD5)
#define EFISIMGBANL                             (0x6FD7)
#define EFISIMNAFKCA                            (0x6FDD)
#define EFISIMUICCIARI                          (0x6FE7)

/* USIM 文件ID定义 参考31.102 */
#define EFPL                                    (0x2F05)
#define EFICCID                                 (0x2FE2)
#define EFLP                                    (0x6F05)
#define EFIMSI                                  (0x6F07)
#define EFAD                                    (0x6FAD)
#define EFEST                                   (0x6F56)
#define EFADN                                   (0x6F3A)
#define EFBDN                                   (0x6F4D)
#define EFFDN                                   (0x6F3B)
#define EFECC                                   (0x6FB7)
#define EFMSISDN                                (0x6F40)
#define EFPHASE                                 (0x6FAE)
#define EFGBABP                                 (0x6FD6)
#define EFGBANL                                 (0x6FDA)
#define EFNAFKCA                                (0x6FDD)
#define EFUICCIARI                              (0x6FE7)
#define EFUST                                   (0x6F38)

/* UIM 文件ID定义，参考C.S0023 */
#define EFCST                                   (0x6F32)
#define EF_CSIM_EST                             (0x6F75)   /*T*/
#define EF_CUIM_ECC                             (0x6F47)   /*T*/
#define EF_CUIM_AD                              (0x6F43)   /*T*/
#define EF_CUIM_CST                             (0x6F32)   /*T*/
#define EF_CUIM_IMSIM                           (0x6F22)   /*T*/
#define EF_CUIM_IMSIT                           (0x6F23)   /*T*/
#define EF_CUIM_TMSI                            (0x6F24)   /*T*/

/* CSIM 文件ID定义 */
#define EFCSIMST                                (0x6F32)
/* SIM 文件ID定义 */
#define EFSST                                   (0x6F38)

/* VSIM 文件ID */
#define EFFPLMN                                 (0x6F7B)
#define EFPSLOCI                                (0x6F73)
#define EFLOCIGPRS                              (0x6F53)
#define EFLOCI                                  (0x6F7E)
/*******************************************************************************
  3 枚举定义
*******************************************************************************/
typedef VOS_UINT32 (*PCARDINITPROC)(VOS_VOID);

typedef struct
{
    PCARDINITPROC                pProcFun;        /* 处理函数 */
}USIMM_CARD_INIT_FUNC;

typedef struct
{
    USIMM_CARD_INIT_FUNC         *pInitFunTbl;
    VOS_UINT32                   ulStepNum;
}USIMM_CARD_INIT_TBL_ST;

/* MANAGE CHANNEL 命令枚举 即下发数据单元的p1参数，参见协议102.221第11.1.17 */
enum USIMM_MANAGE_CHANNEL_ENUM
{
    USIMM_OPEN_CHANNEL         =0x00,
    USIMM_CLOSE_CHANNEL        =0x80,
    USIMM_MANAGE_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_MANAGE_CHANNEL_ENUM_UINT32;

/*是否支持sfi*/
enum USIMM_SUPPORT_SFI_ENUM
{
    USIMM_NOTSUPPORT_SFI         =0,
    USIMM_SUPPORT_SFI            =1,
    USIMM_SUPPORT_SFI_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SFI_ENUM_UINT32;


/*是否支持path*/
enum USIMM_SUPPORT_PATH_ENUM
{
    USIMM_NOTSUPPORT_PATH       = 0,
    USIMM_SUPPORT_PATH          = 1,
    USIMM_SUPPORT_PATH_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_PATH_ENUM_UINT32;


/*是否支持logic channel*/
enum USIMM_SUPPORT_CHANNEL_ENUM
{
    USIMM_NOTSUPPORT_CHANNEL    = 0,
    USIMM_SUPPORT_CHANNEL       = 1,
    USIMM_SUPPORT_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_CHANNEL_ENUM_UINT32;

enum USIMM_CLKLEVEL_ENUM
{
    USIMM_CLKLEVEL_LOW          = 0,
    USIMM_CLKLEVEL_HIGH         = 1,
    USIMM_CLKLEVEL_NONE         = 2,
    USIMM_CLKLEVEL_BUTT
};
typedef VOS_UINT32      USIMM_CLKLEVEL_ENUM_UINT32;

enum USIMM_CLKSTOP_ENUM
{
    USIMM_CLKSTOP_ALLOW             = 0,
    USIMM_CLKSTOP_NOALLOW           = 1,
    USIMM_CLKSTOP_BUTT
};
typedef VOS_UINT32      USIMM_CLKSTOP_ENUM_UINT32;

enum USIMM_SAT_STATE_ENUM
{
    USIMM_SAT_STATE_NODATA          = 0,
    USIMM_SAT_STATE_NEEDFETCH       = 1,
    USIMM_SAT_STATE_NEEDRESPONSE    = 2,
    USIMM_SAT_STATE_BUTT
};
typedef VOS_UINT32      USIMM_SAT_STATE_ENUM_UINT32;


enum USIMM_UNIVERSAL_PIN_STATUS_ENUM
{
    USIMM_UNIVERSAL_PIN_DISABLE     = 0,
    USIMM_UNIVERSAL_PIN_ENABLE      = 1,
    USIMM_UNIVERSAL_PIN_BUTT
};
typedef VOS_UINT32      USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32;


/*文件结构*/
enum USIMM_EF_TYPE_ENUM
{
    USIMM_EFSTRUCTURE_NONE          = 0,
    USIMM_EFSTRUCTURE_TRANSPARENT   = 1,
    USIMM_EFSTRUCTURE_FIXED         = 2,
    USIMM_EFSTRUCTURE_CYCLE         = 3,
    USIMM_EFSTRUCTURE_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_EF_TYPE_ENUM_UINT32;

enum USIMM_SC_ATTRIB_MODE_ENUM
{
    USIMM_SC_ATTRIB_NO          = 0,
    USIMM_SC_ATTRIB_COMPACT     = 1,
    USIMM_SC_ATTRIB_EXPANDED    = 2,
    USIMM_SC_ATTRIB_REFERENCE   = 3,
    USIMM_SC_ATTRIB_BUTT
};
typedef VOS_UINT32      USIMM_SC_ATTRIB_MODE_ENUM_UINT32;


enum USIMM_AC_LEVEL_ENUM
{
    USIMM_AC_LEVEL_ALW          = 0,
    USIMM_AC_LEVEL_PIN1         = 1,
    USIMM_AC_LEVEL_PIN2         = 2,
    USIMM_AC_LEVEL_UPIN         = 3,
    USIMM_AC_LEVEL_ADM          = 4,
    USIMM_AC_LEVEL_NEV          = 5,
    USIMM_AC_LEVEL_BUTT
};
typedef VOS_UINT32      USIMM_AC_LEVEL_ENUM_UINT32;

enum USIMM_POOLSTATUS_ENUM
{
    USIMM_POOL_NOINTIAL         =  0,
    USIMM_POOL_INITIALED        =  1,
    USIMM_POOL_FIRST_STEP       =  2,
    USIMM_POOL_AVAILABLE        =  3,
    USIMM_POOLSTATUS_BUTT
};
typedef VOS_UINT32      USIMM_POOLSTATUS_ENUM_UINT32;

enum USIMM_CARD_STATE_CHANGE_ENUM
{
    USIMM_CARD_STATE_NOCHANGE   = 0,
    USIMM_CARD_STATE_CHANGED    = 1,
    USIMM_CARD_STATE_CHANGE_BUTT
};
typedef VOS_UINT32      USIMM_CARD_STATE_CHANGE_ENUM_UINT32;

enum USIMM_FILE_NEED_FCP_ENUM
{
    USIMM_NO_NEED_FCP           = 0,
    USIMM_NEED_FCP              = 1,
    USIMM_NEED_FCP_BUTT
};
typedef VOS_UINT32      USIMM_FILE_NEED_FCP_ENUM_UINT32;

enum USIMM_LOG_STATE_ENUM
{
    USIMM_NEED_LOG              = 0,
    USIMM_NO_NEED_LOG           = 1,
    USIMM_LOG_STATE_BUTT
};
typedef VOS_UINT32      USIMM_LOG_STATE_ENUM_UINT32;

enum USIMM_SUPPORT_SYSTEM_COMMAND_ENUM
{
    USIMM_NO_SUPSYSCMD           = 0,
    USIMM_SUPSYSCMD              = 1,
    USIMM_SUPSYSCMD_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SYSTEM_COMMAND_ENUM_UINT32;

enum USIMM_MODE_TYPE_ENUM
{
    USIMM_NORMAL_MODE           = 0,    /* 正常上电启动模式 */
    USIMM_RESET_MODE            = 1,    /* 复位重启模式 */
    USIMM_REFRESH_MODE          = 2,    /* refresh模式 */
    USIMM_PROTECT_RESET_MODE    = 3,    /* 保护性复位模式 */
    USIMM_MODE_TYPE_BUTT
};
typedef VOS_UINT8      USIMM_MODE_TYPE_ENUM_UINT8;


/* USIM卡电压等级，协议TS102221 11.1.1.4.6.1 */
enum USIMM_VOLTAGE_CLASS_ENUM
{
    USIMM_VOLTAGE_5V           = 0x10,   /* supply voltage class A */
    USIMM_VOLTAGE_3V           = 0x20,   /* supply voltage class B */
    USIMM_VOLTAGE_1_8V         = 0x40,   /* supply voltage class C */
    USIMM_VOLTAGE_CLASS_BUTT
};
typedef VOS_UINT32      USIMM_VOLTAGE_CLASS_ENUM_UINT32;

/* SIM卡的PHASE枚举 */
enum USIMM_SIM_PHASE_ENUM
{
    USIMM_SIM_PHASE_ONE        = 0x00,   /* PHASE1 的SIM卡 */
    USIMM_SIM_PHASE_TWO        = 0x02,   /* PHASE2 的SIM卡 */
    USIMM_SIM_PHASE_PLUS       = 0x03,   /* PHASE2+ 的SIM卡 */
    USIMM_SIM_PHASE_BUTT
};
typedef VOS_UINT32      USIMM_SIM_PHASE_ENUM_UINT32;

enum USIMM_PROFILE_DOWNLOAD_ENUM
{
    USIMM_PROFILE_DOWNLOAD_SUCCESS      = VOS_OK,
    USIMM_PROFILE_DOWNLOAD_FAIL,
    USIMM_PROFILE_DOWNLOAD_BUTT
};

typedef VOS_UINT8       USIMM_PROFILE_DOWNLOAD_ENUM_UINT8;

/* 初始化阶段ECC文件初始化状态枚举 */
enum USIMM_ECC_INIT_STATUS_ENUM
{
    USIMM_ECC_INIT_SUCCESS      = VOS_OK,
    USIMM_ECC_SELECT_FAIL,
    USIMM_ECC_READ_FAIL,
    USIMM_ECC_TYPE_ERR,
    USIMM_ECC_INIT_STATUS_BUTT
};

typedef VOS_UINT8       USIMM_ECC_INIT_STATUS_ENUM_UINT8;

enum USIMM_SIM_FILE_TYPE_ENUM
{
    USIMM_SIM_FILE_TYPE_RFU = 0x00,
    USIMM_SIM_FILE_TYPE_MF  = 0x01,
    USIMM_SIM_FILE_TYPE_DF  = 0x02,
    USIMM_SIM_FILE_TYPE_EF  = 0x04,
    USIMM_SIM_FILE_TYPE_BUTT
};

typedef VOS_UINT8 USIMM_SIM_FILE_TYPE_ENUM_UINT8;

enum USIMM_VSIM_AUTH_ENUM
{
    USIMM_VSIM_AUTH_NULL        = 0,
    USIMM_VSIM_MILENAGE         = 1,
    USIMM_VSIM_COMPV1           = 2,
    USIMM_VSIM_COMPV2           = 3,
    USIMM_VSIM_COMPV3           = 4,
    USIMM_VSIM_AUTH_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AUTH_ENUM_UINT8;
typedef VOS_UINT32     USIMM_VSIM_AUTH_ENUM_UINT32;

enum USIMM_FILE_ATTR_ENUM
{
    USIMM_MANDATORY_FILE        = 0,    /*SIM USIM都需要的文件*/
    USIMM_USIM_MANDATORY_FILE   = 1,
    USIMM_SIM_MANDATORY_FILE    = 2,
    USIMM_OPTIONAL_FILE         = 3,
    USIMM_FILE_ATTR_BUTT
};
typedef VOS_UINT8      USIMM_FILE_ATTR_ENUM_UINT8;

enum USIMM_VSIM_AC_ENUM
{
    USIMM_VSIM_WRITE_AVALIBALE        = 0,    /*VSIM可以更新的文件*/
    USIMM_VSIM_WRITE_UNAVALIBALE      = 1,    /*VSIM不可以更新的文件*/
    USIMM_VSIM_AC_ENUM_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AC_ENUM_UINT8;

/*****************************************************************************
 枚举名    : USIMM_T1_IFS_SEND_STATUS_ENUM
 结构说明  : T=1 IFS 命令发送状态枚举
*****************************************************************************/
enum USIMM_T1_IFS_SEND_STATUS_ENUM
{
    USIMM_T1_IFS_SEND_SUCCESS = VOS_OK,          /* T=1协议下发送IFS命令成功 */
    USIMM_T1_IFS_SEND_FAILURE,                   /* T=1协议下发送IFS命令失败 */
    USIMM_T1_IFS_SEND_STATUS_BUTT
};

typedef VOS_UINT32      USIMM_T1_IFS_SEND_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_MNTN_ERROR_LEVEL_ENUM
 结构说明  : USIMM ERROR LOG级别枚举
*****************************************************************************/
enum USIMM_MNTN_ERROR_LEVEL_ENUM
{
    USIMM_MNTN_ERROR_LEVEL_CRITICAL = 1,    /* 紧急 */
    USIMM_MNTN_ERROR_LEVEL_MAJOR,           /* 重要 */
    USIMM_MNTN_ERROR_LEVEL_MINOR,           /* 次要 */
    USIMM_MNTN_ERROR_LEVEL_WARNING,         /* 告警 */
    USIMM_MNTN_ERROR_LEVEL_INFO,            /* 信息 */
    USIMM_MNTN_ERROR_LEVEL_BUTT
};
typedef  VOS_UINT16  USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : USIMM_MNTN_STATE_ERROR_REASON_ENUM
 结构说明  : USIMM ERROR LOG 事件枚举
*****************************************************************************/
enum USIMM_MNTN_STATE_ERROR_REASON_ENUM
{
    USIMM_MNTN_STATE_OK = 0,
    USIMM_MNTN_STATE_INIT_FAIL,
    USIMM_MNTN_STATE_POLLING_FAIL,
    USIMM_MNTN_STATE_ERROR_REASON_BUTT
};
typedef  VOS_UINT32  USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_PIN_ENUM
 结构说明  : PIN码索引值
*****************************************************************************/
enum USIMM_PIN_ENUM
{
    USIMM_UNIVERSIAL_PIN = 0,
    USIMM_KEY_REF_PIN_01,
    USIMM_KEY_REF_PIN_02,
    USIMM_KEY_REF_PIN_03,
    USIMM_KEY_REF_PIN_04,
    USIMM_KEY_REF_PIN_05,
    USIMM_KEY_REF_PIN_06,
    USIMM_KEY_REF_PIN_07,
    USIMM_KEY_REF_PIN_08,
    USIMM_KEY_REF_PIN_BUTT,
};
typedef VOS_UINT32      USIMM_COMM_PIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_TEST_PHYCARD_TYPE_ENUM
 结构说明  : 测试卡类型
*****************************************************************************/
enum USIMM_TEST_PHYCARD_TYPE_ENUM
{
    USIMM_TEST_TYPE_NONE        = 0x00,
    USIMM_TEST_TYPE_ROM_SIM,
    USIMM_TEST_TYPE_GCF_SIM,
    USIMM_TEST_TYPE_BUTT
};
typedef VOS_UINT32 USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

/*effcp信息记录结构*/
typedef struct
{
    VOS_UINT16                          usFileLen;              /*当前文件长度*/
    VOS_UINT8                           ucRecordNum;            /*当前记录文件的记录数*/
    VOS_UINT8                           ucRecordLen;            /*当前记录文件的记录长度*/
    VOS_UINT8                           ucSFI;                  /*当前文件的SFI*/
    VOS_UINT8                           ucArrNo;                /*EFARR的记录号*/
    VOS_UINT16                          usEFArrID;              /*记录安全条件的EFARR的SFI*/
    USIMM_EF_TYPE_ENUM_UINT32           enFileType;             /*当前文件类型*/
    USIMM_EFSTATUS_ENUM_UINT8           enFileStatus;           /*当前文件状态*/
    USIMM_EFRWFLAG_ENUM_UINT8           enFileReadUpdateFlag;   /*当前文件无效时，文件可读与可更新标志*/
    VOS_UINT8                           aucRsv[2];
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;               /*当前文件的安全标识方法*/
    USIMM_AC_LEVEL_ENUM_UINT32          enUpdateAC;             /*当前文件的更新权限*/
    USIMM_AC_LEVEL_ENUM_UINT32          enReadAC;               /*当前文件的读取权限*/
    USIMM_AC_LEVEL_ENUM_UINT32          enActiveAC;             /*当前文件的激活权限*/
    USIMM_AC_LEVEL_ENUM_UINT32          enDeaciveAC;            /*当前文件的去激活权限*/
}USIMM_EFFCP_ST;

/*dffcp信息记录结构*/
typedef struct
{
    VOS_UINT16                          usDFID;         /*当前选中DFID*/
    VOS_UINT8                           ucPIN1RefNum;   /*当前DF的PIN1索引*/
    VOS_UINT8                           ucPIN2RefNum;   /*当前DF的PIN2索引*/
    VOS_UINT8                           ucCharaByte;
    VOS_UINT8                           ucNameLen;      /*当前DF的名字长度*/
    VOS_UINT8                           aucName[16];    /*当前DF的名字内容*/
    VOS_UINT8                           ucSupCmd;       /*支持terminal capability */
    VOS_UINT8                           ucRsv;
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;       /*当前DF的安全标识方式*/
    USIMM_PIN_INFO_STRU                 stPINInfo;
}USIMM_DFFCP_ST;

/*sim dffcp 内容记录结构,成员含义见协议3gpp ts 11.11 的9.2.1*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usMemRes;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucReserve2[5];
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucFileChara;
    VOS_UINT8                           ucDFsNum;
    VOS_UINT8                           ucEFsNum;
    VOS_UINT8                           ucSecurityCodeNum;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucPIN1RemainTime;
    VOS_UINT8                           ucPUK1RemainTime;
    VOS_UINT8                           ucPIN2RemainTime;
    VOS_UINT8                           ucPUK2RemainTime;
}USIMM_SIMDF_FCP_ST;

/*sim effcp 内容记录结构,成员含义见协议3gpp ts 11.11 的9.2.1*/
/*lint -e959 -e958*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usFileLen;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucCyclicEFTag;
    VOS_UINT8                           ucAccessCnd[3];
    VOS_UINT8                           ucFileStatus;
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucEFStruct;
    VOS_UINT8                           ucRecordLen;
}USIMM_SIMEF_FCP_ST;
/*lint +e959 +e958*/
/*****************************************************************************
 结构名    : USIMM_AID_INFO_STRU
 结构说明  : 用于记录USIM/ISIM/CSIM的AID内容和长度
 修改历史      :
  1.日    期   : 2013年12月19日
    作    者   : h59254
    修改内容   :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAIDLen;       /*当前的AID长度*/
    VOS_UINT8                           aucAID[USIMM_AID_LEN_MAX];     /*当前AID内容*/
}USIMM_AID_INFO_STRU;

typedef struct
{
    USIMM_PB_INIT_STATUS_ENUM_UINT16    enPBInitStatus;     /*当前电话本初始化状态，以决定是否可以进行时钟停止模式*/
    VOS_UINT16                          usPBDfID;           /*当前电话本的4F文件存在的路径*/
}USIMM_PB_INFO_STRU;

/*基本信息记录结构*/
typedef struct
{
    VOS_UINT8                               ucCLA;              /*当前CLA值*/
    VOS_UINT8                               ucCurChannelNum;    /*当前开启的通道数*/
    VOS_UINT16                              usSATLen;           /*当前的主动命令长度*/
    USIMM_CARDAPP_ENUM_UINT32               enMainAppType;      /*主应用类型*/
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardVersion;      /*保存识别的卡类型*/
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType;         /*保存当前卡类型*/
    USIMM_CARD_STATE_CHANGE_ENUM_UINT32     enStateChange;      /* 状态变更 */
    USIMM_SUPPORT_SFI_ENUM_UINT32           enSupportSFI;       /*是否支持SFI*/
    USIMM_SUPPORT_PATH_ENUM_UINT32          enSupportPath;      /*是否支持路径选择*/
    USIMM_SUPPORT_CHANNEL_ENUM_UINT32       enSupportChannel;   /*是否支持逻辑通道*/
    USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32  enUniversalPINStatus;/*当前全局PIN状态*/
    USIMM_SAT_STATE_ENUM_UINT32             enSATState;         /*当前主动命令状态*/
    VOS_BOOL                                bTimeOut;           /*发生TimeOut事件的时候发送*/
    USIMM_PB_INFO_STRU                      stPBInfo;           /*当前电话簿初时化信息*/
}USIMM_BASE_INFO_ST;

typedef struct
{
    VOS_UINT32                              ulIsimEFID;
    VOS_UINT32                              ulUsimEFID;
}USIMM_ISIMUSIM_EFTBL_STRU;

/*底软信息记录结构*/
typedef struct
{
    USIMM_CLKLEVEL_ENUM_UINT32              enCLKLevel;         /*当前CLK level优先级*/
    USIMM_CLKSTOP_ENUM_UINT32               enCLKStop;          /*当前CLK 是否允许停止*/
}USIMM_DRV_INFO_ST;

/*当前文件信息记录结构*/
typedef struct
{
    VOS_UINT16                              usCurDFID;      /*当前选中DFID*/
    VOS_UINT16                              usCurEFID;      /*当前选中EFID*/
    VOS_UINT16                              usCurDFFcpLen;  /*当前选中的DF的FCP长度*/
    VOS_UINT16                              usFilePathLen;
    VOS_UINT16                              ausFilePath[USIMM_MAX_PATH_LEN];  /*当前路径信息*/
    USIMM_DFFCP_ST                          stDFInfo;       /*当前DF信息*/
    USIMM_EFFCP_ST                          stEFInfo;       /*当前EF信息*/
}USIMM_CURFILEINFO_ST;

/*****************************************************************************
 结构名    : USIMM_POOL_ONERECORD_ST
 结构说明  : 文件池中文件信息记录结构

  1.日    期   : 2012年06月17日
    作    者   : h59254
    修改内容   : ATT定制项目增加APP类型
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEFId;         /* 文件ID */
    VOS_UINT16                              usLen;          /* 文件内容长度 */
    USIMM_CARDAPP_ENUM_UINT32               enAppType;      /* APP类型 */
    USIMM_EF_TYPE_ENUM_UINT32               enFileType;     /* 文件类型 */
    VOS_UINT8                              *pucContent;     /* 文件内容指针 */
}USIMM_POOL_ONERECORD_ST;

/*****************************************************************************
 结构名    : USIMM_POOL_OPTION_FILE_CFG_ST
 结构说明  : USIMM模块可选文件初始化配置结构

  1.日    期   : 2012年12月23日
    作    者   : h59254
    修改内容   : 问题单修改新增加结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usOptionFileNum;
    VOS_UINT16                              aucOptionFilelist[USIMM_INIT_OFILE_MUX_NUM];
}USIMM_POOL_OPTION_FILE_CFG_ST;


typedef struct
{
    USIMM_POOL_ONERECORD_ST                 astpoolRecord[USIMM_POOL_MAX_NUM];  /* 文件池的记录数组 */
    USIMM_POOLSTATUS_ENUM_UINT32            enPoolStatus;                       /* 文件池的状态 */
    VOS_UINT8                               ucPoolFileCount;                    /* 文件池文件个数 */
    VOS_UINT8                               aucReserved[3];
}USIMM_POOL_ST;


typedef VOS_UINT32 (*PUSIMMAPPPROC)(USIMM_CMDHEADER_REQ_STRU * pMsg);

typedef struct
{
    USIMM_CMDTYPE_REQ_ENUM_UINT32           enMsgType;        /* 消息ID */
    PUSIMMAPPPROC                           pProcFun;        /* 处理函数 */
}USIMMAPP_FUNCLIST_ST;

typedef struct
{
    USIMM_LOG_STATE_ENUM_UINT32             enLogState;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               *pucData;
}USIMM_LOG_DATA_STRU;

typedef struct
{
    VOS_UINT32                              ulCurFile;
    VOS_CHAR                                aucFileName[USIMM_LOG_FILE_MAX_NUM][USIMM_LOG_FILE_NAME_LEN];
}USIMM_LOG_CTRLFILE_STRU;

/*****************************************************************************
结构名    : USIMM_OPFILE_LIST_STRU
结构说明  : USIMM模块初始化列表结构

  1.日    期   : 2013年1月25日
    作    者   : h59254
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID;
    VOS_UINT32                          ulService;
}USIMM_OPFILE_LIST_STRU;

/*****************************************************************************
结构名    : USIMM_TERMINAL_POWER_SUPPLY_STRU
结构说明  : 终端电压供应结构，对应协议102.221上11.1.19.2.1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* terminal power supply 的tag:0x80 */
    VOS_UINT8                          ucLen;              /* 长度 */
    VOS_UINT8                          ucActSupVolCla;     /* 实际使用的供电电压等级 */
    VOS_UINT8                          ucMaxAvaPower;      /* 终端上最大可用电压供应 */
    VOS_UINT8                          ucActFre;           /* 实际使用的时钟频率 */
}USIMM_TERMINAL_POWER_SUPPLY_STRU;

/*****************************************************************************
结构名    : USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU
结构说明  : 终端电压供应结构，对应协议102.221上11.1.19.2.2
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* extended logical channel terminal support的tag:0x81 */
    VOS_UINT8                          ucLen;              /* 长度 */
}USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU;

/*****************************************************************************
结构名    : USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU
结构说明  : 终端电压供应结构，对应协议102.221上11.1.19.2.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* the additional interface support的tag:0x82 */
    VOS_UINT8                          ucLen;              /* 长度 */
    VOS_UINT8                          ucAddInterface;     /* 附加接口 */
}USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU;

/*****************************************************************************
结构名    : USIMM_CARD_INIT_INFO_LOG_STRU
结构说明  : 卡初始化阶段的信息记录
*****************************************************************************/
typedef struct
{
    USIMM_PROFILE_DOWNLOAD_ENUM_UINT8  enTPDownloadStatus;    /* terminal profile是否下发失败 */
    USIMM_ECC_INIT_STATUS_ENUM_UINT8   enEccInitStatus;       /* ECC文件初始化状态 */
    VOS_UINT8                          ucVoltageSwitchFlag;   /* 电压是否切换 */
    VOS_UINT8                          ucVoltageMismatchFlag; /* 电压不匹配标记 */
}USIMM_CARD_INIT_RECORD_STRU;

typedef struct
{
    VOS_UINT8                          ucInsertPoolFailFlag;  /* 文件插入缓冲池失败标记 */
    USIMM_CARD_INIT_RECORD_STRU        stUSIMMInfo;
}USIMM_CARD_INIT_INFO_LOG_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag;
}USIMM_SELECT_PARA_STUR;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           aucRsv[3];
}USIMM_GET_COMM_FILE_STRU;

#if (FEATURE_VSIM == FEATURE_ON)
typedef struct
{
    VOS_CHAR                                *pcVSIMName;
    VOS_UINT16                              usFileID;
    USIMM_FILE_ATTR_ENUM_UINT8              enFileAttr;
    USIMM_VSIM_AC_ENUM_UINT8                enFileAC;
}USIMM_VSIM_FILE_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulLen;
    VOS_UINT8                               aucData[USIMM_VSIM_SECUR_MAX_LEN * 2];
}USIMM_VSIM_BASE16_DATA_STRU;

typedef struct
{
    VOS_UINT8                               ucKILen;
    VOS_UINT8                               ucOpcLen;
    USIMM_VSIM_AUTH_ENUM_UINT8              enAuthType;
    VOS_UINT8                               ucRfu;
    VOS_UINT8                               aucKi[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucOpc[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucSimKeyHash[USIMM_VSIM_SIM_KEY_HASH_LEN];
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Ki;
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Opc;
}USIMM_VSIM_AUTH_INFO_STRU;
#endif

#if(FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 结构体名  : USIMM_MNTN_STATE_ERROR_EVENT_STRU
 结构说明  : USIMM ERROR LOG上报结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32       enStateErrorReason;     /*卡异常原因*/
    SCI_RECORD_INFO_S                               stSCIRecordInfo;        /*SCI驱动异常信息*/
    VOS_UINT32                                      aulRsv[4];              /*包括扩展字段 */
}USIMM_MNTN_STATE_ERROR_EVENT_STRU;
#endif

/*****************************************************************************
 结构名    : USIMM_CHANNEL_INFO_STRU
 结构说明  : USIM模块CHANNEL INFO的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRspLen;                               /* GetResponse长度 */
    VOS_UINT32                          ulAIDFcpLen;
    VOS_UINT8                           aucRspContent[USIMM_APDU_MAXLEN];   /* GetResponse的内容 */
    VOS_UINT8                           aucAIDFcp[USIMM_APDU_MAXLEN];
}USIMM_CHANNEL_RESPONSE_STRU;

/*****************************************************************************
 结构体名  : USIMM_STORE_ESN_MEID_STATUS_STRU
 结构说明  : USIMM 存储meid esn 结果状态结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsStoreEsnMeid;               /* 卡初始化是否进行Esn Meid存储 */
    VOS_UINT8                           ucStoreEsnMeidResult;            /* 存储Esn Meid返回结果值 */
    VOS_UINT8                           auRev[2];
}USIMM_STORE_ESN_MEID_STATUS_STRU;

/*****************************************************************************
 结构名    : USIMM_APP_PIN_INFO_STRU
 结构说明  : PIN码信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPINRefNum;
    VOS_UINT8                               ucPinRemainTime;            /* PIN码剩余次数      */
    VOS_UINT8                               ucPukRemainTime;            /* PUK码剩余次数      */
    VOS_UINT8                               ucPINLen;                   /* aucPin中数据是否有效 */
    USIMM_PIN_ENABLE_STATUS_ENUM_UINT32     enPinEnable;                /* PIN激活状态        */
    USIMM_PIN_VERIY_STATUS_ENUM_UINT32      enPinVerified;              /* PIN验证状态        */
    VOS_UINT8                               aucPin[USIMM_PINNUMBER_LEN];/* PIN码操作成功后记录下当前PIN码 */
}USIMM_APP_PIN_INFO_STRU;

/*****************************************************************************
 结构名    : USIMM_UICC_ADF_INFO_STRU
 结构说明  : ADF信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulAIDLen;                   /* 当前的AID长度 */
    VOS_UINT8                               aucAID[USIMM_AID_LEN_MAX];  /* 当前AID内容 */
    VOS_UINT8                               ucCharaByte;
    VOS_UINT8                               ucSupCmd;
    VOS_UINT16                              usFcpLen;
}USIMM_UICC_ADF_INFO_STRU;

/*****************************************************************************
 结构名    : USIMM_COMM_PIN_INFO_STRU
 结构说明  :卡应用的PIN信息
*****************************************************************************/
typedef struct
{
    USIMM_PIN_TYPE_ENUM_UINT32              enCurPINType;       /* 当前密码类型 */
    USIMM_COMM_PIN_ENUM_UINT32              enPinKeyRef;        /* PIN1码的KeyReference */
    USIMM_APP_PIN_INFO_STRU                 stPin2Info;         /* PIN2码信息 */
}USIMM_COMM_PIN_INFO_STRU;

/*****************************************************************************
 结构名    : USIMM_COMM_CARD_APP_INFO_STRU
 结构说明  : 卡应用信息
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32               enAppType;          /* 当前应用使用的类型 */
    USIMM_CARD_SERVIC_ENUM_UINT32           enAppService;       /* 当前卡的状态 */
    USIMM_SIM_PHASE_ENUM_UINT32             enSimPhase;         /* 指示SIM卡的阶段 */
    USIMM_CURFILEINFO_ST                    stCurFileInfo;      /* 当前文件信息 */
    USIMM_UICC_ADF_INFO_STRU                stAdfInfo;          /* 当前应用的UICC信息 */
    USIMM_COMM_PIN_INFO_STRU                stPinInfo;          /* 当前应用的PIN信息 */
    USIMM_FDNSTATUS_ENUM_UINT32             enFDNStatus;        /* 当前FDN状态 */
    USIMM_BDNSTATUS_ENUM_UINT32             enBDNStatus;        /* 当前BDN状态 */
}USIMM_COMM_CARD_APP_INFO_STRU;

/*****************************************************************************
 结构名    : PUSIMPROTECTPROC
 结构说明  : 保护性复位函数指针类型
*****************************************************************************/
typedef VOS_UINT32 (*PUSIMPROTECTPROC)(VOS_VOID);

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
#if(FEATURE_ON == FEATURE_PTM)
extern USIMM_MNTN_STATE_ERROR_EVENT_STRU    g_stCardErrorLog;

extern NV_ID_ERR_LOG_CTRL_INFO_STRU         g_stErrLogCtrlInfo;
#endif

extern USIMM_BASE_INFO_ST                    gstUSIMMBaseInfo;

extern VOS_UINT32                            gulUsimSupportIMS;

extern USIMM_ISIMUSIM_EFTBL_STRU             g_astUSIMMIsimUsimEFTBL[USIMM_ISIMEFTOUSIMEF_TBL_SIZE];

extern USIMM_DRV_INFO_ST                     gstUSIMMDrvInfo;

extern USIMM_AID_INFO_STRU                   g_astUSIMMInitAIDInfo[USIMM_CARDAPP_BUTT];

extern USIMM_LOG_DATA_STRU                   g_stUSIMMLogData;

extern VOS_UINT32                            g_ulUSIMMExcLogLenBK;

extern USIMM_LOG_DATA_STRU                   g_stUSIMMExcLogData;

extern USIMM_POOL_ST                         gstUSIMMPOOL;

extern VOS_UINT32                            gulUSIMMOpenSpeed;

extern VOS_UINT16                            gausInitFileOne[USIMM_INITFIRST_FILENUM];

extern USIMM_OPFILE_LIST_STRU gastSimInitOFile[USIMM_INITSIM_OFILENUM];

extern USIMM_OPFILE_LIST_STRU gastUsimInitOFile[USIMM_INITUSIM_OFILENUM];

extern USIMM_DEF_FILEID_ENUM_UINT32 g_aulAttUsimInitFile[USIMM_USIM_ATT_INITFILE_NUM];

extern USIMM_DEF_FILEID_ENUM_UINT32 g_aulAttSimInitFile[USIMM_SIM_ATT_INITFILE_NUM];

extern USIMM_FEATURE_CFG_STRU       g_stUsimmFeatureCfg;

extern VOS_UINT32                   g_ulATTSpecErrSWCnt;

extern USIMM_CHANNEL_RESPONSE_STRU  g_astUSIMMChGetRsp[USIMM_CHANNEL_NUMBER_MAX];

extern USIMM_CARD_INIT_INFO_LOG_STRU       g_stUSIMMInitInfo;

extern USIMM_DL_T_MODE_ENUM_UINT32         g_enUSIMMTMode;
extern VOS_BOOL                            g_bSendIFSReqFlag;

extern USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 g_enTestCardType;

extern USIMM_APP_PIN_INFO_STRU             g_astUSIMMAppPIN1Info[USIMM_KEY_REF_PIN_BUTT];

extern USIMM_STORE_ESN_MEID_STATUS_STRU    g_stStoreEsnMeidStatus;

#if (FEATURE_VSIM == FEATURE_ON)
extern USIMM_VSIM_AUTH_INFO_STRU        g_stUSIMMVSimAuthInfo;

extern USIMM_VSIM_FILE_INFO_STRU        g_astUSIMMVSimFileInfo[];

extern VOS_CHAR                         *g_pcUSIMMVSimXmlFilePath;

extern VOS_UINT8                        *g_pucUSIMMVsimData ;
#endif

extern USIMM_FILEID_PATHSTR_TABLE_STRU g_stUSIMMFilePathTable[USIMM_DEF_FILEID_BUTT];

/*****************************************************************************
  6 Function定义
*****************************************************************************/
#ifdef  USIMM_DEBUG_PEINT
#define USIMM_NORMAL                0
#define USIMM_INFO                  1
#define USIMM_WARNING               2
#define USIMM_ERROR                 3

#define USIMM_NORMAL_LOG(string)    USIMM_PRINT(USIMM_NORMAL,string)
#define USIMM_INFO_LOG(string)      USIMM_PRINT(USIMM_INFO,string)
#define USIMM_WARNING_LOG(string)   USIMM_PRINT(USIMM_WARNING,string)
#define USIMM_ERROR_LOG(string)     USIMM_PRINT(USIMM_ERROR,string)
#else
#define USIMM_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_USIM), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define USIMM_NORMAL_LOG(string)    (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#define USIMM_INFO_LOG(string)      (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#define USIMM_WARNING_LOG(string)   (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#define USIMM_ERROR_LOG(string)     (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#endif
VOS_UINT32 USIMM_UiccProtectReactiveChannels(VOS_VOID);

extern VOS_VOID USIMM_LogDataClear(VOS_VOID);

extern VOS_UINT32 USIMM_CdmaSpecAuthHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_QueryEsnMeidRsltHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_RAccessPathHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usFileID,
    VOS_UINT8                           ucPathLen,
    VOS_UINT16                         *pusPath,
    USIMM_RESTRIC_CMD_ENUM_UINT32       ulCmdType);

extern VOS_UINT32 USIMM_RAccessHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_RefreshHandle(
    USIMM_CMDHEADER_REQ_STRU                *pMsg);

extern VOS_VOID USIMM_ChangePathToU16(
    VOS_UINT32                              ulDataLen,
    VOS_UINT8                               *pucData,
    VOS_UINT32                              *pulLen,
    VOS_UINT16                              *pusPath);

extern VOS_UINT32 USIMM_SelectFile(
    USIMM_CARDAPP_ENUM_UINT32               enAppType,
    USIMM_FILE_NEED_FCP_ENUM_UINT32         enEfFcpFlag,
    USIMM_FILEPATH_INFO_STRU                *pstFilePath);

extern VOS_UINT32  USIMM_GetDefTFMem(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                         *pusReadLen,
    VOS_UINT8                          **pucData);

extern VOS_UINT32  USIMM_GetTFByDefFID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                          usReadLen,
    VOS_UINT8                          *pucData);

extern VOS_UINT32  USIMM_WriteTFFileByDefID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucData);

extern VOS_VOID USIMM_PRINT(
    VOS_UINT32                          ulPrintLev,
    VOS_INT8                            *pucString);

extern VOS_UINT32 USIMM_SelectDFFile(
    VOS_UINT16                          usFileId,
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectEFByID(
    VOS_UINT16                          usFileId,
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectFileWithPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen
);

extern VOS_UINT32 USIMM_ReadLFFile(
    USIMM_CARDAPP_ENUM_UINT32            enAppType,
    USIMM_EFFCP_ST                      *pstCurEFFcp,
    VOS_UINT8                            ucRecordNum,
    VOS_UINT8                           *pucContent);

extern VOS_UINT32 USIMM_STATUSProc(VOS_VOID);

extern VOS_UINT32 USIMM_VerifyNCK(
    VOS_UINT8                           ucLen,
    VOS_UINT8                           *pucPassword);

extern VOS_UINT32 USIMM_VerifyPCK(
    VOS_UINT8                           ucLen,
    VOS_UINT8                           *pucPassword);

extern VOS_UINT32 USIMM_ChangePIN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           *pucOldPIN,
    VOS_UINT8                           *pucNewPIN);

extern VOS_UINT32 USIMM_UnblockPIN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           *pucPUK,
    VOS_UINT8                           *pucNewPIN);

extern VOS_UINT32 USIMM_PINVerify(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           ucPINCmd,
    VOS_UINT8                           *pucPIN);

extern VOS_UINT32 USIMM_InitUsimFDNBDNStatus(VOS_VOID);

extern VOS_VOID USIMM_FdnCapabilityRequest(
    USIMM_FDNSTATUS_ENUM_UINT32         *pulFdnStatus);

extern VOS_VOID USIMM_BdnCapabilityRequest(
    USIMM_BDNSTATUS_ENUM_UINT32         *pulBdnStatus);

extern VOS_UINT32 USIMM_SimFDNBDNProcess(VOS_VOID);

extern VOS_UINT32 USIMM_UICCFDNEnable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_ICCFDNEnable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_UICCFDNDisable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_ICCFDNDisable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_FDNEstChgInd(VOS_VOID);

extern VOS_UINT32 USIMM_FindTagInBERTLV(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT8                           ucTag,
    VOS_UINT32                          ulDataLen);

extern VOS_UINT32 USIMM_FindTagInSMPTLV(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT8                           ucTag,
    VOS_UINT32                          ulDataLen);

extern VOS_UINT32 USIMM_FindTagInCTLV(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT8                           ucTag,
    VOS_UINT32                          ulDataLen);

extern VOS_UINT32 USIMM_GetBitFromBuf(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT32                          ulBitNo,
    VOS_UINT32                          ulBufLen);

extern VOS_UINT32 USIMM_DecodeEFFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCurCardType,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeDFFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCurCardType,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeFileFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_ReportEvent(
    VOS_UINT16                          usEventId);

extern VOS_VOID USIMM_RefreshFileIndHandle(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_REFRESH_FILE_TYPE_UINT16 USIMM_GetRefreshIndType(
    USIMM_STKREFRESH_REQ_STRU                   *pstMsg);

extern VOS_UINT32 USIMM_CardFilePathCMP(
    VOS_UINT32                          ulPath1Len,
    VOS_UINT16                          *pusPath1,
    VOS_UINT32                          ulPath2Len,
    VOS_UINT16                          *pusPath2);

extern VOS_BOOL USIMM_IsCLEnable(VOS_VOID);

extern VOS_UINT8 USIMM_GetRATMode(VOS_VOID);

extern USIMM_NV_CARDAPP_ENUM_UINT32 USIMM_GetPreferApp(VOS_VOID);

extern VOS_VOID USIMM_FileAccessFix( VOS_VOID );

extern VOS_VOID USIMM_SetAccFileAccess( VOS_VOID );

extern VOS_VOID USIMM_SetImsiFile(VOS_VOID);

extern VOS_UINT32 USIMM_IS_EF_FILE(
    VOS_UINT16                          usFileId);

extern VOS_UINT32 USIMM_GetFreeAppInfo(
    VOS_UINT32                          *pulIndex);

extern VOS_UINT32 USIMM_SelectAIDFile(
    VOS_UINT8                           ucChannelNo,
    USIMM_SELECT_P2_PARA_ENUM_UINT8     enMode,
    USIMM_AID_INFO_STRU                *pstAIDInfo,
    USIMM_APDU_RSP_STRU                *pstApduRsp
);

extern VOS_UINT32 USIMM_CloseChannel(
    VOS_UINT8                           ucChannelID);

extern VOS_UINT32 USIMM_OpenChannel(
    VOS_UINT8                           *pucChannelNo);

extern VOS_BOOL USIMM_SearchAllAID(
    VOS_UINT32                          ulAIDLen,
    VOS_UINT8                           *pucAID,
    VOS_UINT8                           *pucChannelNo);

extern VOS_VOID USIMM_RecordCardErrorLog(
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32                   enErrorReason,
    USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16                          enAlmLevel);

extern VOS_UINT32 USIMM_MakeCHAPCmdData(
    USIMM_COMPUTEIP_CHAP_STRU           *pstChapData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeMNHACmdData(
    USIMM_COMPUTEIP_MNHA_STRU           *pstMNHAData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeMIPCmdData(
    USIMM_COMPUTEIP_MIPRRQHASH_STRU     *pstMIPData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeMNAAACmdData(
    USIMM_COMPUTEIP_MNAAA_STRU          *pstMNAAAData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeHRPDCmdData(
    USIMM_COMPUTEIP_HRPD_STRU           *pstHRPDData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_CdmaSpecAuthComputeIP(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_COMPUTEIP_AUTH_STRU           *pstComputeIP);

extern VOS_UINT32 USIMM_CdmaSpecAuthComputeIP(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_COMPUTEIP_AUTH_STRU           *pstComputeIP);

extern VOS_UINT32 USIMM_MakeRetrieveSKData(
    USIMM_BCMCS_RETRIEVESK_STRU         *pstRetrieveSK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeUpdateBAKData(
    USIMM_BCMCS_UPDATABAK_STRU          *pstUpdateBAK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeDeleteBAKData(
    USIMM_BCMCS_DELETEBAK_STRU          *pstDeleteBAK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeReSRTPData(
    USIMM_BCMCS_RETRIEVE_SRTPSK_STRU    *pstReSRTPSK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeGenAuthData(
    USIMM_BCMCS_GENAUTH_SIGN_STRU       *pstGenAuthSign,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeBCMCSAuthData(
    USIMM_BCMCS_AUTHENTICATION_STRU     *pstAuthentication,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_CdmaSpecAuthBCMCS(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_BCMCS_DATA_STRU               *pstBCMCS);

extern VOS_UINT32 USIMM_CdmaSpecAuthApp(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_CDMAAPP_AUTH_STRU             *pstAppAuth);

extern VOS_VOID USIMM_CheckTimeOutError(VOS_VOID);

/*POOL操作函数*/

extern VOS_UINT32 USIMM_VsimPoolSearchFile(
    VOS_UINT16                          usFileId,
    VOS_UINT32                          *pulData);

extern VOS_UINT32 USIMM_PoolFindFile(
    VOS_UINT16                          usEFileId,
    VOS_UINT32                         *pulPoolIndex,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_PoolInsertOneFile(
    USIMM_POOL_ONERECORD_ST             *pstRecord);

extern VOS_UINT32 USIMM_PoolUpdateOneFile(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usFileID,
    VOS_UINT32                          ulNewLen,
    VOS_UINT8                           *pucNewData);

extern VOS_UINT32 USIMM_InsertFileToPool(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID);

extern VOS_UINT32 USIMM_PoolDelOneFile(
    VOS_UINT16                          usFileId,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_PoolReadOneFile(
    VOS_UINT16                          usFileId,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_PoolDelFilesByAppType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_PoolDelAll(VOS_VOID);

extern VOS_VOID USIMM_PoolDelOneRecByIndex(
    VOS_UINT32                          ulIndex);

extern VOS_VOID USIMM_PoolInsertOneRecByIndex(
    VOS_UINT32                           ulIndex,
    USIMM_POOL_ONERECORD_ST             *pstRecord
);
extern VOS_VOID USIMM_ClearCurDFInfo(
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurEFInfo(
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurFileInfo(
    USIMM_CARDAPP_ENUM_UINT32           enCardApp);

extern VOS_VOID USIMM_OpenSpeedFileInit(VOS_VOID);

extern VOS_UINT32 USIMM_InitProfileStep(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardOptionalFile(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_VOID USIMM_AttUpdataSupportTable(
    VOS_UINT8                           ucChannelID);

extern VOS_VOID USIMM_AttEfTerminalSupportTableValueGet(
    VOS_UINT8                           *pucValue);

extern VOS_UINT32 USIMM_InitUsimEccFile(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimEccFile(
    VOS_UINT8                           ucChannelID);

extern VOS_UINT32 USIMM_SelectFileNoPath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo,
    VOS_UINT16                          *pusCurPathLen);

extern VOS_UINT32 USIMM_SelectFileByPath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectFileByRelativePath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_UpdateFilePath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstUSIMMCurFileInfo);

extern VOS_VOID USIMM_UpdateFileByRelativePath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstUSIMMCurFileInfo);

extern VOS_VOID USIMM_SciDataHook(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           *pucData);

extern USIMM_CARDAPP_ENUM_UINT32 USIMM_GetAIDType(
    VOS_UINT32                          ulAidLen,
    VOS_UINT8                           *pucAid);

extern VOS_VOID USIMM_RefreshNoFileIndHandle(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_VOID USIMM_RefreshInd(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_STKREFRESH_REQ_STRU          *pstMsg);

extern VOS_UINT32 USIMM_UsimRefreshFilePbAppCheck(
    VOS_UINT16                          *pusFilePath,
    VOS_UINT32                          ulPathLen);

extern VOS_VOID USIMM_RefreshIsimFileIndHandle(
    USIMM_STKREFRESH_IND_STRU           *pstRefreshMsg);

extern VOS_UINT32 USIMM_GetEFPathFromFList(
    VOS_UINT8                          *pucFileList,
    VOS_UINT32                          ulFileLen,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    VOS_UINT32                         *pulLen);

extern VOS_UINT32 USIMM_RefreshNoReset(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_UINT32 USIMM_RefreshUICCFile(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_UINT32 USIMM_RefreshICCFile(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_VOID USIMM_RefreshCardFile(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_BOOL                            bUpdatePool);

extern VOS_VOID USIMM_SendRefreshTR(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg,
    VOS_UINT32                          ulResult);

extern VOS_UINT32 USIMM_SelectFileByDefFileId(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId
);

/*log保存接口*/
extern VOS_VOID USIMM_InitLogFile(VOS_VOID);

extern VOS_VOID USIMM_SaveLogFile(VOS_VOID);

extern VOS_VOID USIMM_LogDataSave(
    VOS_UINT8                           *pucData,
    VOS_UINT8                           ucDataLen);

extern VOS_VOID USIMM_ExcLogDataClear(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataSave(
    VOS_UINT8                           *pucData,
    VOS_UINT8                           ucDataLen);

extern VOS_VOID USIMM_ExcLogDataBK(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataRE(VOS_VOID);

extern VOS_VOID USIMM_SaveExcLogFile(VOS_VOID);

extern VOS_VOID USIMM_InitExcLogFile(VOS_VOID);

/*Base Func*/
extern VOS_UINT32  USIMM_PinStatusCheck(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_CMD_TYPE_ENUM_UINT32      enCmdType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT32                         *pulResult
);
extern VOS_UINT32 USIMM_SAT_TerminalResopnse(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_SAT_Envelope(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_PINHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_CheckChangeCardByICCID(VOS_VOID);

extern VOS_UINT32 USIMM_PinPreProcHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PINHANDLE_REQ_STRU           *pstMsg
);

extern VOS_UINT32 USIMM_PinHandleCardStatusCheck(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_BuildPrePinInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_INFO_STRU                *pstPINInfo
);

extern VOS_UINT32 USIMM_ProtectReset(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg);

extern VOS_UINT32 USIMM_ProtectResetProc(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType);

extern VOS_UINT32 USIMM_UiccProtectResetProc(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectResetProc(VOS_VOID);

extern VOS_UINT32 USIMM_UiccProtectResumeAppStep(VOS_VOID);

extern VOS_UINT32 USIMM_UiccProtectProfileDownloadStep(VOS_VOID);

extern VOS_UINT32 USIMM_UiccProtectFirstStep(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectFdnBdnStep(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectProfileDownloadStep(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectAutoVerifyPin(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectFirstStep(VOS_VOID);

extern VOS_UINT32 USIMM_StatusHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_SetFileCommHandle(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_UpdateFile(
    USIMM_EF_TYPE_ENUM_UINT32           enEFFileType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 USIMM_SetSPBFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_ChannelCmdParaCheck(
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg);

extern VOS_VOID USIMM_SAT_Fetch(
    VOS_UINT16                          usLen);

extern VOS_UINT32 USIMM_GetRealFile(
    USIMM_READFILE_REQ_STRU             *pstReadMsg,
    VOS_UINT16                          usEFID);

extern VOS_VOID USIMM_ErrorLogProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID USIMM_MsgProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);
#endif

extern VOS_UINT32 USIMM_UsimVoltageSwitch(
    VOS_UINT8                           ucCharaByte,
    VOS_UINT8                           *pucVoltageMismatchFlag);

extern VOS_VOID USIMM_UsimTerminalCapability(VOS_VOID);

extern VOS_VOID USIMM_QueryPINType(
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info,
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info,
    VOS_UINT8                          *pucPINType
);

extern VOS_UINT32 USIMM_HandlePINType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucCmdType,
    VOS_UINT32                         *pulPINType
);

extern USIMM_DEF_FILEID_ENUM_UINT32 USIMM_IsimEFIDToUsimEFID(
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimID);

extern USIMM_DEF_FILEID_ENUM_UINT32 USIMM_UsimEFIDToIsimEFID(
    USIMM_DEF_FILEID_ENUM_UINT32        enUsimID);

extern VOS_UINT8 USIMM_GetMncLen(
    VOS_UINT8                           *pucAdContent,
    VOS_UINT32                          ulFileSize);

extern VOS_VOID USIMM_GetAsciiMCCAndMNC(
    VOS_UINT8                           *pucAsciiImsi,
    VOS_UINT8                           *pucAsciiMCC,
    VOS_UINT8                           *pucAsciiMNC);

extern VOS_VOID USIMM_BcdNumToAsciiNum(
    VOS_UINT8                           *pucAsciiNum,
    VOS_UINT8                           *pucBcdNum,
    VOS_UINT8                           ucBcdNumLen);

extern VOS_UINT32 USIMM_ImsiBcd2Ascii(
    VOS_UINT8                           *pucAsciiStr);

extern VOS_UINT32 USIMM_InitIsimHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_GetReadFilePara(
    VOS_UINT8                           ucRecordNum,
    USIMM_EFFCP_ST                      *pstEFInfo,
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo);

extern VOS_UINT32 USIMM_ReadFile(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_EFFCP_ST                     *pstCurEFFcp,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo);

extern VOS_UINT32 USIMM_IsSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsUSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsISIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsUIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsCSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_GetFileFromCard(
    USIMM_GET_COMM_FILE_STRU            *pstFileInfo,
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo);

extern VOS_UINT32 USIMM_CheckSetFilePara(
    USIMM_EFFCP_ST                      *pstCurEFFcp,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT16                          usDataLen);

/*vSIM API*/
extern VOS_VOID USIMM_InitVsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_SetVsimFile(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_GetVsimFile(
    USIMM_READFILE_REQ_STRU             *pstReadMsg,
    VOS_UINT16                          usEFID);

extern VOS_VOID USIMM_VsimConfidentialDataVerifyErrHandle(VOS_VOID);

extern VOS_UINT32 USIMM_VsimConfidentialDataVerify(VOS_VOID);

extern VOS_UINT32 USIMM_VsimBase16Decode(
    VOS_CHAR                            *pcSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen);

extern VOS_VOID USIMM_VsimBase16Encode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          ulLen);

extern VOS_UINT32 USIMM_VirtualSimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_VirtualUsimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_VirtualAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_DeactiveVsim(
    USIMM_MsgBlock                      *pMsg);

extern VOS_UINT32 USIMM_InitVsimCard(
    USIMM_MsgBlock                      *pMsg);

extern VOS_UINT32 USIMM_VsimGetRealKiOpc(
    VOS_UINT8                           *pucKi,
    VOS_UINT8                           *pucOpc);

extern VOS_UINT32 USIMM_CheckVsimFileInPool(VOS_VOID);

extern VOS_UINT32 USIMM_VsimHUKDecode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen);

extern VOS_UINT32 USIMM_AddVsimFileToPool(
    VOS_CHAR                            *pucFileStr,
    VOS_UINT32                          ulStrLen,
    VOS_CHAR                            *pcValue,
    VOS_UINT32                          ulValueLen);

extern VOS_UINT32 USIMM_AddVsimAuthPara(
    VOS_CHAR                            *pucFileStr,
    VOS_UINT32                          ulFileLen,
    VOS_CHAR                            *pcValue,
    VOS_UINT32                          ulValueLen);

extern VOS_UINT32 USIMM_AddVsimVerifyHashPara(
    VOS_CHAR                            *pucFileStr,
    VOS_UINT32                          ulFileLen,
    VOS_CHAR                            *pcValue,
    VOS_UINT32                          ulValueLen);

extern VOS_UINT32 USIMM_DecodeVsimEf(
    OAM_XML_NODE_STRU                   *pstXmlNode);

extern VOS_VOID USIMM_VsimDecodeCardType(
    VOS_CHAR                            *pucStr,
    VOS_UINT32                          ulStrLen,
    USIMM_PHYCARD_TYPE_ENUM_UINT32      *pulCardType);

extern VOS_VOID USIMM_VsimDecodeAuthType(
    VOS_CHAR                            *pucStr,
    VOS_UINT32                          ulStrLen,
    USIMM_VSIM_AUTH_ENUM_UINT32         *pulAuthType);

extern VOS_UINT32 USIMM_DecodeVsimRoot(
    OAM_XML_NODE_STRU                   *pstXmlNode,
    USIMM_PHYCARD_TYPE_ENUM_UINT32      *pulCardType,
    USIMM_VSIM_AUTH_ENUM_UINT8          *pucAuthType);

extern VOS_UINT32 USIMM_DecodeVsimFile(
    VOS_UINT8                           *pucData);

extern VOS_UINT8* USIMM_ReadVsimFile(
    VOS_UINT32                          ulReadPID);

extern VOS_UINT32 USIMM_InitCardHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_DeactiveRealCard(
    USIMM_MsgBlock                      *pMsg);

extern VOS_VOID USIMM_CardStatusRegCbFuncProc(VOS_VOID);

extern VOS_UINT32 USIMM_CardStatusHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg);

extern VOS_UINT32 USIMM_CheckAIDFcp(
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg,
    USIMM_SENDTPDU_CNFINFO_STRU         *pstDataCnf);

extern VOS_UINT32 USIMM_SelectTPDUProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_GutlAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_ImsAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_CdmaAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_IsimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_USIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_SIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_VOID USIMM_IsimAkaAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_IsimHttpAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_IsimGbaAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_IsimNafAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_UINT32 USIMM_AuthenticationHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_BSChallengeHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg);

extern VOS_UINT32 USIMM_ManageSsdHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_GenerateKeyVpmHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_ReadFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_UpdateFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_FDNHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_QueryFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_SearchFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_SendTPDUDataHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

/*外部接口*/
extern VOS_VOID HPA_USIMLowPowerLock(
    VOS_UINT32                          ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock(
    VOS_UINT32                          ulPid );

extern USIMM_CARD_TYPE_ENUM_UINT32 USIMM_COMM_CardAppToType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType
);

extern VOS_UINT32 USIMM_DecideTMode(
    SCI_ATRINFO_S                       *pstSCIATRInfo);

extern VOS_UINT32 USIMM_AuthenticationDataFillDataProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_U8_DATA_STRU                 *pstData);

extern VOS_VOID USIMM_SendTPDUCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    USIMM_SENDTPDU_CNFINFO_STRU        *pstDataCnf,
    USIMM_CURFILEINFO_ST               *pstCurFile);

extern VOS_UINT32 USIMM_GetFileCommHandle(
    USIMM_READFILE_REQ_STRU            *pstReadMsg,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_CardInOutHandle(
    USIMM_CMDHEADER_REQ_STRU           *pMsg);

extern VOS_UINT32 USIMM_OpenChannelHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_CloseChannelHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_VOID USIMM_ApplicationMsgProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_ISIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_GetResponseTPDUProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_BOOL USIMM_CheckSupportAP(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#else

#include "UsimmApi.h"
#include "UsimPsInterface.h"
#include "omnvinterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "OamXmlComm.h"
#include "omerrorlog.h"
#include "pamom.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_VSIM == FEATURE_ON)

#define USIMM_VSIM_TYPE_STR         "TYPE"
#define USIMM_VSIM_USIM_STR         "USIM"
#define USIMM_VSIM_SIM_STR          "SIM"
#define USIMM_VSIM_AUTH_STR         "ALGORITHM"
#define USIMM_VSIM_AUTH_3G_STR      "MILENAGE"
#define USIMM_VSIM_AUTH_2GV1_STR    "COMP128V1"
#define USIMM_VSIM_AUTH_2GV2_STR    "COMP128V2"
#define USIMM_VSIM_AUTH_2GV3_STR    "COMP128V3"
#define USIMM_VSIM_KI_STR           "EFKI"
#define USIMM_VSIM_OPC_STR          "EFOPC"
#define USIMM_VSIM_VERIFY_HASH_STR  "VERIFYHASH"
#define USIMM_VSIM_NAME_STR         "NAME"
#define USIMM_VSIM_HASH_LEN         (32)

#endif

#define USIMM_CHANNEL_NUMBER_MAX        (20)

/*fid优先级*/
#define MAPS_USIMM_FID_PRIORITY         VOS_PRIORITY_P1

//快速开机的始能
#define USIMM_OPENSPEEDENABLE           0x01000101
#define USIMM_OPENSPEEDDISABLE          0x00000000

/*Ecc类型*/
#define ECC_USIM                        1
#define ECC_SIM                         0

/*ATR tag*/
#define CTLV_IND_TAG                    0x80
#define CARD_SVR_TAG                    0x30
#define CARD_CPB_TAG                    0x70
#define CARD_CPB3_TAG                   0x73

/*EFDIR tag*/
#define APP_TMP_TAG                     0x61
#define APP_IND_TAG                     0x4F

#define APP_TMP_TAG_OFFSET              (0)
#define APP_IND_TAG_OFFSET              (2)
#define APP_AID_LEN_OFFSET              (3)
#define APP_AID_VALUE_OFFSET            (4)


#define USIMM_RID_LEN                   (5)
#define USIMM_APP_CODE_LEN              (2)

/*fcp tag*/
#define USIMM_FCP_TAG                   0x62
#define USIMM_FCP_FILE_DES_TAG          0x82
#define USIMM_FCP_FID_TAG               0x83
#define USIMM_FCP_NAME_TAG              0x84
#define USIMM_FCP_PRIVITE_TAG           0xA5
#define USIMM_FCP_CHARA_TAG             0x80
#define USIMM_FCP_SA_CF_TAG             0x8C
#define USIMM_FCP_SA_EF_TAG             0xAB
#define USIMM_FCP_SA_REF_TAG            0x8B
#define USIMM_FCP_PIN_TO_TAG            0xC6
#define USIMM_FCP_FILESIZE_TAG          0x80
#define USIMM_FCP_SFI_TAG               0x88
#define USIMM_FCP_PRO_INFO_TAG          0xA5
#define USIMM_FCP_LCSI_TAG              0x8A
#define USIMM_FCP_TOTAL_SIZE_TAG        0x81
#define USIMM_FCP_PINMAP_TAG            0x90
#define USIMM_FCP_PINRER_TAG            0x83
#define USIMM_FCP_PINQUALIFER_TAG       0x95
#define USIMM_FCP_SUPSYSCMD_TAG         0x87


/*Usimm DL调用返回值*/
#define USIMM_DL_SUCESS                 0
#define USIMM_DL_SEND_ERROR             1
#define USIMM_DL_RECEIVE_ERROR          2

/*文件池最大文件数目*/
#define POOLMAXNUM                      32

/*二进制文件池最大文件空间*/
#define USIMM_MAX_FILE_SIZE             0x2000

/*初始化文件数定义,分为不受PIN保护的，和受PIN保护的Mandatory和Optional文件*/
#define USIMM_INITFIRST_FILENUM        2
#define USIMM_INITSIM_MFILENUM         8
#define USIMM_INITUSIM_MFILENUM        12
#define USIMM_INITSIM_OFILENUM         12
#define USIMM_INITUSIM_OFILENUM        15

/* Optional文件初始化最大文件个数 */
#define USIMM_INIT_OFILE_MUX_NUM       (16)

/* ATT定制文件初始化文件列表长度 */
#define USIMM_USIM_ATT_INITFILE_NUM     2
#define USIMM_SIM_ATT_INITFILE_NUM      1

//文件关系的值定义
#define USIMM_SIMDFGSMGDF_MAX           2
#define USIMM_SIMDFTELGDF_MAX           1
#define USIMM_SIMDFCONTENT_MAX          2

#define USIMM_USIMADFGDF_MAX            4
#define USIMM_USIMADFTELGDF_MAX         2
#define USIMM_USIMDFCONTENT_MAX         3

/*读取文件*/
#define USIMM_READ_ALLRECORD            0

/*判断卡复位状态的循环次数*/
#define USIMM_GET_SCISTATUS_MAX         300

/*复位卡操作类型*/
#define USIMM_RESET_CARD                0
#define USIMM_CHANGE_VCC                1

/*SCI操作结果定义*/
#define USIMM_SCI_SUCCESS               0
#define USIMM_SCI_NONEED_CHANGEVCC      1

/*读取全部文件内容*/
#define USIMM_READ_ALL_FILE_CONTENT     0

/*保护性复位事件*/
#define USIMM_PROTECT_RESET             0xFF

#define USIMM_PROTECT_MAX_NUM           (3)

/*当前记录文件最大个数，结构体中使用需要4字节对齐*/
#define USIMM_LOG_FILE_MAX_NUM          (4)

/*当前记录文件最大姓名，结构体中使用需要4字节对齐*/
#define USIMM_LOG_FILE_NAME_LEN         (0x10)

#define USIMM_LOG_DATA_TAG              (0x5A)

#define USIMM_LOG_START_TAG             (0x5555AAAA)

/*当前记录的数据区域的大小*/
#define USIMM_LOG_DATA_MAX_LEN          (8*1024)
#define USIMM_EXCLOG_DATA_MAX_LEN       (4*1024)

/* ATT定制Support Table的长度 */
#define USIMM_ATT_SUPPORT_TABLE_MAX     (16)
#define USIMM_ATT_SUPPORT_TABLE_MIN     (8)

/* ATT定制Support Table字节偏移量 */
#define USIMM_ATT_SCAN_CTRL_OFFSET          (0)
#define USIMM_ATT_NETWORK_SELECTION_OFFSET  (1)
#define USIMM_ATT_ACTING_HPLMN              (2)
#define USIMM_ATT_3G_SUPPORT                (3)
#define USIMM_ATT_RAT_BALANCING             (4)
#define USIMM_ATT_BIP_SUPPORT               (5)
#define USIMM_ATT_LTE_SUPPORT               (6)
#define USIMM_ATT_CSG_SUPPORT               (7)

/* ATT定制Support Table中LTE特性 */
#define USIMM_ATT_LTE_DATA_ONLY             (0x01)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB       (0x02)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB_IMS   (0x03)


#define USIMM_ENVELOPE_PPDOWN                (0xD1)
#define USIMM_ENVELOPE_CBDOWN                (0xD2)

/* ATR信息 */
#define USIMM_ATR_MAX_LEN                   (80)
#define USIMM_ATR_T0_OFFSET                 (1)

/* 逻辑通道最大个数 */
#define USIMM_CHANNEL_NUM_MAX               (4)

/* Session ID最大值 */
#define USIMM_SESSION_ID_MAX                (0x7fffffff)

/* 通道号最大值 */
#define USIMM_CHANNEL_INVALID_NUM           (0xffffffff)

/* UICC基本通道号 */
#define USIMM_BASE_CHANNEL_NUM              (0)

/* 根据随机数和通道号获得SessionID */
#define USIMM_SESSION_ID(RandNum, ChannelID) \
        ((RandNum & (~(USIMM_CHANNEL_NUM_MAX - 1))) | ChannelID)

#define USIMM_RAND_SEED_MAX                 (0xffffffff)

/* 尝试发送选择文件APDU的最大次数 */
#define USIMM_SELECT_MAX_TIME               (3)

#define USIMM_SIM_SELECT_P2_PARA            (0x00)

/*USIMM模块支持的最大APDU命令长度*/
#define USIMM_APDU_MAXLEN                   (256)

#define USIMM_2G_AUTH_SRES_LEN              (4)
#define USIMM_2G_AUTH_KC_LEN                (8)

/* 鉴权数据中使用的TAG标示 */
#define USIMM_GBA_AUTH_TAG                  (0xDD)
#define USIMM_NAF_AUTH_TAG                  (0xDE)
#define USIMM_AUTH_SUCCESS_TAG              (0xDB)
#define USIMM_AUTH_SYNC_FAIL_TAG            (0xDC)


/* 鉴权模式定义，对应APDU中的P2参数 */
#define USIMM_SIM_2G_AUTH_MODE              (0x00)
#define USIMM_USIM_2G_AUTH_MODE             (0x80)
#define USIMM_USIM_3G_AUTH_MODE             (0x81)
#define USIMM_USIM_GBA_AUTH_MODE            (0x84)

/* 获得输入文件类型 */
#define USIMM_FILE_TYPE(usFileId)           (VOS_UINT8)((usFileId>>0x08)&0x00FF)

/* 判断输入文件是否为DF文件 */
#define USIMM_IS_DF_FILE(usFileId) \
        (USIMM_DF_FILE == ((usFileId>>0x0C)&0x01))


#define USIMM_FILE_PATH_MAX_LEN         100

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )
#define USIMM_LOG_PATH                  "Sim1"
#define USIMM_LOGCTRL_FILE              "Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          USIMM_LOG_PATH

#define USIMM_UNITARY_LOGCTRL_FILE      USIMM_LOGCTRL_FILE

#elif (( VOS_VXWORKS == VOS_OS_VER ) || ( VOS_RTOSCK == VOS_OS_VER ))
#if defined (INSTANCE_1)    /*SIM card 1*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim1"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim1"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim1/usimmlogctrl.bin"
#elif defined (INSTANCE_2)   /*SIM card 2*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim2"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim2/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim2"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim2/usimmlogctrl.bin"
#else                       /*SIM Card 0*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim0"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim0/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim0"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim0/usimmlogctrl.bin"

#endif /* end of INSTANCE_1*/
#endif /* end of VOS_WIN32*/


#define USIMM_MNC_TWO_BYTES_LEN        (2)             /* MNC长度为2 */
#define USIMM_MNC_THREE_BYTES_LEN      (3)             /* MNC长度为3 */
#define USIMM_AD_MNC_LEN_POS           (3)             /* AD文件中MNC长度字段所在位置 */
#define USIMM_IMSI_MAX_LEN             (8)             /* IMSI中指示长度的最大值 */

#define USIMM_BIT_NUM_IN_BYTE          (8)             /* 一个字节中包含的bit数 */
#define USIMM_MNC_MCC_FIG_NUM          (3)             /* MNC,MCC数字个数，MNC数字不足3个时，补0 */
#define USIMM_ISIMEFTOUSIMEF_TBL_SIZE  (5)             /* ISIM文件到USIM文件转换表大小 */

#define USIMM_ISIM_FILE_TAG            (0x80)

#define USIMM_AUTH_XRES_LEN             (8)     /* 3G鉴权的返回数据     */
#define USIMM_AUTH_RES_LEN              (4)     /* 2G鉴权的返回数据     */
#define USIMM_AUTH_CK_LEN               (16)    /* 3G鉴权的CK           */
#define USIMM_AUTH_IK_LEN               (16)    /* 3G鉴权的IK           */
#define USIMM_AUTH_KC_LEN               (8)     /* 2G鉴权的Kc           */
#define USIMM_AUTH_KI_LEN               (16)    /* 鉴权的KI             */
#define USIMM_AUTH_OPC_LEN              (16)    /* 鉴权的OPC            */

#define USIMM_VSIM_SECUR_MAX_LEN        (32)    /* vSIM里面机密数据长度 */

#define USIMM_VSIM_SIM_KEY_HASH_LEN     (96)    /* IMSI+KI+OPC加密长度  */


#if (FEATURE_VSIM == FEATURE_ON)
#define USIMM_VSIM_IS_FILE_ATTR_VALID(index)      ( (USIMM_MANDATORY_FILE         == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                  ||((USIMM_USIM_MANDATORY_FILE  == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_CARD_USIM         == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)) \
                                                  ||((USIMM_SIM_MANDATORY_FILE   == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_CARD_SIM          == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)) )
#endif

#define USIMM_SIM_REFRESH_IS_NEED_TP(enRefreshType)      ( (USIMM_INITIAL_FULL_FILE_CHANGE_NOTIFY == (enRefreshType)) \
                                                        || (USIMM_INITIAL_FILE_CHANGE_NOTIFY == (enRefreshType)) \
                                                        || (USIMM_INITIALIZATION == (enRefreshType)) )


#define USIMM_EF_CST_MAX_LEN            (12)

#define USIMM_HUK_LEN                   (0x10)

#define USIMM_HUK_BITS                  (128)

#define USIMM_EFICCID_LEN               (10)

#define USIMM_MNTN_INFODATA_MAX           (64)


/*******************************************************************************
  3 枚举定义
*******************************************************************************/
typedef VOS_UINT32 (*PCARDINITPROC)(VOS_VOID);

typedef struct
{
    PCARDINITPROC                pProcFun;        /* 处理函数 */
}USIMM_CARD_INIT_FUNC;

typedef struct
{
    USIMM_CARD_INIT_FUNC         *pInitFunTbl;
    VOS_UINT32                   ulStepNum;
}USIMM_CARD_INIT_TBL_ST;

/* MANAGE CHANNEL 命令枚举 即下发数据单元的p1参数，参见协议102.221第11.1.17 */
enum USIMM_MANAGE_CHANNEL_ENUM
{
    USIMM_OPEN_CHANNEL         =0x00,
    USIMM_CLOSE_CHANNEL        =0x80,
    USIMM_MANAGE_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_MANAGE_CHANNEL_ENUM_UINT32;

/*是否支持sfi*/
enum USIMM_SUPPORT_SFI_ENUM
{
    USIMM_NOTSUPPORT_SFI         =0,
    USIMM_SUPPORT_SFI            =1,
    USIMM_SUPPORT_SFI_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SFI_ENUM_UINT32;


/*是否支持path*/
enum USIMM_SUPPORT_PATH_ENUM
{
    USIMM_NOTSUPPORT_PATH       = 0,
    USIMM_SUPPORT_PATH          = 1,
    USIMM_SUPPORT_PATH_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_PATH_ENUM_UINT32;


/*是否支持logic channel*/
enum USIMM_SUPPORT_CHANNEL_ENUM
{
    USIMM_NOTSUPPORT_CHANNEL    = 0,
    USIMM_SUPPORT_CHANNEL       = 1,
    USIMM_SUPPORT_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_CHANNEL_ENUM_UINT32;

enum USIMM_CLKLEVEL_ENUM
{
    USIMM_CLKLEVEL_LOW          = 0,
    USIMM_CLKLEVEL_HIGH         = 1,
    USIMM_CLKLEVEL_NONE         = 2,
    USIMM_CLKLEVEL_BUTT
};
typedef VOS_UINT32      USIMM_CLKLEVEL_ENUM_UINT32;

enum USIMM_CLKSTOP_ENUM
{
    USIMM_CLKSTOP_ALLOW             = 0,
    USIMM_CLKSTOP_NOALLOW           = 1,
    USIMM_CLKSTOP_BUTT
};
typedef VOS_UINT32      USIMM_CLKSTOP_ENUM_UINT32;

enum USIMM_SAT_STATE_ENUM
{
    USIMM_SAT_STATE_NODATA          = 0,
    USIMM_SAT_STATE_NEEDFETCH       = 1,
    USIMM_SAT_STATE_NEEDRESPONSE    = 2,
    USIMM_SAT_STATE_BUTT
};
typedef VOS_UINT32      USIMM_SAT_STATE_ENUM_UINT32;


enum USIMM_UNIVERSAL_PIN_STATUS_ENUM
{
    USIMM_UNIVERSAL_PIN_DISABLE     = 0,
    USIMM_UNIVERSAL_PIN_ENABLE      = 1,
    USIMM_UNIVERSAL_PIN_BUTT
};
typedef VOS_UINT32      USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32;


/*文件结构*/
enum USIMM_EF_TYPE_ENUM
{
    USIMM_EFSTRUCTURE_NONE          = 0,
    USIMM_EFSTRUCTURE_TRANSPARENT   = 1,
    USIMM_EFSTRUCTURE_FIXED         = 2,
    USIMM_EFSTRUCTURE_CYCLE         = 3,
    USIMM_EFSTRUCTURE_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_EF_TYPE_ENUM_UINT32;

enum USIMM_SC_ATTRIB_MODE_ENUM
{
    USIMM_SC_ATTRIB_NO          = 0,
    USIMM_SC_ATTRIB_COMPACT     = 1,
    USIMM_SC_ATTRIB_EXPANDED    = 2,
    USIMM_SC_ATTRIB_REFERENCE   = 3,
    USIMM_SC_ATTRIB_BUTT
};
typedef VOS_UINT32      USIMM_SC_ATTRIB_MODE_ENUM_UINT32;


enum USIMM_AC_LEVEL_ENUM
{
    USIMM_AC_LEVEL_ALW          = 0,
    USIMM_AC_LEVEL_PIN1         = 1,
    USIMM_AC_LEVEL_PIN2         = 2,
    USIMM_AC_LEVEL_UPIN         = 3,
    USIMM_AC_LEVEL_ADM          = 4,
    USIMM_AC_LEVEL_NEV          = 5,
    USIMM_AC_LEVEL_BUTT
};
typedef VOS_UINT32      USIMM_AC_LEVEL_ENUM_UINT32;

enum USIMM_POOLSTATUS_ENUM
{
    USIMM_POOL_NOINTIAL         =  0,
    USIMM_POOL_INITIALED        =  1,
    USIMM_POOL_FIRST_STEP       =  2,
    USIMM_POOL_AVAILABLE        =  3,
    USIMM_POOL_NEED_PASSWORD    =  4,
    USIMM_POOLSTATUS_BUTT
};
typedef VOS_UINT32      USIMM_POOLSTATUS_ENUM_UINT32;

enum USIMM_CARD_STATE_CHANGE_ENUM
{
    USIMM_CARD_STATE_NOCHANGE   = 0,
    USIMM_CARD_STATE_CHANGED    = 1,
    USIMM_CARD_STATE_CHANGE_BUTT
};
typedef VOS_UINT32      USIMM_CARD_STATE_CHANGE_ENUM_UINT32;

enum USIMM_FILE_TYPE_ENUM
{
    USIMM_EF_FILE               = 0,
    USIMM_DF_FILE               = 1,
    USIMM_FILE_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_FILE_TYPE_ENUM_UINT32;

enum USIMM_FILE_NEED_FCP_ENUM
{
    USIMM_NO_NEED_FCP           = 0,
    USIMM_NEED_FCP              = 1,
    USIMM_NEED_FCP_BUTT
};
typedef VOS_UINT32      USIMM_FILE_NEED_FCP_ENUM_UINT32;

enum USIMM_LOG_STATE_ENUM
{
    USIMM_NEED_LOG              = 0,
    USIMM_NO_NEED_LOG           = 1,
    USIMM_LOG_STATE_BUTT
};
typedef VOS_UINT32      USIMM_LOG_STATE_ENUM_UINT32;

enum USIMM_SUPPORT_SYSTEM_COMMAND_ENUM
{
    USIMM_NO_SUPSYSCMD           = 0,
    USIMM_SUPSYSCMD              = 1,
    USIMM_SUPSYSCMD_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SYSTEM_COMMAND_ENUM_UINT32;

enum USIMM_MODE_TYPE_ENUM
{
    USIMM_NORMAL_MODE           = 0,    /* 正常上电启动模式 */
    USIMM_RESET_MODE            = 1,    /* 复位重启模式 */
    USIMM_REFRESH_MODE          = 2,    /* refresh模式 */
    USIMM_PROTECT_RESET_MODE    = 3,    /* 保护性复位模式 */
    USIMM_MODE_TYPE_BUTT
};
typedef VOS_UINT8      USIMM_MODE_TYPE_ENUM_UINT8;


/* USIM卡电压等级，协议TS102221 11.1.1.4.6.1 */
enum USIMM_VOLTAGE_CLASS_ENUM
{
    USIMM_VOLTAGE_5V           = 0x10,   /* supply voltage class A */
    USIMM_VOLTAGE_3V           = 0x20,   /* supply voltage class B */
    USIMM_VOLTAGE_1_8V         = 0x40,   /* supply voltage class C */
    USIMM_VOLTAGE_CLASS_BUTT
};
typedef VOS_UINT32      USIMM_VOLTAGE_CLASS_ENUM_UINT32;

/* STATUS命令枚举 即下发数据单元的p1参数，参见协议102.221第11.1.2 */
enum USIMM_STATUS_P1_PARA_ENUM
{
    USIMM_STATUS_NO_INDICATION        = 0x00, /* No indication */
    USIMM_STATUS_CURAPP_INITIALIZED   = 0x01, /* Current application is initialized in the terminal */
    USIMM_STATUS_TERMINATION_CURAPP   = 0x02, /* the terminal will initiate the termination of the current application */
    USIMM_STATUS_P1_PARA_BUTT
};
typedef VOS_UINT8      USIMM_STATUS_P1_PARA_ENUM_UINT8;

/* STATUS命令枚举 即下发数据单元的p2参数，参见协议102.221第11.1.2 */
enum USIMM_STATUS_P2_PARA_ENUM
{
    USIMM_STATUS_FCP_RETURNED       = 0x00,  /* response paremeters and data identical to the response paremeters and data of the select command */
    USIMM_STATUS_DF_NAME_RETURNED   = 0x01,  /* the DF name TLV-object of the currently selected application is returned */
    USIMM_STATUS_NO_DATA_RETURNED   = 0x0C,  /* No data returned */
    USIMM_STATUS_P2_PARA_BUTT
};
typedef VOS_UINT8      USIMM_STATUS_P2_PARA_ENUM_UINT8;


/* USIM卡select命令P1参数含义，协议TS102221 11.1.1.2 */
enum USIMM_SELECT_P1_PARA_ENUM
{
    USIMM_SELECT_BY_FILE_ID         = 0x00,   /* select DF,EF or MF by file id */
    USIMM_SELECT_CHILD_DF           = 0X01,   /* select child DF of the current DF */
    USIMM_SELECT_PARENT_DF          = 0X03,   /* select parent DF of the current DF */
    USIMM_SELECT_BY_DF_NAME         = 0x04,   /* selection by DF name,this is selection by AID */
    USIMM_SELECT_BY_PATH_FROM_MF    = 0x08,   /* select by path from MF */
    USIMM_SELECT_BY_PATH_FROM_CURDF = 0x09,   /* select by path from current DF */
    USIMM_SELECT_P1_PARA_BUTT
};
typedef VOS_UINT8      USIMM_SELECT_P1_PARA_ENUM_UINT8;


/* USIM卡select命令P2参数含义，协议TS102221 11.1.1.2 */
enum USIMM_SELECT_P2_PARA_ENUM
{
    USIMM_SELECT_ACTIVATE_AID         = 0x00,   /* Application session control,激活应用，仅当P1参数为04时，这个值才有意义 */
    USIMM_SELECT_TERMINATION_AID      = 0x40,   /* Application session control,终止应用，仅当P1参数为04时，这个值才有意义*/
    USIMM_SELECT_RETURN_FCP_TEMPLATE  = 0x04,   /* 需要带回FCP */
    USIMM_SELECT_NO_DATA_RETURNED     = 0x0C,   /* 没有数据带回 */
    USIMM_SELECT_P2_PARA_BUTT
};
typedef VOS_UINT8      USIMM_SELECT_P2_PARA_ENUM_UINT8;

/* SIM卡的PHASE枚举 */
enum USIMM_SIM_PHASE_ENUM
{
    USIMM_SIM_PHASE_ONE        = 0x00,   /* PHASE1 的SIM卡 */
    USIMM_SIM_PHASE_TWO        = 0x02,   /* PHASE2 的SIM卡 */
    USIMM_SIM_PHASE_PLUS       = 0x03,   /* PHASE2+ 的SIM卡 */
    USIMM_SIM_PHASE_BUTT
};
typedef VOS_UINT32      USIMM_SIM_PHASE_ENUM_UINT32;

enum USIMM_PROFILE_DOWNLOAD_ENUM
{
    USIMM_PROFILE_DOWNLOAD_SUCCESS      = VOS_OK,
    USIMM_PROFILE_DOWNLOAD_FAIL,
    USIMM_PROFILE_DOWNLOAD_BUTT
};

typedef VOS_UINT8       USIMM_PROFILE_DOWNLOAD_ENUM_UINT8;

/* 初始化阶段ECC文件初始化状态枚举 */
enum USIMM_ECC_INIT_STATUS_ENUM
{
    USIMM_ECC_INIT_SUCCESS      = VOS_OK,
    USIMM_ECC_SELECT_FAIL,
    USIMM_ECC_READ_FAIL,
    USIMM_ECC_TYPE_ERR,
    USIMM_ECC_INIT_STATUS_BUTT
};

typedef VOS_UINT8       USIMM_ECC_INIT_STATUS_ENUM_UINT8;

/* 卡初始化步骤返回值 */
enum USIMM_INIT_RESULT_ENUM
{
    USIMM_INIT_OK       = VOS_OK,
    USIMM_INIT_FAIL     = VOS_ERR,
    USIMM_INIT_RESET,
    USIMM_INIT_NEEDPIN,
    USIMM_INIT_SUSPEND,
    USIMM_INIT_FAIL_CONTINUE,
    USIMM_INIT_FAIL_RESTART,
    USIMM_INIT_FATAL_EXIT,
    USIMM_INIT_BUTT
};

typedef VOS_UINT32 USIMM_INIT_RESULT_ENUM_32;

enum USIMM_UICC_APP_ENUM
{
    USIMM_UICC_USIM,
    USIMM_UICC_ISIM,
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    USIMM_UICC_CDMA,
#endif
    USIMM_UICC_BUTT
};

typedef VOS_UINT32 USIMM_UICC_APP_ENUM_32;

enum USIMM_SIM_FILE_TYPE_ENUM
{
    USIMM_SIM_FILE_TYPE_RFU = 0x00,
    USIMM_SIM_FILE_TYPE_MF  = 0x01,
    USIMM_SIM_FILE_TYPE_DF  = 0x02,
    USIMM_SIM_FILE_TYPE_EF  = 0x04,
    USIMM_SIM_FILE_TYPE_BUTT
};

typedef VOS_UINT8 USIMM_SIM_FILE_TYPE_ENUM_UINT8;

enum USIMM_VSIM_AUTH_ENUM
{
    USIMM_VSIM_AUTH_NULL        = 0,
    USIMM_VSIM_MILENAGE         = 1,
    USIMM_VSIM_COMPV1           = 2,
    USIMM_VSIM_COMPV2           = 3,
    USIMM_VSIM_COMPV3           = 4,
    USIMM_VSIM_AUTH_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AUTH_ENUM_UINT8;
typedef VOS_UINT32     USIMM_VSIM_AUTH_ENUM_UINT32;

enum USIMM_FILE_ATTR_ENUM
{
    USIMM_MANDATORY_FILE        = 0,    /*SIM USIM都需要的文件*/
    USIMM_USIM_MANDATORY_FILE   = 1,
    USIMM_SIM_MANDATORY_FILE    = 2,
    USIMM_OPTIONAL_FILE         = 3,
    USIMM_FILE_ATTR_BUTT
};
typedef VOS_UINT8      USIMM_FILE_ATTR_ENUM_UINT8;

enum USIMM_VSIM_AC_ENUM
{
    USIMM_VSIM_WRITE_AVALIBALE        = 0,    /*VSIM可以更新的文件*/
    USIMM_VSIM_WRITE_UNAVALIBALE      = 1,    /*VSIM不可以更新的文件*/
    USIMM_VSIM_AC_ENUM_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AC_ENUM_UINT8;

/*****************************************************************************
 枚举名    : USIMM_T1_IFS_SEND_STATUS_ENUM
 结构说明  : T=1 IFS 命令发送状态枚举
*****************************************************************************/
enum USIMM_T1_IFS_SEND_STATUS_ENUM
{
    USIMM_T1_IFS_SEND_SUCCESS = VOS_OK,          /* T=1协议下发送IFS命令成功 */
    USIMM_T1_IFS_SEND_FAILURE,                   /* T=1协议下发送IFS命令失败 */
    USIMM_T1_IFS_SEND_STATUS_BUTT
};

typedef VOS_UINT32      USIMM_T1_IFS_SEND_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : USIMM_MNTN_ERROR_LEVEL_ENUM
 结构说明  : USIMM ERROR LOG级别枚举
*****************************************************************************/
enum USIMM_MNTN_ERROR_LEVEL_ENUM
{
    USIMM_MNTN_ERROR_LEVEL_CRITICAL = 1,    /* 紧急 */
    USIMM_MNTN_ERROR_LEVEL_MAJOR,           /* 重要 */
    USIMM_MNTN_ERROR_LEVEL_MINOR,           /* 次要 */
    USIMM_MNTN_ERROR_LEVEL_WARNING,         /* 告警 */
    USIMM_MNTN_ERROR_LEVEL_INFO,            /* 信息 */
    USIMM_MNTN_ERROR_LEVEL_BUTT
};
typedef  VOS_UINT16  USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : USIMM_MNTN_STATE_ERROR_REASON_ENUM
 结构说明  : USIMM ERROR LOG 事件枚举
*****************************************************************************/
enum USIMM_MNTN_STATE_ERROR_ENUM
{
    USIMM_MNTN_STATE_OK             = 0,
    USIMM_MNTN_STATE_PRESET_SUCC,
    USIMM_MNTN_STATE_POLLING_FAIL,
    USIMM_MNTN_STATE_ERROR_BUTT
};
typedef  VOS_UINT8  USIMM_MNTN_STATE_ERROR_ENUM_UINT8;

/*****************************************************************************
 枚举名    : USIMM_MNTN_STATE_ERROR_REASON_ENUM
 结构说明  : USIMM ERROR LOG 事件枚举
*****************************************************************************/
enum USIMM_MNTN_INIT_ERROR_ENUM
{
    USIMM_MNTN_INIT_OK              = 0,
    USIMM_MNTN_INIT_FILEOK,
    USIMM_MNTN_INIT_FAIL,
    USIMM_MNTN_INIT_IMSIFAIL,
    USIMM_MNTN_INIT_SSTFAIL,
    USIMM_MNTN_INIT_FILEERROR,
    USIMM_MNTN_STATE_INIT_ERROR_BUTT
};
typedef  VOS_UINT8  USIMM_MNTN_INIT_ERROR_ENUM_UINT8;

/*****************************************************************************
 枚举名    : USIMM_MNTN_STATE_ERROR_REASON_ENUM
 结构说明  : USIMM ERROR LOG 事件枚举
*****************************************************************************/
enum USIMM_MNTN_MODULE_ENUM
{
    USIMM_MNTN_MODULE_DL = 0,
    USIMM_MNTN_MODULE_INIT,
    USIMM_MNTN_MODULE_STATE,
    USIMM_MNTN_MODULE_BUTT
};
typedef  VOS_UINT32  USIMM_MNTN_MODULE_ENUM_UINT32;


enum USIMM_CARD_VERSION_TYPE
{
    USIMM_CARD_NON_TYPE             = 0,
    USIMM_CARD_ICC_TYPE             = 1,
    USIMM_CARD_UICC_TYPE            = 2,
    USIMM_CARD_VERSION_TYPE_BUTT
};
typedef  VOS_UINT8  USIMM_CARD_VERSION_TYPE_UINT8;


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usDfID;
    VOS_UINT16                          usEFNum;
    VOS_UINT16                          *pusEFList;
}USIMM_FILE_CONTENT_ST;

typedef struct
{
    USIMM_FILE_CONTENT_ST               stFileCont;
    VOS_UINT32                          ulDfFcpLen;
}USIMM_SINGLE_FILEMAP_ST;

typedef struct
{
    USIMM_SINGLE_FILEMAP_ST             stDFFileMap;
    USIMM_SINGLE_FILEMAP_ST             stGDFFileMap;
}USIMM_CARD_FILEMAP_ST;

typedef struct
{
    USIMM_FILE_CONTENT_ST               stDFCont;
    VOS_UINT32                          ulGDFNum;
    USIMM_FILE_CONTENT_ST               *pstGDFCont;
}USIMM_DF_CONTENT_ST;

/*effcp信息记录结构*/
typedef struct
{
    VOS_UINT16                          usFileLen;              /*当前文件长度*/
    VOS_UINT8                           ucRecordNum;            /*当前记录文件的记录数*/
    VOS_UINT8                           ucRecordLen;            /*当前记录文件的记录长度*/
    VOS_UINT8                           ucSFI;                  /*当前文件的SFI*/
    VOS_UINT8                           ucArrNo;                /*EFARR的记录号*/
    VOS_UINT16                          usEFArrID;              /*记录安全条件的EFARR的SFI*/
    USIMM_EF_TYPE_ENUM_UINT32           enFileType;             /*当前文件类型*/
    USIMM_EFSTATUS_ENUM_UINT8           enFileStatus;           /*当前文件状态*/
    USIMM_EFRWFLAG_ENUM_UINT8           enFileReadUpdateFlag;   /*当前文件无效时，文件可读与可更新标志*/
    VOS_UINT8                           aucRsv[2];
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;               /*当前文件的安全标识方法*/
    USIMM_AC_LEVEL_ENUM_UINT32          enUpdateAC;             /*当前文件的更新权限*/
    USIMM_AC_LEVEL_ENUM_UINT32          enReadAC;               /*当前文件的读取权限*/
    USIMM_AC_LEVEL_ENUM_UINT32          enActiveAC;             /*当前文件的激活权限*/
    USIMM_AC_LEVEL_ENUM_UINT32          enDeaciveAC;            /*当前文件的去激活权限*/
}USIMM_EFFCP_ST;

/*dffcp信息记录结构*/
typedef struct
{
    VOS_UINT16                          usDFID;         /*当前选中DFID*/
    VOS_UINT8                           ucPIN1RefNum;   /*当前DF的PIN1索引*/
    VOS_UINT8                           ucPIN2RefNum;   /*当前DF的PIN2索引*/
    VOS_UINT8                           ucCharaByte;
    VOS_UINT8                           ucNameLen;      /*当前DF的名字长度*/
    VOS_UINT8                           aucName[16];    /*当前DF的名字内容*/
    VOS_UINT8                           ucSupCmd;       /*支持terminal capability */
    VOS_UINT8                           ucRsv;
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;       /*当前DF的安全标识方式*/
    USIMM_PIN_INFO_STRU                 stPINInfo;
}USIMM_DFFCP_ST;

/*sim dffcp 内容记录结构,成员含义见协议3gpp ts 11.11 的9.2.1*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usMemRes;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucReserve2[5];
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucFileChara;
    VOS_UINT8                           ucDFsNum;
    VOS_UINT8                           ucEFsNum;
    VOS_UINT8                           ucSecurityCodeNum;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucPIN1RemainTime;
    VOS_UINT8                           ucPUK1RemainTime;
    VOS_UINT8                           ucPIN2RemainTime;
    VOS_UINT8                           ucPUK2RemainTime;
}USIMM_SIMDF_FCP_ST;

/*sim effcp 内容记录结构,成员含义见协议3gpp ts 11.11 的9.2.1*/
/*lint -e959 -e958*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usFileLen;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucCyclicEFTag;
    VOS_UINT8                           ucAccessCnd[3];
    VOS_UINT8                           ucFileStatus;
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucEFStruct;
    VOS_UINT8                           ucRecordLen;
}USIMM_SIMEF_FCP_ST;
/*lint +e959 +e958*/

typedef struct
{
    VOS_UINT32                          ulAIDLen;       /*当前的AID长度*/
    VOS_UINT8                           aucAID[USIMM_AID_LEN_MAX];     /*当前AID内容*/
    VOS_UINT8                           ucPIN1RefNum;   /*当前DF的PIN1索引*/
    VOS_UINT8                           ucPIN2RefNum;   /*当前DF的PIN2索引*/
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    VOS_UINT8                           ucCharaByte;
    VOS_UINT8                           ucSupCmd;
#else
    VOS_UINT16                          usRsv;
#endif
    USIMM_PIN_INFO_STRU                 stPINInfo;      /*当前密码信息*/
    USIMM_PIN_VERIY_STATUS_ENUM_UINT32  enPin1Verified; /* PIN1验证状态         */
    USIMM_PIN_VERIY_STATUS_ENUM_UINT32  enPin2Verified; /* PIN2验证状态         */
    VOS_UINT8                           aucPin1[USIMM_PINNUMBER_LEN];/* PIN码操作成功后记录下当前PIN码 */
}USIMM_ADF_INFO_STRU;


/*****************************************************************************
 结构名    : USIMM_AID_INFO_STRU
 结构说明  : 用于记录USIM/ISIM/CSIM的AID内容和长度
 修改历史      :
  1.日    期   : 2013年12月19日
    作    者   : h59254
    修改内容   :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAIDLen;       /*当前的AID长度*/
    VOS_UINT8                           aucAID[USIMM_AID_LEN_MAX];     /*当前AID内容*/
}USIMM_AID_INFO_STRU;

typedef struct
{
    USIMM_PB_INIT_STATUS_ENUM_UINT16    enPBInitStatus;     /*当前电话本初始化状态，以决定是否可以进行时钟停止模式*/
    VOS_UINT16                          usPBDfID;           /*当前电话本的4F文件存在的路径*/
}USIMM_PB_INFO_STRU;

typedef struct
{
    USIMM_CARD_TYPE_ENUM_UINT32             enCardType;         /* 当前卡类型 */
    USIMM_CARD_SERVIC_ENUM_UINT32           enCardService;      /* 当前卡的状态 */
    USIMM_CARD_STATE_CHANGE_ENUM_UINT32     enStateChange;      /* 状态变更 */
}USIMM_CARD_APP_INFO_ST;

/*基本信息记录结构*/
typedef struct
{
    VOS_UINT8                               ucCLA;              /*当前CLA值*/
    VOS_UINT8                               ucCurChannelNum;    /*当前开启的通道数*/
    VOS_UINT16                              usSATLen;           /*当前的主动命令长度*/
    USIMM_SUPPORT_SFI_ENUM_UINT32           enSupportSFI;       /*是否支持SFI*/
    USIMM_SUPPORT_PATH_ENUM_UINT32          enSupportPath;      /*是否支持路径选择*/
    USIMM_SUPPORT_CHANNEL_ENUM_UINT32       enSupportChannel;   /*是否支持逻辑通道*/
    USIMM_PIN_TYPE_ENUM_UINT32              enCurPINType;       /*当前密码类型*/
    VOS_UINT32                              ulSimPhase;         /*当为SIM卡时，保存PHASE*/
    USIMM_FDNSTATUS_ENUM_UINT32             enFDNStatus;        /*当前FDN状态*/
    USIMM_BDNSTATUS_ENUM_UINT32             enBDNStatus;        /*当前BDN状态*/
    USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32  enUniversalPINStatus;/*当前全局PIN状态*/
    USIMM_SAT_STATE_ENUM_UINT32             enSATState;         /*当前主动命令状态*/
    USIMM_PB_INFO_STRU                      stPBInfo;           /*当前电话簿初时化信息*/
}USIMM_BASE_INFO_ST;

typedef struct
{
    VOS_UINT16                              usIsimEFID;
    VOS_UINT16                              usUsimEFID;
}USIMM_ISIM_USIM_CONVERSION_ST;

/*底软信息记录结构*/
typedef struct
{
    USIMM_CLKLEVEL_ENUM_UINT32              enCLKLevel;         /*当前CLK level优先级*/
    USIMM_CLKSTOP_ENUM_UINT32               enCLKStop;          /*当前CLK 是否允许停止*/
}USIMM_DRV_INFO_ST;

/*当前文件信息记录结构*/
typedef struct
{
    VOS_UINT16                              usCurDFID;      /*当前选中DFID*/
    VOS_UINT16                              usCurEFID;      /*当前选中EFID*/
    VOS_UINT16                              usCurDFFcpLen;  /*当前选中的DF的FCP长度*/
    VOS_UINT16                              usFilePathLen;
    VOS_UINT16                              ausFilePath[USIMM_MAX_PATH_LEN];  /*当前路径信息*/
    USIMM_DFFCP_ST                          stDFInfo;       /*当前DF信息*/
    USIMM_EFFCP_ST                          stEFInfo;       /*当前EF信息*/
}USIMM_CURFILEINFO_ST;

/*****************************************************************************
 结构名    : USIMM_POOL_ONERECORD_ST
 结构说明  : 文件池中文件信息记录结构

  1.日    期   : 2012年06月17日
    作    者   : h59254
    修改内容   : ATT定制项目增加APP类型
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usFId;          /* 文件ID */
    VOS_UINT16                              usLen;          /* 文件内容长度 */
    USIMM_APP_TYPE_ENUM_UINT32              enAppType;      /* APP类型 */
    USIMM_EF_TYPE_ENUM_UINT32               enFileType;     /* 文件类型 */
    VOS_UINT8                              *pucContent;     /* 文件内容指针 */
}USIMM_POOL_ONERECORD_ST;

/*****************************************************************************
 结构名    : USIMM_POOL_OPTION_FILE_CFG_ST
 结构说明  : USIMM模块可选文件初始化配置结构

  1.日    期   : 2012年12月23日
    作    者   : h59254
    修改内容   : 问题单修改新增加结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usOptionFileNum;
    VOS_UINT16                              aucOptionFilelist[USIMM_INIT_OFILE_MUX_NUM];
}USIMM_POOL_OPTION_FILE_CFG_ST;


typedef struct
{
    USIMM_POOL_ONERECORD_ST                 astpoolRecord[POOLMAXNUM];
    USIMM_POOLSTATUS_ENUM_UINT32            enPoolStatus;
    VOS_UINT8                               ucNowLen;
    VOS_UINT8                               aucReserved[3];
}USIMM_POOL_ST;


typedef VOS_UINT32 (*PUSIMMAPPPROC)(USIMM_CMDHEADER_REQ_STRU * pMsg);

typedef struct
{
    USIMM_CMDTYPE_REQ_ENUM_UINT32           enMsgType;        /* 消息ID */
    PUSIMMAPPPROC                           pProcFun;        /* 处理函数 */
}USIMMAPP_FUNCLIST_ST;

typedef struct
{
    USIMM_LOG_STATE_ENUM_UINT32             enLogState;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               *pucData;
}USIMM_LOG_DATA_STRU;

typedef struct
{
    VOS_UINT32                              ulCurFile;
    VOS_CHAR                                aucFileName[USIMM_LOG_FILE_MAX_NUM][USIMM_LOG_FILE_NAME_LEN];
}USIMM_LOG_CTRLFILE_STRU;

/*****************************************************************************
结构名    : USIMM_OPFILE_LIST_STRU
结构说明  : USIMM模块初始化列表结构

  1.日    期   : 2013年1月25日
    作    者   : h59254
    修改内容   : 初始生成
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFileId;
    VOS_UINT16                          usService;
}USIMM_OPFILE_LIST_STRU;

/*****************************************************************************
结构名    : USIMM_TERMINAL_POWER_SUPPLY_STRU
结构说明  : 终端电压供应结构，对应协议102.221上11.1.19.2.1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* terminal power supply 的tag:0x80 */
    VOS_UINT8                          ucLen;              /* 长度 */
    VOS_UINT8                          ucActSupVolCla;     /* 实际使用的供电电压等级 */
    VOS_UINT8                          ucMaxAvaPower;      /* 终端上最大可用电压供应 */
    VOS_UINT8                          ucActFre;           /* 实际使用的时钟频率 */
}USIMM_TERMINAL_POWER_SUPPLY_STRU;

/*****************************************************************************
结构名    : USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU
结构说明  : 终端电压供应结构，对应协议102.221上11.1.19.2.2
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* extended logical channel terminal support的tag:0x81 */
    VOS_UINT8                          ucLen;              /* 长度 */
}USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU;

/*****************************************************************************
结构名    : USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU
结构说明  : 终端电压供应结构，对应协议102.221上11.1.19.2.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* the additional interface support的tag:0x82 */
    VOS_UINT8                          ucLen;              /* 长度 */
    VOS_UINT8                          ucAddInterface;     /* 附加接口 */
}USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU;

/*****************************************************************************
结构名    : USIMM_CARD_INIT_INFO_LOG_STRU
结构说明  : 卡初始化阶段的信息记录
*****************************************************************************/
typedef struct
{
    USIMM_PROFILE_DOWNLOAD_ENUM_UINT8  enTPDownloadStatus;    /* terminal profile是否下发失败 */
    USIMM_ECC_INIT_STATUS_ENUM_UINT8   enEccInitStatus;       /* ECC文件初始化状态 */
    VOS_UINT8                          ucVoltageSwitchFlag;   /* 电压是否切换 */
    VOS_UINT8                          ucVoltageMismatchFlag; /* 电压不匹配标记 */
}USIMM_CARD_INIT_RECORD_STRU;

typedef struct
{
    VOS_UINT8                          ucInsertPoolFailFlag;  /* 文件插入缓冲池失败标记 */
    USIMM_CARD_INIT_RECORD_STRU        stUSIMMInfo;
}USIMM_CARD_INIT_INFO_LOG_STRU;

typedef struct
{
    USIMM_APP_TYPE_ENUM_UINT32          enFileApp;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag;
}USIMM_SELECT_PARA_STUR;

typedef struct
{
    VOS_UINT32                  ulLeValue;                          /* 接收数据长度 */
    VOS_UINT32                  ulLcValue;                          /* 发送数据长度 */
    VOS_UINT32                  ulRecDataLen;
    VOS_UINT8                   ucResult;
    VOS_UINT8                   ucACK;                              /*接收的ACK*/
    VOS_UINT8                   ucSW1;                              /*命令结束后的SW1*/
    VOS_UINT8                   ucSW2;                              /*命令结束后的SW2*/
    VOS_UINT8                   ucApduSW1;                          /*命令第一次发送的SW1*/
    VOS_UINT8                   ucApduSW2;                          /*命令第一次发送的SW2*/
    VOS_UINT8                   aucAPDU[USIMM_APDU_HEADLEN];        /*命令的APDU*/
    VOS_UINT8                   aucGetRepAPDU[USIMM_APDU_HEADLEN];  /*Get Response命令的APDU*/
    VOS_UINT8                   aucRecvBuf[USIMM_APDU_MAXLEN];      /* 接收数据内容*/
    VOS_UINT8                   aucSendBuf[USIMM_APDU_MAXLEN];      /* 发送数据内容*/
}USIMM_APDU_ST;

typedef struct
{
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    VOS_UINT32                      ulPathLen;
    VOS_UINT16                      *pusFilePath;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucRsv[3];
}USIMM_GET_COMM_FILE_STRU;

typedef struct
{
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    USIMM_EF_TYPE_ENUM_UINT32       enEFFileType;
    VOS_UINT16                      usFileID;
    VOS_UINT16                      usDataLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucRsv[3];
    VOS_UINT8                       *pucData;
}USIMM_SET_COMM_FILE_STRU;

#if (FEATURE_VSIM == FEATURE_ON)
typedef struct
{
    VOS_CHAR                                *pcVSIMName;
    VOS_UINT16                              usFileID;
    USIMM_FILE_ATTR_ENUM_UINT8              enFileAttr;
    USIMM_VSIM_AC_ENUM_UINT8                enFileAC;
}USIMM_VSIM_FILE_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulLen;
    VOS_UINT8                               aucData[USIMM_VSIM_SECUR_MAX_LEN * 2];
}USIMM_VSIM_BASE16_DATA_STRU;

typedef struct
{
    VOS_UINT8                               ucKILen;
    VOS_UINT8                               ucOpcLen;
    USIMM_VSIM_AUTH_ENUM_UINT8              enAuthType;
    VOS_UINT8                               ucRfu;
    VOS_UINT8                               aucKi[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucOpc[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucSimKeyHash[USIMM_VSIM_SIM_KEY_HASH_LEN];
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Ki;
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Opc;
}USIMM_VSIM_AUTH_INFO_STRU;
#endif

#if(FEATURE_ON == FEATURE_PTM)
typedef struct
{
    VOS_UINT8                               ucErrorInfo;
    VOS_UINT8                               ucInfo1;
    VOS_UINT16                              usInfo2;
    VOS_UINT32                              ulSlice;
}USIMM_MNTN_SINGLEINFO_STRU;

typedef struct
{
    VOS_UINT32                              ulIndex;
    USIMM_MNTN_SINGLEINFO_STRU              astDLModuleInfo[USIMM_MNTN_INFODATA_MAX];
}USIMM_MNTN_INFODATA_STRU;

/*****************************************************************************
 结构体名  : USIMM_MNTN_STATE_ERROR_EVENT_STRU
 结构说明  : USIMM ERROR LOG上报结构
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;
    USIMM_MNTN_INFODATA_STRU                        stMNTNDLInfo;
    USIMM_MNTN_INFODATA_STRU                        stMNTNInitInfo;
    USIMM_MNTN_INFODATA_STRU                        stMNTNStateInfo;
    SCI_RECORD_INFO_S                               stSCIRecordInfo;        /*SCI驱动异常信息*/
    USIMM_CARD_APP_INFO_ST                          stMNTNUSIMAppInfo;
    USIMM_CARD_APP_INFO_ST                          stMNTNCSIMAppInfo;
    VOS_UINT32                                      aulRsv[4];              /*包括扩展字段 */
}USIMM_MNTN_STATE_ERROR_EVENT_STRU;
#endif

/*****************************************************************************
 结构名    : USIMM_CHANNEL_INFO_STRU
 结构说明  : USIM模块CHANNEL INFO的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRspLen;                               /* GetResponse长度 */
    VOS_UINT8                           aucRspContent[USIMM_APDU_MAXLEN];       /* GetResponse的内容 */
}USIMM_CHANNEL_GET_RSP_STRU;

typedef struct
{
    USIMM_CARD_VERSION_TYPE_UINT8       enCardMode;
    VOS_UINT8                           ucHasCModule;
    VOS_UINT8                           ucHasWGModule;
    VOS_UINT8                           ucRfu;
} USIMM_CARD_VERSIONTYPE_STRU;


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
#if(FEATURE_ON == FEATURE_PTM)
extern USIMM_MNTN_STATE_ERROR_EVENT_STRU    g_stCardErrorLog;

extern NV_ID_ERR_LOG_CTRL_INFO_STRU         g_stErrLogCtrlInfo;
#endif

extern USIMM_BASE_INFO_ST                    gstUSIMMBaseInfo;

extern USIMM_CARD_APP_INFO_ST                gastUSIMMCardAppInfo[USIMM_UICC_BUTT];

extern VOS_UINT32                            gulUsimSupportIMS;

extern USIMM_ISIM_USIM_CONVERSION_ST         gastIsimUsimEFConTBL[5];

extern USIMM_ISIM_USIM_CONVERSION_ST         gastIsimToUsimEFTBL[5];

extern USIMM_DRV_INFO_ST                     gstUSIMMDrvInfo;

extern USIMM_CURFILEINFO_ST                  gstUSIMMCurFileInfo;

extern USIMM_ADF_INFO_STRU                   gstUSIMMADFInfo;

extern USIMM_AID_INFO_STRU                   g_astAidInfo[3];

extern USIMM_LOG_DATA_STRU                   g_stUSIMMLogData;

extern VOS_UINT32                           g_ulUSIMMExcLogLenBK;

extern USIMM_LOG_DATA_STRU                  g_stUSIMMExcLogData;

extern USIMM_POOL_ST                         gstUSIMMPOOL;

extern VOS_UINT32                            gulUSIMMOpenSpeed;

extern VOS_UINT16 gausInitFileOne[USIMM_INITFIRST_FILENUM];

extern VOS_UINT16 gausSimInitMFile[USIMM_INITSIM_MFILENUM];

extern VOS_UINT16 gausUsimInitMFile[USIMM_INITUSIM_MFILENUM];

extern USIMM_OPFILE_LIST_STRU gastSimInitOFile[USIMM_INITSIM_OFILENUM];

extern USIMM_OPFILE_LIST_STRU gastUsimInitOFile[USIMM_INITUSIM_OFILENUM];

extern VOS_UINT16 g_ausAttUsimInitFile[USIMM_USIM_ATT_INITFILE_NUM];

extern VOS_UINT16 g_ausAttSimInitFile[USIMM_SIM_ATT_INITFILE_NUM];

extern VOS_UINT16 gausSimDFTELFile[15];

extern VOS_UINT16 gausSimDFGSMFile[46];

extern VOS_UINT16 gausUsimDFGSMFile[39];

extern VOS_UINT16 gausUsimDFTELFile[17];

extern VOS_UINT16 gausUsimADFFile[88];

extern USIMM_CARD_FILEMAP_ST g_stUSIMMCardFileMap[10];

extern USIMM_FILE_CONTENT_ST g_stSimDFGSMContent[USIMM_SIMDFGSMGDF_MAX];

extern USIMM_FILE_CONTENT_ST g_stSimDFTELContent[USIMM_SIMDFTELGDF_MAX];

extern USIMM_DF_CONTENT_ST g_stSimDFContent[USIMM_SIMDFCONTENT_MAX];

extern USIMM_FILE_CONTENT_ST g_astUsimADFContent[USIMM_USIMADFGDF_MAX];

extern USIMM_FILE_CONTENT_ST g_astUsimDFTELContent[USIMM_USIMADFTELGDF_MAX];

extern USIMM_DF_CONTENT_ST g_stUsimDFContent[USIMM_USIMDFCONTENT_MAX];

extern USIMM_CARD_INIT_FUNC   g_aUsimInitCardProcFuncTbl[USIMM_INIT_USIM_CARD_NUM];

extern USIMM_CARD_INIT_FUNC   g_aSimInitCardProcFuncTbl[USIMM_INIT_SIM_CARD_NUM];

extern USIMM_CARD_INIT_TBL_ST g_aCardInitTbl[USIMM_CARD_INIT_TBL_SIZE];

extern USIMM_FEATURE_CFG_STRU   g_stUsimmFeatureCfg;

extern VOS_UINT32               g_ulATTSpecErrSWCnt;

extern USIMM_CHANNEL_INFO_STRU  g_astUSIMMChCtrl[USIMM_CHANNEL_NUM_MAX];

extern USIMM_CHANNEL_GET_RSP_STRU g_astUSIMMChGetRsp[USIMM_CHANNEL_NUM_MAX];

extern USIMM_CHANNEL_AIDFCPINFO_STRU       g_astUSIMMChAIDFCP[USIMM_CHANNEL_NUM_MAX];

extern USIMM_CARD_INIT_INFO_LOG_STRU       g_stUSIMMInitInfo;

extern USIMM_DL_T_MODE_ENUM_UINT32         g_enUSIMMTMode;
extern VOS_BOOL                            g_bSendIFSReqFlag;


#if (FEATURE_VSIM == FEATURE_ON)
extern USIMM_VSIM_AUTH_INFO_STRU        g_stUSIMMVSimAuthInfo;

extern USIMM_VSIM_FILE_INFO_STRU        g_astUSIMMVSimFileInfo[];

extern VOS_CHAR                         *g_pcUSIMMVSimXmlFilePath;

extern VOS_UINT8                        *g_pucUSIMMVsimData ;
#endif

extern USIMM_CARD_VERSIONTYPE_STRU  g_stUSIMMCardVersionType;

extern VOS_UINT32 g_ulCsimSessionId;

extern VOS_BOOL                         g_bCacheEFIccidData;
extern VOS_UINT8                        g_aucEFIccidData[USIMM_EFICCID_LEN];

extern USIMM_FILEID_PATHSTR_TABLE_STRU g_stUSIMMFilePathTable[USIMM_DEF_FILEID_BUTT];

/*****************************************************************************
  6 Function定义
*****************************************************************************/
#ifdef USIMM_DEBUG_PEINT
#define USIMM_NORMAL                0
#define USIMM_INFO                  1
#define USIMM_WARNING               2
#define USIMM_ERROR                 3

#define USIMM_NORMAL_LOG(string)    USIMM_PRINT(USIMM_NORMAL,string)
#define USIMM_INFO_LOG(string)      USIMM_PRINT(USIMM_INFO,string)
#define USIMM_WARNING_LOG(string)   USIMM_PRINT(USIMM_WARNING,string)
#define USIMM_ERROR_LOG(string)     USIMM_PRINT(USIMM_ERROR,string)
#else
#define USIMM_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_USIM), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define USIMM_NORMAL_LOG(string)    (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#define USIMM_INFO_LOG(string)      (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#define USIMM_WARNING_LOG(string)   (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_WARNING),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#define USIMM_ERROR_LOG(string)     (VOS_VOID)DIAG_LogReport(USIMM_GEN_LOG_MODULE(PS_LOG_LEVEL_ERROR),WUEPS_PID_USIM, __FILE__, __LINE__, "%s", string)
#endif


/*Common 函数*/
extern VOS_VOID USIMM_ChangePathToU16(VOS_UINT32 ulDataLen, VOS_UINT8 *pucData, VOS_UINT32 *pulLen, VOS_UINT16 *pusPath);

extern VOS_UINT32 USIMM_SelectFileHandle(USIMM_SELECT_PARA_STUR *pstSelectPara,USIMM_U16_LVDATA_STRU *pstFilePath);

extern VOS_UINT32 USIMM_SelectFile(USIMM_APP_TYPE_ENUM_UINT32 enFileApp,USIMM_FILE_NEED_FCP_ENUM_UINT32 enEfFcpFlag,VOS_UINT32 ulPathLen,VOS_UINT16 *pusFilePath);

extern VOS_UINT32 USIMM_GetFileAllPath(USIMM_SELECT_PARA_STUR       *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU      *pstFilePathIn,
                                        USIMM_U16_LVDATA_STRU      *pstFilePathOut);

extern VOS_UINT32 USIMM_ReadTFFile(VOS_UINT16 usLen, VOS_UINT8 *pucContent);

extern VOS_UINT32  USIMM_GetTFFile(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFileId, VOS_UINT16 usReadLen,VOS_UINT8 *pucData);

extern VOS_UINT32 USIMM_SelectUiccADF(VOS_VOID);

extern VOS_VOID USIMM_PRINT(VOS_UINT32 ulPrintLev,VOS_INT8*pucString);

extern VOS_UINT32 USIMM_SelectDFFile(
    VOS_UINT16                        usFileId,
    USIMM_SELECT_PARA_STUR           *pstSelectPara,
    USIMM_CURFILEINFO_ST             *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectEFByID(VOS_UINT16 usFileId,USIMM_SELECT_PARA_STUR *pstSelectPara,USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_GetCardFilePath(USIMM_APP_TYPE_ENUM_UINT32 enFileApp,VOS_UINT16 usFileId, VOS_UINT32 *pulPathLen, VOS_UINT16 *pusPath);

extern VOS_UINT32 USIMM_GetAttFilePath(VOS_UINT16 usFileId, VOS_UINT32 *pulPathLen, VOS_UINT16 *pusPath);

extern VOS_UINT32 USIMM_SelectFileWithPath(USIMM_SELECT_PARA_STUR *pstSelectPara, USIMM_U16_LVDATA_STRU *pstFilePath, USIMM_CURFILEINFO_ST *pstCurFilePath,VOS_UINT16 *pstFilePathResult);

extern VOS_UINT32 USIMM_UpdateLFFile(VOS_UINT8 ucRecordNum, VOS_UINT8 *pucData, VOS_UINT8 ucLen);

extern VOS_UINT32 USIMM_UpdateTFFile(VOS_UINT16 usLen, VOS_UINT8 *pucData);

extern VOS_UINT32 USIMM_UpdateCLFFile(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen);

extern VOS_UINT32 USIMM_ReadLFFile(USIMM_EFFCP_ST *pstCurEFFcp, VOS_UINT8 ucRecordNum, VOS_UINT8 *pucContent);

extern VOS_UINT32 USIMM_STATUSProc(VOS_VOID);

extern VOS_UINT32 USIMM_AdjudgeCardState(VOS_VOID);

extern VOS_UINT32 USIMM_GetPINRemainTime(VOS_UINT8 ucPINNo);

extern VOS_UINT32 USIMM_GetPUKRemainTime(VOS_UINT8 ucPINNo);

extern VOS_UINT32 USIMM_VerifyNCK(VOS_UINT8 ucLen,VOS_UINT8 *pucPassword);

extern VOS_UINT32 USIMM_VerifyPCK(VOS_UINT8 ucLen,VOS_UINT8 *pucPassword);

extern VOS_UINT32 USIMM_ChangePIN(USIMM_PIN_TYPE_ENUM_UINT32 enPINType, VOS_UINT8 *pucOldPIN, VOS_UINT8 *pucNewPIN);

extern VOS_UINT32 USIMM_UnblockPIN(USIMM_PIN_TYPE_ENUM_UINT32 enPINType, VOS_UINT8 *pucPUK, VOS_UINT8 *pucNewPIN);

extern VOS_UINT32 USIMM_PINVerify(USIMM_PIN_TYPE_ENUM_UINT32 enPINType,VOS_UINT8 ucPINCmd,VOS_UINT8 *pucPIN);

extern VOS_UINT32 USIMM_InitUsimFDNBDNStatus(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimFDNBDNStatus(VOS_VOID);

extern VOS_VOID USIMM_FdnCapabilityRequest(USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus);

extern VOS_VOID USIMM_BdnCapabilityRequest(USIMM_BDNSTATUS_ENUM_UINT32 *pulBdnStatus);

extern VOS_UINT32 USIMM_SimFDNBDNProcess(VOS_VOID);

extern VOS_UINT32 USIMM_FDNEnable(VOS_VOID);

extern VOS_UINT32 USIMM_FDNDisable(VOS_VOID);

extern VOS_VOID USIMM_FDNEstChgInd(VOS_VOID);

extern VOS_UINT32 USIMM_FindTagInBERTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_FindTagInSMPTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_FindTagInCTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulBufLen);

extern VOS_UINT32 USIMM_DecodeATR(VOS_VOID);

extern VOS_VOID   USIMM_DecodeATRSecondStep(VOS_VOID);

extern VOS_UINT32 USIMM_DecodeEFFcp(USIMM_CARD_TYPE_ENUM_UINT32 enCurCardType, USIMM_APDU_ST *pstApduData, USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeDFFcp(USIMM_CARD_TYPE_ENUM_UINT32 enCurCardType,USIMM_APDU_ST *pstApduData,USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeFileFcp(USIMM_CARD_TYPE_ENUM_UINT32 enCardType,USIMM_U16_LVDATA_STRU *pstFilePath,USIMM_APDU_ST *pstApduData,USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeEFDIR(VOS_VOID);

extern VOS_VOID USIMM_ReportEvent(VOS_UINT16 usEventId);

extern VOS_VOID USIMM_RefreshFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_RefrehFilePath(VOS_UINT8 *pucDstPath, VOS_UINT16 *pusDstLen, VOS_UINT8 *pucSrcPath, VOS_UINT16 usSrcLen);

extern VOS_UINT32 USIMM_CardFilePathCMP(VOS_UINT32 ulPath1Len, VOS_UINT16 *pusPath1,VOS_UINT32 ulPath2Len, VOS_UINT16 *pusPath2);

extern VOS_BOOL USIMM_IsCLEnable(VOS_VOID);

extern TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8 USIMM_GetRATMode(VOS_VOID);

extern VOS_VOID USIMM_FileAccessFix( VOS_VOID );

extern VOS_VOID  USIMM_SetAccFileAccess( VOS_VOID );



extern VOS_UINT32 USIMM_IS_EF_FILE(VOS_UINT16 usFileId);

/*POOL操作函数*/
extern VOS_VOID USIMM_RefreshFileRead(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_VOID USIMM_PoolDataInit(VOS_VOID);

extern VOS_VOID USIMM_FeatureGlobalInit(VOS_VOID);

extern VOS_UINT32 USIMM_VsimPoolSearchFile(VOS_UINT16 usFileId, VOS_UINT32 *pulData);

extern VOS_UINT32 USIMM_PoolFindFile(VOS_UINT16 usFileId, VOS_UINT32 *pulData, USIMM_APP_TYPE_ENUM_UINT32 enAppType);

extern VOS_UINT32 USIMM_PoolInsertOneFile(VOS_UINT16 usFileId, VOS_UINT16 usLen, VOS_UINT8* pData,
                                                 USIMM_APP_TYPE_ENUM_UINT32 enAppType,
                                                 USIMM_EF_TYPE_ENUM_UINT32 enFileType);

extern VOS_UINT32 USIMM_InsertFileToPool(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFileID);

extern VOS_VOID   USIMM_RefreshFileAppCheck(USIMM_APP_TYPE_ENUM_UINT32 *penAppType, VOS_UINT16 *pusFilePath, VOS_UINT32 ulPathLen);

extern VOS_UINT32 USIMM_PoolDelOneFile(VOS_UINT16 usFileId, USIMM_APP_TYPE_ENUM_UINT32 enAppType);

extern VOS_UINT32 USIMM_PoolReadOneFile(VOS_UINT16 usFileId, VOS_UINT16 usLen, VOS_UINT8* pData,
                                                USIMM_APP_TYPE_ENUM_UINT32 enAppType);

extern VOS_VOID USIMM_PoolDelAll(VOS_VOID);

extern VOS_UINT32  USIMM_PoolUpdateOneFile(VOS_UINT16 usFileId, USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData);

extern VOS_VOID USIMM_ClearCurDFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurEFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurFileInfo(VOS_VOID);

extern VOS_VOID USIMM_SaveDFPinInfo(VOS_VOID);

extern VOS_VOID USIMM_InitGlobalVarOnReset(VOS_VOID);

extern VOS_VOID USIMM_InitGlobalVarOnPower(VOS_VOID);

extern VOS_VOID USIMM_OpenSpeedFileInit(VOS_VOID);

extern VOS_VOID USIMM_InitOpenSpeed(VOS_VOID);

extern VOS_UINT32 USIMM_InsertNoNeedPinFileToPool(VOS_VOID);

extern VOS_UINT32 USIMM_InsertLPFileToPool(VOS_VOID);

extern VOS_VOID USIMM_InitNeedPinSteps(USIMM_MODE_TYPE_ENUM_UINT8 ucMode);

extern VOS_VOID USIMM_AttFileInit(VOS_VOID);

extern VOS_VOID USIMM_InsertAttFileToPool(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFile);

extern VOS_UINT32 USIMM_InitProfileStep(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardOptionalFile(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_InitThirdSteps(VOS_VOID);

extern VOS_VOID USIMM_GetTerminalProfile(USIMM_STK_CFG_STRU *pstProfileContent);

extern VOS_UINT32 USIMM_UsimProfileDownload(VOS_VOID);

extern VOS_VOID USIMM_SimProfileDownload(USIMM_MODE_TYPE_ENUM_UINT8 ucMode);

extern VOS_VOID USIMM_AttUpdataSupportTable(VOS_VOID);

extern VOS_VOID USIMM_AttEfTerminalSupportTableValueGet(VOS_UINT8 *pucValue);

extern VOS_UINT32 USIMM_InitUsimEccFile(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimEccFile(VOS_VOID);

extern VOS_UINT32 USIMM_CheckCLStep(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardPINInfo(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardTypeByATR(VOS_VOID);

extern VOS_UINT32 USIMM_InitCard(USIMM_MsgBlock *pMsg);

extern VOS_UINT32 USIMM_SelectFileNoPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen);

extern VOS_UINT32 USIMM_SelectFileByPath(USIMM_SELECT_PARA_STUR *pstSelectPara, USIMM_U16_LVDATA_STRU *pstFilePath, USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectFileByRelativePath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo);

extern VOS_VOID USIMM_UpdateFilePath(USIMM_SELECT_PARA_STUR *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU  *pstFilePath,
                                            USIMM_CURFILEINFO_ST   *pstUSIMMCurFileInfo);

extern VOS_VOID USIMM_UpdateFileByRelativePath(USIMM_SELECT_PARA_STUR *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU  *pstFilePath,
                                            USIMM_CURFILEINFO_ST   *pstUSIMMCurFileInfo);

extern VOS_UINT32 USIMM_InitUsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_Select2GApp(VOS_VOID);

extern VOS_UINT32 USIMM_Select3GApp(VOS_VOID);

extern VOS_VOID USIMM_Reselect3GApp(VOS_VOID);

extern VOS_UINT32 USIMM_RefreshAidVerify(VOS_UINT32 ulAidLen, VOS_UINT8 *pucAid);

extern VOS_UINT32 USIMM_InitUsimCardFileMap(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimCardFileMap(VOS_VOID);

extern VOS_VOID USIMM_SciDataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData);

extern VOS_VOID USIMM_RefreshNoFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_VOID USIMM_RefreshInd(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_SimRefreshFilePbAppCheck(VOS_UINT16 *pusFilePath, VOS_UINT32 ulPathLen);

extern VOS_UINT32 USIMM_UsimRefreshFilePbAppCheck(VOS_UINT16 *pusFilePath, VOS_UINT32 ulPathLen);

extern VOS_VOID USIMM_RefreshIsimFileIndHandle(USIMM_STKREFRESH_IND_STRU *pstRefreshMsg);

/*log保存接口*/
extern VOS_VOID USIMM_InitLogFile(VOS_VOID);

extern VOS_VOID USIMM_SaveLogFile(VOS_VOID);

extern VOS_VOID USIMM_LogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen);

extern VOS_VOID USIMM_ExcLogDataClear(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen);

extern VOS_VOID USIMM_ExcLogDataBK(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataRE(VOS_VOID);

extern VOS_VOID USIMM_SaveExcLogFile(VOS_VOID);

extern VOS_VOID USIMM_InitExcLogFile(VOS_VOID);

/*Base Func*/
extern VOS_UINT32  USIMM_PinStatusCheck(USIMM_PIN_CMD_TYPE_ENUM_UINT32 enCmdType,USIMM_PIN_TYPE_ENUM_UINT32 enPINType,VOS_UINT32 *pulResult);

extern VOS_UINT32 USIMM_SAT_TerminalResopnse(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_SAT_Envelope(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_PINHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_PinPreProcHandle( USIMM_PINHANDLE_REQ_STRU  *pNewstMsg, USIMM_PIN_REQ_STRU  *pPreMsg);

extern VOS_UINT32 USIMM_PinHandleCardStatusCheck(VOS_VOID);

extern VOS_UINT32 USIMM_StatusHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_UpdateFile(USIMM_EF_TYPE_ENUM_UINT32  enEFFileType, VOS_UINT8  ucRecordNum, VOS_UINT16  usDataLen,  VOS_UINT8  *pucData);

extern VOS_UINT32 USIMM_SetSPBFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_SetFileHandle(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetMaxRecordNum(USIMM_MsgBlock *pMsg, USIMM_QUERYFILE_REQ_STRU *pstNewMsg);

extern VOS_VOID USIMM_SAT_Fetch(VOS_UINT16 usLen);

extern VOS_UINT32 USIMM_GetRealFile(USIMM_GETFILE_REQ_STRU* pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetFileHandle(USIMM_GETFILE_REQ_STRU* pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_IsdbAccessHandle(USIMM_MsgBlock *pMsg);

extern VOS_VOID USIMM_ErrorLogProc(USIMM_CMDHEADER_REQ_STRU * pMsg);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID USIMM_MsgProc(USIMM_CMDHEADER_REQ_STRU * pMsg);
#endif

extern VOS_UINT32 USIMM_ProtectFirstStep(VOS_UINT32  ulOldCardType);

extern VOS_UINT32 USIMM_UsimVoltageSwitch(VOS_UINT8 ucCharaByte, VOS_UINT8 *pucVoltageMismatchFlag);

extern VOS_VOID USIMM_UsimTerminalCapability(VOS_VOID);

extern VOS_UINT32 USIMM_AutoVerifyPIN(USIMM_PIN_ENABLE_STATUS_ENUM_UINT32 enPinEnable,    USIMM_PIN_VERIY_STATUS_ENUM_UINT32 *penPinVerified, VOS_UINT8 ucPinRefNum, VOS_UINT8 *paucPin);

extern VOS_VOID USIMM_QueryPINType(VOS_UINT8 *pucPINType);

extern VOS_UINT32 USIMM_HandlePINType(VOS_UINT8 ucCmdType, VOS_UINT32 *pulPINType);

extern VOS_UINT16 USIMM_IsimEFIDToUsimEFID(VOS_UINT16 usFileID);

extern VOS_UINT16 USIMM_UsimEFIDToIsimEFID(VOS_UINT16 usFileID);

extern VOS_UINT8 USIMM_GetMncLen(VOS_UINT8 *pucAdContent, VOS_UINT32 ulFileSize);

extern VOS_VOID USIMM_GetAsciiMCCAndMNC(VOS_UINT8 *pucAsciiImsi, VOS_UINT8 *pucAsciiMCC, VOS_UINT8 *pucAsciiMNC);

extern VOS_VOID USIMM_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum, VOS_UINT8 ucBcdNumLen);

extern VOS_UINT32 USIMM_ImsiBcd2Ascii(VOS_UINT8 *pucAsciiStr);

extern VOS_UINT32 USIMM_InitIsimHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_GetReadFilePara(VOS_UINT8 ucRecordNum, USIMM_EFFCP_ST *pstEFInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_UINT32 USIMM_ReadFile(USIMM_EFFCP_ST               *pstCurEFFcp,
                                 VOS_UINT8                   ucRecordNum,
                                 VOS_UINT16                  usDataLen,
                                 VOS_UINT8                   *pucData);

extern VOS_UINT32 USIMM_IsSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsUSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsISIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsUIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsCSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_GetFileFromCard(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_UINT32 USIMM_CheckSetFilePara(USIMM_EFFCP_ST *pstCurEFFcp, VOS_UINT8 ucRecordNum, VOS_UINT16 usDataLen);

/*vSIM API*/
extern VOS_VOID USIMM_InitVsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_SetVsimFile(USIMM_SETFILE_REQ_STRU *pstMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetVsimFile(USIMM_GETFILE_REQ_STRU  *pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg);

extern VOS_VOID USIMM_VsimConfidentialDataVerifyErrHandle(VOS_VOID);

extern VOS_UINT32 USIMM_VsimConfidentialDataVerify(VOS_VOID);

extern VOS_UINT32 USIMM_VsimBase16Decode(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen);

extern VOS_VOID USIMM_VsimBase16Encode(VOS_UINT8 *pucSrc, VOS_UINT8 *pucDst, VOS_UINT32 ulLen);

extern VOS_UINT32 USIMM_AuthenVirtulSim(USIMM_AUTH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_AuthenVirtulUsim(USIMM_AUTH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_DeactiveVsim(USIMM_MsgBlock *pMsg);

extern VOS_UINT32 USIMM_InitVsimCard(USIMM_MsgBlock *pMsg);

extern VOS_VOID USIMM_ClearVsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_VsimGetRealKiOpc(VOS_UINT8 *pucKi, VOS_UINT8 *pucOpc);

extern VOS_UINT32 USIMM_CheckVsimFileInPool(VOS_VOID);

extern VOS_UINT32 USIMM_AddVsimFileToPool(VOS_CHAR *pucFileStr, VOS_UINT32 ulStrLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen);

extern VOS_UINT32 USIMM_AddVsimAuthPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen);

extern VOS_UINT32 USIMM_AddVsimVerifyHashPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen);

extern VOS_UINT32 USIMM_DecodeVsimEf(OAM_XML_NODE_STRU *pstXmlNode);

extern VOS_VOID USIMM_VsimDecodeCardType(VOS_CHAR *pucStr,VOS_UINT32 ulStrLen,USIMM_CARD_TYPE_ENUM_UINT32 *pulCardType);

extern VOS_VOID USIMM_VsimDecodeAuthType(VOS_CHAR *pucStr, VOS_UINT32 ulStrLen,USIMM_VSIM_AUTH_ENUM_UINT32*pulAuthType);

extern VOS_UINT32 USIMM_DecodeVsimRoot(OAM_XML_NODE_STRU *pstXmlNode,USIMM_CARD_TYPE_ENUM_UINT32 *pulCardType,USIMM_VSIM_AUTH_ENUM_UINT8 *pucAuthType);

extern VOS_UINT32 USIMM_DecodeVsimFile(VOS_UINT8 *pucData);

extern VOS_UINT8* USIMM_ReadVsimFile(VOS_UINT32 ulReadPID);

extern VOS_UINT32 USIMM_InitCardHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_VsimHUKDecode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen);

extern VOS_BOOL USIMM_CheckSupportAP(VOS_VOID);

extern VOS_UINT32 USIMM_DeactiveRealCard(USIMM_MsgBlock *pMsg);

extern VOS_VOID USIMM_CardStatusRegCbFuncProc(VOS_VOID);

extern VOS_UINT32 USIMM_CardStatusHandle(USIMM_CMDHEADER_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_OpenChannel(VOS_UINT8 *pucChannelID, VOS_UINT32 *pulSessionId);

extern VOS_UINT32 USIMM_CloseChannel(VOS_UINT8 ucChannelID);

extern VOS_UINT32 USIMM_OpenChannelForCSIM(VOS_VOID);

extern VOS_UINT32 USIMM_CheckAIDFcp(VOS_UINT32                   ulChannelId,
                                             USIMM_APDU_ST               *pstUsimmApdu,
                                             USIMM_SENDTPDU_CNFINFO_STRU *pstDataCnf);

extern VOS_UINT8 USIMM_SearchCHCtrl(VOS_UINT32 ulSessionId);

extern VOS_VOID USIMM_AuthMsgTransferFillDataProc( USIMM_AUTHENTICATION_REQ_STRU *pstNewMsg, USIMM_AUTH_REQ_STRU *pstPrvMsg);

extern VOS_UINT32 USIMM_AuthMsgTransferProc( USIMM_AUTHENTICATION_REQ_STRU *pstNewMsg, USIMM_AUTH_REQ_STRU *pstPrvMsg);

extern VOS_UINT32 USIMM_AuthenticationHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_ChangeToOldApp(VOS_UINT32                   ulSenderPID,
                                       USIMM_FILEPATH_INFO_STRU    *pstFilePath,
                                       USIMM_CARDAPP_ENUM_UINT32    enNewAPP,
                                       VOS_UINT16                   usDFID,
                                       USIMM_APP_TYPE_ENUM_UINT32  *pstOldApp);

extern VOS_UINT32 USIMM_ReadFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_UpdateFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_FDNHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_QueryFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_SearchFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_SendTPDUDataHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_CheckChangeCardByICCID(VOS_VOID);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID USIMM_AddErrorInfo(
    USIMM_MNTN_INFODATA_STRU           *pstInfoData,
    VOS_UINT8                           ucErrorInfo,
    VOS_UINT8                           ucInfo1,
    VOS_UINT16                          usInfo2);

extern VOS_VOID USIMM_RecordCardErrorLog(
    USIMM_MNTN_MODULE_ENUM_UINT32       enMoudleType,
    VOS_UINT8                           ucErrorInfo,
    VOS_UINT8                           ucInfo1,
    VOS_UINT16                          usInfo2,
    USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16  enAlmLevel);
#endif

/*usimmcuim.c*/
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
extern USIMM_CARD_VERSION_TYPE_UINT8   g_enCardVersionType;

extern USIMM_ADF_INFO_STRU             g_stCSIMADFInfo;

extern VOS_UINT8                       g_aucCUIMCstInfo[12];   /*定义存储CST文件的空间*/

extern VOS_UINT8                       g_ucCSIMESTInfo;

extern VOS_UINT8                       g_ucStoreEsMeidResult;

extern VOS_VOID UICC_InitCsimGlobal(VOS_VOID);

extern VOS_VOID UICC_InitUimGlobal(VOS_VOID);

extern VOS_VOID UICC_InitUICCGlobal(VOS_VOID);

extern VOS_VOID UICC_InitICCGlobal(VOS_VOID);

extern VOS_VOID UICC_SaveDFPinInfo(USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitDecodeEFDIR(VOS_VOID);

extern VOS_UINT32 UICC_InitCommResetStep(VOS_VOID);

extern VOS_VOID UICC_GetTerminalProfile(USIMM_STK_CFG_STRU *pstProfileContent);

extern VOS_UINT32 UICC_TerminalProfileDownload(VOS_VOID);

extern VOS_UINT32 UICC_InitCommCSIMStep(VOS_VOID);

extern VOS_UINT32 UICC_InitCommUIMStep(VOS_VOID);

extern VOS_UINT32 UICC_InitCommStep(VOS_VOID);

extern VOS_UINT32 UICC_SelectCSIMADF(VOS_VOID);

extern VOS_UINT32 UICC_InitCUIMTFileContent(VOS_UINT16 usFileID, USIMM_U8_LVDATA_STRU *pstFileData);

extern VOS_VOID UICC_InitCUIMTFile(VOS_UINT16 usFileID);

extern VOS_VOID UICC_InitCUIMEccFile(VOS_VOID);

extern VOS_VOID UICC_InitCUIMCstFile(VOS_VOID);

extern VOS_VOID UICC_InitCSIMEstFile(VOS_VOID);

extern VOS_UINT32 UICC_InitCUIMEsnMeid(VOS_VOID);

extern VOS_UINT32 UICC_GetPUKRemainTime(VOS_UINT8 ucPINNo, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_GetPINRemainTime(VOS_UINT8 ucPINNo, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitPINRemainTime(USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitCardAppPINInfo(USIMM_CARD_VERSION_TYPE_UINT8 enCardVersionType, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_VOID UICC_AdjudgeAppState(USIMM_CARD_APP_INFO_ST *pstAppState, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitCSIMNeedPINStep(VOS_VOID);

extern VOS_UINT32 UICC_InitCSIM(VOS_VOID);

extern VOS_VOID UICC_UIMFdnRequest(USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus);

extern VOS_VOID UICC_UimFDNProcedure(VOS_VOID);

extern VOS_VOID UICC_CsimFDNCheck(VOS_VOID);

extern VOS_UINT32 UICC_InitUIMNeedPINStep(VOS_VOID);

extern VOS_UINT32 UICC_InitUIM(VOS_VOID);

extern VOS_UINT32 UICC_InitCardHandle(USIMM_MsgBlock *pMsg);

extern VOS_UINT32 USIMM_SelectCdmaFile(USIMM_FILE_NEED_FCP_ENUM_UINT32 enEfFcpFlag, VOS_UINT32 ulPathLen, VOS_UINT16 *pusFilePath);

extern VOS_UINT32 USIMM_SetCdmaFileHandle(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetCdmaFileFromCard(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_UINT32 USIMM_GetCdmaFileHandle(USIMM_MsgBlock *pstMsg, USIMM_CMDHEADER_REQ_STRU *pstReqMsg);

extern VOS_UINT32 USIMM_BSChallengeHandle(USIMM_CMDHEADER_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_ManageSsdHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_GenerateKeyVpmHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_CdmaAuthHandle(USIMM_AUTH_REQ_STRU *pMsg);

extern VOS_UINT32  USIMM_SearchHandle(USIMM_SEARCH_REQ_STRU *pstOldMsg, USIMM_SEARCHFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_PBInitStatusIndHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

#endif /*(FEATURE_UE_MODE_CDMA == FEATURE_ON)*/

/*外部接口*/
extern VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

#endif /* end of UsimmBase.h*/

