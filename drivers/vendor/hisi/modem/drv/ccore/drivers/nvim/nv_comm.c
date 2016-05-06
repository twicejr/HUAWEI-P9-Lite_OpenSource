

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -save -e537*/
#include <securec.h>
#include <bsp_dump.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>
#include "nv_comm.h"
#include "osl_list.h"
#include <stdlib.h>
#include <string.h>
#include <osl_irq.h>
#include "osl_sem.h"
#include "RfNvId.h"
#include "nv_debug.h"
#include <bsp_reset.h>

/*lint -restore +e537*/

/*lint -save -e826 -e958 -e438*/
static const u32 nv_mid_droit[NV_MID_PRI_LEVEL_NUM] = {20,1,1,1,1,1,0};

struct nv_global_ctrl_info_stru  g_nv_ctrl;
struct nv_global_debug_stru      g_nv_debug[NV_FUN_MAX_ID];

u16 g_NvSysList[] = { NV_ID_DRV_IMEI,
                      NV_ID_DRV_NV_FACTORY_INFO_I,
                      NV_ID_DRV_NV_DRV_VERSION_REPLACE_I,
                      NV_ID_DRV_SEC_BOOT_ENABLE_FLAG,
                      en_NV_Item_XO_TEMP_SENSOR_TABLE,
                      en_NV_Item_PA_TEMP_SENSOR_TABLE,
                      NV_ID_DRV_SOCP_LOG_CFG};

/*nv debug func*/
void nv_debug(u32 type,u32 reseverd1,u32 reserved2,u32 reserved3,u32 reserved4)
{
    if(0 == reseverd1)
    {
        g_nv_debug[type].callnum++;
    }
    g_nv_debug[type].reseved1 = reseverd1;
    g_nv_debug[type].reseved2 = reserved2;
    g_nv_debug[type].reseved3 = reserved3;
    g_nv_debug[type].reseved4 = reserved4;
}

void nv_modify_print_sw(u32 arg)
{
    g_nv_ctrl.debug_sw = arg;
}

s32 nv_modify_pm_sw(s32 arg)
{
    g_nv_ctrl.pmSw = (bool)arg;

    return 0;
}

bool nv_isSysNv(u16 itemid)
{
    u32 i = 0;
    if(itemid >= NV_ID_SYS_MIN_ID && itemid <= NV_ID_SYS_MAX_ID)
        return (bool)true;

    for(i = 0;i<sizeof(g_NvSysList)/sizeof(g_NvSysList[0]);i++)
    {
        if(itemid == g_NvSysList[i])
            return (bool)true;
    }
    return (bool)false;

}
/*
 * get nv read right,check the nv init state or upgrade state to read nv,
 * A core may read nv data after kernel init ,C core read nv data must behine the phase of
 *       acore kernel init or acore init ok
 */
bool nv_read_right(u32 itemid)
{
    struct nv_global_ddr_info_stru* ddr_info= (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    /*[false alarm]:Value Never Read*/
    itemid = itemid;
    if((NV_KERNEL_INIT_DOING > ddr_info->ccore_init_state))
    {
        return (bool)false;
    }

    return (bool)true;
}

bool nv_write_right(u32 itemid)
{
    struct nv_global_ddr_info_stru* ddr_info= (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    /* [false alarm]:Value Never Read */
    itemid = itemid;
    if(   (NV_INIT_OK != ddr_info->ccore_init_state)
        ||(NV_INIT_OK != ddr_info->acore_init_state))
    {
        return (bool)false;
    }
    return (bool)true;
}


/*
 * search nv info by nv id
 * &pdata:  data start ddr
 * output: ref_info,file_info
 */
u32 nv_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info)
{
    u32 low;
    u32 high;
    u32 mid;
    u32 offset;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)pdata;

    high = ctrl_info->ref_count;
    low  = 1;

    nv_debug(NV_FUN_SEARCH_NV,0,itemid,high,0);

    while(low <= high)
    {
        mid = (low+high)/2;

        offset =NV_GLOBAL_CTRL_INFO_SIZE +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num + (mid -1)*NV_REF_LIST_ITEM_SIZE;
        if(memcpy_s((u8*)ref_info, sizeof(struct nv_ref_data_info_stru),(u8*)ctrl_info+offset,NV_REF_LIST_ITEM_SIZE))
        {
            nv_printf("memcpy_s error 111\n");
            return BSP_ERR_NV_MEMCPY_ERR;
        }

        if(itemid < ref_info->itemid)
        {
            high = mid -1;
        }
        else if(itemid > ref_info->itemid)
        {
            low = mid +1;
        }
        else
        {
            offset = NV_GLOBAL_CTRL_INFO_SIZE + NV_GLOBAL_FILE_ELEMENT_SIZE*(ref_info->file_id -1);
            if(memcpy_s((u8*)file_info,sizeof(struct nv_file_list_info_stru),(u8*)ctrl_info+offset,NV_GLOBAL_FILE_ELEMENT_SIZE))
            {
                nv_printf("memcpy_s error 111\n");
                return BSP_ERR_NV_MEMCPY_ERR;
            }

            return NV_OK;
        }
    }
    /*lint -save -e718 -e746 -e628*/
    nv_printf("\n[%s]:can not find 0x%x !\n",__FUNCTION__,itemid);
    /*lint -restore*/
    return BSP_ERR_NV_NO_THIS_ID;
}


/*
 * copy user buff to global ddr,used to write nv data to ddr
 * &file_id :file id
 * &offset:  offset of global file ddr
 */
u32 nv_write_to_mem(u8* pdata,u32 size,u32 file_id,u32 offset)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    u32 ret = 0;
    
    if(offset > ddr_info->file_info[file_id-1].size)
    {
        show_ddr_info();
        nv_printf("[%s]:offset 0x%x\n",__FUNCTION__,offset);
        return BSP_ERR_NV_FILE_ERROR;
    }

    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);

    nv_wr_process_set(pdata, size, file_id, offset);

    if(memcpy_s((u8*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+ddr_info->file_info[file_id-1].offset + offset), size ,pdata,size))
    {
        nv_wr_process_clear();
        nv_ipc_sem_give(IPC_SEM_NV_CRC);
        nv_printf("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }

    ret = nv_make_nv_data_crc(ddr_info->file_info[file_id-1].offset+ offset, size);
    if(ret)
    {
        nv_wr_process_clear();
        nv_ipc_sem_give(IPC_SEM_NV_CRC);
        nv_printf("ret = 0x%x\n",ret);
        return BSP_ERR_NV_CRC_CODE_ERR;
    }

    nv_flush_cache((u8*)(NV_GLOBAL_CTRL_INFO_ADDR+ddr_info->file_info[file_id-1].offset + offset),size);

    nv_wr_process_clear();
    
    nv_ipc_sem_give(IPC_SEM_NV_CRC);

    return NV_OK;
}


/*
 * copy global ddr to user buff,used to read nv data from ddr
 * &file_id : file id
 * &offset:  offset of the file
 */
u32 nv_read_from_mem(u8* pdata,u32 size,u32 file_id,u32 offset)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    if(offset > ddr_info->file_info[file_id-1].size)
    {
        show_ddr_info();
        nv_printf("[%s]:offset 0x%x\n",__FUNCTION__,offset);
        return BSP_ERR_NV_FILE_ERROR;
    }
    /*lint -save -e124*/
    if(memcpy_s(pdata,size,(u8*)(NV_GLOBAL_CTRL_INFO_ADDR +ddr_info->file_info[file_id-1].offset + offset),size))
    {
        nv_printf("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }
    /*lint -restore*/
    return NV_OK;
}


/*
 *  nv read data from global ddr of icc through the chanel id
 */
u32 nv_icc_read(u32 chanid, u32 len)
{
    struct nv_icc_stru icc_cnf = {0};
    u32 ret = NV_ERROR;

    if(memset_s(g_nv_ctrl.nv_icc_buf, NV_ICC_BUF_LEN, 0, NV_ICC_BUF_LEN))
    {
        nv_printf("memset_s error 222\n");
        return BSP_ERR_NV_MEMSET_ERR;
    }
    ret = (u32)bsp_icc_read(chanid,g_nv_ctrl.nv_icc_buf,len);

    if(len != ret)
    {
        /*lint -save -e515*/
        nv_printf("[%s]:ret 0x%x,len 0x%x\n",__FUNCTION__,ret,len);
        /*lint -restore*/
        return BSP_ERR_NV_ICC_CHAN_ERR;
    }
    if(memcpy_s(&icc_cnf,sizeof(struct nv_icc_stru),g_nv_ctrl.nv_icc_buf,sizeof(icc_cnf)))
    {
        nv_printf("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }
    nv_pm_trace(icc_cnf);
    nv_debug_record(NV_DEBUG_READ_ICC|((struct nv_icc_stru *)g_nv_ctrl.nv_icc_buf)->msg_type<<16);
    return NV_OK;
}

/*
 *  ccore callback of icc msg.only accept cnf message
 */
s32 nv_icc_msg_proc(u32 chanid ,u32 len,void* pdata)
{
    u32 ret = NV_ERROR;

    pdata = pdata;
    ret = nv_icc_read(chanid,len);
    if(ret)
    {
        osl_sem_up(&g_nv_ctrl.cc_sem);
        /*lint -save -e515*/
        nv_printf("[%s] :%d 0x%x\n",__FUNCTION__,__LINE__,ret);
        /*lint -restore*/
        return (s32)ret;
    }
    osl_sem_up(&g_nv_ctrl.cc_sem);
    return NV_OK;
}

/*
 *  nv use this inter to send data through the icc channel
 */
u32 nv_icc_send(u8* pdata,u32 len)
{
    s32  ret;
    u32 chanid = 0;
    u32 i = 0;
    chanid = ICC_CHN_NV << 16 | NV_RECV_FUNC_AC;

    /*lint -save -e578 -e530 -e515 -e516*/
    nv_debug_trace(pdata, len);
    /*lint -restore*/

    for(i = 0;i<NV_ICC_SEND_COUNT;i++)
    {
        ret = bsp_icc_send(ICC_CPU_APP,chanid,pdata,len);
        /*lint -save -e650 -e737*/
        if(ICC_INVALID_NO_FIFO_SPACE == (u32)ret)/*消息队列满,则50ms之后重新发送*/
        /*lint -restore*/
        {
            /*lint -save -e534*/
            nv_taskdelay(5);
            /*lint -restore*/
            continue;
        }
        else if((u32)ret != len)
        {
            /*lint -save -e515 -e516*/
            nv_printf("[%s]:ret :0x%x,len 0x%x\n",__FUNCTION__,ret,len);
            /*lint -restore*/
            return BSP_ERR_NV_ICC_CHAN_ERR;
        }
        else
        {
            nv_debug_record(NV_DEBUG_SEND_ICC|(((struct nv_icc_stru*)pdata)->msg_type<<16));
            return NV_OK;
        }
    }
    system_error(DRV_ERRNO_NV_ICC_FIFO_FULL,ICC_CPU_APP,chanid,(char*)pdata,len);
    return NV_ERROR;
}

/*
 *  init icc channel used by nv module
 */
u32 nv_icc_chan_init(void)
{
    u32 chanid = 0;
    chanid = ICC_CHN_NV << 16 | NV_RECV_FUNC_AC;

     /*reg icc debug proc*/
    (void)bsp_icc_debug_register(chanid,nv_modify_pm_sw,(s32)true);

    /* [false alarm]:Value Never Read*/
    return (u32)bsp_icc_event_register(chanid,nv_icc_msg_proc,NULL,NULL,NULL);
}
u32 nv_request_flush(void)
{
    struct nv_icc_stru icc_req = {0};
    u32 ret = 0;

    icc_req.msg_type = NV_ICC_REQ_CCORE_DELAY_FLUSH;
    icc_req.data_off = 0;
    icc_req.slice = bsp_get_slice_value();

    ret = nv_icc_send((u8 *)&icc_req, sizeof(icc_req));
    if(ret)
    {
        nv_printf("send icc msg fail,icc type: delay flush\n");
    }

    return ret;
}
/*
 *  write data to file/flash/rfile,base the nv priority,inner packing write to ddr
 *  &pdata:    user buff
 *  &offset:   offset of nv in ddr
 *  &len :     data length
 */
u32 nv_write_to_file(struct nv_ref_data_info_stru* ref_info)
{
    u32 ret = NV_OK;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    /*[false alarm]:Value Never Read*/
    u32 temp_prio = 0;
    unsigned long nvflag = 0;

    ret = nv_pushNvFlushList(ref_info);
    if(ret)
    {
        nv_printf("nv_pushNvFlushList fail, ret = 0x%x\n", ret);
        return ret;
    }

    if(NV_HIGH_PRIORITY == ref_info->priority)
    {
        nv_debug_record(NV_DEBUG_FLUSH_START);
        ret = nv_flushList();
        if(ret)
        {
            nv_printf("nv_flushList fail ret = 0x%x\n", ret);
            return ret;
        }
        nv_debug_record(NV_DEBUG_FLUSH_END);
    }
    else
    {
        nv_spin_lock(nvflag, IPC_SEM_NV);
        ddr_info->priority +=\
            nv_mid_droit[ref_info->priority - NV_MID_PRIORITY1];
        temp_prio = ddr_info->priority;
        nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, (u32)NV_GLOBAL_INFO_SIZE);
        nv_spin_unlock(nvflag, IPC_SEM_NV);

        /*[false alarm]:Value Never Read*//*flush list size subtract five to reserve some space */
        if((temp_prio >= g_nv_ctrl.mid_prio)||(ddr_info->flush_info.count >= NV_FLUSH_LIST_OVER_SIZE))/*优先级已经足够,或者数量已经足够*/
        {
            nv_debug_record(NV_DEBUG_REQ_FLUSH_START);
            ret = nv_request_flush();
            if(ret)
            {
                nv_printf("req flush to flush fail\n");
                return ret;
            }
            nv_debug_record(NV_DEBUG_REQ_FLUSH_END);
        }
    }

    if(true == nv_isSysNv(ref_info->itemid))
    {
        /* coverity[sleep] */
        ret = bsp_nvm_flushSys(ref_info->itemid);
    }
    return ret;
}


/* 计算字符串的CRC */
u32 nv_cal_crc32(u8 *Packet, u32 dwLength)
{
    static u32 CRC32_TABLE[256] = {
        0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
        0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
        0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
        0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
        0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
        0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
        0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
        0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1, 0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
        0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
        0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
        0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
        0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
        0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
        0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
        0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
        0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
        0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
        0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
        0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
        0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
        0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
        0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
        0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7, 0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
        0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
        0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
        0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
        0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
        0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
        0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
        0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
        0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
        0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4,
    };

    u32 CRC32 = 0;
    u32 i     = 0;


    for(i=0; i<dwLength; i++)
    {
        CRC32 = ((CRC32<<8)|Packet[i]) ^ (CRC32_TABLE[(CRC32>>24)&0xFF]); /* [false alarm]:fortify  */
    }

    for(i=0; i<4; i++)
    {
        CRC32 = ((CRC32<<8)|0x00) ^ (CRC32_TABLE[(CRC32>>24)&0xFF]); /* [false alarm]:fortify  */
    }

    return CRC32;
}
/*****************************************************************************
 函 数 名  : nv_make_nv_data_crc
 功能描述  : 对NV写入的NV以4K为单位生成CRC校验码,并写入内存对应位置
 输入参数  : offset:写入偏移,相对于ctrl文件头
             datalen:计算CRC数据的长度
 输出参数  : NV_OK:成功
 返 回 值  : 无
*****************************************************************************/
u32 nv_make_nv_data_crc(u32 offset, u32 datalen)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    u32 ret = 0;
    u8 *pCrcData = 0;
    u32 FileCrcOffset = 0;
    u32 index_num = 0;
    u32 crcSize = 0;
    u32 crcCount = 0;
    u32 skipCrcCount = 0;
	/*lint -save -e124*/
    u32 *p_crc_code = NV_DDR_CRC_CODE_OFFSET;
	/*lint -restore*/

    if(!NV_DATA_CRC_CHECK_YES)/*是否需要进行CRC校验*/
    {
        return NV_OK;
    }
    if((offset + datalen) > ddr_info->file_len)
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }
    /*以4K为单位，生成CRC的总量*/
    crcCount = NV_CRC_CODE_COUNT((offset + datalen- ctrl_info->ctrl_size)) - (offset- ctrl_info->ctrl_size)/NV_CRC32_CHECK_SIZE;
    /*需要跳过的CRC校验码的总数量*/
    skipCrcCount = (offset - ctrl_info->ctrl_size)/NV_CRC32_CHECK_SIZE;
    /*第一个CRC的4K数据的偏移*/
    FileCrcOffset = offset - (offset - ctrl_info->ctrl_size)%NV_CRC32_CHECK_SIZE;
    /*以4K为单位对数据进行CRC校验*/
    for(index_num = 0; index_num < crcCount; index_num++)
    {
        crcSize = (ddr_info->file_len - FileCrcOffset > NV_CRC32_CHECK_SIZE)?NV_CRC32_CHECK_SIZE:(ddr_info->file_len - FileCrcOffset);
        pCrcData = (u8 *)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR + FileCrcOffset);
        ret = nv_cal_crc32(pCrcData, crcSize);
        (void)memcpy_s((void *)((unsigned long)p_crc_code + (index_num + skipCrcCount)*sizeof(u32)), sizeof(u32),(void *)&ret, sizeof(u32));
        FileCrcOffset += crcSize;
    }
    nv_flush_cache((u8*)(NV_GLOBAL_CTRL_INFO_ADDR + offset), crcCount*sizeof(u32));
    return NV_OK;
}

/*****************************************************************************
 函 数 名  : nv_check_part_ddr_crc
 功能描述  : 对一定长度的NV数据进行CRC校验
 输入参数  : pData:数据指针
             old_crc:原来的CRC校验码
             size:需要校验的大小
 输出参数  : 无
 返 回 值  : BSP_ERR_NV_CRC_CODE_ERR 校验错误
             NV_OK:校验成功
*****************************************************************************/
u32 nv_check_part_ddr_crc(u8 *pData, u32 old_crc, u32 size)
{
    u32 new_crc = 0;
    if((NULL == pData)||(0 == size))
    {
        nv_printf("pData is NULL\n");
        return BSP_ERR_NV_INVALID_PARAM;
    }

    new_crc = nv_cal_crc32(pData, size);
    if(old_crc == new_crc)
    {
        return NV_OK;
    }
    else
    {
        nv_printf("pData = 0x%x old_crc = 0x%x \n", pData, old_crc);
        return BSP_ERR_NV_CRC_CODE_ERR;
    }
}
/*****************************************************************************
 函 数 名  : nv_check_nv_data_crc
 功能描述  : 对偏移为offset，长度为datalen的数据按照4k为单位，进行CRC校验
 输入参数  : offset:要写入的数据的偏移，相对于控制文件头
             datalen:待校验的数据长度
 输出参数  : NV_OK:校验通过
 返 回 值  : 无
*****************************************************************************/
u32 nv_check_nv_data_crc(u32 offset, u32 datalen)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    u32 ret = 0;
    u8 *pCrcData = 0;
    u32 FileCrcOffset = 0;
    u32 index_num = 0;
    u32 old_crc = 0;
    u32 crc_size = 0;
    u32 crcCount = 0;
    u32 skipCrcCount = 0;
	/*lint -save -e124*/
    u32 *p_crc_code = NV_DDR_CRC_CODE_OFFSET;
	/*lint -restore*/
    if(!NV_DATA_CRC_CHECK_YES)/*是否需要进行CRC校验*/
    {
        return NV_OK;
    }
    if((offset + datalen) > ddr_info->file_len)
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }
    /*以4K为单位，生成CRC的总量*/
    crcCount = NV_CRC_CODE_COUNT((offset + datalen- ctrl_info->ctrl_size)) - (offset- ctrl_info->ctrl_size)/NV_CRC32_CHECK_SIZE;
    /*需要跳过的CRC校验码的总数量*/
    skipCrcCount = (offset - ctrl_info->ctrl_size)/NV_CRC32_CHECK_SIZE;
    /*第一个CRC的4K数据的偏移*/
    FileCrcOffset = offset - (offset - ctrl_info->ctrl_size)%NV_CRC32_CHECK_SIZE;
    /*以4K为单位对数据进行CRC校验*/
    for(index_num = 0;index_num < crcCount; index_num ++)
    {
        crc_size = (ddr_info->file_len - FileCrcOffset > NV_CRC32_CHECK_SIZE)?NV_CRC32_CHECK_SIZE:(ddr_info->file_len - FileCrcOffset);
        (void)memcpy_s((void *)&old_crc, sizeof(u32),(void *)((unsigned long)p_crc_code + (index_num + skipCrcCount)*sizeof(u32)), sizeof(u32));
        pCrcData = (u8 *)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR + FileCrcOffset);
        ret = nv_check_part_ddr_crc(pCrcData, old_crc, crc_size);
        if(ret)
        {
            nv_printf("nv_check_part_ddr_crc error 2, index_num = 0x%x ret = 0x%x \n", index_num, ret);
            return ret;
        }
        FileCrcOffset += crc_size;
    }
    return NV_OK;
}
/*****************************************************************************
 函 数 名  : nv_resume_ddr_from_img
 功能描述  : 从工作分区/备份分区/出厂分区恢复NV数据,具体操作是通过发送消息给A核进行的
 输入参数  : path 文件路径
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 nv_resume_ddr_from_img(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_icc_stru icc_req = {0};
    struct nv_icc_stru icc_cnf = {0};
    unsigned long nvflag = 0;
    u32 ret = 0;

    nvflag = nvflag;/* [false alarm]:屏蔽Fortify */

    nv_spin_lock(nvflag, IPC_SEM_NV);
    ddr_info->ccore_init_state = NV_KERNEL_INIT_DOING;
    nv_spin_unlock(nvflag, IPC_SEM_NV);

    icc_req.msg_type = NV_ICC_RESUME;
    icc_req.data_len = 0;
    icc_req.data_off = 0;
    icc_req.ret      = 0;   /*use to test ,no meaning*/
    icc_req.itemid   = 0;
    icc_req.slice    = bsp_get_slice_value();

    ret = nv_icc_send((u8*)&icc_req, sizeof(icc_req));
    if(ret)
    {
        return BSP_ERR_NV_ICC_CHAN_ERR;
    }
    /*lint -save -e534*/
    if(osl_sem_downtimeout(&g_nv_ctrl.cc_sem,NV_MAX_WAIT_TICK))
    {
        nv_printf("down time out\n");
    }
    /*lint -restore +e534*/

    if(memcpy_s(&icc_cnf, sizeof(icc_cnf),g_nv_ctrl.nv_icc_buf,sizeof(icc_cnf)))
    {
        nv_printf("memcpy_s error 111\n");
        return BSP_ERR_NV_MEMCPY_ERR;
    }

    if(icc_cnf.msg_type != NV_ICC_CNF)
    {
        /* yangzhi RTOSck */
        nv_error_printf("\n[%s],line:%d\n",__FUNCTION__,__LINE__);
        return BSP_ERR_NV_INVALID_PARAM;
    }
    if(icc_cnf.ret)
    {
        nv_error_printf("\n resume error [%s],line:%d\n",__FUNCTION__,__LINE__);
    }
    else
    {
        nv_spin_lock(nvflag, IPC_SEM_NV);
        ddr_info->ccore_init_state = NV_INIT_OK;
        nv_spin_unlock(nvflag, IPC_SEM_NV);
    }
    return icc_cnf.ret;
}
/*****************************************************************************
 函 数 名  : nv_pushNvFlushList
 功能描述  : 将NV信息加入到NV列表中
 输入参数  : ref_info:NV信息
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32  nv_pushNvFlushList(struct nv_ref_data_info_stru* ref_info)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    unsigned long nvflag = 0;
    u32 index_num = 0;
    u32 i = 0;
    u32 ret = 0;

    if((nv_pop_list_to_glb_list())&&(ref_info->priority > 0))
    {
        ddr_info->priority += nv_mid_droit[0];
    }

    osl_sem_down(&g_nv_ctrl.nv_list_sem);
    nv_spin_lock(nvflag, IPC_SEM_NV);

    for(i = 0; i < ddr_info->flush_info.count; i++)
    {
        if(ddr_info->flush_info.list[i].itemid == ref_info->itemid)
        {
            break;
        }
    }

    ret = nv_check_local_list(ref_info->itemid);

    if(ret && (i >= ddr_info->flush_info.count))
    {
        if(ddr_info->flush_info.count >= NV_FLUSH_LIST_SIZE)
        {
            ret = nv_push_to_local_list(ref_info);
            if(ret)
            {
                nv_spin_unlock(nvflag, IPC_SEM_NV);
                osl_sem_up(&g_nv_ctrl.nv_list_sem);
                return ret;
            }
        }
        else
        {
            index_num = ddr_info->flush_info.count;
            /* coverity[overrun-local] */
            ddr_info->flush_info.list[index_num].itemid = ref_info->itemid;
            ddr_info->flush_info.list[index_num].nv_len= ref_info->nv_len;
            ddr_info->flush_info.list[index_num].nv_off= ddr_info->file_info[ref_info->file_id-1].offset + ref_info->nv_off;
            ddr_info->flush_info.count++;
            nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, (u32)NV_GLOBAL_INFO_SIZE);
        }
    }

    nv_spin_unlock(nvflag, IPC_SEM_NV);
    osl_sem_up(&g_nv_ctrl.nv_list_sem);

    return NV_OK;
}

/*****************************************************************************
 函 数 名  : nv_flushList
 功能描述  : 将所有编辑过的NV写入到文件系统中(发送消息到A核)
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 nv_flushList(void)
{
    u32 ret = NV_ERROR;
    struct nv_icc_stru icc_req = {0};
    struct nv_icc_stru icc_cnf = {0};
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_debug(NV_API_FLUSH_LIST,0,0,0,0);

    if(NV_INIT_OK != ddr_info->ccore_init_state)
    {
        nv_debug(NV_API_FLUSH_LIST,1,ddr_info->ccore_init_state,0,0);
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }
    do{
        icc_req.msg_type = NV_ICC_REQ_INSTANT_FLUSH;
        icc_req.data_len = 0;
        icc_req.data_off = 0;
        icc_req.ret      = 93;   /*use to test ,no meaning*/
        icc_req.itemid   = 0;
        icc_req.slice    = bsp_get_slice_value();

        ret = nv_icc_send((u8*)&icc_req,sizeof(icc_req));
        if(ret)
        {
            nv_debug(NV_API_FLUSH,2,0,ret,0);
            nv_error_printf("\n[%s],line:%d\n",__FUNCTION__,__LINE__);
            nv_help(NV_API_FLUSH_LIST);
            return ret;
        }
        /*lint -save -e534*/
        if(osl_sem_downtimeout(&g_nv_ctrl.cc_sem,NV_MAX_WAIT_TICK))
        {
            nv_printf("down time out\n");
        }
        /*lint -restore +e534*/

        if(memcpy_s(&icc_cnf,sizeof(icc_cnf),g_nv_ctrl.nv_icc_buf,sizeof(icc_cnf)))
        {
            nv_printf("memcpy_s error 111\n");
            return BSP_ERR_NV_MEMCPY_ERR;
        }

        if(icc_cnf.msg_type != NV_ICC_CNF)
        {
            nv_debug(NV_API_FLUSH_LIST,3,0,0,icc_cnf.msg_type);
            nv_error_printf("\n[%s],line:%d\n",__FUNCTION__,__LINE__);
            nv_help(NV_API_FLUSH_LIST);
            return BSP_ERR_NV_INVALID_PARAM;
        }
        if(icc_cnf.ret)
        {
            nv_debug(NV_API_FLUSH_LIST,5,0,0,icc_cnf.msg_type);
            nv_error_printf("\n[%s],line:%d\n",__FUNCTION__,__LINE__);
            nv_help(NV_API_FLUSH_LIST);
            return icc_cnf.ret;
        }
    }while(nv_pop_list_to_glb_list());

    return NV_OK;
}
/*****************************************************************************
 函 数 名  : nv_check_local_list
 功能描述  : 查看指定的nvid在local list中是否存在
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 nv_check_local_list(u32 itemid)
{
    struct list_head * me = NULL;
    struct nv_flush_list_node_stru * cur = NULL;

    list_for_each(me, &g_nv_ctrl.nv_list)
    {
        cur = list_entry(me, struct nv_flush_list_node_stru, stList);/*存在相同的nv id*/
        if(cur->itemid == itemid)
        {
            return NV_OK;
        }
    }
    return NV_ERROR;
}

/*****************************************************************************
 函 数 名  : nv_push_to_local_list
 功能描述  : 将本核的nv写入信息写入到链表中
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 nv_push_to_local_list(struct nv_ref_data_info_stru* ref_info)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_flush_list_node_stru * cur = NULL;
    struct list_head * me = NULL;
    u32 count = 0;

    cur = NULL;
    /* [false alarm]:test using */
    cur = (struct nv_flush_list_node_stru*)nv_malloc(sizeof(struct nv_flush_list_node_stru));/* [false alarm]:test using */
    if(!cur)
    {
        nv_printf("malloc fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }
    cur->itemid = ref_info->itemid;
    cur->nv_len = ref_info->nv_len;
    cur->nv_off = ddr_info->file_info[ref_info->file_id-1].offset + ref_info->nv_off;


    list_add_tail(&cur->stList, &g_nv_ctrl.nv_list);

    list_for_each(me, &g_nv_ctrl.nv_list)
    {
        count++;
    }
    if(count > 2*NV_FLUSH_LIST_SIZE)
    {
        nv_printf("nv local list is full\n");
        system_error(DRV_ERRNO_NV_LIST_FULL, count, 0, NULL, 0);
    }

    return NV_OK;
}
/*****************************************************************************
 函 数 名  : nv_pop_list_to_glb_list
 功能描述  : 将本核的nv写入信息输出到共享内存中
 输入参数  : void
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
u32 nv_pop_list_to_glb_list(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct list_head * me = NULL;
    struct nv_flush_list_node_stru * cur = NULL;
    unsigned long nvflag = 0;
    u32 list_del_mark = 0;
    u32 push_count = 0;

    osl_sem_down(&g_nv_ctrl.nv_list_sem);
    nv_spin_lock(nvflag, IPC_SEM_NV);

    list_for_each(me, &g_nv_ctrl.nv_list)
    {
        if(list_del_mark)
        {
            /*lint -save -e826 -e613*/
            list_del(&(cur->stList));/* [false alarm] *//*lint !e613*/
            nv_free(cur);
            /*lint -restore +e826 +e613*/
            list_del_mark = 0;
        }
        if(ddr_info->flush_info.count < NV_FLUSH_LIST_OVER_SIZE)
        {
            cur = list_entry(me, struct nv_flush_list_node_stru, stList);/* [false alarm] */
            push_count++;
            list_del_mark = 1;
            if(ddr_info->flush_info.list[ddr_info->flush_info.count].itemid == cur->itemid)/* [false alarm] */
            {
                continue;
            }
            ddr_info->flush_info.list[ddr_info->flush_info.count].itemid = cur->itemid;/* [false alarm] */
            ddr_info->flush_info.list[ddr_info->flush_info.count].nv_len= cur->nv_len;/* [false alarm] */
            ddr_info->flush_info.list[ddr_info->flush_info.count].nv_off= cur->nv_off;/* [false alarm] */
            ddr_info->flush_info.count++;
        }
        else
        {
            break;
        }
    }

    nv_spin_unlock(nvflag, IPC_SEM_NV);

    if(list_del_mark)
    {

        /*lint -save -e794*/
        list_del(&(cur->stList));/* [false alarm] *//*lint !e794*/
        nv_free(cur);/* [false alarm] */
        /*lint -restore +e794*/
    }

    osl_sem_up(&g_nv_ctrl.nv_list_sem);
    return push_count;
}

void show_local_list(void)
{
    struct list_head * me = NULL;
    struct nv_flush_list_node_stru * cur = NULL;
    list_for_each(me, &g_nv_ctrl.nv_list)
    {
        cur = list_entry(me, struct nv_flush_list_node_stru, stList);
        nv_printf("nv id :0x%x\n", cur->itemid);
        nv_printf("nv len:0x%x\n", cur->nv_len);
        nv_printf("nv off:0x%x\n", cur->nv_off);
    }
    return;
}
void show_ddr_info(void)
{
    u32 i;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_file_list_info_stru* file_info = (struct nv_file_list_info_stru*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE);
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);

    nv_printf("global start ddr        :0x%x\n",NV_GLOBAL_INFO_ADDR);
    nv_printf("global ctrl file ddr    :0x%x\n",NV_GLOBAL_CTRL_INFO_ADDR);
    nv_printf("global file list ddr    :0x%x\n",file_info);
    nv_printf("global ref info  ddr    :0x%x\n",ref_info);
    nv_printf("*******************ddr global ctrl************************\n");
    nv_printf("acore init state: 0x%x\n",ddr_info->acore_init_state);
    nv_printf("ccore init state: 0x%x\n",ddr_info->ccore_init_state);
    nv_printf("file total len  : 0x%x\n",ddr_info->file_len);
    nv_printf("comm file num   : 0x%x\n",ddr_info->file_num);
    nv_printf("ddr read case  : 0x%x\n",ddr_info->ddr_read);
    nv_printf("mem file type   : 0x%x\n",ddr_info->mem_file_type);
    nv_printf("crc status      : 0x%x\n",ctrl_info->crc_mark.value);
    nv_printf("crc code addr   : 0x%x\n",ddr_info->p_crc_code);
    nv_printf("nv resume mode  : 0x%x\n", g_nv_ctrl.nv_self_ctrl.ulResumeMode);
    nv_printf("mid priority  : 0x%x\n",ddr_info->priority);


    if(ddr_info->ccore_init_state <= NV_INIT_FAIL)
	return;
    for(i = 0;i<ddr_info->file_num;i++)
    {
        nv_printf("##############################\n");
        nv_printf("** file id   0x%x\n",ddr_info->file_info[i].file_id);
        nv_printf("** file size 0x%x\n",ddr_info->file_info[i].size);
        nv_printf("** file off  0x%x\n",ddr_info->file_info[i].offset);
    }

    nv_printf("*******************global ctrl file***********************\n");
    nv_printf("ctrl file size    : 0x%x\n",ctrl_info->ctrl_size);
    nv_printf("file num          : 0x%x\n",ctrl_info->file_num);
    nv_printf("file list off     : 0x%x\n",ctrl_info->file_offset);
    nv_printf("file list size    : 0x%x\n",ctrl_info->file_size);
    nv_printf("ctrl file magic   : 0x%x\n",ctrl_info->magicnum);
    nv_printf("modem num         : 0x%x\n",ctrl_info->modem_num);
    nv_printf("nv count          : 0x%x\n",ctrl_info->ref_count);
    nv_printf("nv ref data off   : 0x%x\n",ctrl_info->ref_offset);
    nv_printf("nv ref data size  : 0x%x\n",ctrl_info->ref_size);
    nv_printf("*******************global file list***********************\n");
    for(i = 0;i<ctrl_info->file_num;i++)
    {
        nv_printf("file_info     : 0x%x\n",file_info);
        nv_printf("file id       : 0x%x\n",file_info->file_id);
        nv_printf("file name     : %s\n",file_info->file_name);
        nv_printf("file size     : 0x%x\n",file_info->file_size);
        file_info ++;
        nv_printf("\n");
    }
}


void show_ref_info(u32 arg1,u32 arg2)
{
    u32 i;
    u32 _max;
    u32 _min;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);

    _max = arg2 > ctrl_info->ref_count ? ctrl_info->ref_count:arg2;
    _min = arg1 > _max ? 0: arg1;

    _max = (arg2 ==0)?ctrl_info->ref_count: _max;

    ref_info = ref_info+_min;

    for(i = _min;i<_max;i++)
    {
        nv_printf("第%d项 :\n",i);
        nv_printf("nvid   :0x%-8x, file id : 0x%-8x\n",ref_info->itemid,ref_info->file_id);
        nv_printf("nvlen  :0x%-8x, nv_off  : 0x%-8x, nv_pri 0x%-8x\n",ref_info->nv_len,ref_info->nv_off,ref_info->priority);
        nv_printf("dsda   :0x%-8x\n",ref_info->modem_num);
        ref_info++;
    }
}

void nv_help(u32 type)
{
    u32 i = type;
    /* [false alarm]:Redundant Initialization*/
    if(type == 63/*'?'*/)
    {
        nv_printf("1   -------  read\n");/* [false alarm]:屏蔽Fortify */
        nv_printf("4   -------  auth read\n");
        nv_printf("5   -------  write\n");
        nv_printf("6   -------  auth write\n");
        nv_printf("8   -------  get len\n");
        nv_printf("9   -------  auth get len\n");
        nv_printf("10  -------  flush\n");
        nv_printf("12  -------  backup\n");
        nv_printf("15  -------  import\n");
        nv_printf("16  -------  export\n");
        nv_printf("19  -------  kernel init\n");
        nv_printf("20  -------  remian init\n");
        nv_printf("21  -------  nvm init\n");
        nv_printf("22  -------  xml decode\n");
        nv_printf("24  -------  revert\n");
        nv_printf("25  -------  update default\n");
        return;

    }
    if(type == NV_FUN_MAX_ID)
    {
        for(i = 0;i< NV_FUN_MAX_ID;i++)/* [false alarm]:屏蔽Fortify */
        {
            nv_printf("************fun id %d******************\n",i);
            nv_printf("call num             : 0x%x\n",g_nv_debug[i].callnum);
            nv_printf("out branch (reseved1): 0x%x\n",g_nv_debug[i].reseved1);
            nv_printf("reseved2             : 0x%x\n",g_nv_debug[i].reseved2);
            nv_printf("reseved3             : 0x%x\n",g_nv_debug[i].reseved3);
            nv_printf("reseved4             : 0x%x\n",g_nv_debug[i].reseved4);
            nv_printf("***************************************\n");
        }
        return ;
    }

    i = type;
    nv_printf("************fun id %d******************\n",i);
    nv_printf("call num             : 0x%x\n",g_nv_debug[i].callnum);
    nv_printf("out branch (reseved1): 0x%x\n",g_nv_debug[i].reseved1);
    nv_printf("reseved2             : 0x%x\n",g_nv_debug[i].reseved2);
    nv_printf("reseved3             : 0x%x\n",g_nv_debug[i].reseved3);
    nv_printf("reseved4             : 0x%x\n",g_nv_debug[i].reseved4);
    nv_printf("***************************************\n");
}
 /*lint -restore*/

u32 nv_show_ref_info(u16 itemid)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    struct nv_ref_data_info_stru ref_info = {};
    struct nv_file_list_info_stru file_info = {};
    u32 nv_phy_addr = 0;
    void* nv_virt_addr = 0;
    u32 ret = 0;

    ret = nv_search_byid((u32)itemid, (u8*)NV_GLOBAL_CTRL_INFO_ADDR, &ref_info, &file_info);
    if(ret)
    {
        return NV_ERROR;
    }
    nv_printf("itemid = 0x%x\n", ref_info.itemid);
    nv_printf("nv_len = 0x%x\n", ref_info.nv_len);
    nv_printf("nv_off = 0x%x\n", ref_info.nv_off);
    nv_printf("file_id = 0x%x\n", ref_info.file_id);
    nv_printf("priority = 0x%x\n", ref_info.priority);
    nv_printf("modem_num = 0x%x\n", ref_info.modem_num);

    nv_printf("file_id = 0x%x\n", file_info.file_id);
    nv_printf("file_name = %s\n", file_info.file_name);
    nv_printf("file_size = 0x%x\n", file_info.file_size);

    nv_virt_addr = (void *)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR + ddr_info->file_info[ref_info.file_id - 1].offset + ref_info.nv_off);

    nv_phy_addr = (u32)(unsigned long)SHD_DDR_V2P(nv_virt_addr);

    nv_printf("nv_virt_addr = 0x%x\n", nv_virt_addr);
    nv_printf("nv_phy_addr = 0x%x\n", nv_phy_addr);

    return NV_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




