

#ifndef __BST_DSPP_REPORT_H__
#define __BST_DSPP_REPORT_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_DSPP_Define.h"
#include "BST_CORE_Regedit.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 类/结构定义
*****************************************************************************/

class BST_DSPP_CReport
{
BST_PUBLIC:
                                        BST_DSPP_CReport( BST_PROCID_T              usProcId,
                                                          BST_TASKID_T              usTaskId );
    BST_ERR_ENUM_UINT8                  Report          ( BST_ERR_ENUM_UINT8        enErrMsg );
    BST_ERR_ENUM_UINT8                  Report          ( BST_CORE_PID_ENUM_UINT16  enParamId,
                                                          BST_UINT16                usCmdLen,
                                                          BST_VOID                 *pRptParam );
    virtual                            ~BST_DSPP_CReport() {};
BST_PROTECTED:
    BST_PROCID_T                        usHostProcId;
    BST_TASKID_T                        usHostTaskId;
};


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
