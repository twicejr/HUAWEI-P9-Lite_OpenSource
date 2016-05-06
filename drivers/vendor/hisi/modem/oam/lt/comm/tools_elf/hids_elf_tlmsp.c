/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hids_elf_tlmsp.c
  版 本 号   : 初稿
  作    者   : c00326366
  生成日期   : 2015年11月13日
  最近修改   :
  功能描述   : 编译ELF文件给HIDS工具解析
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月13日
    作    者   : c00326366
    修改内容   : 创建文件

******************************************************************************/


#include "msp_diag_comm.h"
#include "lte_sleepflow.h"
#include "diag_msgbbp.h"
#include "diag_msgbsp.h"
#include "diag_msgmsp.h"
#include "diag_msgphy.h"

void msp_main(void)
{
// 消息结构声明开始
    MSP_SLEEP_MNTN_MSG_STRU stSleepMsg;
    
    DIAG_MSG_MSP_CONN_STRU  stMspConn;
    
    DIAG_MSG_A_TRANS_C_STRU stMsgATransC;
    
    DIAG_BSP_MSG_A_TRANS_C_STRU  stBspMsgTrans;
    
    DIAG_BBP_MSG_A_TRANS_C_STRU  stBbpMsgTrans;
    
    DIAG_PHY_MSG_A_TRANS_C_STRU  stPhyMsgTrans;
    
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    DIAG_MSG_SOCP_VOTE_REQ_STRU  stMsgSocpVote;
    
    DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU stMsgSocpVoteCnf;
#endif
    
    DIAG_A_DEBUG_C_REQ_STRU      stADebugCReq;
    
    DIAG_BSP_NV_AUTH_STRU        stBspNvAuth;
// 消息结构声明结束
}

