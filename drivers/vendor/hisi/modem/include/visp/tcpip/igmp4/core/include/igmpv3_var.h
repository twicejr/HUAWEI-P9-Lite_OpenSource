
#ifndef _IGMPV3_VAR_H_
#define _IGMPV3_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* 发送IGMP报文时必须在IP头带路由告警选项，该选项值是恒定的，在初始化时组装好 */
extern MBUF_S *g_pstIgmpRouterAlertOpt;

/*定时器队列头指针*/
extern IgmpTimerNode_S *g_pstIgmpTimer;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IGMPV3_VAR_H_ */

