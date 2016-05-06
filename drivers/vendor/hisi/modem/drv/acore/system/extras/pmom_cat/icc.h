/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  icc.h
*
*   作    者 :  yaoguocai 184236
*
*   描    述 :  icc 解析头文件
*
*   修改记录 : 2014年12月27日  v1.00  y00184236  创建
*************************************************************************/

#ifndef  __ICC_H__
#define  __ICC_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

#define GET_CHN_ID(channel_id)    (((channel_id)>>16) & 0xffff)
#define GET_FUNC_ID(channel_id)   ((channel_id) & 0xffff)

typedef s32 (*read_cb_func)(u32 channel_id , u32 len, void* context);

/* 通道id分配 */
enum ICC_CHN_ID
{
	ICC_CHN_ACORE_CCORE_MIN=0, /* add for modem reset : A/C核通道开始标志 */
	ICC_CHN_IFC = 0,     /* acore与ccore之间的IFC的物理通道 */
	ICC_CHN_RFILE = 1,   /* acore与ccore之间的RFILE的物理通道 */
	ICC_CHN_NV = 2,      /* acore与ccore之间的NV的物理通道 */
	ICC_CHN_GUOM0 = 3,  /* acore与ccore之间的GUOM0的物理通道 */
	ICC_CHN_GUOM1,       /* acore与ccore之间的GUOM1的物理通道 */
	ICC_CHN_GUOM2,       /* acore与ccore之间的GUOM2的物理通道 */
	ICC_CHN_GUOM3,       /* acore与ccore之间的GUOM3的物理通道 */
	ICC_CHN_GUOM4,       /* acore与ccore之间的GUOM4的物理通道 */
	ICC_CHN_GUOM5,       /* acore与ccore之间的GUOM5的物理通道 */
	ICC_CHN_CSHELL,      /* acore与ccore之间的CSHELL的物理通道 */
	ICC_CHN_AC_PANRPC,  /* acore与ccore之间的PAN_RPC的物理通道 */
	ICC_CHN_ACORE_CCORE_MAX, /* add for modem reset : A/C核通道结束标志 */
	ICC_CHN_MCORE_CCORE, /* mcore与ccore之间的唯一的物理通道 */
	ICC_CHN_MCORE_ACORE, /* mcore与acore之间的唯一的物理通道 */
	ICC_CHN_CCPU_HIFI_VOS_MSG, /* CCPU  和 HIFI 之间的核间通信通道 */
	ICC_CHN_HIFI_TPHY_MSG, /* BBE16 和 HIFI 之间的核间通信代理通道 */
	ICC_CHN_ID_MAX
};

struct icc_channel_packet
{
	u32 channel_id;               /* 该数据包记录的通道id */
	u32 len;                      /* 该数据包长度 */
	u32 src_cpu_id;               /* 该数据包的发送者的cpu id */
	u32 seq_num;                  /* 该数据包的序列号: 同步发送的等待队列需要用到 */
	u32 need_responsed:1;         /* 该数据包是否需要回复给对方核标识bit位 */
	u32 is_responsed:1;           /* 该数据包是否是对方核回复过来的标识bit位 */
	u32 reserved:30;              /* 保留bit位 */
	s32 data;                     /* 数据包头的context */
	u32 timestamp;                /* 该数据包的时间戳 */
	u32 task_id;                  /* 该数据包的发送者的任务id */
};

struct icc_pm_om
{
	struct icc_channel_packet packet;
	u64 read_cb;
	u64 read_context;
};

int icc_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __ICC_H__ */