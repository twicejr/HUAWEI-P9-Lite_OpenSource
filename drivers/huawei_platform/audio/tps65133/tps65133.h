#ifndef TPS65133_H
#define TPS65133_H
#define TPS65133_NAME "tps65133"
#define TPS65133_IOCTL_MAGIC 'v'
#define TPS65133_ENABLE          _IOW(TPS65133_IOCTL_MAGIC, 0xD0, unsigned int)
#define TPS65133_DISABLE         _IOW(TPS65133_IOCTL_MAGIC, 0xD1, unsigned int)
struct tps65133_platform_data
{
    uint32_t gpio_tps65133_en;
    int gpio_type;
};
#endif