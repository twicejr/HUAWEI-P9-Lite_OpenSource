

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <partition_ops.h>
/*#include <fastboot_interface.h>*/
#include <emmc_ops.h>
#include <nv_file.h>
#include <bsp_nvim.h>

extern void *alloc(signed sz);
extern void cprintf(const char *fmt, ...);
extern  void *memcpy(void *_dst, const void *_src, unsigned len);
extern void *memset(void *_p, unsigned v, unsigned count);
u32 bsp_emmc_read(const char *partition_name, u32 partition_offset, void* ptr_ram_addr, u32 length,u32* skip_len);
u32 bsp_emmc_isbad(const char *partition_name, u32 partition_offset);
u32 bsp_get_emmc_info(struct nand_spec *spec);
unsigned int bsp_emmc_read_flag_nv(const char *partition_name, unsigned int partition_offset, unsigned char *flag);
extern void * get_operators(char * string);



struct nv_flash_file_header_stru g_boot_nv_file[NV_FILE_BUTT] = {
                                  {NULL,NV_FILE_DLOAD,         0,0,0,0,0,NV_DLOAD_PATH,      NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_BACKUP,        0,0,0,0,0,NV_BACK_PATH,       NV_BACK_SEC_NAME},
                                  {NULL,NV_FILE_XNV_CARD_1,    0,0,0,0,0,NV_XNV_CARD1_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_CARD_2,    0,0,0,0,0,NV_XNV_CARD2_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_CARD_3,    0,0,0,0,0,NV_XNV_CARD3_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_CUST_CARD_1,   0,0,0,0,0,NV_CUST_CARD1_PATH, NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_CUST_CARD_2,   0,0,0,0,0,NV_CUST_CARD2_PATH, NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_CUST_CARD_3,   0,0,0,0,0,NV_CUST_CARD3_PATH, NV_DLOAD_SEC_NAME},
                                  //lint --e{784}
                                  {NULL,NV_FILE_SYS_NV,        0,0,0,0,0,NV_FILE_SYS_NV_PATH,     NV_SYS_SEC_NAME},
                                  {NULL,NV_FILE_DEFAULT,       0,0,0,0,0,NV_DEFAULT_PATH,    NV_DEF_SEC_NAME},
                                  {NULL,NV_FILE_XNV_MAP_CARD_1,0,0,0,0,0, NV_XNV_CARD1_MAP_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_MAP_CARD_2,0,0,0,0,0, NV_XNV_CARD2_MAP_PATH,  NV_DLOAD_SEC_NAME},
                                  {NULL,NV_FILE_XNV_MAP_CARD_3,0,0,0,0,0, NV_XNV_CARD3_MAP_PATH,  NV_DLOAD_SEC_NAME},
                                          };

struct file_func_table_stru g_file_func_table =
{
    .file_read =(bsp_file_read)bsp_emmc_read,
    .file_is_bad = (bsp_file_isbad)bsp_emmc_isbad,
    .file_get_info = (bsp_file_get_info)bsp_get_emmc_info,
    .file_read_flag = (bsp_file_read_flag_nv)bsp_emmc_read_flag_nv,
};

struct nv_sec_file_block_info g_sec_info;

/**
 * Name			:	bsp_flash_read
 * Arguments	:	@partition_name		- partition name
 *					@partition_offset	- offset from partition to read from
 *					@ptr_ram_addr	- pointer to ram addr to store the data read from flash
 *					@length		- number of bytes to read
 * Return		:	0				- success
 *				:   else			- failure
 * Desciption	:	length must be block aligned
 */
u32 bsp_emmc_read(const char *partition_name, u32 partition_offset, void* ptr_ram_addr, u32 length,u32* skip_len)
{
    s32 ret;
    struct ptentry *p;
    u32 block_off;  /*offset in the emmc block*/
    u32 sec_off;
    u8* temp_ram_addr = (u8*)ptr_ram_addr;
    static u8* block_data = NULL;
    u32 len;
	struct emmc_operators *emmc_ops = NULL;
	struct partition_operators *part_ops = NULL;

	/*lint -save -e838*/
	emmc_ops = (struct emmc_operators *)get_operators(EMMC_MODULE_NAME_STR);
	if(!emmc_ops){
		cprintf("can not get emmc_ops!\n");
		return 4;
	}
	part_ops = (struct partition_operators *)get_operators(PARTITION_MODULE_NAME_STR);
	if(!part_ops){
		cprintf("can not get part_ops!\n");
		return 4;
	}
	/*lint -restore +e838*/
	//lint --e{605}
	p = part_ops->find_ptn(partition_name);
    if(p == NULL)
    {
        cprintf("ERROR: bsp_nand_read can't find partition %s\n", partition_name);
        return 1;
    }

    if(!block_data)
    {
        block_data = (u8*)alloc(2*SHM_MEM_NV_SIZE);/*lint !e718 !e746*/
        if(!block_data)
            return BSP_ERR_NV_MALLOC_FAIL;
    }
    memset(block_data, 0, 2 * SHM_MEM_NV_SIZE);
    block_off = partition_offset%EMMC_BLOCK_SIZE; /*当前块中的偏移*/
    sec_off   = partition_offset - block_off;  /*当前分区偏移*/
    len = block_off + length;

    len = len%EMMC_BLOCK_SIZE == 0? len : len + EMMC_BLOCK_SIZE - len%EMMC_BLOCK_SIZE;

    if(len > 2*SHM_MEM_NV_SIZE)
    {
        cprintf("%s %d, len : 0x%x > ddr size\n", __func__,__LINE__, len);
        return NV_ERROR;
    }
	ret = emmc_ops->emmc_read(p, sec_off, (void *)block_data, &len);
	if (ret)
    {
        cprintf("%s %d, sec_off :0x%x len : 0x%x\n",__func__,__LINE__,sec_off, len);
		cprintf("emmc read modem fail\n");
        return BSP_ERR_NV_READ_DATA_FAIL;
    }
    memcpy(temp_ram_addr,block_data + block_off, length);/* [false alarm]:屏蔽Fortify错误 */

    if(skip_len)
        *skip_len = 0;
    return NV_OK;

}

/**
 * Name			:	bsp_flash_isbad
 * Arguments	:	@partition_name		- partition name
 *					@partition_offset	- block offset from partition to check
 *
 * Return		:	0				- good block
 *				:   1			    - bad block
 *              :   -1              - error
 * Description	:	check whether a block is bad
 */
/*lint -save -e715*/
u32 bsp_emmc_isbad(const char *partition_name, u32 partition_offset)
{
    /* eMMC doesn't need check bad */
	return 0;
}
/*lint -restore +e715*/

/**
 * Name			:	bsp_get_nand_info
 * Arguments	:	@spec		    - to store flash info
 * Return		:	0				- success
 *				:   else			- failure
 * Desciption	:	adapt for nv in k3v3
 */
u32 bsp_get_emmc_info(struct nand_spec *spec)
{
	spec->pagesize			= 0x1;
	spec->pagenumperblock	= 0;
	spec->addrnum			= 0;
	spec->ecctype			= 0;
	spec->buswidth			= 0;
    spec->blocksize         = 0x200;          /* 512byte */
    spec->sparesize         = 0;
    spec->chipsize          = 0;

	return 0;
}

/**
 * Name			:	bsp_nand_blk_write_nv
 * Arguments	:	@partition_name		- partition name
 *					@partition_offset   - offset from partition to read from, must be block aligned.
 *					@flag		- flag value. NV_FLAG means write successful last time, else failure
 * Return		:	0				- success
 *				:   else			- failure
 * Description	:	read nv_flag of a block
 */
/*lint -save -e715*/
unsigned int bsp_emmc_read_flag_nv(const char *partition_name, unsigned int partition_offset, unsigned char *flag)
{
/*lint -restore +e715*/

    if((!flag)||(!partition_name))
        return 1;

    *flag = NV_OK;

    return 0;
/*lint -save -e715*/
}
/*lint -restore +e715*/

/**
 * Name			:	bsp_nand_blk_write_nv
 * Arguments	:	@partition_name		- partition name
 *					@partition_offset   - offset from partition to read from, must be block aligned.
 *					@flag		- flag value. NV_FLAG means write successful last time, else failure
 * Return		:	0				- success
 *				:   else			- failure
 * Description	:	read nv_flag of a block
 */
/*lint -save -e818 -e715*/
u32 nv_count_file_sec_info(const s8* name,u32 len,u32* file_sec)
{
    return NV_OK;
}
/*lint -restore +e818 +e715*/
/**
 * Name			:	bsp_nand_blk_write_nv
 * Arguments	:	@partition_name		- partition name
 *					@partition_offset   - offset from partition to read from, must be block aligned.
 *					@flag		- flag value. NV_FLAG means write successful last time, else failure
 * Return		:	0				- success
 *				:   else			- failure
 * Description	:	read nv_flag of a block
 */
/*lint -save -e818 -e715*/
u32 nv_sec_off_count(const struct nv_flash_file_header_stru* ffp,u32 vir_off,u32* phy_off)
{
    *phy_off = vir_off;
    return NV_OK;
}
/*lint -restore +e818 +e715*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

