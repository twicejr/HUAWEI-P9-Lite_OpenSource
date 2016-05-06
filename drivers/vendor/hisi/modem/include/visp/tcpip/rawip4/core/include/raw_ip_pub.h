/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              raw_ip_pub.h
*
*  Project Code: VISP1.5
*   Module Name: RawIP
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: 本文件是rawip的数据结构描述 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _RAW_IP_PUB_H_
#define _RAW_IP_PUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/rawip4/include/rawip_api.h"


typedef struct  tagRIP4_MOD_INFO
{
    ULONG ulModID; /* Module id */

    ULONG ulDoubleOSPFEnalbe;          /*2005-9-23 x44006 添加双ospf特性是否使能标志 */

} RIP4_MOD_INFO_S;

#define IP4_RIP_EXT_COMIF_CNT   8

#define RIPSNDQ     8192 /*默认的RawIP Socket发送缓冲区大小为8K*/
#define RIPRCVQ     8192 /*默认的RawIP Socket接收缓冲区大小为8K*/


#ifdef __cplusplus
}
#endif

#endif  /* _RAW_IP_PUB_H_ */

