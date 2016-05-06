
#ifndef _VDM_HAL_V400R004_LOCAL_HEADER_
#define _VDM_HAL_V400R004_LOCAL_HEADER_


#include "basedef.h"
#include "mem_manage.h"
#include "vfmw.h"
#include "vdm_hal.h"

#ifdef _cplusplus
extern "C" {
#endif

#define    VHB_V400R004_STRIDE_BYTE             (0x400)                      // byte stride
#define    VHB_V400R004_STRIDE_WORD             (VHB_V400R004_STRIDE_BYTE/4) // word stride
#define    SLOT_V400R004_WIDTH_BYTE             (64)                         // 64 byte
#define    SLOT_V400R004_WIDTH_WORD             (SLOT_V400R004_WIDTH_BYTE/4) // 16 word
#define    HALF_V400R004_SLOT_WIDTH_WORD        (8)                          // 8 word
#define    MSG_V400R004_SLOT_HEIGHT_BYTE        (32*1024)                    // one slot height
#define    HW_V400R004_MEM_SIZE                 (640*1024)
#define    HW_V400R004_HEVC_MEM_SIZE            (2*1024*1024)//(4*1024*1024 + 100*1024)

#define    MSG_V400R004_SLOT_NUM                (MAX_SLICE_SLOT_NUM + 5)
#define    UP_V400R004_MSG_SLOT_INDEX           (0)
#define    RP_V400R004_MSG_SLOT_INDEX           (2)
#define    DN_V400R004_MSG_SLOT_INDEX           (4)
#define    RP_V400R004_MSG_SLOT_NUM             (2)
#define    DN_V400R004_MSG_SLOT_NUM             (1)
#define    VDM_V400R004_REG_SIZE               	(1024)                                      //分配的寄存器大小
#define    RP_V400R004_MSG_SIZE                 (RP_V400R004_MSG_SLOT_NUM * MSG_SLOT_SIZE)  //分配的消息大小, WORD
#define    DN_V400R004_MSG_SIZE                 (DN_V400R004_MSG_SLOT_NUM * MSG_SLOT_SIZE)  //分配的消息大小, WORD
#define    VDM_V400R004_REG_USED_SIZE           (512)                                       //实际使用的寄存器大小, WORD
#define    RP_V400R004_MSG_USED_SIZE            (RP_V400R004_MSG_SIZE)                      //实际使用的消息大小, WORD
#define    CA_V400R004_HEVC_MN_ADDR_LEN         (1024)     //H265协议CA_MN可减为1K z00290437  20141016   
#define    CA_V400R004_MN_ADDR_LEN              (64*4*20)
#define    SED_V400R004_TOP_ADDR_LEN            (352*96)   //(64*4*96)
#define    PMV_V400R004_TOP_ADDR_LEN            (352*128)  //(64*4*96)
#define    RCN_V400R004_TOP_ADDR_LEN            (352*128)  //(64*4*96)
#define    ITRANS_V400R004_TOP_ADDR_LEN         (352*128)  //(128*128)
#define    DBLK_V400R004_TOP_ADDR_LEN           (352*192)  //(128*512)
#define    PPFD_V400R004_BUF_LEN_DEFAULT        (64*4*400) //(64*4*800)
#define    ONEMB_V400R004_PMV_COLMB_ADDR_LEN    (20*4)     //计算得知，大致需要16words/mb，现在多分配一点        

//db defines
#define    DB_V400R004_THR_LEASTBLKDIFF 		(0)        //key para, (0-128)
#define    DB_V400R004_ALPHA_SCALE 				(8)
#define    DB_V400R004_BETA_SCALE 				(8)

//EMAR_ID default value
#define    EMAR_ID_VALUE                        (0x161f7)

/************************************************************************/
/* VDM寄存器                                                            */
/************************************************************************/
//control registers
#define    VREG_V400R004_VDH_START                      0x000
#define    VREG_V400R004_VDH_REPAIR                     0x004
#define    VREG_V400R004_BASIC_CFG0                     0x008
#define    VREG_V400R004_BASIC_CFG1                     0x00c
#define    VREG_V400R004_AVM_ADDR                       0x010
#define    VREG_V400R004_VAM_ADDR                       0x014
#define    VREG_V400R004_STREAM_BASE_ADDR               0x018
//state registers
#define    VREG_V400R004_VDH_STATE                      0x01c
#define    VREG_V400R004_INT_STATE                      0x020
#define    VREG_V400R004_INT_MASK                       0x024
#define    VREG_V400R004_VCTRL_STATE                    0x028
//emar & timeout registers
#define    VREG_V400R004_EMAR_ID                        0x030    //0x0000FF00: no   RAM OnChip
//0x0001FF00: all  RAM OnChip
//0x0002FF00: all  RAM OnChip, except DBLK RAM
#define    VREG_V400R004_RPT_CNT                        0x034
#define    VREG_V400R004_VCTRL_TO                       0x038
#define    VREG_V400R004_SED_TO                         0x03c
#define    VREG_V400R004_ITRANS_TO                      0x040
#define    VREG_V400R004_PMV_TO                         0x044
#define    VREG_V400R004_PRC_TO                         0x048
#define    VREG_V400R004_RCN_TO                         0x04c
#define    VREG_V400R004_DBLK_TO                        0x050
#define    VREG_V400R004_PPFD_TO                        0x054
#define    VREG_V400R004_PART_DEC_OVER_INT_LEVEL        0x05c
//1d registers
#define    VREG_V400R004_YSTADDR_1D                     0x060
#define    VREG_V400R004_YSTRIDE_1D                     0x064
#define    VREG_V400R004_UVOFFSET_1D                    0x068
//prc registers
#define    VREG_V400R004_PRCNUM_1D_CNT                  0x06c
#define    VREG_V400R004_HEAD_INF_OFFSET                0x06c
#define    VREG_V400R004_PRCMEM1_1D_CNT                 0x070
#define    VREG_V400R004_LINE_NUM_STADDR                0x070
#define    VREG_V400R004_PRCMEM2_1D_CNT                 0x074
//ppfd registers
#define    VREG_V400R004_PPFD_BUF_ADDR                  0x080
#define    VREG_V400R004_PPFD_BUF_LEN                   0x084
#define    VREG_V400R004_REF_PIC_TYPE  					0x094
#define    VREG_V400R004_FF_APT_EN 						0x098
//clock switch registers
#define    VREG_V400R004_MFDE_CLK_EN                    0x09c
#define    MFDE_CLK_EN_DEFAULT_VALUE                    0xffffffff
#define    VREG_V400R004_CRG_CLK_EN                     0xf804
#define    CRG_CLK_EN_DEFAULT_VALUE                     0xffffffff
//performance count registers
#define    VREG_V400R004_DEC_CYCLEPERPIC                0x0B0
#define    VREG_V400R004_RD_BDWIDTH_PERPIC              0x0B4
#define    VREG_V400R004_WR_BDWIDTH_PERPIC              0x0B8
#define    VREG_V400R004_RD_REQ_PERPIC                  0x0BC
#define    VREG_V400R004_WR_REQ_PERPIC                  0x0C0
#define    VREG_V400R004_MB0_QP_IN_CURR_PIC        		0x0D0
#define    VREG_V400R004_SWITCH_ROUNDING        		0x0D4
//axi registers
#define    VREG_V400R004_AXI_TEST_ST                    0x0E0
#define    VREG_V400R004_AXI_TEST_MODE                  0x0E4
#define    VREG_V400R004_AXI_TEST_ADDR                  0x0E8
#define    VREG_V400R004_AXI_TEST_CMD                   0x0EC
#define    VREG_V400R004_AXI_TEST_STA                   0x0F0
#define    VREG_V400R004_AXI_TEST_RAM                   0x100  //0x100~0x13F
//rpr registers
#define    VREG_V400R004_RPR_START                      0x140
#define    VREG_V400R004_RPR_SRC_YSTADDR_1D             0x144
#define    VREG_V400R004_RPR_SRC_YSTRIDE_1D             0x148
#define    VREG_V400R004_RPR_SRC_UVOFFSET_1D            0x14c
#define    VREG_V400R004_RPR_SRC_WIDTH_HEIGHT           0x150
#define    VREG_V400R004_RPR_DST_YSTADDR_1D             0x154
#define    VREG_V400R004_RPR_DST_YSTRIDE_1D             0x158
#define    VREG_V400R004_RPR_DST_UVOFFSET_1D            0x15c
#define    VREG_V400R004_RPR_DST_WIDTH_HEIGHT           0x160
//sed registers
#define    VREG_V400R004_SED_STA                        0x1000
#define    VREG_V400R004_SED_END0                       0x1014
#define    VREG_V400R004_LUMA_HISTORGRAM                0x8100
#define    VREG_V400R004_LUMA_SUM_LOW                   0x8180
#define    VREG_V400R004_LUMA_SUM_HIGH                  0x8184
//avs_plus
#define    VREG_V400R004_AVSPLUS1                       0x7f0
#define    VREG_V400R004_AVSPLUS2                       0x70c

/* VDM寄存器位域定义 */
typedef struct
{
    USIGN dec_start:                            1;
    USIGN reserved:                             31;
} VDH_V400R004_START;

typedef struct
{
    USIGN repair_start:                         1;
    USIGN reserved:                             31;
} VDH_V400R004_REPAIR;

typedef struct
{
    USIGN mbamt_to_dec:                         20;
    USIGN memory_clock_gating_en:               1;
    USIGN module_clock_gating_en:               1;
    USIGN marker_bit_detect_en:                 1;
    USIGN ac_last_detect_en:                    1;
    USIGN coef_idx_detect_en:                   1;
    USIGN vop_type_detect_en:                   1;
    USIGN reserved:                             2;
    USIGN luma_sum_en:                          1;   //亮度像素和计算使能
    USIGN luma_historgam_en:                    1;   //亮度直方图计算使能
    USIGN load_qmatrix_flag:                    1;
    USIGN sec_mode_en:                          1;
} BASIC_V400R004_CFG0;

typedef struct
{
    USIGN mbamt_to_dec:                         20;
    USIGN memory_clock_gating_en:               1;
    USIGN module_clock_gating_en:               1;
    USIGN marker_bit_detect_en:                 1;
    USIGN ac_last_detect_en:                    1;
    USIGN coef_idx_detect_en:                   1;
    USIGN vop_type_detect_en:                   1;
    USIGN work_mode:							2;
    USIGN luma_sum_en:							1;
    USIGN luma_histogram_en:					1;
    USIGN load_qmatrix_flag:                    1;
    USIGN vdh_safe_flag:                        1;
} HEVC_BASIC_CFG0;

typedef struct
{
    USIGN video_standard:                       4;
    USIGN ddr_stride:                           9;
    USIGN uv_order_en:							1;
    USIGN fst_slc_grp:                          1;
    USIGN mv_output_en:                         1;
    USIGN max_slcgrp_num:                       12;
    USIGN line_num_output_en:                   1;
    USIGN vdh_2d_en:                            1;
    USIGN compress_en:                          1;
    USIGN ppfd_en:                              1;
} BASIC_V400R004_CFG1;

typedef struct
{
    USIGN video_standard:                       4;
    USIGN reserved:                           	9;
    USIGN uv_order_en:							1;
    USIGN fst_slc_grp:                          1;
    USIGN mv_output_en:                         1;
    USIGN max_slcgrp_num:                       12;
    USIGN line_num_output_en:                   1;
    USIGN vdh_2d_en:                           	1;
    USIGN frm_cmp_en:                          	1;
    USIGN ppfd_en:                              1;
} HEVC_BASIC_CFG1;

typedef struct
{
    USIGN av_msg_addr:                          32;
} AVM_V400R004_ADDR;

typedef struct
{
    USIGN va_msg_addr:                          32;
} VAM_V400R004_ADDR;

typedef struct
{
    USIGN stream_base_addr:                     32;
} STREAM_V400R004_BASE_ADDR;

typedef struct
{
    USIGN ystaddr_1d:                           32;
} YSTADDR_V400R004_1D;

typedef struct
{
    USIGN ystride_1d:                           32;
} YSTRIDE_V400R004_1D;

typedef struct
{
    USIGN uvoffset_1d:                          32;
} UVOFFSET_V400R004_1D;

typedef struct
{
    USIGN head_inf_offset:                      32;
} HEAD_V400R004_INF_OFFSET;

typedef struct
{
    USIGN ff_apt_en:                            1;
    USIGN reserved:                             31;
} FF_V400R004_APT_EN;

typedef struct
{
    USIGN ref_pic_type_0:                       2;
    USIGN ref_pic_type_1:                       2;
    USIGN ref_pic_type_2:                       2;
    USIGN ref_pic_type_3:                       2;
    USIGN ref_pic_type_4:                       2;
    USIGN ref_pic_type_5:                       2;
    USIGN ref_pic_type_6:                       2;
    USIGN ref_pic_type_7:                       2;

    USIGN ref_pic_type_8:                       2;
    USIGN ref_pic_type_9:                       2;
    USIGN ref_pic_type_10:                      2;
    USIGN ref_pic_type_11:                      2;
    USIGN ref_pic_type_12:                      2;
    USIGN ref_pic_type_13:                      2;
    USIGN ref_pic_type_14:                      2;
    USIGN ref_pic_type_15:                      2;
} REF_V400R004_PIC_TYPE;
typedef struct
{
    USIGN decoded_slice_num:                    17;
    USIGN intrs_vdh_dec_over:                   1;
    USIGN intrs_vdh_dec_err:                    1;
    USIGN version_id:                           8;
    USIGN reserved:                             5;
} VDH_V400R004_STATE;
typedef struct
{
    USIGN intrs_vdm_dec_over:                   1;
    USIGN intrs_vdm_dec_err:                    1;
    USIGN reserved:                             30;
} INT_V400R004_STATE;

typedef struct
{
    USIGN intrs_vdm_dec_over:                   1;
    USIGN intrs_vdm_dec_err:                    1;
    USIGN reserved:                             30;
} INT_V400R004_MASK;

typedef struct
{
    USIGN ppfd_buf_addr:                        32;
} PPFD_V400R004_BUF_ADDR;

typedef struct
{
    USIGN ppfd_buf_len:                         16;
    USIGN reserved:                             16;
} PPFD_V400R004_BUF_LEN;

//MPEG2修补消息池
typedef struct
{
    USIGN src_luma_addr:                        32;
} VDMRPMSG_V400R004_D0;

typedef struct
{
    USIGN src_chroma_addr:                      32;
} VDMRPMSG_V400R004_D1;

typedef struct
{
    USIGN dst_luma_addr:                        32;
} VDMRPMSG_V400R004_D2;

typedef struct
{
    USIGN dst_chroma_addr:                      32;
} VDMRPMSG_V400R004_D3;

typedef struct
{
    USIGN stride_1d:                            32;
} VDMRPMSG_V400R004_D4;
typedef struct
{
    USIGN headInfOffset:                        32;
} VDMRPMSG_V400R004_D5;
typedef struct
{
    USIGN pic_width_in_mb:                      9;
    USIGN reserved0:                            7;
    USIGN pic_height_in_mb:                     9;
    USIGN reserved1:                            7;
} VDMRPMSG_V400R004_D6;
typedef struct
{
    USIGN total_grp_num_minus1:                 16;
    USIGN compress_flag:                        1;
    USIGN reserved0:                            3;
    USIGN dst_store_mode:                       2;
    USIGN src_load_mode:                        2;
    USIGN ctb_size:								2;
    USIGN reserved1:                            8;

} VDMRPMSG_V400R004_D7;
typedef struct
{
    USIGN start_mbx:                            9;
    USIGN reserved0:                            7;
    USIGN start_mby:                            9;
    USIGN reserved1:                            7;
} VDMRPMSG_V400R004_D8;   // D0 in Burst1 (VDH)

typedef struct
{
    USIGN end_mbx:                              9;
    USIGN reserved0:                            7;
    USIGN end_mby:                              9;
    USIGN reserved1:                            7;
} VDMRPMSG_V400R004_D9;   // D1 in Burst1 (VDH)

typedef struct
{
    USIGN mbgrp_stuffing_type:                  2;
    USIGN reserved:                             30;
} VDMRPMSG_V400R004_D10;  // D2 in Burst1 (VDH)


#ifdef _cplusplus
}
#endif

#endif
