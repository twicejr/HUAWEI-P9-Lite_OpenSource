/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  sci_appl131.h
*
*   作    者 :  Y00171698
*
*   描    述 :  本文件命名为"sci_appl131.h", 为ARM公司提供的sample code
*            做了部分改动，编程规范不做修改。
*
*   修改记录 :
*************************************************************************/
/*lint --e{652}*/

#ifndef SCI_APPL131_H
#define SCI_APPL131_H

#ifdef __cplusplus
 #if __cplusplus
    {
 #endif
#endif /* __cplusplus */
#include "product_config.h"
#include "osl_types.h"
#include "soc_clk.h"
#include "bsp_sci.h"


/*
 * --------Type definitions--------
 */
#define  SCI_DEF_MASK_ALL_IRQ  0x0     /* sci irq mask register  */
#define  SCI_DEF_CLEAR_ALL_IRQ 0x1fff  /* sci irq clear register */

#ifndef apPL131_DEF_REF_CLOCK
/*
 * Description:
 * Default reference clock speed (kHz).  This will be used until a clock speed
 * is specified.
*/
#define apPL131_DEF_REF_CLOCK (HI_SCI0_CLK/1000)
#endif

#ifndef apERR_SCI_START
 #define apERR_SCI_START  BSP_ERR_SCI_NOTINIT
#endif
#ifndef apERR_NONE
 #define apERR_NONE 0
#endif

#ifndef apERR_UNSUPPORTED
 #define apERR_UNSUPPORTED BSP_ERR_SCI_UNSUPPORTED             /* Call failed due to a parameter which was in range, but unsupported for
    this variant of the hardware. */
#endif

#ifndef apERR_BUSY
 #define apERR_BUSY 3                             /* Resource is already in use */
#endif

#define BOOL    int

/*
 * Description:
 * Inline functions implemented as macros.  Not included in the standard
 */
/*The larger of __x and __y*/
#define MAX(__x,__y) ((__x)>(__y)?(__x):(__y))
/*The smaller of __x and __y*/
#define MIN(__x,__y) ((__x)<(__y)?(__x):(__y))

/*
 * Description:
 * Possible values for global parameter F (Clock Conversion factor) in the
 * ATR sequence, from ISO7816-3:1997
 */
typedef enum apPL131_xClockRateConv
{
    apPL131_F_RFU0 = 0x0,        /*Reserved*/
    apPL131_F_372  = 0x1,        /*F=372*/
    apPL131_F_558  = 0x2,        /*F=558*/
    apPL131_F_744  = 0x3,        /*F=744*/
    apPL131_F_1116 = 0x4,        /*F=1116*/
    apPL131_F_1488 = 0x5,        /*F=1488*/
    apPL131_F_1860 = 0x6,        /*F=1860*/
    apPL131_F_RFU7 = 0x7,        /*Reserved*/
    apPL131_F_RFU8 = 0x8,        /*Reserved*/
    apPL131_F_512  = 0x9,        /*F=512*/
    apPL131_F_768  = 0xa,        /*F=768*/
    apPL131_F_1024 = 0xb,        /*F=1024*/
    apPL131_F_1536 = 0xc,        /*F=1536*/
    apPL131_F_2048 = 0xd,        /*F=2048*/
    apPL131_F_RFUE = 0xe,        /*Reserved*/
    apPL131_F_RFUF = 0xf         /*Reserved*/
} apPL131_eClockRateConv;

/*
 * Description:
 * Possible values for global parameter D (Bit Rate Adjustment Factor) in the
 * ATR sequence, from ISO7816-3:1997
 */
typedef enum apPL131_xBitRateAdj
{
    apPL131_D_RFU0 = 0x0,        /*Reserved*/
    apPL131_D_1    = 0x1,        /*D=1*/
    apPL131_D_2    = 0x2,        /*D=2*/
    apPL131_D_4    = 0x3,        /*D=4*/
    apPL131_D_8    = 0x4,        /*D=8*/
    apPL131_D_16   = 0x5,        /*D=16*/
    apPL131_D_32   = 0x6,        /*D=32*/
    apPL131_D_RFU7 = 0x7,        /*Reserved*/
    apPL131_D_12   = 0x8,        /*D=12*/
    apPL131_D_20   = 0x9,        /*D=20*/
    apPL131_D_RFUA = 0xa,        /*Reserved*/
    apPL131_D_RFUB = 0xb,        /*Reserved*/
    apPL131_D_RFUC = 0xc,        /*Reserved*/
    apPL131_D_RFUD = 0xd,        /*Reserved*/
    apPL131_D_RFUE = 0xe,        /*Reserved*/
    apPL131_D_RFUF = 0xf         /*Reserved*/
} apPL131_eBitRateAdj;

/*
 * Description:
 * block transfer protocol
 */
typedef enum apPL131_xProtocol
{
    apPL131_PROTOCOL_T0_CHAR = 0x00,  /*No Block transfer*/
    apPL131_PROTOCOL_T1_BLOCK,        /*Block transfer*/
    apPL131_PROTOCOL_T14_CHAR,        /*  add by gaojianming */
    apPL131_PROTOCOL_NONE             /*not yet decided*/
} apPL131_eProtocol;

/*
 * Description:
 * Direction of data transfer
 */
typedef enum apPL131_xDataDirection
{
    apPL131_RX_FROM_CARD = 0,       /*receive direction*/
    apPL131_TX_TO_CARD              /*transmit direction*/
} apPL131_eDataDirection;

/*
 * Description:
 * Clock Stop Mode
 */
typedef enum apPL131_xClockMode
{
    apPL131_CLOCK_START = 0,       /*Clock Start Initiated*/
    apPL131_CLOCK_STOP             /*Clock Stop Initiated*/
} apPL131_eClockMode;

/*
 * Description:
 * Clock Stop Mode Indicator
 */
typedef enum apPL131_xClkStopInd
{
    apPL131_CLK_STOP_UNSUPPORTED = 0,       /*Clock Stop Mode not supported*/
    apPL131_CLK_STATE_LOW,                  /*Clock State low*/
    apPL131_CLK_STATE_HIGH,                 /*Clock State high*/
    apPL131_CLK_STATE_NO_PREF               /*Clock State no preference*/
} apPL131_eClkStopInd;

/*
 * Description:
 * DMA Control Mode
 */
typedef enum apPL131_xDMAMode
{
    apPL131_DMA_OFF = 0,
    apPL131_DMA_RX,
    apPL131_DMA_TX,
    apPL131_DMA_ON              /*DMA enabled for both TX and RX*/
} apPL131_eDMAMode;

/*
 * Description:
 * This specifies handshaking options
 */
typedef enum apPL131_xHandshake
{
    apPL131_EVEN_NO_HANDSHAKE,        /*even parity, SCI does not check or pull line LOW if error detected*/
    apPL131_ODD_NO_HANDSHAKE,         /*odd parity, SCI does not check or pull line LOW if error detected*/
    apPL131_EVEN_HANDSHAKE,           /*even parity, SCI checks or pulls line LOW if error detected*/
    apPL131_ODD_HANDSHAKE             /*odd parity, SCI checks or pulls line LOW if error detected*/
} apPL131_eHandshake;

/*
 * Description:
 * Setup parameters for Smartcard.  These may be specified in apPL131_ParamsSet,
 * or the defaults may be used.  On initialisation, the default values are used
 * and these can be retrieved with apPL131_ParamsGet
 */
typedef struct apPL131_xSetupParams
{
    u32             ClockFreq;/*Reference Clock frequency in kHz (default 48000kHz)*/
    u32             DebounceTime; /*debounce time in ms (default 136ms)*/
    u32             ActEventTime;/*Card activation process time in clock cycles
                                    must be 40,000 to 45,000 (default 42500)*/
    u32             DeactEventTime;/*Card deactivation process time in
                                    microseconds.  Must not exceed 333 (default 210us)*/
    u32             ATRStartTime;/*Start of ATR after reset in clock cycles
                                    (default 40000)*/
    u32             ATRDuration;/*Duration of ATR after reset in clock cycles
                                    (default 19200)*/
    u32             CharacterTime;/*Character to character timeout (etus)
                                    (default 9600)*/
    u32             BlockTime;/*Timeout between blocks (etus)
                                    (default xxxx)*/
    u32             BlockGuard;/*Minimum time between characters in oposite directions (etus)
                                    (default 16)*/
    u32             CardFreq; /*Card Operating frequency in kHz. This
                                    should be in the range 1 to 5 MHz (default 5000kHz)*/
    BOOL               ClockIsOpenDrain;/*Set TRUE if clock is open drain, or FALSE if
                                    buffer output*/
    u32             ReceiveTime;/*System timeout register. If a byte remains in the
                                    input FIFO for this duration without being retrieved
                                    by the SCI driver, an error will occur. The value is
                                    specified in microseconds*/
    u32             StopTime; /*Stop time if clock stop mode supported*/
    u32             StartTime;/*Start time if clock stop mode supported*/
    u32             RxRetries;/*Maximum number of retries allowed*/
    u32             TxRetries;/*Maximum number of retries allowed*/
    apPL131_eHandshake eRxHandshake;  /*handshaking and parity for receiving*/
    apPL131_eHandshake eTxHandshake;  /*handshaking and parity for transmitting*/
    u32             Padding;
} apPL131_sSetupParams;
typedef struct ATR_xBuffer
{
    u8 ATRData[256];
    u8 ulATRLen;
} ATR_sBuffer;

/*
 * Description:
 * ATR data block - stores all the data for ATR.
 */
typedef struct apPL131_xATRParams
{
    apPL131_eBitRateAdj    eBitRateAdj;  /*bit rate adjustment*/
    apPL131_eClockRateConv eClkRateConv; /*clock rate conversion*/
    apPL131_eClkStopInd    eClkStopInd;  /*clock stop indicator*/
    u8                  Padding;      /*structure alignment*/
    u32                 ClassInd;    /*class indicator*/
    u32                 ProtocolType;/*first offered protocol type*/
    u32                 AltProtocolType; /*alternative offered protocol type*/
    u32                 ChGuard;     /*char-char guard time*/
    u8 *                pATRBuffer;  /*location to write ATR data*/
    u32                 BufferAt;    /*number of characters in buffer*/
    BOOL                   InterfaceByteQual;/*T = 15 has been received indicating global
                                          * interface byte qualifier */
    BOOL                   HasChecksum;  /*are we expecting a checksum?*/
    u32                 Checksum;    /*maintains a checksum*/
    u32                 CharPresent; /*mask of characters for this group*/
    u32                 Grouping;    /*grouping being processed*/
    u32                 Current;     /*character being processed*/
    u32                 NumHist;     /*number of chars of historical data to be received */
    u32                 WI;
} apPL131_sATRParams;

/*
 * Description:
 * General errors for this module.  Errors will be returned typecast
 * to the general error type apError.
 */
typedef enum apPL131_xError
{
    apERR_PL131_NOTINIT = apERR_SCI_START, /*Initialisation not completed*/
    apERR_PL131_INVALIDFREQ,               /*Invalid clock frequency specified*/
    apERR_PL131_USEDEFAULT,                /*Illegal parameter - default used*/
    apERR_PL131_INVPARAM,                  /*Illegal parameter*/
    apERR_PL131_NOCARD,                    /*no card present*/
    apERR_PL131_NODATA,                    /*no data specified*/
    apERR_PL131_NOTREADY,                  /*not ready for data transfer*/
    apERR_PL131_DISABLED                   /*driver is disabled*/
} apPL131_eError;

/*
 * Description:
 * Event codes passed to callback routine
 */
typedef enum apPL131_xEvent
{
    apPL131_EVENTNONE = 0,    /*no event (dummy value)*/
    apPL131_CARDIN,           /*Card has been inserted*/
    apPL131_CARDOUT,          /*Card has been physically removed*/
    apPL131_CARDACT,          /*Card has been activated*/
    apPL131_CARDDEACT,        /*Card has been deactivated*/
    apPL131_ATRCOMPLETE,      /*ATR completed successfully*/
    apPL131_ATRBADVALUE,      /*ATR completed but some values cannot be set*/
    apPL131_ATRFAIL,          /*ATR fails - data not available*/
    apPL131_ATRCHAR,          /*One ATR character received - note that characters
                                which are interpreted by the code are NOT reported*/
    apPL131_TXCOMPLETE,       /*Data Transmit completed*/
    apPL131_RXCOMPLETE,       /*Data Receive completed*/
    apPL131_TXERROR,          /*Error during transmit*/
    apPL131_RXERROR,          /*Error during receive*/
    apPL131_RXPARITYERR,      /*Parity error during data receive*/
    apPL131_RXCHARERR,        /*Error in receipt of character from card
                                when not performing data receive*/
    apPL131_RXCHAR,           /*Receipt of character from card when not
                                performing data receive*/
    apPL131_CLKSTOP,          /*Clock stopped interrupt has occured*/
    apPL131_CLKSTART          /*Clock start interrupt has occured*/
} apPL131_eEvent;

/*
 * Description:
 * data bit convention
 */
typedef enum PL131_xDataConvention
{
    PL131_CONVENTION_DIRECT  = 0x00,  /*Low state on IO = logic zero
                                        LSB is first bit after start bit*/
    PL131_CONVENTION_INVERSE = 0x03   /*Low state on IO = logic one
                                        MSB is first bit after start bit*/
} PL131_eDataConvention;

/*
 * Description:
 * Smartcard state conditions
 */
typedef enum PL131_xStateOptions
{
    PL131_STATE_UNINIT = 0,           /*SCI not yet initialised*/
    PL131_STATE_FIRSTINIT,                /*SCI being initialised*/
    PL131_STATE_DISABLED,                 /*driver disabled*/
    PL131_STATE_NOCARD,                   /*no card currently inserted*/
    PL131_STATE_INACTIVECARD,             /*card not active*/
    PL131_STATE_WAITATR,                  /*wait for ATR sequence to start*/
    PL131_STATE_READATR,                  /*wait for ATR sequence to end*/
    PL131_STATE_READY,                    /*card ready for action*/
    PL131_STATE_RX,                       /*receive currently in progress*/
    PL131_STATE_TX                        /*send currently in progress*/
} PL131_eStateOptions;

typedef volatile struct PL131_xReg
{
    u32 RegData;        /* SCIDATA - Data register*/
    u32 RegCtrl0;       /* SCICR0  - Control register 0*/
    u32 RegCtrl1;       /* SCICR1  - Control register 1*/
    u32 RegCtrl2;       /* SCICR2  - Control register 2*/
    u32 RegClkICC;      /* SCICLKICC - External Smart Card clock freq.*/
    u32 RegBaudValue;   /* SCIVALUE - Cycles of baud rate clock*/
    u32 RegBaud;        /* SCIBAUD - Baud rate clock*/
    u32 RegTide;        /* SCITIDE  - FIFO tide mark register*/
    u32 RegDMACtrl;     /* SCIDMACR - DMA control register*/
    u32 RegStable;      /* SCISTABLE - Debounce Timer*/
    u32 RegATime;       /* SCIATIME - Activation Event time*/
    u32 RegDTime;       /* SCIDTIME - Deactivation Event time*/
    u32 RegATRSTime;    /* SCIATRSTIME - Time to start of ATR reception*/
    u32 RegATRDTime;    /* SCIATRDTIME - Maximum ATR duration*/
    u32 RegStopTime;    /* SCISTOPTIME - Duration before the card clock can be stopped*/
    u32 RegStartTime;   /* SCISTARTTIME - Duration before transactions can commence*/
    u32 RegRetry;       /* SCIRETRY - Retry Limit register*/
    u32 RegChTimeLS;      /* SCICHTIMELS - Character timeout least sig 16 bits*/
    u32 RegChTimeMS;      /* SCICHTIMEMS - Character timeout most sig 16 bits*/
    u32 RegBlkTimeLS;     /* SCIBLKTIMELS - Receive timeout between blocks least sig 16 bits*/
    u32 RegBlkTimeMS;     /* SCIBLKTIMEMS - Receive timeout between blocks most sig 16 bits*/
    u32 RegChGuard;     /* SCICHGUARD - Character guard time*/
    u32 RegBlkGuard;    /* SCIBLKGUARD - Block guard time*/
    u32 RegRxTime;      /* SCIRXTIME - Receive timeout register*/
    u32 RegFlag;        /* SCIFIFOSTATUS - FIFO status register*/
    u32 RegTxCount;     /* SCITXCOUNT - Transmit FIFO count*/
    u32 RegRxCount;     /* SCIRXCOUNT - Receive FIFO count*/
    u32 RegIntMask;     /* SCIIMSC  - Interrupt Enable mask set or clear*/
    u32 RegIntRaw;      /* SCIRIS - Raw interrupt status*/
    u32 RegIntStatus;   /* SCIMIS - Masked interrupt status*/
    u32 RegIntClear;    /* SCIICR - Interrupt clear register*/
    u32 RegSyncAct;     /* SCISYNCACT - Direct access to Smartcard signals*/
    u32 RegSyncData;    /* SCISYNCTX - Smartcard input/output and clock signals*/
    u32 RegSyncRaw;     /* SCISYNCRX - Raw IO and clock status*/
} SCI_REG;

/*
 * Description:
 * Smartcard data block - this is kept as a structure in case multiple
 * instances are required.
 */
typedef volatile struct PL131_xStateStruct
{
    volatile PL131_eStateOptions eCurrentState;    /*current state of the smartcard*/
    apPL131_eProtocol eProtocol;          /*block or character transfer*/
    PL131_eDataConvention eConvention;    /*Data convention*/
    u8 Padding;                       /*structure alignment*/
    SCI_REG * pBase;                   /*base address for registers*/
    //    apPL131_rCallBack rCallBackNotify;    /*notification routine*/
    u8 * pDataBuffer;                 /*location to send/receive data*/
    u32 DataLength;                   /*bytes of data to send/receive*/
    apPL131_sSetupParams sSetupParams;    /*specified setup parameters*/
    apPL131_sATRParams sATRParams;        /*data regarding ATR setup*/
} SCI_STATE_STRU;
/*
 * Description:
 * Callback routine for user notification
 *
 * Implementation:
 * eEventNotified - notification of the event having occurred
 * DataByte - any additional data.  This is described below.
 *
 * The values of DataByte will depend on the event as follows:
 * apPL131_ATRCOMPLETE - The number of bytes received
 * apPL131_ATRCHAR     - Bits 0 to 7 of DataByte hold the ATR data byte.
 *                       Bits 8 to 15 indicate which ATR byte has been received.
 *                       The interface characters TAi to TDi are indicated by 0xAi to 0xDi.
 *                       Historical characters are indicated by 0x00.
 * apPL131_TXERROR, apPL131_RXERROR - Number of bytes remaining to send/receive
 * apPL131_RXCHAR - byte of data received
 * Other event - DataByte undefined
 */
typedef void (*apPL131_rCallBack)(apPL131_eEvent eEventNotified, u32 DataByte);

/*
 * Description:
 * This structure specifies the data which may optionally be passed to the driver
 * in the apPL131_Initialize() function
 */
typedef struct apPL131_xInitialData
{
    u32 ReferenceClock;              /*Reference clock speed in Hz*/
} apPL131_sInitialData;

/* These are definited for the PPS and Voltage exchange process
 */
/*
 * Description:
 * PL131_SCI_Class_C means 1.8V,
 * PL131_SCI_Class_B means 3.0V,
 * PL131_SCI_Class_A is not supported now, 060601
 */
typedef enum PL131_SCIClassType{
    PL131_SCI_Class_C = 180,
    PL131_SCI_Class_B = 300,
    PL131_SCI_Class_BUTT = 0
}SCI_Class_Of_Type;



/*
*2014年3月22日10:36:34 l00258701 
*sci voltage siwtch direction
*/
typedef enum VoltageSwitch
{
    SCI_VOLTAGE_SWITCH_CLASS_C2B        = 0, /*1.8v-3v*/
    SCI_VOLTAGE_SWITCH_CLASS_C2C        = 1, /*1.8v-1.8v*/
    SCI_VOLTAGE_SWITCH_CLASS_B2B        = 2, /*3v-3v*/
    SCI_VOLTAGE_SWITCH_CLASS_CB2ZERO    = 3,/*下电*/
    SCI_VOLTAGE_SWITCH_CLASS_ZERO2CB    = 4,/*上电*/
    SCI_VOLTAGE_SWITCH_BUTT,
}SCI_VOLTAGE_SWITCH_DIRECTION;

typedef enum VoltageSwitchSense
{
    SCI_VOLTAGE_SWITCH_SENSE_CLASS_C2B_IMMEDIATELY  = 0,/*当前为1.8v 立即切换不需要尝试*/
    SCI_VOLTAGE_SWITCH_SENSE_CLASS_UNKNOW_TRY       = 1,/*不关心当前电压状态，都需要尝试*/
    SCI_VOLTAGE_SWITCH_SENSE_CLASS_BUTT,  
}SCI_VOLTAGE_SWITCH_SENSE;

typedef enum ATR_IND_CLASS
{
    ATR_IND_CLASS_NONE  = 0,/*当前为1.8v 立即切换不需要尝试*/
    ATR_IND_CLASS_C     = 1,/*不关心当前电压状态，都需要尝试*/
    ATR_IND_CLASS_BUTT,  
}ATR_IND_CLASS;


typedef struct SCI_VOLTAGE_STATE
{
    SCI_Class_Of_Type sciClassKind;/*SCI Clasee Type*/
    u32 ucSCI_CLASS_SWITCH_FLAG ;/*SCI Clasee Switch Flag*/
    SCI_VOLTAGE_SWITCH_SENSE sci_vlotage_switch_sense;
    ATR_IND_CLASS atrIndClass;/*用于ATR中指示电压，暂时还未使用*/
}SCI_VOLTAGE_STATE;



/*
 * Description:
 * For flag the mode of operation
 */
typedef enum PL131_sciModeSet
{
    PL131_NEGOTIABLE_MODE = 0,  /*the ATR operation mode is Negotiable*/
    PL131_SPECIFIC_MODE     /*the ATR operation mode is Specific*/
} SCI_MODE_OF_OPERATION;


/*
*some variable about PPS
*/
typedef struct PL131_PPS_STRUCT
{
    u8 ucTA1Flag ;/* Baud rate set flag   
                                  0 means TA1 == '11', need no PTS process 
                                  1 means TA1 is not supported or invalid, PTS data is 'FF' '00' 'FF'
                                  2 means TA1 == others that supported by ME*/

    unsigned char ucTA2Data;/*To hold the TA2 data in ATR*/

    u8 PL131_PPS_ACTIVATION ;/*To flag that we initiate a PPS process. 0 means not in PPS process, 1 means we are in PPS process*/
    
    u8 ucPPSFlag;/*The flag to count the PPS process times*/
    
    SCI_MODE_OF_OPERATION ucModeOfOperation;/*To flag the mode of operation in ATR*/
    u32 PL131_PPS_Response ;

}PL131_PPS_STATE;


typedef struct reg_times
{
	u32 CharacterTime;
	u32 BlockTime;
	u32 BlockGuard;
} PL131_T1_TIMES;

/*for protocol mode*/
typedef struct T1Prologue
{
    BSP_U8 NAD;
    BSP_U8 PCB;
    BSP_U8 LEN;
}  PL131_T1_PROLOGUE;
/*
 * Description:
 * For Flag and Parameters used in ATR and PPS and Card activation process
 */
#if 0
typedef struct PL131_Global_Param_For_ATR_PPS_CardAct{
    u8 nActiveT;
    u8 PL131_PPS_ACTIVATION;
    u8 ucTA1Flag;
    u8 ucPPSFlag;
    u8 PL131_PPS_Response;
}G_Param_ATR_PPS_CardAct;
#endif

typedef struct
{
    u8 ucbmFindexDindex;
    u8 ucbmTCCKST0;
    u8 ucbGuardTimeT0;
    u8 ucbWaitingIntegerT0;
    u8 ucbClockStop;
}PL131_PCSC_Parameter;

/*
 * Description:
 * SCI_CLASS_SWITCH_NONE means not do class switch process,
 * SCI_CLASS_SWITCH_PROCESS means doing the process now, 060601
 */
#define SCI_CLASS_SWITCH_NONE 0
#define SCI_CLASS_SWITCH_PROCESS 1

/*
 * --------Main Procedure declarations--------
 * These form the basic API for the MMC
 */

/*
 * Description:
 * Pass setup parameters to the SCI
 *
 * Implementation:
 * Setup parameters are passed in a single data block.
 *
 * This routine should be called after card initialisation and before
 * proceding further.  A read-modify-write strategy can be implemented
 * by using apPL131_ParamsGet() to retrieve the current values.
 *
 * ATR (Answer To Reset) data can be returned in a specified buffer or
 * only through the callback routine, which passes notification of any
 * unknown bytes in the sequence.
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 * pATRBuffer - a buffer where ATR data retrieved from a Smartcard
 *              may be stored.  This may be specified as aNULL or MUST
 *              have sufficient size for data retrieval.
 * rCallback -  the callback routine to which notification of events
 *              will be passed.
 * pSetupParams - pointer to block of setup parameters. If aNULL
 *                is specified for the pointer to this block, current
 *                values (initially defaults) will be unchanged
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE              - successful completion
 *  apERR_PL131_NOTINIT     - initialisation routine not run
 *  apERR_PL131_INVALIDFREQ - frequency specified is illegal and
 *                            this routine aborted
 *  apERR_PL131_USEDEFAULT  - at least one specified parameter is illegal
 *                            and a default value has been used
 */
STATUS            appl131_params_set(SCI_STATE_STRU *  parapState,
                                    u8 * const                pATRBuffer,
                                    apPL131_rCallBack            rCallBack,
                                    const apPL131_sSetupParams * pSetupParams);
/*
 * Description:
 * Disables the driver by disabling interrupts and terminating data transfer
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE          - successful completion
 *  apERR_PL131_NOTINIT - initialisation routine not run
 */
STATUS            appl131_driver_disable(SCI_STATE_STRU * parapState);

/*
 * Description:
 * Initialises activation or deactivation of the Smartcard
 *
 * Implementation:
 * If the card is deactivated, this routine will activate it.
 * If already active, the routine will execute a warm reset.
 * In either case, ATR will be resent from the card.
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 * SetActive - whether made active or inactive
 * pATRBuffer - a buffer where ATR data retrieved from a Smartcard
 *              may be stored.  This may be specified as aNULL or MUST
 *              have sufficient size for data retrieval.
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE              - successful completion
 *  apERR_PL131_NOTINIT     - initialisation routine not run
 *  apERR_PL131_NOCARD      - no card present
 *  apERR_PL131_INVALIDFREQ - frequency specified in setup parameters
 *                            is illegal.
 */
STATUS            appl131_card_active_set(SCI_STATE_STRU * parapState,
                                        BOOL                        SetActive,
                                        unsigned char * const       pATRBuffer);

/*
 * Description:
 * Begins data transfer to the card or from the card
 *
 * Implementation:
 * This will send the specified number of bytes from the buffer to the
 * card, using an interrupt-driven system.  Notification of completion
 * will be through the standard callback routine, specified in apPL131_ParamsSet
 *
 * The card can send data at any time, except when the controller is
 * transmitting.  If the controller has specified a receive buffer with this
 * routine, the data will be placed in the buffer and a callback will be
 * made on completion.  Otherwise, a callback will be made on each character.
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 * eDirection - direction of data transfer
 * pDataBuffer - location of data to send or to store received data
 * DataLength - number of bytes/characters to send or receive
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE - transmission commenced successfully
 *  apERR_PL131_NOTINIT - initialisation routine not run
 *  apERR_PL131_DISABLED - driver is in a disabled state
 *  apERR_PL131_NOCARD - no card present
 *  apERR_PL131_NODATA - buffer is aNULL or length is zero
 */
STATUS            appl131_data_transfer (SCI_STATE_STRU * parapState,
                                        apPL131_eDataDirection      eDirection,
                                        u8 * const               pDataBuffer,
                                        u32                      DataLength);

/*
 * Description:
 * Sets the smartcard interface into a known state.
 *
 * Implementation:
 * Flushes FIFOs,
 * clears all interrupts except for CARDIN and CARDOUT.
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE - successful completion
 *  apERR_PL131_NOTINIT - initialisation routine not run
 */
STATUS            appl131_clean(SCI_STATE_STRU * parapState);


/*
 * Description:
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 * Mode - If the card supports clock stop mode, this parameter is used
 *        to stop or start the clock.
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE - successful completion
 *  apERR_PL131_INVPARAM - invalid mode specified
 */
STATUS            appl131_clock_stop_mode_set (SCI_STATE_STRU * parapState,
                                            apPL131_eClockMode Mode, u32 ucClockStopInd);
/*
 * Description:
 * Initialises all the registers to the clock parameters.
 *
 * Implementation:
 * The specified clock-based parameters, or defaults, will be used to
 * reset the internal registers to an initialised state.
 *
 * Note that this masks off all the interrupts, which must be reasserted
 * after the routine has been called.
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 *
 * Outputs:
 * none
 *
 * Return Value:
 *  apERR_NONE - initialisation is successful
 *  apERR_PL131_INVALIDFREQ - frequency specified is illegal and
 *                      this routine aborted
 *  apERR_PL131_USEDEFAULT - at least one specified parameter is illegal
 *                       and a default value has been used
 */

STATUS  pl131_registers_init(SCI_STATE_STRU * parapState);

/*
 * Description:
 * Handles the ATR initialisation.
 *
 * Implementation:
 * Called when a character is received during ATR reception phase.
 *
 * Inputs:
 * oId - Identifier for the SCI interface
 * ATRChar - Character from ATR stream to process
 *
 * Outputs:
 * none
 *
 * Return Value:
 * none
 */
 void appl131_dma_mode_set(SCI_STATE_STRU * parapState, apPL131_eDMAMode DMAMode);


/*
 * Description:
 * Gets the address of data register for use by the DMA controller.
 *
 * Implementation:
 * Returns address of data register
 *
 * Inputs:
 * oId     - SCI device identifier
 *
 * Outputs:
 * None
 *
 * Return Value:
 * Data register address
 */
u32 appl131_dma_address_get(SCI_STATE_STRU * parapState);
void pl131_atr_process (SCI_STATE_STRU * parapState, u32 CharATR);
void pl131_pps_process(SCI_STATE_STRU * parapState,u32 CharATR);
void pl131_pps_request(SCI_STATE_STRU * parapState);
STATUS appl131_get_clk_freq(u32 *len, unsigned char *pbuf);
STATUS appl131_get_baud_rate(u32 *len, unsigned char *pbuf);
STATUS appl131_get_pcsc_paremeter(unsigned char *pbuf);

#ifdef __cplusplus
 #if __cplusplus
    }
 #endif
#endif /* __cplusplus */

#endif

