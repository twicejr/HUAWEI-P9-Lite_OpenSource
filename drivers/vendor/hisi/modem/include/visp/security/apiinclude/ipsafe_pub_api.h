

#ifndef _IPSAFE_PUB_API_H_
#define _IPSAFE_PUB_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* NAT Version */
#define IPSAFE_VERSION "IPSAFE NAT V200R003C02SPC070"


/*ERRORCODE< Beginning of the return value for every module.>*/
typedef enum enumIpsafeGlobalRetCode
{ 
    IPSAFE_NAT_BEGIN_RET_CODE   = 1000,   /* NAT module return begin error value */
    IPSAFE_PUB_BEGIN_RET_CODE   = 2000,   /* PUB module return begin error value */
    IPSAFE_DEBUG_BEGIN_RET_CODE = 3000,   /* Debug module return begin error value */
    IPSAFE_LOG_BEGIN_RET_CODE   = 4000,   /* Log module return begin error value */
    IPSAFE_BLK_BEGIN_RET_CODE   = 5000,   /* Blk module return begin error value */
    IPSAFE_FC_BEGIN_RET_CODE    = 6000,   /* FC module return begin error value */
    IPSAFE_FTP_BEGIN_RET_CODE   = 7000,   /* F*P module return begin error value */
    IPSAFE_ICMP_BEGIN_RET_CODE  = 8000,   /* ICMP module return begin error value */
    IPSAFE_DNS_BEGIN_RET_CODE   = 9000,   /* DNS module return begin error value */
    IPSAFE_HTTP_BEGIN_RET_CODE  = 10000,  /* HTTP module return begin error value */
    IPSAFE_MSN_BEGIN_RET_CODE   = 11000,  /* MSN module return begin error value */
    IPSAFE_RTSP_BEGIN_RET_CODE  = 12000,  /* RTSP module return begin error value */
    IPSAFE_H323_BEGIN_RET_CODE  = 13000,  /* H323 module return begin error value */
    IPSAFE_QQ_BEGIN_RET_CODE    = 14000,  /* QQ module return begin error value */
    IPSAFE_ALG_BEGIN_RET_CODE   = 15000,  /* ALG Frame module return begin error value */    
    IPSAFE_STAT_BEGIN_RET_CODE  = 16000,  /* Statistics module return begin error value */
    IPSAFE_SMTP_BEGIN_RET_CODE  = 17000,  /* SMTP module return begin error value */
    IPSAFE_NBT_BEGIN_RET_CODE   = 18000,  /* NBT module return begin error value */ 
    IPSAFE_MMS_BEGIN_RET_CODE   = 19000,   /* MMS module return begin error value */
    IPSAFE_SIP_BEGIN_RET_CODE   = 20000,    /* SIP module return begin error value, SIP parser return
                                            codes are IPSAFE_SIP_BEGIN_RET_CODE + 500*/
    IPSAFE_ILS_BEGIN_RET_CODE   = 21000,    /* ILS module return begin error value */
    IPSAFE_MGCP_BEGIN_RET_CODE  = 22000  /* MGCP module return begin error value */

}IPSAFE_GLOBAL_RET_CODE_E;


/*ERRORCODE< Error codes in IPSAFE Init and IPSAFE public modules. > */
enum enumPubCode
{
    IPSAFE_PUB_SUCCESS,                                                 /*<0> On success*/
    IPSAFE_ERR_BEGIN_CODE = IPSAFE_PUB_BEGIN_RET_CODE,                  /*<2000> Beginning of IPSAFE init and public 
                                                                                 module error code.*/
    IPSAFE_PUB_INIT_ERR_MEMALLOC_TIMER,                                 /*<2001> Memory Allocation for timer failed in 
                                                                                 ipsafe_pub_init()*/ 
    IPSAFE_INIT_ERR_CREATE_SPINLOCK,                                    /*<2002> Failed to create spin lock*/
    IPSAFE_INIT_ERR_MEMALLOC_SPINLOCK,                                  /*<2003> Failed to allocate memory for global 
                                                                                 spin lock variable*/
    IPSAFE_INIT_ERR_ADDNAME_SPINLOCK,                                   /*<2004> Failed to add name to shared memory 
                                                                                 database*/
    IPSAFE_INIT_ERR_SPIN_LOCK,                                          /*<2005> Spin Lock failed*/

    IPSAFE_INIT_ERR_CREATE_SHARE_TIMER,                                 /*<2006> Failed to create share timer */
    IPSAFE_INIT_ERR_AGING_TIMER_INIT,                                   /*<2007> Failed to initialize aging timer*/
    IPSAFE_INIT_ERR_MEMALLOC_GLOBALTIMER,                               /*<2008> Failed to allocate memory for global 
                                                                                 timer*/
    IPSAFE_INIT_ERR_MEMALLOC_AGINGTIMER,                                /*<2009> Failed to allocate memory for aging 
                                                                                 timer*/
    IPSAFE_INIT_ERR_ADDNAME_GLOBALTIMER,                                /*<2010> Failed to add name to shared memory 
                                                                                 database*/
    IPSAFE_INIT_ERR_ADDNAME_AGINGTIMER,                                 /*<2011> Failed to add name to shared memory 
                                                                                 database*/
    IPSAFE_INIT_ERR_NULL_INPUT_PARA,                                    /*<2012> The input parameter to IPSAFE_INIT() 
                                                                                 is NULL*/
    IPSAFE_CMPUTFCIN_ERR_ICMP_ERROR_PKT_EMPTY_SESSION,                  /*<2013> Session for ICMP incoming error packet 
                                                                                 is not present*/
    IPSAFE_CMPUTFCOUT_ERR_ICMP_ERROR_PKT_EMPTY_SESSION,                 /*<2014> Session for ICMP Outgoing error packet 
                                                                                 is not present*/
    IPSAFE_CMPUTFCIN_ERR_INBOUND_PKT_CONTEXT_NULL,                      /*<2015> Inbound packet context is NULL*/
    IPSAFE_CMPUTFCOUT_ERR_INBOUND_PKT_CONTEXT_NULL,                     /*<2016> Packet context is NULL in 
                                                                                 IPSAFE_ComputeFCOut*/
    IPSAFE_CMPUTFCIN_ERR_INBOUND_PKT_HEADER_NULL,                       /*<2017> Packet header is NULL */
    IPSAFE_CMPUTFCOUT_ERR_OUTBOUND_PKT_HEADER_NULL,                     /*<2018> IP  header is NULL in 
                                                                                 IPSAFE_ComputeFCOut*/
};

#define NAT_NAT 0    /* NAT mode, only translate IP */
#define NAT_PAT 1    /* NAPT mode, translate IP and port */

#define IPSAFE_DEFAULT_CONE             0   /* Default cone */
#define IPSAFE_FULL_CONE                1   /* Full cone */
#define IPSAFE_RESTRICT_CONE            2   /* Restricted cone*/
#define IPSAFE_PORT_RESTRICT_CONE       3   /* Port restricted cone */
#define IPSAFE_SYMMETRIC_CONE           4   /* Symmetric cone */

/*STRUCT< NAT CONE MODE structure > */
typedef struct tagConeMode
{
    UINT8  u8ConeMode;    /*Indicates the Cone Mode. It can be either TRANS_MODE(1) or ALG_MODE(2)*/
    UINT8  u8pad[3];      /*Indicates Padding*/
    union
    {
        struct  tagTransMode
        {
            UINT8 u8TCPMode;   /*TCP mode*/
            UINT8 u8Pad[3];    /*Padding*/
        }TRANS_MODE;

        struct tagAlgMode
        {
            UINT8 u8FtpMode;
            UINT8 u8MsnMode;
            UINT8 u8DnsMode;
            UINT8 u8HttpMode;
            UINT8 u8SmtpMode;
            UINT8 u8RtspMode;
            UINT8 u8MmsMode;
            UINT8 u8NbtMode;
            UINT8 u8SipMode;
            UINT8 u8H323Mode;
            UINT8 u8IlsMode;
            UINT8 u8MgcpMode;
        }ALG_MODE;
        
    }MODE_UN;
}IPSAFE_CONE_MODE;


/*STRUCT< NAT Rule structure > */
typedef struct tagNatPreCfg
{
    UINT32 u32MaxNatSessionNum;      /* Support how many nat session, no limit */
    UINT32 u32AddrPools;             /* Max is 128 */
    UINT16 u16MaxVRF;                /* 1 - No VRF, This will vary from 1 to 256  */
    UINT8  u8NatMode;                /* NAT_NAT(0):NAT mode, only transfer IP,
                                        NAT_PAT(1):NAPT mode, transfer IP and port */ 
    UINT8  u8Pad[1];                 /* Padding */
    IPSAFE_CONE_MODE stModeContent;  /* Different cone mode, set different mode content */
    UINT32 u32MaxFlowStatNum;        /* The maximum number of flow statistics to be supported */
}NAT_PRE_CFG_S;


#define IPSAFE_CONE_MODE_TRANSPORT   1   /* Transport Protocol Mode */
#define IPSAFE_CONE_MODE_ALG         2   /* ALG Protocol Mode */


extern UINT32 IPSAFE_Init(NAT_PRE_CFG_S *pstPreCfg);

/*******************************************************************************
*    Func Name: IPSAFE_ComputeFCIn
* Date Created: 2010-04-19
*       Author: Vinay Gudur
*      Purpose: This function computes the flow context for the given incoming 
*               packet context.
*  Description: This function computes the flow context for the given incoming packet context.
*               The packet context contains details like the source and destination IP and 
*               Based on the type of IP header, the flow context is calculated.
*        Input: PKT_CONTEXT_S *pstPktContext: Pointer to the packet context 
*               structure.<Non null pointer>
*               The User should set the following members of Packet Context before calling
*               this API:
*               a. pstPktContext->u32VpnIndex to 0 if VPN Index is not used else VPN Index value (less than 255)
*               b. pstPktContext->intfHandle to corresponding Interface Handle value.
*               c. pstPktContext->pktHandle to Pointer to message buffer.
*               d. pstPktContext->pstIpHdr to the IP Header.
*
*       Output: 
*       Return: Success: IPSAFE_OK: Computation success
*                   Failure: u32Ret: Refer IPSAFE_FC_Search
*                               u32Ret: Refer ALG_ICMP_SearchFCFromPayload
*                                IPSAFE_CMPUTFCIN_ERR_ICMP_ERROR_PKT_EMPTY_SESSION
*                                IPSAFE_ERR
*      Caution: None
*      Since: V100R008C03
*      Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-04-20   Vinay(71924)     Create the first version.
*
*******************************************************************************/
extern UINT32 IPSAFE_ComputeFCIn(PKT_CONTEXT_S *pstPktContext);


/*******************************************************************************
*    Func Name: IPSAFE_ComputeFCOut
* Date Created: 2010-04-19
*       Author: Vinay Gudur
*      Purpose: This function computes the flow context for the given outgoing packet context.
*  Description: This function computes the flow context for the given outgoing packet context.
*               The packet context contains details like the source and destination IP and 
*               port, the protocol, the checksum, the packet length, the VPN index and so on.
*               Based on the type of IP header, the flow context is calculated.
*        Input: PKT_CONTEXT_S *pstPktContext: Pointer to the packet context 
*               structure.<Non null pointer>
*               The User should set the following members of Packet Context before calling
*               this API:
*               a. pstPktContext->u32VpnIndex to 0 if VPN Index is not used else VPN Index value (less than 255)
*               b. pstPktContext->intfHandle to corresponding Interface Handle value.
*               c. pstPktContext->pktHandle to Pointer to message buffer.
*               d. pstPktContext->pstIpHdr to the IP Header.
*       Output: 
*       Return: Success: IPSAFE_OK: Computation success
*                   Failure: u32Ret: Refer IPSAFE_FC_Attach()
*                               u32Ret: Refer ALG_ICMP_SearchFCFromPayload()
*                               IPSAFE_CMPUTFCOUT_ERR_ICMP_ERROR_PKT_EMPTY_SESSION
*                               IPSAFE_ERR
*      Caution: None
*      Since: V100R008C03
*      Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-04-20   Vinay(71924)     Create the first version.
*
*******************************************************************************/
extern UINT32 IPSAFE_ComputeFCOut(PKT_CONTEXT_S *pstPktContext);


/*******************************************************************************
*    Func Name: IPSAFE_ShowVersion
* Date Created: 2010-04-21
*       Author: zhangchunyu(62474)
*      Purpose: This function displays the version of IPSAFE.
*  Description: This function displays the version of IPSAFE as defined by 
*               IPSAFE_VERSION.
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
VOID IPSAFE_ShowVersion(VOID);


#ifdef  __cplusplus
}
#endif

#endif

