#ifndef _IPSI_ASN_TYPES_H
#define _IPSI_ASN_TYPES_H

#include "ipsi_pse_build_conf.h"
#include "ipsi_types.h"
#include "sec_sys.h"

#define SEC_MAX_PRV_OID_LONG_NAME_LEN 64
#define SEC_MAX_PRV_OID_SHORT_NAME_LEN 32

/**
* @defgroup asn_types
* This section contains asn-types Structures and Enum.
*/



/**
* @defgroup asn_typesStructures
* @ingroup asn_types
* This section contains asn-types Structures.
*/

/**
* @defgroup SEC_AsnOcts_S
* @ingroup asn_typesStructures
* @code
* typedef struct stSEC_ASNOCTS
* {
*   SEC_UINT32 octetLen;
*   SEC_CHAR*  octs;
* } SEC_AsnOcts_S;
* @endcode
*
* @datastruct octetLen Length of the octet buffer.
* @datastruct octs Buffer for octets.
*/
typedef struct stSEC_ASNOCTS{
    SEC_UINT32 octetLen;
    SEC_CHAR* octs;
} SEC_AsnOcts_S;

typedef SEC_AsnOcts_S SEC_AsnOid_S;

/**
* @defgroup SEC_AsnBits_S
* @ingroup asn_typesStructures
* @code
* typedef struct stSEC_ASNBITS
* {
*   SEC_UINT bitLen;
*   SEC_CHAR *bits;
* } SEC_AsnBits_S;
* @endcode
*
* @datastruct bitLen Length of the bits buffer.
* @datastruct bits Buffer for bits.
*/
typedef struct stSEC_ASNBITS{
    SEC_UINT bitLen; /*Length of the bits buffer*/
    SEC_CHAR *bits;  /*Buffer for bits*/
    SEC_UINT noBytes; /*NO of bytes in th bits*/
} SEC_AsnBits_S;


typedef void* SEC_AsnAny_S;



typedef SEC_AsnAny_S SEC_AsnAnyDefinedBy_S;

/* ASN.1 Basic types */
typedef SEC_UCHAR SEC_AsnBool;
typedef SEC_UINT32 SEC_AsnLen;
/* ASN.1 integer needs to be 4 bytes for encoder */
typedef SEC_INT32 SEC_AsnInt;
typedef SEC_UINT32 SEC_AsnTag;
typedef SEC_AsnInt SEC_AsnEnum;
typedef SEC_CHAR SEC_AsnNull;
typedef SEC_AsnOcts_S SEC_AsnRelativeOid_S;

/* Basic ASN.1 string types */
typedef SEC_AsnOcts_S SEC_VisibleString_S;
typedef SEC_AsnOcts_S SEC_TeletexString_S;
typedef SEC_AsnOcts_S SEC_UTF8String_S;
typedef SEC_AsnOcts_S SEC_UniversalString_S;
typedef SEC_AsnOcts_S SEC_PrintableString_S;
typedef SEC_AsnOcts_S SEC_NumericString_S;
typedef SEC_AsnOcts_S SEC_IA5String_S;
typedef SEC_AsnOcts_S SEC_BMPString_S;
typedef SEC_AsnOcts_S SEC_UTCTime_S;
typedef SEC_AsnOcts_S SEC_GeneralizedTime_S;

/**
* @defgroup SEC_ASN1_TYPE_CODE_E
* @ingroup cmpEnums
* @par Prototype
* @code
* typedef enum
* {
* IPSI_ASN1_TYPE_UTF8STRING                = 0,
* IPSI_ASN1_TYPE_PRINTABLESTRING        = 1,
* IPSI_ASN1_TYPE_IA5STRING              = 2,
* IPSI_ASN1_TYPE_X520NAME                = 3,
* IPSI_ASN1_TYPE_MAX      = 4,
* }SEC_ASN1_TYPE_CODE_E;
* @endcode
*
* @datastruct IPSI_ASN1_TYPE_UTF8STRING=0 UTF8 string type
* @datastruct IPSI_ASN1_TYPE_PRINTABLESTRING=1 Printable string type
* @datastruct IPSI_ASN1_TYPE_IA5STRING=2 IA5 string type
* @datastruct IPSI_ASN1_TYPE_X520NAME=3 X520 Name type
* @datastruct IPSI_ASN1_TYPE_MAX=4 Invalid type. Application should not use this type. Only for internal use.
*/
typedef enum
{
    IPSI_ASN1_TYPE_UTF8STRING = 0,
    IPSI_ASN1_TYPE_PRINTABLESTRING,
    IPSI_ASN1_TYPE_IA5STRING,
    IPSI_ASN1_TYPE_X520NAME,
    IPSI_ASN1_TYPE_MAX
} SEC_ASN1_TYPE_CODE_E;

/**
* @defgroup SEC_PRV_OID_INFO_S
* @ingroup asn_typesStructures
* @code
* typedef struct stPrvOIDInfo
* {
*   SEC_AsnOid_S stAsnOid;
*   SEC_CHAR pucLongOIDName[SEC_MAX_PRV_OID_LONG_NAME_LEN];
*   SEC_UINT32 uiLongOIDNameLen;
*   SEC_CHAR pucShortOIDName[SEC_MAX_PRV_OID_SHORT_NAME_LEN];
*   SEC_UINT32 uiShortOIDNameLen;
*   SEC_ASN1_TYPE_CODE_E eTypeCode;
* } SEC_PRV_OID_INFO_S;
* @endcode
*
* @datastruct stAsnOid Private OID.
* @datastruct pucLongOIDName Long OID name
* @datastruct uiLongOIDNameLen Length of Long OID Name. Maximum characters allowed for Long OID Name, 
* excluding the terminating null character is SEC_MAX_PRV_OID_LONG_NAME_LEN - 1
* @datastruct pucShortOIDName Short OID Name
* @datastruct uiShortOIDNameLen Length of Short OID Name. Maximum characters allowed for Short OID Name, 
* excluding the terminating null character is SEC_MAX_PRV_OID_SHORT_NAME_LEN - 1
* @datastruct eTypeCode Type code for OID
*/
typedef struct stPrvOIDInfo
{
    SEC_AsnOid_S stAsnOid;
    SEC_CHAR pucLongOIDName[SEC_MAX_PRV_OID_LONG_NAME_LEN];
    SEC_UINT32 uiLongOIDNameLen;
    SEC_CHAR pucShortOIDName[SEC_MAX_PRV_OID_SHORT_NAME_LEN];
    SEC_UINT32 uiShortOIDNameLen;
    SEC_ASN1_TYPE_CODE_E eTypeCode;
} SEC_PRV_OID_INFO_S;


#endif // _IPSI_ASN_TYPES_H

