

#ifdef __cplusplus
extern "C"
{
#endif
#include "drv_comm.h"
#include "drv_mailbox_cfg.h"
#include "bsp_icc.h"
#include "bsp_nvim.h"
#include "bsp_shared_ddr.h"

#ifdef CONFIG_HIFI
/*****************************************************************************
 函 数 名  : drv_hifi_fill_mb_info
 功能描述  : 邮箱信息设置接口
 输入参数  : addr 段信息地址(由HIFI加载模块传入)
 输出参数  :
 返 回 值  : void
 调用函数  : V9R1中在fastboot中调用，V7R2中与DSP一起加载调用
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月4日
    作    者   : 崔军强 64416
    修改内容   : 新生成函数

*****************************************************************************/
void drv_hifi_fill_mb_info(unsigned int addr)
{
    CARM_HIFI_DYN_ADDR_SHARE_STRU *pdata;

    pdata = (CARM_HIFI_DYN_ADDR_SHARE_STRU*)addr;

    pdata->stCarmHifiMB.uwHifi2CarmIccChannelLen   = (unsigned int)(STRU_SIZE + ICC_HIFI_VOS_SIZE);
    pdata->stCarmHifiMB.uwHifi2TphyIccChannelLen   = (unsigned int)(STRU_SIZE + ICC_HIFI_TPHY_SIZE);
    pdata->stCarmHifiMB.uwHifi2CarmIccChannelAddr  = (unsigned int)SHD_DDR_V2P(ADDR_HIFI_VOS_MSG_SEND);
    pdata->stCarmHifiMB.uwCarm2HifiIccChannelAddr  = (unsigned int)SHD_DDR_V2P(ADDR_HIFI_VOS_MSG_RECV);
    pdata->stCarmHifiMB.uwHifi2TphyIccChannelAddr  = (unsigned int)SHD_DDR_V2P(ADDR_HIFI_TPHY_MSG_SEND);
    pdata->stCarmHifiMB.uwTphy2HifiIccChannelAddr  = (unsigned int)SHD_DDR_V2P(ADDR_HIFI_TPHY_MSG_RECV);
    pdata->stCarmHifiMB.uwProtectWord           = HIFI_MB_ADDR_PROTECT;


    pdata->stAarmHifiMB.uwHifi2AarmMailBoxLen   = MAILBOX_QUEUE_SIZE(HIFI, ACPU, MSG);
    pdata->stAarmHifiMB.uwAarm2HifiMailBoxLen   = MAILBOX_QUEUE_SIZE(ACPU, HIFI, MSG);
    pdata->stAarmHifiMB.uwHifiAarmHeadAddr      = MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG);
    pdata->stAarmHifiMB.uwHifiAarmBodyAddr      = MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG);
    pdata->stAarmHifiMB.uwAarmHifiHeadAddr      = MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG);
    pdata->stAarmHifiMB.uwAarmHifiBodyAddr      = MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG);
    pdata->stAarmHifiMB.uwProtectWord           = HIFI_MB_ADDR_PROTECT;

	pdata->stNVShare.uwAddrPhy = (unsigned int)SHD_DDR_V2P(NV_GLOBAL_CTRL_INFO_ADDR);
	pdata->stNVShare.uwSize = SHM_MEM_NV_SIZE;
	pdata->stNVShare.uwProtectWord = HIFI_MB_ADDR_PROTECT;


    pdata->uwNvBaseAddrPhy = (unsigned int)SHD_DDR_V2P(NV_GLOBAL_CTRL_INFO_ADDR);
    pdata->uwNvBaseAddrVirt = 0; /*NV虚拟地址不需要提供*/

    pdata->uwProtectWord = HIFI_MB_ADDR_PROTECT;

    return ;

}
#endif

#ifdef __cplusplus
}
#endif


