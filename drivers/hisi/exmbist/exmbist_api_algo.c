/********************************************************************************
 File name  : exmbist_api_algo.c
 Version    : 1.00
 Author     :
 Description: mbist test algorithms
********************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "exmbist_api.h"
extern int get_random_number(void);


exmbist_uint32 exm_algo_simple_wr (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2; // Data pattern selector and Address or data inversion

    EXMBIST_info("exm_algo_simple_wr\n");
    ctx->cfg_itl_mode = ctx->cfg_itl_bits;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void) exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*UP w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);

    return uiret;

}


exmbist_uint32 exm_algo_simple_rd(ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2; // Data pattern selector and Address or data inversion

    EXMBIST_info("exm_algo_simple_rd\n");

    ctx->cfg_itl_mode = ctx->cfg_itl_bits;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void) exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*UP r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);

    return uiret;

}



exmbist_uint32 exm_algo_marchcminus (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2; // Data pattern selector and Address or data inversion

    EXMBIST_info("exm_algo_marchc\n");

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    //writel(123456789,0x1000001c);/*错误注入*/

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    EXMBIST_msleep(100);

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/

    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    EXMBIST_msleep((u32)(get_random_number()));

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_butterfly (ExmCtx * ctx) 
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_butterfly\n");

    ctx->cfg_alt_addr_mode = EXMBIST_ALT_MODE_BUTTERFLY;/*butterfly*/

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret)
    {
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_JMP_1);  /*r1,jump 1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret)
    {
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_INV, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN, EXMBIST_I_JMP_1);  /*r0,jump 1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret)
    {
        return EXMBIST_ERR_CODE_ID_23;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_surround (ExmCtx * ctx) 
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_surround\n");

    ctx->cfg_alt_addr_mode = EXMBIST_ALT_MODE_SURROUND;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_JMP_1);  /*r1,jump 1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_INV, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN, EXMBIST_I_JMP_1);  /*r0,jump 1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_dbus_walk (ExmCtx * ctx,exmbist_uint32 mode) 
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_dbus_walk\n");

    ctx->cfg_alt_addr_mode = EXMBIST_ALT_MODE_FIX;
    ctx->cfg_min_addr = 0;
    ctx->cfg_max_addr = ((u32)(0x100 - 1))<<(ctx->cfg_bank_bits); /*make sure loop =256*/
    ctx->cfg_itl_en = 0;

    exm_drv_full_set(ctx);

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | mode | EXMBIST_I_A_ALT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | mode | EXMBIST_I_A_ALT, EXMBIST_I_JMP_0); /*r0 EXMBIST_I_D_WALK just for fifo cmp*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32  exm_algo_addr_walk(ExmCtx *ctx)
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_addr_walk\n");

    ctx->cfg_alt_addr_mode = EXMBIST_ALT_MODE_ONE_BIT_INVERT;

    exm_drv_full_set(ctx);

     ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_ALT, EXMBIST_I_NULL, EXMBIST_I_NULL);   /*write base addr only one times*/
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN |  EXMBIST_I_D_ALT , EXMBIST_I_NULL); /*read base addr  only one times*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_WALK | EXMBIST_I_A_ALT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*write alt addr*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL,  EXMBIST_I_EN |  EXMBIST_I_D_ALT , EXMBIST_I_JMP_2); /*read base addr*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    
    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_3step (ExmCtx *ctx, exmbist_uint32 addr_a,exmbist_uint32 addr_b)
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_3step\n");

    /*write address A all 0*/
    ctx->cfg_min_addr = addr_a<<ctx->cfg_bank_bits;
    ctx->cfg_max_addr = addr_a<<ctx->cfg_bank_bits;
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0x0);
    exm_algo_simple_wr(ctx,0);
    
    /*write address B all 1*/
    ctx->cfg_min_addr = addr_b<<ctx->cfg_bank_bits;
    ctx->cfg_max_addr = addr_b<<ctx->cfg_bank_bits;
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0xffffffff);
    exm_algo_simple_wr(ctx,0);

    /*read address A all 0*/
    ctx->cfg_min_addr = addr_a<<ctx->cfg_bank_bits;
    ctx->cfg_max_addr = addr_a<<ctx->cfg_bank_bits;
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0x0);
    exm_algo_simple_rd(ctx,0);
    
    /*read address B all 1*/
    ctx->cfg_min_addr = addr_b<<ctx->cfg_bank_bits;
    ctx->cfg_max_addr = addr_b<<ctx->cfg_bank_bits;
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0xffffffff);
    exm_algo_simple_rd(ctx,0);
    
    /* fix address A, data bus walking 1*/
    ctx->cfg_alt_fix_addr = addr_a<<ctx->cfg_bank_bits;
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0x0);    /*walk one*/
    ctx->cfg_base_pat[0] = EXMBIST_DDR_BITS_DEFAULT_INIT_WALK1_DATA;
    uiret = exm_algo_dbus_walk(ctx,EXMBIST_I_D_WALK);
    if(EXMBIST_OK != uiret){
       return EXMBIST_ERR_CODE_ID_20;
    }

    /* fix address A, data bus walking 0*/
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0xffffffff);    /*walk zero*/
    ctx->cfg_base_pat[0] = EXMBIST_DDR_BITS_DEFAULT_INIT_WALK0_DATA;
    uiret = exm_algo_dbus_walk(ctx,EXMBIST_I_D_WALK);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    /* walk 1 test on the address bus*/
    ctx->cfg_min_addr = 0;
    ctx->cfg_max_addr = 0;
    (void)exm_util_fill_pattern(ctx, ctx->cfg_base_pat, 0, 0xffffffff);
    (void)exm_util_fill_pattern(ctx, ctx->cfg_alt_pat, 0, 0xffffffff);
    ctx->cfg_base_pat[ctx->data_blk-1]=0x7fffffff;

    uiret = exm_algo_addr_walk(ctx);
    if(EXMBIST_OK != uiret)
    {
        return EXMBIST_ERR_CODE_ID_22;
    }

    /* walk 0 test on the address bus*/
    if(ctx->density == 0xe || ctx->density == 0x1){
        /*地址空洞问题,需要保证地址最高位为0*/
        ctx->cfg_max_addr = ((exmbist_uint32)1<<(ctx->cfg_row_bits+ctx->cfg_col_bits+ctx->cfg_bank_bits - 1))-1;
    }
    else{
        ctx->cfg_max_addr = ((exmbist_uint32)1<<(ctx->cfg_row_bits+ctx->cfg_col_bits+ctx->cfg_bank_bits)) - 1;
    }
    ctx->cfg_min_addr = ctx->cfg_max_addr;

    uiret = exm_algo_addr_walk(ctx);
    if(EXMBIST_OK != uiret)
    {
        return EXMBIST_ERR_CODE_ID_23;
    }

    return uiret;
}


exmbist_uint32 exm_algo_dbus_prbs (ExmCtx * ctx) 
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_dbus_prbs\n");

    /*if without the following line, there will be errors.*/
    ctx->cfg_min_addr = 0;
    ctx->cfg_max_addr = 0;  /*required by prbs test*/
    ctx->cfg_addr_prbs_skew = 1;
    ctx->cfg_addr_prbs_seed = (exmbist_uint32)(get_random_number());

    (void)exm_drv_set_base_dir(ctx, EXMBIST_DIR_UP, EXMBIST_DIR_UP, EXMBIST_DIR_UP);  /*all up*/
    (void)exm_drv_set_alt_mode (ctx, EXMBIST_ALT_MODE_PRBS_LA);
    ctx->cfg_itl_mode = ctx->cfg_itl_bits;

    exm_drv_full_set(ctx);

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_PRBS | EXMBIST_I_A_ALT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_PRBS | EXMBIST_I_A_ALT, EXMBIST_I_JMP_0); /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_PRBS | EXMBIST_I_A_ALT, EXMBIST_I_NULL, EXMBIST_I_JMP_0);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_PRBS | EXMBIST_I_A_ALT, EXMBIST_I_JMP_0); /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}

exmbist_uint32 exm_algo_march_addr_prbs (ExmCtx * ctx,exmbist_uint32 prbs_sel,exmbist_uint32 prbs_skew) 
{
    exmbist_uint32 uiret;

    EXMBIST_info("exm_algo_march_addr_prbs\n");

    /*if without the following line, there will be errors.*/
    /*why? because alt_addr != base_addr, so there will be "holes"!*/
    ctx->cfg_min_addr = 0;
    ctx->cfg_max_addr = 0;

    ctx->cfg_addr_prbs_sel = prbs_sel;     /*0:prbs7  2:prbs15*/
    ctx->cfg_addr_prbs_skew = prbs_skew;  /*0:tap0 1:all*/
    ctx->cfg_addr_prbs_seed = (exmbist_uint32)(get_random_number());

    if(ctx->density == 0xe || ctx->density == 0x1)
    {
       ctx->cfg_row_bits = ctx->cfg_row_bits -1;
    }

    (void)exm_drv_set_alt_mode (ctx, EXMBIST_ALT_MODE_PRBS);
    
    exm_drv_full_set(ctx);

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_JMP_0);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

#if 1
    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_INV, EXMBIST_I_JMP_0);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }


    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_NULL, EXMBIST_I_JMP_0);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }


    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_JMP_0);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_INV, EXMBIST_I_NULL, EXMBIST_I_JMP_0);  /*w1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_INV, EXMBIST_I_JMP_0);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

#endif
    if(ctx->density == 0xe || ctx->density == 0x1)
    {
       ctx->cfg_row_bits = ctx->cfg_row_bits + 1;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_boot_test(ExmCtx * ctx)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = 0;

    EXMBIST_info("**exm_algo_boot\n");

    ctx->cfg_alt_row_en = 1;
    ctx->cfg_alt_col_en = 1;
    ctx->cfg_alt_bank_en = 0;
    ctx->cfg_row_fast_mode =1;

    ctx->cfg_min_addr =0;
    ctx->cfg_max_addr =256;/*太大可能影响算法运行时间*/

    exm_drv_full_set(ctx);

    ctx->num_inst = 5;
    /*lint -e845*/
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_JMP_0);  /*w0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_A_ALT| EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_JMP_1);  /*w1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT| EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_A_ALT | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_JMP_3);  /*w0 */
    /*lint +e845*/
    (void) exm_drv_load_instruction(ctx);

    uiret = exm_util_wait_bist_pass(ctx);

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_march_sl (ExmCtx * ctx, exmbist_uint32 dpat) 
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    EXMBIST_info("**exm_algo_march_sl\n");

    ctx->cfg_rep_cnt = 1;

    exm_drv_full_set(ctx);

     ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r0 r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w1 w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r1 r1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w0 w0*/
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r1 r1*/
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w0 w0*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r0 r0*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w1 w1*/
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r0 r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w1 w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r1 r1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w0 w0*/
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/

    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r1 r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w0 w0*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_REP);  /*r0 r0*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_REP);  /*w1 w1*/
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_march_lr (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2; 

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->cfg_base_row_dir = 1;  /*up*/
    ctx->cfg_base_col_dir = 1;  /*up*/
    ctx->cfg_base_bank_dir = 1;  /*up*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        EXMBIST_arrert(uiret);
        return EXMBIST_ERR_CODE_ID_22;
    }
    
    EXMBIST_msleep((u32)(get_random_number()));

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        EXMBIST_arrert(uiret);
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_march_g (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_26;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_march_la (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}



exmbist_uint32 exm_algo_march_sr (ExmCtx * ctx, exmbist_uint32 dpat) {
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;


    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->cfg_base_row_dir = 1;  /*up*/
    ctx->cfg_base_col_dir = 1;  /*up*/
    ctx->cfg_base_bank_dir = 1;  /*up*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    EXMBIST_msleep((u32)(get_random_number()));

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

   exm_util_reset_cfg(ctx);
   return uiret;
}


exmbist_uint32 exm_algo_march_raw (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 6;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 5, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_march_ss (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 5;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 4, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_march_u (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    EXMBIST_msleep((u32)(get_random_number()));

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 4;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 3, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_25;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_movi (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    printk(KERN_ERR "exm_algo_movi\n");

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->cfg_base_row_dir = 1;  /*up*/
    ctx->cfg_base_col_dir = 1;  /*up*/
    ctx->cfg_base_bank_dir = 1;  /*up*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    ctx->cfg_base_row_dir = 0;  /*down*/
    ctx->cfg_base_col_dir = 0;  /*down*/
    ctx->cfg_base_bank_dir = 0;  /*down*/
    (void) exm_drv_load_counter(ctx);

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    ctx->num_inst = 3;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void)exm_drv_set_inst(ctx, 2, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_24;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_ssn (ExmCtx * ctx, exmbist_uint32 back_ground_data)
{
    exmbist_uint32 uiret;
    exmbist_uint32 i,value,temp;

    ctx->cfg_alt_row_en = 0;
    ctx->cfg_alt_col_en = 0;
    ctx->cfg_alt_bank_en = 0;
    ctx->cfg_alt_addr_mode = EXMBIST_ALT_MODE_FIX;

    /*DDR data bus inv*/
    temp = back_ground_data;
    for(i = 0;i<ctx->data_blk;i++)
    {
        if(ctx->ddr_type == 0x1)
        {
            value = (temp & 0xffff) |((~temp & 0xffff)<< 16);/*lpddr4*/
        }
        else
        {
            value =temp & 0xffffffff;
        }
        ctx->cfg_base_pat[i] = value;
        //printk(KERN_ERR "cfg_base_pat[%d]= 0x%x\n",i,ctx->cfg_base_pat[i]);
        temp = ~temp;
    }

    ctx->cfg_alt_fix_addr = 0;

    exm_drv_full_set(ctx);

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_A_ALT,EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0*/
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_EN | EXMBIST_I_A_INV | EXMBIST_I_A_ALT, EXMBIST_I_NULL,EXMBIST_I_JMP_0);  /*w0 addr inv */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    ctx->num_inst = 2;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_ALT, EXMBIST_I_NULL);  /*r0*/
    (void)exm_drv_set_inst(ctx, 1, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_A_INV | EXMBIST_I_A_ALT, EXMBIST_I_JMP_0);  /*r0 addr inv */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


exmbist_uint32 exm_algo_mscan (ExmCtx * ctx, exmbist_uint32 dpat)
{
    exmbist_uint32 uiret;
    exmbist_uint32 EXMBIST_I_D_DPAT = dpat<<2;

    printk(KERN_ERR "exm_algo_mscan\n");

    exm_drv_full_set(ctx);

    ctx->num_inst = 1;
    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_20;
    }

    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r0 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_21;
    }

    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL, EXMBIST_I_NULL);  /*w1*/
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_22;
    }

    (void)exm_drv_set_inst(ctx, 0, EXMBIST_I_NULL, EXMBIST_I_EN | EXMBIST_I_D_INV | EXMBIST_I_D_DPAT, EXMBIST_I_NULL);  /*r1 */
    (void) exm_drv_load_instruction(ctx);
    uiret = exm_util_wait_bist_pass(ctx);
    if(EXMBIST_OK != uiret){
        return EXMBIST_ERR_CODE_ID_23;
    }

    exm_util_reset_cfg(ctx);
    return uiret;
}


static exmbist_uint32 exm_algo_run_single (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;

    //EXMBIST_info("ctx->cfg_itl_en =0x%x\n",ctx->cfg_itl_en);
    if(ctx->cfg_itl_en == 1) 
    {
        ctx->cfg_min_addr = (ctx->cfg_min_addr>>ctx->cfg_bank_bits)<<ctx->cfg_bank_bits;
        ctx->cfg_max_addr = (ctx->cfg_max_addr>>ctx->cfg_bank_bits)<<ctx->cfg_bank_bits;//XXXX
    }

    switch(ctx->algo_id){
        case EXMBIST_TS_SIMPLE_WR:
            uiret = exm_algo_simple_wr(ctx,0);
            break;
        case EXMBIST_TS_SIMPLE_RD:
            uiret = exm_algo_simple_rd(ctx,0);
            break;
        case EXMBIST_TS_ALGO_MARCHCMINUS:
            uiret = exm_algo_marchcminus(ctx,0);
            break;
        case EXMBIST_TS_ALGO_BUTTERFLY:
            uiret = exm_algo_butterfly(ctx);
            break;
        case EXMBIST_TS_ALGO_SURROUND:
            uiret = exm_algo_surround(ctx);
            break;
        case EXMBIST_TS_ALGO_3STEP:
            uiret = exm_algo_3step(ctx,0x0,0x1);
            break;
        case EXMBIST_TS_ALGO_ADDR_PRBS7:
            uiret = exm_algo_march_addr_prbs(ctx,0x0,0x1);
            break;
        case EXMBIST_TS_ALGO_ADDR_PRBS15:
            uiret = exm_algo_march_addr_prbs(ctx,0x2,0x1);
            break;
        case EXMBIST_TS_ALGO_DATA_PRBS:
            uiret = exm_algo_dbus_prbs(ctx);
            break;
        case EXMBIST_TS_ALGO_BOOT:
            uiret = exm_algo_boot_test(ctx);
            break;
        case EXMBIST_TS_ALGO_DATA_WALK_SHIFT:
            uiret = exm_algo_dbus_walk(ctx,EXMBIST_I_D_WALK);
            break;
        case EXMBIST_TS_ALGO_DATA_WALK_CHK:
            uiret = exm_algo_dbus_walk(ctx,EXMBIST_I_D_CHK);
            break;
        case EXMBIST_TS_ALGO_DATA_WALK_RBAR:
            uiret = exm_algo_dbus_walk(ctx,EXMBIST_I_D_RBAR);
            break;
        case EXMBIST_TS_ALGO_DATA_WALK_CBAR:
            uiret = exm_algo_dbus_walk(ctx,EXMBIST_I_D_CBAR);
            break;
        case EXMBIST_TS_ALGO_MARCH_LA:
            uiret = exm_algo_march_la(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_SR:
            uiret = exm_algo_march_sr(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_RAW:
            uiret = exm_algo_march_raw(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_SS:
            uiret = exm_algo_march_ss(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_U:
            uiret = exm_algo_march_u(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_SL:
            uiret = exm_algo_march_sl(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_LR:
            uiret = exm_algo_march_lr(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MARCH_G:
            uiret = exm_algo_march_g(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MOVI:
            uiret = exm_algo_movi(ctx,EXMBIST_I_D_CONST);
            break;

        case EXMBIST_TS_ALGO_SSN:
            uiret = exm_algo_ssn(ctx,EXMBIST_I_D_CONST);
            break;
        case EXMBIST_TS_ALGO_MSCAN:
            uiret = exm_algo_mscan(ctx,EXMBIST_I_D_CONST);
            break;

        default:
            uiret = EXMBIST_ERR_CODE_ID_17;
            break;
    }
    if(EXMBIST_OK != uiret)
    {
         EXMBIST_arrert(uiret);
    }

   return uiret;
}


exmbist_uint32 exm_algo_run_loop (ExmCtx * ctx) 
{
    exmbist_uint32 uiret = EXMBIST_OK;
    exmbist_uint32 i;

    for(i=0;i<ctx->loop_cnt;i++)
    {
        ctx->loop_id = i+1;
        EXMBIST_info("algo_run loop=%d/%d\n",ctx->loop_id,ctx->loop_cnt);
        
        uiret = exm_algo_run_single (ctx);
        
        if(EXMBIST_OK != uiret)
        {
            if(EXMBIST_ERR_CODE_ID_14 == uiret)
            {
                return EXMBIST_ERR_CODE_ID_14;
            }
            return EXMBIST_ERR_CODE_ID_16;
        }
    }

    return uiret;

}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
