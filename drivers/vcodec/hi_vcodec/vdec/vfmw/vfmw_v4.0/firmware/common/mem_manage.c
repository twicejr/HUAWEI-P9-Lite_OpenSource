/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r32RUqUJ6SrqOZotNmwwDEEnsjhAH6+5VqwgU4Meek63HZxQuHbHx1W4P04LpffXNjY3s
yPzjgK2Jx/B97tctB83xlIFW4vzF6MwWsnA1EdYUhkmtj8ysKx80vGnFvVmGfg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : mem_manage.c
    版 本 号   : 初稿
    作    者   : 
    生成日期   : 
    最近修改   :
    功能描述   : firmware的存储管理模块，包括
                 1. 存储空间虚拟地址/物理地址之间的映射
                 2. 通用存储访问函数（比如寄存器读写）
                 3. 存储空间的分配与销毁（屏蔽多种操作系统差异）
                 4. 寄存器地址映射（屏蔽多种操作系统差异）
                 

    修改历史   :
    1.日    期 : 2009-01-07
    作    者   : z56361
    修改内容   : 

******************************************************************************/

#include "mem_manage.h"
#include "sysconfig.h"


#define    MAX_MEM_MAN_RECORD_NUM    (MAX_CHAN_NUM*32)  //MAX_CHAN_NUM*5 每个通道为ADD 11 次
static UADDR  s_MemBaseAddr;
static UINT32 s_MemSize;
static UINT32 s_MemOffset;
MEM_RECORD_S  s_MemRecord[MAX_MEM_MAN_RECORD_NUM];

EXT_FN_MEM_MALLOC  g_pfnMemMalloc;
EXT_FN_MEM_FREE    g_pfnMemFree;  


/************************************************************************/
/*    初始化                                                            */
/************************************************************************/
VOID MEM_InitMemManager(MEM_INIT_S *pMemInit)
{
    VFMW_OSAL_SpinLock(G_SPINLOCK_RECORD);

    memset( &s_MemRecord, 0, sizeof(MEM_RECORD_S)*MAX_MEM_MAN_RECORD_NUM );
    
    s_MemBaseAddr     = pMemInit->MemBaseAddr;
    s_MemSize         = pMemInit->MemSize;
    s_MemOffset       = 0;
    
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_RECORD);

    return;
}

/************************************************************************/
/*    指定内存操作                                                      */
/************************************************************************/
VOID MEM_ManagerWithOperation(INIT_INTF_S *pIntf)
{
    g_pfnMemMalloc = pIntf->mem_malloc;
    g_pfnMemFree   = pIntf->mem_free;

	return;
}
/************************************************************************/
/*    清除指定内存操作                                                  */
/************************************************************************/
VOID MEM_ManagerClearOperation(VOID)
{
    g_pfnMemMalloc = NULL;
    g_pfnMemFree   = NULL;

    return;
}
/************************************************************************/
/*    添加记录                                                          */
/************************************************************************/
SINT32 MEM_AddMemRecord(UADDR PhyAddr, VOID* VirAddr, UINT32 Length)
{
    SINT32  i;

    VFMW_OSAL_SpinLock(G_SPINLOCK_RECORD);
    for( i=0; i<MAX_MEM_MAN_RECORD_NUM; i++ )
    {
        if( s_MemRecord[i].Length == 0 )
        {
            break;
        }
    }

    if( i < MAX_MEM_MAN_RECORD_NUM )
    {
        s_MemRecord[i].PhyAddr = PhyAddr;
        s_MemRecord[i].VirAddr = VirAddr;
        s_MemRecord[i].Length  = Length;
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_RECORD);

        return MEM_MAN_OK;
    }
    else
    {
        VFMW_OSAL_SpinUnLock(G_SPINLOCK_RECORD);

        return MEM_MAN_ERR;
    }
}

/************************************************************************/
/*    删除记录                                                          */
/************************************************************************/
SINT32 MEM_DelMemRecord(UADDR PhyAddr, VOID* VirAddr, UINT32 Length)
{
    SINT32  i;
    
    VFMW_OSAL_SpinLock(G_SPINLOCK_RECORD);
    for( i=0; i<MAX_MEM_MAN_RECORD_NUM; i++ )
    {
        if( 0 == s_MemRecord[i].Length ) 
        {
            continue;
        }

        if( PhyAddr==s_MemRecord[i].PhyAddr && VirAddr==s_MemRecord[i].VirAddr
              && Length==s_MemRecord[i].Length )
        {
            s_MemRecord[i].Length  = 0;
            s_MemRecord[i].PhyAddr = 0;
            s_MemRecord[i].VirAddr = 0;
            VFMW_OSAL_SpinUnLock(G_SPINLOCK_RECORD);

            return MEM_MAN_OK;
        }
    }
    VFMW_OSAL_SpinUnLock(G_SPINLOCK_RECORD);

    return MEM_MAN_ERR;
}

#if 0
/************************************************************************/
/*   记录表打印                                                         */
/************************************************************************/
VOID MEM_DumpRecord(VOID)
{
    UINT32 i;

    dprint(PRN_ALWS, "\n-------------------- MEM_DumpRecord ---------------------\n");
    for( i=0; i<MAX_MEM_MAN_RECORD_NUM; i++ )
    {        
        if( s_MemRecord[i].Length == 0) 
        {
            continue;
        }
        dprint(PRN_ALWS, " %d: PhyAddr %x, VirAddr %p, Length %d, IsSecure %d\n", i, s_MemRecord[i].PhyAddr, s_MemRecord[i].VirAddr, s_MemRecord[i].Length, s_MemRecord[i].IsSecMem);
    }
    dprint(PRN_ALWS,   "-------------------------- END --------------------------\n\n");

    return;
}
#endif

/************************************************************************/
/*   地址转换： 物理地址 -> 虚拟地址                                    */
/************************************************************************/
VOID *MEM_Phy2Vir(UADDR PhyAddr)
{
    UINT32 i;
    UINT8  *VirAddr = NULL;

    for( i=0; i<MAX_MEM_MAN_RECORD_NUM; i++ )
    {
        if( s_MemRecord[i].Length == 0) 
        {
            continue;
        }

        if( (PhyAddr >= s_MemRecord[i].PhyAddr) && (PhyAddr < s_MemRecord[i].PhyAddr + s_MemRecord[i].Length) )
        {
            VirAddr = s_MemRecord[i].VirAddr + (PhyAddr - s_MemRecord[i].PhyAddr);
            break;
        }
    }

    return (VOID*)VirAddr;
}


/************************************************************************/
/*   地址转换： 虚拟地址 -> 物理地址                                    */
/************************************************************************/
UADDR MEM_Vir2Phy(UINT8 *VirAddr)
{
    UINT32  i;

    UADDR  PhyAddr = 0;
    for( i=0; i<MAX_MEM_MAN_RECORD_NUM; i++ )
    {
        if( s_MemRecord[i].Length == 0) 
        {
            continue;
        }

        if( (VirAddr >= s_MemRecord[i].VirAddr) && (VirAddr < s_MemRecord[i].VirAddr + s_MemRecord[i].Length) )
        {
            PhyAddr = s_MemRecord[i].PhyAddr + (VirAddr - s_MemRecord[i].VirAddr);
            break;
        }
    }

    return PhyAddr;
}


/************************************************************************/
/*   mem操作： 向指定的物理地址写入一个word                             */
/************************************************************************/
VOID MEM_WritePhyWord(UADDR PhyAddr, UINT32 Data32)
{
    UINT32   *pDst;

    pDst = (UINT32*)MEM_Phy2Vir( PhyAddr );
    if( NULL != pDst )
    {
        *pDst = Data32;
    }
}

UINT32 MEM_ReadPhyWord(UADDR PhyAddr)
{
    UINT32   *pDst;
    UINT32   Data32;

    Data32 = 0;
	pDst = (UINT32*)MEM_Phy2Vir( PhyAddr );
    if( NULL != pDst )
    {
        Data32 = *(volatile UINT32 *)pDst;
    }

    return Data32;
}

/************************************************************************/
/*   mem操作： 拷贝一片数据（phy -> phy）                               */
/************************************************************************/
VOID MEM_CopyPhy2Phy(UADDR DstPhyAddr, UADDR SrcPhyAddr, UINT32 Length)
{
    UINT8   *pDst, *pSrc;

    pDst = (UINT8*)MEM_Phy2Vir( DstPhyAddr );
    pSrc = (UINT8*)MEM_Phy2Vir( SrcPhyAddr );
    if( NULL != pDst && NULL != pSrc )
    {
        memcpy( pDst, pSrc, Length );
    }
}

/************************************************************************/
/*   mem操作： 拷贝一片数据（phy -> vir）                               */
/************************************************************************/
VOID MEM_CopyPhy2Vir( UINT8 *DstVirAddr, UADDR SrcPhyAddr, UINT32 Length )
{
    UINT8   *pSrc;

    pSrc = (UINT8*)MEM_Phy2Vir( SrcPhyAddr );
    if( NULL != DstVirAddr && NULL != pSrc )
    {
        memcpy( DstVirAddr, pSrc, Length );
    }
}

/************************************************************************/
/*   mem操作： 拷贝一片数据（vir -> phy）                               */
/************************************************************************/
VOID MEM_CopyVir2Phy(UADDR DstPhyAddr, UINT8* SrcVirAddr, UINT32 Length)
{
    UINT8 *pDst = NULL;

    pDst = (UINT8 *)MEM_Phy2Vir( DstPhyAddr );
    if( NULL != pDst && NULL != SrcVirAddr )
    {
        memcpy( pDst, SrcVirAddr, Length );
    }
}


/************************************************************************/
/*   申请内存块                                                         */
/************************************************************************/
SINT32  MEM_AllocMemBlock(SINT8 *pMemName, UINT32 ExpectedLen, MEM_RECORD_S *pMemRecord, SINT32 IsCached)
{
    SINT32 ret;
    MEM_DESC_S AllocMem;
    
    // 入口参数检查
    if( (NULL == pMemRecord) || (0 == ExpectedLen) )
    {
        return MEM_MAN_ERR;
    }
    
    // 清除输出信息结构
    memset( pMemRecord, 0, sizeof(MEM_RECORD_S) );

    // default not secure & memtype = ion
    memset( &AllocMem,  0, sizeof(MEM_DESC_S) );

    // 申请或者映射地址空间: 物理地址 --> 虚拟地址 */
    ret = VFMW_OSAL_MemAlloc(pMemName, ExpectedLen, 4, IsCached, &AllocMem);
    if (OSAL_OK == ret)
    {
        if (0 == AllocMem.PhyAddr || NULL == AllocMem.VirAddr || ExpectedLen > AllocMem.Length)
        {
            return MEM_MAN_ERR;  /* 异常错误 */
        }
        else
        {
            /* 返回内存分配/映射结果 */
            pMemRecord->PhyAddr = AllocMem.PhyAddr;
            pMemRecord->VirAddr = AllocMem.VirAddr;
            pMemRecord->Length  = AllocMem.Length;
            s_MemOffset += AllocMem.Length;
            s_MemOffset = (s_MemOffset+3) & (~3);
            return MEM_MAN_OK;
        }
    }
    else
    {
        return MEM_MAN_ERR;  /* 异常错误 */
    }
}

/************************************************************************/
/*   映射寄存器                                                         */
/************************************************************************/
SINT32  MEM_MapRegisterAddr(UADDR RegStartPhyAddr, UINT32 RegByteLen, MEM_RECORD_S *pMemRecord)
{
    UINT8 *ptr;

    // 入口参数检查
    if( (NULL == pMemRecord) || (0 == RegStartPhyAddr) || (0 == RegByteLen))
    {
        return MEM_MAN_ERR;
    }

    // 清除输出信息结构
    memset( pMemRecord, 0, sizeof(MEM_RECORD_S) );

    // 地址映射
    ptr = VFMW_OSAL_RegisterMap(RegStartPhyAddr, RegByteLen);
    
    if( NULL != ptr )
    {
        pMemRecord->PhyAddr = RegStartPhyAddr;
        pMemRecord->VirAddr = ptr;
        pMemRecord->Length  = RegByteLen;
        return MEM_MAN_OK;
    }

    return MEM_MAN_ERR;
}

/************************************************************************/
/*   寄存器去映射                                                       */
/************************************************************************/
VOID MEM_UnmapRegisterAddr(UADDR PhyAddr, UINT8 *VirAddr)
{
    // 入口参数检查
    if( (0 == PhyAddr) || (0 == VirAddr) )
    {
        return;
    }
    
    // 地址去映射: IO_ADDRESS */
    VFMW_OSAL_RegisterUnMap(VirAddr);

    return;
}

/************************************************************************/
/*   释放内存块                                                         */
/************************************************************************/
VOID MEM_ReleaseMemBlock(UADDR PhyAddr, UINT8 *VirAddr )
{
    MEM_DESC_S FreeMem;
    UINT32 i;
    
    // 入口参数检查
    if( (0 == PhyAddr) || (0 == VirAddr) )
    {
        return;
    }
    memset(&FreeMem,0,sizeof(MEM_DESC_S));
    
    FreeMem.PhyAddr = PhyAddr;
    FreeMem.VirAddr = VirAddr;
    for( i=0; i<MAX_MEM_MAN_RECORD_NUM; i++ )
    {
        if( s_MemRecord[i].Length == 0) 
        {
            continue;
        }

        if( (PhyAddr >= s_MemRecord[i].PhyAddr) && (PhyAddr < s_MemRecord[i].PhyAddr + s_MemRecord[i].Length) )
        {
            FreeMem.Length = s_MemRecord[i].Length;
            break;
        }
    }   
    
    VFMW_OSAL_MemFree(&FreeMem);
	
    /* 
        删除一个内存块后，理应同步删除s_MemRecord中对应的记录，避免此地址被后续程序错误引用。
        但在firmware中，内存的申请和释放只在解码器的创建与销毁操作中才会进行，所以忽略上述问题。
    */

    return;
}


