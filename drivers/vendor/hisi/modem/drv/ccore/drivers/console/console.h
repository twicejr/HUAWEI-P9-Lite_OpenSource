#ifndef __BALONG_CONSOLE_H_
#define __BALONG_CONSOLE_H_

#include <osl_list.h>
#include <osl_spinlock.h>
#include <bsp_icc.h>
#include "ringbuffer.h"
#include "virtshell.h"

#define LOG_BUF_SHIFT 14
#define CMD_BUF_SHIFT 7

#define CON_ACORE ICC_CPU_APP
#define CON_CCORE ICC_CPU_MODEM
#define CON_MCORE ICC_CPU_MCU
#if defined(__KERNEL__)
#define CON_CURCORE ICC_CPU_APP
#elif defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
#define CON_CURCORE ICC_CPU_MODEM
#elif defined(__CMSIS_RTOS)
#define CON_CURCORE ICC_CPU_MCU
#endif

#define CON_OK           0x0
#define CON_ERR_NULL_PTR 0x1
#define CON_ERR_EXIST    0x2
#define CON_ERR_NOEXIST  0x3


#define CON_ENABLE   (0x1U << 0)
#define CON_PRIMARY  (0x1U << 1)

#define CON_INFLG_AGENT    (1U << 0)
#define CON_INFLG_ICC      (1U << 1)
#define CON_INFLG_UART     (1U << 2)
#define CON_INFLG_CONSTANT (1U << 3)

struct console
{
	/* set by user */
	char name[16];
	void * data;
	void (*start_tx)(struct console * con);
	int (*start_shell)(struct console *con);
	unsigned int coreid;
	unsigned int inflags;
	struct con_ring_buffer cmdbuf;
	struct con_ring_buffer logbuf;
	spinlock_t logbuf_lock;
	/* Set by console manager */
	struct virtshl_icc_l16id * icchn;
	struct console * predecessor;
	/* set by console driver, console ldisc */
	int (*tx)(struct console * con, unsigned char * outbuf, unsigned int size);
	int (*rx)(struct console * con, unsigned char * inbuf, unsigned int size);
	void (*put)(struct console * con, unsigned char * inbuf, unsigned int size);
	int (*get)(struct console * con, unsigned char * outbuf, unsigned int size);

	/* private data, not permitted for user to use */
	struct list_head next;
	unsigned int flags;
};

extern struct list_head consoles;
extern struct list_head agent_consoles;

int con_early_register(struct console * con_new);
int con_register(struct console * con_new);
int con_unregister(struct console * con_new);
struct console * con_get_cur_con(void);
int con_enable(struct console * con);
int con_disable(struct console * con);
int con_driver_lock(void);
int con_driver_unlock(void);
void con_log_clear(struct console * con);
int con_init(void);

#endif
