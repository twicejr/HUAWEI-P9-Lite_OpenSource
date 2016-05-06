/* bastet_comm.c
 *
 * Bastet Hisilicon modem communication mudule.
 *
 * Copyright (C) 2014 Huawei Device Co.,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "v_typdef.h"
#include "VosPidDef.h"
#include "PsCommonDef.h"
#include "BastetInit.h"
#include "RnicCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID		PS_FILE_ID_BST_COMM_C
#define BST_MAX_WRITE_PAYLOAD				(2048)

struct bst_modem_rab_id {
	uint16_t modem_id;
	uint16_t rab_id;
};

extern char cur_netdev_name[IFNAMSIZ];
extern void ind_hisi_com(void *info, u32 len);

typedef struct
{
	VOS_MSG_HEADER
	VOS_UINT32 usLen;
	VOS_UINT8 aucValue[4];
} BASTET_MSG_STRU;

int bastet_comm_write(u8 *msg, u32 len)
{
	BASTET_MSG_STRU *pMsg = NULL;
	VOS_UINT32 ulLength = 0;

	if (NULL == msg) {
		return -1;
	}

	ulLength = sizeof(BASTET_MSG_STRU) + BST_MAX_WRITE_PAYLOAD - 4;
	pMsg = (BASTET_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_BASTET_COMM, ulLength);
	if (NULL == pMsg) {
		vos_printf("PS_ALLOC_MSG_WITH_HEADER_LEN failed");
		return -1;
	}

	pMsg->ulReceiverPid = UEPS_PID_BASTET;
	PS_MEM_CPY((VOS_VOID*)pMsg->aucValue, msg, len);

	pMsg->usLen = len;

	if (PS_SEND_MSG(ACPU_PID_BASTET_COMM, pMsg) != 0) {
		vos_printf("PS_SEND_MSG failed");
		return -1;
	}

	return 0;
}

void bastet_comm_recv(MsgBlock *pMsg)
{
	u32 len = 0;
	BASTET_MSG_STRU *pTmpMsg = (BASTET_MSG_STRU *)pMsg;

	if (NULL == pMsg) {
		vos_printf("MsgBlock is empty");
		return;
	}

	len = pTmpMsg->usLen;
	if (len > BST_MAX_WRITE_PAYLOAD) {
		len = BST_MAX_WRITE_PAYLOAD;
	}
	ind_hisi_com(pTmpMsg->aucValue, len);
}

/*
 * Get modem id and rab id.
 */
int get_modem_rab_id(struct bst_modem_rab_id *info)
{
	struct net_device *dev;
	RNIC_SPEC_CTX_STRU *spec_net_card;
	RNIC_PDP_CTX_STRU *pdp_addr;
	RNIC_NETCARD_DEV_INFO_STRU *priv;

	if (NULL == info) {
		return -EINVAL;
	}

	dev = dev_get_by_name(&init_net, cur_netdev_name);
	if (NULL == dev) {
		return -ENOENT;
	}

	priv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(dev);

	spec_net_card = RNIC_GetSpecNetCardCtxAddr(priv->enRmNetId);
	pdp_addr = &spec_net_card->stPdpCtx;

	if (RNIC_PDP_REG_STATUS_ACTIVE != pdp_addr->stIpv4PdpInfo.enRegStatus) {
		vos_printf("Ipv4 pdp reg status inactive");
		return -EPERM;
	}

	info->modem_id = spec_net_card->enModemId;
	/* Bastet only running in IPv4 mode,
	 * so, get IPv4 Pdp info */
	info->rab_id = pdp_addr->stIpv4PdpInfo.ucRabId;

	return 0;
}

/*lint -e10*/
void bastet_comm_init(void)
{
	BASTET_CommRegRecvCallBack((RECV_MSG_PROC)bastet_comm_recv);
}
/*lint +e10*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
