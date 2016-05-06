

#ifndef _VOS_KER_H_
#define _VOS_KER_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif


#ifdef  __cplusplus
extern "C" {
#endif


#define VOS_Assert(lExpression) \
    VOS_Assert_X(lExpression,__FILE__,__LINE__)

VOID VOS_Assert_X(LONG lExpression,CHAR *pcFileName,ULONG ulLine);



#if (VRP_VERSION_RELEASE == VRP_YES)
ULONG VOS_GetNodeID(VOID);
ULONG VOS_Start(VOID);

ULONG VOS_RegOutString(ULONG (*pfOutString)(CHAR *pStr));
ULONG VOS_RegGetChar(SHORT (*pfGetChar)(VOID));
ULONG VOS_RegisterHousekeeper(CHAR chMainTaskName[4],ULONG ulNotifyEvents);

VOID VOS_ExceptionNotify(ULONG ulExceptionType);
USHORT VOS_GetCPUSpare(VOID); 

#else

#define VOS_GetNodeID()  \
    VOS_GetNodeID_X(__FILE__,__LINE__)

ULONG VOS_GetNodeID_X(CHAR *pcFileName,ULONG ulLine);
ULONG VOS_Start(VOID);

ULONG VOS_RegOutString(ULONG (*pfOutString)(CHAR *pStr));
ULONG VOS_RegGetChar(SHORT (*pfGetChar)(VOID));
ULONG VOS_RegisterHousekeeper(CHAR chMainTaskName[4],ULONG ulNotifyEvents);

VOID VOS_ExceptionNotify(ULONG ulExceptionType);

#endif
#define VOS_DBGASSERT(lExpression) \
{\
    LONG lExpressionTemp = (LONG)(lExpression); \
    if (!(lExpressionTemp))\
    {\
        VOS_Assert(lExpressionTemp);\
    }\
}    

/*该宏的含义: 如果条件lExpression为真, 则输出调试信息pMessage*/
#define TEST_DBGASSERT(lExpression, pMessage)\
{\
    if (lExpression)\
    {\
        vos_printf("%s", pMessage);\
    }\
}    


/*added by anhongjie for unifying output of allocating memory failure*/
#define MEM_ALLOC_FAIL_STR "Failed to allocate memory"
/*end 2003-03-14*/

#ifdef  __cplusplus
}
#endif

#endif


