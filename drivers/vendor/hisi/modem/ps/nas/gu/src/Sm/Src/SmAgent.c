/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmAgent.c
  Description  : SM接收和发送AGENT消息的函数
  Function List:
                 1. SM_RcvAgentSmInquire
                 2. SM_RcvAgentSmPdpnumInquire
                 3. SM_SndAgentSmAgentInfo
                 4. SM_SndAgentStatusInd
                 5. SM_SndAgentSmPdpnumInd
                 6. SM_AgentMsgDistr
  History:
      1.   张志勇   2005.01.10 新规作成
      2.   韩鲁峰   2005-11-20 ADD for A32D00790
      3.   韩鲁峰   2006-04-12     for A32D02451
*******************************************************************************/


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SM_AGENT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

