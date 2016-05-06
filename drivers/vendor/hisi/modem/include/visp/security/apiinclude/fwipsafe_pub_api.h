

#ifndef _FWIPSAFE_PUB_API_H_
#define _FWIPSAFE_PUB_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE< Beginning of the return value for every module.>*/
typedef enum enumFWIpsafeGlobalRetCode
{ 
    FWIPSAFE_NAT_BEGIN_RET_CODE   = 1000,   /* NAT module return begin error value */
    FWIPSAFE_PUB_BEGIN_RET_CODE   = 2000,   /* PUB module return begin error value */
    FWIPSAFE_DEBUG_BEGIN_RET_CODE = 3000,   /* Debug module return begin error value */
    FWIPSAFE_LOG_BEGIN_RET_CODE   = 4000,   /* Log module return begin error value */
    FWIPSAFE_BLK_BEGIN_RET_CODE   = 5000,   /* Blk module return begin error value */
    FWIPSAFE_FC_BEGIN_RET_CODE    = 6000,   /* FC module return begin error value */
    FWIPSAFE_FTP_BEGIN_RET_CODE   = 7000,   /* F*P module return begin error value */
    FWIPSAFE_ICMP_BEGIN_RET_CODE  = 8000,   /* ICMP module return begin error value */
    FWIPSAFE_DNS_BEGIN_RET_CODE   = 9000,   /* DNS module return begin error value */
    FWIPSAFE_HTTP_BEGIN_RET_CODE  = 10000,  /* HTTP module return begin error value */
    FWIPSAFE_MSN_BEGIN_RET_CODE   = 11000,  /* MSN module return begin error value */
    FWIPSAFE_RTSP_BEGIN_RET_CODE  = 12000,  /* RTSP module return begin error value */
    FWIPSAFE_H323_BEGIN_RET_CODE  = 13000,  /* H323 module return begin error value */
    FWIPSAFE_QQ_BEGIN_RET_CODE    = 14000,  /* QQ module return begin error value */
    FWIPSAFE_ALG_BEGIN_RET_CODE   = 15000,  /* ALG Frame module return begin error value */    
    FWIPSAFE_STAT_BEGIN_RET_CODE  = 16000,  /* Statistics module return begin error value */
    FWIPSAFE_SMTP_BEGIN_RET_CODE  = 17000,  /* SMTP module return begin error value */
    FWIPSAFE_HASH_BEGIN_RET_CODE  = 18000, /* hash table module return begin error value*/
    FWIPSAFE_FW_BEGIN_RET_CODE    = 19000, /*Firewall Common module*/
    FWIPSAFE_FW_WLS_BEGIN_RET_CODE = 20000, /*Firewall WLS module*/
    FWIPSAFE_FW_BLS_BEGIN_RET_CODE = 21000, /*Firewall BLS module*/
    FWIPSAFE_FW_ATK_BEGIN_RET_CODE = 22000, /*Firewall Attack module*/
    FWIPSAFE_ACL_BEGIN_RET_CODE    = 23000, /*ACL module*/
}FWIPSAFE_GLOBAL_RET_CODE_E;


/*ERRORCODE< Error codes in IPSAFE Init and IPSAFE public modules. > */
enum enumPubCode
{
    FWIPSAFE_PUB_SUCCESS,                                                 /*<0> On success*/
    FWIPSAFE_ERR_BEGIN_CODE = FWIPSAFE_PUB_BEGIN_RET_CODE,                  /*<2000> Beginning of IPSAFE init and public 
                                                                                 module error code.*/
    FWIPSAFE_PUB_INIT_ERR_MEMALLOC_TIMER,                                 /*<2001> Memory Allocation for timer failed in 
                                                                                 ipsafe_pub_init()*/ 
    FWIPSAFE_INIT_ERR_MEMALLOC_GLOBALTIMER,    
    FWIPSAFE_INIT_ERR_MEMALLOC_SPINLOCK,
    FWIPSAFE_INIT_ERR_CREATE_SPINLOCK,
    FWIPSAFE_INIT_ERR_ADDNAME_SPINLOCK,
    FWIPSAFE_INIT_ERR_SPIN_LOCK,
    FWIPSAFE_INIT_ERR_CREATE_SHARE_TIMER,                                 /*<2006> Failed to create share timer */
        
    FWIPSAFE_INIT_ERR_ADDNAME_GLOBALTIMER,                                /*<2010> Failed to add name to shared memory 
                                                                                 database*/
    FWIPSAFE_CMPUTFCIN_ERR_ICMP_ERROR_PKT_EMPTY_SESSION,                  /*<2013> Session for ICMP incoming error packet 
                                                                                 is not present*/
    FWIPSAFE_CMPUTFCOUT_ERR_ICMP_ERROR_PKT_EMPTY_SESSION,                 /*<2014> Session for ICMP Outgoing error packet 
                                                                                 is not present*/
    FWIPSAFE_CMPUTFCIN_ERR_INBOUND_PKT_CONTEXT_NULL,                      /*<2015> Inbound packet context is NULL*/
    FWIPSAFE_CMPUTFCOUT_ERR_INBOUND_PKT_CONTEXT_NULL,                      /*<2016> Packet context is NULL in IPSAFE_ComputeFCOut*/    
    FWIPSAFE_CMPUTFCIN_ERR_INBOUND_PKT_HEADER_NULL,                        /*<2017> Packet header is NULL */
    FWIPSAFE_CMPUTFCOUT_ERR_OUTBOUND_PKT_HEADER_NULL,                       /*<2018> IP  header is NULL in IPSAFE_ComputeFCOutis not present*/
    FWIPSAFE_SET_INVALID_VALUE,                                           /*<2015> Setting Preconfig Parameters failed*/

    FWIPSAFE_SET_INVALID_KEY,                                             /*<2016> Invalid key for setting Preconfig
                                                                                 Parameters*/
    FWIPSAFE_VAL_NULL_PTR,                                                /*<2017> NULL pointer passed for getting
                                                                                 Parameters*/
    FWIPSAFE_GET_INVALID_KEY                                              /*<2018> Invalid key for getting preconfig
                                                                                 Parameters*/
};


extern UINT32 FWIPSAFE_Init(VOID);


/*******************************************************************************
*    Func Name: FWIPSAFE_ShowVersion
* Date Created: 2010-04-21
*       Author: zhangchunyu(62474)
*      Purpose: This function displays the version of IPSAFE.
*  Description: This function displays the version of IPSAFE as defined by 
*               FWIPSAFE_VERSION.
*        Input: 
*       Output:  
*       Return: VOID
*      Caution: None
*        Since: V200R003C01
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-21   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID FWIPSAFE_ShowVersion(VOID);


#ifdef  __cplusplus
}
#endif

#endif

