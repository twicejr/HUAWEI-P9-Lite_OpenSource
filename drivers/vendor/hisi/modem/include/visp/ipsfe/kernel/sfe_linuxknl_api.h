

#ifndef _SFE_LINUXKNL_API_H_
#define _SFE_LINUXKNL_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*  基本类型定义  */
#ifndef SFE_OK
#define SFE_OK      0
#endif
#ifndef SFE_ERR
#define SFE_ERR     1
#endif

#ifndef SFE_YES
#define SFE_YES     1
#endif

#ifndef SFE_NO
#define SFE_NO      0
#endif

#ifndef SFE_TRUE
#define SFE_TRUE    1
#endif

#ifndef SFE_FALSE
#define SFE_FALSE   0
#endif

#ifndef SFE_INT8
#define SFE_INT8 char
#endif

#ifndef SFE_UINT8
#define SFE_UINT8 unsigned char
#endif

#ifndef SFE_INT16
#define SFE_INT16 short
#endif

#ifndef SFE_UINT16
#define SFE_UINT16 unsigned short
#endif

#ifndef SFE_INT32
#define SFE_INT32 int
#endif

#ifndef SFE_UINT32
#define SFE_UINT32 unsigned int
#endif

#ifndef SFE_UINT64
#define SFE_UINT64 unsigned long
#endif

#ifndef SFE_VOID
#define SFE_VOID void
#endif

/* 向DB中拷贝数据时,DB头部必须预留的长度 */
#define SFE_KNL_DB_HEAD_RESERVE_LEN      128

/* 数据面Linux内核模块错误码定义 */
typedef enum enumsfe_knl_err_code
{
    SFE_KNL_OK = SFE_OK,                       /* 操作成功 */
    SFE_KNL_INIT_DBTAIL_RESERVE_LEN_NOT_ENOUGH,/* 1  内核态初始化,DB尾部预留的空间不够存放skb_shared_info信息 */
    SFE_KNL_MALLOC_STAT_MEM_FAIL,              /* 2  内核态初始化,申请内核态打点统计内存失败 */
    SFE_KNL_CREATE_STAT_PRCODIR_FAIL,          /* 3  内核态初始化,创建PROC文件系统失败 */
    SFE_KNL_CREATE_NORMALSTAT_PRCOFILE_FAIL,   /* 4  内核态初始化,创建正常统计信息显示文件失败 */
    SFE_KNL_CREATE_AUTOSTAT_PRCOFILE_FAIL,     /* 5  内核态初始化,创建打点统计信息显示文件失败 */
    SFE_KNL_RESERVE_MBUF_NUM_NOT_ENOUGH,       /* 6  内核态接收报文,MCUP资源池剩余个数不足 */
    SFE_KNL_SKB_NULL,                          /* 7  内核态接收报文,报文分流,报文skb为空 */
    SFE_KNL_SKB_DEV_NULL,                      /* 8  内核态接收报文,报文分流,设备指针为空 */
    SFE_KNL_RCVPOLICY_NULL,                    /* 9  内核态接收报文,报文分流,接收策略指针为空 */
    SFE_KNL_NEWMBUF_NULL,                      /* 10 内核态接收报文,报文分流,存放新生成MBUF的指针为空 */
    SFE_KNL_RCV_PRE_PROC_HOOK_RETURN_FAIL,     /* 11 内核态接收报文,报文分流,产品预处理钩子返回失败 */
    SFE_KNL_MALLOC_MBUF_FAIL,                  /* 12 根据skb创建MBUF,创建MBUF失败 */
    SFE_KNL_MALLOC_DATA_LEN_TOO_LONG,          /* 13 根据skb创建MBUF,报文skb中数据长度超出一个DB限制 */
    SFE_KNL_MALLOC_SKB_DATA_HEAD_POINTER_NULL, /* 14 根据skb创建MBUF,报文skb中的head或data指针为NULL */
    SFE_KNL_MALLOC_MBUF_DBD_FAIL,              /* 15 根据skb创建MBUF,创建DB失败 */
    SFE_KNL_MALLOC_DB_INPUT_NULL,              /* 16 申请存放数据的data区内存,存放数据的内存为空 */
    SFE_KNL_MALLOC_DB_TOO_LONG,                /* 17 申请存放数据的data区内存,存放数据的长度超出限制 */
    SFE_KNL_MALLOC_DB_FAIL,                    /* 18 申请存放数据的data区内存,申请DB失败 */
    SFE_KNL_FREE_DB_INPUT_NULL,                /* 19 释放存放数据的data区内存,待释放的data区内存起始地址为空 */
    SFE_KNL_MBUF_DESTROY_INPUT_NULL,           /* 20 释放存放skb报文的MBUF,待释放的MBUF内存起始地址为空 */
    SFE_KNL_MBUF_FREE_HEAD_INPUT_NULL,         /* 21 释放存放skb报文的MBUF头和DBD,待释放的MBUF头和DBD内存起始地址为空 */
    SFE_KNL_FREE_DB_NOTMCUP_MEM,               /* 22 释放存放数据的data区内存,不是MCUP的内存 */
    SFE_KNL_FREE_DB_REPEAT_FREE,               /* 23 释放存放数据的data区内存,重复释放DB */
    SFE_KNL_CREATSKB_ALLOC_SKB_HEAD_NULL,      /* 24 根据MBUF创建skb,申请skb头失败 */
    SFE_KNL_CREATSKB_MBUF_NULL,                /* 25 根据MBUF创建skb,输入的MBUF为空 */
    SFE_KNL_CREATSKB_PPSKB_NULL,               /* 26 根据MBUF创建skb,输入的存放输出参数skbuf的指针为空 */
    SFE_KNL_CREATSKB_DBNUM_INVALID,            /* 27 根据MBUF创建skb,输入的MBUF的DB个数错误 */
    SFE_KNL_CREATSKB_MBUF_DBD_NULL,            /* 28 根据MBUF创建skb,输入的MBUF的DBD和DB内存为空 */
    SFE_KNL_CREATSKB_GET_DEV_FAIL,             /* 29 根据MBUF创建skb,获取发送接口设备的节点为空 */
    SFE_KNL_SGOCALLBACK_INPU_NULL_POINTER,     /* 30 硬件IO聚合回调,入参为空 */
    SFE_KNL_SET_SAMPLE_INFO_MODULE_NOT_INIT,   /* 31 内核态采样设置失败,系统尚未初始化不能调用该接口 */
    SFE_KNL_SET_SAMPLE_INFO_VCPUID_INVALID,    /* 32 设置采样失败,输入的采样参数指针为空 */
    SFE_KNL_MALLOC_PROCDELAY_MEM_FAIL,         /* 33 分配内核态处理时延采样记录的内存失败 */
    SFE_KNL_ENABLE_SAMPLE_INPUTPARA_INVALID,   /* 34 使能采样失败,输入参数非法 */
    SFE_KNL_SET_SAMPLEINFO_INPUTPARA_INVALID,  /* 35 设置采样失败,输入参数非法 */
    SFE_KNL_CREATE_SAMPLE_PRCOFILE_FAIL,       /* 36 内核态初始化,创建采样信息显示文件失败 */
    SFE_KNL_SET_SAMPLE_PARA_INVALID,           /* 37 通过命令行echo方式设置采样参数时,输入参数长度不符 */
    SFE_KNL_COPY_SAMPLE_PARA_FAILED,           /* 38 通过命令行echo方式设置采样参数时,拷贝参数失败 */
    SFE_KNL_MALLOC_PREPROCDELAY_MEM_FAIL,      /* 39 分配内核态上次处理时延采样记录的内存失败 */
    SFE_KNL_MALLOC_PREPROCDELAYFLAG_MEM_FAIL,  /* 40 分配内核态是否开启新一轮采样标记的内存失败 */
    SFE_KNL_MALLOC_VCPUSTAT_FAIL,              /* 41 分配内核态全局统计信息内存失败 */
    SFE_KNL_MALLOC_CURSAMPLESTAT_FAIL,         /* 42 分配内核态当前采样记录的信息的内存失败 */
    SFE_KNL_MALLOC_PRESAMPLESTAT_FAIL,         /* 43 分配内核态上次采样记录的信息的内存失败 */
}sfe_knl_err_code_e;


/* 报文由Linux协议栈处理 */
#define SFE_KNL_PKT_OS_HANDLE           0
/* 报文由VISP协议栈处理 */
#define SFE_KNL_PKT_STACK_HANDLE        1

/* 内核态采样宏:采样使能控制,使能 */
#define SFE_KNL_SAMPLE_ENABLE           1
/* 内核态采样宏:采样使能控制,去使能 */
#define SFE_KNL_SAMPLE_DISABLE          0

/* 内核态采样宏:输入流量 */
#define SFE_KNL_SAMPLE_INFLOW           0x01
/* 内核态采样宏:处理时延 */
#define SFE_KNL_SAMPLE_PROCDELAY        0x02
/* 内核态采样宏:输入流量和处理时延 */
#define SFE_KNL_SAMPLE_ALL              0x03

/* 内核态采样宏:采样间隔最小值 */
#define SFE_KNL_SAMPLE_INTERVAL_MIN     10
/* 内核态采样宏:采样间隔最大值 */
#define SFE_KNL_SAMPLE_INTERVAL_MAX     3600
/* 内核态采样宏:采样时长最小值 */
#define SFE_KNL_SAMPLE_STEP_MIN         1
/* 内核态采样宏:采样时长最大值 */
#define SFE_KNL_SAMPLE_STEP_MAX         50
/* 内核态采样宏:采样次数最小值 */
#define SFE_KNL_SAMPLE_COUNT_MIN        1
/* 内核态采样宏:采样次数最大值 */
#define SFE_KNL_SAMPLE_COUNT_MAX        50

/* 内核态采样设置参数结构 */
typedef struct tagSFE_KNL_SAMPLE_PARA
{
    UINT32  u32Switch;                      /* 采样开关,是否使能采样<SFE_KNL_SAMPLE_DISABLE, SFE_KNL_SAMPLE_ENABLE> */
    UINT32  u32Type;                        /* 采样类型,包括:输入流量,处理时延,两类都采<SFE_KNL_SAMPLE_INFLOW, SFE_KNL_SAMPLE_ALL> */
    UINT32  u32Interval;                    /* 采样间隔<SFE_KNL_SAMPLE_INTERVAL_MIN, SFE_KNL_SAMPLE_INTERVAL_MAX>, 单位秒
                                               采样间隔内按照设置的采样时长和采样次数采样,即采样时长x采样次数小于采样间隔 */
    UINT32  u32Step;                        /* 采样时长<SFE_KNL_SAMPLE_STEP_MIN, SFE_KNL_SAMPLE_STEP_MAX>, 单位秒 */
    UINT32  u32Count;                       /* 采样次数<SFE_KNL_SAMPLE_COUNT_MIN, SFE_KNL_SAMPLE_COUNT_MAX> */
    UINT32  u32Resv;
}SFE_KNL_SAMPLE_PARA_S;

/* 内核态采样回调通知信息:输入流量 */
typedef struct tagSFE_KNL_SAMPLE_NOTIFY_FLOW_INFO
{
    UINT32  u32VcpuId;
    UINT32  u32Resv;
    UINT64  u64SfeKnlAllInPPS;              /* 每秒输入总报文数 */
    UINT64  u64SfeKnlAllInBPS;              /* 每秒输入总字节数 */
    UINT64  u64SfeUsrStackInPPS;            /* 每秒输入到用户协议栈的报文数 */
    UINT64  u64SfeUsrStackInBPS;            /* 每秒输入到用户协议栈的字节数 */
    UINT32  u32CurSysTime;                  /* 当前输出采样结果时的系统时间,单位毫秒 */
    UINT32  u32CurSysCpuRate;               /* 当前输出采样结果时的CPU占用率 */
}SFE_KNL_SAMPLE_NOTIFY_FLOW_INFO_S;

/* 内核态采样回调通知信息:处理时延 */
typedef struct tagSFE_KNL_SAMPLE_NOTIFY_DELAY_INFO
{
    UINT32  u32VcpuId;
    UINT32  u32L7ProcDelayMax;              /* L7处理最大时延,单位ms */
    UINT32  u32L7ProcDelayMin;              /* L7处理最小时延,单位ms */
    UINT32  u32L7ProcDelayAvg;              /* L7处理平均时延,单位ms */
    UINT32  u32CurSysTime;                  /* 当前输出采样结果时的系统时间,单位毫秒 */
    UINT32  u32CurSysCpuRate;               /* 当前输出采样结果时的CPU占用率 */
}SFE_KNL_SAMPLE_NOTIFY_DELAY_INFO_S;


/*******************************************************************************
*    Func Name: pf_sfekernel_rcv_pre_proc_hook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 
*  Description: 数据面内核报文接收产品预处理钩子
*        Input: struct sk_buff *skb:Linux报文指针
*       Output: UINT32 *pu32RcvPolicy: 1：该报文由VISP协议栈处理
*                                      0：该报文不由VISP协议栈处理（当前即为由Linux协议栈处理）

*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 1.产品至少要告知VISP该报文是由VISP协议栈处理还是Linux协议栈处理,
*                 如果产品不注册该钩子则报文默认由Linux协议栈处理.
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
typedef UINT32 (*pf_sfekernel_rcv_pre_proc_hook)(struct sk_buff *skb, UINT32 *pu32RcvPolicy);

/*******************************************************************************
*    Func Name: sfekernel_reg_rcv_pre_proc_hook
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: 
*  Description: 注册数据面内核报文接收产品预处理钩子
*        Input: pf_sfekernel_rcv_pre_proc_hook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
UINT32 sfekernel_reg_rcv_pre_proc_hook(pf_sfekernel_rcv_pre_proc_hook pfRegFunc);

/*******************************************************************************
*    Func Name: sfekernel_set_sample_statinfo
* Date Created: 2011-02-22
*       Author: z00166124
*      Purpose: 
*  Description: 设置数据面内核态采样方式和采样参数
*        Input: SFE_KNL_SAMPLE_PARA_S* pstSamplePara: 采样参数指针
*       Output: 
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 1.不论手动或定时采样,用户都需要手动关闭采样
*               2.采样周期为每次的采样时长与采样次数的乘积,加上采样间隔
*               3.采样时长的定时器在采样周期完毕时停止
*        Since: DOPRA VISP V2R3C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-02-22   z00166124               Create
*
*******************************************************************************/
UINT32 sfekernel_set_sample_statinfo(SFE_KNL_SAMPLE_PARA_S* pstSamplePara);

/*******************************************************************************
*    Func Name: pf_sfekernel_sample_output_hook
* Date Created: 2011-02-22
*       Author: z00166124
*      Purpose: 
*  Description: 数据面内核态采样结果输出给产品的钩子
*        Input: UINT32 u32Type: 采样类型:输入流量采样,处理时延采样
*               VOID *pstSampleStatInfo:采样结果输出指针
*       Output: N/A
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 1.用户根据输出的采样类型解析采样结果
*        Since: DOPRA VISP V2R3C03
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-02-22   z00166124               Create
*
*******************************************************************************/
typedef UINT32 (*pf_sfekernel_sample_output_hook)(UINT32 u32Type, VOID *pstSampleStatInfo);

/*******************************************************************************
*    Func Name: sfekernel_reg_sample_output_hook
* Date Created: 2011-02-22
*       Author: z00166124
*      Purpose: 
*  Description: 注册数据面内核态采样输出钩子
*        Input: pf_sfekernel_sample_output_hook pfRegFunc:待注册的钩子函数指针 <非空>
*       Output: 
*       Return: 成功返回 0
*               失败返回 错误码
*      Caution: 
*    Reference:
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-02-22   z00166124               Create
*
*******************************************************************************/
UINT32 sfekernel_reg_sample_output_hook(pf_sfekernel_sample_output_hook pfRegFunc);

#ifdef  __cplusplus
}
#endif

#endif



