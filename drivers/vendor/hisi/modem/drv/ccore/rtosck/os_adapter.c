/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : os_adapt.c
  版 本 号   : 初稿
  作    者   : 李江雄 00134988
  生成日期   : 2013年9月4日
  最近修改   :
  功能描述   : 封装操作系统函数
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月4日
    作    者   : 李江雄 00134988
    修改内容   : 创建文件

  说明:
******************************************************************************
  History:                                                                *
    *   1. Date        :                                                  *
    *      Author      :                                                  *
    *      Modification:                                                  *
******************************************************************************/
#include <osal.h>
#include <string.h>
#ifdef __OS_RTOSCK__
#include <sre_sem.h>
#include <sre_mem.h>
#include <sre_cache.h>
#include <sre_sys.h>
#include <sre_shell.h>
#include <sre_hunt.h>
#include <sre_task.h>
#include <sre_hwi.h>
#include <sre_tick.h>
#else
#include <semLib.h>
#include <memPartLib.h>
#include <private/vmLibP.h>
#include <tickLib.h>
#include <taskHookLib.h>
#include <cacheLib.h>
extern MMU_LIB_FUNCS mmuLibFuncs;
#endif
#include <bsp_om.h>
#ifdef __OS_VXWORKS__
extern void vicIntLvlChgHookAdd(FUNCPTR p_FuncIn, FUNCPTR p_FuncOut);
extern STATUS taskCreateHookAdd(FUNCPTR createHook);
extern STATUS taskSwitchHookAdd(FUNCPTR switchHook);
extern STATUS taskCreateHookDelete(FUNCPTR createHook);
extern STATUS taskSwitchHookDelete(FUNCPTR switchHook);
extern int sysClkRateGet(void);
extern void * malloc(unsigned int nBytes);
extern void * calloc(unsigned int elemNum,unsigned int elemSize);
extern void free(void * ptr);
#endif
#define TIMER_DEFAULT_TICKS             100


/******************************************************************************
                        semaphore adapt
******************************************************************************/
/*************************************************
*  Function:  OSAL_SemMCreate
*  Description: creat mutex semphore
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*        int options: 
                               OSAL_SEM_FIFO
                               OSAL_SEM_PRIORITY
                               OSAL_SEM_INVERSION_SAFE   no priority inversion (mutex opt.)         

*  Output:
*         N/A
*  Return:
*         OSAL_SEM_ID
*************************************************/
/*lint -e702 -e713 -e732 -e734 -e737 -e573*/
int OSAL_SemMCreate (OSAL_SEM_ID * mutex, int options)
{
    OSAL_SEM_ID semId;
    UINT32 ret = OSAL_OK;
#ifdef __OS_RTOSCK__    
    if(options&OSAL_SEM_INVERSION_SAFE)
    {
        ret = SRE_SemBCreate(OSAL_SEM_FULL, &semId, (OS_SEM_MODE_E)(options&~OSAL_SEM_INVERSION_SAFE));
        /*to ensure the sem rtosck created from 1*/
        if(0 == semId)
        {
              ret = SRE_SemBCreate(OSAL_SEM_FULL, &semId, (OS_SEM_MODE_E)(options&~OSAL_SEM_INVERSION_SAFE));  
        }
    }
    else
    {
        ret = SRE_SemCCreate(OSAL_SEM_FULL, &semId, (OS_SEM_MODE_E)options);
        /*to ensure the sem rtosck created from 1*/
        if(0 == semId)
        {
              ret = SRE_SemCCreate(OSAL_SEM_FULL, &semId, (OS_SEM_MODE_E)options); 
        }
        
        (void)SRE_SemCMaxCountSet(semId,OSAL_SEM_FULL);        
    } 
    if(ret != SRE_OK)
#else 
    semId = semMCreate(options);
    if (!semId)     
#endif  
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return  OSAL_ERROR;
    }
    *mutex = semId;
    return OSAL_OK;    
}

/*************************************************
*  Function:  OSAL_SemBCreate
*  Description: creat binary semphore
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*        int options: 
                                OSAL_SEM_Q_FIFO      first in first out queue 
                                OSAL_SEM_Q_PRIORITY   priority sorted queue
          int count:
                               OSAL_SEM_FULL      initialState is 1
                               OSAL_SEM_EMPTY   initialState is 0

*  Output:
*         N/A
*  Return:
*         OSAL_OK
*         OSAL_ERROR
*  Notify:SRE_SemBCreate cannot support OSAL_SEM_FULL+OSAL_SEM_Q_FIFO
*************************************************/

int OSAL_SemBCreate (OSAL_SEM_ID *mutex,int count, int options)
{
    OSAL_SEM_ID semId;
    UINT32 ret = OSAL_OK;
#ifdef __OS_RTOSCK__
    if(count != OSAL_SEM_FULL)
    {
        ret = SRE_SemBCreate(count, &semId, (OS_SEM_MODE_E)options);  
        /*to ensure the sem rtosck created from 1*/
        if(0 == semId)
        {
              ret = SRE_SemBCreate(count, &semId, (OS_SEM_MODE_E)options);   
        }
    }    
    else
    {
        ret = SRE_SemCCreate(OSAL_SEM_FULL, &semId, (OS_SEM_MODE_E)options); 
        /*to ensure the sem rtosck created from 1*/
        if(0 == semId)
        {
              ret = SRE_SemCCreate(OSAL_SEM_FULL, &semId, (OS_SEM_MODE_E)options); 
        }
        (void)SRE_SemCMaxCountSet(semId,OSAL_SEM_FULL);        
    } 
    if(ret != SRE_OK)
#else
    semId = semBCreate(options,count);
    if (!semId)
#endif    
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return  OSAL_ERROR;
    }
    *mutex = semId;
    return OSAL_OK;
    
}

/*************************************************
*  Function:  OSAL_SemCCreate
*  Description: creat mutex semphore
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*        int options: 
                                OSAL_SEM_Q_FIFO      first in first out queue 
                                OSAL_SEM_Q_PRIORITY   priority sorted queue
          int initialCount: initial count value

*  Output:
*         N/A
*  Return:
*         OSAL_SEM_ID
*************************************************/
int OSAL_SemCCreate (OSAL_SEM_ID *mutex,int count, int options)
{
    OSAL_SEM_ID semId;
    UINT32 ret = OSAL_OK;
#ifdef __OS_RTOSCK__    
    ret = SRE_SemCCreate(count, &semId, (OS_SEM_MODE_E)options); 
    /*to ensure the sem rtosck created from 1*/
    if(0 == semId)
    {
          ret = SRE_SemCCreate(count, &semId, (OS_SEM_MODE_E)options); 
    }
    if(ret != SRE_OK)
#else
    semId = semCCreate(options,count);
    if (!semId)
#endif    
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return  OSAL_ERROR;
    }
    *mutex = semId;
    return OSAL_OK;    
}

/*************************************************
*  Function:  OSAL_SemTake
*  Description: take semphore
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       OSAL_SEM_ID SemId:  semid
                            
         int timeout : 
                          #define OSAL_NO_WAIT      0
                          #define  OSAL_WAIT_FOREVER    (-1)
                          other- wait ticks

*  Output:
*         N/A
*  Return:
*         0:OK
          other:ERROR
*************************************************/
int OSAL_SemTake(OSAL_SEM_ID mtx_h,unsigned int timeout)
{
    UINT32 ret;
#ifdef __OS_RTOSCK__
    ret = SRE_SemPend(mtx_h, timeout); 
#else
    ret = semTake(mtx_h, (int)timeout);
#endif
    return (int)ret;
}

/*************************************************
*  Function:  OSAL_SemGive
*  Description: give semphore
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       OSAL_SEM_ID SemId:  semid
                            
       
*  Output:
*         N/A
*  Return:
*         0:OK
*         other:ERROR
*************************************************/
int OSAL_SemGive(OSAL_SEM_ID mtx_h)
{
    UINT32 ret;
#ifdef __OS_RTOSCK__
    ret = SRE_SemPost(mtx_h); 
#else
    ret = semGive(mtx_h);
#endif
    return (int)ret;
}

/*************************************************
*  Function:  OSAL_SemDelete
*  Description: delete semphore
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       OSAL_SEM_ID SemId:  semid
                            
       
*  Output:
*         N/A
*  Return:
*         0:OK
*         other:ERROR
*************************************************/
int osal_semDelete(OSAL_SEM_ID *mtx_h)
{
    UINT32 ret = OSAL_OK;
#ifdef __OS_RTOSCK__
    if(*mtx_h != 0xffff)
    {
        ret = SRE_SemDelete(*mtx_h); 
        *mtx_h = 0xffff;
    }    
#else
    if(*mtx_h != NULL)
    {
        ret = (int)semDelete(*mtx_h);
        *mtx_h = NULL;
    }     
#endif
    if(ret != OSAL_OK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
    return OSAL_OK;
}


/******************************************************************************
                        memory adapt
******************************************************************************/
/*************************************************
*  Function:  OSAL_Malloc
*  Description: malloc from memory
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       int nBytes: the size of malloc memory
                            
       
*  Output:
*         N/A
*  Return:
         memory block pointer
         
*         
*************************************************/
void * OSAL_Malloc ( unsigned int nBytes )
{
#ifdef __OS_RTOSCK__
    return SRE_MemCacheAlloc(nBytes,(OS_MEM_ALIGN_E)MEM_ADDR_ALIGN_004); 
#else
    return malloc(nBytes); /*[false alarm]*/
#endif
}
/*************************************************
*  Function:  OSAL_Calloc
*  Description: malloc items*Bytes space from memory
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       int Bytes: the size of every block malloc memory
*       int elemNum: the number of malloc block      
       
*  Output:
*         N/A
*  Return:
         memory block pointer
         
*         
*************************************************/

void * OSAL_Calloc ( unsigned int elemNum, unsigned int Bytes)
{
#ifdef __OS_RTOSCK__
    void *p = NULL;
    p = SRE_MemCacheAlloc(elemNum*Bytes,(OS_MEM_ALIGN_E)MEM_ADDR_ALIGN_004); 
    if(NULL == p)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"OSAL_Calloc is fail!\n");
        return NULL;
    }
    (void)memset(p, 0, elemNum*Bytes);
    return p;
#else
    return calloc( elemNum, Bytes);
#endif

}
/*************************************************
*  Function:  OSAL_Calloc
*  Description: realloc memory
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       void * pBlock: point the old memory
*       int newSize: the number of malloc block      
       
*  Output:
*         N/A
*  Return:
         new memory block pointer
         
*         
*************************************************/
void * OSAL_Realloc ( void * pBlock,    unsigned int newSize    )
{
#ifdef __OS_RTOSCK__
    void * pNewBlock = NULL;
    if( 0 == newSize)
    {
        (void)SRE_MemCacheFree(pBlock);
        return NULL;
    }   
    pNewBlock = SRE_MemCacheAlloc(newSize,(OS_MEM_ALIGN_E)MEM_ADDR_ALIGN_004); 
    if ((pNewBlock != NULL) && (pBlock != NULL))
    {
        (void)memcpy(pNewBlock, pBlock, newSize);
        (void)SRE_MemCacheFree(pBlock);        
    }
    return pNewBlock;
#else
    return realloc( pBlock, newSize);
#endif
}


/*************************************************
*  Function:  OSAL_MemAlign
*  Description: malloc from memory
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       int nBytes: the size of malloc memory
                            
       
*  Output:
*         N/A
*  Return:
         memory block pointer
*         
*************************************************/
void * OSAL_MemAlign (unsigned int align_size,unsigned int nBytes )
{
#ifdef __OS_RTOSCK__
    int count = 2;
    int align = align_size >> 2;
    while((align >> 1) > 0)
    {
        count ++ ;
        align = align >> 1;
    }
    if(align > MEM_ADDR_ALIGN_16K)
    {
        return NULL;
    }
    return SRE_MemCacheAlloc(nBytes,(OS_MEM_ALIGN_E)count); 
#else
    return memalign(align_size,nBytes);
#endif
}


/*************************************************
*  Function:  OSAL_CacheDmaMalloc
*  Description: malloc from memory uncached
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       int nBytes: the size of malloc memory
                            
       
*  Output:
*         N/A
*  Return:
         memory block pointer
*         
*************************************************/
void * OSAL_CacheDmaMalloc ( unsigned int nBytes )
{
#ifdef __OS_RTOSCK__
    return SRE_MemUncacheAlloc(nBytes,(OS_MEM_ALIGN_E)MEM_ADDR_ALIGN_4K); 
#else
    return cacheDmaMalloc(nBytes);
#endif
}

/*************************************************
*  Function:  OSAL_Free
*  Description: free malloc memory
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       void *ptr: memory block pointer
                            
       
*  Output:
*         N/A
*  Return:
          N/A
         
*         
*************************************************/
void OSAL_Free( void *ptr)
{
#ifdef __OS_RTOSCK__
    (void)SRE_MemCacheFree(ptr); 
#else
    free(ptr);
#endif
    return;
}

/*************************************************
*  Function:  OSAL_CacheDmaFree
*  Description: free malloc memory
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       void *ptr: memory block pointer
                            
       
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
         
*         
*************************************************/
int OSAL_CacheDmaFree ( void *ptr )
{
#ifdef __OS_RTOSCK__
    return SRE_MemUncacheFree(ptr); 
#else
    return cacheDmaFree(ptr);
#endif
}

/*************************************************
*  Function:  OSAL_VmStateSet
*  Description: set MMU state
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*    context:    context - NULL == currentContext 
*    virtAdrs:   virtual address to modify state of 
*    len:        len of virtual space to modify state of 
*    stateMask:      state mask 
*    state:      state 
       
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
         
*         
*************************************************/
int OSAL_VmStateSet ( void *context,unsigned int virtAdrs, unsigned int len,
            unsigned int stateMask,unsigned int state)
{
#ifdef __OS_RTOSCK__
    return SRE_MmuStateSet(virtAdrs,len,0,state); 
#else
    return vmStateSet(context,virtAdrs,len,stateMask,state);
#endif
}

/*************************************************
*  Function:  OSAL_MmuPageMap
*  Description: MMU page map
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*    context:    context - NULL == currentContext 
*    uwVirtAddr:     virtual address to modify state of 
*    uwPhysAddr  physical address
*    uwLen:          len of virtual space to modify state of 
*    uwStateMask:    state mask 
*    uwState:        state 
       
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
         
*         
*************************************************/
int OSAL_MmuPageMap(void *context, unsigned int uwVirtAddr, unsigned int uwPhysAddr, 
    unsigned int uwLen, unsigned int uwStateMask, unsigned int uwState)
{
#ifdef __OS_RTOSCK__
    return (int)SRE_MmuAssign((void *)uwVirtAddr,(void *)uwPhysAddr,uwLen,uwState); 
#else
    return vmPageMap(context,uwVirtAddr,uwPhysAddr,uwLen,uwStateMask,uwState);
#endif
}

/*************************************************
*  Function:  OSAL_MmuEnable
*  Description: MMU  enable
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*    enable: mmu enbale or not. 
       
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
         
*         
*************************************************/
int OSAL_MmuEnable(int enable)
{
#if defined(__OS_VXWORKS__)
    return (MMU_ENABLE(enable));
#elif defined(__OS_RTOSCK__)
    if(enable)
    {
        return SRE_MmuEnable();
    }
    else
    {
        return SRE_MmuDisable();
    }   
#endif
}

/******************************************************************************
                        task adapt
******************************************************************************/
/*************************************************
*  Function:  OSAL_TaskCreate
*  Description: create task
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       name:       task name
*       priority:   task priority
*       options:    task option word
*       stackSize:  task stack Size
*       entryPt:    task entry
*       arg1:       task entry arg1
*       arg2:       task entry arg2
*       arg3:       task entry arg3
*       arg4:       task entry arg4
*  Output:
*       task:       point to task manage info
*  Return:
         OSAL_OK/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskCreate(
    OSAL_TASK_ID *     tskid,
    char *        name,         /* name of new task (stored at pStackBase) */
    int           priority,     /* priority of new task */
    int           options,      /* task option word */
    int           stackSize,    /* size (bytes) of stack needed plus name */
    OSAL_TASK_FUNC       entryPt,      /* entry point of new task */
    int           arg1,         /* 1st of 10 req'd args to pass to entryPt */
    int           arg2,
    int           arg3,
    int           arg4
    )
{
    OSAL_TASK_ID id;
    int ret = OSAL_ERROR;
#ifdef __OS_RTOSCK__ 
    TSK_INIT_PARAM_S tsk;   
    tsk.pfnTaskEntry  = (OSAL_TASK_FUNC)entryPt;
    tsk.uwStackSize   = stackSize;
    tsk.usTaskPrio    = priority;
    tsk.pcName        = name;
    tsk.usQNum        = 0;
    tsk.auwArgs[0]    = arg1;
    tsk.auwArgs[1]    = arg2;
    tsk.auwArgs[2]    = arg3;
    tsk.auwArgs[3]    = arg4;
    tsk.uwStackAddr   = 0;
    ret = SRE_TaskCreate((UINT32 *)&id,&tsk);
    if(ret != SRE_OK)
#else
    id = taskSpawn(name,priority,options,stackSize,(OSAL_TASK_FUNC)entryPt,arg1,arg2,
                arg3,arg4,0,0,0,0,0,0);
    if (id == (int)OSAL_NULL)           /* create failed */
#endif
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
    *tskid = id; /*[false alarm]*/
    return OSAL_OK;
}

/*************************************************
*  Function:  OSAL_TaskDelete
*  Description: delete task
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       task:       point to task manage info
                            
       
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int osal_taskDelete( OSAL_TASK_ID * tskid )
{
    int ret = OSAL_OK;
#ifdef __OS_RTOSCK__
    if(*tskid != 0xffffffff)
    {
        ret = SRE_TaskDelete(*tskid);
        *tskid = 0xffffffff;
    }    
#else
    if(*tskid != (OSAL_TASK_ID)NULL)
    {
        ret = taskDelete((int)*tskid) ;
        *tskid = (OSAL_TASK_ID)NULL;
    }    
#endif
    if(ret != OSAL_OK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
    return OSAL_OK;
}

/*************************************************
*  Function:  OSAL_TaskSuspend
*  Description: suspend task
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       ticks:       ticks for delay
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*************************************************/
int OSAL_TaskSuspend(OSAL_TASK_ID  tskid )
{
#ifdef __OS_RTOSCK__
    return SRE_TaskSuspend(tskid);
#else
    return taskSuspend((int)tskid) ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskDelay
*  Description: delay task
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
*       ticks:       ticks for delay
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*************************************************/
int OSAL_TaskDelay(int ticks )
{
#ifdef __OS_RTOSCK__
    return SRE_TaskDelay((unsigned int)ticks);
#else
    return taskDelay(ticks) ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskSelf
*  Description: get task id
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
       N/A
*  Output:
*         N/A
*  Return:
         task id/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskSelf(void)
{
#ifdef __OS_RTOSCK__
    unsigned int id;
    int ret;
    ret = SRE_TaskSelf((unsigned int *)&id);
    if(OSAL_OK == ret)
    {
        return id;
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
#else
    return taskIdSelf() ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskIdByName
*  Description: get task id by name
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
       name:task name
*  Output:
*         N/A
*  Return:
         task id/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskIdByName(char * name)
{
#ifdef __OS_RTOSCK__
    unsigned int id;
    int ret;
    ret = SRE_HuntByName(0,name,&id);
    if(OSAL_OK == ret)
    {
        return id;
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
#else
    return taskNameToId(name) ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskIDVerify
*  Description: Verify task id 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
       taskID:task id
*  Output:
*         N/A
*  Return:
         OSAL_OK/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskIDVerify(int taskID)
{
#ifdef __OS_RTOSCK__
    BOOL ret;

    ret = SRE_TaskIDCheck((unsigned int) taskID);
    if(TRUE == ret)
    {
        return OSAL_OK;
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
#else
    return (int)taskIdVerify(taskID); 
#endif
}

/*************************************************
*  Function:  OSAL_TaskIdListGet
*  Description: get task list
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:    
*         N/A
*  Output:
*         N/A
*  Return: 
*         current tick value
*************************************************/
int OSAL_TaskIdListGet(int idList[], unsigned int maxTasks, unsigned int *pTaskNum)
{
#ifdef __OS_RTOSCK__
    *pTaskNum = maxTasks;
    if(OSAL_OK != SRE_TaskIDList(( unsigned short *)pTaskNum,(unsigned int *)idList))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error\n",__FUNCTION__,__LINE__);
        return OSAL_ERROR;
    }

#else
    *pTaskNum = taskIdListGet(idList,(int)maxTasks);
#endif    
    return OSAL_OK;
}

/*************************************************
*  Function:  OSAL_TaskNameGet
*  Description: Get task name 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
       taskID:task id
*  Output:
*      pName:  task name
*  Return:
         OSAL_OK/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskNameGet(int taskID,char **pName)
{
#ifdef __OS_RTOSCK__
    if(OSAL_OK != SRE_TaskNameGet((unsigned int)taskID,pName))    
#else
    *pName = taskName(taskID); 
    if( NULL == *pName )    
#endif
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error\n",__FUNCTION__,__LINE__);
        return OSAL_ERROR;
    }
    return OSAL_OK;
}


/*************************************************
*  Function:  OSAL_TaskPriorityGet
*  Description: get task Priority
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
       task:task info       
*  Output:
*         pPriority
*  Return:
         OSAL_OK/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskPriorityGet(int taskID, int * pPriority)
{
#ifdef __OS_RTOSCK__
    int ret;
    ret = SRE_TaskPriorityGet(taskID,(TSK_PRIOR_T *)pPriority) ;
    if(OSAL_OK != ret)    
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
    return OSAL_OK;
#else
    return taskPriorityGet(taskID,pPriority) ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskPrioritySet
*  Description: SET task Priority
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:
       task:task info  
       pPriority
*  Output:
*         N/A
*  Return:
         OSAL_OK/OSAL_ERROR
*         
*************************************************/
int OSAL_TaskPrioritySet(int taskID, int pPriority)
{
#ifdef __OS_RTOSCK__
    int ret;
    ret = SRE_TaskPrioritySet(taskID,pPriority) ;
    if(OSAL_OK != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error:%d\n",__FUNCTION__,__LINE__,ret);
        return OSAL_ERROR;
    }
    return OSAL_OK;
#else
    return taskPrioritySet(taskID,pPriority) ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskLock
*  Description: lock task
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          N/A
*  Output:
*         N/A
*  Return:
          N/A
*         
*************************************************/
void OSAL_TaskLock(void)
{
#ifdef __OS_RTOSCK__
    SRE_TaskLock();
#else
    taskLock() ;
#endif
    return;
}

/*************************************************
*  Function:  OSAL_TaskUnLock
*  Description: unlock task
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          N/A
*  Output:
*         N/A
*  Return:
          N/A
*************************************************/
void OSAL_TaskUnLock(void)
{
#ifdef __OS_RTOSCK__
    SRE_TaskUnlock();
#else
    taskUnlock() ;
#endif
    return;
}

/******************************************************************************
                        interrupter adapt
******************************************************************************/
/*************************************************
*  Function:  OSAL_IntConnect
*  Description: connects a common interrupt dispatcher
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          num:      interrupt number
          routine:  interrupt dispatcher
          parameter:interrupt dispatcher parameter
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int OSAL_IntConnect( unsigned int num, OSAL_INTERRUPT_FUNC routine, int parameter )
{
#ifdef __OS_RTOSCK__
    (void)SRE_HwiSetAttr(num, SRE_HWI_PRIORITY0, OS_HWI_MODE_ENGROSS);
    return SRE_HwiCreate(num,routine,(HWI_ARG_T)parameter);
#else
    return intConnect((VOIDFUNCPTR *)num,routine,parameter);
#endif
}

/*************************************************
*  Function:  OSAL_IntDisconnect
*  Description: Disconnects a common interrupt dispatcher
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          num:      interrupt number
          routine:  interrupt dispatcher
          parameter:interrupt dispatcher parameter
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int OSAL_IntDisconnect( unsigned int num, OSAL_INTERRUPT_FUNC routine, int parameter )
{
#ifdef __OS_RTOSCK__
    return SRE_HwiDelete(num);
#else
    return intDisconnect((VOIDFUNCPTR *)num,routine,parameter);
#endif
}

/*****************************************************************************
 函数名: OSAL_INT_CONTEXTS
 功能描述 : 判断当前任务是否在中断上下文
 输入参数 : 无
 输出参数 : 无
 返回值   ： 0 代表非中断
           ：1  代表中断
*****************************************************************************/
unsigned int OSAL_INT_CONTEXT(void)
{
#ifdef __OS_RTOSCK__
    int ret;
    ret = SRE_CurThreadType();
    if(SYS_HWI == ret ||(SYS_SWI == ret))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#else
    return (unsigned int)INT_CONTEXT(); 
#endif
}

/*************************************************
*  Function:  OSAL_IntEnable
*  Description: enable interrupt 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          num:      interrupt number
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int OSAL_IntEnable( unsigned int num )
{
#ifdef __OS_RTOSCK__
    return SRE_HwiEnable(num);
#else
    return intEnable ((int)num);
#endif
}

/*************************************************
*  Function:  OSAL_IntDisable
*  Description: disable interrupt 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          num:      interrupt number
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int OSAL_IntDisable( unsigned int num )
{
#ifdef __OS_RTOSCK__
    if(OS_ERRNO_HWI_NUM_INVALID == SRE_HwiDisable(num))
    {
        return OSAL_ERROR;
    }
    return OSAL_OK;
#else
    return intDisable ((int)num);
#endif
}



/*************************************************
*  Function:  OSAL_IntLock
*  Description: lock interrupt 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          N/A
*  Output:
*         N/A
*  Return:
         An architecture-dependent lock-out key for the interrupt level
         
*         
*************************************************/

int OSAL_IntLock(void)
{
#ifdef __OS_RTOSCK__
    //if(CALC_INTERRUPT_FUN_ON == g_calcfunswitch)
    //{
       // exchGetFirstTick();
    //}
    return SRE_IntLock();
#else
    return intLock() ;
#endif
}

/*************************************************
*  Function:  OSAL_IntUnLock
*  Description: unlock interrupt 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          s32Lvl:returned by a preceding OSAL_IntLock() call
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/

void OSAL_IntUnLock( int s32Lvl)
{
#ifdef __OS_RTOSCK__
    SRE_IntRestore(s32Lvl);
    //if(CALC_INTERRUPT_FUN_ON == g_calcfunswitch)
    //{
       // exchGetLockInterruptTime();
    //}
#else
    intUnlock(s32Lvl) ;
#endif
}

/*************************************************
*  Function:  OSAL_TaskCreateHookAdd
*  Description: task create hook add function. 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          hook function
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/
int OSAL_TaskCreateHookAdd(OSAL_FUNCPTR hook)
{
#ifdef __OS_RTOSCK__
    return SRE_HookAdd(OS_HOOK_TSK_CREATE, hook);
#else
    return taskCreateHookAdd(hook);
#endif
}

/*************************************************
*  Function:  OSAL_TaskSwitchHookAdd
*  Description: task switch hook add function. 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          hook function
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/
int OSAL_TaskSwitchHookAdd(OSAL_FUNCPTR hook)
{
#ifdef __OS_RTOSCK__
    return SRE_HookAdd(OS_HOOK_TSK_SWITCH, hook);
#else
    return taskSwitchHookAdd(hook);
#endif
}

/*************************************************
*  Function:  OSAL_TaskCreateHookDel
*  Description: task create hook del function. 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          hook function
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/
int OSAL_TaskCreateHookDel(OSAL_FUNCPTR hook)
{
#ifdef __OS_RTOSCK__
    return SRE_HookDel(OS_HOOK_TSK_CREATE, hook);
#else
    return taskCreateHookDelete(hook);
#endif
}

/*************************************************
*  Function:  OSAL_TaskSwitchHookDel
*  Description: task switch hook del function. 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          hook function
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/
int OSAL_TaskSwitchHookDel(OSAL_FUNCPTR hook)
{
#ifdef __OS_RTOSCK__
    return SRE_HookDel(OS_HOOK_TSK_SWITCH, hook);
#else
    return taskSwitchHookDelete(hook);
#endif
}

/*************************************************
*  Function:  OSAL_IntHookAdd
*  Description: system int hook add function. 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          hook function
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/
int OSAL_IntHookAdd(OSAL_FUNCPTR in_hook,OSAL_FUNCPTR out_hook)
{
#ifdef __OS_RTOSCK__
    (void)SRE_HookAdd(OS_HOOK_HWI_ENTRY, in_hook);
    (void)SRE_HookAdd(OS_HOOK_HWI_EXIT, out_hook);
    return OSAL_OK;
#else
    vicIntLvlChgHookAdd(in_hook, out_hook);
    return OSAL_OK; 
#endif
}

/*************************************************
*  Function:  OSAL_ExcHookAdd
*  Description: system exc hook add function. 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          hook function
*  Output:
*         N/A
*  Return:
         N/A
*         
*************************************************/
int OSAL_ExcHookAdd(OSAL_FUNCPTR hook)
{
#ifdef __OS_RTOSCK__
    return SRE_ExcRegHook((EXC_PROC_FUNC)hook);
#else
    excHookAdd(hook);
    return OSAL_OK; 
#endif
}

/******************************************************************************
                        cache adapt
******************************************************************************/
/*************************************************
*  Function:  OSAL_CacheFlush
*  Description: flush cache 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          type: dcache or icache
          address: start flush address
          bytes: flush bytes
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int OSAL_CacheFlush( OSAL_CACHE_TYPE type,void *address,unsigned int bytes  )
{
    int ret = OSAL_OK;
#ifdef __OS_RTOSCK__
    if(OSAL_DATA_CACHE == type)
    {
        ret =  SRE_DCacheFlush(address,bytes,TRUE);
    }
#else
    ret = (int)cacheFlush (type,address,bytes);
#endif
    return ret; 
}

/*************************************************
*  Function:  OSAL_CacheInvalid
*  Description: Invalid cache 
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:                            
          type: dcache or icache
          address: start Invalid address
          bytes: Invalid bytes
*  Output:
*         N/A
*  Return:
         0:ok
         other:error
*         
*************************************************/
int OSAL_CacheInvalid( OSAL_CACHE_TYPE type,void *address,unsigned int bytes  )
{
#ifdef __OS_RTOSCK__
    if(OSAL_DATA_CACHE == type)
    {
        return SRE_DCacheInv(address,bytes,TRUE);
    }
    else
    {
        return SRE_ICacheInv(address,bytes,TRUE);
    }
#else
    return (int)cacheInvalidate (type,address,bytes);
#endif
}

/******************************************************************************
                        system adapt
******************************************************************************/
/*************************************************
*  Function:  OSAL_TickGet
*  Description: get current tick
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:    
*         N/A
*  Output:
*         N/A
*  Return: 
*         current tick value
*************************************************/
OSAL_TICK_T OSAL_TickGet( void )
{
#ifdef __OS_RTOSCK__
    return SRE_TickCountGet();
#else
    return tickGet ();
#endif
}

/*************************************************
*  Function:  OSAL_TickSet
*  Description: set current tick
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:    
*         N/A
*  Output:
*         N/A
*  Return: 
*         current tick value
*************************************************/
void OSAL_TickSet( OSAL_TICK_T tick )
{
#ifdef __OS_RTOSCK__
    int lock ;
    OSAL_TICK_T * ultick ;
    lock = OSAL_IntLock();
    ultick = (OSAL_TICK_T *)SRE_GetTickAddr();
    *ultick = tick;
    OSAL_IntUnLock(lock);
#else
    tickSet (tick);
#endif
    return;
}

#ifdef __OS_RTOSCK__
static struct SysWdTime  g_wdtime ;

/*************************************************
*  Function:  OSAL_TickISR
*  Description: RTOS tick interrupt dispose function
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:    
*         N/A
*  Output:
*         N/A
*  Return: 
*         N/A
*************************************************/
int OSAL_TickISR(void)
{
    int ret = OSAL_OK;
    
    SRE_TickISR();
    if(g_wdtime.flag == TRUE)
    {
        g_wdtime.delay -- ;
        if( ( g_wdtime.delay == 0 )&&( g_wdtime.pRoutine != NULL ) )
        {
            g_wdtime.flag = FALSE ;
            ret = g_wdtime.pRoutine(g_wdtime.parameter);               
        }
    }
    return ret;
}


/*************************************************
*  Function:  OSAL_WdTimerReg
*  Description: RTOS register wdtimer function
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:    
    int     delay,               delay count, in ticks 
    OSAL_TIMER_HANDLER pRoutine,            routine to call on time-out 
    int     parameter            parameter with which to call routine 
*  Output:
*         N/A
*  Return: 
*         N/A
*************************************************/
int  OSAL_WdTimerReg (int delay,OSAL_TIMER_HANDLER pRoutine, int para )
{
    if ( TRUE == g_wdtime.flag) 
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error\n",__FUNCTION__,__LINE__);
        return OSAL_ERROR;
    }        

    g_wdtime.delay = delay;
    g_wdtime.pRoutine = pRoutine;
    g_wdtime.parameter = para;
    g_wdtime.flag = TRUE;
    return OSAL_OK;
}

#endif

/*************************************************
*  Function:  OSAL_TickGet
*  Description: get current tick
*  Called By: 
*  Table Accessed:
*  Table Updated:
*  Input:    
*         N/A
*  Output:
*         N/A
*  Return: 
*         current tick value
*************************************************/
int OSAL_SysClkRateGet( void )
{
#ifdef __OS_RTOSCK__
    return SRE_TickPerSecondGet();
#else
    return sysClkRateGet ();
#endif
}


/******************************************************************************
                        RTOSCK shell adapt
******************************************************************************/
#ifdef __OS_RTOSCK__
static OSAL_SHELL_TYPE s_shell_type = OSAL_SHELL_UART;
static OSAL_SHELL_MODE s_shell_mode = OSAL_SHELL_OPEN;

void OSAL_SetShellType(OSAL_SHELL_TYPE type)
{
    s_shell_type = type;
}

OSAL_SHELL_TYPE OSAL_GetShellType(void)
{
    return s_shell_type;
}

void OSAL_SetShellMode(OSAL_SHELL_MODE mode)
{
    s_shell_mode = mode;
}

OSAL_SHELL_MODE OSAL_GetShellMode(void)
{
    return s_shell_mode;
}

unsigned int OSAL_SendChrToShell(OSAL_SHELL_TYPE shelltype,unsigned char ucChar)
{
    if(( shelltype != s_shell_type )||(s_shell_mode != OSAL_SHELL_OPEN))
    {
        return (unsigned int )OSAL_ERROR;
    }

    return SRE_SendChrToShell(ucChar);
}
#endif


#ifdef __OS_RTOSCK__
/*****************************************************************************
 函数名: clock_gettime
 功能描述 : 获取从系统启动到当前时间经历的s及ns
 输入参数 :int clock_id
 输出参数 : struct timespec * tp
 返回值   ： 0 获取成功
          ：-1 获取失败
*****************************************************************************/
int os_clock_gettime(int clock_id,struct os_timespec * tp)
{

    UINT64     diffTicks;   /* system clock tick count */

    if(NULL == tp)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ALL,"%s:%d:error\n",__FUNCTION__,__LINE__);
        return OSAL_ERROR;  
    }

    diffTicks = SRE_TickCountGet();

    CONVERT_TO_SEC (*tp, diffTicks);

    return OSAL_OK;
}
/*****************************************************************************
 函数名: time
 功能描述 : 获取从系统启动到当前时间经历的s
 输入参数 :time_t *timer 
 输出参数 : time_t
 返回值   ： 从系统启动到当前的时间，单位为s
*****************************************************************************/
#if 0
time_t time ( time_t *timer )
{
    UINT64     diffTicks;   /* system clock tick count */
    struct os_timespec tp = {0,0};
    diffTicks = SRE_TickCountGet();
    CONVERT_TO_SEC (tp, diffTicks);
    if(timer)
    {
        *timer = tp.tv_sec;
    }
    return (time_t)tp.tv_sec;
}
#endif
/*lint +e702 +e713 +e732 +e734 +e737 +e573*/
int fflush(int *fp)
{
    return 0;
}

int fclose(int *fp)
{
    return 0;
}
#endif
