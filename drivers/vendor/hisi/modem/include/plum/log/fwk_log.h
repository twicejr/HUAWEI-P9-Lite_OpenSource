/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 *
 * @author  F73150
 * @version
 * @date    2013/11/12 12:46(+0100)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_FWK_LOG_H
#define INCLUSION_GUARD_FWK_LOG_H
#include "stdint.h"

#include "phytoolinterface.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
#ifdef THIS_FILE_ID
#undef THIS_FILE_ID
#endif
#define THIS_FILE_ID                    __THIS_FILE_ID__

#define WPHY_SRAM_400K
typedef struct print_sig
{
    VOS_MSG_HEADER
    UPHY_TOOL_MNTN_RPT_LEVEL_ENUM_UINT16    enLevel;
    uint32_t                              uhwFileNo;
    uint32_t                              uhwLineNo;
    uint32_t                              uhwVarCnt;
    uint32_t                              uwValue[5];
}print_sig_t;

#ifndef CPROC_NO_USE_FILE_ID
#define FILE_IDENTIFYER __THIS_FILE_ID__
#else
#define FILE_IDENTIFYER (uint32_t)__FILE__
#endif

/**
 * Logs that an unexpected message was received
 * @param[in] pMsg   Pointer to reported message
 */
#define CPROC_BAD_MSG( pMsg )                   \
    CPROC_BadMsg( pMsg , FILE_IDENTIFYER, __LINE__)



/**
 * Logs that bad parameters was received
 *
 * @param[in] pMsg           Meessage that contains the bad parameter.
 * @param[in] paramAddress   Pointer to the bad parameter value.
 * @param[in] uwParamValue   Value to be reported
 */
#define CPROC_BAD_MSG_PARAM( pMsg,paramAddress,uwParamValue )             \
    CPROC_BadMsgParam( pMsg, paramAddress, uwParamValue, FILE_IDENTIFYER, __LINE__ )


#ifndef CPROC_NOLOGGING



extern VOS_MSG_HOOK_FUNC    vos_MsgHook;
extern VOS_UINT32           g_CPROC_1x_CurrentPID; /* From cproc_entry.c since we
                                                    * need to know the current PID
                                                    */

#define CPROC_1X_LogError()                             \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_ERROR,    \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          0,                            \
                          0,                            \
                          0,                            \
                          0,                            \
                          0,                            \
                          0)


#define CPROC_1X_LogError1(uwError1)                    \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_ERROR,    \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          1,                            \
                          (uint32_t)(uwError1),       \
                          0,                            \
                          0,                            \
                          0,                            \
                          0)


#define CPROC_1X_LogError2(uwError1,uwError2)           \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_ERROR,    \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          2,                            \
                          (uint32_t)(uwError1),       \
                          (uint32_t)(uwError2),       \
                          0,                            \
                          0,                            \
                          0)

#define CPROC_1X_LogError3(uwError1,uwError2,uwError3)  \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_ERROR,    \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          3,                            \
                          (uint32_t)(uwError1),       \
                          (uint32_t)(uwError2),       \
                          (uint32_t)(uwError3),       \
                          0,                            \
                          0)


#define CPROC_1X_LogError4(uwError1,uwError2,uwError3,uwError4) \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_ERROR,            \
                          FILE_IDENTIFYER,                      \
                          __LINE__,                             \
                          4,                                    \
                          (uint32_t)(uwError1),               \
                          (uint32_t)(uwError2),               \
                          (uint32_t)(uwError3),               \
                          (uint32_t)(uwError4),               \
                          0)

#define CPROC_1X_LogError5(uwError1,uwError2,uwError3,uwError4,uwError5) \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_ERROR,                    \
                          FILE_IDENTIFYER,                              \
                          __LINE__,                                     \
                          5,                                            \
                          (uint32_t)(uwError1),                       \
                          (uint32_t)(uwError2),                       \
                          (uint32_t)(uwError3),                       \
                          (uint32_t)(uwError4),                       \
                          (uint32_t)(uwError5))




#define CPROC_1X_LogWarning()                           \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_WARNING,  \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          0,                            \
                          0,                            \
                          0,                            \
                          0,                            \
                          0,                            \
                          0)

#define CPROC_1X_LogWarning1(uwWarning1)                \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_WARNING,  \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          1,                            \
                          (uint32_t)(uwWarning1),     \
                          0,                            \
                          0,                            \
                          0,                            \
                          0)

#define CPROC_1X_LogWarning2(uwWarning1, uwWarning2)    \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_WARNING,  \
                          FILE_IDENTIFYER,              \
                          __LINE__,                     \
                          2,                            \
                          (uint32_t)(uwWarning1),     \
                          (uint32_t)(uwWarning2),     \
                          0,                            \
                          0,                            \
                          0)

#define CPROC_1X_LogWarning3(uwWarning1, uwWarning2, uwWarning3)    \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_WARNING,              \
                          FILE_IDENTIFYER,                          \
                          __LINE__,                                 \
                          3,                                        \
                          (uint32_t)(uwWarning1),                 \
                          (uint32_t)(uwWarning2),                 \
                          (uint32_t)(uwWarning3),                 \
                          0,                                        \
                          0)

#define CPROC_1X_LogWarning4(uwWarning1, uwWarning2, uwWarning3, uwWarning4) \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_WARNING,                  \
                          FILE_IDENTIFYER,                              \
                          __LINE__,                                     \
                          4,                                            \
                          (uint32_t)(uwWarning1),                     \
                          (uint32_t)(uwWarning2),                     \
                          (uint32_t)(uwWarning3),                     \
                          (uint32_t)(uwWarning4),                     \
                          0)

#define CPROC_1X_LogWarning5(uwWarning1, uwWarning2, uwWarning3, uwWarning4, uwWarning5) \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_WARNING,                  \
                          FILE_IDENTIFYER,                              \
                          __LINE__,                                     \
                          5,                                            \
                          (uint32_t)(uwWarning1),                     \
                          (uint32_t)(uwWarning2),                     \
                          (uint32_t)(uwWarning3),                     \
                          (uint32_t)(uwWarning4),                     \
                          (uint32_t)(uwWarning5))

#define CPROC_1X_LogInfo()                          \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_INFO, \
                          FILE_IDENTIFYER,          \
                          __LINE__,                 \
                          0,                        \
                          0,                        \
                          0,                        \
                          0,                        \
                          0,                        \
                          0)

#define CPROC_1X_LogInfo1(uwInfo1)                  \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_INFO, \
                          FILE_IDENTIFYER,          \
                          __LINE__,                 \
                          1,                        \
                          (uint32_t)(uwInfo1),    \
                          0,                        \
                          0,                        \
                          0,                        \
                          0)

#define CPROC_1X_LogInfo2(uwInfo1,uwInfo2)          \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_INFO, \
                          FILE_IDENTIFYER,          \
                          __LINE__,                 \
                          2,                        \
                          (uint32_t)(uwInfo1),    \
                          (uint32_t)(uwInfo2),    \
                          0,                        \
                          0,                        \
                          0)

#define CPROC_1X_LogInfo3(uwInfo1,uwInfo2,uwInfo3)  \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_INFO, \
                          FILE_IDENTIFYER,          \
                          __LINE__,                 \
                          3,                        \
                          (uint32_t)(uwInfo1),    \
                          (uint32_t)(uwInfo2),    \
                          (uint32_t)(uwInfo3),    \
                          0,                        \
                          0)

#define CPROC_1X_LogInfo4(uwInfo1,uwInfo2,uwInfo3,uwInfo4)  \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_INFO,         \
                          FILE_IDENTIFYER,                  \
                          __LINE__,                         \
                          4,                                \
                          (uint32_t)(uwInfo1),            \
                          (uint32_t)(uwInfo2),            \
                          (uint32_t)(uwInfo3),            \
                          (uint32_t)(uwInfo4),            \
                          0)

#define CPROC_1X_LogInfo5(uwInfo1,uwInfo2,uwInfo3,uwInfo4,uwInfo5)  \
    CPROC_1X_LogFunction( UPHY_MNTN_RPT_LEVEL_INFO,                 \
                          FILE_IDENTIFYER,                          \
                          __LINE__,                                 \
                          5,                                        \
                          (uint32_t)(uwInfo1),                    \
                          (uint32_t)(uwInfo2),                    \
                          (uint32_t)(uwInfo3),                    \
                          (uint32_t)(uwInfo4),                    \
                          (uint32_t)(uwInfo5))

#else

/* #include "stdio.h" */
#define CPROC_1X_LogError()                             \
    /* printf("Error print in:\n%s:%d:\n"__FILE__,__LINE__) */
#define CPROC_1X_LogError1(dd)                                  \
    /* printf("Error print in:\n %s:%d:\n%s\n"__FILE__,__LINE__, #dd) */
#define CPROC_1X_LogError2(dd,ee)                                       \
    /* printf("Error print in:\n %s:%d:\n%s  0x%x\n "__FILE__,__LINE__, #dd, ee) */
#define CPROC_1X_LogError3(dd,ee,ff)                                       \
    /* printf("Error print in:\n %s:%d:\n%s  0x%x  0x%x\n "__FILE__,__LINE__, #dd, ee, ff) */
#define CPROC_1X_LogError4(dd,ee,ff,gg)                                       \
    /* printf("Error print in:\n %s:%d:\n%s  0x%x  0x%x  0x%x\n "__FILE__,__LINE__, #dd, ee, ff, gg) */
#define CPROC_1X_LogError5(dd,ee,ff,gg,hh)                                       \
    /* printf("Error print in:\n %s:%d:\n%s  0x%x  0x%x  0x%x  0x%x\n "__FILE__,__LINE__, #dd, ee, ff, gg, hh) */

#define CPROC_1X_LogWarning()
#define CPROC_1X_LogWarning1(a)
#define CPROC_1X_LogWarning2(a,b)
#define CPROC_1X_LogWarning3(a,b,c)
#define CPROC_1X_LogWarning4(a,b,c,d)
#define CPROC_1X_LogWarning5(a,b,c,d,e)

#define CPROC_1X_LogInfo()                             \
    /* printf("Info print in:\n%s:%d:\n"__FILE__,__LINE__) */
#define CPROC_1X_LogInfo1(dd)                                  \
    /* printf("Info print in:\n %s:%d:\n%s\n"__FILE__,__LINE__, #dd) */
#define CPROC_1X_LogInfo2(dd,ee)                                       \
    /* printf("Info print in:\n %s:%d:\n%s  0x%x\n "__FILE__,__LINE__, #dd, ee) */
#define CPROC_1X_LogInfo3(dd,ee,ff)                                       \
    /* printf("Info print in:\n %s:%d:\n%s  0x%x  0x%x\n "__FILE__,__LINE__, #dd, ee, ff) */
#define CPROC_1X_LogInfo4(dd,ee,ff,gg)                                       \
    /* printf("Info print in:\n %s:%d:\n%s  0x%x  0x%x  0x%x\n "__FILE__,__LINE__, #dd, ee, ff, gg) */
#define CPROC_1X_LogInfo5(dd,ee,ff,gg,hh)                                       \
    /* printf("Info print in:\n %s:%d:\n%s  0x%x  0x%x  0x%x 0x%x\n "__FILE__,__LINE__, #dd, ee, ff, gg, hh) */
#endif
/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/

/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/

/*****************************************************************************
  5 Message declarations
*****************************************************************************/

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/

/*****************************************************************************
  7 UNION declarations
*****************************************************************************/

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/

/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/**
 * Function to make sure that logging are registerd on the right process.
 *
 * @param[in] pid Acive PID.
 */
VOS_VOID FWK_LOG_SetActivPid(VOS_UINT32 pid);

/**
 * Function to be called by the CPROC_BAD_MSG_PARAM macro
 *
 * @note Don't call this function direct, use the macro CPROC_BAD_MSG_PARAM.
 * @ref CPROC_BAD_MSG_PARAM
 * @param[in] pMsg       Meessage that contains the bad parameter.
 * @param[in] pParam     Pointer to the bad parameter value.
 * @param[in] uwValue    Value to be reported
 * @param[in] fileId     File Id
 * @param[in] line       Line number
 *
 * @return Void.
 */
VOS_VOID CPROC_BadMsgParam( const VOS_VOID* pMsg,
                            const VOS_VOID* pParam,
                                  VOS_UINT32 uwValue,
                                  VOS_UINT32 fileId,
                                  VOS_UINT32 line);


/**
 * Function to be called by the CPROC_BAD_MSG macro
 * @note Don't call this function direct, use the macro CPROC_BAD_MSG.
 * @ref CPROC_BAD_MSG
 * @param[in] pMsg   Pointer to reported message
 * @param[in] fileId     File Id
 * @param[in] line       Line number
 *
 * @return Void.
 */
VOS_VOID CPROC_BadMsg( const VOS_VOID* pMsg, VOS_UINT32 fileId, VOS_UINT32 line);

VOS_VOID CPROC_1X_LogFunction(UPHY_TOOL_MNTN_RPT_LEVEL_ENUM_UINT16 enLevel,
                              VOS_UINT32 uhwFileNo,
                              VOS_UINT32 uhwLineNo,
                              VOS_UINT32 uhwVarCnt,
                              VOS_UINT32 uwValue0,
                              VOS_UINT32 uwValue1,
                              VOS_UINT32 uwValue2,
                              VOS_UINT32 uwValue3,
                              VOS_UINT32 uwValue4);


void PLUM_LogSignal(void *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_FWK_LOG_H */
