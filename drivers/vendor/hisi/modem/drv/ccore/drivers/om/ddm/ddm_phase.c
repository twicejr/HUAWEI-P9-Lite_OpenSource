
/*lint --e{534,801} */
#include <osl_thread.h>
#include <osl_malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "product_config.h"
#include "bsp_shared_ddr.h"
#include "bsp_hardtimer.h"
#include "bsp_om.h"
#include "ddm_phase.h"

#ifdef CONFIG_DDM

#define PHASE_MAX_NAME_SIZE     256

#define RANGE_CONFLICT(s1,e1,s2,e2) ((((s1) >= (e2))||((s2) >= (e1)))?FALSE:TRUE)
#define ALIGN_SIZE(p, a)  (((p) + ((a) - 1)) & ~((a) - 1))

#define  ddm_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_DDM, fmt, ##__VA_ARGS__))

typedef enum
{
    POOL_DIRECT_SINGLE,                 /*when  pool reach end, stop malloc buffer */
}DDM_POOL_TYPE;

typedef enum
{
    POOL_PARENT_LOAD,                   /*pool controller is inited in fastboot*/
    POOL_PARENT_OS                      /*pool controller is inited in vxworks OS*/
}DDM_POOL_PARENT;


typedef struct _buff_list
{
    unsigned int    bufSize  ;
    struct _buff_list *p_next;
}DDM_BUFF_LIST;

typedef struct
{
   DDM_BUFF_LIST*          pData;       /*point to the start of dump data list*/
   DDM_BUFF_LIST*          poolTail;    /*point to the last pool buff */
   unsigned int            sPool;       /*point to local memory pool start address*/
   unsigned int            ePool;       /*indicate the end address of local pool */
   unsigned int            pFree;       /*point to local memory pool free address*/
   unsigned int            nType ;      /*memory pool usage type: circle or single mode DDM_POOL_TYPE*/
   unsigned int            nParent ;    /*memory pool usage type: circle or single mode DDM_POOL_TYPE*/

}DDM_POOL_CTRL;

typedef struct
{
    DDM_BUFF_LIST   dBuff;            /*struct buffer header    */
    unsigned int    slice;            /*phase slice ,time information */
    unsigned int    taskId;           /*phase task id ,which task call this phase record function*/
    unsigned int    value;            /*custom information ,usr-defined value*/
    char *          phName;           /*string contain this phase describ information, */
}DDM_PHASE_DATA;

typedef struct
{
    DDM_BUFF_LIST   dBuff;      /*struct buffer header */
    char*           tName;      /* task name of created task*/
    FUNCPTR         tEntry;		/* 0xb0: tEntry point of task */
    UINT32          tId;        /* task ID of created task*/
    UINT32          tCreater;   /* which task create this task*/
    UINT32          tMs;        /* when this task was created*/
    UINT32          tPrio;
}DDM_TASK_CREATE_INFO;


/*申请SHARE-MEMORY内存,用来存放fastboot各阶段启动时间,DTS2012100800426 by l00225826*/
#define PHASE_BOOT_POOL_ADDR	((unsigned int)SHM_BASE_ADDR + SHM_OFFSET_DDM_LOAD + sizeof(DDM_POOL_CTRL))
#define PHASE_BOOT_POOL_SIZE	(SHM_SIZE_DDM_LOAD - sizeof(DDM_POOL_CTRL))


/*vXWORKS打点计时*/
#define PHASE_BOOT_POOL_SIZE_CCORE                1024  /*EXCH_DDM_SIZE 0xF00*/
static int  score_boot_pool_ccore[PHASE_BOOT_POOL_SIZE_CCORE/sizeof(int)];
static DDM_POOL_CTRL  score_boot_ctrl_ccore;
static unsigned char *  p_score_boot_pool_ccore = (unsigned char *)&score_boot_pool_ccore[0];
static DDM_POOL_CTRL*  p_score_boot_ctrl_ccore = (DDM_POOL_CTRL *)&score_boot_ctrl_ccore;

/*************************************************
 函 数 名   : ddm_phase_buf_get
 功能描述   : get buf from loacal pool or system malloc.
 输入参数   :
 输出参数   :
 返 回 值   : char *
 调用函数   :
 被调函数   :

 修改历史   :
 日    期   : 2011年01月21日
 作    者   : m00176101
 修改内容   : 新生成函数
 功能描述   :
*************************************************/
static char* ddm_phase_buf_get(unsigned int reqSize, DDM_POOL_CTRL* pPoolCtrl)
{
    char *RetBuf = NULL ;
    DDM_POOL_CTRL*  pCtrl = pPoolCtrl;
    unsigned int bufEndAddr = 0;

    bufEndAddr = pCtrl->pFree + reqSize;
    switch (pCtrl->nType)
    {
        case POOL_DIRECT_SINGLE:
        {
            if (bufEndAddr <= pCtrl->ePool)
            {
                RetBuf = (char*)pCtrl->pFree;
                pCtrl->pFree = bufEndAddr;
            }
            else
            {
                /*local pool deplenish, return NULL*/
                RetBuf = NULL;
            }
        }
        break;

        default:
        break;
    }

    return RetBuf;
}

/*******************************************************************
 name       : ddm_phase_score

 input      : DDM_POOL_CTRL* pScoreCtrl: phase handle
              const char* phaseName    : phase name string to store
              int param                : phase param to store

 output      : N/A

 return      :  DDM_OK :     phase store successfully
                DDM_EROR:    phase store failed

 history     :
 date        : 2011年02月21日
 creator     : m00176101
 modified    : new create
 description.   :

**********************************************************************/
static int ddm_phase_score(DDM_POOL_CTRL* pPhaseCtrl ,const char* phaseName,unsigned int param)
{
    unsigned int strSize;
    unsigned int strLength;
    unsigned int reqSize;
    DDM_BUFF_LIST * pBuffNew = NULL ;
    DDM_BUFF_LIST * pBuffLast = NULL;
    DDM_PHASE_DATA* pPhaseData = NULL;

    if(NULL == pPhaseCtrl)
    {
        return DDM_ERROR;
    }
    /*malloc buffer first*/

    strSize = (unsigned int)strlen(phaseName) + 1 ;
    strSize = (strSize <= PHASE_MAX_NAME_SIZE)?strSize:PHASE_MAX_NAME_SIZE;
    strLength = strSize - 1;
    reqSize = sizeof(DDM_PHASE_DATA) + strSize;

    reqSize = ALIGN_SIZE(reqSize,4);

    pBuffNew = (DDM_BUFF_LIST*)ddm_phase_buf_get(reqSize,pPhaseCtrl);
    if(NULL == pBuffNew)
    {
        return DDM_ERROR;
    }

    pBuffNew->bufSize = reqSize;

    /*如果链表为空，初始化当前数据指针*/
    if(NULL == pPhaseCtrl->pData)
    {
        pPhaseCtrl->pData = pBuffNew;
        pBuffNew->p_next = NULL;
    }
    else
    {
        pBuffLast  = pPhaseCtrl->poolTail;
        /*确保指向最后一个*/
        while(NULL != pBuffLast->p_next)
        {
            pBuffLast = pBuffLast->p_next;
        }
        pBuffLast->p_next = pBuffNew;
        pBuffNew->p_next = NULL;
    }

    pPhaseCtrl->poolTail = pBuffNew;

    pPhaseData = (DDM_PHASE_DATA*)pBuffNew;

    /*安全拷贝,使文本长度不超过SCORE_MAX_NAME_SIZE*/
    pPhaseData->phName = (char *)((unsigned int)pPhaseData + sizeof(DDM_PHASE_DATA));
    strncpy(&pPhaseData->phName[0], phaseName, strLength);
    pPhaseData->phName[strLength] = '\0';
	pPhaseData->taskId = (unsigned int)osl_task_self();
	pPhaseData->slice = bsp_get_elapse_ms();
    pPhaseData->value = param;

   return DDM_OK;
}


/*******************************************************************
 name       : ddm_phase_init

 input      : DDM_POOL_CTRL* pScoreCtrl
              void* pScorePool
              unsigned int pSize
              DDM_POOL_TYPE type
              DDM_POOL_PARENT parent

 output      : N/A

 return      :  DDM_OK :     phase store successfully
                DDM_EROR:    phase store failed

 history     :
 date        : 2011年02月21日
 creator     : m00176101
 modified    : new create
 description.   :

**********************************************************************/
static int ddm_phase_init(DDM_POOL_CTRL*   pPhaseCtrl, void* pScorePool,unsigned int pSize ,DDM_POOL_TYPE type ,DDM_POOL_PARENT parent)
{
    pPhaseCtrl->sPool = (unsigned int)pScorePool;
    pPhaseCtrl->ePool = (unsigned int)pScorePool + pSize ;
    pPhaseCtrl->pFree = (unsigned int)pScorePool;
    pPhaseCtrl->pData = NULL;
    pPhaseCtrl->nType = type;
    pPhaseCtrl->nParent = parent;
    pPhaseCtrl->poolTail = NULL;

    return DDM_OK;
}

/*lint -save -e18*/
int ddm_phase_boot_score(const char * phaseName, unsigned int param)
{
    DDM_POOL_CTRL* pCtrl = p_score_boot_ctrl_ccore;

    if((unsigned int)p_score_boot_pool_ccore != pCtrl->sPool)
    {
        if(DDM_OK !=  ddm_phase_init(pCtrl, p_score_boot_pool_ccore, PHASE_BOOT_POOL_SIZE_CCORE, POOL_DIRECT_SINGLE,POOL_PARENT_OS))
        {
            return DDM_ERROR;
        }
    }

    return ddm_phase_score(pCtrl, phaseName, param);
}
/*lint -restore*/

static int ddm_phase_echo(DDM_BUFF_LIST* pBufData, unsigned int localPoolMax)
{
    DDM_PHASE_DATA*    pPhaseDate =  0;
    char * phNameAddr = 0;
    unsigned int lastTick = 0;
    unsigned int step = 0;
    unsigned int totalSize = 0;
    unsigned int localPool = 0;

    if(0 == pBufData)
    {
        goto EXIT;
    }

    pPhaseDate = (DDM_PHASE_DATA*)(pBufData);
    phNameAddr = pPhaseDate->phName;
    lastTick = pPhaseDate->slice;

    while(0 != pBufData)
    {
        pPhaseDate = (DDM_PHASE_DATA*)pBufData;
        phNameAddr = pPhaseDate->phName;
        step++;

	    ddm_print_info(" %3d  0x%08x  %8d  %6d	%6d    %s \n",
			   step,pPhaseDate->slice, pPhaseDate->slice,
			   pPhaseDate->slice - lastTick,
			   pPhaseDate->value, phNameAddr);
        lastTick = pPhaseDate->slice;
        totalSize +=  pBufData->bufSize;
        pBufData = pBufData->p_next;

        localPool = (totalSize<=localPoolMax)?totalSize:localPool;

        if(step%50 == 0)
        {
            osl_task_delay(50);
        }

    }

EXIT:

    return DDM_OK;
}

void ddm_phase_test(void)
{
    if(0 == ddm_phase_boot_score("test", __LINE__))
    {
        ddm_print_info("ok\n");

    }
    else
    {
        ddm_print_info("full\n");
    }

}

void ddm_phase_boot_echo(void)
{
    DDM_POOL_CTRL* pCtrl = NULL;
    DDM_BUFF_LIST* pDumpData = NULL;

    pCtrl = (DDM_POOL_CTRL *)((unsigned int)SHM_BASE_ADDR + SHM_OFFSET_DDM_LOAD);
    pDumpData = pCtrl->pData;


	ddm_print_info("start dump...\r\n");
    ddm_print_info("step     slice     totalMs   curMs    Line    phaseName   \n");
    ddm_print_info("----    -------   ---------  -----   ------   ---------     \n");

    if((unsigned int)PHASE_BOOT_POOL_ADDR == pCtrl->sPool)
    {
        ddm_phase_echo(pDumpData,pCtrl->ePool - pCtrl->sPool);
    }

    pCtrl = p_score_boot_ctrl_ccore;
    pDumpData = pCtrl->pData;

    ddm_phase_echo(pDumpData,pCtrl->ePool - pCtrl->sPool);

	ddm_print_info("end dump...\n");
}
#else

/*lint -save -e18*/
int ddm_phase_boot_score(const char * phaseName, unsigned int param)
{
    return 0;
}
/*lint -restore */

void ddm_phase_boot_echo(void)
{

}
#endif

/* 给其他组件使用 */
int mdrv_sysboot_stampadd(const char * phaseName, unsigned int param)
{
    return ddm_phase_boot_score(phaseName,param);
}
/*end of this file*/
