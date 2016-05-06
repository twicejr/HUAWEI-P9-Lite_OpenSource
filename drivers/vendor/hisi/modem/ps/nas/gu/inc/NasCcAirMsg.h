/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcAirMsg.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月28日
  最近修改   : 2007年8月28日
  功能描述   : 定义CC空口消息的消息类型和每种消息的内容
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月28日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/
#ifndef  NAS_CC_AIR_MSG_H
#define  NAS_CC_AIR_MSG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasCcIe.h"
#include "NasSsIe.h"
#include "NasAirMsgHdr.h"


/*****************************************************************************
  2 类型定义
*****************************************************************************/


/******************************************************************************/
/* Messages for circuit-switched call control (24.008)                        */
/******************************************************************************/

/* 9.3 Messages for circuit-switched call control */
enum NAS_CC_MSG_TYPE_ENUM                                                            /* Table 9.54/3GPP TS 24.008            */
{                                                                               /* 8 7 6 5 4 3 2 1                      */
/* Call establishment messages: */                                              /* x x 0 0 - - - -                      */
    NAS_CC_MSG_ALERTING                                     = 0x01,             /*         0 0 0 1 - ALERTING           */
    NAS_CC_MSG_CALL_CNF                                     = 0x08,             /*         1 0 0 0 - CALL CONFIRMED     */
    NAS_CC_MSG_CALL_PROC                                    = 0x02,             /*         0 0 1 0 - CALL PROCEEDING    */
    NAS_CC_MSG_CONNECT                                      = 0x07,             /*         0 1 1 1 - CONNECT            */
    NAS_CC_MSG_CONNECT_ACK                                  = 0x0F,             /*         1 1 1 1 - CONNECT ACK        */
    NAS_CC_MSG_EMERGENCY_SETUP                              = 0x0E,             /*         1 1 1 0 - EMERGENCY SETUP    */
    NAS_CC_MSG_PROGRESS                                     = 0x03,             /*         0 0 1 1 - PROGRESS           */
    NAS_CC_MSG_CC_EST                                       = 0x04,             /*         0 1 0 0 - CC-EST             */
    NAS_CC_MSG_CC_EST_CNF                                   = 0x06,             /*         0 1 1 0 - CC-EST CNF         */
    NAS_CC_MSG_RECALL                                       = 0x0B,             /*         1 0 1 1 - RECALL             */
    NAS_CC_MSG_START_CC                                     = 0x09,             /*         1 0 0 1 - START CC           */
    NAS_CC_MSG_SETUP                                        = 0x05,             /*         0 1 0 1 - SETUP              */
/* Call information phase messages: */                                          /* x x 0 1 - - - -                      */
    NAS_CC_MSG_MODIFY                                       = 0x17,             /*         0 1 1 1 - MODIFY             */
    NAS_CC_MSG_MODIFY_COMPLETE                              = 0x1F,             /*         1 1 1 1 - MODIFY COMPLETE    */
    NAS_CC_MSG_MODIFY_REJ                                   = 0x13,             /*         0 0 1 1 - MODIFY REJECT      */
    NAS_CC_MSG_USER_INFO                                    = 0x10,             /*         0 0 0 0 - USER INFORMATION   */
    NAS_CC_MSG_HOLD                                         = 0x18,             /*         1 0 0 0 - HOLD               */
    NAS_CC_MSG_HOLD_ACK                                     = 0x19,             /*         1 0 0 1 - HOLD ACK           */
    NAS_CC_MSG_HOLD_REJ                                     = 0x1A,             /*         1 0 1 0 - HOLD REJ           */
    NAS_CC_MSG_RETRIEVE                                     = 0x1C,             /*         1 1 0 0 - RETRIEVE           */
    NAS_CC_MSG_RETRIEVE_ACK                                 = 0x1D,             /*         1 1 0 1 - RETRIEVE ACK       */
    NAS_CC_MSG_RETRIEVE_REJ                                 = 0x1E,             /*         1 1 1 0 - RETRIEVE REJ       */
/* Call clearing messages: */                                                   /* x x 1 0 - - - -                      */
    NAS_CC_MSG_DISCONNECT                                   = 0x25,             /*         0 1 0 1 - DISCONNECT         */
    NAS_CC_MSG_RELEASE                                      = 0x2D,             /*         1 1 0 1 - RELEASE            */
    NAS_CC_MSG_RELEASE_COMPLETE                             = 0x2A,             /*         1 0 1 0 - RELEASE COMPLETE   */
/* Miscellaneous messages: */                                                   /* x x 1 1 - - - -                      */
    NAS_CC_MSG_CONGESTION_CTRL                              = 0x39,             /*         1 0 0 1 - CONGESTION CTRL    */
    NAS_CC_MSG_NOTIFY                                       = 0x3E,             /*         1 1 1 0 - NOTIFY             */
    NAS_CC_MSG_STATUS                                       = 0x3D,             /*         1 1 0 1 - STATUS             */
    NAS_CC_MSG_STATUS_ENQUIRY                               = 0x34,             /*         0 1 0 0 - STATUS ENQUIRY     */
    NAS_CC_MSG_START_DTMF                                   = 0x35,             /*         0 1 0 1 - START DTMF         */
    NAS_CC_MSG_STOP_DTMF                                    = 0x31,             /*         0 0 0 1 - STOP DTMF          */
    NAS_CC_MSG_STOP_DTMF_ACK                                = 0x32,             /*         0 0 1 0 - STOP DTMF ACK      */
    NAS_CC_MSG_START_DTMF_ACK                               = 0x36,             /*         0 1 1 0 - START DTMF ACK     */
    NAS_CC_MSG_START_DTMF_REJ                               = 0x37,             /*         0 1 1 1 - START DTMF REJ     */
    NAS_CC_MSG_FACILITY                                     = 0x3A,             /*         1 0 1 0 - FACILITY           */


/* 自定义消息ID,与协议消息预留8个空位 */
    NAS_CC_MSG_EST_SETUP                                    = 0x47              /*非协议中定义的消息类型，只是为了二次解析CC-EST消息中NAS_CC_IE_SETUP_CONTAINER_STRU的SetupMessage[NAS_CC_MAX_SETUP_MSG_LEN]*/
};
typedef VOS_UINT8 NAS_CC_MSG_TYPE_ENUM_U8;


/* [9.3.1] Alerting */
/*============================================================================*/
/* 9.3.1.1 Alerting (network to mobile station direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Alerting Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │1E  │Progress indicator      │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_PROGRESS_INDICATOR_STRU   stProgInd;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
}NAS_CC_MSG_ALERTING_MT_STRU;


/* 9.3.1.2 Alerting (mobile station to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Alerting Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │SS version              │    O     │  TLV   │  2-3   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSversion;
}NAS_CC_MSG_ALERTING_MO_STRU;


/* [9.3.2] Call confirmed */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Call confirmed          │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │Repeat Indicator        │    C     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 1     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 2     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │1E  │Progress indicator      │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │2D  │Stream Identifier       │    O     │  TLV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │40  │Supported Codec List    │    O     │  TLV   │  5-n   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stRepeatInd;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_CC_CAP_STRU               stCCCap;
    NAS_CC_IE_STREAM_IDENTIFIER_STRU    stStreamID;
    NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU stCodecList;
}NAS_CC_MSG_CALL_CNF_STRU;


/* [9.3.3] Call proceeding */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Call proceeding         │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │Repeat Indicator        │    C     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 1     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 2     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │1E  │Progress Indicator      │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │2D  │Priority granted        │    O     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │2F  │Network CC cap.         │    O     │  TLV   │   3    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stRepeatInd;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_PROGRESS_INDICATOR_STRU   stProgInd;
    NAS_CC_IE_PRIORITY_LEVEL_STRU       stPrioGranted;
    NAS_CC_IE_NW_CALL_CTRL_CAP_STRU     stNwCCCap;
}NAS_CC_MSG_CALL_PROC_STRU;

/* [9.3.4] Congestion control */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Congestion control      │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Congestion level        │    M     │   V    │  1/2   │
    ├──┼────────────┼─────┼────┼────┤
    │    │Spare half octet        │    M     │   V    │  1/2   │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CONG_LEVEL_STRU           stCongLevel;
    NAS_CC_IE_CAUSE_STRU                stCause;
}NAS_CC_MSG_CONG_CTRL_STRU;


/* [9.3.5] Connect */
/*============================================================================*/
/* 9.3.5.1 Connect (network to mobile station direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Connect Message type    │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │1E  │Progress indicator      │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │4C  │Connected number        │    O     │  TLV   │  3-14  │
    ├──┼────────────┼─────┼────┼────┤
    │4D  │Connected subaddress    │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_PROGRESS_INDICATOR_STRU   stProgInd;
    NAS_CC_IE_CONN_NUM_STRU             stConnectedNum;
    NAS_CC_IE_CONN_ADDR_STRU            stConnectedSubaddr;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
}NAS_CC_MSG_CONNECT_MT_STRU;

/* 9.3.5.2 Connect (mobile station to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Connect Message type    │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │4D  │Connected subaddress    │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    ├──┼────────────┼─────┼────┼────┤
    │7F  │SS version              │    O     │  TLV   │  2-3   │
    ├──┼────────────┼─────┼────┼────┤
    │2D  │Stream Identifier       │    O     │  TLV   │   3    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_CONN_ADDR_STRU            stConnectedSubaddr;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSVersion;
    NAS_CC_IE_STREAM_IDENTIFIER_STRU    stStreamID;
}NAS_CC_MSG_CONNECT_MO_STRU;


/* [9.3.6] Connect acknowledge */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Connect acknowledge     │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_CONNECT_ACK_STRU;


/* [9.3.7] Disconnect */
/*============================================================================*/
/* 9.3.7.1 Disconnect (network to mobile station direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Disconnect Message type │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    M     │   LV   │  3-31  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │1E  │Progress indicator      │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    ├──┼────────────┼─────┼────┼────┤
    │7B  │Allowed actions $(CCBS)$│    O     │  TLV   │   3    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_PROGRESS_INDICATOR_STRU   stProgInd;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_ALLOWED_ACTIONS_STRU      stAllowedAct;
}NAS_CC_MSG_DISCONNECT_MT_STRU;

/* 9.3.7.2 Disconnect (mobile station to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Disconnect Message type │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    M     │   LV   │  3-31  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    ├──┼────────────┼─────┼────┼────┤
    │7F  │SS version              │    O     │  TLV   │  2-3   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSVersion;
}NAS_CC_MSG_DISCONNECT_MO_STRU;

/* [9.3.8] Emergency setup */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Emergency setup         │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability       │    O     │  TLV   │  3-11  │
    ├──┼────────────┼─────┼────┼────┤
    │2D  │Stream Identifier       │    O     │  TLV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │40  │Supported Codecs        │    O     │  TLV   │  5-n   │
    ├──┼────────────┼─────┼────┼────┤
    │2E  │Emergency category      │    O     │  TLV   │   3    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_BC_STRU                   stBC;
    NAS_CC_IE_STREAM_IDENTIFIER_STRU    stStreamID;
    NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU stCodecList;
    NAS_CC_IE_SERVICE_CATEGORY_STRU     stEmergencyCAT;
}NAS_CC_MSG_EMERGENCY_STEUP_STRU;


/* [9.3.9] Facility */
/*============================================================================*/
/* 9.3.9.1 Facility (network to mobile station direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Facility Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Facility                │    M     │   LV   │  1-?   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_FACILITY_STRU             stFacility;
}NAS_CC_MSG_FACILITY_MT_STRU;

/* 9.3.9.2 Facility (mobile station to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Facility Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Facility                │    M     │   LV   │  1-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7F  │SS version              │    O     │  TLV   │  2-3   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSVersion;
}NAS_CC_MSG_FACILITY_MO_STRU;


/* [9.3.10] Hold */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Hold Message type       │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
     NAS_AIR_MSG_HDR_STRU               stHeader;
}NAS_CC_MSG_HOLD_STRU;


/* [9.3.11] Hold Acknowledge */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Hold Acknowledge        │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_HOLD_ACK_STRU;


/* [9.3.12] Hold Reject */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Hold Reject Message type│    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    M     │   LV   │  3-31  │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
}NAS_CC_MSG_HOLD_REJ_STRU;


/* [9.3.13] Modify */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Modify Message type     │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Bearer capability       │    M     │   LV   │  2-15  │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    O     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    O     │  TLV   │  2-5   │
    ├──┼────────────┼─────┼────┼────┤
    │A3  │Reverse call setup      │          │        │        │
    │    │direction               │    O     │   T    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │A4  │Network-init. Service   │          │        │        │
    │    │Upgrade indicator       │    O     │   T    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                    stHeader;
    NAS_CC_IE_BC_STRU                       stBC;
    NAS_CC_IE_LLC_STRU                      stLLC;
    NAS_CC_IE_HLC_STRU                      stHLC;
    NAS_CC_IE_REVERSE_CALL_SETUP_DIR_STRU   stReverseDir;
    NAS_CC_IE_NW_INIT_SERV_UPGRADE_STRU     stNwInitServUpgrade;
}NAS_CC_MSG_MODIFY_STRU;


/* [9.3.14] Modify complete */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Modify complete         │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Bearer capability       │    M     │   LV   │  2-15  │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    O     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    O     │  TLV   │  2-5   │
    ├──┼────────────┼─────┼────┼────┤
    │A3  │Reverse call setup      │          │        │        │
    │    │direction               │    O     │   T    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                    stHeader;
    NAS_CC_IE_BC_STRU                       stBC;
    NAS_CC_IE_LLC_STRU                      stLLC;
    NAS_CC_IE_HLC_STRU                      stHLC;
    NAS_CC_IE_REVERSE_CALL_SETUP_DIR_STRU   stReverseDir;
}NAS_CC_MSG_MODIFY_COMPLETE_STRU;


/* [9.3.15] Modify reject */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Modify reject           │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Bearer capability       │    M     │   LV   │  2-15  │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    M     │   LV   │  3-31  │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    O     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    O     │  TLV   │  2-5   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_BC_STRU                   stBC;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_LLC_STRU                  stLLC;
    NAS_CC_IE_HLC_STRU                  stHLC;
}NAS_CC_MSG_MODIFY_REJ_STRU;


/* [9.3.16] Notify */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Notify Message type     │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Notification indicator  │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                    stHeader;
    NAS_CC_IE_NOTIFICATION_INDICATOR_STRU   stNotifyInd;
}NAS_CC_MSG_NOTIFY_STRU;


/* [9.3.17] Progress */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Progres Message type    │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Progress indicator      │    M     │   LV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_PROGRESS_INDICATOR_STRU   stProgInd;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
}NAS_CC_MSG_PROGRESS_STRU;


/* [9.3.17a] CC-Establishment $(CCBS)$ */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │CC-Establishment        │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Setup container         │    M     │   LV   │  3-n   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_SETUP_CONTAINER_STRU      stSetupContainer;
}NAS_CC_MSG_CC_EST_STRU;

/* [9.3.17b] CC-Establishment confirmed $(CCBS)$ */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │CC-Establishment        │          │        │        │
    │    │confirmed Message type  │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │Repeat Indicator        │    C     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 1     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 2     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │40  │Supported Codec List    │    O     │  TLV   │  5-n   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stRepeatInd;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU stCodecList;
}NAS_CC_MSG_CC_EST_CNF_STRU;


/* [9.3.18] Release */
/*============================================================================*/
/* 9.3.18.1 Release (network to mobile station direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Release Message type    │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Second cause            │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_CAUSE_STRU                stCause2;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
}NAS_CC_MSG_RELEASE_MT_STRU;

/* 9.3.18.2 Release (mobile station to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Release Message type    │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Second cause            │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    ├──┼────────────┼─────┼────┼────┤
    │7F  │SS version              │    O     │  TLV   │  2-3   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_CAUSE_STRU                stCause2;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSVersion;
}NAS_CC_MSG_RELEASE_MO_STRU;


/* [9.3.18a] Recall $(CCBS)$ */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Recall Message type     │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Recall Type             │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Facility                │    M     │   LV   │  2-n   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_RECALL_TYPE_STRU          stRecallType;
    NAS_CC_IE_FACILITY_STRU             stFacility;
}NAS_CC_MSG_RECALL_STRU;


/* [9.3.19] Release complete */
/*============================================================================*/
/* 9.3.19.1 Release complete (network to mobile station direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Release complete        │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
}NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU;

/* 9.3.19.2 Release complete (mobile station to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Release complete        │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-131 │
    ├──┼────────────┼─────┼────┼────┤
    │7F  │SS version              │    O     │  TLV   │  2-3   │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSVersion;
}NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU;


/* [9.3.20] Retrieve */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Retrieve Message type   │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_RETRIEVE_STRU;


/* [9.3.21] Retrieve Acknowledge */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Retrieve Acknowledge    │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_RETRIEVE_ACK_STRU;


/* [9.3.22] Retrieve Reject */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Retrieve Reject         │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    O     │   LV   │  3-31  │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
}NAS_CC_MSG_RETRIEVE_REJ_STRU;


/* [9.3.23] Setup */
/*============================================================================*/
/* 9.3.23.1 Setup (mobile terminated call establishment) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Setup Message type      │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │BC repeat indicator     │    C     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 1     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 2     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │1E  │Progress indicator      │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │34  │Signal                  │    O     │  TV    │   2    │
    ├──┼────────────┼─────┼────┼────┤
    │5C  │Calling party BCD num.  │    O     │  TLV   │  3-14  │
    ├──┼────────────┼─────┼────┼────┤
    │5D  │Calling party subaddr.  │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │5E  │Called party BCD num.   │    O     │  TLV   │  3-19  │
    ├──┼────────────┼─────┼────┼────┤
    │6D  │Called party subaddr.   │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │74  │Redirecting BCD num.    │    O     │  TLV   │  3-19  │
    ├──┼────────────┼─────┼────┼────┤
    │75  │Redirecting subaddress. │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │LLC repeat indicator    │    O     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    O     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    C     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │HLC repeat indicator    │    O     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    O     │  TLV   │  2-5   │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    C     │  TLV   │  2-5   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-35  │
    ├──┼────────────┼─────┼────┼────┤
    │8-  │Priority Level          │    O     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │19  │Alerting Pattern        │    O     │  TLV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │2F  │Network CC cap.         │    O     │  TLV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │3A  │Cause of No CLI         │    O     │  TLV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │41  │Backup bearer capability│    O     │  TLV   │  3-15  │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stBCRepeatInd;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_PROGRESS_INDICATOR_STRU   stProgInd;
    NAS_CC_IE_SIGNAL_STRU               stSignal;
    NAS_CC_IE_CALLING_NUM_STRU          stCallingNum;
    NAS_CC_IE_CALLING_SUBADDR_STRU      stCallingSubaddr;
    NAS_CC_IE_CALLED_NUM_STRU           stCalledNum;
    NAS_CC_IE_CALLED_SUBADDR_STRU       stCalledSubaddr;
    NAS_CC_IE_REDIRECTING_NUM_STRU      stRedirectingNum;
    NAS_CC_IE_REDIRECTING_SUBADDR_STRU  stRedirectingSubaddr;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stLLCRepeatInd;
    NAS_CC_IE_LLC_STRU                  stLLC1;
    NAS_CC_IE_LLC_STRU                  stLLC2;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stHLCRepeatInd;
    NAS_CC_IE_HLC_STRU                  stHLC1;
    NAS_CC_IE_HLC_STRU                  stHLC2;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_PRIORITY_LEVEL_STRU       stPriority;
    NAS_CC_IE_ALERTING_PATTERN_STRU     stAlert;
    NAS_CC_IE_NW_CALL_CTRL_CAP_STRU     stNwCCCap;
    NAS_CC_IE_NO_CLI_CAUSE_STRU         stNoCLICause;
    NAS_CC_IE_BAK_BC_STRU               stBackupBC;
}NAS_CC_MSG_SETUP_MT_STRU;

/* 9.3.23.2 Setup (mobile originating call establishment) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Setup Message type      │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │BC repeat indicator     │    C     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 1     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │04  │Bearer capability 2     │    O     │  TLV   │  3-16  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │5D  │Calling party subaddr.  │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │5E  │Called party BCD num.   │    O     │  TLV   │  3-19  │
    ├──┼────────────┼─────┼────┼────┤
    │6D  │Called party subaddr.   │    O     │  TLV   │  2-23  │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │LLC repeat indicator    │    O     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    O     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │7C  │Low layer comp.         │    C     │  TLV   │  2-18  │
    ├──┼────────────┼─────┼────┼────┤
    │D-  │HLC repeat indicator    │    O     │  TV    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    O     │  TLV   │  2-5   │
    ├──┼────────────┼─────┼────┼────┤
    │7D  │High layer comp.        │    C     │  TLV   │  2-5   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │User-user               │    O     │  TLV   │  3-35  │
    ├──┼────────────┼─────┼────┼────┤
    │7F  │SS version              │    O     │  TLV   │  2-3   │
    ├──┼────────────┼─────┼────┼────┤
    │A1  │CLIR suppression        │    C     │   T    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │A2  │CLIR invocation         │    C     │   T    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │15  │CC capabilities         │    O     │  TLV   │   4    │
    ├──┼────────────┼─────┼────┼────┤
    │1D  │Facility $(CCBS)$ (adva-│          │        │        │
    │    │nced recall alignment)  │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │1B  │Facility (recall alig.  │          │        │        │
    │    │Not essential) $(CCBS)$ │    O     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │2D  │Stream Identifier       │    O     │  TLV   │   3    │
    ├──┼────────────┼─────┼────┼────┤
    │40  │Supported Codecs        │    O     │  TLV   │  5-n   │
    ├──┼────────────┼─────┼────┼────┤
    │A3  │Redial                  │    O     │   T    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stBCRepeatInd;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_IE_FACILITY_STRU             stFacility;
    NAS_CC_IE_CALLING_SUBADDR_STRU      stCallingSubaddr;
    NAS_CC_IE_CALLED_NUM_STRU           stCalledNum;
    NAS_CC_IE_CALLED_SUBADDR_STRU       stCalledSubaddr;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stLLCRepeatInd;
    NAS_CC_IE_LLC_STRU                  stLLC1;
    NAS_CC_IE_LLC_STRU                  stLLC2;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     stHLCRepeatInd;
    NAS_CC_IE_HLC_STRU                  stHLC1;
    NAS_CC_IE_HLC_STRU                  stHLC2;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_SS_VER_INDICATOR_STRU     stSSVersion;
    NAS_CC_IE_CLIR_S_STRU               stCLIR_S;
    NAS_CC_IE_CLIR_I_STRU               stCLIR_I;
    NAS_CC_IE_CC_CAP_STRU               stCCCap;
    NAS_CC_IE_FACILITY_STRU             stFacility1D;
    NAS_CC_IE_FACILITY_STRU             stFacility1B;
    NAS_CC_IE_STREAM_IDENTIFIER_STRU    stStreamID;
    NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU stCodecList;
    NAS_CC_IE_REDIAL_STRU               stRedial;
}NAS_CC_MSG_SETUP_MO_STRU;

/* [9.3.23a] Start CC $(CCBS)$ */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Start CC Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │15  │CC Capabilities         │    O     │  TLV   │   4    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CC_CAP_STRU               stCCCap;
}NAS_CC_MSG_START_CC_STRU;


/* [9.3.24] Start DTMF */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Start DTMF Message type │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │2C  │Keypad facility         │    M     │  TV    │   2    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_KEYPAD_FACILITY_STRU      stKeypadFacility;
}NAS_CC_MSG_START_DTMF_STRU;


/* [9.3.25] Start DTMF Acknowledge */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Start DTMF Acknowledge  │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │2C  │Keypad facility         │    M     │  TV    │   2    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_KEYPAD_FACILITY_STRU      stKeypadFacility;
}NAS_CC_MSG_START_DTMF_ACK_STRU;


/* [9.3.26] Start DTMF reject */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Start DTMF reject       │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    M     │   LV   │  3-31  │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
}NAS_CC_MSG_START_DTMF_REJ_STRU;


/* [9.3.27] Status */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Status Message type     │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Cause                   │    M     │   LV   │  3-31  │
    ├──┼────────────┼─────┼────┼────┤
    │    │Call state              │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │24  │Auxiliary states        │    O     │  TLV   │   3    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_CAUSE_STRU                stCause;
    NAS_CC_IE_CALL_STATE_STRU           stCallState;
    NAS_CC_IE_AUX_STATE_STRU            stAuxState;
}NAS_CC_MSG_STATUS_STRU;



/* [9.3.28] Status enquiry */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Status enquiry          │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_STATUS_ENQUIRY_STRU;


/* [9.3.29] Stop DTMF */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Stop DTMF Message type  │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_STOP_DTMF_STRU;


/* [9.3.30] Stop DTMF acknowledge */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Stop DTMF acknowledge   │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
}NAS_CC_MSG_STOP_DTMF_ACK_STRU;


/* [9.3.31] User information */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │User information        │          │        │        │
    │    │Message type            │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │User-user               │    M     │   LV   │  2-130 │
    ├──┼────────────┼─────┼────┼────┤
    │A0  │More data               │    O     │   T    │   1    │
    └──┴────────────┴─────┴────┴────┘
*/
typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_IE_USER_USER_STRU            stUserUser;
    NAS_CC_IE_MORE_DATA_STRU            stMoredata;
}NAS_CC_MSG_USER_INFO_STRU;

/*============================================================================*/
/* CC Peer Messages Union Definition                                          */
/*============================================================================*/
typedef union
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    NAS_CC_MSG_ALERTING_MT_STRU         stAlertingMT;                           /* 9.3.1.1  */
    NAS_CC_MSG_ALERTING_MO_STRU         stAlertingMO;                           /* 9.3.1.2  */
    NAS_CC_MSG_CALL_CNF_STRU            stCallCnf;                              /* 9.3.2    */
    NAS_CC_MSG_CALL_PROC_STRU           stCallProc;                             /* 9.3.3    */
    NAS_CC_MSG_CONG_CTRL_STRU           stCongCtrl;                             /* 9.3.4    */
    NAS_CC_MSG_CONNECT_MT_STRU          stConnectMT;                            /* 9.3.5.1  */
    NAS_CC_MSG_CONNECT_MO_STRU          stConnectMO;                            /* 9.3.5.2  */
    NAS_CC_MSG_CONNECT_ACK_STRU         stConnectAck;                           /* 9.3.6    */
    NAS_CC_MSG_DISCONNECT_MT_STRU       stDisconnectMT;                         /* 9.3.7.1  */
    NAS_CC_MSG_DISCONNECT_MO_STRU       stDisconnectMO;                         /* 9.3.7.2  */
    NAS_CC_MSG_EMERGENCY_STEUP_STRU     stEmergencySetup;                       /* 9.3.8    */
    NAS_CC_MSG_FACILITY_MT_STRU         stFacilityMT;                           /* 9.3.9.1  */
    NAS_CC_MSG_FACILITY_MO_STRU         stFacilityMO;                           /* 9.3.9.2  */
    NAS_CC_MSG_HOLD_STRU                stHold;                                 /* 9.3.10   */
    NAS_CC_MSG_HOLD_ACK_STRU            stHoldAck;                              /* 9.3.11   */
    NAS_CC_MSG_HOLD_REJ_STRU            stHoldRej;                              /* 9.3.12   */
    NAS_CC_MSG_MODIFY_STRU              stModify;                               /* 9.3.13   */
    NAS_CC_MSG_MODIFY_COMPLETE_STRU     stModifyComplete;                       /* 9.3.14   */
    NAS_CC_MSG_MODIFY_REJ_STRU          stModifyRej;                            /* 9.3.15   */
    NAS_CC_MSG_NOTIFY_STRU              stNotify;                               /* 9.3.16   */
    NAS_CC_MSG_PROGRESS_STRU            stProgress;                             /* 9.3.17   */
    NAS_CC_MSG_CC_EST_STRU              stCCEst;                                /* 9.3.17a  */
    NAS_CC_MSG_CC_EST_CNF_STRU          stCCEstCnf;                             /* 9.3.17b  */
    NAS_CC_MSG_RELEASE_MT_STRU          stReleaseMT;                            /* 9.3.18.1 */
    NAS_CC_MSG_RELEASE_MO_STRU          stReleaseMO;                            /* 9.3.18.2 */
    NAS_CC_MSG_RECALL_STRU              stRecall;                               /* 9.3.18a  */
    NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU stReleaseCompleteMT;                    /* 9.3.19.1 */
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU stReleaseCompleteMO;                    /* 9.3.19.2 */
    NAS_CC_MSG_RETRIEVE_STRU            stRetrieve;                             /* 9.3.20   */
    NAS_CC_MSG_RETRIEVE_ACK_STRU        stRetrieveAck;                          /* 9.3.21   */
    NAS_CC_MSG_RETRIEVE_REJ_STRU        stRetrieveRej;                          /* 9.3.22   */
    NAS_CC_MSG_SETUP_MT_STRU            stSetupMT;                              /* 9.3.23.1 */
    NAS_CC_MSG_SETUP_MO_STRU            stSetupMo;                              /* 9.3.23.2 */
    NAS_CC_MSG_START_CC_STRU            stStartCC;                              /* 9.3.23a  */
    NAS_CC_MSG_START_DTMF_STRU          stStartDTMF;                            /* 9.3.24   */
    NAS_CC_MSG_START_DTMF_ACK_STRU      stStartDTMFAck;                         /* 9.3.25   */
    NAS_CC_MSG_START_DTMF_REJ_STRU      stStartDTMFRej;                         /* 9.3.26   */
    NAS_CC_MSG_STATUS_STRU              stStatus;                               /* 9.3.27   */
    NAS_CC_MSG_STATUS_ENQUIRY_STRU      stStatusEnquiry;                        /* 9.3.28   */
    NAS_CC_MSG_STOP_DTMF_STRU           stStopDTMF;                             /* 9.3.29   */
    NAS_CC_MSG_STOP_DTMF_ACK_STRU       stStopDTMFAck;                          /* 9.3.30   */
    NAS_CC_MSG_USER_INFO_STRU           stUserInfo;                             /* 9.3.31   */
}NAS_CC_AIR_MSG_UNION;



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

#endif /* __NAS_CC_AIR_MSG_H__ */

