/* MD5: d563809bdd97c462c8f9e1661bf008d5*/
#if !defined(__PRODUCT_CONFIG_TLPHY_H__)
#define __PRODUCT_CONFIG_TLPHY_H__

#ifndef XTENSA_CORE				
#define XTENSA_CORE				 chicago_bbe16_nc_rf2 
#endif 

#ifndef XTENSA_SYSTEM			
#define XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RF-2015.2-linux/chicago_bbe16_nc_rf2/config 
#endif 

#ifndef TENSILICA_BUILDS	
#define TENSILICA_BUILDS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RF-2015.2-linux 
#endif 

#ifndef TENSILICA_TOOLS	
#define TENSILICA_TOOLS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RF-2015.2-linux 
#endif 

#ifndef LPHY_PUB_DTCM_BASE	
#define LPHY_PUB_DTCM_BASE	 0x72700000 
#endif 

#ifndef LPHY_PUB_ITCM_BASE	
#define LPHY_PUB_ITCM_BASE	 0x72800000 
#endif 

#ifndef LPHY_PRV_DTCM_BASE	
#define LPHY_PRV_DTCM_BASE	 0x72758000 
#endif 

#ifndef LPHY_PRV_ITCM_BASE	
#define LPHY_PRV_ITCM_BASE	 0x7285C000 
#endif 

#ifndef LPHY_PUB_DTCM_SIZE		
#define LPHY_PUB_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PUB_ITCM_SIZE		
#define LPHY_PUB_ITCM_SIZE		 0x5C000 
#endif 

#ifndef LPHY_PRV_DTCM_SIZE		
#define LPHY_PRV_DTCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_PRV_ITCM_SIZE		
#define LPHY_PRV_ITCM_SIZE		 0x74000 
#endif 

#ifndef LPHY_LTE_DTCM_SIZE		
#define LPHY_LTE_DTCM_SIZE		 0x78000 
#endif 

#ifndef LPHY_LTE_ITCM_SIZE		
#define LPHY_LTE_ITCM_SIZE		 0x74000 
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

#ifndef TL_PHY_ASIC_K3V6    	
#define TL_PHY_ASIC_K3V6    	 
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
#endif 

#ifndef FEATURE_TLPHY_SINGLE_XO		
#define FEATURE_TLPHY_SINGLE_XO		 
#endif 

#ifndef FEATURE_LPHY_RFIC_HI6362
#define FEATURE_LPHY_RFIC_HI6362 FEATURE_ON 
#endif 

#ifndef FEATURE_LTE_4RX
#define FEATURE_LTE_4RX FEATURE_OFF 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
