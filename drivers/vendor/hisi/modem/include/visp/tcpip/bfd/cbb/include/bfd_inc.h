/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_inc.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2007-04-04
*        Author: QinYun
*   Description: BFD(Shell)模块的C文件包含的基本头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2007-04-04    QinYun           Create
*
*******************************************************************************/
#ifndef _BFD_INC_H_
#define _BFD_INC_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "tcpip/public/arith_cbb/include/avltree.h"

/*Modefy by Q62011 for bfd ext start*/
#include "bfd/cbb/include/bfd_def.h"
#include "bfd/include/bfd_api.h"
/*Modefy by Q62011 for bfd ext end*/
#include "bfd/shell/include/bfd_ppi.h"
#include "bfd/cbb/include/bfd_type.h"
#include "bfd/cbb/include/bfd_scm.h"
#include "bfd/cbb/include/bfd_dd.h"
#include "bfd/cbb/include/bfd_main.h"
#include "bfd/cbb/include/bfd_fsm.h"
#include "bfd/cbb/include/bfd_var.h"
#include "bfd/shell/include/bfd_sh.h"
#include "bfd/shell/include/bfd6_sh.h"
#include "bfd/shell/include/bfd_ha.h"
#include "bfd/cbb/include/bfd_gr.h"
#include "bfd/cbb/include/bfd_nsr.h"

#ifdef __cplusplus
}
#endif

#endif/* end of _BFD_INC_H_*/

