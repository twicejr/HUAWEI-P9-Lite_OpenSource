

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include <product_config.h>
/*lint -save -e537*/
#ifndef FEATURE_NV_FLASH_ON
/*lint -save -e537*/
#ifdef HI3630_FASTBOOT_MODEM
#include <flash.h>
#else
#include <partition_ops.h>
#include <emmc_ops.h>
#endif
#include <system.h>
#include <boot.h>
#include "nv_boot.h"
#include "nv_xml_dec.h"
#else
#include "nv_boot.h"
#include "nv_file.h"
#include "fdrv.h"
#endif
/*lint -restore*/

/*lint -save -e438 -e718 -e713 -e746 -e732*/
struct nv_flash_global_ctrl_stru g_boot_file_info;
static u32 g_nvInitFlag = 0;


/*flash ops part*/
/**************************************************************/

void nv_fastboot_debug(u32 line,u32 ret,u32 reserved1,u32 reserved2)
{
/*lint -save -e835*/
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)(unsigned long)NV_GLOBAL_INFO_ADDR;
/*lint -restore +e835*/
    ddr_info->fb_debug.line = line;
    ddr_info->fb_debug.ret = ret;
    ddr_info->fb_debug.reseverd1 = reserved1;
    ddr_info->fb_debug.reseverd2 = reserved2;
}

/*****************************************************************************
 函 数 名  : nv_support_multi_card
 功能描述  : 是否支持多卡nv
 输入参数  : void
 输出参数  : 无
 返 回 值  : 1:支持 0:不支持
*****************************************************************************/
u32 nv_boot_support_multi_card(void)
{
    if(g_boot_file_info.nv_dload.nv_bin.magic_num != NV_FILE_EXIST)
    {
       return 0;
    }
    else
    {
        return (u32)((g_boot_file_info.nv_dload.ulSimNumEx > 0)
                &&(NV_CTRL_FILE_MAGIC_NUM != g_boot_file_info.nv_dload.ulSimNumEx)
                &&(g_boot_file_info.other_card_info));
    }
}
/*lint -save -e818*/
u32 nv_boot_get_flash_file_len\
    (struct nv_ctrl_file_info_stru* ctrl_info,struct nv_file_list_info_stru* file_info,u32 * file_len)
/*lint -restore +e818*/
{
    u32 i;
    *file_len = ctrl_info->ctrl_size;

    for(i = 0;i<ctrl_info->file_num;i++)
    {
        *file_len += file_info->file_size;
        file_info ++;
    }
    if(*file_len > NV_MAX_FILE_SIZE)  /*文件不能可容纳最大长度*/
    {
        printf("[%s]:file len 0x%x,max size 0x%x\n",__FUNCTION__,*file_len,NV_MAX_FILE_SIZE);
        return NV_ERROR;
    }
    return NV_OK;
/*lint -save -e818*/
}
/*lint -restore +e818*/


u32 nv_boot_dload_info_init(void)
{
    struct nv_dload_packet_head_stru nv_dload;
    STRU_XNV_MAP_FILE_INFO * other_card_info = NULL;
    u32 total_len = 0;
    u32 ret = 0;
    u32 i = 0;
    u32 multi_card = 0;
    g_sec_info.nv_dload[0] = 0;
	/*lint -save -e838*/
    ret = g_file_func_table.file_read((char*)NV_DLOAD_SEC_NAME,0, &nv_dload, (u32)sizeof(nv_dload),NULL);
	/*lint -restore +e838*/
    if(ret)
    {
        printf("%s :read nvdload error! ret = 0x%x\n",__func__,ret);
        nv_fastboot_debug(__LINE__,ret,0,0);
        return ret;
    }
    if( nv_dload.nv_bin.magic_num != NV_FILE_EXIST)
    {
        printf("dload file not exsit, nv_dload.nv_bin.magic_num = 0x%x\n", nv_dload.nv_bin.magic_num);
        return BSP_ERR_NV_NO_FILE;
    }
	/*lint -save -e838*/
    multi_card = (nv_dload.ulSimNumEx > 0)&&(NV_CTRL_FILE_MAGIC_NUM != nv_dload.ulSimNumEx);
	/*lint -restore +e838*/
    if(multi_card)
    {
    	/*lint -save -e838*/
        other_card_info = (STRU_XNV_MAP_FILE_INFO *)nv_malloc((u32)(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO)));
        g_boot_file_info.other_card_info = (STRU_XNV_MAP_FILE_INFO *)nv_malloc((u32)(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO)));
        if((!other_card_info)||(!g_boot_file_info.other_card_info))
        {
            if(!other_card_info)
            {
                nv_free(other_card_info);
                other_card_info = NULL;
            }
            if(!g_boot_file_info.other_card_info)
            {
                nv_free(g_boot_file_info.other_card_info);
                g_boot_file_info.other_card_info = NULL;
            }
            printf("%s :malloc fail\n",__func__);
            return BSP_ERR_NV_MALLOC_FAIL;
        }

        ret = g_file_func_table.file_read((char*)NV_DLOAD_SEC_NAME, (u32)sizeof(nv_dload), other_card_info, \
            (u32)(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO)), NULL);;
        if(ret)
        {
            printf("%s :read nvdload error! ret = 0x%x\n",__func__,ret);
            nv_fastboot_debug(__LINE__,ret,0,0);
            return ret;
        }
    	/*lint -restore +e838*/
    }

	/*lint -save -e838*/
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
	/*lint -restore +e838*/
    if(multi_card)
    {
        for(i = 0;(i < nv_dload.ulSimNumEx); i++)
        {
			/*lint -save -e668 -e613*/
            total_len += ((other_card_info[i].stXnvFile.magic_num == NV_FILE_EXIST)?other_card_info[i].stXnvFile.len:0);
            total_len += ((other_card_info[i].stCustFile.magic_num == NV_FILE_EXIST)?other_card_info[i].stCustFile.len:0);
            total_len += ((other_card_info[i].stMapFile.magic_num == NV_FILE_EXIST)?other_card_info[i].stMapFile.len:0);
			/*lint -restore +e668 +e613*/
        }
    }
    ret = nv_count_file_sec_info((const s8*)NV_DLOAD_SEC_NAME,total_len,g_sec_info.nv_dload);
    if(ret)
    {
        /*lint -save -e838*/
        printf("[%s] ret : 0x%x\n",__func__,ret);
        if(!other_card_info){nv_free(other_card_info); other_card_info = NULL;}
        if(!g_boot_file_info.other_card_info){nv_free(g_boot_file_info.other_card_info); g_boot_file_info.other_card_info = NULL;}
        /*lint -restore +e838*/
        return NV_ERROR;
    }

    memcpy(&g_boot_file_info.nv_dload, &nv_dload, (u32)sizeof(nv_dload));
    if(multi_card)
    {
		/*lint -save -e668*/
        memcpy(g_boot_file_info.other_card_info, other_card_info, (u32)(nv_dload.ulSimNumEx * sizeof(STRU_XNV_MAP_FILE_INFO)));
		/*lint -restore +e668*/
        nv_free(other_card_info);
    }
	/*lint -save -e438*/
    return NV_OK;
	/*lint -restore +e438*/

}

/*lint -save -e18*/
u32 nv_boot_sec_file_info_init(const s8* name,struct nv_file_info_stru* sec_info, u32* off_info)
{
    u32 ret = NV_ERROR;
    u32 file_len = 0;
    struct nv_file_info_stru info;
    struct nv_ctrl_file_info_stru ctrl_info;
    u8* file_info;

/*lint -save -e838*/
    /*first: read nv ctrl file*/
    ret = (u32)g_file_func_table.file_read((char*)name,0,&ctrl_info,(u32)sizeof(ctrl_info),NULL);
    if(NAND_OK != ret)
    {
        printf("[%s]:patrition name %s,get file magic fail ret 0x%x,\n",__FUNCTION__,name,ret);
        return ret;
    }
/*lint -restore +e838*/
    /*second :check magic num in file head*/
    /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        printf("[%s]:enter this way  1111! %s\n",__FUNCTION__,name);
        return NV_OK;
    }

    /*third: read all nv ctrl file*/
    /* coverity[uninit_use] */
    file_info = (u8*)nv_malloc(ctrl_info.file_size+1);
    if(NULL == file_info)
    {
        printf("[%s]:enter this way  2222!\n",__FUNCTION__);
        return BSP_ERR_NV_MALLOC_FAIL;
    }
    ret = (u32)g_file_func_table.file_read((char*)name,(u32)sizeof(struct nv_ctrl_file_info_stru),file_info,ctrl_info.file_size,NULL);
    if(NAND_OK != ret)
    {
        printf("[%s]:enter this way 3333!\n",__FUNCTION__);
/*lint -save -e801*/
        goto init_end;
/*lint -restore +e801*/
    }

    /*fourth: count nv file len base the ctrl file info*/
    /* coverity[uninit_use_in_call] */
    ret = nv_boot_get_flash_file_len(&ctrl_info,(struct nv_file_list_info_stru*)(unsigned long)file_info,&file_len);
    if(ret)
    {
        printf("[%s]:enter this way 4444!\n",__FUNCTION__);
/*lint -save -e801*/
        goto init_end;
/*lint -restore +e801*/
    }

    /*forth: count nv file good block offset in the sec*/
    ret = nv_count_file_sec_info(name,file_len,off_info);
    if(ret)
    {
        printf("[%s]:enter this way 5555! %s\n",__func__,name);
/*lint -save -e801*/
        goto init_end;
/*lint -restore +e801*/
    }


    info.len       = file_len;
    info.magic_num = NV_FILE_EXIST;
    info.off       = 0;


    memcpy(sec_info,&info,(u32)sizeof(info));
init_end:
/*lint -save -e537 -e438*/
    nv_free(file_info);
    return NV_OK;
/*lint -restore +e537 +e438*/

}
/*lint -restore*/

u32 nv_boot_get_sys_info(const s8* mode,u32* offset,u32* len)
{
    s32 ret = strcmp((char *)NV_FILE_READ, (char *)mode);
    nv_check_file_mode(mode);
    if(B_READ  == ret)
    {
        if(g_boot_file_info.sys_nv.magic_num == NV_FILE_EXIST)
        {
            *offset = g_boot_file_info.sys_nv.off;
            *len    = g_boot_file_info.sys_nv.len;
            return NV_OK;
        }
        return NV_ERROR;
    }
    else
    {
        *offset = g_boot_file_info.sys_nv.off;
        *len    = g_boot_file_info.sys_nv.len;
        return NV_OK;
    }

}
u32 nv_boot_get_nvdload_file_info(u32* offset,u32* len)
{
    if(g_boot_file_info.nv_dload.nv_bin.magic_num == NV_FILE_EXIST)
    {
        *offset = g_boot_file_info.nv_dload.nv_bin.off;
        *len    = g_boot_file_info.nv_dload.nv_bin.len;
        return NV_OK;
    }
    else
    {
        return NV_ERROR;
    }
}

u32 nv_boot_get_bak_file_info(const s8* mode,u32* offset,u32* len)
{
    s32 ret = strcmp((char *)NV_FILE_READ, (char *)mode);

    nv_check_file_mode(mode);

    if(B_READ  == ret)
    {
        if(g_boot_file_info.bak_info.magic_num!= NV_FILE_EXIST)
        {
            return NV_ERROR;
        }
        *offset = g_boot_file_info.bak_info.off;
        *len    = g_boot_file_info.bak_info.len;
        return NV_OK;
    }
    else
    {
        *offset = g_boot_file_info.bak_info.off;
        *len    = g_boot_file_info.bak_info.len;
        return NV_OK;
    }

}

u32 nv_boot_get_xnv_info(u32 card_type,u32* offset,u32* len)
{
    if(card_type <= NV_USIMM_CARD_2)
    {
        if(g_boot_file_info.nv_dload.xnv_xml[card_type-1].magic_num == NV_FILE_EXIST)
        {
            *offset = g_boot_file_info.nv_dload.xnv_xml[card_type-1].off;
            *len    = g_boot_file_info.nv_dload.xnv_xml[card_type-1].len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }

    }
    else
    {
        if((g_boot_file_info.other_card_info[card_type-3].stXnvFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_boot_file_info.other_card_info[card_type-3].stXnvFile.off;
            *len    = g_boot_file_info.other_card_info[card_type-3].stXnvFile.len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }

}
u32 nv_boot_get_xnv_map_info(u32 card_type,u32* offset,u32* len)
{
    if(card_type <= NV_USIMM_CARD_2)
    {
        if(g_boot_file_info.nv_dload.xnv_map[card_type-1].magic_num == NV_FILE_EXIST)
        {
            *offset = g_boot_file_info.nv_dload.xnv_map[card_type-1].off;
            *len    = g_boot_file_info.nv_dload.xnv_map[card_type-1].len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }
    else
    {
        if((g_boot_file_info.other_card_info[card_type-3].stMapFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_boot_file_info.other_card_info[card_type-3].stMapFile.off;
            *len    = g_boot_file_info.other_card_info[card_type-3].stMapFile.len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }
}
u32 nv_boot_get_cust_info(u32 card_type,u32* offset,u32* len)
{
    if(card_type <= NV_USIMM_CARD_2)
    {
        if(g_boot_file_info.nv_dload.cust_xml[card_type-1].magic_num== NV_FILE_EXIST)
        {
            *offset = g_boot_file_info.nv_dload.cust_xml[card_type-1].off;
            *len    = g_boot_file_info.nv_dload.cust_xml[card_type-1].len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }

    }
    else
    {
        if((g_boot_file_info.other_card_info[card_type-3].stCustFile.magic_num == NV_FILE_EXIST)&&(NV_SUPPORT_MULTI_CARD))
        {
            *offset = g_boot_file_info.other_card_info[card_type-3].stCustFile.off;
            *len    = g_boot_file_info.other_card_info[card_type-3].stCustFile.len;
            return NV_OK;
        }
        else
        {
            return NV_ERROR;
        }
    }
}

/***************************************************************************
 函 数 名: nv_get_real_offset
 功能描述: 一个分区中逻辑地址到实际地址的转换(跳过坏块)
 输入参数:  partition_name:分区名称, blk_size:flash块大小
            part_size:flash分区大小, offset:分区中的偏移地址

 输出参数: 需要跳过的blk
 返 回 值: 0:
 注意事项: 由nand驱动检测当前要操作的块，这里只检测之前的坏块情况,
****************************************************************************/
unsigned int nv_get_real_offset( const char *partition_name, unsigned int blk_size,
    unsigned int part_size, unsigned int partition_offset )
{
    int ret_val = 0;
    unsigned int idx = 0;
    unsigned int invlv_blk_num = 0, total_blk_num = 0;
    unsigned int ret_num = 0;
    unsigned int tmp_offset = 0;

    /*当分区大小为零,或者需要检查的块为0时,直接返回*/
    if ( ( 0 == blk_size ) || ( 0 == part_size ) || ( partition_offset < blk_size ) )
    {
        printf( "fastboot: dload nv blk or part size or invlv_blk_num is 0!\n" );
/*lint -save -e801*/
        goto ret_err;
/*lint -restore +e801*/
    }

    /*total_blk_num和invlv_blk_num至少为1*/
    total_blk_num = part_size / blk_size;
    invlv_blk_num = partition_offset / blk_size;

    printf( "fastboot: dload nv invlv_blk_num:%d, total_blk_num:%d!\n",
        (int)invlv_blk_num, (int)total_blk_num );

    for ( idx = 0; idx < total_blk_num /*-1?*/; idx++ )
    {
        tmp_offset = idx * blk_size;
/*lint -save -e713*/
        ret_val = g_file_func_table.file_is_bad( partition_name, tmp_offset );
/*lint -restore +e713*/
        if ( 1 == ret_val )
        {
            printf( "fastboot: dload nv skip bad blk, idx:%d!\n", (int)idx );
            ret_num += 1;
        }
        else if ( 0 == --invlv_blk_num ) /*找到好块*/
        {
            break;
        }
    }

    /*整个分区都没有找到好块的情况不用判断,nand驱动会处理*/

ret_err:
    printf( "fastboot: dload nv skip total bad blk:%d!\n", ret_num );
    return ret_num;
}


u32 nv_file_init(void)
{
    u32 ret = NV_ERROR;
    struct nand_spec  nand_info;
#if defined(FEATURE_NV_FLASH_ON)
    unsigned int nv_tail_magic = 0;
    unsigned int real_offset = 0, skip_blk_num = 0;
    unsigned int nv_dlaod_part_size = 0;
#endif
    memset(&g_boot_file_info,0, (u32)sizeof(struct nv_flash_global_ctrl_stru));
/*lint -save -e838*/
    /*get nand info*/
    ret = (u32)g_file_func_table.file_get_info(&nand_info);
/*lint -restore +e838*/
    if(ret != NAND_OK)
    {
        nv_fastboot_debug(__LINE__,ret,\
            nand_info.blocksize,nand_info.pagesize);
/*lint -save -e801*/
        goto nv_flash_init_err;
/*lint -restore +e801*/
    }
    memcpy(&(g_boot_file_info.nand_info),&nand_info, (u32)sizeof(nand_info));
    /*get dload info*/
    ret = nv_boot_dload_info_init();
    if(ret)
    {
        printf("[%s]:get dload nv info fail need to check file this sec!\n",__FUNCTION__);
    }


    /*get bak info*/
    ret = nv_boot_sec_file_info_init((const s8*)g_boot_nv_file[NV_FILE_BACKUP].name,&g_boot_file_info.bak_info, g_sec_info.nv_bak);
    if(ret)
    {
        printf("[%s]:get bak info fail need to check file this sec!\n",__FUNCTION__);
    }
    /*get img info*/
    ret = nv_boot_sec_file_info_init((const s8*)g_boot_nv_file[NV_FILE_SYS_NV].name, &g_boot_file_info.sys_nv, g_sec_info.sys_nv);
    if(ret)
    {
        printf("[%s]:get sys nv info fail need to check file this sec!\n",__FUNCTION__);
    }
#if defined(FEATURE_NV_FLASH_ON)
    if ( NV_FILE_EXIST == g_boot_file_info.sys_nv.magic_num )
    {
        /*获取g_boot_nv_file[NV_FILE_SYS_NV].name分区size*/
        nv_dlaod_part_size = bsp_get_part_cap((char *)g_boot_nv_file[NV_FILE_SYS_NV].name );

        /*跳过要操作地址之前的坏块*/
        skip_blk_num = nv_get_real_offset( (char *)g_boot_nv_file[NV_FILE_SYS_NV].name,
            nand_info.blocksize, nv_dlaod_part_size, g_boot_file_info.sys_nv.len );

        real_offset = skip_blk_num * nand_info.blocksize;
        real_offset += g_boot_file_info.sys_nv.len;

        /*判断nv dload分区末尾的魔数字是否有效*/
        (void)bsp_nand_read( (char *)g_boot_nv_file[NV_FILE_SYS_NV].name, real_offset,
            (void *)&nv_tail_magic, sizeof(nv_tail_magic), NULL );
        if( NV_FILE_TAIL_MAGIC_NUM != nv_tail_magic )
        {
            printf( "fastboot: dload nv part not valid: 0x%x!\n", nv_tail_magic );

            /*清除nv dload分区有效标志(将会尝试从nvbackup分区获取)*/
            g_boot_file_info.sys_nv.magic_num = 0;
        }
    }
    else
    {
        printf("fastboot: dload nv part not check for pre_err!\n" );
    }
#endif
    return NV_OK;
nv_flash_init_err:
    printf("ret :0x%x\n",ret);
    return ret;
}





FILE* nv_file_open(const s8* path,const s8* mode)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    struct nv_flash_file_header_stru* ffp = NULL;
    u32 offset = 0;
    u32 len = 0;
/*lint -save -e838*/
    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp((char *)path, (char *)g_boot_nv_file[i].path))
        {
            ffp = &g_boot_nv_file[i];
            break;
        }
    }
/*lint -restore +e838*/
    if(NULL == ffp)
    {
        return NULL;
    }
    switch(ffp->flash_type)
    {
        case NV_FILE_DLOAD:
            ret = nv_boot_get_nvdload_file_info(&offset,&len);
            break;
        case NV_FILE_BACKUP:
            ret = nv_boot_get_bak_file_info(mode,&offset,&len);
            break;
        case NV_FILE_XNV_CARD_1:
            ret = nv_boot_get_xnv_info(NV_USIMM_CARD_1,&offset,&len);
            break;
        case NV_FILE_CUST_CARD_1:
            ret = nv_boot_get_cust_info(NV_USIMM_CARD_1,&offset,&len);
            break;
        case NV_FILE_XNV_CARD_2:
            ret = nv_boot_get_xnv_info(NV_USIMM_CARD_2,&offset,&len);
            break;
        case NV_FILE_CUST_CARD_2:
            ret = nv_boot_get_cust_info(NV_USIMM_CARD_2,&offset,&len);
            break;
        case NV_FILE_SYS_NV:
            ret = nv_boot_get_sys_info((const s8*)mode,&offset,&len);
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            ret = nv_boot_get_xnv_map_info(NV_USIMM_CARD_1,&offset,&len);
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            ret = nv_boot_get_xnv_map_info(NV_USIMM_CARD_2,&offset,&len);
            break;
        case NV_FILE_XNV_CARD_3:
            ret = nv_boot_get_xnv_info(NV_USIMM_CARD_3,&offset,&len);
            break;
        case NV_FILE_CUST_CARD_3:
            ret = nv_boot_get_cust_info(NV_USIMM_CARD_3,&offset,&len);
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            ret = nv_boot_get_xnv_map_info(NV_USIMM_CARD_3,&offset,&len);
            break;
        default:
            ret = BSP_ERR_NV_INVALID_PARAM;
            break;
    }

    if(NV_OK != ret)
    {
        return NULL;
    }

    ffp->ops ++;
    ffp->seek   = 0;
    ffp->length = len;
    ffp->off    = offset;
    ffp->fp     = ffp;

    return ffp;
}
 
s32 nv_file_read(u8* ptr, u32 size, u32 count, FILE* fp)
{
    u32 real_size = 0;
    s32 ret = -1;
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;
    u32 len = size*count;
    u32 virt_offset = 0;
    u32 phy_offset = 0;

    if((NULL == ffp)||(ffp->fp != ffp)||(ffp->ops == 0))
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }
/*lint -save -e838 -e713*/
    real_size = ((ffp->seek+len) < ffp->length)? len: (ffp->length - ffp->seek );

    virt_offset = ffp->off+ffp->seek;

    ret = nv_sec_off_count(ffp, virt_offset,&phy_offset);
    if(ret)
    {
        printf("[%s]:%d ret 0x%x\n",__FUNCTION__,__LINE__,ret);

    }
    ret = g_file_func_table.file_read((char*)ffp->name, phy_offset, ptr,real_size,NULL);/*注意文件偏移*/
    if(ret != NAND_OK)
    {
        printf("%x  0x%x\n",ffp->seek,ffp->length);
        printf("%s  0x%x 0x%x \n",ffp->name,phy_offset,real_size);
        printf("[%s]:%d ret 0x%x\n",__FUNCTION__,__LINE__,ret);
        return -1;
    }
/*lint -restore +e838 +e713*/
    ffp->seek += real_size;
    return (s32)real_size;
}
 
s32 nv_file_seek(FILE* fp,s32 offset,s32 whence)
{

    u32 ret = 0;
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;
    if((NULL == ffp)||(ffp->fp != ffp)||(ffp->ops == 0))
    {
/*lint -save -e801*/
        goto out;
/*lint -restore +e801*/
    }
    ret = ffp->seek;
    switch(whence)
    {
        case SEEK_SET:
            ret = (u32)offset;
            break;
        case SEEK_CUR:
            ret += (u32)offset;
            break;
        case SEEK_END:
            ret = ffp->length + (u32)offset;
            break;
        default:
/*lint -save -e801*/
            goto out;
/*lint -restore +e801*/
    }
    if(ret > ffp->length)
    {
        return -1;
    }

    ffp->seek = (u32)ret;
    return NV_OK;
out:
    return -1;
}

s32 nv_file_close(FILE* fp)
{
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;

    if((NULL == ffp)||(ffp->fp != ffp)||(ffp->ops == 0))
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }

    ffp->fp = NULL;
    ffp->seek = 0;
    ffp->length = 0;
    ffp->off = 0;
    ffp->ops --;
    if(ffp->ops != 0)
    {
        return -1;
    }
    return NV_OK;
}

s32 nv_file_ftell(FILE* fp)
{
    struct nv_flash_file_header_stru* ffp = (struct nv_flash_file_header_stru*)fp;

    if((NULL == ffp)||(ffp->fp != ffp)||(ffp->ops == 0))
    {
        return -1;
    }
    return (s32)(ffp->seek);
}

s32 nv_file_access(const s8* path,s32 mode)
{
    u32 ret = NV_ERROR;
    u32 i = 0;
    struct nv_flash_file_header_stru* fd = NULL;

/*lint -save -e838*/
    for(i=0; i<NV_FILE_BUTT; i++)
    {
        if(0 == strcmp((char *)path, (char *)g_boot_nv_file[i].path))
        {
            fd = &g_boot_nv_file[i];
            break;
        }
    }
/*lint -restore +e838*/
    if(NULL == fd)
    {
        return -1;
    }
    mode = mode;
    switch(fd->flash_type)
    {
        case NV_FILE_DLOAD:
            ret = (g_boot_file_info.nv_dload.nv_bin.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_BACKUP:
            ret = (g_boot_file_info.bak_info.magic_num== NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_1:
            ret = (g_boot_file_info.nv_dload.xnv_xml[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_2:
            ret = (g_boot_file_info.nv_dload.xnv_xml[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_boot_file_info.other_card_info[0].stXnvFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        case NV_FILE_CUST_CARD_1:
            ret = (g_boot_file_info.nv_dload.cust_xml[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_CUST_CARD_2:
            ret = (g_boot_file_info.nv_dload.cust_xml[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_CUST_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_boot_file_info.other_card_info[0].stCustFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            }
            break;
        case NV_FILE_SYS_NV:
            ret = (g_boot_file_info.sys_nv.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_1:
            ret = (g_boot_file_info.nv_dload.xnv_map[0].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_2:
            ret = (g_boot_file_info.nv_dload.xnv_map[1].magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
            break;
        case NV_FILE_XNV_MAP_CARD_3:
            if(NV_SUPPORT_MULTI_CARD)
            {
                ret = (g_boot_file_info.other_card_info[0].stMapFile.magic_num == NV_FILE_EXIST)?NV_FILE_EXIST:0;
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
/*flash part end*/
/**************************************************************/
/*
 * pick up the base info from the major info,then reg in base_info
 */
u32 nv_boot_init_file_info(u8* major_info,u8* base_info)
{
    u32 i;
    u32 ret;
    struct nv_ctrl_file_info_stru * ctrl_file = (struct nv_ctrl_file_info_stru*)(unsigned long)major_info;
    struct nv_global_ddr_info_stru* ddr_info  = (struct nv_global_ddr_info_stru*)(unsigned long)base_info;
    struct nv_file_list_info_stru * file_info = (struct nv_file_list_info_stru *)((unsigned long)ctrl_file+NV_GLOBAL_CTRL_INFO_SIZE);

    ddr_info->file_num = ctrl_file->file_num;   /*reg file num*/
    ddr_info->file_len = ctrl_file->ctrl_size;  /*reg ctrl file size,then add file size*/

    for(i = 0;i<ctrl_file->file_num;i++)
    {
        /*check file id*/
        if((i+1) != file_info->file_id)
        {
            ret = BSP_ERR_NV_FILE_ERROR;
            nv_fastboot_debug(__LINE__,ret,i,file_info->file_id);
            return ret;
        }
        ddr_info->file_info[i].file_id = file_info->file_id;
        ddr_info->file_info[i].size    = file_info->file_size;
        ddr_info->file_info[i].offset  = ddr_info->file_len;

        ddr_info->file_len            += file_info->file_size;

        file_info++;
    }
    if(ddr_info->file_len > NV_MAX_FILE_SIZE)
    {
        ret = BSP_ERR_NV_FILE_ERROR;
        nv_fastboot_debug(__LINE__,ret,0,ddr_info->file_len);
        return ret;
    }
    return NV_OK;
}

bool nv_boot_dload_file_check(void )
{
    u32 i;
/*lint -save -e835 -e647*/
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_file_list_info_stru* file_info = (struct nv_file_list_info_stru*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE);
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);
    struct nv_ref_data_info_stru* ref_info_next = ref_info+1;
/*lint -restore -e835 +e647*/

    /*check ref list id sort */
    for(i = 0;i<ctrl_info->ref_count-1;i++)
    {
        if(ref_info->itemid >=ref_info_next->itemid)
        {
            nv_fastboot_debug(__LINE__,i,ref_info->itemid,ref_info_next->itemid);
            return FALSE;
        }
        ref_info ++;
        ref_info_next ++;
    }

    /*check file id sort*/
    for(i = 0;i<ctrl_info->file_num;i++)
    {
        if(file_info->file_id != (i+1))
        {
            nv_fastboot_debug(__LINE__,i,file_info->file_id,0);
            return FALSE;
        }
        file_info ++;
    }
    return TRUE;
}

/*
 * get file len
 * return : file len
 */
u32 nv_boot_get_file_len(FILE* fp)
{
    s32 ret = -1;
    u32 seek = 0;

/*lint -save -e801 -e838*/

    ret = nv_file_seek(fp,0,SEEK_END);
    if(ret)
    {
        goto out;
    }
/*lint -restore +e801 +e838*/
    seek = (u32)nv_file_ftell(fp);

    ret = nv_file_seek(fp,0,SEEK_SET);
    if(ret)
    {
	    /*lint -save -e801*/
        goto out;
		/*lint -restore +e801*/

    }

    return seek;

out:
    printf("[%s]:ret 0x%x\n",__FUNCTION__,ret);
    return NV_ERROR;
}

/*
 * search nv info by nv id
 * &pdata:  data start ddr
 * output: ref_info,file_info
 */
u32 nv_boot_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info)
{
    u32 low;
    u32 high;
    u32 mid;
    u32 offset;
	/*lint -save -e826*/
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)pdata;
	/*lint -restore +e826*/

    high = ctrl_info->ref_count;
    low  = 1;
    while(low <= high)
    {
        mid = (low+high)/2;

        offset = (u32)NV_GLOBAL_CTRL_INFO_SIZE + (u32)NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num + (u32)((mid -1)*NV_REF_LIST_ITEM_SIZE);
        memcpy((u8*)ref_info,(u8*)ctrl_info + offset,(u32)NV_REF_LIST_ITEM_SIZE);
        if(itemid < ref_info->itemid)
        {
            high = mid-1;
        }
        else if(itemid > ref_info->itemid)
        {
            low = mid+1;
        }
        else
        {
            offset = NV_GLOBAL_CTRL_INFO_SIZE + NV_GLOBAL_FILE_ELEMENT_SIZE*(ref_info->file_id -1);
            memcpy((u8*)file_info,(u8*)ctrl_info+offset,(u32)NV_GLOBAL_FILE_ELEMENT_SIZE);
            return NV_OK;
        }
    }
    return BSP_ERR_NV_NO_THIS_ID;

}
/*
 * copy user buff to global ddr,used to write nv data to ddr
 * &file_id :file id
 * &offset:  offset of global file ddr
 */
u32 nv_boot_write_to_mem(const u8* pdata,u32 size,u32 file_id,u32 offset)
{
	/*lint -save -e835*/
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)(unsigned long)NV_GLOBAL_INFO_ADDR;
	/*lint -restore*/
    if(offset > ddr_info->file_info[file_id-1].size)
    {
        printf("[%s]:offset 0x%x\n",__FUNCTION__,offset);
        return BSP_ERR_NV_FILE_ERROR;
    }
	/*lint -save -e124 -e732 -e835*/
    memcpy((u8*)(NV_GLOBAL_CTRL_INFO_ADDR+ddr_info->file_info[file_id-1].offset + offset),pdata,(s32)size);
	/*lint -restore*/
    return NV_OK;
}

u32 nv_boot_read_from_mem(u8* pdata,u32 size,u32 file_id,u32 offset)
{
	/*lint -save -e835*/
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)(unsigned long)NV_GLOBAL_INFO_ADDR;
	/*lint -restore*/
    if(offset > ddr_info->file_info[file_id-1].size)
    {
        printf("[%s]:offset 0x%x\n",__FUNCTION__,offset);
        return BSP_ERR_NV_FILE_ERROR;
    }
	/*lint -save -e835*/
    memcpy(pdata,(u8*)((unsigned long)NV_GLOBAL_CTRL_INFO_ADDR +ddr_info->file_info[file_id-1].offset + offset),size);
	/*lint -restore*/

    return NV_OK;
}
/*
 * read file to ddr,include download,backup,workaround,default
 */

u32 nv_boot_read_from_flash(FILE* fp,u8* ptr,u32* datalen)
{
    u32 ret = NV_ERROR;
/*lint -save -e835*/
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)(unsigned long)NV_GLOBAL_INFO_ADDR;
/*lint -restore +e835*/

/*lint -save -e801*/
    *datalen = nv_boot_get_file_len(fp);
    if(*datalen == 0)
    {
        printf("nv file size==0 \n");
        ret = BSP_ERR_NV_FILE_ERROR;
        goto out;
    }
    if(*datalen > NV_MAX_FILE_SIZE)
    {
        printf("nv file size:0x%x is larger than ddr size 0x%x\n", *datalen, NV_MAX_FILE_SIZE);
        ret = BSP_ERR_NV_FILE_ERROR;
        goto out;
    }

    ret = (u32)nv_file_read((u8*)ptr,1,(*datalen),fp);
    if(ret != (*datalen))
    {
        goto out;
    }
	/*lint -save -e835*/
    ret = nv_boot_init_file_info((u8*)NV_GLOBAL_CTRL_INFO_ADDR,(u8*)NV_GLOBAL_INFO_ADDR);
    if(ret)
    {
        goto out;
    }
	/*lint -restore +e835*/
    if(*datalen != ddr_info->file_len)
    {
        nv_fastboot_debug(__LINE__,ddr_info->file_len,*datalen,0);
        ret = BSP_ERR_NV_FILE_ERROR;
        goto out;
    }
/*lint -restore +e801*/
    return NV_OK;
out:
    printf("[%s]:ret 0x%x\n",__FUNCTION__,ret);
    return NV_ERROR;
}
/*lint -save -e14*/
u32 nv_readEx(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    u32 ret = NV_ERROR;
    struct nv_file_list_info_stru file_info;
    struct nv_ref_data_info_stru  ref_info;

    if((NULL == pdata)||(0 == datalen))
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }
	/*lint -save -e835 -e838*/
    ret = nv_boot_search_byid(itemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&ref_info,&file_info);
    if(ret)
    {
        printf("\n[%s]:can not find 0x%x !\n",__FUNCTION__,itemid);
        return BSP_ERR_NV_NO_THIS_ID;
    }
	/*lint -restore +e835 -e838*/
	/*lint -save -e801*/
    if((offset + datalen) > ref_info.nv_len)
    {
        nv_fastboot_debug(__LINE__,itemid,offset,datalen);
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        goto nv_readEx_err;
    }
    if(modem_id <= ref_info.modem_num)
    {
        ref_info.nv_off += (modem_id - NV_USIMM_CARD_1)*ref_info.nv_len;
    }
    else
    {
        nv_fastboot_debug(__LINE__,itemid,0,0);
        ret = BSP_ERR_NV_INVALID_PARAM;
        goto nv_readEx_err;
    }

    ret = nv_boot_read_from_mem(pdata, datalen,file_info.file_id,(ref_info.nv_off+offset));
    if(ret)
    {
        nv_fastboot_debug(__LINE__,itemid,0,0);
        goto nv_readEx_err;
    }
	/*lint -restore +e801*/
    return NV_OK;
nv_readEx_err:
    printf("\n[%s]:[0x%x]:[%d]\n",__FUNCTION__,itemid,modem_id);
    return ret;
}
u32 bsp_nvm_dcread(u32 modem_id, u32 itemid, u8 * pdata, u32 datalen)
{
    if(!g_nvInitFlag)
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }
    return nv_readEx(modem_id,itemid,0,pdata,datalen);
}
u32 nv_boot_xml_decode(s8* path,s8* map_path,u32 card_type)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;

    cprintf("Decode %s start !\n",path);
	/*lint -save -e838*/
    fp = nv_file_open(path,(s8*)NV_FILE_READ);
    if(!fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        return ret;
    }
    ret = xml_decode_main(fp,map_path,card_type);
    nv_file_close(fp);
    if(ret)
        return ret;
	/*lint -restore +e838*/
    return NV_OK;
}


void nv_xml_decode(void)
{
    u32 ret = NV_ERROR;
	/*lint -save -e835*/
    struct nv_global_ddr_info_stru *ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
	/*lint -restore +e835*/

    cprintf("modem xnv xml is decoding,waiting for a moment ....\n");

    if(!nv_file_access((const s8*)NV_XNV_CARD1_PATH,0))
    {
        ret = nv_boot_xml_decode((s8*)NV_XNV_CARD1_PATH, (s8*)NV_XNV_CARD1_MAP_PATH, NV_USIMM_CARD_1);
        if(ret)
        {
            return;
        }
    }

    if(!nv_file_access((const s8*)NV_XNV_CARD2_PATH,0))
    {
        ret = nv_boot_xml_decode((s8*)NV_XNV_CARD2_PATH, (s8*)NV_XNV_CARD2_MAP_PATH,NV_USIMM_CARD_2);
        if(ret)
        {
            return;
        }
    }

    if(!nv_file_access((const s8*)NV_XNV_CARD3_PATH,0))
    {
        ret = nv_boot_xml_decode((s8*)NV_XNV_CARD3_PATH, (s8*)NV_XNV_CARD3_MAP_PATH,NV_USIMM_CARD_3);
        if(ret)
        {
            return;
        }
    }

    /*CUST XML 无对应MAP文件，传入空值即可*/
    if(!nv_file_access((const s8*)NV_CUST_CARD1_PATH,0))
    {
        ret = nv_boot_xml_decode((s8*)NV_CUST_CARD1_PATH,NULL,NV_USIMM_CARD_1);
        if(ret)
        {
            return;
        }
    }

    if(!nv_file_access((const s8*)NV_CUST_CARD2_PATH,0))
    {
        ret = nv_boot_xml_decode((s8*)NV_CUST_CARD2_PATH,NULL,NV_USIMM_CARD_2);
        if(ret)
        {
            return;
        }
    }

    if(!nv_file_access((const s8*)NV_CUST_CARD3_PATH,0))
    {
        ret = nv_boot_xml_decode((s8*)NV_CUST_CARD3_PATH,NULL,NV_USIMM_CARD_3);
        if(ret)
        {
            return;
        }
    }

    ddr_info->xml_dec_state = NV_XML_DEC_SUCC_STATE;
    return ;
}
/*lint -restore +e14*/
u32 nv_init(void)
{
    u32 ret = NV_ERROR;
    u32 datalen = 0;
    FILE* fp = NULL;
    u32 mem_type = 0;
	/*lint -save -e835*/
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    memset(ddr_info, 0, (u32)sizeof(struct nv_global_ddr_info_stru));
    g_boot_file_info.shared_addr = (struct nv_global_ddr_info_stru *)NV_GLOBAL_INFO_ADDR;
	/*lint -restore +e835*/
	/*lint -save -e838 -e801*/
    ret = nv_file_init();
    if(ret)
    {
        goto nv_boot_init_fail;
    }
	/*lint -restore +e838 +e801*/

    fp = nv_file_open((s8*)NV_DLOAD_PATH,(s8*)NV_FILE_READ);
    if(fp)
    {

    	/*lint -save -e835*/
        ret = nv_boot_read_from_flash(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen);
		/*lint -restore +e835*/
        nv_file_close(fp);
        fp = NULL;
        if(ret)
        {
            ret = BSP_ERR_NV_READ_FILE_FAIL;
	    	/*lint -save -e801*/
            goto nv_boot_init_fail;
			/*lint -restore +e801*/
        }

        if(FALSE == nv_boot_dload_file_check())
        {
            ret = BSP_ERR_NV_FILE_ERROR;
	    	/*lint -save -e801*/
            goto nv_boot_init_fail;
			/*lint -restore +e801*/
        }
        /*fastboot xml decode ,err case */
        nv_xml_decode();

        /*reg dload file in using*/
        mem_type = NV_MEM_DLOAD;
    }
    else
    {
        fp = nv_file_open((s8*)NV_FILE_SYS_NV_PATH,(s8*)NV_FILE_READ);
        if(NULL == fp)
        {
            printf("open  %s fail!\n", NV_FILE_SYS_NV_PATH);
            fp= nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_READ);
            if(NULL == fp)
            {
                nv_fastboot_debug(__LINE__,ret,0,0);
		    	/*lint -save -e801*/
                goto nv_boot_init_fail;
				/*lint -restore +e801*/
            }
            else
            {
                mem_type = NV_MEM_BACKUP;   /**/
            }
        }
        else
        {
            mem_type = NV_MEM_SYSTEM;
        }
		/*lint -save -e835*/
        ret = nv_boot_read_from_flash(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen);
		/*lint -restore +e835*/
        nv_file_close(fp);
        fp = NULL;
        if(ret)
        {
            ret = BSP_ERR_NV_READ_FILE_FAIL;
			/*lint -save -e801*/
            goto nv_boot_init_fail;
			/*lint -restore +e801*/
        }
    }

    ddr_info->acore_init_state = NV_BOOT_INIT_OK;
    ddr_info->ccore_init_state = NV_BOOT_INIT_OK;
    ddr_info->mcore_init_state = NV_BOOT_INIT_OK;/*m3 core may to read*/
    ddr_info->mem_file_type    = mem_type;       /*reg mem file type*/
    g_nvInitFlag = 1;

    printf("nv boot init ok!\n");
    return NV_OK;
nv_boot_init_fail:
    printf("nv boot init err!\n");
	/*lint -save -e438*/
    return NV_ERROR;
	/*lint -restore +e438*/
}

/*lint -restore*/
u32 is_nvbin_burned(void)
{
    struct nv_dload_packet_head_stru nv_dload;
    u32 ret = 0;
	/*lint -save -e838*/
    ret = g_file_func_table.file_read((char*)NV_DLOAD_SEC_NAME,0, &nv_dload, (u32)sizeof(nv_dload),NULL);
	/*lint -restore +e838*/
    if(ret)
    {
        printf("%s :read nvdload error! ret = 0x%x\n",__func__,ret);
        return ret;
    }
    if( nv_dload.nv_bin.magic_num != NV_FILE_EXIST)
    {
        printf("dload file not exsit, nv_dload.nv_bin.magic_num = 0x%x\n", nv_dload.nv_bin.magic_num);
        return BSP_ERR_NV_NO_FILE;
    }
    else
    {
        return NV_OK;
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




