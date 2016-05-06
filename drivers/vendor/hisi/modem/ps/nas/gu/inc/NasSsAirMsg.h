/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcPeerMsg.h
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
******************************************************************************/
#ifndef  NAS_CC_PEER_MSG_H
#define  NAS_CC_PEER_MSG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"

#include "NasCcIe.h"
#include "NasSsIe.h"

/******************************************************************************/
/* Messages for supplementary services control (24.080)                       */
/******************************************************************************/

/* 2.2 Messages for supplementary services control */
enum EN_SS_MSG_TYPE                    /* Table 2.1: Messages for CISS        */
{                                      /* 8 7 6 5 4 3 2 1                     */
    /* Clearing messages:                 x x 1 0 . . . .                     */
    EN_SS_MSG_RELEASE_COMPLETE = 0x2A, /*         1 0 1 0 - RELEASE COMPLETE  */
    /* Miscellaneous message group:       x x 1 1 . . . .                     */
    EN_SS_MSG_FACILITY         = 0x3A, /*         1 0 1 0 - FACILITY          */
    EN_SS_MSG_REGISTER         = 0x3B  /*         1 0 1 1 - REGISTER          */
};
typedef VOS_UINT8 ENUM_SS_MSG_TYPE;


/* [2.3] Facility */
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
    │    │Facility Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │    │Facility                │    M     │   LV   │  2-?   │
    └──┴────────────┴─────┴────┴────┘  
*/
typedef struct
{
    MSG_HEADER_STRU                 Header;
    SS_IE_FACILITY_STRU             Facility;
}SS_MSG_FACILITY_STRU;


/* [2.4] Register */
/*============================================================================*/
/* 2.4.1 Register (network to MS direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤ 
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Register Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    M     │  TLV   │  2-?   │
    └──┴────────────┴─────┴────┴────┘  
*/
typedef struct
{
    MSG_HEADER_STRU                 Header;
    SS_IE_FACILITY_STRU             Facility;
}SS_MSG_REGISTER_MT_STRU;

/* 2.4.2 Register (MS to network direction) */
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤ 
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Register Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    M     │  TLV   │  2-?   │
    ├──┼────────────┼─────┼────┼────┤
    │7E  │SS version              │    O     │  TLV   │   3    │  
    └──┴────────────┴─────┴────┴────┘  
*/
typedef struct
{
    MSG_HEADER_STRU                 Header;
    SS_IE_FACILITY_STRU             Facility;
    SS_IE_SS_VER_INDICATOR_STRU     SSVer;
}SS_MSG_REGISTER_MO_STRU;

/* 2.5 Release complete */
/*============================================================================*/
/*
    ┌──┬────────────┬─────┬────┬────┐
    │IEI │  Information element   │ Presence │ Format │ Length │
    ├──┼────────────┼─────┼────┼────┤ 
    │    │Protocol discriminator  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Transaction identifier  │    M     │   V    │  1/2   │
    │    ├────────────┼─────┼────┼────┤
    │    │Register Message type   │    M     │   V    │   1    │
    ├──┼────────────┼─────┼────┼────┤   
    │08  │Cause                   │    O     │  TLV   │  4-32  │
    ├──┼────────────┼─────┼────┼────┤
    │1C  │Facility                │    O     │  TLV   │  2-?   │
    └──┴────────────┴─────┴────┴────┘  
*/
typedef struct
{
    MSG_HEADER_STRU                 Header;
    CC_IE_CAUSE_STRU                Cause;
    SS_IE_FACILITY_STRU             Facility;
}SS_MSG_RELEASE_COMPLETE_STRU;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/



/******************************************************************************/
/* Messages Lookup Table Definition                                           */
/******************************************************************************/
const MSG_TBL_STRU SsMsgTblFacility[]=
{
   {IE_FORMAT_LV,   IE_PRESENCE_M,  0,  IE_OFFSET(SS_MSG_FACILITY_STRU,Facility),           SsIeTbl[EN_SS_IEI_FACILITY]     }
};

const MSG_TBL_STRU SsMsgTblRegisterMT[]=
{
   {IE_FORMAT_TLV,  IE_PRESENCE_M,  0,  IE_OFFSET(SS_MSG_REGISTER_MT_STRU,Facility),        SsIeTbl[EN_SS_IEI_FACILITY]     }
};

const MSG_TBL_STRU SsMsgTblRegisterMO[]=
{
   {IE_FORMAT_TLV,  IE_PRESENCE_M,  0,  IE_OFFSET(SS_MSG_REGISTER_MO_STRU,Facility),        SsIeTbl[EN_SS_IEI_FACILITY]     },
   {IE_FORMAT_TLV,  IE_PRESENCE_O,  1,  IE_OFFSET(SS_MSG_REGISTER_MO_STRU,SSVer),           SsIeTbl[EN_SS_IEI_SS_VER]       }
};

const MSG_TBL_STRU SsMsgTblReleaseComplete[]=
{
   {IE_FORMAT_TLV,  IE_PRESENCE_O,  0,  IE_OFFSET(SS_MSG_RELEASE_COMPLETE_STRU,Cause),      CcIeTbl[EN_CC_IEI_CAUSE]        },
   {IE_FORMAT_TLV,  IE_PRESENCE_O,  1,  IE_OFFSET(SS_MSG_RELEASE_COMPLETE_STRU,Facility),   SsIeTbl[EN_SS_IEI_SS_VER]       }
};


/******************************************************************************/
/* Entry of SS Messages                                                       */
/******************************************************************************/
const MSG_ENTRY_STRU SsMsgEntry[] =
{
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*00
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*01
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*02
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*03
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*04
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*05
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*06
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*07
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*08
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*09
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*0A
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*0B
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*0C
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*0D
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*0E
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*0F
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*10
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*11
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*12
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*13
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*14
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*15
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*16
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*17
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*18
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*19
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*1A
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*1B
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*1C
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*1D
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*1E
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*1F
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*20
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*21
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*22
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*23
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*24
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*25
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*26
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*27
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*28
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*29
 */
   { 2, (MSG_TBL_STRU *)SsMsgTblReleaseComplete     2, (MSG_TBL_STRU *)SsMsgTblReleaseComplete      },/*2A
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*2B
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*2C
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*2D
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*2E
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*2F
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*30
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*31
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*32
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*33
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*34
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*35
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*36
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*37
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*38
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*39
 */
   { 1, (MSG_TBL_STRU *)SsMsgTblFacility            1, (MSG_TBL_STRU *)SsMsgTblFacility             },/*3A
 */
   { 2, (MSG_TBL_STRU *)SsMsgTblRegisterMO          1, (MSG_TBL_STRU *)SsMsgTblRegisterMT           },/*3B
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*3C
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*3D
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 },/*3E
 */
   { 0, (MSG_TBL_STRU *)VOS_NULL_PTR                0, (MSG_TBL_STRU *)VOS_NULL_PTR                 } /*3F
 */
};


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* NAS_SS_PEER_MSG_H */
