/*****************************************************************************

                  版权所有 (C), 1998-2009, 华为技术有限公司

*****************************************************************************
  文 件 名   : diag_ps_trans_cmd_id.h
  版 本 号   : V1.0
  作    者   : 陈文峰/00149739
  生成日期   : 2009-09-08
  功能描述   : TODO: ...

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2009-09-08
    作    者 : 陈文峰/00149739
    修改内容 : 创建文件

*****************************************************************************/

/*****************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
*****************************************************************************/




#ifndef __DIAG_PS_TRANS_CMD_ID_H__
#define __DIAG_PS_TRANS_CMD_ID_H__

/*****************************************************************************
 PS 协议栈 透传指令 BEGIN
*****************************************************************************/


/*****************************************************************************
     NAS 透传指令 BEGIN
*****************************************************************************/

/* DIAG_CMD_MM_SET_HPLMN*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.1 APP_MM_SET_HPLMN_REQ*/
/*                        APP_MM_SET_HPLMN_CNF*/
/* 应用通过这条原语设置HPLMN，协议栈通过APP_MM_SET_HPLMN_CNF_STRU原语回复应用结果*/
/*#define DIAG_CMD_MM_SET_HPLMN                        (0x1000)*/

/* DIAG_CMD_MM_SET_UEID*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.2 APP_MM_SET_UEID_REQ_STRU*/
/*                        APP_MM_SET_UEID_CNF_STRU*/
/* 应用通过这条原语设置UEID，协议栈通过APP_MM_SET_UEID_CNF_STRU原语回复应用结果*/
#define DIAG_CMD_MM_SET_UEID                         (0x1001)

/* DIAG_CMD_MM_SET_PH_RA_MODE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.3 APP_MM_SET_PH_RA_MODE_REQ_STRU*/
/*                        APP_MM_SET_PH_RA_MODE_CNF_STRU*/
/* 设置LTE物理层接入模式选择：FDD和TDD*/
#define DIAG_CMD_MM_SET_PH_RA_MODE                   (0x1002)

/* DIAG_CMD_MM_SET_MS_CLASSMARK*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.4 APP_MM_SET_MS_CLASSMARK_REQ_STRU*/
/*                        APP_MM_SET_MS_CLASSMARK_CNF_STRU*/
/* 设置CLASSMARK*/
#define DIAG_CMD_MM_SET_MS_CLASSMARK               (0x1003)

/* DIAG_CMD_MM_SET_UE_NET_CAP*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.5 APP_MM_SET_UE_NET_CAP_REQ_STRU*/
/*                        APP_MM_SET_UE_NET_CAP_CNF_STRU*/
/* 设置UE NET CAP*/
#define DIAG_CMD_MM_SET_UE_NET_CAP                  (0x1004)

/* DIAG_CMD_MM_SET_MS_NET_CAP*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.6 APP_MM_SET_MS_NET_CAP_REQ_STRU*/
/*                        APP_MM_SET_MS_NET_CAP_CNF_STRU*/
/* 设置MS NET CAP*/
#define DIAG_CMD_MM_SET_MS_NET_CAP                  (0x1005)

/* DIAG_CMD_MM_SET_PLMN*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_PLMN_REQ_STRU*/
/*                  APP_MM_SET_PLMN_CNF_STRU*/

#define DIAG_CMD_MM_SET_PLMN                        (0x1006)

/* DIAG_CMD_MM_SET_LOCK_PLMN*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_LOCK_PLMN_REQ_STRU*/
/*                  APP_MM_SET_LOCK_PLMN_CNF_STRU*/

#define DIAG_CMD_MM_SET_LOCK_PLMN                    (0x1007)

/* DIAG_CMD_MM_SET_LAC*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_LAC_REQ*/
/*                  APP_MM_SET_LAC_CNF*/

/*#define DIAG_CMD_MM_SET_LAC                          (0x1008)*/

/* DIAG_CMD_MM_SET_RAC*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_RAC_REQ*/
/*                  APP_MM_SET_RAC_CNF*/

/*#define DIAG_CMD_MM_SET_RAC                          (0x1009)*/

/* DIAG_CMD_MM_SET_TAC*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_TAC_REQ*/
/*                  APP_MM_SET_TAC_CNF*/

#define DIAG_CMD_MM_SET_TAC                          (0x100a)

/* DIAG_CMD_MM_SET_CELL_ID*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_CELL_ID_REQ*/
/*                  APP_MM_SET_CELL_ID_CNF*/

/*#define DIAG_CMD_MM_SET_CELL_ID                      (0x100b)*/

/* DIAG_CMD_MM_SET_DRX*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_DRX_REQ_STRU*/
/*                  APP_MM_SET_DRX_CNF_STRU*/

#define DIAG_CMD_MM_SET_DRX                          (0x100c)

/* DIAG_CMD_MM_INQ_UEID*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_UEID_REQ_STRU*/
/*                  APP_MM_INQ_UEID_CNF_STRU*/

#define DIAG_CMD_MM_INQ_UEID                         (0x100d)

/* DIAG_CMD_MM_INQ_PLMN*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_PLMN_REQ_STRU*/
/*                  APP_MM_INQ_PLMN_CNF_STRU*/

#define DIAG_CMD_MM_INQ_PLMN                         (0x100e)

/* DIAG_CMD_MM_INQ_PH_RA_MODE*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_PH_RA_MODE_REQ_STRU*/
/*                  APP_MM_INQ_PH_RA_MODE_CNF_STRU*/

#define DIAG_CMD_MM_INQ_PH_RA_MODE                   (0x100f)

/* DIAG_CMD_MM_INQ_UE_NET_CAP*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_UE_NET_CAP_REQ_STRU*/
/*                  APP_MM_INQ_UE_NET_CAP_CNF_STRU*/

#define DIAG_CMD_MM_INQ_UE_NET_CAP                     (0x1010)

/* DIAG_CMD_MM_INQ_RAC*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_RAC_REQ*/
/*                  APP_MM_INQ_RAC_CNF*/

/*#define DIAG_CMD_MM_INQ_RAC                          (0x1011)*/

/* DIAG_CMD_MM_INQ_TAC*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_TAC_REQ*/
/*                  APP_MM_INQ_TAC_CNF*/

/*#define DIAG_CMD_MM_INQ_TAC                          (0x1012)*/

/* DIAG_CMD_MM_INQ_CELL_ID*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_INQ_CELL_ID_REQ*/
/*                  APP_MM_INQ_CELL_ID_CNF*/

/*#define DIAG_CMD_MM_INQ_CELL_ID                      (0x1013)*/

/* DIAG_CMD_MM_START*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.8 APP_MM_START_REQ_STRU*/
/*                  2.5.9 APP_MM_START_CNF_STRU*/
/* 应用通过这条原语启动协议栈，协议栈通过APP_MM_START_CNF原语回复应用开机结果。*/
/* 开机消息将会引发搜网和注册过程；*/
/* 若APP已经给协议栈发送了该消息，则在APP给协议栈发送APP_MM_STOP_REQ消息之前，*/
/* APP不应该再次向协议栈发送此消息*/
#define DIAG_CMD_MM_START                            (0x1014)

/* DIAG_CMD_MM_STOP*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.10 APP_MM_STOP_REQ_STRU*/
/*                  2.5.11 APP_MM_STOP_CNF_STRU*/
/* 应用通过这条原语通知协议栈关机；协议栈通过APP_MM_STOP_CNF原语回复应用关机结果*/
#define DIAG_CMD_MM_STOP                             (0x1015)

/* DIAG_CMD_MM_PLMN_SEL*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.12 APP_MM_PLMN_SEL_REQ_STRU*/
/*                  2.5.13 APP_MM_PLMN_SEL_CNF_STRU*/
/* APP通过这条原语，通知MM进行指定PLMN 选择，并在该PLMN上进行注册（见27007 COPS说明）*/
#define DIAG_CMD_MM_PLMN_SEL                         (0x1016)

/* DIAG_CMD_MM_PLMN_LIST*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.14 APP_MM_PLMN_LIST_REQ_STRU*/
/*                  2.5.15 APP_MM_PLMN_LIST_CNF_STRU*/
/* 应用通过该原语，查询当前所有PLMN 信息的列表，MM收到该原语，启动PLMN List搜索,*/
/* 并将结果通过APP_MM_PLMN_LIST_CNF上报给应用。*/
/* 结果上报需要一段时间，具体时长将来再细化(FFS)。*/
/* 在PLMN List搜索过程，应用可以通过APP_MM_ABORT_PLMN_LIST_REQ原语，随时中止搜索*/
#define DIAG_CMD_MM_PLMN_LIST                        (0x1017)

/* DIAG_CMD_MM_PLMN_LIST_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.16 APP_MM_PLMN_LIST_IND_STRU*/
/* 应用通过该原语，中止PLMN搜索过程，MM收到该原语，停止PLMN 搜索*/
#define DIAG_CMD_MM_PLMN_LIST_IND                    (0x1018)

/* DIAG_CMD_MM_ABORT_PLMN_SEL*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.17 APP_MM_ABORT_PLMN_SEL_REQ_STRU*/
/*                  2.5.18 APP_MM_ABORT_PLMN_SEL_CNF_STRU*/
/* 应用通过该原语，中止PLMN搜索过程，MM收到该原语，停止PLMN 搜索*/
#define DIAG_CMD_MM_ABORT_PLMN_SEL                   (0x1019)

/* DIAG_CMD_MM_PLMN_RESEL*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.19 APP_MM_PLMN_RESEL_REQ_STRU*/
/*                  2.5.20 APP_MM_PLMN_RESEL_CNF_STRU*/
/* 应用通过这条原语，通知MM设置网络重选，其中包括自动选择或者手工选择，*/
/* 协议栈会按此设置的重选方式执行一次网络重选。*/
/* MM通过APP_MM_PLMN_RESEL_CNF回复应用设置结果*/
#define DIAG_CMD_MM_PLMN_RESEL                       (0x101a)

/* DIAG_CMD_MM_ATTACH*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.21 APP_MM_ATTACH_REQ_STRU*/
/*                  2.5.22 APP_MM_ATTACH_CNF_STRU*/
/* 应用通过这条原语，通知MM发起ATTACH请求。*/
/* 上电后，APP发送APP_MM_START_REQ之前，此消息无效；*/
/* 非关机DETACH完成后，APP发送此消息给协议栈，将导致协议栈注册，但不会引发搜网；*/
/* 若协议栈正在注册过程中，收到APP发来的此消息，协议栈丢弃此消息；*/
/* 若协议栈已经注册成功，收到APP发来的此消息，协议栈直接返回注册成功；*/
#define DIAG_CMD_MM_ATTACH                           (0x101b)

/* DIAG_CMD_MM_ATTACH_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.23 APP_MM_ATTACH_IND*/
/* 网络发起re-attach的DETACH请求，UE在DETACH后，再次发起ATTACH请求，*/
/* 流程结束后，MM上报这条原语通知应用ATTACH结果*/
#define DIAG_CMD_MM_ATTACH_IND                       (0x101c)

/* DIAG_CMD_MM_DETACH*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.24 APP_MM_DETACH_REQ_STRU*/
/*                  2.5.25 APP_MM_DETACH_CNF_STRU*/
/* 应用通过这条原语，通知MM发起Detach*/
#define DIAG_CMD_MM_DETACH                           (0x101d)

/* DIAG_CMD_MM_DETACH_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.26 APP_MM_DETACH_IND*/
/* 网络发起Detach请求，UE收到请求后，上报这条原语通知应用*/
#define DIAG_CMD_MM_DETACH_IND                       (0x101e)

/* DIAG_CMD_MM_AREA_LOST_IND*/
/* IND*/
/* 针对PS提供接口:  APP_MM_AREA_LOST_IND_STRU*/

#define DIAG_CMD_MM_AREA_LOST_IND                    (0x101f)


/* DIAG_CMD_MM_TRANSPARENT_CMD*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.1.8.1 APP_MM_TRANSPARENT_CMD_REQ_STRU*/
/*                  2.1.8.2 APP_MM_TRANSPARENT_CMD_CNF_STRU*/
/* 发送给MM的Transparent命令*/
#define DIAG_CMD_MM_TRANSPARENT_CMD                  (0x1020)

/* DIAG_CMD_MM_TRANSPARENT_CMD_IND*/
/* IND*/
/* 针对PS提供接口:  2.1.8.3	OM_MM_TRANSPARENT_CMD_IND*/
/* MM收到Transparent命令后，可能会自动上报一些数据，*/
/* 这些数据可以通过OM_PS_TRANSPARENT_CMD_IND_STRU上报*/
/*#define DIAG_CMD_MM_TRANSPARENT_CMD_IND              (0x1021)*/

/* DIAG_CMD_ESM_SET_PCO*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.27 APP_ESM_SET_PCO_REQ_STRU*/
/*                  2.5.28 APP_ESM_SET_PCO_CNF_STRU*/
/* 应用通过这条原语设置指定承载上下文的PCO信息。*/
/* 用于传输与一个激活的PDP上下文相关的外部网络协议，*/
/* 以及传输与外部网络协议相关的附加数据*/
#define DIAG_CMD_ESM_SET_PCO                         (0x1022)

/* DIAG_CMD_ESM_SET_BEARER_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.29 APP_ESM_SET_BEARER_TYPE_REQ_STRU*/
/*                  2.5.30 APP_ESM_SET_BEARER_TYPE_CNF_STRU*/
/* 应用通过这条原语设置承载类型，若是专用承载，须设置相关联的缺省承载的CID*/
#define DIAG_CMD_ESM_SET_BEARER_TYPE                 (0x1023)

/* DIAG_CMD_ESM_SET_PDN_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.31 APP_ESM_SET_PDN_TYPE_REQ_STRU*/
/*                  2.5.32 APP_ESM_SET_PDN_TYPE_CNF_STRU*/
/* 应用通过这条原语设置UE请求PDN连接的IP地址版本信息*/
#define DIAG_CMD_ESM_SET_PDN_TYPE                    (0x1024)

/* DIAG_CMD_ESM_SET_APN*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.33 APP_ESM_SET_APN_REQ_STRU*/
/*                  2.5.34 APP_ESM_SET_APN_CNF_STRU*/
/* 应用通过这条原语设置APN参数，APN参数用于确定GPRS用户希望连接到的packet data network*/
/* 和通报希望连接MS的packet data network的接入点*/
#define DIAG_CMD_ESM_SET_APN                         (0x1025)

/* DIAG_CMD_ESM_SET_EPS_QOS_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.35 APP_ESM_SET_EPS_QOS_TYPE_REQ_STRU*/
/*                  2.5.36 APP_ESM_SET_EPS_QOS_TYPE_CNF*/
/* 应用通过这条原语设置EPS_QOS参数，在承载资源分配请求消息，*/
/* 向网络请求业务数据流SDF的Qos参数*/
/*#define DIAG_CMD_ESM_SET_EPS_QOS_TYPE                (0x1026)*/

/* DIAG_CMD_ESM_SET_TFT*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.37 APP_ESM_SET_TFT_REQ_STRU*/
/*                  2.5.38 APP_ESM_SET_TFT_CNF_STRU*/
/* 应用通过这条原语设置指定承载上下文的TFT信息。*/
/* 激活后的承载上下文如果使用TFT 参数，则将只处理满足该TFT 参数要求的数据包。*/
/* 设置承载上下文的TFT参数时，必须满足TFT 的参数组合要求。*/
/* 协议规定需要配置上下行TFT，本接口中是否只需配置上行，由SM从上行TFT中提取下行TFT参数（FFS）*/
#define DIAG_CMD_ESM_SET_TFT                         (0x1027)

/* DIAG_CMD_ESM_SET_EPS_QOS*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.39 APP_ESM_SET_EPS_QOS_REQ_STRU*/
/*                  2.5.40 APP_ESM_SET_EPS_QOS_CNF_STRU*/
/* 应用通过这条原语设置指定承载上下文的QoS信息。*/
/* 该服务质量在终端发起承载资源分配时上报给网络，网络根据实际情况，*/
/* 通知终端是否使用该服务质量，实际的服务质量可能被修改。*/
/* 实际的服务质量将在承载上下文激活成功的上报事件中报给应用；*/
/* 使用参数查询功能查询到的是用此原语设置的服务质量，可能不是实际的服务质量*/
#define DIAG_CMD_ESM_SET_EPS_QOS                     (0x1028)

/* ESM_SET_BEARER_MANAGER_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.41 APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU*/
/*                  2.5.42 APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU*/
/* 应用通过这条原语设置指定BEARER_MANAGER_TYPE信息。*/
/* 用于设置UE对承载建立请求的应答模式，和默认的应答结果*/
#define DIAG_CMD_ESM_SET_PDP_MANAGER_TYPE            (0x1029)

/* DIAG_CMD_ESM_QUERY_TFT*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.43 APP_ESM_INQ_TFT_REQ_STRU*/
/*                  2.5.44 APP_ESM_INQ_TFT_CNF_STRU*/
/* 应用通过这条原语查询指定承载上下文的TFT信息*/
#define DIAG_CMD_ESM_INQ_TFT                       (0x102a)

/* DIAG_CMD_ESM_QUERY_QOS*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.45 APP_ESM_QUERY_QOS_REQ*/
/*                  2.5.46 APP_ESM_QUERY_QOS_CNF*/
/* 应用通过这条原语查询指定承载上下文的QoS信息*/
#define DIAG_CMD_ESM_QUERY_QOS                       (0x102b)

/* DIAG_CMD_ESM_QUERY_PCO*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.47 APP_ESM_QUERY_PCO_REQ*/
/*                  2.5.48 APP_ESM_QUERY_PCO_CNF*/
/* 应用通过这条原语查询指定承载上下文的PCO信息*/
#define DIAG_CMD_ESM_INQ_PCO                         (0x102c)

/* DIAG_CMD_ESM_QUERY_BEARER_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.49 APP_ESM_QUERY_BEARER_TYPE_REQ*/
/*                  2.5.50 APP_ESM_QUERY_BEARER_TYPE_CNF*/
/* 应用通过这条原语查询指定承载上下文的承载类型，*/
/* 若为专有承载，应返回相关联的缺省承载CID*/
#define DIAG_CMD_ESM_INQ_BEARER_TYPE                 (0x102d)

/* DIAG_CMD_ESM_QUERY_PDN_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.51 APP_ESM_QUERY_PDN_TYPE_REQ*/
/*                  2.5.52 APP_ESM_QUERY_PDN_TYPE_CNF*/
/* 应用通过这条原语查询指定承载上下文的PDN_CONN_TYPE信息*/
#define DIAG_CMD_ESM_INQ_PDN_TYPE                    (0x102e)

/* DIAG_CMD_ESM_QUERY_EPS_QOS*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.53 APP_ESM_QUERY_EPS_QOS_REQ*/
/*                  2.5.54 APP_ESM_QUERY_EPS_QOS_CNF*/
/* 应用通过这条原语查询指定承载上下文的EPS QOS信息*/
#define DIAG_CMD_ESM_INQ_EPS_QOS                     (0x102f)

/* DIAG_CMD_ESM_QUERY_APN*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.55 APP_ESM_QUERY_APN_REQ*/
/*                  2.5.56 APP_ESM_QUERY_APN_CNF*/
/* 应用通过这条原语查询指定承载上下文的APN参数*/
#define DIAG_CMD_ESM_INQ_APN                         (0x1030)

/* DIAG_CMD_ESM_SET_BEARER_MANAGER_TYPE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.57 APP_ESM_QUERY_BEARER_MANAGER_TYPE_REQ*/
/*                  2.5.58 APP_ESM_QUERY_BEARER_MANAGER_TYPE_CNF*/
/* 应用通过这条原语，设置终端对承载激活或修改进行自动或人工应答*/
#define DIAG_CMD_ESM_INQ_PDP_MANAGER_TYPE            (0x1031)

/* DIAG_CMD_ESM_PDP_SETUP*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.59 APP_ESM_PDP_SETUP_REQ_STRU*/
/*                  2.5.60 APP_ESM_PDP_SETUP_CNF_STRU*/
/* 应用通过这条原语，通知SM发起承载资源建立；*/
/* 网络收到承载资源分配消息后，发起专有承载激活或承载修改流程*/
#define DIAG_CMD_ESM_PDP_SETUP                       (0x1032)

/* DIAG_CMD_ESM_PDP_SETUP_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.61 APP_ESM_PDP_SETUP_IND_STRU*/
/* 网络主动发起承载激活流程，SM将结果上报给应用。在网络发起的承载激活流程中，*/
/* SM会占用已去激活承载的CID或从未被使用的CID，并在上报消息中将CID报给应用*/
#define DIAG_CMD_ESM_PDP_SETUP_IND                   (0x1033)

/* DIAG_CMD_ESM_PDP_MODIFY*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.62 APP_ESM_PDP_MODIFY_REQ_STRU*/
/*                  2.5.63 APP_ESM_PDP_MODIFY_CNF_STRU*/
/* FFS*/
#define DIAG_CMD_ESM_PDP_MODIFY                      (0x1034)

/* DIAG_CMD_ESM_PDP_MODIFY_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.64 APP_ESM_PDP_MODIFY_IND_STRU*/
/* 网络发起承载修改流程，流程结束后，SM通过这条原语将结果通知APP*/
#define DIAG_CMD_ESM_PDP_MODIFY_IND                  (0x1035)

/* DIAG_CMD_ESM_PDP_RELEASE*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.5.65 APP_ESM_PDP_RELEASE_REQ_STRU*/
/*                  2.5.66 APP_ESM_PDP_RELEASE_CNF_STRU*/
/* 应用通过这条原语，通知SM释放承载资源*/
#define DIAG_CMD_ESM_PDP_RELEASE                     (0x1036)

/* DIAG_CMD_ESM_PDP_RELEASE_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.67 APP_ESM_PDP_RELEASE_IND_STRU*/
/* 网络主动发起承载资源释放流程，流程结束后，*/
/* SM通过这条原语，通知应用对应CID的承载资源被释放*/
#define DIAG_CMD_ESM_PDP_RELEASE_IND                 (0x1037)

/* DIAG_CMD_ESM_PDP_MANAGER_IND*/
/* IND*/
/* 针对PS提供接口:  2.5.68 APP_ESM_PDP_MANAGER_IND_STRU*/
/* 在承载资源管理手动模式下，SM通过这条原语，通知应用网络正在激活或修改承载资源,*/
/* 应用需回复APP_ESM_PDP_MANAGER_RSP原语，告知SM是否接收请求*/
#define DIAG_CMD_ESM_PDP_MANAGER_IND                 (0x1038)

/* DIAG_CMD_ESM_PDP_MANAGER_RSP*/
/* RSP*/
/* 针对PS提供接口:  2.5.69 APP_ESM_PDP_MANAGER_RSP_STRU*/
/* 这条原语是对APP_ESM_BEARER_MANAGER_IND原语的响应。*/
/* 在资源管理手动模式下，应用通过这条原语，通知SM是否接收承载资源的激活或修改请求。*/
/* 如果在一定时间内（时长FFS），没有收到应用的回复，SM认为应用不接收承载资源的分配或修改请求*/
#define DIAG_CMD_ESM_PDP_MANAGER_RSP                 (0x1039)

/* DIAG_CMD_ESM_TRANSPARENT_CMD*/
/* REQ/CNF*/
/* 针对PS提供接口:  2.1.8.4	OM_ESM_TRANSPARENT_CMD_REQ*/
/*                  2.1.8.5	OM_ESM_TRANSPARENT_CMD_CNF*/
/* 发送给ESM的Transparent命令*/
/*#define DIAG_CMD_ESM_TRANSPARENT_CMD                 (0x103a)*/

/* DIAG_CMD_ESM_TRANSPARENT_CMD_IND*/
/* IND*/
/* 针对PS提供接口:  2.1.8.6 OM_ESM_TRANSPARENT_CMD_IND*/
/* ESM收到Transparent命令后，可能会自动上报一些数据，*/
/* 这些数据可以通过OM_PS_TRANSPARENT_CMD_IND_STRU上报*/
/*#define DIAG_CMD_ESM_TRANSPARENT_CMD_IND             (0x103b)*/

/* DIAG_CMD_ESM_INQ_DYNAMIC_ESP_QOS*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU*/
/*                  APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU*/
#define DIAG_CMD_ESM_INQ_DYNAMIC_ESP_QOS             (0x103c)

/* DIAG_CMD_ESM_INQ_DYNAMIC_TFT*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU*/
/*                  APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU*/
#define DIAG_CMD_ESM_INQ_DYNAMIC_TFT                 (0x103d)

/* DIAG_CMD_MM_SET_SMC*/
/* REQ/CNF*/
/* 针对PS提供接口:  APP_MM_SET_SMC_REQ_STRU*/
/*                  APP_MM_SET_SMC_CNF_STRU*/
#define DIAG_CMD_MM_SET_SMC                          (0x103e)

/* DIAG_CMD_MM_REG_STAT_IND*/
/* IND*/
/* 针对PS提供接口:  APP_MM_REG_STAT_IND*/

#define DIAG_CMD_MM_REG_STAT_IND                     (0x103f)

#define DIAG_CMD_MM_INQ_MS_CLASSMARK                 (0x1061)

#define DIAG_CMD_MM_INQ_MS_NET_CAP                   (0x1063)
#define DIAG_CMD_MM_INQ_DRX                          (0x1064)

#define DIAG_CMD_MM_INQ_MM_INFO                      (0x1066)
#define DIAG_CMD_MM_INQ_MM_INFO_IND                  (0x1067)
/*****************************************************************************
     NAS 透传指令 END
*****************************************************************************/

/*****************************************************************************
 PS 新添加消息 BEGIN
*****************************************************************************/




#define DIAG_CMD_APP_RRC_TRANSPARENT_CMD      (0x106b)
#define DIAG_CMD_APP_RRC_TRANSPARENT_CMD_IND  (0x106c)
#define DIAG_CMD_RRC_CELL_MEAS_RPT            (0x106d)
#define DIAG_CMD_RRC_CELL_MEAS_RPT_IND        (0x106e)
#define DIAG_CMD_RRC_TIME_DELAY_RPT           (0x106f)
#define DIAG_CMD_RRC_TIME_DELAY_RPT_IND       (0x1070)
#define DIAG_CMD_RRC_INQ_CAMP_CELL_INFO       (0x1071)
#define DIAG_CMD_RRC_INQ_CAMP_CELL_INFO_IND   (0x1072)
#define DIAG_CMD_APP_RRC_LOCK_WORK_INFO       (0x1073)

/*****************************************************************************
 PS 新添加消息 END
*****************************************************************************/

/*****************************************************************************
 L2 新添加透传指令，根据L2新需求添加
 问题单号：BJ9D01040
 同步序号：BJ9TB00026
*****************************************************************************/

#define DIAG_CMD_MAC_TRANSPARENT_CMD          (0x1074)
#define DIAG_CMD_MAC_TRANSPARENT_CMD_IND      (0x1075)
#define DIAG_CMD_RLC_TRANSPARENT_CMD          (0x1076)
#define DIAG_CMD_RLC_TRANSPARENT_CMD_IND      (0x1077)
#define DIAG_CMD_PDCP_TRANSPARENT_CMD         (0x1078)
#define DIAG_CMD_PDCP_TRANSPARENT_CMD_IND     (0x1079)
/*#define DIAG_CMD_L2_THROUGHPUT_CMD_REQ        (0x107a)*/
/*#define DIAG_CMD_L2_THROUGHPUT_CMD_IND        (0x107b)*/
/*Added for 数传可维可测*/
#define DIAG_CMD_OM_L2_THROUGHPUT_CMD_REQ     (0x107c)

#define DIAG_CMD_L2_OM_THROUGHPUT_CMD_IND     (0x107d)

#define DIAG_CMD_L2_OM_KEYEVENT_CMD_IND       (0x107e)

#define DIAG_CMD_L2_OM_SDUCOUNT_CMD_REQ       (0x107f)
#define DIAG_CMD_L2_OM_SDUCOUNT_CMD_IND       (0x1080)

#define DIAG_CMD_PS_OM_CAMPEDCELL_CMD_REQ     (0x1081)
#define DIAG_CMD_PS_OM_CAMPEDCELL_CMD_IND     (0x1082)

#define DIAG_CMD_PS_OM_HANDOVER_CMD_REQ       (0x1083)
#define DIAG_CMD_PS_OM_HANDOVER_CMD_IND       (0x1084)

#define DIAG_CMD_PS_OM_PRACH_SR_CMD_REQ       (0x1085)
#define DIAG_CMD_PS_OM_PRACH_SR_CMD_IND       (0x1086)

#define DIAG_CMD_PS_OM_BSR_CMD_REQ            (0x1087)
#define DIAG_CMD_PS_OM_BSR_CMD_IND            (0x1088)

/*LTE L2 路测新增*/
#define DIAG_CMD_OM_L2_DT_RA_INFO_CMD_REQ       (0x1089)
#define DIAG_CMD_L2_OM_DT_RA_INFO_CMD_IND       (0x108A)
#define DIAG_CMD_OM_L2_DT_RB_INFO_CMD_REQ       (0x108B)
#define DIAG_CMD_L2_OM_DT_RB_INFO_CMD_IND       (0x108C)
#define DIAG_CMD_OM_L2_DT_HO_LATENCY_CMD_REQ    (0x108D)
#define DIAG_CMD_L2_OM_DT_HO_LATENCY_CMD_IND    (0x108F)

#define DIAG_CMD_RRC_APP_PTL_STATE_QUERY_CNF    (0x1090)
#define DIAG_CMD_OM_L2_DT_CONTENT_TMR_CMD_REQ   (0x1091)
#define DIAG_CMD_L2_OM_DT_CONTENT_TMR_CMD_IND   (0x1092)
#define DIAG_CMD_OM_L2_DT_SR_STATUS_CMD_REQ     (0x1093)
#define DIAG_CMD_L2_OM_DT_SR_STATUS_CMD_IND     (0x1094)

/*LTE RRC路测新增 */
/* niuxiufan DT begin */
#define DIAG_CMD_APP_RRC_SERVING_CELL_INFO_REQ (0x1095)
#define DIAG_CMD_RRC_APP_SERVING_CELL_INFO_IND (0x1096)

#define DIAG_CMD_APP_RRC_CSEL_INFO_REQ         (0x1097)
#define DIAG_CMD_RRC_APP_LTE_CSEL_INFO_IND     (0x1098)
#define DIAG_CMD_RRC_APP_UTRA_CSEL_INFO_IND    (0x1099)
#define DIAG_CMD_RRC_APP_GERAN_CSEL_INFO_IND   (0x109a)

#define DIAG_CMD_APP_RRC_UE_CAP_INFO_REQ       (0x109b)
#define DIAG_CMD_RRC_APP_UE_CAP_INFO_IND       (0x109c)

#define DIAG_CMD_APP_RRC_AC_BARRING_INFO_REQ   (0x109d)
#define DIAG_CMD_RRC_APP_AC_BARRING_INFO_IND   (0x109e)

#define DIAG_CMD_APP_RRC_UE_DRX_INFO_REQ       (0x109f)
#define DIAG_CMD_RRC_APP_UE_DRX_INFO_IND       (0x10a0)

#define DIAG_CMD_APP_RRC_PTL_STATE_REQ         (0x10a1)
#define DIAG_CMD_RRC_APP_PTL_STATE_IND         (0x10a2)


#define DIAG_CMD_APP_EMM_GUTI_INFO_REQ         (0x10a3)
#define DIAG_CMD_EMM_APP_GUTI_INFO_IND         (0x10a4)

#define DIAG_CMD_APP_EMM_IMSI_INFO_REQ         (0x10a5)
#define DIAG_CMD_EMM_APP_IMSI_INFO_IND         (0x10a6)

#define DIAG_CMD_APP_EMM_EMM_STATE_REQ         (0x10a7)
#define DIAG_CMD_EMM_APP_EMM_STATE_IND         (0x10a8)

#define DIAG_CMD_APP_ESM_PDP_INFO_REQ          (0x10a9)
#define DIAG_CMD_EMM_APP_PDP_INFO_IND          (0x10aa)

#define DIAG_CMD_APP_RRC_LOCK_NET_REQ          (0x10ab)

#define DIAG_CMD_EMM_APP_EMM_INFO_IND           (0x10ac)
#define DIAG_CMD_ESM_APP_ESM_INFO_IND           (0x10ad)
#define DIAG_CMD_EMM_INFO_REPORT                (0x10ae)
#define DIAG_CMD_ESM_INFO_REPORT                (0x10af)


/* niuxiufan DT end */

#define DIAG_CMD_TLPS_PRINT2LAYER_IND           (0x10b0)


#define DIAG_CMD_RRC_APP_END                    (0x109F)


/*TDS BEGIN*/
#define DIAG_CMD_TDS_L2_THROUGHPUT_REQ          (0x1100)
#define DIAG_CMD_TDS_L2_THROUGHPUT_IND          (0x1101)

#define DIAG_CMD_TDS_RRC_BASICINFO_REQ          (0x1102)
#define DIAG_CMD_TDS_RRC_BASICINFO_IND          (0x1103)

#define DIAG_CMD_TDS_MAC_CELL_MEAS_REQ          (0x1104)
#define DIAG_CMD_TDS_MAC_CELL_MEAS_IND          (0x1105)

#define DIAG_CMD_TDS_L2_THROUGHPUT_SG_REQ       (0x1106)
#define DIAG_CMD_TDS_L2_THROUGHPUT_SG_IND       (0x1107)

/*DCM logger*/
#define DIAG_CMD_LTE_DCM_MAC_PDU_INFO_REQ       (0x1108)
#define DIAG_CMD_LTE_DCM_MAC_BSR_INFO_REQ       (0x1109)
#define DIAG_CMD_LTE_DCM_MAC_BSR_INFO_IND       (0x110A)
/*end DCM*/

#define DIAG_CMD_TDS_HSDPA_INFO_IND             (0x110B)
#define DIAG_CMD_TDS_L2_RB_INFO_IND             (0x110C)

/* TDS CMCC Begin */
#define DIAG_CMD_TDS_RRC_MEAS_GSM_REQ           (0x110D)
#define DIAG_CMD_TDS_RRC_MEAS_GSM_IND           (0x110E)

#define DIAG_CMD_TDS_RRC_3A_INFO_REQ            (0x110F)
#define DIAG_CMD_TDS_RRC_3A_INFO_IND            (0x1110)
/* TDS CMCC End */

#define DIAG_CMD_RRC_APP_SERVING_CELL_INFO_CA_IND (0x1202)

#define DIAG_CMD_L2_OM_SWITCH_CONTROL_REQ       (0x1203)

#define DIAG_CMD_RRC_SERV_IDLE_INFO_IND        (0x1204)
#define DIAG_CMD_RRC_INTRA_IDLE_INFO_IND       (0x1205)
#define DIAG_CMD_RRC_INTER_IDLE_INFO_IND       (0x1206)
#define DIAG_CMD_RRC_WCDMA_IDLE_INFO_IND       (0x1207)
#define DIAG_CMD_RRC_TDS_IDLE_INFO_IND         (0x1208)
#define DIAG_CMD_RRC_GERAN_IDLE_INFO_IND       (0x1209)

#define DIAG_CMD_RRC_SERV_MEAS_RSLT_IND   (0x120A)
#define DIAG_CMD_RRC_INTRA_MEAS_RSLT_IND  (0x120B)
#define DIAG_CMD_RRC_INTER_MEAS_RSLT_IND  (0x120C)
#define DIAG_CMD_RRC_SCELL_MEAS_RSLT_IND  (0x120D)
#define DIAG_CMD_RRC_UTRAN_MEAS_RSLT_IND  (0x120E)
#define DIAG_CMD_RRC_GERAN_MEAS_RSLT_IND  (0x120F)

/* begin: add for 路测融合 */
#define DIAG_CMD_LRRC_MEAS_RPT_REQ              (0x1210)
#define DIAG_CMD_LRRC_MEAS_INFO_IND             (0x1211)
#define DIAG_CMD_LRRC_SYNC_RPT_REQ              (0x1212)
#define DIAG_CMD_LRRC_SYNC_INFO_IND             (0x1213)
#define DIAG_CMD_LRRC_OUT_OF_SYNC_INFO_IND      (0x1214)
/* end: add for 路测融合 */

/*****************************************************************************
 L2 新添加透传指令，根据L2新需求添加 END
*****************************************************************************/

/*----------------------------------------------------------------------------*/
/*TL用户面新增透明命令: 0x2000-0x2FFF, added by hujianbo, 20140108, begin     */
/*----------------------------------------------------------------------------*/

/*TL用户面事件上报*/
#define DIAG_CMD_L2_OM_UP_EVENT_REQ             (0x2000)
#define DIAG_CMD_L2_OM_UP_EVENT_CNF             (0x2001)

#define DIAG_CMD_L2_OM_SINGLE_UP_EVENT_IND      (0x2002)
#define DIAG_CMD_L2_OM_ALL_UP_EVENT_ACCUL_IND   (0x2003)    /*累计量*/
#define DIAG_CMD_L2_OM_ALL_UP_EVENT_DELTA_IND   (0x2004)    /*增量*/

/*TL用户面各层统计量上报*/
#define DIAG_CMD_TL_STAT_REQ                    (0x2100)
#define DIAG_CMD_TL_STAT_CNF                    (0x2101)

#define DIAG_CMD_CDS_STAT_IND_BASE              (0x2102)
/*More CDS stat ind can added here*/
#define DIAG_CMD_CDS_IPF_PROC_STAT_IND          (0x2103)
#define DIAG_CMD_CDS_UL_IP_PKT_STAT_IND         (0x2104)
#define DIAG_CMD_CDS_DL_SDU_STAT_IND            (0x2105)
#define DIAG_CMD_CDS_LOOP_BACK_STAT_IND         (0x2106)
#define DIAG_CMD_CDS_IMS_PROC_STAT_IND          (0x2107)
#define DIAG_CMD_CDS_UL_IP_PKT_INFO_IND         (0x2108)
#define DIAG_CMD_CDS_DL_IP_PKT_INFO_IND         (0x2109)

#define DIAG_CMD_TDS_PDCP_STAT_SINGLE_RB_IND    (0x2120)
#define DIAG_CMD_TDS_PDCP_STAT_ALL_RB_IND       (0x2121)
/*More TDS PDCP stat ind can added here*/

#define DIAG_CMD_TDS_RLC_STAT_SINGLE_RB_IND     (0x2140)
#define DIAG_CMD_TDS_RLC_STAT_ALL_RB_IND        (0x2141)
/*More TDS RLC stat ind can added here*/

#define DIAG_CMD_TDS_MAC_STAT_IND               (0x2160)
/*More TDS MAC stat ind can added here*/

#define DIAG_CMD_LTE_PDCP_STAT_IND              (0x2180)
/*More LTE PDCP stat ind can added here*/
#define DIAG_CMD_LTE_PDCP_UL_RB_STAT_IND        (0x2181)
#define DIAG_CMD_LTE_PDCP_DL_RB_STAT_IND        (0x2182)
#define DIAG_CMD_LTE_PDCP_ALL_RB_STAT_IND       (0x2183)
#define DIAG_CMD_LTE_PDCP_UL_PDU_INFO_IND       (0x2184)
#define DIAG_CMD_LTE_PDCP_DL_PDU_INFO_IND       (0x2185)
#define DIAG_CMD_LTE_PDCP_DL_SDU_INFO_IND       (0x2186)
#define DIAG_CMD_LTE_PDCP_UL_PKT_COMPRESS_IND   (0x2187)
#define DIAG_CMD_LTE_PDCP_DL_SDU_DECOMP_IND     (0x2188)
#define DIAG_CMD_LTE_PDCP_CIPHER_CH_STAT_IND    (0x2189)

#define DIAG_CMD_LTE_RLC_STAT_IND               (0x21A0)
/*More LTE RLC stat ind can added here*/
#define DIAG_CMD_LTE_RLC_UL_RB_STAT_IND         (0x21A1)
#define DIAG_CMD_LTE_RLC_DL_RB_STAT_IND         (0x21A2)
#define DIAG_CMD_LTE_RLC_UL_ALL_STAT_IND        (0x21A3)
#define DIAG_CMD_LTE_RLC_DL_ALL_STAT_IND        (0x21A4)
#define DIAG_CMD_LTE_RLC_UL_PDU_INFO_IND        (0x21A5)
#define DIAG_CMD_LTE_RLC_DL_PDU_INFO_IND        (0x21A6)
#define DIAG_CMD_LTE_RLC_AM_CTRL_PDU_INFO_IND   (0x21A7)

#define DIAG_CMD_LTE_MAC_STAT_IND_BASE          (0x21C0)
/*More LTE MAC stat ind can added here*/
#define DIAG_CMD_LTE_MAC_RA_STAT_IND            (0x21C1)
#define DIAG_CMD_LTE_MAC_UL_STAT_IND            (0x21C2)
#define DIAG_CMD_LTE_MAC_DL_STAT_IND            (0x21C3)
#define DIAG_CMD_LTE_MAC_CA_STAT_IND            (0x21C4)
#define DIAG_CMD_LTE_MAC_MBMS_STAT_IND          (0x21C5)
#define DIAG_CMD_LTE_MAC_UL_PDU_INFO_IND        (0x21C6)
#define DIAG_CMD_LTE_MAC_DL_PDU_INFO_IND        (0x21C7)
#define DIAG_CMD_LTE_MAC_REG_BSR_SR_INFO_IND    (0x21C8)
#define DIAG_CMD_LTE_MAC_BUFFER_STATUS_IND      (0x21CA)

#define DIAG_CMD_LTE_ROHC_COMP_STAT_IND         (0x21CB)
#define DIAG_CMD_LTE_ROHC_DECOMP_STAT_IND       (0x21CC)

#define DIAG_CMD_LTE_MAC_PHR_TRIGGER_INFO       (0x21CD)
#define DIAG_CMD_LTE_MAC_UL_GRANT_IND           (0x21CE)
#define DIAG_CMD_LTE_MAC_DL_ASSIGN_IND          (0x21CF)


#define DIAG_CMD_TDS_L2_OVERVIEW_STAT_IND       (0x21E0)
#define DIAG_CMD_LTE_L2_OVERVIEW_STAT_IND       (0x2200)
#define DIAG_CMD_LTE_UP_LATENCY_RPT_IND         (0x2201)


#define DIAG_CMD_LTE_ROHC_PKT_CAPTURE_IND               (0x2202)
#define DIAG_CMD_LTE_ROHC_COMPRESS_CTX_INFO_IND         (0x2203)
#define DIAG_CMD_LTE_ROHC_DECOMPRESS_CTX_INFO_IND       (0x2204)


/*TL用户面各层参数配置上报*/
#define DIAG_CMD_LT_CFG_REQ                     (0x2300)
#define DIAG_CMD_LT_CFG_CNF

#define DIAG_CMD_CDS_CFG_IND
#define DIAG_CMD_TDS_PDCP_CFG_IND
#define DIAG_CMD_TDS_RLC_CFG_IND
#define DIAG_CMD_TDS_MAC_CFG_IND
#define DIAG_CMD_LTE_PDCP_CFG_IND
#define DIAG_CMD_LTE_RLC_CFG_IND
#define DIAG_CMD_LTE_MAC_CFG_IND


/*TL用户面各层PDU头上报*/
#define DIAG_CMD_LTE_PDCP_HEAD_REQ              (0x2400)
#define DIAG_CMD_LTE_PDCP_HEAD_IND

#define DIAG_CMD_LTE_RLC_HEAD_REQ
#define DIAG_CMD_LTE_RLC_HEAD_IND

#define DIAG_CMD_LTE_MAC_HEAD_REQ
#define DIAG_CMD_LTE_MAC_HEAD_IND

#define DIAG_CMD_TDS_PDCP_HEAD_REQ
#define DIAG_CMD_TDS_PDCP_HEAD_IND

#define DIAG_CMD_TDS_RLC_HEAD_REQ
#define DIAG_CMD_TDS_RLC_HEAD_IND

#define DIAG_CMD_TDS_MAC_HEAD_REQ
#define DIAG_CMD_TDS_MAC_HEAD_IND

/*TL用户面TCP钩包上报*/
#define DIAG_CMD_LT_TCP_CAP_REQ                 (0x2500)
#define DIAG_CMD_LT_TCP_IND_REQ

#define DIAG_CMD_LT_L2_END                      (0x2FFF)

/*V7R2-DT增加CA L2吞吐量IND消息宏定义的代码 q00208938 2014/03/24，begin*/
#define DIAG_CMD_CA_L2_OM_THROUGHPUT_CMD_IND      (0x1500)
/*V7R2-DT增加CA L2吞吐量IND消息宏定义的代码 q00208938 2014/03/24，end*/

/*----------------------------------------------------------------------------*/
/*TL用户面新增透明命令: 0x2000-0x2FFF, added by hujianbo, 20140108, end       */
/*----------------------------------------------------------------------------*/



/*****************************************************************************
 PS 协议栈 透传指令END
*****************************************************************************/



#endif /*__DIAG_PS_TRANS_CMD_ID_H__*/




