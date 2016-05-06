/*
 *  linux/drivers/mmc/core/lock.h
 *
 *  Copyright 2006 Instituto Nokia de Tecnologia (INdT), All Rights Reserved.
 *  Copyright 2007 Pierre Ossman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _MMC_CORE_LOCK_H
#define _MMC_CORE_LOCK_H

#ifdef CONFIG_MMC_PASSWORDS

/* core-internal data */
struct mmc_key_payload {
	struct rcu_head	rcu;		/* RCU destructor */
	unsigned short	datalen;	/* length of this data */
	char		data[0];	/* actual data */
};

int mmc_register_key_type(void);
void mmc_unregister_key_type(void);

int mmc_lock_add_sysfs(struct mmc_card *card);
void mmc_lock_remove_sysfs(struct mmc_card *card);

#else

static inline int mmc_register_key_type(void)
{
	return 0;
}

static inline void mmc_unregister_key_type(void)
{
}

static inline int mmc_lock_add_sysfs(struct mmc_card *card)
{
	return 0;
}

static inline void mmc_lock_remove_sysfs(struct mmc_card *card)
{
}

#endif

#endif 
