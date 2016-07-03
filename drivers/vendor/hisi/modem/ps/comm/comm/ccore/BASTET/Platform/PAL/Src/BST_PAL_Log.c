

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Log.h"
#include "msp_diag_comm.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_LOG_C
/*lint +e767*/
BST_UINT32 g_BstLogSwitch               = 0;
/******************************************************************************
   2 函数实现
******************************************************************************/
    


BST_VOID BST_PAL_SetLogSwitch(BST_UINT32 ulLevel)
{
    g_BstLogSwitch                      = ulLevel;
}


BST_VOID BST_PAL_LOG(
    const BST_CHAR *pcFileName, 
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId, 
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString)
{
    if( g_BstLogSwitch < ulLevel )
    {
        return;
    }
    
    DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM,ulLevel),ulModuleId,(BST_CHAR *)pcFileName,ulLineNum,"%s",pcString);
}


BST_VOID BST_PAL_LOG1(
    const BST_CHAR *pcFileName, 
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId, 
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString,
    BST_INT32 lPara1)
{
    if( g_BstLogSwitch < ulLevel )
    {
        return;
    }
    
    DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM,ulLevel),ulModuleId,(BST_CHAR *)pcFileName,ulLineNum,"%s,%d",pcString,lPara1);
}


BST_VOID BST_PAL_LOG2(
    const BST_CHAR *pcFileName, 
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId, 
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString,
    BST_INT32 lPara1,
    BST_INT32 lPara2)
{
    if( g_BstLogSwitch < ulLevel )
    {
        return;
    }
    
    DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM,ulLevel),ulModuleId,(BST_CHAR *)pcFileName,ulLineNum,"%s,%d,%d",pcString,lPara1,lPara2);
}


BST_VOID BST_PAL_LOG3(
    const BST_CHAR *pcFileName, 
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId, 
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString,
    BST_INT32 lPara1,
    BST_INT32 lPara2,
    BST_INT32 lPara3)
{
    if( g_BstLogSwitch < ulLevel )
    {
        return;
    }
    
    DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM,ulLevel),ulModuleId,(BST_CHAR *)pcFileName,ulLineNum,"%s,%d,%d,%d",pcString,lPara1,lPara2,lPara3);
}



BST_VOID BST_PAL_LOG4(
    const BST_CHAR *pcFileName, 
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId, 
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString,
    BST_INT32 lPara1,
    BST_INT32 lPara2,
    BST_INT32 lPara3,
    BST_INT32 lPara4)
{
    if( g_BstLogSwitch < ulLevel )
    {
        return;
    }
    
    DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM,ulLevel),ulModuleId,(BST_CHAR *)pcFileName,ulLineNum,"%s,%d,%d,%d,%d",pcString,lPara1,lPara2,lPara3,lPara4);
}





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


