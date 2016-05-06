/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_def.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES模块的宏定义和枚举类型定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_DEF_H_
#define  _POES_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif
/* 以下为POES模块的宏定义 */

#define POES_MAC_BCAST_ADDR "\xff\xff\xff\xff\xff\xff"  /* ethernet broadcast address */

#define POES_COM_NUM 1                 /* Poes相关组件个数 */ 


#define POES_SES_NODE_ARRAY_INCR 100    /* Session节点数组每次递增分配的大小 */

#define POES_SESID_NULL 0xFFFF          /* 非法session id */

#define POES_MAX_SES_LIMIT 65534            /* Session数限制的配置上限 */
#define POES_DEFAULT_ALL_SES_LIMIT 1000     /* 全局Session数限制的缺省值 */
#define POES_DEFAULT_OURMAC_SES_LIMIT 1000  /* 本端MAC Session数限制缺省值 */
#define POES_DEFAULT_HISMAC_SES_LIMIT 100   /* 对端MAC Session数限制缺省值 */

#define POES_PKT_IN 0   /* 入报文标志 */
#define POES_PKT_OUT 1  /* 出报文标志 */
#define POES_SW_OFF 0   /* 开关关闭 */
#define POES_SW_ON 1    /* 开关打开 */

#define POES_PRINT_PACKET_LEN 128   /* 数据报文打印长度 */

#define POES_TIME 1000  /* POES定时器时长,毫秒 */
#define POES_CLEAN_SESSION_TIME 15  /*PADI状态Session清除时间15秒*/
#define POES_GET_QUE_PKT_NUM 40  /* 1次从POES报文队列取报文个数 */

/*POES Version & Type, 目前为0x11*/
#define POES_VERSION_1_TYPE_1  0x11

/* POES 的各种codes */
#define POES_CODE_SESS 0x00 /* PPPoE session */
#define POES_CODE_PADI 0x09 /* PPPoE Active Discovery Initiation */
#define POES_CODE_PADO 0x07 /* PPPoE Active Discovery Offer */
#define POES_CODE_PADR 0x19 /* PPPoE Active Discovery Request */
#define POES_CODE_PADS 0x65 /* PPPoE Active Discovery Session-confirmation */
#define POES_CODE_PADT 0xa7 /* PPPoE Active Discovery Terminate */

/* POES 的各种tag type */
#define POES_TAG_END_OF_LIST           0x0000
#define POES_TAG_SERVICE_NAME          0x0101
#define POES_TAG_AC_NAME               0x0102
#define POES_TAG_HOST_UNIQ             0x0103
#define POES_TAG_AC_COOKIE             0x0104
#define POES_TAG_VENDOR_SPECIFIC       0x0105
#define POES_TAG_RELAY_SESSION_ID      0x0110
#define POES_TAG_SERVICE_NAME_ERROR    0x0201
#define POES_TAG_AC_SYSTEM_ERROR       0x0202
#define POES_TAG_GENERIC_ERROR         0x0203

/* POES 相关长度宏*/
#define POES_MIN_ETHERNET_PAYLOAD 6     /*PPPOE 最小长度*/
#define POES_MAX_ETHERNET_PAYLOAD 1500 
#define POES_ETHER_HEADER_LEN     14   /*以太头的长度*/
#define POES_TAG_AND_LENGTH       4    /*TAG域的最小长度*/

#define POES_HEADER_LEN 20  /*PPPoE 头信息，包括以太网帧头*/
#define POES_PPP_HEAD 2     /*PPP的ACFC字段两字节*/

/*ETH首部 + PPPOE首部的最小长度20*/
#define POES_MIN_ETHERNET_LEN \
    (POES_ETHER_HEADER_LEN + POES_MIN_ETHERNET_PAYLOAD)

/*ETH首部 + PPPOE首部的最大长度14 + 1500 = 1514*/
#define POES_MAX_ETHERNET_LEN \
    (POES_ETHER_HEADER_LEN + POES_MAX_ETHERNET_PAYLOAD)

/*TAG域的最大净荷长度1500- 6 = 1494*/
#define POES_MAX_TAG_PAYLOAD_LEN \
    (POES_MAX_ETHERNET_PAYLOAD - POES_MIN_ETHERNET_PAYLOAD)

/*TAG域的最大长度1500- 6 - 4 = 1490*/
#define POES_MAX_TAG_LENGTH \
    (POES_MAX_ETHERNET_PAYLOAD - POES_MIN_ETHERNET_PAYLOAD - POES_TAG_AND_LENGTH)




/*PPPoE Server所使用的一些宏操作*/
/* 从字符指针cp获得一个char给c，cp指针加1 */
#define POES_GET_CHAR(c, cp) { \
    (c) = *( (UCHAR *)(cp) ); \
    (cp) += 1 ; \
}

/* 将字符c写到字符指针cp处，cp指针加1 */
#define POES_PUT_CHAR(c, cp) { \
    *( (UCHAR *)(cp) ) = (c) ; \
    (cp) += 1 ; \
}

/* 从字符指针cp获得一个ushort值给s，cp指针加2 */
#define POES_GET_SHORT(s, cp) { \
    VOS_CopyVar((s), *((USHORT *)(cp))); \
    (cp) += 2 ; \
}

/* 将ushort变量s的值写到字符指针cp处，cp指针加2 */
#define POES_PUT_SHORT(s, cp) { \
    VOS_CopyVar(*((USHORT*)(cp)), (s)) ; \
    (cp) += 2 ; \
}

/* 从字符指针cp获得一个ulong值给s，cp指针加4 */
#define POES_GET_LONG(l, cp) { \
    VOS_CopyVar((l) , *((ULONG *)(cp))); \
    (cp) += 4 ; \
}

/* 将ulong变量l的值写到字符指针cp处，cp指针加4 */
#define POES_PUT_LONG(l, cp) { \
    VOS_CopyVar(*((ULONG*)(cp)),(l)) ; \
    (cp) += 4 ; \
}

/* 以下为POES模块的枚举类型定义 */
/* Session状态 */
enum enumPoesSesState
{
    POES_RCVD_PADI = 0, /* PADI状态 */
    POES_PPP_SESSION    /* 会话状态 */
};




#ifdef __cplusplus
}
#endif

#endif 

