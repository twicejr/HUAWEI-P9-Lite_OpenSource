
#ifndef __DRV_MAILBOX_MSG_H__
#define __DRV_MAILBOX_MSG_H__

/*****************************************************************************
1 其他头文件包含
*****************************************************************************/
#include "drv_mailbox_cfg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*生成远程调用发起函数*/
#define IFC_GEN_CALL0(id, name) 	  _IFC_GEN_CALLx(0, id, name)
#define IFC_GEN_CALL1(id, name, ...)  _IFC_GEN_CALLx(1, id, name, __VA_ARGS__)
#define IFC_GEN_CALL2(id, name, ...)  _IFC_GEN_CALLx(2, id, name, __VA_ARGS__)
#define IFC_GEN_CALL3(id, name, ...)  _IFC_GEN_CALLx(3, id, name, __VA_ARGS__)
#define IFC_GEN_CALL4(id, name, ...)  _IFC_GEN_CALLx(4, id, name, __VA_ARGS__)
#define IFC_GEN_CALL5(id, name, ...)  _IFC_GEN_CALLx(5, id, name, __VA_ARGS__)
#define IFC_GEN_CALL6(id, name, ...)  _IFC_GEN_CALLx(6, id, name, __VA_ARGS__)

/*生成带各个参数的远程调用执行函数*/
#define IFC_GEN_EXEC0(name) 	 __IFC_GEN_EXECx(0, name)
#define IFC_GEN_EXEC1(name, ...) __IFC_GEN_EXECx(1, name, __VA_ARGS__)
#define IFC_GEN_EXEC2(name, ...) __IFC_GEN_EXECx(2, name, __VA_ARGS__)
#define IFC_GEN_EXEC3(name, ...) __IFC_GEN_EXECx(3, name, __VA_ARGS__)
#define IFC_GEN_EXEC4(name, ...) __IFC_GEN_EXECx(4, name, __VA_ARGS__)
#define IFC_GEN_EXEC5(name, ...) __IFC_GEN_EXECx(5, name, __VA_ARGS__)
#define IFC_GEN_EXEC6(name, ...) __IFC_GEN_EXECx(6, name, __VA_ARGS__)

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


/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*注册远程调用执行函数*/
#define mailbox_ifc_register(id, name) mailbox_ifc_register_exec(id ,IFC_GEN_EXEC_NAME(name))


unsigned long mailbox_init(void);



unsigned long mailbox_send_msg(
	unsigned long			 mailcode,
	void					*data,
	unsigned long			 length);


unsigned long  mailbox_reg_msg_cb(
	unsigned long			  mailcode,
	mb_msg_cb				  func,
	void					 *data);


unsigned int mailbox_read_msg_data(
	void				*MailHandle,
	char				*pData,
	unsigned int		*pSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_mailbox_msg.h */


