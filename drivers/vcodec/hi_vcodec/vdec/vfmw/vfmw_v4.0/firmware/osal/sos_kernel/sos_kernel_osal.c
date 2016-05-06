/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7opllls6N4+3ndAUojS6eCHJa9l6FKEwvAJc6HyzW+LkPf+EbPkekD0NWfuag
+pY0jB2CHfDn/9xjvBVV9gPGXD0r0tJZOHthFHsUfDSn2iRkqtY2hwbEdKCNXBfZ2nWNqMft
fOpdmE9wWpouN/JfIEwnsbx4DpB8hmLAmT5+50WGxX1vLi3et2oWTpAf4zCnzg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************

  版权所有 (C), 2001-2015, 华为技术有限公司

******************************************************************************
    文 件 名   : trusted_vfmw_osal.c
    版 本 号   : 初稿
    作    者   :
    生成日期   :
    最近修改   :
    功能描述   : 为vfmw定制的TEE环境抽象模块


    修改历史   :
    1.日    期 : 2015-09-18
    作    者   :
    修改内容   :

******************************************************************************/

#include "sos_kernel_osal.h"
#include "public.h"


#ifdef ENV_SOS_KERNEL

/* SpinLock */
SOS_IRQ_SPIN_LOCK g_SosLock_Thread;
SOS_IRQ_SPIN_LOCK g_SosLock_Record;
SOS_IRQ_SPIN_LOCK g_SosLock_VoQueue;
SOS_IRQ_SPIN_LOCK g_SosLock_Fsp;
SOS_IRQ_SPIN_LOCK g_SosLock_Destroy;

/* Extern */
extern Vfmw_Osal_Func_Ptr g_vfmw_osal_fun_ptr;


/************************************************************************/
/* secure world printk                                                  */
/************************************************************************/
#define SOS_Print   uart_printf_func


/************* Redefine Unused Functions ************/
inline VOID SOS_mSleep(UINT32 msecs)
{
    return;
}

inline VOID SOS_uDelay(ULONG usecs)
{
    return;
}

inline VOID SOS_Mb(VOID)
{
    return;
}

inline SINT32 SOS_InitWaitQue(MutexType mutextType, SINT32 initVal)
{
    return OSAL_OK;
}

inline SINT32 SOS_WakeupWaitQue(MutexType mutexType)
{
    return OSAL_OK;
}

inline SINT32 SOS_WaitWaitQue(MutexType mutexType, SINT32 waitTimeInMs)
{
    return OSAL_OK;
}

inline VOID SOS_SemaInit(SemType Type)
{
	return;
}

inline SINT32 SOS_SemDown(SemType Type)
{
	return OSAL_OK;
}

inline VOID SOS_SemaUp(SemType Type)
{
	return;
}

inline VOID SOS_RegisterUnMap(UINT8 *VirAddr)
{
    return;
}

inline SINT32 SOS_MemMalloc(UINT8 *MemName, UINT32 Len, UINT32 Align, UINT32 isCached, MEM_DESC_S *pMemDesc)
{
    dprint(PRN_FATAL, "Not support %s\n", __func__);
    return OSAL_ERR;
}

inline SINT32 SOS_MemFree(MEM_DESC_S *pMemDesc)
{
    dprint(PRN_FATAL, "Not support %s\n", __func__);
    return OSAL_ERR;
}


/************************************************************************/
/* SOS_RegisterMap(): already map register, return phy address          */
/************************************************************************/
SINT8 *SOS_RegisterMap(UINT32 PhyAddr, UINT32 Size)
{
    return (SINT8 *)PhyAddr;
}


/************************************************************************/
/*  GetSpinLockByEnum(): Get Lock by enum                               */
/************************************************************************/
SOS_IRQ_SPIN_LOCK *GetSpinLockByEnum(SpinLockType LockType)
{
    SOS_IRQ_SPIN_LOCK *pSosLock = NULL;

    switch (LockType)
    {
        case G_SPINLOCK_THREAD:
            pSosLock = &g_SosLock_Thread;
            break;

        case G_SPINLOCK_RECORD:
            pSosLock = &g_SosLock_Record;
            break;

        case G_SPINLOCK_VOQUEUE:
            pSosLock = &g_SosLock_VoQueue;
            break;

        case G_SPINLOCK_FSP:
            pSosLock = &g_SosLock_Fsp;
            break;

        case G_SPINLOCK_DESTROY:
            pSosLock = &g_SosLock_Destroy;
            break;

        default:
            dprint(PRN_ERROR, "%s unkown SpinLockType %d\n", __func__, LockType);
            break;
    }

    return pSosLock;
}


/************************************************************************/
/* SOS_SpinLockInit(): Init Lock by enum                                */
/************************************************************************/
VOID SOS_SpinLockInit(SpinLockType spinLockType)
{
    SOS_IRQ_SPIN_LOCK *pSosSpinLock = NULL;

    pSosSpinLock = GetSpinLockByEnum(spinLockType);

    if (pSosSpinLock != NULL)
    {
        memset(pSosSpinLock, 0, sizeof(SOS_IRQ_SPIN_LOCK));
    }
}

/************************************************************************/
/* SOS_SpinLock(): Acquire Lock by enum                                 */
/************************************************************************/
SINT32 SOS_SpinLock(SpinLockType spinLockType)
{
    SOS_IRQ_SPIN_LOCK *pSosSpinLock = NULL;

    pSosSpinLock = GetSpinLockByEnum(spinLockType);

    if (pSosSpinLock != NULL)
    {
        pSosSpinLock->irq_lock = SRE_IntLock();
        return OSAL_OK;
    }
    else
    {
        return OSAL_ERR;
    }
}

/************************************************************************/
/* SOS_SpinUnLock(): Release Lock by enum                               */
/************************************************************************/
SINT32 SOS_SpinUnLock(SpinLockType spinLockType)
{
    SOS_IRQ_SPIN_LOCK *pSosSpinLock = NULL;

    pSosSpinLock = GetSpinLockByEnum(spinLockType);

    if (pSosSpinLock != NULL)
    {
        SRE_IntRestore(pSosSpinLock->irq_lock);
        return OSAL_OK;
    }
    else
    {
        return OSAL_ERR;
    }
}

/************************************************************************/
/* SOS_GetTimeInMs(): Get system time in ms                             */
/************************************************************************/
UINT32 SOS_GetTimeInMs(VOID)
{
    UINT64 tmp;
	UINT32 CurrMs = 0;
    timeval_t CurrentTime;

    tmp = SRE_ReadTimestamp();
    CurrentTime.tval.sec = (tmp>>32);
    CurrentTime.tval.nsec = tmp & 0xffffffff;
    CurrMs = (UINT32)(CurrentTime.tval.sec*1000 + CurrentTime.tval.nsec/1000000);

	return CurrMs;
}

/************************************************************************/
/* SOS_GetTimeInUs(): Get system time in us                             */
/************************************************************************/
UINT32 SOS_GetTimeInUs(VOID)
{
    UINT64 tmp;
	UINT32 CurrUs = 0;
    timeval_t CurrentTime;

    tmp = SRE_ReadTimestamp();
    CurrentTime.tval.sec = (tmp>>32);
    CurrentTime.tval.nsec = tmp & 0xffffffff;
    CurrUs = (UINT32)(CurrentTime.tval.sec*1000000 + CurrentTime.tval.nsec/1000);

	return CurrUs;
}


/************************************************************************/
/* Map/Unmap share memory to secure world                               */
/* SecMode  0-map secure mem  1-map normal mem                          */
/************************************************************************/
SINT8* SOS_MapShare(UINT32 Phy, SINT32 Size, UINT32 SecMode, UINT32 IsCached)
{
    SINT32 ret = 0;

    ret = mmap(Phy, Size, SecMode, IsCached);
    if (ret != 0)
    {
        dprint(PRN_FATAL, "%s %d, mmap failed ret=%d\n", __func__,__LINE__,ret);
        return NULL;
    }

    return (SINT8 *)Phy;
}

SINT32 SOS_UnMapShare(VOID *Vir, SINT32 Size)
{
    SINT32 ret = 0;

    ret = unmap((UINT32)Vir, Size);
    if (ret != 0)
    {
        dprint(PRN_FATAL, "%s %d, unmap failed ret=%d\n", __func__,__LINE__,ret);
    }

    return ret;
}


/************************************************************************/
/* Secure IRQ Request & Free                                            */
/************************************************************************/
SINT32 SOS_RequestIrq(UINT32 IrqNum, OSAL_IRQ_HANDLER_t pfnHandler, ULONG flags, const char *name, VOID *dev)
{
    UINT32 ret;

    ret = SRE_HwiCreate(IrqNum, 0xa0, 0x0, (HWI_PROC_FUNC)pfnHandler, flags);
    if (ret != 0)
    {
        dprint(PRN_FATAL, "SRE_HwiCreate failed, IrqNum=%d\n", IrqNum);
        return ret;
    }

    ret = SRE_HwiEnable(IrqNum);
    if (ret != 0)
    {
        dprint(PRN_FATAL, "SRE_HwiEnable failed, IrqNum=%d\n", IrqNum);
    }

    return ret;
}

VOID SOS_FreeIrq(UINT32 IrqNum, VOID *dev)
{
    UINT32 ret;

    ret = SRE_HwiDelete(IrqNum);
    if (ret != 0)
    {
        dprint(PRN_FATAL, "SRE_HwiDelete failed, IrqNum=%d\n", IrqNum);
    }

    return;
}


/************************************************************************/
/*  Secure OS kernel interface initialization                           */
/************************************************************************/
SINT32 SOS_InitInterface(VOID)
{
    memset(&g_vfmw_osal_fun_ptr, 0, sizeof(Vfmw_Osal_Func_Ptr));

    g_vfmw_osal_fun_ptr.pfun_Osal_GetTimeInMs         = SOS_GetTimeInMs;
    g_vfmw_osal_fun_ptr.pfun_Osal_GetTimeInUs         = SOS_GetTimeInUs;
    g_vfmw_osal_fun_ptr.pfun_Osal_SpinLockInit        = SOS_SpinLockInit;
    g_vfmw_osal_fun_ptr.pfun_Osal_SpinLock            = SOS_SpinLock;
    g_vfmw_osal_fun_ptr.pfun_Osal_SpinUnLock          = SOS_SpinUnLock;
    g_vfmw_osal_fun_ptr.pfun_Osal_SemaInit            = SOS_SemaInit;
    g_vfmw_osal_fun_ptr.pfun_Osal_SemaDown            = SOS_SemDown;
    g_vfmw_osal_fun_ptr.pfun_Osal_SemaUp              = SOS_SemaUp;
    g_vfmw_osal_fun_ptr.pfun_Osal_Print               = SOS_Print;
    g_vfmw_osal_fun_ptr.pfun_Osal_mSleep              = SOS_mSleep;
    g_vfmw_osal_fun_ptr.pfun_Osal_Mb                  = SOS_Mb;
    g_vfmw_osal_fun_ptr.pfun_Osal_uDelay              = SOS_uDelay;
    g_vfmw_osal_fun_ptr.pfun_Osal_InitEvent           = SOS_InitWaitQue;
    g_vfmw_osal_fun_ptr.pfun_Osal_GiveEvent           = SOS_WakeupWaitQue;
    g_vfmw_osal_fun_ptr.pfun_Osal_WaitEvent           = SOS_WaitWaitQue;
    g_vfmw_osal_fun_ptr.pfun_Osal_MemAlloc            = SOS_MemMalloc;
    g_vfmw_osal_fun_ptr.pfun_Osal_MemFree             = SOS_MemFree;
    g_vfmw_osal_fun_ptr.pfun_Osal_RegisterMap         = SOS_RegisterMap;
    g_vfmw_osal_fun_ptr.pfun_Osal_RegisterUnMap       = SOS_RegisterUnMap;
    g_vfmw_osal_fun_ptr.pfun_Osal_RequestIrq          = SOS_RequestIrq;
    g_vfmw_osal_fun_ptr.pfun_Osal_FreeIrq             = SOS_FreeIrq;
    g_vfmw_osal_fun_ptr.pfun_Osal_Mmap                = NULL;
    g_vfmw_osal_fun_ptr.pfun_Osal_MmapCache           = NULL;
    g_vfmw_osal_fun_ptr.pfun_Osal_MunMap              = NULL;
    g_vfmw_osal_fun_ptr.pfun_Osal_AllocVirMem         = NULL;
    g_vfmw_osal_fun_ptr.pfun_Osal_FreeVirMem          = NULL;
    g_vfmw_osal_fun_ptr.pfun_Osal_ProcInit            = NULL;
    g_vfmw_osal_fun_ptr.pfun_Osal_ProcExit            = NULL;

    return OSAL_OK;
}


/************************************************************************/
/*  Init Function Declare                                               */
/************************************************************************/
DECLARE_TC_DRV(
        SecureVfmw,
        0,
        0,
        0,
        0,
        SOS_InitInterface,
        NULL
        );

#endif


