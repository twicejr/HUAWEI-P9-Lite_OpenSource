/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dump_mem.c
*
*   作    者 :  l00169177
*
*   描    述 :  临终遗言内存操作功能
*
*   修改记录 :  2014年06月11日  v1.00  l00169177  创建
*************************************************************************/
/*lint --e{830}*/
#ifdef __KERNEL__
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#elif defined( __VXWORKS__)||defined(__OS_RTOSCK__)
#include <of.h>
#include "securec.h"
#elif defined(__CMSIS_RTOS)
#include <libfdt.h>
#endif
#include "bsp_dump_mem.h"
#include "osl_malloc.h"
#include "bsp_version.h"
#include "bsp_shared_ddr.h"

/* dump memory information */
dump_info_t* g_pdump_info = 0;
void*        g_pdump_backup_addr  = 0;
dump_mem_ctrl_t g_dump_mem_ctrl;
#if defined( __VXWORKS__)||defined(__OS_RTOSCK__)
void*        g_pOsaLogTmp;
void*        g_pWasLogTmp;
/*lint -save -e124*/

void bsp_dump_mem_debug_init(void)
{
    g_pOsaLogTmp  = (void*)(SHM_BASE_ADDR+SHM_OFFSET_OSA_LOG);
    g_pWasLogTmp  = (void*)(SHM_BASE_ADDR+SHM_OFFSET_WAS_LOG);
    (void)SRE_Printf("====g_pOsaLogTmp=0x%x, g_pWasLogTmp=0x%x\n", g_pOsaLogTmp, g_pWasLogTmp);
}
/*lint -restore +e124*/


#endif

extern void dump_map_init(void);

/* 验证field_id是否合法，异常id返回BSP_ERROR，正常id返回area id */
static s32 dump_verify_field_id(u32 field_id)
{
    s32 ret;

    if(((field_id>=DUMP_AP_FIELD_BEGIN) && (field_id<DUMP_AP_FIELD_END)) ||  ((field_id>=OM_AP_FIELD_BEGIN) && (field_id<OM_AP_FIELD_END)))
    {
        ret = DUMP_AREA_AP;
    }
    else if(((field_id>=DUMP_CP_FIELD_BEGIN) && (field_id<DUMP_CP_FIELD_END)) || ((field_id>=OM_CP_FIELD_BEGIN) && (field_id<OM_CP_FIELD_END)))
    {
        ret = DUMP_AREA_CP;
    }
    else if((field_id>=DUMP_M3_FIELD_BEGIN) && (field_id<DUMP_M3_FIELD_END))
    {
        ret = DUMP_AREA_LPM3;
    }
    else if((field_id>=DUMP_SHARE_FIELD_BEGIN) && (field_id<DUMP_SHARE_FIELD_END))
    {
        ret = DUMP_AREA_SHARE;
    }
    else
    {
#ifndef __CMSIS_RTOS
        (void)printk("%s:invalid field id 0x%x\n", __FUNCTION__, (u32)field_id);
#endif
        ret = BSP_ERROR;
    }

    return ret;
}

static s32 bsp_dump_mem_map(void)
{
    g_dump_mem_ctrl.smntn_phy_addr  = DDR_MNTN_ADDR;
	g_dump_mem_ctrl.smntn_mem_size  = DDR_MNTN_SIZE;
#ifdef __CMSIS_RTOS
    g_dump_mem_ctrl.smntn_virt_addr = DDR_MNTN_ADDR_VIRT;

#else

    g_dump_mem_ctrl.smntn_virt_addr = (unsigned long)ioremap_wc((void*)g_dump_mem_ctrl.smntn_phy_addr, g_dump_mem_ctrl.smntn_mem_size);
#endif


    if(g_dump_mem_ctrl.smntn_virt_addr == 0)
    {
        return BSP_ERROR;
    }

    return BSP_OK;
}

/* initialize dump memory
   this function should be called before other dump function */
/*lint -save -e438 -e529 */
s32 bsp_dump_mem_init(void)
{
    s32 ret = 0;
    char* str_tmp = 0;
    dump_info_t* pdump_info = 0;

    str_tmp = str_tmp;

    if(g_pdump_info != 0)
    {
        return BSP_OK;
    }

    ret = bsp_dump_mem_map();
    if(ret != BSP_OK)
    {
#ifndef __CMSIS_RTOS
        (void)printk("%s dump memory map fail\n", __FUNCTION__);
#endif
        return BSP_ERROR;
    }

#ifdef __KERNEL__
    /* 拷贝DUMP内存到备份区 */
    g_pdump_backup_addr = osl_malloc(DUMP_SIZE);
    if(g_pdump_backup_addr == NULL)
    {
        printk("dump err:alloc backup addr fail\n");
        return BSP_ERROR;
    }
    memcpy(g_pdump_backup_addr,(void*)DUMP_ADDR, DUMP_SIZE);
#endif

    pdump_info = (dump_info_t*)osl_malloc(sizeof(dump_info_t));
    if(pdump_info == NULL)
    {
#ifndef __CMSIS_RTOS
        (void)printk("%s malloc fail\n", __FUNCTION__);
#endif
        return BSP_ERROR;
    }
#ifdef __OS_RTOSCK__
    (void)memset_s(pdump_info,sizeof(dump_info_t) ,0, sizeof(dump_info_t));
#else
    memset(pdump_info,0, sizeof(dump_info_t));
#endif
    pdump_info->p_dump = (dump_t*)DUMP_ADDR;
    pdump_info->p_area[DUMP_AREA_AP] = (dump_area_t*)DUMP_AREA_AP_ADDR;
    pdump_info->p_area[DUMP_AREA_CP] = (dump_area_t*)DUMP_AREA_CP_ADDR;
    pdump_info->p_area[DUMP_AREA_LPM3] = (dump_area_t*)DUMP_AREA_LPM3_ADDR;
    pdump_info->p_area[DUMP_AREA_SHARE]= (dump_area_t*)DUMP_AREA_SHARE_ADDR;

#ifdef __KERNEL__
    pdump_info->cur_area_id            = DUMP_AREA_AP;
    pdump_info->cur_dynamic_base_addr  = (u8 *)DUMP_AREA_AP_DYNAMIC_ADDR;
    pdump_info->cur_dynamic_total_size = DUMP_AREA_AP_DYNAMIC_SIZE;
    pdump_info->p_cur_area             = (dump_area_t*)DUMP_AREA_AP_ADDR;

    /* AP is the main cpu, intialize dump head */
    memset(&pdump_info->p_dump->dump_head,0, sizeof(dump_head_t));
    pdump_info->p_dump->dump_head.magic       = DUMP_MAGIC;
    pdump_info->p_dump->dump_head.area_number = DUMP_AREA_BUTT;

    /* reset AP area */
    memset((void *)DUMP_AREA_AP_ADDR, 0, DUMP_AREA_AP_SIZE);

    str_tmp = (char*)bsp_version_get_chip();
    if(str_tmp)
    {
        /* coverity[buffer_size_warning] */
        strncpy((char*)pdump_info->p_dump->dump_head.product_name, str_tmp, 32);
    }

    str_tmp = (char*)bsp_version_get_release();
    if(str_tmp)
    {

        /* coverity[buffer_size_warning] */
        strncpy((char*)pdump_info->p_dump->dump_head.product_version, str_tmp, 32);
    }

    str_tmp = (char*)bsp_version_get_build_date_time();
    if(str_tmp)
    {

        /* coverity[buffer_size_warning] */
        strncpy((char*)pdump_info->p_dump->dump_head.build_time, str_tmp, 32);
    }

    /* AP is the main cpu, intialize dump area map */
    memset(&pdump_info->p_dump->area_info[0], 0, sizeof(dump_area_map_t)*DUMP_AREA_MAX_NUM);
    pdump_info->p_dump->area_info[DUMP_AREA_AP].offset   = DUMP_AREA_AP_ADDR - DUMP_ADDR;
    pdump_info->p_dump->area_info[DUMP_AREA_AP].length   = DUMP_AREA_AP_SIZE;
    pdump_info->p_dump->area_info[DUMP_AREA_CP].offset   = DUMP_AREA_CP_ADDR - DUMP_ADDR;
    pdump_info->p_dump->area_info[DUMP_AREA_CP].length   = DUMP_AREA_CP_SIZE;
    pdump_info->p_dump->area_info[DUMP_AREA_LPM3].offset = DUMP_AREA_LPM3_ADDR - DUMP_ADDR;
    pdump_info->p_dump->area_info[DUMP_AREA_LPM3].length = DUMP_AREA_LPM3_SIZE;
    pdump_info->p_dump->area_info[DUMP_AREA_SHARE].offset= DUMP_AREA_SHARE_ADDR - DUMP_ADDR;
    pdump_info->p_dump->area_info[DUMP_AREA_SHARE].length= DUMP_AREA_SHARE_SIZE;

#elif defined( __VXWORKS__)||defined(__OS_RTOSCK__)
    pdump_info->cur_area_id            = DUMP_AREA_CP;
    pdump_info->cur_dynamic_base_addr  = (u8 *)DUMP_AREA_CP_DYNAMIC_ADDR;
    pdump_info->cur_dynamic_total_size = DUMP_AREA_CP_DYNAMIC_SIZE;
    pdump_info->p_cur_area             = (dump_area_t*)DUMP_AREA_CP_ADDR;
    /* reset CP area */
    (void)memset_s((void *)DUMP_AREA_CP_ADDR, DUMP_AREA_CP_SIZE, 0, DUMP_AREA_CP_SIZE);
#elif defined(__CMSIS_RTOS)
    pdump_info->cur_area_id            = DUMP_AREA_LPM3;
    pdump_info->cur_dynamic_base_addr  = (u8 *)DUMP_AREA_LPM3_DYNAMIC_ADDR;
    pdump_info->cur_dynamic_total_size = DUMP_AREA_LPM3_DYNAMIC_SIZE;
    pdump_info->p_cur_area             = (dump_area_t*)DUMP_AREA_LPM3_ADDR;
    /* reset LPM3 area */
    memset((void *)DUMP_AREA_LPM3_ADDR, 0, DUMP_AREA_LPM3_SIZE);
#endif

    pdump_info->cur_field_num = 0;
    pdump_info->cur_hook_list.hook_list.prev = &pdump_info->cur_hook_list.hook_list;
    pdump_info->cur_hook_list.hook_list.next = &pdump_info->cur_hook_list.hook_list;
    pdump_info->cur_dynamic_free_addr    = pdump_info->cur_dynamic_base_addr;
    pdump_info->cur_dynamic_free_size    = pdump_info->cur_dynamic_total_size;

    spin_lock_init(&pdump_info->lock);

    g_pdump_info = pdump_info;

    dump_map_init();

    return BSP_OK;
}
/*lint -restore*/

/* register field hook in dump hook list */
dump_handle bsp_dump_register_hook(char * name, dump_hook func)
{
    dump_field_hook_t* pfieldhook = NULL;
    unsigned long flags = 0;/* [false alarm]:fortify */
    int i;/* [false alarm]:fortify */
    flags = flags;/* [false alarm]:fortify */

    if(g_pdump_info == 0)
    {
        (void)bsp_dump_mem_init();

    }

    pfieldhook = (dump_field_hook_t*)osl_malloc(sizeof(dump_field_hook_t));
    if(pfieldhook == NULL)
    {
        return BSP_ERROR;
    }

    pfieldhook->pfunc = func;
    for(i=0; i<15; i++)
    {
        pfieldhook->name[i] = *(name+i);/* [false alarm]:fortify */
        if(*(name+i) == '\0')
        {
            break;
        }
    }
    pfieldhook->name[i] = '\0';/* [false alarm]:fortify */

    spin_lock_irqsave(&g_pdump_info->lock, flags);
    list_add(&pfieldhook->hook_list, &g_pdump_info->cur_hook_list.hook_list);
    spin_unlock_irqrestore(&g_pdump_info->lock, flags);

    return (dump_handle)((unsigned long)pfieldhook);
}

#ifndef __CMSIS_RTOS
s32 bsp_dump_unregister_hook(dump_handle handle)
{
    dump_field_hook_t * pfieldhook= NULL;/* [false alarm]:fortify */
    dump_field_hook_t * hook_node = NULL;/* [false alarm]:fortify */
    unsigned long flags = 0;/* [false alarm]:fortify */
    flags = flags;/* [false alarm]:fortify */

    if(handle == 0)
    {
        return BSP_ERROR;
    }

    spin_lock_irqsave(&g_pdump_info->lock, flags);
    /*lint -save -e10 -e26 -e64 -e718 -e746 -e413 -e666*/
    list_for_each_entry(pfieldhook, &g_pdump_info->cur_hook_list.hook_list, hook_list)
    {
        if((dump_handle)((unsigned long)pfieldhook) == handle)
        {
            hook_node = pfieldhook;
        }
    }
    /*lint -restore*/

    if(hook_node == NULL)
    {
        spin_unlock_irqrestore(&g_pdump_info->lock, flags);
        return BSP_ERROR;
    }

    list_del(&hook_node->hook_list);
    osl_free(hook_node);
    spin_unlock_irqrestore(&g_pdump_info->lock, flags);

    return BSP_OK;
}
#endif

/* register field in current core area
 * 1. 不带地址注册，传入参数时virt_addr,phy_addr必须传0，成功返回dump注册地址
 * 2. 自带地址注册，传入参数时phy_addr为自带物理地址，virt_addr为虚拟地址，同时在dump内存中分配相同大小内存，成功返回邋virt_addr
 * PS:
 * 1. 两种注册方式，都将在dump划分内存，对于自带地址的注册方式，在系统异常时，由dump模块做数据拷贝
 * 2. 每个注册区域需要由使用者传入对应的版本号，高8位为主版本号，低8位为次版本号
 */
u8 * bsp_dump_register_field(u32 field_id, char * name, void * virt_addr, void * phy_addr, u32 length, u16 version)
{
    u32 i = 0;/* [false alarm]:fortify */
    u8 * p_addr = NULL;/* [false alarm]:fortify */
    unsigned long flags = 0;/* [false alarm]:fortify */
    dump_area_t* p_area = NULL;/* [false alarm]:fortify */
    unsigned long * f_data = NULL;/* [false alarm]:fortify */

    flags = flags;

    if(g_pdump_info == 0)
    {
        (void)bsp_dump_mem_init();
    }

    if((length == 0) || ((virt_addr != NULL || phy_addr != NULL) && (length < 3*sizeof(unsigned long))))
    {
#ifndef __CMSIS_RTOS
        (void)printk("%s: invalid len 0x%x or addr %p %p\n", __FUNCTION__, length, virt_addr, phy_addr);
#endif
        return BSP_NULL;
    }

    if(BSP_ERROR == dump_verify_field_id(field_id))
    {
#ifndef __CMSIS_RTOS      
        (void)printk("%s:invalid field id 0x%x,register fail\n", __FUNCTION__, field_id);
#endif
        return BSP_NULL;
    }

    p_area = (dump_area_t*)(g_pdump_info->p_cur_area);

    spin_lock_irqsave(&g_pdump_info->lock, flags);

    /* can't regitster if this field has been regitstered, return this field address only */
    for(i=0; i<g_pdump_info->cur_field_num; i++)
    {
        if(p_area->fields[i].field_id == field_id)
        {
            if(p_area->fields[i].length != length)
            {
#ifndef __CMSIS_RTOS
                 (void)printk("%s:field registered,len not equal,old:0x%x,new:0x%x\n", 
                    __FUNCTION__,  p_area->fields[i].length, length);
#endif
            }

            spin_unlock_irqrestore(&g_pdump_info->lock, flags);
            return (u8*)((u8 *)p_area + p_area->fields[i].offset_addr);
        }
    }

    /* judge if this field can be registered */
    if(((g_pdump_info->cur_field_num == DUMP_FIELD_MAX_NUM)
        || (g_pdump_info->cur_dynamic_free_size) <= length ))
    {
        spin_unlock_irqrestore(&g_pdump_info->lock, flags);
#ifndef __CMSIS_RTOS
        (void)printk("%s:no more space(left:0x%x,alloc len:0x%x)\n", __FUNCTION__, g_pdump_info->cur_dynamic_free_size, length);
#endif
        return BSP_NULL;
    }

    p_addr = g_pdump_info->cur_dynamic_free_addr;

    /* fill field information */
    p_area->fields[g_pdump_info->cur_field_num].field_id    = field_id;
    p_area->fields[g_pdump_info->cur_field_num].offset_addr = (unsigned long)(g_pdump_info->cur_dynamic_free_addr - (u8 *)p_area);
    p_area->fields[g_pdump_info->cur_field_num].length      = length;
    p_area->fields[g_pdump_info->cur_field_num].status      = DUMP_FIELD_USED;
    p_area->fields[g_pdump_info->cur_field_num].version     = version;
    /* save field name */
    for(i=0; i<15; i++)
    {
        p_area->fields[g_pdump_info->cur_field_num].field_name[i] =(u8)(*(name+i));
        if(*(name+i) == (char)'\0')
        {
            break;
        }
    }
    p_area->fields[g_pdump_info->cur_field_num].field_name[i] = '\0';

    /* save user address in register field */
    f_data    = (unsigned long *)((u8 *)p_area + p_area->fields[g_pdump_info->cur_field_num].offset_addr);
    *f_data++ = (virt_addr != NULL || phy_addr != NULL) ? DUMP_FIELD_MAGIC_NUM : 0;
    *f_data++ = (unsigned long)virt_addr;
    *f_data++ = (unsigned long)phy_addr;

    /* update dynamic area info in this cpu area */
    g_pdump_info->cur_field_num ++;
    g_pdump_info->cur_dynamic_free_addr = g_pdump_info->cur_dynamic_free_addr + length;
    g_pdump_info->cur_dynamic_free_size = g_pdump_info->cur_dynamic_free_size - length;

    /* update area head information */
    p_area->area_head.field_num = g_pdump_info->cur_field_num ;

    spin_unlock_irqrestore(&g_pdump_info->lock, flags);

    if(virt_addr != NULL || phy_addr != NULL)
    {
        return (u8 *)virt_addr;
    }

    return (u8 *)p_addr;
}

/* get area adddress by mod id */
/* get all cpu area address, not just this cpu */
u8 * bsp_dump_get_area_addr(u32 field_id)
{
    DUMP_AREA_ID area_id ;
    dump_area_head_t * parea_head;

    if(g_pdump_info == 0)
    {
        return BSP_NULL;
    }

    area_id = (DUMP_AREA_ID)dump_verify_field_id(field_id);
    if(BSP_ERROR == area_id)
    {
        return BSP_NULL;
    }

    parea_head = &(g_pdump_info->p_area[area_id])->area_head;
    if((area_id == DUMP_AREA_AP) && (parea_head->magic_num !=DUMP_AP_MAGIC_NUM)&&(parea_head->magic_num != DUMP_AP_MAGIC_NUM_64))
    {
        return BSP_NULL;
    }

    if((area_id == DUMP_AREA_CP) && (parea_head->magic_num != DUMP_CP_MAGIC_NUM))
    {
        return BSP_NULL;
    }

    if((area_id == DUMP_AREA_LPM3) && (parea_head->magic_num != DUMP_LPM3_MAGIC_NUM))
    {
        return BSP_NULL;
    }

    return ((u8 *)g_pdump_info->p_dump + g_pdump_info->p_dump->area_info[area_id].offset);
}

/* get field address by mod id, return 0 if failed */
/* get all cpu field address, not just this cpu */
u8 * bsp_dump_get_field_addr(u32 field_id)
{
    u32 i;
    u8 * addr = 0;
    dump_area_t * parea = (dump_area_t*)bsp_dump_get_area_addr(field_id);

    if(BSP_NULL == parea)
    {
        return BSP_NULL;
    }

    /* search field addr by field id */
    for(i=0; i<parea->area_head.field_num; i++)
    {
        if(field_id == parea->fields[i].field_id)
        {
            addr = (u8 *)parea + parea->fields[i].offset_addr;
            break;
        }
    }

    return addr;
}


#ifndef __CMSIS_RTOS
/* get field map information by mode id, return 0 if failed */
u8 * bsp_dump_get_field_map(u32 field_id)
{
    u32 i;
    dump_area_t *parea = (dump_area_t*)bsp_dump_get_area_addr(field_id);

    if(BSP_NULL == parea)
    {
        return BSP_NULL;
    }

    /* search field map by field id */
    for(i=0; i<parea->area_head.field_num; i++)
    {
        if(field_id == parea->fields[i].field_id)
        {
            return (u8 * )&parea->fields[i];
        }
    }

    return BSP_NULL;
}

u8 * bsp_dump_get_field_phy_addr(u32 field_id)
{
    u8 * addr = 0;

    addr = bsp_dump_get_field_addr(field_id);
    if(BSP_NULL == addr)
    {
        return BSP_NULL;
    }

    return (u8 *)((unsigned long)addr - g_dump_mem_ctrl.smntn_virt_addr + g_dump_mem_ctrl.smntn_phy_addr);
}

/* print dump area fields infomation by area id */
s32 bsp_dump_show_area(DUMP_AREA_ID area_id)
{
    u32 i = 0;
    u8*  pcontent = NULL;
    dump_area_t* parea = BSP_NULL;

    if(area_id >= DUMP_AREA_BUTT)
    {
        (void)printk("unknown area id!\n");
        return (s32)(-1);
    }

    if(g_pdump_info == 0)
    {
        (void)printk("dump memory uninit\n");
        return (s32)(-1);
    }

    parea = (dump_area_t*)((u8 *)g_pdump_info->p_dump + g_pdump_info->p_dump->area_info[area_id].offset);

    (void)printk("======%d DUMP AREA INFO==========\n", area_id);
    (void)printk("==Dump area head info:===========\n");
    (void)printk("magic number: 0x%X\n", parea->area_head.magic_num);
    (void)printk("field number: 0x%X\n", parea->area_head.field_num);
    (void)printk("name        : %s\n",   parea->area_head.name);
    (void)printk("version     : %s\n",   parea->area_head.version);
    (void)printk("==Dump area fields info:======================================================\n");
    for(i=0; i<parea->area_head.field_num; i++)
    {
        pcontent = (u8*)parea->data + parea->fields[i].offset_addr;

        (void)printk("Index:%3d, field id: 0x%8X, offset addr: 0x%8X, length: 0x%8X, status: 0x%X, ",
            i, parea->fields[i].field_id, parea->fields[i].offset_addr, parea->fields[i].length, parea->fields[i].status);
        (void)printk("content: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ...\n", pcontent[0], pcontent[1],
            pcontent[2], pcontent[3], pcontent[4], pcontent[5], pcontent[6], pcontent[7],pcontent[8], pcontent[9],
            pcontent[10], pcontent[11], pcontent[12], pcontent[13], pcontent[14], pcontent[15]);
    }

    return 0;
}

/* print extension hook list */
s32 bsp_dump_show_exthook(void)
{
    struct list_head* cur = NULL;
    dump_field_hook_t* pfieldhook = NULL;

    (void)printk("===Area Hook Function List===\n");
    list_for_each(cur, &g_pdump_info->cur_hook_list.hook_list)
    {
        pfieldhook = list_entry(cur, dump_field_hook_t, hook_list);

        if(pfieldhook->pfunc)
        {
            (void)printk("name=%s,Function Addr=%p\n", pfieldhook->name, pfieldhook->pfunc);
        }
    }

    return 0;
}
#endif

#ifdef __KERNEL__
arch_initcall_sync(bsp_dump_mem_init);
#endif


