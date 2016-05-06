#ifndef NSR_INSR_INCLUDED
#define NSR_INSR_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

DECLARE_INTERFACE (IIF_COMP_NSR_ComIntFUN)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfNSR_Common_AddModule)(NSR_SUB_MODULE_RESIST *pstSubModuleRegist);
    METHOD_(ULONG, pfNSR_Common_ReceiveControlMsg)(NSR_COMMON_MSG *pstNSRCommonMsg);
    METHOD_(ULONG, pfNSR_Common_GetNSRBaseInfo)(UCHAR ucType, UCHAR *pucData);
};

DECLARE_INTERFACE (IIF_COMP_NSR_ComIntCFG)
{
    IUNKNOWN_METHODS
};

DECLARE_INTERFACE (IIF_COMP_NSR_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagNSR_IntObj
{
    struct IIF_COMP_NSR_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_NSR_ComIntCFG    *pCompIntCFG;
    struct IIF_COMP_NSR_ComIntSSA    *pCompIntSSA;
}NSR_INT_OBJ_S;

extern struct ComponentInfo m_CompNSRInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

