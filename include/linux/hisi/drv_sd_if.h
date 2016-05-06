#ifndef _DRV_SD_IF_H_
#define _DRV_SD_IF_H_

#include <linux/mmc/card.h>
#include <linux/mmc/core.h>
#define SD_TRACE_CLUSTER_SIZE  0x1000  /*4k*/
#define SD_TRACE_TEST

#define RESULT_OK             0
#define RESULT_FAIL           1
#define RESULT_UNSUP_HOST     2
#define RESULT_UNSUP_CARD     3
#define SD_BUFFER_SIZE        0x4000
#define SDMMC_BLOCK_BYTE     (512)



extern int sd_get_capacity(void);
extern int sd_get_status(void);
extern int sd_sg_init_table(const void *buf,unsigned int buflen);
extern int sd_multi_transfer(unsigned dev_addr, unsigned blocks, unsigned blksz, int write);
extern int bsp_sd_data_cmp(char *buffer1,char *buffer2);
extern int sd_wait_busy(struct mmc_card *card);
extern void sd_prepare_mrq(struct mmc_card *card,
                                struct mmc_request *mrq,
                                struct scatterlist *sg,
                                unsigned sg_len,
                                unsigned dev_addr,
                                unsigned blocks,
                                unsigned blksz,
                                int write);


#ifdef _DRV_LLT_
extern void sg_init_table(struct scatterlist *sgl, unsigned int nents);
extern void sg_set_buf(struct scatterlist *sg, const void *buf,unsigned int buflen);
extern void mmc_claim_host(struct mmc_host *host);
extern void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
extern void mmc_release_host(struct mmc_host *host);
extern int sd_check_result(struct mmc_card *card,struct mmc_request *mrq);
extern void kzfree(const void *p);
#endif


#endif




