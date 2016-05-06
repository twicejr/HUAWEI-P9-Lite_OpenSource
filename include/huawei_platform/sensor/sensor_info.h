/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/board_sensors.h>
//#include <hsad/config_interface.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/moduleparam.h>	
#include <linux/printk.h>
#include <linux/ctype.h>
#include <linux/stat.h>


extern int als_ps_debug_mask; 
extern int gs_debug_mask; 
extern int hall_debug_mask; 
extern int compass_debug_mask; 




/*****APL sensor start*******/
#define als_ps_ERR(x...) do {\
    if (als_ps_debug_mask >=0) \
        printk(KERN_ERR x);\
    } while (0)

#define als_ps_INFO(x...) do {\
    if (als_ps_debug_mask >=0) \
        printk(KERN_ERR x);\
    } while (0)
	
#define als_ps_FLOW(x...) do {\
    if (als_ps_debug_mask >=1) \
        printk(KERN_ERR x);\
    } while (0)


#define als_ps_DBG(x...) do {\
    if (als_ps_debug_mask) \
        printk(KERN_ERR x);\
  } while (0)
/*****APL sensor end *******/


/*****GS sensor start *******/
#define gs_ERR(x...) do {\
    if (gs_debug_mask >=0) \
        printk(KERN_ERR x);\
    } while (0)

#define gs_INFO(x...) do {\
    if (gs_debug_mask >=0) \
        printk(KERN_INFO x);\
    } while (0)
	
#define gs_FLOW(x...) do {\
    if (gs_debug_mask >=1) \
        printk(KERN_ERR x);\
    } while (0)


#define gs_DBG(x...) do {\
    if (gs_debug_mask) \
        printk(KERN_ERR x);\
  } while (0)
/*****GS sensor end *******/

/*****HALL sensor start *******/
#define hall_ERR(x...) do {\
    if (hall_debug_mask >=0) \
        printk(KERN_ERR x);\
    } while (0)

#define hall_INFO(x...) do {\
    if (hall_debug_mask >=0) \
        printk(KERN_INFO x);\
    } while (0)
	
#define hall_FLOW(x...) do {\
    if (hall_debug_mask >=1) \
        printk(KERN_ERR x);\
    } while (0)


#define hall_DBG(x...) do {\
    if (hall_debug_mask) \
        printk(KERN_ERR x);\
  } while (0)
/*****HALL sensor end *******/


/*****COMPASS sensor start *******/
#define compass_ERR(x...) do {\
    if (compass_debug_mask >=0) \
        printk(KERN_ERR x);\
    } while (0)

#define compass_INFO(x...) do {\
    if (compass_debug_mask >=0) \
        printk(KERN_INFO x);\
    } while (0)
	
#define compass_FLOW(x...) do {\
    if (compass_debug_mask >=1) \
        printk(KERN_ERR x);\
    } while (0)


#define compass_DBG(x...) do {\
    if (compass_debug_mask) \
        printk(KERN_ERR x);\
  } while (0)
/*****COMPASS sensor end *******/

struct Gsensor_excep {
int base;
int min_three_axis;
int last_axis[3];
int current_axis[3];
};
