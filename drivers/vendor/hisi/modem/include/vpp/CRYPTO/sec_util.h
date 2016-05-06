/******************************************************************************
                                                                              *
               Copyright 2003, Huawei Technologies Co. Ltd.                   *
                           ALL RIGHTS RESERVED                                *
                                                                              *
Project Code:         iPsi  
Filename:sec_util.h
Version:
Module Name:          Crypto Module                                           *
Date Created:         15-07-2005                                              *
Author:               Sanjay Vasudevan                                        *
Descrption:           Contains various crypto utility functions               *
Modification History*
DATE              NAME                        DESCRIPTION                     *
--------------------------------------------------------------------------    *
  YYYY-MM-DD                                                                  *
   2007-09-18     Jayant Bansal 72052         Cleanup                         *
                                                                              *
******************************************************************************/


#ifndef SEC_UTIL_H
#define SEC_UTIL_H

#include "sec_sys.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This is Version 1 Release 5 of Crypto lib */
#define CRYPTO_VERSION "VPP V300R003C22SPC200" 

/** @defgroup sec_common
* This section contains the sec_common Functions and Enums
*/

/** @defgroup sec_utilEnum
* @ingroup sec_util
* This section contains the sec_common Enum
*/

/**
* @defgroup SEC_CRYPTO_TYPE_E
* @ingroup Enums
* @par Description
* Indicates the type of crypto implementaion type.
* @par Prototype
* @code
* typedef enum
* {
* 	SEC_SOFTWARE = 0,
* 	SEC_OCTEON,
* 	SEC_MAX
* } SEC_CRYPTO_TYPE_E;
*
* @endcode
*
* @datastruct SEC_SOFTWARE=0 Software implemenation type.
* @datastruct SEC_OCTEON Octeon hardware implementation type.
*/
typedef enum
{
    SEC_SOFTWARE = 0,
    SEC_OCTEON,
    SEC_MAX
}SEC_CRYPTO_TYPE_E;


/* This data structure is defined for API's future extensibility */
/**
* @defgroup IPSI_AUX_PAR_S
* @ingroup Structures
* @par Description
* This data structure is defined for API's future extensibility.
* @par Prototype
* @code
* typedef struct stAuxPar
* {
*     SEC_UINT32 ulId;
*     SEC_VOID *pData;
* }IPSI_AUX_PAR_S;
* @endcode
*
* @datastruct ulId ID or value related to feature.
* @datastruct pData Byte stream of data.
*
*/
typedef struct stAuxPar
{
    SEC_UINT32 ulId;
    SEC_VOID *pData;
}IPSI_AUX_PAR_S;





/** @defgroup sec_util
* This section contains the sec_util Functions.
*/


/** @defgroup sec_utilFunctions
* @ingroup sec_util
* This section contains the sec_util Functions.
*/



/*
    Func Name:  SEC_getCryptoVersion
*/

/**
* @defgroup SEC_getCryptoVersion  
* @ingroup sec_utilFunctions	
* @par Prototype
* @code
* SEC_CHAR* SEC_getCryptoVersion();
* @endcode
*
* @par Purpose
* This is used to get crypto library version.
*
* @par Description
* SEC_getCryptoVersion function returns the text which specifies the version of crypto library being used.
*
* @par Parameters
* N/A
*
* @retval SEC_CHAR* The version of Crypto library [1.3|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_CHAR* SEC_getCryptoVersion(SEC_VOID);

/*
    Func Name:  SEC_displayCryptoVersion
*/

/**
* @defgroup  SEC_displayCryptoVersion  
* @ingroup sec_utilFunctions
* @par Prototype
* @code
* SEC_VOID SEC_displayCryptoVersion();
* @endcode
*
* @par Purpose
* This is used to print crypto library version.
*
* @par Description
* SEC_displayCryptoVersion function prints the text which specifies the version of crypto library being used.
*
* @par Parameters
* N/A
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* \n
* This function internally uses printf to print the Crypto Version to the console. Users are advised NOT to
* use this function in C++ based adapter codes as it may have a conflict with std::cout.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID SEC_displayCryptoVersion(SEC_VOID);

/*
    Func Name:  SEC_setDebugSwitch
*/

/**
* @defgroup SEC_setDebugSwitch 
* @ingroup  sec_utilFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setDebugSwitch (SEC_UINT32 ulSecDebugSwitch);
* @endcode
*
* @par Purpose
* This is used to set the debug level for crypto library.
*
* @par Description
* The user can set the debug level for crypto library using SEC_setDebugSwitch function. Calling this function with
* SEC_DEBUG_ON, enables logging of messages which are of type debug, warning, error and fatal. Calling this function
* with SEC_DEBUG_OFF disables debug and warning messages and only errors and fatal messages are logged.
*
* @param[in] ulSecDebugSwitch The debug switch [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID SEC_setDebugSwitch (SEC_UINT32 ulSecDebugSwitch);

/*
    Func Name:  SEC_getDebugSwitch
*/

/**
* @defgroup SEC_getDebugSwitch 
* @ingroup  sec_utilFunctions
* @par Prototype
* @code
* SEC_UINT32 SEC_getDebugSwitch();
* @endcode
*
* @par Purpose
* This is used to get the debug level for crypto library.
*
* @par Description
* SEC_getDebugSwitch function returns the debug level that has been set currently. The function returns SEC_DEBUG_ON
* or SEC_DEBUG_OFF.
*
* @par Parameters
* N/A
*
* @retval SEC_UINT32 The debug level [1|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 SEC_getDebugSwitch(SEC_VOID);

/*
    Func Name:  SEC_showDebugSwitch
*/

/**
* @defgroup  SEC_showDebugSwitch  
* @ingroup  sec_utilFunctions
* @par Prototype
* @code
* SEC_VOID SEC_showDebugSwitch();
* @endcode
*
* @par Purpose
* This is used to display whether debug level is ON or OFF.
*
* @par Description
* SEC_showDebugSwitch function displays a text which specifies if the debug level has been set or reset. If debugging
* is set, "Debug Switch is ON" is displayed else "Debug Switch is OFF" is displayed.
*
* @par Parameters
* N/A
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* \n
* This function internally uses printf to print the Debug Switch Status to the console. 
* Users are advised NOT to use this function in C++ based adapter codes as it may 
* have a conflict with std::cout.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID SEC_showDebugSwitch(SEC_VOID);




/*
    Func Name:  SEC_setImplementationType
*/

/**
* @defgroup SEC_setImplementationType 
* @ingroup  sec_utilFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setImplementationType ( SEC_CRYPTO_TYPE_E eType);
* @endcode
*
* @par Purpose
* This is used to set the implementation type.
*
* @par Description
* SEC_setImplementationType sets the implementation type used for crypto
* operation. The Implementation type should be set in the beginning before
* using APIs of the Crypto/Other VPP Infra Libraries which use
* Crypto library. This API is not thread safe and cannot be used in multithread.
*
*
* @param[in] eType implementation type enum [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* 
* None
*
* @par Related Topics
* None
*/

CRYPTOLINKDLL SEC_VOID SEC_setImplementationType (SEC_CRYPTO_TYPE_E eType);

/*
    Func Name:  SEC_getImplementationType
*/

/**
* @defgroup SEC_getImplementationType 
* @ingroup  sec_utilFunctions
* @par Prototype
* @code
* SEC_CRYPTO_TYPE_E SEC_getImplementationType();
* @endcode
*
* @par Purpose
* This is used to get the crypto implementation type status for crypto library.
*
* @par Description
* SEC_getImplementationType function returns the implementation type used by
* the crypto library to perform different operations.
*
*
* @par Parameters
* None
*
* @retval SEC_CRYPTO_TYPE_E The crypto implementation type [0|N/A]
*
* @par Required Header File
* sec_util.h
*
* @par Note
* 
* None
*
* @par Related Topics
* None
*/

CRYPTOLINKDLL SEC_CRYPTO_TYPE_E SEC_getImplementationType(SEC_VOID);


#ifdef __cplusplus
}
#endif

#endif

