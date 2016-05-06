/*
 *  Copyright (C), 2015-2017, Hisilicon Technologies Co., Ltd.
 *
 * File name     : nand.c
 * Author        :
 * Created       : 2015-12-21
 * Last Modified :
 * Description   :
 * Modification  : Create file
 *
 */

#include <soc_memmap_comm.h>
#include <osl_bio.h>
#include <hi_nandc.h>
#include <bsp_nandc.h>
#include <ptable_com.h>
#include "lib.h"
#include "m3boot.h"

#define PAGE_OFFSET                         (16)

unsigned int get_nand_page_size(void)
{
    HI_NFC_CON_T nfc_con;
    unsigned int page_size = NANDC_SIZE_2K;
    
    nfc_con.u32= readl(HI_NANDC_REGBASE_ADDR + HI_NFC_CON_OFFSET);
    switch(nfc_con.bits.pagesize)
    {
        case 1:
            page_size = NANDC_SIZE_2K;
            break;
        case 2:
            page_size = NANDC_SIZE_4K;
            break;
        case 3:
            page_size = NANDC_SIZE_8K;
            break;
        case 4:
            page_size = NANDC_SIZE_16K;
            break;
        default:
            page_size = NANDC_SIZE_2K;
    };

    return page_size;
}

unsigned int get_block_page_num(void)
{
    HI_NFC_BOOT_SET_T boot_set_reg;
    unsigned int page_nm = NANDC_BLOCK_64PAGE;

    boot_set_reg.u32= readl(HI_NANDC_REGBASE_ADDR + HI_NFC_BOOT_SET_OFFSET);
    switch(boot_set_reg.bits.block_size)
    {
        case 0:
            page_nm = NANDC_BLOCK_64PAGE;
            break;
        case 1:
            page_nm = NANDC_BLOCK_128PAGE;
            break;
        case 2:
            page_nm = NANDC_BLOCK_256PAGE;
            break;
        case 3:
            page_nm = NANDC_BLOCK_512PAGE;
            break;
        default:
            page_nm = NANDC_BLOCK_64PAGE;
    };

    return page_nm;
}

unsigned int get_flash_addr_from_reg(unsigned int page_sz)
{
    volatile unsigned int flash_page_nm = 0, reg_addr_l = 0;
    
    reg_addr_l = readl(HI_NANDC_REGBASE_ADDR + HI_NFC_ADDRL_OFFSET);
    flash_page_nm = (reg_addr_l >> PAGE_OFFSET);
    
    return flash_page_nm * page_sz;
}

unsigned int get_src_addr(void)
{
    volatile unsigned int temp = 0, page_sz = 0, page_nm = 0, block_sz = 0, src = 0;
    
    page_sz = get_nand_page_size();
    page_nm = get_block_page_num();
    print_info_with_u32("\r\npage_sz 0x", page_sz);
    print_info_with_u32("\r\npage_nm 0x", page_nm);    
    block_sz = page_sz * page_nm;
    
    /* 从block 0开始逐块读，直到找到fastboot对应的逻辑地址 */
    for(src = HI_NAND_MEM_BUFFER_ADDR; src <= APPA9_FASTBOOT_BASE; src += block_sz)
    {
        temp = *((unsigned int *)src);
        if(PTABLE_FASTBOOT_START <= get_flash_addr_from_reg(page_sz))
        {
            print_info_with_u32("\r\ncp from 0x", src);
            print_info("\r\n");
            return src;
        }
    }
    print_info("\r\nerr: no fastboot addr\r\n");
    return 0;
}


