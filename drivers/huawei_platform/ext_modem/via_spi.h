/*
 * via_spi.h
 *
 */
#ifndef VIA_SPI_H
#define VIA_SPI_H

#include <linux/spi/spi.h>
#include <linux/types.h>
#include <linux/wait.h>

struct via_spi_dev
{
    struct spi_device*    pm_spi; /* pointer to the via spi device */

    char* pm_spi_page_buf; /* page aligned common buf for tx or rx, as spi work in half-duplex */

    struct workqueue_struct* pm_read_wq; /* workqueue thread for bus read */
    struct work_struct m_read_work; /* bus read work */
};

void via_spi_rts_isr(void);
int via_spi_init(void);
void via_spi_exit(void);


#endif
