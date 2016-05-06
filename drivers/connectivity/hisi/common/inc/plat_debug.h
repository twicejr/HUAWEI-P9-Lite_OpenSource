
#ifndef __PLAT_DEBUG_H__
#define __PLAT_DEBUG_H__

/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include "bfgx_user_ctrl.h"

#ifdef CONFIG_HI1102_PLAT_HW_CHR
#include "chr_user.h"
#else
#define CHR_LOG(prio, tag, fmt...)
#endif

/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define PS_PRINT_FUNCTION_NAME				do { \
		if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
		{ \
			printk(KERN_DEBUG KBUILD_MODNAME ":D]%s]" ,__func__);     \
		} \
	}while(0)

#define PS_PRINT_DBG(s, args...)            do{ \
		if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
		{ \
			printk(KERN_DEBUG KBUILD_MODNAME ":D]%s]" s,__func__, ## args); \
		}\
	}while(0)

#define PS_PRINT_INFO(s, args...)           do{ \
		if (PLAT_LOG_INFO <= g_plat_loglevel) \
		{ \
			printk(KERN_DEBUG KBUILD_MODNAME ":I]%s]" s,__func__, ## args);\
			CHR_LOG(CHR_LOG_INFO, CHR_LOG_TAG_PLAT, s, ##args); \
		} \
	}while(0)

#define PS_PRINT_SUC(s, args...)            do{ \
		if (PLAT_LOG_INFO <= g_plat_loglevel) \
		{ \
			printk(KERN_DEBUG KBUILD_MODNAME ":S]%s]" s,__func__, ## args); \
			CHR_LOG(CHR_LOG_INFO, CHR_LOG_TAG_PLAT, s, ##args); \
		} \
	}while(0)

#define PS_PRINT_WARNING(s, args...)        do{ \
		if (PLAT_LOG_WARNING <= g_plat_loglevel) \
		{ \
			printk(KERN_WARNING KBUILD_MODNAME ":W]%s]" s,__func__, ## args);\
			CHR_LOG(CHR_LOG_WARN, CHR_LOG_TAG_PLAT, s, ##args); \
		} \
	}while(0)

#define PS_PRINT_ERR(s, args...)            do{ \
		if (PLAT_LOG_ERR <= g_plat_loglevel) \
		{ \
			printk(KERN_ERR KBUILD_MODNAME ":E]%s]" s,__func__, ## args); \
			CHR_LOG(CHR_LOG_ERROR, CHR_LOG_TAG_PLAT, s, ##args); \
		} \
	}while(0)

#define PS_PRINT_ALERT(s, args...)          do{ \
		if (PLAT_LOG_ALERT <= g_plat_loglevel) \
		{ \
			printk(KERN_ALERT KBUILD_MODNAME ":ALERT]%s]" s,__func__, ## args); \
			CHR_LOG(CHR_LOG_ERROR, CHR_LOG_TAG_PLAT, s, ##args); \
		} \
	}while(0)

#define PS_BUG_ON(s)                       do{ \
        if((BUG_ON_ENABLE == g_bug_on_enable)) \
        { \
           BUG_ON(s);\
        } \
    }while(0)

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/

#endif /* PLAT_DEBUG_H */


