#ifndef __EXMBIST_API_DRV_H__
#define __EXMBIST_API_DRV_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

/*******************************************************************************
Define struct for reference "cmd_para" of function exmbist_set_cmd.
For example, ExmCmdSetAddrRange is the struct for parameter of command
"EXMBIST_CMD_SET_ADDR_RANGE".
********************************************************************************/
typedef struct _exm_cmd_set_addr_range_ {
    exmbist_uint32 cfg_min_addr;
    exmbist_uint32 cfg_max_addr;
} ExmCmdSetAddrRange;

typedef struct _exm_cmd_set_row_col_bank_bits_ {
    exmbist_uint32 cfg_row_bits;
    exmbist_uint32 cfg_col_bits;
    exmbist_uint32 cfg_bank_bits;
} ExmCmdSetRowColBankBits;

typedef struct _exm_cmd_set_repeat_cnt_ {
    exmbist_uint32 cfg_rep_cnt;
} ExmCmdSetRepeatCnt;

typedef struct _exm_cmd_set_diag_cnt_ {
    exmbist_uint32 cfg_diag_cnt;
} ExmCmdSetDiagCnt;

typedef struct _exm_cmd_set_loop_en_ {
    exmbist_uint32 cfg_loop_en;
} ExmCmdSetLoopEn;

typedef struct _exm_cmd_set_itl_ {
    exmbist_uint32 cfg_itl_en;
    exmbist_uint32 cfg_itl_bits;
    exmbist_uint32 cfg_itl_mode;
} ExmCmdSetItl;

typedef struct _exm_cmd_load_inst_ {
    exmbist_uint32 cfg_operation;
    exmbist_uint32 cfg_execution_last;
} ExmCmdLoadInst;

typedef struct _exm_cmd_set_addr_cnt_ {
    exmbist_uint32 cfg_alt_bank_en      ;
    exmbist_uint32 cfg_alt_col_en       ;
    exmbist_uint32 cfg_alt_row_en       ;
    exmbist_uint32 cfg_alt_addr_mode    ;
    exmbist_uint32 cfg_base_col_off     ;
    exmbist_uint32 cfg_base_row_off     ;
    exmbist_uint32 cfg_base_plustwo_mode;
    exmbist_uint32 cfg_half_addr_mode   ;
    exmbist_uint32 cfg_row_fast_mode    ;
    exmbist_uint32 cfg_base_bank_dir    ;
    exmbist_uint32 cfg_base_col_dir     ;
    exmbist_uint32 cfg_base_row_dir     ;
} ExmCmdSetAddrCnt;

typedef struct _exm_cmd_set_bank_map_ {
    exmbist_uint32 cfg_logic_bank;
    exmbist_uint32 cfg_phy_bank;
} ExmCmdSetBankMap;

typedef struct _exm_cmd_select_prbs_ {
    exmbist_uint32 cfg_addr_prbs_skew;
    exmbist_uint32 cfg_addr_prbs_sel;
} ExmCmdSelectPrbs;

typedef struct _exm_cmd_set_addr_prbs_seed_ {
    exmbist_uint32 cfg_addr_prbs_seed;
} ExmCmdSetAddrPrbsSeed;

typedef struct _exm_cmd_set_global_inorder_ {
    exmbist_uint32 cfg_global_inorder;
} ExmCmdSetGlobalInorder;

typedef struct _exm_cmd_set_alt_fix_addr_ {
    exmbist_uint32 cfg_alt_fix_addr;
} ExmCmdSetAltFixAddr;

typedef struct _exm_cmd_set_addr_prbs_bit_inv_ {
    exmbist_uint32 cfg_addr_prbs_bit_inv;
} ExmCmdSetAddrPrbsBitInv;


/********************************************************************************
 Function  Description: IO interface,
                        used to load commands,configurations and instructions into
                        ExmBIST.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        cmd: command id
********************************************************************************/
exmbist_uint32 exm_io_wr_cmd(ExmCtx * ctx, exmbist_uint32 cmd);

/********************************************************************************
 Function  Description: IO interface,
                        used to load configurations into ExmBIST after a config
                        command is loaded by the CMD register.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        din: command parameter.
********************************************************************************/
exmbist_uint32 exm_io_wr_din(ExmCtx *ctx, exmbist_uint32 din);

/********************************************************************************
 Function  Description: IO interface,
                        used to get ExmBIST test status.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_io_rd_status(ExmCtx * ctx);

/********************************************************************************
 Function Description: IO interface,
                       used to observe data from ExmBIST after a observe command
                       is loaded by the CMD register.

********************************************************************************/
exmbist_uint32 exm_io_rd_dout(ExmCtx *ctx);


/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_GLOBAL_INORDER
                        used to set global in-order mode enable.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_inorder (ExmCtx * ctx);

/********************************************************************************
 Function  Description: observe commands EXMBIST_CMD_GET_CFG0,EXMBIST_CMD_GET_CFG1,
                        EXMBIST_CMD_GET_CFG2,EXMBIST_CMD_GET_CFG3,
                        used to get configurations.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
//exmbist_uint32 exm_drv_get_cfg(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to get Exmbist_status by status register.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_get_status(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_FULL_RST
                        used to full reset Exmbist, clears all config registers,
                        stop execution(if any) and puts EXMBIST to ready state.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_full_reset(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to set the cfg same as default.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
void exm_drv_full_set(ExmCtx * ctx);
/********************************************************************************
 Function  Description: set command EXMBIST_CMD_HALF_RST
                        used to half reset Exmbist, same as FULL_RST, but keep all
                        config registers.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_half_reset(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ADDR_CNT
                        used to load address generation behavior configuration.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_load_counter(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ITL
                        used to set interleave mode.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_interleave(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_REPEAT_CNT
                        used to set repeat times.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_repeat_count(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_LOOP_EN
                        used to set loop mode enable.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_loop_en(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ROW_COL_BANK_BITS
                        used to set row,column and bank bit width.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_row_col_bank_bits(ExmCtx * ctx)
    ;
/********************************************************************************
 Function  Description: set command EXMBIST_CMD_LOAD_ROTATE
                        used to set addr rot dist.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_load_rotate (ExmCtx * ctx) ;

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_BANK_MAP
                        used to set bank address mapping.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        logic: logic bank
                        phy: physic bank
********************************************************************************/
//mbist_uint32 exm_drv_set_bank_map (ExmCtx * ctx, exmbist_uint32 logic, exmbist_uint32 phy) ;


/********************************************************************************
 Function  Description: used to reset bank address mapping.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
//mbist_uint32 exm_drv_reset_bank_map (ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_DIAG_CNT
                        used to set ignored failure number.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_diag_cnt(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ADDR_RANGE
                        used to set address range for testing.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_addr_range(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_BASE_PAT
                        used to set base data pattern.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_base_pattern(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ALT_PAT
                        used to set alt data pattern.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_alt_pattern(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_COMP_MSK
                        used to set comparison bit mask.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_compare_mask(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command  EXMBIST_CMD_LOAD_INST
                        used to load read/write instructions.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_load_instruction(ExmCtx * ctx);
/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SEL_PRBS
                        used to select PRBS generator.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_sel_prbs(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ADDR_PRBS_SEED
                        used to select address PRBS seed.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_addr_prbs_seed(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_SET_ALT_FIX_ADDR
                        used to set fixed value of the alt address.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_alt_fix_addr (ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to get diag information.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_get_diag(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to get single diag information.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
void exm_drv_get_single_diag(ExmCtx * ctx);

/********************************************************************************
 Function  Description: set command EXMBIST_CMD_DIAG_FIFO_ADVANCE
                        used to advance the DIAG FIFO read pointer by 1.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_diag_fifo_advance(ExmCtx * ctx);

/********************************************************************************
 Function Description: used to set base row/column/bank address sweep direction
                      (1=up,0=down).default 1.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        row: row direction
                        col: col direction
                        bank: bank direction
********************************************************************************/
exmbist_uint32 exm_drv_set_base_dir (ExmCtx * ctx, exmbist_uint32 row, exmbist_uint32 col, exmbist_uint32 bank);

/********************************************************************************
 Function  Description: used to set alt address mode and alt row/column/bank address
                        sweep direction.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        row: row direction
                        col: col direction
                        bank: bank direction
 ********************************************************************************/
exmbist_uint32 exm_drv_set_alt_dir (ExmCtx * ctx, exmbist_uint32 row, exmbist_uint32 col, exmbist_uint32 bank);

/********************************************************************************
 Function Description: used to set alt address mode.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        mode: alt address mode.
********************************************************************************/
exmbist_uint32 exm_drv_set_alt_mode (ExmCtx * ctx, exmbist_uint32 mode);

/********************************************************************************
 Function  Description: used to set instructions.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        id: instruction index
                        wr: write operation
                        rd: read operation
                        exec: execution ctrl.
********************************************************************************/
exmbist_uint32 exm_drv_set_inst (ExmCtx * ctx, exmbist_uint32 id, exmbist_uint32 wr, exmbist_uint32 rd, exmbist_uint32 exec);

/********************************************************************************
 Function  Description: used to malloc new diag structure.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        ip: instruction index
                        addr: error address
                        expect: point to expect data pattern
                        actual: point to actual data pattern
 ********************************************************************************/
ExmDiag * exm_drv_new_diag (ExmCtx * ctx, exmbist_uint32 ip, exmbist_uint32 addr, exmbist_uint32 * expect, exmbist_uint32 * actual);

/********************************************************************************
 Function Description: used to wait watchdog error.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_wait_watchdog_error(ExmCtx * ctx);

/********************************************************************************
 Function  Description: used to detect watchdog.
 Parameter Description: ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
                        addr_i: write/read address.
********************************************************************************/
exmbist_uint32 exm_drv_watchdog_detect(ExmCtx * ctx,exmbist_uint32 addr_i);

/********************************************************************************
 Function Description: used to detect config error when setting commands.
 Parameter Description: cmd: command id
                        cmd_para: a pointer which point to the parameter needed by
                                  special command
                        ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_cmd_check(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para);


/********************************************************************************
 Function Description: used to detect config error when setting commands.
 Parameter Description: cmd: command id
                        cmd_para: a pointer which point to the parameter needed by
                                  special command
                        ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_cmd_check1(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para);

/********************************************************************************
 Function Description: used to detect config error when setting commands.
 Parameter Description: cmd: command id
                        cmd_para: a pointer which point to the parameter needed by
                                  special command
                        ctx: a pointer which point to an ExmCtx type structure.
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.
********************************************************************************/
exmbist_uint32 exm_drv_set_cmd_check2(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para);

/********************************************************************************
 Function Description: used to set commands.
 Parameter Description: cmd: command id
                        cmd_para: a pointer which point to the parameter needed by
                                  special command
                        ctx: a pointer which point to an ExmCtx type structure,
                        please refer to "exmbist_api_datatype.h" for more detailed
                        description.

********************************************************************************/
exmbist_uint32 exm_drv_set_cmd1(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para);
exmbist_uint32 exm_drv_set_cmd2(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para);
exmbist_uint32 exm_drv_set_cmd(ExmCtx *ctx, exmbist_uint32 cmd, void *cmd_para);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
