


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafXCallProcUsim.h"
#include "TafXCallCtx.h"
#include "Taf_Common.h"
#include "NasUsimmApi.h"
#include "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_USIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID  TAF_XCALL_SndCardReadFileReq(
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId,
    VOS_UINT8                           ucRecordNum
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      (VOS_UINT16)enFileId,
                                      ucRecordNum);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* 打印卡文件读取失败 */
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_SndCardReadFileReq: Get File Fail ", ulRet);
        return;
    }

    return;
}



#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




