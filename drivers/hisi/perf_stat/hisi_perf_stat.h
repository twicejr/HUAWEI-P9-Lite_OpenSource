/* hisi_perf_stat.h */

#ifndef HISI_PERF_STAT_H
#define HISI_PERF_STAT_H

#define PERF_IS_ALIGNED(x,b)	(((x) % (b)) == 0)
#define Count_xINy_Num(x,y) ((y) % (x) ? (((y) / (x)) + 1) : ((y)/(x)))

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
#define PERF_SEQADDR        0x1C
#define PERF_SEQLEN         0x20
#define PERF_LISTADDR       0x24
#define PERF_CURLIST        0x28

#define PERF_RSTCNT         0x2C

#define PERF_INTEN          0x30
#define PERF_INTCLR         0x34
#define PERF_INTRAWSTAT     0x38
#define PERF_INTMASKSTAT    0x3C

#define PERF_CURSAMPCNT     0x40
#define PERF_CURSAMPADDR    0x44
#define PERF_OVERTIMECNT    0x48
#define PERF_DBGFIFOFULL    0x4C
#define PERF_DBGBLOCK       0x50
#define PERF_MONITORRST     0x54

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
#define PERF_PORT_NUM      (16)
#define PERF_PORT_ALL      (0xFFFF)
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

#define PERF_INIT_DONE		1
#define PERF_ADD_DONE		2
#define PERF_DEL_DONE		3
#define PERF_TASK_DONE		0

#define PERF_LIST_CFG_NORMAL  0x21ULL
#define PERF_LIST_CFG_INT     0x25ULL
#define PERF_LIST_CFG_LINK    0x31ULL

#define PERF_SAMPLE_HIGHSPEED     1
#define PERF_SAMPLE_HSCYCLE     2
#define PERF_MALLOC_PAGES_100M    25600
#define PERF_SIZE_1M (1024*1024)
#define PERF_TIME_1US (1000000)
#define PERF_TIME_1MS (1000)
#define PERF_HIGHSPEED_DATA_PATH  "/data/perf_data_hs.data"
#define PERF_MILLION (1000000)

#define ALIGNED_NUM 8
#define RST_ADDR 0x1 
#define PERF_CLOCK_RATE (60000000)

#define SAMPLE_PERIOD_MASK (0xffffffff)
#define SAMPLE_TIME_MASK (0xffff)

/*hisilicon perf sample_data_head struct*/
typedef struct
{
    u64 sample_cnt_current;
    u64 sample_period;
    u64 sample_cnt_legacy;
    u64 sample_port;
}perf_sample_data_head;

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
	u64 value;

	struct {
		u64 valid:1;
		u64 end:1;
		u64 interrupt:1;
		u64 reserve0:1;
		u64 act:2;
		u64 reserve1:4;
		u64 length:22;
		u64 address:32;
	} bit_config;

} perf_list_descriptor;


struct perfstat_dev_info
{
    struct resource   *res;
    struct clk *sample_clk;
    struct regulator *perf_supply;
    struct regulator *master_supply[PERF_PORT_NUM];

    struct wake_lock wakelock;
    spinlock_t synclock;            /*sync perf_interrupt and perf_del*/

    int  status;                    /*perf_status flag, when it is set rest, interrupt returns directly*/
    int  irq;
    unsigned long sample_clk_rate;


/* hisilicon perf attibute get from dts
 event_id    : hisilicon perf event_id, when a evnet is initialized,
               we deal with the perf_event only if the evend_id matches ours.
 per_data_sz : hisilicon perf per data size,
               perf_add use it to count the per_size,
               per_size = sample_numer * per_data_sz + data_head_size.*/
    int  event_id;
    int  per_data_sz;
    int  per_sample_size;
    int  sprt;
    int  vldmsk_of_sprt;
    int  samp_type;    /*HIGHSPEED : 1, NORMALSPEED : 0*/
    struct delayed_work hs_record_data_work; /*Record Data work in HighSpeed Mode*/

/*We report the sample data in each (list-done)interrupt,
  of course we should know the data start address & size.
  The fisrt start address of data is virt_addr, once a interrupt
  comes, we report PAGE_SIZE*pages_u data, then the cur_page_n += pages_u,
  so we could know the next data start address according to the cur_page_n,
  however, when cur_page_n beyonds the total page numbers(pages_n),
  it becomes zero again.
  */
    int  cur_page_n;
    int  pages_n;
    void *virt_addr;

/*perf generates interrupt by analyzing the perf_list_descriptors,
  we config a serial of descriptors in a continuous address, and
  tell perf the first descriptor's address*/
    perf_list_descriptor *list;
    struct page **pages;
};


#endif /* hisi_perf_stat.h */
