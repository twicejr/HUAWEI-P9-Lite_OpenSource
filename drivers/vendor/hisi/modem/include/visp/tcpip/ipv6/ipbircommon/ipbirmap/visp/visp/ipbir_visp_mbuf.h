/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipbir_visp_mbuf.h
  Version       :
  Author        : Santhosh 71702
  Created       : 2007/11/30
  Last Modified :
  Description   : This file contains IPB IR MBUF macros for VISP related APIs.
  Function List :

  History       :
  1.Date        : 10-12-2007
    Author      : Santhosh 71702
    Modification: Created file

******************************************************************************/

#ifndef _IPB_IR_VISP_MBUF_H_
#define _IPB_IR_VISP_MBUF_H_

/* Dummy macros and needs to be changed for compilation purpose */
#define IPB_IR_MBUF_ASSIGN_SEND_PORT_INDEX(pstMBufM, ulSendPortIndexM) MBUF_SET_PORTIFINDEX((pstMBufM), (ulSendPortIndexM))

#define IPB_IR_MBUF_ASSIGN_VLANID(pstMBufM, usVlanIdM) MBUF_ASSIGN_VLANID((pstMBufM), (usVlanIdM))

#define IPB_IR_MBUF_GET_RECEIVE_PORT_INDEX(pstMBufM) MBUF_GET_PORTIFINDEX((pstMBufM))

#define IPB_IR_MBUF_GET_RECEIVE_VLANID(pstMbufM) MBUF_GET_VLANID((pstMbufM))

#endif  /* end of _IPB_IR_VISP_MBUF_H_ */
