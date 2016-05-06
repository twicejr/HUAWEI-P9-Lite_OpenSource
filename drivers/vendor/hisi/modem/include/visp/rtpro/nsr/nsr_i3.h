#ifndef NSR_I3_INCLUDED
#define NSR_I3_INCLUDED

#define NSR_NOTIFY_I3_ALL_IF_READY    1

typedef struct nsr_notify_i3_data
{
    UCHAR ucMsgType;
    VOID *pMsgInfo;
}NSR_NOTIFY_I3_DTAT;

/*全局变量声明区*/
extern NSR_I3_DATA g_stNSRI3Data;

ULONG i3_receive_nsr_ospf_notify(VOID* pData);
VOID i3_nsr_statistic_if_notify(VOID *pData);
ULONG i3_nsr_ospf_msg_send(UCHAR ucMsgType, VOID *pMsgData);


#endif

