#include <soc_onchiprom.h>
#include <hi_uart.h>
#include "bio.h"

#define STACK_TOP 0x1000FFD0

#define COPYRIGHT "Copyright 2008-2020 HUAWEI TECHNOLOGIES CO., LTD."

/*
 * sc and crg register define
 */
#define HI_SC_REGBASE_ADDR 0x90000000

#define MDDRC_REGBASE_ADR  0x90020000

#define HI_CRG_CTRL14_OFFSET 0x38


int main(void);
void nmi_handler(void);
void hardfault_handler(void);

void mddrc_init();
#define AUTO_ENUM_FLAG_VALUE 0x82822828

#ifdef RAMINIT_CHIP_P531
#define VECTOR_NUM 45
#else
#define VECTOR_NUM 144
#endif


struct head_format
{
#ifdef DX_SEC_BOOT
	unsigned char vrl_reserved[VRL_TABLE_SIZE-4];
	unsigned int file_length;
#endif
	unsigned int vectors[VECTOR_NUM];	/* interrupt vectors */
	unsigned int length;				/* image length */
	unsigned char rootca[ROOT_CA_LEN];			/* reserved for ROOT CA */
	unsigned char version[32];			/* reserved for version */
	unsigned char copyright[sizeof(COPYRIGHT)];			/* copyright, will be used for image check */
};

extern  unsigned int __file_size;

__attribute__ ((section("header"))) struct head_format head =
{
#ifdef DX_SEC_BOOT
	.vrl_reserved = {0},
	.file_length =(unsigned int)&__file_size,
#endif
	.vectors =
	{
		STACK_TOP,
		(unsigned int)main,
		(unsigned int)nmi_handler,
		(unsigned int)hardfault_handler,
	},
	.length = 0,
	.rootca = {0},
	.version = {0},
	.copyright = COPYRIGHT,
};

int main()
{
    mddrc_init();

	/* set auto enum flag */
	writel(AUTO_ENUM_FLAG_VALUE, OCR_AUTO_ENUM_FLAG_ADDR);

    print_info("\r\nraminit ok");
    return 0;
}
#if 0
void print_info(const void *pucBuffer)
{
    volatile unsigned int ulStrLen = 0x00;
    volatile unsigned char *pucTmp = (unsigned char *)pucBuffer;
    volatile unsigned int u32Loop;

    while('\0' != *pucTmp++ )
    {
        ulStrLen++;
    }
    pucTmp = (unsigned char *)pucBuffer;
    while(ulStrLen--)
    {
        /*check tx fifo is empty*/
        u32Loop = 10000;
        while(0x00 == (readl(UART0_BASE+UART_USR) & 0x04))
        {
            /* there is nothing we can do when timeout */
            if(0 == --u32Loop)
            {
                return;
            }
        }
        writel(*pucTmp, UART0_BASE + UART_THR);
        pucTmp++;
    }
}
#endif

void nmi_handler(void)
{
    /* coverity[no_escape] */
    while(1);
}

void hardfault_handler(void)
{
    /* coverity[no_escape] */
    while(1);
}