#ifndef _CORESIGHT_CORESIGHT_TMC_H
#define _CORESIGHT_CORESIGHT_TMC_H

#define TMC_ETR  "etr"
#define TMC_ETB  "etb"
#define TMC_ETF  "etf"

#define MAX_TMC_DEV 5
#define BYTES_PER_WORD          4

#define     HEADER_SIZE         (48)
#define     TMC_MAGIC_START     "TMCDUMP"
#define     TMC_MAGIC_SIZE      (sizeof(TMC_MAGIC_START))
#define     TMC_TIME_LEN        sizeof(u64)
#define     TMC_NAME_LEN        (HEADER_SIZE-TMC_MAGIC_SIZE-4-TMC_TIME_LEN)
#define     BUFF_LEN            (0x80)

struct tcm_dump_head {
	char magic[TMC_MAGIC_SIZE];
	u64 ts_nsec;
	u32 data_size;
	char name[TMC_NAME_LEN];
};

#endif
