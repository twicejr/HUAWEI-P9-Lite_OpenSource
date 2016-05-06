/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_def.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: Macro defininition of PPPMUX Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_DEF_H_
#define _PPPMUX_DEF_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define MUXCP_CI_PID            1            /* MUXCP协商报文类型 */
#define MUXCP_CILEN_PID         4            /* MUXCP协商报文长度 */
#define MUXCP_CILEN_VOID        2

#define MUXCP_NEED_NEGO         1            /* 需要协商MUXCP */
#define MUXCP_NO_NEED_NEGO      0            /* 不需要协商MUXCP */

#define MUXCP_NEED_NEGO_PID     1            /* 需要协商default pid */
#define MUXCP_NO_NEED_NEGO_PID  0            /* 不需要协商default pid */


/* 最大子帧长度 */
#define PPPMUX_MIN_SUBFRAMELEN  1
#define PPPMUX_MAX_SUBFRAMELEN  512
#define PPPMUX_DEF_SUBFRAMELEN  192
/*Added by luogaowei, for MBSC PPPMUX最大子帧长度扩展, 2013/3/5 */
#define PPPMUX_MAX_SUBFRAMELENEX 1498

/* 最大复合帧长度 */
#define PPPMUX_MIN_FRAMELEN  3
#define PPPMUX_MAX_FRAMELEN  1500
#define PPPMUX_DEF_FRAMELEN  1500

/* 最大子帧数 */
#define PPPMUX_MIN_SUBFRAMECOUNT  1
#define PPPMUX_MAX_SUBFRAMECOUNT  15
#define PPPMUX_DEF_SUBFRAMECOUNT  15

/* 最大复合时延 */
#define PPPMUX_MIN_DELAY  1
#define PPPMUX_MAX_DELAY  1000
#define PPPMUX_DEF_DELAY  10

#define PPPMUX_FLAG_PFF 0x80
#define PPPMUX_FLAG_LXT 0x4000

/* 报文输入/输出标记 */
#define PPPMUX_DEBUG_PACKET_IN  0
#define PPPMUX_DEBUG_PACKET_OUT 1

#define PPPMUX_MAXLEN_ONEBYTE   63    /* 6 bits, other 2 bits reserved for PFF & LXT flags */
#define PPPMUX_MAXLEN_TWOBYTE   16383 /* 14 bits, other 2 bits reserved for PFF & LXT flags */

#define MID_PPPMUX     g_stPPPMUXModInfo.ulMID_PPPMUX
#define CPUTIKS_PER_MS g_stPPPMUXModInfo.ulCPU_TICKS_PER_MS

#define PPPMUX_GET_PACKETCLASS g_stPPPMUXShellApi.pfQOS_GetPacketClass
#define PPPMUX_DEBUG_OUTPUT    g_stPPPMUXShellApi.pfPPPMUX_DebugOutput

#define PPPMUX_QUE_GETLEN        200     /* 一次从队列中读取的报文数 */
#define PPPMUX_QUE_REGLEN        1024    /* 队列的缺省注册长度 */
#define PPPMUX_QUE_MAXLEN        1024    /* 队列最大长度 */

/* Added by l57500 for 同步VISPV1R5问题单SWID00221,2007-05-09 */
#define PPPMUX_MBUF_RESERVE_SPACE 200    /* PPPMUX子帧报文解复合后报文头预留空间 */
/* End of addition */


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _PPPMUX_DEF_H_ */
