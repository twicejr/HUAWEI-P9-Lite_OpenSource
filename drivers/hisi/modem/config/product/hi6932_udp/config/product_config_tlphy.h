/* MD5: 285b253341f5a49d301403b03761c1c8*/
#if !defined(__PRODUCT_CONFIG_TLPHY_H__)
#define __PRODUCT_CONFIG_TLPHY_H__

#ifndef XTENSA_CORE				
#define XTENSA_CORE				 v7r22_bbe16 
#endif 

#ifndef XTENSA_SYSTEM			
#define XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux/$(CFG_XTENSA_CORE)/config 
#endif 

#ifndef TENSILICA_BUILDS	
#define TENSILICA_BUILDS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux 
#endif 

#ifndef TENSILICA_TOOLS	
#define TENSILICA_TOOLS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RD-2012.5-linux 
#endif 

#ifndef TENSILICA_BUILDS_HIFI
#define TENSILICA_BUILDS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux 
#endif 

#ifndef TENSILICA_TOOLS_HIFI
#define TENSILICA_TOOLS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RD-2012.5-linux 
#endif 

#ifndef LPHY_PUB_DTCM_BASE	
#define LPHY_PUB_DTCM_BASE	 0x72740000 
#endif 

#ifndef LPHY_PUB_ITCM_BASE	
#define LPHY_PUB_ITCM_BASE	 0x72840000 
#endif 

#ifndef LPHY_PRV_DTCM_BASE	
#define LPHY_PRV_DTCM_BASE	 0x72798000 
#endif 

#ifndef LPHY_PRV_ITCM_BASE	
#define LPHY_PRV_ITCM_BASE	 0x72898000 
#endif 

#ifndef LPHY_PUB_DTCM_SIZE		
#define LPHY_PUB_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PUB_ITCM_SIZE		
#define LPHY_PUB_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PRV_DTCM_SIZE		
#define LPHY_PRV_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PRV_ITCM_SIZE		
#define LPHY_PRV_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_LTE_DTCM_SIZE		
#define LPHY_LTE_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_LTE_ITCM_SIZE		
#define LPHY_LTE_ITCM_SIZE		 0x58000 
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

#ifndef TL_PHY_ASIC_V722        	
#define TL_PHY_ASIC_V722        	 
#endif 

#ifndef LPHY_SFT
#endif 

#ifndef TL_PHY_BBE16_CACHE
#endif 

#ifndef TL_PHY_HI6932         	
#define TL_PHY_HI6932         	 
#endif 

#ifndef TL_PHY_FEATURE_LTE_LCS  	
#define TL_PHY_FEATURE_LTE_LCS  	 
#endif 

#ifndef FEATURE_TAS
#define FEATURE_TAS FEATURE_OFF 
#endif 

#ifndef FEATURE_DSDS
#define FEATURE_DSDS FEATURE_OFF 
#endif 

#ifndef FEATURE_TLPHY_SINGLE_XO		
#define FEATURE_TLPHY_SINGLE_XO		 
#endif 

#ifndef FEATURE_LPHY_RFIC_HI6362
#define FEATURE_LPHY_RFIC_HI6362 FEATURE_ON 
#endif 

#ifndef FEATURE_TLPHY_LOWER_SAR
#define FEATURE_TLPHY_LOWER_SAR FEATURE_ON 
#endif 

#ifndef FEATURE_LTE_4RX
#define FEATURE_LTE_4RX FEATURE_OFF 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
