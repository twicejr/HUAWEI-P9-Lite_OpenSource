/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipbir_visp_def.h
  Version       :
  Author        : Santhosh 71702
  Created       : 2007/11/30
  Last Modified :
  Description   : This file contains IPB IR macros for VISP related APIs.
  Function List :

  History       :
  1.Date        : 10-12-2007
    Author      : Santhosh 71702
    Modification: Created file

******************************************************************************/

#ifndef _IPB_IR_VISP_DEF_H_
#define _IPB_IR_VISP_DEF_H_

/* In VISP IAS product will be disabled */
#define IPB_IR_IAS_IS_PRODUCT_IAS() VOS_ERR


#define IPB_IR_IAS_NOTIFY_ADDR(m_ulOper, m_pstIfNet, m_pstIn6Addr, m_ulPrefixLen) VOS_ERR

#define IPB_IR_IAS_IS_VALID_VLANID_AND_PORTINDEX(m_ulIfIndex, m_usVlanId, m_ulPortIndex) VOS_ERR

#define IPB_IR_IAS_NOTIFY_NB_ENTRY(m_ulOperation, m_pstNBEntry) VOS_ERR

#define IPB_IR_GET_PORTINDEX_BY_PORTNAME(m_szString, m_pulPortIndex) VOS_ERR

#define IPB_IR_GET_PORTNAME_BY_PORTINDEX(m_ulPortIndex, m_szString) VOS_ERR

#define IPB_IR_GET_HELP_PORTNAME(m_szKey, m_pstHelpVec) VOS_ERR

#define IPB_IR_IAS_GET_VLANID_BY_IFINDEX(m_ulIfindex, m_pulVlanID) VOS_ERR

#endif  /* end of _IPB_IR_VISP_DEF_H_ */
