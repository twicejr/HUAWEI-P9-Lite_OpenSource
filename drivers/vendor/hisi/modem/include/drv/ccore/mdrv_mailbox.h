#ifndef __MDRV_CCORE_MAILBOX_H__
#define __MDRV_CCORE_MAILBOX_H__
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum tagMAILBOX_INT_TYPE_E
    {
        EN_MAILBOX_INT_SUBFRAME = 0,        /* 子帧中断 */
        EN_MAILBOX_INT_COM_IPC,             /* IPC中断 */
        EN_MAILBOX_INT_SP_IPC,              /* 专有邮箱IPC中断 */
        EN_MAILBOX_INT_BUTT
    }MAILBOX_INT_TYPE_E;

#if defined(CHIP_BB_HI6210)
    typedef enum tagMAILBOX_SERVICE_TYPE_E
    {
        EN_MAILBOX_SERVICE_LTE_PS = 0,      /* LTE PS请求 */
        EN_MAILBOX_SERVICE_LTE_CT,          /* LTE CT请求 */
        EN_MAILBOX_SERVICE_LTE_BT,          /* LTE BT请求 */
        EN_MAILBOX_SERVICE_LTE_OM,          /* LTE OM邮箱请求 */
        EN_MAILBOX_SERVICE_LTE_COEX,        /* LTE WIFI coex */
        EN_MAILBOX_SERVICE_LTE_HS_DIAG,     /* LTE 可维可测低功耗数采请求 */
        EN_MAILBOX_SERVICE_LTE_RCM,         /* LTE RCM请求 */

        EN_MAILBOX_SERVICE_TDS_PS,          /* TDS PS请求 */
        EN_MAILBOX_SERVICE_TDS_CT,          /* TDS CT请求 */
        EN_MAILBOX_SERVICE_TDS_BT,          /* TDS BT请求 */
        EN_MAILBOX_SERVICE_TDS_OM,          /* TDS OM邮箱请求 */
        EN_MAILBOX_SERVICE_TDS_HS_DIAG,     /* TDS 可维可测低功耗数采请求 */
     	EN_MAILBOX_SERVICE_TDS_RCM,         /* TDS RCM请求 */
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        EN_MAILBOX_SERVICE_1X_RL,
        EN_MAILBOX_SERVICE_1X_OM,
        EN_MAILBOX_SERVICE_1X_BT,
        EN_MAILBOX_SERVICE_1X_CT,
        EN_MAILBOX_SERVICE_1X_HS_DIAG,
        
        EN_MAILBOX_SERVICE_HRPD_RL,
        EN_MAILBOX_SERVICE_HRPD_OM,
        EN_MAILBOX_SERVICE_HRPD_BT,
        EN_MAILBOX_SERVICE_HRPD_CT,
        EN_MAILBOX_SERVICE_HRPD_HS_DIAG,
#endif
        EN_MAILBOX_SERVICE_RTT_SYS_CTRL,    /* DSP可维可测控制业务 */
        EN_MAILBOX_SERVICE_RTT_AGENT,       /* tlphy CHR业务 */
        EN_MAILBOX_SERVICE_RTT_CBT,         /* 装备融合 */

        EN_MAILBOX_SERVICE_RTT_HIFI_AGENT,  //for AMR voice relay between TPHY and HIFI;

        EN_MAILBOX_SERVICE_BUTT
    }MAILBOX_SERVICE_TYPE_E;
#else
typedef enum tagMAILBOX_SERVICE_TYPE_E
    {
        EN_MAILBOX_SERVICE_LTE_PS = 0,      /* LTE PS请求 */
        EN_MAILBOX_SERVICE_LTE_CT,          /* LTE CT请求 */
        EN_MAILBOX_SERVICE_LTE_BT,          /* LTE BT请求 */
        EN_MAILBOX_SERVICE_LTE_OM,          /* LTE OM邮箱请求 */
        EN_MAILBOX_SERVICE_LTE_COEX,        /* LTE WIFI coex */
        EN_MAILBOX_SERVICE_LTE_HS_DIAG,     /* LTE 可维可测低功耗数采请求 */
        EN_MAILBOX_SERVICE_LTE_RCM,         /* LTE RCM请求 */

        EN_MAILBOX_SERVICE_TDS_PS,          /* TDS PS请求 */
        EN_MAILBOX_SERVICE_TDS_CT,          /* TDS CT请求 */
        EN_MAILBOX_SERVICE_TDS_BT,          /* TDS BT请求 */
        EN_MAILBOX_SERVICE_TDS_OM,          /* TDS OM邮箱请求 */
        EN_MAILBOX_SERVICE_TDS_HS_DIAG,     /* TDS 可维可测低功耗数采请求 */
     	EN_MAILBOX_SERVICE_TDS_RCM,         /* TDS RCM请求 */

        EN_MAILBOX_SERVICE_RTT_SYS_CTRL,    /* DSP可维可测控制业务 */
        EN_MAILBOX_SERVICE_RTT_AGENT,       /* tlphy CHR业务 */
		EN_MAILBOX_SERVICE_RTT_CBT,         /* tlphy CBT业务 */
		EN_MAILBOX_SERVICE_RTT_HIFI_AGENT,  /* for AMR voice relay between TPHY and HIFI */

        EN_MAILBOX_SERVICE_BUTT,

        EN_MAILBOX_SERVICE_1X_RL = EN_MAILBOX_SERVICE_BUTT,
        EN_MAILBOX_SERVICE_1X_OM,
        EN_MAILBOX_SERVICE_1X_BT,
        EN_MAILBOX_SERVICE_1X_CT,
        EN_MAILBOX_SERVICE_1X_HS_DIAG,
        
        EN_MAILBOX_SERVICE_HRPD_RL,
        EN_MAILBOX_SERVICE_HRPD_OM,
        EN_MAILBOX_SERVICE_HRPD_BT,
        EN_MAILBOX_SERVICE_HRPD_CT,
        EN_MAILBOX_SERVICE_HRPD_HS_DIAG,

        EN_MAILBOX_SERVICE_TOTAL_BUTT
    }MAILBOX_SERVICE_TYPE_E;

#endif

    typedef enum tagMAILBOX_SLEEP_PROC_E
    {
        EN_MAILBOX_SLEEP_WAKEUP = 0,        /* 强制唤醒DSP后处理请求 */
        EN_MAILBOX_SLEEP_LOST,              /* DSP处于睡眠模式时丢弃该请求 */
        EN_MAILBOX_SLEEP_DIRECT,            /* 不判断DSP状态，直接写操作 慎用*/
        EN_MAILBOX_SLEEP_BUTT
    }MAILBOX_SLEEP_PROC_E;

    typedef enum tagMAILBOX_ERRORCODE_E
    {
        ERR_MAILBOX_NOT_INIT = 1,           /* 未初始化 */
        ERR_MAILBOX_PARAM_INCORRECT,        /* 参数错误 */
        ERR_MAILBOX_MEMORY_NOTENOUGH,       /* 空间不足 */
        ERR_MAILBOX_TIMEOUT,                /* 超时 */
        ERR_MAILBOX_COVER,                  /* 专有邮箱写操作时原语未读走，执行覆盖操作 */
        ERR_MAILBOX_WRITE_FAILED,           /* 邮箱写失败 */
        ERR_MAILBOX_READ_FAILED,            /* 邮箱读失败 */
        ERR_MAILBOX_READ_NULL,              /* 邮箱读到空信息 */
        ERR_MAILBOX_DSP_POWERDOWN,          /* DSP处于低功耗状态 */
        ERR_MAILBOX_OTHER,                  /* 其他错误 */
        ERR_MAILBOX_ERRORCODE_BUTT
    }MAILBOX_ERRORCODE_E;
	typedef enum tagMAILBOX_CALLBACK_TYPE_E
	{
        EN_MAILBOX_CALLBACK_DSP_RUN = 0,        /*DSP RUN CALLBACK*/
        EN_MAILBOX_CALLBACK_DSP_RESUME,         /*DSP RESUME IRQ CALLBACK*/
        EN_MAILBOX_CALLBACK_DSP_BUTT
	}MAILBOX_CALLBACK_TYPE;
	typedef void (*BSP_MBX_RCM_CALLBACK_FUNC)(MAILBOX_CALLBACK_TYPE e);
	void BSP_MailBox_Rcm_CallBackReg(BSP_MBX_RCM_CALLBACK_FUNC pFunc);

    typedef void (*BSP_MBX_NOTIFY_FUNC)(MAILBOX_INT_TYPE_E enIntType);
    typedef int (*BSP_MBX_GET_STATUS_FUNC)(void);
    typedef void (*BSP_MBX_DSP_AWAKE_FUNC)(void);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_ComMsgInit
     * Description    : 通用邮箱的初始化(提供给协议栈调用，
     *                  接口内部实现与DSP握手信息的初始化)
     * Input          : ulworkingmode
     * Return Value   : None
     ******************************************************************************/
    void BSP_MailBox_ComMsgInit(unsigned int ulworkingmode);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_IsDspOk
     * Description    : 与DSP的握手函数，判断DSP是否初始化结束
     *                  (提供给协议栈调用，如果握手不成功，协议栈需要循环多次调用)
     * Input          : None
     * Return Value   : BSP_TRUE:   DSP初始化结束，握手成功
     *                  BSP_FALSE:  DSP没有初始化结束，握手不成功
     ******************************************************************************/
    int BSP_MailBox_IsDspOk(void);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_IntTypeSet
     * Description     : 设置PS邮箱中断源接口(默认IPC中断方式)
     *                   只用于PS邮箱，OM邮箱无中断上报
     * Param           : None
     * Return Value    : 0: 成功; 其他: 设置的type非法
     ******************************************************************************/
    unsigned int BSP_MailBox_IntTypeSet(MAILBOX_INT_TYPE_E enIntType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComMsgWrite
     * Description     : 邮箱写接口(每次只支持写一条原语)
     * Input           : enMbxType    邮箱的业务类型
     *                   pData        数据指针
     *                   ulLen        数据长度(以字节为单位)
     *                   enProcType   DSP睡眠时的处理类型
     * Output          : None.
     * Return Value    : BSP_OK: 成功
     *                     其他: 失败
     ******************************************************************************/
    unsigned int BSP_MailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
            void* pData,
            unsigned int ulLen,
            MAILBOX_SLEEP_PROC_E enProcType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComNotifyReg
     * Description     : 邮箱数据到达通知注册接口（子帧中断即使没数据也要回调）
     * Param           : enMbxType        邮箱的业务类型
     *                   pFun             邮箱数据到达处理函数
     * Return Value    : BSP_OK: 成功
     *                   ERR_MAILBOX_NOT_INIT
     *                   ERR_MAILBOX_PARAM_INCORRECT
     ******************************************************************************/
    unsigned int BSP_MailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
            BSP_MBX_NOTIFY_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComMsgSize
     * Description     : 获取通用邮箱中第一条原语的长度
     *                   (提供给上层调用，驱动不提供邮箱中原语条数接口，需要上层循环
     *                    读，以避免上层漏掉中断通知时造成邮箱中原语缓存)
     * Param           : enMbxType        邮箱的业务类型
     * Return Value    : 0:  没有获取原语（邮箱为空，或有其他类型的原语未读走）
     *                   其他值: 邮箱第一条原语的长度
     ******************************************************************************/
    unsigned int BSP_MailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_ComMsgRead
     * Description     : 邮箱读接口
     *                   (此接口会唤醒DSP，需要BSP_MailBox_ComMsgSize返回非空时调用)
     * Param           : enMbxType    邮箱的业务类型
     *                   pData        接收的数据缓冲区指针(存储原语信息，不包含原语长度)
     *                   ulLen        pData缓冲区的size(以字节为单位)
     *                   enProcType   DSP睡眠时的处理类型
     * Return Value    : 0 : 成功
     *                   其他 : 失败
     ******************************************************************************/
    unsigned int BSP_MailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpULMsgHeadInit
     * Description    : 专有（Special Mailbox）上行邮箱的消息头初始化接口
     *                  (初始化上行邮箱每条原语的消息头，提供给协议栈，需要调用多次
     *                   由调用者保证调用接口时DSP处于非睡眠状态)
     * Input          :
     *                  ulAddr : 专有邮箱的地址
     *                  ulSize : 初始值的大小(以字节为单位)
     *                  ucData : 初始值
     * Return Value   : None
     ******************************************************************************/
    void BSP_MailBox_SpULMsgHeadInit(unsigned int ulAddr, unsigned int ulSize, unsigned char ucData);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpDLMsgHeadInit
     * Description    : 专有（Special Mailbox）下行邮箱的消息头初始化接口
     *                  (初始化上行邮箱每条原语的消息头，提供给协议栈，需要调用多次
     *                   由调用者保证调用接口时DSP处于非睡眠状态)
     * Input          :
     *                  ulAddr : 专有邮箱的地址
     *                  ulSize : 初始值的大小(以字节为单位)
     *                  ucData : 初始值
     * Return Value   : None
     ******************************************************************************/
    void BSP_MailBox_SpDLMsgHeadInit(unsigned int ulAddr, unsigned int ulSize, unsigned char ucData);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpMsgWrite
     * Description    : 专有邮箱（Special Mailbox）的写接口
     *                  (由调用者保证调用接口时DSP处于非睡眠状态)
     * Input          :
     *                  ulAddr : 专有邮箱的偏移地址（从消息头开始的地址）
     *                  ulSize : 初始值的大小(以字节为单位)
     *                  pData  : 数据信息(不包含消息头信息)
     * Return Value   :
     *                  BSP_OK: 表示操作成功
     *                  ERR_MAILBOX_COVER: 表示前一条原语未被读走，覆盖
     *                  ERR_MAILBOX_WRITE_FAILED: 写失败
     *                  ERR_MAILBOX_NOT_INIT: 邮箱未初始化
     *                  ERR_MAILBOX_PARAM_INCORRECT: 参数错误
     ******************************************************************************/
    unsigned int BSP_MailBox_SpMsgWrite(unsigned int ulAddr, unsigned int ulSize, void* pData);

    /*****************************************************************************
     * Prototype      : BSP_MailBox_SpMsgRead
     * Description    : 专有邮箱（Special Mailbox）的读接口
     *                  (由调用者保证调用接口时DSP处于非睡眠状态)
     * Input          :
     *                  ulAddr : 专有邮箱的偏移地址（从消息头开始的地址）
     *                  ulSize : 初始值的大小(以字节为单位)
     *                  pData  : 数据信息(不包含消息头信息)
     * Return Value   :
     *                  BSP_OK: 读取成功
     *                  ERR_MAILBOX_READ_NULL: 无数据
     *                  ERR_MAILBOX_NOT_INIT: 邮箱未初始化
     *                  ERR_MAILBOX_PARAM_INCORRECT: 参数错误
     ******************************************************************************/
    unsigned int BSP_MailBox_SpMsgRead(unsigned int ulAddr, unsigned int ulSize, void* pData);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_SpNotifyReg
     * Description     : 专有邮箱数据到达通知注册接口
     * Param           : pFun             邮箱数据到达处理函数
     * Return Value    : BSP_OK: 成功
     *                     其他: 失败
     ******************************************************************************/
    unsigned int BSP_MailBox_SpNotifyReg(BSP_MBX_NOTIFY_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_SpNotifyEnable
     * Description     : 专有邮箱数据到达通知中断使能接口
     * Param           : None
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_SpNotifyEnable(void);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_SpNotifyDisable
     * Description     : 专有邮箱数据到达通知中断去使能接口
     * Param           : None
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_SpNotifyDisable(void);

    /*****************************************************************************
     * Prototype       : BSP_Mailbox_ForbidDspSleep
     * Description     : 禁止DSP睡眠接口
     * Input           : enProcType     DSP睡眠时的处理类型
     *                   EN_MAILBOX_SLEEP_WAKEUP : 强制唤醒时会有等待处理，
     *                                             不能在中断回调中输入此参数
     *                                             只能在任务中输入此参数
     *                   EN_MAILBOX_SLEEP_LOST   : 中断回调和任务中都可输入此参数
     * Return Value    : BSP_OK: 成功,DSP当前没睡眠，且已设置禁止DSP进入睡眠
     *                   ERR_MAILBOX_DSP_POWERDOWN : 当输入为EN_MAILBOX_SLEEP_LOST,
     *                                               DSP当前处于低功耗状态,设置失败
     *                   ERR_MAILBOX_TIMEOUT       : 当输入为EN_MAILBOX_SLEEP_WAKEUP,
     *                                               唤醒DSP超时(10s)
     ******************************************************************************/
    unsigned int BSP_Mailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType);


    /*****************************************************************************
     * Prototype       : BSP_Mailbox_AllowDspSleep
     * Description     : 允许DSP睡眠接口
     * Input           : None
     * Return Value    : None
     ******************************************************************************/
    void BSP_Mailbox_AllowDspSleep(void);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_GetDspStatusReg
     * Description     : 获取DSP睡眠状态回调函数注册接口，低功耗模块调用
     * Param           : pFun             获取DSP睡眠状态处理函数
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_DspForceAwakeReg
     * Description     : DSP强制唤醒回调函数注册接口，低功耗模块调用
     * Param           : pFun             DSP强制唤醒处理函数
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_DspForceAwakeReg(BSP_MBX_DSP_AWAKE_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_GetSpMsgStatusReg
     * Description     : 获取专有邮箱允许DSP睡眠状态回调函数注册接口，PS调用
     * Param           : pFun             获取DSP睡眠状态处理函数
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_DspAwakeProc
     * Description     : DSP唤醒后的邮箱处理接口，低功耗模块调用
     * Param           : void
     * Return Value    : void
     ******************************************************************************/
    void BSP_MailBox_DspAwakeProc(MAILBOX_CALLBACK_TYPE cbType);

    /*****************************************************************************
     * Prototype       : BSP_MailBox_IsAllowDspSleep
     * Description     : 查询是否允许DSP睡眠的处理接口，低功耗模块调用
     *                   调用此接口时低功耗模块保证DSP未睡眠
     *                   此接口只检测PS邮箱和专有邮箱，不检查OM邮箱(OM原语无时延要求)
     * Param           : void
     * Return Value    : int: TRUE-allow;FALSE-forbid
     ******************************************************************************/
    int BSP_MailBox_IsAllowDspSleep(void);

    /*****************************************************************************
     * Prototype       : BSP_UniMailboxWrite
     * Description     : 邮箱的通用写接口(由调用者保证传入的地址的合法性)
     *                   本接口实现类似memcpy函数的作用
     *                   接口内部保证DSP的唤醒操作，如果唤醒失败，返回ERR_MAILBOX_TIMEOUT
     * Return Value    :
     *                   BSP_OK
     *                   ERR_MAILBOX_PARAM_INCORRECT
     *                   ERR_MAILBOX_TIMEOUT
     ******************************************************************************/
    unsigned int BSP_UniMailboxWrite(void *pDst, void *pSrc, unsigned int ulLen);

    /*****************************************************************************
     * Prototype       : BSP_MailboxAbnormalProc
     * Description     : 邮箱异常处理
     *                   协议栈接收消息超时后调用此接口保存邮箱相关信息
     *                   与协议栈商定，前0.5K保存协议栈信息，后3.5K保存邮箱信息
     * Input           : ucData       缓存首地址
     * Return Value    : NONE
     *****************************************************************************/
    void BSP_MailboxAbnormalProc(unsigned char *ucData);

    /*****************************************************************************
     *  Prototype    : Mbx_ComPsPreProc
     *  Description  : PS邮箱的预处理函数(主要作用是更新PS/CTBT消息长度信息)
     *                 1. 邮箱内有PS消息，则更新PS消息长度
     *                 2. 邮箱内有CT/BT消息，则更新PS消息长度
     *                 3. 可能在中断中调用，不能打印和malloc
     *                 4. DSP保证邮箱中的原语未读走时不睡眠
     * Param         : None
     * Return Value  : void
     ******************************************************************************/
    void Mbx_ComPsPreProc();

    /*****************************************************************************
     *  Prototype    : Mbx_ComOmPreProc
     *  Description  : PS邮箱的预处理函数(主要作用是更新PS/CTBT消息长度信息)
     *                 1. 邮箱内有PS消息，则更新PS消息长度
     *                 2. 邮箱内有CT/BT消息，则更新PS消息长度
     *                 3. 可能在中断中调用，不能打印和malloc
     *                 4. DSP保证邮箱中的原语未读走时不睡眠
     * Param         : None
     * Return Value  : void
     ******************************************************************************/
    void Mbx_ComOmPreProc();
#ifdef __cplusplus
}
#endif
#endif
