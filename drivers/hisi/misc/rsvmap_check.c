#include <linux/module.h>
#include <linux/types.h>
#include <linux/of_fdt.h>
#include <linux/init.h>
#include <linux/timer.h>

extern struct boot_param_header *initial_boot_params;
static struct timer_list delay_timer;

static void mem_rsvmap_exp_handle(unsigned long data)
{
	del_timer(&delay_timer);
	panic("reserved memory check fail\n");
	return;
}

static int __init mem_rsvmap_init_module(void)
{
	int i = 0, j = 0;
	u64 *reserve_map;
	u64 base, size;

	init_timer(&delay_timer);
	delay_timer.function = mem_rsvmap_exp_handle;
	delay_timer.expires = jiffies + HZ * 60;

	reserve_map = ((void *)initial_boot_params) +
		be32_to_cpu(initial_boot_params->off_mem_rsvmap);

	while (1) {
		base = be64_to_cpup(reserve_map + i);
		size = be64_to_cpup(reserve_map + i + 1);

		if (!size)
			goto success;

		i += 2;

		j = i;
		while (1) {
			u64 base_next, size_next;

			base_next = be64_to_cpup(reserve_map + j);
			size_next = be64_to_cpup(reserve_map + j + 1);

			if (!size_next)
				break;

			j += 2;

			if (base_next >= (base + size))
				continue;

			if (base >= (base_next + size_next))
				continue;

			goto error;
		}
	}

error:
	printk(KERN_ERR" Error: resvered memory overlapping!\n");
	add_timer(&delay_timer);
success:
	return 0;
}

static void __exit mem_rsvmap_exit_module(void)
{
	return;
}

module_init(mem_rsvmap_init_module);
module_exit(mem_rsvmap_exit_module);
MODULE_LICENSE("GPL");
