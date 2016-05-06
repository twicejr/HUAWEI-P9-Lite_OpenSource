/*************************************************************************************************
 File name  : exmbist_api_drv.c
 Version    : 1.00
 Author     :
 Description: commands/observe commands functions
              users can change EXMBIST configuration by setting commands, and get EXMBIST test status
              by observe commands.
**************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "exmbist_api.h"
#include "exmbist_wrap_top.h"
#include "exmbist_test.h"
#include <linux/string.h>

#define EXMBIST_ROW_BITS         0x10
#define EXMBIST_COL_BITS         0x10
#define EXMBIST_BANK_BITS        0x3
#define EXMBIST_REPEAT_CNT_BITS  0xa
#define EXMBIST_DIAG_CNT_BITS    0x10
#define EXMBIST_ITL_BITS         0x3

ExmDiag g_single_diag;/*一次记录，这里将重复利用*/
exmbist_uint32 g_expect_data[8];/*一次记录中的期待数据*/
exmbist_uint32 g_actual_data[8];/*一次记录中的实际数据*/

exmbist_uint32 exm_drv_half_reset (ExmCtx * ctx);
extern void exm_log_record(char* log_file, char* buf);
	
/*****************************************************************************
 函 数 名  : exm_drv_get_cfg
 功能描述  : 获取EXMBIST IP cfg0-3配置
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
exmbist_uint32 exm_drv_get_cfg (ExmCtx * ctx) {
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 ret;

    EXMBIST_info("EXMBIST configuration info\n");
    
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_GET_CFG0);
    ret = exm_io_rd_dout(ctx);
    EXMBIST_info("Address bus width:    0x%x\n",(ret >> 16) & 0xffff);
    EXMBIST_info("Data bus width:       0x%x\n",ret & 0xffff);

    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_GET_CFG1);
    ret = exm_io_rd_dout(ctx);
    EXMBIST_info("row addr width:       0x%x\n",ret & 0xff);
    EXMBIST_info("col addr width:       0x%x\n",(ret >> 8) & 0xff);
    EXMBIST_info("bank addr width:      0x%x\n",(ret >> 16) & 0xff);
    EXMBIST_info("Interleaving width:   0x%x\n",(ret >> 24) & 0xff);

    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_GET_CFG2);
    ret = exm_io_rd_dout(ctx);
    EXMBIST_info("Repeat counter length:0x%x\n",ret & 0xff);
    EXMBIST_info("Diag counter length:  0x%x\n",(ret >> 8) & 0xff);
    
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_GET_CFG3);
    ret = exm_io_rd_dout(ctx);
    EXMBIST_info("Has scrambler:        0x%x\n",ret & 0x1);
    EXMBIST_info("Has addr interleaving:0x%x\n",(ret >> 4) & 0x1);
    EXMBIST_info("Support dual port:    0x%x\n",(ret >> 6) & 0x1);
    EXMBIST_info("diag_fifo_len:        0x%x\n",(ret >> 24) & 0xff);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_get_status
 功能描述  : 获取exmbsit 状态
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
exmbist_uint32 exm_drv_get_status (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 st = exm_io_rd_status(ctx);
    ctx->bist_done      = st & 0x1;
    ctx->bist_pass      = (st >> 1) & 0x1;
    ctx->parity_err     = (st >> 4) & 0x1;
    ctx->watchdog_err   = (st >> 5) & 0x1;
    ctx->diag_fifo_last = (st >> 6) & 0x1;
    ctx->diag_ip        = (st >> 8) & 0xf;
    ctx->finger_print   = (st >> 12) & 0xf;
    ctx->cycle_count    = (st >> 16) & 0xffff;
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_full_reset
 功能描述  : 全复位,寄存器所有配置清除
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_full_reset (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_FULL_RST); 
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_full_set
 功能描述  : 配置重新设置
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
void exm_drv_full_set(ExmCtx * ctx)
{

    (void) exm_drv_set_addr_range(ctx);
    (void) exm_drv_set_row_col_bank_bits(ctx);
    (void) exm_drv_set_repeat_count (ctx);
    (void) exm_drv_set_diag_cnt (ctx);
    (void) exm_drv_set_loop_en (ctx);
    (void) exm_drv_set_interleave (ctx);
    (void) exm_drv_load_counter (ctx);
    (void) exm_drv_set_alt_fix_addr (ctx);
    (void) exm_drv_sel_prbs (ctx);
    (void) exm_drv_set_addr_prbs_seed (ctx);
    (void) exm_drv_set_inorder (ctx);
    (void) exm_drv_set_base_pattern (ctx);
    (void) exm_drv_set_alt_pattern (ctx);

}

/*****************************************************************************
 函 数 名  : exm_drv_half_reset
 功能描述  : 半复位，exmbist IP内配置不变
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_half_reset (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_HALF_RST);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_load_counter
 功能描述  : 加载地址计数器相关功能
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_load_counter (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 word = ((0x1 & ctx->cfg_alt_bank_en       )  << 13) |
                          ((0x1 & ctx->cfg_alt_col_en        )  << 12) |
                          ((0x1 & ctx->cfg_alt_row_en        )  << 11) |
                          ((0x7 & ctx->cfg_alt_addr_mode     )  <<  8) |
                          ((0x1 & ctx->cfg_base_col_off      )  <<  7) |
                          ((0x1 & ctx->cfg_base_row_off      )  <<  6) |
                          ((0x1 & ctx->cfg_base_plustwo_mode )  <<  5) |
                          ((0x1 & ctx->cfg_half_addr_mode    )  <<  4) |
                          ((0x1 & ctx->cfg_row_fast_mode     )  <<  3) |
                          ((0x1 & ctx->cfg_base_bank_dir     )  <<  2) |
                          ((0x1 & ctx->cfg_base_col_dir      )  <<  1) |
                          ((0x1 & ctx->cfg_base_row_dir      )       );
    (void) exm_io_wr_cmd(ctx, (word << 8) | EXMBIST_CMD_SET_ADDR_CNT);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_interleave
 功能描述  : 设置bank交织
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_interleave (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 w = (ctx->cfg_itl_mode << 16) | (ctx->cfg_itl_bits << 8) | ctx->cfg_itl_en;
    (void) exm_io_wr_cmd(ctx, (w << 8) | EXMBIST_CMD_SET_ITL);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_repeat_count
 功能描述  : 设置repeat次数
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_repeat_count (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, (ctx->cfg_rep_cnt << 8) | EXMBIST_CMD_SET_REPEAT_CNT);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_loop_en
 功能描述  : 设置loop功能使能
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_loop_en (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, (ctx->cfg_loop_en << 8) | EXMBIST_CMD_SET_LOOP_EN);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_row_col_bank_bits
 功能描述  : 设置bank/row/col地址线
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_row_col_bank_bits (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 w = ctx->cfg_row_bits | (ctx->cfg_col_bits << 8) | (ctx->cfg_bank_bits << 16);
    (void) exm_io_wr_cmd(ctx, (w << 8) | EXMBIST_CMD_SET_ROW_COL_BANK_BITS);
    return uiret;
}



/*****************************************************************************
 函 数 名  : exm_drv_set_inorder
 功能描述  : 设置global_inorder功能
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_inorder (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, (ctx->cfg_global_inorder << 8) |EXMBIST_CMD_SET_GLOBAL_INORDER);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_diag_cnt
 功能描述  : 设置Diag cnt 功能
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_diag_cnt (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, (ctx->cfg_diag_cnt << 8) | EXMBIST_CMD_SET_DIAG_CNT);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_addr_range
 功能描述  : 设置扫描地址范围
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_addr_range (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_SET_ADDR_RANGE);
    (void)exm_io_wr_din(ctx, ctx->cfg_min_addr);
    (void)exm_io_wr_din(ctx, 0x0);
    (void)exm_io_wr_din(ctx, ctx->cfg_max_addr);
    (void)exm_io_wr_din(ctx, 0x0);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_base_pattern
 功能描述  : 设置base 数据pattern
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_base_pattern (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 i;
    exmbist_uint32 * pat = ctx->cfg_base_pat;
    if(NULL == ctx->cfg_base_pat){
        EXMBIST_info("ERROR!! ctx->cfg_base_pat cannot be NULL. Ctx has not be initialized yet\n");
    }else{
        (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_SET_BASE_PAT);
        for (i=0; i<ctx->data_blk; i++) {
            (void) exm_io_wr_din(ctx, pat[i]);
        }
    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_alt_pattern
 功能描述  : 设置alt 数据pattern
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_alt_pattern (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 i;
    exmbist_uint32 * pat = ctx->cfg_alt_pat;
    if(NULL == ctx->cfg_alt_pat){
        EXMBIST_error("exm_drv_set_alt_pattern ERROR!! ctx->cfg_alt_pat cannot be NULL. Ctx has not be initialized yet\n");
    }else{
        (void)exm_io_wr_cmd(ctx, EXMBIST_CMD_SET_ALT_PAT);
        for (i=0; i<ctx->data_blk; i++) {
            (void) exm_io_wr_din(ctx, pat[i]);
        }
    }
    return uiret;
}
/*****************************************************************************
 函 数 名  : exm_drv_sel_prbs
 功能描述  : 设置prbs功能
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_sel_prbs (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 word = 0;
    word =  (ctx->cfg_addr_prbs_skew << 4) | ctx->cfg_addr_prbs_sel;
    (void) exm_io_wr_cmd(ctx, ( word << 8) | EXMBIST_CMD_SEL_PRBS);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_addr_prbs_seed
 功能描述  : 设置prbs 种子
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_addr_prbs_seed (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, ( (ctx->cfg_addr_prbs_seed) << 8) | EXMBIST_CMD_SET_ADDR_PRBS_SEED);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_alt_fix_addr
 功能描述  : 设置alt_fix_addr功能
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_alt_fix_addr (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, ( (ctx->cfg_alt_fix_addr) << 8 ) | EXMBIST_CMD_SET_ALT_FIX_ADDR);
    return uiret;
}

#if 1
extern char *g_Log_file;
char g_exmdiag_str[1536] = {0};

unsigned int exm_util_format_exmdiag(unsigned int diag_cnt, ExmDiag * diag)
{

	char temp_buf[400] = {0};
	memset(temp_buf, 0, 400);
	if (diag_cnt == 0) //first diag 
	{
		snprintf(g_exmdiag_str, strlen("FAILED")+1, "FAILED");
	}

	snprintf(temp_buf, 399, \
"algoid:0x%x stageid:%u errorcnt:%u errorid:%u loop_id:0x%x addr:0x%x \n\
exp: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n\
act: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", 
							diag->algo_id,
							diag->stage_id,
							diag->error_cnt,
							diag->error_id,
							diag->loop_id,
							diag->addr,
							//exm_addr_to_ap_addr(diag->addr),
							diag->expect[0],
							diag->expect[1],
							diag->expect[2],
							diag->expect[3],
							diag->expect[4],
							diag->expect[5],
							diag->expect[6],
							diag->expect[7],
							diag->actual[0],
							diag->actual[1],
							diag->actual[2],
							diag->actual[3],
							diag->actual[4],
							diag->actual[5],
							diag->actual[6],
							diag->actual[7]
							);

	strncat(g_exmdiag_str, temp_buf, strlen(temp_buf));

	if (diag_cnt == 3) //last diag 
	{
		memset(temp_buf, 0, 400);
		snprintf(temp_buf, strlen("#COMPLETE#"), "#COMPLETE#");
		strncat(g_exmdiag_str, temp_buf, strlen(temp_buf));
	}

	EXMBIST_error("DDR_BOARDTEST: %s\n", g_exmdiag_str);

	return 0;
}
#endif

/*****************************************************************************
 函 数 名  : exm_drv_get_diag
 功能描述  : 检查diag_fifo中的错误diag记录
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_get_diag(ExmCtx * ctx) 
{
     exmbist_uint32 uiret = EXMBIST_OK;
     exmbist_uint32 i;
     exmbist_uint32 error_in_fifo_cnt;

     memset(g_exmdiag_str, 0, 1536);
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_GET_FAIL_CNT);
     ctx->diag_fail_cnt = exm_io_rd_dout(ctx);/*错误总数*/
     ctx->error_id = 0;
     error_in_fifo_cnt = exm_util_get_error_num(ctx);
     if(error_in_fifo_cnt>0)
     {
         EXMBIST_error("exm_drv_get_diag: ERROR encounted !!!\n");
     }

     for(i=0;i<error_in_fifo_cnt;i++)
     {
         exm_drv_get_single_diag(ctx);

         (void) exm_util_display_ExmDiag(ctx,&g_single_diag); /*print log when generate the chain*/
	 exm_util_format_exmdiag(i, &g_single_diag);
         if(i<(error_in_fifo_cnt-1))
         {
             (void) exm_drv_diag_fifo_advance(ctx);/*next diag*/
         }
         ctx->error_id++;
    }
    
    if (i != 0)
    {
   	exm_log_record(g_Log_file, g_exmdiag_str);	
    }
    return uiret;

}


/*****************************************************************************
 函 数 名  : exm_drv_get_single_diag
 功能描述  : 获取一次diag记录
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : ExmDiag *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
void exm_drv_get_single_diag(ExmCtx * ctx) 
{
    exmbist_uint32 i;
    ExmDiag * single_diag_info = &g_single_diag;

    single_diag_info->algo_id = 0;
    single_diag_info->stage_id = 0;
    single_diag_info->error_cnt = 0;
    single_diag_info->error_id = 0;
    single_diag_info->loop_id = 0;
    single_diag_info->addr = 0;
    single_diag_info->ip = 0;

    exm_util_init_array(g_expect_data,8,0);
    exm_util_init_array(g_actual_data,8,0);
    
    single_diag_info->expect= (exmbist_uint32 * )&g_expect_data;
    single_diag_info->actual =(exmbist_uint32 * )&g_actual_data;

    
    single_diag_info->algo_id = ctx->algo_id;
    single_diag_info->stage_id = ctx->stage_id;
    single_diag_info->error_cnt = ctx->diag_fail_cnt;
    single_diag_info->error_id = ctx->error_id;
    single_diag_info->loop_id = ctx->loop_id;
    (void) exm_drv_get_status(ctx);
    single_diag_info->ip = ctx->diag_ip;
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_GET_DIAG_ADDR);
    single_diag_info->addr = exm_io_rd_dout(ctx);

    for (i=0; i<ctx->data_blk; i++) {
        (void) exm_io_wr_cmd(ctx, (i<<8) | EXMBIST_CMD_GET_DIAG_EXP);
        single_diag_info->expect[i] = exm_io_rd_dout(ctx);
    }

    for (i=0; i<ctx->data_blk; i++) {
        (void) exm_io_wr_cmd(ctx, (i<<8) | EXMBIST_CMD_GET_DIAG_ACTUAL);
        single_diag_info->actual[i] = exm_io_rd_dout(ctx);
    }
}

/*****************************************************************************
 函 数 名  : exm_drv_diag_fifo_advance
 功能描述  : 切换到下一个diag记录
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_diag_fifo_advance (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_DIAG_FIFO_ADVANCE);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_base_dir
 功能描述  : 设置base地址扫描方向
 输入参数  : ExmCtx * ctx
             exmbist_uint32 row
             exmbist_uint32 col
             exmbist_uint32 bank
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_base_dir (ExmCtx * ctx, exmbist_uint32 row, exmbist_uint32 col, exmbist_uint32 bank) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    ctx->cfg_base_row_dir = row;
    ctx->cfg_base_col_dir = col;
    ctx->cfg_base_bank_dir = bank;
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_alt_dir
 功能描述  : 设置alt地址扫描方向
 输入参数  : ExmCtx * ctx
             exmbist_uint32 row
             exmbist_uint32 col
             exmbist_uint32 bank
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_alt_dir (ExmCtx * ctx, exmbist_uint32 row, exmbist_uint32 col, exmbist_uint32 bank) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    ctx->cfg_alt_addr_mode = row | (col << 1) | (bank << 2);
    ctx->cfg_alt_row_en = row;
    ctx->cfg_alt_col_en = col;
    ctx->cfg_alt_bank_en = bank;
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_alt_mode
 功能描述  : 设置alt 地址模式
 输入参数  : ExmCtx * ctx
             exmbist_uint32 mode
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_alt_mode (ExmCtx * ctx, exmbist_uint32 mode) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    ctx->cfg_alt_addr_mode = mode;
    ctx->cfg_alt_row_en  = 0;
    ctx->cfg_alt_col_en  = 0;
    ctx->cfg_alt_bank_en = 0;
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_inst
 功能描述  : 指令设置功能
 输入参数  : ExmCtx * ctx
             exmbist_uint32 id
             exmbist_uint32 wr
             exmbist_uint32 rd
             exmbist_uint32 exec
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_inst (ExmCtx * ctx, exmbist_uint32 id, exmbist_uint32 wr, exmbist_uint32 rd, exmbist_uint32 exec) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    ctx->inst[id].w = (exec << 16) | (rd << 8) | wr;
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_load_instruction
 功能描述  : 指令加载执行
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_load_instruction (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 i, w;
    for (i=0; i<ctx->num_inst; i++) {
        w = ((i==ctx->num_inst-1 ? 1 : 0) << 22) | ctx->inst[i].w;
        (void) exm_io_wr_cmd(ctx, w << 8 | EXMBIST_CMD_LOAD_INST);
    }
    ctx->stage_id++;
    return uiret;
}

/***********以下函数为cmd流程处理函数******************************/

/*****************************************************************************
 函 数 名  : exm_drv_set_cmd_check1
 功能描述  :  exmbist 配置cmd 检查part1
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_cmd_check1(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    switch(cmd){
        case EXMBIST_CMD_FULL_RST:
            break;
        case EXMBIST_CMD_HALF_RST:
            break;
        case EXMBIST_CMD_SET_ADDR_RANGE:
            if(((ExmCmdSetAddrRange *)cmd_para)->cfg_min_addr > ((ExmCmdSetAddrRange *)cmd_para)->cfg_max_addr) { /*cfg ERROR: cfg_min_addr>cfg_max_addr*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_ROW_COL_BANK_BITS:
            if(!(((ExmCmdSetRowColBankBits *)cmd_para)->cfg_row_bits>0 && ((ExmCmdSetRowColBankBits *)cmd_para)->cfg_row_bits <= EXMBIST_ROW_BITS)){ /*cfg ERROR: cfg_row_bits<=0 || >row_bits*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            if(!(((ExmCmdSetRowColBankBits *)cmd_para)->cfg_col_bits>0 && ((ExmCmdSetRowColBankBits *)cmd_para)->cfg_col_bits <= EXMBIST_COL_BITS)){ /*cfg ERROR: cfg_col_bits<=0 || >col_bits*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            if(!(((ExmCmdSetRowColBankBits *)cmd_para)->cfg_bank_bits>0 && ((ExmCmdSetRowColBankBits *)cmd_para)->cfg_bank_bits <= EXMBIST_BANK_BITS)){ /*cfg ERROR: cfg_bank_bits<=0 || >bank_bits*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_BASE_PAT:
            if(NULL == ctx->cfg_base_pat)
            {
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
                //EXMBIST_error("exm_drv_set_cmd ERROR!! ctx->cfg_base_pat cannot be NULL. Ctx has not be initialized yet!\n");
            }
            break;
        case EXMBIST_CMD_SET_ALT_PAT:
            if(NULL == ctx->cfg_alt_pat)
            {
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
                //EXMBIST_error("exm_drv_set_cmd ERROR!! ctx->cfg_alt_pat cannot be NULL. Ctx has not be initialized yet!\n");
            }
            break;
        case EXMBIST_CMD_SET_REPEAT_CNT:
            if(!(((ExmCmdSetRepeatCnt *)cmd_para)->cfg_rep_cnt < (1 << EXMBIST_REPEAT_CNT_BITS))){ /*cfg ERROR: cfg_repeat_cnt<0 || >2^repeat_cnt -1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_DIAG_CNT:
            if(!(((ExmCmdSetDiagCnt *)cmd_para)->cfg_diag_cnt < (1 << EXMBIST_DIAG_CNT_BITS))){ /*cfg ERROR: cfg_diag_cnt<0 || >2^diag_cnt -1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_LOOP_EN:
            if(((ExmCmdSetLoopEn *)cmd_para)->cfg_loop_en !=0 && ((ExmCmdSetLoopEn *)cmd_para)->cfg_loop_en !=1){ /*cfg ERROR: cfg_loop_en!=0 || 1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_ITL:
            if(((ExmCmdSetItl *)cmd_para)->cfg_itl_en !=0 && ((ExmCmdSetItl *)cmd_para)->cfg_itl_en !=1){ /*cfg ERROR: cfg_itl_en!=0 || 1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            if(!(((ExmCmdSetItl *)cmd_para)->cfg_itl_bits <= EXMBIST_ITL_BITS)){ /*cfg ERROR: cfg_itl_bits<0 || >itl_bits*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            if(!(((ExmCmdSetItl *)cmd_para)->cfg_itl_mode <= EXMBIST_ITL_BITS)){ /*cfg ERROR: cfg_itl_mode<0 || >itl_bits*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        default:
            ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            break;

    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_cmd_check2
 功能描述  : exmbist 配置cmd 检查part2
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_cmd_check2(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 cfg_alt_en;
    exmbist_uint32 cfg_addr_mode;

    switch(cmd){
        case EXMBIST_CMD_LOAD_INST:
            if(((ExmCmdLoadInst *)cmd_para)->cfg_execution_last !=0 && ((ExmCmdLoadInst *)cmd_para)->cfg_execution_last !=1){ /*cfg ERROR:last inst note !=0 || 1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_ADDR_CNT:
        /*if cfg_alt_row_en cfg_alt_row_en cfg_alt_row_en = 0 0 0,then cfg_alt_addr_mode must be 0~5;*/
            cfg_alt_en = 0x0;
            cfg_alt_en = cfg_alt_en | ((((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_bank_en) & 0x1);
            cfg_alt_en = cfg_alt_en | ((((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_col_en) & 0x1);
            cfg_alt_en = cfg_alt_en | ((((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_row_en) & 0x1);
            cfg_addr_mode  = (((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_addr_mode) & 0x7;
            if((0 == cfg_alt_en) && cfg_addr_mode>5){
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SEL_PRBS:
            if(((ExmCmdSelectPrbs *)cmd_para)->cfg_addr_prbs_skew !=0 && ((ExmCmdSelectPrbs *)cmd_para)->cfg_addr_prbs_skew !=1){ /*cfg ERROR: cfg_addr_prbs_skew!=0 || 1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            if(((ExmCmdSelectPrbs *)cmd_para)->cfg_addr_prbs_sel !=0 && ((ExmCmdSelectPrbs *)cmd_para)->cfg_addr_prbs_sel !=2){ /*cfg ERROR: cfg_addr_prbs_sel!=0 || 2*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_ADDR_PRBS_SEED:
            if(((ExmCmdSetAddrPrbsSeed *)cmd_para)->cfg_addr_prbs_seed == 0){ /*cfg ERROR: cfg_addr_prbs_seed=0*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_GLOBAL_INORDER:
            if(((ExmCmdSetGlobalInorder *)cmd_para)->cfg_global_inorder !=0 && ((ExmCmdSetGlobalInorder *)cmd_para)->cfg_global_inorder !=1){ /*cfg ERROR: cfg_global_inorder!=0 || 1*/
                ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            }
            break;
        case EXMBIST_CMD_SET_ALT_FIX_ADDR:
            break;
        case EXMBIST_CMD_SET_ADDR_PRBS_BIT_INV:
            break;

        /*read commands*/
        case EXMBIST_CMD_GET_DIAG_INFO:
            break;
        case EXMBIST_CMD_GET_RUN_STATUS:
            break;
        case EXMBIST_CMD_GET_CFG:
            break;
        case EXMBIST_CMD_WAIT_BIST_PASS:
            break;
        default:
            ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CFG_ERROR;
            break;

    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_cmd_check
 功能描述  : exmbist 配置cmd 检查
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_cmd_check(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    if(cmd <= EXMBIST_CMD_SET_ITL)
    {
        uiret = exm_drv_set_cmd_check1(ctx, cmd, cmd_para);
    }
    else
    {
        uiret = exm_drv_set_cmd_check2(ctx, cmd, cmd_para);
    }

    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_cmd1
 功能描述  : 设置命令part1
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_cmd1(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 *para;
    exmbist_uint32 i;
    exmbist_uint32 word;
    para = (exmbist_uint32 *)cmd_para;
    switch(cmd){
        case EXMBIST_CMD_FULL_RST:
            (void) exm_drv_full_reset(ctx);
            break;
        case EXMBIST_CMD_HALF_RST:
            (void) exm_drv_half_reset(ctx);
            break;
        case EXMBIST_CMD_SET_ADDR_RANGE:
            ctx->cfg_min_addr = ((ExmCmdSetAddrRange *)cmd_para)->cfg_min_addr;
            ctx->cfg_max_addr = ((ExmCmdSetAddrRange *)cmd_para)->cfg_max_addr;
            (void) exm_drv_set_addr_range(ctx);
            break;
        case EXMBIST_CMD_SET_ROW_COL_BANK_BITS:
            ctx->cfg_row_bits = ((ExmCmdSetRowColBankBits *)cmd_para)->cfg_row_bits;
            ctx->cfg_col_bits = ((ExmCmdSetRowColBankBits *)cmd_para)->cfg_col_bits;
            ctx->cfg_bank_bits = ((ExmCmdSetRowColBankBits *)cmd_para)->cfg_bank_bits;
            (void) exm_drv_set_row_col_bank_bits (ctx);
            break;
        case EXMBIST_CMD_SET_BASE_PAT:
            (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_SET_BASE_PAT);
            for(i=0; i<ctx->data_blk; i++) 
            {
                ctx->cfg_base_pat[i]= *(para+i);
                (void) exm_io_wr_din(ctx, *(para+i));
            }
            break;
        case EXMBIST_CMD_SET_ALT_PAT:
            (void) exm_io_wr_cmd(ctx, EXMBIST_CMD_SET_ALT_PAT);
            for(i=0; i<ctx->data_blk; i++)
            {
                ctx->cfg_alt_pat[i]=*(para+i);
                (void) exm_io_wr_din(ctx, *(para+i));
            }
            break;
        case EXMBIST_CMD_SET_REPEAT_CNT:
            ctx->cfg_rep_cnt = ((ExmCmdSetRepeatCnt *)cmd_para)->cfg_rep_cnt;
            (void) exm_drv_set_repeat_count (ctx);
            break;
        case EXMBIST_CMD_SET_DIAG_CNT:
            ctx->cfg_diag_cnt=((ExmCmdSetDiagCnt *)cmd_para)->cfg_diag_cnt;
            (void) exm_drv_set_diag_cnt(ctx);
            break;
        case EXMBIST_CMD_SET_LOOP_EN:
            ctx->cfg_loop_en=((ExmCmdSetLoopEn *)cmd_para)->cfg_loop_en;
            (void) exm_drv_set_loop_en(ctx);
            break;
        case EXMBIST_CMD_SET_ITL:
            ctx->cfg_itl_en = ((ExmCmdSetItl *)cmd_para)->cfg_itl_en;
            ctx->cfg_itl_bits = ((ExmCmdSetItl *)cmd_para)->cfg_itl_bits;
            ctx->cfg_itl_mode = ((ExmCmdSetItl *)cmd_para)->cfg_itl_mode;
            (void) exm_drv_set_interleave (ctx);
            break;
        case EXMBIST_CMD_LOAD_INST:
            word = (((((ExmCmdLoadInst *)cmd_para)->cfg_execution_last)<< 22) | ((ExmCmdLoadInst *)cmd_para)->cfg_operation);
            (void) exm_io_wr_cmd(ctx, word << 8 | EXMBIST_CMD_LOAD_INST);
            break;
        case EXMBIST_CMD_SET_ADDR_CNT:
            ctx->cfg_alt_bank_en      =((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_bank_en       & 0x1;
            ctx->cfg_alt_col_en       =((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_col_en        & 0x1;
            ctx->cfg_alt_row_en       =((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_row_en        & 0x1;
            ctx->cfg_alt_addr_mode    =((ExmCmdSetAddrCnt *) cmd_para)->cfg_alt_addr_mode     & 0x7;
            ctx->cfg_base_col_off     =((ExmCmdSetAddrCnt *) cmd_para)->cfg_base_col_off      & 0x1;
            ctx->cfg_base_row_off     =((ExmCmdSetAddrCnt *) cmd_para)->cfg_base_row_off      & 0x1;
            ctx->cfg_base_plustwo_mode=((ExmCmdSetAddrCnt *) cmd_para)->cfg_base_plustwo_mode & 0x1;
            ctx->cfg_half_addr_mode   =((ExmCmdSetAddrCnt *) cmd_para)->cfg_half_addr_mode    & 0x1;
            ctx->cfg_row_fast_mode    =((ExmCmdSetAddrCnt *) cmd_para)->cfg_row_fast_mode     & 0x1;
            ctx->cfg_base_bank_dir    =((ExmCmdSetAddrCnt *) cmd_para)->cfg_base_bank_dir     & 0x1;
            ctx->cfg_base_col_dir     =((ExmCmdSetAddrCnt *) cmd_para)->cfg_base_col_dir      & 0x1;
            ctx->cfg_base_row_dir     =((ExmCmdSetAddrCnt *) cmd_para)->cfg_base_row_dir      & 0x1;
            (void) exm_drv_load_counter (ctx);
            break;
        default:
            break;
    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_cmd2
 功能描述  : 设置命令part2
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_cmd2(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    switch(cmd){
        case EXMBIST_CMD_SEL_PRBS:
            ctx->cfg_addr_prbs_skew = ((ExmCmdSelectPrbs *)cmd_para)->cfg_addr_prbs_skew;
            ctx->cfg_addr_prbs_sel = ((ExmCmdSelectPrbs *)cmd_para)->cfg_addr_prbs_sel;
            (void) exm_drv_sel_prbs (ctx);
            break;
        case EXMBIST_CMD_SET_ADDR_PRBS_SEED:
            ctx->cfg_addr_prbs_seed = ((ExmCmdSetAddrPrbsSeed *)cmd_para)->cfg_addr_prbs_seed;
            (void) exm_drv_set_addr_prbs_seed (ctx);
            break;
        case EXMBIST_CMD_SET_GLOBAL_INORDER:
            ctx->cfg_global_inorder = ((ExmCmdSetGlobalInorder *)cmd_para)->cfg_global_inorder;
            (void) exm_drv_set_inorder(ctx);
            break;
        case EXMBIST_CMD_SET_ALT_FIX_ADDR:
            ctx->cfg_alt_fix_addr = ((ExmCmdSetAltFixAddr *) cmd_para)->cfg_alt_fix_addr;
            (void) exm_drv_set_alt_fix_addr (ctx);
            break;
        case EXMBIST_CMD_SET_ADDR_PRBS_BIT_INV:
            ctx->cfg_addr_prbs_bit_inv  = ((ExmCmdSetAddrPrbsBitInv *)cmd_para)->cfg_addr_prbs_bit_inv;
            (void) exm_io_wr_cmd(ctx, (ctx->cfg_addr_prbs_bit_inv << 8) | EXMBIST_CMD_SET_ADDR_PRBS_BIT_INV);
            break;

        /*read commands*/
        case EXMBIST_CMD_GET_DIAG_INFO:
            (void)exm_drv_get_diag(ctx);
            break;
        case EXMBIST_CMD_GET_RUN_STATUS:
            (void)exm_util_get_bist_status(ctx);
            (void)exm_util_print_status(ctx);
            break;
        case EXMBIST_CMD_GET_CFG:
            (void)exm_drv_get_cfg(ctx);
            break;
        case EXMBIST_CMD_WAIT_BIST_PASS:
            (void)exm_util_wait_bist_pass(ctx);
            break;
        default:
            break;
    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_drv_set_cmd
 功能描述  : 设置命令主流程
 输入参数  : ExmCtx *ctx
             exmbist_uint32 cmd
             void *cmd_para
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_drv_set_cmd(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    /*cmd 不连续，详见命令表单*/
    if(cmd <= EXMBIST_CMD_SET_BANK_MAP)
    {
        uiret = exm_drv_set_cmd1(ctx, cmd, cmd_para);
    }
    else if( (cmd >= EXMBIST_CMD_SEL_PRBS)&&(cmd <= EXMBIST_CMD_GET_CFG) )
    {
        uiret = exm_drv_set_cmd2(ctx, cmd, cmd_para);
    }
    else
    {
        EXMBIST_error("cmd id is error!");
    }

    return uiret;
}

#if 0

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

#define DATA_PATTERN_LENGTH   8

/*默认数据pattern*/
static exmbist_uint32 g_default_base_pattern[DATA_PATTERN_LENGTH];
static exmbist_uint32 g_default_alt_pattern[DATA_PATTERN_LENGTH];

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

    EXMBIST_POINTER_CHECK(ctx,EXMBIST_ERR_CODE_ID_01);

    /*IO函数指针*/
    ctx->exm_io_wr_cmd_p = exm_wr_cmd;
    ctx->exm_io_wr_din_p = exm_wr_din;
    ctx->exm_io_rd_dout_p = exm_rd_dout;
    ctx->exm_io_rd_status_p = exm_rd_status;
    EXMBIST_POINTER_CHECK(ctx->exm_io_wr_cmd_p,EXMBIST_ERR_CODE_ID_02);
    EXMBIST_POINTER_CHECK(ctx->exm_io_wr_din_p,EXMBIST_ERR_CODE_ID_03);
    EXMBIST_POINTER_CHECK(ctx->exm_io_rd_dout_p,EXMBIST_ERR_CODE_ID_04);
    EXMBIST_POINTER_CHECK(ctx->exm_io_rd_status_p,EXMBIST_ERR_CODE_ID_05);

    /*full reset*/
    (void) exm_drv_full_reset(ctx);

    ctx->data_blk = 8;
    ctx->cfg_base_row_dir  = 1;
    ctx->cfg_base_col_dir  = 1;
    ctx->cfg_base_bank_dir = 1;
    ctx->cfg_addr_prbs_seed = 1;
    ctx->cfg_addr_prbs_skew = 1;
    ctx->cfg_itl_bits = 3;
    ctx->loop_cnt = 1;/*algo loop.Default 1;*/
    /*bank交织关闭*/
    ctx->cfg_itl_en = 0;

    /*默认数据pattern*/
    exm_util_init_array(g_default_base_pattern,DATA_PATTERN_LENGTH,0x5a5a5a5a);
    exm_util_init_array(g_default_alt_pattern,DATA_PATTERN_LENGTH, 0x33333333);
    ctx->cfg_base_pat = (exmbist_uint32 *)&g_default_base_pattern;
    ctx->cfg_alt_pat = (exmbist_uint32 *)&g_default_alt_pattern;
    EXMBIST_POINTER_CHECK(ctx->cfg_base_pat,EXMBIST_ERR_CODE_ID_06);
    EXMBIST_POINTER_CHECK(ctx->cfg_alt_pat,EXMBIST_ERR_CODE_ID_07);

    ctx->status_code = EXMBIST_STATUS_CODE_INITIAL_OK;

    return uiret;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
