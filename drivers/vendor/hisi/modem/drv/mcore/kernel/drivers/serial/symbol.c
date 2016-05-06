
#include <osl_types.h>

#include "printk.h"
#include "symbol.h"
#include "console.h"

extern struct symbol kallsyms[];
extern struct simple_console g_console;

extern unsigned kallsyms_count;
extern int strcmp(const char *a, const char *b);

unsigned long kallsyms_lookup_name(const char *name)
{
	unsigned int i;
	
	for (i = 0; i < kallsyms_count; i++) {
		if (strcmp(kallsyms[i].name, name) == 0)
			return 	kallsyms[i].value;
	}
	return 0;
}

static inline int kallsyms_show()
{
	unsigned int i;

	printk("    command list:%d\r\n", kallsyms_count);
	for (i = 0; i < kallsyms_count; i++) {
		printk("[%d]    %s   \r\n",i, kallsyms[i].name);
	}
	return 0;
}

int help()
{
	return kallsyms_show();
}

int d(int* addr, unsigned int count)
{
	unsigned int i = 0,j = 0;
	while(i < count)
	{
		printk("[0x%x] ",addr + i);
		for ( j=0; j<4 && i < count; j++, i++)
		{
			printk("%x ",addr[i]);
		}
		printk("\r\n");
	}
	return 0;
}

int m(int *addr, int value)
{
	addr  = (int *)ROUND_DOWN(addr, 4); /* 取4字节向下对齐 */
	*addr = value;
	return 0;
}

int change_port(int id)
{
	uart_unregister_ldisc(&g_console.ldisc);
	g_console.ldisc.id = id;
	uart_register_ldisc(&g_console.ldisc);
	return 0;
}