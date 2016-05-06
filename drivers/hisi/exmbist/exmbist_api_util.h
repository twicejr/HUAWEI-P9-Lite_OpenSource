#ifndef __EXMBIST_API_UTIL_H__
#define __EXMBIST_API_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */


/*utilities functions*/
//unsigned int random(unsigned int seed);
void exm_util_init_array(exmbist_uint32 array[],exmbist_uint32 length,exmbist_uint32 data);

/********************************************************************************
 Function  Description: used to fill BIST pattern.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        p: point to the data pattern array
                        b_rand: control how to create data pattern, val or rand()
                        val: data variable
********************************************************************************/
exmbist_uint32 exm_util_fill_pattern (ExmCtx * ctx, exmbist_uint32 * p, exmbist_uint32 b_rand, exmbist_uint32 val);

/********************************************************************************
 Function  Description: used to check BIST configuration.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
//exmbist_uint32 exm_util_check_cfg(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to get the error diag count in fifo.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_util_get_error_num(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to display the error diag information
 Parameter Description: diag: point to the single diag info structure.
                        ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_util_display_ExmDiag(ExmCtx * ctx, ExmDiag * diag);

/********************************************************************************
 Function  Description: used to printf configurations of Exmbist.
                        get from commands EXMBIST_CMD_GET_CFG0,EXMBIST_CMD_GET_CFG1,
                        EXMBIST_CMD_GET_CFG2,EXMBIST_CMD_GET_CFG3.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
//exmbist_uint32 exm_util_print_cfg(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to print Exmbist_status.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_util_print_status(ExmCtx * ctx);

/********************************************************************************
 Function Description: used to wait exmbist test pass.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_util_wait_bist_pass (ExmCtx * ctx);

/********************************************************************************
 Function Description: used to wait bist ready for test.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
//exmbist_uint32 exm_util_wait_bist_ready (ExmCtx * ctx) ;

/********************************************************************************
 Function  Description: used to reset the configurations.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
void exm_util_reset_cfg (ExmCtx * ctx);

/********************************************************************************
 Function Description: used to get bist status.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_util_get_bist_status (ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to init drv.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
//exmbist_uint32 exm_util_drv_init (ExmCtx * ctx);
/********************************************************************************
 Function  Description: used to stop mbist testing(software)
 Parameter Description: ctx: a pointer which point to an pointer of ExmCtx type
                        structure. please refer to "exmbist_api_datatype.h" for
                        more detailed description.
 ********************************************************************************/
//exmbist_uint32 exm_util_stop(ExmCtx * ctx);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
