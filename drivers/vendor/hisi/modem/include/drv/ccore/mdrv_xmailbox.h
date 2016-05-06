#ifndef __MDRV_CCORE_XMAILBOX_H__
#define __MDRV_CCORE_XMAILBOX_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_mailbox.h>

enum _XMBX_RATMODE_ENUM_U32
{
    XMBX_MOD_1X = 0,
    XMBX_MOD_HRPD,
    XMBX_MOD_OTHER,
    XMBX_MOD_BUTT,
};

typedef unsigned int XMBX_RATMODE_ENUM_U32;

typedef struct {
    unsigned int ulProtectWord;                  /* 0x5a5a5a5a,   保护字             */
    unsigned int ulCphyMbxHpaUpAddr;             /* CPHY<->CCORE, HPA邮箱上行基地址  */
    unsigned int ulCphyMbxHpaDownAddr;           /* CPHY<->CCORE, HPA邮箱下行基地址  */
    unsigned int ulCphyMbxOmDownAddr;            /* CPHY<->CCORE, OM邮箱下行基地址   */
    unsigned int ulCphyMbxLoadMemAddr;           /* CPHY<->CCORE, 加载地址           */
    unsigned int ulCphyMbxWorkModeAddr;          /* CPHY<->CCORE, 工作模式地址       */
} CPHY_CCORE_DYN_ADDR_SHARE_STRU;

typedef void (*BSP_xMBX_RCM_CALLBACK_FUNC)(MAILBOX_CALLBACK_TYPE e);
void BSP_xMailBox_Rcm_CallBackReg(BSP_xMBX_RCM_CALLBACK_FUNC pFunc);

typedef void (*BSP_xMBX_NOTIFY_FUNC)(MAILBOX_INT_TYPE_E enIntType);

typedef int (*BSP_xMBX_GET_STATUS_FUNC)(XMBX_RATMODE_ENUM_U32 enMode);
typedef void (*BSP_xMBX_DSP_AWAKE_FUNC)(XMBX_RATMODE_ENUM_U32 enMode);



/*****************************************************************************
 * Prototype      : BSP_xMailBox_ComMsgInit
 * Description    : 通用邮箱的初始化(提供给协议栈调用，
 *                  接口内部实现与DSP握手信息的初始化)
 * Input          : ulworkingmode
 * Return Value   : None
 ******************************************************************************/
//void BSP_xMailBox_ComMsgInit(unsigned int ulworkingmode);

/*****************************************************************************
 * Prototype      : BSP_xMailBox_IsDspOk
 * Description    : 与DSP的握手函数，判断DSP是否初始化结束
 *                  (提供给协议栈调用，如果握手不成功，协议栈需要循环多次调用)
 * Input          : None
 * Return Value   : BSP_TRUE:   DSP初始化结束，握手成功
 *                  BSP_FALSE:  DSP没有初始化结束，握手不成功
 ******************************************************************************/
int BSP_xMailBox_IsDspOk(void);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComMsgWrite
 * Description     : 邮箱写接口(每次只支持写一条原语)
 * Input           : enMbxType    邮箱的业务类型
 *                   pData        数据指针
 *                   ulLen        数据长度(以字节为单位)
 *                   enProcType   DSP睡眠时的处理类型
 * Output          : None.
 * Return Value    : BSP_OK: 成功
 *                     其他: 失败
 ******************************************************************************/
unsigned int BSP_xMailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
        void* pData,
        unsigned int ulLen,
        MAILBOX_SLEEP_PROC_E enProcType);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComNotifyReg
 * Description     : 邮箱数据到达通知注册接口（子帧中断即使没数据也要回调）
 * Param           : enMbxType        邮箱的业务类型
 *                   pFun             邮箱数据到达处理函数
 * Return Value    : BSP_OK: 成功
 *                   ERR_MAILBOX_NOT_INIT
 *                   ERR_MAILBOX_PARAM_INCORRECT
 ******************************************************************************/
unsigned int BSP_xMailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
        BSP_xMBX_NOTIFY_FUNC pFun);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComMsgSize
 * Description     : 获取通用邮箱中第一条原语的长度
 *                   (提供给上层调用，驱动不提供邮箱中原语条数接口，需要上层循环
 *                    读，以避免上层漏掉中断通知时造成邮箱中原语缓存)
 * Param           : enMbxType        邮箱的业务类型
 * Return Value    : 0:  没有获取原语（邮箱为空，或有其他类型的原语未读走）
 *                   其他值: 邮箱第一条原语的长度
 ******************************************************************************/
unsigned int BSP_xMailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType);

/*****************************************************************************
 * Prototype       : BSP_xMailBox_ComMsgRead
 * Description     : 邮箱读接口
 *                   (此接口会唤醒DSP，需要BSP_MailBox_ComMsgSize返回非空时调用)
 * Param           : enMbxType    邮箱的业务类型
 *                   pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
 *                   ulLen        pData缓冲区的size(以字节为单位)
 *                   enProcType   DSP睡眠时的处理类型
 * Return Value    : 0 : 成功
 *                   其他 : 失败
 ******************************************************************************/
unsigned int BSP_xMailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                           void* pData,
                           unsigned int ulLen,
                           MAILBOX_SLEEP_PROC_E enProcType);

/*****************************************************************************
 * Prototype       : BSP_xMailbox_SetDtcmAddr
 * Description     : x模邮箱地址获取接口
 * Param           : CPHY_CCORE_DYN_ADDR_SHARE_STRU    X模邮箱地址结构体
 * Return Value    : 无
 ******************************************************************************/

void BSP_xMailbox_SetDtcmAddr(CPHY_CCORE_DYN_ADDR_SHARE_STRU *addr);


/*****************************************************************************
 * Prototype       : BSP_xMailbox_ForbidDspSleep
 * Description     : 禁止DSP睡眠接口
 * Input           : enProcType     DSP睡眠时的处理类型
 *                   EN_MAILBOX_SLEEP_WAKEUP : 强制唤醒时会有等待处理，
 *                                             不能在中断回调中输入此参数
 *                                             只能在任务中输入此参数
 *                   EN_MAILBOX_SLEEP_LOST   : 中断回调和任务中都可输入此参数
 *                   commtype  通信制式 0表示1X， 1表示hrpd，2表示其他不需要传制式的场景
 * Return Value    : BSP_OK: 成功,DSP当前没睡眠，且已设置禁止DSP进入睡眠
 *                   ERR_MAILBOX_DSP_POWERDOWN : 当输入为EN_MAILBOX_SLEEP_LOST,
 *                                               DSP当前处于低功耗状态,设置失败
 *                   ERR_MAILBOX_TIMEOUT       : 当输入为EN_MAILBOX_SLEEP_WAKEUP,
 *                                               唤醒DSP超时(10s)
 ******************************************************************************/
unsigned int BSP_xMailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType, unsigned int commtype);


/*****************************************************************************
 * Prototype       : BSP_xMailbox_AllowDspSleep
 * Description     : 允许DSP睡眠接口
 * Input           : None
 * Return Value    : None
 ******************************************************************************/
void BSP_xMailbox_AllowDspSleep(void);

/*****************************************************************************
 * Prototype       : mdrv_MailBox_GetCdmaStatusReg
 * Description     : 获取DSP睡眠状态回调函数注册接口，低功耗模块调用
 * Param           : pFun             获取DSP睡眠状态处理函数
 * Return Value    : void
 ******************************************************************************/
void mdrv_MailBox_GetCdmaStatusReg(BSP_xMBX_GET_STATUS_FUNC pFun);

/*****************************************************************************
 * Prototype       : mdrv_MailBox_CdmaForceAwakeReg
 * Description     : DSP强制唤醒回调函数注册接口，低功耗模块调用
 * Param           : pFun             DSP强制唤醒处理函数
 * Return Value    : void
 ******************************************************************************/
void mdrv_MailBox_CdmaForceAwakeReg(BSP_xMBX_DSP_AWAKE_FUNC pFun);

/*****************************************************************************
 * Prototype       : mdrv_MailBox_CdmaResumeProc
 * Description     : DSP唤醒后的邮箱处理接口，低功耗模块调用
 * Param           : void
 * Return Value    : void
 ******************************************************************************/
void mdrv_MailBox_CdmaResumeProc(MAILBOX_CALLBACK_TYPE cbType, XMBX_RATMODE_ENUM_U32 enMode);

/*****************************************************************************
 * Prototype       : mdrv_Mailbox_IsAllowCdmaSleep
 * Description     : 查询是否允许DSP睡眠的处理接口，低功耗模块调用
 *                   调用此接口时低功耗模块保证DSP未睡眠
 *                   此接口只检测PS邮箱和专有邮箱，不检查OM邮箱(OM原语无时延要求)
 * Param           : void
 * Return Value    : int: TRUE-allow;FALSE-forbid
 ******************************************************************************/
int mdrv_Mailbox_IsAllowCdmaSleep(XMBX_RATMODE_ENUM_U32 enMode);

/*****************************************************************************
 * Prototype       : BSP_xMailboxAbnormalProc
 * Description     : 邮箱异常处理
 *                   协议栈接收消息超时后调用此接口保存邮箱相关信息
 *                   与协议栈商定，前0.5K保存协议栈信息，后3.5K保存邮箱信息
 * Input           : ucData       缓存首地址
 * Return Value    : NONE
 *****************************************************************************/
void BSP_xMailboxAbnormalProc(unsigned char *ucData);

/*****************************************************************************
 *  Prototype    : xMbx_ComPsPreProc
 *  Description  : PS邮箱的预处理函数(主要作用是更新PS/CTBT消息长度信息)
 *                 1. 邮箱内有PS消息，则更新PS消息长度
 *                 2. 邮箱内有CT/BT消息，则更新PS消息长度
 *                 3. 可能在中断中调用，不能打印和malloc
 *                 4. DSP保证邮箱中的原语未读走时不睡眠
 * Param         : None
 * Return Value  : void
 ******************************************************************************/
void xMbx_ComPsPreProc();

/*****************************************************************************
 *  Prototype    : xMbx_ComOmPreProc
 *  Description  : PS邮箱的预处理函数(主要作用是更新PS/CTBT消息长度信息)
 *                 1. 邮箱内有PS消息，则更新PS消息长度
 *                 2. 邮箱内有CT/BT消息，则更新PS消息长度
 *                 3. 可能在中断中调用，不能打印和malloc
 *                 4. DSP保证邮箱中的原语未读走时不睡眠
 * Param         : None
 * Return Value  : void
 ******************************************************************************/
void xMbx_ComOmPreProc();

#ifdef __cplusplus
}
#endif
#endif
