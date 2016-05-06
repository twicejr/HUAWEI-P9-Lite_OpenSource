
#ifdef __cplusplus
extern "C" {
#endif
#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"
#include "osl_sem.h"
#include "osl_module.h"

#include "bsp_edma.h"
#include "osl_thread.h"
#include <osl_cache.h>
#include <osl_malloc.h>

/*typedef u32 edma_addr_t;*//*redefine --bsp_edma.h*/
#define EDMA_NONE 0
#define GFP_DMA EDMA_NONE
#define __GFP_WAIT EDMA_NONE

#define EDMA_MEMORY  EDMA_PWC_LDSP_TCM
#define EDMA_M2M_TEST_LENGHT  (64*1024-1)

void edma_clear_data(u8 * pucBuffer, u32 ulSize);
s32 edma_verify_data(u8 * pucBuffer, u32 ulSize, u8 ucFirstData);
void edma_buff_exit(void);
s32 edmac_test_lli(enum edma_req_id req, u32 direction);
s32 edmac_test_all_func(void);
s32 edma_test(enum edma_req_id req_id, u32 size, u32 bst_width, u32 bst_len, s32 vec_flag);
void edma_isr_sema_give(void);

void * dma_alloc_coherent(void* none, u32 size, edma_addr_t *handle, u32 none2)
{
    void * memory;
    memory = osl_cachedma_malloc(size);
    *handle = (edma_addr_t)memory;
    return memory;
}
void dma_free_coherent(void* none, u32 size, void *cpu_addr, edma_addr_t handle)
{
    osl_cachedma_free(cpu_addr);
}



char *src_buf = NULL;
char *des_buf = NULL;
edma_addr_t  edma_src_addr  = 0;
edma_addr_t  edma_des_addr  = 0;


void edma_test_init(void)
{
    src_buf= (char*)dma_alloc_coherent(NULL,EDMA_M2M_TEST_LENGHT * sizeof(char*),&edma_src_addr, GFP_DMA|__GFP_WAIT);
    if(!src_buf){
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"test init alloc src faild \n");
        return;
    }
    des_buf= (char*)dma_alloc_coherent(NULL,EDMA_M2M_TEST_LENGHT * sizeof(char*),&edma_des_addr, GFP_DMA|__GFP_WAIT);
    if(!des_buf){
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"test init alloc src faild \n");
        dma_free_coherent(NULL,EDMA_M2M_TEST_LENGHT * sizeof(char*),(void*)src_buf, edma_src_addr);
        return;
    }
}
void edma_test_exit(void)
{
    if(src_buf)
        dma_free_coherent(NULL,EDMA_M2M_TEST_LENGHT * sizeof(char*),(void*)src_buf, edma_src_addr);
    if(des_buf)
        dma_free_coherent(NULL,EDMA_M2M_TEST_LENGHT * sizeof(char*),(void*)des_buf, edma_des_addr);
    src_buf = NULL;
    des_buf = NULL;
}

s32 edmac_verify_data_blk(char* verify_src_buf, char* verify_des_buf)
{
    s32 count = EDMA_M2M_TEST_LENGHT;
    char *temp_src = verify_src_buf;
    char *temp_des = verify_des_buf;
    while (count--)
    {
        if (*temp_des++ != *temp_src++)
        {
            hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----edma_verify_data failed!----index=%d\n", (EDMA_M2M_TEST_LENGHT - count));
            return EDMA_TRXFER_ERROR;
        }
    }
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG," ---des_buf =%c%c%c%c%c%c%c\n",  *((char*)verify_des_buf + 0),
            *((char*)verify_des_buf + 1), *((char*)verify_des_buf + 2), *((char*)verify_des_buf + 3),
            *((char*)verify_des_buf + 4), *((char*)verify_des_buf + 5), *((char*)verify_des_buf + 6));
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"-----edma_verify_data SUCCESS!\n");
    return EDMA_SUCCESS;
}

/* M2M  sync_trans. do not need isr_func. wait for semaphore of the edma completion  ---in acore
   or async_trans. wait untill the channel is not busy     --- in c core */
s32 edmac_test_channel(enum edma_req_id req, u32 direction)
{
    s32    ret_id = 0;
    u32 bur_width = 2;
    u32 bur_len = 3;
    u32 byte_len = EDMA_M2M_TEST_LENGHT;
    char  *temp = NULL;
    s32    count = 0;
    if((NULL == src_buf) || (NULL == des_buf))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----------edma test not inited \n\n");
        return EDMA_FAIL;
    }

    temp = src_buf;
    while (count < EDMA_M2M_TEST_LENGHT)
    {
        *temp++ = 'a' + count%20;
        ++count;
    }
    src_buf[EDMA_M2M_TEST_LENGHT - 1]='\0';

    temp = des_buf;
    count = 0;
    while (count < EDMA_M2M_TEST_LENGHT)
    {
        *temp++ = 'b' + count%20;
        ++count;
    }
    des_buf[EDMA_M2M_TEST_LENGHT - 1]='\0';

    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---src_buf =%c%c%c%c%c%c%c\n",  *((char*)src_buf + 0),
                    *((char*)src_buf + 1), *((char*)src_buf + 2), *((char*)src_buf + 3),
                    *((char*)src_buf + 4), *((char*)src_buf + 5), *((char*)src_buf + 6));
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---des_buf =%c%c%c%c%c%c%c\n",  *((char*)des_buf + 0),
                    *((char*)des_buf + 1), *((char*)des_buf + 2), *((char*)des_buf + 3),
                    *((char*)des_buf + 4), *((char*)des_buf + 5), *((char*)des_buf + 6));

    ret_id = bsp_edma_channel_init(req, NULL, 0, 0);
    if (ret_id < 0)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------error ret_id = 0x%X\n\n",ret_id);
        return EDMA_CHANNEL_INVALID;
    }

    /* set config reg */
    if (bsp_edma_channel_set_config((u32)ret_id, direction, bur_width, bur_len))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------bsp_edma_channel_set_config failed!\n\n");
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_CONFIG_ERROR;
    }

    if (bsp_edma_channel_start((u32)ret_id, (u32)edma_src_addr, (u32)edma_des_addr , byte_len))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------bsp_edma_channel_start FAILED!\n\n");
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_TRXFER_ERROR;
    }
    while(0==bsp_edma_channel_is_idle((u32) ret_id))
    {;}
    
    bsp_edma_channel_free((u32)ret_id);

    if(edmac_verify_data_blk(src_buf,des_buf))
    {
        return EDMA_TRXFER_ERROR;
    }
    hiedmac_trace(BSP_LOG_LEVEL_CRIT,"=============== EDMA_CHANNEL_START_SUCCESS !\n");
    return EDMA_SUCCESS;
}

/*异步EDMA传输，上层模块查询EDMA传输是否结束*/
s32 edmac_test_channel_async(enum edma_req_id req, u32 direction)
{
    s32    ret_id = 0;
    u32 bur_width = 2;
    u32 bur_len = 3;
    u32 ask_is_idle_loop = 0;

    u32 byte_len = EDMA_M2M_TEST_LENGHT;
    char *temp = NULL;
    s32 count = 0;
    if ((NULL == src_buf) || (NULL == des_buf))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----------edma test not inited \n\n");
        return EDMA_FAIL;
    }

    temp = src_buf;
    while (count < EDMA_M2M_TEST_LENGHT)
    {
        *temp++ = 'a' + count%20;
        ++count;
    }
    src_buf[EDMA_M2M_TEST_LENGHT - 1]='\0';

    temp = des_buf;
    count = 0;
    while (count < EDMA_M2M_TEST_LENGHT)
    {
        *temp++ = 'c' + count%20;
        ++count;
    }
    des_buf[EDMA_M2M_TEST_LENGHT - 1]='\0';
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---src_buf =%c%c%c%c%c%c%c\n",  *((char*)src_buf + 0),
                    *((char*)src_buf + 1), *((char*)src_buf + 2), *((char*)src_buf + 3),
                    *((char*)src_buf + 4), *((char*)src_buf + 5), *((char*)src_buf + 6));
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---des_buf =%c%c%c%c%c%c%c\n",  *((char*)des_buf + 0),
                    *((char*)des_buf + 1), *((char*)des_buf + 2), *((char*)des_buf + 3),
                    *((char*)des_buf + 4), *((char*)des_buf + 5), *((char*)des_buf + 6));
    ret_id = bsp_edma_channel_init(req, NULL, 0, 0);
    if (ret_id < 0)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----------ERROE ret_id = 0x%X\n\n",ret_id);
        return EDMA_CHANNEL_INVALID;
    }

    /* set config reg */
    if (bsp_edma_channel_set_config((u32)ret_id, direction, bur_width, bur_len))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------bsp_edma_channel_set_config FAILED!\n\n");
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_CONFIG_ERROR;
    }
    /* ** */
    //cacheClear( DATA_CACHE, (void*)edma_src_addr, EDMA_M2M_TEST_LENGHT * sizeof(char*));
    //cacheClear( DATA_CACHE, (void*)edma_des_addr, EDMA_M2M_TEST_LENGHT * sizeof(char*));

    if (bsp_edma_channel_async_start((u32)ret_id, (u32)edma_src_addr, (u32)edma_des_addr, byte_len))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------bsp_edma_channel_async_start FAILED!\n\n");
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_CONFIG_ERROR;
    }

    while(0==bsp_edma_channel_is_idle((u32) ret_id))
    {;}
    

    bsp_edma_channel_free((u32)ret_id);

    for (;;)
    {
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---------------pool channel async start!");
        if (!bsp_edma_channel_is_idle((u32)ret_id))
        {
            ask_is_idle_loop++;
            /*ssleep(2);*/
            if (ask_is_idle_loop < 0x100000)
            {
                continue;
            }
            else
            {
                hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------edma_trans_complete is TIMEOUT!");
                return EDMA_TRXFER_ERROR;
            }
        }
        else
        {
            hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"edma_trans_complete-----ask_is_idle_loop=0x%X!\n\n",ask_is_idle_loop);
            if (edmac_verify_data_blk(src_buf,des_buf))
            {
                hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------EDMA_CHANNEL_ASYNC_TEST_FAILED!  verify \n\n");
                return EDMA_TRXFER_ERROR;
            }
            hiedmac_trace(BSP_LOG_LEVEL_CRIT,"===============EDMA_CHANNEL_ASYNC_TEST_SUCCESS!\n");
            return EDMA_SUCCESS;
        }
    }
}

osl_sem_id g_edma_test_sema = 0;
void data_trans_complete(void)
{
    if(g_edma_test_sema){
        osl_sem_down(&g_edma_test_sema);
        hiedmac_trace(BSP_LOG_LEVEL_ERROR, "EDMA sem down from isr OK \n");
    }else{
        hiedmac_trace(BSP_LOG_LEVEL_ERROR, "EDMA sem not inited \n");
    }
}

void edma_isr_sema_give()
{
    if(g_edma_test_sema)
    {
        osl_sem_up(&g_edma_test_sema);
    }
}



/*异步EDMA传输，上层模块注册中断处理程序，处理EDMA传输完成事件*/
s32 edmac_test_channel_async_int(enum edma_req_id req, u32 direction)
{
    s32 ret_id = 0;
    u32 bur_width = 2;
    u32 bur_len = 3;

    u32 byte_len = EDMA_M2M_TEST_LENGHT;
    char *temp = NULL;
    s32 count = 0;
    //OSL_TASK_ID isr_task_id = 0;
    if(!g_edma_test_sema){
        osl_sem_init(0,&g_edma_test_sema);
        if(!g_edma_test_sema){
            hiedmac_trace(BSP_LOG_LEVEL_ERROR, "semBCreate FAILED!");
            return -1;
        }
    }

    if ((NULL == src_buf) || (NULL == des_buf))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----------edma test not inited \n\n");
        return EDMA_FAIL;
    }

    temp = src_buf;
    while (count < EDMA_M2M_TEST_LENGHT)
    {
        *temp++ = 'a' + count%20;
        ++count;
    }
    src_buf[EDMA_M2M_TEST_LENGHT - 1]='\0';

    temp = des_buf;
    count = 0;
    while (count < EDMA_M2M_TEST_LENGHT)
    {
        *temp++ = 'd' + count%20;
        ++count;
    }
    des_buf[EDMA_M2M_TEST_LENGHT - 1]='\0';
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---src_buf =%c%c%c%c%c%c%c\n",  *((char*)src_buf + 0),
                    *((char*)src_buf + 1), *((char*)src_buf + 2), *((char*)src_buf + 3),
                    *((char*)src_buf + 4), *((char*)src_buf + 5), *((char*)src_buf + 6));
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---des_buf =%c%c%c%c%c%c%c\n",  *((char*)des_buf + 0),
                    *((char*)des_buf + 1), *((char*)des_buf + 2), *((char*)des_buf + 3),
                    *((char*)des_buf + 4), *((char*)des_buf + 5), *((char*)des_buf + 6));

    ret_id= bsp_edma_channel_init(req, (channel_isr)edma_isr_sema_give, 0, EDMA_INT_DONE); /*是否要初始化中断回调函数 */
    if (ret_id < 0)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----------ERROR ret_id = 0x%X\n\n",ret_id);
        return EDMA_CHANNEL_INVALID;
    }

    /* set config reg */
    if (bsp_edma_channel_set_config((u32)ret_id, direction, bur_width, bur_len))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"---------EDMA_CHANNEL_ASYNC_TEST_FAILED! config \n\n");
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_CONFIG_ERROR;
    }
    if (bsp_edma_channel_async_start((u32)ret_id, (u32)edma_src_addr, (u32)edma_des_addr, byte_len))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"---------EDMA_CHANNEL_ASYNC_TEST_FAILED! start \n\n");
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_TRXFER_ERROR;
    }

    //osl_task_delay(2);
    data_trans_complete();
    
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG, "EDMA ISR-test ----data_trans_complete!-----\n");
    
    bsp_edma_channel_free((u32)ret_id);
    if (edmac_verify_data_blk(src_buf,des_buf))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"----------EDMA_CHANNEL_ASYNC_TEST_FAILED!  verify \n\n");
        return EDMA_TRXFER_ERROR;
    }
    hiedmac_trace(BSP_LOG_LEVEL_CRIT,"===============EDMA_CHANNEL_ASYNC_INT_TEST_SUCCESS!\n");
    return EDMA_SUCCESS;
}

/*M2M链表传输test*/
#define EDMA_TEST_LLI_NUM               (7)
#define EDMA_TEST_LLI_BLOCK_SIZE        (1024 * 64 - 1)

static struct EDMA_LLI_ALLOC_ADDRESS_STRU  s_edma_alloc_address  = {0, 0};

struct EDMA_SIMPLE_LLI_STRU  stDmaLLI[EDMA_TEST_LLI_NUM];
u8 *              pucSour        = NULL;
u8 *              pucDest        = NULL;
edma_addr_t           edma_buf_phys  = 0;

void edma_clear_data( u8 *pucBuffer, u32 ulSize )
{
    if (pucBuffer && ulSize)
    {
        while( ulSize-- )
        {
            *pucBuffer = 0xAA;
            pucBuffer++;
        }
    }
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"\rEDMA clear data success!\n" );
}

void edma_build_data( u8 *pucBuffer, u32 ulSize, u8 ucFirstData )
{
    u8   ucData = ucFirstData;
    if (pucBuffer && ulSize)
    {
        while( ulSize-- )
        {
            *pucBuffer++ = ucData++;
        }
    }
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"\rEDMA build data success!\n" );
}

s32 edma_verify_data( u8 * pucBuffer, u32 ulSize, u8 ucFirstData )
{
    u8   ucData = ucFirstData;
    if( pucBuffer && ulSize )
    {
        while( ulSize-- )
        {
            if(  *pucBuffer != ucData )
            {
                hiedmac_trace(BSP_LOG_LEVEL_ERROR,"------ edma_verify_data failed!\n");
                return -1;
            }
            pucBuffer++;
            ucData++;
        }
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"------ edma_verify_data success!\n");
        return 0;
    }
    return -1;
}

enum edma_req_id edma_test_req = EDMA_MEMORY;
u32 edma_test_cnt = 1;
s32 edma_set_test_req(enum edma_req_id req_id, u32 test_cnt)
{
    edma_test_req = req_id;
    edma_test_cnt = test_cnt;
    return 0;
}

void edma_buff_init( void )
{
    u32 i = 0;
    pucSour = dma_alloc_coherent(NULL, (EDMA_TEST_LLI_NUM + 2) * EDMA_TEST_LLI_BLOCK_SIZE, &edma_buf_phys, GFP_DMA|__GFP_WAIT);
    if (NULL == pucSour)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"pucSour alloc failed!\n");
        return ;
    }

    pucDest = pucSour + 2 * EDMA_TEST_LLI_BLOCK_SIZE;
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"\rbuffer Sour = 0x%X, Dest = 0x%X\n", (u32)pucSour, (u32)(pucDest));
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"\r------------edma_buf_phys = 0x%X\n", edma_buf_phys);
    /* Build  lli list */
    for (i = 0; i < EDMA_TEST_LLI_NUM; i++)
    {
        stDmaLLI[ i ].ulSourAddr = edma_buf_phys + (i & 0x1) * EDMA_TEST_LLI_BLOCK_SIZE ;
        stDmaLLI[ i ].ulDestAddr = edma_buf_phys + (i + 2) * EDMA_TEST_LLI_BLOCK_SIZE;
        stDmaLLI[ i ].ulLength   = EDMA_TEST_LLI_BLOCK_SIZE;
			/*lint -e506*/
            /* EDMA_M2M - Warning 506: (Warning -- Constant value Boolean) */
        stDmaLLI[ i ].ulConfig   = EDMA_SET_CONFIG((edma_test_req&0x1f), EDMA_M2M, 2, 7);
			/*lint +e506*/
    }

    /* Prepare the transfer data */
    edma_clear_data(pucDest, EDMA_TEST_LLI_NUM * EDMA_TEST_LLI_BLOCK_SIZE);
    edma_build_data(pucSour, EDMA_TEST_LLI_BLOCK_SIZE, 6);
    edma_build_data(pucSour + EDMA_TEST_LLI_BLOCK_SIZE, EDMA_TEST_LLI_BLOCK_SIZE, 0x3a);

}

void edma_buff_exit( void )
{
    if (NULL != pucSour)
    {
        dma_free_coherent(NULL, (EDMA_TEST_LLI_NUM + 2) * EDMA_TEST_LLI_BLOCK_SIZE, pucSour, edma_buf_phys);
        pucSour = NULL;
        pucDest = NULL;
    }
}

/*M2M sync LLI EDMA trans . wait for the completion sem, do not need int handler */
s32 edmac_test_lli(enum edma_req_id req, u32 direction)
{
    edma_addr_t  edma_addr    = 0;
    s32         ret_id       = 0;
    s32         ret          = 0;
    u32      i            = 0;
    struct edma_cb *pstNode   = NULL;
    struct edma_cb *psttemp   = NULL;
    struct edma_cb *FirstNode   = NULL;

    edma_buff_init();
    /*build lli */
    pstNode = (struct edma_cb *)dma_alloc_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                                                                   &edma_addr, GFP_DMA|__GFP_WAIT);
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"---------------edma_addr = 0x%X\n",edma_addr);
    s_edma_alloc_address.s_alloc_virt_address = (u32)pstNode;
    s_edma_alloc_address.s_alloc_phys_address = (u32)edma_addr;
    if (NULL == pstNode)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"LLI list init is failed!\n");
        edma_buff_exit();
        return EDMA_MEMORY_ALLOCATE_ERROR;
    }

    FirstNode = pstNode;
    psttemp = pstNode;
    for (i = 0; i < EDMA_TEST_LLI_NUM; i++)
    {
        psttemp->lli = EDMA_SET_LLI(edma_addr + (i+1) * sizeof(struct edma_cb), ((i < EDMA_TEST_LLI_NUM - 1)?0:1));
        psttemp->config = stDmaLLI[i].ulConfig;
        psttemp->src_addr = stDmaLLI[i].ulSourAddr;/*physical address*/
        psttemp->des_addr = stDmaLLI[i].ulDestAddr;/*physical address*/
        psttemp->cnt0 = stDmaLLI[i].ulLength;
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;

        psttemp++;
    }

    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"LII list init is success!\n");

    /*request the chan_id, and init the sem*/
    ret_id = bsp_edma_channel_init(req, NULL, 0, 0);
    if (ret_id < 0)
    {
        dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                            (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
        edma_buff_exit();
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"-----------error ret_id = 0x%X\n\n",ret_id);
        return EDMA_CHANNEL_INVALID;
    }

    /*获取首节点寄存器地址*/
    psttemp = bsp_edma_channel_get_lli_addr((u32)ret_id);
    if (NULL == psttemp)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"---bsp_edma_channel_get_lli_addr failed!\n\n");
        bsp_edma_channel_free((u32)ret_id);
        dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                            (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
        edma_buff_exit();
        return EDMA_CHANNEL_INVALID;
    }
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"----------- edma_cb LLI = 0x%X!\n\n",(u32)psttemp);

    /*配置首节点寄存器*/
    psttemp->lli = FirstNode->lli;
    psttemp->config = FirstNode->config & 0xFFFFFFFE;
    psttemp->src_addr = FirstNode->src_addr;
    psttemp->des_addr = FirstNode->des_addr;
    psttemp->cnt0 = FirstNode->cnt0;
    psttemp->bindx = 0;
    psttemp->cindx = 0;
    psttemp->cnt1  = 0;

    /* * */
    //cacheClear( DATA_CACHE, (void*)edma_buf_phys, (EDMA_TEST_LLI_NUM + 2) * EDMA_TEST_LLI_BLOCK_SIZE );

    /*启动EDMA传输，等待传输完成信号量释放后返回*/
    if (bsp_edma_channel_lli_start((u32)ret_id))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"bsp_edma_channel_lli_start FAILED!\n\n");
        dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                            (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
        edma_buff_exit();
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_TRXFER_ERROR;
    }
    osl_task_delay(10);
    while(0==bsp_edma_channel_is_idle((u32) ret_id))
    {;}
    
    /* Verify the transfer data */
    for( i = 0; i < EDMA_TEST_LLI_NUM; i++ )
    {
        u8* temp_dest = pucDest + i * EDMA_TEST_LLI_BLOCK_SIZE;
        ret = edma_verify_data( temp_dest, EDMA_TEST_LLI_BLOCK_SIZE, (i & 0x1) ? 0x3a : 0x6 );
        if( !ret )
        {
            break;
        }
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"\rFirst Verify, d[0]=0x%X, d[1]=0x%X, d[2]=0x%X, d[3]=0x%X, d[4]=0x%X, d[5]=0x%X\r\n ",
               *((u8 *)temp_dest + 0 ),
               *((u8 *)temp_dest + 1 ),
               *((u8 *)temp_dest + 2 ),
               *((u8 *)temp_dest + 3 ),
               *((u8 *)temp_dest + 4 ),
               *((u8 *)temp_dest + 5 ));
    }

     /*保证传完数据以后再释放内存*/
    dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                            (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
    edma_buff_exit();

    bsp_edma_channel_free((u32)ret_id);
    if (ret)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"bsp_edma_channel_lli_start FAILED!\n\n");
        return EDMA_TRXFER_ERROR;
    }
    hiedmac_trace(BSP_LOG_LEVEL_CRIT,"=============== EDMA_LLI_START_SUCCESS!\n");
    return EDMA_SUCCESS;
}

u32 g_edma_test_int_flag = EDMA_INT_DONE;
/*异步链式EDMA传输，上层模块注册中断处理程序，处理EDMA传输完成事件*/
s32 edmac_test_async_lli(enum edma_req_id req, u32 direction)
{
    edma_addr_t  edma_addr    = 0;
    s32         ret_id       = 0;
    s32         ret          = 0;
    u32      i            = 0;
    struct edma_cb *pstNode   = NULL;
    struct edma_cb *psttemp   = NULL;
    struct edma_cb *FirstNode   = NULL;

    edma_buff_init();
    /*创建链表*/
    pstNode = (struct edma_cb *)dma_alloc_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                                                                   &edma_addr, GFP_DMA|__GFP_WAIT);
    s_edma_alloc_address.s_alloc_virt_address = (u32)pstNode;
    s_edma_alloc_address.s_alloc_phys_address = (u32)edma_addr;
    if (NULL == pstNode)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"LII list init is failed!");
        edma_buff_exit();
        return EDMA_MEMORY_ALLOCATE_ERROR;
    }

    FirstNode = pstNode;
    psttemp = pstNode;
    for (i = 0; i < EDMA_TEST_LLI_NUM; i++)
    {
        psttemp->lli = EDMA_SET_LLI(edma_addr + (i+1) * sizeof(struct edma_cb), ((i < EDMA_TEST_LLI_NUM - 1)?0:1));
        psttemp->config = stDmaLLI[i].ulConfig;
        psttemp->src_addr = stDmaLLI[i].ulSourAddr;
        psttemp->des_addr = stDmaLLI[i].ulDestAddr;
        psttemp->cnt0 = stDmaLLI[i].ulLength;
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;

        psttemp++;
    }
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"LII list init is success!");

    /*申请通道，注册通道中断回调函数*/
    ret_id = bsp_edma_channel_init(req, (channel_isr)edma_isr_sema_give, 0, g_edma_test_int_flag);
    if (ret_id < 0)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"---------ERROR ret_id = 0x%X\n\n",ret_id);
        dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                          (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
        edma_buff_exit();
        return EDMA_CHANNEL_INVALID;
    }

    /*获取首节点寄存器地址*/
    psttemp = bsp_edma_channel_get_lli_addr((u32)ret_id);
    if (NULL == psttemp)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"---bsp_edma_channel_get_lli_addr FAILED !\n\n");
        bsp_edma_channel_free((u32)ret_id);
        dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                          (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
        edma_buff_exit();
        return EDMA_CHANNEL_INVALID;
    }

    /*配置首节点寄存器*/
    psttemp->lli = FirstNode->lli;
    psttemp->config = FirstNode->config & 0xFFFFFFFE;
    psttemp->src_addr = FirstNode->src_addr;  /*物理地址*/
    psttemp->des_addr = FirstNode->des_addr;  /*物理地址*/
    psttemp->cnt0 = FirstNode->cnt0;
    psttemp->bindx = 0;
    psttemp->cindx = 0;
    psttemp->cnt1  = 0;
    /* * */
    //cacheClear( DATA_CACHE, (void*)edma_buf_phys, (EDMA_TEST_LLI_NUM + 2) * EDMA_TEST_LLI_BLOCK_SIZE );

    /*启动EDMA传输后即返回，可通过查询通道是否busy来确定传输是否完成*/
    if (bsp_edma_channel_lli_async_start((u32)ret_id))
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"bsp_edma_channel_lli_async_start FAILED!\n\n");
        dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                          (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
        edma_buff_exit();
        bsp_edma_channel_free((u32)ret_id);
        return EDMA_TRXFER_ERROR;
    }
    data_trans_complete();

    /*mdelay(200);*/
    bsp_edma_channel_free((u32)ret_id);

    /* Verify the transfer data */
    for( i = 0; i < EDMA_TEST_LLI_NUM; i++ )
    {
        u8* temp_dest = pucDest + i * EDMA_TEST_LLI_BLOCK_SIZE;
        ret = edma_verify_data( temp_dest, EDMA_TEST_LLI_BLOCK_SIZE, (i & 0x1) ? 0x3a : 0x6 );
        if( !ret )
        {
            break;
        }
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"\rFirst Verify, d[0]=0x%X, d[1]=0x%X, d[2]=0x%X, d[3]=0x%X, d[4]=0x%X, d[5]=0x%X\r\n ",
               *((u8 *)temp_dest + 0 ),
               *((u8 *)temp_dest + 1 ),
               *((u8 *)temp_dest + 2 ),
               *((u8 *)temp_dest + 3 ),
               *((u8 *)temp_dest + 4 ),
               *((u8 *)temp_dest + 5 ) );
    }

    dma_free_coherent(NULL,(EDMA_TEST_LLI_NUM * sizeof(struct edma_cb)),
                          (void*)s_edma_alloc_address.s_alloc_virt_address, edma_addr);
    edma_buff_exit();

    if (ret)
    {
        hiedmac_trace(BSP_LOG_LEVEL_ERROR,"bsp_edma_channel_lli_start FAILED!\n");
        return EDMA_TRXFER_ERROR;
    }
    hiedmac_trace(BSP_LOG_LEVEL_CRIT,"===============EDMA_LLI_ASYNC_START_SUCCESS!\n");
    return EDMA_SUCCESS;
}

s32 edmac_test_all_func(void)
{
    u32 index_cnt = 0;
    s32 ret1, ret2, ret3, ret4, ret5 ;

        hiedmac_trace(BSP_LOG_LEVEL_ERROR, "reqs:0x%x  cnt:%d\n",edma_test_req,edma_test_cnt);

    edma_test_init();
    if((NULL==src_buf)||(NULL==des_buf))
        return -1;

    for (index_cnt = 0; index_cnt < edma_test_cnt; index_cnt++)
    {
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"timers %d / %d  !\n",index_cnt,edma_test_cnt );
        ret1 = edmac_test_channel(edma_test_req, EDMA_M2M);
        ret2 = edmac_test_channel_async(edma_test_req, EDMA_M2M);
        ret3 = edmac_test_channel_async_int(edma_test_req, EDMA_M2M);
        ret4 = edmac_test_lli(edma_test_req, EDMA_M2M);
        ret5 = edmac_test_async_lli(edma_test_req, EDMA_M2M);
        if(ret1|ret2|ret3|ret4|ret5)
        {
            hiedmac_trace(BSP_LOG_LEVEL_ERROR,"test ret: %d %d %d %d %d  !\n",ret1, ret2, ret3, ret4, ret5 );
            return -1;
        }
    }

    edma_test_exit();
    return 0;
}




/*************/

u32 * addr1 = 0;
u32 * addr2 = 0;

u32 chan_stop = 0;
u32 edma_align_size = 1024;
s32 edma_test(enum edma_req_id req_id, u32 size, u32  bst_width,u32 bst_len, s32 vec_flag)
{
    u32 chan_id = (u32)(-1);
    u32 index_size = 0;
    u32 addr_use1 = 0;
    u32 addr_use2 = 0;
    u32 * temp = 0;

    //bsp_edma_init();
    if(0 == (addr1 = (u32*)osl_cachedma_malloc(size+32)))
    {
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG," malloc1 size=0x%x  failed \n",size);
        return -1;
    }
    if(0 == (addr2 = (u32*)osl_cachedma_malloc(size+32)))
    {
        osl_cachedma_free(addr1);
        hiedmac_trace(BSP_LOG_LEVEL_DEBUG," malloc2 size=0x%x  failed \n",size);
        return -1;
    }
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"addr1=0x%x, addr2=0x%x \n",(u32)addr1,(u32)addr2);
    edma_build_data((u8*)addr1, size+32, 0x20);
    edma_build_data((u8*)addr2, size+32, 0x40);
    /*test: 让addr 1k 对齐 */
    addr_use1 = (u32)addr1+4;
    addr_use2 = (u32)addr2+4;
    hiedmac_trace(BSP_LOG_LEVEL_DEBUG,"addr_use1=0x%x, addr_use2=0x%x \n",addr_use1,addr_use2);

    temp = (u32*)addr_use1;
    for(index_size=0; index_size<(size/4);index_size++ )
    {
        *temp++ = (u32)index_size;
    }


    chan_id = (u32)bsp_edma_channel_init(req_id,0,0,0);
    bsp_edma_channel_set_config(chan_id,3,bst_width,bst_len);

    if(1==vec_flag)
    {
        bsp_edma_channel_start(chan_id, addr_use1, addr_use2 , size );
    }
    else
    {
        bsp_edma_channel_2vec_start(chan_id, addr_use1, addr_use2 , size,edma_align_size);
    }

    while( EDMA_CHN_BUSY == bsp_edma_channel_is_idle(chan_id) )
    {
        
        chan_stop++;
        if (20==chan_stop)
        {
            bsp_edma_channel_stop( chan_id);
            
        }
    }
    
    bsp_edma_channel_free(chan_id);

    osl_cachedma_free(addr1);
    osl_cachedma_free(addr2);

    return 0;

}

void edma_test_all_requests_map(void)
{
    u32 ret1[EDMA_REQ_MAX];
    u32 ret2[EDMA_REQ_MAX];
    u32 i = 0;

    for(i=0;i<EDMA_REQ_MAX;i++){
        ret1[i] = bsp_edma_get_physical_req((enum edma_req_id)i);
        ret2[i] = (u32)bsp_edma_channel_init((enum edma_req_id)i, NULL, 0, 0);
    }
    for(i=0;i<EDMA_REQ_MAX;i++){
        hiedmac_trace(BSP_LOG_LEVEL_ERROR, "reqs:0x%x,\t peri_id:%d ,\t chan_id:%d \n",i,ret1[i],ret2[i]);
    }
}
void edma_test_all_requests(void)
{
    u32 reqs[]={0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,
                0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x24};
    u32 i = 0;
    for(i=0;i<(sizeof(reqs)/sizeof(u32));i++){
        edma_set_test_req((enum edma_req_id)reqs[i],edma_test_cnt);
        (void)edmac_test_all_func();
    }
}

#ifdef __cplusplus
}
#endif
