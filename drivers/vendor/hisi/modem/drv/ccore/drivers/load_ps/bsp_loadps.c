/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_loadps.c
*
*   描    述 :  本文件主要完成镜像的动态加载功能
*
*
*************************************************************************/
/*lint -save -e534 -e586 -e578 -e801 -e737 -e713 -e830*/

#include <sre_shell.h>
#include <sre_mem.h>
#include <sre_cache.h>
#include <sre_mmu.h>
#include <sre_symbol.h>
#include <sre_symbol_api.h>
#include <sre_callstack.h>
#include <securec.h>
#include <drv_comm.h>
#include <osl_types.h>
#include <osl_wait.h>
#include <osl_sem.h>
#include <bsp_hardtimer.h>
#include <bsp_icc.h>
#include <bsp_loadps.h>
#include <mdrv_sysboot.h>
#include "bsp_om.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*loadps调试信息*/
typedef struct __loadps_debuginfo
{
    u32 call_cnt;
    u32 send_icc_cnt;
    u32 recv_icc_cnt;
    u32 succ_cnt;
    u32 rat_mode;
    u32 load_addr;
    u32 mdrv_start_ms;
    u32 mdrv_wakeup_byacore_ms;
    u32 mdrv_SymbolTableAdd_ms;
    u32 mdrv_total_elapsed_ms;

} loadps_debuginfo;
loadps_debuginfo g_loadps_debuginfo = {0, 0, 0, 0, 0, 0};

loadps_status  g_loadps_status = {0};
/*loadps模块的动态调试功能*/
#define loadps_trace(trace_level, fmt, ...) do { \
        bsp_trace(trace_level, BSP_MODU_LOADPS,"loadps: " fmt "\n", ##__VA_ARGS__); \
} while (0)

#define LOADPS_TEXT_MMU_ATTR (OS_MMU_STATE_READ | OS_MMU_STATE_EXE | OS_MMU_STATE_CACHE_WBWA)
#define LOADPS_DATA_MMU_ATTR (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE | OS_MMU_STATE_CACHE_WBWA)

/*loadps模块的互斥信号量，表示每次只有一个任务才可以执行loadps*/
static osl_sem_id loadps_mutex;

/*挂起loadps的任务，等待直到A核的loadps工作的完成*/
static osl_sem_id loadps_wait_complete_mutex;

/*链接脚本的数据格式*/
struct ovly_addr_info {
    unsigned int addr;
    /*可加载的最大长度*/
    unsigned int size;
};

extern struct ovly_addr_info _ovly_table[];

/*rtosck操作系统的桩函数*/

unsigned int __attribute__ ((weak)) SRE_UnwindTableAdd(unsigned int uwtable_start, unsigned int uwtable_end, unsigned int text_start, unsigned int text_end)
{
        return 0;
}

unsigned int __attribute__ ((weak)) SRE_SymbolTableAdd(OS_SYMBOL_NODE_S *pSymNode, unsigned int symNum, unsigned int ovlay_start, unsigned int ovlay_end)
{
        return 0;
}

#define PAGE_SIZE 0x1000
/*****************************************************************************
 函 数 名  : mdrv_loadas
 功能描述  : 对外提供的镜像加载接口
 输入参数  : rat_mode 镜像类型
 输出参数  : 成功返回0，失败返回非0
*****************************************************************************/
int mdrv_loadas ( DRV_RAT_MODE_ENUM rat_mode )
{

    s32 ret = BSP_OK;
    loadps_msg loadps_msg;
    u32 elapsed;
    int overlay_index = 0;
    int magic =0 ;
    int page_left=0;
    struct loadps_header *pheader;
    struct ovly_addr_info *pRat_addr_info, *pOvly_addr_info;

    /*保证一次只有一个任务执行loadps*/
    osl_sem_down ( &loadps_mutex );
    g_loadps_debuginfo.call_cnt++;
    loadps_trace(BSP_LOG_LEVEL_INFO ,"rat_mode  %d\n" ,rat_mode);
    g_loadps_debuginfo.mdrv_start_ms = bsp_get_elapse_ms();

    if ((DRV_RAT_MODE_UMTS_FDD != rat_mode) && (DRV_RAT_MODE_UMTS_TDD != rat_mode))
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"rat_mode ERROR! %d\n" ,rat_mode);
        ret = -1;
        goto sem_up;
    }
    /*判断一下加载的镜像*/
    if (rat_mode == DRV_RAT_MODE_UMTS_TDD)
    {
        overlay_index = 1;
        magic = 0x00736174;
    }
    else if (rat_mode == DRV_RAT_MODE_UMTS_FDD)
    {
        overlay_index = 2;
        magic = 0x00736177;
    }
    g_loadps_debuginfo.rat_mode = rat_mode;
    pRat_addr_info  = _ovly_table + overlay_index;
    pOvly_addr_info = _ovly_table;
    (void)memset_s(&loadps_msg, sizeof(loadps_msg), 0x0, sizeof(loadps_msg));
    loadps_msg.rat_mode = rat_mode;
    /*加载到内存中的地址*/
    loadps_msg.addr = pRat_addr_info->addr;
    g_loadps_debuginfo.load_addr = loadps_msg.addr;
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps_msg.addr  0x%x\n" ,loadps_msg.addr);

    loadps_msg.size = pRat_addr_info->size;
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps_msg.size  0x%x\n" ,loadps_msg.size);

    ret = bsp_icc_send( ICC_CPU_APP, LOADPS_ICC_IFC_ID, (u8*)(&loadps_msg), sizeof(loadps_msg));

    if (sizeof(loadps_msg) != ret )
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"msg_size != ret: msg_size = 0x%x, ret = 0x%x\n", sizeof(loadps_msg), ret);
        ret = -1;
        goto sem_up;
    }
    g_loadps_debuginfo.send_icc_cnt++;
    /*把任务挂起,等待A核把镜像搬运的工作完成*/
    osl_sem_down ( &loadps_wait_complete_mutex );

    /*C核的任务被唤醒后执行*/
    g_loadps_debuginfo.recv_icc_cnt++;
    g_loadps_debuginfo.mdrv_wakeup_byacore_ms = bsp_get_elapse_ms();
    elapsed = g_loadps_debuginfo.mdrv_wakeup_byacore_ms - g_loadps_debuginfo.mdrv_start_ms;

    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps result = 0x%x and icc complete time %d ms\n", g_loadps_status.result,elapsed);
    ret = g_loadps_status.result;
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"loadps result = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps SRE_ICacheInv addr = 0x%x  size= 0x %x\n", pOvly_addr_info->addr, pOvly_addr_info->size);
    ret = SRE_ICacheInv((VOID *)pOvly_addr_info->addr, (UINT32)pOvly_addr_info->size, TRUE);
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"SRE_ICacheInv error = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps SRE_DCacheInv addr = 0x%x  size= 0x %x\n", pOvly_addr_info->addr, pOvly_addr_info->size);
    ret = SRE_DCacheInv((VOID *)pOvly_addr_info->addr, (UINT32)pOvly_addr_info->size, TRUE);
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"SRE_DCacheInv error = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }
    pheader = (struct loadps_header *)pRat_addr_info->addr;

    if (pheader->magic != magic)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"pheader->magic error = 0x%x\n", pheader->magic);
        ret = -1;
        goto sem_up;
    }
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps pheader->text_start= 0x%x  pheader->text_size= 0x %x\n", pheader->text_start, pheader->text_size);
    /*设置代码段只读可执行属性*/
    ret = SRE_MmuStateSet(pheader->text_start, pheader->text_size, 0, LOADPS_TEXT_MMU_ATTR);
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"SRE_MmuStateSet TEXT error = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }
    loadps_trace(BSP_LOG_LEVEL_INFO,"loadps pheader->data_start= 0x%x  pheader->data_size= 0x %x\n", pheader->data_start, pheader->data_size);
    if( pheader->data_size % PAGE_SIZE)
    {
        page_left = pheader->data_size % PAGE_SIZE;
        page_left = PAGE_SIZE - page_left;

    }
    /*设置数据段可读写属性*/
    ret = SRE_MmuStateSet(pheader->data_start, pheader->data_size+page_left, 0, LOADPS_DATA_MMU_ATTR);
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"SRE_MmuStateSet data error = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps pheader->bss_start= 0x%x  pheader->bss_size= 0x %x\n", pheader->bss_start, pheader->bss_size);
    /*清除bss段的内容*/
    memset_s((void*)pheader->bss_start, pheader->bss_size, 0x0, pheader->bss_size);

    /*Unwind信息的添加，方便打印私有镜像的调用栈信息*/
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps pheader->unwind_start= 0x%x  pheader->unwind_size= 0x %x\n", pheader->unwind_start, pheader->unwind_size);
    ret = SRE_UnwindTableAdd(pheader->unwind_start, pheader->unwind_start + pheader->unwind_size,\
                          pheader->text_start, pheader->text_start + pheader->text_size);
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"SRE_UnwindTableAdd error = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }
    /*符号表信息增加*/
    loadps_trace(BSP_LOG_LEVEL_INFO ,"loadps pheader->symbol_start= 0x%x  pheader->symbol_size= 0x %x\n", pheader->symbol_start, (pheader->symbol_size)/sizeof(OS_SYMBOL_NODE_S));
    /* Add Symbol table for this overlay section */
    ret = SRE_SymbolTableAdd((OS_SYMBOL_NODE_S*)pheader->symbol_start, (pheader->symbol_size)/sizeof(OS_SYMBOL_NODE_S), \
                          pRat_addr_info->addr, pRat_addr_info->addr + pRat_addr_info->size);
    if(ret != 0)
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"SRE_SymbolTableAdd error = 0x%x\n", ret);
        ret = -1;
        goto sem_up;
    }

sem_up:
    osl_sem_up ( &loadps_mutex );
    g_loadps_debuginfo.mdrv_SymbolTableAdd_ms = bsp_get_elapse_ms();
    elapsed = g_loadps_debuginfo.mdrv_SymbolTableAdd_ms - g_loadps_debuginfo.mdrv_start_ms;
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"loadps total load time %d ms ret = %d\n", elapsed, ret);
    g_loadps_debuginfo.mdrv_total_elapsed_ms = elapsed;
    if(!ret)
    {
        g_loadps_debuginfo.succ_cnt++;
    }
    return ret;
}

/*****************************************************************************
 函 数 名  : bsp_loadps_ccore_callback
 功能描述  : loadps的C核的ICC消息回调函数
 输入参数  : channel_id  ICC通道号
 输出参数  : 成功返回0，失败返回非0
*****************************************************************************/
s32 bsp_loadps_ccore_callback ( u32 channel_id , u32 len, void* context )
{
    s32 read_len = 0;
    /*参数判断*/
    if ( channel_id != LOADPS_ICC_IFC_ID )
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"loadps icc channel error: channel_id = 0x%x, LOADPS_ICC_IFC_ID = 0x%x\n", channel_id, LOADPS_ICC_IFC_ID);
        return -1;
    }
    /*把A核发生的icc消息读出来查看*/
    read_len = bsp_icc_read( LOADPS_ICC_IFC_ID, (u8*)(&g_loadps_status), sizeof(loadps_status));
    if ( read_len != sizeof(loadps_status))
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"read_len != msg_size: read_len = 0x%x, msg_size = 0x%x\n", read_len, sizeof(loadps_status));
        return -1;
    }
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"bsp_loadps_ccore_callback \n");
    osl_sem_up(&loadps_wait_complete_mutex);

    return 0;
}

void bsp_loadps_debug(void)
{
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"call count is 0x%x\n", g_loadps_debuginfo.call_cnt);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"send count is 0x%x\n", g_loadps_debuginfo.send_icc_cnt);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"recv count is 0x%x\n", g_loadps_debuginfo.recv_icc_cnt);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"succ count is 0x%x\n", g_loadps_debuginfo.succ_cnt);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"rat  mode  is 0x%x\n", g_loadps_debuginfo.rat_mode);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"load_addr  is 0x%x\n",  g_loadps_debuginfo.load_addr);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"mdrv_start_ms  is 0x%x ms\n",  g_loadps_debuginfo.mdrv_start_ms);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"mdrv_wakeup_byacore_ms  is 0x%x ms\n",  g_loadps_debuginfo.mdrv_wakeup_byacore_ms);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"mdrv_SymbolTableAdd_ms  is 0x%x ms\n",  g_loadps_debuginfo.mdrv_SymbolTableAdd_ms);
    loadps_trace(BSP_LOG_LEVEL_ERROR ,"mdrv_total_elapsed_ms  is 0x%x ms\n",   g_loadps_debuginfo.mdrv_total_elapsed_ms);
}
/*****************************************************************************
 函 数 名  : bsp_loadps_ccore_init
 功能描述  : loadps的C核的初始化函数
 输入参数  : 无
 输出参数  : 成功返回0，失败返回非0
*****************************************************************************/
s32 bsp_loadps_ccore_init(void)
{
    s32 ret = 0;
    struct ovly_addr_info *pOvly_addr_info;
    /*设置一下loadps模块的打印级别函数*/
    bsp_mod_level_set(BSP_MODU_LOADPS,BSP_LOADPS_LOG_LEVEL);
    loadps_trace(BSP_LOG_LEVEL_INFO ,"bsp_loadps_ccore_init start\n");
    osl_sem_init ( 1, &loadps_mutex);
    osl_sem_init ( 0, &loadps_wait_complete_mutex);
    pOvly_addr_info = _ovly_table;
    (void)memset_s((void *)pOvly_addr_info->addr, pOvly_addr_info->size, 0x0, pOvly_addr_info->size);
    (void)memset_s((void *)&g_loadps_debuginfo, sizeof (loadps_debuginfo), 0x0, sizeof (loadps_debuginfo));
    ret = bsp_icc_event_register (LOADPS_ICC_IFC_ID, bsp_loadps_ccore_callback, NULL, NULL, NULL );
    if ( ret )
    {
        loadps_trace(BSP_LOG_LEVEL_ERROR ,"bsp_icc_event_register error, ret = 0x%x\n", ret);
        return ret;
    }
    loadps_trace(BSP_LOG_LEVEL_INFO ,"bsp_loadps_ccore_init complete\n");
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*lint -restore*/

