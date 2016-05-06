#ifndef _LOW_MEM_INJECT_H
#define _LOW_MEM_INJECT_H

enum{
	e_low_mem_setting_enable = 1,
	e_low_mem_setting_inject_size,
}t_cmd;

typedef struct low_mem_inject_flags{
	unsigned enabled : 1;
	unsigned verified : 1;
}t_flags;

typedef struct low_mem_inject_node{
	t_flags flags;
	unsigned long int inject_byte;
}t_low_mem_inject;

#define TEST_MAGIC 'x'
#define TEST_MAX_NR sizeof(t_cmd)
#define LOW_MEM_SETTING_ENABLE _IO(TEST_MAGIC, e_low_mem_setting_enable)
#define LOW_MEM_SETTING_INJECT_SIZE _IO(TEST_MAGIC, e_low_mem_setting_inject_size)

#endif
