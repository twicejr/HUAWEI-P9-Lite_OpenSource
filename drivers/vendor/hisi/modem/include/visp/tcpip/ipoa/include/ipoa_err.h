/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_err.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-30
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-30   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_ERR_H_
#define _IPOA_ERR_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


typedef enum tagATM_ERR_CODE
{
    ATM_OK = 0,                 /* = VOS_OK  */
    ATM_ERR,                    /* = VOS_ERR */
    ATM_ERR_MEM_ALLOC_FAIL,     /* 内存分配失败 */
    ATM_ERR_MBUF_ALLOC_FAIL,    /* MBUF内存分配失败 */
    ATM_ERR_BAD_PARAM,          /*  */
    ATM_ERR_SERVICE_UNSUPPORT = 5,
    ATM_ERR_OAM_UNSUPPORT,
    ATM_ERR_MAP_NOT_FOUND,      /*  */
    ATM_ERR_NO_INARP_MAP,       /* PVC没有InARP MAP */
    ATM_ERR_CREATE_TIMER_FAIL,  /* PVC没有InARP MAP */
    ATM_ERR_CREATE_VA_FAIL,     /* 创建VA失败 */
    ATM_ERR_CANNOT_GET_INTF,
    ATM_ERR_PHY_CREATE_PVC_FAIL,        /* 底层芯片创建PVC失败 */
    ATM_ERR_BAD_PACKET_TYPE,
    ATM_ERR_OAM_NOT_ENABLED,
    ATM_ERR_BAD_COMMAND,
    ATM_ERR_RPC_SYNC_SEND_FAIL,  /* RPC同步取失败 */
    ATM_ERR_CREATE_INTF_FAIL,
    ATM_ERR_MBUF_DATA_NULL,             /* MBUF无数据区 */
    ATM_ERR_PACKET_LEN_ERR,             /* 报文长度错 */
    ATM_ERR_INARP_INTERVAL_ZERO,        /* INARP定时器长为0 */
    ATM_ERR_INARP_PAC_BAD_FIELD,        /* 非法的IANRP报文，字段错 */
    ATM_ERR_INARP_PAC_NO_SOURCE_IP,     /* 非法的IANRP报文，没有源IP */
    ATM_ERR_MBUF_PREPEND_FAIL,          /* 扩展MBUF错 */
    ATM_ERR_MBUF_MAKECONT_FAIL,         /* MBUF连续化错 */
    ATM_ERR_INARP_PAC_SEND_FAIL,

    ATM_ERR_LOW_LAYER_SEND_FAIL,        /* 非法的INARP包 */
    
    ATM_ERR_VC_SEARCH_NAME_ERR,             /* VC查找返回值 */
    ATM_ERR_VC_SEARCH_VPIVCI_ERR,
    ATM_ERR_VC_SEARCH_NAME_OK_VPIVCI_ERR,
    ATM_ERR_VC_SEARCH_NAME_ERR_VPIVCI_OK,
    ATM_ERR_VC_SEARCH_NAME_ERR_VPIVCI_ERR,
    ATM_ERR_VC_SEARCH_NAME_OK_VPIVCI_OK,

    ATM_ERR_PVC_NO_PROTOCOL,
	ATM_ERR_PAC_TYPE_UNSUPPORTED,
	ATM_ERR_INARP_NOT_SNAP,         /* 非SNAP封装发送INARP报文 */
    ATM_ERR_VLINK_ALREADY_EXIST,
    ATM_ERR_INVALID_MAP_TYPE,
    ATM_ERR_VLINK_NOT_EXIST,
    ATM_ERR_EXCEED_VC_MAX_NUM_OF_CB,        /* sunshengtao 2001/04/12 */
    ATM_ERR_EXCEED_VC_MAX_NUM_OF_SUBIF,     /* sunshengtao 2001/04/12 */
	ATM_ERR_EXCEED_MAX_MAP_LIMIT_OF_PVC,    /* sunshengtao 2001/04/12 */
	ATM_ERR_EXCEED_MAX_MAP_LIMIT_OF_SUBIF,  /* sunshengtao 2001/04/12 */

    ATM_ERR_SGSN_DEBUG_DEBUGSET,           /* 配置开关非法 */
    ATM_ERR_SGSN_DEBUG_DEBUGTYPE,          /* debug类型非法 */
    ATM_ERR_SGSN_DEBUG_NULL_BUFFER,        /* 输入存储消息指针非法*/
    ATM_ERR_SGSN_DEBUG_MAX_BUFFER_LEN,     /* 输入存储消息最发长度非法 */
    ATM_ERR_SGSN_DEBUG_IFNET_NOT_EXIST,    /* ifnet指针不存在 */
    ATM_ERR_SGSN_DEBUG_INTF_NOT_EXIST,     /* ATM 主接口指针不存在*/
    ATM_ERR_SGSN_DEBUG_INTF_IS_NOT_ATM,    /* 此接口不是ATM口 */
    ATM_ERR_SGSN_DEBUG_BUFFER_NOT_ENOUGH,  /* 消息过长，缓冲区长度不够*/
    ATM_ERR_SGSN_DEBUG_PVC_INVALIDE,       /* PVC名或者VPI/VCI非法 */
    ATM_ERR_SGSN_DEBUG_NO_PVC,             /* 没有与输入相匹配的PVC */
    ATM_ERR_SGSN_DEBUG_PVCNAME_VPIVCI,     /* 同时存在pvc名和vpi/vci*/
    ATM_ERR_SGSN_DEBUG_CANT_OFF_PVC,       /* 接口级开关已经打开,不允许关闭pvc级开关 */
    ATM_ERR_SGSN_DEBUG_CANT_OFF_INTER,     /* 全局开关已经打开,不允许关闭置接口级开关 */

	ATM_ERR_EXCEED_MAX_MAP_LIMIT_OF_PORT,   /* suishaoshuai 2001/06/16 */
	
    ATM_ERR_ONE_PVC_ONLY_ON_P2P,
    ATM_ERR_PVC_STATE_DOWN,     /* PVC发送报文失败 */
    ATM_ERR_VC_SEND_FAIL,       	/* PVC发送报文失败 */
    ATM_ERR_INTF_SEND_FAIL,     	/* INTF发送报文失败 */
    ATM_ERR_NO_LOCAL_IPADDR,    	/* 本端没有地址 */
    ATM_ERR_IN_PKT_PVC_NOT_EXIST,	/* PVC上收到报文，但PVC不存在 */
    ATM_ERR_IN_PKT_PVC_DOWN,		/* PVC上收到报文，但PVC状态DOWN */
    ATM_ERR_OUT_PKT_NO_MAP,			/* 接口上发送报文，没有指定VLINK，但MAP不存在 */
    ATM_ERR_OUT_PKT_VLINK_NO_MAP,	/* 接口上发送报文，但通过VLINK找不到MAP */
    
    ATM_ERR_OAMSTATE_PVC_NOT_FOUND, /* 底层控制OAM PVC，PVC不存在 */
    ATM_ERR_EXCEED_VC_MAX_NUM_OF_GROUP,
    
    ATM_ERR_PARA_NOT_EXIST,  /* 参数不存在 */
    ATM_ERR_LAST_ONE_NO_COMMA,
    /*#if( VRP_MODULE_ATM_CELL_TRANSPORT == VRP_YES )*/
    ATM_ERR_L2VPN_LEN_ERR,
    ATM_ERR_L2VPN_IN_PVP_NOT_EXIST,
    ATM_ERR_L2VPN_OUT_PVP_NOT_EXIST,
    ATM_ERR_L2VPN_PVC_NOT_EXIST,
    ATM_ERR_L2VPN_L2VPN_NOT_START,
    ATM_ERR_L2VPN_NULL_PTR,
    ATM_ERR_L2VPN_QOS_TRANSMIT_FAIL,
    /*#endif*/
    ATM_ERR_NO_ENOUGH_BANDWIDTH,
    ATM_ERR_PHY_SET_SERVICE_FAIL,
    ATM_ERR_ILLOGICAL_SERVICE_PARAMETER,
    ATM_ERR_VPI_0_VCI_0,

    ATM_ERR_VCI_3_VCI_4,

    ATM_ERR_SERVICE_PARA_NOT_REASONABLE

}ATM_ERR_CODE_EN;





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_ERR_H_ */


