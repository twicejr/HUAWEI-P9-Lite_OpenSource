/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DSPP_Report.cpp
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : DSPP 协议由Slave主动发起上报的接口
  函数列表   :

  修改历史   :
1.日    期   : 2014年04月16日
  作    者   : d00173029
  修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_DSPP_Report.h"
#include "BST_DSPP_AppLayer.h"
#include "BST_DBG_MemLeak.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_REPORT_CPP
/*lint +e767*/
/*****************************************************************************
  2 函数实现
******************************************************************************/

/*****************************************************************************
函 数 名  : BST_DSPP_CReport
功能描述  : 类BST_DSPP_CReport的构造函数
输入参数  : BST_PROCID_T usProcId
            BST_TASKID_T usTaskId
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史  :
1.日   期 : 2014年04月16日
  作   者 : d00173029
  修改内容: 创建文件
*****************************************************************************/
BST_DSPP_CReport::BST_DSPP_CReport ( BST_PROCID_T usProcId,
                                     BST_TASKID_T usTaskId )
{
    usHostProcId                        = usProcId;
    usHostTaskId                        = usTaskId;
}

/*****************************************************************************
函 数 名  : Report
功能描述  : 发送报告
输入参数  : BST_ERR_ENUM_UINT8 enErrMsg
输出参数  :
返 回 值  : BST_ERR_ENUM_UINT8
调用函数  :
被调函数  :

修改历史  :
1.日   期 : 2014年04月16日
  作   者 : d00173029
  修改内容: 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CReport::Report ( BST_ERR_ENUM_UINT8 enErrMsg )
{
    BST_DSPP_CAppUlVa                  *pcDsppApUlVa;

    pcDsppApUlVa                       = BST_DSPP_CAppUlVa::GetInstance ();
    if ( BST_NULL_PTR == pcDsppApUlVa )
    {
        return BST_ERR_INVALID_PTR;
    }
    return ( pcDsppApUlVa->Report ( usHostProcId, usHostTaskId, enErrMsg ) );
}
/*****************************************************************************
函 数 名  : Report
功能描述  : 发送报告
输入参数  : BST_CORE_PID_ENUM_UINT16  enParamId
            BST_UINT16                usCmdLen
            BST_VOID                 *pRptParam
输出参数  :
返 回 值  : BST_ERR_ENUM_UINT8
调用函数  :
被调函数  :

修改历史  :
1.日   期 : 2014年04月16日
  作   者 : d00173029
  修改内容: 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CReport::Report ( BST_CORE_PID_ENUM_UINT16  enParamId,
                                               BST_UINT16                usCmdLen,
                                               BST_VOID                 *pRptParam )
{
    BST_DSPP_CAppUlVa                  *pcDsppApUlVa;

    pcDsppApUlVa                       = BST_DSPP_CAppUlVa::GetInstance ();
    if ( BST_NULL_PTR == pcDsppApUlVa )
    {
        return BST_ERR_INVALID_PTR;
    }
    return ( pcDsppApUlVa->Report ( usHostProcId, usHostTaskId,
                                  usCmdLen, enParamId, (BST_UINT8 *)pRptParam ) );
}

