/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_gr.h
*
*  Project Code: VISPV100R006C02B100
*   Module Name: bfd gr头文件
*  Date Created: 2008-8-16
*        Author: wujie(61195)
*   Description: 包含BFD GR模块的宏定义、全局变量声明和函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-8-16  wujie(61195)         Creat the first version.
*
*******************************************************************************/
#ifndef _BFD_GR_H_
#define _BFD_GR_H_

#ifdef __cplusplus
extern "C"{
#endif

/* BFD的GR状态 */
enum enumBFD_GR_STATE
{
    BFD_STATE_NORMAL,       /* 0 正常状态 */
    BFD_STATE_KEEPALIVE,    /* 1 保活状态, 等待恢复处理 */
    BFD_STATE_RESTORING,    /* 2 正在进行恢复处理 */
    BFD_STATE_RESTORED,     /* 3 已经完成恢复处理, 等待平滑处理 */
    BFD_STATE_SMOOTHING,    /* 4 正在进行平滑处理, 平滑处理完毕后直接进入 0 正常状态 */
};


/* 比较配置的参数和NP保存的参数是否一致, 不一致则记录日志 */
#define BFD_GR_CMP_PARA(cfg_para, np_para) \
if ((ULONG)(cfg_para) != (ULONG)(np_para)) \
{\
    ulParaDiff = 1;\
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_04DC, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, \
                     "\r\nThe para of session %u mismatch(line %u): CFG(%u) != NP(%u)",\
                     ulSessionID, __LINE__, (ULONG)(cfg_para), (ULONG)(np_para));\
}\


USHORT BFD_GR_CalcCksum(USHORT *pusCalcFrom, LONG lTotalLen);
ULONG BFD_GR_RestoreOneSession(BFD_SESS_ENTRY_S *pstBfdSession);
ULONG BFD_GR_Restore(VOID);
ULONG BFD_GR_SmoothOneSession(ULONG ulVrfIndex,ULONG ulSessionID);
ULONG BFD_GR_Smooth(VOID);

extern VOID VOS_GetCpuTick( ULONG *plow,ULONG *phigh );

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _BFD_GR_H_ */
