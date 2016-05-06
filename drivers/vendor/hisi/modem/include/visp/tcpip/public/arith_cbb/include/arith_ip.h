/*************************************************************************
 *
 *              Copyright 2007, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              arith_ip.h
 *
 *  Project Code: VISP1.6
 *   Module Name: CBB
 *  Date Created: 2007-07-30
 *        Author: mafeng 59090
 *   Description: 提供arith cbb模块主要头文件的包含
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      mafeng 59090    Create
 *
 ************************************************************************/
#ifndef _ARITH_IP_H_
#define _ARITH_IP_H_

#ifdef __cplusplus
extern "C" {
#endif

struct tagMBuf;

/* Modified by h00121208 在升级dopraV2时为了兼容两个版本, 由于两个
   版本中VOS_UINT32定义不一致, 因此此处不能自定义类型, 需要与dopra头文件一起使用,
   如果需要单独用此文件请先定义VOS_UINT32类型 */
/*
#ifndef VOS_UINT32
#define VOS_UINT32     unsigned long
#endif
*/
#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

#define MIN_IP_ADDR_CHAR_NUM   7    /* 1.1.1.1 is the lest char num = 7 */
#define MAX_IP_ADDR_CHAR_NUM   15    /*255.255.255.255 is the largest num = 15 */

#ifndef INADDR_ANY
#define INADDR_ANY  (VOS_UINT32)0x00000000L
#endif

#ifndef INADDR_BROADCAST
#define INADDR_BROADCAST    (VOS_UINT32)0xffffffffL /* must be masked */
#endif

#ifndef VRP_IN_CLASSA
#define VRP_IN_CLASSA(i)        (0 == ((long)(i) & 0x80000000L))
#endif

#ifndef VRP_IN_CLASSA_HOST
#define VRP_IN_CLASSA_HOST      0x00ffffffL
#endif

#ifndef VRP_IN_CLASSB
#define VRP_IN_CLASSB(i)        (0x80000000L == ((long)(i) & 0xc0000000L))
#endif

#ifndef VRP_IN_CLASSB_HOST
#define VRP_IN_CLASSB_HOST      0x0000ffffL
#endif

#ifndef VRP_IN_CLASSC
#define VRP_IN_CLASSC(i)        (0xc0000000L == ((long)(i) & 0xe0000000L))
#endif

#ifndef VRP_IN_CLASSC_HOST
#define VRP_IN_CLASSC_HOST      0x000000ffL
#endif

#ifndef ADDCARRY
#define ADDCARRY(x)  (x > 65535L ? x -= 65535L : x)
#endif

#ifndef REDUCE
#define REDUCE \
{ \
    unLUtil.l = lSum;\
    lSum = unLUtil.s[0] + unLUtil.s[1]; \
    ADDCARRY(lSum); \
}
#endif

#ifndef InetAddr
ULONG vrp_InetAddr(CHAR *);
#define InetAddr(a)   vrp_InetAddr(a)
#endif

/* Added by y00176567, at 2011-05-25. 修改原因: 消除VC三级告警 */
extern ULONG VOS_strlen(const CHAR *);
extern VOS_INT32  VOS_atol( const VOS_CHAR * pcStr, VOS_INT32 * pnVal );


/*******************************************************************************
*    Func Name: IP_IsInvalidAddr
*  Description: 作为地址合法性判断的公共函数
*               非法地址有: 全网广播、0.X.X.X 、D类E类地址
*        Input: ULONG ulIpAddr: 地址(主机序)
*       Output: 
*       Return: 0: 合法   1: 非法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
ULONG IP_IsInvalidAddr(ULONG ulIpAddr);
/*******************************************************************************
*    Func Name: InetAddr
*  Description:将点分十进制形式的地址转换为网络字节序的二进制形式 
*        Input: CHAR *pIpChar:点分十进制地址字符串
*       Output: 
*       Return: 成功:转换之后的地址 失败:返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-11-10   wangtao(60012929)       Create
*
*******************************************************************************/
ULONG InetAddr(CHAR *pIpChar);
/*******************************************************************************
*    Func Name: IP_MaskBitLen
*  Description: 获取掩码长度
*        Input: ULONG ulMask: 掩码(网络序)
*       Output: 
*       Return: 0-32 掩码长度,255,掩码不连续
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
USHORT IP_MaskBitLen(ULONG ulMask);
/*******************************************************************************
*    Func Name: Ip_Fast_Cksum
*  Description: Checksum routine for Internet Protocol family headers (Portable Version).
*               This routine is very heavily used in the network
*               code and should be modified for each CPU to be as fast as possible.    
*        Input: USHORT * pusWord: IP首部指针
*       Output: 
*       Return: IP首部校验和
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
USHORT Ip_Fast_Cksum(USHORT * pusWord);
/*******************************************************************************
*    Func Name: IN_Cksum
*  Description: Checksum routine for Internet Protocol family headers    
*        Input: MBUF_S *pstMBuf: IP报文
*               LONG lLen:       IP首部长度
*       Output: 
*       Return: IP首部校验和
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
USHORT IN_Cksum(MBUF_S* pstMbuf, LONG lLen);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _ARITH_IP_H_ */

