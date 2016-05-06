/******************************************************************************

			  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
文 件 名   : drv_mailbox_ifc.h
版 本 号   : 初稿
作	  者   : 莫南 00176101
生成日期   : 2013年4月11日
最近修改   :
功能描述   : mailbox&跨核邮箱驱动软件，核间调用主体代码,包含文件。
函数列表   :

修改历史   :
1.日	期	 : 2013年4月11日
作	  者   : 莫南 00176101
修改内容   : 创建文件
******************************************************************************/
#ifndef __DRV_MAILBOX_IFC_H__
#define __DRV_MAILBOX_IFC_H__


/*****************************************************************************
1 头文件包含
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
远程函数调用规则与约束:
*****************************************************************************/
/*
  远程调用接口形式不固定，接口定义开放给用户，本模块提供一种机制:
	用户可以按自己的实际需要直接定义并生成任意一个远程函数，且此远程函数有以下约束：
	1.	函数的返回值只能为int型，不能返回包含其他数据长度的指针。
		函数调用超时返回错误号: MAILBOX_TIME_OUT
	2.	函数的参数目前最多支持6个。
	3.	函数的参数实际上都被看成指针处理，只能有如下7种类型的参数：
		1>	IFC_INFIX:	定长指针入参，其大小在函数生成的时候被定义并生效。
		2>	IFC_OUTFIX: 定长指针出参，其大小在函数生成的时候被定义并生效。
		3>	IFC_BIFIX:	定长指针双参，其大小在函数生成的时候被定义并生效。
		4>	IFC_INVAR:	变长指针入参，其大小由下一个固定大小的变量参数定义，在函数被调用时生效。
		5>	IFC_OUTVAR: 变长指针出参，其大小由下一个固定大小的变量参数定义，在函数被调用时生效。
		6>	IFC_BIVAR:	变长指针双参，其大小由下一个固定大小的变量参数定义，在函数被调用时生效。
		7>	IFC_INCNT:	4字节常量入参，

	4.	如果某个参数为可变大小参数，那么他的下一个参数必需是固定大小的变量参数，并且后者在函数调用过程中将描述前者的大小。
	5.	函数调用可配置为等待核间返回的调用和不等待核间返回的调用（丢弃式调用）。
	6.	注意(入参+双参)的大小或者(出参+双参)的大小不能超过邮箱单个邮件的最大大小。
*/
/*****************************************************************************
  1 宏定义
*****************************************************************************/
#define IFC_IN		0x1 	/*入参*/
#define IFC_OUT 	0x2 	/*出参*/
#define IFC_BI		0x4 	/*双参*/

#define IFC_CNT 		(0x1 << 8)	 /*四字节常量*/
#define IFC_FIX 		(0x2 << 8)	 /*固定大小指针*/
#define IFC_VAR 		(0x4 << 8)	 /*可变大小指针*/

#define IFC_INCNT		(IFC_IN  | IFC_CNT)
#define IFC_INFIX		(IFC_IN  | IFC_FIX)
#define IFC_OUTFIX		(IFC_OUT | IFC_FIX)
#define IFC_BIFIX		(IFC_BI  | IFC_FIX)
#define IFC_INVAR		(IFC_IN  | IFC_VAR)
#define IFC_OUTVAR		(IFC_OUT | IFC_VAR)
#define IFC_BIVAR		(IFC_BI  | IFC_VAR)

/*远程调用函数的最大参数个数*/
#define IFC_MAX_ARG 	 (6)

#define IFC_LAUNCH		  0
#define IFC_RESPONSE	  1

#define IFC_INLINE	static __inline

#define IFC_WAIT_FOREVER			(0xffffffff)

#ifdef _DRV_LLT_
#define IFC_DEBUG_PARAM
#endif

#ifdef IFC_DEBUG_PARAM
#define _ifc_chk_arg(ph, db, sb)	   __ifc_chk_arg(ph, db, sb)
#define _ifc_dbg_arg(ph, db, sb, df)   __ifc_dbg_arg(ph, db, sb, df)
#else
#define _ifc_chk_arg(ph, db, sb)
#define _ifc_dbg_arg(ph, db, sb, df)
#endif

#define IFC_ALIGN					sizeof(unsigned int)
#define ifc_align_size(a,p) 					(((a)+((p)-1)) & ~((p)-1))

#ifdef _DRV_LLT_
#define C_CALL_ARG_R2L	 /*C语言调用参数从右到左解析*/
#endif
/*****************************************************************************
  2 结构体定义
*****************************************************************************/
/*定义远程函数调用消息头数据结构体*/

struct ifc_param {
	unsigned int type;  /*记录参数类型，出参，入参等，IFC_INVAL*/
	unsigned int size;  /*记录定长参数大小*/
};

struct ifc_head {
	unsigned int		  scode;			/* 发起远程调用邮件编号。*/
	unsigned int		  rcode;			/* 执行方返回时的邮件号。*/
	unsigned int		  stamp;			/* 时间戳，用于筛选超时滞后响应。*/
	unsigned int		  retval;			/* 执行方函数调用返回值。*/
	unsigned int		  needret;			/* 执行方函数调用返回值。*/
	unsigned int		  argv[IFC_MAX_ARG];/* 执行方函数调用返回值,在out buff中的保存地址。*/
	unsigned int		  data; 			/* 消息头和填充空间之后的用户数据线性空间起始地址*/
	unsigned int        data_phy_addr;

#ifdef IFC_DEBUG_PARAM		/*对IFC中的宏中 参数进行调试*/
	struct ifc_param	  param_tbl[IFC_MAX_ARG];
	signed int 		  param_prob;
#endif
};

struct ifc_arg {
	unsigned int		  addr; 	 /* 输出参数地址 */
	unsigned int		  size; 	 /* 输出参数长度 */
};

/*定义远程函数调用消息头数据结构体*/
struct ifc_mb {
	void				 *mbuf; 				/* 邮箱邮件的总描述符号*/
	struct ifc_arg		  argo[IFC_MAX_ARG];	/* 存储输出参数空间的数组*/
	struct ifc_head 	  head; 				/* 待写入邮件中的ifc消息头*/
	void				 *waitsem;				/* 等待调用返回的信号量*/
	unsigned int		  total_size;			/* 邮件数据长度，包括:ifc消息头+空白填充+加数据的总长度*/
	unsigned int		  data_size;			/* ifc数据长度,不包括ifc消息头和填充部分*/
	unsigned long         data_vitrual_addr;
};

#ifdef C_CALL_ARG_R2L
/*vs pc工程 函数参数从右往左计算*/
/*调用核:把输出参数保存在临时数组的宏*/
#define _IFC_ADD_ARG0(ary, p)
#define _IFC_ADD_ARG1(ary, d1, t1, a1, s1)						 __ifc_arg_out(ary, d1, (unsigned int)a1, s1, 0)
#define _IFC_ADD_ARG2(ary, d2, t2, a2, s2, d1, t1, a1, s1, ...)  _IFC_ADD_ARG1(ary, d1, t1, a1, s1); __ifc_arg_out(ary, d2, (unsigned int)a2 ,s2, (unsigned int)a1)
#define _IFC_ADD_ARG3(ary, d3, t3, a3, s3, d2, t2, a2, s2, ...)  _IFC_ADD_ARG2(ary, d2, t2, a2, s2, __VA_ARGS__); __ifc_arg_out(ary, d3, (unsigned int)a3 ,s3, (unsigned int)a2)
#define _IFC_ADD_ARG4(ary, d4, t4, a4, s4, d3, t3, a3, s3, ...)  _IFC_ADD_ARG3(ary, d3, t3, a3, s3, __VA_ARGS__); __ifc_arg_out(ary, d4, (unsigned int)a4 ,s4, (unsigned int)a3)
#define _IFC_ADD_ARG5(ary, d5, t5, a5, s5, d4, t4, a4, s4, ...)  _IFC_ADD_ARG4(ary, d4, t4, a4, s4, __VA_ARGS__); __ifc_arg_out(ary, d5, (unsigned int)a5 ,s5, (unsigned int)a4)
#define _IFC_ADD_ARG6(ary, d6, t6, a6, s6, d5, t5, a5, s5, ...)  _IFC_ADD_ARG5(ary, d5, t5, a5, s5, __VA_ARGS__); __ifc_arg_out(ary, d6, (unsigned int)a6 ,s6, (unsigned int)a5)

/*调用核: 把输入参数压入邮箱用户数据缓存的宏*/ /*往邮箱buf推入数据,同时把返回参数地址暂存*/
/*按x86 c语言调用规范，从右往左压参数*/
#define _IFC_PUSHDATA0(d, av, p)
#define _IFC_PUSHDATA1(d, av, d1, t1, a1, s1)					  __ifc_push_arg(d, av, d1, (unsigned int)a1, s1, 0)
#define _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, d1, t1, a1, s1)	  _IFC_PUSHDATA1(d, av, d1, t1, a1, s1); __ifc_push_arg(d, av, d2, (unsigned int)a2 ,s2, (unsigned int)a1)
#define _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, d2, t2, a2, s2,...) _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, __VA_ARGS__); __ifc_push_arg(d, av, d3, (unsigned int)a3 ,s3, (unsigned int)a2)
#define _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, d3, t3, a3, s3,...) _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, __VA_ARGS__); __ifc_push_arg(d, av, d4, (unsigned int)a4 ,s4, (unsigned int)a3)
#define _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, d4, t4, a4, s4,...) _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, __VA_ARGS__); __ifc_push_arg(d, av, d5, (unsigned int)a5 ,s5, (unsigned int)a4)
#define _IFC_PUSHDATA6(d, av, d6, t6, a6, s6, d5, t5, a5, s5,...) _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, __VA_ARGS__); __ifc_push_arg(d, av, d6, (unsigned int)a6 ,s6, (unsigned int)a5)

/*执行核: 把双向参数从输入缓存拷贝到输出缓存的宏*/
#define _IFC_PCOPY0(in, out, av, ao, p)
#define _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1)					  __ifc_copy_arg(in, out, d1, s1, av, ao)
#define _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, d1, t1, a1, s1)	  _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1); __ifc_copy_arg(in, out, d2, s2, av, ao)
#define _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, d2, t2, a2, s2, ...) _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, __VA_ARGS__); __ifc_copy_arg(in, out, d3, s3, av, ao)
#define _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, d3, t3, a3, s3, ...) _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, __VA_ARGS__); __ifc_copy_arg(in, out, d4, s4, av, ao)
#define _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, d4, t4, a4, s4, ...) _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, __VA_ARGS__); __ifc_copy_arg(in, out, d5, s5, av, ao)
#define _IFC_PCOPY6(in, out, av, ao, d6, t6, a6, s6, d5, t5, a5, s5, ...) _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, __VA_ARGS__); __ifc_copy_arg(in, out, d6, s6, av, ao)

/*执行核:计算函数输出参数总大小的宏*/
#define _IFC_OUTSIZE0(av, p)								   0
#define _IFC_OUTSIZE1(av, d1, t1, a1, s1)					   __ifc_out_size(d1, s1, av)
#define _IFC_OUTSIZE2(av, d2, t2, a2, s2, d1, t1, a1, s1)	   _IFC_OUTSIZE1(av, d1, t1, a1, s1) + __ifc_out_size(d2, s2, av)
#define _IFC_OUTSIZE3(av, d3, t3, a3, s3, d2, t2, a2, s2,...)  _IFC_OUTSIZE2(av, d2, t2, a2, s2, __VA_ARGS__) + __ifc_out_size(d3, s3, av)
#define _IFC_OUTSIZE4(av, d4, t4, a4, s4, d3, t3, a3, s3,...)  _IFC_OUTSIZE3(av, d3, t3, a3, s3, __VA_ARGS__) + __ifc_out_size(d4, s4, av)
#define _IFC_OUTSIZE5(av, d5, t5, a5, s5, d4, t4, a4, s4,...)  _IFC_OUTSIZE4(av, d4, t4, a4, s4, __VA_ARGS__) + __ifc_out_size(d5, s5, av)
#define _IFC_OUTSIZE6(av, d6, t6, a6, s6, d5, t5, a5, s5,...)  _IFC_OUTSIZE5(av, d5, t5, a5, s5, __VA_ARGS__) + __ifc_out_size(d6, s6, av)
#else
/*调用核:单板gcc编译函数参数从左往右计算*/
/*把输出参数保存在临时数组的宏*/
#define _IFC_ADD_ARG0(ary, p)
#define _IFC_ADD_ARG1(ary, d1, t1, a1, s1)						 __ifc_arg_out(ary, d1, (unsigned int)a1, s1, 0)
#define _IFC_ADD_ARG2(ary, d2, t2, a2, s2, d1, t1, a1, s1, ...)  __ifc_arg_out(ary, d2, (unsigned int)a2 ,s2, (unsigned int)a1); _IFC_ADD_ARG1(ary, d1, t1, a1, s1)
#define _IFC_ADD_ARG3(ary, d3, t3, a3, s3, d2, t2, a2, s2, ...)  __ifc_arg_out(ary, d3, (unsigned int)a3 ,s3, (unsigned int)a2); _IFC_ADD_ARG2(ary, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_ADD_ARG4(ary, d4, t4, a4, s4, d3, t3, a3, s3, ...)  __ifc_arg_out(ary, d4, (unsigned int)a4 ,s4, (unsigned int)a3); _IFC_ADD_ARG3(ary, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_ADD_ARG5(ary, d5, t5, a5, s5, d4, t4, a4, s4, ...)  __ifc_arg_out(ary, d5, (unsigned int)a5 ,s5, (unsigned int)a4); _IFC_ADD_ARG4(ary, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_ADD_ARG6(ary, d6, t6, a6, s6, d5, t5, a5, s5, ...)  __ifc_arg_out(ary, d6, (unsigned int)a6 ,s6, (unsigned int)a5); _IFC_ADD_ARG5(ary, d5, t5, a5, s5, __VA_ARGS__)

/*调用核:把输入参数压入邮箱用户数据缓存的宏*/ /*往邮箱buf推入数据,同时把返回参数地址暂存*/
/*按arm c语言调用规范，从左往右压参数*/
#define _IFC_PUSHDATA0(d, av, p)
#define _IFC_PUSHDATA1(d, av, d1, t1, a1, s1)					  __ifc_push_arg(d, av, d1, (unsigned int)a1, s1, 0)
#define _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, d1, t1, a1, s1)	  __ifc_push_arg(d, av, d2, (unsigned int)a2 ,s2, (unsigned int)a1); _IFC_PUSHDATA1(d, av, d1, t1, a1, s1)
#define _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, d2, t2, a2, s2,...) __ifc_push_arg(d, av, d3, (unsigned int)a3 ,s3, (unsigned int)a2); _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, d3, t3, a3, s3,...) __ifc_push_arg(d, av, d4, (unsigned int)a4 ,s4, (unsigned int)a3); _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, d4, t4, a4, s4,...) __ifc_push_arg(d, av, d5, (unsigned int)a5 ,s5, (unsigned int)a4); _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_PUSHDATA6(d, av, d6, t6, a6, s6, d5, t5, a5, s5,...) __ifc_push_arg(d, av, d6, (unsigned int)a6 ,s6, (unsigned int)a5); _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, __VA_ARGS__)

/*执行核:把双向参数从输入缓存拷贝到输出缓存的宏*/
#define _IFC_PCOPY0(in, out, av, ao, p)
#define _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1)					  __ifc_copy_arg(in, out, d1, s1, av, ao)
#define _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, d1, t1, a1, s1)	  __ifc_copy_arg(in, out, d2, s2, av, ao); _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1)
#define _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, d2, t2, a2, s2, ...) __ifc_copy_arg(in, out, d3, s3, av, ao); _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, d3, t3, a3, s3, ...) __ifc_copy_arg(in, out, d4, s4, av, ao); _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, d4, t4, a4, s4, ...) __ifc_copy_arg(in, out, d5, s5, av, ao); _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_PCOPY6(in, out, av, ao, d6, t6, a6, s6, d5, t5, a5, s5, ...) __ifc_copy_arg(in, out, d6, s6, av, ao); _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, __VA_ARGS__)

/*执行核:计算函数输出参数总大小的宏*/
#define _IFC_OUTSIZE0(av, p)								   0
#define _IFC_OUTSIZE1(av, d1, t1, a1, s1)					   __ifc_out_size(d1, s1, av)
#define _IFC_OUTSIZE2(av, d2, t2, a2, s2, d1, t1, a1, s1)	   __ifc_out_size(d2, s2, av) + _IFC_OUTSIZE1(av, d1, t1, a1, s1)
#define _IFC_OUTSIZE3(av, d3, t3, a3, s3, d2, t2, a2, s2,...)  __ifc_out_size(d3, s3, av) + _IFC_OUTSIZE2(av, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_OUTSIZE4(av, d4, t4, a4, s4, d3, t3, a3, s3,...)  __ifc_out_size(d4, s4, av) + _IFC_OUTSIZE3(av, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_OUTSIZE5(av, d5, t5, a5, s5, d4, t4, a4, s4,...)  __ifc_out_size(d5, s5, av) + _IFC_OUTSIZE4(av, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_OUTSIZE6(av, d6, t6, a6, s6, d5, t5, a5, s5,...)  __ifc_out_size(d6, s6, av) + _IFC_OUTSIZE5(av, d5, t5, a5, s5, __VA_ARGS__)

#endif

/*执行核:生成远程执行函数参数指针地址的宏*/
#define _IFC_PARAM0(in, out, av, p)
#define _IFC_PARAM1(in, out, av, d1, t1, a1, s1)					  (t1)__ifc_gen_arg(in, out, d1, s1, av)
#define _IFC_PARAM2(in, out, av, d2, t2, a2, s2, d1, t1, a1, s1)	  (t2)__ifc_gen_arg(in, out, d2, s2, av), _IFC_PARAM1(in, out, av, d1, t1, a1, s1)
#define _IFC_PARAM3(in, out, av, d3, t3, a3, s3, d2, t2, a2, s2, ...) (t3)__ifc_gen_arg(in, out, d3, s3, av), _IFC_PARAM2(in, out, av, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_PARAM4(in, out, av, d4, t4, a4, s4, d3, t3, a3, s3, ...) (t4)__ifc_gen_arg(in, out, d4, s4, av), _IFC_PARAM3(in, out, av, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_PARAM5(in, out, av, d5, t5, a5, s5, d4, t4, a4, s4, ...) (t5)__ifc_gen_arg(in, out, d5, s5, av), _IFC_PARAM4(in, out, av, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_PARAM6(in, out, av, d6, t6, a6, s6, d5, t5, a5, s5, ...) (t6)__ifc_gen_arg(in, out, d6, s6, av), _IFC_PARAM5(in, out, av, d5, t5, a5, s5, __VA_ARGS__)


/*调用核:生成函数声明中的参数的宏*/
#define _IFC_DECL0(p)		/*void*/
#define _IFC_DECL1(d1, t1, a1, s1)		 t1 a1,
#define _IFC_DECL2(d2, t2, a2, s2, ...)  t2 a2, _IFC_DECL1(__VA_ARGS__)
#define _IFC_DECL3(d3, t3, a3, s3, ...)  t3 a3, _IFC_DECL2(__VA_ARGS__)
#define _IFC_DECL4(d4, t4, a4, s4, ...)  t4 a4, _IFC_DECL3(__VA_ARGS__)
#define _IFC_DECL5(d5, t5, a5, s5, ...)  t5 a5, _IFC_DECL4(__VA_ARGS__)
#define _IFC_DECL6(d6, t6, a6, s6, ...)  t6 a6, _IFC_DECL5(__VA_ARGS__)

/*调用核:计算输入参数总大小的宏*/
#define _IFC_INSIZE0(p) 								  0
#define _IFC_INSIZE1(d1, t1, a1, s1)					  __ifc_in_size(d1, s1, 0)
#define _IFC_INSIZE2(d2, t2, a2, s2, d1, t1, a1, s1)	 _IFC_INSIZE1(d1, t1, a1, s1) + __ifc_in_size(d2, s2, (unsigned int)a1)
#define _IFC_INSIZE3(d3, t3, a3, s3, d2, t2, a2, s2,...) _IFC_INSIZE2(d2, t2, a2, s2, __VA_ARGS__) + __ifc_in_size(d3, s3, (unsigned int)a2)
#define _IFC_INSIZE4(d4, t4, a4, s4, d3, t3, a3, s3,...) _IFC_INSIZE3(d3, t3, a3, s3, __VA_ARGS__) + __ifc_in_size(d4, s4, (unsigned int)a3)
#define _IFC_INSIZE5(d5, t5, a5, s5, d4, t4, a4, s4,...) _IFC_INSIZE4(d4, t4, a4, s4, __VA_ARGS__) + __ifc_in_size(d5, s5, (unsigned int)a4)
#define _IFC_INSIZE6(d6, t6, a6, s6, d5, t5, a5, s5,...) _IFC_INSIZE5(d5, t5, a5, s5, __VA_ARGS__) + __ifc_in_size(d6, s6, (unsigned int)a5)

/*调用核:保存并检查参数*/
#define _IFC_DBGPARAM0(p, a)
#define _IFC_DBGPARAM1(ph, d1, t1, a1, s1)					   _ifc_dbg_arg(ph, d1, s1, 0)
#define _IFC_DBGPARAM2(ph, d2, t2, a2, s2, d1, t1, a1, s1)	   _IFC_DBGPARAM1(ph, d1, t1, a1, s1) ; _ifc_dbg_arg(ph, d2, s2, d1)
#define _IFC_DBGPARAM3(ph, d3, t3, a3, s3, d2, t2, a2, s2,...) _IFC_DBGPARAM2(ph, d2, t2, a2, s2, __VA_ARGS__); _ifc_dbg_arg(ph, d3, s3, d2)
#define _IFC_DBGPARAM4(ph, d4, t4, a4, s4, d3, t3, a3, s3,...) _IFC_DBGPARAM3(ph, d3, t3, a3, s3, __VA_ARGS__); _ifc_dbg_arg(ph, d4, s4, d3)
#define _IFC_DBGPARAM5(ph, d5, t5, a5, s5, d4, t4, a4, s4,...) _IFC_DBGPARAM4(ph, d4, t4, a4, s4, __VA_ARGS__); _ifc_dbg_arg(ph, d5, s5, d4)
#define _IFC_DBGPARAM6(ph, d6, t6, a6, s6, d5, t5, a5, s5,...) _IFC_DBGPARAM5(ph, d5, t5, a5, s5, __VA_ARGS__); _ifc_dbg_arg(ph, d6, s6, d5)

/*执行核:检查参数*/
#define _IFC_CHKPARAM0(p, a)
#define _IFC_CHKPARAM1(ph, d1, t1, a1, s1)					   _ifc_chk_arg(ph, d1, s1)
#define _IFC_CHKPARAM2(ph, d2, t2, a2, s2, d1, t1, a1, s1)	   _ifc_chk_arg(ph, d2, s2); _IFC_CHKPARAM1(ph, d1, t1, a1, s1)
#define _IFC_CHKPARAM3(ph, d3, t3, a3, s3, d2, t2, a2, s2,...) _ifc_chk_arg(ph, d3, s3); _IFC_CHKPARAM2(ph, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_CHKPARAM4(ph, d4, t4, a4, s4, d3, t3, a3, s3,...) _ifc_chk_arg(ph, d4, s4); _IFC_CHKPARAM3(ph, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_CHKPARAM5(ph, d5, t5, a5, s5, d4, t4, a4, s4,...) _ifc_chk_arg(ph, d5, s5); _IFC_CHKPARAM4(ph, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_CHKPARAM6(ph, d6, t6, a6, s6, d5, t5, a5, s5,...) _ifc_chk_arg(ph, d6, s6); _IFC_CHKPARAM5(ph, d5, t5, a5, s5, __VA_ARGS__)

/*调用核:生成远程函数调用者的宏*/
#define _IFC_GEN_CALLx(x, id, name,  ...)																							\
int name(_IFC_DECL##x(__VA_ARGS__) unsigned int timeout ) 																		\
{																																	\
	struct ifc_mb ifc_b;																											\
	struct ifc_arg *argo = ifc_b.argo;																								\
	unsigned int in_buf;																											\
	unsigned int *argv = ifc_b.head.argv;	/*此方法需要考虑编译器执行顺序差异*/													\
	unsigned int in_size = (_IFC_INSIZE##x(__VA_ARGS__));																			\
	argo=argo; argv=argv;																											\
	if (x > IFC_MAX_ARG) return 0;																									\
	if (mailbox_ifc_init_buf(&ifc_b, id, IFC_LAUNCH, in_size, timeout)) return 0;													\
	in_buf = ifc_b.head.data;																										\
	_IFC_DBGPARAM##x(&ifc_b.head, __VA_ARGS__);  /*参数调试入口*/																	\
	_IFC_PUSHDATA##x(&in_buf, &argv, __VA_ARGS__);	/*往邮箱buf推入数据,同时把返回参数地址暂存*/									 \
	if (timeout) {				   /*需要等待返回*/ 																				\
		_IFC_ADD_ARG##x(&argo, __VA_ARGS__); /* 把返回值和出参的地址加入本通道的回收邮件消息链表，用于获取返回消息中的出参值*/		 \
		return mailbox_ifc_send_wait(&ifc_b, timeout); /*等待回收调用返回消息完成，*/												\
	}																																\
	else																															\
		return mailbox_ifc_send_no_wait(&ifc_b); /*不需要等待返回*/ 																 \
}

/*执行核:生成远程调用执行函数名*/
#define IFC_GEN_EXEC_NAME(name) ife_##name

/*执行核:生成远程调用执行函数体*/
#define __IFC_GEN_EXECx(x, name, ...)																								 \
int IFC_GEN_EXEC_NAME(name)(struct ifc_head * ifc_h)																				 \
{																																	 \
	struct ifc_mb ifc_b;																											 \
	unsigned int in_b, out_b;																										 \
	unsigned int *argv = ifc_h->argv;	/*需要考虑编译器执行顺序差异*/																 \
	unsigned int *argo;																											 \
	unsigned int out_size = (_IFC_OUTSIZE##x(&argv,__VA_ARGS__));																	 \
	if (mailbox_ifc_init_buf(&ifc_b, ifc_h->rcode, IFC_RESPONSE, out_size , 0)) return MAILBOX_ERRO;								 \
	in_b = ifc_h->data; out_b = ifc_b.head.data;  argv = ifc_h->argv;																 \
	_IFC_CHKPARAM##x(ifc_h, __VA_ARGS__);  /*检查调用方的参数配置是否和执行方一致，并且检查参数是否符合规范*/						 \
	ifc_b.head.retval = (unsigned int)name(_IFC_PARAM##x(&in_b, &out_b, &argv, __VA_ARGS__));										 \
	if (ifc_h->needret) {				 /*需要等待返回*/																			 \
		in_b = ifc_h->data; out_b = ifc_b.head.data; ifc_b.head.stamp = ifc_h->stamp; /*返回时间戳用于校验*/						  \
		argv = ifc_h->argv;  /*输入参数*/ argo = ifc_b.head.argv; /*输出参数*/														 \
		_IFC_PCOPY##x(&in_b, &out_b, &argv, &argo, __VA_ARGS__);  /*把双参从inbuf拷贝到outbuf*/ 									 \
		return mailbox_ifc_send_no_wait(&ifc_b);	/*消息总大小写回邮件头，解锁并且发送数据*/										  \
	}																																 \
	else																															 \
		return mailbox_ifc_discard_buf(&ifc_b); /*取消邮箱buff，解锁并丢弃此次发送*/												  \
}

extern int mailbox_ifc_init_buf(
	struct ifc_mb *ifc_b,
	unsigned int mailcode,
	unsigned int direct,
	unsigned int inlen,
	unsigned int timeout);

extern int mailbox_ifc_send_no_wait(struct ifc_mb *ifc_b);

extern int mailbox_ifc_wait_resp(struct ifc_mb *ifc_b);

extern int mailbox_ifc_discard_buf(struct ifc_mb *ifc_b);

extern int mailbox_ifc_send_wait(struct ifc_mb *ifc_b, unsigned int timeout);

extern int mailbox_ifc_register_exec(
	unsigned int mailcode,
	int (*ife_cb)(struct ifc_head * ifc_h)
);

extern void __ifc_arg_out(struct ifc_arg ** ary, unsigned int db, unsigned long ab, unsigned int sb, unsigned int af);

extern void __ifc_push_arg(unsigned long * in, unsigned int ** av, unsigned int db, unsigned long ab, unsigned int sb, unsigned int af);

extern int __ifc_in_size(unsigned int db, unsigned int sb, unsigned int af);

extern void __ifc_dbg_arg(struct ifc_head *head, unsigned int db, unsigned int sb, unsigned int df);

extern int __ifc_out_size(unsigned int db, unsigned int sb, unsigned int **pp_af);

extern long __ifc_gen_arg(unsigned long *in, unsigned long *out, unsigned int db, unsigned int sb, unsigned int **pp_af);

extern void __ifc_copy_arg(unsigned long *in, unsigned long *out, unsigned int db, unsigned int sb, unsigned int **av , unsigned int **ao);

extern void __ifc_chk_arg(struct ifc_head *head, unsigned int db, unsigned int sb);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*end of __DRV_MAILBOX_IFC_H__*/
