
#ifndef _NV_FILE_FASTBOOT_H_
#define _NV_FILE_FASTBOOT_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "bsp_nvim.h"

#if defined(FEATURE_NV_FLASH_ON)
#include "ptable_com.h"
#include <bsp_nandc.h>

#define NV_BACK_SEC_NAME               PTABLE_NVBACK_NM
#define NV_DLOAD_SEC_NAME              PTABLE_NVDLOAD_NM
#define NV_DEF_SEC_NAME                PTABLE_NVDEFAULT_NM


#elif defined(FEATURE_NV_EMMC_ON)

#define NV_SYS_NV_PATH                          "/system/nvimg.bin"

#define NV_BACK_SEC_NAME               "modemnvm_backup"
#define NV_DLOAD_SEC_NAME              "modemnvm_update"
#define NV_DEF_SEC_NAME                "modemnvm_factory"
#define NV_SYS_SEC_NAME                "modemnvm_system"


/*structure of nand chip specification parameter */
struct nand_spec
{
    u32 blocksize;          /*one block size of nand flash*/
    u32 pagesize;           /*one page size of nand flash*/
    u32 chipsize;           /*the total size of nand flash*/
    u32 sparesize;           /*the total size of nand flash*/

    u32 pagenumperblock;
	u32 ecctype;            /* selected by nandc, not nand itself */
	u32 buswidth;
	u32 addrnum;
};
#endif


typedef u32  (*bsp_file_read)(const char *partition_name, u32 partition_offset, void* ptr_ram_addr, u32 length,u32* skip_len);
typedef u32  (*bsp_file_isbad)(const char *partition_name, u32 partition_offset);
typedef u32  (*bsp_file_get_info)(struct nand_spec *spec);
typedef u32  (*bsp_file_read_flag_nv)(const char *partition_name, unsigned int partition_offset, unsigned char *flag);


struct file_func_table_stru
{
    bsp_file_read           file_read;
    bsp_file_isbad          file_is_bad;
    bsp_file_get_info       file_get_info;
    bsp_file_read_flag_nv   file_read_flag;
};
extern struct file_func_table_stru g_file_func_table;

struct nv_flash_file_header_stru
{
    void* fp;          /*file head pointer*/
    u32   flash_type;  /*flash type*/
    u32   off;         /*offset in this flash*/
    u32   seek;        /*flash seek*/
    u32   ops;         /*ops count*/
    u32   length;      /*file length,not section length*/
    u32   image;       /*nv img id :ptable_com.h*/
    const s8    path[64];    /*file path*/
    const s8    name[16];    /*sec name*/
};
/*file type*/
enum
{
    NV_FILE_DLOAD = 0,
    NV_FILE_BACKUP ,
    NV_FILE_XNV_CARD_1 ,
    NV_FILE_XNV_CARD_2,
    NV_FILE_XNV_CARD_3,
    NV_FILE_CUST_CARD_1,
    NV_FILE_CUST_CARD_2,
    NV_FILE_CUST_CARD_3,
    NV_FILE_SYS_NV,
    NV_FILE_DEFAULT,
    NV_FILE_XNV_MAP_CARD_1,
    NV_FILE_XNV_MAP_CARD_2,
    NV_FILE_XNV_MAP_CARD_3,
    NV_FILE_BUTT
};

extern struct nv_flash_file_header_stru g_boot_nv_file[NV_FILE_BUTT];

/*8bit nand,blocksize = 128k*/
#define NV_BIN_FILE_BLOCK_NUM         32           /*分区最大有4M,32块*/
#define NV_DLOAD_FILE_BLOCK_NUM       24           /*dload 分区长度3M,块数最多24块*/

struct nv_sec_file_block_info
{
    u32 nv_dload[NV_DLOAD_FILE_BLOCK_NUM];
    u32 sys_nv[NV_DLOAD_FILE_BLOCK_NUM];
    u32 nv_bak[NV_BIN_FILE_BLOCK_NUM];
    u32 nv_default[NV_BIN_FILE_BLOCK_NUM];
};

extern struct nv_sec_file_block_info g_sec_info;

u32 nv_sec_off_count(const struct nv_flash_file_header_stru* ffp,u32 vir_off,u32* phy_off);

u32 nv_count_file_sec_info(const s8* name,u32 len,u32* file_sec);

#if defined(FEATURE_NV_FLASH_ON)

struct nv_nand_info_stru
{
    u32 page_size;
    u32 block_size;
    u32 total_size;
};

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /*_NV_FILE_H_*/

