
#ifndef __MSP_L4A_H__
#define __MSP_L4A_H__

#include "vos.h"

/*****************************************************************************
 函数名称: OSA_PostMessageToMsp
 功能描述: 协议栈调用该接口发送消息给MSP
           
 参数说明:
   ulMsgId [in]: 消息ID,该消息ID可能是MSP定义的,有可能是PS定义的
                
   ulParam1 [in]: 输入的消息结构指针,消息体由调用者(PS)分配内存(通过malloc), 接受者释放(通过free)
                 
   ulParam2 [in]:在透传指令使用中,该参数为ulParam1结构长度
                 ,因为针对透传时候,不关心内容;
                 

 返 回 值: 
    TODO: ...

 调用要求: 调用者:协议栈, 发送消息给MSP,该函数不阻塞，能立即返回。
 调用举例: TODO: ...
 作    者: 陈文峰/00149739 [2009-04-24]
*****************************************************************************/
extern VOS_UINT32 OSA_PostMessageToMsp(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);




/* 发送消息给PS,该函数不阻塞，能立即返回。*/
/* ulParam1/2可以为指针.*/
extern VOS_UINT32 OSM_PostMessageToPs(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

#endif