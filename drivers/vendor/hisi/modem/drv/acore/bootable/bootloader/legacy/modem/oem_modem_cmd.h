/* this file is for fastboot oem modem commands,
 * all function in this file must be static in order to other files can include this file.
 */
void oem_modem_l2cache_func(const char* sub_cmd, char** details);

struct oem_modem_rx_cmd {
    char* cmd;
    unsigned int cmd_size;
    void (*cmd_handler)(const char* sub_cmd, char** details);
};

static struct oem_modem_rx_cmd oem_modem_cmd_tbl[] = {
	{"l2cache-test", sizeof("l2cache-test"), oem_modem_l2cache_func },
};

static void oem_modem_func(const char* sub_cmd)
{
	unsigned int i, count = sizeof(oem_modem_cmd_tbl) / sizeof(oem_modem_cmd_tbl[0]);
	struct oem_modem_rx_cmd* sub_rx_cmd = &oem_modem_cmd_tbl[0];
    char* result = NULL;

	for (i = 0; i < count; i++, sub_rx_cmd++) {
		if (strncmp(sub_cmd + 1, sub_rx_cmd->cmd, sub_rx_cmd->cmd_size - 1) != 0)
			continue;
		if (sub_rx_cmd->cmd_handler) {
            sub_rx_cmd->cmd_handler(sub_cmd+sub_rx_cmd->cmd_size, &result);
            if (result)
                usbcmd_common_ack(result , ACK_CMD);
            else
                usbcmd_common_ack("FAILno details" , ACK_CMD);

			return;
		} else {
			PRINT_ERROR("Can't find the handler routine for cmd %s \n",sub_rx_cmd->cmd);
		}

	}
	usbcmd_common_ack("FAILinvalid command" , ACK_CMD);
	return;
}


