#ifndef SPK_5VBOOST_H
#define SPK_5VBOOST_H

#define SPK_5VBOOST_NAME        "spk_5vboost"

#define SPK_5VBOOST_IOCTL_MAGIC 'u'

#define SPK_5VBOOST_ENABLE      _IO(SPK_5VBOOST_IOCTL_MAGIC, 0xC0)
#define SPK_5VBOOST_DISABLE     _IO(SPK_5VBOOST_IOCTL_MAGIC, 0xC1)

struct spk_5vboost_platform_data {
    uint32_t gpio_5vboost_en;
};

#endif /* SPK_5VBOOST_H */