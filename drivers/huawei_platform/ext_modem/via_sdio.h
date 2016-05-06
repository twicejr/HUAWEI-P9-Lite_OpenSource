/*
 * via_sdio.h
 *
 */
#ifndef VIA_SDIO_H
#define VIA_SDIO_H

#include <linux/mmc/sdio_func.h>
#include <linux/types.h>
#include <linux/wait.h>

#define SDIO_FUNC_1    2

struct via_sdio_dev
{
    struct sdio_func*    pm_sdio; /* pointer to the via sdio func */

    char* pm_sdio_page_buf; /* page aligned common buf for tx or rx, as sdio work in half-duplex */
};

int via_sdio_init(void);
void via_sdio_exit(void);
#endif
