
#ifndef    _EDMA_CORE_H_
#define    _EDMA_CORE_H_
#include <osl_list.h>
#include <osl_spinlock.h>
#include <bsp_om.h>
#include <bsp_rsracc.h>
#include <bsp_edma.h>

#ifdef ERROR
#undef ERROR
#undef OK
#define ERROR (-1)
#define OK 0
#endif

#define edma_error(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EDMA, "[edma]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))
#define edma_debug(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_EDMA, "[edma]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))

extern u32 edma_irq_trace_enable;
#define edma_irq_debug(fmt, ...) do{ \
    if(edma_irq_trace_enable)\
        (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EDMA, "[edma]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__)); \
}while(0)

/*外设请求，根据edma 芯片而来*/
enum edma_peri_cfg
{
    edma_peri_enum_start = 0,
    edma_peri_spi0_rx = 0,
    edma_peri_spi0_tx,
    edma_peri_spi1_rx,
    edma_peri_spi1_tx,
    edma_peri_ltesio_rx,
    edma_peri_ltesio_tx,
    edma_peri_reserve_0,
    edma_peri_reserve_1,
    edma_peri_hsuart_rx = 8,
    edma_peri_hsuart_tx,
    edma_peri_uart0_rx,
    edma_peri_uart0_tx,
    edma_peri_uart1_rx,
    edma_peri_uart1_tx,
    edma_peri_uart2_rx,
    edma_peri_uart2_tx,
    edma_peri_sci0_rx = 0x10,
    edma_peri_sci_rx  = 0x10,
    edma_peri_sci0_tx,
    edma_peri_sci1_rx,
    edma_peri_sci1_tx,
    edma_peri_gbbp0_dbg = 0x14,
    edma_peri_bbp_dbg   = 0x14,
    edma_peri_gbbp1_grif = 0x15,
    edma_peri_bbp_grif   = 0x15,
    edma_peri_amon_soc = 0x16,
    edma_peri_amon_cpufast = 0x17,
    edma_peri_i2c0_rx,              /*711新增v7r2没有*/
    edma_peri_i2c0_tx,              /*711新增v7r2没有*/
    edma_peri_i2c1_rx,              /*711新增v7r2没有*/
    edma_peri_i2c1_tx,              /*711新增v7r2没有*/
    edma_peri_emi_trans,            /*711新增v7r2没有,edma_ch16上支持,edma_ch4不支持*/
    edma_peri_req_max,
};

struct edma_chan_request_map {
    u32 request_id;
    u32 peripheral;
    u32 channel_id;
};

struct edma_dpm_global_reg
{
    u32 int_tc1_mask;   /* 0x18+0x40*in */
    u32 int_tc2_mask;   /* 0x1C+0x40*in */
    u32 int_err1_mask;  /* 0x20+0x40*in */
    u32 int_err2_mask;  /* 0x24+0x40*in */
    u32 int_err3_mask;  /* 0x28+0x40*in */
    u32 ch_pri;         /* 0x688 */
    u32 dma_ctrl;       /* 0x698 */
};

struct edma_dpm_global
{
    u32 number;
    u32 mask;   /* bits: channels need suspend */
    struct edma_dpm_global_reg regs;
};

struct edma_request_maps_info
{
    struct edma_chan_request_map *maps;
    u32 number_of_maps;
};

struct edma_device
{
    struct list_head list;
    u32 edma_id;
    u32 edma_type;
    u32 base_addr;
    u32 irq_no;
    u32 irq_index;
    u32 chan_id_start;
    u32 num_of_chans;
    const char * clk_name;
    struct clk *clk;
    struct edma_chan * edma_chans;  /* 对应dma 通道数组的首地址 */
    struct edma_request_maps_info request_map_info;
    struct edma_driver * driver;            /* edma driver  ops  */
    struct edma_dpm_global dpm_global; /* 需要备份恢复的全局寄存器 */
    rsr_acc_description bd_descri; /* rsr_acc方式做低功耗处理 */
};
    
struct edma_chan_cfg
{
    u32 lli;     /*指向下个LLI*/
    u32 bindx;
    u32 cindx;
    u32 cnt1;
    u32 cnt0;   /*块传输或者LLI传输的每个节点数据长度 <= 65535字节*/
    u32 src_addr; /*物理地址*/
    u32 des_addr; /*物理地址*/
    u32 config;
    u32 axi_conf;
};

struct edma_async_tx_descriptor
{
    struct list_head list;
    struct edma_chan_cfg  chan_cfg;
};

struct edma_chan_isr
{
   channel_isr callback;
   u32 chan_arg;
   u32 int_stat;
};

struct edma_chan_debug
{
    u32 start_counts;  /*启动次数*/
    u32 time_start;     /* 启动时间*/
    u32 time_end;      /*  完成时间*/
    u32 err_counts;  /*启动后返回错误次数*/
    u32 err_type;      /* 错误类型 */
};

struct edma_suspend_info
{
    u32 need_suspend;
    struct edma_chan_cfg chan_cfg_bak; /*通道需要备份恢复的寄存器*/
};    

struct edma_chan
{
    struct edma_device * device;
    u32 chan_id;        /* channel id in all edma */
    u32 phy_chan_id;    /* channel id in the edma it belongs to */
    u32 request_id; 
    u32 peri_id; 

    struct edma_async_tx_descriptor desc;   /* 专用通道, 一个描述符 */
    struct list_head *desc_list;            /* 共享通道的描述符队列 */

    struct edma_chan_isr isr;
    struct edma_chan_debug dbg;
    struct edma_suspend_info suspend;
};

struct edma_ctrl
{
    struct list_head device_list;
    struct list_head driver_list;
    spinlock_t lock;

    u32 number_of_devices;
    u32 number_of_chans;
    struct edma_chan * chans;
    struct edma_chan_request_map chan_map_table[EDMA_REQ_MAX];
};

#define ops_adp_mdrv

struct edma_chan_ops
{
    void ( *int_mask_enable )( struct edma_chan *chan, u32 int_flag ); 
    void ( *int_mask_disable )( struct edma_chan *chan );
    void ( *register_isr )(struct edma_chan *chan, struct edma_chan_isr *chan_isr); /* regist & int enable  */
    void ( *unregister_isr )(struct edma_chan *chan); /* unregist & int disable  */
    void ( *irq_handler )(struct edma_chan *chan);

#ifdef ops_adp_mdrv
    void ( *set_peri )( struct edma_chan*chan, u32 peri );
    void ( *set_direction )( struct edma_chan *chan, u32 direction ); 
    void ( *set_src_des_addr )( struct edma_chan *chan, u32 src, u32 des ); 
    void ( *set_burst )( struct edma_chan *chan, u32 burst_width, u32 burst_len ); 
    void ( *set_src_config )( struct edma_chan *chan,  u32 burst_width, u32 burst_len );
    void ( *set_des_config )( struct edma_chan *chan,  u32 burst_width, u32 burst_len );
#endif
    void ( *submit)( struct edma_chan *chan, struct edma_async_tx_descriptor * tx );
    void ( *start )( struct edma_chan *chan );
    void ( *stop )( struct edma_chan *chan );

    u32 ( *get_ch_stat )( struct edma_chan *chan ); 
    u32 ( *get_cur_trans_addr )( struct edma_chan *chan);
    u64 ( *get_cur_cnt )( struct edma_chan *chan ); 
    u32 ( *get_lli_addr )( struct edma_chan *chan );

    s32 ( *suspend )( struct edma_chan *chan ); /*判断edma是否空闲，备份寄存器*/
    void ( *resume )( struct edma_chan *chan ); /*恢复寄存器*/
};

struct edma_global_ops
{
    u32 (*work_state )(struct edma_device *device);
    u32 (*get_int_state )(struct edma_device *device);
    irqreturn_t (*irq_handler )(struct edma_device *device);

    s32 (*suspend)(struct edma_device *device); /*判断edma是否空闲，备份寄存器*/
    void (*resume) (struct edma_device *device); /*恢复寄存器*/
    s32 (*reset_and_wait_idle) (struct edma_device *device); /*单独复位 master 进 idle */
};

struct edma_driver
{
    struct list_head list;
    u32 edma_type;
    const char *driver_name;
    struct edma_global_ops *global_ops;
    struct edma_chan_ops *chan_ops;
};

s32 edma_core_init(void);
int ccpu_reset_edmac_and_wait_idle(void);
int edma_driver_register(struct edma_driver *driver);
int edma_device_register(struct edma_device *device);
int is_request_id_valiad(u32 request_id);
int is_channel_id_valiad(u32 channel_id);
u32 edma_request_chan_id(enum edma_req_id request_id);
/* struct edma_chan * edma_request_chan(enum edma_req_id request_id); */
u32 edma_request_to_peri(enum edma_req_id request_id);
void edma_clear_chan_cfg(struct edma_chan * chan);
struct edma_chan * chan_id_to_chan(u32 channel_id);

#endif

