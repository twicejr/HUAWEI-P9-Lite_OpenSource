
#ifndef    _EDMA_DRIVER_H_
#define    _EDMA_DRIVER_H_

#include <osl_types.h>
#include <bsp_edma.h>

/* edma interrupt state, in:irq_idx */ 
#define EDMA_INT_BASE(in)   (0x0+0x40*in)
#define _INT_STAT        0x00
#define _INT_TC1         0x04
#define _INT_TC2         0x08
#define _INT_ERR1        0x0C
#define _INT_ERR2        0x10
#define _INT_ERR3        0x14
#define _INT_TC1_MASK    0x18
#define _INT_TC2_MASK    0x1C
#define _INT_ERR1_MASK   0x20
#define _INT_ERR2_MASK   0x24
#define _INT_ERR3_MASK   0x28
#define EDMA_INT_STAT(in)       ( EDMA_INT_BASE(in) + _INT_STAT      )
#define EDMA_INT_TC1(in)        ( EDMA_INT_BASE(in) + _INT_TC1       )
#define EDMA_INT_TC2(in)        ( EDMA_INT_BASE(in) + _INT_TC2       )
#define EDMA_INT_ERR1(in)       ( EDMA_INT_BASE(in) + _INT_ERR1      )
#define EDMA_INT_ERR2(in)       ( EDMA_INT_BASE(in) + _INT_ERR2      )
#define EDMA_INT_ERR3(in)       ( EDMA_INT_BASE(in) + _INT_ERR3      )
#define EDMA_INT_TC1_MASK(in)   ( EDMA_INT_BASE(in) + _INT_TC1_MASK  )
#define EDMA_INT_TC2_MASK(in)   ( EDMA_INT_BASE(in) + _INT_TC2_MASK  )
#define EDMA_INT_ERR1_MASK(in)  ( EDMA_INT_BASE(in) + _INT_ERR1_MASK )
#define EDMA_INT_ERR2_MASK(in)  ( EDMA_INT_BASE(in) + _INT_ERR2_MASK )
#define EDMA_INT_ERR3_MASK(in)  ( EDMA_INT_BASE(in) + _INT_ERR3_MASK )

/* edma raw interrupt */
#define EDMA_INT_TC1_RAW    0x600
#define EDMA_INT_TC2_RAW    0x608
#define EDMA_INT_ERR1_RAW   0x610
#define EDMA_INT_ERR2_RAW   0x618
#define EDMA_INT_ERR3_RAW   0x620

#define EDMA_SREQ       0x660
#define EDMA_LSREQ      0x664
#define EDMA_BREQ       0x668
#define EDMA_LBREQ      0x66C
#define EDMA_FREQ       0x670
#define EDMA_LFREQ      0x674
#define EDMA_CH_PRI     0x688
#define EDMA_CH_STAT    0x690
#define EDMA_DMA_CTRL   0x698

/* channel state regs   0x700~0x70c + 0x10*cn */
#define CHAN_STATE_BASE(cn)  (0x700+0x10*cn)
#define _CURR_CNT1        0x0
#define _CURR_CNT0        0x4
#define _CURR_SRC_ADDR    0x8
#define _CURR_DES_ADDR    0xC
#define CHAN_CX_CURR_CNT1(cn)        (CHAN_STATE_BASE(cn) + _CURR_CNT1     )
#define CHAN_CX_CURR_CNT0(cn)        (CHAN_STATE_BASE(cn) + _CURR_CNT0     )
#define CHAN_CX_CURR_SRC_ADDR(cn)    (CHAN_STATE_BASE(cn) + _CURR_SRC_ADDR )
#define CHAN_CX_CURR_DES_ADDR(cn)    (CHAN_STATE_BASE(cn) + _CURR_DES_ADDR )

/* channel config regs   0x800~0x820 + 0x40*cn */
#define CHAN_CFG_BASE(cn)  (0x800+0x40*cn)
#define _LLI         0x0
#define _BINDX       0x4
#define _CINDX       0x8
#define _CNT1        0xC
#define _CNT0        0x10
#define _SRC_ADDR    0x14
#define _DES_ADDR    0x18
#define _CONFIG      0x1C
#define _AXI_CONF    0x20
#define CHAN_CX_LLI(cn)         ( CHAN_CFG_BASE(cn) + _LLI      )
#define CHAN_CX_BINDX(cn)       ( CHAN_CFG_BASE(cn) + _BINDX    )
#define CHAN_CX_CINDX(cn)       ( CHAN_CFG_BASE(cn) + _CINDX    )
#define CHAN_CX_CNT1(cn)        ( CHAN_CFG_BASE(cn) + _CNT1     )
#define CHAN_CX_CNT0(cn)        ( CHAN_CFG_BASE(cn) + _CNT0     )
#define CHAN_CX_SRC_ADDR(cn)    ( CHAN_CFG_BASE(cn) + _SRC_ADDR )
#define CHAN_CX_DES_ADDR(cn)    ( CHAN_CFG_BASE(cn) + _DES_ADDR )
#define CHAN_CX_CONFIG(cn)      ( CHAN_CFG_BASE(cn) + _CONFIG   )
#define CHAN_CX_AXI_CONF(cn)    ( CHAN_CFG_BASE(cn) + _AXI_CONF )

#endif

