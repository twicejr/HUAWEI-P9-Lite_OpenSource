

#ifndef _IPSEC_PUB_H
#define _IPSEC_PUB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IPSEC_YES
#define IPSEC_YES 1
#endif

#ifndef IPSEC_NO
#define IPSEC_NO  0
#endif

#ifndef _IPSEC_TAILOR_H
#if (VRP_YES == VRP_CENTERALIZATION)
#define  IPSEC_CENTERALIZATION   IPSEC_YES    /* use for Centralized system */
#define  IPSEC_DISTRIBUTED       IPSEC_NO     /* use for Distributed system */
#define  IPSEC_IO_BOARD          IPSEC_NO     /* use for IO Board in
                                                  distributed system  */
#define  IPSEC_MAIN_BOARD        IPSEC_NO     /* use for Main Board in
                                                  distributed system  */
#endif

#if ((VRP_YES == VRP_DISTRIBUTED) && (VRP_YES == VRP_MAIN_BOARD))
#define  IPSEC_CENTERALIZATION   IPSEC_NO      /* use for Centralized system */
#define  IPSEC_DISTRIBUTED       IPSEC_YES     /* use for Distributed system */
#define  IPSEC_IO_BOARD          IPSEC_NO      /* use for IO Board in
                                                  distributed system  */
#define  IPSEC_MAIN_BOARD        IPSEC_YES     /* use for Main Board in
                                                  distributed system  */
#endif

#if ((VRP_YES == VRP_DISTRIBUTED) && (VRP_YES == VRP_IO_BOARD))
#define  IPSEC_CENTERALIZATION   IPSEC_NO      /* use for Centralized system */
#define  IPSEC_DISTRIBUTED       IPSEC_YES     /* use for Distributed system */
#define  IPSEC_IO_BOARD          IPSEC_YES     /* use for IO Board in
                                                  distributed system  */
#define  IPSEC_MAIN_BOARD        IPSEC_NO      /* use for Main Board in
                                                  distributed system  */
#endif
#endif

typedef struct tagIPSEC_SPD_TRACKER_S       IPSEC_SPD_TRACKER_S;
typedef struct tagIPSEC_SPDS_S              IPSEC_SPDS_S;
typedef struct tagIPSEC_SPDU_S              IPSEC_SPDU_S;
typedef struct tagTdbEntry                  IPSEC_TdbEntry_S;
typedef struct tdb                          TDB_S;

typedef struct tagCryptoMap             IPSEC_CryptoMap_S;

/*S9300_Moved from Pub internal Hdr File*/
#define SID_IPSEC_PFKEYV2_SOCKET            0x010
#define SID_IPSEC_AH_NEW_CTX                0x020
#define SID_IPSEC_ENC_KEY                   0x030
#define SID_IPSEC_IHASH                     0x040
#define SID_IPSEC_OHASH                     0x050
#define SID_IPSEC_IPSP_TDBP                 0x060
#define SID_IPSEC_IPSP_EXP                  0x070
#define SID_IPSEC_INIT_KEY                  0x080
#define SID_CRYPTO_TRANSFORM                0x090
#define SID_IPSEC_MAPGRPHEAD_S              0x0A0
#define SID_CRYPTO_MAP                      0x0B0
#define SID_CRYPTO_MAP_BOUND                0x0C0
#define SID_IPSEC_MAPIFINDEX_S              0x0D0
#define SID_IPSEC_TRANSFORM_NAME_SET        0x0E0
#define SID_IPSEC_TDB_ENTRY_HEAD_S          0x0F0
#define SID_IPSEC_TDB_ENTRY_S               0x100
#define SID_IPSEC_DYTDB_ENTRY_S             0x110
#define SID_IPSEC_TDBENTRY_ID               0x120
#define SID_IPSEC_INIT                      0x130
#define SID_IPSEC_TDB                       0x140
#define SID_IPSEC_CHAR                      0x150
#define SID_IPSEC_IPC                       0x160
#define SID_IPSEC_SEND_MAP_IPC              0x170
#define SID_IPSEC_IPC_RPC                   0x180
#define SID_IPSEC_CMD                       0x190
#define SID_IPSEC_PROFILE                   0x1A0
#define SID_IPSEC_HOT_INSERT                0x1B0
#define SID_IPSEC_BUILDRUN                  0x1C0
#define SID_IPSEC_BACKUP                    0x1D0
#define SID_IPSEC_HW                        0x1E0
#define SID_IPSEC_ACL_MAP                   0x1F0
#define SID_IPSEC_ADDR_POOL                 0x200


/* Following are all the cache related SIDs */
#define SID_IPSEC_SPDS_PARAMETERS           0x210
#define SID_IPSEC_SPDU_PARAMETERS           0x220
#define SID_IPSEC_SPDS_TRACKER              0x230
#define SID_IPSEC_SPDU_TRACKER              0x240
#define SID_IPSEC_SPDS_DISPLAY              0x250
#define SID_IPSEC_SPDU_DISPLAY              0x260
#define SID_IPSEC_CACHE_SPDS_STAT           0x270
#define SID_IPSEC_CACHE_SPDU_STAT           0x280

#define SID_IPSEC_PEER                      0x290

#define SID_IPSEC_DPD_EXPIRATION            0x2A0

#define SID_IPSEC_MODECFG_TDBENTRY          0x2B0

/* Post B043: This SID should not be macro pruned, it is being used without outside */
#define SID_IPSEC_TRAFFIC_SELECTOR          0x2C0

/*GGSN*/
#ifndef IPPROTO_ICMP
#define    IPPROTO_ICMP    1        /* control message protocol */
#endif
#ifndef IPPROTO_TCP
#define    IPPROTO_TCP        6        /* tcp */
#endif
#ifndef IPPROTO_UDP
#define    IPPROTO_UDP        17        /* user datagram protocol */
#endif
#ifndef IPPROTO_ESP
#define IPPROTO_ESP     50      /* Ip Sec */
#endif
#ifndef IPPROTO_AH
#define IPPROTO_AH      51      /* Ip Sec */
#endif

/* Default lifetime for IPsec SA */
/* 0.5Mb per seconds for one hour */
#define IPSEC_LIFETIME_DEFAULT_KILOBYTES      1843200
#define IPSEC_LIFETIME_DEFAULT_SECONDS        3600

/* Macro indicating the type of lifetime */
#define IPSEC_LIFETIME_GLOBAL 0
#define IPSEC_LIFETIME_LOCAL  1

/* Used for Byte-to-Bit conversion */
#define IPSEC_CHAR_IN_BYTE                       8
#define IPSEC_ESP_HEADER_LEN_WITHOUT_IV          8

/* Anti replay Configuration Change: Start */
#define IPSEC_ENABLE_ANTIREPLAY             IPSEC_OP_ENABLE
#define IPSEC_DISABLE_ANTIREPLAY            IPSEC_OP_DISABLE
/* Anti replay Configuration Change: End */

#define IPSEC_RESERVED_IPC                  0
#define IPSEC_CMD_IPC_VERSION1              1

/*  added by suresh for PAF support */
#define IPSEC_CMD_IPC_VERSION2              2

/*Transform command*/
#define IPSEC_TRANSFORM_PROTOCOL_AH                      0 /*AH*/
#define IPSEC_TRANSFORM_PROTOCOL_ESP                     1 /*ESP*/
#define IPSEC_TRANSFORM_PROTOCOL_AH_ESP                  2 /*AH-ESP*/
#define IPSEC_TRANSFORM_PROTOCOL_AH_IPCOMP               3 /*AH-ESP*/
#define IPSEC_TRANSFORM_PROTOCOL_ESP_IPCOMP              4 /*AH-ESP*/
#define IPSEC_TRANSFORM_PROTOCOL_AH_ESP_IPCOMP           5 /*AH-ESP*/

/*Ipv6: Security Support*/
/*  Address Family Type  */
#define IPSEC_ADDR_TYPE_IPV4             4
#define IPSEC_ADDR_TYPE_IPV6             6
#define IPSEC_ADDR_TYPE_COM              0
#define IPSEC_ADDR_TYPE_ANY              0xFF
#define IPSEC_IPV6_ADDR_LEN              16
/***********Config modes***************/

#define IPSEC_OP_DELETE                                  0
#define IPSEC_OP_SET                                     1
#define IPSEC_OP_ENABLE                                  1
#define IPSEC_OP_DISABLE                                 0
#define IPSEC_OP_CREATE                                  1
#define IPSEC_OP_CREATE_BY_TEMPLATE                      2
#define IPSEC_OP_GET                                     3
#define IPSEC_SA_KEY_INBOUND_AH                          5
#define IPSEC_SA_KEY_INBOUND_ESP                         6
#define IPSEC_SA_KEY_OUTBOUND_AH                         7
#define IPSEC_SA_KEY_OUTBOUND_ESP                        8
#define IPSEC_SA_INBOUND                                 9
#define IPSEC_SA_OUTBOUND                               10
#define IPSEC_SA_SPI_INBOUND_AH                         11
#define IPSEC_SA_SPI_INBOUND_ESP                        12
#define IPSEC_SA_SPI_OUTBOUND_AH                        13
#define IPSEC_SA_SPI_OUTBOUND_ESP                       14

#define IPSEC_SET_TRIGGER_TRAFFIC_BASED                  1
#define IPSEC_SET_TRIGGER_AUTO                           2

#define IPSEC_STRLEN_1                                   1
#define IPSEC_STRLEN_2                                   2
#define IPSEC_STRLEN_3                                   3
#define IPSEC_STRLEN_4                                   4
#define IPSEC_STRLEN_8                                   8
#define IPSEC_STRLEN_15                                 15
#define IPSEC_STRLEN_16                                 16
#define IPSEC_STRLEN_20                                 20
#define IPSEC_STRLEN_31                                 31
#define IPSEC_STRLEN_32                                 32
#define IPSEC_STRLEN_64                                 64
#define IPSEC_STRLEN_128                               128
#define IPSEC_STRLEN_255                               255
#define IPSEC_STRLEN_256                               256
#define IPSEC_STRLEN_512                               512
#define IPSEC_STRLEN_1024                             1024

/* Added By Jayesh */
#define IPSEC_MIN_STRLEN_1                               1
#define IPSEC_MAX_PROPOSAL_LEN_15                       15
#define IPSEC_MAX_POLICY_LEN_15                         15
#define IPSEC_MAX_TEMPLATE_LEN_15                       15
#define IPSEC_MAX_PEERNAME_LEN                          31
#define IPSEC_MAX_SA_HARDEXP_ONDEMAND_TIMEOUT_SEC       1000
#define IPSEC_MIN_SA_HARDEXP_ONDEMAND_TIMEOUT_SEC       10

/* B113: Updated the hardtimeout default from 60 to 360 seconds */
#define IPSEC_DEFAULT_SA_HARDEXP_ONDEMAND_TIMEOUT_SEC   360

/* End  */

#define IPSEC_POLICY_MODE_ISAKMP                         0
#define IPSEC_POLICY_MODE_MANUAL                         1
#define IPSEC_POLICY_MODE_DYNATEMPLET                    2

#define IPSEC_MAX_MAP_NAME                              15
#define IPSEC_MAX_PROF_NAME                             12
#define IPSEC_MAX_PROF_TAG                               3
#define IPSEC_CRYPTO_MAP_MAXPEERS                        1

/*GGSN*/
#define IPSEC_CRYPTOMAP_MAX_TRANSFORM_NUM                12

/*PICO Wi-Max DSCP changes*/
#define IPSEC_MAX_CRYPTO_NAME_LEN                        32

/*End Of PICO Wi-Max DSCP changes*/


/*IPSEC PROPOSAL*/
#define IPSEC_MAX_TRANSFORM_NAME                        15

#define IPSEC_MAX_ALG_NAME_LENGTH                       32

#define IPSEC_HW_TIMER_MILLISEC                        100

#define IPSEC_DEBUG_SA              0
#define IPSEC_DEBUG_MISC            1
#define IPSEC_DEBUG_ALL             2
#define IPSEC_DEBUG_PACKET          3
#define IPSEC_DEBUG_SECURE_CACHE    4
#define IPSEC_DEBUG_UNSECURE_CACHE  5
#define IPSEC_DEBUG_GENERIC_HW      6

/*Iteration2: Story12: Maintainance*/
#define IPSEC_DEBUG_ERROR           7

/* Peer maintained by IPsec */
#define IPSEC_MIN_PEERNAME_LEN_1      1
#define IPSEC_MAX_INTERFACE_NAME_LEN (47 + 1)

/*SGSN Changes Moved to public file for product use.*/
#define IPSEC_TRUE              1
#define IPSEC_FALSE             0

#define IPSEC_SA_LIFETIME_SECONDS                        0
#define IPSEC_SA_LIFETIME_BYTES                          1

/*********************************************************************/

/*B500 - SGSN-CMD Registration*/
#ifdef IKE_PEER_NAME_MAX_LEN
#define IPSEC_PEER_NAME_MAX_LEN IKE_PEER_NAME_MAX_LEN
#define IPSEC_MAX_VPN_NAME_LEN IKE_MAX_VPN_NAME_LEN
#else
#define IPSEC_PEER_NAME_MAX_LEN 32
#define IPSEC_MAX_VPN_NAME_LEN 31
#endif


/* the key length of ipsec_maunal mode       */
#define IPSEC_MAX_SESSION_KEY_LENGTH                64
#define IPSEC_MAX_MANUAL_KEY_LENGTH                 64
#define IPSEC_MAX_MANUAL_CIPHER_KEY_LENGTH          32
#define IPSEC_MAX_MANUAL_AUTHENTICATOR_KEY_LENGTH   64

#define IPSEC_MANUAL_AUTHEN_INVALID_KEY_LENGTH      0
#define IPSEC_MANUAL_AUTHEN_MD5_KEY_LENGTH          16
#define IPSEC_MANUAL_AUTHEN_SHA_KEY_LENGTH          20

/* SHA2 Support */
#define IPSEC_MANUAL_AUTHEN_SHA256_KEY_LENGTH       32
#define IPSEC_MANUAL_AUTHEN_SHA384_KEY_LENGTH       48
#define IPSEC_MANUAL_AUTHEN_SHA512_KEY_LENGTH       64
#define IPSEC_MANUAL_AUTHEN_AESXCBC_96_KEY_LENGTH   16



/* see stESPNewXForm[] in ip_esp_n.c for knowledge */
#define IPSEC_ENCRY_NULL_KEY_LENGTH           8
#define IPSEC_ENCRY_DES_KEY_LENGTH            8
#define IPSEC_ENCRY_3DES_KEY_LENGTH          24
#define IPSEC_ENCRY_BLOWFISH_KEY_LENGTH      24
#define IPSEC_ENCRY_CAST_KEY_LENGTH          16
#define IPSEC_ENCRY_SKIPJACK_KEY_LENGTH      10
#define IPSEC_ENCRY_HARDWARE_KEY_LENGTH      16

#define IPSEC_ENCRY_AES128_KEY_LENGTH        16
#define IPSEC_ENCRY_AES192_KEY_LENGTH        24
#define IPSEC_ENCRY_AES256_KEY_LENGTH        32

#define IPSEC_MIN_HEX_KEY_STRING              8

#define IPSEC_MAX_HEX_KEY_STRING             32

#define IPSEC_MAX_HEX_KEY_ULONG               6
#define IPSEC_MAX_KEY_STRING_LENGTH         256

#define IPSEC_MD5_DIGEST_LENGTH              16
#define IPSEC_DOUBLE_MD5_DIGEST_LENGTH       32
#define IPSEC_DOUBLE_SHA2_DIGEST_LENGTH      128
#define IPSEC_DES_IV_SIZE1                    4
#define IPSEC_DES_IV_SIZE2                    8

/*For build run and display purposes*/
#define IPSEC_AH_NONE                         0x00000000
#define IPSEC_AH_NEW                          0x00000001
#define IPSEC_AH_OLD                          0x00000002
#define IPSEC_AH_MASK                         0x000000FF
#define IPSEC_AH_NEW_HASH_MD5_HMAC96          0x00010000
#define IPSEC_AH_NEW_HASH_SHA1_HMAC96         0x00020000

/* SHA2 Support */
#define IPSEC_AH_NEW_HASH_SHA2_HMAC256        0x00040000
#define IPSEC_AH_NEW_HASH_SHA2_HMAC384        0x00080000
#define IPSEC_AH_NEW_HASH_SHA2_HMAC512        0x00100000
#define IPSEC_AH_NEW_HASH_AESXCBC_96          0x00200000
#define IPSEC_AH_NEW_HASH_MASK                0x00FF0000
#define IPSEC_AH_OLD_HASH_MD5_KEYED           0x01000000
#define IPSEC_AH_OLD_HASH_SHA1_KEYED          0x02000000
#define IPSEC_AH_OLD_HASH_MASK                0xFF000000

#define IPSEC_ESP_NONE                        0x00000000
#define IPSEC_ESP_NEW                         0x00000001
#define IPSEC_ESP_OLD                         0x00000002
#define IPSEC_ESP_MASK                        0x000000FF
#define IPSEC_ESP_NEW_HASH_NULL               0x00000000
#define IPSEC_ESP_NEW_HASH_MD5_HMAC96         0x00010000
#define IPSEC_ESP_NEW_HASH_SHA1_HMAC96        0x00020000

/* SHA2 Support */
#define IPSEC_ESP_NEW_HASH_SHA2_HMAC256       0x00040000
#define IPSEC_ESP_NEW_HASH_SHA2_HMAC384       0x00080000
#define IPSEC_ESP_NEW_HASH_SHA2_HMAC512       0x00100000
#define IPSEC_ESP_NEW_HASH_AESXCBC_96         0x00200000
#define IPSEC_ESP_NEW_HASH_MASK               0x00FF0000
#define IPSEC_ESP_NEW_ENCRYPT_3DES            0x01000000

#define IPSEC_ESP_NEW_ENCRYPT_AES128          0x02000000
#define IPSEC_ESP_NEW_ENCRYPT_CAST            0x04000000
#define IPSEC_ESP_NEW_ENCRYPT_DES             0x08000000
#define IPSEC_ESP_NEW_ENCRYPT_SKIPJACK        0x10000000
#define IPSEC_ESP_NEW_ENCRYPT_HARDWARE        0x20000000
#define IPSEC_ESP_NEW_ENCRYPT_AES192          0x40000000
#define IPSEC_ESP_NEW_ENCRYPT_AES256          0x80000000
#define IPSEC_ESP_NEW_ENCRYPT_MASK            0xFF000000
#define IPSEC_ESP_OLD_ENCRYPT_3DES            0x00000100
#define IPSEC_ESP_OLD_ENCRYPT_DES             0x00000200
#define IPSEC_ESP_OLD_ENCRYPT_MASK            0x0000FF00
#define IPSEC_IPCOMP_COMP_LZS                 0x00000100
#define IPSEC_IPCOMP_COMP_MASK                0x0000FF00

/*
 * When used in tdb entry mode, they means:
 *
 * When used in crypto map mode, they means:
 *     IPSEC_ISAKMP      --> crypto map name seq isakmp
 *     IPSEC_DYNATEMPLET --> crypto map name seq isakmp dynamic dymap-name
 *     IPSEC_DYNAMIC     --> crypto dynamic-map name seq
 *     IPSEC_DYNATEMP    --> Tdb entry
 */
#define IPSEC_MANUAL                          1
#define IPSEC_ISAKMP                          0
#define IPSEC_DYNAMIC                         2
#define IPSEC_DYNATEMP                        3
#define IPSEC_DYNATEMPLET                     4
#define IPSEC_POLICY_MODE_MODECFG             5

#define IPSEC_SA_TRIGGER_MODE_AUTO            0
#define IPSEC_SA_TRIGGER_MODE_TRAFFIC_BASED   1

/*
 * When used in crypto map head mode, they means:
 *     IPSEC_STATIC_GROUP    --> crypto map name seq isakmp
 *                           --> crypto map name seq isakmp dynamic dymap-name
 *                           --> crypto map name seq manual
 *     IPSEC_DYNAMIC_GROUP   --> crypto dynamic-map name seq
 */
/* Used to mark a dynamic map group. */
#define IPSEC_DYNAMIC_GROUP                   1
#define IPSEC_STATIC_GROUP                    2

/* DH Grp 5&14 support */
#define IPSEC_PFS_GROUP_INVALID               0
#define IPSEC_PFS_GROUP1                      1
#define IPSEC_PFS_GROUP2                      2
#define IPSEC_PFS_GROUP5                      5
#define IPSEC_PFS_GROUP14                     14
#define IPSEC_PFS_GROUP15                     15
#define IPSEC_PFS_GROUP16                     16
#define IPSEC_PFS_GROUP17                     17
#define IPSEC_PFS_GROUP18                     18

#define IPSEC_OUTBOUND                        0
#define IPSEC_INBOUND                         1
#define IPSEC_BOUND_UNKNOWN                   2

#define IPSEC_MEM_KB_1                  1024
#define IPSEC_MEM_KB_2                  2048
#define IPSEC_MEM_KB_3                  3072
#define IPSEC_MEM_KB_4                  4096



#ifndef size_t
#define size_t ULONG
#endif /* size_t */

#define IPSEC_EVENT_ACL_UPDATE           0X0080
#define IPSEC_EVENT_ACL6_UPDATE          0X0800

#define IPSEC_SHOW_SA                     1
#define IPSEC_CLEAR_SA                    2
#define IPSEC_SEND_MANUAL_MAP             4
#define IPSEC_SEND_ISAKMP_MAP             5
#define IPSEC_GET_ENPACK_STAT             6
#define IPSEC_CLEAR_ENPACK_STAT           7
#define IPSEC_GET_DBGFLG_STAT             8
#define IPSEC_SYNC_SA                     9
#define IPSEC_IPC_SEND_PAF_VALUES        10
#define IPSEC_GET_INBOUND_SA_STATUS      11
#define IPSEC_GET_OUTBOUND_SA_STATUS     12
#define IPSEC_IPC_DEL_MAP_INTERFACE      13
#define IPSEC_GET_SOFT_EXPIRE_TIME       14
#define IPSEC_GET_HARD_EXPIRE_TIME       15
#define IPSEC_GET_SA_BY_TRIPLET          16
#define IPSEC_GET_SA_KEY                 17
#define IPSEC_GET_SA_ALGORITHM           18
#define IPSEC_DEBUG                      19
#define IPSEC_DEBUG_PACKET_MAP           20
#define IPSEC_DEBUG_PACKET_ENTRY         21
#define IPSEC_SHOW_SA_INTERFACE          22
#define IPSEC_POLICY_DELETE              23
#define IPSEC_CHK_SA_EXISTS              24

/*Begin  message type of Cache */
#define IPSEC_CACHE_END_OF_DATA              25
#define IPSEC_CACHE_NO_END_OF_DATA           26
#define IPSEC_SHOW_CACHE                     27
#define IPSEC_FLUSH_CACHE                    28
#define IPSEC_ENABLE_CACHE                   IPSEC_OP_ENABLE
#define IPSEC_DISABLE_CACHE                  IPSEC_OP_DISABLE
#define IPSEC_SET_AGEING_TIME_CACHE          31
#define IPSEC_SET_SAVED_ENTRY_COUNT_CACHE    32
#define IPSEC_CACHE_IPC_MSG                  33
#define IPSEC_CACHE_SET_DEBUG_SPDS           34
#define IPSEC_CACHE_SET_DEBUG_SPDU           35
#define IPSEC_GET_CACHE_STATISTICS           36
#define IPSEC_DELETE_CACHE_STATISTICS        37
#define IPSEC_DEL_AGED_ENTRIES               38
#define IPSEC_DISPLAY_CACHE_SPDS             39
#define IPSEC_DISPLAY_CACHE_SPDU             40
#define IPSEC_CACHE_SPDS_ACL_UPDATE          42
#define IPSEC_CACHE_POLICY_ADD_UPDATE        43
#define IPSEC_OPEN_CACHE_IO_OBJECT           44
#define IPSEC_CLOSE_CACHE_IO_OBJECT          45
#define IPSEC_DELAGEDCACHE_ENTRIES           46
#define IPSEC_DISABLE_CACHE_IN_INIT          47
#define IPSEC_DELETE_DYNAENTRY_FROM_CACHE    48
#define IPSEC_CACHE_ACL_RECREATED            49

/* DSCP_Comment Anoop   */
#define IPSEC_ENABLE_DSCP                    IPSEC_OP_ENABLE
#define IPSEC_DISABLE_DSCP                   IPSEC_OP_DISABLE

/* End comemnt Anoop    */

/*The value here is for RPC message*/
#define IPSEC_CACHE_GLOBAL_PARA_MSG          50


/* V1R3_DEV_BEGIN: MODECFG*/
/*The value here is for IPC message*/
#define IPSEC_MODECFG_ENTRIES_DELETE            50

#define IPSEC_SEND_PEER_ADD                     52
#define IPSEC_SEND_PEER_DELETE                  51

/* V1R3_DEV_END: MODECFG*/

/*The message is used in Test API*/
#define IPSEC_GLOBAL_SA_TRIGGER_MODE            53

#define IPSEC_CACHE_SECURE                      0
#define IPSEC_CACHE_UNSECURE                    1
#define IPSEC_CACHE_MAX_ENTRY_COUNT             1000
#define IPSEC_CACHE_MIN_ENTRY_COUNT             10

/*#define IPSEC_CACHE_MAX_ACL_MSGS              10*/
#define IPSEC_CACHE_MAX_ACL_MSGS                50

/*End message type of Cache */
/* V1R3_DEV_END: CACHE*/

#define IPSEC_DPD_TRIGGER_FOR_PEERS             46

/* Sub-message-type of IPSEC_SHOW_SA */
#define IPSEC_SHOW_SA_ALL                       1
#define IPSEC_SHOW_SA_BRIEF                     2
#define IPSEC_SHOW_SA_MAP                       3
#define IPSEC_SHOW_SA_PEER                      4

/* Sub-message-type of IPSEC_CLEAR_SA */
#define IPSEC_CLEAR_SA_ALL                      1
#define IPSEC_CLEAR_SA_MAP                      2
#define IPSEC_CLEAR_SA_PEER                     3
#define IPSEC_CLEAR_SA_ENTRY                    4
#define IPSEC_CLEAR_SA_BAK                      5

#define IPSEC_TIMER_UPDATE_RANDOMEVENT          1
#define IPSEC_TIMER_EXPIRE                      2
#define IPSEC_TIMER_IKE_NEGOTIATION             3
#define IPSEC_TIMER_TRASHUPDATE                 4
#define IPSEC_TIMER_AUTO_TRIGGER                5
#define IPSEC_TIMER_UPDATE_CACHE_SPDS           6
#define IPSEC_TIMER_UPDATE_CACHE_SPDU           7
#define IPSEC_TIMER_DPD                         8
#define IPSEC_TIMER_TICK                        9
#define IPSEC_TIMER_HW_TRAFFIC_EXPIRY           10


/*B050: Traffic based SA_Expiry*/
#define IPSEC_SA_HW_TRAFFIC_TIMER_RES           5 * 1000

/*********************************************************************/
#define IPSEC_MEMORY_SHORTAGE                   1
#define IPSEC_MEMORY_RESTORED                   0


/****************************/
/* PAF related parameters   */
/****************************/
#define IPSEC_PAF_PROPOSAL_MAX_NUMBER           400
#define IPSEC_PAF_PROPOSAL_MIN_NUMBER           1
#define IPSEC_PAF_PROPOSAL_AVAIL_NUMBER         400

/* IPv6 support */
#define IPSEC_PAF_PROPOSAL_MAX_NUMBER_IPV6_TRAN_LTE      150
#define IPSEC_PAF_PROPOSAL_MIN_NUMBER_IPV6_TRAN_LTE      1
#define IPSEC_PAF_PROPOSAL_AVAIL_NUMBER_IPV6_TRAN_LTE    150

/****************************/
/* PAF related parameters for PROFILE  */
/* we will support with No profile so the MIN val is 0 */
/****************************/
#define IPSEC_PAF_PROFILE_MAX_NUMBER            100
#define IPSEC_PAF_PROFILE_MIN_NUMBER            0
#define IPSEC_PAF_PROFILE_AVAIL_NUMBER          100

/*For testing set it Max and Avail to 50, But for release set it to 25*/
#define IPSEC_PAF_EASYVPN_MAX_NUMBER            50
#define IPSEC_PAF_EASYVPN_MIN_NUMBER            0
#define IPSEC_PAF_EASYVPN_AVAIL_NUMBER          50


/*Added by Riyaz: For deleting all ACL Groups*/
#define IPSEC_MIN_ACL_GROUP_NO                  3000
#define IPSEC_MAX_ACL_GROUP_NO                  4000

/*B058: Set Window Size for anti Replay*/
#define IPSEC_REPLAY_WINDOW_00                  0
#define IPSEC_REPLAY_WINDOW_32                  32
#define IPSEC_REPLAY_WINDOW_64                  64
#define IPSEC_REPLAY_WINDOW_128                 128
#define IPSEC_REPLAY_WINDOW_256                 256
#define IPSEC_REPLAY_WINDOW_512                 512
#define IPSEC_REPLAY_WINDOW_1024                1024
#define IPSEC_REPLAY_WINDOW_2048                2048
#define IPSEC_REPLAY_WINDOW_4096                4096

/*SGSN Changes: product supports Max policies*/
/* S9300: Max SA support */
#define IPSEC_PAF_CRYPTOMAP_MAX_NUMBER          6000
#define IPSEC_PAF_CRYPTOMAP_MIN_NUMBER          1
#define IPSEC_PAF_CRYPTOMAP_AVAIL_NUMBER        6000

/* IPv6 support */
#define IPSEC_PAF_CRYPTOMAP_MAX_NUMBER_IPV6_TRAN_LTE     100
#define IPSEC_PAF_CRYPTOMAP_MIN_NUMBER_IPV6_TRAN_LTE     1
#define IPSEC_PAF_CRYPTOMAP_AVAIL_NUMBER_IPV6_TRAN_LTE   100

#define IPSEC_PAF_MAX_APPLY_INTERFACE_NUMBER    60
#define IPSEC_PAF_MIN_APPLY_INTERFACE_NUMBER    1
#define IPSEC_PAF_AVAIL_APPLY_INTERFACE_NUMBER  60

/* V1R3_DEV_BEGIN: CACHE  */
#define IPSEC_PAF_MAX_CACHE_SIZE                2048
#define IPSEC_PAF_MIN_CACHE_SIZE                64
#define IPSEC_PAF_AVAIL_CACHE_SIZE              1024

/*SGSN License implementation - B511*/
#define IPSEC_LICENSE_ENABLE                    1
#define IPSEC_LICENSE_DISABLE                   0

/*********************************************************************/

#define IPSEC_MAX_TDB_IN_TDBENTRY        4       /* A TDB entry can have a
                                                    maximum of 4 SA's */

#define IPSEC_MAX_SUBSEQNUM                   1024
#define IPSEC_MAX_BUF_GET_SA_BULK     4096       /* Buffer Size to be Allocated
                                                    to Getting  SA in Bulk */
#define IPSEC_IKE_PORT                 500
#define IPSEC_NAT_TRAV_PORT           4500

/*DHCP Support*/
#define IPSEC_DHCP_SRV_PORT           67

/* flags defined to use in the ipsec data queue message */
#define IPSEC_ESP_FLAG          0x00000001
#define IPSEC_AH_FLAG           0x00000002
#define IPSEC_IPIP_FLAG         0x00000004
#define IPSEC_AH_IN_FLAG        0x00000008
#define IPSEC_ESP_IN_FLAG       0x00000010
#define IPSEC_OUT_PACK_FLAG     0x00000020
#define IPSEC_PKT_DBG_FLAG      0x00000040
#define IPSEC_PKT_NODBG_FLAG    0x00000080

/*Ipv6: Security Support*/
#define IPSEC_IPV6_OUT_PACK_FLAG     0x00000100
#define IPSEC_IPV6_ESP_IN_FLAG       0x00000200
#define IPSEC_IPV6_AH_IN_FLAG        0x00000400

#define IPSEC_MBUF                       0
#define IPSEC_DEST_ADDRESS               2
#define IPSEC_SPI                        1
#define IPSEC_PROTO_FLAG                 3

#define IPSEC_IPV6_TDB_FLAG              1
#define IPSEC_IPV6_HDROFF_FLAG           2

#define MAX_AUTO_TRIGGER_INTERFACE       1

/* Cache information */
#define IPSEC_LEN_4                           4
#define IPSEC_LEN_8                           8
#define IPSEC_LEN_16                         16
#define IPSEC_LEN_24                         24

#define IPSEC_STRPOS_18                      18
#define IPSEC_STRPOS_34                      34
#define IPSEC_STRPOS_40                      40
#define IPSEC_STRPOS_46                      46
#define IPSEC_STRPOS_52                      52
#define IPSEC_STRPOS_63                      63
#define IPSEC_STRPOS_71                      71

#define IPSEC_STRPOS_5                        5
#define IPSEC_STRPOS_21                      21
#define IPSEC_STRPOS_37                      37
#define IPSEC_STRPOS_43                      43
#define IPSEC_STRPOS_49                      49
#define IPSEC_STRPOS_55                      55
#define IPSEC_STRPOS_76                      76
#define IPSEC_STRPOS_84                      84


#define IPSEC_SHIFT_RIGHT_8(var)   ((var) >>  8)
#define IPSEC_SHIFT_RIGHT_16(var)  ((var) >> 16)
#define IPSEC_SHIFT_RIGHT_24(var)  ((var) >> 24)

#define IPSEC_HASH_SIZE                     257
#define IPSEC_IP_ID_BITS                      3
#define IPSEC_CACHE_HASH_6                    6
#define IPSEC_CACHE_HASH_16                  16
#define IPSEC_FLUSH_ONE_SET                  30
#define IPSEC_CACHE_SHOW_ONE_SET             30
#define IPSEC_CACHE_SPDS                    201
#define IPSEC_CACHE_SPDU                    202
#define IPSEC_CACHE_ENTRY_PRESENT_IN_SPDU   203
#define IPSEC_CACHE_ENTRY_ABSENT_IN_SPDU    204
#define IPSEC_CACHE_DEL_OUTDATED_ENTRIES    100
#define IPSEC_CACHE_DEFAULT_TIMER_VALUE     500
#define IPSEC_DEFAULT_TRACKER_VALUE         300
#define IPSEC_CACHE_MAX_AGE_TIME           3600
#define IPSEC_CACHE_MIN_AGE_TIME             30

/* Log information */
typedef enum IPSEC_LOG_ID
{
    IPSEC_LOGINFO_BKP_START = 0,
    IPSEC_LOGINFO_BKP_END,
    IPSEC_LOGERR_SA_MISSING,
    IPSEC_LOGERR_INVALID_SA,
    IPSEC_LOGERR_ALG_NOT_SUPPORTED = 4,
    IPSEC_LOGERR_TRANSMODE_MISMATCH,
    IPSEC_LOGERR_REPLAY_WRAPPED,
    IPSEC_LOGERR_DUPLICATE_RECIEVED ,
    IPSEC_LOGERR_AUTHENTICATION_FAIL=8,
    IPSEC_LOGERR_BAD_IP_HEADER,
    IPSEC_LOGERR_PACKET_TOO_BIG,
    IPSEC_LOGERR_INVALID_PAYLOAD=11,
    IPSEC_LOGERR_INVALID_PAD_LENGTH,
    IPSEC_LOGERR_DECRYPTION_FAIL,
    IPSEC_LOGERR_SOURCE_ADDR_SPOOF=14,
    IPSEC_LOGERR_ACL_MATCH_FAIL,
    IPSEC_LOGERR_IPC_SEND_FAIL,
    IPSEC_LOGERR_TRIPLE_NOT_FREE = 17,
    IPSEC_LOGERR_MEM_ALLOC_FAIL,
    IPSEC_LOGERR_GET_SA_FAIL,
    IPSEC_LOGERR_BATCH_BKUP_SND_FAIL = 20,
    IPSEC_LOGERR_BAD_DATA,
    IPSEC_LOGERR_REAL_PROCESS_FAIL,
    IPSEC_LOGERR_REAL_BKUP_SND_FAIL,
    IPSEC_LOGERR_GET_ENTRY_FAIL = 24,
    IPSEC_LOGERR_IPINIP,
    IPSEC_LOGERR_INV_ENTRY,
    IPSEC_LOGERR_SA_SRC_CHNG,
    IPSEC_LOGERR_INV_PORTS,
    IPSEC_LOGERR_SA_DELETED = 29,
    IPSEC_LOGERR_STRIPHDR_FAIL,
    IPSEC_LOGERR_CHK_PLCY,
    IPSEC_LOGERR_AUTH_DATA_MISMATCH = 32,
    IPSEC_LOGERR_INT_DEL = 33,
    IPSEC_LOGERR_PEER_NOT_PRESENT,
    IPSEC_LOGERR_TIMER_FAIL,
    IPSEC_LOGERR_PEER_DOES_NOT_EXIST,
    /* LOGS added for HW */
    IPSEC_LOGERR_SA_NOT_EXIST,
    IPSEC_LOGERR_CACHE_NOT_PRESENT,
    IPSEC_LOGERR_SA_FAIL_HW,
    IPSEC_LOGERR_CACHE_FAIL_HW = 40,
    IPSEC_LOGERR_SA_ALREADY_EXIST,
    IPSEC_LOGERR_SA_NOT_FOUND,
    IPSEC_LOGERR_SA_WITH_PEER_EXIST,
    IPSEC_LOGERR_INOUTBOUND_SA_NOT_FOUND,
    IPSEC_LOGERR_AUTHENTICATION_FAIL_V6,
    IPSEC_LOGERR_DECRYPT_ESP_PKT_V6,
    IPSEC_LOGERR_REMOVING_ESP_HDR_V6,
    IPSEC_LOGINFO_PROFILE_ADD_SPOKE,
    IPSEC_LOGINFO_PROFILE_DEL_SPOKE,
    IPSEC_LOGINFO_RRI_FQDN_PEER_ADDR_ZERO,
    IPSEC_LOGINFO_RRI_ROUTE_ADDED = 51,
    IPSEC_LOGINFO_RRI_ROUTE_DELETED,
    IPSEC_LOGINFO_MAX_ACLRULEID_USED,
    IPSEC_LOGINFO_RRI_INVLD_ACL_MASK,
    IPSEC_LOGINFO_TRIGGER_INVLD_ACL_MASK,
    IPSEC_LOGERR_MBUF_ERROR,
    IPSEC_LOGERR_HW_FAIL= 57,
    IPSEC_LOGINFO_MAX_NO,
    /* Red Line Requirement: Port Disabling changes*/
    IPSEC_LOGINFO_IKE_PORT_ENABLE_DISABLE,
    IPSEC_LOGERR_MAX_VALUE = 0xFFFFFFFF
}IPSEC_LOG_ID_E;

/* Tdb flags - denoting the states of tdb.*/
#define IPSEC_TDBF_UNIQUE           0x00001    /* This should not be used by others */
#define IPSEC_TDBF_TIMER            0x00002    /* Absolute expiration timer in use */
#define IPSEC_TDBF_BYTES            0x00004    /* Check the byte counters */
#define IPSEC_TDBF_INVALID          0x00010    /* This SPI is not valid yet/anymore */
#define IPSEC_TDBF_FIRSTUSE         0x00020    /* Expire after first use */
#define IPSEC_TDBF_HALFIV           0x00040    /* Use half-length IV(ESP old only) */
#define IPSEC_TDBF_SOFT_TIMER       0x00080    /* Soft expiration */
#define IPSEC_TDBF_SOFT_BYTES       0x00100    /* Soft expiration */
#define IPSEC_TDBF_SOFT_FIRSTUSE    0x00400    /* Soft expiration */
#define IPSEC_TDBF_PFS              0x00800    /* Ask for PFS from Key Mgmt. */
#define IPSEC_TDBF_TUNNELING        0x01000    /* Force IP-IP encapsulation */
#define IPSEC_TDBF_TRANSPORT        0x02000    /* only the payload(data) of the
                                            original IP packet is protected */
#define IPSEC_TDBF_UDP_TUNNELING    0x04000    /* Force udp encapsulation */
#define IPSEC_TDBF_UDP_TRANSPORT    0x08000
#define IPSEC_TDBF_INBOUND          0x10000    /* Inbound SA */
#define IPSEC_TDBF_OUTBOUND         0x20000    /* Outbound SA */
#define IPSEC_TDBF_SOFT_TIMER2      0x40000    /* Soft expiration */
#define IPSEC_TDBF_SOFT_TIMER3      0x80000    /* Soft expiration */

/*********************************************************************/

#define IPSEC_LIST_ENTRY(type)\
struct {\
    struct type *le_next;     /* next element */        \
    struct type **le_prev;     /* address of previous next element */   \
}

#define IPSEC_TAILQ_ENTRY(type)\
struct {\
    struct type *tqe_next;     /* next element */               \
    struct type **tqe_prev;     /* address of previous next element */  \
}

#define IPSEC_TAILQ_HEAD(name, type)\
struct name {\
    struct type *tqh_first;     /* first element */             \
    struct type **tqh_last;     /* addr of last next element */ \
}

/* AH Packet statistics */
typedef struct tagAHSTAT
{
    ULONG ahs_ulHDrops;      /* packet shorter than header shows */
    ULONG ahs_ulNoTdb;
    ULONG ahs_ulBadAuth;
    ULONG ahs_ulNoXForm;
    ULONG ahs_ulQFull;
    ULONG ahs_ulWrap;
    ULONG ahs_ulReplay;
    ULONG ahs_ulBadAuthLen;  /* bad authenticator length */
    ULONG ahs_ulInput;       /* Input AH packets */
    ULONG ahs_ulOutput;      /* Output AH packets */
    ULONG ahs_ulInDrops;     /* Dropped input AH packets */
    ULONG ahs_ulOutDrops;    /* Dropped output AH packets */
    ULONG ahs_ulInvalid;     /* Trying to use an invalid TDB */
    ULONG ahs_ulInBytes;     /* input bytes */
    ULONG ahs_ulOutBytes;    /* output bytes */
    ULONG ahs_ulTooBig;      /* packet got larger than IP_MAXPACKET */
    ULONG ahs_ulPDrops;      /* packet blocked due to policy */
    ULONG ahs_ulSecp;        /* processed successfully by SECP hardware */
    ULONG ahs_ulSecpFails;   /* processed unsuccessfully by SECP hardware */
    ULONG ahs_ulHard;        /* processed successfully by hardware */
    ULONG ahs_ulHardFails;   /* processed unsuccessfully by hardware */
    ULONG ahs_ulMiscDrops;   /* Dropped due to inv addrs family, interface addr
                                chng, inv ports, ike lookup fail, prepend fl,
                                append fail, pullup fail */
}IPSEC_AHSTAT_S;

/* ESP Packet statistics */
typedef struct tagESPSTAT
{
    ULONG esps_ulHDrops;     /* packet shorter than header shows */
    ULONG esps_ulNoTdb;
    ULONG esps_ulQFull;
    ULONG esps_ulNoXForm;
    ULONG esps_ulBadLen;
    ULONG esps_ulWrap;       /* Replay counter wrapped around */
    ULONG esps_ulBadAuth;    /* Only valid for transforms with auth */
    ULONG esps_ulReplay;     /* Possible packet replay detected */
    ULONG esps_ulInput;      /* Input ESP packets */
    ULONG esps_ulOutput;     /* Output ESP packets */
    ULONG esps_ulInDrops;    /* Dropped input ESP packets */
    ULONG esps_ulOutDrops;   /* Dropped output ESP packets */
    ULONG esps_ulInvalid;    /* Trying to use an invalid TDB */
    ULONG esps_ulInBytes;    /* input bytes */
    ULONG esps_ulOutBytes;   /* output bytes */
    ULONG esps_ulTooBig;     /* packet got larger than IP_MAXPACKET */
    ULONG esps_ulPDrops;     /* packet blocked due to policy */
    ULONG esps_ulSecp;       /* processed successfully by SECP hardware */
    ULONG esps_ulSecpFails;  /* processed unsuccessfully by SECP hardware */
    ULONG esps_ulHard;       /* processed successfully by hardware */
    ULONG esps_ulHardFails;  /* processed unsuccessfully by hardware */
    ULONG esps_ulMiscDrops;  /* Dropped due to inv addrs family, interface addr
                                chng, inv ports, ike lookup fail, prepend fl,
                                append fail, pullup fail */
}IPSEC_ESPSTAT_S;

/*IPSec SA Statistics*/
typedef struct tagIPSEC_SA_STAT
{
    /*SAs are first time established for a map*/
    ULONG ulAddAhorEspFirstSa;
    ULONG ulAddAhEspFirstSa;

    /*SAs already exist for a map and new SAs are downloaded to ipsec*/
    ULONG ulAddAhorEspNextSa;
    ULONG ulAddAhEspNextSa;

    /*Expire messages sent to IKE*/
    ULONG ulSoftExpires;
    ULONG ulSecondSoftExpires;
    ULONG ulThirdSoftExpires;

    ULONG ulHardExpires;

    /*Deletion of SAs*/
    ULONG ulDelSa;                  /* Number of times a valid SA is deleted*/

    /*These parameters are updated in case of ipsec sa rekey or
    simultaneous exchange*/
    ULONG ulDelNewSa;               /*The latest downloaded sa is deleted */
    ULONG ulDelOldSaWithinASecond;  /*The old SAs are deleted within a second
                                      of new sa download*/
    ULONG ulDelOldSaAfterASecond;   /*The old SAs are deleted after a second*/


    ULONG ulInvalidTdbCnt;

    /*DHCP Support*/
    ULONG ulInBoundDhcpPackets;
    ULONG ulOutBoundDhcpPackets;

    /*SGSN License implementation - B511*/
    ULONG ulOutBoundPacketsBypassedDueToLic;
    ULONG ulAHInBoundPacketsDroppedDueToLic;
    ULONG ulESPInBoundPacketsDroppedDueToLic;

    /*GGSN-SUPPORT*/
    ULONG ulAcquireDropped;
    /*B057 :  key deletion from IKE/IPSEC after SA establishment*/
    ULONG ulIPSECInboundKeyDelete;
    ULONG ulIPSECOutboundKeyDelete;
    ULONG ulOutBoundPacketsBypassedDueToKeyDel;
    ULONG ulAHInBoundPacketsDroppedDueToKeyDel;
    ULONG ulESPInBoundPacketsDroppedDueToKeyDel;
}IPSEC_SA_STAT_S;

typedef struct tagIPSEC_GEN_HW_NOTIFY_RCV_STAT
{
    /*Notifications sent by Hw module to IPSec*/
    ULONG ulOutBoundSaMiss;          /* Outbound SA miss */
    ULONG ulOutBoundCacheMiss;       /* Outbound Cache miss */
    ULONG ulInBoundSaMiss;           /* Inbound SA miss for a inbound IPSec
                                        packet*/
    ULONG ulNonIpsecCacheMismatch;   /* Unencrypted traffic */
    ULONG ulInputCacheMismatch;      /* Input packet post check */
    ULONG ulSaTrafficExpire;         /* haredware IPSec SA traffic expire */
    ULONG ulDpdTrigger;              /* dpd trigger  notify*/
    ULONG ulIdleCacheCleanup;        /* Cleanup the idle cache which is not used
                                        for long time */
    ULONG ulIdleSaCleanup;           /* Clearnup the idle SA which is not used
                                        for long time*/
    ULONG ulRenegotiationAfterSwitch;/* Renegotiation notification after switch
                                        happen*/
    ULONG ulInBoundSaHit;           /* Inbound SA hit for a inbound IPSec
                                        packet*/

}IPSEC_GEN_HW_NOTIFY_RCV_STAT_S;

/*Notification sent by IPSec module to Hw module*/
typedef struct tagIPSEC_GEN_HW_POLICY_STAT
{
    ULONG ulPeerDel;                /*Delete Peer info */
    ULONG ulPeerAdd;                /*Add Peer info */
    ULONG ulPolDel;                 /*Delete policy*/
    ULONG ulPolAdd;                 /* Add a policy */

    ULONG ulAclChange;              /*Acl change*/
    ULONG ulAclOnePolAdd;           /*Send Policy add with ACL*/
    ULONG ulAclOnePolDel;           /*Send Policy delete with ACL*/
    ULONG ulAclPolGrpAdd;           /*Send Policy group add with ACL*/
    ULONG ulAclPolGrpDel;           /*Send Policy group delete with ACL*/
    ULONG ulAclPolCfgChange;        /*Configuration change in one policy */
}IPSEC_GEN_HW_POLICY_STAT_S;

/*DPD messages*/
typedef struct tagIPSEC_GEN_HW_DPD_STAT
{
    ULONG ulSetOnDemanDpd;          /*Setting of on demand dpd flag*/
    ULONG ulGetInbPktCntZero;       /*Get for inbound packet count */
    ULONG ulGetInbPktCntNonZero;    /*Get for inbound packet count */
}IPSEC_GEN_HW_DPD_STAT_S;

/*SA stats*/
typedef struct tagIPSEC_GEN_HW_SA_STAT
{
    ULONG ulAddNewAhorEspSA;        /*Add newly negotiated SA -1 Pair*/
    ULONG ulAddNewAhEspSA;          /*Add newly negotiated SA -2 Pairs*/
    ULONG ulAddExistingAhorEspSA;   /*Add Existing SAs -1 Pair*/
    ULONG ulAddExistingAhEspSA;     /*Add Existing SAs -2 Pairs*/
    ULONG ulUpdateAhorEspSA;        /*Updatd Existing SAs -1 Pair*/
    ULONG ulUpdateAhEspSA;          /*Add Existing SAs once again -1 Pair*/
    ULONG ulDelSA;                  /*Del SA, child next/previous SA exist*/
    ULONG ulDelNoSAInSw;            /*Send delete to SA which is present in hw
                                    but not in sw*/
    /*SA warnings to hardware*/
    ULONG ulWarnSaGoingToFull;
    ULONG ulWarnSaFull;
}IPSEC_GEN_HW_SA_STAT_S;


typedef struct tagIPSEC_SA_EXP_STAT
{
    /*SAs are first time established for a map*/
    ULONG ulNoOfTimesSoftExpSent;
    ULONG ulNoOfTimesSoft2ExpSent;
    ULONG ulNoOfTimesSoft3ExpSent;

    ULONG ulNoOfTimesHardExpSent;
    ULONG ulNoOfTimesAccuireSent;

    ULONG ulNoOfTimesSAUpdateRecv;
    ULONG ulNoOfTimesSAFillTEntryRecv;
    ULONG ulNoOfTimesSAAddRecv;
    ULONG ulNoOfTimesSADelRcv;

    ULONG ulNoOfTimesErrinIKERcv;

    ULONG ulNoOfTimesGetCryptoFail;
    /*B061: Hardware traffic trigger*/
    ULONG ulNoOfHwTrafficBasedTrigger;

}IPSEC_SA_EXP_S;


/*Secure Cache Stats*/
typedef struct tagIPSEC_GEN_HW_SEC_CACHE_STAT
{
    ULONG ulSecCacheAdd;            /*secure cache add*/
    ULONG ulSecCacheAddWithSa;      /*Sec cache add with SA*/
    ULONG ulSecCacheDel;            /*secure cache delete*/
    ULONG ulResetSecCache;          /*Reset secure cache entries*/
    ULONG ulNoSecCacheDel;          /*Send del for inconsistent cache entries*/
    ULONG ulCleanupSecCache;        /*Send del cache while cleanup*/

    /*Cache warnings to hardware*/
    ULONG ulWarnSecCacheGoingToFull;
    ULONG ulWarnSecCacheFull;

}IPSEC_GEN_HW_SEC_CACHE_STAT_S;

/*Unsecure Cache Stats*/
typedef struct tagIPSEC_GEN_HW_UNSEC_CACHE_STAT
{
    ULONG ulUnSecCacheAdd;          /*unsecure cache add*/
    ULONG ulResetUnSecCache;        /*Reset unsecure cache entries*/
    ULONG ulCleanupUnSecCache;      /*Send del cache while cleanup*/

    /*Cache warnings to hardware*/
    ULONG ulWarnUnSecCacheGoingToFull;
    ULONG ulWarnUnSecCacheFull;
}IPSEC_GEN_HW_UNSEC_CACHE_STAT_S;

/*Statistics for input output Ah/ESP packets downloaded to hardware for
ipsec processing*/
typedef struct tagIPSEC_GEN_HW_PACKET_STAT
{
    ULONG ulDwnAHOutPacket;
    ULONG ulDwnESPOutPacket;
    ULONG ulDwnAhInPacket;
    ULONG ulDwnEspInPacket;
}IPSEC_GEN_HW_PACKET_STAT_S;


/*IPSec Hardware Statistics:
This structure contain statistics of all the messages
received from and sent to hardware module*/
typedef struct tagIPSEC_GEN_HW_STAT
{
    IPSEC_GEN_HW_NOTIFY_RCV_STAT_S stNotifyRcv;
    IPSEC_GEN_HW_POLICY_STAT_S stPolicy;
    IPSEC_GEN_HW_DPD_STAT_S stDpd;
    IPSEC_GEN_HW_SA_STAT_S stSA;
    IPSEC_GEN_HW_SEC_CACHE_STAT_S stSecCache;
    IPSEC_GEN_HW_UNSEC_CACHE_STAT_S stUnSecCache;
    IPSEC_GEN_HW_PACKET_STAT_S stPkt;
}IPSEC_GEN_HW_STAT_S;


/*Iteration2: Story12: Maintainance*/
typedef struct tagIPSEC_PFKEYV2_STATS_S
{
    ULONG ulAcquireSent;
    ULONG ulExpireSent;
    ULONG ulGetMapRcvd;
    ULONG ulGetSPIRcvd;
    ULONG ulGrpSPIRcvd;
    ULONG ulFillRcvd;
    ULONG ulDeleteRcvd;
    ULONG ulDPDNotifyRcvd;
    ULONG ulDPDReqSentSuccess;
    ULONG ulModecfgNotifyRcvd;
    ULONG ulReleaseProductSPI;
    ULONG ulGenProductSPI;
    ULONG ulIPSecKickOldSaWithSameFlow;
}IPSEC_PFKEYV2_STATS_S;

typedef struct tagIPSEC_MSGPARSE_FAIL_S
{
    ULONG ulMsgType; /* Latest Msg for which parsing was failed.*/
}IPSEC_MSGPARSE_FAIL_S;

typedef struct tagIPSEC_GETPOLICYFAIL_S
{
    ULONG ulNoPeer;
    ULONG ulBuildMsgtoIKE;
    ULONG ulFindCryptoMapFailed;

    /*Defect:A75D05538*/
    ULONG ulInvDestIPforTemplate;
    ULONG ulVrfIndexMisMatch;
}IPSEC_GETPOLICYFAIL_S;

/*GGSN*/
typedef struct tagIPSEC_DYNATDBENTRY_FAIL_S
{
    ULONG ulInsertEntryFail;
    ULONG ulRemoveEntryFail;
    ULONG ulCreateMaskEntryFail;
    ULONG ulGetMaskEntryFail;
    ULONG ulCreateHashTableFail;
    ULONG ulDeleteHashTableFail;
    ULONG ulInvMaskEntry;
}IPSEC_DYNATDBENTRY_FAIL_S;

typedef struct tagIPSEC_DYNAPEER_FAIL_S
{
    ULONG ulCreatePeerFail;
    ULONG ulRemovePeerFail;
    ULONG ulCreateDPDTimerFail;
}IPSEC_DYNAPEER_FAIL_S;

typedef struct tagIPSEC_FIND_TDBENTRY_FAIL_S
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulIfIndex;
}IPSEC_FIND_TDBENTRY_FAIL_S;

typedef struct tagIPSEC_PFKEYV2_FAIL_STATS
{
    ULONG ulAcquireSentFail;
    ULONG ulExpireSentFail;
    ULONG ulGetPolicyFail;
    ULONG ulGetSPIRcvdFail;
    ULONG ulGrpSPIRcvdFail;
    ULONG ulFillSAFail;
    ULONG ulFillEntryRcvdFail;
    ULONG ulDeleteRcvdFail;
    ULONG ulDPDNotifyRcvdFail;
    ULONG ulModecfgNotifyRcvdFail;
    ULONG ulMsgParseFail;
    ULONG ulFindEntryFail;
    ULONG ulDynaEntryExist;
    ULONG ulUpdatePh1ConnIdFail;
    ULONG ulReserveSPIFail;   /*Kranthi:*/
    ULONG ulReleaseSPIFail;
    ULONG ulInvOutLinkTdbs;
    ULONG ulInvInLinkTdbs;
    ULONG ulDPDFindPeerFail;
    ULONG ulDPDReqSentFailure;
    ULONG ulFindMapbyPeerFail;
    ULONG ulSPIExist;
    ULONG ulInTdbNotFoundDuringFill;
    ULONG ulOutTdbNotFoundDuringFill;
    ULONG ulInvalidIfIndxDuringFill;
    ULONG ulDPDProcessFail;
    ULONG ulUpdateTdbFortdbEntryFail;
    ULONG ulInTdbNotFound;
    ULONG ulOutTdbAlreadyExist;
    ULONG ulInvOutboundSPI;
    ULONG ulGetPh1ConnIdFail;
    ULONG ulPfkeyv2SendFail;
    IPSEC_FIND_TDBENTRY_FAIL_S stFindEntryFail;
    IPSEC_MSGPARSE_FAIL_S stMsgParseFail;
    IPSEC_GETPOLICYFAIL_S stGetPolicyFail;
    IPSEC_DYNATDBENTRY_FAIL_S stDynaTdbEntryFail;
    IPSEC_DYNAPEER_FAIL_S stDynaPeerFail;
}IPSEC_PFKEYV2_FAIL_STATS_S;

typedef struct tagIPSEC_ACQUIREFAIL_S
{
    USHORT usSockNotReg;
    USHORT usDscpFlowMisMatch;
    USHORT usNoCryptoMap;
    USHORT usNoPeer;
    USHORT usZeroProposal;
    USHORT usBuildMsgtoIKE;
}IPSEC_ACQUIREFAIL_S;

typedef struct tagIPSEC_FillRcvdFail_S
{
    USHORT usInSaFail;
    USHORT usOutSaFail;
    USHORT usGrpSaFail;
    USHORT usFindSaFail;
    USHORT usDynaEntryExistFail;
    USHORT usDynaModecfgFail;
    USHORT usSetTsFail;
    USHORT usUpdateDPDFail;
}IPSEC_FILLRCVDFAIL_S;

typedef enum tagIPSEC_FillRcvdFail_E
{
    IPSEC_FILLRCVD_INSA,
    IPSEC_FILLRCVD_OUTSA,
    IPSEC_FILLRCVD_GRPSA,
    IPSEC_FILLRCVD_FINDSA,
    IPSEC_FILLRCVD_DYNACFG,
    IPSEC_FILLRCVD_SETTS,
    IPSEC_FILLRCVD_UPDATEDPD,
    IPSEC_FILLRCVD_DYNAENTRYEXIST
}IPSEC_FILLRCVDFAIL_E;

typedef struct tagIPSEC_PFKEYV2_MAP_STATS_S
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulDestAddr; /* Peer Remote Address*/
    ULONG usAcquireSent;
    USHORT usExpireSent;
    USHORT usFillRcvd;
    USHORT usDeleteRcvd;
    USHORT usAcquireSentFail;
    USHORT usFillRcvdFail;
    USHORT usIkeGetMapRespFail;
    USHORT usIkeGetSPIFail;
    USHORT usIkeGrpSPIFail;
    USHORT usIKEFillFail;
    USHORT usIKEDeleteFail;
    USHORT usRekeyFail;
    USHORT usResv;
    IPSEC_ACQUIREFAIL_S stAcquireFail;
    IPSEC_FILLRCVDFAIL_S stFillRcvdFail;
}IPSEC_PFKEYV2_MAP_STATS_S;

typedef struct tagIPSEC_PFKEYV2_SHOWMAPSTATS_S
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    IPSEC_PFKEYV2_MAP_STATS_S stStats;
}IPSEC_PFKEYV2_SHOWMAPSTATS_S;

/* Ipsec Proposal parameters*/
typedef struct tagCryptoTransform
{
    IPSEC_LIST_ENTRY (tagCryptoTransform) link;
    ULONG ulMemHead;
    CHAR szTransformName[IPSEC_MAX_TRANSFORM_NAME + 1];
    ULONG  ah; /*ah protocol id (new/old)*/
    ULONG  esp; /*esp protocol id (new/old)*/
    ULONG  ipcomp; /*ip compression algorithm*/
    USHORT InitVectorSize; /*IV size*/
    USHORT transform; /*AH, ESP, AH/ESP*/
    UCHAR ucTransformMode; /*Tunnel/Transport*/
    UCHAR ucReserved[3];
} IPSEC_CryptoTransform_S;

/***************************************************************
 * If the crypto map's transform set includes a DES algorithm, *
 * specify at least 8 bytes per key,                           *
 * If the crypto map's transform set includes a MD5 algorithm, *
 * specify at least 16 bytes per key,                          *
 * If the crypto map's transform set includes a SHA algorithm, *
 * specify at least 20 bytes per key,                          *
 ***************************************************************/
typedef struct tagManualPara  /* crypto map manual mode parament */
{
    ULONG ulMemHead;
    ULONG ulAHSPI;
    ULONG ulESPSPI;
    ULONG ulAhHexKeyLength;
    ULONG ulEspCipherHexKeyLength;
    ULONG ulEspAuthenHexKeyLength;
    ULONG ulAhStringKeyStringLength;
    ULONG ulEspStringKeyStringLength;

    /* session-key string */
    UCHAR ucAhHexKeyString[IPSEC_MAX_MANUAL_KEY_LENGTH];
    UCHAR ucEspCipherHexKeyString[IPSEC_MAX_MANUAL_CIPHER_KEY_LENGTH];
    UCHAR ucEspAuthenHexKeyString[IPSEC_MAX_MANUAL_AUTHENTICATOR_KEY_LENGTH];
    UCHAR ucAhStringKeyString[IPSEC_DOUBLE_SHA2_DIGEST_LENGTH];
    UCHAR ucEspStringKeyString[IPSEC_DOUBLE_SHA2_DIGEST_LENGTH];

    /* clear-text key string */
    UCHAR szAhHexKeyClearString[IPSEC_MAX_KEY_STRING_LENGTH];
    UCHAR szEspCipherKeyClearString[IPSEC_MAX_KEY_STRING_LENGTH];
    UCHAR szEspAuthenKeyClearString[IPSEC_MAX_KEY_STRING_LENGTH];
    UCHAR szAhStringKeyClearString[IPSEC_MAX_KEY_STRING_LENGTH];
    UCHAR szEspStringKeyClearString[IPSEC_MAX_KEY_STRING_LENGTH];
} IPSEC_ManualPara_S;

/* Ipsec Policy */
typedef struct tagCryptoMapInfo
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szDynaMapName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szIkePeerName[IPSEC_PEER_NAME_MAX_LEN];
    CHAR szTransformName[IPSEC_CRYPTOMAP_MAX_TRANSFORM_NUM]\
                        [IPSEC_MAX_TRANSFORM_NAME + 1];
    ULONG ulDynamicSeq;
    ULONG ulLocalAddr;
    ULONG ulSequenceNumber;
    ULONG ulPeerAddr[IPSEC_CRYPTO_MAP_MAXPEERS]; /* peer addrs for isakmp*/
    ULONG ulVrfIndex;              /* peer vpn for manual*/
    ULONG ulPeerAddrManual;        /* peer addrs for manual */
    USHORT usListNumber;
    USHORT usPeers;    /* the number of peer , only for isakmp*/
    ULONG ulSALifetimeKilobytes;  /* for ipsec_isakmp */
    ULONG ulSALifetimeSeconds;    /* for ipsec_isakmp */

    UCHAR ucSaMode;               /* 0-isakmp, 1-manual, 2-dynamic */
    UCHAR ucPFS;
    UCHAR ucLifeTimeIsPrivate;    /* the lifetime is private or global value */
    UCHAR ucKilobytesFlag;        /* if is global lifetime */
    ULONG ulTrafficSelect;        /* 0 Diable, 1 Enable */

    /* AC4D07629: Updated for suggession address */
    ULONG ulModeCfgSugAddr;
    ULONG ulModeCfgSugMask;
    ULONG ulReplayWindowSize;     /*B058: Replay Window Size*/

    IPSEC_ManualPara_S stInbound;    /* for ipsec_manual inbound */
    IPSEC_ManualPara_S stOutbound;   /* for ipsec_manual outbound */
    UCHAR ucAddrType;             /*Added for ipv6 support*/
    UCHAR ucSecondsFlag;          /* if is global lifetime */
    UCHAR ucSaTriggerMode;        /* 0 Auto, 1 traffic based */
    UCHAR ucByProfile;            /* Policy created by profile or not */
    IN6ADDR_S stLocalAddr;        /* IPv6 local address  */
    IN6ADDR_S stPeerAddrManual;   /* IPv6 Peer Address*/

    ULONG ulRRIPreference;          /* Preference */
    UCHAR ucRRIMode;                /* RRI Mode:  1- static, 2- Dynamic */
    UCHAR ucACLVer;                 /* ACL Version, required for v4-over-v6 and v6-over-v4 display*/
    UCHAR ucResv[2];                /* Padding bytes */
} IPSEC_CryptoMap_Info_S;

/*Temp :*/

typedef struct tagIPSEC_SOCKADDR_CMN_S
{
    UCHAR ucLen;
    UCHAR ucFamily;
    SHORT usPort;
}IPSEC_SOCKADDR_CMN_S;

union sockaddr_union
{
    SOCKADDR_S  sa;
    struct tagSOCKADDRIN sin;
    struct tagSOCKADDR_IN6 stSin6;
};

/* This structure is used as function parameter to pass policy name and
   sequence number */
typedef struct tagIPsecPolicyNameAndSeq
{
    CHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulPolicySeq;
} IPSEC_POLICY_NAME_SEQ_S;

/* Structure storing the policy name,template name and sequence */
typedef struct tagIPsecPolicy
{
    UCHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    UCHAR szDynaMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
}IPSEC_POLICY_S;

/* Structure storing the spi configuration parameters */
typedef struct tagIPsecSPIParam
{
    UCHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulFlag;
    ULONG ulSpiValue;
}IPSEC_SPI_PARAM_S;

/* Structure storing the SA key configuration parameters */
typedef struct tagIPsecKeyParam
{
    UCHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulFlag;
    UCHAR szKey[IPSEC_MAX_KEY_STRING_LENGTH];
}IPSEC_KEY_PARAM_S;

/* This structure is used to set the sa lifetime within an isakmp policy */
typedef struct tagIPsecSALifeTime
{
    UCHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulPeriodsType;    /*SA life time, traffic based or time based*/
    ULONG ulPeriods;        /*IPSec sa lifetime in seconds or kilo bytes*/
}IPSEC_SA_LIFETIME_PARAM_S;


/*Template policy content*/
typedef struct tagIPsecTemplateContent
{
    CHAR szTemplateName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szProposalName[IPSEC_CRYPTOMAP_MAX_TRANSFORM_NUM]\
                        [IPSEC_MAX_TRANSFORM_NAME + 1];
    CHAR szIKEPeerName[IPSEC_PEER_NAME_MAX_LEN];
    UCHAR ucPFSType;  /*type of Perfect forward secrecy */
    UCHAR ucReserved[3];
    ULONG ulPolicySeq;
    ULONG ulACLNumber;
    ULONG ulSALifetimeSeconds;
    ULONG ulSALifetimeKilobytes;
} IPSEC_TEMPLATE_CONTENT_S;

/*This structure contains IPSEC Proposal related information, authentication
and encryption algorithm ID for AH and ESP*/
typedef struct tagIPsecProposalContent
{
    CHAR szProposalName[IPSEC_MAX_TRANSFORM_NAME + 1];
    ULONG ulOpMode;
    ULONG ulEncapMode;
    ULONG ulTransProtocol;
    ULONG ulESPAuthAlgorithm;
    ULONG ulESPEncrAlgorithm;
    ULONG ulAHAuthAlgorithm;
    ULONG ulCompressionAlgorithm;
} IPSEC_PROPOSAL_CONTENT_S;


/*Ipv6: Security Support*/
typedef union tagIPsecGenericIPAddr
{
    ULONG ulDestAddr;
    IN6ADDR_S stDestIPv6Addr;
} IPSEC_GENERIC_ADDR_S;

typedef struct tagIPsecGenericIPAddrVer
{
    IPSEC_GENERIC_ADDR_S stIPAddr;
    UCHAR ucAddrType;
    UCHAR ucReserved[3];
}IPSEC_GENERIC_IPADDRVER_S;
/*IPSEC SA*/
typedef struct tagIPsecSAParameters
{
    ULONG ulDestAddr;
    ULONG ulProtocol;
    ULONG ulSPI;
    ULONG ulIfIndex;    /*Interface index*/
} IPSEC_SA_PARA_S;
/*Ipv6: Security Support*/
/*IPv6 SA parameters*/
typedef struct tagIPsec6SAParameters
{
    ULONG ulProtocol;
    ULONG ulSPI;
    ULONG ulIfIndex;    /*Interface index*/
    IN6ADDR_S stDestIPv6Addr;
} IPSEC6_SA_PARA_S;

/*Ipv6: Security Support*/
/*Ipv4 and Ipv6 SA parameter combined*/
typedef struct tagIPsecSACommonParameters
{
    ULONG ulProtocol;
    ULONG ulSPI;
    ULONG ulIfIndex;    /*Interface index*/
    UCHAR ucIPVer;
    UCHAR ucRes[3];
    IPSEC_GENERIC_IPADDRVER_S stDestIPAddr;
} IPSEC_SA_PARACMN_S;


/*This strucuture keeps record of IPSEC Traffic STATISTICS according to
various event occurred during inbound outbound packet processing*/
typedef struct tagIPsecIPSECStat
{
    ULONG ulInputPackets;
    ULONG ulOutputPackets;
    ULONG ulInputBytes;
    ULONG ulOutputBytes;
    ULONG ulInputDropPackets;
    ULONG ulOutputDropPackets;
    ULONG ulNoEnoughMemory;
    ULONG ulCanntFindSASum;
    ULONG ulQueueIsFullSum;
    ULONG ulAuthFailedSum;
    ULONG ulBadLenSum;
    ULONG ulReplayPacketSum;
    ULONG ulTooLongPacketSum;
    ULONG ulWrongSASum;
    ULONG ulNoXFormPacket;
    ULONG ulReplayWrap;
    ULONG ulPolicyPktDrop;
    ULONG ulMiscDrop;
    ULONG ulHardFails;
} IPSEC_STAT_S;

/* Used to index the tdb from tdb entry */
typedef struct tagTdbIndex
{
    ULONG ulPeerAddr;
    ULONG ulSpi;
    UCHAR ucProto;

    UCHAR ucDirection; /* Changed by Sumangala for TRAN */

    USHORT  usAclNo;
    ULONG ulIfIndex;

    /*Ipv6: Security Support*/
    /* VOID  *pvIPsec6PeerAddr; //Added for IPV6 Support*/
    UCHAR ucAddrType;
    UCHAR ucResv[3];
} IPSEC_TdbIndex_S;


#ifndef TCPIP_IN_VRP
#ifdef  IPOS_INVRP
#define TCPIP_IN_VRP             VRP_YES
#else
#define TCPIP_IN_VRP             VRP_NO
#endif
#endif

/* This structure is used to form TdbEntry message to send it to hardware */
typedef struct tagIPsecIPsecSAEntryContent
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulSequenceNumber;
    ULONG ulConnId;
    ULONG ulLocalAddr;
    ULONG ulPeerAddr;
    USHORT usListNumber;
    USHORT usOpMode;
    UCHAR ucSaMode; /* manual, isakmp, dynamic */
    UCHAR ucOutboundTdbFlags;
    UCHAR ucInboundTdbFlags;
    UCHAR ucPacketDebug;        /* Tunnel debugging switch. */
    IPSEC_TdbIndex_S stInTdbIndex;
    IPSEC_TdbIndex_S stOutTdbIndex;
    UCHAR ucSaTriggerMode;
    UCHAR ucReserved[3];
#if (TCPIP_IN_VRP == VRP_NO)
    ACL_Item stFlow;
#else
    IPOS_ACL_Item stFlow;
#endif
    VOID *pvIPsec6InfoBlk;  /*Added for ipv6 support */
}IPSEC_SA_ENTRY_CONTENT_S;

/*This structure serves as the head of list of crypto maps pertaining to a
crypto map group*/
typedef struct tagMapGroupHead
{
    IPSEC_TAILQ_ENTRY (tagMapGroupHead) link;
    ULONG ulMemHead;
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    USHORT usIfReference;    /* the number of interface used this crypto map */
    USHORT usMapNumber;      /* the number of the map in this map group */
    UCHAR ucMode;            /* 0-Statics 2-dynamic */
    UCHAR ucAddrType;        /* Address Family Type 4 for IPv4, 6 For IPv6 */
    UCHAR ucByProfile;       /* Spawned by profile */
    UCHAR ucProtectV4CtrlTraff; /* 1 = allow v4 ike messags in v6 tunnel, 0 = do not allow */
    UCHAR ucEasyVPNMode;
    UCHAR ucReserved[3];
    ULONG ulLocalAddr;
    ULONG ulLocalIfIndex;
    IPSEC_TAILQ_HEAD (tagCryptoMaps, tagCryptoMap) stMaps;/*points to mapgroup*/
} IPSEC_MapGroupHead_S;


/* Used to store information required to get the sa's */
typedef struct tagShow_Sa
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    USHORT usMsgType;
    USHORT usSubMsgType;
    ULONG ulIfIndex;
    ULONG ulMapSeq;
    ULONG ulPeerAddr;
    ULONG ulSpi;
    UCHAR ucProto;
    UCHAR ucSlot;
    UCHAR ucAddrType;    /*Added for ipv6 support*/
    UCHAR ucReseved;
    IN6ADDR_S stIPsec6PeerAddr; /*Added for ipv6 support*/
}IPSEC_SHOW_SAINFO_S;


/* Used to get waitlist handles required during display of SA's */
typedef struct tagShowHandles
{
    ULONG ulErrcode;
    ULONG ulMapIfWaitListHandle;
    ULONG ulTdbEntryIndex;
    ULONG ulDynaEntryIndex;
    ULONG ulTdbWaitIndex;
    ULONG ulNoOfTdbReturn; /*Number of TDBs fetched for display*/

    /* V1R3_DEV_BEGIN: MODECFG  */
    /* Defect ID: AC4D05218*/
    ULONG ulModeCfgTdbEntryIndex;

    /* V1R3_DEV_END: MODECFG */
}IPSEC_SHOWSA_HANDLE_S;

/* Used to get waitlist handle & the hash index required
during the display of cache.*/
typedef struct tagIPSEC_SHOWCACHE_HANDLE_S
{
    ULONG ulCount;
    ULONG ulCacheHandle;
    ULONG ulEndOfData;
    ULONG ulSlot;
}IPSEC_SHOWCACHE_HANDLE_S;

/* Used to get interface details required during display of SA's */
typedef struct tagInterfaceDetails
{
    CHAR szInterfaceName[IPSEC_MAX_INTERFACE_NAME_LEN];
    ULONG ulIntPathMtu; /*Path MTU set on the interface*/
    ULONG ulNoOfSaEntries;
    ULONG ulNoOfSAs;
    UCHAR ucIsTunnelXface;
    UCHAR ucTunnelMode;
    UCHAR ucResv[2];
}IPSEC_SHOW_INTERFACE_S;


/* Used to set paf controllable parameters of IPSec */
typedef struct tagIPSEC_PAF_VALUES
{
    ULONG ulMaxProposals_Avail;
    ULONG ulMaxPolicy_Avail;
    ULONG ulMaxApplyInterface_Avail;

    ULONG ulMaxCacheSize_Avail;
    ULONG ulMaxProfiles_Avail;
    ULONG ulMaxEasyVPNProfiles_Avail;

}IPSEC_PAF_VALUES_S;

/* Sync mesasges for VT interface */
typedef struct tagIPSEC_VT_SYN_Msg
{
    ULONG  ulCurbytes;    /* Bytes processed  */
    ULONG  ulRpl;         /* Replay window  */
}IPSEC_VT_SYN_MSG_S;

/* Structure used by ike to send peer information to IPsec */
typedef struct tagIPSEC_PEER_INFO_S
{
    CHAR szPeerName[IPSEC_MAX_PEERNAME_LEN + 1];
    ULONG ulPeerIndex;
    ULONG ulPeerId;         /* Local id type, name or IP */
    ULONG ulAddress;        /* Peer address in Host Order */
    ULONG ulEndAddress;     /* Peer end address, Host Order */
    ULONG ulExchangeMode;   /* Exchange mode for peer (main, aggr) */
    ULONG ulIdleTime;       /* DPD configured  idle time*/
    ULONG ulVrfIndex;
    USHORT usSrcSubNetType; /* Source subnet, for IP address or mask */
    USHORT usDstSubNetType; /* Destination subnet, for IP address or mask */
    UCHAR ucDPD_Enable;     /* Enable/Disable DPD flag*/
    UCHAR ucDPD_Type;       /* periodic/on-demand*/
    UCHAR ucModeCfgType;    /* Mode-cfg flag enable/disable*/
     /*IKEV2*/
    UCHAR ucDPDVIDVerdict;
    UCHAR ucIKEVersion;
    UCHAR ucAddrType;
    UCHAR ucUseAllSupportedAlg; /* Auto VPN support */
    UCHAR ucFQDNState;      /* FQDN state of the peer */
    UCHAR ucRemoteIPType;   /* To check if user configured IP directly or FQDN */
    UCHAR ucReserved[3];
    IN6ADDR_S stAddress;    /* Kranthi :Added for IPv6Peer address in Host Order */
    IN6ADDR_S stEndAddress;
    ULONG ulLocalAddr;   /*NAG:IPSEC_PROF_GetTunnelStatus : Tunnel Local address. Useful for Profile*/
    IN6ADDR_S stLocalAddress; /* sandeep :Added for IPv6 Peer Local address, Host Order */
    UCHAR ucIsAutoTriggerEnabled; /* This field is used to control the auto trigger for master and backup peers */
    UCHAR ucPeerType;             /* This field is used to identify the peer type(master/backup/normal) */
    UCHAR ucPad[2];
}IPSEC_PEER_INFO_S;

 /* IPSec DO Feature */
typedef struct tagIPSEC_DO_STATS
{
   ULONG ulPeerDOAddCount;
   ULONG ulPeerDODelCount;
   ULONG ulPolicyDOAddCount;
   ULONG ulPolicyDODelCount;
   ULONG ulSADOAddCount;
   ULONG ulSADODelCount;
} IPSEC_DO_STATS_S;

/*HERT 3.4 DO requirement*/
#define IPSEC_GET_PEER_DO_STATS   1
#define IPSEC_GET_POLICY_DO_STATS 2
#define IPSEC_GET_SA_DO_STATS     3

/* Structure used by IKE to get the policy name and address for a peer */
typedef struct tagIPSEC_POLICY_AND_PEER_INFO_S
{
    CHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulAddress;
    ULONG ulSequenceNumber;
}IPSEC_POLICY_AND_PEER_INFO_S;

/* Enum for various error conditions that might occur */
enum tagIPSECErr
{
    IPSEC_OK,                                          /* 0  */
    IPSEC_ERR,                                         /* 1  */
    IPSEC_ERR_INVALID_PARA,                            /* 2  */
    IPSEC_ERR_NO_MEMORY,                               /* 3  */
    IPSEC_ERR_NOT_ISAKMP_MODE,                         /* 4  */
    IPSEC_ERR_NOT_ISAKMPORDYN_MODE,                    /* 5  */
    IPSEC_ERR_NOT_MANUAL_MODE,                         /* 6  */
    IPSEC_ERR_NOT_AH,                                  /* 7  */
    IPSEC_ERR_NOT_ESP,                                 /* 8  */
    IPSEC_ERR_NO_POLICY,                               /* 9  */
    IPSEC_ERR_NO_PROPOSAL,                             /* 10 */
    IPSEC_ERR_NO_VPN_INSTANCE,                         /* 11 */
    IPSEC_ERR_NO_TUNNEL_PEERADDR,                      /* 12 */
    IPSEC_ERR_NO_TUNNEL_LOCALADDR,                     /* 13 */
    IPSEC_ERR_NO_TEMPLATE,                             /* 14 */
    IPSEC_ERR_NO_SA,                                   /* 15 */
    IPSEC_ERR_NO_INTERFACE,                            /* 16 */
    IPSEC_ERR_POLICY_EXIST,                            /* 17 */
    IPSEC_ERR_PROPOSAL_EXIST,                          /* 18 */
    IPSEC_ERR_MAPINTERFACE_EXIST,                      /* 19 */
    IPSEC_ERR_TEMPLATE_EXIST,                          /* 20 */
    IPSEC_ERR_NO_MAPINTERFACE,                         /* 21 */
    IPSEC_ERR_MAX_PROPOSAL_CONFIGURED,                 /* 22 */
    IPSEC_ERR_MAX_POLICY_CONFIGURED,                   /* 23 */
    IPSEC_ERR_PROPOSAL_IMPORT_MAX,                     /* 24 */
    IPSEC_ERR_LACK_POLICY_PARA,                        /* 25 */
    IPSEC_ERR_ENCY_AUTH_NULL,                          /* 26 */
    IPSEC_ERR_NO_PROPOSAL_ON_POLICY,                   /* 27 */
    IPSEC_ERR_TUNNEL_PEERADDR_EXIST,                   /* 28 */
    IPSEC_ERR_TEMPLATE_TYPE,                           /* 29 */
    IPSEC_ERR_TEMPLATE_IN_USE,                         /* 30 */
    IPSEC_ERR_POLICY_DYNAMIC_GROUP,                    /* 31 */
    IPSEC_ERR_MANUAL_POLICY_MULTI_USE,                 /* 32 */
    IPSEC_ERR_POLICY_NO_ACL,                           /* 33 */
    IPSEC_ERR_ISAKMP_POLICY_NO_PEER,                   /* 34 */
    IPSEC_ERR_POLICY_APPLY_IF_MAX,                     /* 35 */
    IPSEC_ERR_GET_RECORD_NUM_REDUCED,                  /* 36 */
    IPSEC_ERR_NOT_TEMPLATE_TYPE,                       /* 37 */
    IPSEC_ERR_VPN_NO_SET_VRF,                          /* 38 */
    IPSEC_ERR_NO_MAP_SUCH_POLICY,                      /* 39 */
    IPSEC_ERR_DYNATEMPLET_TYPE,                        /* 40 */
    IPSEC_ERR_IKE_NO_IKEPEER,                          /* 41 */
    IPSEC_ERR_IKE_PEER_REMOTE_ADDRESS_NOT_SINGLE,      /* 42 */
    IPSEC_ERR_IKE_PEER_NO_REMOTE_ADDRESS,              /* 43 */
    IPSEC_ERR_IKE_MULTI_PEER_ADDRESS,                  /* 44 */
    IPSEC_ERR_CHANGE_MODE,                             /* 45 */
    IPSEC_ERR_ADD_STATIC_TO_DYNA,                      /* 46 */
    IPSEC_ERR_ADD_DYNATOSTATIC,                        /* 47 */
    IPSEC_ERR_ONE_TEMPLATEINPOLICYGROUP,               /* 48 */
    IPSEC_ERR_PROCESS_IN_SOFTWARE,                     /* 49 */
    IPSEC_ERR_MAP_POLICY_EXIST,                        /* 50 */
    IPSEC_ERR_WAITLIST_REG,                            /* 51 */
    IPSEC_ERR_WAITLIST_SET_FAIL,                       /* 52 */
    IPSEC_ERR_WAITLIST_GET_FAIL,                       /* 53 */
    IPSEC_ERR_NO_SA_MAP,                               /* 54 */
    IPSEC_ERR_IF_PORTTYPE_FAIL,                        /* 55 */
    IPSEC_ERR_HA_GET_DATA,                             /* 56 */
    IPSEC_ERR_NO_SA_ENTRY,                             /* 57 */
    IPSEC_ERR_NO_KEY,                                  /* 58 */
    IPSEC_ERR_IPC_RPC_FAIL,                            /* 59 */
    IPSEC_ERR_NO_MORE_ENTRY,                           /* 60 */
    IPSEC_ERR_NO_DYNAPOLICYGROUP,                      /* 61 */
    IPSEC_ERR_DISPSA_DONE,                             /* 62 */
    IPSEC_ERR_MAX_PEERS_SET,                           /* 63 */
    IPSEC_ERR_IF_GET_SAHEAD_FAIL,                      /* 64 */
    IPSEC_ERR_IF_SET_SAHEAD_FAIL,                      /* 65 */
    IPSEC_ERR_MEMORY_SHORTAGE,                         /* 66 */
    IPSEC_ERR_INVALID_SA_MODE,                         /* 67 */
    IPSEC_ERR_STRINGKEY_2LONG,                         /* 68 */
    IPSEC_ERR_VPN_COMP_NOT_AVAILABLE,                  /* 69 */
    IPSEC_ERR_NO_HARDWARE,                             /* 70 */
    IPSEC_ERR_SAS_NOT_SYNC,                            /* 71 */
    IPSEC_ERR_INVALID_POLICY_MODE,                     /* 72 */
    IPSEC_ERR_SAS_EXIST,                               /* 73 */
    IPSEC_ERR_SAS_NOT_EXIST,                           /* 74 */
    IPSEC_ERR_REAPPLY_POLICY,                          /* 75 */
    IPSEC_ERR_ATTEMPTCHANGE_TEMPLATETAG,               /* 76 */
    IPSEC_ERR_IKECOMP_UNAVAILABLE,                     /* 77 */
    IPSEC_ERR_INVALID_IP_ADDRESS,                      /* 78 */
    IPSEC_ERR_ADDR_CONFLICT,                           /* 79 */
    IPSEC_ERR_NO_SUCH_PROPOSAL_ON_POLICY,              /* 80 */
    IPSEC_ERR_PROPOSAL_IN_USE,                         /* 81 */
    IPSEC_ERR_DYNATEMP_TYPE,                           /* 82 */
    IPSEC_ERR_SEMAPHORE_BLOCK,                         /* 83 */
    IPSEC_ERR_NOT_SUPPORTED,                           /* 84 */
    IPSEC_PACKET_PROCESS_IN_HW,                        /* 85 */
    IPSEC_ERR_IKE_PEER_EXIST,                          /* 86 */
    IPSEC_ERR_IKE_PEER_DOES_NOT_EXIST,                 /* 87 */
    IPSEC_ERR_MODECFG_PEER_IN_USE,                     /* 88 */
    IPSEC_ERR_PEER_IN_USE,                             /* 89 */
    IPSEC_ERR_NOT_MODECFG_PEER,                        /* 90 */
    IPSEC_ERR_NOT_ISAKMPORCFG_MODE,                    /* 91 */
    IPSEC_ERR_NO_SPDS_ENTRIES,                         /* 92 */
    IPSEC_ERR_NO_SPDU_ENTRIES,                         /* 93 */
    IPSEC_ERR_CACHE_DISABLED,                          /* 94 */
    IPSEC_ERR_CACHE_ENTRIES_LEFT,                      /* 95 */
    IPSEC_ERR_CACHE_ENTRIES_NOT_LEFT,                  /* 96 */
    IPSEC_ERR_NOT_TUNNEL_MODE,                         /* 97 */
    IPSEC_ERR_PROPOSAL_CFGPOLICY,                      /* 98 */
    IPSEC_ERR_MODECFG_POLICY_MULTI_USE,                /* 99 */
    IPSEC_ERR_PEER_IS_VERSION1,                        /* 100 */
    IPSEC_ERR_TRAFFIC_SELECTOR_ENABLED,                /* 101 */
    IPSEC_ERR_TRAFFIC_SELECTOR_DISABLED,               /* 102 */
    IPSEC_HW_UPDATE_UNSECURE_CACHE,                    /* 103 */
    IPSEC_HW_UPDATE_SECURE_CACHE,                      /* 104 */

    /*B500 - SGSN-CMD Registration*/
    IPSEC_ERR_NOT_ISAKMPORDYNORCFG_MODE,               /* 105 */
    IPSEC_ERR_INVALID_PARA_PROPOSAL_NAME,              /* 106 */
    IPSEC_ERR_INVALID_PARA_ACL_NUMBER,                 /* 107 */
    IPSEC_ERR_INVALID_ACL,                             /* 108 */
    IPSEC_ERR_INVALID_PARA_VPN_NAME,                   /* 109 */
    IPSEC_ERR_INVALID_PARA_TUNNEL_LOCAL_ADDRESS,       /* 110 */
    IPSEC_ERR_INVALID_PARA_TUNNEL_REMOTE_ADDRESS,      /* 111 */
    IPSEC_ERR_INVALID_PARA_INBOUND_AH_SPI,             /* 112 */
    IPSEC_ERR_INVALID_PARA_INBOUND_ESP_SPI,            /* 113 */
    IPSEC_ERR_INVALID_PARA_OUTBOUND_AH_SPI,            /* 114 */
    IPSEC_ERR_INVALID_PARA_OUTBOUND_ESP_SPI,           /* 115 */
    IPSEC_ERR_INVALID_PARA_ESP_ENCR_HEXKEY,            /* 116 */
    IPSEC_ERR_INVALID_PARA_ESP_AUTH_HEXKEY,            /* 117 */
    IPSEC_ERR_INVALID_PARA_AH_HEXKEY,                  /* 118 */
    IPSEC_ERR_INVALID_PARA_AH_STRINGKEY,               /* 119 */
    IPSEC_ERR_INVALID_PARA_ESP_STRINGKEY,              /* 120 */
    IPSEC_ERR_INVALID_PARA_PEER_NAME,                  /* 121 */
    IPSEC_ERR_INVALID_PARA_PFS_TYPE,                   /* 122 */
    IPSEC_ERR_INVALID_PARA_SA_TRIGGER_MODE,            /* 123 */
    IPSEC_ERR_INVALID_PARA_TRAFFICSELECTOR,            /* 124 */
    IPSEC_ERR_INVALID_PARA_SA_LIFETIME,                /* 125 */
    IPSEC_ERR_MANUAL_POLICY_EXISTING_CONFIG,           /* 126 */
    IPSEC_ERR_ISAKMPDYNAMODECFG_POLICY_EXISTING_CONFIG,/* 127 */
    IPSEC_ERR_PROPOSAL_EXISITNG_CONFIG,                /* 128 */
    IPSEC_ERR_OPERATION_DONE,                          /* 129 */

    /*Iteration2-Story3-IpsecPeerHash*/
    IPSEC_ERR_IKE_DYNAPEER_DOES_NOT_EXIST,             /* 130 */

    /*SGSN License implementation - B511*/
    IPSEC_ERR_LICENSE_DISABLED,                        /* 131 */
    IPSEC_ERR_IKE_MAX_DYNAPEER_REACHED,                /* 132 */
    IPSEC_ERR_POLICY_ALREADY_ON_DIFFERENT_INTERFACE,   /* 133 */           /*Jira ID- RLMT61*/
    IPSEC_ERR_TDB_KEY_ALREADY_DELETED,                 /* 134 */           /*B057: key deletion from IKE/IPSEC after SA establishment*/
    IPSEC_ERR_IKE_DUPLICATE_FQDN_CONFLECT,             /* 135 */
    IPSEC_ERR_PROFILE_NOT_EXIST,                       /* 136 */
    IPSEC_ERR_PROFILE_EXIST,                           /* 137 */
    IPSEC_ERR_NO_SUCH_PROPOSAL_ON_PROFILE,             /* 138 */
    IPSEC_ERR_PROFILE_IN_USE,                          /* 139 */
    IPSEC_ERR_NOT_A_TUNNEL_INTERFACE,                  /* 140 */
    IPSEC_ERR_TUNNEL_MODE_NO_SUPPORT,                  /* 141 */
    IPSEC_ERR_TUNNEL_NO_SRC_ADDR,                      /* 142 */
    IPSEC_ERR_TUNNEL_NO_DST_ADDR,                      /* 143 */
    IPSEC_ERR_TUNNEL_MGRE_HAS_DST_ADDR,                /* 144 */
    IPSEC_ERR_MAX_PROFILE,                             /* 145 */
    IPSEC_ERR_NO_PEER_IN_PROFILE,                      /* 146 */
    IPSEC_ERR_IKE_PEER_ADDRESS_CONFIGURED,             /* 147 */
    IPSEC_ERR_TUNNEL_NOT_REGISTERED,                   /* 148 */

    /*Ipv6: Security Support*/
    IPSEC_ERR_POLICY_TYPE_MISMATCH,                    /* 149 */
    IPSEC_ERR_POLICY_EXIST_WITH_OTHER_ADDR_FAM,        /* 150 */

    /*Ipv6: Security Support*/
    IPSEC_ERR_IPV6_ADDRESS_IS_INVALID,                /* 151 */
    IPSEC_ERR_POLICY_EXIST_BYPRONAME,                 /* 152 */
    IPSEC_ERR_IKE_PEER_REMOTE_ADDRESS_CONFIGURED,     /* 153 */
    IPSEC_ERR_TRANSPORTMODE_NOTSUPPORTED,             /* 154 */
    IPSEC_ERR_INVALID_VRFINDEX,                       /* 155 */
    IPSEC_ERR_GET_TUNNEL_MODE,                        /* 156 */
    IPSEC_ERR_GET_TUNNEL_SRCDES,                      /* 157 */
    IPSEC_ERR_PROFILE_APPLIED_ONOTHERINTERFACE,       /* 158 */
    IPSEC_ERR_SPOKE_EXIST,                            /* 159 */
    IPSEC_ERR_NO_SPOKEBY_PROFILE,                     /* 160 */
    IPSEC_ERR_PROFILE_DELETE_IN_PROCESS,              /* 161 */
    IPSEC_ERR_PROFILE_IS_USING,                       /* 162 */
    IPSEC_ERR_CLEANUP_PROFILE_FIRST,                  /* 163 */  /* Delete dynamic policies and peers first */
    IPSEC_ERR_DOMAIN_ALREADY_EXISTS,                  /* 164 */
    IPSEC_ERR_IKE_PEER_REMOTE_FQDN_CONFIGURED,        /* 165 */
    IPSEC_ERR_ROUTE_CANNOT_ADD_DELETE_ACL_DENY,       /* 166 */
    IPSEC_ERR_RRI_SA_NOT_READY,                       /* 167 */
    IPSEC_ERR_RRI_TEMPLATE_RRI_MODE_NOT_DYNAMIC,      /* 168 */
    IPSEC_ERR_RRI_MODECFG_RRI_MODE_NOT_DYNAMIC,       /* 169 */
    IPSEC_ERR_POLICY_IN_USE,                          /* 170 */
    IPSEC_ERR_POL_PEER_VERSION_MISMATCH,              /* 171 */
    IPSEC_ERR_EASYVPN_PROF_NOT_FOUND,                 /* 172 */
    IPSEC_ERR_EASYVPN_ACL_CANNOT_CONFIG_BE_FOR_CLIENT,/* 173 */
    IPSEC_ERR_EASYVPN_ACL_NOT_PRESENT_FOR_CLIENT,     /* 174 */
    IPSEC_ERR_MAX_EASYVPN_PROFILE,                    /* 175 */
    IPSEC_ERR_CANNOT_CFG_ADDR_AND_FQDN,               /* 176 */
    IPSEC_ERR_INVALID_PEER_FQDN,                      /* 177 */
    IPSEC_ERR_EASYVPN_APPLIED_ON_INTERFACE,           /* 178 */
    IPSEC_EASYVPN_SET_PEER_FQDN_FAIL,                 /* 179 */
    IPSEC_EASYVPN_SET_PEER_ADDR_FAIL,                 /* 180 */
    IPSEC_EASYVPN_DEL_PEER_FQDN_FAIL,                 /* 181 */
    IPSEC_EASYVPN_DEL_PEER_ADDR_FAIL,                 /* 182 */
    IPSEC_EASYVPN_PEER_NOT_CONFIG,                    /* 183 */
    IPSEC_EASYVPN_PEER_IP_ALREADY_CONFIG,             /* 184 */
    IPSEC_EASYVPN_PEER_FQDN_ALREADY_CONFIG,           /* 185 */
    IPSEC_ERR_NO_PEER_IN_EASYVPN,                     /* 186 */
    IPSEC_ERR_EASYVPN_SA_EXIST,                       /* 187 */
    IPSEC_ERR_EASYVPN_DEFAULT_PEER_NOT_SET,           /* 188 */
    IPSEC_ERR_EASYVPN_UPDATE_FQDN_FAIL,               /* 189 */
    IPSEC_ERR_EASYVPN_UPDATE_AUTH_METHOD_FAIL,        /* 190 */
    IPSEC_ERR_EASYVPN_UPDATE_PKIOBJ_FAIL,             /* 191 */
    IPSEC_ERR_EASYVPN_UPDATE_PSK_FAIL,                /* 192 */
    IPSEC_ERR_EASYVPN_UPDATE_REMOTE_NAME_FAIL,        /* 193 */
    IPSEC_ERR_EASYVPN_UPDATE_LOCAL_ID_FAIL,           /* 194 */
    IPSEC_ERR_EASYVPN_UPDATE_LOCAL_ADDR_FAIL,         /* 195 */
    IPSEC_ERR_EASYVPN_PEER_ADDR_CONFLICT,             /* 196 */
    IPSEC_ERR_EASYVPN_FQDN_CONFLICT,                  /* 197 */
    IPSEC_ERR_INVALID_RULEID_CONFIGD,                 /* 198 */
    IPSEC_ERR_IKEPEER_ALREADY_EXIST,                  /* 199 */
    IPSEC_ERR_EASYVPN_UPDATE_OCSP_FAIL,               /* 200 */
    IPSEC_ERR_FEATURE_NOT_REGISTERED,                 /* 201 */
    IPSEC_ERR_EASYVPN_ACL_CONFIGURED,                 /* 202 */
    IPSEC_ERR_EASYVPN_UPDATE_LOCALID_FAIL,            /* 203 */
    IPSEC_ERR_WINDOW_SIZE_NOT_UPDATED,                /* 204 */ /*B058: Replay Window Size.*/
    IPSEC_ERR_IPSEC6_NO_LIB,                          /* 205 */
    /* Red Line Requirement: Port Disabling changes*/
    IPSEC_ERR_UDP_OPEN_CLOSE_SOCKET_FAIL,             /* 206 */
    IPSEC_ERR_PEER_ALREADY_BOUND_TO_ANOTHER_POLICY,   /* 207 */
    IPSEC_ERR_PEER_IN_AUTO_NEGOTIATION_BLOCKED_STATE, /* 208 */
    IPSEC_ERR_INVALID_INPUT,                          /* 209 */
    IPSEC_ERR_HW_ACL_MAP_WITH_IFNET_FAILURE,          /* 210 */
    IPSEC_ERR_MAX_DOMAIN_EXISTS,                      /* 211 */
    IPSEC_ERR_MAX = 0xFFFFFFFF
};

/* enum for debug level */
typedef enum tagIPSEC_DEBUG_LEVEL
{
    IPSEC_DEBUG_LEVEL_INFO,
    IPSEC_DEBUG_LEVEL_ERROR,
    IPSEC_DEBUG_LEVEL_WARN,
    IPSEC_DEBUG_LEVEL_MAX,
    IPSEC_MAX_DEBUG_LEV_ENUM_VALUE = 0x7FFFFFFF
}IPSEC_DEBUG_LEVEL_E;



typedef struct tagIPsecTunnelStatusInfo
{
    ULONG ulIfIndex;
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szPeerName[IPSEC_MAX_PEERNAME_LEN + 1]; /*IPSEC PeerName*/
    ULONG ulSequenceNum;
    ULONG ulSubSeqNum;
    ULONG ulModeCfgSourceAddr;
    ULONG  ulVrfIndex;          /*VRF Index*/
    ULONG ulNoOfSAs ;
    BOOL_T bAppModeCfgSA;     /*Application Triggered ModeCfg SA*/
    USHORT usResv;
    ULONG ulLocalAddr;
    ULONG ulPeerAddr;
    ULONG ulApplId;
    IPSEC_TdbIndex_S astTdbIndex[IPSEC_MAX_TDB_IN_TDBENTRY];
}IPSEC_TUNNEL_STATUS_INFO_S;

typedef struct tagIPSEC6_HW_PEER_INFO
{
    IN6ADDR_S stPeerIPAddr;
    ULONG ulVrfIndex;
    ULONG ulPeerID;
    USHORT usSourcePort;
    USHORT usDestPort;
}IPSEC6_HW_PEER_INFO_S;

typedef struct tagIpsec6_TdbIndex
{
    IN6ADDR_S   stIPv6Addr;
    ULONG       ulSpi;
    ULONG       ulIfIndex;
    USHORT      usAclNo;
    UCHAR       ucProto;
    UCHAR       ucDirection;        /* for TRAN */
    UCHAR       ucAddrType;     /* 4:IPv4, 6:IPv6 */
    UCHAR       ucResv[3];
}IPSEC6_TdbIndex_S;

typedef struct tagIPsec6TunnelStatusInfo
{
    ULONG ulIfIndex;
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulSequenceNum;
    ULONG ulSubSeqNum;
    IN6ADDR_S stModeCfgSourceAddr;
    ULONG  ulVrfIndex;          /*VRF Index*/
    ULONG ulNoOfSAs ;
    BOOL_T bAppModeCfgSA;     /*Application Triggered ModeCfg SA*/
    USHORT usResv;
    IN6ADDR_S stLocalAddr;
    IN6ADDR_S  stPeerAddr;
    ULONG ulApplId;
    IPSEC6_TdbIndex_S astTdbIndex[IPSEC_MAX_TDB_IN_TDBENTRY];
}IPSEC6_TUNNEL_STATUS_INFO_S;

/* The packet flow information is sent by Software to HW-FWD Module using
this */
typedef struct tagIPSEC6_PACKET_FLOW_INFO_S
{
    IN6ADDR_S stSourceIP;
    IN6ADDR_S stDestIP;
    USHORT usSourcePort;
    USHORT usDestPort;
    ULONG ulVrfIndex;
    UCHAR ucProtocol;
    UCHAR ucDSCP; /*support Qos extention*/
    UCHAR ucReserved[2];
}IPSEC6_PACKET_FLOW_INFO_S;


typedef struct tagIPSEC6_NP_DOWNLOADFAIL_INFO
{
    IPSEC6_TdbIndex_S stTdbIndex;
    IPSEC6_PACKET_FLOW_INFO_S stPacketFlow;
    ULONG ulCacheType;
}IPSEC6_NP_DOWNLOAD_FAIL_INFO;


typedef struct tagIPsec6_TdbEntry
{
    IN6ADDR_S stLocalAddr;   /* address for ipv6*/
    IN6ADDR_S stPeerAddr;    /* address for ipv6*/
    IPSEC6_TdbIndex_S stInTdbIndex;   /* ternary operator on inbound direction*/
    IPSEC6_TdbIndex_S stOutTdbIndex;  /* ternary operator on outbound direction*/
    IN6ADDR_S  stModeCfgSourceAddr; /* address for ModeCfg support in ipv6*/
    ACL6_Item  stFlow; /*Ipv6: Security Support*/
} IPSEC6_TDBENTRY_S;

typedef VOID (*IPSEC6_NOTIFY_TUNNEL_STATUS_CALLBACK_NEW)
                    (IPSEC6_TUNNEL_STATUS_INFO_S *pstTunnlInfo, ULONG ulState);


typedef VOID (*IPSEC_SemTest_Notify_CALLBACK)(ULONG ulSemID, ULONG ulFlag,
                                              CHAR *szFileName, ULONG ulLine);

/* AC4D07629: Updated for suggession address */
/*Updated for AP requirement of SA message*/
typedef VOID (*IPSEC_TUNNEL_STATUS_CALLBACK) (ULONG IfIndex, CHAR *szPolicyName,
                                            ULONG ulSequenceNum, ULONG ulState,
                                            ULONG ulModeCfgSourceAddr,
                                            TDB_S *apstTdb[],
                                            ULONG ulNoOfSAs,
                                            BOOL_T bIPSecModeCfgSA);

typedef VOID (*IPSEC_NOTIFY_TUNNEL_STATUS_CALLBACK_NEW)
                    (IPSEC_TUNNEL_STATUS_INFO_S *pstTunnlInfo, ULONG ulState);



#define IPSEC_SA_DOWN       0
#define IPSEC_SA_UP         1
#define IPSEC_SA_UPDATE     2 /*Sending notification at the time of rekey*/

/*Structure contains the default configuration paratmeters*/
typedef struct tagDefaultParameterValues
{
    ULONG ulProtocol_type;
    ULONG ulTransformAH;
    ULONG ulTransformESP;
    ULONG ulAH_Auth_Alg;
    ULONG ulESP_Auth_Alg;
    ULONG ulESP_Encr_Alg;
    USHORT usTransform;
    UCHAR ucEncapsulationMode;
    UCHAR ucSaTriggerMode;
}IPSEC_DEFAULT_PARAMETERS_S;


/*Following data structure contains TCP parameters
 of packet which are considerd for calculating hash
 for Ipsec Cache*/
typedef struct tagIPSEC_CACHE_TCPPARA_S
{
    USHORT usSrcPort;
    USHORT usDstPort;
}IPSEC_CACHE_TCPPARA_S;

/*Following data structure contains UDP parameters
 of packet which are considerd for calculating hash
 for Ipsec Cache*/
typedef struct tagIPSEC_CACHE_UDPPARA_S
{
    USHORT usSrcPort;
    USHORT usDstPort;
}IPSEC_CACHE_UDPPARA_S;

/*Following data structure contains ICMP parameters
 of packet which are considerd for calculating hash
 for Ipsec Cache*/
typedef struct tagIPSEC_CACHE_ICMPPARA_S
{
    USHORT   usIcmpType;    /* type of message */
    USHORT   usIcmpCode;    /* type sub code   */
}IPSEC_CACHE_ICMPPARA_S;

/*Following union provides protocol (TCP/UDP/ICMP)
  parameters of packet which are considerd for
  calculating hash for Ipsec Cache*/
typedef union tagIPSEC_PROTO_DATA_U
{
    IPSEC_CACHE_TCPPARA_S   stTcpPara;
    IPSEC_CACHE_UDPPARA_S   stUdpPara;
    IPSEC_CACHE_ICMPPARA_S  stIcmpPara;
}IPSEC_PROTO_DATA_U;

/*Following data structure keeps track of usage
sequence of SPDS entries, with most recently
used cache entry as first node and least recently
used entry as last node of list*/
struct tagIPSEC_SPD_TRACKER_S
{
    ULONG ulIndex;
    IPSEC_SPD_TRACKER_S *next;
    IPSEC_SPD_TRACKER_S *prev;
};


/*Following data structure contains hash
parameters and TdbEntry for SPDS */
struct tagIPSEC_SPDS_S
{
    IPSEC_SPDS_S  *pstNextHashParameter;
    ULONG ulSourceIP;
    ULONG ulDestinationIP;
    ULONG ulProto;          /* No of times this entry has been
                               accessed from the cache*/
    ULONG ulCount;
    ULONG ulVrfIndex; /* If VPN is enabled then VPN id will also be considered
                         for calculating the hash & matching in the cache*/

    UCHAR ucDscp;
    UCHAR ucReserved[3];
    IPSEC_PROTO_DATA_U stProto;
    IPSEC_TdbEntry_S *pstTdbEntry;
};

/*Following data structure contains display
parameters for SPDS */
typedef struct tagIPSEC_SPDS_DISPLAY_S
{
    ULONG ulSourceIP;
    ULONG ulDestinationIP;
    ULONG ulProto;
    ULONG ulCount;          /* No of times this entry has been
                               accessed from the cache*/
    IPSEC_PROTO_DATA_U stProto;
    UCHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulSequenceNumber;
    ULONG ulHashIndex;
    UCHAR ucDscp;
    UCHAR ucReserved[3];
}IPSEC_SPDS_DISPLAY_S;

/*Following data structure contains display
parameters for SPDU */
typedef struct tagIPSEC_SPDU_DISPLAY_S
{
    ULONG ulSourceIP;
    ULONG ulDestinationIP;
    ULONG ulProto;
    ULONG ulCount;          /* No of times this entry has been
                               accessed from the cache*/
    IPSEC_PROTO_DATA_U stProto;
    ULONG ulHashIndex;
    UCHAR ucDscp;
    UCHAR ucReserved[3];
}IPSEC_SPDU_DISPLAY_S;

/*Following data structure forms a node
of hash table of SPDS*/
typedef struct tagIPSEC_SPDS_TABLE_S
{
    ULONG ulIndex;
    IPSEC_SPDS_S *pstSpds;
    IPSEC_SPD_TRACKER_S *pstTracker;
}IPSEC_SPDS_TABLE_S;

/*Following data structure contains hash
parameters and TdbEntry for SPDU */
struct tagIPSEC_SPDU_S
{
    IPSEC_SPDU_S  *pstNextHashParameter;
    ULONG ulSourceIP;
    ULONG ulDestinationIP;
    ULONG ulProto;          /* No of times this entry has been
                               accessed from the cache*/
    ULONG ulCount;

    ULONG ulVrfIndex; /* If VPN is enabled then VPN id will also be considered
                         for calculating the hash & matching in the cache*/

    UCHAR ucDscp;     /* Added for Pico Wi max*/
    UCHAR ucReserved[3];
    IPSEC_PROTO_DATA_U stProto;
};

/*Following data structure forms a node
of hash table of SPDU*/
typedef struct tagIPSEC_SPDU_TABLE_S
{
    ULONG ulIndex;
    IPSEC_SPDU_S  *pstSpdu;
    IPSEC_SPD_TRACKER_S *pstTracker;
}IPSEC_SPDU_TABLE_S;

/*Following data structure contains IPsec
cache statistics*/
typedef struct tagIPSEC_CACHE_STAT_S
{
    ULONG ulSlot;
    ULONG ulNoOfEntries;    /* Current number of entries in cache*/
    ULONG ulCacheHit;       /* Number of times entry found in cache*/
    ULONG ulCacheMiss;      /* Number of times entry not found in cache*/
    ULONG ulSavedEntryCount;/* Number of entries saved in cache after expiry*/
    ULONG ulAgeingTime;     /* Time after which the entries in cache
                               will expire*/
    ULONG ulMaxCacheSize;
    ULONG ulCacheFull;      /* Number of times entry not found in cache
                               because cache was full*/
}IPSEC_CACHE_STAT_S;

typedef struct tagIPSEC_CACHE_GLOBAL_S
{
    ULONG ulCacheEnable;
    ULONG ulSecureCacheAgeTime;
    ULONG ulUnSecureCacheAgeTime;
}IPSEC_CACHE_GLOBAL_S;

/* Structure storing the parameters for getting a TDB entry on IO board*/
typedef struct tagIPSEC_TDB_ENTRY_PARAM_S
{
    UCHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulIfIndex;
}IPSEC_TDB_ENTRY_PARAM_S;

/*This strucutre is used to download SAs to hardware.
The structure contains SA parameters (SPI, Destination address, protocol) and
packet data*/
typedef struct tagSEC2_NOTIFY_CTX
{
    ULONG ulSPI;
    ULONG ulAddr;
    UCHAR ucProtcol;
    UCHAR ucpad[3];
    ULONG ulDirec; /*Inbound and out bound direction*/
    VOID  *pMbuf;
}SEC2_NOTIFY_CTX;

/*Authentication algorithm*/
#define IPSEC_AUTH_ALGORITHM_NULL               0
#define IPSEC_AUTH_ALGORITHM_MD5                1
#define IPSEC_AUTH_ALGORITHM_SHA1               2

/* SHA2 Support */
/*
   Extract - RFC 4868: Page 17.
   ---------------------------------------------------------------------
   For the use of HMAC-SHA-256+ algorithms for data origin
   authentication and integrity verification in IKEv2, ESP, or AH, IANA
   has assigned the following IKEv2 integrity (type 3) transform
   identifiers:

   AUTH_HMAC_SHA2_256_128  12

   AUTH_HMAC_SHA2_384_192  13

   AUTH_HMAC_SHA2_512_256  14
   ---------------------------------------------------------------------

   Maintaining the same values for configuration for IKEv2. For IKEv1 The
   values must be mapped to the RFC values as defined below and should be
   handled in the code.

    Extract - RFC 4868: Page 17.
   ---------------------------------------------------------------------
     For IKE Phase 2 negotiations, IANA has assigned the following
   authentication algorithm identifiers:

   HMAC-SHA2-256:  5

   HMAC-SHA2-384:  6

   HMAC-SHA2-512:  7
   ---------------------------------------------------------------------

 */
#define IPSEC_AUTH_ALGORITHM_SHA256             12
#define IPSEC_AUTH_ALGORITHM_SHA384             13
#define IPSEC_AUTH_ALGORITHM_SHA512             14
#define IPSEC_AUTH_ALGORITHM_AESXCBC            5

/*Encryption algorithm*/
#define IPSEC_ENCR_ALGORITHM_NULL               0
#define IPSEC_ENCR_ALGORITHM_DES                1
#define IPSEC_ENCR_ALGORITHM_3DES               2
#define IPSEC_ENCR_ALGORITHM_BLOWFISH           3
#define IPSEC_ENCR_ALGORITHM_SKIPJACK           4
#define IPSEC_ENCR_ALGORITHM_CAST               5

#define IPSEC_ENCR_ALGORITHM_AES128             6
#define IPSEC_ENCR_ALGORITHM_AES192             7
#define IPSEC_ENCR_ALGORITHM_AES256             8

/* Macros indicating tdb state */
#define IPSEC_TDB_CLOSED                     0x00
#define IPSEC_TDB_INITIALED                  0x01
#define IPSEC_TDB_READY                      0x02
#define IPSEC_TDB_UNSET                      0x04

/*Encapsulation mode command*/
#define IPSEC_TRANSFORM_MODE_TUNNEL             0
#define IPSEC_TRANSFORM_MODE_TRANSPORT          1

#define IPSEC_TRANSFORM_AH_NEW                  0
#define IPSEC_TRANSFORM_AH_ESP_NEW              1
#define IPSEC_TRANSFORM_AH_ESP_OLD              2
#define IPSEC_TRANSFORM_AH_OLD                  3
#define IPSEC_TRANSFORM_ESP_NEW                 4
#define IPSEC_TRANSFORM_ESP_AH_NEW              5
#define IPSEC_TRANSFORM_ESP_AH_OLD              6
#define IPSEC_TRANSFORM_ESP_OLD                 7
#define IPSEC_TRANSFORM_AH_IPCOMP               8
#define IPSEC_TRANSFORM_ESP_IPCOMP              9
#define IPSEC_TRANSFORM_AH_ESP_IPCOMP          10

#ifndef IKE_IPSEC_GLOBAL_IFIDX
#define IKE_IPSEC_GLOBAL_IFIDX	0xBABEFACE
#endif

/*GGSN:HA*/
/*IKEv2 Responder SPI Length*/
#define IPSEC_IKE_RCOOKIE_LENGTH              8

/* For RRI */
#define  IPSEC_RRI_STATIC               1
#define  IPSEC_RRI_DYNAMIC              2
#define  IPSEC_RRI_PREFERENCE_MAX       255
#define  IPSEC_RRI_PREFERENCE_MIN       1

/* For EasyVPN */
#define  IPSEC_EASYVPN_NORM_PROF        0
#define  IPSEC_EASYVPN_CLIENT           1
#define  IPSEC_EASYVPN_NETWORK          2

#define  IPSEC_EASYVPN_AUTH_PRE_SHARED  8


/* Used to get TdbEntry structure for display purpose */
typedef struct tagShowTdbEntry
{
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulMapSeq;
    ULONG ulACLNum; /*Added by Riyaz for Rule ID Display LTE: Multiple ACL-SA*/
    ULONG ulSubSeqNum; /*Added by Riyaz for Rule ID Display LTE: Multiple ACL-SA*/
    ULONG ulConnId;
    ULONG ulFlowSIPAddr;
    ULONG ulFlowSIPMask;
    ULONG ulFlowDIPAddr;
    ULONG ulFlowDIPMask;
    USHORT usFlowSP;    /*Flow source port*/
    USHORT usFlowDP;    /*Flow destination port*/
    UCHAR ucSaMode;
    UCHAR ucOutboundTdbFlags;
    UCHAR ucInboundTdbFlags;
    UCHAR ucFlowPID;        /*Flow Protocol ID*/

    /* Defect ID:AC4D05218 */
    ULONG ulModeCfgSrcAddress;
    ULONG ulDscp;

    /*Added for ipv6  support*/
    UCHAR ucAddrType;
    UCHAR ucReserved[3];
    IN6ADDR_S stFlowSIPAddr;
    IN6ADDR_S stFlowDIPAddr;
    ULONG ulIpv6FlowSIPMask;
    ULONG ulIpv6FlowDIPMask;
    ULONG ulIsTunnelActive; /*Added by Riyaz for Master/Slave Display*/
    USHORT usIPv6FlowSP;
    USHORT usIPv6FlowDP;
    UCHAR ucIPv6FlowPID;
    UCHAR ucACLVer;
    UCHAR ucResv[2];
}IPSEC_SHOW_TDBENTRY_S;

/* This structure contains the information required during displaying sa's in
   brief */
typedef struct tagIPsecIPSecSAContent
{
    ULONG ulSourceAddr;
    ULONG ulDestAddr;
    ULONG ulSPI;
    ULONG ulSubSeqNum;  /*Added by Riyaz for Rule ID Display LTE: Multiple ACL-SA*/
    ULONG ulACLGroupNum; /*Added by Riyaz for Rule ID Display LTE: Multiple ACL-SA*/
    ULONG ulTransformProtocol;
    ULONG ulAuthAlgorithm;
    ULONG ulEncrAlgorithm;
    ULONG ulVrfIndex;
    IN6ADDR_S stSourceAddr;
    IN6ADDR_S stDestAddr;
    ULONG ulIsTunnelActive; /*Added by Riyaz for Master/Slave Display*/

    UCHAR ucAddrType;
    UCHAR ucIsProfile;
    UCHAR ucEasyVpnMode;
    UCHAR ucReserved;
} IPSEC_SA_CONTENT_S;

/* Used to get Tdb Structure for display purpose */
typedef struct tagShowTdb
{
    ULONG ulFlags;
    ULONG ulsrcAddr;    /*pTdb->tdb_src.sin.sin_stAddr.s_ulAddr*/
    ULONG ulDstAddr;    /*pTdb->tdb_dst.sin.sin_stAddr.s_ulAddr*/
    ULONG ulSpi;
    ULONG ulexpbytes;       /*maximum number of kilobytes processed before expiration*/
    ULONG ulcurbytes;           /*current number of kilobytes processed*/
    ULONG ulexptimeout;         /*Time when SA life expires*/
    ULONG ulrpl;                /*Max sent packet sequence-number using this SA*/
    ULONG ulInext;
    ULONG ulOnext;
    ULONG ulVrfIndex;

    LONG lauthalgxformnType;    /*tdb_authalgxform->nType*/
    LONG lencalgxformnType;     /*tdb_encalgxform->nType*/
    USHORT usType;              /*tdb_xform->xf_type*/
    USHORT usEncKeyLen;

    /*Added for ipv6 support*/
    IN6ADDR_S stsrcAddr;
    IN6ADDR_S stDstAddr;

    UCHAR ucIsProfile;
    UCHAR ucEasyVpnMode;
    UCHAR ucSADownloadFail;     /* B204: Flag which is set when IPsec SA download to hardware has failed */
    UCHAR ucReserved;
}IPSEC_SHOW_TDB_S;

/* Tdb entry head structure*/
typedef struct tagTdbEntryHead
{
    IPSEC_TAILQ_ENTRY (tagTdbEntryHead) link;
    ULONG ulLocalAddress;
    ULONG ulLocalIfIndex;
    ULONG ulIfIndex; /* which interface that cryptomap to be used */
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1]; /* cryptomap's name */
    UCHAR ucAutoTriggerComplete;     /* Set when, all in the group
                                        with sa trigger mode auto has SAs */
    UCHAR ucProtectV4CtrlTraff;
    UCHAR ucReserved;
    UCHAR ucAddrType;                /*Added for ipv6 support*/
    VOID  *pvIPSecLocalAddr;
    IPSEC_TAILQ_HEAD (tagTdbEntrys, tagTdbEntry) stEntrys; /* point to tdb entry
                                                                     struct */
} IPSEC_TdbEntryHead_S;

/* xform IDs */
#define XF_IP4       1    /* IP inside IP */
#define XF_OLD_AH    2    /* RFC 1826, */
#define XF_OLD_ESP   3    /* RFC 1827, */
#define XF_NEW_AH    4    /* RFC 2402, AH HMAC 96bits */
#define XF_NEW_ESP   5    /* RFC 2406, ESP + auth 96bits + replay counter */
#define XF_IP6       6

/*Inbound or Outbound AH key sets*/
typedef struct tagIPsecAHSet
{
    ULONG ulSPI;
    CHAR szStringKey[IPSEC_MAX_KEY_STRING_LENGTH];
    CHAR szAuthHEXKey[IPSEC_MAX_KEY_STRING_LENGTH];
}IPSEC_AH_SET_S;

/*Inbound or Outbound ESP key sets*/
typedef struct tagIPsecESPSet
{
    ULONG ulSPI;
    CHAR szStringKey[IPSEC_MAX_KEY_STRING_LENGTH];
    CHAR szEncrHEXKey[IPSEC_MAX_KEY_STRING_LENGTH];
    CHAR szAuthHEXKey[IPSEC_MAX_KEY_STRING_LENGTH];
}IPSEC_ESP_SET_S;

/*Manual policy content*/
typedef struct tagIPsecPolicyContentManual
{
    CHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szProposalName[IPSEC_MAX_TRANSFORM_NAME + 1];
    ULONG ulPolicySeq;
    ULONG ulACLNumber;
    ULONG ulTunnelLocalIPAddr;
    ULONG ulPeerAddrManual;

    /*Manual policy Key sets*/
    IPSEC_AH_SET_S stInboundAHSet;
    IPSEC_AH_SET_S stOutboundAHSet;
    IPSEC_ESP_SET_S stInboundESPSet;
    IPSEC_ESP_SET_S stOutboundESPSet;
}IPSEC_POLICY_CONTENT_MANUAL_S;

/*ISAKMP policy content*/
typedef struct tagIPsecPolicyContentIsakmp
{
    CHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szProposalName[IPSEC_CRYPTOMAP_MAX_TRANSFORM_NUM]\
                       [IPSEC_MAX_TRANSFORM_NAME + 1];
    CHAR szIKEPeerName[IPSEC_PEER_NAME_MAX_LEN];
    ULONG ulPolicySeq;
    ULONG ulACLNumber;
    ULONG ulPFSType; /*Type of Perfect forward secrecy .*/
    ULONG ulSALifetimeSeconds;
    ULONG ulSALifetimeKilobytes;
} IPSEC_POLICY_CONTENT_ISAKMP_S;

/* DYNAMIC policy */
typedef struct tagIPsecPolicyContentTemplate
{
    CHAR  szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    CHAR  szTemplateName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulPolicySeq;
}IPSEC_POLICY_CONTENT_TEMPLATE_S;

/* This structure is used to form a message containg either manual isakmp or
   policy template data, to send to the hardware */
typedef struct tagIPsecPolicyContent
{
    ULONG ulPolicyMode;                        /*0:ISAKMP,1:MANUAL,2:TEMPLATE*/
    ULONG ulOpMode;
    union
    {
        IPSEC_POLICY_CONTENT_MANUAL_S   stPolicyContentManual;   /*MANUAL*/
        IPSEC_POLICY_CONTENT_ISAKMP_S   stPolicyContentIsakmp;   /*ISAKMP*/
        IPSEC_POLICY_CONTENT_TEMPLATE_S stPolicyContentTemplate; /*TEMPLATE*/
    }unPolicyContent;
#define   stManualPolicy    unPolicyContent.stPolicyContentManual
#define   stIskampPolicy    unPolicyContent.stPolicyContentIsakmp
#define   stTemplatePolicy  unPolicyContent.stPolicyContentTemplate
} IPSEC_POLICY_CONTENT_S;

#define M_IPSEC_TDBKEY_LEN_MAX          484
#define M_IPSEC_TDBAUTHCTX_LEN_MAX      92

/* IV lengths */
#define ESP_NULL_IVS        0
#define ESP_DES_IVS         8
#define ESP_3DES_IVS        8
#define ESP_BLF_IVS         8
#define ESP_CAST_IVS        8
#define ESP_SKIPJACK_IVS    8

#define ESP_AES_IVS         16
#define ESP_MAX_IVS         16   /* Keep updated */

/* BEGIN : R3-C03 */
#define IPSEC_MAX_IVS       ESP_MAX_IVS

/* END : R3-C03 */

/* Tdb Structure used during HA backup */
typedef struct tagIPSecTdbBackup
{
    CHAR szPeerName[IPSEC_MAX_PEERNAME_LEN + 1];
    ULONG  tdb_link_spi;
    LONG   tdb_xform_xf_type;       /* TDB_S.tdb_xform->xf_type */
    LONG   tdb_encalgxform_nType;   /* TDB_S.tdb_encalgxform->nType */
    LONG   tdb_authalgxform_nType;  /* TDB_S.tdb_authalgxform->nType */
    ULONG  tdb_flags;              /* TDB_S.tdb_flags */
    ULONG  tdb_exp_bytes;          /* TDB_S.tdb_exp_bytes */
    ULONG  tdb_soft_bytes;         /* TDB_S.tdb_soft_bytes */
    ULONG  tdb_cur_bytes;          /* TDB_S.tdb_cur_bytes */
    ULONG  tdb_cur_kilobytes;          /* TDB_S.tdb_cur_kilobytes */
    ULONG  tdb_exp_timeout_len;    /* TDB_S.tdb_exp_timeout - current time */
    ULONG  tdb_soft_timeout_len;   /* TDB_S.tdb_soft_timeout - current time */
    ULONG  tdb_exp_firstuse_timeout_len; /* TDB_S.tdb_exp_first_use
                                                            - current time */
    ULONG  tdb_soft_exp_firstuse_timeout_len; /* TDB_S.tdb_soft_first_use
                                                             - current time */
    ULONG  tdb_first_use_len;     /* This TDB was first used 'tdb_first_use_len'
                                     seconds back, current time-tdb_first_use*/
    ULONG  tdb_spi;                /* TDB_S.tdb_spi */
    ULONG  tdb_ulVrfIndex;          /* VRF Index */

    USHORT tdb_ivlen;              /* TDB_S.tdb_ivlen */

    UCHAR  tdb_sproto;             /* TDB_S.tdb_sproto */
    UCHAR  tdb_wnd;                /* TDB_S.tdb_wnd */

    USHORT usTdbHasLink;           /* TDB_LINK_INBOUND, TDB_LINK_OUTBOUND,
                                        TDB_HAS_NO_LINK */
    UCHAR  tdb_link_sproto;
    UCHAR  ucNegotiateSaMode;        /* TDB_S.ucNegotiateSaMode */

    ULONG  tdb_ifaddr;               /* TDB_S.tdb_ifaddr */
    ULONG  tdb_key_len;                          /* DES:128, 3DES:384 */
    UCHAR  tdb_key[M_IPSEC_TDBKEY_LEN_MAX];      /* TDB_S.tdb_xform */
    ULONG  tdb_ictx_len;                         /* MD5:92, SHA1:92 */
    UCHAR  tdb_ictx[M_IPSEC_TDBAUTHCTX_LEN_MAX]; /* TDB_S.tdb_xform */
    ULONG  tdb_octx_len;                         /* MD5:92, SHA1:92 */
    UCHAR  tdb_octx[M_IPSEC_TDBAUTHCTX_LEN_MAX];

    USHORT tdb_src_port;
    USHORT tdb_dst_port;

    ULONG  tdb_rpl;          /* TDB_S.tdb_rpl */
    ULONG  tdb_bitmap;       /* TDB_S.tdb_bitmap */
    ULONG  tdb_initial;      /* TDB_S.tdb_initial */
    ULONG  ulTdbEntryNum;            /* TDB_S.ulTdbEntryNum */

    union
    {
        UCHAR Iv[ESP_MAX_IVS];     /* TDB_S.IV.Iv */
        ULONG Ivl;                  /* TDB_S.IV.Ivl */
        UCHAR Ivq[ESP_DES_IVS];     /* TDB_S.IV.Ivq */
    }IV;

    USHORT tdb_usKeyID;            /* TDB_S.tdb_usKeyID */
    USHORT usOpMode;

    USHORT  tdb_encry_keylen;       /* Keylength of the encryption algorithm */

    UCHAR ucReserved[2];

    union sockaddr_union tdb_link_dst;
    union sockaddr_union tdb_dst;   /* TDB_S.tdb_dst */
    union sockaddr_union tdb_src;   /* TDB_S.tdb_src */
}IPSEC_BACKUP_TDB_S;

typedef struct tagIPSEC_PEER_S IPSEC_PEER_S;

/* DPD Expiration list */
typedef struct tagIPSEC_DPD_EXPIRATION_S
{
    IPSEC_TAILQ_ENTRY (tagIPSEC_DPD_EXPIRATION_S) link;
    ULONG ulMemHead;
    ULONG ulExpTimeout;     /* Expiry time in seconds that is configured in
                               the peer */
    IPSEC_PEER_S *pstIPsecPeer; /* Pointer to peer structure */
}IPSEC_DPD_EXPIRATION_S;

/* DPD related info */
typedef struct tagIPSEC_DPD_INFO_S
{
    ULONG ulNoOfSas;        /* SA Count indicates when the expiration node
                             should be removed */
    ULONG ulIdleTime;       /* Idle time configured for the DPD */
    ULONG ulIdleTimeSlot;   /* Counts the number of slots in which inbound
                              traffic has not arrived */
    ULONG ulDpdTrigger_VT;  /* keeps track of how many io board have triggered
                              dpd */
    UCHAR ucDpdType;        /* Periodic or on demand */
    UCHAR ucVendorIDResult; /* Stores the vendor id success or failure */
    UCHAR ucInboundTraffic; /* Stores whether inbound traffic has arrived
                               within configured idle timer */
    UCHAR ucDpdPending;     /* Used for on demand DPD only.  Set when timer
                               expires and dpd should be triggered for next
                               outbound traffic */
    UCHAR ucDpdInProgress;  /* Set once dpd is triggered */
    UCHAR ucVT_Interface;   /* Indicates whether the policy using the peer is
                               applied on VT interface */
    UCHAR ucDpdEnable;      /* Indicates whether DPD is enabled or not */
    /*IKEV2*/
    UCHAR ucIKEVersion;
    ULONG ulDpdTimerId;

    /*GGSN:DPD-DEFECTFIXES*/
    ULONG ulUpdateTimer;
}IPSEC_DPD_INFO_S;

/* Peer Structure maintained by IPsec */
struct tagIPSEC_PEER_S
{

    /*Iteration2-Story3-IpsecPeerHash*/
    IPSEC_TAILQ_ENTRY (tagIPSEC_PEER_S) link;
    IPSEC_TAILQ_ENTRY (tagIPSEC_PEER_S) Idlink;

    IPSEC_TAILQ_HEAD (tagDynaIPSEC_PEER_S, tagIPSEC_PEER_S) stDynaPeers;

    ULONG ulMemHead;
    CHAR szPeerName[IPSEC_MAX_PEERNAME_LEN + 1];

    /* R3-C03 */
    ULONG ulPeerIndex;       /* This along with peer address can be used to
                                uniquely identify a peer */
    ULONG ulPeerId;
    ULONG ulAddress;
    ULONG ulEndAddress;
    ULONG ulExchangeMode;
#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    USHORT usSrcSubNetType;
    USHORT usDstSubNetType;
#endif
    UCHAR ucModeCfgType;     /* whether mode-cfg is enabled for the peer */
    UCHAR ucPeerUsed;        /* Set when the peer is being used by mode-cfg
                                policy */
    UCHAR ucDpdFlag;         /* Indicates the status of inbound traffic, dpd
                                pending, dpd in progress, periodic or ondemand,
                                dpd enabled or not flags.*/


    /*IKEV2*/
    UCHAR ucIKEVersion;
    ULONG ulVrfIndex;

    /*Pfkey-Optimization:STORY-1,2,3 - Acquire Optimization*/
    ULONG ulFlags;

    /*Iteration2-Story3-IpsecPeerHash*/
    USHORT usSourcePort;
    USHORT usDestPort;
    ULONG ulDynaPeerCount;

    IPSEC_DPD_INFO_S stIPsecDpdInfo;

    /*S9300.ITR2.STORY.2*/
    /*In case of template policy, Peer maintains a linked list of dynamic peers.
      And every dynamic peer has a pointer to the parent Peer.*/
    IPSEC_PEER_S *pstParentPeer;
    USHORT usIsDynaPeer;

    /*Ipv6: Security Support*/
    UCHAR ucAddrType;           /* Kranthi : Added for ipv6 support*/
    UCHAR ucUseAllSupportedAlg; /* Auto VPN support */
    VOID *pvIPsec6Peer ;        /* IPv6 Peer  information - IPSEC6_PEER_S */
    ULONG ulPh1SaConnID;        /* GGSN-SUPPORT: DPD*/
    VOID *pvData;               /* Pointer to data for DPD timer processing.*/
    ULONG ulLocalAddr;          /*NAG:IPSEC_PROF_GetTunnelStatus*/

    /*GGSN*/
    UCHAR ucFQDNState;
    UCHAR ucRemoteIPType;       /* To check if user configured IP directly or FQDN */

    UCHAR ucIsAutoTriggerEnabled; /* This field is used to control the auto trigger for master and backup peers */
    UCHAR ucPeerType;             /* This field is used to identify the peer type(master/backup/normal) */
    UCHAR ucPeerBoundWithPolicy;  /* Set when the peer is being bind to policy.
                                     This flag is applicable only for master or back-up peers */
    UCHAR ucPad[3];
};

/*TDBPROBLEM-IkeV2*/
struct tdb;

typedef struct tagIPSEC_TRAFFIC_SELECTOR_S
{
    IPSEC_TAILQ_ENTRY (tagIPSEC_TRAFFIC_SELECTOR_S) link;
    USHORT usIPProtocolID;
    USHORT usReserve;
    USHORT usSrcStartPort;
    USHORT usSrcEndPort;
    USHORT usDstStartPort;
    USHORT usDstEndPort;
    ULONG  ulSrcStartAddr;
    ULONG  ulSrcEndAddr;
    ULONG  ulDstStartAddr;
    ULONG  ulDstEndAddr;

    /*TDBPROBLEM-IkeV2*/
    /*When the traffic selector created for a tdb entry, traffic selector is
      added for each TDB. When the multiple child SAs present for the TDB entry,
      this pointer is useful for deleting/adding the traffic selector from
      the list*/
    struct tdb *pstTdb;

} IPSEC_TRAFFIC_SELECTOR_S;

/*TdbEntry is the intermediate data structure between Cryptomap and TDB. It
    maps crypto map to TDB and vice-versa*/
struct tagTdbEntry
{
    IPSEC_TAILQ_ENTRY (tagTdbEntry) link;
    ULONG ulMemHead;
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1];
#if (TCPIP_IN_VRP == VRP_NO)
    ACL_Item stFlow;
#else
    IPOS_ACL_Item stFlow;
#endif
    ULONG ulSequenceNumber;
    ULONG ulSubSeqNum;     /* To Store ACL Rule ID, to Create Multiple SA for Each Rule*/
    ULONG ulConnId;
    ULONG ulLocalAddr;  /*For Manual policy, user configures local address. Incase of Profile, source address
                            of Tunnel interface is considered as local address*/
    ULONG ulPeerAddr;
    USHORT usListNumber;
    UCHAR ucOutboundTdbFlags; /* tdb flags: closed, initiating, ready */
    UCHAR ucInboundTdbFlags;
    IPSEC_TdbIndex_S stInTdbIndex;
    IPSEC_TdbIndex_S stOutTdbIndex;

    /* Pointer to the peer structure, maintained in IPsec */
    IPSEC_PEER_S *pstIPsecPeer;
    UCHAR ucSaMode; /* manual, isakmp, dynamic */
    /* Tunnel debugging switch. */
    UCHAR ucPacketDebug;
    UCHAR ucSaTriggerMode;
    UCHAR ucModeCfgSeqFlag;

    /*GGSN-SUPPORT*/
    IPSEC_TAILQ_HEAD (tagDyTdbEntrys, tagIPSEC_MaskEntry_S) stDyMaskEntry;

    ULONG ulModeCfgSourceAddr;

    /* This uniquely identifies a modecfg tdb entry within a tdb entry list */
    USHORT usModeCfgSequenceNumber;

    /* This flag when set indicates, that modecfg address is received as part
    of IPsec modecfg trigger in the main tdb entry.  Within the modecfg
    tdb entry the application id pertaining to this address is stored */
    USHORT usModecfgAddressApplId;
    IPSEC_TAILQ_HEAD (tagModeCfgTdbEntrys, tagTdbEntry) stModeCfgEntrys;

    /* IKEv2: @Jayesh
    Indicates Whether traffis selector is enabled or not.*/
    ULONG ulTsEnable;

    /*IKEv2: @Jayesh
    TS downloaded from IKE. Used for matching the traffic first to ACL
    and then to this Traffic selctors for which the SA is created */
    /* If the traffic selector pointer are not NULL, then it indicates that
    the Traffic has been narrowed down and must be downloaded to ASIC */
    IPSEC_TAILQ_HEAD(tagTrafficSelectors, tagIPSEC_TRAFFIC_SELECTOR_S)
                                                        stTrafficSelector;

    /*TDBPROBLEM-IkeV2*/
    /*The time indicating when the SA is downloaded from IKE,
        used in packet processing*/
    ULONG ulNewOutTdbDownloadTime;

    /* Added by sumangala for HW Encryption Suport */
    ULONG ulPacketType;                 /* Given by enum IPSEC_PACKET_TYPE_E*/
    VOID *pstPacket;                /* Pointer to MBUF or to flow */

    /*PICO Wi-Max DSCP changes*/
    ULONG ulSelectCryptoTime;

    /* AC4D07629: Mode CFG Address to be send as sugg at the time of Request */
    ULONG ulModeCfgSugAddr;
    ULONG ulModeCfgSugMask;

    /*[Defect :AC4D07824] B115 DSCP solution. Dscp value while sa negotiation*/
    UCHAR  ucDSCP;

    /*AP requiremnet Tunnel State down should be sent only once.*/
    UCHAR ucTunnelDownSent;
    UCHAR ucAddrType;       /*Added for ipv6 */

    /* This flag is used when spoke is deleted in profile, when spoke is under
       deletion then auto acquire should not be sent */
    UCHAR ucToBeDeleted;
    IPSEC_CryptoMap_S *pstCryptoMap;

    /*End Of PICO Wi-Max DSCP changes*/

    IPSEC_PFKEYV2_MAP_STATS_S stMapStats;

    /*Defect:A75D05537*/
    ULONG ulAcquireTimerID;

    /*LTE multiple ACL-SA: Action defines whether the flow is deny/allow
    this is used to by pass the deny packet*/
    ULONG ulAction;

    VOID *pvIPSEC6_Tdb_Entry;      /*  Points to structure IPSEC6_TDBENTRY_S */

    /*GGSN-SUPPORT : Link to DynaTdbEntry HashTable.*/
    VOID *pvHashTable;

    /*B050: Peer Reliability*/
    ULONG ulIsTunnelActive;

    /*  RRI*/
    UCHAR ucRRIMode;
    UCHAR ucRRIIsRouteAdded;
    UCHAR ucACLVer;
    UCHAR aucRev[1];
    ULONG ulRRIPreference;

    /*B058: Replay Window Size*/
    ULONG ulReplayWindowSize;
};

typedef union tagIPSEC_ACL_ITEM
{
#if (TCPIP_IN_VRP == VRP_NO)
    ACL6_Item stFlow6;
    ACL_Item stFlow4;
#else
    IPOS_ACL6_Item stFlow6;
    IPOS_ACL_Item stFlow4;
#endif
}IPSEC_ACL_ITEM_U;

typedef struct tagIPSEC_COMM_ACL_ITEM
{
    IPSEC_ACL_ITEM_U stFlow;
    UCHAR ucFlowType;      /* 4:ACL4, 6:ACL6 */
    UCHAR aucRes[3];
}IPSEC_COMM_ACL_ITEM_S;

/* tunnel descriptor block (SA) */
struct tdb
{
    ULONG ulMemHead;
    struct tdb      *tdb_hnext;      /* Next in hash chain */
    struct tdb      *tdb_onext;      /* Next in output(outbound tdb link) */
    struct tdb      *tdb_inext;      /* Previous in output(outbound tdb link) */
    IPSEC_TdbEntry_S *pstTdbEntry;
    struct tagXFORMSW   *tdb_xform;     /* Transformation to use */
    struct tagENC_XFORM *tdb_encalgxform;  /* Encryption algorithm xform */
    struct tagAUTH_HASH *tdb_authalgxform; /* Authentication algorithm xform */

    ULONG         tdb_flags;             /* Flags related to this TDB */
    ULONG         tdb_exp_kilobytes;    /* Expire after so many bytes passed */
    ULONG         tdb_soft_kilobytes;   /* Expiration warning */
    ULONG         tdb_cur_kilobytes;          /* TDB_S.tdb_cur_kilobytes */
    ULONG         tdb_cur_bytes;    /* Current count of bytes */
    ULONG         tdb_cur_bytes_synced; /* for HA:Current bytes value sent to
                                                                slave board */

    ULONG         tdb_exp_timeout;  /* When does the SPI expire */
    ULONG         tdb_soft_timeout; /* Send a soft-expire warning */
    ULONG         tdb_established;  /* When was the SPI established */

    ULONG         tdb_first_use;     /* When was it first used */
    ULONG         tdb_soft_first_use; /* Soft warning */
    ULONG         tdb_exp_first_use;  /* Expire if tdb_first_use
                                       * + tdb_exp_first_use <= curtime */
    ULONG         tdb_spi;           /* SPI */
    USHORT        tdb_ivlen;          /* IV length */
    UCHAR         tdb_sproto;        /* IPsec protocol */
    UCHAR         tdb_wnd;            /* Replay window */

    union sockaddr_union tdb_dst;    /* Destination address for this SA */
    union sockaddr_union tdb_src;    /* Source address for this SA */
    ULONG         tdb_ifaddr;        /* The local address of Interface */

    ULONG         tdb_ulVrfIndex;    /* peer vpn */

    /* added for aggressive */
    USHORT        tdb_src_port;
    USHORT        tdb_dst_port;

    UCHAR         *tdb_key;          /* Key material(schedules) */

    UCHAR         *tdb_authKey;      /* These are used for HW encryption */
    ULONG         tdb_authkey_len;   /* support */

    UCHAR         *tdb_ictx;         /* Authentication contexts */
    UCHAR         *tdb_octx;
    UCHAR         *tdb_amxkey;       /* AH-old only */

    union
    {
        UCHAR Iv[ESP_MAX_IVS];        /* That's enough space */
        ULONG Ivl;                    /* Make sure this is 4 bytes */
        UCHAR Ivq[ESP_DES_IVS];       /* Make sure this is 8 bytes! */
    }IV;
#define tdb_iv  IV.Iv
#define tdb_ivl IV.Ivl
#define tdb_ivq IV.Ivq

    ULONG  tdb_rpl;                 /* Replay counter */
    ULONG  tdb_bitmap;              /* Used for replay sliding window */
    ULONG  tdb_initial;             /* Initial replay value */

    ULONG  ulTdbEntryNum;           /* the number of tdb entry which use this
                                                                         tdb */

    USHORT tdb_usKeyID;             /* Hardware only */

    USHORT us_wnd;                  /* B058: New var for Replay window */

    UCHAR  ucNegotiateSaMode;       /* crypto map negotiate mode */
    UCHAR  ucAddrType;
    UCHAR  ucIPsecSADownloadFail;   /* B204: Flag which is set when IPsec SA download to hardware has failed */
    UCHAR  ucReserved;

    UCHAR  *tdb_hw_key;             /* These are used for HW encryption */
    ULONG  tdb_hw_keylen;
    USHORT tdb_encry_keylen;       /* Keylength of the encryption algorithm */
                                   /* support */

    /* Added for TRAN */
    USHORT usAclNum;
    ULONG ulIntfIndex;

    IPSEC_PEER_S *pstIPsecPeer;

    /*TDBPROBLEM-IkeV2*/
    /*For some scenarios in IKE, IKE may download multiple TDBs for the same
      Tdb Entry. Following pointers links to the new set of TDBS.*/
    struct tdb *pstChildNextTdb;
    struct tdb *pstChildPrevTdb;

    /* Added for AH raw key */
    ULONG ulAH_KeyLen;
    UCHAR *pucAH_Key;


    /*RM Timer*/
    ULONG ulTimerId;
    ULONG ulFirstUseTimerId;

    /*Ipv6: Security Support*/
    IN6ADDR_S tdb_Ipv6_ifaddr;

    /* LOOP_OPT */
    ULONG ulConId;
    /*B057: key deletion from IKE/IPSEC after SA establishment*/
    ULONG ulKeyDeletedFlag;

    /*GGSN-SUPPORT: Flag to indicate whether to release product's SPI.*/
    ULONG ulReleaseProductSPI;

    /*GGSN:HA*/
    /* IKE Ph1 SA Responder Cookie is used to associate Ipsec SA
        and IKE Ph1 SA in the GGSN product. This is used only for Inbound Tdb*/
    UCHAR szIkePh1RespSpi[IPSEC_IKE_RCOOKIE_LENGTH];

    IPSEC_COMM_ACL_ITEM_S *psTS;

    /*HS:Added as Now Packet Handling is done in IPSEC sw \
    this flag is used for only Outbound Tdb,\
    ulTdbusage = 1 (can use this tdb to send traffic)*/
    ULONG ulTdbusage;
};

/* The packet flow information is sent by Software to HW-FWD Module using
this */
typedef struct tagIPSEC_PACKET_FLOW_INFO_S
{
    ULONG ulSourceIP;
    ULONG ulDestIP;
    ULONG ulSourcePort;
    ULONG ulDestPort;
    ULONG ulProtocol;
    ULONG ulDSCP;           /* support Qos extention */
    ULONG ulVrfIndex;
}IPSEC_PACKET_FLOW_INFO_S;

typedef struct tagIPSEC6_TRAFFIC_SELECTOR_S
{
    IPSEC_TAILQ_ENTRY (tagIPSEC6_TRAFFIC_SELECTOR_S) link;
    USHORT usIPProtocolID;
    USHORT usReserve;
    USHORT usSrcStartPort;
    USHORT usSrcEndPort;
    USHORT usDstStartPort;
    USHORT usDstEndPort;
    IN6ADDR_S  stSrcStartAddr;
    IN6ADDR_S  stSrcEndAddr;
    IN6ADDR_S  stDstStartAddr;
    IN6ADDR_S  stDstEndAddr;

    /*TDBPROBLEM-IkeV2*/
    /*When the traffic selector created for a tdb entry, traffic selector is
      added for each TDB. When the multiple child SAs present for the TDB entry,
      this pointer is useful for deleting/adding the traffic selector from
      the list*/
    struct tdb *pstTdb;

} IPSEC6_TRAFFIC_SELECTOR_S;

/* Hardware Callback functions */
typedef struct tagIPSECHardCallback
{
    ULONG (*pfIPSEC_SendProposal_To_Hardware)(
                                IPSEC_PROPOSAL_CONTENT_S *pstProposalData);

    ULONG (*pfIPSEC_SendPolicy_To_Hardware)(
                                IPSEC_POLICY_CONTENT_S *pstPolicyData);

    ULONG (*pfIPSEC_SendSAEntry_To_Hardware)(
                                IPSEC_SA_ENTRY_CONTENT_S *pstSAEntryData);

    ULONG (*pfIPSEC_SendSA_To_Hardware)(IPSEC_BACKUP_TDB_S *pstSAData);

    ULONG (*pfIPSEC_ProcessOutpacket_In_Hardware)(VOID *pMBUF,
                                     IPSEC_BACKUP_TDB_S *pTbdInfo,
                                     IPSEC_BACKUP_TDB_S *pTdbOnNextInfo);

    ULONG (*pfIPSEC_ProcessInpacket_In_Hardware)(VOID *pMBUF,
                                     IPSEC_BACKUP_TDB_S *pTbdInfo,
                                     IPSEC_BACKUP_TDB_S *pTdbOnNextInfo);

    VOID  (*pfIPSec_InputIntoHardwareQueue)(TDB_S *pTDB, VOID *pMBUF);

    /* These two callback function is required for 8070_SECP like product ,
      Where SA is maintain in Hardware. */
    ULONG (*pfIPSEC_ProcessSecp_Outpacket_In_Hardware)(VOID *pstMBuf,
                                        IPSEC_TdbEntryHead_S *pTdbEntryHead,
                                        IPSEC_TdbEntry_S *pTdbEntry);

    ULONG (*pfIPSEC_ProcessSecp_Inpacket_In_Hardware) (VOID *pMBUF);

    /* This is for R8070_SECP product , to send message to IPSec queue */
    VOID (*pfIPSEC_SendMsg2CfgQueue)(UCHAR *pMsg, ULONG ulLength, ULONG ulFlag);

    VOID (*pfIPSEC_MapInterface2Secp)(IPSEC_MapGroupHead_S *pstMapGoupHead,
                                       ULONG ulNoFlag, ULONG ulIfIndex);

    ULONG (*pfIPSEC_SendMapUpdate2Secp)(CHAR *szMapName, ULONG ulMapSeq,
                           USHORT usTBL, ULONG ulNoFlag, ULONG ulExecID);

    ULONG (*pfIPSEC_SendLifeTime_To_Hardware)(ULONG ulLifeTimeSeconds,
                                              ULONG ulLifeTimeBytes);

    /* If product can only do Encryption decryption in Hardware, Packet
       encapsulation  Software IPSEC Will  do */
    ULONG (*pfIPSEC_Send_HW_Encryp_Decrypt)(MBUF_S *pMbuf, TDB_S *pTdb);

    /* To check Hardware Encryption/Decryption engine is enabled or  not */
    BOOL_T (*pfIPSEC_HW_Encryp_Decrypt_Enabled)(VOID);
}IPSEC_HARD_CALLBACK_S;

/* authentication algorithms switch table item structure */
typedef struct tagAUTH_HASH
{
    LONG nType;                             /* Algorithm type*/
    CHAR acName[IPSEC_MAX_ALG_NAME_LENGTH]; /* Algorithm name */
    USHORT usKeySize;                       /* Algorithm key size */
    USHORT usHashSize;                      /* Authenticator lengths */
    USHORT usCtxSize;                       /* Context size */
    USHORT usReserved;          /* To Support MIPS : Vivek K Sriwastava */
    VOID(*Init)(VOID *);                    /* Algorithm  initial function */
    VOID(*Update)(VOID *, UCHAR *, ULONG);  /* Algorithm  middle computing
                                                                    function */
    VOID(*Final)(UCHAR *, VOID *);          /* Algorithm  final result
                                                        computing function */
    VOID(*CmacInit)(VOID *, UCHAR *, ULONG);/* Initialization of CMAC Algorithms */
}IPSEC_AUTH_HASH_S;

/*Data structure contains the key authentication and encryption key
information on the basis of
transform used. This structure is used to initialize SA with the key
information.*/
typedef struct tagIPSECINIT
{
    UCHAR  *ii_pEncKey;
    UCHAR  *ii_pAuthKey;
    USHORT ii_usEncKeyLen;
    USHORT ii_usAuthKeyLen;
    UCHAR  ii_ucEncAlg;
    UCHAR  ii_ucAuthAlg;
    UCHAR  ucPad[2];
}IPSECINIT_S;

/*This data structure is used to intialize the TDB on the basis of transform.
The data structure contains TDB intialization, termination and input, output
processing functions*/
typedef struct tagXFORMSW
{
    USHORT xf_type;         /* Unique ID of xform */
    USHORT xf_flags;        /* flags(see below) */
    CHAR   *xf_name;        /* human-readable name */
    LONG (*xf_attach)();    /* called at config time */
    LONG (*xf_init)(TDB_S *, struct tagXFORMSW *, IPSECINIT_S *);
    LONG (*xf_zeroize)(TDB_S *); /* termination */
    MBUF_S *(*xf_input)(MBUF_S *, TDB_S *); /* input */
    LONG (*xf_output)(MBUF_S *, TDB_S *, MBUF_S **);  /* output */
}XFORMSW_S;

/* Encryption algorithms switch table item structure */
typedef struct tagENC_XFORM
{
    LONG nType;
    CHAR acName[IPSEC_MAX_ALG_NAME_LENGTH];        /* Algorithm name */
    USHORT usBlockSize;
    USHORT usIVSize;
    USHORT usMinKey;
    USHORT usMaxKey;
    ULONG ulIVMask;           /* Or all possible modes, zero iv = 1 */
    VOID(*init)(UCHAR *pucTdb_key, UCHAR *pucKey, ULONG ulKeyLen);
    VOID(*encrypt)(UCHAR *pTdb_key, UCHAR *);
    VOID(*decrypt)(UCHAR *pTdb_key, UCHAR *);
}IPSEC_ENC_XFORM_S;

/*Module level information of IPSec module*/
typedef struct tagIPSEC_MOD_INFO
{
    ULONG ulModID;
    ULONG ulSubModID;
    ULONG ulLocalIPC_TID;
    ULONG ulPeerIPC_TID;
    ULONG ulLocalIPC_KEY_TID;
    ULONG ulPeerIPC_KEY_TID;
    ULONG ulTaskId;         /* Task ID of IPSEC module*/
    ULONG ulMsgQId;         /*Message queue ID of IPSEC module*/
    ULONG ulSECMsgQID;  /* Message queue ID of software and SEC hardware */
    ULONG ulTmrQId;
    ULONG ulIPCQId;
    ULONG ulCFGQId;
    ULONG ulDpdQId;
    ULONG ulCacheQId;
    ULONG ulHWQId;

    /*Ipv6: Security Support*/
    ULONG ulIPSEC6QId;     /* Queue for Processing IPV6 packets. Currently,
                            a single queue is used for Ipv4 and Ipv6 packets.
                            So this Queue id is assigned from Ipv4 queue id*/

    /*Ipv6: Security Support*/
    ULONG ulIPv6QID;       /* IPV6 Queue ID. Used by Ipsec6 to send the
                            packet to IPV6 */

    ULONG ulIPSec6TaskId; /* Task ID  where IPSEC6  packet processing will
                            happen.Currently Ipsec task ID is assigned*/
    ULONG ulIntfStateQId; /* Task ID for Interface state noification*/
}IPSEC_MOD_INFO_S;

/*Moved from ipsec_sh_cfg.h*/
#define IPSEC_DATA_QUEUE_LENGTH     2000
#define IPSEC_HWDATA_QUEUE_LENGTH   2000
#define IPSEC_EVENT_IPSP_HWDATAREQ  0x0008

/* Begin: AP performance improve */
#define IPSEC_FF_ETH_OUTPUT_FUNID           0
#define IPSEC_FF_IPSEC_INPUT_FUNID          1
#define IPSEC_FF_ISNEEDMERGETOSECTASK_FUNID 2
#define IPSEC_FF_ISNEEDMERGETOETHTAS_FUNID  3

/* End: AP performance improve */

#define IPSEC_DPD_MAX_MSGS_PROCESS 20

#define IPSEC_CFG_MAX_MSGS_PROCESS 10

#define IPSEC_INTF_MAX_MSGS_PROCESS 10


/* Added by sumangala. For HW encryption support */
#define MODE_CFG_ENABLE  0x0001
#define TS_NARROW        0x0002
#define NAT_T            0x0004

typedef enum  tagIPSEC_PACKET_TYPE_E
{
    IPSEC_PACKET_FLOW = 1,
    IPSEC_PACKET,
    IPSEC_PACKET_FLOW6,
    IPSEC_PACKET6,
    IPSEC_PACKET_MAX = 0xFFFFFFFF,
}IPSEC_PACKET_TYPE_E;

typedef enum tagIPSEC_EXPIRATION_TYPE_E
{
    IPSEC_SOFT_EXPIRATION,
    IPSEC_HARD_EXPIRATION,
    IPSEC_EXP_MAX = 0xFFFFFFFF
}IPSEC_EXPIRATION_TYPE_E;

typedef enum tagIPSEC_REPLAY_ACTION_TYPE_E
{
    IPSEC_P1_REKEY = 1,         /* Rekey Phase 1 SA */
    IPSEC_P2_REKEY,             /* Rekey Phase 2 SA */
    IPSEC_REAUTH,               /* ReAuthenticate the peer */
    IPSEC_REPLAY_ACTION_MAX = 0xFFFFFFFF
}IPSEC_REPLAY_ACTION_TYPE_E;

typedef enum tagIPSEC_CACHE_TYPE_E
{
    IPSEC_SECURE_CACHE,
    IPSEC_UNSECURE_CACHE,
    IPSEC_CACHE_MAX = 0xFFFFFFFF
}IPSEC_CACHE_TYPE_E;

typedef enum tagIPSEC_OPERATE_TYPE_E
{
    SEC_ADD,     /*Add*/
    SEC_DEL,     /*Del*/
    SEC_UPDATE,
    SEC_USE_NEW_SA,
    IPSEC_OPER_MAX = 0xFFFFFFFF
}IPSEC_OPERATE_TYPE_E;

typedef enum tagIPSEC_HW_SYNC_FLAG_E
{
    IPSEC_SYNC,
    IPSEC_ASYNC,
    IPSEC_SYNC_MAX = 0xFFFFFFFF
}IPSEC_HW_SYNC_FLAG_E;

typedef enum tagIPSEC_HW_NOTIFY_TYPE_E
{
    IPSEC_OUTBOUND_SA_MISS,         /* 0  Outbound SA miss */
    IPSEC_OUTBOUND_CACHE_MISS,      /* 1  Outbound Cache miss */
    IPSEC_INBOUND_SA_MISS,          /* 2  Inbound SA miss for a inbound IPSec packet */
    IPSEC_NONIPSEC_CACHE_MISMATCH,  /* 3  Unencrypted traffic */
    IPSEC_INPUT_CACHE_MISMATCH,     /* 4  Input packet post check */
    IPSEC_SA_TRAFFIC_EXPIRE,        /* 5  haredware IPSec SA traffic expire */
    IPSEC_DPD_TRIGGER,              /* 6  dpd trigger  notify */
    IPSEC_IDLE_CACHE_CLEANUP,       /* 7  Cleanup the idle cache which is not used for long time */
    IPSEC_IDLE_SA_CLEANUP,          /* 8  Clearnup the idle SA which is not used for long time */
    IPSEC_RENEGOTIATION_AFTERSWICH, /* 9  Renegotiation notification after switch happen */
    IPSEC_DOWNLOAD_PACKET,          /* 10 When ipsec receives a packet for encryption or decryption
                                           ipsec will download it to hw. This enum is used by
                                           ipsec to notify hw in case of download is not successful */
    IPSEC_PACKET_CACHE_DOWNLOAD,    /* 11 When SW ipsec receives a packet and
                                           downloads cache correcponding to that packet */
    IPSEC_REPLAY_ATTACK,            /* 12 HW_FWD has detected replay attack and wants IPSEC to take action
                                           according to 'ucExpirationType' field in 'IPSEC_HW_COMMON_S'
                                            (IPSEC_P1_REKEY, IPSEC_P2_REKEY, IPSEC_REAUTH) */

    IPSEC6_OUTBOUND_SA_MISS,        /* 13 IPv6 Outbound SA miss */
    IPSEC6_INBOUND_SA_MISS,         /* 14 IPv6 Inbound SA miss for a inbound IPSec packet */
    IPSEC6_DPD_TRIGGER,             /* 15 IPv6 DPD trigger  notify */
    IPSEC6_SA_TRAFFIC_EXPIRE,       /* 16 IPv6 haredware IPSec SA traffic expire */
    IPSEC6_IDLE_SA_CLEANUP,         /* 17 Cleanup the idle SA which is not used for long time */
    IPSEC6_DOWNLOAD_PACKET,         /* 18 When ipsec receives a packet for encryption or decryption ipsec will
                                           download it to hw. This enum is used by ipsec to notify hw in case
                                           of download is not successfull */
    IPSEC6_REPLAY_ATTACK,           /* 19 HW_FWD has detected replay attack and wants IPSEC to take action
                                           according to 'ucExpirationType' field in 'IPSEC_HW_COMMON_S'
                                            (IPSEC_P1_REKEY, IPSEC_P2_REKEY, IPSEC_REAUTH) */

    IPSEC_INBOUND_SA_HIT,

    IPSEC_NOTIFY_MAX = 0xFFFFFFFF
}IPSEC_HW_NOTIFY_TYPE_E;

typedef enum tagIPSEC_CONFIG_PARAM_E
{
    IPSEC_ACL_CHANGE,           /* acl change*/
    IPSEC_PEER_DELETE,          /* Delete Peer info */
    IPSEC_POL_DELETE,           /* Delete policy*/
    IPSEC_POLICY_ADD,           /* Add a policy */
    IPSEC_POLICY_CONFIG_CHANGE, /* Configuration change in policy */
    IPSEC_PEER_ADD,             /* Add Peer info */
    IPSEC_CONFIG_MAX = 0xFFFFFFFF
}IPSEC_CONFIG_PARAM_E;

typedef enum tagIPSEC_WARNING_MSG_E
{
    IPSEC_CACHE_FULL,
    IPSEC_SA_FULL,
    IPSEC_CACHE_GOINGTO_FULL,
    IPSEC_SA_GOINGTO_FULL,
    IPSEC_WAR_MAX = 0xFFFFFFFF
}IPSEC_WARNING_MSG_E;

typedef enum tagIPSEC_HW_SA_MODE_E
{
    IPSEC_TRANSPORT,
    IPSEC_TUNNEL,
    IPSEC_MODE_MAX = 0xFFFFFFFF
}IPSEC_HW_SA_MODE_E;

typedef struct tagIPSEC_HW_SA
{
    CHAR  szPolicyName[IPSEC_MAX_MAP_NAME + 1];     /* Policy Name */
    UCHAR szDynaPolicyName[IPSEC_MAX_MAP_NAME + 1]; /* Template policy name*/
    ULONG ulSequenceNumber;                     /* Sequence number */
    ULONG ulSubSeqNum;           /* To Store ACL Rule ID, to Create Multiple SA for Each Rule*/
    ULONG ulACLGroup;                          /*ACL rule*/
    ULONG ulIfIndex;                            /* IFINDEX where the policy is
                                                    applied*/
    ULONG ulPeerID;                             /* Id for the peer */
    ULONG ulPeerIpAddress;                      /* Peer IP address.  In case
                                                of peer with no remote address
                                                peer id and this will uniquely
                                                identify peer*/
#if (TCPIP_IN_VRP == VRP_NO)
    ACL_Item stFlow;
#else
    IPOS_ACL_Item stFlow;
#endif
    ULONG  ulModeCFGASrcddr;                    /* mode cfg source address */
                                                /* Note:SGSN don't use it */
    IPSEC_TRAFFIC_SELECTOR_S stTS;              /* TS information */
                                                /* Note:SGSN don't use it */

    ULONG  ulDirection;                        /*SA direction,inbound -1 ,
                                                               Outbound 0 */
    ULONG  ulSPI;                               /*SA SPI*/
    ULONG  ulLocalIP;                           /*tunnel local IP*/
    ULONG  ulPeerIP;                            /*tunnel peer IP*/
    ULONG  ulLocalIF;                           /* outgoing interface address */
    USHORT usSrcPort;
    USHORT usDstPort;
    UCHAR ucProto;
    UCHAR ucSaMode;                             /*SA type: manual, isakmp,
                                                    dynamic*/
    UCHAR ucReserved[2];

    ULONG ulTrafficExpire;                      /*SA traffic lifetime,
                                                 hardware support the traffic
                                                 expire.*/
    UCHAR  ucMode;                      /* transform mode:tunnel or transport */
    UCHAR  ucEncrypt_Alg;               /* encryption algorithm */
    UCHAR  ucAuth_Alg;                  /* authentication algirthem  */
    UCHAR  ucBlockSize;                 /*  Encryption algorithm Block Size */

    UCHAR  aucEspEncrypt_key[IPSEC_STRLEN_32];      /*encryption key*/
    ULONG  ulEncrypt_keyLen;                    /*encryption key length*/
    UCHAR  aucEspAuth_key[IPSEC_STRLEN_64];         /*authentication key*/
    ULONG  ulAuth_keyLen;                       /*authentication key length*/

    ULONG ulAHAuthKeyLen;
    UCHAR aucAhAuth_key[IPSEC_STRLEN_64];       /* Authentication key */

    UCHAR puc_iv[IPSEC_MAX_IVS];        /* That's enough space */

    USHORT  us_ivlen;          /* IV length */

    USHORT  us_wnd;

    /*IPB_IR_ACL_ITEM_S stFlow;*/                   /* dynamic policy */

    ULONG  ulFlag;

    /*
    #define MODE_CFG_ENABLE  0x0001
    #define TS_NARROW        0x0002
    #define NAT_T            0x0004
    */
    /*Added for IPOS vpn*/
    ULONG ulVrfIndex;

    /*LTE multiple ACL-SA: Action defines whether the flow is deny/allow
    this is used to by pass the deny packet*/
    ULONG ulAction;

    /*Added for ipv6 support*/
    IN6ADDR_S stPeerIpAddress;                  /* Peer IP address.  In case
                                                of peer with no remote address
                                                peer id and this will uniquely
                                                identify peer*/
    IN6ADDR_S stLocalIP;                           /*tunnel local IP*/
    IN6ADDR_S stPeerIP;                            /*tunnel peer IP*/
    UCHAR ucAddrType;
    UCHAR ucRevd[3];

    /*GGSN:HA*/
    /* IKE Ph1 SA Responder Cookie is used to associate Ipsec SA
        and IKE Ph1 SA in the GGSN product. This is used only for Inbound Tdb*/
    UCHAR szIkePh1RespSpi[IPSEC_IKE_RCOOKIE_LENGTH];
}IPSEC_HW_SA_S;

typedef struct tagIPSEC6_HW_SA
{
    CHAR  szPolicyName[IPSEC_MAX_MAP_NAME + 1];     /* Policy Name */
    UCHAR szDynaPolicyName[IPSEC_MAX_MAP_NAME + 1]; /* Template policy name*/
    ULONG ulSequenceNumber;                         /* Sequence number */
    ULONG ulSubSeqNum;                              /* To Store ACL Rule ID, to Create Multiple SA for Each Rule*/
    ULONG ulACLGroup;                               /* ACL Group number */
    ULONG ulIfIndex;                                /* IFINDEX where the policy is applied*/
    ULONG ulPeerID;                                 /* Id for the peer */
    IN6ADDR_S stPeerIpAddress;                      /* Peer IP address. In case of peer with no remote address
                                                       peer id and this will uniquely identify peer */
    IPSEC_COMM_ACL_ITEM_S stACLItems;
    /* IPSEC6_TRAFFIC_SELECTOR_S stTS6;                TS information for IPv6, Note:SGSN don't use it */
    ULONG  ulDirection;                             /* SA direction, inbound - 1, Outbound 0 */
    ULONG  ulSPI;                                   /* SA SPI */
    IN6ADDR_S stLocalIP;                            /* tunnel local IP */
    IN6ADDR_S stPeerIP;                             /* tunnel peer IP */
    IN6ADDR_S stLocalIF;                               /* outgoing interface address */
    USHORT usSrcPort;
    USHORT usDstPort;
    UCHAR ucProto;
    UCHAR ucSaMode;                                 /* SA type: manual, isakmp, dynamic */
    UCHAR ucAddrType;
    UCHAR ucReserved;

    ULONG ulTrafficExpire;                          /* SA traffic lifetime, hardware support the traffic expire.*/
    UCHAR  ucMode;                                  /* transform mode:tunnel or transport */
    UCHAR  ucEncrypt_Alg;                           /* encryption algorithm */
    UCHAR  ucAuth_Alg;                              /* authentication algirthem  */
    UCHAR  ucBlockSize;                             /* Encryption algorithm Block Size */
    UCHAR  aucEspEncrypt_key[IPSEC_STRLEN_32];      /* encryption key */
    ULONG  ulEncrypt_keyLen;                        /* encryption key length */
    UCHAR  aucEspAuth_key[IPSEC_STRLEN_64];         /* authentication key */
    ULONG  ulAuth_keyLen;                           /* authentication key length */
    ULONG  ulAHAuthKeyLen;
    UCHAR  aucAhAuth_key[IPSEC_STRLEN_64];          /* Authentication key */
    UCHAR  puc_iv[IPSEC_MAX_IVS];                   /* That's enough space */
    USHORT us_ivlen;                                /* IV length */
    USHORT us_wnd;
    ULONG ulVrfIndex;
    ULONG ulAction;                                 /* LTE multiple ACL-SA: Action defines whether the flow
                                                       is deny/allow this is used to by pass the deny packet */
    ULONG  ulFlag;

    UCHAR szIkePh1RespSpi[IPSEC_IKE_RCOOKIE_LENGTH];/* IKE Ph1 SA Responder Cookie is used to associate Ipsec SA
                                                       and IKE Ph1 SA in the GGSN product. This is used only for
                                                       Inbound Tdb*/

   IPSEC_TRAFFIC_SELECTOR_S stTS4;                  /* TS information for IPv4 */
}IPSEC6_HW_SA_S;

typedef struct tagIPSEC6_POLICY_INFO_S
{
    UCHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];     /* Policy group name */
    UCHAR szDynaPolicyName[IPSEC_MAX_MAP_NAME + 1]; /* Template policy name */
    ULONG ulPeerId;
    IN6ADDR_S stPeerIpAddress;
    IN6ADDR_S stModeCfgSourceAddress;
    ULONG ulSequenceNumber;                         /* Policy sequence number */
    ULONG ulAclNumber;                              /* ACL number of policy */
    ULONG ulSubSeqNum;                              /* To Store ACL Rule ID, to Create Multiple SA for Each Rule */
    ULONG ulIfIndex;
    IN6ADDR_S stLocalIP;                            /* Tunnel Local Address */
    IN6ADDR_S stRemoteIP;                           /* Tunnel Remote Address */
    USHORT usSourcePort;                            /* Added for NAT-ondemand DPD support */
    USHORT usDestPort;                              /* Added for NAT-ondemand DPD support */
    ULONG  ulReplayWindowSize;                      /* Replay Window Size */
    UCHAR  ucSaMode;                                /* manual, isakmp, dynamic */
    UCHAR  ucAddrType;                              /* Added for ipv6 */
    UCHAR  ucACLVer;                                /* ACL: 4, 6 */
    UCHAR  ucRes[1];
}IPSEC6_POLICY_INFO_S;

typedef struct tagIPSEC6_HW_COMMON_S
{
    IPSEC6_POLICY_INFO_S stPolicyInfo;
    ULONG ulPacketType;                             /* PacketFlow, packetdata, invalid */
    ULONG ulSyncFlag;                               /* sync, async */
    ULONG ulFlowNumber;                             /* Number of flows sent during cache
                                                       delete message from HW*/
    ULONG ulSANumber;                               /* Number of SAs to be deleted */
    UCHAR ucExpirationType;
    UCHAR ucReserved[3];
}IPSEC6_HW_COMMON_S;

/* By Prateek: The packet flow information is sent by HW-FWD Module to software,
   for cleaning up cache.*/
typedef struct tagIPSEC_HW_CACHE_INFO_S
{
    ULONG ulSourceIP;
    ULONG ulDestIP;
    ULONG ulSourcePort;
    ULONG ulDestPort;
    ULONG ulProtocol;
    UCHAR ucDSCP; /*support Qos extention*/
    UCHAR ucCacheType;
    UCHAR ucReserved[2];

    /*Kuldeep : B513 Changes*/
    ULONG ulVrfIndex;
}IPSEC_HW_CACHE_INFO_S;

typedef struct tagIPSEC_POLICY_INFO_S
{
    UCHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];    /*Policy group name*/
    UCHAR szDynaPolicyName[IPSEC_MAX_MAP_NAME + 1];/*Template policy name*/
    ULONG ulPeerId;
    ULONG ulPeerIpAddress;
    ULONG ulSequenceNumber;                       /*Policy sequence number*/
    ULONG ulAclNumber;                            /* ACL number of policy*/
    ULONG ulModeCfgSourceAddress;                 /* For modecfg policy */
    ULONG ulIfIndex;

    /* IPSEC_ACL_ITEM stFlow; */                  /* Only for dynamic entries*/
    ULONG ulLocalIP;                              /* Tunnel Local Address */
    ULONG ulRemoteIP;                             /* Tunnel Remote Address */
    /*IPSEC_ACL_ITEM stFlow;  */                  /* Only for dynamic entries*/

    VOID  *pvModeCfgSourceAddr;          /* Added for ipv6 modecfg policy and
                                                    it containd ipv6 address */
    USHORT usSourcePort;                 /* Added for NAT-ondemand DPD support*/
    USHORT usDestPort;                   /* Added for NAT-ondemand DPD support*/
    UCHAR ucPolicyType;                 /* 0-isakmp, 1-manual, 2-dynamic 4-dynatemplate 5 - modecfg*/
    UCHAR ucResv[3];
}IPSEC_POLICY_INFO_S;


/* Manjunath :Should be moved to appropriate file */
typedef struct tagIPSEC_HW_COMMON_S
{
    IPSEC_POLICY_INFO_S stPolicyInfo;
    ULONG ulPacketType; /* PacketFlow,packetdata,invalid */
    ULONG ulSyncFlag; /*sync, async*/
    ULONG ulFlowNumber; /* Number of flows sent during cache delete message
                            from HW*/
    ULONG ulSANumber;   /* Number of SAs to be deleted */
    UCHAR ucExpirationType;
    UCHAR ucCacheType;   /* Used by HW to send cache type during cleanup cache*/
    UCHAR ucReserved[2];
}IPSEC_HW_COMMON_S;


/* This structure is required to send  Policy Sequence number and ACL no */
typedef struct tagIPSEC_POLICY_ACL_S
{
    ULONG ulAclGroupNo;
    ULONG ulPolicySeqno;
    ULONG ulACLRuleNum;
    UCHAR ucACLVer;
    UCHAR ucPolicyType;   /* 0-isakmp, 1-manual, 2-dynamic 4-dynatemplate 5 - modecfg*/
    UCHAR ucLocalBackup;  /* Flag used to indicate normal or Local/Backup policy.
                             YES means this is local/backup. NO means normal policy */
    UCHAR ucUsed;         /* Flag used to tell HW whether or not to use this Policy for matching
                             and forwarding traffic. This will be YES for all normal policies */
}IPSEC_POLICY_ACL_S;

/* This structure is required to send the policy name and if index list to HW */
typedef struct tagIPSEC_INTERFACEPOLICY_S
{
    CHAR szPolicyName[IPSEC_MAX_MAP_NAME + 1];
    ULONG ulIfIndex;    /* If index on which policy is applied */
}IPSEC_INTERFACEPOLICY_S;


/*B053: Peer Reliability (Master/Slave)*/
/*structure which contains the interface index information for the Hardware
which is master and which is slave*/
typedef struct  tagIPSEC_MS_POLICY_RELATION_HW_BIND_INFO
{
    ULONG ulMasterIfIndex;      /*Master tunnel if index*/
    ULONG ulMasterPolicySeq;    /*Master policy sequence*/
    ULONG ulSlaveIfIndex;       /*Slave tunnel if index*/
    ULONG ulSlavePolicySeq;     /*Slave policy sequence*/
    ULONG ulSelect;             /*policy need to use currently */
} IPSEC_MS_POLICY_RELATION_HW_BIND_S;

typedef struct tagIPSEC_HW_PEER_INFO
{
    ULONG ulVrfIndex;
    ULONG ulPeerID;
    ULONG ulPeerIPAddr;
    USHORT usSourcePort;
    USHORT usDestPort;

}IPSEC_HW_PEER_INFO_S;

typedef struct tagIPSEC_GEN_HARD_CALLBACK_S
{
    ULONG (*pfNPAGT_IPSEC_AclMapWithIfnet) (ULONG ulOperType,
                                        IPSEC_POLICY_ACL_S *aulPolicyAclGroupNo,
                                        ULONG ulNumOfAclItem, ULONG ulifIndex,
                                        CHAR *szPolicyName);

    ULONG (*pfNPAGT_IPSEC_Get_Peer_InbPkt_Count)(ULONG ulPeerIndex,
                                                       ULONG ulPeerIPAddr,
                                                       ULONG *pulInputPktNo);

    ULONG (*pfNPAGT_IPSEC_Set_OnDemandDpdPending_By_Peer)(ULONG ulPeerId,
                                                            ULONG ulPeerIPAddr,
                                                            UCHAR ucFlag);
#if (IPSEC_YES == IPSEC_CACHE)
    ULONG (*pfNPAGT_IPSEC_Cache_Update)(ULONG ulOperType, ULONG ulCacheType,
                                        IPSEC_PACKET_FLOW_INFO_S *pstFlowInfor,
                                        IPSEC_TdbIndex_S *pstTdbIndex);
#endif

    ULONG (*pfNPAGT_IPSEC_SA_Update)(ULONG ulOperType, IPSEC_HW_SA_S *pstSAMsg,
                                        IPSEC_PACKET_FLOW_INFO_S *pstFlowInfor,
                                        IPSEC_TdbIndex_S *pstSAIndex,
                                        ULONG ulNoOfSAs);

    ULONG (*pfNPAGT_IPSEC_ConfigChange)(ULONG ulOperType,
                                        IPSEC_POLICY_INFO_S *pstPolicy);

    ULONG (*pfNPAGT_IPSEC_DwnPacket)(VOID* pdata, IPSEC_TdbIndex_S *pstTdbIndex);

    ULONG (*pfNPAGT_IPSEC_GetSA)();
#if (IPSEC_YES == IPSEC_CACHE)
    ULONG (*pfNPAGT_IPSEC_GetCache)();
#endif

    ULONG (*pfNPAGT_IPSEC_Warning)(ULONG ulWarnType, ULONG ulCacheType, VOID* pdata);

    /*Added For S9300 */

    /*S9300.ITR2.STORY.2*/
    ULONG (*pfNPAGT_IPSEC_WithTemplate_Get_Peer_InbPkt_Count)(ULONG ulPeerID,
                                                ULONG ulPeerIPAddr,
                                                USHORT usSourcePort,
                                                USHORT usDestPort,
                                                ULONG *pulInputPktNo);


    /*B050: Traffic based SA_Expiry*/
    ULONG (*pfNPAGT_IPSEC_Get_TrafficUsages_ForSA) ( IPSEC_TdbIndex_S *pstTdbIndex,
                                                     ULONG *pulCurTrafficUsages );

    ULONG (*pfNPAGT_IPSEC_Get_Peer_InbPkt_Count_ByAllPara) (IPSEC_HW_PEER_INFO_S *pstPeerInfo,
                                                            ULONG *pulInputPktNo);


    /*B053: Peer Reliability (MAster/Slave)*/
    ULONG (*pfNPAGT_IPSEC_SetDel_MasSlv_Policy)(
                                        IPSEC_MS_POLICY_RELATION_HW_BIND_S *pstMsPolInfo,
                                        ULONG ulOper);

    ULONG (*pfNPAGT_IPSEC_Set_OnDemandDpdPending_By_Peer_Vrf)(ULONG ulPeerId,
                                                            ULONG ulPeerIPAddr,
                                                            USHORT usSourcePort,
                                                            USHORT usDestPort,
                                                            ULONG ulVrfIndex,
                                                            UCHAR ucFlag);

    /*HERT 3.4 DO requirement*/
    ULONG (*pfNPAGT_IPSEC_GetIPSECDoStats)(ULONG ulOperType, IPSEC_DO_STATS_S *pstIpsecDoStats);
#if (IPSEC_YES == IPSEC_IPV6)
    ULONG (*pfNPAGT_IPSEC6_SA_Update)(ULONG ulOperType, IPSEC6_HW_SA_S *pstSAMsg, VOID *pvFlowInfo,
                                        IPSEC6_TdbIndex_S *pstSAIndex, ULONG ulNoOfSAs);

    ULONG (*pfNPAGT_IPSEC6_Set_OnDemandDpdPending_By_Peer)(IPSEC6_HW_PEER_INFO_S *pstPeerInfo, UCHAR ucFlag);

    ULONG (*pfNPAGT_IPSEC6_ConfigChange)(ULONG ulOperType, IPSEC6_POLICY_INFO_S *pstPolicy);

    /* To ask HW to process the packet */
    ULONG (*pfNPAGT_IPSEC6_DwnPacket)(VOID* pdata, IPSEC6_TdbIndex_S *pstTdbIndex);

    /* Traffic based SA_Expiry */
    ULONG (*pfNPAGT_IPSEC6_Get_TrafficUsages_ForSA)(IPSEC6_TdbIndex_S *pstTdbIndex,
                                        ULONG *pulCurTrafficUsages);

    /* DPD: To get the number of packets received from this peer */
    ULONG (*pfNPAGT_IPSEC6_Get_InbPkt_Count)(IPSEC6_HW_PEER_INFO_S *pstPeerInfo,
                                        ULONG *pulInputPktNo);
    ULONG (*pfNPAGT_IPSEC6_AclMapWithIfnet) (ULONG ulOperType,
                                        IPSEC_POLICY_ACL_S *aulPolicyAclGroupNo,
                                        ULONG ulNumOfAclItem, ULONG ulifIndex,
                                        CHAR *szPolicyName);
    ULONG (*pfNPAGT_IPSEC6_Warning)(ULONG ulWarnType, ULONG ulCacheType, VOID* pvData);
#endif

}IPSEC_GEN_HARD_CALLBACK_S;

/* New Warning framework */
#define IPSEC_WARNING_ID  0x00010050

/* Different type of IPSEC warnings */
typedef enum tagIPSEC_WARNING_TYPE_E
{
    IPSEC_POLICYAPPLY_FAIL = IPSEC_WARNING_ID,
    IPSEC_POLICY_DELETE_FROM_INTERFACE,
    IPSEC_WARN_IF_DELETE,
    IPSEC_WARN_PRODUCT_REGISTER,
    IPSEC_WARN_POLICY_MISMATCH,
    IPSEC_WARN_NO_POLICY_FOR_SA_CREATION,
    IPSEC_MAX_WARNING_TYPE_ENUM_VALUE = 0x7FFFFFFF
}IPSEC_WARNING_TYPE_E;

/* These are the sub warning warning types corresponding to the warning types */
typedef enum tagIPSEC_WARN_SUBTYPE_E
{
    IPSEC_WARN_NO_ACL_IN_POLICY,
    IPSEC_WARN_ACL_DOES_NOT_EXIST,
    IPSEC_WARN_PROPOSAL_DOES_NOT_EXIST,
    IPSEC_WARN_NO_PROPOSAL_IN_POLICY,
    IPSEC_WARN_NO_PEER_IN_POLICY,
    IPSEC_WARN_NO_LOCAL_ADDRESS,
    IPSEC_WARN_NO_PEER_ADDRESS,
    IPSEC_WARN_NO_KEY_FOR_AH,
    IPSEC_WARN_NO_KEY_FOR_ESP,
    IPSEC_WARN_KEY_LENGTH_INVALID,
    IPSEC_WARN_NO_SPI_FOR_AH,
    IPSEC_WARN_NO_SPI_FOR_ESP,
    IPSEC_WARN_POL_DEL_FROM_INTERFACE,
    IPSEC_WARN_INTERFACE_DELETE,
    IPSEC_WARN_POLICY_DELETE,
    IPSEC_WARN_TUNNEL_NOTIFY_NOT_REGISTER,
    IPSEC_WARN_NP_DOWNLOAD_FAIL_NOT_REGISTER,
    IPSEC_WARN_NO_POLICY_FOR_FLOW_INFO,
    IPSEC_WARN_POL_NOT_FOUND,
    IPSEC_WARN_NO_POLICY_ON_INTERFACE,
    IPSEC_WARN_SUBTYPE_MAX_ARRAY,
    IPSEC_WARN_MAX_ENUM_VALUE = 0x7FFFFFFF
}IPSEC_WARN_SUBTYPE_E;

/* this structure gives general info related to the sub warning types.
This structure is used for the following sub warning types
IPSEC_WARN_NO_ACL_IN_POLICY,
IPSEC_WARN_ACL_DOES_NOT_EXIST,
IPSEC_WARN_PROPOSAL_DOES_NOT_EXIST,
IPSEC_WARN_NO_PROPOSAL_IN_POLICY,
IPSEC_WARN_NO_PEER_IN_POLICY,
IPSEC_WARN_NO_LOCAL_ADDRESS,
IPSEC_WARN_NO_PEER_ADDRESS,
IPSEC_WARN_NO_KEY_FOR_AH,
IPSEC_WARN_NO_KEY_FOR_ESP,
IPSEC_WARN_KEY_LENGTH_INVALID,
IPSEC_WARN_NO_SPI_FOR_AH,
IPSEC_WARN_NO_SPI_FOR_ESP*/
typedef struct tagIPSEC_POL_INFO_S
{
    ULONG ulWarnType; /* gives the id that specifies why the policy
                                could not be applied */
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1]; /* Name of the policy that could
                                        not be applied on the interface */
    ULONG ulSequenceNumber; /* sequence number of the policy that could not
                                    be applied on the interface */
    ULONG ulPolicyMode;         /* Type of policy */
}IPSEC_POL_INFO_S;

/*
IPSEC_WARN_MANUAL_UNDO
IPSEC_WARN_POLICY_DELETE
IPSEC_WARN_INTERFACE_DELETE*/
typedef struct tagIPSEC_IFINDEX_INFO_S
{
    ULONG ulWarnType; /* gives the id that specifies why the policy
                                could not be applied */
    CHAR szMapName[IPSEC_MAX_MAP_NAME + 1]; /* Name of the policy that could
                                        not be applied on the interface */
    ULONG ulIfIndex;
}IPSEC_IFINDEX_INFO_S;

/* this structure gives general info related to the sub warning types.
This structure is used for the following sub warning types
IPSEC_WARN_NO_POLICY_FOR_FLOW_INFO*/
typedef struct tagIPSEC_FLOW_S
{
    ULONG ulWarnType;
    ULONG ulSourceIPAddr;
    ULONG ulSourceIPMask;
    ULONG ulDestIPAddr;
    ULONG ulDestIPMask;
    UCHAR ucPID;
    UCHAR ucReserved[3];
    USHORT usSP;
    USHORT usDP;
    ULONG ulPeerIpAddress;
    ULONG IfIndex;          /* B211 : Warning Enhancement */
}IPSEC_FLOW_S;

/* this structure gives general info related to the sub warning types.
This structure is used for the following sub warning types
IPSEC_WARN_POL_NOT_FOUND,
IPSEC_WARN_NO_POLICY_ON_INTERFACE*/
typedef struct tagIPSEC_SA_CREATION_INFO_S
{
    ULONG ulWarnType;
    ULONG ulPeerIpAddress;
    ULONG ulIfIndex;
}IPSEC_SA_CREATION_INFO_S;

/* this structure gives general info related to the sub warning types.
This structure is used for the following sub warning types
IPSEC_WARN_TUNNEL_NOTIFY_NOT_REGISTER
IPSEC_WARN_NP_DOWNLOAD_FAIL_NOT_REGISTER */
typedef struct tagIPSEC_PRODUCT_REGISTER_S
{
    ULONG ulWarnType;
}IPSEC_PRODUCT_REGISTER_S;

/*B110-NP*/
/*Hook function from the Product to IPSEC for NP Download failure*/
typedef ULONG (*NPDOWNLOADFAILURENOTIFY) (ULONG ulMid, ULONG ulNpErrcode,
                            ULONG ulIfIndex, ULONG ulCmdOrType, VOID *pArg);

typedef struct tagIPSEC_NP_CACHE_DOWNLOADFAIL_INFO
{
    IPSEC_TdbIndex_S stTdbIndex;
    IPSEC_PACKET_FLOW_INFO_S stPacketFlow;
    ULONG ulCacheType;
}IPSEC_NP_CACHE_DOWNLOAD_FAIL_INFO;

#define IPSEC_CONFIG_STRING_LENGTH           80  /*Maximum length of any name*/
#define IPSEC_CONFIG_HEX_KEY_LENGTH       288 /*Maximum length of hex key*/
#define IPSEC_CONFIG_STRING_KEY_LENGTH    288   /*Maximum length of string key*/

typedef struct tagIPSEC_PROPOSAL_CONFIG_S
{
    CHAR szTransformName[IPSEC_CONFIG_STRING_LENGTH];/*Ipsec Proposal Name <1-16> chars incl '\0'*/
    ULONG ulAHAlg;               /*AH Authentication algorithm Type
                                     MD5 - 1 , SHA1 - 2 , NULL - 0*/
    ULONG ulEspHashType;         /*ESP Authentication algorithm Type
                                     MD5 - 1 , SHA1 - 2 , NULL - 0*/
    ULONG ulEspEncrType;         /*ESP Encryption algorithm Type
                                    NULL -  0,DES - 1,3DES - 2,BLOWFISH - 3,
                                    SKIPJACK - 4, CAST - 5,
                                    AES128 - 6,AES192 - 7,AES256 - 8 */
    ULONG ulEncapsulationType;  /*Encapsulation mode: Tunnel - 0,Transport -1*/
    ULONG ulProtocolType;        /*Ipsec Protocol:AH - 0 or ESP-1 or AHESP - 2
                                    AH-IPCOMP - 3
                                    ESP-IPCOMP - 4
                                    AHESP-IPCOMP - 5*/
    ULONG ulCompressAlgorithm;   /*Compression Algorithm Type - COMP_LZS-4*/
}IPSEC_PROPOSAL_CONFIG_S;

typedef struct tagIPSEC_POLICY_MANUAL_S
{
    CHAR szMapName[IPSEC_CONFIG_STRING_LENGTH];   /*Policy Name*/
    ULONG ulMapSeq;           /*Policy sequence number <1-10000>*/
    USHORT usListNumber;       /*ACL number  - <3000-3999>*/
    UCHAR ucPolicyMode;            /* 0-isakmp, 1-manual, 2-dynamic */
    UCHAR ucResv;

    CHAR szTransformName[IPSEC_CONFIG_STRING_LENGTH]; /*Ipsec Proposal Name of <1-16> Chars incl  '\0'*/
    CHAR szVPNName[IPSEC_CONFIG_STRING_LENGTH];        /* VPN instance Name <1-32> chars incl '\0'*/

    /*String Key configurations */
    UCHAR szAHInboundKeyString[IPSEC_CONFIG_STRING_KEY_LENGTH];        /*<1-256> including '\0'*/
    UCHAR szAHOutboundKeyString[IPSEC_CONFIG_STRING_KEY_LENGTH];       /*<1-256> including '\0'*/
    UCHAR szESPInboundKeyString[IPSEC_CONFIG_STRING_KEY_LENGTH];       /*<1-256> including '\0'*/
    UCHAR szESPOutboundKeyString[IPSEC_CONFIG_STRING_KEY_LENGTH];      /*<1-256> including '\0'*/

    /*Hex Key configurations for*/
    UCHAR szAHInboundAuthHexKeyString[IPSEC_CONFIG_HEX_KEY_LENGTH];  /*<1-20> including '\0'*/
    UCHAR szAHOutboundAuthHexKeyString[IPSEC_CONFIG_HEX_KEY_LENGTH]; /*<1-20> including '\0'*/
    UCHAR szESPInboundAuthHexKeyString[IPSEC_CONFIG_HEX_KEY_LENGTH]; /*<1-20> including '\0'*/
    UCHAR szESPOutboundAuthHexKeyString[IPSEC_CONFIG_HEX_KEY_LENGTH];/*<1-20> including '\0'*/
    UCHAR szESPInboundEncrHexKeyString[IPSEC_CONFIG_HEX_KEY_LENGTH]; /*<1-24> including '\0'*/
    UCHAR szESPOutboundEncrHexKeyString[IPSEC_CONFIG_HEX_KEY_LENGTH];/*<1-24> including '\0'*/

    ULONG ulInboundAhSPI;    /*<256-4294967295> */
    ULONG ulInboundEspSPI;   /*<256-4294967295> */
    ULONG ulOutboundAhSPI;   /*<256-4294967295> */
    ULONG ulOutboundEspSPI;  /*<256-4294967295> */

    ULONG ulLocalAddress; /* Tunnel local Address <X.X.X.X>*/
    ULONG ulPeerAddress[IPSEC_CRYPTO_MAP_MAXPEERS]; /* peer addrs for isakmp*/
    USHORT usPeers;        /*Number of peers for manual policy*/
    UCHAR ucAddrFamType;   /*  Address Family Type 4  for  IPv4 , 6 For  IPv6 */
    USHORT usResv;
    VOID * pvIPSec6Blk;    /*  Point to IPsec6 Control  Block */
}IPSEC_POLICY_MANUAL_S;

typedef struct tagIPSEC_POLICY_ISAKMPMODECFG_S
{
    CHAR szMapName[IPSEC_CONFIG_STRING_LENGTH]; /*Policy name*/
    CHAR szDynaMapName[IPSEC_CONFIG_STRING_LENGTH];
    ULONG ulMapSeq;     /*Policy sequence number <1-10000>*/
    ULONG ulSaTriggerMode;     /*Traffic Based -1 or Auto Trigger - 2 */
    CHAR szTransformName[IPSEC_CRYPTOMAP_MAX_TRANSFORM_NUM][IPSEC_CONFIG_STRING_LENGTH];   /*Ipsec Proposal of <1-16> Chars incl '\0'*/
    CHAR szPeerName[IPSEC_CONFIG_STRING_LENGTH];         /*Ike peer name of <1-16> chars incl  '\0'*/
    ULONG ulPFSType;      /*Dh Group Type -  1 or 2*/
    ULONG ulTrafficPeriodsFlag;  /* 1 for Trafficbased Periods*/
    ULONG ulTrafficPeriods;      /*Kilo bytes - <256-4194303>*/

    ULONG ulTimePeriodsFlag;   /* 1 for Timebased Periods*/
    ULONG ulTimePeriods;       /*Ipsec SA lifetime in seconds - <30-604800>*/

    ULONG ulLocalAddress; /* Tunnel local Address <X.X.X.X> for non-SGSN
                            products*/
    USHORT usListNumber;          /*ACL number- <3000-3999>*/
    UCHAR ucPolicyMode;                /* 0-isakmp, 1-manual, 2-dynamic */
    UCHAR ucTrafficSelectorMode;/*Enable  - 1 Dsiable - 0. Used only for IKEV2*/
    VOID * pvIPSec6Blk;    /*  Point to IPsec6 Control  Block */
    UCHAR ucAddrFamType;   /*  Address Family Type 4  for  IPv4 , 6 For  IPv6 */
    UCHAR  ucRes[3];
}IPSEC_POLICY_ISAKMPMODECFG_S;

/*Added function pointer for S9300 warning messages.*/
typedef VOID (*pfIPSEC_WarningOut)(ULONG ulWarningID, VOID* pWarnParam);

/*Ipv6: Security Support*/



typedef struct tagIPsec6CryptoMap
{
    IN6ADDR_S  stLocalAddr; /* local address */
    IN6ADDR_S  stPeerAddr; /*remote address */
    ULONG      ulIfIndex;
} IPSEC6_CRYPTO_MAP_S;

typedef struct tagIPsec6Peer
{
    IN6ADDR_S  stAddress;
    IN6ADDR_S  stEndAddress;
    IN6ADDR_S  stLocalAddress;
} IPSEC6_PEER_S;

/* ESP6 packet statistics structure */
typedef struct tagIPSEC_IPV6_ESPSTAT_S
{
    ULONG    esps_ulHDrops;     /* packet shorter than header shows */
    ULONG    esps_ulNoTdb;      /* not find SA*/
    ULONG    esps_ulBadKcr;     /* no use var, reserved */
    ULONG    esps_ulQFull;      /* IPSec queue is full*/
    ULONG    esps_ulNoXForm;    /* attempted to use uninitialized SA*/
    ULONG    esps_ulBadLen;     /* Packet header len bad*/
    ULONG    esps_ulWrap;       /* Replay counter wrapped around */
    ULONG    esps_ulBadAuth;    /* authentication failure for packet*/
    ULONG    esps_ulReplay;     /* Possible packet replay detected */
    ULONG    esps_ulInput;      /* Input ESP packets */
    ULONG    esps_ulOutput;     /* Output ESP packets */
    ULONG    esps_ulInDrops;    /* Dropped input ESP packets */
    ULONG    esps_ulOutDrops;   /* Dropped output ESP packets */
    ULONG    esps_ulInvalid;    /* Trying to use an invalid TDB */
    ULONG    esps_ulInBytes;    /* input bytes */
    ULONG    esps_ulOutBytes;   /* output bytes */
    ULONG    esps_ulTooBig;     /* packet got larger than IP_MAXPACKET */
    ULONG    esps_ulPDrops;     /* packet blocked due to policy */
    ULONG    esps_ulHardFails;  /* processed unsuccessfully by hardware */
    ULONG    esps_ulMiscDrops;  /* Dropped due to inv addrs family, interface addr
                                chng, inv ports, ike lookup fail, prepend fl,
                                append fail, pullup fail */
    ULONG    esps_ulEncrptFails;
    ULONG    esps_ulDecrptfails;

}IPSEC_IPV6_ESPSTAT_S;

/* AH6 packet statistics structure */
typedef struct tagIPSEC_IPV6_AHSTAT_S
{
    ULONG    ahs_ulHDrops;      /* packet shorter than header shows */
    ULONG    ahs_ulNoTdb;       /* not find SA*/
    ULONG    ahs_ulBadKcr;      /* no use var, reserved */
    ULONG    ahs_ulBadAuth;     /* authentication failure for packet*/
    ULONG    ahs_ulNoXForm;     /* attempted to use uninitialized SA*/
    ULONG    ahs_ulQFull;       /* IPSec queue is full*/
    ULONG    ahs_ulWrap;        /* replay counter wrapped for packets*/
    ULONG    ahs_ulReplay;      /* duplicate packet received*/
    ULONG    ahs_ulBadAuthLen;  /* bad authenticator length */
    ULONG    ahs_ulInput;       /* Input AH packets */
    ULONG    ahs_ulOutput;      /* Output AH packets */
    ULONG    ahs_ulInDrops;     /* Dropped input AH packets */
    ULONG    ahs_ulOutDrops;    /* Dropped output AH packets */
    ULONG    ahs_ulInvalid;     /* Trying to use an invalid TDB */
    ULONG    ahs_ulInBytes;     /* input bytes */
    ULONG    ahs_ulOutBytes;    /* output bytes */
    ULONG    ahs_ulTooBig;      /* packet got larger than IP_MAXPACKET */
    ULONG    ahs_ulPDrops;      /* packet blocked due to policy */
    ULONG    ahs_ulHardFails;  /* processed unsuccessfully by hardware */
    ULONG    ahs_ulMiscDrops;   /* Dropped due to inv addrs family, interface addr
                                chng, inv ports, ike lookup fail, prepend fl,
                                append fail, pullup fail */
}IPSEC_IPV6_AHSTAT_S;


/*Ipv6: Security Support*/
typedef struct tagIPSEC_IPv6_CallbackAPI_S
{
    ULONG (*pfIPSEC_IPv6_CreateDelPolicy)(IPSEC_POLICY_S *pstPolicy,
                                        ULONG ulPolicyMode,
                                        ULONG ulOpMode);

    ULONG (*pfIPSEC_IPv6_SetDelTunnelPeerAddress)(IPSEC_POLICY_S *pstPolicy,
                                        IN6ADDR_S *pstPeerAddress,
                                        ULONG ulOpMode);

    ULONG (*pfIPSEC_IPv6_SetDelTunnelLocalAddress)(IPSEC_POLICY_S *pstPolicy,
                                        IN6ADDR_S *pstLocalAddress,
                                        ULONG ulOpMode);

    ULONG (*pfIPSEC_IPv6_MapInterface)(ULONG ulIfIndex, CHAR *szInMapName,
                                        ULONG ulOpMode,
                                        ULONG *pulErrMapNum);

    ULONG (*pfIPSEC_IPv6_GetFirst_SAIfHandle)(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                        IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                        IPSEC_SHOW_INTERFACE_S *pstInterface);

    ULONG (*pfIPSEC_IPv6_GetDelIPSECSAStat)(IPSEC_IPV6_AHSTAT_S *pstALLAHStat,
                                        IPSEC_IPV6_ESPSTAT_S *pstALLESPStat,
                                        IPSEC_STAT_S *pstIPSECStat,
                                        ULONG ulOpMode);
    VOID (*pfIPSEC_IPv6_EncryptNAPackets)(ULONG ulOpMode);

    ULONG (*pfIPSEC_IPv6_Hook_IP_Output)(MBUF_S *pstMBuf);

    ULONG (*pfIPSEC_IPv6_InputPreCheck)(MBUF_S *pstMBuf);

    ULONG (*pfIPSEC_IPv6_AH_ProtoInput)(MBUF_S **ppstMBuf, ULONG *pulOff,
                                        ULONG ulNextHdr);

    ULONG (*pfIPSEC_IPv6_ESP_ProtoInput)(MBUF_S **ppstMBuf, ULONG *pulOff,
                                        ULONG ulNextHdr);

    ULONG (*pfIPSEC_IPv6_InputPacketMsg_Handler)(ULONG *pulMsgBuf);

    ULONG (*pfIPSEC_IPv6_OutputPacketMsg_Handler)(ULONG *pulMsgBuf);

    /* IPSEC_IPv6_DeleteTdbEntryGroupfrmInterface */
    VOID (*pfIPSEC_IPv6_DeleteTdbEntryGroupfrmInterface)(CHAR *szMapName,
                                        ULONG ulIfIndex);

    /* IPSEC_IPv6_GetTdbFromTernaryOperator*/
    TDB_S *(*pfIPSEC_IPv6_GetTdbFromTernaryOperator)(ULONG ulSpi,
                                        IN6ADDR_S *pstIpv6Addr, UCHAR ucProto);

    /* IPSEC_IPv6_SetAddressForSA*/
    VOID (*pfIPSEC_IPv6_SetAddressForSA)(VOID *pManualData,
                                        TDB_S *pTdb, UCHAR ucBoundType);

    /* IPSEC_IPv6_GetTdb*/
    TDB_S *(*pfIPSEC_IPv6_GetTdb)(ULONG ulSPI, union sockaddr_union *pDst,
                                        UCHAR ucProto);

    /* IPSEC_IPv6_PutTdb*/
    VOID (*pfIPSEC_IPv6_PutTdb)(TDB_S *pstTdb);

    /* IPSEC_IPv6_RemoveTdb */
    VOID (*pfIPSEC_IPv6_RemoveTdb)(TDB_S *pstTdb);

    /* IPSEC_IPv6_CancelIntefaceUseIpsec */
    VOID (*pfIPSEC_IPv6_CancelIntefaceUseIpsec)(ULONG ulIfIndex);

    /* IPSEC_IPv6_GetSAEntryCnt */
    ULONG (*pfIPSEC_IPv6_GetSAEntryCnt)(ULONG ulIfIndex,
                                        ULONG *pulTotalSAEntryCnt,
                                        ULONG ulSeq, IN6ADDR_S *pstPeerAddr,
                                        ULONG ulType);

    /* IPSEC_Ipv6_GetPrefixLen */
    ULONG (*pfIPSEC_Ipv6_GetPrefixLen)(IN6ADDR_S *pstAddress);

    /* IPSEC_IPv6_Tdb_GetNext */
    TDB_S *(*pfIPSEC_IPv6_Tdb_GetNext)(TDB_S *pCurNode);

    /* IPSEC_IPv6_ProtoInit */
    LONG (*pfIPSEC_IPv6_ProtoInit)(TDB_S *pstTdb,
                                        IPSECINIT_S *pInit, USHORT usAlgorithm);

    /* IPSEC_IPv6_Init */
    ULONG (*pfIPSEC_IPv6_Init)(VOID);

    /* IPSEC_IPv6_AssignAddr*/
    VOID (*pfIPSEC_IPv6_AssignAddr)(IN6ADDR_S *pstAddr,
                                        union sockaddr_union *pstSockAddr);

    /* IPSEC_IPv6_IsAddressZero*/
    ULONG (*pfIPSEC_IPv6_IsAddressZero)(IN6ADDR_S *pstSockAddr);

    /* IPSEC_IPv6_FindCryptoMapByPeerAddress*/
    ULONG (*pfIPSEC_IPv6_FindCryptoMapByPeerAddress)(VOID *pvSockAddr, VOID *pvSrcSockAddr,
                                        ULONG ulIfIndex,
                                        CHAR *szIKEPeerName);

    /* IPSEC_Ipv6_cryptomap_is_a_peer*/
    ULONG (*pfIPSEC_Ipv6_cryptomap_is_a_peer)(IPSEC_PEER_S *pstPeer,
                                        union sockaddr_union *puSockAddr);

    /* IPSEC_IPv6_IsAddressEqual*/
    ULONG (*pfIPSEC_IPv6_IsAddressEqual)(IN6ADDR_S *pstSrcAddr,
                                        union sockaddr_union *pstSockAddr);
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    /* IPSEC_IPv6_Pfkeyv2Acquire    */
    LONG (*pfIPSEC_IPv6_Pfkeyv2Acquire)(IPSEC_TdbEntry_S *pTdbEntry,
                                        MBUF_S *pMBuf, VOID *pFlow,
                                        ULONG ulIfIndex, UCHAR ucDSCP);
#endif

    /*IPSEC_IPv6_ClearSA*/
    ULONG (*pfIPSEC_IPv6_ClearSA)(IPSEC_POLICY_NAME_SEQ_S *pstPolicy,
                                        IPSEC6_SA_PARA_S *pstSAParameters,
                                        IN6ADDR_S *pstRemoteIpAddr, ULONG ulMode);

    /*Ipv6: Security Support*/
    ULONG (*pfIPSEC_IPv6_CreateDelPolicyTemplate)(CHAR *szTemplateName,
                                        ULONG ulSeqNumber, ULONG ulOpMode);

    ULONG (*pfIPSEC_IPv6_FormPrefix) (IN6ADDR_S *pstAddress, ULONG ulPreLen);

    VOID  (*pfIPSEC_Item6ToId6)(VOID *pstFlow, VOID *pvSrcId, VOID *pvDstId);
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    ULONG  (*pfIPSEC_IPV6_SendDetailstoIke)(VOID **headers, VOID **SendHeaders,
                                        LONG *rval);

    VOID (*pfIPSEC_IPv6_IdToItem)(VOID *pvSrc_id, VOID *pvDst_id, VOID *pvFlow);
#endif

    ULONG (*pfIPSEC_IPv6_RemoveDynaTdbEntry)(IPSEC_TdbEntry_S *pstTdbEntry,
                                        IPSEC_TdbEntry_S *pstDynaTdbEntry);
#if ((IPSEC_YES == IPSEC_GENERIC_HW_SUPPORT))
    /* Added HW stat fn for IPV6 by r72335 */
    ULONG (*pfIPSEC_IPV6_GetDelIPSECGenHwStat)(IPSEC_GEN_HW_STAT_S *pstGenHwStat,
                                        ULONG ulOpMode);
#endif

    /* Added peer stat fn for IPV6 by r72335 */
    VOID (*pfIPSEC_IPv6_GetPeerStats)(ULONG *pulIpsecPeerCount,
                                        ULONG *pulIpsecDynaPeerCount,
                                        ULONG *pulIpsecTotalPeerCount,
                                        ULONG *pulIpsecDpdTimerCount);

    ULONG (*pfIPSEC_IPv6_SetDelV4CtrlTrafficOnV6)(UCHAR *szMapName, ULONG ulOpMode);

#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    ULONG (*pfIPSEC_IPv6_HW_NotifyReceive) (ULONG ulNotifyType, IPSEC6_HW_COMMON_S *pstCommNotifyInfo,
                                            VOID* pvPacketInfo, IPSEC6_TdbIndex_S *pstTdbIndex);
#endif

    VOID (*pfIPSEC6_IPv4_Output) (MBUF_S *pstMBuf, ULONG ulIfIndex, ULONG *pulUseIpsec);

    ULONG (*pfIPSEC_CreateIPv6TdbProc)(TDB_S *pTempTdb, VOID *pstManual, UCHAR ucBoundType,
                                        USHORT alg, IPSECINIT_S *pInit);
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    VOID (*pfIPSEC_GetIdItem_IPv6)(VOID **ppvHeaders, IPSEC_COMM_ACL_ITEM_S *pstFlowv2);
#endif
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    VOID (*pfIPSEC_IPV6_HwStatAclMap)(ULONG ulOnePolicy, ULONG ulOpType);
#endif

    ULONG (*pfIPSEC_IPv6_CalculateHashForDynaTdbEntry)(ULONG ulMaskLen, UCHAR *pucAddress);

    ULONG (*pfIPSEC_IPv6_DisplayAllPeers)(ULONG ulWaitListHandle, CHAR *pcBuffer, ULONG *pulFetchCount);

#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    VOID (*pfIPSEC_IPv6_DownloadInOutboundTdbToHW)(IPSEC_TdbEntry_S *pstTdbEntry, ULONG ulIfIndex);

    ULONG (*pfIPSEC_IPv6_FillTdbIndexValues)(IPSEC_TdbEntry_S *pstTdbEntry, IPSEC6_TdbIndex_S *pstSAIndexs);
#endif
    IPSEC_PEER_S * (*pfIPSEC_IPv6_GetFirstDynaPeer)();

    IPSEC_PEER_S * (*pfIPSEC_IPv6_GetNextDynaPeer)(IPSEC_PEER_S *pstDynaPeer);

    VOID (*pfIPSEC_IPv6_GetPeerCount)(ULONG *pulPeerCount);

#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    ULONG (*pfIPSEC_IPv6_HW_CopyTdbInfotoHWSA )(IPSEC_TdbEntry_S *pstTdbEntry, ULONG ulIfIndex,
                                                IPSEC6_HW_SA_S **ppstHWSAMsg, ULONG *pulNoofSAs);

    ULONG (*pfIPSEC_IPv6_HandleGenHWMsg)(ULONG ulNotifyType, IPSEC6_HW_COMMON_S *pstCommNotifyInfo, VOID* pvPacketInfo,
                                         IPSEC6_TdbIndex_S *pstTdbIndex);
#endif

    VOID (*pfIPSEC_IPv6_InsertDynaPeer)(IPSEC_PEER_S *pstDynaPeer);

    BOOL_T (*pfIPSEC_IPv6_MatchAclFlow_TdbEntry)(IPSEC_TdbEntry_S *pstTdbEntry, IPSEC_COMM_ACL_ITEM_S *pstFlow,
                                                 UCHAR ucTrafficSel);
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)

    VOID (*pfIPSEC_IPv6_NotifyNPDownloadFailure)(ULONG ulOperationType, ULONG ulErrorCode,
                                                 IPSEC6_TdbIndex_S *pstInTdbIndex,
                                                 IPSEC6_PACKET_FLOW_INFO_S *pstInPacketFlow,
                                                 ULONG ulCacheType);
#endif

    ULONG (*pfIPSEC_IPv6_RegisterTunnelStatusNotify_Callback)(IPSEC6_NOTIFY_TUNNEL_STATUS_CALLBACK_NEW pfFuncPtr,
                                                              ULONG ulAppId);

    ULONG (*pfIPSEC_IPv6_RemoveDynaPeer)(IPSEC_PEER_S *pstDynaPeer);

    VOID (*pfIPSEC_IPv6_TunnelStateChangeNotify)(TDB_S *pstTdb, ULONG ulState);

    ULONG (*pfIPSEC_IPv6_UpdateDynaPeer)(IPSEC_TdbEntry_S *pstDynaTdbEntry, IN6ADDR_S* pstIpv6Addr, USHORT usSourcePort,
                                         USHORT usDestPort);

    LONG (*pfIPSEC_IPv6_UpdateTdbForTdbEntry)(VOID **headers, TDB_S *pstTdb, IPSEC_TdbEntry_S **ppstTdbEntry,
                                              ACL6_Item *pstFlow);

    ULONG (*pfIPSEC_IPv6_Wrapper_Get_Peer_InbPkt_Count)(ULONG ulVrfIndex, ULONG ulPeerID, IN6ADDR_S *pstPeerIPAddr,
                                                        USHORT usSourcePort, USHORT usDestPort, ULONG *pulInputPktNo);
}IPSEC_IPV6_CALLBACKAPI_S;

typedef struct tagIPSEC_TUNNEL_PARAMS_S
{
    /* To denote the Tunnel protocol is GRE */
    ULONG ulTunnelModeGreValue;

    /* To denote the Tunnel protocol is mGRE */
    ULONG ulTunnelModeMGreValue;

    /* To denote the Tunnel protocol is IPSEC */
    ULONG ulTunnelModeIPsecValue;

    /* If we get the interface type, then we need to check if the interface type
       is TUNNEL or not. This param should denote whether the interface type is
       tunnel or not */
    ULONG ulInterfaceTypeTunnelValue;
}IPSEC_TUNNEL_PARAMS_S;

/* Added To get Flow (ACL-Info) from prodcut, in case IPSEC-Profile */
typedef struct tagIPSEC_TUNNEL_FLOW_S
{
    ULONG ulFlowSrc;
    ULONG ulSrcMask;
    ULONG ulFlowDest;
    ULONG ulDestMask;
    UCHAR ucProtocol;
    UCHAR ucResv[3];
}IPSEC_TUNNEL_FLOW_S;

/* TUNNEL Callback for DMVPN support */
typedef struct tagIPSEC_TUNNEL_CallbackAPI_S
{
    ULONG (*pfIPSEC_TUNNEL_GetTunnelMode)(ULONG ulIfIndex, UCHAR *pucMode);

    ULONG (*pfIPSEC_TUNNEL_GetSrcDestByIfIndex)(ULONG ulIfIndex, ULONG *pulTunnelSrc,
                                                ULONG *pulTunnelDest, ULONG *pulVrfIndex);
    ULONG (*pfIPSEC_TUNNEL_GetParams)(IPSEC_TUNNEL_PARAMS_S *pstTunnelParams);

    /* Added To get Flow (ACL-Info) from prodcut, in case IPSEC-Profile */
    ULONG (*pfIPSEC_TUNNEL_GetTunnelFlow)(ULONG ulIfIndex, ULONG ulSpokeDestAddr, ULONG ulVrfIndex, IPSEC_TUNNEL_FLOW_S *pstFlow);
}IPSEC_TUNNEL_CALLBACKAPI_S;


/* IP-in-IP packet statistics structure */
typedef struct tagIPSEC_IPV6_IPIP_STAT_S
{
    ULONG    ip6s_ulInPackets;      /* total input packets */
    ULONG    ip6s_ulOutPackets;     /* total output packets */
    ULONG    ip6s_ulHDrops;         /* packet shorter than header shows */
    ULONG    ip6s_ulBadLen;         /* Packet header len bad*/
    ULONG    ip6s_ulNotIP6;         /* Packet is not IPv6 packet*/
    ULONG    ip6s_ulQFull;          /* IPSec queue is full*/
    ULONG    ip6s_ulInBytes;        /* input bytes */
    ULONG    ip6s_ulOutBytes;       /* output bytes */
    ULONG    ip6s_ulPDrops;         /* packet dropped due to policy */
    ULONG    ip6s_ulSpoof;          /* IP spoofing attempts */
}IPSEC_IPV6_IPIP_STAT_S;

/* Packet Statistics */
typedef struct tagIPSEC_IP6STAT_S
{
    ULONG   ip6s_ulTotalReceived;   /* total packets received */
    ULONG   ip6s_ulTooShort;        /* packet too short */
    ULONG   ip6s_ulTooSmall;        /* not enough data */
    ULONG   ip6s_ulHopLimitExceed;  /* hop limit exceed */
    ULONG   ip6s_ulBadHeader;       /* error in header processing */
    ULONG   ip6s_ulBadOption;       /* error in option processing */
    ULONG   ip6s_ulFragments;       /* fragments received */
    ULONG   ip6s_ulReassembled;     /* total packets reassembled ok */
    ULONG   ip6s_ulFragDropped;     /* frags dropped (dups, out of space) */
    ULONG   ip6s_ulFragTimeout;     /* fragments timed out */
    ULONG   ip6s_ulOFailedFragments; /* Fragments Failed to Sent Out. */
    ULONG   ip6s_ulNoProto;         /* unknown or unsupported protocol */
    ULONG   ip6s_ulDelivered;       /* datagrams delivered to upper level*/
    ULONG   ip6s_ulLocalOut;        /* total ipv6 packets generated */
    ULONG   ip6s_ulForward;         /* packets forwarded */
    ULONG   ip6s_ulNoRoute;         /* packets discarded due to no route */
    ULONG   ip6s_ulTooBig;          /* packets discarded due to bigger than mtu*/
    ULONG   ip6s_ulFragmented;      /* datagrams sucessfully fragmented */
    ULONG   ip6s_ulOFragments;      /* output fragments created */
    ULONG   ip6s_ulInMulticasts;    /* multicast packets received */
    ULONG   ip6s_ulNotMember;       /* donot join this multicast group */
    ULONG   ip6s_ulOutMulticasts;   /* multicast packets sent */
    ULONG   ip6s_ulDstAddrErr;      /* error in incoming dest addr (invalid and unsupported) */

/* TODO: Where will this happen ??? - this is a MIB requirement */
    ULONG   ip6s_ulInDiscards;      /* Input Dgms which had no pbms, but were discarded due to lack of buffer space */
    ULONG   ip6s_ulOutDiscards;     /* Output Dgms which had no pbms, but were discarded due to lack of buffer space */
}IPSEC_IP6STAT_S;


typedef ULONG (*pfIPSEC_Base_RegIPv6Callback)(IPSEC_IPV6_CALLBACKAPI_S
                                                    *pstIPv6CallbackAPI);

/*GGSN-SUPPORT: DPD*/
typedef struct tagIPSEC_DPDCallBackData_S
{
    ULONG ulPeerType; /* Main Peer or Dynamic Peer.*/
    VOID *pData;
}IPSEC_DPDCALLBACKDATA_S;

/*Defined for EasyVPN*/
#define IPSEC_MAX_FQDN_LEN            254
#define IPSEC_MIN_FQDN_LEN            1

#define IPSEC_MIN_REMOTE_NAME_LEN             1
#define IPSEC_MAX_REMOTE_NAME_LEN             132

#define IPSEC_TRUST_NAME_MIN_LEN          1
#define IPSEC_TRUST_NAME_MAX_LEN          256


typedef struct tagIPSEC_EasyVPN_Info
{
    ULONG ulAuthMethod;
    ULONG ulACLNumber;
    ULONG ulIpAddress;
    ULONG ulIKEVersion;
    ULONG ulLocalAddr;
    ULONG ulVrf;
    ULONG ulLocalIDType;
    ULONG ulPkiFlag;
    CHAR szPreSharedKey[128];
    CHAR szFQDN[IPSEC_MAX_FQDN_LEN];
    CHAR szRemoteName[IPSEC_MAX_REMOTE_NAME_LEN];
    CHAR szObj[IPSEC_TRUST_NAME_MAX_LEN];

} IPSEC_EASYVPN_INFO_S;


typedef struct tagIPSEC_PROFILE_INFO
{
    //IPOS_MEM_CHK_IPSEC_HEAD
    UCHAR szProfileName[IPSEC_MAX_MAP_NAME + 1];
    CHAR szPeerName[IPSEC_MAX_PEERNAME_LEN + 1];
    ULONG ulSALifetimeSeconds;
    ULONG ulSALifetimeKilobytes;
    UCHAR ucSecondsFlag;
    UCHAR ucKilobytesFlag;
    USHORT usTransformCount;  /* Number of IPSec Proposals configured */
    CHAR szTransformName[IPSEC_CRYPTOMAP_MAX_TRANSFORM_NUM][IPSEC_MAX_TRANSFORM_NAME + 1];
    UCHAR ucPFS;

    /* Added for EasyVPN */
    UCHAR ucEasyVPNMode;
    UCHAR ucReserver[2];
    IPSEC_EASYVPN_INFO_S stIpsecEasyVPNInfo;

} IPSEC_PROFILE_INFO_S;


/* Encapsulation Mode */
#define IPSEC_SUPP_MODE_TRANSPORT   0x00000001
#define IPSEC_SUPP_MODE_TUNNEL      0x00000002
#define IPSEC_ALL_SUPPORTED_MODE   (IPSEC_SUPP_MODE_TRANSPORT | IPSEC_SUPP_MODE_TUNNEL)

/* Protocols */
#define IPSEC_SUPP_PROTO_AH         0x00000001
#define IPSEC_SUPP_PROTO_ESP        0x00000002
#define IPSEC_ALL_SUPPORTED_PROTO   (IPSEC_SUPP_PROTO_AH | IPSEC_SUPP_PROTO_ESP)

/* Authentication algorithms */
#define IPSEC_SUPP_AUTH_MD5         0x00000001
#define IPSEC_SUPP_AUTH_SHA1        0x00000002
#define IPSEC_SUPP_AUTH_SHA2_256    0x00000004
#define IPSEC_SUPP_AUTH_SHA2_384    0x00000008
#define IPSEC_SUPP_AUTH_SHA2_512    0x00000010
#define IPSEC_SUPP_AUTH_NULL        0x00000020
#define IPSEC_ALL_SUPPORTED_AUTH_ALGS (IPSEC_SUPP_AUTH_MD5 \
                                            | IPSEC_SUPP_AUTH_SHA1 \
                                            | IPSEC_SUPP_AUTH_SHA2_256 \
                                            | IPSEC_SUPP_AUTH_SHA2_384 \
                                            | IPSEC_SUPP_AUTH_SHA2_512 \
                                            | IPSEC_SUPP_AUTH_NULL)

/* Encryption algorithms */
#define IPSEC_SUPP_ENCR_DES         0x00000001
#define IPSEC_SUPP_ENCR_3DES        0x00000002
#define IPSEC_SUPP_ENCR_AES_128     0x00000004
#define IPSEC_SUPP_ENCR_AES_192     0x00000008
#define IPSEC_SUPP_ENCR_AES_256     0x00000010
#define IPSEC_SUPP_ENCR_NULL        0x00000020
#define IPSEC_ALL_SUPPORTED_ENCR_ALGS (IPSEC_SUPP_ENCR_DES \
                                        | IPSEC_SUPP_ENCR_3DES \
                                        | IPSEC_SUPP_ENCR_AES_128 \
                                        | IPSEC_SUPP_ENCR_AES_192 \
                                        | IPSEC_SUPP_ENCR_AES_256 \
                                        | IPSEC_SUPP_ENCR_NULL)

#define IPSEC_MAX_SUPP_MODE             2
#define IPSEC_MAX_SUPP_TRANSFORM        2
#define IPSEC_MAX_SUPP_AH_AUTHALG       5
#define IPSEC_MAX_SUPP_ESP_AUTHALG      6
#define IPSEC_MAX_SUPP_ENCRALG          6
#define IPSEC_MAX_SUPP_AESALG           3


typedef struct tagIPSEC_PROP_PARAM
{
    ULONG ulEnc;                       /* Bitmap for Encryption Algorithm */
    ULONG ulAuth;                      /* Bitmap for Authentication Method */
    USHORT ustransform;                /* Bitmap for AH, ESP, AHESP */
    UCHAR ucTransformMode;             /* Bitmap for Tunnel/Transport */
    UCHAR ucReserved;                  /* Padding */
}IPSEC_PROP_PARAM_S;

/*B053: Peer Reliability (Master/Slave)*/
/*structure which contains the policy information of which is master
and which is slave*/
typedef struct  tagIPSEC_POLICY_RELATION_BIND_INFO
{
    ULONG  ulMasterPolicySeq;      /*Master policy sequence*/
    ULONG  ulSlavePolicySeq;       /*Slave policy sequence*/
    CHAR  szMasterPolGrpName[IPSEC_MAX_MAP_NAME + 1];   /* master policy group name*/
    CHAR  szSlavePolGrpName[IPSEC_MAX_MAP_NAME + 1];    /*slave policy group name*/
    UCHAR  ulSelect;               /*policy need to use currently,Based on this
                                    value need to select which policy to select
                                    as master,who is slave*/
    UCHAR  ucReserved[3];              /*Byte alignment*/
} IPSEC_POLICY_RELATION_BIND_S;


/*B053: Peer Reliability (Master/Slave): Operation values*/
typedef enum IPSEC_POLICY_RELATION_OPERATE_TYPE_ENUM
{
    IPSEC_RELATION_OPERATE_TYPE_UNBIND = 0, /*UN-BIND:Both the  policy is not
                                                bind to master/slave, it is
                                                independent as normal*/
    IPSEC_RELATION_OPERATE_TYPE_BIND = 1,   /*BIND:Both the  policy will be
                                                master & Slave as per ulSelect*/
    IPSEC_RELATION_OPERATE_TYPE_SET = 2,    /*SET:Same as  bind For  IPSEC */
    IPSEC_RELATION_OPERATE_TYPE_GET = 3,     /*QUERY:Need to pass it to trans,
                                                TRAN will output ulSelect, and
                                                same need to pass to ROSA */
    IPSEC_RELATION_OPERATE_TYPE_MAX = 0xFFFFFFFF
} IPSEC_POLICY_RELATION_OPERATE_TYPE_ENUM;

/*B053: Peer Reliability (Master/Slave) : Select values*/
typedef enum IPSECDRV_SELECT_TYPE_ENUM
{
    IPSECDRV_SELECT_TYPE_UNUSED = 0,        /*unbind*/
    IPSECDRV_SELECT_TYPE_MASTER = 1,        /*use master to encapsulate traffic*/
    IPSECDRV_SELECT_TYPE_SLAVE = 2,         /*use slave to encapsulate traffi*/
    IPSECDRV_SELECT_TYPE__MAX = 0xFFFFFFFF
} IPSECDRV_SELECT_TYPE_ENUM;

/* Type of variable to register IPSEC6/IKE6 registration function */
typedef ULONG (*pfuncIPsecIPv6Reg)();

/* Multi-SeGw Feature */
#define IPSEC_NORMAL_PEER                     0
#define IPSEC_MASTER_PEER                     1
#define IPSEC_SLAVE_PEER                      2

#ifdef __cplusplus
}
#endif

#endif  /* _IPSEC_PUB_H*/

