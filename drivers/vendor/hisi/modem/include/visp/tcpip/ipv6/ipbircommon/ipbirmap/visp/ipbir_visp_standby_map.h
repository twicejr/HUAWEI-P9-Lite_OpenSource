#ifndef _IPB_IR_VISP_STANDBY_MAP_H_
#define _IPB_IR_VISP_STANDBY_MAP_H_

#ifdef    __cplusplus
extern "C"{
#endif

ULONG IPBIR_PostStandbyEvent(ULONG ulTaskUd, ULONG ulEvent);

#define IPBIR_STANDBY_POST_EVENT(ulTaskId, ulEvent, ulRet) \
            ulRet = IPBIR_PostStandbyEvent(ulTaskId, ulEvent)

#define IPBIR_STANDBY_WAKEUP(ulEvent, ulMaxWait, ulRet) \
            {\
                ULONG ulEventRcv;\
                ulRet = VOS_Ev_Read( ulEvent, &ulEventRcv, VOS_WAIT, ulMaxWait );\
            }

#define IPBIR_STANDBY_EVENT(ulSelfTaskId, ulEvent, ulMaxWaitInMilliSecs) \
            {\
                ULONG ulRet;\
                \
                IPBIR_STANDBY_POST_EVENT(ulSelfTaskId, ulEvent, ulRet);\
                if (VOS_OK != ulRet)\
                {\
                    VOS_T_Delay(ulMaxWaitInMilliSecs);\
                }\
                else\
                {\
                    IPBIR_STANDBY_WAKEUP(ulEvent, ulMaxWaitInMilliSecs, ulRet);\
                }\
            }
#ifdef __cplusplus
}
#endif        /* end of __cplusplus */


#endif  /* end of _IPB_IR_VISP_STANDBY_MAP_H_ */


