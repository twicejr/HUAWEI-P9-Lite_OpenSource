#ifndef MMC_HEALTH_DIAG_H
#define MMC_HEALTH_DIAG_H



#define MAX_ERR_TIMES 10
#define MAX_ERR_TYPE 9
#define PRT_TIME_PERIOD 10000000000  //10s
#define SD_IO_BUSY 95
#define MAX_REPORT_TIMES 10
#define LOW_SPEED_WARTING_VALUE 1024


enum MMC_BLK_REPORT_ERR
{
   MMC_BLK_STUCK_IN_PRG_ERR = 0x20,
   MMC_BLK_WR_SPEED_ERR,
   MMC_BLK_RW_CHECK_ERR,
   MMC_RO_CHECK_ERR,
   MMC_RO_ERR,
   MMC_READ_ERR,
   MMC_WRITE_ERR,
   MMC_FILESYSTEM_ERR,
   MMC_LOWSPEED_SPEC_ERR
};

struct mmc_blk_err_report_info
{
   unsigned int err_num;
   char err_info[12];
};



void mmc_diag_sd_health_status(struct gendisk *disk,int status);
unsigned int mmc_calculate_ioworkload_and_rwspeed(unsigned long long time,struct request *rqc,struct gendisk *disk);
int mmc_calculate_rw_size(unsigned long long time,unsigned int rq_byte,struct request *rqc);
void mmc_clear_report_info(void);
int mmc_get_rw_status(int status);
int mmc_trigger_ro_check(struct request *rqc,struct gendisk *disk,unsigned int read_only);
extern unsigned int mmc_get_sd_speed(void);
#endif