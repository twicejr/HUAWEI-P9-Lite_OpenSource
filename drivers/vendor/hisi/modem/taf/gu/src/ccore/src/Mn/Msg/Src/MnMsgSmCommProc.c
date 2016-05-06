/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgSmCommProc.c
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月19日
  最近修改   :
  功能描述   : 实现sms模块公共处理部分,包括事件上报,与NVIM,USIM的交互
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 创建文件
  2.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 问题单号：AT2D03830, 修改en_NV_Item_SMS_SERVICE_Para项读写相关代码
  3.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 问题单号：AT2D03832, EFSMSP文件中若存在全FF的无效地址则解析出错
  4.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 存储短消息设备满时，修改接收短消息处理方式为不存储，没有发送SMMA消息
  5.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号：AT2D04859,设置SMS发送域PS域优先，在电话过程中无法发送短信
  6.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D04609,CMMS命令的增加；
  7.日    期   : 2008年8月14日
    作    者   : fuyingjun
    修改内容   : 问题单号:AT2D04545, SMS相关AT模块和MN模块新增代码复杂度超过要求数值20
  8.日    期   : 2008年8月21日
    作    者   : fuyingjun
    修改内容   : 问题单号:AT2D05119
  9.日    期   : 2008年8月25日
    作    者   : fuyingjun
    修改内容   : 问题单号:AT2D04608
 10.日    期   : 2008年8月29日
    作    者   : fuyingjun
    修改内容   : 问题单号:AT2D05344, 短消息模块初始化过程结束后进行SDT工具与单板反复进行连接和断开操作,协议栈会重复上报初始化完成事件;
 11.日    期   : 2008年09月08日
    作    者   : f62575
    修改内容   : 问题单AT2D05583,CBS功能模块代码PC-lint错误
 12.日    期   : 2008年09月11日
    作    者   : f62575
    修改内容   : 问题单号AT2D05684, SMSP文件操作相关修改
 13.日    期   : 2008年09月26日
    作    者   : f62575
    修改内容   : 问题单号：AT2D05700, UE收到短信后, TAF上报给应用的短信长度不对问题。
 14.日    期   : 2008年10月10日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06152（AT2D06151）, USIMM优化合入后，SMSP文件相关读写操作失败
 15.日    期   : 2008年10月20日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06072, SIM卡中存在编码错误的短消息后，该条记录不可读写；
 16.日    期   : 2008-11-17
    作    者   : f62575
    修改内容   : 问题单号:AT2D06843, 短信状态报告的读，删除和上报接口与终端工具需求不符问题
 17.日    期   : 2008年12月25日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D07869, SIM卡中短信息存储区满后接收一条需要存储的短信溢出，短信模块写(U)SIM卡的SMSS文件失败
 18.Date         : 2009-01-12
    Author       : f62575
    Modification : 问题单号:AT2D07548, 短信中心查询操作失败需要返回准确原因
 19.日    期   : 2009年02月20日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D08974, 开机时串口打印PR地址,短消息中心地址错误
 20.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D07942（AT2D09557）, 短信中心号码上报时间较长
 21.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D08974, 短信打印级别过高
 22.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D10320, PDU格式写入短信与读出短信内容不是完全一致的；
 23.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D10321, SMMA重复发送问题；
 24.日    期   : 2009年3月30日
    作    者   : f62575
    修改内容   : AT2D10546, 短信状态报告无TP-PI，TP-PID，TP-DCS等可选项，必然会读取失败；
 25.日    期   : 2009年3月30日
    作    者   : f62575
    修改内容   : AT2D10538, 发送短信命令并保存在USIM卡中，读取时会当成一条短信状态报告；
 26.日    期   : 2009年4月1日
    作    者   : 周君 40661
    修改内容   : 问题单号:AT2D09786, 用AT+CMGD=,4删除短信时，长时间不回应，导致自动化脚本检测不到单板
 27.日    期   : 2009年4月7日
    作    者   : f62575
    修改内容   : 问题单号 AT2D06392, 不支持短信和状态报告的NV存储相关代码通过宏开关关闭
 28.日    期   : 2009-04-22
    作    者   : f62575
    修改内容   : 问题单号:AT2D11256, 打开后台，再插上单板，无法接收到短信。
 29.日    期   : 2009年05月11日
    作    者   : f62575
    修改内容   : 问题单号：AT2D11136，PICS表设置为仅支持SM存储，执行GCF测试用例34.2.5.3，测试用例失败
 30.日    期   : 2009年05月15日
    作    者   : f62575
    修改内容   : 问题单号：AT2D11703，由于勾包过大,申请内存失败,导致单板复位
 31.日    期   : 2009年7月18日
    作    者   : z40661
    修改内容   : 终端可配置需求合入
 32.日    期   : 2009年07月24日
    作    者   : f62575
    修改内容   : 问题单号：AT2D13258，执行AT&F0恢复出厂设置后，短信功能不可用
 33.日    期   : 2009年08月02日
    作    者   : f62575
    修改内容   : 问题单号：AT2D13420，短信SIM卡相关设置过程中，UE软复位导致设置操作无返回；
 34.日    期   : 2009年08月7日
    作    者   : f62575
    修改内容   : STK特性合入
 35.日    期   : 2009年08月20日
    作    者   : f62575
    修改内容   : CLASS0类短信的上报方式参考27005协议，详细描述参考《定制需求汇总_Individual05.SRS.Class0短信实现方式.doc》
 36.日    期   : 2009年08月25日
    作    者   : f62575
    修改内容   : 问题单号：AT2D14054，【EF_USIM_UST配置】EF_USIM_UST配置的实现代码与产品线提供的需求不一致
 37.日    期   : 2009年9月02日
    作    者   : f62575
    修改内容   : 问题单号:AT2D14189, 执行GCF协议34123的用例16.1.2和16.2.2失败
 38.日    期   : 2009年10月16日
     作    者   : f62575
     修改内容   : 问题单号:AT2D15127, 服务域为PS ONLY，发送域为CS PREFER，参照标杆
                  短信首先尝试从CS域发送；
 39.日    期   : 2009年10月23日
     作    者   : f62575
     修改内容   : 问题单号:AT2D15225, 启用短信重发功能后短信无法在PS域发送问题；
 40.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
 41.日    期   : 2009年12月9日
     作    者   : f62575
     修改内容   : 问题单号:AT2D15782, 短信存储区满时接收到短信状态报告给网络回复RP-ACK消息，
                                  与标竿相同情况下回复RP-ERROR(错误原因值22内存满不一致)；
 42.日    期   : 2009年12月11日
     作    者   : f62575
     修改内容   : 问题单号:AT2D15875, 单板上电时接收到短信状态报告修改为存储到SIM卡；
 43.日    期   : 2009年12月31日
     作    者   : f62575
     修改内容   : PC工程桩合入；
 44.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : AT2D16304, STK PP DOWN功能完善和SMS相关的(U)SIM文件REFRESH
 45.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
 46.日    期   : 2010年4月15日
    作    者   : f62575
    修改内容   : AT2D18539, SMSP文件编码错误时, 短信中心地址读取失败;
 47.日    期   : 2010年04月30日
    作    者   : F62575
    修改内容   : 问题单号AT2D15403
                 短信以CMT方式上报且CSMS配置为1时若应用不下发CNMA命令确认新短信接收,
                 则后续短信既不上报也不存储到本地;
 48.日    期   : 2010年6月10日
    作    者   : f62575
    修改内容   : DTS2010061000153, 关闭从SMSP文件文件中获取TP-DCS,TP-VP和TP-PID的功能;
 49.日    期   : 2010年7月14日
    作    者   : 傅映君/f62575
    修改内容   : DTS2010071302170: PP DOWNLODAD操作导致内存泄漏
 50.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnMsgInclude.h"
#include "NasGmmInterface.h"
#include "MmaAppLocal.h"


#include "mdrv.h"
#include "mnmsgcbencdec.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"
#include "MnComm.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
#include "NasUsimmApi.h"

#include "MnMsgSendSpm.h"
#include "TafStdlib.h"

#if ( VOS_WIN32 == VOS_OS_VER )
#include "wchar.h"
#else
#endif
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID        PS_FILE_ID_MNMSG_SM_COMM_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

VOS_UINT32 MN_MSG_CheckMemAvailable(VOS_VOID);
#define MN_MSG_EF_FIRST_RECORD                              (1)

/* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
MN_MSG_USIM_EFUST_NEED_REFRESH_STRU stUsimFilesNeedRefreshFlag;
/* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

#define MN_MSG_USIM_FILL_BYTE                               0xff

#define MN_MSG_EFSMSP_ADDR_UNIT_LEN                         12
#define MN_MSG_MIN_SRV_PARM_LEN                             28                  /*EFSMSP文件最少的长度*/
#define MN_MSG_MAX_ACTION_NODE_NUM                          60                  /*USIM的最大节点数*/
#define MN_MSG_MAX_USIM_SMS_NUM                             255                 /*USIM中短信的最大条数*/
#define MN_MSG_MAX_USIM_SMSR_NUM                            255                 /*USIM中短信报告的最大条数*/
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
#define MN_MSG_MAX_NVIM_SMS_REC_NUM                         500                 /*NVIM中短信的最大条数*/
#else
#define MN_MSG_MAX_NVIM_SMS_REC_NUM                         0                   /*NVIM中短信的最大条数*/
#endif

/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
#define MN_MSG_MAX_NVIM_SMSR_REC_NUM                        255                 /*NVIM中短信报告的最大条数*/
/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

VOS_CHAR *g_pucSmsFileOnFlash                               = VOS_NULL_PTR;

/* SIM CARD TYPE */
#define MN_MSG_CARD_TYPE_USIM     1
#define MN_MSG_CARD_TYPE_SIM      2

#define TAF_MSG_MIN_DESTINATION_ADDRESS_LEN                 (2)
#define TAF_MSG_MAX_DESTINATION_ADDRESS_LEN                 (11)



/*存储flash短信文件句柄*/
FILE                                   *gfpSmsFlash;

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

extern VOS_UINT8                        g_ucMnOmConnectFlg;
extern VOS_UINT8                        g_ucMnOmPcRecurEnableFlg;

/*****************************************************************************
  3 类型定义
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bEfSmsrState;                           /* USIM中是否存在EfSmsr的标志*/
    VOS_UINT8                           ucSmsrRealRecNum;                       /* 从USIM获得的SMSR实际记录数 */
    VOS_UINT8                           ucSmsrCurRecNum;                        /* 无空闲的记录时,存储的位置*/
    VOS_UINT8                           aucEfSmsrList[MN_MSG_MAX_USIM_SMSR_NUM * MN_MSG_EFSMSR_LEN]; /* 缓存EfSmsr*/
}MN_MSG_USIM_EFSMSR_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmsState;                            /* USIM中是否存在EfSms的标志*/
    VOS_UINT8                           ucSmsRealRecNum;                        /* 从USIM获得的SMS实际记录数 */
    VOS_UINT8                           aucEfSmsList[MN_MSG_MAX_USIM_SMS_NUM * MN_MSG_EFSMS_LEN];/* 缓存EfSms*/
    VOS_UINT8                           aucReserve[3];
}MN_MSG_USIM_EFSMS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmssState;                           /*USIM中是否存在EfSmss的标志*/
    VOS_UINT32                          ulFileLen;
    MN_MSG_SMSS_INFO_STRU               stEfSmssInfo;                           /*EFSMSS的内容*/
    VOS_UINT8                           aucReserve[1];
}MN_MSG_USIM_SMSS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmspState;                           /*USIM中是否存在EfSmsp的标志*/
    VOS_UINT8                           ucSmspRealRecNum;                       /*EFSMSP的记录数目*/
    VOS_UINT8                           aucReserve[3];
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    astEachEfSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];/*第一个为默认值*/
}MN_MSG_USIM_EFSMSP_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucList;                                 /*列表短信时,操作USIM的总记录数*/
    VOS_UINT8                           ucDelete;                               /*删除短信时,操作USIM的总记录数*/
    VOS_UINT8                           ucDeleteBegin;                          /*删除多条短信记录时,一次最多向USIM发送10条,每次向USIM发送开始记录数*/
    VOS_UINT8                           aucReserve[1];
    VOS_BOOL                            bDeleteReportFlag;                      /*删除短信结果是否已经上报给应用*/
    VOS_UINT8                           ucDeleteStaRpt;                         /*删除短信状态报告时,操作USIM的总记录数*/
    VOS_UINT8                           ucDeleteStaRptBegin;                    /*删除多条短信状态记录时,一次最多向USIM发送10条,每次向USIM发送开始记录数*/
    VOS_UINT8                           aucReserve2[2];
    VOS_BOOL                            bDeleteStaRptReportFlag;                /*删除短信状态结果是否已经上报给应用*/
    VOS_UINT8                           ucDeleteEfSmsp;                         /*删除短信文件EFSMSP时,操作USIM的总记录数*/
    VOS_UINT8                           aucReserve3[3];
    VOS_BOOL                            bDeleteEfSmspReportFlag;                /*删除短信参数结果是否已经上报给应用*/
}MN_MSG_SET_USIM_REC_STRU;

typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_MO_SMS_CTRL_STRU;

/*****************************************************************************
 Structure      : NAS_MSG_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC回放工程，存储所有MSG相关的全局变量
 Message origin :
 Note: 该结构已经需要55k的内存，新增全局变量请放入NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST，
       以防内存申请失败导致系统复位。
 2.日    期   : 2011年11月08日
   作    者   : 傅映君/f62575
   修改内容   : DCM&DEVICE，DCM短信接收定制需求，新增enMtCustomize
*****************************************************************************/
#define MN_MSG_BUFFER_SMS_SEG_NUM                             1                 /*USIM中短信的最大条数*/
typedef struct
{
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU f_astMsgOrgSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];
    VOS_UINT8                        f_aucMsgOrgSmsrContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN];
    MN_MSG_CONFIG_PARM_STRU          f_stMsgCfgParm;
    MN_MSG_USIM_EFUST_INFO_STRU      f_stEfUstInfo;                          /*EFUST的内容*/
    MN_MSG_SEND_FAIL_FLAG_U8         f_enMsgSendFailFlag;
    MN_MSG_CLASS0_TAILOR_U8          g_enMsgClass0Tailor;
    VOS_UINT8                        ucMoSmsCtrlFlag;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8   enMtCustomize;
    MN_MSG_RETRY_INFO_STRU           f_stMsgRetryInfo;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    SMR_SMT_MO_REPORT_STRU           f_stMsgRpErrInfo;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    MN_MSG_STORE_MSG_STRU            f_stMsgSmSaved[MN_MSG_BUFFER_SMS_SEG_NUM]; /**/
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST;

typedef struct
{
    MN_MSG_LINK_CTRL_U8              f_enMsgLinkCtrl;
    MN_OPERATION_ID_T                f_tMsgOpId;
    VOS_UINT8                        f_ucMsgInterTpMr;
    VOS_UINT8                        ucSmsRealRecNum;                        /* 从USIM获得的SMS实际记录数 */
    VOS_BOOL                         bEfSmsState;                            /* USIM中是否存在EfSms的标志*/
    VOS_BOOL                         f_bMsgCsRegFlag;
    VOS_BOOL                         f_bMsgPsRegFlag;

    MN_MSG_USIM_STATUS_INFO_STRU     f_stMsgUsimStatusInfo;
    MN_MSG_MO_ENTITY_STRU            f_stMsgMoEntity;
    MN_MSG_MT_ENTITY_STRU            f_stMsgMtEntity;
    MN_MSG_SET_USIM_REC_STRU         f_stMsgSetUsimRec;
    MN_MSG_SET_USIM_INFO_STRU        f_astMsgSetUsimInfo[MN_MSG_MAX_ACTION_NODE_NUM];
    VOS_UINT8                        f_aucMsgOrgSmContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN];
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST;

#define MN_MSG_SEG_USIM_SMS_NUM                                             10
typedef struct
{
    VOS_UINT8                           ucSeqNum;                               /*短信内容消息发送的序号，从0开始计数*/
    VOS_UINT8                           ucMsgNum;                               /*当前消息中有效短信的条数*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucEfSmsList[MN_MSG_SEG_USIM_SMS_NUM * MN_MSG_EFSMS_LEN];/* 缓存EfSms*/
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST;

/*****************************************************************************
 Structure      : NAS_MSG_SDT_MSG_ST
 Description    : PC回放工程，所有MSG相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART1_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART2_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART3_ST;

/*****************************************************************************
  4 变量定义
*****************************************************************************/
LOCAL MN_MSG_MO_BUFFER_STRU            f_stMsgMoBuffer;
LOCAL MN_MSG_MO_ENTITY_STRU            f_stMsgMoEntity;
LOCAL MN_MSG_MT_ENTITY_STRU            f_stMsgMtEntity;
LOCAL MN_MSG_USIM_EFUST_INFO_STRU      f_stEfUstInfo;                          /*EFUST的内容*/
LOCAL MN_MSG_USIM_EFSMSR_INFO_STRU     f_stMsgEfSmsrInfo;                      /*USIM中相关文件的信息*/
LOCAL MN_MSG_USIM_EFSMS_INFO_STRU      f_stMsgEfSmsInfo;
LOCAL MN_MSG_USIM_EFSMSP_INFO_STRU     f_stMsgEfSmspInfo;
LOCAL MN_MSG_USIM_SMSS_INFO_STRU       f_stMsgEfSmssInfo;
LOCAL MN_OPERATION_ID_T                f_tMsgOpId;
LOCAL VOS_UINT8                        f_ucMsgInterTpMr;
LOCAL MN_MSG_CONFIG_PARM_STRU          f_stMsgCfgParm;
LOCAL MN_MSG_SET_USIM_INFO_STRU        f_astMsgSetUsimInfo[MN_MSG_MAX_ACTION_NODE_NUM];
LOCAL MN_MSG_SET_USIM_REC_STRU         f_stMsgSetUsimRec;
LOCAL MN_MSG_USIM_STATUS_INFO_STRU     f_stMsgUsimStatusInfo;
LOCAL MN_MSG_USIM_EFSMSP_DTL_INFO_STRU f_astMsgOrgSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];
LOCAL VOS_UINT8                        f_aucMsgOrgSmContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN];
LOCAL VOS_UINT8                        f_aucMsgOrgSmsrContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
LOCAL VOS_UINT8                        f_aucMsgNvimSmStatus[MN_MSG_MAX_NVIM_SMS_REC_NUM];/*在内存中保留NVIM中短信的状态*/
LOCAL VOS_UINT16                       f_usMsgNvimSmsCurReNum = 0;
#endif

LOCAL MN_MSG_MO_SMS_CTRL_STRU          f_stMsgMoSmsCtrlInfo;
LOCAL VOS_UINT8                        f_ucMsgNvimSmsrCurReNum = 0;
LOCAL VOS_BOOL                         f_bMsgCsRegFlag = VOS_FALSE;
LOCAL VOS_BOOL                         f_bMsgPsRegFlag = VOS_FALSE;
LOCAL MN_MSG_LINK_CTRL_U8              f_enMsgLinkCtrl = MN_MSG_LINK_CTRL_ENABLE;
LOCAL VOS_BOOL                         f_bNeedSendUsim[MN_MSG_MAX_USIM_SMS_NUM];
LOCAL MN_MSG_SEND_FAIL_FLAG_U8         f_enMsgSendFailFlag = MN_MSG_SEND_FAIL_NO_DOMAIN;
LOCAL MN_MSG_RETRY_INFO_STRU           f_stMsgRetryInfo;
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
LOCAL SMR_SMT_MO_REPORT_STRU           f_stMsgRpErrInfo;
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
MN_MSG_CLASS0_TAILOR_U8                g_enMsgClass0Tailor;
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT8                              g_ucSetEfSmspNoRsp = 0;
VOS_UINT8                              g_ucDisableMoRetry = 0;
#endif


/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/
#ifdef __PS_WIN32_RECUR__

/*****************************************************************************
 函 数 名  : NAS_MSG_RestoreContextData_Part1
 功能描述  : 恢复MSG全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年05月14日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
  2.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
  3.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
  4.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求
*****************************************************************************/
VOS_UINT32 NAS_MSG_RestoreContextData_Part1(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART1_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST      *pstOutsideCtx;
    VOS_UINT32                                     ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU                  stMtCustomize;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART1_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART1 == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&f_stMsgCfgParm, &pstOutsideCtx->f_stMsgCfgParm, sizeof(MN_MSG_CONFIG_PARM_STRU));
        PS_MEM_CPY(&f_stEfUstInfo, &pstOutsideCtx->f_stEfUstInfo, sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
        PS_MEM_CPY(f_astMsgOrgSmspInfo,
                   pstOutsideCtx->f_astMsgOrgSmspInfo,
                   (sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU) * MN_MSG_MAX_USIM_EFSMSP_NUM));

        f_stMsgEfSmssInfo.bEfSmssState = f_stEfUstInfo.bEfSmssFlag;
        f_stMsgEfSmspInfo.bEfSmspState = f_stEfUstInfo.bEfSmspFlag;
        f_stMsgEfSmsrInfo.bEfSmsrState = f_stEfUstInfo.bEfSmsrFlag;
        f_stMsgEfSmsInfo.bEfSmsState   = f_stEfUstInfo.bEfSmsFlag;

        PS_MEM_CPY(f_aucMsgOrgSmsrContent,
                   pstOutsideCtx->f_aucMsgOrgSmsrContent,
                   (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN));
        f_enMsgSendFailFlag = pstOutsideCtx->f_enMsgSendFailFlag;
        g_enMsgClass0Tailor = pstOutsideCtx->g_enMsgClass0Tailor;

        PS_MEM_CPY(&f_stMsgRetryInfo, &pstOutsideCtx->f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
        PS_MEM_CPY(&f_stMsgRpErrInfo, &pstOutsideCtx->f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));

        stMtCustomize.ucActFlag     = MN_MSG_NVIM_ITEM_ACTIVE;
        stMtCustomize.enMtCustomize = pstOutsideCtx->enMtCustomize;
        ulRet                       = NV_Write(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                                               &stMtCustomize,
                                               sizeof(stMtCustomize));
        if (NV_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MSG_RestoreContextData_Part1: Fail to write en_NV_Item_SMS_MO_RETRY_PERIOD.");
        }

        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part1 data is restored.");
    }
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : NAS_MSG_RestoreContextData_Part2
 功能描述  : 恢复MSG全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年01月04日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
*****************************************************************************/
VOS_UINT32 NAS_MSG_RestoreContextData_Part2(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART2_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART2_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART2== pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        f_enMsgLinkCtrl = pstOutsideCtx->f_enMsgLinkCtrl;
        f_tMsgOpId = pstOutsideCtx->f_tMsgOpId;
        f_ucMsgInterTpMr = pstOutsideCtx->f_ucMsgInterTpMr;

        f_stMsgEfSmssInfo.stEfSmssInfo.ucLastUsedTpMr = f_ucMsgInterTpMr;

        f_stMsgEfSmsInfo.ucSmsRealRecNum = pstOutsideCtx->ucSmsRealRecNum;
        f_stMsgEfSmsInfo.bEfSmsState = pstOutsideCtx->bEfSmsState;
        f_bMsgCsRegFlag = pstOutsideCtx->f_bMsgCsRegFlag;
        f_bMsgPsRegFlag = pstOutsideCtx->f_bMsgPsRegFlag;

        PS_MEM_CPY(&f_stMsgUsimStatusInfo, &pstOutsideCtx->f_stMsgUsimStatusInfo, sizeof(MN_MSG_USIM_STATUS_INFO_STRU));
        PS_MEM_CPY(&f_stMsgMoEntity, &pstOutsideCtx->f_stMsgMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
        PS_MEM_CPY(&f_stMsgMtEntity,  &pstOutsideCtx->f_stMsgMtEntity,  sizeof(MN_MSG_MT_ENTITY_STRU));
        PS_MEM_CPY(&f_stMsgSetUsimRec, &pstOutsideCtx->f_stMsgSetUsimRec, sizeof(MN_MSG_SET_USIM_REC_STRU));
        PS_MEM_CPY(f_astMsgSetUsimInfo, pstOutsideCtx->f_astMsgSetUsimInfo, sizeof(MN_MSG_SET_USIM_INFO_STRU)*MN_MSG_MAX_ACTION_NODE_NUM);
        PS_MEM_CPY(f_aucMsgOrgSmContent,
                   pstOutsideCtx->f_aucMsgOrgSmContent,
                   (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN));

        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part2 data is restored.");
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : NAS_MSG_RestoreContextData_Part3
 功能描述  : 恢复MSG全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月22日
    作    者   : f62575
    修改内容   : 新生成函数，问题单号：AT2D16941，任意时间点回放
*****************************************************************************/
VOS_UINT32 NAS_MSG_RestoreContextData_Part3(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART3_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART3_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART3 == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&f_stMsgEfSmsInfo.aucEfSmsList[(pstOutsideCtx->ucSeqNum * MN_MSG_EFSMS_LEN)],
                   pstOutsideCtx->aucEfSmsList,
                   (pstOutsideCtx->ucMsgNum * MN_MSG_EFSMS_LEN));
        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part3 data is restored.");
    }

    return MN_ERR_NO_ERROR;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MSG_SndOutsideContextData_Part1
 功能描述  : 把MSG外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年05月14日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
  2.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
  3.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
  4.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求
*****************************************************************************/
VOS_VOID NAS_MSG_SndOutsideContextData_Part1()
{
    NAS_MSG_SDT_MSG_PART1_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART1_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART1_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part1:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid    = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid      = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength         = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST) + 4;
    pSndMsgCB->usMsgID          = MN_MSG_PC_REPLAY_MSG_PART1;
    pSndMsgCB->usReserved       = 0;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgCfgParm, &f_stMsgCfgParm, sizeof(MN_MSG_CONFIG_PARM_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stEfUstInfo, &f_stEfUstInfo, sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
    PS_MEM_CPY(pstOutsideCtx->f_astMsgOrgSmspInfo,
               f_astMsgOrgSmspInfo,
               sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU) * MN_MSG_MAX_USIM_EFSMSP_NUM);
    PS_MEM_CPY(pstOutsideCtx->f_aucMsgOrgSmsrContent,
               f_aucMsgOrgSmsrContent,
               (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN));

    pstOutsideCtx->f_enMsgSendFailFlag = f_enMsgSendFailFlag;
    pstOutsideCtx->g_enMsgClass0Tailor = g_enMsgClass0Tailor;

    pstOutsideCtx->ucMoSmsCtrlFlag     = f_stMsgMoSmsCtrlInfo.ucActFlg;

    PS_MEM_CPY(&pstOutsideCtx->f_stMsgRetryInfo,&f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgRpErrInfo,&f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));

    pstOutsideCtx->enMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;
    MN_MSG_GetMtCustomizeInfo(&pstOutsideCtx->enMtCustomize);

    DIAG_TraceReport(pSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSG_SndOutsideContextData_Part2
 功能描述  : 把MSG外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年01月03日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  Note:
      MSG的变量占内存太大，需要分开发送，否则申请内存会失败，导致单板复位。
  2.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
*****************************************************************************/
VOS_VOID NAS_MSG_SndOutsideContextData_Part2()
{
    NAS_MSG_SDT_MSG_PART2_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART2_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART2_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part2:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid    = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid      = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength         = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST) + 4;
    pSndMsgCB->usMsgID          = MN_MSG_PC_REPLAY_MSG_PART2;
    pSndMsgCB->usReserved       = 0;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;
    pstOutsideCtx->f_enMsgLinkCtrl  = f_enMsgLinkCtrl;
    pstOutsideCtx->f_tMsgOpId       = f_tMsgOpId;

    MN_MSG_GetTpMR(&pstOutsideCtx->f_ucMsgInterTpMr);
    pstOutsideCtx->ucSmsRealRecNum  = f_stMsgEfSmsInfo.ucSmsRealRecNum;

    pstOutsideCtx->bEfSmsState      = f_stMsgEfSmsInfo.bEfSmsState;
    pstOutsideCtx->f_bMsgCsRegFlag  = f_bMsgCsRegFlag;
    pstOutsideCtx->f_bMsgPsRegFlag  = f_bMsgPsRegFlag;

    PS_MEM_CPY(&pstOutsideCtx->f_stMsgUsimStatusInfo, &f_stMsgUsimStatusInfo, sizeof(MN_MSG_USIM_STATUS_INFO_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgMoEntity, &f_stMsgMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgMtEntity,  &f_stMsgMtEntity,  sizeof(MN_MSG_MT_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgSetUsimRec, &f_stMsgSetUsimRec, sizeof(MN_MSG_SET_USIM_REC_STRU));
    PS_MEM_CPY(pstOutsideCtx->f_astMsgSetUsimInfo, f_astMsgSetUsimInfo, sizeof(MN_MSG_SET_USIM_INFO_STRU)*MN_MSG_MAX_ACTION_NODE_NUM);
    PS_MEM_CPY(pstOutsideCtx->f_aucMsgOrgSmContent,
               f_aucMsgOrgSmContent,
               MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN);

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSG_SndOutsideContextData_Part3
 功能描述  : 把MSG外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年2月22日
    作    者   : f62575
    修改内容   : 新生成函数，问题单号：AT2D16941，任意时间点回放
*****************************************************************************/
VOS_VOID NAS_MSG_SndOutsideContextData_Part3()
{
    NAS_MSG_SDT_MSG_PART3_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST      *pstOutsideCtx;
    VOS_UINT8                                     ucLoop;
    VOS_UINT8                                     ucRemainMsgNum;
    VOS_UINT8                                     ucSendMsgNum;
    VOS_UINT8                                     ucTotalSegNum;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART3_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART3_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part2:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid        = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid          = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength             = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST) + 4;
    pSndMsgCB->usMsgID              = MN_MSG_PC_REPLAY_MSG_PART3;
    pSndMsgCB->usReserved           = 0;

    pstOutsideCtx                   = &pSndMsgCB->stOutsideCtx;
    pstOutsideCtx->ucSeqNum         = 0;
    pstOutsideCtx->aucReserved[0]   = 0;
    pstOutsideCtx->aucReserved[1]   = 0;
    ucTotalSegNum                   = (f_stMsgEfSmsInfo.ucSmsRealRecNum + (MN_MSG_SEG_USIM_SMS_NUM - 1))/
                                      MN_MSG_SEG_USIM_SMS_NUM;
    for (ucLoop = 0; ucLoop < ucTotalSegNum; ucLoop++)
    {
        ucSendMsgNum = (VOS_UINT8)(pstOutsideCtx->ucSeqNum * MN_MSG_SEG_USIM_SMS_NUM);
        ucRemainMsgNum = f_stMsgEfSmsInfo.ucSmsRealRecNum - ucSendMsgNum;
        if (ucRemainMsgNum > MN_MSG_SEG_USIM_SMS_NUM)
        {
            pstOutsideCtx->ucMsgNum = MN_MSG_SEG_USIM_SMS_NUM;
        }
        else
        {
            pstOutsideCtx->ucMsgNum = ucRemainMsgNum;
        }
        PS_MEM_CPY(pstOutsideCtx->aucEfSmsList,
                   &f_stMsgEfSmsInfo.aucEfSmsList[(ucSendMsgNum * MN_MSG_EFSMS_LEN)],
                   (pstOutsideCtx->ucMsgNum * MN_MSG_EFSMS_LEN));
        DIAG_TraceReport(pSndMsgCB);
        pstOutsideCtx->ucSeqNum++;
    }

    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

/***********************************************************************
函 数 名  : MN_MSG_PrintConfigParmStru
功能描述  : 打印MN_MSG_CONFIG_PARM_STRU结构数据
输入参数  : pstCfg MN_MSG_CONFIG_PARM_STRU结构数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintConfigParmStru(
    MN_MSG_CONFIG_PARM_STRU             *pstCfg
)
{
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enRcvSmAct ", pstCfg->enRcvSmAct);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enSmMemStore ", pstCfg->enSmMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enRcvStaRptAct ", pstCfg->enRcvStaRptAct);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enStaRptMemStore ", pstCfg->enStaRptMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enCbmMemStore ", pstCfg->enCbmMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enAppMemStatus ", pstCfg->enAppMemStatus);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintMsgEntityStru
功能描述  : 打印MN_MSG_MO_ENTITY_STRU结构数据
输入参数  : pstEntity MN_MSG_MO_ENTITY_STRU结构数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintMsgEntityStru(
    MN_MSG_MO_ENTITY_STRU               *pstEntity
)
{
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: mo status          ", pstEntity->enSmaMoState);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: clientId           ", pstEntity->clientId);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: opId               ", pstEntity->opId);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bEnvelopePending   ", (VOS_INT32)pstEntity->bEnvelopePending);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ucMr               ", pstEntity->ucMr);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSendDomain       ", pstEntity->enSendDomain);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSaveArea         ", pstEntity->enSaveArea);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ulSaveIndex        ", (VOS_INT32)pstEntity->ulSaveIndex);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enTpduType         ", pstEntity->enTpduType);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSmsMoType        ", pstEntity->enSmsMoType);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bReportFlag        ", (VOS_INT32)pstEntity->bReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ucRpDataLen        ", pstEntity->ucRpDataLen);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bStaRptInd        ", (VOS_INT32)pstEntity->bStaRptInd);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintMsgEntityStru
功能描述  : 打印MN_MSG_STORE_MSG_STRU结构数据
输入参数  : pstSmSaved MN_MSG_STORE_MSG_STRU结构数据
            ulSmNum    需要打印短消息的个数
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintStoreMsgStru(
    MN_MSG_STORE_MSG_STRU               *pstSmSaved,
    VOS_UINT32                          ulSmNum
)
{
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;

    for (ulLoop1 = 0; ulLoop1 < ulSmNum; ulLoop1++)
    {
        MN_INFO_LOG2("MN_MSG_PrintStoreMsgStru: index, Used flag", (VOS_INT32)ulLoop1, (VOS_INT32)pstSmSaved->bUsed);
        MN_MSG_PrintMsgEntityStru(&pstSmSaved->stMoInfo);
        for (ulLoop2 = 0; ulLoop2 < MN_MSG_EFSMS_LEN; ulLoop2++)
        {
            MN_INFO_LOG2("MN_MSG_PrintStoreMsgStru: SMS content", (VOS_INT32)ulLoop2, (VOS_INT32)pstSmSaved->aucEfSmContent[ulLoop2]);
        }
        pstSmSaved++;
    }

}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmsrInfoStru
功能描述  : 打印MN_MSG_USIM_EFSMSR_INFO_STRU结构数据
输入参数  : pstUsimSmsr MN_MSG_USIM_EFSMSR_INFO_STRU结构数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmsrInfoStru(
    MN_MSG_USIM_EFSMSR_INFO_STRU        *pstUsimSmsr
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr State flag", (VOS_INT32)pstUsimSmsr->bEfSmsrState);
    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr volume", pstUsimSmsr->ucSmsrRealRecNum);
    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr ocuppy", pstUsimSmsr->ucSmsrCurRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_SMS_NUM; ulLoop++)
    {
        /*Refer 31102 4.2.32 first byte is Zero, then this record is idle.*/
        MN_INFO_LOG2("MN_MSG_PrintSmsrInfoStru: index, SMS index related",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstUsimSmsr->aucEfSmsrList[(MN_MSG_EFSMSR_LEN * ulLoop)]);
    }
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmsInfoStru
功能描述  : 打印MN_MSG_USIM_EFSMS_INFO_STRU结构数据
输入参数  : pstUsimSms MN_MSG_USIM_EFSMS_INFO_STRU结构数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmsInfoStru(
    MN_MSG_USIM_EFSMS_INFO_STRU         *pstUsimSms
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintSmsInfoStru: EfSms State flag", (VOS_INT32)pstUsimSms->bEfSmsState);
    MN_INFO_LOG1("MN_MSG_PrintSmsInfoStru: EfSms volume", pstUsimSms->ucSmsRealRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_SMS_NUM; ulLoop++)
    {
        MN_INFO_LOG2("MN_MSG_PrintSmsInfoStru: index, Sms Status",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstUsimSms->aucEfSmsList[(ulLoop * MN_MSG_EFSMS_LEN)]);
    }
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmspInfoStru
功能描述  : 打印MN_MSG_USIM_EFSMS_INFO_STRU结构数据
输入参数  : pstUsimSmsp MN_MSG_USIM_EFSMSP_INFO_STRU结构数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmspInfoStru(
    MN_MSG_USIM_EFSMSP_INFO_STRU        *pstUsimSmsp
)
{
    VOS_UINT32                          ulLoop;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSmsp;

    MN_INFO_LOG1("MN_MSG_PrintSmspInfoStru: EfSmsp State flag", (VOS_INT32)pstUsimSmsp->bEfSmspState);
    MN_INFO_LOG1("MN_MSG_PrintSmspInfoStru: EfSmsp volume", pstUsimSmsp->ucSmspRealRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_EFSMSP_NUM; ulLoop++)
    {
        pstSmsp = &pstUsimSmsp->astEachEfSmspInfo[ulLoop];
        MN_INFO_LOG2("MN_MSG_PrintSmspInfoStru: index, bUsed flag",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstSmsp->bUsed);
        /*打印MN_MSG_USIM_EFSMSP_DTL_INFO_STRU内容*/
        MN_MSG_PrintSrvParamStru(&pstUsimSmsp->astEachEfSmspInfo[ulLoop].stParm);
    }
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmssInfoStru
功能描述  : 打印MN_MSG_USIM_SMSS_INFO_STRU结构数据
输入参数  : pstUsimSmss MN_MSG_USIM_SMSS_INFO_STRU结构数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmssInfoStru(
    MN_MSG_SMSS_INFO_STRU          *pstUsimSmss
)
{
    MN_INFO_LOG1("MN_MSG_PrintSmssInfoStru: ucLastUsedTpMr", pstUsimSmss->ucLastUsedTpMr);
    MN_INFO_LOG1("MN_MSG_PrintSmssInfoStru: enMemCapExcNotFlag", pstUsimSmss->enMemCapExcNotFlag);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintEfUstInfo
功能描述  : 打印静态变量f_stEfUstInfo
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
  2.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
************************************************************************/
VOS_VOID MN_MSG_PrintEfUstInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmssFlag", (VOS_INT32)f_stEfUstInfo.bEfSmssFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmsFlag", (VOS_INT32)f_stEfUstInfo.bEfSmsFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmsrFlag", (VOS_INT32)f_stEfUstInfo.bEfSmsrFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmspFlag", (VOS_INT32)f_stEfUstInfo.bEfSmspFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bMoSmsCtrlFlag", (VOS_INT32)f_stEfUstInfo.bMoSmsCtrlFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bSmsPpDataFlag", (VOS_INT32)f_stEfUstInfo.bSmsPpDataFlag);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintMsgMoEntity
功能描述  : 打印静态变量f_stMsgMoEntity
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintMsgMoEntity(VOS_VOID)
{
    MN_MSG_PrintMsgEntityStru(&f_stMsgMoEntity);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintMsgMtEntity
功能描述  : 打印静态变量f_stMsgMoEntity
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintMsgMtEntity(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMsgMtEntity: f_stMsgMtEntity.enSmaMtState is ",
                 f_stMsgMtEntity.enSmaMtState);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmsrInfo
功能描述  : 打印静态变量f_stMsgEfSmsrInfo
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmsrInfo(VOS_VOID)
{
    MN_MSG_PrintSmsrInfoStru(&f_stMsgEfSmsrInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmsInfo
功能描述  : 打印静态变量f_stMsgEfSmsInfo
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmsInfo(VOS_VOID)
{
    MN_MSG_PrintSmsInfoStru(&f_stMsgEfSmsInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmspInfo
功能描述  : 打印静态变量f_stMsgEfSmspInfo
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmspInfo(VOS_VOID)
{
    MN_MSG_PrintSmspInfoStru(&f_stMsgEfSmspInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSmssInfo
功能描述  : 打印静态变量f_stMsgEfSmssInfo
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSmssInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintSmssInfo: bEfSmssState", (VOS_INT32)f_stMsgEfSmssInfo.bEfSmssState);
    MN_MSG_PrintSmssInfoStru(&f_stMsgEfSmssInfo.stEfSmssInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintInterTpMr
功能描述  : 打印静态变量f_ucMsgInterTpMr
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintInterTpMr(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintInterTpMr: TpMr", f_ucMsgInterTpMr);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintCfgParm
功能描述  : 打印静态变量f_stMsgCfgParm
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintCfgParm(VOS_VOID)
{
    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintUsimStatusInfo
功能描述  : 打印静态变量f_stMsgCfgParm
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintUsimStatusInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintUsimStatusInfo: ucUsimStatus", f_stMsgUsimStatusInfo.ucUsimStatus);
    MN_INFO_LOG1("MN_MSG_PrintUsimStatusInfo: enPowerState", f_stMsgUsimStatusInfo.enPowerState);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintSetUsimRec
功能描述  : 打印静态变量f_stMsgSetUsimRec
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintSetUsimRec(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucList", f_stMsgSetUsimRec.ucList);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDelete", f_stMsgSetUsimRec.ucDelete);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteBegin", f_stMsgSetUsimRec.ucDeleteBegin);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteStaRpt", f_stMsgSetUsimRec.ucDeleteStaRpt);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteStaRptBegin", f_stMsgSetUsimRec.ucDeleteStaRptBegin);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteStaRptReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteStaRptReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteEfSmsp", f_stMsgSetUsimRec.ucDeleteEfSmsp);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteEfSmspReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteEfSmspReportFlag);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintOpId
功能描述  : 打印静态变量f_tMsgOpId
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年6月17日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintOpId(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintOpId: f_tMsgOpId", f_tMsgOpId);
}

/***********************************************************************
函 数 名  : MN_MSG_PrintDomainRegFlag
功能描述  : 打印SMT中PS域和CS域的注册标志
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年8月13日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_PrintDomainRegFlag(
    VOS_VOID
)
{
    MN_INFO_LOG1("MN_MSG_PrintDomainRegFlag:f_bMsgCsRegFlag ", (VOS_INT32)f_bMsgCsRegFlag);
    MN_INFO_LOG1("MN_MSG_PrintDomainRegFlag:f_bMsgPsRegFlag ", (VOS_INT32)f_bMsgPsRegFlag);
}


/***********************************************************************
函 数 名  : MN_MSG_GetLinkCtrlParam
功能描述  : 获取中继协议链路连续性的控制标志
输入参数  : 无
输出参数  : 无
返 回 值  : 中继协议链路连续性的控制标志
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年7月21日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
MN_MSG_LINK_CTRL_U8 MN_MSG_GetLinkCtrlParam(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetLinkCtrlParam:f_enMsgLinkCtrl ", f_enMsgLinkCtrl);
    return f_enMsgLinkCtrl;
}

/***********************************************************************
函 数 名  : MN_MSG_SetLinkCtrl
功能描述  : 设置中继协议链路连续性的控制标志
输入参数  : setValue - 中继协议链路连续性的控制标志
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR - 设置操作成功
            其他            - 设置操作失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年7月21日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_UpdateLinkCtrlParam(
    MN_MSG_LINK_CTRL_U8                 setValue
)
{
    if (setValue >= MN_MSG_LINK_CTRL_BUTT)
    {
        MN_ERR_LOG("MN_MSG_SetLinkCtrl: invalid set value.");
        return MN_ERR_INVALIDPARM;
    }

    f_enMsgLinkCtrl = setValue;
    return MN_ERR_NO_ERROR;
}

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST  == FEATURE_ON)
#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
/*****************************************************************************
 函 数 名  : MSG_InitFlashMsg
 功能描述  : 初始化FLASH存储介质的ME短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月20日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
                  DTS2011091503912, FLASH文件不存在情况下不做记录读取操作
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
VOS_VOID MSG_InitFlashMsg(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRealSmsNum;
    VOS_UINT32                          ulFileSize;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucContent[MN_MSG_EFSMS_LEN];

    /* 如果FLASH 文件不存在，则不读取FLASH短信记录 */
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_NORM_LOG("MSG_InitFlashMsg: SmsFile not exist.");
        return;
    }

    /* 初始化所有ME短信状态为空闲 */
    PS_MEM_SET(f_aucMsgNvimSmStatus, 0X00, sizeof(f_aucMsgNvimSmStatus));

    PS_MEM_SET(aucContent, 0xff, sizeof(aucContent));

    /* 获取FLASH短信文件长度 */
    ulRet = MN_GetFileSize(gfpSmsFlash, &ulFileSize);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_InitFlashMsg: Get File Size error.");

        return;
    }

    /* 根据FLASH短信文件长度获取有效ME短信容量 */
    ulRealSmsNum = ulFileSize / MN_MSG_EFSMS_LEN;
    if (f_usMsgNvimSmsCurReNum < ulRealSmsNum)
    {
        ulRealSmsNum = f_usMsgNvimSmsCurReNum;
    }

    /* FLASH中的短信序号从0开始逐个读取到指定容量 */
    for (ulIndex = 0; ulIndex < ulRealSmsNum; ulIndex++)
    {
        ulRet = MN_MSG_ReadMsgInFlashByIndex(ulIndex, aucContent);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MSG_InitFlashMsg: Read FLASH SMS Error");
        }
        else
        {
            f_aucMsgNvimSmStatus[ulIndex] = aucContent[0];
        }
    }

    return;
}
#else

/*****************************************************************************
 函 数 名  : MN_MSG_DeliverMsgNotSupport
 功能描述  : 判断UE不支持的短信类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
                  DTS2011091503912, NV_Read接口已经不支持ME短信，此处功能不可用
*****************************************************************************/

LOCAL VOS_VOID MSG_InitNvMsg(VOS_VOID)
{
    /* NV_Read接口已经不支持ME短信，进入此函数意味着异常 */
    MN_WARN_LOG("MSG_InitNvMsg: Get File Size error.");

    return;
}

#endif

/*****************************************************************************
 函 数 名  : MSG_InitMeMsg
 功能描述  : ME短信初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
                  DTS2011091503912, FLASH文件不存在情况下不做记录读取操作
*****************************************************************************/
VOS_VOID MSG_InitMeMsg(VOS_VOID)
{

#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
    MSG_InitFlashMsg();
#else
    MSG_InitNvMsg();
#endif

}
#endif


/***********************************************************************
函 数 名  : MSG_GetNvimParmInfo
功能描述  : 从NVIM中获取保存在NVIM中的短消息参数信息
输入参数  : None
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月15日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2009年12月11日
   作    者   : f62575
   修改内容   : 问题单号:AT2D15875, 单板上电时接收到短信状态报告修改为存储到SIM卡；
 3.日    期   : 2011年3月21日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011031800199，移动短信业务参数初始化过程到MN_MSG_SmInit

 4.日    期   : 2011年12月23日
   作    者   : w00167002
   修改内容   : DTS2011091503912:ME短信文件不存在时，未考虑此异常情况。
                 封装初始化读取短信函数。
  5.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
************************************************************************/
LOCAL VOS_VOID MSG_GetNvimParmInfo(VOS_VOID)
{
    VOS_UINT32                                      ulRet;
    MN_MSG_NVIM_RETRY_PERIOD_STRU                   stNvimRetryPeriod;
    MN_MSG_NVIM_RETRY_INTERVAL_STRU                 stNvimRetryInterval;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU                  stClass0Tailor;
    TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU           stNvimRetryCmSrvRejCfg;
    VOS_UINT32                                      ulLength;

    ulLength = 0;

    MN_INFO_LOG("MSG_GetNvimParmInfo: Step into function.");


    PS_MEM_SET(&stNvimRetryPeriod,0,sizeof(stNvimRetryPeriod));
    ulRet = NV_Read(en_NV_Item_SMS_MO_RETRY_PERIOD, &stNvimRetryPeriod, sizeof(stNvimRetryPeriod));
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stNvimRetryPeriod.ucActFlg))
    {
        f_stMsgRetryInfo.ulRetryPeriod = 1000 *stNvimRetryPeriod.ulRetryPeriod;    /* 需要转化为秒 */
    }
    else
    {
        f_stMsgRetryInfo.ulRetryPeriod = 0;
    }

    PS_MEM_SET(&stNvimRetryInterval,0,sizeof(stNvimRetryInterval));
    ulRet = NV_Read(en_NV_Item_SMS_MO_RETRY_INTERVAL, &stNvimRetryInterval, sizeof(stNvimRetryInterval));
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stNvimRetryInterval.ucActFlg))
    {
        f_stMsgRetryInfo.ulRetryInterval = 1000 *stNvimRetryInterval.ulRetryInterval;/* 需要转化为秒 */
    }
    else
    {
        /* 周期和间隔有一个未激活,则默认为两者都没有激活 */
        f_stMsgRetryInfo.ulRetryPeriod = 0;
        f_stMsgRetryInfo.ulRetryInterval = 0;
    }
    MN_MSG_UpdateRetryPeriod(MN_MSG_ID_WAIT_RETRY_PERIOD,f_stMsgRetryInfo.ulRetryPeriod);
    MN_MSG_UpdateRetryPeriod(MN_MSG_ID_WAIT_RETRY_INTERVAL,f_stMsgRetryInfo.ulRetryInterval);

    PS_MEM_SET(&stClass0Tailor,0,sizeof(stClass0Tailor));

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_CLASS0_TAILOR, &ulLength);

    ulRet = NV_Read(en_NV_Item_SMS_CLASS0_TAILOR, &stClass0Tailor, ulLength);
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stClass0Tailor.ucActFlg))
    {
        g_enMsgClass0Tailor = stClass0Tailor.enClass0Tailor;
    }
    else
    {
        g_enMsgClass0Tailor = MN_MSG_CLASS0_DEF;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MSG_InitMeMsg();
#endif

    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    if (ulLength > sizeof(stNvimRetryCmSrvRejCfg))
    {
        f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = 0;
        return;
    }

    PS_MEM_SET(&stNvimRetryCmSrvRejCfg, 0x0, sizeof(stNvimRetryCmSrvRejCfg));

    ulRet = NV_Read(en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG,
                    &stNvimRetryCmSrvRejCfg,
                    sizeof(stNvimRetryCmSrvRejCfg));

    if (NV_OK != ulRet)
    {
       f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = 0;
       return;
    }

    if (stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum > TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM)
    {
        stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum = TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM;
    }

    f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum;

    PS_MEM_CPY(f_stMsgRetryInfo.aucSmsRetryCmSrvRejCause,
               stNvimRetryCmSrvRejCfg.aucSmsRetryCmSrvRejCause,
               stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum);
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReadAddressFromUsim
 功能描述  : 读取(U)SIM卡中存储的地址到内存；
 输入参数  : pucAddrStr 地址首地址
             bRpAddr    指示地址字符串的编码格式: TP层的TPDU格式的地址或RP层地址编码
                 VOS_TRUE   RP层的地址编码, 参考协议23040 9.1.2.5 Address fields
                 VOS_FALSE  TP层的地址编码, 参考RP层的地址，Refer to 24011 8.2.5.1
 输出参数  : pstBcdAddr MN_MSG_BCD_ADDR_STRU结构的地址
 返 回 值  : 地址获取结果: MN_ERR_NO_ERROR获取成功;
                            其他,获取失败;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月13日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目

*****************************************************************************/
VOS_UINT32  MN_MSG_ReadAddressFromUsim(
    const VOS_UINT8                     *pucAddrStr,
    VOS_BOOL                            bRpAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr
)
{
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    VOS_UINT32                          ulAddrLen;
    VOS_UINT32                          ulRet;

    ulAddrLen = pucAddrStr[0];

    if (MN_MSG_USIM_FILL_BYTE != ulAddrLen)
    {
        ulRet = MN_MSG_DecodeAddress(pucAddrStr,
                                     bRpAddr,
                                     &stAsciiAddr,
                                     &ulAddrLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        ulRet = TAF_STD_ConvertAsciiAddrToBcd(&stAsciiAddr, pstBcdAddr);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    else
    {
        PS_MEM_SET(pstBcdAddr, 0x00, sizeof(MN_MSG_BCD_ADDR_STRU));
    }

    return MN_ERR_NO_ERROR;
}

/***********************************************************************
函 数 名  : MSG_ParseSmsp
功能描述  : 将EFSMSP文件的内容解析为MN_MSG_SRV_PARM_STRU定义的结构
输入参数  : ucLen:EFSMSP文件的长度
            pucSmspContent:EFSMSP文件的内容
输出参数  : pbSrvParmPresent:该文件中是否有参数有效
            pstSrvParm:解析后的数据
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月15日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2010年4月15日
   作    者   : f62575
   修改内容   : AT2D18539, SMSP文件编码错误时, 短信中心地址读取失败;
 3.日    期   : 2010年6月10日
   作    者   : f62575
   修改内容   : DTS2010061000153, 关闭从SMSP文件文件中获取TP-DCS,TP-VP和TP-PID的功能;
 4.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
 5.日    期   : 2013年6月26日
   作    者   : f62575
   修改内容   : V9R1 STK升级
 6.日    期   : 2013年08月23日
   作    者   : f62575
   修改内容   : DTS2011051605439，短信模块短信重新初始化会TP-VP和TP-DCS
 7.日    期   : 2014年9月16日
   作    者   : z00161729
   修改内容   : DTS2014091200106:中国电信4G卡，0x6f42里短信中心号码存在，但indication指示bit为1，表示没有，手机漫游到国外无法获取到短信中心，发不了短信
************************************************************************/
LOCAL VOS_VOID MSG_ParseSmsp(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                     *pucSmspContent,
    VOS_BOOL                            *pbSrvParmPresent,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulRet;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    if (ucLen < MN_MSG_MIN_SRV_PARM_LEN)
    {
        *pbSrvParmPresent = VOS_FALSE;
        return;
    }

    *pbSrvParmPresent = VOS_TRUE;

    /*alpha identifier data:*/
    pstSrvParam->stAlphaIdInfo.ulLen = ucLen - MN_MSG_MIN_SRV_PARM_LEN;
    PS_MEM_CPY(pstSrvParam->stAlphaIdInfo.aucData,
               pucSmspContent,
               pstSrvParam->stAlphaIdInfo.ulLen);

    ulPos       = pstSrvParam->stAlphaIdInfo.ulLen;

    /*parameter idicator data:*/
    /*lint -e961*/
    pstSrvParam->ucParmInd = pucSmspContent[ulPos++];
    /*lint +e961*/

    /*TP-destination address data:*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
    {
        ulRet = MN_MSG_ReadAddressFromUsim(&pucSmspContent[ulPos],
                                           VOS_FALSE,
                                           &pstSrvParam->stDestAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ParseSmsp: Fail to get Destination.");
            PS_MEM_SET(&(pstSrvParam->stDestAddr), 0x00, sizeof(pstSrvParam->stDestAddr));
        }
    }
    else
    {
        PS_MEM_SET(&(pstSrvParam->stDestAddr), 0x00, sizeof(pstSrvParam->stDestAddr));
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TP-service centre address data:*/
    /* 在解析短信中心号码前，先判断一下短信中心号码长度字节，如果长度有效，
       就把ind的标示bit置为存在短信中心号码，9061 nv项可配置
       24011 8.2.5.2 Destination address element
       In the case of MO transfer, this element contains the destination Service Centre address.
       The RP Destination Address information element is coded as shown in figure 8.6/3GPP TS 24.011.
       The RP Destination Address is a type 4 information element. In the mobile station to network
       direction the minimum value of the length octet is 2 and the maximum value is 11. In the network to mobile station direction,
       the value of the length octet of the element is set to 0.*/
    if ((MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetScAddrIgnoreScIndication)
     && (pucSmspContent[ulPos] >= TAF_MSG_MIN_DESTINATION_ADDRESS_LEN)
     && (pucSmspContent[ulPos] <= TAF_MSG_MAX_DESTINATION_ADDRESS_LEN))
    {
        pstSrvParam->ucParmInd &= ~MN_MSG_SRV_PARM_MASK_SC_ADDR;
    }

    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR))
    {
        ulRet = MN_MSG_ReadAddressFromUsim(&pucSmspContent[ulPos],
                                           VOS_TRUE,
                                           &pstSrvParam->stScAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ParseSmsp: Fail to get service centre.");
            PS_MEM_SET(&(pstSrvParam->stScAddr), 0x00, sizeof(pstSrvParam->stScAddr));
        }
    }
    else
    {
        PS_MEM_SET(&(pstSrvParam->stScAddr), 0x00, sizeof(pstSrvParam->stScAddr));
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
        /*TP-PID:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_PID))
        {
            pstSrvParam->ucPid = pucSmspContent[ulPos];
        }
        else
        {
            pstSrvParam->ucPid = 0;
        }
    }
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
    ulPos++;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
        /*TP-DCS:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DCS))
        {
            pstSrvParam->ucDcs = pucSmspContent[ulPos];
        }
        else
        {
            pstSrvParam->ucDcs = 0;
        }
    }
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
    ulPos++;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
         /*TP-VP:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_VALIDITY))
        {
            /*lint -e961*/
            pstSrvParam->ucValidPeriod = pucSmspContent[ulPos++];
            /*lint +e961*/
        }
        else
        {
            pstSrvParam->ucValidPeriod = 0;
        }
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    return;
}

/***********************************************************************
函 数 名  : MSG_GetUsimFileReq
功能描述  : 请求USIM获取相关文件，请求失败后,如果未超过次数限制,则继续尝试
输入参数  : usEfId:请求获取文件的ID
输出参数  : 无
返 回 值  : VOS_UINT32:向USIM发送请求的结果
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数

  2.日    期   : 2010年3月15日
    作    者   : zhoujun /z40661
    修改内容   : VOS_TaskDelay清理
  3.日    期   : 2011年11月26日
    作    者   : f62575
    修改内容   : DTS2011112100079 EFSMSP文件存在第0条以外记录错误时，
                 解决短信中心读取失败问题，只读取目前使用到的第一条记录，
************************************************************************/
LOCAL VOS_UINT32 MSG_GetUsimFileReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

    ulRet = USIMM_API_WRONG_PARA;

    switch (usEfId)
    {
        case USIMM_USIM_EFUST_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
#if ( VOS_WIN32 == VOS_OS_VER )
            if (0 == g_ucSetEfSmspNoRsp)
            {
                ulRet = MN_MSG_SndUsimGetFileReq(usEfId, MN_MSG_EF_FIRST_RECORD);
            }
#else
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, MN_MSG_EF_FIRST_RECORD);
#endif

            break;
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            ulRet = MN_MSG_SndUsimGetMaxRecReq(usEfId);
            break;
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        default:
            break;
    }

    return ulRet;
}

/* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SetSmsFileRefreshFlag
 功能描述  : 设置SMS文件是否需要更新的标示
 输入参数  : VOS_UINT16    usEfId, VOS_UINT8 ucFileRefreshFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : V9R1 STK升级

  2.日    期   : 2015年03月14日
    作    者   : y00245242
    修改内容   : USIMM卡接口调整

*****************************************************************************/
 VOS_VOID MN_MSG_SetSmsFileRefreshFlag (VOS_UINT16 usEfId, VOS_UINT8 ucFileRefreshFlag)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmssNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMSP_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmspNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMS_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmsNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMSR_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmsrNeedRefreshFlag = ucFileRefreshFlag;
             break;

       default:
            MN_WARN_LOG("MN_MSG_SetSmsFileRefreshFlag: The input file name is invalid.");
            break;
    }
}
/* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

/* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_GetSmsFileRefreshFlag
 功能描述  : 设置SMS文件是否需要更新的标示
 输入参数  : VOS_UINT16    usEfId
 输出参数  : VOS_UINT8
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : V9R1 STK升级

*****************************************************************************/
VOS_UINT8 MN_MSG_GetSmsFileRefreshFlag (VOS_UINT16 usEfId)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmssNeedRefreshFlag;

        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmspNeedRefreshFlag;

        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmsNeedRefreshFlag;

        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmsrNeedRefreshFlag;

       default:
            MN_WARN_LOG("MN_MSG_GetSmsFileRefreshFlag: The input file name is invalid.");
            return VOS_FALSE;
    }
}
/* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

/***********************************************************************
函 数 名  : MN_MSG_GetUsimParmReq
功能描述  : 请求USIM获取相关文件的参数
输入参数  : usEfId:请求获取文件的ID
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2009年10月28日
   作    者   : f62575
   修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
 3.日    期   : 2010年2月23日
   作    者   : f62575
   修改内容   : 问题单号：增加短信功能任意点回放功能
 4.日    期   : 2013年7月9日
   作    者   : l00208543
   修改内容   :  V9R1 STK升级项目
************************************************************************/
VOS_VOID MN_MSG_GetUsimParmReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

     /* Modified by l00208543 for V9R1 STK升级, 2013-07-09, begin  */
     /* 读取文件的条件发生变化，由文件存在就读取改为文件存在且需要更新才读取 */

    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmssFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                        break;
                    }
                }
            }
            /* fall through */
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmspFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
            MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
            /* fall through */
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmsFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
            /* fall through */
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmsrFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
        /* Modified by l00208543 for V9R1 STK升级, 2013-07-09, end */

            /* fall through */
       default:
            /*所有节点都加入失败,则置上电完成*/
            f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_ON;

            /*向应用上报初始化完成*/
            MN_MSG_SmInitFinish(MN_CLIENT_ALL);

            #ifndef __PS_WIN32_RECUR__

            if ( (VOS_TRUE == g_ucMnOmConnectFlg)
              && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
            {
                NAS_MSG_SndOutsideContextData_Part1();
                NAS_MSG_SndOutsideContextData_Part2();
                NAS_MSG_SndOutsideContextData_Part3();
            }
            #endif

            break;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReadMsgNvimInfo
 功能描述  : 读取短信NVIM
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月1日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_MSG_ReadMsgNvimInfo( VOS_VOID )
{
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMeStorageEnable;

    MN_MSG_GetSmsServicePara(&f_stMsgCfgParm, &enMeStorageEnable);
    MN_MSG_MtSpecificFeatureInit();

    MN_MSG_CloseSmsCapabilityFeatureInit();
}

/***********************************************************************
函 数 名  : MN_MSG_SmInit
功能描述  : 初始化短信模块的静态变量
输入参数  : None
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月15日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2009年12月9日
    作    者   : f62575
    修改内容   : 问题单号:AT2D15782, 短信存储区满时接收到短信状态报告给网络回复RP-ACK消息，
                                 与标竿相同情况下回复RP-ERROR(错误原因值22内存满不一致)；
 3.日    期   : 2011年02月09日
   作    者   : w00166186
   修改内容   : 增加对FLASH存储短信的处理
 4.日    期   : 2011年3月21日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011031800199，移动短信业务参数初始化过程到MN_MSG_SmInit
 5.日    期   : 2011年6月10日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011061006066, EM三期短信定制需求
 6.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加关闭短信功能定制
 7.日    期   : 2012年3月2日
   作    者   : 傅映君/f62575
   修改内容   : C50_IPC Project, 短信初始化过程增加FDN本地配置获取
 8.日    期   : 2013年7月13日
   作    者   : l00208543
   修改内容   : STK升级项目，MSG_GetNvimParmInfo修改为始终调用
 9.日    期   : 2013年10月18日
   作    者   : w00167002
   修改内容   : NETSCAN:将CNMI设置的MT type类型传输给TAF。在<MT>=3，收到CLASS3
                 短信时候，按照+CMT方式上报。
                初始话TAF MSG模块中保存的<MT>=0,跟AT模块保持一致;
10.日    期   : 2014年03月04日
   作    者   : f62575
   修改内容   : DTS2013091009786 支持通过产品形态和版本区分FLASH文件根目录
************************************************************************/
VOS_VOID MN_MSG_SmInit(VOS_VOID)
{
    VOS_UINT32                          i;

    PS_MEM_SET(&f_stMsgEfSmsrInfo,0X00,sizeof(f_stMsgEfSmsrInfo));
    PS_MEM_SET(&f_stMsgEfSmsInfo,0X00,sizeof(f_stMsgEfSmsInfo));
    PS_MEM_SET(&f_stMsgEfSmssInfo,0X00,sizeof(f_stMsgEfSmssInfo));
    PS_MEM_SET(&f_stMsgEfSmspInfo,0X00,sizeof(f_stMsgEfSmspInfo));

    PS_MEM_SET(&f_stEfUstInfo,0X00,sizeof(f_stEfUstInfo));
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    PS_MEM_SET(f_aucMsgNvimSmStatus,0X00,MN_MSG_MAX_NVIM_SMS_REC_NUM);
#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
        if(VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_NORM_LOG("MN_MSG_SmInit:Open SmsFile Fail.\n");
        }
    }
#endif
#endif
    f_ucMsgNvimSmsrCurReNum= 0;

    f_stMsgEfSmssInfo.stEfSmssInfo.enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
    f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_BEGIN;
    f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_NOT_EXIST;


    f_stMsgCfgParm.enSmsServVersion = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    f_stMsgCfgParm.enMtType         = MN_MSG_CNMI_MT_NO_SEND_TYPE;

    MN_MSG_ReadMsgNvimInfo();

    f_ucMsgInterTpMr = 1;
    for (i = 0; i < MN_MSG_MAX_USIM_SMS_NUM; i++ )
    {
        f_bNeedSendUsim[i] = VOS_FALSE;
    }
    PS_MEM_SET(&f_stMsgRetryInfo,0,sizeof(f_stMsgRetryInfo));
    g_enMsgClass0Tailor = MN_MSG_CLASS0_DEF;

    MN_MSG_InitMoBuffer();
    MN_MSG_DestroyMoInfo();
    MN_MSG_DestroyMtInfo();

    PS_MEM_SET(f_aucMsgOrgSmContent,(VOS_CHAR)0XFF,MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN);
    PS_MEM_SET(f_aucMsgOrgSmsrContent,(VOS_CHAR)0XFF,MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN);
    PS_MEM_SET(f_astMsgOrgSmspInfo,(VOS_CHAR)0XFF,MN_MSG_MAX_USIM_EFSMSP_NUM * sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        MN_MSG_DestroyUsimNode(i);
    }

    PS_MEM_SET(&f_tMsgOpId,0X00,sizeof(f_tMsgOpId));
    PS_MEM_SET(&f_stMsgSetUsimRec,0X00,sizeof(f_stMsgSetUsimRec));
    f_enMsgSendFailFlag = MN_MSG_SEND_FAIL_NO_DOMAIN;

    /*初始化USIM中的相关参数*/
    MN_MSG_InitParm();

    MN_MSG_GetFdnMeCfg();

    /*初始化定时器相关参数*/
    MN_MSG_InitAllTimers();

    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, begin */
    MSG_GetNvimParmInfo();
    /* Modified by l00208543 for V9R1 STK升级, 2013-07-10, end */

}


/*****************************************************************************
 函 数 名  : MN_MSG_GetMoState
 功能描述  : 获取当前是否有短信正在发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_MO_STATE_ENUM_U8  - 当前的enSmaMoState状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_MSG_MO_STATE_ENUM_U8 MN_MSG_GetMoState(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetMoState: f_stMsgMoEntity.enSmaMoState is ", f_stMsgMoEntity.enSmaMoState);
    return f_stMsgMoEntity.enSmaMoState;
}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SetMtRouteStackType
 功能描述  : 设置MT MSG消息从哪种栈路由，即IMS or PS stack
 输入参数  : enSendOnStackType  短消息路由类型
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SetMoRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    f_stMsgMoEntity.enMsgSignallingType = enMsgSignallingType;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoRouteStackType
 功能描述  : 获取MO MSG消息从哪种栈路由，IMS or PS stack
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  - 消息路由栈类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMoRouteStackType(VOS_VOID)
{
    return f_stMsgMoEntity.enMsgSignallingType;
}
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtState
 功能描述  : 获取当前是否有短信增长接收
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_MT_STATE_ENUM_U8  - 当前的enSmaMtState状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_MSG_MT_STATE_ENUM_U8 MN_MSG_GetMtState(VOS_VOID)
{
    return f_stMsgMtEntity.enSmaMtState;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-21, begin */
/*****************************************************************************
 函 数 名  : TAF_MSG_SetMtState
 功能描述  : 设置MT 状态
 输入参数  : enSendOnStackType  MT状态
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_SetMtState(
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState
)
{
    f_stMsgMtEntity.enSmaMtState = enSmaMtState;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-21, end */

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SetMtRouteStackType
 功能描述  : 设置MT MSG消息从哪种栈路由，即IMS or PS stack
 输入参数  : enSendOnStackType  短消息路由类型
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SetMtRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    f_stMsgMtEntity.enMsgSignallingType = enMsgSignallingType;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtRouteStackType
 功能描述  : 获取MT MSG消息从哪种栈路由，IMS or PS stack
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_ROUTE_STACK_TYPE_ENUM_UINT32  - 消息路由栈类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMtRouteStackType(VOS_VOID)
{
    return f_stMsgMtEntity.enMsgSignallingType;
}
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */


/*****************************************************************************
 函 数 名  : MN_MSG_GetMoEntity
 功能描述  : 获取当前发送短信的相关状态
 输入参数  : 无
 输出参数  : pstMoEntity:当前发送短信的相关状态
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetMoEntity(
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
)
{
    PS_MEM_CPY(pstMoEntity,&f_stMsgMoEntity,sizeof(MN_MSG_MO_ENTITY_STRU));
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetStoreMsgIndex
 功能描述  : 获取当前是否还有空间缓存短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前缓存短信的位置

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年6月29日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
  3.日    期   : 2011年12月25日
    作    者   : w00167002
    修改内容   : DTS2011102003157:软关机时Shell口异常打印;短消息的无效索引指示
                  由0xff更改为0xffffffff。
  4.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 2012082906141 解决数据卡STK短信群发失败问题
*****************************************************************************/
VOS_UINT32 MN_MSG_GetStoreMsgIndex(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    /*获取当前空闲缓存；*/
    for(i = 0; i < f_stMsgMoBuffer.ulTotal; i++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + i;
        if (VOS_FALSE == pstMoBuffer->bUsed)
        {
            ulIndex = i;
            break;
        }
    }

    return ulIndex;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SaveStoreMsg
 功能描述  : 将短信存入缓存空间
 输入参数  : ulIndex:存入短信的位置
             pstMoEntity:存入短信的相关参数
             pucEfSmContent:存入EFSMS文件中短信的内容
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_SaveStoreMsg(
    VOS_UINT32                          ulIndex,
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const VOS_UINT8                     *pucEfSmContent
)
{
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    if (ulIndex >= ulTotal)
    {
        MN_ERR_LOG("MN_MSG_SaveStoreMsg: Invalid enulIndex. ");
        return;
    }

    /*若缓存中已存在一个SMMA消息，则丢弃当前待缓存的SMMA消息*/
    if (MN_MSG_MO_TYPE_SMMA == pstMoEntity->enSmsMoType)
    {
        for (ulLoop = 0; ulLoop < f_stMsgMoBuffer.ulTotal; ulLoop++)
        {
            pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
            if (VOS_FALSE == pstMoBuffer->bUsed)
            {
                if (MN_MSG_MO_TYPE_SMMA == pstMoBuffer->stMoInfo.enSmsMoType)
                {
                    return;
                }
            }
        }
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->bUsed = VOS_TRUE;
    PS_MEM_CPY(&pstMoBuffer->stMoInfo, pstMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
    PS_MEM_CPY(pstMoBuffer->aucEfSmContent, pucEfSmContent, MN_MSG_EFSMS_LEN);
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetStoreMsg
 功能描述  : 获取缓存中的一条短信
 输入参数  : 无
 输出参数  : pstStoreMsg:缓存中的消息内容
 返 回 值  : 缓存所在的索引,如果为MN_MSG_NO_AVAILABLE_REC,则表明没有缓存消息

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数

  2.日    期   : 2011年12月25日
    作    者   : w00167002
    修改内容   : DTS2011102003157:软关机时Shell口异常打印;短消息的无效索引指示
                  由0xff更改为0xffffffff。
*****************************************************************************/
VOS_UINT32  MN_MSG_GetStoreMsg(
    MN_MSG_STORE_MSG_STRU               *pstStoreMsg
)
{
    VOS_UINT32                          i;

    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    for (i = 0; i < ulTotal; i++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + i;
        if (VOS_TRUE == pstMoBuffer->bUsed)
        {
            PS_MEM_CPY(pstStoreMsg, pstMoBuffer,sizeof(MN_MSG_STORE_MSG_STRU));

            ulSaveIndex = i;
            break;
        }
    }
    return ulSaveIndex;
}

/*****************************************************************************
 函 数 名  : MN_MSG_FreeStoreMsg
 功能描述  : 释放缓存中的一条消息
 输入参数  : ulIndex:释放消息的索引
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_FreeStoreMsg(
    VOS_UINT32                          ulIndex
)
{
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    if (ulIndex >= ulTotal)
    {
        MN_ERR_LOG("MN_MSG_FreeStoreMsg: Invalid enulIndex. ");
        return;
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->bUsed = VOS_FALSE;
    PS_MEM_SET(&pstMoBuffer->stMoInfo, 0X00, sizeof(MN_MSG_MO_ENTITY_STRU));
}

/*****************************************************************************
 函 数 名  : MN_MSG_CreateMoInfo
 功能描述  : 根据输入参数创建f_stMsgMoEntity中相关参数
 输入参数  : pstMoEntity    - 当前发送短信相关信息
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE
  3.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报CS域业务状态
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoInfo(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity
)
{
    PS_MEM_CPY(&f_stMsgMoEntity,pstMoEntity,sizeof(MN_MSG_MO_ENTITY_STRU));

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    /* 更新短信业务是否存在标志 */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMoEntity.enMsgSignallingType)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_TRUE);
    }
    else
    {
        if (MN_MSG_SEND_DOMAIN_CS == f_stMsgMoEntity.enSendDomain)
        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_TRUE);

            /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */
        }
        else
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_TRUE);
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateMoSaveInfo
 功能描述  : 更新f_stMsgMoEntity中存储的相关参数
 输入参数  : enSaveArea     - 发送短信的存储区域
             ucSaveIndex    - 发送短信的存储位置
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateMoSaveInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea,
    VOS_UINT32                          ulSaveIndex
)
{
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != f_stMsgMoEntity.enSmaMoState)
    {
        return;
    }

    f_stMsgMoEntity.enSaveArea  = enSaveArea;
    f_stMsgMoEntity.ulSaveIndex = ulSaveIndex;
    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateSmaMoState
 功能描述  : 更新短信发送实体状态
 输入参数  : MN_MSG_MO_STATE_ENUM_U8             enSmaMoState  待更新的短信发送实体状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月22日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MSG_UpdateSmaMoState(
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState
)
{
    f_stMsgMoEntity.enSmaMoState = enSmaMoState;
}

/***********************************************************************
函 数 名  : MN_MSG_MoRetryFlag
功能描述  : 获取短信重传功能标记
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE 当前启用了短信重传功能，VOS_FALSE 当前没有启用重传功能；
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2009年09月01日
   作    者   : f62575
   修改内容   : 新生成函数
 2.日    期   : 2013年8月3日
   作    者   : z60575
   修改内容   : TQE修改
************************************************************************/
VOS_UINT32 MN_MSG_MoRetryFlag(
    VOS_VOID
)
{
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);
    if (0 != stRetryInfo.ulRetryPeriod)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/***********************************************************************
函 数 名  : TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo
功能描述  : Destroy MO时，更新SMS业务是否存在标志
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2014年03月01日
   作    者   : s00217060
   修改内容   : CS域业务状态变化时通知MTC
************************************************************************/
VOS_VOID TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo(VOS_VOID)
{
    /*
        有同时收发短信的情况，MO Destroy时，有可能还有MT流程存在
        Destroy IMS域MO时,不存在IMS域MT流程,把IMS标志置为FALSE
        Destroy CS域MO时,不存在CS域MT流程,把CS标志置为FALSE
        Destroy PS域MO时,不存在PS域MT流程,把PS标志置为FALSE
   */

    /* MT状态为NULL，清除所有的标志 */
    if (MN_MSG_MT_STATE_NULL == f_stMsgMtEntity.enSmaMtState)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);

        /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, end */

        return;
    }

    /* Destroy IMS域MO时,不存在IMS域MT流程,把IMS标志置为FALSE */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMoEntity.enMsgSignallingType)
    {
        if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP != f_stMsgMtEntity.enMsgSignallingType)
        {
            TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }
    else
    {
        /* Destroy CS域MO时,不存在CS域MT流程,把CS标志置为FALSE */
        if ( (MN_MSG_SEND_DOMAIN_CS == f_stMsgMoEntity.enSendDomain)
          && (MN_MSG_RCV_DOMAIN_CS != f_stMsgMtEntity.enRcvDomain) )

        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);

            /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, end */
        }
        /* Destroy PS域MO时,不存在PS域MT流程,把PS标志置为FALSE */
        else if ( (MN_MSG_SEND_DOMAIN_PS == f_stMsgMoEntity.enSendDomain)
               && (MN_MSG_RCV_DOMAIN_PS != f_stMsgMtEntity.enRcvDomain) )
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }
}

/***********************************************************************
函 数 名  : TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo
功能描述  : Destryoy MT时，更新SMS业务是否存在标志
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2014年03月01日
   作    者   : s00217060
   修改内容   : CS域业务状态变化时通知MTC
************************************************************************/
VOS_VOID TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo(VOS_VOID)
{
    /*
        有同时收发短信的情况，MT Destroy时，有可能还有MO流程存在
        Destroy IMS域MT时,不存在IMS域MO流程,把IMS标志置为FALSE
        Destroy CS域MT时,不存在CS域MO流程,把CS标志置为FALSE
        Destroy PS域MT时,不存在PS域MO流程,把PS标志置为FALSE
   */

    /* MO状态为NULL，清除所有的标志 */
    if (MN_MSG_MO_STATE_NULL == f_stMsgMoEntity.enSmaMoState)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);

        /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, end */
        return;
    }

    /* Destroy IMS域MT时,不存在IMS域MO流程,把IMS标志置为FALSE */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMtEntity.enMsgSignallingType)
    {
        if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP != f_stMsgMoEntity.enMsgSignallingType)
        {
            TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        }
    }
    else
    {
        /* Destroy CS域MT时,不存在CS域MO流程,把CS标志置为FALSE */
        if ( (MN_MSG_RCV_DOMAIN_CS == f_stMsgMtEntity.enRcvDomain)
          && (MN_MSG_SEND_DOMAIN_CS != f_stMsgMoEntity.enSendDomain) )
        {

            TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);

            /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by s00217060 for CS域业务状态变化时通知MTC, 2014/03/01, end */
        }

        /* Destroy PS域MT时,不存在PS域MO流程,把PS标志置为FALSE */
        else if ( (MN_MSG_RCV_DOMAIN_PS == f_stMsgMtEntity.enRcvDomain)
               && (MN_MSG_SEND_DOMAIN_PS != f_stMsgMoEntity.enSendDomain) )
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }

}
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/*****************************************************************************
 函 数 名  : MN_MSG_DestroyMoInfo
 功能描述  : 清空f_stMsgMoEntity中相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE
  3.日    期   : 2013年7月15日
    作    者   : y00245242
    修改内容   : 增加对MO的栈路由初始化，default为TAF_MSG_SIGNALLING_TYPE_BUTT

  4.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报CS域业务状态
  5.日    期   : 2013年09月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目，清除发送域
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMoInfo(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    /* 更新业务标识时，要用到MO实体信息，要求清除实体信息放在更新标识后面 */
    TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo();

    f_stMsgMoEntity.enSmaMoState = MN_MSG_MO_STATE_NULL;
    f_stMsgMoEntity.bEnvelopePending = VOS_FALSE;
    f_stMsgMoEntity.bReportFlag = VOS_FALSE;
    f_stMsgMoEntity.enSaveArea = MN_MSG_MEM_STORE_MAX;
    f_stMsgMoEntity.ulSaveIndex = 0x00;
    f_stMsgMoEntity.enSmsMoType = MN_MSG_MO_TYPE_MAX;
    f_stMsgMoEntity.opId = 0x00;
    f_stMsgMoEntity.clientId = 0x00;
    f_stMsgMoEntity.ucMr = 0x00;
    f_stMsgMoEntity.ucRpDataLen = 0X00;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    f_stMsgMoEntity.enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_BUTT;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
    f_stMsgMoEntity.enSendDomain        = MN_MSG_SEND_DOMAIN_NO;
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

    PS_MEM_SET(f_stMsgMoEntity.aucRpDataInfo,0X00,MN_MSG_MAX_RPDATA_LEN);
    PS_MEM_SET(&f_stMsgRpErrInfo,0,sizeof(f_stMsgRpErrInfo));

    /* 当前没有设置重发则清除发送失败记录
       避免其对后续发送流程的影响 */
    ulRet = MN_MSG_MoRetryFlag();
    if (TAF_TRUE != ulRet)
    {
        MN_MSG_UpdateSendFailFlag(MN_MSG_SEND_FAIL_NO_DOMAIN);
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

}

/*****************************************************************************
 函 数 名  : MN_MSG_CreateMtInfo
 功能描述  : 创建g_stSmaMtEntity中相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE
  3.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报CS域业务状态
*****************************************************************************/
VOS_VOID MN_MSG_CreateMtInfo(VOS_VOID)
{
    f_stMsgMtEntity.enSmaMtState = MN_MSG_MT_STATE_WAIT_REPORT_REQ;

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
    /* 更新短信业务是否存在标志 */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMtEntity.enMsgSignallingType)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_TRUE);
    }
    else
    {
        if (MN_MSG_RCV_DOMAIN_CS == f_stMsgMtEntity.enRcvDomain)
        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_TRUE);

            /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */
        }
        else
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_TRUE);
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_DestroyMtInfo
 功能描述  : 清空g_stSmaMtEntity中相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年6月17日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE
  3.日    期   : 2013年7月15日
    作    者   : y00245242
    修改内容   : 增加初始化MT栈路由初始化，default为TAF_MSG_SIGNALLING_TYPE_BUTT
  4.日    期   : 2013年08月19日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目，给MTC上报CS域业务状态
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMtInfo(VOS_VOID)
{
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */

    /* 更新业务标识时，要用到MT实体信息，要求清除实体信息放在更新标识后面 */
    TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo();

    f_stMsgMtEntity.enSmaMtState = MN_MSG_MT_STATE_NULL;

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    f_stMsgMtEntity.enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_BUTT;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    f_stMsgMtEntity.enRcvDomain  = MN_MSG_RCV_DOMAIN_BUTT;

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */
}


/*****************************************************************************
 函 数 名  : MN_MSG_CreateNewUsimNode
 功能描述  : 向USIM发起异步操作,由于USIM的节点数有限,调用此函数查看是否有空闲的节点数,
             如果有空闲节点,则填写该节点相关信息
 输入参数  : pstSmaUsimInfo  - 创建节点相关信息
 输出参数  : pulIndex        - 节点所在索引
 返 回 值  : VOS_OK        - 找到空闲的f_astMsgSetUsimInfo
             VOS_ERR       - 未找到空闲的f_astMsgSetUsimInfo

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_CreateNewUsimNode(
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
)
{
    VOS_UINT32                          i;

    MN_INFO_LOG("MN_MSG_CreateNewUsimNode: step into function.");
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        MN_NORM_LOG1("MN_MSG_CreateNewUsimNode: f_astMsgSetUsimInfo[i].bUsed is ", (VOS_INT32)f_astMsgSetUsimInfo[i].bUsed);
        if (VOS_FALSE == f_astMsgSetUsimInfo[i].bUsed)
        {
            PS_MEM_SET(&f_astMsgSetUsimInfo[i].stUsimInfo,0X00,sizeof(MN_MSG_USIM_INFO_STRU));
            PS_MEM_CPY(&f_astMsgSetUsimInfo[i].stUsimInfo,pstSmaUsimInfo,sizeof(MN_MSG_USIM_INFO_STRU));
            *pulIndex = i;
            f_astMsgSetUsimInfo[i].bUsed = VOS_TRUE;
            return VOS_OK;
        }
    }
    /*不允许走到这里*/
    MN_ERR_LOG("MN_MSG_CreateNewUsimNode: failed to create action node.");;
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_DestroyUsimNode
 功能描述  : 清空内存中索引为ucIndex的USIM节点相关信息
 输入参数  : ulIndex - 操作USIM节点的记录数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年12月14日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_DestroyUsimNode(
    VOS_UINT32                          ulIndex
)
{
    if (ulIndex >= MN_MSG_MAX_ACTION_NODE_NUM)
    {
        MN_ERR_LOG("MN_MSG_DestroyUsimNode: Invalid enulIndex. ");
        return;
    }
    PS_MEM_SET(&f_astMsgSetUsimInfo[ulIndex],0X00,sizeof(MN_MSG_USIM_INFO_STRU));
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateUstInfo
功能描述  : 更新内存中保留的EFSMSS文件存在的标志以
输入参数  : pstSmsUstInfo:EFSMSS文件的内容
输出参数  : 无
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2010年10月29日
   作    者   : lijun 00171473
   修改内容   : DTS2010102300072, 关闭E5的短信功能
 3.日    期   : 2011年6月16日
   作    者   : 傅映君/f62575
   修改内容   : 问题单号DTS2011062201273 MO SMS CONTROL
 4.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
 5.日    期   : 2012年4月5日
   作    者   : l00171473
   修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
 6.日    期   : 2013年6月5日
   作    者   : w00242748
   修改内容   : svlte和usim接口调整
 7.日    期   : 2013年7月29日
   作    者   : y00245242
   修改内容   : 适配新的USIM接口
************************************************************************/
VOS_VOID MN_MSG_UpdateUstInfo()
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* E5关闭短信功能 */
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
    f_stEfUstInfo.bEfSmsFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMS);
    f_stEfUstInfo.bEfSmssFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMS);

    /* PS RECUR因为不能通过定时器超时结束初始化过程关闭SMSR文件读取功能 E5关闭短信功能 */
#ifdef __PS_WIN32_RECUR__
    f_stEfUstInfo.bEfSmsrFlag = VOS_FALSE;
#else
    f_stEfUstInfo.bEfSmsrFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMSR);
#endif

    f_stEfUstInfo.bEfSmspFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMSP);

    f_stEfUstInfo.bMoSmsCtrlFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_MOSMS_CONTROL);

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsPpDownlodSupportFlg)
    {
        f_stEfUstInfo.bSmsPpDataFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_DATA_DL_SMSPP);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

}

/***********************************************************************
函 数 名  : MN_MSG_MoFeatureAvailable
功能描述  : 获取MO功能可用标志
输入参数  : VOS_VOID
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR - MO功能可用
            其他            - MO功能不可用
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年4月13日
   作    者   : f62575
   修改内容   : 新生成函数
 2.日    期   : 2010年10月29日
   作    者   : lijun 00171473
   修改内容   : DTS2010102300072, 关闭E5的短信功能

  3.日    期   : 2011年2月26日
    作    者   : 傅映君/f62575
    修改内容   : C31版本支持SMS功能后打开短信发送功能
  4.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加关闭短信功能定制

************************************************************************/
VOS_UINT32 MN_MSG_MoFeatureAvailable(VOS_VOID)
{
    VOS_UINT8                           ucActFlg;

    MN_MSG_GetCloseSMSFeature(&ucActFlg);

    /* 关闭短信功能 */
    if (MN_MSG_NVIM_ITEM_ACTIVE == ucActFlg)
    {
        return MN_ERR_CLASS_SMS_FEATURE_INAVAILABLE;
    }

    if (VOS_TRUE == gstMmaValue.stEfustServiceCfg.ucForbidSndMsg)
    {
        if ((VOS_TRUE != f_stEfUstInfo.bEfSmsFlag)
         && (VOS_TRUE != f_stEfUstInfo.bEfSmspFlag))
        {
            return MN_ERR_CLASS_SMS_FEATURE_INAVAILABLE;
        }
    }

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
函 数 名  : MN_MSG_UpdateSmssInfo
功能描述  : 更新内存中保留的EFSMSS文件存在的标志以及文件的内容
输入参数  : bEfSmssState:文件存在的标志
            pstSmssInfo:EFSMSS文件的内容
输出参数  : 无
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_UpdateSmssInfo(
    VOS_BOOL                            bEfSmssState,
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo,
    VOS_UINT32                          ulFileLen
)
{
    f_stMsgEfSmssInfo.bEfSmssState = bEfSmssState;
    f_stMsgEfSmssInfo.ulFileLen = ulFileLen;
    PS_MEM_CPY(&f_stMsgEfSmssInfo.stEfSmssInfo,pstSmssInfo,sizeof(f_stMsgEfSmssInfo.stEfSmssInfo));
}

/***********************************************************************
函 数 名  : MN_MSG_GetTpMR
功能描述  : 获取当前EFSMSS文件中的TP-MR的值
输入参数  : 无
输出参数  : pucTpMr:当前TP-MR的值,获取USIM,NVIM都失败后,从内存中取
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetTpMR(
    VOS_UINT8                           *pucTpMr
)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        *pucTpMr = stSmssInfo.ucLastUsedTpMr;
    }
    else
    {
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
        *pucTpMr = f_ucMsgInterTpMr;
        f_ucMsgInterTpMr++;
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
    }
}

/***********************************************************************
函 数 名  : MN_MSG_AddTpMR
功能描述  : 更新当前EFSMSS文件中的TP-MR的值
输入参数  : 无
输出参数  : 无
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_AddTpMR(VOS_VOID)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        /*设置TP-MR的值并存入USIM或NVIM中*/
        stSmssInfo.ucLastUsedTpMr++;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }
}

/***********************************************************************
函 数 名  : MN_MSG_ReadSmssInfo
功能描述  : 获取保存在USIM或NVIM中的SMSS的内容,优先获取保存在USIM的EFSMSS文件的内容
输入参数  : 无
输出参数  : pstSmssInfo:获取EFSMSS的内容
返 回 值  : VOS_OK:获取成功
            VOS_ERR:获取失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
************************************************************************/
VOS_UINT32  MN_MSG_ReadSmssInfo(
    MN_MSG_SMSS_INFO_STRU               *pstSmssInfo
)
{
    VOS_UINT32                          ulRet;
    TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU   stSmssContent;

    MN_NORM_LOG1("MN_MSG_ReadSmssInfo: EF SMSS is available in SIM ", (VOS_INT32)f_stMsgEfSmssInfo.bEfSmssState);
    PS_MEM_SET(&stSmssContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSS_PARA_LEN);
    if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
    {
        PS_MEM_CPY(pstSmssInfo,&f_stMsgEfSmssInfo.stEfSmssInfo,sizeof(MN_MSG_SMSS_INFO_STRU));
    }
    else
    {
        ulRet = NV_Read(en_NV_Item_SMS_EFSMSS_Para, &stSmssContent, MN_MSG_EFSMSS_PARA_LEN);
        if (NV_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_ReadSmssInfo:Read NVIM Smss Error");
            return VOS_ERR;
        }
        pstSmssInfo->ucLastUsedTpMr = (stSmssContent.aucSmsEfsmssPara)[0];
        if (MN_MSG_SIM_MEM_FULL_SET == (stSmssContent.aucSmsEfsmssPara)[1])
        {
            pstSmssInfo->enMemCapExcNotFlag = MN_MSG_MEM_FULL_SET;
        }
        else
        {
            pstSmssInfo->enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
        }
    }
    MN_MSG_PrintSmssInfoStru(pstSmssInfo);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MN_MSG_Internal_SendRpt
 功能描述  : 协议栈内部调用此函数发送RP-ACK或RP-ERROR消息到网侧
 输入参数  : bRpAck:是发送RpAck还是RpError
             enRpCause:发送RpError时有效,具体R层的原因值
             enTpCause:发送RpError时有效,具体T层的原因值
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月15日
    作    者   : y00245242
    修改内容   : 在发送RP REPORT之前，获取路由栈标识
  3.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID MN_MSG_Internal_SendRpt(
    VOS_BOOL                            bRpAck   ,                              /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,                              /*used when bRpAck==FALSE*/
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause                               /*TP-Cause*/
)
{
    VOS_UINT8                           ucSendLen;
    VOS_UINT8                           aucSendData[MN_MSG_MAX_LEN];
    VOS_UINT32                          ulRet;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    VOS_UINT8                           ucIdx = 0;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    PS_MEM_SET(aucSendData,0X00,MN_MSG_MAX_LEN);
    if (VOS_TRUE == bRpAck)
    {
        PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
        stRpAck.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ACK;
        stRpAck.bRpUserDataExist = VOS_FALSE;
        MN_MSG_EncodeRpAck(&stRpAck,aucSendData,&ucSendLen);
    }
    else
    {
        PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));
        stRpErr.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ERR;
        stRpErr.ucRpCauseLen = 1;
        stRpErr.stRpCause.bDiagnosticsExist = VOS_FALSE;
        stRpErr.stRpCause.enRpCause = enRpCause;
        stRpErr.bRpUserDataExist = VOS_TRUE;
        stRpErr.ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        /*lint -e961*/
        stRpErr.aucRpUserData[ucIdx++] = MN_MSG_TP_MTI_DELIVER_REPORT;          /*TP-Message type indicator*/
        stRpErr.aucRpUserData[ucIdx++] = enTpCause;                             /*Tp Cause*/
        stRpErr.aucRpUserData[ucIdx++] = 0;
        /*lint +e961*/
        stRpErr.ucRpUserDataLen = ucIdx;
        MN_MSG_EncodeRpErr(&stRpErr,aucSendData,&ucSendLen);

        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_SMS_MT_FAIL,
                        &(enRpCause),
                        sizeof(MN_MSG_RP_CAUSE_ENUM_U8));
    }

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    enMsgSignallingType = MN_MSG_GetMtRouteStackType();
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    ulRet = MN_MSG_SendSmsRpReportReq(aucSendData,ucSendLen, enMsgSignallingType);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpReportReq Send Msg Failed");
    }
}

/*****************************************************************************
 函 数 名  : MSG_RequireDelete
 功能描述  : 判断短信存储状态与删除类型是否匹配，匹配则是待删除消息
                                                 否则不是待删除消息
 输入参数  : enDeleteType    - 删除类型
             ucStatus        - 短消息存储状态
 输出参数  : 无
 返 回 值  : VOS_TRUE         -  短信存储状态与删除类型匹配
             VOS_FALSE        -  短信存储状态与删除类型不匹配

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月19日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_BOOL MSG_RequireDelete(
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_UINT8                           ucStatus
)
{
    VOS_BOOL                            bDeleteFlag = VOS_FALSE;

    if (MN_MSG_DELETE_ALL == enDeleteType)
    {
        bDeleteFlag = VOS_TRUE;
    }
    else if (MN_MSG_DELETE_READ == enDeleteType)
    {
        if (EF_SMS_STATUS_MT_READ == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_UNREAD == enDeleteType)
    {
        if (EF_SMS_STATUS_MT_TO_BE_READ == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_SENT == enDeleteType)
    {
        if (EF_SMS_STATUS_MO_SEND_TO_NT == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_NOT_SENT == enDeleteType)
    {
        if (EF_SMS_STATUS_MO_TO_BE_SEND == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else
    {
        bDeleteFlag = VOS_FALSE;
    }

    return bDeleteFlag;
}


/*****************************************************************************
 函 数 名  : MN_MSG_DeleteMultiSm
 功能描述  : 删除多条短信,NVIM:直接删除NVIM中的短信,USIM,下发删除命令到USIM中
 输入参数  : clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             enMemStore      - 当前短信的存储位置
             enDeleteType    - 删除类型
 输出参数  : pbDeleteAll     - 是否已删除所有短信
             pucDeleteCount  - 本次删除的个数
 返 回 值  : MN_ERR_NO_ERROR - 删除成功或下发命令到USIM成功
             其他             - 删除出错

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_DeleteMultiSm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT32                          *pulDeleteCount
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulSmCapacity;
    VOS_UINT32                          i;
    VOS_UINT8                           ucStatus;
    VOS_BOOL                            bDeleteFlag;
    VOS_UINT32                          ulDeleteCount = 0;
    VOS_UINT8                           ucBeginIndex = f_stMsgSetUsimRec.ucDeleteBegin;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    *pbDeleteAll = VOS_TRUE;
    ulSmCapacity = MN_MSG_GetSmCapacity(enMemStore);
    for (i = ucBeginIndex; i < ulSmCapacity; i++)
    {
        ulRet = MN_MSG_GetStatus(enMemStore,i,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            ulRet = MN_ERR_NO_ERROR;
            continue;
        }

        bDeleteFlag = MSG_RequireDelete(enDeleteType, ucStatus);
        if (VOS_TRUE == bDeleteFlag)
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            aucSmContent[0] = EF_SMS_STATUS_FREE_SPACE;

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = ulFileId;
            stSmaUsimInfo.enDeleteType = enDeleteType;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
            ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
            if (MN_MSG_MEM_STORE_SIM == enMemStore)
            {
                PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
                stWriteUsimInfo.stUsimInfo.clientId = clientId;
                stWriteUsimInfo.stUsimInfo.opId = opId;
                stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
                stWriteUsimInfo.stUsimInfo.enDeleteType = enDeleteType;
                stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)i;
                stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
                stWriteUsimInfo.bCreateNode = VOS_TRUE;
                ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

            }
            else
            {
                ulRet = MN_MSG_WriteSmsFile(enMemStore,&i,VOS_NULL_PTR,aucSmContent);
            }
#endif
            ulDeleteCount++;
            if (MN_ERR_NO_ERROR != ulRet)
            {
                break;
            }
            if ((MN_MSG_MEM_STORE_SIM == enMemStore)
             && (MN_MSG_MAX_DELETE_REC_NUM == ulDeleteCount))
            {
                break;
            }
            bDeleteFlag = VOS_FALSE;
        }
    }

    if (0 == ulDeleteCount)
    {
        *pbDeleteAll = VOS_TRUE;
        *pulDeleteCount = 0;
        return MN_ERR_NO_ERROR;
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*表明已经向APP上报删除结果*/
        f_stMsgSetUsimRec.bDeleteReportFlag = VOS_TRUE;
        f_stMsgSetUsimRec.ucDeleteBegin = 0;
        return ulRet;
    }

    *pulDeleteCount = ulDeleteCount;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE, (VOS_UINT8)ulDeleteCount);

        /*判断是否已经删除完成*/
        if (i < ulSmCapacity)
        {
            /*未能全部删除,更新删除中相关信息,表明未能向APP上报删除结果*/
            *pbDeleteAll = VOS_FALSE;
        }

        /*表明未能向APP上报删除结果*/
        f_stMsgSetUsimRec.ucDeleteBegin = (VOS_UINT8)(i + 1);
        f_stMsgSetUsimRec.bDeleteReportFlag = VOS_FALSE;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_DeleteMultiStaRpt
 功能描述  : 删除多条短信状态报告,NVIM:直接删除NVIM中的短信状态报告,USIM,下发删除命令到USIM中
 输入参数  : clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             enMemStore      - 当前短信的存储位置
 输出参数  : pbDeleteAll     - 是否已删除所有短信状态报告
             pucDeleteCount  - 本次删除的个数
 返 回 值  : MN_ERR_NO_ERROR - 删除成功或下发命令到USIM成功
             其他             - 删除出错

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_DeleteMultiStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT8                           *pucDeleteCount
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulSmsrCapacity;
    VOS_UINT32                          i;
    VOS_UINT8                           ucDeleteCount = 0;
    VOS_UINT8                           ucBeginIndex = f_stMsgSetUsimRec.ucDeleteStaRptBegin;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    ulSmsrCapacity = MN_MSG_GetSmsrCapacity(enMemStore);
    PS_MEM_SET(aucSmsrContent,0X00,MN_MSG_EFSMSR_LEN);

    for (i = ucBeginIndex; i < ulSmsrCapacity; i++)
    {
        ulRet = MN_MSG_ReadSmsrInfo(enMemStore, i, aucSmsrContent);
        if (EF_SMS_STATUS_REPORT_EMPTY != aucSmsrContent[0])
        {
            aucSmsrContent[0] = EF_SMS_STATUS_REPORT_EMPTY;
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_ALL;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE_STARPT;
            ulRet = MN_MSG_WriteSmsrFile(enMemStore,&stSmaUsimInfo,aucSmsrContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                break;
            }
            ucDeleteCount++;
            if ((MN_MSG_MEM_STORE_SIM == enMemStore)
             && (MN_MSG_MAX_DELETE_REC_NUM == ucDeleteCount))
            {
                break;
            }
        }
    }
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT, ucDeleteCount);
    }
    *pucDeleteCount = ucDeleteCount;
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*表明已经向APP上报删除结果*/
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_TRUE;
        f_stMsgSetUsimRec.ucDeleteStaRptBegin = 0;
        return ulRet;
    }
    /*判断是否已经删除完成*/
    if (i >= ulSmsrCapacity)
    {
        *pbDeleteAll = VOS_TRUE;
        if ((MN_MSG_MEM_STORE_SIM == enMemStore)
         && (ucDeleteCount > 0))
        {
            /*表明未能向APP上报删除结果*/
            f_stMsgSetUsimRec.ucDeleteStaRptBegin = (VOS_UINT8)(i + 1);
            f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_FALSE;
        }
        else
        {
            /*表明已经向APP上报删除结果*/
            f_stMsgSetUsimRec.ucDeleteStaRptBegin = 0;
            f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_TRUE;
        }
    }
    else
    {
        /*未能全部删除,更新删除中相关信息,表明未能向APP上报删除结果*/
        *pbDeleteAll = VOS_FALSE;
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_FALSE;
    }
    return MN_ERR_NO_ERROR;
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateSmsRecNumInfo
功能描述  : 收到USIM发送过来的EFSMS的文件内容后,更新内存中EFSMS的记录数和文件存在标志
输入参数  : bEfSmsState:文件存在标志
            ucEFSmNum:USIM中文件记录数,
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateSmsInfo(
    VOS_BOOL                            bEfSmsState,
    VOS_UINT8                           ucEFSmNum
)
{
    f_stMsgEfSmsInfo.bEfSmsState = bEfSmsState;
    f_stMsgEfSmsInfo.ucSmsRealRecNum = ucEFSmNum;
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateUsimStateInfo
功能描述  : 更新当前USIM卡及其USIM卡上电的状态
输入参数  : enPowerState:USIM卡的上电状态
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateUsimStateInfo(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState
)
{
    f_stMsgUsimStatusInfo.enPowerState = enPowerState;
}


/***********************************************************************
函 数 名  : MN_MSG_StartMo
功能描述  : 发送完一条短信后,如果当前有消息缓存,调用此函数继续发送消息
输入参数  : 无
输出参数  : penSendDomain:当前发送短信的发送域
返 回 值  : VOS_OK:发送缓存消息成功
            VOS_ERR:发送缓存消息失败

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2010年6月30日
   作    者   : 傅映君
   修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
 3.日    期   : 2011年6月24日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011062201273 MO SMS CONTROL
 4.日    期   : 2011年10月11日
   作    者   : k66584
   修改内容   : DTS2011093003995,缓存短信发送前重新构建发送实体
 2.日    期   : 2011年12月25日
   作    者   : w00167002
   修改内容   : DTS2011102003157:软关机时Shell口异常打印;
                短消息的无效索引指示由0xff更改为0xffffffff;
                删除当前索引为0XFF就返回的判断。
************************************************************************/
VOS_UINT32 MN_MSG_StartMo(
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penSendDomain
)
{
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;
    VOS_UINT32                          ulRet;
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;

    PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    /*1.获取最早缓存的消息*/
    PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
    ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);


    /*1.1若缓存消息类型为SMMA消息，则判断当前是否需要发送*/
    if ((MN_MSG_NO_AVAILABLE_SMS_REC != ulStoreIndex)
     && (MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType))
    {

        /*获取当前UE的存储状态*/
        ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
        if (VOS_ERR == ulRet)
        {
            MN_WARN_LOG("MN_MSG_StartMo: Fail to read SMSS information.");
            return ulRet;
        }
        MN_NORM_LOG1("MN_MSG_StartMo: enMemCapExcNotFlag is ", stSmssInfo.enMemCapExcNotFlag);

        /*若当前UE的存储状态为存储设备空闲，直接返回*/
        if (MN_MSG_MEM_FULL_SET != stSmssInfo.enMemCapExcNotFlag)
        {
            MN_MSG_FreeStoreMsg(ulStoreIndex);
            PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
            ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
        }
        else
        {
            /*若当前UE存储设备状态不能接收短信，直接返回*/
            ulRet = MN_MSG_CheckMemAvailable();
            if (VOS_OK != ulRet)
            {
                MN_MSG_FreeStoreMsg(ulStoreIndex);
                PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
                ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
            }
        }
    }

    if ((MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
     || (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP == stStoreMsg.stMoInfo.enSmaMoState)
     || (MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP == stStoreMsg.stMoInfo.enSmaMoState))
    {

        MN_NORM_LOG("MN_MSG_StartMo: no buffer to send.");
        return VOS_ERR;
    }

    /*2. 判断当前是否存在可用发送域*/
    MN_MSG_GetCurSendDomain(stStoreMsg.stMoInfo.enHopeSendDomain,&enSendDomain);
    *penSendDomain = enSendDomain;
    if (MN_MSG_SEND_DOMAIN_NO == enSendDomain)
    {
        MN_WARN_LOG("MN_MSG_StartMo:No Avail Send Domain");
        return VOS_ERR;
    }

    /*3.创建发送短信时相关参数*/
    /* 更新当前实际发送域 */
    enHopeSendDomain = stStoreMsg.stMoInfo.enHopeSendDomain;
    stStoreMsg.stMoInfo.enHopeSendDomain = MN_MSG_GetRealPrefSendDomain(enSendDomain,enHopeSendDomain);
    MN_MSG_CreateMoInfo(&stStoreMsg.stMoInfo);
    MN_MSG_SendMsgToSms(&stStoreMsg.stMoInfo);
    MN_MSG_FreeStoreMsg(ulStoreIndex);

    /*此处解决STK覆盖SMMA消息问题；*/
    if (MN_MSG_MO_TYPE_BUFFER_STK == stStoreMsg.stMoInfo.enSmsMoType)
    {
        MN_MSG_StartMemNotification();
    }

    return VOS_OK;
}


/***********************************************************************
函 数 名  : MN_MSG_StartMemNotification
功能描述  : 根据当前存储器的情况决定是否要向网侧发起内存可用通知
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_StartMemNotification(VOS_VOID)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    MN_INFO_LOG("MN_MSG_StartMemNotification: into function.");
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    /*获取当前UE的存储状态*/
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_ERR == ulRet)
    {
        MN_WARN_LOG("MN_MSG_StartMemNotification: Fail to read SMSS information.");
        return;
    }
    MN_NORM_LOG1("MN_MSG_StartMemNotification: enMemCapExcNotFlag is ", stSmssInfo.enMemCapExcNotFlag);

    /*若当前UE的存储状态为存储设备空闲，直接返回*/
    if (MN_MSG_MEM_FULL_SET != stSmssInfo.enMemCapExcNotFlag)
    {
        return;
    }

    ulRet = MN_MSG_CheckMemAvailable();
    if (VOS_OK == ulRet)
    {
        MN_MSG_SendMemAvail();
    }

}


/***********************************************************************
函 数 名  : MN_MSG_SendSmma
功能描述  : 发送SMMA消息到网侧
输入参数  : clientId       - 发起该请求的Client的ID
            opId           - Operation ID, 标识本次操作
            bReportFlag    - 上报标志
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年7月3日
   作    者   : y00245242
   修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈
 3.日    期   : 2014年7月29日
   作    者   : w00242748
   修改内容   : DTS2014052806022:卡文件6F43指示SIM卡内存满，但实际开机后，
                发现SIM卡内存还有余量，所以这时需要通知网络当前能接受短信，
                但SVLTE主modem不应通知(主modem PS only，不支持发送短信)。
************************************************************************/
VOS_UINT32  MN_MSG_SendSmma(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bReportFlag,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealDomain;
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS_PREFERRED,&enRealDomain);
    if (MN_MSG_SEND_DOMAIN_NO == enRealDomain)
    {       
        MN_WARN_LOG("MN_MSG_SendSmma: enRealDomain IS MN_MSG_SEND_DOMAIN_NO.");
        
        ulRet = MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
        return ulRet;
    }

    if ( (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
      && (MN_MSG_SEND_DOMAIN_PS == enRealDomain) )
    {
        ulRet = MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
        return ulRet;
    }

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
    ulRet = MN_MSG_SendSmsSmmaReq(enRealDomain, enMsgSignallingType);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */
    if (VOS_ERR == ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_INTERNAL;
        return ulRet;
    }

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    stMoEntity.clientId = clientId;
    stMoEntity.opId = opId;
    stMoEntity.enSendDomain= enRealDomain;
    stMoEntity.enSaveArea = MN_MSG_MEM_STORE_NONE;
    stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_SMMA;
    stMoEntity.enTpduType = MN_MSG_TPDU_SUBMIT;
    stMoEntity.bReportFlag = bReportFlag;
    stMoEntity.ucRpDataLen = 0;
    stMoEntity.enSmaMoState = MN_MSG_MO_STATE_WAIT_REPORT_IND;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-8-29, begin */
    stMoEntity.enMsgSignallingType = enMsgSignallingType;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-8-29, end */
    MN_MSG_CreateMoInfo(&stMoEntity);
    return ulRet;
}

/***********************************************************************
函 数 名  : MN_MSG_SendMemAvail
功能描述  : 向网侧发起内存可用通知
输入参数  : 无
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2010年6月30日
   作    者   : 傅映君
   修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
 3.日    期   : 2011年12月25日
    作    者   : w00167002
    修改内容   : DTS2011102003157:软关机时Shell口异常打印;短消息的无效索引指示
                  由0xff更改为0xffffffff。
 4.日    期   : 2013年7月15日
    作    者   : y00245242
    修改内容   : 获取消息路由标识，确定SMMA路由
 5.日    期   : 2013年09月24日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目
 6.日    期   : 2015年4月13日
   作    者   : s00217060
   修改内容   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND中的client id不对，重拨缓存未清除
************************************************************************/
VOS_VOID MN_MSG_SendMemAvail(VOS_VOID)
{
    MN_MSG_MO_STATE_ENUM_U8             enMoState;
    VOS_UINT32                          ulSaveIndex;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealDomain;
    /* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
    /* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

    PS_MEM_SET(&stMoEntity, 0x00, sizeof(stMoEntity));

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS_PREFERRED,&enRealDomain);
    enMoState = MN_MSG_GetMoState();
    if ((MN_MSG_SEND_DOMAIN_NO == enRealDomain)
     || (MN_MSG_MO_STATE_WAIT_REPORT_IND == enMoState))
    {

        ulSaveIndex = MN_MSG_GetStoreMsgIndex();

        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSaveIndex)
        {

            MN_WARN_LOG("MN_MSG_SendMemAvail,Type:From Mem, No Enough Buffer");
            return;
        }
        /*将构造好的消息存入缓存*/
        stMoEntity.bReportFlag = VOS_FALSE;
        stMoEntity.enSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        stMoEntity.enSaveArea = MN_MSG_MEM_STORE_MAX;
        stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_SMMA;
        stMoEntity.enTpduType = MN_MSG_TPDU_SUBMIT;
        stMoEntity.ucRpDataLen = 0;
        PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
        MN_MSG_SaveStoreMsg(ulSaveIndex,&stMoEntity,aucSmContent);
    }
    else
    {
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
        /* Here send SMMA request to SPM module */
#if (FEATURE_IMS == FEATURE_ON)
        /* 如果IMS宏打开需要到SPM模块做域选择，否则直接走NAS信令 */
        TAF_MSG_SendSpmSmmaInd();
#else
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        (VOS_VOID)MN_MSG_SendSmma(stMoEntity.clientId, stMoEntity.opId, VOS_FALSE, TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */
#endif
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */
    }
}

/***********************************************************************
函 数 名  : MN_MSG_IsUsimFileExist
功能描述  : 获取USIM中该文件是否存在
输入参数  : usEfId:USIM中的文件ID
输出参数  : NONE
返 回 值  : VOS_TRUE:该文件存在
            VOS_FALSE:该文件不存在
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsUsimFileExist(
    VOS_UINT16                          usEfId
)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            if (VOS_TRUE == f_stMsgEfSmsInfo.bEfSmsState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
            if (VOS_TRUE == f_stMsgEfSmspInfo.bEfSmspState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            if (VOS_TRUE == f_stMsgEfSmsrInfo.bEfSmsrState)
            {
                return VOS_TRUE;
            }
            break;
        default:
            MN_INFO_LOG("MN_MSG_IsUsimFileExist:No EF File ID");
            break;
    }

    return VOS_FALSE;
}

/***********************************************************************
函 数 名  : MN_MSG_ReadUstInfo
功能描述  : 获取USIM保存在内存短信服务表
输入参数  : 无
输出参数  : pstEfUstInfo:USIM保留在内存的(U)SIM Service Table的内容
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID   MN_MSG_ReadUstInfo(
    MN_MSG_USIM_EFUST_INFO_STRU         *pstEfUstInfo
)
{
    PS_MEM_CPY(pstEfUstInfo,&f_stEfUstInfo,sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
    MN_MSG_PrintEfUstInfo();
}

/***********************************************************************
函 数 名  : MN_MSG_ReadSmsInfo
功能描述  : 从内存中读取存在USIM的短信或读取NVIM中的短信
输入参数  : enMemStore:短信的存储位置,NVIM或USIM
            ulIndex:需要读取短信的索引号
输出参数  : pucSmsContent:该条短信的内容
返 回 值  : MN_ERR_NO_ERROR:函数执行成功
            其他:函数执行成功
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2010年01月27日
   作    者   : w00166186
   修改内容   : 增加对FLASH读写的处理
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmContent
)
{
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)&& (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    VOS_UINT32                          ulRet;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmsInfo: USIMM_USIM_EFSMS_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_FREE_SPACE == (f_stMsgEfSmsInfo.aucEfSmsList[ulIndex*MN_MSG_EFSMS_LEN] & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        PS_MEM_CPY(pucSmContent, (f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex*MN_MSG_EFSMS_LEN)), MN_MSG_EFSMS_LEN);
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex >= f_usMsgNvimSmsCurReNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_FREE_SPACE == (f_aucMsgNvimSmStatus[ulIndex] & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
        ulRet = MN_MSG_ReadMsgInFlashByIndex(ulIndex,pucSmContent);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_ERR_LOG("MN_MSG_ReadSmsInfo:Write FLASH Error");
            PS_MEM_SET(f_aucMsgNvimSmStatus, 0x00, sizeof(f_aucMsgNvimSmStatus));
            MN_MNTN_RecordSmsMeError(MNTN_ME_OPERATION_READ, ulRet);
            return ulRet;
        }
#else
        if(NV_OK != NV_Read(en_NV_Item_SMS_Content,pucSmContent, MN_MSG_EFSMS_LEN))
        {
           MN_ERR_LOG("MN_MSG_ReadSmsInfo:Read NVIM Sms Error");
           return MN_ERR_CLASS_SMS_NVIM;
        }
#endif

    }
#endif
    else
    {
       MN_NORM_LOG("MN_MSG_ReadSmsInfo: Memory type is not support.");
       return MN_ERR_INVALIDPARM;
    }
    return MN_ERR_NO_ERROR;
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateEachMemSmInfo
功能描述  : 更新USIM保存在内存中的短信内容
输入参数  : ucIndex:更新记录的index
            pucEFContent:EFSMS的文件内容
            ucEFSmsLen:EFSMS文件的长度
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2014年07月07日
   作    者   : z00234330
   修改内容   : coverity清理
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmInfo(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsLen
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucEfSmsStatus;

    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));

    if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
    {
        return;
    }

    PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex * ucEFSmsLen)),
               pucEFContent,
               ucEFSmsLen);

    ulRet = MN_MSG_ParseEFSmContent(pucEFContent, &stScAddr, &stRawData, &ucEfSmsStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        *(f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex * ucEFSmsLen)) = EF_SMS_STATUS_FREE_SPACE;
    }

    return;
}

/***********************************************************************
函 数 名  : MN_MSG_ReadSmsrInfo
功能描述  : 从内存中读取存在USIM的短信状态报告或读取NVIM中的短信状态报告
输入参数  : enMemStore:短信的存储位置,NVIM或USIM
            ulIndex:需要读取短信状态报告的索引号
输出参数  : pucSmsrContent:该条短信状态报告的内容
返 回 值  : MN_ERR_NO_ERROR:函数执行成功
            其他:执行失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsrInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsrContent
)
{
    VOS_UINT32                          ulLen = MN_MSG_EFSMSR_LEN;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmsrInfo: USIMM_USIM_EFSMSR_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_REPORT_EMPTY == (f_stMsgEfSmsrInfo.aucEfSmsrList[ulIndex*MN_MSG_EFSMSR_LEN]))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        PS_MEM_CPY(pucSmsrContent, (f_stMsgEfSmsrInfo.aucEfSmsrList+ (ulIndex*MN_MSG_EFSMSR_LEN)), MN_MSG_EFSMSR_LEN);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (ulIndex >= MN_MSG_MAX_NVIM_SMSR_REC_NUM)
            {
                return MN_ERR_CLASS_SMS_INVALID_REC;
            }
            if(NV_OK != NV_Read(en_NV_Item_SMS_Status,pucSmsrContent, ulLen))
            {
               MN_ERR_LOG("MN_MSG_ReadSmsrInfo:Read NVIM Smsr Error");
               return MN_ERR_CLASS_SMS_NVIM;
            }

            if (EF_SMS_STATUS_REPORT_EMPTY == *pucSmsrContent)
            {
                return MN_ERR_CLASS_SMS_EMPTY_REC;
            }
        }

        return MN_ERR_NO_ERROR;

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else
    {
        MN_NORM_LOG("MN_MSG_ReadSmsrInfo: Memory type is not support.");
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;

}

/***********************************************************************
函 数 名  : MN_MSG_UpdateEachMemSmsrInfo
功能描述  : 更新USIM保存在内存中的短信状态报告内容
输入参数  : ucIndex:更新记录的index
            pucEFContent:EFSMSR的文件内容
            ucEFSmsLen:EFSMSR文件的长度
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmsrInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsrLen
)
{
    if (ucIndex >= f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
    {
        return;
    }
    PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (ucIndex * ucEFSmsrLen)),
               pucEFContent,
               ucEFSmsrLen);
    return;
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateTotalSmsrInfo
功能描述  : 收到USIM发送过来的EFSMSR的文件内容后,更新内存中EFSMSR的内容
输入参数  : bEfSmspState:EFSMSR的文件是否存在
            ucSmsrRec:EFSMSR的文件个数
            ucEfLen:EFSMSR文件的长度
            pucSmspContent:EFSMSR文件的内容
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmsrInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucSmsrRec,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           *pucSmspContent
)
{
    VOS_UINT32                          i;

    f_stMsgEfSmsrInfo.bEfSmsrState = bEfSmspState;
    f_stMsgEfSmsrInfo.ucSmsrRealRecNum = ucSmsrRec;
    for (i = 0; i < ucSmsrRec; i++)
    {
        PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (MN_MSG_EFSMSR_LEN * i)),
                   (pucSmspContent + (usEfLen * i)),
                   MN_MSG_EFSMSR_LEN);
    }
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateSmspInfo
功能描述  : 更新保留在内存中的USIM的短信参数
输入参数  : ucIndex:需要更新的短信参数索引
            bUsed:该短信参数是否有效
            pstScvParm:更新的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_UpdateEachMemSmspInfo(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bUsed,
    const MN_MSG_SRV_PARAM_STRU         *pstScvParm
)
{

    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return;
    }
    f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].bUsed = bUsed;
    PS_MEM_CPY(&f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].stParm,
               pstScvParm,
               sizeof(MN_MSG_SRV_PARAM_STRU));

    return;
}

/***********************************************************************
函 数 名  : MN_MSG_ReadSmspInfo
功能描述  : 读出索引为ulIndex的短信参数的内容
输入参数  : enMemStore:短信参数的存储器,NVIM或USIM
            ulIndex:短信参数的索引
输出参数  : pstSmspPara:读出短信参数的内容
返 回 值  : MN_ERR_NO_ERROR:读取成功
            其他:读取失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年10月17日
   作    者   : f62575
   修改内容   : 新生成函数
 3.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
 4.日    期   : 2013年08月23日
   作    者   : f62575
   修改内容   : DTS2011051605439，短信模块短信重新初始化会TP-VP和TP-DCS
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmspInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    VOS_BOOL                            bSrvParmPresent = VOS_FALSE;
    VOS_UINT32                          ulRet;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stEfsmsp;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }

    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    PS_MEM_SET(&stEfsmsp,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            /* Modified by f62575 for AT Project，2011-10-17,  Begin*/
            MN_WARN_LOG1("MN_MSG_ReadSmspInfo: ErrCode ", (VOS_INT32)ulRet);
            if (MN_ERR_CLASS_SMS_UPDATE_USIM != ulRet)
            {
                return ulRet;
            }

            MN_MSG_GetUsimPowerState(&enPowerState);
            if (enPowerState <= MN_MSG_USIM_POWER_WAIT_EFSMSP)
            {
                return MN_ERR_CLASS_SMS_UPDATE_USIM;
            }
            /* Modified by f62575 for AT Project，2011-10-17,  End*/
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmspInfo: USIMM_USIM_EFSMSP_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (VOS_TRUE != f_stMsgEfSmspInfo.astEachEfSmspInfo[ulIndex].bUsed)
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
        PS_MEM_CPY(pstSrvParam,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[ulIndex].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));
    }
    else
    {
        if (NV_OK != NV_Read(en_NV_Item_SMS_EFSMSP_Para, &stEfsmsp, MN_MSG_EFSMSP_PARA_LEN))
        {
            MN_ERR_LOG("MN_MSG_ReadSmspInfo:Read NVIM Smsp Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
        PS_MEM_CPY(aucSmspContent, &stEfsmsp, MN_MSG_MAX_EF_LEN);

        PS_MEM_CPY(pstSrvParam,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[0].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));

        MSG_ParseSmsp(MN_MSG_MAX_EF_LEN,aucSmspContent,&bSrvParmPresent,pstSrvParam);
        if (VOS_FALSE == bSrvParmPresent)
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
    }
    return MN_ERR_NO_ERROR;
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateTotalSmspInfo
功能描述  : 收到USIM发送过来的EFSMSP的文件内容后,更新内存中EFSMSP的内容
输入参数  : bEfSmspState:EFSMSP文件存在标志
            ucNumofSmsp:EFSMSP文件的个数
            ucEfLen:EFSMSP文件的长度
            pucSmspContent:EFSMSP文件的内容
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年08月23日
   作    者   : f62575
   修改内容   : DTS2011051605439，短信模块短信重新初始化会TP-VP和TP-DCS
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmspInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucNumofSmsp,
    VOS_UINT8                           ucEfLen,
    const VOS_UINT8                     *pucSmspContent
)
{
    VOS_UINT32                          i;
    MN_MSG_SRV_PARAM_STRU                stSrvParm;
    VOS_BOOL                            bValid = VOS_FALSE;

    PS_MEM_SET(&stSrvParm, 0, sizeof(MN_MSG_SRV_PARAM_STRU));

    MN_INFO_LOG("MN_MSG_UpdateTotalSmspInfo: step into function.");
    f_stMsgEfSmspInfo.bEfSmspState = bEfSmspState;
    MN_NORM_LOG1("MN_MSG_UpdateTotalSmspInfo: ucNumofSmsp", ucNumofSmsp);
    if (ucNumofSmsp < MN_MSG_MAX_USIM_EFSMSP_NUM)
    {
        f_stMsgEfSmspInfo.ucSmspRealRecNum = ucNumofSmsp;
    }
    else
    {
        f_stMsgEfSmspInfo.ucSmspRealRecNum = MN_MSG_MAX_USIM_EFSMSP_NUM;
    }

    for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
    {
        PS_MEM_CPY(&stSrvParm,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                   sizeof(stSrvParm));

        MSG_ParseSmsp(ucEfLen,
                      (pucSmspContent +  (i * ucEfLen)),
                      &bValid,
                      &stSrvParm);
        MN_NORM_LOG1("MN_MSG_UpdateTotalSmspInfo: bValid", (VOS_INT32)bValid);
        if (VOS_TRUE == bValid)
        {
            f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed = VOS_TRUE;
            PS_MEM_CPY(&f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                       &stSrvParm,
                       sizeof(MN_MSG_SRV_PARAM_STRU));
        }
    }
}

/***********************************************************************
函 数 名  : MN_MSG_GetSmStorageList
功能描述  : 获取当前USIM或NVIM中短信的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pusTotalRec:当前存储器的总容量
            psUsedRec:当前存储器的已用空间
            pulEachStatusRec:每种状态的短信的记录数
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetSmStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    VOS_UINT32                          *pulEachStatusRec
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucStatus;

    *pulTotalRec            = 0;
    *pulUsedRec             = 0;
    *pulEachStatusRec       = 0;
    *(pulEachStatusRec + 1) = 0;
    *(pulEachStatusRec + 2) = 0;
    *(pulEachStatusRec + 3) = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmsInfo.ucSmsRealRecNum;
        for (i = 0; i < f_stMsgEfSmsInfo.ucSmsRealRecNum; i++)
        {
            ucStatus = *(f_stMsgEfSmsInfo.aucEfSmsList + (i * MN_MSG_EFSMS_LEN));
            if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & EF_SMS_STATUS_MO_TO_BE_SEND))
            {
                (*pulUsedRec)++;
                (*pulEachStatusRec)++;
            }
            else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & EF_SMS_STATUS_MO_SEND_TO_NT))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 1))++;
            }
            else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & EF_SMS_STATUS_MT_TO_BE_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 2))++;
            }
            else if (EF_SMS_STATUS_MT_READ == (ucStatus & EF_SMS_STATUS_MT_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 3))++;
            }
            else
            {
            }
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        *pulTotalRec = f_usMsgNvimSmsCurReNum;
        for (i = 0; i < f_usMsgNvimSmsCurReNum; i++)
        {
            ucStatus = f_aucMsgNvimSmStatus[i];
            if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & EF_SMS_STATUS_MO_TO_BE_SEND))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec))++;
            }
            else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & EF_SMS_STATUS_MO_SEND_TO_NT))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 1))++;
            }
            else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & EF_SMS_STATUS_MT_TO_BE_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 2))++;
            }
            else if (EF_SMS_STATUS_MT_READ == (ucStatus & EF_SMS_STATUS_MT_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 3))++;
            }
            else
            {
            }
        }
    }
#endif
    else
    {
       MN_WARN_LOG("MN_MSG_GetSmStorageList: Memory type is not support.");
    }
}

/***********************************************************************
函 数 名  : MN_MSG_GetSmsrStorageList
功能描述  : 获取当前USIM或NVIM中短信状态报告的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pusTotalRec:当前存储器的总容量
            psUsedRec:当前存储器的已用空间
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
************************************************************************/
VOS_VOID MN_MSG_GetSmsrStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulLen = MN_MSG_EFSMSR_LEN;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    *pulUsedRec = 0;
    *pulTotalRec = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmsrInfo.ucSmsrRealRecNum;
        for (i = 0; i < f_stMsgEfSmsrInfo.ucSmsrRealRecNum; i++)
        {
            if (EF_SMS_STATUS_REPORT_EMPTY != f_stMsgEfSmsrInfo.aucEfSmsrList[i*MN_MSG_EFSMSR_LEN])
            {
                (*pulUsedRec)++;
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            *pulTotalRec = MN_MSG_MAX_NVIM_SMSR_REC_NUM;
            for (i = 0; i < MN_MSG_MAX_NVIM_SMSR_REC_NUM; i++)
            {
                PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
                if (NV_OK == NV_Read(en_NV_Item_SMS_Status, aucSmsrContent, ulLen))
                {
                    MN_ERR_LOG("MN_MSG_GetSmsrStorageList:Read NVIM Smsr Error");
                    if (EF_SMS_STATUS_REPORT_EMPTY != aucSmsrContent[0])
                    {
                        (*pulUsedRec)++;
                    }
                }
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    else
    {
       MN_WARN_LOG("MN_MSG_GetSmsrStorageList: Memory type is not support.");
    }

}

/***********************************************************************
函 数 名  : MN_MSG_GetSmspStorageList
功能描述  : 获取当前USIM或NVIM中短信参数的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pulTotalRec:当前存储器的总容量
            pulUsedRec:当前存储器的已用空间
            pstSrvParam:短信参数列表
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
 3.日    期   : 2013年08月23日
   作    者   : f62575
   修改内容   : DTS2011051605439，短信模块短信重新初始化会TP-VP和TP-DCS
************************************************************************/
VOS_VOID MN_MSG_GetSmspStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    MN_MSG_SRV_PARAM_STRU               stSrvParm;
    VOS_BOOL                            bValid = VOS_FALSE;
    MN_MSG_SRV_PARAM_STRU               *pTmpSrvParm;
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stEfsmsp;

    PS_MEM_SET(&stEfsmsp,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);
    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0XFF,MN_MSG_MAX_EF_LEN);
    *pulUsedRec = 0;
    pstSrvParam->ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmspInfo.ucSmspRealRecNum;
        pTmpSrvParm = pstSrvParam;
        for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
        {
            if (VOS_TRUE == f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed)
            {
                (*pulUsedRec)++;
                PS_MEM_CPY(pTmpSrvParm,
                           &f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                           sizeof(MN_MSG_SRV_PARAM_STRU));
            }
            else
            {
                pTmpSrvParm->ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
            }
            pTmpSrvParm++;
        }
    }
    else
    {
        PS_MEM_CPY(&stSrvParm,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[0].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));

        *pulTotalRec  = 1;
        if (NV_OK == NV_Read(en_NV_Item_SMS_EFSMSP_Para,&stEfsmsp, MN_MSG_EFSMSP_PARA_LEN))
        {
            PS_MEM_CPY(aucSmspContent, &stEfsmsp, MN_MSG_MAX_EF_LEN);
            /*存在NVIM中无Alpha Identifier,第一个字节表示Parameter Indicators*/
            MSG_ParseSmsp(MN_MSG_MIN_SRV_PARM_LEN,aucSmspContent,&bValid,&stSrvParm);
            if (VOS_TRUE == bValid)
            {
                (*pulUsedRec)++;
                PS_MEM_CPY(pstSrvParam,&stSrvParm,sizeof(stSrvParm));
            }
        }
        else
        {
            MN_ERR_LOG("MN_MSG_GetSmspStorageList:Read NVIM Smsp Error");
        }
    }
}

/***********************************************************************
函 数 名  : MN_MSG_GetStatus
功能描述  : 获取存在USIM或NVIM中的短信状态
输入参数  : enMemStore:需要获取短信状态的存储位置,USIM或NVIM中
            ulIndex:需要获取短信状态的索引号
输出参数  : pucStatus:索引为ulIndex的短信状态
返 回 值  : MN_ERR_NO_ERROR:获取成功
            其他:获取失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年3月21日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011031800199，获取SM消息状态增加调用函数返回值判断
************************************************************************/
VOS_UINT32 MN_MSG_GetStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucStatus
)
{
    VOS_UINT32                          ulPos;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        ulPos = MN_MSG_EFSMS_LEN * ulIndex;
        *pucStatus = f_stMsgEfSmsInfo.aucEfSmsList[ulPos];

        if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
        else
        {
            return MN_ERR_NO_ERROR;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex >= f_usMsgNvimSmsCurReNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        *pucStatus = f_aucMsgNvimSmStatus[ulIndex];
        if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        return MN_ERR_NO_ERROR;
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetStatus: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}


/***********************************************************************
函 数 名  : MN_MSG_GetAvailSmRecIndex
功能描述  : 获取存在USIM或NVIM中的一条空闲的短信索引
输入参数  : enMemStore:需要获取空闲短信索引的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 空闲短信索引号,无空闲短信,则返回MSG_NO_AVAILABLE_REC
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;

    MN_NORM_LOG("MN_MSG_GetAvailSmRecIndex: Step into function.");
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        for (i = 0; i < f_stMsgEfSmsInfo.ucSmsRealRecNum; i++ )
        {
            MN_INFO_LOG2("MN_MSG_GetAvailSmRecIndex: USIM ", (VOS_INT32)i, (f_stMsgEfSmsInfo.aucEfSmsList[i*MN_MSG_EFSMS_LEN] & 0x01));
            if (EF_SMS_STATUS_FREE_SPACE == (f_stMsgEfSmsInfo.aucEfSmsList[i*MN_MSG_EFSMS_LEN] & 0x01))
            {
                ulIndex = i;
                break;
            }
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        for (i = 0; i < f_usMsgNvimSmsCurReNum; i++)
        {
            MN_INFO_LOG2("MN_MSG_GetAvailSmRecIndex: NVIM ", (VOS_INT32)i, (f_aucMsgNvimSmStatus[i] & 0x01));
            if (EF_SMS_STATUS_FREE_SPACE == (f_aucMsgNvimSmStatus[i] & 0x01))
            {
                ulIndex = i;
                break;
            }
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetAvailSmRecIndex: enMemStore is ", enMemStore);
    }
    return ulIndex;
}

/***********************************************************************
函 数 名  : MN_MSG_GetAvailSmsrRecIndex
功能描述  : 获取存在USIM或NVIM中的空闲的短信状态报告索引
输入参数  : enMemStore:需要获取空闲短信状态报告索引的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 空闲短信状态报告索引号,无空闲短信状态报告,则返回MN_MSG_NO_AVAILABLE_SMS_REC
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月1日
   作    者   : 傅映君/f62575
   修改内容   : 问题单号:DTS2011060803050 STATUS REPORT in ME
 3.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulLen;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        for (i = 0; i < f_stMsgEfSmsrInfo.ucSmsrRealRecNum; i++)
        {
            if (EF_SMS_STATUS_REPORT_EMPTY == f_stMsgEfSmsrInfo.aucEfSmsrList[i*MN_MSG_EFSMSR_LEN])
            {
                ulIndex = i;
                break;
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
       if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
       {
           PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
           ulLen = MN_MSG_EFSMSR_LEN;
           for (i = 0; i < MN_MSG_MAX_NVIM_SMSR_REC_NUM; i++)
           {
               if(NV_OK == NV_Read(en_NV_Item_SMS_Status,aucSmsrContent, ulLen))
               {
                   if (EF_SMS_STATUS_REPORT_EMPTY == aucSmsrContent[0])
                   {
                       ulIndex = i;
                       break;
                   }
               }
               else
               {
                   MN_ERR_LOG("MN_MSG_GetAvailSmsrRecIndex:Read NVIM Smsr Error");
               }
           }
       }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else
    {
        MN_WARN_LOG1("MN_MSG_GetAvailSmsrRecIndex: enMemStore is ", enMemStore);
    }
    return ulIndex;

}

/***********************************************************************
函 数 名  : MN_MSG_GetAvailSmspRecIndex
功能描述  : 获取存在USIM中的空闲的短信参数索引
输入参数  : NONE
输出参数  : NONE
返 回 值  : 空闲短信参数索引号,无空闲短信参数,则返回MSG_NO_AVAILABLE_REC
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年01月30日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT8 MN_MSG_GetAvailSmspRecIndex(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex = MN_MSG_NO_AVAILABLE_REC;

    for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
    {
        if (VOS_FALSE == f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed)
        {
            ucIndex = i;
            break;
        }
    }
    return  ucIndex;
}

/***********************************************************************
函 数 名  : MN_MSG_GetReplaceSmsrRecIndex
功能描述  : 获取存在USIM或NVIM中的替换的短信状态报告索引,即寻找最老的一条短信状态报告索引记录
输入参数  : enMemStore:需要获取空闲短信状态报告索引的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 最老的一条短信状态报告索引记录
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年7月1日
   作    者   : 傅映君/f62575
   修改内容   : 问题单号:DTS2011060803050 STATUS REPORT in ME
 3.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
************************************************************************/
VOS_UINT32 MN_MSG_GetReplaceSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{

    VOS_UINT32                          ulSaveIndex;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (0 == f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
        {
            return MN_MSG_NO_AVAILABLE_SMS_REC;
        }

        f_stMsgEfSmsrInfo.ucSmsrCurRecNum = (f_stMsgEfSmsrInfo.ucSmsrCurRecNum + 1) %
                                        (f_stMsgEfSmsrInfo.ucSmsrRealRecNum);
        ulSaveIndex = f_stMsgEfSmsrInfo.ucSmsrCurRecNum;
    }

/*->f62575 PC-LINT error 且协议栈不支持NVIM存储短信 begin*/
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            f_ucMsgNvimSmsrCurReNum = (f_ucMsgNvimSmsrCurReNum + 1) % MN_MSG_MAX_NVIM_SMSR_REC_NUM;
            ulSaveIndex = f_ucMsgNvimSmsrCurReNum;
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    }
/*->f62575 PC-LINT error 且协议栈不支持NVIM存储短信 end */
    else
    {
        MN_WARN_LOG1("MN_MSG_GetReplaceSmsrRecIndex: enMemStore is ", enMemStore);
    }

    return ulSaveIndex;

}

/***********************************************************************
函 数 名  : MN_MSG_GetUsimPowerState
功能描述  : 获取USIM当前的上电状态
输入参数  : 无
输出参数  : penPowerState:获取USIM当前的上电状态
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetUsimPowerState(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     *penPowerState
)
{
    *penPowerState = f_stMsgUsimStatusInfo.enPowerState;
    MN_INFO_LOG1("MN_MSG_GetUsimPowerState: f_stMsgUsimStatusInfo.enPowerState", f_stMsgUsimStatusInfo.enPowerState);
}

/***********************************************************************
函 数 名  : MN_MSG_CheckUsimStatus
功能描述  : 检查当前USIM的状态是否可以正常发送接收短信
输入参数  : 无
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:USIM卡状态正常
            其他:USIM卡状态不正常

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
************************************************************************/
VOS_UINT32 MN_MSG_CheckUsimStatus(VOS_VOID)
{
    VOS_UINT8                           ucCardStatus;


    ucCardStatus = USIMM_CARD_SERVIC_BUTT;

    /*当前的USIM卡不在位*/
    MN_NORM_LOG1("MN_MSG_CheckUsimStatus:Usim Status is ", f_stMsgUsimStatusInfo.ucUsimStatus);
    if (MN_MSG_SIM_NOT_EXIST == f_stMsgUsimStatusInfo.ucUsimStatus)
    {
        (VOS_VOID)MMA_GetUsimStatusFromUsim(&ucCardStatus, VOS_NULL_PTR);
        if (USIMM_CARD_SERVIC_SIM_PIN == ucCardStatus)/*USIMM_CARD_SERVIC_ENUM*/
        {
            return MN_ERR_CLASS_SMS_NEED_PIN1;
        }
        else if (USIMM_CARD_SERVIC_SIM_PUK == ucCardStatus)
        {
            return MN_ERR_CLASS_SMS_NEED_PUK1;
        }
        else if (USIMM_CARD_SERVIC_UNAVAILABLE == ucCardStatus)/*USIMM_CARD_SERVIC_UNAVAILABLE,  313(U)SIM failure*/
        {
            return MN_ERR_CLASS_SMS_UNAVAILABLE;
        }
        /*USIMM_CARD_SERVIC_NET_LCOK,手机中记录了特定的HOME PLMN，若插入SIM卡的HOME PLMN不是手机NV中指定的，则要求输入密码*/
        /*USIMM_CARD_SERVIC_IMSI_LCOK,手机中记录了特定卡的IMSI，非指定IMSI的SIM卡插入手机则要求输入密码*/
        /*上述两种错误原因值的处理目前还不明确，暂时做无卡处理*/
        else
        {
            return MN_ERR_CLASS_SMS_NOUSIM;
        }
    }

    MN_NORM_LOG1("MN_MSG_CheckUsimStatus: SMS power status:", (VOS_INT32)f_stMsgUsimStatusInfo.ucUsimStatus);
    /*USIM卡正在上电过程中*/
    if (MN_MSG_USIM_POWER_ON != f_stMsgUsimStatusInfo.enPowerState)
    {
        return MN_ERR_CLASS_SMS_UPDATE_USIM;
    }

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
函 数 名  : MN_MSG_GetSmCapacity
功能描述  : 获取最大能存在USIM或NVIM中短信的容量
输入参数  : enMemStore:需要获取短信容量的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 当前存储器的短信容量
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmsInfo.ucSmsRealRecNum;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        return f_usMsgNvimSmsCurReNum;
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmCapacity: enMemStore is ", enMemStore);
        return 0;
    }
}

/***********************************************************************
函 数 名  : MN_MSG_GetSmspCapacity
功能描述  : 获取最大能存在USIM或NVIM中短信参数的容量
输入参数  : enMemStore:需要获取短信容量的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 当前存储器的短信容量
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetSmspCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmspInfo.ucSmspRealRecNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        return MN_MSG_NV_SMSP_VOLUME;
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmspCapacity: enMemStore is ", enMemStore);
        return MN_MSG_FILE_NONE_REC;
    }
}

/***********************************************************************
函 数 名  : MN_MSG_GetSmsrCapacity
功能描述  : 获取最大存在USIM或NVIM中短信状态报告的容量
输入参数  : enMemStore:需要获取短信状态报告容量的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 当前存储器的短信状态报告容量
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目
************************************************************************/
VOS_UINT32 MN_MSG_GetSmsrCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmsrInfo.ucSmsrRealRecNum;
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            return MN_MSG_MAX_NVIM_SMSR_REC_NUM;
        }
        else
        {
            return 0;
        }

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmsrCapacity: enMemStore is ", enMemStore);
        return 0;
    }

}

/***********************************************************************
函 数 名  : MN_MSG_IsValidSmIndex
功能描述  : 判断当前输入的Index是合法的还是非法的
输入参数  : enMemStore:需要判断输入短信index的存储位置,USIM或NVIM中
            ucIndex:输入短信的索引
输出参数  : NONE
返 回 值  : VOS_TRUE:输入index合法
            VOS_FALSE:输入index非法
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsValidSmIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (ulIndex < f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return VOS_TRUE;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex < f_usMsgNvimSmsCurReNum)
        {
            return VOS_TRUE;
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmsrCapacity: enMemStore is ", enMemStore);
    }
    return VOS_FALSE;
}

/***********************************************************************
函 数 名  : MN_MSG_IsValidSmspIndex
功能描述  : 判断当前输入的Index是合法的还是非法的
输入参数  : ucIndex:输入短信参数的索引
输出参数  : NONE
返 回 值  : VOS_TRUE:输入index合法
            VOS_FALSE:输入index非法
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsValidSmspIndex(
    VOS_UINT8                           ucIndex
)
{
    if (ucIndex < f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

/***********************************************************************
函 数 名  : MN_MSG_IsEmptySmsp
功能描述  : 判断当前记录是否是空记录
输入参数  : usSmsIndex:输入短信参数的索引
输出参数  : NONE
返 回 值  : VOS_TRUE:输入索引合法
            VOS_FALSE:输入索引非法
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsEmptySmsp(
    VOS_UINT8                           ucIndex
)
{
    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return VOS_TRUE;
    }
    if (VOS_FALSE == f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].bUsed)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

/***********************************************************************
函 数 名  : MN_MSG_GetCurRcvMsgPath
功能描述  : 获取当前短信的相关参数
输入参数  : NONE
输出参数  : pstCfgParm:当前短信的相关参数
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetCurCfgParm(
    MN_MSG_CONFIG_PARM_STRU             *pstCfgParm
)
{
    PS_MEM_CPY(pstCfgParm,&f_stMsgCfgParm,sizeof(MN_MSG_CONFIG_PARM_STRU));
    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateRegState
功能描述  : 更新当前CS,PS域的注册情况
输入参数  : pstRcvPath:需要更新的接收短信的路径
输出参数  : NONE
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateRegState(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
)
{
    MN_NORM_LOG1("MN_MSG_UpdateRegState: current register domain: ", ucDomain);
    MN_NORM_LOG1("MN_MSG_UpdateRegState: current register state: ", (VOS_INT32)bAttachFlag);
    if (MN_MSG_SEND_DOMAIN_PS == ucDomain)
    {
        f_bMsgPsRegFlag = bAttachFlag;
    }
    else
    {
        f_bMsgCsRegFlag = bAttachFlag;
    }
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateRcvMsgPath
功能描述  : 更新当前接收短信的路径
输入参数  : pstRcvPath:需要更新的接收短信的路径
输出参数  : NONE
返 回 值  : MN_ERR_NO_ERROR:更新成功
            其他:更新失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 3.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
 4.日    期   : 2013年10月17日
   作    者   : w00167002
   修改内容   : NETSCAN:将CNMI设置的MT type类型传输给TAF。在<MT>=3，收到CLASS3
                短信时候，按照+CMT方式上报。
************************************************************************/
VOS_UINT32  MN_MSG_UpdateRcvMsgPath(
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPath
)
{
    TAF_NVIM_SMS_SERVICE_PARA_STRU  stSmsSrvParam;


    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    if (NV_OK == NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN))
    {
        if ( ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] == pstRcvPath->enRcvSmAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] == pstRcvPath->enSmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] == pstRcvPath->enRcvStaRptAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] == pstRcvPath->enStaRptMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] == f_stMsgCfgParm.enAppMemStatus))
        {
            f_stMsgCfgParm.enRcvSmAct = pstRcvPath->enRcvSmAct;
            f_stMsgCfgParm.enSmMemStore = pstRcvPath->enSmMemStore;
            f_stMsgCfgParm.enStaRptMemStore = pstRcvPath->enStaRptMemStore;
            f_stMsgCfgParm.enRcvStaRptAct = pstRcvPath->enRcvStaRptAct;
            f_stMsgCfgParm.enSmsServVersion = pstRcvPath->enSmsServVersion;


            /* 保存MT信息，在<MT>=3，收到CLASS3短信时候，按照+CMT方式上报 */
            f_stMsgCfgParm.enMtType         = pstRcvPath->enCnmiMtType;

            MN_INFO_LOG("MN_MSG_UpdateRcvMsgPath():The content to write is same as NV's");
            return MN_ERR_NO_ERROR;
        }
    }
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] = pstRcvPath->enRcvSmAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = pstRcvPath->enSmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] = pstRcvPath->enRcvStaRptAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] = pstRcvPath->enStaRptMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] = f_stMsgCfgParm.enAppMemStatus;

    if (NV_OK != NV_Write(en_NV_Item_SMS_SERVICE_Para,
                          (stSmsSrvParam.aucSmsServicePara),
                          MN_MSG_SRV_PARAM_LEN))
    {

        MN_ERR_LOG("MN_MSG_UpdateRcvMsgPath:Fail to write RcvMsgPath To NVIM!");
        return MN_ERR_CLASS_SMS_NVIM;
    }

    f_stMsgCfgParm.enRcvSmAct = pstRcvPath->enRcvSmAct;
    f_stMsgCfgParm.enSmMemStore = pstRcvPath->enSmMemStore;
    f_stMsgCfgParm.enStaRptMemStore = pstRcvPath->enStaRptMemStore;
    f_stMsgCfgParm.enRcvStaRptAct = pstRcvPath->enRcvStaRptAct;
    f_stMsgCfgParm.enSmsServVersion = pstRcvPath->enSmsServVersion;


    /* 保存MT信息，在<MT>=3，收到CLASS3短信时候，按照+CMT方式上报 */
    f_stMsgCfgParm.enMtType         = pstRcvPath->enCnmiMtType;

    return MN_ERR_NO_ERROR;
}

/***********************************************************************
函 数 名  : MN_MSG_GetRcvMsgPath
功能描述  : 获取当前接收短信的路径
输入参数  : 无
输出参数  : pstRcvPath:需要更新的接收短信的路径
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年10月17日
   作    者   : w00167002
   修改内容   : NETSCAN:将CNMI设置的MT type类型传输给TAF。在<MT>=3，收到CLASS3
                短信时候，按照+CMT方式上报。
************************************************************************/
VOS_VOID  MN_MSG_GetCurRcvMsgPath(
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    *pstRcvPath
)
{
    PS_MEM_SET(pstRcvPath,0,sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU));
    pstRcvPath->enRcvSmAct = f_stMsgCfgParm.enRcvSmAct;
    pstRcvPath->enSmMemStore = f_stMsgCfgParm.enSmMemStore;
    pstRcvPath->enRcvStaRptAct = f_stMsgCfgParm.enRcvStaRptAct;
    pstRcvPath->enStaRptMemStore = f_stMsgCfgParm.enStaRptMemStore;
    pstRcvPath->enSmsServVersion = f_stMsgCfgParm.enSmsServVersion;

    pstRcvPath->enCnmiMtType     = f_stMsgCfgParm.enMtType;

}

/***********************************************************************
函 数 名  : MSG_PreferedGetCurSendDomain
功能描述  : PS域或CS域优先发送时,获取当前短信的实际发送域
输入参数  : penHopeSendDomain:当前发送短信时,优先期望的短信发送域
输出参数  :
返 回 值  : 当前发送短信时,实际的短信发送域
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2009年7月06日
   作    者   : z40661
   修改内容   : 新生成函数
PS域优先发送
                 CSPS域发送无失败   CS域发送失败    PS域发送失败    CSPS域都发送失败
CS域可用         CS域发送           CS域发送        CS域发送        CS域发送
PS域可用         PS域发送           PS域发送        PS域发送        PS域发送
CSPS域都可用     PS域发送           PS域发送        CS域发送        CS域发送
CSPS域都不可用   无可用域           无可用域        无可用域        无可用域

CS域优先发送
                 CSPS域发送无失败   CS域发送失败    PS域发送失败    CSPS域都发送失败
CS域可用         CS域发送           CS域发送        CS域发送        CS域发送
PS域可用         PS域发送           PS域发送        PS域发送        PS域发送
CSPS域都可用     CS域发送           PS域发送        CS域发送        CS域发送
CSPS域都不可用   无可用域           无可用域        无可用域        无可用域
  2.日    期   : 2009年10月16日
    作    者   : f62575
    修改内容   : 问题单号:AT2D15127, 服务域为PS ONLY，发送域为CS PREFER，参照标杆
                 短信首先尝试从CS域发送；
  3.日    期   : 2009年10月23日
     作    者   : f62575
     修改内容   : 问题单号AT2D15225:, 启用短信重发功能后短信无法在PS域发送问题；
  4.日    期   : 2011年3月29日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011030500602，增加CS域可用的判断标准，UE服务域为非PS
                 ONLY, IMSI在CS域有效且CS域未被BAR情况下可以尝试重发，支持在PS域重发短信
************************************************************************/
LOCAL MN_MSG_SEND_DOMAIN_ENUM_U8 MSG_PreferedGetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain
)
{
    VOS_UINT32                          ulPsAvailable;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealSendDomain = MN_MSG_SEND_DOMAIN_NO;
    MN_MSG_DOMAIN_AVAIL_FLAG_U8         enDomainAvail = MN_MSG_NO_DOMAIN_AVAIL;
    VOS_BOOL                            bCsDomainAvailable;

    ulPsAvailable = GMM_ServiceStatusForSms();
    if ((VOS_TRUE == f_bMsgPsRegFlag)
     && (GMM_SMS_SERVICE_AVAILABLE == ulPsAvailable))
    {
        enDomainAvail |= MN_MSG_PS_DOMAIN_AVAIL;
    }

    MN_MSG_CsDomainAvailable(&bCsDomainAvailable);
    if (VOS_TRUE == bCsDomainAvailable)
    {
        enDomainAvail |= MN_MSG_CS_DOMAIN_AVAIL;
    }

    if (MN_MSG_CS_DOMAIN_AVAIL == enDomainAvail)
    {
        /* 当前仅CS域可用 */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
    }
    else if (MN_MSG_PS_DOMAIN_AVAIL == enDomainAvail)
    {
        /* 当前仅PS域可用 */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
    }
    else if (MN_MSG_NO_DOMAIN_AVAIL == enDomainAvail)
    {
        /* 当前CSPS域都不可用 */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_NO;
    }
    else
    {
        /* 当前CSPS域都可用 */
        if ( (MN_MSG_SEND_FAIL_CSPS_DOMAIN == f_enMsgSendFailFlag)
          || (MN_MSG_SEND_FAIL_PS_DOMAIN == f_enMsgSendFailFlag))
        {
            /*CSPS域都发送失败,仍然通过CS域继续发送*/
            /*PS域发送失败,通过CS域继续发送*/
            enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
        }
        else if(MN_MSG_SEND_FAIL_CS_DOMAIN == f_enMsgSendFailFlag)
        {
            /*CS域发送失败,通过PS域继续发送*/
            enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        }
        else
        {
            /* CSPS域都没有发送失败,根据当前设置进行发送 */
            if(MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain)
            {
                enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
            }
            else
            {
                enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
            }
        }
    }

    return enRealSendDomain;
}

/***********************************************************************
函 数 名  : MN_MSG_GetCurSendDomain
功能描述  : 获取当前发送短信时,短信的实际发送域
输入参数  : penHopeSendDomain:当前发送短信时,期望的短信发送域
输出参数  : penRealSendDomain:当前发送短信时,实际的短信发送域
返 回 值  :
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年3月29日
   作    者   : 傅映君/f62575
   修改内容   : DTS2011030500602，增加CS域可用的判断标准，UE服务域为非PS
                ONLY, IMSI在CS域有效且CS域未被BAR情况下可以尝试重发，支持在PS域重发短信
 3.日    期   : 2012年5月7日
   作    者   : z00161729
   修改内容   : GUL BG搜网修改
************************************************************************/
VOS_VOID   MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
)
{
    VOS_UINT32                          ulPsAvailable;
    VOS_UINT32                          bCsDomainAvailable;

    *penRealSendDomain = MN_MSG_SEND_DOMAIN_NO ;

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
    {
        /* 快速指定搜网过程用户发短信，L不缓存，回复error ind后续靠短信重发机制再次触发发短信 ，
           此处无需判断f_bMsgPsRegFlag为VOS_TRUE */
        *penRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        return;
     }
#endif

    ulPsAvailable = GMM_ServiceStatusForSms();
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :f_bMsgPsRegFlag is ", (VOS_INT32)f_bMsgPsRegFlag);
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :ulPsAvailable is ", (VOS_INT32)ulPsAvailable);
    if (MN_MSG_SEND_DOMAIN_PS == enHopeSendDomain)
    {
        if ((VOS_TRUE == f_bMsgPsRegFlag)
         && (GMM_SMS_SERVICE_AVAILABLE == ulPsAvailable))
        {
            *penRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        }
    }
    else if (MN_MSG_SEND_DOMAIN_CS == enHopeSendDomain)
    {
        MN_MSG_CsDomainAvailable(&bCsDomainAvailable);
        if (VOS_TRUE == bCsDomainAvailable)
        {
            *penRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
        }
    }
    else if ( (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain)
           || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain))
    {
        *penRealSendDomain = MSG_PreferedGetCurSendDomain(enHopeSendDomain);
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetCurSendDomain hoped domain: ", enHopeSendDomain);
    }
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :send domain is ", (VOS_INT32)*penRealSendDomain);
}

/***********************************************************************
函 数 名  : MN_MSG_GetCurAppMemStatus
功能描述  : 获取当前APP的内存使用状态
输入参数  : NONE
输出参数  : penMemStatus:当前APP的内存使用状态
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetCurAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             *penMemStatus
)
{
    *penMemStatus = f_stMsgCfgParm.enAppMemStatus;
    MN_INFO_LOG1("MN_MSG_GetCurAppMemStatus: f_stMsgCfgParm.enAppMemStatus is ", f_stMsgCfgParm.enAppMemStatus);
}

/***********************************************************************
函 数 名  : MN_MSG_UpdateAppMemStatus
功能描述  : 更新APP的内存使用状态
输入参数  : enMemStatus:需要更新的APP的内存使用状态
输出参数  : NONE
返 回 值  : MN_ERR_NO_ERROR:更新成功
            MN_ERR_CLASS_SMS_NVIM:更新失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2012年12月11日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 3.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
************************************************************************/
VOS_UINT32  MN_MSG_UpdateAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             enMemStatus
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsSrvParam;


    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    if (NV_OK == NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN))
    {
        if ( ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] == f_stMsgCfgParm.enRcvSmAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] == f_stMsgCfgParm.enSmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] == f_stMsgCfgParm.enRcvStaRptAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] == f_stMsgCfgParm.enStaRptMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_CBM_MEM_STORE_OFFSET] == f_stMsgCfgParm.enCbmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] == enMemStatus))
        {
            f_stMsgCfgParm.enAppMemStatus = enMemStatus;
            MN_INFO_LOG("MN_MSG_UpdateAppMemStatus():The content to write is same as NV's");
            return MN_ERR_NO_ERROR;
        }
    }
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] = f_stMsgCfgParm.enRcvSmAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = f_stMsgCfgParm.enSmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] = f_stMsgCfgParm.enRcvStaRptAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] = f_stMsgCfgParm.enStaRptMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_CBM_MEM_STORE_OFFSET] = f_stMsgCfgParm.enCbmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] = enMemStatus;

    ulRet = NV_Write(en_NV_Item_SMS_SERVICE_Para,
                     &stSmsSrvParam,
                     MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_UpdateAppMemStatus:Write NV Failed");
        return MN_ERR_CLASS_SMS_NVIM;
    }

    f_stMsgCfgParm.enAppMemStatus = enMemStatus;

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
函 数 名  : MN_MSG_FindNodeByUsimResult
功能描述  : 收到从USIM返回的结果记录时,找到该条记录当前进行操作的节点信息f_astMsgSetUsimInfo
输入参数  : ucRecIndex:操作USIM的记录数
            usEfId:操作USIM的文件EFID
输出参数  : pstSmaUsimInfo:找到的节点信息f_astMsgSetUsimInfo
            pucIndex:找到节点在USIM节点列表的索引
返 回 值  : VOS_OK:成功找到
            VOS_ERR:未能找到
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_FindNodeByUsimResult(
    VOS_UINT8                           ucRecIndex,
    VOS_UINT16                          usEfId,
    MN_MSG_USIM_INFO_STRU               *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
)
{
    VOS_UINT32                          i;
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        if (VOS_TRUE == f_astMsgSetUsimInfo[i].bUsed)
        {
            if ((ucRecIndex == f_astMsgSetUsimInfo[i].stUsimInfo.ucRecIndex)
             && (usEfId == f_astMsgSetUsimInfo[i].stUsimInfo.usEfId))
            {
                PS_MEM_CPY(pstSmaUsimInfo,&f_astMsgSetUsimInfo[i].stUsimInfo,sizeof(MN_MSG_USIM_INFO_STRU));
                *pulIndex = i;
                return VOS_OK;
            }
        }
    }
    return VOS_ERR;
}

/***********************************************************************
函 数 名  : MN_MSG_GetUsimRec
功能描述  : 获取当前同一种类型的操作(如list,delete等等),设置USIM的记录数
输入参数  : 无
输出参数  : 无
返 回 值  : 当前同一种类型的操作(如list,delete等等),设置USIM的记录数
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT8  MN_MSG_GetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType
)
{
    if (MN_MSG_SET_USIM_LIST == enType)
    {
        return f_stMsgSetUsimRec.ucList;
    }
    else if (MN_MSG_SET_USIM_DELETE == enType)
    {
        return f_stMsgSetUsimRec.ucDelete;
    }
    else if (MN_MSG_SET_USIM_DELETE_BEGIN == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteBegin;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteStaRpt;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT_BEGIN == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteStaRptBegin;
    }
    else
    {
        return f_stMsgSetUsimRec.ucDeleteEfSmsp;
    }
}

/***********************************************************************
函 数 名  : MN_MSG_GetDeleteReportFlag
功能描述  : 获取当前操作(如list,delete等等),是否已经上报
输入参数  : enType:当前操作的类型
输出参数  : 无
返 回 值  : 当前操作(如list,delete等等),是否已经上报
            VOS_TRUE:已经上报
            VOS_FALSE:未能上报
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月19日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL  MN_MSG_GetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType
)
{
    if (MN_MSG_SET_USIM_DELETE == enType )
    {
        return f_stMsgSetUsimRec.bDeleteReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        return f_stMsgSetUsimRec.bDeleteStaRptReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_EFSMSP == enType)
    {
        return f_stMsgSetUsimRec.bDeleteEfSmspReportFlag;
    }
    else
    {
        return VOS_TRUE;
    }
}

/***********************************************************************
函 数 名  : MN_MSG_SetDeleteReportFlag
功能描述  : 设置当前操作(如list,delete等等),是否上报
输入参数  : enType:当前操作的类型
            bReportFlag:上报标志
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月19日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_SetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_BOOL                            bReportFlag
)
{
    if (MN_MSG_SET_USIM_DELETE == enType )
    {
        f_stMsgSetUsimRec.bDeleteReportFlag = bReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = bReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_EFSMSP == enType)
    {
        f_stMsgSetUsimRec.bDeleteEfSmspReportFlag = bReportFlag;
    }
    else
    {
        return ;
    }
}

/***********************************************************************
函 数 名  : MN_MSG_SetUsimRec
功能描述  : 重新设置向USIM设置的记录数,
输入参数  : enType:当前操作类型
            ucRec:需要设置的记录数
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_SetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_UINT8                           ucRec
)
{
    if (MN_MSG_SET_USIM_LIST == enType)
    {
        f_stMsgSetUsimRec.ucList = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE == enType)
    {
        f_stMsgSetUsimRec.ucDelete = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_BEGIN == enType)
    {
        f_stMsgSetUsimRec.ucDeleteBegin = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        f_stMsgSetUsimRec.ucDeleteStaRpt = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT_BEGIN == enType)
    {
        f_stMsgSetUsimRec.ucDeleteStaRptBegin = ucRec;
    }
    else
    {
        f_stMsgSetUsimRec.ucDeleteEfSmsp = ucRec;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_MoSmsControlEnvelopeReq
 功能描述  : SMS MO CONTROL功能开启时,下发Envelope datadownload到USIM卡
 输入参数  : pstAddrObj1: SC Addr
             pstAddrObj2: Dest Addr
             pucLI:       Location Information
 输出参数  : VOS_TRUE:返回成功
             VOS_FALSE:返回失败
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月16日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  3.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 。
  4.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:MN_MSG_MoSmsControlEnvelopeReq增加client ID参数
  5.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，MN_GetLaiForMoCtrl=>TAF_SDC_GetCurrentLai
  6.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_UINT32  MN_MSG_MoSmsControlEnvelopeReq(
    VOS_UINT16                          usClientId,
    MN_MSG_BCD_ADDR_STRU               *pstRpDestAddr,
    MN_MSG_BCD_ADDR_STRU               *pstTpDestAddr
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    SI_STK_ENVELOPE_STRU                stENStru;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stENStru, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stENStru.enEnvelopeType     = SI_STK_ENVELOPE_SMSCRTL;
    stENStru.DeviceId.ucSDId    = SI_STK_DEV_TERMINAL;
    stENStru.DeviceId.ucDDId    = SI_STK_DEV_UICC;

    stENStru.uEnvelope.MOSMSCtrl.OP_Addr1 = 1;
    stENStru.uEnvelope.MOSMSCtrl.OP_Addr2 = 1;
    stENStru.uEnvelope.MOSMSCtrl.OP_Local = 1;

    stENStru.uEnvelope.MOSMSCtrl.Addr1.ucNumType    = pstRpDestAddr->addrType;
    stENStru.uEnvelope.MOSMSCtrl.Addr1.ucLen        = pstRpDestAddr->ucBcdLen;
    stENStru.uEnvelope.MOSMSCtrl.Addr1.pucAddr      = pstRpDestAddr->aucBcdNum;

    stENStru.uEnvelope.MOSMSCtrl.Addr2.ucNumType    = pstTpDestAddr->addrType;
    stENStru.uEnvelope.MOSMSCtrl.Addr2.ucLen        = pstTpDestAddr->ucBcdLen;
    stENStru.uEnvelope.MOSMSCtrl.Addr2.pucAddr      = pstTpDestAddr->aucBcdNum;

    stENStru.uEnvelope.MOSMSCtrl.LocInfo.pucATSLI   = aucLI;

    /* 获取ENVELOPE消息参数: 服务小区信息 */
    TAF_SDC_Get3GppCurrentLai(aucLI, &stENStru.uEnvelope.MOSMSCtrl.LocInfo.ulLen);


    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stENStru);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_MoSmsControlEnvelopeReq: Usim Returns Error");
        return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
    }
    else
    {
        return MN_ERR_NO_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_SmsPPEnvelopeReq
 功能描述  : 收到Class 2 和PID为USIM DataDownLad短信时,需要下发Envelope datadownload到USIM卡
 输入参数  : pstAddr:     SC Addr
             pucTpduData: SMS TPDU (SMS-DELIVER)
 输出参数  : 无
 返 回 值  : VOS_TRUE; 返回成功
             VOS_FALSE:返回失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年7月14日
    作    者   : 傅映君/f62575
    修改内容   : DTS2010071302170: PP DOWNLODAD操作导致内存泄漏
  3.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 。
  4.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:SI_STK_EnvelopeDownload接口增加client ID
  5.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_UINT32  MN_MSG_SmsPPEnvelopeReq(
    const MN_MSG_BCD_ADDR_STRU          *pstAddr,
    const VOS_UINT8                     *pucTpduData,
    const VOS_UINT32                    ulTpduLen
)
{
    SI_STK_ENVELOPE_STRU stDataDownLoad;
    SI_STK_SMS_PP_DOWNLOAD_STRU *pstPPDown;
    VOS_UINT32 ulRet = VOS_ERR;
    VOS_UINT32 ulOffset;

    if(SI_STK_DATA_MAX_LEN <(pstAddr->ucBcdLen+ulTpduLen))
    {
        return VOS_ERR;
    }

    PS_MEM_SET(&stDataDownLoad, 0, sizeof(stDataDownLoad));

    stDataDownLoad.enEnvelopeType   = SI_STK_ENVELOPE_PPDOWN;
    stDataDownLoad.DeviceId.ucSDId  = SI_DEVICE_NETWORK;
    stDataDownLoad.DeviceId.ucDDId  = SI_DEVICE_UICC;

    pstPPDown = &stDataDownLoad.uEnvelope.PPDown;
    /*填写短信中心地址*/
    pstPPDown->OP_Addr = 1;
    pstPPDown->Addr.ucNumType = pstAddr->addrType;
    pstPPDown->Addr.ucLen     = pstAddr->ucBcdLen;

    PS_MEM_CPY(stDataDownLoad.aucData, pstAddr->aucBcdNum, pstPPDown->Addr.ucLen);

    pstPPDown->Addr.pucAddr = stDataDownLoad.aucData;

    ulOffset = pstPPDown->Addr.ucLen;

    /*填写短信PDU内容*/
    pstPPDown->OP_TPDU = 1;
    pstPPDown->TPDU.ulLen = ulTpduLen;

    PS_MEM_CPY(&stDataDownLoad.aucData[ulOffset], pucTpduData, pstPPDown->TPDU.ulLen);

    pstPPDown->TPDU.pucTPDU = &stDataDownLoad.aucData[ulOffset];


    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, MN_CLIENT_ID_BROADCAST,&stDataDownLoad);

/*
    调用USIM提供的envelope data download函数将内容下发的USIM
    if 函数返回成功
        返回 TAF_OK
    else
        返回 MN_ERR
*/

    return ulRet;
}

/***********************************************************************
函 数 名  : MN_MSG_WriteSmssFile
功能描述  : 更新内存,USIM中和NVIM保留的SMSS文件值,无论USIM,NVIM是否更新成功,
            内存中更新成功,优先更新USIM中的EFSMSS的内容
输入参数  : pstSmssInfo:需要更新EFSMSS的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年01月20日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2012年8月10日
   作    者   : y00213812
   修改内容   : DTS2012082204471, TQE清理
 3.日    期   : 2012年12月26日
   作    者   : 张鹏 id:00214637
   修改内容  : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 。
 4.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
************************************************************************/
VOS_VOID  MN_MSG_WriteSmssFile(
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucWriteData[MN_MSG_MAX_EF_LEN];
    VOS_UINT32                          ulUsimIndex = 0;
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
    TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU   stSmssContent;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMSS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSS_ID;
    }
    ulRet       = 0;

    PS_MEM_SET(aucWriteData,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    PS_MEM_SET(&stSmssContent,(VOS_CHAR)0x00,MN_MSG_EFSMSS_PARA_LEN);

    aucWriteData[0] = pstSmssInfo->ucLastUsedTpMr;
    if (MN_MSG_MEM_FULL_SET == pstSmssInfo->enMemCapExcNotFlag)
    {
        aucWriteData[1] = MN_MSG_SIM_MEM_FULL_SET;
    }
    else
    {
        aucWriteData[1] = MN_MSG_SIM_MEM_FULL_UNSET;
    }

    /*先更新内存中的信息*/
    PS_MEM_CPY(&f_stMsgEfSmssInfo.stEfSmssInfo,pstSmssInfo,sizeof(f_stMsgEfSmssInfo.stEfSmssInfo));

    if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
    {
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSS_ID, aucWriteData, (VOS_UINT8)f_stMsgEfSmssInfo.ulFileLen, MN_MSG_USIM_DEF_REC);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSS_ID, aucWriteData, (VOS_UINT8)f_stMsgEfSmssInfo.ulFileLen, MN_MSG_USIM_DEF_REC);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }

        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmssFile:Add Usim Node Failed");
            return ;
        }
        PS_MEM_SET(&stUsimInfo,0X00, sizeof(stUsimInfo));


        stUsimInfo.opId = 0;
        stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stUsimInfo.ucRecIndex = MN_MSG_USIM_DEF_REC;
        stUsimInfo.enSmaUsimAction = MN_MSG_USIM_SET_EFSMSS;

        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
        ulRet = MN_MSG_CreateNewUsimNode(&stUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmssFile:CreateNewUsimNode Error");
        }
        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    }
    else
    {
        PS_MEM_CPY(&stSmssContent, (VOS_VOID*)aucWriteData, MN_MSG_MAX_EF_LEN);
        ulRet = NV_Write(en_NV_Item_SMS_EFSMSS_Para,(VOS_VOID*)&stSmssContent,MN_MSG_MAX_EF_LEN);
        if (NV_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmssFile:Write NVIM Error");
        }
    }
}

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)\
  && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))
/***********************************************************************
函 数 名  : MN_MSG_WriteSmsFile
功能描述  : 更新内存,USIM中和NVIM保留的SMS文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            pulMeIndex:向FLASH写短信是的索引值
            pstWriteUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pucContentInfo:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:失败以及失败的原因值
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年02月11日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const VOS_UINT32                   *pulMeIndex,
    const MN_MSG_WRITE_USIM_INFO_STRU  *pstWriteUsimInfo,
    VOS_UINT8                          *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    ulRet       = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_NULL_PTR == pstWriteUsimInfo)
        {
            return MN_ERR_NULLPTR;
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile: EFSMS is not available.");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstWriteUsimInfo->stUsimInfo.ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstWriteUsimInfo->stUsimInfo.ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        if (VOS_TRUE == pstWriteUsimInfo->bCreateNode)
        {
            /*设置USIM时,需要将原始的短信保留下来*/
            ucOrgIndex = pstWriteUsimInfo->stUsimInfo.ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
            PS_MEM_SET((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
            PS_MEM_CPY((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),
                       (f_stMsgEfSmsInfo.aucEfSmsList+ (pstWriteUsimInfo->stUsimInfo.ucRecIndex * MN_MSG_EFSMS_LEN)),
                       MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_CreateNewUsimNode(&(pstWriteUsimInfo->stUsimInfo),&ulUsimIndex);
            if (VOS_OK != ulRet)
            {
                return MN_ERR_CLASS_SMS_CREATE_NODE;
            }
        }
        /*更新内存中的信息*/
        PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (pstWriteUsimInfo->stUsimInfo.ucRecIndex * MN_MSG_EFSMS_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMS_LEN);
        return MN_ERR_NO_ERROR;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (VOS_NULL_PTR == pulMeIndex)
        {
            return MN_ERR_NULLPTR;
        }

        ulRet = MN_MSG_WriteMsgInFlashByIndex(*pulMeIndex,pucContentInfo);

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmsFile:Write FLASH Error");
            MN_MNTN_RecordSmsMeError(MNTN_ME_OPERATION_WRITE, ulRet);
            return ulRet;
        }
        else
        {
            /*更新内存中NVIM中的短信状态*/
            f_aucMsgNvimSmStatus[*pulMeIndex] = *pucContentInfo;
            return MN_ERR_NO_ERROR;
        }
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}
#else
/***********************************************************************
函 数 名  : MN_MSG_WriteSmsFile
功能描述  : 更新内存,USIM中和NVIM保留的SMS文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            pstSmaUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pucContentInfo:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:失败以及失败的原因值
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            bCreateNode,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile: EFSMS is not available.");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }

        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        if (VOS_TRUE == bCreateNode)
        {
            /*设置USIM时,需要将原始的短信保留下来*/
            ucOrgIndex = pstSmaUsimInfo->ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
            PS_MEM_SET((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),0XFF,MN_MSG_EFSMS_LEN);
            PS_MEM_CPY((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),
                       (f_stMsgEfSmsInfo.aucEfSmsList+ (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMS_LEN)),
                       MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
            if (VOS_OK != ulRet)
            {
                return MN_ERR_CLASS_SMS_CREATE_NODE;
            }
        }
        /*更新内存中的信息*/
        PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMS_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMS_LEN);
        return MN_ERR_NO_ERROR;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (NV_OK != NV_Write(en_NV_Item_SMS_Content,
                              (VOS_VOID*)pucContentInfo,
                              MN_MSG_EFSMS_LEN))
        {
            MN_ERR_LOG("MN_MSG_WriteSmsFile:Write NVIM Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
        else
        {
            /*更新内存中NVIM中的短信状态*/
            f_aucMsgNvimSmStatus[pstSmaUsimInfo->ucRecIndex] = *pucContentInfo;
            return MN_ERR_NO_ERROR;
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}

#endif

/***********************************************************************
函 数 名  : MN_MSG_WriteSmsrFile
功能描述  : 更新内存,USIM中和NVIM保留的EFSMSR文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            pstSmaUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pucContentInfo:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:失败以及失败的原因值
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsrFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType   = TAF_SDC_GetSimType();
    ulRet       = 0;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        /*设置USIM时,需要将原始的短信状态报告保留下来*/
        ucOrgIndex = pstSmaUsimInfo->ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
        PS_MEM_SET((f_aucMsgOrgSmsrContent + (ucOrgIndex * MN_MSG_EFSMSR_LEN)),0X00,MN_MSG_EFSMSR_LEN);
        PS_MEM_CPY((f_aucMsgOrgSmsrContent + (ucOrgIndex * MN_MSG_EFSMSR_LEN)),
                   (f_stMsgEfSmsrInfo.aucEfSmsrList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMSR_LEN)),
                   MN_MSG_EFSMSR_LEN);
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSR_ID,pucContentInfo,MN_MSG_EFSMSR_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSR_ID,pucContentInfo,MN_MSG_EFSMSR_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsrFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }

        ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_SMS_CREATE_NODE;
        }

        /*更新内存中的信息*/
        PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMSR_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMSR_LEN);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    else if(MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (NV_OK != NV_Write(en_NV_Item_SMS_Status,pucContentInfo,MN_MSG_EFSMSR_LEN))
            {
                MN_ERR_LOG("MN_MSG_WriteSmsrFile:Write NVIM Error");
                return MN_ERR_CLASS_SMS_NVIM;
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsrFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
    return MN_ERR_NO_ERROR;

}

/***********************************************************************
函 数 名  : MN_MSG_WriteSmspFile
功能描述  : 更新内存,USIM中和NVIM保留的SMS文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            pstSmaUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pstSrvParm:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:更新失败以及失败的原因值
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmspFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    const MN_MSG_SRV_PARAM_STRU         *pstSrvParam
)
{
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulAlphaIdLen;
    VOS_UINT32                          ulAddrlen;
    VOS_UINT32                          ulPos = 0;
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stSmspContent;
    VOS_UINT8                           ucLen;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstEfSmspRec;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }
    ulRet       = 0;

    MN_INFO_LOG("MN_MSG_WriteSmspFile: step into function.");

    PS_MEM_SET(&stSmspContent,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);
    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    pstEfSmspRec = &f_stMsgEfSmspInfo.astEachEfSmspInfo[pstSmaUsimInfo->ucRecIndex];
    ucLen = (VOS_UINT8)(MN_MSG_MIN_SRV_PARM_LEN + pstEfSmspRec->stParm.stAlphaIdInfo.ulLen);

    /*Alpha Identifier*/
    if (pstSrvParam->stAlphaIdInfo.ulLen > pstEfSmspRec->stParm.stAlphaIdInfo.ulLen)
    {
        ulAlphaIdLen = pstEfSmspRec->stParm.stAlphaIdInfo.ulLen;
    }
    else
    {
        ulAlphaIdLen = pstSrvParam->stAlphaIdInfo.ulLen;
    }

    PS_MEM_CPY(aucSmspContent,pstSrvParam->stAlphaIdInfo.aucData,ulAlphaIdLen);

    /*将游标移至ALPHAID数据项后，ALPHAID数据数据区的长度为固定值，与用户输入的实际数据长度无关*/
    ulPos = pstEfSmspRec->stParm.stAlphaIdInfo.ulLen;

    /*Parameter Indicators*/
    MN_INFO_LOG1("MN_MSG_WriteSmspFile: pstSrvParam->ucParmInd", pstSrvParam->ucParmInd);
    /*lint -e961*/
    aucSmspContent[ulPos++] = pstSrvParam->ucParmInd;
    /*lint +e961*/

    /*TP Destination Address*/
    MN_NORM_LOG1("MN_MSG_WriteSmspFile: pstSrvParam->stDestAddr.ucBcdLen", pstSrvParam->stDestAddr.ucBcdLen);
    PS_MEM_SET(&aucSmspContent[ulPos], (VOS_CHAR)MN_MSG_USIM_FILL_BYTE, MN_MSG_EFSMSP_ADDR_UNIT_LEN);
    if ((0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
     && (0 != pstSrvParam->stDestAddr.ucBcdLen))
    {
        ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU*)&pstSrvParam->stDestAddr, &stAsciiAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_FALSE, &aucSmspContent[ulPos], &ulAddrlen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TS Service Centre Address*/
    PS_MEM_SET(&aucSmspContent[ulPos],(VOS_CHAR)MN_MSG_USIM_FILL_BYTE, MN_MSG_EFSMSP_ADDR_UNIT_LEN);
    if ((0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR))
     && (0 != pstSrvParam->stScAddr.ucBcdLen))
    {
        ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU *)&pstSrvParam->stScAddr, &stAsciiAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_TRUE, &aucSmspContent[ulPos], &ulAddrlen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TP Protocol Identifier*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_PID))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucPid;
        /*lint +e961*/
    }

    /*TP Data Coding Scheme*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DCS))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucDcs;
        /*lint +e961*/
    }

    /*TP Validity Period*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_VALIDITY))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucValidPeriod;
        /*lint +e961*/
    }
    PS_MEM_CPY(&stSmspContent, aucSmspContent, MN_MSG_MAX_EF_LEN);

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmspFile: USIMM_USIM_EFSMSP_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSP_ID,aucSmspContent,ucLen,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSP_ID,aucSmspContent,ucLen,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmspFile:Add Usim Node Failed");
            if (MN_MSG_USIM_DELETE_EFSMSP == pstSmaUsimInfo->enSmaUsimAction)
            {
                f_stMsgSetUsimRec.bDeleteEfSmspReportFlag = VOS_TRUE;
            }
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }

        ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_SMS_CREATE_NODE;
        }

        /*更新内存中的信息*/
        if (MN_MSG_SRV_PARM_TOTALABSENT == ((pstSrvParam->ucParmInd) & MN_MSG_SRV_PARM_TOTALABSENT))
        {
            pstEfSmspRec->bUsed = VOS_FALSE;
        }
        else
        {
            pstEfSmspRec->bUsed = VOS_TRUE;
        }

        /*将老的短信服务参数保留下来*/
        PS_MEM_CPY(&f_astMsgOrgSmspInfo[pstSmaUsimInfo->ucRecIndex],
                   pstEfSmspRec,
                   sizeof(f_astMsgOrgSmspInfo[pstSmaUsimInfo->ucRecIndex]));

        PS_MEM_CPY(&pstEfSmspRec->stParm, pstSrvParam, sizeof(pstEfSmspRec->stParm));
        pstEfSmspRec->stParm.stAlphaIdInfo.ulLen = ulAlphaIdLen;
    }
    else
    {
        if (NV_OK != NV_Write(en_NV_Item_SMS_EFSMSP_Para,stSmspContent.aucSmsEfsmspPara,MN_MSG_MAX_EF_LEN))
        {
            MN_ERR_LOG("MN_MSG_WriteSmspFile:Write NVIM Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
    }

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
函 数 名  : MN_MSG_RecoverOrgSrvParm
功能描述  : 删除或写短信参数,USIM返回失败,需要将内存中的短信参数恢复回来
输入参数  : ucIndex:恢复短信参数存入的索引
输出参数  : pstSrvParm:需要恢复的短信参数的内容
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSrvParm(
    VOS_UINT8                           ucIndex,
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSrvParam
)
{
    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSrvParm:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pstSrvParam,0X00,sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
    PS_MEM_CPY(pstSrvParam,&f_astMsgOrgSmspInfo[ucIndex],sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
}

/***********************************************************************
函 数 名  : MN_MSG_RecoverOrgSm
功能描述  : 删除或写短信,USIM返回失败,需要将内存中的短信恢复回来
输入参数  : ucIndex:恢复短信存入的索引
输出参数  : pucSmContent:需要恢复的短信的内容
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSm(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmContent
)
{
    if (ucIndex >= MN_MSG_MAX_ORG_REC_NUM)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSrvParm:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_CPY(pucSmContent,
              (f_aucMsgOrgSmContent + (ucIndex * MN_MSG_EFSMS_LEN)),
              MN_MSG_EFSMS_LEN);
}

/***********************************************************************
函 数 名  : MN_MSG_RecoverOrgSmsr
功能描述  : 删除或写短信状态报告时,USIM返回失败,需要将内存中的短信状态报告恢复回来
输入参数  : ucIndex:恢复短信状态报告存入的索引
输出参数  : pucSmsrContent:需要恢复的短信状态报告的内容
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSmsr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmsrContent
)
{
    if (ucIndex >= MN_MSG_MAX_DELETE_REC_NUM)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSmsr:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
    PS_MEM_CPY(pucSmsrContent,
               (f_aucMsgOrgSmsrContent + (ucIndex * MN_MSG_EFSMSR_LEN)),
               MN_MSG_EFSMSR_LEN);
}

/***********************************************************************
函 数 名  : MN_MSG_SmCfgDataInit
功能描述  : TAF模块收到USIM卡在位与否的消息后,调用此函数初始化SM模块变量
            如果卡在位,则向USIM发送请求获取USIM中的SM相关参数,并获取NVIM中
            SM相关参数
输入参数  : ucUsimState:USIM卡是否在位
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年7月13日
   作    者   : l00208543
   修改内容   : STK升级项目，删除MSG_GetNvimParmInfo的调用

************************************************************************/
VOS_VOID MN_MSG_SmCfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_INFO_LOG("MN_MSG_SmCfgDataInit:Step into function.");

    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-11, begin */
    /* Deleted by l00208543 for V9R1 STK升级, 2013-7-11, end */

    MN_INFO_LOG1("MN_MSG_SmCfgDataInit:enUsimStatus is ", (VOS_INT32)enUsimStatus);
    MN_INFO_LOG1("MN_MSG_SmCfgDataInit: current enUsimStatus is ",f_stMsgUsimStatusInfo.ucUsimStatus);
    if (MNPH_USIM_STATUS_AVILABLE == enUsimStatus)
    {
        if (MN_MSG_SIM_EXIST == f_stMsgUsimStatusInfo.ucUsimStatus)
        {
            MN_NORM_LOG("MN_MSG_CfgDataInit:Rcv Usim Exist Flag Again");
            if ((MN_MSG_USIM_POWER_ON != f_stMsgUsimStatusInfo.enPowerState)
             && (MN_MSG_USIM_POWER_BEGIN != f_stMsgUsimStatusInfo.enPowerState))
            {
                MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
                MN_NORM_LOG("MN_MSG_CfgDataInit:Stop Timer");
            }
        }
        f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_EXIST;
        f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_BEGIN;

        MN_MSG_UpdateUstInfo();

        /*获取USIM相关参数*/
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSS_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSS_ID);
        }
    }
    else
    {
        f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_NOT_EXIST;
        f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_ON;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_CreateEFSmContent
 功能描述  : 根据SC Addr和TPDU创建一条短信,短信格式为USIM卡中EFSMS的格式
 输入参数  : pstScAddr:短信中心的地址
             pstRawData:TPDU的内容
             ucStatus:短信的状态
 输出参数  : pucContent:短信内容,USIM卡中EFSMS的格式
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2009年02月02日
    作    者   : s62952
    修改内容   : 问题单号：AT2D08614
*****************************************************************************/
VOS_VOID MN_MSG_CreateEFSmContent(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucStatus,
    VOS_UINT8                           *pucContent
)
{
    VOS_UINT32                          ulWriteSet = 0;

    PS_MEM_SET(pucContent, (VOS_CHAR)0xff, MN_MSG_EFSMS_LEN);
    *pucContent = ucStatus;
    if (pstScAddr->ucBcdLen > 0)
    {
        *(pucContent + 1 ) = (pstScAddr->ucBcdLen + 1);
        *(pucContent + 2 ) = pstScAddr->addrType;
        PS_MEM_CPY(pucContent + 3,pstScAddr->aucBcdNum ,pstScAddr->ucBcdLen);
        ulWriteSet = 1 + pstScAddr->ucBcdLen + 2;
    }
    else
    {
        *(pucContent + 1 ) = 0;
        ulWriteSet = 1 + 1;
    }

    if (ulWriteSet >=  MN_MSG_EFSMS_LEN)
    {
        return;
    }
    if (pstRawData->ulLen > (MN_MSG_EFSMS_LEN - ulWriteSet))
    {
        PS_MEM_CPY(pucContent + ulWriteSet,pstRawData->aucData,MN_MSG_EFSMS_LEN - ulWriteSet);
    }
    else
    {
        PS_MEM_CPY(pucContent + ulWriteSet,pstRawData->aucData,pstRawData->ulLen);
    }
}

/*****************************************************************************
 函 数 名  : MSG_DecodeScAddress
 功能描述  : 根据RP-OA数据结构解码成对应的BCD码数据结构
             Refer to 24011 8.2.5.1
 输入参数  : RP层的地址，Refer to 24011 8.2.5.1
 输出参数  : pstAsciiAddr MN_MSG_ASCII_ADDR_STRU结构表示的地址
             pulLen RP-OA RP-DA等在消息中占用OCTET的个数
 返 回 值  : 解码结果 MN_ERR_NO_ERROR解码成功
                      其他           解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年09月26日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目

*****************************************************************************/
VOS_UINT32 MSG_DecodeScAddress(
    const VOS_UINT8                     *pucAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;

    if ((VOS_NULL_PTR == pucAddr)
     || (VOS_NULL_PTR == pstBcdAddr)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MSG_DecodeScAddress: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_MSG_DecodeAddress(pucAddr, VOS_TRUE, &stAsciiAddr, pulLen);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        pstBcdAddr->ucBcdLen = (VOS_UINT8)(stAsciiAddr.ulLen + 1)/2;
        /* 根据协议23040 9.1.2.5 地址类型域格式如下所示
            bit7   bit6    -   bit4             bit3    -   bit0
             1      type of number      Numbering-plan-identification */
        pstBcdAddr->addrType = 0x80;
        pstBcdAddr->addrType |= (stAsciiAddr.enNumPlan & 0x0f);
        pstBcdAddr->addrType |= (VOS_UINT8)((stAsciiAddr.enNumType << 4) & 0x70);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
        ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)stAsciiAddr.aucAsciiNum,
                                    pstBcdAddr->aucBcdNum,
                                    &pstBcdAddr->ucBcdLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MSG_GetTpduLen
 功能描述  : 获取短信/短信命令/短信状态报告的TPDU长度，不包含短信中心部分
 输入参数  : pstTsDataInfo   - 短信的TEXT格式数据结构指针
 输出参数  : pulLen:短信/短信命令/短信状态报告的TPDU长度
 返 回 值  : MN_ERR_NO_ERROR:获取成功
             其他:获取失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年03月22日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MSG_GetTpduLen(
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    VOS_UINT32                          *pulLen
)
{
    MN_MSG_RAW_TS_DATA_STRU             *pstTmpRawData;
    VOS_UINT32                          ulRet;

    pstTmpRawData = (MN_MSG_RAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MSG_RAW_TS_DATA_STRU));
    if (VOS_NULL_PTR == pstTmpRawData)
    {
        MN_ERR_LOG("MSG_GetTpduLen: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstTmpRawData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_GetTpduLen: Fail to encode msg.");
    }
    else
    {
        *pulLen = pstTmpRawData->ulLen;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpRawData);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_ParseEFSmContent
 功能描述  : 将短信格式为USIM卡中EFSMS的格式解析为SCAddr和TPDU
 输入参数  : pucContent:短信内容,USIM卡中EFSMS的格式
 输出参数  : pstScAddr:短信中心的地址
             pstRawData:TPDU的内容
             ucStatus:短信的状态
 返 回 值  : MN_ERR_NO_ERROR:解析成功
             其他:解析失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_ParseEFSmContent(
    const VOS_UINT8                     *pucContent,
    MN_MSG_BCD_ADDR_STRU                *pstScAddr,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData,
    VOS_UINT8                           *pucStatus
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulScaLen;
    VOS_UINT8                           ucFo;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    VOS_UINT8                           ucSmStatus;
    MN_MSG_TPDU_TYPE_ENUM_U8            aucMtiMapTpduType[4] = {MN_MSG_TPDU_DELIVER,
                                                                MN_MSG_TPDU_SUBMIT,
                                                                MN_MSG_TPDU_COMMAND,
                                                                MN_MSG_TPDU_MAX};

    *pucStatus = *pucContent;
    if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
    {
        return MN_ERR_CLASS_SMS_EMPTY_REC;
    }
    ulRet = MSG_DecodeScAddress((pucContent + 1), pstScAddr, &ulScaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: invalid SC address.");
        return ulRet;
    }

    ucFo = *(pucContent + (1 + ulScaLen));
    pstRawData->enTpduType = aucMtiMapTpduType[(ucFo & 0x03)];
    if (MN_MSG_TPDU_COMMAND == pstRawData->enTpduType)
    {
         /*短信命令和短信状态报告的TP-MTI均为4，这里通过SMS的发送状态来确认是否为短信状态报告*/
         ucSmStatus = ((*pucStatus)& EF_SMS_STATUS_MO_SEND_TO_NT);
         if (EF_SMS_STATUS_MO_SEND_TO_NT != ucSmStatus)
         {
            pstRawData->enTpduType = MN_MSG_TPDU_STARPT;
         }
    }

    if (MN_MSG_TPDU_MAX == pstRawData->enTpduType)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: invalid TPDU type.");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    pstRawData->ulLen = MN_MSG_EFSMS_LEN - (1 + ulScaLen);
    PS_MEM_CPY(pstRawData->aucData,
               (pucContent + (1 + ulScaLen)),
               pstRawData->ulLen);

    while (0 != pstRawData->ulLen)
    {
        if (MN_MSG_USIM_FILL_BYTE == pstRawData->aucData[pstRawData->ulLen - 1])
        {
            pstRawData->ulLen--;
        }
        else
        {
            break;
        }
    }

    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        MN_ERR_LOG("MN_MSG_ParseEFSmContent: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    ulRet = MN_MSG_Decode(pstRawData, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: Fail to decode message.");
        return ulRet;
    }

    /*获取消息的真实长度截取冗余字段*/
    ulRet = MSG_GetTpduLen(pstTsDataInfo, &pstRawData->ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: Fail to get message length.");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
    return ulRet;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetAppStatus
 功能描述  : 根据USIM卡中的短信状态获取对APP提供的短信状态
 输入参数  : ucStatus:USIM卡的短信状态
 输出参数  : penStatus:APP的短信状态

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetAppStatus(
    VOS_UINT8                           ucStatus,
    MN_MSG_STATUS_TYPE_ENUM_U8          *penStatus
)
{
    if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & 0x07))
    {
        *penStatus = MN_MSG_STATUS_MO_NOT_SENT;
    }
    else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & 0x05))
    {
        *penStatus = MN_MSG_STATUS_MO_SENT;
    }
    else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & 0x03))
    {
        *penStatus = MN_MSG_STATUS_MT_NOT_READ;
    }
    else if (EF_SMS_STATUS_MT_READ == (ucStatus & 0x01))
    {
        *penStatus = MN_MSG_STATUS_MT_READ;
    }
    else
    {
        *penStatus = MN_MSG_STATUS_MAX;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetPsStatus
 功能描述  : 根据APP提供的短信状态获取USIM卡中的短信状态
 输入参数  : enStatus:APP的短信状态
 输出参数  : pucStatus:USIM卡的短信状态

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetPsStatus(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    VOS_UINT8                           *pucStatus
)
{
    if (MN_MSG_STATUS_MT_READ == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MT_READ;
    }
    else if (MN_MSG_STATUS_MT_NOT_READ == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MT_TO_BE_READ;
    }
    else if (MN_MSG_STATUS_MO_NOT_SENT == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MO_TO_BE_SEND;
    }
    else if (MN_MSG_STATUS_MO_SENT == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MO_SEND_TO_NT;
    }
    else
    {
        *pucStatus = EF_SMS_STATUS_FREE_SPACE;
    }
}

/*****************************************************************************
 函 数 名  : MSG_BuildDeliverEvtParm
 功能描述  : 构造Deliver事件上报的结构
 输入参数  : pstCfgParm:短信当前的接收路径
             pstScAddr:短信中心地址
             pstRawData:短信的TPDU的值
 输出参数  : pstDeliverEvt:Deliver事件上报的结构

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MSG_BuildDeliverEvtParm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_EVT_INFO_STRU        *pstDeliverEvt
)
{
    PS_MEM_SET(pstDeliverEvt,0X00,sizeof(MN_MSG_DELIVER_EVT_INFO_STRU));
    PS_MEM_CPY(&pstDeliverEvt->stRcvMsgInfo.stScAddr,
               pstScAddr,
               sizeof(pstDeliverEvt->stRcvMsgInfo.stScAddr));
    PS_MEM_CPY(&pstDeliverEvt->stRcvMsgInfo.stTsRawData,
               pstRawData,
               sizeof(pstDeliverEvt->stRcvMsgInfo.stTsRawData));
    pstDeliverEvt->enMemStore = pstCfgParm->enSmMemStore;
    pstDeliverEvt->enRcvSmAct = pstCfgParm->enRcvSmAct;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetBCopId
 功能描述  : 广播上报时,获取OPID的值
 输入参数  : 无
 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_OPERATION_ID_T  MN_MSG_GetBCopId(VOS_VOID)
{
    return f_tMsgOpId++;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateNeedSendUsim
 功能描述  : 更新需要发送到USIM的结构
 输入参数  : ulInedx - 需要更新的发往USIM的结构
 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateNeedSendUsim(
    VOS_UINT32                          ulInedx,
    VOS_BOOL                            bUpdateStatus
)
{
    if (ulInedx >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
    {
        return;
    }
    f_bNeedSendUsim[ulInedx] = bUpdateStatus;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetNeedSendUsim
 功能描述  : 更新需要发送到USIM的结构
 输入参数  : 无
 输出参数  : pulRealRec - 当前实际的短信容量
             pbNeedSendUsim - 是否需要通知USIM修改短信状态
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetNeedSendUsim(
    VOS_UINT32                          *pulRealRec,
    VOS_BOOL                            *pbNeedSendUsim
)
{
    *pulRealRec = f_stMsgEfSmsInfo.ucSmsRealRecNum;
    PS_MEM_CPY(pbNeedSendUsim,f_bNeedSendUsim,sizeof(VOS_BOOL)*MN_MSG_MAX_USIM_SMS_NUM);
}

/***********************************************************************
函 数 名  : MN_MSG_CheckMemFull
功能描述  : 判断短信存储空间是否满
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_TRUE      存储空间满
            其他        存储空间未满
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : f62575
    修改内容   : DTS2012111201995 新生成函数
  2.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
************************************************************************/
LOCAL VOS_UINT32 MN_MSG_CheckMemFull(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bUnavailableFlag;
    VOS_BOOL                            bSmUnavailableFlag;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;

    MN_INFO_LOG("MN_MSG_CheckMemFull: step into function.");

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    /* 获取用户的短信接收存储配置 */
    MN_MSG_GetCurCfgParm(&stCfgParm);

    /* 若用户配置的短信存储方式为非MODEM存储，则检查APP短信接收功能是否可用 */
    if (MN_MSG_RCVMSG_ACT_STORE != stCfgParm.enRcvSmAct)
    {
        ulRet = MN_MSG_AppStorageUnavailable(stCfgParm.enRcvSmAct,
                                            stCfgParm.enAppMemStatus,
                                            &bUnavailableFlag);
    }
    /* 若用户配置的短信存储方式为MODEM存储，则检查用户设置的存储介质是否可用 */
    else
    {
        ulRet = MN_MSG_UeStorageUnavailable(stCfgParm.enSmMemStore, &bUnavailableFlag);
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    ulRet = MN_MSG_UeStorageUnavailable(MN_MSG_MEM_STORE_SIM, &bSmUnavailableFlag);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    /* 仅当用户指定存储空间满且(U)SIM卡满情况下返回短信存储空间满 */
    if ((VOS_TRUE == bUnavailableFlag)
     && (VOS_TRUE == bSmUnavailableFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
*  Prototype       : MN_MSG_FailToWriteEfsms
*  Description     : 接收网络过来的短信写SIM卡的EFSMS文件失败后,MS按协议要求回复网络RP-ERROR并修改EFSMSS文件；
*  Input           : enMemStore  --- 发生存储失败的存储介质类型
                     ucFailCause --- 当前存储失败的原因
                        存储区满；
                        存储区不可用；
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-04-12
*     Author       : 傅映君
*     Modification : Created function
   2.日    期   : 2011年3月21日
     作    者   : 傅映君/f62575
     修改内容   : DTS2011031800199，短信溢出存储介质总是SM，没有对ME存储溢出显示问题
   3.日    期   : 2012年11月08日
     作    者   : f62575
     修改内容   : DTS2012111201995 ： 删除参数ucClassType，错误原因值更新；
   4.日    期   : 2012年12月08日
     作    者   : f62575
     修改内容   : DTS2012120608883 ： USIM卡存储区满时收短信DCM分支也要修改EFSMSS的溢出标志
*****************************************************************************/
VOS_VOID MN_MSG_FailToWriteEfsms(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enFailCause
)
{
    VOS_UINT32                          ulRet;
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8      enMtCustomize;

    /* 根据协议51010 34.2.5.3 SIM卡存储短信异常回复错误原因值9240，UE处理同
       SM存储区满 */
    if ((MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL != enFailCause)
     && (MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM != enFailCause))
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        return;
    }

    /* 此处是否需要判断待确认 */
    if (MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL == enFailCause)
    {
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportMemExceed(bcOpId, enMemStore);
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        enTpCause = MN_MSG_TP_CAUSE_SIM_FULL;
    }
    else
    {
        enTpCause = MN_MSG_TP_CAUSE_MEMORY_FULL;
    }

     /*The MS shall return a "protocol error, unspecified" error message
    (see 3GPP TS 24.011 [6]) if the short message cannot be stored in the
    (U)SIM and there is other short message storage available at the MS.
    If all the short message storage at the MS is already in use, the MS
    shall return "memory capacity exceeded". */
    ulRet = MN_MSG_CheckMemFull();
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_MEMORY_EXCEEDED,
                                enTpCause);

        MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

    }
    else
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                enTpCause);

        enMtCustomize       = MN_MSG_MT_CUSTOMIZE_NONE;
        MN_MSG_GetMtCustomizeInfo(&enMtCustomize);
        if (MN_MSG_MT_CUSTOMIZE_DCM == enMtCustomize)
        {
            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);
        }
    }

    return;
}

/*****************************************************************************
*  Prototype       : MN_MSG_UpdateSendFailFlag
*  Description     : 更新当前发送失败的域
*  Input           : enSendFailFlag --- 当前发送失败的域;
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 VOS_VOID MN_MSG_UpdateSendFailFlag(
    MN_MSG_SEND_FAIL_FLAG_U8            enSendFailFlag
)
{
    f_enMsgSendFailFlag = enSendFailFlag;
}

/*****************************************************************************
*  Prototype       : MN_MSG_GetSendFailFlag
*  Description     : 获取当前发送失败的域
*  Input           : 无;
*  Output          :
*  Return Value    : 当前发送失败的域
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 MN_MSG_SEND_FAIL_FLAG_U8 MN_MSG_GetSendFailFlag(VOS_VOID)
{
    return f_enMsgSendFailFlag;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetRetryPeriod
 功能描述  : 获取当前短信重发时间周期和时间间隔
 输入参数  : 无
 输出参数  :  当前短信重发时间周期
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年01月04日
    作    者   : f62575
    修改内容   : DTS2013010400027, 支持GCF测试流程自动识别
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
VOS_VOID MN_MSG_GetRetryInfo(
    MN_MSG_RETRY_INFO_STRU              *pstRetryInfo
)
{
    VOS_UINT32                          bTestCard;

#if ( VOS_WIN32 == VOS_OS_VER )
    if (0 != g_ucDisableMoRetry)
    {
        PS_MEM_SET(pstRetryInfo, 0x00, sizeof(f_stMsgRetryInfo));
        return;
    }
#endif

    bTestCard = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == bTestCard)
    {
        PS_MEM_SET(pstRetryInfo, 0x00, sizeof(f_stMsgRetryInfo));
    }
    else
    {
        PS_MEM_CPY(pstRetryInfo, &f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SaveRpErrInfo
 功能描述  : 保存最近一次网侧过来的rP-Error消息,定时器超时后无可用域时,取此消息上报
 输入参数  : ucDataLen:网侧过来的数据长度
             pucData:网侧过来的数据
 输出参数  :  无
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : f62575
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID MN_MSG_SaveRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg)
{
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    PS_MEM_CPY(&f_stMsgRpErrInfo, pstMsg, sizeof(f_stMsgRpErrInfo));
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetRpErrInfo
 功能描述  : 获取最近一次网侧过来的rP-Error消息,定时器超时后无可用域时,取此消息上报
 输入参数  : 无
 输出参数  : pstRpErrInfo:最近一次网侧过来的数据信息
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年07月11日
    作    者   : f62575
    修改内容   : V9R1 STK升级项目
*****************************************************************************/
VOS_VOID MN_MSG_GetRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstRpErrInfo)
{
    PS_MEM_CPY(pstRpErrInfo,&f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetClass0Tailor
 功能描述  : 获取Class0短信实现方式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :Class0短信实现方式

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年01月04日
    作    者   : f62575
    修改内容   : DTS2013010400027, 支持GCF测试流程自动识别
  3.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
MN_MSG_CLASS0_TAILOR_U8 MN_MSG_GetClass0Tailor(VOS_VOID)
{
    VOS_UINT32                          bTestCard;

    bTestCard = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == bTestCard)
    {
        return MN_MSG_CLASS0_VIVO;
    }
    else
    {
        return g_enMsgClass0Tailor;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_SetClass0Tailor
 功能描述  : 设置Class0短信实现方式
 输入参数  : enClass0Tailor Class0短信实现方式
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月31日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor)
{
    g_enMsgClass0Tailor = enClass0Tailor;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetRealPrefSendDomain
 功能描述  : 获取当前实际的优先发送域
 输入参数  : enHopeDomain:当前的实际发送域
             enHopeDomain:当前期望的优先发送域
 输出参数  : 无
 返 回 值  :当前实际的优先发送域

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数

当前如果支持CS+PS域发送短信,如果CS域发送失败,则下次发送短信时优先从PS域发送,反之
亦然,此时实际的优先发送域时PS域优先发送
*****************************************************************************/
MN_MSG_SEND_DOMAIN_ENUM_U8  MN_MSG_GetRealPrefSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeDomain
)
{
    if (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeDomain)
    {
        if (MN_MSG_SEND_DOMAIN_PS == enSendDomain)
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        else
        {
            return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        }
    }


    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeDomain)
    {
        if (MN_MSG_SEND_DOMAIN_PS == enSendDomain)
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        else
        {
            return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        }
    }

    return enHopeDomain;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtTpPidAndDcs
 功能描述  : 获取当前接收到短信的TP-PID和TP-DCS
 输入参数  : 无
 输出参数  : MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid 当前接收到短信的TP-PID
             MN_MSG_DCS_CODE_STRU                *pstDcs 当前接收到短信的TP-DCS解析获得的DCS结构
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_GetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid,
    MN_MSG_DCS_CODE_STRU                *pstDcs
)
{
    *penPid = f_stMsgMtEntity.enPid;
    PS_MEM_CPY(pstDcs, &f_stMsgMtEntity.stDcs, sizeof(f_stMsgMtEntity.stDcs));
}

/*****************************************************************************
 函 数 名  : MN_MSG_SetMtTpPidAndDcs
 功能描述  : 保存当前接收到短信的TP-PID和TP-DCS到短信接收实体
 输入参数  : 无
 输出参数  : MN_MSG_TP_PID_TYPE_ENUM_U8          enPid 当前接收到短信的TP-PID
             MN_MSG_DCS_CODE_STRU                stDcs 当前接收到短信的TP-DCS解析获得的DCS结构
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_SetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_DCS_CODE_STRU                stDcs
)
{
    f_stMsgMtEntity.enPid = enPid;
    PS_MEM_CPY(&f_stMsgMtEntity.stDcs, &stDcs, sizeof(f_stMsgMtEntity.stDcs));
}

/*****************************************************************************
 函 数 名  : MSG_UpdateUsimForList
 功能描述  : LIST短信时需更新USIM中短信状态
 输入参数  : clientId     -   上报客户端口号
             ucChangeNum  -   需更改个数
             enMemStore   -   当前存储器
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MSG_UpdateUsimForList(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT8                           ucChangeNum,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            MN_OPERATION_ID_T                   bcOpId;
#endif

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_LIST,ucChangeNum);
    }
    else
    {
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        /*广播上报NVIM中短信已发生了改变*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
#endif
    }
}

/*lint -e438 -e830*/

/*****************************************************************************
 函 数 名  : MN_MSG_RptMsg
 功能描述  : 上报短信内容给APP模块
 输入参数  : clientId         - 上报Client
             opId             - 上报OpId
             ucListStatus     - 列表状态
             ulLeftReportNum  - 剩余上报个数
             pstList           - 列表条件
             pstListRptEvt     - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年9月27日
     作    者   : w00167002
     修改内容   : DTS2013092100149:删除C核TASKDELAY处理，在V9低功耗时，会导致
                   TASKDELAY后未被唤醒，导致AT消息没有回复。
                   删除定时器TI_MN_MSG_LIST_WAIT_APP_READY 修改为AT手动上报后
                   同时做SMS再上报剩余的SMS.
*****************************************************************************/
VOS_VOID MN_MSG_RptMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList,
    MN_MSG_LIST_EVT_INFO_STRU           *pstListRptEvt
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucEventNum  = 0;
    VOS_UINT32                          ulCapality;
    static VOS_UINT32                   ulBeginIdx = 0;
    VOS_UINT8                           ucListStatus;
    static VOS_UINT8                    ucChangeNum = 0;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    /* 获取需列表短信状态 */
    ucListStatus = EF_SMS_STATUS_FREE_SPACE;
    if (MN_MSG_STATUS_NONE != pstList->enStatus)
    {
        MN_MSG_GetPsStatus(pstList->enStatus, &ucListStatus);
    }

    ulCapality = MN_MSG_GetSmCapacity(pstList->enMemStore);

    PS_MEM_CPY( &(pstListRptEvt->stReceivedListPara), pstList, sizeof(MN_MSG_LIST_PARM_STRU) );

    /* 遍历需上报短信,达到列表上限后启动定时器退出 */
    for (; ulBeginIdx < ulCapality; ulBeginIdx++)
    {
        ulRet = MN_MSG_GetStatus(pstList->enMemStore,ulBeginIdx,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }

        if ((MN_MSG_STATUS_NONE == pstList->enStatus)
         || (ucListStatus == ucStatus))
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_ReadSmsInfo(pstList->enMemStore,ulBeginIdx,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                pstListRptEvt->bSuccess = VOS_FALSE;
                pstListRptEvt->ulReportNum = ucEventNum;
                pstListRptEvt->bLastListEvt = VOS_TRUE;
                pstListRptEvt->ulFailCause = ulRet;
                MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
                break;
            }
            ulRet = MN_MSG_ParseEFSmContent(aucSmContent,
                                            &pstListRptEvt->astSmInfo[ucEventNum].stMsgInfo.stScAddr,
                                            &pstListRptEvt->astSmInfo[ucEventNum].stMsgInfo.stTsRawData,
                                            &ucStatus);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                pstListRptEvt->bSuccess = VOS_FALSE;
                pstListRptEvt->bLastListEvt = VOS_TRUE;
                pstListRptEvt->ulReportNum = ucEventNum;
                pstListRptEvt->ulFailCause = ulRet;
                MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
                break;
            }
            MN_MSG_GetAppStatus(ucStatus,&pstListRptEvt->astSmInfo[ucEventNum].enStatus);
            pstListRptEvt->astSmInfo[ucEventNum].ulIndex = ulBeginIdx;
            ucEventNum++;

            if ((VOS_TRUE == pstList->bChangeFlag)
             && (EF_SMS_STATUS_MT_TO_BE_READ == ucStatus))
            {
                ulRet = MSG_ChangeSmStatus(pstList->enMemStore,
                                           clientId,
                                           opId,
                                           MN_MSG_USIM_LIST,
                                           ulBeginIdx,
                                           aucSmContent,
                                           &ucChangeNum);

                if (MN_ERR_NO_ERROR == ulRet )
                {
                    ucChangeNum++;
                }
            }
        }

        if ((ulLeftReportNum != ucEventNum)
         && (MN_MSG_MAX_REPORT_EVENT_NUM != ucEventNum))
        {
            continue;
        }

        /* 列表短信完成后直接上报,否则启动定时器等待定时器超时后上报 */
        if (ulLeftReportNum == ucEventNum)
        {
            pstListRptEvt->bSuccess = VOS_TRUE;
            pstListRptEvt->bLastListEvt = VOS_TRUE;
            pstListRptEvt->ulReportNum = ulLeftReportNum;
            ulBeginIdx = 0;
            MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
            if (ucChangeNum > 0)
            {
                /* 更新USIM文件中短信状态 */
                if (MN_MSG_MEM_STORE_SIM == pstList->enMemStore)
                {
                    MSG_UpdateUsimForList(clientId,ucChangeNum,pstList->enMemStore);
                }
                #if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
                else if (MN_MSG_MEM_STORE_NV == pstList->enMemStore)
                {
                    /*广播上报NVIM中短信已发生了改变*/
                    bcOpId = MN_MSG_GetBCopId();
                    MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
                }
                #endif
                else
                {
                }
            }
            ucChangeNum = 0;
        }
        else
        {
            pstListRptEvt->bSuccess = VOS_TRUE;
            pstListRptEvt->bLastListEvt = VOS_FALSE;
            pstListRptEvt->ulReportNum = MN_MSG_MAX_REPORT_EVENT_NUM;
            ulLeftReportNum = ulLeftReportNum - MN_MSG_MAX_REPORT_EVENT_NUM;
            ucEventNum = 0;
            /* 此处+1的原语为,该index短信已被列表,需列表下一条短信 */
            ulBeginIdx++;
            MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);


            MN_MSG_UpdateListInfo(clientId,opId,ulLeftReportNum,pstList);
        }
        break;
    }

}
/*lint +e438 +e830*/

/*****************************************************************************
 函 数 名  : MN_MSG_InitRcvPath
 功能描述  : 初始化短信接收路径
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年4月29日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_MSG_InitRcvPath( VOS_VOID )
{
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_RCVMSG_PATH_EVT_INFO_STRU    stRcvPathEvt;

    f_stMsgCfgParm.enRcvSmAct       = MN_MSG_RCVMSG_ACT_STORE;
    f_stMsgCfgParm.enSmMemStore     = MN_MSG_MEM_STORE_SIM;
    f_stMsgCfgParm.enRcvStaRptAct   = MN_MSG_RCVMSG_ACT_STORE;
    f_stMsgCfgParm.enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
    f_stMsgCfgParm.enCbmMemStore    = MN_MSG_MEM_STORE_NONE;

    stRcvPathEvt.enRcvSmAct         = f_stMsgCfgParm.enRcvSmAct;
    stRcvPathEvt.enSmMemStore       = f_stMsgCfgParm.enSmMemStore;
    stRcvPathEvt.enRcvStaRptAct     = f_stMsgCfgParm.enRcvStaRptAct;
    stRcvPathEvt.enStaRptMemStore   = f_stMsgCfgParm.enStaRptMemStore;
    stRcvPathEvt.enCbmMemStore      = f_stMsgCfgParm.enCbmMemStore;

    bcOpId = MN_MSG_GetBCopId();
    MN_MSG_ReportRcvPathEvent(MN_CLIENT_ALL, bcOpId, VOS_TRUE, &stRcvPathEvt, MN_MSG_EVT_RCVMSG_PATH_CHANGED);

}

/*****************************************************************************
 函 数 名  : MN_MSG_OutputSmsMoFailureInfo
 功能描述  : 短信发送相关信息导出到异常事件记录
 输入参数  : TAF_MSG_ERROR_ENUM_UINT32 enErrorCode RP-ERROR的错误原因
 输出参数  : NAS_MNTN_SMS_MO_INFO_STRU          *pstSmsMo
                                 短信发送失败的直接相关信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月9日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级

*****************************************************************************/
VOS_VOID MN_MSG_OutputSmsMoFailureInfo(
    TAF_MSG_ERROR_ENUM_UINT32           enErrorCode,
    NAS_MNTN_SMS_MO_INFO_STRU          *pstSmsMo
)
{
    /* 获取短信发送相关的服务数据 */
    pstSmsMo->stUstInfo.bEfSmssFlag     = f_stEfUstInfo.bEfSmssFlag;
    pstSmsMo->stUstInfo.bEfSmsFlag      = f_stEfUstInfo.bEfSmsFlag;
    pstSmsMo->stUstInfo.bEfSmsrFlag     = f_stEfUstInfo.bEfSmsrFlag;
    pstSmsMo->stUstInfo.bEfSmspFlag     = f_stEfUstInfo.bEfSmspFlag;
    pstSmsMo->stUstInfo.bMoSmsCtrlFlag  = f_stEfUstInfo.bMoSmsCtrlFlag;

    /* 获取短信模块初始化状态数据 */
    PS_MEM_CPY(&pstSmsMo->stMsgStatus,
               &f_stMsgUsimStatusInfo,
               sizeof(pstSmsMo->stMsgStatus));

    /* 获取目的号码和短信中心号码 */
    MN_MSG_GetAddressFromSubmit(f_stMsgMoEntity.aucRpDataInfo,
                                f_stMsgMoEntity.ucRpDataLen,
                                &pstSmsMo->stScAddr,
                                &pstSmsMo->stDestAddr);

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstSmsMo->ulMoFailCause = enErrorCode;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReadMsgInFlashByIndex
 功能描述  : 按索引读取Flash的一条短消息
 输入参数  : VOS_UINT32   ulIndex 索引值
 输出参数  : VOS_UINT8    *pucSmContent 读取的Buffer

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年01月24日
    作    者   : 王毛/W00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_ReadMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
)
{
    FILE                                	*fp;
    VOS_INT32                           lRst;
    VOS_UINT32                          ulFileSize;

    /*判断短信文件是否打开*/
    if(VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_WARN_LOG("MN_MSG_ReadFlashByIndex: SmsFile Not Exit.\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_NOTEXIST_FILE;
    }

    fp = gfpSmsFlash;

    /*获取文件大小*/
    lRst = (VOS_INT32)MN_GetFileSize(fp,&ulFileSize);
    if(MN_ERR_NO_ERROR != lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Get File Size error\n");
        return (VOS_UINT32)lRst;
    }

    if (((ulIndex + 1) * MN_MSG_EFSMS_LEN) > ulFileSize)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Para error.\n");
        return MN_ERR_INVALIDPARM;
    }

    /*定位到索引位置*/
    lRst = mdrv_file_seek(fp, (VOS_INT32)(ulIndex * MN_MSG_EFSMS_LEN), SEEK_SET);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*读文件*/
    /* 低软接口修改，调整了参数 */
    lRst = mdrv_file_read(pucSmContent, MN_MSG_EFSMS_LEN, 1, fp);
    if ((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:read error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_READ_FILE;
    }

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 函 数 名  : MN_MSG_WriteMsgInFlashByIndex
 功能描述  : 按索引向Flash写一条短消息
 输入参数  : VOS_UINT32   ulIndex 索引值
 输出参数  : VOS_UINT8    *pucSmContent 要写入短信的Buffer

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年01月24日
    作    者   : 王毛/W00166186
    修改内容   : 新生成函数
  2.日    期   : 2014年03月04日
    作    者   : f62575
    修改内容   : DTS2013091009786 支持通过产品形态和版本区分FLASH文件根目录
*****************************************************************************/
VOS_UINT32 MN_MSG_WriteMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
)
{
    FILE                                *fp;
    VOS_INT32                           lRst;
    VOS_UINT32                          ulFileSize;

    /*如果短信文件不存在，需要创建该文件*/
    if(VOS_NULL_PTR == gfpSmsFlash)
    {
        /*创建文件*/
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"wb+");
        if (VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Create SmsFile Fail.\n");
            return MN_ERR_CLASS_SMS_FLASH_MEM_CREATE_FILE;
        }

        /*读写方式打开文件*/
        (VOS_VOID)mdrv_file_close(gfpSmsFlash);
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
        if (VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Open SmsFile Fail.\n");
            return MN_ERR_CLASS_SMS_FLASH_MEM_OPEN_FILE;
        }
    }

    fp = gfpSmsFlash;

    /*获取文件大小*/
    lRst = (VOS_INT32)MN_GetFileSize(fp,&ulFileSize);
    if(MN_ERR_NO_ERROR != lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Get File Size error\n");
        return (VOS_UINT32)lRst;
    }

    if ((ulIndex*MN_MSG_EFSMS_LEN) > ulFileSize)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Para error.\n");
        return MN_ERR_INVALIDPARM;
    }

    /*定位到索引位置*/
    lRst = mdrv_file_seek(fp,(VOS_INT32)(ulIndex*MN_MSG_EFSMS_LEN),SEEK_SET);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*写文件*/
    /* 低软接口修改，调整了参数 */
    lRst = mdrv_file_write(pucSmContent, MN_MSG_EFSMS_LEN, 1, fp);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:write error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_WRITE_FILE;
    }

    (VOS_VOID)mdrv_file_close(gfpSmsFlash);

    gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Open SmsFile Fail.\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_OPEN_FILE;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetSmsServicePara
 功能描述  : 获取短信业务参数
 输入参数  : 无
 输出参数  : MN_MSG_CONFIG_PARM_STRU  *pstMsgCfgParm  短信业务参数
             MN_MSG_ME_STORAGE_STATUS_UINT8     *penMeStorageEnable ME使能状态
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2011年3月21日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011031800199，支持ME短信容量可配置
  3.日    期   : 2011年6月16日
    作    者   : 傅映君/f62575
    修改内容   : 问题单号DTS2011062201273 MO SMS CONTROL
  4.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  5.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID MN_MSG_GetSmsServicePara(
    MN_MSG_CONFIG_PARM_STRU             *pstMsgCfgParm,
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 *penMeStorageEnable
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsSrvParam;
    /* 短信接收存储介质保存在NV配置文件的使能标志
       VOS_TRUE        短信接收存储介质保存在NV配置文件
       VOS_FALSE       短信接收存储介质不保存在NV配置文件，每次上电后恢复为SM存储 */
    VOS_BOOL                            bSmMemEnable;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;

    MN_MSG_NVIM_MO_SMS_CTRL_STRU        stMnMsgSrvPara;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));
    PS_MEM_SET(&stMnMsgSrvPara, 0x00, sizeof(MN_MSG_NVIM_MO_SMS_CTRL_STRU));

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_BUTT;
    stMeStorageParm.usMeStorageNum    = 0;


    MN_MSG_InitSmsServiceData(pstMsgCfgParm);
    *penMeStorageEnable = MN_MSG_ME_STORAGE_DISABLE;

    ulRet = NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara:Read Service Parm From Nvim Failed");
        return;
    }

    pstMsgCfgParm->enAppMemStatus = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET];
    bSmMemEnable                  = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET];
    ulRet = NV_Read(en_NV_Item_Sms_Me_Storage_Info, &stMeStorageParm, sizeof(stMeStorageParm));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara: Read en_NV_Item_Sms_MeStorageEnable Failed");
        stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
        f_usMsgNvimSmsCurReNum = 0;
        return;
    }

    if (MN_MSG_ME_STORAGE_ENABLE == stMeStorageParm.enMeStorageStatus)
    {
        if (VOS_TRUE == bSmMemEnable)
        {
            pstMsgCfgParm->enSmMemStore = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET];
        }

        if (stMeStorageParm.usMeStorageNum > MN_MSG_MAX_NVIM_SMS_REC_NUM)
        {
            f_usMsgNvimSmsCurReNum = MN_MSG_MAX_NVIM_SMS_REC_NUM;
        }
        else
        {
            f_usMsgNvimSmsCurReNum = stMeStorageParm.usMeStorageNum;
        }
    }
    else
    {
        f_usMsgNvimSmsCurReNum = 0;
    }

    *penMeStorageEnable = stMeStorageParm.enMeStorageStatus;

    (VOS_VOID)NV_GetLength(en_NV_Item_MO_SMS_CONTROL_FEATURE, &ulLength);
    ulRet = NV_Read(en_NV_Item_MO_SMS_CONTROL_FEATURE, &stMnMsgSrvPara, ulLength);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara:Read MO_SMS_CONTROL_FEATURE From Nvim Failed");
        f_stMsgMoSmsCtrlInfo.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;
    }

    PS_MEM_CPY(&f_stMsgMoSmsCtrlInfo, &stMnMsgSrvPara, sizeof(MN_MSG_NVIM_MO_SMS_CTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoSmsCtrlFlag
 功能描述  : 获取MO SMS CONTROL特性的激活标志
 输入参数  : 无
 输出参数  : VOS_UINT8 *pucMoSmsCtrlFlag  MO SMS CONTROL特性的激活标志
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月22日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MSG_GetMoSmsCtrlFlag(
    VOS_UINT8                           *pucMoSmsCtrlFlag
)
{
    *pucMoSmsCtrlFlag = f_stMsgMoSmsCtrlInfo.ucActFlg;
    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateMoSmsCtrlFlag
 功能描述  : 设置MO SMS CONTROL特性的激活标志
 输入参数  : 无
 输出参数  : VOS_UINT8 ucMoSmsCtrlFlag  MO SMS CONTROL特性的激活标志
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月22日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数 DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MSG_UpdateMoSmsCtrlFlag(
    VOS_UINT8                           ucMoSmsCtrlFlag
)
{
    f_stMsgMoSmsCtrlInfo.ucActFlg = ucMoSmsCtrlFlag;
    return;
}

/*****************************************************************************
 函 数 名  : MN_MGS_UpdateSmsCapability
 功能描述  : 更新SMS存储介质的容量
 输入参数  : MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore 存储介质类型
             VOS_UINT32                          ulNum        指定存储介质的容量
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MGS_UpdateSmsCapability(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_UINT32                          ulNum
)
{
    if (MN_MSG_MEM_STORE_SIM == enSmMemStore)
    {
        f_stMsgEfSmsInfo.ucSmsRealRecNum = (VOS_UINT8)ulNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enSmMemStore)
    {
        f_usMsgNvimSmsCurReNum = (VOS_UINT8)ulNum;
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetSpecificStatusMoEntity
 功能描述  : 获取指定状态的发送短息实体
 输入参数  : MN_MSG_MO_STATE_ENUM_U8             enMoStatus  要获取的短信实体状态
 输出参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity 待发送的短信实体
             VOS_BOOL                           *pbBufferEntity 是否缓存实体
             VOS_UINT32                         *pulIndex       缓存实体索引
 返回值    : VOS_UINT32
                MN_ERR_NO_ERROR                 找到了指定的发送短息实体
                其他，                          没有找到指定的发送短息实体
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_GetSpecificStatusMoEntity(
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus,
    VOS_BOOL                           *pbBufferEntity,
    VOS_UINT32                         *pulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
)
{
    VOS_UINT32                          ulTotal;
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    *pbBufferEntity = VOS_FALSE;
    *pulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_GetMoEntity(pstMoEntity);
    if (enMoStatus == pstMoEntity->enSmaMoState)
    {
        return MN_ERR_NO_ERROR;
    }

    ulTotal = MN_MSG_GetMoBufferCap();
    for(ulLoop = 0; ulLoop < ulTotal; ulLoop++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
        if (enMoStatus == pstMoBuffer->stMoInfo.enSmaMoState)
        {
            *pbBufferEntity = VOS_TRUE;
            *pulIndex       = ulLoop;
            PS_MEM_CPY(pstMoEntity, &pstMoBuffer->stMoInfo, sizeof(pstMoBuffer->stMoInfo));
            return MN_ERR_NO_ERROR;
        }
    }

    return MN_ERR_UNSPECIFIED;
}

/*****************************************************************************
 函 数 名  : MN_MSG_CreateMoEntity
 功能描述  : 更新发送短息实体状态
 输入参数  : VOS_BOOL                            bBufferEntity 是否缓存实体
             VOS_UINT32                          ulIndex       缓存实体索引
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity 待发送的短信实体
             VOS_UINT8                           aucEfSmContent[] 待发送的短信
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_UINT8                           aucEfSmContent[]
)
{
    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_CreateMoInfo(pstMoEntity);
        return;
    }

    MN_MSG_SaveStoreMsg(ulIndex, pstMoEntity, aucEfSmContent);
    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateSpecificMoEntityStatus
 功能描述  : 更新发送短息实体状态
 输入参数  : MN_MSG_MO_STATE_ENUM_U8             enMoStatus  短信实体状态
             VOS_BOOL                            bBufferEntity 是否缓存实体
             VOS_UINT32                          ulIndex       缓存实体索引
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateSpecificMoEntityStatus(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus
)
{
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_UpdateSmaMoState(enMoStatus);
        return;
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->stMoInfo.enSmaMoState = enMoStatus;
}

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateSpecificMoEntityStatus
 功能描述  : 清空发送短息实体状态
 输入参数  : VOS_BOOL                            bBufferEntity 是否缓存实体
             VOS_UINT32                          ulIndex       缓存实体索引
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_DestroySpecificMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex
)
{
    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_DestroyMoInfo();
        return;
    }

    MN_MSG_FreeStoreMsg(ulIndex);

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_InitMoBuffer
 功能描述  : 缓存发送短信实体初始化
 输入参数  : 无
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  3.日    期   : 2013年8月8日
    作    者   : y00245242
    修改内容   : 初始化stTotalMsg变量
*****************************************************************************/
VOS_VOID MN_MSG_InitMoBuffer(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    NAS_MN_NVIM_TOTAL_MSG_STRU          stTotalMsg;

    if (VOS_NULL_PTR != f_stMsgMoBuffer.pstMoBuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, f_stMsgMoBuffer.pstMoBuffer);
        f_stMsgMoBuffer.ulTotal = 0;
    }

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-8-8, begin */
    stTotalMsg.ulTotalMsg = 0;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-8-8, end */

    ulRet = NV_Read(en_NV_Item_NVIM_SMS_BUFFER_CAPABILITY,
                    &stTotalMsg,
                    sizeof(stTotalMsg));

    f_stMsgMoBuffer.ulTotal = stTotalMsg.ulTotalMsg;

    if (NV_OK != ulRet)
    {
        f_stMsgMoBuffer.ulTotal = 0;
    }

    if (0 == f_stMsgMoBuffer.ulTotal)
    {
        return;
    }

    f_stMsgMoBuffer.pstMoBuffer = (MN_MSG_STORE_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                            sizeof(MN_MSG_STORE_MSG_STRU) * f_stMsgMoBuffer.ulTotal);
    if (VOS_NULL_PTR == f_stMsgMoBuffer.pstMoBuffer)
    {
        f_stMsgMoBuffer.ulTotal = 0;
    }

    for (ulLoop = 0; ulLoop < f_stMsgMoBuffer.ulTotal; ulLoop++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
        PS_MEM_SET(pstMoBuffer, 0, sizeof(MN_MSG_STORE_MSG_STRU));
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoBufferCap
 功能描述  : 获取缓存发送短信实体容量
 输入参数  : 无
 输出参数  : 无
 返回值    : 缓存发送短信实体容量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_GetMoBufferCap(VOS_VOID)
{
    return f_stMsgMoBuffer.ulTotal;
}

/*****************************************************************************
 函 数 名  : TAF_MSG_SetUsimStatus
 功能描述  : 设置SIM卡状态
 输入参数  : SIM卡状态
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_SetUsimStatus(
    VOS_UINT8                           ucUsimStatus
)
{
    f_stMsgUsimStatusInfo.ucUsimStatus = ucUsimStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MSG_GetUsimStatus
 功能描述  : 获取SIM卡状态
 输入参数  : 无
 输出参数  : 无
 返回值    : SIM卡状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_MSG_GetUsimStatus(VOS_VOID)
{
    return f_stMsgUsimStatusInfo.ucUsimStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MSG_UpdateMtRcvDomain
 功能描述  : 接收短信时，更新MT实体的接收域
 输入参数  : 接收域 0:PS域；1:CS域
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_UpdateMtRcvDomain(
    VOS_UINT8                           ucRcvDomain
)
{
    if ( (MN_MSG_RCV_DOMAIN_CS != ucRcvDomain)
      && (MN_MSG_RCV_DOMAIN_PS != ucRcvDomain) )
    {
        f_stMsgMtEntity.enRcvDomain = MN_MSG_RCV_DOMAIN_BUTT;
    }
    else
    {
        f_stMsgMtEntity.enRcvDomain = ucRcvDomain;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MSG_GetMtRcvDomain
 功能描述  : 获取MT实体的接收域
 输入参数  : 无
 输出参数  : 无
 返回值    : 接收域 MN_MSG_RCV_DOMAIN_PS:PS域；MN_MSG_RCV_DOMAIN_CS:CS域
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
MN_MSG_RCV_DOMAIN_ENUM_U8 TAF_MSG_GetMtRcvDomain(VOS_VOID)
{
    return f_stMsgMtEntity.enRcvDomain;
}



/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

