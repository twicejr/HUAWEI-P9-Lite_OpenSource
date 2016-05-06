

#ifndef __ATAGENT_H__
#define __ATAGENT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"

#include "AtMnInterface.h"
#include "TafAppMma.h"
#include "mdrv.h"

#include "AtPhyInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define AT_MAX_VERSION_LEN              (128)                 /* 版本信息最大长度 */


#define AT_MAX_PDM_VER_LEN              (16)                                    /* PDM版本号的最大长度 */

#define TAF_DLOAD_INFO_LEN              (1024)

#define TAF_AUTH_ID_LEN                 (50)

#define AT_DLOAD_TASK_DELAY_TIME        (500)

#define TAF_MAX_VER_INFO_LEN            (6)

#define TAF_MAX_PROPLAT_LEN             (63)                                    /*最大平台软件版本长度*/

#define TAF_AUTHORITY_LEN               (50)                                    /* AUTHORITYVER命令结果参数长度 */

#define AT_AGENT_DRV_VERSION_TIME_LEN   (32)                                    /* 底软接口DRV_GET_VERSION_TIME返回时间字符串最大长度 */


/* Added by L60609 for AT Project，2011-10-09,  Begin*/
#define TAF_MAX_FLAFH_INFO_LEN          (255)

#define TAF_MAX_GPIO_INFO_LEN           (32)
/* Added by L60609 for AT Project，2011-10-09,  End*/

/*硬件版本号最大长度*/
#define DRV_AGENT_MAX_MODEL_ID_LEN      (31)
#define DRV_AGENT_MAX_REVISION_ID_LEN   (31)

/* MS支持的接收分集类型定义 */
#define DRV_AGENT_MS_SUPPORT_RX_DIV_2100           (0x0001)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_1900           (0x0002)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_1800           (0x0004)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_AWS_1700       (0x0008)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_850            (0x0010)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_800            (0x0020)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_2600           (0x0040)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_900            (0x0080)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_IX_1700        (0x0100)

#define DRV_AGENT_DSP_RF_SWITCH_ON      (1)

#define DRV_AGENT_SIMLOCK_MAX_ERROR_TIMES  (3)  /* Simlock解锁最大失败次数 */

/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
#define  AT_PID_MEM_INFO_LEN                        (150) /* VOS内存查询时支持的最大PID个数 */

#define  AT_KB_TO_BYTES_NUM                         (1024) /* KB向字节转换需乘1024 */
/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */



#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/* 增强SHELL口密码保护相关定义 */
#define AT_SHELL_PWD_LEN                (8)
#endif

/* 设定一个门限值100（考虑到PAD 的NAND为256MB，典型block size为128kB，则共有2048块，
   坏块率一般要低于5%认为是合格的FLASH，故2048*5%=102.4，取100为坏块输出上限）。
   如果坏块总数大于100个，则只输出前100个坏块索引；否则输出所有坏块索引。
   但返回的<totalNum>仍按照实际总块数输出。
 */
#define DRV_AGENT_NAND_BADBLOCK_MAX_NUM (100)

#define DRV_AGENT_CHIP_TEMP_ERR         (65535)

#define DRV_AGENT_HUK_LEN                       (16)        /* HUK为128Bits的码流, 长度为16Bytes */
#define DRV_AGENT_PUBKEY_LEN                    (520)       /* 鉴权公钥码流, 长度为520Bytes */
#define DRV_AGENT_PUBKEY_SIGNATURE_LEN          (32)        /* 鉴权公钥SSK签名长度 */
#define DRV_AGENT_RSA_CIPHERTEXT_LEN            (128)       /* RSA密文长度, 统一为128Bytes */
#define DRV_AGENT_SUPPORT_CATEGORY_NUM          (3)         /* 支持的锁网锁卡CATEGORY类别数，目前只支持三种:network/network subset/SP */
#define DRV_AGENT_PH_LOCK_CODE_GROUP_NUM        (20)        /* 锁网锁卡号段组数 */
#define DRV_AGENT_PH_LOCK_CODE_LEN              (4)         /* 锁网锁卡号段长度 */
#define DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN     (548)       /* 锁网锁卡改制命令参数结构体长度 */
#define DRV_AGENT_PH_PHYNUM_LEN                 (16)        /* 物理号长度 */
#define DRV_AGENT_PH_PHYNUM_IMEI_LEN            (15)        /* IMEI号长度 */
#define DRV_AGENT_PH_PHYNUM_IMEI_NV_LEN         (16)        /* IMEI号NV项长度 */
#define DRV_AGENT_PH_PHYNUM_SN_LEN              (16)        /* SN长度 */
#define DRV_AGENT_PH_PHYNUM_SN_NV_LEN           (DRV_AGENT_PH_PHYNUM_SN_LEN+4)  /* SN的NV项长度 */
#define DRV_AGENT_PORT_PASSWORD_LEN             (16)        /* 网络通信端口锁密码长度 */

#define DRV_AGENT_DH_PUBLICKEY_LEN              (128)       /* DH算法使用的服务器公钥或Modem侧公钥长度 */
#define DRV_AGENT_DH_PRIVATEKEY_LEN             (48)        /* DH算法使用的Modem侧私钥长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : DRV_AGENT_TSELRF_SET_ERROR_ENUM
 结构说明  : ^TSELRF 命令设置操作结果错误码列表
             0: DRV_AGENT_TSELRF_SET_ERROR_NO_ERROR 设置操作成功；
             1: DRV_AGENT_TSELRF_SET_ERROR_LOADDSP  设置操作失败；
*****************************************************************************/
enum DRV_AGENT_TSELRF_SET_ERROR_ENUM
{
    DRV_AGENT_TSELRF_SET_NO_ERROR      = 0,
    DRV_AGENT_TSELRF_SET_LOADDSP_FAIL,

    DRV_AGENT_TSELRF_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_TSELRF_SET_ERROR_ENUM_UINT32;


/*****************************************************************************
 枚举名    : DRV_AGENT_HKADC_GET_ERROR_ENUM
 结构说明  : 获取HKADC电压操作结果错误码列表
             0: DRV_AGENT_HKADC_GET_NO_ERROR操作成功；
             1: DRV_AGENT_HKADC_GET_FAIL         操作失败；
*****************************************************************************/
enum DRV_AGENT_HKADC_GET_ERROR_ENUM
{
    DRV_AGENT_HKADC_GET_NO_ERROR      = 0,
    DRV_AGENT_HKADC_GET_FAIL,

    DRV_AGENT_HKADC_GET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_HKADC_GET_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_USIMWRITESTUB_SET_ERROR_ENUM
 结构说明  : USIMWRITESTUB 命令设置操作结果错误码列表
             0: 设置操作成功；
             1: 设置操作失败；
*****************************************************************************/
enum DRV_AGENT_ERROR_ENUM
{
    DRV_AGENT_NO_ERROR      = 0,
    DRV_AGENT_ERROR,
    DRV_AGENT_PARAM_ERROR,
    DRV_AGENT_CME_ERROR,
    DRV_AGENT_CME_RX_DIV_OTHER_ERR,
    DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED,
    DRV_AGENT_CME_RX_DIV_BAND_ERR,

    DRV_AGENT_BUTT
};
typedef VOS_UINT32 DRV_AGENT_ERROR_ENUM_UINT32;


/*****************************************************************************
 枚举名    : DRV_AGENT_MSID_QRY_ERROR_ENUM
 结构说明  : 调用底软接口查询MS ID错误枚举

  1.日    期   : 2011年10月22日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
enum DRV_AGENT_MSID_QRY_ERROR_ENUM
{
    DRV_AGENT_MSID_QRY_NO_ERROR                  = 0,
    DRV_AGENT_MSID_QRY_READ_PRODUCT_ID_ERROR     = 1,
    DRV_AGENT_MSID_QRY_READ_SOFT_VER_ERROR       = 2,
    DRV_AGENT_MSID_QRY_BUTT
};
typedef VOS_UINT32  DRV_AGENT_MSID_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_APPDMVER_QRY_ERROR_ENUM
 结构说明  : APPDMVER命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_APPDMVER_QRY_ERROR_ENUM
{
    DRV_AGENT_APPDMVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_APPDMVER_QRY_ERROR         = 1,

    DRV_AGENT_APPDMVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_APPDMVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM
 结构说明  : DLOADINFO命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM
{
    DRV_AGENT_DLOADINFO_QRY_NO_ERROR      = 0,
    DRV_AGENT_DLOADINFO_QRY_ERROR         = 1,

    DRV_AGENT_DLOADINFO_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM
 结构说明  : AUTHORITYVER命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM
{
    DRV_AGENT_AUTHORITYVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_AUTHORITYVER_QRY_ERROR         = 1,

    DRV_AGENT_AUTHORITYVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM
 结构说明  : AUTHORITYID命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM
{
    DRV_AGENT_AUTHORITYID_QRY_NO_ERROR      = 0,
    DRV_AGENT_AUTHORITYID_QRY_ERROR         = 1,

    DRV_AGENT_AUTHORITYID_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_GODLOAD_SET_ERROR_ENUM
 结构说明  : GODLOAD_命令设置操作结果错误码列表
             0: 设置操作成功；
             1: 设置操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_GODLOAD_SET_ERROR_ENUM
{
    DRV_AGENT_GODLOAD_SET_NO_ERROR      = 0,
    DRV_AGENT_GODLOAD_SET_ERROR         = 1,

    DRV_AGENT_GODLOAD_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_GODLOAD_SET_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_SDLOAD_SET_ERROR_ENUM
 结构说明  : SDLOAD_命令设置操作结果错误码列表
             0: 设置操作成功；
             1: 设置操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_SDLOAD_SET_ERROR_ENUM
{
    DRV_AGENT_SDLOAD_SET_NO_ERROR      = 0,
    DRV_AGENT_SDLOAD_SET_ERROR         = 1,

    DRV_AGENT_SDLOAD_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_SDLOAD_SET_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM
 结构说明  : HWNATQRY_命令设置操作结果错误码列表
             0: 设置操作成功；
             1: 设置操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM
{
    DRV_AGENT_HWNATQRY_QRY_NO_ERROR      = 0,
    DRV_AGENT_HWNATQRY_QRY_ERROR         = 1,

    DRV_AGENT_HWNATQRY_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM_UINT32;

/* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
/*****************************************************************************
 枚举名    : DRV_AGENT_CPULOAD_QRY_ERROR_ENUM
 结构说明  : CPULOAD命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年11月12日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_CPULOAD_QRY_ERROR_ENUM
{
    DRV_AGENT_CPULOAD_QRY_NO_ERROR      = 0,
    DRV_AGENT_CPULOAD_QRY_ERROR         = 1,

    DRV_AGENT_CPULOAD_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_CPULOAD_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM
 结构说明  : MFREELOCKSIZE命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年11月12日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM
{
    DRV_AGENT_MFREELOCKSIZE_QRY_NO_ERROR      = 0,
    DRV_AGENT_MFREELOCKSIZE_QRY_ERROR         = 1,

    DRV_AGENT_MFREELOCKSIZE_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM_UINT32;

/* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */

/*****************************************************************************
 枚举名    : DRV_AGENT_AUTHVER_QRY_ERROR_ENUM
 结构说明  : AUTHVER_命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_AUTHVER_QRY_ERROR_ENUM
{
    DRV_AGENT_AUTHVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_AUTHVER_QRY_ERROR         = 1,

    DRV_AGENT_AUTHVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_AUTHVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM
 结构说明  : FLASHINFO_命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM
{
    DRV_AGENT_FLASHINFO_QRY_NO_ERROR      = 0,
    DRV_AGENT_FLASHINFO_QRY_ERROR         = 1,

    DRV_AGENT_FLASHINFO_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_PFVER_QRY_ERROR_ENUM
 结构说明  : PFVER_命令查询操作结果错误码列表
            0: 查询操作成功；
            1: 获取版本能时间失败
            2: 获取版本失败
1.日    期   : 2011年10月4日
  作    者   : f62575
  修改内容   : 新生成函数
*****************************************************************************/
enum DRV_AGENT_PFVER_QRY_ERROR_ENUM
{
    DRV_AGENT_PFVER_QRY_NO_ERROR                 = 0,
    DRV_AGENT_PFVER_QRY_ERROR_GET_VERSION_TIME   = 1,
    DRV_AGENT_PFVER_QRY_ERROR_GET_VERSION        = 2,
    DRV_AGENT_PFVER_QRY_ERROR_ALLOC_MEM          = 3,

    DRV_AGENT_PFVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_PFVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_DLOADVER_QRY_ERROR_ENUM
 结构说明  : DLOADVER 命令查询操作结果错误码列表
             0: 查询操作成功；
             1: 查询操作失败；
*****************************************************************************/
enum DRV_AGENT_DLOADVER_QRY_ERROR_ENUM
{
    DRV_AGENT_DLOADVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_DLOADVER_QRY_ERROR         = 1,

    DRV_AGENT_DLOADVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_DLOADVER_QRY_ERROR_ENUM_UINT32;


/*****************************************************************************
 枚举名    : DRV_AGENT_PERSONALIZATION_ERROR_ENUM
 结构说明  : 锁网锁卡错误码列表

  1.日    期   : 2012年04月07日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增枚举

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_ERR_ENUM
{
    DRV_AGENT_PERSONALIZATION_NO_ERROR         = 0,             /* 操作成功 */
    DRV_AGENT_PERSONALIZATION_IDENTIFY_FAIL,                    /* 产线鉴权失败 */
    DRV_AGENT_PERSONALIZATION_SIGNATURE_FAIL,                   /* 签名校验失败 */
    DRV_AGENT_PERSONALIZATION_DK_INCORRECT,                     /* 端口密码错误 */
    DRV_AGENT_PERSONALIZATION_PH_PHYNUM_LEN_ERROR,              /* 物理号长度错误 */
    DRV_AGENT_PERSONALIZATION_PH_PHYNUM_VALUE_ERROR,            /* 物理号码错误 */
    DRV_AGENT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR,             /* 物理号类型错误 */
    DRV_AGENT_PERSONALIZATION_RSA_ENCRYPT_FAIL,                 /* RSA加密失败 */
    DRV_AGENT_PERSONALIZATION_RSA_DECRYPT_FAIL,                 /* RSA解密失败 */
    DRV_AGENT_PERSONALIZATION_GET_RAND_NUMBER_FAIL,             /* 获取随机数失败(crypto_rand) */
    DRV_AGENT_PERSONALIZATION_WRITE_HUK_FAIL,                   /* HUK写入错误 */
    DRV_AGENT_PERSONALIZATION_FLASH_ERROR,                      /* Flash错误 */
    DRV_AGENT_PERSONALIZATION_OTHER_ERROR,                      /* 其它错误 */

    DRV_AGENT_PERSONALIZATION_ERR_BUTT
};
typedef VOS_UINT32 DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32;

/*****************************************************************************
枚举名    : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM
枚举说明  : 锁网锁卡的category类型

  1.日    期   : 2012年04月07日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增枚举

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM
{
    DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK                 = 0x00,          /* category:锁网 */
    DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET          = 0x01,          /* category:锁子网 */
    DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER        = 0x02,          /* category:锁SP */
    DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE               = 0x03,          /* category:锁团体 */
    DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM                = 0x04,          /* category:锁(U)SIM卡 */

    DRV_AGENT_PERSONALIZATION_CATEGORY_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8;

/*****************************************************************************
枚举名    : DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM
枚举说明  : 指定的锁网锁卡类型是否激活

  1.日    期   : 2012年04月07日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增枚举

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM
{
    DRV_AGENT_PERSONALIZATION_INDICATOR_INACTIVE               = 0x00,          /* 未激活 */
    DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE                 = 0x01,          /* 已激活 */

    DRV_AGENT_PERSONALIZATION_INDICATOR_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM_UINT8;

/*****************************************************************************
枚举名    : DRV_AGENT_PERSONALIZATION_STATUS_ENUM
枚举说明  : 指定的锁网锁卡类型的状态

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_STATUS_ENUM
{
    DRV_AGENT_PERSONALIZATION_STATUS_READY      = 0x00,                         /* 已经解锁 */
    DRV_AGENT_PERSONALIZATION_STATUS_PIN        = 0x01,                         /* 未解锁状态，需输入解锁码 */
    DRV_AGENT_PERSONALIZATION_STATUS_PUK        = 0x02,                         /* Block状态，需输入UnBlock码 */

    DRV_AGENT_PERSONALIZATION_STATUS_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PERSONALIZATION_STATUS_ENUM_UINT8;

/*****************************************************************************
枚举名    : DRV_AGENT_PH_PHYNUM_TYPE_ENUM
枚举说明  : 物理号类型枚举

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增枚举

*****************************************************************************/
enum DRV_AGENT_PH_PHYNUM_TYPE_ENUM
{
    DRV_AGENT_PH_PHYNUM_IMEI            = 0x00,          /* IMEI */
    DRV_AGENT_PH_PHYNUM_SN              = 0x01,          /* SN */

    DRV_AGENT_PH_PHYNUM_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PH_PHYNUM_TYPE_ENUM_UINT8;

/*****************************************************************************
枚举名    : DRV_AGENT_PORT_STATUS_ENUM
枚举说明  : 通信端口状态类型枚举

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增枚举

*****************************************************************************/
enum DRV_AGENT_PORT_STATUS_ENUM
{
    DRV_AGENT_PORT_STATUS_OFF              = 0,         /* 端口关闭 */
    DRV_AGENT_PORT_STATUS_ON               = 1,         /* 端口打开 */

    DRV_AGENT_PORT_STATUS_BUTT
};
typedef VOS_UINT32 DRV_AGENT_PORT_STATUS_ENUM_UINT32;

/*****************************************************************************
枚举名    : DRV_AGENT_USIM_OPERATE_ENUM_UINT32
枚举说明  : USIM操作类型枚举

  1.日    期   : 2012年06月18日
    作    者   : f00179208
    修改内容   : 问题单:DTS2012060804905, 新增AT命令AT^APSIMST
*****************************************************************************/
enum DRV_AGENT_USIM_OPERATE_ENUM
{
    DRV_AGENT_USIM_OPERATE_DEACT                = 0,         /* 去激活USIM */
    DRV_AGENT_USIM_OPERATE_ACT                  = 1,         /* 激活USIM */

    DRV_AGENT_USIM_OPERATE_BUTT
};
typedef VOS_UINT32 DRV_AGENT_USIM_OPERATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : DRV_AGENT_MSG_TYPE_ENUM
 结构说明  : AT与DRV AGENT消息接口枚举
  1.日    期   : 2012年1月16日
    作    者   : f62575
    修改内容   : SMALL IMAGE特性合入: 新增下述四条消息
                                DRV_AGENT_TSELRF_SET_REQ
                                DRV_AGENT_HKADC_GET_REQ
                                DRV_AGENT_TSELRF_SET_CNF
                                DRV_AGENT_HKADC_GET_CNF
  2.日    期   : 2012年02月06日
    作    者   : 傅映君/f62575
    修改内容   : B050特性合入: 新增下述两条消息
                   DRV_AGENT_SECUBOOT_SET_REQ
                   DRV_AGENT_SECUBOOT_SET_CNF
  3.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : 删除在DSDA c核项目中调整的与WAS相关的消息ID
*****************************************************************************/
enum DRV_AGENT_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/      /* 备注 */
    /* AT发给DRV AGENT的消息 */
    DRV_AGENT_MSID_QRY_REQ               = 0x0000,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_GCF_IND                    = 0x0002,
    DRV_AGENT_GAS_MNTN_CMD               = 0x0006,
    DRV_AGENT_GPIOPL_SET_REQ             = 0x000E,
    DRV_AGENT_GPIOPL_QRY_REQ             = 0x0010,
    DRV_AGENT_DATALOCK_SET_REQ           = 0x0012,
    DRV_AGENT_TBATVOLT_QRY_REQ           = 0x0014,
    DRV_AGENT_VERTIME_QRY_REQ            = 0x0016,
    DRV_AGENT_YJCX_SET_REQ               = 0x0020,
    DRV_AGENT_YJCX_QRY_REQ               = 0x0022,
    DRV_AGENT_APPDMVER_QRY_REQ           = 0x0024,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_DLOADINFO_QRY_REQ          = 0x0028,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_FLASHINFO_QRY_REQ          = 0x002A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_AUTHVER_QRY_REQ            = 0x002C,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_AUTHORITYVER_QRY_REQ       = 0x0030,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_AUTHORITYID_QRY_REQ        = 0x0032,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_GODLOAD_SET_REQ            = 0x0034,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_HWNATQRY_QRY_REQ           = 0x0036,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
    DRV_AGENT_CPULOAD_QRY_REQ            = 0x0038,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_MFREELOCKSIZE_QRY_REQ      = 0x003A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */

    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
    DRV_AGENT_MEMINFO_QRY_REQ            = 0x003B,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */

    DRV_AGENT_HARDWARE_QRY               = 0x003E, /*查询硬件版本号*/
    DRV_AGENT_FULL_HARDWARE_QRY          = 0x0040, /*查询完整的硬件版本号*/
    DRV_AGENT_TMODE_SET_REQ              = 0x0046,
    DRV_AGENT_VERSION_QRY_REQ            = 0x0048,
    DRV_AGENT_SECUBOOT_QRY_REQ           = 0x004A,
    DRV_AGENT_SECUBOOTFEATURE_QRY_REQ    = 0x004C,
    DRV_AGENT_PFVER_QRY_REQ              = 0x004E,
    DRV_AGENT_FCHAN_SET_REQ              = 0x0052,
    DRV_AGENT_SDLOAD_SET_REQ             = 0x0056,
    DRV_AGENT_SFEATURE_QRY_REQ           = 0x0058,
    DRV_AGENT_PRODTYPE_QRY_REQ           = 0x0060,
    DRV_AGENT_SDREBOOT_REQ               = 0x0062,
    DRV_AGENT_RXDIV_SET_REQ              = 0x0064,
    DRV_AGENT_DLOADVER_QRY_REQ           = 0x0066,

    DRV_AGENT_RXDIV_QRY_REQ              = 0x006A,
    DRV_AGENT_SIMLOCK_SET_REQ            = 0x006C,
    DRV_AGENT_IMSICHG_QRY_REQ            = 0x0072,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVRESTORE_SET_REQ          = 0x0074,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_INFORBU_SET_REQ            = 0x0076,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVRSTSTTS_QRY_REQ          = 0x0078,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_CPNN_TEST_REQ              = 0x007A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVBACKUP_SET_REQ           = 0x007C,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_CPNN_QRY_REQ               = 0x007E,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVRESTORE_MANU_DEFAULT_REQ = 0x0080,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_ADC_SET_REQ                = 0x0082,                              /* _H2ASN_MsgChoice SPY_TEMP_THRESHOLD_PARA_STRU */
    DRV_AGENT_TSELRF_SET_REQ             = 0x0084,                              /* _H2ASN_MsgChoice DRV_AGENT_TSELRF_SET_REQ_STRU */
    DRV_AGENT_HKADC_GET_REQ              = 0x0086,                              /* _H2ASN_MsgChoice  */
    DRV_AGENT_TBAT_QRY_REQ               = 0x0088,
    DRV_AGENT_SECUBOOT_SET_REQ           = 0x008A,

    DRV_AGENT_SIMLOCK_NV_SET_REQ         = 0x008c,

    DRV_AGENT_SPWORD_SET_REQ             = 0x008e,

    DRV_AGENT_PSTANDBY_SET_REQ           = 0x0090,

    DRV_AGENT_NVBACKUPSTAT_QRY_REQ       = 0x0092,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NANDBBC_QRY_REQ            = 0x0094,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NANDVER_QRY_REQ            = 0x0096,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_CHIPTEMP_QRY_REQ           = 0x0098,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */


    DRV_AGENT_HUK_SET_REQ                = 0x009A,                              /* _H2ASN_MsgChoice DRV_AGENT_HUK_SET_REQ_STRU */
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ      = 0x009C,                              /* _H2ASN_MsgChoice DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU */
    DRV_AGENT_IDENTIFYSTART_SET_REQ      = 0x009E,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_IDENTIFYEND_SET_REQ        = 0x00A0,                              /* _H2ASN_MsgChoice DRV_AGENT_IDENTIFYEND_SET_REQ_STRU */
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ   = 0x00A2,                              /* _H2ASN_MsgChoice DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU */
    DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ   = 0x00A4,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ    = 0x00A6,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_PHONEPHYNUM_SET_REQ        = 0x00A8,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU */
    DRV_AGENT_PHONEPHYNUM_QRY_REQ        = 0x00AA,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_PORTCTRLTMP_SET_REQ        = 0x00AC,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU */
    DRV_AGENT_PORTATTRIBSET_SET_REQ      = 0x00AE,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU */
    DRV_AGENT_PORTATTRIBSET_QRY_REQ      = 0x00B0,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_OPWORD_SET_REQ             = 0x00B2,                              /* _H2ASN_MsgChoice DRV_AGENT_OPWORD_SET_REQ_STRU */
    DRV_AGENT_SARREDUCTION_SET_REQ       = 0x00B4,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */

    /* Add by h00135900 for V7代码同步, 2012-04-07, Begin   */
    DRV_AGENT_INFORRS_SET_REQ            = 0x0100,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    /* Add by h00135900 for V7代码同步, 2012-04-07, End   */

    DRV_AGENT_MAX_LOCK_TIMES_SET_REQ     = 0x0102,

    DRV_AGENT_AP_SIMST_SET_REQ           = 0x0104,                              /* _H2ASN_MsgChoice DRV_AGENT_AP_SIMST_SET_REQ_STRU */

    DRV_AGENT_SWVER_SET_REQ              = 0x0106,                              /* _H2ASN_MsgChoice DRV_AGENT_SWVER_INFO_STRU */
    DRV_AGENT_QRY_CCPU_MEM_INFO_REQ      = 0x0108,

    DRV_AGENT_HVPDH_REQ                  = 0x010A,

    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
    DRV_AGENT_NVMANUFACTUREEXT_SET_REQ   = 0x010C,
    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

    DRV_AGENT_ANTSWITCH_SET_REQ          = 0x010E,                              /* _H2ASN_MsgChoice DRV_AGENT_ANTSWITCH_SET_STRU */
    DRV_AGENT_ANTSWITCH_QRY_REQ          = 0x0110,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */

    /* DRV AGENT发给AT的消息 */
    DRV_AGENT_MSID_QRY_CNF               = 0x0001,                              /* _H2ASN_MsgChoice DRV_AGENT_MSID_QRY_CNF_STRU */
    DRV_AGENT_GAS_MNTN_CMD_RSP           = 0x0005,
    DRV_AGENT_GPIOPL_SET_CNF             = 0x000D,
    DRV_AGENT_GPIOPL_QRY_CNF             = 0x000F,
    DRV_AGENT_DATALOCK_SET_CNF           = 0x0011,
    DRV_AGENT_TBATVOLT_QRY_CNF           = 0x0013,
    DRV_AGENT_VERTIME_QRY_CNF            = 0x0015,
    DRV_AGENT_YJCX_SET_CNF               = 0x001F,
    DRV_AGENT_YJCX_QRY_CNF               = 0x0021,
    DRV_AGENT_APPDMVER_QRY_CNF           = 0x0023,                              /* _H2ASN_MsgChoice DRV_AGENT_APPDMVER_QRY_CNF_STRU */
    DRV_AGENT_DLOADINFO_QRY_CNF          = 0x0027,                              /* _H2ASN_MsgChoice DRV_AGENT_DLOADINFO_QRY_CNF_STRU */
    DRV_AGENT_FLASHINFO_QRY_CNF          = 0x0029,                              /* _H2ASN_MsgChoice DRV_AGENT_FLASHINFO_QRY_CNF_STRU*/
    DRV_AGENT_AUTHVER_QRY_CNF            = 0x002B,                              /* _H2ASN_MsgChoice DRV_AGENT_AUTHVER_QRY_CNF_STRU*/
    DRV_AGENT_AUTHORITYVER_QRY_CNF       = 0x002F,                              /* _H2ASN_MsgChoice DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU*/
    DRV_AGENT_AUTHORITYID_QRY_CNF        = 0x0031,                              /* _H2ASN_MsgChoice DRV_AGENT_AUTHORITYID_QRY_CNF_STRU*/
    DRV_AGENT_GODLOAD_SET_CNF            = 0x0033,                              /* _H2ASN_MsgChoice DRV_AGENT_GODLOAD_SET_CNF_STRU*/
    DRV_AGENT_HWNATQRY_QRY_CNF           = 0x0035,                              /* _H2ASN_MsgChoice DRV_AGENT_HWNATQRY_QRY_CNF_STRU*/
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
    DRV_AGENT_CPULOAD_QRY_CNF            = 0x0037,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_MFREELOCKSIZE_QRY_CNF      = 0x0039,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */

    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
    DRV_AGENT_MEMINFO_QRY_CNF            = 0x003A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */

    DRV_AGENT_HARDWARE_QRY_RSP           = 0x003D, /*回复硬件版本号*/
    DRV_AGENT_FULL_HARDWARE_QRY_RSP      = 0x003F, /*回复完整的硬件版本号*/
    DRV_AGENT_VERSION_QRY_CNF            = 0x0047,
    DRV_AGENT_SECUBOOT_QRY_CNF           = 0x0049,
    DRV_AGENT_SECUBOOTFEATURE_QRY_CNF    = 0x004B,
    DRV_AGENT_PFVER_QRY_CNF              = 0x004D,                              /* _H2ASN_MsgChoice DRV_AGENT_PFVER_QRY_CNF_STRU */
    DRV_AGENT_FCHAN_SET_CNF              = 0x0053,
    DRV_AGENT_SDLOAD_SET_CNF             = 0x0057,
    DRV_AGENT_SFEATURE_QRY_CNF           = 0x0059,
    DRV_AGENT_PRODTYPE_QRY_CNF           = 0x0061,
    DRV_AGENT_RXDIV_SET_CNF              = 0x0063,
    DRV_AGENT_DLOADVER_QRY_CNF           = 0x0065,
    DRV_AGENT_RXDIV_QRY_CNF              = 0x0069,
    DRV_AGENT_SIMLOCK_SET_CNF            = 0x006B,
    DRV_AGENT_IMSICHG_QRY_CNF            = 0x0071,                              /* _H2ASN_MsgChoice DRV_AGENT_IMSICHG_QRY_CNF_STRU */
    DRV_AGENT_NVRESTORE_SET_CNF          = 0x0073,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_INFORBU_SET_CNF            = 0x0075,                              /* _H2ASN_MsgChoice DRV_AGENT_INFORBU_SET_CNF_STRU */
    DRV_AGENT_NVRSTSTTS_QRY_CNF          = 0x0077,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_CPNN_TEST_CNF              = 0x0079,                              /* _H2ASN_MsgChoice DRV_AGENT_CPNN_TEST_CNF_STRU */
    DRV_AGENT_NVBACKUP_SET_CNF           = 0x007B,                              /* _H2ASN_MsgChoice DRV_AGENT_NVBACKUP_SET_CNF_STRU */
    DRV_AGENT_CPNN_QRY_CNF               = 0x007D,                              /* _H2ASN_MsgChoice DRV_AGENT_CPNN_QRY_CNF_STRU */
    DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF = 0x007F,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_ADC_SET_CNF                = 0x0081,
    DRV_AGENT_TSELRF_SET_CNF             = 0x0083,                              /* _H2ASN_MsgChoice DRV_AGENT_TSELRF_SET_CNF_STRU */
    DRV_AGENT_HKADC_GET_CNF              = 0x0085,                              /* _H2ASN_MsgChoice DRV_AGENT_HKADC_GET_CNF_STRU */
    DRV_AGENT_TBAT_QRY_CNF               = 0x0087,
    DRV_AGENT_SECUBOOT_SET_CNF           = 0x0089,                              /* _H2ASN_MsgChoice DRV_AGENT_SECUBOOT_SET_CNF_STRU */
    DRV_AGENT_SPWORD_SET_CNF             = 0x008B,

    DRV_AGENT_NVBACKUPSTAT_QRY_CNF       = 0x008D,                              /* _H2ASN_MsgChoice DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU */
    DRV_AGENT_NANDBBC_QRY_CNF            = 0x008F,                              /* _H2ASN_MsgChoice DRV_AGENT_NANDBBC_QRY_CNF_STRU */
    DRV_AGENT_NANDVER_QRY_CNF            = 0x0091,                              /* _H2ASN_MsgChoice DRV_AGENT_NANDVER_QRY_CNF_STRU */
    DRV_AGENT_CHIPTEMP_QRY_CNF           = 0x0093,                              /* _H2ASN_MsgChoice DRV_AGENT_CHIPTEMP_QRY_CNF_STRU */


    DRV_AGENT_HUK_SET_CNF                = 0x0095,                              /* _H2ASN_MsgChoice DRV_AGENT_HUK_SET_CNF_STRU */
    DRV_AGENT_FACAUTHPUBKEY_SET_CNF      = 0x0097,                              /* _H2ASN_MsgChoice DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU */
    DRV_AGENT_IDENTIFYSTART_SET_CNF      = 0x0099,                              /* _H2ASN_MsgChoice DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU */
    DRV_AGENT_IDENTIFYEND_SET_CNF        = 0x009B,                              /* _H2ASN_MsgChoice DRV_AGENT_IDENTIFYEND_SET_CNF_STRU */
    DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF   = 0x009D,                              /* _H2ASN_MsgChoice DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU */
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF   = 0x009F,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU */
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF    = 0x00A1,                              /* _H2ASN_MsgChoice DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU */
    DRV_AGENT_PHONEPHYNUM_SET_CNF        = 0x00A3,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU */
    DRV_AGENT_PHONEPHYNUM_QRY_CNF        = 0x00A5,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU */
    DRV_AGENT_PORTCTRLTMP_SET_CNF        = 0x00A7,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU */
    DRV_AGENT_PORTATTRIBSET_SET_CNF      = 0x00A9,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU */
    DRV_AGENT_PORTATTRIBSET_QRY_CNF      = 0x00AB,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU */
    DRV_AGENT_OPWORD_SET_CNF             = 0x00AD,                              /* _H2ASN_MsgChoice DRV_AGENT_OPWORD_SET_CNF_STRU */
    DRV_AGENT_ANTSTATE_QRY_IND           = 0x00AF,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Add by h00135900 for V7代码同步, 2012-04-07, Begin   */
    DRV_AGENT_INFORRS_SET_CNF            = 0x0101,                              /* _H2ASN_MsgChoice DRV_AGENT_INFORRS_SET_CNF_STRU */

    /* Add by h00135900 for V7代码同步, 2012-04-07, End   */

    DRV_AGENT_MAX_LOCK_TIMES_SET_CNF     = 0x0103,                              /* _H2ASN_MsgChoice DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU */

    DRV_AGENT_AP_SIMST_SET_CNF           = 0x0105,                              /* _H2ASN_MsgChoice DRV_AGENT_AP_SIMST_SET_CNF_STRU */

    DRV_AGENT_SWVER_SET_CNF              = 0x0107,                              /* _H2ASN_MsgChoice DRV_AGENT_SWVER_SET_CNF_STRU */

    DRV_AGENT_HVPDH_CNF                  = 0x0109,

    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
    DRV_AGENT_NVMANUFACTUREEXT_SET_CNF   = 0x010B,
    /* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

    DRV_AGENT_ANTSWITCH_SET_CNF          = 0x010D,                              /* _H2ASN_MsgChoice DRV_AGENT_ANTSWITCH_SET_CNF_STRU */
    DRV_AGENT_ANTSWITCH_QRY_CNF          = 0x010F,                              /* _H2ASN_MsgChoice DRV_AGENT_ANTSWITCH_QRY_CNF_STRU */
    DRV_AGENT_MSG_TYPE_BUTT              = 0xFFFF
};
typedef VOS_UINT32 DRV_AGENT_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_DEVICE_CMD_RAT_MODE_ENUM
 结构说明  : 装备AT命令模式枚举

  1.日    期   : 2011年10月15日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
enum AT_DEVICE_CMD_RAT_MODE_ENUM
{
    AT_RAT_MODE_WCDMA = 0,
    AT_RAT_MODE_CDMA,
    AT_RAT_MODE_TDSCDMA,
    AT_RAT_MODE_GSM,
    AT_RAT_MODE_EDGE,
    AT_RAT_MODE_AWS,
    AT_RAT_MODE_FDD_LTE,
    AT_RAT_MODE_TDD_LTE,
    AT_RAT_MODE_WIFI,
    AT_RAT_MODE_BUTT
};
typedef VOS_UINT8 AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8;

/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */

/* 查询软件内存事情类型  */
enum AT_MEMQUERY_PARA_ENUM
{
    AT_MEMQUERY_VOS = 0,  /* 查询VOS的半静态内存实际的占用情况 */
    AT_MEMQUERY_TTF,      /* 查询TTF的半静态内存实际的占用情况 */
    AT_MEMQUERY_BUTT
};
typedef VOS_UINT32  AT_MEMQUERY_PARA_ENUM_UINT32;

/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */

/*****************************************************************************
枚举名    : DRV_AGENT_DH_KEY_TYPE_ENUM
枚举说明  : DH算法使用的秘钥类型

  1.日    期   : 2013年8月27日
    作    者   : L47619
    修改内容   : V9R1 vSIM项目修改

*****************************************************************************/
enum DRV_AGENT_DH_KEY_TYPE_ENUM
{
    DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY  = 0x00,          /* 服务器公钥 */
    DRV_AGENT_DH_KEY_MODEM_PUBLIC_KEY   = 0x01,          /* MODEM侧公钥 */
    DRV_AGENT_DH_KEY_MODEM_PRIVATE_KEY  = 0x02,          /* MODEM侧私钥 */

    DRV_AGENT_DH_KEY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_DH_KEY_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : DRV_AGENT_HVPDH_ERR_ENUM
枚举说明  : 设置DH算法的秘钥结果

  1.日    期   : 2013年8月27日
    作    者   : L47619
    修改内容   : V9R1 vSIM项目修改

*****************************************************************************/
enum DRV_AGENT_HVPDH_ERR_ENUM
{
    DRV_AGENT_HVPDH_NO_ERROR            = 0x00,          /* 操作成功 */
    DRV_AGENT_HVPDH_AUTH_UNDO           = 0x01,          /* 此时还未进行过产线鉴权 */
    DRV_AGENT_HVPDH_NV_READ_FAIL        = 0x02,          /* NV读取失败 */
    DRV_AGENT_HVPDH_NV_WRITE_FAIL       = 0x03,          /* NV写入失败 */
    DRV_AGENT_HVPDH_OTHER_ERROR         = 0x04,          /* 其他错误 */

    DRV_AGENT_HVPDH_ERR_BUTT
};
typedef VOS_UINT32 DRV_AGENT_HVPDH_ERR_ENUM_UINT32;




/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/* Modify by f62575 for V7代码同步, 2012-04-07, Begin   */
/*****************************************************************************
 结构名    : DRV_AGENT_PSTANDBY _REQ_STRU
 结构说明  : AT与AT AGENT AT^PSTANDBY设置命令结构

  1.日    期   : 2012年04月12日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStandbyTime;                          /* 单板进入待机状态的时间长度，(单位为ms),取值范围 0~65535,默认为5000。 */
    VOS_UINT32                          ulSwitchTime;                           /* 用于指定PC下发待机命令到单板进入待机状态的切换时间。（单位为ms），取值范围为 0~65535，默认为500。 */
} DRV_AGENT_PSTANDBY_REQ_STRU;
/* Modify by f62575 for V7代码同步, 2012-04-07, End   */


/*****************************************************************************
 结构名    : DRV_AGENT_REQ_STRU
 结构说明  : AT与DRV AGENT的消息结构

  1.日    期   : 2011年10月29日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: DRV AGENT给AT的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           aucContent[4];
} DRV_AGENT_MSG_STRU;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 枚举名    : GAS_AT_CMD_ENUM
 结构说明  : GAS测试命令类型枚举结构

  1.日    期   : 2011年10月15日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
typedef enum
{
    GAS_AT_CMD_GAS_STA          =   0,  /* GAS状态 */
    GAS_AT_CMD_NCELL            =   1,  /* 邻区状态 */
    GAS_AT_CMD_SCELL            =   2,  /* 服务小区状态 */
    GAS_AT_CMD_MEASURE_DOWN     =   3,  /* 测量下移 */
    GAS_AT_CMD_MEASURE_UP       =   4,  /* 测量上移 */
    GAS_AT_CMD_FREQ_LOCK        =   5,  /* 锁频点，允许被动重选 */
    GAS_AT_CMD_FREQ_UNLOCK      =   6,  /* 解锁 */
    GAS_AT_CMD_FREQ_SPEC_SEARCH =   7,  /* 指定频点搜网 */
    GAS_AT_CMD_BUTT
}GAS_AT_CMD_ENUM;

typedef VOS_UINT8 GAS_AT_CMD_ENUM_U8;

/*****************************************************************************
 枚举名    : GAS_AT_CMD_ENUM
 结构说明  : GAS测试命令结构

  1.日    期   : 2011年10月15日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    GAS_AT_CMD_ENUM_U8                  ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[10];
}GAS_AT_CMD_STRU;

/*****************************************************************************
 枚举名    : GAS_AT_CMD_ENUM
 结构说明  : GAS测试命令结果结构

  1.日    期   : 2011年10月15日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[20];
}GAS_AT_RSLT_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_MSID_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询MS ID信息消息回复结构

  1.日    期   : 2011年10月15日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                      stAtAppCtrl;                                   /* AT用户控制结构 */
    DRV_AGENT_MSID_QRY_ERROR_ENUM_UINT32 ulResult;                                      /* 消息处理结果 */
    VOS_INT8                             acModelId[TAF_MAX_MODEL_ID_LEN + 1];           /* 模块信息 */
    VOS_INT8                             acSoftwareVerId[TAF_MAX_REVISION_ID_LEN + 1];  /* 软件版本信息 */
    VOS_UINT8                            aucImei[TAF_PH_IMEI_LEN];
} DRV_AGENT_MSID_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_TSELRF_SET_REQ_STRU
 结构说明  : ^TSELRF设置命令，请求加载DSP
             ucLoadDspMode  请求加载的DSP模式
 1.日    期   : 20112年1月10日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLoadDspMode;
    VOS_UINT8                           ucDeviceRatMode;
} DRV_AGENT_TSELRF_SET_REQ_STRU;

/* Added by f62575 for AT Project，2011-10-04,  Begin*/
/*****************************************************************************
 结构名    : DRV_AGENT_APPDMVER_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询AP PDMVER信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_APPDMVER_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_INT8                                 acPdmver[AT_MAX_PDM_VER_LEN + 1];
    VOS_UINT8                                aucReserved1[3];
} DRV_AGENT_APPDMVER_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_DLOADINFO_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询DLOADINFO信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                           stAtAppCtrl;
    DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UCHAR                                 aucDlodInfo[TAF_DLOAD_INFO_LEN];
} DRV_AGENT_DLOADINFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询AUTHORITYVER信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                              stAtAppCtrl;
    DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UINT8                                    aucAuthority[TAF_AUTHORITY_LEN + 1];
    VOS_UINT8                                    aucReserved1[1];
} DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_AUTHORITYID_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询DLOADINFO信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                             stAtAppCtrl;
    DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UINT8                                   aucAuthorityId[TAF_AUTH_ID_LEN + 1];
    VOS_UINT8                                   aucReserved1[1];
} DRV_AGENT_AUTHORITYID_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PFVER_REQ_STRU
 结构说明  : 平台软件版本号
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPfVer[TAF_MAX_PROPLAT_LEN + 1];
    VOS_CHAR                            acVerTime[AT_AGENT_DRV_VERSION_TIME_LEN];
}DRV_AGENT_PFVER_INFO_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PFVER_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询PFVER信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                       stAtAppCtrl;
    DRV_AGENT_PFVER_QRY_ERROR_ENUM_UINT32 enResult;
    DRV_AGENT_PFVER_INFO_STRU             stPfverInfo;
} DRV_AGENT_PFVER_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SDLOAD_SET_CNF_STRU
 结构说明  : AT与AT AGENT 设置SDLOAD 消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                               stAtAppCtrl;
    DRV_AGENT_SDLOAD_SET_ERROR_ENUM_UINT32        enResult;
} DRV_AGENT_SDLOAD_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_DLOADVER_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询DLOADVER 消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                               stAtAppCtrl;
    DRV_AGENT_DLOADVER_QRY_ERROR_ENUM_UINT32      enResult;
    VOS_CHAR                                      aucVersionInfo[TAF_MAX_VER_INFO_LEN + 1];
    VOS_UINT8                                     ucReserved1;
} DRV_AGENT_DLOADVER_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_DLOADINFO_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 设置GODLOAD 信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_GODLOAD_SET_ERROR_ENUM_UINT32  enResult;
} DRV_AGENT_GODLOAD_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_HWNATQRY_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询HWNATQRY信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UINT                                 ulNetMode;
} DRV_AGENT_HWNATQRY_QRY_CNF_STRU;

/* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, begin */
/*****************************************************************************
 结构名    : DRV_AGENT_CPULOAD_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询CPULOAD信息消息回复结构
 1.日    期   : 2011年11月12日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_CPULOAD_QRY_ERROR_ENUM_UINT32  enResult;
    VOS_UINT32                               ulCurACpuLoad;
    VOS_UINT32                               ulCurCCpuLoad;
} DRV_AGENT_CPULOAD_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_MFREELOCKSIZE_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询MFREELOCKSIZE信息消息回复结构
 1.日    期   : 2011年11月12日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;
    DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM_UINT32   enResult;
    VOS_INT32                                       lMaxFreeLockSize;
}DRV_AGENT_MFREELOCKSIZE_QRY_CNF_STRU;
/* Added by 傅映君/f62575 for CPULOAD&MFREELOCKSIZE处理过程移至C核, 2011/11/15, end */

/*****************************************************************************
 结构名    : DRV_AGENT_DLOAD_FLASH_STRU
 结构说明  :升级Flash信息;该结构与DLOAD_FLASH_STRU_S一致

 1.日    期   : 2011年11月1日
   作    者   : l60609
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulBlockCount;                       /*Block个数*/
    VOS_UINT32                              ulPageSize;                         /*page页大小*/
    VOS_UINT32                              ulPgCntPerBlk;                      /*一个Block中的page个数*/
}DRV_AGENT_DLOAD_FLASH_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_FLASHINFO_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询FLASHINFO信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                           stAtAppCtrl;
    DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM_UINT32 enResult;
    DRV_AGENT_DLOAD_FLASH_STRU                stFlashInfo;
} DRV_AGENT_FLASHINFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_AUTHVER_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询AUTHVER信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                           stAtAppCtrl;
    DRV_AGENT_AUTHVER_QRY_ERROR_ENUM_UINT32   enResult;
    VOS_UINT32                                ulSimLockVersion;
} DRV_AGENT_AUTHVER_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_APPDMVER_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询AP PDMVER信息消息回复结构
 1.日    期   : 2011年10月4日
   作    者   : f62575
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_APPDMVER_QRY_ERROR_ENUM_UINT32 enResult;
} DRV_AGENT_SDLOAD_QRY_CNF_STRU;
/* Added by f62575 for AT Project，2011-10-04,  End*/

/* Added by o00132663 for AT Project，2011-10-04,  Begin */
/*****************************************************************************
 结构名    : DRV_AGENT_VERSION_CTRL_STRU
 结构说明  : AT与AT AGENT版本查询与控制结构

1.日    期   : 2011年10月15日
  作    者   : o00132663
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucType;                                 /* 组件类型: COMP_TYPE_I */
    VOS_UINT8                           ucMode;                                 /* 操作模式: 读或者写 */
    VOS_UINT8                           aucReserved[1];                         /* 数据指针 */
    VOS_UINT8                           ucLen;                                  /* 数据长度 */
    VOS_CHAR                            aucData[AT_MAX_VERSION_LEN];
} DRV_AGENT_VERSION_CTRL_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_GAS_MNTN_CMD_CNF_STRU
 结构说明  : AT与AT AGENT AT^CGAS命令回复结构

1.日    期   : 2011年10月15日
  作    者   : o00132663
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    GAS_AT_CMD_ENUM_U8                  ucCmd;
    VOS_UINT8                           aucReserved[3];
    GAS_AT_RSLT_STRU                    stAtCmdRslt;
} DRV_AGENT_GAS_MNTN_CMD_CNF_STRU;

/*****************************************************************************
 结构名    : AT_DRV_AGENT_RXDIV_SET_STRU
 结构说明  : AT与AT AGENT AT^RXDIV设置命令结构

修改历史      :
 1.日    期   : 2011年10月5日
   作    者   : C00173809
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDspBand;       /*DSP格式的频段值*/
    VOS_UINT8                           ucRxOnOff;       /* Rx on off值*/
    VOS_UINT8                           ucReserve;       /*保留位*/
    VOS_UINT32                          ulSetLowBands;   /*转换位数字格式的分集低位*/
    VOS_UINT32                          ulSetHighBands;  /*转换位数字格式的分集高位*/
} AT_DRV_AGENT_RXDIV_SET_STRU;
/*****************************************************************************
 结构名    : DRV_AGENT_RXDIV_CNF_STRU
 结构说明  : AT与AT AGENT AT^RXDIV命令回复结构

修改历史      :
 1.日    期   : 2011年10月5日
   作    者   : C00173809
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;        /*消息头*/
    VOS_UINT32                          ulResult;           /*返回结果*/
    VOS_UINT8                           ucRxOnOff;          /*RX是否已经打开*/
    VOS_UINT8                           ucReserve;          /*保留位*/
    VOS_UINT16                          usSetDivBands;      /*要设置的BAND*/
} DRV_AGENT_AT_RXDIV_CNF_STRU;
/*****************************************************************************
 结构名    : DRV_AGENT_QRY_RXDIV_CNF_STRU
 结构说明  : AT与AT AGENT AT^RXDIV命令回复结构

修改历史      :
 1.日    期   : 2011年10月22日
   作    者   : C00173809
   修改内容   : 新生成函数
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;        /*消息头*/
    VOS_UINT32                          ulResult;           /*返回结果*/
    VOS_UINT16                          usDrvDivBands;      /*支持的BAND*/
    VOS_UINT16                          usCurBandSwitch;    /*当前设置的BAND*/
} DRV_AGENT_QRY_RXDIV_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SIMLOCK_SET_REQ_STRU
 结构说明  : DRV与AT AGENT simlock的校验的消息结构

 1.日    期   : 2011年11月3日
    作    者   : C00173809
    修改内容   : 新增结构体
 2.日    期   : 2012年02月20日
    作    者   : L60609
    修改内容   : 结构中删除错误次数，直接在C核记录

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPwdLen;
    VOS_UINT8                           aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +4];
}DRV_AGENT_SIMLOCK_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SET_SIMLOCK_CNF_STRU
 结构说明  : DRV与AT AGENT simlock的校验的消息结构

 1.日    期   : 2011年11月3日
    作    者   : C00173809
    修改内容   : 新增结构体
  2.日    期   : 2012年2月20日
    作    者   : l60609
    修改内容   : B060 Prj:AT不需要记录SIMLOCK错误次数，删除全局变量g_ucAtSi-
                 mLockErrTimes
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /*消息头*/
    VOS_UINT32                          ulResult;                               /*返回结果*/
}DRV_AGENT_SET_SIMLOCK_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_DRV_AGENT_HARDWARE_QRY_CNF_STRU
 结构说明  : AT与AT AGENT AT^HWVER命令回复结构

1.日    期   : 2011年10月15日
  作    者   : c00173809
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /*消息头*/
    VOS_UINT32                          ulResult;                               /*返回结果*/
    VOS_UINT8                           aucHwVer[DRV_AGENT_MAX_HARDWARE_LEN+1]; /*硬件版本号*/
} DRV_AGENT_HARDWARE_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU
 结构说明  : AT与AT AGENT AT^FHVER命令回复结构

1.日    期   : 2011年10月15日
  作    者   : c00173809
  修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                                        /*消息头*/
    VOS_UINT32                          ulResult;                                           /*返回结果*/
    VOS_UINT8                           aucModelId[DRV_AGENT_MAX_MODEL_ID_LEN + 1];         /*MODE ID号*/
    VOS_UINT8                           aucRevisionId[DRV_AGENT_MAX_REVISION_ID_LEN + 1];   /*软件版本号*/
    VOS_UINT8                           aucHwVer[DRV_AGENT_MAX_HARDWARE_LEN+1];             /*硬件版本号*/
} DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_NVRESTORE_RST_STRU
 结构说明  : AT与AT AGENT AT^NVRESTORE设置命令回复结构

  1.日    期   : 2011年11月03日
    作    者   : f00179208
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /*消息头*/
    VOS_UINT32                          ulResult;                               /*返回结果*/
} DRV_AGENT_NVRESTORE_RST_STRU;

/* Added by o00132663 for AT Project，2011-10-04,  End */

#define AT_SD_DATA_UNIT_LEN             (512)
#define AT_GPIOPL_MAX_LEN               (20)


/*****************************************************************************
 结构名    : DRV_AGENT_GPIOPL_SET_REQ_STRU
 结构说明  : DRV与AT AGENT设置GPIO电平消息的请求结构

 1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enGpioOper;
    VOS_UINT8                           aucGpiopl[AT_GPIOPL_MAX_LEN];

}DRV_AGENT_GPIOPL_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_GPIOPL_SET_CNF_STRU
 结构说明  : DRV与AT AGENT设置GPIO电平消息的请求结构

 1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;

}DRV_AGENT_GPIOPL_SET_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_GPIOPL_QRY_CNF_STRU
 结构说明  : DRV与AT AGENT查询GPIO电平消息的回复结构

  1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_UINT8                           aucGpiopl[AT_GPIOPL_MAX_LEN];

}DRV_AGENT_GPIOPL_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_DATALOCK_SET_REQ_STRU
 结构说明  : DRV与AT AGENT datalock的校验的消息结构

 1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];

}DRV_AGENT_DATALOCK_SET_REQ_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_DATALOCK_SET_CNF_STRU
 结构说明  : DRV与AT AGENT datalock的校验的消息回复结构

 1.日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;           /* DATALOCK校验是否成功 */

}DRV_AGENT_DATALOCK_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_TBATVOLT_QRY_CNF_STRU
 结构说明  : DRV与AT AGENT 查询电池电压的消息回复结构

1.日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{

    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_INT32                           lBatVol;

}DRV_AGENT_TBATVOLT_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_TMODE_SET_CNF
 结构说明  : AT与AT AGENT 设置升级标志位的消息结构

1.日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;

}DRV_AGENT_TMODE_SET_CNF_STRU;

/*****************************************************************************
 枚举名    : DRV_AGENT_VERSION_QRY_ERROR_ENUM
 结构说明  : ^VERSION命令查询操作结果错误码列表

 1. 日    期   : 2011年10月15日
    作    者   : w00181244
    修改内容   : 新增枚举

*****************************************************************************/
enum DRV_AGENT_VERSION_QRY_ERROR_ENUM
{
    DRV_AGENT_VERSION_QRY_NO_ERROR              = 0,
    DRV_AGENT_VERSION_QRY_VERTIME_ERROR         = 1,

    DRV_AGENT_VERSION_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_VERSION_QRY_ERROR_ENUM_UINT32;


/*****************************************************************************
 结构名    : DRV_AGENT_VERSION_QRY_CNF_STRU
 结构说明  : DRV与AT AGENT 查询版本信息的回复消息结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    TAF_PH_REVISION_ID_STRU                  stSoftVersion;                                 /*软件版本号*/
    TAF_PH_HW_VER_STRU                       stFullHwVer;                                   /*外部硬件版本号*/
    TAF_PH_HW_VER_STRU                       stInterHwVer;                                  /*内部硬件版本号*/
    TAF_PH_MODEL_ID_STRU                     stModelId;                                     /*外部产品ID */
    TAF_PH_MODEL_ID_STRU                     stInterModelId;                                /*内部产品ID */
    TAF_PH_CDROM_VER_STRU                    stIsoVer;                                      /*后台软件版本号*/
    DRV_AGENT_VERSION_QRY_ERROR_ENUM_UINT32  enResult;                                      /*错误码枚举 */
    VOS_CHAR                                 acVerTime[AT_AGENT_DRV_VERSION_TIME_LEN];      /*编译时间*/

}DRV_AGENT_VERSION_QRY_CNF_STRU;

/*******************************************************************************
 结构名    : WCDMA_PREF_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : union WCDMA_BAND_SET_UN成员BitBand定义
             bit位置1表示该频段有效

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
2. 日    期   : 2012年5月10日
   作    者   : f62575
   修改内容   : DTS2012051007817 解决SFEATURE查询命令没有WCDMA 的BAND11输出问题
3. 日    期   : 2012年11月12日
   作    者   : t00212959
   修改内容   : DTS2012103101740,MMA中Band结构改为UINT32,AT保持一致
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpare1            :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}AT_WCDMA_PREF_BAND_STRU;

/*******************************************************************************
 结构名    :GSM_PREF_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : union GSM_BAND_SET_UN成员BitBand定义
             bit位置1表示该频段有效

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
2. 日    期   : 2012年11月12日
   作    者   : t00212959
   修改内容   : DTS2012103101740,MMA中Band结构改为UINT32,AT保持一致
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare7      :23;

}AT_GSM_PREF_BAND_STRU;

/*******************************************************************************
 结构名    : WCDMA_BAND_SET_UN
 协议表格  :
 ASN.1描述 :
 结构说明  : WCDMA频段union定义

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
2. 日    期   : 2012年11月12日
   作    者   : t00212959
   修改内容   : DTS2012103101740,MMA中Band结构改为UINT32,AT保持一致
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;
    AT_WCDMA_PREF_BAND_STRU             BitBand;
}AT_WCDMA_BAND_SET_UN;

/*******************************************************************************
 结构名    : GSM_BAND_SET_UN
 协议表格  :
 ASN.1描述 :
 结构说明  : GSM频段union定义

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
2. 日    期   : 2012年11月12日
   作    者   : t00212959
   修改内容   : DTS2012103101740,MMA中Band结构改为UINT32,AT保持一致
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;
    AT_GSM_PREF_BAND_STRU               BitBand;
}AT_GSM_BAND_SET_UN;


/*******************************************************************************
 结构名    : AT_UE_BAND_CAPA_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 单板支持频段信息

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUeGSptBand;
    VOS_UINT32                          ulUeWSptBand;
    VOS_UINT32                          ulAllUeBand;
    AT_WCDMA_BAND_SET_UN                unWRFSptBand;
    AT_GSM_BAND_SET_UN                  unGRFSptBand;
}AT_UE_BAND_CAPA_ST;

/*****************************************************************************
 枚举名    : AT_FEATURE_DRV_TYPE_ENUM
 协议表格  :
 枚举说明  : 驱动支持特性的枚举

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
enum AT_FEATURE_DRV_TYPE_ENUM
{
    AT_FEATURE_LTE = 0,
    AT_FEATURE_HSPAPLUS,
    AT_FEATURE_HSDPA,
    AT_FEATURE_HSUPA,
    AT_FEATURE_DIVERSITY,
    AT_FEATURE_UMTS,
    AT_FEATURE_EVDO,
    AT_FEATURE_EDGE,
    AT_FEATURE_GPRS,
    AT_FEATURE_GSM,
    AT_FEATURE_CDMA,
    AT_FEATURE_WIMAX,
    AT_FEATURE_WIFI,
    AT_FEATURE_GPS,
    AT_FEATURE_TDSCDMA
};
typedef VOS_UINT32  AT_FEATURE_DRV_TYPE_ENUM_UINT32;

#define AT_FEATURE_NAME_LEN_MAX       (16)
#define AT_FEATURE_CONTENT_LEN_MAX    (56)


/*****************************************************************************
 结构名    : AT_PRO_FEA_INFO_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : 对应驱动支持的特性

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucFeatureFlag;
    VOS_UINT8        aucFeatureName[AT_FEATURE_NAME_LEN_MAX];
    VOS_UINT8        aucContent[AT_FEATURE_CONTENT_LEN_MAX];
}AT_FEATURE_SUPPORT_ST;

/*****************************************************************************
 结构名    : AT_RF_CAPA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RF 能力信息

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPowerClass;       /* UE功率级别                      */
    VOS_UINT8                           enTxRxFreqSeparate; /* Tx/Rx 频率区间                  */
    VOS_UINT8                           aucReserve1[2];     /* 4字节对齐，保留                 */
} AT_RF_CAPA_STRU;


/*****************************************************************************
 结构名    : AT_UE_CAPA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : en_NV_Item_WAS_RadioAccess_Capa NV项对应的结构，
             用于保存是否使能了HSDPA、HSUPA、HSDPA能力等级

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHspaStatus;       /* 0表示未激活,那么DPA和UPA都支持;1表示激活           */
    VOS_UINT8                           ucMacEhsSupport;
    VOS_UINT8                           ucHSDSCHPhyCat;
    VOS_UINT8                           aucReserve1[2];     /* 改用一个激活项ulHspaStatus进行控制，此变量不再使用 */
    AT_RF_CAPA_STRU                     stRfCapa;           /* RF 能力信息  */
    VOS_UINT8                           enDlSimulHsDschCfg; /* ENUMERATED  OPTIONAL  */
    VOS_UINT8                           enAsRelIndicator;   /* Access Stratum Release Indicator  */
    VOS_UINT8                           ucHSDSCHPhyCategory; /* 支持HS-DSCH物理层的类型标志 */
    VOS_UINT8                           enEDCHSupport;       /* 是否支持EDCH的标志 */
    VOS_UINT8                           ucEDCHPhyCategory;   /* 支持UPA的等级 */
    VOS_UINT8                           enFDPCHSupport;      /* 是否支持FDPCH的标志  */
    VOS_UINT8                           ucV690Container;     /* V690Container填写 */
    VOS_UINT8                           enHSDSCHSupport;     /* 是否支持enHSDSCHSupport的标志  */
} AT_UE_CAPA_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SFEATURE_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询版本频段信息的消息结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    AT_UE_BAND_CAPA_ST                  stBandFeature;

}DRV_AGENT_SFEATURE_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SECUBOOT_SET_CNF_STRU
 结构说明  : AT与AT AGENT 使能Secure Boot 功能的消息回复结构
 1.日    期   : 2012年02月06日
   作    者   : f62575
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
}DRV_AGENT_SECUBOOT_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SECUBOOT_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询Secure Boot 功能使能状态的消息回复结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_UINT8                           ucSecuBootEnable;
    VOS_UINT8                           aucReserve1[3];                          /* 4字节对齐，保留 */
}DRV_AGENT_SECUBOOT_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_SECUBOOTFEATURE_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询Secure Boot 版本的消息回复结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_UINT8                           ucSecuBootFeature;
    VOS_UINT8                           aucReserve1[7];                          /* 4字节对齐，保留 */
}DRV_AGENT_SECUBOOTFEATURE_QRY_CNF_STRU;

/*****************************************************************************
 枚举名    : AT_DEVICE_CMD_BAND_ENUM
 枚举说明  : 装备频段信息

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
enum AT_DEVICE_CMD_BAND_ENUM
{
    AT_BAND_2100M = 0,
    AT_BAND_1900M,
    AT_BAND_1800M,
    AT_BAND_1700M,
    AT_BAND_1600M,
    AT_BAND_1500M,
    AT_BAND_900M,
    AT_BAND_850M,
    AT_BAND_800M,
    AT_BAND_450M,
    AT_BAND_2600M,
    AT_BAND_1X_BC0,
    AT_BAND_WIFI = 15,
    AT_BAND_BUTT
};
typedef VOS_UINT8 AT_DEVICE_CMD_BAND_ENUM_UINT8;

/*****************************************************************************
 结构名    : AT_DSP_BAND_ARFCN_STRU
 结构说明  : 信道信息

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlArfcn;  /*上行的Channel No*/
    VOS_UINT16                          usDlArfcn;  /*下行的Channel No*/
    VOS_UINT16                          usDspBand;  /*DSP格式的频段值*/
    VOS_UINT8                           aucReserved[2];
}AT_DSP_BAND_ARFCN_STRU;

/*****************************************************************************
 结构名    : AT_ARFCN_RANGE_STRU
 结构说明  :每个信道对应的Afrcn的最大值和最小值

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_UINT16             usArfcnMin;
    VOS_UINT16             usArfcnMax;
}AT_ARFCN_RANGE_STRU;

/*****************************************************************************
 枚举名    : AT_TMODE_ENUM
 枚举说明  : 装备模式信息

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
2.日    期   : 2012年1月3日
  作    者   : f62575
  修改内容   : SMALL IMAGE特性合入: 新增自动关机下电过程，
               原<TESTMODE>4以上操作向后移动7个数值，从11开始
*****************************************************************************/
enum AT_TMODE_ENUM
{
    AT_TMODE_NORMAL = 0,   /*信令模式,正常服务状态*/
    AT_TMODE_FTM ,         /*非信令模式,校准模式*/
    AT_TMODE_UPGRADE ,     /*加载模式,版本升级时使用 */
    AT_TMODE_RESET,        /* 重启单板  */
    AT_TMODE_POWEROFF,
    AT_TMODE_SIGNALING = 11,
    AT_TMODE_OFFLINE,
#if((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS))
    AT_TMODE_F_NONESIGNAL   = 13,
    AT_TMODE_SYN_NONESIGNAL = 14,
    AT_TMODE_SET_SLAVE      = 15,
    AT_TMODE_GU_BT          = 16,
    AT_TMODE_TDS_FAST_CT    = 17,
    AT_TMODE_TDS_BT         = 18,
    AT_TMODE_COMM_CT        = 19,
#endif
    AT_TMODE_BUTT
};
typedef VOS_UINT8  TAF_PH_TMODE_ENUM_UINT8;

/*****************************************************************************
 结构名    : DRV_AGENT_FCHAN_SET_REQ_STRU
 结构说明  : DRV与AT AGENT 设置 FCHAN 的消息结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLoadDspMode;
    VOS_UINT8                           ucCurrentDspMode;
    VOS_UINT16                          usChannelNo;
    AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8   ucDeviceRatMode;
    AT_DEVICE_CMD_BAND_ENUM_UINT8       ucDeviceAtBand;
    VOS_UINT8                           aucReserved[2];
    VOS_BOOL                            bDspLoadFlag;
    AT_DSP_BAND_ARFCN_STRU              stDspBandArfcn;
}DRV_AGENT_FCHAN_SET_REQ_STRU;


/*****************************************************************************
 枚举名    : DRV_AGENT_FCHAN_SET_ERROR_ENUM
 结构说明  : FCHAN_命令设置操作结果错误码列表

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增枚举
*****************************************************************************/
enum DRV_AGENT_FCHAN_SET_ERROR_ENUM
{
    DRV_AGENT_FCHAN_SET_NO_ERROR                            = 0,
    DRV_AGENT_FCHAN_BAND_NOT_MATCH                          = 1,
    DRV_AGENT_FCHAN_BAND_CHANNEL_NOT_MATCH                  = 2,
    DRV_AGENT_FCHAN_OTHER_ERR                               = 3,

    DRV_AGENT_FCHAN_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32;


/*****************************************************************************
 结构名    : DRV_AGENT_FCHAN_SET_CNF_STRU
 结构说明  : AT与AT AGENT 设置 FCHAN 的消息回复结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                       stAtAppCtrl;
    DRV_AGENT_FCHAN_SET_REQ_STRU          stFchanSetReq;
    DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32 enResult;

}DRV_AGENT_FCHAN_SET_CNF_STRU;


/*****************************************************************************
  定义说明  :  MS支持的接收分集类型定义

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
#define AT_MS_SUPPORT_RX_DIV_2100           0x0001
#define AT_MS_SUPPORT_RX_DIV_1900           0x0002
#define AT_MS_SUPPORT_RX_DIV_1800           0x0004
#define AT_MS_SUPPORT_RX_DIV_AWS_1700       0x0008
#define AT_MS_SUPPORT_RX_DIV_850            0x0010
#define AT_MS_SUPPORT_RX_DIV_800            0x0020
#define AT_MS_SUPPORT_RX_DIV_2600           0x0040
#define AT_MS_SUPPORT_RX_DIV_900            0x0080
#define AT_MS_SUPPORT_RX_DIV_IX_1700        0x0100


/*****************************************************************************
 枚举名    : AT_DSP_RF_ON_OFF_ENUM_UINT8
 协议表格  :
 枚举说明  : RF开关

1. 日    期   : 2011年10月18日
   作    者   : w00181244
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
enum AT_DSP_RF_ON_OFF_ENUM
{
    AT_DSP_RF_SWITCH_OFF = 0,
    AT_DSP_RF_SWITCH_ON,
    AT_DSP_RF_SWITCH_BUTT
};
typedef VOS_UINT8 AT_DSP_RF_ON_OFF_ENUM_UINT8;

/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
/*****************************************************************************
 枚举名    : AT_PID_MEM_INFO_PARA_STRU
 协议表格  :
 枚举说明  : 每个PID的内存占用情况的结构体

1. 日    期   : 2011年11月30日
   作    者   : l00171473
   修改内容   : 从 AtCmdProc.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_PID                             ulPid;
    VOS_UINT32                          ulMsgPeakSize;
    VOS_UINT32                          ulMemPeakSize;
}AT_PID_MEM_INFO_PARA_STRU;
/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */

/*****************************************************************************
 结构名    : DRV_AGENT_RXPRI_SET_REQ_STRU
 结构说明  : AT与AT AGENT 设置 RXPRI 的消息结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetLowBands;
    VOS_UINT32                          ulSetHighBands;
    AT_DSP_BAND_ARFCN_STRU              stDspBandArfcn;
}DRV_AGENT_RXPRI_SET_REQ_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_RXPRI_SET_CNF_STRU
 结构说明  : AT与AT AGENT 设置 RXPRI 的消息回复结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    DRV_AGENT_ERROR_ENUM_UINT32         enResult;
    DRV_AGENT_RXPRI_SET_REQ_STRU        stRxpriSetReq;
    VOS_UINT16                          usWPriBands;
    VOS_UINT16                          usGPriBands;
    VOS_UINT16                          usSetPriBands;
    VOS_UINT8                           aucReserved[2];
}DRV_AGENT_RXPRI_SET_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_PRODTYPE_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询 PRODTYPE 的消息回复结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulProdType;

}DRV_AGENT_PRODTYPE_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_TBAT_QRY_CNF_STRU
 结构说明  : AT与AT AGENT 查询 TBAT 的消息回复结构

1. 日    期   : 2012年1月13日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulTbatType;

}DRV_AGENT_TBAT_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_RXPRI_QRY_CNF_STRU
 结构说明  : DRV与AT AGENT  获取驱动支持的RX分集

1. 日    期   : 2011年10月22日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                      stAtAppCtrl;
    VOS_UINT16                           usWDrvPriBands;
    VOS_UINT16                           usGDrvPriBands;
    VOS_BOOL                             bFail;
}DRV_AGENT_RXPRI_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_ADC_SET_REQ_STRU
 结构说明  : AT与DRV AGENT 设置 ADC 的消息请求结构

1. 日    期   : 2011年11月5日
   作    者   : w00181244
   修改内容   : 从monitorps.h中移植过来
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulIsEnable;           /*是否需要启动保护机制, 0为关闭，1为开启*/
    VOS_INT32                   lCloseAdcThreshold;   /*进入低功耗模式的温度门限*/
    VOS_INT32                   lAlarmAdcThreshold;   /*需要进行给出警报的温度门限*/
    VOS_INT32                   lResumeAdcThreshold;  /*恢复到正常模式的温度门限*/
}SPY_TEMP_THRESHOLD_PARA_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_ADC_SET_CNF_STRU
 结构说明  : AT与DRV AGENT 设置 RXPRI 的消息回复结构

1. 日    期   : 2011年10月15日
   作    者   : w00181244
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                        stAtAppCtrl;
    VOS_BOOL                               bFail;

}DRV_AGENT_ADC_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_VERSION_TIME_STRU
 结构说明  : AT与AT AGENT版本查询与控制结构

  1.日    期   : 2011年10月15日
    作    者   : o00132663
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucReserved[2];
    VOS_CHAR                            aucData[AT_AGENT_DRV_VERSION_TIME_LEN+1];
} DRV_AGENT_VERSION_TIME_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_YJCX_SET_CNF_STRU
 结构说明  : AT与AT AGENT AT^YJCX设置命令回复结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    VOS_UCHAR                           aucflashInfo[TAF_MAX_FLAFH_INFO_LEN + 1];
} DRV_AGENT_YJCX_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_YJCX_QRY_CNF_STRU
 结构说明  : AT与AT AGENT AT^YJCX设置命令回复结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    VOS_UCHAR                           aucgpioInfo[TAF_MAX_GPIO_INFO_LEN + 1];
    VOS_UINT8                           aucReserved[3];
} DRV_AGENT_YJCX_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_IMSICHG_QRY_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT查询IMSICHG回复结构

1. 日    期   : 2011年11月3日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulCurImsiSign;
    VOS_UINT16                          usDualIMSIEnable;
    VOS_UINT8                           aucReserved[2];
}DRV_AGENT_IMSICHG_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_INFORBU_SET_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT设置INFORBU回复结构

1. 日    期   : 2011年11月3日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_INFORBU_SET_CNF_STRU;

/* Add by h00135900 for V7代码同步, 2012-04-07, Begin   */
/*****************************************************************************
 结构名    : DRV_AGENT_INFORRS_SET_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT设置INFORRU回复结构

1. 日    期   : 2012年04月11日
   作    者   : H00135900
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_INFORRS_SET_CNF_STRU;

/* Add by h00135900 for V7代码同步, 2012-04-07, End   */

/*****************************************************************************
 结构名    : DRV_AGENT_CPNN_TEST_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT CPNN测试命令回复结构

1. 日    期   : 2011年11月3日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bNormalSrvStatus;
    VOS_UINT32                          ulPnnExistFlg;
    VOS_UINT32                          ulOplExistFlg;

}DRV_AGENT_CPNN_TEST_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_CPNN_TEST_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT CPNN测试命令回复结构

1. 日    期   : 2011年11月3日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_NVBACKUP_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_CPNN_QRY_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT CPNN查询命令回复结构

1. 日    期   : 2011年11月3日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bNormalSrvStatus;
}DRV_AGENT_CPNN_QRY_CNF_STRU;

/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  begin */
/*****************************************************************************
 结构名    : DRV_AGENT_MEMINFO_QRY_RSP_STRU
 结构说明  : DRV与TAF AGENT AT^MEMINFO命令回复结构

  1.日    期   : 2011年11月29日
    作    者   : l00171473
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                         stAtAppCtrl;
    VOS_UINT32                              ulResult;
    AT_MEMQUERY_PARA_ENUM_UINT32            ulMemQryType;                       /* 查询的类型，0:VOS内存, 1: TTF内存 */
    VOS_UINT32                              ulPidNum;                           /* PID的个数 */
    VOS_UINT8                               aucData[4];                         /* 每个PID的内存使用情况 */
}DRV_AGENT_MEMINFO_QRY_RSP_STRU;
/* Added by l00171473 for 内存监控AT命令, 2011-11-29,  end */

/*****************************************************************************
 结构名    : DRV_AGENT_TSELRF_SET_CNF_STRU
 结构说明  : DRV与TAF DRV AGENT TSELRF设置命令回复结构

1. 日    期   : 20112年01月10日
   作    者   : f62575
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                         stAtAppCtrl;
    DRV_AGENT_TSELRF_SET_ERROR_ENUM_UINT32  enResult;
    VOS_UINT8                               ucDeviceRatMode;
    VOS_UINT8                               aucReserved[3];
}DRV_AGENT_TSELRF_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_HKADC_GET_CNF_STRU
 结构说明  : AT与DRV AGENT 获取HKADC电压 的消息回复结构

1. 日    期   : 20112年01月10日
   作    者   : f62575
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                             stAtAppCtrl;
    DRV_AGENT_HKADC_GET_ERROR_ENUM_UINT32  enResult;
    VOS_INT32                                                   TbatHkadc;
}DRV_AGENT_HKADC_GET_CNF_STRU;



#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/*****************************************************************************
 结构名    : DRV_AGENT_SPWORD_SET_REQ_STRU
 结构说明  : AT与DRV AGENT 获取SPWORD的消息请求结构

1. 日    期   : 2012年02月21日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acShellPwd[AT_SHELL_PWD_LEN];
}DRV_AGENT_SPWORD_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SPWORD_SET_CNF_STRU
 结构说明  : AT与DRV AGENT 获取SPWORD的消息回复结构

1. 日    期   : 2012年02月21日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}DRV_AGENT_SPWORD_SET_CNF_STRU;
#endif

/*****************************************************************************
 结构名    : DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询NV备份状态信息消息回复结构
 1.日    期   : 2012年02月16日
   作    者   : l00198894
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /* 消息头 */
    VOS_UINT32                          ulResult;                               /* 返回结果 */
    VOS_UINT32                          ulNvBackupStat;                         /* NV备份状态 */
}DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_NANDBBC_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询NAND FLASH的所有坏块索引列表消息回复结构
 1.日    期   : 2012年02月16日
   作    者   : l00198894
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /* 消息头 */
    VOS_UINT32                          ulResult;                               /* 返回结果 */
    VOS_UINT32                          ulBadBlockNum;                          /* 坏块总数 */
    VOS_UINT32                          aulBadBlockIndex[0];                    /* 坏块索引表 */
} DRV_AGENT_NANDBBC_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_NAND_DEV_INFO_STRU
 结构说明  : AT与DRV AGENT查询NAND FLASH的设备信息消息回复结构
 1.日    期   : 2012年02月16日
   作    者   : l00198894
   修改内容   : 新增结构
*****************************************************************************/
#define DRV_AGENT_NAND_MFU_NAME_MAX_LEN     16                                  /* 厂商名称最大长度 */
#define DRV_AGENT_NAND_DEV_SPEC_MAX_LEN     32                                  /* 设备规格最大长度 */

typedef struct
{
    VOS_UINT32      ulMufId;                                                    /* 厂商ID */
    VOS_UINT8       aucMufName[DRV_AGENT_NAND_MFU_NAME_MAX_LEN];                /* 厂商名称字符串 */
    VOS_UINT32      ulDevId;                                                    /* 设备ID */
    VOS_UINT8       aucDevSpec[DRV_AGENT_NAND_DEV_SPEC_MAX_LEN];                /* 设备规格字符串 */
} DRV_AGENT_NAND_DEV_INFO_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_NANDVER_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询NAND FLASH的型号信息消息回复结构
 1.日    期   : 2012年02月16日
   作    者   : l00198894
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* 消息头 */
    VOS_UINT32                          ulResult;                    /* 返回结果 */
    DRV_AGENT_NAND_DEV_INFO_STRU        stNandDevInfo;               /* 设备信息 */
} DRV_AGENT_NANDVER_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_CHIPTEMP_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询PA、SIM卡和电池的温度信息消息回复结构
 1.日    期   : 2012年02月16日
   作    者   : l00198894
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* 消息头 */
    VOS_UINT32                          ulResult;                    /* 返回结果 */
    VOS_INT                             lGpaTemp;                    /* G PA温度 */
    VOS_INT                             lWpaTemp;                    /* W PA温度 */
    VOS_INT                             lLpaTemp;                    /* L PA温度 */
    VOS_INT                             lSimTemp;                    /* SIM卡温度 */
    VOS_INT                             lBatTemp;                    /* 电池温度 */
} DRV_AGENT_CHIPTEMP_QRY_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_ANTSWITCH_SET_STRU
 结构说明  : AT与DRV AGENT设置天线信息
 1.日    期   : 2013年11月11日
   作    者   : y00258578
   修改内容   : 新增结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulState;                    /* 设置状态 */

} DRV_AGENT_ANTSWITCH_SET_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_ANTSWITCH_SET_CNF_STRU
 结构说明  : AT与DRV AGENT设置天线应答信息
 1.日    期   : 2013年11月11日
   作    者   : y00258578
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* 消息头 */
    VOS_UINT32                          ulResult;                    /* 返回结果 */

} DRV_AGENT_ANTSWITCH_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_ANTSWITCH_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询天线应答信息
 1.日    期   : 2013年11月11日
   作    者   : y00258578
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* 消息头 */
    VOS_UINT32                          ulState;                     /* 天线状态 */
    VOS_UINT32                          ulResult;                    /* 返回结果 */

} DRV_AGENT_ANTSWITCH_QRY_CNF_STRU;



/*****************************************************************************
 结构名    : DRV_AGENT_ANT_STATE_IND_STRU
 结构说明  : AT与DRV AGENT 设置ANT STATE IND的消息回复结构

1. 日    期   : 2012年12月25日
   作    者   : l00227485
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* 消息头 */
    VOS_UINT16                          usAntState;
    VOS_UINT8                           aucRsv[2];
} DRV_AGENT_ANT_STATE_IND_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU
 结构说明  : AT与DRV AGENT 设置MAX LOCK TIMES的消息回复结构

1. 日    期   : 2012年03月19日
   作    者   : f00179208
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_AP_SIMST_SET_REQ_STRU
 结构说明  : AT与DRV AGENT设置APSIMST的消息请求结构

1. 日    期   : 2012年06月18日
   作    者   : f00179208
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsimState;
}DRV_AGENT_AP_SIMST_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_AP_SIMST_SET_CNF_STRU
 结构说明  : AT与DRV AGENT 设置APSIMST的消息回复结构

1. 日    期   : 2012年06月18日
   作    者   : f00179208
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}DRV_AGENT_AP_SIMST_SET_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_HUK_SET_REQ_STRU
 结构说明  : AT与DRV AGENT设置HUK的消息请求结构

  1.日    期   : 2012年04月07日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucHUK[DRV_AGENT_HUK_LEN];  /* HUK码流 128Bits */
}DRV_AGENT_HUK_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_HUK_SET_CNF_STRU
 结构说明  : AT与DRV AGENT设置HUK的消息回复结构

  1.日    期   : 2012年04月07日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_HUK_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU
 结构说明  : AT与DRV AGENT设置鉴权公钥的消息请求结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    /* 鉴权公钥码流 */
    VOS_UINT8                           aucPubKey[DRV_AGENT_PUBKEY_LEN];
    /* 鉴权公钥SSK签名码流 */
    VOS_UINT8                           aucPubKeySign[DRV_AGENT_PUBKEY_SIGNATURE_LEN];
}DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU
 结构说明  : AT与DRV AGENT设置鉴权公钥的消息回复结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU
 结构说明  : AT与DRV AGENT发起产线鉴权的消息回复结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
    /* 使用公钥进行RSA加密后的密文 */
    VOS_UINT8                                       aucRsaText[DRV_AGENT_RSA_CIPHERTEXT_LEN];
}DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_IDENTIFYEND_SET_REQ_STRU
 结构说明  : AT与DRV AGENT完成产线鉴权的消息请求结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    /* 使用私钥进行RSA加密后的密文 */
    VOS_UINT8                           aucRsaText[DRV_AGENT_RSA_CIPHERTEXT_LEN];
}DRV_AGENT_IDENTIFYEND_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_IDENTIFYEND_SET_CNF_STRU
 结构说明  : AT与DRV AGENT完成产线鉴权的消息回复结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_IDENTIFYEND_SET_CNF_STRU;

/*****************************************************************************
结构名    : DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU
结构说明  : AT与DRV AGENT设置锁网锁卡信息的消息请求结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    /* 结构体码流, 包含该锁网锁卡类型的包括状态, 锁网号段, CK, UK等所有信息 */
    VOS_UINT8       aucCategoryData[DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN];
}DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU
 结构说明  : AT与DRV AGENT设置锁网锁卡信息的消息回复结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU;

/*****************************************************************************
结构名    : DRV_AGENT_PH_LOCK_CODE_STRU
结构说明  : 锁网锁卡号段结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
   VOS_UINT8        aucPhLockCodeBegin[DRV_AGENT_PH_LOCK_CODE_LEN];
   VOS_UINT8        aucPhLockCodeEnd[DRV_AGENT_PH_LOCK_CODE_LEN];
}DRV_AGENT_PH_LOCK_CODE_STRU;

/*****************************************************************************
结构名    : DRV_AGENT_SIMLOCK_DATA_CATEGORY_STRU
结构说明  : 锁网锁卡安全数据单个类型的数据结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8           enCategory;             /* 锁网锁卡的category类别 */
    DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM_UINT8          enIndicator;            /* 锁网锁卡的激活指示 */
    DRV_AGENT_PERSONALIZATION_STATUS_ENUM_UINT8             enStatus;
    VOS_UINT8                                               ucMaxUnlockTimes;       /* 锁网锁卡的最大解锁次数 */
    VOS_UINT8                                               ucRemainUnlockTimes;    /* 锁网锁卡的剩余解锁次数 */
    VOS_UINT8                                               aucRsv[3];              /* 保留字节，用于四字节对齐 */
}DRV_AGENT_SIMLOCK_DATA_CATEGORY_STRU;

/*****************************************************************************
结构名    : DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU
结构说明  : AT与DRV AGENT查询锁网锁卡安全数据的消息回复结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
    /* 目前支持3种category，结构体数组按照network->network subset->SP的顺序排列 */
    DRV_AGENT_SIMLOCK_DATA_CATEGORY_STRU            astCategoryData[DRV_AGENT_SUPPORT_CATEGORY_NUM];
}DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU;

/*****************************************************************************
结构名    : DRV_AGENT_SIMLOCK_INFO_CATEGORY_STRU
结构说明  : 锁网锁卡信息单个类型的数据结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8           enCategory;             /* 锁网锁卡的category类别 */
    DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM_UINT8          enIndicator;            /* 锁网锁卡的激活指示 */
    VOS_UINT8                                               ucGroupNum;             /* 号段个数，一个begin/end算一个号段 */
    VOS_UINT8                                               ucRsv;                  /* 4字节对齐, 保留位 */
    /* 锁网锁卡的号段内容*/
    DRV_AGENT_PH_LOCK_CODE_STRU                             astLockCode[DRV_AGENT_PH_LOCK_CODE_GROUP_NUM];
}DRV_AGENT_SIMLOCK_INFO_CATEGORY_STRU;

/*****************************************************************************
结构名    : DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU
结构说明  : AT与DRV AGENT查询锁网锁卡信息的消息回复结构

  1.日    期   : 2012年04月09日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
    /* 目前支持3种category，结构体数组按照network->network subset->SP的顺序排列 */
    DRV_AGENT_SIMLOCK_INFO_CATEGORY_STRU            astCategoryInfo[DRV_AGENT_SUPPORT_CATEGORY_NUM];
}DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU
 结构说明  : AT与DRV AGENT设置物理号的消息请求结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PH_PHYNUM_TYPE_ENUM_UINT8 enPhynumType;                                   /* 物理号类型 */
    VOS_UINT8                           aucPhynumValue[DRV_AGENT_RSA_CIPHERTEXT_LEN];   /* 物理号RSA密文码流 */
}DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU
 结构说明  : AT与DRV AGENT设置物理号的消息回复结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询物理号的消息回复结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
    VOS_UINT8                                       aucImeiRsa[DRV_AGENT_RSA_CIPHERTEXT_LEN];
    VOS_UINT8                                       aucSnRsa[DRV_AGENT_RSA_CIPHERTEXT_LEN];
}DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU
 结构说明  : AT与DRV AGENT临时打开通信端口的消息请求结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucPortPassword[DRV_AGENT_PORT_PASSWORD_LEN];               /* 通信端口锁密码 */
}DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU
 结构说明  : AT与DRV AGENT临时打开通信端口的消息回复结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU
 结构说明  : AT与DRV AGENT设置通信端口开机初始状态及端口锁密码的消息请求结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PORT_STATUS_ENUM_UINT32   enPortStatus;                                   /* 通信端口状态 */
    VOS_UINT8                           aucPortPassword[DRV_AGENT_RSA_CIPHERTEXT_LEN];  /* 通信端口锁密码 */
}DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU
 结构说明  : AT与DRV AGENT设置通信端口开机初始状态及端口锁密码的消息回复结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU
 结构说明  : AT与DRV AGENT查询通信端口开机初始状态的消息回复结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
    DRV_AGENT_PORT_STATUS_ENUM_UINT32               enPortStatus;               /* 通信端口状态 */
}DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_OPWORD_SET_REQ_STRU
 结构说明  : AT与DRV AGENT获取开关DIAG口和开关SHELL口的权限的消息请求结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucPortPassword[DRV_AGENT_PORT_PASSWORD_LEN];               /* 通信端口锁密码 */
}DRV_AGENT_OPWORD_SET_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_OPWORD_SET_CNF_STRU
 结构说明  : AT与DRV AGENT获取开关DIAG口和开关SHELL口的权限的消息回复结构

  1.日    期   : 2012年04月10日
    作    者   : l00198894
    修改内容   : AP-Modem锁网锁卡项目新增结构

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* 命令执行结果 */
}DRV_AGENT_OPWORD_SET_CNF_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_HVPDH_REQ_STRU
 结构说明  : 产线预制DH秘钥，AT向SC发送秘钥信息所用的数据结构

  1.日    期   : 2013年8月27日
    作    者   : L47619
    修改内容   : V9R1 vSIM项目修改

*****************************************************************************/
typedef struct
{
    DRV_AGENT_DH_KEY_TYPE_ENUM_UINT32   enKeyType;                              /* DH秘钥类型 */
    VOS_UINT32                          ulKeyLen;                               /* DH秘钥长度 */
    VOS_UINT8                           aucKey[DRV_AGENT_DH_PUBLICKEY_LEN];     /* DH秘钥，按最大长度来设置数组，以便用于存储公钥和私钥 */
}DRV_AGENT_HVPDH_REQ_STRU;

/*****************************************************************************
 结构名    : DRV_AGENT_HVPDH_CNF_STRU
 结构说明  : SC向AT返回写入预制DH秘钥的响应结果

  1.日    期   : 2013年8月27日
    作    者   : L47619
    修改内容   : V9R1 vSIM项目修改

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* 消息头 */
    DRV_AGENT_HVPDH_ERR_ENUM_UINT32                 enResult;                   /* 命令执行结果 */
}DRV_AGENT_HVPDH_CNF_STRU;

/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, begin */
/*****************************************************************************
 结构名    : DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU
 结构说明  : AT与TAF DRV AGENT 获取NV强制恢复出厂设置的消息回复结构

1. 日    期   : 2011年11月3日
   作    者   : l60609
   修改内容   : 新增结构体
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU;
/* Added by d00212987 for BalongV9R1 NV备份数据丢失容错&恢复 项目 2013-10-24, end */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    DRV_AGENT_MSG_TYPE_ENUM_UINT32      ulMsgId;   /*_H2ASN_MsgChoice_Export DRV_AGENT_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          DRV_AGENT_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}DRV_AGENT_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    DRV_AGENT_MSG_DATA                  stMsgData;
}TafDrvAgent_MSG;


/*****************************************************************************
 结构名    : DRV_AGENT_SWVER_INFO_STRU
 结构说明  : 平台软件版本号
 1.日    期   : 2012年11月24日
   作    者   : s00190137
   修改内容   : 手机产品查询modem版本号接口新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSWVer[TAF_MAX_REVISION_ID_LEN + 1];
    VOS_CHAR                            acVerTime[AT_AGENT_DRV_VERSION_TIME_LEN];
}DRV_AGENT_SWVER_INFO_STRU;


/*****************************************************************************
 结构名    : DRV_AGENT_SWVER_SET_CNF_STRU
 结构说明  : AT与AT AGENT 查询SWVER信息消息回复结构
 1.日    期   : 2012年11月24日
   作    者   : s00190137
   修改内容   : 手机产品查询modem版本号接口新增结构
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                       stAtAppCtrl;
    DRV_AGENT_ERROR_ENUM_UINT32           enResult;
    DRV_AGENT_SWVER_INFO_STRU             stSwverInfo;
} DRV_AGENT_SWVER_SET_CNF_STRU;



/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT32   GAS_AtCmd(GAS_AT_CMD_STRU *pstAtCmd,GAS_AT_RSLT_STRU *pstAtCmdRslt);

extern VOS_VOID MMA_GetProductionVersion(VOS_CHAR *pcDest);
extern VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd);
extern VOS_UINT32 AT_GetWcdmaBandStr(VOS_UINT8 *pucGsmBandstr, AT_UE_BAND_CAPA_ST *pstBandCapa);
extern VOS_UINT32 AT_GetGsmBandStr(VOS_UINT8 *pucGsmBandstr , AT_UE_BAND_CAPA_ST *pstBandCapa);
extern VOS_UINT32 At_SendRfCfgAntSelToHPA(VOS_UINT8 ucDivOrPriOn);
extern VOS_UINT32 At_DelCtlAndBlankCharWithEndPadding(VOS_UINT8 *pucData, VOS_UINT16  *pusCmdLen);
extern VOS_UINT32 Spy_SetTempPara(SPY_TEMP_THRESHOLD_PARA_STRU *stTempPara);

/* Add by w00184875 For L降SAR begin */
#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID L_ExtSarPowerReductionPRI(VOS_UINT32 para);
#endif
/* Add by w00184875 For L降SAR end */


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

#endif /* end of TafDrvAgent.h */
