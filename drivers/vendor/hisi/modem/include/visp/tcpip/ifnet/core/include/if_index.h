/************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                        IF_INDEX.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/02/28  
 *        Author: yuanjie
 *   Description: Ifnet索引头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/02/28      yuanjie         Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2006-05-13      l48923          Delete useless code
 *
 ************************************************************************/

/*
 * 请将这里的模块宏换成该头文件所属模块的模块宏。
 * 例如，对于链路层协议模块PPP的头文件ppp_var.h，应该改为：
 *
 *    #if( VRP_MODULE_LINK_PPP == VRP_YES )
 *
 * 引用该宏的目的是为了通过手工配置在编译时裁减VRP软件，请每个文件保留。
 * 所有的这些模块宏都由VRP3.0的配置管理员管理，在头文件vrpcfg.h中定义。
 */

#ifndef    _TCPIP_IF_INDEX_H_
#define    _TCPIP_IF_INDEX_H_
/*
 * 该宏的定义方式为："_" + "全部大写的文件名" + "_" + "H" + "_"
 * 例如，对于链路层协议模块PPP的头文件ppp_var.h，应该定义为：
 *
 *    #ifndef    _PPP_VAR_H_
 *    #define    _PPP_VAR_H_
 *
 * 定义该宏的目的在去除重复包含一个头文件的可能性
 */

#ifdef __cplusplus
extern "C"{
#endif
/*
 * 为了使VRP3.0适应C++编译器所做的处理，请每个文件保留。
 */


/************************************************************************
 * 请在这里填写该头文件的具体内容                                       *
 * ......                                                               *
 * ......                                                               *
 * ......                                                               *
 ************************************************************************/
/*将这段范围的索引值分配给多播模块专用，
由于这些数字中的前6位表示槽号的位都是1，
而槽号是不会有这么大数字的，因此一般接口
都不会使用这段索引值。  pengjimei  2002/06/05*/
#define IFINDEX_MCAST_RESERVED_BEGIN     0xFC000000
#define IFINDEX_MCAST_RESERVED_END       0xFC00000F

IFNET_S *IF_GetIfByIndex(ULONG ulIfIndex);

ULONG IF_GetFirstIfIndex(ULONG * pIndex);
ULONG IF_GetNextIfIndex( ULONG ulIndex, ULONG * pNextIndex ) ;

#ifdef __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _TEMPLETE_H_ */



