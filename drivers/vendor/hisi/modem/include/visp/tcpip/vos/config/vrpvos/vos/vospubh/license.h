/**********************************************************************
 *
 *                          license.h
 *                       2003/3/29 by lwj
 *
 **********************************************************************/

#ifndef _LICENSE_H
#define _LICENSE_H

#ifdef __cplusplus
extern "C"{
#endif

#include "vos/vospubh/paf.h"

#define LCS_ON                                  PAF_ON
#define LCS_OFF                                 PAF_OFF

#define LICENSE_ERROR_NO_FILE                   100
#define LICENSE_ERROR_RESOURCE_NOT_FOUND        101
#define LICENSE_ERROR_SERVICE_NOT_FOUND         102
#define LICENSE_ERROR_LICENSE_FILE_ERROR        103
#define LICENSE_ERROR_TOO_MANY_CALL_BACK_FUNC   104
#define LICENSE_ERROR_PAF_ERROR                 105
#define LICENSE_ERROR_RESOURCE_VALUE_TOO_LARGE  106
#define LICENSE_ERROR_RESOURCE_VALUE_TOO_SMALL  107
#define LICENSE_ERROR_RESOURCE_PAF_NOT_PERMITTED 108  
#define LICENSE_ERROR_SERVICE_PAF_NOT_PERMITTED 109  
#define LICENSE_ERROR_NO_MEM                    110

#define LICENSE_BUFF_LEN                        10240  /* max license file length is 10K */
#define LICENSE_UPDATE_CALL_BACK_FUNC_SUM       256    /* max call back function application module register */

/*define license cli help info index*/
enum LICENSE_HELP_KEY
{
    LCS_HLP_LICENSE,
    LCS_HLP_ALL,
    LCS_HLP_RESOURCE,
    LCS_HLP_SERVICE,
    LCS_HLP_NAME,
    LCS_HLP_UPDATE,
    LCS_HLP_SYN
};

typedef VOID(*LCS_UPDATE_CALLBACK)();

ULONG LCS_GetResource( CHAR * pchResourceName, ULONG * pulValue );
ULONG LCS_GetService( CHAR * pchServiceName, ULONG * pulValue );
ULONG LCS_RegUpdateCallback( LCS_UPDATE_CALLBACK pfCallback );
VOID  LCS_SetLicenseFileName( CHAR* FileName );
ULONG LCS_PreInit();



/* license cmo */
#define VOS_TBL_LICENSE                         0x01
#define CMO_VOS_LICENSE_DISPLAY_ALL             CFG_CMO_DEF(MID_LICENSE, VOS_TBL_LICENSE, 1)
#define CMO_VOS_LICENSE_DISPLAY_RESOURCE        CFG_CMO_DEF(MID_LICENSE, VOS_TBL_LICENSE, 2)
#define CMO_VOS_LICENSE_DISPLAY_SERVICE         CFG_CMO_DEF(MID_LICENSE, VOS_TBL_LICENSE, 3)
#define CMO_VOS_LICENSE_DISPLAY_NAME            CFG_CMO_DEF(MID_LICENSE, VOS_TBL_LICENSE, 4)
#define CMO_VOS_LICENSE_UPDATE                  CFG_CMO_DEF(MID_LICENSE, VOS_TBL_LICENSE, 5)
#define CMO_VOS_LICENSE_SYN                     CFG_CMO_DEF(MID_LICENSE, VOS_TBL_LICENSE, 6)

#ifdef __cplusplus
}
#endif


#endif

