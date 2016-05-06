

#ifndef __CNAS_HSM_TIMER_H__
#define __CNAS_HSM_TIMER_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
/* define the timer legnth for each timer ID */
#define TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF_LEN                         (335*1000)  /* this length is composed of access length(according to 1x:305s) and active length(30s) */


#define TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN                           (30*1000)


#define TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN                    (15*1000)

#define TI_CNAS_HSM_REVISE_WAIT_HRPD_CONN_CLOSE_IND_LEN             (1500)    /* 修正等待hrpd conn open ind定时器时长 */

#define TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND_LEN                     (30*1000)

#define TI_CNAS_HSM_WAIT_SCP_DEACTIVE_CNF_LEN                       (3*1000)

#define TI_CNAS_HSM_REVISE_WAIT_SCP_DEACTIVE_CNF_LEN                (1500)    /* 修正等待scp deactive cnf定时器时长 */

#define TI_CNAS_HSM_ADDRESS_TIMER_LEN                               (180*1000)
#define TI_CNAS_HSM_DEFAULT_UATI_SESSION_ACT_PROTECT_TIMER_LEN      (180*1000)

#define TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF_LEN                        (4*1000)
#define TI_CNAS_HSM_WAIT_CARD_READ_CNF_LEN                          (5*1000)

#define TI_CNAS_HSM_REVISE_WAIT_SNP_DATA_CNF_LEN                    (2*1000)    /* 修正等待SNP Data CNF定时器时长，power save/power off发送session close时使用 */

#define TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP_LEN                         (60*1000)

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

enum CNAS_HSM_TIMER_ID_ENUM
{
    TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF,
    TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF,
    TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF,
    TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF,
    TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF,
    TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF,
    TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF,
    TI_CNAS_HSM_WAIT_UATI_ASSIGN,
    TI_CNAS_HSM_ADDRESS_TIMER,
    TI_CNAS_HSM_KEEP_ALIVE_TIMER,
    TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
    TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND,
    TI_CNAS_HSM_WAIT_SCP_DEACTIVE_CNF,
    TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,    /* Session激活和重试的最大时间，如果超时，当前的激活流程结束之后，不再重试 */
    TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF,
    TI_CNAS_HSM_WAIT_CARD_READ_CNF,
    TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP,

    TI_CNAS_HSM_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_HSM_TIMER_ID_ENUM_UINT32;



/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/




/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasHsmMain.h */











