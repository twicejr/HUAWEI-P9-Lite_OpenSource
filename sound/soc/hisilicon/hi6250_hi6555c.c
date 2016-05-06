/*
 *  hi6250_hi6555c.c
 *  ALSA SoC
 *  cpu-dai   : Hi6250
 *  codec-dai : hi6555c
 */

#include <linux/clk.h>
#include <linux/kernel.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <asm/io.h>


#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>

#include "hi6250_log.h"
static struct platform_device *hi6250_hi6555c_snd_device;

static struct snd_soc_dai_link hi6250_hi6555c_dai_link[] =
{
    {
        /* dai link name*/
        .name           = "HI6210_hi6555c",
        /* stream name same as name */
        .stream_name    = "HI6210_hi6555c",
        /* cpu(v9r1:hifi) dai name(device name), see in hi6250-pcm.c */
        .cpu_dai_name   = "hi6210-mm",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6555c.c */
        .codec_dai_name = "hi6555c-dai",
        /* platform(v9r1:hifi) device name, see in hi6250-pcm.c */
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "MODEM_hi6555c",
        .stream_name    = "MODEM_hi6555c",
        .cpu_dai_name   = "hi6210-modem",
        .codec_dai_name = "hi6555c-dai",
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "FM_hi6555c",
        .stream_name    = "FM_hi6555c",
        .cpu_dai_name   = "hi6210-fm",
        .codec_dai_name = "hi6555c-dai",
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "BT_hi6555c",
        .stream_name    = "BT_hi6555c",
        .cpu_dai_name   = "hi6210-bt",
        .codec_dai_name = "hi6555c-dai",
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "LPP_hi6555c",
        .stream_name    = "LPP_hi6555c",
        .cpu_dai_name   = "hi6210-lpp",
        .codec_dai_name = "hi6555c-dai",
        .platform_name  = "hi6210-hifi",
    },
};

/* Audio machine driver */
static struct snd_soc_card snd_soc_hi6250_hi6555c =
{
    /* sound card name, can see all sound cards in /proc/asound/cards */
    .name       = "HI6250_hi6555c_CARD",
    .dai_link   = hi6250_hi6555c_dai_link,
    .num_links  = ARRAY_SIZE(hi6250_hi6555c_dai_link),
};


static int hi6250_hi6555c_probe(struct platform_device *pdev)
{
    int ret                             = 0;
    struct device_node  *codec_np       = NULL;
    struct snd_soc_card *card           = &snd_soc_hi6250_hi6555c;
    struct device_node  *np             = pdev->dev.of_node;

    logi("%s Begin\n",__FUNCTION__);

    /* set codec node in dai link*/
    codec_np = of_parse_phandle(np, "codec-handle", 0);
    if (!codec_np) {
        loge( "could not find codec node\n");
        return -EINVAL;
    }

    hi6250_hi6555c_dai_link[0].codec_of_node = codec_np;
    hi6250_hi6555c_dai_link[1].codec_of_node = codec_np;
    hi6250_hi6555c_dai_link[2].codec_of_node = codec_np;
    hi6250_hi6555c_dai_link[3].codec_of_node = codec_np;
    hi6250_hi6555c_dai_link[4].codec_of_node = codec_np;

    /* register card to soc core */
    card->dev = &pdev->dev;
    ret = snd_soc_register_card(card);
    if (ret){
        loge("%s : register failed %d\n", __FUNCTION__, ret);
    }
    logi("%s end\n",__FUNCTION__);
    return ret;
}
static int hi6250_hi6555c_remove(struct platform_device *pdev)
{
    logi("%s\n",__FUNCTION__);

    if( snd_soc_hi6250_hi6555c.dev != &pdev->dev )
    {
        logi("hi6250_hi6555c_remove dev error\n");
        return -ENODEV;
    }

    platform_device_unregister(hi6250_hi6555c_snd_device);

    return 0;
}

static const struct of_device_id hi6250_hi6555c_of_match[] =
{
    {.compatible = "hi6250_hi6555c", },
    { },
};
static struct platform_driver hi6250_hi6555c_driver =
{
    .probe  = hi6250_hi6555c_probe,
    .remove = hi6250_hi6555c_remove,
    .driver =
    {
        .name           = "hi6250_hi6555c",
        .owner          = THIS_MODULE,
        .of_match_table = hi6250_hi6555c_of_match,
    },
};

static int __init hi6250_hi6555c_soc_init(void)
{
    logi("%s\n",__FUNCTION__);
    return platform_driver_register(&hi6250_hi6555c_driver);
}

static void __exit hi6250_hi6555c_soc_exit(void)
{
    logi("%s\n",__FUNCTION__);
    platform_driver_unregister(&hi6250_hi6555c_driver);
}

module_init(hi6250_hi6555c_soc_init);
module_exit(hi6250_hi6555c_soc_exit);

/* Module information */
MODULE_AUTHOR("hisilicon");
MODULE_DESCRIPTION("Hi6250_hi6555c ALSA SoC audio driver");
MODULE_LICENSE("GPL");
