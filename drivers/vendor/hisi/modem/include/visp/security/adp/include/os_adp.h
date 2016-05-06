

#ifdef TCPIP_FORBALONG
#include "tcpip/public/vos_redef.h"
#endif

#if (NAT_WVISP == 1)

#include "security/wvisp_adapter/include/os_adp.h"

#elif (NAT_RPU == 1)

#include "security/rpu_adapter/include/os_adp.h"

#else

#ifndef _OS_ADP_H_
#define _OS_ADP_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef VOS_ARM
#define VOS_ARM                        8
#endif

/**
* @defgroup tagIpsafeAdpDate IPSAFE_ADP_DATE_S
* @ingroup OS adaptor structures
* @par Prototype
* @code
* typedef struct tagIpsafeAdpDate
* {
*   UCHAR u8Date;       
*   UCHAR u8Month;      
*   USHORT u8Year;
* }IPSAFE_ADP_DATE_S;
*
* 
* @par Description
* This structure stores the date information used by ACL Timer.
*
* @datastruct u8Date    Day(1-31)
* @datastruct u8Month   Month(1-12)
* @datastruct u8Year    Year(1970-...)
*
* @par Note
*
*/
typedef struct tagIpsafeAdpDate
{
    UCHAR u8Date;       /* 1-31     */
    UCHAR u8Month;      /* 1-12     */
    USHORT u8Year;      /* 1970-... */
}IPSAFE_ADP_DATE_S;

/**
* @defgroup tagIpsafeAdpTime IPSAFE_ADP_TIME_S
* @ingroup OS adaptor structures
* @par Prototype
* @code
* typedef struct tagIpsafeAdpTime
* {
*   UCHAR u8Second;       
*   UCHAR u8Minute;      
*   USHORT u8Hour;
* }IPSAFE_ADP_TIME_S;
*
* 
* @par Description
* This structure stores the time information used by ACL Timer.
*
* @datastruct u8Second  Seconds(0-59)
* @datastruct u8Minute  Minutes(0-59)
* @datastruct u8Hour    Hours(0-23)
*
* @par Note
*
*/
typedef struct tagIpsafeAdpTime
{
    UCHAR u8Second;     /* 0-59 */
    UCHAR u8Minute;     /* 0-59 */
    USHORT u8Hour;      /* 0-23 */
}IPSAFE_ADP_TIME_S;


typedef VOID * IPSAFE_SPINLOCK_ID;   /* Spin lock type handle, different product enviroment spin lock type maybe different */
typedef VOID * IPSAFE_RWLOCK_ID;     /* Read-write lock type handle, different product enviroment Read-write lock type maybe different */


VOID * IPSAFE_ADP_MCMemAlloc(UINT32 u32Size);


VOID * IPSAFE_ADP_MCMemAllocByName(UINT8 *pszName, UINT32 u32Size);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_MCMemFree
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Free the share memory
*  Description: Free the share memory
*        Input: VOID *pvAddr: Memory address<Not null pointer>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID   IPSAFE_ADP_MCMemFree(VOID *pvAddr);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_MCMemFindByName
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Find share memory address by name
*  Description: Find share memory address by name.
*        Input: UINT8 *pszName: Share memory name<Not null pointer>
*       Output: VOID **ppVAddr: if return success, is share memory address<Not null pointer>
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_MCMemFindByName(UINT8 *pszName, VOID **ppVAddr);


UINT32 IPSAFE_ADP_MCMemNameDBAdd(UINT8 *pszName, VOID *pVAddr);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_SpinLockCreate
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Create a spin lock
*  Description: Create a spin lock. When a process get the spin lock, other process can't get
*               it untill the process which got the spin lock release it.
*        Input: UINT8 *pszName: Spin lock name<Not null pointer>
*       Output: IPSAFE_SPINLOCK_ID *pLockID: Pointer to spin lock id<Not null pointer>
*       Return: 0:Success
*               1:Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_SpinLockCreate(UINT8 *pszName, IPSAFE_SPINLOCK_ID *pLockID);


UINT32 IPSAFE_ADP_SpinLockDelete(UINT8 *pszName, IPSAFE_SPINLOCK_ID *pLockID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_RWLockCreate
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Create a read-write lock
*  Description: Create a read-write lock. Different process can read it at the same time,
*               but can't writer and read at the same time
*        Input: UINT8 *pszName: read-write lock<Not null pointer>
*       Output: IPSAFE_RWLOCK_ID *pLockID: read-write id<Not null pointer>
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_RWLockCreate(UINT8 *pszName, IPSAFE_RWLOCK_ID *pLockID);


UINT32 IPSAFE_ADP_RWLockDelete(UINT8 *pszName, IPSAFE_RWLOCK_ID *pLockID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_RWReadLock
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Get read lock
*  Description: Get read lock
*        Input: IPSAFE_RWLOCK_ID RWLockId: Read-write lock ID<Create lock id>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_RWReadLock(IPSAFE_RWLOCK_ID RWLockId);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_RWReadUnLock
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Release read lock
*  Description: Release read lock
*        Input: IPSAFE_RWLOCK_ID RWLockId: Read-write lock ID<Create lock id>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_RWReadUnLock(IPSAFE_RWLOCK_ID RWLockId);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_RWWriteLock
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Get write lock
*  Description: Get write lock
*        Input: IPSAFE_RWLOCK_ID RWLockId: Read-write lock ID<Create lock id>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_RWWriteLock(IPSAFE_RWLOCK_ID RWLockId);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_RWWriteUnLock
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Release write lock
*  Description: Release write lock
*        Input: IPSAFE_RWLOCK_ID RWLockId: Read-write lock ID<Create lock id>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_RWWriteUnLock(IPSAFE_RWLOCK_ID RWLockId);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_SpinLock
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Get the spin lock
*  Description: Get the spin lock, if can't get the spin lock, it will loop untill other process 
*               the spin lock.
*        Input: IPSAFE_SPINLOCK_ID SpinLockID: Spin lock id<All int>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_SpinLock(IPSAFE_SPINLOCK_ID SpinLockID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_SpinUnLock
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Release the spin lock
*  Description: Release the spin lock, then other process can get the spin lock.
*        Input: IPSAFE_SPINLOCK_ID SpinLockID: XXX<Range>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_SpinUnLock(IPSAFE_SPINLOCK_ID SpinLockID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_InfoOutput
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Nat info output function
*  Description: Nat info output function
*        Input: UINT8 *pszInfo: Info char address<Not null pointer>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID   IPSAFE_ADP_InfoOutput(UINT8 *pszInfo);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_AtomicInc
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Automic increase
*  Description: Automic increase
*        Input: UINT32 *pu32TargetAddr: addend address pointer<Not null pointer>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_AtomicInc(UINT32 *pu32TargetAddr);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_AtomicDec
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: Automic decrease
*  Description: Automic decrease
*        Input: UINT32 *pu32TargetAddr: Minuend address pointer<Not null pointer>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_AtomicDec(UINT32 *pu32TargetAddr);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_MemBarrier
* Date Created: 2010-03-26
*       Author: zhangchunyu(62474)
*      Purpose: Memory Barrier
*  Description: Memory Barrier, prevent cpu optimize the execute order.
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-26   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_MemBarrier(VOID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_AtomicSwap
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Atomic exchange data
*  Description: Atomic exchange data. Exchange the pointer content with new data value and
*               output the pointer content
*        Input: UINT32 *ptr: Exchange data address<Not null pointer>
*               UINT32 new_val: Exchange new data value<All int>
*       Output: 
*       Return: Get the pointer content
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_AtomicSwap(UINT32 *ptr, UINT32 new_val);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrLen
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Get string len
*  Description: Get string len
*        Input: CHAR *pcstr: Char string array <Not null pointer>
*       Output: 
*       Return: The char string length
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_StrLen(CHAR *pcstr);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrNCmp
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Compare two string array whether is same
*  Description: Compare two string array whether is same
*        Input: INT8 *pscStr1: String 1<Not null pointer>
*               INT8 * pscStr2:String 2<Not null pointer>
*               UINT32 ulCount:Compare length<All int>
*       Output: 
*       Return: 0:Same
*               Other: Not same 
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
INT32 IPSAFE_ADP_StrNCmp(CHAR *pscStr1, CHAR * pscStr2, UINT32 ulCount);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_Printf
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Print content by format
*  Description: Print content by format
*        Input: CHAR *pscFormat: Format<Not null pointer>
*       Output: 
*       Return: 0: Success
*               Other: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_Printf(CHAR *pscFormat, ...);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_MemCpy
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Memory copy
*  Description: Memory copy source to destination memory
*        Input: VOID *pvDest: Destination memory address<Not null pointer>
*               UINT32 ulDestLen: Destination memory size
*               VOID * pvSrc: Source memory address<Not null pointer>
*               UINT32 uvCount: Copy length<all int>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID *IPSAFE_ADP_MemCpy(VOID *pvDest, UINT32 ulDestLen, VOID * pvSrc, UINT32 uvCount);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_MemSet
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Set memory to specify value
*  Description: 
*        Input: VOID *pvToSet: Memory address<Not null pointer>
*               INT8 scChar: Specify value<All char>
*               UINT32 uvCount: Set value length <all int>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID *IPSAFE_ADP_MemSet(VOID *pvToSet, CHAR scChar, UINT32 uvCount);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrCmp
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Compare two string
*  Description: Compare two string
*        Input: CHAR * pscStr1: String array 1<Not null pointer>
*               CHAR * pscStr2: String array 2<Not null pointer>
*       Output: 
*       Return: 0: Success, the string is same
*               Other: Fail, the string is not same
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
INT32 IPSAFE_ADP_StrCmp(CHAR * pscStr1, CHAR * pscStr2);


INT32 IPSAFE_ADP_MemCmp(VOID *pvDestAddr, VOID *pvSrcAddr, UINT32 u32Size);



/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrTok
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Get the specify char address from a string array
*  Description: Get the specify char address from a string array
*        Input: CHAR * pcstring: String array<Not null pointer>
*               CHAR * pccontrol: String adday address<Not null pointer>
*       Output: 
*       Return: The specify char address
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
CHAR*  IPSAFE_ADP_StrTok(CHAR * pcstring, CHAR * pccontrol);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_UpperCase
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Transfer string to upper
*  Description: Transfer string to upper
*        Input: CHAR *str: String array<Not null pointer>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_UpperCase(CHAR *str);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_Atoul
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Transfer string to long
*  Description: Transfer string to long untill come a letter, like atoul function.
*        Input: CHAR *pcStr: String array<Not null pointer>
*       Output: UINT32 *pulVal: Long value<All int>
*       Return: 0: Success
*               Other: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
INT32 IPSAFE_ADP_Atoul(CHAR *pcStr, UINT32 *pulVal);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrToInt32
* Date Created: 2010-03-30
*       Author: zhangchunyu(62474)
*      Purpose: Transfer string to ulong
*  Description: Transfer string to ulong untill come a letter, like atol function.
*        Input: CHAR *pcStr: String array<Not null pointer>
*       Output: UINT32 *pulVal: ULong value<All int>
*       Return: 0: Success
*               Other: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
INT32 IPSAFE_ADP_StrToInt32(CHAR *szStr, INT32 *pslVal);


/*******************************************************************************
*    Func Name: IPSAFE_ADP_CreateLoopTimer
* Date Created: 2010-04-13
*       Author: z62474/b71224
*      Purpose: This function is used to create NAT Timers.
*  Description: This function calls VOS_Timer_Create/UPB_PubReltmrCbkStart function to create timers 
*        Input: UINT32 u32MiliSec: Time in mili seconds 
*               VOID (*pfTimerFunc)(VOID *): Call back function
*               VOID  *pArg: function arguments
*               UINT32 u32Type: Timer Function identifier for RPU
*       Output: UINT32 *pu32TimerID: Pointer to Timer ID
*       Return: 0: Success
*               Other: Fail
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   z62474/b71224      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_CreateLoopTimer(UINT32 *pu32TimerID, UINT32 u32MiliSec,
                              VOID (*pfTimerFunc)(VOID *), VOID  *pArg, UINT32 u32Type);


/*******************************************************************************
*    Func Name: IPSAFE_ADP_GetVCPUNum
* Date Created: 2010-04-07
*       Author: Vinay Gudur(71924)
*      Purpose: Get the current VCPU NUmber
*  Description: Get the current VCPU NUmber
*        Input: VOID
*       Output: 
*       Return: UINT32 - The VCPU Number
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-26   Vinay Gudur(71924)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetVCPUNum(VOID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_ClearWDG
* Date Created: 2010-06-07
*       Author: zhangchunyu(z62474)
*      Purpose: Clear watch dog
*  Description: Clear watch dog
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   zhangchunyu(z62474)      Create the first version.
*
*******************************************************************************/
VOID IPSAFE_ADP_ClearWDG(VOID);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrnCpy
* Date Created: 2010-07-26
*       Author: Anish(a72338)
*      Purpose: This function is used to copy string from soure to destination
*  Description: This function copies soure string to destination
*        Input: CHAR *pcDstString  : pointer to destination
*               UINT32 ulDstLen     : Destination memory length
*               CHAR *pcSrcString  : pointer to source string
*               UINT32 u32Count     : no of characters to be copied from source to destination 
*       Output: 
*       Return: Success: returns pointer to destination string
*               Failure: returns NULL
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-08   Anish(a72338)           Create the first version.
*
*******************************************************************************/
CHAR * IPSAFE_ADP_StrnCpy(CHAR *pcDstString, UINT32 ulDstLen, CHAR *pcSrcString, UINT32 u32Count);


/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrICmp
* Date Created: 2010-06-08
*       Author: bhaskar(71224)
*      Purpose: This function compares pi8String1 with pi8String2. 
*               Comparision is case insensetive, meaning "A" and "a" 
*               are considered equal.  
*  Description: This function performs case insensitive comparision of two input strings 
*        Input: CHAR *pcString1: pointer to the first string
*               CHAR *picString2: pointer to the second string
*       Output: 
*       Return: Success: returns 0, if both the strings are equal
*               Failure: A value greater than zero indicates that the first 
*                        character that does not match has a greater value in 
*                        pi8String1 than in pi8String2; And a value less than zero 
*                        indicates the opposite.
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-08   bhaskar(71224)      Create the first version.
*
*******************************************************************************/
INT32 IPSAFE_ADP_StrICmp(CHAR *pcString1, CHAR *pcString2);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_StrNiCmp
* Date Created: 2010-06-08
*       Author: bhaskar(71224)
*      Purpose: This function compares pi8String1 with pi8String2 upto u32Count characters. 
*               Comparision is case insensetive, meaning "A" and "a" are considered equal.  
*  Description: This function performs case insensitive comparision of two input 
*               strings upto ulCount characters 
*        Input: CHAR *pcString1: pointer to the first string
*               CHAR *pcString2: pointer to the second string
*       Output: 
*       Return: Success: returns 0, if both the strings are equal upto u32Count characters
*               Failure: A value greater than zero indicates that the first 
*                        character that does not match has a greater value in 
*                        pi8String1 than in pi8String2; And a value less than zero 
*                        indicates the opposite.
*      Caution: 
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-08   bhaskar(71224)      Create the first version.
*
*******************************************************************************/
INT32 IPSAFE_ADP_StrNiCmp(CHAR *pcStr1, CHAR *pcStr2, UINT32 u32Count);



UINT32 IPSAFE_ADP_DelLoopTimer(UINT32 *pu32TimerID);


UINT32 IPSAFE_ADP_WaitListDelFromList(UINT32 ulType, VOID *pDataToDel);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_MCMemNameDBRemove
* Date Created: 2010-07-26
*       Author: Anish a72338
*      Purpose: Used for removing a name from the shared database
*  Description: Used for removing a name from the shared database
*        Input: CHAR * pcName: The name to be removed from the data base
*               UINT32 u32Type: Shared data type
*       Output: 
*       Return: Successful: 0
*      Caution: 
*        Since: V200R003C01
*    Reference: This is just adapter function.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-26   a72338              Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_MCMemNameDBRemove(CHAR* pcName, UINT32 u32Type);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_Tm_Get
* Date Created: 2010-07-26
*       Author: Anish a72338
*      Purpose: Used for getting the current date and time
*  Description: Used for getting the current date and time
*        Input: IPSAFE_ADP_DATE_S *pstDate: To store the current date
*               IPSAFE_ADP_TIME_S *pstTime: To store the currnet time
*               UINT32 *pu32MillSec: To store the milliseconds
*       Output: 
*       Return: Successful: 0
*      Caution: 
*        Since: V200R003C01
*    Reference: This is just adapter function.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-26   a72338              Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_Tm_Get(IPSAFE_ADP_DATE_S *pstDate, IPSAFE_ADP_TIME_S *pstTime, UINT32 *pu32MillSec);


/*******************************************************************************
*    Func Name: IPSAFE_ADP_GetCPUType
* Date Created: 2008-03-31
*       Author: mafeng(59090)
*  Description: 获取ACL编译CPU的类型
*        Input: CHAR *pCPUType:
*       Output: 
*       Return: Help_ACL_OK
*               Help_ACL_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-31   mafeng(59090)           Create
*
*******************************************************************************/
ULONG IPSAFE_ADP_GetCPUType(CHAR *pCPUType,ULONG ulNameLen);

#ifdef  __cplusplus
}
#endif

#endif


#endif

