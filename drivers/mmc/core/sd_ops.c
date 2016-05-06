

#include <linux/slab.h>
#include <linux/types.h>
#include <linux/export.h>
#include <linux/scatterlist.h>

#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>

#include "core.h"
#include "sd_ops.h"
#ifdef CONFIG_HUAWEI_SDCARD_DSM
#include <linux/mmc/dsm_sdcard.h>
#endif
int mmc_app_cmd(struct mmc_host *host, struct mmc_card *card)
{
	int err;
	struct mmc_command cmd = {0};
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	char *log_buff;
	int buff_len;
#endif
	BUG_ON(!host);
	BUG_ON(card && (card->host != host));

	cmd.opcode = MMC_APP_CMD;

	if (card) {
		cmd.arg = card->rca << 16;
		cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	} else {
		cmd.arg = 0;
		cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_BCR;
	}

	err = mmc_wait_for_cmd(host, &cmd, 0);
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	
	if(!strcmp(mmc_hostname(host), "mmc1"))
	{
		 dsm_sdcard_cmd_logs[DSM_SDCARD_CMD55].value = cmd.resp[0];
	}
	
	if (err)
	{
		if(-ENOMEDIUM != err && -ETIMEDOUT != err
		&& !strcmp(mmc_hostname(host), "mmc1") && !dsm_client_ocuppy(sdcard_dclient))
		{	
			log_buff = dsm_sdcard_get_log(DSM_SDCARD_CMD55,err);
			buff_len = strlen(log_buff);
			dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
			dsm_client_notify(sdcard_dclient,DSM_SDCARD_CMD55_RESP_ERR);
		}
	
		return err;
	}
#else 
	if (err)
		return err;
#endif

	/* Check that card supported application commands */
	if (!mmc_host_is_spi(host) && !(cmd.resp[0] & R1_APP_CMD))
		return -EOPNOTSUPP;

	return 0;
}
EXPORT_SYMBOL_GPL(mmc_app_cmd);

/**
 *	mmc_wait_for_app_cmd - start an application command and wait for
 			       completion
 *	@host: MMC host to start command
 *	@card: Card to send MMC_APP_CMD to
 *	@cmd: MMC command to start
 *	@retries: maximum number of retries
 *
 *	Sends a MMC_APP_CMD, checks the card response, sends the command
 *	in the parameter and waits for it to complete. Return any error
 *	that occurred while the command was executing.  Do not attempt to
 *	parse the response.
 */
int mmc_wait_for_app_cmd(struct mmc_host *host, struct mmc_card *card,
	struct mmc_command *cmd, int retries)
{
	struct mmc_request mrq = {NULL};

	int i, err;

	BUG_ON(!cmd);
	BUG_ON(retries < 0);

	err = -EIO;

	/*
	 * We have to resend MMC_APP_CMD for each attempt so
	 * we cannot use the retries field in mmc_command.
	 */
	for (i = 0;i <= retries;i++) {
		err = mmc_app_cmd(host, card);
		if (err) {
			/* no point in retrying; no APP commands allowed */
			if (mmc_host_is_spi(host)) {
				if (cmd->resp[0] & R1_SPI_ILLEGAL_COMMAND)
					break;
			}
			continue;
		}

		memset(&mrq, 0, sizeof(struct mmc_request));

		memset(cmd->resp, 0, sizeof(cmd->resp));
		cmd->retries = 0;

		mrq.cmd = cmd;
		cmd->data = NULL;

		mmc_wait_for_req(host, &mrq);

		err = cmd->error;
		if (!cmd->error)
			break;

		/* no point in retrying illegal APP commands */
		if (mmc_host_is_spi(host)) {
			if (cmd->resp[0] & R1_SPI_ILLEGAL_COMMAND)
				break;
		}
	}

	return err;
}

EXPORT_SYMBOL(mmc_wait_for_app_cmd);

int mmc_app_set_bus_width(struct mmc_card *card, int width)
{
	int err;
	struct mmc_command cmd = {0};

	BUG_ON(!card);
	BUG_ON(!card->host);

	cmd.opcode = SD_APP_SET_BUS_WIDTH;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	switch (width) {
	case MMC_BUS_WIDTH_1:
		cmd.arg = SD_BUS_WIDTH_1;
		break;
	case MMC_BUS_WIDTH_4:
		cmd.arg = SD_BUS_WIDTH_4;
		break;
	default:
		return -EINVAL;
	}

	err = mmc_wait_for_app_cmd(card->host, card, &cmd, MMC_CMD_RETRIES);
	if (err)
		return err;

	return 0;
}

int mmc_send_app_op_cond(struct mmc_host *host, u32 ocr, u32 *rocr)
{
	struct mmc_command cmd = {0};
	int i, err = 0;
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	int buff_len;
	char *log_buff;
#endif
	BUG_ON(!host);

	cmd.opcode = SD_APP_OP_COND;
	if (mmc_host_is_spi(host))
		cmd.arg = ocr & (1 << 30); /* SPI only defines one bit */
	else
		cmd.arg = ocr;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R3 | MMC_CMD_BCR;

	for (i = 100; i; i--) {
		err = mmc_wait_for_app_cmd(host, NULL, &cmd, MMC_CMD_RETRIES);
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	if (err)
	{	
		if(-ENOMEDIUM != err && -ETIMEDOUT != err
		&& !strncmp(mmc_hostname(host), "mmc1", sizeof("mmc1")) && !dsm_client_ocuppy(sdcard_dclient))
		{

			dsm_sdcard_cmd_logs[DSM_SDCARD_ACMD41].value = cmd.resp[0];
			
			log_buff = dsm_sdcard_get_log(DSM_SDCARD_ACMD41,err);		
			buff_len = strlen(log_buff);
			dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
			dsm_client_notify(sdcard_dclient, DSM_SDCARD_ACMD41_RESP_ERR);

		}

		break;
	}
#else
	if (err)
		break;
#endif
		/* if we're just probing, do a single pass */
		if (ocr == 0)
			break;

		/* otherwise wait until reset completes */
		if (mmc_host_is_spi(host)) {
			if (!(cmd.resp[0] & R1_SPI_IDLE))
				break;
		} else {
			if (cmd.resp[0] & MMC_CARD_BUSY)
				break;
		}

		err = -ETIMEDOUT;

		mmc_delay(10);
	}
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	if(!strncmp(mmc_hostname(host), "mmc1", sizeof("mmc1")))
	{
		dsm_sdcard_cmd_logs[DSM_SDCARD_ACMD41].value = cmd.resp[0];
	}
#endif
	if (rocr && !mmc_host_is_spi(host))
		*rocr = cmd.resp[0];

	return err;
}

int mmc_send_if_cond(struct mmc_host *host, u32 ocr)
{
	struct mmc_command cmd = {0};
	int err;
	static const u8 test_pattern = 0xAA;
	u8 result_pattern;
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	int buff_len;
	char *log_buff;
#endif
	/*
	 * To support SD 2.0 cards, we must always invoke SD_SEND_IF_COND
	 * before SD_APP_OP_COND. This command will harmlessly fail for
	 * SD 1.0 cards.
	 */
	cmd.opcode = SD_SEND_IF_COND;
	cmd.arg = ((ocr & 0xFF8000) != 0) << 8 | test_pattern;
	cmd.flags = MMC_RSP_SPI_R7 | MMC_RSP_R7 | MMC_CMD_BCR;

	err = mmc_wait_for_cmd(host, &cmd, 0);
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	
	if(!strcmp(mmc_hostname(host), "mmc1"))
	{
		 dsm_sdcard_cmd_logs[DSM_SDCARD_CMD8].value = cmd.resp[0];
	}
	
	if (err)
	{
		if(-ENOMEDIUM != err && -ETIMEDOUT != err
		&& !strcmp(mmc_hostname(host), "mmc1") && !dsm_client_ocuppy(sdcard_dclient))
		{
			log_buff = dsm_sdcard_get_log(DSM_SDCARD_CMD8,err);
			buff_len = strlen(log_buff);
			dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
			dsm_client_notify(sdcard_dclient, DSM_SDCARD_CMD8_RESP_ERR);

		}

		return err;
	}
#else
	if (err)
		return err;

#endif
	if (mmc_host_is_spi(host))
		result_pattern = cmd.resp[1] & 0xFF;
	else
		result_pattern = cmd.resp[0] & 0xFF;

	if (result_pattern != test_pattern)
		return -EIO;

	return 0;
}

int mmc_send_relative_addr(struct mmc_host *host, unsigned int *rca)
{
	int err;
	struct mmc_command cmd = {0};
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	int buff_len;
	char *log_buff;
#endif
	BUG_ON(!host);
	BUG_ON(!rca);

	cmd.opcode = SD_SEND_RELATIVE_ADDR;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R6 | MMC_CMD_BCR;

	err = mmc_wait_for_cmd(host, &cmd, MMC_CMD_RETRIES);
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	if(!strcmp(mmc_hostname(host), "mmc1"))
	{
		 dsm_sdcard_cmd_logs[DSM_SDCARD_CMD3].value = cmd.resp[0];
	}

	if (err)
	{
		if(-ENOMEDIUM != err && -ETIMEDOUT != err
		&& !strcmp(mmc_hostname(host), "mmc1") && !dsm_client_ocuppy(sdcard_dclient))
		{
			log_buff = dsm_sdcard_get_log(DSM_SDCARD_CMD3,err);
			buff_len = strlen(log_buff);
			dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
			dsm_client_notify(sdcard_dclient, DSM_SDCARD_CMD3_RESP_ERR);
		}

		return err;
	}
#else
	if (err)
		return err;
#endif
	*rca = cmd.resp[0] >> 16;

	return 0;
}

int mmc_app_send_scr(struct mmc_card *card, u32 *scr)
{
	int err;
	struct mmc_request mrq = {NULL};
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct scatterlist sg;
	void *data_buf;

	BUG_ON(!card);
	BUG_ON(!card->host);
	BUG_ON(!scr);

	/* NOTE: caller guarantees scr is heap-allocated */

	err = mmc_app_cmd(card->host, card);
	if (err)
		return err;

	/* dma onto stack is unsafe/nonportable, but callers to this
	 * routine normally provide temporary on-stack buffers ...
	 */
	data_buf = kmalloc(sizeof(card->raw_scr), GFP_KERNEL);

	if (data_buf == NULL)
		return -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_APP_SEND_SCR;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 8;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, data_buf, 8);

	mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(card->host, &mrq);

	memcpy(scr, data_buf, sizeof(card->raw_scr));
	kfree(data_buf);

	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	scr[0] = be32_to_cpu(scr[0]);
	scr[1] = be32_to_cpu(scr[1]);

	return 0;
}

int mmc_sd_switch(struct mmc_card *card, int mode, int group,
	u8 value, u8 *resp)
{
	struct mmc_request mrq = {NULL};
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct scatterlist sg;
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	int buff_len;
	char *log_buff;
#endif
	BUG_ON(!card);
	BUG_ON(!card->host);

	/* NOTE: caller guarantees resp is heap-allocated */

	mode = !!mode;
	value &= 0xF;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_SWITCH;
	cmd.arg = mode << 31 | 0x00FFFFFF;
	cmd.arg &= ~(0xF << (group * 4));
	cmd.arg |= value << (group * 4);
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, resp, 64);

	mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(card->host, &mrq);
#ifdef CONFIG_HUAWEI_SDCARD_DSM
	if(!strcmp(mmc_hostname(card->host), "mmc1"))
	{
		 dsm_sdcard_cmd_logs[DSM_SDCARD_CMD6_CMDERR].value = cmd.error;
		 dsm_sdcard_cmd_logs[DSM_SDCARD_CMD6_DATERR].value = data.error;
		 if((cmd.error || data.error)&&(!dsm_client_ocuppy(sdcard_dclient)))
		 {
		    log_buff = dsm_sdcard_get_log(DSM_SDCARD_CMD6_DATERR,data.error);
			buff_len = strlen(log_buff);
			dsm_client_copy(sdcard_dclient,log_buff,buff_len + 1);
			dsm_client_notify(sdcard_dclient, DSM_SDCARD_CMD6_RESP_ERR);
		 }
	}
#endif
	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	return 0;
}

int mmc_app_sd_status(struct mmc_card *card, void *ssr)
{
	int err;
	struct mmc_request mrq = {NULL};
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct scatterlist sg;

	BUG_ON(!card);
	BUG_ON(!card->host);
	BUG_ON(!ssr);

	/* NOTE: caller guarantees ssr is heap-allocated */

	err = mmc_app_cmd(card->host, card);
	if (err)
		return err;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_APP_SD_STATUS;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, ssr, 64);

	mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(card->host, &mrq);

	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	return 0;
}
