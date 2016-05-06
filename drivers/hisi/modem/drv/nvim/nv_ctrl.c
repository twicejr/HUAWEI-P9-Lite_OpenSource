

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e537*/
#include <ptable_com.h>
#include "mdrv_rfile_common.h"
#include <bsp_nandc.h>
#include <bsp_slice.h>
#include "nv_comm.h"
#include "nv_debug.h"
#include "nv_ctrl.h"
/*lint -restore +e537*/
/*lint -save -e958*/
struct file_ops_table_stru  g_nv_ops = {
#ifdef FEATURE_NV_FLASH_ON
    .fo = nv_flash_open,
    .fc = nv_flash_close,
    .frm= nv_flash_remove,
    .fr = nv_flash_read,
    .fw = nv_flash_write,
    .fs = nv_flash_seek,
    .ff = nv_flash_ftell,
    .fa = nv_flash_access,
    .fu = nv_flash_update_info,
#elif  defined(FEATURE_NV_LFILE_ON)
    .fo = nv_lfile_open,
    .fc = nv_lfile_close,
    .frm= nv_lfile_remove,
    .fr = nv_lfile_read,
    .fw = nv_lfile_write,
    .fs = nv_lfile_seek,
    .ff = nv_lfile_ftell,
    .fa = nv_lfile_access,
#elif  defined(FEATURE_NV_RFILE_ON)
    .fo = nv_rfile_open,
    .fc = nv_rfile_close,
    .frm= nv_rfile_remove,
    .fr = nv_rfile_read,
    .fw = nv_rfile_write,
    .fs = nv_rfile_seek,
    .fa = nv_lfile_access,
    .ff = nv_rfile_ftell,
    .fa = nv_rfile_access,
#elif  defined(FEATURE_NV_EMMC_ON)
    .fo = nv_emmc_open,
    .fc = nv_emmc_close,
    .frm= nv_emmc_remove,
    .fr = nv_emmc_read,
    .fw = nv_emmc_write,
    .fs = nv_emmc_seek,
    .ff = nv_emmc_ftell,
    .fa = nv_emmc_access,
    .fu = nv_emmc_update_info,
#endif
};

#ifdef CONFIG_MULTI_CARRIER
char sys_path[][32]={NV_FILE_SYS_NV_PATH,NV_BACK_PATH,NV_DLOAD_PATH,NV_XNV_CARD1_PATH,NV_XNV_CARD1_MAP_PATH,\
                    NV_XNV_CARD2_PATH,NV_XNV_CARD2_MAP_PATH, NV_XNV_CARD3_PATH,NV_XNV_CARD3_MAP_PATH,\
                    NV_CUST_CARD1_PATH,NV_CUST_CARD2_PATH, NV_CUST_CARD3_PATH, NV_DEFAULT_PATH};
#endif


/*
 * Function:    nv_file_init
 * Discription: global info init,flash: get mtd device
 */
u32 nv_file_init(void)
{
    u32 ret = NV_ERROR;

#ifdef FEATURE_NV_FLASH_ON
    ret = nv_flash_init();
    if(ret != NV_OK)
    {
        return ret;
    }

#elif  defined(FEATURE_NV_LFILE_ON)
#elif  defined(FEATURE_NV_RFILE_ON)
#elif  defined(FEATURE_NV_EMMC_ON)
    ret = nv_emmc_init();
    if(ret)
    {
        return ret;
    }
#endif
    return NV_OK;

}

/*
 * Function: nv_file_open
 * Discription: open file
 * Parameter:   path  :  file path
 *              mode  :  file ops type etc:"r+","rb+","w+","wb+"
 * Output   :   file pointer
 */
FILE* nv_file_open(const s8* path,const s8* mode)
{
    struct nv_file_p* fp = NULL;
#ifdef CONFIG_MULTI_CARRIER
    u32 i= 0;
#endif

    fp = (struct nv_file_p*)nv_malloc(sizeof(struct nv_file_p));
    if(!fp)
    {
        return NULL;
    }
#ifndef CONFIG_MULTI_CARRIER
    if(0 == strcmp((char*)path,(char*)NV_IMG_PATH))
    {
        fp->fd = mdrv_file_open((char*)path,(char*)mode);
        fp->stor_type = NV_FILE_STOR_FS;
    }
    else
    {
        fp->fd = g_nv_ops.fo(path,mode);
        fp->stor_type = NV_FILE_STOR_NON_FS;
    }

#else

#ifdef BSP_CONFIG_PHONE_TYPE
    if(0 == strcmp((char*)path,(char*)NV_IMG_PATH))
    {
        fp->fd = BSP_fopen((char*)path,(char*)mode);
        fp->stor_type = NV_FILE_STOR_FS;
    }
    else
    {
        fp->fd = g_nv_ops.fo(path,mode);
        fp->stor_type = NV_FILE_STOR_NON_FS;
    }
#else
    if(0 != strcmp((char*)path,(char*)NV_IMG_PATH))
    {
        fp->fd = g_nv_ops.fo(path,mode);
        fp->stor_type = NV_FILE_STOR_NON_FS;
    }
    else
    {
        for(i=0;i<10;i++)
        {
            if(0 == strcmp((char*)path,(char*)(sys_path[i])))
            {
                fp->fd = g_nv_ops.fo(path,mode);
                fp->stor_type = NV_FILE_STOR_NON_FS;
                break;
            }
        }

        if(i>=10)
        {
            fp->fd = mdrv_file_open((char*)path,(char*)mode);
            fp->stor_type = NV_FILE_STOR_FS;
        }

    }
#endif

#endif

    /* coverity[leaked_storage] */
    if(NULL == fp->fd)
    {
        /* coverity[leaked_storage] */
#ifdef CONFIG_MULTI_CARRIER
        printk("nv_file_open: here line:%x,i is 0x%d,path is %s\n",__LINE__,i,path);
#endif
        if(fp)nv_free((void *)fp);
        return NULL;
    }

    return fp;
}

 
s32 nv_file_read(u8* ptr,u32 size,u32 count,FILE* fp)
{
    struct nv_file_p* fd = (struct nv_file_p*)fp;

    if(fd->stor_type == NV_FILE_STOR_FS)
    {
        return mdrv_file_read(ptr,size,count, fd->fd);
    }
    else if(fd->stor_type == NV_FILE_STOR_NON_FS)
    {
        return g_nv_ops.fr(ptr,size,count,fd->fd);
    }
    else
    {
        return -1;
    }

}
 
s32 nv_file_write(u8* ptr,u32 size,u32 count,FILE* fp)
{
    struct nv_file_p* fd = (struct nv_file_p*)fp;
    u32 ret = 0;
    u32 start = 0;
    u32 end = 0;

    if(fd->stor_type == NV_FILE_STOR_FS)
    {
        start = bsp_get_slice_value();
        ret = mdrv_file_write_sync(ptr,size,count,fd->fd);
        end = bsp_get_slice_value();
        nv_debug_record_delta_time(NV_DEBUG_DELTA_WRITE_FILE, start, end);
        return ret;
    }
    else if(fd->stor_type == NV_FILE_STOR_NON_FS)
    {
        return g_nv_ops.fw(ptr,size,count,fd->fd);
    }
    else
    {
        return -1;
    }

}

 
s32 nv_file_seek(FILE* fp,s32 offset,s32 whence)
{
    struct nv_file_p* fd = (struct nv_file_p*)fp;

    if(fd->stor_type == NV_FILE_STOR_FS)
    {
        return mdrv_file_seek(fd->fd,(long)offset,(int)whence);
    }
    else if(fd->stor_type == NV_FILE_STOR_NON_FS)
    {
        return g_nv_ops.fs(fd->fd,offset,whence);
    }
    else
    {
        return -1;
    }

}


s32 nv_file_close(FILE* fp)
{
    struct nv_file_p* fd = (struct nv_file_p*)fp;
    s32 ret;


    if(fd->stor_type == NV_FILE_STOR_FS)
    {
        ret = mdrv_file_close(fd->fd);
    }
    else if(fd->stor_type == NV_FILE_STOR_NON_FS)
    {
        ret= g_nv_ops.fc(fd->fd);
    }
    else
    {
        return -1;
    }
    nv_free(fp);
    return ret;
}
 
s32 nv_file_remove(const s8* path)
{
    if(0 == strcmp((char*)path,(char*)NV_IMG_PATH))
    {
        return mdrv_file_remove((char*)path);
    }
    else
    {
        return g_nv_ops.frm(path);
    }
}

 
s32 nv_file_ftell(FILE* fp)
{
    struct nv_file_p* fd = (struct nv_file_p*)fp;
    if(fd->stor_type == NV_FILE_STOR_FS)
    {
        return mdrv_file_tell(fd->fd);
    }
    else if(fd->stor_type == NV_FILE_STOR_NON_FS)
    {
        return g_nv_ops.ff(fd->fd);
    }
    else
    {
        return -1;
    }
}



 /*
  * Function   : nv_file_access
  * Discription: check the file is exist?
  * Parameter  : fp:   file pointer
  * Output     :
  * return     : 0:表示有文件 其他没文件
  * History    : yuyangyang  00228784  create
  */
s32 nv_file_access(const s8* path,s32 mode)
{
#ifdef CONFIG_MULTI_CARRIER
    u32 i = 0;
#endif

#ifndef CONFIG_MULTI_CARRIER
    if(0 == strcmp((char*)path,(char*)NV_IMG_PATH))
    {
        return mdrv_file_access((char*)path,mode);
    }
    else
    {
        return g_nv_ops.fa(path,mode);
    }
#else

    for(i=0;i<10;i++)
    {
        if(0 == strcmp((char*)path,(char*)(sys_path[i])))
        {
            return g_nv_ops.fa(path,mode);
        }
    }
    return mdrv_file_access((char*)path,mode);

#endif
}

 /*
  * Function   : nv_file_update
  * Discription: update the file info?
  * Parameter  : fp:   file pointer
  * Output     :
  * return     : 0:刷新信息成功 其他失败
  * History    :
  */
s32 nv_file_update(const s8* path)
{

    if(0 == strcmp((char*)path,(char*)NV_IMG_PATH))
    {
        return NV_ERROR;
    }
    else
    {
        return g_nv_ops.fu(path);
    }
}

/*copy img to backup*/
#define NV_FILE_COPY_UNIT_SIZE      (16*1024)

u32 nv_copy_img2backup(void)
{
    u32 ret;
    FILE* fp = NULL;
    u32 total_len;
    u32 phy_off = 0;
    u32 unit_len;
    void* pdata = NULL;


    fp = mdrv_file_open((char*)NV_IMG_PATH,"rb");
    if(!fp)
    {
        return BSP_ERR_NV_NO_FILE;
    }

    mdrv_file_seek(fp,0,SEEK_END);
    total_len = (u32)mdrv_file_tell(fp);
    mdrv_file_seek(fp,0,SEEK_SET);

    pdata = (void*)nv_malloc(NV_FILE_COPY_UNIT_SIZE);
    if(!pdata)
    {
        mdrv_file_close(fp);
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    nv_create_flag_file((s8*)NV_BACK_FLAG_PATH);
    while(total_len)
    {
        unit_len = (total_len >= NV_FILE_COPY_UNIT_SIZE)?NV_FILE_COPY_UNIT_SIZE : total_len;

        ret = (u32)mdrv_file_read(pdata,1,unit_len,fp);
        if(ret != unit_len)
        {
            nv_free(pdata);
            mdrv_file_close(fp);
            return BSP_ERR_NV_READ_FILE_FAIL;
        }

        ret = (u32)bsp_nand_write((char*)NV_BACK_SEC_NAME,phy_off,pdata,unit_len);
        if(ret)
        {
            nv_free(pdata);
            mdrv_file_close(fp);
            return BSP_ERR_NV_WRITE_FILE_FAIL;
        }

        phy_off += unit_len;
        total_len -= unit_len;
    }

    nv_free(pdata);
    mdrv_file_close(fp);
    nv_delete_flag_file((s8*)NV_BACK_FLAG_PATH);

    return NV_OK;

}


/*修改升级包标志
 *true :有效   false :无效
 */

s32 nv_modify_upgrade_flag(bool flag)
{
#if (FEATURE_NV_PARTRION_MULTIPLEX == FEATURE_OFF)
    struct nv_dload_packet_head_stru nv_dload;
    s32 ret;
    u32 old_magic;
    u32 new_magic;

    ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload),NULL);
    if(ret)
    {
        return ret;
    }
/*lint -save -e731*/
    if(true == flag)
    {
        old_magic = NV_DLOAD_INVALID_FLAG;
        new_magic = NV_FILE_EXIST;
    }
    else
    {
        new_magic = NV_DLOAD_INVALID_FLAG;
        old_magic = NV_FILE_EXIST;
    }
/*lint -restore*/
    nv_dload.nv_bin.magic_num = (nv_dload.nv_bin.magic_num == old_magic) ? new_magic : nv_dload.nv_bin.magic_num;
    ret = bsp_nand_write((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload));
    if(ret)
    {
        return ret;
    }
#endif
    return 0;

}

/*获取升级包数据有效性
 *true :有效 false: 无效
 */
bool nv_get_upgrade_flag(void)
{
    struct nv_dload_packet_head_stru nv_dload;
    s32 ret;

    ret = bsp_nand_read((char*)NV_DLOAD_SEC_NAME,0,&nv_dload,sizeof(nv_dload),NULL);
    if(ret)
    {
        return false;
    }

    if(nv_dload.nv_bin.magic_num == NV_FILE_EXIST)
    {
        return true;
    }
    return false;
}



/*lint -restore*/

EXPORT_SYMBOL(nv_file_close);
EXPORT_SYMBOL(nv_file_open);
EXPORT_SYMBOL(nv_file_seek);
EXPORT_SYMBOL(nv_file_write);
EXPORT_SYMBOL(nv_file_read);
EXPORT_SYMBOL(nv_file_remove);
EXPORT_SYMBOL(nv_file_access);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


