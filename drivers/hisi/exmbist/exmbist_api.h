#ifndef __EXMBIST_API_H__
#define __EXMBIST_API_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "exmbist_api_pub.h"
#include "exmbist_api_util.h"
#include "exmbist_api_drv.h"

unsigned int exm_init(void);
unsigned int exm_set_cmd(unsigned int  cmd_id,unsigned int  param_value);
unsigned int exm_algo_run(unsigned int algo_id, unsigned int loop_cnt);
unsigned int exm_rank_algo_run(unsigned int algo_id, unsigned int loop_cnt,unsigned int sub_dmc_rank);
unsigned int exm_all_space_algo_run(unsigned int algo_id, unsigned int loop_cnt);
unsigned int exm_close(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
