

#ifndef __MDRV_TIMER_COMMON_H__
#define __MDRV_TIMER_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        TIMER_ONCE_COUNT = 0,        /* 单次定时器模式 */
        TIMER_PERIOD_COUNT,          /* 周期定时器模式 */
        TIMER_FREERUN_COUNT,         /* 自由定时器模式 */
        TIMER_COUNT_BUTT
    }DRV_TIMER_MODE_E;

    typedef enum
    {
        TIMER_UNIT_MS = 0,           /* 0表示单位ms模式 */
        TIMER_UNIT_US,               /* 1表示单位us模式 */
        TIMER_UNIT_NONE,             /* 2表示单位1，即直接操作load寄存器模式  */
        TIMER_UNIT_BUTT
    }DRV_TIMER_UNIT_E;


  	

	typedef enum
	{
		TIMER_CCPU_DSP_DRX_PROT_ID	,	/*v9r1 新添加，用途待确认，先保证编译通过    liujing*/
		ACORE_SOFTTIMER_ID			,	/*A core 唤醒源软timer id                lixiaojie*/
		CCORE_SOFTTIMER_ID			,	/*C core 唤醒源软timer id                lixiaojie*/
		ACORE_WDT_TIMER_ID			,	/*A CORE看门狗                           yangqiang*/
		CCORE_WDT_TIMER_ID			,	/*C CORE看门狗                           yangqiang*/
		TIME_STAMP_ID				,	/*P531上使用，A core C CORE M3时间戳,在fastboot阶段使能 ，V7R2使用BBP时间戳lixiaojie*/
		USB_TIMER_ID				,	/*A CORE    V7R2 USB使用                lvhui*/
		CCORE_SOFTTIMER_NOWAKE_ID	,	/*C core 非唤醒源软timer                 lixiaojie*/
		ACORE_SOFTTIMER_NOWAKE_ID	,	/*A core 非唤醒源软timer                 lixiaojie*/
		TIMER_DSP_TIMER2_ID			,	/*DSP使用                                 liujing*/
		TIMER_MCPU_ID				,	/*M3使用                                lixiaojie*/
		TIMER_HIFI_TIMER2_ID		,	/*hifi使用                              fuying*/
		TIMER_UDELAY_TIMER_ID		,	/*c核提供udelay函数使用，在fastboot阶段使能              lixiaojie*/
		CCORE_SYSTEM_TIMER_ID		,	/*C Core系统时钟                        luting*/
		ACORE_SYSTEM_TIMER_ID		,	/*A CORE系统时钟                        luting*/
		ACORE_SOURCE_TIMER_ID		,	/*A CORE 事件源                        luting */
		TIMER_ACPU_CPUVIEW_ID		,	/*A CORE CPU VIEW                      duxiaopeng*/
		TIMER_CCPU_CPUVIEW_ID		,	/*C CORE CPU VIEW                     duxiaopeng*/
		TIMER_HIFI_TIMER1_ID		,	/*hifi使用                             fuying*/
		TIMER_ACPU_OSA_ID			,	/*A CORE软件定时                        cuijunqiang*/
		TIMER_CCPU_OSA_ID			,	/*C CORE软件定时                        cuijunqiang*/
		TIMER_CCPU_DRX1_STABLE_ID	,	/*C CORE tcxo稳定时钟xujingcui            */
		TIMER_DSP_TIMER1_ID			,	/*DSP使用                             liujing*/
		TIMER_CCPU_DRX2_STABLE_ID	,	/*C CORE tcxo稳定时钟xujingcui                    */
		TIMER_CCPU_DRX_TIMER_ID		,	/*处理非实时性唤醒,cuijunqiang          */
		TIMER_ACPU_OM_TCXO_ID		,	/*解决vos timer频繁唤醒, cuijunqiang    */
		TIMER_DSP_SWITCH_DELAY_ID	,	/*VOLTE sleep dalay optimize for dsp ,cuijunqiang*/
		TIMER_CCPU_G1PHY_DRX_ID		,	/*只有V9R1使用，V7R2和K3V3等产品形态打桩:luoqingquan*/
		TIMER_CCPU_AUX_ID			,	/*v8 */
		TIMER_CCPU_MSP_ID			,	/*v8 */
		TIMER_CCPU_APP_ID			,	/*v8 */
		TIMER_ALL_SLICE_ID			,	/*v8 */
		TIMER_CCPU_DFS_ID 			,	/*v8 */
		TIMER_CCPU_DRX_STAMP_ID		,	/*v8 */
		TIMER_MCU_TIMER1_ID			,	/*v8 */
		TIMER_MCU_TIMER2_ID			,	/*v8 */
		TIMER_ACPU_FREE_RUN			,	/*v8 */
		TIMER_ACPU_IDLE_ID			,	/*v8 */
		TIMER_ID_MAX 
	} DRV_TIMER_ID;

    /*****************************************************************************
     *  函 数 名  : mdrv_timer_debug_register
     *  功能描述  : 封装给上层注册timer唤醒系统时的OM回调
     *  输入参数  : usrClkId:  时钟ID
     *              routine:  回调函数
     *                 arg:   回调参数
     *  返 回 值  : void
     *  调用函数  :
     *  被调函数  :
     *
     *  修改历史      :
     *      1.日    期   : 2014年5月6日
     *        作    者   : lixiaojie 00227190
     *        修改内容    : 新生成函数
     *
     ******************************************************************************/
    void mdrv_timer_debug_register(unsigned int timer_id, FUNCPTR_1 routinue, int arg);

    /*****************************************************************************
     *  函 数 名  : mdrv_timer_start
     *  功能描述  : 封装给协议栈的用户时钟定时器启动函数
     *  输入参数  : usrClkId:  时钟ID,取值0~19
     *              routine:   回调函数
     *                  arg:   回调参数
     *           timerValue:   计数值
     *                 mode:   定时器模式，单次模式或周期模式.
     *             unitType:   0表示单位ms；1表示单位us；2表示单位1，即直接操作load寄存器模式
     *
     *  输出参数  : 无
     *  返 回 值  : int
     *
     *  修改历史      :
     *      1.日    期   : 2012年7月19日
     *        作    者   : 荆耀辉 00179452
     *        修改内容   : 新生成函数
     *
     ******************************************************************************/
    int mdrv_timer_start(unsigned int usrClkId, FUNCPTR_1 routine, int arg,
            unsigned int timerValue, DRV_TIMER_MODE_E mode,  DRV_TIMER_UNIT_E unitType);

    /*****************************************************************************
     *  函 数 名  : mdrv_timer_stop
     *  功能描述  : 封装给协议栈的用户时钟定时器停止函数
     *  输入参数  : usrClkId:时钟ID,取值0~19
     *  输出参数  : 无
     *  返 回 值  : int
     *
     *  修改历史      :
     *      1.日    期   : 2012年7月19日
     *        作    者   : 荆耀辉 00179452
     *        修改内容   : 新生成函数
     *
     ******************************************************************************/
    int mdrv_timer_stop(unsigned int usrClkId);

    /*****************************************************************************
     *  函 数 名  : mdrv_timer_get_rest_time
     *  功能描述  : 获取定时器的剩余时间
     *  输入参数  : usrClkId:时钟ID,取值0~19
     *              unitType
     *              pRestTime
     *  输出参数  : 无
     *  返 回 值  : int
     *
     *  修改历史  :
     *      1.日    期   : 2012年7月19日
     *        作    者   : 荆耀辉 00179452
     *        修改内容   : 新生成函数
     *
     ******************************************************************************/
    int mdrv_timer_get_rest_time(unsigned int usrClkId, unsigned int unitType, unsigned int * pRestTime);

    /*****************************************************************************
     *  函数  : BSP_BBPGetCurTime
     *  功能  : 获取BBP定时器的值。用于OAM 时戳
     *  输入  : void
     *  输出  :
     *           pulLow32bitValue:    指针参数不能为空，否则会返回失败。
     *           pulHigh32bitValue:   如果为空， 则只返回低32bit的值。
     *  返回  : int
     ******************************************************************************/
    int mdrv_timer_get_accuracy_timestamp(unsigned int *pulHigh32bitValue, unsigned int *pulLow32bitValue);

    /************************************************************************
     *  FUNCTION
     *       mdrv_timer_get_normal_timestamp
     * DESCRIPTION
     *       GetSliceValue
     * INPUTS
     *       NONE
     * OUTPUTS
     *       NONE
             获取时间戳，时间戳返回值为递增值
     *************************************************************************/
    unsigned int mdrv_timer_get_normal_timestamp(void);
	/************************************************************************
     *  FUNCTION
     *       mdrv_timer_get_hrt_timestamp
     * DESCRIPTION
     *       GetHrtSliceValue
     * INPUTS
     *       NONE
     * OUTPUTS
     *       NONE
             获取高精度时间戳，规格最小满足精度0.5us，时间戳返回
             值为递增值,系统深睡会停止计时(lixiaojie\gebaizhang\xiajun讨论添加)
     *************************************************************************/
	unsigned int mdrv_timer_get_hrt_timestamp(void);

#ifdef __cplusplus
}
#endif
#endif
