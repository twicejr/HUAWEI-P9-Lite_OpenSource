/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsafe_hashtable_api.h
*
*  Project Code: DOPRA VISP V200R003C01 NAT
*  Module Name: Hash/Frag/Iterator tables
*  Date Created: 2010
*  Author: Eswar
*   Description: Contain Hash/Frag/Iterator table return values
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2010-6-28    Eswar 72335         Initial version
*
*******************************************************************************/

#ifndef _IPSAFE_HASHTABLE_API_H_
#define _IPSAFE_HASHTABLE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*Return codes of Iterator module*/
/**
* @defgroup enumFWCommonIteratorReturnCode ITERATOR_RETURN_CODE
* @ingroup BLE Black List Enums
* @par Prototype
* @code
* typedef enum enumFWCommonIteratorReturnCode
* {
*     FWCOMMON_ITERATOR_ITEM_NOT_EXIST = 2,
*     FWCOMMON_ITERATOR_ITEM_EXIST = 3,
* } FWCOMMON_ITERATOR_RETURN_CODE;
* @endcode 
* 
* @par Description
* This enum consists of iterator return values.
*
* @datastruct FWCOMMON_ITERATOR_ITEM_NOT_EXIST=2 Indicates entry does not exists in list.
* @datastruct FWCOMMON_ITERATOR_ITEM_EXIST=3 Indicates entry exists in list.
*/
typedef enum enumFWCommonIteratorReturnCode
{
    FWCOMMON_ITERATOR_ITEM_NOT_EXIST = 2,
    FWCOMMON_ITERATOR_ITEM_EXIST = 3,
} FWCOMMON_ITERATOR_RETURN_CODE;

/*define hash table return code*/
/**
* @defgroup enumFWCommonHashTableReturnCode HASH_TABLE_RETURN_CODE
* @ingroup BLE Black List Enums
* @par Prototype
* @code
* typedef enum enumFWCommonHashTableReturnCode
* {
*     FWCOMMON_HASH_TABLE_ITEM_FULL = 1,
*     FWCOMMON_HASH_TABLE_ITEM_NOT_EXIST,
*     FWCOMMON_HASH_TABLE_ITEM_EXIST = 3,
* } FWCOMMON_HASH_TABLE_RETURN_CODE;
* @endcode 
* 
* @par Description
* This enum consists of hash table return values.
*
* @datastruct FWCOMMON_HASH_TABLE_ITEM_FULL=1 Indicates maximum entries reached in hash.
* @datastruct FWCOMMON_HASH_TABLE_ITEM_NOT_EXIST Indicates entry does not exist in hash.
* @datastruct FWCOMMON_HASH_TABLE_ITEM_EXIST=3 Indicates entry exists in hash.
*/
typedef enum enumFWCommonHashTableReturnCode
{
    FWCOMMON_HASH_TABLE_ITEM_FULL = 1,
    FWCOMMON_HASH_TABLE_ITEM_NOT_EXIST,
    FWCOMMON_HASH_TABLE_ITEM_EXIST = 3,
} FWCOMMON_HASH_TABLE_RETURN_CODE;

/*define the hash table alg module error code*/
/**
* @defgroup enumFWCommonHashTableErrCode HASH_TABLE_ERR_CODE
* @ingroup BLE Black List Enums
* @par Prototype
* @code
* typedef enum enumFWCommonHashTableErrCode
* {
*     FWCOMMON_HASH_TABLE_OK = FWIPSAFE_OK,
*     FWCOMMON_HASH_TABLE_ERR_MALLOC_COMMON_HASH_TABLE = FWIPSAFE_HASH_BEGIN_RET_CODE + 400 +1 ,
*     FWCOMMON_HASH_TABLE_ERR_MALLOC_HASH_TABLE,
*     FWCOMMON_HASH_TABLE_ERR_MALLOC_POOL_TABLE,
*     FWCOMMON_HASH_TABLE_ERR_MALLOC_SPINLOCK_ARRAY,
*     FWCOMMON_HASA_TABLE_ERR_ADD_NAMEDB,
*     FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_INSERT,
*     FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_SEARCH,
*     FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_DELETE,
*     FWCOMMON_HASH_TABLE_ERR_PARAMETERS,
*     FWCOMMON_HASH_TABLE_ERR_INSERT_HANDLE_TYPE,
*     FWCOMMON_HASH_TABLE_ERR_CREATE_SPINLOCK_INIT,
*     FWCOMMON_HASH_TABLE_ERR_GETNEXT_NULLINPUT,
*     FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_GETNEXT,
*     FWCOMMON_FLOOD_HASH_TABLE_ERR_HASH_ALG_ID_SEARCH,
*     FWCOMMON_FLOOD_HASH_TABLE_ERR_HASH_ALG_ID_INSERT
* } FWCOMMON_HASH_TABLE_ERR_CODE_E;
* @endcode 
* 
* @par Description
* This enum consists of hash table error values.
*
* @datastruct FWCOMMON_HASH_TABLE_OK=1 Indicates Hash operation success.
* @datastruct FWCOMMON_HASH_TABLE_ERR_MALLOC_COMMON_HASH_TABLE Indicates malloc failure for hashtable structure.
* @datastruct FWCOMMON_HASH_TABLE_ERR_MALLOC_HASH_TABLE Indicates malloc failure for hashtable entries.
* @datastruct FWCOMMON_HASH_TABLE_ERR_MALLOC_POOL_TABLE Indicates malloc failure for pool in hashtable.
* @datastruct FWCOMMON_HASH_TABLE_ERR_MALLOC_SPINLOCK_ARRAY Indicates malloc failure for spinlocks in hashtable..
* @datastruct FWCOMMON_HASA_TABLE_ERR_ADD_NAMEDB Indicates failed to register hash table name in DB.
* @datastruct FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_INSERT Indicates failed to insert the item in hash.
* @datastruct FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_SEARCH Indicates failed to search the item in hash.
* @datastruct FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_DELETE Indicates failed to delete the item from hash
* @datastruct FWCOMMON_HASH_TABLE_ERR_PARAMETERS Indicates recieved invalid parameters to initialize hash list.
* @datastruct FWCOMMON_HASH_TABLE_ERR_INSERT_HANDLE_TYPE Indicates recieved invalid option to insert an item into hash.
* @datastruct FWCOMMON_HASH_TABLE_ERR_CREATE_SPINLOCK_INIT Indicates failed to create spinlocks for hash.
* @datastruct FWCOMMON_HASH_TABLE_ERR_GETNEXT_NULLINPUT Indicates recieved null pointer to get next entry from hash.
* @datastruct FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_GETNEXT Indicates failed to get next entry from hash.
* @datastruct FWCOMMON_FLOOD_HASH_TABLE_ERR_HASH_ALG_ID_SEARCH Indicates failed to search the flood item in hash.
* @datastruct FWCOMMON_FLOOD_HASH_TABLE_ERR_HASH_ALG_ID_INSERT Indicates failed to insert the flood item in hash.
*/
typedef enum enumFWCommonHashTableErrCode
{
    FWCOMMON_HASH_TABLE_OK = FWIPSAFE_OK,
    FWCOMMON_HASH_TABLE_ERR_MALLOC_COMMON_HASH_TABLE = FWIPSAFE_HASH_BEGIN_RET_CODE + 400 +1 ,
    FWCOMMON_HASH_TABLE_ERR_MALLOC_HASH_TABLE,
    FWCOMMON_HASH_TABLE_ERR_MALLOC_POOL_TABLE,
    FWCOMMON_HASH_TABLE_ERR_MALLOC_SPINLOCK_ARRAY,
    FWCOMMON_HASA_TABLE_ERR_ADD_NAMEDB,
    FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_INSERT,
    FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_SEARCH,
    FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_DELETE,
    FWCOMMON_HASH_TABLE_ERR_PARAMETERS,
    FWCOMMON_HASH_TABLE_ERR_INSERT_HANDLE_TYPE,
    FWCOMMON_HASH_TABLE_ERR_CREATE_SPINLOCK_INIT,
    FWCOMMON_HASH_TABLE_ERR_GETNEXT_NULLINPUT,
    FWCOMMON_HASH_TABLE_ERR_HASH_ALG_ID_GETNEXT,
    FWCOMMON_FLOOD_HASH_TABLE_ERR_HASH_ALG_ID_SEARCH,
    FWCOMMON_FLOOD_HASH_TABLE_ERR_HASH_ALG_ID_INSERT
} FWCOMMON_HASH_TABLE_ERR_CODE_E;


/**
* @defgroup FWCOMMON_PubFragTableTimeOutHandleCB FWCOMMON_PubFragTableTimeOutHandleCB
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_PubFragTableTimeOutHandleCB(VOID* pvApplicationFragTable);
* @endcode 
* 
* @par Description
* This functions is used to handle fragment table timeout,it traverse the given 
* fragment table and delete item that timeout.
* 
* @param[in] pApplicationHashTable Pointer to fragtable for which timeout has to be checked. []
* @param[out]   []
* 
* @retval UINT32 Timeout items deleted succesfully. [FWCOMMON_HASH_TABLE_OK|]
*
* @par Dependency
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
*/ 
extern UINT32 FWCOMMON_PubFragTableTimeOutHandleCB(VOID* pvApplicationFragTable);

/**
* @defgroup FWCOMMON_HashTableTimeOutHandle FWCOMMON_HashTableTimeOutHandle
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_HashTableTimeOutHandle(VOID* pApplicationHashTable);
* @endcode 
* 
* @par Description
* This functions is used to handle hash table timeout,it traverse the given 
* hash table and delete item that timeout.
* 
* @param[in] pApplicationHashTable Pointer to hashtable for which timeout has to be checked. []
* @param[out]   []
* 
* @retval UINT32 Timeout items deleted succesfully. [FWCOMMON_HASH_TABLE_OK|]
*
* @par Dependency
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
*/ 
extern UINT32 FWCOMMON_HashTableTimeOutHandle(VOID* pApplicationHashTable);


#ifdef  __cplusplus
}
#endif

#endif /*_IPSAFE_HASHTABLE_API_H_*/


