/*
 *
 * arch/arm/mach-k3v2/clock.c
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */

#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/hardirq.h>
#include <asm/clkdev.h>
#include <mach/clock.h>


static DEFINE_MUTEX(clock_list_lock);
static LIST_HEAD(clocks);

/*
 * all the clocks' cansleep haven't been set, the lock is used as
 * spin_lock_irqsave instead of mutex_lock
 */
#define clk_lock_save(c, flags)						\
	do {								\
		spin_lock_irqsave(&c->spinlock, flags);			\
	} while (0)

#define clk_unlock_restore(c, flags)					\
	do {								\
		spin_unlock_irqrestore(&c->spinlock, flags);		\
	} while (0)

static inline void clk_lock_init(struct clk *c)
{
	spin_lock_init(&c->spinlock);
}

struct clk *k3v2_get_clock_by_name(const char *name)
{
	struct clk *c;
	struct clk *ret = NULL;

#ifdef CONFIG_DEBUG_MUTEX_ERROR
	WARN(in_interrupt(), 
		KERN_ERR "ERROR: MUTEX used in interrupt context! preempt_count = 0x%x, func: %s, line: %d\n",
		preempt_count(), __func__, __LINE__);
#endif

	mutex_lock(&clock_list_lock);
	list_for_each_entry(c, &clocks, node) {
		if (strcmp(c->name, name) == 0) {
			ret = c;
			break;
		}
	}

	mutex_unlock(&clock_list_lock);

	return ret;
}

/* Must be called with clk_lock(c) held */
unsigned long clk_get_rate_locked(struct clk *c)
{
	return c->rate;
}

unsigned long clk_get_rate(struct clk *c)
{
	unsigned long flags;
	unsigned long rate;

	clk_lock_save(c, flags);
	rate = c->rate;

	clk_unlock_restore(c, flags);

	return rate;
}
EXPORT_SYMBOL(clk_get_rate);

void clk_init(struct clk *c)
{
	clk_lock_init(c);

	if (c->ops && c->ops->init)
		c->ops->init(c);

	if (!c->ops || !c->ops->enable
				|| !c->enable_reg) {

		c->refcnt++;
		c->set = true;

		if (c->parent)
			c->state = c->parent->state;
		else
			c->state = ON;
	}

	mutex_lock(&clock_list_lock);
	list_add(&c->node, &clocks);
	mutex_unlock(&clock_list_lock);
}

int clk_enable(struct clk *c)
{

#if 1
	int ret = 0;

	unsigned long flags;

	clk_lock_save(c, flags);

	/* if c->refcnt == 0,clk hasn't been enabled, shoud enable if ,else just refcnt ++ */
	if (c->refcnt == 0) {
		if (c->parent) {
			ret = clk_enable(c->parent); /* enable parent */
			if (ret) {
				WARN(1, "enable clock:%s failed", c->name);
				goto out;
			}
		}

		if (c->ops && c->ops->enable) {
			ret = c->ops->enable(c);

			/* if enable faild ,disable the parent */
			if (ret) {
				if (c->parent)
					clk_disable(c->parent);

				WARN(1, "enable clock:%s failed", c->name);
				goto out;
			}
		}
		c->state = ON;
		c->set = true;
	}
	c->refcnt++;

out:
	clk_unlock_restore(c, flags);

	return ret;
#endif
	return 0;
}
EXPORT_SYMBOL(clk_enable);

void clk_disable(struct clk *c)
{

#if 1
	unsigned long flags;
	int ret = 0;

	clk_lock_save(c, flags);
	if (c->refcnt == 0) {
		WARN(1, "Attempting to disable clock %s with refcnt 0",
			c->name);
		clk_unlock_restore(c, flags);
		return;
	}

	if (c->refcnt == 1) {
		if (c->ops && c->ops->disable)
			ret = c->ops->disable(c);

		/* if disable faild , go to out */
		if (ret) {
			WARN(1, "disable clock:%s failed", c->name);
			goto out;
		}

		if (c->parent)
			clk_disable(c->parent);

		c->state = OFF;
	}
	c->refcnt--;

out:
	clk_unlock_restore(c, flags);
#endif
	return ;
}
EXPORT_SYMBOL(clk_disable);

int clk_set_parent(struct clk *c, struct clk *parent)
{
	int ret = 0;
	unsigned long flags;


	clk_lock_save(c, flags);
	if (!c->ops || !c->ops->set_parent) {
		ret = -ENOSYS;
		goto out;
	}
	ret = c->ops->set_parent(c, parent);

out:
	clk_unlock_restore(c, flags);

	return ret;
}
EXPORT_SYMBOL(clk_set_parent);

struct clk *clk_get_parent(struct clk *c)
{

	return c->parent;
}
EXPORT_SYMBOL(clk_get_parent);

int clk_set_rate(struct clk *c, unsigned long rate)
{

#if 1
	int ret = 0;
	unsigned long flags;
	unsigned long old_rate;
	long new_rate;

	clk_lock_save(c, flags);
	if (!c->ops || !c->ops->set_rate) {
		ret = -ENOSYS;
		goto out;
	}

	old_rate = clk_get_rate_locked(c);

	if (rate > c->max_rate)
		rate = c->max_rate;

	if (c->ops && c->ops->round_rate) {
		new_rate = c->ops->round_rate(c, rate);

		if (new_rate < 0) {
			ret = new_rate;
			goto out;
		}

		rate = new_rate;
	}

	/*printk("will call k3v2_set_rate\n");*/

	ret = c->ops->set_rate(c, rate);
	if (ret)
		goto out;

out:
	clk_unlock_restore(c, flags);

	return ret;
#endif
	return 0;
}
EXPORT_SYMBOL(clk_set_rate);

long clk_round_rate(struct clk *c, unsigned long rate)
{
	unsigned long flags;
	long ret;


	clk_lock_save(c, flags);
	if (!c->ops || !c->ops->round_rate) {
		ret = -ENOSYS;
		goto out;
	}

	if (rate > c->max_rate)
		rate = c->max_rate;

	ret = c->ops->round_rate(c, rate);

out:
	clk_unlock_restore(c, flags);

	return ret;
}
EXPORT_SYMBOL(clk_round_rate);

static int k3v2_clk_init_one_from_table(struct k3v2_clk_init_table *table)
{
	struct clk *c;
	struct clk *p;

	int ret = 0;

	c = k3v2_get_clock_by_name(table->name);

	if (!c) {
		pr_warning("Unable to initialize clock %s\n",
			table->name);
		return -ENODEV;
	}

	if (table->parent) {
		p = k3v2_get_clock_by_name(table->parent);
		if (!p) {
			pr_warning("Unable to find parent %s of clock %s\n",
				table->parent, table->name);
			return -ENODEV;
		}

		if (c->parent != p) {
			ret = clk_set_parent(c, p);
			if (ret) {
				pr_warning("Unable to set parent %s of clock %s: %d\n",
					table->parent, table->name, ret);
				return -EINVAL;
			}
		}
	}

	if (table->rate) {
		ret = clk_set_rate(c, table->rate);
		if (ret) {
			pr_warning("Unable to set clock %s to rate %lu: %d\n",
				table->name, table->rate, ret);
			return -EINVAL;
		}
	}

	if (table->enabled) {
		ret = clk_enable(c);
		if (ret) {
			pr_warning("Unable to enable clock %s: %d\n",
				table->name, ret);
			return -EINVAL;
		}
	} else {
		if (c->refcnt == 0) {
			ret = clk_enable(c);
			if (ret) {
				pr_warning("Unable to enable clock %s: %d\n",
					table->name, ret);
				return -EINVAL;
			}

			clk_disable(c);
		}
	}

	return 0;
}

void k3v2_clk_init_from_table(struct k3v2_clk_init_table *table)
{

		for (; table->name; table++) {
				k3v2_clk_init_one_from_table(table);
		}
}
EXPORT_SYMBOL(k3v2_clk_init_from_table);


void __init k3v2_init_clock(void)
{

	k3v2_init_clocks();
}

#ifdef CONFIG_DEBUG_FS

/*
 * Attempt to lock all the clocks that are marked cansleep
 * Must be called with irqs enabled
 */
char *clk_enabled_check(struct clk *c)
{
	char *result = NULL;


	if (c->ops && c->ops->check_enreg)
		result = c->ops->check_enreg(c);

	return result;
}

char *clk_source_check(struct clk *c)
{
	char *result = NULL;


	if (c->ops && c->ops->check_selreg)
		result = c->ops->check_selreg(c);

	return result;
}

char *clk_rate_check(struct clk *c)
{
	char *result = NULL;


	if (c->ops && c->ops->check_divreg)
		result = c->ops->check_divreg(c);

	return result;
}

/*
 * Attempt to lock all the clocks that are not marked cansleep
 * Must be called with irqs disabled
 */
static int __clk_lock_all_spinlocks(void)
{
	struct clk *c;


	list_for_each_entry(c, &clocks, node)
	if (!spin_trylock(&c->spinlock))
			goto unlock_spinlocks;

	return 0;

unlock_spinlocks:
	list_for_each_entry_continue_reverse(c, &clocks, node)
		spin_unlock(&c->spinlock);

	return -EAGAIN;
}


static void __clk_unlock_all_spinlocks(void)
{
	struct clk *c;


	list_for_each_entry_reverse(c, &clocks, node)
		spin_unlock(&c->spinlock);
}

/*
 * This function retries until it can take all locks, and may take
 * an arbitrarily long time to complete.
 * Must be called with irqs enabled, returns with irqs disabled
 * Must be called with clock_list_lock held
 */
static void clk_lock_all(void)
{
	int ret;

retry:
	local_irq_disable();

	ret = __clk_lock_all_spinlocks();
	if (ret)
		goto failed_spinlocks;

	/* All locks taken successfully, return */
	return;

failed_spinlocks:
	local_irq_enable();
	msleep(20);

	goto retry;
}

/*
 * Unlocks all clocks after a clk_lock_all
 * Must be called with irqs disabled, returns with irqs enabled
 * Must be called with clock_list_lock held
 */
static void clk_unlock_all(void)
{

	__clk_unlock_all_spinlocks();

	local_irq_enable();
}

static struct dentry *clk_debugfs_root;

static void clock_tree_show_one(struct seq_file *s, struct clk *c, int level)
{
	struct clk *child;
	const char *state = "uninit";

	if ((c->state == ON) || (c->refcnt > 0))
		state = "on";
	else if (c->state == OFF)
		state = "off";

	if (c->parent) {
		seq_printf(s, "%*s%c%c%-*s %-6s %-3d %-10lu %-8s %-8s %-8s", level * 3 + 1, "",
			c->rate > c->max_rate ? '!' : ' ',
			!c->set ? '*' : ' ',
			30 - level * 3, c->name,
			state, c->refcnt, c->rate,
			clk_enabled_check(c),
			clk_source_check(c),
			clk_rate_check(c));

		if (c->parent->state == ON)
			state = "on";
		else if (c->parent->state == OFF)
			state = "off";

		seq_printf(s, "%*s%c%c%-*s %-6s %-3d\n",
			level * 3 + 1, "",
			c->parent->rate > c->parent->max_rate ? '!' : ' ',
			!c->parent->set ? '*' : ' ',
			30 - level * 3, c->parent->name,
			state, c->parent->refcnt);
	} else {
		seq_printf(s, "%*s%c%c%-*s %-6s %-3d %-10lu %-8s %-8s %-8s\n", level * 3 + 1, "",
			c->rate > c->max_rate ? '!' : ' ',
			!c->set ? '*' : ' ',
			30 - level * 3, c->name,
			state, c->refcnt, c->rate,
			clk_enabled_check(c),
			clk_source_check(c),
			clk_rate_check(c));
	}

	list_for_each_entry(child, &clocks, node) {
		if (child->parent != c)
			continue;

		clock_tree_show_one(s, child, level + 1);
	}
}

static int clock_tree_show(struct seq_file *s, void *data)
{
	struct clk *c;

	seq_printf(s, "%-*s %-*s %-6s %-3s %-8s %-10s %-8s %-8s %-8s",
		1, "", 30, "  clock", "state", "ref", "   ", "rate", "en_reg",
		"sel_reg", "div_reg");

	seq_printf(s, "%*s%-*s %-6s %-3s %-8s %-10s\n",
			1, "", 30, "  parent", "state", "ref", "   ", "rate");
	seq_printf(s, "-----------------------------------------"
			"-----------------------------------------------\n");

	mutex_lock(&clock_list_lock);
	clk_lock_all();
	list_for_each_entry(c, &clocks, node) {
		clock_tree_show_one(s, c, 0);
	}

	clk_unlock_all();

	mutex_unlock(&clock_list_lock);

	return 0;
}

static int clock_tree_open(struct inode *inode, struct file *file)
{

	return single_open(file, clock_tree_show, inode->i_private);
}

static const struct file_operations clock_tree_fops = {
	.open		= clock_tree_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int possible_parents_show(struct seq_file *s, void *data)
{
	struct clk *c = s->private;

	int i;

	for (i = 0; c->sel_parents[i].sel_parent; i++) {
		char *first = (i == 0) ? "" : " ";
		seq_printf(s, "%s%s", first, c->sel_parents[i].sel_parent->name);
	}
	seq_printf(s, "\n");

	return 0;
}

static int possible_parents_open(struct inode *inode, struct file *file)
{

	return single_open(file, possible_parents_show, inode->i_private);
}

static const struct file_operations possible_parents_fops = {
	.open		= possible_parents_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int clk_debugfs_register_one(struct clk *c)
{
	struct dentry *d, *child, *child_tmp;


	d = debugfs_create_dir(c->name, clk_debugfs_root);
	if (!d)
		return -ENOMEM;
	c->dent = d;

	d = debugfs_create_u8("refcnt", S_IRUGO, c->dent, (u8 *)&c->refcnt);
	if (!d)
		goto err_out;

	d = debugfs_create_u32("rate", S_IRUGO, c->dent, (u32 *)&c->rate);
	if (!d)
		goto err_out;

	d = debugfs_create_x32("parent", S_IRUGO, c->dent,
			(u32 *)&c->parent->name);
	if (!d)
		goto err_out;

	d = debugfs_create_u8("parent_refcnt", S_IRUGO, c->dent,
			(u8 *)&c->parent->refcnt);
	if (!d)
		goto err_out;

	if (c->sel_parents) {
		d = debugfs_create_file("possible_parents", S_IRUGO, c->dent,
				c, &possible_parents_fops);
		if (!d)
			goto err_out;
	}

	return 0;

err_out:
	d = c->dent;
	list_for_each_entry_safe(child, child_tmp, &d->d_subdirs, d_u.d_child)
		debugfs_remove(child);

	debugfs_remove(c->dent);

	return -ENOMEM;
}

static int clk_debugfs_register(struct clk *c)
{
	int err;
	struct clk *pa = c->parent;


	if (pa && !pa->dent) {
		err = clk_debugfs_register(pa);
		if (err)
			return err;
	}

	if (!c->dent) {
		err = clk_debugfs_register_one(c);
		if (err)
			return err;
	}

	return 0;
}

static int __init clk_debugfs_init(void)
{
	struct clk *c;
	struct dentry *d;
	int err = -ENOMEM;

	d = debugfs_create_dir("clock", NULL);
	if (!d)
		return -ENOMEM;
	clk_debugfs_root = d;

	d = debugfs_create_file("clock_tree", S_IRUGO, clk_debugfs_root,
			NULL, &clock_tree_fops);
	if (!d)
		goto err_out;

	list_for_each_entry(c, &clocks, node) {
		err = clk_debugfs_register(c);
		if (err)
			goto err_out;
	}

	return 0;
err_out:
	debugfs_remove_recursive(clk_debugfs_root);

	return err;
}

late_initcall(clk_debugfs_init);

#endif
