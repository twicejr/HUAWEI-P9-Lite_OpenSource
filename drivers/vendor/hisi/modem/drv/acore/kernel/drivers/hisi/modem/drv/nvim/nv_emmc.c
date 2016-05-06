

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e537*/
#include <linux/err.h>
#include <linux/mtd/mtd.h>
#include <bsp_nandc.h>
#include "nv_file.h"
#include "nv_comm.h"
#include "../../adrv/adrv.h"

/*lint -restore +e537*/

/*lint -save -e438 -e958*/
static struct nv_emmc_file_header_stru g_nv_file[NV_FILE_BUTT] = {
                              {NULL,NV_FILE_DLOAD,          0,0,0,0,NV_DLOAD_PATH,          "", NULL},
                              {NULL,NV_FILE_BACKUP,         0,0,0,0,NV_BACK_PATH,           "", NULL},
                              {NULL,NV_FILE_XNV_CARD_1,     0,0,0,0,NV_XNV_CARD1_PATH,      "", NULL},
                              {NULL,NV_FILE_XNV_CARD_2,     0,0,0,0,NV_XNV_CARD2_PATH,      "", NULL},
                              {NULL,NV_FILE_XNV_CARD_3,     0,0,0,0,NV_XNV_CARD3_PATH,      "", NULL},
                              {NULL,NV_FILE_CUST_CARD_1,    0,0,0,0,NV_CUST_CARD1_PATH,     "", NULL},
                              {NULL,NV_FILE_CUST_CARD_2,    0,0,0,0,NV_CUST_CARD2_PATH,     "", NULL},
                              {NULL,NV_FILE_CUST_CARD_3,    0,0,0,0,NV_CUST_CARD3_PATH,     "", NULL},
                              {NULL,NV_FILE_SYS_NV,         0,0,0,0,NV_FILE_SYS_NV_PATH,    "", NULL},
                              {NULL,NV_FILE_DEFAULT,        0,0,0,0,NV_DEFAULT_PATH,        "", NULL},
                              {NULL,NV_FILE_XNV_MAP_CARD_1, 0,0,0,0,NV_XNV_CARD1_MAP_PATH,  "", NULL},
                              {NULL,NV_FILE_XNV_MAP_CARD_2, 0,0,0,0,NV_XNV_CARD2_MAP_PATH,  "", NULL},
                              {NULL,NV_FILE_XNV_MAP_CARD_3, 0,0,0,0,NV_XNV_CARD3_MAP_PATH,  "", NULL},
                                                                      };

static struct nv_emmc_global_ctrl_stru g_emmc_info = {};
static struct nv_global_debug_stru g_emmc_debug[NV_FILE_OPS_MAX_API] = {};
char g_emmc_area_name[NV_FILE_BUTT][64] = {};

/*reseverd1 used to reg branch*/
void nv_file_debug(u32 type,u32 reseverd1,u32 reserved2,u32 reserved3,u32 reserved4)
{
    g_emmc_debug[type].callnum++;
    g_emmc_debug[type].reseved1 = reseverd1;
    g_emmc_debug[type].reseved2 = reserved2;
    g_emmc_debug[type].reseved3 = reserved3;
    g_emmc_debug[type].reseved4 = reserved4;
}


void nv_emmc_help(u32 type)
{
    u32 i;
    if(type == NV_FILE_OPS_MAX_API)
    {
        for(i = 0;i< NV_FILE_OPS_MAX_API;i++)
        {
            printf("************flash fun id %d************\n",i);
            printf("call num             : 0x%x\n",g_emmc_debug[i].callnum);
            printf("out branch (reseved1): 0x%x\n",g_emmc_debug[i].reseved1);
            printf("reseved2             : 0x%x\n",g_emmc_debug[i].reseved2);
            printf("reseved3             : 0x%x\n",g_emmc_debug[i].reseved3);
            printf("reseved4             : 0x%x\n",g_emmc_debug[i].reseved4);
            printf("***************************************\n");
        }
        return ;
    }

    i = type;

    printf("************flash fun id %d************\n",i);
    printf("call num             : 0x%x\n",g_emmc_debug[i].callnum);
    printf("out branch (reseved1): 0x%x\n",g_emmc_debug[i].reseved1);
    printf("reseved2             : 0x%x\n",g_emmc_debug[i].reseved2);
    printf("reseved3             : 0x%x\n",g_emmc_debug[i].reseved3);
    printf("reseved4             : 0x%x\n",g_emmc_debug[i].reseved4);
    printf("**************************************\n");
}

u32 nv_get_emmc_info(const s8* name,struct nv_emmc_info_stru* emmc_info)
{
    struct mtd_info* mtd;

    mtd = get_mtd_device_nm(name);
    if (IS_ERR(mtd))
    {
        printf("[%s]:get mtd device err! %s\n",__func__,name);
        return NV_ERROR;
    }
    emmc_info->page_size  = (u32)mtd->writesize;
    emmc_info->block_size = (u32)mtd->erasesize;
    emmc_info->total_size = (u32)mtd->size;
    put_mtd_device(mtd);

    return NV_OK;
}
/*
 * count off in this sec,bewteen sec head to off in this sec,EMMC:vir_off == phy_off
 */
u32 nv_sec_off_count(struct nv_emmc_file_header_stru* fd,u32 vir_off, loff_t* phy_off)
{
    *phy_off = (loff_t)(unsigned long)vir_off;/* [false alarm]:屏蔽Fortify */
    return NV_OK;
}
/*
 *   off must be block alined,check the every block data,emmc:no need to check the file
 */

u32 nv_img_sec_check(const s8* name,u32 off,u32 len)
{
    return NV_OK;
}

/*
 *get file info in back ,default,nvdload
 */
u32 nv_sec_file_info_init(const s8* name,struct nv_file_info_stru* sec_info)
{
    u32 ret = NV_ERROR;
    u32 file_len = 0;
    struct nv_file_info_stru info;
    struct nv_ctrl_file_info_stru ctrl_info;
    u8* file_info;

    /*first: read nv ctrl file*/
    ret = (u32)bsp_nand_read((char*)name,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(NAND_OK != ret)
    {
        printf("[%s]:patrition name %s,get file magic fail ret 0x%x,\n",__func__,name,ret);
        return ret;
    }

    /*second :check magic num in file head*/
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        printf("[%s]:enter this way  1111! %s\n",__func__,name);
        return NV_OK;
    }

    /*third: read all nv ctrl file*/
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
        ret = nv_get_bin_file_len(&ctrl_info,(struct nv_file_list_info_stru*)file_info, &file_len);
        if(ret)
        {
            printf("[%s]:enter this way 4444! %s\n",__func__,name);
            goto init_end;
        }
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
    u32 multi_card = 0;

    /*first read file packet head*/
    ret = (u32)bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload),NULL);
    if(ret)
    {
        printf("[%s]:ret 0x%x,\n",__func__,ret);
        return ret;
    }
    if((nv_dload.nv_bin.magic_num != NV_FILE_EXIST)&&(nv_dload.nv_bin.magic_num != NV_DLOAD_INVALID_FLAG))
    {
        printf("dload file not exsit, nv_dload.nv_bin.magic_num = 0x%x\n", nv_dload.nv_bin.magic_num);

        memset((void *)&(g_emmc_info.nv_dload), 0, sizeof(g_emmc_info.nv_dload));
        if(g_emmc_info.other_card_info)
        {
            nv_free(g_emmc_info.other_card_info);
            g_emmc_info.other_card_info = NULL;
        }

        return BSP_ERR_NV_NO_FILE;
    }
    multi_card = (nv_dload.ulSimNumEx > 0)&&(NV_CTRL_FILE_MAGIC_NUM != nv_dload.ulSimNumEx);

    /*是否支持双卡外的其他卡*/
    if(multi_card)
    {
        other_card_info = (STRU_XNV_MAP_FILE_INFO *)nv_malloc(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO));
        g_emmc_info.other_card_info = (STRU_XNV_MAP_FILE_INFO *)nv_malloc(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO));
        if((!other_card_info)||(!g_emmc_info.other_card_info))
        {
            if(other_card_info){nv_free(other_card_info); other_card_info = NULL;}
            if(g_emmc_info.other_card_info){nv_free(g_emmc_info.other_card_info); g_emmc_info.other_card_info =NULL;}
            printf("%s :malloc fail\n",__func__);
            return BSP_ERR_NV_MALLOC_FAIL;
        }
        ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,sizeof(nv_dload), other_card_info, \
            (nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO)), NULL);;
        if(ret)
        {
            nv_free(other_card_info);
            other_card_info = NULL;
            nv_free(g_emmc_info.other_card_info);
            g_emmc_info.other_card_info = NULL;
            printf("%s :read nvdload error! ret = 0x%x\n",__func__,ret);
            return ret;
        }
    }
    memcpy(&g_emmc_info.nv_dload,&nv_dload,sizeof(nv_dload));
    if(multi_card)
    {
        memcpy(g_emmc_info.other_card_info, other_card_info, nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO));
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
u32 nv_mtd_read(struct nv_emmc_file_header_stru* fd,FSZ off,u32 len,u8* ptr)
{
    u32 ret;
    loff_t offset = 0;    /*传进来的偏移相对于文件头的逻辑偏移*/
    struct mtd_info* mtd = fd->mtd;

    /* coverity[incompatible] */
    ret = nv_sec_off_count(fd,off,&offset);
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
u32 nv_mtd_write(struct nv_emmc_file_header_stru* fd,FSZ off,u32 len,u8* ptr)
{
    u32 ret;
    loff_t offset = 0;    /*传进来的偏移相对于文件头的逻辑偏移*/
    struct mtd_info* mtd = fd->mtd;

    ret = nv_sec_off_count(fd, off, &offset);
    if(ret != NAND_OK)
    {
        nv_printf("%s\n",mtd->name);
        return ret;
    }
    ret = (u32)bsp_nand_write((char*)mtd->name,offset,(void *)ptr,(size_t)len);
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
    if((g_emmc_info.nv_dload.nv_bin.magic_num== NV_FILE_EXIST) ||
       (g_emmc_info.nv_dload.nv_bin.magic_num== NV_DLOAD_INVALID_FLAG) )
    {
        *offset = g_emmc_info.nv_dload.nv_bin.off;
        *len    = g_emmc_info.nv_dload.nv_bin.len;
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
        if(g_emmc_info.nv_dload.xnv_xml[card_type-1].magic_num == NV_FILE_EXIST)
        {
            *offset = g_emmc_info.nv_dload.xnv_xml[card_type-1].off;
            *len    = g_emmc_info.nv_dload.xnv_xml[card_type-1].len;
            return NV_OK;
        }
    }
    else
    {
        if((g_emmc_info.other_card_info[card_type-3].stXnvFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_emmc_info.other_card_info[card_type-3].stXnvFile.off;
            *len    = g_emmc_info.other_card_info[card_type-3].stXnvFile.len;
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
        if(g_emmc_info.nv_dload.xnv_map[card_type-1].magic_num == NV_FILE_EXIST)
        {
            *offset = g_emmc_info.nv_dload.xnv_map[card_type-1].off;
            *len    = g_emmc_info.nv_dload.xnv_map[card_type-1].len;
            return NV_OK;
        }
    }
    else
    {
        if((g_emmc_info.other_card_info[card_type-3].stMapFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_emmc_info.other_card_info[card_type-3].stMapFile.off;
            *len    = g_emmc_info.other_card_info[card_type-3].stMapFile.len;
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
        if(g_emmc_info.nv_dload.cust_xml[card_type-1].magic_num== NV_FILE_EXIST)
        {
            *offset = g_emmc_info.nv_dload.cust_xml[card_type-1].off;
            *len    = g_emmc_info.nv_dload.cust_xml[card_type-1].len;
            return NV_OK;
        }
    }
    else
    {
        if((g_emmc_info.other_card_info[card_type-3].stCustFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_emmc_info.other_card_info[card_type-3].stCustFile.off;
            *len    = g_emmc_info.other_card_info[card_type-3].stCustFile.len;
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
        if(g_emmc_info.sys_nv.magic_num != NV_FILE_EXIST)
        {
            return NV_ERROR;
        }
        *offset = g_emmc_info.sys_nv.off;
        *len    = g_emmc_info.sys_nv.len;
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
        if(g_emmc_info.def_sec.magic_num == NV_FILE_EXIST)
        {
            *offset = g_emmc_info.def_sec.off;
            *len    = g_emmc_info.def_sec.len;
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
    return NV_ERROR;
}
static inline u32 nv_get_back_info(const s8* mode,u32* offset,u32* len)
{
    s32 ret = strcmp(NV_FILE_READ,mode);

    nv_check_file_mode(mode);

    if(B_READ  == ret)
    {
        if(g_emmc_info.bak_sec.magic_num == NV_FILE_EXIST)
        {
            *offset = g_emmc_info.bak_sec.off;
            *len    = g_emmc_info.bak_sec.len;
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


u32 nv_emmc_area_name_init(void)
{
    char result[64] = "block2mtd: ";
    int ret = 0;
    /*升级分区*/
    ret = flash_find_ptn((const char*)PARTITION_MODEM_NVDLOAD_NAME, (char*)g_emmc_area_name[NV_FILE_DLOAD]);
    if(ret)
    {
        nv_error_printf("find %s name fail, ret = 0x%x\n", PARTITION_MODEM_NVDLOAD_NAME, ret);
        return NV_ERROR;
    }
    else
    {
        nv_error_printf(" %s name :%s\n", PARTITION_MODEM_NVDLOAD_NAME, (char*)g_emmc_area_name[NV_FILE_DLOAD]);
    }
    /*出厂分区*/
    ret = flash_find_ptn((const char*)PARTITION_MODEM_NVDEFAULT_NAME, (char*)g_emmc_area_name[NV_FILE_DEFAULT]);
    if(ret)
    {
        nv_error_printf("find %s name fail, ret = 0x%x\n", PARTITION_MODEM_NVDEFAULT_NAME, ret);
        return NV_ERROR;
    }
    else
    {
        nv_error_printf(" %s name :%s\n", PARTITION_MODEM_NVDEFAULT_NAME, (char*)g_emmc_area_name[NV_FILE_DEFAULT]);
    }
    /*备份分区*/
    ret = flash_find_ptn((const char*)PARTITION_MODEM_NVBACKUP_NAME, (char *)g_emmc_area_name[NV_FILE_BACKUP]);
    if(ret)
    {
        nv_error_printf("find %s name fail, ret = 0x%x\n", PARTITION_MODEM_NVBACKUP_NAME, ret);
        return NV_ERROR;
    }
    else
    {
        nv_error_printf(" %s name :%s\n", PARTITION_MODEM_NVBACKUP_NAME, g_emmc_area_name[NV_FILE_BACKUP]);
    }
    /*系统分区*/
    ret = flash_find_ptn((const char*)PARTITION_MODEM_NVSYS_NAME, (char * )g_emmc_area_name[NV_FILE_SYS_NV]);
    if(ret)
    {
        nv_error_printf("find %s name fail, ret = 0x%x\n", PARTITION_MODEM_NVSYS_NAME, ret);
        return NV_ERROR;
    }
    else
    {
        nv_error_printf(" %s name :%s\n", PARTITION_MODEM_NVSYS_NAME, g_emmc_area_name[NV_FILE_SYS_NV]);
    }

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_DLOAD].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_BACKUP], strlen(g_emmc_area_name[NV_FILE_BACKUP]));
    strncpy(g_nv_file[NV_FILE_BACKUP].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_XNV_CARD_1].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_XNV_CARD_2].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_XNV_CARD_3].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_BACKUP], strlen(g_emmc_area_name[NV_FILE_BACKUP]));
    strncpy(g_nv_file[NV_FILE_CUST_CARD_1].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_CUST_CARD_2].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_CUST_CARD_3].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_SYS_NV], strlen(g_emmc_area_name[NV_FILE_SYS_NV]));
    strncpy(g_nv_file[NV_FILE_SYS_NV].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DEFAULT], strlen(g_emmc_area_name[NV_FILE_DEFAULT]));
    strncpy(g_nv_file[NV_FILE_DEFAULT].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_XNV_MAP_CARD_1].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_XNV_MAP_CARD_2].name, result, strlen(result));

    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_emmc_area_name[NV_FILE_DLOAD], strlen(g_emmc_area_name[NV_FILE_DLOAD]));
    strncpy(g_nv_file[NV_FILE_XNV_MAP_CARD_3].name, result, strlen(result));

    /* coverity[buffer_size_warning] */
    strncpy(g_emmc_area_name[NV_FILE_DLOAD], g_nv_file[NV_FILE_DLOAD].name, sizeof(g_emmc_area_name[NV_FILE_DLOAD])-1);
    /* coverity[buffer_size_warning] */
    strncpy(g_emmc_area_name[NV_FILE_SYS_NV], g_nv_file[NV_FILE_SYS_NV].name, sizeof(g_emmc_area_name[NV_FILE_SYS_NV])-1);
    /* coverity[buffer_size_warning] */
    strncpy(g_emmc_area_name[NV_FILE_BACKUP], g_nv_file[NV_FILE_BACKUP].name, sizeof(g_emmc_area_name[NV_FILE_BACKUP])-1);
    /* coverity[buffer_size_warning] */
    strncpy(g_emmc_area_name[NV_FILE_DEFAULT], g_nv_file[NV_FILE_DEFAULT].name, sizeof(g_emmc_area_name[NV_FILE_DEFAULT])-1);
    return NV_OK;
}

u32 nv_emmc_init(void)
{
    u32 ret = NV_ERROR;
    u32 i = 0;

    nv_file_debug(NV_FILE_INIT_API,0,0,0,0);

    /*first init every file sem*/
    for(i = 0;i<NV_FILE_BUTT;i++)
    {
        osl_sem_init(1,&g_nv_file[i].file_sem);
    }

    memset(&g_emmc_info,0,sizeof(struct nv_emmc_global_ctrl_stru));

    /*get sys nv info*/
    ret = nv_sec_file_info_init(g_nv_file[NV_FILE_SYS_NV].name,&g_emmc_info.sys_nv);
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,1,ret,(u32)(unsigned long)g_nv_file[NV_FILE_SYS_NV].mtd,NV_FILE_SYS_NV);
        goto nv_emmc_init_err;
    }
    /*get dload info*/
    ret = nv_dload_file_info_init();
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,2,ret,0,NV_FILE_DLOAD);
    }
    /*get backup info*/
    ret = nv_sec_file_info_init(g_nv_file[NV_FILE_BACKUP].name,&g_emmc_info.bak_sec);
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,3,ret,0,NV_FILE_BACKUP);
        goto nv_emmc_init_err;
    }

    /*get default info*/
    ret = nv_sec_file_info_init(g_nv_file[NV_FILE_DEFAULT].name,&g_emmc_info.def_sec);
    if(ret)
    {
        nv_file_debug(NV_FILE_INIT_API,4,ret,0,NV_FILE_DEFAULT);
        goto nv_emmc_init_err;
    }
    return NV_OK;
nv_emmc_init_err:
    printf("\n[%s]\n",__func__);
    nv_emmc_help(NV_FILE_INIT_API);
    return NV_ERROR;
}




FILE* nv_emmc_open(const s8* path,const s8* mode)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    struct nv_emmc_file_header_stru* fd = NULL;
    u32 offset = 0;
    u32 len = 0;
    struct mtd_info* mtd = NULL;

    nv_file_debug(NV_FILE_OPEN_API,0,0,0,0);

    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            fd = &g_nv_file[i];
            mtd = get_mtd_device_nm(fd->name);
            if(IS_ERR(mtd))
            {
                printf("[%s]:get mtd device err! %s\n",__func__,fd->name);
                return NULL;
            }
            g_nv_file[i].mtd = mtd;
            break;
        }
    }
    if(NULL == fd)
    {
        nv_file_debug(NV_FILE_OPEN_API,1,0,0,0);
        return NULL;
    }
    osl_sem_down(&fd->file_sem);
    switch(fd->emmc_type)
    {
        case NV_FILE_DLOAD:
            ret = nv_get_nvbin_info(mode,&offset,&len);
            break;
        case NV_FILE_BACKUP:
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_BACKUP].name,&g_emmc_info.bak_sec);
            ret |= nv_get_back_info(mode,&offset,&len);
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
        put_mtd_device(fd->mtd);
        osl_sem_up(&fd->file_sem);
        nv_file_debug(NV_FILE_OPEN_API,3,fd->emmc_type,ret,0);
        return NULL;
    }

    fd->ops ++;
    fd->seek   = 0;
    fd->length = len;
    fd->off    = offset;
    fd->fp     = fd;

    return fd;
}
 
s32 nv_emmc_read(u8* ptr, u32 size, u32 count, FILE* fp)
{
    u32 real_size = 0;
    u32 ret;
    struct nv_emmc_file_header_stru* fd = (struct nv_emmc_file_header_stru*)fp;
    u32 len = size*count;


    nv_file_debug(NV_FILE_READ_API,0,0,size,count);

    if((NULL == fd)||(fd->fp != fd))
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }

    real_size = ((fd->seek+len) < fd->length)? len: (fd->length - fd->seek );

    ret = nv_mtd_read(fd,(fd->off+fd->seek),real_size,ptr);/*读取注意文件seek位置*/
    if(ret != NAND_OK)
    {
        nv_file_debug(NV_FILE_READ_API,2,(u32)ret,real_size,fd->emmc_type);
        printf("\n[%s]\n",__func__);
        nv_emmc_help(NV_FILE_READ_API);
        return -1;
    }
    fd->seek += real_size;
    return (s32)real_size;
}

 
s32 nv_emmc_write(u8* ptr, u32 size, u32 count, FILE* fp)
{
    u32 ret = NV_ERROR;
    u32 len = size*count;
    struct nv_emmc_file_header_stru* fd = (struct nv_emmc_file_header_stru*)fp;
    struct nv_file_info_stru* file_info;

    nv_file_debug(NV_FILE_WRITE_API,0,0,size,count);

    if((NULL == fd)||(fd->fp != fd))
    {
        nv_file_debug(NV_FILE_WRITE_API,1,0,size,count);
        goto nv_flash_write_err;
    }
    switch(fd->emmc_type)
    {
        case NV_FILE_BACKUP:
            file_info = &g_emmc_info.bak_sec;
            break;
        case NV_FILE_SYS_NV:
            file_info = &g_emmc_info.sys_nv;
            break;
        case NV_FILE_DEFAULT:
            file_info = &g_emmc_info.def_sec;
            break;
        default:
            return -1;
    }
    ret = (u32)nv_mtd_write(fd,(fd->off+fd->seek),len,ptr);
    if(ret)
    {
        nv_file_debug(NV_FILE_WRITE_API,3,ret,len,fd->emmc_type);
        goto nv_flash_write_err;
    }

    file_info->magic_num = NV_FILE_EXIST;
    file_info->len       = len;
    file_info->off       = 0;
    fd->seek += len;
    return (s32)len;

nv_flash_write_err:
    nv_mntn_record("\n[%s]\n",__func__);
    nv_emmc_help(NV_FILE_WRITE_API);
    return BSP_ERR_NV_INVALID_PARAM;
}
 
s32 nv_emmc_seek(FILE* fp,s32 offset,s32 whence)
{

    u32 ret = 0;
    struct nv_emmc_file_header_stru* fd = (struct nv_emmc_file_header_stru*)fp;

    nv_file_debug(NV_FILE_SEEK_API,0,(u32)offset,(u32)whence,0);

    if((NULL == fd)||(fd->fp != fd))
    {
        nv_file_debug(NV_FILE_SEEK_API,1,(u32)offset,(u32)whence,0);
        goto out;
    }
    ret = fd->seek;
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
            ret = fd->length + (u32)offset;
            break;
        default:
            nv_file_debug(NV_FILE_SEEK_API,5,(u32)offset,(u32)whence,ret);
            goto out;
    }
    fd->seek = ret;
    return NV_OK;
out:
    printf("\n[%s]\n",__func__);
    nv_emmc_help(NV_FILE_SEEK_API);
    return BSP_ERR_NV_INVALID_PARAM;
}
 

static inline bool nv_dload_exist_file(void)
{
    if(   (g_emmc_info.nv_dload.nv_bin.magic_num      != NV_FILE_EXIST)
        &&(g_emmc_info.nv_dload.xnv_xml[0].magic_num  != NV_FILE_EXIST)
        &&(g_emmc_info.nv_dload.xnv_xml[1].magic_num  != NV_FILE_EXIST)
        &&(g_emmc_info.nv_dload.cust_xml[0].magic_num != NV_FILE_EXIST)
        &&(g_emmc_info.nv_dload.cust_xml[1].magic_num != NV_FILE_EXIST)
        &&(g_emmc_info.nv_dload.xnv_map[0].magic_num != NV_FILE_EXIST)
        &&(g_emmc_info.nv_dload.xnv_map[1].magic_num != NV_FILE_EXIST)
        &&(0 == g_emmc_info.nv_dload.ulSimNumEx)
        )
    {
        return false;
    }
    return true;
}
s32 nv_emmc_remove(const s8* path)
{
    s32 ret = -1;
    struct nv_emmc_file_header_stru* fd = NULL;
    struct erase_info erase = {0,};
    struct mtd_info* mtd = NULL;
    u32 i = 0;

    nv_file_debug(NV_FILE_REMOVE_API,0,0,0,0);

    for(i=0;i<NV_FILE_BUTT;i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            fd = &g_nv_file[i];
            break;
        }
    }

    if(NULL == fd)
    {
        nv_file_debug(NV_FILE_REMOVE_API,1,0,0,0);
        return -1;
    }
    switch(fd->emmc_type)
    {
        case NV_FILE_DLOAD:
            g_emmc_info.nv_dload.nv_bin.magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_BACKUP:
            memset(&g_emmc_info.bak_sec,NV_FLASH_FILL,sizeof(struct nv_file_info_stru));
            goto flash_erase;
        case NV_FILE_CUST_CARD_1:
            g_emmc_info.nv_dload.cust_xml[0].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_CARD_1:
            g_emmc_info.nv_dload.xnv_xml[0].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_CUST_CARD_2:
            g_emmc_info.nv_dload.cust_xml[1].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_CARD_2:
            g_emmc_info.nv_dload.xnv_xml[1].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_CUST_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                /*将支持的其他卡数量改为0，则检测是否支持多卡时会返回不支持*/
                g_emmc_info.nv_dload.ulSimNumEx = 0;
                g_emmc_info.nv_dload.xnv_file[0].stCustFile.magic_num = NV_FLASH_NULL;
            }
            break;
        case NV_FILE_XNV_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                /*将支持的其他卡数量改为0，则检测是否支持多卡时会返回不支持*/
                g_emmc_info.nv_dload.ulSimNumEx = 0;
                g_emmc_info.nv_dload.xnv_file[0].stXnvFile.magic_num = NV_FLASH_NULL;
            }
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            g_emmc_info.nv_dload.xnv_map[0].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            g_emmc_info.nv_dload.xnv_map[1].magic_num = NV_FLASH_NULL;
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                /*将支持的其他卡数量改为0，则检测是否支持多卡时会返回不支持*/
                g_emmc_info.nv_dload.ulSimNumEx = 0;
                g_emmc_info.nv_dload.xnv_file[0].stMapFile.magic_num = NV_FLASH_NULL;
            }
            break;
        case NV_FILE_DEFAULT:
            memset(&g_emmc_info.def_sec,NV_FLASH_FILL,sizeof(struct nv_file_info_stru));
            goto flash_erase;
        case NV_FILE_SYS_NV:
            memset(&g_emmc_info.sys_nv,NV_FLASH_FILL,sizeof(g_emmc_info.sys_nv));
            goto flash_erase;
        default:
            return BSP_ERR_NV_INVALID_PARAM;
    }
    if(true == nv_dload_exist_file())
    {
        return NV_OK;
    }
flash_erase:
    mtd = get_mtd_device_nm(fd->name);
    if(IS_ERR(mtd))
    {
        printf("[%s]:get mtd device err! %s\n",__func__,fd->name);
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
    mtd_sync(mtd);
    put_mtd_device(mtd);
    if(ret)
    {
        nv_file_debug(NV_FILE_REMOVE_API,2,(u32)ret,fd->emmc_type,0);
        printf("[%s]:ret 0x%x,mtd->name %s\n",__func__,ret,mtd->name);
        return ret;
    }

    return NV_OK;
 }

s32 nv_emmc_close(FILE* fp)
{
    struct nv_emmc_file_header_stru* fd = (struct nv_emmc_file_header_stru*)fp;

    nv_file_debug(NV_FILE_CLOSE_API,0,0,0,0);

    if((NULL == fd)||(fd->fp != fd))
    {
        nv_file_debug(NV_FILE_CLOSE_API,1,0,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    put_mtd_device(fd->mtd);
    osl_sem_up(&fd->file_sem);

    fd->fp = NULL;
    fd->seek = 0;
    fd->length = 0;
    fd->off = 0;
    fd->ops --;
    fd->mtd = NULL;
    if(fd->ops != 0)
    {
        nv_file_debug(NV_FILE_CLOSE_API,2,fd->ops,0,0);
        return BSP_ERR_NV_CLOSE_FILE_FAIL;
    }

    return NV_OK;
}

s32 nv_emmc_ftell(FILE* fp)
{
    struct nv_emmc_file_header_stru* fd = (struct nv_emmc_file_header_stru*)fp;

    nv_file_debug(NV_FILE_FTELL_API,0,0,0,0);

    if((NULL == fd)||(fd->fp != fd))
    {
        nv_file_debug(NV_FILE_FTELL_API,1,0,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }
    return (s32)fd->seek;
}



s32 nv_emmc_access(const s8* path,s32 mode)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    struct nv_emmc_file_header_stru* fd = NULL;


    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp(path,g_nv_file[i].path))
        {
            fd = &g_nv_file[i];
            break;
        }
    }
    if(NULL == fd)
    {
        return -1;
    }
    mode = mode;
    switch(fd->emmc_type)
    {
        case NV_FILE_DLOAD:
            ret = ((g_emmc_info.nv_dload.nv_bin.magic_num == NV_FILE_EXIST) ||
                   (g_emmc_info.nv_dload.nv_bin.magic_num == NV_DLOAD_INVALID_FLAG))?NV_FILE_EXIST:0;
            break;
        case NV_FILE_BACKUP:
            ret = (g_emmc_info.bak_sec.magic_num== NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_1:
            ret = (g_emmc_info.nv_dload.xnv_xml[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_2:
            ret = (g_emmc_info.nv_dload.xnv_xml[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_emmc_info.other_card_info[0].stXnvFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        case NV_FILE_CUST_CARD_1:
            ret = (g_emmc_info.nv_dload.cust_xml[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_CUST_CARD_2:
            ret = (g_emmc_info.nv_dload.cust_xml[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_CUST_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_emmc_info.other_card_info[0].stCustFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        case NV_FILE_SYS_NV:
            ret = (g_emmc_info.sys_nv.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_DEFAULT:
            ret = (g_emmc_info.def_sec.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            ret = (g_emmc_info.nv_dload.xnv_map[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            ret = (g_emmc_info.nv_dload.xnv_map[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_emmc_info.other_card_info[0].stMapFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
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
    if((g_emmc_info.nv_dload.nv_bin.magic_num != NV_FILE_EXIST)&&(g_emmc_info.nv_dload.nv_bin.magic_num != NV_DLOAD_INVALID_FLAG))
    {
       return false;
    }
    else
    {
        return (u32)((g_emmc_info.nv_dload.ulSimNumEx > 0)
                &&(NV_CTRL_FILE_MAGIC_NUM != g_emmc_info.nv_dload.ulSimNumEx)
                &&(g_emmc_info.other_card_info != NULL));
    }

}
/*****************************************************************************
 函 数 名  : nv_get_dload_file_len
 功能描述  : 计算dload分区的大小,不包含最后的升级包的CRC校验码
 输入参数  : void
 输出参数  : 无
 返 回 值  : 1:支持 0:不支持
*****************************************************************************/
u32 nv_get_dload_file_len(void)
{
	u32 max_off = 0;
	u32 index = 0;
	u32 max_len = 0;

#define MAX_FILE(info, max, size) \
do{\
	if(((NV_FILE_EXIST == info.magic_num )||(NV_DLOAD_INVALID_FLAG == info.magic_num ))&&(max < info.off))\
	{\
		max = info.off; \
        size = info.len;\
	}\
}while(0)

	MAX_FILE(g_emmc_info.nv_dload.cust_xml[0], max_off, max_len);
	MAX_FILE(g_emmc_info.nv_dload.cust_xml[1], max_off, max_len);
	MAX_FILE(g_emmc_info.nv_dload.xnv_xml[0], max_off, max_len);
	MAX_FILE(g_emmc_info.nv_dload.xnv_xml[1], max_off, max_len);
 	MAX_FILE(g_emmc_info.nv_dload.xnv_map[0], max_off, max_len);
	MAX_FILE(g_emmc_info.nv_dload.xnv_map[1], max_off, max_len);
	MAX_FILE(g_emmc_info.nv_dload.nv_bin, max_off, max_len);

	if(nv_support_multi_card())
	{
		for(index = 0; index < g_emmc_info.nv_dload.ulSimNumEx; index++)
		{
			MAX_FILE(g_emmc_info.other_card_info[index].stCustFile, max_off, max_len);
			MAX_FILE(g_emmc_info.other_card_info[index].stMapFile, max_off, max_len);
			MAX_FILE(g_emmc_info.other_card_info[index].stXnvFile, max_off, max_len);
		}
	}
	nv_printf("max:0x%x len:0x%x\n", max_off, max_len);
	return (max_off + max_len);
}

u32 nv_read_dload_file(u8* ptr, u32 size, u32 count,u32 offset)
{
    u32 ret = 0;
    u32 len = size*count;

    if(NULL == ptr)
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }
    ret = (u32)bsp_nand_read(g_nv_file[NV_FILE_DLOAD].name, offset, ptr, len, NULL);
    if(ret != NAND_OK)
    {
        printf("\n[%s]\n read nand fail\n",__func__);
        return ret;
    }
    return NV_OK;
}

/*****************************************************************************
 函 数 名  : nv_flash_update_info
 功能描述  : 更新各个分区的信息
 输入参数  : void
 输出参数  : 无
 返 回 值  : 0 成功 其他失败
*****************************************************************************/
s32 nv_emmc_update_info(const s8* path)
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
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_BACKUP].name,&g_emmc_info.bak_sec);
            if(ret)
            {
                printf("update backup file fail\n");
            }
            break;
        case NV_FILE_SYS_NV:
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_SYS_NV].name,&g_emmc_info.sys_nv);
            if(ret)
            {
                printf("update sys file fail\n");
            }
            break;
        case NV_FILE_DEFAULT:
            ret = nv_sec_file_info_init(g_nv_file[NV_FILE_DEFAULT].name,&g_emmc_info.def_sec);
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
void show_emmc_info(void)
{
    struct nv_dload_packet_head_stru nv_dload = {};
    struct nv_ctrl_file_info_stru ctrl_info = {};
    u8* file_info = NULL;
    s32 ret = -1 ;
    u32 i = 0;

    printf("\n******************img info*********************\n");
    ret = bsp_nand_read((char*)NV_SYS_SEC_NAME,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(ret)
        return;
    /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        /* coverity[uninit_use] */
        ctrl_info.file_size = 144;
    }
    /* coverity[uninit_use] */
    file_info = (u8*)nv_malloc(ctrl_info.file_size+1);
    if(NULL == file_info)
    {
        return;
    }
    ret = bsp_nand_read((char*)NV_SYS_SEC_NAME,sizeof(ctrl_info),file_info,ctrl_info.file_size,NULL);
    if(ret)
    {
        if(file_info)nv_free((void *)file_info);
        return;
    }
    printf("\n********sys mem info*******\n");
    printf("nv   :flag 0x%x,off 0x%x,len 0x%x\n",g_emmc_info.sys_nv.magic_num,\
        g_emmc_info.sys_nv.off,g_emmc_info.sys_nv.len);
    printf("\n************sys info in nand**************\n");
    /* coverity[uninit_use] */
    printf("magic :0x%x,file num: %d,nv num :0x%x,modem num :%d\n",\
        ctrl_info.magicnum,ctrl_info.file_num,ctrl_info.ref_count,ctrl_info.modem_num);

    printf("\n******************dload info*******************\n");
    ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload),NULL);
    if(ret)
    {
        if(file_info)nv_free((void *)file_info);
        return;
    }
    printf("\n********dload mem info*******\n");
    printf("nv   : flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.nv_bin.magic_num,\
        g_emmc_info.nv_dload.nv_bin.len,g_emmc_info.nv_dload.nv_bin.off);
    printf("xnv1 : flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.xnv_xml[0].magic_num,\
        g_emmc_info.nv_dload.xnv_xml[0].len,g_emmc_info.nv_dload.xnv_xml[0].off);
    printf("cust1: flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.cust_xml[0].magic_num,\
        g_emmc_info.nv_dload.cust_xml[0].len,g_emmc_info.nv_dload.cust_xml[0].off);

    printf("xnv2 : flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.xnv_xml[1].magic_num,\
        g_emmc_info.nv_dload.xnv_xml[1].len,g_emmc_info.nv_dload.xnv_xml[1].off);
    printf("cust2: flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.cust_xml[1].magic_num,\
        g_emmc_info.nv_dload.cust_xml[1].len,g_emmc_info.nv_dload.cust_xml[1].off);
    printf("xnv map1: flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.xnv_map[0].magic_num,\
        g_emmc_info.nv_dload.xnv_map[0].len,g_emmc_info.nv_dload.xnv_map[0].off);
    printf("xnv map2: flag 0x%x,len 0x%x,off 0x%x\n",g_emmc_info.nv_dload.xnv_map[1].magic_num,\
        g_emmc_info.nv_dload.xnv_map[1].len,g_emmc_info.nv_dload.xnv_map[1].off);
    if(NV_SUPPORT_MULTI_CARD)
    {
        for(i = 0; i < g_emmc_info.nv_dload.ulSimNumEx; i++)
        {
            printf("xnv%d : flag 0x%x,len 0x%x,off 0x%x\n",i, g_emmc_info.other_card_info[i].stXnvFile.magic_num,\
                g_emmc_info.other_card_info[i].stXnvFile.len, g_emmc_info.other_card_info[i].stXnvFile.off);
            printf("cust%d: flag 0x%x,len 0x%x,off 0x%x\n",i ,g_emmc_info.other_card_info[i].stCustFile.magic_num,\
                g_emmc_info.other_card_info[i].stCustFile.len,g_emmc_info.other_card_info[i].stCustFile.off);
            printf("xnv map%d: flag 0x%x,len 0x%x,off 0x%x\n",i, g_emmc_info.other_card_info[i].stMapFile.magic_num,\
                g_emmc_info.other_card_info[i].stMapFile.len, g_emmc_info.other_card_info[i].stMapFile.off);

        }
    }
    printf("\n********dload mtd info*******\n");
    printf("nv   : flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.nv_bin.magic_num,\
        nv_dload.nv_bin.len,nv_dload.nv_bin.off);
    printf("xnv1 : flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.xnv_xml[0].magic_num,\
        nv_dload.xnv_xml[0].len,nv_dload.xnv_xml[0].off);
    printf("cust1: flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.cust_xml[0].magic_num,\
        nv_dload.cust_xml[0].len,nv_dload.cust_xml[0].off);

    printf("xnv2 : flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.xnv_xml[1].magic_num,\
        nv_dload.xnv_xml[1].len,nv_dload.xnv_xml[1].off);
    printf("cust2: flag 0x%x,len 0x%x,off 0x%x\n",nv_dload.cust_xml[1].magic_num,\
        nv_dload.cust_xml[1].len,nv_dload.cust_xml[1].off);

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
    printf("\n******************backup info******************\n");
    printf("\n********backup mem info******\n");
    printf("backup flag: 0x%x, len : 0x%x, off:0x%x\n",g_emmc_info.bak_sec.magic_num,\
        g_emmc_info.bak_sec.len,g_emmc_info.bak_sec.off);
    printf("\n********backup mtd info******\n");
    ret = bsp_nand_read((char*)NV_BACK_SEC_NAME,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(ret)
    {
        if(file_info)nv_free((void *)file_info);
        return;
    }

    /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        ctrl_info.file_size = 144;
    }
    ret = bsp_nand_read((char*)NV_BACK_SEC_NAME,sizeof(ctrl_info),file_info,ctrl_info.file_size,NULL);
    if(ret)
    {
        if(file_info)nv_free((void *)file_info);
        return;
    }
    /* coverity[uninit_use] */
    printf("magic :0x%x,file num: %d,nv num :0x%x,modem num :%d\n",\
        ctrl_info.magicnum,ctrl_info.file_num,ctrl_info.ref_count,ctrl_info.modem_num);

    printf("\n******************default info*****************\n");
    printf("\n********default mem info*****\n");
    printf("default flag: 0x%x, len : 0x%x, off:0x%x\n",g_emmc_info.def_sec.magic_num,\
        g_emmc_info.def_sec.len,g_emmc_info.def_sec.off);

    printf("\n********default mtd info*****\n");
    ret = bsp_nand_read((char*)NV_DEF_SEC_NAME,0,&ctrl_info,sizeof(ctrl_info),NULL);
    if(ret)
    {
        if(file_info)nv_free((void *)file_info);
        return;
    }
    /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        /* coverity[uninit_use] */
        ctrl_info.file_size = 144;
    }
    ret = bsp_nand_read((char*)NV_DEF_SEC_NAME,sizeof(ctrl_info),file_info,ctrl_info.file_size,NULL);
    if(ret)
    {
        if(file_info)nv_free((void *)file_info);
        return;
    }
    /* coverity[uninit_use] */
    printf("magic :0x%x,file num: %d,nv num :0x%x,modem num :%d\n",\
        ctrl_info.magicnum,ctrl_info.file_num,ctrl_info.ref_count,ctrl_info.modem_num);


    nv_free(file_info);
}
/*lint -restore*/


EXPORT_SYMBOL(nv_emmc_help);
EXPORT_SYMBOL(show_emmc_info);
EXPORT_SYMBOL(nv_read_dload_file);
EXPORT_SYMBOL(nv_get_dload_file_len);
EXPORT_SYMBOL(nv_support_multi_card);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

