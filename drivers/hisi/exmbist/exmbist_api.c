/********************************************************************************
 File name  : exmbist_api.c
 Version    : 1.00
 Author     :
 Description: exmbist ip api
********************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "exmbist_api.h"

#define DATA_PATTERN_LENGTH   8

/*默认数据pattern*/
static exmbist_uint32 g_default_base_pattern[DATA_PATTERN_LENGTH];
static exmbist_uint32 g_default_alt_pattern[DATA_PATTERN_LENGTH];

/*io函数指针*/
extern exmbist_uint32 exm_wr_cmd (exmbist_uint32 cmd);
extern exmbist_uint32 exm_wr_din (exmbist_uint32 data) ;
extern exmbist_uint32 exm_rd_dout (void) ;
extern exmbist_uint32 exm_rd_status (void) ;

extern exmbist_uint32 exm_algo_run_loop (ExmCtx * ctx);

/*****************************************************************************
 函 数 名  : exmbist_init
 功能描述  : 初始化入口函数
 输入参数  : ExmCtx *ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exmbist_init(ExmCtx *ctx)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    /*lint -e717*/
    EXMBIST_POINTER_CHECK(ctx,EXMBIST_ERR_CODE_ID_01);
    /*lint +e717*/
	
    /*IO函数指针*/
    ctx->exm_io_wr_cmd_p = exm_wr_cmd;
    ctx->exm_io_wr_din_p = exm_wr_din;
    ctx->exm_io_rd_dout_p = exm_rd_dout;
    ctx->exm_io_rd_status_p = exm_rd_status;
    /*lint -e717*/
    EXMBIST_POINTER_CHECK(ctx->exm_io_wr_cmd_p,EXMBIST_ERR_CODE_ID_02);
    EXMBIST_POINTER_CHECK(ctx->exm_io_wr_din_p,EXMBIST_ERR_CODE_ID_03);
    EXMBIST_POINTER_CHECK(ctx->exm_io_rd_dout_p,EXMBIST_ERR_CODE_ID_04);
    EXMBIST_POINTER_CHECK(ctx->exm_io_rd_status_p,EXMBIST_ERR_CODE_ID_05);
    /*lint +e717*/
	
    /*full reset*/
    (void) exm_drv_full_reset(ctx);

    ctx->data_blk = 8;
    ctx->cfg_base_row_dir  = 1;
    ctx->cfg_base_col_dir  = 1;
    ctx->cfg_base_bank_dir = 1;

    ctx->cfg_itl_bits = 3;
    ctx->loop_cnt = 1;/*algo loop.Default 1;*/
    /*bank交织关闭*/
    ctx->cfg_itl_en = 0;

    /*默认数据pattern*/
    exm_util_init_array(g_default_base_pattern,DATA_PATTERN_LENGTH,0x5a5a5a5a);
    exm_util_init_array(g_default_alt_pattern,DATA_PATTERN_LENGTH, 0x33333333);
    ctx->cfg_base_pat = (exmbist_uint32 *)&g_default_base_pattern;
    ctx->cfg_alt_pat = (exmbist_uint32 *)&g_default_alt_pattern;
    /*lint -e717*/
    EXMBIST_POINTER_CHECK(ctx->cfg_base_pat,EXMBIST_ERR_CODE_ID_06);
    EXMBIST_POINTER_CHECK(ctx->cfg_alt_pat,EXMBIST_ERR_CODE_ID_07);
    /*lint +e717*/
    ctx->status_code = EXMBIST_STATUS_CODE_INITIAL_OK;

    return uiret;
}


/*****************************************************************************
 函 数 名  : exmbist_stop
 功能描述  : exmbist停止函数
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exmbist_stop(ExmCtx * ctx)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    if((ctx->status_code & EXMBIST_STATUS_CODE_INITIAL_OK) == 0)
    {
        EXMBIST_arrert(EXMBIST_ERR_CODE_ID_09);
        uiret = EXMBIST_ERR_CODE_ID_09;
        return uiret;
    }

    ctx->status_code &= ~EXMBIST_STATUS_CODE_INITIAL_OK;

    (void) exm_drv_half_reset (ctx);
    EXMBIST_msleep(100);/*wait 100ms*/
    (void) exm_drv_half_reset (ctx);
    EXMBIST_msleep(100);

    return uiret;
}


/*****************************************************************************
 函 数 名  : exmbist_set_cmd
 功能描述  : exmbist 命令配置接口函数
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd_id
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exmbist_set_cmd(ExmCtx *ctx, exmbist_uint32 cmd_id, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    if((ctx->status_code & EXMBIST_STATUS_CODE_INITIAL_OK) == 0)
    {
        EXMBIST_arrert(EXMBIST_ERR_CODE_ID_10);
        uiret = EXMBIST_ERR_CODE_ID_10;
        return uiret;
    }
    ctx->status_code &= ~EXMBIST_STATUS_CODE_CFG_ERROR;

    (void) exm_drv_set_cmd_check(ctx, cmd_id, cmd_para);
    if((ctx->status_code & EXMBIST_STATUS_CODE_CFG_ERROR) != 0) {
        EXMBIST_arrert(cmd_id);
        uiret = EXMBIST_ERR_CODE_ID_11;
        return uiret;
    }

    (void) exm_drv_set_cmd(ctx, cmd_id, cmd_para);
    
    return uiret;
}

/*****************************************************************************
 函 数 名  : exmbist_algo_run
 功能描述  : 算法运行入口函数
 输入参数  : ExmCtx *ctx
             exmbist_uint32 algo_id
             exmbist_uint32 loop_cnt
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月11日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exmbist_algo_run(ExmCtx *ctx, exmbist_uint32 algo_id, exmbist_uint32 loop_cnt)
{
    exmbist_uint32 uiret;

    if((ctx->status_code & EXMBIST_STATUS_CODE_INITIAL_OK) == 0)
    {
        EXMBIST_arrert(EXMBIST_ERR_CODE_ID_15);
        return EXMBIST_ERR_CODE_ID_15;
    }

    ctx->algo_id  = algo_id;
    ctx->loop_cnt = loop_cnt;

    uiret = exm_algo_run_loop(ctx);
    if(EXMBIST_OK != uiret){
        EXMBIST_arrert(algo_id);
        return uiret;
    }

    ctx->status_code |= EXMBIST_STATUS_CODE_RUN_COMPLETE;

    return uiret;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
