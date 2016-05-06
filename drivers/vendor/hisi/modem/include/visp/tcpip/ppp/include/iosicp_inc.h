/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              iosicp_inc.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
*   Description: OSICP提供给外部模块的头文件
*                外部模块引入OSICP只需要包含此头文件即可
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/
 
#ifndef _IOSICP_INC_H_
#define _IOSICP_INC_H_

#ifdef __cplusplus
extern "C"{
#endif

/* OSICP Component Core Basic Header Files */
#include "ppp/core_osicp/include/osicp_def.h"
#include "ppp/core_osicp/include/osicp_type.h"
#include "ppp/core_osicp/include/osicp_var.h"
#include "ppp/core_osicp/include/osicp_funp.h"
#include "ppp/core_osicp/include/osicp_func.h"

#include "ppp/core_osicp/include/iosicp.h"

#ifdef __cplusplus
}
#endif

#endif
