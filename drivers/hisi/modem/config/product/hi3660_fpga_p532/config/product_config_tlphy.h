/* MD5: 86041a82f970958fdcd017f404a116f6*/
#if !defined(__PRODUCT_CONFIG_TLPHY_H__)
#define __PRODUCT_CONFIG_TLPHY_H__

#ifndef XTENSA_CORE				
#define XTENSA_CORE				 p532_bbe16_nocache 
#endif 

#ifndef XTENSA_SYSTEM			
#define XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux/p532_bbe16_nocache/config 
#endif 

#ifndef TENSILICA_BUILDS	
#define TENSILICA_BUILDS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux 
#endif 

#ifndef TENSILICA_TOOLS	
#define TENSILICA_TOOLS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RE-2014.5-linux 
#endif 

#ifndef LPHY_PUB_DTCM_BASE	
#define LPHY_PUB_DTCM_BASE	 0x49000000 
#endif 

#ifndef LPHY_PUB_ITCM_BASE	
#define LPHY_PUB_ITCM_BASE	 0x49100000 
#endif 

#ifndef LPHY_PRV_DTCM_BASE	
#define LPHY_PRV_DTCM_BASE	 0x49058000 
#endif 

#ifndef LPHY_PRV_ITCM_BASE	
#define LPHY_PRV_ITCM_BASE	 0x49158000 
#endif 

#ifndef LPHY_PUB_DTCM_SIZE		
#define LPHY_PUB_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PUB_ITCM_SIZE		
#define LPHY_PUB_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PRV_DTCM_SIZE		
#define LPHY_PRV_DTCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_PRV_ITCM_SIZE		
#define LPHY_PRV_ITCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_LTE_DTCM_SIZE		
#define LPHY_LTE_DTCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_LTE_ITCM_SIZE		
#define LPHY_LTE_ITCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_TDS_DTCM_SIZE		
#define LPHY_TDS_DTCM_SIZE		 0x30000 
#endif 

#ifndef LPHY_TDS_ITCM_SIZE		
#define LPHY_TDS_ITCM_SIZE		 0x38000 
#endif 

#ifndef LPHY_TOTAL_IMG_SIZE
#define LPHY_TOTAL_IMG_SIZE ((LPHY_PUB_DTCM_SIZE)+(LPHY_PUB_ITCM_SIZE)+(LPHY_LTE_DTCM_SIZE)*2+(LPHY_LTE_ITCM_SIZE)*2+(LPHY_TDS_DTCM_SIZE)+(LPHY_TDS_ITCM_SIZE)) 
#endif 

#ifndef TL_PHY_FPGA_P532    	
#define TL_PHY_FPGA_P532    	 
#endif 

#ifndef TL_PHY_HI3660         	
#define TL_PHY_HI3660         	 
#endif 

#ifndef TL_PHY_6950         	
#define TL_PHY_6950         	 
#endif 

#ifndef TL_PHY_BBE16_CACHE
#endif 

#ifndef TL_PHY_FEATURE_LTE_LCS  	
#define TL_PHY_FEATURE_LTE_LCS  	 
#endif 

#ifndef FEATURE_TLPHY_SINGLE_XO		
#define FEATURE_TLPHY_SINGLE_XO		 
#endif 

#ifndef FEATURE_LPHY_RFIC_HI6362
#define FEATURE_LPHY_RFIC_HI6362 FEATURE_ON 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
