

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "bsp_nvim.h"
#include "nv_comm.h"


#if 0
/*添加到全局变量才能在m3串口调用*/
    struct symbol kallsyms[]

extern u32 nv_init_test(void);
extern u32 nv_read_part_test(u32 nvid,u32 off,u32 len);
extern u32 nv_read_rand_test(u32 nvid);
extern u32 nv_read_test_01(void);
extern u32 nv_read_test_02(void);
extern u32 nv_read_test_03(void);
extern u32 nv_read_test_04(void);
extern u32 nv_read_test_05(void);
extern u32 nv_read_test_06(void);
extern u32 nv_read_test_07(void);


{"nv_init_test", (unsigned long)&nv_init_test},
{"nv_read_part_test", (unsigned long)&nv_read_part_test},
{"nv_read_rand_test", (unsigned long)&nv_read_rand_test},
{"nv_read_test_01", (unsigned long)&nv_read_test_01},
{"nv_read_test_02", (unsigned long)&nv_read_test_02},
{"nv_read_test_03", (unsigned long)&nv_read_test_03},
{"nv_read_test_04", (unsigned long)&nv_read_test_04},
{"nv_read_test_05", (unsigned long)&nv_read_test_05},
{"nv_read_test_06", (unsigned long)&nv_read_test_06},
{"nv_read_test_07", (unsigned long)&nv_read_test_07},
#endif
u32 nv_init_test(void)
{
    u32 ret = NV_ERROR;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    if(ddr_info->ccore_init_state == NV_INIT_OK)
    {
        return NV_OK;
    }

    ret = bsp_nvm_init();

    return ret;

}

u32 nv_read_part_test(u32 nvid,u32 off,u32 len)
{
    u32 ret;
    u8* tempdata;
    u32 i= 0;

    tempdata = (u8*)nv_malloc(len +1);
    if(NULL == tempdata)
    {
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    ret = bsp_nvm_readpart(nvid,off,tempdata,len);
    if(NV_OK != ret)
    {
        nv_free(tempdata);
        return BSP_ERR_NV_READ_DATA_FAIL;
    }

    for(i=0;i<len;i++)
    {
        if((i%16) == 0)
        {
            printf("\n");
        }
        printf("%2.2x ",(u8)(*(tempdata+i)));
    }

    printf("\n");
    return 0;
}

u32 nv_read_rand_test(u32 nvid)
{
    u32 ret;
    u8* tempdata;
    u32 i= 0;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};

    ret = nv_search_byid(nvid, (u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
    if(NV_OK != ret)
    {
        return ret;
    }
    if(ref_info.nv_len == 0)
    {
        return NV_ERROR;
    }

    tempdata = (u8*)nv_malloc(ref_info.nv_len +1);
    if(NULL == tempdata)
    {
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    ret = bsp_nvm_read(nvid,tempdata,ref_info.nv_len);
    if(NV_OK != ret)
    {
        return BSP_ERR_NV_READ_DATA_FAIL;
    }

    for(i=0;i<ref_info.nv_len;i++)
    {
        if((i%16) == 0)
        {
            printf("\n");
        }
        printf("%2.2x ",(u8)(*(tempdata+i)));
    }

    printf("\n");

    nv_free(tempdata);
    
    return 0;
}


/*read nv test*/


/*不存在的nv*/
u32 nv_read_test_01(void)
{
    u32 itemid = 0xffff;
    u32 ret;

    ret = nv_read_rand_test(itemid);

    if(ret == BSP_ERR_NV_NO_THIS_ID)
    {
        return NV_OK;
    }

    return ret;
}

/*传入长度偏移错误测试01*/
u32 nv_read_test_02(void)
{
    u32 itemid = 0xd007;
    u32 ret = NV_ERROR;

    u32 datalen  = 5;
    u32 off = 0;

    ret = nv_read_part_test(itemid,off,datalen);
    if(ret == BSP_ERR_NV_READ_DATA_FAIL)
    {
        return NV_OK;
    }

    return NV_ERROR;
}
/*传入长度偏移错误测试02*/
u32 nv_read_test_03(void)
{
    u32 itemid = 0xd007;
    u32 ret = NV_ERROR;

    u32 datalen  = 1;
    u32 off = 4;

    ret = nv_read_part_test(itemid,off,datalen);
    if(ret == BSP_ERR_NV_READ_DATA_FAIL)
    {
        return NV_OK;
    }

    return NV_ERROR;
}

u32 nv_read_test_04(void)
{
    u32 itemid = 0xd007;
    u32 ret = NV_ERROR;

    u32 datalen  = 4;
    u32 off = 0;

    ret = nv_read_part_test(itemid,off,datalen);

    return ret;
}

u32 nv_read_test_05(void)
{
    u32 itemid = 0xd007;
    u32 ret = NV_ERROR;

    ret = nv_read_rand_test(itemid);

    return ret;
}

u32 nv_read_test_06(void)
{
    u32 itemid = 0xd007;
    u32 ret = NV_ERROR;
    u8* pdata = NULL;

    ret = bsp_nvm_read(itemid,pdata,sizeof(u32));
    if(ret == BSP_ERR_NV_INVALID_PARAM)
    {
        return NV_OK;
    }
    return ret;
}

u32 nv_read_test_07(void)
{
    u32 itemid = 0xd007;
    u32 ret = NV_ERROR;
    u32 pdata = 0;

    ret = bsp_nvm_read(itemid,(u8 *)&pdata,1);
    if(ret == BSP_ERR_NV_ITEM_LEN_ERR)
    {
        return NV_OK;
    }
    return ret;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
