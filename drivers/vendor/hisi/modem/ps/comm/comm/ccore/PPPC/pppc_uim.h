/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_uim.h
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年08月08日
  最近修改   :
  功能描述   : pppc_uim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PPPC_UIM_H__
#define __PPPC_UIM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
****************************************************************************/
#include "ppp_inc.h"
#include "UsimPsInterface.h"
#include "CUeSpec.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define PPPC_HRPD_MEID_LEN                                    (7)               /* MEID字节长 */
#define PPPC_HRPD_MEID_BIT_LEN                                (56)              /* MEID固定为56个BIT长 */

#define PPPC_EAP_CIMSI_MCC_MAX_LEN                            (3)               /* MCC的长度固定为3 */
#define PPPC_EAP_CIMSI_MNC_MAX_LEN                            (3)               /* MNC最大长度 */


#define PPPC_EAP_AUTN_LEN                                     (16)              /* AT_AUTN长度 */
#define PPPC_EAP_RAND_LEN                                     (16)              /* AT_RAND长度 */

/* 各个文件的大小 */
#define PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE                  (7)
#define PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE              (256)


#define PPPC_MAX_USIM_FILE_NUM                                (8)               /* UIM 中的文件类别 */
#define PPPC_MAX_USIM_REQSEND_NUM                             (5)               /* 一次发送读卡文件请求的最大次数 */
#define PPPC_HRPD_UIMREAD_MAX_RETRY_CNT                       (3)               /* 读取文件失败重试次数 */
#define PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER_LEN                (3000)            /* 读卡文件定时器时长 */

/* 文件Mask */
#define PPPC_INIT_USIM_ELEMENT_RUIMID_MASK                    (0x01)            /* 6F31 */
#define PPPC_INIT_USIM_ELEMENT_CST_MASK                       (0x02)            /* 6F32 */
#define PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK                 (0x04)            /* 6F38 */
#define PPPC_INIT_USIM_ELEMENT_USGIND_MASK                    (0x08)            /* 6F42 */
#define PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK                   (0x10)            /* 6F57 */
#define PPPC_INIT_USIM_ELEMENT_EFIMSIM_MASK                   (0x20)            /* 6F22 */
#define PPPC_INIT_USIM_EFIMSI_MASK                            (0x40)            /* 6F07 */
#define PPPC_INIT_USIM_EFAD_MASK                              (0x80)            /* 6FAD */


/* 定义 AUTH 过程中使用的 ProcessCtrl 值 */
#define PPPC_HRPD_AUTH_PROCESSCTRL_DEFAULT_PROC               (0x00)
#define PPPC_HRPD_AUTH_PROCESSCTRL_SAVE_REGS_ON               (0x10)

/* 接入鉴权，若卡的NAI信息无效时，使用IMSI构造NAI的固定后缀 */
#define PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_STR                     ("@mycdma.cn")
#define PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_LEN                     (sizeof(PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_STR))

/* 接入鉴权，若卡的NAI信息无效且IMSI无效时，使用固定打桩的NAI */
#define PPPC_HRPD_AUTH_NAI_STUB_STR                           ("370021234567801@mycdma.cn")
#define PPPC_HRPD_AUTH_NAI_STUB_LEN                           (sizeof(PPPC_HRPD_AUTH_NAI_STUB_STR))


/***************************SHA-1算法相关定义 BEGIN**********************************************/

#define VOS_TRAN(var, num) (((var) << (num)) | ((var) >> (32 - (num))))

/* 这里实际上将整个ulong变换了字节序
   例如   | a | b | c | d |
   转换为 | d | c | b | a |
*/

/* 小端序 */
#define VOS_NUM1 (0xFF00FF00)
#define VOS_NUM2 (0x00FF00FF)
#define VOS_VAR0(index) (pStr->ulNum[index] = (VOS_TRAN(pStr->ulNum[index],24)&VOS_NUM1) \
    |(VOS_TRAN(pStr->ulNum[index],8)&VOS_NUM2))

#define VOS_VAR(index) (pStr->ulNum[index&15] = VOS_TRAN(pStr->ulNum[(index+13)&15]^pStr->ulNum[(index+8)&15] \
    ^pStr->ulNum[(index+2)&15]^pStr->ulNum[index&15],1))

#define VOS_NUM3 (0x5A827999)
#define VOS_NUM4 (0x6ED9EBA1)
#define VOS_NUM5 (0x8F1BBCDC)
#define VOS_NUM6 (0xCA62C1D6)

#define OPERA0(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR0(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA1(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA2(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM4+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA3(a,b,c,d,e,f) e+=(((b|c)&d)|(b&c))+VOS_VAR(f)+VOS_NUM5+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA4(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM6+VOS_TRAN(a,5);b=VOS_TRAN(b,30);


/*******************************SHA-1算法相关定义 END******************************************/
#define USIMM_AUTH_IK_LEN               (16)                                    /* IK长度 */
#define USIMM_AUTH_CK_LEN               (16)                                    /* CK长度 */
#define USIMM_AUTH_AUTS_LEN             (14)                                    /* AUTS长度 */
#define USIMM_AUTH_RES_LEN              (16)                                    /* RES最大长度 */


/*******************************************************************************
                             获取FixedData根地址
*******************************************************************************/
#define PPPC_HRPD_GetFixedDataAddr(usModemId)       (&(g_astPppcFixedData[usModemId]))

#define PPPC_HRPD_GetUimStatus(usModemId)           ((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUimStatus)         /* 获取UIM存在标记 */
#define PPPC_HRPD_SetUimStatus(usModemId, enStatus) (((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUimStatus) = (enStatus))    /* 设置UIM存在标记 */
#define PPPC_HRPD_GetUsimStatus(usModemId)          ((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUsimStatus)         /* 获取USIM存在标记 */
#define PPPC_HRPD_SetUsimStatus(usModemId, enStatus)    (((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUsimStatus) = (enStatus))    /* 设置USIM存在标记 */

/* 获取UIM数据地址 */
#define PPPC_HRPD_GetUimDataAddr(usModemId)         (&((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimData))

/* 获取USIM数据地址 */
#define PPPC_HRPD_GetUsimDataAddr(usModemId)         (&((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUsimData))

/* 获取NVIM数据地址 */
#define PPPC_HRPD_GetNvimDataAddr(usModemId)        (&((PPPC_HRPD_GetFixedDataAddr(usModemId))->stNvimData))

/* Terminal info */
#define PPPC_HRPD_GetTerminalInfoAddr(usModemId)    (&((PPPC_HRPD_GetNvimDataAddr(usModemId))->stTerminalInfo))

/* USIM卡读取标示 */
#define PPPC_HRPD_GetUsimFileReqMask(usModemId)            ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileReqMask)    /* 开机后需要读卡的标记位 */
#define PPPC_HRPD_GetUsimFileSucMask(usModemId)            ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileSucMask)    /* 读卡文件成功标志位 */
#define PPPC_HRPD_AddUsimFileSucMask(usModemId, ulFileMask)  ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileSucMask |= (ulFileMask))     /* 添加读取USIM卡文件成功标志位 */
#define PPPC_HRPD_AddUsimFileReqMask(usModemId, ulFileMask)  ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileReqMask |= (ulFileMask))     /* 添加需要读取USIM卡文件标志位 */
#define PPPC_HRPD_GetUsimFileMask(usModemId, ulInd)          ((((PPPC_HRPD_GetUsimFileSucMask(usModemId)) & (PPPC_HRPD_GetUsimFileReqMask(usModemId))) >> ulInd) % 2) /* 获取指定卡文件的读卡标志位 */
#define PPPC_HRPD_UimReadRetryCnt(usModemId)               ((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimReadTimer.ulRetryCnt)   /* 读卡文件失败重试次数 */
#define PPPC_HRPD_SetUimReadRetryCnt(usModemId, ulCnt)       ((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimReadTimer.ulRetryCnt = ulCnt)   /* 设置读卡文件失败重试次数 */
#define PPPC_HRPD_UimReadTimer(usModemId)                  ((&(PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimReadTimer.hTimer))   /* 读卡文件定时器 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*******************************************************************************
* Name        : PPPC_HRPD_MEID_STRU
*
* Description : MEID一共56个bit
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMeidLow;                              /* Low 32 bit of MEID */
    VOS_UINT32                          ulMeidHigh;                             /* High 24 bit of MEID */
}PPPC_HRPD_MEID_STRU;

/*******************************************************************************
 * Name        : PPPC_HRPD_UIM_STATUS_ENUM
 *
 * Description : UIM卡状态
 *******************************************************************************/
enum PPPC_HRPD_UIM_STATUS_ENUM
{
    PPPC_HRPD_UIM_STATUS_ABSENT         = 0,
    PPPC_HRPD_CARD_STATUS_UIM_PRESENT   = 1,
    PPPC_HRPD_CARD_STATUS_CSIM_PRESENT  = 2,
    PPPC_HRPD_UIM_STATUS_BUTT
};
typedef VOS_UINT8 PPPC_HRPD_UIM_STATUS_ENUM_UINT8;

/*******************************************************************************
 * Name        : PPPC_HRPD_ESN_MEID_TYPE_ENUM
 *
 * Description : ESN or MEID 类型
 *******************************************************************************/
enum PPPC_HRPD_ESN_MEID_TYPE_ENUM
{
    PPPC_HRPD_ESN_MEID_TYPE_ESN      = 0,
    PPPC_HRPD_ESN_MEID_TYPE_MEID        ,

    PPPC_HRPD_ESN_MEID_TYPE_BUTT
};
typedef VOS_UINT8 PPPC_HRPD_ESN_MEID_TYPE_ENUM_UINT8;


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
/*******************************************************************************
* Name        : PPPC_USIMM_AUTH_DATA_STRU
*
* Description : 鉴权数据
*******************************************************************************/
typedef struct
{
    USIMM_AUTH_TYPE_ENUM_UINT32         enAuthType;
    USIMM_AUTH_DATA_UNION               unAuthPara;
}PPPC_USIMM_AUTH_DATA_STRU;

/*******************************************************************************
* Name        : PPPC_USIM_READ_REQ_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3] ;                        /* 四字节对齐，保留        */
    VOS_UINT8                           ucFileNum;                              /* 需要读取的File数目      */
    VOS_UINT16                          ausEfId[PPPC_MAX_USIM_FILE_NUM];        /* 需要读取的文件类别      */
}PPPC_USIM_READ_REQ_STRU;

/*******************************************************************************
* Name        : PPPC_GET_FILE_INFO_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* 应用类型 */
    VOS_UINT16                  usEfId;         /* 文件ID */
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
}PPPC_GET_FILE_INFO_STRU;


/*******************************************************************************
* Name        : PPPC_HRPD_CST_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCstLen;
    VOS_UINT8                           aucCst[PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE];
} PPPC_HRPD_CST_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_ESN_MEID_STRU
*
* Description : 卡里面ESN和MEID不能同时存在
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_ESN_MEID_TYPE_ENUM_UINT8  enEsnMeidType;                          /* ESN or MEID */
    VOS_UINT8                           aucReserve[3];

    union
    {
        VOS_UINT32                      ulEsn;                                  /* 从卡里面读出来的ESN */
        PPPC_HRPD_MEID_STRU             stMeid;                                 /* 从卡里面读出来的MEID 56个bit */
    }u;
} PPPC_HRPD_ESN_MEID_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_RUIMID_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumbytes;                             /* 有效地Bytes个数 */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRUIMIDLow;                            /* Low 32 bit of RUIMID */
    VOS_UINT32                          ulRUIMIDHigh;                           /* High 24 bit of RUIMID */
} PPPC_HRPD_RUIMID_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_USGIND_STRU
*
* Description :
*               Bit 0:
*                  FALSE: ESN_ME is used for CAVE Authentication and MS Identification
*                  TRUE: IDUIMID is used for CAVE Authentication and MS Identification
*
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsgInd;

    VOS_UINT8                           aucReserve[3];
}PPPC_HRPD_USGIND_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_UPP_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHrpdUppLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHrpdUpp[PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE];
} PPPC_HRPD_UPP_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_UIM_INFO_STRU
*
* Description : 从UIM卡中读出的信息
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiLen;                              /* IMSI 占用的长度 */
    VOS_UINT8                           aucImsi[PS_CUE_IMSI_MAX_SIZE];          /* MS的IMSI标识 */
    PPPC_HRPD_CST_STRU                  stEfCst;                                /* CDMA业务表 */
    PPPC_HRPD_ESN_MEID_STRU             stEsnMeid;                              /* ESN or MEID */
    PPPC_HRPD_RUIMID_STRU               stRuimid;                               /* RUIMID */
    PPPC_HRPD_USGIND_STRU               stUsgind;                               /* USGIND */
    PPPC_HRPD_UPP_STRU                  stHrpdUpp;                              /* HRPD UPP */
    VOS_UINT8                           aucReserve[4];
} PPPC_HRPD_UIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_NVIM_TERMINAL_INFO_STRU
*
* Description : 手机规格信息
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEsn;                                  /* ESN */
    PPPC_HRPD_MEID_STRU                 stMeid;                                 /* MEID */

    VOS_UINT8                           ucMobMfgCode;                           /* Manufacturer code */
    VOS_UINT8                           ucMobModel;                             /* Model number */
    VOS_UINT16                          usMobFirmRev;                           /* Firmware revision number */
} PPPC_HRPD_NVIM_TERMINAL_INFO_STRU;


/*******************************************************************************
* Name        : PPPC_HRPD_UIM_INFO_STRU
*
* Description : 从UIM卡中读出的信息
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU   stTerminalInfo;                         /* 手机规格信息 */
} PPPC_HRPD_NVIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_READFILE_TIMER_STRU
*
* Description : 读卡文件定时器
*******************************************************************************/
typedef struct
{
    VOS_UINT32               ulRetryCnt;                                        /* 读取文件错误重试次数 */
    HTIMER                   hTimer;                                            /* 读文件超时定时器 */
} PPPC_HRPD_READFILE_TIMER_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_USIM_INFO_STRU
*
* Description : 从 USIM 中读出的信息
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiLen;                              /* IMSI 占用的长度 */
    VOS_UINT8                           aucImsi[PS_CUE_IMSI_MAX_SIZE];          /* MS的IMSI标识 */
    VOS_UINT8                           ucMncLen;                               /* MNC长度 */
    VOS_UINT8                           aucRsv[3];
}PPPC_HRPD_USIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_FIXED_DATA_STRU
*
* Description : 在一次开机后，保持不变的数据，
*               每次Deactive时，不对该部分数据进行初始化，仅仅在关机时才释放
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_UIM_INFO_STRU             stUimData;                              /* 从 UIM 中读出的参数 */
    PPPC_HRPD_USIM_INFO_STRU            stUsimData;                             /* 从 USIM 中读出的参数 */
    PPPC_HRPD_NVIM_INFO_STRU            stNvimData;                             /* 从 NVIM 中读出的参数 */
    VOS_UINT32                          ulUimFileReqMask;                       /* 开机后需要读卡的标记位 */
    VOS_UINT32                          ulUimFileSucMask;                       /* 读卡文件成功标记位 */
    PPPC_HRPD_READFILE_TIMER_STRU       stUimReadTimer;                         /* 读卡文件定时器 */
    PS_BOOL_ENUM_UINT8                  enUimStatus;                            /* UIM存在标记,PS_TRUE:存在,PS_FALSE:不存在 */
    PS_BOOL_ENUM_UINT8                  enUsimStatus;                           /* USIM存在标记,PS_TRUE:存在,PS_FALSE:不存在 */
    VOS_UINT8                           aucReserve[2];
}PPPC_HRPD_FIXED_DATA_STRU;

/****************************** EAP卡鉴权结果集合 ***************************/
enum PPPC_USIMM_AUTH_RESULT_ENUM
{
    PPPC_USIMM_AUTH_SUCCESS             = 0x00,        /*鉴权成功*/
    PPPC_USIMM_AUTH_MAC_FAILURE         = 0x01,        /*MAC失败*/
    PPPC_USIMM_AUTH_SYNC_FAILURE        = 0x02,        /*重同步失败*/
    PPPC_USIMM_AUTH_OTHER_FAILURE       = 0x03,        /*其他失败*/
    PPPC_USIMM_AUTH_RESULT_BUTT
};
typedef VOS_UINT8 PPPC_USIMM_AUTH_RESULT_ENUM_UINT8;

/****************************** EAP卡鉴权返回结构体 ***************************/
typedef struct
{
    PPPC_USIMM_AUTH_RESULT_ENUM_UINT8   enResult;
    VOS_UINT8                           aucIK[USIMM_AUTH_IK_LEN];               /* IK 长度:16bytes */
    VOS_UINT8                           aucCK[USIMM_AUTH_CK_LEN];               /* CK 长度:16bytes */
    VOS_UINT8                           aucAuts[USIMM_AUTH_AUTS_LEN];           /* AUTS 长度:14bytes */
    VOS_UINT8                           aucAuthRes[USIMM_AUTH_RES_LEN];         /* RES 长度:4~16bytes */
    VOS_UINT8                           ucAuthRseLen;
    VOS_UINT8                           ucIdentifier;                           /*透传参数 */
    VOS_UINT8                           aucRsv[3];
}PPPC_EAP_AUTH_RESULT_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/



/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID PPPC_UsimmReadFileCnfProc(USIMM_READFILE_CNF_STRU *pstMsg);
VOS_VOID PPPC_InitFixedData(VOS_VOID);
VOS_UINT32 PPPC_UIM_GetCIMSI(VOS_UINT8 aucIMSI[]);
VOS_UINT32 PPPC_UIM_GetUsimIMSI(VOS_UINT8 aucIMSI[]);
VOS_VOID PPPC_HRPD_UimClearnReadTimer(VOS_VOID);
VOS_UINT32  PPPC_ReadFixedData(VOS_VOID);
PS_BOOL_ENUM_UINT8 PPPC_MD5Active(VOS_VOID);
VOS_UINT32 PPPC_UIM_RunCaveAuthReq(VOS_UINT32 ulRandu);
VOS_UINT32 PPPC_PihUsimStatusIndProc(USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg);
VOS_UINT32 PPPC_UIM_BuildNAIByIMSI(VOS_UINT8 *pucNAIBuff, VOS_UINT32 ulNAIBuffLen);
VOS_UINT32 PPPC_UIM_SendEapAuthReq
(
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn,
    VOS_UINT8                           ucIdentifier
);
VOS_UINT8 PPPC_UIM_GetImsiMncLen(VOS_VOID);





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

#endif /* end of pppc_uim.h */

