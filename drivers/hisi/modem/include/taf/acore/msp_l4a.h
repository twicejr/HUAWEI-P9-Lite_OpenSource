
#ifndef __MSP_L4A_H__
#define __MSP_L4A_H__

#include "vos.h"


extern VOS_UINT32 OSA_PostMessageToMsp(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);




/* 发送消息给PS,该函数不阻塞，能立即返回。*/
/* ulParam1/2可以为指针.*/
extern VOS_UINT32 OSM_PostMessageToPs(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

#endif