/*
 *  slimbus is a kernel driver which is used to manager SLIMbus devices
 *  Copyright (C) 2014  Hisilicon

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/of.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <hisi/hilog.h>

static struct snd_soc_dai_link hi3650_hi6403_dai_link[] = {
    {
        /* dai link name*/
        .name       = "hi3650_hi6403_pb_normal",
        /* stream name same as name */
        .stream_name    = "hi3650_hi6403_pb_normal",
        /* codec(hi6403) device name ,see in hi6403.c */
        .codec_name = "hi6403-codec",
        /* cpu(k3v3:asp) dai name(device name), see in hi3650-pcm.c */
        .cpu_dai_name   = "slimbus-dai",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6403.c */
        .codec_dai_name = "hi6403-audio-dai",
        /* platform(k3v3:asp) device name, see in hi3650-pcm.c */
        .platform_name  = "hi6210-hifi",
    },
    {
        /* dai link name*/
        .name       = "hi3650_voice",
        /* stream name same as name */
        .stream_name    = "hi3650_voice",
        /* codec(hi6403) device name ,see in hi6403.c */
        .codec_name = "hi6403-codec",
        /* cpu(k3v3:asp) dai name(device name), see in hi3650-pcm.c */
        .cpu_dai_name   = "slimbus-dai",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6403.c */
        .codec_dai_name = "hi6403-voice-dai",
        /* platform(k3v3:asp) device name, see in hi3650-pcm.c */
        .platform_name  = "snd-soc-dummy",
    },
    {
        /* dai link name*/
        .name       = "hi3650_fm1",
        /* stream name same as name */
        .stream_name    = "hi3650_fm1",
        /* codec(hi6403) device name ,see in hi6403.c */
        .codec_name = "hi6403-codec",
        /* cpu(k3v3:asp) dai name(device name), see in hi3650-pcm.c */
        .cpu_dai_name   = "slimbus-dai",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6403.c */
        .codec_dai_name = "hi6403-fm-dai",
        /* platform(k3v3:asp) device name, see in hi3650-pcm.c */
        .platform_name  = "snd-soc-dummy",
    },
    {
        /* dai link name*/
        .name       = "hi3650_fm2",
        /* stream name same as name */
        .stream_name    = "hi3650_fm2",
        /* codec(hi6401) device name ,see in hi6403.c */
        .codec_name = "hi6403-codec",
        /* cpu(k3v3:asp) dai name(device name), see in hi3650-pcm.c */
        .cpu_dai_name   = "slimbus-dai",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6403.c */
        .codec_dai_name = "hi6403-fm-dai",
        /* platform(k3v3:asp) device name, see in hi3650-pcm.c */
        .platform_name  = "snd-soc-dummy",
    },
    {
        /* dai link name*/
        .name       = "hi3650_hi6403_pb_dsp",
        /* stream name same as name */
        .stream_name    = "hi3650_hi6403_pb_dsp",
        /* codec(hi6403) device name ,see in hi6403.c */
        .codec_name = "hi6403-codec",
        /* cpu(k3v3:asp) dai name(device name), see in hi3650-pcm.c */
        .cpu_dai_name   = "slimbus-dai",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6403.c */
        .codec_dai_name = "hi6403-audio-dai",
        /* platform(k3v3:asp) device name, see in hi3650-pcm.c */
        .platform_name  = "hi6210-hifi",
    },
};

/* Audio machine driver */
static struct snd_soc_card hi3650_hi6403_card = {
	/* sound card name, can see all sound cards in /proc/asound/cards */
	.name = "hi3650_HI6403_CARD",
	.owner = THIS_MODULE,
	.dai_link = hi3650_hi6403_dai_link,
	.num_links = ARRAY_SIZE(hi3650_hi6403_dai_link),
};

static int hi3650_hi6403_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_card *card = &hi3650_hi6403_card;

	pr_info("Audio : hi3650_hi6403_probe \n");
	card->dev = &pdev->dev;

	ret = snd_soc_register_card(card);
	if (ret) {
		pr_err("%s : register failed %d\n", __FUNCTION__, ret);
		HiLOGE("audio", "Hi3650_hi6403", "%s : register failed %d\n", __FUNCTION__, ret);
	}

	return ret;
}

static int hi3650_hi6403_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	if (NULL != card)
		snd_soc_unregister_card(card);

	return 0;
}

static const struct of_device_id hi3650_hi6403_of_match[] = {
	{.compatible = "hisilicon,hi3xxx-hi6403", },
	{ },
};
MODULE_DEVICE_TABLE(of, hi3650_hi6403_of_match);

static struct platform_driver hi3650_hi6403_driver = {
	.driver	= {
		.name = "hi3650_hi6403",
		.owner = THIS_MODULE,
		.of_match_table = hi3650_hi6403_of_match,
	},
	.probe	= hi3650_hi6403_probe,
	.remove	= hi3650_hi6403_remove,
};
//module_platform_driver(hi3650_hi6403_driver);

static int __init hi3650_init(void)
{
	pr_info("Audio : hi3xxx-hi6403 init \n");
    return platform_driver_register(&hi3650_hi6403_driver);
}

late_initcall(hi3650_init);

static void __exit hi3650_exit(void)
{
    //remove_proc_entry("status", audio_pcm_dir);

    platform_driver_unregister(&hi3650_hi6403_driver);
}
module_exit(hi3650_exit);

/* Module information */
MODULE_AUTHOR("liuyang <liuyang66@hisilicon.com>");
MODULE_DESCRIPTION("ALSA SoC for Hisilicon hi3650 with hi6403 codec");
MODULE_LICENSE("GPL");
MODULE_ALIAS("machine driver:hi3650-hi6403");
