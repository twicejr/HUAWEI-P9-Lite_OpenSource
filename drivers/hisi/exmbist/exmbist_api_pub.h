#ifndef __EXMBIST_API_PUB_H__
#define __EXMBIST_API_PUB_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include <linux/printk.h>

typedef unsigned int  exmbist_uint32;
typedef long long     exmbist_uint64;

#define EXMBIST_info      printk
#define EXMBIST_error     printk


#define EXMBIST_arrert(x)  printk(KERN_ERR "ERROR:File:%s,Line:%d,ERROR_TYPE:%d\n",__FILE__,__LINE__,x)


#define EXMBIST_OK  (0)

#define EXMBIST_POINTER_CHECK(ptr,ErrCode)\
do{\
    if(NULL == (ptr))\
    {\
        EXMBIST_arrert(ErrCode);\
        printk(KERN_ERR "r\nERROR:pointer is NULL!");\
        return ErrCode;\
    }\
}while(0)

/********************************************************************************
 define exmbist error id
 ********************************************************************************/
typedef enum EXMBIST_ERR_CODE_ID
{
    EXMBIST_ERR_CODE_ID_01 = 0x1,/*init流程，ctx指针为空*/
    EXMBIST_ERR_CODE_ID_02,      /*init流程，wr_cmd_p指针为空*/
    EXMBIST_ERR_CODE_ID_03,      /*init流程，wr_din_p指针为空*/
    EXMBIST_ERR_CODE_ID_04,      /*init流程，rd_dout_p指针为空*/
    EXMBIST_ERR_CODE_ID_05,      /*init流程，rd_status_p指针为空*/
    EXMBIST_ERR_CODE_ID_06,      /*init流程，cfg_base_pat指针为空*/
    EXMBIST_ERR_CODE_ID_07,      /*init流程，cfg_alt_pat指针为空*/
    EXMBIST_ERR_CODE_ID_08,      /**/
    EXMBIST_ERR_CODE_ID_09,      /*close流程，close前没有init*/
    EXMBIST_ERR_CODE_ID_10,      /*cmd流程，cmd前exmbist没有初始化*/
    EXMBIST_ERR_CODE_ID_11,      /*cmd流程，cmd异常*/
    EXMBIST_ERR_CODE_ID_12,      /*parity error*/
    EXMBIST_ERR_CODE_ID_13,      /*watchdog error*/
    EXMBIST_ERR_CODE_ID_14,      /**/
    EXMBIST_ERR_CODE_ID_15,      /*algo流程，algo前没有init*/
    EXMBIST_ERR_CODE_ID_16,      /*algo流程，exm_algo_run_single出错*/
    EXMBIST_ERR_CODE_ID_17,      /*algo流程，algo id 错误*/
    EXMBIST_ERR_CODE_ID_18,      /*保留*/
    EXMBIST_ERR_CODE_ID_19,      /*保留*/
    EXMBIST_ERR_CODE_ID_20,      /*algo 第1步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_21,      /*algo 第2步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_22,      /*algo 第3步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_23,      /*algo 第4步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_24,      /*algo 第5步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_25,      /*algo 第6步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_26,      /*algo 第7步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_27,      /*algo 第8步wait_bist_pass返回值异常*/
    EXMBIST_ERR_CODE_ID_MAX_NUM
}EXMBIST_ERR_CODE_ID_E;

/**************************************************************************************
 macro for write/read operation defines.
***************************************************************************************/
#define EXMBIST_I_NULL     0x0          /*disable*/
#define EXMBIST_I_EN       0x1          /*enable*/
#define EXMBIST_I_A_ALT    0x2          /*alt address*/
#define EXMBIST_I_A_INV    0x20         /*address inversion*/
#define EXMBIST_I_D_INV    0x40         /*data inversion*/
#define EXMBIST_I_D_CONST  0x0          /*data pattern:constant pattern*/
#define EXMBIST_I_D_CHK    0x4          /*data pattern:checker board*/
#define EXMBIST_I_D_RBAR   0x8          /*data pattern:row bar*/
#define EXMBIST_I_D_CBAR   0xC          /*data pattern:col bar*/
#define EXMBIST_I_D_PBUF   0x10         /*patbuf (obsolete)*/
#define EXMBIST_I_D_WALK   0x10         /*shift base pat*/
#define EXMBIST_I_D_PRBS   0x14         /*data pattern:prbs*/
#define EXMBIST_I_D_ALT    0x18         /*data pattern:alt data*/
#define EXMBIST_I_JMP_0    0x1          /*jump destination instruction 0*/
#define EXMBIST_I_JMP_1    0x3          /*jump destination instruction 1*/
#define EXMBIST_I_JMP_2    0x5          /*jump destination instruction 2*/
#define EXMBIST_I_JMP_3    0x7          /*jump destination instruction 3*/
#define EXMBIST_I_JMP_4    0x9          /*jump destination instruction 4*/
#define EXMBIST_I_JMP_5    0xb          /*jump destination instruction 5*/
#define EXMBIST_I_JMP_6    0xd          /*jump destination instruction 6*/
#define EXMBIST_I_JMP_7    0xf          /*jump destination instruction 7*/
#define EXMBIST_I_REP      0x10         /*repeate enable*/


/**************************************************************************************
 macro for address sweep direction.
***************************************************************************************/
#define EXMBIST_DIR_UP   1         /*address sweep up direction */
#define EXMBIST_DIR_DOWN 0         /*address sweep down direction*/
#define EXMBIST_DIR_DISABLE -1     /*address sweep disable*/

/**************************************************************************************
 macro for alt address mode.
***************************************************************************************/
#define EXMBIST_ALT_MODE_BUTTERFLY      0    /*butterfly(E->S->W->N neighbors of the base addr)*/
#define EXMBIST_ALT_MODE_SURROUND       1    /*surrounding(E->SE->S->SW->W->NW->N->NE neighbors of the base addr)*/
#define EXMBIST_ALT_MODE_ONE_BIT_INVERT 2    /*one bit invert(flop 1 bit of base addr each time,from LSB to MSB)*/
#define EXMBIST_ALT_MODE_PRBS           3    /*prbs(use prbs sequence as the alt address)*/
#define EXMBIST_ALT_MODE_FIX            4    /*fixed mode(use CFG_ALT_FIX_ADDR as the alt address)*/
#define EXMBIST_ALT_MODE_PRBS_LA        5    /*prbs look ahead(ues prbs look-ahead sequence as the alt address)*/

/*****************************************************************************************
 macro for algo_id
******************************************************************************************/
#define EXMBIST_TS_SIMPLE_WR                    0x1
#define EXMBIST_TS_SIMPLE_RD                    0x2
#define EXMBIST_TS_ALGO_MARCHCMINUS             0x4
#define EXMBIST_TS_ALGO_BUTTERFLY               0x8
#define EXMBIST_TS_ALGO_SURROUND                0x10
#define EXMBIST_TS_ALGO_3STEP                   0x20
#define EXMBIST_TS_ALGO_ADDR_PRBS7              0x40
#define EXMBIST_TS_ALGO_ADDR_PRBS15             0x80
#define EXMBIST_TS_ALGO_DATA_PRBS               0x100
#define EXMBIST_TS_ALGO_BOOT                    0x200
#define EXMBIST_TS_ALGO_DATA_WALK_SHIFT         0x400
#define EXMBIST_TS_ALGO_DATA_WALK_CHK           0x800
#define EXMBIST_TS_ALGO_DATA_WALK_RBAR          0x1000
#define EXMBIST_TS_ALGO_DATA_WALK_CBAR          0x2000
#define EXMBIST_TS_ALGO_MARCH_LA                0x4000
#define EXMBIST_TS_ALGO_MARCH_SR                0x8000
#define EXMBIST_TS_ALGO_MARCH_RAW               0x10000
#define EXMBIST_TS_ALGO_MARCH_SS                0x20000
#define EXMBIST_TS_ALGO_MARCH_U                 0x40000
#define EXMBIST_TS_ALGO_MARCH_SL                0x80000
#define EXMBIST_TS_ALGO_MARCH_LR                0x100000
#define EXMBIST_TS_ALGO_MARCH_G                 0x200000
#define EXMBIST_TS_ALGO_SSN                     0x400000
#define EXMBIST_TS_ALGO_MOVI                    0x800000
#define EXMBIST_TS_ALGO_MSCAN                   0x1000000
#define EXMBIST_TS_ALGO_ID_MAX                  0x2000000
/*****************************************************************************************
 macro for ctx->status_code
 used to record the error information during the mbist test
******************************************************************************************/
#define EXMBIST_STATUS_CODE_RUN_DEADLOCK          0x1
#define EXMBIST_STATUS_CODE_CHECK_ERROR           0x2
#define EXMBIST_STATUS_CODE_PARITY_ERROR          0x4
#define EXMBIST_STATUS_CODE_WATCHDOG_ERROR        0x8
#define EXMBIST_STATUS_CODE_FINGERPRINT_ERROR     0x10
#define EXMBIST_STATUS_CODE_INJECT_ERROR          0x20
//#define EXMBIST_STATUS_CODE_STOP                  0x40
//#define EXMBIST_STATUS_CODE_MALLOC_ERROR          0x80
#define EXMBIST_STATUS_CODE_INITIAL_ERROR         0x100
#define EXMBIST_STATUS_CODE_CFG_ERROR             0x200
#define EXMBIST_STATUS_CODE_DONE                  0x400
#define EXMBIST_STATUS_CODE_INITIAL_OK            0x800/*before run api_run or set_cmd must check api_init is runing before*/
#define EXMBIST_STATUS_CODE_RUN_COMPLETE          0x80000000

/*************************************************
 THREE STEP  Init Data configure of dataline walk
***************************************************/

#define EXMBIST_DDR_BITS_DEFAULT_INIT_WALK1_DATA   0x1
#define EXMBIST_DDR_BITS_DEFAULT_INIT_WALK0_DATA   0xfffffffe

/********************************************************************************
 macro for config commands
 write commands, used to config exmbist
 ********************************************************************************/
#define EXMBIST_CMD_FULL_RST                 0x00  /*purposely set bit 7 to 0 so we know it is a write command*/
#define EXMBIST_CMD_HALF_RST                 0x01
#define EXMBIST_CMD_SET_ADDR_RANGE           0x11
#define EXMBIST_CMD_SET_ROW_COL_BANK_BITS    0x12
#define EXMBIST_CMD_SET_BASE_PAT             0x13
#define EXMBIST_CMD_SET_ALT_PAT              0x14
#define EXMBIST_CMD_SET_REPEAT_CNT           0x15
#define EXMBIST_CMD_SET_DIAG_CNT             0x16
#define EXMBIST_CMD_SET_LOOP_EN              0x17
#define EXMBIST_CMD_SET_ITL                  0x18
#define EXMBIST_CMD_SET_COMP_MSK             0x19
#define EXMBIST_CMD_LOAD_INST                0x20
#define EXMBIST_CMD_SET_ADDR_CNT             0x21
#define EXMBIST_CMD_LOAD_ROTATE              0x22
#define EXMBIST_CMD_SET_BANK_MAP             0x23
#define EXMBIST_CMD_LOAD_PATBUF              0x24
#define EXMBIST_CMD_LOAD_PATMAP              0x25
#define EXMBIST_CMD_DIAG_FIFO_ADVANCE        0x26
#define EXMBIST_CMD_SEL_PRBS                 0x27
#define EXMBIST_CMD_SET_ADDR_PRBS_SEED       0x28
#define EXMBIST_CMD_SET_GLOBAL_INORDER       0x29
#define EXMBIST_CMD_SET_ALT_FIX_ADDR         0x30
#define EXMBIST_CMD_SET_DAT_PRBS_BIT_INV     0x31
#define EXMBIST_CMD_SET_ADDR_PRBS_BIT_INV    0x32
#define EXMBIST_CMD_DOUT_STB                 0x7f  /*change the output value of _dout*/

#define EXMBIST_CMD_SET_SAME_BASE_PAT        0x100  /*just to sample cmd*/
#define EXMBIST_CMD_SET_TEST_SUBSYS_DMC_RANK 0x101  /*change rank*/
/********************************************************************************
 macro for GET STATUS DIAG OR CFG
 read commands, used to get the configuration of the mbist
 ********************************************************************************/
#define EXMBIST_CMD_GET_DIAG_INFO            0x40
#define EXMBIST_CMD_GET_RUN_STATUS           0x41
#define EXMBIST_CMD_GET_CFG                  0x42
#define EXMBIST_CMD_WAIT_BIST_PASS           0x43 //add
/********************************************************************************
 macro for observe commands
 read commands, used to get the configuration of the mbist
 ********************************************************************************/
#define EXMBIST_CMD_GET_DIAG_ADDR            0x80  /*purposely set bit 7 to 1 so we know it is a read command*/
#define EXMBIST_CMD_GET_DIAG_ACTUAL          0x81
#define EXMBIST_CMD_GET_DIAG_EXP             0x82
#define EXMBIST_CMD_GET_FAIL_CNT             0x83
#define EXMBIST_CMD_GET_CFG0                 0x84
#define EXMBIST_CMD_GET_CFG1                 0x85
#define EXMBIST_CMD_GET_CFG2                 0x86
#define EXMBIST_CMD_GET_CFG3                 0x87

/**************************************************************************************
  _exm_inst_field_: instruction structure.
                    the write/read operation defines a write/read request,respectively.
                    EXMBIST CAN hold up to 8 instructions.
***************************************************************************************/
typedef struct _exm_inst_field_ {
    exmbist_uint32 wr_en       : 1; /*0, enables write request*/
    exmbist_uint32 wr_is_alt   : 1; /*1, 1-request is for the alt address;0-request is for the base address*/
    exmbist_uint32 wr_dat      : 3; /*4:2, data pattern selector*/
    exmbist_uint32 wr_addr_inv : 1; /*5, address inversion*/
    exmbist_uint32 wr_dat_inv  : 1; /*6, data inversion*/
    exmbist_uint32 wr_rsvd     : 1; /*7, reserved for future use*/

    exmbist_uint32 rd_en       : 1; /*0, enables read request*/
    exmbist_uint32 rd_is_alt   : 1; /*1, 1-request is for the alt address;0-request is for the base address*/
    exmbist_uint32 rd_dat      : 3; /*4:2, data pattern selector*/
    exmbist_uint32 rd_addr_inv : 1; /*5, address inversion*/
    exmbist_uint32 rd_dat_inv  : 1; /*6, data inversion*/
    exmbist_uint32 rd_rsvd     : 1; /*7, reserved for future use*/

    exmbist_uint32 j_en        : 1; /*0, jump enable*/
    exmbist_uint32 j_ip        : 3; /*3:1, jump destination instruction,meaningful when j_en=1*/
    exmbist_uint32 rep_en      : 1; /*4, instruction repeate enable*/
    exmbist_uint32 last        : 1; /*5, indicate the last instruction*/
    exmbist_uint32 exec_rsvd   : 1; /*6, reserved for future use*/
} ExmInstField;
/*****************************************************************************************
_exm_inst_: union of instruction
******************************************************************************************/
typedef union _exm_inst_ {
    exmbist_uint32 w;
    ExmInstField f;
} ExmInst;

/********************************************************************************
  _exm_diag_ : an important structure ExmDiag.
               the structure is used to record the information when detected a
               fault during the mbist testing.
********************************************************************************/
typedef struct _exm_diag_ {
    exmbist_uint32 algo_id;     /*algoriehm id 指示此节点表示的错误是哪个算法ID检测出的*/
    exmbist_uint32 stage_id;    /*test stage index in algorithm 指示此节点表示的错误是算法的哪个stage检测出的*/
    exmbist_uint32 error_cnt;   /*totoal number of errors detected of this run当前stage发现的错误的计数*/
    exmbist_uint32 error_id;    /*error index指示此节点是存储在EXMBIST中的第几个错误*/
    exmbist_uint32 loop_id;     /*指示此节点表示的错误是在哪轮运行中发现的*/

    exmbist_uint32 addr;        /*the address of the test fault指示此节点发现的错误的地址，
                                  地址格式是{row_addr, col_addr, bank_addr}*/
    exmbist_uint32 * expect;    /*point to the expect data array记录此节点的预期数据*/
    exmbist_uint32 * actual;    /*point to the actual data array记录此节点的实际数据*/
    exmbist_uint32 ip;          /*instruction # that catches the current fault(in the diag FIFO) 指示此节点发现的错误是stage中哪个操作发现的*/

} ExmDiag;

/********************************************************************************
  _exm_ctx_ : an important structure ExmCtx.
              the structure is mirror of EXMBIST, includes hardware configuration,
              software configuration, test status, test result...
********************************************************************************/
typedef struct _exm_ctx_ {

    /*ddr subsysterm information*/
    exmbist_uint32 ddr_type;          /*0 lpddr3,1 lpddr4*/
    exmbist_uint32 density;
    exmbist_uint32 subsys_num_max;
    exmbist_uint32 dmc_num_max;
    exmbist_uint32 rank_num_max;
    exmbist_uint32 data_blk;          /*256/32=8 word,bust*/
    
    /*ICP register status*/
    exmbist_uint32 algo_id;           /*algorithm id */
    exmbist_uint32 stage_id;          /*test stage index in algorithm */
    exmbist_uint32 status_code;       /*exmbist test status*/

    /*status fields*/
    exmbist_uint32 cycle_count;       /*number of iterations that have been executed,meaningful when CFG_LOOP_EN=1*/
    exmbist_uint32 finger_print;      /*used for sanity check*/
    exmbist_uint32 diag_ip;           /*instruction # that catches the current fault(in the diag FIFO)*/
    exmbist_uint32 diag_fifo_last;    /*0/1: not/have reached the last element in the DIAG FIFO*/
    exmbist_uint32 watchdog_err;      /*0:not fired; 1:watchdog error fired*/
    exmbist_uint32 parity_err;        /*0:no parity error; 1:parity error detected on the internal FIFOs*/
    exmbist_uint32 bist_pass;         /*0:found errors; 1:test passed, no errors found*/
    exmbist_uint32 bist_done;         /*0:current execution in progress or never started; 1:current execution finished*/

    /*meta data*/
    exmbist_uint32 error_cnt;         /*totoal number of errors detected of this run*/
    exmbist_uint32 error_id;          /*error index*/

    /*runtime config parameters*/
    exmbist_uint32 cfg_rep_cnt;           /*runtime configuration:repeat count */
    exmbist_uint32 cfg_loop_en;           /*runtime configuration:loop enable */
    exmbist_uint32 cfg_itl_en;            /*runtime configuration:interleave enable*/
    exmbist_uint32 cfg_itl_bits;          /*runtime configuration:interleave width*/
    exmbist_uint32 cfg_itl_mode;          /*runtime configuration:interleave mode, controls the data inversion frequency during interleaving */
    exmbist_uint32 cfg_max_addr;          /*test max address*/
    exmbist_uint32 cfg_min_addr;          /*test min address*/
    exmbist_uint32 cfg_col_bits;          /*runtime configuration:col address width*/
    exmbist_uint32 cfg_row_bits;          /*runtime configuration:row address width*/
    exmbist_uint32 cfg_bank_bits;         /*runtime configuration:bank address width*/
    exmbist_uint32 cfg_row_col_bits;      /*runtime configuration:row address width + col address width*/
    exmbist_uint32 cfg_row_col_bank_bits; /*runtime configuration:row address width + col address width + bank address width*/
    exmbist_uint32 cfg_base_row_dir;      /*base row address sweep direction*/
    exmbist_uint32 cfg_base_col_dir;      /*base col address sweep direction*/
    exmbist_uint32 cfg_base_bank_dir;     /*base bank address sweep direction*/
    exmbist_uint32 cfg_row_fast_mode;     /*1:first increment row address then column address; 0:first increment column address then row address*/
    exmbist_uint32 cfg_half_addr_mode;    /*1:only test [CFG_MIN_ADDR,CFG_MAX_ADDR>>1]; 0:test [CFG_MIN_ADDR,CFG_MAX_ADDR],default 0*/
    exmbist_uint32 cfg_base_plustwo_mode; /*1:increment base address by 2 each time; 0:increment base address by 1 each time*/
    exmbist_uint32 cfg_base_row_off;      /*offset the beginning value the base row address by +1 or -1,determined by CFG_BASE_ROW_DIR*/
    exmbist_uint32 cfg_base_col_off;      /*offset the beginning value the base row address by +1 or -1,determined by CFG_BASE_COL_DIR*/
    exmbist_uint32 cfg_alt_addr_mode;     /*alt address mode:butterfly,surrounding,ont bit invert,prbs,fixed mode,prbs look ahead*/
    exmbist_uint32 cfg_alt_row_en;        /*set alt row address sweep direction*/
    exmbist_uint32 cfg_alt_col_en;        /*set alt column address sweep direction*/
    exmbist_uint32 cfg_alt_bank_en;       /*set alt bank address sweep direction*/
    exmbist_uint32 cfg_diag_cnt;          /*diag counter length*/
    exmbist_uint32 cfg_scr_bit_sel;       /*reserved*/
    exmbist_uint32 cfg_addr_prbs_seed;    /*select address prbs seed*/
    exmbist_uint32 cfg_addr_prbs_sel;     /*select which prbs generator to use for the address bus*/
    exmbist_uint32 cfg_addr_prbs_skew;    /*0:all address bus lines are aligned,driven by output tap 0 of the prbs generator*/
                               /*1:all address bus lines are 1-bit skewed,driven by all the output taps of the prbs generator*/
    exmbist_uint32 cfg_addr_prbs_bit_inv; /*select address prbs bit inversion*/
    exmbist_uint32 cfg_alt_fix_addr;      /*alt fixed address*/
    exmbist_uint32 cfg_global_inorder;    /*add by wls for global test*/

    exmbist_uint32 loop_cnt;              /*add by liqixin for algo loop.loop count*/
    exmbist_uint32 loop_id;               /*add by liqixin for algo loop.loop index*/

    /*diag data read from IP*/
    exmbist_uint32 diag_fail_cnt;         /*diag fail number*/

    exmbist_uint32 addr_ratio;     /*used for reduce addr range*/
    exmbist_uint32 num_inst;       /*number of instructions*/

    /*io function pointer*/
    exmbist_uint32 (*exm_io_wr_cmd_p) (exmbist_uint32);
    exmbist_uint32 (*exm_io_wr_din_p) (exmbist_uint32);
    exmbist_uint32 (*exm_io_rd_dout_p) (void);
    exmbist_uint32 (*exm_io_rd_status_p) (void);

    exmbist_uint32 *cfg_base_pat; /*point to the base data pattern*/
    exmbist_uint32 *cfg_alt_pat;  /*point to the alt data pattern*/

    ExmInst inst[8];               /*ExmInst type instruction array*/
} ExmCtx;


extern void msleep(unsigned int);
#define EXMBIST_msleep(ms) msleep(ms)
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
