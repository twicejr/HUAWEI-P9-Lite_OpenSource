#ifndef _FPGA_ICE40_SPI_H_
#define _FPGA_ICE40_SPI_H_

#define DRIVER_NAME "fpga_ice40_spi"
#define FPGA_SPI__FIFO_SIZE 512
#define FPGA_SPI_TRAN_SIZE 8192
#define FAIL 1
#define SUCCESS 0
#define ENABLE 1
#define DISABLE 0
#define GPIO_OEM_UNKNOW (-1)
#define TRUE 1
#define FALSE 0
#define NORMAL_RATE 1
#define BOOT_RATE 0
#define GPIO_OEM_VALID(gpio) ((gpio == GPIO_OEM_UNKNOW) ? 0 : 1)
int ice40_set_cs_callback(int value, int cs_gpio);
int ice40_cs_set(int control);
int ice40_spi_exit(void);
int ice40_data_spi_write(unsigned char *data, int data_size);
int ice40_data_spi_write_then_read(unsigned char *indata, int indata_size, unsigned char* outdata, int outdata_size);
int ice40_data_spi_recv(unsigned char *data, int len);
void set_firmware_reset_gpio(int gpio);
void set_firmware_is_downloading(int ifdownloading);
int get_firmware_is_downloading();

typedef struct fpga_spi_data_ {
     int spi_cs_gpio;
     unsigned char    *rx_buf;
     /* spi master config and spi device*/
    struct spi_device    *spi;
    struct pl022_config_chip spidev0_chip_info;
}fpga_spi_data;

#define FPGA_ICE40_SPI_SPEED_BOOT    (10000*1000)
#define FPGA_ICE40_SPI_SPEED_NORMAL    (1000*1000)

#endif
