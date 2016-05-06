/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

/*****************************************************************************
  1 头文件包含
 *****************************************************************************/
#include <hisi_noc_info.h>

#define CFG_INITFLOW_ARRAY_SIZE			22
#define CFG_TARGETFLOW_ARRAY_SIZE		33
#define VIVO_INITFLOW_ARRAY_SIZE		9
#define VIVO_TARGETFLOW_ARRAY_SIZE		8
#define VCODEC_INITFLOW_ARRAY_SIZE		3
#define VCODEC_TARGETFLOW_ARRAY_SIZE	7

char *cfg_initflow_array[] = {
	"A7(noc_a7tocfg)",
	"Audio(noc_asp_mst)",
	"ACPU(noc_cci2sysbus)",
	"DJTAG(noc_djtag_mst)",
	"DMA Controller(noc_dmac_mst)",
	"EMMC51(noc_emmc51)",
	"HISEE(noc_hisee_mst)",
	"SensorHub(noc_iomcu_ahb_mst)",
	"DMA-SensorHub(noc_iomcu_dma_mst)",
	"IPF(noc_ipf)",
	"IVP32(noc_ivp32_mst)",
	"LPM3(noc_lpmcu_mst)",
	"MODEM(noc_modem_mst)",
	"OCB(noc_ocb_mcu_mst)",
	"PCIE(noc_pcie)",
	"PERF_STAT_DEBUG(noc_perf_stat)",
	"SD3(noc_sd3)",
	"SDIO(noc_sdio)",
	"SECURITY(noc_sec_p)",
	"SECURITY(noc_sec_s)",
	"SOCP_DEBUG(noc_socp)",
	"CORESIGHT(noc_top_cssys)",
	"UFS(noc_ufs_mst)",
	"USB3(noc_usb3otg)",
};

char *cfg_targetflow_array[] = {
	"AOBUS(aobus_service_target)",
	"Audio(aspbus_service_target)",
	"Service_target(cfgbus_service_target)",
	"Service_target(dmabus_service_target)",
	"Service_target(ivp32bus_service_target)",
	"Service_target(mmc0bus_service_target)",
	"Service_target(mmc1bus_service_target)",
	"Service_target(modembus_service_target)",
	"AO-MMBUF(noc_aobus_mmbuf)",
	"Audio(noc_asp_cfg)",
	"CCI(noc_cci_cfg)",
	"Vivo(noc_cfg2vivo)",
	"DMA controller(noc_dmac_cfg)",
	"EMMC51(noc_emmc51_cfg)",
	"GIC(noc_gic)",
	"EMMC51(noc_emmc51_cfg)",
	"HISEE(noc_hisee_cfg)",
	"SSI(noc_hkadc_ssi)",
	"IOMCU(noc_iomcu_ahb_slv)",
	"IOMCU(noc_iomcu_apb_slv)",
	"IVP32(noc_ivp32_cfg)",
	"LPM3(noc_lpmcu_slv)",
	"MMC0BUS(noc_mmc0bus_apb_cfg)",
	"MMC1BUS(noc_mmc1bus_apb_cfg)",
	"MODEM(noc_modem_cfg)",
	"OCB(noc_ocb_cfg)",
	"PCIE(noc_pcie_cfg)",
	"DDRC(noc_sys2ddrc)",
	"HKMEM(noc_sys2hkmem)",
	"CFG(noc_sys_peri0_cfg)",
	"CFG(noc_sys_peri1_cfg)",
	"DMA(noc_sys_peri2_cfg)",
	"DMA(noc_sys_peri3_cfg)",
	"CORESIGHT(noc_top_cssys_slv)",
	"UFS-CFG(noc_ufs_cfg)",
	"USB3(noc_usb3otg_cfg)",
	"Service_target(sysbus_service_target)",
	"UFS-BUS(ufsbus_service_target)",
};

char *vcodec_initflow_array[] = {
	"VCODEC(noc_vcodec_cfg)",
	"VDEC(noc_vdec)",
	"VENC(noc_venc)",
	"RESERVED",
};

char *vcodec_targetflow_array[] = {
	"DDRC0(noc_vcodecbus_ddrc0)",
	"DDRC0(noc_vcodecbus_ddrc1)",
	"VDEC(noc_vdec_cfg)",
	"VENC(noc_venc_cfg)",
	"service_target (vcodec_bus_service_target)",
	"service_target (vdec_service_target)",
	"venc_service_target",
};

char *vivo_initflow_array[] = {
	"A7_RD(noc_a7tovivobus_rd)",
	"A7_WR (noc_a7tovivobus_wr)",
	"DSS0_RD(noc_dss0_rd)",
	"DSS0_WR(noc_dss0_wr)",
	"DSS1_RD (noc_dss1_rd)",
	"DSS1_WR(noc_dss1_wr)",
	"ISP1_RD(noc_isp1_rd)",
	"ISP1_WR(noc_isp1_wr)",
	"ISP_RD(noc_isp_rd)",
	"ISP_WR(noc_isp_wr)",
	"VIVO(noc_vivo_cfg)",
};


char *vivo_targetflow_array[VIVO_TARGETFLOW_ARRAY_SIZE] = {
	"service_target (dss_service_target)",
	"service_target (isp_service_target)",
	"service_target (noc_dss_cfg)",
	"ISP(noc_isp_cfg)",
	"DDRC(noc_vivobus_ddrc0_rd)",
	"DDRC (noc_vivobus_ddrc0_wr)",
	"DDRC (noc_vivobus_ddrc1_rd)",
	"DDRC (noc_vivobus_ddrc1_wr)"
};

struct noc_mid_info noc_mid[] = {
	/*Bus ID,     init_flow       ,mask   ,mid_va,        mid name */
	{0, 2, 0x3800, 0x0, "AP_CPU0"}, /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x800, "AP_CPU1"},   /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x1000, "AP_CPU2"},  /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x1800, "AP_CPU3"},  /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x2000, "AP_CPU4"},  /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x2800, "AP_CPU5"},  /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x3000, "AP_CPU6"},  /*noc_cci2sysbus,*/
	{0, 2, 0x3800, 0x3800, "AP_CPU7"},  /*noc_cci2sysbus,*/
	{0, 12, 0x007f, 0x02, "HDLC"},  /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x14, "MCPU"},  /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x15, "TL_BBE16"},  /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x16, "BBP_DMA_0"},/*noc_modem_mst,*/
	{0, 12, 0x007f, 0x17, "BBP_DMA_1"},/*noc_modem_mst,*/
	{0, 12, 0x007f, 0x18, "GU_BBP_MST"},    /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x19, "GU_BBP_MST"},    /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x1A, "BBE16_C"},   /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x1B, "EDMA"},  /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x1C, "CIPHER"},    /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x1D, "EDMA1"}, /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x1E, "UPACC"}, /*noc_modem_mst,*/
	{0, 12, 0x007f, 0x1F, "CICOM_0"},   /*noc_modem_mst,*/
	{0, 10, 0x007f, 0x23, "DSP_CORE"},  /*ivp32,*/
	{0xffffffff, 0, 0, 0, 0}    /* empty*/
};


const ROUTE_ID_ADDR_STRU cfgsys_routeid_addr_tbl[] = {
	/*Init_flow_bit   Targ_flow_bit    Targ subrange  Init localAddress*/
	/*-----------------------------------------------------------------*/
	{0x02, 0x00, 0x0, 0xe9830000},
	{0x02, 0x01, 0x0, 0xe9830000},
	{0x02, 0x02, 0x0, 0xe9800000},
	{0x02, 0x03, 0x0, 0xe9860000},
	{0x02, 0x04, 0x0, 0xe9850000},
	{0x02, 0x05, 0x0, 0xe9890000},
	{0x02, 0x06, 0x0, 0xe9880000},
	{0x02, 0x07, 0x0, 0xe9820000},
	{0x02, 0x08, 0x0, 0xea840000},
	{0x02, 0x08, 0x1, 0xea800000},
	{0x02, 0x09, 0x0, 0xe8000000},
	{0x02, 0x0A, 0x0, 0xe8100000},
	{0x02, 0x0B, 0x0, 0xe8400000},
	{0x02, 0x0C, 0x0, 0xfdf30000},
	{0x02, 0x0D, 0x0, 0xff3fb000},
	{0x02, 0x0E, 0x0, 0xe82b0000},
	{0x02, 0x0F, 0x0, 0xe82c0000},
	{0x02, 0x10, 0x0, 0xf0e00000},
	{0x02, 0x11, 0x0, 0xe82b8000},
	{0x02, 0x12, 0x0, 0xf0800000},
	{0x02, 0x12, 0x1, 0xf0000000},
	{0x02, 0x13, 0x0, 0xffd00000},
	{0x02, 0x14, 0x0, 0xe8c00000},
	{0x02, 0x15, 0x0, 0xea900000},
	{0x02, 0x15, 0x1, 0xffe00000},
	{0x02, 0x15, 0x2, 0xed000000},
	{0x02, 0x15, 0x3, 0xec000000},
	{0x02, 0x16, 0x0, 0xff37e000},
	{0x02, 0x17, 0x0, 0xff3fc000},
	{0x02, 0x17, 0x1, 0xff3e0000},
	{0x02, 0x17, 0x2, 0xf3f00000},
	{0x02, 0x18, 0x0, 0xe0000000},
	{0x02, 0x19, 0x0, 0xf1100000},
	{0x02, 0x1A, 0x0, 0xf4000000},
	{0x02, 0x1A, 0x1, 0xf8000000},
	{0x02, 0x1B, 0x0, 0xc0000000},
	{0x02, 0x1B, 0x1, 0x80000000},
	{0x02, 0x1B, 0x2, 0x0},
	{0x02, 0x1B, 0x3, 0x100000000},
	{0x02, 0x1B, 0x4, 0x200000000},
	{0x02, 0x1C, 0x0, 0xea000000},
	{0x02, 0x1C, 0x1, 0x0},
	{0x02, 0x1D, 0x0, 0xe8a00000},
	{0x02, 0x1E, 0x0, 0xe8800000},
	{0x02, 0x1F, 0x0, 0xff000000},
	{0x02, 0x20, 0x0, 0xfdf00000},
	{0x02, 0x21, 0x0, 0xfe000000},
	{0x02, 0x22, 0x0, 0xff3b0000},
	{0x02, 0x23, 0x0, 0xff200000},
	{0x02, 0x23, 0x1, 0xff100000},
	{0x02, 0x24, 0x0, 0xe9840000},
	{0x02, 0x25, 0x0, 0xe9810000},
};

/* vivo_bus */
const ROUTE_ID_ADDR_STRU vivo_routeid_addr_tbl[] = {
	/* Init_flow  Targ_flow  Targ_subrange Init_localAddress */
	/* ----------------------------------------------------- */
	{0x0A, 0x00, 0x0, 0xe86c0000},
	{0x0A, 0x00, 0x1, 0x0},
	{0x0A, 0x01, 0x0, 0xe86d0000},
	{0x0A, 0x02, 0x0, 0xe8600000},
	{0x0A, 0x03, 0x0, 0xe8400000},
	{0x00, 0x04, 0x0, 0x0},
	{0x00, 0x04, 0x1, 0x0},
	{0x01, 0x05, 0x0, 0x0},
	{0x01, 0x05, 0x1, 0x0},
	{0x00, 0x06, 0x0, 0x0},
	{0x00, 0x06, 0x1, 0x0},
	{0x01, 0x07, 0x0, 0x0},
	{0x01, 0x07, 0x1, 0x0},
};

/* vcodec_bus */
const ROUTE_ID_ADDR_STRU vcodec_routeid_addr_tbl[] = {
	/* Init_flow  Targ_flow  Targ_subrange : Init_mapping ,
	Init_localAddress , Targ_mapping , Targ_localAddress */
	/* ---------------------------------------------------*/
	{0x01, 0x00, 0x0, 0x0},
	{0x01, 0x00, 0x1, 0x0},
	{0x01, 0x01, 0x0, 0x0},
	{0x01, 0x01, 0x1, 0x0},
	{0x00, 0x02, 0x0, 0xe8800000},
	{0x00, 0x03, 0x0, 0xe8900000},
	{0x00, 0x04, 0x0, 0xe8920000},
	{0x00, 0x04, 0x1, 0x0},
	{0x00, 0x05, 0x0, 0xe8930000},
	{0x00, 0x06, 0x0, 0xe8940000},
};



const struct noc_bus_info noc_buses_info[] = {
	[0] = {
		.name = "cfg_sys_noc_bus",
		.initflow_mask = ((0x1f) << 18),
		.targetflow_mask = ((0x3f) << 12),
		.targ_subrange_mask = ((0x7) << 9),
		.seq_id_mask = (0x3FFF),
		.initflow_array = cfg_initflow_array,
		.initflow_array_size = 32,
		.targetflow_array = cfg_targetflow_array,
		.targetflow_array_size = 48,
		.routeid_tbl = cfgsys_routeid_addr_tbl,
		.routeid_tbl_size = ARRAY_SIZE(cfgsys_routeid_addr_tbl)
	},
	[1] = {
		.name = "vcodec_bus",
		.initflow_mask = ((0x1f) << 17),
		.targetflow_mask = ((0x1f) << 12),
		.targ_subrange_mask = ((0x7) << 9),
		.seq_id_mask = (0x1FFF),
		.initflow_array = vcodec_initflow_array,
		.initflow_array_size = 4,
		.targetflow_array = vcodec_targetflow_array,
		.targetflow_array_size = 8,
		.routeid_tbl = vcodec_routeid_addr_tbl,
		.routeid_tbl_size = ARRAY_SIZE(vcodec_routeid_addr_tbl)
	},
	[2] = {
		.name = "vivo_bus",
		.initflow_mask = ((0xf) << 12),
		.targetflow_mask = ((0x7) << 9),
		.targ_subrange_mask = ((0x1) << 8),
		.seq_id_mask = (0xFF),
		.initflow_array = vivo_initflow_array,
		.initflow_array_size = 16,
		.targetflow_array = vivo_targetflow_array,
		.targetflow_array_size = 8,
		.routeid_tbl = vivo_routeid_addr_tbl,
		.routeid_tbl_size = ARRAY_SIZE(vivo_routeid_addr_tbl)
	}
};

/*
 * if noc_happend's initflow is in the hisi_modemnoc_initflow,
 * firstly save log, then system reset.
 */
static const struct noc_busid_initflow hisi_modemnoc_initflow[] = {
	/* Bus ID,    init_flow */
	{0, 9},	/*ipf*/
	{0, 20},	/*socp*/
	{ARRAY_END_FLAG, 0},	/*end*/
};

/*
 * if noc_happend's nodename is in the hisi_modemnoc_nodename,
 * firstly save log, then system reset.
 */
static const char *hisi_modemnoc_nodemame[] = {
	"modem_bus",
	NULL,	/*end*/
};

unsigned int hisi_noc_get_bus_info_num(void)
{
	return ARRAY_SIZE(noc_buses_info);
}

/*******************************************************************************
Function:       hisi_get_modemnoc_initflow_nodename
Description:    get the filter conditions of modemnoc.
Input:          NA
Output:         modemnoc_initflow:the filter condition of initflow
				modemnoc_nodename:the filter condition of nodename
Return:         NA
********************************************************************************/
void hisi_get_modemnoc_initflow_nodename(
	struct noc_busid_initflow **modemnoc_initflow, char ***modemnoc_nodename)
{
	*modemnoc_initflow = (struct noc_busid_initflow *)hisi_modemnoc_initflow;
	*modemnoc_nodename = (char **)hisi_modemnoc_nodemame;
}

