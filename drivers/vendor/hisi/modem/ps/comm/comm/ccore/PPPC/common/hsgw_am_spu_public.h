/******************************************************************************

                  版权所有 (C), 2012-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hsgw_public.h
  版 本 号   : 初稿
  作    者   : zhaichao 00129699
  生成日期   : 2012年10月30日
  最近修改   :
  功能描述   : HSGW/PDSN SPU各模块公用数据结构定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月30日
    作    者   : zhaichao 0129699
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HSGW_AM_PUBLIC_H__
#define __HSGW_AM_PUBLIC_H__


#define DIAM_AUTH_DYNAAA_CONTEXT_ALARM_FLAG  "DIAM_DYNAAA_CONTEXT_ALARM_FLAG"
#define DIAM_AUTH_DYNAAA_CONTEXT_ALARM_NUM 64

/* HSGW/PDSN 状态机ID统一定义 */
typedef enum
{
    E_FSM_ID_USM = 1,
    E_FSM_ID_A11,
    E_FSM_ID_PDN,
    E_FSM_ID_SIPV4,
    E_FSM_ID_SIPV6,
    E_FSM_ID_CMIP,
    E_FSM_ID_PMIPV4,
    E_FSM_ID_PMIPV6_4,
    E_FSM_ID_PMIPV6_6,
    E_FSM_ID_L2TP,
    E_FSM_ID_EHRPD,
    E_FSM_ID_DHCP,
    E_FSM_ID_PMV6,

    E_FSM_ID_BUTT
}HSGW_FSM_ID_E;

/*接口配置*/
typedef struct tagFA_COF_CFG_S
{
    VOS_UINT32      ulCmip4Vpn4Index; 
    VOS_UINT32      ulFaCofAddrCmipV4;         /* FA转交地址V4*/
    VOS_UINT32      ulFaCofSubIndexCmipv4;     /* PI接口subindex */

    VOS_UINT32      ulPmip4Vpn4Index; 
    VOS_UINT32      ulFaCofAddrPmipV4;
    VOS_UINT32      ulFaCofSubIndexPmipv4;     /* PI接口subindex */

    VOS_UINT32      ulPdsnPmipv6Vpn6Index;
    in6_addr   stPdsnPmipv6Vpn6CofAddr;
    VOS_UINT32      ulPdsnPmipv6Vpn6CofSubIndex;

    VOS_UINT32      ulHsgwPmipv6Vpn4Index; 
    VOS_UINT32      ulHsgwPmipv6Vpn4CofAddr;
    VOS_UINT32      ulHsgwPmipv6Vpn4CofSubIndex;

    VOS_UINT32      ulHsgwPmipv6Vpn6Index;
    in6_addr   stHsgwPmipv6Vpn6CofAddr;
    VOS_UINT32      ulHsgwPmipv6Vpn6CofSubIndex; 

    VOS_UINT32      ulFaCofIndexCmipv4;        /* PI接口索引*/
    VOS_UINT32      ulFaCofIndexPmipv4;        /* PI接口索引*/
}VOS_PACKED FA_COF_CFG_S;


/*  鉴权应答原因值  */
#define  DIAM_AUTH_SUCCESS           0  /* 鉴权处理成功 */
#define  DIAM_AUTH_FAIL              1  /* 鉴权处理拒绝 */
#define  DIAM_AUTH_SRV_ERR           2  /* 服务器故障或与服务器通信异常 */
#define  DIAM_AUTH_CLT_ERR           3  /* DIAM AUTH模块内资源耗尽等异常 */
#define  DIAM_AUTH_MSG_FMT_ERR       4  /* 消息格式错误 */
#define  DIAM_AUTH_SERVER_DELETE     6  /* 3GPP SERVER去活 */


#define MDN_MAX_LEN 20/* Added by l61463 at 2008-06-18 PDSN V9 for 电信MDN需求 */
#define RD_HW_VPN_NAME_LEN_MAX          31     /* VPN Name最长为31个字节 */
#define MDN_BCD_MAX_LEN_WITH_PREFIX 15
#define MDN_BCD_MAX_LEN_WITHOUT_PREFIX 13

#define A11_RESV_MESSAGE       0x18  /*Resv message*/

#define A11_RESVCONF_MESSAGE  0x19  /*ResvConf message*/

#define A11_RESVERR_MESSAGE   0x20  /*ResvErr message*/
#define A11_RESV_ERR_MESSAGE       0x21  /*Resv err message*/
#define A11_RESV_NW_MESSAGE       0x22  /*网络侧发起的Resv message*/



/* ==============更新类型定义============== */
#define PDN_UPD_MSK_AUXA10_CREATE       0x00000001      /* 辅A10创建 */
#define PDN_UPD_MSK_AUXA10_RELEASE      0x00000002      /* 辅A10释放 */
#define PDN_UPD_MSK_AUXA10_CHANGE       0x00000004      /* 辅A10修改 */
#define PDN_UPD_MSK_PCF_HANDOFF         0x00000008      /* PCF切换 */
#define PDN_UPD_MSK_RAT_CHANGE          0x00000010      /* SO切换 */
#define PDN_UPD_MSK_QOS_CHANGE          0x00000020      /* QOS改变 */
#define PDN_UPD_MSK_LOC_CHANGE          0x00000040      /* 位置(BSID)改变 */
#define PDN_UPD_MSK_SUBNET_CHANGE       0x00000080      /* SUBNET改变 */
#define PDN_UPD_MSK_AIRSTATE_CHANGE     0x00000100      /* 空口状态改变 */
#define PDN_UPD_MSK_COA                 0x00000200      /* AAA发起COA */
#define PDN_UPD_MSK_QCI_ARP             0x00000400      /*QCI ARP更新*/
#define PDN_UPD_MSK_AMBR                0x00000800  
#define PDN_UPD_MSK_STACK_CREATE        0x00001000      /* 双栈创建 */
#define PDN_UPD_MSK_STACK_RELEASE       0x00002000      /* 双栈(之一)释放 */
#define PDN_UPD_MSK_OLD_PCF_RELEASE     0x00004000      /*老的pcf发起去活更新*/

#define HSGW_MAX_APP_NUM                8192
typedef enum
{
    PDN_UPDTYPE_INVALID = 0, 
    PDN_UPDTYPE_A11     = 1,     /* A11发起的更新 */
    PDN_UPDTYPE_SUBNET,          /* PDN子状态机发起的更新 */
    PDN_UPDTYPE_COA,             /* COA发起的更新 */    
    PDN_UPDTYPE_PCC_PCRFC,       /* PDSN PCC用户PCRFC发起的网络侧更新 */    
    PDN_UPDTYPE_PCC_ROLLBACK,    /* PDSN PCC用户回滚到SIP更新 */
    PDN_UPDTYPE_EHRPD_PPP_RENEGO,/* ehrpd重协商 */
    PDN_UPDTYPE_BUTT,
}PDN_UPDATE_TYPE_E;

/* PDN的更新消息头 */
typedef struct
{
    VOS_UINT32 ulUpdateType;     /* 更新类型, PDN_UPDATE_TYPE_E */
    VOS_UINT32 ulUpdateMask;     /* 发生更新的掩码 */
}PDN_UPDATE_MSGHEAD_S;

#define HSGW_AM_MSG_ENCAP_STR(PucMsgStorPointer, PucStr, UlStrLen) \
    (VOID)VOS_MemCpy((PucMsgStorPointer), (PucStr), (UlStrLen));\
    (PucMsgStorPointer) = ((UCHAR *)(PucMsgStorPointer)) + (UlStrLen);


extern  VOID AUTH_RegProductCallBackFun4DEF(VOS_VOID);
extern VOS_UINT32 *g_aulHSGWDynAAAContextAlarmFlag;

VOS_UINT32 A11_GetGrmSruCpuRate(VOS_UINT32 *pulSruCpuValue);
VOID USM_HsgwApnAlarmRefresh(VOID);

extern VOS_UINT32  A11_StringTo4Bits( UCHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum );


#endif /* __HSGW_AM_PUBLIC_H__ */
