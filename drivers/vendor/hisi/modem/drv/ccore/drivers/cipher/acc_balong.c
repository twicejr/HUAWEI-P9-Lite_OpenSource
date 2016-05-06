/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  acc_balong.c
*
*   作    者 :  w00228729
*
*   描    述 :  完成组包加速功能
*
*   修改记录 :  2013年03月12日  v1.00  w00228729 创建
*************************************************************************/
#include <string.h>
#include "securec.h"
#include <osl_bio.h>
#include <osl_malloc.h>
#include <osl_cache.h>
#include <mdrv_cipher.h>
#include <bsp_om.h>
#include "cipher_balong.h"
#include "acc_balong.h"

struct acc_chn_ctl acc_ctl = {
         .acc_chn_num  = 1,
		 .fifo_depth   = 200,
	     .chn_enum     = {CIPHER_SECURITY_CHANNEL_0, CIPHER_SECURITY_CHANNEL_6},
                             };

struct acc_dbg_ctl acc_info = {0};



static struct acc_fifo_ctl *acc_get_fctl(unsigned int fifo_base)
{	
	return (struct acc_fifo_ctl *)(fifo_base - sizeof(struct acc_fifo_ctl));
}


void acc_rollback(void)
{
	unsigned int i;
	struct acc_fifo_ctl *f_ctl;
	
	for(i = 0; i < ACC_FIFO_NUM; i++)
	{
		f_ctl = acc_get_fctl((unsigned int)acc_ctl.fifo_base[i]);
		if (f_ctl) {
			(void)osl_cachedma_free((void *)f_ctl);
		}
	}
}

int acc_init(struct cipher_ctl *cipher_control)
{
	int i = 0;
	struct acc_fifo_ctl *f_ctl;
	unsigned int bdq_size;
	unsigned int fifo_size;

	if(cipher_control->acc_fifo_depth) {
		acc_ctl.fifo_depth = cipher_control->acc_fifo_depth;
	}
	
	bdq_size = acc_ctl.fifo_depth * sizeof(struct acc_bd);
	fifo_size = bdq_size + sizeof(struct acc_fifo_ctl);
	
	for(i = 0; i < ACC_FIFO_NUM; i++)
	{
		f_ctl = (struct acc_fifo_ctl *)osl_cachedma_malloc(fifo_size);
		if (!f_ctl)
			return CIPHER_NO_MEM;
		
		acc_ctl.fifo_base[i] = (void *)(f_ctl + 1);

		f_ctl->cfg_bd_idx = 0;
		f_ctl->status = ACC_STAT_IDLE;
		f_ctl->acc_chn_id = 0xFFFFFFFF;
		f_ctl->fifo_id = (unsigned int)i;

	}
	acc_ctl.reg_base    = cipher_control->reg_virt_base;
	acc_ctl.acc_chn_num = cipher_control->acc_chn_num;

	return CIPHER_SUCCESS;
}

void acc_disable_aes_opt_bypass(void)
{
	unsigned int reg;
	reg = readl((unsigned int)acc_ctl.reg_base + CIPHER_TEST_REG(1));
	reg &= ~0x1;
	writel(reg, (unsigned int)acc_ctl.reg_base + CIPHER_TEST_REG(1));
	
}

void acc_enable_aes_opt_bypass(void)
{
	unsigned int reg;
	reg = readl((unsigned int)acc_ctl.reg_base + CIPHER_TEST_REG(1));
	reg |= 0x1;
	writel(reg, (unsigned int)acc_ctl.reg_base + CIPHER_TEST_REG(1));
}

void acc_enable_bd_done_int(void)
{
	unsigned int reg_mask;
	
	if(mdrv_cipher_enable()){
		ACC_INFOR_PRINT("CIPHER:fail to open clk\n");
		return;
	}
	reg_mask = readl((unsigned int)acc_ctl.reg_base + CIPHER_INT0_MASK);
	reg_mask &= ~(1UL << 3);
	writel(reg_mask, (unsigned int)acc_ctl.reg_base + CIPHER_INT0_MASK);
}

unsigned int mdrv_acc_get_bdq_addr(void)
{
	int i;
	int j;
	void * sel_fifo = NULL;
	unsigned int chn_busy;
	unsigned int reg_base;
	struct acc_fifo_ctl *f_ctl = NULL;

	if(mdrv_cipher_enable())
	{
		ACC_ERROR_PRINT("CIPHER:fail to open clk\n");
		return CIPHER_UNKNOWN_ERROR;
	}
	
	reg_base = (unsigned int)acc_ctl.reg_base;
	for(i = 0; i < (int)acc_ctl.acc_chn_num; i++)
	{
		chn_busy = readl(reg_base + CIPHER_CHN_ENABLE(acc_ctl.chn_enum[i]));
		chn_busy &= CHN_STATBIT;
		if(!chn_busy)
			continue;
		
		for(j = 0; j < ACC_FIFO_NUM; j++)
		{
			f_ctl = acc_get_fctl((unsigned int )acc_ctl.fifo_base[j]);
			if((acc_ctl.chn_enum[i] == f_ctl->acc_chn_id) &&
				(ACC_STAT_WORK == f_ctl->status))
				f_ctl->status = ACC_STAT_IDLE;
		}
	}

	/*第一遍循环，寻找ACC_STAT_IDLE状态FIFO*/
	for(i = 0; i < ACC_FIFO_NUM; i++)
	{
		f_ctl = acc_get_fctl((unsigned int )acc_ctl.fifo_base[i]);
		if(ACC_STAT_IDLE == f_ctl->status)
		{
			sel_fifo = acc_ctl.fifo_base[i];
			/*lint -e801*/
			goto GET_FIFO_ADDR_EXIT;
			/*lint +e801*/
		}
	}
	/*第二遍循环，寻找ACC_STAT_CFG状态FIFO*/
	for(i = 0; i < ACC_FIFO_NUM; i++)
	{
		f_ctl = acc_get_fctl((unsigned int )acc_ctl.fifo_base[i]);
		if(ACC_STAT_CFG == f_ctl->status)
		{
			sel_fifo = acc_ctl.fifo_base[i];
			/*lint -e801*/
			goto GET_FIFO_ADDR_EXIT;
			/*lint +e801*/
		}
	}

	if (NULL == sel_fifo)
	{
		ACC_ERROR_PRINT(ACC_ALL_FIFO_WORK);
		return (unsigned int)NULL;
	}

GET_FIFO_ADDR_EXIT:
	f_ctl->cfg_bd_idx = 0;
	f_ctl->acc_chn_id = 0xFFFFFFFF;
	//st_acc_chx_mgr.acc_debug.get_fifo_times++;

	return (unsigned int)sel_fifo;
}

int mdrv_acc_cipher(unsigned int fifo_addr, ACC_SINGLE_CFG_S *pstCfg)
{
    struct acc_bd 		*cur_bd   = NULL;
	struct acc_fifo_ctl *f_ctl = NULL;

	if(!fifo_addr)
	{
		acc_info.dma_fifo_null++;
		return CIPHER_NULL_PTR;
	}
	
	f_ctl = acc_get_fctl(fifo_addr);
	
	if(f_ctl->cfg_bd_idx >= (acc_ctl.fifo_depth - 1))
	{
		acc_info.drop_pak_times++;
		return CIPHER_FIFO_FULL;
	}

	if((f_ctl->status != ACC_STAT_IDLE) && (f_ctl->status != ACC_STAT_CFG))
	{
		return CIPHER_CHECK_ERROR;
	}

	cur_bd = (struct acc_bd *)fifo_addr + f_ctl->cfg_bd_idx;
	(void)memset_s(cur_bd, sizeof(struct acc_bd), 0, sizeof(struct acc_bd));

	cur_bd->cfg= ((pstCfg->stAlgKeyInfo.u32KeyIndexSec             << 20) |
		           (pstCfg->u32AppdHeaderLen                        << 18) |
		           (pstCfg->u32HeaderLen                            << 16) |
		           (0x1U                                            << 12) |
		           (pstCfg->stAlgKeyInfo.enAlgSecurity              <<  4) |
		           ((pstCfg->stAlgKeyInfo.enAlgSecurity ? 0x1U : 0) <<  1));
	cur_bd->ptr_attr_ilen = pstCfg->u32BlockLen;
	cur_bd->offset_olen   = pstCfg->u32OutLen;
	if(pstCfg->u32Offset || ((pstCfg->u32OutLen < pstCfg->u32BlockLen) && pstCfg->u32OutLen))
	{
		cur_bd->ptr_attr_ilen  |= (0x1U << 19);
		cur_bd->offset_olen    |= ((pstCfg->u32Offset & 0xFFFF) << 16);
	}
	cur_bd->iptr_pad = (u32)pstCfg->pInMemMgr;
	cur_bd->optr     = (u32)pstCfg->pOutMemMgr;
	cur_bd->aph      = ((pstCfg->u32BearId << 27) |
		                ((pstCfg->u32Aph << ((0x3 - pstCfg->u32AppdHeaderLen) << 0x3)) & 0x00FFFFFF));
	cur_bd->count    = pstCfg->u32Count;

	f_ctl->status      = ACC_STAT_CFG;
	f_ctl->cfg_bd_idx += 1;
	//st_acc_chx_mgr.acc_debug.cfg_dma_times++;

	return CIPHER_SUCCESS;
}

int mdrv_acc_dma(unsigned int fifo_addr, ACC_SINGLE_CFG_S *pstCfg)
{
    struct acc_bd *cur_bd   = NULL;
	struct acc_fifo_ctl *f_ctl = NULL;

	if(!fifo_addr)
	{
		acc_info.dma_fifo_null++;
		return CIPHER_NULL_PTR;
	}
	
	f_ctl = acc_get_fctl(fifo_addr);

	if(f_ctl->cfg_bd_idx >= (acc_ctl.fifo_depth - 1))
	{
		//st_acc_chx_mgr.acc_debug.drop_pak_times++;
		ACC_ERROR_PRINT(CIPHER_FIFO_FULL);
		return CIPHER_FIFO_FULL;
	}

	cur_bd = (struct acc_bd *)fifo_addr + f_ctl->cfg_bd_idx;
	(void)memset_s(cur_bd, sizeof(*cur_bd), 0, sizeof(struct acc_bd));
	cur_bd->ptr_attr_ilen = pstCfg->u32BlockLen;
	cur_bd->iptr_pad      = (u32)pstCfg->pInMemMgr;
	cur_bd->optr          = (u32)pstCfg->pOutMemMgr;

	f_ctl->status      = ACC_STAT_CFG;
	f_ctl->cfg_bd_idx += 1;
	//st_acc_chx_mgr.acc_debug.cfg_dma_times++;

	return 0;
}

int mdrv_acc_get_status(unsigned int chn)
{
	unsigned int chn_busy = 0;
	int i;
    int id = -1;
    int ret;
    struct acc_fifo_ctl * f_ctl = NULL;

	/* Channel check, and get the chn_enum order. */
	switch (chn) {
		case CIPHER_SECURITY_CHANNEL_0:
       		id = 0;
       		break;

		case CIPHER_SECURITY_CHANNEL_6:
			if (acc_ctl.acc_chn_num != 2) {
				/*If chn_id is Channel 6, it means new cipher.
				 *and new cipher has 2 channels, if not, return error.
				 */
				return CIPHER_CHECK_ERROR;

			} else {
				id = 1;
				break;
			}
			
		default:
			return CIPHER_INVALID_CHN;
	}

	if(mdrv_cipher_enable())
	{
		ACC_INFOR_PRINT("CIPHER:fail to open clk\n");
		return CIPHER_UNKNOWN_ERROR;
	}
	chn_busy = readl((unsigned int)acc_ctl.reg_base + CIPHER_CHN_ENABLE(chn));
	chn_busy = chn_busy >> 30;

	/* recycle the acc buffer */
	ret = chn_busy & 0x1U;
	if (ret) {
		for(i = 0; i < ACC_FIFO_NUM; i++){
			f_ctl = acc_get_fctl((unsigned int )acc_ctl.fifo_base[i]);
		if((acc_ctl.chn_enum[id] == f_ctl->acc_chn_id) &&
		  (ACC_STAT_WORK == f_ctl->status))
  				f_ctl->status = ACC_STAT_IDLE;
		}
	}

	return ret;
}

int mdrv_acc_enable(unsigned int chn, unsigned int fifo_addr)
{
	struct acc_bd * last_bd = NULL;
	struct acc_fifo_ctl *f_ctl = NULL;
	unsigned int reg_val = 0;
	unsigned int reg_base;

	if(!fifo_addr)
	{
		return CIPHER_NULL_PTR;
	}

	f_ctl = acc_get_fctl(fifo_addr);
	reg_base = (unsigned int)acc_ctl.reg_base;
	
	/*No bd configurated,return it.*/
	if (f_ctl->cfg_bd_idx < 1)
	{
		return CIPHER_CHECK_ERROR;
	}
	
	if(mdrv_cipher_enable())
	{
		ACC_INFOR_PRINT("CIPHER:fail to open clk\n");
		return CIPHER_UNKNOWN_ERROR;
	}
	reg_val = readl(reg_base + CIPHER_CHN_ENABLE(chn));
	writel(reg_val & CHN_PACK_DEN_EN, reg_base + CIPHER_CHN_ENABLE(chn));

	reg_val = readl(reg_base + CIPHER_CHN_CONFIG(chn));
	writel(reg_val | CHN_CFGUSR, reg_base + CIPHER_CHN_CONFIG(chn));

	reg_val = readl(reg_base + CIPHER_CHN_RESET(chn));
	writel(reg_val | CHN_BDRESET, reg_base + CIPHER_CHN_RESET(chn));

	writel((unsigned)fifo_addr, reg_base + CIPHER_CHNBDQ_BASE(chn));
	writel(acc_ctl.fifo_depth - 1, reg_base + CIPHER_CHNBDQ_SIZE(chn));

	f_ctl->status = ACC_STAT_WORK;
	f_ctl->acc_chn_id = chn;

	last_bd = (struct acc_bd *)fifo_addr + f_ctl->cfg_bd_idx - 1;
	writel_relaxed(last_bd->cfg | (0x1U << 13), (unsigned int)&last_bd->cfg);
	//osl_cache_flush(OSL_DATA_CACHE,(void*)u32BdFifoAddr, fifo_ctl->cfg_bd_idx * sizeof(struct acc_bd));

	writel(f_ctl->cfg_bd_idx, reg_base + CIPHER_CHNBDQ_RWPTR(chn));

	reg_val = readl(reg_base + CIPHER_CHN_ENABLE(chn));
	writel(reg_val | CHN_ENBITS, reg_base + CIPHER_CHN_ENABLE(chn));

	//st_acc_chx_mgr.acc_debug.enable_times++;
	return 0;
}

void acc_status(void)
{
	unsigned int i;
	struct acc_fifo_ctl *f_ctl;

	for(i = 0; i < ACC_FIFO_NUM; i++)
	{
		f_ctl = acc_get_fctl((unsigned int)acc_ctl.fifo_base[i]);
		ACC_INFOR_PRINT("fifo base       : 0x%p\n", acc_ctl.fifo_base[i]);
		ACC_INFOR_PRINT("fifo status     : %d\n", f_ctl->status);
		ACC_INFOR_PRINT("fifo fifo_id    : %d\n", f_ctl->fifo_id);
		ACC_INFOR_PRINT("fifo cfg_bd_idx : %d\n", f_ctl->cfg_bd_idx);
		ACC_INFOR_PRINT("fifo acc_chn_id : %d\n", f_ctl->acc_chn_id);
	}
	
	ACC_INFOR_PRINT("ACC dropped packet:   %d\n", acc_info.drop_pak_times);
	ACC_INFOR_PRINT("ACC dma fifo null:    %d\n", acc_info.dma_fifo_null);
	ACC_INFOR_PRINT("ACC cipher fifo null: %d\n", acc_info.cipher_fifo_null);
}
