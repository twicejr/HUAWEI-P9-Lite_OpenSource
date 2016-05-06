#include <linux/ilockdep.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/module.h>

#define FORMAT_LOCKING "locking:\n%-10p %-16s\t\n"
#define FORMAT_LOCKED "%-10p %-16s %-2d [<%p>] %pS\t\n"

void ilockdep_init(struct ilockdep *dep)
{
	memset(dep, 0, sizeof(struct ilockdep));
	return;
}

void ilockdep_clear_locking(struct task_struct *p)
{
	p->ilockdep_lock.locking = NULL;
	p->ilockdep_lock.locking_name = NULL;
	return;
}

void ilockdep_acquire(struct ilockdep_map *lock,
	unsigned long ip, void *lock_addr)
{
	current->ilockdep_lock.locking_name = lock->name;
	current->ilockdep_lock.locking = lock_addr;
	return;
}

void ilockdep_acquired(struct ilockdep_map *lock,
	unsigned long ip, void *lock_addr)
{
	unsigned int i;
	unsigned long flags;
	struct task_struct *curr = current;

	raw_local_irq_save(flags);
	ilockdep_clear_locking(curr);
	if (curr->ilockdep_lock.depth >= CONFIG_DEBUG_ILOCKDEP_NUM) {
		raw_local_irq_restore(flags);
		return;
	}
	for (i = 0; i < CONFIG_DEBUG_ILOCKDEP_NUM; i++) {
		if (curr->ilockdep_lock.held_locks[i].key == NULL) {
			curr->ilockdep_lock.held_locks[i].key = lock_addr;
			curr->ilockdep_lock.held_locks[i].cpu
				= smp_processor_id();
			curr->ilockdep_lock.held_locks[i].name = lock->name;
			curr->ilockdep_lock.held_locks[i].ip = ip;
			break;
		}
	}
	curr->ilockdep_lock.depth++;
	raw_local_irq_restore(flags);
	return;
}

void ilockdep_release(struct ilockdep_map *lock,
	unsigned long ip, void *lock_addr)
{
	unsigned int i;
	unsigned long flags;
	struct task_struct *curr = current;

	raw_local_irq_save(flags);
	for (i = 0; i < CONFIG_DEBUG_ILOCKDEP_NUM; i++) {
		if (curr->ilockdep_lock.held_locks[i].key == lock_addr) {
			curr->ilockdep_lock.held_locks[i].key = NULL;
			curr->ilockdep_lock.held_locks[i].cpu =
				num_possible_cpus() + 1;
			curr->ilockdep_lock.held_locks[i].name = NULL;
			curr->ilockdep_lock.held_locks[i].ip = 0;
			curr->ilockdep_lock.depth--;
			break;
		}
	}
	raw_local_irq_restore(flags);
	return;
}

void show_ilockdep_info(struct task_struct *t)
{
	unsigned int i;
	struct ilockdep *ilockdep_lock = &t->ilockdep_lock;

	if (ilockdep_lock == NULL) {
		pr_err("---show_ilockdep_info: ilockdep_lock NULL.\n");
		return;
	}

	if (ilockdep_lock->locking != NULL)
		pr_err(FORMAT_LOCKING, (char *)ilockdep_lock->locking,
			ilockdep_lock->locking_name);

	if (ilockdep_lock->depth > 0) {
		pr_err("---show_ilockdep_info: depth < 0.\n");
		return;
	}
	pr_err("locked:\n");
	for (i = 0; i < CONFIG_DEBUG_ILOCKDEP_NUM; i++) {
		if (ilockdep_lock->held_locks[i].key != NULL)
			printk(FORMAT_LOCKED,
				(char *)ilockdep_lock->held_locks[i].key,
			ilockdep_lock->held_locks[i].name,
			ilockdep_lock->held_locks[i].cpu,
			(char *)ilockdep_lock->held_locks[i].ip,
			(char *)ilockdep_lock->held_locks[i].ip);
	}
}
EXPORT_SYMBOL(show_ilockdep_info);
