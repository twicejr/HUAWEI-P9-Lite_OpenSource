/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_om_log.c
*
*   作    者 :  h00135900
*
*   描    述 :  打印输出处理头文件
*
*   修改记录 :  2013年03月04日  v1.00  h00135900  创建
*************************************************************************/

#ifndef __BSP_OM_LOG_H__
#define __BSP_OM_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "drv_comm.h"
#include "bsp_om.h"
#include "bsp_om_api.h"



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  BSP_PRINT_BUF_LEN  256
#define  BSP_DIAG_IND_DATA_MAX_LEN         (4096)

#define VXWORKS_INT_LOCK_FLAG   ( 0xc0)
#define BSP_TRACE_BUF_LEN_MAX  (255)
#define BSP_LOG_BUF_LEN         (8192)
/*****************************************************************************
  2 枚举定义
*****************************************************************************/



/*****************************************************************************
  2 结构体
*****************************************************************************/
/*lint -save -e43*/
typedef struct
{
    u32     mod_id;     /* 打印信息所在的模块ID*/
    u32     level;      /* 输出级别*/
    u32     log_sn;     /* IND标号*/
    char     text[0];    /* 所有打印文本内容，可能包括文件和行号,以'\0'结尾 */
} bsp_trace_txt_s;
/*lint -restore +e43*/

typedef struct
{
    bsp_socp_head_s      socp_header;
    bsp_om_head_s        om_header;
    bsp_trace_txt_s  print_stu;
} bsp_trace_s;

typedef struct
{
    u32                     addr;
    u16                     is_edle;
    u16                     is_valible;
}bsp_log_node_ctrl_s;




typedef struct
{
    int                     buf_offset;
    char*                   write_ptr;
}bsp_log_buf_ctrl_s;

/*****************************************************************************
  5 错误码定义
*****************************************************************************/
#define BSP_ERR_LOG_BASE                (int)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_LOG, 0)))
#define BSP_ERR_LOG_INVALID_MODULE      (BSP_ERR_LOG_BASE + 0x1)
#define BSP_ERR_LOG_INVALID_LEVEL       (BSP_ERR_LOG_BASE + 0x2)
#define BSP_ERR_LOG_INVALID_PARAM       (BSP_ERR_LOG_BASE + 0x3)
#define BSP_ERR_LOG_NO_BUF              (BSP_ERR_LOG_BASE + 0x4)
#define BSP_ERR_LOG_SOCP_ERR            (BSP_ERR_LOG_BASE + 0x5)

#ifdef __cplusplus
}
#endif


#endif

