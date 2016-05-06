

#ifndef __TAF_DRX_H__
#define __TAF_DRX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile                            
*****************************************************************************/
#include  "vos.h" 
#pragma   pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare 
*****************************************************************************/


/*****************************************************************************
  4 Enum 
*****************************************************************************/
/* drx fid enum */
#if(VOS_OS_VER == VOS_LINUX)
typedef enum
{
    DRX_DIAG_FW_VOTE = 0,   		/* diag fw */  
    DRX_DIAG_APP_AGENT_VOTE,		/* diag app agent */
    DRX_DIAG_LOG_SAVE_VOTE,
    DRX_TAF_VOTE_BUTT
}drx_taf_fid_vote_e;
#endif

#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_RTOSCK == VOS_OS_VER))
typedef enum
{
    DRX_DIAG_MODEM_AGENT_VOTE = 0,	/* diag modem agent */
    DRX_L4A_VOTE,					/* l4a */
    DRX_FTM_VOTE,					/* ftm */
    DRX_FTM_MAILBOX_VOTE,		/* ftm mailbox self task */
    DRX_TAF_VOTE_BUTT
}drx_taf_fid_vote_e;
#endif

/*****************************************************************************
   5 STRUCT 
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/* lock to vote sleep  */
extern VOS_VOID drx_taf_fid_vote_lock(drx_taf_fid_vote_e e_drx_vote);

/* unlock to vote sleep */
extern VOS_VOID drx_taf_fid_vote_unlock(drx_taf_fid_vote_e e_drx_vote);

extern VOS_VOID drx_taf_init(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










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

#endif /* end of diag_api.h */
