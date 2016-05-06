

/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ScComm.h
  版 本 号   : 初稿
  作    者   : 王笑非
  生成日期   : 2012年4月16日
  最近修改   :
  功能描述   : SC模块
  函数列表   :
  修改历史   :
  1.日    期   : 2012年4月16日
    作    者   : w00184875
    修改内容   : V7R1C51 锁网锁卡项目新增

******************************************************************************/

#ifndef __SCCOMM_H__
#define __SCCOMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "ScInterface.h"
#include "UsimPsInterface.h"
#include "msp_diag_comm.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define   SC_KEY_LEN                (32)                                        /* 密钥的长度 */

#define   SC_HASH_LEN               (32)                                        /* HASH的码流长度 */

#define   SC_FILE_PATH_LEN          (128)

#define   SC_SSK_STRING             "Secure Storage Key"                        /* 生成SSK的字符串 */

#define   SC_SSK_STRLEN             (VOS_StrLen(SC_SSK_STRING))                 /* 生成SSK的字符串长度 */

#define   SC_DSSK_STRING            "Debug port protect Secure Storage Key"     /* 生成DSSK的字符串 */

#define   SC_DSSK_STRLEN            (VOS_StrLen(SC_DSSK_STRING))                /* 生成DSSK的字符串长度 */

#define   SC_IPK_STRING             "Integrity Protection Key"                  /* 生成IPK的字符串 */

#define   SC_IPK_STRLEN             (VOS_StrLen(SC_IPK_STRING))                 /* 生成IPK的字符串长度 */

#define   SC_ASSK_STRING            "AT Secure Storage Key"                     /* 生成ASSK的字符串 */

#define   SC_ASSK_STRLEN            (VOS_StrLen(SC_ASSK_STRING))                /* 生成ASSK的字符串长度 */

#define   SC_SATK_STRING            "Secure AT Key"                             /* 生成SATK的字符串 */

#define   SC_SATK_STRLEN            (VOS_StrLen(SC_SATK_STRING))                /* 生成SATK的字符串长度 */

#define   SC_FILE_EXIST_MAGIC       (0x37ab65cd)                                /* SC备份文件存在标记 */

#define   SC_FILE_PACKET_MAGIC      (0xdeacb589)                                /* SC备份区存在标记 */

#define   SC_LOG_MAX_LEN            (512)

#define   SC_LOG_FILE_MAX_SIZE      (SC_LOG_MAX_LEN * 100)    /* the max size of log file. */

#define   SC_FILE_SEEK_END          (2)

#define   SC_FILE_SEEK_SET          (0)

#define   SC_FILE_EXIST_OK          (0)

#if ((OSA_CPU_CCPU == VOS_OSA_CPU))
#define SC_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(MAPS_PB_PID), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define   SC_NORMAL_LOG(string)                     (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL), MAPS_PB_PID, __FILE__, __LINE__, "%s", string);\
                                                    SC_Printf("%s.\r\n", string)

#define   SC_NORMAL_ASCII_LOG(string)               (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL), MAPS_PB_PID, __FILE__, __LINE__, "%02x ", string);\
                                                    SC_Printf("%02x ", string)

#define   SC_INFO1_LOG(string, para1)               (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1);\
                                                    SC_Printf("%s %d.\r\n", string, para1)

#define   SC_NORMAL1_LOG(string, para1)             (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1);\
                                                    SC_Printf("%s %d.\r\n", string, para1)

#define   SC_WARNING1_LOG(string, para1)            (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1);\
                                                    SC_Printf("%s %d.\r\n", string, para1)

#define   SC_ERROR_LOG(string)                      (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL), MAPS_PB_PID, __FILE__, __LINE__, "%s", string);\
                                                    SC_Printf("%s \r\n", string)

#define   SC_ERROR1_LOG(string, para1)              (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d", string, para1);\
                                                    SC_Printf("%s %d.\r\n", string, para1)

#define   SC_ERROR2_LOG(string, para1, para2)       (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d,%d", string, para1, para2);\
                                                    SC_Printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define   SC_ERROR_LOG(string)                      SC_Printf(string)
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : SC_KEY_TYPE_ENUM
 枚举说明  : 指定KEY的类型

  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增枚举
*****************************************************************************/
enum SC_KEY_TYPE_ENUM
{
    SC_KEY_TYPE_SSK                     = 0x00,             /* SSK */
    SC_KEY_TYPE_DSSK                    = 0x01,             /* DSSK */
    SC_KEY_TYPE_IPK                     = 0x02,             /* IPK */
    SC_KEY_TYPE_BUTT
};
typedef VOS_UINT8 SC_KEY_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SC_CRYPTO_PASSWORD_TYPE_ENUM
 枚举说明  : 指定密文的类型

  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增枚举
*****************************************************************************/
enum SC_CRYPTO_PASSWORD_TYPE_ENUM
{
    SC_CRYPTO_PASSWORD_TYPE_CK          = 0x00,             /* CK的密文 */
    SC_CRYPTO_PASSWORD_TYPE_DK          = 0x01,             /* DK的密文 */
    SC_CRYPTO_PASSWORD_TYPE_BUTT
};
typedef VOS_UINT8 SC_CRYPTO_PASSWORD_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SC_SECRET_FILE_TYPE_ENUM
 结构说明  : 指定安全文件的类型

  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增枚举

*****************************************************************************/
enum SC_SECRET_FILE_TYPE_ENUM
{
    SC_SECRET_FILE_TYPE_CK              = 0x00,             /* CK-FILE */
    SC_SECRET_FILE_TYPE_DK              = 0x01,             /* DK-FILE */
    SC_SECRET_FILE_TYPE_AK              = 0x02,             /* AK-FILE */
    SC_SECRET_FILE_TYPE_PI              = 0x03,             /* PI-FILE */
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
    SC_SECRET_FILE_TYPE_IMEI_I0         = 0x04,             /* IMEI-FILE 卡0 */
    SC_SECRET_FILE_TYPE_IMEI_I1         = 0x05,             /* IMEI-FILE 卡1 */
    SC_SECRET_FILE_TYPE_IMEI_I2         = 0x06,             /* IMEI-FILE 卡2 */
#else
    SC_SECRET_FILE_TYPE_IMEI_I0         = 0x04,             /* IMEI-FILE 卡0 */
    SC_SECRET_FILE_TYPE_IMEI_I1         = 0x05,             /* IMEI-FILE 卡1 */
#endif
#else
    SC_SECRET_FILE_TYPE_IMEI_I0         = 0x04,             /* IMEI-FILE 卡0 */
#endif

    SC_SECRET_FILE_TYPE_BUTT
};
typedef VOS_UINT8 SC_SECRET_FILE_TYPE_ENUM_UINT8;

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
 结构名    : SC_BACKUP_EACH_FILE_INFO_STRU
 结构说明  : SC每个备份文件的明细
 1.日    期   : 2014年07月29日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFileMagicMUM;
    VOS_UINT32                          ulFileLen;
    VOS_UINT32                          ulFileOffset;
    VOS_CHAR                            acFilePath[SC_FILE_PATH_LEN];
}SC_BACKUP_EACH_FILE_INFO_STRU;

/*****************************************************************************
 结构名    : SC_BACKUP_FILE_INFO_STRU
 结构说明  : SC所以文件拼接成一块，统一刷入FLASH
 1.日    期   : 2014年06月10日
   作    者   : d00212987
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulBackMagicMUM;
    VOS_UINT32                         ulTotaleSize;
    SC_BACKUP_EACH_FILE_INFO_STRU      astSCEachFileInfo[SC_SECRET_FILE_TYPE_BUTT*2];
    VOS_CHAR                           aucFileData[4];
}SC_BACKUP_FILE_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if ((OSA_CPU_CCPU == VOS_OSA_CPU))
extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateKey(
    VOS_CHAR                           *pcData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucKey,
    VOS_UINT32                          ulKeyLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadSCFileAndCmpSign(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_WriteSecretFile(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateCryptoPwd(
    SC_CRYPTO_PASSWORD_TYPE_ENUM_UINT8  enPwdType,
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucPwdLen,
    VOS_UINT8                          *pucCryptoPwd,
    VOS_UINT32                          ulCryptoPwdLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_RsaEncrypt(
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                         *pulCipherLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_RsaDecrypt(
    VOS_UINT8                          *pucPwd,
    VOS_UINT32                          ulCipherLen,
    VOS_UINT8                          *pucPubContent,
    VOS_UINT32                         *pulPubLen
);

/*****************************************************************************
 函 数 名  : SC_COMM_GenerateSignCode
 功能描述  : 文件签名的计算
 输入参数  : pucContent: 文件内容
             ucContentLen: 文件内容长度
             ucSignCodeLen: 文件签名长度

 输出参数  : pucSignCode: 文件签名码流

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateSignCode(
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen,
    VOS_UINT8                          *pucSignCode,
    VOS_UINT32                          ulSignCodeLen
);

/*****************************************************************************
 函 数 名  : SC_COMM_WriteFile
 功能描述  : 读取文件接口
 输入参数  : pcFilePath: 文件路径
             ulContentLen: 文件长度

 输出参数  : pucContent: 文件内容

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月18日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_WriteFile(
    VOS_CHAR                           *pcFilePath,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

/*****************************************************************************
 函 数 名  : SC_COMM_ReadFile
 功能描述  : 读取文件接口
 输入参数  : pcFilePath: 文件路径
             ulContentLen: 文件长度

 输出参数  : pucContent: 文件内容

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月18日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadFile(
    VOS_CHAR                           *pcFilePath,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

/*****************************************************************************
 函 数 名  : SC_COMM_GetUsimmCachedFile
 功能描述  : SC模块读取USIMM模块缓存文件封装接口
 输入参数  :enModemID:Modem ID
 输出参数  :pucFilePath:读取的文件ID及路径
            pulDataLen:返回文件的内容长度
            ppucData:返回文件内容的地址
            enAppType:应用类型
 返 回 值  : VOS_OK/VOS_ERR
 修改历史      :
  1.日    期   : 2013年8月15日
    作    者   : h59254
    修改内容   : 初始生成
*****************************************************************************/
extern VOS_UINT32 SC_COMM_GetUsimmCachedFile(
    VOS_CHAR                           *pucFilePath,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    MODEM_ID_ENUM_UINT16                enModemID);

/*****************************************************************************
函 数 名  :SC_COMM_IsUsimServiceAvailable
功能描述  :获取卡服务状态　
输入参数  :enModemID:Modem ID
           enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1.日    期   : 2013年8月15日
  作    者   : h59254
  修改内容   : 初始生成
*****************************************************************************/
extern VOS_UINT32 SC_COMM_IsUsimServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32  enService,
    MODEM_ID_ENUM_UINT16            enModemID);
#endif

#if ((OSA_CPU_ACPU == VOS_OSA_CPU))

/*****************************************************************************
函 数 名  : SC_COMM_Restore
功能描述  : SC文件恢复
输入参数  : 无

输出参数  : 无
返 回 值  : VOS_UINT32

被调函数  :
修订记录  :
1.日    期   : 2015年8月10日
  作    者   : d00212987
  修改内容   : SC备份到底软NV备份的扩展分区
*****************************************************************************/
VOS_UINT32 SC_COMM_Restore(VOS_VOID);

extern VOS_VOID SC_Printf(VOS_CHAR *pcData);

#else
/*lint -e960 */
extern VOS_VOID SC_Printf(const VOS_CHAR *pcformat, ...);
/*lint +e960 */
#endif

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
