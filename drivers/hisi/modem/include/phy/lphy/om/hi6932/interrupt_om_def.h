/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : interrupt_om_def.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月29日
  最近修改   :
  功能描述   : 上报OM相关的定义结构体
  函数列表   :
  修改历史   :
  1.日    期   : 2011年6月20日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件(DTS2011062102036,增加各个函数的运行时间OM统计)

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __INTERRUPT_OM_DEF_H__
#define __INTERRUPT_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_INTERRUPT__
{
    LPHY_REQ_INTERRUPT_RESERVED            = OM_CMD_ID(LPHY_INTERRUPT_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RPT_INTERRUPT_TIME        
}LPHY_REQ_MSGID_INTERRUPT_ENUM;

typedef struct __LPHY_REQ_RPT_INTERRUPT_TIME_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16       enEnaRpt;
}LPHY_REQ_RPT_INTERRUPT_TIME_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_INTERRUPT__
{
    LPHY_CNF_INTERRUPT_RESERVED            = OM_CMD_ID(LPHY_INTERRUPT_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_INTERRUPT_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_INTERRUPT__
{
    LPHY_IND_INTERRUPT_RESERVED            = OM_CMD_ID(LPHY_INTERRUPT_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_INTERRUPT_ENUM;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_INTERRUPT__
{
    LPHY_TRACE_INTERRUPT_RESERVED         =  OM_CMD_ID(LPHY_INTERRUPT_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_INTERRUPT_DUMP_INFO
}LPHY_TRACE_INTERRUPT_ENUM;

typedef enum __LPHY_EXCCAUSE_ENUM__
{
    LPHY_EXCCAUSE_ILLEGAL               ,   /* 0 : Illegal Instruction */
    LPHY_EXCCAUSE_SYSCALL               ,   /* 1 : System Call (SYSCALL instruction) */
    LPHY_EXCCAUSE_INSTR_ERROR           ,   /* 2 : Instruction Fetch Error */
    LPHY_EXCCAUSE_LOAD_STORE_ERROR      ,   /* 3 : Load Store Error */
    LPHY_EXCCAUSE_LEVEL1INTERRUPT       ,   /* 4 : (backward compatibility macro, deprecated, avoid) */
    LPHY_EXCCAUSE_ALLOCA                ,   /* 5 : Stack Extension Assist (MOVSP instruction) for alloca */
    LPHY_EXCCAUSE_DIVIDE_BY_ZERO        ,   /* 6 : Integer Divide by Zero */
    LPHY_EXCCAUSE_SPECULATION           ,   /* 7 : Use of Failed Speculative Access (not implemented) */
    LPHY_EXCCAUSE_PRIVILEGED            ,   /* 8 : Privileged Instruction */
    LPHY_EXCCAUSE_UNALIGNED             ,   /* 9 : Unaligned Load or Store */
    LPHY_EXCCAUSE_RSV_10                ,   /*10 : reserved */
    LPHY_EXCCAUSE_RSV_11                ,   /*11 : reserved */
    LPHY_EXCCAUSE_INSTR_DATA_ERROR      ,   /*12 : PIF Data Error on Instruction Fetch (RB-200x and later) */
    LPHY_EXCCAUSE_LOAD_STORE_DATA_ERROR ,   /*13 : PIF Data Error on Load or Store (RB-200x and later) */
    LPHY_EXCCAUSE_INSTR_ADDR_ERROR      ,   /*14 : PIF Address Error on Instruction Fetch (RB-200x and later) */
    LPHY_EXCCAUSE_LOAD_STORE_ADDR_ERROR ,   /*15 : PIF Address Error on Load or Store (RB-200x and later) */
    LPHY_EXCCAUSE_ITLB_MISS             ,   /*16 : ITLB Miss (no ITLB entry matches, hw refill also missed) */
    LPHY_EXCCAUSE_ITLB_MULTIHIT         ,   /*17 : ITLB Multihit (multiple ITLB entries match) */
    LPHY_EXCCAUSE_INSTR_RING            ,   /*18 : Ring Privilege Violation on Instruction Fetch */
    LPHY_EXCCAUSE_RSV_19                ,   /*19 : reserved */
    LPHY_EXCCAUSE_INSTR_PROHIBITED      ,   /*20 : Cache Attribute does not allow Instruction Fetch */
    LPHY_EXCCAUSE_RSV_21                ,   /*21 : reserved */
    LPHY_EXCCAUSE_RSV_22                ,   /*22 : reserved */
    LPHY_EXCCAUSE_RSV_23                ,   /*23 : reserved */
    LPHY_EXCCAUSE_DTLB_MISS             ,   /*24 : DTLB Miss (no DTLB entry matches, hw refill also missed) */
    LPHY_EXCCAUSE_DTLB_MULTIHIT         ,   /*25 : DTLB Multihit (multiple DTLB entries match) */
    LPHY_EXCCAUSE_LOAD_STORE_RING       ,   /*26 : Ring Privilege Violation on Load or Store */
    LPHY_EXCCAUSE_RSV_27                ,   /*27 : reserved */
    LPHY_EXCCAUSE_LOAD_PROHIBITED       ,   /*28 : Cache Attribute does not allow Load */
    LPHY_EXCCAUSE_STORE_PROHIBITED      ,   /*29 : Cache Attribute does not allow Store */
    LPHY_EXCCAUSE_RSV_30                ,   /*30 : reserved */
    LPHY_EXCCAUSE_RSV_31                ,   /*31 : reserved */
    LPHY_EXCCAUSE_CP0_DISABLED          ,   /*32 : Access to Coprocessor 0 when disabled */
    LPHY_EXCCAUSE_CP1_DISABLED          ,   /*33 : Access to Coprocessor 1 when disabled */
    LPHY_EXCCAUSE_CP2_DISABLED          ,   /*34 : Access to Coprocessor 2 when disabled */
    LPHY_EXCCAUSE_CP3_DISABLED          ,   /*35 : Access to Coprocessor 3 when disabled */
    LPHY_EXCCAUSE_CP4_DISABLED          ,   /*36 : Access to Coprocessor 4 when disabled */
    LPHY_EXCCAUSE_CP5_DISABLED          ,   /*37 : Access to Coprocessor 5 when disabled */
    LPHY_EXCCAUSE_CP6_DISABLED          ,   /*38 : Access to Coprocessor 6 when disabled */
    LPHY_EXCCAUSE_CP7_DISABLED              /*39 : Access to Coprocessor 7 when disabled */          
}LPHY_EXCCAUSE_ENUM;
typedef UINT32 LPHY_EXCCAUSE_ENUM_UINT32;


typedef struct __LPHY_INTERRUPT_EXCEPTION_INFO_STRU__
{
    UINT32                       a[16];  /*异常对应的逻辑寄存器的值*/
    UINT32                      epc[6];  /*产生异常时的指针位置*/
    UINT32                      eps[6];  /*产生异常时候的程序状态寄存器*/
    UINT32                          ps;  /*当前的程序状态寄存器*/
    UINT32                    excvaddr;  /*产生异常时的访问数据地址,通常对应load/store操作*/
    void                     * ptrEpc1; /*存储异常指针epc1的堆栈指针*/
    LPHY_EXCCAUSE_ENUM_UINT32  excause;  /*产生异常的原因*/
    UINT32               ulExcLocation;  /*产生异常的可能位置*/
    UINT32                  ulCurIntNo;  /*死机执行的时候是否在中断函数中,0xffffffff表示在main函数中*/
    UINT32                    ulSymbNo;  /*调度表的符号数*/
    UINT32                  ulCurState;  /*死机执行的时候当前状态*/
    UINT32                    ulIntNo;    /*死机时中断号,0表示没有在中断中死机*/
    UINT32               ulSchedFuncNo;  /*调度表的函数号*/
}LPHY_INTERRUPT_EXCEPTION_INFO_STRU;


/************************************************************
                           5. SG 数据结构定义, 算法需要绘图的
************************************************************/
typedef enum __LPHY_SG_MSGID_INTERRUPT__
{
    LPHY_SG_INTERRUPT_RESERVED            = OM_CMD_ID(LPHY_INTERRUPT_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_INTERRUPT_TIME,
    LPHY_SG_INTERRUPT_CORE_COUNTER,
}LPHY_SG_MSGID_INTERRUPT_ENUM;

typedef struct __LPHY_SG_INTERRUPT_TIME_STRU__
{
    UINT32    ulStartTime[32];      /*表示每个符号的起始时间和结束时间，单位为0.25Ts*/
    UINT32    ulEndTime[32];        /*表示每个符号的起始时间和结束时间，单位为0.25Ts*/
}LPHY_SG_INTERRUPT_TIME_STRU;

typedef struct __LPHY_SG_INTERRUPT_CORE_COUNTER_STRU__
{
    UINT32   ulDuration[32];
}LPHY_SG_INTERRUPT_CORE_COUNTER_STRU;

/************************************************************
                           6. ERROR 数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_INTERRUPT__
{
    LPHY_ERROR_INTERRUPT_RESERVED         =  OM_CMD_ID(LPHY_INTERRUPT_MID, OM_TYPE_ERROR, 0x0),
}LPHY_ERROR_INTERRUPT_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __INTERRUPT_OM_DEF_H__ */
