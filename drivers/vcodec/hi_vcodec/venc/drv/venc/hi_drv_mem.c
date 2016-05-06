
#include "hi_drv_mem.h"
#include <asm/uaccess.h>

#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>
#include <linux/file.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define ALIGN_UP(val, align) ( (val+((align)-1))&~((align)-1) )

HI_U32  g_VencPrintEnable = 0xf;
char *pszMsg[((HI_U8)VENC_ALW) + 1] = {"FATAL","ERR","WARN","IFO","DBG"};
HI_CHAR g_VencPrintMsg[1024];

DDR_MEM_ALLOC DdrMem;


/***********************************************************************************
    func: get system time function
***********************************************************************************/
#define DIV_NS_TO_MS  1000000

HI_S32 DRV_Venc_GetTimeStampMs(HI_U32 *pu32TimeMs)
{
    HI_U64 u64TimeNow = 0;;
    if (HI_NULL == pu32TimeMs)
    {
        HI_ERR_VENC("null pointer error\n");
        return HI_FAILURE;
    }

    u64TimeNow = sched_clock();
    do_div(u64TimeNow, DIV_NS_TO_MS);
    *pu32TimeMs = (HI_U32)u64TimeNow;

    return HI_SUCCESS;
}

HI_S32 gVencNodeNum = 0;
ION_MEM_DESC_S  gVencMemNode[MAX_ION_MEM_NODE];
struct ion_client *g_ion_client = HI_NULL;

HI_S32 DRV_MEM_INIT(HI_VOID)
{
    g_ion_client = (struct ion_client *)hisi_ion_client_create("hi_vcodec_ion");
    if (HI_NULL == g_ion_client)
    {
        HI_ERR_VENC("%s, failed to create hi_vcodec ion client!\n", __func__);
        return HI_FAILURE;
    }

    memset((HI_VOID *)&gVencMemNode, 0, MAX_ION_MEM_NODE*sizeof(ION_MEM_DESC_S));
	gVencNodeNum = 0;
    return HI_SUCCESS;
}

HI_S32 DRV_MEM_EXIT(HI_VOID)
{
    HI_S32 i = 0;

    if (g_ion_client == HI_NULL)
    {
        HI_ERR_VENC("%s, FATAL: g_ion_client = NULL\n", __func__);
        return HI_FAILURE;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (gVencMemNode[i].phys_addr != 0)
        {
			HI_ERR_VENC("%s, FATAL: MEM not free!!!\n", __func__);
            ion_unmap_kernel(g_ion_client, gVencMemNode[i].handle);
            ion_free(g_ion_client, gVencMemNode[i].handle);
			memset(&gVencMemNode[i], 0, sizeof(ION_MEM_DESC_S));
        }
    }

    ion_client_destroy(g_ion_client);
    g_ion_client = HI_NULL;

    return HI_SUCCESS;
}

/* MMU内存分配  */
HI_S32 DRV_MMU_MEM_AllocAndMap(const HI_CHAR *bufname, HI_CHAR *zone_name,HI_U32 size, HI_S32 align, MEM_BUFFER_S *psMBuf,HI_U32 mmu_bypass_flag)
{
    HI_S32 i   = 0;
    HI_S32 ret = 0;
    size_t len = 0;
    struct ion_handle *handle = HI_NULL;
    ion_phys_addr_t phys_addr = 0;
    HI_VOID *virt_addr = HI_NULL;

	struct iommu_map_format iommu_format;
    memset((HI_VOID *)&iommu_format, 0, sizeof(struct iommu_map_format));

    if (HI_NULL != psMBuf->pStartVirAddr)
    {
        HI_ERR_VENC("%s, Param StartVirAddr %p != NULL\n", __func__, psMBuf->pStartVirAddr);
        return HI_FAILURE;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (0 == gVencMemNode[i].phys_addr && HI_NULL == gVencMemNode[i].handle)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        HI_ERR_VENC("%s, FATAL: No free ion mem node!\n", __func__);
        return HI_FAILURE;
    }

	if (mmu_bypass_flag)
	{
		handle = ion_alloc(g_ion_client, size, PAGE_SIZE, ION_HEAP(ION_GRALLOC_HEAP_ID), 0);
	}
	else
	{
		handle = ion_alloc(g_ion_client, size, PAGE_SIZE, ION_HEAP(ION_SYSTEM_HEAP_ID), 0);
	}

	if (IS_ERR_OR_NULL(handle))
    {
        HI_ERR_VENC("%s, failed to alloc ion handle!\n", __func__);
        return HI_FAILURE;
    }

    virt_addr = ion_map_kernel(g_ion_client, handle);
    if (HI_NULL == virt_addr)
    {
        HI_ERR_VENC("%s, failed to map kernel virt addr!\n", __func__);
        goto err_ion_map;
    }

	if (mmu_bypass_flag)
	{
	    ret = ion_phys(g_ion_client, handle, &phys_addr, &len);
	    if (ret < 0)
	    {
        HI_ERR_VENC("%s, failed to get phy addr!\n", __func__);
	        goto err_ion_phys;
	    }
	}
	else
	{
		ret = ion_map_iommu(g_ion_client, handle, &iommu_format);
	if (ret < 0)
	{
		HI_ERR_VENC("%s, failed to ion_map_iommu!\n", __func__);
		goto err_ion_phys;
	}
	phys_addr = iommu_format.iova_start;
    HI_DBG_VENC("%s, iommu_format.iova_start:0x%x\n", __func__, iommu_format.iova_start);
	}

	snprintf(gVencMemNode[i].node_name, MAX_MEM_NAME_LEN, bufname);
	gVencMemNode[i].node_name[MAX_MEM_NAME_LEN-1] = '\0';

	snprintf(gVencMemNode[i].zone_name, MAX_MEM_NAME_LEN, zone_name);
	gVencMemNode[i].zone_name[MAX_MEM_NAME_LEN-1] = '\0';

    gVencMemNode[i].handle    = handle;
    gVencMemNode[i].phys_addr = phys_addr;
    gVencMemNode[i].size      = size;

    gVencNodeNum++;

    psMBuf->pStartVirAddr   = virt_addr;
    psMBuf->u32StartPhyAddr =  phys_addr;
    psMBuf->u32Size         = size;

    *(HI_U32 *)psMBuf->pStartVirAddr = 0xffdd;
    HI_DBG_VENC("%s, Yeah!!!, I write 0x%x into it!!\n", __func__, *(HI_U32 *)psMBuf->pStartVirAddr);

    HI_INFO_VENC("%s, alloc phy 0x%x size %d success!\n", __func__, phys_addr, size);
    return HI_SUCCESS;

    err_ion_phys:
    ion_unmap_kernel(g_ion_client, handle);
    err_ion_map:
    ion_free(g_ion_client, handle);

    return HI_FAILURE;
}

HI_VOID DRV_MMU_MEM_UnmapAndRelease(MEM_BUFFER_S *psMBuf,HI_U32 mmu_bypass_flag)
{
    HI_S32 i = 0;

    if (g_ion_client == HI_NULL || psMBuf == HI_NULL)
    {
        HI_ERR_VENC("%s, FATAL: g_ion_client(%p)/psMBuf(%p) = NULL\n", __func__, g_ion_client, psMBuf);
        return;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (psMBuf->u32StartPhyAddr == gVencMemNode[i].phys_addr)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        HI_ERR_VENC("%s, FATAL: Ion mem node not found!\n", __func__);
        return;
    }

	if (!mmu_bypass_flag)
	{
		ion_unmap_iommu(g_ion_client, gVencMemNode[i].handle);
	}

    ion_unmap_kernel(g_ion_client, gVencMemNode[i].handle);
    ion_free(g_ion_client, gVencMemNode[i].handle);

	memset(&gVencMemNode[i], 0, sizeof(ION_MEM_DESC_S));
	gVencNodeNum = (gVencNodeNum > 0)? (gVencNodeNum-1): 0;

    HI_DBG_VENC("%s, free mem phy 0x%x size %d success!\n", __func__, psMBuf->u32StartPhyAddr, psMBuf->u32Size);

    return;
}

HI_S32 DRV_MMU_GetPhyAddr_KernelVaddr(venc_user_buf * pstFrameBuf)
{
    struct ion_handle *handle    = HI_NULL;
    HI_VOID           *virt_addr = HI_NULL;

   // DRV_SEMA_DOWN_INTERRUPTIBLE();
    if((g_ion_client == HI_NULL) || (pstFrameBuf == HI_NULL))
    {
        printk("%s, invalid Param : g_ion_client = %p, pstFrameBuf = %p\n", __func__, g_ion_client, pstFrameBuf);
        goto err_exit;
    }

	if (pstFrameBuf->share_fd < 0)
	{
        printk("%s, invalid Param share_fd = %d!\n", __func__, pstFrameBuf->share_fd);
        goto err_exit;
	}


    handle = ion_import_dma_buf(g_ion_client, pstFrameBuf->share_fd);
    if(handle == HI_NULL)
    {
        printk("%s, get ion handle failed!\n", __func__);
        goto err_exit;
    }

    virt_addr = ion_map_kernel(g_ion_client, handle);
    if (HI_NULL == virt_addr)
    {
        HI_ERR_VENC("%s failed to map kernel virt addr!\n", __func__);
        goto err_exit;
    }

	pstFrameBuf->kernelbufferaddr = (HI_U64)virt_addr;
    printk("virt_addr:0x%llx\n",pstFrameBuf->kernelbufferaddr);

    return HI_SUCCESS;

err_exit:
    return HI_FAILURE;
}

HI_S32 HI_DRV_UserCopy(struct file *file,
           HI_U32 cmd, unsigned long arg,
           long (*func)(struct file *file,
               HI_U32 cmd, unsigned long uarg))
{
    HI_CHAR  sbuf[128];
    HI_VOID  *mbuf = NULL;
    HI_VOID  *parg = NULL;
    HI_S32   err  = -EINVAL;

    /*  Copy arguments into temp kernel buffer  */
    switch (_IOC_DIR(cmd))
    {
        case _IOC_NONE:
            parg = NULL;
            break;
        case _IOC_READ:
        case _IOC_WRITE:
        case (_IOC_WRITE | _IOC_READ):
            if (_IOC_SIZE(cmd) <= sizeof(sbuf))
            {
                parg = sbuf;
            }
            else
            {
                HI_U32 buff_size = _IOC_SIZE(cmd);
                /* too big to allocate from stack */
                mbuf = kmalloc(buff_size, GFP_KERNEL);
                if (NULL == mbuf)
                {
                    HI_FATAL_VENC("malloc cmd buffer failed\n");
                    return -ENOMEM;

                }
                parg = mbuf;
            }

            err = -EFAULT;
            if (_IOC_DIR(cmd) & _IOC_WRITE)
            {             
                if (copy_from_user(parg, (void __user*)arg, _IOC_SIZE(cmd)))
                {
                    HI_FATAL_VENC("copy_from_user failed, when use ioctl, the para must be a address, cmd=0x%x\n", cmd);
                    goto out;
                }
            }
            break;
    }

    /* call driver */
    err = func(file, cmd, (long)(parg));
    if (err == -ENOIOCTLCMD)
        err = -EINVAL;
    if (err < 0)
        goto out;

    /*  Copy results into user buffer  */
    switch (_IOC_DIR(cmd))
    {
        case _IOC_READ:
        case (_IOC_WRITE | _IOC_READ):
            if (copy_to_user((void __user *)arg, parg, _IOC_SIZE(cmd)))
            {
                HI_FATAL_VENC("copy_to_user failed, when use ioctl, \
                        the para must be a address, cmd=0x%x\n", cmd);
                err = -EFAULT;
            }
        break;
    }

out:
    if (mbuf)
        kfree((HI_VOID *)mbuf);
    return err;
}

HI_VOID HI_PRINT(HI_U32 type,char *file, int line , char * function, HI_CHAR*  msg, ... )
{
    va_list args;
    HI_U32 uTotalChar = 0;

    if ( ((1 << type) & g_VencPrintEnable) == 0 && (type != VENC_ALW) )
        return ;
#if 0
 //获取时间，但用dmesg获取日志已自带时间，暂时可以不用下面的代码
    struct timex  txc;
    struct rtc_time tm;
    do_gettimeofday(&(txc.time));
    rtc_time_to_tm(txc.time.tv_sec,&tm);
    printk("%d-%d-%d %d:%d:%d:%d ",tm.tm_year+1900,tm.tm_mon, tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,txc.time.tv_usec);
#endif

    va_start(args, msg);

    uTotalChar = vsprintf(g_VencPrintMsg, msg, args); //将参数args和msg进行转化形成格式化字符串，即可以显示的字符串。

    va_end(args);

    if (uTotalChar <= 0 || uTotalChar >= 1023)
        return;

  //  printk("%s:<%s:%d:%s>%s",pszMsg[type],file,line,function,g_VencPrintMsg);
  	printk(KERN_ALERT "%s:<%d:%s>%s \n",pszMsg[type],line,function,g_VencPrintMsg);
    return;

}

HI_U32 HI_GetTS()
{
    struct timex  txc;
    struct rtc_time tm;
	HI_U32 uTs;
    do_gettimeofday(&(txc.time));
    rtc_time_to_tm(txc.time.tv_sec,&tm);
	uTs = (tm.tm_min*60 + tm.tm_sec)*1000 + txc.time.tv_usec/1000;
	return uTs;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



