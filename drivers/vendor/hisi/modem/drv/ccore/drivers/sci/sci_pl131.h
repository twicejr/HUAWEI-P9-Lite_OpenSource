/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  sci_pl131.h
*
*   作    者 :  Y00171698
*
*   描    述 :  本文件命名为"sci_pl131.h", 为ARM公司提供的sample code
*            做了部分改动，编程规范不做修改。
*
*   修改记录 :  
*************************************************************************/
    
#ifndef SCI_PL131_H
#define SCI_PL131_H
    
#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "product_config.h"
#include "osl_types.h"
    /*
     * --------Type definitions--------
     */
    
    
    /*
     * Bit masks for register RegData - SCIDATA
     */
#define bsPL131_REGDATA_DATA      ( (long) 0)  /*Data bits*/
#define bwPL131_REGDATA_DATA      ( (long) 8)
#define bsPL131_REGDATA_PARITY    ( (long) 8)  /*Parity flag*/
#define bwPL131_REGDATA_PARITY    ( (long) 1)
    
    /*
     * Description:
     * Bit masks for register RegCtrl0 - SCICR0
     */
#define bsPL131_REGCTRL0_CONV     ( (long) 0)  /*Bit 0 Sense of data and parity bits*/
#define bwPL131_REGCTRL0_CONV     ( (long) 2)  /* 1 = inverse, 0 = direct convention*/
                                                     /*Bit 1 Order of data bits */
                                                     /* 1 = msb first, 0 = lsb first */
#define bsPL131_REGCTRL0_TXPARITY ( (long) 2)  /*Transmit parity setting*/
#define bwPL131_REGCTRL0_TXPARITY ( (long) 1)  /* 1 = Odd, 0 = Even parity */
    
#define bsPL131_REGCTRL0_TXNAK    ( (long) 3)  /*Enables character transmit handshaking*/
#define bwPL131_REGCTRL0_TXNAK    ( (long) 1)
    
#define bsPL131_REGCTRL0_RXPARITY ( (long) 4)  /*Receive parity setting*/
#define bwPL131_REGCTRL0_RXPARITY ( (long) 1)  /* 1 = Odd, 0 = Even parity */
    
#define bsPL131_REGCTRL0_RXNAK    ( (long) 5)  /*Enables character receive handshaking*/
#define bwPL131_REGCTRL0_RXNAK    ( (long) 1)
    
#define bsPL131_REGCTRL0_CLKDIS   ( (long) 6)  /*If card supports clock stop mode*/
#define bwPL131_REGCTRL0_CLKDIS   ( (long) 1)  /*This bit can be used to start/stop clock*/

#define bsPL131_REGCTRL0_CLKVAL   ( (long) 7)  /*If card supports clock stop mode*/
#define bwPL131_REGCTRL0_CLKVAL   ( (long) 1)  /*This bit defines inactive state of clock*/
    
    /* Useful bit masks */
#define bsPL131_REGCTRL0_TX       ( (long) 2)  /*Transmit parity and handshake settings*/
#define bwPL131_REGCTRL0_TX       ( (long) 2)
#define bsPL131_REGCTRL0_RX       ( (long) 4)  /*Receive parity and handshake settings*/
#define bwPL131_REGCTRL0_RX       ( (long) 2)
#define bsPL131_REGCTRL0_RX_TX    ( (long) 2)  /*Transmit/Receive parity and handshake settings*/
#define bwPL131_REGCTRL0_RX_TX    ( (long) 4)
    
    
    /*
      接受发送时是否有校验位
    */
#define bsPL131_REGCTRL0_PARITYBIT   ( (long) 8)  
#define bwPL131_REGCTRL0_PARITYBIT   ( (long) 1)  
    /*
     * Description:
     * Bit masks for register RegCtrl1 - SCICR1
     */
#define bsPL131_REGCTRL1_ATRDEN   ( (long) 0)  /*ATR duration timeout enable*/
#define bwPL131_REGCTRL1_ATRDEN   ( (long) 1)
#define bsPL131_REGCTRL1_BLKEN    ( (long) 1)  /*Block timeout enable*/
#define bwPL131_REGCTRL1_BLKEN    ( (long) 1)
#define bsPL131_REGCTRL1_MODE     ( (long) 2)  /*Interface direction of communication control*/
#define bwPL131_REGCTRL1_MODE     ( (long) 1)
#define bsPL131_REGCTRL1_CLKZ1    ( (long) 3)  /*SCICLK output config*/
#define bwPL131_REGCTRL1_CLKZ1    ( (long) 1)
#define bsPL131_REGCTRL1_BGTEN    ( (long) 4)  /*Block guard time enable*/
#define bwPL131_REGCTRL1_BGTEN    ( (long) 1)
#define bsPL131_REGCTRL1_EXDBNCE  ( (long) 5)  /*External debounce setting*/
#define bwPL131_REGCTRL1_EXDBNCE  ( (long) 1)
#define bsPL131_REGCTRL1_SYNCCARD ( (long) 6)  /*Asynchronous or synchronous mode selected*/
#define bwPL131_REGCTRL1_SYNCCARD ( (long) 1)
    
    /*
     * Description:
     * Bit masks for register RegCtrl2 - SCICR2
     */
#define bsPL131_REGCTRL2_STARTUP  ( (long) 0)  /*activate the card*/
#define bwPL131_REGCTRL2_STARTUP  ( (long) 1)
#define bsPL131_REGCTRL2_FINISH   ( (long) 1)  /*deactivate the card*/
#define bwPL131_REGCTRL2_FINISH   ( (long) 1)
#define bsPL131_REGCTRL2_WRESET   ( (long) 2)  /*initiate a warm reset*/
#define bwPL131_REGCTRL2_WRESET   ( (long) 1)
    
    /*
     * Description:
     * Bit masks for register RegClkICC - SCICLKICC
     */
#define bsPL131_REGCLKICC_DATA   ( (long) 0)  /*Divisor for clock frequency*/
#define bwPL131_REGCLKICC_DATA   ( (long) 8)
    
    /*
     * Description:
     * Bit masks for register RegBaudValue - SCIVALUE
     */
#define bsPL131_REGBAUDVALUE_DATA   ( (long) 0)  /*Baud cycles per etu.*/
#define bwPL131_REGBAUDVALUE_DATA   ( (long) 8)
    
    /*
     * Description:
     * Bit masks for register RegBaud - SCIBAUD
     */
#define bsPL131_REGBAUD_DATA     ( (long) 0)  /*Divisor for baud rate clock*/
#define bwPL131_REGBAUD_DATA     ( (long) 16)
    
    /*
     * Description:
     * Bit masks for register RegTide - SCITIDE
     */
     /*FIFO深度修改至32位*/
#define bsPL131_REGTIDE_TX   ( (long) 0)      /*tidemark when transmitting*/
#define bwPL131_REGTIDE_TX   ( (long) 6)
#define bsPL131_REGTIDE_RX   ( (long) 6)      /*tidemark when receiving*/
#define bwPL131_REGTIDE_RX   ( (long) 6)
    
    /*
     * Description:
     * Bit masks for register RegDMACtrl - SCIDMACR
     */
#define bsPL131_REGDMA_RX   ( (long) 0)      /*Enables DMA for receive FIFO*/
#define bwPL131_REGDMA_RX   ( (long) 1)
#define bsPL131_REGDMA_TX   ( (long) 1)      /*Enables DMA for transmit FIFO*/
#define bwPL131_REGDMA_TX   ( (long) 1)
#define bsPL131_REGDMA      ( (long) 0)      /*Enables DMA for both transmit and receive FIFO*/
#define bwPL131_REGDMA      ( (long) 2)
    
    /*
     * Description:
     * Bit masks for register RegStable - SCISTABLE
     */
#define bsPL131_REGSTABLE_DATA    ( (long) 0)  /*Debounce time before card */
#define bwPL131_REGSTABLE_DATA    ( (long) 8)  /* is indicated as inserted*/
    
    /*
     * Description:
     * Bit masks for register RegAtime - SCIATIME
     */
#define bsPL131_REGATIME_DATA     ( (long) 0)  /*Activation time for the stages */
#define bwPL131_REGATIME_DATA     ( (long) 16) /* of the activation process*/
    
    /*
     * Description:
     * Bit masks for register RegDtime - SCIDTIME
     */
#define bsPL131_REGDTIME_DATA     ( (long) 0)  /*Deactivation time for the stages */
#define bwPL131_REGDTIME_DATA     ( (long) 16) /* of the deactivation process*/
    
    /*
     * Description:
     * Bit masks for register RegATRSTime - SCIATRSTIME
     */
#define bsPL131_REGATRSTIME_DATA  ( (long) 0)  /*Time to start of ATR reception*/
#define bwPL131_REGATRSTIME_DATA  ( (long) 16)
    
    /*
     * Description:
     * Bit masks for register RegATRDTime - SCIATRDTIME
     */
#define bsPL131_REGATRDTIME_DATA  ( (long) 0)  /*Max duration of ATR character */
#define bwPL131_REGATRDTIME_DATA  ( (long) 16) /* stream register */
    
    /*
     * Description:
     * Bit masks for register RegStopTime - SCISTOPTIME
     */
#define bsPL131_REGSTOPTIME_DATA  ( (long) 0)  /*Duration before the card clock */
#define bwPL131_REGSTOPTIME_DATA  ( (long) 12) /*  can be stopped */
    
    /*
     * Description:
     * Bit masks for register RegStartTime - SCISTARTTIME
     */
#define bsPL131_REGSTARTTIME_DATA  ( (long) 0)  /* Duration before transactions */
#define bwPL131_REGSTARTTIME_DATA  ( (long) 12) /*  can commence */
    
    /*
     * Description:
     * Bit masks for register RegRetry - SCIRETRY
     */
#define bsPL131_REGRETRY_TX   ( (long) 0)      /*Number of retries when transmitting*/
#define bwPL131_REGRETRY_TX   ( (long) 3)
#define bsPL131_REGRETRY_RX   ( (long) 3)      /*Number of retries when receiving*/
#define bwPL131_REGRETRY_RX   ( (long) 3)
    
    /*
     * Description:
     * Bit masks for register RegChTimeLS - SCICHTIMELS and RegChTimeMS - SCICHTIMEMS
     */
#define bsPL131_REGCHTIME_DATA   ( (long) 0)  /*Character timeout bits*/
#define bwPL131_REGCHTIME_DATA   ( (long) 16)
#define bsPL131_REGCHTIME_DATA_Bit32   ( (long) 0)
#define bwPL131_REGCHTIME_DATA_Bit32   ( (long) 32)

    
    /*
     * Description:
     * Bit masks for register RegBlkTimeLS - SCIBLKTIMELS and RegBlkTimeMS - SCIBLKTIMEMS
     */
#define bsPL131_REGBLKTIME_DATA  ( (long) 0)  /*Block timeout*/
#define bwPL131_REGBLKTIME_DATA  ( (long) 16)
#define bsPL131_REGBLKTIME_DATA_Bit32  ( (long) 0)  /*Block timeout*/
#define bwPL131_REGBLKTIME_DATA_Bit32  ( (long) 32)

    
    /*
     * Description:
     * Bit masks for register RegChGuard - SCICHGUARD
     */
#define bsPL131_REGCHGUARD_DATA   ( (long) 0)  /*Char to char extra guard time*/
#define bwPL131_REGCHGUARD_DATA   ( (long) 8)
    
    /*
     * Description:
     * Bit masks for register RegBlkGuard - SCIBLKGUARD
     */
#define bsPL131_REGBLKGUARD_DATA   ( (long) 0)  /*Block to block extra guard time*/
#define bwPL131_REGBLKGUARD_DATA   ( (long) 8)
    
    /*
     * Description:
     * Bit masks for register RegRxTime - SCIRXTIME
     */
#define bsPL131_REGRXTIME_DATA    ( (long) 0)  /*Receive read timeout value*/
#define bwPL131_REGRXTIME_DATA    ( (long) 16)
    
    /*
     * Description:
     * Bit masks for register RegFlag - SCIFIFOSTATUS
     */
#define bsPL131_REGFLAG_TXFULL    ( (long) 0)  /*TX FIFO is full*/
#define bwPL131_REGFLAG_TXFULL    ( (long) 1)
#define bsPL131_REGFLAG_TXEMPTY   ( (long) 1)  /*TX FIFO is empty*/
#define bwPL131_REGFLAG_TXEMPTY   ( (long) 1)
#define bsPL131_REGFLAG_RXFULL    ( (long) 2)  /*RX FIFO is full*/
#define bwPL131_REGFLAG_RXFULL    ( (long) 1)
#define bsPL131_REGFLAG_RXEMPTY   ( (long) 3)  /*RX FIFO is empty*/
#define bwPL131_REGFLAG_RXEMPTY   ( (long) 1)
    
    /*
     * Description:
     * Bit masks for register RegTxCount - SCITXCOUNT
     */
#define bsPL131_REGTXCOUNT_CLR    ( (long) 0)  /*clear bit for the FIFO counter*/
#define bwPL131_REGTXCOUNT_CLR    ( (long) 1)
#define bsPL131_REGTXCOUNT_DATA   ( (long) 0)  /*data bits for the FIFO counter*/
#define bwPL131_REGTXCOUNT_DATA   ( (long) 6)
    
    /*
     * Description:
     * Bit masks for register RegRxCount - SCIRXCOUNT
     */
#define bsPL131_REGRXCOUNT_CLR    ( (long) 0)  /*clear bit for the FIFO counter*/
#define bwPL131_REGRXCOUNT_CLR    ( (long) 1)
#define bsPL131_REGRXCOUNT_DATA   ( (long) 0)  /*data bits for the FIFO counter*/
#define bwPL131_REGRXCOUNT_DATA   ( (long) 6)
    
    /*
     * Description:
     * Interrupt Bit masks for registers
     * RegIntMask - SCIIMSC, RegIntRaw - SCIRIS, RegIntStatus - SCIMIS, RegIntClear - SCIICR
     */
#define bsPL131_REGINTMASK_CARDIN     ( (long) 0)  /*Smartcard inserted*/
#define bwPL131_REGINTMASK_CARDIN     ( (long) 1)
#define bsPL131_REGINTMASK_CARDOUT    ( (long) 1)  /*Smartcard removed*/
#define bwPL131_REGINTMASK_CARDOUT    ( (long) 1)
#define bsPL131_REGINTMASK_CARDUP     ( (long) 2)  /*Smartcard powered up*/
#define bwPL131_REGINTMASK_CARDUP     ( (long) 1)
#define bsPL131_REGINTMASK_CARDDOWN   ( (long) 3)  /*Smart card powered down*/
#define bwPL131_REGINTMASK_CARDDOWN   ( (long) 1)
#define bsPL131_REGINTMASK_TXERR      ( (long) 4)  /*Char transmit error*/
#define bwPL131_REGINTMASK_TXERR      ( (long) 1)
#define bsPL131_REGINTMASK_ATRSTOUT   ( (long) 5)  /*ATR receive start timeout*/
#define bwPL131_REGINTMASK_ATRSTOUT   ( (long) 1)
#define bsPL131_REGINTMASK_ATRDTOUT   ( (long) 6)  /*ATR receive duration timeout*/
#define bwPL131_REGINTMASK_ATRDTOUT   ( (long) 1)
#define bsPL131_REGINTMASK_BLKTOUT    ( (long) 7)  /*between block timeout*/
#define bwPL131_REGINTMASK_BLKTOUT    ( (long) 1)
#define bsPL131_REGINTMASK_CHTOUT     ( (long) 8)  /*between char timeout*/
#define bwPL131_REGINTMASK_CHTOUT     ( (long) 1)
#define bsPL131_REGINTMASK_RTOUT      ( (long) 9)  /*receive FIFO timeout*/
#define bwPL131_REGINTMASK_RTOUT      ( (long) 1)
#define bsPL131_REGINTMASK_RORI       ( (long) 10)  /*receive overrun interrupt*/
#define bwPL131_REGINTMASK_RORI       ( (long) 1)
#define bsPL131_REGINTMASK_CLKSTPI    ( (long) 11)  /*Card clock stopped interrupt*/
#define bwPL131_REGINTMASK_CLKSTPI    ( (long) 1)
#define bsPL131_REGINTMASK_CLKACTI    ( (long) 12)  /*Card clock active interrupt*/
#define bwPL131_REGINTMASK_CLKACTI    ( (long) 1)
#define bsPL131_REGINTMASK_RXTIDE     ( (long) 13) /*receive FIFO tide mark*/
#define bwPL131_REGINTMASK_RXTIDE     ( (long) 1)
#define bsPL131_REGINTMASK_TXTIDE     ( (long) 14) /*transmit FIFO tide mark*/
#define bwPL131_REGINTMASK_TXTIDE     ( (long) 1)
    
    /*
     * Description:
     * Derived Interrupt Bit masks for registers
     * RegIntMask and RegIntID
     */
#define bsPL131_REGINTMASK_ALL        ( (long) 0)  /*all registers*/
#define bwPL131_REGINTMASK_ALL        ( (long) 15)
#define bsPL131_REGINTMASK_STATIC     ( (long) 0)  /*static (clearable) registers*/
#define bwPL131_REGINTMASK_STATIC     ( (long) 13)
#define bsPL131_REGINTMASK_ATRNOSTART ( (long) 5)  /*ATR doesn't start ATRSTOUT*/
#define bwPL131_REGINTMASK_ATRNOSTART ( (long) 1)
#define bsPL131_REGINTMASK_ATRSTOP    ( (long) 5)  /*ATR failure ATRSTOUT and ATRDTOUT*/
#define bwPL131_REGINTMASK_ATRSTOP    ( (long) 2)
#define bsPL131_REGINTMASK_FAILDATA   ( (long) 4)  /*Any transmission failure*/
#define bwPL131_REGINTMASK_FAILDATA   ( (long) 5)
    
    /*
     * Description:
     * Bit masks for register RegSyncAct - SCISYNCACT
     */
#define bsPL131_REGSTAT_POWER     ( (long) 0)  /*Smart card Vcc*/
#define bwPL131_REGSTAT_POWER     ( (long) 1)
#define bsPL131_REGSTAT_CRESET    ( (long) 1)  /*Smart card RESET*/
#define bwPL131_REGSTAT_CRESET    ( (long) 1)
#define bsPL131_REGSTAT_CLKEN     ( (long) 2)  /*Smart card clock enable*/
#define bwPL131_REGSTAT_CLKEN     ( (long) 1)
#define bsPL131_REGSTAT_DATAEN    ( (long) 3)  /*Smart card data enable*/
#define bwPL131_REGSTAT_DATAEN    ( (long) 1)
#define bsPL131_REGSTAT_FCB       ( (long) 4)  /*Smart card Function code bit*/
#define bwPL131_REGSTAT_FCB       ( (long) 1)
    
#define bsPL131_REGSTAT_TRICLKOUT ( (long) 5)  /*Clock tristate output buffer enable*/
#define bwPL131_REGSTAT_TRICLKOUT ( (long) 1)
#define bsPL131_REGSTAT_TRICLKEN  ( (long) 6)  /*Tristate control for external off-chip clock buffer*/
#define bwPL131_REGSTAT_TRICLKEN  ( (long) 1)
#define bsPL131_REGSTAT_CLKOUT    ( (long) 7)  /*Smart card clock output*/
#define bwPL131_REGSTAT_CLKOUT    ( (long) 1)
#define bsPL131_REGSTAT_TRIDATAOUT ( (long) 8)  /*Tristate output buffer control for data*/
#define bwPL131_REGSTAT_TRIDATAOUT ( (long) 1)
#define bsPL131_REGSTAT_TRIDATAEN ( (long) 9)  /*Tristate control for external off-chip data buffer*/
#define bwPL131_REGSTAT_TRIDATAEN ( (long) 1)
#define bsPL131_REGSTAT_PRESENT   ( (long) 10)  /*Is smartcard present?*/
#define bwPL131_REGSTAT_PRESENT   ( (long) 1)
    
    /*
     * Description:
     * Bit masks for register RegSyncData - SCISYNCTX
     */
#define bsPL131_REGSYNCDATA_WDATA   ( (long) 0)  /*Synchronous IO line control*/
#define bwPL131_REGSYNCDATA_WDATA   ( (long) 1)
#define bsPL131_REGSYNCDATA_WCLK    ( (long) 1)  /*Synchronous clock control*/
#define bwPL131_REGSYNCDATA_WCLK    ( (long) 1)
#define bsPL131_REGSYNCDATA_WDATAEN ( (long) 2)  /*Synchronous data enable control*/
#define bwPL131_REGSYNCDATA_WDATAEN ( (long) 1)
#define bsPL131_REGSYNCDATA_WCLKEN  ( (long) 3)  /*Synchronous clock enable control*/
#define bwPL131_REGSYNCDATA_WCLKEN  ( (long) 1)
#define bsPL131_REGSYNCDATA_WRST    ( (long) 4)  /*SCIARDRST signal control*/
#define bwPL131_REGSYNCDATA_WRST    ( (long) 1)
#define bsPL131_REGSYNCDATA_WFCB    ( (long) 5)  /*SCIFCB signal control*/
#define bwPL131_REGSYNCDATA_WFCB    ( (long) 1)
    
    /*
     * Description:
     * Bit masks for register RegSyncRaw - SCISYNCRX
     */
#define bsPL131_REGRAWSTAT_DATA     ( (long) 0)  /*Raw value of IO line*/
#define bwPL131_REGRAWSTAT_DATA     ( (long) 1)
#define bsPL131_REGRAWSTAT_CLK      ( (long) 1)  /*Raw value of clock*/
#define bwPL131_REGRAWSTAT_CLK      ( (long) 1)
    
    
    /*
     * Description:
     * Bit masks for register RegIntRaw - SCIRIS
     */
    
#define bsPL131_REGINTROW_ALL        ( (long) 0)  
#define bwPL131_REGINTROW_ALL        ( (long) 15)
    
    
    /*
     * Description:
     * Default values for Smartcard setup parameters (see apPL131_sSetupParams)
     */
#define PL131_DEF_DEBOUNCE     ((u32) 136)      /*debounce time = 136ms*/
#define PL131_DEF_ACTEVENT     ((u32) 42500)    /*activation time 42000 card clock cycles*/
#define PL131_DEF_DEACTEVENT   ((u32) 200)      /*deact time 200us*/
#define PL131_DEF_ATRSTIME     ((u32) 45000)    /*ATR start within 40000 card clock cycles*/
#define PL131_DEF_ATRDTIME     ((u32) 19200)    /*ATR complete within 19200 ETUs*/
#define PL131_DEF_CHARTIME     ((u32) 9600)     /*char interval 9600 ETUs*/
#define PL131_DEF_BLOCKTIME    ((u32) 9600)     /*block timeout interval 9600 ETUs*/
/*2014年5月22日12:27:39 l00258701 add T=1 */
/*CWT = (11+ 2CWI ) etu cwt=13 7816-3 11.4.3*/
#define PL131_DEF_CHARTIME_T1     ((u32) 13)
/* 第一个TB（T=1）的位8~位5编码BWI从0~9。“A”~“F”是为今后使用预设。缺省值BWI=4。BWT是根据下面公式通过BWI计算出来的。
 * BWT=11etu+2^BWI*960*（Fd/f）
 **/
#define PL131_DEF_BLOCKTIME_T1    ((u32) 15371)     /*block timeout interval 15371 ETUs*/
/*7816-3 11.2 BGT=22 also see pl131 document*/
#define PL131_DEF_BLKGUARDTIME    ((u32) 16)       /*minimum time between characters 16 ETUs*/
#define PL131_DEF_BLKGUARDTIME_T1 ((u32) 22)       /*minimum time between characters 22 ETUs*/

#define PL131_MIN_BLKGUARDTIME_T1    ((u32) 971)       /*minimum time between characters 16 ETUs*/
#define PL131_MAX_BLKGUARDTIME_T1 ((u32) 15371)       /*minimum time between characters 22 ETUs*/


/*2014年5月22日12:27:13  l00258701 end*/

/* BEGIN: Modified by b00198513, 2012-05-29 ,DTS2012052503590 解决参考时钟超出48兆问题*/
#define PL131_DEF_CARDFREQ     ((u32) 3750UL)   /*5760UL)*/   /*card frequency 1000kHz*/

#define PL131_DEF_CARD4000     ((u32) 4000UL)   /*card frequency 3579kHz*/
#define PL131_DEF_CARD5MHZ     ((u32) 5000UL)   /*card frequency 5000kHz*/
#define PL131_DEF_RXTIME       ((u32) 16000)    /*receive timeout - ~13ms (4.5MHz)*/
/* BEGIN: Modified by z67193, 2010-8-24, 复位应答之后，重传次数设置为3  */
#define PL131_DEF_RX_RETRIES   ((u32) 3)        /*number of retries allowed*/
#define PL131_DEF_TX_RETRIES   ((u32) 3)        /*number of retries allowed*/
#define PL131_DEF_MIN_BAUDVALUE  5
#define PL131_DEF_MAX_BAUDVALUE  255

    /*
     * Description:
     * Default minimum values for Start and Stop times if Clock Stop Mode supported
     */
/* BEGIN: Modified by z67193, 2010-9-1 逻辑中提前计时2个etu, 最长etu=372/1，2604=1860+2*372/1*/
#define PL131_DEF_STOPTIME     ((u32) 2604)      /*Stop time = 1860 clock cycles*/
#define PL131_DEF_STARTTIME    ((u32) 700)       /*Start time = 700 clock cycles*/
    
    /*
     * Description:
     * Inactive state of card clock when clock stop mode supported
     */
    typedef enum PL131_xClockValue
    {
        PL131_CLOCK_LOW = 0,         /*Inactive Clock LOW*/
        PL131_CLOCK_HIGH             /*Inactive Clock High*/
    } SCI_ClOCL_VALUE;
    
#define PL131_DEF_CLOCK_STATE PL131_CLOCK_LOW
    /*
     * Description:
     * FIFO sizes
     */    
/*FIFO深度修改为32*/    
#define PL131_FIFO_SIZE_TX    ((long) 32)
#define PL131_FIFO_SIZE_RX    ((long) 32)
    /*
     * Description:
     * This macro converts a frequency specified in clock cycles to
     * a value in etus (elementary time units) - duration of character
     * bits.  During ATR, one etu = 372 / ClockFreq seconds
     */
#define PL131_ATR_FREQ_TO_ETU(_freq) ( (_freq) * 372 / PL131_sConfig.ClockFreq )
    
    /*
     * Description:
     * This macro writes a value in a register if it lies within allowed bounds,
     * or a default value otherwise.  The parameters are:
     *  Register name
     *  Minimum allowed value
     *  Maximum allowed value
     *  Scaling factor for the data and default values
     *  Data value - element in state structure to use
     *  Default value - default to use (this is also scaled by the scaling factor)
     *  Default check variable - this boolean is set TRUE if the default is used
     *  Failure check variable - this boolean is set TRUE if the original and 
     *   default are out of range
     */
/*====================================================================*
What:
Why :
Who :liumengcun, 2009-9-7
*========================== Orignal Code ============================*/
#if 1
#define PL131_REG_DATA_WRITE(_reg,_min,_max,_scl,_dat,_def,_isdef,_isfail)  \
        {                                                                       \
            /*check the original value unless being initialised*/               \
            if ((pState->eCurrentState>PL131_STATE_FIRSTINIT) &&                \
                ((long)(pState->_dat * _scl)>=_min) &&                        \
                (pState->_dat * _scl<=_max))                                    \
            {                                                                   \
                _reg=pState->_dat * _scl;                                       \
            }                                                                   \
            /*check the default value*/                                         \
            else if (((long)((_def) * _scl)>=_min) &&                         \
                     ((_def) * _scl<=_max))                                     \
            {                                                                   \
                pState->_dat=_def;                                              \
                _isdef=TRUE;                                                    \
                _reg=pState->_dat * _scl;                                       \
            }                                                                   \
            /*fail*/                                                            \
            else                                                                \
            {                                                                   \
                _isfail=TRUE;                                                   \
            }                                                                   \
        }
#endif
/*========================= Modify Code ===============================*/
    
    /*
     * Description:
     * This macro writes a 32 bit value in to two 16 bit registers
     * if it lies within allowed bounds, or a default value otherwise.  
     * The parameters are:
     *  _reg - Register name
     *  _min - Minimum allowed value
     *  _max - Maximum allowed value
     *  _scl - Scaling factor for the data and default values
     *  _dat - Data value - element in state structure to use
     *  _def - Default value - default to use (this is also scaled by the scaling factor)
     *  _isdef - Default check variable - this boolean is set TRUE if the original
     *                                    is out of range and the default is used.
     *  _isfail - Failure check variable - this boolean is set TRUE if the original and 
     *                                     default are out of range
     */
#define PL131_DBL_REG_DATA_WRITE(_reg,_min,_max,_scl,_dat,_def,_isdef,_isfail)\
        {                                                                         \
            u32 temp;                                                         \
            /*check the original value unless being initialised*/                 \
            if ((pState->eCurrentState > PL131_STATE_FIRSTINIT) &&                \
                ((long)(pState->_dat * _scl) >= _min) &&                        \
                ((pState->_dat * _scl) <= _max))                                  \
            {                                                                     \
                temp = pState->_dat * _scl;                                       \
                _reg ## MS = (temp & 0xFFFF0000) >> 16;                           \
                _reg ## LS = temp & 0x0000FFFF;                                   \
            }                                                                     \
            /*check the default value*/                                           \
            else if (((long)((_def) * _scl) >= _min) &&                         \
                     (((_def) * _scl) <= _max))                                   \
            {                                                                     \
                pState->_dat=_def;                                                \
                _isdef=TRUE;                                                      \
                temp = pState->_dat * _scl;                                       \
                _reg ## MS = (temp & 0xFFFF0000) >> 16;                           \
                _reg ## LS = temp & 0x0000FFFF;                                   \
            }                                                                     \
            /*fail*/                                                              \
            else                                                                  \
            {                                                                     \
                _isfail=TRUE;                                                     \
            }                                                                     \
        }
    
    
    
    
    
    /*
     * Description:
     * ATR data bit masks
     */
#define bwPL131_ATR_CONV      8         /*Convention bit*/
#define bsPL131_ATR_CONV      0
#define bwPL131_ATR_HIST      4         /*num chars of hist data*/
#define bsPL131_ATR_HIST      0
#define bwPL131_ATR_PROT      4         /*protocol type*/
#define bsPL131_ATR_PROT      0
#define bwPL131_ATR_PRESENT   4         /*mask of data items present*/
#define bsPL131_ATR_PRESENT   4
#define bwPL131_ATR_CLKRATE   4       /*mask of clock rate conversion*/
#define bsPL131_ATR_CLKRATE   4
#define bwPL131_ATR_BITRATE   4       /*mask of bit rate adjustment*/
#define bsPL131_ATR_BITRATE   0
#define bwPL131_ATR_CLOCK_STOP   2       /*mask of clock stop indicator*/
#define bsPL131_ATR_CLOCK_STOP   6
#define bwPL131_ATR_CLASS_IND   6       /*mask of class indicator*/
#define bsPL131_ATR_CLASS_IND   0
    
#define PL131_ATR_GROUPSTART 127       /*start of ATR (pre-groups)*/
#define PL131_ATR_GROUPDONE 128       /*end of ATR (post groups)*/
    
    /*
     * Description:
     * This combines the ATR grouping and character into one byte such
     * that the first character of grouping i becomes 0xAi, the second
     * 0xBi etc.
     */
#define PL131_ATR_ITEM(_grp,_cur) ((unsigned short)((((_cur) + 9)<<4) + (_grp)))
    
    /*
     * Description:
     * ATR returned characters
     */
#define PL131_ATR_CONV_NORM       0x3b      /*TS character of ATR for direct convention*/
#define PL131_ATR_CONV_NORM_INV   0x3f      /*TS character of ATR for inverse convention converted by hardware*/
#define PL131_ATR_CONV_INV        0x03      /*TS character of ATR for inverse convention to be converted by software*/
    //#define PL131_ATR_TZ_T0           0x0e
    //#define PL131_ATR_TZ_T1           0x06
    //#define PL131_ATR_TD1             0x81
    //#define PL131_ATR_TD2             0x31
    //#define PL131_ATR_TA3_MIN         0x10
    //#define PL131_ATR_TA3_MAX         0xff
    //#define PL131_ATR_TB3_BWI_MAX     0x04
    //#define PL131_ATR_TB3_CWI_MAX     0x05
    
    /*
     * Macro for executing a non-null callback function
     */
#define PL131_CALLBACK(_a,_b) if (pState->rCallBackNotify) {pState->rCallBackNotify(_a,_b);}
    
    /*
     * Description:
     * For testing only - error simulation values
     */
    typedef enum PL131_xSimError
    {
        PL131_SIM_NOERROR,
        PL131_SIM_PARITY,                    /*parity error in data*/
        PL131_SIM_CHECKSUM,                  /*checksum error in data*/
        PL131_SIM_STOUT,                     /*timeout on start of ATR*/
        PL131_SIM_DTOUT,                     /*failure during ATR*/
        PL131_SIM_ILLEGALCONV,               /*illegal convention*/
        PL131_SIM_ILLEGALPROT,               /*illegal protocol*/
        PL131_SIM_CLOCKSTOPMODE              /*simulate clock stop mode*/
    } PL131_eSimError;


    
    /*BEGIN PN: DTS2014012009585  l00258701 lixiaofan 2014年1月21日15:45:44*/
#define  SCI_USIM_CLASS_C_DETECT_RETRY_CNT    3
#define  SCI_MAX_USIM_CARD_DETECT_RETRY_CNT   6
    /*END PN: DTS2014012009585  l00258701 lixiaofan 2014年1月21日15:45:44*/

    
    /*
     * Description:
     * For testing purposes only.  If the preprocessor constant 'apPL131_SIMULATE' is defined, and an external
     * variable PL131_SimulateError is set to the defined value, this will execute the specified code
     */
#if defined(apPL131_SIMULATE) && apPL131_SIMULATE
    #define apPL131_SIMULATE_ERROR(_val,_code) {__weak u32 PL131_SimulateError;if ((&PL131_SimulateError) && (PL131_SimulateError== _val)) {_code}}
#else
    #define apPL131_SIMULATE_ERROR(_val,_code)
#endif
    
    /*
     * --------Procedure declarations--------
     */
    
    /*The 'include no functions' option allows access to the private types only*/
#ifndef PL131_INCLUDE_NO_FUNCTIONS
    
                                
#endif
    
#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */
    
#endif
    


