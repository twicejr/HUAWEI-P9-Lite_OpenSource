/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rf4CiyMWI2FFurqFcI4iZgZ0uI5aMsvqKpd7kUnhbTsy7ayFNbcl7GAGq1C9
OS6qI72nreUW/5jMSRDWkj3rLX4pnowCVwEMGWHYQIMsew75fF1hGja8YmhXYJWHE+wBO8EA
yl21RjEwph9iL2KaqqSfR/htEq0R5bsJSJZPFK3nUdXOFpetU5mrcs2UtCvHcA==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/































/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vfmw_osal.c
    版 本 号   : 初稿
    作    者   :
    生成日期   :
    最近修改   :
    功能描述   : 为vfmw定制的操作系统抽象模块


    修改历史   :
    1.日    期 : 2009-05-12
    作    者   :
    修改内容   :

******************************************************************************/

#include "public.h"
#include "linux_kernel_osal.h"
#include "linux_kernel_proc.h"


#ifdef ENV_ARMLINUX_KERNEL

/* SpinLock */
OSAL_IRQ_SPIN_LOCK g_SpinLock_Thread;
OSAL_IRQ_SPIN_LOCK g_SpinLock_Record;
OSAL_IRQ_SPIN_LOCK g_SpinLock_VoQueue;
OSAL_IRQ_SPIN_LOCK g_SpinLock_Fsp;
OSAL_IRQ_SPIN_LOCK g_SpinLock_Destroy;

/* Mutext */
OSAL_TASK_MUTEX    g_IntEvent;

/* Semaphore */
OSAL_SEMA          g_VfmwSem;

/* Extern */
extern Vfmw_Osal_Func_Ptr g_vfmw_osal_fun_ptr;
extern EXT_FN_MEM_MALLOC  g_pfnMemMalloc;
extern EXT_FN_MEM_FREE    g_pfnMemFree;
extern UINT8             *pY,*pUl,*pVl;


/************************************************************************/
/* 打印接口定义                                                         */
/************************************************************************/
#define OSAL_Print  printk

/************************************************************************/
/* OSAL_GetTimeInMs():  获取系统时间                                    */
/************************************************************************/
UINT32 OSAL_GetTimeInMs(VOID)
{
    UINT64 SysTime;

    SysTime = sched_clock();
    do_div(SysTime, 1000000);
    
    return (UINT32)SysTime;
}

UINT32 OSAL_GetTimeInUs(VOID)
{
    UINT64 SysTime;

    SysTime = sched_clock();
    do_div(SysTime, 1000);
    
    return (UINT32)SysTime;
}

/************************************************************************/
/*  创建任务                                                            */
/************************************************************************/
SINT32 OSAL_CreateTask( OSAL_TASK *pTask, SINT8 TaskName[], VOID *pTaskFunction )
{
    *pTask = kthread_create(pTaskFunction, (VOID *)NULL, TaskName);

    if (NULL == *pTask || IS_ERR(*pTask))
    {
        dprint(PRN_FATAL, "can not create thread!\n");
        return ( VF_ERR_SYS );
    }

    wake_up_process(*pTask);
    return OSAL_OK;
}

/************************************************************************/
/* 激活任务                                                             */
/************************************************************************/
inline SINT32 OSAL_WakeupTask( OSAL_TASK *pTask )
{
    return OSAL_OK;
}

/************************************************************************/
/* 销毁任务                                                             */
/************************************************************************/
inline SINT32 OSAL_DeleteTask(OSAL_TASK *pTask)
{
    return OSAL_OK;
}

/************************************************************************/
/* 初始化事件                                                           */
/************************************************************************/
inline SINT32 OSAL_InitEvent( OSAL_EVENT *pEvent, SINT32 InitVal )
{
    pEvent->flag = InitVal;
    init_waitqueue_head( &(pEvent->queue_head) );
    return OSAL_OK;
}

/************************************************************************/
/* 发出事件                                                             */
/************************************************************************/
inline SINT32 OSAL_GiveEvent( OSAL_EVENT *pEvent )
{
    pEvent->flag = 1;
    wake_up_interruptible ( &(pEvent->queue_head) );

	return OSAL_ERR;
}

/************************************************************************/
/* 等待事件                                                             */
/* 事件发生返回OSAL_OK，超时返回OSAL_ERR 若condition不满足就阻塞等待    */
/************************************************************************/
inline SINT32 OSAL_WaitEvent( OSAL_EVENT *pEvent, SINT32 msWaitTime )
{
    SINT32 l_ret;

    l_ret = wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime) );

    pEvent->flag = 0;//(pEvent->flag>0)? (pEvent->flag-1): 0;

    return (l_ret == 0) ? OSAL_OK : OSAL_ERR;
}

/************************************************************************/
/*  寄存器映射                                                          */
/************************************************************************/
inline SINT8 *OSAL_RegisterMap(UADDR  PhyAddr, UINT32 RegByteLen)
{
	return (SINT8*)ioremap_nocache(PhyAddr, RegByteLen);
}

/************************************************************************/
/*  寄存器去映射                                                        */
/************************************************************************/
inline VOID OSAL_RegisterUnMap(UINT8 *VirAddr)
{
    iounmap(VirAddr);
    return;
}

/************************************************************************/
/*  打开文件                                                            */
/************************************************************************/
inline OSAL_FILE *OSAL_FileOpen(const char *filename, int flags, int mode)
{
    struct file *filp = filp_open(filename, flags, mode);
    return (IS_ERR(filp)) ? NULL : filp;
}

/************************************************************************/
/*  关闭文件                                                            */
/************************************************************************/
inline VOID OSAL_FileClose(struct file *filp)
{
    if (filp)
    {
        filp_close(filp, NULL);
    }
}

/************************************************************************/
/*  读取文件                                                            */
/************************************************************************/
SINT32 OSAL_FileRead(char *buf, unsigned int len, struct file *filp)
{
    int readlen;
    mm_segment_t oldfs;

    if (filp == NULL)
    {
        return -ENOENT;
    }

    if (filp->f_op->read == NULL)
    {
        return -ENOSYS;
    }

    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) == 0)
    {
        return -EACCES;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    readlen = filp->f_op->read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return readlen;
}

/************************************************************************/
/*  写入文件                                                            */
/************************************************************************/
SINT32 OSAL_FileWrite(char *buf, int len, struct file *filp)
{
    int writelen;
    mm_segment_t oldfs;

    if (filp == NULL)
    {
        return -ENOENT;
    }

    if (filp->f_op->write == NULL)
    {
        return -ENOSYS;
    }

    if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
    {
        return -EACCES;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    writelen = filp->f_op->write(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return writelen;
}

/************************************************************************/
/*  Tile 格式YUV存储                                                    */
/************************************************************************/
VOID OSAL_WriteYuv_Tile( OSAL_FILE *fpYuv, UADDR YPhyAddr, UADDR CPhyAddr, UINT32 Width, UINT32 Height, UINT32 PicStructure, UINT32 Stride, UINT32 chroma_idc,
                          UINT32 LeftOffset,UINT32 RightOffset,UINT32 TopOffset,UINT32 BottomOffset)
{
    UINT32 i,j;
    UINT32 chrom_width = Width/2;
    UINT32 chrom_height = Height/2;
	UINT8 *dst, *src, *tmp;
	SINT32 start;
	UINT32 disp_width;
	UINT32 disp_height;
	UINT8 *pPicAddr;
	UINT32 disp_chroma_width;
	UINT32 disp_chroma_height;
	UINT8 *pCbPicAddr;
	UINT8 *pCrPicAddr;
    UINT8 *Yaddress = NULL;
    UINT8 *Caddress = NULL;

    if (pY == NULL ||  pUl == NULL || pVl== NULL)
    {
       dprint(PRN_ALWS, "%s FATAL: pY(%p), pUl(%p), pVl(%p)\n", __func__, pY, pUl, pVl);
       return;
    }

    Yaddress = (UINT8 *)MEM_Phy2Vir(YPhyAddr);
    if (NULL == Yaddress)
    {
       dprint(PRN_ALWS, "%s FATAL: YPhyAddr = %x, Yaddress = NULL\n", __func__, YPhyAddr);
       return;
    }

    Caddress = (UINT8 *)MEM_Phy2Vir(CPhyAddr);
    if (NULL == Caddress)
    {
       dprint(PRN_ALWS, "%s FATAL: CPhyAddr = %x, Caddress = NULL\n", __func__, CPhyAddr);
       return;
    }

	disp_width  = Width - LeftOffset - RightOffset;
	disp_height = Height - TopOffset - BottomOffset;
	disp_chroma_width  = disp_width/2;
	disp_chroma_height = disp_height/2;

    if (fpYuv)
    {
       dprint(PRN_ALWS, "VFMW: WriteBigTileYuv %dx%d...\n", disp_width, disp_height);
       if (PicStructure == 0 || PicStructure == 3)
       {
         /*Y*/
         for(i=0; i<Height; i++)
         {
             for(j=0;j<Width;j+=256)
             {
                dst  = (unsigned char*)(pY + Width*i + j);
                src =  Yaddress + Stride*(i/16)+(i%16)*256 + (j/256)*256*16;
				memcpy(dst,src,256);
             }
         }

         if (disp_width == Width && disp_height == Height)
         {
		     OSAL_FileWrite(pY,Width*Height, fpYuv);
         }
         else
         {
             pPicAddr = pY + TopOffset*Width + LeftOffset;
             for(i=0;i<disp_height;i++)
             {
             	OSAL_FileWrite(pPicAddr, disp_width, fpYuv );
             	pPicAddr = pPicAddr + Width;
             }
         }

         /*UV*/
         for(i=0;i<Height/2;i++)
         {
             for(j=0;j<Width;j+=256)
             {
                 dst  = (unsigned char*)(pY + Width*i + j);
                 src =  Caddress + (Stride/2)*(i/8)+(i%8)*256 + (j/256)*256*8;
                 memcpy(dst,src,256);
             }
         }
 		 tmp = pY;
         if (1 == chroma_idc)
         {
             for (i=0;i<chrom_height;i++)
             {
                  for (j=0;j<chrom_width;j++)
                  {
                      pVl[i*chrom_width+j] = tmp[2*j];
                      pUl[i*chrom_width+j] = tmp[2*j+1];
                  }
                  tmp += Width;
             }
         }
         else if (0 == chroma_idc)    //yuv400
         {
 			memset(pVl, 0x80, 1024*1024);
 			memset(pUl, 0x80, 1024*1024);
         }
         else
         {
             //add other
         }

         if (disp_width == Width && disp_height == Height)
         {
            OSAL_FileWrite(pUl, chrom_width*chrom_height, fpYuv);
            OSAL_FileWrite(pVl, chrom_width*chrom_height, fpYuv);
         }
         else
         {
         	pCbPicAddr = pUl+(TopOffset/2)*chrom_width + LeftOffset/2;
         	pCrPicAddr = pVl+(TopOffset/2)*chrom_width + LeftOffset/2;
         	for(i=0;i<disp_chroma_height;i++)
         	{
         		OSAL_FileWrite(pCbPicAddr, disp_chroma_width, fpYuv );
         		pCbPicAddr = pCbPicAddr + chrom_width;
         	}
         	for(i=0;i<disp_chroma_height;i++)
         	{
         		OSAL_FileWrite(pCrPicAddr, disp_chroma_width, fpYuv );
         		pCrPicAddr = pCrPicAddr + chrom_width;
         	}
         }
       }
 	   else
 	   {
         if (PicStructure == 1)
         {
           start = 0;
         }
         else
         {
           start = 1;
         }

         /*Y*/
         for(i=start;i<Height;i+=2)
         {
            for(j=0;j<Width;j+=256)
            {
              dst  = (unsigned char*)(pY + Width*(i/2) + j);
              src =  Yaddress + Stride*(i/16)+ ((i%16)*256 )+ (j/256)*256*16;
              memcpy(dst,src,256);
            }
         }
         OSAL_FileWrite(pY,Width*Height/2, fpYuv);

         /*UV*/
         for(i=0;i<Height/2;i++)
         {
            for(j=0;j<Width;j+=256)
            {
              dst  = (unsigned char*)(pY + Width*i + j);
              src =  Caddress + (Stride/2)*(i/8)+ ((i%8)*256 ) + (j/256)*256*8;
              memcpy(dst,src,256);
            }
         }
         tmp = pY+start*Width;
         if (1 == chroma_idc)
         {
            for (i=0;i<chrom_height;i+=2)
            {
               for (j=0;j<chrom_width;j++)
               {
                   pVl[(i/2)*chrom_width+j] = tmp[2*j];
                   pUl[(i/2)*chrom_width+j] = tmp[2*j+1];
               }
               tmp+= Width*2;
            }
         }
         else if (0 == chroma_idc)    //yuv400
         {
            for (i=start;i<chrom_height;i+=2)
            {
            }
            memset(pVl, 0x80, 1024*1024);
            memset(pUl, 0x80, 1024*1024);
         }
         else
         {
            //add other
         }
         OSAL_FileWrite(pUl, chrom_width*chrom_height/2, fpYuv);
         OSAL_FileWrite(pVl, chrom_width*chrom_height/2, fpYuv);
       }
    }
}

/************************************************************************/
/*  Linear 格式YUV存储                                                  */
/************************************************************************/
VOID OSAL_WriteYuv_Linear( OSAL_FILE *fpYuv, UADDR YPhyAddr, UADDR CPhyAddr, UINT32 Width, UINT32 Height,  UINT32 Stride, UINT32 chroma_idc)
{
    UINT32 i, j;
    UINT32 chrom_width = Width/2;
    UINT32 chrom_height = Height/2;
    UINT8 *Yaddress = NULL;
    UINT8 *Caddress = NULL;

    if (pY == NULL ||  pUl == NULL || pVl== NULL)
    {
       dprint(PRN_ALWS, "%s FATAL: pY(%p), pUl(%p), pVl(%p)\n", __func__, pY, pUl, pVl);
       return;
    }

    Yaddress = (UINT8 *)MEM_Phy2Vir(YPhyAddr);
    if (NULL == Yaddress)
    {
       dprint(PRN_ALWS, "%s FATAL: YPhyAddr = %x, Yaddress = NULL\n", __func__, YPhyAddr);
       return;
    }

    Caddress = (UINT8 *)MEM_Phy2Vir(CPhyAddr);
    if (NULL == Caddress)
    {
       dprint(PRN_ALWS, "%s FATAL: CPhyAddr = %x, Caddress = NULL\n", __func__, CPhyAddr);
       return;
    }

    /*write y*/
    for (i=0; i<Height; i++)
    {
        if(Width != OSAL_FileWrite(Yaddress,  Width, fpYuv))
        {
            dprint(PRN_ALWS, "%s %d: fwrite fail!\n", __func__, __LINE__);
        }
        Yaddress += Stride;
    }
    for (i=0; i<chrom_height; i++)
    {
        for (j=0; j<chrom_width; j++)
        {
            pVl[i*chrom_width+j] = Caddress[2*j];
            pUl[i*chrom_width+j] = Caddress[2*j+1];
        }

        Caddress += Stride;
    }
    if(chrom_width*chrom_height != OSAL_FileWrite(pUl,  chrom_width*chrom_height, fpYuv))
    {
        dprint(PRN_ALWS, "%s %d: fwrite fail!\n", __func__, __LINE__);
    }

    if(chrom_width*chrom_height != OSAL_FileWrite(pVl,  chrom_width*chrom_height, fpYuv))
    {
        dprint(PRN_ALWS, "%s %d: fwrite fail!\n", __func__, __LINE__);
    }
}

/************************************************************************/
/*  YUV存储接口                                                         */
/************************************************************************/
VOID OSAL_WriteYuv(VID_STD_E eVidStd, IMAGE *pImage, OSAL_FILE *fpYuv, SINT32 WithCrop)
{
    UINT32 chroma_idc;
    UINT32 left_offset,right_offset,top_offset,bottom_offset;
    
    if (pImage != NULL)
    {
        chroma_idc    = ((pImage->format >> 2) & 0x07) == 0 ? 1 : 0;
        left_offset   = (WithCrop != 0)? pImage->left_offset:   0;
        right_offset  = (WithCrop != 0)? pImage->right_offset:  0;
        top_offset    = (WithCrop != 0)? pImage->top_offset:    0;
        bottom_offset = (WithCrop != 0)? pImage->bottom_offset: 0;

        if (eVidStd == VFMW_H263 || eVidStd == VFMW_SORENSON)
        {
            OSAL_WriteYuv_Linear(fpYuv, pImage->luma_phy_addr, pImage->chrom_phy_addr,
                                 pImage->image_width, pImage->image_height, pImage->image_stride, chroma_idc);
        }
        else
        {
            OSAL_WriteYuv_Tile(fpYuv, pImage->luma_phy_addr, pImage->chrom_phy_addr,
                               pImage->image_width,pImage->image_height, 0, pImage->image_stride,  
                               chroma_idc, left_offset, right_offset, top_offset, bottom_offset);
        }
    }

    return;
}

/************************************************************************/
/*  信号量初始化                                                        */
/************************************************************************/
inline VOID OSAL_SEMA_INTIT(OSAL_SEMA *pSem)
{
    sema_init(pSem, 1);
}

/************************************************************************/
/*  获取信号量                                                          */
/************************************************************************/
inline SINT32 OSAL_DOWN_INTERRUPTIBLE(OSAL_SEMA *pSem)
{
    return down_interruptible(pSem);
}

/************************************************************************/
/*  释放信号量                                                          */
/************************************************************************/
inline VOID OSAL_UP(OSAL_SEMA *pSem)
{
    up(pSem);
}

/************************************************************************/
/* 锁初始化                                                             */
/************************************************************************/
inline VOID OSAL_SpinLockIRQInit(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    spin_lock_init(&pIntrMutex->irq_lock);
    pIntrMutex->isInit = 1;
}

/************************************************************************/
/* 加锁                                                                 */
/************************************************************************/
inline SINT32 OSAL_SpinLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    if(pIntrMutex->isInit == 0)
    {
        spin_lock_init(&pIntrMutex->irq_lock);  
        pIntrMutex->isInit = 1;
    }
    spin_lock_irqsave(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);

    return OSAL_OK;
}

/************************************************************************/
/* 解锁                                                                 */
/************************************************************************/
inline SINT32 OSAL_SpinUnLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    spin_unlock_irqrestore(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);

    return OSAL_OK;
}

/************************************************************************/
/* 编译不做优化标志                                                     */
/************************************************************************/
inline VOID OSAL_Mb(VOID)
{
    mb();
}

/************************************************************************/
/* 盲等待 (微秒)                                                        */
/************************************************************************/
inline VOID OSAL_uDelay(ULONG usecs)
{
    udelay(usecs);
}

/************************************************************************/
/* 休眠等待 (毫秒)                                                      */
/************************************************************************/
inline VOID OSAL_mSleep(UINT32 msecs)
{
    msleep(msecs);
}

/************************************************************************/
/* 注册中断                                                             */
/************************************************************************/
inline SINT32 OSAL_RequestIrq(UINT32 irq, OSAL_IRQ_HANDLER_t handler, ULONG flags, const char *name, VOID *dev)
{
    return request_irq(irq, (irq_handler_t)handler, flags, name, dev);
}

/************************************************************************/
/* 释放中断                                                             */
/************************************************************************/
inline VOID OSAL_FreeIrq(UINT32 irq, VOID *dev)
{
    free_irq(irq, dev);
}

/************************************************************************/
/* 申请虚拟内存（可能非物理连续）                                       */
/************************************************************************/
inline VOID *OSAL_AllocVirMem(SINT32 Size)
{
	return vmalloc(Size);
}

/************************************************************************/
/* 释放虚拟内存（可能非物理连续）                                       */
/************************************************************************/
inline VOID OSAL_FreeVirMem(VOID *p)
{
    if (p)
    {
		vfree(p);
    }
}

/************************************************************************/
/*  内存申请                                                            */
/************************************************************************/
SINT32 OSAL_MemMalloc(UINT8 *MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc)
{
    SINT32 ret = OSAL_ERR;
    MEM_DESC_S AllocMem;
    
    if (NULL == g_pfnMemMalloc || NULL == pMemDesc)
    {
        dprint(PRN_FATAL, "Alloc mem %s failed, g_pfnMemMalloc(%p)/pMemDesc(%p) = NULL\n", MemName, g_pfnMemMalloc, pMemDesc);
        return OSAL_ERR;
    }
    
    memset(&AllocMem, 0, sizeof(AllocMem));
    AllocMem.MemType  = pMemDesc->MemType;
    AllocMem.IsSecure = pMemDesc->IsSecure;
    
    ret = g_pfnMemMalloc( MemName, len, align, (VOID *)&AllocMem);
    if( ret != 0 )
    {
		dprint(PRN_FATAL, "Alloc mem %s failed, size = %d\n", MemName, len);
		return OSAL_ERR;
    }
    else
    {
        pMemDesc->PhyAddr = AllocMem.PhyAddr;
        pMemDesc->VirAddr = AllocMem.VirAddr;
        pMemDesc->Length  = AllocMem.Length;
        return OSAL_OK;
    }
}

/************************************************************************/
/*  内存释放                                                            */
/************************************************************************/
SINT32 OSAL_MemFree(MEM_DESC_S *pMemDesc)
{
    if (g_pfnMemFree == NULL)
    {
        dprint(PRN_FATAL, "Free mem %x failed, mem_free = NULL\n", pMemDesc->PhyAddr);
        return OSAL_ERR;
    }	

    if (NULL == pMemDesc)
    {
        dprint(PRN_FATAL, "Free mem %x failed, param pMemDesc = NULL\n", pMemDesc->PhyAddr);
        return OSAL_ERR;
    }
    
    g_pfnMemFree((VOID *)pMemDesc);

    return OSAL_OK;	
}	

/************************************************************************/
/*  内存映射                                                            */
/************************************************************************/
inline UINT8 *OSAL_Mmap(UADDR phyaddr, UINT32 len)
{
    /*由于相关内存操作由外部进行，且不会进入软解码分支，因此什么都不做即可*/
    return NULL;
}

/************************************************************************/
/*  内存映射带cache                                                     */
/************************************************************************/
inline UINT8 *OSAL_MmapCache(UADDR phyaddr, UINT32 len)
{
    /*由于相关内存操作由外部进行，且不会进入软解码分支，因此什么都不做即可*/
    return NULL;
}

/************************************************************************/
/*  内存去映射                                                       */
/************************************************************************/
inline VOID OSAL_Munmap(UINT8 *p )
{
    /*由于相关内存操作由外部进行，且不会进入软解码分支，因此什么都不做即可*/
    return;
}

/************************************************************************/
/*  根据名称获取锁实体                                                  */
/************************************************************************/
OSAL_IRQ_SPIN_LOCK *GetSpinLockByEnum(SpinLockType LockType)
{
    OSAL_IRQ_SPIN_LOCK *pSpinLock = NULL;

    switch (LockType)
    {
        case G_SPINLOCK_THREAD:
            pSpinLock = &g_SpinLock_Thread;
            break;

        case G_SPINLOCK_RECORD:
            pSpinLock = &g_SpinLock_Record;
            break;

        case G_SPINLOCK_VOQUEUE:
            pSpinLock = &g_SpinLock_VoQueue;
            break;

        case G_SPINLOCK_FSP:
            pSpinLock = &g_SpinLock_Fsp;
            break;

        case G_SPINLOCK_DESTROY:
            pSpinLock = &g_SpinLock_Destroy;
            break;

        default:
            dprint(PRN_ERROR, "%s unkown SpinLockType %d\n", __func__, LockType);
            break;
    }

    return pSpinLock;
}

/************************************************************************/
/*  根据枚举进行锁初始化                                                */
/************************************************************************/
VOID OSAL_SpinLockInit(SpinLockType LockType)
{
    OSAL_IRQ_SPIN_LOCK *pSpinLock = NULL;

    pSpinLock = GetSpinLockByEnum(LockType);

    OSAL_SpinLockIRQInit(pSpinLock);
}

/************************************************************************/
/*  根据枚举进行加锁                                                    */
/************************************************************************/
SINT32 OSAL_SpinLock(SpinLockType LockType)
{
    OSAL_IRQ_SPIN_LOCK *pSpinLock = NULL;

    pSpinLock = GetSpinLockByEnum(LockType);

    return OSAL_SpinLockIRQ(pSpinLock);
}

/************************************************************************/
/*  根据枚举进行解锁                                                    */
/************************************************************************/

SINT32 OSAL_SpinUnLock(SpinLockType LockType)
{
    OSAL_IRQ_SPIN_LOCK *pSpinLock = NULL;

    pSpinLock = GetSpinLockByEnum(LockType);

    return OSAL_SpinUnLockIRQ(pSpinLock);
}

/************************************************************************/
/*  根据名称获取信号量实体                                              */
/************************************************************************/
OSAL_SEMA *GetSemByEnum(SemType Sem)
{
    OSAL_SEMA *pSem = NULL;

    switch (Sem)
    {
        case G_VfmwSem:
            pSem = &g_VfmwSem;
            break;

        default:
            dprint(PRN_ERROR, "%s unkown SemType %d\n", __func__, Sem);
            break;
    }

    return pSem;
}

/************************************************************************/
/*  根据枚举进行信号量初始化                                            */
/************************************************************************/
VOID OSAL_SemInit(SemType Sem)
{
    OSAL_SEMA *pSem = NULL;

    pSem = GetSemByEnum(Sem);

    OSAL_SEMA_INTIT(pSem);
}

/************************************************************************/
/*  根据枚举进行获取信号量                                              */
/************************************************************************/
SINT32 OSAL_SemDown(SemType Sem)
{
    OSAL_SEMA *pSem = NULL;

    pSem = GetSemByEnum(Sem);

    return OSAL_DOWN_INTERRUPTIBLE(pSem);
}

/************************************************************************/
/*  根据枚举进行释放信号量                                              */
/************************************************************************/
VOID OSAL_SemUp(SemType Sem)
{
    OSAL_SEMA *pSem = NULL;

    pSem = GetSemByEnum(Sem);

    OSAL_UP(pSem);
}

/************************************************************************/
/*  根据枚举进行事件和等待队列初始化                                    */
/************************************************************************/
SINT32 OSAL_InitWaitQue(MutexType mutextType, SINT32 initVal)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutextType)
    {
        case G_INTEVENT:
            retVal = OSAL_InitEvent(&g_IntEvent, initVal);
            break;

        default:
            break;
    }

    return retVal;
}

/************************************************************************/
/*  根据枚举发送事情唤醒等待队列                                        */
/************************************************************************/
SINT32 OSAL_WakeupWaitQue(MutexType mutexType)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutexType)
    {
        case G_INTEVENT:
            retVal = OSAL_GiveEvent(&g_IntEvent);
            break;

        default:
            break;
    }

    return retVal;
}

/************************************************************************/
/*  根据枚举进入队列等待事件                                            */
/************************************************************************/
SINT32 OSAL_WaitWaitQue(MutexType mutexType, SINT32 waitTimeInMs)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutexType)
    {
        case G_INTEVENT:
            retVal = OSAL_WaitEvent(&g_IntEvent, waitTimeInMs);
            break;
        default:
            break;
    }

    return retVal;
}

/************************************************************************/
/*  初始化内核接口                                                      */
/************************************************************************/
VOID OSAL_InitInterface(VOID)
{
    memset(&g_vfmw_osal_fun_ptr, 0, sizeof(Vfmw_Osal_Func_Ptr));
    
    g_vfmw_osal_fun_ptr.pfun_Osal_GetTimeInMs         = OSAL_GetTimeInMs;
    g_vfmw_osal_fun_ptr.pfun_Osal_GetTimeInUs         = OSAL_GetTimeInUs;
    g_vfmw_osal_fun_ptr.pfun_Osal_SpinLockInit        = OSAL_SpinLockInit;
    g_vfmw_osal_fun_ptr.pfun_Osal_SpinLock            = OSAL_SpinLock;
    g_vfmw_osal_fun_ptr.pfun_Osal_SpinUnLock          = OSAL_SpinUnLock;
    g_vfmw_osal_fun_ptr.pfun_Osal_SemaInit            = OSAL_SemInit;
    g_vfmw_osal_fun_ptr.pfun_Osal_SemaDown            = OSAL_SemDown;
    g_vfmw_osal_fun_ptr.pfun_Osal_SemaUp              = OSAL_SemUp;
    g_vfmw_osal_fun_ptr.pfun_Osal_Print               = OSAL_Print;
    g_vfmw_osal_fun_ptr.pfun_Osal_mSleep              = OSAL_mSleep;
    g_vfmw_osal_fun_ptr.pfun_Osal_Mb                  = OSAL_Mb;
    g_vfmw_osal_fun_ptr.pfun_Osal_uDelay              = OSAL_uDelay;
    g_vfmw_osal_fun_ptr.pfun_Osal_InitEvent           = OSAL_InitWaitQue;
    g_vfmw_osal_fun_ptr.pfun_Osal_GiveEvent           = OSAL_WakeupWaitQue;
    g_vfmw_osal_fun_ptr.pfun_Osal_WaitEvent           = OSAL_WaitWaitQue;
    g_vfmw_osal_fun_ptr.pfun_Osal_RequestIrq          = OSAL_RequestIrq;
    g_vfmw_osal_fun_ptr.pfun_Osal_FreeIrq             = OSAL_FreeIrq;
    g_vfmw_osal_fun_ptr.pfun_Osal_MemAlloc            = OSAL_MemMalloc;
    g_vfmw_osal_fun_ptr.pfun_Osal_MemFree             = OSAL_MemFree;
    g_vfmw_osal_fun_ptr.pfun_Osal_RegisterMap         = OSAL_RegisterMap;
    g_vfmw_osal_fun_ptr.pfun_Osal_RegisterUnMap       = OSAL_RegisterUnMap;
    g_vfmw_osal_fun_ptr.pfun_Osal_Mmap                = OSAL_Mmap;
    g_vfmw_osal_fun_ptr.pfun_Osal_MmapCache           = OSAL_MmapCache;
    g_vfmw_osal_fun_ptr.pfun_Osal_MunMap              = OSAL_Munmap;
    g_vfmw_osal_fun_ptr.pfun_Osal_AllocVirMem         = OSAL_AllocVirMem;
    g_vfmw_osal_fun_ptr.pfun_Osal_FreeVirMem          = OSAL_FreeVirMem;
    g_vfmw_osal_fun_ptr.pfun_Osal_ProcInit            = OSAL_ProcInit;
    g_vfmw_osal_fun_ptr.pfun_Osal_ProcExit            = OSAL_ProcExit;
}

#endif

