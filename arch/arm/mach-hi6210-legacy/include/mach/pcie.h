#ifndef __K3V2_PCIE_H__
#define __K3V2_PCIE_H__

#include <mach/boardid.h>

#define PCIE0_PHY_ADDR_PHYS	(0xF0000000)
#define PCIE0_BASE_ADDR_PHYS	(0xF0100000)
#define PCIE0_IO_SPACE_START    (0xF0001000)
#define PCIE0_IO_SPACE_END       (0xF0001FFF)

#define TIME_TO_WAIT      1000   //default is 100ms

#define SCPEREN3	(0x0050)
#define SCPERDIS3	(0x0054)
	#define  pcie_clk_req  (16)

#define SCPERRSTEN3 	(0x00A4)
#define SCPERRSTDIS3 	(0x00A8)
	#define  pcie0_rst_req	(16)

#define PERI_CTRL4	(0x010)
#define PERI_CTRL5	(0x014)
#define PERI_CTRL6	(0x018)
#define PERI_CTRL7	(0x01c)
#define PERI_CTRL8	(0x020)
#define PERI_CTRL9	(0x024)
#define PERI_CTRL10	(0x028)
#define PERI_CTRL11	(0x02c)
#define PERI_CTRL12	(0x030)
#define PERI_CTRL13	(0x034)
#define PERI_CTRL18	(0x048)
#define PERI_CTRL19	(0x04c)

#define PERI_PCIE0 PERI_CTRL4
	#define  pcie0_slv_device_type (28)
#define PERI_PCIE1	PERI_CTRL5
#define PERI_PCIE2	PERI_CTRL6
#define PERI_PCIE3 PERI_CTRL7
#define PERI_PCIE4 PERI_CTRL8
	#define   pcie0_slv_armisc_info (0)
#define PERI_PCIE5	PERI_CTRL9
#define PERI_PCIE6	PERI_CTRL10
#define PERI_PCIE7	PERI_CTRL11
	#define  pcie0_app_ltssm_enable	(11)
#define PERI_PCIE8	PERI_CTRL12
#define PERI_PCIE9	PERI_CTRL13
#define PERI_PCIE10	PERI_CTRL18
#define PERI_PCIE11	PERI_CTRL19

#define pcie_x2_slv_armisc_info (0)
#define pcie_cfg_type0 (0x4)
#define pcie_cfg_type1 (0x5)
#define pcie_addr_trans_type (21)
#define pcie_x2_slv_device_type	(28)
#define pcie_x2_app_ltssm_enable	(11)
#define pcie_x2_awaddr_high	(24)	/*pcie1 write op's bus nr*/
#define pcie_x2_araddr_high	(24)
#define pcie0_awaddr_high	(24)
#define pcie0_araddr_high	(24)

#define PERI_STAT1 (0x054) 
#define PERI_STAT2 (0x058) 
#define PERI_STAT3 (0x05c) 
#define PERI_STAT4 (0x200) 

#define PCIE_STAT0 PERI_STAT1
#define pcie0_rdlh_link_up ( \
	(CS_CHIP_ID == get_chipid()) ?\
	5: (DI_CHIP_ID == get_chipid()) ?\
	10:5 )
	
#define pcie_phy_link_up ( \
	(CS_CHIP_ID == get_chipid()) ?\
	15: (DI_CHIP_ID == get_chipid()) ?\
	22:15 )

#define PCIE_STAT1 PERI_STAT2
#define PCIE_STAT2 PERI_STAT3
#define PCIE_STAT3 PERI_STAT4

#define PCIE0_IRQ_INTA  (85)
#define PCIE0_IRQ_INTB  (86)
#define PCIE0_IRQ_INTC  (87)
#define PCIE0_IRQ_INTD  (88)

#define PCIE_INTA_PIN   (1)
#define PCIE_INTB_PIN   (2)
#define PCIE_INTC_PIN   (3)
#define PCIE_INTD_PIN   (4)

enum pcie_sel{
	pcie_sel_none,	/*neither controllers will be selected.*/
	pcie0_x1_sel,	/*pcie0 selected. pcie0 can only connected with a x1 device*/
};
enum pcie_work_mode{
	pcie_wm_ep = 0x0,	/*ep mode*/
	pcie_wm_lep = 0x1,	/*legacy ep mode*/
	pcie_wm_rc = 0x4,	/*rc mode*/
};
enum pcie_controller{
	pcie_controller_none,
	pcie_controller_0,
	pcie_controller_1,
};
struct pcie_iatu{
	unsigned int viewport;		/*iATU Viewport Register*/
	unsigned int region_ctrl_1;	/*Region Control 1 Register*/
	unsigned int region_ctrl_2;	/*Region Control 2 Register*/
	unsigned int lbar;		/*Lower Base Address Register*/
	unsigned int ubar;		/*Upper Base Address Register*/
	unsigned int lar;		/*Limit Address Register*/
	unsigned int ltar;		/*Lower Target Address Register*/
	unsigned int utar;		/*Upper Target Address Register*/
};

struct pcie_info{
	u8		root_bus_nr;			/*root bus number*/
	enum		pcie_controller controller;	/*belong to which controller*/
	unsigned int	base_addr;			/*device config space base addr & mem-io space base addr*/
	unsigned int	conf_base_addr;			/*rc config space base addr*/
};

#define PCIE_DEBUG_LEVEL_REG    (1)
#define PCIE_DEBUG_LEVEL_FUNC   (2)
#define PCIE_DEBUG_LEVEL_MODULE (3)

#define PCIE_DEBUG_LEVEL PCIE_DEBUG_LEVEL_MODULE

#define PCIE_DEBUG
#ifdef PCIE_DEBUG
#define pcie_debug(level,str,arg...)\
do{\
    if((level)<= PCIE_DEBUG_LEVEL){\
        printk(KERN_DEBUG "%s->%d," str "\n" ,__func__,__LINE__,##arg);\
    }\
}while(0)
#else
#define pcie_debug(level,str,arg...)
#endif

#define pcie_assert(con)\
do{\
    if(!(con)){\
        printk(KERN_ERR "%s->%d,assert fail!\n",__func__,__LINE__);\
    }\
}while(0)

#define pcie_error(str,arg...)\
do{\
    printk(KERN_ERR "%s->%d" str "\n",__func__,__LINE__,##arg);\
}while(0)

#endif

