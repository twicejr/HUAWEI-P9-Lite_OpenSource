

#ifndef __MNCLIENT_H__
#define __MNCLIENT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"
#include  "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_MAX_CLIENT_NUM               (AT_CLIENT_ID_BUTT)

/*广播Client Id，供MODEM侧使用 */
#define MN_CLIENT_ID_BROADCAST          (0xFFFF)

/* 广播ClientId说明，最高的2个bit位表示ModemId。
   Modem0对应的广播Client为0011111111111111(0x3FFF)，
   Modem1对应的广播Client为0111111111111111(0x7FFF)
   Modem1对应的广播Client为1011111111111111(0xBFFF) */

/* Modem 0的广播Client Id */
#define AT_BROADCAST_CLIENT_ID_MODEM_0  (0x3FFF)

/* Modem 1的广播Client Id */
#define AT_BROADCAST_CLIENT_ID_MODEM_1  (0x7FFF)

/* Modem 2的广播Client Id */
#define AT_BROADCAST_CLIENT_ID_MODEM_2  (0xBFFF)


#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define AT_MAX_APP_CLIENT_ID            (AT_CLIENT_ID_APP26)
#else
#define AT_MAX_APP_CLIENT_ID            (AT_CLIENT_ID_APP1)
#endif

#define AT_MIN_APP_CLIENT_ID            (AT_CLIENT_ID_APP)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : AT_CLIENT_ID_ENUM_UINT8
 枚举说明  : Client Id

  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 定义AT的Clientid
*****************************************************************************/
enum AT_CLIENT_ID_ENUM
{
    AT_CLIENT_ID_PCUI                 = 0,
    AT_CLIENT_ID_CTRL,
    AT_CLIENT_ID_PCUI2,
    AT_CLIENT_ID_MODEM,
    AT_CLIENT_ID_NDIS,
    AT_CLIENT_ID_UART,
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CLIENT_ID_HSUART,
#endif
    AT_CLIENT_ID_SOCK,
    AT_CLIENT_ID_APPSOCK,
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_CLIENT_ID_HSIC1,
    AT_CLIENT_ID_HSIC2,
    AT_CLIENT_ID_HSIC3,
    AT_CLIENT_ID_HSIC4,
    AT_CLIENT_ID_HSIC_MODEM,
    AT_CLIENT_ID_MUX1,
    AT_CLIENT_ID_MUX2,
    AT_CLIENT_ID_MUX3,
    AT_CLIENT_ID_MUX4,
    AT_CLIENT_ID_MUX5,
    AT_CLIENT_ID_MUX6,
    AT_CLIENT_ID_MUX7,
    AT_CLIENT_ID_MUX8,
#endif
    AT_CLIENT_ID_APP,
    AT_CLIENT_ID_APP1,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    AT_CLIENT_ID_APP2,
    AT_CLIENT_ID_APP3,
    AT_CLIENT_ID_APP4,
    AT_CLIENT_ID_APP5,
    AT_CLIENT_ID_APP6,
    AT_CLIENT_ID_APP7,
    AT_CLIENT_ID_APP8,
    AT_CLIENT_ID_APP9,
    AT_CLIENT_ID_APP10,
    AT_CLIENT_ID_APP11,
    AT_CLIENT_ID_APP12,
    AT_CLIENT_ID_APP13,
    AT_CLIENT_ID_APP14,
    AT_CLIENT_ID_APP15,
    AT_CLIENT_ID_APP16,
    AT_CLIENT_ID_APP17,
    AT_CLIENT_ID_APP18,
    AT_CLIENT_ID_APP19,
    AT_CLIENT_ID_APP20,
    AT_CLIENT_ID_APP21,
    AT_CLIENT_ID_APP22,
    AT_CLIENT_ID_APP23,
    AT_CLIENT_ID_APP24,
    AT_CLIENT_ID_APP25,
    AT_CLIENT_ID_APP26,
#endif

    AT_CLIENT_ID_BUTT
};
typedef VOS_UINT16 AT_CLIENT_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MN_OAM_CLIENT_ID_ENUM_UINT16
 枚举说明  : OAM的client

  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 定义外部client id值
*****************************************************************************/
enum MN_OAM_CLIENT_ID_ENUM
{
    OAM_CLIENT_ID_OM                 = AT_CLIENT_ID_BUTT,
    OAM_CLIENT_ID_SPY,
    OAM_CLIENT_ID_DIAG,
    OAM_CLIENT_ID_STK,
    OAM_CLIENT_ID_PIH,
    OAM_CLIENT_ID_PB,
    OAM_CLIENT_ID_CBT,
    OMA_CLIENT_ID_BUTT
};
typedef VOS_UINT16 MN_OAM_CLIENT_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MN_INTERNAL_CLIENT_ID_ENUM_UINT16
 枚举说明  : INTERNAL的client

  1.日    期   : 2014年1月11日
    作    者   : y00245242
    修改内容   : 定义协议栈内部client ID
  2.日    期   : 2014年4月3日
    作    者   : S00261364
    修改内容   : 增加spm内部client ID
*****************************************************************************/
enum MN_INTERNAL_CLIENT_ID_ENUM
{
    INTERNAL_CLIENT_ID_SMMA             = OMA_CLIENT_ID_BUTT,
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, begin */
    INTERNAL_CLIENT_ID_SPM,
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-4, end */
    INTERNAL_CLIENT_ID_BUTT
};
typedef VOS_UINT16 MN_INTERNAL_CLIENT_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : AT_CLIENT_TAB_INDEX_UINT8
 枚举说明  : 每个client在gastAtClientTab中index值

  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 定义AT每个Client对应的index值
*****************************************************************************/
enum AT_CLIENT_TAB_INDEX_ENUM
{
    AT_CLIENT_TAB_PCUI_INDEX              = 0,
    AT_CLIENT_TAB_CTRL_INDEX,
    AT_CLIENT_TAB_PCUI2_INDEX,
    AT_CLIENT_TAB_MODEM_INDEX,
    AT_CLIENT_TAB_NDIS_INDEX,
    AT_CLIENT_TAB_UART_INDEX,
#if (FEATURE_ON == FEATURE_AT_HSUART)
    AT_CLIENT_TAB_HSUART_INDEX,
#endif
    AT_CLIENT_TAB_SOCK_INDEX,
    AT_CLIENT_TAB_APPSOCK_INDEX,
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_CLIENT_TAB_HSIC1_INDEX,
    AT_CLIENT_TAB_HSIC2_INDEX,
    AT_CLIENT_TAB_HSIC3_INDEX,
    AT_CLIENT_TAB_HSIC4_INDEX,
    AT_CLIENT_TAB_HSIC_MODEM_INDEX,
    AT_CLIENT_TAB_MUX1_INDEX,
    AT_CLIENT_TAB_MUX2_INDEX,
    AT_CLIENT_TAB_MUX3_INDEX,
    AT_CLIENT_TAB_MUX4_INDEX,
    AT_CLIENT_TAB_MUX5_INDEX,
    AT_CLIENT_TAB_MUX6_INDEX,
    AT_CLIENT_TAB_MUX7_INDEX,
    AT_CLIENT_TAB_MUX8_INDEX,
#endif
    AT_CLIENT_TAB_APP_INDEX,
    AT_CLIENT_TAB_APP1_INDEX,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    AT_CLIENT_TAB_APP2_INDEX,
    AT_CLIENT_TAB_APP3_INDEX,
    AT_CLIENT_TAB_APP4_INDEX,
    AT_CLIENT_TAB_APP5_INDEX,
    AT_CLIENT_TAB_APP6_INDEX,
    AT_CLIENT_TAB_APP7_INDEX,
    AT_CLIENT_TAB_APP8_INDEX,
    AT_CLIENT_TAB_APP9_INDEX,
    AT_CLIENT_TAB_APP10_INDEX,
    AT_CLIENT_TAB_APP11_INDEX,
    AT_CLIENT_TAB_APP12_INDEX,
    AT_CLIENT_TAB_APP13_INDEX,
    AT_CLIENT_TAB_APP14_INDEX,
    AT_CLIENT_TAB_APP15_INDEX,
    AT_CLIENT_TAB_APP16_INDEX,
    AT_CLIENT_TAB_APP17_INDEX,
    AT_CLIENT_TAB_APP18_INDEX,
    AT_CLIENT_TAB_APP19_INDEX,
    AT_CLIENT_TAB_APP20_INDEX,
    AT_CLIENT_TAB_APP21_INDEX,
    AT_CLIENT_TAB_APP22_INDEX,
    AT_CLIENT_TAB_APP23_INDEX,
    AT_CLIENT_TAB_APP24_INDEX,
    AT_CLIENT_TAB_APP25_INDEX,
    AT_CLIENT_TAB_APP26_INDEX,
#endif

    AT_CLIENT_BUTT
};
typedef VOS_UINT8 AT_CLIENT_TAB_INDEX_UINT8;


/*****************************************************************************
 枚举名    : MN_CLIENT_ID_TYPE_UINT16
 枚举说明  : CLIENT ID类型

  1.日    期   : 2011年10月15日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CLIENT ID类型
  2.日    期   : 2014年1月11日
    作    者   : y00245242
    修改内容   : 增加CLIENT ID类型
*****************************************************************************/
enum MN_CLIENT_ID_TYPE
{
    MN_CLIENT_ID_TYPE_AT,
    MN_CLIENT_ID_TYPE_OAM,
    MN_CLIENT_ID_TYPE_INTERNAL,
    MN_CLIENT_ID_TYPE_BUTT
};
typedef VOS_UINT16 MN_CLIENT_ID_TYPE_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 AT_GetModemIdFromClient(
    VOS_UINT16                          usClientId,
    MODEM_ID_ENUM_UINT16               *pModemId
);

extern MN_CLIENT_ID_T AT_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
);

extern MN_CLIENT_ID_T MN_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
);


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

#endif /* end of MnClient.h */
