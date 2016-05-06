/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Cds.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : 定义CDS相关的数据结构
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_IPFCTRL_H__
#define __CDS_IPFCTRL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "CdsDepend.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define CDS_IPF_MAX_DL_FILTER_NUM                   (12)          /* 下行Filter目前使用8个 */
#define CDS_IPF_MAX_UL_FILTER_NUM                   (128)         /* 下行Filter目前使用128个 */
#define CDS_IPF_MAX_DL_CFG_NUM                      (128)         /* 下行可配置的最大BD个数为128个 */

/*下行SDU队列大小*/
#define CDS_IPF_DL_SDU_QUE_SIZE                     (2048)

/*AD0短包内存长度*/
#define CDS_IPF_AD_0_PKT_LEN                        (400)

/*AD1长包内存长度*/
#define CDS_IPF_AD_1_PKT_LEN                        (1500)

/*ADQ内存预留长度*/
#define CDS_UL_RESV_LEN_FOR_PDU_HDR                 (4)

/*IPF AD长度分界阈值*/
#define CDS_IPF_AD_LEN_THRESHOLD                    ((CDS_IPF_AD_0_PKT_LEN) + 1)

/*IPF BD完成中断超时时间*/
#define CDS_IPF_BD_CMP_INT_TIMEOUT                  (648)

/*AD描述符缓存大小,取AD0和AD1的最大值*/
#define CDS_IPF_ULAD_DESC_SIZE                      (IPF_ULAD0_DESC_SIZE)

/*启动ADQ空保护定时器的阈值，当可配置AD数量大于该值时则启动保护定时器*/
#define CDS_IPF_ULAD_START_TMR_THRESHOLD            (CDS_IPF_ULAD_DESC_SIZE - 6)

/*AD空保护定时器时长，暂定为10ms*/
#define CDS_IPF_AD_EMPTY_PROTECT_TMR_LEN            (10)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/


/*****************************************************************************
 枚举名    : CDS_IPF_DL_FILTER_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 下行IP过滤ID
*****************************************************************************/
typedef enum CDS_IPF_DL_FILTER_ID
{
    CDS_IPF_DL_FITLER_ID_DHCP4 = 0,
    CDS_IPF_DL_FITLER_ID_DHCP6,
    CDS_IPF_DL_FITLER_ID_RS,
    CDS_IPF_DL_FITLER_ID_RA,
    CDS_IPF_DL_FITLER_ID_NS,
    CDS_IPF_DL_FITLER_ID_NA,
    CDS_IPF_DL_FITLER_ID_REDIRECT,
    CDS_IPF_DL_FITLER_ID_LL_PING6,          /*Link Local Ping V6*/
    CDS_IPF_DL_FITLER_ID_LL_FE80,           /*Link Local Addr*/
    CDS_IPF_DL_FITLER_ID_LL_FF,
    CDS_IPF_DL_FITLER_ID_BUTT
}CDS_IPF_DL_FILTER_ID_ENUM;

typedef VOS_UINT32  CDS_IPF_DL_FILTER_ID_ENUM_UINT32;


/*****************************************************************************
 枚举名    : CDS_UL_IPF_RSLT_IPSEG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 上行IPF过滤结果中IP分段信息
*****************************************************************************/
typedef enum CDS_UL_IPF_IPSEG_TYPE
{
    CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT   = 0,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_MID,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_TAIL,
    CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_BUTT
}CDS_UL_IPF_RSLT_IPSEG_TYPE_ENUM;

typedef VOS_UINT16   CDS_UL_IPF_RSLT_IPSEG_TYPE_ENUM_UINT16;


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : IPF_RESULT
 协议表格  :
 ASN.1描述 :
 结构说明  : 硬件Ip过滤的结果
*****************************************************************************/
typedef struct IPF_RESULT
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
}IPF_RESULT_STRU;

/*****************************************************************************
 结构名    : CDS_IPF_FILTER_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPF FILTER队列结构，预留上行过滤配置结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulDownLinkUsedNum;
    IPF_FILTER_CONFIG_S             astDlFilter[CDS_IPF_MAX_DL_FILTER_NUM];
}CDS_IPF_FILTER_CFG_STRU;


/*****************************************************************************
 结构名    : CDS_IPF_CTRL_ENTITY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPF控制实体
*****************************************************************************/
typedef struct CDS_IPF_CTRL_ENTITY
{
    HTIMER                              pstAdqEmptyProtTmr;                     /*ADQ空保护定时器*/

    IPF_RD_DESC_S                       astUlRdBuff[IPF_ULRD_DESC_SIZE];        /*宏定义会在底软头文件中给出*/
    IPF_CONFIG_DLPARAM_S                astDlIpfCfgPara[CDS_IPF_MAX_DL_CFG_NUM];   /*下行IPF配置数组*/
    CDS_IPF_FILTER_CFG_STRU             stFilterCfgStru;                        /*过滤器配置结构*/

    LUP_QUEUE_STRU                     *pstDlSduQue;                            /*下行SDU缓存队列*/
    LUP_QUEUE_STRU                     *pstDlSrcMemFreeQue;                     /*下行源内存释放队列*/

    IPF_AD_DESC_S                       astUlAdBuff[CDS_IPF_ULAD_DESC_SIZE];    /*上行AD描述符定义*/

    VOS_UINT32                          ulDlMaxBdNum;                           /*下行BD最大个数*/

}CDS_IPF_CTRL_ENTITY_STRU;
/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
/*lint -e960*/
extern CDS_IPF_CTRL_ENTITY_STRU g_stCdsIpfCtrlEntity;
/*lint +e960*/


/*获取CDS IPF控制实体*/
#define CDS_GET_IPF_CTRL_ENTITY()          (&g_stCdsIpfCtrlEntity)

/*上行RD缓存*/
#define CDS_GET_UL_RD_BUFF()               (g_stCdsIpfCtrlEntity.astUlRdBuff)

/*获得ADQ空保护定时器指针*/
#define CDS_GET_ADQ_EMPTY_TMR_PTR()        (g_stCdsIpfCtrlEntity.pstAdqEmptyProtTmr)

/*下行SDU缓存*/
#define CDS_GET_IPF_DL_SDU_QUE()               (g_stCdsIpfCtrlEntity.pstDlSduQue)

/*下行源内存释放*/
#define CDS_IPF_DL_SRCMEM_FREE_QUE()       (g_stCdsIpfCtrlEntity.pstDlSrcMemFreeQue)

/*获得下行IPF配置参数数组地址*/
#define CDS_IPF_GET_DL_CFG_PARA_ARRAY()    (g_stCdsIpfCtrlEntity.astDlIpfCfgPara)

/*下行IPF过滤器组地址*/
#define CDS_GET_DL_IPF_FILTER_ARRAY()      (&(g_stCdsIpfCtrlEntity.stFilterCfgStru.astDlFilter[0]))

/*下行IPF过滤器数量*/
#define CDS_GET_DL_IPF_FILTER_NUM()        (g_stCdsIpfCtrlEntity.stFilterCfgStru.ulDownLinkUsedNum)

/*下行IPF过滤器*/
#define CDS_GET_DL_IPF_FILTER_PTR(ulFilterID)  (&(g_stCdsIpfCtrlEntity.stFilterCfgStru.astDlFilter[ulFilterID]))

/*下行IPF最大BD个数*/
#define CDS_GET_IPF_DL_MAX_BD_NUM()          (g_stCdsIpfCtrlEntity.ulDlMaxBdNum)

/*Set IP Type*/
#define CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,Type)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltType = (Type)

/*设置IP中下一个协议类型*/
#define CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,Protocol) \
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltNhEn = PS_TRUE;\
           (pstFilter)->stMatchInfo.unNextHeader.u32Protocol = (Protocol)

/*Set Hi Port*/
#define CDS_DL_IPF_FILTER_SET_PORT_HI(pstFilter,usHiPort)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn = PS_TRUE;\
           (pstFilter)->stMatchInfo.unDstPort.Bits.u16DstPortHi   = (usHiPort)

/*Set Low Port*/
#define CDS_DL_IPF_FILTER_SET_PORT_LOW(pstFilter,usLowPort)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn = PS_TRUE;\
           (pstFilter)->stMatchInfo.unDstPort.Bits.u16DstPortLo   = (usLowPort)

/*Set ICMP Type*/
#define CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,Type)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltTypeEn  = PS_TRUE;\
           (pstFilter)->stMatchInfo.unFltCodeType.Bits.u16Type    = (Type)

/*Set ICMP Code*/
#define CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,Code)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltCodeEn  = PS_TRUE;\
           (pstFilter)->stMatchInfo.unFltCodeType.Bits.u16Code    = (Code)

/*Set Filter Priority*/
#define CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,Priority)\
           (pstFilter)->stMatchInfo.unFltChain.Bits.u16FltPri     = (Priority)

/*Set Dest Link Local Addr FE80*/
#define CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FE80(pstFilter)\
           (pstFilter)->stMatchInfo.u8DstAddr[0]  = 0xFE;\
           (pstFilter)->stMatchInfo.u8DstAddr[1]  = 0x80;\
           (pstFilter)->stMatchInfo.u8DstMsk[0]   = 0xFF;\
           (pstFilter)->stMatchInfo.u8DstMsk[1]   = 0xC0;\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRAddrEn = PS_TRUE

/*Set Dest Link Local Addr FF*/
#define CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FF(pstFilter)\
           (pstFilter)->stMatchInfo.u8DstAddr[0]  = 0xFF;\
           (pstFilter)->stMatchInfo.u8DstMsk[0]   = 0xFF;\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltRAddrEn = PS_TRUE

/*Set DL IPF Filter Bearer ID*/
#define CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,BearerID)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltBid  = (BearerID)

/*Set Filter Enable*/
#define CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter)\
           (pstFilter)->stMatchInfo.unFltRuleCtrl.Bits.FltEn   = PS_TRUE

/*设置DL BD属性中的中断标志置位*/
#define CDS_DL_BD_SET_ATTR_INT_FLG(usAttr)                  ((usAttr) = (usAttr) | 0x1)

/*设置DL BD属性中过滤器通道链表头*/
#define CDS_DL_BD_SET_ATTR_WITH_FC_HDR(usAttr,ucFcHdr)      ((usAttr) = (ucFcHdr) << 4)

/*清除扩展过滤器标志，将第17bit设置为0*/
#define CDS_DL_IPF_CLR_EX_FILTER_FLG(FilterId)              ((FilterId) = (FilterId) & 0x0000FFFF)

/*设置扩展过滤器标志，将第17bit设置为1*/
#define CDS_DL_IPF_SET_EX_FILTER_FLG(FilterId)              ((FilterId) = (FilterId) | 0x00010000)


/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_UINT32   CDS_IpfInit(VOS_VOID );
extern VOS_UINT32   CDS_EnableDlIPFFilter(VOS_UINT16  usModemId);
extern VOS_UINT32   CDS_DisableDlIPFFilter(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID     CDS_ConfigDlIPF(VOS_VOID);
extern TTF_MEM_ST*  CDS_AllocTtfMem(VOS_UINT32 ulLen);
extern VOS_UINT32   CDS_RxDlSdu(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID     CDS_AdqEmptyProctectTimeOutProc(VOS_VOID);
extern TTF_MEM_ST*  CDS_RdTransferTtfMem(const IPF_RD_DESC_S *pstRdDesc);


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

