

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e537*/
#include "nv_comm.h"
/*lint -restore +e537*/

/*lint -save -e530 -e438*/
static const u32 nv_mid_droit[NV_MID_PRI_LEVEL_NUM] = {1,1,1,1,1,1};

struct nv_global_ctrl_info_stru  g_nv_ctrl;


/*
 * get nv read right,check the nv init state or upgrade state to read nv,
 * A core may read nv data after kernel init ,C core read nv data must behine the phase of
 *       acore kernel init or acore init ok
 */
bool nv_read_right(u32 itemid)
{
    struct nv_global_ddr_info_stru* ddr_info= (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    if(   (NV_BOOT_INIT_OK > ddr_info->mcore_init_state)
        ||(NV_KERNEL_INIT_DOING == ddr_info->acore_init_state))
    {
        return false;
    }
    return true;
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

    while(low <= high)
    {
        mid = (low+high)/2;

        offset =NV_GLOBAL_CTRL_INFO_SIZE +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num + (mid -1)*NV_REF_LIST_ITEM_SIZE;
        memcpy((u8*)ref_info,(u8*)ctrl_info+offset,NV_REF_LIST_ITEM_SIZE);

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
            memcpy((u8*)file_info,(u8*)ctrl_info+offset,NV_GLOBAL_FILE_ELEMENT_SIZE);
            return NV_OK;
        }
    }
    return BSP_ERR_NV_NO_THIS_ID;

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
        return BSP_ERR_NV_FILE_ERROR;
    }

    memcpy(pdata,(u8*)(NV_GLOBAL_CTRL_INFO_ADDR +ddr_info->file_info[file_id-1].offset + offset),size);

    return NV_OK;
}

/*lint -restore*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




