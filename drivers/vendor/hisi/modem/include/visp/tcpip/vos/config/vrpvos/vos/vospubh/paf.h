/**********************************************************************
 *
 *                             paf.h
 *                       2003/3/29 by lwj
 *
 **********************************************************************
 *  Modification History
 *  DATE        NAME             DESCRIPTION    
 *  -------------------------------------------------------------------
 *  2008-02-04  f54882           For A82D23227 
 **********************************************************************/

#ifndef _PAF_H
#define _PAF_H

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */



#define PAF_ON                                  1
#define PAF_OFF                                 0
#define PAF_CONTROLLABLE                        1
#define PAF_NOTCONTROLLABLE                     0

#define PAF_ERROR_NO_FILE                       100
#define PAF_ERROR_RESOURCE_NOT_FOUND            101
#define PAF_ERROR_SERVICE_NOT_FOUND             102
#define PAF_ERROR_PAF_FILE_ERROR                103
#define PAF_ERROR_PAF_PARAMETER_ERROR           104

#define     CONTROLLED_BY_PAF       PAF_NOTCONTROLLABLE
#define     CONTROLLED_BY_PAF_LCS   PAF_CONTROLLABLE
#define     FUNCTION_AVAILABLE      PAF_ON
#define     FUNCTION_UNAVAILABLE    PAF_OFF

/* Modified by X36317, 将MAX_PAF_LCS_KEY_LEN从64改为67，以解决ARM CPU 4字节对齐问题, A82D02016, 2006/6/7 */
#define MAX_PAF_LCS_KEY_LEN 67

/*used for paf and license resource specs.*/
typedef struct tagSPECS_RES_VALUE
{
    CHAR  chKey[MAX_PAF_LCS_KEY_LEN + 1];
    ULONG ulControllable; /*resource is controllable by license , or not controllable*/
    ULONG ulMax_Value;
    ULONG ulMin_Value;
    ULONG ulAvail_Value;  /*When get paf value from paf file ulAvail_Value is identical 
                            to default value*/
}SPECS_RES_VALUE_S; 

/*used for paf and license resource specs.*/
typedef struct tagSPECS_FUN_VALUE
{
    CHAR chKey[MAX_PAF_LCS_KEY_LEN + 1];
    ULONG ulControllable; /*Service is controllable by license , or not controllable*/
    ULONG ulAvail_Value; /*0 Unavailable, 1: Available */
}SPECS_FUN_VALUE_S; 

/*define configure item for vrpv5 system or products*/
typedef struct tagSPECS_CFG_VALUE
{
    CHAR chKey[MAX_PAF_LCS_KEY_LEN + 1]; /*Name for configure item in our system*/
    ULONG ulCfg_Value;                   /*Configure value defined and explained by app user*/
}SPECS_CFG_VALUE_S; 

/*define cli help info index*/
enum PAF_HELP_KEY
{
    PAF_HLP_PAF,
    PAF_HLP_ALL,
    PAF_HLP_RESOURCE,
    PAF_HLP_SERVICE,
    PAF_HLP_NAME,
    PAF_HLP_UPDATE,
    PAF_HLP_SYN
};
/*Output paf api*/

/*Called by system when intialized*/
ULONG PAF_PreInit();
ULONG PAF_Init();
VOID  PAF_SetPafFileName(CHAR * FileName );
/*Used by application module*/
ULONG PAF_GetResource(SPECS_RES_VALUE_S *pResValue );
ULONG PAF_GetService(SPECS_FUN_VALUE_S *pServiceFunValue );
ULONG PAF_GetCfgItem(SPECS_CFG_VALUE_S *pCfgItemValue );


/* paf cmo */
#define VOS_TBL_PAF                     0x01
#define CMO_VOS_PAF_DISPLAY_ALL         CFG_CMO_DEF(MID_PAF, VOS_TBL_PAF, 1)
#define CMO_VOS_PAF_DISPLAY_RESOURCE    CFG_CMO_DEF(MID_PAF, VOS_TBL_PAF, 2)
#define CMO_VOS_PAF_DISPLAY_SERVICE     CFG_CMO_DEF(MID_PAF, VOS_TBL_PAF, 3)
#define CMO_VOS_PAF_DISPLAY_NAME        CFG_CMO_DEF(MID_PAF, VOS_TBL_PAF, 4)
#define CMO_VOS_PAF_UPDATE              CFG_CMO_DEF(MID_PAF, VOS_TBL_PAF, 5)
#define CMO_VOS_PAF_SYN                 CFG_CMO_DEF(MID_PAF, VOS_TBL_PAF, 6)



#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */


#endif /*_PAF_H*/

