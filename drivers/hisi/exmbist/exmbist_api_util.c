/********************************************************************************
 File name  : exmbist_api_util.c
 Version    : 1.00
 Author     :
 Description: common mbist functions
 *******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include <linux/random.h>

#include "exmbist_api.h"
#include "soc_ddrc_dmc_interface.h"
#include "exmbist_test.h"

#define DIAG_FIFO_LEN  0x4

extern unsigned int exm_addr_to_ap_addr(unsigned int addr);

int get_random_number(void)
{
    unsigned long randNum = 0;
 
    get_random_bytes(&randNum, sizeof(unsigned long));
    
    return randNum%400;
}

/*****************************************************************************
 函 数 名  : exm_util_fill_pattern
 功能描述  : 数据pattern填写函数
 输入参数  : ExmCtx * ctx
             exmbist_uint32 * p
             exmbist_uint32 b_rand
             exmbist_uint32 val
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_util_fill_pattern (ExmCtx * ctx, exmbist_uint32 * p, exmbist_uint32 b_rand, exmbist_uint32 val) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 i;
    if(NULL == p)
    {
        //EXMBIST_error("ctx->cfg_alt_pat  is NULL\n");
        return EXMBIST_ERR_CODE_ID_07;
    }
    for (i=0; i<ctx->data_blk; i++)
    {
         p[i] = b_rand ? (b_rand*2560)%(i+1) : val; /*just for test*/
    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_util_get_error_num
 功能描述  : 获取diag fifo中出错记录个数
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_util_get_error_num(ExmCtx * ctx)
{
    exmbist_uint32 error_in_fifo_cnt;
    exmbist_uint32 error_valid;

    if(ctx->diag_fail_cnt > ctx->cfg_diag_cnt) 
    {
        error_valid = ctx->diag_fail_cnt - ctx->cfg_diag_cnt;
    }
    else 
    {
        error_valid = 0;/*ctx->cfg_diag_cnt - ctx->diag_fail_cnt; all ignore*/
    }

    error_in_fifo_cnt = error_valid < DIAG_FIFO_LEN ? error_valid : DIAG_FIFO_LEN;

    return error_in_fifo_cnt;
}

/*****************************************************************************
 函 数 名  : exm_util_display_ExmDiag
 功能描述  : 显示一次错误记录
 输入参数  : ExmCtx * ctx
             ExmDiag * diag
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_util_display_ExmDiag(ExmCtx * ctx, ExmDiag * diag)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 i;
    EXMBIST_error("-------display_ExmDiag-------\n"
                "diag_p->algo_id   : 0x%x\n"
                "diag_p->stage_id  : %d\n"
                "diag_p->error_cnt : %d\n"
                "diag_p->error_id  : %d\n"
                "diag_p->loop_id   : %d\n"
                "diag_p->address   : 0x%x\n"
                "diag_p->ip        : %d\n",
                diag->algo_id,diag->stage_id,diag->error_cnt,diag->error_id,diag->loop_id,diag->addr,diag->ip);
    for(i=0;i<ctx->data_blk;i++)
    {
        EXMBIST_error("diag_p->expect[%d] : 0x%x\n",i,diag->expect[i]);
    }
    for(i=0;i<ctx->data_blk;i++)
    {
        EXMBIST_error("diag_p->actual[%d] : 0x%x\n",i,diag->actual[i]);
    }

    EXMBIST_error("ap_address =0x%x\n" ,exm_addr_to_ap_addr(diag->addr));
    EXMBIST_error("-------------------------------------\n");
    return uiret;
}
/*****************************************************************************
 函 数 名  : exm_util_print_status
 功能描述  : 打印exmbsit 状态
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
exmbist_uint32 exm_util_print_status (ExmCtx * ctx)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    EXMBIST_info("bist_done     : 0x%x \n",ctx->bist_done);
    EXMBIST_info("bist_pass     : 0x%x \n",ctx->bist_pass);
    EXMBIST_info("parity_err    : 0x%x \n",ctx->parity_err);
    EXMBIST_info("watchdog_err  : 0x%x \n",ctx->watchdog_err);
    EXMBIST_info("diag_fifo_last: 0x%x \n",ctx->diag_fifo_last);
    EXMBIST_info("diag_ip       : 0x%x \n",ctx->diag_ip);
    EXMBIST_info("finger_print  : 0x%x \n",ctx->finger_print);
    EXMBIST_info("cycle_count   : 0x%x \n",ctx->cycle_count);
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_util_reset_cfg
 功能描述  : 复位cfg配置
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
void exm_util_reset_cfg (ExmCtx * ctx) {

    ctx->stage_id               = 0;
    ctx->cfg_rep_cnt            = 0;
    ctx->cfg_diag_cnt           = 0;
    ctx->cfg_loop_en            = 0;
    ctx->cfg_base_row_dir       = 1;
    ctx->cfg_base_col_dir       = 1;
    ctx->cfg_base_bank_dir      = 1;
    ctx->cfg_row_fast_mode      = 0;
    ctx->cfg_base_row_off       = 0;
    ctx->cfg_base_col_off       = 0;
    ctx->cfg_alt_row_en         = 0;
    ctx->cfg_alt_col_en         = 0;
    ctx->cfg_alt_bank_en        = 0;
    ctx->cfg_alt_addr_mode      = 0;
    ctx->cfg_alt_fix_addr       = 0;
    ctx->status_code            = EXMBIST_STATUS_CODE_INITIAL_OK;
}

/*****************************************************************************
 函 数 名  : exm_util_inc_error
 功能描述  : error计时器加一
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : static exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
#if 0
static exmbist_uint32 exm_util_inc_error (ExmCtx * ctx)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    ctx->error_cnt++;
    return uiret;
}
#endif
/*****************************************************************************
 函 数 名  : exm_util_init_array
 功能描述  : 数组初始化函数
 输入参数  : exmbist_uint32 array[]
             exmbist_uint32 length
             exmbist_uint32 data
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
void exm_util_init_array(exmbist_uint32 array[],exmbist_uint32 length,exmbist_uint32 data)
{
    exmbist_uint32 i;
    for(i=0;i<length;i++){
        array[i] =data;
    }
}

/*****************************************************************************
 函 数 名  : exm_util_get_bist_status
 功能描述  : 获取mbist状态
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_util_get_bist_status (ExmCtx * ctx)
{
    exmbist_uint32 uiret = EXMBIST_OK;
    (void) exm_drv_get_status(ctx);
    if (ctx->watchdog_err) {
        ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_WATCHDOG_ERROR;
    }
    if (!ctx->bist_pass) {
        ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CHECK_ERROR;
    }
    if (ctx->bist_done) {
        ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_DONE;
    }
    return uiret;
}

/*****************************************************************************
 函 数 名  : exm_util_wait_bist_ready
 功能描述  : 等待mbist 结束并检查
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : static exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
#if 0
static exmbist_uint32 flag = 0;
static exmbist_uint32 exm_util_wait_bist_ready (ExmCtx * ctx)
{
    volatile SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_UNION *ptr_cmd_sum = NULL;
    volatile SOC_DDRC_DMC_DDRC_CFG_STACMD_UNION *ptr_cmd_cfg = NULL;

    ptr_cmd_sum = (volatile SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_UNION *)SOC_DDRC_DMC_DDRC_HIS_CMD_SUM_ADDR(DDR_REG_DMC(exm_get_reg_base(),0,0));
    ptr_cmd_cfg = (volatile SOC_DDRC_DMC_DDRC_CFG_STACMD_UNION *)SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR(DDR_REG_DMC(exm_get_reg_base(),0,0));
            

    do{
        (void) exm_drv_get_status(ctx);

        if (ctx->watchdog_err) {
            //ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_WATCHDOG_ERROR;
            EXMBIST_error("exm_util_wait_bist_ready: watchdog error detected! ****\n");
            //(void) exm_util_inc_error(ctx);
            //return EXMBIST_ERR_CODE_ID_13;
            if(flag == 0)
            {
                ptr_cmd_cfg->reg.load_stat_prd= 0xa;
                ptr_cmd_cfg->reg.load_stat_mode= 0x1;
                ptr_cmd_cfg->reg.load_stat_en= 0x1;
                flag = 1;
            }
            EXMBIST_error("CFG_STACMD = %d\n",ptr_cmd_sum->value);
            EXMBIST_error("CFG_STACMD = %d\n",ptr_cmd_sum->value);
            msleep(10);
        }

        if (ctx->bist_done) 
        {
            ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_DONE;
            return EXMBIST_OK;
        }
    }while (1);
}
#endif
extern struct exm_fsm_state g_exm_cur_fsm_state ;
static exmbist_uint32 exm_util_wait_bist_ready (ExmCtx * ctx)
{
    do{
        (void) exm_drv_get_status(ctx);

        if (ctx->watchdog_err) {
            ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_WATCHDOG_ERROR;
            //printk(KERN_ERR "exm_util_wait_bist_ready: watchdog error detected! ****\n");
            msleep(10);
            //(void) exm_util_inc_error(ctx);
            //return EXMBIST_ERR_CODE_ID_13;
        }

        if (g_exm_cur_fsm_state.exm_hold == EXM_HOLD_UP) {
            printk(KERN_ERR "EXM_HOLD_UP \n");
            return EXMBIST_ERR_CODE_ID_14;
        }

        if (ctx->bist_done) 
        {
            ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_DONE;
            return EXMBIST_OK;
        }
    }while (1);
}
/*****************************************************************************
 函 数 名  : exm_util_wait_bist_pass
 功能描述  : 测试结果检查
 输入参数  : ExmCtx * ctx
 输出参数  : 无
 返 回 值  : exmbist_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : 戚小清 00242728
    修改内容   : 新生成函数

*****************************************************************************/
exmbist_uint32 exm_util_wait_bist_pass (ExmCtx * ctx)
{
    exmbist_uint32 uiret = EXMBIST_OK;

    uiret = exm_util_wait_bist_ready(ctx);
    if(EXMBIST_OK != uiret)
    {
        EXMBIST_arrert(uiret);
        return uiret;
    }
    
    if (!ctx->bist_pass)
    {
        //fail
        uiret = EXMBIST_ERR_CODE_ID_18;
        ctx->status_code = ctx->status_code | EXMBIST_STATUS_CODE_CHECK_ERROR;
        (void)exm_drv_get_diag(ctx);
    }
    return uiret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
