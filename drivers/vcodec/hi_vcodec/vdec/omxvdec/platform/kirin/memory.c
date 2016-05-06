


#include <linux/math64.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/file.h>
#include <linux/major.h>
#include <linux/syscalls.h>

#include "omxvdec.h"
#include "platform.h"
#include "memory.h"
#include "vfmw.h"


/********************************** MACRO *************************************/
#define MAX_ION_MEM_NODE  (800)
#define MAX_CMA_MEM_NODE  (200)
#define MAX_MEM_NAME_LEN  (15)
#define CLIENT_BUF_NAME   "CLIENT"


/********************************* STRUCT *************************************/
typedef struct
{
    HI_U8    is_secure;
    HI_U32   phys_addr;
    HI_VOID *virt_addr;
	HI_U32   size;
    HI_CHAR  node_name[MAX_MEM_NAME_LEN];
    HI_CHAR  zone_name[MAX_MEM_NAME_LEN];
    struct ion_handle *handle;
}ION_MEM_DESC_S;

typedef struct
{
    HI_U32   phys_addr;
    HI_VOID *virt_addr;
	HI_U32   size;
    HI_CHAR  node_name[MAX_MEM_NAME_LEN];
    HI_CHAR  zone_name[MAX_MEM_NAME_LEN];
}CMA_MEM_DESC_S;


/*********************************** VARS *************************************/
struct semaphore   gMemSem;
struct ion_client *gIONClient  = HI_NULL;
HI_S32             gIONNodeNum = 0;
ION_MEM_DESC_S     gIONMemNode[MAX_ION_MEM_NODE];
HI_S32             gCMANodeNum = 0;
CMA_MEM_DESC_S     gCMAMemNode[MAX_CMA_MEM_NODE];


/******************************** LOCAL FUNC **********************************/
/*----------------------------------------
    func: normal memory alloc interface
 ----------------------------------------*/
static HI_S32 VDEC_MEM_AllocNormal(MEM_BUFFER_S *psMBuf, struct ion_handle **phandle)
{
    HI_S32 ret;
    ion_phys_addr_t phys_addr = 0;
    HI_VOID *virt_addr = HI_NULL;
#ifdef HIVDEC_SMMU_SUPPORT
    struct iommu_map_format ion_fmt;
#else
    size_t len = 0;
#endif

#ifdef HIVDEC_SMMU_SUPPORT
    *phandle = ion_alloc(gIONClient, psMBuf->u32Size, PAGE_SIZE, ION_HEAP(ION_SYSTEM_HEAP_ID), 0);
#else
    *phandle = ion_alloc(gIONClient, psMBuf->u32Size, PAGE_SIZE, ION_HEAP(ION_GRALLOC_HEAP_ID), 0);
#endif
    if (IS_ERR_OR_NULL(*phandle))
    {
        OmxPrint(OMX_ERR, "%s failed to alloc ion handle!\n", __func__);
        return HI_FAILURE;
    }

    virt_addr = ion_map_kernel(gIONClient, *phandle);
    if (HI_NULL == virt_addr)
    {
        OmxPrint(OMX_ERR, "%s failed to map kernel virt addr!\n", __func__);
        goto err_ion_map;
    }

#ifdef HIVDEC_SMMU_SUPPORT
    memset(&ion_fmt, 0x00, sizeof(ion_fmt));
    ret = ion_map_iommu(gIONClient, *phandle, &ion_fmt);
    if(ret)
    {
        OmxPrint(OMX_ERR, "ion map mmu failed!\n");
        goto err_ion_phys;
    }
    phys_addr = ion_fmt.iova_start;
#else
    ret = ion_phys(gIONClient, *phandle, &phys_addr, &len);
    if (ret < 0)
    {
        OmxPrint(OMX_ERR, "%s failed to get phy addr!\n", __func__);
        goto err_ion_phys;
    }
#endif

    psMBuf->pStartVirAddr    = virt_addr;
    psMBuf->u32StartPhyAddr  = phys_addr;

    return HI_SUCCESS;

err_ion_phys:
    ion_unmap_kernel(gIONClient, *phandle);
err_ion_map:
    ion_free(gIONClient, *phandle);

    return HI_FAILURE;
}


/*----------------------------------------
    func: normal memory free interface
 ----------------------------------------*/
static HI_VOID VDEC_MEM_FreeNormal(ION_MEM_DESC_S *pMemNode)
{
    // If is client buffer, we should not do free.
    if (0 != strncmp(pMemNode->zone_name, CLIENT_BUF_NAME, MAX_MEM_NAME_LEN))
    {
#ifdef HIVDEC_SMMU_SUPPORT
        ion_unmap_iommu(gIONClient, pMemNode->handle);
#endif
    }
    
    ion_unmap_kernel(gIONClient, pMemNode->handle);
    ion_free(gIONClient, pMemNode->handle);

    return;
}


/*----------------------------------------
    func: secure memory alloc interface
 ----------------------------------------*/
static HI_S32 VDEC_MEM_AllocSecure(MEM_BUFFER_S *psMBuf, struct ion_handle **phandle)
{
    HI_S32              ret = 0;
    ion_phys_addr_t     phys_addr = 0;
    unsigned            allocFlags;
    size_t              len = 0;
    HI_S32              ion_heap;

    ion_heap   = ION_DRM_VCODEC_HEAP_ID;
    allocFlags = ION_FLAG_SECURE_BUFFER;

    *phandle = ion_alloc(gIONClient, psMBuf->u32Size, PAGE_SIZE, 1 << ion_heap, allocFlags);
    if (IS_ERR_OR_NULL(*phandle))
    {
        OmxPrint(OMX_ERR, "%s failed to alloc ion handle!\n", __func__);
        return HI_FAILURE;
    }

	ret = ion_phys(gIONClient, *phandle, &phys_addr, &len);
    if (ret)
    {
        OmxPrint(OMX_ERR, "%s failed to get phy addr!\n", __func__);
        goto err_ion_free;
    }

    psMBuf->u32StartPhyAddr = phys_addr;
    psMBuf->pStartVirAddr   = HI_NULL;
    
    return HI_SUCCESS;

err_ion_free:
    ion_free(gIONClient, *phandle);
    return HI_FAILURE;
}


/*----------------------------------------
    func: secure memory free interface
 ----------------------------------------*/
static HI_VOID VDEC_MEM_FreeSecure(ION_MEM_DESC_S *pMemNode)
{
    ion_free(gIONClient, pMemNode->handle);
    return;
}


/*----------------------------------------
    func: share buffer for IPC
 ----------------------------------------*/
static HI_S32 VDEC_MEM_ShareBuffer(MEM_BUFFER_S *psMBuf, HI_S32 *pShareFd)
{
    HI_S32 i;
    HI_S32 share_fd;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (gIONClient == HI_NULL || psMBuf == HI_NULL || pShareFd == HI_NULL)
    {
        OmxPrint(OMX_ERR, "%s FATAL: gIONClient(%p)/psMBuf(%p)/pShareFd(%p) = NULL\n", __func__, gIONClient, psMBuf, pShareFd);
        goto err_exit;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (psMBuf->u32StartPhyAddr == gIONMemNode[i].phys_addr)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: Ion mem node not found, phy_addr = 0x%x!\n", __func__, psMBuf->u32StartPhyAddr);
        goto err_exit;
    }

    share_fd = ion_share_dma_buf_fd(gIONClient, gIONMemNode[i].handle);
    if (share_fd < 0)
    {
        OmxPrint(OMX_ERR, "%s FATAL: ion_share_dma_buf_fd failed!\n", __func__);
        VDEC_UP_INTERRUPTIBLE(&gMemSem);
        return HI_FAILURE;
    }

    *pShareFd = share_fd;

    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;

err_exit:
	VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/******************************** SHARE FUNC **********************************/
/*----------------------------------------
    func: initialize memory module
 ----------------------------------------*/
HI_S32 VDEC_MEM_Init(HI_VOID)
{
    gIONClient = (struct ion_client *)hisi_ion_client_create("hi_vcodec_ion");
    if (HI_NULL == gIONClient)
    {
        OmxPrint(OMX_ERR, "%s failed to create hi_vcodec ion client!\n", __func__);
        return HI_FAILURE;
    }

    VDEC_INIT_MUTEX(&gMemSem);

	gIONNodeNum = 0;
	gCMANodeNum = 0;
    memset(&gIONMemNode, 0, MAX_ION_MEM_NODE*sizeof(ION_MEM_DESC_S));
    memset(&gCMAMemNode, 0, MAX_CMA_MEM_NODE*sizeof(CMA_MEM_DESC_S));
    
    return HI_SUCCESS;
}


/*----------------------------------------
    func: deinitialize memory module
 ----------------------------------------*/
HI_S32 VDEC_MEM_Exit(HI_VOID)
{
    HI_S32 i;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (gIONClient == HI_NULL)
    {
        OmxPrint(OMX_ERR, "%s FATAL: gIONClient = NULL\n", __func__);
	    VDEC_UP_INTERRUPTIBLE(&gMemSem);
        return HI_FAILURE;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (gIONMemNode[i].phys_addr != 0)
        {
            OmxPrint(OMX_ERR, "Warning: ion mem leak, name %s, zone %s, phy 0x%x, size %d, free now.\n", gIONMemNode[i].node_name, gIONMemNode[i].zone_name, gIONMemNode[i].phys_addr, gIONMemNode[i].size);
            if (1 == gIONMemNode[i].is_secure)
            {
                VDEC_MEM_FreeSecure(&gIONMemNode[i]);
            }
            else
            {
                VDEC_MEM_FreeNormal(&gIONMemNode[i]);
            }
	        memset(&gIONMemNode[i], 0, sizeof(ION_MEM_DESC_S));
        }
    }

    for (i=0; i<MAX_CMA_MEM_NODE; i++)
    {
        if (gCMAMemNode[i].virt_addr != 0)
        {
            OmxPrint(OMX_ERR, "Warning: cma mem leak, name %s, zone %s, phy 0x%x, size %d, free now.\n", gCMAMemNode[i].node_name, gCMAMemNode[i].zone_name, gCMAMemNode[i].phys_addr, gCMAMemNode[i].size);
            kfree(gCMAMemNode[i].virt_addr);
	        memset(&gCMAMemNode[i], 0, sizeof(CMA_MEM_DESC_S));
        }
    }

    ion_client_destroy(gIONClient);
    gIONClient  = HI_NULL;
	gIONNodeNum = 0;
	gCMANodeNum = 0;

	VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;
}

/*----------------------------------------
    func: basic ion alloc & map interface
 ----------------------------------------*/
HI_S32 VDEC_MEM_AllocAndMap(const HI_CHAR *bufname, HI_CHAR *zone_name, MEM_BUFFER_S *psMBuf)
{
    HI_S32 i;
    HI_S32 ret = HI_FAILURE;
    struct ion_handle *handle = HI_NULL;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (psMBuf == NULL)
    {
        OmxPrint(OMX_ERR, "%s param psMBuf = NULL\n", __func__);
        goto err_exit;
    }

    if (HI_NULL != psMBuf->pStartVirAddr)
    {
        OmxPrint(OMX_ERR, "%s param StartVirAddr %p != NULL\n", __func__, psMBuf->pStartVirAddr);
        goto err_exit;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (0 == gIONMemNode[i].phys_addr && HI_NULL == gIONMemNode[i].handle)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: No free ion mem node!\n", __func__);
        goto err_exit;
    }
    
    if (psMBuf->u8IsSecure != 1 && psMBuf->u8IsSecure != 0)
    {
        OmxPrint(OMX_ERR, "%s Warnning!! Buf %s IsSecure %d != 1&0\n", __func__, bufname, psMBuf->u8IsSecure);
    }

    if (1 == psMBuf->u8IsSecure)
    {
        ret = VDEC_MEM_AllocSecure(psMBuf, &handle);
    }
    else
    {
        ret = VDEC_MEM_AllocNormal(psMBuf, &handle);
    }
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s FATAL: alloc memory(size=%d) for %s failed!\n", __func__, psMBuf->u32Size, bufname);
        goto err_exit;
    }

    gIONMemNode[i].handle    = handle;
    gIONMemNode[i].is_secure = psMBuf->u8IsSecure;
    gIONMemNode[i].phys_addr = psMBuf->u32StartPhyAddr;
    gIONMemNode[i].virt_addr = psMBuf->pStartVirAddr;
    gIONMemNode[i].size      = psMBuf->u32Size;

	snprintf(gIONMemNode[i].node_name, MAX_MEM_NAME_LEN, bufname);
	gIONMemNode[i].node_name[MAX_MEM_NAME_LEN-1] = '\0';

	snprintf(gIONMemNode[i].zone_name, MAX_MEM_NAME_LEN, zone_name);
	gIONMemNode[i].zone_name[MAX_MEM_NAME_LEN-1] = '\0';

    gIONNodeNum++;

    OmxPrint(OMX_MEM, "%s %s, size = %d, is_secure = %d\n", __func__, gIONMemNode[i].node_name, gIONMemNode[i].size, gIONMemNode[i].is_secure);

	VDEC_UP_INTERRUPTIBLE(&gMemSem);
	return HI_SUCCESS;

err_exit:
	VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/*----------------------------------------
    func: basic ion unmap & free interface
 ----------------------------------------*/
HI_S32 VDEC_MEM_UnmapAndRelease(MEM_BUFFER_S *psMBuf)
{
    HI_S32 i;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (gIONClient == HI_NULL || psMBuf == HI_NULL)
    {
        OmxPrint(OMX_ERR, "%s FATAL: gIONClient(%p)/psMBuf(%p) = NULL\n", __func__, gIONClient, psMBuf);
        goto err_exit;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (psMBuf->u32StartPhyAddr == gIONMemNode[i].phys_addr)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: Ion mem node not found, phy address = %x.\n", __func__, psMBuf->u32StartPhyAddr);
        goto err_exit;
    }
    
    if (psMBuf->u8IsSecure != 1 && psMBuf->u8IsSecure != 0)
    {
        OmxPrint(OMX_ERR, "%s Warnning!! Buf %s IsSecure %d != 1&0\n", __func__, gIONMemNode[i].node_name, psMBuf->u8IsSecure);
    }
    
    if (1 == psMBuf->u8IsSecure)
    {
        VDEC_MEM_FreeSecure(&gIONMemNode[i]);
    }
    else
    {
        VDEC_MEM_FreeNormal(&gIONMemNode[i]);
    }

    OmxPrint(OMX_MEM, "%s %s, size = %d, is_secure = %d\n", __func__, gIONMemNode[i].node_name, gIONMemNode[i].size, gIONMemNode[i].is_secure);

    memset(&gIONMemNode[i], 0, sizeof(ION_MEM_DESC_S));

    gIONNodeNum = (gIONNodeNum>0)? (gIONNodeNum-1): 0;

	VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;

err_exit:
	VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/*----------------------------------------
    func: map ion buffer
 ----------------------------------------*/
HI_S32 VDEC_MEM_MapKernel(HI_S32 share_fd, MEM_BUFFER_S *psMBuf)
{
    HI_S32 i;
    struct ion_handle *handle    = HI_NULL;
    HI_VOID           *virt_addr = HI_NULL;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if((gIONClient == HI_NULL) || (share_fd < 0) || (psMBuf == HI_NULL))
    {
        OmxPrint(OMX_ERR, "invalid Param for %s!\n", __func__);
        goto err_exit;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (0 == gIONMemNode[i].phys_addr && HI_NULL == gIONMemNode[i].handle)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: Ion mem node not found!\n", __func__);
        goto err_exit;
    }

    handle = ion_import_dma_buf(gIONClient, share_fd);
    if(handle == HI_NULL)
    {
        OmxPrint(OMX_ERR, "%s, get ion handle failed!\n", __func__);
        goto err_exit;
    }

    virt_addr = ion_map_kernel(gIONClient, handle);
    if (HI_NULL == virt_addr)
    {
        OmxPrint(OMX_ERR, "%s failed to map kernel virt addr!\n", __func__);
        goto err_exit;
    }
    psMBuf->pStartVirAddr = virt_addr;

#if 0 //def HIVDEC_SMMU_SUPPORT
    /* Get phy address myself */
    HI_VOID *phys_addr = HI_NULL;
    struct iommu_map_format ion_fmt;

    memset(&ion_fmt, 0x0, sizeof(ion_fmt));
    OmxPrint(OMX_MEM, "Remap iommu\n");
    if(ion_map_iommu(gIONClient, handle, &ion_fmt) != 0)
    {
        OmxPrint(OMX_ERR, "ion map mmu failed!\n");
        ion_unmap_kernel(gIONClient, handle);
        goto err_exit;
    }
    phys_addr = ion_fmt.iova_start;
    if (phys_addr != psMBuf->u32StartPhyAddr)
    {
        OmxPrint(OMX_MEM, "\nAfter %s, phy from 0x%x change to %p\n\n", __func__, psMBuf->u32StartPhyAddr, phys_addr);
    }
    gIONMemNode[i].phys_addr = phys_addr;

#else
    /* Get phy address directly */
    gIONMemNode[i].phys_addr = psMBuf->u32StartPhyAddr;
#endif

    gIONMemNode[i].is_secure = psMBuf->u8IsSecure;
    gIONMemNode[i].handle    = handle;
    gIONMemNode[i].size      = psMBuf->u32Size;

    snprintf(gIONMemNode[i].node_name, MAX_MEM_NAME_LEN, "OMXVDEC_OUT");
    gIONMemNode[i].node_name[MAX_MEM_NAME_LEN-1] = '\0';

    snprintf(gIONMemNode[i].zone_name, MAX_MEM_NAME_LEN, CLIENT_BUF_NAME);
    gIONMemNode[i].zone_name[MAX_MEM_NAME_LEN-1] = '\0';

    gIONNodeNum++;

    OmxPrint(OMX_MEM, "%s %s, size = %d, is_secure = %d\n", __func__, gIONMemNode[i].node_name, gIONMemNode[i].size, gIONMemNode[i].is_secure);

    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;

err_exit:
    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/*----------------------------------------
    func: unmap ion buffer
 ----------------------------------------*/
HI_S32 VDEC_MEM_UnmapKernel(MEM_BUFFER_S *psMBuf)
{
    HI_S32 i;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (gIONClient == HI_NULL || psMBuf == HI_NULL)
    {
        OmxPrint(OMX_ERR, "%s FATAL: gIONClient(%p)/psMBuf(%p) = NULL\n", __func__, gIONClient, psMBuf);
        goto err_exit;
    }

    for (i=0; i<MAX_ION_MEM_NODE; i++)
    {
        if (psMBuf->u32StartPhyAddr == gIONMemNode[i].phys_addr)
        {
            break;
        }
    }

    if (i >= MAX_ION_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: Ion mem node not found!\n", __func__);
        goto err_exit;
    }

    ion_unmap_kernel(gIONClient, gIONMemNode[i].handle);
    
    ion_free(gIONClient, gIONMemNode[i].handle);

    OmxPrint(OMX_MEM, "%s %s, size = %d, is_secure = %d\n", __func__, gIONMemNode[i].node_name, gIONMemNode[i].size, gIONMemNode[i].is_secure);

    memset(&gIONMemNode[i], 0, sizeof(ION_MEM_DESC_S));

    gIONNodeNum = (gIONNodeNum > 0)? (gIONNodeNum-1): 0;

    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;

err_exit:
    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/*----------------------------------------
    func: alloc buffer & share fd for omxvdec
          need share fd
 ----------------------------------------*/
HI_S32 VDEC_MEM_AllocAndShare(const HI_CHAR *bufname, HI_CHAR *zone_name, MEM_BUFFER_S *psMBuf, HI_S32 *pShareFd)
{
    HI_S32 ret;

    if (HI_NULL == psMBuf || HI_NULL == pShareFd)
    {
        OmxPrint(OMX_ERR, "%s param psMBuf(%p)/pShareFd(%p) = NULL\n", __func__, psMBuf, pShareFd);
        return HI_FAILURE;
    }

    ret = VDEC_MEM_AllocAndMap(bufname, zone_name, psMBuf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s FATAL: VDEC_MEM_AllocAndMap failed!\n", __func__);
        return HI_FAILURE;
    }

    ret = VDEC_MEM_ShareBuffer(psMBuf, pShareFd);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s FATAL: VDEC_MEM_ShareBuffer failed!\n", __func__);
        VDEC_MEM_UnmapAndRelease(psMBuf);
        return HI_FAILURE;
    }
 
    return HI_SUCCESS;
}


/*----------------------------------------
    func: close fd & free buffer for omxvdec
          need share fd
 ----------------------------------------*/
HI_S32 VDEC_MEM_CloseAndFree(MEM_BUFFER_S *psMBuf, HI_S32 *pShareFd)
{
    HI_S32 ret;

    if (HI_NULL == psMBuf || HI_NULL == pShareFd)
    {
        OmxPrint(OMX_ERR, "%s param psMBuf(%p)/pShareFd(%p) = NULL\n", __func__, psMBuf, pShareFd);
        return HI_FAILURE;
    }

    if (current->files != NULL)
    {
        sys_close(*pShareFd);
    }
    else
    {
        OmxPrint(OMX_ERR, "%s param current->files = NULL\n", __func__);
    }
    
    ret = VDEC_MEM_UnmapAndRelease(psMBuf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s FATAL: VDEC_MEM_UnmapAndRelease failed!\n", __func__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}


/*----------------------------------------
    func: basic kmalloc & kzalloc interface
 ----------------------------------------*/
HI_S32 VDEC_MEM_KAlloc(const HI_CHAR *bufname, HI_CHAR *zone_name, MEM_BUFFER_S *psMBuf, HI_U8 NeedZero)
{
    HI_S32 i;
    HI_VOID *virt_addr = HI_NULL;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (psMBuf == NULL)
    {
        OmxPrint(OMX_ERR, "%s param psMBuf = NULL\n", __func__);
        goto err_exit;
    }

    if (HI_NULL != psMBuf->pStartVirAddr)
    {
        OmxPrint(OMX_ERR, "%s param StartVirAddr %p != NULL\n", __func__, psMBuf->pStartVirAddr);
        goto err_exit;
    }

    for (i=0; i<MAX_CMA_MEM_NODE; i++)
    {
        if (0 == gCMAMemNode[i].phys_addr && HI_NULL == gCMAMemNode[i].virt_addr)
        {
            break;
        }
    }

    if (i >= MAX_CMA_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: No free cma mem node!\n", __func__);
        goto err_exit;
    }

    if (1 == NeedZero)
    {
        virt_addr = kzalloc(psMBuf->u32Size, GFP_KERNEL|__GFP_DMA);
        if (HI_NULL == virt_addr)
        {
            OmxPrint(OMX_FATAL, "%s call kzalloc size %d failed.\n", __func__, psMBuf->u32Size);
            goto err_exit;
        }
    }
    else
    {
        virt_addr = kmalloc(psMBuf->u32Size, GFP_KERNEL|__GFP_DMA);
        if (HI_NULL == virt_addr)
        {
            OmxPrint(OMX_FATAL, "%s call kmalloc size %d failed.\n", __func__, psMBuf->u32Size);
            goto err_exit;
        }
    }

    psMBuf->pStartVirAddr    = virt_addr;
    psMBuf->u32StartPhyAddr  = __pa(virt_addr);

    snprintf(gCMAMemNode[i].node_name, MAX_MEM_NAME_LEN, bufname);
    gCMAMemNode[i].node_name[MAX_MEM_NAME_LEN-1] = '\0';

    snprintf(gCMAMemNode[i].zone_name, MAX_MEM_NAME_LEN, zone_name);
    gCMAMemNode[i].zone_name[MAX_MEM_NAME_LEN-1] = '\0';

    gCMAMemNode[i].phys_addr = psMBuf->u32StartPhyAddr;
    gCMAMemNode[i].virt_addr = psMBuf->pStartVirAddr;
    gCMAMemNode[i].size      = psMBuf->u32Size;

    gCMANodeNum++;

    OmxPrint(OMX_MEM, "%s %s, size = %d\n", __func__, gCMAMemNode[i].node_name, gCMAMemNode[i].size);

    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;

err_exit:
    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/*----------------------------------------
    func: basic mem free interface
 ----------------------------------------*/
HI_S32 VDEC_MEM_KFree(MEM_BUFFER_S *psMBuf)
{
    HI_S32 i;

    VDEC_DOWN_INTERRUPTIBLE(&gMemSem);

    if (psMBuf == HI_NULL)
    {
        OmxPrint(OMX_ERR, "%s FATAL: psMBuf = NULL\n", __func__);
        goto err_exit;
    }

    for (i=0; i<MAX_CMA_MEM_NODE; i++)
    {
        if (psMBuf->pStartVirAddr == gCMAMemNode[i].virt_addr)
        {
            break;
        }
    }

    if (i >= MAX_CMA_MEM_NODE)
    {
        OmxPrint(OMX_ERR, "%s FATAL: cma mem node not found, phy address = %x.\n", __func__, psMBuf->u32StartPhyAddr);
	    goto err_exit;
    }

    kfree(gCMAMemNode[i].virt_addr);

    OmxPrint(OMX_MEM, "%s %s, size = %d\n", __func__, gCMAMemNode[i].node_name, gCMAMemNode[i].size);

    memset(&gCMAMemNode[i], 0, sizeof(ION_MEM_DESC_S));

    gCMANodeNum = (gCMANodeNum>0)? (gCMANodeNum-1): 0;

	VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_SUCCESS;

err_exit:
    VDEC_UP_INTERRUPTIBLE(&gMemSem);
    return HI_FAILURE;
}


/*----------------------------------------
    func: alloc & map buffer for vfmw
 ----------------------------------------*/
HI_S32 VDEC_MEM_VfmwMalloc(HI_S8 *pMemName, HI_U32 len, HI_U32 align, HI_VOID *pArgs)
{
    HI_U8 NeedZero = 0;
    HI_S32 ret = HI_FAILURE;
    MEM_BUFFER_S stMBuffer;
	MEM_DESC_S *pMemDesc = (MEM_DESC_S *)pArgs;

    if (HI_NULL == pMemName || HI_NULL == pMemDesc)
    {
        OmxPrint(OMX_ERR, "%s param MemName(%p)/pMemDesc(%p) = NULL \n", __func__, pMemName, pMemDesc);
        return HI_FAILURE;
    }

    memset(&stMBuffer, 0, sizeof(MEM_BUFFER_S));
    stMBuffer.u8IsSecure = pMemDesc->IsSecure;
    stMBuffer.u32Size    = len;

    if (MEM_ION == pMemDesc->MemType)
    {
        ret = VDEC_MEM_AllocAndMap(pMemName, "VFMW", &stMBuffer);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_ERR, "%s alloc %s size %d failed!\n", __func__, pMemName, len);
            return HI_FAILURE;
        }
    }
    else if (MEM_CMA == pMemDesc->MemType || MEM_CMA_ZERO == pMemDesc->MemType)
    {
        NeedZero = (MEM_CMA_ZERO == pMemDesc->MemType)? 1:0;
        ret = VDEC_MEM_KAlloc(pMemName, "VFMW", &stMBuffer, NeedZero);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_ERR, "%s alloc %s size %d failed!\n", __func__, pMemName, len);
            return HI_FAILURE;
        }
    }
    else
    {
        OmxPrint(OMX_ERR, "%s unsupport mem type %d of %s.\n", __func__, pMemDesc->MemType, pMemName);
    }

    pMemDesc->PhyAddr = stMBuffer.u32StartPhyAddr;
    pMemDesc->VirAddr = stMBuffer.pStartVirAddr;
    pMemDesc->Length  = stMBuffer.u32Size;

    return HI_SUCCESS;
}


/*----------------------------------------
    func: unmap & free buffer for vfmw
 ----------------------------------------*/
HI_VOID VDEC_MEM_VfmwFree(HI_VOID *pArgs)
{
    MEM_BUFFER_S stMBuffer;
	MEM_DESC_S *pMemDesc = (MEM_DESC_S *)pArgs;

    if (HI_NULL == pMemDesc)
    {
        OmxPrint(OMX_ERR, "%s param pMemDesc(%p) = NULL \n", __func__, pMemDesc);
        return;
    }

    memset(&stMBuffer, 0, sizeof(MEM_BUFFER_S));
    stMBuffer.u32StartPhyAddr = pMemDesc->PhyAddr;
    stMBuffer.pStartVirAddr   = pMemDesc->VirAddr;
    stMBuffer.u32Size         = pMemDesc->Length;

    if (MEM_ION == pMemDesc->MemType)
    {
        VDEC_MEM_UnmapAndRelease(&stMBuffer);
    }
    else if (MEM_CMA == pMemDesc->MemType || MEM_CMA_ZERO == pMemDesc->MemType)
    {
        VDEC_MEM_KFree(&stMBuffer);
    }
    else
    {
        OmxPrint(OMX_ERR, "%s unsupport mem type %d of %x.\n", __func__, pMemDesc->MemType, pMemDesc->PhyAddr);
    }

    return;
}


/*----------------------------------------
    func: memory read proc entry
 ----------------------------------------*/
HI_VOID VDEC_MEM_Read_Proc(HI_VOID *pParam, HI_VOID *v)
{
    HI_S32 i = 0;
    HI_U32 total_size = 0;
    struct seq_file *p = (struct seq_file *)pParam;

    total_size = 0;
    PROC_PRINT(p, "------------------------- ION Memory -------------------------\n\n");
    if (gIONNodeNum > 0)
    {
	    PROC_PRINT(p, " %-13s%-10s%-10s%-10s%-20s\n\n", "NAME", "OWNER", "PHYADDR", "SIZE", "VIRADDR");
    	for (i=0; i<MAX_ION_MEM_NODE; i++)
    	{
    	    if (gIONMemNode[i].phys_addr != 0)
    	    {
                PROC_PRINT(p, " %-13s%-10s%-10x%-10d%-20p%-10s\n",
                          gIONMemNode[i].node_name,
                          gIONMemNode[i].zone_name,
                          gIONMemNode[i].phys_addr,
                          gIONMemNode[i].size,
                          gIONMemNode[i].virt_addr,
                          (1==gIONMemNode[i].is_secure)?"(SEC)":"");

				total_size += gIONMemNode[i].size;
    	    }
    	}
        PROC_PRINT(p, "\n--------------------------------------------------------------\n\n");
    }
    PROC_PRINT(p, "TotalNum         :%-10d\n", gIONNodeNum);
    PROC_PRINT(p, "TotalSize        :%-10d\n", total_size);
    PROC_PRINT(p, "\n--------------------------------------------------------------\n\n");

    total_size = 0;
    PROC_PRINT(p, "------------------------- CMA Memory -------------------------\n\n");
    if (gCMANodeNum > 0)
    {
	    PROC_PRINT(p, " %-13s%-10s%-10s%-10s%-20s\n\n", "NAME", "OWNER", "PHYADDR", "SIZE", "VIRADDR");
    	for (i=0; i<MAX_CMA_MEM_NODE; i++)
    	{
    	    if (gCMAMemNode[i].phys_addr != 0)
    	    {
                PROC_PRINT(p, " %-13s%-10s%-10x%-10d%-20p\n",
                          gCMAMemNode[i].node_name,
                          gCMAMemNode[i].zone_name,
                          gCMAMemNode[i].phys_addr,
                          gCMAMemNode[i].size,
                          gCMAMemNode[i].virt_addr);

				total_size += gCMAMemNode[i].size;
    	    }
    	}
        PROC_PRINT(p, "\n--------------------------------------------------------------\n\n");
    }
    PROC_PRINT(p, "TotalNum         :%-10d\n", gCMANodeNum);
    PROC_PRINT(p, "TotalSize        :%-10d\n", total_size);
    PROC_PRINT(p, "\n--------------------------------------------------------------\n\n");

    return;
}


