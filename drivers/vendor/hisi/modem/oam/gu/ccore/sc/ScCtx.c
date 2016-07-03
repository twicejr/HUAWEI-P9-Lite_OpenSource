

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ScCommCtx.h"
#include "ScCtx.h"
#include "ScApSec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_SC_CONTEXT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


SC_FAC_GLOBAL_STRU*  SC_CTX_GetFacGlobalVarAddr( VOS_VOID )
{
    return &SC_CTX_GetScCtxAddr()->stScFacGlobalVar;
}


VOS_VOID  SC_CTX_InitFacGlobalVar( VOS_VOID )
{
    SC_CTX_GetScCtxAddr()->stScFacGlobalVar.enScFacAuthStatus = SC_AUTH_STATUS_UNDO;

    /*lint -e534*/
    VOS_MemSet(SC_CTX_GetScCtxAddr()->stScFacGlobalVar.aucScFacRandData, 0, SC_RAND_DATA_LEN);
    /*lint +e534*/

    return;
}


SC_AUTH_STATUS_ENUM_UINT8  SC_CTX_GetFacAuthStatus( VOS_VOID )
{
    return SC_CTX_GetScCtxAddr()->stScFacGlobalVar.enScFacAuthStatus;
}


VOS_VOID  SC_CTX_SetFacAuthStatus( SC_AUTH_STATUS_ENUM_UINT8 enScAuthStatus )
{
    SC_CTX_GetScCtxAddr()->stScFacGlobalVar.enScFacAuthStatus = enScAuthStatus;

    return;
}


VOS_UINT8  SC_CTX_GetIdentifyStartFlg( VOS_VOID )
{
    return SC_CTX_GetScCtxAddr()->stScFacGlobalVar.ucIdentifyStartFlg;
}


VOS_VOID  SC_CTX_SetIdentifyStartFlg( VOS_UINT8 ucIdentifyStartFlg )
{
    SC_CTX_GetScCtxAddr()->stScFacGlobalVar.ucIdentifyStartFlg   = ucIdentifyStartFlg;

    return;
}


VOS_UINT8*  SC_CTX_GetFacRandDataAddr( VOS_VOID )
{
    return SC_CTX_GetScCtxAddr()->stScFacGlobalVar.aucScFacRandData;
}


VOS_UINT32*  SC_CTX_GetApSecInitStateAddr(VOS_VOID)
{
    return &SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ulInitState;
}


SC_APSEC_ITEM_STRU*  SC_CTX_GetApSecItemBaseAddr(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.astApSecItem;
}


VOS_UINT8 SC_CTX_GetSecATkeyFlg(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSecATkeyFlg;
}


VOS_VOID SC_CTX_SetSecATkeyFlg(VOS_UINT8 ucSecATkeyFlg)
{
    SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSecATkeyFlg  = ucSecATkeyFlg;
    return;
}


VOS_UINT8* SC_CTX_GetSecATkeyAddr(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.aucSecATkey;
}


VOS_UINT8 SC_CTX_GetApSecSeqID(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSeqID;
}


VOS_VOID SC_CTX_SetApSecSeqID(VOS_UINT8 ucSeqID)
{
    SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSeqID  = ucSeqID;
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

