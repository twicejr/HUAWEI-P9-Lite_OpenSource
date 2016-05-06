/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_def.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块的宏和枚举定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_DEF_H_
#define _TRUNK_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Trunk接口最大数目 */
#define TRUNK_MAX_NUM           g_ulTrunkMaxIfNums
#define TRUNK_MIN_NUM           32

/* Trunk ID最小值 */
#define TRUNK_MIN_ID            0
/* Trunk ID最大值 */
#define TRUNK_MAX_ID            (g_ulTrunkMaxIfNums - 1)

/* Trunk相关组件个数 */
#define TRUNK_COM_NUM           9

/* Trunk模块定时器时长(单位: ms)
为提升定时器精度周期由1000ms修改为100ms,DTS2013060100805 m59090 */
#define TRUNK_TIME              100

/* 定时器周期修改为100ms后需要对超时次数增加10倍,DTS2013060100805 m59090 */
#define TRUNK_TIME_MULT 10

/* Trunk link loop back timer */
#define TRUNK_LB_TIME           3000

/* 10M波特率 (以K为单位--- 修改原因:否则10GE速率无法标识) */
#define TRUNK_SPEED_10M     (10*1024)

/* 100M波特率 (以K为单位--- 修改原因:否则10GE速率无法标识) */
#define TRUNK_SPEED_100M    (100*1024)

/* 1000M波特率 (以K为单位--- 修改原因:否则10GE速率无法标识) */
#define TRUNK_SPEED_1000M   (1000*1024)
#define TRUNK_SPEED_MAX_GE  (1024*1024)

/* 10GE波特率 (以K为单位--- 修改原因:否则10GE速率无法标识) */
#define TRUNK_SPEED_10GE   (10*1000*1024)
#define TRUNK_SPEED_MAX_10GE  (10*1024*1024)

/* 40GE波特率 (以K为单位--- 修改原因:否则10GE速率无法标识) */
#define TRUNK_SPEED_40GE   (40*1000*1024)
#define TRUNK_SPEED_MAX_40GE  (40*1024*1024)

#define TRUNK_SPEED_MAC_MULTI   5  /*GET_SPEEDKEY_BY_BAUD中最大key值/0x100 */

/* 非法Trunk ID */
#define TRUNK_INVALID_ID        0xFFFFFFFF

/* physical地址长度 */
#define TRUNK_MACADDR_LEN       6

#define TRUNK_MAX_NEG_TIME 600         /* 设置首次协商不过对外告警最大时间,单位为s */
#define TRUNK_NEGWARNING_TIMEINIT  (ULONG)~0x0  /* 0xFFFFFFFF */
#define TRUNK_NEGWARNING_TIMEDONE  (ULONG)~0x1  /* 0xFFFFFFFE */

/* 对state进行操作的宏 */
#define LACP_EXPIRED           0x0
#define LACP_STATE_ACTIVITY    0x01
#define LACP_STATE_TIMEOUT     0x02
#define LACP_STATE_AGG         0x04
#define LACP_STATE_SYNC        0x08
#define LACP_STATE_COLLECT     0x10
#define LACP_STATE_DISTRIB     0x20
#define LACP_STATE_DEFAULT     0x40
#define LACP_STATE_EXPIRED     0x80

#define LACP_SET_STATE_ACTIVITY(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_ACTIVITY;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_ACTIVITY);\
    }\
}
#define LACP_GET_STATE_ACTIVITY(ucState) (ucState & LACP_STATE_ACTIVITY)

#define LACP_SET_STATE_TIMEOUT(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_TIMEOUT;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_TIMEOUT);\
    }\
}
#define LACP_GET_STATE_TIMEOUT(ucState) ((ucState & LACP_STATE_TIMEOUT) >> 1)

#define LACP_SET_STATE_AGG(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_AGG;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_AGG);\
    }\
}
#define LACP_GET_STATE_AGG(ucState) ((ucState & LACP_STATE_AGG) >> 2)

#define LACP_SET_STATE_SYNC(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_SYNC;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_SYNC);\
    }\
}
#define LACP_GET_STATE_SYNC(ucState) ((ucState & LACP_STATE_SYNC) >> 3)

#define LACP_SET_STATE_COLLECT(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_COLLECT;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_COLLECT);\
    }\
}
#define LACP_GET_STATE_COLLECT(ucState) ((ucState & LACP_STATE_COLLECT) >> 4)

#define LACP_SET_STATE_DISTRIB(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_DISTRIB;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_DISTRIB);\
    }\
}
#define LACP_GET_STATE_DISTRIB(ucState) ((ucState & LACP_STATE_DISTRIB) >> 5)

#define LACP_SET_STATE_DEFAULT(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_DEFAULT;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_DEFAULT);\
    }\
}
#define LACP_GET_STATE_DEFAULT(ucState) ((ucState & LACP_STATE_DEFAULT) >> 6)

#define LACP_SET_STATE_EXPIRED(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_EXPIRED;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_EXPIRED);\
    }\
}
#define LACP_GET_STATE_EXPIRED(ucState) ((ucState & LACP_STATE_EXPIRED) >> 7)


/* 对于主备\非恢复的Trunk组,未被选中端口的端口号最高位置1. 选择逻辑时,应该不考虑最高位的取值 */
#define LACP_GET_PORTNUM(usPortNum) (usPortNum & 0X7FFF)


/* 每秒发送的LACP报文的最大数目*/
#define LACP_PDU_MAXSEND_PERSECOND  3

#define LACP_FAST_PERIODIC_TIME     1   /* 利用短超时定义的周期性发送时间长度（秒） */
#define LACP_SLOW_PERIODIC_TIME     30  /* 利用长超时定义的周期性发送时间长度（秒） */

#define LACP_SHORT_TIMEOUT_TIME     3   /* 利用三倍短超时定义的接收超时时间长度（秒）*/
#define LACP_LONG_TIMEOUT_TIME      90  /* 利用三倍长超时定义的接收超时时间长度（秒）*/

/* 以下为LACPDU报文中用到的相关的宏定义 */
#define LACP_SUBTYPE                1  /* 慢速协议中LACP的协议号 */
#define LACP_VERSION                1  /* 协议版本号 */
#define LACP_ACTOR_TYPE             1  /* 指示为Actor类型 */
#define LACP_ACTOR_INFO_LEN         20 /* Actor信息的长度 */
#define LACP_PARTNER_TYPE           2  /* 指示为Partner的类型 */
#define LACP_PARTNER_INFO_LEN       20 /* partner信息的长度 */
#define LACP_COLLECTOR_TYPE         3  /* 指示为collector类型 */
#define LACP_COLLECTOR_LEN          16 /* collector信息的长度 */
#define LACP_MAX_COLLECTOR_DELAY    0  /* 最大收集延迟 */

/* 报文输入输出标志 */
#define PKT_INPUT   0
#define PKT_OUTPUT  1

/* 选择逻辑数组无效下标 */
#define LACP_SL_INVALID_PORTID  0xFFFFFFFF

/* 缺省优先级 */
#define LACP_DEFAULT_PRI 0xFFFF

/* trunk或成员端口上建立单跳bfd会话的生效模式 */
#define BFD_TRUNKMODE_TRUNK     0x0 /* trunk上的单跳会话生效 */
#define BFD_TRUNKMODE_PORT      0x1 /* 成员端口上的单跳会话生效 */

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical地址长度*/
#endif

/* 1:1模式下最大端口数 */
#define TRUNK_ONETOONE_MAX_PORT  2

#define GET_SPEEDKEY_BY_BAUD(Baud, Key)\
do\
{\
    switch(Baud)\
    {\
        case TRUNK_SPEED_10M:\
        case (10*1000):\
            (Key) = 0x100;\
            break;\
        case TRUNK_SPEED_100M:\
        case (100*1000):\
            (Key) = 0x200;\
            break;\
        case TRUNK_SPEED_1000M:\
        case (1000*1000):\
        case TRUNK_SPEED_MAX_GE:\
            (Key) = 0x300;\
            break;\
        /* 10GE */\
        case TRUNK_SPEED_10GE:\
        case (10*1000*1000):\
        case TRUNK_SPEED_MAX_10GE:\
            (Key) = 0x400;\
            break;\
        /* 40GE */\
        case TRUNK_SPEED_40GE:\
        case (40*1000*1000):\
        case TRUNK_SPEED_MAX_40GE:\
            (Key) = 0x500;\
            break;\
        default:\
            (Key) = 0;\
            break;\
    }\
}while(0)\

/* 增加LACP down的原因记录 */
enum emumTRUNK_LACP_DOWN_DOT
{
    TRUNK_DOWN_NORMAL               = 0,
    TRUNK_DOWN_PORTDOWN             = 1, /* 底层上报物理down */
    TRUNK_DOWN_PORTSPEED            = 2, /* 端口速率发生变化 */
    TRUNK_DOWN_PORTDUPLEX           = 3, /* 端口双工模式发生变化 */
    TURNK_DOWN_PORTREMOVE           = 4, /* 端口移出TRUNK组 */
    TRUNK_DOWN_RXTIMEOUT            = 5, /* 接收定时器超时 */
    TRUNK_DOWN_PARTNER_UNSEL        = 6, /* 收到对端没有选中标记 */ 
    TRUNK_DOWN_PARTNER_PARA_CHANGE  = 7, /* 收到对端参数变化 */
    TRUNK_DOWN_ACTOR_PARA_CHANGE    = 8, /* 收到对端保存本端参数变化 */
    TRUNK_DOWN_END        = 0xFF,
};

enum enumTRUNK_NSR_LINK_STATE
{
    TRUNK_NSR_LINK_CONFIG_RESUME_FAIL = 1,                  /* 由于转发面的数据错误导致的恢复失败 */
    TRUNK_NSR_LINK_RESUME_FINISH,                       /**/
    TRUNK_NSR_LINK_STATE_MAX
};

/*Added by w00207740, 添加非LACP报文丢弃宏, 2014/1/10 */
#define TRUNK_DROP_NOLACP_OFF    0
#define TRUNK_DROP_NOLACP_ON     1
        
#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_DEF_H_ */
