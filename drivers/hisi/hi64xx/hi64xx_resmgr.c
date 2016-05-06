/*
 * hi64xx_resmgr.c -- resource manager for hi64xx codec
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/notifier.h>
#include <linux/wakelock.h>

#include <linux/hisi/hi64xx/hi64xx_resmgr.h>


enum pll_rel_state {
	REL_IDLE,
	REL_WAIT,
	REL_PENDING
};

#define PLL_LOCK_MAX_RETRY  5

struct hi64xx_resmgr_priv {
	struct hi64xx_resmgr resmgr;

	struct resmgr_config config;

	struct mutex pll_mutex;
	int pll_ref_count[PLL_MAX];
	enum hi64xx_pll_type curr_pll;
	enum hi64xx_pll_type reg_acc_pll;
	int reg_acc_ref_count;

	struct mutex micbias_mutex;
	int micbias_ref_count;

	struct mutex ibias_mutex;
	int ibias_ref_count;

	wait_queue_head_t pll_rel_wq;
	enum pll_rel_state pll_wait_rel[PLL_MAX];
	struct task_struct *pll_rel_thrd;
	struct wake_lock wake_lock;

	struct blocking_notifier_head notifier;

	struct snd_soc_codec *codec;
	struct hi_cdc_ctrl* cdc_ctrl;
	struct hi64xx_irq *irqmgr;
};


static void _dump_pll_state(struct hi64xx_resmgr_priv *priv)
{
	int i;

	pr_info("!=== pll state dump begin: ===\n");

	pr_info("current pll state: %d\n", priv->curr_pll);
	for (i = 0; i < priv->config.pll_num; i++)
		pr_info("pll[%d]: ref cnt - %d, wait ref state - %d\n", i,
			priv->pll_ref_count[i], priv->pll_wait_rel[i]);

	pr_info("register accessing pll: %d\n", priv->reg_acc_pll);
	pr_info("register accessing ref cnt: %d\n", priv->reg_acc_ref_count);

	pr_info("!=== pll state dump end ===\n");
}

static void _event_notify(struct hi64xx_resmgr_priv *priv,
		enum hi64xx_resmgr_event event, void* payload)
{
	unsigned long val = event;
	blocking_notifier_call_chain(&priv->notifier, val, payload);
}

static int _request_ibias(struct hi64xx_resmgr_priv *priv)
{
	mutex_lock(&priv->ibias_mutex);
	if (++priv->ibias_ref_count == 1) {
		hi_cdcctrl_enable_supply(priv->cdc_ctrl, CDC_SUP_ANLG, true);
		priv->config.enable_ibias(priv->codec);
	}
	mutex_unlock(&priv->ibias_mutex);

	return 0;
}

static int _release_ibias(struct hi64xx_resmgr_priv *priv)
{
	mutex_lock(&priv->ibias_mutex);
	if (priv->ibias_ref_count == 0) {
		pr_err("release ibias when reference counter is 0");
		mutex_unlock(&priv->ibias_mutex);
		return -EINVAL;
	}

	if (--priv->ibias_ref_count == 0) {
		priv->config.disable_ibias(priv->codec);
		hi_cdcctrl_enable_supply(priv->cdc_ctrl, CDC_SUP_ANLG, false);
	}
	mutex_unlock(&priv->ibias_mutex);

	return 0;
}

static int _request_micbias(struct hi64xx_resmgr_priv *priv)
{
	mutex_lock(&priv->micbias_mutex);
	if (++priv->micbias_ref_count == 1) {
		_request_ibias(priv);
		priv->config.enable_micbias(priv->codec);
	}
	mutex_unlock(&priv->micbias_mutex);

	return 0;
}

static irqreturn_t _pll_unlock_irq_handler(int irq, void *data)
{
	pr_warn("hi64xx: pll unlock irq received!!!\n");

	return IRQ_HANDLED;
}

static int _release_micbias(struct hi64xx_resmgr_priv *priv, bool force_release)
{
	mutex_lock(&priv->micbias_mutex);

	if (priv->micbias_ref_count == 0) {
		pr_err("release micbias when reference counter is 0");
		mutex_unlock(&priv->micbias_mutex);
		return -EINVAL;
	}

	if (force_release)
		priv->micbias_ref_count = 1;

	if (--priv->micbias_ref_count == 0) {
		priv->config.disable_micbias(priv->codec);
		_release_ibias(priv);
	}
	mutex_unlock(&priv->micbias_mutex);

	return 0;
}

static void _lock_pll(struct hi64xx_resmgr_priv *priv, enum hi64xx_pll_type pll_type)
{
	bool pll_locked = false;
	int retry = PLL_LOCK_MAX_RETRY;

	do {
		if (priv->config.pfn_pll_ctrls[pll_type].turn_on(priv->codec)) {
			pr_warn("try to turn on pll[%d] failed\n", pll_type);
			usleep_range(1000,1100);
			continue;
		}

		pll_locked = true;
		/* check pll lock state for some times */
		if (!priv->config.pfn_pll_ctrls[pll_type].is_locked(priv->codec)) {
			pr_warn("pll[%d] is not locked after turn on, retry time is %d\n", pll_type, (PLL_LOCK_MAX_RETRY - retry));
			pll_locked = false;
		}

		if (pll_locked)
			break;
		else {
			(void)priv->config.pfn_pll_ctrls[pll_type].turn_off(priv->codec);
			usleep_range(5000,5100);
		}

	} while(--retry);

	if (!pll_locked) {
		pr_err("failed to lock pll[%d]\n", pll_type);
		/* Anyway, turn on the pll to provide clock */
		priv->config.pfn_pll_ctrls[pll_type].turn_on(priv->codec);
	}

	if (priv->irqmgr)
		hi64xx_irq_enable_irq(priv->irqmgr, IRQ_PLL_UNLOCK);
}

static int _request_pll(struct hi64xx_resmgr_priv *priv, enum hi64xx_pll_type pll_type)
{
	struct pll_switch_event event;

	BUG_ON(pll_type < 0 || pll_type >= priv->config.pll_num);

	mutex_lock(&priv->pll_mutex);

	if (++priv->pll_ref_count[pll_type] == 1 && pll_type > priv->curr_pll) {
		event.from = priv->curr_pll;
		event.to = pll_type;
		_event_notify(priv, PRE_PLL_SWITCH, &event);

		if (priv->curr_pll == PLL_NONE) {
			_request_ibias(priv);
			hi_cdcctrl_enable_clk(priv->cdc_ctrl, CDC_MCLK, true);
		} else {
			if (priv->irqmgr)
				hi64xx_irq_disable_irq(priv->irqmgr, IRQ_PLL_UNLOCK);
			(void)priv->config.pfn_pll_ctrls[priv->curr_pll].turn_off(priv->codec);
		}

		_lock_pll(priv, pll_type);
		priv->curr_pll = pll_type;

		_event_notify(priv, POST_PLL_SWITCH, &event);
	}

	mutex_unlock(&priv->pll_mutex);

	return 0;
}

static int _release_pll(struct hi64xx_resmgr_priv *priv, enum hi64xx_pll_type pll_type)
{
	int i;
	struct pll_switch_event event;
	enum hi64xx_pll_type new_pll;

	BUG_ON(pll_type < 0 || pll_type >= priv->config.pll_num);

	mutex_lock(&priv->pll_mutex);

	if (priv->pll_ref_count[pll_type] == 0) {
		pr_err("release pll[%d] when reference counter is 0", pll_type);
		mutex_unlock(&priv->pll_mutex);
		return -EINVAL;
	}

	if (--priv->pll_ref_count[pll_type] == 0 && pll_type == priv->curr_pll) {
		new_pll = PLL_NONE;
		for (i = pll_type - 1; i >= 0; i--) {
			if (priv->pll_ref_count[i] > 0) {
				new_pll = i;
				break;
			}
		}

		event.from = pll_type;
		event.to = new_pll;
		_event_notify(priv, PRE_PLL_SWITCH, &event);

		if (priv->irqmgr)
			hi64xx_irq_disable_irq(priv->irqmgr, IRQ_PLL_UNLOCK);
		(void)priv->config.pfn_pll_ctrls[pll_type].turn_off(priv->codec);

		if (new_pll == PLL_NONE) {
			_release_ibias(priv);
			hi_cdcctrl_enable_clk(priv->cdc_ctrl, CDC_MCLK, false);
		} else {
			//(void)priv->config.pfn_pll_ctrls[new_pll].turn_on(priv->codec);
			_lock_pll(priv, new_pll);
		}
		priv->curr_pll = new_pll;

		_event_notify(priv, POST_PLL_SWITCH, &event);
	}

	mutex_unlock(&priv->pll_mutex);
	return 0;
}

static bool _is_pll_waiting_release(struct hi64xx_resmgr_priv* priv)
{
	int i;
	for (i = 0; i < PLL_MAX; i++) {
		if (priv->pll_wait_rel[i] != REL_IDLE)
			return true;
	}
	return false;
}

static int _pll_delay_release(struct hi64xx_resmgr_priv* priv, enum hi64xx_pll_type pll_type)
{
	spin_lock(&priv->pll_rel_wq.lock);

	if (priv->pll_wait_rel[pll_type] == REL_IDLE) {
		priv->pll_wait_rel[pll_type] = REL_WAIT;
		wake_up_locked(&priv->pll_rel_wq);
		spin_unlock(&priv->pll_rel_wq.lock);
	} else {
		if (priv->pll_wait_rel[pll_type] == REL_PENDING)
			priv->pll_wait_rel[pll_type] = REL_WAIT;
		spin_unlock(&priv->pll_rel_wq.lock);

		(void)_release_pll(priv, pll_type);
	}

	return 0;
}

static int _pll_delayed_release_thread(void *data)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)data;
	int i;
	bool pending = false;

	while (!kthread_should_stop()) {
		spin_lock(&priv->pll_rel_wq.lock);

		wait_event_interruptible_locked(priv->pll_rel_wq,
			_is_pll_waiting_release(priv) || kthread_should_stop());

		for (i = 0; i < PLL_MAX; i++) {
			if (priv->pll_wait_rel[i] == REL_WAIT) {
				priv->pll_wait_rel[i] = REL_PENDING;
				pending = true;
			}
		}
		spin_unlock(&priv->pll_rel_wq.lock);

		wake_lock(&priv->wake_lock);
		while (pending && !kthread_should_stop()) {
			msleep(200);
			pending = false;

			for (i = 0; i < PLL_MAX; i++) {
				spin_lock(&priv->pll_rel_wq.lock);
				if (priv->pll_wait_rel[i] == REL_PENDING) {
					priv->pll_wait_rel[i] = REL_IDLE;
					spin_unlock(&priv->pll_rel_wq.lock);
					_release_pll(priv, i);
				} else if (priv->pll_wait_rel[i] == REL_WAIT) {
					priv->pll_wait_rel[i] = REL_PENDING;
					pending = true;
					spin_unlock(&priv->pll_rel_wq.lock);
				} else {
					spin_unlock(&priv->pll_rel_wq.lock);
				}
			}
		}
		wake_unlock(&priv->wake_lock);
	}

	return 0;
}

int hi64xx_resmgr_init(struct snd_soc_codec *codec,
                       struct hi_cdc_ctrl *cdc_ctrl,
                       struct hi64xx_irq *irqmgr,
                       const struct resmgr_config *config,
                       struct hi64xx_resmgr **resmgr)
{
	int ret;

	struct hi64xx_resmgr_priv* priv
		= kzalloc(sizeof(struct hi64xx_resmgr_priv), GFP_KERNEL);
	if (!priv) {
		return -ENOMEM;
	}

	memcpy(&priv->config, config, sizeof(struct resmgr_config));
	priv->curr_pll = PLL_NONE;
	priv->reg_acc_pll = PLL_NONE;
	priv->codec = codec;
	priv->irqmgr = irqmgr;
	priv->cdc_ctrl = cdc_ctrl;

	mutex_init(&priv->pll_mutex);
	mutex_init(&priv->micbias_mutex);
	mutex_init(&priv->ibias_mutex);

	wake_lock_init(&priv->wake_lock, WAKE_LOCK_SUSPEND, "hi64xx-resmgr");

	BLOCKING_INIT_NOTIFIER_HEAD(&priv->notifier);

	init_waitqueue_head(&priv->pll_rel_wq);

	/* irgmgr may be NULL in UT test, so we need a check */
	if (irqmgr) {
		if (hi64xx_irq_request_irq(priv->irqmgr, IRQ_PLL_UNLOCK,
			_pll_unlock_irq_handler, "hi64xx-pll-unlock", priv))
			pr_warn("hi64xx_resmgr_init: request irq %d failed\n",
				IRQ_PLL_UNLOCK);

		hi64xx_irq_disable_irq(priv->irqmgr, IRQ_PLL_UNLOCK);
	}

	priv->pll_rel_thrd = kthread_run(_pll_delayed_release_thread,
				priv, "pll_delayed_release");
	if (IS_ERR(priv->pll_rel_thrd)) {
		pr_err("hi64xx_resmgr_init: fail to create thread\n");
		ret = -EIO;
		goto error_exit;
	}

	*resmgr = &priv->resmgr;

	return 0;

error_exit:
	if (priv->irqmgr)
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_PLL_UNLOCK, priv);
	if (priv)
		kfree(priv);
	return ret;
}
EXPORT_SYMBOL(hi64xx_resmgr_init);

void hi64xx_resmgr_deinit(struct hi64xx_resmgr *resmgr)
{

	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	if (priv == NULL)
		return;

	kthread_stop(priv->pll_rel_thrd);

	if (priv->irqmgr)
		hi64xx_irq_free_irq(priv->irqmgr, IRQ_PLL_UNLOCK, priv);

	mutex_destroy(&priv->pll_mutex);
	mutex_destroy(&priv->micbias_mutex);
	mutex_destroy(&priv->ibias_mutex);
	wake_lock_destroy(&priv->wake_lock);

	kfree(priv);
}
EXPORT_SYMBOL(hi64xx_resmgr_deinit);

enum hi64xx_pll_type _get_reg_acc_pll(
	struct hi64xx_resmgr_priv* priv,
	enum hi64xx_pll_type pll)
{
	enum hi64xx_pll_type ret = pll;

	mutex_lock(&priv->pll_mutex);

	if (priv->reg_acc_pll != PLL_NONE)
		ret = priv->reg_acc_pll;
	else
		if (priv->curr_pll != PLL_NONE)
			ret = priv->curr_pll;

	++priv->reg_acc_ref_count;
	priv->reg_acc_pll = ret;

	mutex_unlock(&priv->pll_mutex);

	return ret;
}

enum hi64xx_pll_type _put_reg_acc_pll(struct hi64xx_resmgr_priv* priv)
{
	enum hi64xx_pll_type ret = PLL_NONE;

	mutex_lock(&priv->pll_mutex);

	if (priv->reg_acc_pll == PLL_NONE) {
		pr_err("pll to release for register accessing should not be NONE\n");
		goto exit;
	}

	if (priv->reg_acc_ref_count == 0) {
		pr_err("ref count for register accessing is wrong\n");
		goto exit;
	}
	ret = priv->reg_acc_pll;
	if (--priv->reg_acc_ref_count == 0)
		priv->reg_acc_pll = PLL_NONE;

exit:
	mutex_unlock(&priv->pll_mutex);
	return ret;
}

int hi64xx_resmgr_request_reg_access(struct hi64xx_resmgr *resmgr,
                                     unsigned int reg_addr)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;
	int ret;

	enum hi64xx_pll_type req_pll =
		priv->config.pll_for_reg_access(priv->codec, reg_addr);

	if (req_pll == PLL_NONE) {
		return 0;
	}

	req_pll = _get_reg_acc_pll(priv, req_pll);
	ret = _request_pll(priv, req_pll);

	/* don't allow pll switch during register access */
	mutex_lock(&priv->pll_mutex);

	return ret;
}
EXPORT_SYMBOL(hi64xx_resmgr_request_reg_access);

int hi64xx_resmgr_release_reg_access(struct hi64xx_resmgr *resmgr,
                                     unsigned int reg_addr)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	enum hi64xx_pll_type req_pll =
		priv->config.pll_for_reg_access(priv->codec, reg_addr);

	if (req_pll == PLL_NONE) {
		return 0;
	}

	/* release the lock aquired in hi64xx_resmgr_request_reg_access */
	mutex_unlock(&priv->pll_mutex);

	req_pll = _put_reg_acc_pll(priv);
	if (req_pll == PLL_NONE) {
		return 0;
	}

	return _pll_delay_release(priv, req_pll);
}
EXPORT_SYMBOL(hi64xx_resmgr_release_reg_access);

int hi64xx_resmgr_request_pll(struct hi64xx_resmgr *resmgr,
                              enum hi64xx_pll_type pll_type)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return _request_pll(priv, pll_type);
}
EXPORT_SYMBOL(hi64xx_resmgr_request_pll);

int hi64xx_resmgr_release_pll(struct hi64xx_resmgr *resmgr,
                              enum hi64xx_pll_type pll_type)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return _release_pll(priv, pll_type);
}
EXPORT_SYMBOL(hi64xx_resmgr_release_pll);

int hi64xx_resmgr_request_micbias(struct hi64xx_resmgr *resmgr)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return _request_micbias(priv);
}
EXPORT_SYMBOL(hi64xx_resmgr_request_micbias);

int hi64xx_resmgr_release_micbias(struct hi64xx_resmgr *resmgr)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return _release_micbias(priv, false);
}
EXPORT_SYMBOL(hi64xx_resmgr_release_micbias);

int hi64xx_resmgr_force_release_micbias(struct hi64xx_resmgr *resmgr)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return _release_micbias(priv, true);
}
EXPORT_SYMBOL(hi64xx_resmgr_force_release_micbias);

int hi64xx_resmgr_register_notifier(struct hi64xx_resmgr *resmgr,
                                    struct notifier_block *nblock)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return blocking_notifier_chain_register(&priv->notifier, nblock);
}
EXPORT_SYMBOL(hi64xx_resmgr_register_notifier);

int hi64xx_resmgr_unregister_notifier(struct hi64xx_resmgr *resmgr,
                                    struct notifier_block *nblock)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;

	return blocking_notifier_chain_unregister(&priv->notifier, nblock);
}
EXPORT_SYMBOL(hi64xx_resmgr_unregister_notifier);

void hi64xx_resmgr_dump(struct hi64xx_resmgr *resmgr)
{
	struct hi64xx_resmgr_priv* priv =
		(struct hi64xx_resmgr_priv*)resmgr;
	_dump_pll_state(priv);
}
EXPORT_SYMBOL(hi64xx_resmgr_dump);

MODULE_DESCRIPTION("hi64xx resouce manager");
MODULE_AUTHOR("dingqing <dingqing@hisilicon.com>");
MODULE_LICENSE("GPL");
