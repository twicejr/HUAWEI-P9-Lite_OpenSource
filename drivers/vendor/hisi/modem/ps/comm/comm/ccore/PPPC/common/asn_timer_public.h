/******************************************************************************

                  版权所有 (C), 2012-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : asn_timer_public.h
  版 本 号   : 初稿
  作         者   :  zhaichao
  生成日期   : 2012年9月27日
  最近修改   :
  功能描述   : 业务定时器模块提供给AM子系统的公共头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月27日
    作    者   : zhaichao
    修改内容   : 创建文件

******************************************************************************/
#ifndef __ASN_TIMER_PUBLIC_H__
#define __ASN_TIMER_PUBLIC_H__



/*--------------------- 定时器类型定义 -----------------------------------*
  定时器类型的宏定义如下图所示:
  -------------------------------------------------
  |  定时器   |  定时器   |      定时器           |
  |   样式    | 功能类型  |      类型码           |
  -------------------------------------------------
  其中,定时器类型对应定时器出超时消息结构中的定时器类型字段.
*/

#define ASN_TIMER_DEF_TYPE(Style, TimerMid, Sub) ((((Style)&0xFF)<<24)  |(((TimerMid) &0xFF)<<16) | ((Sub)&0xFFFF))
#define ASN_TIEMR_GET_MID(TimerType) (((TimerType)>>16)&0xFF)

/* 使用定时器的模块ID，新增模块必须在此处增加mid的定义 */
typedef enum
{
    ASN_COMMON_TIMER_MODULE_START,
    ASN_COMMON_TIMER_MODULE_A11,                         /* a11模块定时器使用的MID */ 
    ASN_COMMON_TIMER_MODULE_IPV6,                       /* IPV6模块定时器使用的MID */ 
    ASN_COMMON_TIMER_MODULE_PDN,                       /* PDN模块定时器使用的MID */ 
    ASN_COMMON_TIMER_MODULE_USM,                       /* USM模块定时器使用的MID */ 
    ASN_COMMON_TIMER_MODULE_FA,                          /* FA模块定时器使用的MID */ 
    ASN_COMMON_TIMER_MODULE_PMIPV6,                      /* PMIPV6模块定时器使用的MID */
    ASN_COMMON_TIMER_MODULE_RESV,                        /*RESV模块定时器使用的MID */
    ASN_COMMON_TIMER_MODULE_END
}ASN_COMM_TIMER_MID_E;

/*定时器样式定义*/
typedef enum
{
    ASN_CP_COMMON_TIMER_STYLE   = 0x01,             /* 标识普通的暂态定时器*/ 
    ASN_CP_LOOP_TIMER_STYLE,                                      /* 标识循环定时器 */

    ASN_CP_TIMER_STYLE_BUTT
}ASN_COMM_TIMER_STYLE_E;


/*启动定时器函数输入参数的数据结构形式,由业务层填写*/
typedef struct
{   
    VOS_UINT32 ulTimerType;             /* 定时器类型 */
    VOS_UINT32 ulTimerLength;        /*定时器超时时长(单位:秒)*/
    VOS_UINT32 ulParam1;      
    VOS_UINT32 ulParam2;                 /*用户参数2*/
} ASN_STARTTIMER_PARAM_S;

/*定时器任务向其它任务发送超时消息的结构*/
typedef struct
{   
    VOS_UINT32  ulTimerType; /*定时器类型, 填写定时器类型定义的宏,参见本文档*/
    VOS_UINT32  ulTimerID;   /*定时器ID*/
    VOS_UINT32  ulParam1;    /*用户参数*/
    VOS_UINT32  ulParam2;    /*用户参数*/
} ASN_TIMER_MSG_S;

/*********************对外提供的借口函数**********************/
VOS_UINT32 ASN_TimerInitRegister(VOS_UINT32 ulTimerMid, VOS_UINT64 ullCsi, VOS_UINT32 ulMsgType);
extern VOS_UINT32 ASN_CPGetTimerNodePosition(VOS_UINT32  ulTimerID, VOS_UINT32  *pulNodePosition);

extern VOS_UINT32 ASN_CPGetTimerSpareTime(VOS_UINT32  ulTimerID, VOS_UINT32  *pulGetSpareTime);
extern VOS_UINT32 ASN_CPStartTimer(ASN_STARTTIMER_PARAM_S* pstStartTimerParam, VOS_UINT32* pulTimerID);
extern VOS_UINT32 ASN_CPStopTimer(VOS_UINT32 ulTimerType, VOS_UINT32 ulTmrIndex);

#endif /* __ASN_TIMER_PUBLIC_H__ */
