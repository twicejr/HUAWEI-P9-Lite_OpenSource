/*
 *  hi6210_hissc.c
 *  ALSA SoC
 *  cpu-dai   : Hi6210
 *  codec-dai : hissc
 */

#include <linux/clk.h>
#include <linux/kernel.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <soc_baseaddr_interface.h>
#include <asm/io.h>


#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>

#include "hi6210_log.h"
static struct platform_device *hi6210_hissc_snd_device;

static struct snd_soc_dai_link hi6210_hissc_dai_link[] =
{
    {
        /* dai link name*/
        .name           = "HI6210_hissc",
        /* stream name same as name */
        .stream_name    = "HI6210_hissc",
        /* cpu(v9r1:hifi) dai name(device name), see in hi6210-pcm.c */
        .cpu_dai_name   = "hi6210-mm",
        /* codec dai name, see in struct snd_soc_dai_driver in hissc.c */
        .codec_dai_name = "hissc-dai",
        /* platform(v9r1:hifi) device name, see in hi6210-pcm.c */
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "MODEM_hissc",
        .stream_name    = "MODEM_hissc",
        .cpu_dai_name   = "hi6210-modem",
        .codec_dai_name = "hissc-dai",
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "FM_hissc",
        .stream_name    = "FM_hissc",
        .cpu_dai_name   = "hi6210-fm",
        .codec_dai_name = "hissc-dai",
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "BT_hissc",
        .stream_name    = "BT_hissc",
        .cpu_dai_name   = "hi6210-bt",
        .codec_dai_name = "hissc-dai",
        .platform_name  = "hi6210-hifi",
    },
    {
        .name           = "LPP_hissc",
        .stream_name    = "LPP_hissc",
        .cpu_dai_name   = "hi6210-lpp",
        .codec_dai_name = "hissc-dai",
        .platform_name  = "hi6210-hifi",
    },
};

/* Audio machine driver */
static struct snd_soc_card snd_soc_hi6210_hissc =
{
    /* sound card name, can see all sound cards in /proc/asound/cards */
    .name       = "HI6210_HISSC_CARD",
    .dai_link   = hi6210_hissc_dai_link,
    .num_links  = ARRAY_SIZE(hi6210_hissc_dai_link),
};


static int hi6210_hissc_probe(struct platform_device *pdev)
{
    int ret                             = 0;
    struct device_node  *codec_np       = NULL;
    struct snd_soc_card *card           = &snd_soc_hi6210_hissc;
    struct device_node  *np             = pdev->dev.of_node;

    logi("%s Begin\n",__FUNCTION__);

    /* set codec node in dai link*/
    codec_np = of_parse_phandle(np, "codec-handle", 0);
    if (!codec_np) {
        loge( "could not find codec node\n");
        return -EINVAL;
    }

    hi6210_hissc_dai_link[0].codec_of_node = codec_np;
    hi6210_hissc_dai_link[1].codec_of_node = codec_np;
    hi6210_hissc_dai_link[2].codec_of_node = codec_np;
    hi6210_hissc_dai_link[3].codec_of_node = codec_np;
    hi6210_hissc_dai_link[4].codec_of_node = codec_np;

    /* register card to soc core */
    card->dev = &pdev->dev;
    ret = snd_soc_register_card(card);
    if (ret){
        loge("%s : register failed %d\n", __FUNCTION__, ret);
    }
    logi("%s end\n",__FUNCTION__);
    return ret;
}
static int hi6210_hissc_remove(struct platform_device *pdev)
{
    logi("%s\n",__FUNCTION__);

    if( snd_soc_hi6210_hissc.dev != &pdev->dev )
    {
        logi("hi6210_hissc_remove dev error\n");
        return -ENODEV;
    }

    platform_device_unregister(hi6210_hissc_snd_device);

    return 0;
}

static const struct of_device_id hi6210_hissc_of_match[] =
{
    {.compatible = "hi6210_hissc", },
    { },
};
static struct platform_driver hi6210_hissc_driver =
{
    .probe  = hi6210_hissc_probe,
    .remove = hi6210_hissc_remove,
    .driver =
    {
        .name           = "hi6210_hissc",
        .owner          = THIS_MODULE,
        .of_match_table = hi6210_hissc_of_match,
    },
};

static int __init hi6210_hissc_soc_init(void)
{
    logi("%s\n",__FUNCTION__);
    return platform_driver_register(&hi6210_hissc_driver);
}

static void __exit hi6210_hissc_soc_exit(void)
{
    logi("%s\n",__FUNCTION__);
    platform_driver_unregister(&hi6210_hissc_driver);
}

module_init(hi6210_hissc_soc_init);
module_exit(hi6210_hissc_soc_exit);

/* Module information */
MODULE_AUTHOR("hisilicon");
MODULE_DESCRIPTION("Hi6210_hissc ALSA SoC audio driver");
MODULE_LICENSE("GPL");
