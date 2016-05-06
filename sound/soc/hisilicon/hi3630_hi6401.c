/*
 *  hi3630_hi6401.c
 *  ALSA SoC
 *  cpu-dai   : hi3630
 *  codec-dai : hi6401
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/of.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>

static struct snd_soc_dai_link hi3630_hi6401_dai_link[] = {
	{
		/* dai link name*/
		.name		= "hi3630_hi6401_pb_normal",
		/* stream name same as name */
		.stream_name	= "hi3630_hi6401_pb_normal",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6401-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-audio",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6401-audio-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-srcup-normal",
	},
	{
		/* dai link name*/
		.name		= "hi3630_hi6401_pb_dsp",
		/* stream name same as name */
		.stream_name	= "hi3630_hi6401_pb_dsp",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6401-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-audio",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6401-audio-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-srcup-dsp",
	},
	{
		/* dai link name*/
		.name		= "hi3630_hi6401_cp",
		/* stream name same as name */
		.stream_name	= "hi3630_hi6401_cp",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6401-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-audio",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6401-audio-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-pcm-asp-dma",
	},
	{
		/* dai link name*/
		.name		= "hi3630_voice",
		/* stream name same as name */
		.stream_name	= "hi3630_voice",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6401-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-voice",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6401-voice-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-srcdown",
	},
	{
		/* dai link name*/
		.name		= "hi3630_dma_voice",
		/* stream name same as name */
		.stream_name	= "hi3630_dma_voice",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6401-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-voice",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6401-voice-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-pcm-asp-dma-voice",
	},
	{
		/* dai link name*/
		.name		= "hi3630_hdmi_pb",
		/* stream name same as name */
		.stream_name	= "hi3630_hdmi_pb",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hdmi-audio",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "i2s-hdmi-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hdmi-audio-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-pcm-hdmi",
	},
};

/* Audio machine driver */
static struct snd_soc_card hi3630_hi6401_card = {
	/* sound card name, can see all sound cards in /proc/asound/cards */
	.name = "hi3630_hi6401_CARD",
	.owner = THIS_MODULE,
	.dai_link = hi3630_hi6401_dai_link,
	.num_links = ARRAY_SIZE(hi3630_hi6401_dai_link),
};

static int hi3630_hi6401_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &hi3630_hi6401_card;

	pr_err("-----cg----- %s", __FUNCTION__);

	card->dev = &pdev->dev;

	ret = snd_soc_register_card(card);
	if (ret)
		pr_err("%s : register failed %d\n", __FUNCTION__, ret);

	return ret;
}

static int hi3630_hi6401_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	if (NULL != card)
		snd_soc_unregister_card(card);

	return 0;
}

static const struct of_device_id hi3630_hi6401_of_match[] = {
	{.compatible = "hisilicon,hi3630-hi6401", },
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_hi6401_of_match);

static struct platform_driver hi3630_hi6401_driver = {
	.driver	= {
		.name = "hi3630_hi6401",
		.owner = THIS_MODULE,
		.of_match_table = hi3630_hi6401_of_match,
	},
	.probe	= hi3630_hi6401_probe,
	.remove	= hi3630_hi6401_remove,
};
module_platform_driver(hi3630_hi6401_driver);

/* Module information */
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("ALSA SoC for Hisilicon Hi3630 with Hi6401 codec");
MODULE_LICENSE("GPL");
MODULE_ALIAS("machine driver:hi3630-hi6401");