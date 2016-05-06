/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipsec_pfkey_ike.h
  Version       : Initial Draft
  Author        : Mahendra
  Created       : 2006/10/5
  Last Modified :
  Description   : Defines pfkey macros and structures required by IKE
  Function List :
  History       :
  1.Date        : 2006/10/5
    Author      : Mahendra
    Modification: Created file

******************************************************************************/


#ifndef _IPSEC_PFKEY_IKE_H
#define _IPSEC_PFKEY_IKE_H

#ifdef __cplusplus
extern "C" {
#endif


#define PFKEYV2_SOCKETFLAGS_REGISTERED 1
#define PFKEYV2_SENDMESSAGE_REGISTERED 2
#define PFKEYV2_SENDMESSAGE_BROADCAST  3

#define PF_KEY_V2 2

/* Message Types */
#define SADB_RESERVED                           0
#define SADB_GETSPI                             1
#define SADB_UPDATE                             2
#define SADB_ADD                                3
#define SADB_DELETE                             4
#define SADB_GET                                5
#define SADB_ACQUIRE                            6
#define SADB_REGISTER                           7
#define SADB_EXPIRE                             8
#define SADB_DELSA                              9
#define SADB_DUMP                               10
#define SADB_X_PROMISC                          11
#define SADB_X_ADDFLOW                          12
#define SADB_X_DELFLOW                          13
#define SADB_X_GRPSPIS                          14
#define SADB_X_BINDSA                           15
#define SADB_X_FILLTDBENTRY                     16
#define SADB_X_FIRSTCRYPTOMAP                   17
#define SADB_X_NEXTCRYPTOMAP                    18
#define SADB_DEL_ALLSA                          19
#define SADB_PUTSPI                             20
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
#define SADB_X_DEL_ALLSA                        21
#define SADB_X_DEL_POLICY                       22
#define SADB_X_DEL_REMOTE                       23
#define SADB_DEL_ALL_PH1PH2_SA                  24
#endif

/* DPD message type */
#define SADB_X_DPD                              25

/* Message type to trigger modecfg, acquire for modecfg and address
notification */
#define SADB_X_TRIGGER_MODE_CFG                 26
#define SADB_X_ACQUIRE_MODE_CFG                 27
#define SADB_X_MODE_CFG_ADD_DEL                 28
#define SADB_X_MODECFG_DELETE_ADDRESS           29

#define SADB_X_INVALID_SPI                      30
#define SADB_X_INVALID_SELECTORS                31
#define SADB_X_MODE_CFG_FILLTDBENTRY            32
#define SADB_X_IKEV2_DEL_ALL_P1P2_SA            33

/* Sumangala : Added for New API requirement from SGSN */
#define SADB_X_DEL_P1P2_SA_BY_PEER              34
#define SADB_X_DEL_P1P2_SA_BY_PEER_DNT_NOTIFY   35

/* AC4D07706 : New requirement to delete IKEv1 ready/non-ready state SA's */
#define SADB_X_DEL_SA_SYNC                      36

/*Pfkey-Optimization:STORY-1,2,3*/
#define SADB_X_FINALIZE_TDB                     37

/*Kuldeep : B513 Changes*/

/*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
#define SADB_X_DEL_P1P2_SA_BY_PEERNAME              38
#define SADB_X_DEL_P1P2_SA_BY_PEERNAME_DNT_NOTIFY   39

#define SADB_X_DEL_P2_SA_BY_PEERNAME                40
#define SADB_X_DEL_P2_SA_BY_PEERNAME_DNT_NOTIFY     41
#define SADB_X_IKEV2_DEL_P1P2_SA_BY_PEER_DNT_NOTIFY_SYNC    42
#define SADB_X_IKEV1_DEL_P1P2_SA_BY_PEER_DNT_NOTIFY_SYNC    43
#define SADB_X_INVALID_IPSEC6_SPI                      44
#define SADB_MAX                                44

 /* Authentication algorithms */
#define SADB_AALG_NONE                0
#define SADB_AALG_MD5HMAC             1
#define SADB_AALG_SHA1HMAC            2
#define SADB_AALG_MD5HMAC96           3
#define SADB_AALG_SHA1HMAC96          4
#define SADB_AALG_X_RIPEMD160HMAC96   5
#define SADB_AALG_X_MD5               6
#define SADB_AALG_X_SHA1              7
#define SADB_AALG_SHA2HMAC256         8
#define SADB_AALG_SHA2HMAC384         9
#define SADB_AALG_SHA2HMAC512         10
#define SADB_AALG_AESXCBC_96          11
#define SADB_AALG_MAX                 11

/* To Support MIPS : Vivek K Sriwastava  */
#define SADB_IPSEC_MIPS_RESERVED      0


/* Encryption algorithms */
#define SADB_EALG_NONE                0
#define SADB_EALG_DESCBC              1
#define SADB_EALG_3DESCBC             2
#define SADB_EALG_X_BLF               3
#define SADB_EALG_X_CAST              4
#define SADB_EALG_X_SKIPJACK          5
#define SADB_EALG_HARDWARE_56S        6   /* hardware from 56 */
#define SADB_EALG_AES                 7
#define SADB_EALG_MAX                 7

/* Extension Header Values */
#define IPSEC_SADB_EXT_RESERVED             0
#define IPSEC_SADB_EXT_SA                   1
#define IPSEC_SADB_EXT_LIFETIME_CURRENT     2
#define IPSEC_SADB_EXT_LIFETIME_HARD        3
#define IPSEC_SADB_EXT_LIFETIME_SOFT        4
#define IPSEC_SADB_EXT_ADDRESS_SRC          5
#define IPSEC_SADB_EXT_ADDRESS_DST          6
#define IPSEC_SADB_EXT_ADDRESS_PROXY        7

/*Iteration2: Story12: Maintainance*/
/* IPSEC_SADB_EXT_KEY_MAT is used instead of
    IPSEC_SADB_EXT_KEY_AUTH & IPSEC_SADB_EXT_KEY_ENCRYPT has been removed.*/
/*Pfkey-Optimization:STORY-1,2,3*/
#define IPSEC_SADB_EXT_KEY_MAT              8
#define IPSEC_SADB_EXT_GET                  9
#define IPSEC_SADB_EXT_IDENTITY_SRC         10
#define IPSEC_SADB_EXT_IDENTITY_DST         11
#define IPSEC_SADB_EXT_SENSITIVITY          12
#define IPSEC_SADB_EXT_PROPOSAL             13
#define IPSEC_SADB_EXT_SUPPORTED            14
#define IPSEC_SADB_EXT_SPIRANGE             15
#define IPSEC_SADB_EXT_X_LIFETIME_CMD       16
#define IPSEC_SADB_EXT_X_DST_MASK           17
#define IPSEC_SADB_EXT_X_PROTOCOL           18
#define IPSEC_SADB_EXT_X_SA2                19
#define IPSEC_SADB_EXT_X_SRC_FLOW           20
#define IPSEC_SADB_EXT_X_DST_FLOW           21
#define IPSEC_SADB_EXT_X_DST2               22
#define IPSEC_SADB_EXT_CRYPTOMAP_NAME       23
#define IPSEC_SADB_EXT_IFINDEX              24
#define IPSEC_SADB_EXT_NAT_ID               25

/* DPD message extension type */
#define IPSEC_SADB_EXT_DPD                  26

/*Modcfg sequence number, address notification, peername extension types */
#define IPSEC_SADB_EXT_MODE_CFG_SEQUENCE    27
#define IPSEC_SADB_EXT_MODE_CFG_ADDR_NOTIFY 28
#define IPSEC_SADB_EXT_PEER_NAME            29
#define IPSEC_SADB_EXT_INVALID_SELECTOR     30

#define IPSEC_SADB_EXT_MAX                  30

/* Security Association Types */
#define IPSEC_SADB_SATYPE_UNSPEC            0
#define IPSEC_SADB_SATYPE_AH                1
#define IPSEC_SADB_SATYPE_ESP               2
#define IPSEC_SADB_SATYPE_RSVP              3
#define IPSEC_SADB_SATYPE_OSPFV2            4
#define IPSEC_SADB_SATYPE_RIPV2             5
#define IPSEC_SADB_SATYPE_MIP               6
#define IPSEC_SADB_SATYPE_X_AH_OLD          7
#define IPSEC_SADB_SATYPE_X_ESP_OLD         8
#define IPSEC_SADB_SATYPE_X_IPIP            9

/*Pfkey-Optimization:STORY-1,2,3*/
#define IPSEC_SADB_SATYPE_AHESP_BUNDLE      10
#define IPSEC_SADB_SATYPE_MAX               10

/* Security Association States */
#define IPSEC_SADB_SASTATE_LARVAL           0
#define IPSEC_SADB_SASTATE_MATURE           1
#define IPSEC_SADB_SASTATE_DYING            2
#define IPSEC_SADB_SASTATE_DEAD             3
#define IPSEC_SADB_SASTATE_MAX              3

/* Security Association Flags */
/* DH Grp 5&14 support */
#define IPSEC_SADB_SAFLAGS_ZERO             0x0     /* For Invalid DH Group */
#define IPSEC_SADB_SAFLAGS_PFS              0x01    /* perfect forward secrecy */
#define IPSEC_SADB_SAFLAGS_PFS_ACC          0x02
#define IPSEC_SADB_SAFLAGS_X_HALFIV         0x02    /* Used for ESP-old */
#define IPSEC_SADB_SAFLAGS_X_TUNNEL         0x04    /* Force tunneling */
#define IPSEC_SADB_SAFLAGS_X_CHAINDEL       0x08    /* Delete whole SA chain */
#define IPSEC_SADB_SAFLAGS_X_LOCALFLOW      0x10    /* Add flow with src=0.0.0.0 */
#define IPSEC_SADB_SAFLAGS_X_REPLACEFLOW    0x20    /* Replace existing flow */
#define IPSEC_SADB_SAFLAGS_PFS_GROUP2       0x40    /* add by zy */
#define IPSEC_SADB_SAFLAGS_INBOUND          0x80    /* Inbound SA.  */
#define IPSEC_SADB_SAFLAGS_X_TRANSPORT      0x0100  /* Force transport */
#define IPSEC_SADB_SAFLAGS_X_UDP_TUNNEL     0x0200  /* Force udp tunneling for
                                                 nat traversal */
#define IPSEC_SADB_SAFLAGS_X_UDP_TRANSPORT  0x0400  /* Force udp transport for
                                                 nat traversal */
#define IPSEC_SADB_SAFLAGS_PFS_GROUP5       0x0800    /* DH Grp5 */
#define IPSEC_SADB_SAFLAGS_PFS_GROUP14      0x1000    /* DH Grp14 */
#define IPSEC_SADB_SAFLAGS_PFS_GROUP15      0x2000    /* DH Grp15 */


/* Identity Extension Values */
#define IPSEC_SADB_IDENTTYPE_RESERVED       0
#define IPSEC_SADB_IDENTTYPE_PREFIX         1
#define IPSEC_SADB_IDENTTYPE_FQDN           2
#define IPSEC_SADB_IDENTTYPE_MBOX           3
#define IPSEC_SADB_IDENTTYPE_CONNECTION     4
#define IPSEC_SADB_IDENTTYPE_IPV4ADDR       5
#define IPSEC_SADB_IDENTTYPE_IPV4SUBNET     6
#define IPSEC_SADB_IDENTTYPE_IPV6ADDR       7
#define IPSEC_SADB_IDENTTYPE_IPV6SUBNET     8
#define IPSEC_SADB_IDENTTYPE_MAX            8

#define IPSEC_SADB_IDENTLEN_MAX             11

/* DPD extension message IPSEC_SADB_DPD_S, usDpdExtType values */
#define IPSEC_SADB_MSG_VENDOR_ID_SUCCESS     1
#define IPSEC_SADB_MSG_VENDOR_ID_FAILURE     2
#define IPSEC_SADB_MSG_DPD_PEER_ALIVE        3
#define IPSEC_SADB_MSG_DPD_PEER_DEAD         4
#define IPSEC_SADB_MSG_DPD_TRIGGER           5
#define IPSEC_SADB_MSG_STOP_DPD              6

#define IPSEC_SADB_MSG_MODECFG_ADDRESS_ADD     1
#define IPSEC_SADB_MSG_MODECFG_ADDRESS_DELETE  2

/*Pfkey-Optimization:STORY-1,2,3*/
#define IPSEC_SADB_MAX_KEY_LEN                64

/*This macro should be the same as IPSEC_MAX_MAP_NAME */
#define IPSEC_SADB_MAX_MAP_NAME               15

/*Ipsec proposal protocols*/
#define IPSEC_SADB_PROTO_AH                  1
#define IPSEC_SADB_PROTO_ESP                 2
#define IPSEC_SADB_PROTO_AHESP               3
#define IPSEC_SADB_PROTO_IP4                 4    /* IP inside IP */

/*GGSN-SUPPORT : IKEv2 Responder SPI Length*/
#define IPSEC_SADB_RCOOKIE_LENGTH              8

/* Base Message Header Format. */
struct sadb_msg
{
    UCHAR sadb_msg_version;   /* The version field of this PF_KEY message */
    UCHAR sadb_msg_type;      /* Identifies the type of message */
    UCHAR sadb_msg_errno;     /* Should be set to zero by the sender. The
                                 responder stores the error code in this field
                                 if an error has occurred */
    UCHAR sadb_msg_satype;    /* Indicates the type of security association(s) */
    USHORT sadb_msg_len;      /* Contains the total length, in 64-bit words, of
                                 all data in the PF_KEY message */
    UCHAR sadb_msg_IPVersion; /* IP version information */
    UCHAR sadb_msg_reserved;  /* Reserved value */
    ULONG sadb_msg_seq;       /* Contains the sequence number of this message */
    ULONG sadb_msg_pid;       /* Identifies the process which originated this
                                 message */
    ULONG sadb_msg_node;      /* Indicate which slot to send. */
    ULONG sadb_msg_ifindex;   /* Add for ipsec over VT */
};

/* The additional data following the base header consists of various
   length-type-values fields */
struct sadb_ext
{
    USHORT sadb_ext_len;      /* Length of the extension header in 64bit word */
    USHORT sadb_ext_type;     /* The type of extension header that follows */
};


/* For transmitting cryptomap name and sequence. */
struct sadb_cryptomap_name
{
    USHORT sadb_cryptomap_name_len;
    USHORT sadb_cryptomap_name_exttype;
    USHORT sadb_cryptomap_name_reserved;
    USHORT usCryptomapType;

    ULONG  sadb_cryptomap_name_number;

    /* B049: AP - ModecfgRekey: During Rekey, Ike provides the
       modecfg sequence number for finding the flow information.*/
    ULONG  sadb_cryptomap_name_modecfg_seqnumber;

    UCHAR   ucDscp;         /*[Defect :AC4D07824] B115 dscp solution*/
    UCHAR   ucDeleteNotifyFlag;  /* Indicates if Notification needs to be
                                       sent to peer on SA deletion by policy */
    UCHAR   ucPad1[2];
    ULONG   ulV1SemID;        /* This semaphore has to be released once the SA
                                  deletion by policy is complete in IKEv1 */
    ULONG   ulV2SemID;        /* This semaphore has to be released once the SA
                                deletion by policy is complete in IKEv2 */
};

struct sadb_invalid_selector
{
    USHORT sadb_invalid_selector_len;
    USHORT sadb_invalid_selector_exttype;
};


/* For transmitting ifindex. */
struct sadb_ifidx
{
    USHORT sadb_ifidx_len;
    USHORT sadb_ifidx_exttype;

    /* added for aggressive */
    USHORT sadb_sour_port;              /* Source port */
    USHORT sadb_dest_port;              /* Destination port */
    ULONG sadb_ifidx_number;            /* Ifnet index number */
    ULONG sadb_conn_id;
    ULONG sadb_ikesaconnid;            /*GGSN-SUPPORT: DPD*/

    /*GGSN:HA*/
    UCHAR sadb_IKE_RespSpi[IPSEC_SADB_RCOOKIE_LENGTH];
};

/* The Association extension specifies data specific to a single
   security association */
struct sadb_sa
{
    USHORT sadb_sa_len;      /* Length of the extension header in 64 bit word */
    USHORT sadb_sa_exttype;  /* The type of extension header that follows */

    /*Pfkey-Optimization:STORY-1,2,3*/
    ULONG sadb_sa_out_spi;       /* The Security Parameters Index value for
                                the Outbound security association */

    ULONG sadb_sa_in_spi;       /* The Security Parameters Index value for
                                the Inbound security association */

    UCHAR sadb_sa_replay;    /* The size of the replay window */
    UCHAR sadb_sa_state;     /* The state of the security association */
    UCHAR sadb_sa_auth;      /* The authentication algorithm to be used with
                                this security association */
    UCHAR sadb_sa_encrypt;   /* The encryption algorithm to be used with this
                                security association */
    ULONG sadb_sa_flags;     /* A bitmap of options defined for the security
                                association. */
    ULONG sadb_sa_vpnindex;  /* VPN index */
    ULONG sadb_sa_conn_id;   /* LOOP_OPT: To hash Sa based on ConnId*/
    /*HS:Added as Now Packet Handling is done in IPSEC sw \
    sadb_sa_usage = 1(means IPSEC sa can be used to send traffic)*/
    ULONG sadb_sa_usage;
};

/* Lifetime Extension */
struct sadb_lifetime
{
    USHORT sadb_lifetime_len;
    USHORT sadb_lifetime_exttype;
    ULONG sadb_lifetime_allocations;
    ULONG sadb_lifetime_bytes;
    ULONG sadb_lifetime_addtime;
    ULONG sadb_lifetime_usetime;
};

/* Address extension */
struct sadb_address
{
    USHORT sadb_address_len;
    USHORT sadb_address_exttype;
    ULONG sadb_address_reserved;
    ULONG sadb_ulVrfIndex;
};

/*Pfkey-Optimization:STORY-1,2,3*/
struct sadb_key_mat
{
    ULONG ulKeyLen;
    UCHAR aucInKey[IPSEC_SADB_MAX_KEY_LEN];
    UCHAR aucOutKey[IPSEC_SADB_MAX_KEY_LEN];
};

/* For tansfer key material from IKE to IPSEC.
 * sadb_key_len = sizeof(struct sadb_key) + length of key material
 * Key material will be appended at the end of this structure. S*/
/*Pfkey-Optimization:STORY-1,2,3*/
struct sadb_key
{
    USHORT sadb_key_len;
    USHORT sadb_key_exttype;
    USHORT sadb_key_proto_type;
    USHORT sadb_key_reserved;
    struct sadb_key_mat sadb_ah_key_mat;
    struct sadb_key_mat sadb_esp_auth_key_mat;
    struct sadb_key_mat sadb_esp_encr_key_mat;
};

/* The Identity extension */
struct sadb_ident
{
    USHORT sadb_ident_len;
    USHORT sadb_ident_exttype;
    USHORT sadb_ident_type;   /* The type of identity info that follows */
    USHORT sadb_ident_reserved;
    ULONG sadb_ident_id;      /* An identifier used to aid in the construction
                                 of an identity string if none is present */
    ULONG sadb_ident_num;
};

/* NAT_ID extenstion */
struct sadb_nat_id
{
    USHORT sadb_nat_len;
    USHORT sadb_nat_exttype;
    USHORT sadb_nat;
    USHORT sadb_nat_id_flag;
};

/* The Sensitivity extension contains security labeling information for
   a security association */
struct sadb_sens
{
    USHORT sadb_sens_len;
    USHORT sadb_sens_exttype;
    ULONG sadb_sens_dpd;            /* Describes the protection domain, which
                                       allows interpretation of the levels and
                                       compartment bitmaps. */
    UCHAR sadb_sens_sens_level;     /* The sensitivity level */
    UCHAR sadb_sens_sens_len;       /* The length, in 64 bit words,
                                       of the sensitivity bitmap. */
    UCHAR sadb_sens_integ_level;    /* The integrity level */
    UCHAR sadb_sens_integ_len;      /* The length, in 64 bit words, of the
                                       integrity bitmap*/
    ULONG sadb_sens_reserved;
};

/* Proposal extension */
typedef struct sadb_prop
{
    USHORT sadb_prop_len;
    USHORT sadb_prop_exttype;
    UCHAR sadb_prop_no;             /* Proposal number */
    UCHAR sadb_prop_replay;
    USHORT sadb_prop_reserved;
    USHORT sadb_prop_protoid;
    USHORT sadb_prop_ntransforms;
}SADB_PROP_S;

/* proposed parameter combinations */
struct sadb_comb
{
    ULONG sadb_comb_trans_id;
    UCHAR sadb_comb_auth;   /* If this combination is accepted, this will be the
                               value of sadb_sa_auth */
    UCHAR sadb_comb_encrypt; /* If this combination is accepted, this will be
                                the value of sadb_sa_encrypt */
    USHORT sadb_comb_flags;

    /* The minimum and maximum acceptable authentication key lengths,in bits. */
    USHORT sadb_comb_auth_minbits;
    USHORT sadb_comb_auth_maxbits;

    /* The minimum and maximum acceptable encryption key lengths,in bits. */
    USHORT sadb_comb_encrypt_minbits;
    USHORT sadb_comb_encrypt_maxbits;

    ULONG sadb_comb_reserved;

    /* If this combination is accepted, these are proposed values of
       sadb_lifetime_allocations in the SOFT and HARD lifetimes, respectively */
    ULONG sadb_comb_soft_allocations;
    ULONG sadb_comb_hard_allocations;

    /* If this combination is accepted, these are proposed values of
        sadb_lifetime_bytes in the SOFT and HARD lifetimes, respectively. */
    ULONG sadb_comb_soft_bytes;
    ULONG sadb_comb_hard_bytes;

    /* If this combination is accepted, these are proposed values of
       sadb_lifetime_addtime in the SOFT and HARD lifetimes, respectively. */
    ULONG sadb_comb_soft_addtime;
    ULONG sadb_comb_hard_addtime;

    /* If this combination is accepted, these are proposed values of
       sadb_lifetime_usetime in the SOFT and HARD lifetimes, respectively. */
    ULONG sadb_comb_soft_usetime;
    ULONG sadb_comb_hard_usetime;
};

/* Supported Algorithms Extension */
struct sadb_supported
{
    USHORT sadb_supported_len;
    USHORT sadb_supported_exttype;
    UCHAR sadb_supported_nauth;
    UCHAR sadb_supported_nencrypt;
    USHORT sadb_supported_reserved;
};

/* Algorithm  descriptions */
struct sadb_alg
{
    UCHAR sadb_alg_type;     /* The identification value for this algorithm */
    UCHAR sadb_alg_ivlen;    /* The length of the initialization vector to be
                                used for the algorithm */
    USHORT sadb_alg_minbits; /* The minimum acceptable key length, in bits */
    USHORT sadb_alg_maxbits; /* The maximum acceptable key length, in bits */
    USHORT sadb_alg_reserved;
};

/* SPI Range Extension */
struct sadb_spirange
{
    USHORT sadb_spirange_len;
    USHORT sadb_spirange_exttype;
    ULONG sadb_spirange_min;    /* The minimum acceptable SPI value */
    ULONG sadb_spirange_max;    /* The maximum acceptable SPI value */
    ULONG sadb_spirange_reserved;
    UCHAR sadb_IKE_RespSpi[IPSEC_SADB_RCOOKIE_LENGTH];
};

/* Protocol Extension */
struct sadb_protocol
{
    USHORT sadb_protocol_len;
    USHORT sadb_protocol_exttype;
    UCHAR  sadb_protocol_proto;
    UCHAR  sadb_protocol_reserved1;
    USHORT sadb_protocol_reserved2;
};

/* This extension is used by IKE to send
   Vendor id negotiation result
   DPD check result
   Used by IPsec to send
   DPD trigger
   Stop message */
typedef struct tagSADB_DPD_S
{

    /* IPSEC6.ITR2.STORY4 */
    USHORT usSadbDpdLen;
    USHORT usSadbDpdExtType;
    USHORT usSadbMsgType;
    USHORT usSadbSrcPort;
    USHORT usSadbDstPort;
    USHORT usIsDynaPeer;
    /*Ipv6: Security Support*/
    CHAR  szPeerName[IPSEC_PEER_NAME_MAX_LEN];

    /* TBD: This var has to be removed, the addr para will be attached at end */
    ULONG  ulSadbDestAddr;
    ULONG ulSadbIkeSaConnid;    /*GGSN-SUPPORT: DPD*/
}SADB_DPD_S;


/*
    This extension is sent by IPsec to IKE for acquire for mode-cfg policy
    Used by IKE to during delete sa and fill tdb entry notification
*/
typedef struct tagSADB_MODE_CFG_SEQUENCE_S
{
    USHORT usSadbModeCfgSeqLen;
    USHORT usSadbModeCfgSeqExttype;
    USHORT usSadbModeCfgSeq;
    USHORT usSadbModeCfgSeqReserved;

    /* AC4D07629: Updated for suggession address */
    ULONG  ulModeCfgSugAddr;
    ULONG  ulModeCfgSugMask;
}SADB_MODE_CFG_SEQUENCE_S;

/* This is used by IKE to send Address notification to IPsec */
typedef struct tagSADB_MODE_CFG_ADDR_NOTIFY_S
{
    USHORT usSadbProtocolLen;
    USHORT usSadbProtocolExttype; /*SADB_X_EXT_MODECFG*/
    ULONG  ulSadbInterfaceIndex;
    ULONG  ulSadbMsgType;/* Add/DEL*/
    ULONG  ulSadbCount;
    USHORT usApplId;
    USHORT usReserved;
}SADB_MODE_CFG_ADDR_NOTIFY_S;

/* This is used by IPsec to send modecfg trigger to IKE */
typedef struct tagSADB_PEER_NAME_S
{
    USHORT usSadbPeerNameLen;
    USHORT usSadbPeerNameExttype;
}SADB_PEER_NAME_S;

/*Pfkey-Optimization:STORY-1,2,3*/
/*Structure used to send the Ipsec proposal and SPI information*/
typedef struct tagSADB_PROP_DETAILS_S
{
    struct sadb_prop sadb_prop;
    struct sadb_comb sadb_comb;
}SADB_PROP_DETAILS_S;

/*This is used to send Cryptomap, Proposal and SPI details from Ipsec to IKE*/
typedef struct tagSADB_MAP_PROP_SPI_S
{
    /*Extension Header Parameters*/
    USHORT usSadbMsgLen;
    USHORT usSadbMsgExtType;

    /*Cryptomap Parameters*/
    UCHAR  sadb_cryptomap_name[IPSEC_SADB_MAX_MAP_NAME + 1];
    USHORT sadb_cryptomap_name_reserved;
    USHORT sadb_cryptomap_pfs_flag;

    ULONG sadb_cryptomap_name_number;

    UCHAR  sadb_cryptomap_Type;
    UCHAR  sadb_cryptomap_Dscp;         /*[Defect :AC4D07824] B115 dscp solution*/

    /*Number of Proposals for the cryptomap*/
    USHORT sadb_prop_count;
}SADB_MAP_PROP_SPI_S;

/*Pfkey-Optimization:STORY-1,2,3*/
/*Structure used to send the Identification details in the Pfkey msg buffer*/
typedef struct tagSADB_IDENT_DATA_S
{
    ULONG sadb_ident_type; /*Type can be Address or Mask*/
    ULONG sadb_ident_addr; /*IP Address */
    ULONG sadb_ident_mask; /*Address mask*/
    USHORT sadb_ident_port; /*Port Number*/
    UCHAR sadb_ident_proto_id;   /*Protocol Id*/
    UCHAR sadb_reserved;
}SADB_IDENT_DATA_S;

/*Ipv6: Security Support*/
typedef struct tagSADB_IPV6_ADDR_AND_MASK
{
    IN6ADDR_S stAddr;
    IN6ADDR_S stAddrMask;
    USHORT usPort;
    USHORT usEndPort;
    UCHAR ucProtocolId;
    UCHAR ucType;
    UCHAR ucPad[2];
}SADB_IPV6_ADDR_AND_MASK;

typedef struct tagSADB_IPV6_IDDATA
{
    /* The ID Information that has to be sent to IKE including addr and mask */
    SADB_IPV6_ADDR_AND_MASK stIpv6AddrMask;

    /* THe ID typr that is being sent, the same value is present in
       stIpv6AddrMask as stIpv6AddrMask.ucTypeIPSEC uses this ucIdType
       internally, and is not sent to IKE.
     */
    UCHAR ucIdType;

    /* Alignment pading */
    UCHAR ucResv[3];
}SADB_IPV6_IDDATA;

#define SADB_ACQ_MSGLEN(m_pucAcqData)\
(((SADB_MAP_PROP_SPI_S *)(m_pucAcqData))->usSadbMsgLen)
/*Pfkey-Optimization:STORY-1,2,3*/

#define SADB_GET_MSGTYPE_AND_IPADDR(m_pstDpdMsg, m_szMsgType, m_ulAddr, \
                                    m_szAddr, m_usMsgType)\
{\
    extern CHAR *VOS_strcpy(CHAR *dst, const CHAR *src);\
    extern CHAR *VOS_IpAddrToStr(ULONG ulAddr, CHAR *szStr);\
    (m_usMsgType) = (USHORT)VOS_HTONS((m_pstDpdMsg)->usSadbMsgType);\
    switch (m_usMsgType)\
    {\
        case IPSEC_SADB_MSG_VENDOR_ID_SUCCESS:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "VENDOR_ID_SUCCESS", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
        case IPSEC_SADB_MSG_VENDOR_ID_FAILURE:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "VENDOR_ID_FAILURE", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
        case IPSEC_SADB_MSG_DPD_PEER_ALIVE:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "DPD_PEER_ALIVE", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
        case IPSEC_SADB_MSG_DPD_PEER_DEAD:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "DPD_PEER_DEAD", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
        case IPSEC_SADB_MSG_DPD_TRIGGER:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "DPD_TRIGGER", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
        case IPSEC_SADB_MSG_STOP_DPD:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "STOP_DPD", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
        default:\
        {\
            (VOID)VOS_strncpy((CHAR *)(m_szMsgType), "Unknown", IPSEC_DEBUG_STR_LENGTH_32);\
            break; \
        }\
    }\
    (m_ulAddr) = VOS_NTOHL((m_pstDpdMsg)->ulSadbDestAddr);\
    (VOID)VOS_IpAddrToStr((m_ulAddr), (CHAR *)(m_szAddr));\
}

/*Iteration2: Story12: Maintainance*/
typedef enum IPSEC_Pfkeyv2_MSG_STATUS_E
{
    SADB_ACQUIRE_SENT_FAIL = (SADB_MAX + 1), /* Continuing from SADB_MAX*/
    SADB_FILL_RECVD_FAIL,
    SADB_GET_RESP_FAILURE,
    SADB_GETSPI_FAILURE,
    SADB_GRPSPI_FAILURE,
    SADB_FILL_FAILURE,
    SADB_DELETE_FAILURE
}IPSEC_PFKEYV2_FAIL_E;


#ifdef __cplusplus
}
#endif

#endif /*_IPSEC_PFKEY_IKE_H*/
