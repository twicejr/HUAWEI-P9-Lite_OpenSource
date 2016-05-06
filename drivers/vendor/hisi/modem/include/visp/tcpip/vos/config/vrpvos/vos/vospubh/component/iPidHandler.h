
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#ifndef _INCLUDE_IPIDHANDLER_H
#define _INCLUDE_IPIDHANDLER_H


#ifdef  __cplusplus
/********************************
 * The IUnknown interface lets clients get pointers to other interfaces on a 
 * given object through the QueryInterface method.
 * All other interfaces are inherited, directly or indirectly, from IUnknown. 
 * Therefore, the method QueryInterface in IUnknown is the first entries in the VTable 
 * for every interface. 
 * You must implement IUnknown as part of every interface. 
********************************/
DECLARE_INTERFACE_(IPIDHandler,IMessageHandler) 
{
public:
    /*************************
     * Returns a pointer to a specified interface on an object to which a client 
     * currently holds an interface pointer. 
     * This function must call AddRef on the pointer it returns. 
     *@param iid, a indentifier of the requested interface
     *@param ppvObj, Address of pointer variable that receives the interface 
     * pointer requested in riid. Upon successful return, *ppvObject contains 
     * the requested interface pointer to the object. 
     * If the object does not support the interface specified 
     * in iid, *ppvObject is set to NULL. 
     *@return VOS_OK if the interface is supported, VOS_ERR if not.
    *************************/
    
    virtual VOS_UINT32 COMP_CALL Init(VOS_UINT32 ulPhase) = 0 ;
    virtual VOS_PID COMP_CALL GetPID(VOS_VOID) = 0 ;
    virtual VOS_UINT32 COMP_CALL SetPID(VOS_PID pid) = 0 ;
    virtual VOS_UINT32 COMP_CALL Enable(VOS_VOID) = 0 ;
    virtual VOS_UINT32 COMP_CALL Disable(VOS_VOID) = 0 ;
};

#else

#undef THIS
#define THIS IPIDHandler * This


DECLARE_INTERFACE(IPIDHandler)
{
    IMESSAGEHANDLER_METHODS
    METHOD(Init)(THIS, VOS_UINT32 ulPhase);
    METHOD_(VOS_PID, GetPID)(THIS);
    METHOD(SetPID)(THIS, VOS_PID pid);
    METHOD(Enable)(THIS);
    METHOD(Disable)(THIS);
};


#define IPIDHANDLER_METHODS                \
    IMESSAGEHANDLER_METHODS;                 \
    METHOD(Init)(THIS, VOS_UINT32 ulPhase);  \
    METHOD_(VOS_PID, GetPID)(THIS);               \
    METHOD(SetPID)(THIS, VOS_PID pid);            \
    METHOD(Enable)(THIS);                     \
    METHOD(Disable)(THIS);                                                       


/* Expand this interface define :
struct IPIDHandler
{
    struct IPIDHandlerVtbl *lpVtbl ;
};

typedef struct IPIDHandler IPIDHandler ;
typedef IPIDHandler *PIPIDHandler ;
struct IPIDHandlerVtbl
{
    VOS_UINT32 ( *QueryInterface)(IUnknown *This , COMP_IID iid, void** ppvObj) ;
    VOS_VOID (*Process)(THIS, struct MsgCB * pMsg );
    struct MsgCB* (*ProcessSynMsg)(THIS, struct MsgCB * pMsg);
    struct MsgCB* (*ProcessTaskSynMsg)(THIS, struct MsgCB * pMsg);

    VOS_UINT32 (*Init)(THIS,VOS_UINT32 ulPhase):
    VOS_PID  (*GetPID)(THIS):
    VOS_UINT32 (*SetPID)(THIS, VOS_PID pid):
    VOS_UINT32 (*Enable)(THIS):
    VOS_UINT32 (*Disable)(THIS);
};
*/
#endif

#define IID_IPIDHANDLER    0x748429F7

#endif   /* _INCLUDE_IPIDHANDLER_H */



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

