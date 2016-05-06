/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl_sh.h
*
*  Project Code: VISPV1R6C02
*   Module Name:   
*  Date Created: 2007-07-31
*        Author: luogaowei61496
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   luogaowei61496          Create
*  2008-09-10   liangjicheng          V1R7C02 同步V1R7C01  
    1 函数增加参数(2)
        extern ULONG ACL_ClassifyInMBufByNumber(MBUF_S *pMBuf, ULONG ulGroupNum, ULONG ulIgnore);
        extern ULONG ACL_GetFlowOfFirstRule(ULONG ulListNumber, ACL_Item *pstFlow, ULONG *pulDscp);
        
*
*******************************************************************************/

#ifndef _ACL_SH_H_
#define _ACL_SH_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "acl/shell/include/fw_acl_sh.h"

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */
