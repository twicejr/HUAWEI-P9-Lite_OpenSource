/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Psprimitive.h
  Version     : V100R001
  Date        : 2005-04-19
  Description :
  History     :
  1. Date:2005-04-19
     Author: w29695
     Modification:Create
  2.日    期   : 2006年5月19日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D03487
*******************************************************************************/

#ifndef _PS_INTER_PRIMITIVE_H_
#define _PS_INTER_PRIMITIVE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                                  /* __cpluscplus                             */
#endif                                                                                  /* __cpluscplus                             */


#include "frmwkext.h"

/*
 * 目前WUEPS系统使用固定16BYTE长度的消息,具体使用方法如下
 * +------------------+
 * | message type =   | 1st VOS_UINT32
 * |  NORMAL/TIMER    |
 * |------------------|
 * | message pointer  | 2nd VOS_UINT32
 * | / PARA           |
 * |------------------|
 * | reserved         | 3rd VOS_UINT32
 * |------------------|
 * | reserved         | 4th VOS_UINT32
 * +------------------+
 */
#define WUEPS_MSG_TYPE_NORMAL       (VOS_UINT32)0                                            /* 普通消息                                 */
#define WUEPS_MSG_TYPE_TIMER        (VOS_UINT32)1                                            /* 定时器消息                               */


/* 消息class定义 */
#define ADMIN_PS_AP_CLASS           (VOS_UINT32)0x80000000                                   /* MAP0: WUEPS ADMIN ---- PS                */
#define L1C_RLC_AP_CLASS            (VOS_UINT32)0x80000001                                   /* MAP1: L1C ---- RLC                       */
/*#define MAIN_FRAMEWORK_AP_CLASS   (VOS_UINT32)0x80000002   */                              /* MAP2: Reserved                           */
/*#define OM_AS_AP_CLASS            (VOS_UINT32)0x80000003   */                              /* MAP3: Reserved                           */
/*#define OM_NAS_AP_CLASS           (VOS_UINT32)0x80000004   */                              /* MAP4: Reserved                           */
#define OM_FRAMEWORK_AP_CLASS       (VOS_UINT32)0x80000005                                   /* MAP5: O&M ---- FRAMEWORK                 */
#define L1C_MAC_AP_CLASS            (VOS_UINT32)0x80000006                                   /* MAP6: L1C ---- MAC                       */
#define L1C_RRC_AP_CLASS            (VOS_UINT32)0x80000007                                   /* MAP7: L1C ---- RRC                       */
#define MAC_RLC_AP_CLASS            (VOS_UINT32)0x80000008                                   /* MAP8: MAC ---- RLC                       */
#define MAC_RRC_AP_CLASS            (VOS_UINT32)0x80000009                                   /* MAP9: MAC ---- RRC                       */
/*#define MAC_NAS_AP_CLASS          (VOS_UINT32)0x8000000A   */                              /* MAP10: Reserved                          */
#define RLC_PDCP_AP_CLASS           (VOS_UINT32)0x8000000B                                   /* MAP11: RLC ---- PDCP                     */
#define RLC_NAS_AP_CLASS            (VOS_UINT32)0x8000000C                                   /* MAP12: RLC ---- NAS                      */
#define RLC_RRC_AP_CLASS            (VOS_UINT32)0x8000000D                                   /* MAP13: RLC ---- RRC                      */
/*#define RLC_BMC_AP_CLASS          (VOS_UINT32)0x8000000E   */                              /* MAP14: Reserved                          */
#define PDCP_NAS_AP_CLASS           (VOS_UINT32)0x8000000F                                   /* MAP15: PDCP ---- NAS                     */
#define PDCP_RRC_AP_CLASS           (VOS_UINT32)0x80000010                                   /* MAP16: PDCP ---- RRC                     */
#define RRC_NAS_AP_CLASS            (VOS_UINT32)0x80000011                                   /* MAP17: RRC ---- NAS                      */
/*#define AS_FRAMEWORK_AP_CLASS     (VOS_UINT32)0x80000012   */                              /* MAP18: Reserved                          */
/*#define NAS_FRAMEWORK_AP_CLASS    (VOS_UINT32)0x80000013   */                              /* MAP19: Reserved                          */
#define USIM_PS_AP_CLASS            (VOS_UINT32)0x80000014                                   /* MAP20: USIM --- PS                       */
#define AGENT_PS_AP_CLASS           (VOS_UINT32)0x80000015                                   /* MAP21: AGENT --- PS                      */
/*#define L1C_L1A_AP_CLASS          (VOS_UINT32)0x80000016   */                              /* MAP22: Reserved                          */
#define RCSF_RRC_AP_CLASS           (VOS_UINT32)0x80000017                                   /* MAP23: RCSF --- RRC                      */
#define RMF_RRC_AP_CLASS            (VOS_UINT32)0x80000018                                   /* MAP24: RMF --- RRC                       */
#define RSRF_RRC_AP_CLASS           (VOS_UINT32)0x80000019                                   /* MAP25: RSRF --- RRC                      */
#define RSRF_RCSF_AP_CLASS          (VOS_UINT32)0x8000001A                                   /* MAP26: RSRF --- RCSF                     */

#define MM_MMC_AP_CLASS             (VOS_UINT32)0x8000001B                                   /* MAP27: MM   ---- MMC                     */
#define MM_CC_AP_CLASS              (VOS_UINT32)0x8000001C                                   /* MAP28: MM   ---- CC                      */
#define MMC_GMM_AP_CLASS            (VOS_UINT32)0x8000001D                                   /* MAP29: MMC  ---- GMM                     */
#define MMC_TAF_AP_CLASS            (VOS_UINT32)0x8000001E                                   /* MAP30: MMC  ---- TAF                     */
#define GMM_SM_AP_CLASS             (VOS_UINT32)0x8000001F                                   /* MAP31: GMM  ---- SM                      */
#define GMM_RABM_AP_CLASS           (VOS_UINT32)0x80000020                                   /* MAP32: GMM  ---- RABM                    */
#define CC_RABM_AP_CLASS            (VOS_UINT32)0x80000021                                   /* MAP33: CC   ---- RABM                    */
#define SM_RABM_AP_CLASS            (VOS_UINT32)0x80000022                                   /* MAP34: SM   ---- RABM                    */
#define RABM_TAF_AP_CLASS           (VOS_UINT32)0x80000023                                   /* MAP35: RABM ---- TAF                     */
#define NAS_TAF_AP_CLASS            (VOS_UINT32)0x80000024                                   /* MAP36: NAS  ---- TAF                     */

#define MM_SS_AP_CLASS              (VOS_UINT32)0x80000025                                   /* MAP37: MM   ---- SS                      */
#define GMM_SMS_AP_CLASS            (VOS_UINT32)0x80000026                                   /* MAP38: GMM  ---- SMS                     */
#define MM_SMS_AP_CLASS             (VOS_UINT32)0x80000027                                   /* MAP39: MM   ---- SMS                     */
#define SMA_SMT_AP_CLASS            (VOS_UINT32)0x80000028                                   /* MAP40: SMA  ---- SMT                     */
#define TC_PS_AP_CLASS              (VOS_UINT32)0x80000029                                   /* MAP41: TC   ---- PS                      */
#define APP_RRC_AP_CLASS            (VOS_UINT32)0x8000002A                                   /* MAP49: APP  ---- RRC                     */
#define SMT_MMC_AP_CLASS            (VOS_UINT32)0x8000002B                                   /* MAP50: SMT  ---- MMC                     */
#define LLC_GMM_AP_CLASS            (VOS_UINT32)0x8000002D                                   /* MAP52: LLC ---- GMM                      */
#define GAS_MM_AP_CLASS             (VOS_UINT32)0x8000002E                              /* MAP53: GAS ---- MM                       */
#define GAS_GMM_AP_CLASS            (VOS_UINT32)0x8000002F                              /* MAP54: GAS ---- GMM                      */
#define GAS_MMC_AP_CLASS            (VOS_UINT32)0x80000030                              /* MAP55: GAS ---- MMC                      */
#define RRC_GAS_AP_CLASS            (VOS_UINT32)0x80000031                                   /* MAP50: SMT  ---- MMC                     */
#define RABM_MMC_AP_CLASS           (VOS_UINT32)0x80000032

/* */
/* OM发给串口的原语 */
#define OM_SEND_DATA_REQ            (VOS_UINT32)0x00000000
/* OM接收到的来自串口的原语 */
#define OM_DATA_IND                 (VOS_UINT32)0x00000001

/*
 * message name: WUEPS_START_REQ
 * direction MAIN --> all thread in WUEPS system
 * function: command all thread start to run
 */
#define WUEPS_START_REQ             (VOS_UINT32)0
#define WUEPS_START_REQ_PRIO        (VOS_UINT32)1

/* 消息头结构 */

typedef struct wueps_start_req_stru
{
    MSG_HEADER_STRU MsgHeader;
}WUEPS_START_REQ_STRU;


#define WUEPS_RESET_REQ             (VOS_UINT32)1
typedef struct
{
    MSG_HEADER_STRU MsgHeader;
}WUEPS_RESET_REQ_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                                  /* __cpluscplus                             */

#endif
