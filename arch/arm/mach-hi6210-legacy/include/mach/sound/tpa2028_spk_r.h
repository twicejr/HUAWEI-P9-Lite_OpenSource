#ifndef TPA2028_SPK_R_H
#define TPA2028_SPK_R_H

#define TPA2028_R_NAME      "tpa2028_r"
#define TPA2028_I2C_ADDR    ( 0x58 )

#define TPA2028_IOCTL_MAGIC 'u'

#define TPA2028_ENABLE      _IOW(TPA2028_IOCTL_MAGIC, 0xC0, unsigned)
#define TPA2028_DISABLE     _IOW(TPA2028_IOCTL_MAGIC, 0xC1, unsigned)
#define TPA2028_SET_REG     _IOW(TPA2028_IOCTL_MAGIC, 0xC2, unsigned)
#define TPA2028_GET_REG     _IOR(TPA2028_IOCTL_MAGIC, 0xC3, unsigned)

struct tpa2028_r_platform_data {
    uint32_t gpio_tpa2028_en;
};

#endif /* TPA2028_SPK_R_H */