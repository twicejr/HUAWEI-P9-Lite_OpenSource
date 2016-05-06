

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
/*lint -e322*//*lint -e7*/
#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>
/*lint +e322*//*lint +e7*/

#include "oal_sdio.h"
#include "oal_sdio_host_if.h"

#include "plat_debug.h"
#include "plat_sdio.h"
#include "plat_pm.h"

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/

/*****************************************************************************
  3 Function Definition
*****************************************************************************/

/*
 * Prototype    : sdio_patch_writesb
 * Description  : provide interface for pm driver
 * Input        : uint8* buf, uint32 len
 * Output       : None
 * Return Value : int32
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         :
 *     Author       :
 *     Modification : Created function
 *
 */
int32 sdio_patch_writesb(uint8* buf, uint32 len)
{
    int ret;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    struct sdio_func *func = pm_data->pst_wlan_pm_info->pst_sdio->func;

    if (NULL == func)
    {
        PS_PRINT_ERR("Sdio device is NOT initialized\n");
        return -FAILURE;
    }

    if (NULL == buf || len == 0)
    {
        PS_PRINT_ERR("Write buf is NULL\n");
        return -FAILURE;
    }

    PS_PRINT_DBG("======sdio write:%u\n",len);
    //print_hex_dump_bytes("writesb :", DUMP_PREFIX_ADDRESS, buf, len);

    len  = HISDIO_ALIGN_4_OR_BLK(len);

    //if(len < HISDIO_BLOCK_SIZE){
    sdio_claim_host(func);
    ret = oal_sdio_writesb(func, HISDIO_REG_FUNC1_FIFO, buf, len);
    if (ret < 0)
    {
        PS_PRINT_ERR("oal_sdio_writesb error:%d\n", ret);
    }
    sdio_release_host(func);
    //}else{
    //    ret = hi110x_sdio_rw_sg(func, SDIO_WRITE, buf, len);
    //}

    return ret;
}

/*
 * Prototype    : sdio_patch_readsb
 * Description  : provide interface for pm driver
 * Input        : uint8* buf, uint32 len uint32 timeout (ms)
 * Output       : None
 * Return Value : int32
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         :
 *     Author       :
 *     Modification : Created function
 *
 */

int32 sdio_patch_readsb(uint8* buf, uint32 len, uint32 timeout)
{
    uint8   int_mask;
    uint8  *ver_info;
    int     ret = 0;
    unsigned long timeout_jiffies;
    uint32  xfer_count;
    int     i;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    struct sdio_func *func = pm_data->pst_wlan_pm_info->pst_sdio->func;


    if (NULL == func)
    {
        PS_PRINT_ERR("sdio device is NOT initialized\n");

        return -FAILURE;
    }

    if (NULL == buf || 0 == len)
    {
        PS_PRINT_ERR("Invalid NULL read buf\n");

        return -FAILURE;
    }


    sdio_claim_host(func);
    timeout_jiffies = jiffies + msecs_to_jiffies(timeout);
    for(;;)
    {
        int_mask = oal_sdio_readb(func, HISDIO_REG_FUNC1_INT_STATUS, &ret);
        if(ret)
        {
            PS_PRINT_ERR("read int mask fail, ret=%d\n", ret);
            sdio_release_host(func);
            return -FAILURE;
        }

        if(int_mask & HISDIO_FUNC1_INT_MASK)
        {
            /*sdio int came*/
            break;
        }

        if(time_after(jiffies, timeout_jiffies))
        {
            PS_PRINT_ERR("read int mask timeout, int_mask=%x\n", int_mask);
            sdio_release_host(func);
            return -FAILURE;
        }
        cpu_relax();
    }

    oal_sdio_writeb(func, int_mask, HISDIO_REG_FUNC1_INT_STATUS, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("clear int mask error:%d\n", ret);
        sdio_release_host(func);
        return -FAILURE;
    }

    xfer_count = oal_sdio_readl(func, HISDIO_REG_FUNC1_XFER_COUNT, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("read xfer_count err:%d\n", ret);
        sdio_release_host(func);
        return -FAILURE;
    }

    PS_PRINT_DBG("xfer_cout=%d, len=%d\n", xfer_count, len);

    if (xfer_count < len)
    {
        len = xfer_count;
        PS_PRINT_DBG("xfer_count(%d) not equal to len(%d)\n", xfer_count, len);
    }

    ver_info = kzalloc((xfer_count + 1), GFP_KERNEL);
    if (NULL == ver_info)
    {
        sdio_release_host(func);
        return -ENOMEM;
    }

    memset(ver_info, 0, xfer_count);
    ret = oal_sdio_readsb(func, ver_info, HISDIO_REG_FUNC1_FIFO, xfer_count);
    if (ret < 0)
    {
        PS_PRINT_ERR("hsdio_readsb error:%d\n", ret);
    }
    else
    {
        for (i = 0; i < len; i++)
        {
            buf[i] = ver_info[i];
        }
    }

    PS_PRINT_DBG("=====sdio read:[ret=%d]\n", ret);

    kfree(ver_info);

    sdio_release_host(func);

    return xfer_count;
}

