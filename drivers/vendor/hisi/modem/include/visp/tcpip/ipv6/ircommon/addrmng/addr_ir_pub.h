/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_ir_pub.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : Saravanya71677
  Created       : 2007/12/11
  Last Modified :
  Description   : addr_ir_pub.h header file contains all Level 2 Definitions,
                  data structures..
  Function List :
  History       :
  1.Date        : 2007/12/11
    Author      : Saravanya71677
    Modification: Created file

******************************************************************************/

#ifndef __ADDR_IR_PUB_H__
#define __ADDR_IR_PUB_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Move to Level 2 */

#define  IP6_DAD_LINK_BROADCAST 0x10  /* Link type is broadcast, like ethernet*/
#define  IP6_DAD_LINK_P2P       0x20  /* Link type is point to point, like PPP*/
#define  IP6_DAD_LINK_NBMA      0x40  /* Link type is NBMA, like Fr,ATM */
#define  IP6_DAD_LINK_LOOPBACK  0x80  /* Link type is loopback */

/*----------------------------------------------------------------------------*/


/* Move it Level 2 Used by ND */
/*----------------------------------------------------------------------------*/


/* When ND Task invokes ADDR to handle appropriate Event then this Enum is
   used to represent the Event type */
typedef enum tagIp6_ADDR_HostEvents
{
    IP6_NDHOST_ADDR_STATELESS_EV = 0,  /* Event Related to Stateless Addresses */
    IP6_NDHOST_ADDR_STATEFUL_EV,       /* Event Related to Stateful addresses */
    IP6_NDHOST_ADDR_MAX_EV,
    IP6_NDHOST_ADDR_MAX_EV_ULONG = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ADDR_HOSTEVENTS_E;

/* Holds the Event Type and the Information Related to the Event */
typedef struct tagIP6_ADDR_HostEvent
{
    IP6_ADDR_HOSTEVENTS_E enHostEvent;   /* Represents Event Type */
    ULONG                 ulIfIndex;     /* Interface Index */

    /* Holds Address of the Data Structure that has information
       related to the event */
    UINTPTR ulHandle;
}IP6_ADDR_HOSTEVENT_S;

/*----------------------------------------------------------------------------*/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ADDR_IR_PUB_H__ */

