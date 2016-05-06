/*
* HDMI ALSA Soc codec driver
*/

#include <linux/init.h>
#include <linux/module.h>
#include <sound/pcm.h>
#include <sound/soc.h>

#define HDMI_AUDIO_MIN_CHANNELS ( 1 )
#define HDMI_AUDIO_MAX_CHANNELS ( 2 )
#define HDMI_AUDIO_FORMATS     ( SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE)
#define HDMI_AUDIO_RATES       ( SNDRV_PCM_RATE_8000_96000)

static int hdmi_audio_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
    pr_info("%s : set codec rate %d %s\n", __FUNCTION__, params_rate(params),
        substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE");

    return 0;
}

struct snd_soc_dai_ops hdmi_audio_dai_ops = {
    .hw_params  = hdmi_audio_hw_params,
};

struct snd_soc_dai_driver hdmi_audio_dai[] = {
   { 
   .name = "hdmi-audio-dai",
    .playback = {
        .stream_name    = "hdmi-playback",
        .channels_min   = HDMI_AUDIO_MIN_CHANNELS,
        .channels_max   = HDMI_AUDIO_MAX_CHANNELS,
        .rates          = HDMI_AUDIO_RATES,
        .formats        = HDMI_AUDIO_FORMATS,
        },
    .ops = &hdmi_audio_dai_ops,
    },
};

static const struct of_device_id hdmi_audio_of_match[] = {
	{
		.compatible = "hisilicon,hdmi-audio",
	},
	{ },
};

MODULE_DEVICE_TABLE(of, hdmi_audio_of_match);

static const struct snd_soc_component_driver hdmi_audio_component = {
	.name		= "hdmi-audio",
};
static int hdmi_audio_codec_probe(struct snd_soc_codec *codec)
{
    return 0;
}

static int hdmi_audio_codec_remove(struct snd_soc_codec *codec)
{
    return 0;
}

static struct snd_soc_codec_driver hdmi_audio_dev = {
    .probe          = hdmi_audio_codec_probe,
    .remove         = hdmi_audio_codec_remove,
};
static int hdmi_audio_probe(struct platform_device *pdev)
{
    int ret = -ENODEV;
    struct device *dev = &pdev->dev;

    BUG_ON(NULL == dev);

    pr_info("%s, hdmi_audio_probe in", __FUNCTION__);

    dev_set_name(dev, "hdmi-audio");
    ret = snd_soc_register_codec(dev, &hdmi_audio_dev,
			hdmi_audio_dai, ARRAY_SIZE(hdmi_audio_dai));
    //ret = snd_soc_register_component(&pdev->dev, &hdmi_audio_component,
    //                                &hdmi_audio_dai, 1);
    if (ret < 0) {
        pr_err("%s: snd_soc_register_codec failed\n", __FUNCTION__);
    }

    return ret;
}

static int hdmi_audio_remove(struct platform_device *pdev)
{
    snd_soc_unregister_codec(&pdev->dev);

    return 0;
}

static struct platform_driver hdmi_audio_driver = {
    .driver = {
        .name  = "hdmi-audio",
        .owner = THIS_MODULE,
        .of_match_table = hdmi_audio_of_match,
    },
    .probe  = hdmi_audio_probe,
    .remove = hdmi_audio_remove,
};

module_platform_driver(hdmi_audio_driver);

MODULE_DESCRIPTION("ASoC hdmi audio driver");
MODULE_AUTHOR("c00166660");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hdmi_audio");
