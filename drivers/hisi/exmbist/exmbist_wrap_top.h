#ifndef __EXMBIST_WARP_TOP_H__
#define __EXMBIST_WARP_TOP_H__

#include "exmbist_api_pub.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#define MAX_RANK_NUM_PER_DMC	2

typedef enum {
	DDR_TYPE_LPDDR3 = 0,
	DDR_TYPE_LPDDR4,
	DDR_TYPE_UNKNOW,
}DDR_TYPE;

typedef enum {
	DRAM_TYPE_LPDDR3 = 0x3,
	DRAM_TYPE_LPDDR4 = 0x8,
}DDR_TYPE_EMUM;

typedef enum {
	DDRC_NUM_0 = 0,
	DDRC_NUM_1,
	DDRC_NUM_MAX,
}DDRC_NUM;

typedef enum {
	DMC_NUM_0 = 0,
	DMC_NUM_1,
	DMC_NUM_MAX,
}DMC_NUM;

typedef struct
{
	int density;
	int size;
	int bank;
	int row;
	int col;
}ddr_density_rbc_str;

typedef struct
{
	int rank_num;
	ddr_density_rbc_str rank_info[MAX_RANK_NUM_PER_DMC];
}ddr_rank_info_str;

/*ioº¯ÊýÖ¸Õë*/
exmbist_uint32 exm_wr_cmd (exmbist_uint32 cmd);
exmbist_uint32 exm_wr_din (exmbist_uint32 data) ;
exmbist_uint32 exm_rd_dout (void) ;
exmbist_uint32 exm_rd_status (void) ;

exmbist_uint32 exm_algo_run_loop (ExmCtx * ctx);

unsigned int exm_init(void);
unsigned int exm_set_cmd(unsigned int  cmd_id,unsigned int  param_value);
unsigned int exm_rank_algo_run(unsigned int algo_id, unsigned int loop_cnt,unsigned int sub_dmc_rank);
unsigned int exm_all_space_algo_run(unsigned int algo_id, unsigned int loop_cnt);
unsigned int exm_close(void);
unsigned int exm_addr_to_ap_addr(unsigned int addr);
unsigned int ap_addr_to_exm_addr(unsigned int addr);
void exm_ddr_self_adapter(void);
unsigned int exm_wait_bist_pass(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
