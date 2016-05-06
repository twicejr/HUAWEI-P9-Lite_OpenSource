/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Fw_acl_sh.h
*
*  Project Code: VISPV1R6C02
*   Module Name:   
*  Date Created: 2007-07-31
*        Author: luogaowei61496
*   Description: 
*   Version:      1
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   luogaowei61496          Create
*  2008-09-10   liangjicheng          V1R7C02 同步V1R7C01  
*   1 函数增加参数(2)
*       extern ULONG ACL_ClassifyInMBufByNumber(MBUF_S *pMBuf, ULONG ulGroupNum, ULONG ulIgnore);
*       extern ULONG ACL_GetFlowOfFirstRule(ULONG ulListNumber, ACL_Item *pstFlow, ULONG *pulDscp);
*******************************************************************************/
#ifndef _FW_ACL_SH_H_
#define _FW_ACL_SH_H_

#ifdef  __cplusplus
extern "C"{
#endif



    
#include "security/acl/include/fw_acl_common.h"

/*Begin 2008-09-10 V1R7C02 同步V1R7C01*/
/*extern ULONG ACL_GetFlowOfFirstRule(ULONG ulListNumber, ACL_Item *pstFlow, ULONG *pulDscp);*/

/*End    2008-09-10 V1R7C02 同步V1R7C01*/

/* Added by z43740 for: ACL变化时对外通知,2008/03/12 */
/**
* @defgroup ACL_RefreshAclRegister ACL_RefreshAclRegister
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_RefreshAclRegister(PF_ACLREFRESHCALLBACK pfFunc, ULONG ulModId);
* @endcode 
* 
* @par Description
* This function is used to register a callback function for ACL changes. If user registers
* any call back function, that function is called for all changes in ACL configuration.
* 
* @param[in] pfFunc The call back function to be registered []
* @param[in] ulModId ACL module number []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Function pointer is empty [Help_ACL_NULL_POINTER|]
* @retval ULONG The same module is already registered callback function [Help_ACL_CALLBACK_EXIST|]
* @retval ULONG Memory allocation failure [Help_ACL_MallocError|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_RefreshAclRegister(PF_ACLREFRESHCALLBACK pfFunc, ULONG ulModId);

/**
* @defgroup ACL_ClearUpdateCallBack ACL_ClearUpdateCallBack
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ClearUpdateCallBack();
* @endcode 
* 
* @par Description
* ACL_RefreshAclRegister does not have corresponding Memory Free function. 
* This function is invoked by legacy VRP APIs like VRPAdapt_ACL_RefreshAclRegister.
* 
* @param[in]   []
* @param[out]   []
*
* @retval  [|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern  VOID ACL_ClearUpdateCallBack(VOID);

/* End of Additon by z43740,2008/03/12 */

/**
* @defgroup ACL_GetIfNameByIffIndex ACL_GetIfNameByIffIndex
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetIfNameByIffIndex(ULONG ulIfIndex, CHAR * pszIfName);
* @endcode 
* 
* @par Description
* This function is used to convert input interface index to string.
* 
* @param[in] ulIfIndex Interface index. The length of the interface should 
* be between 1 and 47 []
* @param[out] pszIfName Interface index as string. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Failed to get interface name [Help_ACL_ERR_GETIFINDEX|]
* @retval ULONG Interface name exceeded maximum length [Help_ACL_ERR_GETIFINDEX_NAMELEN|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetIfNameByIffIndex(ULONG ulIfIndex, CHAR * pszIfName);

/**
* @defgroup ACLFW_Init ACLFW_Init
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_Init(ULONG ulRegPri);
* @endcode 
* 
* @par Description
* This function is used to hook ACL filter function for packet processing. By default, it 
* hooks the ACL inbound functions in the protocol stack.
* 
* @param[in] ulRegPri Priority of hooking function. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Failed to hook filtering function [ACLFW_ERR_PROTOCOL_STACK_HOOK|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACLFW_Init(ULONG ulRegPri);

/**
* @defgroup ACL_OUT_IpIFAclToString ACL_OUT_IpIFAclToString
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* LONG ACL_OUT_IpIFAclToString(CHAR * szOut, ACL_RULE_INFO_OUT_S *pRuleInfo);
* @endcode 
* 
* @par Description
* This function is used to convert an interface based ACL to an ASCII string command.
* 
* @param[in] pRuleInfo The ACL rule that needs to be converted into ASCII string. []
* @param[out] szOut The converted ACL command as ASCII string. []
*
* @retval LONG The number of characters in converted ACL command string. [|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
LONG ACL_OUT_IpIFAclToString(CHAR * szOut, INT32 i32BufLen, ACL_RULE_INFO_OUT_S *pRuleInfo);

/**
* @defgroup ACLFW_InboundFilter ACLFW_InboundFilter
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_InboundFilter(VOID *pMBuf);
* @endcode 
* 
* @par Description
* Process the inbound message for ACL in IP layer.
* 
* @param[in] pMBuf Pointer to MBUF_S structure. []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been process by ACL. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACLFW_OutboundFilter
*
*/ 
extern ULONG ACLFW_InboundFilter(VOID *pMBuf);

/**
* @defgroup ACLFW_OutboundFilter ACLFW_OutboundFilter
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_OutboundFilter(VOID *pMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the outbound message for ACL in IP layer.
* 
* @param[in] pMBuf Pointer to MBUF_S structure. []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been process by ACL. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACLFW_InboundFilter
*
*/ 
extern ULONG ACLFW_OutboundFilter(VOID *pMBuf);

/**
* @defgroup ACLFW_MacOutboundFilter ACLFW_MacOutboundFilter
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_MacOutboundFilter(VOID *pMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the inbound message for ACL in MAC layer.
* 
* @param[in] pMBuf Pointer to MBUF_S structure. []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been process by ACL. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACLFW_MacInboundFilter
*
*/ 
extern ULONG ACLFW_MacOutboundFilter(VOID *pMBuf);

/**
* @defgroup ACLFW_MacInboundFilter ACLFW_MacInboundFilter
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_MacInboundFilter(VOID *pMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the outbound message for ACL in MAC layer.
* 
* @param[in] pMBuf Pointer to MBUF_S structure. []
* 
* @retval ULONG Fill Description [Fill_Revturn_Value|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACLFW_MacOutboundFilter
*
*/ 
extern ULONG ACLFW_MacInboundFilter(VOID *pMBuf);


/* 为支持IR匹配支持DSCP值而增加的接口 */
/*extern BOOL_T ACL_MatchACLItemWithDSCP (ULONG ulACLNumber, ACL_Item * pstFlow, UCHAR ucDSCP);*/
/**
* @defgroup ACL_ClassifyMBufByItemWithDSCP ACL_ClassifyMBufByItemWithDSCP
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T ACL_ClassifyMBufByItemWithDSCP(VOID *pstMBuf, ACL_Item *pstFlow, UCHAR ucDSCP);
* @endcode 
* 
* @par Description
* To determine if a packet (MBUF) matches a five-tuple flow and DSCP values.
* 
* @param[in] pstMBuf MBUF pointer (message) []
* @param[in] pstFlow Quintuple stream pointer []
* @param[in] ucDSCP DSCP value. []
*
* @retval BOOL_T Packet (MBUF) match a five-tuple flow and DSCP values [BOOL_TRUE|]
* @retval BOOL_T Packet (MBUF) does not match a five-tuple flow and DSCP values [BOOL_FALSE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern BOOL_T ACL_ClassifyMBufByItemWithDSCP(VOID *pstMBuf, ACL_Item *pstFlow, UCHAR ucDSCP);

/*Firewall wrapper function to get the interface index from name*/
/**
* @defgroup FW_GetIfIndexByFullName FW_GetIfIndexByFullName
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG FW_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);
* @endcode 
* 
* @par Description
* This function gets interface index for a given interface full name.
* 
* @param[in] pszIfName Interface name for which interface index is required. []
* @param[out] pulIfIndex Interface index []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Error depends on adapter function [|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG FW_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);

/**
* @defgroup ACL_GetVrfIndexByName ACL_GetVrfIndexByName
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetVrfIndexByName(CHAR * pszVrfName, ULONG * pulVrfIndex);
* @endcode 
* 
* @par Description
* This function gets VRF index for a given VRF name.
* 
* @param[in] pszVrfName It is VRF index name for which VRF index is required. []
* @param[out] pulVrfIndex VRF Index. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates failed to get VRF index [Help_ACL_ERR_GETVRFINDEX|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetVrfIndexByName(CHAR * pszVrfName, ULONG * pulVrfIndex);

/**
* @defgroup ACL_GetVrfNameByVrfIndex ACL_GetVrfNameByVrfIndex
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetVrfNameByVrfIndex(ULONG ulVrfIndex, CHAR * pszVrfName);
* @endcode 
* 
* @par Description
* This function gets VRF name for a given VRF index.
* 
* @param[in] ulVrfIndex VRF index for which VRF Index name is required []
* @param[out] pszVrfName VRF Index name. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Failed to get VRF index name [Help_ACL_ERR_GETVRFINDEX|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetVrfNameByVrfIndex(ULONG ulVrfIndex, CHAR * pszVrfName);

/**
* @defgroup ACL_GetVrfIndexByIfIndex ACL_GetVrfIndexByIfIndex
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetVrfIndexByIfIndex(ULONG ulIfIndex, ULONG * pulVrfIndex);
* @endcode 
* 
* @par Description
* This function gets VRF Index for the given interface index.
* 
* @param[in] ulIfIndex Interface index for which VRF index is required []
* @param[out] pulVrfIndex VRF Index []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Failed to get VRF index [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetVrfIndexByIfIndex(ULONG ulIfIndex, ULONG * pulVrfIndex);



/**
* @defgroup ACLFW_GetCfgByIf ACLFW_GetCfgByIf
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetCfgByIf(CHAR *pucIfName, ACLFW_SHOWCFG_S *pstShowCfg);
* @endcode 
* 
* @par Description
* This function gets the configuration information of ACLFW by interface name.
* 
* @param[in] pucIfName Interface name for which configuration is required. []
* @param[out] pstShowCfg Configuration for that interface. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer [ACLFW_ERR_NULL|]
* @retval ULONG Indicates received wrong interface name [ACLFW_ERR_PARA|]
* @retval ULONG Indicates initialization is not done. [ACLFW_ERR_SFE_GETCFGBYIF_INIT|]
* @retval ULONG Indicates failed to get configuration for given interface. [ACLFW_ERR_NONODE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern  ULONG   ACLFW_GetCfgByIf(CHAR *pucIfName, ACLFW_SHOWCFG_S *pstShowCfg);


/**
* @defgroup ACLFW_SecPolicy_Close ACLFW_SecPolicy_Close
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_SecPolicy_Close(ULONG ulHandle);
* @endcode 
* 
* @par Description
* This function releases the handle of ACLFW configure table. 
* 
* @param[in] ulHandle Handle for ACLFW's configuration table. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer handle [ACLFW_ERR_NULL|]
* @retval ULONG Indicates failed to close ACLFW's configuration table. [ACLFW_ERR_IF_TABLE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACLFW_SecPolicy_Close(ULONG ulHandle);

/**
* @defgroup ACLFW_SecPolicy_Open ACLFW_SecPolicy_Open
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_SecPolicy_Open(ULONG *pulHandle, ACLFW_SHOWFILTER_S *pstFilter);
* @endcode 
* 
* @par Description
* This function opens ACLFW configuration table and provides handle. 
* 
* @param[in] pstFilter Filter for ACLFW's configuration table []
* @param[out] pulHandle Handle for ACLFW's configuration table []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer input [ACLFW_ERR_NULL|]
* @retval ULONG Indicates failed to open ACLFW's configuration table [ACLFW_ERR_IF_TABLE|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACLFW_SecPolicy_Open(ULONG *pulHandle, ACLFW_SHOWFILTER_S *pstFilter);

/**
* @defgroup ACLFW_SecPolicy_GetFirst ACLFW_SecPolicy_GetFirst
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_SecPolicy_GetFirst(ULONG ulHandle, ACLFW_SHOWCFG_S *pstShowObj);
* @endcode 
* 
* @par Description
* This function is used to get first entry from ACLFW configuration list.
* 
* @param[in] ulHandle handle for ACLFW's configuration table. []
* @param[out] pstShowObj Pointer to a structure in which ACLFW's first entry has to be copied. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [ACLFW_ERR_NULL|]
* @retval ULONG Indicates there is no entry in configuration table. [ACLFW_ERR_NONODE|]
* @retval ULONG Indicates failed to get first entry from ACLFW's configuration table [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* The behavior of ACLFW_SecPolicy_GetFirst and ACLFW_SecPolicy_GetNext is same.
* ACLFW_SecPolicy_GetFirst function usage is deprecated. 
* Instead, use ACLFW_SecPolicy_GetNext.
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACLFW_SecPolicy_GetFirst(ULONG ulHandle, ACLFW_SHOWCFG_S *pstShowObj);

/**
* @defgroup ACLFW_SecPolicy_GetNext ACLFW_SecPolicy_GetNext
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_SecPolicy_GetNext(ULONG ulHandle, ACLFW_SHOWCFG_S *pstShowObj);
* @endcode 
* 
* @par Description
* This function is used to get next entry from ACLFW configuration list.
* 
* @param[in] ulHandle Handle for configuration table of ACLFW []
* @param[out] pstShowObj Pointer to a structure in which next entry of ACLFW has to be copied []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [ACLFW_ERR_NULL|]
* @retval ULONG Indicates reached end of the configuration table [ACLFW_ERR_END_TABLE|]
* @retval ULONG Indicates there is no entry in configuration table [ACLFW_ERR_NONODE|]
* @retval ULONG Indicates failed to get next entry from configuration table of ACLFW [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* The behavior of ACLFW_SecPolicy_GetFirst and ACLFW_SecPolicy_GetNext is same.
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACLFW_SecPolicy_GetNext(ULONG ulHandle, ACLFW_SHOWCFG_S *pstShowObj);

/**
* @defgroup ACLFW_ShowSecPolicy ACLFW_ShowSecPolicy
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowSecPolicy(CHAR *pszIfName);
* @endcode 
* 
* @par Description
* This function shows ACLFW configuration.
* 
* @param[in] pszIfName Interface name for which configuration needs to be shown []
* @param[out]   []
*
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* If the interface name is NULL, ACLFW_ShowSecPolicy displays all the security policies configured.
* 
* 
* @par Related Topics
* None
*
*/ 
extern VOID ACLFW_ShowSecPolicy(CHAR *pszIfName);

/*End C02NEWR-ACL liangjicheng 2008-10-24*/

/**
* @defgroup ACL_GetNextACLInfo ACL_GetNextACLInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetNextACLInfo(ULONG ulACLInfoHandle, ULONG ulGroupNum, ACL_RULE_INFO_OUT_S* pstACLInfo);
* @endcode 
* 
* @par Description
* This function is used to get next rule from ACL configuration.
* 
* @param[in] ulACLInfoHandle Handle for ACL configuration table. []
* @param[in] ulGroupNum ACL group number from which ACL rules needed. []
* @param[out] pstACLInfo Pointer to ACL_RULE_INFO_OUT_S structure in which ACL rule data to be copied. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_NULL_POINTER|]
* @retval ULONG Indicates given group number does not match with the group number given in handle [Help_ACL_ERR|]
* @retval ULONG Indicates given group number does not exist [Help_ACL_Not_Exist|]
* @retval ULONG Indicates failed to get next rule from the list [Help_ACL_WAITLIST_GetFail|]
* @retval ULONG Indicates reached end of the rules list [Help_ACL_END|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetNextACLInfo(ULONG ulACLInfoHandle, ULONG ulGroupNum, ACL_RULE_INFO_OUT_S* pstACLInfo);

/**
* @defgroup ACL_OpenACLInfoTable ACL_OpenACLInfoTable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_OpenACLInfoTable(ULONG* pulACLInfoHandle, ULONG ulGroupNum, ACL_FILTER_S* pstACLFilter);
* @endcode 
* 
* @par Description
* This function opens ACL rule information table.
* 
* @param[in] ulGroupNum ACL group number for which rules information is required. []
* @param[in] pstACLFilter Filter for ACL rules configuration table. []
* @param[out] pulACLInfoHandle Pointer to handle for ACL configuration table. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_NULL_POINTER|]
* @retval ULONG Indicates given group number does not exist [Help_ACL_Not_Exist|]
* @retval ULONG Indicates reached end of the rules list [Help_ACL_END|]
* @retval ULONG Indicates failed to open ACL rules list [Help_ACL_WAITLIST_OpenFail|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_OpenACLInfoTable(ULONG* pulACLInfoHandle, ULONG ulGroupNum, ACL_FILTER_S* pstACLFilter);

/**
* @defgroup ACL_CloseACLInfoTable ACL_CloseACLInfoTable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CloseACLInfoTable(ULONG ulACLInfoHandle);
* @endcode 
* 
* @par Description
* This function closes ACL rule information table.
* 
* @param[in] ulACLInfoHandle Handle for ACL configuration table. []
* @param[out]   []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_ERR|]
* @retval ULONG Indicates failed to close ACL rules list [Help_ACL_WAITLIST_CloseFail|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_CloseACLInfoTable(ULONG ulACLInfoHandle);


/**
* @defgroup ACL_SH_ClassifyByIfInfo ACL_SH_ClassifyByIfInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_SH_ClassifyByIfInfo(VOID *pstMbuf, 
*                               ULONG ulIfType, 
*                               ULONG ulGroupNum, 
*                               ULONG *pulRuleIndex, 
*                               BOOL_T *pbLog);
* @endcode 
* 
* @par Description
* This function matches packets based on interface configuration.
* 
* @param[in] pstMbuf Pointer to MBUF message []
* @param[in] ulIfType The interface type. It can have the following values:
*    - IPDEBUG_IFIN  - inbound
*    - IPDEBUG_IFOUT - outbound
*    - IPDEBUG_IFANY - either one
*    - IPDEBUG_IFALL - both [IPDEBUG_IFIN-IPDEBUG_IFALL]
* @param[in] ulGroupNum ACL group number in which rules needs to be checked. []
* @param[out] pbLog Which says whether any rule is matched for given packet or not. []
* @param[out] pulRuleIndex Index of the matched rule for given packet. []
*
* @retval ULONG ACL says PERMIT the packet [ACL_PERMIT|]
* @retval ULONG ACL says DENY the packet [ACL_DENY|]
* @retval ULONG ACL says no rule matched for the packet [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* If the ulIfType is IPDEBUG_IFIN, the function checks ACL for inbound interface only. \n
* \n 
* If the ulIfType is IPDEBUG_IFOUT, the function checks ACL for outbound interface only. \n
* \n 
* The priority of match for IPDEBUG_IFANY is ACL_PERMIT > ACL_DENY > ACL_NOTFOUND: \n
* 1. If the interfaces (inbound and outbound) match for permit, the return value is ACL_PERMIT. \n
* 2. If there is no permit matching results, check if any one of the two matches ACL_DENY. If any one is ACL_DENY, then return value is ACL_DENY. \n
* 3. If the interfaces (inbound and outbound) match to ACL_NOTFOUND, then return value is ACL_NOTFOUND. \n
* \n 
* The sequence of calling for IPDEBUG_IFALL is as follows: \n
* 1. If ACL match on interfaces (inbound and outbound) are Permit, then the return value is ACL_PERMIT. \n
* 2. If ACL match on interfaces (inbound and outbound) are Deny, then the return value is ACL_DENY. \n
* 3. In all other cases, the return value is ACL_NOTFOUND. \n
* 
* 
* @par Related Topics
* ACL_ClassifyByIfInfo
*/ 
extern ULONG ACL_SH_ClassifyByIfInfo(VOID *pstMbuf,ULONG ulIfType, 
    ULONG ulGroupNum, ULONG *pulRuleIndex, BOOL_T *pbLog);



/*Begin C02NEWR-ACL liangjicheng 2008-10-24*/

/**
* @defgroup ACL_GetNextGroupInfo ACL_GetNextGroupInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetNextGroupInfo(ULONG ulAclWaitListHandle,ACL_GROUP_INFO_S* pstGroupInfo);
* @endcode 
* 
* @par Description
* This function is used to get next group from ACL configuration.
* 
* @param[in] ulAclWaitListHandle Handle for ACL group list. []
* @param[out] pstGroupInfo Pointer to structure in which group information needs to be copied. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_NULL_POINTER|]
* @retval ULONG Indicates failed to get next group from ACL configuration list [Help_ACL_WAITLIST_GetFail|]
* @retval ULONG Indicates reached end of ACL configuration list [Help_ACL_END|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetNextGroupInfo(ULONG ulAclWaitListHandle,ACL_GROUP_INFO_S* pstGroupInfo);

/**
* @defgroup ACL_OpenGroupInfoTable ACL_OpenGroupInfoTable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_OpenGroupInfoTable(ULONG* pulAclWaitListHandle,
*                              ACL_GROUP_FILTER_S *pstGroupFilter);
* @endcode 
* 
* @par Description
* This function is used to open ACL group configuration list.
* 
* @param[in] pstGroupFilter Filter for ACL group configuration list. []
*
* @param[out] ulAclWaitListHandle Handle for ACL group configuration list
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG  Indicates received null pointer as input [Help_ACL_NULL_POINTER|]
* @retval ULONG  Indicates there is no entry in ACL group configuration list. [Help_ACL_END|]
* @retval ULONG  Indicates failed to open ACL group configuration list. [Help_ACL_WAITLIST_OpenFail|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
*  If pstGroupFilter passed as NULL, all the group information will be returned.
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_OpenGroupInfoTable(ULONG* pulAclWaitListHandle,
                            ACL_GROUP_FILTER_S *pstGroupFilter);

/**
* @defgroup ACL_CloseGroupInfoTable ACL_CloseGroupInfoTable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CloseGroupInfoTable(ULONG ulAclWaitListHandle);
* @endcode 
* 
* @par Description
* This function is used to close ACL group configuration list.
* 
* @param[in] ulAclWaitListHandle Handle for ACL group configuration list. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_NULL_POINTER|]
* @retval ULONG Indicates failed to close  ACL group configuration list [Help_ACL_WAITLIST_CloseFail|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_CloseGroupInfoTable(ULONG ulAclWaitListHandle);


/**
* @defgroup ACL_Rule_OpenList ACL_Rule_OpenList
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_Rule_OpenList(ULONG ulGroupNum, ULONG *pulAclWaitListHandle);
* @endcode 
* 
* @par Description
* This function opens ACL rule information table. 
* 
* @param[in] ulGroupNum ACL group number for which rules information is required. []
* @param[out] pulAclWaitListHandle Handle for ACL rule configuration list. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_ERR|]
* @retval ULONG Indicates received invalid group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates received group does not exist [Help_ACL_Not_Exist|]
* @retval ULONG Indicates there is no entry in the configuration list [Help_ACL_END|]
* @retval ULONG Indicates failed to open ACL rules list [Help_ACL_WAITLIST_OpenFail|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_Rule_OpenList(ULONG ulGroupNum, ULONG *pulAclWaitListHandle);


/**
* @defgroup ACL_GetFirstRuleInfo ACL_GetFirstRuleInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetFirstRuleInfo(ULONG ulGroupNum, 
*                            ULONG ulAclWaitListHandle, 
*                            ACL_RULE_INFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function gets first entry from ACL rule information table. 
* 
* @param[in] ulGroupNum ACL group number for which rules information is required. []
* @param[in] ulAclWaitListHandle Handle for ACL rule configuration list. []
* @param[out] pstRuleInfo Pointer to ACL_RULE_INFO_S structure in which ACL rule data to be copied. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_ERR|]
* @retval ULONG Indicates content info is null in received pstRuleInfo structure [Help_ACL_CONTENT_NULL|]
* @retval ULONG Indicates received invalid group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates received group does not exist [Help_ACL_Not_Exist|]
* @retval ULONG Indicates failed to get first entry from ACL rules list  [Help_ACL_WAITLIST_SetFail|]
* @retval ULONG Indicates there is no entry in the configuration list [Help_ACL_END|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetFirstRuleInfo(ULONG ulGroupNum, ULONG ulAclWaitListHandle, ACL_RULE_INFO_S *pstRuleInfo);

/**
* @defgroup ACL_GetNextRuleInfo ACL_GetNextRuleInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetNextRuleInfo(ULONG ulGroupNum, 
*                           ULONG ulAclWaitListHandle, 
*                           ACL_RULE_INFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function gets next entry from ACL rule information table. 
* 
* @param[in] ulGroupNum ACL group number for which rules information is required. []
* @param[in] ulAclWaitListHandle Handle for ACL rule configuration list. []
* @param[out] pstRuleInfo Pointer to ACL_RULE_INFO_S structure in which ACL rule data to be copied. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_ERR|]
* @retval ULONG Indicates content info is null in received pstRuleInfo structure [Help_ACL_CONTENT_NULL|]
* @retval ULONG Indicates received invalid group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates received group does not exist [Help_ACL_Not_Exist|]
* @retval ULONG Indicates failed to get next entry from ACL rules list  [Help_ACL_WAITLIST_GetFail|]
* @retval ULONG Indicates there is no entry in the configuration list [Help_ACL_END|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_GetNextRuleInfo(ULONG ulGroupNum, ULONG ulAclWaitListHandle, ACL_RULE_INFO_S *pstRuleInfo);

/**
* @defgroup ACL_Rule_CloseList ACL_Rule_CloseList
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_Rule_CloseList(ULONG ulAclWaitListHandle);
* @endcode 
* 
* @par Description
* This function closes ACL rule information table. 
* 
* @param[in] ulAclWaitListHandle Handle for ACL rule configuration list. []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates received null pointer as input [Help_ACL_ERR|]
* @retval ULONG Indicates failed to close ACL rule configuration list [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_Rule_CloseList(ULONG ulAclWaitListHandle);


/**
* @defgroup ACL_SH_Init ACL_SH_Init
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_SH_Init();
* @endcode 
* 
* @par Description
* This function performs ACL initialization and assigns callback functions for PPI and packet filtering.
* 
* @param[in]   []
* @param[out]   []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG ACL already initialized [Help_ACL_INIT_ERR|]
* @retval ULONG g_pstSemForACL_share malloc error [Help_ACL_ACC_SEMSHARE_MallocError|]
* @retval ULONG Failed to register lock [Help_ACL_ERR_CreateSm|]
* @retval ULONG Failed to add semaphore shared variable to name DB [Help_ACL_ERR_SEMAPHORE_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pstAccACL_share global variable [Help_ACL_ACC_SHARE_MallocError|]
* @retval ULONG Failed to add g_pstAccACL_share shared variable to name DB [Help_ACL_ERR_ACC_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pulAclGroupNumSum_share global variable [Help_ACL_ACLGROUPNUMSUM_SHARE_MallocError|]
* @retval ULONG Failed to add g_pulAclGroupNumSum_share shared variable to name DB [Help_ACL_ERR_ACLGROUPNUMSUM_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pbFM_share global variable [Help_ACL_FM_SHARE_MallocError|]
* @retval ULONG Failed to add g_pbFM_share shared variable to name DB [Help_ACL_ERR_FM_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pstACL_share global variable [Help_ACL_GLOBALSTRUCT_SHARE_MallocError|]
* @retval ULONG Failed to malloc basic rule type [Help_ACL_TYPE_BASIC_MallocErr|]
* @retval ULONG Failed to malloc basic acl group [Help_ACL_GROUP_BASIC_MallocErr|]
* @retval ULONG Failed to malloc advance rule type [Help_ACL_TYPE_ADV_MallocErr|]
* @retval ULONG Failed to malloc advance acl group [Help_ACL_GROUP_ADV_MallocErr|]
* @retval ULONG Failed to malloc interface based rule type [Help_ACL_TYPE_IF_MallocErr|]
* @retval ULONG Failed to malloc interface based acl group [Help_ACL_GROUP_IF_MallocErr|]
* @retval ULONG Failed to malloc mac based rule type [Help_ACL_TYPE_MAC_MallocErr|]
* @retval ULONG Failed to malloc mac based acl group [Help_ACL_GROUP_MAC_MallocErr|]
* @retval ULONG Failed to add g_pstACL_share shared variable to name DB [Help_ACL_ERR_ACLGLOBALSTRUCT_ADDNAMEDB|]
* @retval ULONG Failed to initialize statistics component [Help_ACL_ACL_STAT_INIT|]
* @retval ULONG Failed to malloc aclfw debug switch [ACLFW_ERR_INIT_DBG_SWITCH_MALLOC|]
* @retval ULONG Failed to add aclfw debug switch to name DB [ACLFW_ERR_SFE_INIT_DBG_SWITCH_ADDNAMEDB|]
* @retval ULONG Failed to initialize hash table [ACLFW_ERR_HASH_INIT|]
* @retval ULONG Failed to add g_pstACLFWDB_share shared variable to name DB  [ACLFW_ERR_INIT_CFGDB_ADDNAMEDB|]
* @retval ULONG Failed to malloc statistics timer [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_MALLOC|]
* @retval ULONG Failed to add statistics timer shared variable to name DB [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_DBADD|]
* @retval ULONG Failed to create statistics timer [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_CREATE|]
* @retval ULONG Failed to initialize statistics timer [ACLFW_ERR_INIT_STAT_TIMER|]
* @retval ULONG Failed to initialize common Init module [Help_ACL_IPSAFE_INIT_FAIL|]
* 
* @par Dependency
* fw_acl_sh.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*
*/ 
extern ULONG ACL_SH_Init(VOID);


/**
* @defgroup ACL_CreateDelACLBasicRule ACL_CreateDelACLBasicRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CreateDelACLBasicRule(ACL_BASIC_RULE_S* psAcl_BasicRule);
* @endcode 
* 
* @par Description
* This function creates or deletes basic ACL rule.
* 
* @param[in] psAcl_BasicRule Pointer to the basic rule ACL structure. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments / memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates error in operation type [Help_ACL_NotSupportOperType|]
* @retval ULONG Indicates error in getting VRFIndex [Help_ACL_ERR_GETVRFINDEX|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates internal arguments are null pointers [ACLFW_ERR_NULL|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT|] 
* @retval ULONG No configuration entry founds[ACLFW_ERR_END_TABLE|]
* @retval ULONG Failed to register the handle [ACLFW_ERR_IF_TABLE|]
* @retval ULONG Indicates NULL argument [ACLFW_ERR_NULL|]
* @retval ULONG Indicates failure to open ACL interface configuration [ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates error in VRF operation type [Help_ACL_ActionError|]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ManageBasicRule
*	- ACL_ManageAdvanceRule
*	- ACL_ManageIfBasedRule
*	- ACL_ManageExtMacRule
*	- ACL_ManageUserRule
*	- ACL_DeleteNode
*	- ACL_CreateDelACLAdvRule
*
*/ 
extern ULONG ACL_CreateDelACLBasicRule(ACL_BASIC_RULE_S* psAcl_BasicRule);


/**
* @defgroup ACL_CreateDelACLAdvRule ACL_CreateDelACLAdvRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CreateDelACLAdvRule(ACL_ADV_RULE_S* psAcl_AdvRule);
* @endcode 
* 
* @par Description
* This function creates or deletes advanced ACL rule.
* 
* @param[in] psAcl_AdvRule Pointer to the advanced ACL rule structure. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments / memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates error in operation type [Help_ACL_NotSupportOperType|]
* @retval ULONG Indicates error in getting VRFIndex [Help_ACL_ERR_GETVRFINDEX|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates internal arguments are null pointers [ACLFW_ERR_NULL|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT|] 
* @retval ULONG No configuration entry founds[ACLFW_ERR_END_TABLE|]
* @retval ULONG Failed to register the handle [ACLFW_ERR_IF_TABLE|]
* @retval ULONG Indicates NULL argument [ACLFW_ERR_NULL|]
* @retval ULONG Indicates failure to open ACL interface configuration [ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates error in VRF operation type [Help_ACL_ActionError|]
* 
* @par Dependency
* fw_acl_common.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ManageBasicRule
*	- ACL_ManageAdvanceRule
*	- ACL_ManageIfBasedRule
*	- ACL_ManageExtMacRule
*	- ACL_ManageUserRule
*	- ACL_DeleteNode
*	- ACL_CreateDelACLBasicRule
*
*/ 
extern ULONG ACL_CreateDelACLAdvRule(ACL_ADV_RULE_S* psAcl_AdvRule);

/**
* @defgroup ACLFW_CFG_SecurityPolicy ACLFW_CFG_SecurityPolicy
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_CFG_SecurityPolicy(ACLFW_CFG_S* pstFWCfg);
* @endcode 
* 
* @par Description
* This function is used to add or delete the interface index of the system with ACL group for ACL packet classification.
* User can configure ACL group with interface index for MAC packets and for IP packets for both Inbound and Outbound direction. 
* This function finds the interface index based on interface name given by user, if interface index is not found, this function coverts 
* the interface name into integer and use that number as an interface index. 
* This function overwrites the previous configuration for the same interface, if available.
* User can configure the maximum ACLFW_MAXNODE interface index.
*
* @param[in] pstFWCfg Pointer to configuration structure []
* @param[out]   []
* 
* @retval ULONG On Success [ACLFW_OK|]
* @retval ULONG User calls delete for interface index which is not configured [ACLFW_ERR_NONODE|]
* @retval ULONG Input pointer is null [ACLFW_ERR_NULL|]
* @retval ULONG Interface name length is 0 [ACLFW_ERR_PARA|]
* @retval ULONG Failed to find the interface index for given interface name. Or failed to convert
          interface name in to integer value[ACLFW_ERR_IFNAME|]
* @retval ULONG ulFlag contains value other than ACLFW_CFG_ADD or ACLFW_CFG_DEL [ACLFW_ERR_PARA|]
* @retval ULONG ulDirection contains value other than 
          ACLFW_FITLERTYPE_IN/ACLFW_FITLERTYPE_OUT/ACLFW_FITLERTYPE_MACIN/ACLFW_FITLERTYPE_MACOUT [ACLFW_ERR_IFNAME|]
* @retval ULONG ulGroup is not valid. ulGroup in not in the range of ACL_ADV_MAX_EXT/ACL_BAS_MIN_EXT for ulDirection ACLFW_FITLERTYPE_IN/ACLFW_FITLERTYPE_OUT 
          ulGroup is not in the range of ACL_EXTMAC_MAX_EXT/ACL_EXTMAC_MIN_EXT fro ulDirection ACLFW_FITLERTYPE_MACIN/ACLFW_FITLERTYPE_MACOUT[ACLFW_ERR_PARA|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_CFGSECPOLICY_INIT|]
* @retval ULONG Internal configuration error occurs [ACLFW_ERR_SFE_ACLFW_CFG_SECPOLICY_CONFIG|]
* @retval ULONG PPI callback error occurs [ACLFW_ERR_PPI_CFG|]
*
* @par Dependency
* None
* 
* 
* @par Note
* \n
* 
* Only Basic, Advanced and Extended MAC Groups can be used with the function ACLFW_CFG_SecurityPolicy.
* 
* 
* @par Related Topics
*	- ACLFW_GetCfgByIf
*	- ACLFW_ShowSecPolicy
*/
extern ULONG ACLFW_CFG_SecurityPolicy(ACLFW_CFG_S* pstFWCfg);

/**
* @defgroup ACLFW_ShowCfgByIf ACLFW_ShowCfgByIf
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowCfgByIf(CHAR *pucIfName);
* @endcode 
* 
* @par Description
* This function is used to show the interface configuration for the given interface name.
* 
* @param[in] pszIfName Null terminated interface name []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* None
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_CFG_SecurityPolicy
*	- ACLFW_GetCfgByIf
*	- ACLFW_ShowSecPolicy
*/
extern VOID ACLFW_ShowCfgByIf(CHAR *pucIfName);

/**
* @defgroup ACL_ShowGroup ACL_ShowGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowGroup(ULONG ulGroupNum, ULONG ulISAll, ULONG ulRuleNumber);
* @endcode 
* 
* @par Description 
* This function is used to display specific or all ACL Rule information in a group. 
* 
* @param[in] ulGroupNum ACL group number []
* @param[in] ulISAll This parameter can take the following values:
*	- 1 - All rule information for the input group will be displayed.
*	- 0 - Information of the specified rule will be displayed. []
* @param[in] ulRuleNumber ACL Rule number []
* @param[out]   [] 
* 
* @retval VOID This function do not return any value. [|]
* 
* @par Dependency
* None
* 
* 
* @par Note
* \n
* 
* This function does not display user defined group information.
* 
* 
* @par Related Topics
* None
*/ 
extern VOID ACL_ShowGroup(ULONG ulGroupNum, ULONG ulISAll, ULONG ulRuleNumber);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */

