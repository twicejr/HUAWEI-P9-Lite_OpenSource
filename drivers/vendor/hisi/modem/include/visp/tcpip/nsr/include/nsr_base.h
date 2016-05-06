#ifndef NSR_BASE_INCLUDED
#define NSR_BASE_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* NSR 事件位定义 */
#define NSR_EVENT_CONTROL           0X00000001      /* NSR控制类事件 */
#define NSR_EVENT_BAKRCV            0X00000002      /* 备份消息接收事件 */
#define NSR_EVENT_BAKSND            0X00000004      /* 备份消息发送事件 */
#define NSR_EVENT_OSPF_CONTROL     0X00000008      /* OSPF NSR控制类事件 */
#define NSR_EVENT_COMMON_CONTROL   0X00000010      /* NSR COMMON控制类事件 */


/* 消息定义 */
#define NSR_MSG_NULL                0
#define NSR_MSG_CONTROL             1  /* NSR控制类消息 */
#define NSR_MSG_BAKRCV              2  /* 接收备份消息 */
#define NSR_MSG_BAKSND              3  /* 备用 */
#define NSR_MSG_OSPF_NSR_CONTROL   4  /* OSPF NSR控制类消息(OSPF模块同OSPF NSR交互) */
#define NSR_MSG_NSR_OSPF_CONTROL   5  /* NSR OSPF控制类消息(OSPF NSR内部消息消息交互)*/
#define NSR_MSG_COMMON              6  /* NSR 模块间消息 */
#define NSR_MSG_MAX                 7

/*备份状态*/
#define NSR_BACKUP_BATCH       1      /*批量备份*/
#define NSR_BACKUP_REALTIME    2      /*实时备份*/


#define NSR_ASSERT( exp )         VOS_DBGASSERT(exp)

/*NSR内存操作*/
#define NSR_MALLOC(ulMemInfo, ulMemSize)  TCPIP_Malloc(ulMemInfo, ulMemSize)  
#define NSR_FREE(pBuf)  TCPIP_Free(pBuf)

/* NSR队列写操作*/
extern ULONG g_ulNSRMsgQueID;
#define NSR_Enqueue(ulQueueId, ulMsg) \
                    VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0)

/* NSR队列读操作*/ 
#define NSR_Dequeue(ulQueueId, ulMsg) \
                     VOS_Que_Read (ulQueueId, ulMsg, VOS_NO_WAIT, 0)

/* NSR任务写事件 */
extern ULONG g_ulNSRTaskID;
#define NSR_SchedNSRTask(ulEvent) \
                    (VOID)VOS_Ev_Write( g_ulNSRTaskID, ulEvent )

extern ULONG g_ulNSRLock;
extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);

/*NSR任务锁的操作*/
#define NSR_INIT_LOCK()       (0 == TCPIP_CreateMutex("NSR_Mutex", &g_ulNSRLock))
#define NSR_GET_LOCK()        (VOID)TCPIP_BEGIN_PT(g_ulNSRLock)
#define NSR_RELEASE_LOCK()    (VOID)TCPIP_END_PT(g_ulNSRLock)
#define NSR_DESTROY_LOCK()    (0 == TCPIP_DeleteMutex(g_ulNSRLock))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

