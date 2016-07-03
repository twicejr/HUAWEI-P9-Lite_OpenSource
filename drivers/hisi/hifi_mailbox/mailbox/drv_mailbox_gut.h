
#ifndef __DRV_MAILBOX_GUT_H__
#define __DRV_MAILBOX_GUT_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "drv_mailbox_platform.h"
#include "drv_mailbox_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAILBOX_GLOBAL_CHANNEL_NUM	(4)

	/*邮箱ID号组成和获取的系列转换宏*/
#define MAILBOX_SINGLE_ID_MASK						(0xFF)	/*邮箱号的当个元素号(8bit)屏蔽位*/
#define mailbox_get_channel_id(id)					  ((id) & (~MAILBOX_SINGLE_ID_MASK))	/*由邮件ID获得邮箱ID*/

	/*由邮件ID获得源CPUID*/
#define mailbox_get_src_id(id)	(unsigned char)(((id) >> MAILBOX_ID_SRC_CPU_OFFSET) & MAILBOX_SINGLE_ID_MASK)

	/*由邮件ID获得目的CPUID*/
#define mailbox_get_dst_id(id)	(unsigned char)(((id) >> MAILBOX_ID_DST_CPU_OFFSET) & MAILBOX_SINGLE_ID_MASK)

	/*由邮件ID获得通道的物理载体ID*/
#define mailbox_get_carrier_id(id)	(unsigned char)(((id) >> MAILBOX_ID_CHANNEL_OFFSET) & MAILBOX_SINGLE_ID_MASK)

	/*由邮件ID获得邮件应用ID*/
#define mailbox_get_use_id(id)	(unsigned char)((id) & MAILBOX_SINGLE_ID_MASK )

	/*表示邮箱已经初始化的魔鬼数字*/
#define MAILBOX_INIT_MAGIC							(0x87654312)

/*a按p字节对齐*/
#define MAILBOX_ALIGN                                sizeof(unsigned int)
#define mailbox_align_size(a,p)                     (((a)+((p)-1)) & ~((p)-1))

/*写物理地址*/
#define mailbox_write_reg(Addr, Value)                  (*((volatile unsigned int *)(Addr)) = Value)

	/* 定义CPU个数 */
#define MAILBOX_CPU_NUM 							(MAILBOX_CPUID_BUTT)

	/* 定义channel个数 */
#define MAILBOX_CHANNEL_BUTT(src, dst)	(MAILBOX_CHANNEL_##src##2##dst##_BUTT  & 0xff) /*& 0xff 消pclint*/

/* 定义user id的上限值 */
#define MAILBOX_USER_BUTT(src, dst, channel)    \
    ((unsigned int)MAILBOX_MAILCODE_ITEM_END(src, dst, channel) & 0xff)

/*定义数据结构 struct mb_cfg 中的元素*/
#define MAILBOX_CHANNEL_COMPOSE(src, dst, ch)                   \
    /*channel*/                                                 \
    {(unsigned int)MAILBOX_MAILCODE_ITEM_END(src, dst, ch),    \
    /*DataSize*/                                                \
    (unsigned int)MAILBOX_QUEUE_SIZE(src, dst, ch),            \
    /*SingleMax*/                                               \
    (unsigned int)MAILBOX_MAILSIZE_MAX(src, dst, ch),          \
    /*HeadAddr*/                                                \
    (unsigned long)MAILBOX_HEAD_ADDR(src, dst, ch), \
    /*DataAddr*/                                                \
    (unsigned long)MAILBOX_QUEUE_ADDR(src, dst, ch),\
    /*IPC INT NUMBER*/                                          \
    (unsigned int)MAILBOX_IPC_INT_NUM(src, dst, ch)}


#define MAILBOX_USER_QUEUE(mbuf)   (&((struct mb_buff *)(mbuf))->usr_queue)

	/*计算邮箱剩余空间，为了防止队列头尾重叠去除了4byte空间未使用，单位byte*/
#define mailbox_queue_left(Rear, Front, Length) \
           (((Rear) > (Front)) ? (((Rear) - (Front)) - sizeof(unsigned int)): \
           (((Length) - ((Front) - (Rear))) - sizeof(unsigned int)))

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct mb_queue
{
    unsigned long               base;            /* 队列基地址       */
    unsigned int               length;          /* 队列总长度，单位byte */
    unsigned long               front;           /* 队列写指针, 绝对地址，in   */
    unsigned long               rear;            /* 队列读指针, 绝对地址，out  */
    unsigned int               size;        /* 此队列单次读取的长度, 用于应用层回调通知读取函数*/
}mailbox_queue_stru ;

/*****************************************************************************
 结构名    : DRV_MAILBOX_ID_ST
 结构说明  : 邮箱邮件ID号的数据结构定义 MAILBOX_MAIL_ID_E
 ****************************************************************************/
struct mailbox_id_stru
{
    signed char                 UseId;
    signed char                 Channel;
    signed char                 DstCpu;
    signed char                 SrcCpu;
};

/*****************************************************************************
  邮箱通道传送use id 轨迹数据结构
*****************************************************************************/

struct mb_cb
{
    void (*func)(void *mbuf, void *handle, void *data);
    void                *handle;         /*保存用户数据*/
    void                *data;           /*保存用户数据*/
};

/*****************************************************************************
 实体名称  : struct mb_cfg
 功能描述  : Mailbox 某个物理邮箱通道的硬件资源配置
*****************************************************************************/
typedef struct mb_cfg
{
    unsigned int               butt_id;     /*邮箱ID的结束号，包含最大当前邮箱的最大ID信息  */
    unsigned int               data_size;   /*邮箱数据大小*/
    unsigned int               single_max;  /*单次邮件发送最大大小*/
    unsigned long               head_addr;   /*邮箱头内存地址  */
    unsigned long               data_addr;   /*邮箱数据内存地址*/
    unsigned int               int_src;     /*邮箱物理通道ID对应的核间中断资源号*/
}MAILBOX_CHANNEL_CFG_STRU;

/*****************************************************************************
  邮箱通道的操作资源集合
*****************************************************************************/
struct mb_buff
{
    unsigned int               channel_id;  /*邮箱通道ID，由邮箱两个核之间的链路，链路方向，和物理通道号三者确定*/
    unsigned int               mailcode;    /*邮件ID，由邮箱两个核之间的链路，链路方向，物理通道号，和应用号四个方面确定*/
    unsigned int               seq_num;     /*邮箱消息序列号(SN号)记录全局变量*/
    void                       *mutex;       /*互斥机制，防止多个线程同时发送数据到相同邮箱*/
    struct mb                  *mb;
    struct mb_cb               *read_cb;    /*此邮箱通道的功能回调函数队列*/
    struct mb_cfg      *config;             /*此邮箱的共享内存通道信息*/
#ifdef MAILBOX_OPEN_MNTN
	struct mb_mntn				mntn;		/*此邮箱通道的可维可测数据*/
#endif
	struct mb_queue 			mail_queue; /*用于此共享内存邮箱数据处理的环形队列操作句柄*/
	struct mb_queue 			usr_queue;	/*给用户使用的数据，是跳除邮件头大小的mail_queue*/
};

/*****************************************************************************
  单个邮箱通道配置表项
*****************************************************************************/
typedef struct mb_link
{
    unsigned int          carrier_butt;    /*当前CPU连接有多少个邮箱通道*/
    struct mb_buff        *channel_buff;    /*此邮箱的控制资源集合*/
}MAILBOX_LINK_STRU ;

/*****************************************************************************
  邮箱模块的整体控制句柄数据结构,邮箱群的控制句柄集合
*****************************************************************************/
typedef struct mb
{
    unsigned int               local_id;                           /*当前CPU的ID*/
    unsigned int               init_flag;                          /*初始化标志*/
    unsigned int               log_prob;                           /*指向下一条错误记录*/
    struct mb_log               log_array[MAILBOX_ERRO_ARRAY_NUM];  /*记录最近的几次错误信息*/
    struct mb_link              send_tbl[MAILBOX_CPUID_BUTT];       /*邮箱发送通道控制资源列表*/
    struct mb_link              recv_tbl[MAILBOX_CPUID_BUTT];       /*邮箱接收通道控制资源列表*/
}MAILBOX_STRU;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  9 全局变量声明
*****************************************************************************/

/*定义所有已存在的共享内存通道的物理内存及硬件资源配置，全局定义*/
extern MAILBOX_EXTERN struct mb_cfg g_mailbox_global_cfg_tbl[];

/*平台邮箱通道句柄的内存池空间*/
extern MAILBOX_EXTERN struct mb_buff  g_mailbox_channel_handle_pool[MAILBOX_CHANNEL_NUM];

/*平台邮箱用户回调句柄的内存池空间*/
extern MAILBOX_EXTERN struct mb_cb	  g_mailbox_user_cb_pool[MAILBOX_USER_NUM];

/*邮箱模块总控制句柄*/
extern MAILBOX_EXTERN struct mb g_mailbox_handle;
/*****************************************************************************
  10 函数声明
*****************************************************************************/
MAILBOX_EXTERN struct mb *mailbox_get_mb(void);

MAILBOX_EXTERN struct mb_buff *mailbox_get_channel_handle(struct mb *mb, unsigned int mailcode);

MAILBOX_EXTERN int mailbox_register_cb(
                unsigned int  mail_code,
                void (*cb)(void *mbuf, void *handle, void *data),
                void *usr_handle,
                void *usr_data);

MAILBOX_EXTERN  int mailbox_request_buff(unsigned int mailcode,  void * mbuf);

MAILBOX_EXTERN int mailbox_sealup_buff(struct mb_buff * mb_buf , unsigned int usr_size);

MAILBOX_EXTERN int mailbox_flush_buff( struct mb_buff *mbuff);

MAILBOX_EXTERN int mailbox_send_buff(struct mb_buff * mb_buf);

MAILBOX_EXTERN int mailbox_release_buff(struct mb_buff * mb_buf);

MAILBOX_EXTERN  int mailbox_write_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned int         size);

MAILBOX_EXTERN int mailbox_read_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned int         size);

MAILBOX_EXTERN unsigned long mailbox_virt_to_phy(unsigned long  virt_addr);

MAILBOX_EXTERN unsigned long mailbox_phy_to_virt(unsigned long  phy_addr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_mailbox.h */

