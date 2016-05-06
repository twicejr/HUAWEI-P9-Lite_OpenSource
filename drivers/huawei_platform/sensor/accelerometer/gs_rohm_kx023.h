/* include/linux/input/gs_kxtik1004.h*/


#ifndef __KXTIK_H__
#define __KXTIK_H__

#define ECS_IOCTL_READ_ACCEL_XYZ            _IOR(0xA1, 0x06, char[3])
#define ECS_IOCTL_APP_SET_DELAY		        _IOW(0xA1, 0x18, short)
#define ECS_IOCTL_APP_GET_DELAY             _IOR(0xA1, 0x30, short)
#define ECS_IOCTL_APP_SET_AFLAG		        _IOW(0xA1, 0x13, short)
#define ECS_IOCTL_APP_GET_AFLAG		        _IOR(0xA1, 0x14, short)
#define ECS_IOCTL_READ_DEVICEID				_IOR(0xA1, 0x31, char[20])

/* CTRL_REG1: set resolution, g-range, data ready enable 
        Output resolution: 8-bit valid or 12-bit valid */
//#define RES_8BIT		0x00
//#define RES_12BIT		0x40
//u8 res_12bit;
/* Output g-range: +/-2g, 4g, or 8g */
#define KXTIK_G_2G		0x00
#define KXTIK_G_4G		0x08
#define KXTIK_G_8G		0x10
/*move to config_interface.h*/

/* DATA_CTRL_REG: controls the output data rate of the part */
#define ODR12_5F		0x00
#define ODR25F			0x01
#define ODR50F			0x02
#define ODR100F			0x03
#define ODR200F			0x04
#define ODR400F			0x05
#define ODR800F			0x06

//#define G_MAX			8000
/* OUTPUT REGISTERS */
#define XOUT_L_REG		0x06
#define XOUT_H_REG		0x07
#define YOUT_L_REG		0x08
#define YOUT_H_REG		0x09
#define ZOUT_L_REG		0x0A
#define ZOUT_H_REG		0x0B

#define GS_KX_TIMRER		(1000*1000000)		/*1000000s*/
#define WHO_AM_I		0x0F
/* GRP3 CONTROL REGISTERS */
#define INT_REL			0x1A
#define CTRL_REG1		0x1B  /*sunlibin added*/
#define INT_CTRL1		0x1E
#define DATA_CTRL		0x21

/*sunlibin added*/
/* GRP7 CONTROL REGISTERS */
#define GRP7_INT_REL		0x17
#define GRP7_CTRL_REG1	0x18
#define GRP7_INT_CTRL1	0x1C
#define GRP7_DATA_CTRL	0x1B	/* ODCNTL */

/* CONTROL REGISTER 1 BITS */
#define PC1_OFF			0x7F
#define PC1_ON			0x80
/* INPUT_ABS CONSTANTS */
//#define FUZZ			3
//#define FLAT			3
/* RESUME STATE INDICES */
#define RES_DATA_CTRL		0
#define RES_CTRL_REG1		1
#define RES_INT_CTRL1		2
//#define RESUME_ENTRIES		3

#define KIONIX_ACCEL_WHO_AM_I_KXTE9 		0x00
#define KIONIX_ACCEL_WHO_AM_I_KXTF9 		0x01
#define KIONIX_ACCEL_WHO_AM_I_KXTI9_1001 	0x04
#define KIONIX_ACCEL_WHO_AM_I_KXTIK_1004 	0x05
#define KIONIX_ACCEL_WHO_AM_I_KXTJ9_1005 	0x07
#define KIONIX_ACCEL_WHO_AM_I_KXTJ9_1007 	0x08
#define KIONIX_ACCEL_WHO_AM_I_KXCJ9_1008 	0x0A
#define KIONIX_ACCEL_WHO_AM_I_KXTJ2_1009 	0x09
#define KIONIX_ACCEL_WHO_AM_I_KXCJK_1013 	0x11
#define KIONIX_ACCEL_WHO_AM_I_KX023		0x15

#define GS_SUSPEND  0
#define GS_RESUME   1
#define IC_PM_ON   1
#define IC_PM_OFF  0
typedef enum
{
	GS_ADIX345 	= 0x01,
	GS_ST35DE	= 0x02,
	GS_ST303DLH = 0X03,
	GS_MMA8452  = 0x04,
	GS_BMA250   = 0x05,
	GS_STLIS3XH	= 0x06,
	GS_ADI346   = 0x07,
	GS_KXTIK1004= 0x08,
}hw_gs_type;

/*sunlibin added*/
/* Use this variable to control the number of
 * effective bits of the accelerometer output.
 * Use the macro definition to select the desired
 * number of effective bits. */
#define KIONIX_ACCEL_RES_12BIT	0
#define KIONIX_ACCEL_RES_8BIT	1
#define KIONIX_ACCEL_RES_6BIT	2
#define KIONIX_ACCEL_RES_16BIT	3	//KX023

/* Use this variable to control the G range of
 * the accelerometer output. Use the macro definition
 * to select the desired G range.*/
#define KIONIX_ACCEL_G_2G		0
#define KIONIX_ACCEL_G_4G		1
#define KIONIX_ACCEL_G_6G		2
#define KIONIX_ACCEL_G_8G		3

struct kx023_platform_data {
	int (*adapt_fn)(void);	/* fucntion is suported in some product */
	int slave_addr;     /*I2C slave address*/
	int dev_id;         /*who am I*/
	int *init_flag;     /*Init*/
	int (*gs_power)(int on);
	int int1_gpio;
	int int2_gpio;
	int accel_res;
	int accel_g_range;
	int axis_map_x;
	int axis_map_y;
	int axis_map_z;

	int negate_x;
	int negate_y;
	int negate_z;
};

#endif  /* __KXTIK_H__ */
