/******************************************************************************

版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名   : drv_mailbox.c
版 本 号   : 初稿
作	  者   : 莫南 00176101
生成日期   : 2012年9月21日
最近修改   :
功能描述   : mailbox&跨核邮箱驱动软件，主体代码。
函数列表   :
	MAILBOX_BufIdleSize
	MAILBOX_BufDataSize
	mailbox_queue_write
	mailbox_request_channel
	mailbox_release_channel
	mailbox_read_mail
	MAILBOX_PostMails
	mailbox_receive_all_mails
	mailbox_check_mail
	mailbox_read_channel
	mailbox_init_mem
	mailbox_create_box
	mailbox_log_erro
	mailbox_init
	mailbox_queue_read
	MAILBOX_MailReceiverRegister
	mailbox_send_msg
	mailbox_show
修改历史   :
1.日	期	 : 2012年9月21日
作	  者   : 莫南 00176101
修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
1 头文件包含
*****************************************************************************/
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_platform.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"
#include <asm/io.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/console.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/pgtable.h>
#include<linux/vmalloc.h>
#include <asm/io.h>
#include <linux/mm.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
extern int logMsg(char *fmt, ...);
/*****************************************************************************
可维可测信息中包含的C文件编号宏定义
*****************************************************************************/
#undef	_MAILBOX_FILE_
#define _MAILBOX_FILE_	 "gut"

#define SLICE_REG 0xFFF0A534
#define mem_remap_nocache(phys_addr, size) mem_remap_type(phys_addr, size, pgprot_writecombine(PAGE_KERNEL))
/*****************************************************************************
2 全局变量定义
*****************************************************************************/

/*邮箱模块总控制句柄*/
MAILBOX_EXTERN struct mb g_mailbox_handle = {MAILBOX_MAILCODE_INVALID};
void __iomem *g_shareMemBase = NULL;
void * g_slice_reg = NULL;

MAILBOX_LOCAL int mailbox_init_mem(struct mb_cfg *config);

/*****************************************************************************
3 函数实现
*****************************************************************************/

/*邮箱内部接口开始*/
/*****************************************************************************
函 数 名  : mailbox_queue_write
函数类型  :
功能描述  : 往队列写入指定长度数据并更新写指针
输入参数  : struct mb_queue    *queue - 待写入队列操作符
signed char 	   *data	  - 待写入数据指针
unsigned long	   size 	  - 待写入数据长度，单位byte
输出参数  : struct mb_queue    *queue	 - 更队列状态,更新队列写指针。
返 回 值  : void
调用函数  :
被调函数  : mailbox_write_mail()
MAILBOX_Read()

修改历史	  :
1.日	期	 : 2011年6月14日
作	  者   : 袁旦 00145322
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN int mailbox_queue_write(
                struct mb_queue      *queue,
                char                 *data,
                unsigned int         size)
{
    unsigned int SizeToBottom;

    /*计算写指针位置距离环形缓存尾部长度*/
    SizeToBottom  = (unsigned int)((queue->base + queue->length) - queue->front);

    /*若写指针距环形缓存尾部长度大于要写的内容长度，则直接拷贝内容，并更新写指针*/
    if (SizeToBottom > size){
        /*写入pucData到写指针处*/
        mailbox_memcpy((void*)queue->front, (const void*)data, size);

		/*更新写指针*/
		queue->front += size;
	} else {
		/*写入pucData前R长度到写指针处*/
        mailbox_memcpy((void*)(queue->front), (const void*)data, SizeToBottom);

        /*写入pucData+R到环形缓存起始处*/
        mailbox_memcpy((void*)(queue->base),  (const void*)(data + SizeToBottom),
                       (size - SizeToBottom));

        /*更新写指针*/
        queue->front = (queue->base + size) - SizeToBottom;
    }

    return (int)size;
}

/*****************************************************************************
函 数 名  : mailbox_queue_read
功能描述  : 邮箱用户在数据接收回调函数中调用, 从邮箱中读取一封最先到达的邮件

输入参数  : queue -- 邮箱句柄, 数据接收回调函数入参
buff	  -- 保存待读出数据的缓存地址
size	  -- 待读取邮件长度
输出参数  : struct mb_queue    *pMailQueue	 - 更队列状态,更新队列读指针，指针按4字节向前对齐。
返 回 值  : 实际读取长度, 单位byte
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年10月26日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_GLOBAL int mailbox_queue_read(
                struct mb_queue   *queue,
                char              *buff,
                unsigned int      size)
{
    unsigned int             to_bottom;

    /*计算读指针位置距离环形缓存尾部长度*/
    to_bottom  = (unsigned int)((queue->base + queue->length) - queue->rear);

    /*若读指针距环形缓存尾部长度大于要写的内容长度，则直接拷贝内容，并更新读指针*/
    if (to_bottom > size) {
        /*将读指针处数据拷贝至pData处*/
        mailbox_memcpy((void*)buff, (const void*)(queue->rear), size);

        /*更新读指针*/
        queue->rear += size;
    } else {
        /*将读指针处数据前若干byte拷贝到pData处*/
        mailbox_memcpy((void*)buff, (const void*)(queue->rear), to_bottom);

        /*从环形缓存起始处拷贝剩余内容到pData*/
        mailbox_memcpy((void*)(buff + to_bottom), (const void*)(queue->base),
                        (size - to_bottom));

        /*更新读指针*/
        queue->rear = (queue->base + size) - to_bottom;
    }

    return (int)size;
}


/*****************************************************************************
函 数 名  : mailbox_check_mail
接口类型  : 对内接口
功能描述  : 检查读到的消息是否存在异常，包括SN号是否连续、消息滞留时间是否
过长
输入参数  : mb_buff 			*mbuff - 邮箱操作句柄
struct mb_mail		*msg_head  - 读到消息的消息头
输出参数  : 无
返 回 值  : 消息头是否有效
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_check_mail(struct mb_buff *mbuff,
                struct mb_mail *msg_head,
                unsigned long data_addr)
{
    unsigned int          time_stamp;
    unsigned int          seq_num;
    int          ret_val = MAILBOX_OK;
    /* 首先检查消息头保护字*/
    if (MAILBOX_MSGHEAD_NUMBER != msg_head->ulPartition) {
         ret_val = mailbox_logerro_p1(MAILBOX_CRIT_GUT_MSG_CHECK_FAIL, msg_head->ulMailCode);
    }

    seq_num = mbuff->seq_num;

    /*若SN号不连续(去除两CPU可能出现分别下电的情况)*/
    if (MAILBOX_SEQNUM_START == msg_head->ulSeqNum) {
        /*接收者第一次接收*/
        ret_val = mailbox_logerro_p1(MAILBOX_INFO_RECEIVE_FIRST_MAIL, msg_head->ulMailCode);
    } else if ((seq_num + 1) != msg_head->ulSeqNum) {
        /*非翻转出错*/
        #ifndef _DRV_LLT_ /*windows ST 自发自收，不检查*/
        ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_MAILBOX_SEQNUM_CHECK_FAIL, msg_head->ulMailCode);
        #endif
    }

    mbuff->seq_num = msg_head->ulSeqNum;

    /*检查消息在共享内存的滞留时间*/
    time_stamp = (unsigned int)mailbox_get_timestamp();

    msg_head->ulReadSlice = time_stamp;

#ifdef MAILBOX_OPEN_MNTN
    mailbox_record_transport(&(mbuff->mntn), msg_head->ulMailCode ,
                    msg_head->ulWriteSlice, msg_head->ulReadSlice, data_addr);
#endif
    return ret_val;
}

/*****************************************************************************
函 数 名  : mailbox_get_mb
接口类型  : 对外接口
功能描述  : 获取邮箱控制总句柄
输入参数  : 无
输出参数  : 无
返 回 值  : 邮箱控制总句柄
调用函数  :

被调函数  :

修改历史	  :
1.日	期	 : 2012年9月27日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN struct mb *mailbox_get_mb(void)
{
    if (MAILBOX_INIT_MAGIC == g_mailbox_handle.init_flag) {
        return &g_mailbox_handle;
    }

	/*错误邮箱未初始化*/
	mailbox_out(("error: mb not init\n"));
	return MAILBOX_NULL;
}

/*****************************************************************************
函 数 名  : mailbox_request_channel
接口类型  : 对外接口
功能描述  : 打开一个邮箱通道，准备开始写或者一封邮件。
根据现有的邮箱通道号，创建一个邮箱操作符号，并根据邮箱头填充邮箱操作符信息
输入参数  : struct mb *mailbox 邮箱控制总句柄
unsigned long	  mailcode	-- 待访问邮件的ID
输出参数  : 无
返 回 值  : 一个邮箱通道的操作符
调用函数  :

被调函数  :

修改历史	  :
1.日	期	 : 2012年9月27日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN struct mb_buff *mailbox_get_channel_handle(
                struct mb *mailbox,
                unsigned int mailcode)
{
    struct mb_link          *link_array   = MAILBOX_NULL;
    struct mb_buff                 *mbuff   = MAILBOX_NULL;
    unsigned int            src_id        = 0;
    unsigned int            dst_id        = 0;
    unsigned int            carrier_id    = 0;

	src_id		 = mailbox_get_src_id(mailcode);
	dst_id		 = mailbox_get_dst_id(mailcode);
	carrier_id	 = mailbox_get_carrier_id(mailcode);

    if (src_id == mailbox->local_id) {
        if (dst_id < MAILBOX_CPUID_BUTT) {
            link_array = &mailbox->send_tbl[dst_id];
        } else {
            /*无效目标号，数组越界*/
            (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID, mailcode);
            return MAILBOX_NULL;
        }
    } else if (dst_id == mailbox->local_id) {
        if (src_id < MAILBOX_CPUID_BUTT) {
            link_array = &mailbox->recv_tbl[src_id];
        } else {
            /*无效目标号，数组越界*/
            (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID, mailcode);
            return MAILBOX_NULL;
        }
    } else {
        /*此处已在收发入口判断*/
    }

    if ((MAILBOX_NULL == link_array) || (0 == link_array->carrier_butt)) {
        /*当前两个CPU之间不存在任何邮箱通道*/
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CPU_LINK, mailcode);
        return MAILBOX_NULL;
    }

    /*获得通道操作句柄*/
    if (carrier_id < link_array->carrier_butt) {
        mbuff = &link_array->channel_buff[carrier_id];
    } else {
        /*非法载体号，数组越界*/
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CARRIER_ID, mailcode);
        return MAILBOX_NULL;
    }

    /*检查mail code中 use ID的合法性*/
    if (mailbox_get_use_id(mailcode) >= mailbox_get_use_id(mbuff->config->butt_id)) {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_USER_ID, mailcode);

        #ifndef _DRV_LLT_ /*PC工程允许发送非法use ID，用于测试接收通道代码分支*/
        return MAILBOX_NULL;
        #endif
    }

    return mbuff;
}

/*****************************************************************************
 函 数 名  : mailbox_request_channel
 接口类型  : 对外接口
 功能描述  : 打开一个邮箱通道，准备开始写或者一封邮件。
             根据现有的邮箱通道号，创建一个邮箱操作符号，并根据邮箱头填充邮箱操作符信息
 输入参数  : struct mb *mb     -- 邮箱总句柄
             struct mb_buff ** -- 邮箱通道缓存描述符
             unsigned long     mailcode  -- 待访问邮件的ID
 输出参数  : 无
 返 回 值  : 一个邮箱通道的操作符
 调用函数  :

被调函数  :

修改历史	  :
1.日	期	 : 2012年9月27日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_request_channel(
                struct mb *mb,
                struct mb_buff ** mb_buf,
                unsigned int mailcode)
{
    struct mb_head       *head  = MAILBOX_NULL;
    struct mb_queue      *queue = MAILBOX_NULL;
    struct mb_buff       *mbuff = MAILBOX_NULL;
    int ret_val = MAILBOX_OK;

	mailbox_dpm_device_get();

    *mb_buf = MAILBOX_NULL;
    mbuff = mailbox_get_channel_handle(mb, mailcode);
    if (MAILBOX_NULL == mbuff) {
        ret_val = (int)MAILBOX_ERRO;
        goto request_erro;
    }

	/*通过判断通道保护字，检查通道有没有初始化*/
	head = (struct mb_head*)mbuff->config->head_addr;
	if ((  (MAILBOX_PROTECT1 != head->ulProtectWord1) )
		|| (MAILBOX_PROTECT2 != head->ulProtectWord2)
		||(MAILBOX_PROTECT1 != head->ulProtectWord3)
		|| (MAILBOX_PROTECT2 != head->ulProtectWord4)) {
#if 1/*k3 modify 保护字不正确重新初始化一下邮箱头，不要return影响通信流程，后续再找根因*/
		/*保护字不正确，说明邮箱未初始化，或者内存被踩，报错。*/
		/* do not check cause hifi maybe not pwr on when the first ipc message send */

		mailbox_init_mem(mbuff->config);

		mailbox_logerro_p1(MAILBOX_NOT_READY, mailcode);
#endif
	}

	if(mailbox_get_src_id(mailcode) == mb->local_id) {
		/* 不允许在中断中发邮件*/
		if (MAILBOX_TRUE == mailbox_int_context()) {
//TODO:接下来的开发(IFC for 低功耗)可能需要支持在中断中发送邮件，这里就需要锁中断。
			ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_SEND_MAIL_IN_INT_CONTEXT, mailcode);
			goto request_erro;
		} else {
			if (MAILBOX_OK != mailbox_mutex_lock(&mbuff->mutex)) {
				/*非中断发送，需要资源保护，获取当前通道资源。*/
				ret_val = mailbox_logerro_p1(MAILBOX_CRIT_GUT_MUTEX_LOCK_FAILED, mailcode);
				goto request_erro;
			}
		}
	}

	mbuff->mailcode = mailcode;

    /*共享内存队列，需要依据邮箱头信息对队列操作符进行填充*/
    queue = &mbuff->mail_queue;
    queue->front = queue->base + head->ulFront * sizeof(unsigned int);
    queue->rear  = queue->base + head->ulRear * sizeof(unsigned int);

	mbuff->mb = mb;
	*mb_buf = mbuff;
	return MAILBOX_OK;
request_erro:
	mailbox_out(("###mailbox_request_channel ERR! \n"));
	mailbox_dpm_device_put();
	return ret_val;
}

/*****************************************************************************
函 数 名  : mailbox_release_channel
接口类型  : 对内接口
功能描述  : 关闭邮箱，释放资源。

输入参数  : mb_buff* fpMailBox	- 邮箱通道缓存操作符
输出参数  : 无
返 回 值  : 邮箱关闭是否成功
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月27日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_release_channel(struct mb *mb,
                struct mb_buff *mbuff)
{
    unsigned int         channel_id    = mbuff->channel_id;

	/*需要区分是读还是写*/
	if (mb->local_id == mailbox_get_src_id(channel_id)) {
		if (MAILBOX_TRUE == mailbox_int_context()) {
			/*TODO:接下来的开发(IFC for 低功耗)可能需要支持在中断中发送邮件，
			这里就需要解锁中断。*/
		} else {
			mailbox_mutex_unlock(&mbuff->mutex);
		}
	}

	mailbox_dpm_device_put();
	return MAILBOX_OK;
}

/*****************************************************************************
函 数 名  : mailbox_read_mail
接口类型  : 对内接口
功能描述  : 读取并处理一封邮箱的正文数据内容,接受邮箱数据的数据层入口，
并且调用上层注册的邮件数据处理回调函数
输入参数  : mb_buff*	   pstMailbox  - 邮箱通道操作符

输出参数  : 无
返 回 值  : 读取的邮件数据长度，包括邮件头，返回0表示失败。
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_read_mail(struct mb_buff *mbuff)
{
    struct mb_mail        mail;
    struct mb_cb         *read_cb = MAILBOX_NULL;/*此邮箱通道的功能回调函数队列*/
    struct mb_queue       tmp_queue;
    struct mb_queue      *usr_queue   = MAILBOX_NULL;
    struct mb_queue      *m_queue   = MAILBOX_NULL;
    unsigned int         use_id;
    unsigned int         slice_start;
    unsigned int         to_bottom;
    void                 *usr_handle;
    void                 *usr_data;
    void (*usr_func)(void *mbuf, void *handle, void *data);

	m_queue = &(mbuff->mail_queue);
	usr_queue = &(mbuff->usr_queue);
	mailbox_memcpy((void *) usr_queue, (const void *) m_queue, sizeof(struct mb_queue));

	/*保存临时队列状态,交换读写指针。*/
	tmp_queue.base	 = usr_queue->base;
	tmp_queue.length = usr_queue->length;
	tmp_queue.front  = usr_queue->rear;
	tmp_queue.rear	 = usr_queue->front;

	/*读取邮件的头信息*/
	mailbox_queue_read(usr_queue, (char*)&mail, sizeof(struct mb_mail));

	/*1.检查邮件头，判断读到的消息是否存在异常，包括SN号是否连续、消息滞留时间是否过长。
	2.填充信息读取时间*/
	mailbox_check_mail(mbuff, &mail, m_queue->rear);

	/*把读取时间写回邮箱队列*/
	mailbox_queue_write(&tmp_queue, (char*)&mail, sizeof(struct mb_mail));
	use_id = mailbox_get_use_id(mail.ulMailCode);

	/*检查Use ID的有效性*/
	if (use_id >= mailbox_get_use_id(mbuff->config->butt_id)) {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_USER_ID, mail.ulMailCode);
		goto EXIT;
	}

	read_cb = &mbuff->read_cb[use_id];
	mailbox_mutex_lock(&mbuff->mutex);
	usr_handle = read_cb->handle;
	usr_data = read_cb->data;
	usr_func = read_cb->func;
	mailbox_mutex_unlock(&mbuff->mutex);
	if (MAILBOX_NULL != usr_func) {
		usr_queue->size = mail.ulMsgLength;
        slice_start = (unsigned int)mailbox_get_timestamp();
		usr_func(mbuff, usr_handle , usr_data);

		/*记录可维可测信息*/
#ifdef MAILBOX_OPEN_MNTN
         mailbox_record_receive(&mbuff->mntn, mail.ulMailCode, slice_start);
#endif
	} else {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_READ_CALLBACK_NOT_FIND, mail.ulMailCode);
	}

EXIT:

	/*不管用户有没有用回调读数据，读了多少数据，邮箱队列的读指针都需要按实际
	大小偏移，以保证后面邮件读取的正确性。*/
    to_bottom  = (unsigned int)((m_queue->base + m_queue->length) - m_queue->rear);
	if (to_bottom > (mail.ulMsgLength + sizeof(struct mb_mail))) {
		m_queue->rear += (mail.ulMsgLength + sizeof(struct mb_mail));
	} else {
		m_queue->rear = m_queue->base + ((mail.ulMsgLength +
										  sizeof(struct mb_mail)) - to_bottom);
	}

	/*读保证指针4字节对齐*/
	m_queue->rear = mailbox_align_size(m_queue->rear, MAILBOX_ALIGN);

    return (int)(mailbox_align_size(mail.ulMsgLength, MAILBOX_ALIGN)
            + sizeof(struct mb_mail));

}

/****************************************************************************************************
函 数 名  : mailbox_receive_all_mails
接口类型  : 对内接口
功能描述  : 获取当前邮箱的未读取数据长度，如果长度大于0，依次读取并处理一封邮件，
直到所有数据读取完.
输入参数  : mb_buff*  fpMail -- 某个邮箱通道的操作句柄
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************************************/
MAILBOX_LOCAL int mailbox_receive_all_mails(struct mb_buff *mbuf)
{

    struct mb_queue      *queue;   /* 临时队列信息状态结构体 */
    signed int           size_left;   /* 邮箱未接收消息长度 */
    unsigned int         mail_len = 0;
    int          ret_val = MAILBOX_OK;

	queue = &(mbuf->mail_queue);

     /*计算邮箱中待取数据长度，单位byte, 这里的长度已由邮箱的写功能做到4byte对齐*/
    if (queue->front >= queue->rear) {
        size_left    = (signed int)(queue->front - queue->rear);
    } else {
        size_left    = (signed int)( (queue->length) - ((queue->rear)
                       - (queue->front)) );
    }

    /*若待取数据长度非0，即邮箱内容非空*/
    while (size_left > 0) {
        /*每次从邮箱读取一封邮件，包括邮件头*/
        mail_len = (unsigned int)mailbox_read_mail(mbuf);
        if (0 == mail_len) {
            ret_val = mailbox_logerro_p1(MAILBOX_CRIT_GUT_READ_MAIL, mbuf->channel_id);
        }
        /*更新待取数据长度*/
        size_left -= (signed int)(mail_len);
    }

    if (size_left < 0) {
       return mailbox_logerro_p1(MAILBOX_CRIT_GUT_RECEIVE_MAIL, mbuf->channel_id);
    }
    return ret_val ;
}

/*****************************************************************************
函 数 名  : mailbox_read_channel
接口类型  : 对内接口
功能描述  : 邮箱共享内存通道接受到新数据的处理回调函数.
根据传入的参数(MailBoxID)描述的邮箱通道层次来区分，使用不同的扫描邮箱读取策略:
高24bit有效 通知哪个CPU的哪条通道有邮件到达:扫描此邮箱通道，处理所有邮件。
输入参数  : unsigned long MailBoxID -- 邮箱通道号
输出参数  : 无
返 回 值  : 无
调用函数  : mailbox_receive_all_mails()
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_read_channel(unsigned int channel_id)
{
    struct mb_buff      *mbuf  = MAILBOX_NULL;     /*邮箱操作句柄*/
    struct mb           *mb    = MAILBOX_NULL;
    int       ret_val      = MAILBOX_OK;

    mb = mailbox_get_mb();

    if (MAILBOX_NULL == mb) {
        return (int)MAILBOX_ERRO;
    }

	/*判断方向是否正确,是否为接收通道*/
	if (mb->local_id != mailbox_get_dst_id(channel_id)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_TARGET_CPU, channel_id);
	}

	/*打开此邮箱通道*/
	ret_val = mailbox_request_channel(mb, &mbuf, channel_id);
	if (MAILBOX_OK != ret_val) {
		return ret_val;
	}

	/*接收此邮箱通道的所有邮件*/
	ret_val = mailbox_receive_all_mails(mbuf);

	mailbox_flush_buff(mbuf); /*把邮箱通道操作符的信息写回邮箱头。*/

	/*接收完成，关闭邮箱*/
	if (MAILBOX_OK != mailbox_release_channel(mb, mbuf)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_RELEASE_CHANNEL, channel_id);
	}

	return ret_val;
}

/*****************************************************************************
函 数 名  : mailbox_init_mem
接口类型  : 对内接口
功能描述  : 初始化邮箱通道内存,初始化邮箱头及邮箱体，设置结构初始值和保护字等
输入参数  : pstDrvMbMemCfg -- 某个邮箱内存通道描述符
输出参数  : 无
返 回 值  : 成功或失败
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_init_mem(struct mb_cfg *config)
{
    struct mb_head       *head = (struct mb_head*)config->head_addr;
    unsigned long         data_addr       = config->data_addr;
    unsigned int         data_size       = config->data_size;

	/*这里也属于入参判断*/
	if ((0 == data_addr) || (MAILBOX_NULL == head) || (0 == data_size)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INIT_CORESHARE_MEM, config->butt_id);
	}

	/*初始化邮箱体*/
	mailbox_memset((signed char *)data_addr, 0, data_size);

	/*初始化邮箱头部保护字*/
	mailbox_write_reg(data_addr, MAILBOX_PROTECT1);
	mailbox_write_reg(data_addr + MAILBOX_PROTECT_LEN, MAILBOX_PROTECT2);

	/*初始化邮箱尾部保护字*/
	mailbox_write_reg((data_addr + data_size) - (2*MAILBOX_PROTECT_LEN),
					  MAILBOX_PROTECT1);
	mailbox_write_reg((data_addr + data_size) - MAILBOX_PROTECT_LEN,
					  MAILBOX_PROTECT2);

	/*初始化邮箱头*/
	head->ulFront		  = 0;
	head->ulFrontslice	  = 0;
	head->ulRear		  = head->ulFront;
	head->ulRearslice	  = 0;
	head->ulProtectWord4  = MAILBOX_PROTECT2;
	head->ulProtectWord3  = MAILBOX_PROTECT1;
	head->ulProtectWord2  = MAILBOX_PROTECT2;
	head->ulProtectWord1  = MAILBOX_PROTECT1;

	return MAILBOX_OK;
}

/*****************************************************************************
函 数 名  : mailbox_calculate_space
接口类型  : 对内接口
功能描述  : 统计通道信息，计算需要分配的内存空间
输入参数  : pMailbox  -- 邮箱总句柄
ChCfgTbl  -- 邮箱通道的全局配置表。
CpuID	  -- 注册此通道的CPU号。
输出参数  : 无
返 回 值  : 邮箱操作句柄
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月7日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_calculate_space(
                struct mb           *mb,
                struct mb_cfg    *config,
                unsigned int     cpu_id)
{
    struct mb_link          *send_link    = MAILBOX_NULL;/*指向主结构体的发送通道数组基地址*/
    struct mb_link          *recev_link   = MAILBOX_NULL;/*指向主结构体的接收通道数组基地址*/
    int            ret_val      = MAILBOX_OK;
    unsigned int            src_id       = 0;
    unsigned int            dst_id       = 0;
    unsigned int            carrier_id   = 0;

	send_link	=  mb->send_tbl;
	recev_link	=  mb->recv_tbl;

	while (MAILBOX_MAILCODE_INVALID != config->butt_id) {
		src_id		 = mailbox_get_src_id(config->butt_id);
		dst_id		 = mailbox_get_dst_id(config->butt_id);
		carrier_id	 = mailbox_get_carrier_id(config->butt_id);

		/*检查是不是本CPU发送通道*/
		if (cpu_id == src_id) {
			/*检查目的CPU的有效性*/
			if (dst_id < MAILBOX_CPUID_BUTT) {
				/*记录此CPU连接的最大通道*/
				if ((carrier_id + 1) > send_link[dst_id].carrier_butt) {
					send_link[dst_id].carrier_butt = (carrier_id + 1);
				} else {
					/*不记录*/
				}
			} else {
				/*数组越界*/
				ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID,
											 config->butt_id);
			}
		}
		/*检查是不是本CPU接收通道*/
		if (cpu_id == dst_id) {
			/*检查发送CPU的有效性*/
			if (src_id < MAILBOX_CPUID_BUTT) {
				/*记录此CPU连接的最大通道*/
				if ((carrier_id + 1) > recev_link[src_id].carrier_butt) {
					recev_link[src_id].carrier_butt = (carrier_id + 1);
				} else {
					/*不记录*/
				}
			} else {
				/*数组越界*/
				ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID,
											 config->butt_id);
			}
		}

		config++;
	}

	return ret_val;
}

/*****************************************************************************
函 数 名  : mailbox_init_all_handle
接口类型  : 对内接口
功能描述  : 初始化邮箱的所有通道句柄
输入参数  : pMailbox  -- 邮箱总句柄
ChCfgTbl  -- 邮箱通道的全局配置表。
CpuID	  -- 注册此通道的CPU号。
输出参数  : 无
返 回 值  : 邮箱操作句柄
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月7日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_init_all_handle(
                struct mb           *mb,
                struct mb_cfg    *config,
                unsigned int     cpu_id)
{
    struct mb_queue        *queue  = MAILBOX_NULL;
    unsigned int           direct= MIALBOX_DIRECTION_INVALID; /*标记当前邮箱通道
                                            是不是本核相关的有效通道*/
    int           ret_val      = MAILBOX_OK;
    struct mb_link         *send_link    = MAILBOX_NULL;/*指向主结构体的发送通道
                                                          数组基地址*/
    struct mb_link         *recv_link = MAILBOX_NULL;   /*指向主结构体的接收通道
                                                          数组基地址*/
    struct mb_buff         *mbuf_prob   = &g_mailbox_channel_handle_pool[0];
    struct mb_cb           *cb_prob  = &g_mailbox_user_cb_pool[0];
    struct mb_buff         *mbuf_cur = MAILBOX_NULL;    /*指向正在处理的邮箱通道*/
    unsigned int           channel_sum    = 0;
    unsigned int           use_sum    = 0;
    unsigned int           src_id       = 0;
    unsigned int           dst_id       = 0;
    unsigned int           carrier_id   = 0;
    unsigned int           use_max      = 0;

	send_link  =  mb->send_tbl;
	recv_link  =  mb->recv_tbl;




	/*第二次循环对每个通道句柄分配空间,并赋值。(这段代码变量太多，不方便拆开另建函数)*/
	/*初始化每个邮箱的控制句柄*/
	while (MAILBOX_MAILCODE_INVALID != config->butt_id) {
		direct = MIALBOX_DIRECTION_INVALID;
		src_id		 = mailbox_get_src_id(config->butt_id);
		dst_id		 = mailbox_get_dst_id(config->butt_id);
		carrier_id	 = mailbox_get_carrier_id(config->butt_id);
		use_max 	 = mailbox_get_use_id(config->butt_id);

		printk("******************func = %s line = %d src_id = %d dst_id = %d******************\n",
			   __func__, __LINE__, src_id, dst_id);


		/*检查是不是本CPU发送通道*/
		if (cpu_id == src_id) {
			direct = MIALBOX_DIRECTION_SEND;

			/*没有分配空间则分配空间*/
			if (MAILBOX_NULL == send_link[dst_id].channel_buff) {
				send_link[dst_id].channel_buff = mbuf_prob;
				mbuf_prob += (send_link[dst_id].carrier_butt);
				channel_sum  += (send_link[dst_id].carrier_butt);
				if (channel_sum > MAILBOX_CHANNEL_NUM) {
					return mailbox_logerro_p1(MAILBOX_CRIT_GUT_INIT_CHANNEL_POOL_TOO_SMALL,
											  channel_sum);
				}
			}
			mbuf_cur = &send_link[dst_id].channel_buff[carrier_id];
		}

		/*检查是不是本CPU接收通道*/
		if (cpu_id == dst_id) {
			direct = MIALBOX_DIRECTION_RECEIVE;

			/*没有分配空间则分配空间*/
			if (MAILBOX_NULL == recv_link[src_id].channel_buff) {
				recv_link[src_id].channel_buff = mbuf_prob;
				mbuf_prob += (recv_link[src_id].carrier_butt);
				channel_sum  += (recv_link[src_id].carrier_butt);
				if (channel_sum > MAILBOX_CHANNEL_NUM) {
					return mailbox_logerro_p1(MAILBOX_CRIT_GUT_INIT_CHANNEL_POOL_TOO_SMALL,
											  channel_sum);
				}
			}

			mbuf_cur = &recv_link[src_id].channel_buff[carrier_id];

			/*1。为邮件注册回调函数申请空间*/
			mbuf_cur->read_cb = cb_prob;
			cb_prob += use_max;
			use_sum   += use_max;
			if (use_sum > MAILBOX_USER_NUM) {
				return mailbox_logerro_p1(MAILBOX_CRIT_GUT_INIT_USER_POOL_TOO_SMALL, use_sum);
			}

			/*3.注册邮箱线程回调接口，用于获取共享内存邮箱数据的处理*/
			ret_val = mailbox_process_register(mailbox_get_channel_id(config->butt_id),
											   mailbox_read_channel, mbuf_cur);

			/*4.初始化邮箱共享内存，设置标志位。*/
			ret_val |= mailbox_init_mem(config);

		}

		if ((MIALBOX_DIRECTION_INVALID != direct ) && (MAILBOX_NULL != mbuf_cur)) {
			/*发送通道:发送时需要并发互斥，
			接收通道:需要对回调注册进行互斥*/

			/*给控制句柄赋予邮箱ID号*/
			mbuf_cur->channel_id = mailbox_get_channel_id(config->butt_id);
			mbuf_cur->seq_num = MAILBOX_SEQNUM_START;
#ifdef MAILBOX_OPEN_MNTN
			mbuf_cur->mntn.peak_traffic_left = MAILBOX_QUEUE_LEFT_INVALID;
			mbuf_cur->mntn.mbuff	= mbuf_cur;
#endif
			/*给邮箱配置物理资源*/
			mbuf_cur->config = config;

			/*初始化通道资源*/
			queue = &(mbuf_cur->mail_queue);

			/*初始化邮箱通道的环形队列控制符，以下两项是初始化以后不会再变化的。*/
			queue->length  = mbuf_cur->config->data_size -
							 (MAILBOX_DATA_LEN_PROTECT_NUM * MAILBOX_PROTECT_LEN);
			queue->base    = mbuf_cur->config->data_addr +
							 (MAILBOX_DATA_BASE_PROTECT_NUM * MAILBOX_PROTECT_LEN);


			/*把此通道注册到具体平台*/
			ret_val = mailbox_channel_register(mailbox_get_channel_id(config->butt_id), /*lint !e539*/
											   config->int_src,
											   mailbox_get_dst_id(config->butt_id),
											   direct,
											   &mbuf_cur->mutex);
		}

		config++;
	}

	/*检查内存池大小是否刚好,如果报错，请检查宏设置是否匹配:
	这里检查下面三个数组的空间是否适配。
	g_mailbox_global_cfg_tbl[];
	g_mailbox_channel_handle_pool[MAILBOX_CHANNEL_NUM];
	g_mailbox_user_cb_pool[MAILBOX_USER_NUM];
	*/
    if((unsigned int)MAILBOX_CHANNEL_NUM != channel_sum ) {
		ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INIT_CHANNEL_POOL_TOO_LARGE,
                                    ((MAILBOX_CHANNEL_NUM<<16) | channel_sum));
	}

	if(MAILBOX_USER_NUM != use_sum) {
		ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INIT_USER_POOL_TOO_LARGE, use_sum);
	}

	return ret_val;
}

/*****************************************************************************
函 数 名  : mailbox_create_box
接口类型  : 对内接口
功能描述  : 创建邮箱操作句柄,申请邮箱总操作句柄空间，并初始化邮箱通道资源.
输入参数  : ChCfgTbl  -- 邮箱通道的全局配置表。
CpuID	  -- 注册此通道的CPU号。
输出参数  : 无
返 回 值  : 邮箱操作句柄
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月7日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_LOCAL int mailbox_create_box(
                struct mb          *mb,
                struct mb_cfg   *config,
                unsigned int    cpu_id)
{
	mb->local_id = cpu_id;

	printk("<<<<<<<<<<<<<<mailbox_create_box cpu_id = %d>>>>>>>>>>>>>>\n", cpu_id);

	/*第一次循环检查通道号的有效性，并统计每个核间通道数组的空间*/
	if(MAILBOX_OK !=   mailbox_calculate_space(mb, config, cpu_id)) {
		return mailbox_logerro_p0(MAILBOX_ERR_GUT_CALCULATE_SPACE);
	}

	/*第二次循环对每个通道句柄分配空间,并赋值。*/
	/*初始化每个邮箱的控制句柄*/
	return mailbox_init_all_handle(mb, config, cpu_id);
}

/*****************************************************************************
函 数 名  : mem_remap_type
接口类型  : 对内接口
功能描述  : 将一段ddr内存，映射到虚拟内存中
输入参数  :	phys_addr 物理地址，size 物理地址大小， pgprot 映射属性
输出参数  :  无
返 回 值  : 内核虚拟地址

日	期	  : 2014年11月17日
修改内容  :  新生成函数
*****************************************************************************/
void *mem_remap_type(unsigned long phys_addr, size_t size, pgprot_t pgprot)
{
    int i;
    u8* vaddr;
    int npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;
    unsigned long offset = phys_addr & (PAGE_SIZE - 1);
    struct page **pages;
    pages = vmalloc(sizeof(struct page *) * npages);
    if (!pages)
    {
        printk(KERN_ERR "%s: vmalloc return NULL!\n", __FUNCTION__);
        return NULL;
    }
    pages[0] = phys_to_page(phys_addr);
    for (i = 0; i < npages - 1 ; i++) {
        pages[i + 1] = pages[i] + 1;
    }
    vaddr = (u8*)vmap(pages, npages, VM_MAP, pgprot);
    if(vaddr == 0)
    {
        printk(KERN_ERR "%s: vmap return NULL!\n", __FUNCTION__);
    }
    else
    {
        vaddr += offset;
    }
    vfree(pages);
    printk(KERN_DEBUG "%s: phys_addr:0x%08lx size:0x%08lx npages:%d vaddr:%p offset:0x%08lx\n", __FUNCTION__, phys_addr, (unsigned long)size, npages, vaddr, offset);
    return (void *)vaddr;
}

/*****************************************************************************
函 数 名  : mailbox_init
接口类型  : 对外接口
功能描述  : 邮箱模块平台适配部分初始化
输入参数  :

输出参数  : 无
返 回 值  : 线程操作句柄
调用函数  :
被调函数  : mailbox_init_platform()

修改历史	  :
1.日	期	 : 2012年9月24日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

详细描述: 初始化邮箱并初始化与平台相关的差异化部分，在邮箱初始化的时候调用。
*****************************************************************************/
MAILBOX_GLOBAL int mailbox_init(void)
{
	unsigned long offset = 0;
	int i = 0;
	struct mb_head *head = NULL;

	if (MAILBOX_INIT_MAGIC == g_mailbox_handle.init_flag) {
		/*考虑到单核下电重启，静态数据不会丢失，这里只打印告警，
		返回错误的话，后面的平台初始化将调不到，IPC中断无法注册*/
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_ALREADY_INIT, g_mailbox_handle.init_flag);
	}

	printk("func = %s, line = %d baseaddr = 0x%x\n", __func__, __LINE__, MAILBOX_MEM_BASEADDR);

	g_shareMemBase = mem_remap_nocache(MAILBOX_MEM_BASEADDR, MAILBOX_MEM_LENGTH);
	/*初始化邮箱中的数据*/
//memset(g_shareMemBase,0x0,MAILBOX_MEM_LENGTH);

	if(NULL == g_shareMemBase) {
		printk("func = %s, mmap mailbox mem error!!\n", __func__);
		return mailbox_logerro_p0(MAILBOX_CRIT_GUT_MEMORY_CONFIG);
	}

	offset = (unsigned long)g_shareMemBase - MAILBOX_MEM_BASEADDR;
	for(i = 0; i < MAILBOX_GLOBAL_CHANNEL_NUM; i++) {
		g_mailbox_global_cfg_tbl[i].head_addr = g_mailbox_global_cfg_tbl[i].head_addr + offset;
		g_mailbox_global_cfg_tbl[i].data_addr = g_mailbox_global_cfg_tbl[i].data_addr + offset;

		printk("i = %d, head_addr = 0x%lx, data_addr = 0x%lx\n", i,
			   g_mailbox_global_cfg_tbl[i].head_addr, g_mailbox_global_cfg_tbl[i].data_addr);

		/*初始化邮箱头*/
		head = (struct mb_head *)g_mailbox_global_cfg_tbl[i].head_addr;
		head->ulFront = 0x0;
		head->ulRear = 0x0;
		head->ulFrontslice = 0x0;
		head->ulRearslice = 0x0;
	}

	/*TODO:进行单核下电重启特性开发时，这行需要删除*/
	mailbox_memset(&g_mailbox_handle, 0x00, sizeof(struct mb));

#ifdef MAILBOX_OPEN_MNTN
    if ((MAILBOX_HEAD_BOTTOM_ADDR > (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN)) ||
       (MAILBOX_MEMORY_BOTTOM_ADDR > (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_LENGTH)))
    {
        mailbox_out(("mailbox address overflow: headbuttom valid(0x%lx), config(0x%x)!\n\
          \r                          databuttom valid(0x%x), config(0x%x)!"RT,
        (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN), MAILBOX_HEAD_BOTTOM_ADDR,
        (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_LENGTH), MAILBOX_MEMORY_BOTTOM_ADDR));
        return mailbox_logerro_p0(MAILBOX_CRIT_GUT_MEMORY_CONFIG);
    }
#endif

	/*初始化邮箱主体部分，创建邮箱总句柄。*/
	if (MAILBOX_OK != mailbox_create_box(&g_mailbox_handle,
										 &g_mailbox_global_cfg_tbl[0], MAILBOX_LOCAL_CPUID)) {
		return mailbox_logerro_p0(MAILBOX_ERR_GUT_CREATE_BOX);
	}

	/*初始化平台差异部分*/
	if (MAILBOX_OK != mailbox_init_platform()) {
		return mailbox_logerro_p0(MAILBOX_ERR_GUT_INIT_PLATFORM);
	}

	g_mailbox_handle.init_flag = MAILBOX_INIT_MAGIC;

#ifndef _DRV_LLT_
//mailbox_ifc_test_init();
#endif

//fixme: there isn't go to unremap
	g_slice_reg = (void*)ioremap(SLICE_REG, 0x4);
	if (NULL == g_slice_reg) {
		printk("ioremap of slice reg fail.\n");
	}

	mailbox_out(("mb init OK!\n"));

	return MAILBOX_OK;
}

/*邮箱对外接口开始*/
/*****************************************************************************
函 数 名  : MAILBOX_RegisterRecvFuncByHandle
功能描述  : 核间邮件数据接收回调函数的注册
输入参数  : struct mb				*pMailBox	 -- 某个核的邮箱总句柄。
unsigned long				MailId		-- 接收到的邮件的id号。与发送方的邮件发送目标ID号一致。
mb_cb_func		pFun		-- 邮件数据接收处理回调函数
输出参数  : 无
返 回 值  : MAILBOX_OK, 异常返回值
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2012年9月29日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN int mailbox_register_cb(
                unsigned int  mailcode,
                void (*cb)(void *mbuf, void *handle, void *data),
                void *usr_handle,
                void *usr_data)
{
    struct mb_cb           *read_cb    = MAILBOX_NULL;
    struct mb_buff         *mbuf = MAILBOX_NULL;
    struct mb              *mb     = MAILBOX_NULL;
    unsigned int           dst_id;

	mb = &g_mailbox_handle;/*有可能在初始化过程中注册*/

	/*	允许注册空回调，相当于UnRegister
	if (MAILBOX_NULL == pFun)
	{
	return mailbox_logerro_p1(MAILBOX_ERR_GUT_MAILBOX_NULL_PARAM, mailcode);
	}
	*/
	/*往某个CPU的某个邮箱通道中的某个邮件应用用注册回调函数*/
	dst_id = mailbox_get_dst_id(mailcode);

	printk("mb->local_id = %d dst_id = %d\n", mb->local_id, dst_id);

	if (mb->local_id != dst_id) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_TARGET_CPU, mailcode);
	}

	mbuf = mailbox_get_channel_handle(mb, mailcode);
	if (MAILBOX_NULL == mbuf) {
		/*找不到，此通道未初始化。*/
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID, mailcode);
	}

	/*检查OK, 赋值给回调函数指针*/
	read_cb = &mbuf->read_cb[mailbox_get_use_id(mailcode)];
	if (MAILBOX_NULL != read_cb->func) {
		/*mailbox_logerro_p1(MAILBOX_WARNING_USER_CALLBACK_ALREADY_EXIST, mailcode);*/
	}

	mailbox_mutex_lock(&mbuf->mutex);
	read_cb->handle = usr_handle;
	read_cb->data	= usr_data;
	read_cb->func = cb;
	mailbox_mutex_unlock(&mbuf->mutex);

	return MAILBOX_OK;
}

/*初始化留给用户空间的环形fifo描述符*/
MAILBOX_EXTERN int mailbox_init_usr_queue(struct mb_buff *mb_buf)
{
    unsigned int hsize = sizeof(struct mb_mail);
    struct mb_queue * usrqu = &mb_buf->usr_queue;

	/*初始化用户环形fifo,需要跳过邮箱消息头部分*/
	mailbox_memcpy((void*)usrqu, (const void*)&mb_buf->mail_queue, sizeof(struct mb_queue));
	if (hsize >  mailbox_queue_left(usrqu->rear, usrqu->front, usrqu->length)) {
		return mailbox_logerro_p1(MAILBOX_FULL, mb_buf->mailcode);
	}

	if (hsize + usrqu->front >= usrqu->base + usrqu->length) {
		usrqu->front = usrqu->front + hsize - usrqu->length;
	} else {
		usrqu->front =	usrqu->front + hsize;
	}
	return MAILBOX_OK;
}

/*获取一个邮箱物理通道buff*/
MAILBOX_EXTERN int mailbox_request_buff(unsigned int mailcode,  void* mb_buf)
{
    struct mb        *mailbox     = MAILBOX_NULL;
    int     ret_val       = MAILBOX_OK;
    struct mb_buff ** mbuf  = (struct mb_buff **)mb_buf;

	mailbox 	= mailbox_get_mb();
	*mbuf = MAILBOX_NULL;
	if (MAILBOX_NULL == mailbox) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INPUT_PARAMETER, mailcode);
	}

	/*检查是否为发送通道*/
	if (mailbox->local_id != mailbox_get_src_id(mailcode)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_SRC_CPU, mailcode);
	}

	/*获得此邮件邮箱通道的操作句柄: open mail*/
	ret_val = mailbox_request_channel(mailbox, mbuf, mailcode);
	if (MAILBOX_OK == ret_val) {
		(*mbuf)->mb = mailbox;
		ret_val = mailbox_init_usr_queue(*mbuf);
		if (MAILBOX_OK == ret_val) {
			return	MAILBOX_OK;
		} else {
			mailbox_release_channel(mailbox, *mbuf);
			*mbuf = MAILBOX_NULL;
			return ret_val;
		}
	} else {
		return ret_val;
	}
}

/*把用户数据填入邮箱物理通道buff*/
MAILBOX_EXTERN int mailbox_write_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned int         size)
{
	if ((size  <= mailbox_queue_left(queue->rear, queue->front, queue->length)) &&
		(size + sizeof(struct mb_mail)	<= mailbox_queue_left(queue->rear, queue->front, queue->length))
	   ) {
		return mailbox_queue_write(queue, (char*)data, size);
	}
	return 0;
}

/*读取邮箱物理通道数据*/
MAILBOX_EXTERN int mailbox_read_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned int         size)
{
	return mailbox_queue_read(queue, (char*)data, size);
}
/*需要邮箱主体提供的接口，在gut.c里面实现*/

/*封信，准备发送*/
MAILBOX_EXTERN int mailbox_sealup_buff(struct mb_buff * mb_buf , unsigned int usr_size)
{

    struct mb_mail        mail = {0};
    struct mb_queue      *m_queue   = MAILBOX_NULL;
    unsigned int         time_stamp;
    unsigned long         mail_addr;

	m_queue = &mb_buf->mail_queue;

    /*判断是否超过单次发送最大大小*/
    if (usr_size > (mb_buf->config->single_max - sizeof(struct mb_mail) )){
        return (int) mailbox_logerro_p2(MAILBOX_ERR_GUT_WRITE_EXCEED_MAX_SIZE,
            usr_size ,mb_buf->mailcode);
    } else {
    }

    time_stamp = (unsigned int)mailbox_get_timestamp();
    /*填充消息头*/
    mail.ulPartition   =  MAILBOX_MSGHEAD_NUMBER;
    mail.ulWriteSlice  =  time_stamp;
    mail.ulReadSlice   =  0;
    mail.ulPriority    =  0;/*此属性和OM核对已废弃，不使用*/
    mail.ulSeqNum      =  mb_buf->seq_num;
    mail.ulMsgLength   =  usr_size ;
    mail.ulMailCode    =  mb_buf->mailcode;

    if (MAILBOX_SEQNUM_START == mb_buf->seq_num) {
        (void)mailbox_logerro_p1(MAILBOX_INFO_SEND_FIRST_MAIL, mb_buf->mailcode);
    }

    mb_buf->seq_num++;

	/*向邮箱队列中写入邮件头，并更新队列状态记录临时结构体*/
	mail_addr = m_queue->front;
	mailbox_queue_write(m_queue, (char*)(&mail), sizeof(struct mb_mail));

	/*更新邮箱环形缓存信息*/
	m_queue->front = mailbox_align_size(mb_buf->usr_queue.front, MAILBOX_ALIGN);

	mailbox_flush_buff(mb_buf); /*把邮箱通道操作符的信息写回邮箱头。*/

#ifdef MAILBOX_OPEN_MNTN

	mailbox_record_send(&(mb_buf->mntn), mb_buf->mailcode, time_stamp, mail_addr);
#endif

	/*准备下一封邮件写入*/
	return mailbox_init_usr_queue(mb_buf);
}

/*****************************************************************************
函 数 名  : mailbox_flush_buff
接口类型  : 对内接口
功能描述  : 把邮箱消息队列的头尾指针写入邮箱头

输入参数  : mb_buff* fpMailBox	- 邮箱通道操作符
输出参数  : 无
返 回 值  : 邮箱关闭是否成功
调用函数  :
被调函数  :

修改历史	  :
1.日	期	 : 2013年5月08日
作	  者   : 莫南 00176101
修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN int mailbox_flush_buff( struct mb_buff *mbuff)
{
    struct mb_head       *head = MAILBOX_NULL;
    struct mb_queue      *queue   = MAILBOX_NULL;
    unsigned int         channel_id    = mbuff->channel_id;
    struct mb *mb         = mbuff->mb;
    /*把邮箱通道操作符的信息写回邮箱头。*/
    head = (struct mb_head*)mbuff->config->head_addr;
    queue   = &mbuff->mail_queue;

    /*需要区分是读还是写*/
    if (mb->local_id == mailbox_get_src_id(channel_id)) {
        /*写关闭，更新邮箱头写指针,同时释放邮箱资源*/
        head->ulFront      = (unsigned int)(queue->front - queue->base ) / sizeof(unsigned int) ;
        head->ulFrontslice = (unsigned int)mailbox_get_timestamp();

    } else if (mb->local_id == mailbox_get_dst_id(channel_id)) {
        /*读关闭，只更新邮箱头读指针*/
        head->ulRear        =  (unsigned int)(queue->rear - queue->base ) / sizeof(unsigned int);
        head->ulRearslice   =  (unsigned int)mailbox_get_timestamp();
    }

	return MAILBOX_OK;
}

MAILBOX_EXTERN int mailbox_send_buff(struct mb_buff * mbuf)
{
	return mailbox_delivery(mbuf->channel_id);
}

MAILBOX_EXTERN int mailbox_release_buff(struct mb_buff * mbuf)
{
	return mailbox_release_channel(mbuf->mb, mbuf);
}

MAILBOX_EXTERN unsigned long mailbox_virt_to_phy(unsigned long  virt_addr)
{
	unsigned long offset = 0;
	if(NULL == g_shareMemBase) {
		g_shareMemBase = ioremap(MAILBOX_MEM_BASEADDR, MAILBOX_MEM_LENGTH);
	}
	offset = (unsigned long)g_shareMemBase - MAILBOX_MEM_BASEADDR;

	return (virt_addr - offset);
}

MAILBOX_EXTERN unsigned long mailbox_phy_to_virt(unsigned long  phy_addr)
{
	unsigned long offset = 0;
	if(NULL == g_shareMemBase) {
		g_shareMemBase = ioremap(MAILBOX_MEM_BASEADDR, MAILBOX_MEM_LENGTH);
	}
	offset = (unsigned long)g_shareMemBase - MAILBOX_MEM_BASEADDR;


	return (phy_addr + offset);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

