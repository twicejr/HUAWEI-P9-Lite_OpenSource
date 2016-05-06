/*
 *  linux/drivers/mmc/core/lock.h
 *
 *  Copyright 2006 Instituto Nokia de Tecnologia (INdT), All Rights Reserved.
 *  Copyright 2007 Pierre Ossman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * MMC password key handling.
 */
#include <linux/slab.h>

#include <linux/device.h>
#include <linux/key-type.h>
#include <linux/err.h>

#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>

#include "sysfs.h"
#include "mmc_ops.h"
#include "lock.h"
#include "sd.h"
#include "sd_ops.h"
#include "core.h"

#define DEBUG_PWD 0

#define MAX_KEY_SIZE		(48)
#define MAX_COMMAND_SIZE	(16)
#define MMC_SUCCESS				(0)
#define MMC_ERROR				(1)

#define E_NOSUPPORT        (0x7001)
#define E_CARDERROR        (0x7002)

#define dev_to_mmc_card(d)	container_of(d, struct mmc_card, dev)
extern int mmc_sd_init_uhs_card(struct mmc_card *card);

static ssize_t mmc_lockable_show(struct device *dev, struct device_attribute *att, char *buf)
{
        struct mmc_card *card = dev_to_mmc_card(dev);

        //return sprintf(buf, "%slocked\n", mmc_card_locked(card) ? "" : "un");
        if(mmc_card_encrypt(card))
                return snprintf(buf,sizeof("unlocked\n"), "%slocked\n", mmc_card_locked(card) ? "" : "un");
        else
                return snprintf(buf, sizeof("none\n"), "none\n");
}

static void save_unlock_password(struct mmc_card* card,u8* key_buffer,int key_len)
{
        if(!card)
                return;

        //max password (16) + 0xff 0xff
        if(key_len > 18) {
                printk("[SDLOCK] %s password too long \n",__func__);
                return;
        }
        memset(card->unlock_pwd,0,20);
        card->unlock_pwd[0] = (u8)key_len;
        memcpy(card->unlock_pwd+1 , key_buffer , key_len);
}

static void clear_unlock_password(struct mmc_card* card)
{
        memset(card->unlock_pwd,0,20);
}

static int extract(const char *data, u8 *command, u8 *buffer, int *plen)
{
        int i=0;
        if (!data || !command || !buffer || !plen) {
                return -MMC_ERROR;
        }

        //parse command
        while(*data != '/' && *data != '\0') {
                *command++ = *data++;
                //Prevent cross-border array
                i++;
                if(i>=MAX_COMMAND_SIZE) {
                        return -MMC_ERROR;
                }
        }

        if (*data == '\0') {
                *command++ = '\0';
                *plen = 0;
                return MMC_SUCCESS;
        }

        //parse command data
        data++;  //to skip "/"
        i = 0;

        while(*data != '\0') {
                *buffer++ = *data++;
                i++;
                //Prevent cross-border array ,Reserved 2 bytes
                if(i+2 >= MAX_KEY_SIZE) {
                        return -MMC_ERROR;
                }
        }

        //set end chars to data buffer
        *buffer++ = 0xFF;
        *buffer++ = 0xFF;

        *plen = i+2;

        return MMC_SUCCESS;
}

static void check_status(struct mmc_card *card)
{
#if 0
        int status;
        int err;
        err = mmc_send_status(card, &status);
        if (err) {
                printk("[SDLOCK] %s mmc_send_status failed \n",__func__);
        } else {
                printk("[SDLOCK] %s mmc_send_status statuc (%x) \n",__func__,status);
        }
#endif
}

static int mmc_lock_sd_init_card(struct mmc_card *card,bool binit)
{
        u32 cid[4];
        u32 rocr = 0;
        int card_is_null = 0;
        struct mmc_host  *host;
        int err;

        if (NULL == card || NULL == card->host) {
                printk("%s: sd card host is null\n", __func__);
                return -EINVAL;
        }
        host = card->host;

        if(binit) {
                err = mmc_sd_get_cid(host, card->ocr, cid, &rocr);
                if (err) {
                        printk("%s: sd get cid error, err=%d\n", __func__, err);
                        return err;
                }

                if (!mmc_host_is_spi(host)) {
                        err = mmc_send_relative_addr(host, &card->rca);
                        if (err) {
                                printk("%s: send relative addr error, err=%d\n", __func__, err);
                                return err;
                        }

                        mmc_set_bus_mode(host, MMC_BUSMODE_PUSHPULL);
                }

                if (!mmc_host_is_spi(host)) {
                        err = mmc_select_card(card);
                        if (err) {
                                printk("%s: sd select card error, err=%d\n", __func__, err);
                                return err;
                        }
                }
        }
        check_status(card);
        err = mmc_sd_setup_card(host, card, false);
        if (err) {
                printk("%s: sd setup card error, err=%d\n", __func__, err);
                return err;
        }

        /* Initialization sequence for UHS-I cards */
        if (true == card->swith_voltage) {
                err = mmc_sd_init_uhs_card(card);
                if (err) {
                        printk("%s: sd init uhs card error, err=%d\n", __func__, err);
                        return err;
                }

                /* Card is an ultra-high-speed card */
                mmc_sd_card_set_uhs(card);

                /*
                 * Since initialization is now complete, enable preset
                 * value registers for UHS-I cards.
                 */
		// FIXME
//                if (host->ops->enable_preset_value)
//                        host->ops->enable_preset_value(host, true);
        } else {
                /*
                 * Attempt to change to high-speed (if supported)
                 */
                err = mmc_sd_switch_hs(card);
                if (err > 0)
                        mmc_sd_go_highspeed(card);
                else if (err)
                {
                        printk("%s mmc_sd_switch_hs err=%d\n",__func__,err);
                        return err;
                }
                /*
                 * Set bus speed.
                 */
                mmc_set_clock(host, mmc_sd_get_max_clock(card));

                if (!host->card) {
                        host->card = card;
                        card_is_null = 1;
                }
                if (card->host->ops->execute_tuning)
                        card->host->ops->execute_tuning(card->host, MMC_SEND_TUNING_BLOCK);

                /*
                 * Switch to wider bus (if supported).
                 */
                if ((host->caps & MMC_CAP_4_BIT_DATA) &&
                    (card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
                        err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
                        if (err) {
                                if (card_is_null) {
                                        printk("%s: card is null\n", __func__);
                                        host->card = NULL;
                                        return err;
                                }

                        }
                        mmc_set_bus_width(host, MMC_BUS_WIDTH_4);
                }
        }

        return MMC_SUCCESS;
}

/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_reset_device(struct device* dev)
{
        int ret;
        if( !dev)
                return -EINVAL;

        device_release_driver(dev);
        ret = device_attach(dev);
        if(!ret) {
                printk("%s attach failed %d \n",__func__, ret);
                return -EINVAL;
        }
        return MMC_SUCCESS;
}


/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_reinit_full(struct mmc_card* card , struct device* dev)
{
        int ret;
        if(!card || !dev) {
                if (card != NULL){
                    mmc_release_host(card->host);
                }
                return -EINVAL;
        }

        printk("mmc_lock_sd_init_card() true when sd_reinit\n");
        ret = mmc_lock_sd_init_card(card,true);
        if (ret) {
                printk("%s: reinit error (%d) \n", __func__,ret);
                mmc_release_host(card->host);
                ret = sd_reset_device(dev);
                return -EINVAL;
        }

        mmc_release_host(card->host);
        ret = sd_reset_device(dev);

        return ret;
}


/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_reinit(struct mmc_card* card , struct device* dev)
{
        int ret;
        if(!card || !dev) {
		if (card != NULL){
			mmc_release_host(card->host);
		}
		return -EINVAL;
        }

        printk("mmc_lock_sd_init_card() false when sd_reinit\n");
        ret = mmc_lock_sd_init_card(card,false);
        if (ret) {
                printk("%s: reinit error (%d) \n", __func__,ret);
                mmc_release_host(card->host);
                ret = sd_reset_device(dev);
                return -EINVAL;
        }

        mmc_release_host(card->host);
        ret = sd_reset_device(dev);

        return ret;
}
/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_erase_reinit(struct mmc_card* card , struct device* dev)
{
        int ret;
        int err = MMC_SUCCESS;

        if(!card || !dev) {
		if (card != NULL){
			mmc_release_host(card->host);
		}
		return -EINVAL;
        }


        mmc_power_off(card->host);
        /* Wait at least 200 ms according to SD spec */
        mmc_delay(200);
        mmc_power_up(card->host, card->ocr);

        if (card->host->ops->sd_lock_reset)
                card->host->ops->sd_lock_reset(card->host);

        ret = mmc_lock_sd_init_card(card,true);
        if (ret) {
                printk("[SDLOCK]%s: reinit error (%d) \n", __func__,ret);
                err = ret;
        }

        mmc_release_host(card->host);

        ret = sd_reset_device(dev);
        if(ret) {
                printk("[SDLOCK]%s sd_reset_device (%d)\n",__func__,ret);
                err = ret;
        }
#if 0
        //some sd card need suspend - resume , format ok
        ret = mmc_power_save_host(card->host);
        if(ret) {
                printk("[SDLOCK]%s mmc_power_save_host (%d)\n",__func__,ret);
                err = ret;
        }
        mdelay(500);
        ret = mmc_power_restore_host(card->host);
        if(ret) {
                printk("[SDLOCK]%s mmc_power_restore_host (%d)\n",__func__,ret);
                err = ret;
        }

        if(err) {
                ret = err;
        }
#endif


        return ret;
}

/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_lock_do_assign(struct mmc_card *card,struct device *dev,u8* key_buf,int key_len)
{
        int ret;

        if(!card || !dev || !key_buf) {
                return -EINVAL;
        }

        //max password 16byte, key_buf max = max password + 0xff + 0xff (18byte)
        if(key_len > 18) {
                return -EINVAL;
        }

        if(!(card->csd.cmdclass & CCC_LOCK_CARD))
        {
                printk("[SDLOCK] this card don't support LOCK CARD Function from cmdclass!\n");
                return -E_NOSUPPORT;
        }
        else
        {
                printk("[SDLOCK] this card support LOCK CARD Function from cmdclass!\n");
        }

        mmc_claim_host(card->host);
        //set password and lock sd card
        ret = mmc_lock_unlock_by_buf(card,  key_buf,key_len, MMC_LOCK_MODE_LOCK | MMC_LOCK_MODE_SET_PWD);
        if(ret) {
                printk("[SDLOCK] %s lock failed (%d) \r\n",__func__,ret);
                ret = -E_NOSUPPORT;
                mmc_release_host(card->host);
                return ret;
        }

        //unlock sd card
        ret = mmc_lock_unlock_by_buf(card,  key_buf,key_len,MMC_LOCK_MODE_UNLOCK);
        printk("[SDLOCK] after unlock sd card,ret=%d mmc_card_locked(card)=0x%x!\n",ret, mmc_card_locked(card));
        if(ret || mmc_card_locked(card)) {
                printk("[SDLOCK] %s: unlock password fail and try to clear password.\n", __func__);

                if(-ETIMEDOUT == ret)
                {
                    printk("[SDLOCK] %s: ret = -ETIMEDOUT and need power cycle before clear password.\n", __func__);

                    /*sdcard status is ETIMEDOUT and unreachable and  need power cycle first.*/
                    mmc_power_off(card->host);
                    /* Wait at least 200 ms according to SD spec */
                    mmc_delay(200);
                    mmc_power_up(card->host, card->ocr);
                    printk("[SDLOCK] %s: mmc_power_cycle done.\n", __func__);

                    /*sdcard need sd_reinit_full binit = true after mmc_power_cycle*/
                    sd_reinit_full(card,dev);
                    printk("[SDLOCK] %s: sd_reinit_full done.\n", __func__);

                    mmc_claim_host(card->host);
                    //unlock failed ,so clear password
                    ret = mmc_lock_unlock_by_buf(card,  key_buf,key_len,MMC_LOCK_MODE_CLR_PWD);
                    if(!ret)
                    {
                        printk("[SDLOCK] %s lock failed and clear PWD Success! \r\n",__func__);
                        ret = -E_NOSUPPORT;
                    }
                    else
                    {
                        //application need do something , repare card or notify user
                        printk("[SDLOCK] %s lock failed and clear PWD Failed (%d) \r\n",__func__,ret);
                        ret = -E_CARDERROR;
                    }

                    /*sdcard need sd_reinit_full again after clear password, since last sd_reinit_full sdcard is locked.*/
                    sd_reinit_full(card,dev);
                    printk("[SDLOCK] %s: sd_reinit_full done again.\n", __func__);
                    return ret;
                }

                //unlock failed ,so clear password
                ret = mmc_lock_unlock_by_buf(card,  key_buf,key_len,MMC_LOCK_MODE_CLR_PWD);
                if(!ret) {
                        printk("[SDLOCK] %s lock failed and clear PWD Success! \r\n",__func__);
                        ret = -E_NOSUPPORT;
                } else {
                        //application need do something , repare card or notify user
                        printk("[SDLOCK] %s lock failed and clear PWD Failed (%d) \r\n",__func__,ret);
                        ret = -E_CARDERROR;
                }

                //reset device
                mmc_release_host(card->host);
                return ret;
        }
        else
        {
                //save password
                save_unlock_password(card,key_buf,key_len);

                mmc_release_host(card->host);
                printk("[SDLOCK] unlock sd card ok when assign.\n");
                return ret;
        }

}

/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_lock_do_erase(struct mmc_card *card,struct device *dev)
{
        int ret;
        if(!card || !dev)
                return -EINVAL;

        mmc_claim_host(card->host);
        ret = mmc_lock_unlock_by_buf(card, NULL, 0, MMC_LOCK_MODE_ERASE);
        if (ret) {
                dev_dbg(&card->dev, "fail to erase\n");
                mmc_release_host(card->host);
                return ret;
        }

        printk("[SDLOCK] %s erase OK \r\n",__func__);

        card->state &= ~MMC_STATE_ENCRYPT;
        clear_unlock_password(card);
        /* when sd card is erased, sd device must reinit */
        ret = sd_erase_reinit(card,dev);
        if (ret) {
                printk("%s: erase lock, sd init card error %d\n", __func__,ret);
        }
        return ret;
}

/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_lock_do_remove(struct mmc_card *card,struct device *dev,u8* key_buffer, int key_len)
{
        int ret;
        int is_lock_before;
        if(!card || !dev || !key_buffer || (key_len==0) )
                return -EINVAL;
        is_lock_before = mmc_card_locked(card);
        mmc_claim_host(card->host);
        ret =  mmc_lock_unlock_by_buf(card, key_buffer,key_len, MMC_LOCK_MODE_CLR_PWD);
        if (ret) {
                dev_dbg(&card->dev, "fail to remove\n");
                mmc_release_host(card->host);
                return ret;
        }
        card->state &= ~MMC_STATE_ENCRYPT;
        clear_unlock_password(card);
        if (is_lock_before)
        {
                /* when sd card password remove and sd locked, sd device must reinit */
                ret = sd_erase_reinit(card,dev);
                if (ret) {
                        printk("%s: remove password, sd init card error %d\n",__func__, ret);
                }
        } else {
                mmc_release_host(card->host);
        }

        return ret;
}

/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_lock_do_lock(struct mmc_card *card,struct device *dev,u8* key_buffer, int key_len)
{
        int ret;
        if(!card || !dev || !key_buffer || (key_len==0) )
                return -EINVAL;

        mmc_claim_host(card->host);
        ret = mmc_lock_unlock_by_buf(card,  key_buffer,key_len, MMC_LOCK_MODE_LOCK);
        if (ret) {
                dev_dbg(&card->dev, "Wrong password\n");
                printk("%s Wrong password err=%d \n",__func__,ret);
                mmc_release_host(card->host);
                return ret;
        }

        mmc_release_host(card->host);
#if 0
        ret = sd_reset_device(dev);
        if(ret) {
                printk("%s sd_reset_device err=%d \n",__func__,ret);
        }
#endif
        return ret;

}

/* MMC_SUCCESS(0)  -- Success  or Failed */
static int sd_lock_do_unlock(struct mmc_card *card,struct device *dev,u8* key_buffer, int key_len)
{
        int ret;
        if(!card || !dev || !key_buffer || (key_len==0) )
                return -EINVAL;

        mmc_claim_host(card->host);
        ret = mmc_lock_unlock_by_buf(card,  key_buffer,key_len, MMC_LOCK_MODE_UNLOCK);
        if (ret || mmc_card_locked(card) ) {
                dev_dbg(&card->dev, "Wrong password\n");
                printk("%s: unlock password fail and try to clear password.\n", __func__);
                //unlock failed ,so clear password
                ret = mmc_lock_unlock_by_buf(card,  key_buffer,key_len,MMC_LOCK_MODE_CLR_PWD);
                if(!ret) {
                        printk("[SDLOCK] %s lock failed and clear PWD Success! \r\n",__func__);
                        ret = -E_NOSUPPORT;
                } else {
                        //application need do something , repare card or notify user
                        printk("[SDLOCK] %s lock failed and clear PWD Failed (%d) \r\n",__func__,ret);
                        ret = -E_CARDERROR;
                }

                //reset device
                mmc_release_host(card->host);
                return ret;
        }
        //save password
        save_unlock_password(card,key_buffer,key_len);

        /* when sd card unlock, sd device must reinit */
        ret = sd_reinit(card,dev);
        if (ret) {
                printk("%s: unlock password, sd init card error %d\n", __func__,ret);

                mmc_claim_host(card->host);
                //unlock failed ,so clear password
                ret = mmc_lock_unlock_by_buf(card,  key_buffer,key_len,MMC_LOCK_MODE_CLR_PWD);
                if(!ret) {
                        printk("[SDLOCK] %s lock failed and clear PWD Success! \r\n",__func__);
                        ret = -E_NOSUPPORT;
                } else {
                        //application need do something , repare card or notify user
                        printk("[SDLOCK] %s lock failed and clear PWD Failed (%d) \r\n",__func__,ret);
                        ret = -E_CARDERROR;
                }

                //reset device
                mmc_release_host(card->host);
                return ret;
        }
        return ret;
}

/*
 * implement MMC password functions: force erase, remove password, change
 * password, unlock card and assign password.
 */

static ssize_t
mmc_lockable_store(struct device *dev, struct device_attribute *att,
                   const char *data, size_t len)
{
        struct mmc_card *card = dev_to_mmc_card(dev);
        int ret;
        u8 key_buffer[MAX_KEY_SIZE] = {0};
        u8 command[MAX_COMMAND_SIZE] = {0};
        int key_len = 0;


        WARN_ON(card->type != MMC_TYPE_SD /*MMC_TYPE_MMC*/);
        WARN_ON(!(card->csd.cmdclass & CCC_LOCK_CARD));

        if(card->type != MMC_TYPE_SD /*MMC_TYPE_MMC*/)
                return -EINVAL;
        if(!(card->csd.cmdclass & CCC_LOCK_CARD))
        {
                printk("[SDLOCK] this card don't support LOCK CARD Function from cmdclass!\n");
                return -EINVAL;
        }
        else
        {
                printk("[SDLOCK] this card support LOCK CARD Function from cmdclass!\n");
        }

        printk("[SDLOCK] %s \r\n",__func__);

        ret = -EINVAL;
        if(MMC_SUCCESS!=extract(data, command, key_buffer, &key_len)) {
                return ret;
        }

#if DEBUG_PWD
        printk("[SDLOCK] %s data=[%s], command = %s, key = %s\r\n",__func__, data, command, key_buffer);
#endif

        if (mmc_card_locked(card) && !strncmp(command, "erase", 5)) {
                /* forced erase only works while card is locked */
                printk("%s: erase sd card \n", __func__);
                ret = sd_lock_do_erase(card,dev);
                if(MMC_SUCCESS==ret) {
                        ret = len;
                }

        } else if (!strncmp(command, "remove", 6)) {
                /* remove password only works while card is unlocked */
                printk("%s: remove sd card \n", __func__);
                ret = sd_lock_do_remove(card,dev,key_buffer,key_len);
                if(MMC_SUCCESS==ret) {
                        ret = len;
                }

        } else if (!mmc_card_locked(card) && (!strncmp(command, "assign", 6))) {
                /* assign password only works while card is unlocked */
                printk("%s: assign sd card \n", __func__);
                ret = sd_lock_do_assign(card,dev,key_buffer,key_len);
                if(MMC_SUCCESS==ret) {
                        mmc_card_set_encrypted(card);
                        ret = len;
                }

        } else if (mmc_card_locked(card) && !strncmp(command, "unlock", 6)) {
                /* unlock  only works while card is locked*/
                printk("%s: unlock sd card \n", __func__);
                ret = sd_lock_do_unlock(card,dev,key_buffer,key_len);
                if(MMC_SUCCESS==ret) {
                        ret = len;
                }
        } else if (!mmc_card_locked(card) && !strncmp(command, "lock", 4)) {
                /* lock  only works while card is unlocked*/
                printk("%s: lock sd card \n", __func__);
                ret = sd_lock_do_lock(card,dev,key_buffer,key_len);
                if(MMC_SUCCESS==ret) {
                        ret = len;
                }
        } else if(!strncmp(command, "reset", 5)) {
                printk("%s: reset sd  card \n", __func__);
                mmc_claim_host(card->host);
                ret = sd_reinit(card,dev);
                if (ret) {
                        printk("%s: reset sd  card error %d\n", __func__,ret);
                }

        } else {
                ret = -EINVAL;
        }
        return ret;
}

static struct device_attribute mmc_dev_attr_lockable[] = {
        __ATTR(lockable, (S_IWUSR | S_IRUGO),
        mmc_lockable_show, mmc_lockable_store),
        __ATTR_NULL,
};

int mmc_lock_add_sysfs(struct mmc_card *card)
{
        if(card->type != MMC_TYPE_SD /*MMC_TYPE_MMC*/)
                return 0;
        if(!(card->csd.cmdclass & CCC_LOCK_CARD))
                return 0;

        return mmc_add_attrs(card, mmc_dev_attr_lockable);
}

void mmc_lock_remove_sysfs(struct mmc_card *card)
{
        if(card->type != MMC_TYPE_SD /*MMC_TYPE_MMC*/)
                return;
        if(!(card->csd.cmdclass & CCC_LOCK_CARD))
                return;

        mmc_remove_attrs(card, mmc_dev_attr_lockable);
}
