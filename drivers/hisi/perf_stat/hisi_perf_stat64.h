/* hisi_perf_stat.h */

#ifndef HISI_PERF_STAT_H
#define HISI_PERF_STAT_H

#define PERF_IS_ALIGNED(x, b)    ((x % b) == 0)

#define Count_xINy_Num(x, y)     ((y % x) ? ((y / x) + 1) : (y / x))

#define PERF_OK      0
#define PERF_ERROR   -1

/*register define*/
#define PERF_CLKGATE        0x00

#define PERF_SAMPSTART      0x04
#define PERF_SAMPCNT        0x08
#define PERF_SAMPNUM        0x0C
#define PERF_SAMPSTOP       0x10
#define PERF_SAMPPORT       0x14

#define PERF_ADDRMODE       0x18
/* #define PERF_SEQADDR        0x1C */
#define PERF_SEQLEN         0x20
/* #define PERF_LISTADDR       0x24 */
/* #define PERF_CURLIST        0x28 */

#define PERF_RSTCNT         0x2C

#define PERF_INTEN          0x30
#define PERF_INTCLR         0x34
#define PERF_INTRAWSTAT     0x38
#define PERF_INTMASKSTAT    0x3C

#define PERF_CURSAMPCNT     0x40
/* #define PERF_CURSAMPADDR    0x44 */
#define PERF_OVERTIMECNT    0x48
#define PERF_DBGFIFOFULL    0x4C
#define PERF_DBGBLOCK       0x50
#define PERF_MONITORRST     0x54

#define PERF_SEQADDR_L      0x58
#define PERF_SEQADDR_H      0x5c
#define PERF_LISTADDR_L      0x60
#define PERF_LISTADDR_H      0x64
#define PERF_LASTDESCADDR_L   0x68
#define PERF_LASTDESCADDR_H   0x6C
#define PERF_CURSAMPADDR_L    0x70
#define PERF_CURSAMPADDR_H    0x74

/*Sample port*/
#define PERF_PORT_DSS0     (0)
#define PERF_PORT_DSS1     (1)
#define PERF_PORT_CCI0     (2)
#define PERF_PORT_CCI1     (3)
#define PERF_PORT_GPU      (4)
#define PERF_PORT_MODEM0   (5)
#define PERF_PORT_MODEM1   (6)
#define PERF_PORT_ISP0     (7)
#define PERF_PORT_ISP1     (8)
#define PERF_PORT_VDEC     (9)
#define PERF_PORT_VENC     (10)
#define PERF_PORT_IVP      (11)
#define PERF_PORT_SYSNOC   (12)
#define PERF_PORT_AUDIO    (13)
#define PERF_PORT_EMMC     (14)
#define PERF_PORT_USBOTG   (15)
#define PERF_PORT_UFS   (16)
#define PERF_PORT_PCIE   (17)
#define PERF_PORT_ISP_SRT_DRM    (18)
#define PERF_PORT_CCI3    (19)
#define PERF_PORT_CCI4    (20)
#define PERF_PORT_DMSS1    (21)
#define PERF_PORT_DMSS0   (22)
#define PERF_PORT_GPU1   (23)
#define PERF_PORT_IPF     (24)
#define PERF_PORT_DMCA     (25)
#define PERF_PORT_DMCB     (26)
#define PERF_PORT_DMCC     (27)
#define PERF_PORT_DMCD      (28)
#define PERF_PORT_RESERVE0   (29)
#define PERF_PORT_RESERVE1    (30)
#define PERF_PORT_RESERVE2     (31)
#define PERF_PORT_NUM      (32)
#define PERF_PORT_ALL      (0xFFFFFFFF)
#define PERF_PORT_BIT(x)   (1 << (x))

/*perfstat irq*/
#define PERF_INT_SAMP_DONE   (0x1 << 0)
#define PERF_INT_OVER_TIME   (0x1 << 1)
#define PERF_INT_LIST_DONE   (0x1 << 2)
#define PERF_INT_LIST_ERR    (0x1 << 3)
#define PERF_INT_ALL         (0x0F)

/*sample addr mode*/
#define PERF_SEQ_ADDR_MODE    0
#define PERF_LIST_ADDR_MODE   1

#define PERF_SAMPLE_ALWAYS    0
#define PERF_MIN_PAGE_NUM     2

#define PERF_IS_WORK          0
#define PERF_IS_REST          1

#define PERF_LIST_CFG_NORMAL  0x21ULL
#define PERF_LIST_CFG_INT     0x25ULL
#define PERF_LIST_CFG_LINK    0x31ULL

#define PERF_SAMPLE_HIGHSPEED     1
#define PERF_MALLOC_PAGES_100M    25600
#define PERF_HIGHSPEED_DATA_PATH  "/data/perf_data_hs.data"

/*hisilicon perf sample_data_head struct*/
typedef struct {
	u64 sample_cnt_current;
	u64 sample_period;
	u64 sample_cnt_legacy;
	u64 sample_port;
} perf_sample_data_head;

typedef struct {
	u64 sample_cnt_current;
	u64 sample_period;
	u64 sample_data_valid;
	u64 sample_port;
} perf_sample_data_end;

/*hisilicon perf perf_list_descriptor struct*/
/********************************************************************************
  bit[63:32] | bit[31:10] |  bit[9:6]  | bit5 | bit4 | bit3 | bit2 | bit1 | bit0
   address   |  length    |   reserve  | act2 | act1 |  NA  | int  | end  | valid
----------------------------------------------------------------------------------

valid : valid = 1 indicates this line of descriptor is effective,
	if valid = 0 generates error interrupt.
 end  : end = 1 indicates to end of descriptors, transfer completed
	interrupt is generated when operation of this descriptor is completed.
 int  : int = 1 generates DMA interrupt when operation of this descriptor
	is completed.

---------------------------------------------------------------------------------
  act2 | act1 | sympol |    comment    |               operation
---------------------------------------------------------------------------------
   0   |  0   |  Nop   | No operation  | Do not excute current line and go to next
---------------------------------------------------------------------------------
   0   |  1   |  Rsv   |    Reserve    | Do not excute current line and go to next
---------------------------------------------------------------------------------
   1   |  0   |  Tran  | Transfer Data | Transfer data of one descriptor line
---------------------------------------------------------------------------------
   1   |  1   |  Link  |Link Descriptor| Link to another descriptor
---------------------------------------------------------------------------------

length  : transfer data size of this descriptor line
address : when sympol = Tran, it indicates the start address of transfer data
		when sympol = Link, it indicates the address of the link descriptor
*********************************************************************************/
typedef union {
	struct {
		u64 value0;
		u64 value1;
	} value;

	struct {
		u64 valid:1;
		u64 end:1;
		u64 interrupt:1;
		u64 reserve0:1;
		u64 act:2;
		u64 reserve1:4;
		u64 length:22;
		u64 reserve2:32;
		u64 address;
	} bit_config;
} perf_list_descriptor;

#endif /* hisi_perf_stat.h */
