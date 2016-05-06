
#include <osl_spinlock.h>
#include <bsp_clk.h>
#include <bsp_reset.h>
#include <bsp_rsracc.h>
#include "edma_core.h"
#include "edma_driver.h"

spinlock_t edma_driver_lock;

static void edma_execute_chan_isr(struct edma_chan_isr *chan_isr , u32 int_flag)
{
    if(chan_isr->callback != NULL){
        edma_irq_debug("chan_isr executed, int_flag=%d \n", int_flag);
        (chan_isr->callback)(chan_isr->chan_arg, int_flag);
    }else{
        edma_irq_debug("callback = NULL, int_flag=%d \n", int_flag);
    }
}

/* clean irq & run chan's callback */
static void edma_chan_irq_handler(struct edma_chan *chan)
{
    u32 irq_idx;
    u32 reg_base = 0;
    u32 int_tc1    = 0;
    u32 int_tc2    = 0;
    u32 int_err1   = 0;
    u32 int_err2   = 0;
    u32 int_err3   = 0;
    u32 chan_bit = 0;

    irq_idx  = chan->device->irq_index;
    reg_base = chan->device->base_addr;
    chan_bit = (u32)0x1<<chan->phy_chan_id;

    int_tc1  = readl(reg_base + EDMA_INT_TC1(irq_idx));
    int_tc2  = readl(reg_base + EDMA_INT_TC2(irq_idx));
    int_err1 = readl(reg_base + EDMA_INT_ERR1(irq_idx));
    int_err2 = readl(reg_base + EDMA_INT_ERR2(irq_idx));
    int_err3 = readl(reg_base + EDMA_INT_ERR3(irq_idx));
    /* Clear  Interrupt:TC / LLI_TC/ Config Error/Trans Error/LLI read Error */
    if (int_tc1 & chan_bit){
        writel_relaxed(chan_bit, reg_base + EDMA_INT_TC1_RAW);
        edma_execute_chan_isr(&(chan->isr), EDMA_INT_DONE);
    }else{}
    if (int_tc2 & chan_bit){
        writel_relaxed(chan_bit, reg_base + EDMA_INT_TC2_RAW);
        edma_execute_chan_isr(&(chan->isr), EDMA_INT_LLT_DONE);
    }else{}
    if (int_err1 & chan_bit){
        writel_relaxed(chan_bit, reg_base + EDMA_INT_ERR1_RAW);
        edma_execute_chan_isr(&(chan->isr), EDMA_INT_CONFIG_ERR);
    }else{}
    if (int_err2 & chan_bit){
        writel_relaxed(chan_bit, reg_base + EDMA_INT_ERR2_RAW);
        edma_execute_chan_isr(&(chan->isr), EDMA_INT_TRANSFER_ERR);
    }else{}
    if (int_err3 & chan_bit){
        writel_relaxed(chan_bit, reg_base + EDMA_INT_ERR3_RAW);
        edma_execute_chan_isr(&(chan->isr), EDMA_INT_READ_ERR);
    }else{}
}

irqreturn_t edma_irq_handler(struct edma_device *device)
{
    u32 int_stat = 0;
    u32 phy_chan_id;
    u32 chan_bit = 0;
    struct edma_chan *chan;

    int_stat = readl(device->base_addr + EDMA_INT_STAT(device->irq_index));

    edma_debug(" EDMA_INT_STAT = 0x%X \n", int_stat);
    /* decide which channel has trigger the interrupt*/
    for (phy_chan_id = 0; phy_chan_id < device->num_of_chans; phy_chan_id++){
        chan_bit = 1UL << phy_chan_id;
        if (int_stat & chan_bit){
            chan = device->edma_chans + phy_chan_id;
            edma_irq_debug(" intterupt from channel %d \n", phy_chan_id);
            device->driver->chan_ops->irq_handler(chan);
        }
    }
    return IRQ_HANDLED;
}
/* int enable disable   according to int flag  */
void edma_chan_int_enable(struct edma_chan *chan, u32 int_flag)
{
    u32 irq_idx;
    u32 reg_base = 0;
    u32 chan_int_mask = 0;
    u32 reg = 0;
    unsigned long  flags = 0;

    irq_idx = chan->device->irq_index;
    reg_base = chan->device->base_addr;
    chan_int_mask = (u32)0x1<<chan->phy_chan_id;

    spin_lock_irqsave(&edma_driver_lock, flags);
    /* Clear interrupt :write 1 clear; write 0 no change */
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_TC1_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_TC2_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_ERR1_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_ERR2_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_ERR3_RAW);
    /* Enable interrupt: 0-mask, 1-do not mask */
    /*DONOT need multicore mutual exclusion*/
    if (int_flag & EDMA_INT_DONE){
        reg = reg_base + EDMA_INT_TC1_MASK(irq_idx);
        writel_relaxed( readl(reg) | chan_int_mask, reg);
    }
    if (int_flag & EDMA_INT_LLT_DONE){
        reg = reg_base + EDMA_INT_TC2_MASK(irq_idx);
        writel_relaxed( readl(reg) | chan_int_mask, reg);
    }
    if (int_flag & EDMA_INT_CONFIG_ERR){
        reg = reg_base + EDMA_INT_ERR1_MASK(irq_idx);
        writel_relaxed( readl(reg) | chan_int_mask, reg);
    }
    if (int_flag & EDMA_INT_TRANSFER_ERR){
        reg = reg_base + EDMA_INT_ERR2_MASK(irq_idx);
        writel_relaxed( readl(reg) | chan_int_mask, reg);
    }
    if (int_flag & EDMA_INT_READ_ERR){
        reg = reg_base + EDMA_INT_ERR3_MASK(irq_idx);
        writel_relaxed( readl(reg) | chan_int_mask, reg);
    }
    spin_unlock_irqrestore(&edma_driver_lock, flags);
}


void edma_chan_int_disable( struct edma_chan *chan )
{
    u32 irq_idx;
    u32 reg_base = 0;
    u32 chan_int_mask = 0;
    u32 reg = 0;
    unsigned long flags = 0;

    irq_idx = chan->device->irq_index;
    reg_base = chan->device->base_addr;
    chan_int_mask = (u32)0x1<<chan->phy_chan_id;

    spin_lock_irqsave(&edma_driver_lock, flags);
    /* Enable interrupt: 0-mask, 1-do not mask */
    /*DONOT need multicore mutual exclusion*/
    reg = reg_base + EDMA_INT_TC1_MASK(irq_idx);
    writel_relaxed( readl(reg) & (~chan_int_mask), reg);
    reg = reg_base + EDMA_INT_TC2_MASK(irq_idx);
    writel_relaxed( readl(reg) & (~chan_int_mask), reg);
    reg = reg_base + EDMA_INT_ERR1_MASK(irq_idx);
    writel_relaxed( readl(reg) & (~chan_int_mask), reg);
    reg = reg_base + EDMA_INT_ERR2_MASK(irq_idx);
    writel_relaxed( readl(reg) & (~chan_int_mask), reg);
    reg = reg_base + EDMA_INT_ERR3_MASK(irq_idx);
    writel_relaxed( readl(reg) & (~chan_int_mask), reg);
    /* Clear interrupt :write 1 clear; write 0 no change */
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_TC1_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_TC2_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_ERR1_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_ERR2_RAW);
    writel_relaxed(chan_int_mask, reg_base + EDMA_INT_ERR3_RAW);
    spin_unlock_irqrestore(&edma_driver_lock, flags);
}




void edma_chan_register_isr(struct edma_chan *chan, struct edma_chan_isr *chan_isr)
{
    if((NULL==chan_isr->callback)||(0==chan_isr->int_stat)){
        edma_debug("callback=0x%x, int_flag=0x%x \n",chan_isr->callback,chan_isr->int_stat);
        return;
    }else{
        chan->isr.callback = chan_isr->callback;
        chan->isr.chan_arg = chan_isr->chan_arg;
        chan->isr.int_stat = chan_isr->int_stat;
    }
    edma_chan_int_enable( chan, chan_isr->int_stat );
}


void edma_chan_unregister_isr( struct edma_chan *chan )
{
    edma_chan_int_disable( chan );
    /* chans is unshared, do not need protect */
    chan->isr.callback = NULL;
    chan->isr.chan_arg = 0;
    chan->isr.int_stat = 0;
}
/* return (low 16bit): 1-busy, 0-idle*/
u32 edma_get_ch_state( struct edma_device *device ) 
{
    return readl(device->base_addr + EDMA_CH_STAT);
}
/* return (low 16bit): 1-busy, 0-idle*/
u32 edma_get_int_state( struct edma_device *device ) 
{
    return readl(device->base_addr + EDMA_INT_STAT(device->irq_index));
}
/* return src_addr, des_addr */
u32 edma_chan_get_cur_addr ( struct edma_chan *chan )
{
    u32 get_addr_type = 0;
    u32 ret = 0;
    u32 base_addr = 0;
    u32 cn = 0xffffffff;

    base_addr = chan->device->base_addr;
    cn = chan->phy_chan_id;
    get_addr_type = EDMAC_TRANSFER_CONFIG_BOTH_INC\
                    & readl( base_addr + CHAN_CX_CONFIG(cn) );
    switch (get_addr_type)
    {
        case (EDMAC_TRANSFER_CONFIG_DEST_INC|EDMAC_TRANSFER_CONFIG_SOUR_INC):
        case EDMAC_TRANSFER_CONFIG_SOUR_INC:
            ret = readl( base_addr + CHAN_CX_CURR_SRC_ADDR(cn) );
            break;
        case EDMAC_TRANSFER_CONFIG_DEST_INC:
            ret = readl( base_addr + CHAN_CX_CURR_DES_ADDR(cn) );
            break;
        default:
            break;
    }
    return ret;
}

u64 edma_chan_get_cur_cnt( struct edma_chan *chan )
{
    u64 sz = 0;
    u32 chan_cnt0, chan_cnt1;
    u32 a_count,b_count,c_count;
    u32 chan_curr_cnt0, chan_curr_cnt1;
    u32 curr_a_count, curr_b_count, curr_c_count;
    u32 base_addr = 0;
    u32 cn = 0xffffffff;

    base_addr = chan->device->base_addr;
    cn = chan->phy_chan_id;
    /* read the config cnt */
    chan_cnt0 = readl(base_addr+CHAN_CX_CNT0(cn));
    chan_cnt1 = readl(base_addr+CHAN_CX_CNT1(cn));
    a_count = (chan_cnt0&0xFFFF);
    b_count = (chan_cnt0&0xFFFF0000)>>16;
    c_count = (chan_cnt1&0xFFFF);
    edma_debug("a_count:0x%x, b_count:0x%x, c_count:0x%x \n", a_count, b_count, c_count);
    /* read curr cnt */
    chan_curr_cnt0 = readl(base_addr+CHAN_CX_CURR_CNT0(cn));
    chan_curr_cnt1 = readl(base_addr+CHAN_CX_CURR_CNT1(cn));
    curr_a_count = (chan_curr_cnt0&0xFFFF);
    curr_b_count = (chan_curr_cnt0&0xFFFF0000)>>16;
    curr_c_count = (chan_curr_cnt1&0xFFFF);
    edma_debug( "curr_a_count:0x%x, curr_b_count:0x%x, curr_c_count:0x%x \n",\
                   curr_a_count, curr_b_count, curr_c_count);
    sz = (u64)(curr_a_count)
          +((u64)a_count*curr_b_count)
          +((u64)a_count*(u64)b_count*curr_c_count);
    edma_debug(" ------------ size:0x%llx, \n",sz);
    return sz;
}

u32 edma_chan_get_lli_addr ( struct edma_chan *chan )
{
    return (u32)&chan->desc.chan_cfg.lli;
}
static inline void edma_chan_set_cfg( u32 chan_cfg_addr, struct edma_chan_cfg * cfg)
{
    writel_relaxed( cfg->lli     , chan_cfg_addr + _LLI     );
    writel_relaxed( cfg->bindx   , chan_cfg_addr + _BINDX   );
    writel_relaxed( cfg->cindx   , chan_cfg_addr + _CINDX   );
    writel_relaxed( cfg->cnt1    , chan_cfg_addr + _CNT1    );
    writel_relaxed( cfg->cnt0    , chan_cfg_addr + _CNT0    );
    writel_relaxed( cfg->src_addr, chan_cfg_addr + _SRC_ADDR);
    writel_relaxed( cfg->des_addr, chan_cfg_addr + _DES_ADDR);
    writel_relaxed( cfg->config  , chan_cfg_addr + _CONFIG  );
    writel_relaxed( cfg->axi_conf, chan_cfg_addr + _AXI_CONF);
}

#ifdef ops_adp_mdrv
#define CONFIG_FLOW_CTRL_MASK   0xC
#define CONFIG_DI_SI_MASK   0xC0000000

#define CONFIG_SRC_BURST_MASK   0xF070000
#define CONFIG_DES_BURST_MASK   0x0F07000
#define CONFIG_BURST_MASK   0xFF77000

#define CONFIG_PERI_MASK   0x1F0

void edma_chan_set_peri(struct edma_chan*chan, enum edma_peri_cfg peri)
{
    chan->desc.chan_cfg.config &= ~CONFIG_PERI_MASK;
    chan->desc.chan_cfg.config |= peri<<4;
}

void edma_chan_set_direction( struct edma_chan *chan, u32 direction )
{
    u32 chan_cfg = 0;

    switch (direction){
        case EDMA_P2M:
            chan_cfg |= P2M_CONFIG;
            break;
        case EDMA_M2P:
            chan_cfg |= M2P_CONFIG;
            break;
        case EDMA_M2M:
            chan_cfg |= M2M_CONFIG;
            break;
        default:
            edma_error("chan=%d config direction=%d, ERROR \n", chan->chan_id, direction);
            break;
    }
    chan->desc.chan_cfg.config &= (~(CONFIG_FLOW_CTRL_MASK|CONFIG_DI_SI_MASK));
    chan->desc.chan_cfg.config |= chan_cfg;
}
void edma_chan_set_src_des_addr( struct edma_chan *chan, u32 src, u32 des )
{
    chan->desc.chan_cfg.src_addr = src;
    chan->desc.chan_cfg.des_addr = des;
}
void edma_chan_set_burst( struct edma_chan *chan, u32 burst_width, u32 burst_len )
{
    chan->desc.chan_cfg.config &= (~CONFIG_BURST_MASK);
    chan->desc.chan_cfg.config |= EDMAC_BASIC_CONFIG(burst_width, burst_len);
} 

void edma_chan_set_src_config( struct edma_chan *chan,  u32 burst_width, u32 burst_len )
{
    chan->desc.chan_cfg.config &= (~CONFIG_SRC_BURST_MASK);
    chan->desc.chan_cfg.config |= EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH(burst_len);
    chan->desc.chan_cfg.config |= EDMAC_TRANSFER_CONFIG_SOUR_WIDTH(burst_width);
}
void edma_chan_set_des_config( struct edma_chan *chan,  u32 burst_width, u32 burst_len )
{{
    chan->desc.chan_cfg.config &= (~CONFIG_DES_BURST_MASK);
    chan->desc.chan_cfg.config |= EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH(burst_len);
    chan->desc.chan_cfg.config |= EDMAC_TRANSFER_CONFIG_DEST_WIDTH(burst_width);
}
}
#endif

void edma_submit( struct edma_chan *chan, struct edma_async_tx_descriptor * tx )
{
    u32 edma_chan_cfg_addr = 0;
    edma_chan_cfg_addr = chan->device->base_addr + CHAN_CFG_BASE(chan->phy_chan_id);
    edma_chan_set_cfg( edma_chan_cfg_addr, &tx->chan_cfg );
}

void edma_chan_start( struct edma_chan *chan )
{
    u32 chan_config_addr = 0;
    u32 ret = 0;
    chan_config_addr = chan->device->base_addr + CHAN_CX_CONFIG(chan->phy_chan_id);
    ret = readl(chan_config_addr);
    writel(ret&(~0x1), chan_config_addr);  
    writel(ret|0x1, chan_config_addr);    
}

void edma_chan_stop( struct edma_chan *chan )
{
    u32 chan_config_addr = 0;
    u32 ret = 0;
    chan_config_addr = chan->device->base_addr + CHAN_CX_CONFIG(chan->phy_chan_id);
    ret = readl(chan_config_addr);
    writel(ret&(~0x1), chan_config_addr);  
}
/* return 1-busy, 0-idle*/
u32 edma_chan_get_state( struct edma_chan *chan ) 
{
    u32 chan_config_addr = 0;
    u32 ret = 0;
    chan_config_addr = chan->device->base_addr + CHAN_CX_CONFIG(chan->phy_chan_id);
    ret = readl(chan_config_addr);
    return ret&0x1; 
}
/* store chans' regs */
s32 edma_chan_suspend(struct edma_chan *chan)
{
    u32 base_addr = 0;
    u32 cn = 0;
    
    base_addr = chan->device->base_addr;
    cn = chan->phy_chan_id;

    chan->suspend.chan_cfg_bak.lli      = readl( base_addr + CHAN_CX_LLI(cn)     );
    chan->suspend.chan_cfg_bak.bindx    = readl( base_addr + CHAN_CX_BINDX(cn)   );
    chan->suspend.chan_cfg_bak.cindx    = readl( base_addr + CHAN_CX_CINDX(cn)   );
    chan->suspend.chan_cfg_bak.cnt1     = readl( base_addr + CHAN_CX_CNT1(cn)    );
    chan->suspend.chan_cfg_bak.cnt0     = readl( base_addr + CHAN_CX_CNT0(cn)    );
    chan->suspend.chan_cfg_bak.src_addr = readl( base_addr + CHAN_CX_SRC_ADDR(cn));
    chan->suspend.chan_cfg_bak.des_addr = readl( base_addr + CHAN_CX_DES_ADDR(cn));
    chan->suspend.chan_cfg_bak.config   = readl( base_addr + CHAN_CX_CONFIG(cn)  );
    chan->suspend.chan_cfg_bak.axi_conf = readl( base_addr + CHAN_CX_AXI_CONF(cn));

    chan->suspend.need_suspend++;

    return OK;
}
/* restore chans' regs */
void edma_chan_resume(struct edma_chan *chan)
{
    u32 base_addr = 0;
    u32 cn = 0;
    base_addr = chan->device->base_addr;
    cn = chan->phy_chan_id;

    writel_relaxed( chan->suspend.chan_cfg_bak.lli     , base_addr + CHAN_CX_LLI(cn)     );
    writel_relaxed( chan->suspend.chan_cfg_bak.bindx   , base_addr + CHAN_CX_BINDX(cn)   );
    writel_relaxed( chan->suspend.chan_cfg_bak.cindx   , base_addr + CHAN_CX_CINDX(cn)   );
    writel_relaxed( chan->suspend.chan_cfg_bak.cnt1    , base_addr + CHAN_CX_CNT1(cn)    );
    writel_relaxed( chan->suspend.chan_cfg_bak.cnt0    , base_addr + CHAN_CX_CNT0(cn)    );
    writel_relaxed( chan->suspend.chan_cfg_bak.src_addr, base_addr + CHAN_CX_SRC_ADDR(cn));
    writel_relaxed( chan->suspend.chan_cfg_bak.des_addr, base_addr + CHAN_CX_DES_ADDR(cn));
    writel_relaxed( chan->suspend.chan_cfg_bak.config  , base_addr + CHAN_CX_CONFIG(cn)  );
    writel_relaxed( chan->suspend.chan_cfg_bak.axi_conf, base_addr + CHAN_CX_AXI_CONF(cn));
    
    chan->suspend.need_suspend++;

}
/* sotre regs if edma is idle, or return fail */
int edma_suspend(struct edma_device *device)
{
    u32 base_addr = 0;
    u32 in= 0;
    u32 chan_id = 0;
    struct edma_chan *chans = NULL;
    u32 chan_mask = 0;

    if(edma_get_ch_state(device))
        return ERROR;

    base_addr = device->base_addr;
    in = device->irq_index;
    chan_mask = device->dpm_global.mask;

    device->dpm_global.regs.int_tc1_mask  = readl( base_addr + EDMA_INT_TC1_MASK(in)  ) & chan_mask;
    device->dpm_global.regs.int_tc2_mask  = readl( base_addr + EDMA_INT_TC2_MASK(in)  ) & chan_mask;
    device->dpm_global.regs.int_err1_mask = readl( base_addr + EDMA_INT_ERR1_MASK(in) ) & chan_mask;
    device->dpm_global.regs.int_err2_mask = readl( base_addr + EDMA_INT_ERR2_MASK(in) ) & chan_mask;
    device->dpm_global.regs.int_err3_mask = readl( base_addr + EDMA_INT_ERR3_MASK(in) ) & chan_mask;
    device->dpm_global.regs.ch_pri        = readl( base_addr + EDMA_CH_PRI            );
    device->dpm_global.regs.dma_ctrl      = readl( base_addr + EDMA_DMA_CTRL          );

    chans = device->edma_chans;
    for(chan_id = 0; chan_id<device->num_of_chans; chan_id++){
        if(device->dpm_global.mask & (0x1UL<<chan_id))
            (void)edma_chan_suspend(&chans[chan_id]);
    }
    clk_disable(device->clk);
    return OK;
}
/* restore edma regs */
void edma_resume(struct edma_device *device)
{
    u32 base_addr = 0;
    u32 in= 0;
    u32 chan_id = 0;
    struct edma_chan *chans = NULL;

    (void)clk_enable(device->clk);
    
    base_addr = device->base_addr;
    in = device->irq_index;

    writel_relaxed( device->dpm_global.regs.int_tc1_mask , base_addr + EDMA_INT_TC1_MASK(in)  );
    writel_relaxed( device->dpm_global.regs.int_tc2_mask , base_addr + EDMA_INT_TC2_MASK(in)  );
    writel_relaxed( device->dpm_global.regs.int_err1_mask, base_addr + EDMA_INT_ERR1_MASK(in) );
    writel_relaxed( device->dpm_global.regs.int_err2_mask, base_addr + EDMA_INT_ERR2_MASK(in) );
    writel_relaxed( device->dpm_global.regs.int_err3_mask, base_addr + EDMA_INT_ERR3_MASK(in) );
    writel_relaxed( device->dpm_global.regs.ch_pri       , base_addr + EDMA_CH_PRI   );
    writel_relaxed( device->dpm_global.regs.dma_ctrl     , base_addr + EDMA_DMA_CTRL );

    chans = device->edma_chans;
    for(chan_id = 0; chan_id<device->num_of_chans; chan_id++){
        if(device->dpm_global.mask & (0x1UL<<chan_id))
            (void)edma_chan_resume(&chans[chan_id]);
    }
}

int edma_rsracc_suspend_begin(rsr_acc_description *bd_descri)
{
    u32 base_addr = 0;
    u32 in= 0;
    u32 chan_mask = 0;
    struct edma_device *device = NULL;

    device = container_of(bd_descri, struct edma_device, bd_descri);

    if(edma_get_ch_state(device))
        return ERROR;

    base_addr = device->base_addr;
    in = device->irq_index;
    chan_mask = device->dpm_global.mask;

    device->dpm_global.regs.int_tc1_mask  = readl( base_addr + EDMA_INT_TC1_MASK(in)  ) & chan_mask;
    device->dpm_global.regs.int_tc2_mask  = readl( base_addr + EDMA_INT_TC2_MASK(in)  ) & chan_mask;
    device->dpm_global.regs.int_err1_mask = readl( base_addr + EDMA_INT_ERR1_MASK(in) ) & chan_mask;
    device->dpm_global.regs.int_err2_mask = readl( base_addr + EDMA_INT_ERR2_MASK(in) ) & chan_mask;
    device->dpm_global.regs.int_err3_mask = readl( base_addr + EDMA_INT_ERR3_MASK(in) ) & chan_mask;
    device->dpm_global.regs.ch_pri        = readl( base_addr + EDMA_CH_PRI            );
    device->dpm_global.regs.dma_ctrl      = readl( base_addr + EDMA_DMA_CTRL          );

    return OK;
}
void edma_rsracc_suspend_end(rsr_acc_description *bd_descri)
{
    struct edma_device *device = NULL;

    device = container_of(bd_descri, struct edma_device, bd_descri);
    clk_disable(device->clk);
    return;
}


void edma_rsracc_resume_begin(rsr_acc_description *bd_descri)
{
    u32 base_addr = 0;
    u32 in= 0;
    struct edma_device *device = NULL;

    device = container_of(bd_descri, struct edma_device, bd_descri);

    (void)clk_enable(device->clk);
    
    base_addr = device->base_addr;
    in = device->irq_index;

    writel_relaxed( device->dpm_global.regs.int_tc1_mask , base_addr + EDMA_INT_TC1_MASK(in)  );
    writel_relaxed( device->dpm_global.regs.int_tc2_mask , base_addr + EDMA_INT_TC2_MASK(in)  );
    writel_relaxed( device->dpm_global.regs.int_err1_mask, base_addr + EDMA_INT_ERR1_MASK(in) );
    writel_relaxed( device->dpm_global.regs.int_err2_mask, base_addr + EDMA_INT_ERR2_MASK(in) );
    writel_relaxed( device->dpm_global.regs.int_err3_mask, base_addr + EDMA_INT_ERR3_MASK(in) );
    writel_relaxed( device->dpm_global.regs.ch_pri       , base_addr + EDMA_CH_PRI   );
    writel_relaxed( device->dpm_global.regs.dma_ctrl     , base_addr + EDMA_DMA_CTRL );

}

struct rsracc_cb_s edma_rsracc_cb ={
    .suspend_begin  = edma_rsracc_suspend_begin,
    .suspend_end    = edma_rsracc_suspend_end,
    .resume_begin   = edma_rsracc_resume_begin,
    .resume_end     = NULL,
};

s32 edma_rsracc_dpm_init(struct edma_device *device)
{
    s32 ret;
    rsr_acc_description *edma_rsracc_bd;
    edma_rsracc_bd = &device->bd_descri;

    edma_rsracc_bd->level               = rsracc_bd_level_9;
    edma_rsracc_bd->name                = device->clk_name;
    edma_rsracc_bd->ops                 = &edma_rsracc_cb;
    edma_rsracc_bd->only_ops_in_bd      = 0;
    edma_rsracc_bd->reg_addr            = (u32*)(device->base_addr + CHAN_CFG_BASE(0));
    edma_rsracc_bd->reg_num             = 0x40/4* device->num_of_chans;
    edma_rsracc_bd->bak_addr            = NULL;//osl_cachedma_malloc(0x40*16);
    edma_rsracc_bd->need_rsracc_assign_bakaddr = 1;
    edma_rsracc_bd->bd_valid_flow       = both_save_and_resume_flow;
    edma_rsracc_bd->is_negation_resume  =0;
    edma_rsracc_bd->negation_resume_bitmask=0;
    edma_rsracc_bd->is_wait_bd          = 0;
    edma_rsracc_bd->wait_cycle          = 0;

    ret = bsp_rsracc_register(edma_rsracc_bd, 1);
    return ret;
}

int edma_reset_and_wait_idle(struct edma_device *device)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;
    u32 base_addr = 0;

    base_addr = device->base_addr;
    (void)clk_enable(device->clk);

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_EDMA_STOP_BUS);

    /* 请求停止总线访问,相当于halt en */
    regvalue = readl( base_addr + 0x698);
    regvalue |= (unsigned int)0x2;
    writel(regvalue, base_addr + 0x698);

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_EDMA_ENTER_IDLE);

    /*查询是否停止EDMA总线访问，查是否进halt状态 */
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = readl(base_addr + 0x698);
        regvalue &= (unsigned int)0x1;
    }while((0x1 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x1 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_EDMAC)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return BSP_ERROR;
    }
    return BSP_OK;
}


struct edma_global_ops edma_global_ops = {
    .work_state     = edma_get_ch_state,
    .get_int_state  = edma_get_int_state,
    .irq_handler    = edma_irq_handler,
    .suspend        = edma_suspend,
    .resume         = edma_resume,
    .reset_and_wait_idle = edma_reset_and_wait_idle,
};

struct edma_chan_ops edma_chan_ops = {
    .int_mask_enable    = edma_chan_int_enable,
    .int_mask_disable   = edma_chan_int_disable,
    .register_isr       = edma_chan_register_isr,
    .unregister_isr     = edma_chan_unregister_isr,
    .irq_handler        = edma_chan_irq_handler,
#ifdef ops_adp_mdrv
    .set_peri           = edma_chan_set_peri,
    .set_direction      = edma_chan_set_direction,
    .set_src_des_addr   = edma_chan_set_src_des_addr,
    .set_burst          = edma_chan_set_burst,
    .set_src_config     = edma_chan_set_src_config,
    .set_des_config     = edma_chan_set_des_config,
#endif
    .submit             = edma_submit,
    .start              = edma_chan_start,
    .stop               = edma_chan_stop,
    .get_ch_stat        = edma_chan_get_state,
    .get_cur_trans_addr = edma_chan_get_cur_addr,
    .get_cur_cnt        = edma_chan_get_cur_cnt,
    .get_lli_addr       = edma_chan_get_lli_addr,
    .suspend            = edma_chan_suspend,
    .resume             = edma_chan_resume,
};

struct edma_driver balong_edma_driver = {
    .edma_type   = 300,
    .driver_name = "balong_edma",
    .global_ops  = &edma_global_ops,
    .chan_ops    = &edma_chan_ops,

};

int edma_driver_init(void)
{
    spin_lock_init(&edma_driver_lock);
    return edma_driver_register( &balong_edma_driver );
}

