/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_sh_def.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块的宏定义
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2003-01-11      liuhui          Create File
 *  2005-10-29      tuyan           Modify
 *  2006-03-30      liai            Adjust for D00660
 *  2006/04/21      liai            Adjust for D00865
 *  2006-05-13      l48923          Delete useless code
 *   
 ************************************************************************/

#ifndef  _POEC_SH_DEF_H_
#define  _POEC_SH_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

#define PPPOE_TIMER_TICK        1000    /*通用定时器Tick:1秒*/

/*While in VISP,20580 is too long to output, define it as 512. t45114,20051020*/
#define PPPOE_CLIENT_DISPLAY_INFO_BLOCK_LEN   512

/* PPPoE Client RPC 通信消息*/
#define POE_CLIENT_HOT_INSERT_SLOT          0


typedef enum tagPPPOE_CLIENT_DISPLAY_TYPE
{
    POEC_DISPLAY_SUMM_OF_SPEC_SESSION = 1,
    POEC_DISPLAY_SUMM_OF_ALL_SESSION,
    POEC_DISPLAY_PACK_OF_SPEC_SESSION,
    POEC_DISPLAY_PACK_OF_ALL_SESSION
}PPPOE_CLIENT_DISPLAY_TYPE_EN;


/* 从接口板取display信息的RPC超时时间 */
#define PPPOE_CLIENT_CMD_RPC_DISPLAY_TIMEOUT  4000    

#define DEFAULT_ETH_MAX_SESSION_NUM         255

#define PPPOEC_MAC_LEN              6

/* 每次从PPPoE Client接收队列中取出报文的数目 */
#define PPPOE_CLIENT_GET_FROM_QUE   40

/* PPPoE Client接收队列长度 */
#define PPPOE_CLIENT_QUE_LEN        128

#define PPPOE_CLIENT_SYSTRACE_MID_SH_INIT   0x06

/* PPPoE Client的debug 类型 */
#define PPPOE_CLIENT_DEBUG_DATA        PPPOE_CLIENT_DEBUG_DATA_FLAG
#define PPPOE_CLIENT_DEBUG_ERROR       PPPOE_CLIENT_DEBUG_ERROR_FLAG
#define PPPOE_CLIENT_DEBUG_EVENT       PPPOE_CLIENT_DEBUG_EVENT_FLAG
#define PPPOE_CLIENT_DEBUG_PACKET      PPPOE_CLIENT_DEBUG_PACKET_FLAG
#define PPPOE_CLIENT_DEBUG_VERBOSE     PPPOE_CLIENT_DEBUG_VERBOSE_FLAG
#define PPPOE_CLIENT_DEBUG_GR          PPPOE_CLIENT_DEBUG_GR_FLAG
#define PPPOE_CLIENT_DEBUG_ALL         PPPOE_CLIENT_DEBUG_ALL_FLAG

/*----------------------------------------------*
 * 定义错误码,display部分使用
 *----------------------------------------------*/
#define PPPOE_CLIENT_ERR_RPC_SYNC_SEND_FAIL   0x01000008
#define PPPOE_CLIENT_ERR_MEM_ALLOC_FAIL       0x01000009

/*-----------------------------------------------------------*
 * 定义SID，PPPoE Client模块Shell部分使用(需删去vos_id.h中的定义)
 *-----------------------------------------------------------*/
#define SID_COMP_PPPOEC_WAITLIST_PARAM   ( 3 )
#define SID_COMP_PPPOEC_DISPINFO         ( 4 )

#ifdef __cplusplus
}
#endif

#endif 

