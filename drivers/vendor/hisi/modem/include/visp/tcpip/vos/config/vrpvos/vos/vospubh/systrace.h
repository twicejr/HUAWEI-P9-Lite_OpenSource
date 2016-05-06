/**********************************************************************
 *
 *                          systrace.h
 *                       2003/3/16 by lwj
 *
 **********************************************************************/

#ifndef _SYS_TRACE_H
#define _SYS_TRACE_H

/*#include "vrps/vrp_systrace.h"*/

#ifdef  __cplusplus
extern "C" {
#endif

#define SYSTRACE_ERROR_BUFFER_OVERLAID          1
#define SYSTRACE_ERROR_TRACE_INFO_NOT_RECORDED  2
#define SYSTRACE_ERROR_LONG_TASKNO              3
#define SYSTRACE_ERROR_INTERNAL_ERROR           4


#define SYSTRACE_GLOBAL_INIT_SWITCH           BOOL_TRUE /*Added by rainbow 2003 08 27*/
#define SYSTRACE_TASK_INIT_SWITCH              BOOL_TRUE /*Added by rainbow 2003 08 27*/

/*define help info index for systrace cli*/
enum SYSTRACE_HELP_KEY
{
    SYSTRACE_HLP_SYSTRACE,
    SYSTRACE_HLP_START,
    SYSTRACE_HLP_STOP,
    SYSTRACE_HLP_CLEAR,
    SYSTRACE_HLP_ALL,
    SYSTRACE_HLP_BOARDID,
    SYSTRACE_HLP_TASKNO,
    SYSTRACE_HLP_TASKNAME,
    SYSTRACE_HLP_DUMP,
    SYSTRACE_HLP_LASTNO,
};



ULONG DumpLastSysTraceToClient( ULONG ulExecId, ULONG ulLastNo, ULONG ulTaskNo );

#define SYSTRACE(  ulModuleNo,  ulSrcFileID,  ulPara0,  ulPara1,  ulPara2,  ulPara3 ) 


/* systrace cmo */
#define VOS_TBL_V5_SYSTRACE               0x01
#define CMO_VOS_V5_SYSTRACE_SYSTRACE      CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 1)
#define CMO_VOS_V5_SYSTRACE_START         CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 2)
#define CMO_VOS_V5_SYSTRACE_STOP          CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 3)
#define CMO_VOS_V5_SYSTRACE_CLEAR         CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 4)
#define CMO_VOS_V5_SYSTRACE_ALL           CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 5)
#define CMO_VOS_V5_SYSTRACE_BOARDID       CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 6)
#define CMO_VOS_V5_SYSTRACE_TASKNO        CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 7)
#define CMO_VOS_V5_SYSTRACE_TASKNAME      CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 8) /* Terry Added */
#define CMO_VOS_V5_SYSTRACE_DUMP          CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 9)
#define CMO_VOS_V5_SYSTRACE_LASTNO        CFG_CMO_DEF(MID_SYSTRACE, VOS_TBL_V5_SYSTRACE, 10)




#ifdef  __cplusplus
}
#endif


#endif

