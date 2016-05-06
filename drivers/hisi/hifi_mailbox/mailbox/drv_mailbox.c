/******************************************************************************

				  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名	 : drv_mailbox.c
  版 本 号	 : 初稿
  作	者	 : 苏庄銮 59026
  生成日期	 : 2012年12月15日
  最近修改	 :
  功能描述	 : mailbox接口
  函数列表	 :

  修改历史	 :
  1.日	  期   : 2012年12月15日
	作	  者   : 苏庄銮 59026
	修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "drv_mailbox_cfg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 函数声明
*****************************************************************************/
unsigned int mailbox_send_msg(
                unsigned int            mailcode,
                void                    *data,
                unsigned int            length);

unsigned int mailbox_reg_msg_cb(
                unsigned int             mailcode,
                mb_msg_cb                 func,
                void                     *data);

unsigned int mailbox_read_msg_data(
                void                   *mail_handle,
                 char                  *buff,
                unsigned int          *size);
/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : DRV_MAILBOX_SENDMAIL
 功能描述  : 邮箱用户发送邮件数据
 输入参数  : MailCode	-- 邮编, 指定邮件发送目标
			 pData		-- 指向邮件数据的指针
			 Length 	-- 待发送数据长度, 单位byte
 输出参数  : 无
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月28日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length)
{
	return mailbox_send_msg(MailCode, pData, Length);
}

/*****************************************************************************
 函 数 名  : DRV_MAILBOX_REGISTERRECVFUNC
 功能描述  : 注册邮件数据接收函数
 输入参数  : MailCode	-- 数据接收函数处理的对象邮编
			 pFun		-- 邮件数据接收处理函数指针
			 UserHandle -- 用户定义句柄, 数据接收函数被调用时会作为入参, 无则填空
 输出参数  : 无
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年9月29日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle)
{
	return mailbox_reg_msg_cb(MailCode, pFun, UserHandle);
}

/*****************************************************************************
 函 数 名  : DRV_MAILBOX_READMAILDATA
 功能描述  : 邮箱用户在数据接收回调函数中调用, 从邮箱中读取一封最先到达的邮件
 输入参数  : MailHandle -- 邮箱句柄, 数据接收回调函数入参
			 pData		-- 保存待读出数据的缓存地址
			 *pSize 	-- 缓存长度, 单位byte, 需要大于待读取邮件长度
 输出参数  : *pSize 	-- 实际读取长度, 单位byte
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史	   :
  1.日	  期   : 2012年10月26日
	作	  者   : 莫南 00176101
	修改内容   : 新生成函数

*****************************************************************************/
unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize)
{
	return mailbox_read_msg_data(MailHandle, (char *)pData, pSize);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

