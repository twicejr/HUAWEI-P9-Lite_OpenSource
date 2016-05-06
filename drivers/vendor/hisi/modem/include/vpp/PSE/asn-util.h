#ifndef	_IPSI_ASN_UTIL_H
#define	_IPSI_ASN_UTIL_H

#include "ipsi_pse_build_conf.h"
#include "ipsi_types.h"
#include "sec_sys.h"
#include "asn-types.h"
#include "sec_crypto.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup asn_util
* This section contains the asn-util Functions.
*/



/** @defgroup asn_utilFunctions
* @ingroup asn_util
* This section contains the asn-util Functions.
*/

/**
* @defgroup SEC_BigIntToAsnOcts
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* SEC_BigIntToAsnOcts(SEC_BIGINT_S * pstBigInt);
* @endcode
*
* @par Purpose
* To convert a SEC_BIGINT_S structure to a SEC_AsnOcts_S structure.
*
* @par Description
* This function is used to convert from SEC_BIGINT_S to SEC_AsnOcts_S.
*
* @param[in] pstBigInt Input structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* The converted structure [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* In case of invalid arguments or in case of memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnOcts_S* SEC_BigIntToAsnOcts(SEC_BIGINT_S * pstBigInt);

/**
* @defgroup SEC_AsnOctsToBigInt
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_BIGINT_S* SEC_AsnOctsToBigInt(SEC_AsnOcts_S *pstAsnOcts);
* @endcode
*
* @par Purpose
* To convert a SEC_AsnOcts_S structure to a SEC_BIGINT_S structure.
*
* @par Description
* This function is used to convert SEC_AsnOcts_S to SEC_BIGINT_S.
*
* @param[in] pstAsnOcts Input structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BIGINT_S* Converted structure [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* In case of invalid arguments or in case of memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_BIGINT_S* SEC_AsnOctsToBigInt(SEC_AsnOcts_S *pstAsnOcts);

//This function is used by SSL.Hence import define has been added.
/**
* @defgroup SEC_freeAsnBits
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeAsnBits  (SEC_AsnBits_S *pstAsnBits);
* @endcode
*
* @par Purpose
* To free a SEC_AsnBits_S structure.
*
* @par Description
* This function is used to free a SEC_AsnBits_S structure.
*
* @param[in] pstAsnBits The SEC_AsnBits_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeAsnBits  (SEC_AsnBits_S *pstAsnBits);

/**
* @defgroup SEC_cmpAsnBits
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cmpAsnBits  (SEC_AsnBits_S *pstAsnBits1, SEC_AsnBits_S *pstAsnBits2);
* @endcode
*
* @par Purpose
* To compare a pair of Asn Bit strings.
*
* @par Description
* This function is used to compare the source and destination bit strings.
* This function returns TRUE if the source & destination bit strings are the same. Else it returns FALSE.
*
* @param[in] *pstAsnBits1 Source bit string [N/A]
* @param[in] *pstAsnBits2 Destination bit string [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT If both the bit strings are the same. [TRUE|N/A]
* @retval SEC_INT If the bit strings are different. [FALSE|N/A]
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cmpAsnBits  (SEC_AsnBits_S *pstAsnBits1, SEC_AsnBits_S *pstAsnBits2);


/**
* @defgroup SEC_SetAsnBit
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_SetAsnBit  (SEC_AsnBits_S *pstAsnBits1, SEC_UINT bit);
* @endcode
*
* @par Purpose
* To set a given bit in an Asn bit string to 1.
*
* @par Description
* This function sets a given bit in a bit string to 1.
*
* @param[in] *pstAsnBits1 Bit string [N/A]
* @param[in] bit The position of the bit to be set to 1 [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* Most significant bit is bit 0, least significant bit is bit (pstAsnBits1->bitLen -1).
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_SetAsnBit  (SEC_AsnBits_S *pstAsnBits1, SEC_UINT bit);


/**
* @defgroup SEC_ClrAsnBit
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_ClrAsnBit  (SEC_AsnBits_S *pstAsnBits1, SEC_UINT bit);
* @endcode
*
* @par Purpose
* To set a given bit in an Asn bit string to 0.
*
* @par Description
* This function sets a given bit in a bit string to 0.
*
* @param[in] *pstAsnBits1 Bit string [N/A]
* @param[in] bit The position of the bit to be set to 0 [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* Most significant bit is bit 0, least significant bit is bit(pstAsnBits1->bitLen -1).
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_ClrAsnBit  (SEC_AsnBits_S *pstAsnBits1, SEC_UINT bit);


/**
* @defgroup SEC_GetAsnBit
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_GetAsnBit  (SEC_AsnBits_S *pstAsnBits1, SEC_UINT bit);
* @endcode
*
* @par Purpose
* To get a given bit from an Asn bit string.
*
* @par Description
* This function is used to get a given bit from an Asn bit string.
*
* @param[in] *pstAsnBits1 Bit string [N/A]
* @param[in] bit Position of the bit [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT If the bit is 1 [TRUE|N/A]
* @retval SEC_INT If the bit is 0 [FALSE|N/A]
* @retval SEC_INT If the bit is out of range [0|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* Most significant bit is bit 0, least significant bit is bit (pstAsnBits1->bitLen -1).
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_GetAsnBit  (SEC_AsnBits_S *pstAsnBits1, SEC_UINT bit);

/**
* @defgroup SEC_cpyAsnBits
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyAsnBits(SEC_AsnBits_S *pstDestAsnBits,SEC_AsnBits_S *pstSrcAsnBits);
* @endcode
*
* @par Purpose
* To copy a source Asn bit string to a destination bit string.
*
* @par Description
* Copies a source Asn bit string to a destination bit string.
*
* @param[in] pstSrcAsnBits The source structure [N/A]
* @param[out] pstDestAsnBits The destination structure [N/A]
*
* @retval SEC_UINT32 If invalid arguments are passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Upon successful completion [SEC_SUCCESS|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyAsnBits(SEC_AsnBits_S *pstDestAsnBits,SEC_AsnBits_S *pstSrcAsnBits);

/**
* @defgroup SEC_dupAsnBits
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* SEC_dupAsnBits(SEC_AsnBits_S *pstSrcAsnBits);
* @endcode
*
* @par Purpose
* To duplicate a SEC_AsnBits_S structure.
*
* @par Description
* This function is used to duplicate a SEC_AsnBits_S structure.
*
* @param[in] pstSrcAsnBits The structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Upon successful completion [Copy of the input structure |N/A]
* @retval SEC_AsnBits_S* In case of invalid arguments or in case of memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnBits_S* SEC_dupAsnBits(SEC_AsnBits_S *pstSrcAsnBits);

/**
* @defgroup SEC_freeBMPString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeBMPString  (SEC_BMPString_S *pstBMPString);
* @endcode
*
* @par Purpose
* To free a SEC_BMPString_S structure.
*
* @par Description
* This function is used to free a SEC_BMPString_S structure.
*
* @param[in] pstBMPString The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeBMPString  (SEC_BMPString_S *pstBMPString);

/**
* @defgroup SEC_cvtBMPString2wchar
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cvtBMPString2wchar(SEC_BMPString_S *inOcts, SEC_WCHAR **outStr);
* @endcode
*
* @par Purpose
* To convert a BMP string to a Wide char structure.
*
* @par Description
* This function is used to convert a SEC_BMPString_S to a SEC_WCHAR structure.
*
* @param[in] inOcts The structure to be converted [N/A]
* @param[out] outStr The converted output structure [N/A]
*
* @retval SEC_INT Upon success [0|N/A]
* @retval SEC_INT Upon failure [Less than zero|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cvtBMPString2wchar(SEC_BMPString_S *inOcts, SEC_WCHAR **outStr);

/**
* @defgroup SEC_cpyAsnBool
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyAsnBool(SEC_AsnBool* puiDstAsnBool,SEC_AsnBool* puiSrcAsnBool);
* @endcode
*
* @par Purpose
* To copy one SEC_AsnBool structure onto another.
*
* @par Description
* This function is used to copy a source SEC_AsnBool structure to a destination SEC_AsnBool structure.
*
* @param[in] puiSrcAsnBool Source structure [N/A]
* @param[out] puiDstAsnBool Destination structure [N/A]
*
* @retval SEC_UINT32 Upon successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 In case of invalid arguments [SEC_NULL|N/A]
* @retval SEC_UINT32 In case of memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyAsnBool(SEC_AsnBool* puiDstAsnBool,SEC_AsnBool* puiSrcAsnBool);

/**
* @defgroup SEC_dupAsnBool
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnBool* SEC_dupAsnBool(SEC_AsnBool* pbSrcAsnBool);
* @endcode
*
* @par Purpose
* To duplicate a SEC_AsnBool structure.
*
* @par Description
* This function is used to duplicate a SEC_AsnBool structure.
*
* @param[in] pbSrcAsnBool The source structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBool* A copy of the source structure [SEC_AsnBool*|N/A]
* @retval SEC_AsnBool* In case of invalid arguments or in case of memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnBool* SEC_dupAsnBool(SEC_AsnBool* pbSrcAsnBool);


/**
* @defgroup SEC_checkIA5String
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_checkIA5String(SEC_IA5String_S *octs);
* @endcode
*
* @par Purpose
* To check for a valid SEC_IA5String_S string.
*
* @par Description
* This function is used to check for a SEC_IA5String_S string, that is whether the value of the octets are over 0X7F.
*
* @param[in] octs Input string to be checked [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT In case of a valid IA5 string [0|N/A]
* @retval SEC_INT In case the given string is not a valid IA5 string [-1|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_checkIA5String(SEC_IA5String_S *octs);

/**
* @defgroup SEC_freeIA5String
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeIA5String  (SEC_IA5String_S *pstBMPString);
* @endcode
*
* @par Purpose
* To free a SEC_IA5String_S string.
*
* @par Description
* This function is used to free a SEC_IA5String_S string.
*
* @param[in] pstBMPString The string to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeIA5String  (SEC_IA5String_S *pstBMPString);


/**
* @defgroup SEC_cpyAsnInt
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyAsnInt(SEC_AsnInt* puiDstAsnInt,SEC_AsnInt* puiSrcAsnInt);
* @endcode
*
* @par Purpose
* To copy one SEC_AsnInt structure to another.
*
* @par Description
* This function is used to copy a SEC_AsnInt structure to a destination structure.
*
* @param[in] puiSrcAsnInt The source structure [N/A]
* @param[out] puiDstAsnInt The destination structure [N/A]
*
* @retval SEC_UINT32 Upon successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input arguments are NULL [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyAsnInt(SEC_AsnInt* puiDstAsnInt,SEC_AsnInt* puiSrcAsnInt);

/**
* @defgroup SEC_dupAsnInt
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnInt* SEC_dupAsnInt(SEC_AsnInt* puiSrcAsnInt);
* @endcode
*
* @par Purpose
* To duplicated a SEC_AsnInt structure.
*
* @par Description
* This function is used to duplicate a SEC_AsnInt structure.
*
* @param[in] puiSrcAsnInt The source structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnInt* Upon successful completion [copy of the given structure |N/A]
* @retval SEC_AsnInt* If invalid input or memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnInt* SEC_dupAsnInt(SEC_AsnInt* puiSrcAsnInt);

/**
* @defgroup SEC_dupAsnNull
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnNull* SEC_dupAsnNull(SEC_AsnNull *pcSrcNULL);
* @endcode
*
* @par Purpose
* To duplicate a SEC_AsnNull structure.
*
* @par Description
* This function is used to duplicate a SEC_AsnNull structure.
*
* @param[in] pcSrcNULL The source structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnNull* Upon successful completion [Copy of the source structure|N/A]
* @retval SEC_AsnNull* In case of invalid arguments or memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnNull* SEC_dupAsnNull(SEC_AsnNull *pcSrcNULL);

/**
* @defgroup SEC_cpyAsnNull
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyAsnNull(SEC_AsnNull *pcDstNULL,SEC_AsnNull *pcSrcNULL);
* @endcode
*
* @par Purpose
* To copy one SEC_AsnInt structure onto another.
*
* @par Description
* This function is used to copy a SEC_AsnInt structure to a destination structure.
*
* @param[in] pcSrcNULL The source structure [N/A]
* @param[out] pcDstNULL The destination structure [N/A]
*
* @retval SEC_UINT32 Upon successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input arguments are NULL [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyAsnNull(SEC_AsnNull *pcDstNULL,SEC_AsnNull *pcSrcNULL);

/**
* @defgroup SEC_chkNumericString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_chkNumericString (SEC_NumericString_S *checkBuf);
* @endcode
*
* @par Purpose
* To check for a numeric string.
*
* @par Description
* This function is used to check whether the given input string is a purely numeric string or not.
*
* @param[in] checkBuf The Numeric string to be checked [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT If the given string is purely a numeric string [0|N/A]
* @retval SEC_INT If the input is NULL or if the string has non-numeric characters [-1|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_chkNumericString (SEC_NumericString_S *checkBuf);

/**
* @defgroup SEC_freeNumericString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeNumericString  (SEC_NumericString_S *pstNumericStr);
* @endcode
*
* @par Purpose
* To free a numeric string.
*
* @par Description
* This function is used to free a numeric string.
*
* @param[in] pstNumericStr The string to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeNumericString  (SEC_NumericString_S *pstNumericStr);

//This function is used by SSL.Hence import define has been added.
/**
* @defgroup SEC_freeAsnOcts
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeAsnOcts  (SEC_AsnOcts_S *pstAsnOcts);
* @endcode
*
* @par Purpose
* To free a SEC_AsnOcts_S structure.
*
* @par Description
* This function is used to free a SEC_AsnOcts_S structure.
*
* @param[in] pstAsnOcts The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeAsnOcts  (SEC_AsnOcts_S *pstAsnOcts);

/**
* @defgroup SEC_cpyAsnOcts
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyAsnOcts(SEC_AsnOcts_S *pstDestAsnOcts,SEC_AsnOcts_S *pstSrcAsnOcts);
* @endcode
*
* @par Purpose
* To copy one SEC_AsnOcts_S structure onto another.
*
* @par Description
* This function is used to copy a SEC_AsnOcts_S structure to a destination structure.
*
* @param[in] pstSrcAsnOcts The source structure [N/A]
* @param[out] pstDestAsnOcts The destination structure [N/A]
*
* @retval SEC_UINT32 Upon successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input arguments are NULL [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyAsnOcts(SEC_AsnOcts_S *pstDestAsnOcts,SEC_AsnOcts_S *pstSrcAsnOcts);

//This function is used by SSL.Hence import define has been added.
/**
* @defgroup SEC_dupAsnOcts
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S * SEC_dupAsnOcts(SEC_AsnOcts_S *pstSrcAsnOcts);
* @endcode
*
* @par Purpose
* To duplicate a SEC_AsnOcts_S structure.
*
* @par Description
* This function is used to duplicate a SEC_AsnOcts_S structure.
*
* @param[in] pstSrcAsnOcts The source structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Upon successful completion [Copy of the source structure|N/A]
* @retval SEC_AsnOcts_S* In case of invalid arguments or memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnOcts_S * SEC_dupAsnOcts(SEC_AsnOcts_S *pstSrcAsnOcts);

/**
* @defgroup SEC_cmpAsnOcts
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cmpAsnOcts  (SEC_AsnOcts_S *pstAsnOcts1, SEC_AsnOcts_S *pstAsnOcts2);
* @endcode
*
* @par Purpose
* To compare two SEC_AsnOcts_S structures
*
* @par Description
* This function is used to compare two SEC_AsnOcts_S structures, that is to check if both strings are identical or not.
*
* @param[in] pstAsnOcts1 The source structure [N/A]
* @param[in] pstAsnOcts2 The destination structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT If both the SEC_AsnOcts_S are identical [0|N/A]
* @retval SEC_INT Otherwise [Less than zero or Greater than zero|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cmpAsnOcts  (SEC_AsnOcts_S *pstAsnOcts1, SEC_AsnOcts_S *pstAsnOcts2);

/**
* @defgroup SEC_freeAsnOid
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeAsnOid  (SEC_AsnOid_S *pstAsnOid);
* @endcode
*
* @par Purpose
* To free a SEC_AsnOid_S structure.
*
* @par Description
* This function is used to free a SEC_AsnOid_S structure.
*
* @param[in] pstAsnOid The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeAsnOid  (SEC_AsnOid_S *pstAsnOid);

/**
* @defgroup SEC_cpyAsnOid
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyAsnOid(SEC_AsnOid_S *pstDestOID,SEC_AsnOid_S *pstSrcOID);
* @endcode
*
* @par Purpose
* To copy one SEC_AsnOid_S structure onto another.
*
* @par Description
* This function is used to copy a SEC_AsnOid_S structure to a destination structure.
*
* @param[in] pstSrcOID The source structure [N/A]
* @param[out] pstDestOID The destination structure [N/A]
*
* @retval SEC_UINT32 Upon successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input arguments are NULL [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyAsnOid(SEC_AsnOid_S *pstDestOID,SEC_AsnOid_S *pstSrcOID);

/**
* @defgroup SEC_compareOid
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_BOOL SEC_compareOid(SEC_AsnOid_S *pstDestOID,SEC_AsnOid_S *pstSrcOID);
* @endcode
*
* @par Purpose
* To compare two SEC_AsnOid_S structures.
*
* @par Description
* This function compares two SEC_AsnOid_S structures, that is checks whether both the structures are identical or not.
*
* @param[in] pstSrcOID The source structure [N/A]
* @param[in] pstDestOID The destination structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BOOL If the SEC_AsnOid_S structures do not match [SEC_FALSE|N/A]
* @retval SEC_BOOL If the SEC_AsnOid_S structures match [SEC_TRUE|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_BOOL SEC_compareOid(SEC_AsnOid_S *pstDestOID,SEC_AsnOid_S *pstSrcOID);

/**
* @defgroup SEC_dupAsnOid
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_AsnOid_S* SEC_dupAsnOid(SEC_AsnOid_S *pstSrcOID);
* @endcode
*
* @par Purpose
* To duplicate a SEC_AsnOid_S structure.
*
* @par Description
* This function is used to duplicate a SEC_AsnOid_S structure.
*
* @param[in] pstSrcOID The structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOid_S* Upon successful completion[Copy of the source structure|N/A]
* @retval SEC_AsnOid_S* Upon failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnOid_S* SEC_dupAsnOid(SEC_AsnOid_S *pstSrcOID);

/**
* @defgroup SEC_chkPrintableString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_chkPrintableString(SEC_PrintableString_S *checkBuf);
* @endcode
*
* @par Purpose
* To check for a string with printable characters.
*
* @par Description
* This function checks whether the given string has purely printable characters or not.
*
* @param[in] checkBuf The printable string to be checked [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT If the given string has only printable characters [0|N/A]
* @retval SEC_INT If the input is NULL or if the string has non-printable characters [-1|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_chkPrintableString(SEC_PrintableString_S *checkBuf);

/**
* @defgroup SEC_freePrintableString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freePrintableString(SEC_PrintableString_S *pstPrintableStr);
* @endcode
*
* @par Purpose
* To free a printable string.
*
* @par Description
* This function is used to free a printable string.
*
* @param[in] pstPrintableStr The string to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freePrintableString(SEC_PrintableString_S *pstPrintableStr);

/**
* @defgroup SEC_freeTeletexString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeTeletexString  (SEC_TeletexString_S *pstTeletexStr);
* @endcode
*
* @par Purpose
* To free a SEC_TeletexString_S structure.
*
* @par Description
* This function is used to free a SEC_TeletexString_S structure.
*
* @param[in] pstTeletexStr The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeTeletexString  (SEC_TeletexString_S *pstTeletexStr);

/**
* @defgroup SEC_freeUniversalString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeUniversalString  (SEC_UniversalString_S *pstUniversalStr);
* @endcode
*
* @par Purpose
* To free an Universal String.
*
* @par Description
* This function frees a given Universal String.
*
* @param[in] pstUniversalStr The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeUniversalString  (SEC_UniversalString_S *pstUniversalStr);

/**
* @defgroup SEC_cvtUniversalString2wchar
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cvtUniversalString2wchar(SEC_UniversalString_S *inOcts, SEC_WCHAR **outStr);
* @endcode
*
* @par Purpose
* To convert an Universal String to a wide character string.
*
* @par Description
* This function is converts a SEC_UniversalString_S to a SEC_WCHAR string.
*
* @param[in] inOcts Universal String structure [N/A]
* @param[out] outStr Wide Character string [N/A]
*
* @retval SEC_INT Upon success [0|N/A]
* @retval SEC_INT Upon failure [Less than zero|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cvtUniversalString2wchar(SEC_UniversalString_S *inOcts, SEC_WCHAR **outStr);


/**
* @defgroup SEC_freeUTCTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeUTCTime  (SEC_UTCTime_S *pstUTCTime);
* @endcode
*
* @par Purpose
* To free an UTC Time structure.
*
* @par Description
* This function is used to free a SEC_UTCTime_S structure.
*
* @param[in] pstUTCTime The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeUTCTime  (SEC_UTCTime_S *pstUTCTime);

/**
* @defgroup SEC_freeGeneralizedTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeGeneralizedTime  (SEC_GeneralizedTime_S *pstGenTime);
* @endcode
*
* @par Purpose
* To free a generalized time structure.
*
* @par Description
* This function frees a given SEC_GeneralizedTime_S structure.
*
* @param[in] pstGenTime The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeGeneralizedTime  (SEC_GeneralizedTime_S *pstGenTime);

/**
* @defgroup SEC_cpyGenTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_cpyGenTime(SEC_GeneralizedTime_S *pstDestGenTime,SEC_GeneralizedTime_S *pstSrcGenTime);
* @endcode
*
* @par Purpose
* To copy one GeneralizedTime structure onto another.
*
* @par Description
* This function copies the source SEC_GeneralizedTime_S structure to the destination SEC_GeneralizedTime_S structure.
*
* @param[in] pstSrcGenTimes The source GeneralizedTime [N/A]
* @param[in] pstDestGenTime The destination GeneralizedTime [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful copy [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Any of the inputs are null [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 pstSrcGenTime->octs is null [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* Memory for the destination Generalized time structure must be allocated before calling.
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 SEC_cpyGenTime(SEC_GeneralizedTime_S *pstDestGenTime,SEC_GeneralizedTime_S *pstSrcGenTime);

/**
* @defgroup SEC_dupGenTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_GeneralizedTime_S * SEC_dupGenTime(SEC_GeneralizedTime_S *pstSrcGenTime);
* @endcode
*
* @par Purpose
* To duplicate a Generalized Time structure.
*
* @par Description
* This function duplicates a Generalized Time structure.
*
* @param[in] pstSrcGenTime The structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GeneralizedTime_S* Upon successful completion[The duplicated structure|N/A]
* @retval SEC_GeneralizedTime_S* Upon failure [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_GeneralizedTime_S * SEC_dupGenTime(SEC_GeneralizedTime_S *pstSrcGenTime);

/**
* @defgroup SEC_compareGenTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* DATE_COMPARE_E SEC_compareGenTime(SEC_GeneralizedTime_S *pstDestGenTime,
* SEC_GeneralizedTime_S *pstSrcGenTime,SEC_UINT32 *pulDiffSeconds);
* @endcode
*
* @par Purpose
* To compare two Generalized time structures.
*
* @par Descriptiom
* This function is used to compare two Generalized Time structures and
* check whether the source time is before, after or same as the destination time.
*
* @param[in] pstSrcGenTime Source Gen Time structure [N/A]
* @param[in] pstDestGenTime Destination Gen Time structure [N/A]
* @param[out] pulDiffSeconds The difference between the two times in seconds [N/A]
*
* @retval DATE_COMPARE_E If either of the dates are NULL [SEC_FALSE|N/A]
* @retval DATE_COMPARE_E Error in comparison [ERROR_CMP|N/A]
* @retval DATE_COMPARE_E The two dates are same [EQUAL_DATE|N/A]
* @retval DATE_COMPARE_E First date is before second date [BEFORE_DATE|N/A]
* @retval DATE_COMPARE_E First date is after second date [AFTER_DATE|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL DATE_COMPARE_E SEC_compareGenTime(SEC_GeneralizedTime_S *pstDestGenTime,SEC_GeneralizedTime_S *pstSrcGenTime,SEC_UINT32 *pulDiffSeconds);

/* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are not considered in this function */
/**
* @defgroup SEC_DateTimeToGenTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_GeneralizedTime_S* SEC_DateTimeToGenTime(DATETIME_S* pDateTime);
* @endcode
*
* @par Purpose
* To convert DATETIME_S structure to SEC_GeneralizedTime_S structure.
*
* @par Description
* This function converts a DATETIME structure to a Generalized Time Structure.
*
* @param[in] pDateTime The DATETIME_S structure to be converted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GeneralizedTime_S* Equivalent of the input DATETIME_S structure [SEC_GeneralizedTime_S*|N/A]
* @retval SEC_GeneralizedTime_S* If input arguments are invalid [SEC_NULL|N/A]
* @retval SEC_GeneralizedTime_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_GeneralizedTime_S* SEC_DateTimeToGenTime(DATETIME_S* pDateTime);

/**
* @defgroup SEC_GenTimeToDateTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* DATETIME_S* SEC_GenTimeToDateTime(SEC_GeneralizedTime_S* pGenTime);
* @endcode
*
* @par Purpose
* To convert SEC_GeneralizedTime_S to DATETIME_S.
*
* @par Description
* This function converts a Generalized Time Structure to a DATETIME structure.
*
* @param[in] pGenTime The SEC_GeneralizedTime_S structure to be converted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Equivalent of the input SEC_GeneralizedTime_S structure [DATETIME_S*|N/A]
* @retval DATETIME_S* If input arguments are invalid [SEC_NULL|N/A]
* @retval DATETIME_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL DATETIME_S* SEC_GenTimeToDateTime(SEC_GeneralizedTime_S* pGenTime);


/* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are not considered in this function */
/**
* @defgroup SEC_DateTimeToUTCTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_UTCTime_S* SEC_DateTimeToUTCTime(DATETIME_S* pDateTime);
* @endcode
*
* @par Purpose
* To convert DATETIME_S to SEC_UTCTime_S.
*
* @par Description
* This function converts a DATETIME Structure to an UTC Time Structure.
*
* @param[in] pDateTime The DATETIME structure to be converted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UTCTime_S* Equivalent of the input DATETIME structure [SEC_UTCTime_S*|N/A]
* @retval SEC_UTCTime_S* If input arguments are invalid [SEC_NULL|N/A]
* @retval SEC_UTCTime_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UTCTime_S* SEC_DateTimeToUTCTime(DATETIME_S* pDateTime);

/**
* @defgroup SEC_UTCTimeToDateTime
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* DATETIME_S* SEC_UTCTimeToDateTime(SEC_UTCTime_S* pUTCTime);
* @endcode
*
* @par Purpose
* To convert from SEC_UTCTime_S to DATETIME_S.
*
* @par Description
* This function converts an UTC Time Structure to a DATETIME Structure.
*
* @param[in] pUTCTime The UTC Time structure to be converted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Equivalent of the input SEC_UTCTime_S structure [DATETIME_S*|N/A]
* @retval DATETIME_S* If input arguments are invalid [SEC_NULL|N/A]
* @retval DATETIME_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL DATETIME_S* SEC_UTCTimeToDateTime(SEC_UTCTime_S* pUTCTime);


/**
* @defgroup SEC_freeUTF8String
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeUTF8String (SEC_UTF8String_S *pstUTF8Str);
* @endcode
*
* @par Purpose
* To free a SEC_UTF8String_S structure.
*
* @par Description
* This function frees an UTF-8 string.
*
* @param[in] pstUTF8Str The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeUTF8String (SEC_UTF8String_S *pstUTF8Str);

/**
* @defgroup SEC_cvtUTF8String2wchar
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cvtUTF8String2wchar(SEC_UTF8String_S *inOcts, SEC_WCHAR **outStr);
* @endcode
*
* @par Purpose
* To convert a SEC_UTF8String_S to a SEC_WCHAR structure.
*
* @par Description
* This function converts an UTF-8 String to a Wide char structure.
*
* @param[in] inOcts The UTF8String to be converted [N/A]
* @param[out] *outStr Pointer to the structure in which the Wide char structure output is stored [N/A]
*
* @retval SEC_INT If either of the inputs are NULL [-1|N/A]
* @retval SEC_INT In case of memory allocation failure [-2|N/A]
* @retval SEC_INT Upon successful conversion [0|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cvtUTF8String2wchar(SEC_UTF8String_S *inOcts, SEC_WCHAR **outStr);

/**
* @defgroup SEC_cvtUTF8towchar
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cvtUTF8towchar(SEC_CHAR *utf8Str, SEC_WCHAR **outStr);
* @endcode
*
* @par Purpose
* To convert UTF-8 structure to a SEC_WCHAR structure.
*
* @par Description
* This function converts an UTF8 structure to a Wide char structure.
*
* @param[in] utf8Str The UTF8 structure to be converted [N/A]
* @param[out] *outStr Pointer to the structure in which the Wide char string output is stored [N/A]
*
* @retval SEC_INT Upon successful conversion [0|N/A]
* @retval SEC_INT In case conversion failed [Less than zero|N/A]
* @retval SEC_INT In case of memory allocation failure [Less than zero|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cvtUTF8towchar(SEC_CHAR *utf8Str, SEC_WCHAR **outStr);

/**
* @defgroup SEC_cvtWchar2UTF8
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_cvtWchar2UTF8(SEC_WCHAR *inStr, SEC_CHAR **utf8Str);
* @endcode
*
* @par Purpose
* To convert SEC_WCHAR to an UTF8.
*
* @par Description
* This function is used to convert Wide char structure to UTF8.
*
* @param[in] inStr The Wide char structure to be converted [N/A]
* @param[out] *utf8Str Pointer to the structure in which the UTF8 output is stored [N/A]
*
* @retval SEC_INT Upon successful conversion [0|N/A]
* @retval SEC_INT In case conversion failed [Less than zero|N/A]
* @retval SEC_INT In case of memory allocation failure [Less than zero|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_cvtWchar2UTF8(SEC_WCHAR *inStr, SEC_CHAR **utf8Str);

/**
* @defgroup SEC_isValidUTF8String
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT SEC_isValidUTF8String(SEC_UTF8String_S* octs);
* @endcode
*
* @par Purpose
* To check whether the given String is a valid UTF-8 string or not.
*
* @par Description
* This function is used to check whether an UTF8String is valid or not.
*
* @param[in] octs Input UTF8 string [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT If the UTF8 string is valid [TRUE|N/A]
* @retval SEC_INT If the UTF8 string is invalid [FALSE|N/A]
* @retval SEC_INT If the input is NULL [FALSE|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT SEC_isValidUTF8String(SEC_UTF8String_S* octs);

/**
* @defgroup SEC_freeVisibleString
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* void SEC_freeVisibleString (SEC_VisibleString_S *pstVisibleStr);
* @endcode
*
* @par Purpose
* To free a SEC_VisibleString_S structure
*
* @par Description
* This function frees a Visible String structure.
*
* @param[in] pstVisibleStr The structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void This function does not return any value. [N/A|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL void SEC_freeVisibleString (SEC_VisibleString_S *pstVisibleStr);

/**
* @defgroup SEC_setPrivateOID
* @ingroup asn_utilFunctions
* @par Prototype
* @code
* SEC_INT32 SEC_setPrivateOID(SEC_PRV_OID_INFO_S aPvtOIDInfo[], SEC_UINT32 uiCount);
* @endcode
*
* @par Purpose
* To set the private OID information which will be used in X509 certificates
*
* @par Description
* This function sets the private OID information which will be used in X509 certificates.
*
* @param[in] aPvtOIDInfo The array of SEC_PRV_OID_INFO_S structures that has private OID data [N/A]
* @param[in] uiCount The number of items in aPvtOIDInfo array [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 Invalid arguments passed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 Invalid OID type code [SEC_ERR_INVALID_PRV_OID_TYPE_CODE|N/A]
* @retval SEC_INT32 Invalid octal OID string or octal OID length [SEC_ERR_INVALID_OID|N/A]
* @retval SEC_INT32 Invalid long or short OID name length [SEC_ERR_INVALID_PRV_OID_NAME_LENGTH|N/A]
* @retval SEC_INT32 Duplicate OID entry found [SEC_ERR_DUPLICATE_PRV_OID|N/A]
* @retval SEC_INT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* asn-util.h
*
* @par Note
*
* 1. Support for Private OIDs is provided only for 'Subject Name' and 'Issuer Name' fileds of the X.509 Certificates.
* 2. Memory is allocated dynamically for the Private OID Table. It is not freed explicitly,
* but reclaimed automatically when application exit.
* 3. This API & its related structures are enabled for only for CSC & CGP PDT on specific requirement. Users are not 
* allowed to use this API with out contacting the VPP support team. If used, it leads to unresolved symbols.
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_INT32 SEC_setPrivateOID(SEC_PRV_OID_INFO_S aPvtOIDInfo[], SEC_UINT32 uiCount);

#ifdef __cplusplus
}
#endif

#endif // _IPSI_ASN_UTIL_H


