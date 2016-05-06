/******************************************************************************
*
*             Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : IPBIRV100R003.IPv6.E001
*    File Name      : Nd_nb.h
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef        _ND_NB_H_
#define        _ND_NB_H_

#ifdef        __cplusplus
extern "C"{
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/* Macros to set and reset the DAD flag */
#define NS_NOTFORDAD                0
#define NS_FORDAD                   1

#define NS_MAX_DEFAULT_INTERVAL     (10*60*1000)  /*10 min*/

/* Macros to set and reset the ND option flag */
#define ND_HAVENOTOPTION            0
#define ND_HAVEOPTION               1

/* Maximum DAD Limit on DAD Timeout */
#define MAXDADWALKNUM               100

/* Macros used to check ND Look up is required or not */
#define ND_LOOKUP_REQUIRED          8
#define ND_LOOKUP_NOTREQUIRED       9


/* RFC 2461 :=> NA message format

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |     Type      |     Code      |          Checksum             |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |R|S|O|                     Reserved                            |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      +                                                               +
      |                                                               |
      +                       Target Address                          +
      |                                                               |
      +                                                               +
      |                                                               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |   Options ...
      +-+-+-+-+-+-+-+-+-+-+-+-
*/

/* NA message flags */
#if (VRP_BIG_ENDIAN == VRP_YES)

#define ND_NA_FLAG_ROUTER          0x80000000
#define ND_NA_FLAG_SOLICITED       0x40000000
#define ND_NA_FLAG_OVERRIDE        0x20000000

#else

#define ND_NA_FLAG_ROUTER          0x80
#define ND_NA_FLAG_SOLICITED       0x40
#define ND_NA_FLAG_OVERRIDE        0x20

#endif

 /*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

 /*----------------------------------------------*
 * Data Structures                   *
 *----------------------------------------------*/

/* NA message format */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagND_NA
{
    ULONG        ulIfIndex; /* Ifnet index */
    IN6ADDR_S    stDstAddr; /* Destination address */
    IN6ADDR_S    stSrcAddr; /* Source address */
    IN6ADDR_S    stTgtAddr; /* Target address */
    UCHAR        ucSflag; /* Solicit flag */
    UCHAR        ucOflag; /* Override flag */
    UCHAR        ucOptionFlag; /* Option flag */

    /* IPV6 start Defect ID:BYAD14144 Mod : Bharath Date : 28/03/2005  */
    UCHAR        ucDadReply; /* DAD reply flag */
}ND_NA_S;

/*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文 , 2014/1/26   问题单号:S-IP-005-PUBLIC-FUNC-003 */
typedef struct tagND_NA_Timer_Node
{
    SLL_NODE_S stSLLNode;
    ULONG ulIfIndex;
    IN6ADDR_S  stTgtAddr;
    ULONG ulNAInterval;
    ULONG ulNAAttempt;  /*待发送RA报文的次数*/
    ULONG ulExpireHigh; /*下一次RA报文预期时间*/
    ULONG ulExpireLow;  /*下一次RA报文预期时间*/
}ND_NA_TIMER_NODE;

#define IP6_ND_NA_SET_TIME(m_pstVal, m_ulHighMilSec, m_ulLowMilSec, m_ulInterval)\
{\
    ULONG ulTmpHigTim = (m_ulHighMilSec);\
    ULONG ulTmpLowTim = (m_ulLowMilSec) + (m_ulInterval);\
    if (ulTmpLowTim < (m_ulLowMilSec))\
    {\
        ulTmpHigTim = (m_ulHighMilSec) + 1;\
    }\
    (m_pstVal)->ulExpireHigh = ulTmpHigTim;\
    (m_pstVal)->ulExpireLow = ulTmpLowTim;\
}

/*ND定时器超时判断(基于毫秒判断)*/
#define IP6_ND_TIMER_EXPIRE_BY_MS(CUR_MS_H, CUR_MS_L, EXPIRT_MS_H, EXPIRE_MS_L)  \
  ((((CUR_MS_H) == (EXPIRT_MS_H)) && ((CUR_MS_L) >= (EXPIRE_MS_L))) || \
   ((CUR_MS_H) > (EXPIRT_MS_H)))

/*NA定时器超时判断*/
#define IP6_ND_NA_TIMER_EXPIRE(NA_TIMER, CUR_MS_H, CUR_MS_L)  \
  IP6_ND_TIMER_EXPIRE_BY_MS(CUR_MS_H, CUR_MS_L, (NA_TIMER)->ulExpireHigh, (NA_TIMER)->ulExpireLow)

/* End of Added by guojianjun178934, 2014/1/26   问题单号:S-IP-005-PUBLIC-FUNC-003 */


#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif        /* end of _ND_NB_H_ */

