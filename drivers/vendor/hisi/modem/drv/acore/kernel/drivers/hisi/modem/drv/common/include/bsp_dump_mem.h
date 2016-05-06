/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _BSP_DUMP_MEM_H
#define _BSP_DUMP_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLY__
#include "bsp_dump.h"
#include "osl_types.h"
#include "osl_list.h"
#include "osl_spinlock.h"
#endif
#include "bsp_memmap.h"
#include "bsp_s_memory.h"
#ifdef __OS_RTOSCK__
#include <string.h>
#endif

/*  dump content

    ---------------
   | head          |
    ---------------
   | area map [8]  |
    ---------------
   | area 1        |
    ---------------
   | area 2        |
    ---------------
   | area 3        |
    ---------------
   | area 4        |
    ---------------
   | area 5        |
    ---------------
   | area 6        |
    ---------------
   | area 7        |
    ---------------
   | area 8        |
    ---------------    
*/

/* area content

    ---------------
   | head          |
    ---------------
   | field map[64] |
    ---------------
   | field 1       |
    ---------------
   | field 2       |
    ---------------
   | ...           |
    ---------------
   | field N(N<=64)|
    ---------------
*/
#ifdef __OS_RTOSCK__
#ifdef printk
#undef printk
#endif
#define printk  SRE_Printf
#endif


#ifdef __KERNEL__
#elif defined( __VXWORKS__)
#elif defined(__OS_RTOSCK__)
#elif defined( __CMSIS_RTOS)
typedef  s32 spinlock_t;

#define spin_lock_init(lock)    \
do{ 	\
	*lock = *lock; \
}while(0)


#define spin_lock_irqsave(lock, flags)    \
do{ 	\
	local_irq_save(*lock); \
}while(0)

#define spin_unlock_irqrestore(lock, flags)    \
do{ 	\
	local_irq_restore(*lock); \
}while(0)
#else
typedef s32 spinlock_t;
#endif

//#define DUMP_MAGIC 0xdead5a5a 
#define DUMP_MAGIC 0xdead6b6b


/* area number supported by dump */
#define DUMP_AREA_MAX_NUM   8   

/* field number supported by area */
#define DUMP_FIELD_MAX_NUM  64  

#ifndef __ASSEMBLY__
/* field status */
enum
{
    DUMP_FIELD_UNUSED = 0,
    DUMP_FIELD_USED   = 1,
};

/* areas, max number is 8 */ 
typedef enum
{
	DUMP_AREA_AP    = 0,
	DUMP_AREA_CP    = 1, 
	DUMP_AREA_LPM3  = 2,
	DUMP_AREA_SHARE = 3,
	DUMP_AREA_BUTT,
}DUMP_AREA_ID;


/* dump memory map */
typedef struct dump_mem_ctrl_s
{
    unsigned long smntn_virt_addr;
	unsigned long smntn_phy_addr;
	unsigned long smntn_mem_size;
}dump_mem_ctrl_t;

extern dump_mem_ctrl_t g_dump_mem_ctrl;
#endif

/* DUMP重启备份区地址 */
#define DUMP_BACKUP_PHY_ADDR DDR_SOCP_ADDR

/* dump */
#if defined (__FASTBOOT__)|| defined (__M3BOOT__)
#define DUMP_ADDR            DDR_MNTN_ADDR
#define DUMP_SIZE            DDR_MNTN_SIZE
#else
#define DUMP_ADDR            (g_dump_mem_ctrl.smntn_virt_addr)
#define DUMP_SIZE            (g_dump_mem_ctrl.smntn_mem_size)
#endif

/* dump head  */
#define DUMP_HEAD_ADDR       DUMP_ADDR
#define DUMP_HEAD_SIZE       0x100

/* dump map */
#define DUMP_AREA_MAP_ADDR   (DUMP_HEAD_ADDR+DUMP_HEAD_SIZE)
#define DUMP_AREA_MAP_SIZE   0x200

/* AP area */
#define DUMP_AREA_AP_ADDR         (DUMP_AREA_MAP_ADDR+DUMP_AREA_MAP_SIZE)
#define DUMP_AREA_AP_SIZE         0x50000 /* 320K */
#define DUMP_AREA_AP_HEAD_ADDR    DUMP_AREA_AP_ADDR
#define DUMP_AREA_AP_HEAD_SIZE    0x20
#define DUMP_AREA_AP_MAP_ADDR     (DUMP_AREA_AP_HEAD_ADDR+DUMP_AREA_AP_HEAD_SIZE)
#define DUMP_AREA_AP_MAP_SIZE     (32*DUMP_FIELD_MAX_NUM)
#define DUMP_AREA_AP_STATIC_ADDR  (DUMP_AREA_AP_MAP_ADDR+DUMP_AREA_AP_MAP_SIZE)
#define DUMP_AREA_AP_STATIC_SIZE  (0x2C000) /* 实际使用0x2B980 */
#define DUMP_AREA_AP_DYNAMIC_ADDR (DUMP_AREA_AP_STATIC_ADDR+DUMP_AREA_AP_STATIC_SIZE)
#define DUMP_AREA_AP_DYNAMIC_SIZE (DUMP_AREA_AP_SIZE-DUMP_AREA_AP_HEAD_SIZE-DUMP_AREA_AP_MAP_SIZE-DUMP_AREA_AP_STATIC_SIZE)

/* CP area */
#define DUMP_AREA_CP_ADDR         (DUMP_AREA_AP_ADDR+DUMP_AREA_AP_SIZE)
#define DUMP_AREA_CP_SIZE         0x80000 /* 512k */
#define DUMP_AREA_CP_HEAD_ADDR    DUMP_AREA_CP_ADDR
#define DUMP_AREA_CP_HEAD_SIZE    0x20
#define DUMP_AREA_CP_MAP_ADDR     (DUMP_AREA_CP_HEAD_ADDR+DUMP_AREA_CP_HEAD_SIZE)
#define DUMP_AREA_CP_MAP_SIZE     (32*DUMP_FIELD_MAX_NUM)
#define DUMP_AREA_CP_STATIC_ADDR  (DUMP_AREA_CP_MAP_ADDR+DUMP_AREA_CP_MAP_SIZE)
#define DUMP_AREA_CP_STATIC_SIZE  (0x40000) /* 实际使用0x3F180 */
#define DUMP_AREA_CP_DYNAMIC_ADDR (DUMP_AREA_CP_STATIC_ADDR+DUMP_AREA_CP_STATIC_SIZE)
#define DUMP_AREA_CP_DYNAMIC_SIZE (DUMP_AREA_CP_SIZE-DUMP_AREA_CP_HEAD_SIZE-DUMP_AREA_CP_MAP_SIZE-DUMP_AREA_CP_STATIC_SIZE)

/* LPM3 area */
#define DUMP_AREA_LPM3_ADDR        (DUMP_AREA_CP_ADDR+DUMP_AREA_CP_SIZE)
#define DUMP_AREA_LPM3_SIZE        0x20000 /* 128K */
#define DUMP_AREA_LPM3_HEAD_ADDR    DUMP_AREA_LPM3_ADDR
#define DUMP_AREA_LPM3_HEAD_SIZE    0x20
#define DUMP_AREA_LPM3_MAP_ADDR     (DUMP_AREA_LPM3_HEAD_ADDR+DUMP_AREA_LPM3_HEAD_SIZE)
#define DUMP_AREA_LPM3_MAP_SIZE     (32*DUMP_FIELD_MAX_NUM)
#define DUMP_AREA_LPM3_STATIC_ADDR (DUMP_AREA_LPM3_MAP_ADDR+DUMP_AREA_LPM3_MAP_SIZE)
#define DUMP_AREA_LPM3_STATIC_SIZE (0x19000) /* 实际使用95-98K */
#define DUMP_AREA_LPM3_DYNAMIC_ADDR (DUMP_AREA_LPM3_STATIC_ADDR+DUMP_AREA_LPM3_STATIC_SIZE)
#define DUMP_AREA_LPM3_DYNAMIC_SIZE (DUMP_AREA_LPM3_SIZE-DUMP_AREA_LPM3_HEAD_SIZE-DUMP_AREA_LPM3_MAP_SIZE-DUMP_AREA_LPM3_STATIC_SIZE)

/* Share area */
#define DUMP_AREA_SHARE_ADDR       (DUMP_AREA_LPM3_ADDR+DUMP_AREA_LPM3_SIZE)
#define DUMP_AREA_SHARE_SIZE       (DUMP_SIZE- DUMP_HEAD_SIZE-DUMP_AREA_MAP_SIZE-DUMP_AREA_AP_SIZE-DUMP_AREA_CP_SIZE-DUMP_AREA_LPM3_SIZE)/* 63K */
#define DUMP_AREA_SHARE_HEAD_ADDR  DUMP_AREA_SHARE_ADDR
#define DUMP_AREA_SHARE_HEAD_SIZE  0x20
#define DUMP_AREA_SHARE_MAP_ADDR   (DUMP_AREA_SHARE_HEAD_ADDR+DUMP_AREA_SHARE_HEAD_SIZE)
#define DUMP_AREA_SHARE_MAP_SIZE   (32*DUMP_FIELD_MAX_NUM)
#define DUMP_GLOBAL_INFO_ADDR      (DUMP_AREA_SHARE_MAP_ADDR+DUMP_AREA_SHARE_MAP_SIZE)
#define DUMP_GLOBAL_INFO_SIZE      0x100
#define DUMP_LOAD_INFO_ADDR        (DUMP_GLOBAL_INFO_ADDR+DUMP_GLOBAL_INFO_SIZE)
#define DUMP_LOAD_INFO_SIZE        (0x100)
#define DUMP_FASTBOOT_ADDR         (DUMP_LOAD_INFO_ADDR + DUMP_LOAD_INFO_SIZE)
#define DUMP_FASTBOOT_SIZE         0x100


/* AREA magic num */
#define DUMP_AP_MAGIC_NUM       (0x4D4D4F42)    /* 适用于V7R11C60, V7R5 */
#define DUMP_AP_MAGIC_NUM_64    (0x5D5D4F42)    /* 适用于K3V5 */
#define DUMP_CP_MAGIC_NUM       (0x4D4D4F43)
#define DUMP_LPM3_MAGIC_NUM     (0x4D4D4F44)
#define DUMP_SHARE_MAGIC_NUM    (0x4D4D4F45)

/* AREA NAME */
#define DUMP_AP_AREA_NAME       "AP"
#define DUMP_CP_AREA_NAME       "CP"
#define DUMP_LPM3_AREA_NAME     "LPM3"
#define DUMP_SHARE_AREA_NAME    "SHARE"

/* field magic num */
#define DUMP_FIELD_MAGIC_NUM    (0x6C7D9F8E)

#ifndef __ASSEMBLY__
/* dump head */
typedef struct _dump_head_s 
{
	u32 magic;
	u32 version;
	u32 area_number;
	u32 reserve;
	u8  product_name[32];   /* the pruduct name of dump data */
	u8  product_version[32];/* the pruduct version of dump data */
	u8  build_time[32];
	u32 except_core;
	u32 except_reason;
    u32 except_time;
    u32 voice;
	u8  padding1[DUMP_HEAD_SIZE - 0x80];
}dump_head_t;

/* area map */
typedef struct _dump_area_map_s 
{
	u32 offset;          /* offset from area, unit is bytes(1 bytes) */
	u32 length;          /* unit is bytes */
}dump_area_map_t;

/* area head  */
typedef struct _dump_area_head_s
{
    u32 magic_num;  
    u32 field_num;   
    u8  name[8]; 
    u8  version[16]; /* area format version */
}dump_area_head_t;

/* field map */
typedef struct _dump_field_map_s
{
    u32 field_id;
    u32 offset_addr;
    u32 length;
    u16 version;
    u16 status;
    u8  field_name[16];
}dump_field_map_t;

/* area */
typedef struct _dump_area_s
{
    dump_area_head_t  area_head;
    dump_field_map_t  fields[DUMP_FIELD_MAX_NUM];  
    u8                data[4];
}dump_area_t;
  
/* dump */
typedef struct _dump_s
{
    dump_head_t     dump_head;   
    dump_area_map_t area_info[DUMP_AREA_MAX_NUM];    
    u8              data[4];
}dump_t;

/* one field can have some hook function, called by dump framework */
typedef struct _dump_field_hook_t
{
    struct list_head hook_list;
    dump_hook        pfunc;
    char             name[16];
}dump_field_hook_t;

/* dump memory infortion in this cpu */
typedef struct dump_info_s
{
    DUMP_AREA_ID       cur_area_id;                    /* current cpu area id */
    u32                cur_field_num;                  /* current cpu registered field number   */    
    dump_field_hook_t  cur_hook_list;                  /* current cpu registered field hook list*/
    u8 *               cur_dynamic_base_addr;          /* current cpu dynamic area base address */
    u8 *               cur_dynamic_free_addr;          /* current cpu dynamic free area address */
    u32                cur_dynamic_total_size;         /* current cpu dynamic area total size   */
    u32                cur_dynamic_free_size;          /* current cpu dynamic free area size    */     
    dump_area_t*       p_cur_area;                     /* current cpu area */
    dump_t*            p_dump;                         /* dump memory */
    dump_area_t*       p_area[DUMP_AREA_MAX_NUM];      /* dump area */ 
    spinlock_t         lock;                           /* lock for protecting dump */
}dump_info_t;

#ifdef __OS_RTOSCK__
#define MAKE_FIXED_FIELD(p, id, name, base_addr, addr, size) \
{ \
    ((dump_field_map_t*)p)->field_id    = id; \
    ((dump_field_map_t*)p)->length      = size; \
    ((dump_field_map_t*)p)->offset_addr = (u32)(addr - base_addr); \
    ((dump_field_map_t*)p)->version     = 0; \
    ((dump_field_map_t*)p)->status      = DUMP_FIELD_USED; \
    (void)memcpy_s((char *)(((dump_field_map_t*)p)->field_name), 16, (char *)name, 16); \
}
#else
#define MAKE_FIXED_FIELD(p, id, name, base_addr, addr, size) \
{ \
    ((dump_field_map_t*)p)->field_id    = id; \
    ((dump_field_map_t*)p)->length      = size; \
    ((dump_field_map_t*)p)->offset_addr = (u32)(addr - base_addr); \
    ((dump_field_map_t*)p)->version     = 0; \
    ((dump_field_map_t*)p)->status      = DUMP_FIELD_USED; \
    memcpy((char *)(((dump_field_map_t*)p)->field_name), (char *)name, 16); \
}
#endif

extern dump_info_t* g_pdump_info;

#ifdef ENABLE_BUILD_OM
s32 bsp_dump_mem_init(void);
u8* bsp_dump_get_field_map(u32 field_id);
u8* bsp_dump_get_area_addr(u32 field_id);
#else
static s32 inline bsp_dump_mem_init(void)
{
    return 0;
}
static inline u8 * bsp_dump_get_field_map(u32 field_id)
{
    return 0;
}
static inline u8 * bsp_dump_get_area_addr(u32 field_id)
{
    return 0;
}
static u32 inline bsp_dump_mem_map(void)
{
    return BSP_OK;
}
#endif

#endif /*__ASSEMBLY__*/

#ifdef __cplusplus
}
#endif

#endif /* _BSP_DUMP_MEM_H */

