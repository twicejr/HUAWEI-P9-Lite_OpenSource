
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */




#ifndef _INCLUDE_IMESSAGEHANDLER_H
#define _INCLUDE_IMESSAGEHANDLER_H


#ifdef __cplusplus

DECLARE_INTERFACE_(IMessageHandler, IUnknown) 
{
public :
    virtual VOS_VOID  COMP_CALL Process(struct MsgCB *pMsg) = 0 ;
    virtual struct MsgCB * COMP_CALL ProcessSynMsg(struct MsgCB  *pMsg) = 0;
    virtual struct MsgCB* COMP_CALL ProcessTaskSynMsg(struct MsgCB  *pMsg) = 0 ;
    	
};

#else

#undef THIS
#define THIS IMessageHandler * This

DECLARE_INTERFACE(IMessageHandler)
{
    IUNKNOWN_METHODS
    METHOD_(VOS_VOID, Process)(THIS, struct MsgCB * pMsg );
    METHOD_(struct MsgCB*, ProcessSynMsg)(THIS, struct MsgCB* pMsg);
    METHOD_(struct MsgCB*, ProcessTaskSynMsg)(THIS, struct MsgCB* pMsg);
};


#define IMESSAGEHANDLER_METHODS  \
    IUNKNOWN_METHODS            \
    METHOD_(VOS_VOID, Process)(THIS, struct MsgCB * pMsg );  \
    METHOD_(struct MsgCB*, ProcessSynMsg)(THIS, struct MsgCB * pMsg);   \
    METHOD_(struct MsgCB*, ProcessTaskSynMsg)(THIS, struct MsgCB * pMsg);
    
#endif /* __cplusplus */

#define IID_IMESSAGEHANDLER    0x748429F8
    
#endif   /* _INCLUDE_IMESSAGEHANDLER_H */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

