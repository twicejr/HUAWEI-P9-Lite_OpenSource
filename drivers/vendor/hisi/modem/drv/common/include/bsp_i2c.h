

#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__

#include "bsp_om.h"

#include <product_config.h>

/*types*/
#define I2C_ERROR (-1)
#define I2C_OK (0)
/*log*/
#define  i2c_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_I2C, "[i2c]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  i2c_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_I2C, "[i2c]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#define I2C_READ_FLAG		0x01/*read flag*/
#define I2C_WRITE_FLAG		0x00/*write flag*/
#define SLAVE_ID_MASK		0x7f/*slave id mask*/
#define I2C_STATUS_TIMEOUT	10000/*time out*/

#define HI_I2C_CTRL_ALL		(0x7f)
#define HI_I2C_CTRL_I2CEN		(1<<8)
#define HI_I2C_CTRL_IRQEN		(1<<7)
#define HI_I2C_CTRL_START		(1<<6)
#define HI_I2C_CTRL_ACKEN		(1<<2)
#define HI_I2C_CTRL_ARBLOSS	(1<<1)
#define HI_I2C_CTRL_DONE		(1<<0)

#define HI_I2C_COM_ACK		(1<<4)
#define HI_I2C_COM_START		(1<<3)
#define HI_I2C_COM_READ		(1<<2)
#define HI_I2C_COM_WRITE		(1<<1)
#define HI_I2C_COM_STOP		(1<<0)

#define HI_I2C_SR_BUSBUSY 	(1<<7)
#define HI_I2C_SR_START		(1<<6)
#define HI_I2C_SR_ACKERR 		(1<<2)
#define HI_I2C_SR_ABITR 		(1<<1)
#define HI_I2C_SR_INTDONE 	(1<<0)

#define HI_I2C_ICR_ALLMASK	(0x7f)
#define HI_I2C_ICR_START		(1<<6)
#define HI_I2C_ICR_ACK_ERR	(1<<2)
#define HI_I2C_ICR_INTDONE_ERR	(1<<0)

#define HI_I2C_SCL_H_NUM		0x77
#define HI_I2C_SCL_L_NUM		0x77

enum i2c_master{
	I2C_MASTER0,
	I2C_MASTER1,
	I2C_MASTER_MAX

};

#ifdef CONFIG_DESIGNWARE_I2C

int bsp_i2c_slave_register(enum i2c_master,u8 slave_id);


s32 bsp_i2c_byte_data_send(u8 device_id,u8 addr, u8 data);



s32 bsp_i2c_word_data_send(u8 device_id,u8 addr, u16 data);



s32 bsp_i2c_byte_data_receive(u8 device_id, u8 addr,  u16 *data);



s32 bsp_i2c_word_data_receive(u8 device_id,u8 addr, u16 *data);



s32 bsp_i2c_initial(void);

#endif

#endif
