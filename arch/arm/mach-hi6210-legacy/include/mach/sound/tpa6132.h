#ifndef TPA6132_H
#define TPA6132_H

#define TPA6132_NAME "tpa6132"

#define TPA6132_IOCTL_MAGIC 'u'

#define TPA6132_ENABLE      _IOW(TPA6132_IOCTL_MAGIC, 0xC0, unsigned)
#define TPA6132_DISABLE     _IOW(TPA6132_IOCTL_MAGIC, 0xC1, unsigned)

struct tpa6132_platform_data {
    uint32_t gpio_tpa6132_en;
};

#endif //TPA6132_H
