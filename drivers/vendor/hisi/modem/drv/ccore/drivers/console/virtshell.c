#include <string.h>
#include <securec.h>
#include <osl_malloc.h>
#include <bsp_icc.h>
#include <bsp_slice.h>
#include "../serial/serial_core.h"
#include "ringbuffer.h"
#include "console.h"
#include "con_platform.h"
#include "virtshell.h"

struct virtshl_module_ctr virtshl_ctrl_info;

int virtshl_ctrl_cmd_process(unsigned char * cmd, unsigned int size);

void virtshl_send_tsk_func(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	static unsigned char tmpbuf[VIRTSHL_MAX_PACKAGE_LEN] = {0,};
	unsigned char * outbuf = tmpbuf;
	int retval = 0;
	int len = 0;

	/* coverity[no_escape] */
	while(1)
	{
WAIT_FOR_SPACE:
		down(&virtshl_ctrl_info.send_tsk_sem);

		while(!list_empty(&virtshl_ctrl_info.slist))
		{
			struct console * con = NULL;
			struct virtshl_icc_l16id * chn = NULL;
			unsigned long slist_lock_flg = 0;

			spin_lock_irqsave(&virtshl_ctrl_info.slist_lock, slist_lock_flg);
			chn = list_first_entry(&virtshl_ctrl_info.slist, struct virtshl_icc_l16id, slist);
			con = chn->con;

			list_del_init(&chn->slist);
			spin_unlock_irqrestore(&virtshl_ctrl_info.slist_lock, slist_lock_flg);

			/*lint -e506*/
			do{
				outbuf = tmpbuf;

				if(NULL == con)
					break;
				else if(con->coreid != CON_CURCORE)
					len = con->get(con, outbuf, VIRTSHL_MAX_PACKAGE_LEN);
				else
					len = con->tx(con, outbuf, VIRTSHL_MAX_PACKAGE_LEN);

				if(len <= 0)
					break;

				retval = bsp_icc_send(chn->target_coreid, chn->chn_id, outbuf, (unsigned int)len);
				if(retval < len)
				{
					goto WAIT_FOR_SPACE;
				}
				else
				{
					/* everything is ok. */
				}
			}while(1);
			/*lint +e506*/
		}
	}
}

void virtshl_start_tx(struct console * con)
{
	struct virtshl_icc_l16id * chn = con->icchn;
	unsigned long slist_lock_flg = 0;

	spin_lock_irqsave(&virtshl_ctrl_info.slist_lock, slist_lock_flg);
	if(list_empty_careful(&chn->slist))
		list_add_tail(&chn->slist, &virtshl_ctrl_info.slist);
	spin_unlock_irqrestore(&virtshl_ctrl_info.slist_lock, slist_lock_flg);

	up(&virtshl_ctrl_info.send_tsk_sem);
}

int virtshl_start_shell(struct console * con)
{
	struct virtshl_icc_l16id * chn = con->icchn;
	unsigned long slist_lock_flg = 0;

	if(NULL == chn)
		return -1;

	spin_lock_irqsave(&virtshl_ctrl_info.slist_lock, slist_lock_flg);
	if(list_empty_careful(&chn->slist))
		list_add_tail(&chn->slist, &virtshl_ctrl_info.slist);
	spin_unlock_irqrestore(&virtshl_ctrl_info.slist_lock, slist_lock_flg);

	up(&virtshl_ctrl_info.send_tsk_sem);

	return 0;
}

void virtshl_recv_tsk_func(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4)
{
	static unsigned char tmpbuf[VIRTSHL_MAX_PACKAGE_LEN] = {0,};

	/* coverity[no_escape] */
	while(1)
	{
		down(&virtshl_ctrl_info.recv_tsk_sem);

		while(!list_empty(&virtshl_ctrl_info.rlist))
		{
			struct console * con = NULL;
			struct virtshl_icc_l16id* chn = NULL;
			int icc_return_sz = 0;
			unsigned long rlist_lock_flg = 0;

			spin_lock_irqsave(&virtshl_ctrl_info.rlist_lock, rlist_lock_flg);
			chn = list_first_entry(&virtshl_ctrl_info.rlist, struct virtshl_icc_l16id, rlist);
			con = chn->con;

			list_del_init(&chn->rlist);
			spin_unlock_irqrestore(&virtshl_ctrl_info.rlist_lock, rlist_lock_flg);

			while(1)
			{
				icc_return_sz = bsp_icc_read(chn->chn_id, tmpbuf, VIRTSHL_MAX_PACKAGE_LEN);
				if(icc_return_sz <= 0 || icc_return_sz > VIRTSHL_MAX_PACKAGE_LEN)
				{
					/* TODO: some unknown error happens, take it */
					break;
				}

				if(NULL == con)
				{
					(void)virtshl_ctrl_cmd_process(tmpbuf, (unsigned int)icc_return_sz);
				}
				else if(con->coreid != CON_CURCORE)
				{
					(void)con->put(con, tmpbuf, (unsigned int)icc_return_sz);
					if(con->start_tx)
						(void)con->start_tx(con);
				}
				else
				{
					(void)con->rx(con, tmpbuf, (unsigned int)icc_return_sz);
				}
			}
		}
	}
}

int virtshl_icc_readcb(unsigned int chn_id, unsigned int len, void * context)
{
	struct virtshl_icc_l16id * chn = (struct virtshl_icc_l16id *)context;
	unsigned long rlist_lock_flg = 0;

	spin_lock_irqsave(&virtshl_ctrl_info.rlist_lock, rlist_lock_flg);
	if(list_empty_careful(&chn->rlist))
	{
		list_add_tail(&chn->rlist, &virtshl_ctrl_info.rlist);
	}
	spin_unlock_irqrestore(&virtshl_ctrl_info.rlist_lock, rlist_lock_flg);

	up(&virtshl_ctrl_info.recv_tsk_sem);

	return 0;
}


static unsigned int virtshl_get_nxt_id(struct virtshl_icc_h16id * hchn)
{
	unsigned int nxtid = ~0U;

	nxtid = hchn->next_l16id;

	/* TODO: Think about using atomic integer */
	hchn->next_l16id++;
	if(hchn->next_l16id >= 20)/* 20 is the maxmum number of icc sub channel */
		hchn->next_l16id = 1;

	return nxtid;
}

void virtshl_gen_con_name(char * namebuf, unsigned int coreid, unsigned int chnid)
{
	int i = 0;
	char tmpch = 0;

	for(i = 0; i < (int)sizeof(unsigned int); i++)
	{
		tmpch = (char)((coreid >> (i * 4)) & 0xF);
		*namebuf = tmpch <= 9 ? (tmpch + '0') : (tmpch - 10 + 'A');
		namebuf++;
	}

	for(i = 0; i < (int)sizeof(unsigned int); i++)
	{
		tmpch = (char)((chnid >> (i * 4)) & 0xF);
		*namebuf = tmpch <= 9 ? (tmpch + '0') : (tmpch - 10 + 'A');
		namebuf++;
	}

	*namebuf = 0;
}

/*
 * Input must be a complete command.
 */
/*lint -e413*/
int virtshl_ctrl_cmd_process(unsigned char * cmd, unsigned int size)
{
	struct virtshl_ctrl_cmd * ctrl_cmd = (struct virtshl_ctrl_cmd *)cmd;
	struct console *con = NULL;
	struct virtshl_icc_l16id * subchn = NULL;
	unsigned char *cmd_base = NULL, *log_base = NULL;
	int retval = 0;
	int h16id_index = 0;

	if(memcmp(ctrl_cmd->cmd_magic, VIRTSHL_CMD_MAGIC, VIRTSHL_CMD_MAGIC_LEN))
		return -VIRTSHL_ERR_NOT_CTRLCMD;

	for(h16id_index = 0; h16id_index < VIRTSHL_MAX_H16ID_NUM; h16id_index++)
	{
		if(virtshl_ctrl_info.h16ids[h16id_index].h16id == (ctrl_cmd->entire_iccid >> 16))
			break;
	}
	if(h16id_index >= VIRTSHL_MAX_H16ID_NUM)
	{
		return -1;
	}

	switch(ctrl_cmd->cmd_type)
	{
	case VCMD_CONNECT:
		con = (struct console *)osl_malloc(sizeof(struct console) + sizeof(struct virtshl_icc_l16id) + (1U << LOG_BUF_SHIFT) + (1U << CMD_BUF_SHIFT));
		subchn = (struct virtshl_icc_l16id *)(con + 1);
		cmd_base = (void*)(subchn + 1);
		log_base = cmd_base + (1U << CMD_BUF_SHIFT);
		if(!con)
		{
			retval = -1;
			goto ACKNOWLEDGE_OUT;
		}

		//memcpy(con->name, VCON_NAME(c), strlen(VCON_NAME(c)));
		virtshl_gen_con_name(con->name, ctrl_cmd->target_coreid, ctrl_cmd->entire_iccid);
		con->coreid = ctrl_cmd->target_coreid;
		con->start_tx = virtshl_start_tx;
		con->start_shell = shell_start;
		con->data = NULL;
		con->inflags = CON_INFLG_ICC;
		con->icchn = subchn;
		con_ring_init(&con->cmdbuf, cmd_base, (1U << CMD_BUF_SHIFT));
		con_ring_init(&con->logbuf, log_base, (1U << LOG_BUF_SHIFT));

		subchn->target_coreid = ctrl_cmd->local_coreid;
		subchn->owner_coreid = ctrl_cmd->local_coreid;
		subchn->chn_id = ctrl_cmd->entire_iccid;
		subchn->con = con;
		INIT_LIST_HEAD(&subchn->subchn_list);
		INIT_LIST_HEAD(&subchn->slist);
		INIT_LIST_HEAD(&subchn->rlist);

		retval  = bsp_icc_event_register(subchn->chn_id, virtshl_icc_readcb, subchn, NULL, NULL);
		retval += con_register(con);
		if(retval)
		{
			retval = -1;
			osl_free(con);
			goto ACKNOWLEDGE_OUT;
		}

		list_add(&subchn->subchn_list, &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list);
ACKNOWLEDGE_OUT:
		ctrl_cmd->acknowledge = retval ? VACK_FAIL : VACK_SUCC;
		ctrl_cmd->cmd_type = VCMD_CONEC_ACK;
		ctrl_cmd->target_coreid = ctrl_cmd->local_coreid;
		ctrl_cmd->local_coreid = CON_CURCORE;
		retval = bsp_icc_send(ctrl_cmd->target_coreid, ((ctrl_cmd->entire_iccid & 0xFFFF0000) | 0), (unsigned char*)ctrl_cmd, sizeof(struct virtshl_ctrl_cmd));
		if(retval != (int)sizeof(struct virtshl_ctrl_cmd))
		{
			udelay(100);
			goto ACKNOWLEDGE_OUT;
		}

		break;
	case VCMD_DISCONNECT:
		list_for_each_entry(subchn, &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list, subchn_list)
		{
			if(CON_CURCORE == subchn->owner_coreid &&
			   subchn->chn_id == ctrl_cmd->entire_iccid)
			   break;
		}
		if(&subchn->subchn_list == &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list)
		{
			retval = -1;
			break;
		}

		list_del_init(&subchn->subchn_list);

		(void)bsp_icc_event_unregister(ctrl_cmd->entire_iccid);

		con = subchn->con;
		con->icchn = NULL;
		subchn->con = NULL;

		if(con->predecessor)
		{
			(void)con_enable(con->predecessor);
			((struct uart_ldisc *)(con->predecessor->data))->bind_con = con->predecessor;
		}

		(void)con_unregister(con);
		if(con->inflags & CON_INFLG_CONSTANT)
			osl_free(subchn);
		else
			osl_free(con);
		/* last step: clear all data in icc channel */
		/* TODO:clear icc data */

		ctrl_cmd->cmd_type = VCMD_DISCONEC_ACK;
		ctrl_cmd->target_coreid = ctrl_cmd->local_coreid;
		ctrl_cmd->local_coreid = CON_CURCORE;
		ctrl_cmd->acknowledge = VACK_SUCC;

		do{
			retval = bsp_icc_send(ctrl_cmd->target_coreid, ((ctrl_cmd->entire_iccid & 0xFFFF0000) | 0), (unsigned char*)ctrl_cmd, sizeof(struct virtshl_ctrl_cmd));
			if(retval != (int)sizeof(struct virtshl_ctrl_cmd))
				udelay(100);
		}while(retval != (int)sizeof(struct virtshl_ctrl_cmd));

		break;
	case VCMD_CONEC_ACK:
		if(VACK_FAIL == ctrl_cmd->acknowledge)
		{
			list_for_each_entry(subchn, &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list, subchn_list)
			{
				if(CON_CURCORE == subchn->owner_coreid &&
				   subchn->chn_id == ctrl_cmd->entire_iccid)
				   break;
			}
			if(&subchn->subchn_list == &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list)
			{
				retval = -1;
				break;
			}

			list_del_init(&subchn->subchn_list);
			
			(void)bsp_icc_event_unregister(subchn->chn_id);
			
			con = subchn->con;
			con->icchn = NULL;
			subchn->con = NULL;
			(void)con_unregister(con);

			if(con->predecessor)
				(void)con_enable(con->predecessor);

			if(con->inflags & CON_INFLG_CONSTANT)
				osl_free(subchn);
			else
				osl_free(con);
			break;
		}

		break;
	case VCMD_DISCONEC_ACK:
		list_for_each_entry(subchn, &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list, subchn_list)
		{
			if(ctrl_cmd->local_coreid == subchn->owner_coreid &&
			   subchn->chn_id == ctrl_cmd->entire_iccid)
			   break;
		}
		if(&subchn->subchn_list == &virtshl_ctrl_info.h16ids[h16id_index].virtchn_list)
		{
			retval = -1;
			break;
		}

		(void)bsp_icc_event_unregister(subchn->chn_id);
		list_del_init(&subchn->subchn_list);
		osl_free(subchn->con);

		break;
	default:
		break;
	}

	return retval;
}
/*lint +e413*/

unsigned int establish_icc_chn(unsigned int target_core, struct console * con)
{
	unsigned int hid = ~0U, lid = ~0U;
	int i = 0, retval = 0;
	struct virtshl_icc_h16id * hchn = virtshl_ctrl_info.h16ids;
	struct virtshl_icc_l16id * lchn = NULL;
	struct virtshl_ctrl_cmd ctrl_cmd;

	/*
	 * find an available sub channel.
	 */
	for(i = 0; i < (int)virtshl_ctrl_info.h16id_num; i++, i++)
	{
		hchn = &virtshl_ctrl_info.h16ids[i];
		if(CON_CURCORE == hchn->local_coreid &&
		   target_core == hchn->target_coreid)
			break;
	}
	if(i >= (int)virtshl_ctrl_info.h16id_num)
	{
		/*TODO:print something.*/
		return ~0;
	}

	hid = hchn->h16id;
	lid = virtshl_get_nxt_id(hchn);

	lchn = (struct virtshl_icc_l16id *)osl_malloc(sizeof(struct virtshl_icc_l16id));
	if(!lchn)
	{
		return ~0;
	}

	con->predecessor = NULL;
	con->icchn = lchn;

	lchn->target_coreid = target_core;
	lchn->owner_coreid = CON_CURCORE;
	lchn->chn_id = ((hid << 16) | lid);
	lchn->hid_idx = (unsigned int)i;
	lchn->con = con;
	INIT_LIST_HEAD(&lchn->subchn_list);
	INIT_LIST_HEAD(&lchn->slist);
	INIT_LIST_HEAD(&lchn->rlist);

	list_add(&lchn->subchn_list, &hchn->virtchn_list);

	if(bsp_icc_event_register(lchn->chn_id, virtshl_icc_readcb, lchn, NULL, NULL))
		return ~0;

	/*
	 * Notify the target core to establish console.
	 * And we must succeed to send out this message.
	 */
	(void)memcpy(ctrl_cmd.cmd_magic, VIRTSHL_CMD_MAGIC, VIRTSHL_CMD_MAGIC_LEN);
	ctrl_cmd.cmd_type = VCMD_CONNECT;
	ctrl_cmd.local_coreid = CON_CURCORE;
	ctrl_cmd.target_coreid = target_core;
	ctrl_cmd.entire_iccid = lchn->chn_id;
	ctrl_cmd.acknowledge = 0;

	do{
		retval = bsp_icc_send(ctrl_cmd.target_coreid, (hid << 16) | 0, (unsigned char*)&ctrl_cmd, sizeof(ctrl_cmd));
		if(retval != (int)sizeof(ctrl_cmd))
			udelay(100);
	}while(retval != (int)sizeof(ctrl_cmd));

	return 0;
}

int login(int target_core)
{
	struct virtshl_ctrl_cmd ctrl_cmd;
	unsigned int h16id = ~0U;
	unsigned int l16id = ~0U;
	unsigned int memlen = 0;
	int retval = 0;
	int i = 0;
	struct console *con = NULL, *uartcon = NULL;
	struct virtshl_icc_l16id *subchn = NULL;
	void *con_cmd_base = NULL, *con_log_base = NULL;

	if(CON_CURCORE == target_core)
	{
		/* print something. */
		return -1;
	}
	/*
	 * Confirm the current console which recieve command 'login' is bound with an uart.
	 * If the current console is a virtual console, in other words, an icc console, refuse
	 * the request. The reason is:
	 * AUART->ACORE->ICC->CCORE->vconsole->CSHELL   OK!
	 * AUART->ACORE->ICC->CCORE->vconsole->MCORE    DENY!
	 */
	uartcon = con_get_cur_con();
	if(!uartcon || !(uartcon->inflags & CON_INFLG_UART))
	{
		/* print something. */
		return -1;
	}

	/*lint -e413*/
	list_for_each_entry(con, &agent_consoles, next)
	{
		if(con->predecessor && con->predecessor == uartcon)
			return -1;
	}
	/*lint +e413*/

	/*
	 * find an available sub channel.
	 */
	for(i = 0; i < (int)virtshl_ctrl_info.h16id_num; i++)
	{
		if(CON_CURCORE == virtshl_ctrl_info.h16ids[i].local_coreid &&
		   (unsigned int)target_core == virtshl_ctrl_info.h16ids[i].target_coreid)
			break;
	}
	if(i >= (int)virtshl_ctrl_info.h16id_num)
	{
		/*TODO:print something.*/
		return -1;
	}
	h16id = virtshl_ctrl_info.h16ids[i].h16id;
	l16id = virtshl_get_nxt_id(&virtshl_ctrl_info.h16ids[i]);

	/* Establish local core console */
	memlen = sizeof(struct console) + sizeof(struct virtshl_icc_l16id) + (1U << LOG_BUF_SHIFT) + (1U << CMD_BUF_SHIFT);
	con = (struct console *)osl_malloc(memlen);
	subchn = (struct virtshl_icc_l16id *)(con + 1);
	con_cmd_base = (void*)(subchn + 1);
	con_log_base = (void*)((unsigned long)con_cmd_base + (1U << CMD_BUF_SHIFT));
	if(!con)
	{
		retval = -1;
		goto ERR_NOMEM_OUT;
	}

	//memcpy(con->name, VCON_NAME(c), strlen(VCON_NAME(c)));
	virtshl_gen_con_name(con->name, (unsigned int)target_core, ((h16id << 16) | l16id));
	con->data = uartcon->data;
	con->start_tx = uartcon->start_tx;
	con->start_shell = virtshl_start_shell;
	con->coreid = (unsigned int)target_core;
	con->inflags = CON_INFLG_AGENT | CON_INFLG_ICC;
	con->icchn = subchn;
	con->predecessor = uartcon;
	con_ring_init(&con->cmdbuf, con_cmd_base, (1U << CMD_BUF_SHIFT));
	con_ring_init(&con->logbuf, con_log_base, (1U << LOG_BUF_SHIFT));

	subchn->target_coreid = (unsigned int)target_core;
	subchn->owner_coreid = CON_CURCORE;
	subchn->chn_id = ((h16id << 16) | l16id);
	subchn->hid_idx = (unsigned int)i;
	subchn->con = con;
	INIT_LIST_HEAD(&subchn->subchn_list);
	INIT_LIST_HEAD(&subchn->slist);
	INIT_LIST_HEAD(&subchn->rlist);

	list_add(&subchn->subchn_list, &virtshl_ctrl_info.h16ids[i].virtchn_list);

	if(bsp_icc_event_register(subchn->chn_id, virtshl_icc_readcb, subchn, NULL, NULL))
	{
		retval = -1;
		goto ERR_REG_ICC_CHN;
	}
	if(con_register(con))
	{
		retval = -1;
		goto ERR_REG_CON;
	}

	/*
	 * Disable the current console connect with uart console.
	 * The ldisc can only be used by one console.
	 */
	(void)con_disable(uartcon);
	((struct uart_ldisc *)uartcon->data)->bind_con = con;

	/*
	 * Notify the target core to establish console.
	 * And we must succeed to send out this message.
	 */
	(void)memcpy(ctrl_cmd.cmd_magic, VIRTSHL_CMD_MAGIC, VIRTSHL_CMD_MAGIC_LEN);
	ctrl_cmd.cmd_type = VCMD_CONNECT;
	ctrl_cmd.local_coreid = CON_CURCORE;
	ctrl_cmd.target_coreid = (unsigned int)target_core;
	ctrl_cmd.entire_iccid = subchn->chn_id;
	ctrl_cmd.acknowledge = 0;

	do{
		retval = bsp_icc_send(ctrl_cmd.target_coreid, (h16id << 16) | 0, (unsigned char*)&ctrl_cmd, sizeof(ctrl_cmd));
		if(retval != (int)sizeof(ctrl_cmd))
			udelay(100);
	}while(retval != (int)sizeof(ctrl_cmd));

	return 0;

ERR_REG_CON:
ERR_REG_ICC_CHN:
	list_del_init(&subchn->subchn_list);
ERR_NOMEM_OUT:
	return retval;
}

int logout(void)
{
	struct console *vcon = NULL;
	struct virtshl_icc_l16id * lchn = NULL;
	struct virtshl_ctrl_cmd ctrl_cmd;
	unsigned int h16id = ~0U;
	int retval = 0;

	vcon = con_get_cur_con();
	if(!vcon || !(vcon->inflags & CON_INFLG_ICC))
	{
		/* Only virtual console can be logout and destroyed */
		/* TODO: print error */
		return -1;
	}

	lchn = (struct virtshl_icc_l16id *)vcon->icchn;
	h16id = lchn->chn_id >> 16;

	/*
	 * Unregister the current console, no longer recieve any log.
	 * However, the input command through this console can still be processed.
	 */
	(void)con_disable(vcon);
	(void)con_unregister(vcon);
	/* Clear all the log already in current console. */
	con_log_clear(vcon);

	/* notify the corresponding core */
	(void)memcpy(ctrl_cmd.cmd_magic, VIRTSHL_CMD_MAGIC, VIRTSHL_CMD_MAGIC_LEN);
	ctrl_cmd.cmd_type = VCMD_DISCONNECT;
	ctrl_cmd.local_coreid = CON_CURCORE;
	ctrl_cmd.target_coreid = lchn->target_coreid;
	ctrl_cmd.entire_iccid = lchn->chn_id;

	do{
		retval = bsp_icc_send(ctrl_cmd.target_coreid, (h16id << 16) | 0, (unsigned char*)&ctrl_cmd, sizeof(ctrl_cmd));
		if(retval != (int)sizeof(ctrl_cmd))
			udelay(100);
	}while(retval != (int)sizeof(ctrl_cmd));

	return 0;
}

unsigned int g_icc_h16id[VIRTSHL_MAX_H16ID_NUM] = {ICC_CHN_CSHELL};
unsigned int g_targetcore[VIRTSHL_MAX_H16ID_NUM] ={CON_ACORE};
int virtshl_init(void)
{
	int retval = 0;
	int i = 0;
	unsigned int buf_size = 0;
	void * buf_tail_nxt = NULL;
	struct virtshl_icc_l16id * ctrl_chn = NULL;

	INIT_LIST_HEAD(&virtshl_ctrl_info.slist);
	INIT_LIST_HEAD(&virtshl_ctrl_info.rlist);
	sema_init(&virtshl_ctrl_info.send_tsk_sem, SEM_EMPTY);
	sema_init(&virtshl_ctrl_info.recv_tsk_sem, SEM_EMPTY);
	spin_lock_init(&virtshl_ctrl_info.slist_lock);
	spin_lock_init(&virtshl_ctrl_info.rlist_lock);

	buf_size = sizeof(struct virtshl_icc_l16id);
	buf_size += sizeof(struct virtshl_icc_h16id);
	buf_size *= VIRTSHL_MAX_H16ID_NUM;
	buf_tail_nxt = osl_malloc(buf_size);
	if(NULL == buf_tail_nxt)
	{
		retval = -VIRTSHL_ERR_NO_MEM;
		goto NO_MEM_OUT;
	}
	virtshl_ctrl_info.h16ids = (struct virtshl_icc_h16id *)buf_tail_nxt;
	virtshl_ctrl_info.h16id_num = VIRTSHL_MAX_H16ID_NUM;
	ctrl_chn = (struct virtshl_icc_l16id *)(virtshl_ctrl_info.h16ids + VIRTSHL_MAX_H16ID_NUM);

	for(i = 0; i < VIRTSHL_MAX_H16ID_NUM; i++)
	{
		virtshl_ctrl_info.h16ids[i].target_coreid = g_targetcore[i];
		virtshl_ctrl_info.h16ids[i].local_coreid = CON_CURCORE;
		virtshl_ctrl_info.h16ids[i].h16id = g_icc_h16id[i];
		virtshl_ctrl_info.h16ids[i].next_l16id = 1;
		INIT_LIST_HEAD(&virtshl_ctrl_info.h16ids[i].virtchn_list);

		ctrl_chn[i].target_coreid = virtshl_ctrl_info.h16ids[i].target_coreid;
		ctrl_chn[i].owner_coreid = CON_CURCORE;
		ctrl_chn[i].chn_id = (virtshl_ctrl_info.h16ids[i].h16id << 16) | 0;
		ctrl_chn[i].hid_idx = (unsigned int)i;
		ctrl_chn[i].con = NULL;
		INIT_LIST_HEAD(&ctrl_chn[i].subchn_list);
		INIT_LIST_HEAD(&ctrl_chn[i].slist);
		INIT_LIST_HEAD(&ctrl_chn[i].rlist);

		list_add(&ctrl_chn[i].subchn_list, &virtshl_ctrl_info.h16ids[i].virtchn_list);

		retval = bsp_icc_event_register(ctrl_chn[i].chn_id, virtshl_icc_readcb, &ctrl_chn[i], NULL, NULL);
		if(retval)
		{
			retval = -VIRTSHL_ERR_ICC_REG_EVENT;
			goto ICC_CB_REG_FAIL;
		}
	}

	retval = osl_task_init("virtshl_rfunc", VIRTSHL_SEND_TSK_PRIORITY, VIRTSHL_SEND_TSK_STACKSZ,
		virtshl_recv_tsk_func, NULL, &virtshl_ctrl_info.recv_tsk_id);
	if(retval)
		goto TSK_INIT_FAIL;
	retval = osl_task_init("virtshl_sfunc", VIRTSHL_SEND_TSK_PRIORITY, VIRTSHL_SEND_TSK_STACKSZ,
		virtshl_send_tsk_func, NULL, &virtshl_ctrl_info.send_tsk_id);
	if(retval)
	{
		retval = -VIRTSHL_ERR_TSK_INIT;
		goto TSK_INIT_FAIL;
	}

	return retval;

TSK_INIT_FAIL:
ICC_CB_REG_FAIL:
	osl_free(virtshl_ctrl_info.h16ids);
NO_MEM_OUT:
	return retval;
}
