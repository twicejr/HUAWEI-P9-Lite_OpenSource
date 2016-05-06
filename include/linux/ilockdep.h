#ifndef _ILOCKDEP_H
#define _ILOCKDEP_H

#include <linux/kernel.h>

#ifdef CONFIG_ILOCKDEP
struct task_struct;
struct ilockdep_map {
	void *key;
	const char *name;
	unsigned int cpu;
	unsigned long ip;
};

struct ilockdep {
	void			*locking;
	const char		*locking_name;
	struct ilockdep_map     held_locks[CONFIG_DEBUG_ILOCKDEP_NUM];
	unsigned int            depth;
};


extern void ilockdep_acquired(struct ilockdep_map *dep,
	unsigned long ip, void *lock_addr);
extern void ilockdep_release(struct ilockdep_map *dep,
	unsigned long ip, void *lock_addr);
extern void ilockdep_acquire(struct ilockdep_map *dep,
	unsigned long ip, void *lock_addr);
extern void ilockdep_init(struct ilockdep *dep);
extern void ilockdep_clear_locking(struct task_struct *p);
extern void show_ilockdep_info(struct task_struct *t);

#define ILOCKDEP_CONTENDED(_lock, try, lock) \
do { \
	lock(_lock); \
	ilockdep_acquired(&(_lock)->idep_map, _RET_IP_, (void *)_lock); \
} while (0)

#else
# define ilockdep_acquired(l, i, a)	do { } while (0)
# define ilockdep_acquire(l, i, a)	do { } while (0)
# define ilockdep_release(l, i, a)	do { } while (0)
# define ilockdep_init(l)		do { } while (0)
# define ilockdep_clear_locking(p)	do { } while (0)
# define show_ilockdep_info(p)		do { } while (0)
#endif

#endif /*_ILOCKDEP_H*/
