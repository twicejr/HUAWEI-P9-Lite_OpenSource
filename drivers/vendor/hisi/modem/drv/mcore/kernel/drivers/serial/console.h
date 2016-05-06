
#ifndef __M_CONSOLE_H__
#define __M_CONSOLE_H__

#include <cmsis_os.h>
#include "ring_buffer.h"
#include "serial_core.h"

struct simple_console {
	struct uart_ldisc ldisc;
	osThreadId cmd_process_tid;
	osSemaphoreId cmd_process_sem;
	DECLARE_S_RING_BUFFER(send_buff, 1024);
	DECLARE_S_RING_BUFFER(recv_buff, 128);
	int echo_enabled;
	int enabled;
};

extern struct simple_console g_console;

int console_init(void);

int console_xput(char ch, void *cookie);

void console_flush(void);

#endif
