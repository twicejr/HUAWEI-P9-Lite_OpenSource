

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include "product_config.h"
#include "bsp_om.h"
#include "mdrv_efuse.h"
#include "bsp_efuse.h"
#include "hi_efuse.h"

#ifdef HI_K3_EFUSE
#include <mdrv.h>
#include "../../adrv/adrv.h"
#endif

#include <soc_onchiprom.h>

#ifdef CONFIG_EFUSE

int mdrv_efuse_write_huk(char *pBuf,unsigned int len)
{
    return OK;
}

int mdrv_efuse_check_huk_valid(void)
{
    return OK;
}

/*************************************************
 函 数 名   : DRV_GET_DIEID
 功能描述   : DRV_GET_DIEID
 输入参数   : buf: data buffer
              len: length of the group
 输出参数   :
 返 回 值   : OK                (0)
              BUF_ERROR         (-55)
              LEN_ERROR         (-56)
              READ_EFUSE_ERROR  (-57)
 调用函数   :
 被调函数   :

 修改历史   :
   日    期 : 2013年8月12日
   作    者 : l00225826
   修改内容 : 新生成函数

*************************************************/
int mdrv_efuse_get_dieid(unsigned char* buf,int length)
{
#ifdef HI_K3_EFUSE
    return get_efuse_dieid_value(buf, (unsigned int)length, 0);
#else
    unsigned int i = 0;
    int ret = 0;

#if (EFUSE_DIEID_BIT < 32)
    u32 *buf_die_id = (u32*)buf;
#endif

    if(NULL == buf)
    {
        efuse_print_error("die id buf is error.\n");
        return EFUSE_ERROR;
    }

    if(length < EFUSE_DIEID_LEN)
    {
        efuse_print_error("die id lenth is error.\n");
        return EFUSE_ERROR;
    }

    memset(buf, 0, EFUSE_DIEID_LEN);

    pr_info("efuse read start group %d length %d.\n", EFUSE_GRP_DIEID, EFUSE_DIEID_SIZE);

    if(0 != (ret = bsp_efuse_read((u32*)buf, EFUSE_GRP_DIEID, EFUSE_DIEID_SIZE)))
    {
        efuse_print_error("die id read efuse error.\n");
        return READ_EFUSE_ERROR;
    }

    for(i = 0;i < EFUSE_DIEID_SIZE;i++)
    {
        pr_info("efuse end buf[%d] is 0x%x.\n", i, buf[i]);
    }
    pr_info("efuse read end ret %d\n", ret);

#if (EFUSE_DIEID_BIT < 32)
    buf_die_id[EFUSE_DIEID_SIZE-1] &= (((u32)0x1 << EFUSE_DIEID_BIT) - 1);
#endif

    return EFUSE_OK;
#endif
}


/*************************************************
 函 数 名   : DRV_GET_CHIPID
 功能描述   : DRV_GET_CHIPID
 输入参数   : buf: data buffer
              len: length of the group
 输出参数   :
 返 回 值   : OK                (0)
              BUF_ERROR         (-55)
              LEN_ERROR         (-56)
              READ_EFUSE_ERROR  (-57)
 调用函数   :
 被调函数   :

 修改历史   :
   日    期 : 2013年8月12日
   作    者 : l00225826
   修改内容 : 新生成函数

*************************************************/
#ifdef HI_K3_EFUSE
int mdrv_efuse_get_chipid(unsigned char* buf,int length)
{
    return get_efuse_chipid_value(buf, (unsigned int)length, 0);
}
#else
int mdrv_efuse_get_chipid(unsigned char* buf,int length)
{
    return EFUSE_OK;
}

#endif

void DRV_DIEID_TEST(void)
{
    int i = 0;
    char *buf = kzalloc(EFUSE_DIEID_LEN, GFP_KERNEL);
    if(NULL == buf)
    {
        efuse_print_info("alloc mem is fail.\n");
        return;
    }

    if(EFUSE_OK == mdrv_efuse_get_dieid(buf, EFUSE_DIEID_LEN))
    {
        for(i = 0;i < EFUSE_DIEID_LEN;i++)
        {
            efuse_print_info("0x%x \n", *(buf+i));
        }

    }
    else
    {
        efuse_print_error("DRV_GET_DIEID is fail.\n");
    }

    kfree(buf);
}
#else

int mdrv_efuse_write_huk(char *pBuf,unsigned int len)
{
    return OK;
}

int mdrv_efuse_check_huk_valid(void)
{
    return OK;
}

int mdrv_efuse_get_dieid(unsigned char* buf,int length)
{
    return EFUSE_OK;
}

int mdrv_efuse_get_chipid(unsigned char* buf,int length)
{
    return EFUSE_OK;
}

#endif

#ifdef DX_SEC_BOOT

#define DX_SECURESTATE_SECURE   (1)
#define DX_SECURESTATE_RMA      (2)

int bsp_efuse_ioctl_get_securestate(void)
{
    int ret = 0;
    u32 value = 0;

    ret = bsp_efuse_read(&value, 0x0A, 1);
    if (ret)
        return ret;

    if (value & 0x80000000)
        return DX_SECURESTATE_RMA;

    if (((value >> 16) & 0x0F) == 0x03)
        return DX_SECURESTATE_SECURE;

    return 0;
}

int bsp_efuse_ioctl_set_securestate(int arg)
{
    int ret = 0;
    u32 value = 0;

    ret = bsp_efuse_ioctl_get_securestate();
    if (ret < 0)
        return ret;

    if (ret > 0)
        return 1;

    if (arg == DX_SECURESTATE_SECURE)
        return -1;

    if (arg == DX_SECURESTATE_RMA)
        value |= 0x80000000;

    ret = bsp_efuse_write(&value, 0x0A, 1);

    return ret;
}

int mdrv_efuse_ioctl(int cmd, int arg, unsigned char* buf, int len)
{
    int ret = 0;

    switch (cmd) {
        case MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE:
            ret = bsp_efuse_ioctl_set_securestate(arg);
            break;
        case MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE:
            ret = bsp_efuse_ioctl_get_securestate();
            break;
    }

    return ret;
}

#else

int mdrv_efuse_ioctl(int cmd, int arg, unsigned char* buf, int len)
{
    efuse_print_error("It's only a stub");

    return 0;
}

#endif


