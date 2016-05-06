#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "pmom_cat.h"
#include "dpm_m3pm.h"
#include "cpufreq_regulator.h"
#include "ipc_clk.h"
#include "pm_parse.h"
#include "wakelock_parse.h"
#include "bbp_pmu.h"
#include "icc.h"
#include "nvim.h"
#include "rfile.h"
#include "dsp.h"
#include "tcxo.h"
#include "cosa.h"
#include "pm_log_cat.h"

void pm_log_str_dummy_msg_parse(char *in_buf, size_t len, char *out_buf, unsigned int *out_ptr)
{
	unsigned int data_len = 0;
	unsigned int i        = 0;

	if (0 == len || NULL == in_buf) {
		return;
	}

	if (len % 4 == 0) {
		for (i = 0; i < (len - 4); i += 4) {
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "0x%08x, ", *(u32 *)in_buf);
			in_buf   += 4;
			*out_ptr = *out_ptr + data_len;
		}

		/* 最后一个数据要加回车 */
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "0x%08x\n", *(u32 *)in_buf);
		in_buf += 4;
		*out_ptr = *out_ptr + data_len;
	}else {
		modem_log_debug("err: non-4byte align\n");
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "non-4byte align:");
		*out_ptr = *out_ptr + data_len;

		for (i = 0; i < len - 1; i++) {
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "%2x ", *(u32 *)in_buf);
			in_buf ++;
			*out_ptr = *out_ptr + data_len;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "%2x\n", *(u32 *)in_buf);
		in_buf ++;
		*out_ptr = *out_ptr + data_len;
	}
}

int pm_log_waketime_parse(char *in_buf, size_t len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	unsigned int *interval = (unsigned int *)in_buf;

	/* step1: 消息类型检查 */
	if(len != sizeof(*interval)) {
		return -1;
	}

	/* step2: 格式化消息到out_buf: 以回车结束 */
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,"wake_acore_interval=%dsec\n", *interval);
	*out_ptr = *out_ptr + data_len;

	return 0;
}

void pm_log_str_msg_parse(struct modem_logger *logger, char *buf, struct pm_om_log_header *msg_head, unsigned int *str_ptr)
{
	int ret                 = PMOM_OK;
	char *magic_name        = NULL;
	unsigned int i          = 0;
	unsigned int data_len   = 0;
	unsigned int msg_magic  = 0;
	unsigned int msg_len    = 0;
	unsigned int msg_typeid = 0;
	unsigned int head_len   = sizeof(struct pm_om_log_header);
	struct tm *ptm          = NULL;
	struct timeval tv;
	struct modem_logger_list *logger_list = logger->top;

	/* step1: format date */
	gettimeofday(&tv, NULL);
	ptm = localtime(&(tv.tv_sec));
	if (ptm) {
		strftime(logger_list->timebuf, sizeof(logger_list->timebuf), "%m-%d %H:%M:%S", ptm);

		data_len = snprintf(&logger_list->str_buf[*str_ptr], sizeof(logger_list->str_buf),
			"%s.%03ld ", logger_list->timebuf, tv.tv_usec / 1000);
		*str_ptr += data_len;
	}

	/* step2: format message head */
	magic_name  = (char *)&msg_head->magic;
	msg_magic  = msg_head->magic;
	msg_len    = msg_head->length;
	msg_typeid = msg_head->typeid;

	data_len    = snprintf(&logger_list->str_buf[*str_ptr], sizeof(logger_list->str_buf),
				"[0x%08x] [0x%08x] [%c%c%c%c, 0x%08x] ", msg_head->timestamp, msg_head->sn, 
				magic_name[0], magic_name[1], magic_name[2], magic_name[3], 
				msg_len);
	*str_ptr += data_len;
	buf += head_len;

	ret = PMOM_OK;
	switch (msg_magic) {
		case PM_OM_MAGIC_CPUF:
			ret = cpufreq_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_REGU:
			ret = regulator_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_DPM:
			ret = dpm_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_PMM:
			ret = m3pm_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_ACLK:
			ret = clk_msg_parse(PM_LOG_ACORE, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_CCLK:
			ret = clk_msg_parse(PM_LOG_CCORE, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_AIPC:
			ret = ipc_msg_parse(PM_LOG_ACORE, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_CIPC:
			ret = ipc_msg_parse(PM_LOG_CCORE, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_PMA:
			ret = pm_msg_parse_acore(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_PMC:
			ret = pm_msg_parse_ccore(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_WAKE:
			ret = wakelock_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;
        case PM_OM_MAGIC_BBP:
			ret = bbp_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
        case PM_OM_MAGIC_PMU:
			ret = pmu_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;
        case PM_OM_MAGIC_NVA:
            ret = nvim_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
            break;
        case PM_OM_MAGIC_NVC:
            ret = nvim_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
            break;
		case PM_OM_MAGIC_AICC:
			ret = icc_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_CICC:
			ret = icc_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;

		case PM_OM_MAGIC_DSP:
			ret = dsp_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_ARFILE:
			ret = rfile_msg_parse(msg_typeid, buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_PMLG:
			ret = pm_log_waketime_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;
		case PM_OM_MAGIC_TCXO:
			ret = tcxo_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
			break;
        case PM_OM_MAGIC_COSA:
            ret = pm_cosa_main_parse(buf, msg_len, logger_list->str_buf, str_ptr);
            break;
		default:
			ret = PMOM_ERR;
			break;
	}

	if (ret != PMOM_OK) {
		pm_log_str_dummy_msg_parse(buf, msg_len, logger_list->str_buf, str_ptr);
	}

	return;
}

int pm_log_bin_msg_iterate(char *buf)
{
	struct pm_om_log_header *msg_head= (struct pm_om_log_header *)buf;
	return (sizeof(*msg_head) + msg_head->length);
}

size_t pm_log_msg_handle(struct modem_logger *logger, char *buf, size_t len)
{
	struct pm_om_log_header *msg_head = NULL;
	ssize_t nw       = 0;
	size_t read_off  = 0;
	size_t parse_len = 0;
	size_t head_len  = sizeof(*msg_head);
	size_t msg_len   = 0;
	size_t i;
	struct modem_logger_list *logger_list = logger->top;

	modem_log_debug("buf=%p, len=0x%x, head_len=0x%x, out_file_type=%d\n", buf, 
		(unsigned int)len, (unsigned int)head_len, logger->output_file.type);

	while (read_off < len) {
		msg_head = (struct pm_om_log_header *)buf;
		msg_len  = msg_head->length;

		if ((len - read_off) < head_len || (len - read_off) < (head_len + msg_len)) {
			modem_log_debug("break loop: magic=0x%x, msg_len= 0x%x, head_len=0x%x, read_off=0x%x\n", 
				msg_head->magic, (unsigned int)msg_len, (unsigned int)head_len, (unsigned int)read_off);
			for (i = 0; i < (len - read_off + 20); i += 4) {
				printf("0x%08x, ", *(u32 *)(buf + i));
			}
			printf("0x%08x\n", *(u32 *)(buf + i));
			break;
		}

		if (MODEM_T_PARSER_STRING == logger->output_file.type) {
			pm_log_str_msg_parse(logger, buf, msg_head, &logger->output_file.str_wr);

			if(0 != access(logger->output_file.name, F_OK)) {
				modem_log_rotate(logger);
			}
			nw = write(logger->output_file.fd, logger_list->str_buf, logger->output_file.str_wr);
		}
		else if (MODEM_T_PARSER_BINARY == logger->output_file.type) {
			pm_log_bin_msg_iterate(buf);

			if(0 != access(logger->output_file.name, F_OK)) {
				modem_log_rotate(logger);
			}
			nw = write(logger->output_file.fd, buf, read_off);
		}
		logger->output_file.str_wr = 0;

		logger->output_file.size_cnt += nw;
		if (logger->output_file.rotate_size > 0 && (logger->output_file.size_cnt / 1024) >= logger->output_file.rotate_size) {
			modem_log_debug("call modem_log_rotate\n");
			modem_log_rotate(logger);
		}

		buf      += (head_len + msg_len);
		read_off += (head_len + msg_len);
	} /* while (read_off < len) */

	return read_off;
}

void pmom_cat(struct modem_logger *logger, ssize_t *left_size)
{
	char *buf         = NULL;
	ssize_t nr, read_off  = 0;
	ssize_t i;

	buf = logger->top->parsed_buf;

	modem_log_debug("[%s]: begin, buf=0x%p\n", logger->input_file.name, buf);
	nr = read(logger->input_file.fd, buf + *left_size, MODEM_LOG_CAT_BUFSIZE - *left_size);
	if(nr < 0) {
		modem_log_pr_err("read fail! buf_size = 0x%x\n", MODEM_LOG_CAT_BUFSIZE);
		sleep(1);
		return;
	}
	if (*left_size > 0) {
		modem_log_info("read: \n" );
		for (i = 0; i < *left_size+48; i += 4) {
			modem_log_info("0x%08x, ", *(u32 *)(buf + i));
		}
		modem_log_info("0x%08x\n", *(u32 *)(buf + i));
	}

	/* 消息处理 */
	read_off = pm_log_msg_handle(logger, buf, nr + *left_size);
	if (read_off == 0 || read_off > MODEM_LOG_CAT_BUFSIZE)
	{
		modem_log_pr_err("read_off= 0x%x, msg parse error\n", (unsigned int)read_off);
		for (i = 0; i < 100; i += 4)
		{
			modem_log_info("0x%08x, ", *(u32 *)(buf + i));
		}
		modem_log_info("\n");
	}

	/* 处理剩余非对齐的包 */
	*left_size =  nr + *left_size - read_off;
	modem_log_debug("[%s]: end, nr= 0x%x, read_off=0x%x, left=0x%x\n\n", logger->input_file.name, 
		(unsigned int)nr, (unsigned int)read_off, (unsigned int)(*left_size));
	if (*left_size > 0)
	{
		memcpy((void *)buf, (void *)(buf + read_off), *left_size);
	}
}
