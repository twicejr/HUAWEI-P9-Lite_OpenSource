#ifndef __SPINLOCKAMP_H
#define __SPINLOCKAMP_H

extern void raw_spin_lock(volatile unsigned int *);
extern void raw_spin_unlock(volatile unsigned int *);
extern int raw_spin_trylock(volatile unsigned int *);


#endif
