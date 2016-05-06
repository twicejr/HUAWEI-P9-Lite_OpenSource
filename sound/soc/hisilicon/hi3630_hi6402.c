/*
 *  hi3630_hi6402.c
 *  ALSA SoC
 *  cpu-dai   : hi3630
 *  codec-dai : hi6402
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/of.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>

static struct snd_soc_dai_link hi3630_hi6402_dai_link[] = {
	{
		/* dai link name*/
		.name		= "hi3630_hi6402_pb_normal",
		/* stream name same as name */
		.stream_name	= "hi3630_hi6402_pb_normal",
		/* codec(hi6402) device name ,see in hi6402.c */
		.codec_name	= "hi6402-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-audio",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name	= "hi6402-audio-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi6210-hifi",
	},
	{
		/* dai link name*/
		.name		= "hi3630_voice",
		/* stream name same as name */
		.stream_name	= "hi3630_voice",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6402-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "snd-soc-dummy-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6402-voice-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "snd-soc-dummy",
	},
	{
		/* dai link name*/
		.name		= "hi3630_fm1",
		/* stream name same as name */
		.stream_name	= "hi3630_fm1",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6402-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "snd-soc-dummy-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6402-fm-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "snd-soc-dummy",
	},		
	{
		/* dai link name*/
		.name		= "hi3630_fm2",
		/* stream name same as name */
		.stream_name	= "hi3630_fm2",
		/* codec(hi6401) device name ,see in hi6401.c */
		.codec_name	= "hi6402-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "snd-soc-dummy-dai",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
		.codec_dai_name	= "hi6402-fm-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "snd-soc-dummy",
	},
	{
		/* dai link name*/
		.name		= "hi3630_hi6402_pb_dsp",
		/* stream name same as name */
		.stream_name	= "hi3630_hi6402_pb_dsp",
		/* codec(hi6402) device name ,see in hi6402.c */
		.codec_name	= "hi6402-codec",
		/* cpu(k3v3:asp) dai name(device name), see in hi3630-pcm.c */
		.cpu_dai_name	= "sio-audio",
		/* codec dai name, see in struct snd_soc_dai_driver in hi6402.c */
		.codec_dai_name	= "hi6402-audio-dai",
		/* platform(k3v3:asp) device name, see in hi3630-pcm.c */
		.platform_name	= "hi3630-srcup-dsp",
	},
};

/* Audio machine driver */
static struct snd_soc_card hi3630_hi6402_card = {
	/* sound card name, can see all sound cards in /proc/asound/cards */
	.name = "HI3630_HI6402_CARD",
	.owner = THIS_MODULE,
	.dai_link = hi3630_hi6402_dai_link,
	.num_links = ARRAY_SIZE(hi3630_hi6402_dai_link),
};

static int hi3630_hi6402_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &hi3630_hi6402_card;

	card->dev = &pdev->dev;

	ret = snd_soc_register_card(card);
	if (ret)
		pr_err("%s : register failed %d\n", __FUNCTION__, ret);

	return ret;
}

static int hi3630_hi6402_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	if (NULL != card)
		snd_soc_unregister_card(card);

	return 0;
}

static const struct of_device_id hi3630_hi6402_of_match[] = {
	{.compatible = "hisilicon,hi3xxx-hi6402", },
	{ },
};
MODULE_DEVICE_TABLE(of, hi3630_hi6402_of_match);

static struct platform_driver hi3630_hi6402_driver = {
	.driver	= {
		.name = "hi3630_hi6402",
		.owner = THIS_MODULE,
		.of_match_table = hi3630_hi6402_of_match,
	},
	.probe	= hi3630_hi6402_probe,
	.remove	= hi3630_hi6402_remove,
};
module_platform_driver(hi3630_hi6402_driver);

/* Module information */
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("ALSA SoC for Hisilicon Hi3630 with hi6402 codec");
MODULE_LICENSE("GPL");
MODULE_ALIAS("machine driver:hi3630-hi6402");
