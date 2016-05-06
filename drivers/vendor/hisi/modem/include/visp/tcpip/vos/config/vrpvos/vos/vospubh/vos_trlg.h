
#ifndef _VOS_TRLOG_H_
#define _VOS_TRLOG_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef  __cplusplus
extern "C" {
#endif


#define VOS_TARCE0	0
#define VOS_TRACE1	1
#define VOS_TRACE2	2
#define VOS_TRACE3	3

#define VOS_LOG0	0
#define VOS_LOG1	1
#define VOS_LOG2	2
#define VOS_LOG3	3


#define VOS_Trace  
#define VOS_Trace_Control(ulTraceOnOff)

#define VOS_Log

#define VOS_DBGTRACE


#ifdef  __cplusplus
}
#endif

#endif

