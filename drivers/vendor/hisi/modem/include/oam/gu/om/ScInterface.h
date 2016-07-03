



#ifndef __SCINTERFACE_H__
#define __SCINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  1 消息头定义
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define   SC_MAX_SUPPORT_CATEGORY   (3)   /* 支持的锁网锁卡CATEGORY类别数，目前只支持三种:network/network subset/SP */

#define   SC_MAX_CODE_LEN           (4)   /* 号段的最大长度(锁网为3，锁子网为4，锁SP为4，取上限) */

#define   SC_MAX_CODE_NUM           (20)  /* 锁网锁卡号段最大个数 */

#define   SC_AUTH_PUB_KEY_LEN       (520) /* 鉴权公钥长度 */

#define   SC_SIGNATURE_LEN          (32)  /* 签名长度 */

#define   SC_RSA_ENCRYPT_LEN        (128) /* 经过RSA加密后的密文长度 */

#define   SC_CRYPTO_PWD_LEN         (16)  /* 密码的密文长度 */

#define   SC_PERS_PWD_LEN           (16)  /* CK/UK/DK密码的明文长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum SC_ERROR_CODE_ENUM
{
    SC_ERROR_CODE_NO_ERROR = 0,                     /* 操作成功 */
    SC_ERROR_CODE_OPEN_FILE_FAIL,                   /* 打开文件失败 */
    SC_ERROR_CODE_READ_FILE_FAIL,                   /* 读取文件失败 */
    SC_ERROR_CODE_WRITE_FILE_FAIL,                  /* 写入文件失败 */
    SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL,            /* 签名校验失败 */
    SC_ERROR_CODE_DK_INCORRECT,                     /* DK密码不正确 */
    SC_ERROR_CODE_UNLOCK_KEY_INCORRECT,             /* CK/UK密码不正确 */
    SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL,           /* 解锁/UNBLOCK时，状态不正确 */
    SC_ERROR_CODE_RSA_ENCRYPT_FAIL,                 /* RSA加密失败 */
    SC_ERROR_CODE_RSA_DECRYPT_FAIL,                 /* RSA解密失败 */
    SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL,    /* 鉴权公钥的摘要签名校验失败 */
    SC_ERROR_CODE_GET_RAND_NUMBER_FAIL,             /* 获取随机数失败(crypto_rand) */
    SC_ERROR_CODE_IDENTIFY_FAIL,                    /* 产线鉴权失败 */
    SC_ERROR_CODE_IDENTIFY_NOT_FINISH,              /* 还未完成产线鉴权 */
    SC_ERROR_CODE_LOCK_CODE_INVALID,                /* 锁网号段本身取值不正确 */
    SC_ERROR_CODE_CREATE_KEY_FAIL,                  /* 密钥生成失败(create_crypto_key) */
    SC_ERROR_CODE_GENERATE_HASH_FAIL,               /* 生成HASH失败(crypto_hash) */
    SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL,             /* AES ECB算法加密失败(crypto_encrypt) */
    SC_ERROR_CODE_WRITE_HUK_FAIL,                   /* HUK写入错误 */
    SC_ERROR_CODE_ALLOC_MEM_FAIL,                   /* 申请内存失败 */
    SC_ERROR_CODE_PARA_FAIL,                        /* 传入参数错误 */
    SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL,             /* IMEI密文写入文件错误 */
    SC_ERROR_CODE_CMP_IMEI_FAIL,                    /* 比较IMEI字符串失败 */
    SC_ERROR_CODE_MODEM_ID_FAIL,                    /* ModemID 错误 */
    SC_ERROR_CODE_NV_READ_FAIL,                     /* NV读失败 */
    SC_ERROR_CODE_NV_WRITE_FAIL,                    /* NV写失败 */
    SC_ERROR_CODE_SCCONTENT_WRITE_FAIL,             /* SC文件写入备份区失败 */
    SC_ERROR_CODE_SCBACKUP_READ_FAIL,               /* 读取SC备份区失败 */
    SC_ERROR_CODE_MAGNUM_CMP_FAIL,                  /* 比较SC备份区标记失败 */
    SC_ERROR_CODE_SCFILE_RESTORE_FAIL,              /* SC文件写入使用区失败 */
    SC_ERROR_CODE_SC_NO_NEED_RESTORE,               /* SC文件不需要恢复 */
    SC_ERROR_CODE_OTHER_ERROR,                      /* 其他错误 */

    SC_ERROR_CODE_BUTT
};
typedef VOS_UINT32  SC_ERROR_CODE_ENUM_UINT32;


enum SC_PERSONALIZATION_CATEGORY_ENUM
{
    SC_PERSONALIZATION_CATEGORY_NETWORK                     = 0x00, /* category:锁网 */
    SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET              = 0x01, /* category:锁子网 */
    SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER            = 0x02, /* category:锁SP */
    SC_PERSONALIZATION_CATEGORY_CORPORATE                   = 0x03, /* category:锁团体 */
    SC_PERSONALIZATION_CATEGORY_SIM_USIM                    = 0x04, /* category:锁(U)SIM卡 */

    SC_PERSONALIZATION_CATEGORY_BUTT
};
typedef VOS_UINT8 SC_PERSONALIZATION_CATEGORY_ENUM_UINT8;



enum SC_PERSONALIZATION_INDICATOR_ENUM
{
    SC_PERSONALIZATION_INDICATOR_INACTIVE                   = 0x00, /* 未激活 */
    SC_PERSONALIZATION_INDICATOR_ACTIVE                     = 0x01, /* 已激活 */

    SC_PERSONALIZATION_INDICATOR_BUTT
};
typedef VOS_UINT8 SC_PERSONALIZATION_INDICATOR_ENUM_UINT8;



enum SC_PERSONALIZATION_STATUS_ENUM
{
    SC_PERSONALIZATION_STATUS_READY     = 0x00, /* 已经解锁 */
    SC_PERSONALIZATION_STATUS_PIN       = 0x01, /* 未解锁状态，需输入解锁码 */
    SC_PERSONALIZATION_STATUS_PUK       = 0x02, /* Block状态，需输入UnBlock码 */

    SC_PERSONALIZATION_STATUS_BUTT
};
typedef VOS_UINT8 SC_PERSONALIZATION_STATUS_ENUM_UINT8;



enum SC_VERIFY_SIMLOCK_RESULT_ENUM
{
    SC_VERIFY_SIMLOCK_RESULT_READY            = 0x00, /* READY: MT is not pending for any simlock */
    SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN       = 0x01, /* PH-NET PIN: MT is waiting network personalization password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK       = 0x02, /* PH-NET PUK: MT is waiting network personalization unblocking password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN    = 0x03, /* PH-NETSUB PIN: MT is waiting network subset personalization password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK    = 0x04, /* PH-NETSUB PUK: MT is waiting network subset personalization unblocking password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN        = 0x05, /* PH-SP PIN: MT is waiting service provider personalization password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK        = 0x06, /* PH-SP PUK: MT is waiting service provider personalization unblocking password to be given */

    SC_VERIFY_SIMLOCK_RESULT_BUTT
};
typedef VOS_UINT8 SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8;



enum SC_PORT_STATUS_ENUM
{
    SC_PORT_STATUS_OFF                  = 0x00, /* 端口关闭 */
    SC_PORT_STATUS_ON                   = 0x01, /* 端口打开 */

    SC_PORT_STATUS_BUTT
};
typedef VOS_UINT32 SC_PORT_STATUS_ENUM_UINT32;


enum SC_DH_KEY_TYPE_ENUM
{
    SC_DH_KEY_SERVER_PUBLIC_KEY         = 0x00,             /* 服务器公钥 */
    SC_DH_KEY_MODEM_PUBLIC_KEY          = 0x01,             /* MODEM侧公钥 */
    SC_DH_KEY_MODEM_PRIVATE_KEY         = 0x02,             /* MODEM侧私钥 */

    SC_DH_KEY_BUTT
};
typedef VOS_UINT32 SC_DH_KEY_TYPE_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct
{
   VOS_UINT8                            aucPhLockCodeBegin[SC_MAX_CODE_LEN];
   VOS_UINT8                            aucPhLockCodeEnd[SC_MAX_CODE_LEN];
}SC_PH_LOCK_CODE_STRU;



typedef struct
{
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;                  /* 锁网锁卡的category类别 */
    SC_PERSONALIZATION_INDICATOR_ENUM_UINT8                 enIndicator;                 /* 锁网锁卡的激活指示 */
    SC_PERSONALIZATION_STATUS_ENUM_UINT8                    enStatus;                    /* 锁网锁卡的当前状态 */
    VOS_UINT8                                               ucMaxUnlockTimes;            /* 锁网锁卡的最大解锁次数 */
    VOS_UINT8                                               ucRemainUnlockTimes;         /* 锁网锁卡的剩余解锁次数 */
    VOS_UINT8                                               aucReserved[2];              /* 保留字节，用于四字节对齐 */
    VOS_UINT8                                               ucGroupNum;                  /* 号段个数，一个begin/end算一个号段 */
    SC_PH_LOCK_CODE_STRU                                    astLockCode[SC_MAX_CODE_NUM];/* 锁网锁卡的号段内容*/
}SC_SIMLOCK_CATEGORY_STRU;


typedef struct
{
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;                  /* 锁网锁卡的category类别 */
    SC_PERSONALIZATION_INDICATOR_ENUM_UINT8                 enIndicator;                 /* 锁网锁卡的激活指示 */
    VOS_UINT8                                               ucMaxUnlockTimes;            /* 锁网锁卡的最大解锁次数 */
    VOS_UINT8                                               ucGroupNum;                  /* 号段个数，一个begin/end算一个号段 */
    SC_PH_LOCK_CODE_STRU                                    astLockCode[SC_MAX_CODE_NUM];/* 锁网锁卡的号段内容*/
    /* astLockCode摘要密文，生成过程：aucSimlockRsaData是由astLockCode先经过MD5算法生成摘要，
       然后使用USB dog中的私钥进行加密的校验数据。 在simlock code合法性检查的时候，先使用AK-File中
       的公钥对aucSimlockRsaData进行解密，然后与astLockCode使用MD5生成的摘要进行比较。*/
    VOS_UINT8                                               aucSimlockRsaData[SC_RSA_ENCRYPT_LEN];
    /* 锁卡的解锁密码，由16位的PIN码使用USB dog中的私钥进行加密的数据 */
    VOS_UINT8                                               aucLockRsaPin[SC_RSA_ENCRYPT_LEN];
    /* 锁卡的UnBlock密码，由16位的PUK码使用USB dog中的私钥进行加密的数据 */
    VOS_UINT8                                               aucLockRsaPuk[SC_RSA_ENCRYPT_LEN];
}SC_WRITE_SIMLOCK_DATA_STRU;




typedef struct
{
    VOS_UINT8       aucAuthPubKey[SC_AUTH_PUB_KEY_LEN];   /* 鉴权公钥 */
    VOS_UINT8       aucSignature[SC_SIGNATURE_LEN];       /* 鉴权公钥的摘要经AES-ECB算法(密钥为SSK)计算生成的摘要签名 */
}SC_SET_FAC_AUTH_PUB_KEY_STRU;



typedef struct
{
    /* SC获取随机数并采用公钥进行RSA加密后的码流 */
    VOS_UINT8       aucIdentifyStartRsp[SC_RSA_ENCRYPT_LEN];
}SC_IDENTIFY_START_RESPONSE_STRU;



typedef struct
{
    /* 后台通过私钥和<identify_start_response>解密生成随机数，再用私钥对随机数加密生成<identify_end_request>，
       通过命令^IDENTIFYEND参数<identify_end_request>发送给协议栈，协议栈使用该数据和产线鉴权公钥还原随机数，
       若还原随机数与原随机数一致则鉴权通过，否则，鉴权失败 */
    VOS_UINT8       aucIdentifyEndReq[SC_RSA_ENCRYPT_LEN];
}SC_IDENTIFY_END_REQUEST_STRU;



typedef struct
{
    /* AT命令^IDENTIFYEND中的参数<onoff>的值 */
    SC_PORT_STATUS_ENUM_UINT32          enStatus;

    /* AT命令^IDENTIFYEND中的参数<port_passwd>的值，<port_passwd>为16位密码（密码长度
       为固定的16个“0”-“9”字符）经过RSA加密生成的128字节密文 */
    VOS_UINT8                           aucRsaPwd[SC_RSA_ENCRYPT_LEN];
}SC_SET_PORT_ATTRIBUTE_STRU;


typedef struct
{
    VOS_UINT8                           aucCKCryptoPwd[SC_CRYPTO_PWD_LEN]; /* CK密文 */
    VOS_UINT8                           aucUKCryptoPwd[SC_CRYPTO_PWD_LEN]; /* UK密文 */
}SC_CK_CATEGORY_STRU;




typedef struct
{
    /* 目前支持3种category，结构体数组按照network->network subset->SP的顺序排列 */
    SC_SIMLOCK_CATEGORY_STRU            astSimlockCategory[SC_MAX_SUPPORT_CATEGORY];
}SC_PI_FILE_STRU;


typedef struct
{
    /* 目前支持3种category，结构体数组按照network->network subset->SP的顺序排列 */
    SC_CK_CATEGORY_STRU                 astCKCategory[SC_MAX_SUPPORT_CATEGORY];
}SC_CK_FILE_STRU;


typedef struct
{
    SC_PORT_STATUS_ENUM_UINT32          enPortStatus;       /* 端口锁状态，明文 */
    VOS_UINT8                           aucDKCryptoPwd[SC_CRYPTO_PWD_LEN]; /* DK密文 */
}SC_DK_FILE_STRU;



typedef struct
{
    VOS_UINT8                           aucAuthPubKey[SC_AUTH_PUB_KEY_LEN];    /* AK明文 */
}SC_AK_FILE_STRU;



typedef struct
{
    VOS_UINT8                           aucSignature[SC_SIGNATURE_LEN];    /* 签名文件码流 */
}SC_SIGN_FILE_STRU;


typedef SC_PI_FILE_STRU SC_SIMLOCK_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_GetSimlockInfo(SC_SIMLOCK_INFO_STRU *pstSimlockInfo);



extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_WriteSimLockData(SC_WRITE_SIMLOCK_DATA_STRU *pstWriteSimLockData);


extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                enModemID
);


extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyIMEI(MODEM_ID_ENUM_UINT16 enModemID);


SC_ERROR_CODE_ENUM_UINT32 SC_PERS_NoVerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
);


SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
);


extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UnLock(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                enModemID
);


extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetFacAuthPubKey(SC_SET_FAC_AUTH_PUB_KEY_STRU *pstSetFacAuthPubKey);



extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_StartIdentify(SC_IDENTIFY_START_RESPONSE_STRU *pstIdentifyStartRsp);



extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_EndIdentify(SC_IDENTIFY_END_REQUEST_STRU *pstIdentifyEndReq);



extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaEncrypt(
    VOS_UINT8   *pucRawData,
    VOS_UINT32   ulLen,
    VOS_UINT8   *pucCipherData,
    VOS_UINT32  *pulCipherLen
);



extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaDecrypt(
    VOS_UINT8  *pucCipherData,
    VOS_UINT32  ulCipherLen,
    VOS_UINT8  *pucRawData,
    VOS_UINT32 *pulLen
);


extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteHUK(VOS_UINT8 *pucHuk, VOS_UINT32 ulLen);


extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteIMEI(MODEM_ID_ENUM_UINT16    enModemID,
                                                  VOS_UINT8              *pucCipherData,
                                                  VOS_UINT32              ulCipherLen);


extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetPortAttrib(SC_SET_PORT_ATTRIBUTE_STRU *pstSetPortAttrib);



extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_GetPortAttrib(SC_PORT_STATUS_ENUM_UINT32   *penStatus);


extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_VerifyPortPassword(VOS_UINT8 *pucPwd, VOS_UINT8 ucLen);


extern VOS_UINT32 SC_APSEC_ParseSecPacket(
    VOS_UINT32                         *pulSPLen,
    VOS_UINT8                          *pucSecPacket );


extern VOS_UINT32 SC_PERS_SimlockUnlock(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucPwd );

#if (FEATURE_ON == FEATURE_VSIM)

SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetDhKey(
    MODEM_ID_ENUM_UINT16                enModemID,
    SC_DH_KEY_TYPE_ENUM_UINT32          enKeyType,
    VOS_UINT32                          ulKeyLen,
    VOS_UINT8                          *pucKey
);
#endif


VOS_UINT32 SC_COMM_Backup(VOS_VOID);

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



