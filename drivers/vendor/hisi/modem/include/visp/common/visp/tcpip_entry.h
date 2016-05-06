/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_entry.h
*
*  Project Code: VISPV1R5
*   Module Name: PUBLIC  
*  Date Created: 2006-6-15
*        Author: X36317
*   Description: 此文件定义了tcpip_entry.c中使用的数据结构和宏等
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-6-15  X36317         Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_ENTRY_H_
#define _TCPIP_ENTRY_H_
#ifdef  __cplusplus
extern "C"{
#endif

#define TCPIP_UNREFERENCED_PARAMETER(P) { (P) = (P); }

/*--------------------------------*/
/* 公共事件位:定时器事件          */
/*--------------------------------*/
#define VRP_EVENT_TIMERREQ          0X00008000  /* "00000000 00000000 10000000 00000000" */

/*Added by zhukun*/ /*IPv6 Pmtu的两个事件*/
#define VRP_EVENT_PMTUREQ           0X00080000  /* "00000000 00001000 00000000 00000000" */
#define VRP_EVENT_PMTUFLUSH         0X00100000  /* "00000000 00010000 00000000 00000000" */


/*Modified by X36317, 大小从16调整到15，以保证结构体4字节对齐, 2006-05-12*/
#define APP_NAME_MAX_LEN        15 
/*Modified by X36317, 大小从4调整到7，以保证结构体4字节对齐, 2006-05-12*/
#define APP_TASK_NAME_LEN       7  
#define APP_TASK_PARA_NUM       4

typedef VOID  (*APP_TASK_ENTRY) (UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3);
typedef ULONG (*APP_INIT_FUNC)();
typedef VOID  (*APP_MIB_REG)();
typedef VOID  (*APP_IFNET_HOT_NOTIFY_CB)(ULONG ulEvent, ULONG ulSlot, VOID * pstIfnet, ULONG ulIfIndex);
typedef ULONG (*APP_CFA_CB)(VOID *, VOID **);


typedef struct tagAPP_INIT_INFO
{
    ULONG                   ulMID;                          /*MID*/
    UCHAR                   szAppName[APP_NAME_MAX_LEN + 1];    /*Application name, '\0' terminated */
    VOID                   *pstComponentInfo;

    APP_TASK_ENTRY          pfTaskEntry;                    /*Task entry, NULL for no own task*/
    UCHAR                   szTaskName[APP_TASK_NAME_LEN + 1];  /*Task name, zero terminated*/
    ULONG                   ulTaskPriority;                 /*Task priority*/   
    ULONG                   ulTaskMode;                     /*task mode*/
    ULONG                   ulTaskStackSize;                /*task stack size */
    UINTPTR                 ulTaskArg[APP_TASK_PARA_NUM];   /*task entry parameters*/

    APP_INIT_FUNC           pfAppInit;
    APP_MIB_REG             pfMibReg;                       /*register MIB*/
    APP_IFNET_HOT_NOTIFY_CB pfIfnetHotNotifyCB;
    APP_CFA_CB              pfCfaCB;                        /*config process func on IO board*/

    CHAR                  **ppcExecInfor_EN;                
    CHAR                  **ppcExecInfor_CN;                
    CHAR                  **ppcExecInfor_EXTD;              

    ULONG                   ulAppIndex;                     /*to store app id*/ 
    ULONG                   ulTaskId;                       /*to store the task ID*/
    ULONG                   ulExecInforIndex;               /*to store the execinfo index*/

}APP_INIT_INFO_S;

typedef struct tagTCPIP_PRECFG_VALUE
{
    ULONG ulKey;        /* 预配置参数ID */
    ULONG ulCfg_Value;  /* 配置值 */
    ULONG ulMin_Value;  /* 可配置值的下限 */
    ULONG ulMax_Value;  /* 可配置值的上限 */
}TCPIP_PRECFG_VALUE_S;

VOID TCPIP_InfoOutput(CHAR *pInfo);
#define TCPIP_printf TCPIP_InfoOutput



ULONG SYS_RegAppInfo(APP_INIT_INFO_S *);

extern ULONG        ulVRPTID_SOCK;      
extern ULONG        ulSOCKTmrQueID; 

ULONG TCPIP_IC_SendMsg(ULONG ulMId, ULONG ulInfoId, char *pBuf);

/****************************************************************************
* Prototype    : TCPIP_Set_PreConfigPara
* Description  : VISP 预配置参数设置函数
* Called by     : 应用VISP的产品
* Calls           : 
*----------------------------------------------------------------------------
* NOTICE       : 应用VISP时，调用此函数设置VISP系统参数。
* NOTICE       : ulKey取值为TCPIP_PRECONFIG_INFO_E中的枚举值，
* NOTICE       : ulValue取值参考ulKey对应的取值说明。
*****************************************************************************/
ULONG TCPIP_Set_PreConfigPara(ULONG ulKey, ULONG ulValue);

/****************************************************************************
* Prototype    : TCPIP_Set_PreConfigPara
* Description  : VISP 预配置参数值获取函数
* Called by     : 应用VISP的产品
* Calls           : 
*----------------------------------------------------------------------------
* NOTICE       : 应用VISP时，调用此函数获取VISP系统参数默认值。
* NOTICE       : ulKey取值为TCPIP_PRECONFIG_INFO_E中的枚举值，
* NOTICE       : 返回的ulCfg_Value为VISP系统参数默认值。
*****************************************************************************/
ULONG TCPIP_Get_PreConfigPara(TCPIP_PRECFG_VALUE_S *pstComPara);

/*Begin 2013-02-07 liangjicheng 增加Linux 默认栈配置 默认值:8M 考虑DLC任务嵌套*/

#define  LINUX_DEFAULTSTACKSIZE 1024*1024*8
#define  LINUX_MAXSTACKSIZE 1024*1024*16

/*End   2008-09-10 liangjicheng */

#ifdef  __cplusplus
}
#endif
#endif


