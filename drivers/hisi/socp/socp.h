/*
 * Includes for socp.c
 * Mainly take from balong BALONG V7R2
 */

#include <linux/highmem.h>
#include <linux/dma-mapping.h>
#include <linux/semaphore.h>
#include <linux/workqueue.h>
#include <linux/io.h>

#include <linux/huawei/socp/hi_socp.h>
#include <linux/huawei/socp/bsp_socp.h>

#define SOCP_VIRT_PHY(virt) 		 virt_to_phys((void *)virt)
#define SOCP_PHY_VIRT(phy)			 phys_to_virt((unsigned long)phy)
#define SOCP_FLUSH_CACHE(ptr, size) dmac_flush_range((ptr), (ptr)+(size))

typedef int (*socp_task_entry) (void *);

#define SOCP_REG_GBLRST 			(HI_SOCP_GLOBAL_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCRST 			(HI_SOCP_ENC_SRST_CTRL_OFFSET)
#define SOCP_REG_DECRST 			(HI_SOCP_DEC_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCSTAT			(HI_SOCP_ENC_CH_STATUS_OFFSET)
#define SOCP_REG_DECSTAT			(HI_SOCP_DEC_CH_STATUS_OFFSET)
#define SOCP_REG_CLKCTRL			(HI_SOCP_CLK_CTRL_OFFSET)
#define SOCP_REG_PRICFG 			(HI_SOCP_PRIOR_CFG_OFFSET)
#define SOCP_REG_INTTIMEOUT 		(HI_SOCP_INT_TIMEOUT_OFFSET)
#define SOCP_REG_BUFTIMEOUT 		(HI_SOCP_BUFFER_TIMEOUT_OFFSET)
#define SOCP_REG_DEC_PKTLEN 		(HI_SOCP_DEC_PKT_LEN_CFG_OFFSET)
#define SOCP_REG_GBL_INTSTAT		(HI_SOCP_GLOBAL_INT_STATUS_OFFSET)

#define SOCP_REG_ENC_MASK0			(HI_SOCP_ENC_CORE0_MASK0_OFFSET)
#define SOCP_REG_ENC_RAWINT0		(HI_SOCP_ENC_CORE0_RAWINT0_OFFSET)
#define SOCP_REG_ENC_INTSTAT0		(HI_SOCP_ENC_CORE0_INT0_OFFSET)
#define SOCP_REG_APP_MASK1			(HI_SOCP_ENC_CORE0_MASK1_OFFSET)
#define SOCP_REG_MODEM_MASK1		(HI_SOCP_ENC_CORE1_MASK1_OFFSET)
#define SOCP_REG_ENC_RAWINT1		(HI_SOCP_ENC_RAWINT1_OFFSET)
#define SOCP_REG_APP_INTSTAT1		(HI_SOCP_ENC_CORE0_INT1_OFFSET)
#define SOCP_REG_MODEM_INTSTAT1 	(HI_SOCP_ENC_CORE1_INT1_OFFSET)
#define SOCP_REG_ENC_MASK2			(HI_SOCP_ENC_CORE0_MASK2_OFFSET)
#define SOCP_REG_ENC_RAWINT2		(HI_SOCP_ENC_CORE0_RAWINT2_OFFSET)
#define SOCP_REG_ENC_INTSTAT2		(HI_SOCP_ENC_CORE0_INT2_OFFSET)
#define SOCP_REG_APP_MASK3			(HI_SOCP_ENC_CORE0_MASK3_OFFSET)
#define SOCP_REG_MODEM_MASK3		(HI_SOCP_ENC_CORE1_MASK3_OFFSET)
#define SOCP_REG_ENC_RAWINT3		(HI_SOCP_ENC_RAWINT3_OFFSET)
#define SOCP_REG_APP_INTSTAT3		(HI_SOCP_ENC_CORE0_INT3_OFFSET)
#define SOCP_REG_MODEM_INTSTAT3 	(HI_SOCP_ENC_CORE1_INT3_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK0	(HI_SOCP_ENC_CORE1_MASK0_OFFSET)
#define SOCP_REG_ENC_CORE1_INT0 	(HI_SOCP_ENC_CORE1_INT0_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK2	(HI_SOCP_ENC_CORE1_MASK2_OFFSET)
#define SOCP_REG_ENC_CORE1_INT2 	(HI_SOCP_ENC_CORE1_INT2_OFFSET)

#define SOCP_REG_DEC_CORE0MASK0 	(HI_SOCP_DEC_CORE0_MASK0_OFFSET)
#define SOCP_REG_DEC_CORE1MASK0 	(HI_SOCP_DEC_CORE1_MASK0_OFFSET)
#define SOCP_REG_DEC_RAWINT0		(HI_SOCP_DEC_RAWINT0_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT0	(HI_SOCP_DEC_CORE0_INT0_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT0	(HI_SOCP_DEC_CORE1_INT0_OFFSET)
#define SOCP_REG_DEC_MASK1			(HI_SOCP_DEC_CORE0_MASK1_OFFSET)
#define SOCP_REG_DEC_RAWINT1		(HI_SOCP_DEC_CORE0_RAWINT1_OFFSET)
#define SOCP_REG_DEC_INTSTAT1		(HI_SOCP_DEC_CORE0_INT1_OFFSET)
#define SOCP_REG_DEC_CORE0MASK2 	(HI_SOCP_DEC_CORE0_MASK2_OFFSET)
#define SOCP_REG_DEC_CORE1MASK2 	(HI_SOCP_DEC_CORE1NOTE_MASK2_OFFSET)
#define SOCP_REG_DEC_RAWINT2		(HI_SOCP_DEC_RAWINT2_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT2	(HI_SOCP_DEC_CORE0NOTE_NT2_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT2	(HI_SOCP_DEC_CORE1NOTE_INT2_OFFSET)
#define SOCP_REG_DEC_CORE1_MASK1	(HI_SOCP_DEC_CORE1_MASK1_OFFSET)
#define SOCP_REG_DEC_CORE1_INT1 	(HI_SOCP_DEC_CORE1_INT1_OFFSET)

#define SOCP_REG_ENCSRC_BUFWPTR(m)	\
	(HI_SOCP_ENC_SRC_BUFM_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFRPTR(m)	\
	(HI_SOCP_ENC_SRC_BUFM_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFADDR(m)	\
	(HI_SOCP_ENC_SRC_BUFM_ADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG0(m)	\
	(HI_SOCP_ENC_SRC_BUFM_CFG0_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG1(m)	\
	(HI_SOCP_ENC_SRC_BUFM_CFG1_0_OFFSET + m*0x40)

#define SOCP_REG_ENCSRC_RDQWPTR(m)	\
	(HI_SOCP_ENC_SRC_RDQ_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQRPTR(m)	\
	(HI_SOCP_ENC_SRC_RDQ_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQADDR(m)	\
	(HI_SOCP_ENC_SRC_RDQ_BADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQCFG(m)	\
	(HI_SOCP_ENC_SRC_RDQ_CFG_0_OFFSET + m*0x40)

#define SOCP_REG_ENCDEST_BUFWPTR(n) \
	(HI_SOCP_ENC_DEST_BUFN_WPTR_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFRPTR(n) \
	(HI_SOCP_ENC_DEST_BUFN_RPTR_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFADDR(n) \
	(HI_SOCP_ENC_DEST_BUFN_ADDR_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFCFG(n)	\
	(HI_SOCP_ENC_DEST_BUFN_CFG_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRH(n) \
	(HI_SOCP_ENC_DEST_BUFN_THRH_0_OFFSET + n*0x20)

#define SOCP_REG_DECSRC_BUFWPTR(x)	\
	(HI_SOCP_DEC_SRC_BUFX_WPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFRPTR(x)	\
	(HI_SOCP_DEC_SRC_BUFX_RPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFADDR(x)	\
	(HI_SOCP_DEC_SRC_BUFX_ADDR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFCFG0(x)	\
	(HI_SOCP_DEC_SRC_BUFX_CFG0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT0(x)	\
	(HI_SOCP_DEC_BUFX_STATUS0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT1(x)	\
	(HI_SOCP_DEC_BUFX_STATUS1_0_OFFSET + x*0x40)

#define SOCP_REG_DECDEST_BUFWPTR(y) \
	(HI_SOCP_DEC_DEST_BUFY_WPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFRPTR(y) \
	(HI_SOCP_DEC_DEST_BUFY_RPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFADDR(y) \
	(HI_SOCP_DEC_DEST_BUFY_ADDR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFCFG(y)	\
	(HI_SOCP_DEC_DEST_BUFY_CFG0_0_OFFSET + y*0x10)

#define SOCP_REG_ENCCD_DBG0 		(HI_SOCP_ENC_CD_DBG0_OFFSET)
#define SOCP_REG_ENCCD_DBG1 		(HI_SOCP_ENC_CD_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG0		(HI_SOCP_ENC_IBUF_DBG0_OFFSET)
#define SOCP_REG_ENCIBUF_DBG1		(HI_SOCP_ENC_IBUF_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG2		(HI_SOCP_ENC_IBUF_DBG2_OFFSET)
#define SOCP_REG_ENCIBUF_DBG3		(HI_SOCP_ENC_IBUF_DBG3_OFFSET)
#define SOCP_REG_ENCOBUF_DBG0		(HI_SOCP_ENC_OBUF_DBG0_OFFSET)
#define SOCP_REG_ENCOBUF_DBG1		(HI_SOCP_ENC_OBUF_DBG1_OFFSET)
#define SOCP_REG_ENCOBUF_DBG2		(HI_SOCP_ENC_OBUF_DBG2_OFFSET)
#define SOCP_REG_ENCOBUF_DBG3		(HI_SOCP_ENC_OBUF_DBG3_OFFSET)
#define SOCP_REG_DECIBUF_DBG0		(HI_SOCP_DEC_IBUF_DBG0_OFFSET)
#define SOCP_REG_DECIBUF_DBG1		(HI_SOCP_DEC_IBUF_DBG1_OFFSET)
#define SOCP_REG_DECIBUF_DBG2		(HI_SOCP_DEC_IBUF_DBG2_OFFSET)
#define SOCP_REG_DECIBUF_DBG3		(HI_SOCP_DEC_IBUF_DBG3_OFFSET)
#define SOCP_REG_DECOBUF_DBG0		(HI_SOCP_DEC_OBUF_DBG0_OFFSET)
#define SOCP_REG_DECOBUF_DBG1		(HI_SOCP_DEC_OBUF_DBG1_OFFSET)
#define SOCP_REG_DECOBUF_DBG2		(HI_SOCP_DEC_OBUF_DBG2_OFFSET)
#define SOCP_REG_DECOBUF_DBG3		(HI_SOCP_DEC_OBUF_DBG3_OFFSET)

#define BBP_REG_LOG_ADDR(m) 		(0x0200 + 0x10*m)
#define BBP_REG_LOG_WPTR(m) 		(0x0204 + 0x10*m)
#define BBP_REG_LOG_RPTR(m) 		(0x0208 + 0x10*m)
#define BBP_REG_LOG_CFG(m)			(0x020C + 0x10*m)
#define BBP_REG_DS_ADDR 			(0x0280)
#define BBP_REG_DS_WPTR 			(0x0284)
#define BBP_REG_DS_RPTR 			(0x0288)
#define BBP_REG_DS_CFG				(0x028C)
#define BBP_REG_PTR_ADDR			(0x0290)
#define BBP_REG_CH_EN				(0x0294)
#define BBP_REG_PKT_CNT 			(0x0298)
#define BBP_REG_CH_STAT 			(0x029C)
#define BBP_REG_LOG_EN				(0x02B8)

#define SOCP_TOTAL_ENCSRC_CHN		  (0x20)

#define BBP_MAX_CHN 				  (0x09)
#define BBP_MAX_LOG_CHN 			  (0x08)
#define DSP_MAX_CHN 				  (0x02)
#define SOCP_FIXED_MAX_CHAN 		  (BBP_MAX_CHN+DSP_MAX_CHN)
#define SOCP_MAX_ENCSRC_CHN 		  (0x20)
#define SOCP_MAX_ENCDST_CHN 		  (0x07)
#define SOCP_MAX_DECSRC_CHN 		  (0x04)
#define SOCP_MAX_DECDST_CHN 		  (0x10)
#define SOCP_CCORE_ENCSRC_CHN_BASE	  (4)
#define SOCP_CCORE_ENCSRC_CHN_NUM	  (5)

#define SOCP_DSPLOG_CHN 			  (0x0e)
#define SOCP_BBPLOG_CHN 			  (SOCP_DSPLOG_CHN + 2)
#define SOCP_BBPDS_CHN				  (SOCP_BBPLOG_CHN + 8)
#define SOCP_FIXCHN_BASE			  (SOCP_DSPLOG_CHN)
#define SOCP_FIXCHN_END 			  (SOCP_BBPDS_CHN)

#define SOCP_REG_BASE				  HI_SOCP_REGBASE_ADDR_VIRT

#define BBP_REG_ARM_BASEADDR		  (0x20200000)
#define TENSILICA_CORE0_DRAM_ADDR	  (0x49f80000)
#define SOCP_REG_BASEADDR			  (g_strSocpStat.baseAddr)

/*SOCP BBP channel buffer addr*/
#define PBXA9_DRAM_BBPDS_VIRT		  0 /*need check*/
#define PBXA9_DRAM_BBPDS_PHYS		  0 /*need check*/
#define PBXA9_DRAM_BBPDS_SIZE		  0 /*need check*/
#define INT_LVL_SOCP				  INT_LVL_SOCP0

/*sys ctrl reg*/
#define INTEGRATOR_SC_BASE			  (SOCP_REG_BASEADDR+0x14)	/*need check*/
#define INTEGRATOR_SC_SIZE			  SZ_4K
#define SOCP_BBPDS_CHN_ADDR 		  (PBXA9_DRAM_BBPDS_PHYS)
#define SOCP_BBPDS_CHN_SIZE 		  (PBXA9_DRAM_BBPDS_SIZE)

#define SOCP_DSP_CHN_ADDR		   (0x49F80000 + 0x400) /*need check*/
#define SOCP_DSP_CHN_SIZE		   (0x2000) /*need check*/

#define SOCP_DSPLOG_CHN_ADDR		  (SOCP_DSP_CHN_ADDR)
#define SOCP_DSPLOG_CHN_SIZE		  (SOCP_DSP_CHN_SIZE)
#define SOCP_BBPLOG_CHN_SIZE		  (0x2000)
#define SOCP_FIXEDID_BASE			  (SOCP_DSPLOG_CHN - SOCP_FIXCHN_BASE)

#define SOCP_DSPLOG_DST_BUFID		  ((s32) 1)
#define SOCP_BBPLOG_DST_BUFID		  ((s32) 1)
#define SOCP_BBPDS_DST_BUFID		  ((s32) 1)

typedef struct tagSOCP_RING_BUF_S {
	u32 u32Start;
	u32 u32End;
	u32 u32Write;
	u32 u32Read;
	u32 u32Length;
	u32 u32IdleSize;
} SOCP_RING_BUF_S;

typedef struct tagSOCP_ENCSRC_CHAN_S {
	u32 u32ChanID;
	u32 u32ChanEn;
	u32 u32DestChanID;
	u32 u32BypassEn;
	u32 u32AllocStat;
	u32 u32LastRdSize;
	u32 u32RdThreshold;
	SOCP_ENCSRC_CHNMODE_E eChnMode;
	SOCP_CHAN_PRIORITY_E ePriority;
	SOCP_DATA_TYPE_E eDataType;
	SOCP_DATA_TYPE_EN_E eDataTypeEn;
	SOCP_ENC_DEBUG_EN_E eDebugEn;
	SOCP_RING_BUF_S sEncSrcBuf;
	SOCP_RING_BUF_S sRdBuf;
	socp_event_cb event_cb;
	socp_rd_cb rd_cb;
} SOCP_ENCSRC_CHAN_S;

typedef struct tagSOCP_ENCSRC_FIXCHAN_S {
	u32 u32ChanID;
	u32 u32ChanEn;
	u32 u32DestChanID;
	SOCP_ENCSRC_CHNMODE_E eChnMode;
	SOCP_CHAN_PRIORITY_E ePriority;
	SOCP_DATA_TYPE_E eDataType;
	SOCP_DATA_TYPE_EN_E eDataTypeEn;
	SOCP_ENC_DEBUG_EN_E eDebugEn;
	SOCP_RING_BUF_S sEncSrcBuf;
	SOCP_RING_BUF_S sRdBuf;
	socp_event_cb event_cb;
	socp_rd_cb rd_cb;
} SOCP_ENCSRC_FIXCHAN_S;

typedef struct tagSOCP_ENCDST_CHAN_S {
	u32 u32ChanID;
	u32 u32SetStat;
	u32 u32Thrh;
	SOCP_RING_BUF_S sEncDstBuf;
	SOCP_EVENT_E eChnEvent;
	socp_event_cb event_cb;
	socp_read_cb read_cb;
} SOCP_ENCDST_CHAN_S;

typedef struct tagSOCP_DECSRC_CHAN_S {
	u32 u32ChanID;
	u32 u32ChanEn;
	u32 u32SetStat;
	u32 u32RdThreshold;
	SOCP_DATA_TYPE_EN_E eDataTypeEn;
	SOCP_DECSRC_CHNMODE_E eChnMode;
	SOCP_RING_BUF_S sDecSrcBuf;
	SOCP_RING_BUF_S sDecRdBuf;
	socp_event_cb event_cb;
	socp_rd_cb rd_cb;
} SOCP_DECSRC_CHAN_S;

typedef struct tagSOCP_DECDST_CHAN_S {
	u32 u32ChanID;
	u32 u32AllocStat;
	SOCP_DATA_TYPE_E eDataType;
	SOCP_RING_BUF_S sDecDstBuf;
	socp_event_cb event_cb;
	socp_read_cb read_cb;
} SOCP_DECDST_CHAN_S;

typedef struct tagSOCP_GBL_STATE {
	s32 bInitFlag;
	u32 baseAddr;
	u32 armBaseAddr;
	u32 tensiAddr;
	u32 bbpDsAddr;
	struct semaphore u32EncSrcSemID;
	struct semaphore u32EncDstSemID;
	struct semaphore u32DecSrcSemID;
	struct semaphore u32DecDstSemID;
	s32 u32EncSrcTskID;
	s32 u32EncDstTskID;
	s32 u32DecSrcTskID;
	s32 u32DecDstTskID;
	u32 u32IntEncSrcHeader;
	u32 u32IntEncSrcRD;
	u32 u32IntEncDstTfr;
	u32 u32IntEncDstOvf;
	u32 u32IntEncDstThresholdOvf;
	u32 u32IntDecSrcErr;
	u32 u32IntDecDstTfr;
	u32 u32IntDecDstOvf;
	SOCP_ENCSRC_CHAN_S sEncSrcChan[SOCP_MAX_ENCSRC_CHN];
	SOCP_ENCDST_CHAN_S sEncDstChan[SOCP_MAX_ENCDST_CHN];
	SOCP_DECSRC_CHAN_S sDecSrcChan[SOCP_MAX_DECSRC_CHN];
	SOCP_DECDST_CHAN_S sDecDstChan[SOCP_MAX_DECDST_CHN];
} SOCP_GBL_STATE;

typedef struct tagSOCP_DEBUG_GBL_S {
	u32 u32SocpAllocEncSrcCnt;
	u32 u32SocpAllocEncSrcSucCnt;
	u32 u32SocpSetEncDstCnt;
	u32 u32SocpSetEncDstSucCnt;
	u32 u32SocpSetDecSrcCnt;
	u32 u32SocpSetDeSrcSucCnt;
	u32 u32SocpAllocDecDstCnt;
	u32 u32SocpAllocDecDstSucCnt;
	u32 u32SocpAppEtrIntCnt;
	u32 u32SocpAppSucIntCnt;
} SOCP_DEBUG_GBL_S;

typedef struct tagSOCP_DEBUG_ENCSRC_S {
	u32 u32SocpFreeEncSrcCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpSoftResetEncSrcCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpStartEncSrcCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpStopEncSrcCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpRegEventEncSrcCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpGetWBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpGetWBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32socp_write_doneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32socp_write_doneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32socp_write_doneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpRegRdCBEncSrcCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpGetRdBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpGetRdBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpReadRdDoneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpReadRdDoneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpReadRdDoneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpEncSrcTskHeadCbCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpEncSrcTskHeadCbOriCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpEncSrcTskRdCbCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpEncSrcTskRdCbOriCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpEncSrcIsrHeadIntCnt[SOCP_MAX_ENCSRC_CHN];
	u32 u32SocpEncSrcIsrRdIntCnt[SOCP_MAX_ENCSRC_CHN];
} SOCP_DEBUG_ENCSRC_S;

typedef struct tagSOCP_DEBUG_ENCDST_S {
	u32 u32SocpRegEventEncDstCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpRegReadCBEncDstCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpGetReadBufEncDstEtrCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpGetReadBufEncDstSucCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32socp_read_doneEncDstEtrCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32socp_read_doneEncDstSucCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32socp_read_doneEncDstFailCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32socp_read_doneZeroEncDstCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32socp_read_doneValidEncDstCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstTskTrfCbCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstTskTrfCbOriCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstTskOvfCbCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstTskOvfCbOriCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstIsrTrfIntCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstIsrOvfIntCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstTskThresholdOvfCbCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstTskThresholdOvfCbOriCnt[SOCP_MAX_ENCDST_CHN];
	u32 u32SocpEncDstIsrThresholdOvfIntCnt[SOCP_MAX_ENCDST_CHN];
} SOCP_DEBUG_ENCDST_S;

typedef struct tagSOCP_DEBUG_DECSRC_S {
	u32 u32SocpSoftResetDecSrcCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpStartDecSrcCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpStopDecSrcCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpRegEventDecSrcCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpGetWBufDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpGetWBufDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32socp_write_doneDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32socp_write_doneDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32socp_write_doneDecSrcFailCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpRegRdCBDecSrcCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpGetRdBufDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpGetRdBufDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpReadRdDoneDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpReadRdDoneDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpReadRdDoneDecSrcFailCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpDecSrcIsrErrIntCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpDecSrcTskErrCbCnt[SOCP_MAX_DECSRC_CHN];
	u32 u32SocpDecSrcTskErrCbOriCnt[SOCP_MAX_DECSRC_CHN];
} SOCP_DEBUG_DECSRC_S;

typedef struct tagSOCP_DEBUG_DECDST_S {
	u32 u32SocpFreeDecDstCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpRegEventDecDstCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpRegReadCBDecDstCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpGetReadBufDecDstEtrCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpGetReadBufDecDstSucCnt[SOCP_MAX_DECDST_CHN];
	u32 u32socp_read_doneDecDstEtrCnt[SOCP_MAX_DECDST_CHN];
	u32 u32socp_read_doneDecDstSucCnt[SOCP_MAX_DECDST_CHN];
	u32 u32socp_read_doneDecDstFailCnt[SOCP_MAX_DECDST_CHN];
	u32 u32socp_read_doneZeroDecDstCnt[SOCP_MAX_DECDST_CHN];
	u32 u32socp_read_doneValidDecDstCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpDecDstIsrTrfIntCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpDecDstTskTrfCbCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpDecDstTskTrfCbOriCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpDecDstIsrOvfIntCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpDecDstTskOvfCbCnt[SOCP_MAX_DECDST_CHN];
	u32 u32SocpDecDstTskOvfCbOriCnt[SOCP_MAX_DECDST_CHN];
} SOCP_DEBUG_DECDST_S;

/*debug info*/
typedef struct tagSOCP_DEBUG_INFO_S {
	SOCP_DEBUG_GBL_S sSocpDebugGBl;
	SOCP_DEBUG_ENCSRC_S sSocpDebugEncSrc;
	SOCP_DEBUG_ENCDST_S sSocpDebugEncDst;
	SOCP_DEBUG_DECSRC_S sSocpDebugDecSrc;
	SOCP_DEBUG_DECDST_S sSocpDebugDecDst;
} SOCP_DEBUG_INFO_S;

#define SOCP_CHN_BUSY					((s32)1)
#define SOCP_CHN_IDLE					((s32)0)

#define SOCP_CHN_ALLOCATED				((s32)1)
#define SOCP_CHN_UNALLOCATED			((s32)0)

#define SOCP_CHN_ENABLE 				((s32)1)
#define SOCP_CHN_DISABLE				((s32)0)

#define SOCP_CHN_SET					((s32)1)
#define SOCP_CHN_UNSET					((s32)0)

#define SOCP_ENCSRC_BYPASS_ENABLE		((s32)1)
#define SOCP_ENCSRC_BYPASS_DISABLE		((s32)0)

#define SOCP_DECSRC_DEBUG_ENBALE		((s32)1)
#define SOCP_DECSRC_DEBUG_DISBALE		((s32)0)

#define SOCP_CORE0_DEC_OUTOVFINT_MASK	((s32)(1))
#define SOCP_DEC_INERRINT_MASK			((s32)(1<<1))
#define SOCP_CORE0_DEC_TFRINT_MASK		((s32)(1<<2))
#define SOCP_CORE1_DEC_TFRINT_MASK		((s32)(1<<3))
#define SOCP_CORE1_DEC_OUTOVFINT_MASK	((s32)(1<<4))
#define SOCP_MODEM_ENC_RDINT_MASK		((s32)(1<<10))
#define SOCP_APP_ENC_RDINT_MASK 		((s32)(1<<11))
#define SOCP_APP_ENC_OUTOVFINT_MASK 	((s32)(1<<12))
#define SOCP_MODEM_ENC_FLAGINT_MASK 	((s32)(1<<13))
#define SOCP_APP_ENC_FLAGINT_MASK		((s32)(1<<14))
#define SOCP_APP_ENC_TFRINT_MASK		((s32)(1<<15))
#define SOCP_DEC_SRCINT_NUM 			(6)

#define SOCP_TRANS_TIMEOUT_DEFAULT		(0x17)
#define SOCP_OVERFLOW_TIMEOUT_DEFAULT	(0x5969)

#define SOCP_DEC_PKTLGTH_MAX			(0x04)
#define SOCP_DEC_PKTLGTH_MIN			(0x06)
#define SOCP_TIMEOUT_MAX				(0xffff)
#define SOCP_DEC_MAXPKT_MAX 			(0x1000)
#define SOCP_DEC_MINPKT_MAX 			(0x1f)
#define SOCP_ENC_SRC_BUFLGTH_MAX		(0x7ffffff)
#define SOCP_ENC_SRC_RDLGTH_MAX 		(0xffff)
#define SOCP_ENC_DST_BUFLGTH_MAX		(0x1fffff)
#define SOCP_ENC_DST_TH_MAX 			(0x7ff)
#define SOCP_DEC_SRC_BUFLGTH_MAX		(0xffff)
#define SOCP_DEC_SRC_RDLGTH_MAX 		(0xffff)
#define SOCP_DEC_DST_BUFLGTH_MAX		(0xffff)
#define SOCP_DEC_DST_TH_MAX 			(0xff)

#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK	(0x007f0000)
#define SOCP_ENC_DST_BUFF_OVF_MASK				(0x0000007f)

#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN	(16)

#define SOCP_STATE_SC_ENC_OFFSET			0x0c
#define SOCP_STATE_SC_DEC_OFFSET			0x10

#define SOCP_STATE_SC_MASK				0x00000001

#define SOCP_RESET_TIME 				(1000)
#define SOCP_GBLRESET_TIME				(100)

extern SOCP_GBL_STATE g_strSocpStat;

#define SOCP_CHECK_INIT() \
	do {\
		if (!g_strSocpStat.bInitFlag) {\
			pr_info("the module has not been initialized!\n");\
			return BSP_ERR_SOCP_NOT_INIT;\
		} \
	} while (0)

#define SOCP_CHECK_PARA(para) \
	do {\
		if (NULL == para) {\
			pr_info("the parameter is NULL!\n");\
			return BSP_ERR_SOCP_NULL;\
		} \
	} while (0)

#define SOCP_CHECK_BUF_ADDR(start, end) \
	do {\
		if (start >= end) {\
			pr_info("the buff is valid!\n");\
			return BSP_ERR_SOCP_INVALID_PARA;\
		} \
	} while (0)

#define SOCP_CHECK_CHAN_TYPE(para, type) \
	do {\
		if (type != para) {\
			pr_info("the Chan's Type is Valid!\n");\
			return BSP_ERR_SOCP_INVALID_CHAN;\
		} \
	} while (0)

#define SOCP_CHECK_CHAN_ID(para, id) \
	do {\
		if (para >= id) {\
			pr_info("the Chan Id is Valid!\n");\
			return BSP_ERR_SOCP_INVALID_CHAN;\
		} \
	} while (0)

#define SOCP_CHECK_ENCSRC_CHAN_ID(id) \
	do {\
		if ((id >= SOCP_CCORE_ENCSRC_CHN_BASE) && \
			(id < (SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM))) {\
			pr_info("the Chan Id is Valid!\n"); \
			return BSP_ERR_SOCP_INVALID_CHAN; \
		} \
	} while (0)

#define SOCP_CHECK_8BYTESALIGN(para) \
	do {\
		if (0 != (para%8)) {\
			pr_info("the parameter is not 8 bytes aligned!\n");\
			return BSP_ERR_SOCP_NOT_8BYTESALIGN;\
		} \
	} while (0)

#define SOCP_CHECK_ENCSRC_CHNMODE(para) \
	do {\
		if (para >= SOCP_ENCSRC_CHNMODE_BUTT) {\
			pr_info("encoder src channele mode is %d,it is valid!\n", para);\
			return BSP_ERR_SOCP_INVALID_PARA;\
		} \
	} while (0)

#define SOCP_CHECK_DECSRC_CHNMODE(para) \
	do {\
		if (para >= SOCP_DECSRC_CHNMODE_BUTT) {\
			pr_info("decoder dst channele mode is %d,it is valid!\n", para);\
			return BSP_ERR_SOCP_INVALID_PARA;\
		} \
	} while (0)

#define SOCP_CHECK_CHAN_PRIORITY(para) \
	do {\
		if (para >= SOCP_CHAN_PRIORITY_BUTT) {\
			pr_info("encoder src channele priority is %d,it is valid!\n", para);\
			return BSP_ERR_SOCP_INVALID_PARA;\
		} \
	} while (0)

#define SOCP_CHECK_DATA_TYPE(para) \
	do {\
		if (para >= SOCP_DATA_TYPE_BUTT) {\
			pr_info("channel data type is %d,it is valid!\n", para);\
			return BSP_ERR_SOCP_INVALID_PARA;\
		} \
	} while (0)

#define SOCP_CHECK_ENCSRC_ALLOC(id) \
	do {\
		if (SOCP_CHN_ALLOCATED != g_strSocpStat.sEncSrcChan[id].u32AllocStat) {\
			pr_info("encoder src[%d] not allocated!\n", id);\
			return BSP_ERR_SOCP_INVALID_CHAN;\
		} \
	} while (0)

#define SOCP_CHECK_ENCDST_SET(id) \
	do {\
		if (SOCP_CHN_SET != g_strSocpStat.sEncDstChan[id].u32SetStat) {\
			pr_info("encoder dst[%d] set failed!\n", id);\
			return BSP_ERR_SOCP_INVALID_CHAN;\
		} \
	} while (0)

#define SOCP_CHECK_DECSRC_SET(id) \
	do {\
		if (SOCP_CHN_SET != g_strSocpStat.sDecSrcChan[id].u32SetStat) {\
			pr_info("decoder[%d] src set failed!\n", id);\
			return BSP_ERR_SOCP_INVALID_CHAN;\
		} \
	} while (0)

#define SOCP_CHECK_DECDST_ALLOC(id) \
	do {\
		if (SOCP_CHN_ALLOCATED != g_strSocpStat.sDecDstChan[id].u32AllocStat) {\
			pr_info("decoder dst[%d] alloc failed!\n", id);\
			return BSP_ERR_SOCP_INVALID_CHAN;\
		} \
	} while (0)

#define SOCP_CHECK_DATA_TYPE_EN(param) \
	do {\
		if (param >= SOCP_DATA_TYPE_EN_BUTT) {\
			pr_info("the data type en is valid, para is %d!\n", param); \
			return BSP_ERR_SOCP_INVALID_PARA; \
		} \
	} while (0)

#define SOCP_CHECK_ENC_DEBUG_EN(param) \
	do {\
		if (param >= SOCP_ENC_DEBUG_EN_BUTT) {\
			pr_info("the enc src debug en is valid, para is %d!\n", param); \
			return BSP_ERR_SOCP_INVALID_PARA; \
		} \
	} while (0)

s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId);
s32 socp_soft_free_decsrc_chan(u32 u32DecSrcChanId);
s32 socp_reset_dec_chan(u32 u32ChanID);
s32 socp_get_index(u32 u32Size, u32 *index);
u32 BSP_SOCP_CanSleep(void);

#define BSP_REG_SETBITS(base, reg, pos, bits, val) \
	(BSP_REG(base, reg) = (BSP_REG(base, reg) & \
	(~((((u32)1 << (bits)) - 1) << (pos)))) |\
	((u32)((val) & (((u32)1 << (bits)) - 1)) << (pos)))

#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) \
	& (((u32)1 << (bits)) - 1))

#define SOCP_REG_WRITE(reg, data) \
	(writel(data, (void *)(g_strSocpStat.baseAddr + reg)))
#define SOCP_REG_READ(reg, result) \
	(result = readl((void *)(g_strSocpStat.baseAddr + reg)))
#define SOCP_REG_SETBITS(reg, pos, bits, val) \
	BSP_REG_SETBITS(g_strSocpStat.baseAddr, reg, pos, bits, val)
#define SOCP_REG_GETBITS(reg, pos, bits) \
	BSP_REG_GETBITS(g_strSocpStat.baseAddr, reg, pos, bits)

#define BBP_REG_WRITE(reg, data) \
	(writel(data, (void *)(g_strSocpStat.armBaseAddr + reg)))
#define BBP_REG_READ(reg, result) \
	(result = readl((void *)(g_strSocpStat.armBaseAddr + reg)))
#define BBP_REG_SETBITS(reg, pos, bits, val) \
	BSP_REG_SETBITS(g_strSocpStat.armBaseAddr, reg, pos, bits, val)
#define BBP_REG_GETBITS(reg, pos, bits) \
	BSP_REG_GETBITS(g_strSocpStat.armBaseAddr, reg, pos, bits)

