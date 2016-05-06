/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ScApSec.h
  版 本 号   : 初稿
  作    者   : 胡骏
  生成日期   : 2012年8月27日
  最近修改   :
  功能描述   : SC模块
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
******************************************************************************/

#ifndef __SCAPSEC_H__
#define __SCAPSEC_H__

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
#include "ScCommCtx.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define SC_SECURITY_ITEM_LENGTH_SIZE                        (4)                 /* 安全存储项长度字段大小 */
#define SC_SECURITY_ITEM_CONTENT_SIZE                       (256)               /* 安全存储项内容字段大小 */
#define SC_SECURITY_ITEM_HASH_SIZE                          (32)                /* 安全存储项HASH字段大小 */
#define SC_SECURITY_ITEM_PADDING_SIZE                       (12)                /* 安全存储固定填充字段大小 */
#define SC_SECURITY_ITEM_TOTAL_SIZE                         (SC_SECURITY_ITEM_LENGTH_SIZE\
                                                            + SC_SECURITY_ITEM_CONTENT_SIZE\
                                                            + SC_SECURITY_ITEM_HASH_SIZE\
                                                            + SC_SECURITY_ITEM_PADDING_SIZE) /* 安全存储项总大小 */

#define SC_SECURITY_ITEM_PADDING_VALUE                      (0xC)               /* 安全存储固定填充内容 */

#define SC_APSEC_SP_MAX_DATA_LEN                            (266)               /* 安全封包数据段最大长度 */
#define SC_AES_TEXT_MIN_LEN                                 (16)                /* AES加解密算法文本最小字节数 */
#define SC_APSEC_SP_MAJOR_VERSION                           (1)                 /* 安全封包主命令版本 */
#define SC_APSEC_SP_MAJOR_SECSTORE                          (1)                 /* 安全封包主命令类型安全存储 */
#define SC_APSEC_SP_MAJOR_AT_KEY                            (0xD0)              /* 安全封包主命设置安全AT key */
#define SC_APSEC_SP_MINOR_VERSION                           (1)                 /* 安全封包次命令版本 */
#define SC_APSEC_SP_MINOR_AT_KEY                            (0x90)              /* 安全封包次命设置安全AT key */
#define SC_APSEC_SP_MINOR_READ                              (1)                 /* 安全封包次命读安全数据项 */
#define SC_APSEC_SP_MINOR_WRITE                             (2)                 /* 安全封包次命写安全数据项 */
#define SC_APSEC_SP_FLAG_REQ                                (1)                 /* AP下发请求安全封包中的标志位 */
#define SC_APSEC_SP_FLAG_CNF                                (2)                 /* Modem回复安全封包中的标志位 */
#define SC_APSEC_SP_FLAG_AT_KEY                             (0x40)              /* AP设置安全AT key安全封包中的标志位 */
#define SC_APSEC_SP_FLAG_ATSEC_REQ_AT_KEY                   (1)                 /* 安全封包标志位请求安全AT key */
#define SC_APSEC_SP_FLAG_ATSEC_SEQID_ERR                    (4)                 /* 安全封包标志位请求安全AT key */
#define SC_APSEC_SP_FLAG_ATSEC_PARA_ERR                     (5)                 /* 安全封包标志位请求安全AT key */
#define SC_APSEC_SP_FLAG_RLT_SUCCESS                        (0)                 /* 安全封包标志位返回处理成功 */
#define SC_APSEC_SP_FLAG_RLT_PARAERR                        (5)                 /* 安全封包标志位返回参数错误 */
#define SC_APSEC_SP_FLAG_RLT_DUALBACK_FAILED                (6)                 /* 安全封包标志位返回双备份失败 */
#define SC_APSEC_SP_SEQID_MIN_VALUE                         (0x01)              /* 安全封包中SeqID的最小值 */
#define SC_APSEC_SP_SEQID_MAX_VALUE                         (0xFF)              /* 安全封包中SeqID的最大值 */
#define SC_APSEC_SP_SEQID_AT_KEY                            (0x00)              /* 设置安全AT key时安全封包中SeqID的值 */
#define SC_APSEC_SP_RANDOM_LEN                              (16)                /* AP下发的随机数长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : SC_APSEC_ITME_ENUM
 枚举说明  : 指定安全数据项的类型

  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
enum SC_APSEC_ITME_ENUM
{
    SC_APSEC_ITME_UE_IMEI_I             =   0,              /* IMEI */
    SC_APSEC_ITME_MMB_KL_TEMP           =   1,              /* Temporary license key */
    SC_APSEC_ITME_MMB_KL_REAL           =   2,              /* Usually license key */
    SC_APSEC_ITME_MMB_CASID             =   3,              /* CA system ID */
    SC_APSEC_ITME_MMB_ME_PUBKEY         =   4,              /* Public key */
    SC_APSEC_ITME_MMB_ME_PRIVKEY        =   5,              /* Private key */
    SC_APSEC_ITME_MMB_ME_SIGNATURE      =   6,              /* signature */
    SC_APSEC_ITME_MMB_SEC_SRV_STAT      =   7,              /* secure clock state */
    SC_APSEC_ITME_MMB_SEC_NITZ          =   8,              /* Broadcast clock */
    SC_APSEC_ITME_MMB_SEC_RTC           =   9,              /* RTC */
    SC_APSEC_ITME_MMB_NUM               =  10,              /* 保留1 */
    SC_APSEC_ITME_MMB_RESERVED2         =  11,              /* 保留2 */
    SC_APSEC_ITME_MMB_RESERVED3         =  12,              /* 保留3 */
    SC_APSEC_ITME_MMB_RESERVED4         =  13,              /* 保留4 */
    SC_APSEC_ITME_MMB_RESERVED5         =  14,              /* 保留5 */
    SC_APSEC_ITME_MMB_RESERVED6         =  15,              /* 保留6 */
    SC_APSEC_ITEM_MMB_BUTT,
};
typedef VOS_UINT32 SC_APSEC_ITME_ENUM_UINT32;


/*****************************************************************************
 枚举名    : SC_APSEC_SP_RESULT_ENUM
 枚举说明  : 安全封包处理结果枚举值

  1.日    期   : 2012年9月12日
    作    者   : l00198894
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
enum SC_APSEC_SP_RESULT_ENUM
{
    SC_APSEC_SP_OK                      =   0,              /* 安全封包OK */
    SC_APSEC_SP_NO_SATK                 =   1,              /* 安全封包无安全AT key */
    SC_APSEC_SP_PADDING_ERR             =   2,              /* 安全封包PADDING位错误 */
    SC_APSEC_SP_SEQID_ERR               =   3,              /* 安全封包SeqID校验失败 */
    SC_APSEC_SP_PARA_ERR                =   4,              /* 安全封包字段参数错误 */
    SC_APSEC_SP_ERROR,                                      /* 安全封包存在其他异常 */
};
typedef VOS_UINT32 SC_APSEC_SP_RESULT_ENUM_UINT32;


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
 结构名    : SC_APSEC_SECTURE_ITEM_STRU
 枚举说明  : 安全存储项读取写入项结构

  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
typedef struct
{
    SC_APSEC_ITME_ENUM_UINT32           enItemId;
    VOS_UINT32                          ulItemLen;
    VOS_UINT8                          *pucContent;
}SC_APSEC_SECTURE_ITEM_STRU;

/*****************************************************************************
 结构名    : SC_APSEC_SECTURE_ITEM_STRU
 枚举说明  : 安全存储项读取写入项结构

  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucEncryptContent[SC_SECURITY_ITEM_TOTAL_SIZE];
}SC_APSEC_ENCRYPT_STRU;

/*****************************************************************************
 结构名    : SC_APSEC_DEFAULT_ITEM_STRU
 枚举说明  : 安全存储项默认结构

  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulItemLen;
    VOS_UINT8                           aucContent[SC_SECURITY_ITEM_CONTENT_SIZE];
    VOS_UINT8                           aucHash[SC_SECURITY_ITEM_HASH_SIZE];
}SC_APSEC_DEFAULT_ITEM_STRU;

/*****************************************************************************
 结构名    : SC_APSEC_SP_HEADER_STRU
 结构说明  : 安全存储特性安全封包包头结构体

 1.日    期   : 2012年08月24日
   作    者   : l00198894
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSeqID;
    VOS_UINT8                           ucMajorCMD;
    VOS_UINT8                           ucMinorCMD;
    VOS_UINT8                           ucFlag;
} SC_APSEC_SP_HEADER_STRU;

/*****************************************************************************
 结构名    : SC_APSEC_SP_MAJOR_CMD_STRU
 结构说明  : 安全存储特性安全封包中主命令结构体

 1.日    期   : 2012年08月24日
   作    者   : l00198894
   修改内容   : 新建

*****************************************************************************/
/*lint -e46*/
typedef struct
{
    VOS_UINT8                           ucReserved  :4;
    VOS_UINT8                           ucVer       :2;
    VOS_UINT8                           ucType      :2;
} SC_APSEC_SP_MAJOR_CMD_STRU;
/*lint +e46*/
/*****************************************************************************
 结构名    : SC_APSEC_SP_MINOR_CMD_STRU
 结构说明  : 安全存储特性安全封包中次命令结构体

 1.日    期   : 2012年08月24日
   作    者   : l00198894
   修改内容   : 新建

*****************************************************************************/
/*lint -e46*/
typedef struct
{
    VOS_UINT8                           ucSecItem   :4;
    VOS_UINT8                           ucVer       :2;
    VOS_UINT8                           ucType      :2;
} SC_APSEC_SP_MINOR_CMD_STRU;
/*lint +e46*/
/*****************************************************************************
 结构名    : SC_APSEC_SP_FLAG_STRU
 结构说明  : 安全存储特性安全封包中命令标志结构体

 1.日    期   : 2012年08月24日
   作    者   : l00198894
   修改内容   : 新建

*****************************************************************************/
/*lint -e46*/
typedef struct
{
    VOS_UINT8                           ucResult    :3;
    VOS_UINT8                           ucAtSec     :3;
    VOS_UINT8                           ucType      :2;
} SC_APSEC_SP_FLAG_STRU;
/*lint +e46*/
/*****************************************************************************
 结构名    : SC_APSEC_SECURE_PACKET_STRU
 结构说明  : 安全存储特性安全封包结构体

 1.日    期   : 2012年08月24日
   作    者   : l00198894
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    SC_APSEC_SP_HEADER_STRU             stHeader;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[SC_APSEC_SP_MAX_DATA_LEN];
} SC_APSEC_SECURE_PACKET_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/


/*****************************************************************************
 函 数 名  : SC_APSEC_GetFileInitState
 功能描述  : 获取双备份文件初始化状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_GetFileInitState(VOS_VOID);

/*****************************************************************************
 函 数 名  : SC_APSEC_SetFileInitState
 功能描述  : 设置双备份文件初始化状态
 输入参数  : ulState:双备份文件初始化状态
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_VOID  SC_APSEC_SetFileInitState(SC_APSEC_FILE_STATE_INIT_ENUM_UINT32 ulState);

/*****************************************************************************
 函 数 名  : SC_APSEC_EncryptItem
 功能描述  : 安全存储项更新接口
 输入参数  : pucSrc: 未加密数据
             ulItemLen: item的长度
 输出参数  : pucDest:加密后密文
 返 回 值  : VOS_UINT32
 修改历史      :
  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_EncryptItem(
    VOS_UINT32                          ulItemLen,
    const VOS_CHAR                     *pucSrc,
    VOS_CHAR                           *pucDest);

/*****************************************************************************
 函 数 名  : SC_APSEC_UpdateSecItem
 功能描述  : 安全存储项更新接口
 输入参数  : pstSecItem: 需要更新的安全存储项内容
             enSecItemId:安全存储项ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 修改历史      :
  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_UpdateSecItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem);

/*****************************************************************************
 函 数 名  : SC_APSEC_ReadEncryptFile
 功能描述  : 备份加密文件读取到内存中
 输入参数  : pucFile:文件路径
 输出参数  : ppstEncryptFile:文件内容在内存中保存的地址
 返 回 值  : 加密文件在内存中的地址
 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern SC_APSEC_ENCRYPT_STRU*  SC_APSEC_ReadEncryptFile(VOS_CHAR *pucFile);

/*****************************************************************************
 函 数 名  : SC_APSEC_ReadEncryptItem
 功能描述  : 双备份文件加密存储项读取，完成HASH检验并解密
 输入参数  : enSecItemId:安全存储项ID
             pstFileContent:安全存储文件原始数据

 输出参数  : pstSecItem:解密后的安全存储项
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_ReadEncryptItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_ENCRYPT_STRU              *pstFileContent,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem);


/*****************************************************************************
 函 数 名  : SC_APSEC_InitDualBackFile
 功能描述  : 双备份文件解密后的数据初始化到内存中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_InitDualBackFile(VOS_VOID);

/*****************************************************************************
 函 数 名  : SC_APSEC_GetFileSyncFlg
 功能描述  : 双备份文件重同步标记获取函数
 输入参数  : enSecItemId:安全存储项
             pstEncryptFileA:指向加密文件A中安全存储项的指针
             pstEncryptFileC:指向加密文件C中安全存储项的指针
 输出参数  : pstSecItemA:加密文件A解密后得到的安全存储项
             pstSecItemC:加密文件C解密后得到的安全存储项
             pulFileSyncFlgA:文件A需要重同步的标记
             pulFileSyncFlgC:文件C需要重同步的标记
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年9月3日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_VOID    SC_APSEC_GetFileSyncFlg(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFileA,
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFileC,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItemA,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItemC,
    VOS_UINT32                         *pulFileSyncFlgA,
    VOS_UINT32                         *pulFileSyncFlgC);

/*****************************************************************************
 函 数 名  : SC_APSEC_ResyncFile
 功能描述  : 双备份文件重同步处理函数
 输入参数  : ulSyncFileFlg:双备份文件重同步标记
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年9月3日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32 SC_APSEC_ResyncFile(VOS_UINT32 ulSyncFileFlg);

/*****************************************************************************
 函 数 名  : SC_APSEC_ReadSecItem
 功能描述  : 安全存储荐读取
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_ReadSecItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem);

/*****************************************************************************
 函 数 名  : SC_APSEC_FreshDualBackFile
 功能描述  : 安全存储双备份文件刷新
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
extern VOS_UINT32  SC_APSEC_FreshDualBackFile(VOS_VOID);

/*****************************************************************************
 函 数 名  : SC_APSEC_IncrementSeqID
 功能描述  : 本地全局变量中的SeqID自增1
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_VOID SC_APSEC_IncrementSeqID( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_APSEC_RegressSeqID
 功能描述  : 复原本地全局变量中的SeqID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_VOID SC_APSEC_RegressSeqID( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_APSEC_GenerateSecATkey
 功能描述  : 完成生成安全AT key功能
 输入参数  : VOS_UINT32    *pulSPLen
             VOS_UINT8     *pucSecPacket
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 SC_APSEC_GenerateSecATkey(
    VOS_UINT32                         *pulSPLen,
    VOS_UINT8                          *pucSecPacket );

/*****************************************************************************
 函 数 名  : SC_APSEC_DecryptSecPacket
 功能描述  : 使用AES-ECB算法解密安全封包
 输入参数  : VOS_UINT8     *pucCipherSP     -- 安全封包密文
             VOS_UINT32     ulCipherSPLen   -- 安全封包密文长度
 输出参数  : SC_APSEC_SECURE_PACKET_STRU   *pstSecPacket    -- 解密后的安全封包
 返 回 值  : SC_APSEC_DECRYPT_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
SC_APSEC_SP_RESULT_ENUM_UINT32 SC_APSEC_DecryptSecPacket(
    VOS_UINT8                          *pucCipherSP,
    VOS_UINT32                          ulCipherSPLen,
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket );

/*****************************************************************************
 函 数 名  : SC_APSEC_CheckSecPacket
 功能描述  : 检查安全封包校验位
 输入参数  : pstSecPacket   -- 待校验的安全封包
 输出参数  : 无
 返 回 值  : SC_APSEC_SP_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
SC_APSEC_SP_RESULT_ENUM_UINT32 SC_APSEC_CheckSecPacket(
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket );

/*****************************************************************************
 函 数 名  : SC_APSEC_EncryptSecPacket
 功能描述  : 使用AES-ECB算法加密安全封包
 输入参数  : SC_APSEC_SECURE_PACKET_STRU   *pstSecPacket    -- 待加密的安全封包
 输出参数  : VOS_UINT8     *pucCipherSP     -- 安全封包密文
             VOS_UINT32    *ulCipherSPLen   -- 安全封包密文长度
 返 回 值  : VOS_UINT32
                VOS_OK  : 解密成功
                VOS_ERR : 解密失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 SC_APSEC_EncryptSecPacket(
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket,
    VOS_UINT8                          *pucCipherSP,
    VOS_UINT32                         *pulCipherSPLen);

/*****************************************************************************
 函 数 名  : SC_APSEC_CreateSecPacket
 功能描述  : 根据结果值填写回复安全封包
 输入参数  : enResult                   -- 安全封包处理结果值
             pstSecPacket               -- 源安全封包
 输出参数  : VOS_UINT8  *pucSecPacket   -- 回复安全封包二进制码流
             VOS_UINT32 *pulSPLen       -- 回复安全封包长度字节数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 SC_APSEC_CreateSecPacket(
    SC_APSEC_SP_RESULT_ENUM_UINT32      enResult,
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket,
    VOS_UINT8                          *pucSecPacket,
    VOS_UINT32                         *pulSPLen );

/*****************************************************************************
 函 数 名  : SC_APSEC_DealSecureStorage
 功能描述  : 处理安全存储命令
 输入参数  : SC_APSEC_SECURE_PACKET_STRU  *pstSecPacket -- 待处理的安全封包
 输出参数  : SC_APSEC_SECURE_PACKET_STRU  *pstSecPacket -- 处理完成的安全封包
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_VOID SC_APSEC_DealSecureStorage(
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket );

/*****************************************************************************
 函 数 名  : SC_APSEC_GetDefaultSecItem
 功能描述  : 获取安全项默认值
 输入参数  : SC_APSEC_ITME_ENUM_UINT32   enSecItemId    -- 安全项ID
 输出参数  : SC_APSEC_DEFAULT_ITEM_STRU *pstSecItem     -- 安全项默认值
 返 回 值  : VOS_OK     -- 安全项默认值获取成功
             VOS_ERR    -- 安全项默认值获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT32 SC_APSEC_GetDefaultSecItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem);

/*****************************************************************************
 函 数 名  : SC_APSEC_GetSecItemDefaultTbl
 功能描述  : 获取安全项默认值表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC_APSEC_SECTURE_ITEM_STRU     -- 安全项默认值表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月05日
    作    者   : l00198894
    修改内容   : DTS2013010400039: ISDB安全存储增加NV项，控制默认值版本

*****************************************************************************/
extern SC_APSEC_SECTURE_ITEM_STRU* SC_APSEC_GetSecItemDefaultTbl(VOS_VOID);

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

