/**
 * @file sre_shell.h
 *
 * Copyright(C), 2011-2011, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：Shell模块对外头文件。 \n
 */

#ifndef __SRE_SHELL_H__
#define __SRE_SHELL_H__

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**@defgroup sre_shell Shell功能
  *@ingroup SRE_inspect
  */

/**
 *@ingroup sre_shell
 * Cortex-AX平台串口打印输出结束符。
 */
#define OS_SHELL_END_SIGN        0

 /**
 * @ingroup sre_shell
 * HShell错误码：调试命令注册时内存分配失败。
 *
 * 值: 0x02002d04
 *
 * 解决方案: 检查原先命令注册时内存分配空间是否已被释放以及所在分区空间是否已经用完。
 *
 */
#define OS_ERRNO_SHELL_CMDREG_MEMALLOC_ERROR                                    SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x04)

/**
 * @ingroup sre_shell
 * HShell错误码：生成TRANSID时，入参为空。
 *
 * 值: 0x02002d05
 *
 * 解决方案: 检查生成TRANSID 所需参数信息的合法性。
 *
 */
#define OS_ERRNO_SHELL_TRANSID_PARA_NULL                                        SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x05)

/**
 * @ingroup sre_shell
 * HShell错误码：生成TRANSID时，内存申请失败
 *
 * 值: 0x02002d06
 *
 * 解决方案:  检查生成TRANSID 时，原先申请的内存是否被释放以及所在内存分区空间是否被用完。
 *
 */
#define OS_ERRNO_SHELL_TRANSID_MEMALLOC_ERROR                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x06)

/**
 * @ingroup sre_shell
 * HShell错误码：Server向Channel返回的消息分发时消息指针为空。
 *
 * 值: 0x02002d09
 *
 * 解决方案:  检查适配层消息分发时入参消息指针的合法性。
 *
 */
#define OS_ERRNO_SHELL_RES_MSG_NULL                                             SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x09)

/**
 * @ingroup sre_shell
 * HShell错误码：Channel与Server之间发送的消息类型不合法。
 *
 * 值: 0x02002d0a
 *
 * 解决方案: 检查适配层消息分发时Channel与Server之间发送的消息类型的合法性。
 *
 */
#define OS_ERRNO_SHELL_RES_TYPE_ERROR                                           SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0a)

/**
 * @ingroup sre_shell
 * HShell错误码：SVR模块 服务端消息处理函数获取信息类型不合法。
 *
 * 值: 0x02002d0b
 *
 * 解决方案:  检查SVR模块 服务端消息处理函数获取信息类型的合法性。
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGTYPE_ERROR                                        SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0b)

/**
 * @ingroup sre_shell
 * HShell错误码：SVR模块svr 向通道驱动发数据时申请内存失败。
 *
 * 值: 0x02002d0c
 *
 * 解决方案: 检查SVR模块svr 向通道驱动发数据时原先内存是否已被释放以及所在内存分区空间是否被用完。
 *
 */
#define OS_ERRNO_SHELL_SVR_MEMALLOC_ERROR                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0c)

/**
 * @ingroup sre_shell
 * HShell错误码：SVR模块svr 端消息处理时发送消息分配消息内存空间失败。
 *
 * 值: 0x02002d0d
 *
 * 解决方案:  检查SVR模块svr 端消息处理时发送消息原先分配消息内存空间是否已被以及所在内存分区空间是否被用完。
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGALLOC_ERROR                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0d)

/**
 * @ingroup sre_shell
 * HShell错误码：SVR模块Agent 向Server返回的进程信息结构指针为空,或服务端处理代理端消息时，消息指针为空。
 *
 * 值: 0x02002d0e
 *
 * 解决方案:   检查SVR模块Agent向Server返回的进程信息结构指针是否已经被初始化过。
 *
 */
#define OS_ERRNO_SHELL_SVR_POINT_NULL                                           SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0e)

/**
 * @ingroup sre_shell
 * HShell错误码：SVR模块服务端消息分发处理时入参消息指针为空。
 *
 * 值: 0x02002d0f
 *
 * 解决方案: 检查SVR模块服务端消息分发处理时入参消息指针是否已经初始化。
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGDISPATCH_POINT_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x0f)

/**
 * @ingroup sre_shell
 * HShell错误码：SVR模块服务端消息处理函入参消息参数指针为空。
 * 值: 0x02002d10
 *
 * 解决方案:  检查SVR模块服务端消息处理时入参消息参数指针是否已经初始化。
 *
 */
#define OS_ERRNO_SHELL_SVR_MSGSUB_MSG_NULL                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x10)

/**
 * @ingroup sre_shell
 * HShell错误码：分离TransId信息时入参生成id需要的参数信息结构体指针为空。
 *
 * 值: 0x02002d11
 *
 * 解决方案:  检查分离TransId信息时入参生成id需要的参数信息结构体指针是否为空。
 *
 */
#define OS_ERRNO_SHELL_TRAN_POINT_NULL                                          SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x11)

/**
 * @ingroup sre_shell
 * HShell错误码：分离TransId信息时没有分离得到有效的TransId 参数信息。
 *
 * 值: 0x02002d12
 *
 * 解决方案:  检查分离TransId信息时有效TransId 是否存在。
 *
 */
#define OS_ERRNO_SHELL_TRANID_FAIL                                              SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x12)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块主控发送的消息上报给前端时公共信息收集响应中的收集对象不合法。
 *
 * 值: 0x02002d17
 *
 * 解决方案: 检查CHANNEL 模块主控发送的消息上报给前端时公共信息收集响应中的收集对象参数的合法性。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_COLLECT_OBJ_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x17)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块调试命令申请内存失败。
 *
 * 值: 0x02002d18
 *
 * 解决方案:  检查CHANNEL 模块调试命令原先申请的内存是否已被释放以及所在分区是否已被用完。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_MEMALLOC_ERROR                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x18)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块接收到的命令数据的指针为空。
 *
 * 值: 0x02002d19
 *
 * 解决方案:  检查CHANNEL 模块接收到的命令数据的指针是否已经被初始化。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_POINT_NULL                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x19)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块ACSCOMM定义的公共信息收集请求内容消息帧内存分配失败。
 *
 * 值: 0x02002d1a
 *
 * 解决方案:   CHANNEL 模块ACSCOMM定义的公共信息收集请求内容消息帧原先内存分配是否已被释放以及所使用分区空间是否已被用完。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_MSGALLOC_ERROR                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1a)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块调用dbg_acscomm提供的发送接口把传消息给 dbg_server 时命令输入错误。
 *
 * 值: 0x02002d1b
 *
 * 解决方案: 检查CHANNEL 模块调用dbg_acscomm提供的发送接口把传消息给 dbg_server 时命令输入的合法性。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_CMDTYPE_ERROR                                    SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1b)

/**
 * @ingroup sre_shell
 * HShell错误码：AGENT 模块申请消息内存失败。
 *
 * 值: 0x02002d1c
 *
 * 解决方案:  检查AGENT 模块原先申请消息内存空间是否没有被释放以及所使用的分区内存空间是否已被用完。
 *
 */
#define OS_ERRNO_SHELL_AGENT_MSGALLOC_ERROR                                     SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1c)

/**
 * @ingroup sre_shell
 * HShell错误码：显示模块SRE_Show或者SRE_Printf处理的数据过长。
 *
 * 值: 0x02002d1d
 *
 * 解决方案:  显示模块需要限制SRE_Show或者SRE_Printf处理数据的长度目前最长为512字节。
 *
 */
#define OS_ERRNO_SHELL_SHOW_TOO_LONG                                            SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1d)

/**
 * @ingroup sre_shell
 * HShell错误码：SHOW模块SRE_Show或者SRE_Printf输出处理分配的内存失败。
 *
 * 值: 0x02002d1e
 *
 * 解决方案:  检查SHOW模块SRE_Show或者SRE_Printf输出处理原先分配的内存是否已被释放以及所使用分区是否已被用完。
 *
 */
#define OS_ERRNO_SHELL_SHOW_ALLOC_ERROR                                         SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1e)

/**
 * @ingroup sre_shell
 * HShell错误码：SHOW模块SRE_Show钩子函数为空。
 *
 * 值: 0x02002d1f
 *
 * 解决方案: 检查SHOW模块SRE_Show钩子函数是否已被注册。
 *
 */
#define OS_ERRNO_SHELL_SHOW_HOOK_NULL                                           SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x1f)

/**
 * @ingroup sre_shell
 * HShell错误码：SHOW模块SRE_Show输出的钩子函数已经存在。
 *
 * 值: 0x02002d20
 *
 * 解决方案: 不需要重新注册相同的钩子函数，去掉注册相同的钩子函数。
 *
 */
#define OS_ERRNO_SHELL_SHOW_HOOK_EXIST                                          SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x20)

/**
 * @ingroup sre_shell
 * HShell错误码：SHOW模块SRE_Show输出的钩子函数注册过多，一般 最大SHOW钩子为2个。
 *
 * 值: 0x02002d21
 *
 * 解决方案:  去掉多余的SRE_Show输出的钩子函数。
 *
 */
#define OS_ERRNO_SHELL_SHOW_HOOK_TOO_MUCH                                       SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x21)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块通道接收数据的缓冲区过小。
 *
 * 值: 0x02002d24
 *
 * 解决方案:  CHANNEL 模块通道接受数据的缓冲区设置增大或减小向通道发送的报文大小。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_BUFFER_OVERFLOW                                  SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x24)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块通道传输包格式错误。
 *
 * 值: 0x02002d25
 *
 * 解决方案:CHANNEL 模块 查看Host端发送的报文是否符合协议。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_FORMAT_ERROR                                     SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x25)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块 通道传输包校验错误。
 *
 * 值: 0x02002d26
 *
 * 解决方案:  检查通道传输过来的报文数据的正确性。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_CHECK_ERROR                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x26)

/**
 * @ingroup sre_shell
 * HShell错误码：CHANNEL 模块通道传输包没有没有消息包头，即没有@符号。
 *
 * 值: 0x02002d27
 *
 * 解决方案: 查看Host端消息发送是否正确，查看通道是否将消息截断成两半发过来，去除消息头。
 *
 */
#define OS_ERRNO_SHELL_CHANNEL_NO_MSG_HEAD                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x27)

/**
 * @ingroup sre_shell
 * HShell错误码:Target shell内存操作时，指定修改或查询的内存宽度不合法。
 *
 * 值: 0x02002d30
 *
 * 解决方案: 排查Target shell内存修改操作时需指定宽度为1,2或4字节；内存查询时最大宽度不能超过256字节。
 *
 */
#define OS_ERRNO_SHELL_MEMWR_WIDTH_INVALID                                      SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x30)

/**
 * @ingroup sre_shell
 * HShell错误码:  内存操作时，临时内存申请失败。
 *
 * 值: 0x02002d36
 *
 * 解决方案: 排查代码有无内存泄露。
 *
 */
#define OS_ERRNO_SHELL_MEMWR_ALLOC                                              SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x36)

/**
 * @ingroup sre_shell
 * HShell错误码: 内存操作时，目的地址无效。
 *
 * 值: 0x02002d37
 *
 * 解决方案: 排查目的地址是否有效。
 *
 */
#define OS_ERRNO_SHELL_MEMWR_ADDR_INVAIL                                        SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x37)

/**
 * @ingroup sre_shell
 * HShell错误码: Target shell查询内存操作时，输入的内存单元个数非法或者被忽略。
 *
 * 值: 0x02002d38
 *
 * 解决方案: 使用查询内存操作命令时，必须输入内存单元个数，若已经输入内存单元个数，请排查输入的内存单元个数大小是否在合法范围[1, 512]内。
 *
 */
#define OS_ERRNO_SHELL_MEMWR_UNITS_NUM_INVALID                                  SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x38)

/**
 * @ingroup sre_shell
 * HShell错误码: Target shell查询或者修改内存操作时，输入的内存地址未按照要求对齐。
 *
 * 值: 0x02002d39
 *
 * 解决方案: 排查输入的内存地址是否按照要求对齐，当输入的数据宽度为2或者4时，要求输入的地址须为2字节或者4字节对齐。
 *
 */
#define OS_ERRNO_SHELL_MEMWR_ADDR_NOT_ALIGNED                                   SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x39)

/**
 * @ingroup sre_shell
 * HShell错误码：调用SRE_Printf时传入的格式化字符串指针为NULL。
 *
 * 值: 0x02002d3a
 *
 * 解决方案: 调用SRE_Printf时保证传入的格式化字符串指针为非NULL。
 *
 */
#define OS_ERRNO_SHELL_PTR_NULL                                                 SRE_ERRNO_OS_ERROR(OS_MID_SHELL, 0x3a)

/**
 * @ingroup sre_shell
 * 表示shell终端驱动类型。
 *
 */
#define DBG_TERMINAL_TOOL               1   /**< 终端为TOOL   */
#define DBG_TERMINAL_VRPCLI             2   /**< 终端为VRPCLI */
#define DBG_TERMINAL_MML                3   /**< 终端为MML    */
#define DBG_TERMINAL_UART               4   /**< 终端为UART   */
#define DBG_TERMINAL_SRIO               5   /**< 终端为SRIO   */
#define DBG_TERMINAL_GE                 6   /**< 终端为GE     */


/**
 * @ingroup sre_shell
 * Target shell支持的show模块命令序号。
 *
 */
typedef enum tagShellShowModCmdNo
{
    OS_SHELL_SHOW_CPUP_CMD_NO = 0,          /**< 当前系统showcpup命令序号*/
    OS_SHELL_SHOW_SEM_CMD_NO,               /**< 当前系统showsem命令序号*/
    OS_SHELL_SHOW_QUEUE_CMD_NO,             /**< 当前系统showqueue命令序号*/
    OS_SHELL_SHOW_MSG_CMD_NO,               /**< 当前系统showmsg命令序号*/
    OS_SHELL_SHOW_EVENT_CMD_NO,             /**< 当前系统showevent命令序号*/
    OS_SHELL_SHOW_TIMER_CMD_NO,             /**< 当前系统showetimer命令序号*/
    OS_SHELL_SHOW_HWI_CMD_NO,               /**< 当前系统showhwi命令序号*/
    OS_SHELL_SHOW_ERROR_CMD_NO,             /**< 当前系统showerror命令序号*/
    OS_SHELL_SHOW_MEMPT_CMD_NO,             /**< 当前系统showmempt命令序号*/
    OS_SHELL_SHOW_CMD_NO_BUTT
} SHELL_SHOW_CMD_NO_E;

/**
 *@defgroup  sre_shell sre_show模块接口
 *@ingroup sre_shell
 */

/**< 最大Show长度 */
#define SHOW_MAX_LEN 321

/**
 *@ingroup sre_shell
 *输出重定向标识
 */
typedef UINT32 TRANSID_T;

/**
 *@ingroup sre_shell
 *SHOW输出钩子函数类型。
 */
typedef UINT32 (*SHOW_HOOK_FUNC)
(
    TRANSID_T   TransId,    /**<重定向标识。*/
    UINT8       ucType,     /**<类型       .*/
    UINT32      uwLength,   /**<输出信息长度，不包含'/0'。*/
    CHAR*       pscOutPut   /**<格式化信息。*/
);

/**
 *@ingroup sre_shell
 *热点函数使用tick和timer的函数钩子类型。
 */
typedef UINT32 (* SHELL_SAM_RP_FUNC)(UINT32* puwPeriod, UINT8 *pucLevel, UINT32 uwDo);

/**
* @ingroup  sre_shell
*
* 设置热点函数的配置信息。
*/
typedef struct tagShellSamModInfo
{
    UINT32 uwAddr;                  /**<默认PC存储区起始地址, 需4字节对齐 */
    UINT32 uwLen;                   /**<默认PC存储区长度, 需8字节对齐     */
    SHELL_SAM_RP_FUNC pfnRpTick;    /**<操作tick中断的钩子                */
    SHELL_SAM_RP_FUNC pfnUseTimer;  /**<操作timer的钩子                   */
}SHELL_SAM_MOD_INFO_S;

/**
* @ingroup  sre_shell
*
* 设置HSHELL模块的配置信息。
*/
typedef struct tagHshellModInfo
{
    UINT8 ucServerCoreID;           /**<运行Server 核号                           */
    UINT8 ucSvrPrority;             /**<运行Server 的优先级                       */
    UINT8 ucAgtPrority;             /**<运行Agent  的优先级                       */
    UINT32 uwThreadType;            /**<Shell线程类型，分为任务和软中断           */
    UINT32 uwSvrStackSize;          /**<运行Server 的栈大小                       */
    UINT32 uwAgtStackSize;          /**<运行Agent  的栈大小                       */
} HSHELL_MOD_INFO_S;

/**
 *@ingroup sre_shell
 *经过性断点钩子注册函数。
 *每个核至多可注册一个函数。
 */
typedef VOID (*HSHELL_TRACE_COLLECT_FUNC)(VOID);

/**
 *@ingroup sre_shell
 *Shell agent端消息处理钩子函数处理。
 */
typedef UINT32 (*HSHELL_AGENT_MSG_PROC_HOOK_FUNC)(UINT32 uwSendId, VOID *pMsg);


/**
 *@ingroup sre_shell
 *注册的自定义调试接口的钩子定义，该钩子提供统一的钩子类型，通常该钩子是各个模块的调试接口。
 */
typedef UINT32 (*CMD_CBK_FUNC)();

/**
* @ingroup  sre_shell
* @brief 格式化信息输出函数。
*
* @par 描述:
* 格式化信息输出函数。
*
*
*@param TransId [IN]#TRANSID_T， 重定向标识。
*@param pscFormat [IN]#CHAR *，  字符串，要输出的格式化信息内容。
*
* @retval  #OS_ERRNO_SHELL_SHOW_ALLOC_ERROR        0x02002d1e，SHOW模块输出处理分配的内存失败。
* @retval  #OS_ERRNO_SHELL_SHOW_TOO_LONG           0x02002d1d，显示模块处理的数据过长。
* @retval  #SRE_OK                                 0x00000000，成功。
* @par 依赖:
* <ul><li>sre_shell.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R002C00
* @see 无
*/
extern UINT32 SRE_Show(TRANSID_T TransId, CHAR * pscFormat, ...);

/**
* @ingroup  sre_shell
* @brief 接收通道输入字符处理函数
*
* @par 描述:
* 驱动调用该接口，向shell输入驱动接收到的字符信息。
*
* @attention
* <ul>
* <li>目前只有CORTEX_AX平台支持串口接收字符处理函数</li>
* </ul>
*
* @param  ucChar  [IN] 类型#UINT8，串口接收的字符值。
*
* @retval  #OS_ERRNO_IO_INTF_SENDCHR2CHL_HOOK_NULL    0x02002d32，注册的通道输出字符钩子函数为空。
* @retval  #SRE_OK                                  0x00000000，成功。
* @par 依赖:
* <ul><li>sre_shell.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R002C00
* @see 无
*/
extern UINT32 SRE_SendChrToShell(UINT8 ucChar);

/**
* @ingroup  sre_shell
* @brief 标准输出打印。
*
* @par 描述:
* 注册通道输出钩子后，调用该函数可实现输出打印。
*
* @attention
* <ul>
* <li>目前只有CORTEX_AX平台支持标准输出打印函数。</li>
* <li>支持c、d、i、x、s、f、%几种类型格式化转换。</li>
* <li>支持右对齐(左边补0或者空格)和左对齐(右边补空格)。</li>
* <li>对于Balong产品，在初始化阶段系统满足打印条件前支持延时打印，待系统满足打印条件后(需要在SRE_HardDrvInit中先初始化UART，最后调用SRE_SendChrToShell注册串口接收字符处理函数)，一起打印相关内容。最大支持4K字节大小的缓存空间。</li>
* <li>最大支持打印字符数为SHOW_MAX_LEN(321)，包含结束符。</li>
* <li>调用此函数时，需要额外消耗当前线程所在的栈空间资源(大约为343个字节)。</li>
* <li>可选参数的合法性由用户保证，避免造成打印异常。</li>
* </ul>
*
* @param  pcFormat  [IN] 类型#CHAR *，输出格式化字符串指针。
* @param  ...  [IN] 可选参数。
*
* @retval  #OS_ERROR                               0xFFFFFFFF，传入的格式化字符串指针为NULL或串口输出函数未注册或者显示的数据过长,该接口支持的最大显示长度为SHOW_MAX_LEN(包含结束符)。
* @retval  #[0,SHOW_MAX_LEN)                       已经输出打印的字符数，输出打印成功。
* @par 依赖:
* <ul><li>sre_shell.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R002C00
* @see 无
*/
extern UINT32 SRE_Printf (const CHAR *pcFormat, ...);

#ifdef __cplusplus
#if __cplusplus

}
#endif
#endif

#endif    /*__SRE_SHOW_H__*/

