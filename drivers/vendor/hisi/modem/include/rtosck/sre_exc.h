/**
 * @file sre_exc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：异常模块的对外头文件。 \n
 */

/**@defgroup SRE_exc 异常接管
  *@ingroup SRE_inspect
*/

#ifndef _SRE_EXC_H
#define _SRE_EXC_H

#include "sre_base.h"
#include "sre_hook.h"
#include "sre_sys.h"
#include "sre_hw_ecc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//目前UOS不支持异常自接管功能
//#if (OS_OPTION_EXC == YES)

/**
 *@ingroup SRE_exc
 *异常错误码: 获取异常缓冲区信息接口入参为空指针。
 *
 *值：0x02001c02
 *
 *解决方案：检查入参指针有效性。
 */
#define OS_ERRNO_EXC_PARA_INVLAID                               SRE_ERRNO_OS_ERROR(OS_MID_EXC,0x2)

/**
 *@ingroup SRE_exc
 *异常错误码: Cortex-Ax配置的复位不丢失内存起始地址没有4字节对齐。
 *
 *值：0x02001c04
 *
 *解决方案：A7,A9 配置的复位不丢失内存起始地址必须4字节对齐。
 */
#define OS_ERRNO_EXC_RESET_NOLOSE_MEM_ADDR_NOT_ALIGN            SRE_ERRNO_OS_ERROR(OS_MID_EXC,0x4)

/**
 *@ingroup SRE_exc
 *异常错误码: 异常模块注册异常钩子函数为空。
 *
 *值：0x02001c09
 *
 *解决方案：查看注册异常钩子函数是否为空。
 */
#define OS_ERRNO_EXC_REG_HOOK_PTR_NULL                          SRE_ERRNO_OS_ERROR(OS_MID_EXC,0x9)

/**
 *@ingroup SRE_exc
 *异常错误码: 异常注册函数中,double异常栈空间设置太小。
 *
 *值：0x02001c0a
 *
 *解决方案：请增大double异常栈空间的长度，使之不小于异常寄存器信息EXC_REGS_S的3倍(double异常,NMI异常,Debug异常共用)。
 */
#define OS_ERRNO_EXC_REGISTER_DOUBLE_EXC_STACK_TOOSMALL              SRE_ERRNO_OS_ERROR(OS_MID_EXC,0xa)

/**
 *@ingroup SRE_exc
 *异常错误码: 中断优先级掩码被踩，导致系统异常重启。
 *
 *值：0x03001c0b
 *
 *解决方案：
 *产品可以通过&g_auwIntMask找到掩码存放地址，判断是否是以下的值
 *SD6108/SD6181 DSP:0xC00010C0 0x307F8D20 0x0F80201E 0x00000201
 *SD6108/SD6181 CPU:0x000000C0 0xF07F9B20 0x0F80201E 0x00000401
 *SD6182:0x2BFFB8C1 0xD400043C 0x00000302
 *如果不是，说明掩码被踩，可在中断优先级掩码所在的内存中打数据断点，定位为何会出现中断优先级掩码被踩的错误。
 */
#define OS_ERRNO_EXC_INTERRUPT_LEVEL_MASK_ERROT                      SRE_ERRNO_OS_FATAL(OS_MID_EXC,0xb)

/**
 *@ingroup SRE_exc
 *异常错误码: Hac超时处理钩子未注册。
 *
 *值：0x03001c12
 *
 *解决方案：进入此分支有两种情况，一种是Hac超时导致soc中的interrupt寄存器被清，导致中断调度到此异常分支，
 *一种是中断优先级掩码被踩，导致进入这个分支，然而由于产品没有注册此类异常的钩子，因此进入致命错误处理。
 *产品可以通过&g_auwIntMask找到掩码存放地址，判断是否是以下的值
 *SD6108/SD6181 DSP:0xC00010C0 0x307F8D20 0x0F80201E 0x00000201
 *SD6108/SD6181 CPU:0x000000C0 0xF07F9B20 0x0F80201E 0x00000401
 *SD6182:0x2BFFB8C1 0xD400043C 0x00000302
 *如果掩码都正确，则是hac出现超时自清了。
 */
#define OS_ERRNO_EXC_HAC_EXCEPTION_HOOK_NOREG                       SRE_ERRNO_OS_FATAL(OS_MID_EXC, 0x12)

/**
 *@ingroup SRE_exc
 *异常错误码: 进程异常信息保存结构体内存申请失败。
 *
 *值：0x02001c13
 */
#define OS_ERRNO_EXC_INFO_STRUC_MALLOC_FAIL                         SRE_ERRNO_OS_ERROR(OS_MID_EXC, 0x13)


/**
 *@ingroup SRE_exc
 *调用栈解析最大层数。
 */
#define EXC_CSTK_DEAPTH             10

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:指令预取错误异常。
 */
#define OS_EXCCAUSE_INSTRPIFDATAERROR_CAUSE                 12

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:数据预存取错误异常。
 */
#define OS_EXCCAUSE_LOADSTOREPIFDATAERROR_CAUSE             13

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:WriteError错误异常。
 */
#define OS_EXCCAUSE_WRITEERROR             67

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:ECC错误异常。
 */
#define OS_EXCCAUSE_ECCERROR               68

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:NMI中断异常。
 */
#define OS_EXCCAUSE_NMIERROR               69

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:重复位异常。
 */
#define OS_EXCCAUSE_RESET_REENTRY          70

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:Double异常。
 */
#define OS_EXCCAUSE_DOUBLEERROR            71

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:致命错误异常。
 */
#define OS_EXCCAUSE_FATALERROR             72

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:栈越界异常。
 */
#define OS_EXCCAUSE_STACKOVERFLOW          73

/**
 *@ingroup SRE_exc
 *SD6182/SD6157异常具体类型:硬件信号量错误异常。
 */
#define OS_EXCCAUSE_HWSEMERROR             74

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:指令断点异常。
 */
#define OS_EXCCAUSE_INSTRUCTION_BP         75

/**
 *@ingroup SRE_exc
 *SD6182/SD6157/SD6108/SD6181异常具体类型:数据断点异常。
 */
#define OS_EXCCAUSE_DATA_BP                76

#if ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 *@ingroup SRE_exc
 *SD6182异常具体类型:Hac自清异常。
 */
#define OS_EXCCAUSE_HACERROR               77

/**
 *@ingroup SRE_exc
 *SD6182/SD6157异常具体类型:Msgm错误异常。
 */
#define OS_EXCCAUSE_MSGM_ERROR             78

/**
 *@ingroup SRE_exc
 *SD6182/SD6157异常具体类型:msgQ bus err异常。
 */
#define OS_EXCCAUSE_MSGQBUSERROR           79

#endif

#endif

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 *@ingroup SRE_exc
 * 调用栈信息结构体。
 */
typedef struct tagCstkStackInfo
{
    UINT32  uwStackAddr;                /**< 函数堆栈框地址 */
    UINT32  uwInstrAddr;                /**< 函数返回地址   */
} CSTK_FRAME_INFO_S;
#endif

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170))

/*
 *异常时记录的ipc邮箱信息,注意同步更新测试代码的结构体TST_IPC_STATUS_S。
 */
typedef struct tagIpcStatus
{
    UINT32 vuwSrc;
    UINT32 vuwData[2];
} IPC_STATUS_S;


/**
 *@ingroup SRE_exc
 *SD6181平台下发生全局硬件信号量异常标志。
 */
#define  GHWSEM_ERR_FLAG                   0x1

/**
 *@ingroup SRE_exc
 *SD6181平台下发生局部硬件信号量异常标志。
 */
#define  LHWSEM_ERR_FLAG                   0x2

/**
 * @ingroup SRE_exc
 * 硬件信号量错误结构体
 * SD6181平台硬件信号量错误结构体信息
 */
typedef struct tagTensilicaHwSemErrInfo
{
    UINT8   ucHwSemType;               /**< 出错的硬件信号量类型：GHWSEM_ERR_FLAG(表示全局)或LHWSEM_ERR_FLAG(表示局部)*/
    UINT8   ucResvered;                /**< 预留                                                                     */
    UINT16  usResvered;                /**< 预留                                                                     */
    UINT32  uwHwsemErr;                 /**< 硬件信号量异常信息                                                      */
} HWSEM_ERR_S;

/**
 *@ingroup SRE_exc
 * 寄存器信息结构
 *
 * 描述:SD6181&SD6108平台下的异常触发时保存的寄存器信息。
 *
 * 注意:以下寄存器名称去掉类型前缀‘uw’，即对应芯片手册中的寄存器名称
 * 可接管的异常类型:除了包括系统自带的64种异常外，还可以接管以下异常类型
 * #define OS_EXCCAUSE_WRITEERROR           67   //write error异常
 * #define OS_EXCCAUSE_ECCERROR             68   //L1 ECC异常
 * #define OS_EXCCAUSE_NMIERROR             69   //NMI中断
 * #define OS_EXCCAUSE_RESET_REENTRY        70   //复位向量重入异常
 * #define OS_EXCCAUSE_DOUBLEERROR          71   //double异常
 * #define OS_EXCCAUSE_FATALERROR           72   //致命错误异常
 * #define OS_EXCCAUSE_STACKOVERFLOW        73   //栈越界异常
 * #define OS_EXCCAUSE_HWSEMERROR           74   //硬件信号量错误异常
 * #define OS_EXCCAUSE_INSTRUCTION_BP       75   //指令断点异常
 * #define OS_EXCCAUSE_DATA_BP              76   //数据断点异常
 */
typedef struct tagTensilicaExcRegInfo
{
    UINT32 uwPC;            /**< pc指针地址                             */
    UINT32 uwPS;            /**< 处理器状态                             */
    UINT32 uwEXCCAUSE;      /**< 上一次异常类型                         */
    UINT32 uwEXCVADDR;      /**< 上一次读取、加载或转储异常的虚拟地址   */
    UINT32 uwLBEG;          /**< 循环起始地址                           */
    UINT32 uwLEND;          /**< 循环结束地址                           */
    UINT32 uwLCOUNT;        /**< 循环计数器寄存器                       */
    UINT32 uwSAR;           /**< 移位寄存器                             */
    UINT32 auwA[32];        /**< A组32个通用寄存器                      */
    UINT32 uwWINDOWBASE;    /**< 目前AR REG窗口位置寄存器               */
    UINT32 uwWINDOWSTART;   /**< AR REG窗口pending寄存器                */
    UINT32 uwDEPC;          /**< double 异常程序寄存器                  */
    UINT32 uwBR;            /**< br 寄存器                              */
    UINT32 uwEPC1;          /**< lv1 异常PC寄存器                       */
    UINT32 uwEPC2;          /**< lv2 异常PC寄存器                       */
    UINT32 uwEPC3;          /**< lv3 异常PC寄存器                       */
    UINT32 uwEPC4;          /**< lv4 异常PC寄存器                       */
    UINT32 uwEPC5;          /**< lv5 异常PC寄存器                       */
    UINT32 uwEPC6;          /**< lv6 异常PC寄存器                       */
    UINT32 uwEPS2;          /**< lv2 异常状态寄存器                     */
    UINT32 uwEPS3;          /**< lv3 异常状态寄存器                     */
    UINT32 uwEPS4;          /**< lv4 异常状态寄存器                     */
    UINT32 uwEPS5;          /**< lv5 异常状态寄存器                     */
    UINT32 uwEPS6;          /**< lv6 异常状态寄存器                     */
    UINT32 uwEXCSAVE1;      /**< lv1 异常保存寄存器                     */
    UINT32 uwEXCSAVE2;      /**< lv2 异常保存寄存器                     */
    UINT32 uwEXCSAVE3;      /**< lv3 异常保存寄存器                     */
    UINT32 uwEXCSAVE4;      /**< lv4 异常保存寄存器                     */
    UINT32 uwEXCSAVE5;      /**< lv5 异常保存寄存器                     */
    UINT32 uwEXCSAVE6;      /**< lv6 异常保存寄存器                     */
    UINT32 uwINTENABLE;     /**< 中断使能寄存器                         */
    UINT32 uwINTERRUPT;     /**< 中断pending寄存器                      */
    UINT32 uwSCOMPARE1;     /**< 条件存储比较寄存器                     */
    UINT32 uwCCOMPARE0;     /**< 比较寄存器0                            */
    UINT32 uwCCOMPARE1;     /**< 比较寄存器1                            */
    UINT32 uwCCOMPARE2;     /**< 比较寄存器2                            */
    UINT32 uwCCOUNT;        /**< 比较寄存器计数值                       */
    UINT32 uwCPENABLE;      /**< 协处理使能寄存器                       */
    UINT32 uwVECBASE;       /**< 动态向量表基址                         */
    UINT32 uwDBREAKA0;      /**< 数据断点地址0                          */
    UINT32 uwDBREAKA1;      /**< 数据断点地址1                          */
    UINT32 uwDBREAKC0;      /**< 数据断点控制寄存器0                    */
    UINT32 uwDBREAKC1;      /**< 数据断点控制寄存器1                    */
    UINT32 uwDEBUGCAUSE;    /**< 上一次debug异常原因                    */
    UINT32 uwIBREAK0;       /**< 指令断点地址0                          */
    UINT32 uwIBREAK1;       /**< 指令断点地址1                          */
    UINT32 uwIBREAKENABLE;  /**< 指令断点使能寄存器                     */
    UINT32 uwICOUNT;        /**< 指令计数器                             */
    UINT32 uwICOUNTLEVEL;   /**< 指令计数等级阈值寄存器                 */
    UINT32 uwReserved;      /**< 保留，保证对齐，不要去掉               */
    ECC_REGS_S stEccRegInfo;/**< ECC异常保存寄存器信息                  */
} EXC_REGS_S;

#elif ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 *@ingroup SRE_exc
 * SD6182/SD6157平台下，对于上报所有CPU的硬件信号量异常，记录的核号大小。
 */
#define  HWSEM_ERR_DEFAULT_CORE            0xff

/**
 *@ingroup SRE_exc
 *SD6182/SD6157平台下发生全局硬件信号量异常标志。
 */
#define  GHWSEM_ERR_FLAG                   0x1

/**
 *@ingroup SRE_exc
 *SD6182/SD6157平台下发生局部硬件信号量异常标志。
 */
#define  LHWSEM_ERR_FLAG                   0x2

/**
 * @ingroup SRE_exc
 * 硬件信号量错误信息类型。
 * SD6182/SD6157的错误结构体信息。
 */
typedef enum tagTensilicaHwSemErrType
{
    OS_HWSEM_ERR_PEND_IN_QUEUE_SEM    = 1,      /**< 申请在队列中继续申请获取                       */
    OS_HWSEM_ERR_PEND_BUSY_SEM        = 2,      /**< 申请获取已经获取到的信号量                     */
    OS_HWSEM_ERR_POST_OTHER_CORE_SEM  = 3,      /**< 释放其他cpu占用的信号量                        */
    OS_HWSEM_ERR_CPU_ID_INVALID       = 4,      /**< 申请或释放信号量的cpu id越界                   */
    OS_HWSEM_ERR_READ_DIRECT_REG      = 5,      /**< 非查询模式下读Direct寄存器                     */
    OS_HWSEM_ERR_WRITE_INDIRECT_REG   = 6,      /**< 非队列模式下写InDirect寄存器                   */
    OS_HWSEM_ERR_WRITE_COMBINED_REG   = 7,      /**< 非组合模式下写Combined寄存器                   */
    OS_HWSEM_ERR_OPERATE_CNT_REG      = 8,      /**< 未使能计数模式，对计数模式寄存器进行访问操作   */
    OS_HWSEM_ERR_CNT_UNDER_RUN        = 9,      /**< 计数器under-run异常                            */
    OS_HWSEM_ERR_OPERATE_CNT_EN_REG   = 10      /**< 非递减计数模式下，对计数模式使能寄存器进行访问 */
} HWSEM_ERR_TYPE_E;

/**
 * @ingroup SRE_exc
 * 硬件信号量错误结构体。
 * SD6182/SD6157的错误结构体信息。
 */
typedef struct tagTensilicaHwSemErrInfo
{
    UINT8  ucHwSemType;               /**< 出错的硬件信号量类型：GHWSEM_ERR_FLAG(表示全局)或LHWSEM_ERR_FLAG(表示局部)*/
    UINT8  ucHwsemClustId;            /**< 簇ID，出错的硬件信号量类型为局部时有效                                    */
    UINT8  ucHwSemId;                 /**< 出错的硬件信号量ID                                                        */
    UINT8  ucHwsemCoreId;             /**< 引起硬件信号量错误的核号，无效时为#HWSEM_ERR_DEFAULT_CORE                 */
    HWSEM_ERR_TYPE_E  enHwsemErrTpye; /**< 硬件信号量的错误类型                                                      */
} HWSEM_ERR_S;

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:AXI总线slverr错误。
 */
#define MSGM_EXC_TYPE_AXI_SLVERR     0

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:AXI总线decerr错误。
 */
#define MSGM_EXC_TYPE_AXI_DECERR     1

/**
 *@ingroup SRE_exc
 *SD6182 MSGM异常类型:LSI总线错误。
 */
#define MSGM_EXC_TYPE_LSI_ERR        2

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:filter功能消息阻塞丢失错误, 当前不接管。
 */
#define MSGM_EXC_TYPE_DBG_LOST       3

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:正常消息队列溢出错误。
 */
#define MSGM_EXC_TYPE_NOR_OV         4

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:正常消息队列溢出丢失错误。
 */
#define MSGM_EXC_TYPE_NOR_OV_LOST    5

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:正常消息队列credit失配错误。
 */
#define MSGM_EXC_TYPE_CRED_MM        8

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:共享消息队列溢出错误。
 */
#define MSGM_EXC_TYPE_SH_OV          9

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:同步队列入队消息非法错误。
 */
#define MSGM_EXC_TYPE_SYNC_ERR      12

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:同步队列消息发送阻塞丢失错误。
 */
#define MSGM_EXC_TYPE_SYNC_LOST     13

/**
 *@ingroup SRE_exc
 *SD6182/SD6157 MSGM异常类型:同步消息队列超时错误。
 */
#define MSGM_EXC_TYPE_SYNC_TOT      14

/*
 *@ingroup SRE_exc
 * 寄存器信息结构
 *
 * 描述:SD6182/SD6157平台下的异常触发时保存的MSGM异常寄存器信息。
*/
typedef struct tagMsgmExcInfo
{
    UINT8   ucExcMsgm;              /**< 异常MSGM标识，0表示GMSGM，1表示LMSGM */
    UINT8   ucExcType;              /**< MSGM异常类型 */
    UINT8   ucSynTotQue;            /**< 同步消息超时队列ID，异常类型为MSGM_EXC_TYPE_SYNC_TOT时记录 */
    UINT8   ucSynErrMsgQue;         /**< 同步消息无效队列ID，异常类型为MSGM_EXC_TYPE_SYNC_ERR时记录 */
    UINT32  uwSynErrMsgData;        /**< 同步消息无效高32bit数据，异常类型为MSGM_EXC_TYPE_SYNC_ERR时记录 */
    UINT8   ucNorOvCnt;             /**< 普通消息溢出计数，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT8   ucNorOvCore;            /**< 普通消息溢出对应核号，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT8   ucNorOvQport;           /**< 普通消息溢出对应QPort编号，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT8   ucNorOvQue;             /**< 普通消息溢出对应队列编号，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT32  uwNorOvPtr;             /**< 普通消息溢出缓存指针，异常类型为MSGM_EXC_TYPE_NOR_OV，且配置了溢出缓存区时记录 */
    UINT8   ucShOvQue;              /**< 共享消息溢出队列ID，异常类型为MSGM_EXC_TYPE_SH_OV时记录 */
    UINT8   ucSynLostQue;           /**< 同步消息阻塞丢失队列ID，异常类型为MSGM_EXC_TYPE_SYNC_LOST时记录 */
    UINT8   ucNorOvLostCnt;         /**< 普通消息溢出阻塞丢失计数，异常类型为MSGM_EXC_TYPE_NOR_OV_LOST时记录 */
    UINT8   ucNorOvLostQue;         /**< 普通消息溢出阻塞丢失的第一个队列号，异常类型为MSGM_EXC_TYPE_NOR_OV_LOST时记录 */
    UINT32  uwCreditVioError;       /**< 普通消息Credit不匹配信息(寄存器MSGM_CRED_VIO), 异常类型为MSGM_EXC_TYPE_CRED_MM时记录  */
    UINT32  uwLsiVioBusError;       /**< LSI总线错误的类型记录(寄存器MSGM_LSI_VIO), 异常类型为MSGM_EXC_TYPE_LSI_ERR时记录  */
    UINT32  uwLsiVioBusErrorAddr;   /**< LSI总线错误时的访问地址(寄存器MSGM_LSI_VIO_ADDR),异常类型为MSGM_EXC_TYPE_LSI_ERR时记录 */
}MSGM_EXC_INFO_S;

/**
 *@ingroup SRE_exc
 * 寄存器信息结构
 *
 * 描述:SD6182/SD6157平台下的异常触发时保存的寄存器信息。
 *
 * 注意:以下寄存器名称去掉类型前缀‘uw’，即对应芯片手册中的寄存器名称
 * 可接管的异常类型:除了包括系统自带的64种异常外，还可以接管以下异常类型
 * #define OS_EXCCAUSE_WRITEERROR           67   //write error异常
 * #define OS_EXCCAUSE_ECCERROR             68   //核内 ECC异常
 * #define OS_EXCCAUSE_NMIERROR             69   //NMI中断
 * #define OS_EXCCAUSE_RESET_REENTRY        70   //复位向量重入异常
 * #define OS_EXCCAUSE_DOUBLEERROR          71   //double异常
 * #define OS_EXCCAUSE_FATALERROR           72   //致命错误异常
 * #define OS_EXCCAUSE_STACKOVERFLOW        73   //栈越界异常
 * #define OS_EXCCAUSE_HWSEMERROR           74   //硬件信号量异常
 * #define OS_EXCCAUSE_INSTRUCTION_BP       75   //指令断点异常
 * #define OS_EXCCAUSE_DATA_BP              76   //数据断点异常
 * #define OS_EXCCAUSE_HACERROR             77   //HAC异常
 * #define OS_EXCCAUSE_MSGM_ERROR           78   //Msgm错误异常
 * #define OS_EXCCAUSE_MSGQBUSERROR         79   //msgQ bus err异常
 */
typedef struct tagTensilicaExcRegInfo
{
    UINT32 uwPC;            /**< pc指针地址                             */
    UINT32 uwPS;            /**< 处理器状态                             */
    UINT32 uwEXCCAUSE;      /**< 上一次异常类型                         */
    UINT32 uwEXCVADDR;      /**< 上一次读取、加载或转储异常的虚拟地址   */
    UINT32 uwLBEG;          /**< 循环起始地址                           */
    UINT32 uwLEND;          /**< 循环结束地址                           */
    UINT32 uwLCOUNT;        /**< 循环计数器寄存器                       */
    UINT32 uwSAR;           /**< 移位寄存器                             */
    UINT32 auwA[64];        /**< A组64个通用寄存器                      */
    UINT32 uwWINDOWBASE;    /**< 目前AR REG窗口位置寄存器               */
    UINT32 uwWINDOWSTART;   /**< AR REG窗口pending寄存器                */
    UINT32 uwDEPC;          /**< double 异常程序寄存器                  */
    UINT32 uwBR;            /**< br 寄存器                              */
    UINT32 uwEPC1;          /**< lv1 异常PC寄存器                       */
    UINT32 uwEPC2;          /**< lv2 异常PC寄存器                       */
    UINT32 uwEPC3;          /**< lv3 异常PC寄存器                       */
    UINT32 uwEPC4;          /**< lv4 异常PC寄存器                       */
    UINT32 uwEPC5;          /**< lv5 异常PC寄存器                       */
    UINT32 uwEPS2;          /**< lv2 异常状态寄存器                     */
    UINT32 uwEPS3;          /**< lv3 异常状态寄存器                     */
    UINT32 uwEPS4;          /**< lv4 异常状态寄存器                     */
    UINT32 uwEPS5;          /**< lv5 异常状态寄存器                     */
    UINT32 uwEXCSAVE1;      /**< lv1 异常保存寄存器                     */
    UINT32 uwEXCSAVE2;      /**< lv2 异常保存寄存器                     */
    UINT32 uwEXCSAVE3;      /**< lv3 异常保存寄存器                     */
    UINT32 uwEXCSAVE4;      /**< lv4 异常保存寄存器                     */
    UINT32 uwEXCSAVE5;      /**< lv5 异常保存寄存器                     */
    UINT32 uwINTENABLE;     /**< 中断使能寄存器                         */
    UINT32 uwINTERRUPT;     /**< 中断pending寄存器                      */
    UINT32 uwCCOMPARE0;     /**< 比较寄存器0                            */
    UINT32 uwCCOMPARE1;     /**< 比较寄存器1                            */
    UINT32 uwCCOUNT;        /**< 比较寄存器计数值                       */
    UINT32 uwCPENABLE;      /**< 协处理使能寄存器                       */
    UINT32 uwVECBASE;       /**< 动态向量表基址                         */
    UINT32 uwDBREAKA0;      /**< 数据断点地址0                          */
    UINT32 uwDBREAKA1;      /**< 数据断点地址1                          */
    UINT32 uwDBREAKC0;      /**< 数据断点控制寄存器0                    */
    UINT32 uwDBREAKC1;      /**< 数据断点控制寄存器1                    */
    UINT32 uwDEBUGCAUSE;    /**< 上一次debug异常原因                    */
    UINT32 uwIBREAK0;       /**< 指令断点地址0                          */
    UINT32 uwIBREAK1;       /**< 指令断点地址1                          */
    UINT32 uwIBREAKENABLE;  /**< 指令断点使能寄存器                     */
    UINT32 uwICOUNT;        /**< 指令计数器                             */
    UINT32 uwICOUNTLEVEL;   /**< 指令计数等级阈值寄存器                 */
    UINT32 uwResvered0;     /**< 对齐保留,不能去掉，切记                */
    ECC_REGS_S stEccRegInfo;/**< ECC异常保存寄存器信息                  */
} EXC_REGS_S;

#elif (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
typedef struct tagAXExcRegInfo
{
    UINT32 uwCPSR;  /**< CPSR程序状态寄存器，发生预取指令异常时，由于硬件机制的问题，此寄存器的T标志位会被置为1                        */
    UINT32 uwSCTLR; /**< 异常时的SCTLR寄存器                                                                                           */
    UINT32 uwDFAR;  /**< 异常时的DFAR寄存器                                                                                            */
    UINT32 uwDFSR;  /**< 异常时的DFSR寄存器                                                                                            */
    UINT32 uwIFSR;  /**< 异常时的IFSR寄存器                                                                                            */
    UINT32 uwR0;    /**< RO寄存器                                                                                                      */
    UINT32 uwR1;    /**< R1寄存器                                                                                                      */
    UINT32 uwR2;    /**< R2寄存器                                                                                                      */
    UINT32 uwR3;    /**< R3寄存器                                                                                                      */
    UINT32 uwR4;    /**< R4寄存器                                                                                                      */
    UINT32 uwR5;    /**< R5寄存器                                                                                                      */
    UINT32 uwR6;    /**< R6寄存器                                                                                                      */
    UINT32 uwR7;    /**< R7寄存器                                                                                                      */
    UINT32 uwR8;    /**< R8寄存器                                                                                                      */
    UINT32 uwR9;    /**< R9寄存器                                                                                                      */
    UINT32 uwR10;   /**< R1O寄存器                                                                                                     */
    UINT32 uwR11;   /**< R11寄存器                                                                                                     */
    UINT32 uwR12;   /**< R12寄存器                                                                                                     */
    UINT32 uwSP;    /**< 程序栈指针                                                                                                    */
    UINT32 uwLR;    /**< 程序返回地址，即异常时的下一条指令。发生软件触发异常、致命错误异常和栈越界异常时，由于硬件机制问题，此值不准确*/
    UINT32 uwPC;    /**< 异常时的PC指针(预取指令异常时，记录做4字节对齐处理后的下一条指令地址，其他异常时，记录异常时的PC值)           */
}EXC_REGS_S;

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:非法指令异常。
 */
#define OS_EXCEPT_UNDEF_INSTR      1

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:软件触发异常。
 */
#define OS_EXCEPT_SWI              2

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:预取指令异常。
 */
#define OS_EXCEPT_PREFETCH_ABORT   3

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:数据中止异常。
 */
#define OS_EXCEPT_DATA_ABORT       4

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:快速中断异常。
 */
#define OS_EXCEPT_FIQ              5

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:致命错误异常。
 */
#define OS_EXCEPT_FATALERROR       6

/**
 *@ingroup SRE_exc
 *Cortex-AX异常具体类型:栈越界异常。
 */
#define OS_EXCEPT_STACKOVERFLOW    7

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:正常消息队列溢出错误。
 */
#define MSGM_EXC_TYPE_NOR_OV            0

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:正常消息队列溢出丢失错误。
 */
#define MSGM_EXC_TYPE_NOR_OV_LOST       1

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:正常消息队列credit失配错误。
 */
#define MSGM_EXC_TYPE_CRED_MM           2

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:共享消息队列溢出错误。
 */
#define MSGM_EXC_TYPE_SH_OV             3

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:同步队列入队消息非法错误。
 */
#define MSGM_EXC_TYPE_SYNC_ERR          4

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:同步消息队列超时错误。
 */
#define MSGM_EXC_TYPE_SYNC_TOT          5

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:AXI总线decerr错误。
 */
#define MSGM_EXC_TYPE_AXI_DECERR        6

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:AXI总线slverr错误。
 */
#define MSGM_EXC_TYPE_AXI_SLVERR        7

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:LSI总线错误。
 */
#define MSGM_EXC_TYPE_LSI_ERR           8

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:LSI总线vmid或lock权限错误。
 */
#define MSGM_EXC_TYPE_LSI_VMLOCK_ERR    9

/**
 *@ingroup SRE_exc
 *SD6183 MSGM异常类型:同步队列消息发送阻塞丢失错误。
 */
#define MSGM_EXC_TYPE_SYNC_LOST         14

/*
 *@ingroup SRE_exc
 * 寄存器信息结构
 *
 * 描述:SD6183平台下的异常触发时保存的MSGM异常寄存器信息。
*/
typedef struct tagMsgmExcInfo
{
    UINT8   ucExcMsgm;              /**< 异常MSGM标识，0表示GMSGM，1表示LMSGM */
    UINT8   ucExcType;              /**< MSGM异常类型 */
    UINT8   ucSynTotQue;            /**< 同步消息超时队列ID，异常类型为MSGM_EXC_TYPE_SYNC_TOT时记录 */
    UINT8   ucSynErrMsgQue;         /**< 同步消息无效队列ID，异常类型为MSGM_EXC_TYPE_SYNC_ERR时记录 */
    UINT32  uwSynErrMsgData;        /**< 同步消息无效高32bit数据，异常类型为MSGM_EXC_TYPE_SYNC_ERR时记录 */
    UINT8   ucNorOvCnt;             /**< 普通消息溢出计数，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT8   ucNorOvCore;            /**< 普通消息溢出对应核号，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT8   ucNorOvQport;           /**< 普通消息溢出对应QPort编号，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT8   ucNorOvQue;             /**< 普通消息溢出对应队列编号，异常类型为MSGM_EXC_TYPE_NOR_OV时记录 */
    UINT32  uwNorOvPtr;             /**< 普通消息溢出缓存指针，异常类型为MSGM_EXC_TYPE_NOR_OV，且配置了溢出缓存区时记录 */
    UINT8   ucShOvQue;              /**< 共享消息溢出队列ID，异常类型为MSGM_EXC_TYPE_SH_OV时记录 */
    UINT8   ucSynLostQue;           /**< 同步消息阻塞丢失队列ID，异常类型为MSGM_EXC_TYPE_SYNC_LOST时记录 */
    UINT8   ucNorOvLostCnt;         /**< 普通消息溢出阻塞丢失计数，异常类型为MSGM_EXC_TYPE_NOR_OV_LOST时记录 */
    UINT8   ucNorOvLostQue;         /**< 普通消息溢出阻塞丢失的第一个队列号，异常类型为MSGM_EXC_TYPE_NOR_OV_LOST时记录 */
    UINT32  uwCreditVioError;       /**< 普通消息Credit不匹配信息(寄存器MSGM_CRED_VIO), 异常类型为MSGM_EXC_TYPE_CRED_MM时记录  */
    UINT32  uwLsiVioBusError;       /**< LSI总线错误的类型记录(寄存器MSGM_LSI_VIO), 异常类型为MSGM_EXC_TYPE_LSI_ERR时记录  */
    UINT32  uwLsiVioBusErrorAddr;   /**< LSI总线错误时的访问地址(寄存器MSGM_LSI_VIO_ADDR),异常类型为MSGM_EXC_TYPE_LSI_ERR时记录 */
    UINT32  uwLsiVioBusErrorID;     /**< LSI总线访问命令错误命令ID和vmid(寄存器MSGM_LSI_VIO_ID) */
    UINT32  uwLsiVioVMLock;         /**< LSI权限异常错误类型(寄存器MSGM_LSI_VMLOCK_VIO) */
    UINT32  uwLsiVioVMLockAddr;     /**< LSI总线vmid或者lock权限访问命令错误地址(寄存器MSGM_LSI_VMLOCKVIO_ADDR) */
    UINT32  uwLsiVioVMLockID;       /**< LSI总线vmid或者lock权限访问命令错误命令ID和vmid(寄存器MSGM_LSI_VMLOCKVIO_ID) */
}MSGM_EXC_INFO_S;

/**
 *@ingroup SRE_exc
 * HIDSP异常寄存器信息结构
 *
 *
 */
typedef struct tagExcRegInfo
{
    UINT32  uwUSP;         /* 发生异常前的USP寄存器值                      */
    UINT32  uwSP;          /* 发生异常前的SSP寄存器值                      */
    UINT32  uwISR;         /* 发生异常后的异常相关ISR寄存器值              */
    UINT32  uwEMADDR;      /* 发生异常后的EMADDR寄存器值，导致异常的地址   */
    UINT32  uwLBEG0;
    UINT32  uwLEND0;
    UINT32  uwLCOUNT0;
    UINT32  uwPrex1;
    UINT32  uwLBEG1;
    UINT32  uwLEND1;
    UINT32  uwLCOUNT1;
    UINT32  uwCIDR;
    UINT32  auwA[32];
    UINT32  auwV[16][4];
    UINT32  uwBX;
    UINT32  uwCBEGIN;
    UINT32  uwCEND;
    UINT32  uwPrex2;
    UINT32  uwPC;          /* 发生异常现场的PC寄存器值     */
    UINT32  uwPreSR;       /* 发生异常前的SR寄存器值       */
    UINT32  uwPreISR;      /* 发生异常前的ISR寄存器值      */
    UINT32  uwPreEmaddr;   /* 发生异常前的Emaddr寄存器值   */
}EXC_REGS_S;

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LDP,取数据cache奇偶校验错误。
 */
#define OS_DATA_LOAD_ERR_LDP        0

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LDT,取数据cache tag奇偶校验错误。
 */
#define OS_DATA_LOAD_ERR_LDT        1

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LSL,取二级数据错误(SLVERR)。
 */
#define OS_DATA_LOAD_ERR_LSL        2

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LDE,取数据二级地址错误(DECERR)。
 */
#define OS_DATA_LOAD_ERR_LDE        3

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LEE,取数据专用错误。
 */
#define OS_DATA_LOAD_ERR_LEE        4

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LUM,取数据非对齐错误。
 */
#define OS_DATA_LOAD_ERR_LUM        5

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LMH,MMU多重命中错误。
 */
#define OS_DATA_LOAD_ERR_LMH        6

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LMT,取数据MMU二级tag(二级TLB校验也包含在该异常类内)奇偶校验错误。
 */
#define OS_DATA_LOAD_ERR_LMT        7

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LPF,MMU页错误。
 */
#define OS_DATA_LOAD_ERR_LPF        8

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LPV, MMU的权限违规。
 */
#define OS_DATA_LOAD_ERR_LPV        9

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LXS,取数据MMU AXI二级数据错误(SLVERR)。
 */
#define OS_DATA_LOAD_ERR_LXS        10

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LXD,取数据MMU AXI二级地址错误(DECERR)。
 */
#define OS_DATA_LOAD_ERR_LXD        11

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LMU,取数据不支持的MMU页大小错误。
 */
#define OS_DATA_LOAD_ERR_LMU        12

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_LOAD_ERR, 取数据异常
 *HIDSP异常具体类型:LMP,MPU错误。
 */
#define OS_DATA_LOAD_ERR_LMP        13

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SUM, 存数据非对齐内存错误。
 */
#define OS_DATA_STORE_MMU_ERR_SUM   14

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SMH, MMU多重命中错误。
 */
#define OS_DATA_STORE_MMU_ERR_SMH   15

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SIM, 隐式压栈时存数据MMU错误。
 */
#define OS_DATA_STORE_MMU_ERR_SIM   16

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SPF, MMU页错误。
 */
#define OS_DATA_STORE_MMU_ERR_SPF   17

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SPV, MMU的权限违规。
 */
#define OS_DATA_STORE_MMU_ERR_SPV   18

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SXS, 存数据MMU AXI二级数据错误(SLVERR)。
 */
#define OS_DATA_STORE_MMU_ERR_SXS   19

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SXD, 存数据MMU AXI二级地址错误(DECERR)。
 */
#define OS_DATA_STORE_MMU_ERR_SXD   20

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SMT, 存数据MMU二级tag(二级TLB校验也包含在该异常类内)奇偶校验错误。
 */
#define OS_DATA_STORE_MMU_ERR_SMT   21

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DATA_STORE_MMU_ERR, 存数据MMU异常
 *HIDSP异常具体类型:SMU, 存数据不支持的MMU页大小错误。
 */
#define OS_DATA_STORE_MMU_ERR_SMU   22

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_ILLEGAL, 非法指令异常
 *HIDSP异常具体类型:IOP, 非法操作码-未定义的操作码或者遇到非法指令。
 */
#define OS_ILLEGAL_IOP              23

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_ILLEGAL, 非法指令异常
 *HIDSP异常具体类型:IIT, 使用非法的指令编码类型。
 */
#define OS_ILLEGAL_IIT              24

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_ILLEGAL, 非法指令异常
 *HIDSP异常具体类型:IIO, 使用非法的指令操作数。
 */
#define OS_ILLEGAL_IIO              25

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_ILLEGAL, 非法指令异常
 *HIDSP异常具体类型:IIC, VLIW里使用了非法的指令组合。
 */
#define OS_ILLEGAL_IIC              26

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_ILLEGAL, 非法指令异常
 *HIDSP异常具体类型:IVO, 非法的VLIW起始地址，VLIW起始地址必须为3的倍数。
 */
#define OS_ILLEGAL_IVO              27

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_ILLEGAL, 非法指令异常
 *HIDSP异常具体类型:IVW, 非法VLIW的宽度-VLIW太宽。
 */
#define OS_ILLEGAL_IVW              28

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PPE, 指令cache奇偶校验错误。
 */
#define OS_PFETCHERR_PPE            29

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PMT, 指令MMU二级tag奇偶校验错误。
 */
#define OS_PFETCHERR_PMT            30

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PFB, 填充总线错误。
 */
#define OS_PFETCHERR_PFB            31

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PTP, 指令tag奇偶校验错误。
 */
#define OS_PFETCHERR_PTP            32

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PMH, MMU多重命中错误。
 */
#define OS_PFETCHERR_PMH            33

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PPF, MMU页错误。
 */
#define OS_PFETCHERR_PPF            34

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PPV, MMU的权限违规。
 */
#define OS_PFETCHERR_PPV            35

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PXS, 程序MMU AXI二级数据错误(SLVERR)。
 */
#define OS_PFETCHERR_PXS            36

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PXD, 程序MMU AXI地址错误(DECERR)。
 */
#define OS_PFETCHERR_PXD            37

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PPS, MMU不支持的页大小错误。
 */
#define OS_PFETCHERR_PPS            38

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PMP, MPU错误。
 */
#define OS_PFETCHERR_PMP            39

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PRIVILEGE_ERR, 权限异常
 *HIDSP异常具体类型:非特权模式访问了特权模式下资源的权限错误。
 */
#define OS_PRIVILEGE_ERR_PER        40

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DIV_ZERO_ERR, 除0异常
 *HIDSP异常具体类型:除数为0的异常。
 */
#define OS_DIV_ZERO_ERR_ZDE         41

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_DEBUG_EXCP, debug异常
 *HIDSP异常具体类型:debug异常。
 */
#define OS_DEBUG_EXCP_DBG           42

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_SYSCALL, syscall异常
 *HIDSP异常具体类型:syscall异常。
 */
#define OS_SYSCALL_SYS              43

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_CPENABLE_PRO, 矢量寄存器异常
 *HIDSP异常具体类型:矢量寄存器异常。
 */
#define OS_CPENABLE_PRO_CSP         44

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_MSG_QUE_ERR, MSGQ异常
 *HIDSP异常具体类型:MSGQ异常。
 */
#define OS_MSG_QUE_ERR_MSA          45

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_MSG_QUE_ERR, MSGQ异常
 *HIDSP异常具体类型:不存在的消息检测错误。
 */
#define OS_MSG_QUE_ERR_MSC          46

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_PFETCH_ERR, 预取指令异常
 *HIDSP异常具体类型:PFS, 指令预取L2地址错误(DECERR)。
 */
#define OS_PFETCHERR_PFS            47

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_FATALERROR, 致命错误异常
 *HIDSP异常具体类型:发生OS致命错误异常。
 */
#define OS_EXCCAUSE_FATALERROR      48

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_STACKOVERFLOW, 栈越界异常
 *HIDSP异常具体类型:发生任务栈越界异常。
 */
#define OS_EXCCAUSE_STACKOVERFLOW   49

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_NMIERROR, NMI中断
 *HIDSP异常具体类型:NMI中断。
 */
#define OS_EXCCAUSE_NMIERROR        69

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_PCC_ERROR, PCC错误异常
 *HIDSP异常具体类型:PCC错误异常。
 */
#define OS_EXCCAUSE_PCC_ERROR               70

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_DCC_ERROR, DCC错误异常
 *HIDSP异常具体类型:DCC错误异常。
 */
#define OS_EXCCAUSE_DCC_ERROR               71

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_MMU_ERROR, MMU错误异常
 *HIDSP异常具体类型:MMU错误异常。
 */
#define OS_EXCCAUSE_MMU_ERROR               72
/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_HWSEMERROR, 硬件信号量异常。
 *HIDSP异常具体类型:硬件信号量异常。
 */
#define OS_EXCCAUSE_HWSEMERROR      74

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_MSGM_ERROR, MSGM错误异常
 *HIDSP异常具体类型:MSGM异常。
 */
#define OS_EXCCAUSE_MSGM_ERROR      78

/**
 *@ingroup SRE_exc
 *HIDSP异常分类:OS_EXCCAUSE_MCHWTMRERROR, 全局硬件定时器错误异常
 *HIDSP异常具体类型:全局硬件定时器异常。
 */
#define OS_EXCCAUSE_MCHWTMRERROR    80

/**
 *@ingroup SRE_exc
 * SD6183平台下，对于不能识别CPU ID的硬件信号量异常记录的核号。
 */
#define  HWSEM_ERR_DEFAULT_CORE            0xff

/**
 *@ingroup SRE_exc
 *SD6183平台下发生全局硬件信号量异常标志。
 */
#define  GHWSEM_ERR_FLAG                   0x1

/**
 *@ingroup SRE_exc
 *SD6183平台下发生局部硬件信号量异常标志。
 */
#define  LHWSEM_ERR_FLAG                   0x2

/**
 * @ingroup SRE_exc
 * 硬件信号量记录的错误信息类型，1-6共6种，HWSEM_ERR_S中的ucHwsemErrTpye记录。
 * SD6183的错误结构体信息。
 */
typedef enum tagHiDSPHwSemErrType
{
    OS_HWSEM_ERR_PEND_IN_QUEUE_SEM    = 1,      /**< 申请在队列中继续申请获取                          */
    OS_HWSEM_ERR_PEND_BUSY_SEM        = 2,      /**< 申请获取已经获取到的信号量                        */
    OS_HWSEM_ERR_POST_OTHER_CORE_SEM  = 3,      /**< 释放其他cpu占用的信号量                           */
    OS_HWSEM_ERR_CPUID_OVERFLOW       = 4,      /**< 申请或释放的CPUID越界                             */
    OS_HWSEM_ERR_READ_DIRECT_REG      = 5,      /**< 非查询模式下读Direct寄存器                        */
    OS_HWSEM_ERR_WRITE_INDIRECT_REG   = 6,      /**< 非队列模式下写InDirect寄存器                      */
} HWSEM_ERR_TYPE_E;

/**
 * @ingroup SRE_exc
 * 硬件信号量记录的COMM类错误信息类型，按bit置位，可能有多个bit被置上，HWSEM_ERR_S中的ucHwsemCommErrTpye记录。
 * SD6183的错误结构体信息。
 */
typedef enum tagHiDSPHwSemCommErrType
{
    OS_HWSEM_ERR_1BIT_ECC             = 0,   /**< Bit0置位表示:队列或者组合模式下，存储的申请CPU ID 1bit ECC错误 */
    OS_HWSEM_ERR_2BIT_ECC             = 1,   /**< Bit1置位表示:队列或者组合模式下，存储的申请CPU ID 2bit ECC错误 */
    OS_HWSEM_ERR_SW_ACCESS_VMID       = 2,   /**< Bit2置位表示:软件访问的VMID错误                                */
    OS_HWSEM_ERR_CPU_ID_INVALID       = 3,   /**< Bit3置位表示:不能识别CPUID的信号量错误                         */
    OS_HWSEM_ERR_WRITE_LOCK_REG       = 4,   /**< Bit4置位表示:Lock情况下写受lock保护寄存器                      */
}HWSEM_ERR_COMM_TYPE_E;

typedef struct tagHiDSPHwSemErrInfo
{
    UINT8  ucHwSemType;               /**< 出错的硬件信号量类型：GHWSEM_ERR_FLAG(表示全局)或LHWSEM_ERR_FLAG(表示局部)*/
    UINT8  ucHwsemClustId;            /**< 簇ID，出错的硬件信号量类型为局部时有效                                    */
    UINT8  ucHwSemId;                 /**< 出错的硬件信号量ID                                                        */
    UINT8  ucHwsemCoreId;             /**< 引起硬件信号量错误的核号，无效时为#HWSEM_ERR_DEFAULT_CORE                 */
    UINT8  ucHwsemOwner;              /**< 出错的硬件信号量的持有核的核号，无效时为#HWSEM_ERR_DEFAULT_CORE           */
    UINT8  ucHwsemQueueCPUNum;        /**< 出错的硬件信号量的队列中的CPU数量                                         */
    UINT8  ucHwsemErrTpye;            /**< 硬件信号量记录的错误类型，1-6共6种， 参照SD6183枚举HWSEM_ERR_TYPE_E       */
    UINT8  ucHwsemCommErrTpye;        /**< 硬件信号量COMM类错误类型，按bit记录，参照SD6183枚举HWSEM_ERR_COMM_TYPE_E  */
} HWSEM_ERR_S;

/**
 * @ingroup SRE_exc
 * 全局硬件定时器记录的错误信息类型，1-3共3种，MCHWTMR_EXC_INFO_S中的uwMcHwtmrErrTpye记录。
 * SD6183的错误结构体信息。
 */
typedef enum tagMcHwtmrErrType
{
    OS_MCHWTMR_ERR_VMID    = 1,      /**< VMID检查出错               */
    OS_MCHWTMR_ERR_LOCK    = 2,      /**< 违反LOCK保护               */
    OS_MCHWTMR_ERR_VMLOCK  = 3,      /**< VMID检查出错且违反LOCK保护 */
} MCHWTMR_ERR_TYPE_E;

typedef struct tagMcHwtmrErrInfo
{
    UINT32  uwMcHwtmrErrTpye;        /**< 全局硬件定时器错误类型，1-3共3种， 参照SD6183枚举MCHWTMR_ERR_TYPE_E*/
} MCHWTMR_EXC_INFO_S;

typedef struct tagMcDCCErrInfo
{
    UINT32  uwDccIntStatus;           /**< 出错的DCC错误中断状态*/
    UINT32  uwDccL2WErr;              /**< Data Cache L2 Memory Access Error Attribute Register      */
    UINT32  uwDccEccAddr;             /**< Data Cache ECC Error Address                              */
} DCC_ERR_S;

#endif

#if (OS_OPTION_KERNEL_PROCESS == YES)
/*
 *@ingroup SRE_exc
 *
 *用户可以看到异常信息
 */
typedef struct tageExcListObject
{
    struct tageExcListObject *pstPrev;
    struct tageExcListObject *pstNext;

}EXC_LIST_OBJECT_S;

#endif


typedef struct tagExcInfo
{
    CHAR        acOSVer[OS_SYS_OS_VER_LEN];                  /**< OS版本号                                         */
    CHAR        acAppVer[OS_SYS_APP_VER_LEN];                /**< 产品版本号                                       */
    UINT32      uwExcCause;                                  /**< 异常原因                                         */

    UINT32      uwThreadType;                                /**< 异常前的线程类型                                 */
    UINT32      uwThreadID;                                  /**< 异常前的线程ID, 该ID组成濉禩ID = LTID | ProcessID | COREID | GTID>*/

#if (OS_OPTION_KERNEL_PROCESS == YES)

    EXC_LIST_OBJECT_S stExcInfoList;                         /**< 进程异常信息链表指针                             */

#endif

    UINT16      usByteOrder;                                 /**< 字节序                                           */
    UINT16      usCpuType;                                   /**< CPU类型                                          */
    UINT32      uwCpuID;                                     /**< CPU ID                                           */
    CPU_TICK    stCpuTick;                                   /**< CPU Tick                                         */
    UINT32      uwNestCnt;                                   /**< 异常嵌套计数                                     */
    UINT32      uwSp;                                        /**< 异常前栈指针                                     */
    UINT32      uwStackBottom;                               /**< 异常前栈底                                       */
    EXC_REGS_S  stRegInfo;                                   /**< 异常发生时的核内寄存器上下文信息，82\57必须位于152字节处，若有改动，需更新sre_platform.eh中的OS_EXC_REGINFO_OFFSET宏 */

#if ((OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_DSP220)||(OS_HARDWARE_PLATFORM == OS_HACCC))
    CSTK_FRAME_INFO_S   astStackLayer[EXC_CSTK_DEAPTH];      /**< 调用栈解析结果                                   */
    HWSEM_ERR_S     stHwSemErrInfo;                          /**< 硬件信号量异常保存寄存器信息                     */
    MSGM_EXC_INFO_S stMsgmExcInfo;                           /**< MSGM异常信息                                     */
    UINT32          uwMsgqBusErrorCoreId;                    /**< 发生msgQ bus error异常的核号                     */
#endif

#if ((OS_HARDWARE_PLATFORM == OS_RISC170)||(OS_HARDWARE_PLATFORM == OS_DSP170))
    CSTK_FRAME_INFO_S   astStackLayer[EXC_CSTK_DEAPTH];      /**< 调用栈解析结果                                   */
    HWSEM_ERR_S         stHwSemErrInfo;                      /**< 硬件信号量异常保存寄存器信息                     */
    IPC_STATUS_S        auwIpcStatus[8];                     /**< ipc邮箱状态，每个核只有8个mailbox                */
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
    HWSEM_ERR_S     stHwSemErrInfo;
    DCC_ERR_S       stDccErrInfo;                            /**< DCC错误信息                                      */
    MSGM_EXC_INFO_S stMsgmExcInfo;                           /**< MSGM异常信息                                     */
    MCHWTMR_EXC_INFO_S stMcHwtmrExcInfo;                     /**< 全局硬件定时器异常信息                           */
#endif
} EXC_INFO_S;

/**
 *@ingroup SRE_exc
 *@brief 保存异常的处理状态函数类型定义。
 *
 *@par 描述:
 *在单核复位时钩子执行失败的返回信息通过该钩子函数进行保存。
 *@attention 无。
 *
 *@param uwState [IN] 类型#UINT32，异常处理的出错信息。
 *
 *@retval 无。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件。
 *@since UniDSP V100R001C01
 *@see 无
 */
typedef VOID (* EXC_STATE_TRACE_HOOK)(UINT32 uwState);

/**
 *@ingroup SRE_exc
 *@brief 临终遗言钩子函数类型定义。
 *
 *@par 描述:
 *通过该函数类型定义临终遗言钩子函数。
 *@attention 无。
 *
 *@param 无。
 *
 *@retval 无。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件。
 *@since UniDSP V100R001C01
 *@see 无
 */
typedef VOID (* SRE_LASTWORDS_FUNC)(VOID);

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

/**
 *@ingroup SRE_exc
 *异常处理函数返回类型:系统在发生异常后(并做完相关处理后)继续运行。
 */
#define SRE_EXC_PROC_TYPE_RETURN            0

/**
 *@ingroup SRE_exc
 *异常处理函数返回类型:系统在发生异常后(并做完相关处理后)进入死循环，等待重启。
 */
#define SRE_EXC_PROC_TYPE_NO_RETURN         1

/**
 *@ingroup SRE_exc
 *异常处理函数返回类型:系统在发生异常后(并做完相关处理后)跳过异常指令继续运行。
 */
#define SRE_EXC_PROC_TYPE_RETURN_SKIP_INST  2

/**
 *@ingroup SRE_exc
 *@brief 异常处理函数类型定义。
 *
 *@par 描述:
 *通过异常处理函数类型定义异常处理函数钩子，记录异常信息。
 *@attention 无。
 *
 *@param pstExcRegs [IN] 类型#EXC_REGS_S *，异常时寄存器信息。
 *
 *@retval SRE_EXC_PROC_TYPE_RETURN，系统在发生异常后(并做完相关处理后)继续运行。
 *@retval SRE_EXC_PROC_TYPE_NO_RETURN，系统在发生异常后(并做完相关处理后)进入死循环，等待重启。
 *@retval SRE_EXC_PROC_TYPE_RETURN_SKIP_INST，系统在发生异常后(并做完相关处理后)跳过异常指令继续运行。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件。
 *@since UniDSP V100R001C01
 *@see 无
 */
typedef UINT32 (* EXC_PROC_FUNC)(EXC_INFO_S *pstExcInfo);

#else
/**
 *@ingroup SRE_exc
 *@brief 异常处理函数类型定义。
 *
 *@par 描述:
 *通过异常处理函数类型定义异常处理函数钩子，记录异常信息。
 *@attention 无。
 *
 *@param pstExcRegs [IN] 类型#EXC_REGS_S *，异常时寄存器信息。
 *
 *@retval TRUE，系统在发生异常后(并做完相关处理后)进入死循环，等待重启。
 *@retval FALSE，系统在发生异常后(并做完相关处理后)继续运行。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件。
 *@since UniDSP V100R001C01
 *@see 无
 */
typedef BOOL (* EXC_PROC_FUNC)(EXC_INFO_S *pstExcInfo);
#endif

/**
 *@ingroup SRE_exc
 *@brief Hac超时自清异常处理函数类型定义。
 *
 *@par 描述:
 *通过Hac超时自清异常处理函数类型定义异常处理函数钩子，产品通过查看Hac超时寄存器判断是否存在超时，如果存在超时返回TRUE(1)，如果不存在超时，说明系统出现异常，返回FALSE(0),系统进入异常接管。
 *@attention 无。
 *
 *@param VOID
 *
 *@retval TRUE，系统检测到HAC超时，返回之后OS做中断丢弃处理。
 *@retval FALSE，系统未检测到HAC超时，返回之后OS做异常处理。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件。
 *@since UniDSP V200R003C06
 *@see 无
 */
typedef BOOL (* HACTIMEOUT_PROC_FUNC)(VOID);

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 *@ingroup SRE_exc
 *模块配置信息结构体。
 */
typedef struct tagExcModInfo
{
    EXC_PROC_FUNC           pfnExcepHook;           /**< 异常时用户注册的函数钩子                    */
    VOID                    *pResetNoLoseMemAddr;  /**< 复位不丢失内存的起始地址                    */
    UINT32                  uwResetNoLoseMemSize;   /**< 复位不丢失内存的大小                        */
} EXC_MOD_INFO_S;

#else
/**
 *@ingroup SRE_exc
 *模块配置信息结构体。
 */
typedef struct tagExcModInfo
{
    HACTIMEOUT_PROC_FUNC    pfnHacExtHook;          /**< Hac异常钩子                                */
    EXC_PROC_FUNC           pfnExcepHook;           /**< 异常时用户注册的函数钩子                    */
    UINT32                  uwStackSize;            /**< 发生异常时保存堆栈的大小                    */
    VOID                    *pDoubleExcStackStart;  /**< DoubleException堆栈起始地址                */
    UINT32                  uwDoubleExcStackSize;   /**< DoubleException堆栈大小                    */
} EXC_MOD_INFO_S;
#endif

/**
 *@ingroup SRE_exc
 *@brief 异常缓冲区首地址和长度获取函数。
 *
 *@par 描述:
 *获取异常信息缓冲区的首地址与大小。
 *@attention 异常发生时，可根据缓冲区的首地址和大小，进而获取到异常信息；无异常时，此间内存值为0。
 *
 *@param ppBufAddr [OUT] 类型#VOID **，返回缓冲区首地址。
 *@param puwBufLen [OUT] 类型#UINT32 *，缓冲区长度。
 *
 *@retval #OS_ERRNO_EXC_PARA_INVLAID 0x02001c02，入参指针为空。
 *@retval #SRE_OK                    0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件
 *@since UniDSP V100R001C01
 *@see 无
 */
extern UINT32 SRE_ExcGetBufInfo(VOID **ppBufAddr, UINT32 *puwBufLen);

/**
 *@ingroup SRE_exc
 *@brief 用户注册异常处理钩子。
 *
 *@par 描述:
 *注册异常处理钩子。
 *@attention
 * <ul>
 * <li>当多次注册该钩子时，最后一次注册的钩子生效。
 * <li>注册的钩子函数不能为空，即一旦注册钩子函数，不能通过注册空函数将其取消。
 * </ul>
 *
 *@param pfnHook [IN] 类型#EXC_PROC_FUNC，钩子函数。
 *
 *@retval #OS_ERRNO_EXC_REG_HOOK_PTR_NULL 0x02001c09，钩子函数为空
 *@retval #SRE_OK 0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件
 *@since UniDSP V100R001C02
 *@see 无
 */
extern UINT32 SRE_ExcRegHook( EXC_PROC_FUNC pfnHook );

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 *@ingroup SRE_exc
 *@brief 用户注册Hac超时自清异常处理用户钩子。
 *
 *@par 描述:
 *注册Hac超时自清异常处理用户钩子。
 *@attention 当多次注册该钩子时，最后一次注册的钩子生效。
 *
 *@param pfnHook [IN] 类型#HACTIMEOUT_PROC_FUNC，钩子函数。
 *
 *
 *@retval #OS_ERRNO_EXC_REG_HOOK_PTR_NULL 0x02001c09，钩子函数为空。
 *@retval #SRE_OK 0x00000000，成功返回。
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件。
 *@since UniDSP V200R003C06
 *@see 无
 */
extern UINT32 SRE_HacTimeOutCheckHook( HACTIMEOUT_PROC_FUNC pfnHook );
#endif

/**
 * @ingroup  SRE_exc
 * @brief 获取RTOSck异常入口地址。
 *
 * @par 描述:
 * Tensilica芯片以及HIDSP芯片提供有一个硬件TraceBuffer功能，可以实时循环记录指令执行流，当进入异常处理时，为避免TraceBuffer中的信息被异常处理本身的指令流覆盖，
 * 应该停止记录指令流。用户可以用这个API获取异常入口地址,设置到硬件Trace提供的一个结束寄存器，当PC与结束寄存器的值相同时，TraceBuffer自动停止
 * 指令流的记录。
 * @attention 无
 *
 * <ul>
 * <li>无</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 函数地址                  函数地址，异常处理的函数地址。
 * @par 依赖:
 * sre_exc.h：该接口声明所在的头文件。
 * @since UniDSP V200R003C05
 * @see 无
 */
extern VOID * SRE_ExcEntryGet(VOID);

/**
 *@ingroup SRE_exc
 *@brief 临终遗言钩子注册函数。
 *
 *@par 描述:
 *注册临终遗言钩子到临终遗言链表中。
 *@attention
 *
 *@param ptrHook [IN] 类型#SRE_LASTWORDS_FUNC，钩子函数。
 *
 *@retval #OS_ERRNO_HOOK_TYPE_INVALID  0x02001600，入参钩子类型非法
 *@retval #OS_ERRNO_HOOK_PTR_NULL      0x02001602，入参钩子地址为NULL
 *@retval #OS_ERRNO_HOOK_FULL          0x02001604，HOOK已满或配置个数为0
 *@retval #OS_ERRNO_HOOK_EXISTED       0x02001603，HOOK已存在
 *@retval #SRE_OK 0x00000000，成功返回。
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件
 *@since UniDSP V100R001C02
 *@see SRE_LastWordsDisHook
 */
#define SRE_LastWordsRegHook(pfnHook) SRE_HookAdd(OS_HOOK_LAST_WORDS, (OS_VOID_FUNC)(SRE_LASTWORDS_FUNC)pfnHook)

/**
 *@ingroup SRE_exc
 *@brief 临终遗言钩子取消函数。
 *
 *@par 描述:
 *将已注册的临终遗言钩子从链表中删除。
 *@attention 无
 *
 *@param ptrHook [IN] 类型#SRE_LASTWORDS_FUNC，钩子函数。
 *
 *@retval #OS_ERRNO_HOOK_TYPE_INVALID  0x02001600，入参钩子类型非法
 *@retval #OS_ERRNO_HOOK_PTR_NULL      0x02001602，入参钩子地址为NULL
 *@retval #OS_ERRNO_HOOK_NOT_EXISTED   0x02001605，HOOK不存在
 *@retval #SRE_OK 0x00000000，成功返回。
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件
 *@since UniDSP V100R001C02
 *@see SRE_LastWordsRegHook
 */
#define SRE_LastWordsDisHook(pfnHook) SRE_HookDel(OS_HOOK_LAST_WORDS, (OS_VOID_FUNC)(SRE_LASTWORDS_FUNC)pfnHook)

/**
 * @ingroup  SRE_exc
 * @brief 获取异常向量表地址。
 *
 * @par 描述:
 * 获取异常向量表地址。
 *
 * @attention
 * <ul>
 * <li>该操作仅在Cortex-AX平台下支持。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #任意值       地址，异常向量表的地址
 * @par 依赖:
 * <ul><li>sre_exc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern VOID * SRE_ExcGetVectorTable(VOID);

/**
 *@ingroup SRE_exc
 *@brief 单核复位资源回收。
 *
 *@par 描述:
 *单核复位资源回收。
 *@attention
 * <ul>
 * <li>该接口仅支持SD6182芯片。</li>
 * <li>回收本核创建的硬件信号量资源、核间消息所占的共享内存资源、hunt、核间信号量占用的1号分区资源。
 * </ul>
 *
 *@param 无
 *
 *@retval 无
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件
 *@since RTOSck V100R003C00
 *@see 无
 */
extern VOID SRE_ExcSingleCoreReclaim();

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 *@ingroup SRE_exc
 *@brief 异常信息打印接口。
 *
 *@par 描述:
 *打印异常信息。
 *@attention
 * <ul>
 * <li>该接口仅支持Cortex-AX芯片。</li>
 * </ul>
 *
 *@param pstExcInfo [IN] 类型#EXC_INFO_S*，异常信息结构体指针。
 *
 *@retval 无
 *
 *@par 依赖:
 *sre_exc.h：该接口声明所在的头文件
 *@since RTOSck V100R005C00
 *@see 无
 */
extern VOID SRE_ExcInfoPrintf(EXC_INFO_S *pstExcInfo);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_EXC_H */



