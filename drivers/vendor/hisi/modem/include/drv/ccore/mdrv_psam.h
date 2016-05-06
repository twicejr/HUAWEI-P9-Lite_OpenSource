#ifndef __MDRV_CCORE_PSAM_H__
#define __MDRV_CCORE_PSAM_H__
#ifdef __cplusplus
extern "C"
{
#endif



/*****************************************************************************
* 函 数 名  : mdrv_psam_set_crdq_ctrl
*
* 功能描述  : 直通RD转BD，配置下行过滤器链表头索引
*
* 输入参数  : unsigned int cipher_fc_head，索引号
* 输出参数  :
*
* 返 回 值  : 	0 配置成功
*             		-1 配置失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_psam_set_crdq_ctrl(unsigned int cipher_fc_head);






#ifdef __cplusplus
}
#endif
#endif
