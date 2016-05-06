/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : TcNasinterface.h
  Description : TC与NAS其它TASK的接口头文件
  History     :
      1. 2004-05-17 Creat
      2. L47619   2005.11.26   问题单:    A32D01107
      3.日    期  : 2006年12月4日
        作    者  : luojian id:60022475
        修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
*******************************************************************************/

#ifndef TC_NAS_INTERFACE_H_
#define TC_NAS_INTERFACE_H_

#include "NasMmlCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)
/***********************************
    Define TC-INTRA Primitive
************************************/
/* TC -> NAS */
#define TCRABM_TEST_LOOP_REQ                      0x00000001
#define TCMM_TEST_REQ                             0x00000002
#define TCGMM_TEST_REQ                            0x00000003
#define TCRABM_TEST_REQ                           0x00000004
#define TCCC_TEST_REQ                             0x00000005
#define TCSM_TEST_REQ                             0x00000006
#define TCSMS_TEST_REQ                            0x00000007
#define TCSS_TEST_REQ                             0x00000008
#define TCMM_DATA_REQ                             0x00000009
#define TCGMM_DATA_REQ                            0x0000000A

/* NAS -> TC */
#define TCRABM_TEST_LOOP_CNF                      0x0000000B
#define TCRABM_TEST_CNF                           0x0000000C
#define TCRABM_RAB_IND                            0x0000000D
#define TCMM_DATA_IND                             0x0000000E
#define TCGMM_DATA_IND                            0x0000000F

#define TCMM_RR_REL_IND                           0x00000010
#define TCGMM_RR_REL_IND                          0x00000011
#define TCGMM_HANDOVER_IND                        0x00000012


/* TC -> MTA */
#define TCMTA_RESET_UE_POS_STORED_INFO_IND        0x00000020

/***********************************
    NAS-TC 接口中使用的宏定义
************************************/
#define TC_NAS_MAX_SIZE_TC_MSG                       0x10                       /* TC消息的最大长度    16字节               */
#define TC_CN_DOMAIN_CS                              0x00                       /* CS域的名称    0                          */
#define TC_CN_DOMAIN_PS                              0x01                       /* PS域的名称    1                          */
#define TC_LB_MAX_RBNUM                              0x10                       /* LOOP BACK实体的最大个数    16            */
#define TC_RB_TEST_ACTIVE                            0x01                       /* 激活RB测试    1                          */
#define TC_RB_TEST_DEACTIVE                          0x00                       /* 去激活RB测试    0                        */
#define TC_RABM_MAX_RAB_SETUP                        0x10                       /* CN Domain中RAB的最大个数    16           */
#define TC_LOOP_OPEN                                 0x00                       /* 停止回环测试    0                        */
#define TC_LOOP_CLOSE                                0x01                       /* 开始进行回环测试    1                    */
#define TC_MODE_1                                    0x00                       /* LOOP MODE 1                              */
#define TC_MODE_2                                    0x01                       /* LOOP MODE 2                              */
#define TC_RAB_SETUP                     (VOS_UINT32)0x00                       /* 建立新的RAB                              */
#define TC_RAB_RELEASE                   (VOS_UINT32)0x01                       /* 释放已经建立的RAB                        */
#define TC_CMPMSG_SIZE                   (VOS_UINT32)0x02                       /* TC发给mm或gmm的消息长度，2个字节         */

/******************************************************************************
*       TCRABM_TEST_LOOP_REQ
******************************************************************************/
typedef struct
{
    VOS_UINT32                 ulRBID;                                               /* LB 实体的RBID                            */
    VOS_UINT32                 ulUpRlcSduSize;                                       /* LB实体的信息                             */
}LB_INFO_STRU;

typedef struct tcrabm_test_loop_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32             ulMode;                                              /* 开始或者结束的标志                       */
    VOS_UINT32             ulRBNum;                                             /* LB 实体个数                              */
    LB_INFO_STRU           aLBIdList[TC_LB_MAX_RBNUM];                          /* LB实体的信息                             */

    VOS_UINT8              ucTestLoopMode;                                      /* 模式一或模式二 */
} TCRABM_TEST_LOOP_REQ_STRU;

/******************************************************************************
*       TCRABM_TEST_LOOP_CNF
******************************************************************************/
typedef struct tcrabm_test_loop_cnf_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
} TCRABM_TEST_LOOP_CNF_STRU;

/******************************************************************************
*       TCMM_TEST_REQ
******************************************************************************/
typedef struct tcmm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCMM_TEST_REQ_STRU;

/******************************************************************************
*       TCGMM_TEST_REQ
******************************************************************************/
typedef struct tcgmm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCGMM_TEST_REQ_STRU;

/******************************************************************************
*       TCCC_TEST_REQ
******************************************************************************/
typedef struct tccc_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCCC_TEST_REQ_STRU;

/******************************************************************************
*       TCSM_TEST_REQ
******************************************************************************/
typedef struct tcsm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCSM_TEST_REQ_STRU;

/******************************************************************************
*       TCSMS_TEST_REQ
******************************************************************************/
typedef struct tcsms_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCSMS_TEST_REQ_STRU;

/******************************************************************************
*       TCSS_TEST_REQ
******************************************************************************/
typedef struct tcss_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCSS_TEST_REQ_STRU;

/******************************************************************************
*       TCRABM_TEST_REQ
******************************************************************************/
typedef struct tcrabm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulMode;                                              /* 激活或者去激活的标志                     */
} TCRABM_TEST_REQ_STRU;

/******************************************************************************
*       TCRABM_TEST_CNF
******************************************************************************/
typedef struct
{
    VOS_UINT32                  ulRabId;                                             /* RAB ID                                   */
    VOS_UINT32                  ulCnDomainId;                                        /* 该RAB所属CN Domain                       */
    VOS_UINT32                  ulRbId;                                              /* 该RAB包含RB ID                           */
} RAB_INFORMATION_STRU;

typedef struct tcrabm_test_cnf_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulRabCnt;                                            /* 当前已经建立的RAB数量                    */
    RAB_INFORMATION_STRU   aRabInfo[TC_RABM_MAX_RAB_SETUP];                     /* RAB实体的信息                            */
} TCRABM_TEST_CNF_STRU;

/******************************************************************************
*       TCRABM_RAB_IND
******************************************************************************/
typedef struct tcrabm_rab_ind_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    VOS_UINT32                  ulRabChangeType;                                     /* RAB的操作类型                            */
    RAB_INFORMATION_STRU   RabInfo;                                             /* RAB实体的信息                            */
} TCRABM_RAB_IND_STRU;

/******************************************************************************
*       TCMM_DATA_IND
******************************************************************************/
typedef struct tc_msg_stru{
    VOS_UINT32                   ulTcMsgSize;                                        /* [1,TC_NAS_MAX_SIZE_TC_MSG]               */
    VOS_UINT8                   aucTcMsg[4];                                        /* 消息的前四个字节内容                     */
}TC_MSG_STRU;

typedef struct tcmm_data_ind_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    TC_MSG_STRU            RcvTcMsg;                                            /* 消息内容                                 */
}TCMM_DATA_IND_STRU;

/******************************************************************************
*       TCMM_DATA_REQ
******************************************************************************/
typedef struct tcmm_data_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    TC_MSG_STRU            SendTcMsg;                                           /* 该域需要发送的TC消息                     */
}TCMM_DATA_REQ_STRU;

/******************************************************************************
*       TCGMM_DATA_IND
******************************************************************************/
typedef struct tcgmm_data_ind_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    TC_MSG_STRU            RcvTcMsg;                                            /* 消息内容                                 */
}TCGMM_DATA_IND_STRU;

/******************************************************************************
*       TCGMM_DATA_REQ
******************************************************************************/
typedef struct tcgmm_data_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* 消息头                                   */
    TC_MSG_STRU            SendTcMsg;                                           /* 该域需要发送的TC消息                     */
}TCGMM_DATA_REQ_STRU;


/*****************************************************************************
 结构名    : TCMM_RR_REL_IND_STRU
 结构说明  :  MM用此消息通知TC连接释放
 1.日    期   : 2011年9月14日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头    */
}TCMM_RR_REL_IND_STRU;

/*****************************************************************************
 结构名    : TCGMM_RR_REL_IND_STRU
 结构说明  :  GMM用此消息通知TC连接释放
 1.日    期   : 2011年9月14日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头    */
}TCGMM_RR_REL_IND_STRU;

/*****************************************************************************
 结构名    : TCGMM_HANDOVER_IND_STRU
 结构说明  :  GMM用此消息通知TC异系统切换完成
 1.日    期   : 2011年9月14日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头           */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRat;                               /* 当前驻留的接入技术  */
    VOS_UINT8                           aucReserve[3];                          /* 保留 */
}TCGMM_HANDOVER_IND_STRU;


/*****************************************************************************
枚举名    : TC_UE_POS_TECH_ENUM_UINT8
枚举说明  : RESET UE POSITIONING STORED INFORMATION消息中的IE "UE Positioning
            Technology"的取值枚举定义
1.日    期  : 2012年7月10日
  作    者  : L47619
  修改内容  : Add for V7R1C50 A-GPS Project
*****************************************************************************/
enum TC_UE_POS_TECH_ENUM
{
    TC_UE_POS_TECH_AGPS   = 0 ,
    TC_UE_POS_TECH_AGNSS      ,
    TC_UE_POS_TECH_BUTT
};
typedef VOS_UINT8 TC_UE_POS_TECH_ENUM_UINT8;

/*****************************************************************************
 结构名    : TCMTA_RESET_UE_POS_STORED_INFO_STRU
 结构说明  :  TC通知MTA清除定位辅助数据的指示
 1.日    期   : 2011年9月14日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头           */

    TC_UE_POS_TECH_ENUM_UINT8           enUePosTech;                            /* UE Positioning Technology  */
    VOS_UINT8                           aucReserve[3];                          /* 保留 */
}TCMTA_RESET_UE_POS_STORED_INFO_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif  /* TC_NAS_INTERFACE_H_ */

