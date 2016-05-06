/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              rpm_type.h
*                 本文件为RIP、OSPF、RTM 提供公共部分的定义
*******************************************************************************/

#ifndef _RPM_TYPE_H_
#define _RPM_TYPE_H_

#ifdef  __cplusplus
    extern "C"{
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef BOOL_T
#define BOOL_T  short   /* boolean */  
#endif 


/*DTS2010120804467  
  g_ulNbaseProcCpuSwitchValue     CPU切换门限值
  g_ulSckStubProcMsgSwitchValue
  避免nbase任务占用CPU时间太长，主动释放CPU资源
*/
/*Modified by lKF35457, LACP DOWN问题, 2011/3/9   问题单号:DTS2011010702134 */
#define NBASE_MSG_SWITCH_VALUE    10
#define SCKSTUB_MSG_SWITCH_VALUE  10
/*End of Modified by lKF35457, 2011/3/9   问题单号:DTS2011010702134 */
#define DCL_TASK_SWITCH_INTERVAL  1/*切换CPU时间1ms*/
/*在不调用GET FIRST情况下调用GET NEXT返回失败

定义宏来表示 查询状态

只有在查询第一个完成，处于MORE 状态，才允许
GET NEXT 操作

OPEN 后，状态为GET_STATE_BEGIN
查询FIRST 并返回成功后，状态为GET_STATE_MORE
GET_STATE_END 表示查询结束
*/
#define  GET_STATE_BEGIN  0x01   
#define  GET_STATE_MORE   0x02
#define  GET_STATE_END     0x04

typedef enum tagSI_ERROR_E  
{
    SI_INIT_SUCSESS,
    SI_RRR_GEN_ERROR = MID_COMP_MIB + 2, 
    SI_RRR_WRONG_VALUE, /*MIB配置的值错误*/
    SI_RRR_INCONSISTENT_VALUE,/*MIB配置的值不一致*/
    SI_RRR_RESOURCE_UNAVAILABLE,/*MIB配置的资源无效*/
    SI_RRR_NO_SUCH_OBJECT, /*对象不存在*/
    SI_RRR_END_OF_TABLE,/*表项结束*/
    SI_RRR_AGENT_ERROR, 
    SI_RRR_INCOMPLETE,  
    SI_RRR_PARTIAL_FAMILY_OK,
    SI_RRR_PRODUCT_NOT_READY,
    SI_RRR_CFG_TIMEOUT = MID_COMP_MIB + 15,/*配置超时*/   
    SI_RRR_POINTER_IS_NULL ,
    SI_RRR_CONF_DATA_IS_NULL,
    SI_ERR_CONN_CB_IS_NULL,
    SI_ERR_RET_IPS_IS_NULL,
    SI_ERR_MAX = MID_COMP_MIB + 255,
}SI_ERROR_E; /*系统MIB */

typedef struct tagRM_Rpm_Plcy_Id_s
{
    USHORT usSrcType;   /*源协议类型*/
    USHORT usSrcProcId; /*源协议ID*/
    ULONG  ulDirection; /*过滤的方向:入或者出*/
    USHORT usDstType;   /*目的协议ID*/
    USHORT usDstProcId; /*目的实例号*/
    ULONG  ulPolicyId; /*策略ID*/
    /* Begin BC3D03313 liangjicheng 2010-06-22 */
    ULONG  ulUseFlag;      /*表示当前策略被谁使用-以位来使用*/
    ULONG  ulACLNo;        /*过滤策略ACL*/
    /* End   BC3D03313 liangjicheng 2010-06-22 */
    NBB_LLQE  stListNode;   /*链表*/
} RM_RPM_PLCY_ID_S;


/*l61496用于RIP 和OSPF使用的钩子函数类型定义*/
typedef ULONG (*OSPF_IF_UPDATE_HOOK_FUNC)(CHAR *, ULONG , ULONG ,ULONG);
typedef ULONG (*RIP_IPADDR_UPDATE_HOOK_FUNC)(USHORT, USHORT ,ULONG, ULONG);

#ifdef  __cplusplus
}
#endif

#endif

