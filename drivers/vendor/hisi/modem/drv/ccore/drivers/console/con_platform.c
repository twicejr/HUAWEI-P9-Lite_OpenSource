#include <sre_io_intf.h>
#include <osl_list.h>
#include <bsp_om.h>
#include "console.h"

static print_hook dump_cb = NULL;

int syslog_recv_fun(char ch)
{
	struct console *pos = NULL;

	if(dump_cb)
		(void)dump_cb(&ch);

	(void)con_driver_lock();

	/*lint -e413*/
	list_for_each_entry(pos, &consoles, next)
	{
		if(ch)
			pos->put(pos, (unsigned char*)&ch, 1);
		if((pos->flags & CON_ENABLE) && pos->start_tx && ('\0' == ch))
			pos->start_tx(pos);
	}
	/*lint +e413*/

	(void)con_driver_unlock();

	return 0;
}

int shell_start(struct console * con)
{
	unsigned char ch = 0;

	while((int)sizeof(char) == con->get(con, &ch, 1))
		(void)SRE_SendChrToShell(ch);
	return 0;
}

void uart_register_hook(print_hook hook)
{
	dump_cb = hook;
}
