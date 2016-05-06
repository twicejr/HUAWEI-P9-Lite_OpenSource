/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_cipher.c
*
*   作    者 :  w00228729
*
*   描    述 :  cipher接口适配文件
*
*   修改记录 :  2013年03月12日  v1.00  w00228729 创建
*************************************************************************/
#include <product_config.h>
#include <mdrv_cipher.h>
#include <bsp_cipher.h>
#ifdef CONFIG_CIPHER

int mdrv_cipher_single_submit_task(unsigned int u32Chn, CIPHER_SINGLE_CFG_S * pstCfg)
{
	return mdrv_cipher_set_bdinfo(u32Chn, 1, pstCfg);
}

int mdrv_cipher_rela_submit_task(unsigned int u32Chn, CIPHER_RELA_CFG_S * pstCfg)
{
	int retval = 0;
	/*for real opt, we set 31-28bit max single opt*/
	pstCfg->enOpt |= 0x80000000;//(CIPHER_SINGLE_OPT_BUTTOM << 28);
	retval = mdrv_cipher_set_bdinfo(u32Chn, 1, (CIPHER_SINGLE_CFG_S *)pstCfg);
	pstCfg->enOpt &= ~0x80000000;//~(CIPHER_SINGLE_OPT_BUTTOM << 28);
	return retval;
}

int mdrv_cipher_get_cmplt_data(unsigned int u32Chn, unsigned int * pu32SourAddr, unsigned int * pu32DestAddr, CIPHER_NOTIFY_STAT_E * penStatus, unsigned int * pu32Private)
{
	unsigned int space_rd = 1;
	CIPHER_RD_INFO_S rds_info = {0};
	int ret = 0;
	
	ret = mdrv_cipher_get_rdinfo(u32Chn, &rds_info, &space_rd);
	*penStatus    = rds_info.enstat;
	*pu32SourAddr = rds_info.usr_field1;
	*pu32DestAddr = rds_info.usr_field2;
	*pu32Private  = rds_info.usr_field3;
	return ret;
}

int mdrv_cipher_write_key(unsigned int u32KeyIndex, void * pSourAddr, unsigned int u32Length)
{
	return kdf_rw_key(KDF_OPS_KEY_WRITE, pSourAddr, u32KeyIndex, u32Length);
}

int mdrv_cipher_read_key (void * pDestAddr, unsigned int u32KeyIndex ,unsigned int u32ReadLength)
{
	return kdf_rw_key(KDF_OPS_KEY_READ, pDestAddr, u32KeyIndex, u32ReadLength);
}

#endif
