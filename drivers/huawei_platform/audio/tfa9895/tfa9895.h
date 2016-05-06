#ifndef TFA9895_H
#define TFA9895_H

//#include <linux/ioctl.h>

#define TFA9895_NAME  "tfa9895"
//#define TFA9887_I2C_ADDR 0x34

#if 0
/* ioctls for TFA9895 */
#define TFA9895_IOCTL_MAGIC 'u'

/* this is for i2c-dev.c	*/
#define I2C_SLAVE	0x0703	/* Change slave address			*/
				/* Attn.: Slave address is 7 or 10 bits */
#define I2C_SLAVE_FORCE	0x0706	/* Change slave address			*/
				/* Attn.: Slave address is 7 or 10 bits */
				/* This changes the address, even if it */
				/* is already taken!			*/
#endif
#define POLLING_RETRY_TIMES             ( 3 )
#define TFA9895_EACH_MSG_SIZE           ( 32 )

#endif //TFA9895_H