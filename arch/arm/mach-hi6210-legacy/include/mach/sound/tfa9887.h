#ifndef TFA9887_H
#define TFA9887_H

#include <linux/ioctl.h>

#define TFA9887_NAME  "tfa9887"
#define TFA9887_I2C_ADDR 0x0E

/* ioctls for TFA9887 */
#define TFA9887_IOCTL_MAGIC 'u'
#define I2C_SLAVE    _IOW(TFA9887_IOCTL_MAGIC, 0x10, unsigned)

#define POLLING_RETRY_TIMES             ( 3 )

#endif //TFA9887_H
