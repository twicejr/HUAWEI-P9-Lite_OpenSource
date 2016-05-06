/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmInterface.h
  Author      : 韩鲁峰
  Version     : V200R001
  Date        :
  Description : 该头文件定义了RABM与其他模块的接口数据结构、消息、函数
  History     :
  1. Date:
     Author: 韩鲁峰
     Modification:Create
  2. Data:2005-08-25
     Author: 罗小烽
     Modification:修改与增加函数定义、数据结构定义
  3. Date:2006-08-09
     Author: 60010247
     Modification:根据问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  4 .Date        : 2006-06-24
     Author      : l47619
     Modification: 问题单: A32D05709
 ************************************************************************/

#ifndef __RABM_INTERFACE_H__
#define __RABM_INTERFACE_H__



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TTFMem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifndef RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN
#define RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN                  19
#endif

#ifndef RABM_MAX_ENT_NUM
#define RABM_MAX_ENT_NUM                                    11
#endif

#ifndef RABM_NSAPI_OFFSET
#define RABM_NSAPI_OFFSET                                   5
#endif

#define NAS_RABM_RAB_ID_MIN                                 (5)
#define NAS_RABM_RAB_ID_MAX                                 (15)

/*****************************************************************************
  3 枚举定义
typedef enum
{
    模块名_意义描述_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2


    MAPS_TEMPLATE_BUTT,    用这个统一的BUTT，作为最后一个枚举值。

}MAPS_TEMPLATE_ENUM;   模块名_枚举类型描述_ENUM
*****************************************************************************/
typedef enum
{
    RABM_ABM_ENUM = 0,                  /*确认模式      */
    RABM_ADM_ENUM                       /*非确认模式    */

}RABM_TRANS_MODE_ENUM;




typedef enum
{
    RABM_FLOW_REPORT_ACCUMULATE = 1,           /*上报所有RABID的累加流量*/
    RABM_FLOW_REPORT_WITH_RABID,               /*上报指定RABID的流量*/
    RABM_FLOW_REPORT_TOTAL,                    /*上报所有RABID的流量*/

    RABM_FLOW_REPORT_BUTT
}RABM_FLOW_REPORT_MODE_ENUM;   /*流量上报模式*/
/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*---------------------------------------------------------
            Structs used between APS and RABM.
---------------------------------------------------------*/
typedef struct
{
    VOS_UINT8                           ucNsapi;
    RABM_TRANS_MODE_ENUM                TransMode;

}RABM_APS_SET_TRANS_MODE_ST;

/*---------------------------------------------------------
            Structs used between APP and RABM.
---------------------------------------------------------*/


/*----------------------------------------------------------
   SIGNAL PLANE Structs used between SNDCP and RABM.
----------------------------------------------------------*/
typedef struct
{
    /*In aucNPDUNumList[16][2], the items from[5] to [15] will be used
    for NSAPIs from NSAPI5 to NSAPI15. The position is the index of a NSAPI.

    aucNPDUNumList[i][0] == 0 : The NSAPI hasn't Received N-PDU Num;
                         == 1 : The NSAPI has Received N-PDU Number;

    aucNPDUNumList[i][1] == xx: The Receive N-PDU Number of NSAPI(i).
    "i" belongs to [5, 15]. */

    VOS_UINT8                          aucNPDUNumList[16][2];

}RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST;

typedef RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RABM_SNDCP_SEND_N_PDU_NUM_LIST_ST;
typedef RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RABM_PDCP_GET_N_PDU_NUM_LIST_ST;

typedef struct
{
    VOS_UINT32                          ulTLLI;
    RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RecvNPduNumList;

}RABM_SNDCP_SEQUENCE_IND_ST;

typedef RABM_SNDCP_SEQUENCE_IND_ST      RABM_SNDCP_SEQUENCE_RSP_ST;

/*---------------------------------------------------------
   User Plane DATA Structs used between SNDCP and RABM.
---------------------------------------------------------*/
typedef struct
{
    VOS_UINT8        ucNsapi;
    VOS_UINT16       usDataLen;          /*byte numbers of the PDU*/
    VOS_VOID        *pPdu;               /*the head pointer of the PDU*/
}RABM_USER_PLANE_DATA_ST;

typedef RABM_USER_PLANE_DATA_ST             RABM_USER_PLANE_UNITDATA_ST;



/*---------------------------------------------------------
         Structs used for set DS Flow Report Mode.
---------------------------------------------------------*/

typedef struct
{
    /*流量上报模式Mode可取如下三个值:
            RABM_FLOW_REPORT_ACCUMULATE : 上报所有RABID的累加流量
            RABM_FLOW_REPORT_WITH_RABID : 上报指定RABID的流量
            RABM_FLOW_REPORT_TOTAL      : 上报所有RABID的流量  */
    RABM_FLOW_REPORT_MODE_ENUM       Mode;

   /*指定的RABID,对模式RABM_FLOW_REPORT_WITH_RABID有意义*/
    VOS_UINT8       ucRabId;

}RABM_SET_FLOW_REPORT_MODE_ST;          /*设置流量上报的模式*/



/*****************************************************************************
  8 UNION定义
typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_UNION;
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
extern VOS_UINT8* pgucMapsTemplateBuffer;指针＋全局标识＋类型＋模块名＋意义描述
*****************************************************************************/

/*设置流量上报模式*/
extern RABM_SET_FLOW_REPORT_MODE_ST     gstRabmFlowReportMode;


/*****************************************************************************
  5 消息头定义
模块名＋意义＋HEADER
*****************************************************************************/



/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*---------------------------------------------------------
            MSG used between SNDCP and RABM.
---------------------------------------------------------*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*消息类型*/
    VOS_UINT16                          usPId;              /*SNDCP使用的子进程标识，填5即可*/
    RABM_SNDCP_SEQUENCE_IND_ST          RabmSnSequenceInd;
}RABM_SN_SEQUENCE_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP的回复消息使用V100R001的消息头*/
    RABM_SNDCP_SEQUENCE_RSP_ST          RabmSnSequenceRsp;

}RABM_SN_SEQUENCE_RSP_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP的回复消息使用V100R001的消息头*/
    RABM_USER_PLANE_DATA_ST             RabmSnDataInd;

}RABM_SN_DATA_IND_MSG;                          /*SNDCP的下行确认数据消息结构体*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP的回复消息使用V100R001的消息头*/
    RABM_USER_PLANE_UNITDATA_ST         RabmSnUnitDataInd;

}RABM_SN_UNITDATA_IND_MSG;                    /*SNDCP的下行非确认数据消息结构体*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          usPId;              /*SNDCP使用的子进程标识，填5即可*/
}RABM_SNDCP_SAVE_DATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                          ulMsgName;         /*SNDCP的回复消息使用V100R001的消息头*/
}RABM_SNDCP_SAVE_DATA_RSP_MSG;

typedef  struct
{
    VOS_UINT8                           ucFlag;             /*VOS_YES, 当前NSAPI有效; VOS_NO, 无效*/
    VOS_UINT8                           ucRbId;             /*NSAPI对应的RbId*/
    VOS_UINT8                           ucReserve[2];       /*保留*/
}SNDCP_NSAPI_MAP_RB_INFO;


#define   SNDCP_RABM_MAX_NSAPI_NUM   16
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          usPId;
    SNDCP_NSAPI_MAP_RB_INFO             astNsapiMapRb[SNDCP_RABM_MAX_NSAPI_NUM]; /* 数组索引值为NSAPI */
}RABM_SNDCP_RESUME_DATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP的回复消息使用V100R001的消息头*/
}RABM_SNDCP_RESUME_DATA_RSP_MSG;

/*---------------------------------------------------------
            MSG used between APS and RABM.
---------------------------------------------------------*/
#define RABM_APS_SET_TRANSMODE_MSG_TYPE                 4    /*其他TAF ==> RABM的原语ID在RabmTafInterface.h中定义*/


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*消息类型*/
    RABM_APS_SET_TRANS_MODE_ST          RabmApsSetTransMode;
}RABM_APS_SET_TRANSMODE_MSG;


/*****************************************************************************
  9 FUNCTIONS 定义
*****************************************************************************/
/*----------------------------------------------------------------------------
            FUNCTIONS used by APS and provided by RABM.
----------------------------------------------------------------------------*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function            : Rabm_setTransMode()
Description         : This function is used by APS to set translation mode in RABM.
Calls               :
Called By           :
Date Accessed       :
Date Update         :
Input               : pSetTransMode        传输模式结构体指针
Output              :
Return Value        : VOID
Others              :
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern VOS_VOID  NAS_RabmSetTransMode( RABM_APS_SET_TRANS_MODE_ST   *pSetTransMode );


/*****************************************************************************
 函 数 名  : RABM_SendUlData
 功能描述  : 发送上行数据，提供给应用使用
 输入参数  : ucRabId    -- RAB的值，G模式下为NSAPI
             pData      -- 要发送的数据，TTF_MEM形式
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008-02-27
    作    者   : g45205
    修改内容   : Created
*****************************************************************************/
extern VOS_VOID RABM_SendUlData(VOS_UINT8 ucRabId, TTF_MEM_ST *pData);

/*****************************************************************************
 函 数 名  : RABM_SendDlData
 功能描述  : 分发RB下行数据，提供给接入层使用，如SNDCP和PDCP
 输入参数  : ucRbId     -- RB的值，G模式下为NSAPI
             pData      -- 要发送的数据，TTF_MEM形式
 输出参数  :
 返 回 值  : 成功，返回 PS_SUCC，否则返回 PS_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008-02-27
    作    者   : g45205
    修改内容   : Created
*****************************************************************************/
extern VOS_UINT32 RABM_SendDlData(VOS_UINT8 ucRbId, TTF_MEM_ST *pData);


/*****************************************************************************
 函 数 名  : NAS_RABM_SetTcFlowCtrl
 功能描述  : 启动环回数据流控
 输入参数  :
 输出参数  :
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010-01-12
    作    者   : s00164817
    修改内容   : Created
*****************************************************************************/
extern VOS_VOID NAS_RABM_SetTcFlowCtrl(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_ClearTcFlowCtrl
 功能描述  : 停止环回数据流控
 输入参数  :
 输出参数  :
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010-01-12
    作    者   : s00164817
    修改内容   : Created
*****************************************************************************/
extern VOS_VOID NAS_RABM_ClearTcFlowCtrl(VOS_VOID);

VOS_VOID NAS_RABM_GetCurrFluxRate(
    VOS_UINT32                             *pulCurrSndFluxRate,
    VOS_UINT32                             *pulCurrRcvFluxRate
);

/*****************************************************************************
 10 OTHERS定义
*****************************************************************************/

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

#endif /* end of RabmInterface.h*/
