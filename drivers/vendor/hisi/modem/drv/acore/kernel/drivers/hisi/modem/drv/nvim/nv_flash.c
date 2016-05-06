

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e537*/
#include "nv_file.h"
#include "nv_comm.h"
#include <linux/err.h>
#include <linux/mtd/mtd.h>
#include "ptable_com.h"
#include "bsp_nandc.h"
/*lint -restore +e537*/

/*lint -save -e438 -e958*/
static struct nv_flash_file_header_stru g_nv_file[NV_FILE_BUTT] = {
                          {NULL,NV_FILE_DLOAD,          0,0,0,0,IMAGE_NVDLD,    NV_DLOAD_PATH,            NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_BACKUP,         0,0,0,0,IMAGE_NVBACKLTE,NV_BACK_PATH,             NV_BACK_SEC_NAME,  NULL},
                          {NULL,NV_FILE_XNV_CARD_1,     0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD1_PATH,        NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_XNV_CARD_2,     0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD2_PATH,        NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_XNV_CARD_3,     0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD3_PATH,        NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_CUST_CARD_1,    0,0,0,0,IMAGE_NVDLD,    NV_CUST_CARD1_PATH,       NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_CUST_CARD_2,    0,0,0,0,IMAGE_NVDLD,    NV_CUST_CARD2_PATH,       NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_CUST_CARD_3,    0,0,0,0,IMAGE_NVDLD,    NV_CUST_CARD3_PATH,       NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_SYS_NV,         0,0,0,0,IMAGE_NVDLD,    NV_FILE_SYS_NV_PATH,      NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_DEFAULT,        0,0,0,0,IMAGE_NVFACTORY,NV_DEFAULT_PATH,          NV_DEF_SEC_NAME,   NULL},
                          {NULL,NV_FILE_XNV_MAP_CARD_1, 0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD1_MAP_PATH,    NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_XNV_MAP_CARD_2, 0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD2_MAP_PATH,    NV_DLOAD_SEC_NAME, NULL},
                          {NULL,NV_FILE_XNV_MAP_CARD_3, 0,0,0,0,IMAGE_NVDLD,    NV_XNV_CARD3_MAP_PATH,    NV_DLOAD_SEC_NAME, NULL},
                                                                  };

static struct nv_flash_global_ctrl_stru g_flash_info = {};
static struct nv_global_debug_stru g_flash_debug[NV_FILE_OPS_MAX_API] = {};

static struct nv_sec_file_block_info g_sec_info = {};

extern s32 bsp_nand_write_dload(const char *partition_name, u32 partition_offset,
    void* ptr_ram_addr, u32 length);
/*reseverd1 used to reg branch*/
void nv_file_debug(u32 type,u32 reseverd1,u32 reserved2,u32 reserved3,u32 reserved4)
{
    g_flash_debug[type].callnum++;
    g_flash_debug[type].reseved1 = reseverd1;
    g_flash_debug[type].reseved2 = reserved2;
    g_flash_debug[type].reseved3 = reserved3;
    g_flash_debug[type].reseved4 = reserved4;
}


void nv_flash_help(u32 type)
{
    u32 i;
    if(type == NV_FILE_OPS_MAX_API)
    {
        for(i = 0;i< NV_FILE_OPS_MAX_API;i++)
        {
            printf("************flash fun id %d************\n",i);
            printf("call num             : 0x%x\n",g_flash_debug[i].callnum);
            printf("out branch (reseved1): 0x%x\n",g_flash_debug[i].reseved1);
            printf("reseved2             : 0x%x\n",g_flash_debug[i].reseved2);
            printf("reseved3             : 0x%x\n",g_flash_debug[i].reseved3);
            printf("reseved4             : 0x%x\n",g_flash_debug[i].reseved4);
            printf("***************************************\n");
        }
        return ;
    }

    i = type;

    nv_mntn_record("************flash fun id %d************\n",i);
    nv_mntn_record("call num             : 0x%x\n",g_flash_debug[i].callnum);
    nv_mntn_record("out branch (reseved1): 0x%x\n",g_flash_debug[i].reseved1);
    nv_mntn_record("reseved2             : 0x%x\n",g_flash_debug[i].reseved2);
    nv_mntn_record("reseved3             : 0x%x\n",g_flash_debug[i].reseved3);
    nv_mntn_record("reseved4             : 0x%x\n",g_flash_debug[i].reseved4);
    nv_mntn_record("**************************************\n");
}

u32 nv_get_nand_info(const s8* name,struct nv_nand_info_stru* nand_info)
{
    struct mtd_info* mtd;

    mtd = get_mtd_device_nm(name);
    if (IS_ERR(mtd))
    {
        printf("[%s]:get mtd device err! %s\n",__func__,name);
        return NV_ERROR;
    }
    nand_info->page_size  = (u32)mtd->writesize;
    nand_info->block_size = (u32)mtd->erasesize;
    nand_info->total_size = (u32)mtd->size;
    put_mtd_device(mtd);

    return NV_OK;
}
/*
 * count off in this sec,bewteen sec head to off in this sec
 * count good block
 */
u32 nv_sec_off_count(struct nv_flash_file_header_stru* ffp,u32 vir_off,u32* phy_off)
{
    u32 block_size = ffp->mtd->erasesize;
    u32 block_count;

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

/*
 *get file info in back ,default,nvdload
 */
u32 nv_sec_file_info_init(const s8* name,struct nv_file_info_stru* sec_info,u32* off_info)
{
    u32 ret = NV_ERROR;
    u32 file_len = 0;
    struct nv_file_info_stru info;
    struct nv_ctrl_file_info_stru ctrl_info;
    u8* file_info;

    *off_info = 0;
    /*first: read nv ctrl file*/
    ret = (u32)bsp_nand_read((char*)name,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(NAND_OK != ret)
    {
        printf("[%s]:patrition name %s,read file ret 0x%x,\n",__func__,name,ret);
        return ret;
    }

    /*second :check magic num in file head*/
    /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        printf("[%s]:enter this way  1111! %s\n",__func__,name);
        return NV_OK;
    }

    /*third: read all nv ctrl file*/
    /* coverity[uninit_use] */
    file_info = (u8*)nv_malloc(ctrl_info.file_size+1);
    if(NULL == file_info)
    {
        printf("[%s]:enter this way  2222! %s\n",__func__,name);
        return BSP_ERR_NV_MALLOC_FAIL;
    }
    ret = (u32)bsp_nand_read((char*)name,sizeof(struct nv_ctrl_file_info_stru),file_info,ctrl_info.file_size,NULL);
    if(NAND_OK != ret)
    {
        printf("[%s]:enter this way 3333! %s\n",__func__,name);
        goto init_end;
    }

    if(!strcmp(name, g_nv_file[NV_FILE_BACKUP].name))
    {
        /*fourth: count nv file len base the ctrl file info*/
        /* coverity[uninit_use_in_call] */
        ret = nv_get_bin_crc_file_len(&ctrl_info,(struct nv_file_list_info_stru*)file_info,&file_len);
        if(ret)
        {
            printf("[%s]:enter this way 4444! %s\n",__func__,name);
            goto init_end;
        }
    }
    else
    {
        /* coverity[uninit_use_in_call] */
        ret = nv_get_bin_file_len(&ctrl_info,(struct nv_file_list_info_stru*)file_info,&file_len);
        if(ret)
        {
            printf("[%s]:enter this way 4444! %s\n",__func__,name);
            goto init_end;
        }
    }
    /*forth: count nv file good block offset in the sec*/
    ret = nv_count_file_sec_info(name,file_len,off_info);
    if(ret)
    {
        printf("[%s]:enter this way 5555! %s\n",__func__,name);
        goto init_end;
    }


    info.len       = file_len;
    info.magic_num = NV_FILE_EXIST;
    info.off       = 0;


    memcpy(sec_info,&info,sizeof(info));
init_end:
    nv_free(file_info);
    return NV_OK;
}


u32 nv_dload_file_info_init(void)
{
    u32 ret = NV_ERROR;
    struct nv_dload_packet_head_stru nv_dload;
    STRU_XNV_MAP_FILE_INFO * other_card_info = NULL;
    u32 total_len;
    u32 i = 0;
    u32 multi_card = 0;

    g_sec_info.nv_dload[0] = 0;
    /*first read file packet head*/
    ret = (u32)bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload),NULL);
    if(ret)
    {
        printf("[%s]:ret 0x%x,\n",__func__,ret);
        return ret;
    }
    if( nv_dload.nv_bin.magic_num != NV_FILE_EXIST)
    {
        printf("dload file not exsit, nv_dload.nv_bin.magic_num = 0x%x\n", nv_dload.nv_bin.magic_num);

        memset((void *)&(g_flash_info.nv_dload), 0, sizeof(g_flash_info.nv_dload));
        if(g_flash_info.other_card_info)
        {
            nv_free(g_flash_info.other_card_info);
            g_flash_info.other_card_info = NULL;
        }
        return BSP_ERR_NV_NO_FILE;
    }

    multi_card = (nv_dload.ulSimNumEx > 0)&&(NV_CTRL_FILE_MAGIC_NUM != nv_dload.ulSimNumEx);

    /*是否支持双卡外的其他卡*/
    if(multi_card)
    {
        other_card_info = (STRU_XNV_MAP_FILE_INFO *)nv_malloc(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO));
        g_flash_info.other_card_info = (STRU_XNV_MAP_FILE_INFO *)nv_malloc(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO));
        if((!other_card_info)||(!g_flash_info.other_card_info))
        {
            if(other_card_info){nv_free(other_card_info);other_card_info = NULL;}
            if(g_flash_info.other_card_info){nv_free(g_flash_info.other_card_info);g_flash_info.other_card_info = NULL;}
            printf("%s :malloc fail\n",__func__);
            return BSP_ERR_NV_MALLOC_FAIL;
        }
        ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,sizeof(nv_dload), other_card_info, \
            (nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO)), NULL);;
        if(ret)
        {
            nv_free(other_card_info);
            other_card_info = NULL;
            nv_free(g_flash_info.other_card_info);
            g_flash_info.other_card_info = NULL;
            printf("%s :read nvdload error! ret = 0x%x\n",__func__,ret);
            return ret;
        }

    }

    /*second count file total len*/
    total_len = sizeof(nv_dload);
    total_len += ((nv_dload.nv_bin.magic_num == NV_FILE_EXIST)?nv_dload.nv_bin.len:0);
    for(i=0;i<2;i++)/*双卡双待有双份xml数据*/
    {
        /* coverity[uninit_use] */
        total_len += ((nv_dload.xnv_xml[i].magic_num == NV_FILE_EXIST)?nv_dload.xnv_xml[i].len:0);
        /* coverity[uninit_use] */
        total_len += ((nv_dload.cust_xml[i].magic_num == NV_FILE_EXIST)?nv_dload.cust_xml[i].len:0);
        /* coverity[uninit_use] */
        total_len += ((nv_dload.xnv_map[i].magic_num == NV_FILE_EXIST)?nv_dload.xnv_map[i].len:0);
    }

    if(multi_card)
    {
        for(i = 0;(i < nv_dload.ulSimNumEx); i++)
        {
            total_len += ((other_card_info[i].stXnvFile.magic_num == NV_FILE_EXIST)?other_card_info[i].stXnvFile.len:0);
            total_len += ((other_card_info[i].stCustFile.magic_num == NV_FILE_EXIST)?other_card_info[i].stCustFile.len:0);
            total_len += ((other_card_info[i].stMapFile.magic_num == NV_FILE_EXIST)?other_card_info[i].stMapFile.len:0);
        }
    }


    ret = nv_count_file_sec_info((const s8*)NV_DLOAD_SEC_NAME,total_len,g_sec_info.nv_dload);
    if(ret)
    {
        if(other_card_info){nv_free(other_card_info);other_card_info = NULL;}
        if(g_flash_info.other_card_info){nv_free(g_flash_info.other_card_info);g_flash_info.other_card_info = NULL;}
        printf("[%s] ret : 0x%x\n",__func__,ret);
        return NV_ERROR;
    }
    memcpy(&g_flash_info.nv_dload,&nv_dload,sizeof(nv_dload));
    if(multi_card)
    {
        memcpy(g_flash_info.other_card_info, other_card_info, nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO));
        if(other_card_info){nv_free(other_card_info);}
    }
    return NV_OK;
}

/*
 * 读nand接口
 * mtd      :   mtd device
 * off      :   loggic offset in this file,need
 * len      :   data len write to flash ,len <= mtd->erasesize
 * ptr      :   the data need to write
 */
u32 nv_mtd_read(struct nv_flash_file_header_stru* ffp,FSZ off,u32 len,u8* ptr)
{
    u32 ret;
    u32 offset = 0;    /*传进来的偏移相对于文件头的逻辑偏移*/
    struct mtd_info* mtd = ffp->mtd;

    ret = nv_sec_off_count(ffp,off,&offset);
    if(ret != NAND_OK)
    {
        return ret;
    }
    ret = (u32)bsp_nand_read((char*)mtd->name,offset,ptr,len,NULL);

    return ret;
}


/*
 * 写nand接口
 * mtd      :   mtd device
 * off      :   loggic offset in this file,need
 * len      :   data len write to flash ,len <= mtd->erasesize
 * ptr      :   the data need to write
 */
u32 nv_mtd_write(struct nv_flash_file_header_stru* ffp,FSZ off,u32 len,u8* ptr)
{
    u32 ret;
    u32 offset = 0;    /*传进来的偏移相对于文件头的逻辑偏移*/
    struct mtd_info* mtd = ffp->mtd;

    ret = nv_sec_off_count(ffp,off,&offset);
    if(ret != NAND_OK)
    {
        nv_printf("%s\n",mtd->name);
        return ret;
    }
    if ( NV_FILE_SYS_NV == ffp->flash_type )
    {
        ret = (u32)bsp_nand_write_dload((char*)mtd->name,offset,ptr,len);
    }
    else
    {
        ret = (u32)bsp_nand_write((char*)mtd->name,offset,ptr,len);
    }
    if(ret)
    {
        nv_printf("%s\n",mtd->name);
        return ret;
    }
    return ret;
}

/*read area init info*/
static inline u32 nv_get_nvbin_info(const s8* mode,u32* offset,u32* len)
{
    if(g_flash_info.nv_dload.nv_bin.magic_num== NV_FILE_EXIST)
    {
        *offset = g_flash_info.nv_dload.nv_bin.off;
        *len    = g_flash_info.nv_dload.nv_bin.len;
        return NV_OK;
    }
    else
    {
        return NV_ERROR;
    }
}

static inline u32 nv_get_xnv_info(u32 card_type,u32* offset,u32* len)
{
    if(card_type <= NV_USIMM_CARD_2)
    {

        if(g_flash_info.nv_dload.xnv_xml[card_type-1].magic_num == NV_FILE_EXIST)
        {
            *offset = g_flash_info.nv_dload.xnv_xml[card_type-1].off;
            *len    = g_flash_info.nv_dload.xnv_xml[card_type-1].len;
            return NV_OK;
        }
    }
    else
    {
        if((g_flash_info.other_card_info[card_type-3].stXnvFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_flash_info.other_card_info[card_type-3].stXnvFile.off;
            *len    = g_flash_info.other_card_info[card_type-3].stXnvFile.len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }
    return NV_ERROR;
}

static inline u32 nv_get_xnv_map_info(u32 card_type,u32* offset,u32* len)
{
    if(card_type <= NV_USIMM_CARD_2)
    {

        if(g_flash_info.nv_dload.xnv_map[card_type-1].magic_num == NV_FILE_EXIST)
        {
            *offset = g_flash_info.nv_dload.xnv_map[card_type-1].off;
            *len    = g_flash_info.nv_dload.xnv_map[card_type-1].len;
            return NV_OK;
        }
    }
    else
    {
        if((g_flash_info.other_card_info[card_type-3].stMapFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_flash_info.other_card_info[card_type-3].stMapFile.off;
            *len    = g_flash_info.other_card_info[card_type-3].stMapFile.len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }
    return NV_ERROR;
}
static inline u32 nv_get_cust_info(u32 card_type,u32* offset,u32* len)
{
    if(card_type <= NV_USIMM_CARD_2)
    {
        if(g_flash_info.nv_dload.cust_xml[card_type-1].magic_num== NV_FILE_EXIST)
        {
            *offset = g_flash_info.nv_dload.cust_xml[card_type-1].off;
            *len    = g_flash_info.nv_dload.cust_xml[card_type-1].len;
            return NV_OK;
        }
    }
    else
    {
        if((g_flash_info.other_card_info[card_type-3].stCustFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_flash_info.other_card_info[card_type-3].stCustFile.off;
            *len    = g_flash_info.other_card_info[card_type-3].stCustFile.len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }
    return NV_ERROR;
}
static inline u32 nv_get_sys_nv_info(const s8* mode,u32* offset,u32* len)
{
    s32 ret = strcmp(NV_FILE_READ,mode);

    nv_check_file_mode(mode);

    if(B_READ  == ret)
    {
        if(g_flash_info.sys_nv.magic_num != NV_FILE_EXIST)
        {
            return NV_ERROR;
        }
        *offset = g_flash_info.sys_nv.off;
        *len    = g_flash_info.sys_nv.len;
        return NV_OK;
    }
    else
    {
        *offset = 0;
        *len    = 0;
        return NV_OK;
    }

}
static inline u32 nv_get_default_info(const s8* mode,u32* offset,u32* len)
{
    s32 ret = strcmp(NV_FILE_READ,mode);

    nv_check_file_mode(mode);

    if(B_READ  == ret)
    {
        if(g_flash_info.def_sec.magic_num == NV_FILE_EXIST)
        {
            *offset = g_flash_info.def_sec.off;
            *len    = g_flash_info.def_sec.len;
            return NV_OK;
        }
        return NV_ERROR;
    }
    else
    {
        *offset = 0;
        *len    = 0;
        return NV_OK;
    }
}
static inline u32 nv_get_back_info(const s8* mode,u32* offset,u32* len)
{
    s32 ret = strcmp(NV_FILE_READ,mode);

    nv_check_file_mode(mode);

    if(B_READ  == ret)
    {
        if(g_flash_info.bak_sec.magic_num == NV_FILE_EXIST)
        {
            *offset = g_flash_info.bak_sec.off;
            *len    = g_flash_info.bak_sec.len;
            return NV_OK;
        }
        return NV_ERROR;
    }
    else
    {
        *offset = 0;
        *len    = 0;
        return NV_OK;
    }
}


u32 nv_flash_init(void)
{
    u32 ret = NV_ERROR;
    u32 i = 0;

    nv_file_debug(NV_FILE_INIT_API,0,0,0,0);

    /*first init every file sem*/
    for(i = 0;i<NV_FILE_BUTT;i++)
    {
        osl_sem_init(1,&g_nv_file[i].file_sem);
    }

    memset(&g_flash_info,0,sizeof(struct nv_flash_global_ctrl_stru));
    memset(&g_sec_info,0xff,sizeof(struct nv_sec_file_block_info));

    /*get dload info*/
    ret = nv_dload_file_info_init();
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,1,ret,0,0);
    }
    /*get sys nv file info*/
    ret = nv_sec_file_info_init(g_nv_file[NV_FILE_SYS_NV].name,&g_flash_info.sys_nv,g_sec_info.sys_nv);
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,2,ret,0,0);
        goto nv_flash_init_err;
    }
    /*get backup info*/
    ret = nv_sec_file_info_init(g_nv_file[NV_FILE_BACKUP].name,&g_flash_info.bak_sec,g_sec_info.nv_bak);
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,3,ret,0,0);
        goto nv_flash_init_err;
    }

    /*get default info*/
    ret = nv_sec_file_info_init(g_nv_file[NV_FILE_DEFAULT].name,&g_flash_info.def_sec,g_sec_info.nv_default);
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,4,ret,0,0);
        goto nv_flash_init_err;
    }
    return NV_OK;
nv_flash_init_err:
    nv_mntn_record("\n[%s]\n",__func__);
    nv_flash_help(NV_FILE_INIT_API);
    return NV_ERROR;
}




FILE* nv_flash_open(const s8* path,const s8* mode)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    struct nv_flash_file_header_stru* ffp = NULL;
    u32 offset = 0;
    u32 len = 0;
    struct mtd_info* mtd = NULL;

    nv_file_debug(NV_FILE_OPEN_API,0,0,0,0);

    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            ffp = &g_nv_file[i];
            mtd = get_mtd_device_nm(ffp->name);
            if(IS_ERR(mtd))
            {
                printf("[%s]:get mtd device err! %s\n",__func__,ffp->name);
                return NULL;
            }
            g_nv_file[i].mtd = mtd;
            break;
        }
    }
    if(NULL == ffp)
    {
        nv_file_debug(NV_FILE_OPEN_API,1,0,0,0);
        return NULL;
    }
    osl_sem_down(&ffp->file_sem);
    switch(ffp->flash_type)
    {
        case NV_FILE_DLOAD:
            ret = nv_get_nvbin_info(mode,&offset,&len);
            break;
        case NV_FILE_BACKUP:
            ret = nv_get_back_info(mode,&offset,&len);
            break;
        case NV_FILE_XNV_CARD_1:
            ret = nv_get_xnv_info(NV_USIMM_CARD_1,&offset,&len);
            break;
        case NV_FILE_CUST_CARD_1:
            ret = nv_get_cust_info(NV_USIMM_CARD_1,&offset,&len);
            break;
        case NV_FILE_XNV_CARD_2:
            ret = nv_get_xnv_info(NV_USIMM_CARD_2,&offset,&len);
            break;
        case NV_FILE_CUST_CARD_2:
            ret = nv_get_cust_info(NV_USIMM_CARD_2,&offset,&len);
            break;
        case NV_FILE_XNV_CARD_3:
            ret = nv_get_xnv_info(NV_USIMM_CARD_3,&offset,&len);
            break;
        case NV_FILE_CUST_CARD_3:
            ret = nv_get_cust_info(NV_USIMM_CARD_3,&offset,&len);
            break;
        case NV_FILE_SYS_NV:
            ret = nv_get_sys_nv_info(mode,&offset,&len);
            break;
        case NV_FILE_DEFAULT:
            ret = nv_get_default_info(mode,&offset,&len);
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            ret = nv_get_xnv_map_info(NV_USIMM_CARD_1,&offset,&len);
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            ret = nv_get_xnv_map_info(NV_USIMM_CARD_2,&offset,&len);
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            ret = nv_get_xnv_map_info(NV_USIMM_CARD_3,&offset,&len);
            break;
        default:
            ret = BSP_ERR_NV_INVALID_PARAM;
    }

    if(NV_OK != ret)
    {
        put_mtd_device(ffp->mtd);
        osl_sem_up(&ffp->file_sem);
        nv_file_debug(NV_FILE_OPEN_API,3,ffp->flash_type,ret,0);
        return NULL;
    }

    ffp->ops ++;
    ffp->seek   = 0;
    ffp->length = len;
    ffp->off    = offset;
    ffp->fp     = ffp;

    return ffp;
}
 
s32 nv_flash_read(u8* ptr, u32 size, u32 count, FILE* fp)
{
    u32 real_size = 0;
    s32 ret = -1;
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;
    u32 len = size*count;


    nv_file_debug(NV_FILE_READ_API,0,0,size,count);

    if((NULL == ffp)||(ffp->fp != ffp))
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }

    real_size = ((ffp->seek+len) < ffp->length)? len: (ffp->length - ffp->seek );

    ret = (s32)nv_mtd_read(ffp,(ffp->off+ffp->seek),real_size,ptr);/*读取注意文件seek位置*/
    if(ret != NAND_OK)
    {
        nv_file_debug(NV_FILE_READ_API,2,(u32)ret,real_size,ffp->flash_type);
        nv_mntn_record("\n[%s]\n",__func__);
        nv_flash_help(NV_FILE_READ_API);
        return -1;
    }
    ffp->seek += real_size;
    return (s32)real_size;
}

 
s32 nv_flash_write(u8* ptr, u32 size, u32 count, FILE* fp)
{
    s32 ret = -1;
    u32 len = size*count;
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;
    u32* sec_off = NULL;
    struct nv_file_info_stru* file_info;

    nv_file_debug(NV_FILE_WRITE_API,0,0,size,count);

    if((NULL == ffp)||(ffp->fp != ffp))
    {
        nv_file_debug(NV_FILE_WRITE_API,1,0,size,count);
        goto nv_flash_write_err;
    }
    switch(ffp->flash_type)
    {
        case NV_FILE_BACKUP:
            sec_off = g_sec_info.nv_bak;
            file_info = &g_flash_info.bak_sec;
            break;
        case NV_FILE_SYS_NV:
            sec_off = g_sec_info.sys_nv;
            file_info = &g_flash_info.sys_nv;
            break;
        case NV_FILE_DEFAULT:
            sec_off = g_sec_info.nv_default;
            file_info = &g_flash_info.def_sec;
            break;
        default:
            return -1;
    }
    ret = (s32)nv_mtd_write(ffp,(ffp->off+ffp->seek),len,ptr);
    if(ret)
    {
        nv_file_debug(NV_FILE_WRITE_API,3,(u32)ret,len,ffp->flash_type);
        goto nv_flash_write_err;
    }

    ret = (s32)nv_count_file_sec_info(ffp->name,len,sec_off);
    if(ret)
    {
        nv_file_debug(NV_FILE_WRITE_API,4,(u32)ret,len,ffp->flash_type);
        goto nv_flash_write_err;
    }

    file_info->magic_num = NV_FILE_EXIST;
    file_info->len       = len;
    file_info->off       = 0;
    ffp->seek += len;
    return (s32)len;

nv_flash_write_err:
    nv_mntn_record("\n[%s]\n",__func__);
    nv_flash_help(NV_FILE_WRITE_API);
    return BSP_ERR_NV_INVALID_PARAM;
}
 
s32 nv_flash_seek(FILE* fp,s32 offset,s32 whence)
{

    u32 ret = 0;
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;

    nv_file_debug(NV_FILE_SEEK_API,0,(u32)offset,(u32)whence,0);

    if((NULL == ffp)||(ffp->fp != ffp))
    {
        nv_file_debug(NV_FILE_SEEK_API,1,(u32)offset,(u32)whence,0);
        goto out;
    }
    ret = ffp->seek;
    switch(whence)
    {
        case SEEK_SET:
            nv_file_debug(NV_FILE_SEEK_API,2,(u32)offset,(u32)whence,ret);
            ret = (u32)offset;
            break;
        case SEEK_CUR:
            nv_file_debug(NV_FILE_SEEK_API,3,(u32)offset,(u32)whence,ret);
            ret += (u32)offset;
            break;
        case SEEK_END:
            nv_file_debug(NV_FILE_SEEK_API,4,(u32)offset,(u32)whence,ret);
            ret = ffp->length + (u32)offset;
            break;
        default:
            nv_file_debug(NV_FILE_SEEK_API,5,(u32)offset,(u32)whence,ret);
            goto out;
    }
    ffp->seek = ret;
    return NV_OK;
out:
    nv_mntn_record("\n[%s]\n",__func__);
    nv_flash_help(NV_FILE_SEEK_API);
    return BSP_ERR_NV_INVALID_PARAM;
}
 

static inline bool nv_dload_exist_file(void)
{
    u32 ret = 0;
    if(   (g_flash_info.nv_dload.nv_bin.magic_num      != NV_FILE_EXIST)
        &&(g_flash_info.nv_dload.xnv_xml[0].magic_num  != NV_FILE_EXIST)
        &&(g_flash_info.nv_dload.xnv_xml[1].magic_num  != NV_FILE_EXIST)
        &&(g_flash_info.nv_dload.cust_xml[0].magic_num != NV_FILE_EXIST)
        &&(g_flash_info.nv_dload.cust_xml[1].magic_num != NV_FILE_EXIST)
        &&(g_flash_info.nv_dload.xnv_map[0].magic_num != NV_FILE_EXIST)
        &&(g_flash_info.nv_dload.xnv_map[1].magic_num != NV_FILE_EXIST)
        &&(0 == g_flash_info.nv_dload.ulSimNumEx)    
    )
    {
        ret = false;
    }


    return true;
}
s32 nv_flash_remove(const s8* path)
{
    s32 ret = -1;
    struct nv_flash_file_header_stru* ffp = NULL;
    struct erase_info erase;
    struct mtd_info* mtd = NULL;
    u32 i = 0;

    nv_file_debug(NV_FILE_REMOVE_API,0,0,0,0);

    for(i=0;i<NV_FILE_BUTT;i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            ffp = &g_nv_file[i];
            break;
        }
    }

    if(NULL == ffp)
    {
        nv_file_debug(NV_FILE_REMOVE_API,1,0,0,0);
        return -1;
    }
    switch(ffp->flash_type)
    {
        case NV_FILE_DLOAD:
            g_flash_info.nv_dload.nv_bin.magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_BACKUP:
            memset(&g_flash_info.bak_sec,NV_FLASH_FILL,sizeof(struct nv_file_info_stru));
            goto flash_erase;
        case NV_FILE_CUST_CARD_1:
            g_flash_info.nv_dload.cust_xml[0].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_CARD_1:
            g_flash_info.nv_dload.xnv_xml[0].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_CUST_CARD_2:
            g_flash_info.nv_dload.cust_xml[1].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_CARD_2:
            g_flash_info.nv_dload.xnv_xml[1].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_CUST_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                g_flash_info.nv_dload.ulSimNumEx = 0;
                g_flash_info.other_card_info[0].stCustFile.magic_num = NV_FLASH_NULL;
            }
            break;
        case NV_FILE_XNV_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                /*将支持的其他卡数量改为0，则检测是否支持多卡时会返回不支持*/
                g_flash_info.nv_dload.ulSimNumEx = 0;
                g_flash_info.other_card_info[0].stXnvFile.magic_num = NV_FLASH_NULL;
            }
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            g_flash_info.nv_dload.xnv_map[0].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            g_flash_info.nv_dload.xnv_map[1].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                g_flash_info.nv_dload.ulSimNumEx = 0;
                g_flash_info.other_card_info[0].stMapFile.magic_num = NV_FLASH_NULL;
            }
            break;
        case NV_FILE_DEFAULT:
            memset(&g_flash_info.def_sec,NV_FLASH_FILL,sizeof(struct nv_file_info_stru));
            goto flash_erase;
        case NV_FILE_SYS_NV:
            memset(&g_flash_info.sys_nv,NV_FLASH_FILL,sizeof(g_flash_info.sys_nv));
            goto flash_erase;
        default:
            return BSP_ERR_NV_INVALID_PARAM;
    }
    if(true == nv_dload_exist_file())
    {
        return NV_OK;
    }
flash_erase:
    mtd = get_mtd_device_nm(ffp->name);
    if(IS_ERR(mtd))
    {
        printf("[%s]:get mtd device err! %s\n",__func__,ffp->name);
        return -1;
    }
    erase.addr = 0;
    erase.mtd = mtd;
    erase.len = mtd->size;
    erase.callback = NULL;
    erase.priv     = 0;
    erase.time     = 10000;
    erase.retries  = 2;

    ret = mtd_erase(mtd,&erase);
    put_mtd_device(mtd);
    if(ret)
    {
        nv_file_debug(NV_FILE_REMOVE_API,2,(u32)ret,(u32)ffp->flash_type,0);
        nv_mntn_record("[%s]:ret 0x%x,mtd->name %s\n",__func__,ret,mtd->name);
        return ret;
    }

    return NV_OK;
 }

s32 nv_flash_close(FILE* fp)
{
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;

    nv_file_debug(NV_FILE_CLOSE_API,0,0,0,0);

    if((NULL == ffp)||(ffp->fp != ffp))
    {
        nv_file_debug(NV_FILE_CLOSE_API,1,0,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    put_mtd_device(ffp->mtd);
    osl_sem_up(&ffp->file_sem);

    ffp->fp = NULL;
    ffp->seek = 0;
    ffp->length = 0;
    ffp->off = 0;
    ffp->ops --;
    ffp->mtd = NULL;
    if(ffp->ops != 0)
    {
        nv_file_debug(NV_FILE_CLOSE_API,2,ffp->ops,0,0);
        return BSP_ERR_NV_CLOSE_FILE_FAIL;
    }

    return NV_OK;
}

s32 nv_flash_ftell(FILE* fp)
{
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;

    nv_file_debug(NV_FILE_FTELL_API,0,0,0,0);

    if((NULL == ffp)||(ffp->fp != ffp))
    {
        nv_file_debug(NV_FILE_FTELL_API,1,0,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }
    return (s32)(ffp->seek);
}

s32 nv_flash_access(const s8* path,s32 mode)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    struct nv_flash_file_header_stru* ffp = NULL;


    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            ffp = &g_nv_file[i];
            break;
        }
    }
    if(NULL == ffp)
    {
        return -1;
    }
    mode = mode;/* [false alarm]:mode never used */
    switch(ffp->flash_type)
    {
        case NV_FILE_DLOAD:
            ret = (g_flash_info.nv_dload.nv_bin.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_BACKUP:
            ret = (g_flash_info.bak_sec.magic_num== NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_1:
            ret = (g_flash_info.nv_dload.xnv_xml[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_2:
            ret = (g_flash_info.nv_dload.xnv_xml[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_flash_info.other_card_info[0].stXnvFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        case NV_FILE_CUST_CARD_1:
            ret = (g_flash_info.nv_dload.cust_xml[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_CUST_CARD_2:
            ret = (g_flash_info.nv_dload.cust_xml[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_CUST_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_flash_info.other_card_info[0].stCustFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        case NV_FILE_SYS_NV:
            ret = (g_flash_info.sys_nv.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_DEFAULT:
            ret = (g_flash_info.def_sec.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            ret = (g_flash_info.nv_dload.xnv_map[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            ret = (g_flash_info.nv_dload.xnv_map[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_flash_info.other_card_info[0].stMapFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        default:
            return -1;
    }
    if(ret != NV_FILE_EXIST)
    {
        return -1;
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : nv_support_multi_card
 功能描述  : 是否支持多卡nv
 输入参数  : void
 输出参数  : 无
 返 回 值  : 1:支持 0:不支持
*****************************************************************************/
u32 nv_support_multi_card(void)
{
    if(g_flash_info.nv_dload.nv_bin.magic_num != NV_FILE_EXIST) 
    {
       return false; 
    }
    else
    {
        return (u32)((g_flash_info.nv_dload.ulSimNumEx > 0)
                &&(NV_CTRL_FILE_MAGIC_NUM != g_flash_info.nv_dload.ulSimNumEx)
                &&(g_flash_info.other_card_info));/* [false alarm]:屏蔽Fortify */
    }
}
/*****************************************************************************
 函 数 名  : nv_get_dload_file_len
 功能描述  : 计算dload分区的大小
 输入参数  : void
 输出参数  : 无
 返 回 值  : 1:支持 0:不支持
*****************************************************************************/
u32 nv_get_dload_file_len(void)
{
	return 0;
}
u32 nv_read_dload_file(u8* ptr, u32 size, u32 count,u32 offset)
{
    printf("this is a stub\n");
    return NV_OK;
}
/*****************************************************************************
 函 数 名  : nv_flash_update_info
 功能描述  : 更新各个分区的信息
 输入参数  : void
 输出参数  : 无
 返 回 值  : 0 成功 其他失败
*****************************************************************************/
s32 nv_flash_update_info(const s8* path)
{
    u32 ret = NV_ERROR;
    u32 i = 0;

    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            break;
        }
    }
    switch(i)
    {
        case NV_FILE_DLOAD:
            ret = nv_dload_file_info_init();

            if((ret != BSP_ERR_NV_NO_FILE)&&(ret != NV_OK))
            {
                printf("update dload file fail\n");
            }
            else
            {
                ret = NV_OK;
            }

            break;
        case NV_FILE_BACKUP:
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_BACKUP].name,&g_flash_info.bak_sec,g_sec_info.nv_bak);
            if(ret)
            {
                printf("update backup file fail\n");
            }
            break;
        case NV_FILE_SYS_NV:
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_SYS_NV].name,&g_flash_info.sys_nv,g_sec_info.sys_nv);
            if(ret)
            {
                printf("update sys file fail\n");
            }
            break;
        case NV_FILE_DEFAULT:
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_DEFAULT].name,&g_flash_info.def_sec,g_sec_info.nv_default);
            if(ret)
            {
                printf("update default file fail\n");
            }
            break;
        default:
            ret = BSP_ERR_NV_INVALID_PARAM;
    }

    return ret;
}

void show_flash_info(void)
{
    struct nv_dload_packet_head_stru nv_dload;
    struct nv_ctrl_file_info_stru ctrl_info;
    u8* file_info;
    s32 ret = -1 ;
    u32 i = 0;

    printf("\n******************sys info*********************\n");
    printf("\n************sys nv info in mem**************\n");
    ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(ret)
        return;
     /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        ctrl_info.file_size = 144;
    }
    /* coverity[uninit_use] */
    file_info = (u8*)nv_malloc(ctrl_info.file_size+1);
    if(NULL == file_info)
    {
        return;
    }
    ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,sizeof(ctrl_info),file_info,ctrl_info.file_size,NULL);
    if(ret){
        nv_free(file_info);
        return;
    }
    printf("\n********sys mem info*******\n");
    printf("nv   :flag 0x%x,off 0x%x,len 0x%x\n",g_flash_info.sys_nv.magic_num,\
        g_flash_info.sys_nv.off,g_flash_info.sys_nv.len);
    printf("\n************sys info in nand**************\n");
    /* coverity[uninit_use_in_call] */
    printf("magic :0x%x,file num: %d,nv num :0x%x,modem num :%d\n",\
        ctrl_info.magicnum,ctrl_info.file_num,ctrl_info.ref_count,ctrl_info.modem_num);

    for(i= 0;i< NV_DLOAD_FILE_BLOCK_NUM;i++)
        printf("nv img file %d block off :0x%x\n",i,g_sec_info.sys_nv[i]);

    printf("\n******************dload info*******************\n");
    ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload),NULL);
    if(ret){
        nv_free(file_info);
        return;
    }
    printf("\n********dload mem info*******\n");
    printf("nv   : flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.nv_bin.magic_num,\
        g_flash_info.nv_dload.nv_bin.len,g_flash_info.nv_dload.nv_bin.off);

    printf("xnv1 : flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.xnv_xml[0].magic_num,\
        g_flash_info.nv_dload.xnv_xml[0].len,g_flash_info.nv_dload.xnv_xml[0].off);
    printf("cust1: flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.cust_xml[0].magic_num,\
        g_flash_info.nv_dload.cust_xml[0].len,g_flash_info.nv_dload.cust_xml[0].off);

    printf("xnv2 : flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.xnv_xml[1].magic_num,\
        g_flash_info.nv_dload.xnv_xml[1].len,g_flash_info.nv_dload.xnv_xml[1].off);
    printf("cust2: flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.cust_xml[1].magic_num,\
        g_flash_info.nv_dload.cust_xml[1].len,g_flash_info.nv_dload.cust_xml[1].off);

    printf("xnv map1: flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.xnv_map[0].magic_num,\
        g_flash_info.nv_dload.xnv_map[0].len,g_flash_info.nv_dload.xnv_map[0].off);
    printf("xnv map2: flag 0x%x,len 0x%x,off 0x%x\n",g_flash_info.nv_dload.xnv_map[1].magic_num,\
        g_flash_info.nv_dload.xnv_map[1].len,g_flash_info.nv_dload.xnv_map[1].off);

    if(NV_SUPPORT_MULTI_CARD)
    {
        for(i = 0; i < g_flash_info.nv_dload.ulSimNumEx; i++)
        {
            printf("xnv%d : flag 0x%x,len 0x%x,off 0x%x\n",i, g_flash_info.other_card_info[i].stXnvFile.magic_num,\
                g_flash_info.other_card_info[i].stXnvFile.len, g_flash_info.other_card_info[i].stXnvFile.off);
            printf("cust%d: flag 0x%x,len 0x%x,off 0x%x\n",i ,g_flash_info.other_card_info[i].stCustFile.magic_num,\
                g_flash_info.other_card_info[i].stCustFile.len,g_flash_info.other_card_info[i].stCustFile.off);
            printf("xnv map%d: flag 0x%x,len 0x%x,off 0x%x\n",i, g_flash_info.other_card_info[i].stMapFile.off,\
                g_flash_info.other_card_info[i].stMapFile.len, g_flash_info.other_card_info[i].stMapFile.off);

        }
    }
    printf("\n********dload mtd info*******\n");
    printf("nv   : flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.nv_bin.magic_num,\
        nv_dload.nv_bin.len,nv_dload.nv_bin.off);
    /* coverity[uninit_use] */
    printf("xnv1 : flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.xnv_xml[0].magic_num,\
        nv_dload.xnv_xml[0].len,nv_dload.xnv_xml[0].off);
     /* coverity[uninit_use] */
    printf("cust1: flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.cust_xml[0].magic_num,\
        nv_dload.cust_xml[0].len,nv_dload.cust_xml[0].off);

    printf("xnv2 : flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.xnv_xml[1].magic_num,\
        nv_dload.xnv_xml[1].len,nv_dload.xnv_xml[1].off);
    printf("cust2: flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.cust_xml[1].magic_num,\
        nv_dload.cust_xml[1].len,nv_dload.cust_xml[1].off);
     /* coverity[uninit_use] */
    printf("xnv map1: flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.xnv_map[0].magic_num,\
        nv_dload.xnv_map[0].len,nv_dload.xnv_map[0].off);
    printf("xnv map2: flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.xnv_map[1].magic_num,\
        nv_dload.xnv_map[1].len,nv_dload.xnv_map[1].off);

    if(NV_SUPPORT_MULTI_CARD)
    {
        for(i = 0; i < nv_dload.ulSimNumEx; i++)
        {
            printf("xnv%d : flag 0x%x,len 0x%x,off 0x%x\n",i ,nv_dload.xnv_file[i].stXnvFile.magic_num,\
                nv_dload.xnv_file[i].stXnvFile.len,nv_dload.xnv_file[i].stXnvFile.off);
             /* coverity[uninit_use] */
            printf("cust%d: flag 0x%x,len 0x%x,off 0x%x\n",i ,nv_dload.xnv_file[i].stCustFile.magic_num,\
                nv_dload.xnv_file[i].stCustFile.len,nv_dload.xnv_file[i].stCustFile.off);
             printf("xnv map%d: flag 0x%x,len 0x%x,off 0x%x\n",i ,nv_dload.xnv_file[i].stMapFile.magic_num,\
                 nv_dload.xnv_file[i].stMapFile.len,nv_dload.xnv_file[i].stMapFile.off);
        }
    }
    for(i= 0;i<NV_DLOAD_FILE_BLOCK_NUM;i++)
        printf("nv dload file %d block off :0x%x\n",i,g_sec_info.nv_dload[i]);

    printf("\n******************backup info******************\n");
    printf("\n********backup mem info******\n");
    printf("backup flag: 0x%x, len : 0x%x, off:0x%x\n",g_flash_info.bak_sec.magic_num,\
        g_flash_info.bak_sec.len,g_flash_info.bak_sec.off);
    printf("\n********backup mtd info******\n");
    ret = bsp_nand_read((char*)NV_BACK_SEC_NAME,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(ret){
        nv_free(file_info);
        return;
    }
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        ctrl_info.file_size = 144;
    }
    ret = bsp_nand_read((char*)NV_BACK_SEC_NAME,sizeof(ctrl_info),file_info,ctrl_info.file_size,NULL);
    if(ret){
        nv_free(file_info);
        return;
    }
    printf("magic :0x%x,file num: %d,nv num :0x%x,modem num :%d\n",\
        ctrl_info.magicnum,ctrl_info.file_num,ctrl_info.ref_count,ctrl_info.modem_num);
    for(i= 0;i<NV_BIN_FILE_BLOCK_NUM;i++)
        printf("nv back file %d block off :0x%x\n",i,g_sec_info.nv_bak[i]);

    printf("\n******************default info*****************\n");
    printf("\n********default mem info*****\n");
    printf("default flag: 0x%x, len : 0x%x, off:0x%x\n",g_flash_info.def_sec.magic_num,\
        g_flash_info.def_sec.len,g_flash_info.def_sec.off);

    printf("\n********default mtd info*****\n");
    ret = bsp_nand_read((char*)NV_DEF_SEC_NAME,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(ret){
        nv_free(file_info);
        return;
    }
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        ctrl_info.file_size = 144;
    }
    ret = bsp_nand_read((char*)NV_DEF_SEC_NAME,sizeof(ctrl_info),file_info,ctrl_info.file_size,NULL);
    if(ret){
        nv_free(file_info);
        return;
    }
    printf("magic :0x%x,file num: %d,nv num :0x%x,modem num :%d\n",\
        ctrl_info.magicnum,ctrl_info.file_num,ctrl_info.ref_count,ctrl_info.modem_num);
    for(i= 0;i<NV_BIN_FILE_BLOCK_NUM;i++)
        printf("nv default file %d block off :0x%x\n",i,g_sec_info.nv_default[i]);
    nv_free(file_info);
}



#if 0
void nv_bak_bad_block_flag(u32 num)
{
    struct mtd_info* mtd;
    u32 sec_off;

    mtd = get_mtd_device_nm((char*)NV_BACK_SEC_NAME);
    if(!mtd)
    {
        return;
    }
    sec_off = num*mtd->erasesize;

    mtd_block_markbad(mtd,sec_off);
    put_mtd_device(mtd);
}

void nv_dload_bad_block_flag(u32 num)
{
    struct mtd_info* mtd;
    u32 sec_off;

    mtd = get_mtd_device_nm((char*)NV_DLOAD_SEC_NAME);
    if(!mtd)
    {
        return;
    }
    sec_off = num*mtd->erasesize;

    mtd_block_markbad(mtd,sec_off);
    put_mtd_device(mtd);
}

void nv_def_bad_block_flag(u32 num)
{
    struct mtd_info* mtd;
    u32 sec_off;

    mtd = get_mtd_device_nm((char*)NV_DEF_SEC_NAME);
    if(!mtd)
    {
        return;
    }
    sec_off = num*mtd->erasesize;

    mtd_block_markbad(mtd,sec_off);
    put_mtd_device(mtd);
}
#endif
/*lint -restore*/
EXPORT_SYMBOL(show_flash_info);
EXPORT_SYMBOL(nv_flash_help);
EXPORT_SYMBOL(nv_support_multi_card);
EXPORT_SYMBOL(nv_get_dload_file_len);
EXPORT_SYMBOL(nv_read_dload_file);
EXPORT_SYMBOL(nv_flash_update_info);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
