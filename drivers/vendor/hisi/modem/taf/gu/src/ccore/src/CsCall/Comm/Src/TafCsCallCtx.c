

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafCsCallCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID TAF_CSCALL_InitCtx(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_InitCtx();
#endif

}

/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */






