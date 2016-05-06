/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  cipher_balong.c
*
*   作    者 :  w00228729
*
*   描    述 :  cipher功能实现
*
*   修改记录 :  2013年03月12日  v1.00  w00228729 创建
*************************************************************************/
#include <of.h>
#include <osl_common.h>
#include <osl_cache.h>
#include <osl_malloc.h>
#include <osl_irq.h>
#include <osl_thread.h>
#include <hi_cipher.h>
#include <mdrv_public.h>
#include "securec.h"
#include <bsp_hardtimer.h>
#include <bsp_psam.h>
#include <bsp_dpm.h>
#include <bsp_rsracc.h>
#include <bsp_dump.h>
#include <bsp_memmap.h>
#include <bsp_reset.h>
#include "cipher_balong.h"
#include "kdf_balong.h"

//#define CIPHER_CACHE_ENABLE
#define CIPHER_ERR_PRINT(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "[CIPHER]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define CIPHER_INFO(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER,fmt, ##__VA_ARGS__)


struct cipher_ctl cipher_module_ctl =
{
	.reg_int_sta   = {0x408, 0x414, 0x420, 0x444, 0x450},
	.reg_int_mask  = {0x40C, 0x418, 0x424, 0x448, 0x454},
	.reg_int_msta  = {0x410, 0x41c, 0x428, 0x44c, 0x458},
#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
	.keyram_backup = {0}
#endif
};
unsigned int fifo_elem_cnt[7][3] =
{  /*  bd    cd    rd */
	{ 200,    0,    0},/* chn-0 */
	{  32,  320,   32},/* chn-1 */
	{  32,  320,   32},/* chn-2 */
	{ 1024, 4096,1024},/* chn-3 */
	{   0,    0,    0},/* chn-4 */
	{ 1024, 4096,   0},/* chn-5 */
	{ 200,    0,    0} /* chn-6 */
};
static unsigned int  intmask[] = {0x3737373F, 0x0707070F, 0x000000FF, 0xFFFFFFF7, 0xFFFFFFFF};
static unsigned char key_length_table[CIPHER_KEY_LEN_BUTTOM] = {16, 24, 32};
static unsigned char direction      [CIPHER_SINGLE_OPT_BUTTOM + CIPHER_RELA_OPT_BUTTOM]  = {0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1};
static unsigned char security_en    [CIPHER_SINGLE_OPT_BUTTOM + CIPHER_RELA_OPT_BUTTOM]  = {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
static unsigned char integrity_en   [CIPHER_SINGLE_OPT_BUTTOM + CIPHER_RELA_OPT_BUTTOM]  = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static unsigned char mac_position   [CIPHER_SINGLE_OPT_BUTTOM + CIPHER_RELA_OPT_BUTTOM]  = {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1};
static unsigned char mac_length     [CIPHER_SINGLE_OPT_BUTTOM + CIPHER_RELA_OPT_BUTTOM]  = {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};
static unsigned char integrity_first[CIPHER_SINGLE_OPT_BUTTOM + CIPHER_RELA_OPT_BUTTOM]  = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1};
static unsigned char int_enable_tbl [CIPHER_SUBM_BUTTOM] = {0, 0, 1};
static unsigned char ph_len_in_pkt [CIPHER_HDR_BIT_TYPE_BUTT] = {    0,     1,     1,     2,     1,     1,     2};
static unsigned char aph_len_in_bd [CIPHER_HDR_BIT_TYPE_BUTT] = {    0,     1,     1,     2,     1,     1,     2};
static unsigned char aph_attr      [CIPHER_HDR_BIT_TYPE_BUTT] = {    0,     1,     1,     1,     0,     0,     0};
static unsigned int  aph_mast      [CIPHER_HDR_BIT_TYPE_BUTT] = {0x000, 0x01F, 0x07F, 0xFFF, 0x01F, 0x07F, 0xFFF};

struct cipher_debug_ctl cipher_dbg_log =
{
	.bdq_full_times 	= {0},
	.cdq_full_times 	= {0},
	.chn_rst_times  	= {0},
	.chn_bdset_time		= {0},
	.set_bd_timeout		= {0},

	/*RD related*/
	.rdq_empty_cnt		= {0},
	.rd_int_chk_err		= {0},
	.rd_len_chk_err 	= {0},
	.rd_invalid			= {0},

	/*cipher status*/
	.set_rate_err		= 0,
	.alloc_failed		= 0,
	.set_psam_failed	= 0,
	.dump_init_failed	= 0,
	.suspend_failed		= 0
};

#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
int cipher_suspend(struct dpm_device *dev);
int cipher_resume(struct dpm_device *dev);

struct dpm_device cipher_device =
{
	.device_name  = "balong cipher driver",
	.suspend      = cipher_suspend,
	.resume       = cipher_resume,
	.prepare      = NULL,
	.suspend_late = NULL,
	.complete     = NULL,
	.resume_early = NULL,
};
#elif (defined(CONFIG_RSR_ACC))
int cipher_suspend_begin(rsr_acc_description *bd_descri);
void cipher_suspend_end(rsr_acc_description *bd_descri);
void cipher_resume_begin(rsr_acc_description *bd_descri);
void cipher_resume_end(rsr_acc_description *bd_descri);
struct rsracc_cb_s cipher_dev = {
	.suspend_begin = cipher_suspend_begin,
	.suspend_end = cipher_suspend_end,
	.resume_begin = cipher_resume_begin,
	.resume_end = cipher_resume_end,
};

rsr_acc_description cipher_rsr_bd = {
	.level = rsracc_bd_level_0,
	.name = "cipher_rsr",
	.ops = &cipher_dev,
	.only_ops_in_bd = false,
	.need_rsracc_assign_bakaddr = true,
	.bd_valid_flow = both_save_and_resume_flow,
};
#endif

//extern u32 bsp_get_slice_value_hrt(void);

#define CCORE_RST_TIMEOUT         (327) /*10ms*/
#define TIMEOUT(a)   (get_timer_slice_delta(a, bsp_get_slice_value()) < CCORE_RST_TIMEOUT)

#ifdef CIPHER_DEBUG_BD_CD_QUEUE
#define CIPHER_BCD_CNT 22

struct cipher_debug_bd_cd {
	unsigned int bd_widx;
	unsigned int bd_ridx;

	unsigned int cd_widx;
	unsigned int cd_ridx;
};

unsigned int cipher_debug_bd_idx = 0;
#endif

static int ccpu_reset_cipher_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;
	unsigned int cipher_reg_base;
	unsigned int crg_clk_stat4;
	unsigned int i;

    bsp_reset_timestamp(0x1, STAMP_RESET_CIPHER_ENTER_IDLE);
	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	crg_clk_stat4 = cipher_module_ctl.crg_clk_stat4;
	if(!crg_clk_stat4) {
        bsp_reset_timestamp(0x2, STAMP_RESET_CIPHER_ENTER_IDLE);
		return CIPHER_SUCCESS;
	}

    /*查询cipher clk的状态*/
    regvalue = readl((unsigned long)bsp_sysctrl_addr_byindex(sysctrl_mdm) + crg_clk_stat4);
    regvalue &= (unsigned int)0x1 << 17;
    if(regvalue != ((unsigned int)0x1 << 17)){
        bsp_reset_timestamp(0x3, STAMP_RESET_CIPHER_ENTER_IDLE);
        return CIPHER_SUCCESS;
    }
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_CIPHER_DISABLE_CHANNLE);

	/*disable all channels*/
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		writel(0x40000000, cipher_reg_base + CIPHER_CHN_ENABLE(i));//chn-i
	}

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_CIPHER_ENTER_IDLE);
    u32slicebegin = bsp_get_slice_value();
	//wait for cipher being idle
    do{
        regvalue = readl(cipher_reg_base + HI_CIPHER_CTRL_OFFSET);
        regvalue &= (0x1U << 31);
    }while(regvalue && TIMEOUT(u32slicebegin));
    if(regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_CIPHER)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return CIPHER_TIME_OUT;
    }

	/* reset whole cipher ip*/
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_CIPHER_SOFT_RESET);
    regvalue = readl(cipher_reg_base + HI_CIPHER_CTRL_OFFSET);
    regvalue |= 0x1U;
    writel(regvalue, cipher_reg_base + HI_CIPHER_CTRL_OFFSET);

    return CIPHER_SUCCESS;
}


void cipher_disable_aes_opt_bypass(int channel)
{
	unsigned int reg;
	unsigned int cipher_reg_base;

	cipher_reg_base= (unsigned int)cipher_module_ctl.reg_virt_base;
	/*lint -e737*/
	reg = readl(cipher_reg_base + CIPHER_TEST_REG(channel));
	reg &= ~0x1;
	writel(reg, cipher_reg_base + CIPHER_TEST_REG(channel));
	/*lint +e737*/

}

int bsp_cipher_set_channel_dma(int channel, int dma)
{
	if (channel < 0 || channel > (CIPHER_CHN_NUM - 1)) {
		return -1;
	}
	cipher_module_ctl.cipher_chn[channel].dma = dma;

	return 0;
}

void cipher_enable_aes_opt_bypass(int channel)
{
	unsigned int reg;
	unsigned int cipher_reg_base;

	cipher_reg_base= (unsigned int)cipher_module_ctl.reg_virt_base;
	/*lint -e737*/
	reg = readl(cipher_reg_base + CIPHER_TEST_REG(channel));
	reg |= 0x1;
	writel(reg, cipher_reg_base + CIPHER_TEST_REG(channel));
	/*lint +e737*/
}

unsigned int cipher_get_cd_ridx(struct cipher_bd *bd, struct fifo_ctl *cd)
{
	unsigned int r_idx;
	r_idx = (bd->iptr_pad - (unsigned int)cd->fifo_base) / cd->elem_size;

	return r_idx;
}

//valid only when bd->ptr_attr_ilen & CIPHER_BD_IN_CHAIN != 0
unsigned int cipher_get_cd_widx(struct cipher_bd *bd, struct fifo_ctl *cd_fifo)
{
	unsigned int w_idx;
	struct cipher_cd *cur_cd = (struct cipher_cd *)bd->iptr_pad;
	unsigned int end;

	end = cur_cd->ptr_attr & CIPHER_CD_CHAIN_END;
	w_idx = cipher_get_cd_ridx(bd,cd_fifo);

	while(!end) {
		w_idx++;
		cur_cd++;
		end = cur_cd->ptr_attr & CIPHER_CD_CHAIN_END;
	}
	w_idx = w_idx % cd_fifo->elem_cnt;

	return w_idx;
}

static int cipher_special_chn(unsigned int chn)
{
	if(LTE_KEY_OPT_CHANNEL_KDF		 == chn
	|| LTE_SECURITY_CHANNEL_UL_ACC_0 == chn
	|| LTE_SECURITY_CHANNEL_UL_ACC_1 == chn)
		return 1;
	return 0;
}

static void fifo_update_rw_idx(struct cipher_chn_ctl * cur_chn)
{
	unsigned int ridx;
	unsigned int widx;
	unsigned int idx;
	struct cipher_bd * pre_bd = NULL;
	struct fifo_ctl  *f_ctl;

	/* Update CD and BD,
	 * updating CD must before updating BD, because CD rely on BD
	 */
	f_ctl = &(cur_chn->cd_fifo);
	(*(cur_chn->ops.get_bdq_rwptr))(cur_chn, &ridx, &widx);
	if (ridx == widx){
		f_ctl->read_idx = f_ctl->write_idx;
	} else {
		idx = ridx; /*get the last bd*/
		while(idx != cur_chn->bd_fifo.read_idx) {
			pre_bd = (struct cipher_bd *)cur_chn->bd_fifo.fifo_base + idx;

			if(pre_bd->ptr_attr_ilen & CIPHER_BD_IN_CHAIN) {
				if (idx == ridx){	//Hardware owned it.
					f_ctl->read_idx = cipher_get_cd_ridx(pre_bd, f_ctl);
				} else {			//Software owned it.
					f_ctl->read_idx = cipher_get_cd_widx(pre_bd, f_ctl);
				}
				break;
			}

			idx += cur_chn->bd_fifo.elem_cnt - 1;
			idx %= cur_chn->bd_fifo.elem_cnt;
		}
	}

	cur_chn->bd_fifo.read_idx = ridx;
}

void cipher_update_all_chn(void)
{
	unsigned int chn;
	struct cipher_chn_ctl * cur_chn;

	for (chn = 0; chn < cipher_module_ctl.chn_cnt; chn++) {
		cur_chn = cipher_module_ctl.cipher_chn + chn;
		if(cipher_special_chn(chn)) {
			continue;
		}

		fifo_update_rw_idx(cur_chn);

		/* Only channels that not special or straight have RDs. */
		if (!(cur_chn->straight)) {
			unsigned int cipher_reg_base;
			unsigned int w_ptr;

			cipher_reg_base= (unsigned int)cipher_module_ctl.reg_virt_base;
			w_ptr = readl(cipher_reg_base + CIPHER_CHNRDQ_RWPTR(cur_chn->chn_id));
			w_ptr = (w_ptr & CIPHER_RW_MASK);

			cur_chn->rd_fifo.write_idx = w_ptr;
		}
	}
}

static unsigned int fifo_get_free_bd_cnt(struct fifo_ctl * f_ctl)
{
	unsigned long spinlock_flag = 0;
	unsigned int bd_num = 0;

	spin_lock_irqsave(&f_ctl->lock, spinlock_flag);

	bd_num = (f_ctl->elem_cnt + f_ctl->read_idx - f_ctl->write_idx - 1) % f_ctl->elem_cnt;

	spin_unlock_irqrestore(&f_ctl->lock, spinlock_flag);

	return bd_num;
}

static void fifo_get_free_cd_cnt(struct fifo_ctl * f_ctl,
						unsigned int * l_cnt, unsigned int * r_cnt)
{
	unsigned long spinlock_flag = 0;
	unsigned int left_count;
	unsigned int right_count;

	spin_lock_irqsave(&f_ctl->lock, spinlock_flag);

	if (f_ctl->read_idx <= f_ctl->write_idx) {
		right_count = f_ctl->elem_cnt - f_ctl->write_idx;
		if (f_ctl->read_idx == 0) {

			/* ridx=0, rcnt must leave 1 gap to avoid widx catch ridx */
			right_count--;
			left_count = 0;
		} else if (f_ctl->read_idx == 1) {

			/* ridx=1, lcnt have no spce */
			left_count = 0;
		} else {

			/* normal*/
			left_count = f_ctl->read_idx - 1;
		}
	} else {
		left_count = 0;
		right_count = f_ctl->read_idx - f_ctl->write_idx - 1;	//at least leave 1 gap
	}

	*l_cnt = left_count;
	*r_cnt = right_count;

	spin_unlock_irqrestore(&f_ctl->lock, spinlock_flag);
}

static unsigned int fifo_get_filled_bd_cnt(struct fifo_ctl * f_ctl)
{
	unsigned int bd_num = 0;
	unsigned long spinlock_flag = 0;

	spin_lock_irqsave(&f_ctl->lock, spinlock_flag);

	bd_num = (f_ctl->elem_cnt + f_ctl->write_idx - f_ctl->read_idx) % f_ctl->elem_cnt;

	spin_unlock_irqrestore(&f_ctl->lock, spinlock_flag);

	return bd_num;
}

static int fifo_get_free_elems(struct fifo_ctl * f_ctl,
					enum fifo_free_pos free_pos, void ** element_addr)
{
	unsigned long flag = 0;

	spin_lock_irqsave(&f_ctl->lock, flag);
	if(FIFO_RIGHT == free_pos)
		*element_addr = (void *)((unsigned int)f_ctl->fifo_base +
									f_ctl->elem_size * f_ctl->write_idx);
	else
		*element_addr = f_ctl->fifo_base;
	spin_unlock_irqrestore(&f_ctl->lock, flag);
	return 0;
}

static void fifo_move_bd_widx(struct fifo_ctl * f_ctl, unsigned int nn)
{
	unsigned long flag = 0;

	spin_lock_irqsave(&f_ctl->lock, flag);

	f_ctl->write_idx += nn;
	f_ctl->write_idx %= f_ctl->elem_cnt;

	spin_unlock_irqrestore(&f_ctl->lock, flag);
}

static int fifo_move_ridx(struct fifo_ctl * f_ctl, unsigned int nn)
{
	unsigned long flag = 0;

	if(FIFO_BDQ == f_ctl->type)
	{
		CIPHER_ERR_PRINT("ERR : bdq ridx should not be moved\n");
		return CIPHER_CHECK_ERROR;
	}

	spin_lock_irqsave(&f_ctl->lock, flag);
	f_ctl->read_idx += nn;
	f_ctl->read_idx %= f_ctl->elem_cnt;
	spin_unlock_irqrestore(&f_ctl->lock, flag);
	return 0;
}

static int fifo_rst_rwidx(struct fifo_ctl * f_ctl)
{
	unsigned long flag = 0;

	spin_lock_irqsave(&f_ctl->lock, flag);
	f_ctl->read_idx  = 0;
	f_ctl->write_idx = 0;
	spin_unlock_irqrestore(&f_ctl->lock, flag);
	return 0;
}

struct fifo_ops cipher_fifo_ops = {.get_free_cd_cnt   	= fifo_get_free_cd_cnt,
								   .get_free_bd_cnt		= fifo_get_free_bd_cnt,
                                   .get_elems_addr      = fifo_get_free_elems,
                                   .get_filled_bd_cnt 	= fifo_get_filled_bd_cnt,
                                   .move_bd_widx        = fifo_move_bd_widx,
                                   .move_ridx           = fifo_move_ridx,
                                   .rst_rwidx           = fifo_rst_rwidx
                                  };

static int cipher_chn_idle(struct cipher_chn_ctl * chn_ctl)
{
	unsigned int reg_en = 0;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;

	reg_en = readl(cipher_reg_base + CIPHER_CHN_ENABLE(chn_ctl->chn_id));
	return reg_en & (0x1U << 31) ? 0 : 1;
}

//FIXME:reset psam first, or reset cipher chn first ?
//WARNING:the chn must be idle befor calling this function
static inline int cipher_rst_chn(struct cipher_chn_ctl * chn_ctl)
{
	int ret = 0;
	unsigned int chn_cfg_val = (0x1U << 3) | (0x3U << 5);
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	chn_cfg_val |= (((CIPHER_IV_NUM & 0x1) << 1) | CIPHER_IV_SEL);

	writel(0x3, cipher_reg_base + CIPHER_CHN_RESET(chn_ctl->chn_id));
	writel(chn_cfg_val, cipher_reg_base + CIPHER_CHN_CONFIG(chn_ctl->chn_id));

	/*restore BDQ*/
	writel((unsigned long)(chn_ctl->bd_fifo.fifo_base),
			cipher_reg_base + CIPHER_CHNBDQ_BASE(chn_ctl->chn_id));
	writel(chn_ctl->bd_fifo.elem_cnt - 1,
				cipher_reg_base + CIPHER_CHNBDQ_SIZE(chn_ctl->chn_id));
	writel(0, cipher_reg_base + CIPHER_CHNBDQ_RWPTR(chn_ctl->chn_id));

	/*restore RDQ*/
	writel((unsigned long)(chn_ctl->rd_fifo.fifo_base),
						cipher_reg_base + CIPHER_CHNRDQ_BASE(chn_ctl->chn_id));
	writel(chn_ctl->rd_fifo.elem_cnt - 1,
						cipher_reg_base + CIPHER_CHNRDQ_SIZE(chn_ctl->chn_id));
	writel(0, cipher_reg_base + CIPHER_CHNRDQ_RWPTR(chn_ctl->chn_id));

	if(chn_ctl->straight)
		ret = bsp_psam_cipher_ch_srst(1);
	writel(0x1, cipher_reg_base + CIPHER_CHN_ENABLE(chn_ctl->chn_id));

	cipher_dbg_log.chn_rst_times[chn_ctl->chn_id] += 1;
	return ret;
}

static inline void cipher_get_rdq_rwptr(struct cipher_chn_ctl * chn_ctl,
								unsigned int *read_idx, unsigned int *write_idx)
{
	unsigned int rwptr = 0;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	rwptr = readl(cipher_reg_base + CIPHER_CHNRDQ_RWPTR(chn_ctl->chn_id));

	*read_idx = (int)((rwptr >> CIPHER_RW_OFFSET) & CIPHER_RW_MASK);
	*write_idx = (int)(rwptr & CIPHER_RW_MASK);
}

static inline void cipher_get_bdq_rwptr(struct cipher_chn_ctl * chn_ctl,
											unsigned int * r, unsigned int * w)
{
	unsigned int rwptr = 0;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	rwptr = readl(cipher_reg_base + CIPHER_CHNBDQ_RWPTR(chn_ctl->chn_id));

	*r = (rwptr >> CIPHER_RW_OFFSET) & CIPHER_RW_MASK;
	*w = rwptr & CIPHER_RW_MASK;
}

static inline void cipher_move_rdq_r_ptr(struct cipher_chn_ctl * chn_ctl)
{
	unsigned int r_ptr;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;

	if(chn_ctl->straight)
		return ;

	r_ptr = (chn_ctl->rd_fifo.read_idx & CIPHER_RW_MASK) << CIPHER_RW_OFFSET;
	writel(r_ptr, cipher_reg_base + CIPHER_CHNRDQ_RWPTR(chn_ctl->chn_id));
}

static inline int cipher_move_bdq_w_ptr(struct cipher_chn_ctl * chn_ctl)
{
	unsigned int reg_rwptr;
	unsigned int chn_id;
	unsigned int cipher_reg_base;
	struct fifo_ctl  *f_ctl;
	unsigned long flag = 0;

	chn_id = chn_ctl->chn_id;
	f_ctl = &(chn_ctl->bd_fifo);
	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;

	spin_lock_irqsave(&f_ctl->lock, flag);
	if(chn_ctl->straight) {
		int ret;
		reg_rwptr = chn_ctl->bd_fifo.write_idx & CIPHER_WMASK;
		ret = bsp_psam_move_cbdq_ptr(reg_rwptr);
		spin_unlock_irqrestore(&f_ctl->lock, flag);

		return ret;
	} else {
		reg_rwptr = readl(cipher_reg_base + CIPHER_CHNBDQ_RWPTR(chn_id));
		reg_rwptr = (reg_rwptr & ~ CIPHER_WMASK);
		reg_rwptr = reg_rwptr | (chn_ctl->bd_fifo.write_idx & CIPHER_WMASK);
		writel(reg_rwptr, cipher_reg_base + CIPHER_CHNBDQ_RWPTR(chn_id));
		spin_unlock_irqrestore(&f_ctl->lock, flag);
	}

	return CIPHER_SUCCESS;
}

/*
 * note : cd list 中cd的个数一定等于ptr中节点的个数
 */
static int cipher_cfg_cds(struct cipher_chn_ctl * chn_ctl,
								struct cipher_cd * cds_base, void * ptr)
{
	unsigned int total_size = 0;
	void *       next_node = ptr;
	struct cipher_cd * cur_cd = cds_base;

	while(next_node)
	{
		cur_cd->ptr = (u32)readl((unsigned long)next_node + chn_ctl->idata_ptr_off);
		cur_cd->ptr_attr = (u32)readl((unsigned long)next_node + chn_ctl->idata_size_off);
		next_node  = (void *)readl((unsigned long)next_node + chn_ctl->idata_nxt_ptr_off);
		total_size += cur_cd->ptr_attr;
		cur_cd++;
	}
	cur_cd--;
	cur_cd->ptr_attr |= 0x1U << 16;
#ifdef CIPHER_CACHE_ENABLE
	osl_cache_flush(OSL_DATA_CACHE,(void*)cds_base,
							(cur_cd - cds_base + 1) * sizeof(struct cipher_cd));
#endif
	return (int)total_size;
}


int cipher_cfg_single_bd(struct cipher_chn_ctl * chn_ctl,
	CIPHER_SINGLE_CFG_S * cfg_infor, struct cdlist_info * cdlist_infor)
{
	struct cipher_bd * cur_bd;
	unsigned int aph_count = 0;
	int opt_idx = 0;
#if(0 != CIPHER_IV_SEL)
	int j = 0;
#endif

	cur_bd = (struct cipher_bd * )chn_ctl->bd_fifo.fifo_base + chn_ctl->bd_fifo.write_idx;
	opt_idx = (cfg_infor->enOpt & 0xFFFF) +
						(((unsigned int)cfg_infor->enOpt >> 28) & 0xF);
	if (chn_ctl->dma) {
		cur_bd->cfg = 0x1 | (0x1 << 28); /*down link and enable bd done intr*/
	} else {
		cur_bd->cfg = ((0x0    							 & 0x7) << 29) |
			 ((0x1 							             & 0x1) << 28) |
			 ((cfg_infor->stAlgKeyInfo.u32KeyIndexInt    & 0xF) << 24) |
			 ((cfg_infor->stAlgKeyInfo.u32KeyIndexSec    & 0xF) << 20) |
			 ((aph_len_in_bd[cfg_infor->enAppdHeaderLen] & 0x3) << 18) |
			 ((ph_len_in_pkt[cfg_infor->enHeaderLen]     & 0x3) << 16) |
			 ((mac_length  [opt_idx]                     & 0x1) << 15) |
			 ((mac_position[opt_idx]                     & 0x1) << 14) |
			 ((int_enable_tbl[cfg_infor->enSubmAttr]     & 0x1) << 13) |
			 ((CIPHER_CONFIG_AEC_CTR                     & 0x7) << 10) |
			 ((cfg_infor->stAlgKeyInfo.enAlgIntegrity    & 0x7) <<  7) |
			 ((cfg_infor->stAlgKeyInfo.enAlgSecurity     & 0x7) <<  4) |
			 ((integrity_first[opt_idx]                  & 0x1) <<  3) |
			 ((integrity_en   [opt_idx]                  & 0x1) <<  2) |
			 ((security_en    [opt_idx]                  & 0x1) <<  1) |
			 ((direction      [opt_idx]                  & 0x1) <<  0);
	}

	if (chn_ctl->straight) {
		cur_bd->usr_field[0] = cfg_infor->usr_field1;
		cur_bd->usr_field[1] = cfg_infor->usr_field2;
		cur_bd->usr_field[2] = cfg_infor->usr_field3;
	} else {
		cur_bd->usr_field[0] = (unsigned int)cfg_infor->pInMemMgr;
		cur_bd->usr_field[1] = (unsigned int)cfg_infor->pOutMemMgr;
		cur_bd->usr_field[2] = (unsigned int)cfg_infor->u32Private;
	}

	/*lint -e701*/
	aph_count = (cfg_infor->u32Count & aph_mast[cfg_infor->enAppdHeaderLen]) <<
		((3 - aph_len_in_bd[cfg_infor->enAppdHeaderLen]) << 3);

	cur_bd->aph = (cfg_infor->u8BearId                &       0x1F) << 27 |
		        (cfg_infor->u8Direction               &        0x1) << 26 |
		        (aph_attr[cfg_infor->enAppdHeaderLen] &        0x1) << 24 |
		        (aph_count                            & 0x00FFFFFF) <<  0;
	/*lint +e701*/
#if(0 == CIPHER_IV_SEL)
	cur_bd->count = cfg_infor->u32Count;
#else
	for(j = 0; j < (CIPHER_IV_NUM + 1); j++)
	{
		writel_relaxed(cfg_infor->iv[0], (unsigned long)((u32*)(&cur_bd->iv[j]) + 0));
		writel_relaxed(cfg_infor->iv[1], (unsigned long)((u32*)(&cur_bd->iv[j]) + 1));
		writel_relaxed(cfg_infor->iv[2], (unsigned long)((u32*)(&cur_bd->iv[j]) + 2));
		writel_relaxed(cfg_infor->iv[3], (unsigned long)((u32*)(&cur_bd->iv[j]) + 3));
	}
#endif
	if(cfg_infor->bMemBlock)
	{
		cur_bd->iptr_pad      = (u32)cfg_infor->pInMemMgr;
		cur_bd->ptr_attr_ilen = (u32)((cfg_infor->u32BlockLen & 0xFFFF) & ~(0x1U << 16));
		cur_bd->optr          = (u32)cfg_infor->pOutMemMgr;
	}
	else
	{
		cur_bd->iptr_pad      = (u32)cdlist_infor->cdlist_base;
		cur_bd->ptr_attr_ilen = ((cdlist_infor->cdlist_size & 0xFFFF) | (0x1U << 16));
		if (NULL == cfg_infor->pOutMemMgr)
			cur_bd->optr = 0U;
		else
			cur_bd->optr = readl((unsigned long)cfg_infor->pOutMemMgr + chn_ctl->odata_ptr_off);
	}
#if 0
	cur_bd->offset_olen = cfg_infor->u32OutLen & 0xFFFF;
	if(cfg_infor->u32Offset || ((cfg_infor->u32OutLen < cfg_infor->u32BlockLen) && cfg_infor->u32OutLen))
	{
		cur_bd->ptr_attr_ilen |= 0x1U << 19;
		cur_bd->offset_olen   |= ((cfg_infor->u32Offset & 0xFFFF) << 16);
	}
#else
	cur_bd->ptr_attr_ilen &= (~0xe0000);
#endif

#ifdef CIPHER_CACHE_ENABLE
	osl_cache_flush(OSL_DATA_CACHE,(void*)cur_bd, sizeof(struct cipher_bd));
#endif

	return MDRV_OK;
}

/*
 *Fucntion name:cipher_get_rds
 *return value > 0:fetched rd count
 *return value = 0:input parameters check error
 *err_cnt: record invalid cipher RD number
 */
int cipher_get_rds(struct cipher_chn_ctl * chn_ctl,unsigned int *err_cnt,
							CIPHER_RD_INFO_S * rds_info, unsigned int rds_cnt)
{
	unsigned int r_idx = 0;
	unsigned int w_idx = 0;
	unsigned int rd_status;
	unsigned int i;
	struct cipher_rd *tmp_rd = NULL;
	struct fifo_ctl  *tmp_fifo = &(chn_ctl->rd_fifo);

	/*error count should be initialized to zero*/
	*err_cnt = 0;
	if(chn_ctl->straight)
		return CIPHER_GET_ZERO_RD;/* straight channel rds should not be fetched */

	cipher_get_rdq_rwptr(chn_ctl, &r_idx, &w_idx);
	tmp_fifo->write_idx = w_idx;
	if(r_idx == w_idx)
	{
		cipher_dbg_log.rdq_empty_cnt[chn_ctl->chn_id]++;
		return CIPHER_GET_ZERO_RD;
	}

#ifdef CIPHER_CACHE_ENABLE
	osl_cache_invalid(OSL_DATA_CACHE, tmp_fifo->fifo_base,
									tmp_fifo->elem_size * tmp_fifo->elem_cnt);
#endif

	for( i = 0; (r_idx != w_idx) && (i < rds_cnt); i++)
	{
		tmp_rd = (struct cipher_rd *)((unsigned int)tmp_fifo->fifo_base +
												tmp_fifo->elem_size * r_idx);
		if(!(tmp_rd->cfg & CIPHER_RD_VALID))
		{
			CIPHER_ERR_PRINT("CIPHER_INVALID_RD chn:%d\n", chn_ctl->chn_id);
			CIPHER_ERR_PRINT("rd config:%#x\n", tmp_rd->cfg);
			cipher_dbg_log.rd_invalid[chn_ctl->chn_id]++;
			(*err_cnt)++;
		} else {
			if(rds_info){
				rds_info[i].enstat = (CIPHER_NOTIFY_STAT_E)((tmp_rd->cfg & RD_ENSTAT_MASK) >> 29);
				rds_info[i].usr_field1 = tmp_rd->usr_field[0];
				rds_info[i].usr_field2 = tmp_rd->usr_field[1];
				rds_info[i].usr_field3 = tmp_rd->usr_field[2];
			}

			tmp_rd->cfg &= ~CIPHER_RD_VALID;
			rd_status = (tmp_rd->cfg >> 29) & 0x3;
			if(rd_status){
				if (CIPHER_STAT_CHECK_ERR == rd_status)
					cipher_dbg_log.rd_int_chk_err[chn_ctl->chn_id]++;
				else if (CIPHER_LEN_CHK_ERR == rd_status)
					cipher_dbg_log.rd_len_chk_err[chn_ctl->chn_id]++;

				(*err_cnt)++;
			}
		}

		(void)(tmp_fifo->ops.move_ridx)(tmp_fifo, 1);
		r_idx = (r_idx + 1) % chn_ctl->rd_fifo.elem_cnt;
	}

	cipher_move_rdq_r_ptr(chn_ctl);
	return (int)i;
}

struct chn_ops cipher_chn_ops = {.cfg_cds = cipher_cfg_cds,
	                             .cfg_single_bd = cipher_cfg_single_bd,
	                             .get_rds = cipher_get_rds,
	                             .get_rdq_rwptr = cipher_get_rdq_rwptr,
	                             .get_bdq_rwptr = cipher_get_bdq_rwptr,
	                             .move_rdq_r_ptr = cipher_move_rdq_r_ptr,
	                             .move_bdq_w_ptr = cipher_move_bdq_w_ptr,
	                             .chn_idle = cipher_chn_idle,
	                             .chn_rst = cipher_rst_chn
	                            };

OSL_IRQ_FUNC(irqreturn_t, cipher_isr, intLvl, arg)
{
	unsigned int r_idx, w_idx;
	struct cipher_rd      * cur_rd  = NULL;
	struct cipher_chn_ctl * cur_chn = NULL;
	unsigned char           int_chn_bd_done = 0;
	unsigned int i = 0;
	u32 reg_int[4] = {0};
	unsigned int int_reg_num;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	if (CIPHER_CHN_NUM == cipher_module_ctl.chn_cnt)
		int_reg_num = 4;
	else
		int_reg_num = 2;

	for(i = 0; i < int_reg_num; i++)
	{
		reg_int[i] = readl(cipher_reg_base + cipher_module_ctl.reg_int_msta[i]);
		writel(reg_int[i], cipher_reg_base + cipher_module_ctl.reg_int_msta[i]);
	}

	int_chn_bd_done = ((reg_int[0] >>  3) & 0x1) << CIPHER_SECURITY_CHANNEL_0 |
		              ((reg_int[0] >> 11) & 0x1) << CIPHER_SECURITY_CHANNEL_1 |
		              ((reg_int[0] >> 19) & 0x1) << CIPHER_SECURITY_CHANNEL_2 |
		              ((reg_int[0] >> 27) & 0x1) << CIPHER_SECURITY_CHANNEL_3 |
		              ((reg_int[2] >>  3) & 0x1) << CIPHER_SECURITY_CHANNEL_4 |
		              ((reg_int[3] >>  3) & 0x1) << CIPHER_SECURITY_CHANNEL_5 |
		              ((reg_int[3] >> 11) & 0x1) << CIPHER_SECURITY_CHANNEL_6;

	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		if(!(int_chn_bd_done & (0x1U << i)))
			continue;
		cur_chn = &cipher_module_ctl.cipher_chn[i];
		if(NULL == cur_chn->func_notify)
			continue;

		/*Acc uplink exstreme stress test*/
		if(i == CIPHER_SECURITY_CHANNEL_0 || i == CIPHER_SECURITY_CHANNEL_6){
			cur_chn->func_notify(i,	0, 0, CIPHER_STAT_OK, 0);
		} else {
			(*cur_chn->ops.get_rdq_rwptr)(cur_chn, &r_idx, &w_idx);

			for( ; r_idx != w_idx; r_idx = (r_idx + 1) % cur_chn->rd_fifo.elem_cnt)
			{
				cur_rd = (struct cipher_rd *)(
							(unsigned int)cur_chn->rd_fifo.fifo_base +
										  r_idx * sizeof(struct cipher_rd));

				cur_chn->func_notify(
					i,
					cur_rd->usr_field[0],
					cur_rd->usr_field[1],
					(CIPHER_NOTIFY_STAT_E)((cur_rd->cfg & 0x60000000) >> 29),
					cur_rd->usr_field[2]
					);
				cur_rd->cfg &= ~(0x80000000);
				(void)(*cur_chn->rd_fifo.ops.move_ridx)(&(cur_chn->rd_fifo), 1);
			}
			cipher_move_rdq_r_ptr(&cipher_module_ctl.cipher_chn[i]);
		}
	}
	return IRQ_HANDLED;
}

int mdrv_cipher_set_key(const void * pKeyAddr, CIPHER_KEY_LEN_E enKeyLen,
												unsigned int u32KeyIndex)
{
	unsigned int i = 0;
	unsigned int value = 0;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	void * dest_addr = (void *)(cipher_reg_base + HI_KEY_RAM_OFFSET	  +
						u32KeyIndex * CIPHER_KEY_LEN + CIPHER_KEY_LEN -
							(unsigned int)key_length_table[enKeyLen]);
	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}
	while(i < key_length_table[enKeyLen])
	{
		value = readl((unsigned long)pKeyAddr);
		value = CIPHER_BSWAP32(value);
		writel_relaxed(value, (unsigned long)dest_addr);

		dest_addr = (void *)((unsigned int)dest_addr + sizeof(u32));
		pKeyAddr  = (void *)((unsigned int)pKeyAddr + sizeof(u32));
		i         += sizeof(u32);
	}
	return MDRV_OK;
}

int mdrv_cipher_get_key(unsigned int u32KeyIndex, KEY_GET_S *pstKeyGet)
{
	void * dest_addr = NULL;
	void * src_addr  = NULL;
	unsigned int i     = 0;
	u32 value = 0;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	src_addr = (void *)(cipher_reg_base + HI_KEY_RAM_OFFSET      +
				(u32KeyIndex * CIPHER_KEY_LEN) + (CIPHER_KEY_LEN -
			(unsigned int)key_length_table[pstKeyGet->enKeyLen]));

	dest_addr = pstKeyGet->pKeyAddr;

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}
	while(i < key_length_table[pstKeyGet->enKeyLen])
	{
		value = readl((unsigned long)src_addr);
		value = CIPHER_BSWAP32(value);
		writel_relaxed(value, (unsigned long)dest_addr);

		i         += sizeof(u32);
		src_addr = (void *)((unsigned int)src_addr + sizeof(u32));
		dest_addr = (void *)((unsigned int)dest_addr + sizeof(u32));
	}

	/* Reverse key_length_table to get lenth enum */
	if (i >= 16) {
		*(pstKeyGet->penOutKeyLen) = (i-16)/8;
	} else {
		return CIPHER_INVALID_NUM;
	}
	
	return MDRV_OK;
}

int mdrv_cipher_purge_chan(unsigned int chn_id)
{
	/*lint -e830*/
	unsigned int reg_en = 0;
	int ret = 0;
	unsigned long irq_flag = 0;
	unsigned int err_cnt = 0;
	CIPHER_RD_INFO_S tmp_rd_info;
	/*lint +e830*/
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	struct cipher_chn_ctl * cur_chn = &cipher_module_ctl.cipher_chn[chn_id];

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	if(cur_chn->need_purge)
		osl_sem_down(&cur_chn->chn_sem);

	cur_chn->purging = 1;

	/* protect this not to be interrupted by irqs */
	local_irq_save(irq_flag);
	do{
		if(!cur_chn->straight)
		{
			ret = (*cur_chn->ops.get_rds)(cur_chn, &err_cnt, &tmp_rd_info, 1);
			if(ret > 0)
			{
				if(cur_chn->func_free_inmem)
					cur_chn->func_free_inmem((void*)tmp_rd_info.usr_field1);
				if(cur_chn->func_free_outmem)
					cur_chn->func_free_outmem((void*)tmp_rd_info.usr_field2);
			}
		}
		reg_en = readl(cipher_reg_base + CIPHER_CHN_ENABLE(chn_id));
		reg_en &= (0x1U << 31);
	}while(reg_en && !ret);/* chn is idle and all rds are handled */

	(void)(*cur_chn->ops.chn_rst)(cur_chn);
	(void)(*cur_chn->bd_fifo.ops.rst_rwidx)(&(cur_chn->bd_fifo));
	(void)(*cur_chn->rd_fifo.ops.rst_rwidx)(&(cur_chn->rd_fifo));
	(void)(*cur_chn->cd_fifo.ops.rst_rwidx)(&(cur_chn->cd_fifo));
	cur_chn->pre_check_bd_idx = 0;

	local_irq_restore(irq_flag);

	cur_chn->purging = 0;

	if (cur_chn->need_purge)
		osl_sem_up(&cur_chn->chn_sem);

	if (!cur_chn->need_purge)
		cur_chn->need_purge = 1;

	return MDRV_OK;
}

int mdrv_cipher_set_dbuf_para(unsigned int chn_id, int bSrc,
	unsigned int u32BufOft, unsigned int u32LenOft, unsigned int u32NextOft)
{
	struct cipher_chn_ctl * cur_chn = &cipher_module_ctl.cipher_chn[chn_id];

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if(chn_id > (cipher_module_ctl.chn_cnt - 1)){
		return CIPHER_CHECK_ERROR;
	}

	if(bSrc)
	{
		cur_chn->idata_ptr_off     = u32BufOft;
		cur_chn->idata_size_off    = u32LenOft;
		cur_chn->idata_nxt_ptr_off = u32NextOft;
	}
	else
	{
		cur_chn->odata_ptr_off     = u32BufOft;
		cur_chn->odata_size_off    = u32LenOft;
		cur_chn->odata_nxt_ptr_off = u32NextOft;
	}
	return MDRV_OK;
}

int mdrv_cipher_register_memfree_cb(unsigned int chn_id, int bSrc,
										CIPHER_FREEMEM_CB_T pFunFreeMemCb)
{
	struct cipher_chn_ctl * cur_chn = &cipher_module_ctl.cipher_chn[chn_id];

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if (chn_id > cipher_module_ctl.chn_cnt - 1)	{
		return CIPHER_CHECK_ERROR;
	}

	if(!bSrc)
		cur_chn->func_free_inmem= pFunFreeMemCb;
	else
		cur_chn->func_free_outmem= pFunFreeMemCb;
	return MDRV_OK;
}

int mdrv_cipher_register_notify_cb(CIPHER_NOTIFY_CB_T pFunNotifyCb)
{
	int i = 0;
	struct cipher_chn_ctl * cur_chn = NULL;

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	for(i = 0; i < CIPHER_CHN_NUM; i++)
	{
		cur_chn = &cipher_module_ctl.cipher_chn[i];
		cur_chn->func_notify = pFunNotifyCb;
	}

	return MDRV_OK;
}

#ifdef CIPHER_DEBUG_BD_CD_QUEUE

unsigned int cipher_debug_set_chn(int chn_id)
{
	cipher_module_ctl.idx_dbg_chn = chn_id;

	return cipher_module_ctl.idx_dbg_chn;
}

void cipher_debug_print_idx(void)
{
	unsigned int i;
	unsigned int cfg_num;
	struct cipher_debug_bd_cd * bcd_dbg;

	cfg_num = (CIPHER_BCD_CNT + cipher_module_ctl.cfg_num - 1) % CIPHER_BCD_CNT;
	CIPHER_INFO("Channel:%-1d, last num:%02dth\n", cipher_module_ctl.idx_dbg_chn,
					cfg_num);

	for (i = 0; i < CIPHER_BCD_CNT; i++) {
		bcd_dbg = cipher_module_ctl.bd_cd_idx + i;
		CIPHER_INFO("[%02dth]bd w:%-4d r:%-4d,cd w:%-4d r:%-4d\n", i,
			bcd_dbg->bd_widx, bcd_dbg->bd_ridx, bcd_dbg->cd_widx, bcd_dbg->cd_ridx);

		if ((i+1)%0x40) {
			(void)osl_task_delay(1);
		}
	}
}
#endif

int cipher_prepare_cdlist(struct cipher_chn_ctl *cur_chn,
				CIPHER_SINGLE_CFG_S * p_cfg, struct cdlist_info * cdlist_infor)
{
	void * input_list = p_cfg->pInMemMgr;
	struct fifo_ctl  *cd_fifo = &(cur_chn->cd_fifo);
	unsigned int node_num = 0;
	unsigned int l_cnt = 0;
	unsigned int r_cnt = 0;

	struct cipher_cd * cds_base = NULL;

	if(p_cfg->bMemBlock)
		return MDRV_OK;

	if (!input_list) {
		return CIPHER_NULL_PTR;
	}

	/* count the input list node num */
	while(input_list)
	{
		node_num++;
		input_list = (void*)readl((unsigned long)input_list + cur_chn->idata_nxt_ptr_off);
	}

	(void)(*(cd_fifo->ops.get_free_cd_cnt))(cd_fifo, &l_cnt, &r_cnt);

	/* get cdlist base */
	if(r_cnt >= node_num) {
		(void)(*(cd_fifo->ops.get_elems_addr))(cd_fifo, FIFO_RIGHT, (void **)&cds_base);
		cd_fifo->write_idx += node_num;
		cd_fifo->write_idx %= cd_fifo->elem_cnt;
	} else if(l_cnt >= node_num) {
		(void)(*(cd_fifo->ops.get_elems_addr))(cd_fifo, FIFO_LEFT, (void **)&cds_base);
		cd_fifo->write_idx = node_num;
	} else {

#ifdef CIPHER_DEBUG_BD_CD_QUEUE
		if (cipher_module_ctl.idx_dbg_chn == cur_chn->chn_id) {
			cipher_debug_print_idx();
		}
#endif
		cipher_dbg_log.cd_node_num[cur_chn->chn_id] = node_num;
		cipher_dbg_log.cd_left_cnt[cur_chn->chn_id] = l_cnt;
		cipher_dbg_log.cd_right_cnt[cur_chn->chn_id] = r_cnt;
		cipher_dbg_log.cdq_full_times[cur_chn->chn_id] += 1;

		return CIPHER_FIFO_FULL;
	}

	/* cfg cds */
	cdlist_infor->cdlist_size = (unsigned int)(*cur_chn->ops.cfg_cds)(cur_chn,
												cds_base, p_cfg->pInMemMgr);
	cdlist_infor->cdlist_base = cds_base;
	cdlist_infor->cd_cnt      = node_num;

	return MDRV_OK;
}

int cipher_start_channel(unsigned int chn, unsigned int rd_num,
												CIPHER_SUBMIT_TYPE_E subm_attr)
{
	struct cipher_chn_ctl * cur_chn = &cipher_module_ctl.cipher_chn[chn];
	int ret = 0;
	int r_idx = 0;
	int w_idx = 0;
	unsigned int reg_en = 0;
	unsigned int cipher_reg_base;
	unsigned int err_cnt = 0;
	unsigned int time_record;
	unsigned int time_out;

	/* We use tmp_rdinfo  just for input, it should be NULL in get_rds. */
	CIPHER_RD_INFO_S *tmp_rdinfo = NULL;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	ret = cipher_move_bdq_w_ptr(cur_chn);
	if (ret) {
		return CIPHER_RESETTING_CCORE;
	}

	/*All of the subm_attr should be the same, or it will be error.*/
	if(CIPHER_SUBM_BLK_HOLD != subm_attr)
		return CIPHER_SUCCESS;

	time_record = bsp_get_slice_value();
	do{
		time_out = get_timer_slice_delta(time_record, bsp_get_slice_value());
		if (time_out > (rd_num * TEN_MS)) {
			cipher_dbg_log.set_bd_timeout[chn]++;
			return CIPHER_TIME_OUT;
		}

		/* wait for this bd to be fectched */
		cipher_get_bdq_rwptr(cur_chn, (unsigned int *)&r_idx, (unsigned int *)&w_idx);

		/* wait for this bd being compeleted */
		reg_en = readl(cipher_reg_base + CIPHER_CHN_ENABLE(chn));
		reg_en &= (0x1U << 31);
		
	}while((r_idx != w_idx) || reg_en);

	/*
	 *Confirm : Maybe the current rd is currently on the bus, not reach the ddr yet!
	 *So, should it be waited for a while ?
	 */
	ret = cipher_get_rds(cur_chn, &err_cnt, tmp_rdinfo, rd_num);
	if(ret == 0)			/*Get no RD*/
		return CIPHER_RDQ_NULL;

	if(err_cnt > 0)			/*RD checked error*/
		return CIPHER_INVALID_RD;

	return CIPHER_SUCCESS;
}

int mdrv_cipher_set_bdinfo(unsigned int chn_id, unsigned int num,
												CIPHER_SINGLE_CFG_S * pstCfg)
{
	int ret = -1;
	unsigned int i = 0;
	unsigned int timestamp = 0;
	struct cdlist_info cdlist_infor = {.cd_cnt = 0};/* this entry must be initialize 0 */
	struct cipher_chn_ctl * cur_chn = &cipher_module_ctl.cipher_chn[chn_id];
	unsigned int cd_widx = 0;
	unsigned int bd_widx = 0;
	unsigned int cd_ridx = 0;
	unsigned int free_bd_cnt = 0;

#ifdef CIPHER_DEBUG_BD_CD_QUEUE
	struct cipher_debug_bd_cd *bd_cd_idx;
	struct cipher_ctl *cipher = &cipher_module_ctl;
	if (chn_id == cipher->idx_dbg_chn) {
		bd_cd_idx = cipher->bd_cd_idx + cipher->cfg_num;
		bd_cd_idx->bd_widx = cur_chn->bd_fifo.write_idx;
		bd_cd_idx->bd_ridx = cur_chn->bd_fifo.read_idx;
		bd_cd_idx->cd_widx = cur_chn->cd_fifo.write_idx;
		bd_cd_idx->cd_ridx = cur_chn->cd_fifo.read_idx;
		cipher->cfg_num = (cipher->cfg_num + 1) % CIPHER_BCD_CNT;
	}
#endif

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if(chn_id > cipher_module_ctl.chn_cnt - 1 )
	{
		return CIPHER_CHECK_ERROR;
	}

	timestamp = bsp_get_slice_value_hrt();
	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	if(cur_chn->purging)
	{
		ret = CIPHER_PURGING;
		CIPHER_ERR_PRINT("CIPHER_PURGING\n");
		/*lint -e801*/
		goto SUBMIT_EXT;
		/*lint +e801*/
	}

	fifo_update_rw_idx(cur_chn);

	/*If num > 1, backup bd and cd's status to rollback in case of failure.*/
	if(num > 1){
		bd_widx = cur_chn->bd_fifo.write_idx;
		cd_widx = cur_chn->cd_fifo.write_idx;
		cd_ridx = cur_chn->cd_fifo.read_idx;
	}

	for(i = 0; i < num; i++)
	{
/*lint -save -e801*/
		/* cfg cd list */
		ret = cipher_prepare_cdlist(cur_chn, pstCfg + i, &cdlist_infor);
		if(ret)
			goto SUBMIT_EXT;
		/* cfg bd list */
		free_bd_cnt = (*cur_chn->bd_fifo.ops.get_free_bd_cnt)(&(cur_chn->bd_fifo));
		if (free_bd_cnt < 1) {
			cipher_dbg_log.bdq_full_times[chn_id]++;
			ret = CIPHER_FIFO_FULL;
			goto SUBMIT_EXT;
		}

		(void)(*cur_chn->ops.cfg_single_bd)(cur_chn, pstCfg + i, &cdlist_infor);

/*lint -restore*/
		(*cur_chn->bd_fifo.ops.move_bd_widx)(&(cur_chn->bd_fifo), 1);
	}

	ret = cipher_start_channel(chn_id, num, pstCfg->enSubmAttr);
	if(ret)
		CIPHER_ERR_PRINT("cipher_start_channel fail\n");

SUBMIT_EXT:

	timestamp = bsp_get_slice_value_hrt() - timestamp;

	if(cipher_dbg_log.chn_bdset_time[chn_id] < timestamp)
		cipher_dbg_log.chn_bdset_time[chn_id] = timestamp;
	else
		cipher_dbg_log.chn_bdset_time[chn_id] = cipher_dbg_log.chn_bdset_time[chn_id];

	/*If failed, rollback.*/
	if((num > 1) && ret){
		cur_chn->bd_fifo.write_idx = bd_widx;
		cur_chn->cd_fifo.write_idx = cd_widx;
		cur_chn->cd_fifo.read_idx  = cd_ridx;
	}

	return ret;
}

int mdrv_cipher_get_rdinfo(unsigned int chn_id, CIPHER_RD_INFO_S * pstRd,
													unsigned int * pstRdNum)
{
	int rd_cnt;
	unsigned int err_cnt = 0;
	struct cipher_chn_ctl * cur_chn = NULL;

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if (chn_id > cipher_module_ctl.chn_cnt - 1)
		return CIPHER_CHECK_ERROR;

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	cur_chn = &cipher_module_ctl.cipher_chn[chn_id];
	/*lint -e713*/
	rd_cnt = (*cur_chn->ops.get_rds)(cur_chn, &err_cnt, pstRd, *pstRdNum);
	/*lint +e713*/

	*pstRdNum = rd_cnt;
	if(rd_cnt == 0)
		return CIPHER_RDQ_NULL;

	if(err_cnt > 0)
		return CIPHER_CHECK_ERROR;

	return CIPHER_SUCCESS;
}

int mdrv_cipher_get_bd_num(unsigned int chn_id, BD_TYPE_E bd_type)
{
	int bd_num = 0;
	struct cipher_chn_ctl *cur_chn = &cipher_module_ctl.cipher_chn[chn_id];

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	/*Channel id can't bigger than cipher's biggest channel id,which equal to channel count minus 1.*/
	if (chn_id > (cipher_module_ctl.chn_cnt - 1))
		return CIPHER_CHECK_ERROR;

	/*ACC and KDF channel will return, because they weren't register these two functions.*/
	if (!cur_chn->bd_fifo.ops.get_free_bd_cnt)
		return CIPHER_NULL_PTR;
	if (!cur_chn->bd_fifo.ops.get_filled_bd_cnt)
		return CIPHER_NULL_PTR;

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	fifo_update_rw_idx(cur_chn);
	if(BD_TYPE_FREE == bd_type)
	{
		bd_num = (int)(*cur_chn->bd_fifo.ops.get_free_bd_cnt)(&(cur_chn->bd_fifo));
		return bd_num;
	}
	else if(BD_TYPE_CFG == bd_type)
	{
		bd_num = (int)(*cur_chn->bd_fifo.ops.get_filled_bd_cnt)(&(cur_chn->bd_fifo));
		return bd_num;
	}

	return (int)cur_chn->bd_fifo.elem_cnt;
}

int mdrv_cipher_enable(void)
{
	unsigned long flag = 0;

	if(cipher_module_ctl.clk_en)
		return MDRV_OK;

	spin_lock_irqsave(&cipher_module_ctl.clk_lock, flag);
	if(clk_enable(cipher_module_ctl.pclk))
	{
		spin_unlock_irqrestore(&cipher_module_ctl.clk_lock, flag);
		return MDRV_ERROR;
	}
	cipher_module_ctl.clk_en = 1;
	spin_unlock_irqrestore(&cipher_module_ctl.clk_lock, flag);
	return MDRV_OK;
}

int  mdrv_cipher_disable(void)
{
	unsigned long flag = 0;

	if(!cipher_module_ctl.clk_en)
		return MDRV_OK;

	spin_lock_irqsave(&cipher_module_ctl.clk_lock, flag);
	clk_disable(cipher_module_ctl.pclk);
	cipher_module_ctl.clk_en = 0;
	spin_unlock_irqrestore(&cipher_module_ctl.clk_lock, flag);
	return MDRV_OK;
}

int mdrv_cipher_chn_idle(unsigned int chn)
{
	struct cipher_chn_ctl * cur_chn = &cipher_module_ctl.cipher_chn[chn];

	if (!cipher_module_ctl.init_flag)
		return CIPHER_NOT_INIT;

	if(chn > cipher_module_ctl.chn_cnt - 1)
	{
		return CIPHER_CHECK_ERROR;
	}

	if (!(cur_chn->ops.chn_idle))
		return CIPHER_NULL_PTR;

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("ERR: fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	return ((*cur_chn->ops.chn_idle)(cur_chn));
}

static int cipher_fifo_init(struct fifo_ctl *f_ctl, enum fifo_type ftype,
													unsigned int chnid)
{
	void *f_buf;
	unsigned int elem_sz = 0;

	switch(ftype) {
		case FIFO_BDQ:
			elem_sz = sizeof(struct cipher_bd);
			break;

		case FIFO_RDQ:
			elem_sz = sizeof(struct cipher_rd);
			break;

		case FIFO_CDQ:
			elem_sz = sizeof(struct cipher_cd);
			break;

		default:
			return CIPHER_CHECK_ERROR;
	}

	(void)memcpy_s((void *)&(f_ctl->ops), sizeof(struct fifo_ops),
							(void *)&cipher_fifo_ops, sizeof(struct fifo_ops));
	f_ctl->type           = ftype;
	spin_lock_init(&(f_ctl->lock));
	f_ctl->chn_id         = chnid;
	f_ctl->elem_cnt       = fifo_elem_cnt[chnid][ftype];
	f_ctl->elem_size      = elem_sz;
	f_ctl->write_idx      = 0;
	f_ctl->read_idx       = 0;

	if (fifo_elem_cnt[chnid][ftype])
	{

#ifdef CIPHER_CACHE_ENABLE
		f_buf = osl_mem_align(OSL_CACHE_ALIGN_SIZE,
									elem_sz * fifo_elem_cnt[chnid][ftype]);
#else
		f_buf = osl_cachedma_malloc(elem_sz * fifo_elem_cnt[chnid][ftype]);
#endif
		if(NULL == f_buf){
			CIPHER_ERR_PRINT("Chnid:%d,ftype:%d,fifo malloc failed!\n", chnid,
																		ftype);
			return CIPHER_NO_MEM;
		}

		f_ctl->fifo_base = f_buf;

		/*bdq must be initialed 0, or fifo_update_rw_idx will be wrong.*/
		(void)memset_s(f_ctl->fifo_base, elem_sz * fifo_elem_cnt[chnid][ftype], 0,
									elem_sz * fifo_elem_cnt[chnid][ftype]);
	} else {
		f_ctl->fifo_base = NULL;
	}

	return CIPHER_SUCCESS;
}

static int cipher_chn_init(void)
{
	int i = 0;
	int ret = 0;
	struct cipher_chn_ctl * chn_ctl = NULL;

	for(i = 0; i < (int)cipher_module_ctl.chn_cnt; i++)
	{
		if(cipher_special_chn((unsigned int)i))
			continue;

		chn_ctl = &cipher_module_ctl.cipher_chn[i];
		(void)memset_s(chn_ctl, sizeof(struct cipher_chn_ctl), 0,
								sizeof(struct cipher_chn_ctl));

		osl_sem_init(1, &chn_ctl->chn_sem);

		/*LTE_SECURITY_CHANNEL_SRB inlucde UL_SRB and DL_SRB*/
		chn_ctl->need_purge = LTE_SECURITY_CHANNEL_SRB == i ? 1 : 0;
		chn_ctl->straight   = LTE_SECURITY_CHANNEL_DL_DRB_ACORE == i ? 1 : 0;
		chn_ctl->chn_id     = (unsigned int)i;
		(void)memcpy_s((void *)&(chn_ctl->ops), sizeof(struct chn_ops),
							(void *)&cipher_chn_ops, sizeof(struct chn_ops));

		ret  = cipher_fifo_init(&(chn_ctl->bd_fifo), FIFO_BDQ, chn_ctl->chn_id);
		ret += cipher_fifo_init(&(chn_ctl->cd_fifo), FIFO_CDQ, chn_ctl->chn_id);
		ret += cipher_fifo_init(&(chn_ctl->rd_fifo), FIFO_RDQ, chn_ctl->chn_id);
		if(ret){
			CIPHER_ERR_PRINT("cipher_fifo_init err\n");
			return CIPHER_NOT_INIT;
		}
		if(chn_ctl->straight)
		{
			cipher_addr_s psam_info;

			(void)memset_s((void *)&psam_info, sizeof(cipher_addr_s), 0,
											sizeof(cipher_addr_s));
			ret = bsp_psam_config_cipher_rd(&psam_info);
			if (ret) {
				CIPHER_ERR_PRINT("Get psam para failed!\n");
				return MDRV_ERROR;
			}

			chn_ctl->rd_fifo.fifo_base = psam_info.direct_addr;
			chn_ctl->rd_fifo.elem_cnt = psam_info.cnt;

			CIPHER_INFO("Cipher:PSAM CRDQ base addr:0x%p, RD count:%d\n",
								psam_info.direct_addr, psam_info.cnt);
		}
	}

	return MDRV_OK;
}

static void cipher_set_chn_pri(CIPHER_PRI_T *priority)
{
	priority->bits.ch0_pri = 1;
	priority->bits.ch1_pri = 0;
	priority->bits.ch2_pri = 0;
	priority->bits.ch3_pri = 2;
	priority->bits.ch5_pri = 3;
	priority->bits.ch6_pri = 1;
}

extern struct kdf_chn_ctl kdf_ctl;
void cipher_init_reg(void)
{
    unsigned int i = 0;
	u32 val = 0;
	unsigned int int_reg_num;
	struct cipher_chn_ctl * chn_ctl = NULL;
	unsigned int cipher_reg_base;
	CIPHER_PRI_T cipher_chn_pri;
#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
	unsigned int * keyram_base;
#endif

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	writel(0x3, cipher_reg_base + HI_CIPHER_CTRL_OFFSET);
	while(0x80000000 & readl(cipher_reg_base + HI_CIPHER_CTRL_OFFSET))
        ;

	if (CIPHER_CHN_NUM == cipher_module_ctl.chn_cnt) {
		int_reg_num	= CIPHER_INT_REG_NUM;
		cipher_set_chn_pri(&cipher_chn_pri);	//set priority
	} else {
		int_reg_num =  3;
		cipher_chn_pri.u32 = CIPHER_THRESHOLD;	//set flow threshold
	}
	
	writel(cipher_chn_pri.u32, cipher_reg_base + HI_CIPHER_PRI_OFFSET);
	
#ifdef HI_CIPHER_DIRECT
	if (cipher_module_ctl.fama_enable) {
		val = readl(cipher_reg_base + HI_CIPHER_DIRECT);
		val = (val & (~0x7F)) | CIPHER_DIRECT_CHN_SEL;
		writel(val , cipher_reg_base + HI_CIPHER_DIRECT);
	}
#endif

	/* If using RSR_ACC, we will restore key ram in other function. */
#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
	/*
	*restore KeyRam
	*【此段内部ram被映射为寄存器，只能按字单位写】
	*/
	/*lint -e830*/
	keyram_base =(unsigned int *)(cipher_reg_base + HI_KEY_RAM_OFFSET);
	for(i = 0; i < (int)(CIPHER_KEYRAM_SIZE / sizeof(unsigned int)); i++){
    	val = cipher_module_ctl.keyram_backup[i];
		writel(val, (unsigned long)(keyram_base + i));
	}
	/*lint +e830*/
#endif

	/* config interrupt registers */
	for(i = 0; i < int_reg_num; i++)
	{
		writel(0xFFFFFFFF, cipher_reg_base + cipher_module_ctl.reg_int_sta [i]);
		writel(intmask[i], cipher_reg_base + cipher_module_ctl.reg_int_mask[i]);
		writel(0xFFFFFFFF, cipher_reg_base + cipher_module_ctl.reg_int_msta[i]);
	}

    for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		if(cipher_special_chn(i))
			continue;
		chn_ctl = &cipher_module_ctl.cipher_chn[i];

		/*Configure BDQ*/
		writel((unsigned long)chn_ctl->bd_fifo.fifo_base, cipher_reg_base +
													CIPHER_CHNBDQ_BASE(i));
		writel(chn_ctl->bd_fifo.elem_cnt - 1, cipher_reg_base + CIPHER_CHNBDQ_SIZE(i));
		writel(0,cipher_reg_base + CIPHER_CHNBDQ_RWPTR(i));

		/*Configure RDQ*/
		writel((unsigned long)chn_ctl->rd_fifo.fifo_base, cipher_reg_base +
														CIPHER_CHNRDQ_BASE(i));
		writel(chn_ctl->rd_fifo.elem_cnt - 1,cipher_reg_base +
														CIPHER_CHNRDQ_SIZE(i));
		writel(0,cipher_reg_base + CIPHER_CHNRDQ_RWPTR(i));

		val  = (0x1U << 3) | (0x3U << 5);
		val |= (((CIPHER_IV_NUM & 0x1) << 1) | CIPHER_IV_SEL);
		writel(val, cipher_reg_base + CIPHER_CHN_CONFIG(i));
		writel(0x1, cipher_reg_base + CIPHER_CHN_ENABLE(i));
	}
    //kdf bdq
    writel((unsigned long)kdf_ctl.bd_fifo_base, cipher_reg_base + HI_CH4_BDQ_BADDR_OFFSET);
    writel(KDF_BD_NUM - 1,cipher_reg_base + HI_CH4_BDQ_SIZE_OFFSET);
    writel(0x0,cipher_reg_base+ HI_CH4_BDQ_PTR_OFFSET);
    //kdf rdq
    writel((unsigned long)kdf_ctl.rd_fifo_base, cipher_reg_base + HI_CH4_RDQ_BADDR_OFFSET);
	writel(KDF_RD_NUM - 1,cipher_reg_base + HI_CH4_RDQ_SIZE_OFFSET);
	writel(0x0,cipher_reg_base + HI_CH4_RDQ_PTR_OFFSET);

    /* 配置KDF通道config寄存器*/
	writel(0x1U << 2, cipher_reg_base + HI_CH4_CONFIG_OFFSET);
	writel(0x1, cipher_reg_base + HI_CH4_EN_OFFSET);
}

extern int bsp_kdf_init(void * base);
extern void kdf_rollback(void);
extern int acc_init(struct cipher_ctl *cipher_control);
extern void acc_rollback(void);

int cipher_set_psam(void)
{
	int ret;
	unsigned int chn;
	cipher_reg_s psam_reg_addr;
	struct cipher_chn_ctl psam_chn;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	chn = LTE_SECURITY_CHANNEL_DL_DRB_ACORE;
	psam_chn = cipher_module_ctl.cipher_chn[chn];
	psam_reg_addr.cbdq_baddr     = (unsigned long)psam_chn.bd_fifo.fifo_base;
	psam_reg_addr.cbdq_config    = (((CIPHER_IV_NUM & 0x1) << 1) | CIPHER_IV_SEL);
	psam_reg_addr.cbdq_size      = psam_chn.bd_fifo.elem_cnt;
	psam_reg_addr.cbdq_wptr_addr = cipher_reg_base + CIPHER_CHNBDQ_RWPTR(chn);
	psam_reg_addr.crdq_rptr_addr = cipher_reg_base + CIPHER_CHNRDQ_RWPTR(chn);

	ret = bsp_psam_get_cipher_bd(&psam_reg_addr);
	if (ret)
		CIPHER_ERR_PRINT("PSAM set cipher parameters failed!\n");

	return ret;
}

int cipher_para_dts(void)
{
	int ret = 0;
	const char * dts_node_name = "hisilicon,cipher";
	struct device_node * dts_node = NULL;

	dts_node = of_find_compatible_node(NULL, NULL, dts_node_name);
	if(!dts_node)
	{
		CIPHER_ERR_PRINT("Fail to finde dts node!\n");
		return CIPHER_NULL_PTR;
	}
	cipher_module_ctl.reg_virt_base = of_iomap(dts_node, 0);
	cipher_module_ctl.irq_num       = irq_of_parse_and_map(dts_node, 0);

	ret = of_property_read_u32_array(dts_node, "clkrate", &cipher_module_ctl.clkrate, 1);
	if(ret) {
		CIPHER_ERR_PRINT("Fail to get cipher clkrate!\n");
		return CIPHER_UNKNOWN_ERROR;
	}

	ret = of_property_read_u32_array(dts_node, "crg_clk_stat4", &cipher_module_ctl.crg_clk_stat4, 1);
	if(ret) {
		CIPHER_ERR_PRINT("Fail to get cipher_switch!\n");
		return CIPHER_UNKNOWN_ERROR;
	}

	ret = of_property_read_u32_array(dts_node, "acc_fifo_depth", &cipher_module_ctl.acc_fifo_depth, 1);
	if(ret) {
		CIPHER_ERR_PRINT("Fail to get acc fifo depth!\n");
	}

	return CIPHER_SUCCESS;
}

static void cipher_rollback(void)
{
	unsigned int i;
	struct cipher_chn_ctl *cur_chn = NULL;

	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		if(LTE_KEY_OPT_CHANNEL_KDF == i)
			kdf_rollback();
		else if(LTE_SECURITY_CHANNEL_UL_ACC_0 == i ||
				LTE_SECURITY_CHANNEL_UL_ACC_1 == i)
			acc_rollback();
		else {
			cur_chn = &cipher_module_ctl.cipher_chn[i];

			/*Free bd memory.*/
			if (cur_chn->bd_fifo.fifo_base)
				(void)osl_cachedma_free(cur_chn->bd_fifo.fifo_base);

			/*Free rd memory.*/
			if (cur_chn->rd_fifo.fifo_base)
				(void)osl_cachedma_free(cur_chn->rd_fifo.fifo_base);

			/*Free cd memory.*/
			if (cur_chn->cd_fifo.fifo_base)
				(void)osl_cachedma_free(cur_chn->cd_fifo.fifo_base);
		}
	}
}
static void cipher_dump_cb(void)
{
	unsigned int i;
	unsigned int ptr;
	unsigned int reg_base;

	reg_base= (unsigned int)cipher_module_ctl.reg_virt_base;
	ptr = cipher_module_ctl.dump_reg;

	if(mdrv_cipher_enable())
		CIPHER_ERR_PRINT("fail to open clk\n");

	for (i = 0; i < CIPHER_DUMP_SIZE; i += 4){
		*(unsigned int *)(ptr + i) = readl(reg_base + i);
	}
}

int cipher_om_dump_init(void)
{
	unsigned int dump = 0;

	/*Register Cipher dump memory.*/
	dump = (unsigned int)bsp_dump_register_field(DUMP_CP_CIPHER, "Cipher", 0,
													0, CIPHER_DUMP_SIZE, 0);
	if(!dump){
		CIPHER_ERR_PRINT("Fail to get dump memory!\n");
		return CIPHER_NO_MEM;
	} else {

		/*address should be an should an integral multiple of 4 bytes,
		* because registers are 32bit width.
		*/
		if(dump % sizeof(unsigned int)){
			CIPHER_ERR_PRINT("Dump address align error!\n");
			return CIPHER_CHECK_ERROR;
		} else {
			cipher_module_ctl.dump_reg = dump;
		}
	}

	/*Register dump callback function to om module*/
	if (BSP_ERROR == bsp_dump_register_hook("Cipher", cipher_dump_cb)){
		CIPHER_ERR_PRINT("Fail to register dump handler!\n");
		return CIPHER_NO_MEM;
	}

	return CIPHER_SUCCESS;
}

void cipher_clear_keyram(void)
{	
	int i;
	unsigned int cipher_reg_base;
	unsigned int *keyram_base;
	
	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	keyram_base =(unsigned int *)(cipher_reg_base + HI_KEY_RAM_OFFSET);
	
	for(i = 0; i < (int)(CIPHER_KEYRAM_SIZE / sizeof(unsigned int)); i++){
		writel(0, (unsigned long)(keyram_base + i));
	}

}

int cipher_init(void)
{
	unsigned int reg_val = 0;
	int retval;
	unsigned int cipher_reg_base;

	retval = cipher_para_dts();
	if(retval)
		return retval;

	spin_lock_init(&cipher_module_ctl.clk_lock);
	cipher_module_ctl.suspend_resume = 0;
	cipher_module_ctl.clk_en         = 0;
	cipher_module_ctl.pclk           = clk_get(NULL, "cipher_clk");
	if(IS_ERR(cipher_module_ctl.pclk))
	{
		CIPHER_ERR_PRINT("fail to get clk ptr\n");
		return MDRV_ERROR;
	}

	if(mdrv_cipher_enable())
	{
		CIPHER_ERR_PRINT("fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	retval = clk_set_rate(cipher_module_ctl.pclk, cipher_module_ctl.clkrate);
	if (retval)
		cipher_dbg_log.set_rate_err++;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	reg_val = readl(cipher_reg_base + HI_CIPHER_VERSION_OFFSET);
	if ( CIPHER_VERSION_6950 == reg_val) {
		cipher_module_ctl.chn_cnt = CIPHER_CHN_NUM;
		cipher_module_ctl.acc_chn_num = 2;
	} else if (CIPHER_VERSION_CHICAGO == reg_val ) {
		cipher_module_ctl.chn_cnt = CIPHER_CHN_NUM;
		cipher_module_ctl.acc_chn_num = 2;
		cipher_module_ctl.fama_enable = 1;
	} else {
		cipher_module_ctl.chn_cnt = CIPHER_CHN_NUM_LESS;
		cipher_module_ctl.acc_chn_num = 1;
	}

	retval  = cipher_chn_init();
	retval += bsp_kdf_init(cipher_module_ctl.reg_virt_base);
	retval += acc_init(&(cipher_module_ctl));
	if(retval)
	{
		cipher_dbg_log.alloc_failed++;
		cipher_rollback();
		return CIPHER_NOT_INIT;
	}

	(void)disable_irq(cipher_module_ctl.irq_num);
	cipher_init_reg();
	cipher_clear_keyram();	//clear keyram to 0

	(void)mdrv_cipher_disable();

	retval = cipher_set_psam();
	if (retval){
		cipher_dbg_log.set_psam_failed++;
		return CIPHER_NOT_INIT;
	}

	(void)osl_int_connect(cipher_module_ctl.irq_num, (irq_handler_t)cipher_isr, 0);
	(void)enable_irq(cipher_module_ctl.irq_num);

#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
	/* If using RSR_ACC, it doesn't use dpm. */
	if(bsp_device_pm_add(&cipher_device))
	{
		CIPHER_ERR_PRINT("fail bsp_device_pm_add\n");
		return CIPHER_UNKNOWN_ERROR;
	}
#elif (defined(CONFIG_RSR_ACC))
	cipher_rsr_bd.reg_addr = (u32 *)((u32)cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET);
	cipher_rsr_bd.reg_num = CIPHER_KEYRAM_SIZE / sizeof(unsigned int);
	if (bsp_rsracc_register(&cipher_rsr_bd, 1)) {
		CIPHER_ERR_PRINT("Register rsr acc failed!\n");
		return CIPHER_UNKNOWN_ERROR;
	}
#endif
	
	retval = cipher_om_dump_init();
	if(retval)
		cipher_dbg_log.dump_init_failed = 1;

	CIPHER_ERR_PRINT("cipher init ok\n");
	cipher_module_ctl.init_flag = 1;

	(void)bsp_register_master_idle(CIPHER_IDLE, ccpu_reset_cipher_and_wait_idle);

#ifdef CIPHER_DEBUG_BD_CD_QUEUE
	cipher_module_ctl.bd_cd_idx =
				(struct cipher_debug_bd_cd *)osl_cachedma_malloc(
				CIPHER_BCD_CNT * sizeof(struct cipher_debug_bd_cd));

	(void)memset_s((void *)cipher_module_ctl.bd_cd_idx,
				CIPHER_BCD_CNT * sizeof(struct cipher_debug_bd_cd), 0,
				CIPHER_BCD_CNT * sizeof(struct cipher_debug_bd_cd));

	cipher_module_ctl.idx_dbg_chn = CIPHER_SECURITY_CHANNEL_3;
	cipher_module_ctl.cfg_num = 0;
#endif

	return CIPHER_SUCCESS;
}

#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
int cipher_reg_backup(void)
{
	unsigned int i       = 0;
	u32 reg_val = 0;
	unsigned int * keyram_base;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	keyram_base = (unsigned int *)(cipher_reg_base + HI_KEY_RAM_OFFSET);

	/*Check whether cipher is busy*/
	reg_val = readl(cipher_reg_base + HI_CIPHER_CTRL_OFFSET);
	if(reg_val & (0x1U << 31))
		return CIPHER_PERR_BUSY;

	/*Check if BDQ or RDQ  is empty to backup registers*/
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		reg_val = readl(cipher_reg_base + CIPHER_CHNBDQ_RWPTR(i));
		if((reg_val & 0x3FF) != ((reg_val >> 16) & 0x3FF))
			return CIPHER_PERR_BDNOTEMPTY;

		reg_val = readl(cipher_reg_base + CIPHER_CHNRDQ_RWPTR(i));
		if((reg_val & 0x3FF) != ((reg_val >> 16) & 0x3FF))
			return CIPHER_PERR_RDNOTEMPTY;
	}

	/* Disable channels */
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++){
		reg_val = readl(cipher_reg_base + CIPHER_CHN_ENABLE(i));
		writel(reg_val & (~0x1U), cipher_reg_base + CIPHER_CHN_ENABLE(i));
	}

	for(i = 0; i < (int)(CIPHER_KEYRAM_SIZE / sizeof(u32)); i++)
	{
		reg_val = readl((unsigned long)(keyram_base + i));
		cipher_module_ctl.keyram_backup[i] = reg_val;
	}

	return CIPHER_SUCCESS;
}

int cipher_suspend(struct dpm_device *dev)
{
	int ret;

	if(mdrv_cipher_enable())
	{
		CIPHER_INFO("CIPHER:fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	ret = cipher_reg_backup();
	if (ret) {
		cipher_dbg_log.suspend_failed++;
		return ret;
	}

	(void)mdrv_cipher_disable();
	return MDRV_OK;
}

int cipher_resume(struct dpm_device *dev)
{
	unsigned int i = 0;
	struct cipher_chn_ctl * cur_chn = NULL;

	if(mdrv_cipher_enable())
	{
		CIPHER_INFO("CIPHER:fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}
	cipher_init_reg();
	(void)mdrv_cipher_disable();
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		if(cipher_special_chn(i))
			continue;
		cur_chn = &cipher_module_ctl.cipher_chn[i];
		(void)(*cur_chn->bd_fifo.ops.rst_rwidx)(&(cur_chn->bd_fifo));
		(void)(*cur_chn->rd_fifo.ops.rst_rwidx)(&(cur_chn->rd_fifo));
		(void)(*cur_chn->cd_fifo.ops.rst_rwidx)(&(cur_chn->cd_fifo));
		cur_chn->pre_check_bd_idx = 0;
	}
	kdf_ctl.bd_w_idx = kdf_ctl.rd_r_idx = 0;
	(void)bsp_psam_cipher_ch_srst(1);

    return MDRV_OK;
}
#elif defined(CONFIG_RSR_ACC)

int cipher_prepare_backup(void)
{
	unsigned int i       = 0;
	u32 reg_val = 0;
	unsigned int cipher_reg_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	
	/*Check whether cipher is busy*/
	reg_val = readl(cipher_reg_base + HI_CIPHER_CTRL_OFFSET);
	if(reg_val & (0x1U << 31))
		return CIPHER_PERR_BUSY;

	/*Check if BDQ or RDQ  is empty to backup registers*/
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		reg_val = readl(cipher_reg_base + CIPHER_CHNBDQ_RWPTR(i));
		if((reg_val & 0x3FF) != ((reg_val >> 16) & 0x3FF))
			return CIPHER_PERR_BDNOTEMPTY;

		reg_val = readl(cipher_reg_base + CIPHER_CHNRDQ_RWPTR(i));
		if((reg_val & 0x3FF) != ((reg_val >> 16) & 0x3FF))
			return CIPHER_PERR_RDNOTEMPTY;
	}

	/* Disable channels */
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++){
		reg_val = readl(cipher_reg_base + CIPHER_CHN_ENABLE(i));
		writel(reg_val & (~0x1U), cipher_reg_base + CIPHER_CHN_ENABLE(i));
	}

	return CIPHER_SUCCESS;
}

int cipher_suspend_begin(rsr_acc_description *bd_descri)
{
	int ret;

	if(mdrv_cipher_enable())
	{
		CIPHER_INFO("CIPHER:fail to open clk\n");
		return CIPHER_ENABLE_FAILED;
	}

	ret = cipher_prepare_backup();//cipher_reg_backup();
	if (ret) {
		cipher_dbg_log.suspend_failed++;
		return ret;
	}
	return MDRV_OK;
}
void cipher_suspend_end(rsr_acc_description *bd_descri)
{
	(void)mdrv_cipher_disable();
}

void cipher_resume_begin(rsr_acc_description *bd_descri)
{
	if(mdrv_cipher_enable())
	{
		CIPHER_INFO("CIPHER:fail to open clk\n");
		return;
	}
	cipher_init_reg();
}

void cipher_resume_end(rsr_acc_description *bd_descri)
{
	unsigned int cipher_reg_base;
	unsigned int i;
	unsigned int reg_val;
	struct cipher_chn_ctl * cur_chn = NULL;

	for(i = 0; i < cipher_module_ctl.chn_cnt; i++)
	{
		if(cipher_special_chn(i))
			continue;
		cur_chn = &cipher_module_ctl.cipher_chn[i];
		(void)(*cur_chn->bd_fifo.ops.rst_rwidx)(&(cur_chn->bd_fifo));
		(void)(*cur_chn->rd_fifo.ops.rst_rwidx)(&(cur_chn->rd_fifo));
		(void)(*cur_chn->cd_fifo.ops.rst_rwidx)(&(cur_chn->cd_fifo));
		cur_chn->pre_check_bd_idx = 0;
	}
	kdf_ctl.bd_w_idx = kdf_ctl.rd_r_idx = 0;
	(void)bsp_psam_cipher_ch_srst(1);

	/* Enable channels */
	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	for(i = 0; i < cipher_module_ctl.chn_cnt; i++){
		reg_val = readl(cipher_reg_base + CIPHER_CHN_ENABLE(i));
		writel(reg_val | (0x1U), cipher_reg_base + CIPHER_CHN_ENABLE(i));
	}

	(void)mdrv_cipher_disable();
}
#endif
int mdrv_cipher_get_chn_status(unsigned int chn_id)
{
	int bd_status;
	unsigned int rd_status;
	struct fifo_ctl *rd_fifo;
	struct cipher_chn_ctl *cur_chn;
	int ret = CIPHER_CHN_BDINUSE_RDINUSE;

	rd_fifo = &(cipher_module_ctl.cipher_chn[chn_id].rd_fifo);
	cur_chn = &(cipher_module_ctl.cipher_chn[chn_id]);

	bd_status = mdrv_cipher_get_bd_num(chn_id, BD_TYPE_CFG);

	/* update rd write index */
	if (!(cur_chn->straight)) {
		unsigned int cipher_reg_base;
		unsigned int w_ptr;

		cipher_reg_base= (int)cipher_module_ctl.reg_virt_base;
		w_ptr = readl(cipher_reg_base + CIPHER_CHNRDQ_RWPTR(chn_id));
		w_ptr = (w_ptr & CIPHER_RW_MASK);

		rd_fifo->write_idx = w_ptr;
	} else {
		return CIPHER_INVALID_CHN;
	}

	rd_status = (rd_fifo->elem_cnt + rd_fifo->write_idx - rd_fifo->read_idx) % rd_fifo->elem_cnt;

	if ((bd_status > 0) && (rd_status > 0)) {
		ret =  CIPHER_CHN_BDINUSE_RDINUSE;
	} else if ((bd_status > 0) && (rd_status == 0)) {
		ret = CIPHER_CHN_BDINUSE_RDEMPTY;
	} else if ((bd_status == 0) && (rd_status > 0)) {
		ret = CIPHER_CHN_BDEMPTY_RDINUSE;
	} else if ((bd_status == 0) && (rd_status == 0)) {
		ret = CIPHER_CHN_BDEMPTY_RDEMPTY;
	} else {
		ret = bd_status;
	}

	return ret;
}


void cipher_help(void)
{
	CIPHER_INFO("cipher_status(ctl)\n");
	CIPHER_INFO("ctl=0:main info,ctl=1:all info\n");
	CIPHER_INFO("cipher_show_channel(chn_id)\n");
	CIPHER_INFO("cipher_show_keyram(void)\n");

#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
	CIPHER_INFO("cipher_show_keyram_backup(void)\n");
#endif

	CIPHER_INFO("acc_status(void)\n");
}

/* control 0:no update, 1:update  */
void cipher_show_channel(unsigned int chn_id, int control)
{
	unsigned int cipher_reg_base;
	unsigned int cfg_bd, invalid_bd;
	struct cipher_chn_ctl *cur_chn;
	struct fifo_ctl  *cdfifo;
	struct fifo_ctl  *bdfifo;
	struct fifo_ctl  *rdfifo;

	if (control) {
		cipher_update_all_chn();
	}

	cur_chn = &(cipher_module_ctl.cipher_chn[chn_id]);
	cdfifo = &(cur_chn->cd_fifo);
	bdfifo = &(cur_chn->bd_fifo);
	rdfifo = &(cur_chn->rd_fifo);
	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	(void)mdrv_cipher_enable();

	cfg_bd = readl(cipher_reg_base + 0xA0 + 0x80 * chn_id);
	invalid_bd = readl(cipher_reg_base + 0xA4 + 0x80 * chn_id);

	CIPHER_INFO("********chn%d begin********\n", chn_id);
	CIPHER_INFO("cfg bd:%d\n", cfg_bd);
	CIPHER_INFO("invalid bd:%d\n", invalid_bd);
	CIPHER_INFO("bdq full:%d\n", cipher_dbg_log.bdq_full_times[chn_id]);
	CIPHER_INFO("cdq full:%d\n", cipher_dbg_log.cdq_full_times[chn_id]);
	CIPHER_INFO("reset:%d\n", cipher_dbg_log.chn_rst_times[chn_id]);
	CIPHER_INFO("bdset:%d\n", cipher_dbg_log.chn_bdset_time[chn_id]);
	CIPHER_INFO("rd empty:%d\n",cipher_dbg_log.rdq_empty_cnt[chn_id]);
	CIPHER_INFO("rd int chk err:%d\n", cipher_dbg_log.rd_int_chk_err[chn_id]);
	CIPHER_INFO("rd len chk err:%d\n", cipher_dbg_log.rd_len_chk_err[chn_id]);
	CIPHER_INFO("rd invalid:%d\n", cipher_dbg_log.rd_invalid[chn_id]);
	CIPHER_INFO("bdptr:0x%08X\n", readl(cipher_reg_base + CIPHER_CHNBDQ_RWPTR(chn_id)));
	CIPHER_INFO("rdptr:0x%08X\n", readl(cipher_reg_base + CIPHER_CHNRDQ_RWPTR(chn_id)));

	if(!cipher_special_chn(chn_id))
	{
		CIPHER_INFO("cd widx:%d ridx:%d\n", cdfifo->write_idx, cdfifo->read_idx);
		CIPHER_INFO("bd widx:%d ridx:%d\n", bdfifo->write_idx, bdfifo->read_idx);

		if (!(cur_chn->straight)) {
			CIPHER_INFO("rd widx:%d ridx:%d\n", rdfifo->write_idx, rdfifo->read_idx);
		}
	}

	CIPHER_INFO("********chn%d end**********\n", chn_id);
}

void cipher_print_hex(unsigned int *data, unsigned int len)
{
	unsigned int i;
	for(i=0; i< len / 4; i++ ) {
		if((i+1)%4 == 0 || i==((len/4)-1))
			CIPHER_INFO("0x%08x\n", *(data + i));
		else
			CIPHER_INFO("0x%08x\t", *(data + i));
		if((i+1)%0x40)
			(void)osl_task_delay(1);
	}
}

void cipher_show_keyram(void)
{
	unsigned int cipher_reg_base;
	unsigned int *keyram_base;

	cipher_reg_base = (unsigned int)cipher_module_ctl.reg_virt_base;
	keyram_base = (unsigned int *)(cipher_reg_base + HI_KEY_RAM_OFFSET);

	cipher_print_hex(keyram_base, CIPHER_KEYRAM_SIZE);
}
#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
void cipher_show_keyram_backup(void)
{
	unsigned int *keyram_bak;

	keyram_bak = cipher_module_ctl.keyram_backup;
	cipher_print_hex(keyram_bak, CIPHER_KEYRAM_SIZE);
}
#endif
/*
 *****Input parameters,control=0:main info, control=1:main info and keyram.
*/
void cipher_status(unsigned int control)
{
	unsigned int chn_id;

	for(chn_id = 0;chn_id < cipher_module_ctl.chn_cnt; chn_id++)
	{
		cipher_show_channel(chn_id, 0);
	}

	if(control)
	{
		CIPHER_INFO("==========cipher keyram==========\n");
		cipher_show_keyram();

#if (defined(CONFIG_CCORE_PM) && (!defined(CONFIG_RSR_ACC)))
		CIPHER_INFO("==========cipher keyram backup==========\n");
		cipher_show_keyram_backup();
#endif
	}

	CIPHER_INFO("set_rate_err    : %d\n", cipher_dbg_log.set_rate_err);
	CIPHER_INFO("alloc_failed    : %d\n", cipher_dbg_log.alloc_failed);
	CIPHER_INFO("set_psam_failed : %d\n", cipher_dbg_log.set_psam_failed);
	CIPHER_INFO("dump_init_failed: %d\n", cipher_dbg_log.dump_init_failed);
}

