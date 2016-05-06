

#ifndef _IKE_PUB_H_
#define _IKE_PUB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Ipv6: Security Support*/
#define IKE_IP_COM  0
#define IKE_IP_VER4 4
#define IKE_IP_VER6 6

/*Kuldeep : B514 Changes*/
#define IKE_PUB_ID_MAX_LENGTH               131
#define IKE_PEER_NAME_MAX_LEN               32

/* Added for EasyVPN */
#define IKE_MIN_KEY_LEN                     1
#define IKE_KEY_MAX_LEN                     128

/* Added for EasyVPN */
#define IKE_MIN_REMOTE_ID_LEN               1
#define IKE_MAX_REMOTE_ID_LEN               256
#define IKE_MAX_REMOTE_ADDR_LEN             256
#define IKE_MAX_EXCH_NAME_LEN               128
#define IKE_MAX_EVENT_NAME_LEN              64
/* Added for EasyVPN */
#define IKE_MIN_REMOTE_NAME_LEN             1
#define IKE_MAX_REMOTE_NAME_LEN             132
/*Kuldeep : B514 Changes*/
#define IKE_MAX_LOCAL_NAME_LEN              132
#define IKE_MAX_FIELD_NAME_LEN              32
#define IKE_MAX_IFNET_NAME_LEN              48
#define IKE_MAX_FLAG_STR_LEN                32
#define IKE_MAX_VPN_NAME_LEN                31
#define IKE_MAX_TRPT_NAME_LEN               16
#define ISAKMP_EXCH_ID_PROT                 2

/* From ike_ipsnum.h */
/* IPSEC ID type DOI values */
#define IPSEC_ID_IPV4_ADDR                  1
#define IPSEC_ID_FQDN                       2
#define IPSEC_ID_USER_FQDN                  3
#define IPSEC_ID_IPV4_ADDR_SUBNET           4
#define IPSEC_ID_IPV6_ADDR                  5
#define IPSEC_ID_IPV6_ADDR_SUBNET           6
#define IPSEC_ID_IPV4_RANGE                 7
#define IPSEC_ID_IPV6_RANGE                 8
#define IPSEC_ID_DER_ASN1_DN                9
#define IPSEC_ID_DER_ASN1_GN                10
#define IPSEC_ID_KEY_ID                     11

/*Ipv6: Security Support*/
#define IPSEC_ID_IPV6_ADDR                  5
#define IKE_STRLEN_64                       64
#define IKE_STRLEN_32                       32
#define IKE_STRLEN_16                       16
#define IKE_STRLEN_4                        4


/*Prateek Moved from Ikev2_def.h*/
#define IKEV2_ID_IPV4_ADDR                  1
#define IKEV2_ID_FQDN                       2

/* Same as IPSEC_ID_USER_FQDN */
#define IKEV2_ID_RFC822_ADDR                3
#define IKEV2_ID_IPV6_ADDR                  5
#define IKEV2_ID_KEY_ID                     11

#define IKE_DEBUG_SET                       1
#define IKE_DEBUG_RESET                     0

#define IKE_CONNECTION_ID_MIN               1

#define IKE_CONNECTION_ID_MAX         65536  /* for GGSN */


/*BEGIN : R3-C03 */
#define IKE_PEER_INDEX_MIN                  1
/* IKE_PEER_INDEX_MAX shoule be grater or equal IKE_CONFIG_PEER_CUR + IKE_PROF_PEER_CUR */
#define IKE_PEER_INDEX_MAX                  3072

/*END : R3-C03 */

/*Added for cfg opmode*/
#define IKE_MODE_SET                    0
#define IKE_MODE_UNDO                   1
#define IKE_MODE_ENCR_ALG_DES           2
#define IKE_MODE_ENCR_ALG_3DES          3
#define IKE_MODE_AUTH_ALG_MD5           4
#define IKE_MODE_AUTH_ALG_SHA1          5

/* AES_XCBC Support */
#define IKE_MODE_AUTH_AES_XCBC_96       6
/*HS:Sha2-support*/
#define IKE_MODE_AUTH_ALG_SHA2_256      7
#define IKE_MODE_AUTH_ALG_SHA2_384      8
#define IKE_MODE_AUTH_ALG_SHA2_512      9
#define IKE_MODE_AUTH_INVALID           0


/* DH Grp 5&14 support */
#define IKE_MODE_DH_GROUP_INVALID       0
#define IKE_MODE_DH_GROUP1              6
#define IKE_MODE_DH_GROUP2              7
/* DH Grp 5&14 support: Maintaining the group number for the macro */
#define IKE_MODE_DH_GROUP5              5
#define IKE_MODE_DH_GROUP14             14
/* DH Grp 5&14 support: For Future usage */
#define IKE_MODE_DH_GROUP15             15
#define IKE_MODE_DH_GROUP16             16
#define IKE_MODE_DH_GROUP17             17
#define IKE_MODE_DH_GROUP18             18

#define IKE_MODE_AUTH_PRE_SHARED        8
#define IKE_MODE_AUTH_RSA_SIG           9
#define IKE_MODE_AUTH_DSS               21
#define IKE_MODE_ENCR_ALG_AES           10
#define IKE_MODE_ENCR_AES_128           11
#define IKE_MODE_ENCR_AES_192           12
#define IKE_MODE_ENCR_AES_256           13
#define IKE_MODE_PRF_HMAC_ALG_MD5       14
#define IKE_MODE_PRF_HMAC_ALG_SHA1      15
#define IKE_MODE_AUTH_ALG_SHA1_96       16
#define IKE_MODE_AUTH_ALG_MD5_96        17

/* AES_XCBC Support */
#define IKE_MODE_PRF_AES_XCBC_128       18

/* IKEv2 */
#define IKE_MODE_EAP                    18

/* Sunil: PKI changes */
#define IKE_MODE_AUTH_PUB_KEY_ENC       19
#define IKE_MODE_AUTH_REV_PUB_KEY_ENC   20


#define IKE_MODE_VPN_SET                11

/* End : AC4D01565 */

/* Defect:AC4D06999 */
#define IKE_NAT_TRAVERSAL_ENABLE        1
#define IKE_NAT_TRAVERSAL_DISABLE       0

#define IKE_TASK_DELAY_ENABLE        1
#define IKE_TASK_DELAY_DISABLE       0
#define IKE_MAX_WARN_LEN                256

#define IKE_PUB_ISAKMP_HDR_MESSAGE_ID_LEN    4

#define IKE_PUB_ISAKMP_HDR_ICOOKIE_LEN       8
#define IKE_PUB_ISAKMP_HDR_COOKIES_LEN      (IKE_PUB_ISAKMP_HDR_ICOOKIE_LEN \
                                            + IKE_PUB_ISAKMP_HDR_ICOOKIE_LEN)

#define IKE_POLICY_NAME_MAX_LEN             128
#define IKE_MAX_IPSECPOLICY_NAME            15

#define IKE_IPSEC_ID_SIZE                    8

/*iv length*/
#define IKE_MAX_IV_LEN                       24
#define IKE_KEYDATA_SIZE                     24
/*HS:Sha2-support:Modified SKEYID Length:HERT-300*/ 
#define IKE_MAX_SKEYID_LEN                   64/*SHA2_SIZE_512*/
#define IKE_MAX_SPI_LEN                      4

#define IKE_TRPT_MESSAGES                    5

#define IKE_PEER_MULTI_SUBNET           1

/* IPSEC authentication attributes */
#define IPSEC_AH_MD5                    2
#define IPSEC_AH_SHA                    3
#define IPSEC_AH_DES                    4
#define IPSEC_AH_SHA256                 5
#define IPSEC_AH_SHA384                 6
#define IPSEC_AH_SHA512                 7
#define IPSEC_AH_AES_XCBC_96            8
#define IPSEC_AH_MAX                    8
#define IPSEC_AH_INVALID_AUTH_ALGO      0


/* IPSEC encryption attributes */
#define IPSEC_ESP_DES_IV64              1
#define IPSEC_ESP_DES                   2
#define IPSEC_ESP_3DES                  3
#define IPSEC_ESP_RC5                   4
#define IPSEC_ESP_IDEA                  5
#define IPSEC_ESP_CAST                  6
#define IPSEC_ESP_BLOWFISH              7
#define IPSEC_ESP_3IDEA                 8
#define IPSEC_ESP_DES_IV32              9
#define IPSEC_ESP_RC4                   10
#define IPSEC_ESP_NULL                  11
#define IPSEC_ESP_AES                   12
#define IPSEC_ESP_3DES_OLD              13
#define IPSEC_ESP_HARDWARE_56S          14
#define IPSEC_ESP_SKIPJACK              15

/* IPSEC authentication DOI values */
#define IPSEC_AUTH_HMAC_MD5             1
#define IPSEC_AUTH_HMAC_SHA             2
#define IPSEC_AUTH_DES_MAC              3
#define IPSEC_AUTH_KPDK                 4
#define IPSEC_AUTH_SHA_OLD              5

/*SHA2 Support*/
#define IPSEC_AUTH_HMAC_SHA256          12
#define IPSEC_AUTH_HMAC_SHA384          13
#define IPSEC_AUTH_HMAC_SHA512          14
#define IPSEC_AUTH_AES_XCBC_96          15
#define IPSEC_AUTH_HMAC_MAX             15
#define IPSEC_AUTH_HMAC_NULL            0


/* IPSEC protocol attributes */
#define IPSEC_PROTO_NONE                0
#define IPSEC_PROTO_ISAKMP              1
#define IPSEC_PROTO_IPSEC_AH            2
#define IPSEC_PROTO_IPSEC_ESP           3
#define IPSEC_PROTO_IPCOMP              4

/* Moved from ike_pub_intrnl.h */
/* Change for defect AC4D05498 */
/* Kranthi: AR-Changes */
/*Get_DefectID_FromGiri*/
#define IKE_EV_PFKEY_READ               0x40000000

/* Moved for common file changes in tcpip_ipsec.c file */
#define IKE_OK      VOS_OK
#define IKE_ERR     VOS_ERR

#define IKE_ENCRYPT_DES_CBC                 1
#define IKE_ENCRYPT_3DES_CBC                5

#define IKE_ENCRYPT_AES_CBC                 7
#define IKE_HASH_MD5                        1
#define IKE_HASH_SHA                        2

/*HS:Sha2-support*/
#define IKE_HASH_SHA2_256                   4
#define IKE_HASH_SHA2_384                   5
#define IKE_HASH_SHA2_512                   6
/* IKE_HASH_TIGER is currently un supported */
#define IKE_HASH_TIGER                      3

#define IKE_HASH_MD5_96                     3
#define IKE_HASH_SHA_96                     16/*Modified value else conflict with IKE_HASH_SHA2_256 */
/* AES_XCBC Support */
#define IKE_HASH_AES_XCBC_128              20
#define IKE_HASH_AES_XCBC_96               21
#define IKE_HASH_AES_XCBC_96_UNSET         0

/* just adjust place by limao */
/* Begin: macro for display/buildrun, do not use for cfg input */
#define IKE_AUTH_PRE_SHARED                 1
#define IKE_AUTH_DSS                        2
#define IKE_AUTH_RSA_SIG                    3
#define IKE_AUTH_RSA_ENC                    4
#define IKE_AUTH_RSA_ENC_REV                5
/* IKEv2 */
#define IKE_AUTH_EAP                        6
/* End: macro for display/buildrun */



/* Moved from IKE_type.h */
#define IKE_XAUTH_AUTH_METHOD_XAUTH_INITPRESHARED   65001
#define IKE_XAUTH_AUTH_METHOD_XAUTH_RESPPRESHARED   65002

/* IKEv1_PKI */
#define IKE_XAUTH_AUTH_METHOD_XAUTH_INITDSSSIG      65003
#define IKE_XAUTH_AUTH_METHOD_XAUTH_RESPDSSSIG      65004
#define IKE_XAUTH_AUTH_METHOD_XAUTH_INITRSASIG      65005
#define IKE_XAUTH_AUTH_METHOD_XAUTH_RESPRSASIG      65006

/*IPv6 support, max peers in tran LTE 64 peer supported*/
#define IKE_CONFIG_PEER_MIN_IPV6_TRAN_LTE           1
#define IKE_CONFIG_PEER_CUR_IPV6_TRAN_LTE           100
#define IKE_CONFIG_PEER_MAX_IPV6_TRAN_LTE           100

/*IPv6 support, max ike proposals in tran LTE, 150 proposal supported*/
#define IKE_PROPOSAL_MIN_IPV6_TRAN_LTE              1
#define IKE_PROPOSAL_CUR_IPV6_TRAN_LTE              150
#define IKE_PROPOSAL_MAX_IPV6_TRAN_LTE              150

/*IPv6 support*/
#define IKE_SA_MIN_IPV6_TRAN_LTE                    1

/*HERT-89 fix : In wireless, SA count should be set as 256 irrespective of
whether IPv6 is registered or not*/
#define IKE_SA_CUR_IPV6_TRAN_LTE                    256
#define IKE_SA_MAX_IPV6_TRAN_LTE                    256

#define IKE_AUTH_RSA_ENC_REV                5
/* IKEv2 */
#define IKE_AUTH_EAP                        6
#define IKE_MIN_EAP_TIMEOUT                 10
#define IKE_DEFAULT_EAP_TIMEOUT             60
#define IKE_MAX_EAP_TIMEOUT                 300

/* DH Grp 5&14 support */
#define IKE_GROUP_DESC_MODP_INVALID         0
#define IKE_GROUP_DESC_MODP_768             1
#define IKE_GROUP_DESC_MODP_1024            2
#define IKE_GROUP_DESC_MODP_1536            5
#define IKE_GROUP_DESC_MODP_2048           14

/* DH Grp 5&14 support: For Future usage */
#define IKE_GROUP_DESC_MODP_3072           15
#define IKE_GROUP_DESC_MODP_4096           16
#define IKE_GROUP_DESC_MODP_6114           17
#define IKE_GROUP_DESC_MODP_8192           18

#define ISAKMP_EXCH_AGGRESSIVE              4
#define IKE_EXCH_QUICK_MODE                32

#define IKE_IPSEC_SA_OUTBOUND               0
#define IKE_IPSEC_SA_INBOUND                1


/*Kuldeep : B513 Changes*/
#define IKE_SA_PH2                   2
#define IKE_SA_PH1_PH2            0


#define SA_FLAG_NONE                0x00

/* This SA is alive.  */
#define SA_FLAG_READY               0x01

/* Renegotiate the SA at each expiry.  */
#define SA_FLAG_STAYALIVE           0x02

/* This SA has been replaced by another newer one.  */
#define SA_FLAG_REPLACED            0x04

/* This SA has seen a soft timeout and wants to be renegotiated on use.  */
#define SA_FLAG_FADING              0x08

/* SA is timeout (phase1 only).  */
#define SA_FLAG_TIMEOUT             0x10

#define SA_FLAG_HEARTBEAT_READY     0x20
#define SA_FLAG_LKG_BCKUP           0x40
#define SA_FLAG_BCKD_UP             0x80

/* Added for Crash changes need to proper comment */
#define SA_FLAG_PH2_OUT_SA_LIST_INSERT     0x100
#define SA_FLAG_PH2_IN_SA_LIST_INSERT      0x200


#define SA_FLAG_MAX                 0x200

/* The key lengths in terms of bits*/
#define IKE_AES_KEYLENGTH_128       128
#define IKE_AES_KEYLENGTH_192       192
#define IKE_AES_KEYLENGTH_256       256
#define IKE_DES_KEYLENGTH           64
#define IKE_TRIPLE_DES_KEYLENGTH    192

#define IKE_DPD_ON_DEMAND               1
#define IKE_DPD_PERIODIC                2
#define IKE_DPD_ENABLE                  1
#define IKE_DPD_DISABLE                 0

/*  Default Idle Time in seconds    */
/* B505: Default DPD idle time should be 20 seconds for window size 1 */
#define IKE_DPD_DEFAULT_IDLE_TIME       30

/*  Default Retransmission Interval  */
/* S9300 - To reduce the CPU overload when other device reboots */
#define IKE_DPD_DEFAULT_RETRANS_INT     15

/*  Default Number of Retries   */
//#define IKE_DPD_DEFAULT_NO_RETRY        5
/* S9300 - To reduce the CPU overload when other device reboots */
#define IKE_DPD_DEFAULT_NO_RETRY        3

#define IKE_DPD_IDLE_TIME_ATTR_MASK     0x0001
#define IKE_DPD_RETRANS_LIMIT_ATTR_MASK 0x0010
#define IKE_DPD_RETRY_ATTR_MASK         0x0100
/* end aded */


#define IKE_DPD_MSG_HDR_HASH_NOTIFY     1
#define IKE_DPD_MSG_HDR_NOTIFY_HASH     2



#define IKE_XAUTH_ATTR_USERNAME_MINSIZE     8
#define IKE_XAUTH_ATTR_PASSWORD_MINSIZE     8
#define IKE_XAUTH_ATTR_PASSCODE_MINSIZE     8
#define IKE_XAUTH_ATTR_DOMAIN_MINSIZE       8

#define IKE_XAUTH_ATTR_USERNAME_MAXSIZE     63
#define IKE_XAUTH_ATTR_PASSWORD_MAXSIZE     31
#define IKE_XAUTH_ATTR_PASSCODE_MAXSIZE     31
#define IKE_XAUTH_ATTR_DOMAIN_MAXSIZE       63

/* XAUTH Authentication Types */
#define IKE_XAUTH_AUTHTYPE_GENERIC          0
#define IKE_XAUTH_AUTHTYPE_RADIUSCHAP       1
#define IKE_XAUTH_AUTHTYPE_OTP              2
#define IKE_XAUTH_AUTHTYPE_SKEY             3


/* XAUTH Authentication Types flag bits */
#define IKE_XAUTH_TYPE_NO_FLAG              0x00
#define IKE_XAUTH_AUTHTYPE_GENERIC_FLAG     0x01
#define IKE_XAUTH_AUTHTYPE_RADIUSCHAP_FLAG  0x02
#define IKE_XAUTH_AUTHTYPE_OTP_FLAG         0x04
#define IKE_XAUTH_AUTHTYPE_SKEY_FLAG        0x08

/* XAUTH Modes */
#define IKE_XAUTH_DISABLE       0
#define IKE_XAUTH_MODE_STATIC   1
#define IKE_XAUTH_MODE_DYNAMIC  2

/*Referrenced by API IKE_SetRChapHashSeq*/
#define IKE_XAUTH_RCHAP_ID_CHLNG_SCRT   1
#define IKE_XAUTH_RCHAP_ID_SCRT_CHLNG   2

/*Referenced by API  IKE_GetOTPPswdMode */
#define IKE_XAUTH_HEX_MODE              0
#define IKE_XAUTH_ENCODED_MODE          1

/* Flags for XAUTH Attributes */
#define IKE_XAUTH_ATTR_TYPE_FLAG            0x0001
#define IKE_XAUTH_ATTR_USERNAME_FLAG        0x0002
#define IKE_XAUTH_ATTR_PASSWORD_FLAG        0x0004
#define IKE_XAUTH_ATTR_PASSCODE_FLAG        0x0008
#define IKE_XAUTH_ATTR_MESSAGE_FLAG         0x0010
#define IKE_XAUTH_ATTR_CHALLENGE_FLAG       0x0020
#define IKE_XAUTH_ATTR_DOMAIN_FLAG          0x0040
#define IKE_XAUTH_ATTR_STATUS_FLAG          0x0080

/* Used in IKE_STATISTICS_S */
#define IKE_STATS_ISAKMP_NOTIFY_MAX         31

/* Size of ID|COOKIES|PEER_NAME to be passed to the product when requesting
XAUTH attributes */
#define IKE_XAUTH_ID_SIZE       2
#define IKE_XAUTH_ID_COOKIE_SIZE    \
                    (IKE_XAUTH_ID_SIZE + IKE_PUB_ISAKMP_HDR_COOKIES_LEN)


#define IKE_MAX_APPLICATION 10

#define IKE_APPLICATION_IPSEC (IKE_MAX_APPLICATION + 1)

#define IKE_MODECFG_APPSTART 1

/* Max Group Name length */
#define IKE_GROUP_NAME_MIN_LEN          1
#define IKE_GROUP_NAME_MAX_LEN          64


/* Represents the MODE-CFG configuration status */
#define IKE_MODECFG_ENABLE              1
#define IKE_MODECFG_DISABLE             0


/* Flags indicating the attribute types in the IKE_PRODUCT_NOTIFY_S structure */
#define IKE_CFG_ATTR_ADDR      0x00000001
#define IKE_CFG_ATTR_MASK      0x00000002
#define IKE_CFG_ATTR_NBNS      0x00000004
#define IKE_CFG_ATTR_DNS       0x00000008
#define IKE_CFG_ATTR_DHCP      0x00000010
#define IKE_CFG_ATTR_SUBNET    0x00000020
#define IKE_CFG_ATTR_ADDR_EXP  0x00000040
#define IKE_CFG_ATTR_APP_VER   0x00000080
#define IKE_CFG_ATTR_SUPPORTED 0x00000100

//#if (IKE_YES == IKE_MODECFG_PUBADDR)
#define IKE_CFG_ATTR_ADDR_PUBLIC 0x00000200  /* Modem outer ip address */
//#endif

/*GGSN*/
/*
    Sandeep kampati(s72459)
    for IKE ModeCFG & Product AAA interaction
*/
#define IKE_CFG_AAA_IP4_ADDRESS             0x00000001
#define IKE_CFG_AAA_IP4_NETMASK             0x00000002
#define IKE_CFG_AAA_IP4_DNS                 0x00000004
#define IKE_CFG_AAA_IP4_NBNS                0x00000008
#define IKE_CFG_AAA_ADDRESS_EXPIRY          0x00000010
#define IKE_CFG_AAA_IP4_DHCP                0x00000020
#define IKE_CFG_AAA_APPLICATION_VERSION     0x00000040
#define IKE_CFG_AAA_IP6_ADDRESS             0x00000080
#define IKE_CFG_AAA_IP6_DNS                 0x00000100
#define IKE_CFG_AAA_IP6_NBNS                0x00000200
#define IKE_CFG_AAA_IP6_DHCP                0x00000400
#define IKE_CFG_AAA_IP4_SUBNET              0x00000800
#define IKE_CFG_AAA_SUPPORTED_ATTRIBUTES    0x00001000
#define IKE_CFG_AAA_IP6_SUBNET              0x00002000
#define IKE_CFG_AAA_MAX                     0x00002000



/* Notification type value as per RFC */
#define ISAKMP_NOTIFY_INVALID_PAYLOAD_TYPE          1 /* Used to define Notification type as Invalid */
#define ISAKMP_NOTIFY_DOI_NOT_SUPPORTED             2 /* Used to define Notification type as DOI not Supported */
#define ISAKMP_NOTIFY_SITUATION_NOT_SUPPORTED       3 /* Used to define Notification type as Situation not supported */
#define ISAKMP_NOTIFY_INVALID_COOKIE                4 /* Used to define Notification type as Invalid cookie */
#define ISAKMP_NOTIFY_INVALID_MAJOR_VERSION         5 /* Used to define Notification type as Invalid Major version*/
#define ISAKMP_NOTIFY_INVALID_MINOR_VERSION         6 /* Used to define Notification type as Invalid Minor version*/
#define ISAKMP_NOTIFY_INVALID_EXCHANGE_TYPE         7 /* Used to define Notification type as Invalid Exchange type */
#define ISAKMP_NOTIFY_INVALID_FLAGS                 8 /* Used to define Notification type as Invalid Flags*/
#define ISAKMP_NOTIFY_INVALID_MESSAGE_ID            9 /* Used to define Notification type as Invalid Message ID */
#define ISAKMP_NOTIFY_INVALID_PROTOCOL_ID           10 /* Used to define Notification type as Invalid Protocol ID */
#define ISAKMP_NOTIFY_INVALID_SPI                   11 /* Used to define Notification type as Invalid SPI*/
#define ISAKMP_NOTIFY_INVALID_TRANSFORM_ID          12 /* Used to define Notification type as Invalid Transform ID*/
#define ISAKMP_NOTIFY_ATTRIBUTES_NOT_SUPPORTED      13 /* Used to define Notification type as Attribute not supported */
#define ISAKMP_NOTIFY_NO_PROPOSAL_CHOSEN            14 /* Used to define Notification type as No proposal choosen */
#define ISAKMP_NOTIFY_BAD_PROPOSAL_SYNTAX           15 /* Used to define Notification type as Bad Proposal syntax */
#define ISAKMP_NOTIFY_PAYLOAD_MALFORMED             16 /* Used to define Notification type as Payload malformed */
#define ISAKMP_NOTIFY_INVALID_KEY_INFORMATION       17 /* Used to define Notification type as Invalid Key Information */
#define ISAKMP_NOTIFY_INVALID_ID_INFORMATION        18 /* Used to define Notification type as Invalid ID Information*/
#define ISAKMP_NOTIFY_INVALID_CERT_ENCODING         19 /* Used to define Notification type as Invalid Certificate encoding */
#define ISAKMP_NOTIFY_INVALID_CERTIFICATE           20 /* Used to define Notification type as Invalid Certificate*/
#define ISAKMP_NOTIFY_CERT_TYPE_UNSUPPORTED         21 /* Used to define Notification type as Certificate type unsupported */
#define ISAKMP_NOTIFY_INVALID_CERT_AUTHORITY        22 /* Used to define Notification type as Invalid certificate  */
#define ISAKMP_NOTIFY_INVALID_HASH_INFORMATION      23 /* Used to define Notification type as Invalid Hash Information*/
#define ISAKMP_NOTIFY_AUTHENTICATION_FAILED         24 /* Used to define Notification type as Authentication failed */
#define ISAKMP_NOTIFY_INVALID_SIGNATURE             25 /* Used to define Notification type as Invalid Signature*/
#define ISAKMP_NOTIFY_ADDRESS_NOTIFICATION          26 /* Used to define Notification type as Address notify */
#define ISAKMP_NOTIFY_NOTIFY_SA_LIFETIME            27 /* Used to define Notification type as SA lifetime */
#define ISAKMP_NOTIFY_CERTIFICATE_UNAVAILABLE       28 /* Used to define Notification type as Certificate Unavailable */
#define ISAKMP_NOTIFY_UNSUPPORTED_EXCHANGE_TYPE     29 /* Used to define Notification type as unsupported exchange type */
#define ISAKMP_NOTIFY_UNEQUAL_PAYLOAD_LENGTHS       30 /* Used to define Notification type as unequal payload length */
#define ISAKMP_NOTIFY_RESERVED_MIN                  31 /* Used to define Notification type as Reserved Min */
#define ISAKMP_NOTIFY_RESERVED_MAX                  8191 /* Used to define Notification type as Reserved Max */
#define ISAKMP_NOTIFY_PRIVATE_MIN                   8192 /* Used to define Notification type as Priviate Min */
#define ISAKMP_NOTIFY_PRIVATE_MAX                   16383 /* Used to define Notification type as Priviate Max */
#define ISAKMP_NOTIFY_STATUS_CONNECTED              16384 /* Used to define Notification type as Status Connected */
#define ISAKMP_NOTIFY_STATUS_RESERVED1_MIN          16385 /* Used to define Notification type as Status Connected Reserved Min */
#define ISAKMP_NOTIFY_STATUS_RESERVED1_MAX          24575 /* Used to define Notification type as Status Connected Reserved Max */
#define ISAKMP_NOTIFY_STATUS_DOI_MIN                12576 /* Used to define Notification type as Status DOI Min */
#define ISAKMP_NOTIFY_STATUS_DOI_MAX                32767 /* Used to define Notification type as Status DOI Max */
#define ISAKMP_NOTIFY_STATUS_PRIVATE_MIN            32768 /* Used to define Notification type as Staus Priviate Min */
#define ISAKMP_NOTIFY_STATUS_PRIVATE_MAX            40959 /* Used to define Notification type as Status Priviate MAx */
#define ISAKMP_NOTIFY_STATUS_RESERVED2_MIN          40960 /* Used to define Notification type as Status Reserved2 Min */
#define ISAKMP_NOTIFY_STATUS_RESERVED2_MAX          65535 /* Used to define Notification type as Status Reserved2 Max */

/* DPD notification message types */
#define ISAKMP_NOTIFY_RU_THERE                      36136
#define ISAKMP_NOTIFY_RU_THERE_ACK                  36137


/* To control sending of VID information to peer to get conmfiguration
   attributes */
#define IKE_CFG_NO_VID                  0
#define IKE_CFG_SEND_VID                1

/* sunil: PKI changes */
/* Added for EasyVPN */
#define IKE_TRUST_NAME_MIN_LEN          1
#define IKE_TRUST_NAME_MAX_LEN          256

/* PKI Flags to Set, Reset in Peer */
#define IKE_CFG_PKI_CRL          0x00000001
#define IKE_CFG_URL_ONLY         0x00000002
#define IKE_CFG_URL_HTTP         0x00000004
#define IKE_PKI_ID_VALIDATE      0x00000008
#define IKE_PKI_USE_DFLT_CERT    0x00000010
#define IKE_CFG_PKI_ARL          0x00000020
#define IKE_CFG_PKI_OCSP         0x00000040

#define IKE_INITIATOR                    1

#define IKE_RESPONDER                    0

#define IKE_TIME_TO_START_REAUTH_REKEY_WITHOUT_ERR    60

/*Interface state Notification*/
#define IKE_IPSEC_INTF_UP                   1
#define IKE_IPSEC_INTF_DOWN                 0

/* Re-authentication interval */
#define IKE_POLICY_REAUTH_INTERVAL_MIN      g_ulReauthMinInterval
#define IKE_POLICY_REAUTH_INTERVAL_MAX      604800
#define IKE_POLICY_DEFAULT_REAUTH_INTERVAL  0

#define IKE_OP_ENABLE                       1
#define IKE_OP_DISABLE                      0

/* Multi-SeGw Feature */
#define IKE_NORMAL_PEER                     0
#define IKE_MASTER_PEER                     1
#define IKE_SLAVE_PEER                      2

#define MAX_BACKUP_PEERS                    7

/*B102 smoke changes*/
typedef enum Debug_classes
{
    IKE_DEBUG_MISC = 0,
    IKE_DEBUG_TRANSPORT,                    /* 1 */
    IKE_DEBUG_MESSAGE,                      /* 2 */
    IKE_DEBUG_EXCHANGE,                     /* 3 */
    IKE_DEBUG_CRYPTO,                       /* 4 */
    IKE_DEBUG_TIMER_ALL,                    /* 5 */
    IKE_DEBUG_SYSDEP,                       /* 6 */
    IKE_DEBUG_ERROR,                        /* 7 */
    IKE_DEBUG_SA,                           /* 8 */
    IKE_DEBUG_HSB,                          /* 9 */
    IKE_DEBUG_PCKT,                         /* 10 */
    IKE_DEBUG_EXT_EVENT,                    /* 11 */
    IKE_DEBUG_TIMER_HEARTBEAT,              /* 12 */
    IKE_DEBUG_TIMER_NAT_KEEPALIVE,          /* 13 */
    IKE_DEBUG_TIMER_HEARTBEAT_TIMEOUT,      /* 14 */
    IKE_DEBUG_TIMER_MESSAGE_RETRANS,        /* 15 */
    IKE_DEBUG_TIMER_EXCHANGE,               /* 16 */
    IKE_DEBUG_TIMER_SA_SOFT,                /* 17 */
    IKE_DEBUG_TIMER_SA_HARD,                /* 18 */
    IKE_DEBUG_TASK,                         /* 19 */
    IKE_DEBUG_MODECFG,                      /* 20 */
    IKE_DEBUG_DPD,                          /* 21 */
    IKE_DEBUG_XAUTH,                        /* 22 */

    /* IKEv2 */
    IKEV2_DEBUG_MESSAGE,                    /* 23 */
    IKEV2_DEBUG_STATE_MACHINE,              /* 24 */
    IKEV2_DEBUG_KEYGEN,                     /* 25 */
    IKEV2_DEBUG_ERROR,                      /* 26 */
    IKEV2_DEBUG_SA,                         /* 27 */
    IKEV2_DEBUG_PCKT,                       /* 28 */
    IKEV2_DEBUG_EXT_EVENT,                  /* 29 */
    IKEV2_DEBUG_EAP,                        /* 30 */
    IKEV2_DEBUG_SADELETE,                   /* 31 */
    IKEV2_DEBUG_TIMER_MESSAGE_RETRANS,      /* 32 */
    IKEV2_DEBUG_TIMER,                      /* 33 */
    IKEV2_DEBUG_TIMER_SA_SOFT,              /* 34 */
    IKEV2_DEBUG_TIMER_SA_HARD,              /* 35 */
    IKEV2_DEBUG_TIMER_SOFT_REAUTH,          /* 36 */
    IKEV2_DEBUG_TIMER_HARD_REAUTH,          /* 37 */
    IKEV2_DEBUG_TIMER_ALL,                  /* 38 */
    IKEV2_DEBUG_MODECFG,                    /* 39 */
    IKEV2_DEBUG_ALL,                        /* 40 */
    IKE_DEBUG_ALL,                          /* 41 */
    IKEV2_DEBUG_PKI,                        /* 42 */
    IKEV1_DEBUG_PKI,                        /* 43 */
    IKECMN_DEBUG_PKI,                       /* 44 */
    IKE_DEBUG_SH_PKI,                       /* 45 */
    IKECMN_DEBUG_OCSP,                      /* 46 */
    IKE_DEBUG_NONE,
    IKE_DEBUG_ENDCLASS,
    IKE_MAX_DEBUG_SW_ENUM_VALUE = 0x7FFFFFFF       /* For 4 byte alignment */
}IKE_DEBUG_SWITCH_E;

/************************************************************************
 * ike_cfg.c help information's index:
 ************************************************************************/
typedef enum enumIKEInf
{
    /*-----------------------------------------------------------------------*/
    /* debug IKE ......    should keep the order with enum log_classes       */
    /*-----------------------------------------------------------------------*/
    Help_IKE_Misc_Debug_On = 2,
    Help_IKE_Transport_Debug_On,
    Help_IKE_Message_Debug_On,
    Help_IKE_Exchange_Debug_On,
    Help_IKE_Crypto_Debug_On,
    Help_IKE_Timer_Debug_On,
    Help_IKE_Sysdep_Debug_On,
    Help_IKE_Error_Debug_On,
    HELP_IKE_SA_DEBUG_ON,
    HELP_IKE_HSB_DEBUG_ON,
    HELP_IKE_PCKT_DEBUG_ON,
    HELP_IKE_EVENT_DEBUG_ON,                /* 13 */

    HELP_IKE_TIMER_HEARTBEAT_ON,
    HELP_IKE_TIMER_NAT_KEEPALIVE_ON,
    HELP_IKE_TIMER_HEARTBEAT_TIMEOUT_ON,
    HELP_IKE_TIMER_MESSAGE_RETRANS_ON,
    HELP_IKE_TIMER_EXCHANGE_ON,
    HELP_IKE_TIMER_SA_SOFT_ON,
    HELP_IKE_TIMER_SA_HARD_ON,              /* 20 */

    /*-----------------------------------------------------------------------*/
    /* show crypto ike policy                                                */
    /*-----------------------------------------------------------------------*/
    Help_Show_IKE_Policy_Default_Header,
    Help_Show_IKE_Policy_Header,
    Help_Show_IKE_Policy_EncAlg,
    Help_Show_IKE_Policy_Hash,
    Help_Show_IKE_Policy_Auth,
    Help_Show_IKE_Policy_Group,
    Help_Show_IKE_Policy_LifeTime,          /* 27 */

    /*-----------------------------------------------------------------------*/
    /* display ike proposal                                                  */
    /*-----------------------------------------------------------------------*/
    Help_Display_IKE_Policy_Header,
    Help_Display_IKE_Policy_Priority_Default, /* 29 */

    /*-----------------------------------------------------------------------*/
    /* display ike proposal                                                  */
    /*-----------------------------------------------------------------------*/
    Help_Display_IKE_Peer_Header,

    /*-----------------------------------------------------------------------*/
    /* show crypto ike sa ; clear crypto ike sa                              */
    /*-----------------------------------------------------------------------*/
    Help_Show_IKE_SA,
    Help_Show_IKE_Event,
    Help_Show_IKE_SA_Flag,

    /* AC4D01569, Commented for error code sync */
    /* Err_Show_IKE_SA_NotFound, */
    Err_Show_IKE_SA_Invalid,                /* 34 */

    /*-----------------------------------------------------------------------*/
    /* crypto ike peer                                                       */
    /*-----------------------------------------------------------------------*/
    Err_CryptoIKEPeer_NoPeer,
    Err_CryptoIKEPeer_Invalid,
    Err_CryptoIKEPeer_Exist,
    Err_CryptoIKEPeer_IdType,
    Err_CryptoIKEPeer_Name,                 /* 39 */

    /*-----------------------------------------------------------------------*/
    /* crypto ike key                                                        */
    /*-----------------------------------------------------------------------*/
    Err_CryptoIKEKey_NoKey,
    Err_CryptoIKEKey_Invalid,
    Err_CryptoIKEKey_Exist,                 /* 42 */

    /*-----------------------------------------------------------------------*/
    /* crypto ike key                                                        */
    /*-----------------------------------------------------------------------*/
    Err_CryptoIKEPolicy_NoPolicy,
    Err_CryptoIKEPolicy_WrongNumber,         /* 44 */

    /*Ikev2-ByteAlignment*/
    Err_Max = 0x7FFFFFFF                    /* For 4 byte alignment */
}IKE_INFO;



/* IKE Error information */
typedef enum enumIKEErr
{
    IKE_ERR_NO_SA = Err_CryptoIKEPolicy_WrongNumber + 1, /* 45 */
    IKE_ERR_INVALID_PARA, /*"\r\nInvalid Peer parameter"*/
    IKE_ERR_INVALID_INPUT,
    IKE_ERR_INVALID_EXCHANGE_MODE, /*"\r\nInvalid Exchange mode"*/
    IKE_ERR_NO_PROPOSAL, /*"\r\nIKE Proposal does not exist"*/
    IKE_ERR_NO_ENOUGH_MEMORY, /*"\r\nInsufficient memory"*/ /* 50 */
    IKE_ERR_PROPOSAL_ALREADY_EXIST,
    IKE_ERR_PROPOSAL_MAX,
    IKE_ERR_NO_PROPOSAL_PENDING,
    IKE_ERR_NOT_SUPPORTED,
    IKE_ERR_NO_PEER, /*"\r\nIKE Peer does not exist"*/ /* 55 */
    IKE_ERR_PEER_EXIST,
    IKE_ERR_PEER_MAX,   /* "\r\nIKE Peer exceeding maximun value" */
    IKE_ERR_PEER_IN_USE, /*"\r\nIKE Peer in use"*/
    IKE_ERR_NO_PEER_PENDING,
    IKE_ERR_NOT_SUPPORTED_FOR_MAIN_MODE,        /* 60 */
    IKE_ERR_EXCEEDING_LIMIT,
    IKE_ERR_PEER_REMOTEADDR_CONFLICT, /*"\r\nIKE Peer remote address conflict"*/
    IKE_ERR_PEER_REMOTENAME_CONFLICT, /*"\r\nIKE Peer remote name conflict"*/
    IKE_ERR_NO_VPN,
    IKE_ERR_IP_ADDR_INVALID,                    /* 65 */
    IKE_ERR_IPSEC_VPN_NOT_SET_VRF, /*"\r\nVPN vrf index not set"*/
    IKE_ERR_IPSEC_NO_VPN_INSTANCE, /*"\r\nVPN vrf index not set"*/
    IKE_ERR_GET_RECORD_NUM_REDUCED,
    IKE_ERR_NO_PROPOSAL_TO_REGISTER_WAITLIST,
    IKE_ERR_WAITLIST_REGISTER_FAILED,           /* 70 */
    IKE_ERR_WAITLIST_IS_INVALID,
    IKE_ERR_WAITLIST_UNREG_FAILED,
    IKE_ERR_WAITLIST_GET_FAILED,
    IKE_ERR_WAITLIST_GETNXT_FAILED,
    IKE_ERR_NO_PEERS_TO_REGISTER_WAITLIST,      /* 75 */
    IKE_ERR_NO_SA_TO_REGISTER_WAITLIST,
    IKE_ERR_NO_EXCHANGE_TO_REGISTER_WAITLIST,
    IKE_ERR_NO_MESSAGE_TO_REGISTER_WAITLIST,
    IKE_ERR_NO_EVENT_TO_REGISTER_WAITLIST,
    IKE_ERR_NO_TRANSPORT_TO_REGISTER_WAITLIST,  /* 80 */
    IKE_ERR_NO_SA_BUNDLE,
    IKE_ERR_NO_SA_PENDING,
    IKE_ERR_NO_EXCHANGE_PENDING,
    IKE_ERR_NO_MESSAGE_PENDING,
    IKE_ERR_NO_EVENT_PENDING,                   /* 85 */
    IKE_ERR_NO_TRANSPORT_PENDING,
    IKE_ERR_PROPOSAL_PENDING,
    IKE_ERR_PEER_PENDING,
    IKE_ERR_SA_PENDING,
    IKE_ERR_EXCHANGE_PENDING,                   /* 90 */
    IKE_ERR_MESSAGE_PENDING,
    IKE_ERR_EVENT_PENDING,
    IKE_ERR_TRANSPORT_PENDING,
    IKE_ERR_TIMER,
    IKE_ERR_NO_LOCAL_ID,                        /* 95 */
    IKE_ERR_PROP_IN_USE,
    IKE_ERR_MEMORY_SHORTAGE,
    IKE_ERR_INVALID_IP_ADDRESS,
    IKE_ERR_HARDWARE_NOT_SUPPORTED,
    IKE_ERR_NAT_NOT_SUPPORTED_FOR_MAIN_MODE,    /* 100 */
    IKE_ERR_UPDATE_IPSEC_FAILED,
    IKE_ERR_PEER_IN_USE_SA,
    IKE_ERR_WAITLIST_SET_FAILED,
    IKE_ERR_SET_KEEPALIVE_INTV_FAILED,
    IKE_ERR_SET_KEEPALIVE_TIMEOUT_FAILED,       /* 105 */
    IKE_ERR_SET_NAT_KEEPALIVE_INTV_FAILED,
    IKE_ERR_VPN_NOT_BINDED,
    HELP_IKE_TASK_DEBUG_ON,
    HELP_IKE_MODECFG_DEBUG_ON,
    HELP_IKE_DPD_DEBUG_ON,
    HELP_IKE_XAUTH_DEBUG_ON,
    IKE_ERR_SEM_ACCESS,
    IKE_ERR_UNDO_NAT_TRAVERSAL,                 /* 113 */
    IKE_ERR_FREE_POOL_EMPTY,
    IKE_ERR_NO_REMOTE_ADDRESS,
    IKE_ERR_DUP_REQ,
    IKE_ERR_XAUTH_NOT_SUPPORTED_FOR_MAIN_MODE,
    IKE_ERR_EXCHANGE_NOT_FOUND,                 /* 118 */
    IKE_ERR_XAUTH_REPLY_FORMATION_FAILED,
    IKE_ERR_MODECFG_NOTIFY_IPSEC_FAIL,
    IKE_ERR_PAF_LIMIT_REACHED,
    IKE_ERR_MODECFG_DISABLED,
    IKE_ERR_APP_NOT_REGISTERED,                 /* 123 */
    IKE_ERR_EVENT_WRITE_FAIL,
    IKE_ERR_QUEUE_WRITE_FAIL,
    IKE_ERR_NO_MDCFGADDRESS,
    IKE_ERR_SEM_CREATE,
    IKE_ERR_MAX_APP_REGISTERED,                 /* 128 */
    IKE_ERR_EXCH_TIMEDOUT,
    IKE_ERR_SA_CREATION_FAILED,
    IKE_ERR_MAX_REQUEST_PENDING,
    IKE_ERR_EMPTYMODECFG_REPLY,
    IKE_ERR_EXCH_CREATION_FAILED,
    IKE_ERR_RDXADD_FAIL,                        /* 134 */

    /*  Defect ID:AC4D05485 */
    IKE_ERR_MAIN_MODE_NOT_SUPPORTED_FOR_MODECFG,
    IKE_ERR_MAIN_MODE_NOT_SUPPORTED_FOR_XAUTH,
    IKE_ERR_MAIN_MODE_NOT_SUPPORTED_WITH_KEYID, /* 137 */


    /*  End Defect ID:AC4D05485 */
    HELP_IKEV2_DEBUG_MESSAGE_ON,                /* Message handling debugs */
    HELP_IKEV2_DEBUG_STATE_MACHINE_ON,          /* State machine debugs */
    HELP_IKEV2_DEBUG_KEYGEN_ON,                 /* Key generation debugs */
    HELP_IKEV2_DEBUG_ERROR_ON,                  /* All the error cases */
    HELP_IKEV2_DEBUG_SA_ON,                     /* SA management debugs */
    HELP_IKEV2_DEBUG_PCKT_ON,                   /* IKEv2 packet debugs */
    HELP_IKEV2_DEBUG_EXT_EVENT_ON,              /* External events */
    HELP_IKEV2_DEBUG_EAP_ON,                    /* EAP auth debugs */
    HELP_IKEV2_DEBUG_SADELETE_ON,               /* SA DELETE debugs */
    HELP_IKEV2_DEBUG_TIMER_MESSAGE_RETRANS_ON,  /* Msg retransmission */
    HELP_IKEV2_DEBUG_TIMER_ON,                  /* Exchange timer */
    HELP_IKEV2_DEBUG_TIMER_SA_SOFT_ON,          /* Soft expiry timer */
    HELP_IKEV2_DEBUG_TIMER_SA_HARD_ON,          /* Hard expiry timer */
    HELP_IKEV2_DEBUG_TIMER_SOFT_REAUTH_ON,      /* Re-auth soft timer */
    HELP_IKEV2_DEBUG_TIMER_HARD_REAUTH_ON,      /* Re-auth hard timer */
    IKE_ERR_OPERATION_DONE,
    HELP_IKEV2_DEBUG_MODECFG_ON,                /* Mode-Cfg */
    IKE_ERR_SOCKT_NOT_INITIALIZED,              /* IKE socket not yet init */ /* 155 */

    /*B500 - SGSN-CMD Registration*/
    IKE_ERR_IKEV1_COMP_NOTAVAILABLE,
    IKE_ERR_IKEV2_COMP_NOTAVAILABLE,
    IKE_ERR_INVALID_VERSION,
    IKE_ERR_EXCH_MODE_NOT_SUPPORTED,
    IKE_ERR_INVALID_PARA_EXCH_MODE,
    IKE_ERR_INVALID_PARA_LOCAL_ID_TYPE,
    IKE_ERR_INVALID_PARA_PROPOSAL_NUM,
    IKE_ERR_INVALID_PARA_PRESHARED_KEY,
    IKE_ERR_INVALID_PARA_REMOTENAME,
    IKE_ERR_INVALID_PARA_NAT_MODE,
    IKE_ERR_INVALID_PARA_GROUPNAME,
    IKE_ERR_INVALID_PARA_MODECFG_MODE,
    IKE_ERR_INVALID_PARA_VPN_NAME,
    IKE_ERR_INVALID_PARA_PEER_START_REMOTE_ADDR,
    IKE_ERR_INVALID_PARA_PEER_END_REMOTE_ADDR,
    IKE_ERR_INVALID_PARA_PEER_ID_TYPE,
    IKE_ERR_INVALID_PARA_DPD_MODE,
    IKE_ERR_INVALID_PARA_DPD_IDLETIME,
    IKE_ERR_INVALID_PARA_DPD_RETRANSMIT,
    IKE_ERR_INVALID_PARA_DPD_RETRY,
    IKE_ERR_INVALID_PARA_DPD_HASHSEQ,
    IKE_ERR_INVALID_PARA_DPD_ATTRFLAG,  /* 177 */
    IKE_EVENT_WRITE_SUCCESS,                    /* IKEv1_SYNC_Delete */
    IKE_ERR_IPSEC_POLICY_EXIST,

    /* Anoop_PKI PKI related errors   */
    IKE_ERR_OBJECT_NOT_CONFIGURED,     /* 180 */
    IKE_ERR_PROCESS_ASYNC,
    IKE_ERR_PROCESS_SYNC,
    IKE_ERR_NOSA_FOR_CONNID,
    IKE_ERR_NOAUTH_EXCH_FOR_SA,
    IKE_ERR_TRUSTPOINT_NOT_CONFIGURED,  /* 185 */
    IKE_ERR_OBJECT_EXIST,
    IKE_ERR_INVALID_OBJECT_NAME,
    IKE_ERR_GETOBJECTAPI_NOTREGISTERED,
    IKE_ERR_OBJECT_IN_USE,
    IKE_ERR_OBJECT_NOT_USED,
    IKE_ERR_PKI_NOT_SUPPORTED,

    /*AP : Allowing duplicate remote name in different peers*/
    IKE_ALLOW_DUPLICATE_REMOTE_NAME,        /*192*/
    IKE_DENY_DUPLICATE_REMOTE_NAME,

    /*Kuldeep : B513 Changes*/

    /*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
    IKE_ERR_INVALID_PHASE,
    IKE_ERR_INVALID_NOTIFY_PARA,
    IKE_ERR_INVALID_VRF_NAME_LENGTH,
    IKE_ERR_NULL_POINTER,
    IKE_ERR_NO_ESTABLISHED_STATE_SA_FOUND,
    IKE_ERR_FADING_STATE_SA_FOUND,
    IKE_ERR_HALFOPEN_SA_FOUND,          /*200*/
    IKE_ERR_MORE_THAN_ONE_ESTB_SA_FOUND,
    IKE_ERR_NOT_ORIGINAL_INITIATOR,
    IKE_ERR_REAUTH_SCHEDULED_WITHIN_DEFAULT_TIME,
    IKE_ERR_REKEY_SCHEDULED_WITHIN_DEFAULT_TIME,
    IKE_ERR_NO_CHILD_SA_FOR_REAUTH,
    IKE_ERR_ADDRESS_IS_INVALID,
    IKE_ERR_INVALID_INTERFACENAME, /*ITERATIN-3 IPV6 compatibility modification*/
    IKE_ERR_OPER_ON_V4,         /*Invalid operation setting V6 address on V4 peer*/
    IKE_ERR_OPER_ON_V6,         /*Invalid operation setting V4 address on V6 peer*/
    IKE_ERR_OPER_ONV4_NAT,      /*Invalid operation setting V6 NAT on V4 peer*/
    IKE_ERR_OPER_ONV6_NAT,      /*Invalid operation setting V4 NAT on V6 peer*/

    IKE_ERR_VPN_NOT_SUPPORTED,   /*VPN not supported for IPv6*/
    IKE_ERR_ADDR_CONFLICT,       /*Local addr conflict Peer addr*/
    IKE_ERR_IKE6REGISTER_FAILED,
    IKE_ERR_IPSEC6REGISTER_FAILED,      /*215*/

    /*GGSN*/
    IKE_ERR_VALIDATE_ID,
    IKE_ERR_BYPASS_IDVALIDATION,
    IKE_ERR_NO_EXCH_BY_MSGID,
    IKE_ERR_REMOTENAME_NOT_CONFIGURED,
    IKE_ERR_AUTHDOMAIN_ALREADYCONFIGURED,/*220*/
    IKE_ERR_FEATUREACTIVATION_APINOT_REGISTERED,
    IKE_ERR_PROFILE_ID_EXIST,
    IKE_ERR_AH_AUTH_NULL,               /* Auth algo is NULL for AH */
    IKE_ERR_ESP_AUTH_ENCR_NULL,         /* Both Auth and Encr algo is NULL for ESP */
    IKE_ERR_CONFIG_PEER_MAX,            /*225*/
    IKE_ERR_PROF_PEER_MAX,
    IKE_ERR_FEATURE_NOT_REGISTERED,     /* The corrosponding callback is not registered */
    IKE_ERR_INVALID_IF,                 /*228*/
    IKE_ERR_FQDN_RESL_IN_PROGRESS,      /* FQDN Resolution is in progress */
    IKE_ERR_DUPLICATE_FQDN,             /* Same FQDN is configured in another peer */
    IKE_ERR_PEER_ADDR_NOT_USER_CONFIG,  /* Trying to undo remote IP which is not user configured (FQDN) */
    IKE_ERR_PEER_FQDN_NOT_USER_CONFIG,  /* Trying to undo FQDN which is not user configured (FQDN) */
    IKE_ERR_UNDO_FQDN_FIRST,            /* User cannot set remote address unless FQDN config is removed */
    IKE_ERR_UNDO_IP_FIRST,              /* User cannot set FQDN unless remote address config is removed */
    IKE_ERR_GET_OCSPREQ_FAIL,           /*235*/
    IKE_ERR_PEER_AUTHDOMAIN_MISMATCH,   /*236 Authdomain received from product is not matched*/
    IKE_ERR_NOPOLICY_ON_INTFACE,        /*237 Signifies policy is not applied on iterface */
    IKE_ERR_AUTH_ALGO_NOT_SUPPORTED_IKEV1_PEER,/*238 Signifies policy is not applied on iterface */
    IKE_ERR_EASYVPN_PEER_ADDR_CONFLICT, /* 239 */
    IKE_ERR_EASYVPN_FQDN_CONFLICT,      /* 240 */
    IKE_ERR_IPSEC6_NO_LIB,              /* 241 */
    IKE_ERR_POSTSEND,                   /* 242 */
    IKE_ERR_INVALID_PROPOSAL,           /* 243 */
    IKE_ERR_PEER_TYPE_MISMATCH,         /* 244 */
    IKE_ERR_MAX_BACKUP_PEERS_REACHED,   /* 245 */
    IKE_ERR_NOT_A_MASTER_PEER,          /* 246 */
    IKE_ERR_REAUTH_PROGRESS,            /* 247 */
    IKE_ERR_MAX,
    IKE_MAX_ERR_ENUM_VALUE = 0x7FFFFFFF       /* For 4 byte alignment */
}IKE_ERR_TYPE_E;


/* Mode-CFG operation mode */
typedef enum enumIKE_MODECFG_OPMODE
{
    IKE_OPMODE_SYNC = 1, /* Sync mode of operation */
    IKE_OPMODE_ASYNC, /* Async mode of operation */
    IKE_OPMODE_ADDR_RENEGOTIATE, /* Address re-negotiation */
    IKE_OPMODE_NOLIFETIME_ADDR_RENEGOTIATE, /* No lifetime address re-key */
    IKE_MODECFG_MAX_OPMODE_ENUM,
    IKE_CFG_OPMODE_ENUM_VALUE_MAX_ULONG = 0x7FFFFFFF /* For 4 byte alignment */
}IKE_MODECFG_OPMODE_E;


/* The enum defines the notification type from and to the application */
typedef enum enumIKE_CFG_ATTRMSG_OPTYPE_E
{
    IKE_CFG_NO_ATTR_INFO = 0,/* Indicates attributes in reply already notified*/
    IKE_CFG_ATTR_REQ,
    IKE_CFG_ATTR_NOTIFY,
    IKE_CFG_ATTR_DEL,
    IKE_CFG_ATTR_SOFT_EXPIRE,
    IKE_CFG_ATTR_TRIGGER,
    IKE_CFG_ATTR_MAX_ENUM_VALUE,
    IKE_MAX_CFG_ATTR_ENUM_VALUE = 0x7FFFFFFF       /* For 4 byte alignment */
}IKE_CFG_ATTRMSG_OPTYPE_E;


typedef enum tagIKE_VERSION
{
    IKE_V1_ONLY = 1,
    IKE_V2_ONLY,
    IKE_V1_INITIATOR,
    IKE_V2_INITIATOR,
    IKE_VERSION_MAX,
    IKE_MAX_VERSION_VALUE = 0x7FFFFFFF       /* For 4 byte alignment */
}IKE_VERSION_E;

typedef enum tagIKE_CONFIG_ID_TYPE_E
{
    IKE_REMOTE_IP_NONE,             /* User has Not configured any ID */
    IKE_REMOTE_IP_MANUAL,           /* User has configured Remote IP directly */
    IKE_REMOTE_IP_FQDN,             /* User has configured FQDN */
    IKE_REMOTE_IP_MAX = 0x7FFFFFFF  /* For 4 byte alignment */
}IKE_CONFIG_ID_TYPE_E;

/* IKE proposal structure */
typedef struct stIKEProposalContent
{
    ULONG ulProposalLevel;  /* proposal priority level / number */
    ULONG ulAuthMethod;     /* Authentication method- preshared or EAP */
    ULONG ulAuthAlgorithm;  /* Auth algorithm   MD5 / SHA1  */
    ULONG ulEncrAlgorithm;  /* Encryption Algorithm DES/3DES/AES    */
    ULONG ulDHGroup;        /* DH Group1 / DH group 2   */
    ULONG ulLifePeriods;    /* Phase 1 SA life time in seconds  */
    ULONG ulAuthLifeTime;   /* re-auth interval in seconds  */
    USHORT usEncKeyLen;     /* Use to store the Key Length in case of AES */
    USHORT usPrf;           /* prf PRF_HMAC_MD5 / PRF_HMAC_SHA1*/
}IKE_PROPOSAL_CONTENT_S;

/* IKE proposal structure for setting the priority for the proposal order */
typedef struct stIKEPropPrio
{
    ULONG ulAuthAlgorithm;  /* Auth algorithm   MD5 / SHA1 */
    ULONG ulEncrAlgorithm;  /* Encryption Algorithm DES/3DES/AES */
    ULONG ulDHGroup;        /* DH Group1 / DH group 2 */
    USHORT usEncKeyLen;     /* Use to store the Key Length in case of AES */
    USHORT usPrf;           /* prf PRF_HMAC_MD5 / PRF_HMAC_SHA1*/
}IKE_PROP_PRIO_S;

/* IKEv1 proposal structure for setting the priority for the proposal order */
typedef struct stIKEV1PropPrio
{
    ULONG ulAuthAlgorithm;  /* Auth algorithm   MD5 / SHA1 */
    ULONG ulEncrAlgorithm;  /* Encryption Algorithm DES/3DES/AES */
    ULONG ulDHGroup;        /* DH Group1 / DH group 2 */
    USHORT usEncKeyLen;     /* Use to store the Key Length in case of AES */
    USHORT usAuthMethd;     /* Auth method used only in case of IKEv1 */
}IKEV1_PROP_PRIO_S;

/* AR Req: FQDN changes */
#define IKE_FQDN_NAME_MIN_LEN           1
#define IKE_FQDN_NAME_MAX_LEN           254
#define IKE_FQDN_DOMAIN_LABEL_MAX_LEN   63
#define IKE_FQDN_TRIGGER_INTRVL         (30 * 1000) /* 30 seconds */

typedef enum tagIKE_FQDN_SWITCH_E
{
    IKE_FQDN_UN_CFG,            /* FQDN not configured for this peer */
    IKE_FQDN_RESP_PENDING,      /* FQDN resolution request has been sent to Peer, responce pending */
    IKE_FQDN_RESOL_COMPLETE,    /* FQDN resolution is complete and the address is present in Peer address */
    IKE_MAX_FQDN_SW_ENUM_VALUE = 0x7FFFFFFF       /* For 4 byte alignment */
}IKE_FQDN_SWITCH_E;

/* IKE peer structure */
typedef struct stIKEPeerContent
{
    CHAR  szPeerName[IKE_PEER_NAME_MAX_LEN];        /* IKE Peer name*/
    CHAR  szKey[IKE_KEY_MAX_LEN];                   /* Pre-shared key */
    CHAR  szRemoteID[IKE_PUB_ID_MAX_LENGTH + 1];    /* IKE Remote id information */
    CHAR  szFQDN[IKE_FQDN_NAME_MAX_LEN + 1];        /* FQDN */
    CHAR  szAuthDomain[IKE_TRUST_NAME_MAX_LEN];     /* Authentication domain */
    UCHAR ucResv;
    ULONG ulAddress;            /* Peer address in Host Order */
    ULONG ulEndAddress;         /* Peer end address, Host Order */
    ULONG ulVrfIndex;           /* VPN vrf index */
    ULONG ulIfVrfIndex;         /* VPN ifnet vrf index */
    ULONG ulExchangeMode;       /* Exchange mode for peer(main, aggr, quick) */
    ULONG ulIdType;             /* Local id type, name or IP */
    ULONG ulNatTraversal;       /* Enabled if NAT exist */
    ULONG ulProposal;           /* Proposal number, if non-zero, only
                                   this proposal is used for negotiation */
    /*Ikev2-ByteAlignment*/
    ULONG ulDpdIdleTime;        /*  DPD idle time in seconds  */
    USHORT usSrcSubNetType;     /* Source subnet, for IP address or mask */
    USHORT usDstSubNetType;     /* Destination subnet, for IP address or mask */
    USHORT usDpdRetransmitInterval; /* DPD retransmit interval in seconds   */
    USHORT usDpdRetries;        /* Number of retries    */
    UCHAR ucDpdEnable;          /*  DPD enable/disable  */
    UCHAR ucDpdMode;            /* dpd mode On Demand / Periodic    */
    UCHAR ucXauthMode;          /* Xauth mode, Static/dynamic   */
    UCHAR ucXauthType;          /* Xauth type:- Generic/skey/otp/radius-chap */
    UCHAR szXauthPasscode[IKE_XAUTH_ATTR_PASSCODE_MAXSIZE + 1];
    UCHAR szXauthUserName[IKE_XAUTH_ATTR_USERNAME_MAXSIZE + 1];
    UCHAR szXauthPassword[IKE_XAUTH_ATTR_PASSWORD_MAXSIZE + 1];
    UCHAR szXauthDomainName[IKE_XAUTH_ATTR_DOMAIN_MAXSIZE + 1];
    CHAR szGroupName[IKE_GROUP_NAME_MAX_LEN]; /* Groupname for id type KEY-ID */
    UCHAR ucModeCfgType;        /* Mode cfg flag- enable or disable */
    UCHAR ucDPDHashSeq;         /* DPD message sending format HASH_NOTIFY /
                                    NOTIFY_HASH */
    UCHAR ucNegIkeVersion;      /* Negotiated IKE version */
    UCHAR ucConfiguredIkeVer;   /* Ike peer version V1 or V2*/
    /* Peer ID type for IKEv2 */
    ULONG ulPeerIdType;  /* Peer ID type to be sent in IDr of IKEv2 */

    /*Sunil: Peer local address*/
    ULONG ulLocalAddr;

    ULONG ulPkiFlag;

    /* AP-REQ: Validate Peer auth method */
    ULONG ulRemoteAuthMethod;

    /* PKI object name*/
    CHAR  szObjName[IKE_TRUST_NAME_MAX_LEN];

    /* IPSEC6_Changes Story 10 */
    ULONG ulDpdReqSent;
    ULONG ulDpdAckRecvd;
    ULONG ulDpdFailed;

    /*Post B039: added for Proposal Initialization*/
    ULONG ulPeerLifeTime;
    ULONG ulPeerReauthLifeTime;
    ULONG ulPeerAuthMethod;
    UCHAR ucUseAllSupportedAlg;
    UCHAR ucPeerVer;
    UCHAR ucFQDNState;
    UCHAR ucRemoteAddrType;

    /*Ipv6: Security Support*/
    IN6ADDR_S stLocalIPv6Addr;
    IN6ADDR_S stPeerIPv6Addr;
    IN6ADDR_S stPeerIPv6EndAddr;

    /* AR-PERFORMANCE*/
    ULONG ulPeerIndex;
    UCHAR ucPeerType;  /* This field is used to identify the peer type (master/backup/normal)*/
    UCHAR ucIsAutoTriggerEnabled; /* This field will identify if the auto trigger is enabled for the
                                     peer(master/slave) or not */
    UCHAR ucReserved[2];
}IKE_PEER_CONTENT_S;


/* IKE peer structure */
typedef struct stIKESpokePeerContent
{
    ULONG ulAddress;            /* Peer address in Host Order */
    ULONG ulVrfIndex;           /* VPN vrf index */
    ULONG ulLocalAddr;          /* Peer local address*/
}IKE_SPOKE_PEER_CONTENT_S;


/* IKE global data Structure */
typedef struct stIKEGlobalContent
{
    CHAR  szLocalName[IKE_MAX_LOCAL_NAME_LEN];
    ULONG ulModuleID;       /* Module ID information  */
    ULONG ulWaitListID;     /* Waitlist ID information  */
    ULONG ulPeerCount;      /* Total peer count (Configured & Profile peers ) */
    ULONG ulConfigPeerCount;/* Total Configured peer count */
    ULONG ulProfPeerCount;  /* Total Profile peer count */
    ULONG ulProposalCount;  /* Total proposal count */
    ULONG ulSACount;        /* Total SA count Phase1 and pahse 2    */
    ULONG ulPhase1SACount;  /* Total number of phase 1 SA   */
    ULONG ulPhase2SACount;  /* Total number of phase 2 SA   */

    /* PostB102: Display Req */
    ULONG ulEstPhase1SACount; /* Total number of established phase1 SA */
    ULONG ulEstPhase2SACount; /* Total number of established phase2 SA */

    /* Added to fill IPV6 IKEV1 established SA count */
    ULONG ulIPV6IKEV1EstPhase1SACount; /* Total number of established phase1 SA of IKEV1 IPV6 */
    ULONG ulIPV6IKEV1EstPhase2SACount; /* Total number of established phase2 SA of IKEV1 IPV6 */

    /* total Peers(Configured & profile Peers) */
    ULONG ulPeerMax;        /* Maximum Peer supported   */
    ULONG ulPeerCur;        /* Peer count   */
    ULONG ulPeerMin;        /* Minimum peer count value */

    /* Configured peer */
    ULONG ulConfigPeerMax;  /* Maximum Configured Peer supported   */
    ULONG ulConfigPeerCur;  /* Peer Configured count   */
    ULONG ulConfigPeerMin;  /* Minimum Configured peer count value */

    /* profile peer */
    ULONG ulProfPeerMax;    /* Maximum Profile Peer supported   */
    ULONG ulProfPeerCur;    /* Peer Profile count   */
    ULONG ulProfPeerMin;    /* Minimum Profile peer count value */

    ULONG ulProposalMax;    /* Maximum proposal count   */
    ULONG ulProposalCur;    /* Current proposal count   */
    ULONG ulProposalMin;    /* Minimum proposal count   */
    ULONG ulSAMax;          /* Maximum SA supported count   */
    ULONG ulSACur;          /* Current SA count */
    ULONG ulSaMin;          /* Min SA count */
    ULONG ulDebugFlag;      /* Debug flag   */
    ULONG ulIPCCapacity;    /* IPC capacity value   */
    ULONG ulHAState;        /* HA state information Master / Slave  */
    ULONG ulKeepAlivInt;    /* Keep alive interval */
    ULONG ulKeepAlivTime;   /* Keep alive time out */
    ULONG ulNatKeepAlivInt; /* NAT keep alive interval  */
    ULONG ulSendSPIList;    /* For sending SPI list */
    ULONG ulModeCfgAddrMin; /* Min Mode-cfg address supported   */
    ULONG ulModeCfgAddrCur; /* Current configured mode-cfg addres value */
    ULONG ulModeCfgAddrMax; /* Maximum supported mode-cfg address count */
    ULONG ulModeCfgAddrCount;/* global mode-cfg address count   */
    UCHAR ucHrbtSeqNumType; /* @@Gopa *//* Heart beat sequence payload type */
    UCHAR aucResv[3];

    /* IKEv2 */
    ULONG ulIKEV2SaNum;     /* IKEv2 SA count   */
    ULONG ulIKEV2Peernum;   /* IKEv2 peer count */
    //IKEV2_COOKIE_S stcookie;        /* Cookie */
    CHAR *pucApplicationVersion;    /* App. version to be sent when queried */
    USHORT usInitiatorAlways;       /* The node can only be initiator if this
                                       is set */
    USHORT usResv;
    /* Added for the command display ike stat v2 */
    ULONG ulV2Phase1SACount;    /* IKEv2 SA count   */
    ULONG ulV2Phase2SACount;    /* Child SA count   */
    ULONG ulV2TotalCount;       /* Total SA count IKEv1 and IKEv2   */
    ULONG ulV1V2TotalCount;     /* Total SA count IKEv1 and IKEv2   */
    ULONG ulPh1EstCount;        /* Established IKEv2 Phase 1 SA count */
    ULONG ulPh2EstCount;        /* Established IKEv2 child SA count */
    /* Added for V6 established stats */
    ULONG ulPh1EstIPV6Count;    /* Established IKEv2 Phase 1 SA count for IPV6 */
    ULONG ulPh2EstIPV6Count;    /* Established IKEv2 child SA count for IPV6 */
}IKE_GLOBAL_CONTENT_S;

/*  Holds Statistics values  */
typedef struct tagIKE_Statistics_S
{
    /* To hold ISAKMP Notify message Sent Stats */
    ULONG ulISAKMPNotifySent[IKE_STATS_ISAKMP_NOTIFY_MAX];

    /* To hold ISAKMP Notify message Received Stats */
    ULONG ulISAKMPNotifyRcvd[IKE_STATS_ISAKMP_NOTIFY_MAX];

    /* IPSec Notifications Sent */
    ULONG ulNotifyRespLifetimeSent;
    ULONG ulNotifyReplayStatusSent;
    ULONG ulNotifyInitialContactSent;
    ULONG ulNotifyStillConnectedSent;

    /* IPSec Notifications Received */
    ULONG ulNotifyRespLifetimeRcvd;
    ULONG ulNotifyReplayStatusRcvd;
    ULONG ulNotifyInitialContactRcvd;
    ULONG ulNotifyStillConnectedRcvd;

    /* DPD Notifications Sent */
    ULONG ulNotifyRUThereSent;
    ULONG ulNotifyRUThereAckSent;

    /* DPD Notifications Received */
    ULONG ulNotifyRUThereRcvd;
    ULONG ulNotifyRUThereAckRcvd;

    /* Delete messages sent */
    ULONG ulDeleteSent;

    /* Delete messages Received */
    ULONG ulDeleteRcvd;
} IKE_STATISTICS_S;


/*structure to store IKE statistics */
typedef struct stIKEStatistics
{
    ULONG ulPeerCount;                /* Total peer count (Configured & Profile peers ) */
    ULONG ulConfigPeerCount;          /* Total Configured peer count */
    ULONG ulProfPeerCount;            /* Total Profile peer count */

    ULONG ulIPv4PeerCount;            /* Number of Ipv4 peer */
    ULONG ulIPv6PeerCount;            /* Number of Ipv6 peer */

    ULONG ulProposalCount;            /* Number of proposals */
    ULONG ulSACount;                  /* Number of SA */
    ULONG ulPhase1SACount;            /* Number of phase 1 SA */
    ULONG ulPhase1Ike6SACount;        /* Number of phase 1 SA  for IPv6*/

    ULONG ulPhase2SACount;            /* Number of phase 2 SA */
    ULONG ulPhase2Ike6SACount;        /* Number of phase 2 SA for ipv6 */

    /* PostB102: Display Req */
    ULONG ulEstPhase1SACount;         /* Total number of established phase1 SA */
    ULONG ulEstPhase1Ike6SACount;     /* Total number of established phase1 SA for IPv6 */

    ULONG ulEstPhase2SACount;         /* Total number of established phase2 SA */
    ULONG ulEstPhase2Ike6SACount;     /* Total number of established phase2 SA for IPV6 */

    ULONG ulExchangeCount;            /* Current exchanges count    */
    ULONG ulTransportCount;           /* Current transport count    */

    IKE_STATISTICS_S stIkeNotStats;   /* IKE statistics values  */
    ULONG ulIKEv1PeerCount;           /* IKEv1 Peer count   */

    /* IKEv2 */
    ULONG ulIKEv2PeerCount;           /* IKEv2 Peer count   */
    ULONG ulIKEv2SaCount;             /* IKEv2 Total SA count   */
    ULONG ulIKEv2IkeSaCount;          /* IKEv2 Phase 1 SA (IKE SA)count */
    ULONG ulIKEv2Ike6SaCount;         /* IKEv2 Phase 1 SA (IKE SA)count for IPv6 */

    ULONG ulIKEv2ChildSaCount;        /* IKEv2 Child SA count   */
    ULONG ulIKEv2ChildIke6SaCount;    /* IKEv2 Child SA count for ipv6  */

    /* S9300 Stat addition: for number of allocated conn IDs */
    ULONG ulAllocatedConnIdCount;

    /*Added for IKEV2 established SA count*/
    ULONG ulEstPhase1IKEv2SACount;    /* Total number of established phase1 SA with IKEv2 */
    ULONG ulEstPhase1IKEv2IP6SACount; /* Total number of established phase1 SA
                                         for IPv6 with IKEv2 */

    ULONG ulEstPhase2IKEv2SACount;    /* Total number of established phase2 SA with IKEv2 */
    ULONG ulEstPhase2IKEv2IP6SACount; /* Total number of established phase2 SA for IPV6 with IKEv2 */

}IKE_STATS_CONTENT_S;

/* To register callback for hardware support */
typedef struct tagIKESGSN
{
    ULONG (*pfIKE_SH_GetLocalAddr) (CHAR *pucPolName, ULONG ulSeqNum,
                                 VOID *pvAddr);
    ULONG (*pfIKE_SH_GetLocalIpv6Addr) (CHAR *pucPolName, ULONG ulSeqNum,
                                            IN6ADDR_S *pstIpv6Addr);
}IKE_SGSN_S;

/* Temporary structure in SA, stores the information about the exchange for
that SA */
typedef struct tagIKEv2TempExch
{
    ULONG ulSentMessageId;  /* Sent message Identifier  */
    ULONG ulIsRequest;      /* Request / Response   */
    ULONG ulSecondsRem;     /* Time-out value   */
}IKEv2_TEMP_EXCH_S;

/*ITR3.Story.9, Structure to hold initiator/responder template information*/
typedef struct tagIKEv2_DynaTempTs
{
    ULONG ulAddr;
    UCHAR ucType;   /* Type IPSEC_ID_IPV4_ADDR / IPSEC_ID_IPV4_ADDR_SUBNET  */
    UCHAR ucRes[3];
    IN6ADDR_S stIPV6Addr;
    IN6ADDR_S stIPV6SubnetAddr;

}IKEV2_DYNATEMP_TS_S;

typedef struct tagIKEv2_TempPolicy
{
    ULONG policy;       /* IKE Proposal priority number */
    ULONG ulAuthLifeTime;
    ULONG ulNegAuthLifeTime;
    ULONG life;         /* ISAKMP SA lifetime */
    USHORT enc;         /* Encryption algorithm (DES, 3DES)*/
    USHORT hash;        /* Hash algorithm (MD5, SHA) */
    USHORT auth;        /* Authentication method (Pre-shared)*/
    USHORT grp;         /* DH group used (group-1, group-2) */
    USHORT usKeyLength; /*Key Length of the corresponding Encryption algorithm*/
    USHORT usPad;

    /* IKEv2 */
    USHORT usPrf;
    USHORT usResvd;
}IKEV2_TEMP_POLICY;

typedef struct tagIKEv2_TempWindow
{

    /*By default 25*/
    ULONG ulWindowSize;

    /*Stores the starting point of window.
     This is incremented when window size goes beyond 25*/
    ULONG ulWindowStart;

    /*The latest largest received message id*/
    ULONG ulWindowEnd;

    /*Bitmap of all the received messages ids within the windowsize*/
    ULONG ulBitMap;
}IKEV2_TEMP_WINDOW_S;

/* IKE exchange structure */
typedef struct stIKEExchangeContent
{
    ULONG ulNatVersion;

    /* the result of NAT-traversal negotiation
       0:  No NAT gateway in the middle
       1:  the local site locates behind the NAT gateway
       2:  the peer site locates behind the NAT gateway
    */
    ULONG ulNatTraversal;

    ULONG ulUdpEncapsulate;

    /* zhangpeng 2004-11-17 for support access of MPLS VPN by IPSec tunnel*/
    /* the VPN index of peer*/
    ULONG ulVrfIndex;

    /* Various flags, look below for descriptions.  */
    ULONG ulFlags;

    CHAR szName[IKE_MAX_EXCH_NAME_LEN];

    UCHAR ucCookies[IKE_PUB_ISAKMP_HDR_COOKIES_LEN];

    /* The message ID signifying phase 2 exchanges.  */
    UCHAR ucMessage_id[IKE_PUB_ISAKMP_HDR_MESSAGE_ID_LEN];

    /* 1 if we are the initiator, 0 if we are the responder.  */
    UCHAR ucInitiator;

    /* The exchange type we are using.  */
    UCHAR ucExchType;

    /* Phase is 1 for ISAKMP SA exchanges, and 2 for application ones.  */
    UCHAR ucPhase;

    /* The "step counter" of the exchange, starting from zero.  */
    UCHAR ucStepCounter;

    /* XXX Do we want to save these in the exchange at all?  */
    UCHAR ucId_i[IKE_IPSEC_ID_SIZE];
    UCHAR ucId_r[IKE_IPSEC_ID_SIZE];

    /* The corresponding bit is set in this flag for each requested attribute in
    the XAUTH Request */
    /* Attributes requested in a CFG/XAUTH Request by the server */
    ULONG ulRequestedAttr;

    /* This is to keep a count of XAUTH Requests received in an XAUTH
    Transaction */
    ULONG ulXauthRequestCount;

    /* The Challenge string received in the Request.It is not null terminated */
    UCHAR *pucChallenge;

    /* Size of Challenge string received in the Request */
    ULONG ulChallengeLen;

    /* The XAUTH Authentication Type */
    USHORT usXauthType;

    /* The Status verdict arrived in Set from the Server. It could only be Pass
    or Fail */
    USHORT usXauthStatus;


    /* Sequence number of the first sent DPD R-U-THERE message for the on going
    DPD exchange */
    ULONG ulDpdFirstSentSeqNo;

    /* Sequence number of the last sent DPD R-U-THERE message for the on going
    DPD exchange */
    ULONG ulDpdLastSentSeqNo;

    /* Retransmit interval for DPD R-U-THERE message*/
    USHORT usDPDRetransmitInterval;

    /* Max number of re-transmit for DPD R-U-THERE message */
    USHORT usDPDRetransmitLimit;

    /* Transaction Exchange Identifier (for CFG/XAUTH/Heartbeat) */
    USHORT usIdentifier;

    /* V1R3_DEV: Mode-CFG or XAUTH or Heartbeat or DPD */
    UCHAR ucTransExchType;

    /* XAUTH transaction complete or pending or reply-pending */
    UCHAR ucTransactionStatus;
}IKE_EXCHANGE_CONTENT_S;

/*Ipv6: Security Support*/
typedef union tagIKE_IPADDR_U
{
    ULONG ulIpv4Addr;
    IN6ADDR_S stIpv6Addr;
}IKE_IPADDR_U;

/* Structure to store SA contents */
typedef struct stIKESAContent
{
    ULONG ulPhase1ConnID; /*Only for phase 2*/

    /*The sequence number sent for phase 2 messages */
    ULONG ulSeqNo;

    /*To store the last known good sequence number to check for duplicate or
    incorrect packet*/
    ULONG ulLkgSeqNo;

    /* Flag stores if NAT is enabled and if the NAT device is local or remote*/
    ULONG ulNatTraversal;

    /* Stores if UDP tunnel mode/ Transport mode is used  */
    ULONG ulUdpEncapsulate;

    ULONG ulVrfIndex; /* VRF index of vpn instance */

    ULONG ulAddr; /* must be in network byteorder */
    ULONG ulMask; /*From ipsec_policy*/

    /* Various flags, look below for descriptions.  */
    ULONG ulFlags;

    /* Lifetime data.  */
    ULONG ulSeconds;
    ULONG ulKilobytes;
    ULONG ulSecondsRem;

    /* SA Index */
    ULONG ulConnId;/* For L4 warning  */
    /*The source & destination port in case of UDP encapsulation*/
    ULONG ulUdpSrcPort;/* For L4 warning  */
    ULONG ulUdpDstPort;/* For L4 warning */

    ULONG ulBlockSize;
    ULONG ulSkeyid_len; /* Size of Authentication key for phase1 SA */

    /* End IP Addresses*/
    ULONG ulSrcAddr; /* must be in network byteorder */
    ULONG ulDstAddr; /* must be in network byteorder */

    /* DOI ID */
    /* DOI is 4-bytes long */
    ULONG ulDOIId;

    ULONG ulModeCfgPolicySeqNo; /* Use to store the mode-cfg policy sequence
                                   number for Phase 2 SA */
    ULONG ulDPDSentSeqNo; /* Last sent DPD sequence number */
    ULONG ulDPDRecvSeqNo; /* Last recv DPD sequence number */
    USHORT usLastSentIdentifier; /* Last sent transaction identifier */
    USHORT usLastRecvXauthIdentifier; /* Last recv Xauth identifier */
    USHORT usLastRecvModecfgIdentifier; /* Last recv Modecfg identifier */
    USHORT usLastRecvHrtbtIdentifier; /* Last recv Hrtbt identifier */
    UCHAR ucVidFlag; /* Stores the result of DPD VID negotiation */
    UCHAR ucXauthStatus; /* Xauth pending/time-out/success result*/
    UCHAR ucDscp; /* B115 : Added for DSCP value display */
    UCHAR ucResv;

    /* Both initiator and responder cookies.  */
    UCHAR szCookies[IKE_PUB_ISAKMP_HDR_COOKIES_LEN];

    /* The message ID signifying non-ISAKMP SAs.  */
    UCHAR szMessageId[IKE_PUB_ISAKMP_HDR_MESSAGE_ID_LEN];

    CHAR  szPeerName[IKE_PEER_NAME_MAX_LEN];

    /* A name of the major policy deciding offers and acceptable proposals.  */
    CHAR szPolicyName[IKE_POLICY_NAME_MAX_LEN];

    UCHAR aucRiv[IKE_MAX_IV_LEN];
    UCHAR aucLiv[IKE_MAX_IV_LEN];
    UCHAR aucKeyData[IKE_KEYDATA_SIZE];
    UCHAR aucAuthKey[IKE_MAX_SKEYID_LEN]; /* Authentication Key of Phase1 SA*/

    /* For SPI (Inbound and Outbound) for phase 2 SAs*/
    /* Element 0 - outgoing, 1 - incoming.*/
    UCHAR szSpiProto1[2][IKE_MAX_SPI_LEN];
    UCHAR szSpiProto2[2][IKE_MAX_SPI_LEN];

    /* The protection suite chosen.  */
    UCHAR ucProto1;
    UCHAR ucProto2;

    /* The exchange type we should use when rekeying.  */
    UCHAR ucExchType;

    /* Phase is 1 for ISAKMP SAs, and 2 for application ones.  */
    UCHAR ucphase;

    UCHAR ulProtoId;

    /* Added to display Auth and encryption algo for phase 1 SA's */
    UCHAR ucAuthAlgo;
    UCHAR ucEncAlgo;

    /*AC4D02063: For SPI List Negotiated or not */
    UCHAR ucSendSPIList;

    /*-------------------------------------------------------------------------*
    *                           IkeV2 specific                                 *
    *-------------------------------------------------------------------------*/

    /*incremented when a new request is sent out and decrmented when response
      is received for that request*/
    ULONG ulNumReqPending;

    ULONG ulAuthSecRem;

    /* sending message id. Should be incremented after the response is recvd*/
    ULONG ulSendMessageId;

    /*When a message is received, the message id is checked against this.
      Incremented after request is received and validated*/
    ULONG ulRecvMessageId;

    /* Authentication method */
    ULONG ulAuthMethod;

    USHORT usIkeVersion;

    /*initiator = 1 responder = 0*/
    UCHAR ucInitiator;

    UCHAR ucState;

    /* Both initiator and responder cookies.
       The SPIs are the old IKE SA SPI both for re-key and re-auth */
    UCHAR szOldSaSpi [16];

    /* To indicate that this SA was created due to Re-key.
    When this SA is re-keyed, the flag is reset */
    UCHAR ucRekeyedFlag;

    /* Need to check if DPD needs to be initiated after Phase 1 is established
    or when maximum re-transmission has exceeded */
    UCHAR ucDpdInitiate;

    /*IN parameters used for sending IPSEC and OUT parameters
      received from IPSEC and to be sent to initiator */
    UCHAR ucUseTransportMode;

    /*IKEv2_Reauth-Rekey*/
    UCHAR ucReauthedFlag;

    /* If the SA is to be rekeyed */
    UCHAR ucToBeRekeyed;

    /* If the SA is to be deleted */
    UCHAR ucToBeDeleted;

    /* If the SA is to be DPD initiated */
    UCHAR ucToBeDPDInitiated;

    UCHAR ucSaIpVer;

    /* Number of exchanges under this SA */
    ULONG ulExchCnt;

    /* List of exchanges for this SA */
    IKEv2_TEMP_EXCH_S stTempExchange[31];

    IKEV2_DYNATEMP_TS_S stTempTsi[10];
    IKEV2_DYNATEMP_TS_S stTempTsr[10];

    /*This is applicable for child sa exchange only.
    This window size check will be done only for CREATE_CHILD_SA exchange
    For other exchanges only the window is updated but the
    received message should be checked against IKE_SA message ids.*/
    IKEV2_TEMP_WINDOW_S stSndWindow;
    IKEV2_TEMP_WINDOW_S stRecvWindow;

    IKEV2_TEMP_POLICY stTempPolicy;

    /* B044 : Policy sequence number */
    ULONG ulPolSeqNo;
    /*Ipv6: Security Support*/
    IN6ADDR_S stIPAddr;

    /*To display Source ID and Destination ID */
    IN6ADDR_S stSrcIPAddr;

    /* Added by Arun for IPSV1R2C3-60 */
    IN6ADDR_S stSrcSubnetMask;

    IN6ADDR_S stDstIPAddr;

    /* Added by Arun for IPSV1R2C3-60 */
    IN6ADDR_S stDstSubnetMask;

    /*To display destination address maintained in the transport*/
    IKE_IPADDR_U unSADstAddr;

    /* v4 over v6 ID display support */
    UCHAR id_ci_type;
    UCHAR id_cr_type;
    UCHAR ucSAType;  /* This field is used to identify the SA type based on the peer type */
    UCHAR padd;
}IKE_SA_CONTENT_S;

/* IKE message structure */
typedef struct stIKEMessageContent
{
    /* Message flags described below.  */
    ULONG ulFlags;
    ULONG ulConnID;

    /* Number of times this message has been sent.  */
    ULONG ulXmits;

    /* The timeout event causing retransmission of this message.  */
    ULONG ulSecondsRem;

    /* Both initiator and responder cookies.  */
    UCHAR szCookies[IKE_PUB_ISAKMP_HDR_COOKIES_LEN];

    /* Version */
    UCHAR ucIkeVersion;
    UCHAR ucResv[3];

}IKE_MESSAGE_CONTENT_S;

/* structure for IKE event */
typedef struct stIKEEventContent
{
    ULONG ulSecondsRem;
    ULONG ulTimerID;    /* The Name/Type of timer event */

}IKE_EVENT_CONTENT_S;


typedef enum tagIKE_TIMER_TYPE
{
    IKE_TIMER_COOKIE_RESET,
    IKE_TIMER_EXCHG_ERR_FREE_AUX,
    IKE_TIMER_LGKSN_TIMER,
    IKE_TIMER_SA_SOFT_EXPIRE,
    IKE_TIMER_SA_HARD_EXPIRE,
    IKE_TIMER_KEEPALIVE_NOTIFY,
    IKE_TIMER_KEEPALIVE_TIMEOUT,
    IKE_TIMER_NAT_KEEP_ALIVE,
    IKE_TIMER_SA_REPLCE_EXPR_2,
    IKE_TIMER_SA_REPLCE_EXPR_1,
    IKE_TIMER_MESSAGE_SEND,
    IKE_TIMER_ADDR_SOFT_EXPIRE, /*instead of IKE_MODECFG_ADDR_SOFT_EXPTIMER*/
    IKE_TIMER_ADDR_HARD_EXPIRE, /*instead of IKE_MODECFG_ADDR_HARD_EXPTIMER*/
    IKE_TIMER_XAUTH_WAIT_EXPIRE, /* Timer to wait for xauth request from server*/

     /* AC4D05579, time after which the ipsec re-negotiated address will be
     moved to free pool */
    IKE_TIMER_ADDR_RENEGOTIATED_MOVE,

    /* AC4D08200: DH group Creation Timer IDs */
    IKE_TIMER_CREATE_DH_GROUP_ONE,
    IKE_TIMER_CREATE_DH_GROUP_TWO,

    /* IPSEC6_Changes Story 10 */
    IKE_TIMER_PH1SA_DPD,

    IKE_TIMER_MAX_TYPE,
    IKE_MAX_TIMER_LEV_ENUM_VALUE = 0x7FFFFFFF
}IKE_TIMER_TYPE_E;

/* IKE transport structure */
typedef struct stIKETransportContent
{
    LONG lFlags;      /* Flags describing the transport.  */
    ULONG ulIfVrfIndex; /* Vrf Index    */
    ULONG ulSrcAddr;    /* source address   */
    ULONG ulDstAddr;    /* Destination address  */
    USHORT usSrcPort;   /* UDP source port  */
    USHORT usDstPort;   /* UDP Destination port */

    /* AC4D01584: Increased the size of interface name from 16 to 32 */
    CHAR szIfName[IKE_MAX_IFNET_NAME_LEN]; /*Added to display Ifnet interface*/
    CHAR szName[IKE_MAX_TRPT_NAME_LEN];
    IKE_MESSAGE_CONTENT_S stMessage[IKE_TRPT_MESSAGES]; /* Message buffer   */

}IKE_TRANSPORT_CONTENT_S;

/* structure to store the source & dest port of SA */
typedef struct stIKESAPort
{
    ULONG ulSrcPort;
    ULONG ulDstPort;
}IKE_SA_PORT_S;

/* To pass HA function pointers from shell to core. */
typedef struct tagIKEProdVal
{
    ULONG ulKeepaliveEnable;
    ULONG ulKeepaliveInt;
    ULONG ulKeepaliveTimout;
    ULONG ulNATEnable;
    ULONG ulExchMode;
    ULONG ulIdType;
    ULONG ulSPIListEnable;
    UCHAR ucRChapHashSeq; /* Value for order of RCHAP PSWD calculation*/
    UCHAR ucXauthPswdMode;/* HEX/Encoded PSWD calculation for OTP/SKEY*/
    UCHAR ucXauthAuthType;/* The xauth authetication methods supported*/
    UCHAR ucPad[1];
    ULONG ulIdleTime; /* DPD Idle-Time in seconds */
    USHORT usRetransmit; /* DPD Retransmit interval */
    USHORT usRetries; /* DPD Retry-Limit */

    /* IKEv2 */
    ULONG ulReauthTimeout;/* Check */
    UCHAR ucInitiator;
    UCHAR usRes;
    USHORT usNAT;
    USHORT usReAuth;
    USHORT usPad;
}IKE_PRODUCT_VAL_S;

/*  Structure to pass the DPD attributes from shell function to the core
    function */

typedef struct tagIKE_DPD_CFG_S
{
    ULONG ulIdleTime;   /* Value of the idle time during configuration in
                           seconds*/
    USHORT usRetransmitInterval; /* The value of the retransmit interval */
    USHORT usRetries;           /* The maximum number of DPD retry*/
    ULONG ulOpMode;             /* The mode UNDO/CONFIG*/
    ULONG ulAttrFlag;   /*  Carries the infromation which of the attribute
                        is to be set/reset    */
}IKE_DPD_CFG_S;

/*  Structure to pass the DPD Mode from shell function to the core function */
typedef struct tagIKE_DPD_EN_CFG_S
{
    ULONG ulOpMode;  /* The mode UNDO/CONFIG */
    UCHAR ucDpdMode; /* On-Demand / Periodic */
    UCHAR ucResv[3];
}IKE_DPD_EN_CFG_S;

/*  Structure to pass the XAUTH attributes  from shell function to the core
    function */

typedef struct tagIKE_XAUTH_ATTR_S
{
    UCHAR *szUserName; /* Pointer to string containing username Len<8-63>*/
    UCHAR *szPassword; /* Pointer to string containing PSWD Len<8-31>*/
    UCHAR *szDomainName; /* Pointer to string containing Domain name Len<8-63>*/
}IKE_XAUTH_ATTR_S;



/* Structure to notify the required (and suggested) attributes */
typedef struct tagIKE_PRODUCT_NOTIFY_S
{
    ULONG ulFlag;        /* Notification type CONFG/GET/NOTIFY/DEL/SOFTEXPIRE */
    ULONG ulAttributes;  /* Bits for each of the attributes */
    ULONG ulNumAddr;     /* The number of addresses obtained/ to be requested */
    ULONG *pulAddr;      /* Pointer to the list of addresses */
    ULONG *pulAddrMask;  /* Pointer to the address and mask */
    ULONG ulNumWins;     /* Number of wins server addresses */
    ULONG *pulWins;      /* Pointer to the list of wins server addresses */
    ULONG ulNumDns;      /* Number of Dns addresses */
    ULONG *pulDns;       /* Pointer to the list of Dns server addresses */
    ULONG ulNumDhcp;     /* Number of dhcp server addresses */
    ULONG *pulDhcp;      /* Pointer to the list of dhcp server addresses */
    ULONG ulNumSubNet;   /* Number of subnets */
    ULONG *pulSubNet;    /* Pointer to the list of subnets */
    ULONG ulAddrExpire;  /* The value of address expiry in seconds */
    UCHAR *pszAppVersion;/* The version string of the peer */
    ULONG ulNumSupAttr;  /* The number of supported attributes */
    ULONG *pulAttrList;  /* The list of supported attributes of peer */
    ULONG ulAddrPublic;  /* The received IP address by Peer IKE instance */

} IKE_PRODUCT_NOTIFY_S;

/* Structure to notify the required Parameters */
typedef struct tagIKE_PRODUCT_NOTIFY_PARA_S
{
    ULONG ulPeerAddr;    /* PeerAddress*/
    ULONG ulVrfIndx;     /* VrfIndex */
    CHAR  szAuthDomain[IKE_TRUST_NAME_MAX_LEN]; /* Authentication domain */
    CHAR  szPeerName[IKE_PEER_NAME_MAX_LEN];
} IKE_PRODUCT_NOTIFY_PARA_S;

/*  Address related information in Mode-CFG request   */
typedef struct tagIKE_PRODUCT_GET_ATTR
{
    CHAR  szAuthDomain[IKE_TRUST_NAME_MAX_LEN]; /*Auth domain*/
    ULONG ulAppHandle;/* The application as per which the mode-cfg is trigger*/
    ULONG ulIdentifier; /*The identifier given by the application */
    ULONG ulPeerAddr; /* The address of the remote-peer */
    ULONG ulVrfIndx;  /* VrfIndex */
    UCHAR ucMode; /* Flag to identify SYNC/ASYNC mode of operation */
    UCHAR ucResv[3];
}IKE_GET_ATTR_S ;


/*  Holds the information to Notify IPSEC  */
typedef struct tagIKE_CFG_IPSEC_NOTIFY_S
{
    CHAR  szPeerName[IKE_PEER_NAME_MAX_LEN];
    ULONG *pulAddr; /* Pointer to addresses to  be added */
    ULONG ulIfindex; /* Ifindex of the Phase 1 SA */
    ULONG ulAddrCount;  /* No. of addresses to be added */
    ULONG ulAppHandle; /* Application handle corresponding to the address.
                          Filled only if it corresponds to IPsec */
    UCHAR ucMsgType;/* Add/DEL/ADD_DEL*/
    UCHAR ucResv[3];
}IKE_CFG_IPSEC_NOTIFY_S;

/*  Mode-CFG addrss related information  */
typedef struct stIKE_ADDR_INFO
{
    ULONG ulAddr;       /* Address information */
    ULONG ulLifetime;   /* Lifetime of the address */
    USHORT usAppId;     /* Application ID */
    USHORT usResv;      /* Reserved for padding */
}IKE_ADDR_INFO_S;

/*  Store the information about the Mode-CFD for Display purpose  */
typedef struct stIKE_ADDR_CONTENT
{
    ULONG ulAddrCount;              /*Total number of addrresses*/
    USHORT usUsedAddrCount;         /* Count of number of used pool addresses */
    USHORT usFreeAddrCount;         /* Count of number of free pool addresses */
    IKE_ADDR_INFO_S *pstAddrdata;   /* Pointer to address information */
}IKE_ADDR_CONTENT_S;


/* Structure used by product to give the username, PSWD and domain to IKE */
typedef struct tagIKE_XAUTH_DYNAMIC_USER_ATTR_S
{
    /* IKE peer-name given by the product */
    UCHAR szPeerName[IKE_PEER_NAME_MAX_LEN];

    /* To store the Identifier|Cookie, passed back by the product */
    UCHAR szIDCookies[IKE_XAUTH_ID_COOKIE_SIZE];

    /*Ikev2-ByteAlignment*/
    UCHAR ucResv[2];

    /* IKE user name for the ike-peer*/
    UCHAR *pucUserName;

    /* IKE PSWD for the ike-peer*/
    UCHAR *pucPassWord;

    /* Domain as per which the user is to be authenticated*/
    UCHAR *pucDomain;
} IKE_XAUTH_DYNAMIC_USER_ATTR_S;

typedef struct tagIKE_DISPLAY_TYPE_S
{
    ULONG ulNatFlag;     /* 0:ALL SA; 1:NAT SA */
    ULONG ulSaStates;    /* 0:ALL SA; 1:NOT ESTABLISHED SA */
    ULONG ulRemoteIpAddr;
    ULONG ulProfileID;
}IKE_DISPLAY_TYPE_S;


/*--------------------------------------------------------------------------*/
/* IKEv2 related definations                                                */
/*--------------------------------------------------------------------------*/

/* IKEv2 Modifications */
#define IKE_VERSION1                1
#define IKE_VERSION2                2
#define IKE_VERSIONBOTH             3

#define IKE_SET                     1
#define IKE_RESET                   0

/* IKE init information */
typedef enum enumIKEProdInit
{
    IKE_INIT_V1_COMPONENT,
    IKE_INIT_V2_COMPONENT,
    IKE_INIT_V1V2_COMPONENT,
    IKE_INIT_MAX_ENUM_VALUE = 0x7FFFFFFF       /* For 4 byte alignment */
}IKE_PRODUCT_INIT_E;

/*EAP error codes*/
#define IKEV2_ERR_MAX_EAP_EXCH_EXCEEDED 3
#define IKEV2_INVALID_EAP_MSG           4
#define IKEV2_EAP_IKESA_NOT_EXIST       5
#define IKEV2_EAP_IKE_ERROR             6
#define IKEV2_EAP_EXCH_TIMEOUT          7
#define IKEV2_EAP_NOTIFY_MSG_FAILED     8

/*EAP result without MSK*/
#define IKEV2_EAP_WITHOUT_MSK           2

typedef struct tagIKEv2_EAP_REGISTER_FUNC
{
    ULONG (*pfIKEv2_MsgNotifyToEAP) (UCHAR* pEAPMsg, ULONG ulMsgLength, ULONG
                                     ulConnId);
    ULONG (*pfIKEv2_ErrNotifyToEAP) (UCHAR* pEAPMsg, ULONG ulMsgLength,
                                       ULONG ulConnId, ULONG ulErrCode);
    ULONG (*pfIKEv2_GetMSKFromEAP) (UCHAR* pMSK, ULONG* pulKeyLength, ULONG
                                     ulConnId);
}IKEv2_EAP_REGISTER_FUNC_S;

/* To MODE-CFG, sometime product malloc memory and IKE to free it,
sometime IKE malloc a memory and product to free it. But the malloc and free
need to call visp function. so we have to provide id to product.*/
#define SID_IKE_BASE_S              0x700
#define SID_IKE_MODECFG             (SID_IKE_BASE_S + 29)
#if (TCPIP_IN_VRP == VRP_YES)
#else
#define IKE_MODULE_ID               MID_COMP_IKE
#endif

/*Post B102 changes by Anoop and Prateek*/
/* The structures IKE_XAUTH_REQ_ATTR_S & IKE_USR_PASS_S has been moved  here
    from ike_pub_internal.h. This  movement was done by Anoop & Prateek as part
    of adding comments to data structures and data structure placement.These
    are moved because they are used by Exposed APIs
 */

/* Structure to Request attributes from Product */
typedef struct tagIKE_XAUTH_REQ_ATTR_S
{
    /* To store the Identifier|Cookie, to be passed to the product */
    UCHAR szIDCookies[IKE_XAUTH_ID_COOKIE_SIZE];
    UCHAR ucResv[2];
    /* Flag to specify the required attributes */
    ULONG ulReqdAttrFlag;
} IKE_XAUTH_REQ_ATTR_S;

/*B107-Merging-IKELIB*/
/*Describes the availability of the IKE-Versions V1 & V2 from the system*/
#define  IKE_UNAVAILABLE            0
#define  IKE_AVAILABLE              1


/*
  Note that the following two macros are used by interface
  IKE_ClearPh1Ph2ByPeerAddress, for deleting IKEv1 and IKEv2 SA. If their values
  are changed then it might cause a problem. so always note that the macros
  IKE_NOTIFY and IKE_SA_DEL_NOTIFY are same and IKE_DNT_NOTIFY and
  IKE_SA_DEL_DONOT_NOTIFY are same.
 */
/* Moved from ikev2_notify.h to make it available to customer */
#define IKE_NOTIFY     1
#define IKE_DNT_NOTIFY 0


/* Defect ID: AC4D07447 - IKEv1_DSCP  */
#define IKE_SND_INITIAL_CONTACT     0
#define IKE_DNT_SND_INITIAL_CONTACT 1

/*End   */

/*Macro to represent if a notification needs to be sent to the peer */
#define IKE_SA_DEL_NOTIFY           1
#define IKE_SA_DEL_DONOT_NOTIFY     0

#define IKE_IPSECMAPNAME_LEN 16

/* AC4D07928 [B116] : Support Tunnel UP/DOWN notification */
#define IKE_TUNNEL_UP       1
#define IKE_TUNNEL_DOWN     0

/*SGSN License implementation - B511*/
typedef ULONG(*IPSECIKE_GET_LICENSE_STATE_CALLBACK_FUNC)(
    ULONG *pulLicenseState);
#define IKE_LICENSE_ENABLE 1
#define IKE_LICENSE_DISABLE 0


/*AP : Allowing duplicate remote name in different peers*/
typedef ULONG(*IKE_DUPLICATE_REMOTE_NAME)(
    UCHAR *szRemoteName);

/*Kuldeep : B514 Changes*/
typedef ULONG (*IKE_RegFuncGetPeerID_HOOK_FUNC)(ULONG ulAuthMethod,
                        UCHAR *ucPeerName, ULONG ulBufLen,  UCHAR *pucIDInfo);



typedef VOID (*IKE_TUNNEL_STATUS_CALLBACK) (CHAR *szIKEPeerName,
                                            UCHAR ucStatus);

/*B054: Crypt sign*/
typedef struct tagIKE_SHELL_CALLBACK_PKI_CRYPT_SIGN_S
{
    ULONG (*pfIKEv2_RegFuncCryptSignHw) (ULONG ulAlg, VOID  *pucCert, UCHAR* pucData, ULONG ulDataLen,
                UCHAR* pucSign, ULONG* pulSignLen);

    ULONG (*pfIKEv1_RegFuncCryptSignSslHw) (VOID  *pucCert, UCHAR* pucData, ULONG ulDataLen,
                UCHAR* pucSign, ULONG* pulSignLen);

}IKE_SHELL_CALLBACK_PKI_CRYPT_SIGN_S;


/* This structure is used to provide info for the sub warning types
IKE_WARN_SA_NEGOTIATE_P1
IKE_WARN_EVENT
*/
typedef struct tagIKE_WARN_IKESA
{
    ULONG ulWarnType;
    ULONG ulSAConnId; /* SA connection ID */
    ULONG ulPeerAddr;
    UCHAR szPeerName[IKE_PEER_NAME_MAX_LEN]; /* IKE Peer name*/
}IKE_WARN_IKESA_S;

/* This structure is used to provide info for the sub warning types
IKE_WARN_SA_NEGOTIATE_P2
*/
typedef struct tagIKE_WARN_IPSECSA
{
    ULONG ulWarnType;
    ULONG ulSAConnId; /* SA connection ID */
    ULONG ulPeerAddr;
    UCHAR szPeerName[IKE_PEER_NAME_MAX_LEN]; /* IKE Peer name*/
    ULONG ulSeqNum;                /* Concatenation of IPSEC policy sequence number and ACL Rule ID*/
    CHAR szPolName[IKE_IPSECMAPNAME_LEN]; /* IPsec policy name */
    ULONG ulIfIndex;  /* B210 : Warning Enhancement */
}IKE_WARN_IPSECSA_S;

/* This structure is used to provide info for the sub warning types
IKE_WARN_HOUSEKEEP
*/
typedef struct tagIKE_WARN_HOUSEKEEP
{
    ULONG ulWarnType;
    UCHAR szPeerName[IKE_PEER_NAME_MAX_LEN]; /* IKE Peer name*/
}IKE_WARN_HOUSEKEEP_S;

#define IKE_WARNING_ID  0x00010000

/* This enum defines the main warning types */
typedef enum tagIKE_WARNING_ID_E
{
    IKE_WARN_SA_NEGOTIATE    = IKE_WARNING_ID,
    IKE_WARN_SA_NEGOTIATE_P1,
    IKE_WARN_SA_NEGOTIATE_P2,
    IKE_WARN_EVENT,
    IKE_WARN_HOUSEKEEP,
    IKE_WARN_MAX_ENUM_VALUE  = 0x7FFFFFFF /* For 4 byte alignment */
}IKE_WARNING_ID_E;

/* sub warning type corresponding to IKE_WARN_SA_NEGOTIATE and IKE_WARN_EVENT. */
typedef enum tagIKE_WARNING_SA
{
    IKE_WARN_HASH_MISMATCH,                                 /* 0 */
    IKE_WARN_DPD_HASH_MISMATCH,                             /* 1 */
    IKE_WARN_MAX_MODECFG_ADDR,                              /* 2 */
    IKE_WARN_INTERFACE_DELETED,                             /* 3 */
    IKE_WARN_SADELETE_PEERDEAD,                             /* 4 */
    IKE_WARN_SADELETE_USER,                                 /* 5 */
    IKE_WARN_SADELETE_INTFPOLREMOVED,                       /* 6 */
    IKE_WARN_SADELETE_P2,                                   /* 7 */
    IKE_WARN_SADELETE_REMOTE,                               /* 8 */
    IKE_WARN_SADELETE_BRDPLGOUT,                            /* 9 */
    IKE_WARN_SADELETE_INTFDEL,                              /* 10 */
    IKE_WARN_SADELETE_USERBYPEER,                           /* 11 */
    IKE_WARN_SADELETE_HARDEXPIRE,                           /* 12 */
    IKE_WARN_SADELETE_HARDREAUTH,                           /* 13 */
    IKE_WARN_SADELETE_USERBYCONNID,                         /* 14 */
    IKE_WARN_MEMSHORTAGE_NOPEER,                            /* 15 */
    IKE_WARN_MEMSHORTAGE_IGNRMODECFGREQ,                    /* 16 */
    IKE_WARN_NO_SA_OR_INVALID_TO_START_REAUTH_OR_REKEY,     /* 17 */
    IKE_WARN_MODECFGADDR_MISMATCH,                          /* 18 */
    IKE_WARN_RCV_IKE_SA_DELETE,                             /* 19 */
    IKE_WARN_RCV_IPSEC_SA_DELETE,                           /* 20 */
    IKE_WARN_SA_MAX_ARRAY,                                  /* For Array Bounds Check */
    IKE_WARN_SA_MAX_ENUM_VALUE = 0x7FFFFFFF /* For 4 byte alignment */
}IKE_WARNING_SA_E;

/* sub warning type corresponding to IKE_WARN_SA_NEGOTIATE_P1 */
typedef enum tagIKE_WARNING_SAP1
{
    IKE_WARN_INVALID_PEER_ADDR,              /* 0 */
    IKE_WARN_INVALID_EXCHANGE_TYPE,          /* 1 */
    IKE_WARN_HEARTBEAT_NEG_FAIL,             /* 2 */
    IKE_WARN_XAUTH_TYPE_MISMATCH,            /* 3 */
    IKE_WARN_NO_PRESHARED_KEY,               /* 4 */
    IKE_WARN_ID_MISMATCH,                    /* 5 */
    IKE_WARN_MODECFG_DISABLED,               /* 6 */
    IKE_WARN_NO_PEER_BY_ID,                  /* 7 */
    IKE_WARN_NO_AUTH_PYLD,                   /* 8 */
    IKE_WARN_NO_GROUPNAME,                   /* 9 */
    IKE_WARN_NO_SRCFORDEST,                  /* 10 */
    IKE_WARN_EAPEXCH_TIMEDOUT,               /* 11 */
    IKE_WARN_DHGROUP_MISMATCH,               /* 12 */
    IKE_WARN_NAT_DETECTED,                   /* 13 */
    IKE_WARN_AUTHENTICATION_FAILURE,         /* 14 */
    IKE_WARN_SA_INIT_TIMEOUT,                /* 15 */
    IKE_WARN_MORE_NO_OF_PROPOSALS,           /* 16 */
    IKE_WARN_AUTH_EXCH_TIMEOUT,              /* 17 */
    IKE_WARN_CERT_VALIDATION_FAIL,           /* 18 */
    IKE_WARN_PH1_SA_TIMEOUT,                 /* 19 *//*B058:added for better Readability*/
    IKE_WARN_NOPEER_FORREMOTEID_P1,          /* 20 */
    IKE_WARN_NOEAPSUPPORT_ONRESPONDER,       /* 21 */
    IKE_WARN_RECVINVLDKE_DHGROUPSAME,        /* 22 */
    IKE_WARN_MEMSHORTAGE_NOSA_P1,            /* 23 */
    IKE_WARN_RECV_INVALID_ID,                /* 24 */
    IKE_WARN_HASH_MISMATCH_P1,               /* 25 */
    IKE_WARN_NO_PROPOSAL_CHOSEN_P1,          /* 26 */
    IKE_WARN_PKTDECRYPT_FAIL_P1,             /* 27 */
    IKE_WARN_MEM_SHORTAGE_P1,                /* 28 */
    IKE_WARN_MAX_SA_P1,                      /* 29 */
    IKE_WARN_INVALID_MAJOR_VERSION,          /* 30 */ /* B211 : Warning Enhancement */
    IKE_WARN_REKEY_HARD_EXPIRE_P1,           /* 31 */
    IKE_WARN_REAUTH_HARD_EXPIRE,             /* 32 */
    IKE_WARN_PRE_SHARED_KEY_MISMATCH,        /* 33 */
    IKE_WARN_INVALID_SIGNATURE,              /* 34 */
    IKE_WARN_INVALID_HASH_INFORMATION,       /* 35 */
    IKE_WARN_LOCAL_ID_NOT_CONFIGURED,        /* 36 */
    IKE_WARN_CERTREQ_NOT_RECEIVED,           /* 37 */
    IKE_WARN_INVALID_KEY_INFORMATION,        /* 38 */
    IKE_WARN_INVALID_ID_INFORMATION,         /* 39 */
    IKE_WARN_CERTIFICATE_UNAVAILABLE,        /* 40 */ /* B214 : Warning enhancement */
    IKE_WARN_INVALID_CERTIFICATE,            /* 41 */
    IKE_WARN_DPP_VENDOR_ID_NEGOTIATION_FAIL, /* 42 */
    IKE_WARN_INVALID_CERTIFICATE_ENCODING,   /* 43 */
    IKE_WARN_LOCAL_ADDR_MISMATCH,            /* 44 */
    IKE_WARN_SA_P1_MAX_ARRAY,                /* For Array Bounds Check */
    IKE_WARN_SAP1_MAX_ENUM_VALUE = 0x7FFFFFFF /* For 4 byte alignment */
}IKE_WARNING_SAP1_E;

/* sub warning type corresponding to IKE_WARN_SA_NEGOTIATE_P2 */
typedef enum tagIKE_WARNING_SAP2
{
    IKE_WARN_TRANSFORM_MISMATCH,            /* 0 */
    IKE_WARN_CRYPTOMAP_GET_FAILED,          /* 1 */
    IKE_WARN_TS_INVALIDPORT,                /* 2 */
    IKE_WARN_TS_MISMATCH,                   /* 3 */
    IKE_WARN_CHILD_SA_NEGOTIATION_TIMEOUT,  /* 4 */
    IKE_WARN_NOPEER_FORREMOTEID_P2,         /* 5 */
    IKE_WARN_NOPEER_FORKEYID_P2,            /* 6 */
    IKE_WARN_MEMSHORTAGE_NOSA_P2,           /* 7 */
    IKE_WARN_TSPROTOID_MISMATCH,            /* 8 */
    IKE_WARN_PKTDECRYPT_FAIL_P2,            /* 9 */
    IKE_WARN_MEM_SHORTAGE_P2,               /* 10 */
    IKE_WARN_MAX_SA_P2,                     /* 11 */
    IKE_WARN_NO_PROPOSAL_CHOSEN_P2,         /* 12 */
    IKE_WARN_RECV_INVALID_ID_INFORMATION,   /* 13 */
    IKE_WARN_REKEY_HARD_EXPIRE_P2,          /* 14 */ /* B211 : Warning Enhancement */
    IKE_WARN_DHGROUP_MISMATCH_P2,           /* 15 */
    IKE_WARN_SA_P2_MAX_ARRAY,               /* For Array Bounds Check */
    IKE_WARN_SAP2_MAX_ENUM_VALUE = 0x7FFFFFFF /* For 4 byte alignment */
}IKE_WARNING_SAP2_E;

/* sub warning type corresponding to IKE_WARN_HOUSEKEEP */
typedef enum tagIKE_WARNING_HOUSEKEEP
{
    IKE_WARN_DEADPEER,                       /* 0 */
    IKE_WARN_IGNMODECFGREQ_PAFRCHD,          /* 1 */
    IKE_WARN_MODECFGRPLY_PAFRECHD,           /* 2 */
    IKE_WARN_MAX_MODECFG_ADDRESS,            /* 3 */
    IKE_WARN_HOUSEKEEP_MAX_ARRAY,            /* For Array Bounds Check */
    IKE_WARN_HOUSEKEEP_MAX_ENUM_VALUE = 0x7FFFFFFF /* For 4 byte alignment */
}IKE_WARNING_HOUSEKEEP_E;

/*B500 - SGSN-CMD Registration*/

/*Kuldeep : B514 Changes*/
#define IKE_ID_MAX_LENGTH               131

/* V1R3_DEV_BEGIN: XAUTH */
#define IKE_XAUTH_VID_LENGTH            8
#define IKE_DPD_VID_LENGTH              16
#define IKE_MODECFG_VID_LENGTH              16

#define IKE_CONFIG_STRING_LENGTH     80

typedef struct tagIKE_PROPOSAL_CONFIG_S
{
    ULONG ulProposalNum;      /* Ike Proposal Number <1-99>*/
    ULONG ulAuthMethodType;   /* PreShared Method - 8 &  EAP Method - 18*/
    ULONG ulEncryptionType;   /* DES - 2 , 3DES - 3, AES_128 - 11,AES_192 - 12
                                  AES_256 - 13 and (AES - 10 only for Hardware Encr)*/
    ULONG ulAuthAlgorithmType;/* MD5 - 4 SHA1 - 5*/
    ULONG ulDHGroupType;      /* DH Group 1 or 2*/
    ULONG ulIsakmpSaLifeTime; /* ISAKMP SA lifetime <60-604800> Seconds*/
    ULONG ulReauthLifeTime;   /* Reauthentication-Inteval For IKE-V2
                                    <300-86400> Seconds*/
    ULONG ulPrfNum;           /*Prf Type MD5-14, SHA1- 15. Used only for IKE-V2*/
}IKE_PROPOSAL_CONFIG_S;

typedef struct tagIKE_PEER_CONFIG_S
{
    CHAR szPeerName[IKE_CONFIG_STRING_LENGTH];  /*Peername of <1-16> characters including '\0'*/
    CHAR szPresharedKey[IKE_CONFIG_STRING_LENGTH]; /*Key of <1-128> characters including '\0'*/
    CHAR szVPNName[IKE_CONFIG_STRING_LENGTH];      /*VPN instance name of <1-32> chars including '\0'*/
    CHAR szRemoteID[IKE_CONFIG_STRING_LENGTH];   /*Remote Name for the peer of <1-32> chars
                                                including '\0'*/
    UCHAR szGroupName[IKE_CONFIG_STRING_LENGTH];      /*GroupName for Key ID of <1-64> chars incl '\0'*/
    UCHAR szModeCfgVendorId[IKE_CONFIG_STRING_LENGTH]; /*Vendor Id of <1-16> chars incl '\0'*/

    /*Ipv6: Security Support*/
    UCHAR ucPeerVer; /*Peer IP version 4 or 6 */
    UCHAR ucReserved[3]; /*For 4-bytes alignment*/

    ULONG ulIkeVersion;    /*Ike Version 1 or 2*/
    ULONG ulExchangeMode;  /*Main - 2 or Aggressive Mode - 4   */
    ULONG ulProposalNum;   /*IKE-Proposal Number <1-99>   */
    ULONG ulNatMode;       /*Nat enable - 0 or disable - 1    */
    ULONG ulLocalIdType;   /*IPSEC_ID_IPV4_ADDR - 1
                             IPSEC_ID_FQDN      - 2
                             IPSEC_ID_KEY_ID    - 11 */
    ULONG ulModecfgMode;    /*Modecfg enable - 0 or disable - 1  */
    ULONG ulPeerIdType;     /*IPSEC_ID_IPV4_ADDR - 1
                             IPSEC_ID_FQDN      - 2
                             IPSEC_ID_KEY_ID    - 11*/
    ULONG ulStartRemoteAddress;  /*Starting remote IP Address <X.X.X.X>*/
    ULONG ulEndRemoteAddress;    /*Ending remote IP Address <X.X.X.X>*/
}IKE_PEER_CONFIG_S;

typedef struct tagIKE_DPD_CONFIG_S
{
    CHAR szPeerName[IKE_CONFIG_STRING_LENGTH];  /*Peername of <1-16> characters including '\0'*/
    ULONG ulIdleTime;   /* Value of the idle time during configuration in
                           seconds <10-3600>*/
    USHORT usRetransmitInterval; /* The value of the retransmit interval <3-30>*/
    USHORT usRetries;           /* The maximum number of DPD retry <3-10> */
    ULONG ulOpMode;             /* The mode UNDO - 1, Set - 0*/
    ULONG ulAttrFlag;   /* Attrribute flag. IdleTime - 1, Retransmit Limit  - 2
                            RetryLimit - 4. Do the OR of these values*/

    UCHAR ucDpdMode;    /* On-Demand / Periodic */
    UCHAR ucHashSeq;    /*Dpd Hash Sequence  Hash-Notify - 1 and
                                            Notify-Hash - 2*/
    UCHAR ucResv[2];
}IKE_DPD_CONFIG_S;

/*Xauth Feature is available only in IKE-V1*/
typedef struct tagIKE_XAUTH_CONFIG_S
{
    CHAR szPeerName[IKE_CONFIG_STRING_LENGTH];  /*Peername of <1-16> characters including '\0'*/

    /* Xauth Attributes */
    UCHAR szUsername[IKE_CONFIG_STRING_LENGTH]; /* Pointer to string containing username Len<8-63>*/
    UCHAR szPassword[IKE_CONFIG_STRING_LENGTH]; /* Pointer to string containing PSWD Len<8-31>*/
    UCHAR szPasscode[IKE_CONFIG_STRING_LENGTH]; /*Xauth - Passcode <8-32> characters incl'\0'*/
    UCHAR szDomainName[IKE_CONFIG_STRING_LENGTH]; /* Pointer to string containing Domain name Len<8-63>*/

    UCHAR ucXauthMode;     /*Static - 1 or Dynamic -2  or None -0*/
    UCHAR ucXauthType;     /*Generic -1, RADIUS-CHAP -2, OTP - 4
                                S/KEY-8 */
    UCHAR ucOTPPswdMode;   /*HEX - 0 or Encoded Mode - 1*/
    UCHAR ucHashSeq;       /*Radius chap hash sequence
                            ID-CHALLENGE-SECRET-1
                            ID-SECRET-CHALLENGE -2 */

}IKE_XAUTH_CONFIG_S;

/*Sunil: IKE packet trace*/
#define IKE_HOOK_SEND                       0
#define IKE_HOOK_RECEIVE                    1

typedef ULONG (*IKE_GetAppControlPacket_HOOK_FUNC)(ULONG ulIfIndex,
                                ULONG ulSndOrRcv, ULONG ulProtocalType,
                                ULONG ulSubProtocalType, ULONG ulPktLen,
                                UCHAR  *pucBuf);

/*GGSN*/
/* Structure to store HA statistics of IKE module */
typedef struct tagIKE_HA_STATS_S
{
    ULONG ulBatchBckupCounter;
    ULONG ulBatchBckupSACnt;
    ULONG ulRealtimeBckupAddSA;
    ULONG ulRealtimeBckupDelSA;
    ULONG ulRealtimeBckupSndWndw;
    ULONG ulRealtimeBckupRcvWndw;
    ULONG ulRoutineBckupCount;
    ULONG ulRoutineBckupMsgCnt;
    ULONG ulRealtimeBckupAddSAFail;
    ULONG ulBatchBckupSAFailCnt;
    ULONG ulRealtimeBckupDelSAFail;
    ULONG ulRealtimeBckupSndWndwFail;
    ULONG ulBatchBkcupPh2SAFailCnt;
    ULONG ulPh1SANotFound;
    ULONG ulRoutineBckupRstWndFail;
    ULONG ulRealTimeBkpFail;
    ULONG ulSendRealTimeBkpFail;
    ULONG ulSendBatchBkpFail;
    ULONG ulSendRoutineBkpFail;
}IKE_HA_STAT_S;

/* Structure to store statistics for IKEv2 SA deletion */
typedef struct tagIKEV2_SADELSTATS_S
{
    /* SA deleted by DPD */
    ULONG ulDeleteByDPD;

    /* Delete all SA from user */
    ULONG ulDeleteAll;

    /* Delete SA by IPSec policy */
    ULONG ulDeleteByPolicy;

    /* Delete all Phase2 SA event */
    ULONG ulDeleteAllChildSA;

    /* Delete SA by remote-address */
    ULONG ulDeleteByRemoteAddress;

    /* Delete SA by board plugout */
    ULONG ulDeleteByBoardPlgOut;

    /* Delete SA by interface delete */
    ULONG ulDeleteByIfDelete;

    /* SA deleted by peer */
    ULONG ulDeleteByPeer;

    /* SA deleted by hard expire */
    ULONG ulDeleteByHardExp;

    /* SA deleted by hard re-auth */
    ULONG ulDeleteByHardReAuth;

    /* SA deleted by connection ID */
    ULONG ulDeleteByConnId;

    /* SA deleted by VRF index */
    ULONG ulDeleteByVrfIndex;
}IKEV2_SADELSTATS_S;

/*IKE Message releated stats*/
typedef struct tagIKE_MSG_STAT
{
    ULONG ulIKEMsgReceived;
    ULONG ulIKEMsgSent;
    ULONG ulIKEv1P1RekeySuccess;
    ULONG ulIKEv1P2RekeySuccess;
    ULONG ulIKEv1P1ExchagneTO;
    ULONG ulIKEv1P2ExchagneTO;

    ULONG ulIKEv2IkeSaRekeySuccess;
    ULONG ulIKEv2ChildSaRekeySuccess;
    ULONG ulIKEv2IkeSaRekeyFail;
    ULONG ulIKEv2ChildSaRekeyFail;
    ULONG ulIKEv2AuthExchangeTO;

    /* B114 : Updated statistics for expire and acquire messages */
    ULONG ulIKEExpireReceive;
    ULONG ulIKEAcquireReceive;
    ULONG ulIKEAcquireDropped;
    ULONG ulIKEExpireDropped;
    ULONG ulIKEReplaceReceive;
    ULONG ulTrptNullForDpdMsg;
    ULONG ulIKEv2RespHalfOpenConnNum; /* LOOP_OPT */
    ULONG ulIKEv2InitHalfOpenConnNum; /* LOOP_OPT */
    ULONG ulIKEv2ReAuthSuccess;      /* S9300 Re-Auth Success scenario */
    ULONG ulIKEv2SoftReAuth;
    ULONG ulIKEv2SoftReAuthDropInvalidState;
    ULONG ulIKEv2SoftReAuthDropNoChild;
    ULONG ulIKEv2HardReAuth;
    ULONG ulIKEv2IkeSaSoftExpire;
    ULONG ulIKEv2IkeSaHardExpire;
    ULONG ulIKEv2Ph2SaNotFoundForSoftExpire;
    ULONG ulIKEv2Ph2SaNotFoundForHardExpire;
    ULONG ulIKEv1Ph2SoftExpire;
    ULONG ulIKEv1Ph2HardExpire;
    ULONG ulIKEv1Ph2SaNotFoundForSoftExpire;
    ULONG ulIKEv1Ph2SaNotFoundForHardExpire;
    ULONG ulIKEv1TempSaDeleteFrmExchRelease;
    ULONG ulIKETrptNullWhileMsgSend;
    ULONG ulIKETtgMsgSendErr;
    ULONG ulIKEDupIkeSaExpire;
    ULONG ulIKEDupChildSaExpire;
    ULONG ulIKEv2EAPInitiateFailed;
    ULONG ulIKEv2EAPSendMsgFailed;
    ULONG ulIKEv2EapTimeout;
    ULONG ulIKEv2EapSuccess;
    ULONG ulIKEv2EapFail;
    ULONG ulIKEModeCfgAttributeReqFailed;
    ULONG ulIKEv2ModeCfgRcvAuthExchCPPayload;
    ULONG ulIKEv2ModeCfgRcvInfoExchCPPayload;
    ULONG ulIKEv2ModeCfgSendServerReply;
    ULONG ulIKEModeCfgTimeout;

    /* AP-REQ: Validate Peer auth method */
    ULONG ulRemoteAuthMethodMismatch;
    ULONG ulIKEIpv4GetSourceByDestFail;
    ULONG ulIKEIpv6GetSourceByDestFail;

    /* GGSN: INcremented on successful allocation of IKE SPI from GGSN */
    ULONG ulGetIkeSpi;

    /* GGSN: INcremented when IKE SPI allocation is un-successful from GGSN */
    ULONG ulGetIkeSpiErr;

    /* GGSN: INcremented on successful allocation of IKE SPI from GGSN */
    ULONG ulGetIkeSpiForRekey;

    /* GGSN: INcremented when IKE SPI allocation is un-successful from GGSN */
    ULONG ulGetIkeSpiForRekeyErr;

    /* GGSN: INcremented on successful REl of IKE SPI from GGSN */
    ULONG ulRelIkeSpi;

    /* GGSN: INcremented when IKE SPI release is un-successful from GGSN */
    ULONG ulRelIkeSpiErr;

    /* SA delete due to duplicate IPSec SPI */
    ULONG ulDuplicateSPI;

    /* Statistics related to IKEV2 SA deletion */
    IKEV2_SADELSTATS_S stSADeleteStats;

    /* Statistics related to HA */
    IKE_HA_STAT_S stHAStats;

    /* AP B050: Stats to determine the Trigger happened in IKE DPD */
    ULONG ulIKEv1DPDCount;
    ULONG ulIKEv2DPDCount;

    /* To Check if the selected Policy is droped due to invalid config */
    ULONG ulResponderSelectedTransUnUsable;
    ULONG ulInitiatorSelectedTransUnUsable;

    /* B057 : Stats to determine the key deletion */
    ULONG ulIKEInboundKeyDelete;
    ULONG ulIKEOutboundKeyDelete;

    /* set socket option returns error hence message dropped in udp while sending message */
    ULONG ulMsgDropSetSockOptErr;
    ULONG ulMsgSendFailInUDP;

    ULONG ulIKEDropPktArriveOnTunnel;
    ULONG ulIKETunnelPktDropAsIntfDown;
    ULONG ulIKERecvTunnelPktSuccess;

    /* B202 : Addition of New statistics */
    ULONG ulIKEv1Ph1SaNegFail;
    ULONG ulIKEv1Ph2SaNegFail;
    ULONG ulIKEv2Ph1SaNegFail;
    ULONG ulIKEv2Ph2SaNegFail;

}IKE_MSG_STAT_S;

typedef ULONG (*IKE_PKI_Download_Notify)(VOID *pstPKIObject, ULONG ulFlag, ULONG ulReqIdentifier);

typedef struct tagIKE_PKI_REGISTER_FUNC_S
{
    /* Function used by IKE to trigger product to download CERT from
       the URL given by IKE */
    ULONG (*pfSEC_ADP_PKI_GetCertFromURL) (CHAR *szObjectName,
                                            CHAR *szURLInfo,
                                            USHORT usUrlLen,
                                            UCHAR *pucCertHash,
                                            ULONG ulReqIdentifer);

    /* Function used by IKE to trigger CRL download by product */
    ULONG (* pfSEC_ADP_PKI_DownloadCRL) (CHAR *szObjectName,
                                        VOID *pstCdpList,
                                        ULONG ulReqIdentifier);

    /* Function used by IKE to trigger OCSP download by product */
    ULONG (*pfSEC_ADP_PKI_DownloadOCSP) (UCHAR* pszContextName,
                                    VOID *pvObject,
                                    VOID *pvCertList, /* SEC_List_S* */
                                    ULONG ulAppData,
                                    IKE_PKI_Download_Notify pfOCSPCallback);

    /* Function used by IKE to get the object pointer by name */
    ULONG (*pfSEC_ADP_PKI_GetObjectByName) (CHAR *szObjname, VOID **ppvObj);

    /* Function used by IKE to get the object pointer by name */
    ULONG (*pfSEC_ADP_PKI_GetObjectByDomain) (CHAR *szPkiDomain, VOID **ppvObj);

    ULONG (*pfSEC_ADP_PKI_DeleteObject) (CHAR *szPkiDomain, VOID *pvObj);

    ULONG (*pfPKI_ADP_ctxRemoveAllOCSPResp)(CHAR *szCtxName);

    ULONG (*pfPKI_ADP_GetCertCheckType)(CHAR *szCtxName);

    /* Function used by IKE to trigger CRL download by product */
    ULONG (*pfSEC_ADP_PKI_DownloadCRL_NotifyCallbak) (UCHAR* pszContextName,
                                                        VOID *pstObject,
                                                        VOID *pvCertList,
                                                        ULONG ulAppData,
                                                        IKE_PKI_Download_Notify pfCRLCallback);

}IKE_PKI_REGISTER_FUNC_S;

/* Notify stat */
typedef struct tagIKEV2_NOTIFY_STAT
{
    USHORT usUnsupportedCriticalPayload;
    USHORT usInvalidIkeSpi;
    USHORT usInvalidMajorVersion;
    USHORT usInvalidSyntax;
    USHORT usInvalidMsgId;
    USHORT usInvalidIpsecSpi;
    USHORT usNoPropChosen;
    USHORT usInvalidKe;
    USHORT usAuthFailed;
    USHORT usSinglePairReq;
    USHORT usNoAddSA;
    USHORT usIntrnlAddrFail;
    USHORT usCpReq;
    USHORT usTsUnAccept;
    USHORT usInvalidSelector;
    USHORT usInitialContact;
    USHORT usSetWindowSize;
    USHORT usAddTsPossible;
    USHORT usIpCompSupport;
    USHORT usNatDetectSrcIp;
    USHORT usNatDetectDestIp;
    USHORT usNotifyCookie;
    USHORT usUseTransportMode;
    USHORT usHttpCertLookupSupp;
    USHORT usRekeySA;
    USHORT usTfcPaddNotSupp;
    USHORT usNoFirstFrag;
    USHORT usAuthLifeTime;
    USHORT usDeletOldChildSa;
    USHORT usPad;
}IKEV2_NOTIFY_STAT_S;

/* PKI stat */
typedef struct tagIKE_PKI_STAT
{
    USHORT usCertValidationFail;
    USHORT usCrlDownloadReq;
    USHORT usCrlDownloadFail;
    USHORT usSentCertIDValidationFail;
    USHORT usRecvCertIDValidationFail;
    USHORT usSentCertAlgValidationFail;
    USHORT usRecvCertAlgValidationFail;
    USHORT usAuthFail;

    /*Nagendra-OCSP*/

    USHORT usOcspInbandReqForm;
    USHORT usOcspInbandRspForm;
    USHORT usOcspDownloadReq;
    USHORT usOcspDownloadReply;

    USHORT usCertValidateOcspDownTimeout;
    USHORT usFormPayloadOcspDownTimeout;

    USHORT usCrlDownloadTimeout;
    USHORT usOcspDownloadFail;
    USHORT usGetOcspReqFail;
    USHORT usRecvSgnDataFrmProduct;
}IKE_PKI_STAT_S;

typedef struct tagIKEv1_DEFAULT_S
{
    ULONG ulIKEv1Ph1ExchTimout;
    ULONG ulIKEv1Ph2ExchTimout;
}IKEV1_DEFAULT_S;

typedef struct tagIKEv2_DEFAULT_S
{
    ULONG ulIKEv2SaInitExchTimeout;
    ULONG ulIKEv2AuthExchTimeout;
    ULONG ulIKEv2ChildExchTimeout;
}IKEV2_DEFAULT_S;


/* IPSEC6.STORY.04 - Moved from ike_pub_intrnl.h, used by IPSec */
/* Distinguishes the message type in the event for DPD, MODECFG and XAUTH */
typedef enum IKE_EVENT_MSGTYPE
{
    /* IPSEC6.ITR2.STORY4 - Removed IKE_DPD_MSG event type*/
    IKE_XAUTH_MSG = 1,                          /*1*/
    IKE_MODECFG_APP_REQ,                        /*2*/
    IKE_MODECFG_ADDR_DEL,                       /*3*/
    IKE_MODECFG_PEERADDR_DEL,                   /*4*/
    IKE_DEL_ALL_SA_PEER,                        /*5*/
    IKE_INIT_HRTBT_TRANS_PEER,                  /*6*/
    IKE_MODECFG_APPUNREG,                       /*7*/
    IKE_BOARD_PLUG_OUT,                         /*8*/
    IKE_INTERFACE_PLUG_OUT,                     /*9*/
    IKE_IFDELETE,                               /*10*/
    IKE_VPNDELETE,                              /*11*/
    IKE_POLICYDELETE,                           /*12*/
    IKE_REMOTEDELETE,                           /*13*/
    IKE_PH1PH2SADELETE,                         /*14*/
    IKE_PFKEYQUEUE,                             /*15*/
    IKEV2_BOARD_PLUG_OUT,                       /*16*/
    IKEV2_IFDELETE,                             /*17*/
    IKEV2_VPNDELETE,                            /*18*/
    IKEV2_POLICYDELETE,                         /*19*/
    IKEV2_REMOTEDELETE,                         /*20*/
    IKEV2_PH1PH2SADELETE,                       /*21*/ /*delete all ph1 and ph2 SA's */
    IKEV2_PH2SADELETE,                          /*22*/ /*delete all ph2 SA's*/
    IKEV2_SPIDELETE,                            /*23*/ /*delete particular SPI's*/
    IKEV2_CONNDELETE,                           /*24*/  /*delete the SA per connection ID*/
    IKEv2_PROCESS_EAP_COMPLETE,                 /*25*/
    IKEV2_PEERDELETE,                           /*26*/  /*delete SA by PeerName*/
    IKEV2_IKESADELETE,                          /*27*/ /*de*/
    IKEV2_SH_BOARD_PLUG_OUT,                    /*28*/
    IKEV2_SH_IFDELETE,                          /*29*/
    IKEV2_PENDINGCHILD_DEL,                     /*30*/
    IKE_EVENT_MSGTYPE_MAX_ENUM_VALUE,           /*31*//* For 4 byte alignment */
    IKE_SOCKET_CLOSE,                           /*32*/ /* Defect AC4D06272*/
    IKE_SETRESET_SOCKET_OPTION,                 /*33*/ /* To set reset the socket option */

    /* Sumangala : Added for New API requirement from SGSN */
    IKE_PH1PH2SADELETEBYPEER,                   /*34*/ /* To reset SA by peer address */
    IKEV2_PH1PH2SADELETEBYPEER,                 /*35*/ /* To reset SA by peer address */
    IKE_PH1PH2SADELETEBYPEER_DNT_NOTIFY,        /*36*/ /*To reset SA by peer address*/
    IKEV2_PH1PH2SADELETEBYPEER_DNT_NOTIFY,      /*37*/ /* To reset SA by peer address */
    IKEV2_PH1PH2SADELETEBYVPNINDEX,             /*38*/  /*Anoop_VPN - SA delete on VrfIndex delete*/

    /* Defect ID: AC4D07447 - IKEv1_DSCP Phase2SA batch delete */
    IKE_PH2DELETEBYPEER,                        /* 39  */

    /* AC4D07706 : New requirement to delete IKEv1 ready/non-ready state SA's */
    IKE_PH1PH2SADELETE_SYNC,                    /*40*/ /* To reset SA by sync call */

    /* Anoop_Added for PKI  */
    IKEV2_URLCERT_DWNLD,                        /* 41  */
    IKE_CRL_DOWNLOAD_COMPLETE,                  /* 42 */

    /* IPSEC6_Changes */
    IKEV1_ALLPH1SADELETE,                       /* 43 */

    /* IPSEC6.ITR2.STORY5 */
    IKEV1_PH1SADELETEBYCONNID,                  /* 44 */



    /*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
    IKE_PH2SADELETEBYPEERINDEX,                 /* 45 */
    IKE_PH2SADELETEBYPEERINDEX_DNT_NOTIFY,      /* 46 */
    IKEV2_PH2SADELETEBYPEERINDEX,               /* 47 */
    IKEV2_PH2SADELETEBYPEERINDEX_DNT_NOTIFY,    /* 48 */

    IKE_PH1PH2SADELETEBYPEERINDEX,              /* 49 */
    IKEV2_PH1PH2SADELETEBYPEERINDEX,            /* 50 */
    IKEV2_PH1PH2SADELETEBYPEERINDEX_DNT_NOTIFY, /* 51 */
    IKE_PH1PH2SADELETEBYPEERINDEX_DNT_NOTIFY,   /* 52 */
    IKEV1_START_PH1_REKEY,                      /* 53 */
    IKEV2_START_PH1_REAUTH,                     /* 54 */
    IKE_POLICYPH1SADELETE,                      /* 55 */

    /*Ipv6: Security Support*/
    IKEV1_DEL_ALL_V6_SA_PEER,                   /* 56 */

    /* GGSN EAP: Start */

    IKEV2_RESPONDER_PROCESSMSG_FROM_EAP,        /* 57 */
    IKEV2_RESPONDER_EAP_COMPELTE,               /* 58 */

    /* GGSN EAP: End */

    IKE_MODECFG_AAA_RESPOND_ATTR,               /* 59 */

    IKEV2_INITIATE_PENDING_REQ,                 /* 60 */
    IKEV2_WINDOW_ROUTINEBACKUP,                 /* 61 */
    IKEV2_POLICYDELETE_DNTNOTIFY,               /* 62 */
    IKE_CRLOCSP_DOWNLOAD_COMPLETE,              /* 63 */

    /* To set reset the ike6 socket option */
    IKE6_SETRESET_SOCKET_OPTION,                /* 64 */
    IKEV2_EVENT_BYTE_ALIGNMENT = 0x7FFFFFFF
}IKE_EVENT_MSGTYPE_E;

/*S9300.ITR2.STORY.1*/
typedef enum IKE_HASH_SEARCH
{
    IKE_HASH_SEARCH_PEER = 1,              /*1*/
    IKE_HASH_SEARCH_CHECKPROPOSALUSED,     /*2*/
    IKE_HASH_SEARCH_ADDRCONFLICT,          /*3*/
    IKE_HASH_SEARCH_OBJECTINUSE,           /*4*/
    IKE_HASH_SEARCH_PEERREMOTEADDR,        /*5*/
    IKE_HASH_SEARCH_BYREMOTEID,            /*6*/
    IKE_HASH_GENERIC_RET,                  /*7*/

}IKE_HASH_SEARCH_E;

/*AR-PERFORMANCE*/
/*Hash size 101 is sufficient to hold 3072 SAs - where in on avergage 30 Pees would be stored
in one location */
#define IKE_PEER_HASH_BUCKET_MASK                    101

#define IKE_EV_PFKEYQUEUE                   0x80002000

typedef enum tagIKE_DEBUG_LEVEL
{
    IKE_DEBUG_LEVEL_INFO,
    IKE_DEBUG_LEVEL_ERROR,
    IKE_DEBUG_LEVEL_WAR,
    IKE_DEBUG_LEVEL_MAX,
    IKE_MAX_DEBUG_LEV_ENUM_VALUE = 0x7FFFFFFF
}IKE_DEBUG_LEVEL_E;

#define IKE_HRBT_SEQNUM_OLD             0
#define IKE_HRBT_SEQNUM_NEW             1

/*
using the macro IKE_HASH_SHA and removing the duplicate.
*/
#define IKE_MAX_DEL_TIMEOUT_IN_SEC         300
#define IKE_MIN_DEL_TIMEOUT_IN_SEC         15

/*V1R3_DEV_END: feature*/
typedef struct tagIKE_SA_Display
{
    ULONG (*pfIKE_OpenObject_SA)(ULONG *pulSAWaitListHandle);
    ULONG (*pfIKE_CloseObject_SA)(ULONG *pulSAWaitListHandle);
    ULONG (*pfIKE_GetBulkSA)(ULONG ulSAWaitListHandle,
                           ULONG ulNumOfSAWanted,
                           ULONG *pulNumOfSAReturn,
                           IKE_SA_CONTENT_S *pstSABuf,
                           UCHAR ucPhase);
    ULONG (*pfIKE_GetGlobalInfo)(IKE_GLOBAL_CONTENT_S *pstIKEGlobalContent);
    ULONG (*pfIKE_SH_Display_SABuf)(IKE_SA_CONTENT_S *pstSABuf,
                                     CHAR *szShowBuf,
                                     ULONG ulDisplayType);
}IKE_SA_DISPLAY_S;


/* IKEv1_DSCP Anoop Added */
#define IKE_NO_DSCP                     0xFE
#define IKE_DSCP_ANY                    0xFF
#define IKE_DSCP_VALUE_MAX              63

/*S9300_Moved from Pub internal Hdr File*/

/*Added function pointer for S9300 warning messages.*/
typedef VOID (*pfIKE_WarningOut)(ULONG ulWarningID, VOID* pWarnParam);

/*Iteration2: Story12: Maintainance*/
typedef struct tagIKE_PFKEYV2_STATS_S
{
    ULONG ulAcquireRcvd;
    ULONG ulExpireRcvd;
    ULONG ulGetMapSent;
    ULONG ulGetSPISent;
    ULONG ulGrpSPISent;
    ULONG ulFillSent;
    ULONG ulDeleteSent;
    ULONG ulDeleteRcvd;
    ULONG ulDPDNotifySent;
    ULONG ulDPDTriggerRcvd;
    ULONG ulModecfgNotifySent;
    ULONG ulModecfgTriggerRcvd;
    ULONG ulModecfgDelAddrRcvd;
}IKE_PFKEYV2_STATS_S;

typedef struct tagIKE_GETPOLICY_FAIL_S
{
    ULONG ulSrcAddr;
    ULONG ulDestAddr;
    ULONG ulPeerIndex;
}IKE_GETPOLICY_FAIL_S;


typedef struct tagIKE_PFKEYV2_FAIL_STATS_S
{
    ULONG ulAcquireRcvdFail;
    ULONG ulExpireRcvdFail;
    ULONG ulGetPolicyFail;
    ULONG ulGetSPISentFail;
    ULONG ulGrpSPISentFail;
    ULONG ulFillSentFail;
    ULONG ulDeleteSentFail;
    ULONG ulDeleteRcvdFail;
    ULONG ulDPDNotifySentFail;
    ULONG ulModecfgNotifySentFail;
    ULONG ulMsgParseFail;
    IKE_GETPOLICY_FAIL_S stGetPolicyFail;
}IKE_PFKEYV2_FAIL_STATS_S;

/*B058: Stats improvement for exchange IKEv2*/
typedef struct tagIKE_V2EXCHANGE_STATS_S
{
    ULONG ulRespRecvAuthReq;            /*Responder receive IKE auth request*/
    ULONG ulInRecvAuthResponse;         /*Initiator receive IKE auth response*/
    ULONG ulInSendAuthReq;              /*Initiator send IKE auth request*/
    ULONG ulRespSendAuthResponse;       /*Responder send IKE Auth response*/
    ULONG ulRespRecvChildSAReq;         /*Responder receive child SA request*/
    ULONG ulInRecvChildSAResponse;      /*Initiator receive child Sa response*/
    ULONG ulInSendChildSAReq;           /*Initiator send child SA request*/
    ULONG ulRespSendChildSAResponse;    /*Responder send child SA response*/
    ULONG ulRespRecvInfoReq;            /*Responder receive information request*/
    ULONG ulInRecvInfoResponse;         /*Initiator receive information response*/
    ULONG ulInSendInfoReq;              /*Initiator send information request*/
    ULONG ulRespSendInfoResponse;       /*Responder send information response*/
    ULONG ulRespRecvInitReq;            /*Responder receive SA init request*/
    ULONG ulInRecvInitResponse;         /*Initiator receive SA init response*/
    ULONG ulInSendInitReq;              /*Initiator send SA init request*/
    ULONG ulRespSendInitResponse;       /*Responder send SA init response*/
    ULONG ulInvalidPacketReceived;      /*Invalid packet received*/
}IKE_V2EXCHANGE_STATS_S;
/*B058: Stats improvement for exchange IKEv1*/
typedef struct tagIKE_V1EXCHANGE_STATS_S
{
    ULONG ulInMmSASent;     /*Initiator Main mode SA message sent */
    ULONG ulInMmSARecv;     /*Initiator Main mode SA message receive*/
    ULONG ulRespMmSASent;   /*Responder Main mode SA message sent*/
    ULONG ulRespMmSARecv;   /*Responder Main mode SA message receive*/
    ULONG ulInMmKESent;    /*Initiator Main mode KE message sent*/
    ULONG ulInMmKERecv;   /*Initiator Main mode KE message receive*/
    ULONG ulRespMmKESent;  /*Responder Main mode KE message sent*/
    ULONG ulRespMmKERecv;  /*Responder Main mode KE message receive*/
    ULONG ulInMmIDSent;    /*Initiator Main mode ID message sent*/
    ULONG ulInMmIDRecv;    /*Initiator Main mode ID message receive*/
    ULONG ulRespMmIDSent;  /*Responder Main mode ID message sent*/
    ULONG ulRespMmIDRecv;  /*Responder Main mode ID message receive*/
    ULONG ulInAmSASent;    /*Initiator Aggressive mode SA message sent*/
    ULONG ulInAmSARecv;    /*Initiator Aggressive mode SA message receive*/
    ULONG ulRespAmSASent;  /*Responder Aggressive mode SA message sent*/
    ULONG ulRespAmSARecv;  /*Responder Aggressive mode SA message receive*/
    ULONG ulInAmHashSent;  /*Initiator Aggressive mode hash message sent*/
    ULONG ulRespAmHashRecv;/*Responder Aggressive mode hash message receive*/
    ULONG ulInQmSASent;    /*Initiator quick mode SA message sent*/
    ULONG ulInQmSARecv;    /*Initiator quick mode SA message receive*/
    ULONG ulRespQmSASent;  /*Responder quick mode SA message sent*/
    ULONG ulRespQmSARecv;  /*Responder quick mode SA message receive*/
    ULONG ulInQmHashSent;  /*Initiator quick mode hash message sent*/
    ULONG ulRespQmHashRecv;/*Responder quick mode hash message receive*/
    ULONG ulRespRecvInfoReq;            /*Responder receive information request*/
    ULONG ulInSendInfoReq;              /*Initiator send information request*/
}IKE_V1EXCHANGE_STATS_S;

#define IKE_DH_HW_RET_OK    1
#define IKE_DH_HW_RET_ERR   0

#define IKE_MAX_ADDR_CNT    32
/* The group on which diffie hellmann calculations are done. */
typedef struct tagIKE_DH_HW_REG_FUNC
{
    /*function that calculates the modp exp in H/w*/
    /*
      vR   should be of type BIGNUM *.
      vA   should be of type BIGNUM *.
      vP   should be of type BIGNUM *.
      vM   should be of type BIGNUM *.
      vCtx should be of type BN_CTX *.

      Please note that the structures BN_CTX and BIGNUM should match the in
      both IKE and the product code.

      THis function should return IKE_DH_HW_RET_OK on success and
      IKE_DH_HW_RET_ERR on error.
     */
    LONG (*pfModExp) (VOID *vR, VOID *vA, VOID *vP, VOID *vM, VOID *vCtx);
}IKE_DH_HW_REG_FUNC;

typedef struct tagIKEV2_SA_PARAM
{
    USHORT usDhGrp;
    USHORT usEnc;
    USHORT usIntegrity;
    USHORT usPrf;
}IKEV2_SA_PARAM_S;

typedef struct tagIKEV1_SA_PARAM
{
    USHORT usDhGrp;
    USHORT usEnc;
    USHORT usIntegrity;
    USHORT usAuthMethod;
}IKEV1_SA_PARAM_S;


/* 1> IKE_ENCRYPT_DES_CBC */
/* 2> IKE_ENCRYPT_3DES_CBC */
/* 3> IKE_ENCRYPT_AES_CBC 128 */
/* 3> IKE_ENCRYPT_AES_CBC 192 */
/* 3> IKE_ENCRYPT_AES_CBC 256 */
#define IKE_MAX_SUPP_ENCR_ALG       5

/*
    IKE_HASH_MD5,
    IKE_HASH_SHA,
    IKE_HASH_AES_XCBC_96,
    IKE_HASH_SHA2_256,
    IKE_HASH_SHA2_384,
    IKE_HASH_SHA2_512
*/
#define IKE_MAX_SUPP_INTEGRITY_ALG  6

/*
    IKE_HASH_MD5,
    IKE_HASH_SHA,
    IKE_HASH_SHA2_256,
    IKE_HASH_SHA2_384,
    IKE_HASH_SHA2_512
*/
#define IKEv1_MAX_SUPP_INTEGRITY_ALG  5

/*
    IKE_HASH_MD5,
    IKE_HASH_SHA,
    IKE_HASH_AES_XCBC_128
*/
#define IKE_MAX_SUPP_PRF_ALG        3

/*
    IKE_GROUP_DESC_MODP_768,
    IKE_GROUP_DESC_MODP_1024,
    IKE_GROUP_DESC_MODP_1536,
    IKE_GROUP_DESC_MODP_2048
*/
#define IKE_MAX_SUPP_DH_GRP         5

/* IKE authentication method attributes
#define IKE_AUTH_PRE_SHARED
#define IKE_AUTH_DSS
#define IKE_AUTH_RSA_SIG
*/
#define IKE_MAX_SUPP_AUTH_METHOD    3

typedef struct tagIKE_SUPPORTED_ENCR_ALG
{
    USHORT usAlg;
    USHORT usKeyLen;
}IKE_SUPPORTED_ENCR_ALG_S;

/*Post B039: Proposal payload initialisation*/

/*Post B039: Supported Encryption algorithms*/
#define IKE_SUPPORT_ENCRYPT_DES_CBC             0x00000001
#define IKE_SUPPORT_ENCRYPT_3DES_CBC            0x00000002
#define IKE_SUPPORT_ENCRYPT_AES_CBC_128         0x00000004
#define IKE_SUPPORT_ENCRYPT_AES_CBC_192         0x00000008
#define IKE_SUPPORT_ENCRYPT_AES_CBC_256         0x00000010

/*Post B039: Supported authentication algorithms*/
#define IKE_SUPPORT_INTEGRITY_MD5               0x00000001
#define IKE_SUPPORT_INTEGRITY_SHA               0x00000002
#define IKE_SUPPORT_INTEGRITY_AES_XCBC_96       0x00000004
/*HS:Sha2-support*/
#define IKE_SUPPORT_INTEGRITY_SHA2_256          0x00000008
#define IKE_SUPPORT_INTEGRITY_SHA2_384          0x00000010
#define IKE_SUPPORT_INTEGRITY_SHA2_512          0x00000020


/*Post B039: Supported PRF algorithms only for v2*/
#define IKE_SUPPORT_PRF_MD5                     0x00000001
#define IKE_SUPPORT_PRF_SHA                     0x00000002
#define IKE_SUPPORT_PRF_AES_XCBC_128            0x00000004

/*Post B039: Supported DH group*/
#define IKE_SUPPORT_GROUP_DESC_MODP_768         0x00000001
#define IKE_SUPPORT_GROUP_DESC_MODP_1024        0x00000002
#define IKE_SUPPORT_GROUP_DESC_MODP_1536        0x00000004
#define IKE_SUPPORT_GROUP_DESC_MODP_2048        0x00000008
#define IKE_SUPPORT_GROUP_DESC_MODP_3072        0x00000010

/*Post B039: Supported Auth Methods only for v1*/
#define IKE_SUPPORT_AUTH_METHOD_PRE_SHARED      0x00000001
#define IKE_SUPPORT_AUTH_METHOD_DSS             0x00000002
#define IKE_SUPPORT_AUTH_METHOD_RSA_SIG         0x00000004

/*Post B039: This macro is common for IKEv1 and IKEv2*/
#define IKE_ALL_SUPPORTED_DH_GRP (IKE_SUPPORT_GROUP_DESC_MODP_768 \
                                    | IKE_SUPPORT_GROUP_DESC_MODP_1024 \
                                    | IKE_SUPPORT_GROUP_DESC_MODP_2048 \
                                    | IKE_SUPPORT_GROUP_DESC_MODP_3072)

/*Post B039: This macro is common for IKEv1 and IKEv2*/
#define IKE_ALL_SUPPORTED_ENCR_ALGS (IKE_SUPPORT_ENCRYPT_DES_CBC \
                                        | IKE_SUPPORT_ENCRYPT_3DES_CBC \
                                        | IKE_SUPPORT_ENCRYPT_AES_CBC_128 \
                                        | IKE_SUPPORT_ENCRYPT_AES_CBC_192 \
                                        | IKE_SUPPORT_ENCRYPT_AES_CBC_256)

/*Post B039: This macro is only for IKEv1, since it supports only MD5 and SHA1*/
/*HS:Sha2-support*/
#define IKEv1_ALL_SUPPORTED_INTEGRITY_ALGS (IKE_SUPPORT_INTEGRITY_MD5 \
                                                | IKE_SUPPORT_INTEGRITY_SHA \
                                                | IKE_SUPPORT_INTEGRITY_SHA2_256 \
                                                | IKE_SUPPORT_INTEGRITY_SHA2_384 \
                                                | IKE_SUPPORT_INTEGRITY_SHA2_512 )

/*Post B039: This macro is only for IKEv1*/
#define IKEv1_ALL_SUPPORTED_AUTH_METHOD (IKE_SUPPORT_AUTH_METHOD_PRE_SHARED \
                | IKE_SUPPORT_AUTH_METHOD_DSS | IKE_SUPPORT_AUTH_METHOD_RSA_SIG)

/*Post B039: This macro is only for IKEv2, since AES_XCBC is supported by
  only IKEv2*/
/*HS:Sha2-support*/  
#define IKEv2_ALL_SUPPORTED_INTEGRITY_ALGS (IKE_SUPPORT_INTEGRITY_MD5 \
                | IKE_SUPPORT_INTEGRITY_SHA | IKE_SUPPORT_INTEGRITY_AES_XCBC_96 \
                | IKE_SUPPORT_INTEGRITY_SHA2_256 | IKE_SUPPORT_INTEGRITY_SHA2_384 \
                | IKE_SUPPORT_INTEGRITY_SHA2_512)

/*Post B039: This macro is only for IKEv2, since PRF is supported by
  only IKEv2*/
#define IKEv2_ALL_SUPPORTED_PRF_ALGS (IKE_SUPPORT_PRF_MD5 | IKE_SUPPORT_PRF_SHA \
                                                | IKE_SUPPORT_PRF_AES_XCBC_128)

#define IKE_AUTOVPN_ENABLE      1
#define IKE_AUTOVPN_DISABLE     0

#ifndef _IKE_PACKET_INFO_DEFINED_
#define _IKE_PACKET_INFO_DEFINED_
/* The packet information SRc_addr, Dst_Addr, port etc for IKE packet comming
   from GGSN */

/*
Structures (tagIKE_IN_ADDR, tagIKESockAddr_in) is mapped to socket structures
(in_addr, sockaddr_in) to remove dependency on socket header file.
NOTE : Any change in socket structure should be reflected in IKE structures
aswell
*/

struct tagIKE_IN_ADDR
{
    ULONG s_addr;
};

typedef struct tagIKESockAddr_in
{
    UCHAR sin_len;
    UCHAR sin_family;               /* must be AF_INET */
    USHORT sin_port;                /* 16-bit port number */
    struct tagIKE_IN_ADDR sin_addr; /* 32-bit IP address */
    CHAR sin_zero[8];               /* must be 0 */
}IKE_SOCKADDR_IN_S;

typedef struct tagIKE_PACKET_INFO_S
{
    struct tagIKESockAddr_in stSrc;
    struct tagIKESockAddr_in stDest;
    ULONG ulIfIndex;
    ULONG ulVrfIndex;
    UCHAR ucProtocol;
    UCHAR aucRes [3];
}IKE_PACKET_INFO_S;
#endif

/* The API's that are registered by the GGSN product for usage by IKE/IPSEC */
typedef struct tagCMN_GGSN_API_CALLBACK_S
{
    ULONG (*pfTTG_UdpOutPut) (IKE_PACKET_INFO_S *pstPktInfo,
                                    UCHAR *pucMsgBuf, ULONG  ulMsgBufLen);

    ULONG (*pfTTG_GenerateIKESPI)(UCHAR *pucIKESPI, UCHAR ucSPILen,
        UCHAR *pucOldIKESPI, UCHAR ucOldSPILen);

    ULONG (*pfTTG_ReleaseIKESPI)(UCHAR *pucIKESPI, UCHAR ucSPILen);

    ULONG (*pfTTG_GenerateIPSecSPI)(UCHAR *pucIPSecSPI, UCHAR ucSPILen ,
                                        UCHAR  *pucIKESPI, UCHAR ucIKESPILen);

    ULONG (*pfTTG_ReleaseIPSecSPI)(UCHAR *pucIPSecSPI, UCHAR ucSPILen);

    /* Currently there TTG supports a max of 32 IP Address so max count will be
       32.
     */
    ULONG (*pfGetAllIpAddrOnIntf)(ULONG *pulIPAddr, UCHAR *pucAddrCount,
                                                        ULONG ulMaxCount);

    ULONG (*pfTTG_SlaveDownloadIkeSA) (UCHAR *pucIKESPI, UCHAR ucSPILen,
                                        ULONG ulConnID);

}CMN_GGSN_API_CALLBACK_S;

/*Contains mode-cfg attributes which are provided by the Product IP pool module
to the IKE on server.
*/
typedef struct tagIKE_AAA_MODECFG_ATTR_S
{
    ULONG ulErrorFlag;       /* Contains error code in case of failure, for
                                success case it should be filled with IKE_OK */
    ULONG ulAttributes;      /* Each bit in the variable represents the                      mode-cfg attributes
                                IKE_CFG_AAA_IP4_ADDRESS             0x00000001
                                IKE_CFG_AAA_IP4_NETMASK             0x00000002
                                IKE_CFG_AAA_IP4_DNS                 0x00000004
                                IKE_CFG_AAA_IP4_NBNS                0x00000008
                                IKE_CFG_AAA_ADDRESS_EXPIRY          0x00000010
                                IKE_CFG_AAA_IP4_DHCP                0x00000020
                                IKE_CFG_AAA_APPLICATION_VERSION     0x00000040
                                IKE_CFG_AAA_IP6_ADDRESS             0x00000080
                                IKE_CFG_AAA_IP6_DNS                 0x00000100
                                IKE_CFG_AAA_IP6_NBNS                0x00000200
                                IKE_CFG_AAA_IP6_DHCP                0x00000400
                                IKE_CFG_AAA_IP4_SUBNET              0x00000800
                                IKE_CFG_AAA_SUPPORTED_ATTRIBUTES    0x00001000
                                IKE_CFG_AAA_IP6_SUBNET              0x00002000*/

    USHORT usAddrCount_IPV4;    /* Holds the IPV4  address count */
    USHORT usSubnetCount_IPV4;  /* Holds the IPV4  Subnet Attribute count   */
    USHORT usDnsCount_IPV4;     /* Holds the IPV4 DNS Attribute count */
    USHORT usNbnsCount_IPV4;    /* Holds the IPV4 NBNS Attribute count */
    USHORT usDhcpCount_IPV4;    /* Holds the IPV4 DHCP Attribute count */
    USHORT usPad;               /* Padding bytes */
    UCHAR *pucIPV4Addr;         /* Pointer to buffer contains IPV4 Address */
    UCHAR *pucIPV4NetMask;      /* Pointer to buffer contains IPV4 NetMask */
    UCHAR *pucIPV4Dns;          /* Pointer to buffer contains DNS */
    UCHAR *pucIPV4Subnet;       /* Pointer to buffer contains IPV4 Subnet */
    UCHAR *pucIPV4Nbns;         /* Pointer to buffer contains IPV4 Nbns */
    UCHAR *pucIPV4Dhcp;         /* Pointer to buffer contains IPV4 Dhcp */
    UCHAR *pucAppVersion;       /* Pointer to buffer contains Application Version */
    ULONG ulSupportedAttr;      /* Bit mask of supported attributes */
}IKE_AAA_MODECFG_ATTR_S;

/* GGSN EAP: Start */

typedef struct tagIKE_AAA_ID_INFO_S
{
    UCHAR  szDomain[IKE_TRUST_NAME_MAX_LEN];      /* DOMAIN */
    USHORT usRespIDType;      /* Peer ID type, Ipv4, Ipv6, FQDN etc */
    USHORT usRespIDlen;       /* Length of the Responder ID buffer */
    UCHAR  aucBufRespID[IKE_ID_MAX_LENGTH + 1]; /* Responder ID information */
    USHORT usInitIDType;      /* Local ID type, Ipv4, Ipv6, FQDN etc */
    USHORT usInitIDlen;       /* Length of the initiator ID buffer */
    UCHAR  aucBufInitID[IKE_ID_MAX_LENGTH + 1]; /* Local ID information */
    ULONG  ulPeerIPv4IP;      /* The product need this information for the generating unique peer information. */
    USHORT usPortNumber;      /* Port from which the message is received from peer */
    USHORT usPad;             /* Padding bytes */
    ULONG  ulconnectionid;    /* IKE connection ID */
    ULONG  ulReqId;           /* Request ID corresponding to the request */
    ULONG  ulVrfId;           /* VRF associated with the current IKE
                                 session */
    UCHAR  szRespIKESPI[8];   /* IKE SPI-Responder */

    /* Added ifindex to add routes. Product uses this parameter*/
    ULONG ulIfIndex;
}IKE_AAA_ID_INFO_S;

/* Used by IKE for communicating with the Product for Mode-CFG server */
typedef struct tagIKE_MODECFGSERVER_REGISTER_FUNC
{
    ULONG (*pfIKE_AAA_ModeCfgAttributeReq) (IKE_AAA_ID_INFO_S *pstIDInfo,
        IKE_AAA_MODECFG_ATTR_S *pstModeCfgAttr);
    ULONG (*pfIKE_AAA_ModeCfgAttributeRelease)(IKE_AAA_ID_INFO_S *pstIDInfo,
        IKE_AAA_MODECFG_ATTR_S *pstModeCfgAttr);

} IKE_MODECFGSERVER_REGISTER_FUNC_S;

/* GGSN EAP: Start */

/* This structure contains the set of function pointers to be
   register to be able to use EAP on the Server side */
typedef struct tagIKEV2_EAPGENERIC_REGISTER_FUNC_S
{
    ULONG (*pfIKEv2_MsgNotifyToEAP) (IKE_AAA_ID_INFO_S
            *pstIDInfo, ULONG ulMsgLength, UCHAR * pEAPMsg);

    VOID (*pfIKEv2_ErrNotifyToEAP) (IKE_AAA_ID_INFO_S
            *pstIDInfo, ULONG ulErrCode);

    ULONG (*pfIKEv2_InitiateEAP) (IKE_AAA_ID_INFO_S
            *pstIDInfo);
}IKEV2_EAPGENERIC_REGISTER_FUNC_S;

/* Macros to represent EAP sucess and EAP failure */
#define IKEV2_EAP_REQUEST   1
#define IKEV2_EAP_RESPONSE  2
#define IKEV2_EAP_SUCCESS   3
#define IKEV2_EAP_FAIL      4
/* GGSN EAP: End */

/*Added function pointer for S9300 warning messages.*/
typedef struct tagIKE_IDVALIDATIONCALLBACK_S
{
    /* This function is called to decide if Initiators ID needs to be validated
       on the responder side

       Return value
       IKE_ERR_VALIDATE_ID - ID should be validated
       IKE_ERR_BYPASS_IDVALIDATION - ID validation should be bypassed
       If this callback is not registered then ID valiadtion is enabled by
       defualt

       Memory Handling: Peername will be allocated and released by IKE */

    ULONG (*pfIKE_IDiValidationCallback)(CHAR *pszIkePeerName);

    /* This function is called to decide if Responders ID needs to be validated
       on the responder side

       Return value
       IKE_ERR_VALIDATE_ID - ID should be validated
       IKE_ERR_BYPASS_IDVALIDATION - ID validation should be bypassed
       If this callback is not registered then ID valiadtion is enabled by
       default

       Memory Handling: Peername will be allocated and released by IKE */
    ULONG (*pfIKE_IDrValidationCallback)(CHAR *pszIkePeerName);

}IKE_IDVALIDATIONCALLBACK_S;

/* To pass HA function pointers from shell to core. */
typedef struct tagIKEShellHSBBackUpSet
{
    ULONG (*pfIKE_SH_HSB_SendRealtimeData) (UCHAR *, ULONG);
    ULONG (*pfIKE_SH_HSB_SendBatchBackupData) (UCHAR *, ULONG);
    VOID *(*pfIKE_SH_HSB_MemAllocate) (ULONG);
    ULONG (*pfIKE_SH_HSB_MemFreeup) (VOID *);
    ULONG (*pfIKE_SH_HSB_BoardType) (VOID);
    ULONG (*pfIKE_SH_HSB_SendRoutineBackupData)(UCHAR *, ULONG);
} IKE_SHELL_HSB_BACKUP_SET_S;

/* To support Tunnel interface in IKE */
typedef struct tagIKETUNNELINTERFACE_S
{
    ULONG (*pfIKE_TunnelInterfaceCallback) (ULONG ulSrc,  ULONG ulDest,
                                                ULONG ulVRF,  ULONG *pulIfindex);
    ULONG (*pfIKE_IsInterfaceTunnel) (ULONG ulIfindex);
}IKETUNNELINTERFACE_S;

/* AR Req: FQDN changes */
typedef struct tagIKEIPSEC_FQDN_PARAMS
{
    /*
        The Module Flag IPSEC should use for Querying the IP address using
        the API registered for pfIKE_IPSEC_DNSE_GetIpByName

        typedef enum tagDNSEModuleType
        {
           DNSE_DDNS = 1,
           DNSE_SIP = 2,
           DNSE_IPSEC = 3,

           DNSE_MODULE_MAX
        }DNSE_MODULE_TYPE;

        IPSEC module should use DNSE_IPSEC always
     */
    ULONG ulModuleFlag;

    /*
        The operation type IPSEC should use for Querying the IP address using
        the API registered for pfIKE_IPSEC_DNSE_GetIpByName.

        #define DNSE_QUERY_CACHE  1
        #define DNSE_NO_QUERY_CACHE  0

        IPSEC Should use DNSE_QUERY_CACHE as we use ASYNC call always.

     */
    ULONG ulOperType;

    /*
        This is the maximum IP address that the DNS module can return for a
        particular FQDN.

        #define DNSE_DOMAIN_IP_MAX_NUM  4

        if produce can return 5 IP addresses for a FQDN, then the value of the
        ulMaxIPAddrReturned should be 5. IKE module will allocate
        5 * sizeof(ULONG), and pass the buffer cotaining the allocated memory
        whenever request for resolution.
     */
    ULONG ulMaxIPAddrReturned;

    /*
        THE maximum and minimum length of the FQDN allowed.
        #define DNSE_DOMAIN_NAME_MAX_LEN  255
     */
    ULONG ulMaxFQDNNameLen;
    ULONG ulMinFQDNNameLen;
}IKEIPSEC_FQDN_PARAMS;

/* IPSEC Reverse Route support */
typedef struct tagIKE_IPSEC_ROUTE_INFO_S
{
    ULONG   ulDest;
    ULONG   ulMask;
    ULONG   ulVrfindex;
    ULONG   ulNexthop;
    ULONG   ulIfindex;
    ULONG   ulMetric;
    ULONG   ulPreference;
} IKE_IPSEC_ROUTE_INFO_S;

typedef struct tagIKE_IPSEC_SPLFEATURECBK
{
    ULONG (*pfIKE_IPSEC_GetFQDNParams)(IKEIPSEC_FQDN_PARAMS *pstFQDNParams);
    ULONG (*pfIKE_IPSEC_ValidateFQDN)(UCHAR *pucFQDN);
    ULONG (*pfIKE_IPSEC_DNSE_GetIpByName)(CHAR *pszFQDN, ULONG *pulIpAddr,
                                        USHORT usModuleFlag, ULONG ulOperType, VOID *pvHandle);
    ULONG (*pfIPSec_AddRoute) (IKE_IPSEC_ROUTE_INFO_S *pstRoute);
    ULONG (*pfIPSec_DelRoute) (IKE_IPSEC_ROUTE_INFO_S *pstRoute);
    ULONG (*pfIPSec_RRI_GetInterfaceState) (ULONG ulIfIndex, ULONG *pulIfState);

}IKE_IPSEC_SPLFEATURECBK;

typedef struct tagIKE_IPSEC_SPLFEATURESTAT
{
    ULONG ulFQDNInvalidPara;            /* Invalid parameter */
    ULONG ulFQDNCantFindPeerByIndex;    /* Unable to find the peer in DNS notification */
    ULONG ulFQDNPeerStateNotPending;    /* FQDN Resolution is not pending, but received DNS notification */
    ULONG ulFQDNRetPeerAddrSetErr;      /* Failed to set the peer address in peer */
    ULONG ulFQDNCfgDelBeforeDnsRet;     /* FQDN is unconfigured by the time DNS notified the address */
    ULONG ulFQDNPeerUsedBySa;           /* Unable to set the resolved address in peer, as there are some SAs present */
    ULONG ulRRIAddRouteFail;            /* Failed to add route for RRI */
    ULONG ulRRIDelRouteFail;            /* Failed to delete route for RRI */
    ULONG ulRRIIntfDownRouteAddFail;    /* Failed to delete route for RRI */
}IKE_IPSEC_SPLFEATURESTAT;

/* To get Attributes from Modecfg Product */
typedef struct IKE_MODECFG_ATTRMASK
{
    ULONG (*pfIKE_ModecfgAttrMaskCallBack)(CHAR *pszIkePeerName,  ULONG *pulMask);

}IKE_MODECFG_ATTRMASK_S;

/* Type of variable to register IPSEC6/IKE6 registration function */
typedef ULONG (*pfuncIkeIPv6Reg)(VOID);


#ifndef IKE_CERT_CHECK_TYPE_DEF_MACRO

#define IKE_CERT_CHECK_TYPE_DEF_MACRO  1

typedef enum enumIKE_CERT_CHECK_TYPE
{
    IKE_PKI_CERT_CHECK_TYPE_INVALID         = 0,
    IKE_PKI_CERT_CHECK_TYPE_CRL             = 1,
    IKE_PKI_CERT_CHECK_TYPE_OCSP            = 2,
    IKE_PKI_CERT_CHECK_TYPE_NONE            = 3,
    IKE_PKI_CERT_CHECK_TYPE_MAX             = 0xff
}IKE_CERT_CHECK_TYPE_E;

/*HERT3.3 DH HW Support - Start */
/* Macros specifies the DH Phase operation */
#define IKE_HW_DHPHASE1     1
#define IKE_HW_DHPHASE2     2

typedef struct tagIKE_DH_HW_CBK_S
{
    /*******************************************************************************
     Function that calculates the DH Phase1 and DH Phase2 Operations in hardware
     DH Phase1 :
     =========
     A = g^a mod p    , B = g^b mod p

    DH Phase2 :
    =========
    S = A^b mod p    , S =B^a mod p

    vSharedSecret : OutputBuffer ( A or B for DH Phase1 and S in DH Phase 2) and of type IKE_Buffer
    vPublicKey: (g for DH Phase1 and A or B for DH Phase 2) type IKE_Buffer
    ulDHPhase: 1 == DH Phase1 and 2 == DH Phase2
    ulGroupId: DH Group
     *******************************************************************************/

    ULONG (*pfIKE_HW_DHCalculation) (VOID *vSharedSecret, VOID *vPublicKey, VOID *vPrivateKey,
                                                                ULONG ulDHPhase, ULONG ulGroupId);
}IKE_DH_HW_CBK_S;

typedef struct tagIkeBuffer
{
    ULONG ulDataLenInBytes;
    UCHAR *pucData;
}IKE_Buffer;
/*HERT3.3 DH HW Support - End */

#define IKE_PKI_OCSP_DOWNLOAD_STATUS_IS_OK       0
#define IKE_PKI_OCSP_DOWNLOAD_STATUS_IS_ERR      1
#define IKE_PKI_OCSP_DOWNLOAD_STATUS_IS_PENDING  2

#endif

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IKE_PUB_H_ */


