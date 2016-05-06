/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_PAL_Log.c
  版 本 号   : 初稿
  作    者   : z00128442
  生成日期   : 2015年07月14日
  最近修改   :
  功能描述   : 实现HISI平台log匹配
  函数列表   :
  修改历史   :
  1.日    期   : 2015年07月14日
    作    者   : z00128442
    修改内容   : 建立文件

******************************************************************************/

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
    
/*****************************************************************************
 函 数 名  : BST_PAL_SetLogSwitch
 功能描述  : 协议栈log打印
 输入参数  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月14日
      作    者   :  z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_PAL_SetLogSwitch(BST_UINT32 ulLevel)
{
    g_BstLogSwitch                      = ulLevel;
}

/*****************************************************************************
 函 数 名  : BST_PAL_LOG
 功能描述  : 协议栈log打印
 输入参数  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月14日
      作    者   :  z00128442
      修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : BST_PAL_LOG1
 功能描述  : 协议栈log打印
 输入参数  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月14日
      作    者   :  z00128442
      修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : BST_PAL_LOG1
 功能描述  : 协议栈log打印
 输入参数  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月14日
      作    者   :  z00128442
      修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : BST_PAL_LOG1
 功能描述  : 协议栈log打印
 输入参数  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月14日
      作    者   :  z00128442
      修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : BST_PAL_LOG4
 功能描述  : 协议栈log打印
 输入参数  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月14日
      作    者   :  z00128442
      修改内容   : 新生成函数
*****************************************************************************/
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


