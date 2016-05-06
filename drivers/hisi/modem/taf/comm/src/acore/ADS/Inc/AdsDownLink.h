

#ifndef __ADSDOWNLINK_H__
#define __ADSDOWNLINK_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "AdsIntraMsg.h"
#include "AdsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 定义ADS下行IP TYPE */
#define ADS_DL_IP_TYPE_FLAG                         (0x0200)

/* bd_cd_noeqBD中len和CD的长度不等错误提示 */
#define ADS_DL_IPF_RD_RSLT_BDCD_LEN_ERR_FLG         (0x4000)    /* 0100 0000 0000 0000 B */

/* pkt_parse_err数据解析错误指示 */
#define ADS_DL_IPF_RD_RSLT_PKT_PARSE_ERR_FLG        (0x2000)    /* 0010 0000 0000 0000 B */

/* bd_pkt_noeqBD中len和IP包头指示的len不等错误指示 */
#define ADS_DL_IPF_RD_RSLT_BD_PKT_LEN_ERR_FLG       (0x1000)    /* 0001 0000 0000 0000 B */

/* head_len_err IPV4长度错误指示信号 */
#define ADS_DL_IPF_RD_RSLT_HDR_LEN_ERR_FLG          (0x0800)    /* 0000 1000 0000 0000 B */

/* version_err版本号错误指示 */
#define ADS_DL_IPF_RD_RSLT_VER_ERR_FLG              (0x0400)    /* 0000 0100 0000 0000 B */

/* 定义IPF BEARID 错包标志位 */
#define ADS_DL_IPF_BEARID_ERR_PKT_FLAG              (ADS_DL_IPF_RD_RSLT_BDCD_LEN_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_PKT_PARSE_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_BD_PKT_LEN_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_HDR_LEN_ERR_FLG \
                                                   | ADS_DL_IPF_RD_RSLT_VER_ERR_FLG)

/* 检查是RD Result, 是否为异常Packet */
#define ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(usRslt)       ((usRslt) & ADS_DL_IPF_BEARID_ERR_PKT_FLAG)

/* 检查是RD Result, 是否为Version错包 */
#define ADS_DL_IPF_RD_RSLT_IS_VER_ERR_PKT(usRslt)   ((usRslt) & ADS_DL_IPF_RD_RSLT_VER_ERR_FLG)

/*lint -emacro({717}, ADS_DL_SAVE_RD_DESC_TO_IMM)*/
#define ADS_DL_SAVE_RD_DESC_TO_IMM(pstImmZc, pstRdDesc)\
            do\
            {\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = (pstRdDesc)->u16Result;\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = ((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) << 16) | ((pstRdDesc)->u16UsrField1);\
            } while(0)

/* 从IPF Result获取IP包类型 */
#define ADS_DL_GET_IPTYPE_FROM_IPF_RESULT(usRslt)   ((ADS_PKT_TYPE_ENUM_UINT8)(((ADS_DL_IPF_RESULT_STRU *)&(usRslt))->usIpType))

/* RD的user field 1，高1byte为Modem id，低1byte为Rab Id */
#define ADS_DL_GET_IPF_RESULT_FORM_IMM(pstImmZc)    ((VOS_UINT16)(((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0xFFFF0000) >> 16))
#define ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc)       ((VOS_UINT16)(((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0x0000FF00) >> 8))
#define ADS_DL_GET_RABID_FROM_IMM(pstImmZc)         ((VOS_UINT8)((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0x000000FF))

/* 下行内存cache invalidate (map) */
/*lint -emacro({717}, ADS_IPF_DL_MEM_MAP)*/
#define ADS_IPF_DL_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_FALSE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/* 下行内存cache invalidate (unmap) */
/*lint -emacro({717}, ADS_IPF_DL_MEM_UNMAP)*/
#define ADS_IPF_DL_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_FALSE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
 结构名    : IPF_RESULT
 结构说明  : 硬件Ip过滤结果的结构

  1.日    期   : 2012年4月12日
    作    者   : A00165503
    新    增   : 硬件Ip过滤结果的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usBearedId:6;
    VOS_UINT16                          usIpSegInfo:2;
    VOS_UINT16                          usUpperLayer:1;
    VOS_UINT16                          usIpType:1;
    VOS_UINT16                          usVerErr:1;
    VOS_UINT16                          usHdrLenErr:1;
    VOS_UINT16                          usPktLenNotEq:1;
    VOS_UINT16                          usPktLenErr:1;
    VOS_UINT16                          usBdCdNotEq:1;
    VOS_UINT16                          usResv:1;
} ADS_DL_IPF_RESULT_STRU;

/*****************************************************************************
结构名    : ADS_DL_RD_STRU
结构说明  : ADS保存下行RD信息

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS保存下行RD信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucRabId;                               /* Rab Id*/
    ADS_PKT_TYPE_ENUM_UINT8              enPktType;                             /* Pkt Type*/
    VOS_UINT8                            aucRsv[6];                             /* 保留 */
    CDS_ADS_DL_IPF_BEARER_ID_ENUM_UINT32 enBearId;                              /* Bear Id*/
    VOS_UINT32                           ulLen;                                 /* 搬移后的数据包长度 */
    VOS_UINT8                           *pucData;                               /* 搬移后的数据包指针 */
    VOS_VOID                            *pTtfMem;                               /* 目的TTF指针*/
} ADS_DL_RD_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg);
VOS_VOID ADS_DL_ProcTxData(IMM_ZC_STRU *pstImmZc);
VOS_UINT32 ADS_DL_RcvAtMsg(MsgBlock* pMsg);
VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg);
VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg);
VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID);
VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID);
VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum);
VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty);
VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(VOS_UINT32 ulParam, VOS_UINT32 ulTimerName);
VOS_UINT32 ADS_DL_ConfigAdq(IPF_AD_TYPE_E enAdType, VOS_UINT ulIpfAdNum);
VOS_VOID ADS_DL_AllocMemForAdq(VOS_VOID);
VOS_INT ADS_DL_CCpuResetCallback(DRV_RESET_CB_MOMENT_E enParam, VOS_INT lUserData);
VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(MsgBlock *pMsg);
VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(MsgBlock *pMsg);
VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID);
VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID);
VOS_VOID ADS_DL_SendNdClientDataInd(IMM_ZC_STRU *pstImmZc);


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

#endif /* end of AdsDlProcData.h */
