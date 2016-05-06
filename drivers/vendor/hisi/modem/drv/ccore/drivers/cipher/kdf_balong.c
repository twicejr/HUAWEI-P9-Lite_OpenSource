#include <string.h>
#include <hi_cipher.h>
#include "securec.h"
#include <osl_malloc.h>
#include <osl_cache.h>
#include <mdrv_public.h>
#include <mdrv_cipher.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include "kdf_balong.h"

//#define KDF_CACHE_ENABLE
#define KDF_ERR_PRINT(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "[KDF]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__)

struct kdf_chn_ctl kdf_ctl = {.bd_fifo_base = NULL,
                              .rd_fifo_base = NULL,
                              .key_s_buf    = NULL,
                              .bd_w_idx     = 0,
                              .rd_r_idx     = 0,
                              .reg_base     = NULL
                             };
static unsigned char key_length_table[CIPHER_KEY_LEN_BUTTOM] = {16, 24, 32};

void kdf_rollback(void)
{
	if (kdf_ctl.bd_fifo_base) 
 		(void)osl_cachedma_free((void *)kdf_ctl.bd_fifo_base);	

	if (kdf_ctl.rd_fifo_base)
		(void)osl_cachedma_free((void *)kdf_ctl.rd_fifo_base);		

	if (kdf_ctl.key_s_buf)
		(void)osl_cachedma_free((void *)kdf_ctl.key_s_buf);			
}


int bsp_kdf_init(void * base)
{
	unsigned int bdq_size       = KDF_BD_NUM * sizeof(struct kdf_bd);
	unsigned int rdq_size       = KDF_RD_NUM * sizeof(struct kdf_rd);
	unsigned int sha_key_s_size = KDF_SHA_KEY_MAX_LEN + KDF_SHA_S_MAX_LEN;

	osl_sem_init(1, &kdf_ctl.kdf_sem);

#ifdef KDF_CACHE_ENABLE
	kdf_ctl.bd_fifo_base = (struct kdf_bd *)osl_mem_align(OSL_CACHE_ALIGN_SIZE, 
																	bdq_size);
	kdf_ctl.rd_fifo_base = (struct kdf_rd *)osl_mem_align(OSL_CACHE_ALIGN_SIZE, 
																	rdq_size);
	kdf_ctl.key_s_buf    = osl_mem_align(OSL_CACHE_ALIGN_SIZE, sha_key_s_size);
#else
	kdf_ctl.bd_fifo_base = (struct kdf_bd *)osl_cachedma_malloc(bdq_size);
	kdf_ctl.rd_fifo_base = (struct kdf_rd *)osl_cachedma_malloc(rdq_size);
	kdf_ctl.key_s_buf    = osl_cachedma_malloc(sha_key_s_size);
#endif

	if(!kdf_ctl.bd_fifo_base || !kdf_ctl.rd_fifo_base || !kdf_ctl.key_s_buf)
	{
		KDF_ERR_PRINT("fail to malloc memory\n");
		return CIPHER_NULL_PTR;
	}

	kdf_ctl.reg_base = base;
	
	return CIPHER_SUCCESS;
}

void kdf_bd_cfg(KDF_OPS kdf_op, KEY_CONFIG_INFO_S * pstKeyCfgInfo, 
			S_CONFIG_INFO_S * pstSCfgInfo,unsigned int u32DestIndex, 
										unsigned int len, void * addr)
{
	struct kdf_bd * cur_addr = kdf_ctl.bd_fifo_base + kdf_ctl.bd_w_idx;

	cur_addr->cfg = (kdf_op                        &   0x3)   <<  0 |
	                (pstKeyCfgInfo->enShaKeySource &   0x3)   <<  2 |
	                (pstSCfgInfo->enShaSSource     &   0x1)   <<  4 |
	                (0x0U                          &   0x1)   <<  6 |
	                (pstKeyCfgInfo->u32ShaKeyIndex &   0xF)   <<  7 |
	                (pstSCfgInfo->u32ShaSIndex     &   0xF)   << 11 |
	                (len                           & 0x1FF)   << 15 |
	                (u32DestIndex                  &   0xF)   << 24 |
	                (0x1U                          &   0x1)   << 28;
	cur_addr->addr = (u32)addr;
#ifdef KDF_CACHE_ENABLE
	(void)osl_cache_flush(OSL_DATA_CACHE,(void*)cur_addr, sizeof(struct kdf_bd));
#endif
}

static int kdf_wait_bd_done(void)
{
	struct kdf_rd * cur_rd  = kdf_ctl.rd_fifo_base + kdf_ctl.rd_r_idx;
	int             ret     = 0;
	u32             reg_val = 0;
	unsigned int	bd_idx;
	unsigned int 	kdf_chn_status;
	unsigned int 	bd_widx;
	unsigned int	bd_ridx;
	unsigned int 	time_out = 0;
	unsigned int	time_record = 0;
	unsigned int	kdf_reg_base;

#ifdef KDF_CACHE_ENABLE
	osl_cache_flush(OSL_DATA_CACHE, cur_rd, sizeof(struct kdf_rd));
	osl_cache_invalid(OSL_DATA_CACHE, cur_rd, sizeof(struct kdf_rd));
#endif

	kdf_reg_base = (unsigned int)kdf_ctl.reg_base;
	kdf_ctl.bd_w_idx = (kdf_ctl.bd_w_idx + 1) & (KDF_BD_NUM - 1);
	writel(kdf_ctl.bd_w_idx, kdf_reg_base + HI_CH4_BDQ_PTR_OFFSET);

	time_record = bsp_get_slice_value();
	do{
		time_out = get_timer_slice_delta(time_record, bsp_get_slice_value());
		if (time_out > TEN_MS) {
			kdf_ctl.kdf_dbg.timeout++;
			return CIPHER_TIME_OUT;
		}

		/* wait for this bd to be fectched */
		bd_idx = readl(kdf_reg_base + HI_CH4_BDQ_PTR_OFFSET);
		bd_widx = bd_idx & KDF_IDX_MASK;
		bd_ridx = (bd_idx >> KDF_RPTR_OFFSET) & KDF_IDX_MASK;

		/* wait for this bd being compeleted */
		reg_val = readl(kdf_reg_base + HI_CH4_EN_OFFSET);
		kdf_chn_status = KDF_CH_BUSY & reg_val;
	}while(kdf_chn_status || (bd_widx != bd_ridx));

	writel_relaxed(cur_rd->cfg & ~KDF_RD_VALID, (unsigned)&(cur_rd->cfg));

	kdf_ctl.rd_r_idx = (kdf_ctl.rd_r_idx + 1) % KDF_RD_NUM;
	writel(kdf_ctl.rd_r_idx << KDF_RPTR_OFFSET, 
								kdf_reg_base + HI_CH4_RDQ_PTR_OFFSET);

	if(KDF_RD_CHECK_ERR & cur_rd->cfg)
	{
		KDF_ERR_PRINT("rd check err\n");
		ret = CIPHER_STAT_CHECK_ERR;
	}
	
	return ret;
}

static void kdf_get_new_key(unsigned int u32DestIndex, KEY_MAKE_S * pstKeyMake)
{
	void * ram_key_addr = NULL;
	void * dst_addr = pstKeyMake->stKeyGet.pKeyAddr;
	u32    key_word = 0;
	int    i = 0;
	unsigned int kdf_reg_base;

	if(CIPHER_KEY_NOT_OUTPUT == pstKeyMake->enKeyOutput)
		return;
	*(pstKeyMake->stKeyGet.penOutKeyLen) = pstKeyMake->stKeyGet.enKeyLen;

	kdf_reg_base = (unsigned int)kdf_ctl.reg_base;
	ram_key_addr = (void *)(kdf_reg_base + HI_KEY_RAM_OFFSET + 
							KDF_SHA_KEY_MAX_LEN * (u32DestIndex + 1) - 
				(unsigned int)key_length_table[pstKeyMake->stKeyGet.enKeyLen]);

	for(i = 0; i < (int)key_length_table[pstKeyMake->stKeyGet.enKeyLen] / 4; i++)
	{
		key_word = readl((unsigned long)ram_key_addr);
		key_word = CIPHER_BSWAP32(key_word);
		writel_relaxed(key_word, (unsigned long)dst_addr);
		ram_key_addr = (void *)((unsigned int)ram_key_addr + 4);
		dst_addr = (void *)((unsigned int)dst_addr + 4);;
	}
}

int mdrv_cipher_gen_key(KEY_CONFIG_INFO_S * pstKeyCfgInfo, 
				S_CONFIG_INFO_S * pstSCfgInfo, unsigned int u32DestIndex,
													KEY_MAKE_S * pstKeyMake)
{
	int             ret     = 0;
	unsigned int    buf_off = 0;

	if(mdrv_cipher_enable())
	{
		KDF_ERR_PRINT("ERR: fail to open clk\n");
		return MDRV_ERROR;
	}
	osl_sem_down(&kdf_ctl.kdf_sem);

	if(SHA_KEY_SOURCE_DDR == pstKeyCfgInfo->enShaKeySource)
	{
		(void)memcpy_s(kdf_ctl.key_s_buf, KDF_SHA_KEY_MAX_LEN + KDF_SHA_S_MAX_LEN, 
							pstKeyCfgInfo->pKeySourceAddr, KDF_SHA_KEY_MAX_LEN);
		buf_off += KDF_SHA_KEY_MAX_LEN;//all of the low 256 bits belong to key.
	}
	if(SHA_S_SOURCE_DDR == pstSCfgInfo->enShaSSource)
		(void)memcpy_s((void *)((unsigned int)kdf_ctl.key_s_buf + buf_off), 
			KDF_SHA_S_MAX_LEN, pstSCfgInfo->pSAddr, pstSCfgInfo->u32ShaSLength);
#ifdef KDF_CACHE_ENABLE
	osl_cache_flush(OSL_DATA_CACHE, kdf_ctl.key_s_buf, 
									KDF_SHA_KEY_MAX_LEN + KDF_SHA_S_MAX_LEN);
#endif

	kdf_bd_cfg(KDF_OPS_KEY_MAKE, pstKeyCfgInfo, pstSCfgInfo, u32DestIndex, 
						pstSCfgInfo->u32ShaSLength - 1, kdf_ctl.key_s_buf);

	ret = kdf_wait_bd_done();
	if(ret)
	{
		KDF_ERR_PRINT("kdf_wait_bd_done err\n");
		/*lint -e801*/
		goto EXT_KDF_GEN;
		/*lint +e801*/
	}
	kdf_get_new_key(u32DestIndex, pstKeyMake);

EXT_KDF_GEN:
	osl_sem_up(&kdf_ctl.kdf_sem);
	return ret;
}

int kdf_rw_key (KDF_OPS kdf_op, void * pAddr, 
					unsigned int u32KeyIndex ,unsigned int u32ReadLength)
{
	int ret = 0;
	/*lint -e64*/
	KEY_CONFIG_INFO_S pstKeyCfgInfo = {0};
	S_CONFIG_INFO_S pstSCfgInfo = {0};
	/*lint +e64*/
	if(mdrv_cipher_enable())
	{
		KDF_ERR_PRINT("ERR: fail to open clk\n");
		return MDRV_ERROR;
	}
	osl_sem_down(&kdf_ctl.kdf_sem);
	kdf_bd_cfg(kdf_op, &pstKeyCfgInfo, &pstSCfgInfo, u32KeyIndex, 
													u32ReadLength, pAddr);
	ret = kdf_wait_bd_done();
	if(ret)
		KDF_ERR_PRINT("kdf_wait_bd_done err\n");
	osl_sem_up(&kdf_ctl.kdf_sem);
	return ret;
}

int kdf_info(void)
{
	KDF_ERR_PRINT("timeout count:%d\n", kdf_ctl.kdf_dbg.timeout);
	return CIPHER_SUCCESS;
}
