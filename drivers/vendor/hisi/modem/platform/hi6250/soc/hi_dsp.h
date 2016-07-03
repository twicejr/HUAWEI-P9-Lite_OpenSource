
#ifndef __DSP_H__
#define __DSP_H__

#include <product_config.h>
#include <ptable_com.h>
#include <soc_memmap.h>

#ifdef __cplusplus
extern "C" {
#endif


#define CONFIG_G_POWER_OPTIMIZE

#define BBE_TCM_ADDR (HI_BBE16DMEM_BASE_ADDR)
#define BBE_TCM_SIZE (0x00100000) /* 1 MB */

/* MUTI */
/*--------------*-- 256KB
 *    TDS-I     *
 *--------------*-- 256KB
 *    TDS-D     *
 *--------------*-- 256KB
 *    LTE-I     *
 *--------------*-- 256KB
 *    LTE-D     *
 *--------------*-- 260KB
 *    PUB-I     *
 *--------------*-- 252KB
 *    PUB-D     *
 *--------------*-- BBE_TCM_ADDR
 */
#define LPHY_BBE16_PUB_DTCM_LOAD_ADDR (LPHY_PUB_DTCM_BASE)
#define LPHY_BBE16_PUB_DTCM_LOAD_SIZE (LPHY_PUB_DTCM_SIZE)
#define LPHY_BBE16_MOD_DTCM_LOAD_ADDR (LPHY_PRV_DTCM_BASE)
#define LPHY_BBE16_MOD_DTCM_LOAD_SIZE (LPHY_PRV_DTCM_SIZE)

#define LPHY_BBE16_PUB_ITCM_LOAD_ADDR (LPHY_PUB_ITCM_BASE)
#define LPHY_BBE16_PUB_ITCM_LOAD_SIZE (LPHY_PUB_ITCM_SIZE)
#define LPHY_BBE16_MOD_ITCM_LOAD_ADDR (LPHY_PRV_ITCM_BASE)
#define LPHY_BBE16_MOD_ITCM_LOAD_SIZE (LPHY_PRV_ITCM_SIZE)

#define BBE_DDR_PUB_DTCM_ADDR (DDR_TLPHY_IMAGE_ADDR)
#define BBE_DDR_PUB_ITCM_ADDR (BBE_DDR_PUB_DTCM_ADDR + LPHY_BBE16_PUB_DTCM_LOAD_SIZE)

#define LPHY_BBE16_MUTI_IMAGE_OFFSET    (0)
#define LPHY_BBE16_MUTI_IMAGE_SIZE (LPHY_TOTAL_IMG_SIZE)

#define TPHY_BBE16_CFG_DATA_OFFSET  (LPHY_BBE16_MUTI_IMAGE_OFFSET + LPHY_BBE16_MUTI_IMAGE_SIZE)
#define TPHY_BBE16_CFG_DATA_SIZE    (0x00040000)    /* 256KB */

/* HiFi2 */
#define HIFI_TCM_ADDR (0xFFFFFFFF)
#define HIFI_TCM_SIZE (0xFFFFFFFF)


#ifdef __cplusplus
}
#endif

#endif
