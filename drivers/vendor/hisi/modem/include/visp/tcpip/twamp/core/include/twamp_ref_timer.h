
#ifndef __TWAMP_REF_TIMER_H__
#define __TWAMP_REF_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*    Func Name: TWAMP_TimerInit
* Date Created: 2013-04-03
*       Author: m70989
*  Description: Twamp Timer Intialization
*        Input: ulTableSize , Timer Table Size
*                  pfTimerExpiry Timer Expiry function   
*       Output: 
*       Return: TWAMP_OK  on Success, Non Zero value on error.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-02-25      m70989       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_TimerInit(ULONG ulTableSize, TWAMP_TIMER_EXPIRY_FUN pfTimerExpiry);


/*******************************************************************************
*    Func Name: TWAMP_TimerAdd
* Date Created: 2013-04-03
*       Author: m70989
*  Description: Adding timer to the timer list
*        Input: VOID
*       Output: 
*       Return: TWAMP_OK  on Success, Non Zero value on error.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-02-25      m70989       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_TimerAdd(ULONG ulId, ULONG ulTimeOut, UINTPTR *pulTimerId);


/*******************************************************************************
*    Func Name: TWAMP_TimerDel
* Date Created: 2013-04-03
*       Author: m70989
*  Description: Deleting the timer from the timer list
*        Input: VOID
*       Output: 
*       Return: TWAMP_OK  on Success, Non Zero value on error.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-02-25      m70989       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_TimerDel(UINTPTR  ulTimerId);



extern VOID TWAMP_RefTimer(VOID *pArg);



extern ULONG TWAMP_ProcessTimer(VOID);


#ifdef __cplusplus
}
#endif

#endif /*__TWAMP_REF_TIMER_H__*/

