/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cpu_view_adapter.h
  版 本 号   : 初稿
  作    者   : g00178567
  生成日期   : 2013年10月30日
  最近修改   :
  功能描述   : 操作系统适配
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月30日
    作    者   : g00178567
    修改内容   : 创建文件

******************************************************************************/

#ifndef  _CPU_VIEW_INTERFACE_H
#define  _CPU_VIEW_INTERFACE_H


/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "cpu_view_adapter.h"

/******************************************************************************
   2 函数声明
******************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/
enum CPU_VIEW_TYPE_ENUM
{
    CPU_VIEW_TYPE_TASK      = 0,
    CPU_VIEW_TYPE_INT       = 1,
    CPU_VIEW_TYPE_POINT     = 2,
    CPU_VIEW_TYPE_SUB_INT   = 3,
    CPU_VIEW_TYPE_FUNC      = 4,

    CPU_VIEW_TYPE_BUTT
};
typedef VOS_UINT32 CPU_VIEW_TYPE_ENUM_UINT32;

enum CPU_VIEW_LEV_ENUM
{
    CPU_VIEW_LEV_EXIT           = 0,                        /* 退出记录 */
    CPU_VIEW_LEV_ENTRY          = 1,                        /* 进入记录 */

    CPU_VIEW_LEV_BUTT
};
typedef VOS_UINT32 CPU_VIEW_LEV_ENUM_UINT32;

enum CPU_VIEW_RECORD_MODE_ENUM
{
    CPU_VIEW_RECORD_MODE_CYCLE_NO           = 0,            /* 非循环模式 */
    CPU_VIEW_RECORD_MODE_CYCLE_YES          = 1,            /* 循环模式 */

    CPU_VIEW_RECORD_MODE_BUTT
};
typedef VOS_UINT32 CPU_VIEW_RECORD_MODE_ENUM_UINT32;


enum CPU_VIEW_MEMORY_MODE_ENUM
{
    CPU_VIEW_MEMORY_MODE_DYNAMIC            = 0,            /* 动态申请内存模式 */
    CPU_VIEW_MEMORY_MODE_STATIC             = 1,            /* 静态分配内存模式 */

    CPU_VIEW_MEMORY_MODE_BUTT
};
typedef VOS_UINT32 CPU_VIEW_MEMORY_MODE_ENUM_UINT32;

enum CPU_VIEW_DUMP_GEN_MODE_ENUM
{
    CPU_VIEW_DUMP_GEN_MODE_FLASH            = 0,            /* CPUVIEW记录dump文件导出到flash中模式 */
    CPU_VIEW_DUMP_GEN_MODE_NETCARD          = 1,            /* CPUVIEW记录dump文件导出到虚拟网卡中模式 */

    CPU_VIEW_DUMP_GEN_MODE_BUTT
};
typedef VOS_UINT32 CPU_VIEW_DUMP_GEN_MODE_ENUM_UINT32;

enum CPU_VIEW_RECORD_OVERTURN_ENUM
{
    CPU_VIEW_RECORD_OVERTURN_NO             = 0,            /* CPUVIEW记录没有翻转 */
    CPU_VIEW_RECORD_OVERTURN_YES            = 1,            /* CPUVIEW记录发生翻转 */

    CPU_VIEW_RECORD_OVERTURN_BUTT
};
typedef VOS_UINT32 CPU_VIEW_RECORD_OVERTURN_ENUM_UINT32;

#define CPU_VIEW_GET_TICK()                         VOS_GetTick()
#define CPU_MOD_GET(x, y)                           ((x) % (y))
#define CPU_MOD_ADD(x, y, z)                        (((x) + (y)) % (z))
#define CPU_MOD_SUB(x, y, z)                        ((((x) + (z)) - (y)) % (z))
#define CPU_MIN(x, y)                               (((x)<(y))?(x):(y))
#define CPU_MAX(x, y)                               (((x)>(y))?(x):(y))

/*max value of timer's clock count */
#define TIMER_MAX_VALUE                             (0xFFFFFFFF)

/*max task number */
#define CPU_VIEW_MAX_TASK_NUMBER                    (128)

/*max task name lenth */
#define CPU_VIEW_TASK_NAME_LEN                      (16)

#define CPU_VIEW_TASK_TCB_SIZE                      (sizeof(CPUVIEW_TCB))
#define CPU_VIEW_TASK_STACK_MAX_CARE_SIZE           (4096)
#define CPU_VIEW_TASK_STACK_SIZE                    (CPU_VIEW_TASK_STACK_MAX_CARE_SIZE)     /* 32*1024 */

/* 不分配固定内存给CPU_VIEW使用，故此处需要出临时版本时修改，
   划分一块单板复位不重新初始化的内存临时使用 */
#define CPU_VIEW_STATIC_MEM_ADDRESS_START           (0x0)
#define CPU_VIEW_STATIC_MEM_ADDRESS_END             (0x0)

/* 若定义PS_TASK_CHECK，则需更新该值 */
#define  PS_CODE_ADDRESS_START                      (0x60000000)
#define  PS_CODE_ADDRESS_END                        (0x70000000)

#define CPU_VIEW_RECORD_DEFAULT_NUM                 (20 * 1024)
#define CPU_VIEW_RECORD_MAX_NUM                     (20 * 1024)

#define CPU_VIEW_INSIDE(ulAddress, ulStart, ulEnd)  (((ulAddress) >= (ulStart)) && ((ulAddress) <= (ulEnd)))
#define CPU_VIEW_NO                                 (0)
#define CPU_VIEW_YES                                (1)

typedef struct
{
    VOS_UINT32      ulId;       /*任务Id，点灯的INDEX，中断的中断号, 函数地址 */
    VOS_UINT8       ucType;
    VOS_UINT8       ucLev;
    VOS_UINT8       aucRsv[2];
    VOS_UINT32      ulSlice;
    VOS_UINT32      ulTick;
    VOS_UINT32      ulPC;
    VOS_UINT32      ulPara1;
} CPU_VIEW_STRU;

/*lint -e959 -e958*/
typedef struct
{
    CPUVIEW_TCB    *pTcb;
    CPUVIEW_TCB     stTcb;
    VOS_UINT32      ulTaskIndex;
    VOS_UINT32      ulTcbStart;
    VOS_UINT32      ulTcbEnd;
    VOS_UINT32      ulStackStart;
    VOS_UINT32      ulStackEnd;
    VOS_UINT32      ulStackCareStart;
    VOS_UINT32      ulStackCareSize;
    VOS_UINT8       aucStack[CPU_VIEW_TASK_STACK_SIZE];
} CPU_TASK_INFO_STRU;

typedef struct
{
    CPUVIEW_TCB    *pTcb;
    char            aucTaskName[CPU_VIEW_TASK_NAME_LEN];
} CPU_TASK_NAME_STRU;

typedef struct
{
    VOS_UINT32          ulCpuViewMode;      /* 记录模式，0:非循环模式 1:循环模式 */
    VOS_UINT32          ulCpuViewTraceCnt;  /* 需要记录的CpuView记录数目之合 */

    VOS_UINT32          ulCpuViewCnt;       /* 当前CpuView记录的指针 */
    VOS_UINT32          ulCpuViewOC;        /* 指针是否已经翻转 */

    VOS_UINT32          ulPointWatch;
    VOS_UINT32          ulTaskWatch;
    VOS_UINT32          ulFuncWatch;

    VOS_UINT32          ulLastTaskId;
    VOS_UINT32          ulDebugTaskId;      /* 需要观测的任务ID，RR_FID,TaskId,stack begin,tcb address */

    VOS_UINT32          ulTaskNumber;       /* 当前系统的任务个数 */
    CPU_TASK_NAME_STRU  astCpuTaskName[CPU_VIEW_MAX_TASK_NUMBER];   /* 最多记录50个任务 */

    CPU_VIEW_STRU      *pstCpuView;         /* CpuView记录表 */
} CPU_VIEW_CTRL_STRU;

/******************************************************************************
   4 全局变量定义
******************************************************************************/
extern CPU_VIEW_CTRL_STRU      *g_pstCpuViewCtrl;
#define g_ulCpuViewMode         (g_pstCpuViewCtrl->ulCpuViewMode)
#define g_ulCpuViewTraceCnt     (g_pstCpuViewCtrl->ulCpuViewTraceCnt)
#define g_ulCpuViewCnt          (g_pstCpuViewCtrl->ulCpuViewCnt)
#define g_ulCpuViewOC           (g_pstCpuViewCtrl->ulCpuViewOC)
#define g_ulTaskNumber          (g_pstCpuViewCtrl->ulTaskNumber)
#define g_pstCpuView            (g_pstCpuViewCtrl->pstCpuView)
#define g_astCpuTaskName        (g_pstCpuViewCtrl->astCpuTaskName)

extern VOS_UINT32               g_ulCpuViewInitFlag;
extern VOS_UINT32               g_ulCpuViewStartFlag;
extern VOS_UINT32               g_ulPointWatch;
extern VOS_UINT32               g_ulTaskWatch;
extern VOS_UINT32               g_ulFuncWatch;

/******************************************************************************
   5 函数申明
******************************************************************************/
VOS_VOID CpuView_Init(VOS_UINT32 ulRecordMode, VOS_UINT32 ulRecordCnt);
VOS_VOID CpuView_Close(VOS_VOID);
VOS_VOID CpuView_Start(VOS_UINT32 ulMode);
VOS_VOID CpuView_End(VOS_VOID);
VOS_VOID CpuView_Restart(VOS_VOID);
VOS_VOID CpuView_Dump(VOS_UINT32 ulDumpMode);
VOS_VOID CpuView_SetPoint(VOS_UINT32 ulId, VOS_UINT8 ucLev, VOS_UINT32 ulPara0, VOS_UINT32 ulPara1);


#endif  /* _CPU_VIEW_ADAPTER_H */


