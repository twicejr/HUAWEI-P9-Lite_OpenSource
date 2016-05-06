
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#include <nandc_balong.h>
#include "nv_boot.h"
#include "nv_file.h"


struct nv_flash_file_header_stru g_boot_nv_file[NV_FILE_BUTT] = {
                                  {NULL,NV_FILE_DLOAD,           0,0,0,0,IMAGE_NVDLD,    NV_DLOAD_PATH,      NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_BACKUP,          0,0,0,0,IMAGE_NVBACKLTE,NV_BACK_PATH,       NV_BACK_SEC_NAME},
                                  {NULL,NV_FILE_XNV_CARD_1,      0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD1_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_CARD_2,      0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD2_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_CARD_3,      0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD3_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_CUST_CARD_1,     0,0,0,0,IMAGE_NVDLD,    NV_CUST_CARD1_PATH, NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_CUST_CARD_2,     0,0,0,0,IMAGE_NVDLD,    NV_CUST_CARD2_PATH, NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_CUST_CARD_3,     0,0,0,0,IMAGE_NVDLD,    NV_CUST_CARD3_PATH, NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_SYS_NV,          0,0,0,0,IMAGE_NVIMG,    NV_FILE_SYS_NV_PATH,NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_DEFAULT,         0,0,0,0,IMAGE_NVFACTORY,NV_DEFAULT_PATH,    NV_DEF_SEC_NAME},
                                  {NULL,NV_FILE_XNV_MAP_CARD_1,  0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD1_MAP_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_MAP_CARD_2,  0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD2_MAP_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_MAP_CARD_3,  0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD3_MAP_PATH,  NV_DLOAD_SEC_NAME},
                                          };

struct file_func_table_stru g_file_func_table =
{
    .file_read = (bsp_file_read)bsp_nand_read,
    .file_is_bad = (bsp_file_isbad)bsp_nand_isbad,
    .file_get_info = (bsp_file_get_info)bsp_get_nand_info,
    .file_read_flag = (bsp_file_read_flag_nv)bsp_nand_read_flag_nv,
};
struct nv_sec_file_block_info g_sec_info;


u32 nv_get_nand_info(const s8* name,struct nv_nand_info_stru* nand_info)
{
    struct ST_PART_TBL * ptable = find_partition_by_name((char *)name);
    struct nand_spec spec;
    u32 ret = 0;

    if(NULL == ptable)
    {
        printf("get ptable fail, area name: %s\n", name);
        return NV_ERROR;
    }

    ret = bsp_get_nand_info(&spec);
    if(ret)
    {
        printf("get nand info error, ret = 0x%x\n", ret);
        return NV_ERROR;
    }

    nand_info->page_size  = (u32)spec.pagesize;
    nand_info->block_size = (u32)spec.blocksize;
    nand_info->total_size = (u32)ptable->capacity;

    return NV_OK;
}

/*
 * count off in this sec,bewteen sec head to off in this sec
 * count good block
 */
u32 nv_sec_off_count(const struct nv_flash_file_header_stru* ffp,u32 vir_off,u32* phy_off)
{
    u32 block_size = 0;
    struct nand_spec spec;
    u32 block_count;
    u32 ret = 0;

    ret = bsp_get_nand_info(&spec);
    if(ret)
    {
        printf("get nand info error, ret = 0x%x\n", ret);
        return NV_ERROR;
    }
    block_size = (u32)spec.blocksize;

    block_count = vir_off/block_size;/*vir off属于第几个好块*/
    *phy_off = vir_off % block_size;

    switch(ffp->flash_type)
    {
        case NV_FILE_DLOAD:
        case NV_FILE_XNV_CARD_1:
        case NV_FILE_CUST_CARD_1:
        case NV_FILE_XNV_CARD_2:
        case NV_FILE_CUST_CARD_2:
        case NV_FILE_XNV_CARD_3:
        case NV_FILE_CUST_CARD_3:
        case NV_FILE_XNV_MAP_CARD_1:
        case NV_FILE_XNV_MAP_CARD_2:
        case NV_FILE_XNV_MAP_CARD_3:
            *phy_off += g_sec_info.nv_dload[block_count];
            break;
        case NV_FILE_SYS_NV:
            *phy_off += g_sec_info.sys_nv[block_count];
            break;
        case NV_FILE_BACKUP:
            *phy_off += g_sec_info.nv_bak[block_count];
            break;
        case NV_FILE_DEFAULT:
            *phy_off += g_sec_info.nv_default[block_count];
            break;
        default:
            return BSP_ERR_NV_INVALID_PARAM;
    }
    return NV_OK;
}


u32 nv_count_file_sec_info(const s8* name,u32 len,u32* file_sec)
{
    u32 ret = NV_ERROR;
    u32 block_size;
    u32 block_count;
    u32 total_count;
    u32 i = 0;
    u32 offset = 0;
    struct nv_nand_info_stru nand_info;

    ret = nv_get_nand_info(name,&nand_info);
    if(ret)
    {
        printf("[%s]  ret : 0x%x\n",__func__,ret);
        return NV_ERROR;
    }
    block_size  = nand_info.block_size;
    total_count = nand_info.total_size/block_size;
    block_count = len/block_size + ((len%block_size == 0)?0:1);

    if((len > nand_info.total_size)||(block_count > total_count))
    {
        printf("[%s]: name %s file len 0x%x,sec size 0x%x\n",__func__,name,len,nand_info.total_size);
        return NV_ERROR;
    }

    while(i < block_count)
    {
        ret = (u32)bsp_nand_isbad((char*)name,offset);
        if(NV_BAD_SECTION == ret)
        {
            offset += block_size;
            continue;
        }
        file_sec[i] = offset;
        i++;
        offset += block_size;
        if(offset > nand_info.total_size)
        {
            printf("[%s]:name %s,offset 0x%x,sec size 0x%x\n",__func__,name,offset,nand_info.total_size);
            return BSP_ERR_NV_NAND_ALL_BAD;
        }
    }
    return NV_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

