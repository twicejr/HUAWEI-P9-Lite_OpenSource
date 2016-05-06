
#ifndef __VFMW_OSAL_EXT_HEADER__
#define __VFMW_OSAL_EXT_HEADER__

#include "vfmw.h"
#include "mem_manage.h"


#define OSAL_OK     0
#define OSAL_ERR   -1

typedef SINT32 (*OSAL_IRQ_HANDLER_t)(SINT32, VOID *);

typedef enum SpinLockType
{
    G_SPINLOCK_THREAD    = 0,
    G_SPINLOCK_RECORD,
    G_SPINLOCK_VOQUEUE,
    G_SPINLOCK_FSP,
    G_SPINLOCK_DESTROY,
} SpinLockType;

typedef enum MutexType
{
    G_INTEVENT = 0,
} MutexType;

typedef enum SemType
{
    G_VfmwSem = 0,
} SemType;

typedef UINT32 (*FN_OSAL_GetTimeInMs)(VOID);
typedef UINT32 (*FN_OSAL_GetTimeInUs)(VOID);
typedef VOID   (*FN_OSAL_SpinLockInit)(SpinLockType);
typedef SINT32 (*FN_OSAL_SpinLock)(SpinLockType);
typedef SINT32 (*FN_OSAL_SpinUnlock)(SpinLockType);
typedef VOID   (*FN_OSAL_SemaInit)(SemType);
typedef SINT32 (*FN_OSAL_SemaDown)(SemType);
typedef VOID   (*FN_OSAL_SemaUp)(SemType);
typedef SINT32 (*FN_OSAL_Print)(const char *, ...);
typedef VOID   (*FN_OSAL_Mb)(VOID);
typedef VOID   (*FN_OSAL_uDelay)(ULONG);
typedef VOID   (*FN_OSAL_mSleep)(UINT32);
typedef SINT32 (*FN_OSAL_InitEvent)(MutexType, SINT32);
typedef SINT32 (*FN_OSAL_GiveEvent)(MutexType);
typedef SINT32 (*FN_OSAL_WaitEvent)(MutexType, SINT32);
typedef SINT32 (*FN_OSAL_MemAlloc)(UINT8*, UINT32, UINT32, UINT32, MEM_DESC_S*);
typedef SINT32 (*FN_OSAL_MemFree)(MEM_DESC_S*);
typedef SINT8* (*FN_OSAL_RegisterMap)(UADDR, UINT32);
typedef VOID   (*FN_OSAL_RegisterUnMap)(UINT8*);
typedef UINT8* (*FN_OSAL_Mmap)(UADDR, UINT32);
typedef UINT8* (*FN_OSAL_MmapCache)(UADDR, UINT32);  
typedef VOID   (*FN_OSAL_MunMap)(UINT8*);  
typedef SINT32 (*FN_OSAL_RequestIrq)(UINT32, OSAL_IRQ_HANDLER_t, ULONG, const char *, VOID*);
typedef VOID   (*FN_OSAL_FreeIrq)(UINT32, VOID*);
typedef VOID*  (*FN_OSAL_AllocVirMem)(SINT32);
typedef VOID   (*FN_OSAL_FreeVirMem)(VOID*);
typedef SINT32 (*FN_OSAL_ProcInit)(VOID);
typedef VOID   (*FN_OSAL_ProcExit)(VOID);

typedef struct Vfmw_Osal_Func_Ptr
{
    FN_OSAL_GetTimeInMs         pfun_Osal_GetTimeInMs;
    FN_OSAL_GetTimeInUs         pfun_Osal_GetTimeInUs;
    FN_OSAL_SpinLockInit        pfun_Osal_SpinLockInit;
    FN_OSAL_SpinLock            pfun_Osal_SpinLock;
    FN_OSAL_SpinUnlock          pfun_Osal_SpinUnLock;
    FN_OSAL_SemaInit            pfun_Osal_SemaInit;
    FN_OSAL_SemaDown            pfun_Osal_SemaDown;
    FN_OSAL_SemaUp              pfun_Osal_SemaUp;
    FN_OSAL_Print               pfun_Osal_Print;
    FN_OSAL_Mb                  pfun_Osal_Mb;
    FN_OSAL_uDelay              pfun_Osal_uDelay;
    FN_OSAL_mSleep              pfun_Osal_mSleep;
    FN_OSAL_InitEvent           pfun_Osal_InitEvent;
    FN_OSAL_GiveEvent           pfun_Osal_GiveEvent;
    FN_OSAL_WaitEvent           pfun_Osal_WaitEvent;
    FN_OSAL_RequestIrq          pfun_Osal_RequestIrq;
    FN_OSAL_FreeIrq             pfun_Osal_FreeIrq;
    FN_OSAL_MemAlloc            pfun_Osal_MemAlloc;
    FN_OSAL_MemFree             pfun_Osal_MemFree;
    FN_OSAL_RegisterMap         pfun_Osal_RegisterMap;
    FN_OSAL_RegisterUnMap       pfun_Osal_RegisterUnMap;
    FN_OSAL_Mmap                pfun_Osal_Mmap;
    FN_OSAL_MmapCache           pfun_Osal_MmapCache;
    FN_OSAL_MunMap              pfun_Osal_MunMap;
    FN_OSAL_AllocVirMem         pfun_Osal_AllocVirMem;
    FN_OSAL_FreeVirMem          pfun_Osal_FreeVirMem;
    FN_OSAL_ProcInit            pfun_Osal_ProcInit;
    FN_OSAL_ProcExit            pfun_Osal_ProcExit;
    
} Vfmw_Osal_Func_Ptr;

extern Vfmw_Osal_Func_Ptr g_vfmw_osal_fun_ptr;

#define VFMW_OSAL_GetTimeInMs          g_vfmw_osal_fun_ptr.pfun_Osal_GetTimeInMs
#define VFMW_OSAL_GetTimeInUs          g_vfmw_osal_fun_ptr.pfun_Osal_GetTimeInUs
#define VFMW_OSAL_SpinLockInit         g_vfmw_osal_fun_ptr.pfun_Osal_SpinLockInit
#define VFMW_OSAL_SpinLock             g_vfmw_osal_fun_ptr.pfun_Osal_SpinLock
#define VFMW_OSAL_SpinUnLock           g_vfmw_osal_fun_ptr.pfun_Osal_SpinUnLock
#define VFMW_OSAL_SemaInit             g_vfmw_osal_fun_ptr.pfun_Osal_SemaInit
#define VFMW_OSAL_SemaDown             g_vfmw_osal_fun_ptr.pfun_Osal_SemaDown
#define VFMW_OSAL_SemaUp               g_vfmw_osal_fun_ptr.pfun_Osal_SemaUp
#define VFMW_OSAL_Print                g_vfmw_osal_fun_ptr.pfun_Osal_Print
#define VFMW_OSAL_Mb                   g_vfmw_osal_fun_ptr.pfun_Osal_Mb
#define VFMW_OSAL_uDelay               g_vfmw_osal_fun_ptr.pfun_Osal_uDelay
#define VFMW_OSAL_mSleep               g_vfmw_osal_fun_ptr.pfun_Osal_mSleep
#define VFMW_OSAL_InitEvent            g_vfmw_osal_fun_ptr.pfun_Osal_InitEvent
#define VFMW_OSAL_GiveEvent            g_vfmw_osal_fun_ptr.pfun_Osal_GiveEvent
#define VFMW_OSAL_WaitEvent            g_vfmw_osal_fun_ptr.pfun_Osal_WaitEvent
#define VFMW_OSAL_RequestIrq           g_vfmw_osal_fun_ptr.pfun_Osal_RequestIrq
#define VFMW_OSAL_FreeIrq              g_vfmw_osal_fun_ptr.pfun_Osal_FreeIrq
#define VFMW_OSAL_MemAlloc             g_vfmw_osal_fun_ptr.pfun_Osal_MemAlloc
#define VFMW_OSAL_MemFree              g_vfmw_osal_fun_ptr.pfun_Osal_MemFree
#define VFMW_OSAL_RegisterMap          g_vfmw_osal_fun_ptr.pfun_Osal_RegisterMap
#define VFMW_OSAL_RegisterUnMap        g_vfmw_osal_fun_ptr.pfun_Osal_RegisterUnMap
#define VFMW_OSAL_Mmap                 g_vfmw_osal_fun_ptr.pfun_Osal_Mmap
#define VFMW_OSAL_MmapCache            g_vfmw_osal_fun_ptr.pfun_Osal_MmapCache
#define VFMW_OSAL_MunMap               g_vfmw_osal_fun_ptr.pfun_Osal_MunMap
#define VFMW_OSAL_AllocVirMem          g_vfmw_osal_fun_ptr.pfun_Osal_AllocVirMem
#define VFMW_OSAL_FreeVirMem           g_vfmw_osal_fun_ptr.pfun_Osal_FreeVirMem
#define VFMW_OSAL_ProcInit             g_vfmw_osal_fun_ptr.pfun_Osal_ProcInit
#define VFMW_OSAL_ProcExit             g_vfmw_osal_fun_ptr.pfun_Osal_ProcExit

#endif
