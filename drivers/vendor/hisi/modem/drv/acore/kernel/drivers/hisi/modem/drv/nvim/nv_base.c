

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e537*/
#include <linux/kthread.h>
#include <linux/vmalloc.h>
#include <osl_thread.h>
#include <bsp_nvim.h>
#include "nv_comm.h"
#include "nv_file.h"
#include "nv_ctrl.h"
#include "nv_xml_dec.h"
#include "nv_debug.h"
#include "NVIM_ResumeId.h"
#include "bsp_dump.h"

/*lint -restore +e537*/

/*lint -save -e713 -e830*/
u32 nv_readEx(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    u32 ret = NV_ERROR;
    struct nv_file_list_info_stru file_info;
    struct nv_ref_data_info_stru  ref_info;

    nv_debug(NV_FUN_READ_EX,0,itemid,modem_id,datalen);

    if((NULL == pdata)||(0 == datalen))
    {
        nv_debug(NV_FUN_READ_EX,1,itemid,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    ret = nv_search_byid(itemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&ref_info,&file_info);
    if(ret)
    {
        nv_printf("\ncan not find 0x%x !\n",itemid);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    if((offset + datalen) > ref_info.nv_len)
    {
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        nv_debug(NV_FUN_READ_EX,3,offset,datalen,ref_info.nv_len);
        goto nv_readEx_err;
    }
    if(modem_id <= ref_info.modem_num)
    {
        ref_info.nv_off += (modem_id - NV_USIMM_CARD_1)*ref_info.nv_len;
    }
    else
    {
#if (FEATURE_OFF == FEATURE_MULTI_MODEM)
        ret = BSP_ERR_NV_INVALID_PARAM;
        nv_debug(NV_FUN_READ_EX,4,ret,itemid,modem_id);
        goto nv_readEx_err;
#endif
    }

    ret = nv_read_from_mem(pdata, datalen,file_info.file_id,(ref_info.nv_off+offset));
    if(ret)
    {
        nv_debug(NV_FUN_READ_EX,5,offset,datalen,ref_info.nv_len);
        goto nv_readEx_err;
    }
    /*lint -save -e578 -e530*/
    nv_debug_trace(pdata, datalen);
    /*lint -restore +e578 +e530*/

    return NV_OK;
nv_readEx_err:
    nv_mntn_record("\n[%s]:[0x%x]:[%d]\n",__FUNCTION__,itemid,modem_id);
    nv_help(NV_FUN_READ_EX);
    return ret;
}

u32 nv_writeEx(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    u32 ret = NV_ERROR;
    struct nv_file_list_info_stru file_info;
    struct nv_ref_data_info_stru  ref_info;
    u32 nv_offset = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    u8  test_byte;

    nv_debug(NV_FUN_WRITE_EX,0,itemid,modem_id,datalen);
    nv_debug_record(NV_DEBUG_WRITEEX_START|itemid<<16);

    if((NULL == pdata)||(0 == datalen))
    {
        nv_debug(NV_FUN_WRITE_EX,1,itemid,datalen,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    /* test pdata is accessable */
    test_byte = *pdata;
    UNUSED(test_byte);

    ret = nv_search_byid(itemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&ref_info,&file_info);
    if(ret)
    {

        nv_printf("\ncan not find 0x%x !\n",itemid);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    /*lint -save -e578 -e530*/
    nv_debug_trace(pdata, datalen);
    /*lint -restore +e578 +e530*/

    if((datalen + offset) >ref_info.nv_len)
    {
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        nv_debug(NV_FUN_WRITE_EX,3,itemid,datalen,ref_info.nv_len);
        goto nv_writeEx_err;
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
        goto nv_writeEx_err;
#endif
    }

    nv_offset = ddr_info->file_info[file_info.file_id -1].offset+offset+ref_info.nv_off;

    /*IPC锁保护，防止在校验CRC时写NV操作还没有完成*/
    nv_debug_record(NV_DEBUG_WRITEEX_GET_IPC_START);
    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    nv_debug_record(NV_DEBUG_WRITEEX_GET_IPC_END);
    ret = nv_check_nv_data_crc(nv_offset, datalen);
    nv_ipc_sem_give(IPC_SEM_NV_CRC);
    nv_debug_record(NV_DEBUG_WRITEEX_GIVE_IPC);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX, 5, itemid,datalen,0);
        ret = nv_resume_ddr_from_img();
        if(ret)
        {
            nv_debug(NV_FUN_WRITE_EX,6, itemid, ret, modem_id);
            goto nv_writeEx_err;
        }
    }
    nv_debug_record(NV_DEBUG_WRITEEX_MEM_START);
    ret = nv_write_to_mem(pdata,datalen,file_info.file_id,ref_info.nv_off+offset);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,7,itemid,datalen,0);
        goto nv_writeEx_err;
    }

    nv_debug_record(NV_DEBUG_WRITEEX_FILE_START);

    ret = nv_write_to_file(&ref_info);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,8,itemid,datalen,ret);
        goto nv_writeEx_err;
    }
    nv_debug_record(NV_DEBUG_WRITEEX_END|itemid<<16);
    return NV_OK;
nv_writeEx_err:
    nv_mntn_record("\n[%s]:[0x%x]:[%d]\n",__FUNCTION__,itemid,modem_id);
    nv_help(NV_FUN_WRITE_EX);
    return ret;
}

u32 bsp_nvm_get_nv_num(void)
{
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    return ctrl_info->ref_count;
}

u32 bsp_nvm_get_nvidlist(NV_LIST_INFO_STRU*  nvlist)
{
    u32 i;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)(NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);

    if(NULL == nvlist)
    {
        return NV_ERROR;
    }

    for(i = 0;i<ctrl_info->ref_count;i++)
    {
        nvlist[i].usNvId       = ref_info[i].itemid;
        nvlist[i].ucNvModemNum = ref_info[i].modem_num;
    }
    return NV_OK;
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



/*lint -save -e529*/
u32 bsp_nvm_flushEx(u32 off,u32 len,u32 itemid)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 crc_count = 0;
    u32 skip_crc_count = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    u32 crc_value_off = 0;
    u32 crc_value_len = 0;

    nv_debug(NV_API_FLUSH,0,off,len,itemid);
    nv_debug_record(NV_DEBUG_FLUSHEX_START);

    if((off + len) > (ddr_info->file_len))
    {
        nv_debug(NV_API_FLUSH,1,off,len,ddr_info->file_len);
        goto nv_flush_err;
    }

    nv_debug_record(NV_DEBUG_FLUSHEX_OPEN_START);

    if(nv_file_access((s8*)NV_IMG_PATH,0))
    {
        fp = nv_file_open((s8*)NV_IMG_PATH,(s8*)NV_FILE_WRITE);
        if(NULL == fp)
        {
            nv_debug(NV_API_FLUSH, 6, ret,0,0);
            goto nv_flush_err;
        }
        nv_file_close(fp);
        return bsp_nvm_flushEn(NV_FLAG_NEED_CRC);
    }
    else
    {
        fp = nv_file_open((s8*)NV_IMG_PATH,(s8*)NV_FILE_RW);
        if(NULL == fp)
        {
            ret = BSP_ERR_NV_NO_FILE;
            nv_debug(NV_API_FLUSH,2,ret,0,0);
            goto nv_flush_err;
        }
    }
    nv_debug_record(NV_DEBUG_FLUSHEX_OPEN_END);

    /*如果支持CRC校验码则需要将CRC校验码写入文件*/
    if(NV_DATA_CRC_CHECK_YES)
    {
        nv_debug_record(NV_DEBUG_FLUSHEX_GET_PROTECT_SEM_START);
        osl_sem_down(&g_nv_ctrl.nv_buf_sem);
        nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
        nv_debug_record(NV_DEBUG_FLUSHEX_GET_PROTECT_SEM_END);

        crc_count = NV_CRC_CODE_COUNT((off + len - ctrl_info->ctrl_size)) - (off- ctrl_info->ctrl_size)/NV_CRC32_CHECK_SIZE;
        skip_crc_count = (off - ctrl_info->ctrl_size)/NV_CRC32_CHECK_SIZE;
        len = crc_count * NV_CRC32_CHECK_SIZE;
        if(off + len > ddr_info->file_len)
        {
            len = len - (off + len - ddr_info->file_len);
        }
        off = ctrl_info->ctrl_size + (skip_crc_count)*NV_CRC32_CHECK_SIZE;
        memcpy(g_nv_ctrl.p_nv_data_buf, (u8*)NV_GLOBAL_CTRL_INFO_ADDR + off, len);

        crc_value_off = ddr_info->file_len + (skip_crc_count + 1)* sizeof(u32);
        crc_value_len = crc_count * sizeof(u32);
        memcpy(g_nv_ctrl.p_nv_crc_buf, NV_GLOBAL_CTRL_INFO_ADDR + crc_value_off, crc_value_len);

        nv_ipc_sem_give(IPC_SEM_NV_CRC);
        nv_debug_record(NV_DEBUG_FLUSHEX_GIVE_IPC);


        nv_debug_record(NV_DEBUG_FLUSHEX_WRITE_FILE_START);
        (void)nv_file_seek(fp, off ,SEEK_SET);/*jump to write*/
        ret = (u32)nv_file_write((u8*)g_nv_ctrl.p_nv_data_buf,1,len,fp);
        if(ret != len)
        {
            nv_file_close(fp);
            nv_debug(NV_API_FLUSH,3, off , ret,len);
            ret = BSP_ERR_NV_WRITE_FILE_FAIL;
            osl_sem_up(&g_nv_ctrl.nv_buf_sem);
            goto nv_flush_err;
        }

        (void)nv_file_seek(fp, crc_value_off ,SEEK_SET);/*jump to write*/
        ret = (u32)nv_file_write((u8*)g_nv_ctrl.p_nv_crc_buf, 1, crc_value_len, fp);
        if(ret != crc_value_len)
        {
            nv_debug(NV_API_FLUSH,4, crc_value_off, ret,crc_value_len);
            ret = BSP_ERR_NV_WRITE_FILE_FAIL;
            nv_file_close(fp);
            osl_sem_up(&g_nv_ctrl.nv_buf_sem);
            goto nv_flush_err;
        }
        nv_debug_record(NV_DEBUG_FLUSHEX_WRITE_FILE_END);

        osl_sem_up(&g_nv_ctrl.nv_buf_sem);
        nv_debug_record(NV_DEBUG_FLUSHEX_GIVE_SEM);
    }
    else
    {
        (void)nv_file_seek(fp,(s32)off,SEEK_SET);/*jump to write*/
        ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR+off,1,len,fp);
        if(ret != len)
        {
            nv_file_close(fp);
            nv_debug(NV_API_FLUSH,5,0,ret,len);
            ret = BSP_ERR_NV_WRITE_FILE_FAIL;
            goto nv_flush_err;
        }
    }


    nv_file_close(fp);

    return NV_OK;

nv_flush_err:
    nv_mntn_record("\n[%s] len :0x%x, off :0x%x\n",__FUNCTION__,len,off);
    nv_help(NV_API_FLUSH);
    return ret;
}
/*lint -restore +e529*/

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

u32 bsp_nvm_flushEn(u32 crc_flag)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    u32 writeLen = 0;

    nv_create_flag_file((s8*)NV_IMG_FLAG_PATH);
    nv_debug(NV_API_FLUSH,0,0,0,0);
    fp = nv_file_open((s8*)NV_IMG_PATH,(s8*)NV_FILE_WRITE);
    if(NULL == fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_API_FLUSH,1,ret,0,0);
        goto nv_flush_err;
    }

    writeLen = ddr_info->file_len;

    if(NV_DATA_CRC_CHECK_YES)
    {
        writeLen += NV_CRC_CODE_COUNT(ddr_info->file_len - ctrl_info->ctrl_size)*sizeof(u32) \
                + sizeof(u32);/*sizeof是文件尾结束符*/
    }
    if(NV_CTRL_CRC_CHECK_YES)
    {
        writeLen += sizeof(u32);/*ctrl段CRC校验码*/
    }

    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    /*如果需要进行CRC校验*/
    if(NV_FLAG_NEED_CRC == crc_flag)
    {
        ret = nv_check_ddr_crc();
        if(ret)
        {
            nv_ipc_sem_give(IPC_SEM_NV_CRC);
            nv_debug(NV_API_FLUSH, 4, ret, 0, 0);
            (void)nv_debug_store_ddr_data();
            goto nv_flush_err;
        }
    }
    ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1, writeLen, fp);
    nv_ipc_sem_give(IPC_SEM_NV_CRC);
    nv_file_close(fp);
    fp = NULL;
    if(ret != writeLen)
    {
        nv_debug(NV_API_FLUSH,5,(u32)(unsigned long)fp,ret,writeLen);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_flush_err;
    }
    nv_delete_flag_file((s8*)NV_IMG_FLAG_PATH);

    return NV_OK;

nv_flush_err:
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_API_FLUSH);
    return ret;
}


u32 bsp_nvm_flushSys(u32 itemid)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 ulTotalLen = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_create_flag_file((s8*)NV_SYS_FLAG_PATH);

    nv_debug(NV_FUN_FLUSH_SYS,0,0,0,0);
    if(nv_file_access((s8*)NV_FILE_SYS_NV_PATH,0))
    {
        fp = nv_file_open((s8*)NV_FILE_SYS_NV_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        fp = nv_file_open((s8*)NV_FILE_SYS_NV_PATH,(s8*)NV_FILE_RW);
    }
    if(NULL == fp)
    {
        nv_debug(NV_FUN_FLUSH_SYS,1,ret,0,0);
        ret = BSP_ERR_NV_NO_FILE;
        goto nv_flush_err;
    }
    ulTotalLen = ddr_info->file_len;
#if defined(FEATURE_NV_FLASH_ON)
    /*在nvdload分区文件末尾置标志0xabcd8765*/
    *( unsigned int* )( (u8*)NV_GLOBAL_CTRL_INFO_ADDR + ddr_info->file_len )
        = ( unsigned int )NV_FILE_TAIL_MAGIC_NUM;
    ulTotalLen += sizeof(unsigned int);
#endif
    /*系统分区数据不做CRC校验，因此回写时不考虑CRC校验码的存放位置*/
    ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,ulTotalLen,fp);
    nv_file_close(fp);
    if(ret != ulTotalLen)
    {
        nv_debug(NV_FUN_FLUSH_SYS,3,ret,ulTotalLen,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_flush_err;
    }

    nv_delete_flag_file((s8*)NV_SYS_FLAG_PATH);
    return NV_OK;

nv_flush_err:
    nv_mntn_record("\n[%s]\n",__func__);
    nv_help(NV_FUN_FLUSH_SYS);
    return ret;
}



u32 bsp_nvm_backup(u32 crc_flag)
{
    u32 ret = NV_ERROR;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    FILE* fp = NULL;
    u32 writeLen = 0;
    nv_debug(NV_API_BACKUP,0,0,0,0);

    if( (ddr_info->acore_init_state != NV_INIT_OK)&&
        (ddr_info->acore_init_state != NV_KERNEL_INIT_DOING))
    {
        return NV_ERROR;
    }

    nv_create_flag_file((s8*)NV_BACK_FLAG_PATH);

    if(nv_file_access((s8*)NV_BACK_PATH,0))
    {
        fp = nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        fp = nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_RW);
    }
    if(NULL == fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_API_BACKUP,1,ret,0,0);
        goto nv_backup_fail;
    }

    writeLen = ddr_info->file_len;
    if(NV_DATA_CRC_CHECK_YES)
    {
        writeLen +=  NV_CRC_CODE_COUNT(ddr_info->file_len - ctrl_info->ctrl_size)*sizeof(u32) + sizeof(u32);
    }
    if(NV_CTRL_CRC_CHECK_YES)
    {
        writeLen += sizeof(u32);/*sizeof是文件尾结束符和ctrl段CRC校验码*/
    }

    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    /*如果需要进行CRC校验*/
    if(NV_FLAG_NEED_CRC == crc_flag)
    {
        ret = nv_check_ddr_crc();
        if(ret)
        {
            nv_ipc_sem_give(IPC_SEM_NV_CRC);
            nv_debug(NV_API_BACKUP,2,ret,0, 0);
            (void)nv_debug_store_ddr_data();
            goto nv_backup_fail;
        }
    }
    ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,writeLen,fp);
    nv_ipc_sem_give(IPC_SEM_NV_CRC);
    nv_file_close(fp);
    fp = NULL;
    if(ret != writeLen)
    {
        nv_debug(NV_API_BACKUP,3,ret,writeLen,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_backup_fail;
    }

    if(nv_file_update(NV_BACK_PATH))
    {
        nv_debug(NV_API_BACKUP, 4 , 0, 0, 0);
    }

    nv_delete_flag_file((s8*)NV_BACK_FLAG_PATH);

    return NV_OK;
nv_backup_fail:
    if(fp){nv_file_close(fp);}
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_API_BACKUP);
    return ret;

}

#ifdef CONFIG_MULTI_CARRIER
/*
* Function   : bsp_nvm_mtcarrier_backup
* Discription: flush the memory to sys sec for system use
* Parameter  : none
* Output     : result
* History    :
*/
u32 bsp_nvm_mtcarrier_backup(char* back_path)
{
    u32 ret = NV_ERROR;
    s32 routine_len = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    FILE* mt_fp = NULL;
    char  mtca_rontine[MTCA_ROUTINE_MAX_LENGTH];

    if(NULL == back_path)
    {
        ret = BSP_ERR_NV_INVALID_PARAM;
        printk("here path error\n");
        nv_debug(NV_FUN_MTCARRIER_BACKUP,1,ret,0,0);  /* para2 is 0,is right? */
        return NV_ERROR;
    }

    if( (ddr_info->acore_init_state != NV_INIT_OK)&&
        (ddr_info->acore_init_state != NV_KERNEL_INIT_DOING))
    {
        printk("%s init error\n",__FUNCTION__);
        return NV_ERROR;
    }

    if(nv_file_access((s8*)NV_BACK_MTCARRIER_FLAG_PATH,0))
    {
        mt_fp = nv_file_open((s8*)NV_BACK_MTCARRIER_FLAG_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        mt_fp = nv_file_open((s8*)NV_BACK_MTCARRIER_FLAG_PATH,(s8*)NV_FILE_RW);
    }
    ret = (u32)nv_file_write((u8*)NV_BACK_MTCARRIER_FLAG_PATH,1,sizeof(back_path),mt_fp);
    nv_file_close(mt_fp);
    if(ret!=sizeof(back_path))
    {
        printk("%s save rountine error, ret is %d\n",mtca_rontine,ret);
        return NV_ERROR;
    }

    /* packet a nv.bin rountine */
    routine_len = snprintf(mtca_rontine,(MTCA_ROUTINE_MAX_LENGTH-1),"%s/nv.bin",back_path);
    if(!routine_len)
    {
        printk("%s rountine error\n",mtca_rontine);
        return NV_ERROR;
    }

    if(nv_file_access((s8*)mtca_rontine,0))
    {
        mt_fp = nv_file_open((s8*)mtca_rontine,(s8*)NV_FILE_WRITE);
    }
    else
    {
        mt_fp = nv_file_open((s8*)mtca_rontine,(s8*)NV_FILE_RW);
    }

    if(NULL == mt_fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_FUN_MTCARRIER_BACKUP,2,ret,0,0);
        printk("open error\n");
        goto nv_backup_mtcarrierr_fail;
    }

    ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,ddr_info->file_len,mt_fp);
    nv_file_close(mt_fp);
    mt_fp = NULL;
    if(ret != ddr_info->file_len)
    {
        nv_debug(NV_FUN_MTCARRIER_BACKUP,3,ret,ddr_info->file_len,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        printk("write error\n");
        goto nv_backup_mtcarrierr_fail;
    }

    //nv_delete_flag_file((s8*)NV_BACK_MTCARRIER_FLAG_PATH);

    return NV_OK;
nv_backup_mtcarrierr_fail:
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_MTCARRIER_BACKUP);
    return ret;
}
#endif


u32 bsp_nvm_revert_user(void)
{
    return nv_revert_data(NV_BACK_PATH,g_ausNvResumeUserIdList,\
        bsp_nvm_getRevertNum(NV_USER_ITEM), NV_FLAG_NEED_CRC);
}


u32 bsp_nvm_revert_manufacture(void)
{
    return nv_revert_data(NV_BACK_PATH,g_ausNvResumeManufactureIdList,\
        bsp_nvm_getRevertNum(NV_MANUFACTURE_ITEM), NV_FLAG_NEED_CRC);
}

u32 bsp_nvm_revert_secure(void)
{
    return nv_revert_data(NV_BACK_PATH,g_ausNvResumeSecureIdList,\
        bsp_nvm_getRevertNum(NV_SECURE_ITEM), NV_FLAG_NEED_CRC);
}

u32 bsp_nvm_revert(void)
{
    u32 ret  = NV_ERROR;

    nv_debug(NV_API_REVERT,0,0,0,0);

    nv_printf("enter to revert nv !\n");
    ret = bsp_nvm_revert_user();
    if(ret)
    {
        nv_debug(NV_API_REVERT,1,ret,0,0);
        goto nv_revert_fail;
    }

    ret = bsp_nvm_revert_manufacture();
    if(ret)
    {
        nv_debug(NV_API_REVERT,2,ret,0,0);
        goto nv_revert_fail;
    }
    ret = bsp_nvm_revert_secure();
    if(ret)
    {
        nv_debug(NV_API_REVERT,3,ret,0,0);
        goto nv_revert_fail;
    }
    nv_printf("revert nv end !\n");

    return NV_OK;
nv_revert_fail:
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_API_REVERT);
    return ret;
}




u32 bsp_nvm_update_default(void)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    NV_SELF_CTRL_STRU self_ctrl = {};

    nv_debug(NV_FUN_UPDATE_DEFAULT,0,0,0,0);

    if(ddr_info->acore_init_state != NV_INIT_OK)
    {
        return NV_ERROR;
    }

#if defined(BSP_CONFIG_PHONE_TYPE)
    if(false == nv_check_update_default_right())
    {
        nv_printf("no right to write factory data!\n");
    }
#endif

    ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL, (u8*)&self_ctrl, sizeof(NV_SELF_CTRL_STRU));
    if(ret)
    {
        nv_printf("read nv 0x%x fail,ret = 0x%x\n", NV_ID_DRV_SELF_CTRL);
        return NV_ERROR;
    }
    self_ctrl.ulResumeMode = NV_MODE_USER;
    ret = bsp_nvm_write(NV_ID_DRV_SELF_CTRL, (u8*)&self_ctrl, sizeof(NV_SELF_CTRL_STRU));
    if(ret)
    {
        nv_printf("write nv 0x%x fail,ret = 0x%x\n", NV_ID_DRV_SELF_CTRL);
        return NV_ERROR;
    }
    /*在写入文件前进行CRC校验，以防数据不正确*/
    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    ret = nv_check_ddr_crc();
    if(ret)
    {
        nv_ipc_sem_give(IPC_SEM_NV_CRC);
        nv_debug(NV_FUN_UPDATE_DEFAULT,3,ret,ddr_info->file_len,0);
        (void)nv_debug_store_ddr_data();
        goto nv_update_default_err;
    }
    nv_ipc_sem_give(IPC_SEM_NV_CRC);

    if(nv_file_access((s8*)NV_DEFAULT_PATH,0))
    {
        fp = nv_file_open((s8*)NV_DEFAULT_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        fp = nv_file_open((s8*)NV_DEFAULT_PATH,(s8*)NV_FILE_RW);
    }
    if(NULL == fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_FUN_UPDATE_DEFAULT,2,ret,0,0);
        goto nv_update_default_err;
    }
    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    datalen = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,ddr_info->file_len,fp);
    nv_ipc_sem_give(IPC_SEM_NV_CRC);

    nv_file_close(fp);
    if(datalen != ddr_info->file_len)
    {
        nv_debug(NV_FUN_UPDATE_DEFAULT,6,ret,ddr_info->file_len,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_update_default_err;
    }

    ret = bsp_nvm_backup(NV_FLAG_NO_CRC);
    if(ret)
    {
        nv_debug(NV_FUN_UPDATE_DEFAULT,7,ret,0,0);
        goto nv_update_default_err;
    }

#if defined(BSP_CONFIG_PHONE_TYPE)
    nv_delete_update_default_right();
#endif

    return NV_OK;
nv_update_default_err:
    if(fp){nv_file_close(fp);}
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_UPDATE_DEFAULT);
    return ret;
}


u32 bsp_nvm_revert_defaultEx(const s8* path)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    FILE* fp = NULL;
    struct nv_ctrl_file_info_stru  manu_ctrl_file = {0};
    u8* ctrl_file_data = NULL;
    struct nv_global_ddr_info_stru *manu_ddr_info = NULL;


    nv_debug(NV_FUN_REVERT_DEFAULT,0,0,0,0);
    fp = nv_file_open((s8*)path,(s8*)NV_FILE_READ);
    if(NULL == fp)
    {
        nv_debug(NV_FUN_REVERT_DEFAULT,1,0,0,0);
        return BSP_ERR_NV_NO_FILE;
    }

    ret = (u32)nv_file_read((u8*)&manu_ctrl_file,1,sizeof(manu_ctrl_file),fp);
    if(ret != sizeof(manu_ctrl_file))
    {
        nv_debug(NV_FUN_REVERT_DEFAULT,2,ret,0,0);
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        goto file_close_err;
    }
    nv_file_seek(fp,0,SEEK_SET);
    ctrl_file_data = (u8*)vmalloc(manu_ctrl_file.ctrl_size+1);
    if(NULL == ctrl_file_data)
    {
        nv_debug(NV_FUN_REVERT_DEFAULT,3,BSP_ERR_NV_MALLOC_FAIL,0,0);
        ret = BSP_ERR_NV_MALLOC_FAIL;
        goto file_close_err;
    }

    ret = (u32)nv_file_read(ctrl_file_data,1,manu_ctrl_file.ctrl_size,fp);
    if(ret != manu_ctrl_file.ctrl_size)
    {
        nv_error_printf("ret 0x%x,ctrl size 0x%x\n",ret,manu_ctrl_file.ctrl_size);
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        nv_debug(NV_FUN_REVERT_DEFAULT,4,ret,manu_ctrl_file.ctrl_size,0);
        goto free_ctrl_file;
    }
    manu_ddr_info = (struct nv_global_ddr_info_stru *)nv_malloc(sizeof(struct nv_global_ddr_info_stru));
    if(!manu_ddr_info)
    {
        ret = BSP_ERR_NV_MALLOC_FAIL;
        nv_debug(NV_FUN_REVERT_DEFAULT,5,ret,manu_ctrl_file.ctrl_size,0);
        goto free_ctrl_file;
    }
    ret = nv_init_file_info((u8*)ctrl_file_data,(u8*)manu_ddr_info);
    if(ret)
    {
        nv_debug(NV_FUN_REVERT_DEFAULT,6,ret,0,0);
        ret = BSP_ERR_NV_MEM_INIT_FAIL;
        goto free_ctrl_file;
    }
    for(i = 0;i<manu_ctrl_file.file_num;i++)
    {
        ret = nv_revert_default(fp,manu_ddr_info->file_info[i].size);
        if(ret)
        {
            nv_debug(NV_FUN_REVERT_DEFAULT,7,ret,manu_ddr_info->file_info[i].size,0);
            goto free_ctrl_file;
        }
    }

    if(fp){nv_file_close(fp);}
    if(ctrl_file_data)vfree(ctrl_file_data);
    if(manu_ddr_info){nv_free((void *)manu_ddr_info);}

    return NV_OK;
free_ctrl_file:
    if(ctrl_file_data){vfree(ctrl_file_data);}
    if(manu_ddr_info){nv_free((void *)manu_ddr_info);}
file_close_err:
    nv_file_close(fp);
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_REVERT_DEFAULT);
    return ret;
}


u32 bsp_nvm_revert_default(void)
{
    u32 ret;

    ret = bsp_nvm_revert_defaultEx((s8*)NV_DEFAULT_PATH);
    if(ret)
    {
        return ret;
    }

    /*机要nv项不恢复,需要重新生成CRC校验码*/
    ret = nv_revert_data(NV_IMG_PATH,g_ausNvResumeSecureIdList,\
        bsp_nvm_getRevertNum(NV_SECURE_ITEM), NV_FLAG_NEED_CRC);
    if(ret)
    {
        return ret;
    }

    ret = bsp_nvm_flushEn(NV_FLAG_NEED_CRC);
    ret |= bsp_nvm_flushSys(NV_ERROR);
    return ret;
}

s32 bsp_nvm_icc_task(void* parm)
{
    s32 ret = -1;
    struct nv_icc_stru icc_req;
    /* coverity[var_decl] */
    struct nv_icc_stru icc_cnf;
    u32 chanid = 0;

    /* coverity[no_escape] */
    for(;;)
    {
        osl_sem_down(&g_nv_ctrl.task_sem);

        g_nv_ctrl.opState = NV_OPS_STATE;
        wake_lock(&g_nv_ctrl.wake_lock);

        /*如果当前处于睡眠状态，则等待唤醒处理*/
        if(g_nv_ctrl.pmState == NV_SLEEP_STATE)
        {
            printk("%s cur state in sleeping,wait for resume end!\n",__func__);
            continue;
        }
        if(g_nv_ctrl.acore_flush_req)
        {
            /*deal with acore msg*/
            memset(&icc_req, 0, sizeof(icc_req));
            icc_req.msg_type = g_nv_ctrl.acore_flush_req;
            g_nv_ctrl.acore_flush_req = 0;
        }
        else
        {
            /*deal with ccore msg*/
            memset(g_nv_ctrl.nv_icc_buf,0,NV_ICC_BUF_LEN);
            memset(&icc_req,0,sizeof(icc_req));

            chanid = ICC_CHN_NV << 16 | NV_RECV_FUNC_AC;
            ret = bsp_icc_read(chanid,g_nv_ctrl.nv_icc_buf,NV_ICC_BUF_LEN);
            if(((u32)ret > NV_ICC_BUF_LEN)||(ret <= 0))
            {
                nv_debug_printf("bsp icc read error, chanid :0x%x ret :0x%x\n",chanid,ret);

                chanid = ICC_CHN_MCORE_ACORE << 16 | NV_RECV_FUNC_AM;
                ret = bsp_icc_read(chanid,g_nv_ctrl.nv_icc_buf,NV_ICC_BUF_LEN);
                if(((u32)ret > NV_ICC_BUF_LEN)||(ret <= 0))
                {
                    g_nv_ctrl.opState = NV_IDLE_STATE;
                    wake_unlock(&g_nv_ctrl.wake_lock);
                    nv_debug_printf("bsp icc read error, chanid :0x%x ret :0x%x\n",chanid,ret);
                    continue;
                }
            }
            memcpy(&icc_req,g_nv_ctrl.nv_icc_buf,sizeof(icc_req));
            /*lint -save -e578 -e530*/
            nv_debug_trace(&icc_req, sizeof(icc_req));
        }
        g_nv_ctrl.task_proc_count ++;

        /*lint -restore +e578 +e530*/
        if(icc_req.msg_type == NV_ICC_REQ_SYS)
        {
            icc_cnf.ret = bsp_nvm_flushSys(icc_req.itemid);
        }
        else if(icc_req.msg_type == NV_ICC_RESUME)
        {
            icc_cnf.ret = nv_resume_ddr_from_img();
        }
        else if(icc_req.msg_type == NV_ICC_REQ_INSTANT_FLUSH)
        {
            /**flush to flush no delay*/
            icc_cnf.ret = nv_flushList();
        }
        else if((icc_req.msg_type == NV_ICC_REQ_CCORE_DELAY_FLUSH)||(icc_req.msg_type == NV_REQ_ACORE_DELAY_FLUSH))
        {
            /*flush to flash delay and no cnf*/
            icc_cnf.ret = nv_flushList();
            if(icc_cnf.ret)
            {
                nv_mntn_record("flush to nv file fail, fail info:0x%x\n", icc_cnf.ret);
                nv_mntn_record("req core:%s ret:0x%x, req slice 0x%x fail slice:0x%x\n", (icc_req.msg_type == NV_ICC_REQ_CCORE_DELAY_FLUSH)?"ccore":"acore",\
                    icc_cnf.ret, icc_req.slice, bsp_get_slice_value());
            }
            wake_unlock(&g_nv_ctrl.wake_lock);
            osl_sem_up(&g_nv_ctrl.task_sem);
            continue;
        }
        else
        {
            nv_printf("invalid parameter :0x%x\n",icc_req.msg_type);
            wake_unlock(&g_nv_ctrl.wake_lock);
            osl_sem_up(&g_nv_ctrl.task_sem);
            continue;
        }
        nv_pm_trace(icc_req);

        icc_cnf.msg_type = NV_ICC_CNF;
        icc_cnf.data_off = icc_req.data_off;
        icc_cnf.data_len = icc_req.data_len;
        icc_cnf.itemid   = icc_req.itemid;
        icc_cnf.slice    = bsp_get_slice_value();

        /* coverity[uninit_use_in_call] */
        ret = (s32)nv_icc_send(chanid,(u8*)&icc_cnf,sizeof(icc_cnf));
        if(ret)
        {
            nv_printf("icc send error !\n");
        }
        wake_unlock(&g_nv_ctrl.wake_lock);
        osl_sem_up(&g_nv_ctrl.task_sem);
    }
}


u32 bsp_nvm_xml_decode(void)
{
    u32 ret = NV_ERROR;

    if(!nv_file_access(NV_XNV_CARD1_PATH,0))
    {
        ret = nv_xml_decode(NV_XNV_CARD1_PATH,NV_XNV_CARD1_MAP_PATH,NV_USIMM_CARD_1);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_XNV_CARD2_PATH,0))
    {
        ret = nv_xml_decode(NV_XNV_CARD2_PATH,NV_XNV_CARD2_MAP_PATH,NV_USIMM_CARD_2);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_XNV_CARD3_PATH,0))
    {
        ret = nv_xml_decode(NV_XNV_CARD3_PATH, NV_XNV_CARD3_MAP_PATH, NV_USIMM_CARD_3);
        if(ret)
        {
            return ret;
        }
    }

    /*CUST XML 无对应MAP文件，传入空值即可*/
    if(!nv_file_access(NV_CUST_CARD1_PATH,0))
    {
        ret = nv_xml_decode(NV_CUST_CARD1_PATH,NULL,NV_USIMM_CARD_1);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_CUST_CARD2_PATH,0))
    {
        ret = nv_xml_decode(NV_CUST_CARD2_PATH,NULL,NV_USIMM_CARD_2);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_CUST_CARD3_PATH,0))
    {
        ret = nv_xml_decode(NV_CUST_CARD3_PATH, NULL, NV_USIMM_CARD_3);
        if(ret)
        {
            return ret;
        }
    }

    return NV_OK;
}

#ifdef CONFIG_MULTI_CARRIER
/*
* Function   : bsp_nvm_mtcarrier_cust_xml_decode
* Discription: flush the memory to sys sec for system use
* Parameter  : none
* Output     : result
* History    :
*/
u32 bsp_nvm_mtcarrier_cust_xml_decode(void)
{
    u32 ret = NV_ERROR;
    s32 routine_len ;
    s32 read_len= 0;
    s8* norm_routine = NULL;
    s8  mtca_cust_rontine[MTCA_ROUTINE_MAX_LENGTH] = {};
    FILE* mt_fp = NULL;

    if(nv_file_access((s8*)NV_BACK_MTCARRIER_FLAG_PATH,0))
    {
        mt_fp = nv_file_open((s8*)NV_BACK_MTCARRIER_FLAG_PATH,(s8*)NV_FILE_READ);
    }
    else
    {
        printk("get %s rountine error\n",NV_BACK_MTCARRIER_FLAG_PATH);
        return NV_ERROR;
    }
    read_len = nv_get_file_len(mt_fp);
    if(read_len<0)
    {
        printk("read length error, read_len is %d\n",read_len);
        return NV_ERROR;
    }
    norm_routine = (s8*)nv_malloc(read_len + 1);
    if(!norm_routine)
    {
        printk("malloc fail, len:0x%x\n",read_len);
        return NV_ERROR;
    }
    ret = nv_file_read(norm_routine, 1, read_len, mt_fp);
    if(ret != read_len)
    {
        nv_free(norm_routine);
        printk("read length not equal,ret is %d,read_len is %d \n",ret,read_len);
        return NV_ERROR;
    }
    nv_file_close(mt_fp);


    /*get path*/
    routine_len = snprintf(mtca_cust_rontine,(MTCA_ROUTINE_MAX_LENGTH-1),"%s/cust.xml",norm_routine);
    nv_free(norm_routine);
    norm_routine = NULL;
    if(!routine_len)
    {
        printk("%s rountine error\n",mtca_cust_rontine);
        return NV_ERROR;
    }

    if(NULL==mtca_cust_rontine)
    {
        ret = BSP_ERR_NV_INVALID_PARAM;
        return NV_ERROR;
    }

    /*MUTI CARRIER CUST XML 无对应MAP文件，传入空值即可*/
    if(!nv_file_access(mtca_cust_rontine,0))
    {
        ret = nv_xml_decode(mtca_cust_rontine,NULL,NV_USIMM_CARD_1);
        if(ret)
        {
            return ret;
        }
    }

    /*CUST XML 无对应MAP文件，传入空值即可*/
    if(!nv_file_access(mtca_cust_rontine,0))
    {
        ret = nv_xml_decode(mtca_cust_rontine,NULL,NV_USIMM_CARD_2);
        if(ret)
        {
            return ret;
        }
    }

    return ret;
}

/*
* Function   : bsp_nvm_revert_mtcarrier_user
* Discription: flush the memory to sys sec for system use
* Parameter  : none
* Output     : result
* History    :
*/
u32 bsp_nvm_revert_mtcarrier_user(void)
{
    s8  mtca_user_rontine[MTCA_ROUTINE_MAX_LENGTH] = {};
    s32 ret = 0;
    s32 read_len= 0;
    u32 file_length = 0;
    struct nv_mtcarrier_userlist_bin_stru nv_mt_bin_list = {0};
    FILE* mt_fp = NULL;
    s8* norm_routine = NULL;
    u16* nvidlist = NULL;
    s32 routine_len ;

    /*get path*/
    if(nv_file_access((s8*)NV_BACK_MTCARRIER_FLAG_PATH,0))
    {
        mt_fp = nv_file_open((s8*)NV_BACK_MTCARRIER_FLAG_PATH,(s8*)NV_FILE_READ);
    }
    else
    {
        printk("get %s rountine error\n",NV_BACK_MTCARRIER_FLAG_PATH);
        return NV_ERROR;
    }
    read_len = nv_get_file_len(mt_fp);
    if(read_len<0)
    {
        printk("read length error, read_len is %d\n",read_len);
        return NV_ERROR;
    }
    norm_routine = (s8*)nv_malloc(read_len + 1);
    if(!norm_routine)
    {
        printk("malloc fail, len:0x%x\n",read_len);
        return NV_ERROR;
    }
    ret = nv_file_read(norm_routine, 1, read_len, mt_fp);
    if(ret != read_len)
    {
        nv_free(norm_routine);
        printk("read length not equal,ret is %d,read_len is %d \n",ret,read_len);
        return NV_ERROR;
    }
    nv_file_close(mt_fp);
    nv_file_remove((s8*)NV_BACK_MTCARRIER_FLAG_PATH);

    routine_len = snprintf(mtca_user_rontine,(MTCA_ROUTINE_MAX_LENGTH-1),"%s/usr_list.bin",norm_routine);
    nv_free(norm_routine);
    norm_routine = NULL;
    if(!routine_len)
    {
        printk("%s rountine error\n",mtca_user_rontine);
        return NV_ERROR;
    }

    if(NULL==mtca_user_rontine)
    {
        ret = BSP_ERR_NV_INVALID_PARAM;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,1,ret,0,0);  /* para2 is 0,is right? */
        return NV_ERROR;
    }

    /* */
    if(nv_file_access(mtca_user_rontine,0))
    {
        mt_fp = nv_file_open(mtca_user_rontine,(s8*)NV_FILE_WRITE);
    }

    if(NULL == mt_fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,2,ret,0,0);
        goto nv_revert_mtcarrier_fail;
    }

    file_length = nv_get_file_len(mt_fp);
    if((file_length > NV_MAX_FILE_SIZE)||(file_length == 0))
    {
        ret = BSP_ERR_NV_FILE_ERROR;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,3,ret,0,0);
        goto nv_revert_mtcarrier_fail;
    }

    ret = (u32)nv_file_read((u8*)&nv_mt_bin_list,1,sizeof(nv_mt_bin_list),mt_fp);
    if(ret<0)
    {
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,4,ret,0,0);

        goto nv_revert_mtcarrier_fail;
    }

    if(NV_MTCARRIER_USR_BIN_MAGIC != nv_mt_bin_list.magic_head)
    {
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,5,ret,0,0);

        goto nv_revert_mtcarrier_fail;
    }

    if(0==nv_mt_bin_list.nvid_num)
    {
        ret = BSP_ERR_NV_FILE_ERROR;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,6,ret,0,0);

        goto nv_revert_mtcarrier_fail;
    }

    nvidlist = (u16 *)nv_malloc(nv_mt_bin_list.nvid_num * sizeof(u16));
    if(NULL == nvidlist)
    {
        ret = BSP_ERR_NV_FILE_ERROR;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,7,ret,0,0);

        goto nv_revert_mtcarrier_fail;
    }

    /* seek nv file */
    nv_file_seek(mt_fp,0,SEEK_SET);

    ret = (u32)nv_file_read((u8*)(nvidlist),1,nv_mt_bin_list.nvid_num * sizeof(u16),mt_fp);
    if(ret<0)
    {
        nv_free(nvidlist);
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,8,ret,0,0);

        goto nv_revert_mtcarrier_fail;
    }

    ret = nv_revert_data(NV_BACK_PATH,nvidlist,nv_mt_bin_list.nvid_num, NV_FLAG_NO_CRC);
    if(ret<0)
    {
        ret = BSP_ERR_NV_BACKUP_DATA_FAIL;
        nv_debug(NV_FUN_MTCARRIER_USR_REVERT,9,ret,0,0);

        goto nv_revert_mtcarrier_fail;
    }

    nv_free(nvidlist);

    return NV_OK;
nv_revert_mtcarrier_fail:
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_MTCARRIER_USR_REVERT);
    return ret;
}
#endif

u32 bsp_nvm_upgrade(void)
{
    u32 ret;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_debug(NV_FUN_UPGRADE_PROC,0,0,0,0);


    /*判断fastboot阶段xml 解析是否异常，若出现异常，则需要重新解析xml*/
    if(ddr_info->xml_dec_state != NV_XML_DEC_SUCC_STATE)
    {
        ret = bsp_nvm_xml_decode();
        if(ret)
        {
            nv_debug(NV_FUN_UPGRADE_PROC,1,ret,0,0);
            goto upgrade_fail_out;
        }
    }
    ret = nv_set_crc_offset();
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,2,ret,0,0);
        goto upgrade_fail_out;
    }

#ifdef CONFIG_MULTI_CARRIER
    ret = bsp_nvm_mtcarrier_cust_xml_decode();
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,3,ret,0,0);
        goto upgrade_fail_out;
    }
#endif

    /*升级恢复处理，烧片版本直接返回ok*/
    ret = nv_upgrade_revert_proc();
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,4,ret,0,0);
        goto upgrade_fail_out;
    }
#ifdef CONFIG_MULTI_CARRIER
    ret = bsp_nvm_revert_mtcarrier_user();
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,5,ret,0,0);
        goto upgrade_fail_out;
    }
#endif

    ret = nv_make_ddr_crc();
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,6,ret,0,0);
        goto upgrade_fail_out;
    }
    /*将最新数据写入各个分区*/
    ret = nv_data_writeback();
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,7,ret,0,0);
        goto upgrade_fail_out;
    }

    /*置升级包无效*/
    ret = (u32)nv_modify_upgrade_flag(false);/*lint !e747 */
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC,8,ret,0,0);
        goto upgrade_fail_out;
    }

    ret = nv_file_update(NV_DLOAD_PATH);
    if(ret)
    {
        nv_debug(NV_FUN_UPGRADE_PROC, 9,ret,0,0);
        goto upgrade_fail_out;
    }

    return NV_OK;
upgrade_fail_out:
    nv_mntn_record("\n%s\n",__func__);
    nv_help(NV_FUN_UPGRADE_PROC);
    return NV_ERROR;
}

u32 bsp_nvm_resume_bakup(void)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;

    if(true == nv_check_file_validity((s8 *)NV_BACK_PATH, (s8 *)NV_BACK_FLAG_PATH))
    {
        nv_mntn_record("load from %s ...%s %s \n",NV_BACK_PATH,__DATE__,__TIME__);
        fp = nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_READ);
        if(!fp)
        {
            nv_debug(NV_FUN_MEM_INIT,5,0,0,0);
            goto load_err_proc;
        }

        ret = nv_read_from_file(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen, NV_FILE_BACKUP);
        nv_file_close(fp);
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,6,0,0,0);
            goto load_err_proc;
        }
        ret = nv_set_crc_offset();
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,7,ret,0,0);
            goto load_err_proc;
        }

        ret = nv_check_ddr_crc();
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,8,ret,0,0);
            goto load_err_proc;
        }

        /*从备份区加载需要首先写入工作区*/
        ret = bsp_nvm_flushEn(NV_FLAG_NO_CRC);
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,9,0,0,0);
            goto load_err_proc;
        }

        return NV_OK;
    }

load_err_proc:
    ret = nv_load_err_proc();
    if(ret)
    {
        nv_mntn_record("%s %d ,err revert proc ,ret :0x%x\n",__func__,__LINE__,ret);
        nv_help(NV_FUN_MEM_INIT);
    }

    return ret;
}



u32 bsp_nvm_reload(void)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;

    nv_debug(NV_FUN_MEM_INIT,0,0,0,0);

    /*工作分区数据存在，且无未写入完成的标志文件*/
    if( true == nv_check_file_validity((s8 *)NV_IMG_PATH, (s8 *)NV_IMG_FLAG_PATH))
    {
        nv_mntn_record("load from %s ...%s %s \n",NV_IMG_PATH,__DATE__,__TIME__);
        fp = nv_file_open((s8*)NV_IMG_PATH,(s8*)NV_FILE_READ);
        if(!fp)
        {
            nv_debug(NV_FUN_MEM_INIT,1,0,0,0);
            goto load_bak;
        }

        ret = nv_read_from_file(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen, NV_FILE_SYS_NV);
        nv_file_close(fp);
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,2,ret,0,0);
            goto load_bak;
        }

        ret = nv_set_crc_offset();
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,3,ret,0,0);
            goto load_bak;
        }

        ret = nv_check_ddr_crc();
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,4,ret,0,0);
            nv_mntn_record("nv image check crc failed %d...%s %s \n", ret, __DATE__,__TIME__);

            /* 保存错误镜像，然后从bakup分区恢复 */
            (void)nv_debug_store_file(NV_IMG_PATH);
            if(nv_debug_is_resume_bakup())
            {
                ret = bsp_nvm_resume_bakup();
                if(ret)
                {
                    nv_mntn_record("nv resume bakup failed %d...%s %s \n", ret, __DATE__,__TIME__);
                }
            }
            else
            {
                nv_mntn_record("config don't resume bakup...%s %s \n",__DATE__,__TIME__);
            }

            /* 复位系统 */
            if(nv_debug_is_reset())
            {
                system_error(DRV_ERRNO_NV_CRC_ERR, NV_FUN_MEM_INIT, 3, NULL, 0);
            }
        }

        return ret;
    }

load_bak:

    return bsp_nvm_resume_bakup();
}
/*****************************************************************************
 函 数 名  : bsp_nvm_write_buf_init
 功能描述  : 初始化写入NV时使用的buf和信号量
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 bsp_nvm_buf_init(void)
{
    /*create sem*/
    osl_sem_init(1,&g_nv_ctrl.nv_buf_sem);

    /*malloc buf*/
    g_nv_ctrl.p_nv_data_buf = (void *)nv_malloc(NV_CRC32_CHECK_SIZE*3);

    if(NULL == g_nv_ctrl.p_nv_data_buf)
    {
        nv_printf("malloc p_nv_data_buf fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }
    g_nv_ctrl.p_nv_crc_buf = (void *)nv_malloc((SHM_MEM_NV_SIZE/NV_CRC32_CHECK_SIZE + 1) * sizeof(u32));
    if(NULL == g_nv_ctrl.p_nv_crc_buf)
    {
        nv_free(g_nv_ctrl.p_nv_data_buf);
        nv_printf("malloc p_nv_crc_buf fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    /*create sem*/
    osl_sem_init(1,&g_nv_ctrl.nv_list_sem);
    INIT_LIST_HEAD(&g_nv_ctrl.nv_list);

    return NV_OK;
}

s32 bsp_nvm_kernel_init(void)
{
    u32 ret = NV_ERROR;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    nv_debug(NV_FUN_KERNEL_INIT,0,0,0,0);

    /*sem & lock init*/
    spin_lock_init(&g_nv_ctrl.spinlock);
    osl_sem_init(0,&g_nv_ctrl.task_sem);
    osl_sem_init(1,&g_nv_ctrl.rw_sem);
    osl_sem_init(0,&g_nv_ctrl.cc_sem);
    wake_lock_init(&g_nv_ctrl.wake_lock,WAKE_LOCK_SUSPEND,"nv_wakelock");
    g_nv_ctrl.shared_addr = (struct nv_global_ddr_info_stru *)NV_GLOBAL_INFO_ADDR;

    nv_mntn_record("Balong nv init  start! %s %s\n",__DATE__,__TIME__);

    (void)nv_debug_init();

    /*file info init*/
    ret = nv_file_init();
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,1,ret,0,0);
        goto out;
    }
    if(ddr_info->acore_init_state != NV_BOOT_INIT_OK)
    {
        nv_mntn_record("fast boot nv init fail !\n");
        nv_show_fastboot_err();
        memset(ddr_info,0,sizeof(struct nv_global_ddr_info_stru));
    }

    ddr_info->acore_init_state = NV_KERNEL_INIT_DOING;
    nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, (u32)NV_GLOBAL_INFO_SIZE);

    if((ddr_info->mem_file_type == NV_MEM_DLOAD) &&
       (!nv_file_access((s8*)NV_DLOAD_PATH,0)) &&/*升级分区存在数据*/
       (true == nv_get_upgrade_flag())/*升级文件有效*/
       )
    {
        ret = bsp_nvm_upgrade();
        if(ret)
        {
            nv_debug(NV_FUN_KERNEL_INIT,3,ret,0,0);
            goto out;
        }
        /*读取NV自管理配置*/
        ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL,(u8*)(&(g_nv_ctrl.nv_self_ctrl)),sizeof(NV_SELF_CTRL_STRU));
        if(ret)
        {
            g_nv_ctrl.nv_self_ctrl.ulResumeMode = NV_MODE_USER;
            nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_DRV_SELF_CTRL,ret);
        }
    }
    else
    {
        /*读取NV自管理配置*/
        ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL,(u8*)(&(g_nv_ctrl.nv_self_ctrl)),sizeof(NV_SELF_CTRL_STRU));
        if(ret)
        {
            g_nv_ctrl.nv_self_ctrl.ulResumeMode = NV_MODE_USER;
            nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_DRV_SELF_CTRL,ret);
        }

        /*重新加载最新数据*/
        ret = bsp_nvm_reload();
        if(ret)
        {
            nv_debug(NV_FUN_KERNEL_INIT,4,ret,0,0);
            goto out;
        }
    }
    /*初始化双核使用的链表*/
    nv_flushListInit();
    ret = bsp_ipc_sem_create(IPC_SEM_NV_CRC);
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,6,ret,0,0);
        goto out;
    }

    ret = bsp_nvm_buf_init();
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,10,ret,0,0);
        goto out;
    }

    /*置初始化状态为OK*/
    ddr_info->acore_init_state = NV_INIT_OK;
    nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, (u32)NV_GLOBAL_INFO_SIZE);

    /*保证各分区数据正常写入*/
    nv_file_flag_check();

    INIT_LIST_HEAD(&g_nv_ctrl.stList);
/*lint -save -e740*/
    ret = (u32)osl_task_init("drv_nv",15,1024,(OSL_TASK_FUNC)bsp_nvm_icc_task,NULL,(OSL_TASK_ID*)&g_nv_ctrl.task_id);
    if(ret)
    {
        nv_mntn_record("[%s]:nv task init err! ret :0x%x\n",__func__,ret);
        goto out;
    }
/*lint -restore +e740*/

    if((ret = nv_icc_chan_init(NV_RECV_FUNC_AC))\
        ||(ret = nv_icc_chan_init(NV_RECV_FUNC_AM))\
        )
    {
        nv_debug(NV_FUN_KERNEL_INIT,5,ret,0,0);
        goto out;
    }

    /*to do:nv id use macro define*/
    ret = bsp_nvm_read(NV_ID_MSP_FLASH_LESS_MID_THRED,(u8*)(&(g_nv_ctrl.mid_prio)),sizeof(u32));
    if(ret)
    {
        g_nv_ctrl.mid_prio = 20;
        nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_MSP_FLASH_LESS_MID_THRED,ret);
    }

    nv_mntn_record("Balong nv init ok!\n");
    return NV_OK;

out:
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    ddr_info->acore_init_state = NV_INIT_FAIL;
    nv_help(NV_FUN_KERNEL_INIT);
    show_ddr_info();
    return -1;
}

/*lint -save -e529*/
static void bsp_nvm_exit(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    /*关机写数据*/
    (void)bsp_nvm_flush();
    /*清除标志*/
    memset(ddr_info,0,sizeof(struct nv_global_ddr_info_stru));
}
/*lint -restore +e529*/


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
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_NV,"[0x%x]:len 0x%x,off 0x%x,file id %d\n",nvid,ref_info.nv_len,ref_info.nv_off,ref_info.file_id);

    tempdata = (u8*)nv_malloc((u32)(ref_info.nv_len) +1);
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

    for(i=0;i<ref_info.nv_len;i++)
    {
        if((i%32) == 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_NV, "\n");
        }
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_NV, "%02x ",(u8)(*(tempdata+i)));
    }
    nv_free(tempdata);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_NV,"\n\n");
    return 0;
}


u32 nvm_read_randex(u32 nvid,u32 modem_id)
{
	u32 ret;    u8* tempdata;    u32 i= 0;
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

	nv_printf("[0x%x]:len 0x%x,off 0x%x,file id %d\n",nvid,ref_info.nv_len,ref_info.nv_off,ref_info.file_id);
	nv_printf("[0x%x]:dsda 0x%x\n",nvid,ref_info.modem_num);

	tempdata = (u8*)nv_malloc((u32)(ref_info.nv_len) +1);
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

	for(i=0;i<ref_info.nv_len;i++)
	{
		if((i%32) == 0)
		{
			printf("\n");
		}
		printf("%02x ",(u8)(*(tempdata+i)));
	}

	printf("\n\n");
	nv_free(tempdata);

	return 0;

}
#if defined(FEATURE_NV_FLASH_ON)

/*lint -save -e19*/
module_init(bsp_nvm_kernel_init);
module_exit(bsp_nvm_exit);
/*lint -restore +e19*/
#elif defined(FEATURE_NV_EMMC_ON)

/*lint -save -e537*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/printk.h>
#include "mdrv_rfile_common.h"
//#include <drv_sync.h>
/*lint -restore +e537*/
/*lint -save -e537*/
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
/*lint -restore +e537*/
/*lint -save -e26*/
static ssize_t Modem_NvRead(struct file *file,char __user *buf, size_t len, loff_t *ppos)
{
    return len;
}
/*lint -restore +e26*/
static ssize_t Modem_NvWrite(struct file *file,const char __user *buf, size_t len, loff_t *ppos)
{
    signed int ret;
    ret = nv_modify_upgrade_flag(true);
    if(ret)
        return ret;
    nv_mntn_record("%s %s modify upgrade flag success !\n",__DATE__,__TIME__);
    return len;
}
static const struct file_operations g_ModemNv ={
    .owner    = THIS_MODULE,
    .read     = Modem_NvRead,
    .write    = Modem_NvWrite,
};
/*lint -save -e745*/
int modemNv_ProcInit(void)
{
    if(NULL == proc_create("ModemNv", 0660, NULL, &g_ModemNv))
    {
        return -1;
    }
    return 0;
}

/*lint -restore +e745*/
#include <linux/mtd/mtd.h>
void modem_nv_delay(void)
{
    struct mtd_info* mtd;
    int i;

    /*最长等待时长10s*/
    for(i=0;i<10;i++)
    {
        nv_printf("modem nv wait for mtd device %d s\n",i);
        mtd = get_mtd_device_nm(NV_BACK_SEC_NAME);
        if(IS_ERR(mtd)){
            nv_taskdelay(1000);
            nv_printf("get mtd device %s fail\n", NV_BACK_SEC_NAME);
            continue;
        }
        put_mtd_device(mtd);

        mtd = get_mtd_device_nm(NV_DLOAD_SEC_NAME);
        if(IS_ERR(mtd)){
            nv_taskdelay(1000);
            nv_printf("get mtd device %s fail\n", NV_DLOAD_SEC_NAME);
            continue;
        }
        put_mtd_device(mtd);

        mtd = get_mtd_device_nm(NV_SYS_SEC_NAME);
        if(IS_ERR(mtd)){
            nv_taskdelay(1000);
            nv_printf("get mtd device %s fail\n", NV_SYS_SEC_NAME);
            continue;
        }
        put_mtd_device(mtd);

        mtd = get_mtd_device_nm(NV_DEF_SEC_NAME);
        if(IS_ERR(mtd)){
            nv_taskdelay(1000);
            nv_printf("get mtd device %s fail\n", NV_DEF_SEC_NAME);
            continue;
        }
        put_mtd_device(mtd);

        return;
    }
}


static int  modem_nv_probe(struct platform_device *dev)
{
    int ret = -1;

    g_nv_ctrl.pmState = NV_WAKEUP_STATE;
    g_nv_ctrl.opState = NV_IDLE_STATE;

    ret = nv_emmc_area_name_init();
    if(ret)
    {
        return ret;
    }
    modem_nv_delay();

	/* coverity[Event check_return] *//* coverity[Event unchecked_value] */
    if(mdrv_file_access("/modem_log/modem_nv/",0))
        (void)mdrv_file_mkdir("/modem_log/modem_nv/");


    ret = bsp_nvm_kernel_init();

    ret |= modemNv_ProcInit();

    return ret;
}

#define NV_SHUTDOWN_STATE   NV_BOOT_INIT_OK
static void modem_nv_shutdown(struct platform_device *dev)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    printk("%s shutdown start %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n",__func__);

    /*read only*/
    ddr_info->acore_init_state = NV_SHUTDOWN_STATE;
    ddr_info->ccore_init_state = NV_SHUTDOWN_STATE;
    ddr_info->mcore_init_state = NV_SHUTDOWN_STATE;

}
#ifdef CONFIG_PM
static s32 modem_nv_suspend(struct device *dev)
{
    static int count = 0;
    if(g_nv_ctrl.opState == NV_OPS_STATE)
    {
        printk(KERN_ERR"%s Modem nv in doing !\n",__func__);
        return -1;
    }
    g_nv_ctrl.pmState = NV_SLEEP_STATE;
    printk(KERN_ERR"Modem nv enter suspend! %d times\n",++count);
    return 0;
}
static s32 modem_nv_resume(struct device *dev)
{
    static int count;
    g_nv_ctrl.pmState = NV_WAKEUP_STATE;
    if(NV_OPS_STATE== g_nv_ctrl.opState)
    {
        printk(KERN_ERR"%s need to enter task proc!\n",__func__);
        osl_sem_up(&g_nv_ctrl.task_sem);
    }
    printk(KERN_ERR"Modem nv enter resume! %d times\n",++count);
    return 0;
}
static const struct dev_pm_ops modem_nv_pm_ops ={
	.suspend = modem_nv_suspend,
    .resume  = modem_nv_resume,
};

#define MODEM_NV_PM_OPS (&modem_nv_pm_ops)
#else
#define MODEM_NV_PM_OPS  NULL
#endif

static struct platform_driver modem_nv_drv = {
    .shutdown   = modem_nv_shutdown,
    .driver     = {
        .name     = "modem_nv",
        .owner    = THIS_MODULE,
        .pm       = MODEM_NV_PM_OPS,
    },
};


static struct platform_device modem_nv_device = {
    .name = "modem_nv",
    .id = 0,
    .dev = {
    .init_name = "modem_nv",
    },
};
extern void dump_show_stack(void);

int  modem_nv_init(void)
{
    struct platform_device *dev = NULL;
    int ret;
    if(0 == g_nv_ctrl.initStatus)
    {
        g_nv_ctrl.initStatus = 1;
    }
    else
    {
        dump_show_stack();
    }

    ret = modem_nv_probe(dev);

    return ret;
}
/*仅用于初始化nv设备*/
int nv_init_dev(void)
{
    u32 ret = 0;
    ret = platform_device_register(&modem_nv_device);
    if(ret)
    {
        printk(KERN_ERR"platform_device_register modem_nv_device fail !\n");
        return -1;
    }

    ret = platform_driver_register(&modem_nv_drv);
    if(ret)
    {
        printk(KERN_ERR"platform_device_register modem_nv_drv fail !\n");
        platform_device_unregister(&modem_nv_device);
        return -1;
    }
    return NV_OK;
}
void  modem_nv_exit(void)
{
    bsp_nvm_exit();
    platform_device_unregister(&modem_nv_device);
    platform_driver_unregister(&modem_nv_drv);
}

device_initcall(nv_init_dev);
//module_exit(modem_nv_exit);

#endif

EXPORT_SYMBOL(bsp_nvm_backup);
EXPORT_SYMBOL(bsp_nvm_dcread);
EXPORT_SYMBOL(bsp_nvm_kernel_init);
EXPORT_SYMBOL(bsp_nvm_revert);
EXPORT_SYMBOL(bsp_nvm_update_default);
EXPORT_SYMBOL(bsp_nvm_revert_default);
EXPORT_SYMBOL(bsp_nvm_dcreadpart);
EXPORT_SYMBOL(bsp_nvm_get_len);
EXPORT_SYMBOL(bsp_nvm_dcwrite);
EXPORT_SYMBOL(bsp_nvm_flush);
EXPORT_SYMBOL(bsp_nvm_reload);
EXPORT_SYMBOL(nvm_read_rand);
EXPORT_SYMBOL(nvm_read_randex);
EXPORT_SYMBOL(show_ddr_info);
EXPORT_SYMBOL(bsp_nvm_dcread_direct);
EXPORT_SYMBOL(bsp_nvm_dcwrite_direct);
EXPORT_SYMBOL(bsp_nvm_auth_dcread);
EXPORT_SYMBOL(bsp_nvm_auth_dcwrite);
EXPORT_SYMBOL(bsp_nvm_dcwritepart);
EXPORT_SYMBOL(bsp_nvm_get_nvidlist);
EXPORT_SYMBOL(bsp_nvm_authgetlen);
EXPORT_SYMBOL(bsp_nvm_flushEx);
EXPORT_SYMBOL(bsp_nvm_xml_decode);

/*lint -restore*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



