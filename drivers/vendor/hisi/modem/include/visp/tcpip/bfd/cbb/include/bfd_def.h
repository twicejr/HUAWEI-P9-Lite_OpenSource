/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_def.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-01
*        Author: Wangchengyang
*   Description: BFD需要用到的宏定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_DEF_H_
#define _BFD_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 全局宏 */
#define BFD_Min(a, b)              ((a) < (b) ? (a) : (b))
#define BFD_Max(a, b)              ((a) > (b) ? (a) : (b))

#define BFD_TRUE                       1
#define BFD_FALSE                      0

#define BFD_ON                         1
#define BFD_OFF                        0

/* 一些BFD会话表项中能用到的宏 */
#define BFD_VER                        1           /* BFD版本 */
#define BFD_EVENT_ADD_IPADDR           0           /* 增加地址事件 */
#define BFD_EVENT_DEL_IPADDR           1           /* 删除地址事件 */

#define BFD_MIN_TX_RX_INTERVAL         1           /* BFD最小发送接收时间间隔 */
#define BFD_MAX_TX_RX_INTERVAL         1000         /* BFD最大发送接收时间间隔 */
#define BFD_MIN_DETECT_MULTI           3            /* BFD最小检测倍数 */

#define BFD_MAX_DETECT_MULTI           50           /* BFD最大检测倍数 */
#define BFD_DEFAULT_DOWN_INTERVAL      2000         /* 建立会话的时候,本端默认接收时间间隔或者查询序列下定时查询时间 */
#define BFD_DEFAULT_TX_RX_INTERVAL     30           /* BFD会话建立之后默认发送接收时间间隔 */
/* Modify by Q62011 for BC3D00536 start(修改BFD最大会话数目), 08-10-23 */
#define BFD_MAX_SESSION_NUM_DEF            1000     /* BFD默认最大会话数目 */
#define BFD_MIN_DETECT_TIME            10           /* BFD本端最小探测时间 */

/* Modify by Q62011 for BC3D00536 start(BFD最大session id), 08-10-23 */
#define BFD_MAX_SESSION_ID             9215         /* BFD最大session id*/
#define BFD_MIN_SESSION_ID             1            /* BFD最小session id*/
#define BFD_INVALID_DISCR              0            /* 无效BFD discr */
#define BFD_DEFAULT_TOSEXP             0xE0         /* BFD报文默认TOS值，优先权最高(8位TOS的三个高位bit为全1) */
#define BFD_INVALID_TIMERID            0            /* 无效的timer id */
#define BFD_INVALID_IFINDEX            0            /* 无效的接口索引 */

/* 一些BFD控制报文不同格式长度宏 */
#define BFD_LEN_AUTH_KEYID             6            /* Key ID长度*/
#define BFD_LEN_AUTH_MD5               ( 24 + 24 )  /* MD5验证报文长度 */
#define BFD_LEN_AUTH_SHA1              ( 24 + 28 )  /* SHA1验证报文长度 */
#define BFD_LEN_MAX_SIMPLE_PWD         16           /* 最大简单pwd长度 */
#define BFD_LEN_MIN_SIMPLE_PWD         1            /* 最小简单pwd长度 */

/* 会话配置、地址增删、用户发起查询统一写该事件 */
#define BFD_EVT_OTHER_Q                0x00000100
/*Begin BC3D02903 liangjicheng 2010-04-19 */
#define BFD_EVT_EXT_Q                  0x00000200
/*End   BC3D02903 liangjicheng 2010-04-19 */

/* GR恢复事件 */
#define BFD_EVT_GR_RESTORE             0x00000400
/* GR平滑事件 */
#define BFD_EVT_GR_SMOOTH              0x00000800

#define BFD_EVT_NSR_Q                  0x00001000

#define BFD_MAX_TASK_PRI               255          /* BFD最大优先级 */
#define BFD_ONEROUNDTIMES              8            /* 全局去使能每次删除的会话个数 */

#define BFD_DEFAULT_SNDPKT_LEN         100          /* BFD会话缓存报文的大小 */

/* 源对端端口号定义 */
#define BFD_DEFAULT_SRCPORT            49151        /* 缺省源端口,具体设定到会话的时候需要加上会话id */
#define BFD_DEFAULT_MULTIHOP_DSTPORT   4784         /* 多跳目的端口号 */
#define BFD_DEFAULT_ONEHOP_DSTPORT     3784         /* 单跳目的端口号 */

/* BFD队列、任务需要用到的一些宏定义 */
#define BFD_QDEPTH                     2048         /* BFD队列长度 */
#define BFD_QMODE                      VOS_Q_FIFO   /* 队列标志 */

/* HA标记位 */
#define BFD_HA_BEFORESMOOTH                0x0001    /* 平滑处理前标记位 */
#define BFD_HA_SMOOTHING                   0x0002    /* 正在平滑处理中标记 */
#define BFD_HA_SMOOTHED                    0x0000    /* 已平滑完成标记 */


/* WTR上限，单位:秒 */
#define BFD_MAX_WTR_TIME               1000000       /* WTR上限为一百万秒，约277个小时 */

/* BFD模块使用的SID统一在此定义 */

#define SID_BFD_SESS_ENTRY_S       1  /* BFD_SESS_ENTRY_S */
#define SID_BFD_SNDBUF             2  /* 会话缓存的BFD报文 */

/* end of SID */

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-02 */
/* VRF规格最大值 */
#define BFD_MAX_VRF_INDEX          255 
#define BFD_DEFAULT_VRF_INDEX      0 

/* BFDVRF索引值操作宏:主要用来作为定时器参数传给定时器超时处理函数:
 * ulBfdVrfIndex中高位标识BFD会话ID,低16位表示BFD所在的VRF Index */
#define BFD_GETBFDVRFINDEX(ulTmpSessId,ulTmpVrfId,ulBfdVrfIndex)\
{\
    ulBfdVrfIndex = (((ulTmpSessId << 16 ) & 0xFFFF0000) |(ulTmpVrfId & 0x0000FFFF));\
}

#define BFD_GET_VRFINDEX(ulTmpSessId,ulTmpVrfId,ulBfdVrfIndex)\
{\
    ulTmpSessId = ((ulBfdVrfIndex >> 16 ) & 0x0000FFFF);\
    ulTmpVrfId  = (ulBfdVrfIndex & 0x0000FFFF);\
}

/* End:VISP1.7C03 VRF wangchengyang,2009-02-02 */

#define BFD_OVER_IPV4      0
#define BFD_OVER_IPV6      1
#define BFD_OVER_ALL       2

/*SGSN需求DTS2010090200956: BFD 多会话和应用共用问题*/
#define BFD_CREATE_STATIC_MANUAL    1 /*静态指定描述符创建,暂不涉及*/
#define BFD_CREATE_STATIC_AUTO  2 /*静态自协商*/
#define BFD_CREATE_DYNAMIC  3 /*动态创建*/

/* BFD默认首次协商次数为0,即默认不协商,for VISPV1R8C01-219,wangchengyang 2009/5/18 */
#define BFD_DEFAULT_NEGO_TIMES 0

/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a NULL address
 *      0 -- pAddress isn't a NULL address
 */

#define BFD6_IS_ADDRESS_NULL( pAddress )         \
    ( (0 == (VOS_NTOHL((pAddress)[0]))) \
     && (0 == (VOS_NTOHL((pAddress)[1]))) \
     && (0 == (VOS_NTOHL((pAddress)[2]))) \
     && (0 == (VOS_NTOHL((pAddress)[3]))) )


/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a link-local address
 *      0 -- pAddress isn't a link-local address
 */
#define BFD6_IS_ADDRESS_LINKLOCAL( pAddress )    \
    ( 0xFE800000 == (0xFFC00000&(VOS_NTOHL((pAddress)[0]))) )

/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a site-local address
 *      0 -- pAddress isn't a site-local address
 */
#define BFD6_IS_ADDRESS_SITELOCAL( pAddress )    \
    ( 0xFEC00000 == (0xFFC00000&(VOS_NTOHL((pAddress)[0]))) )

/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a loopback address
 *      0 -- pAddress isn't a loopback address
 */
#define BFD6_IS_ADDRESS_LOOPBACK( pAddress )     \
    ( (0 == (VOS_NTOHL((pAddress)[0]))) \
     && (0 == (VOS_NTOHL((pAddress)[1]))) \
     && (0 == (VOS_NTOHL((pAddress)[2]))) \
     && (1 == (VOS_NTOHL((pAddress)[3]))) )


/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a multicast address
 *      0 -- pAddress isn't a multicast address
 */
#define BFD6_IS_ADDRESS_MULTICAST( pAddress )    \
    ( 0xFF000000 == (0xFF000000&(VOS_NTOHL((pAddress)[0]))) )


/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a global address
 *      0 -- pAddress isn't a global address
 */
/* Modified by w00207740, DTS2013121700565 ,sitelocal地址属于global地址, 2013/12/17 */
#define BFD6_IS_ADDRESS_GLOBAL( pAddress )    \
    ( !((BFD6_IS_ADDRESS_MULTICAST(pAddress))\
     ||(BFD6_IS_ADDRESS_LOOPBACK(pAddress))\
     ||(BFD6_IS_ADDRESS_LINKLOCAL(pAddress))\
     ||(BFD6_IS_ADDRESS_NULL(pAddress))) )   

#define BFD6_ADDRESS_NTOH(x) \
     {\
        (x)[0] = VOS_NTOHL((x)[0]);\
        (x)[1] = VOS_NTOHL((x)[1]);\
        (x)[2] = VOS_NTOHL((x)[2]);\
        (x)[3] = VOS_NTOHL((x)[3]);\
     }
     
     /* x must be a array that have 4 ULONG element */
#define BFD6_ADDRESS_HTON(x) \
     {\
        (x)[0] = VOS_HTONL((x)[0]);\
        (x)[1] = VOS_HTONL((x)[1]);\
        (x)[2] = VOS_HTONL((x)[2]);\
        (x)[3] = VOS_HTONL((x)[3]);\
     }

#define BFD_ADDR_CMP(pulDstAddr,pulSrcAddr,ulIpVer,ulResult)\
{\
    (ulResult) = 1;\
    if (BFD_OVER_IPV4 == (ulIpVer))\
    {\
        if ((pulDstAddr)[0] == (pulSrcAddr)[0])\
        {\
            (ulResult) = 0;\
        }\
    }\
    else\
    {\
        if (((pulDstAddr)[0] == (pulSrcAddr)[0])\
            && ((pulDstAddr)[1] == (pulSrcAddr)[1])\
            && ((pulDstAddr)[2] == (pulSrcAddr)[2])\
            && ((pulDstAddr)[3] == (pulSrcAddr)[3]))\
        {\
            (ulResult) = 0;\
        }\
    }\
}

#define BFD6_ADDR_COPY(pulDstAddr,pulSrcAddr)\
{\
    (pulDstAddr)[0] = (pulSrcAddr)[0];\
    (pulDstAddr)[1] = (pulSrcAddr)[1];\
    (pulDstAddr)[2] = (pulSrcAddr)[2];\
    (pulDstAddr)[3] = (pulSrcAddr)[3];\
}

/* 网络序地址间的比较,字节序最好能够统一啊 */
#define BFD_ADDR_STREAM_CMP(pucDstAddr,pucSrcAddr,ulIpVer,ulResult)\
{\
    ULONG ulAddrLen = 4;\
    INT32 lRetResult = 0;\
    ulResult = 1;\
    if (BFD_OVER_IPV4 == ulIpVer)\
    {\
        ulAddrLen = 4;\
    }\
    else\
    {\
        ulAddrLen = 16;\
    }\
    (VOID)VOS_Mem_Cmp((VOID*) pucDstAddr, (VOID*)pucSrcAddr, ulAddrLen, &lRetResult);\
    if (0 == lRetResult)\
    {\
        ulResult = 0;\
    }\
}
/* 网络序地址间的比较 */

/* 完成GR恢复处理 */
#define BFD_GR_RESTORE_OVER  0
/* 完成GR平滑处理 */
#define BFD_GR_SMOOTH_OVER   1

#define INVALID_IF_TYPE   0xffffffff
#define INVALID_IF_NUM    0xffffffff

/* BFD License功能相关定义 */

#define BFD_LICENSE_ONEROUNDTIMES   256     /* BFD License功能动态打开或关闭时每次处理的会话个数 */
extern ULONG g_ulBfdLicenseGlobalCapability;
extern ULONG g_ulBfd6LicenseGlobalCapability;

typedef enum tagBFD_TOEXT_MSG_TYPE_E
{
    BFD_TOEXT_SESSION_DELETE        = 1               ,         /* 删除会话 */
    /*Added by guojianjun178934, BFD问题单同步处理, 2013/11/18   问题单号:DTS2013111409068 */
    /*Added by qinyun62011, 优化BFD会话ID扩展到9215的性能问题, 2013/9/27 */
    /*VRF删除时，会删除所有的会话每个会话删除时调用SESSION_DELETE通知，因此不需
      要遍历删除操作了*/
    /* End of Added by guojianjun178934, 2013/11/18   问题单号:DTS2013111409068 */
    BFD_TOEXT_UNCAPABILITY                            ,         /* 全局去使能 */
    /* Add for DTS2011021002203, by chenyaoKF34558, at 2011-02-28. 修改原因: 重新设计license功能 */
    BFD_TOEXT_UNLICENSE                               ,         /* 关闭license */
    
    /*Added by guo00178934, BFD全局使能, 2011/7/8   问题单号:DTS2011070601537 */
    BFD_TOEXT_CAPABILITY                              ,
    /* End of Added by guo00178934, 2011/7/8   问题单号:DTS2011070601537 */
    /*Modified by qinyun62011, RFC5882认为在BFD为Admin down的情况下, 路由应该依照其他方式来检测, 2011/8/16   问题单号:DTS2011081005979 */
    BFD_TOEXT_ROUTE_UP                              ,
    /*End of Modified by qinyun62011, 2011/8/16   问题单号:DTS2011081005979 */
    BFD_TOEXT_NSR_RESUME_MODIFY,                               /* NSR过程中底层恢复的动态路由联动会话ID需要变更*/
    BFD6_TOEXT_SESSION_DELETE,
    BFD6_TOEXT_UNCAPABILITY,
    BFD6_TOEXT_UNLICENSE,
    BFD6_TOEXT_CAPABILITY,
    BFD6_TOEXT_ROUTE_UP,
    BFD_TOEXT_MSG_MAX
}BFD_TOEXT_MSG_TYPE_E;

/*Added by luogaowei 2012-01-18 DTS2013011700000  PF重传处理*/
typedef enum tagBFD_PF_STATE_E
{
   PF_STATE_P_NULL = 0,    /*P标记初始状态*/
   PF_STATE_P_OPEN = 1,    /*P标记OPEN状态*/
   PF_STATE_P_EXPIRE = 2,  /*P标记重传超时状态*/
   PF_STATE_F_ACK = 3      /*P标记 F确认状态*/
}BFD_PF_STATE_E;

#define  BFD_PF_TIMER_NUM       32  /*BFD PF 处理定时器个数*/

#define PF_PROC_MODE_NP_RETRAN        0    /* NP重传模式: 同时下发P标记给NP : SGSN 模式*/
#define PF_PROC_MODE_NO_RETRAN        1    /* 发送一个P报文 不下发P标记给NP，即不重传*/
#define PF_PROC_MODE_CONTROL_RETRAN   2    /* 控制面重传模式: 发送一个P报文， 不下发P标记给NP， 同时VISP启动P报文重传 : MBSC、Hert 采用*/

#define PF_PROC_TIMER_PERIOD_MIN 3  /*定时器发送周期最小值 3秒*/
#define PF_PROC_TIMER_PERIOD_DFT 10  /*定时器发送周期默认值 10秒*/
#define PF_PROC_TIMER_PERIOD_MAX 20 /*定时器发送周期最大值 20秒*/

#define PF_PROC_TIMER_RETRAN_MIN  1  /*定时器重传次数最小值 1*/
#define PF_PROC_TIMER_RETRAN_DFT  5  /*定时器重传次数默认值 5*/
#define PF_PROC_TIMER_RETRAN_MAX  10 /*定时器重传次数最大值 10*/

#define  PF_PROC_SRAND_VALUE   4   /*种子值*/
#define  PF_PROC_RAND_OFFSET   2   /*随机偏移值*/

/*Added by w00207740, DTS2013042203832 ,BFD队列调度最大次数,由于disable操作步进为8而去使能license步进为265，故使用32, 2013/6/25 */
#define BFD_SCHEDULE_MAX_NUM    32


/************************ BFD  支持4K VPN 需求开发***************************************/
typedef struct tagBFD_TREE_SET_S/*BFD树集合*/
{
  AVL3_TREE_S  stBfdTree;
  ULONG   ulBfd4Count; /*此树下的BFD4会话个数*/
  ULONG   ulBfd6Count; /*此树下的BFD6会话个数*/
} BFD_TREE_SET_S;

extern int BFD_compare(void *a, void *b);
#define BFD_INIT_AVL_NODE(NODE)            (NODE).parent = 0;                \
                                             (NODE).left = 0;                  \
                                             (NODE).right = 0;                 \
                                             (NODE).sLeftHeight = -1;                \
                                             (NODE).sLeftHeight = -1
#define BFD_TREE_OFFSET(STRUCT,FIELD) (unsigned short)((unsigned char *)(&((STRUCT *)1)->FIELD) - (unsigned char *)1)
#define BFD_AVL_INSERT(TREE, NODE, TREE_INFO) (NULL == AVL3_FindToInsert(&(TREE), &(NODE), &(TREE_INFO)))
#define BFD_AVL_DELETE(TREE, NODE)            AVL3_DeleteNode(&(TREE), &(NODE))
#define BFD_AVL_FIND(TREE, KEY, TREE_INFO) AVL3_FindNode(&(TREE), (KEY), &(TREE_INFO))

#define BFD_AVL_NEXT(NODE, TREE_INFO) AVL3_GetNextNode(&(NODE), &(TREE_INFO))
#define BFD_AVL_FIRST(TREE, TREE_INFO) AVL3_GetFirstNode(&(TREE), &(TREE_INFO))
#define BFD_AVL_GET_OR_NEXT(TREE, KEY, TREE_INFO)  AVL3_GetOrGetNext(&(TREE), (KEY), &(TREE_INFO))

#ifdef __cplusplus
}
#endif

#endif

