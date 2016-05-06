// ******************************************************************************
//  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd.
//
// ******************************************************************************
// File name     : Reg_HEVC_H264.h
// Version       : 2.0
// Created       : 2014-10-28
// Last Modified : 
// Description   :  逻辑寄存器结构体
// Function List : 
// History       : 
// 1 Date        : 
// Author        : xxx
// Modification  : Create file
// ******************************************************************************

#ifndef __C_UNION_DEFINE_VEDU_REG_H__
#define __C_UNION_DEFINE_VEDU_REG_H__


/*-------------- Vcpi start  0x20620000 ---------------------*/ 

/* Define the union U_VEDU_INTSTAT_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_ve_eop_ns         : 1   ; /* [0]  */
        unsigned int    int_ve_buffull_ns     : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    int_ve_pbitsover_ns   : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    int_vedu_slice_end_ns : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    int_vedu_brkpt_ns     : 1   ; /* [16]  */
        unsigned int    int_vedu_step_ns      : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    int_vedu_timeout_ns   : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    int_cfg_err_ns        : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTSTAT_NS;

/* Define the union U_VEDU_INTMASK_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enable_ve_eop_ns      : 1   ; /* [0]  */
        unsigned int    enable_ve_buffull_ns  : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    enable_ve_pbitsover_ns : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    enable_vedu_slice_end_ns : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    enable_vedu_brkpt_ns  : 1   ; /* [16]  */
        unsigned int    enable_vedu_step_ns   : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    enable_vedu_timeout_ns : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    enable_cfg_err_ns     : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTMASK_NS;

/* Define the union U_VEDU_RAWINT_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rint_ve_eop_ns        : 1   ; /* [0]  */
        unsigned int    rint_ve_buffull_ns    : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    rint_ve_pbitsover_ns  : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    rint_vedu_slice_end_ns : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    rint_vedu_brkpt_ns    : 1   ; /* [16]  */
        unsigned int    rint_vedu_step_ns     : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    rint_vedu_timeout_ns  : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    rint_cfg_err_ns       : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RAWINT_NS;

/* Define the union U_VEDU_INTCLR_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clr_ve_eop_ns         : 1   ; /* [0]  */
        unsigned int    clr_ve_buffull_ns     : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    clr_ve_pbitsover_ns   : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    clr_vedu_slice_end_ns : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    clr_vedu_brkpt_ns     : 1   ; /* [16]  */
        unsigned int    clr_vedu_step_ns      : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    clr_vedu_timeout_ns   : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    clr_cfg_err_ns        : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTCLR_NS;

/* Define the union U_VEDU_START */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_vstart           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 15  ; /* [15..1]  */
        unsigned int    vcpi_vstep            : 1   ; /* [16]  */
        unsigned int    reserved_1            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_START;

/* Define the union U_VEDU_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_vedsel           : 1   ; /* [0]  */
        unsigned int    vcpi_lcu_time_sel     : 1   ; /* [1]  */
        unsigned int    vcpi_cfg_mode         : 1   ; /* [2]  */
        unsigned int    vcpi_protocol         : 2   ; /* [4..3]  */
        unsigned int    vcpi_slice_int_en     : 1   ; /* [5]  */
        unsigned int    vcpi_sao_luma         : 1   ; /* [6]  */
        unsigned int    vcpi_sao_chroma       : 1   ; /* [7]  */
        unsigned int    vcpi_rec_cmp_en       : 1   ; /* [8]  */
        unsigned int    vcpi_img_improve_en   : 1   ; /* [9]  */
        unsigned int    vcpi_frame_type       : 2   ; /* [11..10]  */
        unsigned int    vcpi_entropy_mode     : 1   ; /* [12]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vcpi_idr_pic          : 1   ; /* [16]  */
        unsigned int    vcpi_pskp_en          : 1   ; /* [17]  */
        unsigned int    vcpi_trans_mode       : 2   ; /* [19..18]  */
        unsigned int    reserved_1            : 4   ; /* [23..20]  */
        unsigned int    vcpi_ref_cmp_en       : 1   ; /* [24]  */
        unsigned int    vcpi_tiles_en         : 1   ; /* [25]  */
        unsigned int    vcpi_lcu_size         : 2   ; /* [27..26]  */
        unsigned int    vcpi_time_en          : 2   ; /* [29..28]  */
        unsigned int    vcpi_bkp_en           : 1   ; /* [30]  */
        unsigned int    vcpi_dbgmod           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_MODE;

/* Define the union U_VEDU_TILE_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_tile_width       : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    vcpi_tile_height      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_TILE_SIZE;

/* Define the union U_VEDU_SLICE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_slice_size       : 16  ; /* [15..0]  */
        unsigned int    vcpi_slcspilt_mod     : 1   ; /* [16]  */
        unsigned int    vcpi_multislc_en      : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_SLICE;

/* Define the union U_VEDU_QPCFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_cr_qp_offset     : 5   ; /* [4..0]  */
        unsigned int    vcpi_cb_qp_offset     : 5   ; /* [9..5]  */
        unsigned int    vcpi_frm_qp           : 6   ; /* [15..10]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_QPCFG;

/* Define the union U_VEDU_DBLKCFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_dblk_beta        : 4   ; /* [3..0]  */
        unsigned int    vcpi_dblk_alpha       : 4   ; /* [7..4]  */
        unsigned int    vcpi_dblk_filter_flag : 2   ; /* [9..8]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_DBLKCFG;

/* Define the union U_VEDU_LOW_POWER */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_intra_lowpow     : 1   ; /* [0]  */
        unsigned int    vcpi_fme_lowpow       : 1   ; /* [1]  */
        unsigned int    vcpi_ime_lowpow       : 1   ; /* [2]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    tqitq_gtck_en         : 1   ; /* [16]  */
        unsigned int    mrg_gtck_en           : 1   ; /* [17]  */
        unsigned int    fme_gtck_en           : 1   ; /* [18]  */
        unsigned int    vcpi_clkgate_en       : 2   ; /* [20..19]  */
        unsigned int    vcpi_mem_clkgate_en   : 1   ; /* [21]  */
        unsigned int    vcpi_protocol_clkgate_en : 1   ; /* [22]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_LOW_POWER;

/* Define the union U_VEDU_PICSIZE_PIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_imgwidth_pix     : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vcpi_imgheight_pix    : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_PICSIZE_PIX;

/* Define the union U_VEDU_BP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_bp_lcu_x         : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    vcpi_bp_lcu_y         : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_BP_POS;

/* Define the union U_VEDU_OUTSTD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_r_outstanding    : 5   ; /* [4..0]  */
        unsigned int    vcpi_w_outstanding    : 5   ; /* [9..5]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OUTSTD;

/* Define the union U_VEDU_FRAME_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_frame_cnt        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_FRAME_CNT;

/* Define the union U_VEDU_SW_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_sw_width         : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    vcpi_sw_height        : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_SW_SIZE;

/* Define the union U_VEDU_MV_LOAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_tmv_wr_rd_avail  : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_MV_LOAD;

/* Define the union U_VEDU_CROSS_TILE_SLC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_cross_slice      : 1   ; /* [0]  */
        unsigned int    vcpi_cross_tile       : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CROSS_TILE_SLC;

/* Define the union U_VEDU_MEM_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mem_ctrl_s            : 16  ; /* [15..0]  */
        unsigned int    mem_ctrl_d1w2r        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_MEM_CTRL;

/* Define the union U_VEDU_OSD_ENABLE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd0_en               : 1   ; /* [0]  */
        unsigned int    osd1_en               : 1   ; /* [1]  */
        unsigned int    osd2_en               : 1   ; /* [2]  */
        unsigned int    osd3_en               : 1   ; /* [3]  */
        unsigned int    osd4_en               : 1   ; /* [4]  */
        unsigned int    osd5_en               : 1   ; /* [5]  */
        unsigned int    osd6_en               : 1   ; /* [6]  */
        unsigned int    osd7_en               : 1   ; /* [7]  */
        unsigned int    osd0_absqp            : 1   ; /* [8]  */
        unsigned int    osd1_absqp            : 1   ; /* [9]  */
        unsigned int    osd2_absqp            : 1   ; /* [10]  */
        unsigned int    osd3_absqp            : 1   ; /* [11]  */
        unsigned int    osd4_absqp            : 1   ; /* [12]  */
        unsigned int    osd5_absqp            : 1   ; /* [13]  */
        unsigned int    osd6_absqp            : 1   ; /* [14]  */
        unsigned int    osd7_absqp            : 1   ; /* [15]  */
        unsigned int    osd_en                : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_ENABLE;

/* Define the union U_VEDU_OSD_POS_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd0_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd0_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_0;

/* Define the union U_VEDU_OSD_POS_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd1_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd1_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_1;

/* Define the union U_VEDU_OSD_POS_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd2_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd2_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_2;

/* Define the union U_VEDU_OSD_POS_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd3_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd3_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_3;

/* Define the union U_VEDU_OSD_POS_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd4_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd4_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_4;

/* Define the union U_VEDU_OSD_POS_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd5_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd5_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_5;

/* Define the union U_VEDU_OSD_POS_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd6_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd6_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_6;

/* Define the union U_VEDU_OSD_POS_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd7_x                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd7_y                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_POS_7;

/* Define the union U_VEDU_OSD_SIZE_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd0_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd0_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_0;

/* Define the union U_VEDU_OSD_SIZE_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd1_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd1_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_1;

/* Define the union U_VEDU_OSD_SIZE_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd2_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd2_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_2;

/* Define the union U_VEDU_OSD_SIZE_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd3_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd3_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_3;

/* Define the union U_VEDU_OSD_SIZE_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd4_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd4_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_4;

/* Define the union U_VEDU_OSD_SIZE_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd5_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd5_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_5;

/* Define the union U_VEDU_OSD_SIZE_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd6_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd6_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_6;

/* Define the union U_VEDU_OSD_SIZE_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd7_w                : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    osd7_h                : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_SIZE_7;

/* Define the union U_VEDU_OSD_LAYERID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd0_layer_id         : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    osd1_layer_id         : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    osd2_layer_id         : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    osd3_layer_id         : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    osd4_layer_id         : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    osd5_layer_id         : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    osd6_layer_id         : 3   ; /* [26..24]  */
        unsigned int    reserved_6            : 1   ; /* [27]  */
        unsigned int    osd7_layer_id         : 3   ; /* [30..28]  */
        unsigned int    reserved_7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_LAYERID;

/* Define the union U_VEDU_OSD_QP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd0_qp               : 7   ; /* [6..0]  */
        unsigned int    osd1_qp               : 7   ; /* [13..7]  */
        unsigned int    osd2_qp               : 7   ; /* [20..14]  */
        unsigned int    osd3_qp               : 7   ; /* [27..21]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_QP0;

/* Define the union U_VEDU_OSD_QP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd4_qp               : 7   ; /* [6..0]  */
        unsigned int    osd5_qp               : 7   ; /* [13..7]  */
        unsigned int    osd6_qp               : 7   ; /* [20..14]  */
        unsigned int    osd7_qp               : 7   ; /* [27..21]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_OSD_QP1;

/* Define the union U_VEDU_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_stride        : 16  ; /* [15..0]  */
        unsigned int    curld_y_stride        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_STRIDE;

/* Define the union U_VEDU_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_ch_stride       : 16  ; /* [15..0]  */
        unsigned int    curld_yh_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_HEAD_STRIDE;

/* Define the union U_VEDU_REC_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    recst_ystride         : 16  ; /* [15..0]  */
        unsigned int    recst_cstride         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_REC_STRIDE;

/* Define the union U_VEDU_REC_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    recst_head_stride     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_REC_HEAD_STRIDE;

/* Define the union U_VEDU_REF_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    refld_chroma_vstride  : 16  ; /* [15..0]  */
        unsigned int    refld_luma_vstride    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_REF_STRIDE;

/* Define the union U_VEDU_REF_HSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    refld_ch_stride       : 16  ; /* [15..0]  */
        unsigned int    refld_yh_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_REF_HSTRIDE;

/* Define the union U_VEDU_CURLD_LOWDLY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_read_interval   : 8   ; /* [7..0]  */
        unsigned int    curld_lowdly_en       : 1   ; /* [8]  */
        unsigned int    vcpi_para_sprat_en    : 1   ; /* [9]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CURLD_LOWDLY;

/* Define the union U_VEDU_STRFMT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_crop_en          : 1   ; /* [0]  */
        unsigned int    vcpi_scale_en         : 1   ; /* [1]  */
        unsigned int    vcpi_store_mode       : 1   ; /* [2]  */
        unsigned int    vcpi_blk_type         : 3   ; /* [5..3]  */
        unsigned int    vcpi_str_fmt          : 4   ; /* [9..6]  */
        unsigned int    vcpi_package_sel      : 4   ; /* [13..10]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_STRFMT;

/* Define the union U_VEDU_CROP_START */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_crop_xstart      : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vcpi_crop_ystart      : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CROP_START;

/* Define the union U_VEDU_CROP_END */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_crop_xend        : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vcpi_crop_yend        : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CROP_END;

/* Define the union U_VEDU_SCALE_PARA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_xscale           : 16  ; /* [15..0]  */
        unsigned int    vcpi_yscale           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_SCALE_PARA;

/* Define the union U_VEDU_ORI_PICSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_oriwidth_pix     : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vcpi_oriheight_pix    : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_ORI_PICSIZE;

/* Define the union U_VEDU_INTRA_INTER_CU_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_intra_cu_en      : 4   ; /* [3..0]  */
        unsigned int    vcpi_ipcm_en          : 1   ; /* [4]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    vcpi_fme_cu_en        : 4   ; /* [11..8]  */
        unsigned int    vcpi_mrg_cu_en        : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTRA_INTER_CU_EN;

/* Define the union U_VEDU_VLC_CONFIG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ref_idc          : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    vcpi_cabac_init_idc   : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    vcpi_num_refidx       : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    vcpi_byte_stuffing    : 1   ; /* [12]  */
        unsigned int    reserved_3            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_VLC_CONFIG;

/* Define the union U_VEDU_PRE_JUDGE_EXT_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_iblk_pre_en      : 1   ; /* [0]  */
        unsigned int    vcpi_pblk_pre_en      : 1   ; /* [1]  */
        unsigned int    vcpi_force_inter      : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vcpi_ext_edge_en      : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_PRE_JUDGE_EXT_EN;

/* Define the union U_VEDU_PRE_JUDGE_COST_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_iblk_pre_cost_thr : 16  ; /* [15..0]  */
        unsigned int    vcpi_pblk_pre_cost_thr : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_PRE_JUDGE_COST_THR;

/* Define the union U_VEDU_IBLK_PRE_MV_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_iblk_pre_mv_dif_thr0 : 8   ; /* [7..0]  */
        unsigned int    vcpi_iblk_pre_mv_dif_thr1 : 8   ; /* [15..8]  */
        unsigned int    vcpi_iblk_pre_mvx_thr : 8   ; /* [23..16]  */
        unsigned int    vcpi_iblk_pre_mvy_thr : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_IBLK_PRE_MV_THR;

/* Define the union U_VEDU_WINDOW_SIZE0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_win0_width       : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    vcpi_win0_height      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_WINDOW_SIZE0;

/* Define the union U_VEDU_WINDOW_SIZE1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_win1_width       : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    vcpi_win1_height      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_WINDOW_SIZE1;

/* Define the union U_VEDU_WINDOW_SIZE2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_win2_width       : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    vcpi_win2_height      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_WINDOW_SIZE2;

/* Define the union U_VEDU_WINDOW_SIZE3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_win3_width       : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    vcpi_win3_height      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_WINDOW_SIZE3;

/* Define the union U_VEDU_PIC_STRONG_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_skin_en          : 1   ; /* [0]  */
        unsigned int    vcpi_highedge_en      : 1   ; /* [1]  */
        unsigned int    vcpi_static_en        : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_PIC_STRONG_EN;

/* Define the union U_VEDU_DOWN_FREQ_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    down_freq_en          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_DOWN_FREQ_EN;

/* Define the union U_VEDU_PBLK_PRE_MV_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_pblk_pre_mvx_thr : 8   ; /* [7..0]  */
        unsigned int    vcpi_pblk_pre_mvy_thr : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_PBLK_PRE_MV_THR;

/* Define the union U_VEDU_INTSTAT_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_ve_eop_s          : 1   ; /* [0]  */
        unsigned int    int_ve_buffull_s      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    int_ve_pbitsover_s    : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    int_vedu_slice_end_s  : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    int_vedu_brkpt_s      : 1   ; /* [16]  */
        unsigned int    int_vedu_step_s       : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    int_vedu_timeout_s    : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    int_cfg_err_s         : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTSTAT_S;

/* Define the union U_VEDU_INTMASK_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enable_ve_eop_s       : 1   ; /* [0]  */
        unsigned int    enable_ve_buffull_s   : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    enable_ve_pbitsover_s : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    enable_vedu_slice_end_s : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    enable_vedu_brkpt_s   : 1   ; /* [16]  */
        unsigned int    enable_vedu_step_s    : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    enable_vedu_timeout_s : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    enable_cfg_err_s      : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTMASK_S;

/* Define the union U_VEDU_RAWINT_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rint_ve_eop_s         : 1   ; /* [0]  */
        unsigned int    rint_ve_buffull_s     : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    rint_ve_pbitsover_s   : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    rint_vedu_slice_end_s : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    rint_vedu_brkpt_s     : 1   ; /* [16]  */
        unsigned int    rint_vedu_step_s      : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    rint_vedu_timeout_s   : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    rint_cfg_err_s        : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RAWINT_S;

/* Define the union U_VEDU_INTCLR_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clr_ve_eop_s          : 1   ; /* [0]  */
        unsigned int    clr_ve_buffull_s      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    clr_ve_pbitsover_s    : 1   ; /* [3]  */
        unsigned int    reserved_1            : 6   ; /* [9..4]  */
        unsigned int    clr_vedu_slice_end_s  : 1   ; /* [10]  */
        unsigned int    reserved_2            : 5   ; /* [15..11]  */
        unsigned int    clr_vedu_brkpt_s      : 1   ; /* [16]  */
        unsigned int    clr_vedu_step_s       : 1   ; /* [17]  */
        unsigned int    reserved_3            : 9   ; /* [26..18]  */
        unsigned int    clr_vedu_timeout_s    : 1   ; /* [27]  */
        unsigned int    reserved_4            : 2   ; /* [29..28]  */
        unsigned int    clr_cfg_err_s         : 1   ; /* [30]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_INTCLR_S;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_VEDU_INTSTAT_NS      VEDU_INTSTAT_NS;
    volatile U_VEDU_INTMASK_NS      VEDU_INTMASK_NS;
    volatile U_VEDU_RAWINT_NS       VEDU_RAWINT_NS;
    volatile U_VEDU_INTCLR_NS       VEDU_INTCLR_NS;
    volatile U_VEDU_START           VEDU_START;
    volatile U_VEDU_MODE            VEDU_MODE;
    volatile U_VEDU_TILE_SIZE       VEDU_TILE_SIZE;
    volatile U_VEDU_SLICE           VEDU_SLICE;
    volatile U_VEDU_QPCFG           VEDU_QPCFG;
    volatile unsigned int           VEDU_CNTCLR;
    volatile unsigned int           VEDU_FRAMENO;
    volatile U_VEDU_DBLKCFG         VEDU_DBLKCFG;
    volatile U_VEDU_LOW_POWER       VEDU_LOW_POWER;
    volatile U_VEDU_PICSIZE_PIX     VEDU_PICSIZE_PIX;
    volatile U_VEDU_BP_POS          VEDU_BP_POS;
    volatile unsigned int           VEDU_TIMEOUT;
    volatile U_VEDU_OUTSTD          VEDU_OUTSTD;
    volatile unsigned int           VEDU_TIMER;
    volatile unsigned int           VEDU_IDLE_TIMER;
    volatile unsigned int           VEDU_VERSION0;
    volatile unsigned int           VEDU_VERSION1;
    volatile U_VEDU_FRAME_CNT       VEDU_FRAME_CNT;
    volatile U_VEDU_SW_SIZE         VEDU_SW_SIZE;
    volatile U_VEDU_MV_LOAD         VEDU_MV_LOAD;
    volatile U_VEDU_CROSS_TILE_SLC  VEDU_CROSS_TILE_SLC;
    volatile U_VEDU_MEM_CTRL        VEDU_MEM_CTRL;
    volatile U_VEDU_OSD_ENABLE      VEDU_OSD_ENABLE;
    volatile U_VEDU_OSD_POS_0       VEDU_OSD_POS_0;
    volatile U_VEDU_OSD_POS_1       VEDU_OSD_POS_1;
    volatile U_VEDU_OSD_POS_2       VEDU_OSD_POS_2;
    volatile U_VEDU_OSD_POS_3       VEDU_OSD_POS_3;
    volatile U_VEDU_OSD_POS_4       VEDU_OSD_POS_4;
    volatile U_VEDU_OSD_POS_5       VEDU_OSD_POS_5;
    volatile U_VEDU_OSD_POS_6       VEDU_OSD_POS_6;
    volatile U_VEDU_OSD_POS_7       VEDU_OSD_POS_7;
    volatile U_VEDU_OSD_SIZE_0      VEDU_OSD_SIZE_0;
    volatile U_VEDU_OSD_SIZE_1      VEDU_OSD_SIZE_1;
    volatile U_VEDU_OSD_SIZE_2      VEDU_OSD_SIZE_2;
    volatile U_VEDU_OSD_SIZE_3      VEDU_OSD_SIZE_3;
    volatile U_VEDU_OSD_SIZE_4      VEDU_OSD_SIZE_4;
    volatile U_VEDU_OSD_SIZE_5      VEDU_OSD_SIZE_5;
    volatile U_VEDU_OSD_SIZE_6      VEDU_OSD_SIZE_6;
    volatile U_VEDU_OSD_SIZE_7      VEDU_OSD_SIZE_7;
    volatile U_VEDU_OSD_LAYERID     VEDU_OSD_LAYERID;
    volatile U_VEDU_OSD_QP0         VEDU_OSD_QP0;
    volatile U_VEDU_OSD_QP1         VEDU_OSD_QP1;
    volatile unsigned int           VEDU_TUNLCELL_ADDR;
    volatile unsigned int           VEDU_SRC_YADDR;
    volatile unsigned int           VEDU_SRC_CADDR;
    volatile unsigned int           VEDU_SRC_VADDR;
    volatile unsigned int           VEDU_YH_ADDR;
    volatile unsigned int           VEDU_CH_ADDR;
    volatile U_VEDU_STRIDE          VEDU_STRIDE;
    volatile U_VEDU_HEAD_STRIDE     VEDU_HEAD_STRIDE;
    volatile unsigned int           VEDU_REC_YADDR;
    volatile unsigned int           VEDU_REC_CADDR;
    volatile U_VEDU_REC_STRIDE      VEDU_REC_STRIDE;
    volatile unsigned int           VEDU_REC_YH_ADDR;
    volatile unsigned int           VEDU_REC_CH_ADDR;
    volatile U_VEDU_REC_HEAD_STRIDE VEDU_REC_HEAD_STRIDE;
    volatile unsigned int           VEDU_REF_YADDR;
    volatile unsigned int           VEDU_REF_CADDR;
    volatile U_VEDU_REF_STRIDE      VEDU_REF_STRIDE;
    volatile unsigned int           VEDU_REF_YH_ADDR;
    volatile unsigned int           VEDU_REF_CH_ADDR;
    volatile U_VEDU_REF_HSTRIDE     VEDU_REF_HSTRIDE;
    volatile unsigned int           VEDU_PMELD_ADDR;
    volatile unsigned int           VEDU_PMEST_ADDR;
    volatile unsigned int           VEDU_NBI_UPST_ADDR;
    volatile unsigned int           VEDU_NBI_MVST_ADDR;
    volatile unsigned int           VEDU_NBI_MVLD_ADDR;
    volatile U_VEDU_CURLD_LOWDLY    VEDU_CURLD_LOWDLY;
    volatile unsigned int           RESERVED_1[2];
    volatile U_VEDU_STRFMT          VEDU_STRFMT;
    volatile U_VEDU_CROP_START      VEDU_CROP_START;
    volatile U_VEDU_CROP_END        VEDU_CROP_END;
    volatile U_VEDU_SCALE_PARA      VEDU_SCALE_PARA;
    volatile U_VEDU_ORI_PICSIZE     VEDU_ORI_PICSIZE;
    volatile U_VEDU_INTRA_INTER_CU_EN VEDU_INTRA_INTER_CU_EN;
    volatile U_VEDU_VLC_CONFIG      VEDU_VLC_CONFIG;
    volatile U_VEDU_PRE_JUDGE_EXT_EN VEDU_PRE_JUDGE_EXT_EN;
    volatile U_VEDU_PRE_JUDGE_COST_THR VEDU_PRE_JUDGE_COST_THR;
    volatile U_VEDU_IBLK_PRE_MV_THR VEDU_IBLK_PRE_MV_THR;
    volatile U_VEDU_WINDOW_SIZE0    VEDU_WINDOW_SIZE0;
    volatile U_VEDU_WINDOW_SIZE1    VEDU_WINDOW_SIZE1;
    volatile U_VEDU_WINDOW_SIZE2    VEDU_WINDOW_SIZE2;
    volatile U_VEDU_WINDOW_SIZE3    VEDU_WINDOW_SIZE3;
    volatile U_VEDU_PIC_STRONG_EN   VEDU_PIC_STRONG_EN;
    volatile unsigned int           VEDU_STRMBUFLEN0;
    volatile unsigned int           VEDU_STRMBUFLEN1;
    volatile unsigned int           VEDU_STRMBUFLEN2;
    volatile unsigned int           VEDU_STRMBUFLEN3;
    volatile unsigned int           VEDU_STRMBUFLEN4;
    volatile unsigned int           VEDU_STRMBUFLEN5;
    volatile unsigned int           VEDU_STRMBUFLEN6;
    volatile unsigned int           VEDU_STRMBUFLEN7;
    volatile unsigned int           VEDU_STRMBUFLEN8;
    volatile unsigned int           VEDU_STRMBUFLEN9;
    volatile unsigned int           VEDU_STRMBUFLEN10;
    volatile unsigned int           VEDU_STRMBUFLEN11;
    volatile unsigned int           VEDU_STRMBUFLEN12;
    volatile unsigned int           VEDU_STRMBUFLEN13;
    volatile unsigned int           VEDU_STRMBUFLEN14;
    volatile unsigned int           VEDU_STRMBUFLEN15;
    volatile unsigned int           VEDU_STRMADDR0;
    volatile unsigned int           VEDU_STRMADDR1;
    volatile unsigned int           VEDU_STRMADDR2;
    volatile unsigned int           VEDU_STRMADDR3;
    volatile unsigned int           VEDU_STRMADDR4;
    volatile unsigned int           VEDU_STRMADDR5;
    volatile unsigned int           VEDU_STRMADDR6;
    volatile unsigned int           VEDU_STRMADDR7;
    volatile unsigned int           VEDU_STRMADDR8;
    volatile unsigned int           VEDU_STRMADDR9;
    volatile unsigned int           VEDU_STRMADDR10;
    volatile unsigned int           VEDU_STRMADDR11;
    volatile unsigned int           VEDU_STRMADDR12;
    volatile unsigned int           VEDU_STRMADDR13;
    volatile unsigned int           VEDU_STRMADDR14;
    volatile unsigned int           VEDU_STRMADDR15;
    volatile unsigned int           VEDU_PARA_ADDR;
    volatile U_VEDU_DOWN_FREQ_EN    VEDU_DOWN_FREQ_EN;
    volatile U_VEDU_PBLK_PRE_MV_THR VEDU_PBLK_PRE_MV_THR;
    volatile U_VEDU_INTSTAT_S       VEDU_INTSTAT_S;
    volatile U_VEDU_INTMASK_S       VEDU_INTMASK_S;
    volatile U_VEDU_RAWINT_S        VEDU_RAWINT_S;
    volatile U_VEDU_INTCLR_S        VEDU_INTCLR_S;

} S_vcpi_REGS_TYPE;






/*-------------- Vctrl   start 0x20620200 ---------------------*/ 
/* Define the union U_VCTRL_ROI_CFG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    region0en             : 1   ; /* [0]  */
        unsigned int    region1en             : 1   ; /* [1]  */
        unsigned int    region2en             : 1   ; /* [2]  */
        unsigned int    region3en             : 1   ; /* [3]  */
        unsigned int    region4en             : 1   ; /* [4]  */
        unsigned int    region5en             : 1   ; /* [5]  */
        unsigned int    region6en             : 1   ; /* [6]  */
        unsigned int    region7en             : 1   ; /* [7]  */
        unsigned int    absqp0                : 1   ; /* [8]  */
        unsigned int    absqp1                : 1   ; /* [9]  */
        unsigned int    absqp2                : 1   ; /* [10]  */
        unsigned int    absqp3                : 1   ; /* [11]  */
        unsigned int    absqp4                : 1   ; /* [12]  */
        unsigned int    absqp5                : 1   ; /* [13]  */
        unsigned int    absqp6                : 1   ; /* [14]  */
        unsigned int    absqp7                : 1   ; /* [15]  */
        unsigned int    region0keep           : 1   ; /* [16]  */
        unsigned int    region1keep           : 1   ; /* [17]  */
        unsigned int    region2keep           : 1   ; /* [18]  */
        unsigned int    region3keep           : 1   ; /* [19]  */
        unsigned int    region4keep           : 1   ; /* [20]  */
        unsigned int    region5keep           : 1   ; /* [21]  */
        unsigned int    region6keep           : 1   ; /* [22]  */
        unsigned int    region7keep           : 1   ; /* [23]  */
        unsigned int    vcpi_roi_en           : 1   ; /* [24]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_CFG0;

/* Define the union U_VCTRL_ROI_CFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    roiqp0                : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    roiqp1                : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    roiqp2                : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    roiqp3                : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_CFG1;

/* Define the union U_VCTRL_ROI_CFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    roiqp4                : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    roiqp5                : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    roiqp6                : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    roiqp7                : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_CFG2;

/* Define the union U_VCTRL_ROI_SIZE_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size0_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size0_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_0;

/* Define the union U_VCTRL_ROI_START_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start0_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start0_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_0;

/* Define the union U_VCTRL_ROI_SIZE_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size1_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size1_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_1;

/* Define the union U_VCTRL_ROI_START_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start1_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start1_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_1;

/* Define the union U_VCTRL_ROI_SIZE_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size2_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size2_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_2;

/* Define the union U_VCTRL_ROI_START_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start2_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start2_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_2;

/* Define the union U_VCTRL_ROI_SIZE_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size3_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size3_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_3;

/* Define the union U_VCTRL_ROI_START_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start3_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start3_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_3;

/* Define the union U_VCTRL_ROI_SIZE_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size4_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size4_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_4;

/* Define the union U_VCTRL_ROI_START_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start4_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start4_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_4;

/* Define the union U_VCTRL_ROI_SIZE_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size5_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size5_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_5;

/* Define the union U_VCTRL_ROI_START_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start5_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start5_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_5;

/* Define the union U_VCTRL_ROI_SIZE_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size6_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size6_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_6;

/* Define the union U_VCTRL_ROI_START_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start6_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start6_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_6;

/* Define the union U_VCTRL_ROI_SIZE_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    size7_roiwidth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    size7_roiheight       : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_SIZE_7;

/* Define the union U_VCTRL_ROI_START_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start7_roistartx      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    start7_roistarty      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_ROI_START_7;

/* Define the union U_VCTRL_LCU_TARGET_BIT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_target_bit        : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_LCU_TARGET_BIT;

/* Define the union U_VCTRL_NARROW_THRESHOLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    narrow_tile_width     : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_NARROW_THRESHOLD;

/* Define the union U_VCTRL_LCU_BASELINE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_performance_baseline : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_LCU_BASELINE;

/* Define the union U_VCTRL_PIPE_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stage_1_busy          : 1   ; /* [0]  */
        unsigned int    stage_2_busy          : 1   ; /* [1]  */
        unsigned int    stage_3_busy          : 1   ; /* [2]  */
        unsigned int    stage_4_busy          : 1   ; /* [3]  */
        unsigned int    stage_5_busy          : 1   ; /* [4]  */
        unsigned int    stage_6_busy          : 1   ; /* [5]  */
        unsigned int    stage_7_busy          : 1   ; /* [6]  */
        unsigned int    stage_8_busy          : 1   ; /* [7]  */
        unsigned int    stage_9_busy          : 1   ; /* [8]  */
        unsigned int    stage_10_busy         : 1   ; /* [9]  */
        unsigned int    reseve                : 18  ; /* [27..10]  */
        unsigned int    nbi_picend            : 1   ; /* [28]  */
        unsigned int    pmest_end             : 1   ; /* [29]  */
        unsigned int    vclst_end             : 1   ; /* [30]  */
        unsigned int    recst_end             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_PIPE_STATE;

/* Define the union U_VCTRL_MODULE_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_valid           : 1   ; /* [0]  */
        unsigned int    pmeld_valid           : 1   ; /* [1]  */
        unsigned int    nbi_valid             : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    pme_valid             : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    refld_luma_ready      : 1   ; /* [8]  */
        unsigned int    qpg_valid             : 1   ; /* [9]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    ime_valid             : 1   ; /* [12]  */
        unsigned int    pintra_valid          : 1   ; /* [13]  */
        unsigned int    refld_chma_valid      : 1   ; /* [14]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    intra_valid           : 1   ; /* [16]  */
        unsigned int    mrg_valid             : 1   ; /* [17]  */
        unsigned int    fme_valid             : 1   ; /* [18]  */
        unsigned int    pmv_valid             : 1   ; /* [19]  */
        unsigned int    sel_valid             : 1   ; /* [20]  */
        unsigned int    reserved_4            : 3   ; /* [23..21]  */
        unsigned int    dblk_valid            : 1   ; /* [24]  */
        unsigned int    sao_valid             : 1   ; /* [25]  */
        unsigned int    reserved_5            : 2   ; /* [27..26]  */
        unsigned int    pack_valid            : 1   ; /* [28]  */
        unsigned int    cabac_valid           : 1   ; /* [29]  */
        unsigned int    reserved_6            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_MODULE_STATE;

/* Define the union U_VCTRL_CUR_TILE_INFO_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tile_x                : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    tile_y                : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_CUR_TILE_INFO_0;

/* Define the union U_VCTRL_CUR_TILE_INFO_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tile_base_lcu_x       : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    tile_base_lcu_y       : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_CUR_TILE_INFO_1;

/* Define the union U_VCTRL_CUR_TILE_INFO_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tile_lcu_x            : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    tile_lcu_y            : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_CUR_TILE_INFO_2;

/* Define the union U_VCTRL_SLICE_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slice_base_lcu_x      : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    slice_base_lcu_y      : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 3   ; /* [27..25]  */
        unsigned int    slice_number          : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_SLICE_INFO;

/* Define the union U_VCTRL_CTB_PIPE_S_COORD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_x                 : 9   ; /* [8..0]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    lcu_y                 : 9   ; /* [24..16]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_CTB_PIPE_S_COORD;

/* Define the union U_VCTRL_NORM_TR32X32_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    norm32_coeff_protect_num : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    norm32_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_NORM_TR32X32_COEFF_DENOISE;

/* Define the union U_VCTRL_NORM_TR16X16_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    norm16_coeff_protect_num : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    norm16_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_NORM_TR16X16_COEFF_DENOISE;

/* Define the union U_VCTRL_SKIN_TR32X32_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin32_coeff_protect_num : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    skin32_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_SKIN_TR32X32_COEFF_DENOISE;

/* Define the union U_VCTRL_SKIN_TR16X16_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin16_coeff_protect_num : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    skin16_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_SKIN_TR16X16_COEFF_DENOISE;

/* Define the union U_VCTRL_STATIC_TR32X32_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    static32_coeff_protect_num : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    static32_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_STATIC_TR32X32_COEFF_DENOISE;

/* Define the union U_VCTRL_STATIC_TR16X16_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    static16_coeff_protect_num : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    static16_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_STATIC_TR16X16_COEFF_DENOISE;

/* Define the union U_VCTRL_HEDGE_TR32X32_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hedge32_coeff_protect_num : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    hedge32_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_HEDGE_TR32X32_COEFF_DENOISE;

/* Define the union U_VCTRL_HEDGE_TR16X16_COEFF_DENOISE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hedge16_coeff_protect_num : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    hedge16_tr1_denois_max_num : 5   ; /* [20..16]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_HEDGE_TR16X16_COEFF_DENOISE;

/* Define the union U_VCTRL_NORMAL_INTRA_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    norm_intra_cu4_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    norm_intra_cu8_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    norm_intra_cu16_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    norm_intra_cu32_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_NORMAL_INTRA_RDO_FACTOR;

/* Define the union U_VCTRL_NORMAL_MRG_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    norm_mrg_cu8_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    norm_mrg_cu16_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    norm_mrg_cu32_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    norm_mrg_cu64_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_NORMAL_MRG_RDO_FACTOR;

/* Define the union U_VCTRL_NORMAL_FME_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    norm_fme_cu8_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    norm_fme_cu16_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    norm_fme_cu32_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    norm_fme_cu64_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_NORMAL_FME_RDO_FACTOR;

/* Define the union U_VCTRL_SKIN_REGION_INTRA_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_intra_cu4_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    skin_intra_cu8_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    skin_intra_cu16_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    skin_intra_cu32_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_SKIN_REGION_INTRA_RDO_FACTOR;

/* Define the union U_VCTRL_SKIN_REGION_MRG_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_mrg_cu8_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    skin_mrg_cu16_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    skin_mrg_cu32_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    skin_mrg_cu64_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_SKIN_REGION_MRG_RDO_FACTOR;

/* Define the union U_VCTRL_SKIN_REGION_FME_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_fme_cu8_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    skin_fme_cu16_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    skin_fme_cu32_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    skin_fme_cu64_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_SKIN_REGION_FME_RDO_FACTOR;

/* Define the union U_VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hedge_intra_cu4_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    hedge_intra_cu8_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    hedge_intra_cu16_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    hedge_intra_cu32_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR;

/* Define the union U_VCTRL_HIGH_EDGE_MRG_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hedge_mrg_cu8_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    hedge_mrg_cu16_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    hedge_mrg_cu32_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    hedge_mrg_cu64_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_HIGH_EDGE_MRG_RDO_FACTOR;

/* Define the union U_VCTRL_HIGH_EDGE_FME_RDO_FACTOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hedge_fme_cu8_rdcost_offset : 4   ; /* [3..0]  */
        unsigned int    hedge_fme_cu16_rdcost_offset : 4   ; /* [7..4]  */
        unsigned int    hedge_fme_cu32_rdcost_offset : 4   ; /* [11..8]  */
        unsigned int    hedge_fme_cu64_rdcost_offset : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_HIGH_EDGE_FME_RDO_FACTOR;

/* Define the union U_VCTRL_OVERHEAD_PIPE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_PIPE;

/* Define the union U_VCTRL_OVERHEAD_PMELD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_PMELD;

/* Define the union U_VCTRL_OVERHEAD_NBI */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_NBI;

/* Define the union U_VCTRL_OVERHEAD_QPG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_QPG;

/* Define the union U_VCTRL_OVERHEAD_PME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_PME;

/* Define the union U_VCTRL_OVERHEAD_REFLD_LUMA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_REFLD_LUMA;

/* Define the union U_VCTRL_OVERHEAD_REFLD_CHMA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_REFLD_CHMA;

/* Define the union U_VCTRL_OVERHEAD_CURLD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_CURLD;

/* Define the union U_VCTRL_OVERHEAD_IME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_IME;

/* Define the union U_VCTRL_OVERHEAD_PINTRA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_PINTRA;

/* Define the union U_VCTRL_OVERHEAD_MRG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_MRG;

/* Define the union U_VCTRL_OVERHEAD_FME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_FME;

/* Define the union U_VCTRL_OVERHEAD_PMV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_PMV;

/* Define the union U_VCTRL_OVERHEAD_SEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_SEL;

/* Define the union U_VCTRL_OVERHEAD_INTRA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_INTRA;

/* Define the union U_VCTRL_OVERHEAD_SAO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_SAO;

/* Define the union U_VCTRL_OVERHEAD_DBLK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_DBLK;

/* Define the union U_VCTRL_OVERHEAD_PACK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_PACK;

/* Define the union U_VCTRL_OVERHEAD_CABAC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_num_ovr_pref_base : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_OVERHEAD_CABAC;

/* Define the union U_VCTRL_FME_CU_INFO_LOW_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_cu_info_low_cnt   : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_FME_CU_INFO_LOW_CNT;

/* Define the union U_VCTRL_FME_CU_INFO_HIGH_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_cu_info_high_cnt  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_FME_CU_INFO_HIGH_CNT;

/* Define the union U_VCTRL_INTRA_LOW_PWR_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_low_pwr_en_cnt  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_INTRA_LOW_PWR_CNT;

/* Define the union U_VCTRL_INTER_LOW_PWR_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    inter_low_pwr_en_cnt  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VCTRL_INTER_LOW_PWR_CNT;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_VCTRL_ROI_CFG0       VCTRL_ROI_CFG0;
    volatile U_VCTRL_ROI_CFG1       VCTRL_ROI_CFG1;
    volatile U_VCTRL_ROI_CFG2       VCTRL_ROI_CFG2;
    volatile U_VCTRL_ROI_SIZE_0     VCTRL_ROI_SIZE_0;
    volatile U_VCTRL_ROI_START_0    VCTRL_ROI_START_0;
    volatile U_VCTRL_ROI_SIZE_1     VCTRL_ROI_SIZE_1;
    volatile U_VCTRL_ROI_START_1    VCTRL_ROI_START_1;
    volatile U_VCTRL_ROI_SIZE_2     VCTRL_ROI_SIZE_2;
    volatile U_VCTRL_ROI_START_2    VCTRL_ROI_START_2;
    volatile U_VCTRL_ROI_SIZE_3     VCTRL_ROI_SIZE_3;
    volatile U_VCTRL_ROI_START_3    VCTRL_ROI_START_3;
    volatile U_VCTRL_ROI_SIZE_4     VCTRL_ROI_SIZE_4;
    volatile U_VCTRL_ROI_START_4    VCTRL_ROI_START_4;
    volatile U_VCTRL_ROI_SIZE_5     VCTRL_ROI_SIZE_5;
    volatile U_VCTRL_ROI_START_5    VCTRL_ROI_START_5;
    volatile U_VCTRL_ROI_SIZE_6     VCTRL_ROI_SIZE_6;
    volatile U_VCTRL_ROI_START_6    VCTRL_ROI_START_6;
    volatile U_VCTRL_ROI_SIZE_7     VCTRL_ROI_SIZE_7;
    volatile U_VCTRL_ROI_START_7    VCTRL_ROI_START_7;
    volatile U_VCTRL_LCU_TARGET_BIT VCTRL_LCU_TARGET_BIT;
    volatile U_VCTRL_NARROW_THRESHOLD VCTRL_NARROW_THRESHOLD;
    volatile U_VCTRL_LCU_BASELINE   VCTRL_LCU_BASELINE;
    volatile unsigned int           RESERVED0[2];
    volatile U_VCTRL_PIPE_STATE     VCTRL_PIPE_STATE;
    volatile U_VCTRL_MODULE_STATE   VCTRL_MODULE_STATE;
    volatile U_VCTRL_CUR_TILE_INFO_0 VCTRL_CUR_TILE_INFO_0;
    volatile U_VCTRL_CUR_TILE_INFO_1 VCTRL_CUR_TILE_INFO_1;
    volatile U_VCTRL_CUR_TILE_INFO_2 VCTRL_CUR_TILE_INFO_2;
    volatile U_VCTRL_SLICE_INFO     VCTRL_SLICE_INFO;
    volatile U_VCTRL_CTB_PIPE_S_COORD VCTRL_CTB_PIPE_S_COORD;
    volatile unsigned int           RESERVED1;
    volatile U_VCTRL_NORM_TR32X32_COEFF_DENOISE VCTRL_NORM_TR32X32_COEFF_DENOISE;
    volatile U_VCTRL_NORM_TR16X16_COEFF_DENOISE VCTRL_NORM_TR16X16_COEFF_DENOISE;
    volatile U_VCTRL_SKIN_TR32X32_COEFF_DENOISE VCTRL_SKIN_TR32X32_COEFF_DENOISE;
    volatile U_VCTRL_SKIN_TR16X16_COEFF_DENOISE VCTRL_SKIN_TR16X16_COEFF_DENOISE;
    volatile U_VCTRL_STATIC_TR32X32_COEFF_DENOISE VCTRL_STATIC_TR32X32_COEFF_DENOISE;
    volatile U_VCTRL_STATIC_TR16X16_COEFF_DENOISE VCTRL_STATIC_TR16X16_COEFF_DENOISE;
    volatile U_VCTRL_HEDGE_TR32X32_COEFF_DENOISE VCTRL_HEDGE_TR32X32_COEFF_DENOISE;
    volatile U_VCTRL_HEDGE_TR16X16_COEFF_DENOISE VCTRL_HEDGE_TR16X16_COEFF_DENOISE;
    volatile U_VCTRL_NORMAL_INTRA_RDO_FACTOR VCTRL_NORMAL_INTRA_RDO_FACTOR;
    volatile U_VCTRL_NORMAL_MRG_RDO_FACTOR VCTRL_NORMAL_MRG_RDO_FACTOR;
    volatile U_VCTRL_NORMAL_FME_RDO_FACTOR VCTRL_NORMAL_FME_RDO_FACTOR;
    volatile U_VCTRL_SKIN_REGION_INTRA_RDO_FACTOR VCTRL_SKIN_REGION_INTRA_RDO_FACTOR;
    volatile U_VCTRL_SKIN_REGION_MRG_RDO_FACTOR VCTRL_SKIN_REGION_MRG_RDO_FACTOR;
    volatile U_VCTRL_SKIN_REGION_FME_RDO_FACTOR VCTRL_SKIN_REGION_FME_RDO_FACTOR;
    volatile U_VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR VCTRL_HIGH_EDGE_INTRA_RDO_FACTOR;
    volatile U_VCTRL_HIGH_EDGE_MRG_RDO_FACTOR VCTRL_HIGH_EDGE_MRG_RDO_FACTOR;
    volatile U_VCTRL_HIGH_EDGE_FME_RDO_FACTOR VCTRL_HIGH_EDGE_FME_RDO_FACTOR;
    volatile unsigned int           RESERVED2[15];
    volatile unsigned int           VCTRL_PERF_TOTAL_PIPE;
    volatile unsigned int           VCTRL_PERF_TOTAL_PMELD;
    volatile unsigned int           VCTRL_PERF_TOTAL_NBI;
    volatile unsigned int           VCTRL_PERF_TOTAL_QPG;
    volatile unsigned int           VCTRL_PERF_TOTAL_PME;
    volatile unsigned int           VCTRL_PERF_TOTAL_REFLD_LUMA;
    volatile unsigned int           VCTRL_PERF_TOTAL_REFLD_CHMA;
    volatile unsigned int           VCTRL_PERF_TOTAL_CURLD;
    volatile unsigned int           VCTRL_PERF_TOTAL_IME;
    volatile unsigned int           VCTRL_PERF_TOTAL_PINTRA;
    volatile unsigned int           VCTRL_PERF_TOTAL_MRG;
    volatile unsigned int           VCTRL_PERF_TOTAL_FME;
    volatile unsigned int           VCTRL_PERF_TOTAL_PMV;
    volatile unsigned int           VCTRL_PERF_TOTAL_SEL;
    volatile unsigned int           VCTRL_PERF_TOTAL_INTRA;
    volatile unsigned int           VCTRL_PERF_TOTAL_SAO;
    volatile unsigned int           VCTRL_PERF_TOTAL_DBLK;
    volatile unsigned int           VCTRL_PERF_TOTAL_PACK;
    volatile unsigned int           VCTRL_PERF_TOTAL_CABAC;
    volatile U_VCTRL_OVERHEAD_PIPE  VCTRL_OVERHEAD_PIPE;
    volatile U_VCTRL_OVERHEAD_PMELD VCTRL_OVERHEAD_PMELD;
    volatile U_VCTRL_OVERHEAD_NBI   VCTRL_OVERHEAD_NBI;
    volatile U_VCTRL_OVERHEAD_QPG   VCTRL_OVERHEAD_QPG;
    volatile U_VCTRL_OVERHEAD_PME   VCTRL_OVERHEAD_PME;
    volatile U_VCTRL_OVERHEAD_REFLD_LUMA VCTRL_OVERHEAD_REFLD_LUMA;
    volatile U_VCTRL_OVERHEAD_REFLD_CHMA VCTRL_OVERHEAD_REFLD_CHMA;
    volatile U_VCTRL_OVERHEAD_CURLD VCTRL_OVERHEAD_CURLD;
    volatile U_VCTRL_OVERHEAD_IME   VCTRL_OVERHEAD_IME;
    volatile U_VCTRL_OVERHEAD_PINTRA VCTRL_OVERHEAD_PINTRA;
    volatile U_VCTRL_OVERHEAD_MRG   VCTRL_OVERHEAD_MRG;
    volatile U_VCTRL_OVERHEAD_FME   VCTRL_OVERHEAD_FME;
    volatile U_VCTRL_OVERHEAD_PMV   VCTRL_OVERHEAD_PMV;
    volatile U_VCTRL_OVERHEAD_SEL   VCTRL_OVERHEAD_SEL;
    volatile U_VCTRL_OVERHEAD_INTRA VCTRL_OVERHEAD_INTRA;
    volatile U_VCTRL_OVERHEAD_SAO   VCTRL_OVERHEAD_SAO;
    volatile U_VCTRL_OVERHEAD_DBLK  VCTRL_OVERHEAD_DBLK;
    volatile U_VCTRL_OVERHEAD_PACK  VCTRL_OVERHEAD_PACK;
    volatile U_VCTRL_OVERHEAD_CABAC VCTRL_OVERHEAD_CABAC;
    volatile U_VCTRL_FME_CU_INFO_LOW_CNT VCTRL_FME_CU_INFO_LOW_CNT;
    volatile U_VCTRL_FME_CU_INFO_HIGH_CNT VCTRL_FME_CU_INFO_HIGH_CNT;
    volatile U_VCTRL_INTRA_LOW_PWR_CNT VCTRL_INTRA_LOW_PWR_CNT;
	volatile U_VCTRL_INTER_LOW_PWR_CNT VCTRL_INTER_LOW_PWR_CNT;
    volatile unsigned int           VCTRL_CLK_VEDU_FRM_CYC_CNT;
    volatile unsigned int           RESERVED3[21];

} S_vctrl_REGS_TYPE;




/*-------------- Curld  start 0x20620400---------------------*/ 
/*-------------- Curld  end 0x206205FF---------------------*/ 
/* Curld寄存器结构体   0x20620400  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[128];

} S_curld_REGS_TYPE;


/*--------------Pme  start 0x20620600--------------------*/ 
/* Define the union U_PME_SW_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_psw_adapt_en     : 1   ; /* [0]  */
        unsigned int    vcpi_new_cost_en      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_SW_EN;

/* Define the union U_PME_SW_TR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_psw_thr0         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_SW_TR0;

/* Define the union U_PME_SW_TR1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_psw_thr1         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_SW_TR1;

/* Define the union U_PME_SW_TR2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_psw_thr2         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_SW_TR2;

/* Define the union U_PME_TR_WEIGHTX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tr_weightx_0          : 9   ; /* [8..0]  */
        unsigned int    tr_weightx_1          : 9   ; /* [17..9]  */
        unsigned int    tr_weightx_2          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_TR_WEIGHTX;

/* Define the union U_PME_TR_WEIGHTY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tr_weighty_0          : 8   ; /* [7..0]  */
        unsigned int    tr_weighty_1          : 8   ; /* [15..8]  */
        unsigned int    tr_weighty_2          : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_TR_WEIGHTY;

/* Define the union U_PME_SR_WEIGHT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sr_weight_0           : 4   ; /* [3..0]  */
        unsigned int    sr_weight_1           : 4   ; /* [7..4]  */
        unsigned int    sr_weight_2           : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PME_SR_WEIGHT;

/* Define the union U_pme_skin_thr */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_u_max_thr        : 8   ; /* [7..0]  */
        unsigned int    skin_u_min_thr        : 8   ; /* [15..8]  */
        unsigned int    skin_v_max_thr        : 8   ; /* [23..16]  */
        unsigned int    skin_v_min_thr        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_pme_skin_thr;

/* Define the union U_pme_high_edge */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_num              : 9   ; /* [8..0]  */
        unsigned int    high_edge_thr         : 8   ; /* [16..9]  */
        unsigned int    high_edge_cnt         : 5   ; /* [21..17]  */
        unsigned int    still_scene_thr       : 9   ; /* [30..22]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_pme_high_edge;

/*--------------Pme  end 0x20620600--------------------*/


/* Pme寄存器结构体   0x20620600  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_PME_SW_EN            PME_SW_EN;
    volatile U_PME_SW_TR0           PME_SW_TR0;
    volatile U_PME_SW_TR1           PME_SW_TR1;
    volatile U_PME_SW_TR2           PME_SW_TR2;
    volatile unsigned int           RESERVED0;
    volatile U_PME_TR_WEIGHTX       PME_TR_WEIGHTX;
    volatile U_PME_TR_WEIGHTY       PME_TR_WEIGHTY;
    volatile U_PME_SR_WEIGHT        PME_SR_WEIGHT;
    volatile unsigned int           RESERVED1[2];
    volatile unsigned int           pme_iblk_lcu_num;
    volatile unsigned int           pme_pblk_lcu_num;
    volatile U_pme_skin_thr         pme_skin_thr;
    volatile unsigned int           RESERVED2[2];
    volatile U_pme_high_edge        pme_high_edge;
    volatile unsigned int           RESERVED3[112];

} S_pme_REGS_TYPE;



/*--------------Refid  start 0x20620800--------------------*/ 
/* Define the union U_REFLD_CMD_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_cross_idx         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 7   ; /* [16..10]  */
        unsigned int    refld_vcpi2cont_title_en : 1   ; /* [17]  */
        unsigned int    reserved_1            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_CMD_CFG;

/* Define the union U_REFLD_LOCK_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcux                  : 9   ; /* [8..0]  */
        unsigned int    lcuy                  : 9   ; /* [17..9]  */
        unsigned int    need_modify_flag      : 1   ; /* [18]  */
        unsigned int    nulock_miss_flag      : 1   ; /* [19]  */
        unsigned int    lock_table_cs_err     : 1   ; /* [20]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_LOCK_STATE;

/* Define the union U_REFLD_CMD_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cacheline_posx        : 7   ; /* [6..0]  */
        unsigned int    cacheline_posy        : 12  ; /* [18..7]  */
        unsigned int    buf_pose              : 3   ; /* [21..19]  */
        unsigned int    cacheline_lcux        : 9   ; /* [30..22]  */
        unsigned int    cacheline_wr_full     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_CMD_STATE;

/* Define the union U_REFLD_MAG_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    data_blk_rd_pntr      : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    data_blk_wr_pntr      : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    pre_blk_rd_pntr       : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    refld2dcmp_empty      : 1   ; /* [24]  */
        unsigned int    rdata_blk_empty       : 1   ; /* [25]  */
        unsigned int    data_blk_full         : 1   ; /* [26]  */
        unsigned int    reserved_3            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_MAG_STATE;

/* Define the union U_REFLD_DARB_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    refld_wr_fifo_empty   : 1   ; /* [0]  */
        unsigned int    refld_data_fifo_empty : 1   ; /* [1]  */
        unsigned int    cacheline_sche_wr_empty : 1   ; /* [2]  */
        unsigned int    need_modify_flag      : 1   ; /* [3]  */
        unsigned int    axi_return_empty      : 1   ; /* [4]  */
        unsigned int    axi_return_rd_pntr    : 10  ; /* [14..5]  */
        unsigned int    axi_return_wr_pntr    : 10  ; /* [24..15]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_DARB_STATE;

/* Define the union U_REFLD_BUF_STATE0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    refld_luma_buf_full   : 1   ; /* [0]  */
        unsigned int    luma_rd_pntr          : 2   ; /* [2..1]  */
        unsigned int    luma_wr_pntr          : 2   ; /* [4..3]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    refld_chroma_buf_full : 1   ; /* [8]  */
        unsigned int    chroma_h265_rd_pntr   : 3   ; /* [11..9]  */
        unsigned int    chroma_h265_wr_pntr   : 3   ; /* [14..12]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_BUF_STATE0;

/* Define the union U_REFLD_BUF_STATE1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dcmp_data_rdy         : 16  ; /* [15..0]  */
        unsigned int    dcmp_data_empty       : 1   ; /* [16]  */
        unsigned int    dcmp_data_full        : 1   ; /* [17]  */
        unsigned int    dcmp_data_rd_base     : 5   ; /* [22..18]  */
        unsigned int    dcmp_data_wr_base     : 5   ; /* [27..23]  */
        unsigned int    chroma_head_buf_empty : 1   ; /* [28]  */
        unsigned int    luma_head_buf_empty   : 1   ; /* [29]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_BUF_STATE1;

/* Define the union U_REFLD_ERROR_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dcmp_error            : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_ERROR_STATE;

/* Define the union U_REFLD_PRE_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pre_split_curr_state  : 1   ; /* [0]  */
        unsigned int    reserved_0            : 15  ; /* [15..1]  */
        unsigned int    pre_judge_curr_state  : 2   ; /* [17..16]  */
        unsigned int    reserved_1            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REFLD_PRE_STATE;

/*--------------Refid  end 0x20620800--------------------*/  


/* Refid寄存器结构体   0x20620800  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_REFLD_CMD_CFG        REFLD_CMD_CFG;
    volatile unsigned int           RESERVED0[3];
    volatile unsigned int           REFLD_TBL_ADDR;
    volatile unsigned int           REFLD_TBL_RD_DATA0;
    volatile unsigned int           REFLD_TBL_RD_DATA1;
    volatile unsigned int           REFLD_TBL_RD_DATA2;
    volatile unsigned int           REFLD_TBL_RD_DATA3;
    volatile unsigned int           REFLD_TBL_RD_DATA4;
    volatile unsigned int           RESERVED1[3];
    volatile U_REFLD_LOCK_STATE     REFLD_LOCK_STATE;
    volatile U_REFLD_CMD_STATE      REFLD_CMD_STATE;
    volatile U_REFLD_MAG_STATE      REFLD_MAG_STATE;
    volatile U_REFLD_DARB_STATE     REFLD_DARB_STATE;
    volatile U_REFLD_BUF_STATE0     REFLD_BUF_STATE0;
    volatile U_REFLD_BUF_STATE1     REFLD_BUF_STATE1;
    volatile unsigned int           REFLD_DATA_STATE0;
    volatile unsigned int           REFLD_DATA_STATE1;
    volatile unsigned int           REFLD_DATA_STATE2;
    volatile unsigned int           REFLD_DATA_STATE3;
    volatile U_REFLD_ERROR_STATE    REFLD_ERROR_STATE;
    volatile U_REFLD_PRE_STATE      REFLD_PRE_STATE;
    volatile unsigned int           RESERVED2[103];

} S_refld_REGS_TYPE;



/*--------------Ime start 0x20620a00--------------------*/  

/* Define the union U_INTER_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    vcpi_inter8x8_en      : 1   ; /* [1]  */
        unsigned int    reserved_1            : 1   ; /* [2]  */
        unsigned int    vcpi_rect1_mod        : 1   ; /* [3]  */
        unsigned int    vcpi_rect2_mod        : 1   ; /* [4]  */
        unsigned int    vcpi_rect3_mod        : 1   ; /* [5]  */
        unsigned int    vcpi_high3pre_en      : 2   ; /* [7..6]  */
        unsigned int    reserved_2            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTER_MODE;

/* Define the union U_IME_CFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rect0_hstep      : 2   ; /* [1..0]  */
        unsigned int    vcpi_rect0_vstep      : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_CFG1;

/* Define the union U_IME_CFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rect1_hstep      : 2   ; /* [1..0]  */
        unsigned int    vcpi_rect1_vstep      : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_CFG2;

/* Define the union U_IME_CFG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rect2_hstep      : 2   ; /* [1..0]  */
        unsigned int    vcpi_rect2_vstep      : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_CFG3;

/* Define the union U_IME_CFG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rect3_hstep      : 2   ; /* [1..0]  */
        unsigned int    vcpi_rect3_vstep      : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_CFG4;

/* Define the union U_IME_THR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_start_thr        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_THR0;

/* Define the union U_IME_THR1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_intra_thr        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_THR1;

/* Define the union U_IME_RDOCFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_lambdaoff8       : 16  ; /* [15..0]  */
        unsigned int    vcpi_lambdaoff16      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_RDOCFG;

/* Define the union U_IME_FME_LPOW_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_lowpow_fme_thr0  : 6   ; /* [5..0]  */
        unsigned int    vcpi_lowpow_fme_thr1  : 6   ; /* [11..6]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IME_FME_LPOW_THR;

/*--------------Ime end 0x20620a00--------------------*/  


/* Ime寄存器结构体   0x20620a00  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_INTER_MODE           INTER_MODE;
    volatile unsigned int           RESERVED0;
    volatile U_IME_CFG1             IME_CFG1;
    volatile U_IME_CFG2             IME_CFG2;
    volatile U_IME_CFG3             IME_CFG3;
    volatile U_IME_CFG4             IME_CFG4;
    volatile U_IME_THR0             IME_THR0;
    volatile U_IME_THR1             IME_THR1;
    volatile U_IME_RDOCFG           IME_RDOCFG;
    volatile U_IME_FME_LPOW_THR     IME_FME_LPOW_THR;
    volatile unsigned int           RESERVED1[118];

} S_ime_REGS_TYPE;



/*--------------Qpg   start 0x20620c00--------------------*/  
/* Define the union U_QPG_MAX_MIN_QP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_qp                : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    max_qp                : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_MAX_MIN_QP;

/* Define the union U_QPG_AVERAGE_LCU_BITS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ave_lcu_bits          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_AVERAGE_LCU_BITS;

/* Define the union U_QPG_QP_DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qp_delta              : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_DELTA;

/* Define the union U_QPG_CU_QP_DELTA_THRESH_REG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cu_qp_delta_thresh0   : 8   ; /* [7..0]  */
        unsigned int    cu_qp_delta_thresh1   : 8   ; /* [15..8]  */
        unsigned int    cu_qp_delta_thresh2   : 8   ; /* [23..16]  */
        unsigned int    cu_qp_delta_thresh3   : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_CU_QP_DELTA_THRESH_REG0;

/* Define the union U_QPG_CU_QP_DELTA_THRESH_REG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cu_qp_delta_thresh4   : 8   ; /* [7..0]  */
        unsigned int    cu_qp_delta_thresh5   : 8   ; /* [15..8]  */
        unsigned int    cu_qp_delta_thresh6   : 8   ; /* [23..16]  */
        unsigned int    cu_qp_delta_thresh7   : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_CU_QP_DELTA_THRESH_REG1;

/* Define the union U_QPG_CU_QP_DELTA_THRESH_REG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cu_qp_delta_thresh8   : 8   ; /* [7..0]  */
        unsigned int    cu_qp_delta_thresh9   : 8   ; /* [15..8]  */
        unsigned int    cu_qp_delta_thresh10  : 8   ; /* [23..16]  */
        unsigned int    cu_qp_delta_thresh11  : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_CU_QP_DELTA_THRESH_REG2;

/* Define the union U_QPG_STRONG_EDGE_QP_DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    strong_edge_qp_delta  : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_STRONG_EDGE_QP_DELTA;

/* Define the union U_QPG_SKIN_QP_DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    skin_qp_delta         : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_SKIN_QP_DELTA;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda00              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG00;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda01              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG01;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda02              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG02;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG03 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda03              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG03;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG04 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda04              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG04;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG05 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda05              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG05;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG06 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda06              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG06;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG07 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda07              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG07;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG08 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda08              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG08;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG09 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda09              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG09;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda10              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG10;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda11              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG11;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda12              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG12;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda13              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG13;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda14              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG14;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda15              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG15;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda16              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG16;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda17              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG17;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda18              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG18;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda19              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG19;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda20              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG20;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda21              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG21;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda22              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG22;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda23              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG23;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda24              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG24;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda25              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG25;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda26              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG26;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda27              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG27;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda28              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG28;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda29              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG29;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda30              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG30;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda31              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG31;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda32              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG32;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG33 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda33              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG33;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG34 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda34              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG34;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG35 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda35              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG35;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG36 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda36              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG36;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda37              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG37;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG38 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda38              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG38;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda39              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG39;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda40              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG40;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda41              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG41;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda42              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG42;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG43 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda43              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG43;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG44 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda44              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG44;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG45 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda45              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG45;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG46 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda46              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG46;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG47 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda47              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG47;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG48 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda48              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG48;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG49 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda49              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG49;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda50              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG50;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda51              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG51;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG52 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda52              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG52;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda53              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG53;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda54              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG54;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda55              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG55;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG56 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda56              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG56;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG57 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda57              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG57;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG58 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda58              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG58;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG59 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda59              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG59;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda60              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG60;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda61              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG61;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG62 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda62              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG62;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda63              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG63;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda64              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG64;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG65 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda65              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG65;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG66 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda66              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG66;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG67 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda67              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG67;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG68 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda68              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG68;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG69 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda69              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG69;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG70 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda70              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG70;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG71 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda71              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG71;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG72 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda72              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG72;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG73 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda73              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG73;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG74 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda74              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG74;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG75 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda75              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG75;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG76 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda76              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG76;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG77 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda77              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG77;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG78 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda78              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG78;

/* Define the union U_QPG_QP_LAMBDA_CTRL_REG79 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lambda79              : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_QP_LAMBDA_CTRL_REG79;

/* Define the union U_QPG_VERSION */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    version               : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_QPG_VERSION;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0;
    volatile U_QPG_MAX_MIN_QP       QPG_MAX_MIN_QP;
    volatile U_QPG_AVERAGE_LCU_BITS QPG_AVERAGE_LCU_BITS;
    volatile U_QPG_QP_DELTA         QPG_QP_DELTA;
    volatile U_QPG_CU_QP_DELTA_THRESH_REG0 QPG_CU_QP_DELTA_THRESH_REG0;
    volatile U_QPG_CU_QP_DELTA_THRESH_REG1 QPG_CU_QP_DELTA_THRESH_REG1;
    volatile U_QPG_CU_QP_DELTA_THRESH_REG2 QPG_CU_QP_DELTA_THRESH_REG2;
    volatile unsigned int           RESERVED1;
    volatile U_QPG_STRONG_EDGE_QP_DELTA QPG_STRONG_EDGE_QP_DELTA;
    volatile unsigned int           RESERVED2;
    volatile U_QPG_SKIN_QP_DELTA    QPG_SKIN_QP_DELTA;
    volatile unsigned int           RESERVED3[9];
    volatile U_QPG_QP_LAMBDA_CTRL_REG00 QPG_QP_LAMBDA_CTRL_REG00;
    volatile U_QPG_QP_LAMBDA_CTRL_REG01 QPG_QP_LAMBDA_CTRL_REG01;
    volatile U_QPG_QP_LAMBDA_CTRL_REG02 QPG_QP_LAMBDA_CTRL_REG02;
    volatile U_QPG_QP_LAMBDA_CTRL_REG03 QPG_QP_LAMBDA_CTRL_REG03;
    volatile U_QPG_QP_LAMBDA_CTRL_REG04 QPG_QP_LAMBDA_CTRL_REG04;
    volatile U_QPG_QP_LAMBDA_CTRL_REG05 QPG_QP_LAMBDA_CTRL_REG05;
    volatile U_QPG_QP_LAMBDA_CTRL_REG06 QPG_QP_LAMBDA_CTRL_REG06;
    volatile U_QPG_QP_LAMBDA_CTRL_REG07 QPG_QP_LAMBDA_CTRL_REG07;
    volatile U_QPG_QP_LAMBDA_CTRL_REG08 QPG_QP_LAMBDA_CTRL_REG08;
    volatile U_QPG_QP_LAMBDA_CTRL_REG09 QPG_QP_LAMBDA_CTRL_REG09;
    volatile U_QPG_QP_LAMBDA_CTRL_REG10 QPG_QP_LAMBDA_CTRL_REG10;
    volatile U_QPG_QP_LAMBDA_CTRL_REG11 QPG_QP_LAMBDA_CTRL_REG11;
    volatile U_QPG_QP_LAMBDA_CTRL_REG12 QPG_QP_LAMBDA_CTRL_REG12;
    volatile U_QPG_QP_LAMBDA_CTRL_REG13 QPG_QP_LAMBDA_CTRL_REG13;
    volatile U_QPG_QP_LAMBDA_CTRL_REG14 QPG_QP_LAMBDA_CTRL_REG14;
    volatile U_QPG_QP_LAMBDA_CTRL_REG15 QPG_QP_LAMBDA_CTRL_REG15;
    volatile U_QPG_QP_LAMBDA_CTRL_REG16 QPG_QP_LAMBDA_CTRL_REG16;
    volatile U_QPG_QP_LAMBDA_CTRL_REG17 QPG_QP_LAMBDA_CTRL_REG17;
    volatile U_QPG_QP_LAMBDA_CTRL_REG18 QPG_QP_LAMBDA_CTRL_REG18;
    volatile U_QPG_QP_LAMBDA_CTRL_REG19 QPG_QP_LAMBDA_CTRL_REG19;
    volatile U_QPG_QP_LAMBDA_CTRL_REG20 QPG_QP_LAMBDA_CTRL_REG20;
    volatile U_QPG_QP_LAMBDA_CTRL_REG21 QPG_QP_LAMBDA_CTRL_REG21;
    volatile U_QPG_QP_LAMBDA_CTRL_REG22 QPG_QP_LAMBDA_CTRL_REG22;
    volatile U_QPG_QP_LAMBDA_CTRL_REG23 QPG_QP_LAMBDA_CTRL_REG23;
    volatile U_QPG_QP_LAMBDA_CTRL_REG24 QPG_QP_LAMBDA_CTRL_REG24;
    volatile U_QPG_QP_LAMBDA_CTRL_REG25 QPG_QP_LAMBDA_CTRL_REG25;
    volatile U_QPG_QP_LAMBDA_CTRL_REG26 QPG_QP_LAMBDA_CTRL_REG26;
    volatile U_QPG_QP_LAMBDA_CTRL_REG27 QPG_QP_LAMBDA_CTRL_REG27;
    volatile U_QPG_QP_LAMBDA_CTRL_REG28 QPG_QP_LAMBDA_CTRL_REG28;
    volatile U_QPG_QP_LAMBDA_CTRL_REG29 QPG_QP_LAMBDA_CTRL_REG29;
    volatile U_QPG_QP_LAMBDA_CTRL_REG30 QPG_QP_LAMBDA_CTRL_REG30;
    volatile U_QPG_QP_LAMBDA_CTRL_REG31 QPG_QP_LAMBDA_CTRL_REG31;
    volatile U_QPG_QP_LAMBDA_CTRL_REG32 QPG_QP_LAMBDA_CTRL_REG32;
    volatile U_QPG_QP_LAMBDA_CTRL_REG33 QPG_QP_LAMBDA_CTRL_REG33;
    volatile U_QPG_QP_LAMBDA_CTRL_REG34 QPG_QP_LAMBDA_CTRL_REG34;
    volatile U_QPG_QP_LAMBDA_CTRL_REG35 QPG_QP_LAMBDA_CTRL_REG35;
    volatile U_QPG_QP_LAMBDA_CTRL_REG36 QPG_QP_LAMBDA_CTRL_REG36;
    volatile U_QPG_QP_LAMBDA_CTRL_REG37 QPG_QP_LAMBDA_CTRL_REG37;
    volatile U_QPG_QP_LAMBDA_CTRL_REG38 QPG_QP_LAMBDA_CTRL_REG38;
    volatile U_QPG_QP_LAMBDA_CTRL_REG39 QPG_QP_LAMBDA_CTRL_REG39;
    volatile U_QPG_QP_LAMBDA_CTRL_REG40 QPG_QP_LAMBDA_CTRL_REG40;
    volatile U_QPG_QP_LAMBDA_CTRL_REG41 QPG_QP_LAMBDA_CTRL_REG41;
    volatile U_QPG_QP_LAMBDA_CTRL_REG42 QPG_QP_LAMBDA_CTRL_REG42;
    volatile U_QPG_QP_LAMBDA_CTRL_REG43 QPG_QP_LAMBDA_CTRL_REG43;
    volatile U_QPG_QP_LAMBDA_CTRL_REG44 QPG_QP_LAMBDA_CTRL_REG44;
    volatile U_QPG_QP_LAMBDA_CTRL_REG45 QPG_QP_LAMBDA_CTRL_REG45;
    volatile U_QPG_QP_LAMBDA_CTRL_REG46 QPG_QP_LAMBDA_CTRL_REG46;
    volatile U_QPG_QP_LAMBDA_CTRL_REG47 QPG_QP_LAMBDA_CTRL_REG47;
    volatile U_QPG_QP_LAMBDA_CTRL_REG48 QPG_QP_LAMBDA_CTRL_REG48;
    volatile U_QPG_QP_LAMBDA_CTRL_REG49 QPG_QP_LAMBDA_CTRL_REG49;
    volatile U_QPG_QP_LAMBDA_CTRL_REG50 QPG_QP_LAMBDA_CTRL_REG50;
    volatile U_QPG_QP_LAMBDA_CTRL_REG51 QPG_QP_LAMBDA_CTRL_REG51;
    volatile U_QPG_QP_LAMBDA_CTRL_REG52 QPG_QP_LAMBDA_CTRL_REG52;
    volatile U_QPG_QP_LAMBDA_CTRL_REG53 QPG_QP_LAMBDA_CTRL_REG53;
    volatile U_QPG_QP_LAMBDA_CTRL_REG54 QPG_QP_LAMBDA_CTRL_REG54;
    volatile U_QPG_QP_LAMBDA_CTRL_REG55 QPG_QP_LAMBDA_CTRL_REG55;
    volatile U_QPG_QP_LAMBDA_CTRL_REG56 QPG_QP_LAMBDA_CTRL_REG56;
    volatile U_QPG_QP_LAMBDA_CTRL_REG57 QPG_QP_LAMBDA_CTRL_REG57;
    volatile U_QPG_QP_LAMBDA_CTRL_REG58 QPG_QP_LAMBDA_CTRL_REG58;
    volatile U_QPG_QP_LAMBDA_CTRL_REG59 QPG_QP_LAMBDA_CTRL_REG59;
    volatile U_QPG_QP_LAMBDA_CTRL_REG60 QPG_QP_LAMBDA_CTRL_REG60;
    volatile U_QPG_QP_LAMBDA_CTRL_REG61 QPG_QP_LAMBDA_CTRL_REG61;
    volatile U_QPG_QP_LAMBDA_CTRL_REG62 QPG_QP_LAMBDA_CTRL_REG62;
    volatile U_QPG_QP_LAMBDA_CTRL_REG63 QPG_QP_LAMBDA_CTRL_REG63;
    volatile U_QPG_QP_LAMBDA_CTRL_REG64 QPG_QP_LAMBDA_CTRL_REG64;
    volatile U_QPG_QP_LAMBDA_CTRL_REG65 QPG_QP_LAMBDA_CTRL_REG65;
    volatile U_QPG_QP_LAMBDA_CTRL_REG66 QPG_QP_LAMBDA_CTRL_REG66;
    volatile U_QPG_QP_LAMBDA_CTRL_REG67 QPG_QP_LAMBDA_CTRL_REG67;
    volatile U_QPG_QP_LAMBDA_CTRL_REG68 QPG_QP_LAMBDA_CTRL_REG68;
    volatile U_QPG_QP_LAMBDA_CTRL_REG69 QPG_QP_LAMBDA_CTRL_REG69;
    volatile U_QPG_QP_LAMBDA_CTRL_REG70 QPG_QP_LAMBDA_CTRL_REG70;
    volatile U_QPG_QP_LAMBDA_CTRL_REG71 QPG_QP_LAMBDA_CTRL_REG71;
    volatile U_QPG_QP_LAMBDA_CTRL_REG72 QPG_QP_LAMBDA_CTRL_REG72;
    volatile U_QPG_QP_LAMBDA_CTRL_REG73 QPG_QP_LAMBDA_CTRL_REG73;
    volatile U_QPG_QP_LAMBDA_CTRL_REG74 QPG_QP_LAMBDA_CTRL_REG74;
    volatile U_QPG_QP_LAMBDA_CTRL_REG75 QPG_QP_LAMBDA_CTRL_REG75;
    volatile U_QPG_QP_LAMBDA_CTRL_REG76 QPG_QP_LAMBDA_CTRL_REG76;
    volatile U_QPG_QP_LAMBDA_CTRL_REG77 QPG_QP_LAMBDA_CTRL_REG77;
    volatile U_QPG_QP_LAMBDA_CTRL_REG78 QPG_QP_LAMBDA_CTRL_REG78;
    volatile U_QPG_QP_LAMBDA_CTRL_REG79 QPG_QP_LAMBDA_CTRL_REG79;
    volatile unsigned int           RESERVED4[4];
    volatile U_QPG_VERSION          QPG_VERSION;
    volatile unsigned int           RESERVED5[23];

} S_qpg_REGS_TYPE;





/*--------------Mrg   start 0x20620e00--------------------*/  
/* Define the union U_MRG_PMV_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmv_pu8_cnt           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    pmv_pu16_cnt          : 8   ; /* [15..8]  */
        unsigned int    pmv_pu32_cnt          : 5   ; /* [20..16]  */
        unsigned int    pmv_pu64_cnt          : 1   ; /* [21]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MRG_PMV_CNT;

/* Define the union U_MRG_FMV_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_pu8_cnt           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    fme_pu16_cnt          : 8   ; /* [15..8]  */
        unsigned int    fme_pu32_cnt          : 5   ; /* [20..16]  */
        unsigned int    fme_pu64_cnt          : 1   ; /* [21]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MRG_FMV_CNT;

/* Define the union U_MRG_LCU_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_oper_cnt          : 16  ; /* [15..0]  */
        unsigned int    lcu_oper_state        : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MRG_LCU_STA;

/* Define the union U_MRG_LCU_INFO_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_roikeep_en        : 16  ; /* [15..0]  */
        unsigned int    cu_info               : 2   ; /* [17..16]  */
        unsigned int    layer_info            : 2   ; /* [19..18]  */
        unsigned int    lcu_roikeep           : 1   ; /* [20]  */
        unsigned int    lcu_lpw_en            : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MRG_LCU_INFO_STA;

/*--------------Mrg  end 0x20620e00--------------------*/  


/* Mrg寄存器结构体   0x20620e00  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[8];
    volatile unsigned int           MRG_INT_GTCK_CNT;
    volatile unsigned int           MRG_FRAC_GTCK_CNT;
    volatile unsigned int           RESERVED1[2];
    volatile unsigned int           MRG_PU0_INFO;
    volatile unsigned int           MRG_PU1_INFO;
    volatile unsigned int           MRG_PU2_INFO;
    volatile unsigned int           MRG_PU3_INFO;
    volatile U_MRG_PMV_CNT          MRG_PMV_CNT;
    volatile U_MRG_FMV_CNT          MRG_FMV_CNT;
    volatile U_MRG_LCU_STA          MRG_LCU_STA;
    volatile U_MRG_LCU_INFO_STA     MRG_LCU_INFO_STA;
    volatile unsigned int           RESERVED2[108];

} S_mrg_REGS_TYPE;



/*--------------Fme  start 0x20621000--------------------*/  
/* Define the union U_FME_PMV_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmv_pu8_cnt           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    pmv_pu16_cnt          : 8   ; /* [15..8]  */
        unsigned int    pmv_pu32_cnt          : 5   ; /* [20..16]  */
        unsigned int    pmv_pu64_cnt          : 1   ; /* [21]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FME_PMV_CNT;

/* Define the union U_FME_IMV_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ime_pu8_cnt           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    ime_pu16_cnt          : 8   ; /* [15..8]  */
        unsigned int    ime_pu32_cnt          : 5   ; /* [20..16]  */
        unsigned int    ime_pu64_cnt          : 1   ; /* [21]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FME_IMV_CNT;

/* Define the union U_FME_FME_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_oper_cnt          : 16  ; /* [15..0]  */
        unsigned int    lcu_oper_state        : 1   ; /* [16]  */
        unsigned int    reserved_0            : 3   ; /* [19..17]  */
        unsigned int    pu_ctrl_state         : 2   ; /* [21..20]  */
        unsigned int    mv_ctrl_state         : 2   ; /* [23..22]  */
        unsigned int    lcu_lpw_en            : 1   ; /* [24]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_FME_FME_STA;

/*--------------Fme  end 0x20621000--------------------*/  


/* Fme寄存器结构体   0x20621000  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[8];
    volatile unsigned int           FME_GTCK_CNT;
    volatile unsigned int           RESERVED1[3];
    volatile U_FME_PMV_CNT          FME_PMV_CNT;
    volatile U_FME_IMV_CNT          FME_IMV_CNT;
    volatile U_FME_FME_STA          FME_FME_STA;
    volatile unsigned int           RESERVED2[113];

} S_fme_REGS_TYPE;








/*--------------Intra  start 0x20621200--------------------*/ 
/* Define the union U_INTER_AVAIL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    inter_avail           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTER_AVAIL;

/* Define the union U_INTRA_SMOOTH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_smooth          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_SMOOTH;

/* Define the union U_INTRA_BIT_WEIGHT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_bit_weight      : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_BIT_WEIGHT;

/* Define the union U_INTRA_CHNL4_ANG_0EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu4_mode0_en    : 1   ; /* [0]  */
        unsigned int    intra_cu4_mode1_en    : 1   ; /* [1]  */
        unsigned int    intra_cu4_mode2_en    : 1   ; /* [2]  */
        unsigned int    intra_cu4_mode3_en    : 1   ; /* [3]  */
        unsigned int    intra_cu4_mode4_en    : 1   ; /* [4]  */
        unsigned int    intra_cu4_mode5_en    : 1   ; /* [5]  */
        unsigned int    intra_cu4_mode6_en    : 1   ; /* [6]  */
        unsigned int    intra_cu4_mode7_en    : 1   ; /* [7]  */
        unsigned int    intra_cu4_mode8_en    : 1   ; /* [8]  */
        unsigned int    intra_cu4_mode9_en    : 1   ; /* [9]  */
        unsigned int    intra_cu4_mode10_en   : 1   ; /* [10]  */
        unsigned int    intra_cu4_mode11_en   : 1   ; /* [11]  */
        unsigned int    intra_cu4_mode12_en   : 1   ; /* [12]  */
        unsigned int    intra_cu4_mode13_en   : 1   ; /* [13]  */
        unsigned int    intra_cu4_mode14_en   : 1   ; /* [14]  */
        unsigned int    intra_cu4_mode15_en   : 1   ; /* [15]  */
        unsigned int    intra_cu4_mode16_en   : 1   ; /* [16]  */
        unsigned int    intra_cu4_mode17_en   : 1   ; /* [17]  */
        unsigned int    intra_cu4_mode18_en   : 1   ; /* [18]  */
        unsigned int    intra_cu4_mode19_en   : 1   ; /* [19]  */
        unsigned int    intra_cu4_mode20_en   : 1   ; /* [20]  */
        unsigned int    intra_cu4_mode21_en   : 1   ; /* [21]  */
        unsigned int    intra_cu4_mode22_en   : 1   ; /* [22]  */
        unsigned int    intra_cu4_mode23_en   : 1   ; /* [23]  */
        unsigned int    intra_cu4_mode24_en   : 1   ; /* [24]  */
        unsigned int    intra_cu4_mode25_en   : 1   ; /* [25]  */
        unsigned int    intra_cu4_mode26_en   : 1   ; /* [26]  */
        unsigned int    intra_cu4_mode27_en   : 1   ; /* [27]  */
        unsigned int    intra_cu4_mode28_en   : 1   ; /* [28]  */
        unsigned int    intra_cu4_mode29_en   : 1   ; /* [29]  */
        unsigned int    intra_cu4_mode30_en   : 1   ; /* [30]  */
        unsigned int    intra_cu4_mode31_en   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL4_ANG_0EN;

/* Define the union U_INTRA_CHNL4_ANG_1EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu4_mode32_en   : 1   ; /* [0]  */
        unsigned int    intra_cu4_mode33_en   : 1   ; /* [1]  */
        unsigned int    intra_cu4_mode34_en   : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL4_ANG_1EN;

/* Define the union U_INTRA_CHNL8_ANG_0EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu8_mode0_en    : 1   ; /* [0]  */
        unsigned int    intra_cu8_mode1_en    : 1   ; /* [1]  */
        unsigned int    intra_cu8_mode2_en    : 1   ; /* [2]  */
        unsigned int    intra_cu8_mode3_en    : 1   ; /* [3]  */
        unsigned int    intra_cu8_mode4_en    : 1   ; /* [4]  */
        unsigned int    intra_cu8_mode5_en    : 1   ; /* [5]  */
        unsigned int    intra_cu8_mode6_en    : 1   ; /* [6]  */
        unsigned int    intra_cu8_mode7_en    : 1   ; /* [7]  */
        unsigned int    intra_cu8_mode8_en    : 1   ; /* [8]  */
        unsigned int    intra_cu8_mode9_en    : 1   ; /* [9]  */
        unsigned int    intra_cu8_mode10_en   : 1   ; /* [10]  */
        unsigned int    intra_cu8_mode11_en   : 1   ; /* [11]  */
        unsigned int    intra_cu8_mode12_en   : 1   ; /* [12]  */
        unsigned int    intra_cu8_mode13_en   : 1   ; /* [13]  */
        unsigned int    intra_cu8_mode14_en   : 1   ; /* [14]  */
        unsigned int    intra_cu8_mode15_en   : 1   ; /* [15]  */
        unsigned int    intra_cu8_mode16_en   : 1   ; /* [16]  */
        unsigned int    intra_cu8_mode17_en   : 1   ; /* [17]  */
        unsigned int    intra_cu8_mode18_en   : 1   ; /* [18]  */
        unsigned int    intra_cu8_mode19_en   : 1   ; /* [19]  */
        unsigned int    intra_cu8_mode20_en   : 1   ; /* [20]  */
        unsigned int    intra_cu8_mode21_en   : 1   ; /* [21]  */
        unsigned int    intra_cu8_mode22_en   : 1   ; /* [22]  */
        unsigned int    intra_cu8_mode23_en   : 1   ; /* [23]  */
        unsigned int    intra_cu8_mode24_en   : 1   ; /* [24]  */
        unsigned int    intra_cu8_mode25_en   : 1   ; /* [25]  */
        unsigned int    intra_cu8_mode26_en   : 1   ; /* [26]  */
        unsigned int    intra_cu8_mode27_en   : 1   ; /* [27]  */
        unsigned int    intra_cu8_mode28_en   : 1   ; /* [28]  */
        unsigned int    intra_cu8_mode29_en   : 1   ; /* [29]  */
        unsigned int    intra_cu8_mode30_en   : 1   ; /* [30]  */
        unsigned int    intra_cu8_mode31_en   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL8_ANG_0EN;

/* Define the union U_INTRA_CHNL8_ANG_1EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu8_mode32_en   : 1   ; /* [0]  */
        unsigned int    intra_cu8_mode33_en   : 1   ; /* [1]  */
        unsigned int    intra_cu8_mode34_en   : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL8_ANG_1EN;

/* Define the union U_INTRA_CHNL16_ANG_0EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu16_mode0_en   : 1   ; /* [0]  */
        unsigned int    intra_cu16_mode1_en   : 1   ; /* [1]  */
        unsigned int    intra_cu16_mode2_en   : 1   ; /* [2]  */
        unsigned int    intra_cu16_mode3_en   : 1   ; /* [3]  */
        unsigned int    intra_cu16_mode4_en   : 1   ; /* [4]  */
        unsigned int    intra_cu16_mode5_en   : 1   ; /* [5]  */
        unsigned int    intra_cu16_mode6_en   : 1   ; /* [6]  */
        unsigned int    intra_cu16_mode7_en   : 1   ; /* [7]  */
        unsigned int    intra_cu16_mode8_en   : 1   ; /* [8]  */
        unsigned int    intra_cu16_mode9_en   : 1   ; /* [9]  */
        unsigned int    intra_cu16_mode10_en  : 1   ; /* [10]  */
        unsigned int    intra_cu16_mode11_en  : 1   ; /* [11]  */
        unsigned int    intra_cu16_mode12_en  : 1   ; /* [12]  */
        unsigned int    intra_cu16_mode13_en  : 1   ; /* [13]  */
        unsigned int    intra_cu16_mode14_en  : 1   ; /* [14]  */
        unsigned int    intra_cu16_mode15_en  : 1   ; /* [15]  */
        unsigned int    intra_cu16_mode16_en  : 1   ; /* [16]  */
        unsigned int    intra_cu16_mode17_en  : 1   ; /* [17]  */
        unsigned int    intra_cu16_mode18_en  : 1   ; /* [18]  */
        unsigned int    intra_cu16_mode19_en  : 1   ; /* [19]  */
        unsigned int    intra_cu16_mode20_en  : 1   ; /* [20]  */
        unsigned int    intra_cu16_mode21_en  : 1   ; /* [21]  */
        unsigned int    intra_cu16_mode22_en  : 1   ; /* [22]  */
        unsigned int    intra_cu16_mode23_en  : 1   ; /* [23]  */
        unsigned int    intra_cu16_mode24_en  : 1   ; /* [24]  */
        unsigned int    intra_cu16_mode25_en  : 1   ; /* [25]  */
        unsigned int    intra_cu16_mode26_en  : 1   ; /* [26]  */
        unsigned int    intra_cu16_mode27_en  : 1   ; /* [27]  */
        unsigned int    intra_cu16_mode28_en  : 1   ; /* [28]  */
        unsigned int    intra_cu16_mode29_en  : 1   ; /* [29]  */
        unsigned int    intra_cu16_mode30_en  : 1   ; /* [30]  */
        unsigned int    intra_cu16_mode31_en  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL16_ANG_0EN;

/* Define the union U_INTRA_CHNL16_ANG_1EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu16_mode32_en  : 1   ; /* [0]  */
        unsigned int    intra_cu16_mode33_en  : 1   ; /* [1]  */
        unsigned int    intra_cu16_mode34_en  : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL16_ANG_1EN;

/* Define the union U_INTRA_CHNL32_ANG_0EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu32_mode0_en   : 1   ; /* [0]  */
        unsigned int    intra_cu32_mode1_en   : 1   ; /* [1]  */
        unsigned int    intra_cu32_mode2_en   : 1   ; /* [2]  */
        unsigned int    intra_cu32_mode3_en   : 1   ; /* [3]  */
        unsigned int    intra_cu32_mode4_en   : 1   ; /* [4]  */
        unsigned int    intra_cu32_mode5_en   : 1   ; /* [5]  */
        unsigned int    intra_cu32_mode6_en   : 1   ; /* [6]  */
        unsigned int    intra_cu32_mode7_en   : 1   ; /* [7]  */
        unsigned int    intra_cu32_mode8_en   : 1   ; /* [8]  */
        unsigned int    intra_cu32_mode9_en   : 1   ; /* [9]  */
        unsigned int    intra_cu32_mode10_en  : 1   ; /* [10]  */
        unsigned int    intra_cu32_mode11_en  : 1   ; /* [11]  */
        unsigned int    intra_cu32_mode12_en  : 1   ; /* [12]  */
        unsigned int    intra_cu32_mode13_en  : 1   ; /* [13]  */
        unsigned int    intra_cu32_mode14_en  : 1   ; /* [14]  */
        unsigned int    intra_cu32_mode15_en  : 1   ; /* [15]  */
        unsigned int    intra_cu32_mode16_en  : 1   ; /* [16]  */
        unsigned int    intra_cu32_mode17_en  : 1   ; /* [17]  */
        unsigned int    intra_cu32_mode18_en  : 1   ; /* [18]  */
        unsigned int    intra_cu32_mode19_en  : 1   ; /* [19]  */
        unsigned int    intra_cu32_mode20_en  : 1   ; /* [20]  */
        unsigned int    intra_cu32_mode21_en  : 1   ; /* [21]  */
        unsigned int    intra_cu32_mode22_en  : 1   ; /* [22]  */
        unsigned int    intra_cu32_mode23_en  : 1   ; /* [23]  */
        unsigned int    intra_cu32_mode24_en  : 1   ; /* [24]  */
        unsigned int    intra_cu32_mode25_en  : 1   ; /* [25]  */
        unsigned int    intra_cu32_mode26_en  : 1   ; /* [26]  */
        unsigned int    intra_cu32_mode27_en  : 1   ; /* [27]  */
        unsigned int    intra_cu32_mode28_en  : 1   ; /* [28]  */
        unsigned int    intra_cu32_mode29_en  : 1   ; /* [29]  */
        unsigned int    intra_cu32_mode30_en  : 1   ; /* [30]  */
        unsigned int    intra_cu32_mode31_en  : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL32_ANG_0EN;

/* Define the union U_INTRA_CHNL32_ANG_1EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_cu32_mode32_en  : 1   ; /* [0]  */
        unsigned int    intra_cu32_mode33_en  : 1   ; /* [1]  */
        unsigned int    intra_cu32_mode34_en  : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_CHNL32_ANG_1EN;

/* Define the union U_INTRA_DFX_FRM_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_frm_cnt           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_FRM_CNT;

/* Define the union U_INTRA_DFX_LCU_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_lcu_cnt           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_LCU_CNT;

/* Define the union U_INTRA_DFX_LCU_END_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_lcu_end_cnt       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_LCU_END_CNT;

/* Define the union U_INTRA_DFX_LCU_CYCLE_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_lcu_cycle_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_LCU_CYCLE_CNT;

/* Define the union U_INTRA_DFX_NBI_RD_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_nbi_rd_cnt        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_NBI_RD_CNT;

/* Define the union U_INTRA_DFX_NBI_WR_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_nbi_wr_cnt        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_NBI_WR_CNT;

/* Define the union U_INTRA_DFX_CU8_DONE_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu8_done_cnt      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU8_DONE_CNT;

/* Define the union U_INTRA_DFX_CU16_DONE_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu16_done_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU16_DONE_CNT;

/* Define the union U_INTRA_DFX_CU32_DONE_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu32_done_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU32_DONE_CNT;

/* Define the union U_INTRA_DFX_CU64_DONE_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu64_done_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU64_DONE_CNT;

/* Define the union U_INTRA_DFX_CU8_RDO_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu8_rdo_cnt       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU8_RDO_CNT;

/* Define the union U_INTRA_DFX_CU16_RDO_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu16_rdo_cnt      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU16_RDO_CNT;

/* Define the union U_INTRA_DFX_CU32_RDO_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu32_rdo_cnt      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU32_RDO_CNT;

/* Define the union U_INTRA_DFX_CU8_FSM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu8_fsm           : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU8_FSM;

/* Define the union U_INTRA_DFX_CU16_FSM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu16_fsm          : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU16_FSM;

/* Define the union U_INTRA_DFX_CU32_FSM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu32_fsm          : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_CU32_FSM;

/* Define the union U_INTRA_DFX_PCM_PWR__TYPE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_pcm               : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    dfx_lpw               : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    dfx_frm_type          : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_PCM_PWR__TYPE;

/* Define the union U_INTRA_DFX_HEAD_BIT_WEIGHT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_head_bit_weight   : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_HEAD_BIT_WEIGHT;

/* Define the union U_INTRA_DFX_RDO_WEIGHT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_rdo_weight        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_RDO_WEIGHT;

/* Define the union U_INTRA_DFX_BLK_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_cu4_idx           : 8   ; /* [7..0]  */
        unsigned int    dfx_cu8_idx           : 6   ; /* [13..8]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    dfx_cu16_idx          : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 4   ; /* [23..20]  */
        unsigned int    dfx_cu32_idx          : 2   ; /* [25..24]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTRA_DFX_BLK_CNT;


/*--------------Intra  end 0x20621200--------------------*/  


/* Intra寄存器结构体   0x20621200  */

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_INTER_AVAIL          INTER_AVAIL;
    volatile U_INTRA_SMOOTH         INTRA_SMOOTH;
    volatile unsigned int           RESERVED0;
    volatile U_INTRA_BIT_WEIGHT     INTRA_BIT_WEIGHT;
    volatile unsigned int           RESERVED1[4];
    volatile U_INTRA_CHNL4_ANG_0EN  INTRA_CHNL4_ANG_0EN;
    volatile U_INTRA_CHNL4_ANG_1EN  INTRA_CHNL4_ANG_1EN;
    volatile U_INTRA_CHNL8_ANG_0EN  INTRA_CHNL8_ANG_0EN;
    volatile U_INTRA_CHNL8_ANG_1EN  INTRA_CHNL8_ANG_1EN;
    volatile U_INTRA_CHNL16_ANG_0EN INTRA_CHNL16_ANG_0EN;
    volatile U_INTRA_CHNL16_ANG_1EN INTRA_CHNL16_ANG_1EN;
    volatile U_INTRA_CHNL32_ANG_0EN INTRA_CHNL32_ANG_0EN;
    volatile U_INTRA_CHNL32_ANG_1EN INTRA_CHNL32_ANG_1EN;
    volatile U_INTRA_DFX_FRM_CNT    INTRA_DFX_FRM_CNT;
    volatile U_INTRA_DFX_LCU_CNT    INTRA_DFX_LCU_CNT;
    volatile U_INTRA_DFX_LCU_END_CNT INTRA_DFX_LCU_END_CNT;
    volatile U_INTRA_DFX_LCU_CYCLE_CNT INTRA_DFX_LCU_CYCLE_CNT;
    volatile U_INTRA_DFX_NBI_RD_CNT INTRA_DFX_NBI_RD_CNT;
    volatile U_INTRA_DFX_NBI_WR_CNT INTRA_DFX_NBI_WR_CNT;
    volatile unsigned int           RESERVED2[2];
    volatile U_INTRA_DFX_CU8_DONE_CNT INTRA_DFX_CU8_DONE_CNT;
    volatile U_INTRA_DFX_CU16_DONE_CNT INTRA_DFX_CU16_DONE_CNT;
    volatile U_INTRA_DFX_CU32_DONE_CNT INTRA_DFX_CU32_DONE_CNT;
    volatile U_INTRA_DFX_CU64_DONE_CNT INTRA_DFX_CU64_DONE_CNT;
    volatile U_INTRA_DFX_CU8_RDO_CNT INTRA_DFX_CU8_RDO_CNT;
    volatile U_INTRA_DFX_CU16_RDO_CNT INTRA_DFX_CU16_RDO_CNT;
    volatile U_INTRA_DFX_CU32_RDO_CNT INTRA_DFX_CU32_RDO_CNT;
    volatile unsigned int           RESERVED3;
    volatile U_INTRA_DFX_CU8_FSM    INTRA_DFX_CU8_FSM;
    volatile U_INTRA_DFX_CU16_FSM   INTRA_DFX_CU16_FSM;
    volatile U_INTRA_DFX_CU32_FSM   INTRA_DFX_CU32_FSM;
    volatile unsigned int           RESERVED4;
    volatile U_INTRA_DFX_PCM_PWR__TYPE INTRA_DFX_PCM_PWR__TYPE;
    volatile U_INTRA_DFX_HEAD_BIT_WEIGHT INTRA_DFX_HEAD_BIT_WEIGHT;
    volatile U_INTRA_DFX_RDO_WEIGHT INTRA_DFX_RDO_WEIGHT;
    volatile U_INTRA_DFX_BLK_CNT    INTRA_DFX_BLK_CNT;
    volatile unsigned int           RESERVED5[88];

} S_intra_REGS_TYPE;







/*--------------Pmv  start 0x20621400--------------------*/  

/* Define the union U_PMV_CNT_FRAME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_lcu_done          : 8   ; /* [7..0]  */
        unsigned int    cnt_lcu_start         : 8   ; /* [15..8]  */
        unsigned int    cnt_frame             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_CNT_FRAME;

/* Define the union U_PMV_TMV_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_0_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_0_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_0_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_0;

/* Define the union U_PMV_TMV_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_1_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_1_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_1_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_1;

/* Define the union U_PMV_TMV_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_2_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_2_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_2_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_2;

/* Define the union U_PMV_TMV_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_3_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_3_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_3_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_3;

/* Define the union U_PMV_TMV_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_4_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_4_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_4_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_4;

/* Define the union U_PMV_TMV_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_5_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_5_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_5_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_5;

/* Define the union U_PMV_TMV_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_6_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_6_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_6_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_6;

/* Define the union U_PMV_TMV_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_7_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_7_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_7_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_7;

/* Define the union U_PMV_TMV_8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_8_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_8_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_8_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_8;

/* Define the union U_PMV_TMV_9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_9_ver             : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_9_hor             : 13  ; /* [28..16]  */
        unsigned int    tmv_9_vld             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_9;

/* Define the union U_PMV_TMV_10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_10_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_10_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_10_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_10;

/* Define the union U_PMV_TMV_11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_11_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_11_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_11_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_11;

/* Define the union U_PMV_TMV_12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_12_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_12_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_12_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_12;

/* Define the union U_PMV_TMV_13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_13_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_13_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_13_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_13;

/* Define the union U_PMV_TMV_14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_14_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_14_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_14_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_14;

/* Define the union U_PMV_TMV_15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_15_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_15_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_15_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_15;

/* Define the union U_PMV_TMV_16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_16_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_16_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_16_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_16;

/* Define the union U_PMV_TMV_17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_17_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_17_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_17_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_17;

/* Define the union U_PMV_TMV_18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_18_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_18_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_18_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_18;

/* Define the union U_PMV_TMV_19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_19_ver            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    tmv_19_hor            : 13  ; /* [28..16]  */
        unsigned int    tmv_19_vld            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_19;

/* Define the union U_PMV_TMV_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tmv_en                : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PMV_TMV_EN;

/*--------------Pmv end 0x20621400--------------------*/  

/* Pmv寄存器结构体   0x20621400  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_PMV_CNT_FRAME        PMV_CNT_FRAME;
    volatile U_PMV_TMV_0            PMV_TMV_0;
    volatile U_PMV_TMV_1            PMV_TMV_1;
    volatile U_PMV_TMV_2            PMV_TMV_2;
    volatile U_PMV_TMV_3            PMV_TMV_3;
    volatile U_PMV_TMV_4            PMV_TMV_4;
    volatile U_PMV_TMV_5            PMV_TMV_5;
    volatile U_PMV_TMV_6            PMV_TMV_6;
    volatile U_PMV_TMV_7            PMV_TMV_7;
    volatile U_PMV_TMV_8            PMV_TMV_8;
    volatile U_PMV_TMV_9            PMV_TMV_9;
    volatile U_PMV_TMV_10           PMV_TMV_10;
    volatile U_PMV_TMV_11           PMV_TMV_11;
    volatile U_PMV_TMV_12           PMV_TMV_12;
    volatile U_PMV_TMV_13           PMV_TMV_13;
    volatile U_PMV_TMV_14           PMV_TMV_14;
    volatile U_PMV_TMV_15           PMV_TMV_15;
    volatile U_PMV_TMV_16           PMV_TMV_16;
    volatile U_PMV_TMV_17           PMV_TMV_17;
    volatile U_PMV_TMV_18           PMV_TMV_18;
    volatile U_PMV_TMV_19           PMV_TMV_19;
    volatile U_PMV_TMV_EN           PMV_TMV_EN;
    volatile unsigned int           RESERVED0[106];

} S_pmv_REGS_TYPE;








/*--------------Tqitq   start 0x20621600--------------------*/
/* Define the union U_TQITQ_QSCALINGLIST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    q_scaling_wdata       : 16  ; /* [15..0]  */
        unsigned int    q_scaling_waddr       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TQITQ_QSCALINGLIST;

/*--------------Tqitq   end 0x20621600--------------------*/ 


/* Tqitq寄存器结构体   0x20621600  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_TQITQ_QSCALINGLIST   TQITQ_QSCALINGLIST;
    volatile unsigned int           TQITQ_LCU_COUNT;
    volatile unsigned int           RESERVED0[2];
    volatile unsigned int           TQITQ_TU4GATE_ENCNT;
    volatile unsigned int           TQITQ_DST4GATE_ENCNT;
    volatile unsigned int           TQITQ_TU8GATE_ENCNT;
    volatile unsigned int           TQITQ_TU16GATE_ENCNT;
    volatile unsigned int           TQITQ_TU32GATE_ENCNT;
    volatile unsigned int           RESERVED1[119];

} S_tqitq_REGS_TYPE;






/*--------------Sel    start 0x20621800--------------------*/ 
/* Define the union U_SEL_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opt_8x8_cnt          : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_OPT_8X8_CNT;

/* Define the union U_SEL_INTRA_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_opt_8x8_cnt  : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTRA_OPT_8X8_CNT;

/* Define the union U_SEL_INTRA_NORMAL_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
       unsigned int    intra_normal_opt_8x8_cnt : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTRA_NORMAL_OPT_8X8_CNT;

/* Define the union U_SEL_INTRA_PCM_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcm_opt_8x8_cnt       : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTRA_PCM_OPT_8X8_CNT;

/* Define the union U_SEL_INTER_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    inter_opt_8x8_cnt     : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_OPT_8X8_CNT;

/* Define the union U_SEL_INTER_FME_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_opt_8x8_cnt       : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_FME_OPT_8X8_CNT;

/* Define the union U_SEL_INTER_MERGE_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_opt_8x8_cnt       : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_MERGE_OPT_8X8_CNT;

/* Define the union U_SEL_INTER_SKIP_OPT_8X8_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_skip_opt_8x8_cnt  : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_SKIP_OPT_8X8_CNT;

/* Define the union U_SEL_OPT_16X16_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opt_16x16_cnt         : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_OPT_16X16_CNT;

/* Define the union U_SEL_INTRA_OPT_16X16_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_opt_16x16_cnt   : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTRA_OPT_16X16_CNT;

/* Define the union U_SEL_OPT_4X4_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opt_4x4_cnt           : 19  ; /* [18..0]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_OPT_4X4_CNT;

/* Define the union U_SEL_INTER_OPT_16X16_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    inter_opt_16x16_cnt   : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_OPT_16X16_CNT;

/* Define the union U_SEL_INTER_FME_OPT_16X16_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_opt_16x16_cnt     : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_FME_OPT_16X16_CNT;

/* Define the union U_SEL_INTER_MERGE_OPT_16X16_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_opt_16x16_cnt     : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_MERGE_OPT_16X16_CNT;

/* Define the union U_SEL_INTER_SKIP_OPT_16X16_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_skip_opt_16x16_cnt : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_SKIP_OPT_16X16_CNT;


/* Define the union U_SEL_OPT_32X32_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opt_32x32_cnt         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_OPT_32X32_CNT;

/* Define the union U_SEL_INTRA_OPT_32X32_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intra_opt_32x32_cnt   : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTRA_OPT_32X32_CNT;

/* Define the union U_SEL_INTER_OPT_32X32_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    inter_opt_32x32_cnt   : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_OPT_32X32_CNT;

/* Define the union U_SEL_INTER_FME_OPT_32X32_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_opt_32x32_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_FME_OPT_32X32_CNT;

/* Define the union U_SEL_INTER_MERGE_OPT_32X32_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_opt_32x32_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_MERGE_OPT_32X32_CNT;

/* Define the union U_SEL_INTER_SKIP_OPT_32X32_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_skip_opt_32x32_cnt : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_SKIP_OPT_32X32_CNT;

/* Define the union U_SEL_OPT_64X64_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opt_64x64_cnt         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_OPT_64X64_CNT;

/* Define the union U_SEL_INTER_FME_OPT_64X64_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fme_opt_64x64_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_FME_OPT_64X64_CNT;

/* Define the union U_SEL_INTER_MERGE_OPT_64X64_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_opt_64x64_cnt     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_MERGE_OPT_64X64_CNT;

/* Define the union U_SEL_INTER_SKIP_OPT_64X64_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_skip_opt_64x64_cnt : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_INTER_SKIP_OPT_64X64_CNT;

/* Define the union U_SEL_TOTAL_LUMA_QP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    total_luma_qp         : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_TOTAL_LUMA_QP;

/* Define the union U_SEL_VERSION */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    version               : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEL_VERSION;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_SEL_OPT_8X8_CNT      SEL_OPT_8X8_CNT;
    volatile U_SEL_INTRA_OPT_8X8_CNT SEL_INTRA_OPT_8X8_CNT;
    volatile U_SEL_INTRA_NORMAL_OPT_8X8_CNT SEL_INTRA_NORMAL_OPT_8X8_CNT;
    volatile U_SEL_INTRA_PCM_OPT_8X8_CNT SEL_INTRA_PCM_OPT_8X8_CNT;
    volatile U_SEL_INTER_OPT_8X8_CNT SEL_INTER_OPT_8X8_CNT;
    volatile U_SEL_INTER_FME_OPT_8X8_CNT SEL_INTER_FME_OPT_8X8_CNT;
    volatile U_SEL_INTER_MERGE_OPT_8X8_CNT SEL_INTER_MERGE_OPT_8X8_CNT;
    volatile U_SEL_INTER_SKIP_OPT_8X8_CNT SEL_INTER_SKIP_OPT_8X8_CNT;
    volatile U_SEL_OPT_16X16_CNT    SEL_OPT_16X16_CNT;
    volatile U_SEL_INTRA_OPT_16X16_CNT SEL_INTRA_OPT_16X16_CNT;
    volatile U_SEL_OPT_4X4_CNT      SEL_OPT_4X4_CNT;
    volatile unsigned int           RESERVED0;
    volatile U_SEL_INTER_OPT_16X16_CNT SEL_INTER_OPT_16X16_CNT;
    volatile U_SEL_INTER_FME_OPT_16X16_CNT SEL_INTER_FME_OPT_16X16_CNT;
    volatile U_SEL_INTER_MERGE_OPT_16X16_CNT SEL_INTER_MERGE_OPT_16X16_CNT;
    volatile U_SEL_INTER_SKIP_OPT_16X16_CNT SEL_INTER_SKIP_OPT_16X16_CNT;
    volatile U_SEL_OPT_32X32_CNT    SEL_OPT_32X32_CNT;
    volatile U_SEL_INTRA_OPT_32X32_CNT SEL_INTRA_OPT_32X32_CNT;
    volatile unsigned int           RESERVED1;
    volatile U_SEL_INTER_OPT_32X32_CNT SEL_INTER_OPT_32X32_CNT;
    volatile U_SEL_INTER_FME_OPT_32X32_CNT SEL_INTER_FME_OPT_32X32_CNT;
    volatile U_SEL_INTER_MERGE_OPT_32X32_CNT SEL_INTER_MERGE_OPT_32X32_CNT;
    volatile U_SEL_INTER_SKIP_OPT_32X32_CNT SEL_INTER_SKIP_OPT_32X32_CNT;
    volatile U_SEL_OPT_64X64_CNT    SEL_OPT_64X64_CNT;
    volatile U_SEL_INTER_FME_OPT_64X64_CNT SEL_INTER_FME_OPT_64X64_CNT;
    volatile U_SEL_INTER_MERGE_OPT_64X64_CNT SEL_INTER_MERGE_OPT_64X64_CNT;
    volatile U_SEL_INTER_SKIP_OPT_64X64_CNT SEL_INTER_SKIP_OPT_64X64_CNT;
    volatile U_SEL_TOTAL_LUMA_QP    SEL_TOTAL_LUMA_QP;
    volatile unsigned int           RESERVED2[4];
    volatile U_SEL_VERSION          SEL_VERSION;
    volatile unsigned int           RESERVED3[95];

} S_sel_REGS_TYPE;







/*--------------Dblk    start 0x20621a00--------------------*/  
/* Define the union U_dblk_frame_cnt */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_cnt             : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_dblk_frame_cnt;

/* Define the union U_dblk_lcu_cnt */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_cnt               : 18  ; /* [17..0]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_dblk_lcu_cnt;

/* Define the union U_dblk_dfx_flag */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_sao_cft_ls_c       : 1   ; /* [0]  */
        unsigned int    db_sao_cft_us_c       : 1   ; /* [1]  */
        unsigned int    db_sao_cft_ls         : 1   ; /* [2]  */
        unsigned int    db_sao_cft_us         : 1   ; /* [3]  */
        unsigned int    reserved0             : 6   ; /* [9..4]  */
        unsigned int    fsm_error_c           : 1   ; /* [10]  */
        unsigned int    fsm_error             : 1   ; /* [11]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_dblk_dfx_flag;

/*--------------Dblk    end  0x20621a00--------------------*/ 


/* Dblk寄存器结构体   0x20621a00  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[32];
    volatile U_dblk_frame_cnt       dblk_frame_cnt;
    volatile U_dblk_lcu_cnt         dblk_lcu_cnt;
    volatile U_dblk_dfx_flag        dblk_dfx_flag;
    volatile unsigned int           RESERVED1[93];

} S_dblk_REGS_TYPE;







/*--------------Sao    start 0x20621c00--------------------*/ 
/* Define the union U_SAO_FSM_DFX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sao2vcpi_fsm_dfx      : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SAO_FSM_DFX;

/* Define the union U_SAO_LCU_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sao2vcpi_lcu_cnt      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SAO_LCU_CNT;

/* Define the union U_SAO_OFF_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sao2vcpi_saooff_num_luma : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    sao2vcpi_saooff_num_chroma : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SAO_OFF_NUM;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[29];
    volatile U_SAO_FSM_DFX          SAO_FSM_DFX;
    volatile U_SAO_LCU_CNT          SAO_LCU_CNT;
    volatile U_SAO_OFF_NUM          SAO_OFF_NUM;
    volatile unsigned int           RESERVED1[96];

} S_sao_REGS_TYPE;






/*--------------Pack    start 0x20621e00--------------------*/
/* Define the union U_PACK_CU_PARAMETER */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi2cu_tq_bypass_enabled_flag : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    vcpi2cu_qp_min_cu_size : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PACK_CU_PARAMETER;

/* Define the union U_PACK_PCM_PARAMETER */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi2pu_log2_min_ipcm_cbsizey : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vcpi2pu_log2_max_ipcm_cbsizey : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PACK_PCM_PARAMETER;

/* Define the union U_PACK_TF_SKIP_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi2res_tf_skip_enabled_flag : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PACK_TF_SKIP_FLAG;

/*--------------Pack    end  0x20621e00--------------------*/


/* Pack寄存器结构体   0x20621e00  */
/* Define the global struct */
typedef struct
{
    volatile unsigned int           PACK_DFX_0;
    volatile U_PACK_CU_PARAMETER    PACK_CU_PARAMETER;
    volatile U_PACK_PCM_PARAMETER   PACK_PCM_PARAMETER;
    volatile U_PACK_TF_SKIP_FLAG    PACK_TF_SKIP_FLAG;
    volatile unsigned int           PACK_DFX_1;
    volatile unsigned int           PACK_DFX_ERR_CNT;
    volatile unsigned int           PACK_DFX_FSM;
    volatile unsigned int           PACK_DFX_FIFO_STATE;
    volatile unsigned int           RESERVED2[120];

} S_pack_REGS_TYPE;








/*--------------Cabac    start 0x20622000--------------------*/
/* Define the union U_CABAC_GLB_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    max_num_mergecand     : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 5   ; /* [15..11]  */
        unsigned int    nal_unit_head         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CABAC_GLB_CFG;

/* Define the union U_CABAC_SLCHDR_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slchdr_size_part1     : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 11  ; /* [15..5]  */
        unsigned int    slchdr_size_part2     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CABAC_SLCHDR_SIZE;

/* Define the union U_CABAC_SLCHDR_PART1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slchdr_part1          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CABAC_SLCHDR_PART1;

/*--------------Cabac    end  0x20622000--------------------*/


/* Cabac寄存器结构体   0x20622000  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_CABAC_GLB_CFG        CABAC_GLB_CFG;
    volatile U_CABAC_SLCHDR_SIZE    CABAC_SLCHDR_SIZE;
    volatile U_CABAC_SLCHDR_PART1   CABAC_SLCHDR_PART1;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG1;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG2;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG3;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG4;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG5;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG6;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG7;
    volatile unsigned int           CABAC_SLCHDR_PART2_SEG8;
    volatile unsigned int           RESERVED0[21];
    volatile unsigned int           CABAC_PIC_STRMSIZE;
    volatile unsigned int           RESERVED1[31];
    volatile unsigned int           CABAC_DFX_0;
    volatile unsigned int           CABAC_DFX_1;
    volatile unsigned int           CABAC_DFX_2;
    volatile unsigned int           CABAC_DFX_3;
    volatile unsigned int           CABAC_DFX_4;
    volatile unsigned int           CABAC_DFX_5;
    volatile unsigned int           RESERVED2[58];

} S_cabac_REGS_TYPE;






/*--------------Pmeld     start 0x20622200--------------------*/ 
/*--------------Pmeld     end  0x20622200--------------------*/
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[128];

} S_pmeld_REGS_TYPE;




/*--------------Pmest     start 0x20622400--------------------*/  
/*--------------Pmest     end  0x20622400--------------------*/ 
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           PMEST_DFX_0;
    volatile unsigned int           PMEST_DFX_1;
    volatile unsigned int           PMEST_DFX_2;
    volatile unsigned int           RESERVED0[125];

} S_pmest_REGS_TYPE;





/*--------------nbi     start 0x20622600--------------------*/
/* Define the union U_NBI_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ld_fifo_empty         : 1   ; /* [0]  */
        unsigned int    ld_fifo_full          : 1   ; /* [1]  */
        unsigned int    ld_fsm_state          : 2   ; /* [3..2]  */
        unsigned int    st_fifo_empty         : 1   ; /* [4]  */
        unsigned int    st_fifo_full          : 1   ; /* [5]  */
        unsigned int    st_fsm_state          : 2   ; /* [7..6]  */
        unsigned int    tmv_wr_en             : 1   ; /* [8]  */
        unsigned int    tmv_rd_en             : 1   ; /* [9]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NBI_STATE;

/* Define the union U_NBI_STATE_UP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fsm_state_up          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NBI_STATE_UP;

/* Define the union U_NBI_LCU_COUNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lcu_cnt               : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NBI_LCU_COUNT;

/* Define the union U_NBI_TILE_COUNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tile_cnt              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NBI_TILE_COUNT;

/* Define the union U_NBI_FRAME_COUNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_cnt             : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NBI_FRAME_COUNT;

/*--------------nbi     end  0x20622600--------------------*/ 

/* nbi寄存器结构体   0x20622600  */


/*--------------RESERVED     start 0x20622800--------------------*/  
/*--------------RESERVED     end  0x20622800--------------------*/  
/* RESERVED保留 0x20622800  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[4];
    volatile U_NBI_STATE            NBI_STATE;
    volatile U_NBI_STATE_UP         NBI_STATE_UP;
    volatile unsigned int           RESERVED1[2];
    volatile U_NBI_LCU_COUNT        NBI_LCU_COUNT;
    volatile U_NBI_TILE_COUNT       NBI_TILE_COUNT;
    volatile U_NBI_FRAME_COUNT      NBI_FRAME_COUNT;
    volatile unsigned int           RESERVED2[117];

} S_nbi_REGS_TYPE;




/*--------------Unvld       start 0x20623200--------------------*/ 
/*--------------Unvld       end  0x20623200--------------------*/ 
/* unvld  寄存器结构体   0x20622800  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[128];

} S_unvld_REGS_TYPE;





/*--------------recst     start 0x20622a00--------------------*/  
/*--------------recst     end  0x20622a00--------------------*/ 

/* recst寄存器结构体   0x20622a00  */
/* Define the union U_RECST_DDR_CROSS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_cross_idx         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RECST_DDR_CROSS;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_RECST_DDR_CROSS      RECST_DDR_CROSS;
    volatile unsigned int           RESERVED0[31];
    volatile unsigned int           RECST_DFX_0;
    volatile unsigned int           RECST_DFX_1;
    volatile unsigned int           RECST_DFX_2;
    volatile unsigned int           RECST_DFX_3;
    volatile unsigned int           RECST_DFX_4;
    volatile unsigned int           RECST_DFX_5;
    volatile unsigned int           RECST_DFX_6;
    volatile unsigned int           RECST_DFX_7;
    volatile unsigned int           RESERVED1[88];

} S_recst_REGS_TYPE;







/*--------------vlcst      start 0x20622c00--------------------*/
/* Define the union U_VLCST_PTBITS_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ptbits_en             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_PTBITS_EN;

/* Define the union U_VLCST_PARAMETER */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vlcst_para_set_len    : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    vlcst_para_set_en     : 1   ; /* [16]  */
        unsigned int    reserved_1            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_PARAMETER;

/* Define the union U_VLCST_DSRPTR00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len0              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR00;

/* Define the union U_VLCST_DSRPTR01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum0           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR01;

/* Define the union U_VLCST_DSRPTR10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len1              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR10;

/* Define the union U_VLCST_DSRPTR11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum1           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR11;

/* Define the union U_VLCST_DSRPTR20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len2              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR20;

/* Define the union U_VLCST_DSRPTR21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum2           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc2            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR21;

/* Define the union U_VLCST_DSRPTR30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len3              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR30;

/* Define the union U_VLCST_DSRPTR31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum3           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR31;

/* Define the union U_VLCST_DSRPTR40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len4              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR40;

/* Define the union U_VLCST_DSRPTR41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum4           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc4            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR41;

/* Define the union U_VLCST_DSRPTR50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len5              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR50;

/* Define the union U_VLCST_DSRPTR51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum5           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR51;

/* Define the union U_VLCST_DSRPTR60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len6              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR60;

/* Define the union U_VLCST_DSRPTR61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum6           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc6            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR61;

/* Define the union U_VLCST_DSRPTR70 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len7              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR70;

/* Define the union U_VLCST_DSRPTR71 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum7           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR71;

/* Define the union U_VLCST_DSRPTR80 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len8              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR80;

/* Define the union U_VLCST_DSRPTR81 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum8           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc8            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR81;

/* Define the union U_VLCST_DSRPTR90 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len9              : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR90;

/* Define the union U_VLCST_DSRPTR91 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum9           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc9            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR91;

/* Define the union U_VLCST_DSRPTR100 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len10             : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR100;

/* Define the union U_VLCST_DSRPTR101 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum10          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc10           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR101;

/* Define the union U_VLCST_DSRPTR110 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len11             : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR110;

/* Define the union U_VLCST_DSRPTR111 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum11          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc11           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR111;

/* Define the union U_VLCST_DSRPTR120 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len12             : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR120;

/* Define the union U_VLCST_DSRPTR121 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum12          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc12           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR121;

/* Define the union U_VLCST_DSRPTR130 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len13             : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR130;

/* Define the union U_VLCST_DSRPTR131 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum13          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc13           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR131;

/* Define the union U_VLCST_DSRPTR140 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len14             : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR140;

/* Define the union U_VLCST_DSRPTR141 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum14          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc14           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR141;

/* Define the union U_VLCST_DSRPTR150 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slc_len15             : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR150;

/* Define the union U_VLCST_DSRPTR151 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    invalidnum15          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 24  ; /* [30..7]  */
        unsigned int    islastslc15           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLCST_DSRPTR151;

/*--------------vlcst      end  0x20622c00--------------------*/

/* vlcst 寄存器结构体   0x20622c00  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[4];
    volatile U_VLCST_PTBITS_EN      VLCST_PTBITS_EN;
    volatile unsigned int           VLCST_PTBITS;
    volatile U_VLCST_PARAMETER      VLCST_PARAMETER;
    volatile unsigned int           RESERVED1[25];
    volatile unsigned int           VLCST_SLC_LEN_CNT;
    volatile U_VLCST_DSRPTR00       VLCST_DSRPTR00;
    volatile U_VLCST_DSRPTR01       VLCST_DSRPTR01;
    volatile U_VLCST_DSRPTR10       VLCST_DSRPTR10;
    volatile U_VLCST_DSRPTR11       VLCST_DSRPTR11;
    volatile U_VLCST_DSRPTR20       VLCST_DSRPTR20;
    volatile U_VLCST_DSRPTR21       VLCST_DSRPTR21;
    volatile U_VLCST_DSRPTR30       VLCST_DSRPTR30;
    volatile U_VLCST_DSRPTR31       VLCST_DSRPTR31;
    volatile U_VLCST_DSRPTR40       VLCST_DSRPTR40;
    volatile U_VLCST_DSRPTR41       VLCST_DSRPTR41;
    volatile U_VLCST_DSRPTR50       VLCST_DSRPTR50;
    volatile U_VLCST_DSRPTR51       VLCST_DSRPTR51;
    volatile U_VLCST_DSRPTR60       VLCST_DSRPTR60;
    volatile U_VLCST_DSRPTR61       VLCST_DSRPTR61;
    volatile U_VLCST_DSRPTR70       VLCST_DSRPTR70;
    volatile U_VLCST_DSRPTR71       VLCST_DSRPTR71;
    volatile U_VLCST_DSRPTR80       VLCST_DSRPTR80;
    volatile U_VLCST_DSRPTR81       VLCST_DSRPTR81;
    volatile U_VLCST_DSRPTR90       VLCST_DSRPTR90;
    volatile U_VLCST_DSRPTR91       VLCST_DSRPTR91;
    volatile U_VLCST_DSRPTR100      VLCST_DSRPTR100;
    volatile U_VLCST_DSRPTR101      VLCST_DSRPTR101;
    volatile U_VLCST_DSRPTR110      VLCST_DSRPTR110;
    volatile U_VLCST_DSRPTR111      VLCST_DSRPTR111;
    volatile U_VLCST_DSRPTR120      VLCST_DSRPTR120;
    volatile U_VLCST_DSRPTR121      VLCST_DSRPTR121;
    volatile U_VLCST_DSRPTR130      VLCST_DSRPTR130;
    volatile U_VLCST_DSRPTR131      VLCST_DSRPTR131;
    volatile U_VLCST_DSRPTR140      VLCST_DSRPTR140;
    volatile U_VLCST_DSRPTR141      VLCST_DSRPTR141;
    volatile U_VLCST_DSRPTR150      VLCST_DSRPTR150;
    volatile U_VLCST_DSRPTR151      VLCST_DSRPTR151;
    volatile unsigned int           VLCST_DFX_0;
    volatile unsigned int           RESERVED2[4];
    volatile unsigned int           VLCST_PARA_DATA0;
    volatile unsigned int           VLCST_PARA_DATA1;
    volatile unsigned int           VLCST_PARA_DATA2;
    volatile unsigned int           VLCST_PARA_DATA3;
    volatile unsigned int           VLCST_PARA_DATA4;
    volatile unsigned int           VLCST_PARA_DATA5;
    volatile unsigned int           VLCST_PARA_DATA6;
    volatile unsigned int           VLCST_PARA_DATA7;
    volatile unsigned int           VLCST_PARA_DATA8;
    volatile unsigned int           VLCST_PARA_DATA9;
    volatile unsigned int           VLCST_PARA_DATA10;
    volatile unsigned int           VLCST_PARA_DATA11;
    volatile unsigned int           VLCST_PARA_DATA12;
    volatile unsigned int           VLCST_PARA_DATA13;
    volatile unsigned int           VLCST_PARA_DATA14;
    volatile unsigned int           VLCST_PARA_DATA15;
    volatile unsigned int           VLCST_PARA_DATA16;
    volatile unsigned int           VLCST_PARA_DATA17;
    volatile unsigned int           VLCST_PARA_DATA18;
    volatile unsigned int           VLCST_PARA_DATA19;
    volatile unsigned int           VLCST_PARA_DATA20;
    volatile unsigned int           VLCST_PARA_DATA21;
    volatile unsigned int           VLCST_PARA_DATA22;
    volatile unsigned int           VLCST_PARA_DATA23;
    volatile unsigned int           VLCST_PARA_DATA24;
    volatile unsigned int           VLCST_PARA_DATA25;
    volatile unsigned int           VLCST_PARA_DATA26;
    volatile unsigned int           VLCST_PARA_DATA27;
    volatile unsigned int           VLCST_PARA_DATA28;
    volatile unsigned int           VLCST_PARA_DATA29;
    volatile unsigned int           VLCST_PARA_DATA30;
    volatile unsigned int           VLCST_PARA_DATA31;
    volatile unsigned int           VLCST_PARA_DATA32;
    volatile unsigned int           VLCST_PARA_DATA33;
    volatile unsigned int           VLCST_PARA_DATA34;
    volatile unsigned int           VLCST_PARA_DATA35;
    volatile unsigned int           VLCST_PARA_DATA36;
    volatile unsigned int           VLCST_PARA_DATA37;
    volatile unsigned int           VLCST_PARA_DATA38;
    volatile unsigned int           VLCST_PARA_DATA39;
    volatile unsigned int           VLCST_PARA_DATA40;
    volatile unsigned int           VLCST_PARA_DATA41;
    volatile unsigned int           VLCST_PARA_DATA42;
    volatile unsigned int           VLCST_PARA_DATA43;
    volatile unsigned int           VLCST_PARA_DATA44;
    volatile unsigned int           VLCST_PARA_DATA45;
    volatile unsigned int           VLCST_PARA_DATA46;
    volatile unsigned int           VLCST_PARA_DATA47;
    volatile unsigned int           RESERVED3[10];

} S_vlcst_REGS_TYPE;







/*--------------vlc       start 0x20622e00--------------------*/ 
/* Define the union U_VLC_SLCHDRPARA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_markingbit       : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    vcpi_reorderbit       : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    vcpi_parabit          : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLC_SLCHDRPARA;

/* Define the union U_VLC_SVC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_svc_en           : 1   ; /* [0]  */
        unsigned int    vcpi_svc_strm         : 24  ; /* [24..1]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLC_SVC;

/* Define the union U_VLC_CABAC_BIT_OVER_FLOW */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_cabac_bitout_overflow : 25  ; /* [24..0]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VLC_CABAC_BIT_OVER_FLOW;

/*--------------vlc       end  0x20622e00--------------------*/  

/* vlc  寄存器结构体   0x20622e00  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0;
    volatile unsigned int           VLC_SlcHdrStrm0;
    volatile unsigned int           VLC_SlcHdrStrm1;
    volatile unsigned int           VLC_SlcHdrStrm2;
    volatile unsigned int           VLC_SlcHdrStrm3;
    volatile unsigned int           VLC_ReorderStrm0;
    volatile unsigned int           VLC_ReorderStrm1;
    volatile unsigned int           VLC_MarkingStrm0;
    volatile unsigned int           VLC_MarkingStrm1;
    volatile U_VLC_SLCHDRPARA       VLC_SLCHDRPARA;
    volatile U_VLC_SVC              VLC_SVC;
    volatile unsigned int           RESERVED1[21];
    volatile U_VLC_CABAC_BIT_OVER_FLOW VLC_CABAC_BIT_OVER_FLOW;
    volatile unsigned int           VLC_PIC_TOTAL_BITS;
    volatile unsigned int           RESERVED2[94];

} S_vlc_REGS_TYPE;







/*--------------Curpre       start 0x20623000--------------------*/
/* Define the union U_VEDU_FILTER_PARAMETER0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_filter_h0       : 4   ; /* [3..0]  */
        unsigned int    curld_filter_h1       : 4   ; /* [7..4]  */
        unsigned int    curld_filter_h2       : 4   ; /* [11..8]  */
        unsigned int    curld_filter_h3       : 4   ; /* [15..12]  */
        unsigned int    curld_filter_hrnd     : 4   ; /* [19..16]  */
        unsigned int    curld_filter_hshift   : 3   ; /* [22..20]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_FILTER_PARAMETER0;

/* Define the union U_VEDU_FILTER_PARAMETER1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_filter_v0       : 4   ; /* [3..0]  */
        unsigned int    curld_filter_v1       : 4   ; /* [7..4]  */
        unsigned int    curld_filter_v2       : 4   ; /* [11..8]  */
        unsigned int    curld_filter_v3       : 4   ; /* [15..12]  */
        unsigned int    curld_filter_vrnd     : 4   ; /* [19..16]  */
        unsigned int    curld_filter_vshift   : 3   ; /* [22..20]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_FILTER_PARAMETER1;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_00coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_01coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER0;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_02coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_03coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER1;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_10coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_11coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER2;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_12coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_13coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER3;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_20coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_21coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER4;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_22coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_23coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER5;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_30coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_31coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER6;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_32coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_33coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER7;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_00coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_01coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER8;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_02coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_03coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER9;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_10coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_11coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER10;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_12coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_13coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER11;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_20coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_21coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER12;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_22coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_23coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER13;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_30coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_31coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER14;

/* Define the union U_VEDU_CUR_SCALE_PARAMETER15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_32coef   : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_33coef   : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_PARAMETER15;

/* Define the union U_VEDU_CUR_GCFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_clip_en         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_GCFG;

/* Define the union U_VEDU_CLIP_THX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_luma_min         : 8   ; /* [7..0]  */
        unsigned int    clip_luma_max         : 8   ; /* [15..8]  */
        unsigned int    clip_chrm_min         : 8   ; /* [23..16]  */
        unsigned int    clip_chrm_max         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CLIP_THX;

/* Define the union U_VEDU_RGB_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_coeff_gy         : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    vcpi_coeff_ry         : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF0;

/* Define the union U_VEDU_RGB_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_coeff_rcb        : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    vcpi_coeff_by         : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF1;

/* Define the union U_VEDU_RGB_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_coeff_bcb        : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    vcpi_coeff_gcb        : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF2;

/* Define the union U_VEDU_RGB_COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_coeff_gcr        : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    vcpi_coeff_rcr        : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF3;

/* Define the union U_VEDU_RGB_COEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_coeff_bcr        : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF4;

/* Define the union U_VEDU_RGB_COEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rgb_rndy         : 16  ; /* [15..0]  */
        unsigned int    vcpi_rgb_shift        : 4   ; /* [19..16]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF5;

/* Define the union U_VEDU_RGB_COEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rgb_rndcr        : 16  ; /* [15..0]  */
        unsigned int    vcpi_rgb_rndcb        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_COEF6;

/* Define the union U_VEDU_RGB_CLIP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_rgb_clpmin       : 8   ; /* [7..0]  */
        unsigned int    vcpi_rgb_clpmax       : 8   ; /* [15..8]  */
        unsigned int    vcpi_rgb_clip_en      : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_RGB_CLIP;

/* Define the union U_VEDU_WIDE_NARROW_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_wide_narrow_en : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_WIDE_NARROW_EN;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_00coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_01coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER0;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_02coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_03coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER1;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_10coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_11coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER2;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_12coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_13coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER3;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_20coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_21coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER4;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_22coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_23coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER5;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_30coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_31coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER6;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_y_filt_col_32coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_y_filt_col_33coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER7;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_00coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_01coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER8;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_02coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_03coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER9;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_10coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_11coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER10;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_12coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_13coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER11;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_20coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_21coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER12;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_22coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_23coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER13;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_30coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_31coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER14;

/* Define the union U_VEDU_CUR_SCALE_COL_PARAMETER15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    curld_c_filt_col_32coef : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    curld_c_filt_col_33coef : 14  ; /* [29..16]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VEDU_CUR_SCALE_COL_PARAMETER15;





/*--------------Curpre       end  0x20623000--------------------*/ 

/* Curpre  寄存器结构体   0x20623000  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_VEDU_FILTER_PARAMETER0 VEDU_FILTER_PARAMETER0;
    volatile U_VEDU_FILTER_PARAMETER1 VEDU_FILTER_PARAMETER1;
    volatile U_VEDU_CUR_SCALE_PARAMETER0 VEDU_CUR_SCALE_PARAMETER0;
    volatile U_VEDU_CUR_SCALE_PARAMETER1 VEDU_CUR_SCALE_PARAMETER1;
    volatile U_VEDU_CUR_SCALE_PARAMETER2 VEDU_CUR_SCALE_PARAMETER2;
    volatile U_VEDU_CUR_SCALE_PARAMETER3 VEDU_CUR_SCALE_PARAMETER3;
    volatile U_VEDU_CUR_SCALE_PARAMETER4 VEDU_CUR_SCALE_PARAMETER4;
    volatile U_VEDU_CUR_SCALE_PARAMETER5 VEDU_CUR_SCALE_PARAMETER5;
    volatile U_VEDU_CUR_SCALE_PARAMETER6 VEDU_CUR_SCALE_PARAMETER6;
    volatile U_VEDU_CUR_SCALE_PARAMETER7 VEDU_CUR_SCALE_PARAMETER7;
    volatile U_VEDU_CUR_SCALE_PARAMETER8 VEDU_CUR_SCALE_PARAMETER8;
    volatile U_VEDU_CUR_SCALE_PARAMETER9 VEDU_CUR_SCALE_PARAMETER9;
    volatile U_VEDU_CUR_SCALE_PARAMETER10 VEDU_CUR_SCALE_PARAMETER10;
    volatile U_VEDU_CUR_SCALE_PARAMETER11 VEDU_CUR_SCALE_PARAMETER11;
    volatile U_VEDU_CUR_SCALE_PARAMETER12 VEDU_CUR_SCALE_PARAMETER12;
    volatile U_VEDU_CUR_SCALE_PARAMETER13 VEDU_CUR_SCALE_PARAMETER13;
    volatile U_VEDU_CUR_SCALE_PARAMETER14 VEDU_CUR_SCALE_PARAMETER14;
    volatile U_VEDU_CUR_SCALE_PARAMETER15 VEDU_CUR_SCALE_PARAMETER15;
    volatile U_VEDU_CUR_GCFG        VEDU_CUR_GCFG;
    volatile U_VEDU_CLIP_THX        VEDU_CLIP_THX;
    volatile U_VEDU_RGB_COEF0       VEDU_RGB_COEF0;
    volatile U_VEDU_RGB_COEF1       VEDU_RGB_COEF1;
    volatile U_VEDU_RGB_COEF2       VEDU_RGB_COEF2;
    volatile U_VEDU_RGB_COEF3       VEDU_RGB_COEF3;
    volatile U_VEDU_RGB_COEF4       VEDU_RGB_COEF4;
    volatile U_VEDU_RGB_COEF5       VEDU_RGB_COEF5;
    volatile U_VEDU_RGB_COEF6       VEDU_RGB_COEF6;
    volatile U_VEDU_RGB_CLIP        VEDU_RGB_CLIP;
    volatile U_VEDU_WIDE_NARROW_EN  VEDU_WIDE_NARROW_EN;
    volatile unsigned int           RESERVED0[3];
    volatile unsigned int           CURPRE_DFX_0;
    volatile unsigned int           RESERVED1[5];
    volatile unsigned int           CURPRE_DFX_1;
    volatile unsigned int           RESERVED2[25];
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER0 VEDU_CUR_SCALE_COL_PARAMETER0;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER1 VEDU_CUR_SCALE_COL_PARAMETER1;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER2 VEDU_CUR_SCALE_COL_PARAMETER2;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER3 VEDU_CUR_SCALE_COL_PARAMETER3;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER4 VEDU_CUR_SCALE_COL_PARAMETER4;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER5 VEDU_CUR_SCALE_COL_PARAMETER5;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER6 VEDU_CUR_SCALE_COL_PARAMETER6;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER7 VEDU_CUR_SCALE_COL_PARAMETER7;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER8 VEDU_CUR_SCALE_COL_PARAMETER8;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER9 VEDU_CUR_SCALE_COL_PARAMETER9;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER10 VEDU_CUR_SCALE_COL_PARAMETER10;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER11 VEDU_CUR_SCALE_COL_PARAMETER11;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER12 VEDU_CUR_SCALE_COL_PARAMETER12;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER13 VEDU_CUR_SCALE_COL_PARAMETER13;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER14 VEDU_CUR_SCALE_COL_PARAMETER14;
    volatile U_VEDU_CUR_SCALE_COL_PARAMETER15 VEDU_CUR_SCALE_COL_PARAMETER15;
    volatile unsigned int           RESERVED3[48];

} S_curpre_REGS_TYPE;



/*--------------Imeld       start 0x20623200--------------------*/ 
/*--------------Imeld       end  0x20623200--------------------*/ 

/* Imeld  寄存器结构体   0x20623200  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED0[128];

} S_imeld_REGS_TYPE;




/*--------------Emar       start 0x20623400--------------------*/ 
/* Define the union U_EMAR_WAIT_TIM_OUT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_wtmax            : 10  ; /* [9..0]  */
        unsigned int    vcpi_rtmax            : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_WAIT_TIM_OUT;

/* Define the union U_EMAR_RCH_RPT_TH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ch00_rrmax       : 5   ; /* [4..0]  */
        unsigned int    vcpi_ch01_rrmax       : 5   ; /* [9..5]  */
        unsigned int    vcpi_ch02_rrmax       : 5   ; /* [14..10]  */
        unsigned int    vcpi_ch03_rrmax       : 5   ; /* [19..15]  */
        unsigned int    vcpi_ch04_rrmax       : 5   ; /* [24..20]  */
        unsigned int    vcpi_ch05_rrmax       : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_RCH_RPT_TH0;

/* Define the union U_EMAR_RCH_RPT_TH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ch06_rrmax       : 5   ; /* [4..0]  */
        unsigned int    vcpi_ch07_rrmax       : 5   ; /* [9..5]  */
        unsigned int    vcpi_ch08_rrmax       : 5   ; /* [14..10]  */
        unsigned int    vcpi_ch09_rrmax       : 5   ; /* [19..15]  */
        unsigned int    vcpi_ch10_rrmax       : 5   ; /* [24..20]  */
        unsigned int    vcpi_ch11_rrmax       : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_RCH_RPT_TH1;

/* Define the union U_EMAR_RCH_RPT_TH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ch12_rrmax       : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_RCH_RPT_TH2;

/* Define the union U_EMAR_RCH_RPT_TH3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ch00_wrmax       : 5   ; /* [4..0]  */
        unsigned int    vcpi_ch01_wrmax       : 5   ; /* [9..5]  */
        unsigned int    vcpi_ch02_wrmax       : 5   ; /* [14..10]  */
        unsigned int    vcpi_ch03_wrmax       : 5   ; /* [19..15]  */
        unsigned int    vcpi_ch04_wrmax       : 5   ; /* [24..20]  */
        unsigned int    vcpi_ch05_wrmax       : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_RCH_RPT_TH3;

/* Define the union U_EMAR_RCH_RPT_TH4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ch06_wrmax       : 5   ; /* [4..0]  */
        unsigned int    vcpi_ch07_wrmax       : 5   ; /* [9..5]  */
        unsigned int    vcpi_ch08_wrmax       : 5   ; /* [14..10]  */
        unsigned int    vcpi_ch09_wrmax       : 5   ; /* [19..15]  */
        unsigned int    vcpi_ch10_wrmax       : 5   ; /* [24..20]  */
        unsigned int    vcpi_ch11_wrmax       : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_RCH_RPT_TH4;

/* Define the union U_EMAR_RCH_RPT_TH5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_ch12_wrmax       : 5   ; /* [4..0]  */
        unsigned int    vcpi_ch13_wrmax       : 5   ; /* [9..5]  */
        unsigned int    vcpi_ch14_wrmax       : 5   ; /* [14..10]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_RCH_RPT_TH5;

/* Define the union U_EMAR_STA_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cur_rcmd_st           : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    rcmd_chn_cnt          : 7   ; /* [10..4]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    save_cnt              : 2   ; /* [13..12]  */
        unsigned int    all_r_mid_info        : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_STA_0;

/* Define the union U_EMAR_STA_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    r00_arbit_cfifo_cnt   : 6   ; /* [5..0]  */
        unsigned int    r00_sp_128_rd_cnt     : 6   ; /* [11..6]  */
        unsigned int    r00_sp_bst8_rd_cnt    : 6   ; /* [17..12]  */
        unsigned int    r00_syn_cfifo_cnt     : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_STA_1;

/* Define the union U_EMAR_STA_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    r01_arbit_cfifo_cnt   : 6   ; /* [5..0]  */
        unsigned int    r01_sp_128_rd_cnt     : 6   ; /* [11..6]  */
        unsigned int    r01_sp_bst8_rd_cnt    : 6   ; /* [17..12]  */
        unsigned int    r01_syn_cfifo_cnt     : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_STA_2;

/* Define the union U_EMAR_STA_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    warbit_cfifo_cnt      : 6   ; /* [5..0]  */
        unsigned int    wsp_128_rd_cnt        : 6   ; /* [11..6]  */
        unsigned int    wsp_bst8_rd_cnt       : 6   ; /* [17..12]  */
        unsigned int    wsyn_cfifo_cnt        : 4   ; /* [21..18]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_EMAR_STA_3;

/*--------------Emar       end  0x20623400--------------------*/ 

/* Emar  寄存器结构体   0x20623400  */
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_EMAR_WAIT_TIM_OUT    EMAR_WAIT_TIM_OUT;
    volatile U_EMAR_RCH_RPT_TH0     EMAR_RCH_RPT_TH0;
    volatile U_EMAR_RCH_RPT_TH1     EMAR_RCH_RPT_TH1;
    volatile U_EMAR_RCH_RPT_TH2     EMAR_RCH_RPT_TH2;
    volatile U_EMAR_RCH_RPT_TH3     EMAR_RCH_RPT_TH3;
    volatile U_EMAR_RCH_RPT_TH4     EMAR_RCH_RPT_TH4;
    volatile U_EMAR_RCH_RPT_TH5     EMAR_RCH_RPT_TH5;
    volatile unsigned int           EMAR_RCH_BST1_NUM;
    volatile unsigned int           EMAR_RCH_BST2_NUM;
    volatile unsigned int           EMAR_RCH_BST3_NUM;
    volatile unsigned int           EMAR_RCH_BST4_NUM;
    volatile unsigned int           EMAR_RCH_BST5_NUM;
    volatile unsigned int           EMAR_RCH_BST6_NUM;
    volatile unsigned int           EMAR_RCH_BST7_NUM;
    volatile unsigned int           EMAR_RCH_BST8_NUM;
    volatile unsigned int           EMAR_WCH_BST1_NUM;
    volatile unsigned int           EMAR_WCH_BST2_NUM;
    volatile unsigned int           EMAR_WCH_BST3_NUM;
    volatile unsigned int           EMAR_WCH_BST4_NUM;
    volatile unsigned int           EMAR_WCH_BST5_NUM;
    volatile unsigned int           EMAR_WCH_BST6_NUM;
    volatile unsigned int           EMAR_WCH_BST7_NUM;
    volatile unsigned int           EMAR_WCH_BST8_NUM;
    volatile U_EMAR_STA_0           EMAR_STA_0;
    volatile U_EMAR_STA_1           EMAR_STA_1;
    volatile U_EMAR_STA_2           EMAR_STA_2;
    volatile U_EMAR_STA_3           EMAR_STA_3;
    volatile unsigned int           RESERVED1[101];

} S_emar_REGS_TYPE;







/*--------------COMN0    start 0x20623600--------------------*/  
/* Define the union U_COMN0_SMMU_SCR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    glb_bypass           : 1   ; /* [0]  */
        unsigned int    rqos_en                : 1   ; /* [1]  */
        unsigned int    wqos_en               : 1   ; /* [2]  */
        unsigned int    int_en                   : 1   ; /* [3]  */
        unsigned int    cache_l1_en          : 1   ; /* [4]  */
        unsigned int    cache_l2_en          : 1   ; /* [5]  */
        unsigned int    rqos                      : 4   ; /* [9..6]  */
        unsigned int    wqos                     : 4   ; /* [13..10]  */
        unsigned int    reserved_0            : 1   ; /* [14]  */
        unsigned int    smr_rd_shadow     : 1   ; /* [15]  */
        unsigned int    ptw_pf                  : 4   ; /* [19..16]  */
        unsigned int    ptw_mid                : 8   ; /* [27..20]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SCR;

/* Define the union U_COMN0_SMMU_MEMCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mem_ctrl_wr           : 16  ; /* [15..0]  */
        unsigned int    mem_ctrl_rd           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_MEMCTRL;

/* Define the union U_COMN0_SMMU_LP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    auto_clk_gt_en        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    smmu_idle             : 1   ; /* [2]  */
        unsigned int    reserved_1            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_LP_CTRL;

/* Define the union U_COMN0_SMMU_PRESS_REMAP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    remap_sel0            : 2   ; /* [1..0]  */
        unsigned int    remap_sel1            : 2   ; /* [3..2]  */
        unsigned int    remap_sel2            : 2   ; /* [5..4]  */
        unsigned int    remap_sel3            : 2   ; /* [7..6]  */
        unsigned int    remap_sel4            : 2   ; /* [9..8]  */
        unsigned int    remap_sel5            : 2   ; /* [11..10]  */
        unsigned int    remap_sel6            : 2   ; /* [13..12]  */
        unsigned int    remap_sel7            : 2   ; /* [15..14]  */
        unsigned int    remap_sel8            : 2   ; /* [17..16]  */
        unsigned int    remap_sel9            : 2   ; /* [19..18]  */
        unsigned int    remap_sel10           : 2   ; /* [21..20]  */
        unsigned int    remap_sel11           : 2   ; /* [23..22]  */
        unsigned int    remap_sel12           : 2   ; /* [25..24]  */
        unsigned int    remap_sel13           : 2   ; /* [27..26]  */
        unsigned int    remap_sel14           : 2   ; /* [29..28]  */
        unsigned int    remap_sel15           : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_PRESS_REMAP;

/* Define the union U_COMN0_SMMU_INTMASK_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_permis_msk      : 1   ; /* [0]  */
        unsigned int    intns_ext_msk         : 1   ; /* [1]  */
        unsigned int    intns_tlbmiss_msk     : 1   ; /* [2]  */
        unsigned int    intns_ptw_trans_msk   : 1   ; /* [3]  */
        unsigned int    intns_ptw_invalid_msk : 1   ; /* [4]  */
        unsigned int    intns_ptw_ns_msk      : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_INTMASK_NS;

/* Define the union U_COMN0_SMMU_INTRAW_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_permis_raw      : 1   ; /* [0]  */
        unsigned int    intns_ext_raw         : 1   ; /* [1]  */
        unsigned int    intns_tlbmiss_raw     : 1   ; /* [2]  */
        unsigned int    intns_ptw_trans_raw   : 1   ; /* [3]  */
        unsigned int    intns_ptw_invalid_raw : 1   ; /* [4]  */
        unsigned int    intns_ptw_ns_raw      : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_INTRAW_NS;

/* Define the union U_COMN0_SMMU_INTSTAT_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_permis_stat     : 1   ; /* [0]  */
        unsigned int    intns_ext_stat        : 1   ; /* [1]  */
        unsigned int    intns_tlbmiss_stat    : 1   ; /* [2]  */
        unsigned int    intns_ptw_trans_stat  : 1   ; /* [3]  */
        unsigned int    intns_ptw_invalid_stat : 1   ; /* [4]  */
        unsigned int    intns_ptw_ns_stat     : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_INTSTAT_NS;

/* Define the union U_COMN0_SMMU_INTCLR_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_permis_clr      : 1   ; /* [0]  */
        unsigned int    intns_ext_clr         : 1   ; /* [1]  */
        unsigned int    intns_tlbmiss_clr     : 1   ; /* [2]  */
        unsigned int    intns_ptw_trans_clr   : 1   ; /* [3]  */
        unsigned int    intns_ptw_invalid_clr : 1   ; /* [4]  */
        unsigned int    intns_ptw_ns_clr      : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_INTCLR_NS;

/* Define the union U_COMN0_SMMU_SMR0_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr0_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr0_invld_en         : 1   ; /* [4]  */
        unsigned int    smr0_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr0_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR0_NS;

/* Define the union U_COMN0_SMMU_SMR1_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr1_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr1_invld_en         : 1   ; /* [4]  */
        unsigned int    smr1_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr1_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR1_NS;

/* Define the union U_COMN0_SMMU_SMR2_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr2_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr2_invld_en         : 1   ; /* [4]  */
        unsigned int    smr2_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr2_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR2_NS;

/* Define the union U_COMN0_SMMU_SMR3_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr3_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr3_invld_en         : 1   ; /* [4]  */
        unsigned int    smr3_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr3_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR3_NS;

/* Define the union U_COMN0_SMMU_SMR4_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr4_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr4_invld_en         : 1   ; /* [4]  */
        unsigned int    smr4_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr4_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR4_NS;

/* Define the union U_COMN0_SMMU_SMR5_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr5_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr5_invld_en         : 1   ; /* [4]  */
        unsigned int    smr5_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr5_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR5_NS;

/* Define the union U_COMN0_SMMU_SMR6_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr6_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr6_invld_en         : 1   ; /* [4]  */
        unsigned int    smr6_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr6_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR6_NS;

/* Define the union U_COMN0_SMMU_SMR7_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr7_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr7_invld_en         : 1   ; /* [4]  */
        unsigned int    smr7_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr7_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR7_NS;

/* Define the union U_COMN0_SMMU_SMR8_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr8_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr8_invld_en         : 1   ; /* [4]  */
        unsigned int    smr8_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr8_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR8_NS;

/* Define the union U_COMN0_SMMU_SMR9_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr9_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr9_invld_en         : 1   ; /* [4]  */
        unsigned int    smr9_ptw_qos          : 7   ; /* [11..5]  */
        unsigned int    smr9_offset_addr      : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR9_NS;

/* Define the union U_COMN0_SMMU_SMR10_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr10_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr10_invld_en        : 1   ; /* [4]  */
        unsigned int    smr10_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr10_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR10_NS;

/* Define the union U_COMN0_SMMU_SMR11_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr11_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr11_invld_en        : 1   ; /* [4]  */
        unsigned int    smr11_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr11_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR11_NS;

/* Define the union U_COMN0_SMMU_SMR12_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr12_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr12_invld_en        : 1   ; /* [4]  */
        unsigned int    smr12_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr12_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR12_NS;

/* Define the union U_COMN0_SMMU_SMR13_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr13_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr13_invld_en        : 1   ; /* [4]  */
        unsigned int    smr13_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr13_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR13_NS;

/* Define the union U_COMN0_SMMU_SMR14_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr14_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr14_invld_en        : 1   ; /* [4]  */
        unsigned int    smr14_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr14_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR14_NS;

/* Define the union U_COMN0_SMMU_SMR15_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr15_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr15_invld_en        : 1   ; /* [4]  */
        unsigned int    smr15_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr15_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR15_NS;

/* Define the union U_COMN0_SMMU_SMR16_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr16_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr16_invld_en        : 1   ; /* [4]  */
        unsigned int    smr16_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr16_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR16_NS;

/* Define the union U_COMN0_SMMU_SMR17_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr17_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr17_invld_en        : 1   ; /* [4]  */
        unsigned int    smr17_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr17_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR17_NS;

/* Define the union U_COMN0_SMMU_SMR18_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr18_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr18_invld_en        : 1   ; /* [4]  */
        unsigned int    smr18_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr18_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR18_NS;

/* Define the union U_COMN0_SMMU_SMR19_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr19_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr19_invld_en        : 1   ; /* [4]  */
        unsigned int    smr19_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr19_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR19_NS;

/* Define the union U_COMN0_SMMU_SMR20_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr20_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr20_invld_en        : 1   ; /* [4]  */
        unsigned int    smr20_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr20_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR20_NS;

/* Define the union U_COMN0_SMMU_SMR21_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr21_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr21_invld_en        : 1   ; /* [4]  */
        unsigned int    smr21_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr21_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR21_NS;

/* Define the union U_COMN0_SMMU_SMR22_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr22_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr22_invld_en        : 1   ; /* [4]  */
        unsigned int    smr22_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr22_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR22_NS;

/* Define the union U_COMN0_SMMU_SMR23_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr23_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr23_invld_en        : 1   ; /* [4]  */
        unsigned int    smr23_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr23_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR23_NS;

/* Define the union U_COMN0_SMMU_SMR24_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr24_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr24_invld_en        : 1   ; /* [4]  */
        unsigned int    smr24_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr24_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR24_NS;

/* Define the union U_COMN0_SMMU_SMR25_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr25_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr25_invld_en        : 1   ; /* [4]  */
        unsigned int    smr25_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr25_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR25_NS;

/* Define the union U_COMN0_SMMU_SMR26_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr26_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr26_invld_en        : 1   ; /* [4]  */
        unsigned int    smr26_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr26_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR26_NS;

/* Define the union U_COMN0_SMMU_SMR27_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr27_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr27_invld_en        : 1   ; /* [4]  */
        unsigned int    smr27_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr27_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR27_NS;

/* Define the union U_COMN0_SMMU_SMR28_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr28_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr28_invld_en        : 1   ; /* [4]  */
        unsigned int    smr28_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr28_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR28_NS;

/* Define the union U_COMN0_SMMU_SMR29_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr29_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr29_invld_en        : 1   ; /* [4]  */
        unsigned int    smr29_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr29_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR29_NS;

/* Define the union U_COMN0_SMMU_SMR30_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr30_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr30_invld_en        : 1   ; /* [4]  */
        unsigned int    smr30_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr30_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR30_NS;

/* Define the union U_COMN0_SMMU_SMR31_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr31_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr31_invld_en        : 1   ; /* [4]  */
        unsigned int    smr31_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr31_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR31_NS;

/* Define the union U_COMN0_SMMU_SMR32_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr32_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr32_invld_en        : 1   ; /* [4]  */
        unsigned int    smr32_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr32_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR32_NS;

/* Define the union U_COMN0_SMMU_SMR33_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr33_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr33_invld_en        : 1   ; /* [4]  */
        unsigned int    smr33_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr33_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR33_NS;

/* Define the union U_COMN0_SMMU_SMR34_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr34_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr34_invld_en        : 1   ; /* [4]  */
        unsigned int    smr34_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr34_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR34_NS;

/* Define the union U_COMN0_SMMU_SMR35_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr35_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr35_invld_en        : 1   ; /* [4]  */
        unsigned int    smr35_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr35_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR35_NS;

/* Define the union U_COMN0_SMMU_SMR36_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr36_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr36_invld_en        : 1   ; /* [4]  */
        unsigned int    smr36_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr36_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR36_NS;

/* Define the union U_COMN0_SMMU_SMR37_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr37_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr37_invld_en        : 1   ; /* [4]  */
        unsigned int    smr37_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr37_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR37_NS;

/* Define the union U_COMN0_SMMU_SMR38_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr38_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr38_invld_en        : 1   ; /* [4]  */
        unsigned int    smr38_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr38_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR38_NS;

/* Define the union U_COMN0_SMMU_SMR39_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr39_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr39_invld_en        : 1   ; /* [4]  */
        unsigned int    smr39_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr39_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR39_NS;

/* Define the union U_COMN0_SMMU_SMR40_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr40_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr40_invld_en        : 1   ; /* [4]  */
        unsigned int    smr40_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr40_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR40_NS;

/* Define the union U_COMN0_SMMU_SMR41_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr41_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr41_invld_en        : 1   ; /* [4]  */
        unsigned int    smr41_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr41_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR41_NS;

/* Define the union U_COMN0_SMMU_SMR42_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr42_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr42_invld_en        : 1   ; /* [4]  */
        unsigned int    smr42_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr42_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR42_NS;

/* Define the union U_COMN0_SMMU_SMR43_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr43_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr43_invld_en        : 1   ; /* [4]  */
        unsigned int    smr43_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr43_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR43_NS;

/* Define the union U_COMN0_SMMU_SMR44_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr44_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr44_invld_en        : 1   ; /* [4]  */
        unsigned int    smr44_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr44_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR44_NS;

/* Define the union U_COMN0_SMMU_SMR45_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr45_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr45_invld_en        : 1   ; /* [4]  */
        unsigned int    smr45_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr45_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR45_NS;

/* Define the union U_COMN0_SMMU_SMR46_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr46_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr46_invld_en        : 1   ; /* [4]  */
        unsigned int    smr46_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr46_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR46_NS;

/* Define the union U_COMN0_SMMU_SMR47_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr47_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr47_invld_en        : 1   ; /* [4]  */
        unsigned int    smr47_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr47_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR47_NS;

/* Define the union U_COMN0_SMMU_SMR48_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr48_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr48_invld_en        : 1   ; /* [4]  */
        unsigned int    smr48_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr48_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR48_NS;

/* Define the union U_COMN0_SMMU_SMR49_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr49_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr49_invld_en        : 1   ; /* [4]  */
        unsigned int    smr49_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr49_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR49_NS;

/* Define the union U_COMN0_SMMU_SMR50_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr50_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr50_invld_en        : 1   ; /* [4]  */
        unsigned int    smr50_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr50_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR50_NS;

/* Define the union U_COMN0_SMMU_SMR51_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr51_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr51_invld_en        : 1   ; /* [4]  */
        unsigned int    smr51_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr51_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR51_NS;

/* Define the union U_COMN0_SMMU_SMR52_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr52_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr52_invld_en        : 1   ; /* [4]  */
        unsigned int    smr52_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr52_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR52_NS;

/* Define the union U_COMN0_SMMU_SMR53_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr53_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr53_invld_en        : 1   ; /* [4]  */
        unsigned int    smr53_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr53_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR53_NS;

/* Define the union U_COMN0_SMMU_SMR54_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr54_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr54_invld_en        : 1   ; /* [4]  */
        unsigned int    smr54_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr54_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR54_NS;

/* Define the union U_COMN0_SMMU_SMR55_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr55_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr55_invld_en        : 1   ; /* [4]  */
        unsigned int    smr55_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr55_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR55_NS;

/* Define the union U_COMN0_SMMU_SMR56_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr56_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr56_invld_en        : 1   ; /* [4]  */
        unsigned int    smr56_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr56_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR56_NS;

/* Define the union U_COMN0_SMMU_SMR57_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr57_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr57_invld_en        : 1   ; /* [4]  */
        unsigned int    smr57_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr57_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR57_NS;

/* Define the union U_COMN0_SMMU_SMR58_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr58_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr58_invld_en        : 1   ; /* [4]  */
        unsigned int    smr58_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr58_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR58_NS;

/* Define the union U_COMN0_SMMU_SMR59_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr59_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr59_invld_en        : 1   ; /* [4]  */
        unsigned int    smr59_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr59_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR59_NS;

/* Define the union U_COMN0_SMMU_SMR60_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr60_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr60_invld_en        : 1   ; /* [4]  */
        unsigned int    smr60_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr60_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR60_NS;

/* Define the union U_COMN0_SMMU_SMR61_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr61_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr61_invld_en        : 1   ; /* [4]  */
        unsigned int    smr61_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr61_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR61_NS;

/* Define the union U_COMN0_SMMU_SMR62_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr62_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr62_invld_en        : 1   ; /* [4]  */
        unsigned int    smr62_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr62_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR62_NS;

/* Define the union U_COMN0_SMMU_SMR63_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr63_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr63_invld_en        : 1   ; /* [4]  */
        unsigned int    smr63_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr63_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR63_NS;

/* Define the union U_COMN0_SMMU_SMR64_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr64_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr64_invld_en        : 1   ; /* [4]  */
        unsigned int    smr64_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr64_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR64_NS;

/* Define the union U_COMN0_SMMU_SMR65_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr65_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr65_invld_en        : 1   ; /* [4]  */
        unsigned int    smr65_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr65_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR65_NS;

/* Define the union U_COMN0_SMMU_SMR66_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr66_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr66_invld_en        : 1   ; /* [4]  */
        unsigned int    smr66_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr66_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR66_NS;

/* Define the union U_COMN0_SMMU_SMR67_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr67_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr67_invld_en        : 1   ; /* [4]  */
        unsigned int    smr67_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr67_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR67_NS;

/* Define the union U_COMN0_SMMU_SMR68_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr68_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr68_invld_en        : 1   ; /* [4]  */
        unsigned int    smr68_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr68_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR68_NS;

/* Define the union U_COMN0_SMMU_SMR69_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr69_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr69_invld_en        : 1   ; /* [4]  */
        unsigned int    smr69_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr69_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR69_NS;

/* Define the union U_COMN0_SMMU_SMR70_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr70_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr70_invld_en        : 1   ; /* [4]  */
        unsigned int    smr70_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr70_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR70_NS;

/* Define the union U_COMN0_SMMU_SMR71_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr71_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr71_invld_en        : 1   ; /* [4]  */
        unsigned int    smr71_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr71_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR71_NS;

/* Define the union U_COMN0_SMMU_SMR72_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr72_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr72_invld_en        : 1   ; /* [4]  */
        unsigned int    smr72_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr72_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR72_NS;

/* Define the union U_COMN0_SMMU_SMR73_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr73_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr73_invld_en        : 1   ; /* [4]  */
        unsigned int    smr73_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr73_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR73_NS;

/* Define the union U_COMN0_SMMU_SMR74_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr74_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr74_invld_en        : 1   ; /* [4]  */
        unsigned int    smr74_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr74_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR74_NS;

/* Define the union U_COMN0_SMMU_SMR75_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr75_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr75_invld_en        : 1   ; /* [4]  */
        unsigned int    smr75_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr75_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR75_NS;

/* Define the union U_COMN0_SMMU_SMR76_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr76_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr76_invld_en        : 1   ; /* [4]  */
        unsigned int    smr76_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr76_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR76_NS;

/* Define the union U_COMN0_SMMU_SMR77_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr77_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr77_invld_en        : 1   ; /* [4]  */
        unsigned int    smr77_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr77_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR77_NS;

/* Define the union U_COMN0_SMMU_SMR78_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr78_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr78_invld_en        : 1   ; /* [4]  */
        unsigned int    smr78_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr78_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR78_NS;

/* Define the union U_COMN0_SMMU_SMR79_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr79_bypass          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    smr79_invld_en        : 1   ; /* [4]  */
        unsigned int    smr79_ptw_qos         : 7   ; /* [11..5]  */
        unsigned int    smr79_offset_addr     : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_SMR79_NS;

/* Define the union U_COMN0_SMMU_RLD_EN2_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr_rld_en2           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN0_SMMU_RLD_EN2_NS;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_COMN0_SMMU_SCR       COMN0_SMMU_SCR;
    volatile U_COMN0_SMMU_MEMCTRL   COMN0_SMMU_MEMCTRL;
    volatile U_COMN0_SMMU_LP_CTRL   COMN0_SMMU_LP_CTRL;
    volatile U_COMN0_SMMU_PRESS_REMAP COMN0_SMMU_PRESS_REMAP;
    volatile U_COMN0_SMMU_INTMASK_NS COMN0_SMMU_INTMASK_NS;
    volatile U_COMN0_SMMU_INTRAW_NS COMN0_SMMU_INTRAW_NS;
    volatile U_COMN0_SMMU_INTSTAT_NS COMN0_SMMU_INTSTAT_NS;
    volatile U_COMN0_SMMU_INTCLR_NS COMN0_SMMU_INTCLR_NS;
    volatile U_COMN0_SMMU_SMR0_NS   COMN0_SMMU_SMR0_NS;
    volatile U_COMN0_SMMU_SMR1_NS   COMN0_SMMU_SMR1_NS;
    volatile U_COMN0_SMMU_SMR2_NS   COMN0_SMMU_SMR2_NS;
    volatile U_COMN0_SMMU_SMR3_NS   COMN0_SMMU_SMR3_NS;
    volatile U_COMN0_SMMU_SMR4_NS   COMN0_SMMU_SMR4_NS;
    volatile U_COMN0_SMMU_SMR5_NS   COMN0_SMMU_SMR5_NS;
    volatile U_COMN0_SMMU_SMR6_NS   COMN0_SMMU_SMR6_NS;
    volatile U_COMN0_SMMU_SMR7_NS   COMN0_SMMU_SMR7_NS;
    volatile U_COMN0_SMMU_SMR8_NS   COMN0_SMMU_SMR8_NS;
    volatile U_COMN0_SMMU_SMR9_NS   COMN0_SMMU_SMR9_NS;
    volatile U_COMN0_SMMU_SMR10_NS  COMN0_SMMU_SMR10_NS;
    volatile U_COMN0_SMMU_SMR11_NS  COMN0_SMMU_SMR11_NS;
    volatile U_COMN0_SMMU_SMR12_NS  COMN0_SMMU_SMR12_NS;
    volatile U_COMN0_SMMU_SMR13_NS  COMN0_SMMU_SMR13_NS;
    volatile U_COMN0_SMMU_SMR14_NS  COMN0_SMMU_SMR14_NS;
    volatile U_COMN0_SMMU_SMR15_NS  COMN0_SMMU_SMR15_NS;
    volatile U_COMN0_SMMU_SMR16_NS  COMN0_SMMU_SMR16_NS;
    volatile U_COMN0_SMMU_SMR17_NS  COMN0_SMMU_SMR17_NS;
    volatile U_COMN0_SMMU_SMR18_NS  COMN0_SMMU_SMR18_NS;
    volatile U_COMN0_SMMU_SMR19_NS  COMN0_SMMU_SMR19_NS;
    volatile U_COMN0_SMMU_SMR20_NS  COMN0_SMMU_SMR20_NS;
    volatile U_COMN0_SMMU_SMR21_NS  COMN0_SMMU_SMR21_NS;
    volatile U_COMN0_SMMU_SMR22_NS  COMN0_SMMU_SMR22_NS;
    volatile U_COMN0_SMMU_SMR23_NS  COMN0_SMMU_SMR23_NS;
    volatile U_COMN0_SMMU_SMR24_NS  COMN0_SMMU_SMR24_NS;
    volatile U_COMN0_SMMU_SMR25_NS  COMN0_SMMU_SMR25_NS;
    volatile U_COMN0_SMMU_SMR26_NS  COMN0_SMMU_SMR26_NS;
    volatile U_COMN0_SMMU_SMR27_NS  COMN0_SMMU_SMR27_NS;
    volatile U_COMN0_SMMU_SMR28_NS  COMN0_SMMU_SMR28_NS;
    volatile U_COMN0_SMMU_SMR29_NS  COMN0_SMMU_SMR29_NS;
    volatile U_COMN0_SMMU_SMR30_NS  COMN0_SMMU_SMR30_NS;
    volatile U_COMN0_SMMU_SMR31_NS  COMN0_SMMU_SMR31_NS;
    volatile U_COMN0_SMMU_SMR32_NS  COMN0_SMMU_SMR32_NS;
    volatile U_COMN0_SMMU_SMR33_NS  COMN0_SMMU_SMR33_NS;
    volatile U_COMN0_SMMU_SMR34_NS  COMN0_SMMU_SMR34_NS;
    volatile U_COMN0_SMMU_SMR35_NS  COMN0_SMMU_SMR35_NS;
    volatile U_COMN0_SMMU_SMR36_NS  COMN0_SMMU_SMR36_NS;
    volatile U_COMN0_SMMU_SMR37_NS  COMN0_SMMU_SMR37_NS;
    volatile U_COMN0_SMMU_SMR38_NS  COMN0_SMMU_SMR38_NS;
    volatile U_COMN0_SMMU_SMR39_NS  COMN0_SMMU_SMR39_NS;
    volatile U_COMN0_SMMU_SMR40_NS  COMN0_SMMU_SMR40_NS;
    volatile U_COMN0_SMMU_SMR41_NS  COMN0_SMMU_SMR41_NS;
    volatile U_COMN0_SMMU_SMR42_NS  COMN0_SMMU_SMR42_NS;
    volatile U_COMN0_SMMU_SMR43_NS  COMN0_SMMU_SMR43_NS;
    volatile U_COMN0_SMMU_SMR44_NS  COMN0_SMMU_SMR44_NS;
    volatile U_COMN0_SMMU_SMR45_NS  COMN0_SMMU_SMR45_NS;
    volatile U_COMN0_SMMU_SMR46_NS  COMN0_SMMU_SMR46_NS;
    volatile U_COMN0_SMMU_SMR47_NS  COMN0_SMMU_SMR47_NS;
    volatile U_COMN0_SMMU_SMR48_NS  COMN0_SMMU_SMR48_NS;
    volatile U_COMN0_SMMU_SMR49_NS  COMN0_SMMU_SMR49_NS;
    volatile U_COMN0_SMMU_SMR50_NS  COMN0_SMMU_SMR50_NS;
    volatile U_COMN0_SMMU_SMR51_NS  COMN0_SMMU_SMR51_NS;
    volatile U_COMN0_SMMU_SMR52_NS  COMN0_SMMU_SMR52_NS;
    volatile U_COMN0_SMMU_SMR53_NS  COMN0_SMMU_SMR53_NS;
    volatile U_COMN0_SMMU_SMR54_NS  COMN0_SMMU_SMR54_NS;
    volatile U_COMN0_SMMU_SMR55_NS  COMN0_SMMU_SMR55_NS;
    volatile U_COMN0_SMMU_SMR56_NS  COMN0_SMMU_SMR56_NS;
    volatile U_COMN0_SMMU_SMR57_NS  COMN0_SMMU_SMR57_NS;
    volatile U_COMN0_SMMU_SMR58_NS  COMN0_SMMU_SMR58_NS;
    volatile U_COMN0_SMMU_SMR59_NS  COMN0_SMMU_SMR59_NS;
    volatile U_COMN0_SMMU_SMR60_NS  COMN0_SMMU_SMR60_NS;
    volatile U_COMN0_SMMU_SMR61_NS  COMN0_SMMU_SMR61_NS;
    volatile U_COMN0_SMMU_SMR62_NS  COMN0_SMMU_SMR62_NS;
    volatile U_COMN0_SMMU_SMR63_NS  COMN0_SMMU_SMR63_NS;
    volatile U_COMN0_SMMU_SMR64_NS  COMN0_SMMU_SMR64_NS;
    volatile U_COMN0_SMMU_SMR65_NS  COMN0_SMMU_SMR65_NS;
    volatile U_COMN0_SMMU_SMR66_NS  COMN0_SMMU_SMR66_NS;
    volatile U_COMN0_SMMU_SMR67_NS  COMN0_SMMU_SMR67_NS;
    volatile U_COMN0_SMMU_SMR68_NS  COMN0_SMMU_SMR68_NS;
    volatile U_COMN0_SMMU_SMR69_NS  COMN0_SMMU_SMR69_NS;
    volatile U_COMN0_SMMU_SMR70_NS  COMN0_SMMU_SMR70_NS;
    volatile U_COMN0_SMMU_SMR71_NS  COMN0_SMMU_SMR71_NS;
    volatile U_COMN0_SMMU_SMR72_NS  COMN0_SMMU_SMR72_NS;
    volatile U_COMN0_SMMU_SMR73_NS  COMN0_SMMU_SMR73_NS;
    volatile U_COMN0_SMMU_SMR74_NS  COMN0_SMMU_SMR74_NS;
    volatile U_COMN0_SMMU_SMR75_NS  COMN0_SMMU_SMR75_NS;
    volatile U_COMN0_SMMU_SMR76_NS  COMN0_SMMU_SMR76_NS;
    volatile U_COMN0_SMMU_SMR77_NS  COMN0_SMMU_SMR77_NS;
    volatile U_COMN0_SMMU_SMR78_NS  COMN0_SMMU_SMR78_NS;
    volatile U_COMN0_SMMU_SMR79_NS  COMN0_SMMU_SMR79_NS;
    volatile unsigned int           RESERVED_1[36];
    volatile unsigned int           COMN0_SMMU_RLD_EN0_NS;
    volatile unsigned int           COMN0_SMMU_RLD_EN1_NS;
    volatile U_COMN0_SMMU_RLD_EN2_NS COMN0_SMMU_RLD_EN2_NS;
    volatile unsigned int           RESERVED_2;

} S_comn0_REGS_TYPE;




/*--------------COMN1    start 0x20623800--------------------*/ 
/* Define the union U_COMN1_SMMU_CB_SCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cb_bypass             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_CB_SCTRL;

/* Define the union U_COMN1_SMMU_CB_TTBCR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cb_ttbcr_des          : 1   ; /* [0]  */
        unsigned int    cb_ttbcr_t0sz         : 3   ; /* [3..1]  */
        unsigned int    cb_ttbcr_n             : 3   ; /* [6..4]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    cb_ttbcr_t1sz         : 3   ; /* [18..16]  */
        unsigned int    reserved_1            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_CB_TTBCR;

/* Define the union U_COMN1_SMMU_OFFSET_ADDR_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    offset_addr_ns        : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_OFFSET_ADDR_NS;

/* Define the union U_COMN1_SMMU_SCACHEI_ALL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cache_all_invalid     : 1   ; /* [0]  */
        unsigned int    cache_all_level       : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_SCACHEI_ALL;

/* Define the union U_COMN1_SMMU_SCACHEI_L1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cache_l1_invalid      : 1   ; /* [0]  */
        unsigned int    cache_l1_security     : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_SCACHEI_L1;

/* Define the union U_COMN1_SMMU_SCACHEI_L2L3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cache_l2l3_invalid    : 1   ; /* [0]  */
        unsigned int    cache_l2l3_strmid     : 15  ; /* [15..1]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_SCACHEI_L2L3;

/* Define the union U_COMN1_SMMU_FAMA_CTRL0_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fama_sdes_msb_ns   : 7   ; /* [6..0]  */
        unsigned int    fama_chn_sel_ns      : 1   ; /* [7]  */
        unsigned int    fama_bps_msb_ns    : 6   ; /* [13..8]  */
        unsigned int    reserved_0               : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAMA_CTRL0_NS;

/* Define the union U_COMN1_SMMU_FAMA_CTRL1_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fama_ptw_msb_ns   : 7   ; /* [6..0]  */
        unsigned int    reserved_0              : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAMA_CTRL1_NS;

/* Define the union U_COMN1_SMMU_ADDR_MSB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    msb_errrd             : 7   ; /* [6..0]  */
        unsigned int    msb_errwr             : 7   ; /* [13..7]  */
        unsigned int    msb_ova               : 7   ; /* [20..14]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_ADDR_MSB;

/* Define the union U_COMN1_SMMU_FAULT_ID_TCU */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_tcu    : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_tcu     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_ID_TCU;

/* Define the union U_COMN1_SMMU_FAULT_ID_TBU0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_tbu0   : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_tbu0    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_ID_TBU0;

/* Define the union U_COMN1_SMMU_FAULT_INFO0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_tlbmiss_err_tbu0 : 2   ; /* [1..0]  */
        unsigned int    fault_permis_err_tbu0 : 2   ; /* [3..2]  */
        unsigned int    fautl_ext_err_tbu0    : 2   ; /* [5..4]  */
        unsigned int    fault_ext_err_id_tbu0 : 10  ; /* [15..6]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_INFO0;

/* Define the union U_COMN1_SMMU_FAULT_ID_TBU1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_tbu1   : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_tbu1    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_ID_TBU1;

/* Define the union U_COMN1_SMMU_FAULT_INFO1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_tlbmiss_err_tbu1 : 2   ; /* [1..0]  */
        unsigned int    fault_permis_err_tbu1 : 2   ; /* [3..2]  */
        unsigned int    fautl_ext_err_tbu1    : 2   ; /* [5..4]  */
        unsigned int    fault_ext_err_id_tbu1 : 10  ; /* [15..6]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_INFO1;

/* Define the union U_COMN1_SMMU_FAULT_ID_TBU2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_tbu2   : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_tbu2    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_ID_TBU2;

/* Define the union U_COMN1_SMMU_FAULT_INFO2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_tlbmiss_err_tbu2 : 2   ; /* [1..0]  */
        unsigned int    fault_permis_err_tbu2 : 2   ; /* [3..2]  */
        unsigned int    fautl_ext_err_tbu2    : 2   ; /* [5..4]  */
        unsigned int    fault_ext_err_id_tbu2 : 10  ; /* [15..6]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_INFO2;

/* Define the union U_COMN1_SMMU_FAULT_ID_TBU3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_tbu3   : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_tbu3    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_ID_TBU3;

/* Define the union U_COMN1_SMMU_FAULT_INFO3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_tlbmiss_err_tbu3 : 2   ; /* [1..0]  */
        unsigned int    fault_permis_err_tbu3 : 2   ; /* [3..2]  */
        unsigned int    fautl_ext_err_tbu3    : 2   ; /* [5..4]  */
        unsigned int    fault_ext_err_id_tbu3 : 10  ; /* [15..6]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_FAULT_INFO3;

/* Define the union U_COMN1_SMMU_DBGRPTR_TLB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_tlbword_pointer   : 3   ; /* [2..0]  */
        unsigned int    dbg_tlbentry_pointer  : 13  ; /* [15..3]  */
        unsigned int    reserved_0            : 14  ; /* [29..16]  */
        unsigned int    dbg_tlb_type          : 1   ; /* [30]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_DBGRPTR_TLB;

/* Define the union U_COMN1_SMMU_DBGRDATA_TLB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_tlb_rdata         : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_DBGRDATA_TLB;

/* Define the union U_COMN1_SMMU_DBGRPTR_CACHE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_cache_level       : 2   ; /* [1..0]  */
        unsigned int    dbg_cache_l1_pointer  : 2   ; /* [3..2]  */
        unsigned int    dbg_cache_l1_ns       : 1   ; /* [4]  */
        unsigned int    dbg_cache_l2_strmid   : 11  ; /* [15..5]  */
        unsigned int    reserved_0            : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_DBGRPTR_CACHE;

/* Define the union U_COMN1_SMMU_DBGRDATA0_CACHE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_cache_rdata0      : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_DBGRDATA0_CACHE;

/* Define the union U_COMN1_SMMU_DBGRDATA1_CACHE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_cache_rdata1      : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_DBGRDATA1_CACHE;

/* Define the union U_COMN1_SMMU_DBGAXI_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_axilock_en        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_DBGAXI_CTRL;

/* Define the union U_COMN1_SMMU_OPA_ADDR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    override_acquire_pa   : 22  ; /* [21..0]  */
        unsigned int    override_pa_done      : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_OPA_ADDR;

/* Define the union U_COMN1_SMMU_OVA_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    override_va_cfg       : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    override_va_type      : 1   ; /* [2]  */
        unsigned int    override_va_indexid   : 13  ; /* [15..3]  */
        unsigned int    override_va_strmid    : 12  ; /* [27..16]  */
        unsigned int    override_tbu_num      : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_OVA_CTRL;

/* Define the union U_COMN1_SMMU_OPREF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    override_pref_cfg     : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    override_pref_type    : 1   ; /* [2]  */
        unsigned int    override_pref_initial : 1   ; /* [3]  */
        unsigned int    override_pref_indexid : 12  ; /* [15..4]  */
        unsigned int    override_pref_strmid  : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN1_SMMU_OPREF_CTRL;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_COMN1_SMMU_CB_SCTRL  COMN1_SMMU_CB_SCTRL;
    volatile unsigned int           COMN1_SMMU_CB_TTBR0;
    volatile unsigned int           COMN1_SMMU_CB_TTBR1;
    volatile U_COMN1_SMMU_CB_TTBCR  COMN1_SMMU_CB_TTBCR;
    volatile U_COMN1_SMMU_OFFSET_ADDR_NS COMN1_SMMU_OFFSET_ADDR_NS;
    volatile U_COMN1_SMMU_SCACHEI_ALL COMN1_SMMU_SCACHEI_ALL;
    volatile U_COMN1_SMMU_SCACHEI_L1 COMN1_SMMU_SCACHEI_L1;
    volatile U_COMN1_SMMU_SCACHEI_L2L3 COMN1_SMMU_SCACHEI_L2L3;
    volatile U_COMN1_SMMU_FAMA_CTRL0_NS COMN1_SMMU_FAMA_CTRL0_NS;
    volatile U_COMN1_SMMU_FAMA_CTRL1_NS COMN1_SMMU_FAMA_CTRL1_NS;
    volatile unsigned int           RESERVED_1[54];
    volatile U_COMN1_SMMU_ADDR_MSB  COMN1_SMMU_ADDR_MSB;
    volatile unsigned int           COMN1_SMMU_ERR_RDADDR;
    volatile unsigned int           COMN1_SMMU_ERR_WRADDR;
    volatile unsigned int           RESERVED_2;
    volatile unsigned int           COMN1_SMMU_FAULT_ADDR_TCU;
    volatile U_COMN1_SMMU_FAULT_ID_TCU COMN1_SMMU_FAULT_ID_TCU;
    volatile unsigned int           RESERVED_3[2];
    volatile unsigned int           COMN1_SMMU_FAULT_ADDR_TBU0;
    volatile U_COMN1_SMMU_FAULT_ID_TBU0 COMN1_SMMU_FAULT_ID_TBU0;
    volatile U_COMN1_SMMU_FAULT_INFO0 COMN1_SMMU_FAULT_INFO0;
    volatile unsigned int           RESERVED_4;
    volatile unsigned int           COMN1_SMMU_FAULT_ADDR_TBU1;
    volatile U_COMN1_SMMU_FAULT_ID_TBU1 COMN1_SMMU_FAULT_ID_TBU1;
    volatile U_COMN1_SMMU_FAULT_INFO1 COMN1_SMMU_FAULT_INFO1;
    volatile unsigned int           RESERVED_5;
    volatile unsigned int           COMN1_SMMU_FAULT_ADDR_TBU2;
    volatile U_COMN1_SMMU_FAULT_ID_TBU2 COMN1_SMMU_FAULT_ID_TBU2;
    volatile U_COMN1_SMMU_FAULT_INFO2 COMN1_SMMU_FAULT_INFO2;
    volatile unsigned int           RESERVED_6;
    volatile unsigned int           COMN1_SMMU_FAULT_ADDR_TBU3;
    volatile U_COMN1_SMMU_FAULT_ID_TBU3 COMN1_SMMU_FAULT_ID_TBU3;
    volatile U_COMN1_SMMU_FAULT_INFO3 COMN1_SMMU_FAULT_INFO3;
    volatile unsigned int           RESERVED_7[9];
    volatile U_COMN1_SMMU_DBGRPTR_TLB COMN1_SMMU_DBGRPTR_TLB;
    volatile U_COMN1_SMMU_DBGRDATA_TLB COMN1_SMMU_DBGRDATA_TLB;
    volatile U_COMN1_SMMU_DBGRPTR_CACHE COMN1_SMMU_DBGRPTR_CACHE;
    volatile U_COMN1_SMMU_DBGRDATA0_CACHE COMN1_SMMU_DBGRDATA0_CACHE;
    volatile U_COMN1_SMMU_DBGRDATA1_CACHE COMN1_SMMU_DBGRDATA1_CACHE;
    volatile U_COMN1_SMMU_DBGAXI_CTRL COMN1_SMMU_DBGAXI_CTRL;
    volatile unsigned int           COMN1_SMMU_OVA_ADDR;
    volatile U_COMN1_SMMU_OPA_ADDR  COMN1_SMMU_OPA_ADDR;
    volatile U_COMN1_SMMU_OVA_CTRL  COMN1_SMMU_OVA_CTRL;
    volatile unsigned int           COMN1_SMMU_OPREF_ADDR;
    volatile U_COMN1_SMMU_OPREF_CTRL COMN1_SMMU_OPREF_CTRL;
    volatile unsigned int           COMN1_SMMU_OPREF_CNT;
    volatile unsigned int           RESERVED_8[20];

} S_comn1_REGS_TYPE;








/*--------------COMN2    start 0x2062a00--------------------*/ 
/* Define the union U_COMN2_SMMU_SMR0_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr0_nscfg            : 1   ; /* [0]  */
        unsigned int    smr0_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr0_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR0_S;

/* Define the union U_COMN2_SMMU_SMR1_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr1_nscfg            : 1   ; /* [0]  */
        unsigned int    smr1_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr1_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR1_S;

/* Define the union U_COMN2_SMMU_SMR2_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr2_nscfg            : 1   ; /* [0]  */
        unsigned int    smr2_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr2_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR2_S;

/* Define the union U_COMN2_SMMU_SMR3_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr3_nscfg            : 1   ; /* [0]  */
        unsigned int    smr3_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr3_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR3_S;

/* Define the union U_COMN2_SMMU_SMR4_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr4_nscfg            : 1   ; /* [0]  */
        unsigned int    smr4_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr4_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR4_S;

/* Define the union U_COMN2_SMMU_SMR5_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr5_nscfg            : 1   ; /* [0]  */
        unsigned int    smr5_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr5_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR5_S;

/* Define the union U_COMN2_SMMU_SMR6_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr6_nscfg            : 1   ; /* [0]  */
        unsigned int    smr6_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr6_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR6_S;

/* Define the union U_COMN2_SMMU_SMR7_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr7_nscfg            : 1   ; /* [0]  */
        unsigned int    smr7_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr7_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR7_S;

/* Define the union U_COMN2_SMMU_SMR8_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr8_nscfg            : 1   ; /* [0]  */
        unsigned int    smr8_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr8_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR8_S;

/* Define the union U_COMN2_SMMU_SMR9_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr9_nscfg            : 1   ; /* [0]  */
        unsigned int    smr9_nscfg_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr9_offset_addr_s    : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR9_S;

/* Define the union U_COMN2_SMMU_SMR10_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr10_nscfg           : 1   ; /* [0]  */
        unsigned int    smr10_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr10_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR10_S;

/* Define the union U_COMN2_SMMU_SMR11_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr11_nscfg           : 1   ; /* [0]  */
        unsigned int    smr11_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr11_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR11_S;

/* Define the union U_COMN2_SMMU_SMR12_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr12_nscfg           : 1   ; /* [0]  */
        unsigned int    smr12_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr12_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR12_S;

/* Define the union U_COMN2_SMMU_SMR13_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr13_nscfg           : 1   ; /* [0]  */
        unsigned int    smr13_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr13_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR13_S;

/* Define the union U_COMN2_SMMU_SMR14_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr14_nscfg           : 1   ; /* [0]  */
        unsigned int    smr14_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr14_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR14_S;

/* Define the union U_COMN2_SMMU_SMR15_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr15_nscfg           : 1   ; /* [0]  */
        unsigned int    smr15_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr15_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR15_S;

/* Define the union U_COMN2_SMMU_SMR16_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr16_nscfg           : 1   ; /* [0]  */
        unsigned int    smr16_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr16_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR16_S;

/* Define the union U_COMN2_SMMU_SMR17_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr17_nscfg           : 1   ; /* [0]  */
        unsigned int    smr17_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr17_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR17_S;

/* Define the union U_COMN2_SMMU_SMR18_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr18_nscfg           : 1   ; /* [0]  */
        unsigned int    smr18_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr18_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR18_S;

/* Define the union U_COMN2_SMMU_SMR19_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr19_nscfg           : 1   ; /* [0]  */
        unsigned int    smr19_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr19_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR19_S;

/* Define the union U_COMN2_SMMU_SMR20_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr20_nscfg           : 1   ; /* [0]  */
        unsigned int    smr20_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr20_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR20_S;

/* Define the union U_COMN2_SMMU_SMR21_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr21_nscfg           : 1   ; /* [0]  */
        unsigned int    smr21_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr21_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR21_S;

/* Define the union U_COMN2_SMMU_SMR22_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr22_nscfg           : 1   ; /* [0]  */
        unsigned int    smr22_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr22_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR22_S;

/* Define the union U_COMN2_SMMU_SMR23_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr23_nscfg           : 1   ; /* [0]  */
        unsigned int    smr23_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr23_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR23_S;

/* Define the union U_COMN2_SMMU_SMR24_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr24_nscfg           : 1   ; /* [0]  */
        unsigned int    smr24_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr24_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR24_S;

/* Define the union U_COMN2_SMMU_SMR25_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr25_nscfg           : 1   ; /* [0]  */
        unsigned int    smr25_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr25_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR25_S;

/* Define the union U_COMN2_SMMU_SMR26_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr26_nscfg           : 1   ; /* [0]  */
        unsigned int    smr26_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr26_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR26_S;

/* Define the union U_COMN2_SMMU_SMR27_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr27_nscfg           : 1   ; /* [0]  */
        unsigned int    smr27_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr27_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR27_S;

/* Define the union U_COMN2_SMMU_SMR28_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr28_nscfg           : 1   ; /* [0]  */
        unsigned int    smr28_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr28_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR28_S;

/* Define the union U_COMN2_SMMU_SMR29_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr29_nscfg           : 1   ; /* [0]  */
        unsigned int    smr29_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr29_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR29_S;

/* Define the union U_COMN2_SMMU_SMR30_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr30_nscfg           : 1   ; /* [0]  */
        unsigned int    smr30_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr30_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR30_S;

/* Define the union U_COMN2_SMMU_SMR31_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr31_nscfg           : 1   ; /* [0]  */
        unsigned int    smr31_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr31_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR31_S;

/* Define the union U_COMN2_SMMU_SMR32_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr32_nscfg           : 1   ; /* [0]  */
        unsigned int    smr32_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr32_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR32_S;

/* Define the union U_COMN2_SMMU_SMR33_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr33_nscfg           : 1   ; /* [0]  */
        unsigned int    smr33_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr33_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR33_S;

/* Define the union U_COMN2_SMMU_SMR34_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr34_nscfg           : 1   ; /* [0]  */
        unsigned int    smr34_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr34_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR34_S;

/* Define the union U_COMN2_SMMU_SMR35_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr35_nscfg           : 1   ; /* [0]  */
        unsigned int    smr35_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr35_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR35_S;

/* Define the union U_COMN2_SMMU_SMR36_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr36_nscfg           : 1   ; /* [0]  */
        unsigned int    smr36_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr36_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR36_S;

/* Define the union U_COMN2_SMMU_SMR37_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr37_nscfg           : 1   ; /* [0]  */
        unsigned int    smr37_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr37_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR37_S;

/* Define the union U_COMN2_SMMU_SMR38_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr38_nscfg           : 1   ; /* [0]  */
        unsigned int    smr38_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr38_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR38_S;

/* Define the union U_COMN2_SMMU_SMR39_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr39_nscfg           : 1   ; /* [0]  */
        unsigned int    smr39_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr39_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR39_S;

/* Define the union U_COMN2_SMMU_SMR40_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr40_nscfg           : 1   ; /* [0]  */
        unsigned int    smr40_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr40_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR40_S;

/* Define the union U_COMN2_SMMU_SMR41_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr41_nscfg           : 1   ; /* [0]  */
        unsigned int    smr41_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr41_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR41_S;

/* Define the union U_COMN2_SMMU_SMR42_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr42_nscfg           : 1   ; /* [0]  */
        unsigned int    smr42_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr42_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR42_S;

/* Define the union U_COMN2_SMMU_SMR43_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr43_nscfg           : 1   ; /* [0]  */
        unsigned int    smr43_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr43_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR43_S;

/* Define the union U_COMN2_SMMU_SMR44_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr44_nscfg           : 1   ; /* [0]  */
        unsigned int    smr44_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr44_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR44_S;

/* Define the union U_COMN2_SMMU_SMR45_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr45_nscfg           : 1   ; /* [0]  */
        unsigned int    smr45_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr45_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR45_S;

/* Define the union U_COMN2_SMMU_SMR46_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr46_nscfg           : 1   ; /* [0]  */
        unsigned int    smr46_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr46_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR46_S;

/* Define the union U_COMN2_SMMU_SMR47_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr47_nscfg           : 1   ; /* [0]  */
        unsigned int    smr47_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr47_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR47_S;

/* Define the union U_COMN2_SMMU_SMR48_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr48_nscfg           : 1   ; /* [0]  */
        unsigned int    smr48_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr48_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR48_S;

/* Define the union U_COMN2_SMMU_SMR49_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr49_nscfg           : 1   ; /* [0]  */
        unsigned int    smr49_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr49_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR49_S;

/* Define the union U_COMN2_SMMU_SMR50_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr50_nscfg           : 1   ; /* [0]  */
        unsigned int    smr50_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr50_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR50_S;

/* Define the union U_COMN2_SMMU_SMR51_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr51_nscfg           : 1   ; /* [0]  */
        unsigned int    smr51_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr51_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR51_S;

/* Define the union U_COMN2_SMMU_SMR52_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr52_nscfg           : 1   ; /* [0]  */
        unsigned int    smr52_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr52_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR52_S;

/* Define the union U_COMN2_SMMU_SMR53_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr53_nscfg           : 1   ; /* [0]  */
        unsigned int    smr53_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr53_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR53_S;

/* Define the union U_COMN2_SMMU_SMR54_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr54_nscfg           : 1   ; /* [0]  */
        unsigned int    smr54_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr54_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR54_S;

/* Define the union U_COMN2_SMMU_SMR55_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr55_nscfg           : 1   ; /* [0]  */
        unsigned int    smr55_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr55_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR55_S;

/* Define the union U_COMN2_SMMU_SMR56_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr56_nscfg           : 1   ; /* [0]  */
        unsigned int    smr56_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr56_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR56_S;

/* Define the union U_COMN2_SMMU_SMR57_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr57_nscfg           : 1   ; /* [0]  */
        unsigned int    smr57_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr57_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR57_S;

/* Define the union U_COMN2_SMMU_SMR58_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr58_nscfg           : 1   ; /* [0]  */
        unsigned int    smr58_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr58_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR58_S;

/* Define the union U_COMN2_SMMU_SMR59_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr59_nscfg           : 1   ; /* [0]  */
        unsigned int    smr59_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr59_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR59_S;

/* Define the union U_COMN2_SMMU_SMR60_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr60_nscfg           : 1   ; /* [0]  */
        unsigned int    smr60_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr60_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR60_S;

/* Define the union U_COMN2_SMMU_SMR61_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr61_nscfg           : 1   ; /* [0]  */
        unsigned int    smr61_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr61_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR61_S;

/* Define the union U_COMN2_SMMU_SMR62_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr62_nscfg           : 1   ; /* [0]  */
        unsigned int    smr62_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr62_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR62_S;

/* Define the union U_COMN2_SMMU_SMR63_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr63_nscfg           : 1   ; /* [0]  */
        unsigned int    smr63_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr63_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR63_S;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile unsigned int           RESERVED_1[64];
    volatile U_COMN2_SMMU_SMR0_S    COMN2_SMMU_SMR0_S;
    volatile U_COMN2_SMMU_SMR1_S    COMN2_SMMU_SMR1_S;
    volatile U_COMN2_SMMU_SMR2_S    COMN2_SMMU_SMR2_S;
    volatile U_COMN2_SMMU_SMR3_S    COMN2_SMMU_SMR3_S;
    volatile U_COMN2_SMMU_SMR4_S    COMN2_SMMU_SMR4_S;
    volatile U_COMN2_SMMU_SMR5_S    COMN2_SMMU_SMR5_S;
    volatile U_COMN2_SMMU_SMR6_S    COMN2_SMMU_SMR6_S;
    volatile U_COMN2_SMMU_SMR7_S    COMN2_SMMU_SMR7_S;
    volatile U_COMN2_SMMU_SMR8_S    COMN2_SMMU_SMR8_S;
    volatile U_COMN2_SMMU_SMR9_S    COMN2_SMMU_SMR9_S;
    volatile U_COMN2_SMMU_SMR10_S   COMN2_SMMU_SMR10_S;
    volatile U_COMN2_SMMU_SMR11_S   COMN2_SMMU_SMR11_S;
    volatile U_COMN2_SMMU_SMR12_S   COMN2_SMMU_SMR12_S;
    volatile U_COMN2_SMMU_SMR13_S   COMN2_SMMU_SMR13_S;
    volatile U_COMN2_SMMU_SMR14_S   COMN2_SMMU_SMR14_S;
    volatile U_COMN2_SMMU_SMR15_S   COMN2_SMMU_SMR15_S;
    volatile U_COMN2_SMMU_SMR16_S   COMN2_SMMU_SMR16_S;
    volatile U_COMN2_SMMU_SMR17_S   COMN2_SMMU_SMR17_S;
    volatile U_COMN2_SMMU_SMR18_S   COMN2_SMMU_SMR18_S;
    volatile U_COMN2_SMMU_SMR19_S   COMN2_SMMU_SMR19_S;
    volatile U_COMN2_SMMU_SMR20_S   COMN2_SMMU_SMR20_S;
    volatile U_COMN2_SMMU_SMR21_S   COMN2_SMMU_SMR21_S;
    volatile U_COMN2_SMMU_SMR22_S   COMN2_SMMU_SMR22_S;
    volatile U_COMN2_SMMU_SMR23_S   COMN2_SMMU_SMR23_S;
    volatile U_COMN2_SMMU_SMR24_S   COMN2_SMMU_SMR24_S;
    volatile U_COMN2_SMMU_SMR25_S   COMN2_SMMU_SMR25_S;
    volatile U_COMN2_SMMU_SMR26_S   COMN2_SMMU_SMR26_S;
    volatile U_COMN2_SMMU_SMR27_S   COMN2_SMMU_SMR27_S;
    volatile U_COMN2_SMMU_SMR28_S   COMN2_SMMU_SMR28_S;
    volatile U_COMN2_SMMU_SMR29_S   COMN2_SMMU_SMR29_S;
    volatile U_COMN2_SMMU_SMR30_S   COMN2_SMMU_SMR30_S;
    volatile U_COMN2_SMMU_SMR31_S   COMN2_SMMU_SMR31_S;
    volatile U_COMN2_SMMU_SMR32_S   COMN2_SMMU_SMR32_S;
    volatile U_COMN2_SMMU_SMR33_S   COMN2_SMMU_SMR33_S;
    volatile U_COMN2_SMMU_SMR34_S   COMN2_SMMU_SMR34_S;
    volatile U_COMN2_SMMU_SMR35_S   COMN2_SMMU_SMR35_S;
    volatile U_COMN2_SMMU_SMR36_S   COMN2_SMMU_SMR36_S;
    volatile U_COMN2_SMMU_SMR37_S   COMN2_SMMU_SMR37_S;
    volatile U_COMN2_SMMU_SMR38_S   COMN2_SMMU_SMR38_S;
    volatile U_COMN2_SMMU_SMR39_S   COMN2_SMMU_SMR39_S;
    volatile U_COMN2_SMMU_SMR40_S   COMN2_SMMU_SMR40_S;
    volatile U_COMN2_SMMU_SMR41_S   COMN2_SMMU_SMR41_S;
    volatile U_COMN2_SMMU_SMR42_S   COMN2_SMMU_SMR42_S;
    volatile U_COMN2_SMMU_SMR43_S   COMN2_SMMU_SMR43_S;
    volatile U_COMN2_SMMU_SMR44_S   COMN2_SMMU_SMR44_S;
    volatile U_COMN2_SMMU_SMR45_S   COMN2_SMMU_SMR45_S;
    volatile U_COMN2_SMMU_SMR46_S   COMN2_SMMU_SMR46_S;
    volatile U_COMN2_SMMU_SMR47_S   COMN2_SMMU_SMR47_S;
    volatile U_COMN2_SMMU_SMR48_S   COMN2_SMMU_SMR48_S;
    volatile U_COMN2_SMMU_SMR49_S   COMN2_SMMU_SMR49_S;
    volatile U_COMN2_SMMU_SMR50_S   COMN2_SMMU_SMR50_S;
    volatile U_COMN2_SMMU_SMR51_S   COMN2_SMMU_SMR51_S;
    volatile U_COMN2_SMMU_SMR52_S   COMN2_SMMU_SMR52_S;
    volatile U_COMN2_SMMU_SMR53_S   COMN2_SMMU_SMR53_S;
    volatile U_COMN2_SMMU_SMR54_S   COMN2_SMMU_SMR54_S;
    volatile U_COMN2_SMMU_SMR55_S   COMN2_SMMU_SMR55_S;
    volatile U_COMN2_SMMU_SMR56_S   COMN2_SMMU_SMR56_S;
    volatile U_COMN2_SMMU_SMR57_S   COMN2_SMMU_SMR57_S;
    volatile U_COMN2_SMMU_SMR58_S   COMN2_SMMU_SMR58_S;
    volatile U_COMN2_SMMU_SMR59_S   COMN2_SMMU_SMR59_S;
    volatile U_COMN2_SMMU_SMR60_S   COMN2_SMMU_SMR60_S;
    volatile U_COMN2_SMMU_SMR61_S   COMN2_SMMU_SMR61_S;
    volatile U_COMN2_SMMU_SMR62_S   COMN2_SMMU_SMR62_S;
    volatile U_COMN2_SMMU_SMR63_S   COMN2_SMMU_SMR63_S;

} S_comn2_REGS_TYPE;






/*--------------COMN3    start 0x2062c00--------------------*/ 
/* Define the union U_COMN2_SMMU_SMR64_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr64_nscfg           : 1   ; /* [0]  */
        unsigned int    smr64_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr64_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR64_S;

/* Define the union U_COMN2_SMMU_SMR65_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr65_nscfg           : 1   ; /* [0]  */
        unsigned int    smr65_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr65_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR65_S;

/* Define the union U_COMN2_SMMU_SMR66_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr66_nscfg           : 1   ; /* [0]  */
        unsigned int    smr66_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr66_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR66_S;

/* Define the union U_COMN2_SMMU_SMR67_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr67_nscfg           : 1   ; /* [0]  */
        unsigned int    smr67_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr67_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR67_S;

/* Define the union U_COMN2_SMMU_SMR68_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr68_nscfg           : 1   ; /* [0]  */
        unsigned int    smr68_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr68_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR68_S;

/* Define the union U_COMN2_SMMU_SMR69_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr69_nscfg           : 1   ; /* [0]  */
        unsigned int    smr69_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr69_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR69_S;

/* Define the union U_COMN2_SMMU_SMR70_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr70_nscfg           : 1   ; /* [0]  */
        unsigned int    smr70_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr70_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR70_S;

/* Define the union U_COMN2_SMMU_SMR71_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr71_nscfg           : 1   ; /* [0]  */
        unsigned int    smr71_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr71_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR71_S;

/* Define the union U_COMN2_SMMU_SMR72_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr72_nscfg           : 1   ; /* [0]  */
        unsigned int    smr72_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr72_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR72_S;

/* Define the union U_COMN2_SMMU_SMR73_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr73_nscfg           : 1   ; /* [0]  */
        unsigned int    smr73_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr73_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR73_S;

/* Define the union U_COMN2_SMMU_SMR74_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr74_nscfg           : 1   ; /* [0]  */
        unsigned int    smr74_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr74_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR74_S;

/* Define the union U_COMN2_SMMU_SMR75_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr75_nscfg           : 1   ; /* [0]  */
        unsigned int    smr75_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr75_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR75_S;

/* Define the union U_COMN2_SMMU_SMR76_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr76_nscfg           : 1   ; /* [0]  */
        unsigned int    smr76_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr76_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR76_S;

/* Define the union U_COMN2_SMMU_SMR77_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr77_nscfg           : 1   ; /* [0]  */
        unsigned int    smr77_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr77_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR77_S;

/* Define the union U_COMN2_SMMU_SMR78_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr78_nscfg           : 1   ; /* [0]  */
        unsigned int    smr78_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr78_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR78_S;

/* Define the union U_COMN2_SMMU_SMR79_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr79_nscfg           : 1   ; /* [0]  */
        unsigned int    smr79_nscfg_en        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    smr79_offset_addr_s   : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN2_SMMU_SMR79_S;

/* Define the union U_COMN3_SMMU_RLD_EN2_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smr_rld_en2_s         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_RLD_EN2_S;

/* Define the union U_COMN3_SMMU_INTMAS_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_permis_msk       : 1   ; /* [0]  */
        unsigned int    ints_ext_msk          : 1   ; /* [1]  */
        unsigned int    ints_tlbmiss_msk      : 1   ; /* [2]  */
        unsigned int    ints_ptw_trans_msk    : 1   ; /* [3]  */
        unsigned int    ints_ptw_invalid_msk  : 1   ; /* [4]  */
        unsigned int    ints_ptw_ns_msk       : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_INTMAS_S;

/* Define the union U_COMN3_SMMU_INTRAW_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_permis_raw       : 1   ; /* [0]  */
        unsigned int    ints_ext_raw          : 1   ; /* [1]  */
        unsigned int    ints_tlbmiss_raw      : 1   ; /* [2]  */
        unsigned int    ints_ptw_trans_raw    : 1   ; /* [3]  */
        unsigned int    ints_ptw_invalid_raw  : 1   ; /* [4]  */
        unsigned int    ints_ptw_ns_raw       : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_INTRAW_S;

/* Define the union U_COMN3_SMMU_INTSTAT_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_permis_stat      : 1   ; /* [0]  */
        unsigned int    ints_ext_stat         : 1   ; /* [1]  */
        unsigned int    ints_tlbmiss_stat     : 1   ; /* [2]  */
        unsigned int    ints_ptw_trans_stat   : 1   ; /* [3]  */
        unsigned int    ints_ptw_invalid_stat : 1   ; /* [4]  */
        unsigned int    ints_ptw_ns_stat      : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_INTSTAT_S;

/* Define the union U_COMN3_SMMU_INTCLR_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_permis_clr       : 1   ; /* [0]  */
        unsigned int    ints_ext_clr          : 1   ; /* [1]  */
        unsigned int    ints_tlbmiss_clr      : 1   ; /* [2]  */
        unsigned int    ints_ptw_trans_clr    : 1   ; /* [3]  */
        unsigned int    ints_ptw_invalid_clr  : 1   ; /* [4]  */
        unsigned int    ints_ptw_ns_clr       : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_INTCLR_S;

/* Define the union U_COMN3_SMMU_SCR_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    glb_nscfg             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_SCR_S;

/* Define the union U_COMN3_SMMU_SCB_SCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scb_bypass            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_SCB_SCTRL;

/* Define the union U_COMN3_SMMU_SCB_TTBCR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scb_ttbcr_des         : 1   ; /* [0]  */
        unsigned int    reserved_0             : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_SCB_TTBCR;

/* Define the union U_COMN3_SMMU_OFFSET_ADDR_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    offset_addr_s         : 14  ; /* [13..0]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_OFFSET_ADDR_S;

/* Define the union U_COMN3_SMMU_FAMA_CTRL0_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fama_sdes_msb_s       : 7   ; /* [6..0]  */
        unsigned int    fama_chn_sel_s        : 1   ; /* [7]  */
        unsigned int    fama_bps_msb_s        : 6   ; /* [13..8]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_FAMA_CTRL0_S;

/* Define the union U_COMN3_SMMU_FAMA_CTRL1_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fama_ptw_msb_s        : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_FAMA_CTRL1_S;

/* Define the union U_COMN3_SMMU_DBGRPTR_TLB_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_tlb_en            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_DBGRPTR_TLB_S;

/* Define the union U_COMN3_SMMU_DBGRPTR_CACHE_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbg_cache_en          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_DBGRPTR_CACHE_S;

/* Define the union U_COMN3_SMMU_OVERRIDE_CTRL_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    override_va_security  : 1   ; /* [1]  */
        unsigned int    reserved_1            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_COMN3_SMMU_OVERRIDE_CTRL_S;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_COMN2_SMMU_SMR64_S   COMN2_SMMU_SMR64_S;
    volatile U_COMN2_SMMU_SMR65_S   COMN2_SMMU_SMR65_S;
    volatile U_COMN2_SMMU_SMR66_S   COMN2_SMMU_SMR66_S;
    volatile U_COMN2_SMMU_SMR67_S   COMN2_SMMU_SMR67_S;
    volatile U_COMN2_SMMU_SMR68_S   COMN2_SMMU_SMR68_S;
    volatile U_COMN2_SMMU_SMR69_S   COMN2_SMMU_SMR69_S;
    volatile U_COMN2_SMMU_SMR70_S   COMN2_SMMU_SMR70_S;
    volatile U_COMN2_SMMU_SMR71_S   COMN2_SMMU_SMR71_S;
    volatile U_COMN2_SMMU_SMR72_S   COMN2_SMMU_SMR72_S;
    volatile U_COMN2_SMMU_SMR73_S   COMN2_SMMU_SMR73_S;
    volatile U_COMN2_SMMU_SMR74_S   COMN2_SMMU_SMR74_S;
    volatile U_COMN2_SMMU_SMR75_S   COMN2_SMMU_SMR75_S;
    volatile U_COMN2_SMMU_SMR76_S   COMN2_SMMU_SMR76_S;
    volatile U_COMN2_SMMU_SMR77_S   COMN2_SMMU_SMR77_S;
    volatile U_COMN2_SMMU_SMR78_S   COMN2_SMMU_SMR78_S;
    volatile U_COMN2_SMMU_SMR79_S   COMN2_SMMU_SMR79_S;
    volatile unsigned int           RESERVED_0[44];
    volatile unsigned int           COMN3_SMMU_RLD_EN0_S;
    volatile unsigned int           COMN3_SMMU_RLD_EN1_S;
    volatile U_COMN3_SMMU_RLD_EN2_S COMN3_SMMU_RLD_EN2_S;
    volatile unsigned int           RESERVED_1;
    volatile U_COMN3_SMMU_INTMAS_S  COMN3_SMMU_INTMAS_S;
    volatile U_COMN3_SMMU_INTRAW_S  COMN3_SMMU_INTRAW_S;
    volatile U_COMN3_SMMU_INTSTAT_S COMN3_SMMU_INTSTAT_S;
    volatile U_COMN3_SMMU_INTCLR_S  COMN3_SMMU_INTCLR_S;
    volatile U_COMN3_SMMU_SCR_S     COMN3_SMMU_SCR_S;
    volatile U_COMN3_SMMU_SCB_SCTRL COMN3_SMMU_SCB_SCTRL;
    volatile unsigned int           COMN3_SMMU_SCB_TTBR;
    volatile U_COMN3_SMMU_SCB_TTBCR COMN3_SMMU_SCB_TTBCR;
    volatile U_COMN3_SMMU_OFFSET_ADDR_S COMN3_SMMU_OFFSET_ADDR_S;
    volatile U_COMN3_SMMU_FAMA_CTRL0_S COMN3_SMMU_FAMA_CTRL0_S;
    volatile U_COMN3_SMMU_FAMA_CTRL1_S COMN3_SMMU_FAMA_CTRL1_S;
    volatile U_COMN3_SMMU_DBGRPTR_TLB_S COMN3_SMMU_DBGRPTR_TLB_S;
    volatile U_COMN3_SMMU_DBGRPTR_CACHE_S COMN3_SMMU_DBGRPTR_CACHE_S;
    volatile U_COMN3_SMMU_OVERRIDE_CTRL_S COMN3_SMMU_OVERRIDE_CTRL_S;
    volatile unsigned int           RESERVED_2[50];

} S_comn3_REGS_TYPE;








/*--------------mmu0       start 0x20623e00--------------------*/ 
/* Define the union U_MST_GLB_SCR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    glb_scr               : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_GLB_SCR;

/* Define the union U_MST_GLB_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    glb_bypass            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_GLB_BYPASS;

/* Define the union U_MST_SID0_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sid0_bypass           : 1   ; /* [0]  */
        unsigned int    sid1_bypass           : 1   ; /* [1]  */
        unsigned int    sid2_bypass           : 1   ; /* [2]  */
        unsigned int    sid3_bypass           : 1   ; /* [3]  */
        unsigned int    sid4_bypass           : 1   ; /* [4]  */
        unsigned int    sid5_bypass           : 1   ; /* [5]  */
        unsigned int    sid6_bypass           : 1   ; /* [6]  */
        unsigned int    sid7_bypass           : 1   ; /* [7]  */
        unsigned int    sid8_bypass           : 1   ; /* [8]  */
        unsigned int    sid9_bypass           : 1   ; /* [9]  */
        unsigned int    sid10_bypass          : 1   ; /* [10]  */
        unsigned int    sid11_bypass          : 1   ; /* [11]  */
        unsigned int    sid12_bypass          : 1   ; /* [12]  */
        unsigned int    sid13_bypass          : 1   ; /* [13]  */
        unsigned int    sid14_bypass          : 1   ; /* [14]  */
        unsigned int    sid15_bypass          : 1   ; /* [15]  */
        unsigned int    sid16_bypass          : 1   ; /* [16]  */
        unsigned int    sid17_bypass          : 1   ; /* [17]  */
        unsigned int    sid18_bypass          : 1   ; /* [18]  */
        unsigned int    sid19_bypass          : 1   ; /* [19]  */
        unsigned int    sid20_bypass          : 1   ; /* [20]  */
        unsigned int    sid21_bypass          : 1   ; /* [21]  */
        unsigned int    sid22_bypass          : 1   ; /* [22]  */
        unsigned int    sid23_bypass          : 1   ; /* [23]  */
        unsigned int    sid24_bypass          : 1   ; /* [24]  */
        unsigned int    sid25_bypass          : 1   ; /* [25]  */
        unsigned int    sid26_bypass          : 1   ; /* [26]  */
        unsigned int    sid27_bypass          : 1   ; /* [27]  */
        unsigned int    sid28_bypass          : 1   ; /* [28]  */
        unsigned int    sid29_bypass          : 1   ; /* [29]  */
        unsigned int    sid30_bypass          : 1   ; /* [30]  */
        unsigned int    sid31_bypass          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_SID0_BYPASS;

/* Define the union U_MST_SID1_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sid32_bypass          : 1   ; /* [0]  */
        unsigned int    sid33_bypass          : 1   ; /* [1]  */
        unsigned int    sid34_bypass          : 1   ; /* [2]  */
        unsigned int    sid35_bypass          : 1   ; /* [3]  */
        unsigned int    sid36_bypass          : 1   ; /* [4]  */
        unsigned int    sid37_bypass          : 1   ; /* [5]  */
        unsigned int    sid38_bypass          : 1   ; /* [6]  */
        unsigned int    sid39_bypass          : 1   ; /* [7]  */
        unsigned int    sid40_bypass          : 1   ; /* [8]  */
        unsigned int    sid41_bypass          : 1   ; /* [9]  */
        unsigned int    sid42_bypass          : 1   ; /* [10]  */
        unsigned int    sid43_bypass          : 1   ; /* [11]  */
        unsigned int    sid44_bypass          : 1   ; /* [12]  */
        unsigned int    sid45_bypass          : 1   ; /* [13]  */
        unsigned int    sid46_bypass          : 1   ; /* [14]  */
        unsigned int    sid47_bypass          : 1   ; /* [15]  */
        unsigned int    sid48_bypass          : 1   ; /* [16]  */
        unsigned int    sid49_bypass          : 1   ; /* [17]  */
        unsigned int    sid50_bypass          : 1   ; /* [18]  */
        unsigned int    sid51_bypass          : 1   ; /* [19]  */
        unsigned int    sid52_bypass          : 1   ; /* [20]  */
        unsigned int    sid53_bypass          : 1   ; /* [21]  */
        unsigned int    sid54_bypass          : 1   ; /* [22]  */
        unsigned int    sid55_bypass          : 1   ; /* [23]  */
        unsigned int    sid56_bypass          : 1   ; /* [24]  */
        unsigned int    sid57_bypass          : 1   ; /* [25]  */
        unsigned int    sid58_bypass          : 1   ; /* [26]  */
        unsigned int    sid59_bypass          : 1   ; /* [27]  */
        unsigned int    sid60_bypass          : 1   ; /* [28]  */
        unsigned int    sid61_bypass          : 1   ; /* [29]  */
        unsigned int    sid62_bypass          : 1   ; /* [30]  */
        unsigned int    sid63_bypass          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_SID1_BYPASS;

/* Define the union U_MST_PREF_CHN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mst_pref_0chn         : 1   ; /* [0]  */
        unsigned int    mst_pref_1chn         : 1   ; /* [1]  */
        unsigned int    mst_pref_2chn         : 1   ; /* [2]  */
        unsigned int    mst_pref_3chn         : 1   ; /* [3]  */
        unsigned int    mst_pref_4chn         : 1   ; /* [4]  */
        unsigned int    mst_pref_5chn         : 1   ; /* [5]  */
        unsigned int    mst_pref_6chn         : 1   ; /* [6]  */
        unsigned int    mst_pref_7chn         : 1   ; /* [7]  */
        unsigned int    mst_pref_8chn         : 1   ; /* [8]  */
        unsigned int    mst_pref_9chn         : 1   ; /* [9]  */
        unsigned int    mst_pref_10chn        : 1   ; /* [10]  */
        unsigned int    mst_pref_11chn        : 1   ; /* [11]  */
        unsigned int    mst_pref_12chn        : 1   ; /* [12]  */
        unsigned int    mst_pref_13chn        : 1   ; /* [13]  */
        unsigned int    mst_pref_14chn        : 1   ; /* [14]  */
        unsigned int    mst_pref_15chn        : 1   ; /* [15]  */
        unsigned int    mst_pref_16chn        : 1   ; /* [16]  */
        unsigned int    mst_pref_17chn        : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_PREF_CHN;

/* Define the union U_MST_RD0_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd0_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd0_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd0_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD0_0CFG;

/* Define the union U_MST_RD0_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd0_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd0_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd0_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd0_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD0_1CFG;

/* Define the union U_MST_RD1_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd1_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd1_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd1_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD1_0CFG;

/* Define the union U_MST_RD1_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd1_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd1_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd1_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd1_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD1_1CFG;

/* Define the union U_MST_RD2_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd2_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd2_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd2_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD2_0CFG;

/* Define the union U_MST_RD2_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd2_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd2_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd2_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd2_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD2_1CFG;

/* Define the union U_MST_RD3_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd3_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd3_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd3_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD3_0CFG;

/* Define the union U_MST_RD3_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd3_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd3_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd3_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd3_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD3_1CFG;

/* Define the union U_MST_RD4_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd4_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd4_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd4_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD4_0CFG;

/* Define the union U_MST_RD4_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd4_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd4_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd4_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd4_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD4_1CFG;

/* Define the union U_MST_RD5_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd5_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd5_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd5_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD5_0CFG;

/* Define the union U_MST_RD5_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd5_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd5_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd5_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd5_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD5_1CFG;

/* Define the union U_MST_RD6_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd6_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd6_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd6_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD6_0CFG;

/* Define the union U_MST_RD6_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd6_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd6_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd6_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd6_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD6_1CFG;

/* Define the union U_MST_RD7_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd7_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd7_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd7_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD7_0CFG;

/* Define the union U_MST_RD7_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd7_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd7_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd7_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd7_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD7_1CFG;

/* Define the union U_MST_RD8_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd8_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd8_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd8_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD8_0CFG;

/* Define the union U_MST_RD8_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd8_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd8_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd8_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd8_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD8_1CFG;

/* Define the union U_MST_RD9_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd9_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    rd9_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    rd9_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD9_0CFG;

/* Define the union U_MST_RD9_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd9_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    rd9_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    rd9_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    rd9_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_RD9_1CFG;

/* Define the union U_MST_WR0_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr0_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr0_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr0_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR0_0CFG;

/* Define the union U_MST_WR0_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr0_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr0_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr0_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr0_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR0_1CFG;

/* Define the union U_MST_WR1_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr1_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr1_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr1_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR1_0CFG;

/* Define the union U_MST_WR1_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr1_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr1_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr1_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr1_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR1_1CFG;

/* Define the union U_MST_WR2_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr2_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr2_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr2_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR2_0CFG;

/* Define the union U_MST_WR2_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr2_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr2_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr2_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr2_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR2_1CFG;

/* Define the union U_MST_WR3_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr3_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr3_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr3_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR3_0CFG;

/* Define the union U_MST_WR3_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr3_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr3_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr3_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr3_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR3_1CFG;

/* Define the union U_MST_WR4_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr4_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr4_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr4_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR4_0CFG;

/* Define the union U_MST_WR4_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr4_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr4_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr4_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr4_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR4_1CFG;

/* Define the union U_MST_WR5_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr5_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr5_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr5_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR5_0CFG;

/* Define the union U_MST_WR5_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr5_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr5_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr5_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr5_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR5_1CFG;

/* Define the union U_MST_WR6_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr6_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr6_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr6_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR6_0CFG;

/* Define the union U_MST_WR6_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr6_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr6_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr6_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr6_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR6_1CFG;

/* Define the union U_MST_WR7_0CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr7_tlb_depth         : 9   ; /* [8..0]  */
        unsigned int    wr7_tlb_base          : 9   ; /* [17..9]  */
        unsigned int    wr7_tlb_last          : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR7_0CFG;

/* Define the union U_MST_WR7_1CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr7_tlb_nxt           : 8   ; /* [7..0]  */
        unsigned int    wr7_tlb_uw            : 8   ; /* [15..8]  */
        unsigned int    wr7_tlb_upd_dis       : 8   ; /* [23..16]  */
        unsigned int    wr7_tlb_upd_len       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_WR7_1CFG;

/* Define the union U_MST_SOFT_RST_REQ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    axi_soft_rst_req      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_SOFT_RST_REQ;

/* Define the union U_MST_SOFT_RST_ACK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    axi_soft_rst_ack      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_SOFT_RST_ACK;

/* Define the union U_MST_VEDU_DFX_PREF_FSM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_pref_fsm          : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_PREF_FSM;

/* Define the union U_MST_VEDU_DFX_ARJDG_FSM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_ar_fsm            : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_ARJDG_FSM;

/* Define the union U_MST_VEDU_DFX_AWJDG_FSM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_aw_fsm            : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_AWJDG_FSM;

/* Define the union U_MST_VEDU_DFX_PREF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mst2com_pref_vld      : 1   ; /* [0]  */
        unsigned int    com2mst_pref_rdy      : 1   ; /* [1]  */
        unsigned int    com2mst_pref_resp_vld : 1   ; /* [2]  */
        unsigned int    mst2com_pref_resp_rdy : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_PREF;

/* Define the union U_MST_VEDU_DFX_ARJDG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    emar2mst_arvalid      : 1   ; /* [0]  */
        unsigned int    mst2emar_arready      : 1   ; /* [1]  */
        unsigned int    mst2com_arvalid       : 1   ; /* [2]  */
        unsigned int    com2mst_arready       : 1   ; /* [3]  */
        unsigned int    ar_rx_fifo_full       : 1   ; /* [4]  */
        unsigned int    ar_rx_fifo_empty      : 1   ; /* [5]  */
        unsigned int    ar_tx_fifo_full       : 1   ; /* [6]  */
        unsigned int    ar_tx_fifo_empty      : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_ARJDG;

/* Define the union U_MST_VEDU_DFX_AWJDG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    emar2mst_awvalid      : 1   ; /* [0]  */
        unsigned int    mst2emar_awready      : 1   ; /* [1]  */
        unsigned int    mst2com_awvalid       : 1   ; /* [2]  */
        unsigned int    com2mst_awready       : 1   ; /* [3]  */
        unsigned int    aw_rx_fifo_full       : 1   ; /* [4]  */
        unsigned int    aw_rx_fifo_empty      : 1   ; /* [5]  */
        unsigned int    aw_tx_fifo_full       : 1   ; /* [6]  */
        unsigned int    aw_tx_fifo_empty      : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_AWJDG;

/* Define the union U_MST_VEDU_DFX_ARERR_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arerr_ar_flag     : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_ARERR_FLAG;

/* Define the union U_MST_VEDU_DFX_ARERR_ID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_ar_id         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_ARERR_ID;

/* Define the union U_MST_VEDU_DFX_AWERR_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arerr_aw_flag     : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_AWERR_FLAG;

/* Define the union U_MST_VEDU_DFX_AWERR_ID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_aw_id         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_AWERR_ID;

/* Define the union U_MST_VEDU_DFX_PREF_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_pref_err          : 18  ; /* [17..0]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_PREF_FLAG;

/* Define the union U_MST_VEDU_DFX_MISS_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_miss_flag         : 18  ; /* [17..0]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_MISS_FLAG;

/* Define the union U_MST_VEDU_DFX_ID_FLAG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_tx_rd_err         : 1   ; /* [0]  */
        unsigned int    dfx_rx_rd_err         : 1   ; /* [1]  */
        unsigned int    dfx_tx_wr_err         : 1   ; /* [2]  */
        unsigned int    dfx_rx_wr_err         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_ID_FLAG;

/* Define the union U_MST_VEDU_DFX_AXI_BUS_DEC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_ar_dec            : 1   ; /* [0]  */
        unsigned int    dfx_r_dec             : 1   ; /* [1]  */
        unsigned int    dfx_aw_dec            : 1   ; /* [2]  */
        unsigned int    dfx_w_dec             : 1   ; /* [3]  */
        unsigned int    dfx_b_dec             : 1   ; /* [4]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_DFX_AXI_BUS_DEC;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_MST_GLB_SCR          MST_GLB_SCR;
    volatile unsigned int           RESERVED_1[3];
    volatile U_MST_GLB_BYPASS       MST_GLB_BYPASS;
    volatile U_MST_SID0_BYPASS      MST_SID0_BYPASS;
    volatile U_MST_SID1_BYPASS      MST_SID1_BYPASS;
    volatile U_MST_PREF_CHN         MST_PREF_CHN;
    volatile unsigned int           RESERVED_2[4];
    volatile U_MST_RD0_0CFG         MST_RD0_0CFG;
    volatile U_MST_RD0_1CFG         MST_RD0_1CFG;
    volatile U_MST_RD1_0CFG         MST_RD1_0CFG;
    volatile U_MST_RD1_1CFG         MST_RD1_1CFG;
    volatile U_MST_RD2_0CFG         MST_RD2_0CFG;
    volatile U_MST_RD2_1CFG         MST_RD2_1CFG;
    volatile U_MST_RD3_0CFG         MST_RD3_0CFG;
    volatile U_MST_RD3_1CFG         MST_RD3_1CFG;
    volatile U_MST_RD4_0CFG         MST_RD4_0CFG;
    volatile U_MST_RD4_1CFG         MST_RD4_1CFG;
    volatile U_MST_RD5_0CFG         MST_RD5_0CFG;
    volatile U_MST_RD5_1CFG         MST_RD5_1CFG;
    volatile U_MST_RD6_0CFG         MST_RD6_0CFG;
    volatile U_MST_RD6_1CFG         MST_RD6_1CFG;
    volatile U_MST_RD7_0CFG         MST_RD7_0CFG;
    volatile U_MST_RD7_1CFG         MST_RD7_1CFG;
    volatile U_MST_RD8_0CFG         MST_RD8_0CFG;
    volatile U_MST_RD8_1CFG         MST_RD8_1CFG;
    volatile U_MST_RD9_0CFG         MST_RD9_0CFG;
    volatile U_MST_RD9_1CFG         MST_RD9_1CFG;
    volatile U_MST_WR0_0CFG         MST_WR0_0CFG;
    volatile U_MST_WR0_1CFG         MST_WR0_1CFG;
    volatile U_MST_WR1_0CFG         MST_WR1_0CFG;
    volatile U_MST_WR1_1CFG         MST_WR1_1CFG;
    volatile U_MST_WR2_0CFG         MST_WR2_0CFG;
    volatile U_MST_WR2_1CFG         MST_WR2_1CFG;
    volatile U_MST_WR3_0CFG         MST_WR3_0CFG;
    volatile U_MST_WR3_1CFG         MST_WR3_1CFG;
    volatile U_MST_WR4_0CFG         MST_WR4_0CFG;
    volatile U_MST_WR4_1CFG         MST_WR4_1CFG;
    volatile U_MST_WR5_0CFG         MST_WR5_0CFG;
    volatile U_MST_WR5_1CFG         MST_WR5_1CFG;
    volatile U_MST_WR6_0CFG         MST_WR6_0CFG;
    volatile U_MST_WR6_1CFG         MST_WR6_1CFG;
    volatile U_MST_WR7_0CFG         MST_WR7_0CFG;
    volatile U_MST_WR7_1CFG         MST_WR7_1CFG;
    volatile unsigned int           RESERVED_3[16];
    volatile U_MST_SOFT_RST_REQ     MST_SOFT_RST_REQ;
    volatile U_MST_SOFT_RST_ACK     MST_SOFT_RST_ACK;
    volatile unsigned int           RESERVED_4[2];
    volatile U_MST_VEDU_DFX_PREF_FSM MST_VEDU_DFX_PREF_FSM;
    volatile U_MST_VEDU_DFX_ARJDG_FSM MST_VEDU_DFX_ARJDG_FSM;
    volatile U_MST_VEDU_DFX_AWJDG_FSM MST_VEDU_DFX_AWJDG_FSM;
    volatile unsigned int           RESERVED_5;
    volatile U_MST_VEDU_DFX_PREF    MST_VEDU_DFX_PREF;
    volatile U_MST_VEDU_DFX_ARJDG   MST_VEDU_DFX_ARJDG;
    volatile U_MST_VEDU_DFX_AWJDG   MST_VEDU_DFX_AWJDG;
    volatile unsigned int           RESERVED_6;
    volatile unsigned int           MST_VEDU_DFX_PREF_CNT;
    volatile unsigned int           MST_VEDU_DFX_RESP_CNT;
    volatile unsigned int           RESERVED_7[2];
    volatile unsigned int           MST_VEDU_DFX_ARIN_CNT;
    volatile unsigned int           MST_VEDU_DFX_AROUT_CNT;
    volatile unsigned int           MST_VEDU_DFX_ARACK_CNT;
    volatile unsigned int           RESERVED_8;
    volatile unsigned int           MST_VEDU_DFX_AWIN_CNT;
    volatile unsigned int           MST_VEDU_DFX_AWOUT_CNT;
    volatile unsigned int           MST_VEDU_DFX_WOUT_CNT;
    volatile unsigned int           MST_VEDU_DFX_AWACK_CNT;
    volatile U_MST_VEDU_DFX_ARERR_FLAG MST_VEDU_DFX_ARERR_FLAG;
    volatile U_MST_VEDU_DFX_ARERR_ID MST_VEDU_DFX_ARERR_ID;
    volatile unsigned int           MST_VEDU_DFX_ARERR_ADDR;
    volatile unsigned int           RESERVED_9;
    volatile U_MST_VEDU_DFX_AWERR_FLAG MST_VEDU_DFX_AWERR_FLAG;
    volatile U_MST_VEDU_DFX_AWERR_ID MST_VEDU_DFX_AWERR_ID;
    volatile unsigned int           MST_VEDU_DFX_AWERR_ADDR;
    volatile unsigned int           RESERVED_10;
    volatile U_MST_VEDU_DFX_PREF_FLAG MST_VEDU_DFX_PREF_FLAG;
    volatile unsigned int           RESERVED_11[3];
    volatile U_MST_VEDU_DFX_MISS_FLAG MST_VEDU_DFX_MISS_FLAG;
    volatile unsigned int           RESERVED_12[3];
    volatile unsigned int           MST_VEDU_AR_PRESS_CNT;
    volatile unsigned int           MST_VEDU_AW_PRESS_CNT;
    volatile unsigned int           RESERVED_13[2];
    volatile U_MST_VEDU_DFX_ID_FLAG MST_VEDU_DFX_ID_FLAG;
    volatile U_MST_VEDU_DFX_AXI_BUS_DEC MST_VEDU_DFX_AXI_BUS_DEC;
    volatile unsigned int           RESERVED_14[2];
    volatile unsigned int           MST_VEDU_DFX_RD_FLAG_LOW;
    volatile unsigned int           MST_VEDU_DFX_RD_FLAG_HIGH;
    volatile unsigned int           MST_VEDU_DFX_WR_FLAG_LOW;
    volatile unsigned int           MST_VEDU_DFX_WR_FLAG_HIGH;
    volatile unsigned int           RESERVED_15[12];

} S_mmu0_REGS_TYPE;








/*--------------mmu1       start 0x20624000--------------------*/ 
/* Define the union U_MST_VEDU_MODE_MMU */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vcpi_protocol         : 2   ; /* [1..0]  */
        unsigned int    vcpi_str_fmt          : 4   ; /* [5..2]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MST_VEDU_MODE_MMU;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_MST_VEDU_MODE_MMU    MST_VEDU_MODE_MMU;
    volatile unsigned int           RESERVED_1[3];
    volatile unsigned int           MST_VEDU_NBI_MVST_ADDR_STR;
    volatile unsigned int           MST_VEDU_NBI_MVST_ADDR_END;
    volatile unsigned int           MST_VEDU_NBI_MVLD_ADDR_STR;
    volatile unsigned int           MST_VEDU_NBI_MVLD_ADDR_END;
    volatile unsigned int           MST_VEDU_PMEST_ADDR_STR;
    volatile unsigned int           MST_VEDU_PMEST_ADDR_END;
    volatile unsigned int           MST_VEDU_PMELD_ADDR_STR;
    volatile unsigned int           MST_VEDU_PMELD_ADDR_END;
    volatile unsigned int           MST_VEDU_REC_YH_ADDR_STR;
    volatile unsigned int           MST_VEDU_REC_YH_ADDR_END;
    volatile unsigned int           MST_VEDU_REC_CH_ADDR_STR;
    volatile unsigned int           MST_VEDU_REC_CH_ADDR_END;
    volatile unsigned int           MST_VEDU_REC_YADDR_STR;
    volatile unsigned int           MST_VEDU_REC_YADDR_END;
    volatile unsigned int           MST_VEDU_REC_CADDR_STR;
    volatile unsigned int           MST_VEDU_REC_CADDR_END;
    volatile unsigned int           MST_VEDU_REF_YH_ADDR_STR;
    volatile unsigned int           MST_VEDU_REF_YH_ADDR_END;
    volatile unsigned int           MST_VEDU_REF_CH_ADDR_STR;
    volatile unsigned int           MST_VEDU_REF_CH_ADDR_END;
    volatile unsigned int           MST_VEDU_REF_YADDR_STR;
    volatile unsigned int           MST_VEDU_REF_YADDR_END;
    volatile unsigned int           MST_VEDU_REF_CADDR_STR;
    volatile unsigned int           MST_VEDU_REF_CADDR_END;
    volatile unsigned int           MST_VEDU_SRC_YADDR_STR;
    volatile unsigned int           MST_VEDU_SRC_YADDR_END;
    volatile unsigned int           MST_VEDU_SRC_CADDR_STR;
    volatile unsigned int           MST_VEDU_SRC_CADDR_END;
    volatile unsigned int           MST_VEDU_SRC_VADDR_STR;
    volatile unsigned int           MST_VEDU_SRC_VADDR_END;
    volatile unsigned int           MST_VEDU_LAT_ADDR_STR;
    volatile unsigned int           MST_VEDU_LAT_ADDR_END;
    volatile unsigned int           MST_VEDU_PPS_ADDR_STR;
    volatile unsigned int           MST_VEDU_PPS_ADDR_END;
    volatile unsigned int           RESERVED_2[26];
    volatile unsigned int           MST_VEDU_STRMADDR0_STR;
    volatile unsigned int           MST_VEDU_STRMADDR1_STR;
    volatile unsigned int           MST_VEDU_STRMADDR2_STR;
    volatile unsigned int           MST_VEDU_STRMADDR3_STR;
    volatile unsigned int           MST_VEDU_STRMADDR4_STR;
    volatile unsigned int           MST_VEDU_STRMADDR5_STR;
    volatile unsigned int           MST_VEDU_STRMADDR6_STR;
    volatile unsigned int           MST_VEDU_STRMADDR7_STR;
    volatile unsigned int           MST_VEDU_STRMADDR8_STR;
    volatile unsigned int           MST_VEDU_STRMADDR9_STR;
    volatile unsigned int           MST_VEDU_STRMADDR10_STR;
    volatile unsigned int           MST_VEDU_STRMADDR11_STR;
    volatile unsigned int           MST_VEDU_STRMADDR12_STR;
    volatile unsigned int           MST_VEDU_STRMADDR13_STR;
    volatile unsigned int           MST_VEDU_STRMADDR14_STR;
    volatile unsigned int           MST_VEDU_STRMADDR15_STR;
    volatile unsigned int           MST_VEDU_STRMADDR0_END;
    volatile unsigned int           MST_VEDU_STRMADDR1_END;
    volatile unsigned int           MST_VEDU_STRMADDR2_END;
    volatile unsigned int           MST_VEDU_STRMADDR3_END;
    volatile unsigned int           MST_VEDU_STRMADDR4_END;
    volatile unsigned int           MST_VEDU_STRMADDR5_END;
    volatile unsigned int           MST_VEDU_STRMADDR6_END;
    volatile unsigned int           MST_VEDU_STRMADDR7_END;
    volatile unsigned int           MST_VEDU_STRMADDR8_END;
    volatile unsigned int           MST_VEDU_STRMADDR9_END;
    volatile unsigned int           MST_VEDU_STRMADDR10_END;
    volatile unsigned int           MST_VEDU_STRMADDR11_END;
    volatile unsigned int           MST_VEDU_STRMADDR12_END;
    volatile unsigned int           MST_VEDU_STRMADDR13_END;
    volatile unsigned int           MST_VEDU_STRMADDR14_END;
    volatile unsigned int           MST_VEDU_STRMADDR15_END;
    volatile unsigned int           RESERVED_3[32];

} S_mmu1_REGS_TYPE;









/*--------------axidfx       start 0x20624200--------------------*/ 
/* Define the union U_DFX_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_ar_r_err          : 1   ; /* [0]  */
        unsigned int    dfx_aw_w_err          : 1   ; /* [1]  */
        unsigned int    dfx_aw_b_err          : 1   ; /* [2]  */
        unsigned int    dfx_arid_err          : 1   ; /* [3]  */
        unsigned int    dfx_rid_err           : 1   ; /* [4]  */
        unsigned int    dfx_awid_err          : 1   ; /* [5]  */
        unsigned int    dfx_wid_err           : 1   ; /* [6]  */
        unsigned int    dfx_bid_err           : 1   ; /* [7]  */
        unsigned int    dfx_arid_tx_err       : 1   ; /* [8]  */
        unsigned int    dfx_rid_rx_err        : 1   ; /* [9]  */
        unsigned int    dfx_awid_tx_err       : 1   ; /* [10]  */
        unsigned int    dfx_bid_rx_err        : 1   ; /* [11]  */
        unsigned int    dfx_arid_len_err      : 1   ; /* [12]  */
        unsigned int    dfx_awid_len          : 1   ; /* [13]  */
        unsigned int    dfx_rresp_err         : 1   ; /* [14]  */
        unsigned int    dfx_bresp_err         : 1   ; /* [15]  */
        unsigned int    dfx_ar_ovr_err        : 1   ; /* [16]  */
        unsigned int    dfx_r_ovr_err         : 1   ; /* [17]  */
        unsigned int    dfx_aw_ovr_err        : 1   ; /* [18]  */
        unsigned int    dfx_w_ovr_err         : 1   ; /* [19]  */
        unsigned int    dfx_b_ovr_err         : 1   ; /* [20]  */
        unsigned int    dfx_ar_outstanding_err : 1   ; /* [21]  */
        unsigned int    dfx_aw_outstanding_err : 1   ; /* [22]  */
        unsigned int    dfx_arlen_err         : 1   ; /* [23]  */
        unsigned int    dfx_awlen_err         : 1   ; /* [24]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR;

/* Define the union U_DFX_AR_R_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ar_r_cnt              : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_AR_R_CNT;

/* Define the union U_DFX_AW_W_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aw_w_cnt              : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_AW_W_CNT;

/* Define the union U_DFX_AW_B_CNT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aw_b_cnt              : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_AW_B_CNT;

/* Define the union U_dfx_AR_R_ID_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid_err          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    dfx_rid_err           : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_dfx_AR_R_ID_ERR;

/* Define the union U_DFX_ERR_ARID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_arid          : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_ARID;

/* Define the union U_DFX_ERR_RID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_rid           : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_RID;

/* Define the union U_dfx_AW_W_B_ID_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_awid_err          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    dfx_wid_err           : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    dfx_bid_err           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_dfx_AW_W_B_ID_ERR;

/* Define the union U_DFX_ERR_AWID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_awid          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_AWID;

/* Define the union U_DFX_ERR_WID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_wid           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_WID;

/* Define the union U_DFX_ERR_BID */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_bid           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_BID;

/* Define the union U_DFX_ARID_TX_0ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid0_tx_err      : 1   ; /* [0]  */
        unsigned int    dfx_arid1_tx_err      : 1   ; /* [1]  */
        unsigned int    dfx_arid2_tx_err      : 1   ; /* [2]  */
        unsigned int    dfx_arid3_tx_err      : 1   ; /* [3]  */
        unsigned int    dfx_arid4_tx_err      : 1   ; /* [4]  */
        unsigned int    dfx_arid5_tx_err      : 1   ; /* [5]  */
        unsigned int    dfx_arid6_tx_err      : 1   ; /* [6]  */
        unsigned int    dfx_arid7_tx_err      : 1   ; /* [7]  */
        unsigned int    dfx_arid8_tx_err      : 1   ; /* [8]  */
        unsigned int    dfx_arid9_tx_err      : 1   ; /* [9]  */
        unsigned int    dfx_arid10_tx_err     : 1   ; /* [10]  */
        unsigned int    dfx_arid11_tx_err     : 1   ; /* [11]  */
        unsigned int    dfx_arid12_tx_err     : 1   ; /* [12]  */
        unsigned int    dfx_arid13_tx_err     : 1   ; /* [13]  */
        unsigned int    dfx_arid14_tx_err     : 1   ; /* [14]  */
        unsigned int    dfx_arid15_tx_err     : 1   ; /* [15]  */
        unsigned int    dfx_arid16_tx_err     : 1   ; /* [16]  */
        unsigned int    dfx_arid17_tx_err     : 1   ; /* [17]  */
        unsigned int    dfx_arid18_tx_err     : 1   ; /* [18]  */
        unsigned int    dfx_arid19_tx_err     : 1   ; /* [19]  */
        unsigned int    dfx_arid20_tx_err     : 1   ; /* [20]  */
        unsigned int    dfx_arid21_tx_err     : 1   ; /* [21]  */
        unsigned int    dfx_arid22_tx_err     : 1   ; /* [22]  */
        unsigned int    dfx_arid23_tx_err     : 1   ; /* [23]  */
        unsigned int    dfx_arid24_tx_err     : 1   ; /* [24]  */
        unsigned int    dfx_arid25_tx_err     : 1   ; /* [25]  */
        unsigned int    dfx_arid26_tx_err     : 1   ; /* [26]  */
        unsigned int    dfx_arid27_tx_err     : 1   ; /* [27]  */
        unsigned int    dfx_arid28_tx_err     : 1   ; /* [28]  */
        unsigned int    dfx_arid29_tx_err     : 1   ; /* [29]  */
        unsigned int    dfx_arid30_tx_err     : 1   ; /* [30]  */
        unsigned int    dfx_arid31_tx_err     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_TX_0ERR;

/* Define the union U_DFX_ARID_TX_1ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid32_tx_err     : 1   ; /* [0]  */
        unsigned int    dfx_arid33_tx_err     : 1   ; /* [1]  */
        unsigned int    dfx_arid34_tx_err     : 1   ; /* [2]  */
        unsigned int    dfx_arid35_tx_err     : 1   ; /* [3]  */
        unsigned int    dfx_arid36_tx_err     : 1   ; /* [4]  */
        unsigned int    dfx_arid37_tx_err     : 1   ; /* [5]  */
        unsigned int    dfx_arid38_tx_err     : 1   ; /* [6]  */
        unsigned int    dfx_arid39_tx_err     : 1   ; /* [7]  */
        unsigned int    dfx_arid40_tx_err     : 1   ; /* [8]  */
        unsigned int    dfx_arid41_tx_err     : 1   ; /* [9]  */
        unsigned int    dfx_arid42_tx_err     : 1   ; /* [10]  */
        unsigned int    dfx_arid43_tx_err     : 1   ; /* [11]  */
        unsigned int    dfx_arid44_tx_err     : 1   ; /* [12]  */
        unsigned int    dfx_arid45_tx_err     : 1   ; /* [13]  */
        unsigned int    dfx_arid46_tx_err     : 1   ; /* [14]  */
        unsigned int    dfx_arid47_tx_err     : 1   ; /* [15]  */
        unsigned int    dfx_arid48_tx_err     : 1   ; /* [16]  */
        unsigned int    dfx_arid49_tx_err     : 1   ; /* [17]  */
        unsigned int    dfx_arid50_tx_err     : 1   ; /* [18]  */
        unsigned int    dfx_arid51_tx_err     : 1   ; /* [19]  */
        unsigned int    dfx_arid52_tx_err     : 1   ; /* [20]  */
        unsigned int    dfx_arid53_tx_err     : 1   ; /* [21]  */
        unsigned int    dfx_arid54_tx_err     : 1   ; /* [22]  */
        unsigned int    dfx_arid55_tx_err     : 1   ; /* [23]  */
        unsigned int    dfx_arid56_tx_err     : 1   ; /* [24]  */
        unsigned int    dfx_arid57_tx_err     : 1   ; /* [25]  */
        unsigned int    dfx_arid58_tx_err     : 1   ; /* [26]  */
        unsigned int    dfx_arid59_tx_err     : 1   ; /* [27]  */
        unsigned int    dfx_arid60_tx_err     : 1   ; /* [28]  */
        unsigned int    dfx_arid61_tx_err     : 1   ; /* [29]  */
        unsigned int    dfx_arid62_tx_err     : 1   ; /* [30]  */
        unsigned int    dfx_arid63_tx_err     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_TX_1ERR;

/* Define the union U_DFX_ARID_TX_2ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid64_tx_err     : 1   ; /* [0]  */
        unsigned int    dfx_arid65_tx_err     : 1   ; /* [1]  */
        unsigned int    dfx_arid66_tx_err     : 1   ; /* [2]  */
        unsigned int    dfx_arid67_tx_err     : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_TX_2ERR;

/* Define the union U_DFX_RID_RX_0ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_rid0_rx_err       : 1   ; /* [0]  */
        unsigned int    dfx_rid1_rx_err       : 1   ; /* [1]  */
        unsigned int    dfx_rid2_rx_err       : 1   ; /* [2]  */
        unsigned int    dfx_rid3_rx_err       : 1   ; /* [3]  */
        unsigned int    dfx_rid4_rx_err       : 1   ; /* [4]  */
        unsigned int    dfx_rid5_rx_err       : 1   ; /* [5]  */
        unsigned int    dfx_rid6_rx_err       : 1   ; /* [6]  */
        unsigned int    dfx_rid7_rx_err       : 1   ; /* [7]  */
        unsigned int    dfx_rid8_rx_err       : 1   ; /* [8]  */
        unsigned int    dfx_rid9_rx_err       : 1   ; /* [9]  */
        unsigned int    dfx_rid10_rx_err      : 1   ; /* [10]  */
        unsigned int    dfx_rid11_rx_err      : 1   ; /* [11]  */
        unsigned int    dfx_rid12_rx_err      : 1   ; /* [12]  */
        unsigned int    dfx_rid13_rx_err      : 1   ; /* [13]  */
        unsigned int    dfx_rid14_rx_err      : 1   ; /* [14]  */
        unsigned int    dfx_rid15_rx_err      : 1   ; /* [15]  */
        unsigned int    dfx_rid16_rx_err      : 1   ; /* [16]  */
        unsigned int    dfx_rid17_rx_err      : 1   ; /* [17]  */
        unsigned int    dfx_rid18_rx_err      : 1   ; /* [18]  */
        unsigned int    dfx_rid19_rx_err      : 1   ; /* [19]  */
        unsigned int    dfx_rid20_rx_err      : 1   ; /* [20]  */
        unsigned int    dfx_rid21_rx_err      : 1   ; /* [21]  */
        unsigned int    dfx_rid22_rx_err      : 1   ; /* [22]  */
        unsigned int    dfx_rid23_rx_err      : 1   ; /* [23]  */
        unsigned int    dfx_rid24_rx_err      : 1   ; /* [24]  */
        unsigned int    dfx_rid25_rx_err      : 1   ; /* [25]  */
        unsigned int    dfx_rid26_rx_err      : 1   ; /* [26]  */
        unsigned int    dfx_rid27_rx_err      : 1   ; /* [27]  */
        unsigned int    dfx_rid28_rx_err      : 1   ; /* [28]  */
        unsigned int    dfx_rid29_rx_err      : 1   ; /* [29]  */
        unsigned int    dfx_rid30_rx_err      : 1   ; /* [30]  */
        unsigned int    dfx_rid31_rx_err      : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_RID_RX_0ERR;

/* Define the union U_DFX_RID_RX_1ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_rid32_rx_err      : 1   ; /* [0]  */
        unsigned int    dfx_rid33_rx_err      : 1   ; /* [1]  */
        unsigned int    dfx_rid34_rx_err      : 1   ; /* [2]  */
        unsigned int    dfx_rid35_rx_err      : 1   ; /* [3]  */
        unsigned int    dfx_rid36_rx_err      : 1   ; /* [4]  */
        unsigned int    dfx_rid37_rx_err      : 1   ; /* [5]  */
        unsigned int    dfx_rid38_rx_err      : 1   ; /* [6]  */
        unsigned int    dfx_rid39_rx_err      : 1   ; /* [7]  */
        unsigned int    dfx_rid40_rx_err      : 1   ; /* [8]  */
        unsigned int    dfx_rid41_rx_err      : 1   ; /* [9]  */
        unsigned int    dfx_rid42_rx_err      : 1   ; /* [10]  */
        unsigned int    dfx_rid43_rx_err      : 1   ; /* [11]  */
        unsigned int    dfx_rid44_rx_err      : 1   ; /* [12]  */
        unsigned int    dfx_rid45_rx_err      : 1   ; /* [13]  */
        unsigned int    dfx_rid46_rx_err      : 1   ; /* [14]  */
        unsigned int    dfx_rid47_rx_err      : 1   ; /* [15]  */
        unsigned int    dfx_rid48_rx_err      : 1   ; /* [16]  */
        unsigned int    dfx_rid49_rx_err      : 1   ; /* [17]  */
        unsigned int    dfx_rid50_rx_err      : 1   ; /* [18]  */
        unsigned int    dfx_rid51_rx_err      : 1   ; /* [19]  */
        unsigned int    dfx_rid52_rx_err      : 1   ; /* [20]  */
        unsigned int    dfx_rid53_rx_err      : 1   ; /* [21]  */
        unsigned int    dfx_rid54_rx_err      : 1   ; /* [22]  */
        unsigned int    dfx_rid55_rx_err      : 1   ; /* [23]  */
        unsigned int    dfx_rid56_rx_err      : 1   ; /* [24]  */
        unsigned int    dfx_rid57_rx_err      : 1   ; /* [25]  */
        unsigned int    dfx_rid58_rx_err      : 1   ; /* [26]  */
        unsigned int    dfx_rid59_rx_err      : 1   ; /* [27]  */
        unsigned int    dfx_rid60_rx_err      : 1   ; /* [28]  */
        unsigned int    dfx_rid61_rx_err      : 1   ; /* [29]  */
        unsigned int    dfx_rid62_rx_err      : 1   ; /* [30]  */
        unsigned int    dfx_rid63_rx_err      : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_RID_RX_1ERR;

/* Define the union U_DFX_RID_RX_2ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_rid64_rx_err      : 1   ; /* [0]  */
        unsigned int    dfx_rid65_rx_err      : 1   ; /* [1]  */
        unsigned int    dfx_rid66_rx_err      : 1   ; /* [2]  */
        unsigned int    dfx_rid67_rx_err      : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_RID_RX_2ERR;

/* Define the union U_DFX_ARID_RX_0ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_awid0_rx_err      : 1   ; /* [0]  */
        unsigned int    dfx_awid1_rx_err      : 1   ; /* [1]  */
        unsigned int    dfx_awid2_rx_err      : 1   ; /* [2]  */
        unsigned int    dfx_awid3_rx_err      : 1   ; /* [3]  */
        unsigned int    dfx_awid4_rx_err      : 1   ; /* [4]  */
        unsigned int    dfx_awid5_rx_err      : 1   ; /* [5]  */
        unsigned int    dfx_awid6_rx_err      : 1   ; /* [6]  */
        unsigned int    dfx_awid7_rx_err      : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_RX_0ERR;

/* Define the union U_DFX_BID_RX_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_bid0_rx_err       : 1   ; /* [0]  */
        unsigned int    dfx_bid1_rx_err       : 1   ; /* [1]  */
        unsigned int    dfx_bid2_rx_err       : 1   ; /* [2]  */
        unsigned int    dfx_bid3_rx_err       : 1   ; /* [3]  */
        unsigned int    dfx_bid4_rx_err       : 1   ; /* [4]  */
        unsigned int    dfx_bid5_rx_err       : 1   ; /* [5]  */
        unsigned int    dfx_bid6_rx_err       : 1   ; /* [6]  */
        unsigned int    dfx_bid7_rx_err       : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_BID_RX_ERR;

/* Define the union U_DFX_ARID_LEN_0ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid0_len_err     : 1   ; /* [0]  */
        unsigned int    dfx_arid1_len_err     : 1   ; /* [1]  */
        unsigned int    dfx_arid2_len_err     : 1   ; /* [2]  */
        unsigned int    dfx_arid3_len_err     : 1   ; /* [3]  */
        unsigned int    dfx_arid4_len_err     : 1   ; /* [4]  */
        unsigned int    dfx_arid5_len_err     : 1   ; /* [5]  */
        unsigned int    dfx_arid6_len_err     : 1   ; /* [6]  */
        unsigned int    dfx_arid7_len_err     : 1   ; /* [7]  */
        unsigned int    dfx_arid8_len_err     : 1   ; /* [8]  */
        unsigned int    dfx_arid9_len_err     : 1   ; /* [9]  */
        unsigned int    dfx_arid10_len_err    : 1   ; /* [10]  */
        unsigned int    dfx_arid11_len_err    : 1   ; /* [11]  */
        unsigned int    dfx_arid12_len_err    : 1   ; /* [12]  */
        unsigned int    dfx_arid13_len_err    : 1   ; /* [13]  */
        unsigned int    dfx_arid14_len_err    : 1   ; /* [14]  */
        unsigned int    dfx_arid15_len_err    : 1   ; /* [15]  */
        unsigned int    dfx_arid16_len_err    : 1   ; /* [16]  */
        unsigned int    dfx_arid17_len_err    : 1   ; /* [17]  */
        unsigned int    dfx_arid18_len_err    : 1   ; /* [18]  */
        unsigned int    dfx_arid19_len_err    : 1   ; /* [19]  */
        unsigned int    dfx_arid20_len_err    : 1   ; /* [20]  */
        unsigned int    dfx_arid21_len_err    : 1   ; /* [21]  */
        unsigned int    dfx_arid22_len_err    : 1   ; /* [22]  */
        unsigned int    dfx_arid23_len_err    : 1   ; /* [23]  */
        unsigned int    dfx_arid24_len_err    : 1   ; /* [24]  */
        unsigned int    dfx_arid25_len_err    : 1   ; /* [25]  */
        unsigned int    dfx_arid26_len_err    : 1   ; /* [26]  */
        unsigned int    dfx_arid27_len_err    : 1   ; /* [27]  */
        unsigned int    dfx_arid28_len_err    : 1   ; /* [28]  */
        unsigned int    dfx_arid29_len_err    : 1   ; /* [29]  */
        unsigned int    dfx_arid30_len_err    : 1   ; /* [30]  */
        unsigned int    dfx_arid31_len_err    : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_LEN_0ERR;

/* Define the union U_DFX_ARID_LEN_1ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid32_len_err    : 1   ; /* [0]  */
        unsigned int    dfx_arid33_len_err    : 1   ; /* [1]  */
        unsigned int    dfx_arid34_len_err    : 1   ; /* [2]  */
        unsigned int    dfx_arid35_len_err    : 1   ; /* [3]  */
        unsigned int    dfx_arid36_len_err    : 1   ; /* [4]  */
        unsigned int    dfx_arid37_len_err    : 1   ; /* [5]  */
        unsigned int    dfx_arid38_len_err    : 1   ; /* [6]  */
        unsigned int    dfx_arid39_len_err    : 1   ; /* [7]  */
        unsigned int    dfx_arid40_len_err    : 1   ; /* [8]  */
        unsigned int    dfx_arid41_len_err    : 1   ; /* [9]  */
        unsigned int    dfx_arid42_len_err    : 1   ; /* [10]  */
        unsigned int    dfx_arid43_len_err    : 1   ; /* [11]  */
        unsigned int    dfx_arid44_len_err    : 1   ; /* [12]  */
        unsigned int    dfx_arid45_len_err    : 1   ; /* [13]  */
        unsigned int    dfx_arid46_len_err    : 1   ; /* [14]  */
        unsigned int    dfx_arid47_len_err    : 1   ; /* [15]  */
        unsigned int    dfx_arid48_len_err    : 1   ; /* [16]  */
        unsigned int    dfx_arid49_len_err    : 1   ; /* [17]  */
        unsigned int    dfx_arid50_len_err    : 1   ; /* [18]  */
        unsigned int    dfx_arid51_len_err    : 1   ; /* [19]  */
        unsigned int    dfx_arid52_len_err    : 1   ; /* [20]  */
        unsigned int    dfx_arid53_len_err    : 1   ; /* [21]  */
        unsigned int    dfx_arid54_len_err    : 1   ; /* [22]  */
        unsigned int    dfx_arid55_len_err    : 1   ; /* [23]  */
        unsigned int    dfx_arid56_len_err    : 1   ; /* [24]  */
        unsigned int    dfx_arid57_len_err    : 1   ; /* [25]  */
        unsigned int    dfx_arid58_len_err    : 1   ; /* [26]  */
        unsigned int    dfx_arid59_len_err    : 1   ; /* [27]  */
        unsigned int    dfx_arid60_len_err    : 1   ; /* [28]  */
        unsigned int    dfx_arid61_len_err    : 1   ; /* [29]  */
        unsigned int    dfx_arid62_len_err    : 1   ; /* [30]  */
        unsigned int    dfx_arid63_len_err    : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_LEN_1ERR;

/* Define the union U_DFX_ARID_LEN_2ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arid64_len_err    : 1   ; /* [0]  */
        unsigned int    dfx_arid65_len_err    : 1   ; /* [1]  */
        unsigned int    dfx_arid66_len_err    : 1   ; /* [2]  */
        unsigned int    dfx_arid67_len_err    : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ARID_LEN_2ERR;

/* Define the union U_DFX_RESP_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_rresp_err         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    dfx_bresp_err         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_RESP_ERR;

/* Define the union U_DFX_ERR_RESP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_rresp         : 2   ; /* [1..0]  */
        unsigned int    dfx_err_bresp         : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_RESP;

/* Define the union U_DFX_LEN_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_arlen_err         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    dfx_awlen_err         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_LEN_ERR;

/* Define the union U_DFX_ERR_LEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dfx_err_arlen         : 4   ; /* [3..0]  */
        unsigned int    dfx_err_awlen         : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DFX_ERR_LEN;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_DFX_ERR              DFX_ERR;
    volatile unsigned int           RESERVED_1[3];
    volatile U_DFX_AR_R_CNT         DFX_AR_R_CNT;
    volatile U_DFX_AW_W_CNT         DFX_AW_W_CNT;
    volatile U_DFX_AW_B_CNT         DFX_AW_B_CNT;
    volatile unsigned int           RESERVED_2;
    volatile U_dfx_AR_R_ID_ERR      dfx_AR_R_ID_ERR;
    volatile U_DFX_ERR_ARID         DFX_ERR_ARID;
    volatile U_DFX_ERR_RID          DFX_ERR_RID;
    volatile unsigned int           RESERVED_3;
    volatile U_dfx_AW_W_B_ID_ERR    dfx_AW_W_B_ID_ERR;
    volatile U_DFX_ERR_AWID         DFX_ERR_AWID;
    volatile U_DFX_ERR_WID          DFX_ERR_WID;
    volatile U_DFX_ERR_BID          DFX_ERR_BID;
    volatile U_DFX_ARID_TX_0ERR     DFX_ARID_TX_0ERR;
    volatile U_DFX_ARID_TX_1ERR     DFX_ARID_TX_1ERR;
    volatile U_DFX_ARID_TX_2ERR     DFX_ARID_TX_2ERR;
    volatile unsigned int           RESERVED_4;
    volatile U_DFX_RID_RX_0ERR      DFX_RID_RX_0ERR;
    volatile U_DFX_RID_RX_1ERR      DFX_RID_RX_1ERR;
    volatile U_DFX_RID_RX_2ERR      DFX_RID_RX_2ERR;
    volatile unsigned int           RESERVED_5;
    volatile U_DFX_ARID_RX_0ERR     DFX_ARID_RX_0ERR;
    volatile U_DFX_BID_RX_ERR       DFX_BID_RX_ERR;
    volatile unsigned int           RESERVED_6[2];
    volatile U_DFX_ARID_LEN_0ERR    DFX_ARID_LEN_0ERR;
    volatile U_DFX_ARID_LEN_1ERR    DFX_ARID_LEN_1ERR;
    volatile U_DFX_ARID_LEN_2ERR    DFX_ARID_LEN_2ERR;
    volatile unsigned int           RESERVED_7;
    volatile unsigned int           DFX_AWLEN_CNT;
    volatile unsigned int           DFX_WLEN_CNT;
    volatile unsigned int           RESERVED_8[2];
    volatile U_DFX_RESP_ERR         DFX_RESP_ERR;
    volatile U_DFX_ERR_RESP         DFX_ERR_RESP;
    volatile U_DFX_LEN_ERR          DFX_LEN_ERR;
    volatile U_DFX_ERR_LEN          DFX_ERR_LEN;
    volatile unsigned int           RESERVED_9[88];

} S_axidfx_REGS_TYPE;
typedef struct
{ 
    /* Vcpi寄存器结构体   0x20620000  */
    volatile S_vcpi_REGS_TYPE   VEDU_VCPI_REGS;
    
    /* Vctrl寄存器结构体   0x20620200  */
    volatile S_vctrl_REGS_TYPE  VEDU_VCTRL_REGS;
    
    /* Curld寄存器结构体   0x20620400  */
    volatile S_curld_REGS_TYPE  VEDU_CURID_REGS;
    
    /* Pme寄存器结构体    0x20620600  */
    volatile S_pme_REGS_TYPE  VEDU_PME_REGS;
    
    /* Refid寄存器结构体   0x20620800  */
    volatile S_refld_REGS_TYPE VEDU_REFID_REGS;
    
    /* Ime寄存器结构体   0x20620a00  */
    volatile S_ime_REGS_TYPE VEDU_IME_REGS;
    
    /* Qpg寄存器结构体   0x20620c00  */
    volatile S_qpg_REGS_TYPE VEDU_QPG_REGS;
    
    /* Mrg寄存器结构体   0x20620e00  */
    volatile S_mrg_REGS_TYPE VEDU_MRG_REGS;
    
    /* Fme寄存器结构体   0x20621000  */
    volatile S_fme_REGS_TYPE VEDU_FME_REGS;
    
    /* Intra寄存器结构体   0x20621200  */
    volatile S_intra_REGS_TYPE VEDU_INTRA_REGS;
    
    /* Pmv寄存器结构体   0x20621400  */
    volatile S_pmv_REGS_TYPE VEDU_PMV_REGS;

    /* Tqitq寄存器结构体   0x20621600  */
     volatile S_tqitq_REGS_TYPE VEDU_TQITQ_REGS;   
       
    /* Sel寄存器结构体   0x20621800  */
    volatile S_sel_REGS_TYPE  VEDU_SEL_REGS;   
          
    /* Dblk寄存器结构体   0x20621a00  */
    volatile S_dblk_REGS_TYPE  VEDU_DBLK_REGS;   
     
    /* Sao寄存器结构体   0x20621c00  */
    volatile S_sao_REGS_TYPE  VEDU_SAO_REGS; 
    
    /* Pack寄存器结构体   0x20621e00  */
    volatile S_pack_REGS_TYPE  VEDU_PACK_REGS;     
      
    /* Cabac寄存器结构体   0x20622000  */
    volatile S_cabac_REGS_TYPE  VEDU_CABAC_REGS;     

    /* Pmeld寄存器结构体   0x20622200  */
    volatile S_pmeld_REGS_TYPE  VEDU_PMEID_REGS;  
   
    /* Pmest寄存器结构体   0x20622400  */ 
    volatile S_pmest_REGS_TYPE  VEDU_PMEST_REGS;
    
    /* nbi寄存器结构体   0x20622600  */
    volatile S_nbi_REGS_TYPE  VEDU_NBI_REGS;
    
    /* unvld寄存器结构体   0x20622800  */
    volatile S_unvld_REGS_TYPE  VEDU_UNVLD_REGS;
  
    /* recst寄存器结构体   0x20622a00  */
    volatile S_recst_REGS_TYPE  VEDU_RECST_REGS;
     
    /* vlcst 寄存器结构体   0x20622c00  */
    volatile S_vlcst_REGS_TYPE  VEDU_VLCST_REGS;
         
    /* vlc  寄存器结构体   0x20622e00  */       
    volatile S_vlc_REGS_TYPE  VEDU_VLC_REGS;

    /* Curpre  寄存器结构体   0x20623000  */
    volatile S_curpre_REGS_TYPE  VEDU_CURPRE_REGS;

    /* Imeld  寄存器结构体   0x20623200  */
    volatile S_imeld_REGS_TYPE  VEDU_IMEID_REGS;    
    
    /* Emar  寄存器结构体   0x20623400  */
    volatile S_emar_REGS_TYPE  VEDU_EMAR_REGS;
    
    /* Comn0  寄存器结构体   0x20623600  */
    volatile  S_comn0_REGS_TYPE VEDU_COMN0_REGS;
    
    /* Comn1  寄存器结构体   0x20623800  */
    volatile  S_comn1_REGS_TYPE VEDU_COMN1_REGS;
    
    /* Comn2  寄存器结构体   0x20623a00  */
    volatile  S_comn2_REGS_TYPE  VEDU_COMN2_REGS;

    /* Comn3  寄存器结构体   0x20623c00  */
    volatile  S_comn3_REGS_TYPE  VEDU_COMN3_REGS;
    
    /* mmu0  寄存器结构体   0x20623e00  */
    volatile  S_mmu0_REGS_TYPE VEDU_MMU0_REGS;

    /* mmu1  寄存器结构体   0x20624000  */
    volatile  S_mmu1_REGS_TYPE VEDU_MMU1_REGS;

    /* axidfx  寄存器结构体   0x20624200  */
    volatile  S_axidfx_REGS_TYPE VEDU_AXIDFX_REGS;
}S_HEVC_AVC_REGS_TYPE;

#endif
 















