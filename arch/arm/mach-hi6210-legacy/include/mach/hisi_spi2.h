#ifndef _HI_SPI2_H__
#define _HI_SPI2_H__

#include <linux/wait.h>

/* Defines */
#define CSPI_IOCTL_EXCHANGE     0x10
#define CSPI_IOCTL_DMA_READ     0x16
#define CSPI_IOCTL_DMA_WRITE    0x17

typedef enum _CEDEVICE_POWER_STATE {
	PwrDeviceUnspecified = -1,
	D0 = 0,
	D1,
  	D2,
  	D3,
  	D4,
  	PwrDeviceMaximum
} CEDEVICE_POWER_STATE, *PCEDEVICE_POWER_STATE;

/* Types */
typedef enum {
	CS0 = 0,     
	CS1 = 1,    
	CS2 = 2,   
	NO_DEVICE
}SPI_CS;

/* CSPI bus configuration */
typedef struct
{    
	unsigned char    bitcount;       /*spii bus trans bits per word(4-16bit) */
	unsigned char    scr;            /* spi div rate*/
	unsigned char    cpsdvsr;        /* spi div must not odd.spi rate =Fsspclk/(cpsdvsr*(1+scr))*/
	unsigned char    burst_num;      /* spi a packages contains burst_num，8 at most */
	unsigned char    spo;            /* SPI Clock 极性  值域:0,1 */
	unsigned char    sph;            /* SPI Clock 相位  值域:0,1 */
} CSPI_BUSCONFIG_T, *PCSPI_BUSCONFIG_T;

/* CSPI exchange packet */
typedef struct
{    
    void* pTxBuf;                  /* pi tx buffer addr */
    void* pRxBuf;                  /* spi rx buffer addr */
    unsigned int xchCnt;           /* spi send count */
    wait_queue_head_t *xchEvent;   /* async trans wait event */
    SPI_CS spiDevice;              /* spi slave devices */
    PCSPI_BUSCONFIG_T pBusCnfg;    /* spi reg configure */
} CSPI_XCH_PKT_T, *PCSPI_XCH_PKT_T;

int CspiDataExchange(PCSPI_XCH_PKT_T pXchPkt);
int CspiDMARead(PCSPI_XCH_PKT_T pXchPkt);
int CspiDMAWrite(PCSPI_XCH_PKT_T pXchPkt);
#endif
