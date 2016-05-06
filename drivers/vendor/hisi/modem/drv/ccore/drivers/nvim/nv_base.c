

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -save -e537*/
#include <securec.h>
#include <mdrv_sync.h>
#include <bsp_nvim.h>
#include <bsp_hardtimer.h>
#include "nv_comm.h"
#include <stdlib.h>
#include <string.h>
#include "nv_debug.h"
#include <bsp_reset.h>
#include <bsp_dump.h>

/*lint -restore +e537*/

u32 nv_readEx(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    u32 ret = NV_ERROR;
    struct nv_file_list_info_stru file_info = {0};
    struct nv_ref_data_info_stru  ref_info  = {0};

    nv_debug(NV_FUN_READ_EX,0,itemid,modem_id,datalen);

    if((NULL == pdata)||(0 == datalen))
    {
        nv_debug(NV_FUN_READ_EX,1,itemid,0,0);
        ret = BSP_ERR_NV_INVALID_PARAM;
        /*lint -save -e801*/
        goto nv_readEx_err;
        /*lint -restore*/
    }

    /*lint -save -e826*/
    ret = nv_search_byid(itemid,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
    /*lint -restore +e826*/
    if(ret)
    {
        nv_debug(NV_FUN_READ_EX,2,itemid,ret,0);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    if((offset + datalen) > ref_info.nv_len)
    {
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        nv_debug(NV_FUN_READ_EX,4,offset,datalen,ref_info.nv_len);
        /*lint -save -e801*/
        goto nv_readEx_err;
        /*lint -restore*/
    }
    if(modem_id <= ref_info.modem_num)
    {
        ref_info.nv_off += (modem_id - NV_USIMM_CARD_1)*ref_info.nv_len;
    }
    else
    {
#if (FEATURE_OFF == FEATURE_MULTI_MODEM)
        ret = BSP_ERR_NV_INVALID_PARAM;
        nv_debug(NV_FUN_READ_EX,5,ret,itemid,modem_id);
        /*lint -save -e801*/
        goto nv_readEx_err;
        /*lint -restore*/
#endif
    }


    ret = nv_read_from_mem(pdata,datalen,file_info.file_id,ref_info.nv_off+offset);
    if(ret)
    {
        nv_debug(NV_FUN_READ_EX,6,offset,datalen,ref_info.nv_len);
        /*lint -save -e801*/
        goto nv_readEx_err;
        /*lint -restore*/
    }
    /*lint -save -e578 -e530 -e718 -e746 -e628 -e515 -e516*/
    nv_debug_trace(pdata,datalen);/*lint !e628*/
    /*lint -restore*/

    return NV_OK;
nv_readEx_err:
    /*lint -save -e515 -e516*/
    nv_error_printf("\n[%s]:[0x%x]:[%d],line:%d\n",__FUNCTION__,itemid,modem_id,__LINE__);
    /*lint -restore*/
    nv_help(NV_FUN_READ_EX);
    return ret;
}

u32 nv_writeEx(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    u32 ret = NV_ERROR;
    struct nv_file_list_info_stru file_info = {0};
    struct nv_ref_data_info_stru  ref_info  = {0};
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    u32 nv_offset = 0;/*nv数据相对于ctrl start的偏移*/
    u8  test_byte;

    nv_debug_record(NV_DEBUG_WRITEEX_START|itemid<<16);
    nv_debug(NV_FUN_WRITE_EX,0,itemid,modem_id,datalen);

    if((NULL == pdata)||(0 == datalen))
    {
        nv_debug(NV_FUN_WRITE_EX,1,itemid,datalen,0);
        ret = BSP_ERR_NV_INVALID_PARAM;
        /*lint -save -e801*/
        goto nv_writeEx_err;
        /*lint -restore*/
    }

    /* test pdata is accessable */
    test_byte = *pdata;
    UNUSED(test_byte);

    ret = nv_search_byid(itemid,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
    if(ret)
    {

        nv_debug(NV_FUN_WRITE_EX,2,itemid,datalen,ret);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    /*lint -save -e578 -e530 -e515 -e516*/
    nv_debug_trace(pdata, datalen);
    /*lint -restore*/

    if((datalen + offset) >ref_info.nv_len)
    {
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        nv_debug(NV_FUN_WRITE_EX,3,itemid,datalen,ref_info.nv_len);
        /*lint -save -e801*/
        goto nv_writeEx_err;
        /*lint -restore*/
    }
    if(modem_id <= ref_info.modem_num)
    {
        ref_info.nv_off += (modem_id - NV_USIMM_CARD_1)*ref_info.nv_len;
    }
    else
    {
#if (FEATURE_OFF == FEATURE_MULTI_MODEM)
        ret = BSP_ERR_NV_INVALID_PARAM;
        nv_debug(NV_FUN_WRITE_EX,4,itemid,ret,modem_id);
        /*lint -save -e801*/
        goto nv_writeEx_err;
        /*lint -restore*/
#endif
    }

    nv_offset = ddr_info->file_info[file_info.file_id - 1].offset+offset+ref_info.nv_off;

    /*IPC锁保护，防止在校验CRC时写NV 操作还没有完成*/
    nv_debug_record(NV_DEBUG_WRITEEX_GET_IPC_START);
    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    nv_debug_record(NV_DEBUG_WRITEEX_GET_IPC_END);
    ret = nv_check_nv_data_crc(nv_offset, datalen);
    nv_ipc_sem_give(IPC_SEM_NV_CRC);
    nv_debug_record(NV_DEBUG_WRITEEX_GIVE_IPC);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,5,itemid,datalen,0);
        ret = nv_resume_ddr_from_img();
        if(ret)
        {
            nv_debug(NV_FUN_WRITE_EX,6,itemid,datalen,ret);
            /*lint -save -e801*/
            goto nv_writeEx_err;
            /*lint -restore*/
        }
    }
    
    nv_debug_record(NV_DEBUG_WRITEEX_MEM_START);
    ret = nv_write_to_mem(pdata,datalen,file_info.file_id,ref_info.nv_off+offset);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,7,itemid,datalen,0);
        /*lint -save -e801*/
        goto nv_writeEx_err;
        /*lint -restore*/
    }
    
    nv_debug_record(NV_DEBUG_WRITEEX_FILE_START);
    ret = nv_write_to_file(&ref_info);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,8, itemid,datalen,ret);
        /*lint -save -e801*/
        goto nv_writeEx_err;
        /*lint -restore*/
    }
    nv_debug_record(NV_DEBUG_WRITEEX_END|itemid<<16);
    
    return NV_OK;
    
nv_writeEx_err:
    /*lint -save -e515 -e516*/
    nv_error_printf("\n[%s]:[0x%x]:[%d],line:%d\n",__FUNCTION__,itemid,modem_id,__LINE__);
    /*lint -restore*/
    nv_help(NV_FUN_WRITE_EX);
    return ret;
}


u32 bsp_nvm_get_len(u32 itemid,u32* len)
{
    u32 ret  = NV_ERROR;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};

    nv_debug(NV_API_GETLEN,0,itemid,0,0);

    if(NULL == len)
    {
        nv_debug(NV_API_GETLEN,1,itemid,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    /*check init state*/
    if(false == nv_read_right(itemid))
    {
        nv_debug(NV_API_GETLEN,3,itemid,0,0);
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }
    ret = nv_search_byid(itemid,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info, &file_info);
    if(NV_OK == ret)
    {
        *len = ref_info.nv_len;
        return NV_OK;
    }
    return ret;
}

u32 bsp_nvm_authgetlen(u32 itemid,u32* len)
{
    return bsp_nvm_get_len(itemid,len);
}

u32 bsp_nvm_dcread_direct(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return nv_readEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_dcread(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    /*check init state*/
    if(false == nv_read_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_readEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_auth_dcread(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return bsp_nvm_dcread(modem_id,itemid,pdata,datalen);
}

u32 bsp_nvm_dcreadpart(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    /*check init state*/
    if(false == nv_read_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_readEx(modem_id,itemid,offset,pdata,datalen);
}

u32 bsp_nvm_dcwrite(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    if(false == nv_write_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_writeEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_auth_dcwrite(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return bsp_nvm_dcwrite(modem_id,itemid,pdata,datalen);
}

u32 bsp_nvm_dcwritepart(u32 modem_id,u32 itemid, u32 offset,u8* pdata,u32 datalen)
{
    if(false == nv_write_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_writeEx(modem_id,itemid,offset,pdata,datalen);
}

u32 bsp_nvm_dcwrite_direct(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return nv_writeEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_flushEx(u32 off,u32 len,u32 itemid)
{
    u32 ret = NV_ERROR;
    struct nv_icc_stru icc_req = {0};
    struct nv_icc_stru icc_cnf = {0};
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_debug(NV_API_FLUSH,0,0,0,0);

    if(NV_INIT_OK != ddr_info->ccore_init_state)
    {
        nv_debug(NV_API_FLUSH,1,ddr_info->ccore_init_state,0,0);
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    icc_req.msg_type = NV_ICC_REQ_INSTANT_FLUSH;
    icc_req.data_len = len;
    icc_req.data_off = off;
    icc_req.ret      = 93;   /*use to test ,no meaning*/
    icc_req.itemid   = itemid;
    icc_req.slice    = bsp_get_slice_value();

    ret = nv_icc_send((u8*)&icc_req,sizeof(icc_req));
    if(ret)
    {
        nv_debug(NV_API_FLUSH,2,0,ret,0);
        return ret;
    }
    /*lint -save -e534*/
    if(osl_sem_downtimeout(&g_nv_ctrl.cc_sem,NV_MAX_WAIT_TICK))
    {
        nv_printf("down time out\n");
    }
    
    /*lint -restore +e534*/

    if(memcpy_s(&icc_cnf,sizeof(struct nv_icc_stru),g_nv_ctrl.nv_icc_buf,sizeof(icc_cnf)))
    {
        nv_printf("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }
    if(icc_cnf.msg_type != NV_ICC_CNF)
    {


        nv_debug(NV_API_FLUSH,3,0,0,icc_cnf.msg_type);
        /*lint -save -e515 -e516*/
        nv_error_printf("\n[%s],line:%d\n",__FUNCTION__,__LINE__);
        /*lint -restore*/
        nv_help(NV_API_FLUSH);
        return BSP_ERR_NV_INVALID_PARAM;
    }
    return icc_cnf.ret;
}


u32 bsp_nvm_flush(void)
{
    u32 ret;

    ret = nv_flushList();
    if(ret)
    {
        return ret;
    }
    return NV_OK;
}


u32 bsp_nvm_flushSys(u32 itemid)
{
    u32 ret = NV_ERROR;
    struct nv_icc_stru icc_req = {0};
    struct nv_icc_stru icc_cnf = {0};
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_debug(NV_API_FLUSH,0,0,0,0);

    if(NV_INIT_OK != ddr_info->ccore_init_state)
    {
        nv_debug(NV_API_FLUSH,1,ddr_info->ccore_init_state,0,0);
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    icc_req.msg_type = NV_ICC_REQ_SYS;
    icc_req.data_len = ddr_info->file_len;
    icc_req.data_off = 0;
    icc_req.ret      = 93;   /*use to test ,no meaning*/
    icc_req.itemid   = itemid;
    icc_req.slice    = bsp_get_slice_value();

    ret = nv_icc_send((u8*)&icc_req,sizeof(icc_req));
    if(ret)
    {
        nv_debug(NV_API_FLUSH,2,0,ret,0);
        return ret;
    }
    /*lint -save -e534*/
    if(osl_sem_downtimeout(&g_nv_ctrl.cc_sem,NV_MAX_WAIT_TICK))
    {
        nv_printf("down timeout 22\n");
    }
    /*lint -restore +e534*/

    if(memcpy_s(&icc_cnf,sizeof(struct nv_icc_stru),g_nv_ctrl.nv_icc_buf,sizeof(icc_cnf)))
    {
        nv_printf("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }
    if(icc_cnf.msg_type != NV_ICC_CNF)
    {
        nv_debug(NV_API_FLUSH,3,0,0,icc_cnf.msg_type);
        /*lint -save -e515 -e516*/
        nv_error_printf("\n[%s],line:%d\n",__FUNCTION__,__LINE__);
        /*lint -restore*/
        nv_help(NV_API_FLUSH);
        return BSP_ERR_NV_INVALID_PARAM;
    }
    return icc_cnf.ret;
}

u32 bsp_nvm_buf_init(void)
{
    /*create sem*/
    osl_sem_init(1,&g_nv_ctrl.nv_list_sem);
    INIT_LIST_HEAD(&g_nv_ctrl.nv_list);

    return NV_OK;
}


typedef struct _nv_wr_process_s{
    u32 in_proc;
    u8* pdata;
    u32 size;
    u32 file_id;
    u32 offset;
}nv_wr_process_s;

nv_wr_process_s g_nv_wr_process = {0};

u32 nv_in_wr_process(void)
{
    return g_nv_wr_process.in_proc;
}

void nv_wr_process_set(u8* pdata,u32 size,u32 file_id,u32 offset)
{
    g_nv_wr_process.pdata   = pdata;
    g_nv_wr_process.size    = size;
    g_nv_wr_process.file_id = file_id;
    g_nv_wr_process.offset  = offset;
    g_nv_wr_process.in_proc = TRUE;

    return;
}

void nv_wr_process_clear(void)
{
    g_nv_wr_process.in_proc = FALSE;
    g_nv_wr_process.pdata   = NULL;
    g_nv_wr_process.size    = 0;
    g_nv_wr_process.file_id = 0;
    g_nv_wr_process.offset  = 0;

    return;
}

u32 nv_reset_write2mem(u32 in_reset, u32* stamp)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    u32 ret = 0;
    u8* pdata = g_nv_wr_process.pdata;
    u32 size = g_nv_wr_process.size;
    u32 file_id = g_nv_wr_process.file_id;
    u32 offset = g_nv_wr_process.offset;

    if((!pdata) || (!size))
    {
        bsp_print2dmsg("[%s]:data 0x%x size 0x%x\n",__FUNCTION__, pdata, size);
        return BSP_ERR_NV_INVALID_PARAM;
    }
    
    if(offset > ddr_info->file_info[file_id-1].size)
    {
        bsp_print2dmsg("[%s]:offset 0x%x\n",__FUNCTION__,offset);
        return BSP_ERR_NV_FILE_ERROR;
    }

    if(in_reset)
    {
        *stamp |= 0x10;
        bsp_reset_timestamp(*stamp, STAMP_RESET_NV_IDLE);
    }
    
    /* if flow is in nv write process, ipc semphone has been taked
       modem reset flow can not clear ipc bit before ccore reset */
    /*
    if(ccore != bsp_ipc_sem_get_locked(IPC_SEM_NV_CRC))
    {
        ipc_sem = nv_ipc_sem_try_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
        if(ipc_sem)
        {
            return BSP_ERR_NV_GIVE_IPC_ERR;
        }
    }
    */
    
    bsp_print2dmsg("[0x%x][%s]:memcpy start\n",bsp_get_slice_value(), __FUNCTION__);
    if(memcpy_s((u8*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+ddr_info->file_info[file_id-1].offset + offset), size ,pdata,size))
    {
        bsp_print2dmsg("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }

    if(in_reset)
    {
        *stamp |= 0x20;
        bsp_reset_timestamp(*stamp, STAMP_RESET_NV_IDLE);
    }
    bsp_print2dmsg("[0x%x][%s]:make crc start\n",bsp_get_slice_value(), __FUNCTION__);

    ret = nv_make_nv_data_crc(ddr_info->file_info[file_id-1].offset+ offset, size);
    if(ret)
    {
        bsp_print2dmsg("ret = 0x%x\n",ret);
        return BSP_ERR_NV_CRC_CODE_ERR;
    }

    if(in_reset)
    {
        *stamp |= 0x40;
        bsp_reset_timestamp(*stamp, STAMP_RESET_NV_IDLE);
    }
    bsp_print2dmsg("[0x%x][%s]:cache flush start\n",bsp_get_slice_value(), __FUNCTION__);

    nv_flush_cache((u8*)(NV_GLOBAL_CTRL_INFO_ADDR+ddr_info->file_info[file_id-1].offset + offset),size);

    return NV_OK;
}

int bsp_nvm_reset_prepare(void)
{
    u32 stamp = 0;

    stamp |= 0x1;
    bsp_reset_timestamp(stamp, STAMP_RESET_NV_IDLE);

    if(nv_in_wr_process())
    {
        stamp |= 0x2;
        bsp_reset_timestamp(stamp, STAMP_RESET_NV_IDLE);
        (void)nv_reset_write2mem(TRUE, &stamp);
        nv_wr_process_clear();
    }

    stamp |= 0x4;
    bsp_reset_timestamp(stamp, STAMP_RESET_NV_IDLE);
    nv_ipc_sem_give(IPC_SEM_NV_CRC);

    stamp |= 0x8;
    stamp = ((stamp<<16)&0xffff0000) | (bsp_get_slice_value()&0xffff);
    bsp_reset_timestamp(stamp, STAMP_RESET_NV_IDLE);

    return BSP_OK;
}

u32 bsp_nvm_dump_hook(void)
{
    u32 stamp = 0;

    if(nv_in_wr_process())
    {
        bsp_print2dmsg("[0x%x][%s]:in write process\n",bsp_get_slice_value(), __FUNCTION__);
        (void)nv_reset_write2mem(FALSE, &stamp);
        nv_wr_process_clear();
        bsp_print2dmsg("[0x%x][%s]:reset_write2mem end\n",bsp_get_slice_value(), __FUNCTION__);
    }

    nv_ipc_sem_give(IPC_SEM_NV_CRC);
    bsp_print2dmsg("[0x%x][%s]:nv_ipc_sem_give end\n",bsp_get_slice_value(), __FUNCTION__);

    return BSP_OK;
}


void bsp_nvm_reset_init(void)
{
    dump_handle nvc_reset;

    (void)bsp_register_master_idle(NV_IDLE, bsp_nvm_reset_prepare);

    nvc_reset = bsp_dump_register_hook("nvc_hook", (dump_hook)bsp_nvm_dump_hook);
    if(BSP_ERROR == nvc_reset)
    {
        nv_printf("register nvc_reset to dump failed!\n");
        return;
    }

    return;
}



u32 bsp_nvm_init(void)
{

    u32 ret = NV_ERROR;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;


    nv_debug(NV_FUN_NVM_INIT,0,0,0,0);

    (void)nv_debug_init();

    if(ddr_info->ccore_init_state < NV_BOOT_INIT_OK)
    {
		/* yangzhi RTOSck */
        nv_error_printf("[%s]:pre init fail,break here!\n",__FUNCTION__);
        nv_debug(NV_FUN_NVM_INIT,1,0,0,0);
        /*lint -save -e801*/
        goto nv_init_fail;
        /*lint -restore*/
    }
    g_nv_ctrl.shared_addr = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    spin_lock_init(&g_nv_ctrl.spinlock);

    ret = nv_icc_chan_init();
    if(ret)
    {
        nv_debug(NV_FUN_NVM_INIT,2,ret,0,0);
        /*lint -save -e801*/
        goto nv_init_fail;
        /*lint -restore*/
    }
    osl_sem_init(1,&g_nv_ctrl.rw_sem);
    osl_sem_init(0,&g_nv_ctrl.cc_sem);

    ret = bsp_nvm_read(NV_ID_MSP_FLASH_LESS_MID_THRED,(u8*)&g_nv_ctrl.mid_prio,sizeof(u32));
    if(ret)
    {
        g_nv_ctrl.mid_prio = 20;
		/* yangzhi RTOSck */
        nv_error_printf("read 0x%x error : 0x%x,use default count\n",NV_ID_MSP_FLASH_LESS_MID_THRED,ret);
    }
    ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL,(u8*)(&(g_nv_ctrl.nv_self_ctrl)),sizeof(NV_SELF_CTRL_STRU));
    if(ret)
    {
        g_nv_ctrl.nv_self_ctrl.ulResumeMode = NV_MODE_USER;
        nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_DRV_SELF_CTRL,ret);
    }
    ret = (u32)bsp_ipc_sem_create(IPC_SEM_NV_CRC);
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,3 ,ret ,0,0);
        /*lint -save -e801*/
        goto nv_init_fail;
        /*lint -restore*/
    }
    ret = bsp_nvm_buf_init();
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT, 5 , ret ,0,0);
        /*lint -save -e801*/
        goto nv_init_fail;
        /*lint -restore*/
    }
    ddr_info->ccore_init_state = NV_INIT_OK;
    nv_printf("nv init ok !\n");

    INIT_LIST_HEAD(&g_nv_ctrl.stList);

    bsp_nvm_reset_init();
    
    return NV_OK;
nv_init_fail:
    ddr_info->ccore_init_state = NV_INIT_FAIL;
	/* yangzhi RTOSck */
    nv_error_printf("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_NVM_INIT);
    return ret;
}

u32 nvm_read_rand(u32 nvid)
{
    u32 ret;
    u8* tempdata;
    u32 i= 0;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};

    ret = nv_search_byid(nvid, (u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
    if(NV_OK != ret)
    {
        return ret;
    }
    if(ref_info.nv_len == 0)
    {
        return NV_ERROR;
    }
    /*lint -save -e515 -e516*/
	/* yangzhi RTOSck */
    nv_printf_info("[0x%x]:len 0x%x,off 0x%x,file id %d\n",nvid,ref_info.nv_len,ref_info.nv_off,ref_info.file_id);
    /*lint -restore*/

    /*lint -save -e516*/
    tempdata = (u8*)nv_malloc(ref_info.nv_len);
    /*lint -restore +e516*/
    if(NULL == tempdata)
    {
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    ret = bsp_nvm_read(nvid,tempdata,ref_info.nv_len);
    if(NV_OK != ret)
    {
        nv_free(tempdata);
        return BSP_ERR_NV_READ_DATA_FAIL;
    }
    /*lint -save -e515 -e516*/
    for(i=0;i<(ref_info.nv_len);i++)
    {
        if((i%32) == 0)
        {
			/* yangzhi RTOSck */
            nv_printf_info("\n");
        }
		/* yangzhi RTOSck */
        nv_printf_info("%02x ",(u8)(*(tempdata+i)));
    }
	/* yangzhi RTOSck */
    nv_printf_info("\n\n");
    /*lint -restore*/
    nv_free(tempdata);
    return 0;
}


u32 nvm_read_randex(u32 nvid,u32 modem_id)
{
	u8* tempdata=NULL;   
	struct nv_ref_data_info_stru ref_info = {0};
	struct nv_file_list_info_stru file_info = {0};
    u32 ret = 0;
    u32 i = 0;

	ret = nv_search_byid(nvid, (u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
	if(NV_OK != ret)
	{
		return ret;
	}
	if(ref_info.nv_len == 0)
	{
		return NV_ERROR;
	}
    /*lint -save -e515 -e516*/
	/* yangzhi RTOSck */
	nv_printf("[0x%x]:len 0x%x,off 0x%x,file id %d\n",nvid,ref_info.nv_len,ref_info.nv_off,ref_info.file_id);
	/* yangzhi RTOSck */
	nv_printf("[0x%x]:dsda 0x%x\n",nvid,ref_info.modem_num);
    /*lint -restore*/

	/*lint -save -e516*/
	tempdata = (u8*)nv_malloc(ref_info.nv_len +1);
	/*lint -restore +e516*/
	if(NULL == tempdata)
	{
		return BSP_ERR_NV_MALLOC_FAIL;
	}
	ret = bsp_nvm_dcread(modem_id,nvid,tempdata,ref_info.nv_len);
	if(NV_OK != ret)
	{
		nv_free(tempdata);
		return BSP_ERR_NV_READ_DATA_FAIL;
	}
    /*lint -save -e515 -e516*/
	for(i=0;i<ref_info.nv_len;i++)
	{
		if((i%32) == 0)
		{
			nv_printf_info("\n");
		}
		nv_printf_info("%02x ",(u8)(*(tempdata+i)));
	}

	nv_printf("\n\n");
    /*lint -restore*/
	nv_free(tempdata);

	return 0;

}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




