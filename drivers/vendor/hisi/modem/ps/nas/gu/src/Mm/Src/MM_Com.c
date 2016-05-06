/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_Com.c
  Description  : MM公共处理
  Function List:
                1.  Mm_TimerStart
                2.  Mm_TimerStop
                3.  Mm_TimerPause
                4.  Mm_TimerResume
                5.  Mm_SendMsg
                6.  Mm_SendMsgNoWait
                7.  Mm_ComNasInfoSav
                8.  NAS_MML_IsCsLaiChanged
                9.  Mm_ComRandJudge
                10. Mm_ComT3212
                11. Mm_ComSvcStaJudge
                12. Mm_ComRelAllMmConn
                13. Mm_ComRejectCause11
                14. Mm_ComRejectCause12
                15. Mm_ComRejectCause13
                16. Mm_ComRejectCause15
                17. Mm_ComAuthenRcvAuthenRej
                18. Mm_ComTmsiReloc
                19. Mm_ComInfo
                20. Mm_ComIdentity
                21. Mm_ComAbortCause6
                22. Mm_ComAbortCause17
                23. Mm_ComT3214orT3216Expired
                24. Mm_ComDelRandRes
                25. Mm_ComT3218Expired
                26. Mm_ComAuthenNoAutn
                27. Mm_ComAuthenRcvAuthenReq
                28. Mm_ComAuthenRcvUsimCnfSuccess
                29. Mm_ComAuthenRcvUsimCnfFail
                30. Mm_ComAuthenRcvUsimCnf
                31. Mm_ComRejectCause4
                32. Mm_ComRejectCause6
                33. Mm_T3240Expire
                34. Mm_T3230Expire
                35. Mm_ComCheckDelayMmConn
                36. Mm_ComLuOnly
                37. Mm_ComInit
                38. Mm_ComStart
                39. NasMmLock
                40. NasMmUnLock
                41. Mm_ComToU2Handle
                42. Mm_ComLuCauseHandle
                43. Mm_ComGmmAttachCauseHandle
                44. Mm_ComGmmRauCauseHandle
                45. Mm_ComGmmSrCauseHandle
                46. Mm_ComNetDetachCauseHandle
                47. Mm_ComCauseHandleAllProc
                48. Mm_ComToNoImsiHandle
                49. Mm_ComRcvSysHandle
                50. Mm_ComMmConnExist
                51. Mm_ComJudgeProcForMmConn
                52. Mm_ComSaveProcAndCauseVal
                53. Mm_ComJudgeLimitSvc
                54. Mm_ComFillInCMSncReq
                55. Mm_ComFollowOnProc
                56. Mm_ComChkAttDelay
                57. Mm_ComProcCauseProcess
                58. Mm_ComDelLai
                59. Mm_ComProcCauseClear
                60. Mm_ComProcCauseClear
                61. MM_Com_RacChgChk


  History:
      1.  张志勇    2003-12-8  新版做成
      2.  s46746 2006-02-09 根据问题单A32D01864修改
      3.  s46746 2006-02-28 根据问题单A32D03324修改
      4.  s46746 2006-02-28 根据问题单A32D02503修改
      5.  s46746 2006-03-29  根据问题单A32D02486修改
      6. s46746 2006-03-31  根据问题单A32D02790修改
      7.日    期   : 2006年4月14日
        作    者   : liuyang id:48197
        修改内容   : 问题单号：A32D03031
      8.  s46746 2006-04-19 根据问题单A32D03273修改
      9.  x51137 2006/5/30 A32D04051
      10. s46746 2006-06-21  根据问题单A32D04355修改
     11.  s46746  2006-06-24  根据问题单A32D04439修改
     12.  s46746  2006-07-25  根据问题单A32D05058修改
     13.  s46746  2006.08.02  根据问题单A32D03686修改
     14.  日    期   : 2006年9月6日
          作    者   : sunxibo id:46746
          修改内容   : 问题单号：A32D05604
     15.日    期   : 2006年10月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D05960
     16.x51137 2006/11/3 A32D06511
     17.x51137 2006/11/3 A32D06821
     18.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442
     19. 日    期   : 2006年11月22日
         作    者   : luojian id:60022475
         修改内容   : 问题单号：A32D07582
     20. 日    期   : 2006年11月22日
         作    者   : luojian id:60022475
         修改内容   : 问题单号：A32D07583
     21.日    期   : 2006年12月5日
        作    者   : s46746
        修改内容   : 问题单号:A32D07740
     22.日    期   : 2007年01月03日
        作    者   : x51137
        修改内容   : 问题单号:A32D08115
     23.日    期   : 2007年3月5日
        作    者   : liurui id:40632
        修改内容   : 根据问题单号：A32D09094
     24.日    期   : 2007年3月10日
        作    者   : x51137
        修改内容   : 根据问题单号：A32D09201
     25.日    期   : 2007年04月13日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10663
     26.日    期   : 2007年05月11日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10713
     27.日    期   : 2007年06月01日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单A32D10964修改
     28.日    期   : 2007年07月10日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单A32D11966
     29.日    期   : 2007年07月31日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D12640,MM CONNECTION ACTIVE状态
                     不用记录连接建立前状态
     30.日    期   : 2007年9月27日
        作    者   : s46746
        修改内容   : 将卡无效信息从RRMM_NAS_INFO_CHANGE消息中拿掉
     31.日    期   : 2007年10月06日
        作    者   : l65478
        修改内容   : 根据问题单号：A32D12977
     32.日    期   : 2007年11月26日
        作    者   : luojian id:107747
        修改内容   : 问题单号：A32D13605,卡无效时需要更新卡状态
     33.日    期   : 2007年12月12日
        作    者   : l00107747
        修改内容   : 根据问题单号：A32D13861
     34.日    期   : 2007年12月15日
        作    者   : l00107747
        修改内容   : 问题单号:A32D13897,SIM卡在W下进行CS 注册时，
                     如果当前LAI无效，将CKSN也置为无效
     35.日    期   : 2007年12月21日
        作    者   : l00107747
        修改内容   : 问题单号:A32D13951
     36.日    期   : 2008年5月27日
        作    者   : s46746
        修改内容   : 问题单号:AT2D03209,增加列表搜索时响应寻呼处理
     37.日    期   : 2008年7月23日
        作    者   : luojian id:107747
        修改内容   : 根据问题单：AT2D04627/AT2D04237,
                     ATTEMPT TO UPDATE/ATTACH 状态对CM服务处理
     38.日    期   : 2008年7月28日
        作    者   : s46746
        修改内容   : 问题单号:AT2D03915,修改联合RAU类型,CS如果已经单独LAU成功，需要
                     发起with IMSI Attach的RAU
     39.日    期   : 2008年08月1日
        作    者   : luojian id:00107747
        修改内容   : 根据问题单AT2D04486/AT2D04822,修改CM服务请求拒绝原因值为#4,
                     RR连接释放后处理,依据 24.008 4.5.1.1,4.2.2.3
     40.日    期   : 2008年8月13日
        作    者   : l0010747
        修改内容   : 问题单号:AT2D04996/AT2D05037,IDLE ATTEMPT TO UPDATE状态只发起Normal LAU.
     41.日    期   : 2008年8月23日
        作    者   : l00130025
        修改内容   : 问题单号:At2D05016,MM注册状态修改
     42.日    期   : 2008年9月5日
        作    者   : s46746
        修改内容   : 问题单号:AT2D05514,MM通知短消息状态改变
     43.日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm状态修改
     44.日    期   : 2008年12月22日
        作    者   : o00132663
        修改内容   : 问题单号:AT2D07757,MM丢网后重回原小区，不发起LU
     45.日    期   : 2009年01月15日
        作    者   : l00130025
        修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
     46.日    期   : 2009年02月24日
        作    者   : x00115505
        修改内容   : 问题单号:AT2D09321,MM给WRR下发的NAS_INFO_CHANGE_REQ TMSI中
                     的 plmn全 F，使WAS编码失败，RRC连接建立失败。
     47.日    期   : 2009年02月28日
        作    者   : s46746
        修改内容   : 根据问题单AT2D09542,WCDMA单模下，A5/1能力设置为不支持
     49.日    期   : 2009年03月12日
        作    者   : ouyangfei id:00132663
        修改内容   : 问题单AT2D09683,丢网时，GMM上报服务状态异常导致MMC没有发起搜网。
     50.日    期   : 2009年04月21日
        作    者   : h44270
        修改内容   : 问题单号：AT2D10800/AT2D11202
     51.日    期   : 2009年04月29日
        作    者   : x00115505
        修改内容   : AT2D11365,2G下MM建立信令链接保护定时器的长度过长，从190s修改为15s。
     52.日    期   : 2009年05月11日
        作    者   : h44270
        修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
     53.日    期   : 2009年07月18日
        作    者   : s46746
        修改内容   : AT2D12943，CS Detach后，查询注册状态仍然为注册漫游网络
     54.日    期   : 2009年07月22日
        作    者   : s46746
        修改内容   : AT2D12764，双模W下注册时，MM调用GSM函数获取当前频段，导致GSM异常打印
     55.日    期   : 2009年07月24日
        作    者   : z40661
        修改内容   : 异系统重选后，紧急呼叫不能接通
     56.日    期   : 2009年07月31日
        作    者   : x00115505
        修改内容   : AT2D13428,2G下联合注册后，去注册PS域，之后发起语音呼叫，网络回复Cm Service Reject（#4），呼叫失败。
     57. 日    期   : 2009年08月11日
         作    者   : z40661
         修改内容   : 问题单号：AT2D13689，搜网时，拨打紧急呼叫，网络回复原因值4时，且当前PLMN被禁止时，再一次发送Cm Service Req，原因为MM缓存未被清空
     58.日    期   : 2009年09月23日
        作    者   : x00115505
        修改内容   : AT2D14632,开机注册失败，查询CREG返回 1
     59.日    期   : 2010年3月2日
        作    者   : o00132663
        修改内容   : NAS R7协议升级，增加链路释放增强处理等特性
*******************************************************************************/
#include        "MM_Inc.h"
#include        "stdlib.h"
#include        "GmmMmInterface.h"
#include        "NasMmSndOm.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#include "NasMmEcall.h"
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

#include "MmCmInterface.h"
#include "MmCcInterface.h"
#include "MmSsInterface.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

extern MM_SUSPEND_MSG_BUF_ST gstMmSuspendMsgQue;
extern MM_TIMER_ST  gstMmTimerSuspend;

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_COM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 变量定义
*****************************************************************************/
RRC_TO_MMCC_REL_CAUSE_STRU g_astRrcToMmCcRelCause[] =
{
    {RRC_REL_CAUSE_RR_NORM_EVENT             ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_EVENT},
    {RRC_REL_CAUSE_RR_UNSPEC                 ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED},
    {RRC_REL_CAUSE_RR_PRE_EMPT_REL           ,  NAS_MMCM_REL_CAUSE_RR_REL_PREEMPTIVE_RELEASE},
    {RRC_REL_CAUSE_RR_CONGEST                ,  NAS_MMCM_REL_CAUSE_RR_REL_CONGESTION},
    {RRC_REL_CAUSE_RR_RE_EST_REJ             ,  NAS_MMCM_REL_CAUSE_RR_REL_REEST_REJ},
    {RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST   ,  NAS_MMCM_REL_CAUSE_RR_REL_DIRECTED_SIGNAL_CONN_REEST},
    {RRC_REL_CAUSE_RR_USER_INACT             ,  NAS_MMCM_REL_CAUSE_RR_REL_USER_INACTIVE},
    {RRC_REL_CAUSE_UTRAN_RELEASE             ,  NAS_MMCM_REL_CAUSE_RR_REL_UTRAN_RELEASE},
    {RRC_REL_CAUSE_NAS_REL_SUCCESS           ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_REL_ABSENT            ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_ABORT                 ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_NAS_STOP_SETUP            ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ},
    {RRC_REL_CAUSE_CONN_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_CONN_FAIL},
    {RRC_REL_CAUSE_NAS_DATA_ABSENT           ,  NAS_MMCM_REL_CAUSE_RR_REL_NAS_DATA_ABSENT},
    {RRC_REL_CAUSE_RRC_ERROR                 ,  NAS_MMCM_REL_CAUSE_RR_REL_RRC_ERROR},
    {RRC_REL_CAUSE_RL_FAILURE                ,  NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE},
    {RRC_REL_CAUSE_GAS_TIMEOUT               ,  NAS_MMCM_REL_CAUSE_RR_REL_NORMAL_UNSPECIFIED},
    {RRC_REL_CAUSE_OTHER_REASON              ,  NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON},
    {RRC_REL_CAUSE_NO_RF                     ,  NAS_MMCM_REL_CAUSE_RR_REL_NO_RF},
    {RRC_REL_CAUSE_RLC_ERROR                 ,  NAS_MMCM_REL_CAUSE_RR_REL_RLC_ERR_OR},
    {RRC_REL_CAUSE_CELL_UPDATE_FAIL          ,  NAS_MMCM_REL_CAUSE_RR_REL_CELL_UP_DATE_FAIL},
    {RRC_REL_CAUSE_T314_EXPIRED              ,  NAS_MMCM_REL_CAUSE_RR_REL_T314_EXPIRED},
    {RRC_REL_CAUSE_W_RL_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_W_RL_FAIL},

    {RRC_REL_CAUSE_G_RL_FAIL                 ,  NAS_MMCM_REL_CAUSE_RR_REL_G_RL_FAIL},
};

EST_RSLT_TO_MMCC_REL_CAUSE_STRU g_astEstRsltToMmCcRelCause[] =
{
    {RRC_EST_SUCCESS                            ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_PRESENT                            ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_ESTING                             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_DELING                             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_RJ_CONGEST                         ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CONGESTION},
    {RRC_EST_RJ_UNSPEC                          ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UNSPECIFIED},
    {RRC_EST_ACCESS_BARRED                      ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR},
    {RRC_EST_EST_CONN_FAIL                      ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_EST_CONN_FAIL},
    {RRC_EST_RJ_INTER_RAT                       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RJ_INTER_RAT},
    {RRC_EST_IMMEDIATE_ASSIGN_REJECT            ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT},
    {RRC_EST_RANDOM_ACCESS_REJECT               ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_REJECT},
    {RRC_EST_PAGING_ACCESS_BARRED               ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_REGISTER_ACCESS_BARRED             ,   (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT},
    {RRC_EST_OTHER_ACCESS_BARRED                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR},
    {RRC_EST_RJ_T3122_RUNNING                   ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING},
    {RRC_EST_RJ_NO_RF                           ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RF},
    {RRC_EST_RJ_SNW                             ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_LOW_LEVEL_SEARCHING_NETWORK},
    {RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_VALID_INFO},
    {RRC_EST_RJ_RA_FAIL                         ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RANDOM_ACCESS_SEND_FAIL},
    {RRC_EST_RJ_NOT_ALLOW                       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_UE_NOT_ALLOW},
    {RRC_EST_RJ_TIME_OUT                        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_TIME_OUT},
    {RRC_EST_RJ_RA_RESOURCE_FAIL                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_NO_RANDOM_ACCESS_RESOURCE},
    {RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_IMMEDIATE_ASSIGNED_MSG},
    {RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL    ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACTIVE_PHYSICAL_CHANNEL_FAIL},
    {RRC_EST_RJ_AIRMSG_DECODE_ERR               ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_AIR_MSG_DECODE_ERROR},
    {RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT       ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT},
    {RRC_EST_RJ_INVALID_UE_STATE                ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE},
    {RRC_EST_RJ_CELL_BAR                        ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED},
    {RRC_EST_RJ_FASTRETURN_LTE                  ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_FAST_RETURN_TO_LTE},
    {RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           ,   NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_RA_FAIL_NO_VALID_INFO},
};


NAS_MM_LAU_EST_CNF_TO_T3212_START_SCENE_STRU g_astLauEstCnfRsltToT3212StartScene[] =
{
    {RRC_EST_SUCCESS                            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_PRESENT                            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_ESTING                             ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_DELING                             ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_RJ_CONGEST                         ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_UNSPEC                          ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_ACCESS_BARRED                      ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_EST_CONN_FAIL                      ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_INTER_RAT                       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_IMMEDIATE_ASSIGN_REJECT            ,   NAS_MM_T3212_START_SCENE_BUTT},
    {RRC_EST_RANDOM_ACCESS_REJECT               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_PAGING_ACCESS_BARRED               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_REGISTER_ACCESS_BARRED             ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_OTHER_ACCESS_BARRED                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_RJ_T3122_RUNNING                   ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_NO_RF                           ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_SNW                             ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_FAIL                         ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_NOT_ALLOW                       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_TIME_OUT                        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_RESOURCE_FAIL                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL    ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_AIRMSG_DECODE_ERR               ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT       ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_INVALID_UE_STATE                ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_CELL_BAR                        ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR},
    {RRC_EST_RJ_FASTRETURN_LTE                  ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
    {RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           ,   NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},
};

NAS_MM_T3212_START_SCENE_CFG_TBL_STRU g_astNasMmT3212StartSceneCfgTbl[] =
{
    /* 当前BIT位,    配置控制场景 */
    {0,             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL},            /* BIT0控制: LAU建联时候失败启动T3212场景 */
    {1,             NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS},            /* BIT1控制: LAU建联时候被REL启动T3212场景 */
};
#if (FEATURE_ON == FEATURE_LTE)
CSFB_RSLT_TO_MMCC_REL_CAUSE_STRU g_astCsfbRsltToMmCcRelCause[] =
{
    {MM_LMM_CSFB_SERVICE_RSLT_FAILURE                           ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_LMM_LOCAL_FAIL},
    {MM_LMM_CSFB_SERVICE_RSLT_AUTH_REJ                          ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_AUTH_REJ},
    {MM_LMM_CSFB_SERVICE_RSLT_T3417EXT_TIME_OUT                 ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_T3417_TIME_OUT},
    {MM_LMM_CSFB_SERVICE_RSLT_MMC_DETACH_FAIL                   ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_APP_DETACH_SERVICE},
    {MM_LMM_CSFB_SERVICE_RSLT_CN_DETACH_FAIL                    ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_CN_DETACH_SERVICE},
    {MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_OTHERS       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_OTHERS},
    {MM_LMM_CSFB_SERVICE_RSLT_VERIFY_CSFB_FAIL_FOR_EMM_STATE    ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_FOR_EMM_STATE},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_SMS_ONLY       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_SMS_ONLY},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_PS_ONLY        ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_PS_ONLY},
    {MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_ABNORMAL       ,NAS_MMCM_REL_CAUSE_CSFB_LMM_FAIL_TAU_COLL_ABNORMAL},
};
#endif
/*lint -save -e958 */

/*******************************************************************************
  Module:   Mm_ComNasInfoSav
  Function: MM 初始化
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇      2003.12.16   新版作成
  2.张志勇   2004.10.25   数据存储结构变更对应
  3.日    期   : 2006年9月6日
    作    者   : sunxibo id:46746
    修改内容   : 问题单号：A32D05604
  4.日    期   : 2007年11月26日
    作    者   : luojian id:107747
    修改内容   : 问题单号：A32D13605
  5.日    期   : 2009年04月21日
    作    者   : h44270
    修改内容   : 问题单号：AT2D10800/AT2D11202
  6.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  7.日    期   : 2012年02月29日
    作    者   : l00130025
    修改内容   : DTS2012022206186:不发起LAU,而注册成功时，需要同步注册状态给AS
  8.日    期   : 2012年03月20日
    作    者   : l00130025
    修改内容   : DTS2012030105247,NAS只在网侧实际发起鉴权时,通知W SecurityKey，其它情况下由WAS调用对应接口获取
*******************************************************************************/
VOS_VOID Mm_ComNasInfoSav (
                       VOS_UINT8    ucAttachState,
                       VOS_UINT8    ucCksnFlg
                       )
{
    /* 更新CS注册状态 */
    if ( g_MmSubLyrShare.MmShare.ucCsAttachState != ucAttachState )
    {
        g_MmSubLyrShare.MmShare.ucCsAttachState = ucAttachState;
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_ATTACH_FLG);
        if ((g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL)
          &&(g_MmGlobalInfo.usCauseVal != NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED))
        {
            Mm_SndSmsRegStsInd( g_MmSubLyrShare.MmShare.ucCsAttachState );
        }
    }
    else
    {
        if ((g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL)
          ||(g_MmGlobalInfo.usCauseVal == NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED))
        {

            Mm_SndSmsRegStsInd(MM_STATUS_ATTACHED);
        }
    }


    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);
    }


    /* 更新CS域安全数据 */
    if ( NAS_MML_GetSimCsSecurityCksn() != ucCksnFlg )
    {
        NAS_MML_SetSimCsSecurityCksn(ucCksnFlg);
        if ( MM_CKSN_INVALID == NAS_MML_GetSimCsSecurityCksn() )
        {
            NAS_MML_InitCsSecurityUmtsCkInvalid();
            NAS_MML_InitCsSecurityUmtsIkInvalid();

            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_DEL_KEY_FLG);
        }
        else
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
            }
        }
    }
    return;                                                                     /* 返回                                     */
}

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */

/*******************************************************************************
  Module:   Mm_ComRandJudge
  Function: 判断RAND是否变化
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   MM_TRUE     RAND变化
            MM_FALSE    RAND不变化
  History:
      1.  张志勇     2003.12.10  新版做成
*******************************************************************************/

VOS_UINT8 Mm_ComRandJudge()
{
    VOS_UINT8                       i;
    VOS_UINT8                   ucRet = MM_FALSE;

    for ( i = 0; i < 16; i++ )
    {
        if ( g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand[i] !=
            g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand[i] )
        {
            ucRet = MM_TRUE;
            break;
        }
    }
    return ucRet;

}

/*******************************************************************************
  Module:   Mm_ComUpdateUsimFileReq
  Function: 更新卡文件
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:
  History:
      1.  hezhijun     2015.02.17  新版做成
*******************************************************************************/
VOS_VOID Mm_ComUpdateUsimFileReq(
    VOS_VOID
)
{
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
    }

    return;
}


/*******************************************************************************
  Module:   Mm_ComSvcStaJudge
  Function: 判断服务状态是否改变
  Input:    VOS_UINT8 ucSvcStatus
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.16  新版做成
*******************************************************************************/

VOS_VOID Mm_ComSvcStaJudge(VOS_UINT8 ucSvcStatus)
{
    if ( ucSvcStatus != g_MmGlobalInfo.ucMmServiceState )
    {
        g_MmGlobalInfo.ucMmServiceState = ucSvcStatus;
    }
}

/*******************************************************************************
  Module:   Mm_ComRelAllMmConn
  Function: 释放所有MM连接,正在建的MM连接
  Input:    enMmccRelCause - 释放原因值
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.16  新版做成
      2.  s46746     2006.08.09  根据问题单A32D05269修改

      3.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态

      4.日    期   : 2012年2月24日
        作    者   : w00167002
        修改内容   : CSFB&PPAC&ETWS&ISR 开发:清除CSFB存在标志
      5.日    期   : 2012年5月26日
        作    者   : w00176964
        修改内容   : GUL BG项目调整:支持CSFB时先不清除CC SS的缓存,等收到LMM的注册结果清除
      6.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      7.日    期   : 2013年01月23日
        作    者   : s00217060
        修改内容   : 问题单: DTS2013012106172,清除紧急呼的标志
      8.日    期   : 2013年3月30日
        作    者   : l00167671
        修改内容   : 主动上报AT命令控制下移至C核
      9.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容   :DTS2013082903019:支持ss重发功能
      10.日    期   :2013年10月18日
         作    者   :z00161729
         修改内容   :DTS2013101900866:mm在wait for mm connection状态收到gas丢网消息没有给cc回复rel ind导致呼叫T303超时呼叫失败
      11.日    期   :2013年10月20日
         作    者   :z00234330
         修改内容   :DTS2013111903821:MM回复的ti不正确,导致上层业务没有触发重发操作。
      12.日    期   : 2014年6月13日
         作    者   : w00242748
         修改内容   : DSDS 新特性
      13.日    期   :2014年7月22日
         作    者   :s00217060
         修改内容   :K3V3 多模多天线特性:CS业务链接释放时,通知MMC
      14.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRelAllMmConn(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT8                                               i;

    /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
    VOS_UINT8                                               ucCsSrvFlg;

    ucCsSrvFlg  = VOS_FALSE;
    /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */


    for ( i = 0; i < 7; i++ )
    {
        /*lint -e701*/
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在CC建立的MM连接                       */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在CC建立的MM连接                       */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[0] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {

            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[0] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i , enMmCcRelCause );
        }
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[1] & (0x01 << i) ) )
        {
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
            ucCsSrvFlg  = VOS_TRUE;
            /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

            /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i + 8, enMmCcRelCause );
        }

        /*lint +e701*/
    }


    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {

        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                       enMmCcRelCause);


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
    }



    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        ucCsSrvFlg  = VOS_TRUE;
        /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
    }

    /* 将MM连接存在标志设置成没有 */
    g_MmGlobalInfo.ucMMConnEstingPD  = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI       = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI       = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI      = NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]     = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]    = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]    = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]   = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]   = 0;

    NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    /* CSFB结束 */

    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
#endif

    NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

    /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
    /* 之前有CS业务存在，释放链接时通知MMC */
    if (VOS_TRUE == ucCsSrvFlg)
    {
        Mm_SndMmcCmSvcInd(VOS_FALSE);
    }
    /* Add by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */

}
/*******************************************************************************
  Module:   Mm_ComRelAllMmConnExcEmergencyCall
  Function: 释放除了紧急呼之外所有MM连接,正在建的MM连接
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.
      2.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      3.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容   :DTS2013082903019:支持ss重发功能
      4.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_ComRelAllMmConnExcEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    VOS_UINT8               i;

    /*lint -e701*/
    for (i = 0; i < 7; i++)
    {
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[0] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC重建立的MM连接 */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnExtFlg[1] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC建立的MM连接并且不是紧急呼         */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[0] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i, enMmCcRelCause);
        }
        /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
           并不能判断哪一个呼叫是紧急呼 */
        if ((0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            aucMMConnReestFlg[1] & (0x01 << i)))
            && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg))
        {
            /* 存在CC重建立的MM连接                     */
            Mm_SndCcRelInd(i + 8, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[0] & (0x01 << i)))
        {                                                                       /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            aucMMConnExtFlg[1] & (0x01 << i)))
        {                                                                       /* 存在SS建立的MM连接                       */
            Mm_SndSsRelInd(i + 8, enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[0] & (0x01 << i)))
        {                                                                       /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i , enMmCcRelCause);
        }
        if (0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            aucMMConnExtFlg[1] & (0x01 << i)))
        {                                                                       /* 存在SMS建立的MM连接                      */
            Mm_SndSmsRelInd(i + 8, enMmCcRelCause);
        }
    }

    /*lint +e701*/

    /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
       并不能判断哪一个呼叫是紧急呼 */
    if ((NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg))
    {
        /* 正在建立MM连接且不是紧急呼的MM连接       */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                       ucMMConnEstingTI,
                       enMmCcRelCause);
    }
    if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                       ucMMConnEstingTI, enMmCcRelCause);
    }
    if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI,
                        enMmCcRelCause);
    }
    /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
       并不能判断哪一个呼叫是紧急呼 */
    if ((MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        && (MMCC_EMERGENCY_CALL != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        RcvXXEstReq.ulCallType))
    {
        /* 有缓存的MM连接建立请求                   */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                       RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);                       /* 指示缓存的MM连接建立失败                 */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* 清除缓存标志                             */
    }
    if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {                                                                           /* 有缓存的MM连接建立请求                   */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        RcvXXEstReq.ulTransactionId,
                        enMmCcRelCause);                        /* 指示缓存的MM连接建立失败                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* 清除缓存标志                             */
    }
    if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {                                                                           /* 有缓存的MM连接建立请求                   */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                       RcvXXEstReq.ulTransactionId, enMmCcRelCause);

        /* 指示缓存的MM连接建立失败                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_FALSE;                                                         /* 清除缓存标志                             */
    }


    /* 以下判断仅针对只支持一个CC呼叫的情况，当支持多个CC呼叫功能时，
       并不能判断哪一个呼叫是紧急呼 */
    if (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg)
    {
        g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] = 0;
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]  = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]  = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] = 0;

    if ( ( MM_CONST_NUM_0 ==
      g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 ==
      g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
    }

}

/*******************************************************************************
  Module:   Mm_ComRejectCause11
  Function: 收到原因值为#11的处理
  Input:    VOS_UINT8 ucType
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.09  新版做成
  2. 日    期   : 2008年8月21日
     作    者   : l00130025
     修改内容   : 问题单号:At2D05016,MM注册状态修改
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  7.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/

VOS_VOID Mm_ComRejectCause11(VOS_UINT8 ucType)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        /* 注册被12拒绝不用尝试呼叫重发 */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
    }

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* 设置服务状态                             */
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* 设置更新状态                             */

    switch(ucType)
    {
    case MM_ATTACH:
    case MM_RAU:
    case MM_NET_DETACH:
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        Mm_ComUpdateUsimFileReq();

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause11:WARNING: Type Abnormal");
        break;
    }
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                                       /* 向RRC发送RRMM_REL_REQ(CS域)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* 设置释放RR连接时候进入的状态             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause11:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause11:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}



/*******************************************************************************
  Module:   Mm_ComRejectCause13
  Function: 收到原因值为#13的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.16  新版做成
  2. 日    期   : 2008年8月21日
     作    者   : l00130025
     修改内容   : 问题单号:At2D05016,MM注册状态修改
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年9月12日
    作    者   : z00161729
    修改内容   : DTS2013082903019:支持ss重发功能
  7.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRejectCause13(VOS_UINT8 ucType)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                       */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause13:INFO: MmServiceState is MM_LIMITED_SERVICE");
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* 设置更新状态                             */

    switch(ucType)
    {
    case MM_ATTACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        Mm_ComUpdateUsimFileReq();

        break;
    case MM_RAU:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    case MM_NET_DETACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        break;
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause13:WARNING: Type Abnormal");
        break;
    }
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* 设置释放RR连接时候进入的状态             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}

/*******************************************************************************
  Module:   Mm_ComRejectCause15
  Function: 收到原因值为#15的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.16  新版做成
  2. 日    期   : 2008年8月21日
     作    者   : l00130025
     修改内容   : 问题单号:At2D05016,MM注册状态修改
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年9月12日
    作    者   : z00161729
    修改内容   : DTS2013082903019:支持ss重发功能
  7.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRejectCause15(VOS_UINT8 ucType)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                       /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                       */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause15:INFO: MmServiceState is MM_LIMITED_SERVICE");
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);                  /* 设置更新状态                             */

    switch(ucType)
    {
    case MM_ATTACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();
        /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* 更新SIM卡更新状态                        */
        Mm_ComUpdateUsimFileReq();

        break;
    case MM_RAU:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    case MM_NET_DETACH:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();
        /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);*/                     /* 更新SIM卡更新状态                        */
        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        break;
    case MM_SERVICE_REQ:
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComRejectCause15:WARNING: Type Abnormal");
        break;
    }
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                                                MM_IDLE_LIMITED_SERVICE;        /* 设置释放RR连接时候进入的状态             */
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*" \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause15:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*" \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause15:NORMAL: STATUS is  MM_IDLE_LIMITED_SERVICE");
    }
}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvAuthenRej
  Function: 鉴权失败的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.09  新版做成
  2. 日    期   : 2007年06月01日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单A32D10964修改
  3.日    期   : 2008年09月03日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403,mm状态修改
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  6.日    期   : 2012年12月29日
    作    者   : w00167002
    修改内容   : DTS2012122900619:DCM MM-18-01-22 局方要求更新CS:4F20文件，PS更新
                 4F52文件;balong更新了PS没有更新CS。
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   : 2013年06月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  9.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 10.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口
 11.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvAuthenRej()
{
    VOS_UINT32                          ulRet;

    ulRet = PS_USIM_SERVICE_NOT_AVAILIABLE;

    Mm_TimerStop(MM_TIMER_T3210);
    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_RR_REL_AUTH_REJ);

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComAuthenRcvAuthenRej:INFO: MmServiceState is MM_NO_IMSI");
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;
    /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);*/                     /* 更新SIM卡更新状态                        */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);                     /* 更新SIM卡更新状态                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);                     /* 更新SIM卡更新状态                        */

        /* DCM MM-18-01-22 要求更新CS:4F20文件，PS更新4F52文件 */
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKC_ID);
        }
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenRej:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        /* A32D10964 ==> */
        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S0_E23(VOS_NULL_PTR);
        }
        /* <== A32D10964 */
    }
}


/*******************************************************************************
  Module:   Mm_ComTmsiReloc
  Function: TMSI RELOC过程的公共处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.日    期   : 2010年9月30日
    作    者   : 欧阳飞 00132663
    修改内容   : 根据问题单号DTS2010092902368,TMSI只在等效PLMN内有效
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年3月24日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发,BBIT问题修改
  5.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  6.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*******************************************************************************/

VOS_VOID Mm_ComTmsiReloc()
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    NAS_MML_LAI_STRU                   *pstCurrCampLai = VOS_NULL_PTR;

    pstCurrCampLai = NAS_MML_GetCurrCampLai();
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    pstCsSuccLai->stPlmnId.ulMcc
        = g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.PlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc
        = g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.PlmnId.ulMnc;
    pstCsSuccLai->aucLac[0] = (g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
    pstCsSuccLai->aucLac[1] = (g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai.ulLac) & (0x00FF);

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ( MM_MS_ID_IMSI_PRESENT ==
        ( g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg &
                                                    MM_MS_ID_IMSI_PRESENT ) )
    {
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMSI无效                             */

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMSI_PRESENT;    /* 设置IMSI有效                             */

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

    }
    else
    {
        if ( MM_MS_ID_TMSI_PRESENT ==

                    ( g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg &
                                                MM_MS_ID_TMSI_PRESENT ) )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }

        }

    }
    Mm_ComMsgTmsiRelocCpltSnd();                                                /* 发送TMSI REALLOCATION COMPLETE           */
}

/*******************************************************************************
  Module:   Mm_ComInfo
  Function: MM INFO过程的公共处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.  s46746  2005.10.20  修改
      3.  x51137 2006/5/30 A32D04051

      4.日    期   : 2011年7月13日
        作    者   : zhoujun 40661
        修改内容   : SIM卡内容更新到MML中
*******************************************************************************/

VOS_VOID Mm_ComInfo()
{

    Mm_SndMmcInfoInd();
}

/*******************************************************************************
  Module:   Mm_ComIdentity
  Function: IDENTITY过程的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
*******************************************************************************/

VOS_VOID Mm_ComIdentity()
{
    MM_MSG_ID_RSP_STRU    Msg;

    NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

    switch( g_MmMsgIdReq.MmIeIdType.ucIDType )
    {
    case MM_IE_MI_ID_TYPE_IMSI:
        if ( 0 != ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
            & MM_MS_ID_IMSI_PRESENT ) )
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMSI_PRESENT;
        }
        else
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_ABSENT;
        }
        break;
    case MM_IE_MI_ID_TYPE_IMEI:
        Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMEI_PRESENT;
        break;
    case MM_IE_MI_ID_TYPE_IMEISV:
        Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_IMEISV_PRESENT;
        break;
    case MM_IE_MI_ID_TYPE_TMSI:
        if ( 0 != ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
            & MM_MS_ID_TMSI_PRESENT ) )
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_TMSI_PRESENT;
        }
        else
        {
            Msg.MmIeMobileId.MobileID.ucMsIdFlg = MM_MS_ID_ABSENT;
        }
        break;
    default:
        break;
    }
    Mm_ComMsgIdRspSnd(&Msg);                                                    /* IDENTITY RESPONSE消息                    */

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_IDResInfoRecord(g_MmMsgIdReq.MmIeIdType.ucIDType);
#endif

}

/*******************************************************************************
  Module:   Mm_ComAbortCause6
  Function: ABORT过程的处理,#6
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.  日    期   : 2008年09月03日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D05403,mm注册状态修改
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   : 2013年9月12日
    作    者   : z00161729
    修改内容   : DTS2013082903019:支持ss重发功能
  7.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
  9.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*******************************************************************************/

VOS_VOID Mm_ComAbortCause6()
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME);

    Mm_ComSaveProcAndCauseVal(MM_MM_NET_ABORT, NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);        /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComAbortCause6:INFO: MmServiceState is MM_NO_IMSI");
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

    NAS_MML_InitUeIdTmsiInvalid();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;

    Mm_ComUpdateUsimFileReq();

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;                   /* 设置释放RR连接时候进入的状态             */
    Mm_TimerStart(MM_TIMER_T3240);
    /* Mm_SndMmcCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME); */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAbortCause6:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComAbortCause17
  Function: ABORT过程的处理,#17
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComAbortCause17()
{
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_NETWORK_FAILURE);

    Mm_ComSaveProcAndCauseVal(MM_MM_NET_ABORT, NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);   /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;            /* 设置释放RR连接时候进入的状态             */
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                              */
    /*" \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAbortCause17:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComT3214orT3216Expired
  Function: T3214或者T3216溢出的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.12  新版做成
******************************************************************************/

VOS_VOID Mm_ComT3214orT3216Expired()
{
    Mm_ComAuthMsRej();
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */

}

/*******************************************************************************
  Module:   Mm_ComDelRandRes
  Function: 删除RAND和RES的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  李  彬   2004.01.07   新版做成
      2.  张志勇   2004.10.25   数据存储结构变更对应
*******************************************************************************/

VOS_VOID Mm_ComDelRandRes()
{
    VOS_UINT8                   i;

    g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg = MM_AUTHEN_RES_ABSENT;

    g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg = MM_AUTHEN_RES_ABSENT;

    /* Modified by 张志勇 2004.10.25 begin */
    /* g_MmGlobalInfo.AuthenCtrlInfo.ulRes = 0; */
    PS_MEM_SET(g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 0, 4);
    /* Modified by 张志勇 2004.10.25 end */
    g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;
    /* Modified by 张志勇 2004.10.25 begin */
    /* g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] = 0;
       g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] = 0;
       g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] = 0; */
    PS_MEM_SET(g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 0, 12);
    /* Modified by 张志勇 2004.10.25 end */
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_ABSENT;
    for ( i = 0; i < 16; i ++ )
    {
        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand[i] = 0;
        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand[i] = 0;
    }
}

/*******************************************************************************
  Module:   Mm_ComT3218Expired
  Function: T3218溢出的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.12  新版做成
*******************************************************************************/

VOS_VOID Mm_ComT3218Expired()
{
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

}

/*******************************************************************************
  Module:   Mm_ComAuthenNoAutn
  Function: 消息中不含AUTN的场合
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.日    期   : 2013年1月30日
        作    者   : w00176964
        修改内容   : DTS2013012906743:连续3次鉴权失败才认为鉴权失败
      3.日    期  : 2013年11月15日
        作    者  : m00217266
        修改内容  : sim卡鉴权失败原因上报
*******************************************************************************/

VOS_VOID Mm_ComAuthenNoAutn()
{
    MM_MSG_AUTHENTICATION_FAIL_STRU     Msg;
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAuthFailFlg;

    ucAuthFailFlg   = VOS_FALSE;
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE;

    Mm_ComMsgAuthFailSnd(&Msg);                                                 /* 发送AUTHENTICATION FAILURE消息           */
    NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_AUT_UNACCEPTABLE);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,
                              NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt++;

    /* R6版本以后连续三次鉴权失败UE可以认为鉴权失败 */
    if ((PS_PTL_VER_R6  <= cVersion)
     && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
    {
        ucAuthFailFlg = VOS_TRUE;
    }

    /* 此处实现原来参考R5协议连续两次鉴权失败UE可以认为鉴权失败 */
    if ((PS_PTL_VER_R5  >= cVersion)
     && ((MM_CONST_NUM_3   == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
      || (MM_MAC_CODE_FAIL == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
    {
        ucAuthFailFlg = VOS_TRUE;
    }

    if (VOS_TRUE == ucAuthFailFlg)
    {
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
        Mm_ComAuthMsRej();

    }
    else
    {
        g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_MAC_CODE_FAIL;       /* 设置上一次的错误信息                     */
        Mm_TimerStart(MM_TIMER_T3214);
    }
}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvAuthenReq
  Function: 收到AUTHEN REQ的处理
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  李  彬  2003.12.10  新版做成
  2.  张志勇  2004.10.25  数据存储结构变更对应
  3.  张志勇     2005.01.27  007037 for MM
  4.  s46746  2005.09.05  for HSS4100 V200R001
  5.日    期   : 2006年12月5日
    作    者   : s46746
    修改内容   : 问题单号:A32D07740
  6.日    期   : 2010年11月19日
    作    者   : s46746
    修改内容   : 问题单号:DTS2010111604811,鉴权过程中接收到相同鉴权消息处理
  7.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  8.日    期   : 2014年10月20日
    作    者   : w00167002
    修改内容   : DTS2014102000868:在鉴权成功后才更新CKSN
  9.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvAuthenReq()
{
    VOS_UINT8                           i;
    MM_MSG_AUTHENTICATION_RSP_STRU      Msg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType   = NAS_MML_GetCurrNetRatType();

    /* 增加 SIM 卡鉴权和 USIM 卡在 GSM 下鉴权 */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus()) /* 卡不存在 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_WARNING,
                    "Mm_ComAuthenRcvAuthenReq: WARNING: Sim is invalid!");

        /* 此条消息被丢弃, 不作处理，直接返回 */
        return;
    }
    /* 为 SIM 卡或者在 USIM 卡在 GSM 网中的 GSM 鉴权 */
    else if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
          || ((MM_IE_AUTN_ABSENT == g_MmMsgAuthReq.ucAutnFlg)
          && (NAS_MML_NET_RAT_TYPE_GSM == enRatType)))
    {

        MM_GsmAuthProc();

        return;
    }
    else
    {

    }
    /* USIM 卡在 UMTS 网中鉴权，或 USIM 卡在 GSM 网中的 UMTS 鉴权按下面进行处理 */


    if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
    {                                                                           /* MS不支持UMTS ALGO                        */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComAuthenRcvAuthenReq:WARNING: Not support UMTS ALGO");
        return;
    }
    PS_MEM_SET(&Msg,0,sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);
    PS_MEM_CPY(
                g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                g_MmMsgAuthReq.MmIeRAND.aucRandValue,
                16 * sizeof(VOS_UINT8)
                );

    /* 做3G鉴权，清除2G鉴权标记 */
    NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);

    if ( MM_IE_AUTN_PRESENT == g_MmMsgAuthReq.ucAutnFlg )
    {                                                                           /* AUTN存在的场合                           */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAutnLen
            = g_MmMsgAuthReq.MmIeAUTN.ucAutnLen;
        for ( i = 0; i < g_MmMsgAuthReq.MmIeAUTN.ucAutnLen; i++ )
        {
            g_MmGlobalInfo.AuthenCtrlInfo.aucAutn[i]
                = g_MmMsgAuthReq.MmIeAUTN.aucAutn[i];
        }
        if ( MM_AUTHEN_RAND_ABSENT ==  g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg )
        {
            PS_MEM_CPY(
                        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                        16 * sizeof(VOS_UINT8)
                        );
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_PRESENT;   /* 设置RAND存在标识                         */
            /*A32D07740==>*/
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat   = MM_AUTHEN_RAND_REPEAT;
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
            /*<==A32D07740*/
            Mm_SndAgentUsimAuthenReq();                                         /* 发送AGENT_USIM_AUTHENTICATION_REQ        */
            Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                              /* 启动保护TIMER                            */
            /* Mm_TimerStart(MM_TIMER_PROTECT); */
        }
        else
        {
            if ( ( MM_FALSE == Mm_ComRandJudge() ) )
            {                                                                   /* RAND相同                                 */
                /* 前两次 RAND 是否相同 */
                if (MM_AUTHEN_RAND_DIFFER == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
                {
                    /* 本次 RAND 与上次相同 */
                    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat = MM_AUTHEN_RAND_REPEAT;

                    Mm_SndAgentUsimAuthenReq();                                 /* 发送AGENT_USIM_AUTHENTICATION_REQ        */

                    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;

                    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                      /* 启动保护TIMER                            */
                }
                /* 前两次 RAND 相同而且 RES 存在，本次鉴权类型与上次相同 */
                else if ((MM_AUTHEN_RES_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg)
                    && (AUTHENTICATION_REQ_UMTS_CHALLENGE == g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType))
                /* if ( MM_AUTHEN_RES_PRESENT ==
                                g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg ) */
                {                                                               /* RES存在的场合                            */

                    /* Modified by 张志勇 2004.10.25 begin */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[0] =  */
                    /*    (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ulRes & 0xFF);  */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[1] = */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 8 )    */
                    /*                                                & 0xFF);  */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[2] =                   */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 16 )   */
                    /*                                                 & 0xFF); */
                    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[3] =                   */
                    /* (VOS_UINT8)( ( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 24 )   */
                    /*                                                 & 0xFF); */
                    PS_MEM_CPY(Msg.MmIeAuthRspPara.aucSgnfcntRES,
                                g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);
                    /* Modified by 张志勇 2004.10.25 end */
                    if ( MM_CONST_NUM_0 !=
                            g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength )
                    {
                        Msg.ucAutnRspParaExtFlg = MM_IE_AUTN_EXT_PRESENT;
                        Msg.MmIeAuthRspParaExt.ucLength =
                        (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);
                        /* Modified by 张志勇 2004.10.25 begin */
                        /* for ( i = 0; i < 4; i ++ )                    */
                        /* {                                              */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i] =          */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);  */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 4] =    */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);  */
                        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 8] =          */
                        /* (VOS_UINT8)((g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] >>  */
                        /*                                 ( i * 8 ) ) & 0xFF);   */
                        /* }                                                  */
                        PS_MEM_CPY(Msg.MmIeAuthRspParaExt.aucRES,
                                  g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 12);
                        /* Modified by 张志勇 2004.10.25 end */
                    }

                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvAuthenReq: Send Auth Rsp");
                    NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);
                    
                    Mm_ComMsgAuthRspSnd(&Msg);                                  /* 发送AUTHENTICATION RESPONSE(RES)         */
                }
                else
                {                                                               /* RES不存在的场合                          */
                    /* Res 是否存在的标志变量在鉴权成功后设置 */
                    /*g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg =
                                                        MM_AUTHEN_RES_PRESENT;*/  /* 设置RES存在的标识                        */

                    Mm_SndAgentUsimAuthenReq();                                 /* 发送AGENT_USIM_AUTHENTICATION_REQ        */

                    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;

                    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);                      /* 启动保护TIMER                            */
                    /* Mm_TimerStart(MM_TIMER_PROTECT); */
                }
            }
            else
            {                                                                   /* RAND不相同的场合                         */
                PS_MEM_CPY(
                        g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                        16 * sizeof(VOS_UINT8)
                        );

                /* 本次 RAND 与上次不同，需要清除RES存在标志 */
                g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat   = MM_AUTHEN_RAND_REPEAT;
                g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
                g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg       = MM_AUTHEN_RES_ABSENT;
                g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg      = MM_AUTHEN_RES_ABSENT;

                Mm_SndAgentUsimAuthenReq();
                Mm_TimerStart(MM_TIMER_PROTECT_AGENT);
            }
        }
    }
    else
    {
        Mm_ComAuthenNoAutn();
    }
}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnfSuccess
  Function: 收到USIM发来的AGENT_USIM_AUTHENTICATION_CNF(SUCCESS)的处理
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  李  彬  2003.12.12  新版做成
  2.  张志勇  2004.10.25  数据存储结构变更对应
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

  4.日    期   : 2012年12月29日
    作    者   : w00167002
    修改内容   : DTS2012122900619:DCM MM-18-01-22 局方要求更新CS:4F20文件，PS更新
                 4F52文件;balong更新了PS没有更新CS。
  5.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口修改
  6.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口
  7.日    期   : 2014年4月175日
    作    者   : s00246516
    修改内容   : DTS2014041700472:使用2G SIM卡，PAD形态上出现鉴权被网络拒绝
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnfSuccess()
{
    /* Deleted by 张志勇 2004.10.25 begin */
    /* VOS_UINT8                               i;*/
    /* Deleted by 张志勇 2004.10.25 end */
    MM_MSG_AUTHENTICATION_RSP_STRU    Msg;

    VOS_UINT32                          ulRet;

    ulRet = PS_USIM_SERVICE_NOT_AVAILIABLE;

    if ( ( WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState ) ||
        ( WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION ==
                                            g_MmGlobalInfo.ucState ) )
    {                                                                           /* 为T3230运行的状态的场合                  */
        Mm_TimerStart(MM_TIMER_T3230);                                          /* 启动T3230                                */
    }
    if ( LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState )
    {
        Mm_TimerStart(MM_TIMER_T3210);                                          /* 启动T3210                                */
    }
    if ( IMSI_DETACH_INITIATED == g_MmGlobalInfo.ucState )
    {
        Mm_TimerStart(MM_TIMER_T3220);                                          /* 启动T3220                                */
    }
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;


    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {

        /* 调用函数 Mm_SndAgentUsimUpdateFileReq 更新 KC、CKSN */
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);
    }
    else /* USIM 卡 */
    {
        /* 更新 USIM 卡 CK IK CKSN */
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);

        /* DCM MM-18-01-22 要求更新CS:4F20文件，PS更新4F52文件 */
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKC_ID);
        }
    }

    /* 向 AS 发送RRMM_NAS_INFO_CHANGE_REQ */
    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);

    /* 连续两次 RAND 相同，要起定时器保护 Res、RAND 有效性 */
    if (MM_AUTHEN_RAND_REPEAT == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
    {
        Mm_TimerStop(MM_TIMER_T3218);                                           /* 停止T3218                                */
        Mm_TimerStart(MM_TIMER_T3218);                                          /* 启动T3218                                */
    }


    /*if ( MM_AUTHEN_RES_ABSENT == g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg )*/
    /*{*/
    /*    Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* 更新SIM卡CK IK CKSN                      */
    /*    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);   */                           /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
    /*}*/
    /*else*/
    /*{*/
    /*    Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID);  */                   /* 更新SIM卡CK IK CKSN                      */
    /*    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);  */                            /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
    /*     */
    /*    Mm_TimerStop(MM_TIMER_T3218);  */                                         /* 停止T3218                                */
    /*    Mm_TimerStart(MM_TIMER_T3218);  */                                        /* 启动T3218                                */
    /*}                                                                                                                       */

    /* Modified by 张志勇 2004.10.25 begin */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[0] =   */
    /*     (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ulRes & 0x000000FF);  */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[1] =   */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 8 ) & 0x000000FF);  */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[2] =   */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 16 ) & 0x000000FF); */
    /* Msg.MmIeAuthRspPara.aucSgnfcntRES[3] = */
    /*     (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.ulRes >> 24 ) & 0x000000FF); */

    PS_MEM_SET(&Msg, 0x0, sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));

    PS_MEM_CPY(Msg.MmIeAuthRspPara.aucSgnfcntRES,
                g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);
    /* Modified by 张志勇 2004.10.25 end */
    if ( MM_CONST_NUM_0 != g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength )
    {
        Msg.ucAutnRspParaExtFlg = MM_IE_AUTN_EXT_PRESENT;
        Msg.MmIeAuthRspParaExt.ucLength =
            (VOS_UINT8)(g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength);
        /* Modified by 张志勇 2004.10.25 begin */
        /* for ( i = 0; i < 4; i ++ )   */
        /* {              */
        /*     Msg.MmIeAuthRspParaExt.aucRES[i] =   */
        /*     (VOS_UINT8)( (g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[0] >>   */
        /*                                             ( i * 8 ) ) & 0x000000FF); */
        /*     Msg.MmIeAuthRspParaExt.aucRES[i + 4] =    */
        /*    (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[1] >>   */
        /*                                            ( i * 8 ) ) & 0x000000FF);*/
        /*    Msg.MmIeAuthRspParaExt.aucRES[i + 8] =   */
        /*    (VOS_UINT8)(( g_MmGlobalInfo.AuthenCtrlInfo.aulExtRes[2] >>   */
        /*                                            ( i * 8 ) ) & 0x000000FF);*/
        /* }        */
        PS_MEM_CPY(Msg.MmIeAuthRspParaExt.aucRES,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucExtRes, 12);
        /* Modified by 张志勇 2004.10.25 end */
    }
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthenRcvUsimCnfSuccess: Return Auth Succ");
    Mm_ComMsgAuthRspSnd(&Msg);                                                  /* 发送AUTHENTICATION RESPONSE(RES)         */

}

/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnfFail
  Function: 收到USIM发来的AGENT_USIM_AUTHENTICATION_CNF(FAILURE)的处理
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1. 李  彬  2003.12.12  新版做成
      2. 张志勇  2004.10.23  AGENT接口变更对应
      3.日    期   : 2013年1月30日
        作    者   : w00176964
        修改内容   : DTS2013012906743:连续3次鉴权失败才认为鉴权失败
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnfFail()
{
    MM_MSG_AUTHENTICATION_FAIL_STRU     Msg;
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAuthFailFlg;

    ucAuthFailFlg   = VOS_FALSE;
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    Mm_TimerStop(MM_TIMER_T3230);                                               /* 停止T3230                                */
    Mm_TimerStop(MM_TIMER_T3220);                                               /* 停止T3220                                */
    Mm_TimerStop(MM_TIMER_T3210);                                               /* 停止T3210                                */
    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    if ( AGENT_AUTH_FAIL_MAC_CODE == g_AgentUsimAuthCnf.ucFailureCause )
    {                                                                           /* 失败的类型为MAC CODE FAIL的场合          */
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE;
        Mm_ComMsgAuthFailSnd(&Msg);                                             /* 发送AUTHENTICATION FAILURE               */

        /* 3GPP.24008 The MS shall deem that the network has failed the authentication check and behave
        as described in subclause 4.3.2.6.1, if any of the following occurs:
        -the timer T3216 expires;
        -the MS detects any combination of the authentication failures: "MAC failure", "invalid SQN",
        and "GSM authentication unacceptable", during three consecutive authentication challenges.
        The authentication challenges shall be considered as consecutive only, if the authentication
        challenges causing the second and third authentication failure are received by the MS, while
        the timer T3214 or T3216 started after the previous authentication failure is running. */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt ++;

        /* R6版本以后连续三次鉴权失败UE可以认为鉴权失败 */
        if ((PS_PTL_VER_R6  <= cVersion)
         && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        /* 此处实现原来参考R5协议连续两次鉴权失败UE可以认为鉴权失败 */
        if ((PS_PTL_VER_R5  >= cVersion)
         && ((MM_CONST_NUM_3   == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
          || (MM_MAC_CODE_FAIL == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if (VOS_TRUE == ucAuthFailFlg)
        {
            Mm_ComAuthMsRej();
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_MAC_CODE_FAIL;
            Mm_TimerStart(MM_TIMER_T3214);
        }
    }
    /* else */
    else if (AGENT_AUTH_FAIL_SQN == g_AgentUsimAuthCnf.ucFailureCause)
    {
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE;
        Msg.MmIeAuthFailPara.ucLength =
             g_MmGlobalInfo.AuthenCtrlInfo.ucFailParaLength;
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
        PS_MEM_CPY(Msg.MmIeAuthFailPara.aucAuthFailPara,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucFailPara, 14);
        /* Modified by 张志勇 2004.10.23 end */
        Mm_ComMsgAuthFailSnd(&Msg);                                             /* 发送AUTHENTICATION FAILURE               */
        g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt ++;

        /* R6版本以后连续三次鉴权失败UE可以认为鉴权失败 */
        if ((PS_PTL_VER_R6  <= cVersion)
         && (MM_CONST_NUM_3 == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if ((PS_PTL_VER_R5          >= cVersion)
         && ((MM_CONST_NUM_3        == g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt)
          || (MM_SQN_FAIL           == g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause)))
        {
            ucAuthFailFlg = VOS_TRUE;
        }

        if (VOS_TRUE == ucAuthFailFlg)
        {
            Mm_ComAuthMsRej();
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
        }
        else
        {
            g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_SQN_FAIL;
            Mm_TimerStart(MM_TIMER_T3216);
        }
    }
    else
    {
        /* 异常处理 */
        Msg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR;
        Mm_ComMsgAuthFailSnd(&Msg);

        MM_WARN_LOG(
                   " \nMM:UMTS AUTH RESULT IS NOT EXPECTED!\r " );

    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,
                              Msg.MmIeRejCause.ucRejCause);

}


/*******************************************************************************
  Module:   Mm_ComAuthenRcvUsimCnf
  Function: 收到USIM发来的AGENT_USIM_AUTHENTICATION_CNF的处理
  Input:    VOS_VOID*   pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.  张志勇     2005.01.27  007037 for MM
*******************************************************************************/

VOS_VOID Mm_ComAuthenRcvUsimCnf()
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);                                       /* 停止保护TIMER                            */
    /* Mm_TimerStop(MM_TIMER_PROTECT); */
    if ( AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst )
    {                                                                           /* USIM的结果是否成功                       */
        Mm_ComAuthenRcvUsimCnfSuccess();
    }
    else
    {
        Mm_ComAuthenRcvUsimCnfFail();
    }
}

/*******************************************************************************
  Module:   Mm_ComRejectCause4
  Function: 收到原因值为#4的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.12  新版做成
  2.  日    期   : 2008年09月03日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D05403,mm注册状态修改
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 201112月16日
    作    者   : l65478
    修改内容   : 问题单号：DTS2011111403722,网络模式I CS注册失败#4时,没有发起注册,导致CS业务不可用
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/

VOS_VOID Mm_ComRejectCause4()
{
    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;                  /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause4:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    MM_CKSN_INVALID
                    );
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;       /* 清除标志位                               */

    NAS_MML_InitUeIdTmsiInvalid();

    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    Mm_ComUpdateUsimFileReq();


    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_ATTEMPTING_TO_UPDATE;      /* 设置释放RR连接时候进入的状态             */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR
                             );                                                 /* 记录流程和原因值                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause4:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_ComRejectCause6
  Function: 收到原因值为#4的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.12  新版做成
  2.  日    期   : 2008年09月03日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D05403,mm注册状态修改
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_ComRejectCause6()
{
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_CM_SRV_REJ_ILLEGAL_ME);

    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRejectCause6:INFO: MmServiceState is MM_NO_IMSI");
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;       /* 清除标志位                               */

    NAS_MML_InitUeIdTmsiInvalid();

    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);

    Mm_ComUpdateUsimFileReq();

    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;                   /* 设置释放RR连接时候进入的状态             */
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME
                             );                                                 /* 记录流程和原因值                         */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRejectCause6:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/***********************************************************************
 *  MODULE   : Mm_T3240Expire
 *  FUNCTION : T3240溢出
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-11      新版作成
       2.  s46746     05-11-24      修改
 ************************************************************************/
VOS_VOID Mm_T3240Expire(
                        VOS_VOID
                    )
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3240);
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* 记录迁移之前的状态                       */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_T3240_TIMEOUT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /*Mm_SndRrAbortReq(RRC_ABORT_CS_SIGN_CONN); */                                  /* 向RRC发送RRMM_ABORT_REQ(CS域)            */

    /* if ( MM_LU_PROC != g_MmGlobalInfo.ucProc ) */
    /* {                            */                                          /* 如果不是LU流程                           */
    /*     Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* 通知MMC，CS域的业务已经停止              */
    /* } */
    Mm_TimerStart(MM_TIMER_T3240);
    return;
}

/***********************************************************************
 *  MODULE   : Mm_T3230Expire
 *  FUNCTION : T3230溢出
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇      03-12-11  新版作成

       2.日    期   : 2011年7月14日
         作    者   : zhoujun 40661
         修改内容   : 更新MML_CTX中的业务存在状态
       3.日    期   : 2012年10月29日
         作    者   : z00161729
         修改内容   : DTS2012083102536:支持cc呼叫重建
       4.日    期   :2013年9月12日
         作    者   :z00161729
         修改内容   :DTS2013082903019:支持ss重发功能
       5.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_T3230Expire(
                        VOS_VOID
                    )
 {
    VOS_UINT8   i = 0;                                                              /* 循环计数变量                             */

    Mm_TimerStop(MM_TIMER_T3230);

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ( WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF != g_MmGlobalInfo.ucState )
    {                                                                           /* 不是重建过程                             */
        switch ( g_MmGlobalInfo.ucMMConnEstingPD )
        {                                                                       /* 确定是哪个PD建立的MM连接                 */
        case MM_IE_PD_CALL_CONTROL:

            /* CC要求建立的MM连接                       */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);            /* 通知CC,MM连接建立失败                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* 清除正在建立MM连接的标志                 */
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                      /* SS要求建立的MM连接                       */
            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* 清除正在建立MM连接的标志                 */
            break;
        case MM_IE_PD_SMS_MSG:                                                  /* SMS要求建立的MM连接                      */
            Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);              /* 通知SMS,MM连接建立失败                   */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                            /* 清除正在建立MM连接的标志                 */
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_T3230Expire:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
            break;
        }
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* 设置没有正在建立的连接                   */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
        NO_MM_CONN_ESTING;                                                      /* 清除正在建立的MM连接的标志               */
    if ( ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
        && ( MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
    {                                                                           /* 没有MM连接存在                           */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* 记录要进入的状态                         */
        Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_NULL
                             );                                                 /* 记录流程和原因值                         */

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动TIMER3240                            */
    }
    else if ( WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF ==
        g_MmGlobalInfo.ucState )
    {                                                                           /* 重建过程                                 */
        for ( i = 0; i < MM_CONST_NUM_7; i++ )
        {                                                                       /* 重建的MM连接                             */
            /*lint -e701*/
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & ( 0x01 << i ) ) )
            {
                /* 该TI的MM连接失效                         */
                Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);           /* 通知CC,MM连接建立失败                    */
            }
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & ( 0x01 << i ) ) )
            {
                /* 该TI的MM连接失效                         */
                Mm_SndCcRelInd( ( i + 8 ),
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT);                          /* 通知CC,MM连接建立失败                    */
            }
            /*lint +e701*/
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;    /* 清除标志位                               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;    /* 清除标志位                               */
        Mm_ComSaveProcAndCauseVal(
                                MM_MM_CONN_PROC,
                                NAS_MML_REG_FAIL_CAUSE_NULL
                             );                                                 /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* WAIT_FOR_NETWORK_COMMAND之后进入的状态   */
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动TIMER3240                            */
    }
    else
    {                                                                           /* 不是重建并且不是建立第一条MM连接         */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /* " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                        */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_T3230Expire:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );                                     /* 检查是否有保留的需要建立的MM连接         */
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_IDLE_NORMAL_SERVICE 状态下，CC ESTREQ FLAG 为TRUE的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期   : 2010年09月02日
   作    者   : w00167002
   修改内容   : 问题单号：DTS2010090101612,重定向到G后，掉话，但是紧急呼是好的
 3.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist(VOS_UINT8   ucLUFlg)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */
    g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;       /* 设置呼叫类型                             */
    g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;  /* 设置呼叫TI                               */
    if ( MMCC_MO_NORMAL_CALL ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulCallType )
    {                                                               /* 正常呼叫                                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg = MM_FALSE;                             /* 正常呼叫                                 */
    }
    else
    {                                                               /* 紧急呼叫                                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        ucEstingCallTypeFlg = MM_TRUE;                              /* 紧急呼叫                                 */
    }
    pucCmSvcReq =
        Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );       /* 填充CM SERVICE REQUEST 消息              */
    if ( VOS_NULL_PTR == pucCmSvcReq )
    {                                                               /* 消息制作失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                     /* 返回                                     */
    }
    else
    {                                                               /* 消息制作成功                             */
        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {                                                           /* 正常呼叫                                 */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL,
                MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
        }
        else
        {                                                           /* 紧急呼叫                                 */
            Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
        }
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );             /* 释放CM SERVICE REQUEST 消息结构体        */
        if ( MM_TRUE == ucLUFlg )
        {
            /* 是LU后调用该函数                         */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                    /* 通知MMC，CS域的业务已经启动              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulTransactionId;                            /* 记录正在建立的MM连接                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;    /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* 启动保护TIMER                            */
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_IDLE_NORMAL_SERVICE 状态下，SS ESTREQ FLAG 为TRUE的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 4.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */
    if ( ( MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
        ulTransactionId )
        || ( MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
        ulTransactionId ) )
    {                                                               /* TI不合法                                 */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE,
            &CmSvcReq);                                             /* 填充CM SERVICE REQUEST结构体             */
        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq,
            &usMsgSize );                                           /* 填充CM SERVICE REQUEST 消息              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            Mm_SndRrEstReq(
                RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                MM_FALSE, usMsgSize, pucCmSvcReq );                 /* 发送消息                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );         /* 释放CM SERVICE REQUEST 消息结构体        */
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            RcvXXEstReq.ulTransactionId;                            /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD =
            MM_IE_PD_NON_CALL_RLT_SS_MSG;                           /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* 启动保护TIMER                            */

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_IDLE_NORMAL_SERVICE 状态下，SMS ESTREQ FLAG 为TRUE的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */

    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
    if ( ( MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
        ulTransactionId )
        || ( MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
        ulTransactionId ) )
    {                                                               /* TI不合法                                 */
        Mm_SndSmsRelInd( g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* 通知SMS建立失败                          */
    }
    else
    {                                                               /* TI合法                                   */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE,
            &CmSvcReq);                                             /* 填充CM SERVICE REQUEST结构体             */
        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq,
            &usMsgSize );                                           /* 填充CM SERVICE REQUEST 消息              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, ":WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            Mm_SndRrEstReq(
               RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
               MM_FALSE,
               usMsgSize, pucCmSvcReq );                            /* 发送消息                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );          /* 释放CM SERVICE REQUEST 消息结构体        */
        }
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            RcvXXEstReq.ulTransactionId;                            /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                 /* 启动保护TIMER                            */

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_IDLE_NORMAL_SERVICE 状态处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   : 2012年09月01日
   作    者   : s46746
   修改内容   : DTS2012090405619:DCM外场测试,联合RAU过程中响应寻呼被网络abort
 4.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 5.日    期   : 2013年9月12日
   作    者   : w00242748
   修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                G下原小区时做LAU
 6.日    期   : 2015年3月20日
   作    者   : w00167002
   修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                进行封装。
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(VOS_UINT8   ucLUFlg)
{
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* 有等待的CC触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_CC_EST_Exist(ucLUFlg);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SS_EST_Exist();
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE_SMS_EST_Exist();
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* 没有等待的CC要求建立的MM连接             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_IDLE_ATTEMPTING_TO_UPDATE 状态处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 4.日    期   : 2013年07月05日
   作    者   : l65478
   修改内容   : DTS2013070408274:MM进入NORMAL SERVICE后没有处理缓冲的CC消息
 5.日    期   : 2013年9月12日
   作    者   : w00242748
   修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                G下原小区时做LAU
  6.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
  8.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE(VOS_UINT8   ucLUFlg)
{
    MM_MSG_CM_SVC_REQ_STRU   CmSvcReq;                                              /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16               usMsgSize = 0;                                         /* 消息长度,以字节为单位                    */
    VOS_UINT8               *pucCmSvcReq = 0;                                       /* 要发送的CM SERVICE REQ消息指针           */

    RRMM_PAGING_IND_STRU     stWPagingMsg;
    GRRMM_PAGING_IND_ST      stGPagingMsg;

    if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* 由等待的CC触发的需要建立的MM连接         */
        if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulCallType )
        {                                                               /* 是紧急呼叫                               */
            g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;   /* 设置呼叫类型                             */
            g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
                ulTransactionId;                                        /* 设置呼叫TI                               */
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* 记录收到建立请求时的状态                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_TRUE;                              /* 紧急呼叫                                 */
            pucCmSvcReq =
                Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );   /* 填充CM SERVICE REQUEST 消息              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                           /* 消息制作失败                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                 /* 返回                                     */
            }
            else
            {                                                           /* 消息制作成功                             */
                if ( MM_TRUE == ucLUFlg )
                {                                                       /* 是LU后调用该函数                         */
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                /* 通知MMC，CS域的业务已经启动              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
                }
                Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                    usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);             /* 启动保护TIMER                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucMMConnEstingTI =
                    (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulTransactionId;                        /* 记录正在建立的MM连接                     */
                g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;/* 记录正在建立的MM连接的PD                 */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;   /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            }
        }
        else
        {
            /* 是正常呼叫                               */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);                      /* 通知CC指定建立的MM连接建立失败           */

            if ( MM_FALSE == ucLUFlg )
            {
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                /* 通知MMC，CS域的业务已经停止              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE);                        /* 通知SMS建立失败                          */
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* 没有等待的CC要求建立的MM连接             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3213].ucTimerStatus))
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_CONNECTION_ACTIVE CC EST FLAG为 TRUE的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     4.日    期   : 2014年5月28日
       作    者   : z00234330
       修改内容   : covertity修改
     5.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(&CmSvcReq, 0x00, sizeof(CmSvcReq));
    /* modified by z00234330 for coverity修改 2014-05-28 end */

    g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;       /* 设置呼叫类型                             */
    g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
        ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;  /* 设置呼叫TI                               */
    /*lint -e701*/
    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        aucMMConnExtFlg[1] & ( 0x01 <<
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId - 8 ) ) ) )
        )
    {
        /* 要求建立的MM连接已经存在或受限服务状态   */
        Mm_SndCcRelInd( g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* 通知CC指定建立的MM连接建立失败           */
    }
    /*lint +e701*/
    else
    {                                                               /* 要求建立的MM连接不存在                   */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
                                                                    /* 记录收到建立请求时的状态                 */
        if ( MMCC_MO_NORMAL_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulCallType )
        {                                                           /* 主叫正常呼叫                             */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                MM_FALSE, &CmSvcReq);                               /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_FALSE;                         /* 正常呼叫                                 */
        }
        else if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulCallType )
        {                                                           /* 主叫紧急呼叫                             */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                               /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg = MM_TRUE;                      /* 紧急呼叫                                 */
        }
        else
        {
        }
        Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                            /* 向网侧发送建立MM连接的请求               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI = (VOS_UINT8)g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq
            .ulTransactionId;                                       /* 记录正在建立的MM连接                     */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;    /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_T3230);                              /* 启动TIMER3230                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_CONNECTION_ACTIVE SS EST FLAG为 TRUE的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     3.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */

    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||(8 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId)
        ||(14 < g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId)
        )
    {
        /* TI不合法或受限服务状态   */

        /* 通知SS指定建立的MM连接建立失败           */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    /*lint -e701*/
    else if (MM_CONST_NUM_0 !=
            ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
              &( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId - 8 ) ) ))
    /*lint +e701*/
    {
        /* 要求建立的MM连接已经存在                 */

        /* 记录收到建立请求时的状态                 */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
        /* 该MM连接建立成功                         */
        Mm_SndSsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId,MMSS_EST_SUCCESS);
    }
    else
    {
        /* 填充CM SERVICE REQUEST结构体             */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);
        /* 向网侧发送建立MM连接的请求               */
        Mm_ComMsgCmSvcReqSnd( &CmSvcReq );
        /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                    .RcvXXEstReq.ulTransactionId);
        /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;
        /* 启动TIMER3230                            */
        Mm_TimerStart(MM_TIMER_T3230);
        /* 记录迁移之前的状态                       */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* 状态迁移                                 */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_CONNECTION_ACTIVE SMS EST FLAG为 TRUE的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
    2.日    期   :2013年9月12日
      作    者   :z00161729
      修改内容   :DTS2013082903019:支持ss重发功能
    3.日    期   :2014年9月24日
      作    者   :s00217060
      修改内容   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */

    if ( ( MM_TRUE == Mm_ComJudgeLimitSvc( ) )
        ||(8 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId)
        ||(14 < g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId)
        )
    {
        /* TI不合法或受限服务状态   */

        /* 通知SMS指定建立的MM连接建立失败           */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
    }
    /*lint -e701*/
    else if (MM_CONST_NUM_0 !=
            ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
              &( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId - 8 ) ) ))
    /*lint +e701*/
    {
        /* 要求建立的MM连接已经存在                 */

        /* 记录收到建立请求时的状态                 */
        /* ==>A32D12640 */
        /*
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;
        */
        /* 该MM连接建立成功                         */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId);
    }
    else
    {
        /* 填充CM SERVICE REQUEST结构体             */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);
        /* 向网侧发送建立MM连接的请求               */
        Mm_ComMsgCmSvcReqSnd( &CmSvcReq );
        /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                    .RcvXXEstReq.ulTransactionId);
        /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;
        /* 启动TIMER3230                            */
        Mm_TimerStart(MM_TIMER_T3230);
        /* 记录迁移之前的状态                       */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* 状态迁移                                 */
        Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度: MM_CONNECTION_ACTIVE 状态处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE(VOS_VOID)
{
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                   /* 有等待的CC触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_CC_EST_Exist();
    }
    else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        /* 有等待的SS触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SS_EST_Exist();
    }
    else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        /* 有等待的SMS触发的需要建立的MM连接         */
        Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE_SMS_EST_Exist();
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 函 数 名  : Mm_ComCheckDelayMmConn_OtherStateHandling_CC
 功能描述  : 由等待的CC触发的需要建立的MM连接
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_CC(
    VOS_UINT8                           ucLUFlg
)
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                                  /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* 要发送的CM SERVICE REQ消息指针           */

    if ( MMCC_EMERGENCY_CALL ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
        RcvXXEstReq.ulCallType )
    {                                                               /* 是紧急呼叫                               */
        g_MmCcEstReq.ulCallType           = g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;   /* 设置呼叫类型                             */
        g_MmCcEstReq.ulTransactionId      = g_MmGlobalInfo.
            ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
            ulTransactionId;                                        /* 设置呼叫TI                               */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* 记录收到建立请求时的状态                 */
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
            MM_FALSE, &CmSvcReq);                                   /* 填充CM SERVICE REQUEST结构体             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucEstingCallTypeFlg = MM_TRUE;                          /* 紧急呼叫                                 */
        pucCmSvcReq =
            Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize );   /* 填充CM SERVICE REQUEST 消息              */
        if ( VOS_NULL_PTR == pucCmSvcReq )
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            if ( MM_TRUE == ucLUFlg )
            {                                                       /* 是LU后调用该函数                         */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                /* 通知MMC，CS域的业务已经启动              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            }
            Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL, MM_FALSE,
                usMsgSize, pucCmSvcReq );                           /* 发送消息                                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);             /* 启动保护TIMER                            */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI =
                (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId;                        /* 记录正在建立的MM连接                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;/* 记录正在建立的MM连接的PD                 */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;   /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComCheckDelayMmConn:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
    }
    else
    {
        if ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
        {
            /* 是正常呼叫                               */
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                      /* 通知CC指定建立的MM连接建立失败           */
        }
        else if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
              && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
        {
            /* 不是由于被拒原因值12引起的限制服务状态可以尝试呼叫重发*/
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
        }
        else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
        }
        else
        {
            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                      NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                      /* 通知CC指定建立的MM连接建立失败           */
        }

        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
    }
}

/*****************************************************************************
 函 数 名  : Mm_ComCheckDelayMmConn_OtherStateHandling_SS
 功能描述  : 由等待的SS触发的需要建立的MM连接
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_SS(VOS_VOID)
{
    if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
          && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
    {
        /* 不是由于被拒原因值12引起的限制服务状态可以尝试ss重发 */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }
    else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
    }

}

/*****************************************************************************
 函 数 名  : Mm_ComCheckDelayMmConn_OtherStateHandling_SMS
 功能描述  : 由等待的SS触发的需要建立的MM连接
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_OtherStateHandling_SMS(VOS_VOID)
{
    if ((MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState)
          && (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW != g_MmGlobalInfo.usCauseVal))
    {
        /* 不是由于被拒原因值12引起的限制服务状态可以尝试ss重发 */
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }
    else if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
    }
    else
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
    }

}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn_Other_State_Handling
 *  FUNCTION : Mm_ComCheckDelayMmConn函数降复杂度:
                      MM_IDLE_LIMITED_SERVICE,
                      MM_IDLE_LOCATION_UPDATE_NEEDED,
                      MM_IDLE_NO_IMSI状态处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   : 2012年09月01日
   作    者   : s46746
   修改内容  : DTS2012090405619:DCM外场测试,联合RAU过程中响应寻呼被网络abort
 4.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 5.日    期   :2013年9月14日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 6.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayMmConn_Other_State_Handling(VOS_UINT8   ucLUFlg)
{
    RRMM_PAGING_IND_STRU        stWPagingMsg;
    GRRMM_PAGING_IND_ST         stGPagingMsg;

    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_CC(ucLUFlg);
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_SS();
    }
    else if ( MM_TRUE ==
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        Mm_ComCheckDelayMmConn_OtherStateHandling_SMS();
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            Mm_MakeGPagingInd(&stGPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
            /*lint +e961*/
        }
        else
        {
            Mm_MakeWPagingInd(&stWPagingMsg);
            /*lint -e961*/
            gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
            /*lint +e961*/
        }
    }
    else
    {                                                                   /* 没有等待的CC要求建立的MM连接             */
        if ( MM_FALSE == ucLUFlg )
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayMmConn
 *  FUNCTION : 在进入稳态时检查是否有保留的需要建立的MM连接
 *  INPUT    : VOS_UINT8   ucLUFlg          是否是LU结束后调用的该函数
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇        03-12-11    新版作成
 *     2.  x51137        07-03-10    A32D09201
       3.日    期   : 2007年04月13日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D10663
       4.日    期   : 2007年07月31日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D12640
       5.日    期   : 2008年8月13日
         作    者   : l0010747
         修改内容   : 问题单号:AT2D04996/AT2D05037
       3.日    期   : 2012年3月07日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
       4.日    期   : 2012年09月01日
         作    者   : s46746
         修改内容  : DTS2012090405619:DCM外场测试,联合RAU过程中响应寻呼被网络abort
       5.日    期   : 2012年10月29日
         作    者   : z00161729
         修改内容   : DTS2012083102536:支持cc呼叫重建
       6.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
       7.日    期   :2014年9月24日
         作    者   :s00217060
         修改内容   :for cs_err_log
 ************************************************************************/

VOS_VOID Mm_ComCheckDelayMmConn(
                            VOS_UINT8   ucLUFlg                                     /* 是否是LU结束后调用的该函数               */
                    )
{
    if ( ((MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId ) ||(MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.
        ulTransactionId )) && (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg) )
    {
        /* TI不合法                                 */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);        /* 通知CC建立失败                           */
    }
    else
    {                                                                           /* TI合法                                   */
        switch ( g_MmGlobalInfo.ucState )
        {                                                                       /* 当前状态                                 */
        case MM_IDLE_NORMAL_SERVICE:
            Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(ucLUFlg);
            break;
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
            Mm_ComCheckDelayMmConn_MM_IDLE_ATTEMPTING_TO_UPDATE(ucLUFlg);
            break;
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_NO_IMSI:
            Mm_ComCheckDelayMmConn_Other_State_Handling(ucLUFlg);
            break;
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
            if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
            {
                Mm_ComCheckDelayMmConn_MM_IDLE_NORMAL_SERVICE(ucLUFlg);
            }
            else
            {
                Mm_ComCheckDelayMmConn_Other_State_Handling(ucLUFlg);
            }
            break;
        case MM_CONNECTION_ACTIVE:
            Mm_ComCheckDelayMmConn_MM_CONNECTION_ACTIVE();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComCheckDelayMmConn:WARNING: g_MmGlobalInfo.ucState Abnormal");
            break;
        }
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    return;
}
/***********************************************************************
 *  MODULE   : Mm_ComRrConnRelChk
 *  FUNCTION : 判断是否需要通知MMC信令连接释放
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇        2005.01.31    新版作成
       2.日    期   : 2013年2月4日
         作    者   : w00176964
         修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 ************************************************************************/
VOS_UINT8 Mm_ComRrConnRelChk()
{
    if ( ( ( MM_MM_CONN_PROC != g_MmGlobalInfo.ucProc ) ||
        ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR !=
        g_MmGlobalInfo.usCauseVal ) )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ))
    {                                                                           /* 原因值不是4或者流程不是MM连接没有缓存    */
        return MM_TRUE;
    }
    else
    {
        if (( MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc ) &&
        ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR ==  g_MmGlobalInfo.usCauseVal )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        && (  MM_FALSE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ))
        {                                                                       /* 没有缓存                                 */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
            if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
            {                                                                   /* 判断是否为A+I模式                        */
                return MM_TRUE;
            }
        }
    }
    return MM_FALSE;
}
/***********************************************************************
 *  MODULE   : Mm_ComTiChk
 *  FUNCTION : TI的合法性检查
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇     2005.01.31  新版作成
       2.  张志勇  2005.03.09  MM_Review_HW_BUG_027对应
 ************************************************************************/
VOS_UINT8 Mm_ComTiChk()
{
    if ( ((MM_CONST_NUM_8 >
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                RcvXXEstReq.ulTransactionId )
        ||(MM_CONST_NUM_14 <
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                RcvXXEstReq.ulTransactionId ))
        && (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg) )
    {                                                                           /* TI不合法                                 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                                                                    = MM_FALSE;

        NAS_MM_UpdateCsServiceBufferStatusFlg();
        return MM_FALSE;
    }
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                    .RcvXXEstReq.ucFlg )
    {
        if ( ( MM_CONST_NUM_8 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
            ulTransactionId )
            || ( MM_CONST_NUM_14 <
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
            ulTransactionId ) )
        {                                                                       /* TI不合法                                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                      .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_UpdateCsServiceBufferStatusFlg();
            return MM_FALSE;
        }
    }
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                    .RcvXXEstReq.ucFlg )
    {
        if ( ( MM_CONST_NUM_8 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId )
            || ( MM_CONST_NUM_14 <
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
            ulTransactionId ) )
        {                                                                       /* TI不合法                                 */
            /*return MM_FALSE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                       .RcvXXEstReq.ucFlg = MM_FALSE; */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_UpdateCsServiceBufferStatusFlg();
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}
/***********************************************************************
 *  MODULE   : Mm_ComSigRelForDelayMmConnRej
 *  FUNCTION : MM拒绝上层请求后通知MMC信令连接释放
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇        2005.01.31    新版作成
       2.  日    期   :  2007年10月06日
           作    者   :  l65478
           修改内容   :  问题单号：A32D12977
************************************************************************/
VOS_VOID Mm_ComSigRelForDelayMmConnRej()
{
    switch ( g_MmGlobalInfo.ucState )
    {                                                                           /* 当前状态                                 */
    case MM_IDLE_NORMAL_SERVICE:
        break;
    case MM_CONNECTION_ACTIVE:
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
    case MM_IDLE_LIMITED_SERVICE:
    case MM_IDLE_LOCATION_UPDATE_NEEDED:
    case MM_IDLE_NO_IMSI:
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                                       /* 由等待的CC触发的需要建立的MM连接         */
            if ( MMCC_EMERGENCY_CALL ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType )
            {                                                                   /* 是紧急呼叫                               */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {                                                                   /* 是正常呼叫                               */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }
        else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {

        }
        break;
    default:
        break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_FillMobileID
 功能描述  : 根据MM的全局变量取值，填充MobileID的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_FillMobileID(
    MM_MOBILE_ID_STRU                  *pstMobileID
)
{
    VOS_UINT8                          *pucIMSI;

    pstMobileID->ucMsIdFlg = g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg;

    PS_MEM_CPY(pstMobileID->aucImei,
               g_MmGlobalInfo.MsCsInfo.MobileId.aucImei,
               sizeof(pstMobileID->aucImei));

    PS_MEM_CPY(pstMobileID->aucImeisv,
               g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv,
               sizeof(pstMobileID->aucImeisv));

    PS_MEM_CPY(pstMobileID->aucTmsi,
               NAS_MML_GetUeIdTmsi(),
               sizeof(pstMobileID->aucTmsi));

    pucIMSI = NAS_MML_GetSimImsi();

    pstMobileID->Imsi.ucLength = pucIMSI[0];

    PS_MEM_CPY(pstMobileID->Imsi.aucImsi,
               pucIMSI + 1,
               sizeof(pstMobileID->Imsi.aucImsi));


    return;
}

/*******************************************************************************
  Module:   Mm_ComLuOnly
  Function: A+II模式或者B模式的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.16  新版做成
  2.  张志勇     2005.01.27  007037 for MM
  3.日    期   : 2006年11月6日
    作    者   : s46746
    修改内容   : 问题单号:A32D06442
  4.日    期   : 2007年05月11日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D10713
  5.日    期   : 2007年12月15日
    作    者   : l00107747
    修改内容   : 问题单号:A32D13897
  6.日    期   : 2007年12月21日
    作    者   : l00107747
    修改内容   : 问题单号:A32D13951
  7.日    期   : 2008年09月03日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403,mm注册状态修改
  8.日    期   : 2008年11月22日
    作    者   : l65478
    修改内容   : 问题单号：AT2D06900,mm注册状态修改
  9.日    期   : 2009年05月11日
    作    者   : h44270
    修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
  10.日    期   : 2011年07月14日
     作    者   : z00161729
     修改内容   : V7R1 phase II全局变量调整修改
  11.日    期   : 2011年7月22日
     作    者   : h44270
     修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  12.日    期   : 2011年7月25日
     作    者   : h44270
     修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  13.日    期   : 2011年7月26日
     作    者   : l00130025
     修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
  14.日    期   : 2011年04月23日
     作    者   : f00179208
     修改内容   : 问题单号：DTS2011032903294,[出服务区】【非闪电卡】出服务区再回原小区，UE只是重启了T3212，但是没有发起LAU
  15.日    期   : 2011年12月17日
     作    者   : w00166186
     修改内容   : dts2011120603107，从一个正常服务小区重选到一个不支持GPRS的小区，不停发起LAU
  16.日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
  17.日    期   : 2012年2月15日
     作    者   : w00167002
     修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR:调整，存在CSFB的paging时，做LAU，也需要
                   携带FOLLOW ON 标志。
                   TS24008 4.5.1.3.4 Paging response for CS fallback
                   NOTE: For the race condition when the mobile station has a CM
                   application request pending, the mobile station also indicates
                   that it has a follow-on request pending.
  18.日    期   : 2012年9月24日
     作    者   : s46746
     修改内容   : 问题单号DTS2012090801459，进行位置更新时停止T3212
  19.日    期   : 2012年10月29日
     作    者   : z00161729
     修改内容   : DTS2012083102536:支持cc呼叫重建
  20.日    期   : 2012年12月22日
     作    者   : l65478
     修改内容   : DTS2012122103936 发起紧急呼叫时MM状态迁移错误
  21.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  22.日    期   : 2013年7月25日
     作    者   : w00242748
     修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                  网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                  rau req中带follow on标志,无明确协议依据
  23.日    期   : 2013年9月12日
     作    者   : z00161729
     修改内容   : DTS2013082903019:支持ss重发功能
  24.日    期   : 2014年4月2日
     作    者   : w00176964
     修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  25.日    期   : 2014年5月21日
     作    者   : w00167002
     修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                MM删除对SOR的特殊处理。
  26.日    期   : 2014年6月4日
     作    者   : w00167002
     修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
  27.日    期   : 2014年6月13日
     作    者   : w00242748
     修改内容   : DSDS 新特性
  28.日    期   :2014年9月24日
     作    者   :s00217060
     修改内容   :for cs_err_log
  29.日    期   : 2014年11月26日
     作    者   : w00167002
     修改内容   : DTS2014092806342:在L下被叫CSFB到GSM后，建联失败，后重选到新的位置区
                  发起LAU时候，没有携带CSMT标志，在华为网络上，网络会下发SETUP，被叫
                  成功；在非华为网络上，网络未下发SETUP。修改为携带CSMT标志。
  30.日    期   : 2015年1月26日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
  31.日    期   : 2015年6月30日
     作    者   : z00161729
     修改内容   : 24008 23122 R11 CR升级项目修改
  32.日    期   : 2015年8月13日
     作    者   : l00289540
     修改内容   : User_Exp_Improve修改
  33.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
*******************************************************************************/

VOS_VOID Mm_ComLuOnly()
{
    MM_MSG_LU_REQ_STRU     Msg;

    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    VOS_UINT32                          ulCsLastSucLac;

    VOS_UINT32                          ulUsimDoneGsmCsAuthFlg;

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo   = NAS_MML_GetRplmnCfg();

    ulCsLastSucLac = NAS_MML_GetCsLastSuccLac();
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstMsCapability = NAS_MML_GetMsCapability();
    ucSimType       = NAS_MML_GetSimType();

    ulUsimDoneGsmCsAuthFlg              = NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth();


    /* 发起LAU前清除重试标志位 */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        return;
    }
    if ( VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        if (VOS_TRUE == NAS_MM_IsNeedDeactiveIsrLauInit())
        {
            /* 去激活ISR,更新TIN值为P-TMSI */
            NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
            NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
        }

        Mm_TimerStop(MM_TIMER_T3211);
        Mm_TimerStop(MM_TIMER_T3213);

        /* 4.4.4.1 Location updating initiation by the mobile station
           Any timer used for triggering the location updating procedure
           (e.g. T3211, T3212) is stopped if running. */
        Mm_TimerStop(MM_TIMER_T3212);



        Msg.MmIeLuType.ucLUT =
            g_MmGlobalInfo.LuInfo.ucLuType & MM_IE_LU_TYPE_LUT_MASK;            /* 设置LU TYPE                              */
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                                       /* 有保留的MM连接                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI合法                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* 设置FOR                                  */
            }
            else
            {
                /* TI不合法, 通知CC建立失败 */
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg =
                    MM_FALSE;                                                   /* 设置没有缓存的MM连接                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* 设置FOR                                  */
            }
        }
        else if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
        {                                                                       /* 有保留的MM连接                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI合法                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* 设置FOR                                  */
            }
            else
            {                                                                   /* TI不合法                                 */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg =
                    MM_FALSE;                                                   /* 设置没有缓存的MM连接                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* 设置FOR                                  */
            }
        }
        else if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
        {                                                                       /* 有保留的MM连接                           */
            if ( ( MM_CONST_NUM_7 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) ||
                ( ( MM_CONST_NUM_7 < g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) &&
                ( MM_CONST_NUM_15 > g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId ) ) )
            {                                                                   /* TI合法                                   */
                Msg.MmIeLuType.ucFOR = MM_IE_LU_TYPE_FOR_MASK;                          /* 设置FOR                                  */
            }
            else
            {                                                                   /* TI不合法                                 */
                Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                            /* 通知CC建立失败                           */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                    ucFlg = MM_FALSE;                                           /* 设置没有缓存的MM连接                     */
                Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                          /* 设置FOR                                  */
            }
        }
        else
        {                                                                       /* 没有保留的MM连接                         */
            Msg.MmIeLuType.ucFOR = MM_CONST_NUM_0;                              /* 设置FOR                                  */
        }

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        /* SIM卡在W下进行CS 注册时，如果当前LAI无效，将CKSN也置为无效 */
        if ( ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
           && (NAS_MML_SIM_TYPE_SIM       == ucSimType)
           && ((MM_INVALID_LAI            == ulCsLastSucLac)
            || (0x0                       == ulCsLastSucLac)))
          || (VOS_TRUE                    == ulUsimDoneGsmCsAuthFlg) )
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);

            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        Msg.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();             /* 设置CKSN                                 */
        Msg.MmIeLAI.IeLai.PlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
        Msg.MmIeLAI.IeLai.PlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
        Msg.MmIeLAI.IeLai.ulLac        = NAS_MML_GetCsLastSuccLac();
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

        if ( MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0] )
        {
            Msg.ucMsClsMskFrUMTSFlg = MM_TRUE;                                  /* 设置ClassMark For UMTS存在               */
            MM_Fill_IE_ClassMark2(Msg.MmIeMsClsMskFrUMTS.aucClassmark2);
        }
        else
        {
            Msg.ucMsClsMskFrUMTSFlg = MM_FALSE;                                 /* 设置ClassMark For UMTS不存在             */
        }


        /* 发起LAU时候清除ATTEMPT UPDATE LAI信息 */
        NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

        g_MmMsgLuRjct.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_NULL;

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;

        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING);

        Mm_ComMsgLuReqSndOfEstReq(&Msg);                                        /* 发送消息                                 */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuOnly:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

        NAS_EventReport(WUEPS_PID_MM,NAS_OM_EVENT_LOCATION_UPDATE_REQ,
                        &g_MmGlobalInfo.LuInfo.ucLuType,NAS_OM_EVENT_LAU_REQ_LEN);
    }
}

/*******************************************************************************
  Module:   Mm_ComInit
  Function: MM 初始化
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇      2003.12.23   新版作成
  2.  张志勇        2005.01.27  007037 for MM
  3.  s46746     2005.09.05   for HSS4100 V200R001
  4.  h44270     2009.01.22   问题单号：AT2D08559
  5.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
  7.日    期   : 2012年2月14日
    作    者   : z00161729
    修改内容   : V7R1C50 支持CSFB特性修改
  7.日    期   : 2012年05月21日
    作    者   :  z40661
    修改内容  :  DTS2012052308001:从L重选到G后反复进行LAU
  8.日    期   : 2012年9月07日
    作    者   : l00171473
    修改内容   : DTS2012081701006, 添加MM关机保护定时器
  9.日    期   : 2012年09月21日
    作    者   : z00161729
    修改内容  : DTS2012090706407 :法电lau accept中携带与系统消息中不同的non broadcast lai时需要出发lau
 10.日    期   : 2012年10月22日
    作    者   : t00212959
    修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
 11.日    期   : 2012年12月22日
    作    者   : l65478
    修改内容   : DTS2012122103936 发起紧急呼叫时MM状态迁移错误
 12.日    期   : 2013年05月21日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

 13.日    期   : 2013年7月4日
    作    者   : w00167002
    修改内容   : SVLTE BBIT，CS detach保护定时器设置为非循环定时器

 14.日    期   : 2013年9月4日
    作    者   : w00167002
    修改内容   : DTS2013090403562:NAS定时器清理，需要启动32K定时器。将MM/MMA/SMS
                 模块的循环定时器修改为非循环定时器。
 15.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                rau req中带follow on标志,无明确协议依据
 16.日    期   : 2013年11月01日
    作    者   : l65478
    修改内容   : DTS2013103107433:紧急呼叫CSFB HO到GU在收到系统信息前先发起了业务
 17.日    期   : 2013年9月25日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseII 项目修改:增加SRVCC过程标记初始化
 18.日    期   : 2014年4月175日
    作    者   : s00246516
    修改内容   : DTS2014041700472:使用2G SIM卡，PAD形态上出现鉴权被网络拒绝
 19.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
  20.日    期   : 2014年8月14日
     作    者   : z00161729
     修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
  21.日    期   : 2015年5月5日
    作    者   : w00167002
    修改内容   : csmt修改
  22.日    期   : 2015年6月15日
     作    者   : z00161729
     修改内容   : 24008 23122 R11 CR升级项目修改
  23.日    期   : 2015年8月13日
     作    者   : l00289540
     修改内容   : User_Exp_Improve修改
*******************************************************************************/
VOS_VOID Mm_ComInit ()
{

    VOS_UINT8                           i;
    VOS_UINT32                          ulHoWaitSysinfoTimeLen;
    ulHoWaitSysinfoTimeLen = NAS_MML_GetHoWaitSysinfoTimerLen();

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    PS_MEM_SET( &gstMmTimer[0], 0, ( MM_TIMER_MAX * sizeof( MM_TIMER_STRU ) ) );/* 初始化                                   */
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

    PS_MEM_SET( &g_MmGlobalInfo, 0, sizeof( MM_GLOBAL_CTRL_STRU ) );           /* 初始化                                   */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    PS_MEM_SET(&gstMmSuspendMsgQue, 0, sizeof(MM_SUSPEND_MSG_BUF_ST));        /* 初始化                                   */
    PS_MEM_SET(&gstMmTimerSuspend, 0, sizeof(MM_TIMER_ST));                   /* 初始化                                   */

    g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = 0;

    gstMmTimerSuspend.ulTimerLength     = MM_TIMER_PROTECT_SUSPEND_VALUE;

    PS_MEM_SET(&g_MmMsgLuAccpt, 0, sizeof(MM_MSG_LU_ACCPT_STRU));
    PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

    PS_MEM_SET(&g_AgentUsimAuthCnf, 0, sizeof(MM_USIM_AUTHENTICATION_CNF_STRU));

    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

    g_MmGlobalInfo.ucSysInfoFlg =  MM_FALSE;

    g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;

    g_MmGlobalInfo.ucFollowOnFlg         = MM_NO_FOLLOW_ON;
    g_MmGlobalInfo.ucCsSigConnFlg        = MM_CS_SIG_CONN_ABSENT;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComInit:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_ABSENT");
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg = MM_AUTHEN_RAND_ABSENT;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI   =
        NO_MM_CONN_ESTING;                                                      /* 没有正在建立的MM连接                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg  =
        MM_FALSE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI   =
        NO_MM_CONN_ESTING;                                                      /* 没有正在建立的MM连接                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg  =
        MM_FALSE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI  =
        NO_MM_CONN_ESTING;                                                      /* 没有正在建立的MM连接                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg =
        MM_FALSE;
    g_MmGlobalInfo.ucMMConnEstingPD                                 =
        NO_MM_CONN_ESTING;

    g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc = MM_WasRrEstReq;
    g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc = As_RrRelReq;
    g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc = MM_WasRrDataReq;

    g_NasMmImportFunc.ucFuncEnvironment             = NAS_MML_NET_RAT_TYPE_WCDMA;
    g_stMmNsd.ucNsdMod = MM_NSD_MOD_R99_ONWARDS;

    g_MmGlobalInfo.ucLikeB = MM_FALSE;
    g_MmGlobalInfo.ucAttDelay = MM_FALSE;

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    g_MmGlobalInfo.ucCsCipherAlgor = NAS_MM_CIPHER_ALGO_NOPRESENT;
    g_MmSubLyrShare.MmShare.ucCsSpecificFlg = MM_SPECIFIC_OFF;

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
    {
        gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;

        /* 将定时器修改为非循环定时器 */
        gstMmTimer[i].ucMode        = VOS_RELTIMER_NOLOOP;
    }

    /* 初始化TIMER的时长 */
    gstMmTimer[MM_TIMER_T3210].ulTimerLen = MM_TIMER_T3210_VALUE;
    gstMmTimer[MM_TIMER_T3211].ulTimerLen = MM_TIMER_T3211_VALUE;
    gstMmTimer[MM_TIMER_T3213].ulTimerLen = MM_TIMER_T3213_VALUE;
    gstMmTimer[MM_TIMER_T3214].ulTimerLen = MM_TIMER_T3214_VALUE;
    gstMmTimer[MM_TIMER_T3216].ulTimerLen = MM_TIMER_T3216_VALUE;
    gstMmTimer[MM_TIMER_T3218].ulTimerLen = MM_TIMER_T3218_VALUE;
    gstMmTimer[MM_TIMER_T3220].ulTimerLen = MM_TIMER_T3220_VALUE;

    gstMmTimer[MM_TIMER_T3230].ulTimerLen = MM_TIMER_T3230_VALUE;

    gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_AGENT].ulTimerLen =
                                    MM_TIMER_PROTECT_AGENT_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_DETACH].ulTimerLen =
                                    MM_TIMER_PROTECT_DETACH_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen
                                     = MM_TIMER_PROTECT_W_SIGNALLING_VALUE;

    gstMmTimer[MM_TIMER_PROTECT_CC].ulTimerLen = MM_TIMER_PROTECT_CC_VALUE;
    gstMmTimer[MM_TIMER_PROTECT_CCBS].ulTimerLen = MM_TIMER_PROTECT_CCBS_VALUE;
    gstMmTimer[MM_TIMER_DELAY_LU_GSM].ulTimerLen = MM_TIMER_DELAY_LU_GSM_VALUE;
    gstMmTimer[MM_TIMER_DELAY_CS_SERVICE_GSM].ulTimerLen = MM_TIMER_DELAY_CS_SERVICE_GSM_VALUE;

    gstMmTimer[MM_TIMER_WAIT_CONNECT_REL].ulTimerLen = MM_TIMER_WAIT_CONNECT_REL_VALUE;

    gstMmTimer[MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;

    gstMmTimer[MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;

    gstMmTimer[MM_TIMER_CS_HO_WAIT_SYSINFO].ulTimerLen = ulHoWaitSysinfoTimeLen;


    gstMmTimer[MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT].ulTimerLen = NAS_MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT_LEN_VALUE;

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, begin */
    gstMmTimer[MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerLen = MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_LEN_VALUE;
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-11, end */

    gstMmTimer[MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE].ulTimerLen = (VOS_UINT32)(NAS_MML_GetProtectMtCsfbPagingProcedureLen() * 1000);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    gstMmTimer[MM_TIMER_T3242].ulTimerLen = MM_TIMER_T3242_VALUE;
    gstMmTimer[MM_TIMER_T3243].ulTimerLen = MM_TIMER_T3243_VALUE;
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;


    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat              = MM_AUTHEN_RAND_DIFFER;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType            = MM_CONST_NUM_2;

    g_T3211Flag = 0;
    g_MmGlobalInfo.ucMmServiceState = MMC_MM_NO_SERVICE;

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect        = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;


    g_MmSubLyrShare.MmShare.MmSuspendEvent              = MM_EVENT_ID_INVALID;


    /* 初始化为无延迟的LAU标志 */
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    g_MmGlobalInfo.enPreRatType                         = NAS_MML_NET_RAT_TYPE_BUTT;

    g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg  = VOS_FALSE;

    NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
    NAS_MM_SetSrvccFlg(VOS_FALSE);

    NAS_MM_SetRcvSrvccCallInfoFlg(VOS_FALSE);
#endif
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

    NAS_MML_InitOldCampLai(NAS_MM_GetAllocT3212ValueLaiInfo());
    NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BUTT);

    NAS_MM_InitT3212Counter();

    g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246    = VOS_FALSE;

    return;                                                                     /* 返回                                     */
}


VOS_VOID    Mm_Nop(VOS_VOID* pMsg)
{
}

/***********************************************************************
 *  MODULE   : Mm_ComStart
 *  FUNCTION : 收到MMCMM_START_REQ的公共处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.张志勇      04-02-06  新版作成
       2.日    期   : 2008年12月22日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D07757,MM丢网后重回原小区，不发起LU
       3.日    期   : 2010年9月30日
         作    者   : 欧阳飞 00132663
         修改内容   : 根据问题单号DTS2010092902368,TMSI只在等效PLMN内有效

       4.日    期   : 2011年7月13日
         作    者   : zhoujun 40661
         修改内容   : SIM卡内容更新到MML中
       5.日    期   : 2012年2月22日
         作    者   : w00199382
         修改内容   : B060项目移植防卡贴
       6.日    期   : 2014年4月2日
         作    者   : w00176964
         修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
************************************************************************/
VOS_VOID Mm_ComStart(
                 VOS_VOID
                 )
{

    VOS_UINT8                           i;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    VOS_UINT8                           ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsi;

    /*根据卡状态信息，更新CS的Sim卡状态*/
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MML_SetSimCsRegStatus(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* SIM有效                                  */
        /* IMSI */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
           |= MM_MS_ID_IMSI_PRESENT;                                            /* 置Mobile ID存在标志                      */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        /* 根据当前存储的TMSI是否有效，设定是否存在TMSI */
        ulInvalidCnt = 0;
        pucTmpTmsi = NAS_MML_GetUeIdTmsi();
        for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
        {
            if (NAS_MML_TMSI_INVALID == pucTmpTmsi[i])
            {
                ulInvalidCnt++;
            }
        }

        if ( ulInvalidCnt < NAS_MML_MAX_PTMSI_LEN )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
                |= MM_MS_ID_TMSI_PRESENT;

        }


        /* 保存分配当前TMSI的网络ID */
        if ( MM_MS_ID_TMSI_PRESENT ==
              (MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg) )
        {
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        }
    }

    /* IMEI(SV) */
    pstMsCapability = NAS_MML_GetMsCapability();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMEI_PRESENT;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[0]
       = (VOS_UINT8)((pstMsCapability->aucImeisv[0] << 4) | 0x0f);

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_IMEISV_PRESENT;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[0]
       = g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[0];

    for (i = MM_CONST_NUM_1; i < MM_CONST_NUM_8; i++ )
    {                                                                           /* 存储IMEI                                 */
        g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[i]
           = (VOS_UINT8)((pstMsCapability->aucImeisv[2*i]<<4)
                       | pstMsCapability->aucImeisv[(2*i)-1]);
        g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[i]
           = g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[i];
    }
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImei[7] &= 0x0f;
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[8]
       = (VOS_UINT8)( pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1]
                   & 0x0f);
    g_MmGlobalInfo.MsCsInfo.MobileId.aucImeisv[8] |= 0xf0;




    /* 为了防止使用测试号段避过IMSI的检查，使得能够使用TMSI进行注册，需要
       进行防卡贴的判定，在NV项激活的情况下，特殊号段TMSI置为无效
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    }


    Mm_SndMmcStartCnf();
}


/***********************************************************************
 *  MODULE   : Mm_ComToU2Handle
 *  FUNCTION : MM进U2的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-09  新版作成,二期添加
    2.  日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm注册状态修改
    3. 日    期   : 2010年12月24日
       作    者   : s46746
      修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
    4.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    5.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
************************************************************************/

VOS_VOID Mm_ComToU2Handle()
{
    /* g_MmSubLyrShare.MmShare.ucUpdateSts = MM_UPDATE_STATUS_NOT_UPDATED; */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    MM_CKSN_INVALID
                    );                                                          /* 设置MM信息                               */
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

    NAS_MML_InitUeIdTmsiInvalid();

    /* Mm_SndAgentUsimUpdateFileReq(MM_READ_CKIK_FILE_ID); */                    /* 更新SIM卡更新状态                        */
    Mm_ComUpdateUsimFileReq();


    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                              */
    /*" \nMM:STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE\r " );                     */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComToU2Handle:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
}


/***********************************************************************
 *  MODULE   : Mm_ComLuCauseHandle
 *  FUNCTION : MM对LU过程原因值的处理
 *  INPUT    : VOS_UINT8   ucCause                  原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-09  新版作成,二期添加
    2.  s46746  2006-07-25  根据问题单A32D05058修改
    3.日    期   : 2006年11月22日
      作    者   : luojian id:60022475
      修改内容   : 问题单号：A32D07583
    4.日    期   : 2007年05月11日
      作    者   : luojian id:60022475
      修改内容   : 问题单号:A32D10713
    5.日    期   : 2007年06月01日
      作    者   : luojian id:60022475
      修改内容   : 问题单号:A32D1964
    6.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    7.日    期   : 2011年7月28日
      作    者   : sunxibo 46746
      修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
    8.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    9.日    期   :2013年9月12日
      作    者   :z00161729
      修改内容  :DTS2013082903019:支持ss重发功能
    10.日    期   : 2014年5月21日
       作    者   : w00167002
       修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                MM删除对SOR的特殊处理。
    11.日    期   : 2014年6月4日
       作    者   : w00167002
       修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                    是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                    发起了LAU.
                    在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                    DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                    在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                    不发起LAU.
    12.日    期   : 2015年3月20日
       作    者   : w00167002
       修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
 ************************************************************************/

VOS_VOID Mm_ComLuCauseHandle(VOS_UINT16 usCause)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.usCauseVal   = usCause;                            /* 记录原因值                               */
    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:

        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_NO_IMSI");

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;
        Mm_ComUpdateUsimFileReq();


        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* 设置LU COUNTER为0                        */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;   /* 设置TMIS不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* 设置LU COUNTER为0                        */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }


        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* 判断LU Counter是否小于4                  */
            enCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();
            if ( ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 判断LAI是否未改变,且更新状态为U1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");

                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComLuCauseHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
            }
            else
            {
                if ( ( usCause >=
                    MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW ) &&
                    ( usCause <=
                    MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP ) )
                {                                                               /* 判断原因值是否在retry范围内              */
                    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;                 /* 设置ucRetryFlg为MM_TRUE                  */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;                /* 设置ucRetryFlg为MM_FALSE                 */
                }

                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComToU2Handle();
                Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
            }
        }
        else
        {
            if ( ( usCause >
                MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_LOW ) &&
                ( usCause <
                MM_IE_REJ_CAUSE_RETRY_UPON_ENTRY_INTO_NEW_CELL_UP ) )
            {                                                                   /* 判断原因值是否在retry范围内              */
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;                     /* 设置ucRetryFlg为MM_TRUE                  */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;                    /* 设置ucRetryFlg为MM_FALSE                 */
            }
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComLuCauseHandle:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            Mm_ComToU2Handle();



            /* SOR特性由MMC触发MM发起LAU */
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);



            /*A32D10964==>*/
            if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
            {
                Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
                g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
                Mm_Cell_S0_E23(VOS_NULL_PTR);
            }
            /*<==A32D10964*/
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_FALSE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}

/***********************************************************************
 *  MODULE   : Mm_ComGmmAttachCauseHandle
 *  FUNCTION : MM对GMM ATTACH过程原因值的处理
 *  INPUT    : VOS_UINT8   ucCause                  原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-09  新版作成,二期添加
    2. 日    期   : 2007年3月5日
       作    者   : liurui id:40632
       修改内容   : 根据问题单号：A32D09094
    3. 日    期   : 2008年09月03日
       作    者   : l00130025
       修改内容   : 问题单号：AT2D05403,mm注册状态修改
    4.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    5.日    期   : 2011年07月21日
      作    者   : h44270
      修改内容   : 问题单号：DTS2011071901850,PLMN NOT ALLOW时停T3212定时器
    6.日    期   : 2011年11月22日
      作    者   : W00166186
      修改内容   : DTS2011122107833,PS 11拒绝，CS ok等效PLMN没有删除
    7.日    期   : 2013年03月14日
      作    者   : l65478
      修改内容   : DTS2013031309016,PS REJ#3时，没有把CS卡置为无效
    8.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    9.日    期   : 2014年4月2日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
    10.日    期   : 2015年2月6日
       作    者   : h00313353
       修改内容   : USIMM卡接口调整
 ************************************************************************/

VOS_VOID Mm_ComGmmAttachCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* 参考24.008：
           If the MS is IMSI attached, the MS shall in addition
           set the update status to U3 ROAMING NOT ALLOWED,
           shall delete any TMSI, LAI and ciphering key sequence number.
           If the MS is operating in MS operation mode A and an RR connection exists,
           the MS shall abort the RR connection, unless an emergency call is ongoing.
           The SIM/USIM shall be considered as invalid also for non-GPRS services
           until switching off or the SIM/USIM is removed */
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_NO_IMSI \r " );                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);          /* 设置更新状态                             */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             MM_CKSN_INVALID
                             );
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;

            NAS_MML_InitUeIdTmsiInvalid();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_IMSI_PRESENT;

            Mm_ComUpdateUsimFileReq();

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_ATTACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_GMM_ATTACH_PROC \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_GMM_ATTACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmAttachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MM_UpdateEquPlmnInfo(usCause);

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmAttachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == usCause)
            {
                /* Modified by h44270 for DTS2011071901850， 2011-07-21 Begin */
                Mm_TimerStop(MM_TIMER_T3212);
                /* Modified by h44270 for DTS2011071901850， 2011-07-21 end */
            }
        }
        break;
    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComGmmRauCauseHandle
 *  FUNCTION : MM对GMM RAU过程原因值的处理
 *  INPUT    : VOS_UINT8   ucCause                  原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-10  新版作成,二期添加
    2.  日    期   : 2007年1月26日
        作    者   : liurui id:40632
        修改内容   : 根据问题单号：A32D08577
    3.  日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm注册状态修改
    4.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    5.日    期   : 2011年07月21日
      作    者   : h44270
      修改内容   : 问题单号：DTS2011071901850,PLMN NOT ALLOW时停T3212定时器
    6.日    期   : 2011年11月22日
      作    者   : W00166186
      修改内容   : DTS2011111400747,RAU被3号或6号原因值拒绝后，后续又发起了LAU
    7.日    期   : 2011年11月22日
      作    者   : W00166186
      修改内容   : DTS2011122107833,PS 11拒绝，CS ok等效PLMN没有删除
    8.日    期   : 2012年04月19日
      作    者   : W00166186
      修改内容   : DTS2012041804101,一个域被拒13#,没有删除EPLMN
    9.日    期   : 2013年03月14日
      作    者   : l65478
      修改内容   : DTS2013031309016,PS REJ#3时，没有把CS卡置为无效
   10.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   11.日    期   : 2014年4月2日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 ************************************************************************/

VOS_VOID Mm_ComGmmRauCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* 参考24.008：
           If the MS is IMSI attached, the MS shall in addition
           set the update status to U3 ROAMING NOT ALLOWED,
           shall delete any TMSI, LAI and ciphering key sequence number.
           If the MS is operating in MS operation mode A and an RR connection exists,
           the MS shall abort the RR connection, unless an emergency call is ongoing.
           The SIM/USIM shall be considered as invalid also for non-GPRS services
           until switching off or the SIM/USIM is removed */
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.usCauseVal   = usCause;                                /* 记录原因值                               */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_NO_IMSI \r " );                       */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);          /* 设置更新状态                             */

            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             MM_CKSN_INVALID
                             );
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;

            NAS_MML_InitUeIdTmsiInvalid();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_IMSI_PRESENT;

            Mm_ComUpdateUsimFileReq();

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MM_UpdateEquPlmnInfo(usCause);

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == usCause)
            {
                /* Modified by h44270 for DTS2011071901850， 2011-07-21 Begin */
                Mm_TimerStop(MM_TIMER_T3212);
                /* Modified by h44270 for DTS2011071901850， 2011-07-21 end */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        /*if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )*/
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_RAU_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_RAU_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_GMM_RAU_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmRauCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            NAS_MML_GetSimCsSecurityCksn()
                            );                                                  /* 设置MM信息                               */


            NAS_MM_UpdateEquPlmnInfo(usCause);

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);             /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);              /* 更新SIM卡更新状态                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmRauCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    default:
        break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcGmmSeriveRejCause3
 功能描述  : MM处理gmm发来的service被拒原因值#3/#6/#8
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月11日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID NAS_MM_ProcGmmSeriveRejCause3(VOS_UINT16 usCause)
{
    g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
    g_MmGlobalInfo.usCauseVal   = usCause;
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(
                     MM_STATUS_DETACHED,
                     MM_CKSN_INVALID
                     );                                                     /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
    Mm_ComDelLai();                                                         /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                        ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMSI不存在                           */

    NAS_MML_InitUeIdTmsiInvalid();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;         /* 设置IMSI不存在                           */

    Mm_ComUpdateUsimFileReq();

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    Mm_ComSetMmState(MM_IDLE_NO_IMSI);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
    Mm_ComProcCauseClear();

    return;

}

/***********************************************************************
 *  MODULE   : Mm_ComGmmSrCauseHandle
 *  FUNCTION : MM对GMM SR过程原因值的处理
 *  INPUT    : VOS_UINT8   ucCause                  原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.张志勇    04-03-10  新版作成,二期添加
    2.日    期   : 2008年09月03日
      作    者   : l00130025
      修改内容   : 问题单号：AT2D05403,mm注册状态修改
    3.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    4.日    期   : 2011年07月21日
      作    者   : h44270
      修改内容   : 问题单号：DTS2011071901850,PLMN NOT ALLOW时停T3212定时器

    5.日    期   : 2013年2月4日
      作    者   : w00176964
      修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
    6.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    7.日    期   : 2013年9月12日
      作    者   : w00242748
      修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                   原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                   G下原小区时做LAU
    8.日    期   : 2014年4月2日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
    9.日    期   : 2015年3月20日
      作    者   : w00167002
      修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                   进行封装。
    10.日    期   : 2015年6月11日
       作    者   : z00161729
       修改内容   : 24008 23122 R11 CR升级项目修改
************************************************************************/

VOS_VOID Mm_ComGmmSrCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        NAS_MM_ProcGmmSeriveRejCause3(usCause);
        break;

    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
    /*24008_CR2297R2_(Rel-11)_C1-124967 24008 4.7.13.4描述如下:
    #8 - The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED (and
    shall store it according to subclause 4.1.3.2) and shall delete any P-TMSI,
    P-TMSI signature, RAI and GPRS ciphering key sequence number. The new GMM state
    is GMM-DEREGISTERED.
    The MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI
    and ciphering key sequence number. If the MS is operating in MS operation mode A and an RR
    connection exists, the MS shall abort the RR connection, unless an emergency call is ongoing.
    The SIM/USIM shall be considered as invalid for GPRS and non-GPRS services until switching off
    or the SIM/USIM is removed. */
        NAS_MM_ProcGmmSeriveRejCause3(usCause);
        break;


    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* 如果为A+I模式                            */
            if ( (MM_FALSE == g_MmGlobalInfo.ucLikeB)
             && ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                   && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))))

            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似B模式                            */
                /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );*/
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMIS不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComProcCauseClear();

        /* Modified by h44270 for DTS2011071901850， 2011-07-21 Begin */
        Mm_TimerStop(MM_TIMER_T3212);
        /* Modified by h44270 for DTS2011071901850， 2011-07-21 end */

        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_GMM_SR_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_GMM_SR_PROC \r " );                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_GMM_SR_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /* " \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );              */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComGmmSrCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            NAS_MML_GetSimCsSecurityCksn()
                            );                                                  /* 设置MM信息                               */


            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);             /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);              /* 更新SIM卡更新状态                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComGmmSrCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;
    default:
        break;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedStartT3212RcvGmmDetachInd
 功能描述  : 判断MM收到gmm的detach ind消息是否需要启动T3212
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要启动T3212
             VOS_FALSE - 不需要启动T3212
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedStartT3212RcvGmmDetachInd( VOS_VOID )
{
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
       || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
        && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus))))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/***********************************************************************
 *  MODULE   : Mm_ComNetDetachCauseHandle
 *  FUNCTION : MM对NET DETACH过程原因值的处理
 *  INPUT    : VOS_UINT8   ucCause                  原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-10  新版作成,二期添加
    2.  日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm注册状态修改
    3.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    4.日    期   : 2011年07月05日
      作    者   : c00173809
      修改内容   : DTS2011070100651,BVT用例6.2.7失败，在HOME PLMN上，GMM收到网测DETACH，
           原因为PLMN NOT ALLOW，重选到LAI的小区，没有发起LAU。

    5.日    期   : 2013年2月4日
      作    者   : w00176964
      修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
    6.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    7.日    期   : 2013年9月12日
      作    者   : w00242748
      修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                   原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                   G下原小区时做LAU
    8.日    期   : 2014年4月2日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
    9.日    期   : 2015年3月20日
      作    者   : w00167002
      修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                   进行封装。
    10.日    期   : 2015年6月8日
       作    者   : z00161729
       修改内容   : 24008 23122 R11 CR升级项目修改
************************************************************************/

VOS_VOID Mm_ComNetDetachCauseHandle(VOS_UINT16 usCause)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    switch(usCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NO_IMSI \r " );  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NO_IMSI");
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);              /* 设置更新状态                             */

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         MM_CKSN_INVALID
                         );                                                     /* 向RRC发送RRMM_NAS_INFO_CHANGE_REQ        */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMSI不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_IMSI_PRESENT;         /* 设置IMSI不存在                           */

        Mm_ComUpdateUsimFileReq();

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        Mm_ComProcCauseClear();
        break;

        /*24008_CR2243R2_(Rel-11)_C1-124176 24008  4.7.4.2.2章节描述如下:
        If the MS is attached for GPRS and non-GPRS services and the network operates in network operation mode I,
        then if in the MS the timer T3212 is not already running, the timer T3212 shall be
        set to its initial value and restarted if:
        -   the detach type IE indicates "re-attach required";
        -   the detach type IE indicates "re-attach not required" and no cause code is included; or
        -   the detach type IE indicates "re-attach not required" and the cause code is #7 "GPRS services not allowed"
            or #14 "GPRS services not allowed in this PLMN". */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
    case NAS_MML_REG_FAIL_CAUSE_NULL:
        if (VOS_TRUE == NAS_MM_IsNeedStartT3212RcvGmmDetachInd())
        {
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式                          */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmLikeB is MM_TRUE");
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        /* g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;    */
        /* g_MmGlobalInfo.usCauseVal   = ucCause;               */
        /* g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE; */              /* 设置服务状态                             */
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
        g_MmGlobalInfo.usCauseVal   = usCause;
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* 设置服务状态                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );                   */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);              /* 设置更新状态                             */
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        MM_CKSN_INVALID
                        );                                                      /* 设置MM信息                               */
        Mm_ComDelLai();                                                         /* 删除LAI                                  */
        g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_TMSI_PRESENT;             /* 设置TMIS不存在                           */

        NAS_MML_InitUeIdTmsiInvalid();

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComProcCauseClear();
        /* Modified by c00173809 for DTS2011070100651， 2011-07-05 Begin */
        Mm_TimerStop(MM_TIMER_T3212);
        /* Modified by c00173809 for DTS2011070100651， 2011-07-05 End */
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            g_MmGlobalInfo.ucProc       = MM_NET_DETACH_PROC;
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_NET_DETACH_PROC");
            g_MmGlobalInfo.usCauseVal   = usCause;
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*" \nMM:MmServiceState is MM_LIMITED_SERVICE \r " );               */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComNetDetachCauseHandle:INFO: MmServiceState is MM_LIMITED_SERVICE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;               /* 设置LU COUNTER为0                        */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* 设置更新状态                             */
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;         /* 设置TMIS不存在                           */

            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComNetDetachCauseHandle:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComProcCauseClear();
        }
        break;



    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComCauseHandleAllProc
 *  FUNCTION : MM对原因值的处理
 *  INPUT    : VOS_UINT8   ucProcType                当前流程的类型
 *             VOS_UINT8   ucCause                   流程收到的原因值
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  张志勇    04-03-10  新版作成,二期添加
 *     2.
 ************************************************************************/

VOS_VOID Mm_ComCauseHandleAllProc(
                              VOS_UINT8   ucProcType,
                              VOS_UINT16  usCause
                              )
{
    switch(ucProcType)
    {
    case MM_LU_PROC:
        Mm_ComLuCauseHandle(usCause);
        break;
    case MM_GMM_ATTACH_PROC:
        Mm_ComGmmAttachCauseHandle(usCause);
        break;
    case MM_GMM_RAU_PROC:
        Mm_ComGmmRauCauseHandle(usCause);
        break;
    case MM_GMM_SR_PROC:
        Mm_ComGmmSrCauseHandle(usCause);
        break;
    case MM_NET_DETACH_PROC:
        Mm_ComNetDetachCauseHandle(usCause);
        break;
    default:
        break;
    }
}
/*****************************************************************************
 函 数 名  : NAS_MM_DelLaiTmsiCK
 功能描述  : 删除LAI、TMSI、CK或者KC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月14日
   作    者   : luokaihui / 00167671
   修改内容   : 新生成函数
 2.日    期   : 2011年3月14日
   作    者   : w00167002
   修改内容   : 删除将CS域卡设置为无效的代码: NAS_MML_SetSimCsRegStatus(VOS_FALSE);
                原因:L下注册被拒原因值#11，后在GU下注册，CS域被设置为卡无效
 3.日    期   : 2011年10月31日
   作    者   : s46746
   修改内容   : V7R1 PhaseIII,支持L模联合注册
*****************************************************************************/
VOS_VOID NAS_MM_DelLaiTmsiCK(VOS_VOID)
{
    /* 删除全局变量中的LAI */
    Mm_ComDelLai();

    /* 删除全局变量中的TMSI */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg              &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();

    /* 删除SIM卡中的LAI、IMSI */
    NAS_MM_WriteLocaInCard();

    NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);

    /* 根据SIM卡类型决定当前需要删除KC还是CKIK*/
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        NAS_MM_WriteKCInCard();
    }
    else
    {
        NAS_MM_WriteCkIkInCard();
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComToNoImsiHandle
 *  FUNCTION : MM进到NO SIM的公共处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-11  新版作成,二期添加
    2. 日    期   : 2007年12月12日
       作    者   : l00107747
       修改内容   : 根据问题单号：A32D13861
    3.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
************************************************************************/

VOS_VOID Mm_ComToNoImsiHandle()
{
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);                  /* 设置更新状态                             */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, MM_CKSN_INVALID);
    Mm_ComDelLai();                                                             /* 删除LAI                                  */
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
    NAS_MML_InitUeIdTmsiInvalid();
    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                            ~MM_MS_ID_IMSI_PRESENT;

    Mm_ComUpdateUsimFileReq();

}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1
 功能描述  : 网络模式I收到系统消息指示cs不bar、ps bar，位置区未改变,mm update状态
             是U1态在location update needed时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月21日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1(VOS_VOID)
{
    /* 如果LAI不变,更新状态为U1                 */
    if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
    {
        Mm_ComNasInfoSav(
                         MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn()
                         );

        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
            }

            NAS_MM_NotifyAsInfoChgReq();

            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;/* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                 NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else
    {
        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
        {
            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(MM_FALSE, MM_IE_LUT_IMSI_ATTACH);
        }
        else
        {
            Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                              /* 设置服务状态                             */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }

    return;
}



/***********************************************************************
 *  MODULE   : Mm_ComSysInfoHandleWithLaiNoChange
 *  FUNCTION : 在位置区不改变时的公共处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-11  新版作成,二期添加
    2. 日    期   : 2009年8月23日
       作    者   : l65478
       修改内容   : 问题单号：AT2D13980,在LU失败后，改变小区后，此后再不会发起LU,因为在收到系统信息时，把T3211停止了
    3. 日    期   : 2010年10月5日
       作    者   : 欧阳飞
       修改内容   : DTS2010100500028, LAU 4次失败后触发MMC发起列表搜网，仍然驻
                    留原小区，此后背景搜定时器超时，未发起背景搜
    4. 日    期   : 2010年9月29日
       作    者   : w00167002
       修改内容   : 问题单号：DTS2010091903182,注册失败后，没有发起搜网
    5.日    期   : 2011年7月14日
      作    者   : h44270
      修改内容   : V7R1 PhaseII阶段调整，注册结果简化
    6.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    7.日    期   : 2011年12月23日
      作    者   : w00167002
      修改内容   : DTS2011111901055:假流程上报原因值由NAS_MML_REG_FAIL_CAUSE_NULL
                   修改为NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                   修改原因:在ON PLMN状态，收到此假流程消息，若原因值小于
                   NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE，则可能发起搜网。
    8.日    期   : 2012年02月23日
      作    者   : l65478
      修改内容  : DTS2012020402238,GCF测试，LU类型错误
    9.日    期   : 2012年02月07日
      作    者   : l65478
      修改内容   : DTS2012012902539:从G->L->G重选时，在L下CS注册失败,回到G下MM没有发起注册
   10.日    期   : 2012年03月20日
      作    者   : l00130025
      修改内容   : DTS2012030105247,NAS只在网侧实际发起鉴权时,通知W SecurityKey，其它情况下由WAS调用对应接口获取
   11.日    期   : 2012年9月24日
      作    者   : s46746
      修改内容   : 问题单号DTS2012090801459，进行位置更新时停止T3212
   12.日    期   : 2012年12月25日
      作    者   : l00167671
      修改内容   : 问题单号DTSl00167671，L下搜网打紧急呼时到W下搜到与上次注册相同的小区
                   先发起了LU
   13.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   14.日    期   : 2013年06月09日
      作    者   : l65478
      修改内容   : 问题单号DTS2013060407637，T3212长度设置为0,当前环境只存在一个网络并且注册拒绝时每次PLMN搜索结束后MM立刻发起注册
   15.日    期   : 2014年5月21日
      作    者   : w00167002
      修改内容   : DTS2014051602857:在SOR打开时候，用户指定搜网时候，则清除ATTEMPT
                   COUNTER。
   16.日    期   : 2014年8月14日
      作    者   : z00161729
      修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
   17.日    期   : 2015年3月20日
      作    者   : w00167002
      修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                   进行封装。
 ************************************************************************/
VOS_VOID    Mm_ComSysInfoHandleWithLaiNoChange(VOS_UINT8     ucUserSpecificSearchFlg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        /* 如果LAI不变,更新状态为U1                 */
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_TRUE ==
                g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            }
            else
            {
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                {
                    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                    {
                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
                    }

                    NAS_MM_NotifyAsInfoChgReq();

                    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;/* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                if ( (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3213].ucTimerStatus)
                  || (VOS_TRUE == ulIsTestCard) )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
        else
        {
            if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);
            }
            else if ( MM_TRUE ==
                g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            }
            /* 由于发起LAU的时候停止了T3212，因此如果T3212没有运行，表示前面已经发起过 */
            else if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3213].ucTimerStatus))
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                Mm_ComNasInfoSav(
                         MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn()
                         );
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                              /* 设置服务状态                             */

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComRcvSysHandle:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */


                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComRcvSysHandle:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                if ( (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3213].ucTimerStatus)
                  || (VOS_TRUE == ulIsTestCard) )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
    else if ( (1 == ucUserSpecificSearchFlg)                        /* 用户发起的指定搜网，且当前不在U1，即使位置区不变，也发起注册 */
            ||(MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))             /* 刚开机，位置区不变，也发起注册 */
    {
        /* 搜网状态，在手动搜网时候，则清除ATTMPTCNT */
        if ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }

        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
    }
    else
    {   /* MM 状态迁回到搜网前的状态 */
        /* 在非U1状态并且周期注册定时器没有运行时,要进行一次LU过程 */
        if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
         && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
         && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
        {
            /* 在NOT UPDATED状态，MM应该发起的是NORMAL LU */
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
           NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
        }
        else if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


            /* 如果T3212在运行且T3211不在运行，则通知MMC当前T3212在运行,否则继续等待T3211超时注册处理 */
            if ( (MM_TIMER_STOP     == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
              && (MM_TIMER_RUNNING  == gstMmTimer[MM_TIMER_T3212].ucTimerStatus) )
            {
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_T3212_RUNNING);
            }
            else
            {
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);/* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */

            }

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);              /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
        }
        else
        {

        }
    }
}


/***********************************************************************
 *  MODULE   : Mm_ComRcvSysHandle
 *  FUNCTION : MM在NO CELL和PLMN SEARCH收到系统信息的公共处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *  1.  张志勇    04-03-11  新版作成,二期添加
    2.  s46746    06-06-21  根据问题单A32D04355修改
    3. s46746  2006-07-27 根据问题单A32D03975修改
    4.日    期   : 2006年11月22日
      作    者   : luojian   id:60022475
      修改内容   : 问题单号：A32D07582
    5.日    期   : 2008年8月21日
      作    者   : l00130025
      修改内容   : 问题单号:At2D05016,MM注册状态修改
    6.日    期   : 2008年12月22日
      作    者   : o00132663
      修改内容   : 问题单号:AT2D07757,MM丢网后重回原小区，不发起LU
    7.日    期   : 2009年01月05日
      作    者   : l65478
      修改内容   : 根据问题单:AT2D07749,修改周期搜网时间,在重进服务区时，如果LAI不改变，不应该进行LU
    8.日    期   : 2011年7月14日
      作    者   : h44270
      修改内容   : V7R1 PhaseII阶段调整，注册结果简化
    9.日    期   : 2011年10月27日
      作    者   : s46746
      修改内容   : V7R1 PhaseIII,支持L模联合注册
   10.日    期   : 2012年03月17日
      作    者   : s46746
      修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
    11.日    期  : 2012年2月15日
       作    者  : z00161729
       修改内容  : V7R1C50 支持CSFB特性修改，存在CSFB标志时，发起LAU
    12.日    期  : 2012年3月21日
       作    者  : w00166186
       修改内容  : V7R1C50 L异系统到G时，不停的LAU
   13.日    期   : 2012年11月07日
      作    者   : t00212959
      修改内容   : DTS2011110100336,紧急呼先呼叫后做LAU
   14.日    期   : 2013年05月15日
      作    者   : s46746
      修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   15.日    期   : 2013年10月15日
      作    者   : l65478
      修改内容   : DTS2013102501008从收到搜网模式设置成自动搜网模式后没有发起注册
   16.日    期   : 2013年12月5日
      作    者   : w00167002
      修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                   PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                   上，不发起注册，重选回LAC1上，检测不发起注册。
   17.日    期   : 2014年04月1日
      作    者   : w00176964
      修改内容   : V3R3C60_eCall项目:系统消息处理优化以及全局变量替换
  18.日    期   : 2014年6月4日
      作    者   : w00167002
      修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                 是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                 发起了LAU.
                 在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                 DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                 在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                 不发起LAU.
************************************************************************/

VOS_VOID Mm_ComRcvSysHandle(VOS_UINT8     ucUserSpecificSearchFlg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    MM_LAI_STRU                         stCurLai;
    NAS_MML_LAI_STRU                   *pstCurrCampLai = VOS_NULL_PTR;

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
    {
        return;
    }
#endif

    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);

    /* 在前状态是attempt tO update时,和上一次驻留的LAI相比较;
       在前状态是limit service时,和上次成功驻留的LAI相比较 */
    if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            if (VOS_FALSE == NAS_MM_IsSameLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo(),
                                                   &stCurLai))

            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                return;
            }
        }
        else if (MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucNotCampONPreState)
        {
            if (VOS_TRUE == ulLaiChangeFlag)
            {
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                return;
            }
        }
        else
        {
        }
    }

    if ( g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod )
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
            {
                Mm_TimerStop(MM_TIMER_T3213);
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                Mm_ComSysInfoHandleWithLaiNoChange(ucUserSpecificSearchFlg);
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        else if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
             /* 如果在NOT UPDATE时候，当前LAI不再ATTEMPT LAI中，则发起LAU */
            if (VOS_FALSE == NAS_MM_IsSameLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo(), &stCurLai))
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            {
                /* 发送LU REQ */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                /* LA 没发生改变 */
                Mm_ComSysInfoHandleWithLaiNoChange(ucUserSpecificSearchFlg);
            }
        }
        else
        {
            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
        }
    }
    else
    {
        Mm_ComNetModeChange();
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
}


/*******************************************************************************
  MODULE   : Mm_ComMmConnExist
  FUNCTION : 判断是否有MM连接存在
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_UINT8             ucResult         是否有MM连接存在的结果
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11  新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMmConnExist(
                        VOS_VOID
                    )
{
    VOS_UINT8           ucResult = MM_FALSE;                                        /* 是否有MM连接存在的结果                   */
    VOS_UINT8           i        = 0;                                               /* 循环变量                                 */

    for ( i = 0; i < MM_CONN_CM_ENTITY_NUM; i++)
    {                                                                           /* 遍历CM实体个数                           */
        if ( ( MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[i].aucMMConnExtFlg[0] )
            || ( MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[i].aucMMConnExtFlg[1] ) )
        {                                                                       /* 有存在的MM连接                           */
            ucResult = MM_TRUE;                                                 /* 返回值设置成有MM连接存在                 */
        }
    }

    return ucResult;
}


/*******************************************************************************
  MODULE   : Mm_ComSaveProcAndCauseVal
  FUNCTION : 存储流程和原因值
  INPUT    : VOS_UINT8             ucProc          流程
             VOS_UINT8             ucCauseVal      原因值
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
*******************************************************************************/
VOS_VOID Mm_ComSaveProcAndCauseVal(
                                VOS_UINT8             ucProc,
                                VOS_UINT16            usCauseVal
                                )
{
    if ( ( MM_NULL_PROC == g_MmGlobalInfo.ucProc )
        && ( NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal ) )
    {
        g_MmGlobalInfo.usCauseVal   = usCauseVal;
        g_MmGlobalInfo.ucProc       = ucProc;
    }
    else
    {
        if ( ( MM_NULL_PROC != ucProc )
            && ( NAS_MML_REG_FAIL_CAUSE_NULL != usCauseVal ) )
        {
            g_MmGlobalInfo.usCauseVal   = usCauseVal;
            g_MmGlobalInfo.ucProc       = ucProc;
        }
        else
        {
            if ( MM_AUTH_FAIL_PROC == ucProc )
            {
                g_MmGlobalInfo.usCauseVal   = usCauseVal;
                g_MmGlobalInfo.ucProc       = ucProc;
            }
        }
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_ComJudgeLimitSvc
  FUNCTION : 判断是否是受限服务状态
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_UINT8             ucResult         是否是受限服务
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
     2.
*******************************************************************************/
VOS_UINT8 Mm_ComJudgeLimitSvc(
                         VOS_VOID
                         )
{
    VOS_UINT8             ucResult = MM_FALSE;                                      /* 是否是受限服务                           */
    if ( ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
        || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )
        || ( MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState ) )
    {                                                                           /* 是受限服务                               */
        ucResult = MM_TRUE;                                                     /* 设置是受限服务                           */
    }

    return ucResult;                                                            /* 返回                                     */
}

/*******************************************************************************
  MODULE   : Mm_ComFillInCMSncReq
  FUNCTION : 填充消息内容
  INPUT    : VOS_UINT8                      ucCMSvcType          CM服务类型
             VOS_UINT8                      ucPrioLeveFlg        优先级
             MM_MSG_CM_SVC_REQ_STRU     *CmSvcReq            消息内容结构体指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成

  2.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
*******************************************************************************/
VOS_VOID Mm_ComFillInCMSncReq(
                            VOS_UINT8                       ucCMSvcType,
                            VOS_UINT8                       ucPrioLeveFlg,
                            MM_MSG_CM_SVC_REQ_STRU      *CmSvcReq
                            )
{
    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }
    
    CmSvcReq->MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();           /* 存储CKSN                                 */
    CmSvcReq->MmIeCmSvcType.ucCMSvcType = ucCMSvcType;                          /* Supplementary service activation         */
    NAS_MM_FillMobileID(&(CmSvcReq->MmIeMobileId.MobileID));
    CmSvcReq->ucPrioLeveFlg = ucPrioLeveFlg;                                    /* 没有优先级                               */

    return;
}
/*******************************************************************************
  MODULE   : Mm_ComFollowOnProc
  FUNCTION : 处理带有FollowOn的情况
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15    新版作成
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建

  2.日    期   : 2013年4月15日
    作    者   : w00167002
    修改内容   : DTS2013041108015:用户通过HISC2通道在L下发起SMS业务，SMS业务
                  失败，用户在HISC1通道发起普通电话业务，在GU下LAU成功后，
                  指示FOLLOW ON标识，电话业务与SMS业务同时发起，收到CM SERVICE RSLT
                  时候，MM无法判别收到时哪一个CM业务的结果。
                  修改为MM只发送一条CM SERVICE REQ,SMS业务被缓存，这样MM在收到
                  CM SERVICE RSLT时候便可发起缓存的SMS业务。
  3.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
  5.日    期   :2015年02月23日
    作    者   :j00174725
    修改内容   :for DTS2015012303754
*******************************************************************************/
VOS_VOID Mm_ComFollowOnProc(
                        VOS_VOID
                        )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT8                           ucCmSvsType;
    VOS_UINT8                           ucPdType;
    NAS_MM_CONN_CTRL_ENUM_UINT8         i;

    /* 局部变量初始化 */
    ucCmSvsType = 0xFF;
    ucPdType    = 0xFF;
    i           = MM_CONN_CTRL_CC;

    /* 有缓存的合法的CC业务的处理 */
    if (  ( MM_CONST_NUM_7 <
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_CONST_NUM_15 >
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_TRUE ==
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg ) )
    {                                                                           /* 有等待的CC触发的需要建立的MM连接         */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;             /* 记录收到建立请求时的状态                 */
        if ( MMCC_MO_NORMAL_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
        {                                                                       /* 正常呼叫                                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                MM_FALSE, &CmSvcReq);                                           /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                = MM_FALSE;                                                     /* 正常呼叫                                 */
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE);
        }
        else
        {                                                                       /* 紧急呼叫                                 */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                MM_FALSE, &CmSvcReq);                                           /* 填充CM SERVICE REQUEST结构体             */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                = MM_TRUE;                                                      /* 紧急呼叫                                 */
            NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
        }
        Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                        /* 向网侧发送建立MM连接的请求               */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            RcvXXEstReq.ulTransactionId;                                        /* 记录正在建立的MM连接                     */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;                /* 记录正在建立的MM连接的PD                 */
        g_MmGlobalInfo.ucPreState   = WAIT_FOR_RR_CONNECTION_MM_CONNECTION;     /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        Mm_TimerStart(MM_TIMER_T3230);                                          /* 启动TIMER3230                            */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;  /* 清除存在缓存的MM连接建立请求的标志       */

        /* 通知MMC当前CS业务已经建立 */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

        /* 更新CS业务连接状态 */
        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

        return;
    }

    /* 有缓存的不合法的CC业务的处理 */
    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {
        /* 有等待的CC要求建立的MM连接,TI不合法      */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);   /* 通知CC建立失败  */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;  /* 清除存在缓存的MM连接建立请求的标志       */

    }

    /* 循环处理CM缓存业务 */
    for ( i = 0 ; i < MM_CONN_CTRL_BUTT; i++ )
    {
        if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg )
        {
            if (  ( MM_CONST_NUM_7 <  g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId)
               && ( MM_CONST_NUM_15 > g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId) )
            {
                if ( MM_CONN_CTRL_SS == i )
                {
                    ucCmSvsType = MM_IE_CM_SVC_TYPE_SS_ACT;
                    ucPdType    = MM_IE_PD_NON_CALL_RLT_SS_MSG;
                }
                else if ( MM_CONN_CTRL_SMS == i )
                {
                    ucCmSvsType = MM_IE_CM_SVC_TYPE_SMS;
                    ucPdType    = MM_IE_PD_SMS_MSG;
                }
                else
                {
                    /* 非SS/SMS消息，则异常处理 */
                    break;
                }


                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;         /* 记录收到建立请求时的状态                 */
                Mm_ComFillInCMSncReq(ucCmSvsType,
                    MM_FALSE, &CmSvcReq);                                           /* 填充CM SERVICE REQUEST结构体             */
                Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* 向网侧发送建立MM连接的请求               */

                g_MmGlobalInfo.ConnCtrlInfo[i].ucMMConnEstingTI =
                (VOS_UINT8)g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId;                                        /* 记录正在建立的MM连接                     */
                g_MmGlobalInfo.ucMMConnEstingPD = ucPdType;                         /* 记录正在建立的MM连接的PD                 */
                g_MmGlobalInfo.ucPreState   = WAIT_FOR_RR_CONNECTION_MM_CONNECTION; /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
                Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */

                /* 清除存在缓存的MM连接建立请求的标志 */
                g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg = MM_FALSE;

                /* 通知MMC当前CS业务已经建立 */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

                /* 更新CS业务连接状态 */
                NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

                /* 处理CM 缓存结束 */
                return;
            }

            /* 有缓存的非法的CM业务的处理 */
            if ( MM_CONN_CTRL_SS == i )
            {
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
            }
            else if ( MM_CONN_CTRL_SMS == i )
            {
                Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[i].
                    RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* 通知SMS建立失败                          */
            }
            else
            {
            }

            /* 清除存在缓存的MM连接建立请求的标志 */
            g_MmGlobalInfo.ConnCtrlInfo[i].RcvXXEstReq.ucFlg = MM_FALSE;

        }

    }

    /* 如果当前没有缓存或者缓存的消息TI非法，则进行状态迁移 */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;        /* 进入空闲的状态                           */
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM连接流程                               */
    g_MmGlobalInfo.ucPreState   = LOCATION_UPDATING_INITIATED;              /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComFollowOnProc:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    Mm_TimerStart(MM_TIMER_T3240);

    return;
}

/*******************************************************************************
  MODULE   : Mm_ComChkAttDelay
  FUNCTION : 检查是否有保留的ATTACH
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_ComChkAttDelay( )
{
    if ( MM_TRUE == g_MmGlobalInfo.ucAttDelay )
    {
        if ( ( MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState )
            && ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
            )
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        g_MmGlobalInfo.ucAttDelay = MM_FALSE;
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_LU_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: LU_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     3.日    期   : 2015年3月20日
       作    者   : w00167002
       修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_LU_PROC(VOS_VOID)
{
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal )
    {
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_LU_PROC:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }
    }
    else
    {
        Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                     /* 调用原因值的处理                         */
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_GMM_ATTACH_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmAttachCauseHandle(g_MmGlobalInfo.usCauseVal);              /* 调用原因值的处理                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: GMM_RAU_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmRauCauseHandle(g_MmGlobalInfo.usCauseVal);                 /* 调用原因值的处理                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_GMM_SR_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        /* 参考4.5.1.1 */
        Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComGmmSrCauseHandle(g_MmGlobalInfo.usCauseVal);                  /* 调用原因值的处理                         */
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_NET_DETACH_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2013年2月4日
       作    者   : w00176964
       修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
     3.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     4.日    期   : 2013年9月12日
       作    者   : w00242748
       修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                    原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                    G下原小区时做LAU
     5.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
     6.日    期   : 2015年3月20日
       作    者   : w00167002
       修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC(VOS_VOID)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComNetDetachCauseHandle(g_MmGlobalInfo.usCauseVal);              /* 调用原因值的处理                         */
        break;
    case NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI:
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        Mm_ComToU2Handle();
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_MM_CONN_PROC处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
    1.  欧阳飞   2009.06.11  新版作成
    2.日    期   : 2011年7月25日
      作    者   : h44270
      修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
   3.日    期   : 201112月16日
     作    者   : l65478
     修改内容   : 问题单号：DTS2011111403722,网络模式I CS注册失败#4时,没有发起注册,导致CS业务不可用
   4.日    期   : 2012年10月29日
     作    者   : z00161729
     修改内容   : DTS2012083102536:支持cc呼叫重建
   5.日    期   : 2013年2月4日
     作    者   : w00176964
     修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
   6.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   7.日    期   :2013年9月12日
     作    者   :z00161729
      修改内容  :DTS2013082903019:支持ss重发功能
   8.日    期   :2014年9月24日
     作    者   :s00217060
     修改内容   :for cs_err_log
************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC(VOS_VOID)
{
    VOS_UINT8                           ucPsSimStatus;

    ucPsSimStatus = NAS_MML_GetSimPsRegStatus();

    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_NULL:
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaAfterWaitForNwkCmd);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

        /* 当前CS有效，LAI没有禁止 */
        if ( (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (( MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
           || ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )))
        {
            /*
            24.008 4.5.1.1 CM SERVICE REJECT Process: If cause value #4
            is received, If subsequently the RR connection is released
            or aborted, this will force the mobile station to initiate
            a normal location updating.
            */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
            if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
             && (VOS_TRUE == ucPsSimStatus)
             && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
            {                                                               /* 判断是否为A+I模式                        */
                /* MM收到CM Service Reject消息时已经通知GMM,GMM在收到
                CM_SERVICE_IND消息指示无CS服务时发起 COMBINED_RALAU_WITH_IMSI_ATTACH*/
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
        else
        {
            /* 释放当前连接 */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            /* 转到连接建立前的状态 */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_MM_NET_ABORT处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT(VOS_VOID)
{
    switch ( g_MmGlobalInfo.usCauseVal )
    {
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        switch ( g_MmGlobalInfo.ucMmServiceState )
        {
        case MM_NORMAL_SERVICE:
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            break;
        case MM_LIMITED_SERVICE:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case MM_ATTEMPTING_TO_UPDATE:
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            break;
        case MM_NO_IMSI:
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        default:
            break;
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    default:
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH
 *  FUNCTION : Mm_ComProcCauseProcess函数降复杂度: MM_IMSI_DETACH处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 ************************************************************************/
VOS_VOID Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH(VOS_VOID)
{
    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    return;
}

/*******************************************************************************
  MODULE   : Mm_ComProcCauseProcess
  FUNCTION : 根据流程和原因值的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2004.04.01  新版作成,MM_PT_二期_BUG_014 对应

     2.日    期   : 2006年4月14日
       作    者   : liuyang id:48197
       修改内容   : 问题单号：A32D03031
     3.日    期   : 2007年06月01日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单A32D10964修改
     4.日    期   : 2007年07月10日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单A32D11966
     5.日    期   : 2008年08月1日
       作    者   : luojian id:00107747
       修改内容   : 根据问题单AT2D04486/AT2D04822
     6.日    期   : 2008年09月03日
       作    者   : l00130025
       修改内容   : 问题单号：AT2D05403,mm注册状态修改
     7.日    期   : 2009年02月21日
       作    者   : l65478
       修改内容   : AT2D09308,收到SR拒绝，如果是原因值6，没有更新服务状态和卡中的文件信息
     8.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_ComProcCauseProcess( )
{
    switch ( g_MmGlobalInfo.ucProc )
    {
    case MM_NULL_PROC:
        break;
    case MM_LU_PROC:
        Mm_ComProcCauseProcess_Handling_LU_PROC();
        break;
    case MM_GMM_ATTACH_PROC:
        Mm_ComProcCauseProcess_Handling_MM_GMM_ATTACH_PROC();
        break;
    case MM_GMM_RAU_PROC:
        Mm_ComProcCauseProcess_Handling_GMM_RAU_PROC();
        break;
    case MM_COMB_ATTACH_PROC:
        break;
    case MM_COMB_RAU_PROC:
        break;
    case MM_GMM_SR_PROC:
        Mm_ComProcCauseProcess_Handling_MM_GMM_SR_PROC();
        break;
    case MM_NET_DETACH_PROC:
        Mm_ComProcCauseProcess_Handling_MM_NET_DETACH_PROC();
        break;
    case MM_AUTH_FAIL_PROC:
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case MM_MM_CONN_PROC:
        Mm_ComProcCauseProcess_Handling_MM_MM_CONN_PROC();
        break;
    case MM_MM_NET_ABORT:
        Mm_ComProcCauseProcess_Handling_MM_MM_NET_ABORT();
        break;
    case MM_IMSI_DETACH:
        Mm_ComProcCauseProcess_Handling_MM_IMSI_DETACH();
        break;
    case MM_MM_MS_AUTH_FAIL_PROC:

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComProcCauseProcess:NORMAL: STATUS is ",g_MmGlobalInfo.ucState);
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComProcCauseProcess:WARNING: ucProc Abnormal");
        break;
    }
    Mm_ComProcCauseClear();
}

/*******************************************************************************
  MODULE   : Mm_ComDelLai
  FUNCTION : 删除LAI的公共处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2004.04.12  新版作成,MM_CHK_BUG_021 对应
     2.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/

VOS_VOID Mm_ComDelLai()
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    pstCsSuccLai->aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstCsSuccLai->aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;
}

/*******************************************************************************
  MODULE   : Mm_ComProcCauseClear
  FUNCTION : 清除原因值和流程
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1. 张志勇   2004.04.26 新规作成
*******************************************************************************/

VOS_VOID Mm_ComProcCauseClear()
{
    g_MmGlobalInfo.ucProc       = MM_NULL_PROC;                                 /* 设置流程                                 */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmServiceState is MM_NULL_PROC \r " );*/
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseClear:INFO: MmServiceState is MM_NULL_PROC");
    g_MmGlobalInfo.usCauseVal   = NAS_MML_REG_FAIL_CAUSE_NULL;                            /* 记录原因值                               */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:mmCauseVal is NAS_MML_REG_FAIL_CAUSE_NULL \r " );*/
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComProcCauseClear:INFO: mmCauseVal is NAS_MML_REG_FAIL_CAUSE_NULL");
}

/*******************************************************************************
  MODULE   : Mm_ComChkLu
  FUNCTION : 处理缓存的LU流程
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1. 张志勇   2004.05.21 新规作成
  2. s46746   2006.07.27 根据问题单A32D03975修改
  3.日    期   : 2009年8月18日
    作    者   : 欧阳飞 00132663
    修改内容   : AT2D13774,正常呼建链过程中发生异系统重选，W->G,NMOII->NMOI，LAI改变，
                 联合RAU成功后，未发起缓存的CS业务。
  4.日    期   : 2009年8月25日
    作    者   : 欧阳飞 00132663
    修改内容   : AT2D14050,【NAS R6协议升级测试】驻留后系统消息改变，指示DSAC PS域被BAR，
                 拨打普通电话,通话期间T3312超时，释放后发起了错误的周期性LAU。
  5.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2011年03月24日
    作    者   : 陈志敏 C00173809
    修改内容   : 问题单号：DTS2011031803983, 异系统切换到被拒12小区,发起LAU
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发

  8.日    期   : 2012年09月21日
    作    者   : z00161729
    修改内容  : DTS2012090706407:法电lau accept中携带与系统消息中不同的non broadcast lai时需要出发lau
  9.日    期   : 2012年10月27日
    作    者   : s000217060
    修改内容  : DTS2012041605494:RRC链接存在，不等系统消息，立即发起LAU
  10.日    期   : 2013年1月9日
    作    者   : l00167671
    修改内容  : DTS2012112803062:打电话过程中从NMOI G小区切换到NMOII W小区再切换回原G小区，发起了LAU
 11.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 12.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 13.日    期   : 2013年09月03日
    作    者   : l65478
    修改内容   : DTS2013041602825:CSFB连接建立失败后没有发起LU
*******************************************************************************/
VOS_UINT8    Mm_ComChkLu( )
{
    VOS_UINT8                           ucRet = MM_FALSE;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;


    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    if (VOS_TRUE != pstConnStatus->ucRrcStatusFlg)
    {
        return MM_FALSE;
    }

    ucRet = NAS_MM_ProcessLuAfterCsConnectNotExist();

    return ucRet;
}

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-18, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-18, end */

/*******************************************************************************
  Module:   Mm_TimerPause
  Function: MM使用定时器暂停
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
*******************************************************************************/
VOS_VOID Mm_TimerPause( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
        {
            if ( MM_TIMER_RUNNING == gstMmTimer[i].ucTimerStatus )
            {
                if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
                {                                                               /* 暂停失败：已经暂停或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerPause:WARNING: TIMER STOP ERROR!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_PAUSE;
            }
        }
    }
    else
    {
        if ( MM_TIMER_RUNNING == gstMmTimer[ucTimerId].ucTimerStatus)
        {                                                                       /* 该timer已经启动                          */

            if ( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer) )
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerPause:WARNING: TIMER STOP ERROR!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_PAUSE;                /* 清Timer的启动标志                        */
        }
    }
}

/*******************************************************************************
  Module:   Mm_TimerResume
  Function: MM使用定时器恢复
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
*******************************************************************************/
VOS_VOID Mm_TimerResume( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
        {
            if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus )
            {




                if( VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[i].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[i].ulTimerLen,         /* 时长                                     */
                                           (VOS_UINT32)i,            /* 消息队列的ID                             */
                                           gstMmTimer[i].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[i].ucMode          /* 消息优先级                               */
                                           ))
                {                                                               /* 恢复失败：已经恢复或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_TimerResume:ERROR: TIMER START ERROR!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_RUNNING;
            }
        }
    }
    else
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[ucTimerId].ucTimerStatus)
        {                                                                       /* 该timer已经启动                          */






            if ( VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* 时长                                     */
                                           (VOS_UINT32)ucTimerId,            /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           ) )
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_TimerResume:ERROR: TIMER START ERROR!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;              /* 清Timer的启动标志                        */
        }
    }
}

/*******************************************************************************
  Module:   Mm_ComT3212
  Function: 保存T3212的时长
  Input:    VOS_UINT8  ucT3212Timer     毫秒单位
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
      2.  s46746     2006.08.02  根据问题单A32D03686修改
      3.  日    期   : 2012年1月30日
          作    者   : l00130025
          修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
      4.日    期   : 2013年5月20日
        作    者   : s00217060
        修改内容   : coverity和foritfy修改
      5.日    期   : 2014年6月22日
        作    者   : z00234330
        修改内容   : coverity和foritfy修改
*******************************************************************************/

VOS_VOID Mm_ComT3212(VOS_UINT32  ulT3212Timer)
{
    VOS_UINT32                          ulTemp;
    VOS_UINT32                          ulTemp1;
    VOS_UINT32                          ulTempRemain;

    /* Modified by z00234330 for PCLINT清理, 2014-06-20, begin */
    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_STATE_NULL:
    case MM_IDLE_NO_CELL_AVAILABLE:
    case MM_IDLE_LIMITED_SERVICE:
    case MM_IDLE_PLMN_SEARCH:
    case MM_IDLE_PLMN_SEARCH_NORMAL_SERVICE:

        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Timer;                    /* T3212时长的赋值                          */

        break;

    /* Modified by z00234330 for PCLINT清理, 2014-06-20, end */

    default:
        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Timer;                    /* T3212时长的赋值                          */

        if ( MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
        {                                                                       /* 如果T3212正在运行中                      */
            ulTemp1 = ulT3212Timer;


            ulTempRemain = MM_CONST_NUM_0;

            if (VOS_NULL_PTR != gstMmTimer[MM_TIMER_T3212].hTimer)
            {
                /* hTimer 为空时，说明此定时器已超时或停止,不为空时，才取其剩余长度 */
                if (VOS_OK != VOS_GetRelTmRemainTime(&(gstMmTimer[MM_TIMER_T3212].hTimer), &ulTempRemain))
                {
                    ulTempRemain = MM_CONST_NUM_0;
                }
            }

            ulTemp = ulTempRemain * MM_TIMER_TICK;


            if ( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_T3212, &gstMmTimer[MM_TIMER_T3212].hTimer ) )
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComT3212:WARNING: TIMER STOP FAILURE!");
            }

            if ( MM_CONST_NUM_0 == ( ulTemp%ulTemp1 ) )
            {
                ulTemp = 1000;
            }
            else
            {
                ulTemp = (VOS_UINT32)ulTemp%ulTemp1;
            }
            if (VOS_OK != Mm_StartRelTimer(
                                           &gstMmTimer[MM_TIMER_T3212].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           ulTemp,         /* 时长                                     */
                                           MM_TIMER_T3212,            /* 消息队列的ID                             */
                                           gstMmTimer[MM_TIMER_T3212].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[MM_TIMER_T3212].ucMode          /* 消息优先级                               */
                                           ) )
            {                                                                   /* 启动失败：已经恢复或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComT3212:WARNING: TIMER START FAILURE!");
            }


        }
        else
        {
            ulTemp1 = ulT3212Timer;

            /* Modified by s00217060 for coverity和foritfy修改 , 2013-05-20, begin */
            /* 随机种子 */
            VOS_SetSeed(VOS_GetTick());

            NAS_MM_SetNetworkT3212RandLen(VOS_Rand(ulTemp1));

            /* Modified by s00217060 for coverity和foritfy修改 , 2013-05-20, end */
        }
        break;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MM_QryTimerStatus
 功能描述  : 查询指定的MM定时器的状态以及剩余时间
 输入参数  : ucTimerId  - 需要查询的定时器ID
 输出参数  : pusLeftLen - 定时器的剩余时间
 返 回 值  : NAS_MMC_TIMER_STATUS_ENUM_U8:定时器状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月26日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
*****************************************************************************/
VOS_UINT32  NAS_MM_QryTimerStatus(VOS_UINT8 ucTimerId)
{

    if ( MM_TIMER_STOP  != gstMmTimer[ucTimerId].ucTimerStatus )
    {
        return MM_TIMER_RUNNING;
    }
    else
    {
        return MM_TIMER_STOP;
    }

}

/*******************************************************************************
  Module:   Mm_TimerStart
  Function: MM使用定时器启动
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
*******************************************************************************/
VOS_VOID Mm_TimerStart( VOS_UINT8   ucTimerId )
{
    VOS_UINT32 ulResult;

    if ( MM_TIMER_STOP ==  gstMmTimer[ucTimerId].ucTimerStatus )
    {
        if ( MM_TIMER_T3212 == ucTimerId )
        {                                                                       /* 如果为T3212                              */
            if ( MM_CONST_NUM_0 != gstMmTimer[ucTimerId].ulTimerLen )
            {
                if ( MM_CONST_NUM_0 != NAS_MM_GetNetworkT3212RandLen())
                {
                    ulResult = Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           NAS_MM_GetNetworkT3212RandLen(),         /* 时长                                     */
                                           MM_TIMER_T3212,            /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           );                                   /* 创建支持消息的定时器                     */
                    if ( VOS_OK != ulResult )
                    {                                                           /* 创建失败                                 */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                        return;
                    }

                    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);
                }
                else
                {
                    ulResult = Mm_StartRelTimer(
                                           &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* 时长                                     */
                                           MM_TIMER_T3212,            /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           );                                                /* 创建支持消息的定时器                     */
                    if ( VOS_OK != ulResult )
                    {                                                           /* 创建失败                                 */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                        return;
                    }

                }

                gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;          /* 置Timer的启动标志                        */
                /*WUEPS_TRACE(MM_LOG_LEVEL_6,"\nMM StartTimer: %d\r",ucTimerId);*/
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStart:INFO: StartTimer: ", ucTimerId);
            }
        }
        else
        {
            if (MM_TIMER_PROTECT_SIGNALLING  == ucTimerId)
            {
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen = MM_TIMER_PROTECT_G_SIGNALLING_VALUE;
                }
                else
                {
                    gstMmTimer[MM_TIMER_PROTECT_SIGNALLING].ulTimerLen = MM_TIMER_PROTECT_W_SIGNALLING_VALUE;
                }
            }
            ulResult = Mm_StartRelTimer(  &gstMmTimer[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_MM,
                                           gstMmTimer[ucTimerId].ulTimerLen,         /* 时长                                     */
                                           (VOS_UINT32)ucTimerId,                       /* 消息队列的ID                             */
                                           gstMmTimer[ucTimerId].ulParam,               /* 消息地址                                 */
                                           gstMmTimer[ucTimerId].ucMode          /* 消息优先级                               */
                                           );                                             /* 创建支持消息的定时器                     */
            if ( VOS_OK != ulResult )                        /* 创建失败                                 */
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStart:WARNING: TIMER CREATE FAILURE!");
                return;
            }
            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_RUNNING;              /* 置Timer的启动标志                        */
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStart:INFO: StartTimer: ", ucTimerId);
        }
    }

}
/*****************************************************************************
 函 数 名  : NAS_MM_IsTimerIdInTimerList
 功能描述  : 判断某个定时器是否在定时器数组中
 输入参数  : ucTimerId   特定定时器
             ucTimerNum  定时器个数
             pucTimer    定时器数组
 输出参数  : 无
 返 回 值  : VOS_TRUE  表示在该数组中
             VOS_FALSE 表示不在该数组中

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月2日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_IsTimerIdInTimerList(
    VOS_UINT8                           ucTimerId,
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           ucIndex;

    for ( ucIndex = 0 ; ucIndex < ucTimerNum; ucIndex++ )
    {
        if ( ucTimerId == *(pucTimer + ucIndex) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_TimerStopExceptSpecialTimers
 功能描述  : MM模块停止所有除特定定时器外的所有定时器
 输入参数  : ucTimerNum  定时器个数
             pucTimer    定时器数组
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月2日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年10月16日
    作    者   : j00174725
    修改内容   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           i;

    /* Modified by w00176964 for V3R360_eCall项目, 2014-5-19, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by w00176964 for V3R360_eCall项目, 2014-5-19, end */
    {
        if ( VOS_TRUE == NAS_MM_IsTimerIdInTimerList(i, ucTimerNum, pucTimer) )
        {
            continue;
        }


        if ( MM_TIMER_STOP != gstMmTimer[i].ucTimerStatus )
        {
            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
            Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
            {                                                               /* 停止失败：已经停止或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
            }

            if (MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE == i)
            {
                NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);
            }

            gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", i);
        }
    }
}


/*******************************************************************************
  Module:   Mm_TimerStop
  Function: MM使用定时器停止
  Input:    VOS_UINT8       ucTimerId   Timer ID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2005.01.25  新版做成
      24. 日    期   : 2014年5月28日
          作    者   : z00234330
          修改内容   : covertity修改
      24. 日    期   : 2015年10月16日
          作    者   : j00174725
          修改内容   : DTS2015101603066
*******************************************************************************/
VOS_VOID Mm_TimerStop( VOS_UINT8   ucTimerId )
{
    VOS_UINT8   i;

    if ( MM_TIMER_STOP_ALL == ucTimerId )
    {
        /* 直接将CSFB 的保护定时器状态置为stop */
        NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
        for ( i = 0; i < MM_TIMER_MAX; i++ )
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
        {
            if ( MM_TIMER_STOP != gstMmTimer[i].ucTimerStatus )
            {
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_MM, i, &gstMmTimer[i].hTimer))
                {                                                               /* 停止失败：已经停止或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
                }

                gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;
                /* modified by z00234330 for coverity修改 2014-05-28 begin */
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", i);
                /* modified by z00234330 for coverity修改 2014-05-28 begin */
            }
        }
    }
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    else if ( ucTimerId < MM_TIMER_MAX )
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
    {
        if ( MM_TIMER_STOP != gstMmTimer[ucTimerId].ucTimerStatus )
        {
            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer))
            {                                                                   /* 停止失败：已经停止或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER STOP FAILURE!");
            }

            gstMmTimer[ucTimerId].ucTimerStatus = MM_TIMER_STOP;
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_TimerStop:INFO: StopTimer: ", ucTimerId);
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_TimerStop:WARNING: TIMER ID ERROR!");
    }

}
/*******************************************************************************
  MODULE   : Mm_ComAuthMsRej
  FUNCTION : 在MS侧拒绝鉴权的公共处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.01.27 新规作成
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_ComAuthMsRej()
{
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause = MM_AUTHEN_NO_CAUSE;
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);


    Mm_SndRrRelReq(RRC_CELL_BARRED);
    switch(g_MmGlobalInfo.ucState)
    {
    case WAIT_FOR_OUTGOING_MM_CONNECTION:
        Mm_TimerStart(MM_TIMER_T3230);
        break;
    case MM_CONNECTION_ACTIVE:
    case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthMsRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSaveProcAndCauseVal(
                                  MM_MM_MS_AUTH_FAIL_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
        break;
    case WAIT_FOR_NETWORK_COMMAND:
        break;
    case LOCATION_UPDATING_INITIATED:
        Mm_TimerStart(MM_TIMER_T3210);
        break;
    case LOCATION_UPDATE_REJECTED:
        break;
    case IMSI_DETACH_INITIATED:
        Mm_TimerStart(MM_TIMER_T3220);
        break;
    case PROCESS_CM_SERVICE_PROMPT:
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                          */
        /* " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );    */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComAuthMsRej:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);
        Mm_ComSaveProcAndCauseVal(
                                  MM_MM_MS_AUTH_FAIL_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComAuthMsRej:WARNING: g_MmGlobalInfo.ucState Abnormal");
        break;
    }
}

/*******************************************************************************
  MODULE   : Mm_ComTempIdJudge
  FUNCTION : 判断临时ID是否变化的公共处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : MM_TRUE  变化
             MM_FALSE 不变化
  NOTE     :
  HISTORY  :
  1.  张志勇   2005.01.06 新规作成
  2.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*******************************************************************************/

VOS_UINT8 Mm_ComTempIdJudge()
{
    VOS_UINT8 ucRet = MM_TRUE;

    if ( ( MM_MS_ID_TMSI_PRESENT ==
        ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
/*                                & MM_MS_ID_IMSI_PRESENT ) ) && */
                                & MM_MS_ID_TMSI_PRESENT ) ) &&
         ( MM_MS_ID_TMSI_PRESENT ==
        ( g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
/*                                & MM_MS_ID_IMSI_PRESENT ) ) ) */
                                & MM_MS_ID_TMSI_PRESENT ) ) )
    {
        if ( 0 == VOS_MemCmp(NAS_MML_GetUeIdTmsi(), g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi, NAS_MML_MAX_TMSI_LEN))
        {
            ucRet = MM_FALSE;
        }

    }
    return ucRet;
}
/*******************************************************************************
  MODULE   : Mm_Com_UsimAuthenticationCnfChgFormat
  FUNCTION : USIM_AUTHENTICATION_CNF格式转换
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   2005.02.03 新规作成
     2.  张志勇2005.02.03 指针参数修改为数组格式

     3.日    期  : 2013年7月22日
       作    者  : y00245242
       修改内容  : VoIP开发，适配新的USIM接口

     4.日    期  : 2013年8月12日
       作    者  : y00245242
       修改内容  : 优化函数
     5.日    期   : 2014年4月175日
       作    者   : s00246516
       修改内容   : DTS2014041700472:使用2G SIM卡，PAD形态上出现鉴权被网络拒绝
*******************************************************************************/
VOS_VOID Mm_Com_UsimAuthenticationCnfChgFormat(
                               USIMM_AUTHENTICATION_CNF_STRU *pUsimMsg
                               )
{
    VOS_UINT8                           i = 0;
    VOS_UINT8*                          pPointer;
    VOS_UINT8                           ucCause;
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-24, begin */
    USIMM_TELECOM_AUTH_CNF_STRU        *pstTELECnf = VOS_NULL_PTR;

    pstTELECnf = &(pUsimMsg->uCnfData.stTELECnf);

    /* UMTS AUTH SUCCESS or GSM AUTH SUCCESS */
    if ((USIMM_AUTH_UMTS_SUCCESS == pUsimMsg->enResult)
     || (USIMM_AUTH_GSM_SUCCESS == pUsimMsg->enResult))
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_SUCCESS;

        pPointer = pstTELECnf->aucAuthRes;

        if (pPointer[0] <= 4)
        {
            for ( i = 0; i < pPointer[0]; i++)
            {
                g_AgentUsimAuthCnf.aucResponse[i] = pPointer[i+1];
            }
            for ( ;i < 4; i++ )
            {
                g_AgentUsimAuthCnf.aucResponse[i] = 0xFF;
            }

            g_AgentUsimAuthCnf.ucExtRspLength = 0x0;
        }
        else
        {
            for ( i = 0; i < 4; i++)
            {
                g_AgentUsimAuthCnf.aucResponse[i] = pPointer[i+1];
            }

            if ( pPointer[0] > 16 )
            {
                g_AgentUsimAuthCnf.ucExtRspLength = 12;
            }
            else
            {
                g_AgentUsimAuthCnf.ucExtRspLength = pPointer[0] - 4;
            }

            for (i=0; i<g_AgentUsimAuthCnf.ucExtRspLength; i++)
            {
                g_AgentUsimAuthCnf.aucExtResponse[i] = pPointer[i+5];
            }
        }

        if (MM_ZERO == pstTELECnf->aucGsmKc[0]) /* 鉴权结果不包含 KC */
        {
            g_AgentUsimAuthCnf.ucKcLength = 0;
        }
        else /* 鉴权结果包含 KC, 读取 KC 值 */
        {
            for (i=0; i<8; i++)
            {
                /* skip the first length byte */
                g_AgentUsimAuthCnf.aucKc[i] = pstTELECnf->aucGsmKc[i+1];
            }

            /* get KC length from the first byte */
            g_AgentUsimAuthCnf.ucKcLength   = pstTELECnf->aucGsmKc[0];
        }

        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-8-12, begin */
        for (i=0; i<16; i++)
        {
            /* skip the first length byte */
            g_AgentUsimAuthCnf.aucCipheringKey[i] = pstTELECnf->aucCK[i+1];

            /* skip the first length byte */
            g_AgentUsimAuthCnf.aucIntegrityKey[i] = pstTELECnf->aucIK[i+1];
        }
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-8-12, end */
    }
    else if (USIMM_AUTH_MAC_FAILURE == pUsimMsg->enResult)
    {
        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = AGENT_AUTH_FAIL_MAC_CODE;
        ucCause = NAS_OM_MM_CAUSE_MAC_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE);
    }
    else if (USIMM_AUTH_SYNC_FAILURE == pUsimMsg->enResult)
    {
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-8-12, begin */
        g_AgentUsimAuthCnf.ucFailParaLength = 14;

        pPointer = pstTELECnf->aucAuts;
        if ( pstTELECnf->aucAuts[0] > 14 )
        {
            for ( i = 0; i < g_AgentUsimAuthCnf.ucFailParaLength; i++)
            {
                g_AgentUsimAuthCnf.aucFailPara[i] = pPointer[i+1];
            }
        }
        else
        {
            for ( i = 0; i < pstTELECnf->aucAuts[0]; i++)
            {
                g_AgentUsimAuthCnf.aucFailPara[i] = pPointer[i+1];
            }
            if ( pstTELECnf->aucAuts[0] < 14 )
            {
                for ( ;i < 14; i++ )
                {
                    g_AgentUsimAuthCnf.aucFailPara[i] = 0xFF;
                }
            }
        }
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-8-12, end */

        g_AgentUsimAuthCnf.ucCheckRst = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = AGENT_AUTH_FAIL_SQN;
        ucCause = NAS_OM_MM_CAUSE_SYNCH_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE);
    }
    else if (USIMM_AUTH_GSM_OTHER_FAILURE == pUsimMsg->enResult) /* GSM AUTH FAILURE */
    {
        g_AgentUsimAuthCnf.ucCheckRst     = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = USIM_GAS_AUTH_FAIL;
        ucCause = NAS_OM_MM_CAUSE_AUT_GSM_OTHER_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_OTHER_FAILURE);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Com_UsimAuthenticationCnfChgFormat:WARNING: ucResult Abnormal");
        /* WUEPS_ASSERT(0); */
        g_AgentUsimAuthCnf.ucCheckRst     = AGENT_AUTH_RST_FAILURE;
        g_AgentUsimAuthCnf.ucFailureCause = USIM_AUTH_FAIL_UNKNOWN;
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        NAS_MM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE);
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_FAILURE,
                        &ucCause, NAS_OM_EVENT_AUTH_FAIL_LEN);
        return ;
    }

    if(AGENT_AUTH_RST_FAILURE == g_AgentUsimAuthCnf.ucCheckRst)
    {
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_FAILURE,
                        &ucCause, NAS_OM_EVENT_AUTH_FAIL_LEN);
    }
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-24, end */
}

/*******************************************************************************
  MODULE   : Mm_ComNetModeChange
  FUNCTION : 网络模式变化处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746 2005.07.27 create
     2.  x51137 A32D08115 2007/01/03
     3.日    期   : 2010年12月01日
       作    者   : z00161729
       修改内容  : DTS2010111903590:LAI、RAI、CELL均未变只是网络模式发生改变，UE发起RAU或LAU，标杆不会

     4.日    期   : 2011年8月15日
       作    者   : zhoujun 40661
       修改内容   : 未进行LAU时，需要上报假流程给MMC模块
     5.日    期   : 2011年12月23日
       作    者   : w00167002
       修改内容   : DTS2011111901055:假流程上报原因值由NAS_MML_REG_FAIL_CAUSE_NULL
                    修改为NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                    修改原因:在ON PLMN状态，收到此假流程消息，若原因值小于
                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE，则可能发起搜网。
     6.日    期   : 2012年02月29日
       作    者   : l00130025
       修改内容   : DTS2012022206186:不发起LAU,而注册成功时，需要同步注册状态给AS
     7.日    期   : 2012年03月17日
       作    者   : s46746
       修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程

     8.日    期   : 2012年05月22日
       作    者   : z40661
       修改内容   : DTS2012052105040:回到原小区,MM状态未迁移到正常服务
     9.日    期   : 2012年08月21日
       作    者   : l65478
       修改内容   : DTS2012082003615:出服务区后3212超时重进服务区没有发起LU
    10.日    期   : 2012年11月07日
       作    者   : t00212959
       修改内容   : DTS2011110100336,紧急呼先呼叫后做LAU
    11.日    期   : 2012年11月17日
       作    者   : l65478
       修改内容   : DTS2012111508506,进入正常服务状态后MM没有启动T3212
    12.日    期   : 2013年07月05日
       作    者   : l65478
       修改内容   : DTS2013070408274:MM进入NORMAL SERVICE后没有处理缓冲的CC消息
    13.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
    14.日    期   : 2014年9月17日
       作    者   : w00167002
       修改内容   : DTS2014091001010:在小区A(II)上注册成功，指定搜小区B(I)被拒13后，
                    ANYCELL驻留到小区B上，再指定搜小区A(II）,没有发起CS域的注册。
    15.日    期   : 2014年9月17日
       作    者   : w00167002
       修改内容   : DTS2015010504216:在GSM下，CS ONLY,触发LAU。网络模式I<->II间
                    网络模式变换，相同LAC，不需要触发LAU.
    16.日    期   : 2015年3月20日
       作    者   : w00167002
       修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
*******************************************************************************/
VOS_VOID Mm_ComNetModeChange()
{
    VOS_UINT8                               ucProcessLu;

    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    ucProcessLu     = MM_TRUE;

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        if ( MM_TRUE
         == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
        {
            g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
            return;
        }

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        if (VOS_FALSE == NAS_MM_IsLauNeeded_NetModeChange())
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        {
            ucProcessLu = MM_FALSE;   /*收到系统消息只是小区的网络模式改变无需发起LU*/


            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);



            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
             if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
               && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
               && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
             {

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
             }

            g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        }
    }
    else if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        if (VOS_FALSE == NAS_MM_IsLauNeeded_NetModeChange())
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        {
            ucProcessLu = MM_FALSE;   /*收到系统消息只是小区的网络模式改变无需发起LU*/

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


        }
    }
    else
    {
    }

    if (MM_TRUE == ucProcessLu)
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);

    }

}

/*******************************************************************************
  Module   : MM_Update_Revision_Level
  Function : 更新空口消息中的ClassMark IE 的 revision level参数
  Input    : classmark 的第一个字节
  Output   : 无
  NOTE     : 无
  Return   : 无。
  History  :
    1. 欧阳飞  2009.06.19  新规作成
*******************************************************************************/
VOS_VOID MM_Update_Revision_Level(VOS_UINT8 *pucClassMark)
{
    VOS_INT8                    cVersion;
    VOS_UINT8                   ucRevisionLevel;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    /* R99以前版本，上报 revision level 为 GSM PHASE 2*/
    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_GSM_PH2;
    }
    else
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }

    *pucClassMark &= 0x9f;
    *pucClassMark |= (VOS_UINT8)(ucRevisionLevel << 5);

    return;
}

/*******************************************************************************
  Module   : MM_Fill_IE_ClassMark1
  Function : 填写空口消息中的ClassMark1 IE (V)
  Input    : VOS_VOID *pAddr  填写ClassMark1 IE的地址
  Output   : 无
  NOTE     : 无
  Return   : 无。
  History  :
    1. 欧阳飞  2009.05.10  新规作成
    2. 日    期   : 2010年09月07日
       作    者   : w00167002
       修改内容   : 问题单号：DTS2010090101367,RRC CONN setup cmp消息中Class mark2 填写内容不正确
    3. 日    期   : 2011年07月14日
       作    者   : z00161729
       修改内容   : V7R1 phase II全局变量调整修改
    4.日    期   : 2013年4月7日
      作    者   : z00161729
      修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
    5.日    期   : 2014年06月04日
      作    者   : s00217060
      修改内容   : 不支持GSM时，classmark1中的ES IND => 0, A5/1 => 1
*******************************************************************************/
VOS_VOID MM_Fill_IE_ClassMark1(
                               VOS_UINT8 *pucClassMark1                           /* 填写ClassMark1 IE的首地址                */
                              )
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    GSM_BAND_SET_UN                     unSysCfgSetGsmBand;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

    VOS_UINT8                           ucBandNum;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstUserSetBand  = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstCurrBand     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;

    enCurrNetRat    = NAS_MML_GetCurrNetRatType();
    pstMsCapability = NAS_MML_GetMsCapability();
    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    pstCurrBand     = NAS_MML_GetCurrBandInfo();
    *pucClassMark1 = pstMsCapability->ucClassmark1;

    NAS_MML_Update_Revision_Level(pucClassMark1);

    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_GSM))
    {

        /* W only */
        /* bi8 ES IND => 0, A5/1 => 1, RF power capability => 111 */
        *pucClassMark1 &= 0xE0;
        *pucClassMark1 |= 0x0F;
    }
    else
    {
        /*获取当前的小区网络频段*/
        unSysCfgSetGsmBand.ulBand = pstCurrBand->unGsmBand.ulBand;
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
           )
        {
            unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;
        }

        /*根据当前驻留的频段填写RF power capability*/

        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
        if ((VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1800)
         || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1900))
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
        {
           /*power class 1*/
            *pucClassMark1 &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
            *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_CLASS1;
        }
        else /* 其它频段 */
        {
            /*power class 4*/
            *pucClassMark1 &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
            *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_CLASS4;
        }

        /* 如果当前网络驻留在W下,且用户设置为多频段的处理 */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
           )
        {
            /* 获取用户设置的可在小区内驻留的频段 */
            NAS_MML_GetSupportBandNum(unSysCfgSetGsmBand.ulBand, &ucBandNum);

            /*如果支持多频段或者不支持任何频段，设置RF power capability => 111*/
            if ((ucBandNum > 1) || (0 == ucBandNum))
            {
                *pucClassMark1 |= MM_CLASSMARK_RF_POWER_CAP_MASK;
            }
        }
    }
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_GetSupportBandNum
 功能描述  : 根据输入参数ulBand来判读该参数变量中有多少个bit值为1，
             此函数可用于判断当前所处频段是否为多频段。
 输入参数  : VOS_UINT32 ulBand
 输出参数  : VOS_UINT8 &ucBandNum，用来取得ulBand中的bit值为1的个数，即频段个数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月26日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年3月5日
    作    者   : w00176964
    修改内容   : DTS201212345678:增加BAND6,BAND19的支持

*****************************************************************************/
VOS_VOID NAS_MM_GetSupportBandNum(VOS_UINT32 ulBand, VOS_UINT8 *pucBandNum)
{
    /* ucIndicator用来进行移位指示 */
    VOS_UINT8                           ucIndicator;

    /* ucTotalLen表示用来参数usBand的总bit位数 */
    VOS_UINT8                           ucTotalLen;

    /* ucBandNum用来记录bit值为1的个数，并作为函数的返回值 */
    *pucBandNum = 0;
    ucIndicator = 0;
    ucTotalLen  = sizeof(ulBand) * 8;

    /* 通过循环移位计算ulBand中的bit值为1的总个数，并保存到ucBandNum中 */
    while (ucIndicator < ucTotalLen)
    {
        if ((ulBand>>ucIndicator) & 0x01)
        {
            (*pucBandNum)++;
        }

        ucIndicator++;
    }

    return;
}

/*******************************************************************************
  Module   : MM_Fill_IE_ClassMark2
  Function : 填写空口消息中的ClassMark2 IE (V)
  Input    : VOS_VOID *pAddr  填写ClassMark2 IE的地址
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞  2009.05.10  新规作成
    2. 日    期   : 2010年09月07日
       作    者   : w00167002
       修改内容   : 问题单号：DTS2010090101367,RRC CONN setup cmp消息中Class mark2 填写内容不正确
   3. 日    期   : 2010年11月1日
      作    者   : 欧阳飞
      修改内容  : 问题单号DTS2010102903975:RRC conn setup cmp消息中classmark2的RF power参数赋值不对
   4. 日    期   : 2010年12月22日
      作    者   : z00161729
      修改内容  : DTS2010120900138:只支持900P频段且驻留900P情况下，classmark2的FC应该上报为0
   5.日    期   : 2011年07月14日
      作    者   : z00161729
      修改内容   : V7R1 phase II全局变量调整修改,替换classmark2
   6. 日    期   : 2011年09月14日
      作    者   : f00179208
      修改内容  : DTS2011062803354:CM Service Request消息中A53消息填充有误
   7. 日    期   : 2012年11月06日
      作    者   : t00212959
      修改内容  : DTS2012101005815:不支持G就不填写GSM能力
   8. 日    期   : 2012年11月06日
      作    者   : t00212959
      修改内容   : DTS2013022703646:填写ClassMark2 IE在MML完成，以便L调用
*******************************************************************************/
VOS_VOID MM_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2                           /* 填写ClassMark2 IE的首地址                */
)
{
    NAS_MML_Fill_IE_ClassMark2(pClassMark2);

    return;
}

/*******************************************************************************
  MODULE   : MM_ComGetChanMode
  FUNCTION : GSM网络下，转换信道模式
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746 2006.11.06 create for A32D06442
     2.日    期  : 2008年12月2日
       作    者  : s62952
       修改内容  : 根据问题单A32D07110修改

     3.日    期   : 2012年2月9日
       作    者   : z40661
       修改内容   : 支持AMR-WB
*******************************************************************************/
MMCC_CHANNEL_MODE_ENUM_U32 MM_ComGetChanMode(NAS_RR_CHANNEL_MODE_ENUM_U8 enChanMode)
{
    MMCC_CHANNEL_MODE_ENUM_U32   enMmCcChanMode;

    switch(enChanMode)
    {
    case RR_CHAN_MOD_SINGAL_ONLY:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    case RR_CHAN_MOD_FR:
        enMmCcChanMode = MMCC_CHAN_MOD_FR;
        break;
    case RR_CHAN_MOD_EFR:
        enMmCcChanMode = MMCC_CHAN_MOD_EFR;
        break;
    case RR_CHAN_MOD_AFS:
        enMmCcChanMode = MMCC_CHAN_MOD_AMR;
        break;
    case RR_CHAN_MOD_CSD_2400:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_2400;
        break;
    case RR_CHAN_MOD_CSD_4800:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_4800;
        break;
    case RR_CHAN_MOD_CSD_9600:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_9600;
        break;
    case RR_NAS_DATA_CSD_14400:
        enMmCcChanMode = MMCC_CHAN_MOD_DATA_14400;
        break;
    case RR_CHAN_MOD_HR:
        enMmCcChanMode = MMCC_CHAN_MOD_HR;
        break;
    case RR_CHAN_MOD_AHR:
        enMmCcChanMode = MMCC_CHAN_MOD_AHR;
        break;
    case RR_CHAN_MOD_H24:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    case RR_CHAN_MOD_H48:
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;

    case RR_CHAN_MOD_WFS:
        enMmCcChanMode = MMCC_CHAN_MOD_AMRWB;
        break;

    default :
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                            "MM_ComGetChanMode:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
        enMmCcChanMode = MMCC_CHAN_MOD_SIG_ONLY;
        break;
    }

    return enMmCcChanMode;
}

/*******************************************************************************
  MODULE   : Mm_ComSetMmState
  FUNCTION : 设定MM状态
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.日    期  : 2009年2月10日
       作    者  :
       修改内容  :
     2.日    期   : 2009年03月12日
       作    者   : ouyangfei id:00132663
       修改内容   : 问题单AT2D09683,丢网时，GMM上报服务状态异常导致MMC没有发起搜网。
     3.日    期   : 2010年07月29日
       作    者   : l65478
       修改内容   : 问题单DTS2010070502239,在设置成PS only后，发起CS呼叫，然后设置成CS ONLY，MM没有发起注册
     4.日    期   : 2010年08月21日
       作    者   : s46746
       修改内容   : 根据问题单号：DTS2010080502037，注册状态改变通过MM IDLE状态决定
     5.日    期   : 2012年9月07日
       作    者   : l00171473
       修改内容   : DTS2012081701006, 添加GMM状态的可维可测消息
     6.日    期   : 2013年05月08日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     7.日    期   : 2014年04月29日
       作    者   : y00245242
       修改内容   : eCall项目修改
     8.日    期   : 2014年6月13日
       作    者   : w00242748
       修改内容   : DSDS 新特性
     9.日    期   : 2015年6月01日
       作    者   : j00174725
       修改内容   : DTS2015053000044
    10.日    期   : 2015年10月16日
       作    者   : j00174725
       修改内容   : DTS2015101603066
*******************************************************************************/
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
VOS_VOID Mm_ComSetMmState(NAS_MM_STATE_ENUM_UINT8 ulState)
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */
{


#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MM_NotifySessionAccordingStateChg(g_MmGlobalInfo.ucState, ulState);
#endif

    if (( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (MM_IDLE_NORMAL_SERVICE == ulState))
    {
        g_MmGlobalInfo.ucState = MM_IDLE_LIMITED_SERVICE;
        g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_ComSetMmState:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
    else
    {
        g_MmGlobalInfo.ucState = ulState;
    }

    NAS_MM_LogMmStateInfo(g_MmGlobalInfo.ucState);

    switch(ulState)
    {
        case MM_STATE_NULL:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_IDLE_NO_IMSI:
        case MM_IDLE_NO_CELL_AVAILABLE:
            /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, begin */

            /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, end */
            break;

        case MM_CONNECTION_ACTIVE:
            /* 停止定时器 */
            Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

            NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

            /* 通知接入层TRANSACTION状态 */
            NAS_MM_SndTransactionStatusNotify(RRMM_TRANSACTION_CONNECTION_EST_SUCC);

            NAS_MM_ClearErrorLogInfo();

            /* 与收到call status nty(succ)/ss status nty(succ)处理相同 */
            NAS_MM_UpdateCallStatus_RcvCallStatusNty(MNCC_CALL_STATUS_SETUP_SUCC);
            NAS_MM_UpdateSsStatus_RcvSsStatusNty(SSA_SS_STATUS_SETUP_SUCC);

            break;

        default:
            break;
    }


    return;
}

/*****************************************************************************
 函 数 名  : MM_LocalEndAllCalls
 功能描述  : 本地释放所有的呼叫
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月02日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MM_LocalEndAllCalls(VOS_VOID)
{
    Mm_RcvRrmmRelInd();
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    return;
}
/*******************************************************************************
  MODULE   : Mm_GetServiceStatus
  FUNCTION : 获取当前的服务状态和原因值
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.日    期  : 2009年1月16日
       作    者  :
       修改内容  :
*******************************************************************************/
VOS_VOID Mm_GetServiceStatus(VOS_UINT32 *pulCsServiceStatus, VOS_UINT32 *pulCsCause)
{
    *pulCsServiceStatus = g_MmGlobalInfo.ucMmServiceState;
    *pulCsCause = g_MmGlobalInfo.usCauseVal;
}

/***********************************************************************
 *  MODULE   : Mm_ComCheckDelayDetach
 *  FUNCTION : PS ONLY下，CS业务结束后进行Detach
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 *     1.  s46746        09-06-23    新版作成
     2.日    期   : 2010年07月29日
       作    者   : l65478
       修改内容   : 问题单DTS2010070502239,在设置成PS only后，发起CS呼叫，然后设置成CS ONLY，MM没有发起注册
     3.日    期   : 2011年03月01日
       作    者   : A00165503
       修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                    服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
     6.日    期   : 2012年03月03日
       作    者   : s62952
       修改内容   : BalongV300R002 Build优化项目
     7.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     8.日    期   : 2014年05月21日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目:PS ONLY也需要支持ecall的回呼,因此不做CS的detach
     9.日    期   : 2014年6月13日
       作    者   : w00242748
       修改内容   : DSDS 新特性
     10.日    期   : 2015年6月16日
       作    者   : z00161729
       修改内容   : 24008 23122 R11 CR升级项目修改
 ************************************************************************/
VOS_VOID Mm_ComCheckDelayDetach()
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-21, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;

    enCallMode   = NAS_MML_GetCallMode();
#endif
    if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
#if (FEATURE_ON == FEATURE_ECALL)
     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-21, end */
    {
        Mm_TimerStop(MM_TIMER_T3212);

        if (MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
        {
            /*Detach CS*/
            if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)))
            {
                Mm_SndMmcDeRegisterInit();
            }
            else if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* 填写消息,发送消息                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* 启动保护TIMER                            */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Mm_ComCheckDelayDetach:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
            }
            else
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Mm_ComCheckDelayDetach:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
        }
        else if ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
              || (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState))
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                   "Mm_ComCheckDelayDetach:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

        }
        else
        {
        }

        /*设置attach not allow 标志*/
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }
}

/***********************************************************************
 *  MODULE   : Mm_ComIsCsServExist
 *  FUNCTION : 判断当前CS域是否有业务存在,包括SS,SMS,CC
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_BOOL
 *  NOTE     :
 *  HISTORY  :
 *     1.  z40661        09-07-22    新版作成 AT2D12429
       2.日    期   : 2012年09月01日
         作    者   : s46746
         修改内容  : DTS2012090405619:DCM外场测试,联合RAU过程中响应寻呼被网络abort
 ************************************************************************/
VOS_UINT32 Mm_ComJudgeCsServExist(VOS_VOID)
{
    VOS_UINT32                          ulRet = MM_CS_SERV_NONE_EXIST;

    if(  ( MM_CONST_NUM_7 <
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_CONST_NUM_15 >
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId)
       && ( MM_TRUE ==
       g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg ) )
    {
        if ( MMCC_EMERGENCY_CALL ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
        {
            ulRet = MM_CS_SERV_EMERGENCY_CALL_EXIST;
        }
        else
        {
            ulRet = MM_CS_SERV_NORMAL_CALL_EXIST;
        }
    }

    else if ( MM_TRUE ==
         g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
    {
        ulRet = MM_CS_SERV_SS_EXIST;
    }

    else if ( MM_TRUE ==
         g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
    {
        ulRet = MM_CS_SERV_SMS_EXIST;
    }
    else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
    {
        ulRet = MM_CS_SERV_MT_EXIST;
    }
    else
    {
        ;
    }

    return ulRet;
}




/*****************************************************************************
 函 数 名  : NAS_MM_IsExistBufferService
 功能描述  : 判断当前是否存在有缓冲的业务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月8日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsExistBufferService(VOS_VOID)
{
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : MM_GetSignalingStatus
 功能描述  : 判断当前是否允许进行HPLMN搜索
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年10月10日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2010年03月20日
    作    者   : l65478
    修改内容   : 问题单号：AT2D17070,呼叫中止指定搜索时，MMC后续没有发起搜网

*****************************************************************************/
VOS_UINT8  MM_GetSignalingStatus(VOS_VOID)
{
    /* 因为MMC和MM间信令连接信息的通知是采用异步消息，所以在发起PLMN搜索前需要判断MM的当前状态。
    在注册或者去注册过程中,不允许发起搜网 */
    if((WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_RR_CONNECTION_IMSI_DETACH == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ == g_MmGlobalInfo.ucState)
        || (WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF == g_MmGlobalInfo.ucState))
    {
        return MMC_MM_SIGNALING_STATUS_PRESENT;
    }
    else if (VOS_TRUE == NAS_MM_IsExistBufferService())
    {
        return MMC_MM_SIGNALING_STATUS_PRESENT;
    }
    else
    {
        return MMC_MM_SIGNALING_STATUS_ABSENT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_CheckIfMmIsEstablishRRConnection
 功能描述  : 判断当前MM是否正在建链
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月20日
    作    者   : o00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  NAS_MM_CheckIfMmIsEstablishRRConnection()
{
    /* 因为MMC和MM间信令连接信息的通知是采用异步消息，所以在发起PLMN搜索前需要判断MM的当前状态。
    在注册或者去注册过程中,不允许发起搜网 */
    if( (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_RR_CONNECTION_IMSI_DETACH == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF == g_MmGlobalInfo.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/* 废弃函数 */

/*****************************************************************************
 函 数 名  : NAS_MM_RetryCurrentProcedureCheck
 功能描述  : 判断是否需要重新发起当前流程
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月26日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_RetryCurrentProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.4.4.9 f1/4.5.1.2 a1:
      a.1) RR connection failure in Iu mode (i.e. RRC connection release) with,
      for example, cause "Normal", "User inactivity" or "Directed signalling
      connection re-establishment" (see 3GPP TS 25.331 [32c] and 3GPP TS 44.118
      [111])
      The MM connection establishment procedure shall be initiated again, if
      the following conditions apply:
      i) The original MM connection establishment was initiated over an existing
      RRC connection; and
      ii) No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS) mess-
      ages relating to the CS signalling connection (e.g. CS authentication
      procedures, see subclause 4.3.2), were received after the CM SERVICE REQU-
      EST message was transmitted.
      NOTE 1:  The RRC connection release cause that triggers the re-initiation
      of the MM connection establishment procedure is implementation specific.*/

    VOS_UINT8                           ucRst;

    ucRst = VOS_FALSE;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (   (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            && (VOS_TRUE == g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn)
            && (VOS_FALSE
                    == g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg)
            && (g_MmGlobalInfo.ucProc
                    == g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc))
        {
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT           == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T314_EXPIRED            == ulRelCause) )
            {
                ucRst = VOS_TRUE;
            }
        }
    }

    /* 判断完毕后，清除MM链路控制变量 */
    NAS_MM_ClearMmLinkCtrlStru();

    return ucRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsRrRelCauseNeedRetryLau
 功能描述  : 通过连接释放原因判断是否需要重新发起Lau
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2015年1月28日
    作    者   : w00167002
    修改内容   : DTS2015011400748:在G下RL FAILURE，后FR,导致上下配合异常。修改为
                G上报RRC_REL_CAUSE_G_RL_FAIL原因值，这样NAS就不发起CC 重建。
*****************************************************************************/
VOS_UINT8 NAS_MM_IsRrRelCauseNeedRetryLau(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
)
{
    VOS_UINT8                           ucRst;

    ucRst = VOS_FALSE;  /* [false alarm]:ucRst作为初始化值 */

    switch ( ulRelCause )
    {
        case RRC_REL_CAUSE_RR_UNSPEC :
        case RRC_REL_CAUSE_NAS_DATA_ABSENT :
        case RRC_REL_CAUSE_RRC_ERROR :
        case RRC_REL_CAUSE_RL_FAILURE :
        case RRC_REL_CAUSE_OTHER_REASON :
        case RRC_REL_CAUSE_NO_RF :
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            ucRst = VOS_FALSE;
            break;

        default:
            ucRst = VOS_TRUE;
            break;
    }

    return ucRst;
}



/*****************************************************************************
 函 数 名  : NAS_MM_RetryMmConnectionProc
 功能描述  : 重新发起当前的MM CONNECTION流程
 输入参数  : VOS_UINT8                           ucMMConnEstingPD
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月27日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RetryMmConnectionProc(
    VOS_UINT8                           ucMMConnEstingPD
)
{
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl;

    switch (ucMMConnEstingPD)
    {
        case MM_IE_PD_CALL_CONTROL:
            ucMmConnCtrl = MM_CONN_CTRL_CC;
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:
            ucMmConnCtrl = MM_CONN_CTRL_SS;
            break;
        case MM_IE_PD_SMS_MSG:
            ucMmConnCtrl = MM_CONN_CTRL_SMS;
            break;
        default:
            ucMmConnCtrl = MM_CONN_CTRL_BUTT;
            NAS_WARNING_LOG1(WUEPS_PID_MM, "NAS_MM_RetryMmConnectionProc: unexpected ucMMConnEstingPD received: ", ucMMConnEstingPD);
            break;
    }

    if (MM_CONN_CTRL_BUTT != ucMmConnCtrl)
    {
        NAS_MM_EstMmConnection(ucMmConnCtrl);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetPDFromConnCtrlEnum
 功能描述  : 根据NAS_MM_CONN_CTRL_ENUM枚举类型获取相应的MMConnEstingPD
 输入参数  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
 输出参数  : UINT8                               *pucMMConnEstingPD
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月27日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_GetPDFromConnCtrlEnum(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucMMConnEstingPD
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            *pucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;
            break;
        case MM_CONN_CTRL_SS:
            *pucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;
            break;
        case MM_CONN_CTRL_SMS:
            *pucMMConnEstingPD = MM_IE_PD_SMS_MSG;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_GetPDFromConnCtrlEnum: unexpected ucMmConnCtrl.");
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_EstMmConnection
 功能描述  : 发起建立MM CONNECTION
 输入参数  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年1月27日
   作    者   : o00132663
   修改内容   : 新生成函数
 2.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化

*****************************************************************************/
VOS_VOID NAS_MM_EstMmConnection(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize;
    VOS_UINT8                           *pucCmSvcReq;
    VOS_UINT8                           ucCMSvcType;
    VOS_UINT32                          ulRrcEstCause;

    /* 缓存消息，在连接建立过程中如果发生重选，如果LU改变，在LU结束后可以进行重传 */
    NAS_MM_UpdateConnCtrlInfo(ucMmConnCtrl);

    NAS_MM_GetCMSvcType(ucMmConnCtrl, &ucCMSvcType);

    /* 填充CM SERVICE REQUEST结构体             */
    Mm_ComFillInCMSncReq(ucCMSvcType, MM_FALSE, &stCmSvcReq);

    /* 填充CM SERVICE REQUEST 消息              */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&stCmSvcReq, &usMsgSize);
    if (VOS_NULL_PTR == pucCmSvcReq)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_EstMmConnection:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;
    }
    else
    {
        NAS_MM_GetRrcEstCause(ucMmConnCtrl, &ulRrcEstCause);

        Mm_SndRrEstReq(ulRrcEstCause, MM_FALSE, usMsgSize, pucCmSvcReq);

        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
    }

    NAS_MM_GetPDFromConnCtrlEnum(ucMmConnCtrl, &g_MmGlobalInfo.ucMMConnEstingPD);

    /* 启动保护TIMER                            */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    /* 通知MMC，CS域的业务已经启动              */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_EstMmConnection:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsCcServiceNeedTriggerPlmnSearchNoRf
 功能描述  : mm收到cc业务是否需要通知mmc触发搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年09月09日
    作    者   : c00318887
    修改内容   : for 预置频点搜网优化

*****************************************************************************/
VOS_UINT32 NAS_MM_IsCcServiceNeedTriggerPlmnSearch(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* 紧急呼叫时需要触发搜网 */
    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {
        return VOS_TRUE;
    }

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    /* 普通呼叫且卡有效no rf时需要触发搜网 */
    if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
     && (VOS_TRUE == ucSimCsRegStatus)
     && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType))
    {
        return VOS_TRUE;
    }
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_UpdateConnCtrlInfo
 功能描述  : 更新MM Connection控制信息
 输入参数  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月27日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_UpdateConnCtrlInfo(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl
)
{
    g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ucFlg = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucRat = NAS_MML_GetCurrNetRatType();
    NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = g_MmCcEstReq.ulCallPri;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = g_MmCcEstReq.ulCallType;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallMode
                = g_MmCcEstReq.ulCallMode;

            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucMMConnEstingTI
                = (VOS_UINT8)g_MmCcEstReq.ulTransactionId;

            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucEstingCallTypeFlg
                    = MM_FALSE;
            }
            else
            {
                g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucEstingCallTypeFlg
                    = MM_TRUE;
            }
            break;

        case MM_CONN_CTRL_SS:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSsEstReq.ulTi;

            break;

        case MM_CONN_CTRL_SMS:
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[ucMmConnCtrl].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_GetCMSvcType
 功能描述  : 获取当前进行的MM CONNECTION流程的CM Service 类型
 输入参数  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
 输出参数  : VOS_UINT8                           *pucCmSrvType
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月27日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_GetCMSvcType(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT8                           *pucCmSrvType
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                *pucCmSrvType = MM_IE_CM_SVC_TYPE_MO_CALL_EST;
            }
            else
            {
                *pucCmSrvType = MM_IE_CM_SVC_TYPE_EMG_CALL_EST;
            }
            break;

        case MM_CONN_CTRL_SS:
            *pucCmSrvType = MM_IE_CM_SVC_TYPE_SS_ACT;
            break;

        case MM_CONN_CTRL_SMS:
            *pucCmSrvType = MM_IE_CM_SVC_TYPE_SMS;
            break;

        default:
            *pucCmSrvType = 0;
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_GetRrcEstCause
 功能描述  : 获取建立RRC连接的原因值
 输入参数  : NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
 输出参数  : VOS_UINT32                          *pulRrcEstCause
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月27日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_GetRrcEstCause(
    NAS_MM_CONN_CTRL_ENUM_UINT8         ucMmConnCtrl,
    VOS_UINT32                          *pulRrcEstCause
)
{
    switch (ucMmConnCtrl)
    {
        case MM_CONN_CTRL_CC:
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {
                *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            }
            else
            {
                *pulRrcEstCause = RRC_EST_CAUSE_EMERGENCY_CALL;
            }
            break;

        case MM_CONN_CTRL_SS:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;

        case MM_CONN_CTRL_SMS:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;
            break;

        default:
            *pulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_UpdateMmLinkCtrlStru
 功能描述  : 更新MM连接释放控制结构
 输入参数  : NAS_MM_COM_PROCEDURE_ENUM_UINT8     ucCurrentProc
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月3日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的全局变量
*****************************************************************************/
VOS_VOID NAS_MM_UpdateMmLinkCtrlStru(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc = g_MmGlobalInfo.ucProc;
    g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    /* 检查当前流程是否在已建立的RRC连接上发起 */
    if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
    {
        g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    }
    else
    {
        g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ClearMmLinkCtrlStru
 功能描述  : 清除MM链路控制管理相关变量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月9日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ClearMmLinkCtrlStru( VOS_VOID )
{
    g_MmGlobalInfo.stMmLinkCtrl.ucCurrentProc = MM_NULL_PROC;
    g_MmGlobalInfo.stMmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ClearConnCtrlInfo.g_MmGlobalInfo
 功能描述  : 清除MM ConnCtrlInfo全局变量的标志位
 输入参数  : VOS_UINT8 ucMMConnEstingPD - 当前建链的业务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年5月15日
    作    者   : w00167002
    修改内容   : DTS2013051408623:更新CS BUFFER STATUS时候，孙习波检视直接更新
                 缓存不存在存在风险NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE)，
                 修改为调用NAS_MM_UpdateCsServiceBufferStatusFlg函数来更新缓存的
                 业务状态。

*****************************************************************************/
VOS_VOID NAS_MM_ClearConnCtrlInfo(VOS_UINT8 ucMMConnEstingPD)
{
    if(MM_IE_PD_CALL_CONTROL == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else if(MM_IE_PD_SMS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else if(MM_IE_PD_NON_CALL_RLT_SS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_FALSE;
    }
    else
    {
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-9-5, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ClearConnCtrlInfoExcEmgCall
 功能描述  : 清除MM ConnCtrlInfo全局变量的标志位,紧急呼叫不清除
 输入参数  : VOS_UINT8 ucMMConnEstingPD - 当前建链的业务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月4日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ClearConnCtrlInfoExcEmgCall(VOS_UINT8 ucMMConnEstingPD)
{
    if ((MM_IE_PD_CALL_CONTROL == ucMMConnEstingPD)
     && (MMCC_EMERGENCY_CALL != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType))
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
        return;
    }

    if (MM_IE_PD_SMS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
        return;
    }

    if (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucMMConnEstingPD)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-9-5, end */

/*****************************************************************************
 函 数 名  : NAS_MM_ProcEstCnfSuccessCauseAtState12
 功能描述  : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下，收到RRMM_EST_CNF(成功)的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年7月23日
    作    者   : w00167002
    修改内容   : DTS2013072205858:2g rf 13.2用例测试异常。
                  收到寻呼时候，网侧不下发SETUP,测试底层性能指标。
                  T3240超时后，释放了当前链接，导致用例测试失败。
  3.日    期   : 2014年03月04日
    作    者   : z00161729
    修改内容   : DTS2014022800234:被叫mm收到paging会设置cs业务信令连接存在，但查询^usersrvstate时返回无cs业务，syscfgex设置失败回复存在cs业务，不一致
  4.日    期   :2015年3月13日
    作    者   :n00269697
    修改内容   :CHR 优化项目
*****************************************************************************/
VOS_VOID NAS_MM_ProcEstCnfSuccessCauseAtState12(VOS_VOID)
{
    VOS_UINT32                          ulIsTestCard;
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* 是否支持cs语音业务包括普通语音和vp业务，VOS_TRUE:支持cs语音业务；VOS_FALSE:不支持cs语音业务*/

    ulIsTestCard          = NAS_USIMMAPI_IsTestCard();
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    if ( (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
       ||(NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
       ||(NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI))
    {
        Mm_TimerStart(MM_TIMER_T3230);
        Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:NORMAL: STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION");
    }
    else
    {
        /* 由网侧寻呼引起的连接建立                 */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");

        NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

        if ( (VOS_TRUE  == ulIsTestCard)
          && (VOS_FALSE == ucSupportCsServiceFlg) )
        {
            gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_MAX_VALUE;
            Mm_TimerStart( MM_TIMER_T3240 );
            gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
        }
        else
        {
            /*A32D12629==>在此期间可能发起频率重定义，时间为50秒，因此增加定时器长度*/
            gstMmTimer[MM_TIMER_T3240].ulTimerLen += 50000;
            Mm_TimerStart( MM_TIMER_T3240 );
            gstMmTimer[MM_TIMER_T3240].ulTimerLen -= 50000;
        }
        /*<==A32D12629*/
    }

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
    NAS_INFO_LOG(WUEPS_PID_MM, "NAS_MM_ProcEstCnfSuccessCauseAtState12:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_InformCmLayerEstFail
 功能描述  : 通知上层应用模式，建链失败
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  3.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_InformCmLayerEstFail(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    enMmCcRelCause  = NAS_MM_ConvertEstCnfRsltToMmCcRelCause(ulResult);

    if ( NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {
        /* CC发起的RR连接的建立, 通知CC建立失败             */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                        enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {
        /* SS发起的RR连接的建立 ，通知SS,MM连接建立失败      */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {
        /* SMS发起的RR连接的建立 ,通知SMS,MM连接建立失败      */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                       enMmCcRelCause);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }
    else
    {
        /* 没有正在建立的MM连接，即被叫             */
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcEstCnfOtherFailCauseAtState12
 功能描述  : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下，收到RRMM_EST_CNF(失败,非特定原因值)的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  3.日    期   : 2013年09月03日
    作    者   : l65478
    修改内容   : DTS2013041602825:CSFB连接建立失败后没有发起LU
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
  5.日    期   :2015年3月10日
    作    者   :n00269697
    修改内容   :CHR优化项目，删除CHR错误的记录点CS PAGING FAIL
*****************************************************************************/
VOS_VOID NAS_MM_ProcEstCnfOtherFailCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    VOS_UINT8               ucTiValidFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_InformCmLayerEstFail(ulResult);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_ProcEstCnfOtherFailCauseAtState12:NORMAL: ucState = ",
                    g_MmGlobalInfo.ucState);

    enMmCcRelCause  = NAS_MM_ConvertEstCnfRsltToMmCcRelCause(ulResult);

    /* 因为函数Mm_ComChkLu有是否当前在连接态的判断,所以在连接建立失败时,
       不能直接调用此函数,而要调用NAS_MM_CheckLuAfterCsConnectRelease进行处理 */
    if ( MM_FALSE == NAS_MM_ProcessLuAfterCsConnectNotExist() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
         || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
         || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            /* 删除CHR错误的记录点CS PAGING FAIL */
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );

        Mm_ComCheckDelayDetach();
    }
    else
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                           enMmCcRelCause);
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                           enMmCcRelCause);
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                               /* 有等待的CC触发的需要建立的MM连接         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           enMmCcRelCause);
        }
        else
        {
            /* 删除CHR错误的记录点CS PAGING FAIL */
            ;
        }
    }

    if ( g_T3211Flag )
    {
        Mm_TimerStart(MM_TIMER_T3211);
        g_T3211Flag = 0;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ProcEstCnfCauseAtState12
 功能描述  : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下，收到RRMM_EST_CNF后的处理
 输入参数  : RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult - 建链结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  4.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 删除小区禁止业务标记,由系统消息和AC INFO CHANGE信息触发更新

  5.日    期   : 2013年8月22日
    作    者   : w00167002
    修改内容   : DTS2013081604476:w重选到G下后，被立即指派拒绝，GAS启动T3122
                  定时器，接着用户发起电话，NAS发起LAU,GAS由于T3122运行，直接回复
                  建联失败。MM启动了T3211,在这种场景下，NAS不需要启动T3211定时器。
  6.日    期   : 2013年4月1日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:增加对RRC_EST_RJ_NO_RF的处理
*****************************************************************************/
VOS_VOID NAS_MM_ProcEstCnfCauseAtState12(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    switch (ulResult)
    {
        case RRC_EST_SUCCESS:
        case RRC_EST_PRESENT:
            NAS_MM_ProcEstCnfSuccessCauseAtState12();
            break;
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        case RRC_EST_RJ_SNW:
        case RRC_EST_RJ_NO_RF:                                                     /* RR Connection failed because of no rf */
        case RRC_EST_RJ_T3122_RUNNING:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);

            break;
        case RRC_EST_OTHER_ACCESS_BARRED:
            /* 主要接入受限，设置标志位 */
            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);

            break;
        case RRC_EST_PAGING_ACCESS_BARRED:
            /* 主要接入受限，设置标志位 */
            NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);
            break;
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_CELL_BAR:
            /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-18, begin */
            /* 非紧急呼叫才设置限制注册和寻呼标记 */
            if (MMCC_EMERGENCY_CALL !=  g_MmCcEstReq.ulCallType)
            /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-18, end */
            {
                /* 接入受限，设置标志位 */
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
            }

            NAS_MM_ProcEstCnfOtherFailCauseAtState12(ulResult);
            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E32:WARNING: ulResult Abnormal");
            break;
    }
}



/*****************************************************************************
 函 数 名  : NAS_MM_DecodeFullNameForNetworkIe
 功能描述  : 解析Full Name for Network IE
 输入参数  :
     VOS_UINT8     - *pucRcvMsg  : 消息指针
     VOS_UINT16    - usMsgSize,  : 消息长度
     VOS_UINT16    - *pusIndex,  : 当前处理消息位置
 输出参数  :
     VOS_UINT8     - *pucEventId : 事件ID
     VOS_UINT8     - *pucLongNetWorkNameExist : IE有效标志
 返 回 值  : MM_DECODE_RESULT_ENUM_U32 - 消息IE解析结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月20日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : DTS2013010809507网络名称上报错误
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFullNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucLongNetWorkNameExist
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH))
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if ( 0 == usIeLen )
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeFullNameForNetworkIe:WARNING: NETWORK NAME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;

        }
        else if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkNtwkNam( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ) )
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeFullNameForNetworkIe:WARNING: NETWORK NAME ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            else
            {
                PS_MEM_SET(pstCurrOperatorName->aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
                if (NAS_MML_MAX_OPER_LONG_NAME_LEN >= (pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1))
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1);
                }
                else
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], NAS_MML_MAX_OPER_LONG_NAME_LEN);
                }
            }

            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeShortNameForNetworkIe
 功能描述  : 解析Short Name for Network IE
 输入参数  :
     VOS_UINT8     - *pucRcvMsg  : 消息指针
     VOS_UINT16    - usMsgSize,  : 消息长度
     VOS_UINT16    - *pusIndex,  : 当前处理消息位置
 输出参数  :
     VOS_UINT8     - *pucEventId : 事件ID
     VOS_UINT8     - *pucShortNetWorkNameExist : IE有效标志
 返 回 值  : MM_DECODE_RESULT_ENUM_U32 - 消息IE解析结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月20日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2013年01月09日
    作    者   : l65478
    修改内容   : DTS2013010809507网络名称上报错误
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeShortNameForNetworkIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId,
    VOS_UINT8                           *pucShortNetWorkNameExist
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH))
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if ( 0 == usIeLen )
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeShortNameForNetworkIe:WARNING: NETWORK NAME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        else if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkNtwkNam( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ) )
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeShortNameForNetworkIe:WARNING: NETWORK NAME ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            else
            {
                PS_MEM_SET(pstCurrOperatorName->aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);
                if (NAS_MML_MAX_OPER_SHORT_NAME_LEN >= (pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1))
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] + 1);
                }
                else
                {
                    PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH], NAS_MML_MAX_OPER_SHORT_NAME_LEN);
                }
            }

            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeLocalTimeZoneIe
 功能描述  : 解析Local Time Zone IE
 输入参数  :
     VOS_UINT8     - *pucRcvMsg  : 消息指针
     VOS_UINT16    - usMsgSize,  : 消息长度
     VOS_UINT16    - *pusIndex,  : 当前处理消息位置
 输出参数  :
     VOS_UINT8     - *pucEventId : 事件ID
 返 回 值  :
     MM_DECODE_RESULT_ENUM_U32 - 解析结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月20日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        if ( VOS_FALSE == MM_IeChkTimZone(&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalTimeZoneIe:WARNING: Local Time Zone Value ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        usIndex = usIndex + MM_IE_LOCAL_TIME_ZONE_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe
 功能描述  : 解析Universal Time And Local Time Zone IE
 输入参数  :
     VOS_UINT8     - *pucRcvMsg  : 消息指针
     VOS_UINT16    - usMsgSize,  : 消息长度
     VOS_UINT16    - *pusIndex,  : 当前处理消息位置
 输出参数  :
     VOS_UINT8     - *pucEventId : 事件ID
 返 回 值  :
     MM_DECODE_RESULT_ENUM_U32 - 消息IE解析结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月20日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2010年7月20日
    作    者   : 欧阳飞
    修改内容   : DTS2010072001259，当IE检查失败时，忽略该消息，但不再给网络
                 回复MM STATUS消息
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        if ( VOS_FALSE == MM_IeChkTimAndTimZone(&pucRcvMsg[usIndex + MM_IE_TAG_LENGTH]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe:WARNING: Universal Time and Zone value error!");
        }
        usIndex = usIndex + MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeLocalizedServiceAreaIe
 功能描述  : 解析Localize Service Area IE
 输入参数  :
     VOS_UINT8     - *pucRcvMsg  : 消息指针
     VOS_UINT16    - usMsgSize,  : 消息长度
     VOS_UINT16    - *pusIndex,  : 当前处理消息位置
 输出参数  :
     VOS_UINT8     - *pucEventId : 事件ID
 返 回 值  : MM_DECODE_RESULT_ENUM_U32 - 消息IE解析结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月20日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeLocalizedServiceAreaIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_TL_LENGTH) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];

        if (usIeLen > MM_IE_LSA_IDENTITY_VALUE_MAX_LEN)
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalizedServiceAreaIe:WARNING: LSA ID SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        if ( usMsgSize < (usIndex + usIeLen + MM_IE_TL_LENGTH) )
        {
            usIndex = usMsgSize;
        }
        else
        {
            if ( VOS_FALSE == MM_IeChkLsaIdtfr( &pucRcvMsg[usIndex + MM_IE_TAG_LENGTH] ))
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeLocalizedServiceAreaIe:WARNING: LSA ID ERROR!");
                *pucEventId = MM_EVENT_ID_STATUS_95;
                ulRst       = MM_DECODE_END;
            }
            usIndex = usIndex + usIeLen + MM_IE_TL_LENGTH;
        }
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeNetworkDaylightSavingTimeIe
 功能描述  : 解析Network Daylight Saving Time IE
 输入参数  :
     VOS_UINT8     - *pucRcvMsg  : 消息指针
     VOS_UINT16    - usMsgSize,  : 消息长度
     VOS_UINT16    - *pusIndex,  : 当前处理消息位置
 输出参数  :
     VOS_UINT8     - *pucEventId : 事件ID
 返 回 值  : MM_DECODE_RESULT_ENUM_U32 - 消息IE解析结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月20日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeNetworkDaylightSavingTimeIe(
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT16                          *pusIndex,
    VOS_UINT8                           *pucEventId
)
{
    VOS_UINT16                          usIndex;
    MM_DECODE_RESULT_ENUM_U32           ulRst;
    VOS_UINT16                          usIeLen;

    usIndex = *pusIndex;
    ulRst   = MM_DECODE_SUCCESS;

    if ( usMsgSize < (usIndex + MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN) )
    {
        usIndex = usMsgSize;
    }
    else
    {
        usIeLen = pucRcvMsg[usIndex + MM_IE_TAG_LENGTH];
        if ( MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_VALUE_LEN !=  usIeLen)
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeNetworkDaylightSavingTimeIe:WARNING: DAYLIGHT SAVING TIME SIZE ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }

        if ( MM_FALSE == MM_IeChkDayLightSavTim( &pucRcvMsg[usIndex + 1]))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_DecodeNetworkDaylightSavingTimeIe:WARNING: DAYLIGHT SAVING TIME ERROR!");
            *pucEventId = MM_EVENT_ID_STATUS_95;
            ulRst       = MM_DECODE_END;
        }
        usIndex = usIndex + MM_IE_NETWORK_DAYLIGHT_SAVING_TIME_LEN;
    }

    *pusIndex = usIndex;

    return ulRst;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsInRegisterProcedure
 功能描述  : 判断当前是否在注册过程中
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年10月10日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MM_IsInRegisterProcedure(VOS_VOID)
{
    /* 判断当前是否在注册过程中 */
    if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
        || (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_NeedSendEPlmnConnFail
 功能描述  : 判断CS连接释放是否需要发送EPLMN给接入层
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月3日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL NAS_MM_NeedSendEPlmnConnFail()
{
    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
      && (1 == g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsPLmnIdInEplmnList
 功能描述  : 判断当前PLMN ID是否在EPLMN和RPLMN中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月11日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MM_IsPLmnIdInEplmnList (
    MM_PLMN_ID_STRU                    *pstPlmnId
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList    =   NAS_MML_GetEquPlmnList();
    for ( i = 0 ; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if ( ( pstPlmnId->ulMcc == pstEplmnList->astEquPlmnAddr[i].ulMcc)
          && ( pstPlmnId->ulMnc == pstEplmnList->astEquPlmnAddr[i].ulMnc))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MM_ConvertToMmcServiceStatus
 功能描述  : 把MM的服务状态转换为MMC的服务状态
 输入参数  : VOS_UINT8                           ucMmServiceStatus
             MMCMM_LU_RESULT_IND_STRU           *pMmcLuRstInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月15日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ConvertToMmcServiceStatus(
    VOS_UINT8                           ucMmServiceStatus,
    VOS_UINT32                         *pCsServiceStatus
)
{
    switch(ucMmServiceStatus)
    {
        case MM_NORMAL_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_NORMAL_SERVICE;
            break;
        case MM_LIMITED_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        case MM_NO_IMSI:
            *pCsServiceStatus = MM_COM_SRVST_NO_IMSI;
            break;
        case MM_NO_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_NO_SERVICE;
            break;
        case MM_LIMIT_REGION_SERVICE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            break;
        case MM_ATTEMPTING_TO_UPDATE:
            *pCsServiceStatus = MM_COM_SRVST_NO_CHANGE;
            break;
        case MM_DETACHED:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        case MM_DISABLE:
            *pCsServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_HandleGmmCauseValAsLuAccept
 功能描述  : MM位置更新成功后清除GMM attach/rau失败原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月7日
    作    者   : 12
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_HandleGmmCauseValAsLuAccept()
{
    if ((MM_GMM_ATTACH_PROC == g_MmGlobalInfo.ucProc)
     || (MM_GMM_RAU_PROC == g_MmGlobalInfo.ucProc))
    {
        if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW  == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
         || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal))
        {
            Mm_ComProcCauseClear();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateCsServiceConnStatusFlg
 功能描述  : 根据当前链接状态更新CS域的业务存在状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月3日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCsServiceConnStatusFlg(VOS_VOID)
{
    if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
      && ( MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
    }

    if ( ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
      || ( MM_CONST_NUM_0 != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
    {
        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateCsServiceBufferStatusFlg
 功能描述  : 更新CS域缓存业务是否存在
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月3日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCsServiceBufferStatusFlg(VOS_VOID)
{
    if ( ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
      && ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
      && ( MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ) )
    {
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
      || ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
      || ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg ) )
    {
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetLikeBFlg
 功能描述  : 设置LIKE B标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月3日
    作    者   : c00173809
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_SetLikeBFlg(VOS_VOID)
{
    if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 设置类似于B模式的全局量                  */
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_WriteRplmnWithRatNvim
 功能描述  : 写NV: en_NV_Item_RPlmnWithRat
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年10月8日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU    stRplmn;

    stRplmn.ucLastRplmnRat          = (VOS_UINT8)pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if(NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsGURplmnChanged
 功能描述  : 判断lau成功后RPLMN是否改变
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE:RPLMN改变
             VOS_FALSE:RPLMN未改变
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月08日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulGRplmnCompareRslt;
    VOS_UINT32                          ulWRplmnCompareRslt;

    /* 默认RPlmn比较结果未发生改变 */
    ulGRplmnCompareRslt = VOS_TRUE;
    ulWRplmnCompareRslt = VOS_TRUE;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 判断全局变量中的LastRPLMN的接入技术是否发生改变 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        /* RPlmn信息发生了改变，返回VOS_TRUE */
        return VOS_TRUE;
    }

    /* 判断全局变量中的双RPLMN是否支持 */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stGRplmnInNV);

        ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stWRplmnInNV);
    }
    else
    {
        /* 支持双RPLMN, 则只判断对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stGRplmnInNV);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stWRplmnInNV);
        }
        else
        {
            ;
        }
    }

    /* RPlmn比较结果，VOS_FALSE表示发生了改变 */
    if ((VOS_FALSE == ulGRplmnCompareRslt)
     || (VOS_FALSE == ulWRplmnCompareRslt))
    {
        /* RPlmn信息发生了改变，返回VOS_TRUE */
        return VOS_TRUE;
    }

    /* RPlmn信息未发生改变，返回VOS_FALSE */
    return VOS_FALSE;

}



/*****************************************************************************
 函 数 名  : NAS_MM_GenerateEPlmnInfo
 功能描述  : 将RPlmn加入到网侧携带的EPlmn列表中，
              从EPLMN列表中删除无效 、禁止和不允许漫游的网络
 输入参数  : ulLauAcceptPlmnNum:lau accept中带的EPLMN个数
              pHandlingPlmnList:lau accept中带的EPLMN信息
 输出参数  : pstEquPlmnInfo:MML保存的EPLMN信息
 返 回 值  : VOS_TRUE:EPLMN改变
              VOS_FALSE:EPLMN未改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月13日
    作    者   : W00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_GenerateEPlmnInfo(
    VOS_UINT32                          ulLauAcceptPlmnNum,
    MM_PLMN_ID_STRU                    *pstLauAcceptPlmnList,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId       = VOS_NULL_PTR;

    /* 检测网侧的Eplmn个数不大于15个 */
    if (ulLauAcceptPlmnNum > NAS_MML_MAX_NETWORK_EQUPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_GenerateEPlmnInfo:NETWORK EPlmn NUMBER > 15");
        ulLauAcceptPlmnNum = NAS_MML_MAX_NETWORK_EQUPLMN_NUM;
    }

    /* 先添加当前驻留的plmn信息到EPlmn列表中 */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;
    pstEquPlmnInfo->ucEquPlmnNum = 1;

    /* 添加网侧的EPlmn，EPLMN信息从第一个位置开始记录 */
    for ( i = 0; i < ulLauAcceptPlmnNum; i++ )
    {
        pstEquPlmnInfo->astEquPlmnAddr[1 + i].ulMcc = pstLauAcceptPlmnList[i].ulMcc;
        pstEquPlmnInfo->astEquPlmnAddr[1 + i].ulMnc = pstLauAcceptPlmnList[i].ulMnc;
        pstEquPlmnInfo->ucEquPlmnNum += 1;
    }

    /* 从EPLMN列表中删除无效 、禁止和不允许漫游的网络 */
    pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList(pstEquPlmnInfo->ucEquPlmnNum,
                                            pstEquPlmnInfo->astEquPlmnAddr);
    pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList(pstEquPlmnInfo->ucEquPlmnNum,
                                            pstEquPlmnInfo->astEquPlmnAddr);

    return ;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn
 功能描述  : 将MML格式的PlmnID转换为Nvim的Eplmn
              23002f(MML的格式 Mcc:0x000302,Mnc:0x0f0200)-->2,3,0,0,2,f
 输入参数  : pstPlmnId: MML的PLMN ID
 输出参数  : pstNvimPlmnId: NvimEPlmn格式
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* 转化MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* 转化MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmlEquListToNvimEquPlmnList
 功能描述  : 将MML格式的Eplmn列表转换为Nvim的Eplmn列表
 输入参数  : pstMmlEPlmnList: MML的EplmnList
 输出参数  : pstNvimEPlmnList:Nvim格式的EPlmnList
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_MM_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsInNvEplmnList
 功能描述  : 判断PLMN ID是否在NV中的EPLMN LIST列表中
 输入参数  : pstPlmnId:需要判断的PLMN ID
             ucPlmnNum:PLMN ID个数
             pstPlmnIdList:PLMN ID列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在NV中的EPLMN LIST列表中
             VOS_FALSE : PLMN ID不在NV中的EPLMN LIST列表中
 调用函数  :
 被调函数  :
 修改历史      :
    1.日    期   : 2012年03月15日
      作    者   : l00130025
      修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_UINT32 NAS_MM_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNvimEPlmnListEqual
 功能描述  : 判断2个NVIM_EQUIVALENT_PLMN_LIST_STRU是否相同
 输入参数  : pstNvimEPlmnList1,pstNvimEPlmnList2待比较的2个NvimPlmnList
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 2个EplmnList相同
              VOS_FALSE : 2个EplmnList不同
 调用函数  :
 被调函数  :
 修改历史      :
    1.日    期   : 2012年03月15日
      作    者   : l00130025
      修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn个数大于0,但Rplmn不同时，EplmnList不相同 */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
                                                 1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* 其它Eplmn没有进行排序且有重复数据，需要对比2个列表才能确定相同 */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
                                                 pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MM_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DeleteEPlmnList
 功能描述  : 清除EPLMN列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MM_DeleteEPlmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList = NAS_MML_GetEquPlmnList();

    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* 清除NV中保存的EPLMN */
    NAS_MM_WriteEplmnNvim( pstEPlmnList );

    /*将当前网络添加Eplmn列表*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_WriteEplmnNvim
 功能描述  : 将Eplmn更新到NV中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月08日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
)
{

    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;

    ulUpdateNvFlag  = VOS_FALSE;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MM,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_MM,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_MM, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_MM_ConvertMmlEquListToNvimEquPlmnList(pstEplmnAddr,
                                              pstNewNvEquPlmnList);

    /* 读取NV中EPLMN信息 */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)) )
    {
        if (VOS_FALSE == NAS_MM_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                     pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MM, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_MM, pstOldNvEquPlmnList);

}

/*****************************************************************************
函 数 名  : NAS_MM_UpdateEquPlmnInfo
功能描述  : 判断是否需要初始化EPLMN信息
输入参数  : ulCause :LU失败的原因值
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期  : 2011年10月8日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年03月15日
  作    者   : l00130025
  修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MM_UpdateEquPlmnInfo(
    VOS_UINT32                          ulCause
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* 如果LAU失败，需要判断是否删除EPLMN */
    switch (ulCause)
    {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            NAS_MM_DeleteEPlmnList();

            break;

        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        case NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS:
        case NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM:
        case NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI:
        case NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT:

            break;

        default:
           /* 其他原因值，如果LAU attempt acounter超过Roam broker特性注册失败的次数，需要清除EPLMN */
           if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
            || (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= MM_CONST_NUM_4)
            || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                NAS_MM_DeleteEPlmnList();

            }
           break;

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_CsSimValid
 功能描述  : 提供给短消息模块获取CS SIM卡是否有效
 输入参数  : 无
 输出参数  : VOS_BOOL *pbCsSimValids
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月28日
    作    者   : 孙习波/s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_CsSimValid(VOS_BOOL *pbCsSimValid)
{
    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {
        *pbCsSimValid = VOS_TRUE;
    }
    else
    {
        *pbCsSimValid = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_CsCellBar
 功能描述  : 提供给短消息模块获取UE驻留小区CS域是否被BAR
 输入参数  : 无
 输出参数  : VOS_BOOL *pCsCellBar  CS域是否被BAR
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月28日
    作    者   : 孙习波/s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  3.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
*****************************************************************************/
VOS_VOID NAS_MM_CsCellBar(VOS_BOOL *pbCsCellBar)
{
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
    {
        *pbCsCellBar = VOS_TRUE;
    }
    else
    {
        *pbCsCellBar = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetLauUptNeededCsSrvStatus
 功能描述  : 获取MM_IDLE_LOCATION_UPDATE_NEEDED状态时CS域服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 CS域服务状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_MM_GetLauUptNeededCsSrvStatus(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* 当前LAI和上次注册成功LAI相同，且更新状态为U1 */
    if((VOS_FALSE == NAS_MML_IsCsLaiChanged())
    && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
    && ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState ))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        return MM_COM_SRVST_LIMITED_SERVICE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated
 功能描述  : MM_IDLE_LOCATION_UPDATE_NEEDED U1 状态时CS注册从受限变为不受限的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。

*****************************************************************************/
VOS_VOID  NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated()
{
    /* 如果LAI不变,更新状态为U1 */
    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
    {
        if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型                               */
            Mm_ComLuOnly();
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                /* 设置服务状态                             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }
    else
    {
        /* 当前是上电开机 */
        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* 设置LU类型                               */
            Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        }
        else if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型                               */
            Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                /* 设置服务状态                             */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
    }
}
/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated
 功能描述  : MM_IDLE_LOCATION_UPDATE_NEEDED 非U状态时CS注册从受限变为不受限,网络模式II的处理
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

  3.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.sunxibo走读T3212定时器时长不为0才发起LAU.

*****************************************************************************/
VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated(VOS_VOID)
{
    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)                                 /* 刚开机，位置区不变，也发起注册 */
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型                               */
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
        return;
    }


    /* 在非U1状态并且周期注册定时器没有运行时,要进行一次LU过程 */
    if ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
     && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
     && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen))
    {
        if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
        }

        Mm_ComLuOnly();
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;                /* 设置服务状态                             */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsAcChgRegisterNetModeII
 功能描述  : MM_IDLE_LOCATION_UPDATE_NEEDED CS注册从受限变为不受限
             网络模式II下的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcCsAcChgRegisterNetModeII(VOS_VOID)
{
    /* LAI发生改变 */
    if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    {
        Mm_TimerStop(MM_TIMER_T3213);
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型                               */
        Mm_ComLuOnly();                                                         /* 发送LU REQ                               */
    }
    else
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            /* 当前CS UPDATE状态为U1 */
            NAS_MM_ProcCsAcChgRegisterNetModeIIUpdated();
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeIINotUpdated();
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar
 功能描述  : 业务过程中，CS BAR TO UNBAR更新MM状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 CS域服务状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2014年5月7日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
*****************************************************************************/
VOS_VOID NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucStaOfRcvXXEstReq)
    {
        return;
    }

    /* 当前CS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* 用户设置不支持CS */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_LIMITED_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* 当前网络在禁止列表中 */
    if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_LIMITED_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
        return;
    }

    /* 当前CS ATTACH状态，LAI没有改变，更新状态为U1 */
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-7, begin */
    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-7, end */
     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
     && ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState ))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_NORMAL_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_NORMAL_SERVICE;
    }
    else
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = MM_IDLE_NORMAL_SERVICE;

        g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
    }
}



/*****************************************************************************
 函 数 名  : NAS_MM_ProcEccNumList_RcvSysinfo
 功能描述  : MM收到系统消息后，对紧急呼列表的处理
 输入参数  : pSysInfoInd 系统消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月5日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2014年04月03日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.CurLai替换成MML中的
  3.日    期   : 2015年6月5日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_ProcEccNumList_RcvSysinfo(
    VOS_UINT32                          ulMcc
)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU     EmcNumLst;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId        = VOS_NULL_PTR;

    pstCurPlmnId  = NAS_MML_GetCurrCampPlmnId();

    pstEmergencyNumList = NAS_MML_GetEmergencyNumList();

    /* 消息中包不含紧急呼列表但之前存储了紧急呼列表,如果不是同一个国家的mcc则，删除之前存储的紧急呼叫列表
    24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6、4.7.3.1.3、4.7.5.1.3描述如下:
    The emergency number(s) received in the Emergency Number List IE are valid only
    in networks with in.the same MCCcountry as in  the cell on which this IE
    is received.*/
    if (VOS_FALSE == NAS_MML_ComparePlmnMcc(ulMcc, pstCurPlmnId->ulMcc))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    {                                                                       /* 新小区的MCC与上次驻留小区的MCC不同       */
        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, pstEmergencyNumList->ulMcc))
        {
            Mm_SndCcEmergencyNumberList(pstEmergencyNumList);               /* 通知CC紧急呼号码 */
        }
        else
        {
            EmcNumLst.ulMcc             = ulMcc;
            EmcNumLst.ucEmergencyNumber = 0;

            PS_MEM_SET(EmcNumLst.aucEmergencyList, 0xFF, NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS);
            Mm_SndCcEmergencyNumberList(&EmcNumLst);                            /* 通知CC紧急呼号码无效                     */
        }
    }

    return;
}


#if (FEATURE_LTE == FEATURE_ON)

/*****************************************************************************
 函 数 名  : NAS_MM_IsLInterSysGuLauNeededLaiNoChange
 功能描述  : 判断L异系统到GU后，LAI没改变是否也需要发起LAU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要LAU
              VOS_FALSE:不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月21日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年05月21日
    作    者   : z40661
    修改内容   : DTS2012052308001:从L重选到G后反复进行LAU
  3.日    期   : 2013年12月14日
    作    者   : f00261443
    修改内容   : Volte_PhaseIII:如果UE支持IMS，则即使Lai没有变化，且强制Lau的的nv项打开，则需要进行LAU
  4.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
  5.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改

*****************************************************************************/
VOS_UINT32  NAS_MM_IsLauNeededLaiNoChange_LInterSys(VOS_VOID)
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;

    VOS_UINT8                                               ucLauForceFlg;
    VOS_UINT8                                               ucImsVoiceAvailFlg;

    enLteCsServiceCfg   = NAS_MML_GetLteCsServiceCfg();

    /**
     * 如果不是从 L 异系统变换 则不进行后续判断
     */
    if (NAS_MML_NET_RAT_TYPE_LTE != g_MmGlobalInfo.enPreRatType)
    {
        return VOS_FALSE;
    }

    /* 如果CS业务配置为SMS over SGs，而且TIN类型为"GUTI" */
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && ((NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)))
    {
        return VOS_TRUE;
    }

    /**
     * 新增场景：如果UE支持IMS（读取Nv且语音优选域不是CS ONLY)
     * 且控制从L到GU下即使LAI没有改变也需要进行LAU的Nv项打开，
     * 只要无CSFB服务，则需要进行LAU
     */
    /**
     * VDF的标书要求支持IMS voice的终端在从L异系统变换到GU后，无条件进行一次LAU,原文如下：
     * The LTE terminal supporting Voice over IMS (GSMA IR.92),
     * shall always issue a Location Update following a RAT change.
     * With terminal in IDLE mode a LAU is performed.
     * If a call is initiated under CS network,
     * all the procedures currently in use today shall be applicable.
     * For example, when a terminal that initially registers on 2G roams into LTE coverage,
     * then roams back into 2G under the same LAC that it previously registered,
     * will it always send a LU towards the MSC.
     */

    ucLauForceFlg = NAS_MML_GetImsVoiceInterSysLauEnableFlg();
    ucImsVoiceAvailFlg = NAS_MML_GetImsVoiceAvailFlg();

    if ((VOS_TRUE == ucLauForceFlg)
     && (VOS_TRUE == ucImsVoiceAvailFlg))
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
     && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg))
    {
        return VOS_TRUE;
    }

    /* 23122_CR0122R1_(Rel-8)_C1-083459 23122 4.5.2章节描述如下:
    -The MS detects that it has entered a registration area that has the same identity
    as the one stored in the MS, while being in the ROAMING NOT ALLOWED update state,
    and the LAI or the PLMN identity is not contained in any of the lists of "forbidden LAs for roaming",
    "forbidden LAs for regional provision of service", "forbidden PLMNs for GPRS service"
    or "forbidden PLMNs" respectively. */
    if (NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED == NAS_MML_GetCsUpdateStatus())
    {
        return VOS_TRUE;
    }

    /* TS 24301 5.5.3.3.6章节描述如下:
     * 3)otherwise, the abnormal cases specified in subclause 5.5.3.2.6 apply with the following modification.
     *   If the tracking area updating attempt counter is incremented according to subclause 5.5.3.2.6 the next actions depend on
     *   the value of the tracking area updating attempt counter.
     *   - If the tracking area updating attempt counter is less than 5, the UE shall set the update status to U2 NOT UPDATED,
     *     but shall not delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs;
     *
     * TS 23122 4.5.2章节描述如下:
     * - the MS changes cell while the update status is "NOT UPDATED";(for MS capable of GPRS and non-GPRS services when at least
     *   one of both update statuses is "NOT UPDATED")
     */

    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsT3412ExpiredNeedRegist
 功能描述  : T3412超时网络模式II是否需要LAU
 输入参数  : enLteCsServiceCfg - UE支持的cs 业务能力
             enTinType         - TIN类型
             enT3412Status     - T3412定时器状态
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要发起注册
             VOS_FALSE - 不需要发起注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
)
{
     /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((NAS_MML_TIMER_EXP == enT3412Status)
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsT3423StatusChangeNeedRegist
 功能描述  : T3423在运行时或超时网络模式II是否需要LAU
 输入参数  : enLteCsServiceCfg - UE支持的cs 业务能力
             enTinType         - TIN类型
             enT3423Status     - T3423定时器状态
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要发起注册
             VOS_FALSE - 不需要发起注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
)
{
      /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
       The normal location updating procedure shall also be started when the MS,
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       enters a GERAN or UTRAN cell in network operation mode II or III and the
       E-UTRAN deactivate ISR timer T3423 has expired.

       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       -   when the MS enters a GERAN or UTRAN cell in network operation mode II
       or III and the E-UTRAN deactivate ISR timer T3423 is running.
    */
    if (((NAS_MML_TIMER_START == enT3423Status)
      || (NAS_MML_TIMER_EXP == enT3423Status))
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_WriteTinInfoNvim
 功能描述  : 更新TIN INFO的内容到NVIM
 输入参数  : enTinType - TIN类型
             pucImsi   - IMSI
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月15日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  NAS_MM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
    NAS_NVIM_TIN_INFO_STRU              stTinInfo;
    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end */

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    if (pstRplmnCfgInfo->enTinType != enTinType)
    {
        /* 先更新MML的参数 */
        pstRplmnCfgInfo->enTinType  = enTinType;
        PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

        /* 再更新NVIM中的参数 */
        stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
        PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
        PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

        /* 保存在NVIM中 */
        if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                               &stTinInfo,
                               sizeof(stTinInfo)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_WriteTinInfoNvim:Write NV Failed");
        }

        /* 可维可测，勾消息 */
        NAS_MM_LogTinTypeInfo(enTinType);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_LogTinTypeInfo
 功能描述  : MM 更新TIN类型时需要把消息勾出到trace中
 输入参数  : enTinType - TIN类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月17日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_MM_LOG_TIN_INFO_STRU           *pstTinTypeInfo = VOS_NULL_PTR;

    pstTinTypeInfo = (NAS_MM_LOG_TIN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                             sizeof(NAS_MM_LOG_TIN_INFO_STRU));

    if ( VOS_NULL_PTR == pstTinTypeInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogTinTypeInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstTinTypeInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstTinTypeInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstTinTypeInfo->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_TIN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstTinTypeInfo->stMsgHeader.ulMsgName       = NAS_MM_LOG_TIN_TYPE_INFO_IND;

    pstTinTypeInfo->enTinType = enTinType;

    DIAG_TraceReport(pstTinTypeInfo);

    PS_MEM_FREE(WUEPS_PID_MM, pstTinTypeInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedDeactiveIsrLauInit
 功能描述  : LAU发起时是否需要去激活ISR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要去激活ISR
             VOS_FALSE - 不需要去激活ISR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月29日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedDeactiveIsrLauInit(VOS_VOID)
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;
    VOS_INT8                                                cVersion;


    cVersion       = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();

    /* 24008_CR1902R1_(Rel-11)_C1-113481-c1-113200-tin 24008 4.4.4.1描述如下:
    If the mobile station is configured to use CS fallback and SMS over SGs, or SMS over SGs only,
    and TIN indicates "RAT-related TMSI" the mobile station shall set the TIN to "P-TMSI"
    unless the mobile station had already received the EMM cause #18 during a combined
    attach procedure (see subclause 5.5.1.3.4.3 of 3GPP TS 24.301 [120]) or a combined
    tracking area updating procedure (see subclause 5.5.3.3.4.3 of 3GPP TS 24.301 [120])
    on the same PLMN, but not disabled the E-UTRAN capability.*/
    enTinType         = NAS_MML_GetTinType();
    enLteCsServiceCfg = NAS_MML_GetLteCsServiceCfg();

    if (((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
       || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
     && (cVersion >= PS_PTL_VER_R11))
    {
        if ((VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapStatus)
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapStatus))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedDeactiveIsrAfterLau
 功能描述  : LAU结束后是否需要去激活ISR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要去激活ISR
             VOS_FALSE - 不需要去激活ISR
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月15日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedDeactiveIsrAfterLau(VOS_VOID)
{
    VOS_UINT32                                             ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                             ulT3412StatusChgNeedRegFlg;

    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function描述去激活ISR场景：
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
     || (VOS_TRUE == ulT3412StatusChgNeedRegFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvSysInfoSurpportLte_PreProc
 功能描述  : 支持LTE时，收到系统消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 预处理完成
             VOS_FALSE - 预处理未完成,还需要后续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年4月5日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2012年06月08日
   作    者   : l65478
    修改内容   : DTS2012060708776:开机L下注册失败#7后搜网到GU下LU类型错误
 3.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
 4.日    期   : 2012年12月28日
   作    者   : t00212959
   修改内容   : DTS2012122607665:L下搜网时被紧急呼打断
 5.日    期   : 2013年7月25日
   作    者   : w00242748
   修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                rau req中带follow on标志,无明确协议依据
 6.日    期   : 2014年4月18日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目调整:将预处理中停止等待系统消息定时器的逻辑移到到此处
*****************************************************************************/
VOS_UINT32 NAS_MM_RcvSysInfoSurpportLte_PreProc(VOS_VOID)
{
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-18, begin */
    /* 调整定时器名称 */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
    }

    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
    }
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-18, end */

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* 记录状态为CSFB MT已收到系统消息 */
        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_MM_RcvSysInfo_CSFB();

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg() )
    {
        /* CSFB流程从L异系统变换到GU,网络模式II,LAI未改变时先做业务，
           记录需要等业务结束后做LAU */
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    /* 如果CS业务配置为SMS over SGs或CSFB和短信都支持，而且TIN类型为"GUTI"
       3GPP 24008 4.4.1:
       indicating to the network that the MS, configured to use CS fallback and
       SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell
       in NMO II or III, after intersystem change from S1 mode to Iu
       or A/Gb mode, the TIN indicates "GUTI" and the location area of
       the current cell is the same as the stored location area; */

    if (VOS_TRUE == NAS_MM_IsLauNeededLaiNoChange_LInterSys())
    {
        /* 发起LAU流程 有紧急呼先进行紧急呼*/
        enLauType = NAS_MM_GetLuType();
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);



        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        return VOS_TRUE;
    }

    /* 3GPP 24.008中4.4.1   Location updating procedure章节描述:
       The normal location updating procedure shall also be started if
       the MS is configured to use CS fallback and SMS over SGs,
       or SMS over SGs only, and the TIN indicates "RAT-related TMSI",
       when the MS enters a GERAN or UTRAN cell in network operation
       mode II or III and the E-UTRAN deactivate ISR timer T3423 is running.
       The normal location updating procedure shall also be started when
       the MS, configured to use CS fallback and SMS over SGs, or SMS over
       SGs only, enters a GERAN or UTRAN cell in network operation mode
       II or III and the E-UTRAN deactivate ISR timer T3423 has expired*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        /* 发起LAU流程 有紧急呼先进行紧急呼*/
        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);


        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif
/*****************************************************************************
 函 数 名  : NAS_MM_GetLuType
 功能描述  : 设置LU类型
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月08日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2012年12月27日
    作    者   : t00212959
    修改内容   : DTS2012122607665
*****************************************************************************/
VOS_UINT8 NAS_MM_GetLuType(VOS_VOID)
{
    if ( VOS_TRUE == NAS_MML_IsCsLaiChanged() )
    {
        return MM_IE_LUT_NORMAL_LU;
    }
    else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
         && (MM_TRUE     == g_MmGlobalInfo.ucPowerOnFlg)
         && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
    {
        return MM_IE_LUT_IMSI_ATTACH;
    }
    else if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
    {
        return MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        return MM_IE_LUT_NORMAL_LU;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_LogMmStateInfo
 功能描述  : 勾MM的状态
 输入参数  : ucMmState: MM的当前状态
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月21日
    作    者   : l00171473
    修改内容   : 新生成函数

  2.日    期   : 2014年04月29日
    作    者   : y00245242
    修改内容   : 为eCall feature 修改

*****************************************************************************/
VOS_VOID  NAS_MM_LogMmStateInfo(
    NAS_MM_STATE_ENUM_UINT8             ucMmState
)
{
    NAS_MM_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MM_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogMmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_STATE_INFO_IND;
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
    pstMsg->enMmState                   = ucMmState;
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_IsCcTiValid
 功能描述  : 判断cc的transaction id是否合法
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - TI合法
             VOS_FALSE - TI非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月18日
    作    者   : z00161729
    修改内容   : 新生成函数,将圈复杂度

*****************************************************************************/
VOS_UINT32 NAS_MM_IsCcTiValid(VOS_VOID)
{
    if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
      ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ProcBufferedEmgCallBeforeLau_RcvSysinfo
 功能描述  : 收到系统消息需要做lau前判断是否有缓存的紧急呼叫，如果有且lai未改变
             先做紧急呼叫，呼叫结束后再做lau，如果lai改变且lai改变先做lau nv项
             关闭，先进行紧急呼叫呼叫结束后再做lau
 输入参数  : ulLaiChangeFlag - lai是否改变标志
             ulLuType        - Lau的类型
 输出参数  : 无
 返 回 值  : VOS_TRUE -
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月22日
    作    者   : z00161729
    修改内容   : 新生成函数, 降圈复杂度
  2.日    期   : 2012年10月25日
    作    者   : z00161729
    修改内容   : DTS2012102305986:csfb到gu access bar小区无法拨打紧急呼叫
  3.日    期   : 2012年11月09日
    作    者   : t00212959
    修改内容   : DTS2012110810521:紧急呼的判断不准确
  4.日    期   : 2012年12月22日
    作    者   : l65478
    修改内容   : DTS2012122103936 发起紧急呼叫时MM状态迁移错误
  5.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                rau req中带follow on标志,无明确协议依据
*****************************************************************************/
VOS_VOID NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(
    VOS_UINT32                          ulLaiChangeFlag,
    VOS_UINT8                           ucLuType
)
{
    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT32                          ulCsRestrictRegFlg;

    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulCsRestrictRegFlg             = NAS_MML_GetCsRestrictRegisterFlg();
    ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

    if (VOS_FALSE == ulLaiChangeFlag)
    {
        /* LAI未改变且存在缓存的紧急呼叫则先进行紧急呼叫，呼叫结束后再做lau */
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
#endif

            /* 不禁止CS并且LAI不改变时，在连接释放后需要进行LU */
            if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
             || ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                &&(MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
            {
                if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                 && ((MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                  && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (0x0 != gstMmTimer[MM_TIMER_T3212].ulTimerLen)))
                {
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
                }
            }
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* 记录收到建立请求时的状态                 */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-13, begin */
            /* 紧急呼叫的时候,等待进行LAU后上报注册结果,后面会进行delay的LAU流程
               正常呼叫的时候,可以上报假流程注册成功 */
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-13, end */

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            return;
        }

        /* 无缓存的紧急呼叫直接进行lau */
        g_MmGlobalInfo.LuInfo.ucLuType = ucLuType;
        Mm_ComLuOnly();
        return;
    }

    /* 存在缓存的紧急呼叫lai改变先进行紧急呼叫结束后再做lau nv开启 */
    if (((VOS_FALSE == ulCsfbEmgCallLaiChgLauFirstFlg)
      || ((VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg)
       && (VOS_TRUE == ulCsRestrictRegFlg)))
     && (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg))
    {
#if (FEATURE_LTE == FEATURE_ON)
         /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
        NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
#endif
        /* 不禁止CS并且LAI不改变时，在连接释放后需要进行LU */
        if ((MMCMM_NO_FORBIDDEN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         || ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            &&(MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
        {
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
        }
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* 记录收到建立请求时的状态                 */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-13, begin */
        /* 紧急呼叫的时候,等待进行LAU后上报注册结果,后面会进行delay的LAU流程
           正常呼叫的时候,可以上报假流程注册成功 */
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-13, end */

        Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

        return;
    }

    /* 无缓存的紧急呼叫直接进行lau */
    g_MmGlobalInfo.LuInfo.ucLuType = ucLuType;
    Mm_ComLuOnly();
    return;
}
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, end */


/*****************************************************************************
 函 数 名  : NAS_MM_IsCsEnableLau
 功能描述  : 判断CS域能否进行LAU
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月7日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MM_IsCsEnableLau( VOS_VOID )
{

    /* CS域的卡无效,不需要进行 */
    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus()  )
    {
        return VOS_FALSE;
    }

    /* CS域不允许aTTach,不需要进行 */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    /* CS域接入受限,不需要进行 */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        return VOS_FALSE;
    }

    /* 当前是禁止网络,不需要进行 */
    if ((MMCMM_NO_FORBIDDEN !=g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        return VOS_FALSE;
    }

    /* T3211定时器运行,不需要进行 */
    if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedLauCsSigRel
 功能描述  : 网络模式相同时，判断是否需要LAU
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月27日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年09月03日
    作    者   : l65478
    修改内容   : DTS2013041602825:CSFB连接建立失败后没有发起LU
  3.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                 网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                 rau req中带follow on标志,无明确协议依据
  4.日    期   : 2014年05月07日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
*****************************************************************************/
VOS_UINT32  NAS_MM_IsNeedLauCsSigRel( VOS_VOID )
{
    /* 调用此函数前,如果需要判断信令连接状态,需要由调用此函数的上级函数保证 */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-7, begin */
    if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-7, end */
      && ((MM_TRUE == g_MmGlobalInfo.ucConnRcvSysFlg)
       || (VOS_TRUE == g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg)) )
    {
        return VOS_TRUE;
    }

#if (FEATURE_LTE == FEATURE_ON)

    if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_MM_IsAbleRecover_EstCnfFailResult
 功能描述  : 判断接入层回复的est cnf失败原因值是否需要可恢复，可恢复需要cc/ss/sms重发
 输入参数  : enEstResult - 接入层回复的est cnf失败原因值
 输出参数  : VOS_TRUE  - 建链失败原因值可恢复，需要触发呼叫/补充业务/短信重发
             VOS_FALSE - 建链失败原因值暂时不可恢复，不需要触发呼叫/补充业务/短信重发
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2013年8月22日
    作    者   : w00167002
    修改内容   : DTS2013081604476:w重选到G下后，被立即指派拒绝，GAS启动T3122
                  定时器，接着用户发起电话，NAS发起LAU,GAS由于T3122运行，直接回复
                  建联失败。MM启动了T3211,在这种场景下，NAS不需要启动T3211定时器。
  3.日    期   :2013年9月15日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
*****************************************************************************/
VOS_UINT32  NAS_MM_IsAbleRecover_EstCnfFailResult(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstResult
)
{
    /* RRC_EST_RJ_CELL_BAR不可恢复 */
    if ((RRC_EST_IMMEDIATE_ASSIGN_REJECT == enEstResult)
     || (RRC_EST_ACCESS_BARRED           == enEstResult)
     || (RRC_EST_OTHER_ACCESS_BARRED     == enEstResult)
     || (RRC_EST_RJ_T3122_RUNNING        == enEstResult)
     || (RRC_EST_RJ_CELL_BAR             == enEstResult))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedCmServiceRetry_RelIndResult
 功能描述  : 判断接入层回复的rel ind失败原因值是否需要触发呼叫/补充业务/短信重发
 输入参数  : enRelCause - 接入层回复的rel ind失败原因值
 输出参数  : VOS_TRUE  - 需要触发呼叫/补充业务/短信重发
             VOS_FALSE - 不需要触发呼叫/补充业务/短信重发
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   :2013年9月15日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能

*****************************************************************************/
VOS_UINT32  NAS_MM_IsNeedCmServiceRetry_RelIndResult(
    RRC_REL_CAUSE_ENUM_UINT32           enRelCause
)
{
    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd
 功能描述  : MM收到RelInd，建链失败，尝试小于4次的初处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : t00212959
    修改内容   : 新生成函数, 降圈复杂度
  2.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  3.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  4.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
*****************************************************************************/
VOS_VOID NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(
    RRC_REL_CAUSE_ENUM_UINT32                   enRelCauses
)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    VOS_UINT8                                               ucGsmEstConnFailFlg = MM_FALSE;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (RRC_REL_CAUSE_CONN_FAIL   == enRelCauses))
    {
        ucGsmEstConnFailFlg = MM_TRUE;
    }

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
      && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
    {                                                                   /* 如果LAI不变,且更新状态为U1的时候         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd:INFO: MmServiceState is MM_NORMAL_SERVICE");

        if (MM_FALSE == ucGsmEstConnFailFlg)
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* 向MMC发送MMCMM_LU_RESULT_IND             */

        }

        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
        g_T3211Flag = 1;
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        if (MM_FALSE == ucGsmEstConnFailFlg)
        {
            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
        }
        else
        {
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        Mm_TimerStart(MM_TIMER_T3211);                                  /* 启动T3211                                */
    }

}


/*****************************************************************************
 函 数 名  : NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd
 功能描述  : MM收到RelInd，建链失败，向MMC发送RR链接状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : t00212959
    修改内容   : 新生成函数, 降圈复杂度
*****************************************************************************/
VOS_VOID NAS_MM_SndMmcRrConn_RcvRelInd(VOS_VOID)
{
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;

    if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
     ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
     ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR连接不存在                             */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
    }
    else
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR连接不存在                             */

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

}





/*****************************************************************************
 函 数 名  : NAS_MM_LocalDetach_MmInterRatChange
 功能描述  : MM在挂起状态收到detach消息的处理
 输入参数  : VOS_VOID* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年05月15日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 3.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 4.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_LocalDetach_MmInterRatChange(VOS_VOID)
{
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 通知GMM当前CS域已本地DETACH超时处理 */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                           /* 设置MM信息                               */

    /* 设置服务状态为DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* 备份全局变量在CS域进行本地detach后需要进行删除 */
    if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
      && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucSuspendPreState ) )
    {
        NAS_MM_InitCcoFallbackCtx();
    }

    /* 由于mm迁移了状态,3212在挂起状态未停止,此时需要停止 */
    Mm_TimerStop(MM_TIMER_T3212);

    if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucSuspendPreState)
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_NO_IMSI;
        g_MmGlobalInfo.ucPreState = MM_IDLE_NO_IMSI;
    }
    else
    {
        g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucPreState = MM_IDLE_LIMITED_SERVICE;
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucSuspendPreState;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucSuspendPreState;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_LocalDetach_MmNoImsi
 功能描述  : MM在无卡时候本地去注册的函数处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月11日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  3.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_LocalDetach_MmNoImsi(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

    /* 本地去注册通用操作 */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 通知GMM当前CS域已本地DETACH超时处理 */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    /* 建链不成功，直接本地DETACH */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* 设置服务状态为DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* 通知MMC当前卡无效 */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    /* 如果当前有信令链接，则释放链接 */
    if ( VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_LocalDetach
 功能描述  : MM本地去注册的函数处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月11日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmTimerProtectCsDetachExpired(VOS_VOID)
{
    NAS_MM_LocalDetach();

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_LocalDetach
 功能描述  : MM本地去注册的函数处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月11日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2013年9月12日
    作    者   : z00161729
    修改内容   : DTS2013082903019:支持ss重发功能
  3.日    期   : 2014年04月30日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_LocalDetach(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulMmState;

    pstConnStatus = NAS_MML_GetConnStatus();
    ulMmState     = Mm_GetState();

    /* 本地状态处理 */
    switch ( ulMmState )
    {
        case MM_INTER_RAT_CHANGE :

            /* 异系统时候的本地去注册处理，处理完毕直接返回 */
            NAS_MM_LocalDetach_MmInterRatChange();
            return;

        case MM_IDLE_NO_IMSI :

            /* NO IMSI的本地去注册处理，处理完毕直接返回 */
            NAS_MM_LocalDetach_MmNoImsi();
            return;

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        case MM_IDLE_ECALL_INACTIVE:

            NAS_MM_ProcMmcMmDetachReq_MmIdleECallInactive();
            return;
#endif
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-30, end */

        /* 不进行状态迁移的处理 */
        case MM_STATE_NULL :
            break;

        default:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            break;
    }

    /* 本地去注册通用操作 */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 通知GMM当前CS域已本地DETACH超时处理 */
    NAS_MM_SndGmmCsLocalDetachInd();

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    /* 建链不成功，直接本地DETACH */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* 设置服务状态为DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    /* 通知MMC当前服务域不支持 */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    /* 如果当前有信令链接，则释放链接 */
    if ( VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg )
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_StartDetachProtectingTimer
 功能描述  : 启动MM的Detach消息的保护定时器
 输入参数  : MMCMM_DETACH_REQ_STRU              *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2015年4月13日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_MM_StartDetachProtectingTimer(
    MMCMM_DETACH_REQ_STRU              *pstMsg
)
{
    /* Detach流程保护定时器时长 */
    VOS_UINT32                          ulDetachTimerVal;

    /* MM的CS域Detach保护定时器运行状态 */
    VOS_UINT32                          ulCsDetachTimerStatus;

    if (MMC_MM_DETACH_REASON_USER_DETACH == pstMsg->enDetachReason)
    {
        /* 用户触发的DETACH的时长: 90s */
        ulDetachTimerVal = NAS_MM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;
    }
    else
    {
        /* 如果当前是SYSCFG或服务域触发的DETACH,则设置保护定时器的时长为26s */
        ulDetachTimerVal = NAS_MM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE;
    }

    /* 获取MM的Detach保护定时器运行状态 */
    ulCsDetachTimerStatus = NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_CS_DETACH);

    /* 如果MM的CS域Detach保护定时器在运行，则不启动CS域Detach保护定时器 */
    if ( MM_TIMER_RUNNING == ulCsDetachTimerStatus )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartDetachProtectingTimer:WARN:TIMER HAS BEEN STARTED ALREADY");
        Mm_TimerStop(MM_TIMER_PROTECT_CS_DETACH);
    }

    /* 设置MM的CS域Detach保护定时器时长 */
    gstMmTimer[MM_TIMER_PROTECT_CS_DETACH].ulTimerLen = ulDetachTimerVal;

    /* 启动MM的CS域detach保护定时器 */
    Mm_TimerStart(MM_TIMER_PROTECT_CS_DETACH);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer
 功能描述  : 收到接入侧的RRMM_EST_CNF消息时，当前存在CS域DETACH标志的处理
 输入参数  : RRMM_EST_CNF_STRU              *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月11日
    作    者   : w00167002
    修改内容   : 新生成函数

  2.日    期   : 2013年6月24日
    作    者   : w00167002
    修改内容   : 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF
  3.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  4.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  5.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(
    RRMM_EST_CNF_STRU                  *pRrcEstCnf
)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    /* 如果当前建链成功，且有缓存用户发起的IMSI detach请求，则直接发起去注册 */
    if ( (RRC_EST_SUCCESS == pRrcEstCnf->ulResult)
      || (RRC_EST_PRESENT == pRrcEstCnf->ulResult))
    {

        /* 设置DETACH类型，否则在收到REL时候，不回复MMC的DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;             /* 设置信令连接已存在                       */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                        /* RR连接建立成功                           */

        /* 填写消息,发送IMSI detach消息 */
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);

        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);
        Mm_TimerStart(MM_TIMER_T3220);                                      /* 启动T3220                                */


        return;
    }

    /* MM进行本地DETACH */
    NAS_MM_LocalDetach();

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedGmmProcUserDetach
 功能描述  : 用来判别是否由GMM来处理用户发起的CS/CS+PS的detach
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE          -- 不需要GMM进行处理用户发起的CS/CS+PS的detach
             VOS_TRUE           -- 需要GMM进行处理用户发起的CS/CS+PS的detach
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedGmmProcUserDetach(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前网络模式 */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取当前的网络信息 */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;


    /* 非网络模式I下，不用GMM处理用户发起的detach */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* PS域不准许注册，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* PS域注册首限，不用GMM处理用户发起的detach */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }

    /* PS 卡无效，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* 当前小区是否支持GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_FALSE;
    }

    /* 当前小区是否在FORB GPRS PLMN里面 */

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_FALSE;
    }

    /* MM已处于ATTACHED状态，但当前GS接口不存在 */
    if ( (VOS_FALSE          == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState) )
    {
        return VOS_FALSE;
    }

    /* 否则用户发起的CS域的DETACH，可由GMM进行处理 */
    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MM_IsLauNeeded_NetModeChange
 功能描述  : 用来判别是否由GMM来处理用户发起的CS/CS+PS的detach
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE          -- 不需要LAU
             VOS_TRUE           -- 需要LAU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsLauNeeded_NetModeChange(VOS_VOID)
{
    /* LAI改变，需要触发LAU */
    if (VOS_TRUE == NAS_MML_IsCsLaiChanged())
    {
        return VOS_TRUE;
    }

    /* LAI/RAC都没改变 */
    if (g_MmGlobalInfo.MsCsInfo.ucOldRac == NAS_MML_GetCurrCampRac())
    {
        return VOS_FALSE;
    }

    /* 开机W下联合注册但PS ONLY成功，后模式改变为II，也需要LAU */
    if ( (MM_ATT_NEED  == g_MmGlobalInfo.ucAttFlg)
      && (MM_TRUE      == g_MmGlobalInfo.ucPowerOnFlg) )
    {
        return VOS_TRUE;
    }

    /* I->II, GS口存在，需要LAU */
    if ( (VOS_FALSE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
      && (VOS_TRUE  == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg) )
    {
        return VOS_TRUE;
    }

    /* 其他不需要触发LAU  */
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MM_IsEmergencyCallEndTrigLau
 功能描述  : 紧急呼被释放后，检测是否立即需要发起LAU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE          -- 不需要立即发起LAU
             VOS_TRUE           -- 需要立即发起LAU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数
                 CS未注册下，紧急呼时用户下发ATTACH,链接释放，当前有PS业务，需要发起LAU。
  2.日    期   : 2013年8月28日
    作    者   : l65478
    修改内容   : DTS2013082607368:限制驻留在禁止的网络上,CS业务结束后发起了LU

*****************************************************************************/
VOS_UINT32 NAS_MM_IsEmergencyCallEndTrigLau(VOS_VOID)
{
    VOS_UINT8                           ucEmergencyServiceFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;
    VOS_UINT8                           ucSimCsRegStatus;                       /* SIM卡CS域的注册结果导致的卡是否有效VOS_TRUE:CS域的卡有效,VOS_FALSE:CS域的卡无效*/
    VOS_UINT8                           ucRestrictRegister;                     /*是否限制注册 */

    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo         = VOS_NULL_PTR;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus       = VOS_NULL_PTR;

    pstConnStatus         = NAS_MML_GetConnStatus();
    pstCampInfo           = NAS_MML_GetCurrCampPlmnInfo();
    ucEmergencyServiceFlg = NAS_MML_GetCsEmergencyServiceFlg();
    ucCsAttachAllowFlg    = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus      = NAS_MML_GetSimCsRegStatus();
    ucRestrictRegister    = NAS_MML_GetCsRestrictRegisterFlg();

    /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
       判断如果当前有PS业务，需要发起LAU */
    if ( (VOS_TRUE            == pstConnStatus->ucRrcStatusFlg)
      && (VOS_TRUE            == ucEmergencyServiceFlg)
      && (MM_STATUS_DETACHED  == g_MmSubLyrShare.MmShare.ucCsAttachState)
      && (VOS_TRUE            == ucCsAttachAllowFlg)
      && (VOS_TRUE            == ucSimCsRegStatus)
      && (VOS_FALSE           == ucRestrictRegister)
      && (MM_TIMER_RUNNING    != gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
      && (MM_TIMER_RUNNING    != gstMmTimer[MM_TIMER_T3211].ucTimerStatus )
      && (NAS_MML_NET_MODE_II  == pstCampInfo->enNetworkMode)
      && ((MMCMM_NO_FORBIDDEN            == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
       || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)))
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MM_RelEstingMmConn
 功能描述  : 释放当前正在建立的MM连接的TI
 输入参数  : ulRelCause         -- 释放原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数
                 Mm_Cell_S9_E33降圈复杂度。
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  3.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_RelEstingMmConn(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause
)
{
        NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(ulRelCause);

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
    {
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                       enMmCcRelCause);            /* 通知CC,MM连接建立失败                    */


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* 清除正在建立的MM连接的标志               */
    }

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
    {                                                                   /* 是SS正在建立的MM连接                     */
        Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                        enMmCcRelCause);


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* 清除正在建立的MM连接的标志               */
    }

    if ( NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
    {                                                                   /* 是SMS正在建立的MM连接                    */
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        enMmCcRelCause);                                          /* 通知SS,MM连接建立失败                    */


        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;                                          /* 清除正在建立的MM连接的标志               */
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_RelBufferedServiceEstReq
 功能描述  : 释放MM当前缓存的CS业务建立请求
 输入参数  : ulRelCause         -- 释放原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数
                 Mm_Cell_S14_E33降圈复杂度。
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  3.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_RelBufferedServiceEstReq(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
    {                                                                           /* 有等待的CC触发的需要建立的MM连接         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg
            = MM_FALSE;

        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
             enMmCcRelCause);                          /* 通知CC建立失败                           */
    }
    if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
    {                                                                           /* 有等待的SMS触发的需要建立的MM连接         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                RcvXXEstReq.ucFlg = MM_FALSE;
        Mm_SndSmsRelInd(
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
            .RcvXXEstReq.ulTransactionId,
            enMmCcRelCause);
    }
    if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                RcvXXEstReq.ucFlg )
    {                                                                           /* 有等待的SS触发的需要建立的MM连接         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                RcvXXEstReq.ucFlg = MM_FALSE;

        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall
 功能描述  : 释放MM当前缓存的除紧急呼叫的CS业务建立请求
 输入参数  : ulRelCause         -- 释放原因
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause
)
{
    if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
     && (MMCC_MO_NORMAL_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType))
    {
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
             enMmCcRelCause);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
            enMmCcRelCause);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       enMmCcRelCause);
    }

    return;

}



/*****************************************************************************
 函 数 名  : NAS_MM_NotifyBufferedServiceRRConnNotExist
 功能描述  : 有缓存CS业务时，通知MMC/GMM当前RR链接不存在
 输入参数  : ulRelCause         -- 释放原因
 输出参数  : 无
 返 回 值  : VOS_FALSE          -- 释放失败
             VOS_TRUE           -- 释放成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : w00167002
    修改内容   : 新生成函数
                 Mm_Cell_S10_E33降圈复杂度。

*****************************************************************************/
VOS_UINT32 NAS_MM_NotifyBufferedServiceRRConnNotExist(VOS_VOID)
{
    VOS_UINT8                           ucTiValidFlg;

    if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                  .RcvXXEstReq.ucFlg)
      || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                  .RcvXXEstReq.ucFlg)
      || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                  .RcvXXEstReq.ucFlg))
    {
        ucTiValidFlg = Mm_ComTiChk();
        if ( MM_FALSE == ucTiValidFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;

}



/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedNormLu
 功能描述  : 判断是否需要由MM自己做LAU
 输入参数  :
 输出参数  :
 返 回 值  : VOS_FALSE          不需要
             VOS_TRUE           需要

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2013年09月03日
    作    者   : l65478
    修改内容   : DTS2013041602825:CSFB连接建立失败后没有发起LU
*****************************************************************************/
VOS_UINT32 NAS_MM_IsDisableGprsCombineAttach(VOS_VOID)
{

    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 获取当前网络模式 */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* 获取当前的网络信息 */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;

    /* CS域注册受限，MM不需要做LAU */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }


    /* 非网络模式I下，MM需要自己做LAU */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_TRUE;
    }

    /* PS域不准许注册，MM需要自己做LAU */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_TRUE;
    }

    /* PS域注册首限，MM需要自己做LAU */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_TRUE;
    }

    /* PS 卡无效，不用GMM处理用户发起的detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_TRUE;
    }

    /* 当前小区是否支持GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_TRUE;
    }

    /* 当前小区是否在FORB GPRS PLMN里面 */
    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RestartT3240_WaitForNetworkCommand
 功能描述  : WaitForNetworkCommand状态重启T3240
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RestartT3240_WaitForNetworkCommand(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus       = VOS_NULL_PTR;
    VOS_UINT32                          ulIsTestCard;
    VOS_UINT8                           ucSupportCsServiceFlg;                  /* 是否支持cs语音业务包括普通语音和vp业务，VOS_TRUE:支持cs语音业务；VOS_FALSE:不支持cs语音业务*/
    VOS_UINT8                           ucCsServiceConnStatusFlg;

    pstConnStatus            = NAS_MML_GetConnStatus();
    ulIsTestCard             = NAS_USIMMAPI_IsTestCard();
    ucSupportCsServiceFlg    = NAS_MML_GetSupportCsServiceFLg();
    ucCsServiceConnStatusFlg = pstConnStatus->ucCsServiceConnStatusFlg;

    /* 停T3240 */
    Mm_TimerStop( MM_TIMER_T3240 );

    /* 当前测试卡，当前设置为不支持CS业务，当前有CS业务，则设置T3240最大值 */
    if ( (VOS_TRUE  == ulIsTestCard)
      && (VOS_FALSE == ucSupportCsServiceFlg)
      && (VOS_TRUE  == ucCsServiceConnStatusFlg) )
    {
        gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_MAX_VALUE;
        Mm_TimerStart( MM_TIMER_T3240 );
        gstMmTimer[MM_TIMER_T3240].ulTimerLen = MM_TIMER_T3240_VALUE;
    }
    else
    {
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动T3240                                  */
    }

}
/*****************************************************************************
 函 数 名  : NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending
 功能描述  : MM状态恢复到先前状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending(VOS_VOID)
{
    VOS_UINT8                           ucPreMmState;

    ucPreMmState  = g_MmGlobalInfo.ucPreState;

    /* CS卡无效的状态迁移 */
    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
    {
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        return;
    }

    /* CS不准许注册的状态迁移 */
    if ( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg() )
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    /* 当前禁止注册的状态迁移 */
    if ( (MMCMM_NO_FORBIDDEN            != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
      && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    /* CS域受限的状态迁移 */
    if ( VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg() )
    {
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        return;
    }

    /* MM先前是MM_IDLE_NORMAL_SERVICE状态，则更新当前状态为MM_IDLE_NORMAL_SERVICE */
    if ( MM_IDLE_NORMAL_SERVICE == ucPreMmState )
    {
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        return;
    }

    /* MM先前是MM_IDLE_ATTEMPTING_TO_UPDATE状态，则更新当前状态为MM_IDLE_ATTEMPTING_TO_UPDATE */
    if ( MM_IDLE_ATTEMPTING_TO_UPDATE == ucPreMmState )
    {
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        return;
    }

    /* 统一迁移到MM_IDLE_ATTEMPTING_TO_UPDATE状态 */
    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

}



/*****************************************************************************
 函 数 名  : NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject
 功能描述  : LAU时被立即指派被拒，清除缓存的普通CC呼叫，不需要重播
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  3.日    期   :2013年12月9日
    作    者   :w00242748
    修改内容   :DTS2013120502018:MM模块发送给SMS短消息的被拒原因值不对，修改
                该函数为判断是否存在缓存的CS Service
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject()
{
    /* 根据缓存业务的类型，获取相应的函数指针以及TransActionId */
    if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
      && (MMCC_MO_NORMAL_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType) )
    {
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT);
    }

    /* 通知MMC，CS域的业务已经停止 */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_
 功能描述  : 链接释放网络模式I下处理LAU请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月13日
    作    者   : z00234330
    修改内容   : 新生成函数
  2.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_NetModeI( VOS_VOID )
{
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    if ( MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac )
    {                                                               /* RAC为0的场合                             */
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_ComChkLu:INFO: MmLikeB is MM_TRUE");
        if ( ( MMCMM_NO_FORBIDDEN !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) &&
            ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
        {
            if ( MMCMM_FORBIDDEN_PLMN
                == (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                )
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_CheckLuAfterCsConnectNotExist:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            }
            else if ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                    & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
                )
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);

                 Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);
                 /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState =
                    MM_LIMITED_SERVICE;                             /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);

                Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
            }
        }
        else
        {
           g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
           Mm_ComLuOnly();                                          /* LU REQ                                   */
           ucRet = MM_TRUE;
        }
    }

    return ucRet;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode
 功能描述  : 链接释放网络其他模式下处理LAU请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月13日
    作    者   : z00234330
    修改内容   : 新生成函数
  2.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode( VOS_VOID )
{                                                                   /* 非A+I模式                                */
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    if ( ( MMCMM_NO_FORBIDDEN !=
        g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) &&
        ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
        g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
    {                                                               /* 如果没有CS域禁止的信息                   */
        if ( MMCMM_FORBIDDEN_PLMN == ( MMCMM_FORBIDDEN_PLMN &
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_CheckLuAfterCsConnectNotExist:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else if ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);

            Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW);
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;   /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_CheckLuAfterCsConnectNotExist:INFO: MmServiceState is MM_LIMITED_SERVICE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);

            Mm_ComLuCauseHandle(NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW);
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
        Mm_ComLuOnly();                                             /* 发送LU REQ                               */
        ucRet = MM_TRUE;
    }

    return ucRet;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire
 功能描述  : 链接释放网络T3212超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月13日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire(
    VOS_UINT8                           ucPsRestrictionFlg
)
{
    VOS_UINT8                           ucRet;

    ucRet = MM_FALSE;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_IDLE_NORMAL_SERVICE:
        ucRet = MM_TRUE;

        if((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
            && (VOS_TRUE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* 设置LU类型                               */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型                               */
        }

        Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
        ucRet = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* 设置LU类型                               */
        Mm_ComLuOnly();                                                     /* 发送LU REQ                               */
        break;
    default:
        break;
    }

    return ucRet;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist
 功能描述  : 链接释放,rrc链接存在的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月13日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist( VOS_VOID )
{
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucFlg;

    ucRet = MM_FALSE;
    ucFlg = MM_FALSE;

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;

    g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_FALSE;

    switch ( g_MmGlobalInfo.ucState )
    {
    case MM_IDLE_NORMAL_SERVICE:
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
    case MM_IDLE_LIMITED_SERVICE:
    case WAIT_FOR_RR_CONNECTION_MM_CONNECTION:
        ucFlg = MM_TRUE;
        break;
    default:
        break;
    }
    if ( MM_TRUE == ucFlg )
    {
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
        {                                                                   /* 如果为A+I,且不是类似B或A+II处理的场合    */
            ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_NetModeI();
        }
        else
        {
            ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_OhterNetMode();
        }
    }

    return ucRet;
}



/*****************************************************************************
 函 数 名  : NAS_MM_ProcessLuAfterCsConnectNotExist
 功能描述  : CS连接释放或者连接建立失败后,检查是否发起LU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MM_FALSE: 不需要发起LU过程
             MM_TRUE:  需要发起LU过程
 调用函数  : 调用此函数前,由调用函数决定是否需要判断RRC连接是否存在;
             例如:如果是CSFB->GU,业务连接建立失败后要发起LU,不需要判断RRC状态;
                  如果是CS业务结束后,CS连接释放后要发起LU,需要判断RRC状态
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月03日
    作    者   : l65478
    修改内容   : 新生成函数

  2.日    期   : 2013年12月11日
    作    者   : z00234330
    修改内容   : dts2013121106833,降圈复杂度

*****************************************************************************/
VOS_UINT8 NAS_MM_ProcessLuAfterCsConnectNotExist(VOS_VOID)
{
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    ucRet = MM_FALSE;
    ucFlg = MM_FALSE;
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();


    if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
    {
        if ( ( MMCMM_FORBIDDEN_PLMN == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
          || ( MMCMM_FORBIDDEN_LA_FOR_ROAM == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
          || ( MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ))
        {
            return ucRet;
        }

        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        switch ( g_MmGlobalInfo.ucState )
        {
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LIMITED_SERVICE:
            ucFlg = MM_TRUE;
            break;
        default:
            break;
        }
        if  ( MM_NET_MODE_II == g_MmGlobalInfo.ucNtMod )
        {
            if (MM_TRUE == ucFlg)
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
                ucRet = MM_TRUE;
                return ucRet;
            }
        }
    }

    if (VOS_TRUE == NAS_MM_IsNeedLauCsSigRel())
    {
        ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_RrcExist();
    }
    else if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
    {
        ucRet = (VOS_UINT8)NAS_MM_ProcessLuAfterCsConnectNotExist_T3212Expire(ucPsRestrictionFlg);
    }
    else
    {

    }

    return ucRet;
}

/*****************************************************************************
 函 数 名  : NAS_MM_LogAuthInfo
 功能描述  : 勾MM的期望的鉴权信息
 输入参数  : VOS_VOID
 输出参数  : ucRcvOpId    : 消息中接受到的OPID
             ucExpectOpId : MM期望的OPID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月21日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
)
{
    NAS_MM_LOG_AUTH_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MM_LOG_AUTH_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_AUTH_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogAuthInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_AUTH_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_AUTH_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_AUTH_INFO_IND;
    pstMsg->ucExpectOpId                = ucExpectOpId;
    pstMsg->ucRcvOpId                   = ucRcvOpId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_LogMmCtxInfo
 功能描述  : 勾MM的全局变量值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_LogMmCtxInfo(VOS_VOID)
{
    MMOM_LOG_CTX_INFO_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg = (MMOM_LOG_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(MMOM_LOG_CTX_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogMmCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(MMOM_LOG_CTX_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMOM_LOG_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_CTX_INFO_IND;

    pstMsg->stMmGlobalInfo.ConnCtrlInfo_CC_RcvXXEstReq_ucFlg  = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.ConnCtrlInfo_SMS_RcvXXEstReq_ucFlg = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.ConnCtrlInfo_SS_RcvXXEstReq_ucFlg  = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg;
    pstMsg->stMmGlobalInfo.enPreRatType                       = g_MmGlobalInfo.enPreRatType;
    pstMsg->stMmGlobalInfo.LuInfo_ucT3212ExpiredFlg           = g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg;
    pstMsg->stMmGlobalInfo.MsCsInfo_ucOldRac                  = g_MmGlobalInfo.MsCsInfo.ucOldRac;
    pstMsg->stMmGlobalInfo.stDetachInfo_enDetachType          = g_MmGlobalInfo.stDetachInfo.enDetachType;
    pstMsg->stMmGlobalInfo.ucAttFlg                           = g_MmGlobalInfo.ucAttFlg;
    pstMsg->stMmGlobalInfo.ucLikeB                            = g_MmGlobalInfo.ucLikeB;
    pstMsg->stMmGlobalInfo.ucMmServiceState                   = g_MmGlobalInfo.ucMmServiceState;
    pstMsg->stMmGlobalInfo.ucNotCampONPreState                = g_MmGlobalInfo.ucNotCampONPreState;
    pstMsg->stMmGlobalInfo.ucNtMod                            = g_MmGlobalInfo.ucNtMod;
    pstMsg->stMmGlobalInfo.ucPowerOnFlg                       = g_MmGlobalInfo.ucPowerOnFlg;
    pstMsg->stMmGlobalInfo.ucPreState                         = g_MmGlobalInfo.ucPreState;
    pstMsg->stMmGlobalInfo.usRac                              = g_MmGlobalInfo.usRac;

#if (FEATURE_ON == FEATURE_ECALL)
    pstMsg->stMmlCtxInfo.enCallMode                           = NAS_MML_GetCallMode();
#else
    pstMsg->stMmlCtxInfo.enCallMode                           = NAS_MML_CALL_MODE_BUTT;
#endif
    pstMsg->stMmlCtxInfo.enCsfbServiceStatus                  = NAS_MML_GetCsfbServiceStatus();
    pstMsg->stMmlCtxInfo.enCsUpdateStatus                     = NAS_MML_GetCsUpdateStatus();
    pstMsg->stMmlCtxInfo.enT3423Status                        = NAS_MML_GetT3423Status();
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stAttemptUpdateLaiInfo, NAS_MM_GetAttemptUpdateLaiInfo(), sizeof(pstMsg->stMmlCtxInfo.stAttemptUpdateLaiInfo));
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stCsLastSuccLai, NAS_MML_GetCsLastSuccLai(), sizeof(pstMsg->stMmlCtxInfo.stCsLastSuccLai));
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stCurrCampLai, NAS_MML_GetCurrCampLai(), sizeof(pstMsg->stMmlCtxInfo.stCurrCampLai));
    pstMsg->stMmlCtxInfo.ucCsSecurityCksn                     = NAS_MML_GetSimCsSecurityCksn();
    pstMsg->stMmlCtxInfo.ucImsVoiceAvailFlg                   = NAS_MML_GetImsVoiceAvailFlg();
    pstMsg->stMmlCtxInfo.ucImsVoiceInterSysLauEnableFlg       = NAS_MML_GetImsVoiceInterSysLauEnableFlg();
    pstMsg->stMmlCtxInfo.ucStaOfRcvXXEstReqCsfb               = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

    pstMsg->stMmTimerInfo.ucT3211TimerStatus                  = gstMmTimer[MM_TIMER_T3211].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3212TimerStatus                  = gstMmTimer[MM_TIMER_T3212].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3213TimerStatus                  = gstMmTimer[MM_TIMER_T3213].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3242TimerStatus                  = gstMmTimer[MM_TIMER_T3242].ucTimerStatus;
    pstMsg->stMmTimerInfo.ucT3243TimerStatus                  = gstMmTimer[MM_TIMER_T3243].ucTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MM_GetEstCnfResult
 功能描述  : 获取MM模块建链失败原因值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : est cnf失败原因值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
RRC_NAS_EST_RESULT_ENUM_UINT32 NAS_MM_GetEstCnfResult(VOS_VOID)
{
    return g_MmGlobalInfo.enEstCnfResult;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetEstCnfResult
 功能描述  : 设置MM模块建链失败原因值
 输入参数  : est cnf失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstCnfResult)
{
    g_MmGlobalInfo.enEstCnfResult = enEstCnfResult;
}


/* Added by n00355355 for 呼叫重建, 2015-9-29, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_GetTransactionEnqSenderPid
 功能描述  : 获取MM TransactionEnq消息的SenderPid
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TransactionEnq消息的SenderPid
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月29日
    作    者   : n00355355
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetTransactionEnqSenderPid(VOS_VOID)
{
    return g_MmGlobalInfo.ulTransactionEnqSenderPid;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetTransactionEnqSenderPid
 功能描述  : 设置MM TransactionEnq消息的SenderPid
 输入参数  : est cnf失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
  1.日    期   : 2015年9月29日
    作    者   : n00355355
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_SetTransactionEnqSenderPid(
    VOS_UINT32                          ulSenderPid
)
{
    g_MmGlobalInfo.ulTransactionEnqSenderPid = ulSenderPid;

    return;
}

/* Added by n00355355 for 呼叫重建, 2015-9-29, end */

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf
 功能描述  : 收到lau建立链接结果判定是否需要处理缓存的cs detach消息
 输入参数  : enEstCnfResult - 建链结果
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要
             VOS_FALSE:不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult
)
{
    /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4章节描述:If a RR connection
        exists and the ATT flag indicates that no detach procedure is required,
        the MM sublayer will release locally any ongoing MM connections before
        releasing the RR connection. If a MM specific procedure is active,
        the release of the RR connection may be delayed until the MM specific
        procedure is complete. lau结束后连接释放时再做本地detach,如果lau建链失败则做本地detach */
    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
    {
        if ((RRC_EST_SUCCESS != enEstCnfResult)
         && (RRC_EST_PRESENT !=enEstCnfResult))
        {
            return VOS_TRUE;
        }

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ClearAuthInfo
 功能描述  : 清除鉴权相关信息
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月21日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_ClearAuthInfo(VOS_VOID)
{
    g_MmGlobalInfo.AuthenCtrlInfo.ucAuthenAttmptCnt = 0;
    g_MmGlobalInfo.AuthenCtrlInfo.ucLastFailCause   = MM_AUTHEN_NO_CAUSE;

    g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat      = MM_AUTHEN_RAND_DIFFER;

    /* 24.008 4.3.2.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3218, if running, shall be stopped:
    -   if the mobile station enters the MM state MM IDLE or NULL.
    */
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();

    if (MM_RCV_AUTH_CNF_FLG == (MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    }

    if ((VOS_TRUE == NAS_MML_GetNwIgnoreAuthFailCfg())
     && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3216].ucTimerStatus))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ClearAuthInfo: Clear CKSN and Stop T3216");
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        Mm_TimerStop(MM_TIMER_T3216);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired
 功能描述  : 保护CSFB后携带CSMT标志定时器超时，则清除FLG标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年4月28日
    作    者   : w00167002
    修改内容   : csmt modify
  3.日    期   : 2015年6月01日
    作    者   : j00174725
    修改内容   : DTS2015053000044
  4.日    期   : 2015年10月16日
    作    者   : j00174725
    修改内容   : DTS2015101603066
  5.日    期   : 2016年2月2日
    作    者   : z00359541
    修改内容   : DTS2016011809099:不需要发送CSFB ABORT消息打断状态机，收到PLMN SERACH IND消息时会打断
*****************************************************************************/
VOS_VOID NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRcvPid;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    ulRet            = VOS_ERR;
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();

    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);


    if (MM_INTER_RAT_CHANGE == Mm_GetState())
    {
        if ( (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
          && (NAS_MML_NET_RAT_TYPE_LTE             == enCurrNetRatType) )
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            /* 通知L CSFB 流程终止 */
            NAS_MM_SndLmmCsfbServiceAbortNotify();
        }
    }

    /* 通知接入层TRANSACTION状态 */
    ulRet = NAS_MM_GetRrcPidFromCurrRatType(&ulRcvPid);
    if (VOS_OK == ulRet)
    {
        NAS_MM_SndRrcTransactionStatusNotify(ulRcvPid, RRMM_TRANSACTION_FAIL);
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

#if (FEATURE_ON == FEATURE_PTM)
    /* 如果CS信令链接不存在，则记录CSFB MT异常 */
    if (VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
    {
        NAS_MM_CsfbMtFailRecord();
    }
#endif

    /* 如果MMC正在搜网时业务结束，通知MMC停止搜GU，重新从LTE开始搜网;如果MMC处于ON PLMN启高优先级接入技术BG搜定时器 */
    NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);

    return;
}



/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired
 功能描述  : MM在HO流程获取CS安全上下文超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired(VOS_VOID)
{
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
    {
        /* 向MMC回复挂起rsp */
        NAS_MM_SndMmcSuspendRsp();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetSrvccFlg
 功能描述  : 获取MM模块在SRVCC过程标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_GetSrvccFlg(VOS_VOID)
{
    return g_MmGlobalInfo.ucSrvccFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetSrvccFlg
 功能描述  : 设置MM模块在SRVCC过程标记
 输入参数  : ucFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_SetSrvccFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.ucSrvccFlg = ucFlg;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */

/*****************************************************************************
 函 数 名  : NAS_MM_GetRcvSrvccCallInfoFlg
 功能描述  : 获取MM模块在SRVCC过程收到CC同步CALLINFO标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_GetRcvSrvccCallInfoFlg(VOS_VOID)
{
    return g_MmGlobalInfo.ucRcvSrvccCallInfoFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetRcvSrvccCallInfoFlg
 功能描述  : 设置MM模块在SRVCC过程收到CC同步CALLINFO标记
 输入参数  : ucFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_SetRcvSrvccCallInfoFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.ucRcvSrvccCallInfoFlg = ucFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertToLmmSrvccStatus
 功能描述  : 把MM的SRVCC状态转换为LMM的格式
 输入参数  : enSrvccStatus---MM格式的SRVCC状态
 输出参数  : penMmlSrvccStatus--LMM格式的SRVCC状态
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ConvertToLmmSrvccStatus(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus,
    MM_LMM_SRVCC_STATUS_ENUM_UINT32    *penMmlSrvccStatus
)
{
    switch(enSrvccStatus)
    {
        case NAS_MMCC_SRVCC_STATUS_START:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_START;
            break;
        case NAS_MMCC_SRVCC_STATUS_SUCCESS:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_SUCC;
            break;
        case NAS_MMCC_SRVCC_STATUS_FAIL:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_FAIL;
            break;
        default:
            *penMmlSrvccStatus = MM_LMM_SRVCC_STATUS_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedSetCsmtFlg
 功能描述  : 判断是否需要携带CSMT标志
 输入参数  : 无
 输出参数  : VOS_TRUE :需要携带CSMT
             VOS_FALSE:不需要携带CSMT
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月25日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年5月5日
    作    者   : b00269685
    修改内容   : csmt修改
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedSetCsmtFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsfbMtFlg;

    ucCsfbMtFlg = NAS_MM_GetCsfbMtLauFlg();

    /* 存在CSMT标志，则需要携带CSMT标志 */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
      || (VOS_TRUE                             == ucCsfbMtFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedSetCsmoFlg
 功能描述  : 判断是否需要携带CSMO标志
 输入参数  : 无
 输出参数  : VOS_TRUE :需要携带CSMO
             VOS_FALSE:不需要携带CSMO
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月25日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2016年1月9日
    作    者   : z00359541
    修改内容   : DTS2015111402223:增加小区是否支持CSMO标识
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedSetCsmoFlg(VOS_VOID)
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucCellNotSupportCsmoFlg;
    VOS_UINT8                           ucCsfbMoSetupFlg;

    ucCsmoSupportedFlg      = NAS_MML_GetCsmoSupportedFlg();
    ucCellNotSupportCsmoFlg = NAS_MML_GetCellNotSupportCsmoFlg();
    ucCsfbMoSetupFlg        = NAS_MML_GetCsfbMoSetupFlg();

    NAS_NORMAL_LOG3(WUEPS_PID_MM,
        "NAS_MM_IsNeedSetCsmoFlg: ucCsmoSupportedFlg, ucCellNotSupportCsmoFlg, ucCsfbMoSetupFlg",
        ucCsmoSupportedFlg, ucCellNotSupportCsmoFlg, ucCsfbMoSetupFlg);

    /* 当前配置支持CSMO，且当前存在CSMO业务 */
    if ((VOS_TRUE == ucCsmoSupportedFlg)
     && (VOS_FALSE == ucCellNotSupportCsmoFlg)
     && (VOS_TRUE == ucCsfbMoSetupFlg))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_IsNeedSetCsmoFlg: Need to set CSMO");
        return VOS_TRUE;
    }

    /* 否则不携带CSMO 标志 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_SetCsfbAdditionalUpdateParameters
 功能描述  : 设置AdditionalUpdateParameters
 输入参数  : pusMsgSize  :当前消息的长度
             pucSndMsg   : 发送消息地址
 输出参数  : pusMsgSize  :当前消息的长度
             pucSndMsg   : 发送消息地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_SetCsfbAdditionalUpdateParameters(
    VOS_UINT8                           ucCsmtFlg,
    VOS_UINT8                           ucCsmoFlg,
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
)
{
    VOS_UINT16                          usIdx;

    usIdx       = *pusMsgSize;

    /* 同时携带CSMT/CSMO标志 */
    if ( (VOS_TRUE == ucCsmtFlg)
      && (VOS_TRUE == ucCsmoFlg) )
    {
        /* 设置CS fallback mobile terminating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMT_FLAG_EXIST;

        /* 设置CS fallback mobile originating call */
        pucSndMsg[usIdx]    |= MM_IE_CSFB_CSMO_FLAG_EXIST;

        /* 设置ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* 消息长度增加 */
        (*pusMsgSize) ++;

        return;
    }

    /* 携带CSMT标志 */
    if (VOS_TRUE == ucCsmtFlg)
    {
        /* 设置CS fallback mobile terminating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMT_FLAG_EXIST;

        /* 设置ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* 消息长度增加 */
        (*pusMsgSize) ++;

        return;
    }

    /* 携带CSMO标志 */
    if (VOS_TRUE == ucCsmoFlg)
    {
        /* 设置CS fallback mobile originating call */
        pucSndMsg[usIdx]    = MM_IE_CSFB_CSMO_FLAG_EXIST;

        /* 设置ADDITIONAL UPDATE PARAMETERS IEI */
        pucSndMsg[usIdx]    |= MM_IEI_ADDITIONAL_UPDATE_PARAMETERS;

        /* 消息长度增加 */
        (*pusMsgSize) ++;

        return;
    }

    /* 不需要携带CSMT/CSMO标志 */
    return;
}



#endif

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq
 功能描述  : 判断是否需要在lau请求中封装MS network feature support IE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq(VOS_VOID)
{
    VOS_UINT8                          ucIsNeedSetCsmoFlg;
    VOS_UINT8                          ucIsNeedSetCsmtFlg;

    ucIsNeedSetCsmoFlg = NAS_MM_IsNeedSetCsmoFlg();
    ucIsNeedSetCsmtFlg = NAS_MM_IsNeedSetCsmtFlg();


    /* 24008_CR1821R6_(Rel-10)_C1-113736-was-3626-24008-a30 9.2.15章节描述如下:
    9.2.15.6    MS network feature support
    This IE shall be included if the MS supports extended periodic timer T3212 and
    the Additional update parameters IE is not included. */
    if ((PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
     && (VOS_FALSE == ucIsNeedSetCsmoFlg)
     && (VOS_FALSE == ucIsNeedSetCsmtFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetMsNetworkFeatureSupportIE
 功能描述  : 设置MS network feature support IE
 输入参数  : pusMsgSize  :当前消息的长度
             pucSndMsg   : 发送消息地址
 输出参数  : pusMsgSize  :当前消息的长度
             pucSndMsg   : 发送消息地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_SetMsNetworkFeatureSupportIE(
    VOS_UINT16                         *pusMsgSize,
    VOS_UINT8                          *pucSndMsg
)
{
    VOS_UINT16                          usIdx;

    usIdx  = *pusMsgSize;

    /* 24008_CR1821R6_(Rel-10)_C1-113736-was-3626-24008-a30 9.2.15章节描述如下:
    9.2.15.6    MS network feature support
    This IE shall be included if the MS supports extended periodic timer T3212 and
    the Additional update parameters IE is not included. */
    pucSndMsg[usIdx]    = MM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN;

    /* 设置MS NETWORK FEATURE SUPPORT IEI */
    pucSndMsg[usIdx]    |= MM_IEI_MS_NETWORK_FEATURE_SUPPORT;

    /* 消息长度增加 */
    (*pusMsgSize) ++;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_GetCsfbMtLauFlg
 功能描述  : 获取MM模块在CsfbMtLau过程标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_GetCsfbMtLauFlg(VOS_VOID)
{
    return g_MmGlobalInfo.LuInfo.ucCsfbMtLauFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetCsfbMtLauFlg
 功能描述  : 设置MM模块在CsfbMtLau过程标记
 输入参数  : ucFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_SetCsfbMtLauFlg(
    VOS_UINT8                           ucFlg
)
{
    g_MmGlobalInfo.LuInfo.ucCsfbMtLauFlg = ucFlg;
}






/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */

/*****************************************************************************
 函 数 名  : Mm_IsMultiSrvCollisionAllow
 功能描述  : 多业务冲突处理流程，处理包括
             1. 两个不同类型MO请求冲突处理
             2. 一个MT进行时，再来一个MO业务请求时冲突处理

 输入参数  : ucMmConnCtrl -- 当前请求的业务类型

 输出参数  : 无


 返 回 值  : VOS_TRUE  -- 当前业务请求允许
             VOS_FALSE -- 当前业务请求不允许

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月21日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年2月21日
    作    者   : y00245242
    修改内容   : 移dts201412901179函数处理到该函数中处理
*****************************************************************************/
VOS_UINT32 Mm_IsMultiSrvCollisionAllow(NAS_MM_CONN_CTRL_ENUM_UINT8  ucMmConnCtrl)
{
    if ((WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_OUTGOING_MM_CONNECTION      == g_MmGlobalInfo.ucState)
     || (WAIT_FOR_NETWORK_COMMAND             == g_MmGlobalInfo.ucState))
    {
        /* 当前有一个被叫业务正在进行 */
        if (MM_MT_PAGING == g_MmGlobalInfo.ucPagingType)
        {
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                /* 当前网络如果为GSM，拒绝当前的MO呼叫业务请求，原因: GSM业务请求在业务链接建立阶段，
                 * 无法知道当前的业务类型
                 */
                if (MM_CONN_CTRL_CC == ucMmConnCtrl)
                {
                    return VOS_FALSE;
                }

                return VOS_TRUE;
            }
            else
            {
                if ((MM_CONN_CTRL_CC                                 == ucMmConnCtrl)
                 && (RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL          == g_MmGlobalInfo.ucPagingCause))
                {
                    /* 如果当前MO业务请求为呼叫业务且MT业务请求也是呼叫，拒绝当前的MO业务 */
                    return VOS_FALSE;
                }
                else
                {
                    /* 其他场景,允许当前业务发起 */
                    return VOS_TRUE;
                }
            }
        }

        /* 下面是为了规避多个MO业务请求同时到来时的处理流程
         *
         * 注: 未来高版本，可以考虑根据T3246定时器方式来处理(Ref: section 4.5.1.1/4.5.1.2
         *     in 24.008 version 10.6.1)
         */
        if (WAIT_FOR_NETWORK_COMMAND != g_MmGlobalInfo.ucState)
        {
            if ((MM_IE_PD_NON_CALL_RLT_SS_MSG == g_MmGlobalInfo.ucMMConnEstingPD)
             && (MM_CONN_CTRL_CC              == ucMmConnCtrl))
            {
                /* 当前一个MO SS业务请求正在建立，如果收到呼叫业务请求，拒绝当前呼叫业务请求 */
                return VOS_FALSE;
            }
            else if ((MM_IE_PD_CALL_CONTROL   == g_MmGlobalInfo.ucMMConnEstingPD)
                  && (MM_CONN_CTRL_SS         == ucMmConnCtrl))
            {
                /* 当前一个MO 呼叫业务请求正在建立，如果收到补充业务请求，拒绝当前补充业务请求 */
                return VOS_FALSE;
            }
            else
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_TRUE;
}



/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow
 功能描述  : CS不允许attach时对MMC转发给MM的系统消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow( VOS_VOID )
{
    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    if ((VOS_TRUE           == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I      == g_MmGlobalInfo.ucNtMod)
     && (MM_UNSUPPORT_GPRS  == g_MmGlobalInfo.usRac))
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);


    Mm_DealWithBuffMsg();

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_IsCsForbidden
 功能描述  : 判断系统消息指示CS域是否forbidden
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前系统消息指示CS域forbidden
             VOS_FALSE:当前系统消息指示CS域非forbidden
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_IsCsForbidden( VOS_VOID )
{
    if ((MMCMM_NO_FORBIDDEN            == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
     || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsCsNotSupport
 功能描述  : 判断系统消息指示CS域是否支持
 输入参数  : 系统消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前系统消息指示CS域不支持
             VOS_FALSE:当前系统消息指示CS域支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年6月11日
    作    者   : b00269685
    修改内容   : 区分ota 和 sys
*****************************************************************************/
VOS_UINT8 NAS_MM_IsCsNotSupport(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstWSysInfoInd = VOS_NULL_PTR;                    /* 定义接收到的消息类型指针                 */

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        pstWSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;                                                      /* 消息转换                                */

        if ((0 == pstWSysInfoInd->ucCsInfoSize)
         && (MMC_MM_SYS_INFO_TYPE_SYS == pstWSysInfoInd->enSysInfoType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict
 功能描述  : CS限制注册时对MMC转发给MM的系统消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict( VOS_VOID )
{
    Mm_TimerStop(MM_TIMER_T3210);
    Mm_TimerStop(MM_TIMER_T3211);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmlLaiFormatToMMFormat
 功能描述  : 将MML格式的LAI信息转换成MM格式的LAI信息
 输入参数  : pstSrcLai------------MML格式的LAI信息
 输出参数  : pstDstLai------------MM格式的LAI信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmlLaiFormatToMMFormat(
    NAS_MML_LAI_STRU                   *pstSrcLai,
    MM_LAI_STRU                        *pstDstLai
)
{
    pstDstLai->PlmnId.ulMcc = pstSrcLai->stPlmnId.ulMcc;
    pstDstLai->PlmnId.ulMnc = pstSrcLai->stPlmnId.ulMnc;

    pstDstLai->ulLac        = (pstSrcLai->aucLac[0]<< 8) & 0xFF00;
    pstDstLai->ulLac        |= pstSrcLai->aucLac[1];

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_CheckMmcMmSysInfoIE
 功能描述  : 检查MMC转发给MM的系统消息合法性
 输入参数  : MMC转发给MM的系统消息
 输出参数  : 无
 返 回 值  : VOS_TRUE:系统消息检查通过
             VOS_FALSE:系统消息检查不通过
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月4日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_CheckMmcMmSysInfoIE(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstWSysInfoInd = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pstGSysInfoInd = VOS_NULL_PTR;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pstGSysInfoInd = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

        /* 判断是否为 GSM 的系统信息指示消息 */
        if (MMCMM_GSM_SYS_INFO_IND != pstGSysInfoInd->MsgHeader.ulMsgName)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        pstWSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;

        /* 判断是否为 WCDMA 的系统信息指示消息 */
        if (MMCMM_SYS_INFO_IND != pstWSysInfoInd->MsgHeader.ulMsgName)
        {
            return VOS_FALSE;
        }

        if ((MM_CONST_NUM_8 < pstWSysInfoInd->ucCnCommonSize)
         || (MM_CONST_NUM_8 < pstWSysInfoInd->ucCsInfoSize))
        {                                                                           /* 消息中的取值不合法                       */
            return VOS_FALSE;                                                       /* 返回消息检查失败                         */
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateT3212Value_RcvLauAccept
 功能描述  : 更新T3212定时器时长
 输入参数  : ucTimerName     - 定时器名称
             ucMsgTimerValue - 消息中定时器值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_UpdateT3212Value_RcvLauAccept(
    VOS_UINT8                            ucMsgTimerValue
)
{
    VOS_UINT8                            ucTimerUnit;                                                   /* 定义临时变量存储时长单位                 */
    VOS_UINT8                            ucTimerValue;                                                   /* 定义临时变量存储时长                     */

    ucTimerUnit     = 0;
    ucTimerValue    = 0;
    ucTimerUnit     = (VOS_UINT8)(ucMsgTimerValue >> NAS_MML_OCTET_MOVE_FIVE_BITS);
    ucTimerValue    = (VOS_UINT8)(ucMsgTimerValue & NAS_MML_OCTET_LOW_FIVE_BITS);

    /* 24008 10.5.163a章节描述如下:
    GPRS Timer 3 value (octet 3)
    Bits 5 to 1 represent the binary coded timer value.
    Bits 6 to 8 defines the timer value unit for the GPRS timer as follows:
    Bits
    8 7 6
    0 0 0 value is incremented in multiples of 10 minutes
    0 0 1 value is incremented in multiples of 1 hour
    0 1 0 value is incremented in multiples of 10 hours
    0 1 1 value is incremented in multiples of 2 seconds
    1 0 0 value is incremented in multiples of 30 seconds
    1 0 1 value is incremented in multiples of 1 minute
    1 1 1 value indicates that the timer is deactivated.

    Other values shall be interpreted as multiples of 1 hour in this version of the protocol.
    */
    switch (ucTimerUnit)
    {
        case 0:
            /* 10分钟 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 10 * 60 * 1000);
            break;

        case 1:
            /* 1小时 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 60 * 1000);
            break;

        case 2:
            /* 10小时 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 10 * 60 * 60 * 1000);
            break;

        case 3:
            /* 2秒 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 2 * 1000);
            break;

        case 4:
            /* 30秒 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 30 * 1000);
            break;

        case 5:
            /* 1分钟 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 1000);
            break;

        case 7:
            /* timer is deactivated */
            NAS_MM_SetNetworkAllocT3212Len(0);
            break;

        default:
            /* 1小时 */
            NAS_MM_SetNetworkAllocT3212Len(ucTimerValue * 60 * 60 * 1000);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo
 功能描述  : 收到gu系统消息是否需要更新T3212定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE - 需要更新
             VOS_TRUE - 不需要更新
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月8日
   作    者   : z00161729
   修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo(VOS_VOID)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo  = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo  = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstNetWorkInfo             = NAS_MML_GetNetworkInfo();

    /* 如果协议版本小于R11,返回需要根据系统消息更新T3212定时器时长 */
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }

    /* 如果之前下发T3212定时器时长的网络接入技术与当前驻留网络的接入技术不同，返回需要更新T3212时长 */
    if (pstAllocT3212ValueLaiInfo->enCampPlmnNetRat != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 如果之前下发T3212定时器时长的网络与当前驻留的网络lai不同，则返回需要更新T3212时长 */
    if (VOS_FALSE == NAS_MML_CompareLai(&pstNetWorkInfo->stCampPlmnInfo.stLai, pstAllocT3212ValueLaiInfo))
    {
        return VOS_TRUE;
    }

    /* 之前下发T3212时长的网络lai与当前驻留网络lai相同，且之前网络不是通过lau accept下发的，则返回需要更新T3212时长 */
    if (NAS_MM_T3212_VALUE_TYPE_NONE_BROADCAST != NAS_MM_GetNetworkT3212ValueType())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_UpdateT3212Value_RcvGuSysInfo
 功能描述  : 收到GU下的系统消息更新T3212的时长
 输入参数  : ucLRTimerT3212-------GU的系统消息中携带的T3212时长
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_UpdateT3212Value_RcvGuSysInfo(
    VOS_UINT8                           ucLRTimerT3212
)
{
    VOS_UINT32                          ulT3212Value;

    /* 从收到的消息结构中获取新的 T3212 定时长度 */
    ulT3212Value    = ucLRTimerT3212 * MM_T3212_UNIT_TRANSFORM;     /* 6分钟->毫秒 */

    if (ulT3212Value > MM_TIMER_T3212_MAX_VALUE)
    {
        ulT3212Value = MM_TIMER_T3212_MAX_VALUE;
    }

    /* 对定时长度分析处理 */
    if ((MM_CONST_NUM_0 == ulT3212Value)
     || (MM_CONST_NUM_0 == gstMmTimer[MM_TIMER_T3212].ulTimerLen))                /* 为零 */
    {
        /* 设置 T3212 定时长度为无效值 */
        gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulT3212Value;
        Mm_TimerStop(MM_TIMER_T3212);
    }
    else /* 正常值 */
    {
        if (gstMmTimer[MM_TIMER_T3212].ulTimerLen != ulT3212Value)
        {
            Mm_ComT3212(ulT3212Value);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateNetModeInfo_RcvGuSysInfo
 功能描述  : 收到GU下的系统消息更新网络模式信息
 输入参数  : ucNetworkOperationMode-------GU的系统消息中携带的网络模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(
    VOS_UINT8                           ucNetworkOperationMode
)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if (ucNetworkOperationMode < MM_CONST_NUM_4)
        {
            /* 网络模式信息有效 */
            if (MM_CONST_NUM_0 != ucNetworkOperationMode)
            {
                /* 获取 ucNewNtMod 值 */
                g_MmGlobalInfo.ucNewNtMod = ucNetworkOperationMode;
            }
            else
            {
                g_MmGlobalInfo.ucNewNtMod = MM_NET_MODE_II;
            }
        }
    }
    else
    {
        g_MmGlobalInfo.ucNewNtMod = ucNetworkOperationMode;

        /* 如果当前的网络被bar，那么直接刷新一下网络模式*/
        if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        {
             g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
        }
    }

    /* 如果当前网络模式未知,设置为新获取网络模式 */
    if (MM_CONST_NUM_0 == g_MmGlobalInfo.ucNtMod)
    {
        g_MmGlobalInfo.ucNtMod      = g_MmGlobalInfo.ucNewNtMod;
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MM_UpdateNetworkInfo_GasSysInfo
 功能描述  : 更新GSM下的系统消息
 输入参数  : pRcvMsg-------系统消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_UpdateNetworkInfo_GasSysInfo(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;
    MMCMM_GSM_SYS_INFO_IND_ST          *pstSysInfoInd     = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrCampLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstCurrCampLaiInfo         = NAS_MML_GetCurrCampLai();

    pstSysInfoInd = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    g_MmGlobalInfo.ucSysInfoFlg             = MM_TRUE;
    g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg  = pstSysInfoInd->ulForbiddenFlg;

    /* 收到系统消息默认小区ID不改变 */
    g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;

    if (pstSysInfoInd->ulCellId != g_MmGlobalInfo.MsCsInfo.ulCellId)
    {
        g_MmGlobalInfo.MsCsInfo.ulCellId = pstSysInfoInd->ulCellId;
        g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_TRUE;
    }

    /* 处理紧急呼列表 */
    NAS_MM_ProcEccNumList_RcvSysinfo(pstSysInfoInd->stPlmnId.ulMcc);

    if (VOS_TRUE == NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo())
    {
        NAS_MM_UpdateT3212Value_RcvGuSysInfo(pstSysInfoInd->ucLRTimerT3212);

        pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = pstCurrCampLaiInfo->stPlmnId.ulMcc;
        pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = pstCurrCampLaiInfo->stPlmnId.ulMnc;
        pstAllocT3212ValueLaiInfo->aucLac[0]        = pstCurrCampLaiInfo->aucLac[0];
        pstAllocT3212ValueLaiInfo->aucLac[1]        = pstCurrCampLaiInfo->aucLac[1];
        pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = pstCurrCampLaiInfo->enCampPlmnNetRat;
        NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);
    }

    /* 默认收到系统消息允许attach */
    g_MmGlobalInfo.ucAttFlg         = MM_ATT_NEED;

    /* 依据消息中 Att 内容，设置全局 Att 标志 */
    if (MM_CONST_NUM_0 == pstSysInfoInd->ucAttachDetach)
    {
        g_MmGlobalInfo.ucAttFlg     = MM_ATT_NOT_NEED;
    }

    /* GPRS不支持 */
    if (MM_CONST_NUM_0 == pstSysInfoInd->ucGprsSupportInd)
    {
        g_MmGlobalInfo.usRac            = MM_UNSUPPORT_GPRS;
        g_MmGlobalInfo.ucNtMod          = MM_NET_MODE_INVALID;
        g_MmGlobalInfo.ucNewNtMod       = MM_NET_MODE_INVALID;
    }
    else
    {
        /* RAI发生改变 */
        if ((VOS_TRUE             == NAS_MML_IsCampLaiInfoChanged())
         || (g_MmGlobalInfo.usRac != pstSysInfoInd->ucRac))
        {
            if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
            {
                g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
                Mm_TimerStop( MM_TIMER_T3211 );
                Mm_TimerStop( MM_TIMER_T3212 );
            }

            /* 更改 LikeB 标志 */
            g_MmGlobalInfo.ucLikeB = MM_FALSE;
        }

        g_MmGlobalInfo.usRac  = (VOS_UINT16)pstSysInfoInd->ucRac;

        NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(pstSysInfoInd->ucNetworkOperationMode);

        ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
        ucPsAttachAllow     = NAS_MML_GetPsAttachAllowFlg();

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
         && ((VOS_FALSE    == ucSimPsRegStatus)
          || (VOS_FALSE    == ucPsAttachAllow)))
        {
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
        }
    }

    /* 收到G下的系统消息默认NSD MOD为R99的 */
    g_stMmNsd.ucNsdMod = MM_NSD_MOD_R99_ONWARDS;

    if (GRRMM_MSC_RELEASE98_OR_OLDER == pstSysInfoInd->ucMsrRelease)
    {
        g_stMmNsd.ucNsdMod = MM_NSD_MOD_R98_OR_OLDER;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_UpdateNetworkInfo_WasSysInfo
 功能描述  : 更新WRR下的系统消息
 输入参数  : pRcvMsg-------系统消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年6月11日
    作    者   : b00269685
    修改内容   : 区分ota 和 sys
  3.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MM_UpdateNetworkInfo_WasSysInfo(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucPsAttachAllow;
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoInd = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrCampLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo  = NAS_MM_GetAllocT3212ValueLaiInfo();
    pstCurrCampLaiInfo         = NAS_MML_GetCurrCampLai();

    pstSysInfoInd = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;

    if (RRC_NAS_SYS_MSK_CS_DRX == (RRC_NAS_SYS_MSK_CS_DRX & pstSysInfoInd->ulMask))
    {
        g_MmGlobalInfo.MsCsInfo.ucCsDrxLen = (VOS_UINT8)pstSysInfoInd->ulCsDrxLength;
    }

    if (RRC_NAS_SYS_MSK_CSPS_INFO == (RRC_NAS_SYS_MSK_CSPS_INFO & pstSysInfoInd->ulMask))
    {
        /* W下PS不支持 */
        if (0 == pstSysInfoInd->ucPsInfoSize)
        {
            if (MMC_MM_SYS_INFO_TYPE_SYS == pstSysInfoInd->enSysInfoType)
            {
                g_MmGlobalInfo.usRac      = MM_UNSUPPORT_GPRS;
                g_MmGlobalInfo.ucNtMod    = MM_NET_MODE_INVALID;
                g_MmGlobalInfo.ucNewNtMod = MM_NET_MODE_INVALID;
            }
        }
        else
        {
            /* RAI发生改变 */
            if ((VOS_TRUE             == NAS_MML_IsCampLaiInfoChanged())
             || (g_MmGlobalInfo.usRac != pstSysInfoInd->ucRac))
            {
                if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
                {
                    g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
                    Mm_TimerStop( MM_TIMER_T3211 );
                    Mm_TimerStop( MM_TIMER_T3212 );
                }

                g_MmGlobalInfo.ucLikeB = MM_FALSE;
            }

            g_MmGlobalInfo.usRac  = (VOS_UINT16)pstSysInfoInd->ucRac;

            /* 更新网络模式信息 */
            NAS_MM_UpdateNetModeInfo_RcvGuSysInfo(pstSysInfoInd->ucNetworkOperationMode);

            ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
            ucPsAttachAllow     = NAS_MML_GetPsAttachAllowFlg();

            if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
             && ((VOS_FALSE    == ucSimPsRegStatus)
              || (VOS_FALSE    == ucPsAttachAllow)))
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
            }
        }

        if (0 != pstSysInfoInd->ucCsInfoSize)
        {
            if (VOS_TRUE == NAS_MM_IsNeedUpdateT3212Value_RcvGuSysInfo())
            {
                NAS_MM_UpdateT3212Value_RcvGuSysInfo(pstSysInfoInd->ucLRTimerT3212);

                pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = pstCurrCampLaiInfo->stPlmnId.ulMcc;
                pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = pstCurrCampLaiInfo->stPlmnId.ulMnc;
                pstAllocT3212ValueLaiInfo->aucLac[0]        = pstCurrCampLaiInfo->aucLac[0];
                pstAllocT3212ValueLaiInfo->aucLac[1]        = pstCurrCampLaiInfo->aucLac[1];
                pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = pstCurrCampLaiInfo->enCampPlmnNetRat;
                NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);
            }

            /* 收到系统消息默认允许attach */
            g_MmGlobalInfo.ucAttFlg = MM_ATT_NEED;

            if (MM_CONST_NUM_0 == pstSysInfoInd->ucAttachDetach)
            {
                g_MmGlobalInfo.ucAttFlg = MM_ATT_NOT_NEED;
            }
        }
    }

    /* 处理紧急呼列表 */
    NAS_MM_ProcEccNumList_RcvSysinfo(pstSysInfoInd->PlmnId.ulMcc);

    g_MmGlobalInfo.ucSysInfoFlg = MM_TRUE;
    g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg = pstSysInfoInd->ulForbiddenFlg;

    /* 收到系统消息默认小区ID不改变 */
    g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;

    if (pstSysInfoInd->ulCellId != g_MmGlobalInfo.MsCsInfo.ulCellId)
    {
        g_MmGlobalInfo.MsCsInfo.ulCellId     = pstSysInfoInd->ulCellId;
        g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_TRUE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedClearAttemptCounter
 功能描述  : 判断是否需要清除attempt counter
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要清除attemp counter
             VOS_FALSE:不需要清除attempt counter
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedClearAttemptCounter( VOS_VOID )
{
    /* 根据24.008 4.4.4.5 The attempt counter is reset when:
        in case of service state ATTEMPTING to UPDATE，
        a MS detects that a new location area is entered */
    if ((MM_IDLE_PLMN_SEARCH           == g_MmGlobalInfo.ucState)
     && ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucPreState)
      || (MM_IDLE_NO_CELL_AVAILABLE    == g_MmGlobalInfo.ucPreState)))
    {
        if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SndMmcForbidenRslt
 功能描述  : 当前如果有fobiden时给MMC发送注册结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月14日
   作    者   : l00167671 罗开辉
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_SndMmcForbidenRslt(VOS_VOID)
{
    if (MMCMM_FORBIDDEN_PLMN == (MMCMM_FORBIDDEN_PLMN & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                MM_MMC_LU_RESULT_FAILURE,
                NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);
    }
    else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
            MM_MMC_LU_RESULT_FAILURE,
            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM);
    }
}



/*****************************************************************************
 函 数 名  : NAS_MM_IsClassAAndNmoIMode
 功能描述  : 判断当前终端为A模式,驻留网络为NMO1
 输入参数  : ucCurNtMod-----当前驻留网络的网络模式
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前是为A+I模式
             VOS_FALSE:当前不是A+I模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月29日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MM_IsClassAAndNmoIMode(
    VOS_UINT8                               ucCurNtMod
)
{
    if ((VOS_TRUE      == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == ucCurNtMod)
     && (MM_FALSE      == g_MmGlobalInfo.ucLikeB))
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}




/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-17, end */


/*****************************************************************************
 函 数 名  : NAS_MM_GetAttemptUpdateLaiInfo
 功能描述  : 获取ATTEMPT UPDATE时的LAI信息
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : MM_LAI_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月03日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
MM_LAI_STRU *NAS_MM_GetAttemptUpdateLaiInfo(VOS_VOID)
{
    return &(g_MmGlobalInfo.MsCsInfo.stAttemptToUpdateLai);
}

/*****************************************************************************
 函 数 名  : NAS_MM_InitLaiInfo
 功能描述  : 初始化MM的LAI信息
 输入参数  : pstLai
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月03日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_InitLaiInfo(
    MM_LAI_STRU                        *pstLai
)
{
    pstLai->PlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstLai->PlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstLai->ulLac        = MM_INVALID_LAI;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsSameLaiInfo
 功能描述  : 判断MM的LAI信息是否改变
 输入参数  : pstCurrLai
             pstOldLai
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月03日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_IsSameLaiInfo(
    MM_LAI_STRU                        *pstCurrLai,
    MM_LAI_STRU                        *pstOldLai
)
{
    if ( pstCurrLai->PlmnId.ulMcc != pstOldLai->PlmnId.ulMcc )
    {
        return VOS_FALSE;
    }

    if ( pstCurrLai->PlmnId.ulMnc != pstOldLai->PlmnId.ulMnc )
    {
        return VOS_FALSE;
    }

    if ( pstCurrLai->ulLac != pstOldLai->ulLac)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MM_LocationUpdateAttemptCounter
 功能描述  : Location Update时Attempt Counter的处理
 输入参数  : ulMmCause:失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月12日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*****************************************************************************/
VOS_VOID NAS_MM_LocationUpdateAttemptCounter(
    VOS_UINT32                          ulMmCause
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;
    MM_LAI_STRU                                *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                           *pstCampLaiInfo  = VOS_NULL_PTR;

    /* 次数加1 */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            NAS_MM_UpdateEquPlmnInfo(ulMmCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        ulMmCause);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     ulMmCause);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */


        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
            NAS_MM_UpdateEquPlmnInfo(ulMmCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        ulMmCause);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     ulMmCause);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* 在U2状态，保存当前的LAI信息 */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, begin */
        NAS_MM_UpdateEquPlmnInfo(ulMmCause);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    ulMmCause);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 ulMmCause);

        /* 进U2的公共处理 */
        Mm_ComToU2Handle();
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-15, end */

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212先进行停止                                */

        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateLauRetryFlg_RcvRelInd
 功能描述  : 收到rel_ind时更新LauRetryFlg标识
 输入参数  : ulMmCause:失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月12日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_UpdateLauRetryFlg_RcvRelInd(
    RRMM_REL_IND_STRU                  *pRrcRelInd
)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    enCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();

    /* ucLuAttmptCnt是加1之后的次数 */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }
        else
        {
            if (VOS_FALSE == NAS_MM_IsRrRelCauseNeedRetryLau(pRrcRelInd->ulRelCause))
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
        }
    }
    else
    {
        if (VOS_FALSE == NAS_MM_IsRrRelCauseNeedRetryLau(pRrcRelInd->ulRelCause))
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
    }
}


/*****************************************************************************
 函 数 名  : NAS_MM_GetNetworkT3212ValueType
 功能描述  : 获取网络下发T3212时长值来源，是从系统消息中获取还是从lau accept
             中Per Ms T3212 IE中获取
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8 NAS_MM_GetNetworkT3212ValueType(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.enNetworkT3212ValueType;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetNetworkT3212ValueType
 功能描述  : 设置网络下发T3212时长值来源，是从系统消息中获取还是从lau accept
             中Per Ms T3212 IE中获取
 输入参数  : enT3212ValueType - 网络下发T3212时长值来源
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID NAS_MM_SetNetworkT3212ValueType(
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8              enT3212ValueType
)
{
    g_MmGlobalInfo.stT3212Info.enNetworkT3212ValueType = enT3212ValueType;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetAllocT3212ValueLaiInfo
 功能描述  : 获取下发t3212定时器时长的LAI信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 下发t3212定时器时长的网络信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
NAS_MML_LAI_STRU *NAS_MM_GetAllocT3212ValueLaiInfo(VOS_VOID)
{
    return (&g_MmGlobalInfo.stT3212Info.stAllocT3212ValueLaiInfo);
}



/*****************************************************************************
 函 数 名  : NAS_MM_GetNetworkAllocT3212Len
 功能描述  : 获取T3212启动时长值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_GetNetworkAllocT3212Len(VOS_VOID)
{
    return gstMmTimer[MM_TIMER_T3212].ulTimerLen;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetNetworkAllocT3212Len
 功能描述  : 设置当前启动的T3212启动时长值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_SetNetworkAllocT3212Len(
    VOS_UINT32                          ulNetworkAllocT3212Len
)
{
    gstMmTimer[MM_TIMER_T3212].ulTimerLen = ulNetworkAllocT3212Len;
}

/*****************************************************************************
 函 数 名  : NAS_MM_LogT3212Info
 功能描述  : 勾MM的期望的T3212信息
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月21日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年6月15日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改

*****************************************************************************/
VOS_VOID  NAS_MM_LogT3212Info(VOS_VOID)
{
    NAS_MM_LOG_T3212_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();

    pstMsg = (NAS_MM_LOG_T3212_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MM,
                                         sizeof(NAS_MM_LOG_T3212_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_LogT3212Info:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MM_LOG_T3212_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MM_LOG_T3212_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMOM_LOG_T3212_INFO_IND;

    /* NV中定制的T3212信息 */
    PS_MEM_CPY( &(pstMsg->stMmlT3212NvCfgInfo), NAS_MML_GetT3212TimerInfo(), sizeof(NAS_MML_T3212_TIMER_INFO_CONFIG_STRU));

    /* 当前使用NV的T3212时长的计数 */
    pstMsg->ulT3212Count                = NAS_MM_GetT3212StartCount();

    /* 网络分配的T3212定时器时长 */
    pstMsg->ulNetworkT3212Len           = NAS_MM_GetNetworkAllocT3212Len();

    /* 网络分配的T3212定时器时长 */
    pstMsg->ulNetworkRandT3212Len       = NAS_MM_GetNetworkT3212RandLen();

    PS_MEM_CPY(&pstMsg->stAllocT3212ValueLaiInfo, pstAllocT3212ValueLaiInfo, sizeof(pstMsg->stAllocT3212ValueLaiInfo));
    pstMsg->enT3212ValueType = NAS_MM_GetNetworkT3212ValueType();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MM, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_Start3212Timer
 功能描述  : MM启动T3212定时器
 输入参数  : T3212启动场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月20日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_StartT3212Timer(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    VOS_UINT32                          ulCurrT3212Len;
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8    enCurrT3212LenType;
    VOS_UINT32                          ulResult;

    enCurrT3212LenType = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN;

    /* 如果当前T3212定时器不是停止状态，则不需要处理 */
    if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus )
    {
        return;
    }

    /* 可维可测勾T3212相关信息包 */
    NAS_MM_LogT3212Info();

    /* 在启动T3212时候需要设置时长: NV配置的时长或者原有的时长 */
    ulCurrT3212Len = NAS_MM_GetT3212StartSceneTimerLen(enT3212StartScene, &enCurrT3212LenType);

    /* 如果当前的T3212时长为0，则不需要启动 */
    if (0 == ulCurrT3212Len)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartT3212Timer:WARNING: Currt3212 TIMER LEN IS ZERO !");

        return;
    }

    /* 启动T3212  Mm_TimerStart(MM_TIMER_T3212); */
    ulResult = Mm_StartRelTimer(
                               &gstMmTimer[MM_TIMER_T3212].hTimer,              /* 存放TIMER ID的地址 */
                               WUEPS_PID_MM,
                               ulCurrT3212Len,                                  /* 时长 */
                               MM_TIMER_T3212,                                  /* 消息队列的ID */
                               gstMmTimer[MM_TIMER_T3212].ulParam,              /* 消息地址 */
                               gstMmTimer[MM_TIMER_T3212].ucMode                /* 消息优先级 */
                               );                                               /* 创建支持消息的定时器 */

    /* 启动失败，则退出 */
    if ( VOS_OK != ulResult )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StartT3212Timer:WARNING: TIMER CREATE FAILURE!");
        return;
    }

    /* 设置当前定时器运行标志 */
    gstMmTimer[MM_TIMER_T3212].ucTimerStatus = MM_TIMER_RUNNING;

    if (NAS_MM_T3212_LEN_TYPE_NV_DEFINED == enCurrT3212LenType)
    {
        /* 如果当前需要用NV中的定时器时长，则T3212启动累计加1 */
        NAS_MM_IncreaseT3212Counter();
    }
    else if (NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN == enCurrT3212LenType)
    {
        /* 初始化全局变量的值 */
        NAS_MM_SetNetworkT3212RandLen(0);
    }
    else
    {
    }

    /* T3212正常启动后，重置T3212计数 */
    if (NAS_MM_T3212_START_SCENE_NORMAL_START == enT3212StartScene)
    {
        NAS_MM_InitT3212Counter();
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_IncreaseT3212Counter
 功能描述  : 增加当前T3212计数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_IncreaseT3212Counter(VOS_VOID)
{
    /* 达到最大值就不增加  */
    if (g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount >= NAS_MM_T3212_START_SCENE_COUNTER_MAX_VALUE )
    {
        return;
    }

    g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_InitT3212Counter
 功能描述  : 重置 T3212计数为0
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_InitT3212Counter(VOS_VOID)
{
    g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetT3212StartCount
 功能描述  : 获取T3212计数值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulT3212StartCount
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_GetT3212StartCount(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.ulUseNvT3212StartLenCount;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetNetworkT3212RandLen
 功能描述  : 获取T3212启动时长值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_GetNetworkT3212RandLen(VOS_VOID)
{
    return g_MmGlobalInfo.stT3212Info.ulNetworkT3212RandLen;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SetNetworkT3212RandLen
 功能描述  : 设置当前启动的T3212启动时长值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月15日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_SetNetworkT3212RandLen(
    VOS_UINT32                          ulCurrT3212Len
)
{
    g_MmGlobalInfo.stT3212Info.ulNetworkT3212RandLen = ulCurrT3212Len;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedUseTheNvimT3212TimerLen
 功能描述  : 判断是否使用NV中配置的T3212定时器时长
 输入参数  : enT3212StartScene:启动场景
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要用NV中的时长
             VOS_FALSE:不需要用NV中的时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月20日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedUseTheNvimT3212TimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartSceneCtrlBitIndex;
    VOS_UINT32                                              ulT3212StartCount;

    pstT3212Info                    = NAS_MML_GetT3212TimerInfo();
    ulT3212StartCount               = NAS_MM_GetT3212StartCount();
    ulT3212StartSceneCtrlBitIndex   = NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX;

    /* 判断当前是测试卡，不需要从NVIM中配置的T3212定时器时长值 */
    if (VOS_TRUE == USIMM_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* NV未激活时候，则不使用NVIM中的值  */
    if (VOS_FALSE == pstT3212Info->ulT3212NvActiveFlg)
    {
        return VOS_FALSE;
    }

    /* 判断当前T3212失败的COUNTER已经超过第二阶段了，则不需要从NVIM中获取T3212定时器的时长 */
    if (ulT3212StartCount >= (pstT3212Info->ulT3212Phase1Count + pstT3212Info->ulT3212Phase2Count))
    {
        return VOS_FALSE;
    }

    /* 从表中获取当前场景对应的控制BIT索引 */
    ulT3212StartSceneCtrlBitIndex = NAS_MM_MapT3212StartSceneToCtrlBitIndex(enT3212StartScene);

    /* 判断当前T3212启动场景NVIM配置是否使能，TRUE为使能，FALSE为不使能 */
    if (VOS_TRUE == NAS_MM_GetT3212StartSceneCtrlBitIndexValue(ulT3212StartSceneCtrlBitIndex))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MM_MapT3212StartSceneToCtrlBitIndex
 功能描述  : 根据T3212的启动场景，获取配置表中
 输入参数  : ulMmCause:失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月20日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_MapT3212StartSceneToCtrlBitIndex(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene
)
{
    NAS_MM_T3212_START_SCENE_CFG_TBL_STRU                  *pstT3212StartSceanCtrlTblPtr = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartSceanCtrlBitIndex;
    VOS_UINT32                                              i;

    pstT3212StartSceanCtrlTblPtr = NAS_MM_GET_T3212_START_SCENE_CFG_TBL_PTR();

    /* 默认为非法INDEX */
    ulT3212StartSceanCtrlBitIndex = NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX;

    /* 从表中获取当前场景对应的控制BIT索引 */
    for (i = 0; i < NAS_MM_GET_T3212_START_SCENE_CFG_TBL_SIZE(); i++)
    {
        /* 根据配置表,获取当前场景的控制BIT位索引 */
        if (enT3212StartScene == pstT3212StartSceanCtrlTblPtr[i].enT3212StartScene)
        {
            ulT3212StartSceanCtrlBitIndex = pstT3212StartSceanCtrlTblPtr[i].ulT3212StartSceneCtrlBitIndex;

            break;
        }
    }

    return ulT3212StartSceanCtrlBitIndex;

}


/*****************************************************************************
 函 数 名  : NAS_MM_GetT3212StartSceneCtrlBitIndexValue
 功能描述  : 根据T3212的启动场景，获取配置表中
 输入参数  : ulMmCause:失败原因值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月20日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetT3212StartSceneCtrlBitIndexValue(
    VOS_UINT32                          ulT3212StartSceneCtrlBitIndex
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;

    pstT3212Info = NAS_MML_GetT3212TimerInfo();

    /* 当前索引非法 */
    if (ulT3212StartSceneCtrlBitIndex >= NAS_MML_T3212_START_SCEAN_INVALID_BIT_INDEX)
    {
        return VOS_FALSE;
    }

    /* 使用控制字节1:bit0~bit31 */
    if (ulT3212StartSceneCtrlBitIndex <= NAS_MML_T3212_START_SCEAN_MASK1_MAX_BIT_INDEX)
    {
        /* 根据NV中是否使能BIT值为1则使能，为0则不使能 */
        if (NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE == ((pstT3212Info->ulT3212StartSceneCtrlBitMask >> ulT3212StartSceneCtrlBitIndex) & NAS_MML_T3212_START_SCENE_VALID_BIT_INDEX_VALUE))
        {
            return VOS_TRUE;
        }
    }
    else
    {
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetT3212StartSceneTimerLen
 功能描述  : 获取T3212定时器时长
 输入参数  : enT3212StartScene:T3212定时器启动场景
 输出参数  : penT3212LenType
 返 回 值  : VOS_UINT32: T3212启动时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月19日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetT3212StartSceneTimerLen(
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene,
    NAS_MM_T3212_LEN_TYPE_ENUM_UINT8                       *penT3212LenType
)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    VOS_UINT32                                              ulT3212StartCount;
    VOS_UINT32                                              ulNetworkAllocT3212Len;
    VOS_UINT32                                              ulNetworkT3212RandLen;

    pstT3212Info                    = NAS_MML_GetT3212TimerInfo();
    ulT3212StartCount               = NAS_MM_GetT3212StartCount();
    ulNetworkAllocT3212Len          = NAS_MM_GetNetworkAllocT3212Len();
    ulNetworkT3212RandLen           = NAS_MM_GetNetworkT3212RandLen();
    *penT3212LenType                = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN;

    /* 判断当前是否从NV中获取配置的T3212定时器时长 */
    if (VOS_TRUE == NAS_MM_IsNeedUseTheNvimT3212TimerLen(enT3212StartScene))
    {
        *penT3212LenType = NAS_MM_T3212_LEN_TYPE_NV_DEFINED;

        /* 如果T3212失败次数小于第一阶段，则使用第一阶段的时长，否则用第二阶段的时长 */
        if (ulT3212StartCount < pstT3212Info->ulT3212Phase1Count)
        {
            return pstT3212Info->ulT3212Phase1TimeLen;
        }

        return pstT3212Info->ulT3212Phase2TimeLen;
    }

    /* 取网络分配的T3212 RAND定时器时长  */
    if ( (MM_CONST_NUM_0 != ulNetworkT3212RandLen)
      && (MM_CONST_NUM_0 != ulNetworkAllocT3212Len) )
    {
        *penT3212LenType = NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN;

        /* 如果网络下发新的T3212时长，当前T3212没有在运行，则取不大于网络下发时长的随机值 */
        return ulNetworkT3212RandLen;
    }

    /* 取网络下发的T3212时长 */
    return ulNetworkAllocT3212Len;
}

#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MM_ConvertCsfbServiceStatusToRrcSessionType
 功能描述  : 将CSFB服务状态转换成相应的Session类型
             (建议调用该函数时，配合CSFB服务状态使用)
 输入参数  : enCsfbServiceStatus:CSFB类型
 输出参数  : penRrcSessionType  :相应Rrc的Session类型

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月18日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8                        *penRrcSessionType
)
{
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_CSFB;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsfbServiceStatusChange
 功能描述  : 更新CSFB标记，CSFB标记从存在更新成不存在时，需要释放申请资源
 输入参数  : enCurStatus   :当前的CSFB标志     ----- BUTT当做NOT_EXIST处理
             enTargetStatus:需要更新的CSFB标志 ----- BUTT当做NOT_EXIST处理
             (最好不要使用BUTT值)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年9月16日
   作    者   : f00179208
   修改内容   : cs_err_log项目添加异常记录
*****************************************************************************/
VOS_VOID NAS_MM_ProcCsfbServiceStatusChange(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCurStatus,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enTargetStatus
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;


    /* 如果传入BUTT值，默认认为不存在，一般禁止传入BUTT */
    if ( NAS_MML_CSFB_SERVICE_STATUS_BUTT == enCurStatus )
    {
        enCurStatus = NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;
    }

    if ( NAS_MML_CSFB_SERVICE_STATUS_BUTT == enTargetStatus )
    {
        enTargetStatus = NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST;
    }

    /* CSFB标志从无到有，发送申请资源通知 */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST == enCurStatus)
      && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enTargetStatus) )
    {
        NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(enTargetStatus, &enRrcSessionType);

        /* 释放申请资源 */
        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    /* CSFB标志从有到无，发送释放资源通知 */
    if ( (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enCurStatus)
      && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST == enTargetStatus) )
    {
        NAS_MM_ConvertCsfbServiceStatusToRrcSessionType(enCurStatus, &enRrcSessionType);

        /* 释放申请资源 */
        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }
#endif

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertRrcRelCauseToMmCcRelCause
 功能描述  : 把RRC REL原因值转换成MM与CC的原因值
 输入参数  : RRC_REL_CAUSE_ENUM_UINT32     :RRC REL原因值
 输出参数  : 无
 返 回 值  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:MM与CC的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月20日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertRrcRelCauseToMmCcRelCause(
    RRC_REL_CAUSE_ENUM_UINT32           enRrcRelCause
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON;

    for (i = 0; i < (sizeof(g_astRrcToMmCcRelCause) / sizeof(g_astRrcToMmCcRelCause[0])); i++)
    {
        if (enRrcRelCause == g_astRrcToMmCcRelCause[i].enRrcRelCause)
        {
            enRelCause = g_astRrcToMmCcRelCause[i].enMmCcRelCause;
        }
    }

    return enRelCause;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertEstCnfRsltToMmCcRelCause
 功能描述  : 把EST_CNF结果转换成MM与CC的原因值
 输入参数  : RRC_NAS_EST_RESULT_ENUM_UINT32:RRC REL原因值
 输出参数  : 无
 返 回 值  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:MM与CC的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月20日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertEstCnfRsltToMmCcRelCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32     enEstCnfRslt
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = NAS_MMCM_REL_CAUSE_RR_REL_OTHER_REASON;

    for (i = 0; i < (sizeof(g_astEstRsltToMmCcRelCause) / sizeof(g_astEstRsltToMmCcRelCause[0])); i++)
    {
        if (enEstCnfRslt == g_astEstRsltToMmCcRelCause[i].enEstRslt)
        {
            enRelCause = g_astEstRsltToMmCcRelCause[i].enMmCcRelCause;
        }
    }

    return enRelCause;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ConvertLauEstCnfRsltToT3212StartScean
 功能描述  : 把LAU的EST_CNF结果转换成启动T3212的场景
 输入参数  : RRC_NAS_EST_RESULT_ENUM_UINT32:enEstCnfRslt原因值
 输出参数  : 无
 返 回 值  : NAS_MM_T3212_START_SCENE_ENUM_UINT32:T3212启动场景
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月20日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MM_T3212_START_SCENE_ENUM_UINT32 NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfRslt
)
{
    VOS_UINT32                                              i;
    NAS_MM_T3212_START_SCENE_ENUM_UINT32                    enT3212StartScene;

    enT3212StartScene  = NAS_MM_T3212_START_SCENE_BUTT;

    for (i = 0; i < (sizeof(g_astLauEstCnfRsltToT3212StartScene) / sizeof(g_astLauEstCnfRsltToT3212StartScene[0])); i++)
    {
        if (enEstCnfRslt == g_astLauEstCnfRsltToT3212StartScene[i].enEstRslt)
        {
            enT3212StartScene = g_astLauEstCnfRsltToT3212StartScene[i].enT3212StartScene;
            break;
        }
    }

    return enT3212StartScene;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause
 功能描述  : 把CSFB失败结果转换成MM与CC的原因值
 输入参数  : LMM_MM_CSFB_SERVICE_END_IND_STRU:CSFB流程异常终止结构体
 输出参数  : 无
 返 回 值  : NAS_MMCM_REL_CAUSE_ENUM_UINT32:MM与CC的原因值
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月07日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMCM_REL_CAUSE_ENUM_UINT32 NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause(
    LMM_MM_CSFB_SERVICE_END_IND_STRU   *pstCsfbEndInd
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;
    VOS_UINT32                          i;

    enRelCause  = (VOS_UINT32)NAS_MMCM_REL_CAUSE_BUTT;

    /* CSFB service rej */
    if (MM_LMM_CSFB_SERVICE_RSLT_CN_REJ == pstCsfbEndInd->enCsfbSrvRslt)
    {
        enRelCause  = (pstCsfbEndInd->ulCnCause) + NAS_MMCM_REL_CAUSE_CSFB_SRV_REJ_BEGIN;
    }
    /* 以下为CSFB LMM Error */
    else
    {
        for (i = 0; i < (sizeof(g_astCsfbRsltToMmCcRelCause) / sizeof(g_astCsfbRsltToMmCcRelCause[0])); i++)
        {
            if (pstCsfbEndInd->enCsfbSrvRslt    == g_astCsfbRsltToMmCcRelCause[i].enCsfbRslt)
            {
                enRelCause = g_astCsfbRsltToMmCcRelCause[i].enMmCcRelCause;
            }
        }
    }

    return enRelCause;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MM_IsGsmOnlyEstCnfRslt
 功能描述  : 判断是不是只有GSM下才有的EST_CNF原因值
 输入参数  : RRC_NAS_EST_RESULT_ENUM_UINT32
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsGsmOnlyEstCnfRslt(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT == ulResult)
     || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == ulResult)
     || (RRC_EST_RJ_RA_FAIL == ulResult)
     || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO == ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsHoBetweenGU
 功能描述  : 判断是否是GU之间的切换流程
 输入参数  : enSrcRatType:异系统前的接入技术
             enDestRatType:异系统后的接入接入技术
             enSuspendCause:挂起原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE:是GU之间的切换流程 VOS_FALSE:不是GU之间的切换流程
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 新增函数

*****************************************************************************/
VOS_UINT8 NAS_MM_IsHoBetweenGU(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSrcRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRatType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
 {
    /* 异系统失败，返回FALSE */
    if (enSrcRatType == enDestRatType)
    {
        return VOS_FALSE;
    }

    /* 异系统前后的接入技术是LTE，返回FALSE */
#if (FEATURE_ON == FEATURE_LTE)
    if ( (NAS_MML_NET_RAT_TYPE_LTE == enSrcRatType)
      || (NAS_MML_NET_RAT_TYPE_LTE == enDestRatType) )
    {
        return VOS_FALSE;
    }
#endif

    /* 挂起原因值不是handover，返回FALSE */
    if (MMC_SUSPEND_CAUSE_HANDOVER != enSuspendCause)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_StartHoWaitSysInfoTimer
 功能描述  : HO时启等待系统消息定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月18日
   作    者   : s00217060
   修改内容   : 新增函数

*****************************************************************************/
VOS_VOID NAS_MM_StartHoWaitSysInfoTimer(
    VOS_UINT8                           ucTimerId
)
{
    /* 定时器先停再启,定时器时长可NV配置 */
    Mm_TimerStop(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
    Mm_TimerStop(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
    Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

    /* 启动HO等系统消息的定时器 */
    Mm_TimerStart(ucTimerId);

    return;
}


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_MM_RecordCsPagingFail_WaitForRrConnection
 功能描述  : 尝试记录Cs Paging Fail
 输入参数  : RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult   - 建链结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月10日
   作    者   : n00269697
   修改内容   : 新增函数

*****************************************************************************/
VOS_VOID NAS_MM_RecordCsPagingFail_WaitForRrConnection(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    /* 建链结果是RRC_EST_SUCCESS或者RRC_EST_PRESENT，不需要记录 */
    if ((RRC_EST_SUCCESS == ulResult)
     || (RRC_EST_PRESENT == ulResult))
    {
        return;
    }

    /* 如果在CSFB MT的过程中则不需要记录CS PAGING FAIL */
    if (NAS_ERR_LOG_CSFB_MT_STATE_NULL != NAS_MML_GetCsfbMtCurrState())
    {
        return;
    }

    if ((MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
     && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
     && (MM_FALSE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
    {
        /* CS PAGING链路建立失败的异常记录 */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_FAIL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ParseErrLogCsPagingInfo
 功能描述  : 将上层传递过来的参数存储全局变量
 输入参数  : VOS_VOID            *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年03月13日
   作    者   : zwx247453
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ParseErrLogCsPagingInfo(
    VOS_VOID                           *pRcvMsg
)
{
    RRMM_PAGING_IND_STRU               *pstWPagingMsg = VOS_NULL_PTR;
    GRRMM_PAGING_IND_ST                *pstGPagingMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_NULL_PTR == pRcvMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_ParseErrLogCsPagingInfo(): parameter is NULL pointer.");
        return;
    }

    enRatType = NAS_MML_GetCurrNetRatType();

    if (NAS_MML_NET_RAT_TYPE_GSM == enRatType)
    {
        pstGPagingMsg = (GRRMM_PAGING_IND_ST *)pRcvMsg;

        NAS_MML_SetErrLogGMsIdType(pstGPagingMsg->ucMSIDType);
        NAS_MML_SetErrLogGPagingType(pstGPagingMsg->ucPagingType);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
    {
        pstWPagingMsg = (RRMM_PAGING_IND_STRU *)pRcvMsg;

        NAS_MML_SetErrLogWCnDomainId(pstWPagingMsg->ulCnDomainId);
        NAS_MML_SetErrLogWPagingType(pstWPagingMsg->ulPagingType);
        NAS_MML_SetErrLogWPagingCause(pstWPagingMsg->ulPagingCause);
        NAS_MML_SetErrLogWPagingUeId(pstWPagingMsg->ulPagingUeId);
    }
    else
    {
        ;
    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MM_RecordErrorLogInfo
 功能描述  : 记录错误信息
 输入参数  : enState        ---  过程状态
             ulCause        ---  原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_RecordErrorLogInfo(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState,
    VOS_UINT32                          ulCause
)
{
    VOS_UINT32                          ulTimerStatus;
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;

    ulTimerStatus = NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    /* 如果在CSFB MT的流程中，则记录相关的CSFB MT的信息 */
    if ((MM_TIMER_RUNNING                                       == ulTimerStatus)
     || (NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT     == enBaseState)
     || (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == enBaseState))
    {
        enCsfbMtState = NAS_MNTN_ConvertBaseStateToCsfbMtState(enBaseState);

        NAS_MM_FillCsfbMtInfo(enCsfbMtState, ulCause);
    }

    /* 需要记录其他业务场景的信息，添加到下面 */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ClearErrorLogInfo
 功能描述  : 清除错误信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月24日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ClearErrorLogInfo(VOS_VOID)
{
    NAS_MML_InitCsfbMtInfo();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_FillCsfbMtInfo
 功能描述  : 填充CSFB MT的过程的信息
 输入参数  : enCsfbMtState  ---  过程状态
             ulCause        ---  原因值
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月15日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_FillCsfbMtInfo(
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState,
    VOS_UINT32                          ulCause
)
{
    NAS_MML_ERRLOG_CSFB_MT_INFO_STRU       *pstCsfbMtInfo   = VOS_NULL_PTR;
    NAS_MNTN_POSITION_INFO_STRU            *pstPositionInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU    *pstStateInfo    = VOS_NULL_PTR;
    VOS_UINT32                              ulPositionNum;
    VOS_UINT32                              ulStateNum;

    pstCsfbMtInfo       = NAS_MML_GetCsfbMtInfoAddr();

    /* 不是对应的状态，则不记录信息 */
    if (enCsfbMtState > NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT)
    {
        return;
    }

    NAS_MML_SetCsfbMtCurrState(enCsfbMtState);

    ulPositionNum = NAS_MML_GetCsfbMtRecordPositionNum();
    ulStateNum    = NAS_MML_GetCsfbMtRecordStateNum();

    /* 收到LMM的paging ind状态，需要将当前L的位置区信息记录下来，
       收到系统消息的状态，需要保存相关的位置区信息，
       超过记录的最大个数后就不再记录 */
    if ((NAS_ERR_LOG_CSFB_MT_STATE_GU_SYS_INFO_RECEIVED     == enCsfbMtState)
     || (NAS_ERR_LOG_CSFB_MT_STATE_LTE_SYS_INFO_RECEIVED    == enCsfbMtState)
     || (NAS_ERR_LOG_CSFB_MT_STATE_LMM_CS_PAGING_RECEIVED   == enCsfbMtState))
    {
        if (ulPositionNum < NAS_ERR_LOG_MAX_POSITION_RECORD_NUM)
        {
            pstPositionInfo = &(pstCsfbMtInfo->astPositionInfo[ulPositionNum]);

            NAS_MNTN_OutputPositionInfo(pstPositionInfo);
        }

        NAS_MML_AddCsfbMtRecordPositionNum();
    }

    /* 更新相应的状态信息，超过记录的最大个数后就不再记录 */
    if (ulStateNum < NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM)
    {
        pstStateInfo = &(pstCsfbMtInfo->astStateInfo[ulStateNum]);
        pstStateInfo->enCsfbMtState = enCsfbMtState;
        pstStateInfo->ulMmState     = Mm_GetState();
        pstStateInfo->ulCause       = ulCause;
        pstStateInfo->ulTick        = VOS_GetTick();
    }

    NAS_MML_AddCsfbMtRecordStateNum();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetRrcPidFromCurrRatType
 功能描述  : 获取当前接入模式的接入层PID
 输入参数  : VOS_UNT
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年06月01日
   作    者   : j00174725
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetRrcPidFromCurrRatType(
    VOS_UINT32                         *pulPid
)
{
    VOS_UINT32                          ulRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    /* 初始化 */
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();

    switch(enCurrNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            *pulPid = UEPS_PID_GAS;
            ulRet   = VOS_OK;
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            *pulPid = WUEPS_PID_WRR;
            ulRet   = VOS_OK;
            break;

        default:
            ulRet   = VOS_ERR;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsLauRejNeedRetry
 功能描述  : LAU注册被拒时，是否需要继续尝试注册
 输入参数  : VOS_UINT8                           ucCause
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_IsLauRejNeedRetry(
    VOS_UINT8                           ucCause
)
{
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     *pstLauRejCfg = VOS_NULL_PTR;
    VOS_UINT8                                               ucIsCurCauseInNvCauseList;
    VOS_UINT32                                              i;

    pstLauRejCfg                = NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo();
    ucIsCurCauseInNvCauseList   = VOS_FALSE;

    /* 测试卡时需要继续尝试 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_TRUE;
    }

    /* 查找当前原因值是否在NV配置的原因值列表中 */
    for (i=0; i < pstLauRejCfg->ucLauRejCauseNum; i++)
    {
        if (ucCause == pstLauRejCfg->aucLauRejCause[i])
        {
            ucIsCurCauseInNvCauseList   = VOS_TRUE;
            break;
        }
    }


    /* 如果业务存在时，并且原因值在NV列表中，并且尝试次数已经达到NV中配置的次数，不需要继续尝试 */
    if ((VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
     && (VOS_TRUE == ucIsCurCauseInNvCauseList)
     && (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= pstLauRejCfg->ucLauRejTimes))
    {
        return VOS_FALSE;
    }

    /* 如果是漫游网络被拒不需要尝试的NV激活，不需要再尝试 */
    if (VOS_TRUE == NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertCallStatusToTransactionStatus
 功能描述  : 从CALL STATUS中得到transaction状态
 输入参数  : RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ConvertCallStatusToTransactionStatus(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
)
{
    *penTransStatus = RRMM_TRANSACTION_FAIL;

    if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
    {
        *penTransStatus = RRMM_TRANSACTION_CONNECTION_EST_SUCC;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateCallStatus_RcvCcEstReq
 功能描述  : 收到MMCC_EST_REQ时更新call status标志
 输入参数  : MMCC_EST_REQ_STRU                   *pstEstReq
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCallStatus_RcvCcEstReq(
    MMCC_EST_REQ_STRU                   *pstEstReq
)
{
    /* 第一次发起呼叫(不是重拨时),先默认为gu下的呼叫，
       如果后续是发给LMM的，在给LMM发送csfb start时会更新该标志
    */

    if (VOS_FALSE == pstEstReq->ucRedialFlg)
    {

        NAS_NORMAL_LOG(WUEPS_PID_MM,
        "NAS_MM_UpdateCallStatus_RcvCcEstReq: Not Redail call, Set CellNotSupportCsmoFlg to FALSE");
        NAS_MML_SetCellNotSupportCsmoFlg(VOS_FALSE);

        if (MMCC_EMERGENCY_CALL == pstEstReq->ulCallType)
        {
            NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_START);
        }
        else
        {
            NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_START);
        }

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateCallStatus_RcvCallStatusNty
 功能描述  : 收到呼叫建立状态时，更新MML中的call status
 输入参数  : MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_UpdateCallStatus_RcvCallStatusNty(
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus
)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enOldMoCallStatus;

    enOldMoCallStatus   = NAS_MML_GetMoCallStatus();

    /* 更新主叫标志 */
    switch (enOldMoCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_NORMAL_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_NORMAL_CALL_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_EMC_CALL_SETUP_START:
            if (MNCC_CALL_STATUS_SETUP_SUCC == enCallStatus)
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoCallStatus(NAS_MML_MO_EMC_CALL_SETUP_FAIL);
            }
            break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_UpdateSsStatus_RcvSsStatusNty
 功能描述  : 收到MMSS_STATUS_NTY时更新ss status
 输入参数  : MMSS_STATUS_ENUM_UINT8              enSsStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_UpdateSsStatus_RcvSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
)
{

    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enOldMoSsStatus;

    enOldMoSsStatus = NAS_MML_GetMoSsStatus();

    /* 更新MO标志 */
    switch (enOldMoSsStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:
            if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
            {
                NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_FAIL);
            }
            break;

        case NAS_MML_MO_NORMAL_SS_SETUP_START:
            if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
            {
                NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_SUCC);
            }
            else
            {
                NAS_MML_SetMoSsStatus(NAS_MML_MO_NORMAL_SS_SETUP_FAIL);
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertSsStatusToTransactionStatus
 功能描述  : 从SS STATUS中得到transaction状态
 输入参数  : RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ConvertSsStatusToTransactionStatus(
    MMSS_STATUS_ENUM_UINT8              enSsStatus,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8 *penTransStatus
)
{
    *penTransStatus = RRMM_TRANSACTION_FAIL;

    if (SSA_SS_STATUS_SETUP_SUCC == enSsStatus)
    {
        *penTransStatus = RRMM_TRANSACTION_CONNECTION_EST_SUCC;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_IsNeedLauFirst_CsfbMoEmcExist
 功能描述  : CSFB MO紧急呼存在时，是否需要先做LAU
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedLauFirst_CsfbMoEmcExist(VOS_VOID)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulCsRestrictRegFlg;

    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();
    ulCsRestrictRegFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    /* 满足以下条件时，CSFB MO EMC需要先做LAU，再处理紧急呼:
        1. 紧急呼叫csfb到gu后LAI改变先进行lau的NV项打开
        2. LAI发生变化
        3. CS域不受限
    */

    if ((VOS_TRUE == NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg())
     && (VOS_TRUE == ulLaiChangeFlag)
     && (VOS_FALSE == ulCsRestrictRegFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist
 功能描述  : CSFB MO EMC存在时，MM上报cs域注册状态的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月13日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist(VOS_VOID)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT32                          ulCsRestrictRegFlg;

    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();
    ulCsRestrictRegFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    /* 紧急呼CSFB到GU,需要做LAU时，不上报CS域注册状态，等注册结束时上报真实的注册状态 */
    if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
    {
        return;
    }

    /* CS域受限直接上报注册结果为access bar */
    if (VOS_TRUE == ulCsRestrictRegFlg)
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

    }
    /* LAI未发生改变时，update status状态是updated，可以直接报注册成功，因为该LAI是last succ lai */
    else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
          && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
          && (VOS_FALSE == ulLaiChangeFlag))
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

    }
    /* NV项定制导致的不做LAU，上报注册结果为异系统成功，MMC会报之前的CS域服务状态和注册状态 */
    else if (VOS_FALSE == NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg())
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);

    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ProcT3213AttemptCounter
 功能描述  : GSM下T3213运行时，如果LAI改变，则增加T3213 Attempt Counter
 输入参数  : ulT3213Status: T3213运行状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcT3213AttemptCounter(
    VOS_UINT32                          ulT3213Status
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    VOS_UINT32                          ucIsCampLaiChange;

    enCurrNetRat = NAS_MML_GetCurrNetRatType();
    ucIsCampLaiChange = NAS_MML_IsCampLaiInfoChanged();

    /* GSM下T3213运行时，如果LAI改变，发起Lau后MM的状态变为WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING，此时增加T3213 Attempt Counter */
    if ((NAS_MML_NET_RAT_TYPE_GSM                 == enCurrNetRat)
     && (VOS_TRUE                                 == ucIsCampLaiChange)
     && (MM_TIMER_RUNNING                         == ulT3213Status)
     && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLuAttemptCounter
 功能描述  : 根据建链结果来更新 Lu Attempt Counter
 输入参数  : enEstResult: 建链结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcLuAttemptCounter(RRC_NAS_EST_RESULT_ENUM_UINT32 enEstResult)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    VOS_UINT8                           ucTrigLauOnceFlg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode           = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurrNetRat              = NAS_MML_GetCurrNetRatType();
    ucTrigLauOnceFlg          = NAS_MML_GetPsRegFailMaxTimesTrigLauOnceFlg();

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
     && (VOS_TRUE == ucTrigLauOnceFlg)
     && (MM_CONST_NUM_5 == g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt))
    {
        if ((RRC_EST_RANDOM_ACCESS_REJECT == enEstResult)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
            return;
        }

        if ((RRC_EST_RJ_TIME_OUT == enEstResult)
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurrUtranMode))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
            return;
        }
    }

    /* NO_RF时不累加 */
    if (RRC_EST_RJ_NO_RF != enEstResult)
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ComProcPsRandomAccessFailCnt
 功能描述  : W下联合RAU/Attach因建链失败，MM根据原因值来更新全局变量ucPsEstCnfFailCnt
 输入参数  : enRegFailCause: 建链失败原因值
             ulRegCounter  : RAU/Attach Attempt Counter
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MM_ComProcPsRandomAccessFailCnt(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause,
    VOS_UINT32                          ulRegAttemptCounter
)
{
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT != enRegFailCause)
        {
            g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
        }
        else
        {
            /* RAI改变时，GMM模块会重置Rau/Attach Attempt Counter，此时也需要重置ucPsEstCnfFailCnt
            *  但是，重置的时候没有通知MM模块，之后发起Rau/Attach，如果建链失败则ulRegCounter为1，
            *  此时，同步更新全局变量ucPsEstCnfFailCnt的值为1
            */
            if (MM_CONST_NUM_1 == ulRegAttemptCounter)
            {
                g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = MM_CONST_NUM_1;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt++;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcLauEstCnfNoRf
 功能描述  : 建链失败原因值 no_rf的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年06月23日
   作    者   : j00174725
   修改内容   : DTS2015060105317(LAU 建链失败原因NO_RF时，不需要通知MMC)
*****************************************************************************/
VOS_VOID NAS_MM_ProcLauEstCnfNoRf(VOS_VOID)
{
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
    }

    NAS_MM_ProcLuAttemptCounter(RRC_EST_RJ_NO_RF);

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
            && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* 如果LAI不变,且更新状态为U1的时候         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);  /* 向MMC发送MMCMM_LU_RESULT_IND             */

            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
            g_T3211Flag = 1;
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* 在U2状态，保存当前的LAI信息 */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* 进U2的公共处理 */
            Mm_ComToU2Handle();

            Mm_TimerStart(MM_TIMER_T3211);                                      /* 启动T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* 在U2状态，保存当前的LAI信息 */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        /* 进U2的公共处理 */
        Mm_ComToU2Handle();

        NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(RRC_EST_RJ_NO_RF));
    }

    if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
    {
         Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                          /* RR连接不存在                             */

         NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    Mm_ComCheckDelayMmConn(MM_FALSE);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ConvertToMmlSessionType
 功能描述  : 把MM的Session type 转换MML的类型
 输入参数  :
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ConvertToMmlSessionType(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8   enMmSessionType,
    NAS_MML_SESSION_TYPE_ENUM_UINT8  *penMmlSessionType
)
{
    switch(enMmSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SMS;
            break;

        default:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_BUTT;
            break;
    }

    return;
}




/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

