#ifndef NSR_API_DEF_INCLUDED
#define NSR_API_DEF_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*ERRORCODE<错误码> added by 178934 2013-11-7*/
enum  enNSRErrorCode
{
    NSR_OK = 0,                                     /*<0>操作成功*/
    NSR_ERR,                                        /*<1>操作失败*/
    NSR_ERR_WRITE_QUEUE_FAIL,                       /*<2>写队列失败*/
    NSR_ERR_REINIT,                                 /*<3>重复初始化*/
    NSR_ERR_RESOURCE_UAAVAILABLE,                   /*<4>内存申请失败*/
    NSR_ERR_GET_I3_INDEX_ERROR,                     /*<5>NSR获取I3 Index失败*/
    NSR_ERR_GET_I3_JOIN_ERROR,                      /*<6>NSR获取I3 Join失败*/
    NSR_ERR_PARAMETER_ERROR,                        /*<7>参数错误*/
    NSR_ERR_SEND_BATCH_ERROR,                       /*<8>发送批量备份错误*/
    NSR_ERR_SEND_REALTIME_ERROR,                    /*<9>发送实时备份错误*/
    NSR_ERR_OSPF_NOT_EXIST,                         /*<10>OSPF进程不存在*/
    NSR_ERR_CB_TYPE_NOT_FOUND,                      /*<11>备份数据类型不存在*/
    NSR_ERR_OSPF_DATA_INIT_ERROR,                   /*<12>OSPF NSR数据初始化错误*/
    NSR_ERR_OSPF_REPL_INIT_ERROR,                   /*<13>OSPF NSR备份数据初始化错误*/
    NSR_ERR_GET_LSDB_TLV_ERROR,                     /*<14>获取备份的LSDB TLV错误*/
    NSR_ERR_INSERT_LSDB_ERROR,                      /*<15>LSDB入库错误*/
    NSR_ERR_REMOVE_LSDB_ERROR,                      /*<16>LSDB入库错误*/
    NSR_ERR_CAN_NOT_FIND_OSPF_ENT,                  /*<17>查找备份的OSPF进程错误*/
    NSR_ERR_RESTORE_IF_CB_NOT_FOUND,                /*<18>数据恢复时无法找到OSPF接口控制块*/
    NSR_ERR_RESTORE_REPL_IF_CB_ERROR,               /*<19>恢复备份的接口信息时错误*/
    NSR_ERR_RESTORE_IF_CB_ERROR,                    /*<20>备份恢复接口控制块时错误*/
    NSR_ERR_RESTORE_TYPE_NOT_FOUND,                 /*<21>备份恢复数据类型不存在*/
    NSR_ERR_RESTORE_ERROR,                          /*<22>备份恢复数据过程错误*/
    NSR_ERR_RESTORE_PERMANENT_NBR_CB_NOT_FOUND,     /*<23>数据恢复时无法找到OSPF配置邻居控制块*/
    NSR_ERR_RESTORE_DYNAMIC_NBR_CB_ALREADY_EXIST,   /*<24>数据恢复时无法找到OSPF动态控制块*/
    NSR_ERR_RESTORE_REPL_NBR_CB_ERROR,              /*<25>恢复备份的邻居信息时错误*/
    NSR_ERR_RESTORE_NBR_CB_ERROR,                   /*<26>备份恢复接口控制块时错误*/
    NBR_ERR_RESTORE_LSDB_AREA_NOT_FOUND,            /*<27>备份恢复LSA时区域不存在*/
    NBR_ERR_RESTORE_LSDB_CB_ERROR,                  /*<28>备份恢复LSA时错误*/
    NBR_ERR_RESTORE_LSDB_TO_IF_ERROR,               /*<29>备份恢复LSA到邻居时错误*/
    NBR_ERR_RESTORE_LSDB_TO_AREA_ERROR,             /*<30>备份恢复LSA到邻居时错误*/
    NSR_ERR_QUERY_INPUT_NULL,                       /*<31>查询接口入参为NULL*/
    NSR_ERR_OSPF_PROCESSID_OVERFLOW,                /*<32>ospf实例号超出最大值*/
    NSR_ERR_OSPF_PROCESS_NOT_FOUND,                 /*<33>找不到对应的ospf实例*/
    NSR_ERR_OSPF_IF_CB_NOT_FOUND,                   /*<34>找不到接口*/
    NSR_ERR_NO_OSPF_PROCESS_EXIT,                   /*<35>没有正在运行的ospf实例*/
    NSR_ERR_END_OF_TABLE,                           /*<36>已经查找到表项末尾 */
    NSR_ERR_AREA_FILTER_FLAG_INVALID,               /*<37>查询区域过滤条件标志不合法 */
    NSR_ERR_RESTORE_NBR_PARENT_IF_CONSISTENT,       /*<38>备份恢复邻居父接口地址冲突*/
    NSR_ERR_BACKUP_DATA_CHECK_ERROR,                /*<39>接收的备份数据检查出错*/
    NSR_ERR_NSR_ALREADY_BEEN_ENABLE,                /*<40>NSR功能已经使能*/
    NSR_ERR_NSR_ALREADY_BEEN_DISABLE,               /*<41>NSR功能已经去是能*/
    NSR_ERR_OSPF_PROCESSID_NOT_MATCH,               /*<42>输入的ospf进程号与查找到的不匹配*/
    NSR_ERR_CREATE_BACKUP_BEGIN_TIMER_FAIL,         /*<43>创建nsr备份开始定时器失败*/
    NSR_ERR_DELETE_BACKUP_BEGIN_TIMER_FAIL,         /*<44>创建nsr备份开始定时器失败*/
    NSR_ERR_CREATE_BACKUP_TIMER_FAIL,               /*<45>创建nsr备份定时器失败*/
    NSR_ERR_DELETE_BACKUP_TIMER_FAIL,               /*<46>创建nsr备份定时器失败*/
    NSR_ERR_BACKUP_MSG_TYPE_ERROR,                  /*<47>ospf发送的备份消息类型错误*/
    NSR_ERR_IF_BACKUP_DATA_ERROR,                   /*<48>slave收到if备份数据数据异常*/
    NSR_ERR_IF_BACKUP_MSG_TYPE_ERROR,               /*<49>slave收到if备份数据消息类型错误*/
    NSR_ERR_ALLOC_INIT_IF_CB_FAIL,                  /*<50>slave收到if备份数据，分配初始化if控制块失败*/
    NSR_ERR_IF_CB_NOT_EXIST,                        /*<51>if控制块不存在*/
    NSR_ERR_IF_BACKUP_DATA_LENGH_IS_ZERO,           /*<52>备份的接口消息数据长度为0*/
    NSR_ERR_IF_BACKUP_DATA_LENGH_IS_NOT_ZERO,       /*<53>备份的接口消息数据长度不为0*/
    NSR_ERR_IF_BACKUP_MSG_REP_OPERATION_ERROR,      /*<54>备份的接口消息操作类型错误*/
    NSR_ERR_BACKUP_MSG_DATA_LENGH_IS_ZERO,          /*<55>备份的接口消息操作类型错误*/
    NSR_ERR_BACKUP_NBR_KEY_ERROR,                   /*<56>备份的接口消息操作类型错误*/
    NSR_ERR_BACKUP_IF_KEY_ERROR,                    /*<57>备份的接口消息操作类型错误*/
    NSR_ERR_RESTORE_IF_ALREADY_UP,                  /*<58>数据恢复时无法找到OSPF接口控制块*/
    NSR_ERR_PARAMETER_IS_NULL,                      /*<59>参数为空*/
    NSR_ERR_SUB_MODULE_ALREADY_REGIST,              /*<60>NSR此模块已经注册*/
    NSR_ERR_NOT_SUPPORT_NSR,                        /*<61>NSR功能被裁减，当前不支持*/
    NSR_ERR_I3AGENT_NSR_OSPF_MSGSENDHOOK_IS_NULL,   /*<62>I3Agent注册的OSPF NSR消息处理函数为NULL*/
    NSR_ERR_NSR_NOT_INIT,                           /*<63>NSR未初始化*/
    NSR_ERR_NSR_OSPF_NOT_INIT,                      /*<64>NSR OSPF未初始化*/
    NSR_ERR_NSR_NOT_ENABLE,                         /*<65>NSR未使能*/
    NSR_ERR_NSR_CAPABILITY_IS_CONFLICT,             /*<66>NSR使能去使能状态冲突*/
    NSR_ERR_NSR_OSPF_CAPABILITY_IS_CONFLICT,        /*<67>NSR OSPF 使能去使能状态冲突*/
    NSR_ERR_NSR_OSPF_STATUS_NOT_EXPECTED,           /*<68>OSPF NSR处于非预期状态(使能NSR时已启动备份)*/
    NSR_ERR_GET_BASE_INFO_HOOK_NOT_REGIST,          /*<69>获取NSR基础信息的钩子未注册(该钩子由产品注册)*/
    NSR_ERR_SEND_BACKUP_MSG_HOOK_NOT_REGIST,        /*<70>NSR发送备份数据的钩子未注册(该钩子由产品注册)*/
    NSR_ERR_SEND_CONTROL_MSG_HOOK_NOT_REGIST        /*<71>NSR发送控制消息钩子未注册(该钩子由产品注册)*/
};

/*NSR控制类消息类型定义*/
#define NSR_CONTROL_MSG_BOARD            1     /*单板状态消息(主/备)*/
#define NSR_CONTROL_MSG_CHANNEL          2     /*备份通道消息(通道是否OK)*/
#define NSR_CONTROL_MSG_SLAVE_BOARD      3     /*备板状态消息(备板是否OK)*/
#define NSR_CONTROL_MSG_BACKUP           4     /*备份状态消息*/
#define NSR_CONTROL_MSG_RESTORE          5     /*备份恢复消息()*/
#define NSR_CONTROL_MSG_SMOOTH           6     /*平滑消息*/

/*NSR角色(主/备)*/
#define NSR_ROLE_NULL    0      /*NSR角色为初始状态*/
#define NSR_ROLE_MASTER  1      /*NSR角色为主*/
#define NSR_ROLE_SLAVE   2      /*NSR角色为备*/

/*NSR控制类操作结果定义*/
#define NSR_CONTROL_OK              0   /*成功*/
#define NSR_CONTROL_UNSUCCESS       1   /*失败*/

/*通道状态定义*/
#define NSR_CHANNEL_INACTIVE   0        /*通道有效*/
#define NSR_CHANNEL_ACTIVE     1        /*通道无效*/

/*备板状态定义*/
#define NSR_SLAVE_BOARD_INACTIVE   0    /*备板未激活*/
#define NSR_SLAVE_BOARD_ACTIVE     1    /*备板激活*/

/*备份状态定义*/
#define NSR_BACKUP_NULL                     0   /*备份命令字初始值*/
#define NSR_BACKUP_START                    1   /*备份开始*/
#define NSR_BACKUP_ERROR                    2   /*备份错误*/
#define NSR_BACKUP_OUT_OF_ORDER             3   /*备份乱序*/
#define NSR_BACKUP_TIMEOUT                  4   /*备份超时*/
#define NSR_BACKUP_FINISH                   5   /*备份结束*/
#define NSR_BACKUP_CANCEL                   6   /*取消备份*/
#define NSR_BACKUP_START_ACK                7   /*备板回复主板，收到主板发来的 backup start 消息*/
#define NSR_BACKUP_MAX                      8   /*备份命令字最大值*/

/*备份数据恢复通知定义*/
#define NSR_RESTORE_NULL        0   /*恢复命令字初始值*/
#define NSR_RESTORE_START       1   /*恢复开始*/
#define NSR_RESTORE_FINISH      2   /*恢复结束*/
#define NSR_RESTORE_MAX         3   /*恢复命令子最大值*/

/*NSR平滑通知定义*/
#define NSR_SMOOTH_NULL          0    /*平滑命令字初始值*/
#define NSR_SMOOTH_START         1    /*平滑开始*/
#define NSR_SMOOTH_FINISH        2    /*平滑结束*/
#define NSR_SMOOTH_MAX           3    /*平滑命令字最大值*/

/*NSR控制类消息接收目标定义(UCHAR的高两位分别代表Master和Slave)*/
#define NSR_CONTROL_MSG_DEST_MASTER     0x80    /*NSR控制类消息接收目标是 主*/
#define NSR_CONTROL_MSG_DEST_SLAVE      0x40    /*NSR控制类消息接收目标是 备*/

/*NSR控制类消息转交哪个模块处理*/
#define NSR_CONTROL_MSG_DIRECT_AGENT   0x01   /*NSR控制类消息接收目标是 产品*/
#define NSR_CONTROL_MSG_DIRECT_NSR     0x02   /*NSR控制类消息接收目标是 OSPF NSR 模块*/

#define NSR_CAPABILITY_NULL        0x0    /*NSR使能/去使能初始值*/
#define NSR_CAPABILITY_ENABLE      0x1    /*NSR使能*/
#define NSR_CAPABILITY_DISENABLE   0x2    /*NSR去使能*/

/*STRUCT<备份状态信息>*/
typedef struct nsr_backup_info
{
    USHORT usProcessID;      /*OSPF进程ID*/
    UCHAR ucBackupType;      /*数据备份标识信息*/
    UCHAR ucResult;          /*备份结果*/
    UCHAR ulReserve[8];      /*预留扩展字段*/
}NSR_BACKUP_INFO;

/*STRUCT<恢复信息>*/
typedef struct nsr_restore_info
{
    UCHAR ucRestoreType;    /*备份恢复标识信息*/
    UCHAR ucResult;         /*备份恢复结果*/
    CHAR  pad[2];
    UCHAR ulReserve[8];     /*预留扩展字段*/
}NSR_RESTORE_INFO;

/*STRUCT<平滑信息>*/
typedef struct nsr_smooth_info
{
    UCHAR ucSmoothType;     /*NSR平滑标识信息*/
    UCHAR ucResult;         /*NSR平滑结果*/
    CHAR  pad[2];
    UCHAR ulReserve[8];     /*预留扩展字段*/
}NSR_SMOOTH_INFO;

/*STRUCT<NSR控制类型消息定义>*/
typedef struct nsr_control_msg
{
    UCHAR ucMsgType;                         /*消息类型*/
    UCHAR ucDirect;                          /*控制类消息的发送目标*/
    CHAR  pad[2];
    UCHAR ulReserve[4];                      /*预留扩展字段*/
    union
      {
          UCHAR ucBoardInfo;                  /*单板状态通知*/
          UCHAR ucChannelInfo;                /*通道状态通知*/
          UCHAR ucSlaveBoardInfo;             /*备板状态通知*/
          NSR_BACKUP_INFO stBackupInfo;       /*备份状态通知*/
          NSR_RESTORE_INFO stRestoreInfo;     /*备份恢复通知*/
          NSR_SMOOTH_INFO stSmothInfo;        /*平滑通知*/
      }uControlMsg;

}NSR_CONTROL_MSG;

/* Modified by w00207740, DTS2014021106399,数据结构对齐删除pad保留字段, 2014/2/14 */
/*STRUCT<NSR COMMON的本地数据>*/
typedef struct nsr_common_info_show
{
    BOOL_T bNSRInit;              /*NSR是否初始化 0-未初始化  1-已初始化*/
    UCHAR ucNSRCapability;        /*NSR是否使能   1-使能  2-不使能, 默认为2*/
    UCHAR ucNextNSRCapability;    /*延迟生效的NSR使能状态，默认为0*/
    UCHAR ucNSRRole;              /*NSR角色,默认为备*/
    UCHAR ucIFReadyFlag;          /*接口上报结束标识*/
    UCHAR ucIFReadyStatus;        /*接口上报状态*/
    UCHAR ucNSRStatus;            /*NSR状态*/
    ULONG ulNSRFlag;              /*NSR标记，按位使用*/
}NSR_COMMON_INFO_SHOW;

/*STRUCT<NSR基础信息>*/
typedef struct nsr_base_info
{
    UCHAR ucBoardInfo;                  /*单板状态*/
    UCHAR ucChannelInfo;                /*通道状态*/
    UCHAR ucSlaveBoardInfo;             /*备板状态*/
    UCHAR pad[1];
}NSR_BASE_INFO;

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-11-07
*       Author: guojianjun178934
*      Purpose: 发送备份数据
*  Description: 
*        Input: UCHAR  *: 备份数据
*               ULONG :   数据长度
*               BOOL_T :  批备首包标识
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_RegFunSendBackupMsgHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-07   guojianjun178934        Create
*
*******************************************************************************/
typedef ULONG (*NSR_SEND_BACKUP_MSG_FUNC)(UCHAR *, ULONG, BOOL_T);

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-11-07
*       Author: guojianjun178934
*      Purpose: 发送控制消息
*  Description: 
*        Input: NSR_CONTROL_MSG  *: 控制消息
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_RegFunSendControlMsgHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-07   guojianjun178934        Create
*
*******************************************************************************/
typedef ULONG (*NSR_SEND_CONTROL_MSG_FUNC)(NSR_CONTROL_MSG *);

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-11-07
*       Author: guojianjun178934
*      Purpose: 从NSR模块获取 单板角色、通道状态、备板状态
*  Description: 
*        Input: 
*       Output: NSR_BASE_INFO *:NSR基础信息 单板角色、通道状态、备板状态
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_RegFunGetNSRBaseInfoHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-07   guojianjun178934        Create
*
*******************************************************************************/
typedef ULONG (*NSR_GET_NSR_BASE_INFO_FUNC)(NSR_BASE_INFO *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
