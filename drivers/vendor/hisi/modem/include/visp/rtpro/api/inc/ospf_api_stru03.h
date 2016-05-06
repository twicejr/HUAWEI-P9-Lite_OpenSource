/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_stru03.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF API 结构定义(Query接口整改)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/
#ifndef _OSPF_API_STRU03_H
#define _OSPF_API_STRU03_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#if 31 /*31 Query接口结构体*/
/*********************快查询相关定义***************************/

typedef struct tagOSPF_SHOWLSDB
{
    USHORT  usProcessId;
    UCHAR   ucLsaType;   
/*
#define OSPF_ROUTER_LSA           1
#define OSPF_NETWORK_LSA          2
#define OSPF_SUMMARY_LSA          3
#define OSPF_SUMMARY_ASBR_LSA     4
#define OSPF_ASEXTERNAL_LSA       5
#define OSPF_NSSA_LSA             7
#define OSPF_OPAQUE_LOCAL_LSA     9
#define OSPF_OPAQUE_AREA_LSA      10
#define OSPF_OPAQUE_AS_LSA        11*/
    UCHAR   ucPadding;
}OSPF_SHOWLSDB_S;


typedef struct tagOspf_Lsdb_in
{
    USHORT   usProcId;  /*OSPF实例ID*/    
    USHORT   usLsaType; /*LSA类型 */
    ULONG    ulAreaId;  /*域ID */
    ULONG    ulLsaId;   /*LSA ID*/
    ULONG    ulAdvRtrId; /*route id*/ 
}OSPF_LSDB_IN_S; /*OSPF 的LSDB 查询条件*/

typedef struct tagOSPF_LSAHdr_OUT
{
    USHORT  usLsaAge;   /* 老化时间 */
    UCHAR   ucOptions;   /* 可选项 */
    UCHAR   ucLsaType;   /* LSA 类型 */
    ULONG   ulLinkId;   /* 链路ID */
    ULONG   ulAdvRtr;   /* 通告路由器ID */
    LONG    ILSSeqNum;   /* 序列号 */
    USHORT  usLSChksum; /* 校验和 */
    USHORT  usLength;   /* 包含LSA头部在内的LSA长度 */
}OSPF_LSAHDR_OUT_S; /*LSA的头部信息*/

typedef struct tagOSPF_RtrTOS_OUT
{
    UCHAR   ucTOS;   /* TOS */
    UCHAR   ucVar;   /* unused value Zero */
    USHORT  usMetric;   /* Metric */
}OSPF_RTRTOS_OUT_S;

typedef struct tagOSPF_RtrPiece_OUT
{
    ULONG   ulLinkId;   /* Link ID */
    ULONG   ulLinkdata;   /* Link data */
    UCHAR   ucType;   /* Type */
    UCHAR   ucNumTOS;   /* number of  TOS */
    USHORT   usMetric;   /* Metric */
    OSPF_RTRTOS_OUT_S  stTOS[OSPF_LSA_MAX_TOS_COUNT];     /* Array to first node of List of TOS */
}OSPF_RTRPIECE_OUT_S; /*路由器LSA 内部数据*/

typedef struct tagOSPF_RtrLSA_OUT
{
    UCHAR    ucVEBBit;   /* V , E and B bit */
    UCHAR    ucPad;
    USHORT   usLinkCount;   /* Link count */
    OSPF_RTRPIECE_OUT_S   stRtrPieces[OSPF_LSA_MAX_RTR_PIECE]; 
}OSPF_RTRLSA_OUT_S; /*路由器LSA*/



typedef struct tagOSPF_NetLSA_Adv_OUT
{
    ULONG   ulNetMask;   /* Network Mask */
    ULONG   ulAttachedRtr[OSPF_LSA_MAX_NET_NBR];
}OSPF_NETLSA_OUT_S; /*网络LSA*/


typedef struct tagOSPF_SummPiece_OUT
{
    UCHAR   ucTOS;   /* TOS */
    UCHAR   szTOSMetric[OSPF_ARRAY_SIZE_3];   /* TOS Metric */
}OSPF_SUMMPIECE_OUT_S; /*SUMMARY LSA 内部数据*/

typedef struct tagOSPF_SummLSA_Adv_OUT
{
    ULONG   ulNetMask;   /* Network Mask */
    ULONG   ulMetric;   /* Metric -First 8 bits are zero */
    OSPF_SUMMPIECE_OUT_S   stSummPiece[OSPF_LSA_MAX_SUM_PIECE];   
}OSPF_SUMMLSA_OUT_S; /*SUMMARY LSA 结构*/


typedef struct tagOSPF_ASEPiece_OUT
{
    UCHAR   ucE_TOS;   /* E bit in first Netpiece indicates type of metric  in others Backward Compatibility & TOS*/
    UCHAR   szTOSMetric[OSPF_ARRAY_SIZE_3];   /* Metric & TOS Metric */
    ULONG   ulFwdAddr;   /* Forwarding Address */
    ULONG   ulExtRtTag;   /* External Route Tag */
}OSPF_ASEPIECE_OUT_S;


typedef struct tagOSPF_ASELSA_Adv_OUT
{
    ULONG   ulNetMask;   /* Network Mask */
    OSPF_ASEPIECE_OUT_S   stASEPiece[OSPF_LSA_MAX_ASE_PIECE];   /* Array to first node of list of ASE/NSSA LSA */
}OSPF_ASELSA_OUT_S; /*ASE LSA类型*/

typedef struct tagOSPF_OpqLsa_Adv_OUT
{
    UCHAR   szOpqData[OSPF_LSA_MAX_OPQ_DATA];   /*Unparsed Data to be used by external modules*/
    UCHAR   ucPadding[2]; /*B015-L*/
}OSPF_OPQLSA_OUT_S; /*OPQ扩展数据*/


typedef struct tagOSPF_SHOW_LSADATA
{
    OSPF_LSAHDR_OUT_S   stLsaHdr;   /* LSA header */
    union   tagOSPF_LSA_BODY_OUT
    {
        OSPF_RTRLSA_OUT_S   stRtrLSA;   /* Router LSA */
        OSPF_NETLSA_OUT_S   stNetLSA;   /* Network LSA */
        OSPF_SUMMLSA_OUT_S   stSummLSA;   /* Summary LSA */
        OSPF_ASELSA_OUT_S   stAseLSA;   /* External LSA */
        OSPF_OPQLSA_OUT_S   stOpqLSA;   /* Opaque LSA */
    }unLSAOut;
}OSPF_SHOW_LSADATA_S;  /*所有的LSA共有结构*/


typedef struct tagOSPF_SHOWLSDB_OUT
{
    ULONG   ulRouterId;
    ULONG   ulAreaId;   /* for type-5 LSA, this field is invalid */
    USHORT  usProcId;
    USHORT  usRes;
    OSPF_SHOW_LSADATA_S stLSAData;
    /*UCHAR   *pucLSA;*/   /* defined in ospf\include\ospf_lsa.h */
}OSPF_SHOWLSDB_OUT_S;

typedef struct tagOSPF_VLSDB_KEY
{
    /*域ID 和邻居ID用于查询IF CB ,LS id和route id 用于查询VLSDB CB*/
    UCHAR ucAreaId[4]; /*域ID*/
    UCHAR ucNeighbor[4]; /*邻居*/
    UCHAR ucLsId[4];  /*链路ID */
    UCHAR ucRouterId[4]; /*route id*/
    ULONG ulProcId;
}OSPF_VLSDB_KEY_S; /*虚链路LSDB 查询关键字*/

/*OSPF 收发报文注册钩子函数类型*/
/*注意: 如果修改该类型，请同步修改qonmscks.c qonmsck2.c中的定义
为了避免头文件包含导致编译不过，定义类似类型
l61496 */

/*OSPF 报文钩子处理函数:OSPF实例号、数据首地址、数据长度*/
typedef ULONG (*OSPF_PACKET_HOOK_FUNC)(USHORT usProcId, ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);

/*Modified by liangjicheng 00103192, G3, 2011/1/25   问题单号:V2R3C03-ROTUE-MERGE */
/*PRU新需求，邻居状态变化通知结构体*/
/*此结构如果修改必须修改 I3_NBR_STATE_NOTIFY_S*/
typedef struct tagOSPF_NBR_STATE_NOTIFY
{
    ULONG ulVrfIndex;          /*VRF索引*/
    ULONG ulProcID;            /*进程ID*/
    ULONG ulRouterID;          /*Router ID*/
    ULONG ulAreaID;            /*区域ID*/   
    ULONG ulLocalIfIndex;      /*和邻居对应的本地接口索引*/ 
    ULONG ulNbrAddr;           /*邻居地址route id*/
    ULONG ulNbrReachable;      /*邻居是否可达标识
                                                      0:邻居不可达
                                                      1:邻居不可达*/
    ULONG ulPeerAddress;       /*邻居对应接口的地址*/
    ULONG ulReason;            /*状态变化的原因值,暂时保留不用 */
}OSPF_NBR_STATE_NOTIFY_S;  /*邻居状态通知结构体*/
/*commented by r62469 */
/*PRU新需求，邻居状态变化通知接口*/
typedef ULONG (*OSPF_NBR_STATE_NOTIFY_FUNC)(OSPF_NBR_STATE_NOTIFY_S *pstNotify);
/*End of Modified by liangjicheng 00103192, 2011/1/25   问题单号:V2R3C03-ROTUE-MERGE */

/* Begin BC3D03438 liangjicheng 2010-08-10*/
typedef struct tagOSPF_NBR_EVNET_NOTIFY
{
    ULONG ulVrfIndex;         /*VRF索引*/
    ULONG ulProcID;            /*进程ID*/ 
    ULONG ulNbrRouterID;   /*邻居地址route id*/
    ULONG ulNbrIntAddr;     /*邻居对应接口的地址*/
    ULONG ulReason;            /*状态变化的原因值 具体参见原因值说明*/
    ULONG ulPrevState;        /*前一状态 具体参见状态值说明*/
    ULONG ulNewState;         /*新状态 具体参见状态值说明*/
    /*Add by q62011 for DTS2010082701594:OSPF邻居告警字段增强*/
    ULONG ulLocalRouterID;   /*自己的route id*/
    ULONG ulAreaID;            /*区域ID*/
    ULONG ulIfIndex ;           /*接口索引*/
    ULONG ulIfAddr ;           /*接口地址*/
}OSPF_NBR_EVENT_NOTIFY_S;  /*邻居状态通知结构体*/
typedef ULONG (*OSPF_NBR_EVENT_NOTIFY_FUNC)(OSPF_NBR_EVENT_NOTIFY_S *pstNotify);
/* End   BC3D03438 */

/*Modified by lKF35457, 添加接口状态转变告警 for v1r8c01, 2010/10/20 */
typedef struct tagOSPF_IF_EVENT_NOTIFY
{
  ULONG ulProcID; /*OSPF进程ID*/
  ULONG ulAreaID; /*接口区域号*/

  ULONG ulIfIndex;  /*本地接口索引*/
  ULONG ulLocalRouterID;  /*自身router id*/
  ULONG ulIfAddr; /*自身接口IP*/

  ULONG ulReason; /*触发事件*/
  ULONG ulPrevState;  /*接口状态机转变前的状态*/
  ULONG ulNewState; /*接口状态机转变后的状态*/	
}OSPF_IF_EVENT_NOTIFY_S;
typedef ULONG (*OSPF_IF_EVENT_NOTIFY_FUNC)(OSPF_IF_EVENT_NOTIFY_S *pstNotify);

#endif
/*add by lkf35460 问题单号：DTS2011040603509*/
typedef struct tagOSPF_DR_INFO
{
   ULONG ulDrRouteId;   /*DR Router id*/
   ULONG ulBDrRouteId;  /*BDR Router id*/
   UCHAR ucIfType;      /*OSPF接口类型 分别定义广播，NBMA，P2P，P2MP类型*/
   UCHAR ucRes[LEN_8-1];/*预留7字节空间*/
}OSPF_DR_INFO_S;/*DR BDR信息结构*/
/*end add by lkf35460 问题单号：DTS2011040603509*/

/*Added by guo00178934, 全系统邻居、LSA个数统计, 2011/7/19   问题单号:DTS2011071901386 */
typedef struct tagOSPF_SYS_COUNT_S
{
  ULONG ulTotalNbrs;         /* 本系统所有邻居个数 */
  ULONG ulTotalLSAs;         /* 本系统所有LSA个数 */
  ULONG ulDetailLSAs[10];    /* 本系统各类LSA个数(下标对应LSA类型:
                               1、2、3、4、5、7有效) */
}OSPF_SYS_COUNT_S;
/* End of Added by guo00178934, 2011/7/19   问题单号:DTS2011071901386 */

/*Added by guojianjun178934, 【DOPRA IP V3R2C10-同步问题单-DTS2014081600138】【OSPF可靠性提升专项】同一区域内Router-ID数量过多触发路由计算上限，导致路由生成失败 , 2014/9/25   问题单号:DTS2014092408371  */
/*Added by guojianjun178934, 【检视发现问题】OSPF的LSA冲突检测及告警需求 , 2013/10/14   问题单号:DTS2013101400241 */
/*OSPF告警类型*/
typedef enum tagOSPF_WARNING_TYPE
{
    OSPF_WARNING_NETWORK_LSA_CLASH = 1,   /*Network LSA冲突告警*/
    OSPF_WARNING_ROUTE_CALC_OVER_LIMIT = 2,   /*路由计算超过计算上限*/
    OSPF_WARNING_MAX = 100
} OSPF_WARNING_TYPE_E;
/* End of Added by guojianjun178934, 2013/10/14   问题单号:DTS2013101400241 */
/* End of Added by guojianjun178934, 2014/9/25   问题单号:DTS2014092408371  */

typedef ULONG (*OSPF_WARNING_HOOK_FUNC)(ULONG ulWarningType, VOID *pWarningInfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
