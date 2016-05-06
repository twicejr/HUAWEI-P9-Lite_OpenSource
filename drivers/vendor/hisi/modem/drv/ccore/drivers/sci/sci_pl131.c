/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  sci_pl131.c
*
*   作    者 :  Y00171698
*
*   描    述 :  本文件命名为"sci_pl131.c", 为ARM公司提供的sample code
*            做了部分改动。
*
*   修改记录 :  
*************************************************************************/
/*lint --e{944,506,525,64,119,101,132,537,958,438,830,752,762,713,732,534,550,650,715,734,774,826,831,830,539,568} */

/* ecs */
#include "osl_thread.h"
#include "osl_sem.h"
#include "osl_malloc.h"
#include "product_config.h"
#include "osl_types.h"
#include "osl_bio.h"
#include "mdrv_timer.h"
#include "mdrv_sci.h"
#include "bsp_om.h"
#include "bsp_dump_def.h"
#include "bsp_sci.h"
#include "sci_debug.h"
#include "sci_pl131.h"
#include "sci_apbitops.h"
#include "sci_appl131.h"
#include <bsp_hardtimer.h>

/*
 * Description:
 * Limitted the activation times
 */
u8 nActiveT = 0;

/*Date:2006-9-21, Modification:A32D06010, Author:H55798, Changed for SIM Card compatibility. End*/

/*
 * Description:
 * To get the MAX byte number allowed in I-Block
 */
//unsigned long IFSC;
/* --------Data declarations--------
 */

/*
 * Description:
 * Global CH Time Out(WWT) offset value, add to micro adjust WWT for GCF.
 * Default value is set zero.
 */
const int g_ulChTimeOffset = 12;
/*Date:2006-9-21, Modification:A32D03058, Author:H55798, End*/

/*
 * Description:
 * Settings for clock rate conversion and bit rate adjustment from ISO7816-3:1997
 */
static const unsigned short PL131_ClkRateConv[] =
{ 372, 372, 558, 744, 1116, 1488, 1860, 0, 0, 512, 768, 1024, 1536, 2048, 0, 0 };
static const unsigned char PL131_BitRateAdj[] =
{   0, 1, 2, 4, 8, 16, 32, 0, 12, 20, 0, 0, 0, 0, 0, 0 };

ATR_sBuffer g_strATRData;  /* cann't init zero because byte overrun */

SCI_ATRINFO_S g_sci_atr_info = {T0_PROTOCOL_MODE,32,32,T1_ERR_DETECT_MODE_LRC,0};
//CharcterTimeGraud g_ChrTimeInfo;


PL131_PPS_STATE g_Pl131_pps_state = {0,0,0,0,0,0};
PL131_T1_TIMES g_t1_times = {PL131_DEF_CHARTIME_T1,PL131_DEF_BLOCKTIME_T1,PL131_DEF_BLKGUARDTIME_T1};
extern u32 g_sci_no_atr;
extern u32 g_u32ResetSuccess ;
extern BSP_BOOL g_SciDeactivateFlag ;

/*
 * Description:
 * To hold the TA2 data in ATR
 */
//unsigned char ucTA2Data;

/*
 * Description:
 * To flag the mode of operation in ATR.
 */
//SCI_MODE_OF_OPERATION ucModeOfOperation;

/*
 * Description:
 * To flag that we initiate a PPS process.
 * 0 means not in PPS process, 1 means we are in PPS process*
 */
//u8 PL131_PPS_ACTIVATION = 0;

/*
 * Description:
 * To flag that we are doing a PPS_Response process.
 * 0 means not in PPS_Response process, 1 means we are in PPS_Response process*
 */
//u8 PL131_PPS_Response = 0;



//static u8 ucTA1Flag = 0;

/*0 means TA1 == '11', need no PTS process
 *1 means TA1 == '94', PTS data is 'FF' '10' '94' '7B'
 *2 means TA1 == others, PTS data is 'FF' '00' 'FF'
 */

//static u8 ucPTSFlag   = 0;

/*
 * Description:
 * Baud rate set flag
 * 0 means TA1 == '11', need no PTS process
 * 1 means TA1 is not supported or invalid, PTS data is 'FF' '00' 'FF'
 * 2 means TA1 == others that supported by ME
 */
//u8 ucTA1Flag = 0;

/*
 * Description:
 * The flag to count the PPS process times
 */
//u8 ucPPSFlag = 0;

//u8 TotalT14ATR = 0;



/*
 * Description:
 * SCI Class Type
 */
//extern SCI_Class_Of_Type sciClassKind;

/*
 * Description:
 * SCI Class Switch Flag
 */
//extern unsigned char ucSCI_CLASS_SWITCH_FLAG;

/*Date:2006-9-21, Modification:A32D06010, Author:H55798, Changed for SIM Card compatibility. Begin*/

/*
 * Description:
 * Synchronous semphor for power class switch or PPS process
 */
extern osl_sem_id g_SCISynSem;

extern sci_debug_str  g_sci_debug_base;

extern apPL131_eClockMode g_ulSciClkTimeStpFlag;
extern SCI_DETECT_STATE_E g_sci_detect_state ;
extern SCI_HOT_PLUG_PROC_STATUS g_sci_hot_plug_proc_status;




/* 回调函数注册函数指针*/
extern Sci_Event_Func g_FuncCb;
extern osl_sem_id g_SCIClockStartSem;
extern SCI_STATE_STRU g_strSciState;
extern u32 g_SciExcResetTimes;
extern u32 g_ulSciGcfStubFlag;


extern SCI_CFG_STRU g_stSciHwCfg;

extern SCI_VOLTAGE_STATE g_sci_voltage_state;

extern int QueueLoopIn(dump_queue_t *Q, UINT32 element);

static STATUS  appl131_driver_enable(SCI_STATE_STRU * parapState);
static void    pl131_bit_duration(SCI_STATE_STRU * parapState, u32 EtuNum, u32 EtuDen);
static void    pl131_atr_param_set (SCI_STATE_STRU * parapState,
                                  u32              ATRGrouping,
                                  u32              ATRCurrent,
                                  u32              ATRCharacter);

STATUS appl131_bit_duration_set(SCI_STATE_STRU *       pState,
                              apPL131_eClockRateConv eClockRateConversion,
                              apPL131_eBitRateAdj    eBitRateAdjustment);
void pl131_reset_wwt (SCI_STATE_STRU * parapState);
extern void sci_class_switch_sence_try(void);
extern void sci_check_current_state(PL131_eStateOptions eCurrentState);

/*****************************************************************************
* 函 数 名  : appl131_driver_enable
*
* 功能描述  : 使能SCI的驅動
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
static STATUS appl131_driver_enable(SCI_STATE_STRU * parapState)
{
    /* Create pointers to the instance data block and the register base */
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    if (apERR_PL131_NOTINIT == appl131_clean(pState))
    {
        return (STATUS) apERR_PL131_NOTINIT;
    }

    apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0x7FF);
    return apERR_NONE;
}

/*****************************************************************************
* 函 数 名  : appl131_driver_disable
*
* 功能描述  : 禁用SCI的驅動
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_driver_disable(SCI_STATE_STRU * parapState)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    //__BSP_ASSERT__(parapState);

    if ((pState->eCurrentState == PL131_STATE_UNINIT) || !pBase)
    {
        return (STATUS) apERR_PL131_NOTINIT;
    }

    apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0);

    appl131_clean(pState);

    apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 0); /*disable RX interrupt*/
    
    pState->eCurrentState = PL131_STATE_DISABLED;
    return apERR_NONE;
}

/*****************************************************************************
* 函 数 名  : appl131_params_set
*
* 功能描述  : 設定相關參數
*
* 输入参数  :SCI_STATE_STRU               *parapState 全局狀態
         unsigned char * const         pATRBuffer ATR接收BUF
         apPL131_rCallBack             rCallBack,
         const apPL131_sSetupParams    *pSetupParams 設置參數
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_params_set(SCI_STATE_STRU    *         parapState,
                         u8 * const              pATRBuffer,
                         apPL131_rCallBack           rCallBack,
                         const apPL131_sSetupParams *pSetupParams)
{
    /* Create pointers to the instance data block and the register base */
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    /* any error in initialisation */
    STATUS ErrInInit = apERR_NONE;

    if ((pState->eCurrentState == PL131_STATE_UNINIT) || !pBase)
    {
        sci_print_error("current state is un-init\n");

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        return (STATUS) apERR_PL131_NOTINIT;
    }

    /*copy the setup parameters*/
    if (pSetupParams)
    {
        pState->sSetupParams = *pSetupParams;
    }

    /*check the clock frequency is legal*/
    if (pState->sSetupParams.ClockFreq < 2000UL)
    {
        sci_print_error("reference clock frequency isn't legal.\n");

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        return (STATUS) apERR_PL131_INVALIDFREQ;
    }

    /*deactivate the interrupts*/
    /*mask all the interrupts*/
    apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0);

    /*store the details*/
    pState->sATRParams.pATRBuffer = pATRBuffer;

    /*reset according to the parameters*/
    ErrInInit = pl131_registers_init(pState);
    if ((ErrInInit != apERR_NONE) && (ErrInInit != apERR_PL131_USEDEFAULT))
    {
        sci_print_error("for code review : register init is error. ErrInInit is 0x%x\n", ErrInInit, 0, 0, 0, 0, 0);
    }

    /*state is now valid */
    pState->eCurrentState = PL131_STATE_INACTIVECARD;

    /*activate the clearable interrupts*/

    //apBIT_SET(pBase->RegCtrl0,PL131_REGCTRL0_CLKDIS ,1);
    apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0x7FF);

    /*return the error code*/
    return ErrInInit;
}

/*****************************************************************************
* 函 数 名  : pl131_registers_init
*
* 功能描述  : 將寄存器設定為默認值
*
* 输入参数  :SCI_STATE_STRU * parapState當前狀態的全局變量
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS pl131_registers_init(SCI_STATE_STRU * parapState)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    /*a parameter is invalid and the default is used*/
    BOOL InvalidParam = FALSE;

    /*a parmeter and default is invalid*/
    BOOL InvalidDefault = FALSE;

    /* for T14  */
    u32 PAdjust = 0;

    /*消除告警*/
    u32 u32DefaultActevent  = PL131_DEF_ACTEVENT;
    u32 u32DefaultATRSTime  = PL131_DEF_ATRSTIME;
    u32 u32DefaultATRDTime  = PL131_DEF_ATRDTIME;
    u32 u32DefaultBlockTime = PL131_DEF_BLOCKTIME;
    u32 u32DefaultBlkGuardTime = PL131_DEF_BLKGUARDTIME;
    u32 u32DefaultStopTime  = PL131_DEF_STOPTIME;
    u32 u32DefaultStartTime = PL131_DEF_STARTTIME;

    /*************************************************************
     *    Check the clock setting is valid.
     *          Refclock                          Refclock
     *   F = ------------- x 2  ==> CLKICC = 2 x ---------- - 1
     *        (CLKICC + 1)                            F
     ************************************************************/
    if (pState->sSetupParams.CardFreq
        && (((pState->sSetupParams.ClockFreq / pState->sSetupParams.CardFreq) / 2 - 1)
            <= apBIT_MASK(PL131_REGCLKICC_DATA)))
    {
        //bsp_trace1(SCI_LOG_LEVEL_DEBUG, "The value of pState->sSetupParams.CardFreq is %ld.\n", (int)pState->sSetupParams.CardFreq);
    }
    /*check the default value*/
    else if (((pState->sSetupParams.ClockFreq / g_stSciHwCfg.sci_freq.sci_work_freq) / 2 - 1) <= apBIT_MASK(PL131_REGCLKICC_DATA))
    {
        pState->sSetupParams.CardFreq = g_stSciHwCfg.sci_freq.sci_work_freq;
        InvalidParam = TRUE;
    }
    /*fail*/
    else
    {
        sci_print_debug("Check the clock setting isn't valid.\n");
        InvalidDefault = TRUE;
    }

    PAdjust = 1000UL;

    if (!InvalidDefault)
    {
        /*setting clock*/
        pBase->RegClkICC = (pState->sSetupParams.ClockFreq / pState->sSetupParams.CardFreq) / 2 - 1;

        /*
         * Initialising smartcard settings uses the macro PL131_REG_DATA_WRITE
         * This is passed the requested data and default value.
         * It sets the InvalidParam flag TRUE if the requested data is invalid
         * and the default is used.
         * If the data is invalid and the default is also invalid then
         * InavlidDefault is set TRUE and aborts with apERR_SCI_INVALIDFREQ.
         */

        /*Debounce time*/
        PL131_REG_DATA_WRITE(pBase->RegStable,
                             0,
                             apBIT_MASK(PL131_REGSTABLE_DATA),
                             (pState->sSetupParams.ClockFreq / ((1 << 16) - 1)),
                             sSetupParams.DebounceTime,
                             PL131_DEF_DEBOUNCE,
                             InvalidParam,
                             InvalidDefault);

        /*Activation event time*/
        PL131_REG_DATA_WRITE(pBase->RegATime,
                             40, /**** This parameter has been reduced to enable simulation speed ****/
                             45000,
                             1,
                             sSetupParams.ActEventTime,
                             u32DefaultActevent,
                             InvalidParam,
                             InvalidDefault);

        /*Deactivation event time*/
        PL131_REG_DATA_WRITE(pBase->RegDTime,
                             0,
                             (MIN(apBIT_MASK(PL131_REGDTIME_DATA), (333 * pState->sSetupParams.CardFreq) / PAdjust)),
                             (pState->sSetupParams.CardFreq / PAdjust),
                             sSetupParams.DeactEventTime,
                             PL131_DEF_DEACTEVENT,
                             InvalidParam,
                             InvalidDefault);

        /*ATR start time*/
        PL131_REG_DATA_WRITE(pBase->RegATRSTime,
                             0,
                             apBIT_MASK(PL131_REGATRSTIME_DATA),
                             1,
                             sSetupParams.ATRStartTime,
                             u32DefaultATRSTime,
                             InvalidParam,
                             InvalidDefault);

        /*ATR duration*/
        PL131_REG_DATA_WRITE(pBase->RegATRDTime,
                             0,
                             apBIT_MASK(PL131_REGATRDTIME_DATA),
                             1,
                             sSetupParams.ATRDuration,
                             u32DefaultATRDTime,
                             InvalidParam,
                             InvalidDefault);

        /*enable timeout unless time is zero*/
        apBIT_SET(pState->pBase->RegCtrl1, PL131_REGCTRL1_ATRDEN, (pState->sSetupParams.ATRDuration != 0));

        /*Character to character duration time*/
        /* 两个连续字符上升沿之间的延迟至少是12etu*/
        /* 在复位应答期间,卡发出的两个连续字符的上升沿间的延迟应不超过9600etu,*/
        PL131_DBL_REG_DATA_WRITE(pBase->RegChTime,
                                 13,
                                 apBIT_MASK(PL131_REGCHTIME_DATA),
                                 1,
                                 sSetupParams.CharacterTime,
                                 (PL131_DEF_CHARTIME - 12 + g_ulChTimeOffset),     /*Add offset value: g_ulChTimeOffset, default value set is zero*/
                                 InvalidParam,
                                 InvalidDefault);

        /*Receive timeout between blocks*/
        PL131_DBL_REG_DATA_WRITE(pBase->RegBlkTime,
                                 13,
                                 apBIT_MASK(PL131_REGBLKTIME_DATA),
                                 1,
                                 sSetupParams.BlockTime,
                                 (u32DefaultBlockTime),                         /* 逻辑不会自动+12，所以直接赋值，不-12 */
                                 InvalidParam,
                                 InvalidDefault);

        /*Minimum time between characters in oposite directions*/
        PL131_REG_DATA_WRITE(pBase->RegBlkGuard,
                             (16 - 12),
                             apBIT_MASK(PL131_REGBLKGUARD_DATA),
                             1,
                             sSetupParams.BlockGuard,
                             (u32DefaultBlkGuardTime),                          /* 逻辑不会自动+12，所以直接赋值，不-12 */
                             InvalidParam,
                             InvalidDefault);

        /*receive timeout*/
        PL131_REG_DATA_WRITE(pBase->RegRxTime,
                             1,
                             apBIT_MASK(PL131_REGRXTIME_DATA),
                             (pState->sSetupParams.CardFreq / PAdjust),
                             sSetupParams.ReceiveTime,
                             PL131_DEF_RXTIME,
                             InvalidParam,
                             InvalidDefault);

        /*Clock stop mode Stop timeout*/
        PL131_REG_DATA_WRITE(pBase->RegStopTime,
                             1860,
                             apBIT_MASK(PL131_REGSTOPTIME_DATA),
                             1,
                             sSetupParams.StopTime,
                             u32DefaultStopTime,
                             InvalidParam,
                             InvalidDefault);

        /*Clock stop mode Start timeout*/
        PL131_REG_DATA_WRITE(pBase->RegStartTime,
                             700,
                             apBIT_MASK(PL131_REGSTARTTIME_DATA),
                             1,
                             sSetupParams.StartTime,
                             u32DefaultStartTime,
                             InvalidParam,
                             InvalidDefault);
        pBase->RegChGuard = 1;
    }

    /*any of the registers won't accept defaults means clock is too high*/
    if (InvalidDefault)
    {
        sci_print_error("any of the registers won't accept defaults means clock is too high.\n");

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        return (STATUS) apERR_PL131_INVALIDFREQ;
    }

    /*any other settings from the setup data*/
    apBIT_SET(pBase->RegTide, PL131_REGTIDE_RX, 0x1);
    apBIT_SET(pBase->RegTide, PL131_REGTIDE_TX, 0x0);

    /*The handshaking enums are set up to match the bit patterns here*/
    apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_RX, pState->sSetupParams.eRxHandshake);
    apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_TX, pState->sSetupParams.eTxHandshake);

    /* BEGIN: Modified by z67193, 2010-8-24 , 复位应答期间设置为0*/
    apBIT_SET(pBase->RegRetry, PL131_REGRETRY_RX, 0);
    apBIT_SET(pBase->RegRetry, PL131_REGRETRY_TX, 0);

    /* BEGIN: Modified by z67193, 2010-9-2 GCF测试7.2.1，返回ATR时，CHDTIME=9600etu，导致ATRDTIME超时*/
    if (g_ulSciGcfStubFlag)
    {
        //initialize od/cmos
        pBase->RegCtrl1 = (pState->sSetupParams.ClockIsOpenDrain ?
                           apBIT_MASK(PL131_REGCTRL1_CLKZ1) : 0);/*set open drain/buffered clock*/
    }
    else
    {
        //initialize od/cmos
        pBase->RegCtrl1 = apBIT_MASK(PL131_REGCTRL1_ATRDEN) | (pState->sSetupParams.ClockIsOpenDrain ?
                                                               apBIT_MASK(PL131_REGCTRL1_CLKZ1) : 0);/*set open drain/buffered clock*/
    }


    /*clear existing interrupt flags*/
    pBase->RegIntClear = 0x1FFF;

    pl131_bit_duration(pState,
                      PL131_ClkRateConv[apPL131_F_372],
                      PL131_BitRateAdj[apPL131_D_1]);

    //enable bgten bit
    apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_BGTEN, 1);

    return (STATUS) (InvalidParam ? (apERR_PL131_USEDEFAULT) : (apERR_NONE));
}

/*****************************************************************************
* 函 数 名  : appl131_bit_duration_set
*
* 功能描述  : 設定波特率
*
* 输入参数  :SCI_STATE_STRU *         pState,當前狀態
         apPL131_eClockRateConv   eClockRateConversion  F
         apPL131_eBitRateAdj      eBitRateAdjustment    D
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/

STATUS appl131_bit_duration_set(SCI_STATE_STRU *       pState,
                              apPL131_eClockRateConv eClockRateConversion,
                              apPL131_eBitRateAdj    eBitRateAdjustment)
{
    if (
        (PL131_ClkRateConv[eClockRateConversion] == 0)
       || (PL131_BitRateAdj[eBitRateAdjustment] == 0)
    )
    {
        sci_print_error("PL131_ClkRateConv[eClockRateConversion] = %d and  PL131_BitRateAdj[eBitRateAdjustment] = %d.\n",
                  PL131_ClkRateConv[eClockRateConversion], PL131_BitRateAdj[eBitRateAdjustment], 0, 0, 0, 0);
        return (STATUS) apERR_PL131_INVPARAM;
    }

    pl131_bit_duration(pState,
                      PL131_ClkRateConv[eClockRateConversion],
                      PL131_BitRateAdj[eBitRateAdjustment]);

    return apERR_NONE;
}

/******************************************************************************
 * Function:      pl131_bit_duration
 * Description:   setting baud rate clock register
 * Input:         F and D
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
static void pl131_bit_duration(SCI_STATE_STRU *parapState,
                              u32          ClkRateConv,
                              u32          BitRateAdj)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    /*used for calculating baud rate*/

    //    u32 BaudTotal, BaudValue;
    u32 BaudTotal, SciValue, temp, SciBaud, missError;
    u32 flag = 0;

    /* record_008 for division by zero in kernel. */
    if ((BitRateAdj == 0) || (ClkRateConv == 0))
    {
        sci_print_error("ClkRateConv = %d and  BitRateAdj = %d.\n",
                  ClkRateConv, BitRateAdj, 0, 0, 0, 0);
        pState->eCurrentState = PL131_STATE_INACTIVECARD;
        return;
    }

    /*
     *set baud clock frequency.  This must be set as:
     * (1 + BAUD) * VALUE = Reference freq / Card Clock Freq * (ClkRateConv / BitRateAdj)
     */
    BaudTotal = (pState->sSetupParams.ClockFreq / pState->sSetupParams.CardFreq) * ClkRateConv;

    SciValue = PL131_DEF_MIN_BAUDVALUE;

    temp = SciValue * BitRateAdj;  /*BAUD=BaudTotal/temp -1*/

    /*查看是否可以整除，且BAUD>=1*/
    while ((temp <= (BaudTotal / 2)) && (SciValue <= PL131_DEF_MAX_BAUDVALUE))
    {
        if (0 == (BaudTotal % temp))/*BAUD取值可以整除*/
        {
            flag = 1;
            break;
        }

        SciValue++;
        temp = SciValue * BitRateAdj;
    }

    if (!flag)/*不能整除,则需要寻找合适的SciValue，使误差小于2%*/
    {
        SciValue = PL131_DEF_MIN_BAUDVALUE;
        temp = SciValue * BitRateAdj;

        /*寻找合适的SciValue，满足误差要求*/
        while ((temp <= (BaudTotal / 2)) && (SciValue <= PL131_DEF_MAX_BAUDVALUE))
        {
            SciBaud   = (BaudTotal * 100) / temp;/*乘以100，是计算结果扩大100倍*/
            missError = (SciBaud % 100) + 1;

            if ((missError * 50) < SciBaud)/*误差小于2%*/
            {
                flag = 1;

                /*OSAL_LogMsg("find the baud!\n",0,0,0,0,0,0);*/
                break;/*找到了*/
            }

            SciValue++;
            temp = SciValue * BitRateAdj;
        }

        if (!flag)/*没有找到，使用默认值*/
        {
            SciValue = PL131_DEF_MIN_BAUDVALUE;
        }
    }

    SciBaud = (BaudTotal / (SciValue * BitRateAdj)) - 1;

    apBIT_SET(pBase->RegBaud, PL131_REGBAUD_DATA, SciBaud);
    apBIT_SET(pBase->RegBaudValue, PL131_REGBAUDVALUE_DATA, SciValue);

    /*
     * set baud clock frequency. This must be set as:
     *             F     1       (1 + SCIBAUD)
     *    1 etu = --- * --- = -------------------- * SCIVALUE
     *             f     D      Reference clock
     *
     *             Reference clock
     *      f = --------------------
     *           (SCICLKICC + 1) * 2
     *
     *                                      F
     *      ==> (1 + SCIBAUD) * SCIVALUE = --- * (SCICLKICC + 1) * 2
     *                                      D
     */
}

/******************************************************************************
 * Function:      appl131_card_active_set
 * Description:   ACTIVATION AND DEACTIVATION
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
STATUS appl131_card_active_set(SCI_STATE_STRU *parapState,
                             BOOL            SetActive,
                             unsigned char * const  pATRBuffer)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    /*any error in flushing buffers*/
    STATUS ErrReturn = apERR_NONE;

    /*limited the times of activation sequence*/
    if (nActiveT > SCI_MAX_USIM_CARD_DETECT_RETRY_CNT)
    {
        /*Changed for Card Status Type Error, Change Begin*/
        if (g_sci_voltage_state.sciClassKind == PL131_SCI_Class_C)
        {
            sci_print_debug("Although Card Activation time is more than 8, but we do class switch here before we do Card Truly Deactivation Process!\n");
            g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_PROCESS;

            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pState->eCurrentState, __LINE__);
            g_sci_voltage_state.sci_vlotage_switch_sense= SCI_VOLTAGE_SWITCH_SENSE_CLASS_C2B_IMMEDIATELY;
            SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
            apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);

            pState->eCurrentState = PL131_STATE_INACTIVECARD;

            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        }
        else
        {
            /*Set SCI Current State is NOCARD*/
            sci_print_debug("\r\n no card is the state ");
            
            SCI_RECORD_EVENT(SCI_EVENT_ERROR_NOCARD, parapState->eCurrentState, __LINE__);

            SCI_RECORD_EXCGBL(SCI_EVENT_ERROR_NOCARD, parapState->eCurrentState, bsp_get_slice_value());
            pState->eCurrentState = PL131_STATE_NOCARD;
            apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pState->eCurrentState, __LINE__);

            g_SciDeactivateFlag = true;
        }

        (BSP_VOID)appl131_clean(pState);          /*terminate transfer*/
        (BSP_VOID)pl131_registers_init(pState);    /*restore state*/

        /*NOTIFICATION - card has been deactivated, do Card deactivate*/
        sci_print_debug("appl131_card_active_set: nActiveT > 7 Card Activation time is more than limit times, so do Deactivation Process No3 here!\n");
   

        return MDRV_ERROR;

        /* Changed for Card Status Type Error, Change End*/
    }

    nActiveT++;

    g_strATRData.ulATRLen = 0;

    /*automatically enable the driver*/
    if (pState->eCurrentState == PL131_STATE_DISABLED)
    {
        appl131_driver_enable(pState);
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
    }

    if (apBIT_GET(pBase->RegCtrl0, PL131_REGCTRL0_CLKDIS) == 1)
    {
        apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKDIS, 0);
        apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_CLKACTI, 1);
    }

    /*reset the pointers for ATR*/
    pState->sATRParams.pATRBuffer = pATRBuffer;           /*set the buffer*/
    pState->sATRParams.Grouping = PL131_ATR_GROUPSTART;   /*ready for ATR*/
    pState->sATRParams.BufferAt = 0;                      /*reset counter for ATR buffer*/

    /*reset convention incase last card used inverse*/
    pState->eConvention = PL131_CONVENTION_DIRECT;

    /*check the current state*/
    switch (pState->eCurrentState)
    {
        /*error states*/
    case PL131_STATE_UNINIT:
    {
        sci_print_error("smartcard's state isn't init.\n");

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        
        return (STATUS) apERR_PL131_NOTINIT;
    }
    case PL131_STATE_NOCARD:
    {
        sci_print_error("smartcard's state is no card.\n");

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);

        return (STATUS) apERR_PL131_NOCARD;
    }

        /*if inactive, perform an activate*/
    case PL131_STATE_INACTIVECARD:
    {
        if (SetActive)
        {
            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
            
            /*deactivate the interrupts*/
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0);

            /*reset convention incase last card used inverse*/
            apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CONV, PL131_CONVENTION_DIRECT);

            ErrReturn = pl131_registers_init(pState);
            if (!ErrReturn || (ErrReturn == apERR_PL131_USEDEFAULT))
            {
                ErrReturn = appl131_clean(pState);

                SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
            }

            if (ErrReturn != apERR_PL131_INVALIDFREQ)
            {
                pState->eCurrentState = PL131_STATE_INACTIVECARD;

                /*execute the cold reset*/
                apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_STARTUP, 1);
                apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_WRESET, 1);

                SCI_RECORD_EVENT(SCI_EVENT_REGISTER_COLD_RESET, pState->eCurrentState, __LINE__);
            }

            /*activate the interrupts*/
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0x7FF);           /*enable general interrupts*/
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 1);           /*enable RX interrupt*/

           
        }
        else
        {
            apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);/* [false alarm]:fortify */

            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pState->eCurrentState, __LINE__);
        }

        break;
    }

        /*if active, perform a warm reset*/
    default:
    {
        ErrReturn = appl131_clean(pState);

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);

        if (SetActive)
        {
            if (pState->eProtocol == apPL131_PROTOCOL_T0_CHAR)
            {
                pState->sSetupParams.CardFreq = g_stSciHwCfg.sci_freq.sci_work_freq;
                pBase->RegClkICC = (pState->sSetupParams.ClockFreq / pState->sSetupParams.CardFreq) / 2 - 1;

                pl131_bit_duration(pState,
                                  PL131_ClkRateConv[apPL131_F_372],
                                  PL131_BitRateAdj[apPL131_D_1]);

                SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
            }

            pState->eCurrentState = PL131_STATE_READATR;
            apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_WRESET, 1);

            /*activate the interrupts*/
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_ALL, 0x7FF);           /*enable general interrupts*/
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 1);   /*enable RX interrupt*/
            

            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_WARM_RESET, pBase->RegIntMask, __LINE__);

        }
        else
        {
            pState->eCurrentState = PL131_STATE_INACTIVECARD;/* [false alarm]:fortify */
            apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);/* [false alarm]:fortify */
            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pState->eCurrentState, __LINE__);/* [false alarm]:fortify */

        }
    }
    }

    return ErrReturn;
}

/******************************************************************************
 * Function:      appl131_clean
 * Description:   clean
 * Input:
 * Output:
 * Return:
 * Others:
 *****************************************************************************/
STATUS appl131_clean(SCI_STATE_STRU * parapState)
{
    /* Create pointers to the instance data block and the register base */
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    //__BSP_ASSERT__(parapState);

    /*check the current state and abort if incorrect*/
    if ((PL131_STATE_UNINIT == pState->eCurrentState) || !pBase)
    {
        sci_print_error("smartcard's state isn't init.\n");
        return (STATUS) apERR_PL131_NOTINIT;
    }

    /*clear the data buffer*/
    pState->DataLength  = 0;
    pState->pDataBuffer = NULL;

    /*flush FIFOs - any values here will clear the FIFOs*/
    pBase->RegTxCount = apBITS_ALL;
    pBase->RegRxCount = apBITS_ALL;

    /*clear all interrupts except card moving*/
    apBIT_SET(pBase->RegIntClear,
              PL131_REGINTMASK_ALL,
              ~(apBIT_MASK(PL131_REGINTMASK_CARDIN) | apBIT_MASK(PL131_REGINTMASK_CARDOUT)));

    /*mark as receiving*/
    apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_MODE, apPL131_RX_FROM_CARD);

    /*enable RX interrupt*/
    apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 1);

    if (pState->eCurrentState > PL131_STATE_READY)
    {
        pState->eCurrentState = PL131_STATE_READY;
    }

    return apERR_NONE;
}

/*****************************************************************************
* 函 数 名  : appl131_data_transfer
*
* 功能描述  : 本接口用于數據發送
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_data_transfer (SCI_STATE_STRU *       parapState,
                             apPL131_eDataDirection eDirection,
                             u8 * const         pDataBuffer,
                             u32                 DataLength)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;
    apPL131_eError ErrorReturn = (apPL131_eError) apERR_NONE;
    apPL131_eClockMode ulClkStart = apPL131_CLOCK_START;
    int lClkCurState = (int)apPL131_CLOCK_START;


    /*check the current state and abort if incorrect
     *for clarity, this case statement has been compacted and
     *the break or fall-through comments removed
     */
    switch (pState->eCurrentState)
    {
    case PL131_STATE_DISABLED:
        ErrorReturn = apERR_PL131_DISABLED;
        break;
    case PL131_STATE_UNINIT:
        ErrorReturn = apERR_PL131_NOTINIT;
        break;
    case PL131_STATE_NOCARD:
        ErrorReturn = apERR_PL131_NOCARD;
        break;
    case PL131_STATE_READY:
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        break;
    default:
        sci_print_error("smartcard's state cann't execute send/receive opertaion before smartcard's state is equal to three., state is 0x%x\n",
                  pState->eCurrentState, 0, 0, 0, 0, 0);
        ErrorReturn = apERR_PL131_NOTREADY;
        break;
    }

    /*check for valid parameters*/
    if (!ErrorReturn && (!pDataBuffer || !DataLength))
    {
        SCI_RECORD_EVENT(SCI_EVENT_ERROR_NODATA, pState->eCurrentState, __LINE__);
        
        ErrorReturn = apERR_PL131_NODATA;
    }

    if (ErrorReturn)
    {
        sci_print_error("apPL131_DataTransfer, state is 0x%x\n",
                  ErrorReturn, 0, 0, 0, 0, 0);
        
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        return (STATUS) ErrorReturn;
    }
    if(g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {       
        sci_print("status not statify\n");
        return BSP_ERR_SCI_NOTINIT;
    }


    sci_lowpower_vote_lock(SCI_LOWPWR_USIM);
    SCI_RECORD_EVENT(SCI_EVENT_LOW_POWER_EXIT, SCI_LOWPWR_USIM , __LINE__);

    /*store the transfer parameters*/
    pState->DataLength  = DataLength;
    pState->pDataBuffer = pDataBuffer;


    /*mark as transmitting or receiving*/
    apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_MODE, eDirection);

    /*reinitialise the FIFO - TIDE interrupts will start now*/
    if (eDirection == apPL131_TX_TO_CARD)
    {       
        lClkCurState = apBIT_GET(pBase->RegCtrl0, PL131_REGCTRL0_CLKDIS);/* [false alarm]:*/
        if (lClkCurState & 0x1)
        {
            SCI_RECORD_EVENT(SCI_EVENT_CLK_START, ErrorReturn, __LINE__);
            if ((ErrorReturn = (apPL131_eError)appl131_clock_stop_mode_set(pState, ulClkStart, 0)) != apERR_NONE)
            {
                SCI_RECORD_EVENT(SCI_EVENT_CLK_ERROR, ErrorReturn, __LINE__);
                sci_print("ErrorReturn\n");
                return ErrorReturn;
            }

            /* BEGIN: Modified by z67193, 2010-8-21 使用信号量等待时钟启动完毕*/
             /*   逻辑启动时钟需要等待700cycle, 1M时钟下，为700us，使用100ms作为超时阈值 */
              /*  从实践经验看，如果等待10ms，有可能会因为操作系统的tick误差而产生提前超时*/
          /*     使用20ms则不会出现误差，为确保正常，使用100ms*/
            
            if(BSP_OK != osl_sem_downtimeout(&g_stSciHwCfg.sci_sem.g_SCIClockStartSem, 10))/* [false alarm]:*/
            {
                SCI_RECORD_EVENT(SCI_EVENT_CLK_ERROR, ulClkStart, __LINE__);
                
                sci_print_error("apPL131_DataTransfer:clk start error\n",pState->eCurrentState, 0, 0, 0, 0, 0);
 
            }

            /*Set Current SCI CLK Status Flag*/
            g_ulSciClkTimeStpFlag = apPL131_CLOCK_START;

            /*SCI_RECORD_EVENT(SCI_EVENT_CLK_START, (u32)ulClkStart, (u32)lClkCurState);*/
        }
        if(apPL131_CLOCK_STOP == g_ulSciClkTimeStpFlag)/* [false alarm]:*/
        {

            SCI_RECORD_EVENT(SCI_EVENT_CLK_STOP,g_ulSciClkTimeStpFlag,__LINE__);

            sci_print_error("apPL131_DataTransfer:set clk failed , state is 0x%x,g_ulSciClkTimeStpFlag is 1\n",
                      pState->eCurrentState, g_ulSciClkTimeStpFlag, 0, 0, 0, 0);
            return  apERR_PL131_NOTREADY;
        }

        SCI_RECORD_DATA(SCI_DATA_SEND_EVENT, (BSP_U8)(pState->DataLength), pState->pDataBuffer);

        
        pState->eCurrentState = PL131_STATE_TX;
        pBase->RegTxCount = apBITS_ALL;                   /*flush the counter*/


        /* DTS2011051001744 z67193, 发送数据的下水标修改为4，减少中断*/
        apBIT_SET(pBase->RegTide, PL131_REGTIDE_TX, 4);
        if (!apBIT_GET(pBase->RegDMACtrl, PL131_REGDMA_TX))
        {
            SCI_RECORD_EVENT(SCI_EVENT_DATA_TRANS, (u32)(g_strSciState.eCurrentState), __LINE__);
            
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_TXTIDE, 1); /*enable TX interrupt*/
        }
    }
    else
    {
        pState->eCurrentState = PL131_STATE_RX;/* [false alarm]:fortify */
        pBase->RegRxCount = apBITS_ALL;                   /*flush the counter*/
        apBIT_SET(pBase->RegTide, PL131_REGTIDE_RX, MIN(PL131_FIFO_SIZE_RX / 2, 1));
        if (apBIT_GET(pBase->RegDMACtrl, PL131_REGDMA_RX))
        {
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 0); /*disable RX interrupt*/
        }
        else
        {
            apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 1); /*enable RX interrupt*/
        }
        SCI_RECORD_EVENT(SCI_EVENT_API_DATA_REC_START, pState->eCurrentState, __LINE__);
    }

    return apERR_NONE;
}

/*****************************************************************************
* 函 数 名  : pl131_reset_wwt
*
* 功能描述  : 本接口用於重新設定WWT，更新pl131寄存器
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
* 备注：如果需要更新WWT，当前默认是T=0协议，因此到最后一定会把寄存器的值更新一遍，
* parapState->sSetupParams.CharacterTime里存储的都是T=0的值
* 当USIM确认支持T=1协议，并且使用T=1协议时，会将寄存器的值写成T=1的正确值
* T=1的正确值存储在g_t1_reg_times变量
*
*****************************************************************************/

void pl131_reset_wwt (SCI_STATE_STRU * parapState)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    if(0==PL131_BitRateAdj[parapState->sATRParams.eBitRateAdj])
    {
        sci_print_error("pl131_reset_wwt: 1: RegChTimeMS is %d, RegChTimeLs %d, eBitRateAdj is %d, wi is %d, CharacterTime is %d\n", parapState->pBase->RegChTimeMS, parapState->pBase->RegChTimeLS, parapState->sATRParams.eBitRateAdj, parapState->sATRParams.WI, parapState->sSetupParams.CharacterTime, 0);

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);
        return ;
    }
    
    parapState->sSetupParams.CharacterTime = 960
                                            * parapState->sATRParams.WI
                                            * PL131_BitRateAdj[parapState->sATRParams.eBitRateAdj];
    sci_print_info("pl131_reset_wwt: 1: RegChTimeMS is %d, RegChTimeLs %d, eBitRateAdj is %d, wi is %d, CharacterTime is %d\n", parapState->pBase->RegChTimeMS, parapState->pBase->RegChTimeLS, parapState->sATRParams.eBitRateAdj, parapState->sATRParams.WI, parapState->sSetupParams.CharacterTime, 0);

    /*if TC2 is got from ATR, or after PPS PROCESS, reset WWT here*/
    if ((pState->sSetupParams.CharacterTime != PL131_DEF_CHARTIME - 12 + g_ulChTimeOffset)
       && ((unsigned long)(pState->sSetupParams.CharacterTime) >= 1))
    {
        if (pState->eProtocol == apPL131_PROTOCOL_T0_CHAR)
        {
            pBase->RegChTimeMS = ((pState->sSetupParams.CharacterTime - 12
                                   + g_ulChTimeOffset) & 0xFFFF0000) >> 16;
            pBase->RegChTimeLS = ((pState->sSetupParams.CharacterTime - 12 + g_ulChTimeOffset) & 0x0000FFFF);
        }
        else
        {
            pBase->RegChTimeMS = ((pState->sSetupParams.CharacterTime - 11) & 0xFFFF0000) >> 16;
            pBase->RegChTimeLS = ((pState->sSetupParams.CharacterTime - 11) & 0x0000FFFF);
        }
        sci_print_info("pl131_reset_wwt: 2: RegChTimeMS is %d, RegChTimeLs %d, eBitRateAdj is %d, wi is %d, CharacterTime is %d\n", parapState->pBase->RegChTimeMS, parapState->pBase->RegChTimeLS, parapState->sATRParams.eBitRateAdj, parapState->sATRParams.WI, parapState->sSetupParams.CharacterTime, 0);
    }
    /*if TB3 is got from ATR, means T1 mode is used*/
    pState->sSetupParams.BlockTime = pState->sSetupParams.CharacterTime;
    if ((pState->sSetupParams.BlockTime != PL131_DEF_BLOCKTIME - 12)
       && (pState->sSetupParams.BlockTime >= 13))
    {
        if (pState->eProtocol == apPL131_PROTOCOL_T0_CHAR)
        {
            pBase->RegBlkTimeMS = ((pState->sSetupParams.BlockTime - 12) & 0xFFFF0000) >> 16;
            pBase->RegBlkTimeLS = ((pState->sSetupParams.BlockTime - 12) & 0x0000FFFF);
        }
        else
        {
            pBase->RegBlkTimeMS = ((pState->sSetupParams.BlockTime - 11) & 0xFFFF0000) >> 16;
            pBase->RegBlkTimeLS = ((pState->sSetupParams.BlockTime - 11) & 0x0000FFFF);
        }
    }
}

/*****************************************************************************
* 函 数 名  : pl131_atr_process
*
* 功能描述  : 本接口用於在ATR接收階段處理收到的每個ATR字節
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
void   pl131_atr_process (SCI_STATE_STRU * parapState, u32 CharATR)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;
    u32 i = 0;
    u32 temp = 0;
    int retVal;

    /*any failure in ATR causes a problem*/
    /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. Begin*/
    if (apBIT_GET(CharATR, PL131_REGDATA_PARITY)    \
       && (pState->sATRParams.Grouping != PL131_ATR_GROUPSTART)    \
       && (pState->eConvention != PL131_CONVENTION_INVERSE))
    {
        /* 奇偶校验位出错，认为收到的ATR不正确重新上电尝试begin*/
        
        SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, CharATR, __LINE__);
        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH,pState->eCurrentState, __LINE__);
        sci_class_switch_sence_try();
        SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
       
        sci_print_error("apPL131_ATRFAIL\n");

        return;
    }

    /* Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. End*/
    CharATR = apBIT_GET(CharATR, PL131_REGDATA_DATA);    /* make CharATR hold Data only, no Parity data */

    /* Changed back to direct convention mode for SIM card compatibility,
       not open retry function in ATR proceduce. Begin*/

    /* Changed for SIM Card compatibility(3B/3F). Begin*/
    /* Enable this inverse process for inverse convention*/
    /* DTS2011051001744 z67193, PPS阶段的自己反序由芯片完成*/
    if ((pState->eConvention == PL131_CONVENTION_INVERSE) && (0 == g_Pl131_pps_state.PL131_PPS_Response))
    {
        sci_print_info("PL131_CONVENTION_INVERSE\n");

        for (i = 8; i > 0; i--)
        {
            if (CharATR & 0x1)
            {
                temp |= 0x1;
            }

            temp = temp << 1;
            CharATR = CharATR >> 1;
        }

        CharATR = 0xFF & ~(temp >> 1);
    }

    /*Changed for SIM Card compatibility(3B/3F). End*/
    /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. End*/

    /*determine whether we are process PPS data here, not ATR data*/
    /*Changed for SIM Card compatibility. Begin*/
    if ((g_Pl131_pps_state.PL131_PPS_ACTIVATION) && (PPS_RESPONE_WORK == g_Pl131_pps_state.PL131_PPS_Response))
    {
        sci_print_info("We just move in PPS_Response process\n");
        pl131_pps_process(parapState, CharATR);

        SCI_RECORD_EVENT(SCI_EVENT_PPS_DONE, CharATR, __LINE__);
        return;
    }

    /* Changed for SIM Card compatibility. End*/

    /* copy to ATR buffer block */

    g_strATRData.ATRData[g_strATRData.ulATRLen] = (u8)CharATR;

    g_strATRData.ulATRLen++;

    /*-----------first character of ATR (TS: convention)-----------*/
    if (pState->sATRParams.Grouping == PL131_ATR_GROUPSTART)
    {
        /*Simulate error*/
        apPL131_SIMULATE_ERROR(PL131_SIM_ILLEGALCONV, CharATR = 0;
        )

        sci_print_info("PL131_ATR_GROUPSTART\n", 0, 0, 0, 0, 0, 0);

        /*Changed back to direct convention mode for SIM card compatibility,
          not open retry function in ATR proceduce. Begin*/

        /*Changed for SIM Card compatibility(3B/3F). Begin*/
        SCI_RECORD_EVENT(SCI_EVENT_ATR_REC_START, CharATR, __LINE__); 

        if (CharATR == PL131_ATR_CONV_NORM)
        {
            pState->eConvention = PL131_CONVENTION_DIRECT;
        }
        else if (CharATR == PL131_ATR_CONV_NORM_INV)
        {
            /* BEGIN: Modified by z67193, 2010-8-24, 如果返回'3F'，说明控制器已经反正过了，不需要软件处理 */

            //            pState->eConvention = PL131_CONVENTION_INVERSE;
            pState->eConvention = PL131_CONVENTION_DIRECT;
        }
        else if (CharATR == PL131_ATR_CONV_INV)
        {
            pState->eConvention = PL131_CONVENTION_INVERSE;
            sci_print_info("pState->eConvention = PL131_CONVENTION_INVERSE\n", 0, 0, 0, 0,
                      0, 0);
        }
        else
        {
            /*reset if invalid convention received*/
            sci_print_error("Invalid Convention Received, So do Card Deactivation No9 (PL131_CONVENTION_INVERSE)\n", 0, 0, 0,
                      0, 0, 0);

            SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, CharATR, __LINE__);
            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, CharATR, __LINE__);
            sci_class_switch_sence_try();
            SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
           
            return;

            /*NOTIFICATION - ATR error*/
        }

        /*Changed for SIM Card compatibility(3B/3F). End*/
        /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. End*/

        pState->sATRParams.Grouping = 0;         /*format character*/
        pState->sATRParams.Current  = 0;         /*format character*/
        pState->sATRParams.Checksum = 0;         /*initialise the checksum*/
        pState->sATRParams.ChGuard = 1;
        pState->sATRParams.eClkRateConv = apPL131_F_372;  /*clock rate conversion*/
        pState->sATRParams.eBitRateAdj = apPL131_D_1;    /*bit rate adjustment*/
        pState->sATRParams.WI = 10;

        /*----------Open SCI Clock Stop Mode -------*/
        /*Close time stop mode for default setting, Begin*/

        /* DTS2011051001744 z67193, 将默认时钟停止模式设置为NO_PREF，如果ATR处理中没有时钟配置，上层可以停止时钟*/
        pState->sATRParams.eClkStopInd = apPL131_CLK_STATE_NO_PREF;

        /*Close time stop mode for default setting, End*/
        /*----------Open SCI Clock Stop Mode -------*/
        pState->sATRParams.ClassInd = 0;
        pState->eProtocol = apPL131_PROTOCOL_T0_CHAR;
        g_Pl131_pps_state.ucModeOfOperation = PL131_NEGOTIABLE_MODE;
    }
    /*-----------format character for next block (T0 or TDi)-----------*/
    else if (pState->sATRParams.Grouping != PL131_ATR_GROUPDONE)
    {
        /*build the checksum by XORing T0,TAi,TBi,TCi and TDi characters*/
        pState->sATRParams.Checksum = (unsigned char) (pState->sATRParams.Checksum ^ CharATR);

        /*-----------historical data-----------*/
        if ((pState->sATRParams.Current == 0)
           || (pState->sATRParams.Current == 4))
        {
            /*mask of expected characters A-D.
             *Bit 0 = A, Bit 1 = B, Bit 2 = C, Bit 3 = D */
            pState->sATRParams.CharPresent = apBIT_GET(CharATR, PL131_ATR_PRESENT);

            if (pState->sATRParams.Grouping == 0)     /*check if it's the T0 character*/
            {
                /*历史字符个数*/
                pState->sATRParams.NumHist = apBIT_GET(CharATR, PL131_ATR_HIST);
                pState->sATRParams.ProtocolType = 0;     /*first block always protocol 0*/
                pState->sATRParams.AltProtocolType   = 0;
                pState->sATRParams.InterfaceByteQual = FALSE;
                pState->sATRParams.HasChecksum = FALSE;
            }
            else if ((pState->sATRParams.Grouping >= 2) && ((unsigned long)apBIT_GET(CharATR, PL131_ATR_PROT) == 15))
            {
                pState->sATRParams.InterfaceByteQual = TRUE; /*T = 15 indicates gobal interface byte*/
                pState->sATRParams.HasChecksum = TRUE;       /*expect a checksum */
                g_sci_atr_info.tckLen = 1;
            }
            else if (pState->sATRParams.Grouping > 1)
            {
                pState->sATRParams.AltProtocolType =
                    apBIT_GET(CharATR, PL131_ATR_PROT);        /*alternative protocol offered*/
            }
            else
            {
                pState->sATRParams.ProtocolType =
                    apBIT_GET(CharATR, PL131_ATR_PROT);        /*first offered protocol*/
            }

            /*we only support protocol T0 and T1*/
            if (pState->sATRParams.ProtocolType > 1)
            {

                SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, CharATR, __LINE__);
                SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, CharATR, __LINE__);
                sci_class_switch_sence_try();
                SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
              
                return;

            }

            /*check if this block specifies a non-zero protocol*/
            if (pState->sATRParams.ProtocolType)
            {
                pState->sATRParams.HasChecksum = TRUE; /*lint !e64*/  /*expect a checksum here*/
                pState->eProtocol = apPL131_PROTOCOL_T1_BLOCK; /*always use protocol T1*/
                g_sci_atr_info.tckLen = 1;

            }

            if (!pState->sATRParams.CharPresent)    /*stop if no chars in next block*/
            {
                pState->sATRParams.Grouping = PL131_ATR_GROUPDONE;
                sci_print_info("\nHistorical data if UICC send them!-\n", 0, 0, 0, 0, 0, 0);
                if (pState->sATRParams.HasChecksum || (pState->sATRParams.NumHist != 0))
                {
                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->sATRParams.CharPresent, __LINE__);
                    return;
                }
            }

            pState->sATRParams.Grouping++;          /*next group (i) of characters*/
            pState->sATRParams.Current = 0;         /*Character TAi is next*/
        }
        /*-----------other character of ATR (TAi, TBi, TCi)-----------*/
        else
        {
            /*still working on this block - process the character*/
            pl131_atr_param_set(pState,
                              pState->sATRParams.Grouping,
                              pState->sATRParams.Current,
                              CharATR);
            /*这里没看懂先不改了，即不进行电压切换的操作*/
            if ((PL131_ATR_ITEM(pState->sATRParams.Grouping, pState->sATRParams.Current) == 0xC1)
               && ((0 < CharATR) && (CharATR < 255)))
            {
                pState->eCurrentState = PL131_STATE_INACTIVECARD;
                SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, CharATR, __LINE__);
                retVal = appl131_card_active_set(pState, TRUE, pState->sATRParams.pATRBuffer);
                if(retVal == 0)
                {                  
                    SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, CharATR, __LINE__);
                }
                                
                return;
            }
        }

        /*-----------next character of ATR (TAi, TBi, TCi, TDi)-----------*/

        /*find which character (A-D) is expected next*/
        do
        {
            pState->sATRParams.Current++;
        } while ((pState->sATRParams.Current < 5)
           && (!(pState->sATRParams.CharPresent & (1UL << (pState->sATRParams.Current - 1))
                  )));

        if (pState->sATRParams.Current == 5)
        {
            pState->sATRParams.Grouping = PL131_ATR_GROUPDONE;
            pBase->RegTide = 0x10;
            if (pState->sATRParams.HasChecksum || (pState->sATRParams.NumHist != 0))
            {
                SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->sATRParams.CharPresent, __LINE__);
                return;
            }
        }
    }

    /*-----------historical data-----------*/
    if (pState->sATRParams.Grouping == PL131_ATR_GROUPDONE)
    {
        /*build the checksum by XORing Historical characters */
        pState->sATRParams.Checksum = (unsigned char) (pState->sATRParams.Checksum ^ CharATR);

        /*character after historical is the checksum - should be zero*/
        if ((pState->sATRParams.HasChecksum)    \
           && (pState->sATRParams.NumHist == 0)    \
           && (pState->sATRParams.Checksum))
        {

            SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, CharATR, __LINE__);
            SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH,pState->eCurrentState, __LINE__);
            sci_class_switch_sence_try();
            SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
          
            return;
        }

        /*-----------ATR completed - set up parameters-----------*/

        /*finished if reached 0 and Checksum need (or 1 and no checksum)*/
        if (((pState->sATRParams.NumHist == 0)
               && (pState->sATRParams.Checksum == 0))
           || ((!pState->sATRParams.HasChecksum)
               && ((pState->sATRParams.NumHist == 0)
                   || (pState->sATRParams.NumHist == 1))))
        {
            /*(Class Switch) Change Begin*/
            /*judge that the class offerer by UICC is supported or not*/
            if (((pState->sATRParams.ClassInd & 0x3F) != 0x00))
            {
                switch (pState->sATRParams.ClassInd)
                {
                case (0x01):
                {
                    apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
                    SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, CharATR, __LINE__);
                    SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, CharATR, __LINE__);
                    return;
                }
                case (0x02):
                case (0x03):
                {
                    if (g_sci_voltage_state.sciClassKind == PL131_SCI_Class_C)
                    {

                        g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_PROCESS;
                        
                        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, CharATR, __LINE__);
                       
                        g_sci_voltage_state.sci_vlotage_switch_sense = SCI_VOLTAGE_SWITCH_SENSE_CLASS_C2B_IMMEDIATELY;
                        SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
                        

                        apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);                     
                        
                        return;
                    }
                    else
                    {
                        break;
                    }
                }
                case (0x04):
                case (0x06):
                case (0x07):
                {
                    break;
                }
                default:
                {
                    sci_print_error("Card asked Class Value was out of special range! Current Class is %ld\r\n",
                              (int)g_sci_voltage_state.sciClassKind,
                              0, 0, 0, 0, 0);

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, g_sci_voltage_state.sciClassKind, __LINE__);
                    return;
                }
                }
            }

            /*(Class Switch) Change End*/

            

            /*Guard time*/
            
            if (pState->sATRParams.ChGuard == 255 || pState->sATRParams.ChGuard == 0)
            {
                pBase->RegChGuard = 1;
            }
            else if ((pState->sATRParams.ChGuard)
               && (pState->eProtocol == apPL131_PROTOCOL_T0_CHAR))
            {
                pBase->RegChGuard = pState->sATRParams.ChGuard;
            }
            /*2014年6月10日16:07:53 T = 1的场景不直接修改chGuand的值，待协议切换时统一修改
                        ,这里不会影响在T=0模式下直接使用*/
            /* 
            else if ((pState->sATRParams.ChGuard)
               && (pState->eProtocol == apPL131_PROTOCOL_T1_BLOCK))
            {
                pBase->RegChGuard = pState->sATRParams.ChGuard  + 1;
            }
             */
            /*set handshake settings for T0 mode*/
            if (pState->eProtocol == apPL131_PROTOCOL_T0_CHAR)
            {
                /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. Begin*/
                apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_RX, pState->sSetupParams.eRxHandshake); /*Open Even Parity Check*/
                apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_TX, pState->sSetupParams.eTxHandshake);
                apBIT_SET(pBase->RegRetry, PL131_REGRETRY_RX, pState->sSetupParams.RxRetries); /*Open retry function after ATR proceduce, 3 times retry*/
                apBIT_SET(pBase->RegRetry, PL131_REGRETRY_TX, pState->sSetupParams.TxRetries);

                /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. End*/
            }
            /*set handshake settings for T1 mode*/
            else
            {
                apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_TXNAK, 0);
                apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_RXNAK, 0);
                apBIT_SET(pBase->RegRetry, PL131_REGRETRY_TX, 0);
                apBIT_SET(pBase->RegRetry, PL131_REGRETRY_RX, 0);
            }

            /*set data convention for remaining data*/
            apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CONV, pState->eConvention);

            /*disable ATR Duration Timeout*/
            apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_ATRDEN, 0);

            /* 2014年5月28日14:56:21 这里不应该减1，应该在协议切换时操作
            if (pState->eProtocol == apPL131_PROTOCOL_T1_BLOCK)
            {
                pBase->RegBlkGuard = PL131_DEF_BLKGUARDTIME - 5;
            }
            */

            /* if TA2 is got, we are in specific mode set*/
            if (g_Pl131_pps_state.ucModeOfOperation == PL131_SPECIFIC_MODE)
            {
                //logMsg( "We are in Specific mode!!!!!!!!\n",0,0,0,0,0,0);

                /*if b8=1 and b5=0, then we set F and D use interface byte*/
                if ((g_Pl131_pps_state.ucTA2Data & 0x90) == 0x80)
                {
                    if (!g_Pl131_pps_state.ucTA1Flag)
                    {}
                    else if (g_Pl131_pps_state.ucTA1Flag == 1)
                    {
                        apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
                        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, (g_Pl131_pps_state.ucTA2Data), __LINE__);
                    }

                }
                /* if the F and D are not supported, we warm reset to invoke negotiable mode of UICC*/
                else if ((g_Pl131_pps_state.ucTA2Data & 0x90) == 0x0)
                {
                    if ((PL131_ClkRateConv[pState->sATRParams.eClkRateConv] == 0)    \
                       || (PL131_BitRateAdj[pState->sATRParams.eBitRateAdj] == 0))
                    {
                        pState->eCurrentState = PL131_STATE_INACTIVECARD;
                        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, (g_Pl131_pps_state.ucTA2Data), __LINE__);
                        retVal = appl131_card_active_set(pState, TRUE, pState->sATRParams.pATRBuffer);
                        if(retVal == 0)
                        {
                            SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, (g_Pl131_pps_state.ucTA2Data), __LINE__);
                        }
                        
                        return;
                    }
                }
                if(10!=pState->sATRParams.WI)
                {
                    pl131_reset_wwt(pState);
                    
                    SCI_RECORD_EVENT(SCI_EVENT_ATR_WWT_RESET, ((pState->sSetupParams.CharacterTime - 12 + g_ulChTimeOffset)), __LINE__);
                    sci_print_info("if wi is not equal to 10, reset it,wi is %d, and eBitRateAdj is %d\n", pState->sATRParams.WI, pState->sATRParams.eBitRateAdj, 0, 0, 0, 0);
                }
            }
            else if(0 == g_Pl131_pps_state.ucTA1Flag)
            {
                /* 协商模式下，TA1为0x11时，不进行PPS协商，但是需要更新WWT */
                if(10!=pState->sATRParams.WI)
                {
                    pl131_reset_wwt(pState);
                    SCI_RECORD_EVENT(SCI_EVENT_ATR_WWT_RESET, ((pState->sSetupParams.CharacterTime - 12 + g_ulChTimeOffset)), __LINE__);
                    
                    sci_print_info("if wi is not equal to 10, reset it,wi is %d, and eBitRateAdj is %d\n", pState->sATRParams.WI, pState->sATRParams.eBitRateAdj, 0, 0, 0, 0);
                }
            }

            /* if in Negotiable mode and TA1 not equal to 11, then a PPS process is needed*/
            if ((g_Pl131_pps_state.ucModeOfOperation == PL131_NEGOTIABLE_MODE)    \
               && (g_Pl131_pps_state.ucTA1Flag)  \
               && (g_Pl131_pps_state.PL131_PPS_ACTIVATION <= 3)\
               && (PL131_ClkRateConv[pState->sATRParams.eClkRateConv] != 0) \
               && (PL131_BitRateAdj[pState->sATRParams.eBitRateAdj] != 0))
            {
                g_Pl131_pps_state.PL131_PPS_ACTIVATION++; /*Flag the activation of PPS process, and the times we initiated it*/
                /* Changed for SIM Card compatibility. Begin*/
                g_Pl131_pps_state.PL131_PPS_Response = PPS_RESPONE_READY;  /*Set another flag to ensure PPS request process well*/
                osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCISynSem);

                SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, (g_Pl131_pps_state.ucTA1Flag), __LINE__);
                /*Changed for SIM Card compatibility. End*/
                return;
            }

            /*confirm normal process, set flag as default value*/
            g_Pl131_pps_state.PL131_PPS_ACTIVATION = 0;
            g_Pl131_pps_state.ucTA1Flag = 0;
            nActiveT = 0;
            pState->eCurrentState = PL131_STATE_READY;
            g_u32ResetSuccess = SCI_DEF_RESET_SUCCESS;

            
            sci_check_current_state(PL131_STATE_READY);
 
            //sciRecordInitPara();

            /* Optimize SCI interrupt process times. Begin*/
            /*Changed for SCI RX FIFO Overflow issue. Begin*/
            apBIT_SET(pBase->RegTide, PL131_REGTIDE_RX, 0x01);    /*From 0x06 to 0x01*/
            /*Changed for SCI RX FIFO Overflow issue. End*/
            /*Optimize SCI interrupt process times. End*/

            /*NOTIFICATION - ATR complete*/
            /* 通知上层平台sim卡已经上电*/
            if (NULL != g_FuncCb)
            {
                (BSP_VOID)g_FuncCb((u32)SCI_EVENT_CARD_RESET_SUCCESS, NULL);
            }

            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pState->eCurrentState, __LINE__);

            sci_record_init_para();
            return;
        }

        /*minus Historiacl data number*/
        pState->sATRParams.NumHist--;                   /*next historical character*/
    }
    if(pState->eCurrentState == PL131_STATE_READY)
    {
        SCI_RECORD_EVENT(SCI_EVENT_ATR_REC_OVER, pState->eCurrentState, __LINE__);
    }
}

/*****************************************************************************
* 函 数 名  : pl131_atr_param_set
*
* 功能描述  : 解析ATR字節的含義
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
static void pl131_atr_param_set (SCI_STATE_STRU * parapState,
                               u32           ATRGrouping,
                               u32           ATRCurrent,
                               u32           ATRCharacter)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;

    if ((pState->sATRParams.InterfaceByteQual) && (ATRCurrent == 1))
    {
        pState->sATRParams.eClkStopInd =
            (apPL131_eClkStopInd)
            apBIT_GET(ATRCharacter, PL131_ATR_CLOCK_STOP);
        pState->sATRParams.ClassInd =
            (u32)
            apBIT_GET(ATRCharacter, PL131_ATR_CLASS_IND);

        sci_print_info("UICC send TA3 to set Class and Clock Stop parameters pState->sATRParams.ClassInd = %l#x!\n",
                  (int)pState->sATRParams.ClassInd, 0, 0, 0, 0, 0);
    }
    else
    {
        /*The ATR grouping and the current item within the grouping determine
         *how characters are interpreted.  The PL131_ATR_ITEM macro allows us to use a
         *single switch statement
         */
        u32 ATRItem;
        u32 cwi = 0;
        u32 bwi = 0;
        SCI_RECORD_EVENT(SCI_EVENT_ATR_REC_GLOBAL, pState->eCurrentState, __LINE__);
        ATRItem = PL131_ATR_ITEM(ATRGrouping, ATRCurrent);
        switch (ATRItem)
        {
            /*specify the clock rate conversion and bit rate adjustment factor*/
        case 0xA1:        /*character A1*/
        {
            sci_print_info("TA1 = %l#x\n", (int)ATRCharacter, 0, 0, 0, 0, 0);
            pState->sATRParams.eClkRateConv =
                (apPL131_eClockRateConv)
                apBIT_GET(ATRCharacter, PL131_ATR_CLKRATE);                 /*clock rate conversion*/
            pState->sATRParams.eBitRateAdj =
                (apPL131_eBitRateAdj)
                apBIT_GET(ATRCharacter, PL131_ATR_BITRATE);                /*bit rate adjustment*/
            if (0x11 == ATRCharacter || 0x01 == ATRCharacter)
            {
                g_Pl131_pps_state.ucTA1Flag = 0;
            }
            else if ((PL131_ClkRateConv[pState->sATRParams.eClkRateConv] != 0)
                   && (PL131_BitRateAdj[pState->sATRParams.eBitRateAdj] != 0))
            {
                g_Pl131_pps_state.ucTA1Flag = 2;
            }
            else
            {
                g_Pl131_pps_state.ucTA1Flag = 1;
            }

            break;
        }
        case 0xA2:
        {
            if((ATRCharacter & 0x80) == 0x00)
            {
                
                g_Pl131_pps_state.ucModeOfOperation = PL131_SPECIFIC_MODE;
                g_Pl131_pps_state.ucTA2Data = (u8)ATRCharacter;
                if ((g_Pl131_pps_state.ucTA2Data & 0x01) == 0x01)
                {
                    pState->sATRParams.HasChecksum = TRUE;      /*we now expect a checksum*/
                    pState->eProtocol = apPL131_PROTOCOL_T1_BLOCK;     /*always use protocol T1*/
                    g_sci_atr_info.tckLen = 1;

             
                }
            }
            
            break;
        }
        case 0xA3:
        {
            /*2014年5月22日20:29:16 l00258701 7816-3 11.4.2 0和FF为保留值
                        这里是否应该重启?还是按照电压切换的流程走?
                    */
            /* coverity[unchecked_value] */
            if(ATRCharacter == 0 ||ATRCharacter == 0XFF)
                appl131_card_active_set(pState, TRUE, pState->sATRParams.pATRBuffer);

            g_sci_atr_info.valIFSC = ATRCharacter & 0XFF;
            sci_print_info("The max information bytes we can send to UICC is %l#x\n",
                      (u8)ATRCharacter, 0, 0, 0, 0, 0);
            break;
        }

            /* set BWI and CWI for BLKTOUT and CHTOUT REG*/
        case 0xB3:
        {
            if (pState->eProtocol == apPL131_PROTOCOL_T1_BLOCK)
            {
                cwi = (ATRCharacter & 0x0F);
                bwi = ((ATRCharacter & 0xF0) >> 4);
                /*lint -save  -e685*/
                 /* coverity[unsigned_compare] */
                if(cwi >= 0 && cwi <= 5)
                {
                    g_t1_times.CharacterTime = (1UL << cwi) + 11;;
                }
                /* coverity[unsigned_compare] */
                if(bwi >= 0 && bwi <=4 )
                {
                    g_t1_times.BlockTime = ((1UL << ((ATRCharacter & 0xF0) >> 4)) * 960 + 11);
                }
                if(cwi > 5 || bwi > 4)
                {
                    /*ATR 错误*/
                    SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, ATRCharacter, __LINE__);
                    SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, ATRCharacter, __LINE__);
                    sci_class_switch_sence_try();
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);
                }
                /*lint -restore  +e685*/
            }

            break;
        }

            /*specify the character-character guard time*/
        case 0xC1:        /*character C1*/
        {
            /*在最后写入寄存器的时候已按照pl131文档处理*/
            pState->sATRParams.ChGuard = ATRCharacter;
            break;
        }
        case 0xC2:      /*character TC2, for getting the WI in ATR to set WWT*/
        {
            sci_print_info("TC2 = %l#x\n", (int)ATRCharacter, 0, 0, 0, 0, 0);
            if (ATRCharacter != 0)
            {
                pState->sATRParams.WI = ATRCharacter;
            }

            break;
        }
        case 0xC3:
        {
            /*有TC3回送则计算，没有则使用默认值*/
            if(ATRCharacter == T1_ERR_DETECT_MODE_CRC)
            {
                g_sci_atr_info.errDetectMode = T1_ERR_DETECT_MODE_CRC;
            }
            else if(ATRCharacter != T1_ERR_DETECT_MODE_LRC)
            {
                /*回送了不是0和1的值*/
                SCI_RECORD_EVENT(SCI_EVENT_ATR_DECODE_ERR, ATRCharacter, __LINE__);
                SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, ATRCharacter, __LINE__);
                sci_class_switch_sence_try();
                SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH,pState->eCurrentState, __LINE__);

            }

        }
            /*notify the user of an ATR item*/
        default:
        {
            /*PL131_CALLBACK(apPL131_ATRCHAR, (ATRItem << 8) + ATRCharacter);*/
            break;
        }
        }
    }
}

/*****************************************************************************
* 函 数 名  : appl131_clock_stop_mode_set
*
* 功能描述  : 設置時鐘停止模式
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_clock_stop_mode_set (SCI_STATE_STRU *   parapState,
                                 apPL131_eClockMode Mode, u32 ucClockStopInd)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    
    /*Simulate functionality*/
    apPL131_SIMULATE_ERROR(PL131_SIM_CLOCKSTOPMODE, pState->sATRParams.eClkStopInd = apPL131_CLK_STATE_LOW;)
    
    if (pState->sATRParams.eClkStopInd == apPL131_CLK_STOP_UNSUPPORTED)
    {
        SCI_RECORD_EVENT(SCI_EVENT_CLK_ERROR, pState->eCurrentState, __LINE__);
        return apERR_UNSUPPORTED;
    }

    if (Mode == apPL131_CLOCK_STOP)
    {   
        SCI_RECORD_EVENT(SCI_EVENT_CLK_STOP, pState->eCurrentState, __LINE__);

        switch (pState->sATRParams.eClkStopInd)
        {
        case apPL131_CLK_STATE_LOW:
            apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKVAL, PL131_CLOCK_LOW);
            break;
        case apPL131_CLK_STATE_HIGH:
            apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKVAL, PL131_CLOCK_HIGH);
            break;
        /* ATR指示NO_PREFER，可以按照上层传入的参数完成 */
        case apPL131_CLK_STATE_NO_PREF:
            {
                switch(ucClockStopInd)
                {
                case SCI_CLK_STATE_LOW:
                    apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKVAL, PL131_CLOCK_LOW);
                    break;
                case SCI_CLK_STATE_HIGH:
                    apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKVAL, PL131_CLOCK_HIGH);
                    break;
                default:
                    apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKVAL, PL131_DEF_CLOCK_STATE);
                    break;
                }
                break;
            }
        default:
            apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKVAL, PL131_DEF_CLOCK_STATE);
            break;
        }

        apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKDIS, 1);
        apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_CLKSTPI, 1);
        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_CLOCK_STOP, pState->eCurrentState, __LINE__);

    }
    else if (Mode == apPL131_CLOCK_START)
    {
        apBIT_SET(pBase->RegCtrl0, PL131_REGCTRL0_CLKDIS, 0);
        apBIT_SET(pBase->RegIntMask, PL131_REGINTMASK_CLKACTI, 1);
        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_CLOCK_START, pState->eCurrentState, __LINE__);
    }

    return apERR_NONE;
}

/*****************************************************************************
* 函 数 名  : appl131_dma_mode_set
*
* 功能描述  : 設置傳輸方式為DMA
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
void appl131_dma_mode_set(SCI_STATE_STRU * parapState, apPL131_eDMAMode DMAMode)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    /* Set DMA enable bits */
    apBIT_SET(pBase->RegDMACtrl, PL131_REGDMA, DMAMode);
}

/*****************************************************************************
* 函 数 名  : appl131_dma_address_get
*
* 功能描述  : 獲取DMA的地址
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
u32 appl131_dma_address_get(SCI_STATE_STRU * parapState)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;

    return (u32) &pBase->RegData;
}

/*****************************************************************************
* 函 数 名  : pl131_pps_request
*
* 功能描述  : 發送PPS協商請求
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
void pl131_pps_request(SCI_STATE_STRU * parapState)
{
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;
    unsigned char PPS0, PPS1, PCK;
    int retVal = 0;

    /*if the WWT timeout was valid more than 2 times, we should send "FF,00,FF" to UICC*/
    if ((g_Pl131_pps_state.PL131_PPS_ACTIVATION == 3) || (g_SciExcResetTimes == 2) || (g_SciExcResetTimes > 3))
    {
        sci_print_error("WWT was timeout more than 2 times, so we set ucTA1Flag = 1\n");
        g_Pl131_pps_state.ucTA1Flag = 1;
    }

    /*packet different PPS packet and sent them out*/
    switch (g_Pl131_pps_state.ucTA1Flag)
    {
    case 1:
    {
        sci_print_info("ucTA1Flag = 1, need simple PPS request\n");
        apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_MODE, apPL131_TX_TO_CARD);
        writel(0xff,SCI_REG_DATA);
        sci_print_info("We send 0xFF to UICC\n");
        writel(0x00,SCI_REG_DATA);
        sci_print_info("We send 0x00 to UICC\n");
        writel(0xff,SCI_REG_DATA);
        sci_print_info("We send 0xFF to UICC\n");
        apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_MODE, apPL131_RX_FROM_CARD);

        /*set F and D as implicit value*/
        pState->sATRParams.eClkRateConv = apPL131_F_372;      /*clock rate conversion*/
        pState->sATRParams.eBitRateAdj = apPL131_D_1;         /*bit rate adjustment*/
        /*Changed for SIM Card compatibility. Begin*/
        g_Pl131_pps_state.PL131_PPS_Response = PPS_RESPONE_WORK;
        SCI_RECORD_EVENT(SCI_EVENT_PPS_PPS0, pState->eCurrentState, __LINE__);

        /*Author:H55798, Changed for SIM Card compatibility. End*/
        break;
    }

        /*for GSM and normal WCDMA PPS process only*/
    case 2:
    {
        PPS0 = (0x10 | (u8)pState->sATRParams.ProtocolType);/* [false alarm]: fortify 误报*/
        PPS1 = (pState->sATRParams.eClkRateConv << 4) | (pState->sATRParams.eBitRateAdj);
        PCK = ((0xFF) ^ (0x10) ^ (PPS1));
        sci_print_info("ucTA1Flag = 2, need complex PPS request. The eClkRateConv is %d, The eBitRateAdj is %d\n",
                  (PPS1 >> 4), (PPS1 & 0x0F), 0, 0, 0, 0);
        apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_MODE, apPL131_TX_TO_CARD);
        writel(0xff,SCI_REG_DATA);
        sci_print_info("We send 0xFF to UICC\n", 0, 0, 0, 0, 0, 0);
        writel(PPS0,SCI_REG_DATA);
        sci_print_info("We send 0x10 to UICC\n", 0, 0, 0, 0, 0, 0);
        writel(PPS1,SCI_REG_DATA);
        sci_print_info("We send 0x%x to UICC\n", PPS1, 0, 0, 0, 0, 0);
        writel(PCK, SCI_REG_DATA);
        sci_print_info("We send 0x%x to UICC\n", PCK, 0, 0, 0, 0, 0);
        apBIT_SET(pBase->RegCtrl1, PL131_REGCTRL1_MODE, apPL131_RX_FROM_CARD);

        /*Changed for SIM Card compatibility. Begin*/
        g_Pl131_pps_state.PL131_PPS_Response = PPS_RESPONE_WORK;
        SCI_RECORD_EVENT(SCI_EVENT_PPS_PPS1, pState->eCurrentState, __LINE__);

        /*Changed for SIM Card compatibility. End*/
        break;
    }
    default:
    {
        sci_print_info("Not process the valid PPS parameters, unknow error happened here\n", 0, 0, 0, 0, 0, 0);

        /*  pState->eCurrentState = PL131_STATE_INACTIVECARD;*/
        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pState->eCurrentState, __LINE__);
        retVal = appl131_card_active_set(pState, TRUE, pState->sATRParams.pATRBuffer);
        if(retVal == 0)
        {
             SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pState->eCurrentState, __LINE__);
        }
       
        break;
    }
    }

    return;
}
/*****************************************************************************
* 函 数 名  : pl131_pps_process
*
* 功能描述  : 處理PPS的響應
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
void pl131_pps_process(SCI_STATE_STRU * parapState, u32 CharATR)
{
    SCI_STATE_STRU * const pState = parapState;
    SCI_REG * const pBase = pState->pBase;
    static unsigned char PPS1_Response;
    int retVal = 0;

    sci_print_info("We are in PPS process, input PPS data = %l#x\n",
              (int)CharATR, 0, 0, 0, 0, 0);
    /*do two kinds process here, according to the value of ucTA1Flag*/
    switch (g_Pl131_pps_state.ucTA1Flag)
    {
        /*ucTA1Flag = 1 means we negotiate to use Fd and Dd if PPS passed*/
    case 1:
    {
        if ((g_Pl131_pps_state.ucPPSFlag == 0) && (CharATR == 0xFF))
        {
            g_Pl131_pps_state.ucPPSFlag++;
        }
        else if ((g_Pl131_pps_state.ucPPSFlag == 1) && (CharATR == 0x00))
        {
            g_Pl131_pps_state.ucPPSFlag++;
        }
        else if ((g_Pl131_pps_state.ucPPSFlag == 2) && (CharATR == 0xFF))
        {
            sci_print_info("PPS process is successful, now we use Fd and Dd to communication with UICC\n", 0, 0, 0, 0, 0, 0);
            g_Pl131_pps_state.ucModeOfOperation  = PL131_SPECIFIC_MODE;
            g_Pl131_pps_state.PL131_PPS_Response = 0;
            g_Pl131_pps_state.ucPPSFlag = 0;
            g_Pl131_pps_state.ucTA1Flag = 0;
            g_Pl131_pps_state.PL131_PPS_ACTIVATION = 0;       /*confirm normal process*/
            nActiveT = 0;
            pState->eCurrentState = PL131_STATE_READY;          /*Update state*/
            g_u32ResetSuccess = SCI_DEF_RESET_SUCCESS;

            sci_check_current_state(PL131_STATE_READY);

            apBIT_SET(pBase->RegTide, PL131_REGTIDE_RX, 0x01);      /*From 0x06 to 0x01*/
            /* 通知上层平台sim卡已经上电*/
            if (NULL != g_FuncCb)
            {
                (BSP_VOID)g_FuncCb((u32)SCI_EVENT_CARD_RESET_SUCCESS, NULL);
            }
            /* record debug info */
            SCI_RECORD_EVENT(SCI_EVENT_PPS_DONE, 0, 0);

            sci_record_init_para();

        }
        else
        {
            sci_print_error("Error happened here, the value of ucTA1Flag is %d, the ucPPSFlag is %d, the CharATR is %l#d\n",
                      g_Pl131_pps_state.ucTA1Flag, g_Pl131_pps_state.ucPPSFlag, (u8) CharATR, 0, 0, 0);

            //  pState->eCurrentState = PL131_STATE_INACTIVECARD;
            (BSP_VOID)appl131_card_active_set(pState, TRUE, pState->sATRParams.pATRBuffer);
            g_Pl131_pps_state.PL131_PPS_Response = 0;
            g_Pl131_pps_state.ucPPSFlag = 0;
        }

        break;
    }

        /*ucTA1Flag = 2 means we negotiate to use Fn and Dn got from TA1 if PPS passed*/
    case 2:
    {
        if ((g_Pl131_pps_state.ucPPSFlag == 0) && (CharATR == 0xFF))
        {
            g_Pl131_pps_state.ucPPSFlag++;
        }
        else if ((g_Pl131_pps_state.ucPPSFlag == 1) && (CharATR == 0x10))
        {
            g_Pl131_pps_state.ucPPSFlag++;
        }
        else if ((g_Pl131_pps_state.ucPPSFlag == 1) && (CharATR == 0x00))
        {
            sci_print_info("PPS0 = 0x00, so PPS1 will not be present, we use Fd and Dd now\n", 0, 0, 0, 0, 0, 0);

            /*set F and D as implicit value*/
            pState->sATRParams.eClkRateConv = apPL131_F_372;      /*clock rate conversion*/
            pState->sATRParams.eBitRateAdj = apPL131_D_1;             /*bit rate adjustment*/
            g_Pl131_pps_state.ucPPSFlag = 0xFF;
        }
        else if ((g_Pl131_pps_state.ucPPSFlag == 2)
                 && (CharATR == ((pState->sATRParams.eClkRateConv << 4) | (pState->sATRParams.eBitRateAdj))))
        {
            g_Pl131_pps_state.ucPPSFlag++;
            PPS1_Response = (pState->sATRParams.eClkRateConv << 4) | (pState->sATRParams.eBitRateAdj);
        }
        else if ((g_Pl131_pps_state.ucPPSFlag == 3) && (CharATR == ((0xFF) ^ (0x10) ^ (PPS1_Response))))
        {
            sci_print_info("PPS process is successful, now we use Fn and Dn to communication with UICC\n", 0, 0, 0, 0, 0, 0);

            pl131_reset_wwt(parapState);
            SCI_RECORD_EVENT(SCI_EVENT_ATR_WWT_RESET, ((pState->sSetupParams.CharacterTime - 12 + g_ulChTimeOffset)), __LINE__);

            sci_print_info("RegChTimeMS is %d, RegChTimeLs %d, eBitRateAdj is %d, wi is %d\n", parapState->pBase->RegChTimeMS, parapState->pBase->RegChTimeLS, parapState->sATRParams.eBitRateAdj, parapState->sATRParams.WI, 0, 0);
            
            appl131_bit_duration_set(pState, pState->sATRParams.eClkRateConv, pState->sATRParams.eBitRateAdj);
            g_Pl131_pps_state.ucModeOfOperation  = PL131_SPECIFIC_MODE;
            g_Pl131_pps_state.PL131_PPS_Response = 0;
            g_Pl131_pps_state.ucPPSFlag = 0;
            g_Pl131_pps_state.ucTA1Flag = 0;
            g_Pl131_pps_state.PL131_PPS_ACTIVATION = 0;       /*confirm normal process*/
            nActiveT = 0;
            pState->eCurrentState = PL131_STATE_READY;          /*Update state*/
            g_u32ResetSuccess = SCI_DEF_RESET_SUCCESS;

            sci_check_current_state(PL131_STATE_READY);
 
            apBIT_SET(pBase->RegTide, PL131_REGTIDE_RX, 0x01);      /*From 0x06 to 0x01*/
            /* 通知上层平台sim卡已经上电*/
            if (NULL != g_FuncCb)
            {
                (BSP_VOID)g_FuncCb((u32)SCI_EVENT_CARD_RESET_SUCCESS, NULL);
            }
            SCI_RECORD_EVENT(SCI_EVENT_PPS_DONE, 0, 0);

            sci_record_init_para();
            
        }
        else if ((u32)g_Pl131_pps_state.ucPPSFlag == CharATR)
        {
            sci_print_info("PPS process is successful, now we use Fd and Dd to communication with UICC\n", 0, 0, 0, 0, 0, 0);
            g_Pl131_pps_state.ucModeOfOperation  = PL131_SPECIFIC_MODE;
            g_Pl131_pps_state.PL131_PPS_Response = 0;
            g_Pl131_pps_state.ucPPSFlag = 0;
            g_Pl131_pps_state.ucTA1Flag = 0;
            g_Pl131_pps_state.PL131_PPS_ACTIVATION = 0;       /*confirm normal process*/
            nActiveT = 0;
            pState->eCurrentState = PL131_STATE_READY;          /*Update state*/
            g_u32ResetSuccess = SCI_DEF_RESET_SUCCESS;

            sci_check_current_state(PL131_STATE_READY);
            
            apBIT_SET(pBase->RegTide, PL131_REGTIDE_RX, 0x01);      /*From 0x06 to 0x01*/
            /* 通知上层平台sim卡已经上电*/
            if (NULL != g_FuncCb)
            {
                (BSP_VOID)g_FuncCb((u32)SCI_EVENT_CARD_RESET_SUCCESS, NULL);
            }

            /* record debug info */
            SCI_RECORD_EVENT(SCI_EVENT_PPS_DONE, 0, 0);

            sci_record_init_para();

        }
        else
        {
            sci_print_error("Error happened here, the value of ucTA1Flag is %d, the ucPPSFlag is %d, the CharATR is %l#d\n",
                      g_Pl131_pps_state.ucTA1Flag, g_Pl131_pps_state.ucPPSFlag, (u8) CharATR, 0, 0, 0);

            //  pState->eCurrentState = PL131_STATE_INACTIVECARD;
            SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pState->eCurrentState, __LINE__);

            retVal = appl131_card_active_set(pState, (int)TRUE, pState->sATRParams.pATRBuffer);

            if(retVal == 0)
            {
                SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pState->eCurrentState, __LINE__);
            }
            
            g_Pl131_pps_state.PL131_PPS_Response = 0;
            g_Pl131_pps_state.ucPPSFlag = 0;
        }

        break;
    }
    default:
    {
        sci_print_error("Error happened here, the value of ucTA1Flag is %l#x\n", g_Pl131_pps_state.ucTA1Flag, 0, 0, 0, 0, 0);
        pState->eCurrentState = PL131_STATE_INACTIVECARD;
        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pState->eCurrentState, __LINE__);
        retVal = appl131_card_active_set(pState, TRUE, pState->sATRParams.pATRBuffer);
        if(retVal == 0)
        {
            SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pState->eCurrentState, __LINE__);
        }
        
        g_Pl131_pps_state.PL131_PPS_Response = 0;
        g_Pl131_pps_state.ucPPSFlag = 0;
        break;
    }
    }

    return;
}


/*****************************************************************************
* 函 数 名  : appl131_get_clk_freq
*
* 功能描述  : 獲取卡片時鐘頻率
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_get_clk_freq(u32 *len, unsigned char *pbuf)
{
    if ((NULL == len) || (NULL == pbuf))
    {       
        sci_print_error("appl131_get_clk_freq: NULL POINTER\n");
        return BSP_ERR_SCI_INVALIDPARA;
    }
        
    *pbuf = g_strSciState.sSetupParams.CardFreq;
    *len = 4;

    return MDRV_OK;
}
/*****************************************************************************
* 函 数 名  : appl131_get_baud_rate
*
* 功能描述  : 獲取卡片時鐘波特率
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_get_baud_rate(u32 *len, unsigned char *pbuf)
{
    if ((NULL == len) || (NULL == pbuf))
    {       
        sci_print_error("appl131_get_baud_rate: NULL POINTER\n");
        return BSP_ERR_SCI_INVALIDPARA;
    }

    *pbuf = g_strSciState.sSetupParams.CharacterTime;
    *len = 4;

    return MDRV_OK;
}
/*****************************************************************************
* 函 数 名  : appl131_get_pcsc_paremeter
*
* 功能描述  : 獲取PCSC參數
*
* 输入参数  :
*
* 输出参数  : 无
*
* 返 回 值  :
* 修改记录  :
*
*****************************************************************************/
STATUS appl131_get_pcsc_paremeter(unsigned char *pbuf)
{
    PL131_PCSC_Parameter *pPara;
    
    if (NULL == pbuf)
    {
        sci_print_error("appl131_get_pcsc_paremeter: NULL POINTER\n");
        return BSP_ERR_SCI_INVALIDPARA;
    }

    pPara = (PL131_PCSC_Parameter*)pbuf;

    pPara->ucbmFindexDindex = (((unsigned char)(g_strSciState.sATRParams.eClkRateConv & 0xf)) << 4)
                              | ((unsigned char)(g_strSciState.sATRParams.eBitRateAdj & 0xf));
    pPara->ucbmTCCKST0 = (unsigned char)(g_strSciState.eConvention);
    pPara->ucbGuardTimeT0 = (unsigned char)(g_strSciState.sATRParams.ChGuard);
    pPara->ucbWaitingIntegerT0 =
        (unsigned char)(g_strSciState.sSetupParams.CharacterTime
                 / (960 * PL131_BitRateAdj[g_strSciState.sATRParams.eBitRateAdj]));
    pPara->ucbClockStop = (unsigned char)(g_strSciState.sATRParams.eClkStopInd);

    return MDRV_OK;
}


/*lint -restore */


