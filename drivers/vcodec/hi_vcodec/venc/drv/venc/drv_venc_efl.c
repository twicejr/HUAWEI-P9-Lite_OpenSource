#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_osal.h"
#include "hi_drv_mem.h"
#include "hal_venc.h"
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "hi_drv_venc.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))
#define ABS(x)            (( (x) <  0  ) ? -(x) : (x))
#define SIGN(a)           (( (a)<0 ) ? (-1) : (1))
#define MEDIAN(a, b, c)   ((a) + (b) + (c) - MIN((a), MIN((b), (c))) - MAX((a), MAX((b), (c))))
#define CLIP1(high, x)             (MAX( MIN((x), high), 0))
#define CLIP3(low, high, x)        (MAX( MIN(((HI_S32)x), (high)), (low)))

HI_U32 gVeduIrqNum = 0;
HI_U32 gMmuIrqNum = 0;
HI_U32 gVedusecIrqNum = 0;
HI_U32 gMmusecIrqNum = 0;
HI_U32 gVencRegBaseAddr = 0;
HI_U32 gVencRegRange = 0;
HI_U64 gSmmuPageBaseAddr = 0;
HI_U32 gVencIsFPGA = 0;

int scale_coef_table[16][32] =
{
{
-195, 4117, 232, -58,
-480, 3967, 814, -206,
-618, 3573, 1514, -373,
-622, 2981, 2265, -527,
-527, 2265, 2981, -622,
-373, 1514, 3573, -618,
-206, 814, 3967, -480,
-58, 232, 4117, -195,
},
{
  364, 3322, 770, -361,
  29, 3268, 1253, -455,
 -233, 3066, 1772, -509,
 -412, 2728, 2281, -501,
 -501, 2281, 2728, -412,
 -509, 1772, 3066, -233,
 -455, 1253, 3268, 29,
 -361, 770, 3322, 364,
},
{
713, 2748, 1039, -406,
417, 2686, 1385, -392,
156, 2544, 1729, -334,
-59, 2328, 2051, -224,
-224, 2051, 2328, -59,
-334, 1729, 2544, 156,
-392, 1385, 2686, 417,
-406, 1039, 2748, 713,
},
{
898, 2332, 1149, -284,
650, 2264, 1387, -206,
423, 2154, 1615, -96,
220, 2005, 1823, 46,
46, 1823, 2005, 220,
-96, 1615, 2154, 423,
-206, 1387, 2264, 650,
-284, 1149, 2332, 898,
},
{
990, 2036, 1183, -114,
784, 1972, 1350, -11,
592, 1884, 1506, 111,
414, 1776, 1650, 254,
254, 1650, 1776, 414,
111, 1506, 1884, 592,
-11, 1350, 1972, 784,
-114, 1183, 2036, 990,
},
{
1034, 1825, 1186, 49,
863, 1768, 1307, 156,
701, 1698, 1419, 276,
549, 1616, 1523, 407,
407, 1523, 1616, 549,
276, 1419, 1698, 701,
156, 1307, 1768, 863,
49, 1186, 1825, 1034,
},
{
1055, 1671, 1177, 191,
911, 1622, 1267, 294,
774, 1565, 1351, 403,
644, 1501, 1429, 520,
520, 1429, 1501, 644,
403, 1351, 1565, 774,
294, 1267, 1622, 911,
191, 1177, 1671, 1055,
},
{
1064, 1558, 1163, 309,
942, 1515, 1233, 403,
825, 1468, 1299, 502,
713, 1416, 1360, 605,
605, 1360, 1416, 713,
502, 1299, 1468, 825,
403, 1233, 1515, 942,
309, 1163, 1558, 1064,
},
{
1067, 1471, 1149, 407,
962, 1435, 1205, 492,
862, 1395, 1257, 580,
764, 1353, 1307, 670,
670, 1307, 1353, 764,
580, 1257, 1395, 862,
492, 1205, 1435, 962,
407, 1149, 1471, 1067,
},
{
1067, 1404, 1136, 487,
976, 1373, 1182, 563,
889, 1339, 1225, 641,
804, 1303, 1265, 722,
722, 1265, 1303, 804,
641, 1225, 1339, 889,
563, 1182, 1373, 976,
487, 1136, 1404, 1067,
},
{
1065, 1351, 1125, 553,
986, 1324, 1162, 621,
910, 1295, 1198, 691,
835, 1264, 1232, 762,
762, 1232, 1264, 835,
691, 1198, 1295, 910,
621, 1162, 1324, 986,
553, 1125, 1351, 1065,
},
{
1063, 1309, 1115, 608,
994, 1285, 1146, 670,
926, 1259, 1177, 732,
860, 1233, 1205, 795,
795, 1205, 1233, 860,
732, 1177, 1259, 926,
670, 1146, 1285, 994,
608, 1115, 1309, 1063,
},
{
1060, 1274, 1106, 654,
999, 1253, 1133, 710,
939, 1231, 1159, 766,
880, 1208, 1184, 823,
823, 1184, 1208, 880,
766, 1159, 1231, 939,
710, 1133, 1253, 999,
654, 1106, 1274, 1060,
},
{
1058, 1245, 1098, 693,
1003, 1226, 1121, 743,
949, 1207, 1144, 794,
897, 1187, 1166, 845,
845, 1166, 1187, 897,
794, 1144, 1207, 949,
743, 1121, 1226, 1003,
693, 1098, 1245, 1058,
},
{
1055, 1221, 1091, 727,
1006, 1204, 1111, 772,
958, 1187, 1131, 818,
911, 1169, 1150, 864,
864, 1150, 1169, 911,
818, 1131, 1187, 958,
772, 1111, 1204, 1006,
727, 1091, 1221, 1055,
},
{
1053, 1201, 1085, 755,
1009, 1186, 1103, 796,
965, 1170, 1121, 838,
922, 1154, 1138, 880,
880, 1138, 1154, 922,
838, 1121, 1170, 965,
796, 1103, 1186, 1009,
755, 1085, 1201, 1053,
}
};

#ifdef MD5_WC_EN
	HI_U8 *pMd5SrcY = NULL;
	HI_U8 *pMd5SrcU = NULL;
	HI_U8 *pMd5SrcV = NULL;
	HI_U8 *pMd5SrcUV = NULL;
	MD5Context context[8];
	struct file *fpmd5 = NULL;
#endif



enum {
	VENC_YUV_420	= 0,
	VENC_YUV_422	= 1,
	VENC_YUV_444	= 2,
	VENC_YUV_NONE	= 3
};

enum {
	VENC_V_U		= 0,
	VENC_U_V		= 1,
	VENC_A_R_G_B	= 2,
	VENC_R_G_B_A	= 3,
	VENC_A_B_G_R	= 4,
	VENC_B_G_R_A	= 5
};

enum {
	VENC_STORE_SEMIPLANNAR	= 0,
	VENC_STORE_PACKAGE		= 1,
	VENC_STORE_PLANNAR		= 2,
	VENC_STORE_RGB			= 3
};

enum {
	VENC_PACKAGE_UY0VY1 	= 141/*0b10001101*/,
	VENC_PACKAGE_Y0UY1V 	= 216/*0b11011000*/,
	VENC_PACKAGE_Y0VY1U 	= 120/*0b01111000*/,
	VENC_PACKAGE_VY0UY1 	= 121
};

enum {
	VENC_SEMIPLANNAR_420_UV  = 0,
	VENC_SEMIPLANNAR_420_VU  = 1,
	VENC_PLANNAR_420         = 2,
	VENC_PLANNAR_422         = 3,
	VENC_PACKAGE_422_YUYV    = 4,
	VENC_PACKAGE_422_UYVY    = 5,
	VENC_PACKAGE_422_YVYU    = 6,
	VENC_UNKNOW              = 7

};


#ifdef __VENC_DRV_DBG__

HI_U32 TmpTime_dbg[100][7] = {{0,0,0,0,0,0,0}};
HI_U32 Isr_ID = 0;
HI_U32 PutMsg_EBD_ID = 0;
HI_U32 PutMsg_FBD_ID = 0;
HI_U32 GetMsg_EBD_ID = 0;
HI_U32 GetMsg_FBD_ID = 0;
HI_BOOL flage_dbg = 1;

#endif

/*******************************************************************/

VeduEfl_ChnCtx_S VeduChnCtx[MAX_VEDU_CHN];

VeduEfl_IpCtx_S VeduIpCtx;

extern OPTM_VENC_CHN_S g_stVencChn[VENC_MAX_CHN_NUM];

extern spinlock_t g_SendFrame_Lock[VENC_MAX_CHN_NUM];     /*lock the destroy and send frame*/
VEDU_OSAL_EVENT g_VENC_Event;

extern HI_U32 g_stKernelVirAddr[6];

extern HI_S8 PriorityTab[2][MAX_VEDU_CHN];

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        u32VeChn = 0; \
        while (u32VeChn < MAX_VEDU_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_CHN_FROM_TAB(s32ChnID,TabNO)\
    do{  \
         s32ChnID = PriorityTab[0][TabNO];\
      } while (0)



static HI_VOID H264e_PutTrailingBits(tBitStream *pstBS)
{
    VENC_DRV_BsPutBits31(pstBS, 1, 1);

    if (pstBS->totalBits & 7)
    {
        VENC_DRV_BsPutBits31(pstBS, 0, 8 - (pstBS->totalBits & 7));
    }

    *pstBS->pBuff++ = (pstBS->bBigEndian ? pstBS->tU32b : REV32(pstBS->tU32b));
}

/*获取VPS语法信息*/
static HI_U32 H265e_MakeVPS(HI_U8 *pVPSBuf, const VeduEfl_H265e_VPS_S *pstVPS)
{
    HI_U32 code;
    int    bits;
    HI_U32 i = 0;
    tBitStream BS;
    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pVPSBuf);
    VENC_DRV_BsPutBits32(&BS, 1, 32);


    VENC_DRV_BsPutBits32(&BS, 0x4001, 16);
    //video_parameter_set_id = 0  u(4)
    VENC_DRV_BsPutBits32(&BS, 0, 4);
    //vps_reserved_three_2bits = 3  u(2)
    VENC_DRV_BsPutBits32(&BS, 3, 2);
	//vps_max_layers_minus1 = 0   u(6)
    VENC_DRV_BsPutBits32(&BS, pstVPS->uiMaxSubLayersMinus1, 6);
    //vps_max_sub_layers_minus1 = 0或1  u(3)   开大小P，取值为1；否则取值为0
    VENC_DRV_BsPutBits32(&BS, 0, 3);
    //vps_temporal_id_nesting_flag = 1 u(1)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
	//vps_reserved_ffff_16bits = 0xffff u(16)
    VENC_DRV_BsPutBits32(&BS, 0xffff, 16);
////////profile_tier_level
    {
        //general_profile_space=0  u(2)
        VENC_DRV_BsPutBits32(&BS, 0, 2);
        //general_tier_flag=0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
        //general_profile_idc =1   u(5)
        VENC_DRV_BsPutBits32(&BS, 1, 5);
        //general_profile_compatibility_flag[0]  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
        //general_profile_compatibility_flag[1]  u(1)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //general_profile_compatibility_flag[2]  u(1)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //PutBits32(&BS, 1, 1);
        for(i = 3; i<32;i++)//cjh  i=2会跟gc对不上 0701
	    {
	        //general_profile_compatibility_flag[][j]  u(1)
	        VENC_DRV_BsPutBits32(&BS, 0, 1);
	    }

	    //general_progressive_source_flag = 0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
	    //general_interlaced_source_flag = 0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
        //general_non_packed_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
         //general_frame_only_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
	    //general_reserved_zero_44bits[0..15] = 0  u(16)
        VENC_DRV_BsPutBits32(&BS, 0, 16);
        //general_reserved_zero_44bits[16..31] = 0  u(16)
        VENC_DRV_BsPutBits32(&BS, 0, 16);
	    //general_reserved_zero_44bits[32..43] = 0  u(12)
        VENC_DRV_BsPutBits32(&BS, 0, 12);
        //general_level_idc=0    u(8)
        VENC_DRV_BsPutBits32(&BS, 0, 8);
	    for(i = 0; i<pstVPS->uiMaxSubLayersMinus1;i++)
	    {
	    //sub_layer_profile_present_flag=0    u(1)
	        VENC_DRV_BsPutBits32(&BS, 0, 1);
            //sub_layer_level_present_flag=0    u(1)
            VENC_DRV_BsPutBits32(&BS, 0, 1);
	    }
	    if(pstVPS->uiMaxSubLayersMinus1 > 0)
	    {
	        for(i = pstVPS->uiMaxSubLayersMinus1;i < 8;i++)
	      	{
	      	    //reserved_zero_2bits = 0    u(2)
	      	    VENC_DRV_BsPutBits32(&BS, 0, 2);
	      	}
	    }
    }

    //vps_sub_layer_ordering_info_present_flag=1  u(1)
	VENC_DRV_BsPutBits32(&BS, 1, 1);
    for( i = 0; i <= (HI_U32)pstVPS->uiMaxSubLayersMinus1; i++ )
    {
        //vps_max_dec_pic_buffering_minus1[ j ]  ue(v), 1
        ue_vlc(bits, code, pstVPS->uiMaxDecPicBufferMinus1[i]);
        VENC_DRV_BsPutBits32(&BS, code, bits);
		//vps_max_num_reorder_pics[ j ]  ue(v),0
	    ue_vlc(bits, code, pstVPS->uiMaxNumReorderPics[i]);
        VENC_DRV_BsPutBits32(&BS, code, bits);
	    //vps_max_latency_increase_plus1[ j ]  ue(v),0
        ue_vlc(bits, code, pstVPS->uiMaxLatencyIncreasePlus1[i]);
        VENC_DRV_BsPutBits32(&BS, code, bits);
    }
    //vps_max_layer_id=0  u(6)
    VENC_DRV_BsPutBits32(&BS, 0, 6);
    //vps_num_layer_sets_minus1=0  ue(v)
    ue_vlc(bits, code, 0);

    VENC_DRV_BsPutBits32(&BS, code, bits);
   //vps_timing_info_present_flag = 0  u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //vps_extension_flag=0    u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
	H264e_PutTrailingBits(&BS);

    return (HI_U32)BS.totalBits;
}

/*获取SPS语法信息*/
static HI_U32 H265e_MakeSPS(HI_U8 *pSPSBuf, const VeduEfl_H265e_SPS_S *pstSPS)
{
    HI_U32 code;
    HI_S32 bits;
    HI_U32 i = 0;
    tBitStream BS;
    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pSPSBuf);

    VENC_DRV_BsPutBits32(&BS, 1, 32);
    VENC_DRV_BsPutBits32(&BS, 0x4201, 16);
    // video_parameter_set_id  u(4)
    VENC_DRV_BsPutBits32(&BS, 0, 4);
    // sps_max_sub_layers_minus1=0  u(3)
    VENC_DRV_BsPutBits32(&BS, 0, 3);
    // sps_temporal_id_nesting_flag = 1  u(1)
    VENC_DRV_BsPutBits32(&BS, 1, 1);

    //profile_tier_level
    {
  	    //general_profile_space  u(2)
  	    VENC_DRV_BsPutBits32(&BS, 0, 2);
	    //general_tier_flag=0  u(1)
	    VENC_DRV_BsPutBits32(&BS, 0, 1);
        //general_profile_idc=1   u(5)
	    VENC_DRV_BsPutBits32(&BS, 1, 5);
	    //general_profile_compatibility_flag[][0] =1u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
        //general_profile_compatibility_flag[][1] =1u(1)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //general_profile_compatibility_flag[][2] =1u(1)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //PutBits32(&BS, 1, 1);
	    for ( i = 3; i < 32; i++ )
        {
            //general_profile_compatibility_flag[][j]=0  u(1)
            VENC_DRV_BsPutBits32(&BS, 0, 1);
        }
	    //general_progressive_source_flag = 0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
	    //general_interlaced_source_flag = 0  u(1)
	    VENC_DRV_BsPutBits32(&BS, 0, 1);
	    //general_non_packed_constraint_flag = 0  u(1)
	    VENC_DRV_BsPutBits32(&BS, 0, 1);
        //general_frame_only_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
	    //general_reserved_zero_44bits[0..15] = 0  u(16)
        VENC_DRV_BsPutBits32(&BS, 0, 16);
	    //general_reserved_zero_44bits[16..31] = 0  u(16)
        VENC_DRV_BsPutBits32(&BS, 0, 16);
	    //general_reserved_zero_44bits[32..43] = 0  u(12)
	    VENC_DRV_BsPutBits32(&BS, 0, 12);
	    //general_level_idc    u(8)
	    VENC_DRV_BsPutBits32(&BS, 0, 8);
    }

    //seq_parameter_set_id   ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);//sps_id = 0

    //chroma_format_idc = 1  ue(v)
    ue_vlc(bits, code, 1);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //pic_width_in_luma_samples   ue(v)
    ue_vlc(bits, code, pstSPS->uiPicWidthInLumaSamples);
    VENC_DRV_BsPutBits32(&BS, code, bits);

    //pic_height_in_luma_samples  ue(v)
    ue_vlc(bits, code, pstSPS->uiPicHeightInLumaSamples);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //conformance_window_flag   u(1)
    VENC_DRV_BsPutBits32(&BS, pstSPS->bPicCroppingFlag, 1);

    if( 1 == pstSPS->bPicCroppingFlag )
    {
        //conf_win_left_offset  ue(v)
        ue_vlc(bits, code, pstSPS->uiPicCropLeftOffset);
        VENC_DRV_BsPutBits32(&BS, code, bits);
        //conf_win_right_offset  ue(v)
        ue_vlc(bits, code, pstSPS->uiPicCropRightOffset);
        VENC_DRV_BsPutBits32(&BS, code, bits);

        //conf_win_top_offset   ue(v)
        ue_vlc(bits, code, pstSPS->uiPicCropTopOffset);
        VENC_DRV_BsPutBits32(&BS, code, bits);
        //conf_win_bottom_offset   ue(v)
        ue_vlc(bits, code, pstSPS->uiPicCropBottomOffset);
        VENC_DRV_BsPutBits32(&BS, code, bits);
    }
    // bit_depth_luma_minus8 = 0    ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    // bit_depth_chroma_minus8 = 0   ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //log2_max_pic_order_cnt_lsb_minus4 =12   ue(v)
    ue_vlc(bits, code, 12);
    VENC_DRV_BsPutBits32(&BS, code, bits);

    //sps_sub_layer_ordering_info_present_flag = 1   u(1)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    for( i = 0; i <= pstSPS->uiSPSMaxSubLayersMinus1; i++ )
    {
        //sps_max_dec_pic_buffering_minus1[ i ] = 1    ue(v)
        ue_vlc(bits, code, 1);
        VENC_DRV_BsPutBits32(&BS, code, bits);
        //sps_max_num_reorder_pics[ i ]=0      ue(v),
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //sps_max_latency_increase_plus1[ i ]=0     ue(v)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
    }
    // log2_min_luma_coding_block_size_minus3=0     ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    // log2_diff_max_min_luma_coding_block_size = 3	  ue(v)
    ue_vlc(bits, code, 3);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //log2_min_transform_block_size_minus2 =0	 ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //log2_diff_max_min_transform_block_size=3   ue(v)
    ue_vlc(bits, code, 3);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //max_transform_hierarchy_depth_inter =0   ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //max_transform_hierarchy_depth_intra =0   ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //scaling_list_enable_flag=0         u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //amp_enabled_flag =0        u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //sample_adaptive_offset_enabled_flag =0   u(1)
    VENC_DRV_BsPutBits32(&BS, pstSPS->bSAOEnabledFlag, 1);
    //pcm_enabled_flag    u(1)
    VENC_DRV_BsPutBits32(&BS, pstSPS->bPcmEnable, 1);

    if (1 == pstSPS->bPcmEnable)
    {
        //pcm_sample_bit_depth_luma_minus1=7    u(4)
        VENC_DRV_BsPutBits32(&BS, 7, 4);
	    //pcm_sample_bit_depth_chroma_minus1=7    u(4)
        VENC_DRV_BsPutBits32(&BS, 7, 4);
        //log2_min_pcm_luma_coding_block_size_minus3    ue(v)
        ue_vlc(bits, code, (pstSPS->iPcmLog2MinSize - 3));
        VENC_DRV_BsPutBits32(&BS, code, bits);
        //log2_diff_max_min_pcm_luma_coding_block_size    ue(v)
	    ue_vlc(bits, code, (pstSPS->iPcmLog2MaxSize - pstSPS->iPcmLog2MinSize));
        VENC_DRV_BsPutBits32(&BS, code, bits);
        //pcm_loop_filter_disabled_flag    u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);  //00297269
        //PutBits32(&BS, pSPS->bPcmFilterDisable, 1);
    }
    //num_short_term_ref_pic_sets = 1             ue(v)
    ue_vlc(bits, code, 1);
    VENC_DRV_BsPutBits32(&BS, code, bits);
	/*short_term_ref_pic_set*/
    //num_negative_pics = 1            ue(v)
    ue_vlc(bits, code, 1);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //num_positive_pics = 0            ue(v)
	VENC_DRV_BsPutBits32(&BS, 1, 1);
	for( i=0; i < pstSPS->uiNumNegativePics; i++ )
	{
	    //delta_poc_s0_minus1 =0           ue(v)
	    VENC_DRV_BsPutBits32(&BS, 1, 1);
        //used_by_curr_pic_s0_flag            u(1)
	    VENC_DRV_BsPutBits32(&BS, 1, 1);
	}
	//long_term_ref_pics_present_flag = 0     u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
	//sps_temporal_mvp_enable_flag =1           u(1)
	VENC_DRV_BsPutBits32(&BS, pstSPS->sps_temporal_mvp_enable_flag, 1);
    //strong_intra_smoothing_enable_flag=1      u(1)
    VENC_DRV_BsPutBits32(&BS, pstSPS->bStrongIntraSmoothingFlag, 1);
    //vui_parameters_present_flag =0          u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
	//sps_extension_flag = 0                u(1)
	VENC_DRV_BsPutBits32(&BS, 0, 1);
	H264e_PutTrailingBits(&BS);
    return (HI_U32)BS.totalBits;
}


/*获取PPS语法信息*/
static HI_U32 H265e_MakePPS(HI_U8 *pPPSBuf, const VeduEfl_H265e_PPS_S *pstPPS)
{
    HI_U32 code;
    HI_S32 bits;
    //  HI_U32  iSizeId, iListId,iCoefNum;
    tBitStream BS;
    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pPPSBuf);

    VENC_DRV_BsPutBits32(&BS, 1, 32);
    VENC_DRV_BsPutBits32(&BS, 0x4401, 16);
    // pic_parameter_set_id=0   ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    // seq_parameter_set_id=0   ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    // dependent_slice_segments_enabled_flag=0        u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    // output_flag_present_flag=0        u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    // num_extra_slice_header_bits = 0     u(3)
    VENC_DRV_BsPutBits32(&BS, 0, 3);
    //sign_data_hiding_flag = 0   u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //cabac_init_present_flag=0    u(1)
    //VENC_DRV_BsPutBits32(&BS, 1, 1);
    VENC_DRV_BsPutBits32(&BS, 0, 1); //0729 保证对齐 GC
    //num_ref_idx_l0_default_active_minus1 =0     ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //num_ref_idx_l1_default_active_minus1=0      ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //pic_init_qp_minus26=0                       se(v)
    se_vlc(bits, code, 0);
    VENC_DRV_BsPutBits32(&BS, code, bits);

    //constrained_intra_pred_flag =0              u(1)
    VENC_DRV_BsPutBits32(&BS, pstPPS->constrained_intra_pred_flag, 1);
    //transform_skip_enabled_flag=0               u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //cu_qp_delta_enabled_flag               u(1)
    VENC_DRV_BsPutBits32(&BS, pstPPS->bCUQpDeltaEnable, bits);
    if( 1 == pstPPS->bCUQpDeltaEnable )
    {
        //diff_cu_qp_delta_depth                ue(v)
        ue_vlc(bits, code, 2);
        VENC_DRV_BsPutBits32(&BS, code, bits);
    }
    //pic_cb_qp_offset                    se(v)
    se_vlc(bits, code, pstPPS->iCbQpOffset);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //pic_cr_qp_offset                    se(v)
    se_vlc(bits, code, pstPPS->iCrQpOffset);
    VENC_DRV_BsPutBits32(&BS, code, bits);
    //pic_slice_chroma_qp_offsets_present_flag = 0   u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //weighted_pred_flag = 0        u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //weighted_bipred_flag = 0        u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //transquant_bypass_enable_flag   u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //tiles_enabled_flag              u(1)
    VENC_DRV_BsPutBits32(&BS, pstPPS->bTilesEnabledFlag, 1);
    //entropy_coding_sync_enabled_flag    u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    if( 1 == pstPPS->bTilesEnabledFlag)   //must be partitioned into 2 tiles
    {
        //num_tile_columns_minus1=1     ue(v)
        ue_vlc(bits, code, 1);
        VENC_DRV_BsPutBits32(&BS, code, bits);
        //num_tile_rows_minus1 =0       ue(v)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //uniform_spacing_flag = 1        u(1)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //loop_filter_across_tiles_enabled_flag     u(1)
        VENC_DRV_BsPutBits32(&BS, pstPPS->InLoopFilterCrossTiles, 1);
    }
    //loop_filter_across_slices_enabled_flag    u(1)
    VENC_DRV_BsPutBits32(&BS, pstPPS->bSliceLFAcrossSlicepps, 1);
    //deblocking_filter_control_present_flag = 1   u(1)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    if ( 1 == pstPPS->bDBFilterCtlPresent )
    {
        //deblocking_filter_override_enabled_flag   u(1)
        VENC_DRV_BsPutBits32(&BS, 1, 1);
        //pic_disable_deblocking_filter_flag   u(1)
        VENC_DRV_BsPutBits32(&BS, pstPPS->bPicDisableDBFilter, 1);
        if( 0 == pstPPS->bPicDisableDBFilter )
        {
            //pps_beta_offset_div2    se(v)
            se_vlc(bits, code, pstPPS->iBetaOffsetDiv2);
            VENC_DRV_BsPutBits32(&BS, code, bits);
            //pps_tc_offset_div2       se(v)
            se_vlc(bits, code, pstPPS->iTcOffsetDiv2);
            VENC_DRV_BsPutBits32(&BS, code, bits);
        }
    }
    //pic_scaling_list_data_present_flag    u(1)
    VENC_DRV_BsPutBits32(&BS, pstPPS->bPicScalingListPresent , 1);

    //lists_modification_present_flag = 0        u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    //log2_parallel_merge_level_minus2=0        ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);
    //slice_segment_header_extension_present_flag=0     u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);
    // pps_extension_flag    u(1)
    VENC_DRV_BsPutBits32(&BS, 0, 1);

    H264e_PutTrailingBits(&BS);
    return (HI_U32)BS.totalBits;
}

static HI_U32 H265e_MakeSlcHdr(HI_HANDLE EncHandle, const VeduEfl_H265e_SlcHdr_S *pSlcHdr)
{
    HI_U32 code,bSAOEnabled,bDBFEnabled,buf[8];
    HI_S32 bits,bitPara,i;
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;
    // HI_U32  iSizeId, iListId,iCoefNum;
    tBitStream BS;
    VENC_DRV_BsOpenBitStream(&BS, buf);

    //first_slice_in_pic_flag        u(1)
    //PutBits32(&BS, pSlcHdr->bFirstSliceInPic, 1);
    if( 2 == pSlcHdr->eSliceType ) /////H265E_I_SLICE
    {
        //no_output_of_prior_pics_flag = 0    u(1)
        VENC_DRV_BsPutBits32(&BS, 0, 1);
    }
    //slice_pic_parameter_set_id=0         ue(v)
    VENC_DRV_BsPutBits32(&BS, 1, 1);

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pEncPara->slchdr_part1 = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32) { pEncPara->slchdr_part1 >>= (32 - bits); }
    }
    bitPara = BS.totalBits;
    pEncPara->slchdr_size_part1 = BS.totalBits;
    VENC_DRV_BsOpenBitStream(&BS, buf);

    if( pSlcHdr->iSliceAddr > 0 )
    {
        //slice_address         u(n)
        ue_vlc(bits, code, pSlcHdr->iSliceAddr);
        VENC_DRV_BsPutBits32(&BS, code, bits);
		//HI_ERR_VENC("***###BS.totalBits:%d\n",BS.totalBits);
    }
    {
         //slice_type         ue(v)
        if ( 2 == pSlcHdr->eSliceType )///H265E_I_SLICE
        {
			ue_vlc(bits, code, 2);
            VENC_DRV_BsPutBits32(&BS, code, bits);
        }
        else
        {
            ue_vlc(bits, code, 1);
            VENC_DRV_BsPutBits32(&BS, code, bits);
        }
        if ( 2 != pSlcHdr->eSliceType )//
        {
            //pic_order_cnt_lsb            u(16)
            //ue_vlc(bits, code, pSlcHdr->uiPocLsb);
            VENC_DRV_BsPutBits32(&BS, pSlcHdr->uiPocLsb, 16);
            //short_term_ref_pic_set_sps_flag=1      u(1)
            VENC_DRV_BsPutBits32(&BS, 1, 1);
        }

        if (2 != pSlcHdr->eSliceType )
        {
            if ( pSlcHdr->bSpsTemporalMvpEnableFlag )
            {
                //enable_temporal_mvp_flag=1        u(1)
                VENC_DRV_BsPutBits32(&BS, 1, 1);
            }
        }
        if( 1 == pSlcHdr->bSAOEnabledFlag )
        {
            //slice_sao_luma_flag                  u(1)
            VENC_DRV_BsPutBits32(&BS, pSlcHdr->bSliceSaoLuma, 1);
            //slice_sao_chroma_flag                u(1)
            VENC_DRV_BsPutBits32(&BS, pSlcHdr->bSliceSaoChroma, 1);
        }
        if ( pSlcHdr->eSliceType !=2 )
        {
            //num_ref_idx_active_override_flag = 0    u(1)
            VENC_DRV_BsPutBits32(&BS, 0, 1);
            //cabac_init_flag
            //VENC_DRV_BsPutBits32(&BS, pSlcHdr->cabac_init_flag, 1); //0729与 gc对齐
            //five_minus_max_num_merge_cand=3         ue(v)
            ue_vlc(bits, code, pSlcHdr->five_minus_max_num_merge_cand);
            VENC_DRV_BsPutBits32(&BS, code, bits);
        }
        //slice_qp_delta     se(v)
        se_vlc(bits, code, pSlcHdr->iSliceQPDelta);
        VENC_DRV_BsPutBits32(&BS, code, bits);
        if ( 1 == pSlcHdr->bDBFilterCtlPresent )
        {
            if ( 1 == pSlcHdr->bDBFilterOverrideEnabled )
            {
                //deblocking_filter_override_flag        u(1)
                VENC_DRV_BsPutBits32(&BS, pSlcHdr->bDFOverrideFlag, 1);
            }
	        if ( 1 == pSlcHdr->bDFOverrideFlag )
	        {
	            //slice_disable_deblocking_filter_flag     u(1)
                VENC_DRV_BsPutBits32(&BS, pSlcHdr->bSliceHeaderDisableDF, 1);
	            if( 0 == pSlcHdr->bSliceHeaderDisableDF )
	            {
	                //beta_offset_div2        se(v)
	                se_vlc(bits, code, pSlcHdr->iBetaOffsetDiv2);
                    VENC_DRV_BsPutBits32(&BS, code, bits);
	                //tc_offset_div2          se(v)
	                se_vlc(bits, code, pSlcHdr->iTcOffsetDiv2);
                    VENC_DRV_BsPutBits32(&BS, code, bits);
	            }
	        }
        }
        bSAOEnabled = (0 == pSlcHdr->bSAOEnabledFlag) ? 0 : (pSlcHdr->bSliceSaoLuma || pSlcHdr->bSliceSaoChroma);
        bDBFEnabled = (0 == pSlcHdr->bSliceHeaderDisableDF) ? 1 : 0;

        if( (1 == pEncPara->bSliceLFAcrossSlicepps) && ( 1 == bSAOEnabled || 1 == bDBFEnabled ||pSlcHdr->bSliceHeaderDisableDF==0) )
        //if( ( 1 == bSAOEnabled || 1 == bDBFEnabled ) )
        {
            //slice_loop_filter_across_slices_enabled_flag     u(1)
            VENC_DRV_BsPutBits32(&BS, pSlcHdr->bSliceLFAcrossSlice, 1);
        }
    }
    /*if ( (1 == pPPS->bTilesEnabledFlag) || (1 == pPPS->bEntropyCodingSyncEnabled) )
    {
        //num_entry_point_offsets = 0        ue(v)
        ue_vlc(bits, code, 0);
        PutBits32(&BS, code, bits);
    }
*/

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pEncPara->CABAC_SLCHDR_PART2_SEG[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32) { pEncPara->CABAC_SLCHDR_PART2_SEG[i] >>= (32 - bits); }
    }
    bitPara=BS.totalBits;
    //bitPara |= BS.totalBits << 16;
    pEncPara->slchdr_size_part2 = bitPara;
    ///H264e_PutTrailingBits(&BS);
    return (HI_U32)bitPara;
}

HI_S32 CheckPreventionThreeByte(HI_U8 *pcStream, HI_U32 iNum ,HI_U8 *tempStream)
{
    HI_U32 iInsertBytes  = 0;
    HI_U32 i = 0, j = 0;
    HI_U32 inum = iNum/8;

    if ( inum < 5 )
    {
        return iInsertBytes;
       //return;
    }
    for ( i=0; i<6; i++,j++ )
    {
        tempStream[j]     = pcStream[i];

    }
    for ( i=6,j = 6; i<=inum-3; i++ )
    {
        tempStream[j]     = pcStream[i];
        tempStream[j + 1] = pcStream[i + 1];

        if ( ( 0 == pcStream[i] ) && ( 0 == pcStream[i+1] ) )
        {
            if ( ( 0 == pcStream[i+2] ) || ( 1 == pcStream[i+2] ) || ( 2 == pcStream[i+2] ) || ( 3 == pcStream[i+2] ))
            {
                tempStream[j + 2] = 0x03;
                iInsertBytes++;


                if ( (i == (inum - 3)) || (i == (inum - 4)) )
                {
                    tempStream[j + 3] = pcStream[i + 2];
					tempStream[j + 4] = pcStream[i + 3];
					i += 1;
                }
                else
                {
                    i += 1;
                    j += 3;
                }
            }
            else
            {
                tempStream[j + 2] = pcStream[i + 2];
                j++;
            }
        }
        else
        {
            tempStream[j + 2] = pcStream[i + 2];
            j++;
        }
    }

    return iInsertBytes;
}

static HI_U32 H264e_MakeSPS(HI_U8 *pSPSBuf, const VeduEfl_H264e_SPS_S *pSPS)
{
	HI_U32 code, TotalMb, profile_idc, level_idc;
	HI_S32 bits;

	tBitStream BS;
	VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pSPSBuf);


	TotalMb = pSPS->FrameWidthInMb * pSPS->FrameHeightInMb;

	if     (TotalMb <= 99  ) level_idc = 10;
	else if(TotalMb <= 396 ) level_idc = 20;
	else if(TotalMb <= 792 ) level_idc = 21;
	else if(TotalMb <= 1620) level_idc = 30;
	else if(TotalMb <= 3600) level_idc = 31;
	else if(TotalMb <= 5120) level_idc = 32;
	else if(TotalMb <= 8192) level_idc = 42;
	else                     level_idc = 50;

	profile_idc = pSPS->ProfileIDC;

	VENC_DRV_BsPutBits32(&BS, 1, 32);

	VENC_DRV_BsPutBits31(&BS, 0, 1); // forbidden_zero_bit
	VENC_DRV_BsPutBits31(&BS, 3, 2); // nal_ref_idc
	VENC_DRV_BsPutBits31(&BS, 7, 5); // nal_unit_type

	VENC_DRV_BsPutBits31(&BS, profile_idc, 8);
	VENC_DRV_BsPutBits31(&BS, 0x00, 8);
	VENC_DRV_BsPutBits31(&BS, level_idc, 8);

	VENC_DRV_BsPutBits31(&BS, 1, 1); // ue, sps_id = 0

	if(100 == pSPS->ProfileIDC)   //just for high profile
	{
		VENC_DRV_BsPutBits31(&BS, 0x2, 3);
		VENC_DRV_BsPutBits31(&BS, 0xC, 4);
	}

	VENC_DRV_BsPutBits31(&BS, 1, 1); // ue, log2_max_frame_num_minus4 = 0

	VENC_DRV_BsPutBits31(&BS, 3, 3); // ue, pic_order_cnt_type = 2
	VENC_DRV_BsPutBits31(&BS, 3, 3); // ue, num_ref_frames = 1 (or 2)
	VENC_DRV_BsPutBits31(&BS, 0, 1); // u1, gaps_in_frame_num_value_allowed_flag

	ue_vlc(bits, code, (pSPS->FrameWidthInMb - 1));
	VENC_DRV_BsPutBits31(&BS, code, bits);
	ue_vlc(bits, code, (pSPS->FrameHeightInMb - 1));
	VENC_DRV_BsPutBits31(&BS, code, bits);

	VENC_DRV_BsPutBits31(&BS, 1, 1); // u1, frame_mbs_only_flag = 1 (or 0)

	if (0)                // !pSPS->FrameMbsOnlyFlag
	{
		VENC_DRV_BsPutBits31(&BS, 0, 1); // mb_adaptive_frame_field_flag = 0
		VENC_DRV_BsPutBits31(&BS, 1, 1); // direct_8x8_inference_flag
	}
	else
	{
		VENC_DRV_BsPutBits31(&BS, 0, 1); // direct_8x8_inference_flag
	}

	{
	int bFrameCropping = ((pSPS->FrameCropLeft | pSPS->FrameCropRight |
	                       pSPS->FrameCropTop | pSPS->FrameCropBottom) != 0);

	VENC_DRV_BsPutBits31(&BS, bFrameCropping, 1);

	if (bFrameCropping)
	{
		ue_vlc(bits, code, pSPS->FrameCropLeft);
		VENC_DRV_BsPutBits31(&BS, code, bits);
		ue_vlc(bits, code, pSPS->FrameCropRight);
		VENC_DRV_BsPutBits31(&BS, code, bits);
		ue_vlc(bits, code, pSPS->FrameCropTop);
		VENC_DRV_BsPutBits31(&BS, code, bits);
		ue_vlc(bits, code, pSPS->FrameCropBottom);
		VENC_DRV_BsPutBits31(&BS, code, bits);
	}
	}
	VENC_DRV_BsPutBits31(&BS, 0, 1); // vui_parameters_present_flag
	H264e_PutTrailingBits(&BS);

	HI_INFO_VENC("VENC h264 profile_id:%d,level_id:%d,num_ref_frames: %d\n",profile_idc,level_idc,1);
	return (HI_U32)BS.totalBits;
}

static HI_U32 H264e_MakePPS(HI_U8 *pPPSBuf, const VeduEfl_H264e_PPS_S *pPPS)
{
	HI_U32 code, b = pPPS->H264CabacEn;
	int    bits;

	tBitStream BS;
	VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pPPSBuf);

	VENC_DRV_BsPutBits32(&BS, 1, 32);

	VENC_DRV_BsPutBits31(&BS, 0, 1); // forbidden_zero_bit
	VENC_DRV_BsPutBits31(&BS, 3, 2); // nal_ref_idc
	VENC_DRV_BsPutBits31(&BS, 8, 5); // nal_unit_type

	VENC_DRV_BsPutBits31(&BS, 1, 1); // pps_id = 0
	VENC_DRV_BsPutBits31(&BS, 1, 1); // sps_id = 0

	VENC_DRV_BsPutBits31(&BS, b, 1); // entropy_coding_mode_flag
	VENC_DRV_BsPutBits31(&BS, 0, 1); // pic_order_present_flag
	VENC_DRV_BsPutBits31(&BS, 1, 1); // num_slice_groups_minus1
	VENC_DRV_BsPutBits31(&BS, 2, 3); // num_ref_idx_l0_active_minus1 = 0 (or 1)
	VENC_DRV_BsPutBits31(&BS, 1, 1); // num_ref_idx_l1_active_minus1 = 0
	VENC_DRV_BsPutBits31(&BS, 0, 3); // weighted_pred_flag & weighted_bipred_idc
	VENC_DRV_BsPutBits31(&BS, 3, 2); // pic_init_qp_minus26 & pic_init_qs_minus26
	se_vlc(bits, code, pPPS->CbQpOffset); // chroma_qp_index_offset
	VENC_DRV_BsPutBits31(&BS, code, bits);

	VENC_DRV_BsPutBits31(&BS, 1,  1);                 // deblocking_filter_control_present_flag
	VENC_DRV_BsPutBits31(&BS, pPPS->ConstIntra, 1);   // constrained_intra_pred_flag

	VENC_DRV_BsPutBits31(&BS, 0, 1);                  // redundant_pic_cnt_present_flag

	if (pPPS->H264HpEn)
	{
		//int i, j;

		VENC_DRV_BsPutBits31(&BS, 1, 1); // transform_8x8_mode_flag
		VENC_DRV_BsPutBits31(&BS, 0, 1); // pic_scaling_matrix_present_flag
        se_vlc(bits, code, pPPS->CrQpOffset); VENC_DRV_BsPutBits31(&BS, code, bits);
    }

    H264e_PutTrailingBits(&BS);
    return (HI_U32)BS.totalBits;
}

static HI_U32 H264e_MakeSlcHdr(HI_U32 *pHdrBuf, HI_U32 *pReorderBuf, HI_U32 *pMarkBuf,
                               VeduEfl_H264e_SlcHdr_S*pSlcHdr)
{
	HI_U32 code, buf[8];
	int    bits, i, bitPara;

	//static HI_U32 idr_pic_id = 0;
	tBitStream BS;

	VENC_DRV_BsOpenBitStream(&BS, buf);

	ue_vlc(bits, code, pSlcHdr->slice_type);
	VENC_DRV_BsPutBits31(&BS, code, bits); // slice_type, 0(P) or 2(I)
	VENC_DRV_BsPutBits31(&BS, 1, 1);                        // pic_parameter_set_id
	VENC_DRV_BsPutBits31(&BS, pSlcHdr->frame_num & 0xF, 4); // frame number

	if(pSlcHdr->slice_type == 2) // all I Picture be IDR
	{
		ue_vlc(bits, code, pSlcHdr->idr_pic_id & 0x7FFF);
		VENC_DRV_BsPutBits31(&BS, code, bits);
		pSlcHdr->idr_pic_id++;
	}
	//  else if(pSlcHdr->NumRefIndex ==  0)
	//  {
	//    PutBits31(&BS, 0, 1); // num_ref_idx_active_override_flag
	//  }
	else
	{
		VENC_DRV_BsPutBits31(&BS, 1, 1); // num_ref_idx_active_override_flag
		ue_vlc(bits, code, pSlcHdr->NumRefIndex);
		VENC_DRV_BsPutBits31(&BS, code, bits);
	}

	*BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

	bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pHdrBuf[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32)
        {
            pHdrBuf[i] >>= (32 - bits);
        }
    }

    bitPara = BS.totalBits;

    /****** RefPicListReordering() ************************************/

    VENC_DRV_BsOpenBitStream(&BS, buf);

    VENC_DRV_BsPutBits31(&BS, 0, 1);/* ref_pic_list_reordering_flag_l0 = 0 ("0") */

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pReorderBuf[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32) { pReorderBuf[i] >>= (32 - bits); }
    }

    bitPara |= BS.totalBits << 8;

    /****** DecRefPicMarking() *****************************************/

    VENC_DRV_BsOpenBitStream(&BS, buf);

    if (pSlcHdr->slice_type == 2)
    {
        VENC_DRV_BsPutBits31(&BS, 0, 1);/* no_output_of_prior_pics_flag */
        VENC_DRV_BsPutBits31(&BS, 0, 1);/* long_term_reference_flag     */
    }
    else
    {
        VENC_DRV_BsPutBits31(&BS, 0, 1);/* adaptive_ref_pic_marking_mode_flag */
    }

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pMarkBuf[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32) { pMarkBuf[i] >>= (32 - bits); }
    }

    bitPara |= BS.totalBits << 16;
    return (HI_U32)bitPara;
}


HI_S32 VENC_SetDtsConfig(VeduEfl_DTS_CONFIG_S *pDtsConfig)
{
    if (HI_NULL == pDtsConfig)
    {
        HI_ERR_VENC("%s FATAL: pDtsConfig = NULL.\n", __func__);
        return HI_FAILURE;
    }

    if (0 == pDtsConfig->VeduIrqNum     || 0 == pDtsConfig->MmuIrqNum
     //|| 0 == pDtsConfig->VedusecIrqNum    || 0 == pDtsConfig->MmusecIrqNum
     || 0 == pDtsConfig->VencRegBaseAddr|| 0 == pDtsConfig->VencRegRange
     || 0 == pDtsConfig->SmmuPageBaseAddr)
    {
        HI_ERR_VENC("%s invalid param: VeduIrqNum=%d, MmuIrqNum=%d, VedusecIrqNum=%d, MmusecIrqNum=%d, VencRegBaseAddr=0x%x, VencRegRange=%d, SmmuPageBaseAddr=0x%x\n", __func__,
               pDtsConfig->VeduIrqNum, pDtsConfig->MmuIrqNum, pDtsConfig->VedusecIrqNum, pDtsConfig->MmusecIrqNum, pDtsConfig->VencRegBaseAddr, pDtsConfig->VencRegRange, pDtsConfig->SmmuPageBaseAddr);
        return HI_FAILURE;
    }
    gVencIsFPGA       = pDtsConfig->IsFPGA;
    gVeduIrqNum       = pDtsConfig->VeduIrqNum;
    gMmuIrqNum        = pDtsConfig->MmuIrqNum;
    gVedusecIrqNum    = pDtsConfig->VedusecIrqNum;
    gMmusecIrqNum     = pDtsConfig->MmusecIrqNum;

    gVencRegBaseAddr  = pDtsConfig->VencRegBaseAddr;
    gVencRegRange     = pDtsConfig->VencRegRange;
    gSmmuPageBaseAddr = pDtsConfig->SmmuPageBaseAddr;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflInitEncParaCfgHevc_LowPwr0( VeduEfl_EncPara_S  *pEncPara)
{
	VeduEfl_EncPara_S_Cfg  *pEncParaCfg = (VeduEfl_EncPara_S_Cfg*)kmalloc(sizeof(VeduEfl_EncPara_S_Cfg),GFP_KERNEL);
    if(NULL == pEncParaCfg)
    {
        return -1;
    }
    memset(pEncParaCfg, 0, sizeof(VeduEfl_EncPara_S_Cfg));
    pEncPara->pstCfg_EncPara = pEncParaCfg;

    pEncParaCfg->enable_cfg_err = 0;
    pEncParaCfg->enable_vedu_timeout = 0;
    pEncParaCfg->enable_vedu_step = 0;
    pEncParaCfg->enable_vedu_brkpt = 0;
    pEncParaCfg->enable_vedu_slice_end = 1;// enable sliec IRQ需同步修改vcpi_slice_int_en
    //pEncParaCfg->enable_vedu_slice_end = 0;
    pEncParaCfg->enable_ve_pbitsover = 0;
    pEncParaCfg->enable_ve_buffull = 1;
#ifndef IRQ_EN
    pEncParaCfg->enable_ve_eop = 0;
#else
    pEncParaCfg->enable_ve_eop = 1;//to do for irq test
#endif
    pEncParaCfg->clr_cfg_err = 0;
    pEncParaCfg->clr_vedu_timeout = 0;
    pEncParaCfg->clr_vedu_step = 0;
    pEncParaCfg->clr_vedu_brkpt = 0;
    pEncParaCfg->clr_vedu_slice_end = 0;
    pEncParaCfg->clr_ve_pbitsover = 0;
    pEncParaCfg->clr_ve_buffull = 0;
    pEncParaCfg->clr_ve_eop = 0;
    pEncParaCfg->vcpi_vstep = 0;
    pEncParaCfg->vcpi_vstart = 1;
    pEncParaCfg->vcpi_dbgmod = 0;
    pEncParaCfg->vcpi_bkp_en = 0;
    pEncParaCfg->vcpi_time_en = 0;
    pEncParaCfg->vcpi_lcu_size = 2;
    pEncParaCfg->vcpi_tiles_en = 0;
    pEncParaCfg->vcpi_trans_mode = 0;
    pEncParaCfg->vcpi_pskp_en = 1;
    pEncParaCfg->vcpi_idr_pic = 0;
    pEncParaCfg->vcpi_entropy_mode = 0;
    pEncParaCfg->vcpi_img_improve_en = 1;

    pEncParaCfg->vcpi_rec_cmp_en = 1;//
    pEncParaCfg->vcpi_ref_cmp_en = 1;//

    pEncParaCfg->vcpi_sao_chroma = 1;
    pEncParaCfg->vcpi_sao_luma = 1;
    //pEncParaCfg->vcpi_slice_int_en = 0;
    pEncParaCfg->vcpi_slice_int_en = 1;// enable sliec IRQ
    pEncParaCfg->vcpi_protocol = 0;
    pEncParaCfg->vcpi_cfg_mode = 0;
    pEncParaCfg->vcpi_lcu_time_sel = 1;
    pEncParaCfg->vcpi_vedsel = 0;
    pEncParaCfg->vcpi_tile_height = 0;
    pEncParaCfg->vcpi_tile_width = 0;
    pEncParaCfg->vcpi_multislc_en = 0;
    pEncParaCfg->vcpi_slcspilt_mod = 1;
    pEncParaCfg->vcpi_slice_size = 12;
    pEncParaCfg->vcpi_frm_qp = 26;
    pEncParaCfg->vcpi_cb_qp_offset = 0;
    pEncParaCfg->vcpi_cr_qp_offset = 0;
    pEncParaCfg->vcpi_cnt_clr = 0;
    pEncParaCfg->vcpi_frame_no = 4294967295;
    pEncParaCfg->vcpi_dblk_filter_flag = 0;
    pEncParaCfg->vcpi_dblk_alpha = 0;
    pEncParaCfg->vcpi_dblk_beta = 0;
    pEncParaCfg->vcpi_mem_clkgate_en = 1;
    pEncParaCfg->vcpi_clkgate_en = 2;
    pEncParaCfg->fme_gtck_en = 1;
    pEncParaCfg->mrg_gtck_en = 1;
    pEncParaCfg->tqitq_gtck_en = 1;
    pEncParaCfg->vcpi_ime_lowpow = 1;
    pEncParaCfg->vcpi_fme_lowpow = 1;
    pEncParaCfg->vcpi_intra_lowpow = 1;
    pEncParaCfg->vcpi_imgheight_pix = 480;
    pEncParaCfg->vcpi_imgwidth_pix = 640;
    pEncParaCfg->vcpi_bp_lcu_y = 0;
    pEncParaCfg->vcpi_bp_lcu_x = 0;
    pEncParaCfg->vedu_timeout = 4294967295;
    pEncParaCfg->vcpi_w_outstanding = 3;
    pEncParaCfg->vcpi_r_outstanding = 31;//31  0615 FPGA环境目前只支持0-7
    pEncParaCfg->vcpi_sw_height = 32;
    pEncParaCfg->vcpi_sw_width = 72;
    pEncParaCfg->vcpi_tmv_wr_rd_avail = 3;
    pEncParaCfg->vcpi_cross_tile = 1;
    pEncParaCfg->vcpi_cross_slice = 1;
    pEncParaCfg->osd_en = 0;
    pEncParaCfg->osd7_absqp = 0;
    pEncParaCfg->osd6_absqp = 0;
    pEncParaCfg->osd5_absqp = 0;
    pEncParaCfg->osd4_absqp = 0;
    pEncParaCfg->osd3_absqp = 0;
    pEncParaCfg->osd2_absqp = 0;
    pEncParaCfg->osd1_absqp = 0;
    pEncParaCfg->osd0_absqp = 0;
    pEncParaCfg->osd7_en = 0;
    pEncParaCfg->osd6_en = 0;
    pEncParaCfg->osd5_en = 0;
    pEncParaCfg->osd4_en = 0;
    pEncParaCfg->osd3_en = 0;
    pEncParaCfg->osd2_en = 0;
    pEncParaCfg->osd1_en = 0;
    pEncParaCfg->osd0_en = 0;
    pEncParaCfg->osd0_y = 0;
    pEncParaCfg->osd0_x = 0;
    pEncParaCfg->osd1_y = 0;
    pEncParaCfg->osd1_x = 0;
    pEncParaCfg->osd2_y = 0;
    pEncParaCfg->osd2_x = 0;
    pEncParaCfg->osd3_y = 0;
    pEncParaCfg->osd3_x = 0;
    pEncParaCfg->osd4_y = 0;
    pEncParaCfg->osd4_x = 0;
    pEncParaCfg->osd5_y = 0;
    pEncParaCfg->osd5_x = 0;
    pEncParaCfg->osd6_y = 0;
    pEncParaCfg->osd6_x = 0;
    pEncParaCfg->osd7_y = 0;
    pEncParaCfg->osd7_x = 0;
    pEncParaCfg->osd0_h = 0;
    pEncParaCfg->osd0_w = 0;
    pEncParaCfg->osd1_h = 0;
    pEncParaCfg->osd1_w = 0;
    pEncParaCfg->osd2_h = 0;
    pEncParaCfg->osd2_w = 0;
    pEncParaCfg->osd3_h = 0;
    pEncParaCfg->osd3_w = 0;
    pEncParaCfg->osd4_h = 0;
    pEncParaCfg->osd4_w = 0;
    pEncParaCfg->osd5_h = 0;
    pEncParaCfg->osd5_w = 0;
    pEncParaCfg->osd6_h = 0;
    pEncParaCfg->osd6_w = 0;
    pEncParaCfg->osd7_h = 0;
    pEncParaCfg->osd7_w = 0;
    pEncParaCfg->osd7_layer_id = 0;
    pEncParaCfg->osd6_layer_id = 0;
    pEncParaCfg->osd5_layer_id = 0;
    pEncParaCfg->osd4_layer_id = 0;
    pEncParaCfg->osd3_layer_id = 0;
    pEncParaCfg->osd2_layer_id = 0;
    pEncParaCfg->osd1_layer_id = 0;
    pEncParaCfg->osd0_layer_id = 0;
    pEncParaCfg->osd3_qp = 0;
    pEncParaCfg->osd2_qp = 0;
    pEncParaCfg->osd1_qp = 0;
    pEncParaCfg->osd0_qp = 0;
    pEncParaCfg->osd7_qp = 0;
    pEncParaCfg->osd6_qp = 0;
    pEncParaCfg->osd5_qp = 0;
    pEncParaCfg->osd4_qp = 0;
    pEncParaCfg->curld_tunlcell_addr = 0;
    pEncParaCfg->curld_y_addr = 2415919104;
    pEncParaCfg->curld_c_addr = 2483027968;
    pEncParaCfg->curld_v_addr = 2499805184;
    pEncParaCfg->curld_yh_addr = 2821718016;
    pEncParaCfg->curld_ch_addr = 2821849088;
    pEncParaCfg->curld_y_stride = 640;
    pEncParaCfg->curld_c_stride = 640;
    pEncParaCfg->curld_yh_stride = 4096;
    pEncParaCfg->curld_ch_stride = 4096;
    pEncParaCfg->recst_yaddr = 2516582400;
    pEncParaCfg->recst_caddr = 2583691264;
    pEncParaCfg->recst_cstride = 4096;
    pEncParaCfg->recst_ystride = 4096;
    pEncParaCfg->recst_yh_addr = 2821980160;
    pEncParaCfg->recst_ch_addr = 2823028736;
    pEncParaCfg->recst_head_stride = 4096;
    pEncParaCfg->refld_luma_addr = 2617245696;
    pEncParaCfg->refld_chroma_addr = 2684354560;
    pEncParaCfg->refld_luma_vstride = 4096;
    pEncParaCfg->refld_chroma_vstride = 4096;
    pEncParaCfg->refld_yh_addr = 2824077312;
    pEncParaCfg->refld_ch_addr = 2825125888;
    pEncParaCfg->refld_yh_stride = 4096;
    pEncParaCfg->refld_ch_stride = 4096;
    pEncParaCfg->vcpi_pmeld_addr = 2804940800;
    pEncParaCfg->vcpi_pmest_addr = 2788163584;
    pEncParaCfg->upst_address = 2789212160;
    pEncParaCfg->mvst_address = 2786066432;
    pEncParaCfg->mvld_address = 2787115008;
    pEncParaCfg->csst_strmaddr = 2717908992;
    pEncParaCfg->csst_swptraddr = 2785017856;
    pEncParaCfg->csst_srptraddr = 2785018112;
    pEncParaCfg->vcpi_package_sel = 0;
    pEncParaCfg->vcpi_str_fmt = 0;
    pEncParaCfg->vcpi_blk_type = 0;
    pEncParaCfg->vcpi_store_mode = 0;
    pEncParaCfg->vcpi_scale_en = 0;
    pEncParaCfg->vcpi_crop_en = 0;
    pEncParaCfg->vcpi_crop_ystart = 0;
    pEncParaCfg->vcpi_crop_xstart = 0;
    pEncParaCfg->vcpi_crop_yend = 0;
    pEncParaCfg->vcpi_crop_xend = 0;
    pEncParaCfg->vcpi_yscale = 0;
    pEncParaCfg->vcpi_xscale = 0;
    pEncParaCfg->vcpi_oriheight_pix = 480;
    pEncParaCfg->vcpi_oriwidth_pix = 640;
    pEncParaCfg->vcpi_mrg_cu_en = 15;
    pEncParaCfg->vcpi_fme_cu_en = 15;
    pEncParaCfg->vcpi_ipcm_en = 1;
    pEncParaCfg->vcpi_intra_cu_en = 15;
    pEncParaCfg->vcpi_byte_stuffing = 0;
    pEncParaCfg->vcpi_num_refidx = 0;
    pEncParaCfg->vcpi_cabac_init_idc = 0;
    pEncParaCfg->vcpi_ref_idc = 0;
    pEncParaCfg->vcpi_ext_edge_en = 1;
    pEncParaCfg->vcpi_force_inter = 0;
    pEncParaCfg->vcpi_pblk_pre_en = 1;
    pEncParaCfg->vcpi_iblk_pre_en = 1;
    pEncParaCfg->vcpi_pblk_pre_cost_thr = 100;
    pEncParaCfg->vcpi_iblk_pre_cost_thr = 500;
    pEncParaCfg->vcpi_iblk_pre_mvy_thr = 5;
    pEncParaCfg->vcpi_iblk_pre_mvx_thr = 5;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr1 = 15;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr0 = 15;
    pEncParaCfg->vcpi_win0_height = 8;
    pEncParaCfg->vcpi_win0_width = 8;
    pEncParaCfg->vcpi_win1_height = 8;
    pEncParaCfg->vcpi_win1_width = 8;
    pEncParaCfg->vcpi_win2_height = 16;
    pEncParaCfg->vcpi_win2_width = 16;
    pEncParaCfg->vcpi_win3_height = 24;
    pEncParaCfg->vcpi_win3_width = 24;
    pEncParaCfg->vcpi_static_en = 1;
    pEncParaCfg->vcpi_highedge_en = 1;
    pEncParaCfg->vcpi_skin_en = 1;
    pEncParaCfg->vcpi_roi_en = 0;
    pEncParaCfg->region7keep = 0;
    pEncParaCfg->region6keep = 0;
    pEncParaCfg->region5keep = 0;
    pEncParaCfg->region4keep = 0;
    pEncParaCfg->region3keep = 0;
    pEncParaCfg->region2keep = 0;
    pEncParaCfg->region1keep = 0;
    pEncParaCfg->region0keep = 1;
    pEncParaCfg->absqp7 = 0;
    pEncParaCfg->absqp6 = 0;
    pEncParaCfg->absqp5 = 0;
    pEncParaCfg->absqp4 = 0;
    pEncParaCfg->absqp3 = 0;
    pEncParaCfg->absqp2 = 0;
    pEncParaCfg->absqp1 = 0;
    pEncParaCfg->absqp0 = 0;
    pEncParaCfg->region7en = 0;
    pEncParaCfg->region6en = 0;
    pEncParaCfg->region5en = 0;
    pEncParaCfg->region4en = 0;
    pEncParaCfg->region3en = 0;
    pEncParaCfg->region2en = 0;
    pEncParaCfg->region1en = 0;
    pEncParaCfg->region0en = 0;
    pEncParaCfg->roiqp3 = 0;
    pEncParaCfg->roiqp2 = 0;
    pEncParaCfg->roiqp1 = 0;
    pEncParaCfg->roiqp0 = 0;
    pEncParaCfg->roiqp7 = 0;
    pEncParaCfg->roiqp6 = 0;
    pEncParaCfg->roiqp5 = 0;
    pEncParaCfg->roiqp4 = 0;
    pEncParaCfg->size0_roiheight = 0;
    pEncParaCfg->size0_roiwidth = 0;
    pEncParaCfg->start0_roistarty = 0;
    pEncParaCfg->start0_roistartx = 0;
    pEncParaCfg->size1_roiheight = 0;
    pEncParaCfg->size1_roiwidth = 0;
    pEncParaCfg->start1_roistarty = 0;
    pEncParaCfg->start1_roistartx = 0;
    pEncParaCfg->size2_roiheight = 0;
    pEncParaCfg->size2_roiwidth = 0;
    pEncParaCfg->start2_roistarty = 0;
    pEncParaCfg->start2_roistartx = 0;
    pEncParaCfg->size3_roiheight = 0;
    pEncParaCfg->size3_roiwidth = 0;
    pEncParaCfg->start3_roistarty = 0;
    pEncParaCfg->start3_roistartx = 0;
    pEncParaCfg->size4_roiheight = 0;
    pEncParaCfg->size4_roiwidth = 0;
    pEncParaCfg->start4_roistarty = 0;
    pEncParaCfg->start4_roistartx = 0;
    pEncParaCfg->size5_roiheight = 0;
    pEncParaCfg->size5_roiwidth = 0;
    pEncParaCfg->start5_roistarty = 0;
    pEncParaCfg->start5_roistartx = 0;
    pEncParaCfg->size6_roiheight = 0;
    pEncParaCfg->size6_roiwidth = 0;
    pEncParaCfg->start6_roistarty = 0;
    pEncParaCfg->start6_roistartx = 0;
    pEncParaCfg->size7_roiheight = 0;
    pEncParaCfg->size7_roiwidth = 0;
    pEncParaCfg->start7_roistarty = 0;
    pEncParaCfg->start7_roistartx = 0;
    pEncParaCfg->lcu_target_bit = 0;
    pEncParaCfg->narrow_tile_width = 0;
    pEncParaCfg->lcu_performance_baseline = 0;
    pEncParaCfg->norm32_tr1_denois_max_num = 4;
    pEncParaCfg->norm32_coeff_protect_num = 255;
    pEncParaCfg->norm16_tr1_denois_max_num = 3;
    pEncParaCfg->norm16_coeff_protect_num = 64;
    pEncParaCfg->skin32_tr1_denois_max_num = 8;
    pEncParaCfg->skin32_coeff_protect_num = 32;
    pEncParaCfg->skin16_tr1_denois_max_num = 6;
    pEncParaCfg->skin16_coeff_protect_num = 16;
    pEncParaCfg->static32_tr1_denois_max_num = 8;
    pEncParaCfg->static32_coeff_protect_num = 16;
    pEncParaCfg->static16_tr1_denois_max_num = 6;
    pEncParaCfg->static16_coeff_protect_num = 8;
    pEncParaCfg->hedge32_tr1_denois_max_num = 8;
    pEncParaCfg->hedge32_coeff_protect_num = 32;
    pEncParaCfg->hedge16_tr1_denois_max_num = 6;
    pEncParaCfg->hedge16_coeff_protect_num = 16;
    pEncParaCfg->norm_intra_cu32_rdcost_offset = 0;
    pEncParaCfg->norm_intra_cu16_rdcost_offset = 0;
    pEncParaCfg->norm_intra_cu8_rdcost_offset = 0;
    pEncParaCfg->norm_intra_cu4_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu64_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu32_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu16_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu8_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu64_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu32_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu16_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu8_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu32_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu16_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu8_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu4_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu64_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu32_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu16_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu8_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu64_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu32_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu16_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu8_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu32_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu16_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu8_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu4_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu64_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu32_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu16_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu8_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu64_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu32_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu16_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu8_rdcost_offset = 0;
    pEncParaCfg->vcpi_new_cost_en = 1;
    pEncParaCfg->vcpi_psw_adapt_en = 1;
    pEncParaCfg->vcpi_psw_thr0 = 20;
    pEncParaCfg->vcpi_psw_thr1 = 50;
    pEncParaCfg->vcpi_psw_thr2 = 150;
    pEncParaCfg->tr_weightx_2 = 12;
    pEncParaCfg->tr_weightx_1 = 8;
    pEncParaCfg->tr_weightx_0 = 4;
    pEncParaCfg->tr_weighty_2 = 12;
    pEncParaCfg->tr_weighty_1 = 8;
    pEncParaCfg->tr_weighty_0 = 4;
    pEncParaCfg->sr_weight_2 = 2;
    pEncParaCfg->sr_weight_1 = 4;
    pEncParaCfg->sr_weight_0 = 6;
    pEncParaCfg->skin_v_min_thr = 135;
    pEncParaCfg->skin_v_max_thr = 160;
    pEncParaCfg->skin_u_min_thr = 100;
    pEncParaCfg->skin_u_max_thr = 127;
    pEncParaCfg->still_scene_thr = 0;
    pEncParaCfg->high_edge_cnt = 6;
    pEncParaCfg->high_edge_thr = 40;
    pEncParaCfg->skin_num = 200;
    pEncParaCfg->refld_vcpi2cont_title_en = 1;
    pEncParaCfg->vcpi_high3pre_en = 0;
    pEncParaCfg->vcpi_rect3_mod = 1;
    pEncParaCfg->vcpi_rect2_mod = 1;
    pEncParaCfg->vcpi_rect1_mod = 1;
    //	pEncParaCfg->vcpi_inter16x16_en = 1;
    pEncParaCfg->vcpi_inter8x8_en = 1;
    pEncParaCfg->vcpi_rect0_vstep = 0;
    pEncParaCfg->vcpi_rect0_hstep = 0;
    pEncParaCfg->vcpi_rect1_vstep = 0;
    pEncParaCfg->vcpi_rect1_hstep = 0;
    pEncParaCfg->vcpi_rect2_vstep = 1;
    pEncParaCfg->vcpi_rect2_hstep = 1;
    pEncParaCfg->vcpi_rect3_vstep = 0;
    pEncParaCfg->vcpi_rect3_hstep = 0;
    pEncParaCfg->vcpi_start_thr = 1500;
    pEncParaCfg->vcpi_intra_thr = 4096;
    pEncParaCfg->vcpi_lambdaoff16 = 0;
    pEncParaCfg->vcpi_lambdaoff8 = 0;
    pEncParaCfg->vcpi_lowpow_fme_thr1 = 16;
    pEncParaCfg->vcpi_lowpow_fme_thr0 = 10;
    pEncParaCfg->max_qp = 51;
    pEncParaCfg->min_qp = 0;
    pEncParaCfg->ave_lcu_bits = 100;

    pEncParaCfg->qp_delta = 4;
    pEncParaCfg->cu_qp_delta_thresh3 = 18;
    pEncParaCfg->cu_qp_delta_thresh2 = 15;
    pEncParaCfg->cu_qp_delta_thresh1 = 4;
    pEncParaCfg->cu_qp_delta_thresh0 = 1;
    pEncParaCfg->cu_qp_delta_thresh7 = 44;
    pEncParaCfg->cu_qp_delta_thresh6 = 34;
    pEncParaCfg->cu_qp_delta_thresh5 = 27;
    pEncParaCfg->cu_qp_delta_thresh4 = 22;
    pEncParaCfg->cu_qp_delta_thresh11 = 255;
    pEncParaCfg->cu_qp_delta_thresh10 = 255;
    pEncParaCfg->cu_qp_delta_thresh9 = 255;
    pEncParaCfg->cu_qp_delta_thresh8 = 255;

    pEncParaCfg->strong_edge_qp_delta = 2;
    pEncParaCfg->skin_qp_delta = 3;
    pEncParaCfg->lambda00 = 18;
    pEncParaCfg->lambda01 = 22;
    pEncParaCfg->lambda02 = 28;
    pEncParaCfg->lambda03 = 36;
    pEncParaCfg->lambda04 = 45;
    pEncParaCfg->lambda05 = 57;
    pEncParaCfg->lambda06 = 72;
    pEncParaCfg->lambda07 = 91;
    pEncParaCfg->lambda08 = 115;
    pEncParaCfg->lambda09 = 145;
    pEncParaCfg->lambda10 = 183;
    pEncParaCfg->lambda11 = 231;
    pEncParaCfg->lambda12 = 291;
    pEncParaCfg->lambda13 = 367;
    pEncParaCfg->lambda14 = 463;
    pEncParaCfg->lambda15 = 583;
    pEncParaCfg->lambda16 = 735;
    pEncParaCfg->lambda17 = 926;
    pEncParaCfg->lambda18 = 1167;
    pEncParaCfg->lambda19 = 1470;
    pEncParaCfg->lambda20 = 1853;
    pEncParaCfg->lambda21 = 2334;
    pEncParaCfg->lambda22 = 2941;
    pEncParaCfg->lambda23 = 3706;
    pEncParaCfg->lambda24 = 4666;

    pEncParaCfg->lambda25 = 5883;
    pEncParaCfg->lambda26 = 7412;
    pEncParaCfg->lambda27 = 9338;
    pEncParaCfg->lambda28 = 11766;
    pEncParaCfg->lambda29 = 14824;
    pEncParaCfg->lambda30 = 18677;
    pEncParaCfg->lambda31 = 23532;
    pEncParaCfg->lambda32 = 29649;
    pEncParaCfg->lambda33 = 37355;
    pEncParaCfg->lambda34 = 47065;
    pEncParaCfg->lambda35 = 59298;
    pEncParaCfg->lambda36 = 74711;
    pEncParaCfg->lambda37 = 94130;
    pEncParaCfg->lambda38 = 118596;
    pEncParaCfg->lambda39 = 131071;
    pEncParaCfg->lambda40 = 193;
    pEncParaCfg->lambda41 = 216;
    pEncParaCfg->lambda42 = 243;
    pEncParaCfg->lambda43 = 273;
    pEncParaCfg->lambda44 = 306;
    pEncParaCfg->lambda45 = 344;
    pEncParaCfg->lambda46 = 386;
    pEncParaCfg->lambda47 = 433;
    pEncParaCfg->lambda48 = 487;
    pEncParaCfg->lambda49 = 546;
    pEncParaCfg->lambda50 = 613;
    pEncParaCfg->lambda51 = 688;
    pEncParaCfg->lambda52 = 773;
    pEncParaCfg->lambda53 = 867;
    pEncParaCfg->lambda54 = 974;
    pEncParaCfg->lambda55 = 1093;
    pEncParaCfg->lambda56 = 1227;
    pEncParaCfg->lambda57 = 1377;
    pEncParaCfg->lambda58 = 1546;
    pEncParaCfg->lambda59 = 1735;
    pEncParaCfg->lambda60 = 1948;
    pEncParaCfg->lambda61 = 2186;
    pEncParaCfg->lambda62 = 2454;
    pEncParaCfg->lambda63 = 2755;
    pEncParaCfg->lambda64 = 3092;
    pEncParaCfg->lambda65 = 3471;
    pEncParaCfg->lambda66 = 3896;
    pEncParaCfg->lambda67 = 4373;
    pEncParaCfg->lambda68 = 4908;
    pEncParaCfg->lambda69 = 5510;
    pEncParaCfg->lambda70 = 6184;
    pEncParaCfg->lambda71 = 6942;
    pEncParaCfg->lambda72 = 7792;
    pEncParaCfg->lambda73 = 8746;
    pEncParaCfg->lambda74 = 9817;
    pEncParaCfg->lambda75 = 11020;
    pEncParaCfg->lambda76 = 12369;
    pEncParaCfg->lambda77 = 13884;
    pEncParaCfg->lambda78 = 15584;
    pEncParaCfg->lambda79 = 17493;
    pEncParaCfg->inter_avail = 0;
    pEncParaCfg->intra_smooth = 1;
    pEncParaCfg->intra_bit_weight = 13;
    pEncParaCfg->intra_cu4_mode1 = 7;
    pEncParaCfg->intra_cu4_mode0 = 4294967295;
    pEncParaCfg->intra_cu8_mode1 = 7;
    pEncParaCfg->intra_cu8_mode0 = 4294967295;
    pEncParaCfg->intra_cu16_mode1 = 7;
    pEncParaCfg->intra_cu16_mode0 = 4294967295;
    pEncParaCfg->intra_cu32_mode1 = 7;
    pEncParaCfg->intra_cu32_mode0 = 4294967295;
    pEncParaCfg->tmv_en = 1;

    pEncParaCfg->q_scaling_waddr = 0;
    pEncParaCfg->q_scaling_wdata = 0;
    pEncParaCfg->vcpi2cu_qp_min_cu_size = 2;
    pEncParaCfg->vcpi2cu_tq_bypass_enabled_flag = 0;
    pEncParaCfg->vcpi2pu_log2_max_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2pu_log2_min_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2res_tf_skip_enabled_flag = 0;

    pEncParaCfg->nal_unit_head = 0;
    pEncParaCfg->max_num_mergecand = 2;
    pEncParaCfg->slchdr_size_part2 = 0;
    pEncParaCfg->slchdr_size_part1 = 0;
    pEncParaCfg->slchdr_part1 = 0;
    pEncParaCfg->slchdr_part2_seg1 = 0;
    pEncParaCfg->slchdr_part2_seg2 = 0;
    pEncParaCfg->slchdr_part2_seg3 = 0;
    pEncParaCfg->slchdr_part2_seg4 = 0;
    pEncParaCfg->slchdr_part2_seg5 = 0;
    pEncParaCfg->slchdr_part2_seg6 = 0;
    pEncParaCfg->slchdr_part2_seg7 = 0;
    pEncParaCfg->slchdr_part2_seg8 = 0;
    pEncParaCfg->strmbuflen = 10000000;
    pEncParaCfg->ptbits_en = 0;
    pEncParaCfg->ptbits = 0;

    pEncParaCfg->vcpi_slchdrstrm0 = 0;
    pEncParaCfg->vcpi_slchdrstrm1 = 0;
    pEncParaCfg->vcpi_slchdrstrm2 = 0;
    pEncParaCfg->vcpi_slchdrstrm3 = 0;
    pEncParaCfg->vcpi_reorderstrm0 = 0;
    pEncParaCfg->vcpi_reorderstrm1 = 0;
    pEncParaCfg->vcpi_markingstrm0 = 0;
    pEncParaCfg->vcpi_markingstrm1 = 0;
    pEncParaCfg->vcpi_parabit = 0;
    pEncParaCfg->vcpi_reorderbit = 0;
    pEncParaCfg->vcpi_markingbit = 0;
    pEncParaCfg->vcpi_svc_strm = 0;
    pEncParaCfg->vcpi_svc_en = 0;
    pEncParaCfg->curld_filter_hshift = 2;
    pEncParaCfg->curld_filter_hrnd = 2;
    pEncParaCfg->curld_filter_h3 = 1;
    pEncParaCfg->curld_filter_h2 = 1;
    pEncParaCfg->curld_filter_h1 = 1;
    pEncParaCfg->curld_filter_h0 = 1;
    pEncParaCfg->curld_filter_vshift = 2;
    pEncParaCfg->curld_filter_vrnd = 2;
    pEncParaCfg->curld_filter_v3 = 1;
    pEncParaCfg->curld_filter_v2 = 1;
    pEncParaCfg->curld_filter_v1 = 1;
    pEncParaCfg->curld_filter_v0 = 1;
    pEncParaCfg->curld_y_filt_01coef = 4783;
    pEncParaCfg->curld_y_filt_00coef = 15743;
    pEncParaCfg->curld_y_filt_03coef = 16358;
    pEncParaCfg->curld_y_filt_02coef = 16364;
    pEncParaCfg->curld_y_filt_11coef = 4265;
    pEncParaCfg->curld_y_filt_10coef = 15573;
    pEncParaCfg->curld_y_filt_13coef = 16259;
    pEncParaCfg->curld_y_filt_12coef = 568;
    pEncParaCfg->curld_y_filt_21coef = 3855;
    pEncParaCfg->curld_y_filt_20coef = 15584;
    pEncParaCfg->curld_y_filt_23coef = 16101;
    pEncParaCfg->curld_y_filt_22coef = 1324;
    pEncParaCfg->curld_y_filt_31coef = 3058;
    pEncParaCfg->curld_y_filt_30coef = 15716;
    pEncParaCfg->curld_y_filt_33coef = 15937;
    pEncParaCfg->curld_y_filt_32coef = 2182;
    pEncParaCfg->curld_c_filt_01coef = 4059;
    pEncParaCfg->curld_c_filt_00coef = 16242;
    pEncParaCfg->curld_c_filt_03coef = 16380;
    pEncParaCfg->curld_c_filt_02coef = 183;
    pEncParaCfg->curld_c_filt_11coef = 3783;
    pEncParaCfg->curld_c_filt_10coef = 16074;
    pEncParaCfg->curld_c_filt_13coef = 16344;
    pEncParaCfg->curld_c_filt_12coef = 664;
    pEncParaCfg->curld_c_filt_21coef = 3286;
    pEncParaCfg->curld_c_filt_20coef = 16036;
    pEncParaCfg->curld_c_filt_23coef = 16262;
    pEncParaCfg->curld_c_filt_22coef = 1270;
    pEncParaCfg->curld_c_filt_31coef = 2649;
    pEncParaCfg->curld_c_filt_30coef = 16085;
    pEncParaCfg->curld_c_filt_33coef = 16177;
    pEncParaCfg->curld_c_filt_32coef = 1953;
    pEncParaCfg->curld_clip_en = 0;//for gc test
    pEncParaCfg->clip_chrm_max = 235;
    pEncParaCfg->clip_chrm_min = 16;
    pEncParaCfg->clip_luma_max = 240;
    pEncParaCfg->clip_luma_min = 16;
    pEncParaCfg->vcpi_coeff_ry = 263;
    pEncParaCfg->vcpi_coeff_gy = 516;
    pEncParaCfg->vcpi_coeff_by = 100;
    pEncParaCfg->vcpi_coeff_rcb = (HI_S32)4294967145;
    pEncParaCfg->vcpi_coeff_gcb = (HI_S32)4294966998;
    pEncParaCfg->vcpi_coeff_bcb = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_rcr = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_gcr = (HI_S32)4294966919;
    pEncParaCfg->vcpi_coeff_bcr = (HI_S32)4294967223;
    pEncParaCfg->vcpi_rgb_shift = 10;
    pEncParaCfg->vcpi_rgb_rndy = 16;
    pEncParaCfg->vcpi_rgb_rndcb = 128;
    pEncParaCfg->vcpi_rgb_rndcr = 128;
    pEncParaCfg->vcpi_rgb_clip_en = 0;//for gc test
    pEncParaCfg->vcpi_rgb_clpmax = 235;
    pEncParaCfg->vcpi_rgb_clpmin = 16;

    pEncParaCfg->vcpi_protocol_clkgate_en = 1;
    pEncParaCfg->curld_lowdly_en = 0;
    pEncParaCfg->curld_read_interval = 0;
    pEncParaCfg->vcpi_pblk_pre_mvy_thr = 2;
    pEncParaCfg->vcpi_pblk_pre_mvx_thr = 2;
    pEncParaCfg->refld_ddr_cross_idx = 0;
    pEncParaCfg->recst_ddr_cross_idx = 0;
    pEncParaCfg->vcpi_wide_narrow_en = 0;
    pEncParaCfg->vcpi_wtmax = 0xff;
    pEncParaCfg->vcpi_rtmax = 0xff;
    pEncParaCfg->vcpi_ch00_rrmax = 0xf;
    pEncParaCfg->vcpi_ch01_rrmax = 0xf;
    pEncParaCfg->vcpi_ch02_rrmax = 0xf;
    pEncParaCfg->vcpi_ch03_rrmax = 0xf;
    pEncParaCfg->vcpi_ch04_rrmax = 0xf;
    pEncParaCfg->vcpi_ch05_rrmax = 0xf;
    pEncParaCfg->vcpi_ch06_rrmax = 0xf;
    pEncParaCfg->vcpi_ch07_rrmax = 0xf;
    pEncParaCfg->vcpi_ch08_rrmax = 0xf;
    pEncParaCfg->vcpi_ch09_rrmax = 0xf;
    pEncParaCfg->vcpi_ch10_rrmax = 0xf;
    pEncParaCfg->vcpi_ch11_rrmax = 0xf;
    pEncParaCfg->vcpi_ch12_rrmax = 0xf;
    pEncParaCfg->vcpi_ch00_wrmax = 0xf;
    pEncParaCfg->vcpi_ch01_wrmax = 0xf;
    pEncParaCfg->vcpi_ch02_wrmax = 0xf;
    pEncParaCfg->vcpi_ch03_wrmax = 0xf;
    pEncParaCfg->vcpi_ch04_wrmax = 0xf;
    pEncParaCfg->vcpi_ch05_wrmax = 0xf;
    pEncParaCfg->vcpi_ch06_wrmax = 0xf;
    pEncParaCfg->vcpi_ch07_wrmax = 0xf;
    pEncParaCfg->vcpi_ch08_wrmax = 0xf;
    pEncParaCfg->vcpi_ch09_wrmax = 0xf;
    pEncParaCfg->vcpi_ch10_wrmax = 0xf;
    pEncParaCfg->vcpi_ch11_wrmax = 0xf;
    pEncParaCfg->vcpi_ch12_wrmax = 0xf;
    pEncParaCfg->vcpi_ch13_wrmax = 0xf;
    pEncParaCfg->vcpi_ch14_wrmax = 0xf;

    if (pEncParaCfg->vcpi_rec_cmp_en != pEncParaCfg->vcpi_ref_cmp_en)
    {
        pEncParaCfg->vcpi_rec_cmp_en = 0;
        pEncParaCfg->vcpi_ref_cmp_en = 0;
    }


    pEncParaCfg->curld_y_filt_col_01coef = 0;
    pEncParaCfg->curld_y_filt_col_00coef = 0;
    pEncParaCfg->curld_y_filt_col_03coef = 0;
    pEncParaCfg->curld_y_filt_col_02coef = 0;
    pEncParaCfg->curld_y_filt_col_11coef = 0;
    pEncParaCfg->curld_y_filt_col_10coef = 0;
    pEncParaCfg->curld_y_filt_col_13coef = 0;
    pEncParaCfg->curld_y_filt_col_12coef = 0;
    pEncParaCfg->curld_y_filt_col_21coef = 0;
    pEncParaCfg->curld_y_filt_col_20coef = 0;
    pEncParaCfg->curld_y_filt_col_23coef = 0;
    pEncParaCfg->curld_y_filt_col_22coef = 0;
    pEncParaCfg->curld_y_filt_col_31coef = 0;
    pEncParaCfg->curld_y_filt_col_30coef = 0;
    pEncParaCfg->curld_y_filt_col_33coef = 0;
    pEncParaCfg->curld_y_filt_col_32coef = 0;
    pEncParaCfg->curld_c_filt_col_01coef = 0;
    pEncParaCfg->curld_c_filt_col_00coef = 0;
    pEncParaCfg->curld_c_filt_col_03coef = 0;
    pEncParaCfg->curld_c_filt_col_02coef = 0;
    pEncParaCfg->curld_c_filt_col_11coef = 0;
    pEncParaCfg->curld_c_filt_col_10coef = 0;
    pEncParaCfg->curld_c_filt_col_13coef = 0;
    pEncParaCfg->curld_c_filt_col_12coef = 0;
    pEncParaCfg->curld_c_filt_col_21coef = 0;
    pEncParaCfg->curld_c_filt_col_20coef = 0;
    pEncParaCfg->curld_c_filt_col_23coef = 0;
    pEncParaCfg->curld_c_filt_col_22coef = 0;
    pEncParaCfg->curld_c_filt_col_31coef = 0;
    pEncParaCfg->curld_c_filt_col_30coef = 0;
    pEncParaCfg->curld_c_filt_col_33coef = 0;
    pEncParaCfg->curld_c_filt_col_32coef = 0;


    pEncParaCfg->comn0_ptw_pf = 0x3;
    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->comn0_intns_ptw_ns_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_trans_msk = 0x0;
    pEncParaCfg->comn0_intns_tlbmiss_msk = 0x0;
    pEncParaCfg->comn0_intns_ext_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_smr0_ptw_qos = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn2_smr0_nscfg = 0x1;
    pEncParaCfg->comn2_smr1_nscfg = 0x1;
    pEncParaCfg->comn2_smr2_nscfg = 0x1;
    pEncParaCfg->comn2_smr3_nscfg = 0x1;
    pEncParaCfg->comn2_smr4_nscfg = 0x1;
    pEncParaCfg->comn2_smr5_nscfg = 0x1;
    pEncParaCfg->comn2_smr6_nscfg = 0x1;
    pEncParaCfg->comn2_smr7_nscfg = 0x1;
    pEncParaCfg->comn2_smr8_nscfg = 0x1;
    pEncParaCfg->comn2_smr9_nscfg = 0x1;
    pEncParaCfg->comn2_smr10_nscfg = 0x1;
    pEncParaCfg->comn2_smr11_nscfg = 0x1;
    pEncParaCfg->comn2_smr12_nscfg = 0x1;
    pEncParaCfg->comn2_smr13_nscfg = 0x1;
    pEncParaCfg->comn2_smr14_nscfg = 0x1;
    pEncParaCfg->comn2_smr15_nscfg = 0x1;
    pEncParaCfg->comn2_smr16_nscfg = 0x1;
    pEncParaCfg->comn2_smr17_nscfg = 0x1;
    pEncParaCfg->comn3_ints_ptw_ns_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_trans_msk = 0x0;
    pEncParaCfg->comn3_ints_tlbmiss_msk = 0x0;
    pEncParaCfg->comn3_ints_ext_msk = 0x0;
    pEncParaCfg->comn3_ints_permis_msk = 0x0;

    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->glb_bypass =  pEncParaCfg->comn0_glb_bypass;

    pEncParaCfg->comn0_smr18_bypass = 0;
    pEncParaCfg->comn0_smr19_bypass = 0;
    pEncParaCfg->comn0_smr20_bypass = 0;
    pEncParaCfg->comn0_smr21_bypass = 0;
    pEncParaCfg->comn0_smr22_bypass = 0;
    pEncParaCfg->comn0_smr23_bypass = 0;
    pEncParaCfg->comn0_smr24_bypass = 0;
    pEncParaCfg->comn0_smr25_bypass = 0;
    pEncParaCfg->comn0_smr26_bypass = 0;
    pEncParaCfg->comn0_smr27_bypass = 0;
    pEncParaCfg->comn0_smr28_bypass = 0;
    pEncParaCfg->comn0_smr29_bypass = 0;
    pEncParaCfg->comn0_smr30_bypass = 0;
    pEncParaCfg->comn0_smr31_bypass = 0;
    pEncParaCfg->comn0_smr32_bypass = 0;
    pEncParaCfg->comn0_smr33_bypass = 0;
    pEncParaCfg->comn0_smr34_bypass = 0;
    pEncParaCfg->comn0_smr35_bypass = 0;
    pEncParaCfg->sid18_bypass = 0;
    pEncParaCfg->sid19_bypass = 0;
    pEncParaCfg->sid20_bypass = 0;
    pEncParaCfg->sid21_bypass = 0;
    pEncParaCfg->sid22_bypass = 0;
    pEncParaCfg->sid23_bypass = 0;
    pEncParaCfg->sid24_bypass = 0;
    pEncParaCfg->sid25_bypass = 0;
    pEncParaCfg->sid26_bypass = 0;
    pEncParaCfg->sid27_bypass = 0;
    pEncParaCfg->sid28_bypass = 0;
    pEncParaCfg->sid29_bypass = 0;
    pEncParaCfg->sid30_bypass = 0;
    pEncParaCfg->sid31_bypass = 0;
    pEncParaCfg->sid32_bypass = 0;
    pEncParaCfg->sid33_bypass = 0;
    pEncParaCfg->sid34_bypass = 0;
    pEncParaCfg->sid35_bypass = 0;

    pEncParaCfg->glb_scr = 1;
    return 0;
}

HI_S32 VENC_DRV_EflInitEncParaCfgHevc_LowPwr1( VeduEfl_EncPara_S  *pEncPara)
{
	VeduEfl_EncPara_S_Cfg  *pEncParaCfg = (VeduEfl_EncPara_S_Cfg*)kmalloc(sizeof(VeduEfl_EncPara_S_Cfg),GFP_KERNEL);
    if(NULL == pEncParaCfg)
    {
        return -1;
    }
    memset(pEncParaCfg, 0 ,sizeof(VeduEfl_EncPara_S_Cfg));
    pEncPara->pstCfg_EncPara = pEncParaCfg;

    pEncParaCfg->enable_cfg_err = 0;
    pEncParaCfg->enable_vedu_timeout = 0;
    pEncParaCfg->enable_vedu_step = 0;
    pEncParaCfg->enable_vedu_brkpt = 0;
    pEncParaCfg->enable_vedu_slice_end = 1;// enable sliec IRQ需同步修改vcpi_slice_int_en
    //pEncParaCfg->enable_vedu_slice_end = 0;
    pEncParaCfg->enable_ve_pbitsover = 0;
    pEncParaCfg->enable_ve_buffull = 0;
    #ifndef IRQ_EN
    pEncParaCfg->enable_ve_eop = 0;
    #else
    pEncParaCfg->enable_ve_eop = 1;//to do for irq test
    #endif
    pEncParaCfg->clr_cfg_err = 0;
    pEncParaCfg->clr_vedu_timeout = 0;
    pEncParaCfg->clr_vedu_step = 0;
    pEncParaCfg->clr_vedu_brkpt = 0;
    pEncParaCfg->clr_vedu_slice_end = 0;
    pEncParaCfg->clr_ve_pbitsover = 0;
    pEncParaCfg->clr_ve_buffull = 0;
    pEncParaCfg->clr_ve_eop = 0;
    pEncParaCfg->vcpi_vstep = 0;
    pEncParaCfg->vcpi_vstart = 0;
    pEncParaCfg->vcpi_dbgmod = 0;
    pEncParaCfg->vcpi_bkp_en = 0;
    pEncParaCfg->vcpi_time_en = 0;
    pEncParaCfg->vcpi_lcu_size = 2;
    pEncParaCfg->vcpi_tiles_en = 0;
    pEncParaCfg->vcpi_trans_mode = 0;
    pEncParaCfg->vcpi_pskp_en = 1;
    pEncParaCfg->vcpi_idr_pic = 0;
    pEncParaCfg->vcpi_entropy_mode = 0;
    pEncParaCfg->vcpi_img_improve_en = 1;

    pEncParaCfg->vcpi_rec_cmp_en = 1;
    pEncParaCfg->vcpi_ref_cmp_en = 1;//

    pEncParaCfg->vcpi_sao_chroma = 1;
    pEncParaCfg->vcpi_sao_luma = 1;
    pEncParaCfg->vcpi_slice_int_en = 1;// enable sliec IRQ需同步修改vcpi_slice_int_en

    pEncParaCfg->vcpi_protocol = 0;
    pEncParaCfg->vcpi_cfg_mode = 0;
    pEncParaCfg->vcpi_lcu_time_sel = 1;
    pEncParaCfg->vcpi_vedsel = 0;
    pEncParaCfg->vcpi_tile_height = 0;
    pEncParaCfg->vcpi_tile_width = 0;
    pEncParaCfg->vcpi_multislc_en = 0;
    pEncParaCfg->vcpi_slcspilt_mod = 1;
    pEncParaCfg->vcpi_slice_size = 12;
    pEncParaCfg->vcpi_frm_qp = 26;
    pEncParaCfg->vcpi_cb_qp_offset = 0;
    pEncParaCfg->vcpi_cr_qp_offset = 0;
    pEncParaCfg->vcpi_cnt_clr = 0;
    pEncParaCfg->vcpi_frame_no = 4294967295;
    pEncParaCfg->vcpi_dblk_filter_flag = 0;
    pEncParaCfg->vcpi_dblk_alpha = 0;
    pEncParaCfg->vcpi_dblk_beta = 0;
    pEncParaCfg->vcpi_mem_clkgate_en = 1;
    pEncParaCfg->vcpi_clkgate_en = 2;
    pEncParaCfg->fme_gtck_en = 1;
    pEncParaCfg->mrg_gtck_en = 1;
    pEncParaCfg->tqitq_gtck_en = 1;
    pEncParaCfg->vcpi_ime_lowpow = 1;
    pEncParaCfg->vcpi_fme_lowpow = 1;
    pEncParaCfg->vcpi_intra_lowpow = 1;
    pEncParaCfg->vcpi_imgheight_pix = 480;
    pEncParaCfg->vcpi_imgwidth_pix = 640;
    pEncParaCfg->vcpi_bp_lcu_y = 0;
    pEncParaCfg->vcpi_bp_lcu_x = 0;
    pEncParaCfg->vedu_timeout = 4294967295;
    pEncParaCfg->vcpi_w_outstanding = 3;
    pEncParaCfg->vcpi_r_outstanding = 31;//31  0615 FPGA环境目前只支持0-7
    pEncParaCfg->vcpi_sw_height = 32;
    pEncParaCfg->vcpi_sw_width = 72;
    pEncParaCfg->vcpi_tmv_wr_rd_avail = 3;
    pEncParaCfg->vcpi_cross_tile = 1;
    pEncParaCfg->vcpi_cross_slice = 1;
    pEncParaCfg->osd_en = 0;
    pEncParaCfg->osd7_absqp = 0;
    pEncParaCfg->osd6_absqp = 0;
    pEncParaCfg->osd5_absqp = 0;
    pEncParaCfg->osd4_absqp = 0;
    pEncParaCfg->osd3_absqp = 0;
    pEncParaCfg->osd2_absqp = 0;
    pEncParaCfg->osd1_absqp = 0;
    pEncParaCfg->osd0_absqp = 0;
    pEncParaCfg->osd7_en = 0;
    pEncParaCfg->osd6_en = 0;
    pEncParaCfg->osd5_en = 0;
    pEncParaCfg->osd4_en = 0;
    pEncParaCfg->osd3_en = 0;
    pEncParaCfg->osd2_en = 0;
    pEncParaCfg->osd1_en = 0;
    pEncParaCfg->osd0_en = 0;
    pEncParaCfg->osd0_y = 0;
    pEncParaCfg->osd0_x = 0;
    pEncParaCfg->osd1_y = 0;
    pEncParaCfg->osd1_x = 0;
    pEncParaCfg->osd2_y = 0;
    pEncParaCfg->osd2_x = 0;
    pEncParaCfg->osd3_y = 0;
    pEncParaCfg->osd3_x = 0;
    pEncParaCfg->osd4_y = 0;
    pEncParaCfg->osd4_x = 0;
    pEncParaCfg->osd5_y = 0;
    pEncParaCfg->osd5_x = 0;
    pEncParaCfg->osd6_y = 0;
    pEncParaCfg->osd6_x = 0;
    pEncParaCfg->osd7_y = 0;
    pEncParaCfg->osd7_x = 0;
    pEncParaCfg->osd0_h = 0;
    pEncParaCfg->osd0_w = 0;
    pEncParaCfg->osd1_h = 0;
    pEncParaCfg->osd1_w = 0;
    pEncParaCfg->osd2_h = 0;
    pEncParaCfg->osd2_w = 0;
    pEncParaCfg->osd3_h = 0;
    pEncParaCfg->osd3_w = 0;
    pEncParaCfg->osd4_h = 0;
    pEncParaCfg->osd4_w = 0;
    pEncParaCfg->osd5_h = 0;
    pEncParaCfg->osd5_w = 0;
    pEncParaCfg->osd6_h = 0;
    pEncParaCfg->osd6_w = 0;
    pEncParaCfg->osd7_h = 0;
    pEncParaCfg->osd7_w = 0;
    pEncParaCfg->osd7_layer_id = 0;
    pEncParaCfg->osd6_layer_id = 0;
    pEncParaCfg->osd5_layer_id = 0;
    pEncParaCfg->osd4_layer_id = 0;
    pEncParaCfg->osd3_layer_id = 0;
    pEncParaCfg->osd2_layer_id = 0;
    pEncParaCfg->osd1_layer_id = 0;
    pEncParaCfg->osd0_layer_id = 0;
    pEncParaCfg->osd3_qp = 0;
    pEncParaCfg->osd2_qp = 0;
    pEncParaCfg->osd1_qp = 0;
    pEncParaCfg->osd0_qp = 0;
    pEncParaCfg->osd7_qp = 0;
    pEncParaCfg->osd6_qp = 0;
    pEncParaCfg->osd5_qp = 0;
    pEncParaCfg->osd4_qp = 0;
    pEncParaCfg->curld_tunlcell_addr = 0;
    pEncParaCfg->curld_y_addr = 2415919104;
    pEncParaCfg->curld_c_addr = 2483027968;
    pEncParaCfg->curld_v_addr = 2499805184;
    pEncParaCfg->curld_yh_addr = 2821718016;
    pEncParaCfg->curld_ch_addr = 2821849088;
    pEncParaCfg->curld_y_stride = 640;
    pEncParaCfg->curld_c_stride = 640;
    pEncParaCfg->curld_yh_stride = 4096;
    pEncParaCfg->curld_ch_stride = 4096;
    pEncParaCfg->recst_yaddr = 2516582400;
    pEncParaCfg->recst_caddr = 2583691264;
    pEncParaCfg->recst_cstride = 4096;
    pEncParaCfg->recst_ystride = 4096;
    pEncParaCfg->recst_yh_addr = 2821980160;
    pEncParaCfg->recst_ch_addr = 2823028736;
    pEncParaCfg->recst_head_stride = 4096;
    pEncParaCfg->refld_luma_addr = 2617245696;
    pEncParaCfg->refld_chroma_addr = 2684354560;
    pEncParaCfg->refld_luma_vstride = 4096;
    pEncParaCfg->refld_chroma_vstride = 4096;
    pEncParaCfg->refld_yh_addr = 2824077312;
    pEncParaCfg->refld_ch_addr = 2825125888;
    pEncParaCfg->refld_yh_stride = 4096;
    pEncParaCfg->refld_ch_stride = 4096;
    pEncParaCfg->vcpi_pmeld_addr = 2804940800;
    pEncParaCfg->vcpi_pmest_addr = 2788163584;
    pEncParaCfg->upst_address = 2789212160;
    pEncParaCfg->mvst_address = 2786066432;
    pEncParaCfg->mvld_address = 2787115008;
    pEncParaCfg->csst_strmaddr = 2717908992;
    pEncParaCfg->csst_swptraddr = 2785017856;
    pEncParaCfg->csst_srptraddr = 2785018112;
    pEncParaCfg->vcpi_package_sel = 0;
    pEncParaCfg->vcpi_str_fmt = 0;
    pEncParaCfg->vcpi_blk_type = 0;
    pEncParaCfg->vcpi_store_mode = 0;
    pEncParaCfg->vcpi_scale_en = 0;
    pEncParaCfg->vcpi_crop_en = 0;
    pEncParaCfg->vcpi_crop_ystart = 0;
    pEncParaCfg->vcpi_crop_xstart = 0;
    pEncParaCfg->vcpi_crop_yend = 0;
    pEncParaCfg->vcpi_crop_xend = 0;
    pEncParaCfg->vcpi_yscale = 0;
    pEncParaCfg->vcpi_xscale = 0;
    pEncParaCfg->vcpi_oriheight_pix = 480;
    pEncParaCfg->vcpi_oriwidth_pix = 640;
    pEncParaCfg->vcpi_mrg_cu_en = 15;
    pEncParaCfg->vcpi_fme_cu_en = 15;
    pEncParaCfg->vcpi_ipcm_en = 1;
    pEncParaCfg->vcpi_intra_cu_en = 15;
    pEncParaCfg->vcpi_byte_stuffing = 0;
    pEncParaCfg->vcpi_num_refidx = 0;
    pEncParaCfg->vcpi_cabac_init_idc = 0;
    pEncParaCfg->vcpi_ref_idc = 0;
    pEncParaCfg->vcpi_ext_edge_en = 1;
    pEncParaCfg->vcpi_force_inter = 0;
    pEncParaCfg->vcpi_pblk_pre_en = 1;
    pEncParaCfg->vcpi_iblk_pre_en = 1;
    pEncParaCfg->vcpi_pblk_pre_cost_thr = 400;
    pEncParaCfg->vcpi_iblk_pre_cost_thr = 300;
    pEncParaCfg->vcpi_iblk_pre_mvy_thr = 2;
    pEncParaCfg->vcpi_iblk_pre_mvx_thr = 2;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr1 = 4;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr0 = 4;
    pEncParaCfg->vcpi_win0_height = 8;
    pEncParaCfg->vcpi_win0_width = 8;
    pEncParaCfg->vcpi_win1_height = 8;
    pEncParaCfg->vcpi_win1_width = 8;
    pEncParaCfg->vcpi_win2_height = 16;
    pEncParaCfg->vcpi_win2_width = 16;
    pEncParaCfg->vcpi_win3_height = 24;
    pEncParaCfg->vcpi_win3_width = 24;
    pEncParaCfg->vcpi_static_en = 1;
    pEncParaCfg->vcpi_highedge_en = 1;
    pEncParaCfg->vcpi_skin_en = 1;
    pEncParaCfg->vcpi_roi_en = 0;
    pEncParaCfg->region7keep = 0;
    pEncParaCfg->region6keep = 0;
    pEncParaCfg->region5keep = 0;
    pEncParaCfg->region4keep = 0;
    pEncParaCfg->region3keep = 0;
    pEncParaCfg->region2keep = 0;
    pEncParaCfg->region1keep = 0;
    pEncParaCfg->region0keep = 1;
    pEncParaCfg->absqp7 = 0;
    pEncParaCfg->absqp6 = 0;
    pEncParaCfg->absqp5 = 0;
    pEncParaCfg->absqp4 = 0;
    pEncParaCfg->absqp3 = 0;
    pEncParaCfg->absqp2 = 0;
    pEncParaCfg->absqp1 = 0;
    pEncParaCfg->absqp0 = 0;
    pEncParaCfg->region7en = 0;
    pEncParaCfg->region6en = 0;
    pEncParaCfg->region5en = 0;
    pEncParaCfg->region4en = 0;
    pEncParaCfg->region3en = 0;
    pEncParaCfg->region2en = 0;
    pEncParaCfg->region1en = 0;
    pEncParaCfg->region0en = 0;
    pEncParaCfg->roiqp3 = 0;
    pEncParaCfg->roiqp2 = 0;
    pEncParaCfg->roiqp1 = 0;
    pEncParaCfg->roiqp0 = 0;
    pEncParaCfg->roiqp7 = 0;
    pEncParaCfg->roiqp6 = 0;
    pEncParaCfg->roiqp5 = 0;
    pEncParaCfg->roiqp4 = 0;
    pEncParaCfg->size0_roiheight = 0;
    pEncParaCfg->size0_roiwidth = 0;
    pEncParaCfg->start0_roistarty = 0;
    pEncParaCfg->start0_roistartx = 0;
    pEncParaCfg->size1_roiheight = 0;
    pEncParaCfg->size1_roiwidth = 0;
    pEncParaCfg->start1_roistarty = 0;
    pEncParaCfg->start1_roistartx = 0;
    pEncParaCfg->size2_roiheight = 0;
    pEncParaCfg->size2_roiwidth = 0;
    pEncParaCfg->start2_roistarty = 0;
    pEncParaCfg->start2_roistartx = 0;
    pEncParaCfg->size3_roiheight = 0;
    pEncParaCfg->size3_roiwidth = 0;
    pEncParaCfg->start3_roistarty = 0;
    pEncParaCfg->start3_roistartx = 0;
    pEncParaCfg->size4_roiheight = 0;
    pEncParaCfg->size4_roiwidth = 0;
    pEncParaCfg->start4_roistarty = 0;
    pEncParaCfg->start4_roistartx = 0;
    pEncParaCfg->size5_roiheight = 0;
    pEncParaCfg->size5_roiwidth = 0;
    pEncParaCfg->start5_roistarty = 0;
    pEncParaCfg->start5_roistartx = 0;
    pEncParaCfg->size6_roiheight = 0;
    pEncParaCfg->size6_roiwidth = 0;
    pEncParaCfg->start6_roistarty = 0;
    pEncParaCfg->start6_roistartx = 0;
    pEncParaCfg->size7_roiheight = 0;
    pEncParaCfg->size7_roiwidth = 0;
    pEncParaCfg->start7_roistarty = 0;
    pEncParaCfg->start7_roistartx = 0;
    pEncParaCfg->lcu_target_bit = 0;
    pEncParaCfg->narrow_tile_width = 0;
    pEncParaCfg->lcu_performance_baseline = 0;
    pEncParaCfg->norm32_tr1_denois_max_num = 4;
    pEncParaCfg->norm32_coeff_protect_num = 255;
    pEncParaCfg->norm16_tr1_denois_max_num = 3;
    pEncParaCfg->norm16_coeff_protect_num = 64;
    pEncParaCfg->skin32_tr1_denois_max_num = 8;
    pEncParaCfg->skin32_coeff_protect_num = 32;
    pEncParaCfg->skin16_tr1_denois_max_num = 6;
    pEncParaCfg->skin16_coeff_protect_num = 16;
    pEncParaCfg->static32_tr1_denois_max_num = 8;
    pEncParaCfg->static32_coeff_protect_num = 16;
    pEncParaCfg->static16_tr1_denois_max_num = 6;
    pEncParaCfg->static16_coeff_protect_num = 8;
    pEncParaCfg->hedge32_tr1_denois_max_num = 8;
    pEncParaCfg->hedge32_coeff_protect_num = 32;
    pEncParaCfg->hedge16_tr1_denois_max_num = 6;
    pEncParaCfg->hedge16_coeff_protect_num = 16;
    pEncParaCfg->norm_intra_cu32_rdcost_offset = 0;
    pEncParaCfg->norm_intra_cu16_rdcost_offset = 0;
    pEncParaCfg->norm_intra_cu8_rdcost_offset = 0;
    pEncParaCfg->norm_intra_cu4_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu64_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu32_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu16_rdcost_offset = 0;
    pEncParaCfg->norm_mrg_cu8_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu64_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu32_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu16_rdcost_offset = 0;
    pEncParaCfg->norm_fme_cu8_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu32_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu16_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu8_rdcost_offset = 0;
    pEncParaCfg->skin_intra_cu4_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu64_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu32_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu16_rdcost_offset = 0;
    pEncParaCfg->skin_mrg_cu8_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu64_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu32_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu16_rdcost_offset = 0;
    pEncParaCfg->skin_fme_cu8_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu32_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu16_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu8_rdcost_offset = 0;
    pEncParaCfg->hedge_intra_cu4_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu64_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu32_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu16_rdcost_offset = 0;
    pEncParaCfg->hedge_mrg_cu8_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu64_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu32_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu16_rdcost_offset = 0;
    pEncParaCfg->hedge_fme_cu8_rdcost_offset = 0;
    pEncParaCfg->vcpi_new_cost_en = 1;
    pEncParaCfg->vcpi_psw_adapt_en = 1;
    pEncParaCfg->vcpi_psw_thr0 = 20;
    pEncParaCfg->vcpi_psw_thr1 = 1200;
    pEncParaCfg->vcpi_psw_thr2 = 1500;
    pEncParaCfg->tr_weightx_2 = 12;
    pEncParaCfg->tr_weightx_1 = 8;
    pEncParaCfg->tr_weightx_0 = 4;
    pEncParaCfg->tr_weighty_2 = 12;
    pEncParaCfg->tr_weighty_1 = 8;
    pEncParaCfg->tr_weighty_0 = 4;
    pEncParaCfg->sr_weight_2 = 4;
    pEncParaCfg->sr_weight_1 = 6;
    pEncParaCfg->sr_weight_0 = 8;
    pEncParaCfg->skin_v_min_thr = 135;
    pEncParaCfg->skin_v_max_thr = 160;
    pEncParaCfg->skin_u_min_thr = 100;
    pEncParaCfg->skin_u_max_thr = 127;
    pEncParaCfg->still_scene_thr = 0;
    pEncParaCfg->high_edge_cnt = 6;
    pEncParaCfg->high_edge_thr = 40;
    pEncParaCfg->skin_num = 200;
    pEncParaCfg->refld_vcpi2cont_title_en = 1;
    pEncParaCfg->vcpi_high3pre_en = 0;
    pEncParaCfg->vcpi_rect3_mod = 1;
    pEncParaCfg->vcpi_rect2_mod = 1;
    pEncParaCfg->vcpi_rect1_mod = 1;
    //pEncParaCfg->vcpi_inter16x16_en = 1;
    pEncParaCfg->vcpi_inter8x8_en = 1;
    pEncParaCfg->vcpi_rect0_vstep = 0;
    pEncParaCfg->vcpi_rect0_hstep = 0;
    pEncParaCfg->vcpi_rect1_vstep = 0;
    pEncParaCfg->vcpi_rect1_hstep = 0;
    pEncParaCfg->vcpi_rect2_vstep = 1;
    pEncParaCfg->vcpi_rect2_hstep = 1;
    pEncParaCfg->vcpi_rect3_vstep = 0;
    pEncParaCfg->vcpi_rect3_hstep = 0;
    pEncParaCfg->vcpi_start_thr = 1500;
    pEncParaCfg->vcpi_intra_thr = 4096;
    pEncParaCfg->vcpi_lambdaoff16 = 0;
    pEncParaCfg->vcpi_lambdaoff8 = 0;
    pEncParaCfg->vcpi_lowpow_fme_thr1 = 25;
    pEncParaCfg->vcpi_lowpow_fme_thr0 = 15;
    pEncParaCfg->max_qp = 51;
    pEncParaCfg->min_qp = 0;
    pEncParaCfg->ave_lcu_bits = 100;

    pEncParaCfg->qp_delta = 4;
    pEncParaCfg->cu_qp_delta_thresh3 = 18;
    pEncParaCfg->cu_qp_delta_thresh2 = 15;
    pEncParaCfg->cu_qp_delta_thresh1 = 4;
    pEncParaCfg->cu_qp_delta_thresh0 = 1;
    pEncParaCfg->cu_qp_delta_thresh7 = 44;
    pEncParaCfg->cu_qp_delta_thresh6 = 34;
    pEncParaCfg->cu_qp_delta_thresh5 = 27;
    pEncParaCfg->cu_qp_delta_thresh4 = 22;
    pEncParaCfg->cu_qp_delta_thresh11 = 255;
    pEncParaCfg->cu_qp_delta_thresh10 = 255;
    pEncParaCfg->cu_qp_delta_thresh9 = 255;
    pEncParaCfg->cu_qp_delta_thresh8 = 255;

    pEncParaCfg->strong_edge_qp_delta = 2;
    pEncParaCfg->skin_qp_delta = 3;
    pEncParaCfg->lambda00 = 18;
    pEncParaCfg->lambda01 = 22;
    pEncParaCfg->lambda02 = 28;
    pEncParaCfg->lambda03 = 36;
    pEncParaCfg->lambda04 = 45;
    pEncParaCfg->lambda05 = 57;
    pEncParaCfg->lambda06 = 72;
    pEncParaCfg->lambda07 = 91;
    pEncParaCfg->lambda08 = 115;
    pEncParaCfg->lambda09 = 145;
    pEncParaCfg->lambda10 = 183;
    pEncParaCfg->lambda11 = 231;
    pEncParaCfg->lambda12 = 291;
    pEncParaCfg->lambda13 = 367;
    pEncParaCfg->lambda14 = 463;
    pEncParaCfg->lambda15 = 583;
    pEncParaCfg->lambda16 = 735;
    pEncParaCfg->lambda17 = 926;
    pEncParaCfg->lambda18 = 1167;
    pEncParaCfg->lambda19 = 1470;
    pEncParaCfg->lambda20 = 1853;
    pEncParaCfg->lambda21 = 2334;
    pEncParaCfg->lambda22 = 2941;
    pEncParaCfg->lambda23 = 3706;
    pEncParaCfg->lambda24 = 4666;
    pEncParaCfg->lambda25 = 5883;
    pEncParaCfg->lambda26 = 7412;
    pEncParaCfg->lambda27 = 9338;
    pEncParaCfg->lambda28 = 11766;
    pEncParaCfg->lambda29 = 14824;
    pEncParaCfg->lambda30 = 18677;
    pEncParaCfg->lambda31 = 23532;
    pEncParaCfg->lambda32 = 29649;
    pEncParaCfg->lambda33 = 37355;
    pEncParaCfg->lambda34 = 47065;
    pEncParaCfg->lambda35 = 59298;
    pEncParaCfg->lambda36 = 74711;
    pEncParaCfg->lambda37 = 94130;
    pEncParaCfg->lambda38 = 118596;
    pEncParaCfg->lambda39 = 131071;
    pEncParaCfg->lambda40 = 193;
    pEncParaCfg->lambda41 = 216;
    pEncParaCfg->lambda42 = 243;
    pEncParaCfg->lambda43 = 273;
    pEncParaCfg->lambda44 = 306;
    pEncParaCfg->lambda45 = 344;
    pEncParaCfg->lambda46 = 386;
    pEncParaCfg->lambda47 = 433;
    pEncParaCfg->lambda48 = 487;
    pEncParaCfg->lambda49 = 546;
    pEncParaCfg->lambda50 = 613;
    pEncParaCfg->lambda51 = 688;
    pEncParaCfg->lambda52 = 773;
    pEncParaCfg->lambda53 = 867;
    pEncParaCfg->lambda54 = 974;
    pEncParaCfg->lambda55 = 1093;
    pEncParaCfg->lambda56 = 1227;
    pEncParaCfg->lambda57 = 1377;
    pEncParaCfg->lambda58 = 1546;
    pEncParaCfg->lambda59 = 1735;
    pEncParaCfg->lambda60 = 1948;
    pEncParaCfg->lambda61 = 2186;
    pEncParaCfg->lambda62 = 2454;
    pEncParaCfg->lambda63 = 2755;
    pEncParaCfg->lambda64 = 3092;
    pEncParaCfg->lambda65 = 3471;
    pEncParaCfg->lambda66 = 3896;
    pEncParaCfg->lambda67 = 4373;
    pEncParaCfg->lambda68 = 4908;
    pEncParaCfg->lambda69 = 5510;
    pEncParaCfg->lambda70 = 6184;
    pEncParaCfg->lambda71 = 6942;
    pEncParaCfg->lambda72 = 7792;
    pEncParaCfg->lambda73 = 8746;
    pEncParaCfg->lambda74 = 9817;
    pEncParaCfg->lambda75 = 11020;
    pEncParaCfg->lambda76 = 12369;
    pEncParaCfg->lambda77 = 13884;
    pEncParaCfg->lambda78 = 15584;
    pEncParaCfg->lambda79 = 17493;
    pEncParaCfg->inter_avail = 0;
    pEncParaCfg->intra_smooth = 1;
    pEncParaCfg->intra_bit_weight = 13;
    pEncParaCfg->intra_cu4_mode1 = 7;
    pEncParaCfg->intra_cu4_mode0 = 4294967295;
    pEncParaCfg->intra_cu8_mode1 = 7;
    pEncParaCfg->intra_cu8_mode0 = 4294967295;
    pEncParaCfg->intra_cu16_mode1 = 7;
    pEncParaCfg->intra_cu16_mode0 = 4294967295;
    pEncParaCfg->intra_cu32_mode1 = 7;
    pEncParaCfg->intra_cu32_mode0 = 4294967295;
    pEncParaCfg->tmv_en = 1;
    pEncParaCfg->q_scaling_waddr = 0;
    pEncParaCfg->q_scaling_wdata = 0;
    pEncParaCfg->vcpi2cu_qp_min_cu_size = 2;
    pEncParaCfg->vcpi2cu_tq_bypass_enabled_flag = 0;
    pEncParaCfg->vcpi2pu_log2_max_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2pu_log2_min_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2res_tf_skip_enabled_flag = 0;
    pEncParaCfg->nal_unit_head = 0;
    pEncParaCfg->max_num_mergecand = 2;
    pEncParaCfg->slchdr_size_part2 = 0;
    pEncParaCfg->slchdr_size_part1 = 0;
    pEncParaCfg->slchdr_part1 = 0;
    pEncParaCfg->slchdr_part2_seg1 = 0;
    pEncParaCfg->slchdr_part2_seg2 = 0;
    pEncParaCfg->slchdr_part2_seg3 = 0;
    pEncParaCfg->slchdr_part2_seg4 = 0;
    pEncParaCfg->slchdr_part2_seg5 = 0;
    pEncParaCfg->slchdr_part2_seg6 = 0;
    pEncParaCfg->slchdr_part2_seg7 = 0;
    pEncParaCfg->slchdr_part2_seg8 = 0;
    pEncParaCfg->strmbuflen = 10000000;
    pEncParaCfg->ptbits_en = 0;
    pEncParaCfg->ptbits = 0;
    pEncParaCfg->vcpi_slchdrstrm0 = 0;
    pEncParaCfg->vcpi_slchdrstrm1 = 0;
    pEncParaCfg->vcpi_slchdrstrm2 = 0;
    pEncParaCfg->vcpi_slchdrstrm3 = 0;
    pEncParaCfg->vcpi_reorderstrm0 = 0;
    pEncParaCfg->vcpi_reorderstrm1 = 0;
    pEncParaCfg->vcpi_markingstrm0 = 0;
    pEncParaCfg->vcpi_markingstrm1 = 0;
    pEncParaCfg->vcpi_parabit = 0;
    pEncParaCfg->vcpi_reorderbit = 0;
    pEncParaCfg->vcpi_markingbit = 0;
    pEncParaCfg->vcpi_svc_strm = 0;
    pEncParaCfg->vcpi_svc_en = 0;
    pEncParaCfg->curld_filter_hshift = 2;
    pEncParaCfg->curld_filter_hrnd = 2;
    pEncParaCfg->curld_filter_h3 = 1;
    pEncParaCfg->curld_filter_h2 = 1;
    pEncParaCfg->curld_filter_h1 = 1;
    pEncParaCfg->curld_filter_h0 = 1;
    pEncParaCfg->curld_filter_vshift = 2;
    pEncParaCfg->curld_filter_vrnd = 2;
    pEncParaCfg->curld_filter_v3 = 1;
    pEncParaCfg->curld_filter_v2 = 1;
    pEncParaCfg->curld_filter_v1 = 1;
    pEncParaCfg->curld_filter_v0 = 1;
    pEncParaCfg->curld_y_filt_01coef = 4783;
    pEncParaCfg->curld_y_filt_00coef = 15743;
    pEncParaCfg->curld_y_filt_03coef = 16358;
    pEncParaCfg->curld_y_filt_02coef = 16364;
    pEncParaCfg->curld_y_filt_11coef = 4265;
    pEncParaCfg->curld_y_filt_10coef = 15573;
    pEncParaCfg->curld_y_filt_13coef = 16259;
    pEncParaCfg->curld_y_filt_12coef = 568;
    pEncParaCfg->curld_y_filt_21coef = 3855;
    pEncParaCfg->curld_y_filt_20coef = 15584;
    pEncParaCfg->curld_y_filt_23coef = 16101;
    pEncParaCfg->curld_y_filt_22coef = 1324;
    pEncParaCfg->curld_y_filt_31coef = 3058;
    pEncParaCfg->curld_y_filt_30coef = 15716;
    pEncParaCfg->curld_y_filt_33coef = 15937;
    pEncParaCfg->curld_y_filt_32coef = 2182;
    pEncParaCfg->curld_c_filt_01coef = 4059;
    pEncParaCfg->curld_c_filt_00coef = 16242;
    pEncParaCfg->curld_c_filt_03coef = 16380;
    pEncParaCfg->curld_c_filt_02coef = 183;
    pEncParaCfg->curld_c_filt_11coef = 3783;
    pEncParaCfg->curld_c_filt_10coef = 16074;
    pEncParaCfg->curld_c_filt_13coef = 16344;
    pEncParaCfg->curld_c_filt_12coef = 664;
    pEncParaCfg->curld_c_filt_21coef = 3286;
    pEncParaCfg->curld_c_filt_20coef = 16036;
    pEncParaCfg->curld_c_filt_23coef = 16262;
    pEncParaCfg->curld_c_filt_22coef = 1270;
    pEncParaCfg->curld_c_filt_31coef = 2649;
    pEncParaCfg->curld_c_filt_30coef = 16085;
    pEncParaCfg->curld_c_filt_33coef = 16177;
    pEncParaCfg->curld_c_filt_32coef = 1953;
    pEncParaCfg->curld_clip_en = 0;//for gc test
    pEncParaCfg->clip_chrm_max = 235;
    pEncParaCfg->clip_chrm_min = 16;
    pEncParaCfg->clip_luma_max = 240;
    pEncParaCfg->clip_luma_min = 16;
    pEncParaCfg->vcpi_coeff_ry = 263;
    pEncParaCfg->vcpi_coeff_gy = 516;
    pEncParaCfg->vcpi_coeff_by = 100;
    pEncParaCfg->vcpi_coeff_rcb = (HI_S32)4294967145;
    pEncParaCfg->vcpi_coeff_gcb = (HI_S32)4294966998;
    pEncParaCfg->vcpi_coeff_bcb = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_rcr = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_gcr = (HI_S32)4294966919;
    pEncParaCfg->vcpi_coeff_bcr = (HI_S32)4294967223;
    pEncParaCfg->vcpi_rgb_shift = 10;
    pEncParaCfg->vcpi_rgb_rndy = 16;
    pEncParaCfg->vcpi_rgb_rndcb = 128;
    pEncParaCfg->vcpi_rgb_rndcr = 128;
    pEncParaCfg->vcpi_rgb_clip_en = 0;//for gc test
    pEncParaCfg->vcpi_rgb_clpmax = 235;
    pEncParaCfg->vcpi_rgb_clpmin = 16;

    pEncParaCfg->vcpi_protocol_clkgate_en = 1;
    pEncParaCfg->curld_lowdly_en = 0;
    pEncParaCfg->curld_read_interval = 0;
    pEncParaCfg->vcpi_pblk_pre_mvy_thr = 1;
    pEncParaCfg->vcpi_pblk_pre_mvx_thr = 1;
    pEncParaCfg->refld_ddr_cross_idx = 0;
    pEncParaCfg->recst_ddr_cross_idx = 0;
    pEncParaCfg->vcpi_wide_narrow_en = 0;
    pEncParaCfg->vcpi_wtmax = 0xff;
    pEncParaCfg->vcpi_rtmax = 0xff;
    pEncParaCfg->vcpi_ch00_rrmax = 0xf;
    pEncParaCfg->vcpi_ch01_rrmax = 0xf;
    pEncParaCfg->vcpi_ch02_rrmax = 0xf;
    pEncParaCfg->vcpi_ch03_rrmax = 0xf;
    pEncParaCfg->vcpi_ch04_rrmax = 0xf;
    pEncParaCfg->vcpi_ch05_rrmax = 0xf;
    pEncParaCfg->vcpi_ch06_rrmax = 0xf;
    pEncParaCfg->vcpi_ch07_rrmax = 0xf;
    pEncParaCfg->vcpi_ch08_rrmax = 0xf;
    pEncParaCfg->vcpi_ch09_rrmax = 0xf;
    pEncParaCfg->vcpi_ch10_rrmax = 0xf;
    pEncParaCfg->vcpi_ch11_rrmax = 0xf;
    pEncParaCfg->vcpi_ch12_rrmax = 0xf;
    pEncParaCfg->vcpi_ch00_wrmax = 0xf;
    pEncParaCfg->vcpi_ch01_wrmax = 0xf;
    pEncParaCfg->vcpi_ch02_wrmax = 0xf;
    pEncParaCfg->vcpi_ch03_wrmax = 0xf;
    pEncParaCfg->vcpi_ch04_wrmax = 0xf;
    pEncParaCfg->vcpi_ch05_wrmax = 0xf;
    pEncParaCfg->vcpi_ch06_wrmax = 0xf;
    pEncParaCfg->vcpi_ch07_wrmax = 0xf;
    pEncParaCfg->vcpi_ch08_wrmax = 0xf;
    pEncParaCfg->vcpi_ch09_wrmax = 0xf;
    pEncParaCfg->vcpi_ch10_wrmax = 0xf;
    pEncParaCfg->vcpi_ch11_wrmax = 0xf;
    pEncParaCfg->vcpi_ch12_wrmax = 0xf;
    pEncParaCfg->vcpi_ch13_wrmax = 0xf;
    pEncParaCfg->vcpi_ch14_wrmax = 0xf;


    if (pEncParaCfg->vcpi_rec_cmp_en != pEncParaCfg->vcpi_ref_cmp_en)
    {
        pEncParaCfg->vcpi_rec_cmp_en = 0;
        pEncParaCfg->vcpi_ref_cmp_en = 0;
    }

    pEncParaCfg->curld_y_filt_col_01coef = 0;
    pEncParaCfg->curld_y_filt_col_00coef = 0;
    pEncParaCfg->curld_y_filt_col_03coef = 0;
    pEncParaCfg->curld_y_filt_col_02coef = 0;
    pEncParaCfg->curld_y_filt_col_11coef = 0;
    pEncParaCfg->curld_y_filt_col_10coef = 0;
    pEncParaCfg->curld_y_filt_col_13coef = 0;
    pEncParaCfg->curld_y_filt_col_12coef = 0;
    pEncParaCfg->curld_y_filt_col_21coef = 0;
    pEncParaCfg->curld_y_filt_col_20coef = 0;
    pEncParaCfg->curld_y_filt_col_23coef = 0;
    pEncParaCfg->curld_y_filt_col_22coef = 0;
    pEncParaCfg->curld_y_filt_col_31coef = 0;
    pEncParaCfg->curld_y_filt_col_30coef = 0;
    pEncParaCfg->curld_y_filt_col_33coef = 0;
    pEncParaCfg->curld_y_filt_col_32coef = 0;
    pEncParaCfg->curld_c_filt_col_01coef = 0;
    pEncParaCfg->curld_c_filt_col_00coef = 0;
    pEncParaCfg->curld_c_filt_col_03coef = 0;
    pEncParaCfg->curld_c_filt_col_02coef = 0;
    pEncParaCfg->curld_c_filt_col_11coef = 0;
    pEncParaCfg->curld_c_filt_col_10coef = 0;
    pEncParaCfg->curld_c_filt_col_13coef = 0;
    pEncParaCfg->curld_c_filt_col_12coef = 0;
    pEncParaCfg->curld_c_filt_col_21coef = 0;
    pEncParaCfg->curld_c_filt_col_20coef = 0;
    pEncParaCfg->curld_c_filt_col_23coef = 0;
    pEncParaCfg->curld_c_filt_col_22coef = 0;
    pEncParaCfg->curld_c_filt_col_31coef = 0;
    pEncParaCfg->curld_c_filt_col_30coef = 0;
    pEncParaCfg->curld_c_filt_col_33coef = 0;
    pEncParaCfg->curld_c_filt_col_32coef = 0;

    pEncParaCfg->comn0_ptw_pf = 0x3;
    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->comn0_intns_ptw_ns_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_trans_msk = 0x0;
    pEncParaCfg->comn0_intns_tlbmiss_msk = 0x0;
    pEncParaCfg->comn0_intns_ext_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_smr0_ptw_qos = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn2_smr0_nscfg = 0x1;
    pEncParaCfg->comn2_smr1_nscfg = 0x1;
    pEncParaCfg->comn2_smr2_nscfg = 0x1;
    pEncParaCfg->comn2_smr3_nscfg = 0x1;
    pEncParaCfg->comn2_smr4_nscfg = 0x1;
    pEncParaCfg->comn2_smr5_nscfg = 0x1;
    pEncParaCfg->comn2_smr6_nscfg = 0x1;
    pEncParaCfg->comn2_smr7_nscfg = 0x1;
    pEncParaCfg->comn2_smr8_nscfg = 0x1;
    pEncParaCfg->comn2_smr9_nscfg = 0x1;
    pEncParaCfg->comn2_smr10_nscfg = 0x1;
    pEncParaCfg->comn2_smr11_nscfg = 0x1;
    pEncParaCfg->comn2_smr12_nscfg = 0x1;
    pEncParaCfg->comn2_smr13_nscfg = 0x1;
    pEncParaCfg->comn2_smr14_nscfg = 0x1;
    pEncParaCfg->comn2_smr15_nscfg = 0x1;
    pEncParaCfg->comn2_smr16_nscfg = 0x1;
    pEncParaCfg->comn2_smr17_nscfg = 0x1;
    pEncParaCfg->comn3_ints_ptw_ns_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_trans_msk = 0x0;
    pEncParaCfg->comn3_ints_tlbmiss_msk = 0x0;
    pEncParaCfg->comn3_ints_ext_msk = 0x0;
    pEncParaCfg->comn3_ints_permis_msk = 0x0;

    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->glb_bypass =  pEncParaCfg->comn0_glb_bypass;

    pEncParaCfg->comn0_smr18_bypass = 0;
    pEncParaCfg->comn0_smr19_bypass = 0;
    pEncParaCfg->comn0_smr20_bypass = 0;
    pEncParaCfg->comn0_smr21_bypass = 0;
    pEncParaCfg->comn0_smr22_bypass = 0;
    pEncParaCfg->comn0_smr23_bypass = 0;
    pEncParaCfg->comn0_smr24_bypass = 0;
    pEncParaCfg->comn0_smr25_bypass = 0;
    pEncParaCfg->comn0_smr26_bypass = 0;
    pEncParaCfg->comn0_smr27_bypass = 0;
    pEncParaCfg->comn0_smr28_bypass = 0;
    pEncParaCfg->comn0_smr29_bypass = 0;
    pEncParaCfg->comn0_smr30_bypass = 0;
    pEncParaCfg->comn0_smr31_bypass = 0;
    pEncParaCfg->comn0_smr32_bypass = 0;
    pEncParaCfg->comn0_smr33_bypass = 0;
    pEncParaCfg->comn0_smr34_bypass = 0;
    pEncParaCfg->comn0_smr35_bypass = 0;
    pEncParaCfg->sid18_bypass = 0;
    pEncParaCfg->sid19_bypass = 0;
    pEncParaCfg->sid20_bypass = 0;
    pEncParaCfg->sid21_bypass = 0;
    pEncParaCfg->sid22_bypass = 0;
    pEncParaCfg->sid23_bypass = 0;
    pEncParaCfg->sid24_bypass = 0;
    pEncParaCfg->sid25_bypass = 0;
    pEncParaCfg->sid26_bypass = 0;
    pEncParaCfg->sid27_bypass = 0;
    pEncParaCfg->sid28_bypass = 0;
    pEncParaCfg->sid29_bypass = 0;
    pEncParaCfg->sid30_bypass = 0;
    pEncParaCfg->sid31_bypass = 0;
    pEncParaCfg->sid32_bypass = 0;
    pEncParaCfg->sid33_bypass = 0;
    pEncParaCfg->sid34_bypass = 0;
    pEncParaCfg->sid35_bypass = 0;

    pEncParaCfg->glb_scr = 1;
    return 0;
}

HI_S32 VENC_DRV_EflInitEncParaCfgH264_LowPwr0( VeduEfl_EncPara_S  *pEncPara)
{
	VeduEfl_EncPara_S_Cfg  *pEncParaCfg = (VeduEfl_EncPara_S_Cfg*)kmalloc(sizeof(VeduEfl_EncPara_S_Cfg),GFP_KERNEL);
    if(NULL == pEncParaCfg)
    {
        return -1;
    }

    memset(pEncParaCfg, 0 ,sizeof(VeduEfl_EncPara_S_Cfg));
    pEncPara->pstCfg_EncPara = pEncParaCfg;

    pEncParaCfg->vcpi_oriheight_pix = 720;
    pEncParaCfg->vcpi_oriwidth_pix = 1280;
    pEncParaCfg->vcpi_ipcm_en = 1;
    pEncParaCfg->vcpi_intra_cu_en = 0xf;
    pEncParaCfg->vcpi_pskp_en = 1;
    pEncParaCfg->vcpi_fme_cu_en = 0xf;
    pEncParaCfg->vcpi_mrg_cu_en = 0xf;
    pEncParaCfg->vcpi_entropy_mode = 0;
    pEncParaCfg->vcpi_img_improve_en = 1;
    pEncParaCfg->vcpi_sao_chroma = 1;
    pEncParaCfg->vcpi_sao_luma = 1;
    pEncParaCfg->vcpi_slice_int_en = 1;// enable sliec IRQ
    pEncParaCfg->vcpi_protocol = 1;
    pEncParaCfg->vcpi_lcu_size = 0x0;
    pEncParaCfg->vcpi_tiles_en = 0;

    pEncParaCfg->enable_cfg_err = 0;
    pEncParaCfg->enable_vedu_timeout = 0;
    pEncParaCfg->enable_vedu_step = 0;
    pEncParaCfg->enable_vedu_brkpt = 0;
    pEncParaCfg->enable_vedu_slice_end = 1;// enable sliec IRQ需同步修改vcpi_slice_int_en
    pEncParaCfg->enable_ve_pbitsover = 0;
    pEncParaCfg->enable_ve_buffull = 1;
#ifndef IRQ_EN
    pEncParaCfg->enable_ve_eop = 0;
#else
    pEncParaCfg->enable_ve_eop = 1;//to do for irq test
#endif
    pEncParaCfg->vcpi_vstep = 0;
    pEncParaCfg->vcpi_vstart = 0;
    pEncParaCfg->vcpi_dbgmod = 0;
    pEncParaCfg->vcpi_bkp_en = 0;
    pEncParaCfg->vcpi_time_en = 0;
    pEncParaCfg->vcpi_trans_mode = 0;

    pEncParaCfg->vcpi_rec_cmp_en = 1;
    pEncParaCfg->vcpi_ref_cmp_en = 1;//

    pEncParaCfg->vcpi_num_refidx = 0;//614 add
    pEncParaCfg->vcpi_ref_idc = 0;//614 add
    pEncParaCfg->lcu_performance_baseline = 0;

    pEncParaCfg->vcpi_cfg_mode = 0;
    pEncParaCfg->vcpi_lcu_time_sel = 1;
    pEncParaCfg->vcpi_vedsel = 0;
    pEncParaCfg->vcpi_tile_height = 0x0;
    pEncParaCfg->vcpi_tile_width = 0;
    pEncParaCfg->vcpi_multislc_en = 0;
    pEncParaCfg->vcpi_slcspilt_mod = 1;
    pEncParaCfg->vcpi_slice_size = 0x17;
    pEncParaCfg->vcpi_frm_qp = 22;
    pEncParaCfg->vcpi_cb_qp_offset = 0;
    pEncParaCfg->vcpi_cr_qp_offset = 0;
    pEncParaCfg->vcpi_cnt_clr = 0x0;
    pEncParaCfg->vcpi_frame_no = 0xffffffff;
    pEncParaCfg->vcpi_dblk_filter_flag = 0x0;
    pEncParaCfg->vcpi_dblk_alpha = 0;
    pEncParaCfg->vcpi_dblk_beta = 0;
    pEncParaCfg->vcpi_mem_clkgate_en = 1;
    pEncParaCfg->vcpi_clkgate_en = 2;
    pEncParaCfg->fme_gtck_en = 1;
    pEncParaCfg->mrg_gtck_en = 1;
    pEncParaCfg->tqitq_gtck_en = 1;
    pEncParaCfg->vcpi_ime_lowpow = 1;
    pEncParaCfg->vcpi_fme_lowpow = 1;
    pEncParaCfg->vcpi_intra_lowpow = 1;
    pEncParaCfg->vcpi_imgheight_pix = 720;
    pEncParaCfg->vcpi_imgwidth_pix = 1280;
    pEncParaCfg->vcpi_bp_lcu_y = 0x0;
    pEncParaCfg->vcpi_bp_lcu_x = 0x0;
    pEncParaCfg->vedu_timeout = 0xffffffff;
    pEncParaCfg->vcpi_w_outstanding = 0x3;
    pEncParaCfg->vcpi_r_outstanding = 0x1f;
    pEncParaCfg->vcpi_sw_height = 0x1;
    pEncParaCfg->vcpi_sw_width = 0x2;
    pEncParaCfg->vcpi_tmv_wr_rd_avail = 0x3;
    pEncParaCfg->vcpi_cross_tile = 1;
    pEncParaCfg->vcpi_cross_slice = 1;
    pEncParaCfg->osd7_absqp = 0;
    pEncParaCfg->osd6_absqp = 0;
    pEncParaCfg->osd5_absqp = 0;
    pEncParaCfg->osd4_absqp = 0;
    pEncParaCfg->osd3_absqp = 0;
    pEncParaCfg->osd2_absqp = 0;
    pEncParaCfg->osd1_absqp = 0;
    pEncParaCfg->osd0_absqp = 0;
    pEncParaCfg->osd7_en = 0;
    pEncParaCfg->osd6_en = 0;
    pEncParaCfg->osd5_en = 0;
    pEncParaCfg->osd4_en = 0;
    pEncParaCfg->osd3_en = 0;
    pEncParaCfg->osd2_en = 0;
    pEncParaCfg->osd1_en = 0;
    pEncParaCfg->osd0_en = 0;
    pEncParaCfg->osd_en = 0;
    pEncParaCfg->osd0_x = 0x0;
    pEncParaCfg->osd0_y = 0x0;
    pEncParaCfg->osd1_y = 0x0;
    pEncParaCfg->osd1_x = 0x0;
    pEncParaCfg->osd2_y = 0x0;
    pEncParaCfg->osd2_x = 0x0;
    pEncParaCfg->osd3_y = 0x0;
    pEncParaCfg->osd3_x = 0x0;
    pEncParaCfg->osd4_y = 0x0;
    pEncParaCfg->osd4_x = 0x0;
    pEncParaCfg->osd5_y = 0x0;
    pEncParaCfg->osd5_x = 0x0;
    pEncParaCfg->osd6_y = 0x0;
    pEncParaCfg->osd6_x = 0x0;
    pEncParaCfg->osd7_y = 0x0;
    pEncParaCfg->osd7_x = 0x0;
    pEncParaCfg->osd0_h = 0x0;
    pEncParaCfg->osd0_w = 0x0;
    pEncParaCfg->osd1_h = 0x0;
    pEncParaCfg->osd1_w = 0x0;
    pEncParaCfg->osd2_h = 0x0;
    pEncParaCfg->osd2_w = 0x0;
    pEncParaCfg->osd3_h = 0x0;
    pEncParaCfg->osd3_w = 0x0;
    pEncParaCfg->osd4_h = 0x0;
    pEncParaCfg->osd4_w = 0x0;
    pEncParaCfg->osd5_h = 0x0;
    pEncParaCfg->osd5_w = 0x0;
    pEncParaCfg->osd6_h = 0x0;
    pEncParaCfg->osd6_w = 0x0;
    pEncParaCfg->osd7_h = 0x0;
    pEncParaCfg->osd7_w = 0x0;
    pEncParaCfg->osd7_layer_id = 0x0;
    pEncParaCfg->osd6_layer_id = 0x0;
    pEncParaCfg->osd5_layer_id = 0x0;
    pEncParaCfg->osd4_layer_id = 0x0;
    pEncParaCfg->osd3_layer_id = 0x0;
    pEncParaCfg->osd2_layer_id = 0x0;
    pEncParaCfg->osd1_layer_id = 0x0;
    pEncParaCfg->osd0_layer_id = 0x0;
    pEncParaCfg->osd3_qp = 0x0;
    pEncParaCfg->osd2_qp = 0x0;
    pEncParaCfg->osd1_qp = 0x0;
    pEncParaCfg->osd0_qp = 0x0;
    pEncParaCfg->osd7_qp = 0x0;
    pEncParaCfg->osd6_qp = 0x0;
    pEncParaCfg->osd5_qp = 0x0;
    pEncParaCfg->osd4_qp = 0x0;
    pEncParaCfg->curld_tunlcell_addr = 0x0;
    pEncParaCfg->curld_y_addr = 0x90000000;
    pEncParaCfg->curld_c_addr = 0x94000000;
    pEncParaCfg->curld_v_addr = 0x95000000;
    pEncParaCfg->curld_yh_addr = 0xa8300000;
    pEncParaCfg->curld_ch_addr = 0xa8320000;
    pEncParaCfg->curld_y_stride = 0x1000;
    pEncParaCfg->curld_c_stride = 0x1000;
    pEncParaCfg->curld_yh_stride = 0x1000;
    pEncParaCfg->curld_ch_stride = 0x1000;
    pEncParaCfg->recst_yaddr = 0x96000000;
    pEncParaCfg->recst_caddr = 0x9a000000;
    pEncParaCfg->recst_cstride = 0x1000;
    pEncParaCfg->recst_ystride = 0x1000;
    pEncParaCfg->recst_yh_addr = 0xa8340000;
    pEncParaCfg->recst_ch_addr = 0xa8440000;
    pEncParaCfg->recst_head_stride = 0x1000;
    pEncParaCfg->refld_luma_addr = 0x9c000000;
    pEncParaCfg->refld_chroma_addr = 0xa0000000;
    pEncParaCfg->refld_luma_vstride = 0x1000;
    pEncParaCfg->refld_chroma_vstride = 0x1000;
    pEncParaCfg->refld_yh_addr = 0xa8540000;
    pEncParaCfg->refld_ch_addr = 0xa8640000;
    pEncParaCfg->refld_yh_stride = 0x1000;
    pEncParaCfg->refld_ch_stride = 0x1000;
    pEncParaCfg->vcpi_pmeld_addr = 0xa7300000;
    pEncParaCfg->vcpi_pmest_addr = 0xa6300000;
    pEncParaCfg->upst_address = 0xa6400000;
    pEncParaCfg->mvst_address = 0xa6100000;
    pEncParaCfg->mvld_address = 0xa6200000;
    pEncParaCfg->csst_strmaddr = 0xa2000000;
    pEncParaCfg->csst_swptraddr = 0xa6000000;
    pEncParaCfg->csst_srptraddr = 0xa6000100;
    pEncParaCfg->vcpi_package_sel = 0x0;
    pEncParaCfg->vcpi_str_fmt = 0x0;
    pEncParaCfg->vcpi_blk_type = 0x0;
    pEncParaCfg->vcpi_store_mode = 0x0;
    pEncParaCfg->vcpi_scale_en = 0;
    pEncParaCfg->vcpi_crop_en = 0;
    pEncParaCfg->vcpi_crop_ystart = 0x0;
    pEncParaCfg->vcpi_crop_xstart = 0x0;
    pEncParaCfg->vcpi_crop_yend = 0x0;
    pEncParaCfg->vcpi_crop_xend = 0x0;
    pEncParaCfg->vcpi_yscale = 0x0;
    pEncParaCfg->vcpi_xscale = 0x0;
    pEncParaCfg->vcpi_byte_stuffing = 0;
    pEncParaCfg->vcpi_cabac_init_idc = 0;
    pEncParaCfg->vcpi_ext_edge_en = 1;
    pEncParaCfg->vcpi_iblk_pre_en = 1;
    pEncParaCfg->vcpi_pblk_pre_en = 1;
    pEncParaCfg->vcpi_force_inter = 0;
    pEncParaCfg->vcpi_iblk_pre_cost_thr = 0x7d0;
    pEncParaCfg->vcpi_pblk_pre_cost_thr = 0x708;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr0 = 0xa;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr1 = 0xa;
    pEncParaCfg->vcpi_iblk_pre_mvx_thr = 0x5;
    pEncParaCfg->vcpi_iblk_pre_mvy_thr = 0x5;
    pEncParaCfg->vcpi_win0_width = 0x2;
    pEncParaCfg->vcpi_win0_height = 0x2;
    pEncParaCfg->vcpi_win1_width = 0x8;
    pEncParaCfg->vcpi_win1_height = 0x8;
    pEncParaCfg->vcpi_win2_width = 0xd;
    pEncParaCfg->vcpi_win2_height = 0xd;
    pEncParaCfg->vcpi_win3_width = 0x4;
    pEncParaCfg->vcpi_win3_height = 0x4;
    pEncParaCfg->vcpi_skin_en = 1;
    pEncParaCfg->vcpi_highedge_en = 1;
    pEncParaCfg->vcpi_static_en = 1;
    pEncParaCfg->vcpi_roi_en = 0;
    pEncParaCfg->region7keep = 0;
    pEncParaCfg->region6keep = 0;
    pEncParaCfg->region5keep = 0;
    pEncParaCfg->region4keep = 0;
    pEncParaCfg->region3keep = 0;
    pEncParaCfg->region2keep = 0;
    pEncParaCfg->region1keep = 0;
    pEncParaCfg->region0keep = 1;
    pEncParaCfg->absqp7 = 0;
    pEncParaCfg->absqp6 = 0;
    pEncParaCfg->absqp5 = 0;
    pEncParaCfg->absqp4 = 0;
    pEncParaCfg->absqp3 = 0;
    pEncParaCfg->absqp2 = 0;
    pEncParaCfg->absqp1 = 0;
    pEncParaCfg->absqp0 = 0;
    pEncParaCfg->region7en = 0;
    pEncParaCfg->region6en = 0;
    pEncParaCfg->region5en = 0;
    pEncParaCfg->region4en = 0;
    pEncParaCfg->region3en = 0;
    pEncParaCfg->region2en = 0;
    pEncParaCfg->region1en = 0;
    pEncParaCfg->region0en = 0;
    pEncParaCfg->roiqp0 = 0;
    pEncParaCfg->roiqp1 = 0;
    pEncParaCfg->roiqp2 = 0;
    pEncParaCfg->roiqp3 = 0;
    pEncParaCfg->roiqp4 = 0;
    pEncParaCfg->roiqp5 = 0;
    pEncParaCfg->roiqp6 = 0;
    pEncParaCfg->roiqp7 = 0;
    pEncParaCfg->size0_roiheight = 0x0;
    pEncParaCfg->size0_roiwidth = 0x0;
    pEncParaCfg->start0_roistarty = 0x0;
    pEncParaCfg->start0_roistartx = 0x0;
    pEncParaCfg->size1_roiheight = 0x0;
    pEncParaCfg->size1_roiwidth = 0x0;
    pEncParaCfg->start1_roistarty = 0x0;
    pEncParaCfg->start1_roistartx = 0x0;
    pEncParaCfg->size2_roiheight = 0x0;
    pEncParaCfg->size2_roiwidth = 0x0;
    pEncParaCfg->start2_roistarty = 0x0;
    pEncParaCfg->start2_roistartx = 0x0;
    pEncParaCfg->size3_roiheight = 0x0;
    pEncParaCfg->size3_roiwidth = 0x0;
    pEncParaCfg->start3_roistarty = 0x0;
    pEncParaCfg->start3_roistartx = 0x0;
    pEncParaCfg->size4_roiheight = 0x0;
    pEncParaCfg->size4_roiwidth = 0x0;
    pEncParaCfg->start4_roistarty = 0x0;
    pEncParaCfg->start4_roistartx = 0x0;
    pEncParaCfg->size5_roiheight = 0x0;
    pEncParaCfg->size5_roiwidth = 0x0;
    pEncParaCfg->start5_roistarty = 0x0;
    pEncParaCfg->start5_roistartx = 0x0;
    pEncParaCfg->size6_roiheight = 0x0;
    pEncParaCfg->size6_roiwidth = 0x0;
    pEncParaCfg->start6_roistarty = 0x0;
    pEncParaCfg->start6_roistartx = 0x0;
    pEncParaCfg->size7_roiheight = 0x0;
    pEncParaCfg->size7_roiwidth = 0x0;
    pEncParaCfg->start7_roistarty = 0x0;
    pEncParaCfg->start7_roistartx = 0x0;
    pEncParaCfg->lcu_target_bit = 0;
    pEncParaCfg->narrow_tile_width = 0;
    pEncParaCfg->norm32_tr1_denois_max_num = 0x4;
    pEncParaCfg->norm32_coeff_protect_num = 0xff;
    pEncParaCfg->norm16_tr1_denois_max_num = 0x3;
    pEncParaCfg->norm16_coeff_protect_num = 0x40;
    pEncParaCfg->skin32_tr1_denois_max_num = 0x8;
    pEncParaCfg->skin32_coeff_protect_num = 0x20;
    pEncParaCfg->skin16_tr1_denois_max_num = 0x6;
    pEncParaCfg->skin16_coeff_protect_num = 0x10;
    pEncParaCfg->static32_tr1_denois_max_num = 0x8;
    pEncParaCfg->static32_coeff_protect_num = 0x10;
    pEncParaCfg->static16_tr1_denois_max_num = 0x6;
    pEncParaCfg->static16_coeff_protect_num = 0x8;
    pEncParaCfg->hedge32_tr1_denois_max_num = 0x8;
    pEncParaCfg->hedge32_coeff_protect_num = 0x20;
    pEncParaCfg->hedge16_tr1_denois_max_num = 0x6;
    pEncParaCfg->hedge16_coeff_protect_num = 0x10;
    pEncParaCfg->norm_intra_cu32_rdcost_offset = 0x0;
    pEncParaCfg->norm_intra_cu16_rdcost_offset = 0x0;
    pEncParaCfg->norm_intra_cu8_rdcost_offset = 0x0;
    pEncParaCfg->norm_intra_cu4_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu64_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu32_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu16_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu8_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu64_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu32_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu16_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu8_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu32_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu16_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu8_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu4_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu64_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu32_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu16_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu8_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu64_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu32_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu16_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu8_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu32_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu16_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu8_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu4_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu64_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu32_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu16_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu8_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu64_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu32_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu16_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu8_rdcost_offset = 0x0;
    pEncParaCfg->max_qp = 51;
    pEncParaCfg->min_qp = 0;
    pEncParaCfg->ave_lcu_bits = 0x64;

    pEncParaCfg->qp_delta = 4;
    pEncParaCfg->cu_qp_delta_thresh3 = 18;
    pEncParaCfg->cu_qp_delta_thresh2 = 15;
    pEncParaCfg->cu_qp_delta_thresh1 = 4;
    pEncParaCfg->cu_qp_delta_thresh0 = 1;
    pEncParaCfg->cu_qp_delta_thresh7 = 44;
    pEncParaCfg->cu_qp_delta_thresh6 = 34;
    pEncParaCfg->cu_qp_delta_thresh5 = 27;
    pEncParaCfg->cu_qp_delta_thresh4 = 22;
    pEncParaCfg->cu_qp_delta_thresh11 = 255;
    pEncParaCfg->cu_qp_delta_thresh10 = 255;
    pEncParaCfg->cu_qp_delta_thresh9 = 255;
    pEncParaCfg->cu_qp_delta_thresh8 = 255;

    pEncParaCfg->strong_edge_qp_delta = 0x2;
    pEncParaCfg->skin_qp_delta = 0x3;
    pEncParaCfg->lambda00 = 0x1;
    pEncParaCfg->lambda01 = 0x1;
    pEncParaCfg->lambda02 = 0x1;
    pEncParaCfg->lambda03 = 0x2;
    pEncParaCfg->lambda04 = 0x2;
    pEncParaCfg->lambda05 = 0x3;
    pEncParaCfg->lambda06 = 0x3;
    pEncParaCfg->lambda07 = 0x4;
    pEncParaCfg->lambda08 = 0x5;
    pEncParaCfg->lambda09 = 0x7;
    pEncParaCfg->lambda10 = 0x9;
    pEncParaCfg->lambda11 = 0xb;
    pEncParaCfg->lambda12 = 0xe;
    pEncParaCfg->lambda13 = 0x11;
    pEncParaCfg->lambda14 = 0x16;
    pEncParaCfg->lambda15 = 0x1b;
    pEncParaCfg->lambda16 = 0x22;
    pEncParaCfg->lambda17 = 0x2b;
    pEncParaCfg->lambda18 = 0x36;
    pEncParaCfg->lambda19 = 0x45;
    pEncParaCfg->lambda20 = 0x56;
    pEncParaCfg->lambda21 = 0x6d;
    pEncParaCfg->lambda22 = 0x89;
    pEncParaCfg->lambda23 = 0xad;
    pEncParaCfg->lambda24 = 0xda;//0xad;改善效果 l00214825
    pEncParaCfg->lambda25 = 0x112;
    pEncParaCfg->lambda26 = 0x159;
    pEncParaCfg->lambda27 = 0x1b3;
    pEncParaCfg->lambda28 = 0x224;
    pEncParaCfg->lambda29 = 0x2b3;
    pEncParaCfg->lambda30 = 0x366;
    pEncParaCfg->lambda31 = 0x449;
    pEncParaCfg->lambda32 = 0x566;
    pEncParaCfg->lambda33 = 0x6cd;
    pEncParaCfg->lambda34 = 0x891;
    pEncParaCfg->lambda35 = 0xacb;
    pEncParaCfg->lambda36 = 0xd9a;
    pEncParaCfg->lambda37 = 0xfff;
    pEncParaCfg->lambda38 = 0xfff;
    pEncParaCfg->lambda39 = 0xfff;
    pEncParaCfg->lambda40 = 0x1;
    pEncParaCfg->lambda41 = 0x1;
    pEncParaCfg->lambda42 = 0x1;
    pEncParaCfg->lambda43 = 0x1;
    pEncParaCfg->lambda44 = 0x2;
    pEncParaCfg->lambda45 = 0x2;
    pEncParaCfg->lambda46 = 0x2;
    pEncParaCfg->lambda47 = 0x2;
    pEncParaCfg->lambda48 = 0x3;
    pEncParaCfg->lambda49 = 0x3;
    pEncParaCfg->lambda50 = 0x3;
    pEncParaCfg->lambda51 = 0x4;
    pEncParaCfg->lambda52 = 0x4;
    pEncParaCfg->lambda53 = 0x4;
    pEncParaCfg->lambda54 = 0x5;
    pEncParaCfg->lambda55 = 0x6;
    pEncParaCfg->lambda56 = 0x6;
    pEncParaCfg->lambda57 = 0x7;
    pEncParaCfg->lambda58 = 0x8;
    pEncParaCfg->lambda59 = 0x9;
    pEncParaCfg->lambda60 = 0xa;
    pEncParaCfg->lambda61 = 0xb;
    pEncParaCfg->lambda62 = 0xd;
    pEncParaCfg->lambda63 = 0xe;
    pEncParaCfg->lambda64 = 0x10;
    pEncParaCfg->lambda65 = 0x12;
    pEncParaCfg->lambda66 = 0x14;
    pEncParaCfg->lambda67 = 0x17;
    pEncParaCfg->lambda68 = 0x19;
    pEncParaCfg->lambda69 = 0x1d;
    pEncParaCfg->lambda70 = 0x20;
    pEncParaCfg->lambda71 = 0x24;
    pEncParaCfg->lambda72 = 0x28;
    pEncParaCfg->lambda73 = 0x2d;
    pEncParaCfg->lambda74 = 0x33;
    pEncParaCfg->lambda75 = 0x39;
    pEncParaCfg->lambda76 = 0x40;
    pEncParaCfg->lambda77 = 0x48;
    pEncParaCfg->lambda78 = 0x51;
    pEncParaCfg->lambda79 = 0x5b;
    pEncParaCfg->inter_avail = 0;
    pEncParaCfg->intra_smooth = 1;
    pEncParaCfg->intra_bit_weight = 0xd;
    pEncParaCfg->intra_cu4_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu4_mode1 = 0x7;
    pEncParaCfg->intra_cu8_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu8_mode1 = 0x7;
    pEncParaCfg->intra_cu16_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu16_mode1 = 0x7;
    pEncParaCfg->intra_cu32_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu32_mode1 = 0x7;
    pEncParaCfg->vcpi_new_cost_en = 1;
    pEncParaCfg->vcpi_psw_adapt_en = 1;
    pEncParaCfg->vcpi_psw_thr0 = 0x14;
    pEncParaCfg->vcpi_psw_thr1 = 0x32;
    pEncParaCfg->vcpi_psw_thr2 = 0x96;
    pEncParaCfg->tr_weightx_2 = 0xc;
    pEncParaCfg->tr_weightx_1 = 0x8;
    pEncParaCfg->tr_weightx_0 = 0x4;
    pEncParaCfg->tr_weighty_2 = 0xc;
    pEncParaCfg->tr_weighty_1 = 0x8;
    pEncParaCfg->tr_weighty_0 = 0x4;
    pEncParaCfg->sr_weight_2 = 0x2;
    pEncParaCfg->sr_weight_1 = 0x4;
    pEncParaCfg->sr_weight_0 = 0x6;
    pEncParaCfg->skin_v_min_thr = 0x87;
    pEncParaCfg->skin_v_max_thr = 0xa0;
    pEncParaCfg->skin_u_min_thr = 0x64;
    pEncParaCfg->skin_u_max_thr = 0x7f;
    pEncParaCfg->still_scene_thr = 0x0;
    pEncParaCfg->high_edge_cnt = 0x6;
    pEncParaCfg->high_edge_thr = 0x28;
    pEncParaCfg->skin_num = 0x40;
    pEncParaCfg->refld_vcpi2cont_title_en = 1;
    pEncParaCfg->tmv_en = 1;
    pEncParaCfg->vcpi_high3pre_en = 0;
    pEncParaCfg->vcpi_rect3_mod = 1;
    pEncParaCfg->vcpi_rect2_mod = 1;
    pEncParaCfg->vcpi_rect1_mod = 1;
    //pEncParaCfg->vcpi_inter16x16_en = 1;
    pEncParaCfg->vcpi_inter8x8_en = 1;
    pEncParaCfg->vcpi_rect0_vstep = 0x0;
    pEncParaCfg->vcpi_rect0_hstep = 0x0;
    pEncParaCfg->vcpi_rect1_vstep = 0x0;
    pEncParaCfg->vcpi_rect1_hstep = 0x0;
    pEncParaCfg->vcpi_rect2_vstep = 0x1;
    pEncParaCfg->vcpi_rect2_hstep = 0x1;
    pEncParaCfg->vcpi_rect3_vstep = 0x0;
    pEncParaCfg->vcpi_rect3_hstep = 0x0;
    pEncParaCfg->vcpi_start_thr = 0x5dc;
    pEncParaCfg->vcpi_intra_thr = 0x1000;
    pEncParaCfg->vcpi_lambdaoff16 = 0x0;
    pEncParaCfg->vcpi_lambdaoff8 = 0x0;
    pEncParaCfg->vcpi_lowpow_fme_thr1 = 0x14;
    pEncParaCfg->vcpi_lowpow_fme_thr0 = 0xa;
    pEncParaCfg->curld_filter_hshift = 0x2;
    pEncParaCfg->curld_filter_hrnd = 0x2;
    pEncParaCfg->curld_filter_h3 = 0x1;
    pEncParaCfg->curld_filter_h2 = 0x1;
    pEncParaCfg->curld_filter_h1 = 0x1;
    pEncParaCfg->curld_filter_h0 = 0x1;
    pEncParaCfg->curld_filter_vshift = 0x2;
    pEncParaCfg->curld_filter_vrnd = 0x2;
    pEncParaCfg->curld_filter_v3 = 0x1;
    pEncParaCfg->curld_filter_v2 = 0x1;
    pEncParaCfg->curld_filter_v1 = 0x1;
    pEncParaCfg->curld_filter_v0 = 0x1;
    pEncParaCfg->curld_y_filt_00coef = 0x3d7f;
    pEncParaCfg->curld_y_filt_01coef = 0x12af;
    pEncParaCfg->curld_y_filt_02coef = 0x3fec;
    pEncParaCfg->curld_y_filt_03coef = 0x3fe6;
    pEncParaCfg->curld_y_filt_10coef = 0x3cd5;
    pEncParaCfg->curld_y_filt_11coef = 0x10a9;
    pEncParaCfg->curld_y_filt_12coef = 0x238;
    pEncParaCfg->curld_y_filt_13coef = 0x3f83;
    pEncParaCfg->curld_y_filt_20coef = 0x3ce0;
    pEncParaCfg->curld_y_filt_21coef = 0xf0f;
    pEncParaCfg->curld_y_filt_22coef = 0x52c;
    pEncParaCfg->curld_y_filt_23coef = 0x3ee5;
    pEncParaCfg->curld_y_filt_30coef = 0x3d64;
    pEncParaCfg->curld_y_filt_31coef = 0xbf2;
    pEncParaCfg->curld_y_filt_32coef = 0x886;
    pEncParaCfg->curld_y_filt_33coef = 0x3e41;
    pEncParaCfg->curld_c_filt_00coef = 0x3f72;
    pEncParaCfg->curld_c_filt_01coef = 0xfdb;
    pEncParaCfg->curld_c_filt_02coef = 0xb7;
    pEncParaCfg->curld_c_filt_03coef = 0x3ffc;
    pEncParaCfg->curld_c_filt_10coef = 0x3eca;
    pEncParaCfg->curld_c_filt_11coef = 0xec7;
    pEncParaCfg->curld_c_filt_12coef = 0x298;
    pEncParaCfg->curld_c_filt_13coef = 0x3fd8;
    pEncParaCfg->curld_c_filt_20coef = 0x3ea4;
    pEncParaCfg->curld_c_filt_21coef = 0xcd6;
    pEncParaCfg->curld_c_filt_22coef = 0x4f6;
    pEncParaCfg->curld_c_filt_23coef = 0x3f86;
    pEncParaCfg->curld_c_filt_30coef = 0x3ed5;
    pEncParaCfg->curld_c_filt_31coef = 0xa59;
    pEncParaCfg->curld_c_filt_32coef = 0x7a1;
    pEncParaCfg->curld_c_filt_33coef = 0x3f31;
    pEncParaCfg->curld_clip_en = 0;//for gc test
    pEncParaCfg->clip_chrm_max = 235;
    pEncParaCfg->clip_chrm_min = 16;
    pEncParaCfg->clip_luma_max = 240;
    pEncParaCfg->clip_luma_min = 16;
    pEncParaCfg->vcpi_coeff_gy = 516;
    pEncParaCfg->vcpi_coeff_ry = 263;
    pEncParaCfg->vcpi_coeff_rcb = (HI_S32)4294967145;
    pEncParaCfg->vcpi_coeff_by  = (HI_S32)100;
    pEncParaCfg->vcpi_coeff_bcb = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_gcb = (HI_S32)4294966998;
    pEncParaCfg->vcpi_coeff_gcr = (HI_S32)4294966919;
    pEncParaCfg->vcpi_coeff_rcr = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_bcr = (HI_S32)4294967223;
    pEncParaCfg->vcpi_rgb_rndy = 0x10;
    pEncParaCfg->vcpi_rgb_shift = 0xa;
    pEncParaCfg->vcpi_rgb_rndcr = 0x80;
    pEncParaCfg->vcpi_rgb_rndcb = 0x80;
    pEncParaCfg->vcpi_rgb_clpmin = 16;
    pEncParaCfg->vcpi_rgb_clpmax = 235;
    pEncParaCfg->vcpi_rgb_clip_en = 0;//for gc test
    pEncParaCfg->max_num_mergecand = 2;
    pEncParaCfg->strmbuflen = 10000000;

    if (pEncParaCfg->vcpi_rec_cmp_en != pEncParaCfg->vcpi_ref_cmp_en)
    {
        pEncParaCfg->vcpi_rec_cmp_en = 0;
        pEncParaCfg->vcpi_ref_cmp_en = 0;
    }



    pEncParaCfg->vcpi_protocol_clkgate_en = 1;
    pEncParaCfg->curld_lowdly_en = 0;
    pEncParaCfg->curld_read_interval = 0;
    pEncParaCfg->vcpi_pblk_pre_mvy_thr = 1;
    pEncParaCfg->vcpi_pblk_pre_mvx_thr = 1;
    pEncParaCfg->refld_ddr_cross_idx = 0;
    pEncParaCfg->recst_ddr_cross_idx = 0;
    pEncParaCfg->vcpi_wide_narrow_en = 0;
    pEncParaCfg->vcpi_wtmax = 0xff;
    pEncParaCfg->vcpi_rtmax = 0xff;
    pEncParaCfg->vcpi_ch00_rrmax = 0xf;
    pEncParaCfg->vcpi_ch01_rrmax = 0xf;
    pEncParaCfg->vcpi_ch02_rrmax = 0xf;
    pEncParaCfg->vcpi_ch03_rrmax = 0xf;
    pEncParaCfg->vcpi_ch04_rrmax = 0xf;
    pEncParaCfg->vcpi_ch05_rrmax = 0xf;
    pEncParaCfg->vcpi_ch06_rrmax = 0xf;
    pEncParaCfg->vcpi_ch07_rrmax = 0xf;
    pEncParaCfg->vcpi_ch08_rrmax = 0xf;
    pEncParaCfg->vcpi_ch09_rrmax = 0xf;
    pEncParaCfg->vcpi_ch10_rrmax = 0xf;
    pEncParaCfg->vcpi_ch11_rrmax = 0xf;
    pEncParaCfg->vcpi_ch12_rrmax = 0xf;
    pEncParaCfg->vcpi_ch00_wrmax = 0xf;
    pEncParaCfg->vcpi_ch01_wrmax = 0xf;
    pEncParaCfg->vcpi_ch02_wrmax = 0xf;
    pEncParaCfg->vcpi_ch03_wrmax = 0xf;
    pEncParaCfg->vcpi_ch04_wrmax = 0xf;
    pEncParaCfg->vcpi_ch05_wrmax = 0xf;
    pEncParaCfg->vcpi_ch06_wrmax = 0xf;
    pEncParaCfg->vcpi_ch07_wrmax = 0xf;
    pEncParaCfg->vcpi_ch08_wrmax = 0xf;
    pEncParaCfg->vcpi_ch09_wrmax = 0xf;
    pEncParaCfg->vcpi_ch10_wrmax = 0xf;
    pEncParaCfg->vcpi_ch11_wrmax = 0xf;
    pEncParaCfg->vcpi_ch12_wrmax = 0xf;
    pEncParaCfg->vcpi_ch13_wrmax = 0xf;
    pEncParaCfg->vcpi_ch14_wrmax = 0xf;

    pEncParaCfg->vcpi_svc_strm = 0;
    pEncParaCfg->vcpi_svc_en = 0;

    pEncParaCfg->clr_vedu_step = 0;
    pEncParaCfg->clr_vedu_brkpt = 0;
    pEncParaCfg->clr_vedu_slice_end = 0;
    pEncParaCfg->clr_ve_pbitsover = 0;
    pEncParaCfg->clr_ve_buffull = 0;
    pEncParaCfg->clr_ve_eop = 0;

    pEncParaCfg->q_scaling_waddr = 0;
    pEncParaCfg->q_scaling_wdata = 0;
    pEncParaCfg->vcpi2cu_qp_min_cu_size = 2;
    pEncParaCfg->vcpi2cu_tq_bypass_enabled_flag = 0;
    pEncParaCfg->vcpi2pu_log2_max_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2pu_log2_min_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2res_tf_skip_enabled_flag = 0;

    pEncParaCfg->nal_unit_head = 0;
    pEncParaCfg->slchdr_size_part2 = 0;
    pEncParaCfg->slchdr_size_part1 = 0;
    pEncParaCfg->slchdr_part1 = 0;
    pEncParaCfg->slchdr_part2_seg1 = 0;
    pEncParaCfg->slchdr_part2_seg2 = 0;
    pEncParaCfg->slchdr_part2_seg3 = 0;
    pEncParaCfg->slchdr_part2_seg4 = 0;
    pEncParaCfg->slchdr_part2_seg5 = 0;
    pEncParaCfg->slchdr_part2_seg6 = 0;
    pEncParaCfg->slchdr_part2_seg7 = 0;
    pEncParaCfg->slchdr_part2_seg8 = 0;

    pEncParaCfg->ptbits_en = 0;
    pEncParaCfg->ptbits = 0;

    pEncParaCfg->vcpi_slchdrstrm0 = 0;
    pEncParaCfg->vcpi_slchdrstrm1 = 0;
    pEncParaCfg->vcpi_slchdrstrm2 = 0;
    pEncParaCfg->vcpi_slchdrstrm3 = 0;
    pEncParaCfg->vcpi_reorderstrm0 = 0;
    pEncParaCfg->vcpi_reorderstrm1 = 0;
    pEncParaCfg->vcpi_markingstrm0 = 0;
    pEncParaCfg->vcpi_markingstrm1 = 0;
    pEncParaCfg->vcpi_parabit = 0;
    pEncParaCfg->vcpi_reorderbit = 0;
    pEncParaCfg->vcpi_markingbit = 0;

    pEncParaCfg->curld_y_filt_col_01coef = 0;
    pEncParaCfg->curld_y_filt_col_00coef = 0;
    pEncParaCfg->curld_y_filt_col_03coef = 0;
    pEncParaCfg->curld_y_filt_col_02coef = 0;
    pEncParaCfg->curld_y_filt_col_11coef = 0;
    pEncParaCfg->curld_y_filt_col_10coef = 0;
    pEncParaCfg->curld_y_filt_col_13coef = 0;
    pEncParaCfg->curld_y_filt_col_12coef = 0;
    pEncParaCfg->curld_y_filt_col_21coef = 0;
    pEncParaCfg->curld_y_filt_col_20coef = 0;
    pEncParaCfg->curld_y_filt_col_23coef = 0;
    pEncParaCfg->curld_y_filt_col_22coef = 0;
    pEncParaCfg->curld_y_filt_col_31coef = 0;
    pEncParaCfg->curld_y_filt_col_30coef = 0;
    pEncParaCfg->curld_y_filt_col_33coef = 0;
    pEncParaCfg->curld_y_filt_col_32coef = 0;
    pEncParaCfg->curld_c_filt_col_01coef = 0;
    pEncParaCfg->curld_c_filt_col_00coef = 0;
    pEncParaCfg->curld_c_filt_col_03coef = 0;
    pEncParaCfg->curld_c_filt_col_02coef = 0;
    pEncParaCfg->curld_c_filt_col_11coef = 0;
    pEncParaCfg->curld_c_filt_col_10coef = 0;
    pEncParaCfg->curld_c_filt_col_13coef = 0;
    pEncParaCfg->curld_c_filt_col_12coef = 0;
    pEncParaCfg->curld_c_filt_col_21coef = 0;
    pEncParaCfg->curld_c_filt_col_20coef = 0;
    pEncParaCfg->curld_c_filt_col_23coef = 0;
    pEncParaCfg->curld_c_filt_col_22coef = 0;
    pEncParaCfg->curld_c_filt_col_31coef = 0;
    pEncParaCfg->curld_c_filt_col_30coef = 0;
    pEncParaCfg->curld_c_filt_col_33coef = 0;
    pEncParaCfg->curld_c_filt_col_32coef = 0;


    pEncParaCfg->comn0_ptw_pf = 0x3;
    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->comn0_intns_ptw_ns_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_trans_msk = 0x0;
    pEncParaCfg->comn0_intns_tlbmiss_msk = 0x0;
    pEncParaCfg->comn0_intns_ext_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_smr0_ptw_qos = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn2_smr0_nscfg = 0x1;
    pEncParaCfg->comn2_smr1_nscfg = 0x1;
    pEncParaCfg->comn2_smr2_nscfg = 0x1;
    pEncParaCfg->comn2_smr3_nscfg = 0x1;
    pEncParaCfg->comn2_smr4_nscfg = 0x1;
    pEncParaCfg->comn2_smr5_nscfg = 0x1;
    pEncParaCfg->comn2_smr6_nscfg = 0x1;
    pEncParaCfg->comn2_smr7_nscfg = 0x1;
    pEncParaCfg->comn2_smr8_nscfg = 0x1;
    pEncParaCfg->comn2_smr9_nscfg = 0x1;
    pEncParaCfg->comn2_smr10_nscfg = 0x1;
    pEncParaCfg->comn2_smr11_nscfg = 0x1;
    pEncParaCfg->comn2_smr12_nscfg = 0x1;
    pEncParaCfg->comn2_smr13_nscfg = 0x1;
    pEncParaCfg->comn2_smr14_nscfg = 0x1;
    pEncParaCfg->comn2_smr15_nscfg = 0x1;
    pEncParaCfg->comn2_smr16_nscfg = 0x1;
    pEncParaCfg->comn2_smr17_nscfg = 0x1;
    pEncParaCfg->comn3_ints_ptw_ns_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_trans_msk = 0x0;
    pEncParaCfg->comn3_ints_tlbmiss_msk = 0x0;
    pEncParaCfg->comn3_ints_ext_msk = 0x0;
    pEncParaCfg->comn3_ints_permis_msk = 0x0;

    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->glb_bypass =  pEncParaCfg->comn0_glb_bypass;

    pEncParaCfg->comn0_smr18_bypass = 0;
    pEncParaCfg->comn0_smr19_bypass = 0;
    pEncParaCfg->comn0_smr20_bypass = 0;
    pEncParaCfg->comn0_smr21_bypass = 0;
    pEncParaCfg->comn0_smr22_bypass = 0;
    pEncParaCfg->comn0_smr23_bypass = 0;
    pEncParaCfg->comn0_smr24_bypass = 0;
    pEncParaCfg->comn0_smr25_bypass = 0;
    pEncParaCfg->comn0_smr26_bypass = 0;
    pEncParaCfg->comn0_smr27_bypass = 0;
    pEncParaCfg->comn0_smr28_bypass = 0;
    pEncParaCfg->comn0_smr29_bypass = 0;
    pEncParaCfg->comn0_smr30_bypass = 0;
    pEncParaCfg->comn0_smr31_bypass = 0;
    pEncParaCfg->comn0_smr32_bypass = 0;
    pEncParaCfg->comn0_smr33_bypass = 0;
    pEncParaCfg->comn0_smr34_bypass = 0;
    pEncParaCfg->comn0_smr35_bypass = 0;
    pEncParaCfg->sid18_bypass = 0;
    pEncParaCfg->sid19_bypass = 0;
    pEncParaCfg->sid20_bypass = 0;
    pEncParaCfg->sid21_bypass = 0;
    pEncParaCfg->sid22_bypass = 0;
    pEncParaCfg->sid23_bypass = 0;
    pEncParaCfg->sid24_bypass = 0;
    pEncParaCfg->sid25_bypass = 0;
    pEncParaCfg->sid26_bypass = 0;
    pEncParaCfg->sid27_bypass = 0;
    pEncParaCfg->sid28_bypass = 0;
    pEncParaCfg->sid29_bypass = 0;
    pEncParaCfg->sid30_bypass = 0;
    pEncParaCfg->sid31_bypass = 0;
    pEncParaCfg->sid32_bypass = 0;
    pEncParaCfg->sid33_bypass = 0;
    pEncParaCfg->sid34_bypass = 0;
    pEncParaCfg->sid35_bypass = 0;

    pEncParaCfg->glb_scr = 1;
    return 0;
}

HI_S32 VENC_DRV_EflInitEncParaCfgH264_LowPwr1( VeduEfl_EncPara_S  *pEncPara)
{
    VeduEfl_EncPara_S_Cfg  *pEncParaCfg = (VeduEfl_EncPara_S_Cfg*)kmalloc(sizeof(VeduEfl_EncPara_S_Cfg),GFP_KERNEL);
    if(NULL == pEncParaCfg)
    {
        return -1;
    }
    memset(pEncParaCfg, 0, sizeof(VeduEfl_EncPara_S_Cfg));
    pEncPara->pstCfg_EncPara = pEncParaCfg;

    pEncParaCfg->vcpi_oriheight_pix = 720;
    pEncParaCfg->vcpi_oriwidth_pix = 1280;
    pEncParaCfg->vcpi_ipcm_en = 1;
    pEncParaCfg->vcpi_intra_cu_en = 0xf;
    pEncParaCfg->vcpi_pskp_en = 1;
    pEncParaCfg->vcpi_fme_cu_en = 0xf;
    pEncParaCfg->vcpi_mrg_cu_en = 0xf;
    pEncParaCfg->vcpi_entropy_mode = 0;
    pEncParaCfg->vcpi_img_improve_en = 1;
    pEncParaCfg->vcpi_sao_chroma = 1;
    pEncParaCfg->vcpi_sao_luma = 1;
    pEncParaCfg->vcpi_slice_int_en = 1;
    pEncParaCfg->vcpi_protocol = 1;
    pEncParaCfg->vcpi_lcu_size = 0x0;
    pEncParaCfg->vcpi_tiles_en = 0;

    pEncParaCfg->enable_cfg_err = 0;
    pEncParaCfg->enable_vedu_timeout = 0;
    pEncParaCfg->enable_vedu_step = 0;
    pEncParaCfg->enable_vedu_brkpt = 0;
    pEncParaCfg->enable_vedu_slice_end = 1;// enable sliec IRQ需同步修改vcpi_slice_int_en
    pEncParaCfg->enable_ve_pbitsover = 0;
    pEncParaCfg->enable_ve_buffull = 0;
#ifndef IRQ_EN
    pEncParaCfg->enable_ve_eop = 0;
#else
    pEncParaCfg->enable_ve_eop = 1;//to do for irq test
#endif
    pEncParaCfg->vcpi_vstep = 0;
    pEncParaCfg->vcpi_vstart = 0;
    pEncParaCfg->vcpi_dbgmod = 0;
    pEncParaCfg->vcpi_bkp_en = 0;
    pEncParaCfg->vcpi_time_en = 0;
    pEncParaCfg->vcpi_trans_mode = 0;

    pEncParaCfg->vcpi_rec_cmp_en = 1;
    pEncParaCfg->vcpi_ref_cmp_en = 1;//

    pEncParaCfg->vcpi_num_refidx = 0;//614 add
    pEncParaCfg->vcpi_ref_idc = 0;//614 add
    pEncParaCfg->lcu_performance_baseline = 0;

    pEncParaCfg->vcpi_cfg_mode = 0;
    pEncParaCfg->vcpi_lcu_time_sel = 1;
    pEncParaCfg->vcpi_vedsel = 0;
    pEncParaCfg->vcpi_tile_height = 0x0;
    pEncParaCfg->vcpi_tile_width = 0;
    pEncParaCfg->vcpi_multislc_en = 0;
    pEncParaCfg->vcpi_slcspilt_mod = 1;
    pEncParaCfg->vcpi_slice_size = 0x17;
    pEncParaCfg->vcpi_frm_qp = 22;
    pEncParaCfg->vcpi_cb_qp_offset = 0;
    pEncParaCfg->vcpi_cr_qp_offset = 0;
    pEncParaCfg->vcpi_cnt_clr = 0x0;
    pEncParaCfg->vcpi_frame_no = 0xffffffff;
    pEncParaCfg->vcpi_dblk_filter_flag = 0x0;
    pEncParaCfg->vcpi_dblk_alpha = 0;
    pEncParaCfg->vcpi_dblk_beta = 0;
    pEncParaCfg->vcpi_mem_clkgate_en = 1;
    pEncParaCfg->vcpi_clkgate_en = 2;
    pEncParaCfg->fme_gtck_en = 1;
    pEncParaCfg->mrg_gtck_en = 1;
    pEncParaCfg->tqitq_gtck_en = 1;
    pEncParaCfg->vcpi_ime_lowpow = 1;
    pEncParaCfg->vcpi_fme_lowpow = 1;
    pEncParaCfg->vcpi_intra_lowpow = 1;
    pEncParaCfg->vcpi_imgheight_pix = 720;
    pEncParaCfg->vcpi_imgwidth_pix = 1280;
    pEncParaCfg->vcpi_bp_lcu_y = 0x0;
    pEncParaCfg->vcpi_bp_lcu_x = 0x0;
    pEncParaCfg->vedu_timeout = 0xffffffff;
    pEncParaCfg->vcpi_w_outstanding = 0x3;
    pEncParaCfg->vcpi_r_outstanding = 0x1f;
    pEncParaCfg->vcpi_sw_height = 0x1;
    pEncParaCfg->vcpi_sw_width = 0x2;
    pEncParaCfg->vcpi_tmv_wr_rd_avail = 0x3;
    pEncParaCfg->vcpi_cross_tile = 1;
    pEncParaCfg->vcpi_cross_slice = 1;
    pEncParaCfg->osd7_absqp = 0;
    pEncParaCfg->osd6_absqp = 0;
    pEncParaCfg->osd5_absqp = 0;
    pEncParaCfg->osd4_absqp = 0;
    pEncParaCfg->osd3_absqp = 0;
    pEncParaCfg->osd2_absqp = 0;
    pEncParaCfg->osd1_absqp = 0;
    pEncParaCfg->osd0_absqp = 0;
    pEncParaCfg->osd7_en = 0;
    pEncParaCfg->osd6_en = 0;
    pEncParaCfg->osd5_en = 0;
    pEncParaCfg->osd4_en = 0;
    pEncParaCfg->osd3_en = 0;
    pEncParaCfg->osd2_en = 0;
    pEncParaCfg->osd1_en = 0;
    pEncParaCfg->osd0_en = 0;
    pEncParaCfg->osd_en = 0;
    pEncParaCfg->osd0_x = 0x0;
    pEncParaCfg->osd0_y = 0x0;
    pEncParaCfg->osd1_y = 0x0;
    pEncParaCfg->osd1_x = 0x0;
    pEncParaCfg->osd2_y = 0x0;
    pEncParaCfg->osd2_x = 0x0;
    pEncParaCfg->osd3_y = 0x0;
    pEncParaCfg->osd3_x = 0x0;
    pEncParaCfg->osd4_y = 0x0;
    pEncParaCfg->osd4_x = 0x0;
    pEncParaCfg->osd5_y = 0x0;
    pEncParaCfg->osd5_x = 0x0;
    pEncParaCfg->osd6_y = 0x0;
    pEncParaCfg->osd6_x = 0x0;
    pEncParaCfg->osd7_y = 0x0;
    pEncParaCfg->osd7_x = 0x0;
    pEncParaCfg->osd0_h = 0x0;
    pEncParaCfg->osd0_w = 0x0;
    pEncParaCfg->osd1_h = 0x0;
    pEncParaCfg->osd1_w = 0x0;
    pEncParaCfg->osd2_h = 0x0;
    pEncParaCfg->osd2_w = 0x0;
    pEncParaCfg->osd3_h = 0x0;
    pEncParaCfg->osd3_w = 0x0;
    pEncParaCfg->osd4_h = 0x0;
    pEncParaCfg->osd4_w = 0x0;
    pEncParaCfg->osd5_h = 0x0;
    pEncParaCfg->osd5_w = 0x0;
    pEncParaCfg->osd6_h = 0x0;
    pEncParaCfg->osd6_w = 0x0;
    pEncParaCfg->osd7_h = 0x0;
    pEncParaCfg->osd7_w = 0x0;
    pEncParaCfg->osd7_layer_id = 0x0;
    pEncParaCfg->osd6_layer_id = 0x0;
    pEncParaCfg->osd5_layer_id = 0x0;
    pEncParaCfg->osd4_layer_id = 0x0;
    pEncParaCfg->osd3_layer_id = 0x0;
    pEncParaCfg->osd2_layer_id = 0x0;
    pEncParaCfg->osd1_layer_id = 0x0;
    pEncParaCfg->osd0_layer_id = 0x0;
    pEncParaCfg->osd3_qp = 0x0;
    pEncParaCfg->osd2_qp = 0x0;
    pEncParaCfg->osd1_qp = 0x0;
    pEncParaCfg->osd0_qp = 0x0;
    pEncParaCfg->osd7_qp = 0x0;
    pEncParaCfg->osd6_qp = 0x0;
    pEncParaCfg->osd5_qp = 0x0;
    pEncParaCfg->osd4_qp = 0x0;
    pEncParaCfg->curld_tunlcell_addr = 0x0;
    pEncParaCfg->curld_y_addr = 0x90000000;
    pEncParaCfg->curld_c_addr = 0x94000000;
    pEncParaCfg->curld_v_addr = 0x95000000;
    pEncParaCfg->curld_yh_addr = 0xa8300000;
    pEncParaCfg->curld_ch_addr = 0xa8320000;
    pEncParaCfg->curld_y_stride = 0x1000;
    pEncParaCfg->curld_c_stride = 0x1000;
    pEncParaCfg->curld_yh_stride = 0x1000;
    pEncParaCfg->curld_ch_stride = 0x1000;
    pEncParaCfg->recst_yaddr = 0x96000000;
    pEncParaCfg->recst_caddr = 0x9a000000;
    pEncParaCfg->recst_cstride = 0x1000;
    pEncParaCfg->recst_ystride = 0x1000;
    pEncParaCfg->recst_yh_addr = 0xa8340000;
    pEncParaCfg->recst_ch_addr = 0xa8440000;
    pEncParaCfg->recst_head_stride = 0x1000;
    pEncParaCfg->refld_luma_addr = 0x9c000000;
    pEncParaCfg->refld_chroma_addr = 0xa0000000;
    pEncParaCfg->refld_luma_vstride = 0x1000;
    pEncParaCfg->refld_chroma_vstride = 0x1000;
    pEncParaCfg->refld_yh_addr = 0xa8540000;
    pEncParaCfg->refld_ch_addr = 0xa8640000;
    pEncParaCfg->refld_yh_stride = 0x1000;
    pEncParaCfg->refld_ch_stride = 0x1000;
    pEncParaCfg->vcpi_pmeld_addr = 0xa7300000;
    pEncParaCfg->vcpi_pmest_addr = 0xa6300000;
    pEncParaCfg->upst_address = 0xa6400000;
    pEncParaCfg->mvst_address = 0xa6100000;
    pEncParaCfg->mvld_address = 0xa6200000;
    pEncParaCfg->csst_strmaddr = 0xa2000000;
    pEncParaCfg->csst_swptraddr = 0xa6000000;
    pEncParaCfg->csst_srptraddr = 0xa6000100;
    pEncParaCfg->vcpi_package_sel = 0x0;
    pEncParaCfg->vcpi_str_fmt = 0x0;
    pEncParaCfg->vcpi_blk_type = 0x0;
    pEncParaCfg->vcpi_store_mode = 0x0;
    pEncParaCfg->vcpi_scale_en = 0;
    pEncParaCfg->vcpi_crop_en = 0;
    pEncParaCfg->vcpi_crop_ystart = 0x0;
    pEncParaCfg->vcpi_crop_xstart = 0x0;
    pEncParaCfg->vcpi_crop_yend = 0x0;
    pEncParaCfg->vcpi_crop_xend = 0x0;
    pEncParaCfg->vcpi_yscale = 0x0;
    pEncParaCfg->vcpi_xscale = 0x0;
    pEncParaCfg->vcpi_byte_stuffing = 0;
    pEncParaCfg->vcpi_cabac_init_idc = 0;
    pEncParaCfg->vcpi_ext_edge_en = 1;
    pEncParaCfg->vcpi_iblk_pre_en = 1;
    pEncParaCfg->vcpi_pblk_pre_en = 1;
    pEncParaCfg->vcpi_force_inter = 0;
    pEncParaCfg->vcpi_iblk_pre_cost_thr = 0x708;
    pEncParaCfg->vcpi_pblk_pre_cost_thr = 0x9c4;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr0 = 0x9;
    pEncParaCfg->vcpi_iblk_pre_mv_dif_thr1 = 0x9;
    pEncParaCfg->vcpi_iblk_pre_mvx_thr = 0x4;
    pEncParaCfg->vcpi_iblk_pre_mvy_thr = 0x4;
    pEncParaCfg->vcpi_win0_width = 0x2;
    pEncParaCfg->vcpi_win0_height = 0x2;
    pEncParaCfg->vcpi_win1_width = 0x8;
    pEncParaCfg->vcpi_win1_height = 0x8;
    pEncParaCfg->vcpi_win2_width = 0xd;
    pEncParaCfg->vcpi_win2_height = 0xd;
    pEncParaCfg->vcpi_win3_width = 0x4;
    pEncParaCfg->vcpi_win3_height = 0x4;
    pEncParaCfg->vcpi_skin_en = 1;
    pEncParaCfg->vcpi_highedge_en = 1;
    pEncParaCfg->vcpi_static_en = 1;
    pEncParaCfg->vcpi_roi_en = 0;
    pEncParaCfg->region7keep = 0;
    pEncParaCfg->region6keep = 0;
    pEncParaCfg->region5keep = 0;
    pEncParaCfg->region4keep = 0;
    pEncParaCfg->region3keep = 0;
    pEncParaCfg->region2keep = 0;
    pEncParaCfg->region1keep = 0;
    pEncParaCfg->region0keep = 1;
    pEncParaCfg->absqp7 = 0;
    pEncParaCfg->absqp6 = 0;
    pEncParaCfg->absqp5 = 0;
    pEncParaCfg->absqp4 = 0;
    pEncParaCfg->absqp3 = 0;
    pEncParaCfg->absqp2 = 0;
    pEncParaCfg->absqp1 = 0;
    pEncParaCfg->absqp0 = 0;
    pEncParaCfg->region7en = 0;
    pEncParaCfg->region6en = 0;
    pEncParaCfg->region5en = 0;
    pEncParaCfg->region4en = 0;
    pEncParaCfg->region3en = 0;
    pEncParaCfg->region2en = 0;
    pEncParaCfg->region1en = 0;
    pEncParaCfg->region0en = 0;
    pEncParaCfg->roiqp0 = 0;
    pEncParaCfg->roiqp1 = 0;
    pEncParaCfg->roiqp2 = 0;
    pEncParaCfg->roiqp3 = 0;
    pEncParaCfg->roiqp4 = 0;
    pEncParaCfg->roiqp5 = 0;
    pEncParaCfg->roiqp6 = 0;
    pEncParaCfg->roiqp7 = 0;
    pEncParaCfg->size0_roiheight = 0x0;
    pEncParaCfg->size0_roiwidth = 0x0;
    pEncParaCfg->start0_roistarty = 0x0;
    pEncParaCfg->start0_roistartx = 0x0;
    pEncParaCfg->size1_roiheight = 0x0;
    pEncParaCfg->size1_roiwidth = 0x0;
    pEncParaCfg->start1_roistarty = 0x0;
    pEncParaCfg->start1_roistartx = 0x0;
    pEncParaCfg->size2_roiheight = 0x0;
    pEncParaCfg->size2_roiwidth = 0x0;
    pEncParaCfg->start2_roistarty = 0x0;
    pEncParaCfg->start2_roistartx = 0x0;
    pEncParaCfg->size3_roiheight = 0x0;
    pEncParaCfg->size3_roiwidth = 0x0;
    pEncParaCfg->start3_roistarty = 0x0;
    pEncParaCfg->start3_roistartx = 0x0;
    pEncParaCfg->size4_roiheight = 0x0;
    pEncParaCfg->size4_roiwidth = 0x0;
    pEncParaCfg->start4_roistarty = 0x0;
    pEncParaCfg->start4_roistartx = 0x0;
    pEncParaCfg->size5_roiheight = 0x0;
    pEncParaCfg->size5_roiwidth = 0x0;
    pEncParaCfg->start5_roistarty = 0x0;
    pEncParaCfg->start5_roistartx = 0x0;
    pEncParaCfg->size6_roiheight = 0x0;
    pEncParaCfg->size6_roiwidth = 0x0;
    pEncParaCfg->start6_roistarty = 0x0;
    pEncParaCfg->start6_roistartx = 0x0;
    pEncParaCfg->size7_roiheight = 0x0;
    pEncParaCfg->size7_roiwidth = 0x0;
    pEncParaCfg->start7_roistarty = 0x0;
    pEncParaCfg->start7_roistartx = 0x0;
    pEncParaCfg->lcu_target_bit = 0;
    pEncParaCfg->narrow_tile_width = 0;
    pEncParaCfg->norm32_tr1_denois_max_num = 0x4;
    pEncParaCfg->norm32_coeff_protect_num = 0xff;
    pEncParaCfg->norm16_tr1_denois_max_num = 0x3;
    pEncParaCfg->norm16_coeff_protect_num = 0x40;
    pEncParaCfg->skin32_tr1_denois_max_num = 0x8;
    pEncParaCfg->skin32_coeff_protect_num = 0x20;
    pEncParaCfg->skin16_tr1_denois_max_num = 0x6;
    pEncParaCfg->skin16_coeff_protect_num = 0x10;
    pEncParaCfg->static32_tr1_denois_max_num = 0x8;
    pEncParaCfg->static32_coeff_protect_num = 0x10;
    pEncParaCfg->static16_tr1_denois_max_num = 0x6;
    pEncParaCfg->static16_coeff_protect_num = 0x8;
    pEncParaCfg->hedge32_tr1_denois_max_num = 0x8;
    pEncParaCfg->hedge32_coeff_protect_num = 0x20;
    pEncParaCfg->hedge16_tr1_denois_max_num = 0x6;
    pEncParaCfg->hedge16_coeff_protect_num = 0x10;
    pEncParaCfg->norm_intra_cu32_rdcost_offset = 0x0;
    pEncParaCfg->norm_intra_cu16_rdcost_offset = 0x0;
    pEncParaCfg->norm_intra_cu8_rdcost_offset = 0x0;
    pEncParaCfg->norm_intra_cu4_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu64_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu32_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu16_rdcost_offset = 0x0;
    pEncParaCfg->norm_mrg_cu8_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu64_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu32_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu16_rdcost_offset = 0x0;
    pEncParaCfg->norm_fme_cu8_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu32_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu16_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu8_rdcost_offset = 0x0;
    pEncParaCfg->skin_intra_cu4_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu64_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu32_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu16_rdcost_offset = 0x0;
    pEncParaCfg->skin_mrg_cu8_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu64_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu32_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu16_rdcost_offset = 0x0;
    pEncParaCfg->skin_fme_cu8_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu32_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu16_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu8_rdcost_offset = 0x0;
    pEncParaCfg->hedge_intra_cu4_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu64_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu32_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu16_rdcost_offset = 0x0;
    pEncParaCfg->hedge_mrg_cu8_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu64_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu32_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu16_rdcost_offset = 0x0;
    pEncParaCfg->hedge_fme_cu8_rdcost_offset = 0x0;
    pEncParaCfg->max_qp = 51;
    pEncParaCfg->min_qp = 0;
    pEncParaCfg->ave_lcu_bits = 0x64;
#if 1//huangliang
    pEncParaCfg->qp_delta = 4;
    pEncParaCfg->cu_qp_delta_thresh3 = 18;
    pEncParaCfg->cu_qp_delta_thresh2 = 15;
    pEncParaCfg->cu_qp_delta_thresh1 = 4;
    pEncParaCfg->cu_qp_delta_thresh0 = 1;
    pEncParaCfg->cu_qp_delta_thresh7 = 44;
    pEncParaCfg->cu_qp_delta_thresh6 = 34;
    pEncParaCfg->cu_qp_delta_thresh5 = 27;
    pEncParaCfg->cu_qp_delta_thresh4 = 22;
    pEncParaCfg->cu_qp_delta_thresh11 = 255;
    pEncParaCfg->cu_qp_delta_thresh10 = 255;
    pEncParaCfg->cu_qp_delta_thresh9 = 255;
    pEncParaCfg->cu_qp_delta_thresh8 = 255;
#else
    pEncParaCfg->qp_delta = 0x2;
    pEncParaCfg->cu_qp_delta_thresh0 = 0x3;
    pEncParaCfg->cu_qp_delta_thresh1 = 0x3;
    pEncParaCfg->cu_qp_delta_thresh2 = 0x5;
    pEncParaCfg->cu_qp_delta_thresh3 = 0x5;
    pEncParaCfg->cu_qp_delta_thresh4 = 0x9;
    pEncParaCfg->cu_qp_delta_thresh5 = 0x9;
    pEncParaCfg->cu_qp_delta_thresh6 = 0xc;
    pEncParaCfg->cu_qp_delta_thresh7 = 0xc;
    pEncParaCfg->cu_qp_delta_thresh8 = 0x12;
    pEncParaCfg->cu_qp_delta_thresh9 = 0x12;
    pEncParaCfg->cu_qp_delta_thresh10 = 0xff;
    pEncParaCfg->cu_qp_delta_thresh11 = 0xff;
#endif
    pEncParaCfg->strong_edge_qp_delta = 0x2;
    pEncParaCfg->skin_qp_delta = 0x3;
    pEncParaCfg->lambda00 = 0x1;
    pEncParaCfg->lambda01 = 0x1;
    pEncParaCfg->lambda02 = 0x1;
    pEncParaCfg->lambda03 = 0x2;
    pEncParaCfg->lambda04 = 0x2;
    pEncParaCfg->lambda05 = 0x3;
    pEncParaCfg->lambda06 = 0x3;
    pEncParaCfg->lambda07 = 0x4;
    pEncParaCfg->lambda08 = 0x5;
    pEncParaCfg->lambda09 = 0x7;
    pEncParaCfg->lambda10 = 0x9;
    pEncParaCfg->lambda11 = 0xb;
    pEncParaCfg->lambda12 = 0xe;
    pEncParaCfg->lambda13 = 0x11;
    pEncParaCfg->lambda14 = 0x16;
    pEncParaCfg->lambda15 = 0x1b;
    pEncParaCfg->lambda16 = 0x22;
    pEncParaCfg->lambda17 = 0x2b;
    pEncParaCfg->lambda18 = 0x36;
    pEncParaCfg->lambda19 = 0x45;
    pEncParaCfg->lambda20 = 0x56;
    pEncParaCfg->lambda21 = 0x6d;
    pEncParaCfg->lambda22 = 0x89;
    pEncParaCfg->lambda23 = 0xad;
    pEncParaCfg->lambda24 = 0xda;//0xad;改善效果 l00214825
    pEncParaCfg->lambda25 = 0x112;
    pEncParaCfg->lambda26 = 0x159;
    pEncParaCfg->lambda27 = 0x1b3;
    pEncParaCfg->lambda28 = 0x224;
    pEncParaCfg->lambda29 = 0x2b3;
    pEncParaCfg->lambda30 = 0x366;
    pEncParaCfg->lambda31 = 0x449;
    pEncParaCfg->lambda32 = 0x566;
    pEncParaCfg->lambda33 = 0x6cd;
    pEncParaCfg->lambda34 = 0x891;
    pEncParaCfg->lambda35 = 0xacb;
    pEncParaCfg->lambda36 = 0xd9a;
    pEncParaCfg->lambda37 = 0xfff;
    pEncParaCfg->lambda38 = 0xfff;
    pEncParaCfg->lambda39 = 0xfff;
    pEncParaCfg->lambda40 = 0x1;
    pEncParaCfg->lambda41 = 0x1;
    pEncParaCfg->lambda42 = 0x1;
    pEncParaCfg->lambda43 = 0x1;
    pEncParaCfg->lambda44 = 0x2;
    pEncParaCfg->lambda45 = 0x2;
    pEncParaCfg->lambda46 = 0x2;
    pEncParaCfg->lambda47 = 0x2;
    pEncParaCfg->lambda48 = 0x3;
    pEncParaCfg->lambda49 = 0x3;
    pEncParaCfg->lambda50 = 0x3;
    pEncParaCfg->lambda51 = 0x4;
    pEncParaCfg->lambda52 = 0x4;
    pEncParaCfg->lambda53 = 0x4;
    pEncParaCfg->lambda54 = 0x5;
    pEncParaCfg->lambda55 = 0x6;
    pEncParaCfg->lambda56 = 0x6;
    pEncParaCfg->lambda57 = 0x7;
    pEncParaCfg->lambda58 = 0x8;
    pEncParaCfg->lambda59 = 0x9;
    pEncParaCfg->lambda60 = 0xa;
    pEncParaCfg->lambda61 = 0xb;
    pEncParaCfg->lambda62 = 0xd;
    pEncParaCfg->lambda63 = 0xe;
    pEncParaCfg->lambda64 = 0x10;
    pEncParaCfg->lambda65 = 0x12;
    pEncParaCfg->lambda66 = 0x14;
    pEncParaCfg->lambda67 = 0x17;
    pEncParaCfg->lambda68 = 0x19;
    pEncParaCfg->lambda69 = 0x1d;
    pEncParaCfg->lambda70 = 0x20;
    pEncParaCfg->lambda71 = 0x24;
    pEncParaCfg->lambda72 = 0x28;
    pEncParaCfg->lambda73 = 0x2d;
    pEncParaCfg->lambda74 = 0x33;
    pEncParaCfg->lambda75 = 0x39;
    pEncParaCfg->lambda76 = 0x40;
    pEncParaCfg->lambda77 = 0x48;
    pEncParaCfg->lambda78 = 0x51;
    pEncParaCfg->lambda79 = 0x5b;
    pEncParaCfg->inter_avail = 0;
    pEncParaCfg->intra_smooth = 1;
    pEncParaCfg->intra_bit_weight = 0xd;
    pEncParaCfg->intra_cu4_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu4_mode1 = 0x7;
    pEncParaCfg->intra_cu8_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu8_mode1 = 0x7;
    pEncParaCfg->intra_cu16_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu16_mode1 = 0x7;
    pEncParaCfg->intra_cu32_mode0 = 0xffffffff;
    pEncParaCfg->intra_cu32_mode1 = 0x7;
    pEncParaCfg->vcpi_new_cost_en = 1;
    pEncParaCfg->vcpi_psw_adapt_en = 1;
    pEncParaCfg->vcpi_psw_thr0 = 0x14;
    pEncParaCfg->vcpi_psw_thr1 = 0x32;
    pEncParaCfg->vcpi_psw_thr2 = 0x96;
    pEncParaCfg->tr_weightx_2 = 0xc;
    pEncParaCfg->tr_weightx_1 = 0x8;
    pEncParaCfg->tr_weightx_0 = 0x4;
    pEncParaCfg->tr_weighty_2 = 0xc;
    pEncParaCfg->tr_weighty_1 = 0x8;
    pEncParaCfg->tr_weighty_0 = 0x4;
    pEncParaCfg->sr_weight_2 = 0x2;
    pEncParaCfg->sr_weight_1 = 0x4;
    pEncParaCfg->sr_weight_0 = 0x6;
    pEncParaCfg->skin_v_min_thr = 0x87;
    pEncParaCfg->skin_v_max_thr = 0xa0;
    pEncParaCfg->skin_u_min_thr = 0x64;
    pEncParaCfg->skin_u_max_thr = 0x7f;
    pEncParaCfg->still_scene_thr = 0x0;
    pEncParaCfg->high_edge_cnt = 0x6;
    pEncParaCfg->high_edge_thr = 0x28;
    pEncParaCfg->skin_num = 0x40;
    pEncParaCfg->refld_vcpi2cont_title_en = 1;
    pEncParaCfg->tmv_en = 1;
    pEncParaCfg->vcpi_high3pre_en = 0;
    pEncParaCfg->vcpi_rect3_mod = 1;
    pEncParaCfg->vcpi_rect2_mod = 1;
    pEncParaCfg->vcpi_rect1_mod = 1;
    //	pEncParaCfg->vcpi_inter16x16_en = 1;
    pEncParaCfg->vcpi_inter8x8_en = 1;
    pEncParaCfg->vcpi_rect0_vstep = 0x0;
    pEncParaCfg->vcpi_rect0_hstep = 0x0;
    pEncParaCfg->vcpi_rect1_vstep = 0x0;
    pEncParaCfg->vcpi_rect1_hstep = 0x0;
    pEncParaCfg->vcpi_rect2_vstep = 0x1;
    pEncParaCfg->vcpi_rect2_hstep = 0x1;
    pEncParaCfg->vcpi_rect3_vstep = 0x0;
    pEncParaCfg->vcpi_rect3_hstep = 0x0;
    pEncParaCfg->vcpi_start_thr = 0x5dc;
    pEncParaCfg->vcpi_intra_thr = 0x1000;
    pEncParaCfg->vcpi_lambdaoff16 = 0x0;
    pEncParaCfg->vcpi_lambdaoff8 = 0x0;
    pEncParaCfg->vcpi_lowpow_fme_thr1 = 0x1b;
    pEncParaCfg->vcpi_lowpow_fme_thr0 = 0x11;
    pEncParaCfg->curld_filter_hshift = 0x2;
    pEncParaCfg->curld_filter_hrnd = 0x2;
    pEncParaCfg->curld_filter_h3 = 0x1;
    pEncParaCfg->curld_filter_h2 = 0x1;
    pEncParaCfg->curld_filter_h1 = 0x1;
    pEncParaCfg->curld_filter_h0 = 0x1;
    pEncParaCfg->curld_filter_vshift = 0x2;
    pEncParaCfg->curld_filter_vrnd = 0x2;
    pEncParaCfg->curld_filter_v3 = 0x1;
    pEncParaCfg->curld_filter_v2 = 0x1;
    pEncParaCfg->curld_filter_v1 = 0x1;
    pEncParaCfg->curld_filter_v0 = 0x1;
    pEncParaCfg->curld_y_filt_00coef = 0x3d7f;
    pEncParaCfg->curld_y_filt_01coef = 0x12af;
    pEncParaCfg->curld_y_filt_02coef = 0x3fec;
    pEncParaCfg->curld_y_filt_03coef = 0x3fe6;
    pEncParaCfg->curld_y_filt_10coef = 0x3cd5;
    pEncParaCfg->curld_y_filt_11coef = 0x10a9;
    pEncParaCfg->curld_y_filt_12coef = 0x238;
    pEncParaCfg->curld_y_filt_13coef = 0x3f83;
    pEncParaCfg->curld_y_filt_20coef = 0x3ce0;
    pEncParaCfg->curld_y_filt_21coef = 0xf0f;
    pEncParaCfg->curld_y_filt_22coef = 0x52c;
    pEncParaCfg->curld_y_filt_23coef = 0x3ee5;
    pEncParaCfg->curld_y_filt_30coef = 0x3d64;
    pEncParaCfg->curld_y_filt_31coef = 0xbf2;
    pEncParaCfg->curld_y_filt_32coef = 0x886;
    pEncParaCfg->curld_y_filt_33coef = 0x3e41;
    pEncParaCfg->curld_c_filt_00coef = 0x3f72;
    pEncParaCfg->curld_c_filt_01coef = 0xfdb;
    pEncParaCfg->curld_c_filt_02coef = 0xb7;
    pEncParaCfg->curld_c_filt_03coef = 0x3ffc;
    pEncParaCfg->curld_c_filt_10coef = 0x3eca;
    pEncParaCfg->curld_c_filt_11coef = 0xec7;
    pEncParaCfg->curld_c_filt_12coef = 0x298;
    pEncParaCfg->curld_c_filt_13coef = 0x3fd8;
    pEncParaCfg->curld_c_filt_20coef = 0x3ea4;
    pEncParaCfg->curld_c_filt_21coef = 0xcd6;
    pEncParaCfg->curld_c_filt_22coef = 0x4f6;
    pEncParaCfg->curld_c_filt_23coef = 0x3f86;
    pEncParaCfg->curld_c_filt_30coef = 0x3ed5;
    pEncParaCfg->curld_c_filt_31coef = 0xa59;
    pEncParaCfg->curld_c_filt_32coef = 0x7a1;
    pEncParaCfg->curld_c_filt_33coef = 0x3f31;
    pEncParaCfg->curld_clip_en = 0;//for gc test
    pEncParaCfg->clip_chrm_max = 235;
    pEncParaCfg->clip_chrm_min = 16;
    pEncParaCfg->clip_luma_max = 240;
    pEncParaCfg->clip_luma_min = 16;
    pEncParaCfg->vcpi_coeff_gy = 516;
    pEncParaCfg->vcpi_coeff_ry = 263;
    pEncParaCfg->vcpi_coeff_rcb = (HI_S32)4294967145;
    pEncParaCfg->vcpi_coeff_by  = (HI_S32)100;
    pEncParaCfg->vcpi_coeff_bcb = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_gcb = (HI_S32)4294966998;
    pEncParaCfg->vcpi_coeff_gcr = (HI_S32)4294966919;
    pEncParaCfg->vcpi_coeff_rcr = (HI_S32)450;
    pEncParaCfg->vcpi_coeff_bcr = (HI_S32)4294967223;
    pEncParaCfg->vcpi_rgb_rndy = 0x10;
    pEncParaCfg->vcpi_rgb_shift = 0xa;
    pEncParaCfg->vcpi_rgb_rndcr = 0x80;
    pEncParaCfg->vcpi_rgb_rndcb = 0x80;
    pEncParaCfg->vcpi_rgb_clpmin = 16;
    pEncParaCfg->vcpi_rgb_clpmax = 235;
    pEncParaCfg->vcpi_rgb_clip_en = 0;//for gc test
    pEncParaCfg->max_num_mergecand = 2;
    pEncParaCfg->strmbuflen = 10000000;

    if (pEncParaCfg->vcpi_rec_cmp_en != pEncParaCfg->vcpi_ref_cmp_en)
    {
        pEncParaCfg->vcpi_rec_cmp_en = 0;
        pEncParaCfg->vcpi_ref_cmp_en = 0;
    }

    pEncParaCfg->vcpi_protocol_clkgate_en = 1;
    pEncParaCfg->curld_lowdly_en = 0;
    pEncParaCfg->curld_read_interval = 0;
    pEncParaCfg->vcpi_pblk_pre_mvy_thr = 4;
    pEncParaCfg->vcpi_pblk_pre_mvx_thr = 4;
    pEncParaCfg->refld_ddr_cross_idx = 0;
    pEncParaCfg->recst_ddr_cross_idx = 0;
    pEncParaCfg->vcpi_wide_narrow_en = 0;
    pEncParaCfg->vcpi_wtmax = 0xff;
    pEncParaCfg->vcpi_rtmax = 0xff;
    pEncParaCfg->vcpi_ch00_rrmax = 0xf;
    pEncParaCfg->vcpi_ch01_rrmax = 0xf;
    pEncParaCfg->vcpi_ch02_rrmax = 0xf;
    pEncParaCfg->vcpi_ch03_rrmax = 0xf;
    pEncParaCfg->vcpi_ch04_rrmax = 0xf;
    pEncParaCfg->vcpi_ch05_rrmax = 0xf;
    pEncParaCfg->vcpi_ch06_rrmax = 0xf;
    pEncParaCfg->vcpi_ch07_rrmax = 0xf;
    pEncParaCfg->vcpi_ch08_rrmax = 0xf;
    pEncParaCfg->vcpi_ch09_rrmax = 0xf;
    pEncParaCfg->vcpi_ch10_rrmax = 0xf;
    pEncParaCfg->vcpi_ch11_rrmax = 0xf;
    pEncParaCfg->vcpi_ch12_rrmax = 0xf;
    pEncParaCfg->vcpi_ch00_wrmax = 0xf;
    pEncParaCfg->vcpi_ch01_wrmax = 0xf;
    pEncParaCfg->vcpi_ch02_wrmax = 0xf;
    pEncParaCfg->vcpi_ch03_wrmax = 0xf;
    pEncParaCfg->vcpi_ch04_wrmax = 0xf;
    pEncParaCfg->vcpi_ch05_wrmax = 0xf;
    pEncParaCfg->vcpi_ch06_wrmax = 0xf;
    pEncParaCfg->vcpi_ch07_wrmax = 0xf;
    pEncParaCfg->vcpi_ch08_wrmax = 0xf;
    pEncParaCfg->vcpi_ch09_wrmax = 0xf;
    pEncParaCfg->vcpi_ch10_wrmax = 0xf;
    pEncParaCfg->vcpi_ch11_wrmax = 0xf;
    pEncParaCfg->vcpi_ch12_wrmax = 0xf;
    pEncParaCfg->vcpi_ch13_wrmax = 0xf;
    pEncParaCfg->vcpi_ch14_wrmax = 0xf;

    pEncParaCfg->vcpi_svc_strm = 0;
    pEncParaCfg->vcpi_svc_en = 0;

    pEncParaCfg->clr_vedu_step = 0;
    pEncParaCfg->clr_vedu_brkpt = 0;
    pEncParaCfg->clr_vedu_slice_end = 0;
    pEncParaCfg->clr_ve_pbitsover = 0;
    pEncParaCfg->clr_ve_buffull = 0;
    pEncParaCfg->clr_ve_eop = 0;

    pEncParaCfg->q_scaling_waddr = 0;
    pEncParaCfg->q_scaling_wdata = 0;
    pEncParaCfg->vcpi2cu_qp_min_cu_size = 2;
    pEncParaCfg->vcpi2cu_tq_bypass_enabled_flag = 0;
    pEncParaCfg->vcpi2pu_log2_max_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2pu_log2_min_ipcm_cbsizey = 3;
    pEncParaCfg->vcpi2res_tf_skip_enabled_flag = 0;

    pEncParaCfg->curld_y_filt_col_01coef = 0;
    pEncParaCfg->curld_y_filt_col_00coef = 0;
    pEncParaCfg->curld_y_filt_col_03coef = 0;
    pEncParaCfg->curld_y_filt_col_02coef = 0;
    pEncParaCfg->curld_y_filt_col_11coef = 0;
    pEncParaCfg->curld_y_filt_col_10coef = 0;
    pEncParaCfg->curld_y_filt_col_13coef = 0;
    pEncParaCfg->curld_y_filt_col_12coef = 0;
    pEncParaCfg->curld_y_filt_col_21coef = 0;
    pEncParaCfg->curld_y_filt_col_20coef = 0;
    pEncParaCfg->curld_y_filt_col_23coef = 0;
    pEncParaCfg->curld_y_filt_col_22coef = 0;
    pEncParaCfg->curld_y_filt_col_31coef = 0;
    pEncParaCfg->curld_y_filt_col_30coef = 0;
    pEncParaCfg->curld_y_filt_col_33coef = 0;
    pEncParaCfg->curld_y_filt_col_32coef = 0;
    pEncParaCfg->curld_c_filt_col_01coef = 0;
    pEncParaCfg->curld_c_filt_col_00coef = 0;
    pEncParaCfg->curld_c_filt_col_03coef = 0;
    pEncParaCfg->curld_c_filt_col_02coef = 0;
    pEncParaCfg->curld_c_filt_col_11coef = 0;
    pEncParaCfg->curld_c_filt_col_10coef = 0;
    pEncParaCfg->curld_c_filt_col_13coef = 0;
    pEncParaCfg->curld_c_filt_col_12coef = 0;
    pEncParaCfg->curld_c_filt_col_21coef = 0;
    pEncParaCfg->curld_c_filt_col_20coef = 0;
    pEncParaCfg->curld_c_filt_col_23coef = 0;
    pEncParaCfg->curld_c_filt_col_22coef = 0;
    pEncParaCfg->curld_c_filt_col_31coef = 0;
    pEncParaCfg->curld_c_filt_col_30coef = 0;
    pEncParaCfg->curld_c_filt_col_33coef = 0;
    pEncParaCfg->curld_c_filt_col_32coef = 0;

    pEncParaCfg->comn0_ptw_pf = 0x3;
    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->comn0_intns_ptw_ns_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn0_intns_ptw_trans_msk = 0x0;
    pEncParaCfg->comn0_intns_tlbmiss_msk = 0x0;
    pEncParaCfg->comn0_intns_ext_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_smr0_ptw_qos = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn0_intns_permis_msk = 0x0;
    pEncParaCfg->comn2_smr0_nscfg = 0x1;
    pEncParaCfg->comn2_smr1_nscfg = 0x1;
    pEncParaCfg->comn2_smr2_nscfg = 0x1;
    pEncParaCfg->comn2_smr3_nscfg = 0x1;
    pEncParaCfg->comn2_smr4_nscfg = 0x1;
    pEncParaCfg->comn2_smr5_nscfg = 0x1;
    pEncParaCfg->comn2_smr6_nscfg = 0x1;
    pEncParaCfg->comn2_smr7_nscfg = 0x1;
    pEncParaCfg->comn2_smr8_nscfg = 0x1;
    pEncParaCfg->comn2_smr9_nscfg = 0x1;
    pEncParaCfg->comn2_smr10_nscfg = 0x1;
    pEncParaCfg->comn2_smr11_nscfg = 0x1;
    pEncParaCfg->comn2_smr12_nscfg = 0x1;
    pEncParaCfg->comn2_smr13_nscfg = 0x1;
    pEncParaCfg->comn2_smr14_nscfg = 0x1;
    pEncParaCfg->comn2_smr15_nscfg = 0x1;
    pEncParaCfg->comn2_smr16_nscfg = 0x1;
    pEncParaCfg->comn2_smr17_nscfg = 0x1;
    pEncParaCfg->comn3_ints_ptw_ns_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_invalid_msk = 0x0;
    pEncParaCfg->comn3_ints_ptw_trans_msk = 0x0;
    pEncParaCfg->comn3_ints_tlbmiss_msk = 0x0;
    pEncParaCfg->comn3_ints_ext_msk = 0x0;
    pEncParaCfg->comn3_ints_permis_msk = 0x0;

    pEncParaCfg->comn0_glb_bypass = 0;
    pEncParaCfg->glb_bypass =  pEncParaCfg->comn0_glb_bypass;

    pEncParaCfg->comn0_smr18_bypass = 0;
    pEncParaCfg->comn0_smr19_bypass = 0;
    pEncParaCfg->comn0_smr20_bypass = 0;
    pEncParaCfg->comn0_smr21_bypass = 0;
    pEncParaCfg->comn0_smr22_bypass = 0;
    pEncParaCfg->comn0_smr23_bypass = 0;
    pEncParaCfg->comn0_smr24_bypass = 0;
    pEncParaCfg->comn0_smr25_bypass = 0;
    pEncParaCfg->comn0_smr26_bypass = 0;
    pEncParaCfg->comn0_smr27_bypass = 0;
    pEncParaCfg->comn0_smr28_bypass = 0;
    pEncParaCfg->comn0_smr29_bypass = 0;
    pEncParaCfg->comn0_smr30_bypass = 0;
    pEncParaCfg->comn0_smr31_bypass = 0;
    pEncParaCfg->comn0_smr32_bypass = 0;
    pEncParaCfg->comn0_smr33_bypass = 0;
    pEncParaCfg->comn0_smr34_bypass = 0;
    pEncParaCfg->comn0_smr35_bypass = 0;
    pEncParaCfg->sid18_bypass = 0;
    pEncParaCfg->sid19_bypass = 0;
    pEncParaCfg->sid20_bypass = 0;
    pEncParaCfg->sid21_bypass = 0;
    pEncParaCfg->sid22_bypass = 0;
    pEncParaCfg->sid23_bypass = 0;
    pEncParaCfg->sid24_bypass = 0;
    pEncParaCfg->sid25_bypass = 0;
    pEncParaCfg->sid26_bypass = 0;
    pEncParaCfg->sid27_bypass = 0;
    pEncParaCfg->sid28_bypass = 0;
    pEncParaCfg->sid29_bypass = 0;
    pEncParaCfg->sid30_bypass = 0;
    pEncParaCfg->sid31_bypass = 0;
    pEncParaCfg->sid32_bypass = 0;
    pEncParaCfg->sid33_bypass = 0;
    pEncParaCfg->sid34_bypass = 0;
    pEncParaCfg->sid35_bypass = 0;

    pEncParaCfg->glb_scr = 1;

    return 0;
}

HI_VOID VENC_DRV_EflWakeUpThread( HI_VOID)
{
    VENC_DRV_OsalGiveEvent(&g_VENC_Event);
    return ;
}

//按照优先级排序，优先级高的在前面  l00214825
HI_VOID VENC_DRV_EflSortPriority(HI_VOID)
{
   HI_U32 i = 0;
   HI_U32 j = 0;
   for( i = 0; i < MAX_VEDU_CHN - 1; i++)
   {
      for(j =  MAX_VEDU_CHN - 1; j > i; j--)
      {
          if(PriorityTab[1][j]>PriorityTab[1][j-1])
          {
             HI_U32 temp0 = PriorityTab[0][j];
             HI_U32 temp1 = PriorityTab[1][j];
             PriorityTab[0][j]   = PriorityTab[0][j-1];
             PriorityTab[1][j]   = PriorityTab[1][j-1];
             PriorityTab[0][j-1] = temp0;
             PriorityTab[1][j-1] = temp1;
          }
      }
   }
}

HI_S32 VENC_DRV_EflSortPriority_2(HI_S8 priority)
{
   HI_U32 i                = 0;
   HI_U32 cnt              = 0;//记录共找到多少个优先级为priority的通道 l00214825
   HI_U32 id               = MAX_VEDU_CHN - 1;
   HI_BOOL bFind           = HI_FALSE;
   HI_U32 chnID_temp       = 0;
   HI_U32 chnPriority_temp = 0;

   for (i = 0; i < MAX_VEDU_CHN; i++)
   {
      if ((priority == PriorityTab[1][i]) && (INVAILD_CHN_FLAG != PriorityTab[0][i]))
      {
         if (!bFind)
         {
            id = i;
			bFind = HI_TRUE;
         }
		 cnt++;
      }
   }

   if (!bFind)
   {
      HI_WARN_VENC("can't fine the channel match with priority(%d)\n",priority);
      return HI_FAILURE;
   }

   if (1 == cnt || (id>=MAX_VEDU_CHN-1))
   {
      return HI_SUCCESS;
   }

   for(i = 0; (i<(cnt-1)) && (id<(MAX_VEDU_CHN-1)); i++,id++)
   {
       chnID_temp = PriorityTab[0][id];
       chnPriority_temp = PriorityTab[1][id];
       PriorityTab[0][id]   = PriorityTab[0][id+1];
       PriorityTab[1][id]   = PriorityTab[1][id+1];
       PriorityTab[0][id+1] = chnID_temp;
       PriorityTab[1][id+1] = chnPriority_temp;
   }

   return HI_SUCCESS;
}


HI_S32 VENC_DRV_EflCfgRegVenc( HI_HANDLE EncHandle )
{
    HI_DBG_VENC("enter %s ()\n", __func__);
	VENC_HAL_CfgReg( EncHandle );
	HI_DBG_VENC("exit %s ()\n", __func__);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflStartVencByReg( HI_HANDLE EncHandle )
{
	S_HEVC_AVC_REGS_TYPE *pAllReg = NULL;
	VeduEfl_EncPara_S  *pEncPara  = NULL;
    pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    HI_INFO_VENC("enter %s ()\n", __func__);

#ifdef TEST_TIME
     HI_U32 timetmp3 = HI_GetTS();
#endif

	pAllReg = (S_HEVC_AVC_REGS_TYPE *)pEncPara->pRegBase;

	pAllReg->VEDU_VCPI_REGS.VEDU_START.u32 = 0;
	pAllReg->VEDU_VCPI_REGS.VEDU_START.u32 = 1;

#ifdef TEST_TIME
	pEncPara->stStat.StartVencTime = HI_GetTS();
#endif

#ifdef TEST_TIME
    if(pEncPara->stStat.TotalFrame>5)
    {
	    HI_U32 timetmp4 = HI_GetTS();
        pEncPara->stStat.TotalISRTime5 += (timetmp4 - timetmp3);
    }
#endif

    HI_INFO_VENC("out %s()\n", __func__);
    return HI_SUCCESS;
}

HI_VOID VENC_DRV_EflReadRegVenc( HI_HANDLE EncHandle )
{
    HI_DBG_VENC("enter %s ()\n", __func__);
	VENC_HAL_ReadReg( EncHandle );
    HI_DBG_VENC("out %s()\n", __func__);
    return ;
}

HI_VOID VENC_DRV_EflReadRegVencSimple( HI_HANDLE EncHandle )
{
    HI_DBG_VENC("enter %s ()\n", __func__);
	VENC_HAL_ReadRegSimple( EncHandle );
    HI_DBG_VENC("out %s()\n", __func__);
    return ;
}

HI_S32 VENC_DRV_H265e_ReMakeSlcHdr(HI_HANDLE EncHandle)
{
    VeduEfl_EncPara_S  *pEncPara  = (VeduEfl_EncPara_S *)EncHandle;

    VeduEfl_H265e_SlcHdr_S  stSlcHdr;
    memset(&stSlcHdr, 0, sizeof(stSlcHdr));
    //pEncPara->H265FrmNum = pEncPara->IntraPic ? 0 : pEncPara->H265FrmNum + 1;

    stSlcHdr.frame_num     = pEncPara->H265FrmNum;
    stSlcHdr.eSliceType    = pEncPara->IntraPic ? 2 : 1;
    stSlcHdr.NumRefIndex   = pEncPara->NumRefIndex;
    stSlcHdr.iSliceAddr = 0;
    stSlcHdr.uiPocLsb = pEncPara->H265FrmNum;

    stSlcHdr.bSpsTemporalMvpEnableFlag = pEncPara->pstCfg_EncPara->tmv_en;
#ifdef SAO_LOWPOWER_EN
    pEncPara->sao2vcpi_saooff_num_luma = 0;
    pEncPara->sao2vcpi_saooff_num_chroma = 0;
    stSlcHdr.bSAOEnabledFlag = 1;//pEncPara->abSaoLumaFlag || pEncPara->abSaoChromaFlag;
    stSlcHdr.bSliceSaoLuma   = pEncPara->abSaoLumaFlag ;
    stSlcHdr.bSliceSaoChroma = pEncPara->abSaoChromaFlag;
    pEncPara->pstCfg_EncPara->vcpi_sao_luma = pEncPara->abSaoLumaFlag ;
    pEncPara->pstCfg_EncPara->vcpi_sao_chroma = pEncPara->abSaoChromaFlag;
#else
	stSlcHdr.bSAOEnabledFlag = pEncPara->pstCfg_EncPara->vcpi_sao_luma || pEncPara->pstCfg_EncPara->vcpi_sao_chroma;
    stSlcHdr.bSliceSaoLuma   = pEncPara->pstCfg_EncPara->vcpi_sao_luma;
	stSlcHdr.bSliceSaoChroma = pEncPara->pstCfg_EncPara->vcpi_sao_chroma;
#endif

    stSlcHdr.cabac_init_flag = pEncPara->pstCfg_EncPara->vcpi_cabac_init_idc;

	stSlcHdr.iSliceQPDelta   = pEncPara->iFrameQp - 26;// iSliceQp - (pstPPS->iPicInitQPMinus26 + 26);

	stSlcHdr.bDBFilterCtlPresent      = 1;
	stSlcHdr.bDBFilterOverrideEnabled = 1;

	stSlcHdr.bFirstSliceInPic      = 1;//= iSliceIdx == 0 ? TRUE : FALSE;
	stSlcHdr.bDFOverrideFlag       = 0;
    stSlcHdr.bSliceHeaderDisableDF = 0;// 0729 for gc

	stSlcHdr.bSliceLFAcrossSlice   = (pEncPara->pstCfg_EncPara->vcpi_multislc_en == 0) ? 1 : pEncPara->pstCfg_EncPara->vcpi_cross_slice;//
	stSlcHdr.iBetaOffsetDiv2       = pEncPara->pstCfg_EncPara->vcpi_dblk_beta;// 1
	stSlcHdr.iTcOffsetDiv2         = pEncPara->pstCfg_EncPara->vcpi_dblk_alpha;//0
    stSlcHdr.five_minus_max_num_merge_cand = 5 - pEncPara->pstCfg_EncPara->max_num_mergecand;
    pEncPara->SlcHdrBits = H265e_MakeSlcHdr(EncHandle,&stSlcHdr);
	return pEncPara->SlcHdrBits;
}

HI_S32 VENC_DRV_EflStartOneFrameVenc( HI_HANDLE EncHandle, VeduEfl_EncIn_S *pEncIn )
{
    VeduEfl_EncPara_S  *pEncPara  = (VeduEfl_EncPara_S *)EncHandle;

	HI_S32 iBytes = 0;
	HI_U32* buf   = NULL;
    HI_U32 i      = 0;
	HI_U8 StreamHeader[200] = {0};// =	kmalloc(uLength,GFP_KERNEL);
	HI_U8* pStreamHeader = (HI_U8* )StreamHeader;
	HI_INFO_VENC("%s, pEncPara->IntraPic:%d\n", __func__, pEncPara->IntraPic);

#ifdef TEST_TIME
		pEncPara->stStat.StartEncSHRCTime = HI_GetTS();
#endif

    if(pEncPara->IntraPic)
	{
		pEncPara->pstCfg_EncPara->vcpi_frame_type = 0;
		pEncPara->vcpi_frame_type                 = 0;
	}
	else
	{
		pEncPara->pstCfg_EncPara->vcpi_frame_type = 1;
		pEncPara->vcpi_frame_type                 = 1;
	}

    HI_DBG_VENC("enter %s()\n", __func__);
    VENC_DRV_EflRcOpenOneFrm( EncHandle );
#ifdef TEST_TIME

	pEncPara->stStat.EndEncRCTime = HI_GetTS();

	if(pEncPara->stStat.TotalFrame>5)
	{
			pEncPara->stStat.TotalEncRCTime += pEncPara->stStat.EndEncRCTime - pEncPara->stStat.StartEncSHRCTime;
			pEncPara->stStat.AvgEncRCTime = pEncPara->stStat.TotalEncRCTime/(pEncPara->stStat.TotalFrame-5);//timetmp - pEncPara->stStat.StartVencTime;//
	}
#endif


#ifdef TEST_TIME
	pEncPara->stStat.StartEncSHTime = HI_GetTS();
#endif

	pEncPara->EncFrameTotalNum++;
	HI_DBG_VENC("pEncPara->EncFrameTotalNum:%d\n",pEncPara->EncFrameTotalNum);

    /* Make slice header bitstream */
    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        VeduEfl_H265e_SlcHdr_S  stSlcHdr;
        memset(&stSlcHdr, 0, sizeof(stSlcHdr));
        pEncPara->H265FrmNum = pEncPara->IntraPic ? 0 : pEncPara->H265FrmNum + 1;

        stSlcHdr.frame_num     = pEncPara->H265FrmNum;
        stSlcHdr.eSliceType    = pEncPara->IntraPic ? 2 : 1;
        stSlcHdr.NumRefIndex   = pEncPara->NumRefIndex;
		stSlcHdr.iSliceAddr    = 0;//
		stSlcHdr.uiPocLsb      = pEncPara->H265FrmNum;
		stSlcHdr.bSpsTemporalMvpEnableFlag = pEncPara->pstCfg_EncPara->tmv_en;
#ifdef SAO_LOWPOWER_EN
		if(pEncPara->IntraPic||pEncPara->Sao_Frame_Count == 0)
		{
			pEncPara->abSaoLumaFlag   = 1;//pEncPara->vcpi_sao_luma
			pEncPara->abSaoChromaFlag = 1;//pEncPara->vcpi_sao_chroma
			pEncPara->Sao_Frame_Count = 0;
			pEncPara->sao2vcpi_saooff_num_luma   = 0;
			pEncPara->sao2vcpi_saooff_num_chroma = 0;
			pEncPara->sao2vcpi_lcu_cnt= 0;
		}
		pEncPara->Sao_Frame_Count++;
		if(pEncPara->Sao_Frame_Count == SAO_FRAME_REFRESH)
		{
			pEncPara->Sao_Frame_Count = 0;
		}
		//aiRatioSaoLumaOff default 60   ,aiRatioSaoChromaOff:75
		HI_INFO_VENC("sao2vcpi_lcu_cnt:%d",pEncPara->sao2vcpi_lcu_cnt);
		HI_INFO_VENC("sao2vcpi_saooff_num_lum:%d",pEncPara->sao2vcpi_saooff_num_luma);
		HI_INFO_VENC("sao2vcpi_saooff_num_chroma:%d",pEncPara->sao2vcpi_saooff_num_chroma);
		if (pEncPara->sao2vcpi_saooff_num_luma*100 > pEncPara->aiRatioSaoLumaOff * pEncPara->sao2vcpi_lcu_cnt)
		{
			pEncPara->abSaoLumaFlag = 0;
		}
		if (pEncPara->sao2vcpi_saooff_num_chroma*100 > pEncPara->aiRatioSaoChromaOff * pEncPara->sao2vcpi_lcu_cnt)
		{
			pEncPara->abSaoChromaFlag = 0;
		}

		pEncPara->sao2vcpi_saooff_num_luma   = 0;
		pEncPara->sao2vcpi_saooff_num_chroma = 0;

		stSlcHdr.bSAOEnabledFlag = 1;//pEncPara->abSaoLumaFlag || pEncPara->abSaoChromaFlag;
		stSlcHdr.bSliceSaoLuma   = pEncPara->abSaoLumaFlag ;
		stSlcHdr.bSliceSaoChroma = pEncPara->abSaoChromaFlag;
		pEncPara->pstCfg_EncPara->vcpi_sao_luma = pEncPara->abSaoLumaFlag ;
		pEncPara->pstCfg_EncPara->vcpi_sao_chroma = pEncPara->abSaoChromaFlag;
#else
		stSlcHdr.bSAOEnabledFlag = pEncPara->pstCfg_EncPara->vcpi_sao_luma || pEncPara->pstCfg_EncPara->vcpi_sao_chroma;
        stSlcHdr.bSliceSaoLuma   = pEncPara->pstCfg_EncPara->vcpi_sao_luma;
		stSlcHdr.bSliceSaoChroma = pEncPara->pstCfg_EncPara->vcpi_sao_chroma;
#endif

        stSlcHdr.cabac_init_flag = pEncPara->pstCfg_EncPara->vcpi_cabac_init_idc; //cabac or cavlc

		stSlcHdr.iSliceQPDelta = pEncPara->iFrameQp - 26;// iSliceQp - (pstPPS->iPicInitQPMinus26 + 26);

		stSlcHdr.bDBFilterCtlPresent      = 1;
		stSlcHdr.bDBFilterOverrideEnabled = 1;

		stSlcHdr.bFirstSliceInPic = 1;//= iSliceIdx == 0 ? TRUE : FALSE;
		stSlcHdr.bDFOverrideFlag  = 0;
        stSlcHdr.bSliceHeaderDisableDF = 0;// 0729 for gc

		stSlcHdr.bSliceLFAcrossSlice = (pEncPara->pstCfg_EncPara->vcpi_multislc_en == 0) ? 1 : pEncPara->pstCfg_EncPara->vcpi_cross_slice;//
		stSlcHdr.iBetaOffsetDiv2 = pEncPara->pstCfg_EncPara->vcpi_dblk_beta;// 1
		stSlcHdr.iTcOffsetDiv2 = pEncPara->pstCfg_EncPara->vcpi_dblk_alpha;//0
        stSlcHdr.five_minus_max_num_merge_cand = 5 - pEncPara->pstCfg_EncPara->max_num_mergecand;
	    pEncPara->SlcHdrBits = H265e_MakeSlcHdr(EncHandle,&stSlcHdr);
    }
    else if (pEncPara->vcpi_protocol == VEDU_H264)
    {
        VeduEfl_H264e_SlcHdr_S stSlcHdr;
        memset(&stSlcHdr, 0, sizeof(stSlcHdr));
        pEncPara->H264FrmNum = pEncPara->IntraPic ? 0 : pEncPara->H264FrmNum + 1;
        stSlcHdr.frame_num   = pEncPara->H264FrmNum;
        stSlcHdr.slice_type  = pEncPara->IntraPic ? 2 : 0;
		stSlcHdr.NumRefIndex = pEncPara->NumRefIndex;
		stSlcHdr.idr_pic_id  = pEncPara->idr_pic_id;
		//SH分了3段
        pEncPara->SlcHdrBits = H264e_MakeSlcHdr(pEncPara->SlcHdrStream,
                                                pEncPara->ReorderStream,
                                                pEncPara->MarkingStream, &stSlcHdr);
		pEncPara->idr_pic_id = stSlcHdr.idr_pic_id;
    }

	if(pEncPara->vcpi_protocol == VEDU_H265)
    {
        pEncPara->VEDU_SRC_YADDR = pEncIn->BusViY;
        pEncPara->VEDU_SRC_CADDR = pEncIn->BusViC;
        pEncPara->VEDU_SRC_VADDR = pEncIn->BusViV;

        pEncPara->curld_y_stride = pEncIn->ViYStride;//pEncIn->SStrideY;//寄存器y_stride并不使用pEncPara->y_stride
        pEncPara->curld_c_stride = pEncIn->ViCStride;//pEncIn->SStrideC;//寄存器c_stride并不使用pEncPara->c_stride


        pEncPara->PTS0 = pEncIn->PTS0;
        pEncPara->PTS1 = pEncIn->PTS1;

        pEncPara->RcnIdx = !pEncPara->RcnIdx;
		// add by l00214825 MV信息，每帧进行交换
		SWAP(pEncPara->VEDU_NBI_MVLD_ADDR,pEncPara->VEDU_NBI_MVST_ADDR);
		SWAP(pEncPara->VEDU_PMELD_ADDR,pEncPara->VEDU_PMEST_ADDR);

        //if (pEncPara->IntraPic && pEncPara->stStat.GetFrameNumOK == 1)
        // IDR帧
        if (pEncPara->IntraPic && pEncPara->bAddHeader)
        {
            HI_DBG_VENC("pEncPara->VpsBits/8:%d pEncPara->SpsBits/8:%d pEncPara->PpsBits/8:%d\n",
            pEncPara->VpsBits/8,pEncPara->SpsBits/8,pEncPara->PpsBits/8);

            //HI_U8 pHeaderPtr[200];
        	for (i = 0;i < 48;i++)
        	{
        		pEncPara->VEDU_HEADER[i] = 0;
        	}
#ifdef SPLIT_SPS_PPS
        	pEncPara->vlcst_para_set_en = 0;
#else
        	pEncPara->vlcst_para_set_en = 1;
#endif

        	pEncPara->uHeaderRealLength = pEncPara->VpsBits/8+pEncPara->SpsBits/8+pEncPara->PpsBits/8;
        	pEncPara->vlcst_para_set_len =	ALIGN_UP(pEncPara->uHeaderRealLength, 4);
            HI_DBG_VENC("pEncPara->vlcst_para_set_len:%d\n",pEncPara->vlcst_para_set_len);
            memset((HI_VOID *)pStreamHeader,0,sizeof(StreamHeader));

			memcpy((HI_VOID *)pStreamHeader,(HI_VOID *)pEncPara->VpsStream, pEncPara->VpsBits/8);
			pStreamHeader += pEncPara->VpsBits/8;

			memcpy((HI_VOID *)pStreamHeader,(HI_VOID *)pEncPara->SpsStream, pEncPara->SpsBits/8);
			pStreamHeader += pEncPara->SpsBits/8;

			memcpy((HI_VOID *)pStreamHeader,(HI_VOID *)pEncPara->PpsStream, pEncPara->PpsBits/8);
			pStreamHeader += pEncPara->PpsBits/8;

        	iBytes = pEncPara->uHeaderRealLength;
        	buf = (HI_U32*)StreamHeader;

        	for (i = 0; iBytes > 0; i++, iBytes -= 4)
        	{
                HI_DBG_VENC("buf[i]:%x\n",buf[i]);
        		pEncPara->VEDU_HEADER[i] =  buf[i] ;
        	}
		    pEncPara->bAddHeader = HI_FALSE;
        }
    }
	else if(pEncPara->vcpi_protocol == VEDU_H264)
    {
        pEncPara->VEDU_SRC_YADDR   = pEncIn->BusViY;
        pEncPara->VEDU_SRC_CADDR   = pEncIn->BusViC;
        pEncPara->VEDU_SRC_VADDR   = pEncIn->BusViV;
        pEncPara->curld_y_stride = pEncIn->ViYStride;
        pEncPara->curld_c_stride = pEncIn->ViCStride;

        if (pEncPara->LowDlyMod)
        {
            pEncPara->VEDU_TUNLCELL_ADDR = pEncIn->TunlCellAddr;
        }

        pEncPara->PTS0 = pEncIn->PTS0;
        pEncPara->PTS1 = pEncIn->PTS1;

        pEncPara->RcnIdx = !pEncPara->RcnIdx;
		// add by l00214825 MV信息，每帧进行交换
		SWAP(pEncPara->VEDU_NBI_MVLD_ADDR,pEncPara->VEDU_NBI_MVST_ADDR);
		SWAP(pEncPara->VEDU_PMELD_ADDR,pEncPara->VEDU_PMEST_ADDR);

        //if (pEncPara->IntraPic && pEncPara->stStat.GetFrameNumOK == 1)
        if (pEncPara->IntraPic && pEncPara->bAddHeader)
        {
        	for (i = 0;i < 48;i++)
        	{
        		pEncPara->VEDU_HEADER[i] = 0;
        	}
#ifdef SPLIT_SPS_PPS
        	pEncPara->vlcst_para_set_en = 0;
#else
        	pEncPara->vlcst_para_set_en = 1;
#endif
        	pEncPara->uHeaderRealLength = pEncPara->SpsBits/8+pEncPara->PpsBits/8;
        	pEncPara->vlcst_para_set_len =	ALIGN_UP(pEncPara->uHeaderRealLength, 4);
            HI_DBG_VENC("pEncPara->vlcst_para_set_len:%d\n",pEncPara->vlcst_para_set_len);
            memset((HI_VOID *)pStreamHeader,0,sizeof(StreamHeader));

			memcpy((HI_VOID *)pStreamHeader,(HI_VOID *)pEncPara->SpsStream, pEncPara->SpsBits/8);
			pStreamHeader += pEncPara->SpsBits/8;

			memcpy((HI_VOID *)pStreamHeader,(HI_VOID *)pEncPara->PpsStream, pEncPara->PpsBits/8);
			pStreamHeader += pEncPara->PpsBits/8;

        	iBytes = pEncPara->uHeaderRealLength;
        	buf = (HI_U32*)StreamHeader;

        	for (i = 0; iBytes > 0; i++, iBytes -= 4)
        	{
                HI_DBG_VENC("buf[i]:%x\n",buf[i]);
        		pEncPara->VEDU_HEADER[i] =  buf[i] ;
        	}
			pEncPara->bAddHeader = HI_FALSE;
        }
    }

#ifdef OUTPUT_LOWDELAY_EN
	pEncPara->iLastEncodedStreamCnt = 0;
#endif
	HI_DBG_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflEndOneFrameVenc( HI_HANDLE EncHandle )
{
    VeduEfl_EncPara_S  *pEncPara  = (VeduEfl_EncPara_S *)EncHandle;

	if (!pEncPara->LowDlyMod)  // not use low delay mode
	{
	    if (!pEncPara->VencBufFull )//|| !pEncPara->VencPbitOverflow 此功能暂不支持
	    {
            //fix me to do...
	    }
		else
		{
		    HI_WARN_VENC("VencBufFull  ,next farme is I frame!\n");
			pEncPara->bRequestIFrame = HI_TRUE;//add by ljh 码流buffer满了，此帧没编码完成，下一帧需要I帧，但下一帧仍满的概率也大
			pEncPara->stStat.TooFewBufferSkip++;
			return HI_SUCCESS;//2015/07/18 ljh 返回不统计码控信息
		}
    }
	else
	{
	}
//    VENC_DRV_OsalUnlock(((VeduEfl_EncPara_S *)EncHandle)->pStrmBufLock, &flag);

    HI_DBG_VENC("enter\n");
    VENC_DRV_EflRcCloseOneFrm( EncHandle );
    HI_DBG_VENC("out\n");

#if 0 //参考帧获取
    pEncPara->WaitingIsr = 1;//等待参考帧写完，防止销毁通道时挂死
	HI_DRV_VIDEO_FRAME_S stFrame;
	stFrame.u32Height = pEncPara->vcpi_imgheight_pix;
	stFrame.u32Width =  pEncPara->vcpi_imgwidth_pix;
	stFrame.stBufAddr[0].u32PhyAddr_Y = pEncPara->RcnYAddr[pEncPara->RcnIdx] ;
	stFrame.stBufAddr[0].u32PhyAddr_C = pEncPara->RcnCAddr[pEncPara->RcnIdx] ;
	stFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;

	stFrame.stBufAddr[0].u32Stride_Y = (pEncPara->vcpi_imgwidth_pix + 15)/16*16;
	stFrame.stBufAddr[0].u32Stride_C = (pEncPara->vcpi_imgwidth_pix + 15)/16*16;

	stFrame.stBufAddr[0].pVirAddr_Y = pEncPara->VirRcnYAddr[pEncPara->RcnIdx] ;
	stFrame.stBufAddr[0].pVirAddr_C= pEncPara->VirRcnCAddr[pEncPara->RcnIdx] ;
	if (pEncPara->pstCfg_EncPara->vcpi_ref_cmp_en == 0)//目前暂时只支持非压缩的参考帧导出
	{
		VENC_DRV_DbgWriteYUV(&stFrame, g_stVencChn[0].stProcWrite.YUVFileName,pEncPara->Vir2BusOffset);
	}
	pEncPara->WaitingIsr = 0;
#endif

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflEndOneSliceVenc( VeduEfl_EncPara_S * pEncCfg )
{
    HI_DBG_VENC("enter %s()\n", __func__);
    //VENC_DRV_EflRcCloseOneFrm( EncHandle );
    HI_DBG_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
static HI_S32 VENC_DRV_EflChkChnCfg( VeduEfl_EncCfg_S *pEncCfg )
{
    HI_DBG_VENC("enter %s()\n", __func__);
    HI_INFO_VENC("pEncCfg->FrameWidth:%d\n",pEncCfg->FrameWidth);
    HI_INFO_VENC("pEncCfg->FrameHeight:%d\n",pEncCfg->FrameHeight);
    HI_INFO_VENC("pEncCfg->vcpi_protocol:%d\n",pEncCfg->Protocol);
    HI_INFO_VENC("pEncCfg->Profile:%d\n",pEncCfg->Profile);

    if((pEncCfg->FrameWidth < VEDU_MIN_ENC_WIDTH) || (pEncCfg->FrameWidth > VEDU_MAX_ENC_WIDTH)||
    (pEncCfg->FrameHeight < VEDU_MIN_ENC_HEIGHT) || (pEncCfg->FrameHeight > VEDU_MAX_ENC_HEIGHT)||
    (pEncCfg->Protocol > (HI_U32)VEDU_H264))
    {
        HI_ERR_VENC("check params failed,FrameWidth%d,FrameHeight:%d,Protocol:%d\n",pEncCfg->FrameWidth,pEncCfg->FrameHeight,pEncCfg->Protocol);
		return HI_FAILURE;
    }
	if (((HI_U32)VEDU_H264 == pEncCfg->Protocol)&&((pEncCfg->Profile > (HI_U32)VEDU_H264_HIGH_PROFILE) ||(pEncCfg->Profile == (HI_U32)VEDU_H264_EXTENDED_PROFILE)  ))
    {
        HI_ERR_VENC("check params failed,Protocol:%d,Profile:%d\n",pEncCfg->Protocol,pEncCfg->Profile);
		return HI_FAILURE;
    }

    HI_DBG_VENC("exit %s()\n", __func__);
	return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflFlushStrmHeader( VeduEfl_EncPara_S  *pEncPara )
{
    HI_U32 i = 0;

    VeduEfl_H265e_VPS_S vps;
    VeduEfl_H265e_SPS_S sps;
    VeduEfl_H265e_PPS_S pps;
    HI_U8   tempVpsStream[300] ={0};
    HI_U8   tempSpsStream[300]= {0};
    HI_U8   tempPpsStream[320] ={0};
    HI_U32  insert;

    VeduEfl_H264e_SPS_S sps_264;
    VeduEfl_H264e_PPS_S pps_264;

    D_VENC_CHECK_PTR(pEncPara);

	HI_DBG_VENC("pEncPara->pstCfg_EncPara->vcpi_protocol:%d\n",pEncPara->pstCfg_EncPara->vcpi_protocol);
    /* make sps & pps & VOL stream */
    if (pEncPara->pstCfg_EncPara->vcpi_protocol == VEDU_H265)
    {
		////vps
        vps.uiMaxSubLayersMinus1 = 0;
        for(i = 0;i<2;i++)
        {
            vps.uiMaxDecPicBufferMinus1[0]   = 1;
            vps.uiMaxDecPicBufferMinus1[1]   = 0;
            vps.uiMaxNumReorderPics[i]       = 0;
            vps.uiMaxLatencyIncreasePlus1[i] = 0;
        }

		/////sps
        sps.uiPicWidthInLumaSamples  = ((pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix + 7) >> 3 ) << 3;
        sps.uiPicHeightInLumaSamples =  ((pEncPara->pstCfg_EncPara->vcpi_imgheight_pix + 7) >> 3) << 3;
        sps.uiPicCropLeftOffset      = 0 ;
        sps.uiPicCropRightOffset     = (sps.uiPicWidthInLumaSamples  - pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix) >> 1;
        sps.uiPicCropTopOffset       = 0 ;
        sps.uiPicCropBottomOffset    = (sps.uiPicHeightInLumaSamples - pEncPara->pstCfg_EncPara->vcpi_imgheight_pix) >> 1;
        sps.bPicCroppingFlag         = sps.uiPicCropLeftOffset  || sps.uiPicCropTopOffset ||
        sps.uiPicCropRightOffset || sps.uiPicCropBottomOffset;
        sps.bSAOEnabledFlag          = pEncPara->pstCfg_EncPara->vcpi_sao_luma || pEncPara->pstCfg_EncPara->vcpi_sao_chroma ;//pEncPara->pstCfg_EncPara->bSAOEnabledFlag;
        sps.uiSPSMaxSubLayersMinus1      = 0;
        sps.sps_temporal_mvp_enable_flag = pEncPara->pstCfg_EncPara->tmv_en;
        sps.bPcmEnable                   = pEncPara->pstCfg_EncPara->vcpi_ipcm_en;
        sps.iPcmLog2MaxSize              = 3 ;
        sps.iPcmLog2MinSize              = 3 ;
        sps.bPcmFilterDisable            = 0;
        sps.uiNumNegativePics            = 1;
        sps.bStrongIntraSmoothingFlag = pEncPara->pstCfg_EncPara->intra_smooth;
//        sps.ProfileIDC = 100;

		//////pps
        pps.constrained_intra_pred_flag = pEncPara->pstCfg_EncPara->inter_avail;
        pps.bCUQpDeltaEnable            = (pEncPara->pstCfg_EncPara->max_qp == pEncPara->pstCfg_EncPara->min_qp ? 0:1);
        pps.iCbQpOffset                 = pEncPara->pstCfg_EncPara->vcpi_cb_qp_offset;
        pps.iCrQpOffset                 = pEncPara->pstCfg_EncPara->vcpi_cr_qp_offset;
        pps.bTilesEnabledFlag           = 0;
        pps.bEntropyCodingSyncEnabled   = 0;
        pps.InLoopFilterCrossTiles      = pEncPara->pstCfg_EncPara->vcpi_cross_tile;//1

        pps.bSliceLFAcrossSlicepps =(pEncPara->pstCfg_EncPara->vcpi_multislc_en == 0) ? 1 : pEncPara->pstCfg_EncPara->vcpi_cross_slice;
        pps.bDBFilterCtlPresent    = 1;
        //pps.bPicDisableDBFilter = pEncPara->dblk_filter_flag & 1;//根据测试ok代码修改
		pps.bPicDisableDBFilter    = 0;//pEncCfg->vcpi_dblk_filter_flag & 1;  // 0729 gc对齐
        pps.iBetaOffsetDiv2        = 0;
        pps.iTcOffsetDiv2          = 0;
        pps.bPicScalingListPresent = 0;

        pEncPara->bSliceLFAcrossSlicepps = pps.bSliceLFAcrossSlicepps;

        pEncPara->VpsBits = H265e_MakeVPS(pEncPara->VpsStream, &vps);
        pEncPara->SpsBits = H265e_MakeSPS(pEncPara->SpsStream, &sps);
        pEncPara->PpsBits = H265e_MakePPS(pEncPara->PpsStream, &pps);

        memcpy((HI_VOID *)tempVpsStream,(HI_VOID *)pEncPara->VpsStream,VPS_MAX_LEN*sizeof(HI_U8));
        memcpy((HI_VOID *)tempSpsStream,(HI_VOID *)pEncPara->SpsStream,SPS_MAX_LEN*sizeof(HI_U8));
        memcpy((HI_VOID *)tempPpsStream,(HI_VOID *)pEncPara->PpsStream,PPS_MAX_LEN*sizeof(HI_U8));

        memset ((HI_VOID *)pEncPara->VpsStream, 0,VPS_MAX_LEN*sizeof(HI_U8));
        memset ((HI_VOID *)pEncPara->SpsStream, 0,SPS_MAX_LEN*sizeof(HI_U8));
        memset ((HI_VOID *)pEncPara->PpsStream, 0,PPS_MAX_LEN*sizeof(HI_U8));
        insert =  CheckPreventionThreeByte(tempVpsStream,  pEncPara->VpsBits, pEncPara->VpsStream);
        pEncPara->VpsBits = pEncPara->VpsBits +insert*8;
        insert = CheckPreventionThreeByte(tempSpsStream,  pEncPara->SpsBits, pEncPara->SpsStream);
        pEncPara->SpsBits = pEncPara->SpsBits +insert*8;
        insert = CheckPreventionThreeByte(tempPpsStream,  pEncPara->PpsBits, pEncPara->PpsStream);
        pEncPara->PpsBits = pEncPara->PpsBits +insert*8;
    }
    else if (pEncPara->pstCfg_EncPara->vcpi_protocol == VEDU_H264)
    {
        switch(pEncPara->H264Profile)
        {
           case VEDU_H264_BASELINE_PROFILE:
		   	sps_264.ProfileIDC = 66;
		   	break;
		   case VEDU_H264_MAIN_PROFILE:
		   	sps_264.ProfileIDC = 77;
		   	break;
		   case VEDU_H264_HIGH_PROFILE:
		   	sps_264.ProfileIDC = 100;
		   	break;
		   default:
		   	sps_264.ProfileIDC = 100;
		   	break;
        }

        sps_264.FrameWidthInMb  = (pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix + 15) >> 4;
        sps_264.FrameHeightInMb = (pEncPara->pstCfg_EncPara->vcpi_imgheight_pix+ 15) >> 4;
        sps_264.FrameCropLeft   = 0;
        sps_264.FrameCropTop    = 0;
        sps_264.FrameCropRight  = (sps_264.FrameWidthInMb * 16 - pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix) >> 1;
        sps_264.FrameCropBottom = (sps_264.FrameHeightInMb * 16 - pEncPara->pstCfg_EncPara->vcpi_imgheight_pix) >> 1;

        pps_264.CbQpOffset  = pEncPara->pstCfg_EncPara->vcpi_cb_qp_offset;
		pps_264.CrQpOffset  = pEncPara->pstCfg_EncPara->vcpi_cr_qp_offset;
        pps_264.ConstIntra  = pEncPara->pstCfg_EncPara->inter_avail;//pEncPara->pstCfg_EncPara->ConstIntra;
        pps_264.H264HpEn    = (pEncPara->H264Profile == VEDU_H264_HIGH_PROFILE)? 1 : 0;   //pEncPara->H264HpEn;
        pps_264.H264CabacEn = pEncPara->pstCfg_EncPara->vcpi_entropy_mode ? 0 : 1;
        pEncPara->SpsBits = H264e_MakeSPS(pEncPara->SpsStream, &sps_264);
        pEncPara->PpsBits = H264e_MakePPS(pEncPara->PpsStream, &pps_264);
    }
    return HI_SUCCESS;
}

void scale_coeff_select(VeduEfl_EncPara_S_Cfg* pEncPara)
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    if (pEncPara->vcpi_scale_en == 1)
    {
		i = (pEncPara->vcpi_xscale * 10 - 73728)/16384;
		j = (pEncPara->vcpi_yscale * 10 - 73728)/16384;
        pEncPara->curld_y_filt_00coef = scale_coef_table[i][0];
        pEncPara->curld_y_filt_01coef = scale_coef_table[i][1];
        pEncPara->curld_y_filt_02coef = scale_coef_table[i][2];
        pEncPara->curld_y_filt_03coef = scale_coef_table[i][3];
        pEncPara->curld_y_filt_10coef = scale_coef_table[i][4];
        pEncPara->curld_y_filt_11coef = scale_coef_table[i][5];
        pEncPara->curld_y_filt_12coef = scale_coef_table[i][6];
        pEncPara->curld_y_filt_13coef = scale_coef_table[i][7];
        pEncPara->curld_y_filt_20coef = scale_coef_table[i][8];
        pEncPara->curld_y_filt_21coef = scale_coef_table[i][9];
        pEncPara->curld_y_filt_22coef = scale_coef_table[i][10];
        pEncPara->curld_y_filt_23coef = scale_coef_table[i][11];
        pEncPara->curld_y_filt_30coef = scale_coef_table[i][12];
        pEncPara->curld_y_filt_31coef = scale_coef_table[i][13];
        pEncPara->curld_y_filt_32coef = scale_coef_table[i][14];
        pEncPara->curld_y_filt_33coef = scale_coef_table[i][15];
        pEncPara->curld_c_filt_00coef = scale_coef_table[i][16];
        pEncPara->curld_c_filt_01coef = scale_coef_table[i][17];
        pEncPara->curld_c_filt_02coef = scale_coef_table[i][18];
        pEncPara->curld_c_filt_03coef = scale_coef_table[i][19];
        pEncPara->curld_c_filt_10coef = scale_coef_table[i][20];
        pEncPara->curld_c_filt_11coef = scale_coef_table[i][21];
        pEncPara->curld_c_filt_12coef = scale_coef_table[i][22];
        pEncPara->curld_c_filt_13coef = scale_coef_table[i][23];
        pEncPara->curld_c_filt_20coef = scale_coef_table[i][24];
        pEncPara->curld_c_filt_21coef = scale_coef_table[i][25];
        pEncPara->curld_c_filt_22coef = scale_coef_table[i][26];
        pEncPara->curld_c_filt_23coef = scale_coef_table[i][27];
        pEncPara->curld_c_filt_30coef = scale_coef_table[i][28];
        pEncPara->curld_c_filt_31coef = scale_coef_table[i][29];
        pEncPara->curld_c_filt_32coef = scale_coef_table[i][30];
        pEncPara->curld_c_filt_33coef = scale_coef_table[i][31];
        pEncPara->curld_y_filt_col_00coef = scale_coef_table[j][0];
        pEncPara->curld_y_filt_col_01coef = scale_coef_table[j][1];
        pEncPara->curld_y_filt_col_02coef = scale_coef_table[j][2];
        pEncPara->curld_y_filt_col_03coef = scale_coef_table[j][3];
        pEncPara->curld_y_filt_col_10coef = scale_coef_table[j][4];
        pEncPara->curld_y_filt_col_11coef = scale_coef_table[j][5];
        pEncPara->curld_y_filt_col_12coef = scale_coef_table[j][6];
        pEncPara->curld_y_filt_col_13coef = scale_coef_table[j][7];
        pEncPara->curld_y_filt_col_20coef = scale_coef_table[j][8];
        pEncPara->curld_y_filt_col_21coef = scale_coef_table[j][9];
        pEncPara->curld_y_filt_col_22coef = scale_coef_table[j][10];
        pEncPara->curld_y_filt_col_23coef = scale_coef_table[j][11];
        pEncPara->curld_y_filt_col_30coef = scale_coef_table[j][12];
        pEncPara->curld_y_filt_col_31coef = scale_coef_table[j][13];
        pEncPara->curld_y_filt_col_32coef = scale_coef_table[j][14];
        pEncPara->curld_y_filt_col_33coef = scale_coef_table[j][15];
        pEncPara->curld_c_filt_col_00coef = scale_coef_table[j][16];
        pEncPara->curld_c_filt_col_01coef = scale_coef_table[j][17];
        pEncPara->curld_c_filt_col_02coef = scale_coef_table[j][18];
        pEncPara->curld_c_filt_col_03coef = scale_coef_table[j][19];
        pEncPara->curld_c_filt_col_10coef = scale_coef_table[j][20];
        pEncPara->curld_c_filt_col_11coef = scale_coef_table[j][21];
        pEncPara->curld_c_filt_col_12coef = scale_coef_table[j][22];
        pEncPara->curld_c_filt_col_13coef = scale_coef_table[j][23];
        pEncPara->curld_c_filt_col_20coef = scale_coef_table[j][24];
        pEncPara->curld_c_filt_col_21coef = scale_coef_table[j][25];
        pEncPara->curld_c_filt_col_22coef = scale_coef_table[j][26];
        pEncPara->curld_c_filt_col_23coef = scale_coef_table[j][27];
        pEncPara->curld_c_filt_col_30coef = scale_coef_table[j][28];
        pEncPara->curld_c_filt_col_31coef = scale_coef_table[j][29];
        pEncPara->curld_c_filt_col_32coef = scale_coef_table[j][30];
        pEncPara->curld_c_filt_col_33coef = scale_coef_table[j][31];
	}
	HI_DBG_VENC("i = %d,j = %d\n",i,j);
	HI_DBG_VENC("coef00 = %d\n",pEncPara->curld_y_filt_00coef);
	HI_DBG_VENC("coef01 = %d\n",pEncPara->curld_y_filt_01coef);
	HI_DBG_VENC("col_coef00 = %d\n",pEncPara->curld_y_filt_col_00coef);
	HI_DBG_VENC("col_coef01 = %d\n",pEncPara->curld_y_filt_col_01coef);
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     : EncHandle
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflCreateVenc( HI_HANDLE *pEncHandle, VeduEfl_EncCfg_S *pEncCfg, HI_U32 Index, HI_UNF_VENC_CHN_ATTR_S *pstAttr)
{
	HI_S32 iRet       = 0;
	HI_U32 uTmpWidth  = 0;
	HI_U32 uTmpHeight = 0;
    VeduEfl_EncPara_S *pEncPara = NULL;

	HI_U32 WidthInMb   = (pEncCfg->FrameWidth + 15) >> 4;
	HI_U32 HeightInMb  = (pEncCfg->FrameHeight + 15) >> 4;
	HI_U32 WidthInCtb  = (pEncCfg->FrameWidth + 63) >> 6;
	HI_U32 HeightInCtb = (pEncCfg->FrameHeight + 63) >> 6;

	HI_U32 uRECLumaSize       = 0;
	HI_U32 uRECChromaSize     = 0;
	HI_U32 uNBISize           = 0;
	HI_U32 uPMESize           = 0;
	HI_U32 uRECLumaHeadSize   = 0;
	HI_U32 uRECChromaHeadSize = 0;

    HI_U32 uRECLumaAlignSize = 0;
    HI_U32 uRECChromaAlignSize = 0;
    HI_U32 uNBIAlignSize  = 0;
    HI_U32 uPMEAlignSize  = 0;
    HI_U32 uRECLumaHeadAlignSize = 0;
    HI_U32 uRECChromaHeadAlignSize = 0;
    HI_U32 uAllocteTotalSize = 0;
    HI_U32 u32StartPhyAlignAddr = 0;
    HI_U8* pStartVirAlignAddr = NULL;

	HI_INFO_VENC("enter %s, pEncHandle:0x%x\n", __func__, pEncHandle);
    if(NULL == pEncHandle)
    {
    	HI_ERR_VENC("%s, pEncHandle can not be null\n", __func__);
    	return HI_FAILURE;
    }

    /* check channel config */
    if (HI_FAILURE == VENC_DRV_EflChkChnCfg( pEncCfg ))
    {
        return HI_FAILURE;
    }

    pEncPara = (VeduEfl_EncPara_S *)kmalloc(sizeof(VeduEfl_EncPara_S), GFP_KERNEL);
	if (NULL == pEncPara)
	{
		HI_ERR_VENC("%s, kmalloc failed, size = %d\n", __func__, sizeof(VeduEfl_EncPara_S));
		goto error_1; //return前要释放内存goto error_0是错的 ljh
	}

    memset((HI_VOID *)pEncPara, 0, sizeof(VeduEfl_EncPara_S));

    pEncPara->bCfgVencPerFrame = 0;
    pEncPara->bSecureFlag = 0;
    if (pEncCfg->Protocol == VEDU_H265)
    {
        HI_INFO_VENC("init hevc\n");
        if (pstAttr->bLowPowerMode == 0)
        {
            HI_DBG_VENC("LowPower mode:0\n");
            //if(VENC_DRV_EflInitEncParaCfgHevc(pEncPara))
            if (VENC_DRV_EflInitEncParaCfgHevc_LowPwr0(pEncPara))
            {
                HI_ERR_VENC("VENC_DRV_EflInitEncParaCfgHevc failed!\n");
                goto error_1;
            }
        }
        else
        {
            HI_DBG_VENC("LowPower mode:1\n");
            if(VENC_DRV_EflInitEncParaCfgHevc_LowPwr1(pEncPara))
            {
                HI_ERR_VENC("VENC_DRV_EflInitEncParaCfgHevc failed!\n");
                goto error_1;
            }
        }
    }
    else if (pEncCfg->Protocol == VEDU_H264)
    {
        HI_INFO_VENC("init h264\n");

        if (pstAttr->bLowPowerMode == 0)
        {
            HI_DBG_VENC("LowPower mode:0\n");
            if (VENC_DRV_EflInitEncParaCfgH264_LowPwr0(pEncPara))
            {
                HI_ERR_VENC("VENC_DRV_EflInitEncParaCfgH264 failed!\n");
                goto error_1;
            }
        }
        else
        {
            HI_DBG_VENC("LowPower mode:1\n");
            if (VENC_DRV_EflInitEncParaCfgH264_LowPwr1(pEncPara))
            {
                HI_ERR_VENC("VENC_DRV_EflInitEncParaCfgH264 failed!\n");
                goto error_1;
            }
        }
    }
    else
    {
        HI_ERR_VENC("this protocol is not support!!!\n");
        goto error_1;
    }

    pEncPara->pstCfg_EncPara->vcpi_protocol = pEncCfg->Protocol;
    pEncPara->pstCfg_EncPara->vcpi_crop_en = pstAttr->bEnableCrop;
    if(pEncPara->pstCfg_EncPara->vcpi_crop_en)
    {
        pEncPara->pstCfg_EncPara->vcpi_crop_ystart = pstAttr->CropInfo.u32CropTop;
        pEncPara->pstCfg_EncPara->vcpi_crop_yend = pstAttr->CropInfo.u32CropBottom;
        pEncPara->pstCfg_EncPara->vcpi_crop_xstart = pstAttr->CropInfo.u32CropLeft;
        pEncPara->pstCfg_EncPara->vcpi_crop_xend = pstAttr->CropInfo.u32CropRight;
    }

    pEncPara->pstCfg_EncPara->vcpi_scale_en = pstAttr->bEnableScale;

    if(pEncPara->pstCfg_EncPara->vcpi_scale_en)
    {
        if(pEncPara->pstCfg_EncPara->vcpi_crop_en)
        {
            if ((pstAttr->CropInfo.u32CropHeight<<13)%(HI_S32)pstAttr->ScaleInfo.s32Height == 0)
            {
                pEncPara->pstCfg_EncPara->vcpi_yscale = (pstAttr->CropInfo.u32CropHeight<<13)/(HI_U32)pstAttr->ScaleInfo.s32Height;
            }
            else
            {
                pEncPara->pstCfg_EncPara->vcpi_yscale = (pstAttr->CropInfo.u32CropHeight<<13)/(HI_U32)pstAttr->ScaleInfo.s32Height+1;//配到寄存器要左移13位
            }

            if ((pstAttr->CropInfo.u32CropWidth<<13)%(HI_U32)pstAttr->ScaleInfo.s32Width == 0)
            {
                pEncPara->pstCfg_EncPara->vcpi_xscale = (pstAttr->CropInfo.u32CropWidth<<13)/(HI_U32)pstAttr->ScaleInfo.s32Width;
            }
            else
            {
                pEncPara->pstCfg_EncPara->vcpi_xscale = (pstAttr->CropInfo.u32CropWidth<<13)/(HI_U32)pstAttr->ScaleInfo.s32Width+1;//配到寄存器要左移13位
            }
        }
        else
        {
            if ((pEncCfg->FrameHeight<<13)%(HI_U32)pstAttr->ScaleInfo.s32Height == 0)
            {
                pEncPara->pstCfg_EncPara->vcpi_yscale = (pEncCfg->FrameHeight<<13)/(HI_U32)pstAttr->ScaleInfo.s32Height;
            }
            else
            {
                pEncPara->pstCfg_EncPara->vcpi_yscale =(pEncCfg->FrameHeight<<13)/(HI_U32)pstAttr->ScaleInfo.s32Height+1;//配到寄存器要左移13位
            }

            if ((pEncCfg->FrameWidth<<13)%(HI_U32)pstAttr->ScaleInfo.s32Width == 0)
            {
                pEncPara->pstCfg_EncPara->vcpi_xscale = (pEncCfg->FrameWidth<<13)/(HI_U32)pstAttr->ScaleInfo.s32Width;
            }
            else
            {
                pEncPara->pstCfg_EncPara->vcpi_xscale = (pEncCfg->FrameWidth<<13)/(HI_U32)pstAttr->ScaleInfo.s32Width+1;//配到寄存器要左移13位
            }
        }
        scale_coeff_select(pEncPara->pstCfg_EncPara);
        HI_DBG_VENC("pEncPara->pstCfg_EncPara->vcpi_yscale:0x%x\n",pEncPara->pstCfg_EncPara->vcpi_yscale);
        HI_DBG_VENC("pEncPara->pstCfg_EncPara->vcpi_xscale:0x%x\n",pEncPara->pstCfg_EncPara->vcpi_xscale);
    }

    pEncPara->pstCfg_EncPara->vcpi_oriwidth_pix = pEncCfg->FrameWidth;
    pEncPara->pstCfg_EncPara->vcpi_oriheight_pix =  pEncCfg->FrameHeight;

    if (pEncPara->pstCfg_EncPara->vcpi_crop_en || pEncPara->pstCfg_EncPara->vcpi_scale_en)
    {
        uTmpWidth = pEncCfg->FrameWidth;
        uTmpHeight = pEncCfg->FrameHeight;

        if (pEncPara->pstCfg_EncPara->vcpi_crop_en)
        {
            uTmpWidth = pstAttr->CropInfo.u32CropWidth;
            uTmpHeight = pstAttr->CropInfo.u32CropHeight;
            HI_DBG_VENC("uTmpWidth:%d uTmpHeight:%d\n",uTmpWidth,uTmpHeight);
        }

        if (pEncPara->pstCfg_EncPara->vcpi_scale_en)
        {
            uTmpWidth = pstAttr->ScaleInfo.s32Width;
            uTmpHeight = pstAttr->ScaleInfo.s32Height;
            HI_DBG_VENC("scale:uTmpWidth:%d uTmpHeight:%d\n",uTmpWidth,uTmpHeight);
        }

        pEncCfg->FrameWidth = uTmpWidth;
        pEncCfg->FrameHeight = uTmpHeight;
    }

    pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix = pEncCfg->FrameWidth;
    pEncPara->pstCfg_EncPara->vcpi_imgheight_pix = pEncCfg->FrameHeight;

    pEncPara->pstCfg_EncPara->vcpi_roi_en = pstAttr->bEnableROI;

    if (pEncPara->pstCfg_EncPara->vcpi_roi_en)
    {

        pEncPara->pstCfg_EncPara->region0keep = pstAttr->ROIInfo.bRegion0keep;
        pEncPara->pstCfg_EncPara->absqp0 = pstAttr->ROIInfo.absqp0;
        pEncPara->pstCfg_EncPara->region0en = pstAttr->ROIInfo.bRegion0en;
        pEncPara->pstCfg_EncPara->roiqp0 = pstAttr->ROIInfo.roiqp0;
        pEncPara->pstCfg_EncPara->start0_roistartx = pstAttr->ROIInfo.start0_roistartx;
        pEncPara->pstCfg_EncPara->start0_roistarty = pstAttr->ROIInfo.start0_roistarty;
        pEncPara->pstCfg_EncPara->size0_roiwidth = pstAttr->ROIInfo.size0_roiwidth;
        pEncPara->pstCfg_EncPara->size0_roiheight = pstAttr->ROIInfo.size0_roiheight;

        HI_DBG_VENC("create:pstAttr->ROIInfo.roiqp0:%d\n",pstAttr->ROIInfo.roiqp0);
        HI_DBG_VENC("create:pEncPara->pstCfg_EncPara->roiqp0:%d\n",pEncPara->pstCfg_EncPara->roiqp0);

        pEncPara->pstCfg_EncPara->region1keep = pstAttr->ROIInfo.bRegion1keep;
        pEncPara->pstCfg_EncPara->absqp1 = pstAttr->ROIInfo.absqp1;
        pEncPara->pstCfg_EncPara->region1en = pstAttr->ROIInfo.bRegion1en;
        pEncPara->pstCfg_EncPara->roiqp1 = pstAttr->ROIInfo.roiqp1;
        pEncPara->pstCfg_EncPara->start1_roistartx = pstAttr->ROIInfo.start1_roistartx;
        pEncPara->pstCfg_EncPara->start1_roistarty = pstAttr->ROIInfo.start1_roistarty;
        pEncPara->pstCfg_EncPara->size1_roiwidth = pstAttr->ROIInfo.size1_roiwidth;
        pEncPara->pstCfg_EncPara->size1_roiheight = pstAttr->ROIInfo.size1_roiheight;

        pEncPara->pstCfg_EncPara->region2keep = pstAttr->ROIInfo.bRegion2keep;
        pEncPara->pstCfg_EncPara->absqp2 = pstAttr->ROIInfo.absqp2;
        pEncPara->pstCfg_EncPara->region2en = pstAttr->ROIInfo.bRegion2en;
        pEncPara->pstCfg_EncPara->roiqp2 = pstAttr->ROIInfo.roiqp2;
        pEncPara->pstCfg_EncPara->start2_roistartx = pstAttr->ROIInfo.start2_roistartx;
        pEncPara->pstCfg_EncPara->start2_roistarty = pstAttr->ROIInfo.start2_roistarty;
        pEncPara->pstCfg_EncPara->size2_roiwidth = pstAttr->ROIInfo.size2_roiwidth;
        pEncPara->pstCfg_EncPara->size2_roiheight = pstAttr->ROIInfo.size2_roiheight;

        pEncPara->pstCfg_EncPara->region3keep = pstAttr->ROIInfo.bRegion3keep;
        pEncPara->pstCfg_EncPara->absqp3 = pstAttr->ROIInfo.absqp3;
        pEncPara->pstCfg_EncPara->region3en = pstAttr->ROIInfo.bRegion3en;
        pEncPara->pstCfg_EncPara->roiqp3 = pstAttr->ROIInfo.roiqp3;
        pEncPara->pstCfg_EncPara->start3_roistartx = pstAttr->ROIInfo.start3_roistartx;
        pEncPara->pstCfg_EncPara->start3_roistarty = pstAttr->ROIInfo.start3_roistarty;
        pEncPara->pstCfg_EncPara->size3_roiwidth = pstAttr->ROIInfo.size3_roiwidth;
        pEncPara->pstCfg_EncPara->size3_roiheight = pstAttr->ROIInfo.size3_roiheight;

        pEncPara->pstCfg_EncPara->region4keep = pstAttr->ROIInfo.bRegion4keep;
        pEncPara->pstCfg_EncPara->absqp4 = pstAttr->ROIInfo.absqp4;
        pEncPara->pstCfg_EncPara->region4en = pstAttr->ROIInfo.bRegion4en;
        pEncPara->pstCfg_EncPara->roiqp4 = pstAttr->ROIInfo.roiqp4;
        pEncPara->pstCfg_EncPara->start4_roistartx = pstAttr->ROIInfo.start4_roistartx;
        pEncPara->pstCfg_EncPara->start4_roistarty = pstAttr->ROIInfo.start4_roistarty;
        pEncPara->pstCfg_EncPara->size4_roiwidth = pstAttr->ROIInfo.size4_roiwidth;
        pEncPara->pstCfg_EncPara->size4_roiheight = pstAttr->ROIInfo.size4_roiheight;

        pEncPara->pstCfg_EncPara->region5keep = pstAttr->ROIInfo.bRegion5keep;
        pEncPara->pstCfg_EncPara->absqp5 = pstAttr->ROIInfo.absqp5;
        pEncPara->pstCfg_EncPara->region5en = pstAttr->ROIInfo.bRegion5en;
        pEncPara->pstCfg_EncPara->roiqp5 = pstAttr->ROIInfo.roiqp5;
        pEncPara->pstCfg_EncPara->start5_roistartx = pstAttr->ROIInfo.start5_roistartx;
        pEncPara->pstCfg_EncPara->start5_roistarty = pstAttr->ROIInfo.start5_roistarty;
        pEncPara->pstCfg_EncPara->size5_roiwidth = pstAttr->ROIInfo.size5_roiwidth;
        pEncPara->pstCfg_EncPara->size5_roiheight = pstAttr->ROIInfo.size5_roiheight;

        pEncPara->pstCfg_EncPara->region6keep = pstAttr->ROIInfo.bRegion6keep;
        pEncPara->pstCfg_EncPara->absqp6 = pstAttr->ROIInfo.absqp6;
        pEncPara->pstCfg_EncPara->region6en = pstAttr->ROIInfo.bRegion6en;
        pEncPara->pstCfg_EncPara->roiqp6 = pstAttr->ROIInfo.roiqp6;
        pEncPara->pstCfg_EncPara->start6_roistartx = pstAttr->ROIInfo.start6_roistartx;
        pEncPara->pstCfg_EncPara->start6_roistarty = pstAttr->ROIInfo.start6_roistarty;
        pEncPara->pstCfg_EncPara->size6_roiwidth = pstAttr->ROIInfo.size6_roiwidth;
        pEncPara->pstCfg_EncPara->size6_roiheight = pstAttr->ROIInfo.size6_roiheight;

        pEncPara->pstCfg_EncPara->region7keep = pstAttr->ROIInfo.bRegion7keep;
        pEncPara->pstCfg_EncPara->absqp7 = pstAttr->ROIInfo.absqp7;
        pEncPara->pstCfg_EncPara->region7en = pstAttr->ROIInfo.bRegion7en;
        pEncPara->pstCfg_EncPara->roiqp7 = pstAttr->ROIInfo.roiqp7;
        pEncPara->pstCfg_EncPara->start7_roistartx = pstAttr->ROIInfo.start7_roistartx;
        pEncPara->pstCfg_EncPara->start7_roistarty = pstAttr->ROIInfo.start7_roistarty;
        pEncPara->pstCfg_EncPara->size7_roiwidth = pstAttr->ROIInfo.size7_roiwidth;
        pEncPara->pstCfg_EncPara->size7_roiheight = pstAttr->ROIInfo.size7_roiheight;

    }

	pEncPara->pstCfg_EncPara->vcpi_store_mode     = pstAttr->uiYUVStoreMode;
	pEncPara->vcpi_store_mode                     = pstAttr->uiYUVStoreMode;
	pEncPara->bMMUByPass                          = pstAttr->bMMUByPass;
	pEncPara->pstCfg_EncPara->vcpi_wide_narrow_en = pstAttr->WideToNarrowEn;

	if (1 != pstAttr->ui32nSlices && pstAttr->bSlcSplitEn)
	{
		pEncPara->pstCfg_EncPara->vcpi_multislc_en  = 1;
		pEncPara->pstCfg_EncPara->vcpi_slcspilt_mod = 1;//按照寄存器表描述，当前必须为1，按Lcu行划分
		HI_DBG_VENC("%s, pstAttr->ui32nSlices:%d pEncPara->pstCfg_EncPara->vcpi_imgheight_pix:%d\n", __func__, pstAttr->ui32nSlices,pEncPara->pstCfg_EncPara->vcpi_imgheight_pix);

		if(pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)//MB 16*16
		{
			//OMX层已保证slice划分个数是符合规则的
			pEncPara->pstCfg_EncPara->vcpi_slice_size = (ALIGN_UP(pEncPara->pstCfg_EncPara->vcpi_imgheight_pix,16)/16) / pstAttr->ui32nSlices ;
			if((ALIGN_UP(pEncPara->pstCfg_EncPara->vcpi_imgheight_pix,16)/16) % pstAttr->ui32nSlices)
			{
				pEncPara->pstCfg_EncPara->vcpi_slice_size++;
			}
		}
		else//LCU 64*64
		{
			pEncPara->pstCfg_EncPara->vcpi_slice_size = (ALIGN_UP(pEncPara->pstCfg_EncPara->vcpi_imgheight_pix,64)/64) / pstAttr->ui32nSlices ;
			if((ALIGN_UP(pEncPara->pstCfg_EncPara->vcpi_imgheight_pix,64)/64) % pstAttr->ui32nSlices)
			{
				pEncPara->pstCfg_EncPara->vcpi_slice_size++;
			}
		}
	}
	else
	{
		pEncPara->pstCfg_EncPara->vcpi_multislc_en  = 0;
		pEncPara->pstCfg_EncPara->vcpi_slcspilt_mod = 1;
		pEncPara->iSliceSplitNum                    = 1;
		pEncPara->pstCfg_EncPara->vcpi_slice_size   = 0;
	}

	{
		pEncPara->pstCfg_EncPara->min_qp			= pstAttr->u32MinQp;
		pEncPara->pstCfg_EncPara->max_qp			= pstAttr->u32MaxQp;

		HI_INFO_VENC("enVencHevcProfile:%d\n",pstAttr->enVencHevcProfile);
		HI_INFO_VENC("enVencAvcProfile:%d\n",pstAttr->enVencProfile);

		HI_INFO_VENC("u32TargetBitRate:%d\n",pstAttr->u32TargetBitRate);
		HI_INFO_VENC("u32Gop:%d\n",pstAttr->u32Gop);
		HI_INFO_VENC("MaxQp:%d MinQp:%d \n",pstAttr->u32MaxQp,pstAttr->u32MinQp);
		HI_INFO_VENC("h265Level:%d\n",pstAttr->h265Level);


		HI_INFO_VENC("pstAttr->ui32nSlices:%d pstAttr->bSlcSplitEn:%d\n",pstAttr->ui32nSlices,pstAttr->bSlcSplitEn);

		HI_INFO_VENC("pstAttr->bEnableCrop:%d\n",pstAttr->bEnableCrop);
		HI_INFO_VENC("CropInfo.u32CropHeight:%d\n",pstAttr->CropInfo.u32CropHeight);
		HI_INFO_VENC("CropInfo.u32CropWidth:%d\n",pstAttr->CropInfo.u32CropWidth);
		HI_INFO_VENC("CropInfo.u32CropLeft:%d\n",pstAttr->CropInfo.u32CropLeft);
		HI_INFO_VENC("CropInfo.u32CropTop:%d\n",pstAttr->CropInfo.u32CropTop);

		HI_INFO_VENC("pstAttr->bEnableCrop:%d\n",pstAttr->bEnableScale);
		HI_INFO_VENC("ScaleInfo.s32Height:%d\n",pstAttr->ScaleInfo.s32Height);
		HI_INFO_VENC("ScaleInfo.s32Widt:%d\n",pstAttr->ScaleInfo.s32Width);

		HI_INFO_VENC("bEnableROI:%d\n",pstAttr->bEnableROI);

		HI_INFO_VENC("bLowPowerMode:%d\n",pstAttr->bLowPowerMode);
		HI_INFO_VENC("bInputLowDelayMode:%d\n",pstAttr->bInputLowDelayMode);
		HI_INFO_VENC("bOutputLowDelayMode:%d\n",pstAttr->bOutputLowDelayMode);
		HI_INFO_VENC("pEncPara->bMMUByPass:%d\n",pEncPara->bMMUByPass);
	}

	if (pEncCfg->Protocol == VEDU_H264)
	{
		if (HI_UNF_H264_PROFILE_BASELINE == pstAttr->enVencProfile)
		{
			pEncPara->pstCfg_EncPara->vcpi_trans_mode  = 1; // 4*4
			pEncPara->pstCfg_EncPara->vcpi_intra_cu_en = 0x5;
		}
		else if(HI_UNF_H264_PROFILE_MAIN == pstAttr->enVencProfile)
		{
			pEncPara->pstCfg_EncPara->vcpi_trans_mode  = 1;// 4*4
			pEncPara->pstCfg_EncPara->vcpi_intra_cu_en = 0x5;
		}
		else if(HI_UNF_H264_PROFILE_HIGH == pstAttr->enVencProfile)
		{
			pEncPara->pstCfg_EncPara->vcpi_trans_mode  = 0;// 4*4 &8*8
			pEncPara->pstCfg_EncPara->vcpi_intra_cu_en = 0x7;
		}

	    if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)
		{
			pEncPara->H264Profile                       = (HI_U32)pstAttr->enVencProfile;
			pEncPara->pstCfg_EncPara->vcpi_entropy_mode = (pEncPara->H264Profile == VEDU_H264_BASELINE_PROFILE)? 1 : 0;
			if(pEncCfg->FrameWidth*pEncCfg->FrameHeight > 1920*1080)
			{
				pEncPara->pstCfg_EncPara->vcpi_entropy_mode = 1;//分辨率大，不使用cabac
			}
	    }
	}

	// 高帧率关闭intra 4x4 图像增强功能  to do
	if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_HEVC)
	{
		if ((pstAttr->u32InputFrmRate >= 240 && pEncCfg->FrameWidth*pEncCfg->FrameHeight >= 1280*720)
			|| (pstAttr->u32InputFrmRate >= 360 && pEncCfg->FrameWidth*pEncCfg->FrameHeight >= 800*480)
			|| (pstAttr->u32InputFrmRate >= 120 && pEncCfg->FrameWidth*pEncCfg->FrameHeight >= 1920*1080))
		{
			HI_INFO_VENC("%s, High FrameRate Mode!\n", __func__);
			pEncPara->pstCfg_EncPara->vcpi_intra_cu_en    = pEncPara->pstCfg_EncPara->vcpi_intra_cu_en & 0xe;
			pEncPara->pstCfg_EncPara->vcpi_img_improve_en = 0;
		}
	}

    if (pEncPara->bSecureFlag == 1)
    {
        pEncPara->bMMUByPass = 1;
		pEncPara->pstCfg_EncPara->glb_scr = 0;

        pEncPara->pstCfg_EncPara->sid0_bypass = 1;
        pEncPara->pstCfg_EncPara->sid1_bypass = 1;
        pEncPara->pstCfg_EncPara->sid2_bypass = 1;
        pEncPara->pstCfg_EncPara->sid3_bypass = 1;
        pEncPara->pstCfg_EncPara->sid4_bypass = 1;
        pEncPara->pstCfg_EncPara->sid5_bypass = 1;
        pEncPara->pstCfg_EncPara->sid6_bypass = 1;
        pEncPara->pstCfg_EncPara->sid7_bypass = 1;
        pEncPara->pstCfg_EncPara->sid8_bypass = 1;
        pEncPara->pstCfg_EncPara->sid9_bypass = 1;
        pEncPara->pstCfg_EncPara->sid10_bypass = 1;
        pEncPara->pstCfg_EncPara->sid11_bypass = 1;
        pEncPara->pstCfg_EncPara->sid12_bypass = 1;
        pEncPara->pstCfg_EncPara->sid13_bypass = 1;
        pEncPara->pstCfg_EncPara->sid14_bypass = 1;
        pEncPara->pstCfg_EncPara->sid15_bypass = 1;
        pEncPara->pstCfg_EncPara->sid16_bypass = 1;
        pEncPara->pstCfg_EncPara->sid17_bypass = 1;

        pEncPara->pstCfg_EncPara->sid18_bypass = 0;
        pEncPara->pstCfg_EncPara->sid19_bypass = 0;
        pEncPara->pstCfg_EncPara->sid20_bypass = 0;
        pEncPara->pstCfg_EncPara->sid21_bypass = 0;
        pEncPara->pstCfg_EncPara->sid22_bypass = 0;
        pEncPara->pstCfg_EncPara->sid23_bypass = 0;
        pEncPara->pstCfg_EncPara->sid24_bypass = 0;
        pEncPara->pstCfg_EncPara->sid25_bypass = 0;
        pEncPara->pstCfg_EncPara->sid26_bypass = 0;
        pEncPara->pstCfg_EncPara->sid27_bypass = 0;
        pEncPara->pstCfg_EncPara->sid28_bypass = 0;
        pEncPara->pstCfg_EncPara->sid29_bypass = 0;
        pEncPara->pstCfg_EncPara->sid30_bypass = 0;
        pEncPara->pstCfg_EncPara->sid31_bypass = 0;
        pEncPara->pstCfg_EncPara->sid32_bypass = 0;
        pEncPara->pstCfg_EncPara->sid33_bypass = 0;
        pEncPara->pstCfg_EncPara->sid34_bypass = 0;
        pEncPara->pstCfg_EncPara->sid35_bypass = 0;

        pEncPara->pstCfg_EncPara->comn0_smr0_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr1_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr2_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr3_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr4_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr5_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr6_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr7_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr8_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr9_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr10_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr11_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr12_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr13_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr14_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr15_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr16_bypass = 1;
        pEncPara->pstCfg_EncPara->comn0_smr17_bypass = 1;

        pEncPara->pstCfg_EncPara->comn0_smr18_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr19_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr20_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr21_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr22_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr23_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr24_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr25_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr26_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr27_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr28_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr29_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr30_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr31_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr32_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr33_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr34_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr35_bypass = 0;

        pEncPara->pstCfg_EncPara->comn0_smr18_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr19_ptw_qos = 3;
        pEncPara->pstCfg_EncPara->comn0_smr20_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr21_ptw_qos = 3;
        pEncPara->pstCfg_EncPara->comn0_smr22_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr23_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr24_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr25_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr26_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr27_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr28_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr29_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr30_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr31_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr32_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr33_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr34_ptw_qos = 3;
		pEncPara->pstCfg_EncPara->comn0_smr35_ptw_qos = 3;
	}
	else
	{
        pEncPara->pstCfg_EncPara->glb_scr = 1;
        if( pEncPara->bMMUByPass  == 0 )
        {
            pEncPara->pstCfg_EncPara->sid18_bypass = 0;
            pEncPara->pstCfg_EncPara->sid19_bypass = 0;
            pEncPara->pstCfg_EncPara->sid20_bypass = 0;
            pEncPara->pstCfg_EncPara->sid21_bypass = 0;
            pEncPara->pstCfg_EncPara->sid22_bypass = 0;
            pEncPara->pstCfg_EncPara->sid23_bypass = 0;
            pEncPara->pstCfg_EncPara->sid24_bypass = 0;
            pEncPara->pstCfg_EncPara->sid25_bypass = 0;
            pEncPara->pstCfg_EncPara->sid26_bypass = 0;
            pEncPara->pstCfg_EncPara->sid27_bypass = 0;
            pEncPara->pstCfg_EncPara->sid28_bypass = 0;
            pEncPara->pstCfg_EncPara->sid29_bypass = 0;
            pEncPara->pstCfg_EncPara->sid30_bypass = 0;
            pEncPara->pstCfg_EncPara->sid31_bypass = 0;
            pEncPara->pstCfg_EncPara->sid32_bypass = 0;
            pEncPara->pstCfg_EncPara->sid33_bypass = 0;
            pEncPara->pstCfg_EncPara->sid34_bypass = 0;
            pEncPara->pstCfg_EncPara->sid35_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr18_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr19_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr20_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr21_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr22_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr23_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr24_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr25_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr26_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr27_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr28_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr29_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr30_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr31_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr32_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr33_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr34_bypass = 0;
            pEncPara->pstCfg_EncPara->comn0_smr35_bypass = 0;
        }
        else
        {
            pEncPara->pstCfg_EncPara->sid18_bypass = 1;
            pEncPara->pstCfg_EncPara->sid19_bypass = 1;
            pEncPara->pstCfg_EncPara->sid20_bypass = 1;
            pEncPara->pstCfg_EncPara->sid21_bypass = 1;
            pEncPara->pstCfg_EncPara->sid22_bypass = 1;
            pEncPara->pstCfg_EncPara->sid23_bypass = 1;
            pEncPara->pstCfg_EncPara->sid24_bypass = 1;
            pEncPara->pstCfg_EncPara->sid25_bypass = 1;
            pEncPara->pstCfg_EncPara->sid26_bypass = 1;
            pEncPara->pstCfg_EncPara->sid27_bypass = 1;
            pEncPara->pstCfg_EncPara->sid28_bypass = 1;
            pEncPara->pstCfg_EncPara->sid29_bypass = 1;
            pEncPara->pstCfg_EncPara->sid30_bypass = 1;
            pEncPara->pstCfg_EncPara->sid31_bypass = 1;
            pEncPara->pstCfg_EncPara->sid32_bypass = 1;
            pEncPara->pstCfg_EncPara->sid33_bypass = 1;
            pEncPara->pstCfg_EncPara->sid34_bypass = 1;
            pEncPara->pstCfg_EncPara->sid35_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr18_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr19_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr20_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr21_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr22_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr23_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr24_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr25_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr26_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr27_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr28_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr29_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr30_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr31_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr32_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr33_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr34_bypass = 1;
            pEncPara->pstCfg_EncPara->comn0_smr35_bypass = 1;
        }
        pEncPara->pstCfg_EncPara->sid0_bypass = 0;
        pEncPara->pstCfg_EncPara->sid1_bypass = 0;
        pEncPara->pstCfg_EncPara->sid2_bypass = 0;
        pEncPara->pstCfg_EncPara->sid3_bypass = 0;
        pEncPara->pstCfg_EncPara->sid4_bypass = 0;
        pEncPara->pstCfg_EncPara->sid5_bypass = 0;
        pEncPara->pstCfg_EncPara->sid6_bypass = 0;
        pEncPara->pstCfg_EncPara->sid7_bypass = 0;
        pEncPara->pstCfg_EncPara->sid8_bypass = 0;
        pEncPara->pstCfg_EncPara->sid9_bypass = 0;
        pEncPara->pstCfg_EncPara->sid10_bypass = 0;
        pEncPara->pstCfg_EncPara->sid11_bypass = 0;
        pEncPara->pstCfg_EncPara->sid12_bypass = 0;
        pEncPara->pstCfg_EncPara->sid13_bypass = 0;
        pEncPara->pstCfg_EncPara->sid14_bypass = 0;
        pEncPara->pstCfg_EncPara->sid15_bypass = 0;
        pEncPara->pstCfg_EncPara->sid16_bypass = 0;
        pEncPara->pstCfg_EncPara->sid17_bypass = 0;

        pEncPara->pstCfg_EncPara->comn0_smr0_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr1_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr2_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr3_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr4_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr5_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr6_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr7_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr8_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr9_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr10_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr11_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr12_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr13_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr14_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr15_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr16_bypass = 0;
        pEncPara->pstCfg_EncPara->comn0_smr17_bypass = 0;

        pEncPara->pstCfg_EncPara->comn0_smr18_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr19_ptw_qos = 0;
        pEncPara->pstCfg_EncPara->comn0_smr20_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr21_ptw_qos = 0;
        pEncPara->pstCfg_EncPara->comn0_smr22_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr23_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr24_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr25_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr26_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr27_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr28_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr29_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr30_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr31_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr32_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr33_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr34_ptw_qos = 0;
		pEncPara->pstCfg_EncPara->comn0_smr35_ptw_qos = 0;
	}

    if(pEncPara->pstCfg_EncPara->glb_scr == 0){
        pEncPara->pstCfg_EncPara->comn2_smr0_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr0_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr1_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr1_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr2_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr2_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr3_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr3_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr4_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr4_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr5_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr5_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr6_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr6_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr7_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr7_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr8_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr8_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr9_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr9_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr10_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr10_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr11_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr11_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr12_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr12_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr13_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr13_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr14_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr14_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr15_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr15_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr16_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr16_nscfg_en = 0;
        pEncPara->pstCfg_EncPara->comn2_smr17_nscfg = 0;
        pEncPara->pstCfg_EncPara->comn2_smr17_nscfg_en = 0;
    }
    else{
        pEncPara->pstCfg_EncPara->comn2_smr18_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr18_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr19_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr19_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr20_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr20_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr21_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr21_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr22_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr22_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr23_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr23_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr24_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr24_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr25_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr25_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr26_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr26_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr27_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr27_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr28_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr28_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr29_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr29_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr30_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr30_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr31_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr31_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr32_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr32_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr33_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr33_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr34_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr34_nscfg_en = 1;
        pEncPara->pstCfg_EncPara->comn2_smr35_nscfg = 1;
        pEncPara->pstCfg_EncPara->comn2_smr35_nscfg_en = 1;
    }

    // check函数
    check_enc_para(pEncPara->pstCfg_EncPara, HI_TRUE);

#ifdef SAO_LOWPOWER_EN
    pEncPara->aiRatioSaoLumaOff          = SAO_RATIO_OFF_LUMA;
    pEncPara->aiRatioSaoChromaOff       = SAO_RATIO_OFF_CHROMA;
    pEncPara->numof_Frame_Refresh      = SAO_FRAME_REFRESH;
    pEncPara->Sao_Frame_Count           = 0;
#endif

    if (pEncPara->pstCfg_EncPara->vcpi_multislc_en == 1)
    {
        pEncPara->iSliceSplitNum = pstAttr->ui32nSlices;
    }

	if (pEncPara->pstCfg_EncPara->vcpi_protocol == VEDU_H265)
	{
		uRECLumaSize       = ALIGN_UP(pEncCfg->FrameWidth,256)*ALIGN_UP(pEncCfg->FrameHeight,16);
		uRECChromaSize     = ALIGN_UP(pEncCfg->FrameWidth,256)*ALIGN_UP(pEncCfg->FrameHeight/2,16);
		uNBISize           = WidthInCtb*HeightInCtb*64;
		uPMESize           = WidthInCtb*HeightInCtb*256;
		uRECLumaHeadSize   = ALIGN_UP(pEncCfg->FrameWidth,64)/2*HeightInCtb;
		uRECChromaHeadSize = ALIGN_UP(pEncCfg->FrameWidth,64)/2*HeightInCtb;
	}
	else if (pEncPara->pstCfg_EncPara->vcpi_protocol == VEDU_H264)
	{
		uRECLumaSize       = ALIGN_UP(pEncCfg->FrameWidth,256)*ALIGN_UP(pEncCfg->FrameHeight,16);
		uRECChromaSize     = ALIGN_UP(pEncCfg->FrameWidth,256)*ALIGN_UP(pEncCfg->FrameHeight/2,16);
		uNBISize           = WidthInMb*HeightInMb*64;
		uPMESize           = WidthInMb*HeightInMb*256;
		uRECLumaHeadSize   = ALIGN_UP(pEncCfg->FrameWidth,256)/8*HeightInMb;
		uRECChromaHeadSize = ALIGN_UP(pEncCfg->FrameWidth,256)/8*HeightInMb;
	}

    uRECLumaAlignSize = ALIGN_UP(uRECLumaSize,0x8000);
    uRECChromaAlignSize = ALIGN_UP(uRECChromaSize,0x8000);
    uNBIAlignSize = ALIGN_UP(uNBISize,0x8000);
    uPMEAlignSize = ALIGN_UP(uPMESize,0x8000);
    uRECLumaHeadAlignSize = ALIGN_UP(uRECLumaHeadSize,0x8000);
    uRECChromaHeadAlignSize = ALIGN_UP(uRECChromaHeadSize,0x8000);
    uAllocteTotalSize = (uRECLumaAlignSize + uRECChromaAlignSize + uNBIAlignSize
                        + uPMEAlignSize + uRECLumaHeadAlignSize + uRECChromaHeadAlignSize + 128)*2 + 0x8000;

    pEncPara->bAXIPressEn = 1; //默认开启反压

    iRet = DRV_MMU_MEM_AllocAndMap("ALL_MEM","OMXVENC",uAllocteTotalSize,0,&(pEncPara->MEM_VEDU_START_ADDR),pEncPara->bMMUByPass);
    if (iRet != 0)
    {
        HI_ERR_VENC("allocte mem error\n");
        goto error_2;
    }
    u32StartPhyAlignAddr = ALIGN_UP(pEncPara->MEM_VEDU_START_ADDR.u32StartPhyAddr,0x8000);
    pStartVirAlignAddr = pEncPara->MEM_VEDU_START_ADDR.pStartVirAddr + (u32StartPhyAlignAddr - pEncPara->MEM_VEDU_START_ADDR.u32StartPhyAddr);

    pEncPara->RcnYAddr[0] = u32StartPhyAlignAddr;
    pEncPara->RcnYLength = uRECLumaSize;
    pEncPara->VirRcnYAddr[0] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECLumaAlignSize;
    pStartVirAlignAddr +=  uRECLumaAlignSize;

    pEncPara->RcnCAddr[0] = u32StartPhyAlignAddr;
    pEncPara->RcnCLength = uRECChromaSize;
    pEncPara->VirRcnCAddr[0] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECChromaAlignSize;
    pStartVirAlignAddr +=  uRECChromaAlignSize;

    pEncPara->RcnYAddr[1] = u32StartPhyAlignAddr;
    pEncPara->VirRcnYAddr[1] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECLumaSize;
    pStartVirAlignAddr +=  uRECLumaSize;

    pEncPara->RcnCAddr[1] = u32StartPhyAlignAddr;
    pEncPara->VirRcnCAddr[1] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECChromaAlignSize;
    pStartVirAlignAddr +=  uRECChromaAlignSize;

    pEncPara->RcnYHeadAddr[0] = u32StartPhyAlignAddr;
    pEncPara->RcnYHeadLength = uRECLumaHeadSize;//pEncPara->MEM_RcnYHeadAddr[0].u32Size;
    pEncPara->VirRcnYHAddr[0] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECLumaHeadAlignSize;
    pStartVirAlignAddr +=  uRECLumaHeadAlignSize;

    pEncPara->RcnCHeadAddr[0] = u32StartPhyAlignAddr;
    pEncPara->RcnCHeadLength = uRECChromaHeadSize;//pEncPara->MEM_RcnCHeadAddr[0].u32Size;
    pEncPara->VirRcnCHAddr[0] = pStartVirAlignAddr;;
    u32StartPhyAlignAddr += uRECChromaHeadAlignSize;
    pStartVirAlignAddr +=  uRECChromaHeadAlignSize;

    pEncPara->RcnYHeadAddr[1] = u32StartPhyAlignAddr;
    pEncPara->VirRcnYHAddr[1] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECLumaHeadAlignSize;
    pStartVirAlignAddr +=  uRECLumaHeadAlignSize;

    pEncPara->RcnCHeadAddr[1] = u32StartPhyAlignAddr;
    pEncPara->VirRcnCHAddr[1] = pStartVirAlignAddr;
    u32StartPhyAlignAddr += uRECChromaHeadAlignSize;
    pStartVirAlignAddr +=  uRECChromaHeadAlignSize;

    pEncPara->VEDU_NBI_MVST_ADDR = u32StartPhyAlignAddr;
    pEncPara->VEDU_NBI_MVST_Length = uNBISize;//pEncPara->MEM_VEDU_NBI_MVST_ADDR.u32Size;
    u32StartPhyAlignAddr += uNBIAlignSize;

    pEncPara->VEDU_NBI_MVLD_ADDR = u32StartPhyAlignAddr;
    pEncPara->VEDU_NBI_MVLD_Length = uNBISize;//pEncPara->MEM_VEDU_NBI_MVLD_ADDR.u32Size;
    u32StartPhyAlignAddr += uNBIAlignSize;

    pEncPara->VEDU_PMELD_ADDR = u32StartPhyAlignAddr;
    pEncPara->VEDU_PMELD_Length =uPMESize;// pEncPara->MEM_VEDU_PMELD_ADDR.u32Size;
    u32StartPhyAlignAddr += uPMEAlignSize;

    pEncPara->VEDU_PMEST_ADDR = u32StartPhyAlignAddr;
    pEncPara->VEDU_PMEST_Length = uPMESize;//pEncPara->MEM_VEDU_PMEST_ADDR.u32Size;
    u32StartPhyAlignAddr += uPMEAlignSize;

    pEncPara->MMURdAddr = u32StartPhyAlignAddr;
    pEncPara->VEDU_MMU_ERR_RD_Length = 128;//pEncPara->MEM_VEDU_PMEST_ADDR.u32Size;
    u32StartPhyAlignAddr += 128;

    pEncPara->MMUWrAddr = u32StartPhyAlignAddr;
    pEncPara->VEDU_MMU_ERR_WR_Length = 128;//pEncPara->MEM_VEDU_PMEST_ADDR.u32Size;
    u32StartPhyAlignAddr += 128;

    printk("u32StartPhyAlignAddr - pEncPara->MEM_VEDU_START_ADDR.u32StartPhyAddr:0x%x uAllocteTotalSize:0x%x\n",
       u32StartPhyAlignAddr - pEncPara->MEM_VEDU_START_ADDR.u32StartPhyAddr,uAllocteTotalSize );

    pEncPara->RcnIdx = 0;

/************************************* add ******************************************/

    pEncPara->FrameQueue_OMX = VENC_DRV_MngQueueInit(MAX_VEDU_QUEUE_NUM,HI_TRUE);
	if (HI_NULL == pEncPara->FrameQueue_OMX)
	{
		HI_ERR_VENC("%s, failed to init FrameQueue, size = %d\n", __func__, sizeof(queue_info_s));
        goto error_4;
	}

    pEncPara->StreamQueue_OMX = VENC_DRV_MngQueueInit(MAX_VEDU_QUEUE_NUM,HI_TRUE);
	HI_DBG_VENC("%s, pEncPara->StreamQueue_OMX:0x%x\n", __func__, pEncPara->StreamQueue_OMX);
	if (HI_NULL == pEncPara->StreamQueue_OMX)
	{
		HI_ERR_VENC("%s, failed to init StreamQueue, size = %d\n", __func__, sizeof(queue_info_s));
        goto error_5;
	}

    pEncPara->MsgQueue_OMX = VENC_DRV_MngQueueInit(MSG_QUEUE_NUM,HI_TRUE);
	if (HI_NULL == pEncPara->MsgQueue_OMX)
	{
		HI_ERR_VENC("%s, failed to init MsgQueue, size = %d\n", __func__, sizeof(queue_info_s));
        goto error_6;
    }

    /* get channel para */
    pEncPara->vcpi_protocol  = pEncCfg->Protocol;
    pEncPara->vcpi_imgwidth_pix  = pEncCfg->FrameWidth;//WidthInMb  << 4;
    pEncPara->vcpi_imgheight_pix = pEncCfg->FrameHeight;//HeightInMb << 4;

    HI_INFO_VENC("vcpi_imgheight_pix:%d", pEncPara->vcpi_imgheight_pix);
    HI_INFO_VENC("vcpi_imgwidth_pix:%d", pEncPara->vcpi_imgwidth_pix);

    pEncPara->vcpi_multislc_en = pEncPara->pstCfg_EncPara->vcpi_multislc_en;

    pEncPara->Priority   = pEncCfg->Priority;
    pEncPara->Gop        = pEncCfg->Gop;
    pEncPara->WaitingIsr = 0;
    pEncPara->CalcMd5Flag = 1;
    pEncPara->pRegBase = VeduIpCtx.pRegBase;

    /* other */
    pEncPara->NumRefIndex = 0;

    //pEncPara->iSliceSplitNum = 1; //先设置成划分两个slice   l00214825
    pEncPara->iCurrentStreamCnt = 0;
#ifdef OUTPUT_LOWDELAY_EN
	pEncPara->iLastEncodedStreamCnt = 0;
#endif
	/* make sps & pps & VOL stream */
    VENC_DRV_EflFlushStrmHeader(pEncPara);

    /* init RC para */
    pEncPara->IntraPic = 1;
    pEncPara->bAddHeader = HI_TRUE;
    pEncPara->bFirstNal2Send = HI_TRUE;

    pEncPara->stRc.FrmNumInGop = 0;
    pEncPara->stRc.MinTimeOfP = 3;
    pEncPara->stRc.MaxTimeOfP = 5;
    pEncPara->stRc.DeltaTimeOfP = 0;
    pEncPara->stRc.AveFrameMinusAveP = 0;     //15; change by tyx
    pEncPara->stRc.StillToMoveDelay  = 8;
    pEncPara->stRc.IQpDelta = 2;
    pEncPara->stRc.PQpDelta = 2;
    pEncPara->stRc.MbNum    = WidthInMb * HeightInMb;

    pEncPara->stSrcInfo.handle = HI_INVALID_HANDLE;

    /* get return val */
    *pEncHandle = (HI_HANDLE)pEncPara;

	HI_INFO_VENC("exit %s, pEncHandle:0x%x\n", __func__, pEncHandle);
    return HI_SUCCESS;

error_6:
	VENC_DRV_MngQueueDeinit(pEncPara->StreamQueue_OMX);
error_5:
	VENC_DRV_MngQueueDeinit(pEncPara->FrameQueue_OMX);
error_4:
	//HI_DRV_MMZ_Unmap(&sMBufVenc);
//error_3:

error_2:
    //HI_DRV_MMZ_Release(&sMBufVenc);
error_1:
    if(NULL != pEncPara)
    {
        kfree((HI_VOID *)pEncPara);
        pEncPara = NULL;
    }

	HI_ERR_VENC("%s, creat channel failed, pEncHandle:0x%x\n", __func__, pEncHandle);
    return HI_FAILURE;
}

HI_S32 VENC_DRV_EflDestroyVenc( HI_HANDLE EncHandle )
{
    VEDU_LOCK_FLAG flag;

	VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;
	if((HI_U64)NULL == EncHandle)
	{
    	HI_ERR_VENC("%s, EncHandle can not be null\n", __func__);
    	return HI_FAILURE;
    }

	HI_INFO_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);
    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag );

    DRV_MMU_MEM_UnmapAndRelease(&(pEncPara->MEM_VEDU_START_ADDR),pEncPara->bMMUByPass);

    if( VENC_DRV_MngQueueDeinit(pEncPara->StreamQueue_OMX))
	{
		HI_ERR_VENC("HI_KFREE failed to free StreamQueue_OMX, size = %d\n", sizeof(queue_info_s));
		VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
		return HI_FAILURE;
	}

    if( VENC_DRV_MngQueueDeinit(pEncPara->FrameQueue_OMX))
    {
        HI_ERR_VENC("HI_KFREE failed to free FrameQueue_OMX, size = %d\n", sizeof(queue_info_s));
        VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
        return HI_FAILURE;
    }

    if( VENC_DRV_MngQueueDeinit(pEncPara->MsgQueue_OMX))
    {
        HI_ERR_VENC("HI_KFREE failed to free MsgQueue_OMX, size = %d\n", sizeof(queue_info_s));
        VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
        return HI_FAILURE;
    }

    if(NULL != pEncPara->pstCfg_EncPara)
    {
        kfree((HI_VOID *)pEncPara->pstCfg_EncPara);
        pEncPara->pstCfg_EncPara = NULL;
    }

	if(pEncPara == (VeduEfl_EncPara_S *)VeduIpCtx.CurrHandle)
	{
		VeduIpCtx.CurrHandle = (HI_HANDLE)NULL;
	}

    if(NULL != pEncPara)
    {
        kfree((HI_VOID *)pEncPara);
        pEncPara = NULL;
    }

	VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
    HI_INFO_VENC("exit %s()\n", __func__);
	return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflRequestIframe( HI_HANDLE EncHandle )
{
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    HI_INFO_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);

    pEncPara->bRequestIFrame = HI_TRUE;
    pEncPara->bFirstNal2Send = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflRcGetAttr( HI_HANDLE EncHandle, VeduEfl_RcAttr_S *pRcAttr )
{
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    pRcAttr->Gop        = pEncPara->Gop;
    pRcAttr->BitRate    = pEncPara->iBitRate;
    pRcAttr->InFrmRate  = pEncPara->iFrameRate;
    pRcAttr->SkipFrameEn= pEncPara->bFrameSkip;
    pRcAttr->MinQp      = pEncPara->pstCfg_EncPara->min_qp;
    pRcAttr->MaxQp      = pEncPara->pstCfg_EncPara->max_qp;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflRcSetAttr( HI_HANDLE EncHandle, VeduEfl_RcAttr_S *pRcAttr )
{
    HI_S32 i        = 0;
    HI_S32 lGopBits = 0;
    HI_S32 iKeyInterval = pRcAttr->Gop;
    HI_S32 iIFrameBit   = 0;
    HI_S32 iPFrameBit   = 0;
    HI_S32 iIPRatio     = 0;
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

	if (pRcAttr->InFrmRate > MAX_FRAME_RATE)//输出帧率暂不支持 ljh 2015-0716
	{
		HI_ERR_VENC("Invaild params. pRcAttr->InFrmRate:%d pRcAttr->OutFrmRate:%d \n",pRcAttr->InFrmRate,pRcAttr->OutFrmRate);
        return HI_FAILURE;
    }

    if((pEncPara->vcpi_protocol <= (HI_U32)VEDU_H264) && (pRcAttr->MaxQp > 51 || pRcAttr->MaxQp < pRcAttr->MinQp))
    {
		HI_ERR_VENC("Invaild params. pEncPara->vcpi_protocol:%d, pRcAttr->MaxQp:%d, pRcAttr->MinQp:%d\n",pEncPara->vcpi_protocol,pRcAttr->MaxQp,pRcAttr->MinQp);
        return HI_FAILURE;
    }

	pEncPara->bReEncode     = 0;
    pEncPara->iFrameRate    = pRcAttr->InFrmRate;
    pEncPara->iBitRate      = pRcAttr->BitRate;
    pEncPara->pstCfg_EncPara->max_qp = pRcAttr->MaxQp;
    pEncPara->pstCfg_EncPara->min_qp = pRcAttr->MinQp;
//    pEncPara->iKeyInterval  = pRcAttr->Gop;
	pEncPara->Gop        = pRcAttr->Gop;
    pEncPara->bFrameSkip = pRcAttr->SkipFrameEn;

    pEncPara->iBitsPerFrame = pEncPara->iBitRate/(pEncPara->iFrameRate);
    pEncPara->iQpDelta      = 3;
    pEncPara->iMaxIBits     = pEncPara->iBitsPerFrame*20;
    pEncPara->iMaxPBits     = pEncPara->iBitsPerFrame*10;
    pEncPara->iIpQpDelta    = 0;

    if (iKeyInterval <= 20)
    {
        iIPRatio = 3;
    }
    else if (iKeyInterval <= 40)
    {
        iIPRatio = iKeyInterval*15/100;
    }
    else
    {
        iIPRatio = 6;
    }

    pEncPara->iCounter = 0;
    lGopBits = (HI_S64)(pEncPara->iBitRate)*(HI_S64)iKeyInterval/((HI_S64)(pEncPara->iFrameRate));

    iIFrameBit = (HI_S32)(lGopBits*iIPRatio/(iKeyInterval-1+iIPRatio));
    iPFrameBit = (HI_S32)(lGopBits/(iKeyInterval-1+iIPRatio));
    pEncPara->iIBitsPerFrame = iIFrameBit;
    pEncPara->iPBitsPerFrame = iPFrameBit;

    iPFrameBit = pEncPara->iBitRate/pEncPara->iFrameRate;

    for (i = MAX_FRAME_RATE - 1; i >= 0; i--)
    {
        pEncPara->iFrameBitsQueue[i] = iPFrameBit;
    }

    /* 设置buffer的满度 */
    pEncPara->iVbvBufferSize = pEncPara->iBitRate >> 1;
    pEncPara->iVbvBuffFillInit = pEncPara->iVbvBufferSize * 7 / 10;
    pEncPara->iVbvBuffFillFinal = pEncPara->iVbvBuffFillInit;

    return HI_SUCCESS;
}

static HI_S32 GetInstBitsNew(VeduEfl_EncPara_S *pEncPara)
{
    HI_S32 i          = 0;
    HI_S32 iTotalBits = 0;

    for (i = 0; i < pEncPara->iFrameRate; i++)
    {
        iTotalBits += pEncPara->iFrameBitsQueue[i];
    }

    return iTotalBits;
}

HI_S32 VENC_DRV_EflRcFrmRateCtrl( HI_HANDLE EncHandle, HI_U32 TR )
{
    VeduEfl_EncPara_S *pEncPara = (VeduEfl_EncPara_S *)EncHandle;
    HI_S32 iTargetBitRate       = pEncPara->iBitRate;
    HI_S32 iCurInstBits  = GetInstBitsNew(pEncPara);
    HI_S32 iLastInstBits = pEncPara->iInstBits;
    HI_S32 bFrameSkip    = 0;

	HI_DBG_VENC("RCinfo:pEncPara->RcStart:%d pEncPara->InterFrmCnt:%d pEncPara->Gop:%d\n",pEncPara->RcStart,pEncPara->InterFrmCnt,pEncPara->Gop);

	if(HI_TRUE == pEncPara->bRequestIFrame)//add by ljh免去加锁的I帧请求
	{
		pEncPara->InterFrmCnt    = pEncPara->Gop  - 1;
		pEncPara->bAddHeader     = HI_TRUE;
		pEncPara->bRequestIFrame = HI_FALSE;
	}

    if( pEncPara->RcStart )
    {
        pEncPara->IntraPic = 1;
    }
    else
    {
        /* intra or inter based gop */
        //if( pEncPara->InterFrmCnt == pEncPara->iKeyInterval - 1 )
        if( pEncPara->InterFrmCnt >= pEncPara->Gop  - 1 )//modify by ljh原始代码也是大于等于
        {
            pEncPara->IntraPic = 1;
        }
        else
        {
            pEncPara->IntraPic = 0;
        }
    }

    //fixed QP not skip
    if (pEncPara->pstCfg_EncPara->min_qp == pEncPara->pstCfg_EncPara->max_qp || pEncPara->bFrameSkip == 0)
    {
        return 0;
    }

    if (4*iCurInstBits > 5*iTargetBitRate && 4*(iCurInstBits - iLastInstBits) > iTargetBitRate)
    {
        if (4*iCurInstBits > 5*iTargetBitRate)
        {
            pEncPara->iFrameBitsQueue[pEncPara->iCounter] = 0;
            pEncPara->iCounter++;
            if (pEncPara->iCounter == pEncPara->iFrameRate)
            {
                pEncPara->iCounter = 0;
            }
            pEncPara->iVbvBuffFillFinal += pEncPara->iBitsPerFrame;
            bFrameSkip = 1;
        }
    }
    else if (20*iCurInstBits > 23*iTargetBitRate && 5*(iCurInstBits - iLastInstBits) < iTargetBitRate)
    {
        if (20*iCurInstBits > 23*iTargetBitRate)
        {
            pEncPara->iFrameBitsQueue[pEncPara->iCounter] = 0;
            pEncPara->iCounter++;
            if (pEncPara->iCounter == pEncPara->iFrameRate)
            {
                pEncPara->iCounter = 0;
            }
            pEncPara->iVbvBuffFillFinal += pEncPara->iBitsPerFrame;
            bFrameSkip = 1;
        }
    }

    HI_INFO_VENC("RCinfo:iCurInstBits:%d iTargetBitRate:%d iLastInstBits:%d\n",iCurInstBits,iTargetBitRate,iLastInstBits);

    return bFrameSkip;
}

static const HI_S32 TabLnx[64] =
{
    0, -1216, -972, -830, -729, -651, -587, -533,
    -486,  -445, -408, -374, -344, -316, -290, -265,
    -243,  -221, -201, -182, -164, -147, -131, -115,
    -100,   -86,  -72,  -59,  -46,  -34,  -22,  -11,
    0,    10,   21,   31,   41,   50,   60,   69,
    78,    86,   95,  103,  111,  119,  127,  134,
    142,   149,  156,  163,  170,  177,  183,  190,
    196,   202,  208,  214,  220,  226,  232,  237,
};

static const unsigned char QpTable[96] =
{
    15, 15, 15, 15,    15, 16, 18, 20,    21, 22, 23, 24,    25, 25, 26, 27,
    28, 28, 29, 29,    30, 30, 30, 31,    31, 32, 32, 33,    33, 33, 34, 34,
    34, 34, 35, 35,    35, 36, 36, 36,    36, 36, 37, 37,    37, 37, 38, 38,
    38, 38, 38, 39,    39, 39, 39, 39,    39, 40, 40, 40,    40, 41, 41, 41,
    41, 41, 41, 41,    42, 42, 42, 42,    42, 42, 42, 42,    43, 43, 43, 43,
    43, 43, 43, 43,    44, 44, 44, 44,    44, 44, 44, 44,    45, 45, 45, 45,
};

// 计算初始StartQP;
// s32Ptbits 以bit为单位
static void InitFirstIStartQP(VeduEfl_EncPara_S *pEncPara, HI_S32 iTargetBits, HI_S32 iMacroBlockNum, HI_S32 iIPQpDelta)
{
    HI_S32 i = 0;
    HI_S32 aiInitSizeLv[12]   = {88,200,700,1200,2000,4000,8000,16000,20000,20000,20000,20000};
    HI_S32 aiSizeCostRate[12] = {18, 17, 15,  14,  13,  18,  10,    8,   10,   10,   10,   10};

    HI_S32 iCost2    = 0;
    HI_S32 iStartQP2 = 0;
    HI_S32 iCost     = 0;
    HI_S32 iCostInit = 2100;
    HI_S32 iBetaI    = -300;

    for (i = 0; i < 11; i++)
    {
        if(iMacroBlockNum < aiInitSizeLv[i])
        {
            break;
        }
    }

    iCost = aiSizeCostRate[i] * iCostInit * iMacroBlockNum / 10 + iBetaI;

    iCost2 = iCost / iTargetBits;
    iCost2 = (iCost2 < 4 )?   4: iCost2;
    iCost2 = (iCost2 > 95)?  95: iCost2;
    iStartQP2 = QpTable[iCost2] * 64;

    pEncPara->iStartQP  = iStartQP2;
    pEncPara->iStartQP += iIPQpDelta * 64;
}

HI_S32 VENC_DRV_EflRcOpenOneFrm( HI_HANDLE EncHandle )
{
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    HI_S32 bIFrameFlag = pEncPara->IntraPic;
    HI_S32 iTargetBits;
    HI_S32 iStartQp;
    HI_S32 iDelta0, iDelta1, iDelta11, iDelta12, iDelta2, iDelta3, iDelta4, iDelta5;
    HI_S32 iMaxQP = pEncPara->pstCfg_EncPara->max_qp;
    HI_S32 iMinQP = pEncPara->pstCfg_EncPara->min_qp;
    HI_S32 iIPQpDelta = 3;
    HI_S32 iTotalBits = pEncPara->iTotalBits;
    HI_S32 iInstBits = GetInstBitsNew(pEncPara);
    HI_S32 iTarBitRate  = pEncPara->iBitRate;
    HI_S32 iDeltaBitRate = iTarBitRate / 16;
    HI_S32 iDeltaQp = 0;
    HI_S32 iLastIFrameBits = pEncPara->iLastIFrameBits;
    HI_S32 iCurInstBits, iLastInstBits;
    HI_S32 iIRatio;
    HI_S64 lTotalIBits, lTotalPBits;
    HI_S32 iInstIPRatio, i;

    if(pEncPara->pstCfg_EncPara->min_qp == pEncPara->pstCfg_EncPara->max_qp)
    {
        pEncPara->iFrameQp = pEncPara->pstCfg_EncPara->min_qp;
        pEncPara->RcStart = 0;
        return HI_SUCCESS;
    }

    if (0 == pEncPara->bLastIFrameFlag)
    {
        iIRatio = pEncPara->iI8x8Num*100/pEncPara->iFrameCuNum;
        pEncPara->aiIRatio[pEncPara->iIRatioCounter] = iIRatio;
        pEncPara->iIRatioCounter++;
        if (pEncPara->iIRatioCounter == I_RATIO_NUM)
        {
            pEncPara->iIRatioCounter = 0;
        }
        pEncPara->iIRatioDelta += iIRatio - pEncPara->aiIRatio[pEncPara->iIRatioCounter];
    }

    //序列第一个I帧初始化qp
    if (pEncPara->RcStart == 1)
    {
        pEncPara->RcStart = 0;

        if (1 == bIFrameFlag)
        {
            iTargetBits = pEncPara->iIBitsPerFrame;
        }
        else
        {
            iTargetBits = pEncPara->iPBitsPerFrame;
        }

        InitFirstIStartQP(pEncPara, pEncPara->iBitsPerFrame*5, pEncPara->iPicMbs, iIPQpDelta);

        iStartQp = (pEncPara->iStartQP>>6) - iIPQpDelta;
        iStartQp = CLIP3(iMinQP, iMaxQP, iStartQp);
        pEncPara->iFrameQp = iStartQp;
        pEncPara->iTargetBits = iTargetBits;

        if (pEncPara->vcpi_protocol == VEDU_H265)
        {
            pEncPara->iAveLcuBits = iTargetBits*16/pEncPara->iPicMbs;
        }
        else
        {
            pEncPara->iAveLcuBits = iTargetBits/pEncPara->iPicMbs;
        }

        if (1 == bIFrameFlag)
        {
            pEncPara->iLastIFrameQp = iStartQp;
        }

        return HI_SUCCESS;
    }

    //calc frame target bits
    if (pEncPara->Gop == 0)
    {
        if (1 == bIFrameFlag)
        {
            iTargetBits = pEncPara->iIBitsPerFrame;

            if (iInstBits > iTarBitRate)
            {
                iTargetBits = iTargetBits - (iInstBits - iTarBitRate)/pEncPara->iFrameRate;
            }
        }
        else
        {
            iTargetBits = pEncPara->iPBitsPerFrame;

            if (pEncPara->iIRatioDelta > LARGE_MOVE_DET_THRESH)
            {
                iTargetBits = iTargetBits*6/5;
            }
            else if (pEncPara->iIRatioDelta > SMALL_MOVE_DET_THRESH)
            {
                iTargetBits = iTargetBits*8/7;
            }
            else if (pEncPara->iStaticFrame > 0)
            {
                iTargetBits = iTargetBits*8/7;
                pEncPara->iStaticFrame--;
            }

            if (iInstBits*7 > iTarBitRate*8)
            {
                iTargetBits = iTargetBits - (iInstBits - iTarBitRate)/pEncPara->iFrameRate;
            }
            else
            {
                if (pEncPara->iIRatioDelta > LARGE_MOVE_DET_THRESH)
                {
                    iTargetBits = iTargetBits - (iInstBits - iTarBitRate*6/5)/pEncPara->iFrameRate;
                }
                else if (pEncPara->iIRatioDelta > SMALL_MOVE_DET_THRESH)
                {
                    iTargetBits = iTargetBits - (iInstBits - iTarBitRate*8/7)/pEncPara->iFrameRate;
                }
                else if (pEncPara->iStaticFrame > 0)
                {
                    iTargetBits = iTargetBits - (iInstBits - iTarBitRate*8/7)/pEncPara->iFrameRate;
                }
            }
        }
    }
    else
    {
        if (pEncPara->bLastIFrameFlag == 1)
        {
            pEncPara->aiIntraFrmBits[pEncPara->iIntraPointer] = iTotalBits;
            pEncPara->iIntraPointer++;
            if (pEncPara->iIntraPointer >= RC_MAX_INTRA_LOADSIZE)
                pEncPara->iIntraPointer = 0;
        }
        else
        {
            pEncPara->aiInterFrmBits[pEncPara->iInterPointer] = iTotalBits;
            pEncPara->iInterPointer++;
            if (pEncPara->iInterPointer >= RC_MAX_INTER_LOADSIZE)
                pEncPara->iInterPointer = 0;
        }

        // 计算新的 IPRatio
        for (lTotalIBits = 0, i=0; i<RC_MAX_INTRA_LOADSIZE; i++)
        {
            lTotalIBits += pEncPara->aiIntraFrmBits[i];
        }

        for (lTotalPBits = 0, i=0; i<RC_MAX_INTER_LOADSIZE; i++)
        {
            lTotalPBits += pEncPara->aiInterFrmBits[i];
        }

        lTotalIBits  = lTotalIBits * RC_MAX_INTER_LOADSIZE * 16;
        lTotalPBits  = lTotalPBits * RC_MAX_INTRA_LOADSIZE;
        if (0 == lTotalPBits)
        {
            return HI_FAILURE;
        }
        iInstIPRatio = (HI_S32)(lTotalIBits/lTotalPBits);

        // 计算目标bits数
        if (bIFrameFlag == HI_TRUE)
        {
            HI_S64 lBitsPerGop = (HI_S64)pEncPara->iBitsPerFrame*pEncPara->Gop;
            HI_S32 iIPRatio    = ((pEncPara->Gop - 1) * 16) + iInstIPRatio;

            lBitsPerGop     = lBitsPerGop * iInstIPRatio;
            iTargetBits     = (lBitsPerGop/iIPRatio);

            if (iInstBits > iTarBitRate)
            {
                iTargetBits = iTargetBits - (iInstBits - iTarBitRate)/pEncPara->iFrameRate;
            }
        }
        else
        {
            HI_S64 lBitsPerGop = (HI_S64)pEncPara->iBitsPerFrame*pEncPara->Gop;
            HI_S32 iIPRatio = ((pEncPara->Gop - 1) * 16) + iInstIPRatio;

            lBitsPerGop = lBitsPerGop * 16;
            iTargetBits     = (lBitsPerGop/iIPRatio);

            if (pEncPara->iIRatioDelta > LARGE_MOVE_DET_THRESH)
            {
                iTargetBits = iTargetBits*6/5;
            }
            else if (pEncPara->iIRatioDelta > SMALL_MOVE_DET_THRESH)
            {
                iTargetBits = iTargetBits*8/7;
            }
            else if (pEncPara->iStaticFrame > 0)
            {
                iTargetBits = iTargetBits*8/7;
                pEncPara->iStaticFrame--;
            }

            if (iInstBits*7 > iTarBitRate*8)
            {
                iTargetBits = iTargetBits - (iInstBits - iTarBitRate)/pEncPara->iFrameRate;
            }
            else
            {
                if (pEncPara->iIRatioDelta > LARGE_MOVE_DET_THRESH)
                {
                    iTargetBits = iTargetBits - (iInstBits - iTarBitRate*6/5)/pEncPara->iFrameRate;
                }
                else if (pEncPara->iIRatioDelta > SMALL_MOVE_DET_THRESH)
                {
                    iTargetBits = iTargetBits - (iInstBits - iTarBitRate*8/7)/pEncPara->iFrameRate;
                }
                else if (pEncPara->iStaticFrame > 0)
                {
                    iTargetBits = iTargetBits - (iInstBits - iTarBitRate*8/7)/pEncPara->iFrameRate;
                }
            }
        }
    }


    if (iTargetBits > pEncPara->iFrameBitsQueue[pEncPara->iCounter] && iInstBits > iTarBitRate)
    {
        iTargetBits -= (iTargetBits - pEncPara->iFrameBitsQueue[pEncPara->iCounter])/pEncPara->iFrameRate;
    }

    //iTargetBits = MIN(iTargetBits, pEncPara->iBitsPerFrame * pEncPara->iPeakRatio);

    if (iTargetBits < (pEncPara->iBitsPerFrame/3))
    {
        iTargetBits = pEncPara->iBitsPerFrame/3;
    }

    /*这里是有溢出的风险*/
    if (iTotalBits >= pEncPara->iTargetBits)
    {
        // 超出1倍QP调整1
        iDelta0 = (iTotalBits - pEncPara->iTargetBits) * 64 / pEncPara->iTargetBits;
    }
    else
    {
        iDelta0 = (iTotalBits - pEncPara->iTargetBits) * 40 / pEncPara->iTargetBits; //s32TotalBits;
    }

    iCurInstBits  = iInstBits;
    iLastInstBits = pEncPara->iInstBits;

    iDelta11 = iLastInstBits * 32 / iTarBitRate;
    iDelta12 = iCurInstBits  * 32 / iTarBitRate;
    iDelta11 = CLIP3(0,63, iDelta11);
    iDelta12 = CLIP3(0,63, iDelta12);
    iDelta1  = TabLnx[iDelta12] - TabLnx[iDelta11];

    if (iCurInstBits > iLastInstBits &&
        iLastInstBits > (iTarBitRate - iDeltaBitRate))
    {
        // QP 上调的力度比下调大1倍
        iDelta1 = iDelta1 * 6;
    }
    else if (iCurInstBits < iLastInstBits &&
        iLastInstBits < (iTarBitRate + iDeltaBitRate))
    {
        iDelta1 = iDelta1 * 4;
    }
    else
    {
        iDelta1 = 0;
    }

    // 超出 1/8 QP调整1
    // s32Delta2 = (u32InstBits - s32TarBitRate) * 96 / s32TarBitRate;
    iDelta2 = (iInstBits - iTarBitRate) * 96 / iTarBitRate;

    /*VbvBuf对起始Qp的作用*/
    // s32Delta2 = s32Delta22;
    // s32Delta3 = (s32BufferCur - pRcRunTimeCtx->s32Waterline) * 32 / pRcRunTimeCtx->s32Waterline;

    iDelta3 = (pEncPara->iVbvBuffFillInit - pEncPara->iVbvBuffFillFinal) * 128 / pEncPara->iVbvBufferSize;

    iDelta5 = 0;
    if (1 == bIFrameFlag)
    {
        if ( iTotalBits > pEncPara->iMaxIBits ||
            (iTotalBits <= pEncPara->iMaxIBits && pEncPara->iIpQpDelta > 0))
        {
            iDelta5 = (iTotalBits - pEncPara->iMaxIBits)  * 64 / pEncPara->iBitsPerFrame;
            iDelta5 = CLIP3(-64*4, 64*4,  iDelta5);

            pEncPara->iIpQpDelta += iDelta5;
        }
    }
    else
    {
        if ( iTotalBits > pEncPara->iMaxPBits ||
            (iTotalBits <= pEncPara->iMaxPBits && pEncPara->iIpQpDelta > 0))
        {
            iDelta5 = (iTotalBits - pEncPara->iMaxPBits)  * 64 / pEncPara->iBitsPerFrame;
            iDelta5 = CLIP3(-64*4, 64*4,  iDelta5);

            pEncPara->iIpQpDelta += iDelta5;
            pEncPara->iIpQpDelta = MAX(0, pEncPara->iIpQpDelta);
        }
    }

    iDelta4 = pEncPara->iIpQpDelta;

    iDelta0 = CLIP3(-128,256, iDelta0);
    iDelta1 = CLIP3(-128,256, iDelta1);
    iDelta2 = CLIP3(-32, 32,  iDelta2);
    iDelta3 = CLIP3(-32, 32,  iDelta3);

    pEncPara->iStartQP += iDelta0 + iDelta1 + iDelta2 + iDelta3 + iDelta4;
    pEncPara->iTargetBits  = iTargetBits;
    pEncPara->iInstBits= iInstBits;
    pEncPara->iStartQP = CLIP3(iMinQP * 64, iMaxQP * 64, pEncPara->iStartQP);

    pEncPara->iFrameQp = pEncPara->iStartQP>>6;

	HI_INFO_VENC("iDelta0:%d iDelta1:%d iDelta2:%d iDelta3:%d iDelta4:%d iDelta5:%d iDelta11:%d iDelta12:%d\n",
		iDelta0,iDelta1,iDelta2,iDelta3,iDelta4,iDelta5,iDelta11,iDelta12);


    if (pEncPara->Gop == 0)
    {
        if (1 == bIFrameFlag)
        {
            iTargetBits = pEncPara->iIBitsPerFrame - (GetInstBitsNew(pEncPara) - pEncPara->iBitRate)/pEncPara->iFrameRate;
            //计算I帧QP
            if (iLastIFrameBits > iTargetBits)
            {

                while(iLastIFrameBits > iTargetBits)
                {
                    iLastIFrameBits = (iLastIFrameBits*114) >> 7; //*1/power(2,1/6)
                    iDeltaQp++;
                }
            }
            else
            {
                while(iLastIFrameBits < iTargetBits)
                {
                    iLastIFrameBits = (iLastIFrameBits*144) >> 7; //*power(2,1/6)
                    iDeltaQp--;
                }
            }

            pEncPara->iFrameQp = CLIP3(iMinQP, iMaxQP, (pEncPara->iLastIFrameQp + iDeltaQp));

            pEncPara->iLastIFrameQp = pEncPara->iFrameQp;
        }
    }
    else
    {
        if (1 == bIFrameFlag)
        {
            pEncPara->iFrameQp = ((pEncPara->iStartQP>>6) + pEncPara->iLastIFrameQp) >> 1;
            pEncPara->iFrameQp -= 2;
            pEncPara->iLastIFrameQp = pEncPara->iFrameQp;

        }
    }

    if (pEncPara->iIRatioDelta > SMALL_MOVE_DET_THRESH && 0 == bIFrameFlag)
    {
        pEncPara->iStaticFrame = STATIC_FRAME_NUM;
    }

    if (pEncPara->vcpi_protocol == VEDU_H265)
    {
        pEncPara->iAveLcuBits = iTargetBits*16/pEncPara->iPicMbs;
    }
    else
    {
        pEncPara->iAveLcuBits = iTargetBits/pEncPara->iPicMbs;
    }

    pEncPara->bLastIFrameFlag = bIFrameFlag;

    HI_INFO_VENC("rcinfo: pEncPara->iAveLcuBits:%d iFrameQp:%d \n",pEncPara->iAveLcuBits,pEncPara->iFrameQp);
    return HI_SUCCESS;
}

/* 更新vbv buffer 及预测系数*/
static void UpdateVbvNew( VeduEfl_EncPara_S *pEncPara, HI_S32 iFrameBits )
{
    /* 当前vbv存放的bits */
    pEncPara->iVbvBuffFillFinal += pEncPara->iBitsPerFrame - iFrameBits;

    pEncPara->iVbvBuffFillFinal = MIN( pEncPara->iVbvBuffFillFinal, pEncPara->iVbvBufferSize );
}

HI_S32 VENC_DRV_EflRcReEncodeFlag( HI_HANDLE EncHandle )
{
    HI_S32 iDeltaQp      = 0;
    HI_S32 iTargetBits   = 0;
    HI_S32 iReEncodeTime = 0;
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    if (pEncPara->bReEncode == 1)
	{
	    pEncPara->bReEncode = 0;

		return 0;
	}

    if (1 == pEncPara->bLastIFrameFlag)
    {
        iReEncodeTime = 2;
    }
    else
    {
        iReEncodeTime = 5;//5
    }

    if (1 == pEncPara->bLastIFrameFlag)
    {
        iTargetBits = pEncPara->iTargetBits;
    }
    else
    {
        iTargetBits = pEncPara->iTargetBits * 3;
    }

    if (pEncPara->PicBits > pEncPara->iTargetBits * iReEncodeTime && pEncPara->iFrameQp != pEncPara->pstCfg_EncPara->max_qp && pEncPara->bReEncode == 0)
    {
        pEncPara->bReEncode = 1;
    }
    else
    {
        pEncPara->bReEncode = 0;
    }

    if (pEncPara->bReEncode)
    {
        while(pEncPara->PicBits > iTargetBits)
        {
            iTargetBits = (iTargetBits*144) >> 7;
            iDeltaQp++;
        }

        pEncPara->iFrameQp = MIN(pEncPara->iFrameQp + iDeltaQp, (HI_S32)pEncPara->pstCfg_EncPara->max_qp);
        pEncPara->iStartQP = MIN(pEncPara->iStartQP + iDeltaQp*64, (HI_S32)pEncPara->pstCfg_EncPara->max_qp*64);
        pEncPara->iLastIFrameQp = pEncPara->iFrameQp;
        pEncPara->bLastIFrameFlag = 1;
        //帧估计bits
        iTargetBits = pEncPara->iTargetBits << 1;
        pEncPara->iTargetBits  = iTargetBits;
        //计算Lcu估计bits
        if (pEncPara->vcpi_protocol == VEDU_H265)
        {
            pEncPara->iAveLcuBits = iTargetBits*16/pEncPara->iPicMbs;
        }
        else
        {
            pEncPara->iAveLcuBits = iTargetBits/pEncPara->iPicMbs;
        }
    }

    return pEncPara->bReEncode;
}

HI_S32 VENC_DRV_EflRcCloseOneFrm( HI_HANDLE EncHandle )
{
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;
#ifdef RE_ENCODE_EN
    if (1 == VENC_DRV_EflRcReEncodeFlag(EncHandle))
    {
       return HI_SUCCESS;
    }
#endif
    pEncPara->iTotalBits = pEncPara->PicBits;
    pEncPara->iI8x8Num = pEncPara->I8x8Num;

    if (1 == pEncPara->bLastIFrameFlag)
    {
        pEncPara->iLastIFrameBits = pEncPara->PicBits;
    }

    UpdateVbvNew( pEncPara, pEncPara->PicBits );

    pEncPara->iFrameBitsQueue[pEncPara->iCounter] = pEncPara->PicBits;
    pEncPara->iCounter++;
    if (pEncPara->iCounter == pEncPara->iFrameRate)
    {
        pEncPara->iCounter = 0;
    }

    if( pEncPara->IntraPic )
    {
        pEncPara->InterFrmCnt = 0;
    }
    else
    {
        pEncPara->InterFrmCnt++;
    }
    pEncPara->stRc.FrmNumSeq++;
    return HI_SUCCESS;
}


/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflRcSkipOneFrameVenc( HI_HANDLE EncHandle, HI_U32 tr )
{
    return VENC_DRV_EflRcFrmRateCtrl( EncHandle, tr );
}


HI_S32 VENC_DRV_EflRcAttrInit( HI_HANDLE EncHandle, VeduEfl_RcAttr_S *pRcAttr )
{
    HI_S32 i            = 0;
    HI_S64 lGopBits     = 0;
    HI_S32 iKeyInterval = pRcAttr->Gop;
    HI_S32 iIFrameBit   = 0;
    HI_S32 iPFrameBit   = 0;
    HI_S32 iIPRatio     = 0;
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    //if ((pRcAttr->InFrmRate > MAX_FRAME_RATE) || (pRcAttr->InFrmRate < pRcAttr->OutFrmRate))
	if (pRcAttr->InFrmRate > MAX_FRAME_RATE)//输出帧率暂不支持ljh 2015-0716
	{
        return HI_FAILURE;
    }

    if(pEncPara->vcpi_protocol <= (HI_U32)VEDU_H264  && (pRcAttr->MaxQp > 51 ||  pRcAttr->MaxQp < pRcAttr->MinQp))
    {
        return HI_FAILURE;
    }

    /*initialize re-start parameter*/
    pEncPara->RcStart    = 1;
	pEncPara->bReEncode  = 0;
    pEncPara->iImgWidth  = pRcAttr->ImgWidth;
    pEncPara->iImgHeight = pRcAttr->ImgHeight;
    pEncPara->iFrameRate = pRcAttr->InFrmRate;
    pEncPara->iBitRate   = pRcAttr->BitRate;
    pEncPara->pstCfg_EncPara->max_qp = pRcAttr->MaxQp;
    pEncPara->pstCfg_EncPara->min_qp = pRcAttr->MinQp;

    if (pEncPara->pstCfg_EncPara->min_qp < RC_QP_MIN)
    {
        pEncPara->pstCfg_EncPara->min_qp = RC_QP_MIN;
    }

    if (pEncPara->pstCfg_EncPara->max_qp > RC_QP_MAX)
    {
        pEncPara->pstCfg_EncPara->max_qp = RC_QP_MAX;
    }

    if (pEncPara->pstCfg_EncPara->max_qp < pEncPara->pstCfg_EncPara->min_qp)
    {
        pEncPara->pstCfg_EncPara->max_qp = pEncPara->pstCfg_EncPara->min_qp;
    }

	pEncPara->Gop             = pRcAttr->Gop;
    pEncPara->bFrameSkip      = pRcAttr->SkipFrameEn;
    pEncPara->iPicMbs         = ((pRcAttr->ImgWidth + 16 - 1) >> 4) * ((pRcAttr->ImgHeight + 16 - 1) >> 4);
    pEncPara->iFrameCuNum     = ((pEncPara->iImgWidth + 7) >> 3) * ((pEncPara->iImgHeight + 7) >> 3); //计算一帧Cu数，8x8
    pEncPara->bLastIFrameFlag = 1;
    pEncPara->bInitFlag       = 0;

    pEncPara->iBitsPerFrame = pEncPara->iBitRate/(pEncPara->iFrameRate);
    pEncPara->iQpDelta      = 3;
    pEncPara->iMaxIBits     = pEncPara->iBitsPerFrame*20;
    pEncPara->iMaxPBits     = pEncPara->iBitsPerFrame*10;
    pEncPara->iIpQpDelta    = 0;

    iIPRatio           = 6;
	iKeyInterval       = iKeyInterval ? iKeyInterval : 1000;//add by huangliang 0715
    pEncPara->iCounter = 0;

    lGopBits   = ((HI_S64)pEncPara->iBitRate)*iKeyInterval/(pEncPara->iFrameRate);
    iIFrameBit = (HI_S32)(lGopBits*iIPRatio/(iKeyInterval-1+iIPRatio));
    iPFrameBit = (HI_S32)(lGopBits/(iKeyInterval-1+iIPRatio));

    pEncPara->iIBitsPerFrame = iIFrameBit;
    pEncPara->iPBitsPerFrame = iPFrameBit;
    for (i = pEncPara->iFrameRate - 1; i >= 0; i--)
    {
        if (i%iKeyInterval == 0)
        {
            pEncPara->iFrameBitsQueue[i] = iIFrameBit;
        }
        else
        {
            pEncPara->iFrameBitsQueue[i] = iPFrameBit;
        }
    }

    for (i = 0; i < I_RATIO_NUM; i++)
    {
        pEncPara->aiIRatio[i] = 0;
    }

    pEncPara->iIntraPointer = 0;
    pEncPara->iInterPointer = 0;
    for (i = 0; i < RC_MAX_INTRA_LOADSIZE; i++)
    {
        pEncPara->aiIntraFrmBits[i] = iIFrameBit;
    }

    for (i = 0; i < RC_MAX_INTER_LOADSIZE; i++)
    {
        pEncPara->aiInterFrmBits[i] = iPFrameBit;
    }

    pEncPara->iIRatioDelta = 0;
    pEncPara->iStaticFrame = 0;
    pEncPara->iInstBits    = pEncPara->iBitRate;

    /* 设置buffer的满度 */
    pEncPara->iVbvBufferSize    = pEncPara->iBitRate >> 1;
    pEncPara->iVbvBuffFillInit  = pEncPara->iVbvBufferSize * 7 / 10;
    pEncPara->iVbvBuffFillFinal = pEncPara->iVbvBuffFillInit;

    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflSetResolution( HI_HANDLE EncHandle, HI_U32 FrameWidth, HI_U32 FrameHeight )
{
    VeduEfl_RcAttr_S RcAttr;
    HI_U32 WidthInMb  = (FrameWidth + 15) >> 4;
    HI_U32 HeightInMb = (FrameHeight + 15) >> 4;
    HI_U32 LumaSize   = (WidthInMb * HeightInMb) << 8;

    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;
    memset(&RcAttr, 0, sizeof(RcAttr));

    /* check config */
    if (LumaSize > pEncPara->RcnCAddr[0] - pEncPara->RcnYAddr[0])
    {
        HI_ERR_VENC("%s, The memory size of Rcn is not enougth! LumaSize:%d Rcn:%d\n", __func__, LumaSize,(pEncPara->RcnCAddr[0] - pEncPara->RcnYAddr[0]));
		return HI_FAILURE;
    }

    VENC_DRV_EflRcGetAttr( EncHandle, &RcAttr );
    if (HI_SUCCESS != VENC_DRV_EflRcAttrInit( EncHandle, &RcAttr ))
    {
        HI_ERR_VENC("%s, config venc Rate Control Attribute err!.\n", __func__);
        return HI_FAILURE;
    }

    pEncPara->NumRefIndex        = 0;
    pEncPara->vcpi_imgwidth_pix  = FrameWidth;
    pEncPara->vcpi_imgheight_pix = FrameHeight;

	VENC_DRV_EflFlushStrmHeader( pEncPara );
    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflStartVenc( HI_HANDLE EncHandle )
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    VEDU_LOCK_FLAG flag;
    VeduEfl_EncPara_S *pEncPara = NULL;
	HI_INFO_VENC("enter %s, EncHandle:0x%llx\n", __func__, EncHandle);

    if((HI_HANDLE)NULL == EncHandle)
    {
    	HI_ERR_VENC("%s, EncHandle can not be null\n", __func__);
    	return HI_FAILURE;
    }

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag );
    for (i = 0; i < MAX_VEDU_CHN; i++)
    {
        if (VeduChnCtx[i].EncHandle == (HI_HANDLE)NULL)
        {
            HI_INFO_VENC("%s, VeduChnCtx[%d].EncHandle:0x%llx\n", __func__, i, EncHandle);
            VeduChnCtx[i].EncHandle = EncHandle;
            break;
        }
    }

    if (i >= VENC_MAX_CHN_NUM)
	{
	    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

	pEncPara = (VeduEfl_EncPara_S*)EncHandle;
    for (j = 0; j < MAX_VEDU_CHN; j++)
    {
        if( INVAILD_CHN_FLAG ==PriorityTab[0][j])
        {
           PriorityTab[0][j] = i;
           PriorityTab[1][j] = pEncPara->Priority;
           VENC_DRV_EflSortPriority();

           HI_INFO_VENC("PriorityTab[0][%d]:%d\n",j,i);
           break;
        }
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

	pEncPara->bStartEnc         = HI_TRUE;
	pEncPara->bFirstNal2Send    = HI_TRUE;
	pEncPara->vlcst_para_set_en = 1;
#ifdef OUTPUT_LOWDELAY_EN
	pEncPara->iLastEncodedStreamCnt = 0;
#endif
	HI_INFO_VENC("exit %s, EncHandle:0x%llx\n", __func__, EncHandle);
	return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflStopVenc( HI_HANDLE EncHandle )
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    VEDU_LOCK_FLAG flag;
	VeduEfl_EncPara_S *pEncPara = NULL;
    HI_INFO_VENC("enter %s()\n", __func__);

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag );

    for (i = 0; i < MAX_VEDU_CHN; i++)
    {
        if (VeduChnCtx[i].EncHandle == EncHandle)
        {
            VeduChnCtx[i].EncHandle = (HI_HANDLE)NULL;
            break;
        }
    }

    for (j = 0;(i < MAX_VEDU_CHN)&&(j < MAX_VEDU_CHN); j++)
    {
        if( i ==PriorityTab[0][j])
        {
           PriorityTab[0][j] = INVAILD_CHN_FLAG;
           PriorityTab[1][j] = 0;
           VENC_DRV_EflSortPriority();
           break;
        }
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if (i == MAX_VEDU_CHN)
    {
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    pEncPara = (VeduEfl_EncPara_S*)EncHandle;
	pEncPara->bStartEnc = HI_FALSE;

    /* wait finish last frame */
#ifdef MD5_WC_EN
    while (pEncPara->WaitingIsr ||(!pEncPara->CalcMd5Flag))
#else
    while (pEncPara->WaitingIsr)
#endif
    {
    	HI_DBG_VENC("WaitingIsr = 1\n");
        msleep(1);
    }

	HI_DBG_VENC("%s, WaitingIsr = 0\n", __func__);

	/* rfresh the queue of the Img */
    VENC_DRV_EflFlushPort_OMX(EncHandle,ALL_PORT,HI_TRUE);
    VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_STOP_DONE, HI_SUCCESS, NULL);
    pEncPara->stStat.MsgQueueNum++;

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}


static HI_S32 VENC_DRV_EflCheckImgCfg_OMX(const venc_user_buf *pstPreImage,HI_U32 yuvStoreType)
{
    HI_U32 u32PhyAddr_Y = pstPreImage->bufferaddr_Phy + pstPreImage->offset;
    HI_U32 u32PhyAddr_C = u32PhyAddr_Y + pstPreImage->offset_YC;
    HI_U32 u32Stride_Y  = pstPreImage->strideY;
	HI_U32 u32Stride_C  = pstPreImage->strideC;

    HI_DBG_VENC("u32PhyAddr_Y:0x%x\n",u32PhyAddr_Y);
    HI_DBG_VENC("u32PhyAddr_C:0x%x\n",u32PhyAddr_C);
    HI_DBG_VENC("u32Stride_Y:0x%x\n",u32Stride_Y);
    HI_DBG_VENC("u32Stride_C:0x%x\n",u32Stride_C);
    HI_DBG_VENC("VENC_STORE_PLANNAR:0x%x\n",yuvStoreType);
    HI_DBG_VENC("pstPreImage->picWidth:0x%x\n",pstPreImage->picWidth);
    HI_DBG_VENC("pstPreImage->picHeight:0x%x\n",pstPreImage->picHeight);

	if((pstPreImage->picWidth> VEDU_MAX_ENC_WIDTH)||(pstPreImage->picWidth< VEDU_MIN_ENC_WIDTH)||
	(pstPreImage->picHeight> VEDU_MAX_ENC_HEIGHT)||(pstPreImage->picHeight< VEDU_MIN_ENC_HEIGHT))
	{
       HI_ERR_VENC("check YUV params failed,picWidth:%d,picHeight:%d\n",pstPreImage->picWidth,pstPreImage->picHeight);
	   return HI_FAILURE;
	}

    if((!u32PhyAddr_Y) || (u32PhyAddr_Y % 16) || (!u32Stride_Y ) || (u32Stride_Y  % 16))
    {
       HI_ERR_VENC("check YUV params failed,u32PhyAddr_Y:0x%x,u32Stride_Y:%d\n",u32PhyAddr_Y,u32Stride_Y);
	   return HI_FAILURE;
	}

	if (VENC_STORE_PLANNAR == yuvStoreType)
	{
        HI_U32 u32PhyAddr_Cr = u32PhyAddr_C + pstPreImage->offset_YCr;
        HI_U32 u32Stride_Cr  = pstPreImage->strideC;
		if((!u32PhyAddr_C) || (u32PhyAddr_C  %16) || (!u32PhyAddr_Cr) || (u32PhyAddr_Cr %16) ||
 		(!u32Stride_C ) || (u32Stride_C   %16) || (!u32Stride_Cr) || (u32Stride_Cr  %16))
	    {
	       HI_ERR_VENC("check YUV params failed,u32PhyAddr_C:0x%x,u32PhyAddr_Cr:0x%x,u32Stride_C:%d,u32Stride_Cr:%d \n",u32PhyAddr_C,u32PhyAddr_Cr,u32Stride_C,u32Stride_Cr);
		   return HI_FAILURE;
		}
    }
	else if (VENC_STORE_SEMIPLANNAR == yuvStoreType)
    {
		if((!u32PhyAddr_C)  || (u32PhyAddr_C %16) || (!u32Stride_C )  || (u32Stride_C  %16))
		{
		   HI_ERR_VENC("check YUV params failed,u32PhyAddr_C:0x%x,u32Stride_C:%d\n",u32PhyAddr_C,u32Stride_C);
		   return HI_FAILURE;
		}
	}

    return HI_SUCCESS;
}

static HI_S32 VENC_DRV_ConvertYUVType(VeduEfl_EncPara_S *pEncPara)
{
	if (pEncPara->YuvStoreType == VENC_STORE_SEMIPLANNAR)
	{
		if (pEncPara->YuvSampleType == VENC_YUV_420)
		{
			pEncPara->vcpi_str_fmt = 0;
		}
		else
		{
			HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
			return HI_FAILURE;
		}

		if (pEncPara->YuvSelType == VENC_U_V)
		{
			pEncPara->vcpi_package_sel = 0;
		}
		else if (pEncPara->YuvSelType == VENC_V_U)
		{
			pEncPara->vcpi_package_sel = 1;
		}
		else
		{
			HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
			return HI_FAILURE;
		}
	}
	else if (pEncPara->YuvStoreType == VENC_STORE_PLANNAR)
	{
		if (pEncPara->YuvSampleType == VENC_YUV_420)
		{
			pEncPara->vcpi_str_fmt = 3;
		}
		else if (pEncPara->YuvSampleType == VENC_YUV_422)
		{
			pEncPara->vcpi_str_fmt = 4;
		}
		else
		{
			HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
			return HI_FAILURE;
		}

		if (pEncPara->YuvSelType == VENC_U_V)
		{
			pEncPara->vcpi_package_sel = 0;
		}
		else
		{
			HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
			return HI_FAILURE;
		}
	}
	else if (pEncPara->YuvStoreType == VENC_STORE_PACKAGE)
	{
		if (pEncPara->YuvSampleType == VENC_YUV_422)
		{
			pEncPara->vcpi_str_fmt = 6;
		}
		else
		{
			HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
			return HI_FAILURE;
		}

		if (pEncPara->YuvSelType == VENC_PACKAGE_Y0UY1V)
		{
			pEncPara->vcpi_package_sel = 0;
		}
		else if (pEncPara->YuvSelType == VENC_PACKAGE_Y0VY1U)
		{
			pEncPara->vcpi_package_sel = 1;
		}
		else if (pEncPara->YuvSelType == VENC_PACKAGE_UY0VY1)
		{
			pEncPara->vcpi_package_sel = 2;
		}
		else if (pEncPara->YuvSelType == VENC_PACKAGE_VY0UY1)
		{
			pEncPara->vcpi_package_sel = 3;
		}
		else
		{
			HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
			return HI_FAILURE;
		}
	}
	else if (pEncPara->YuvStoreType == VENC_STORE_RGB)
	{
			pEncPara->vcpi_str_fmt = 8;

			if (pEncPara->YuvSelType == VENC_A_R_G_B)
			{
				pEncPara->vcpi_package_sel = 0x0;//0x8;
			}
			else if (pEncPara->YuvSelType == VENC_A_B_G_R)
			{
				pEncPara->vcpi_package_sel = 0x5;//0xd;
			}
			else if (pEncPara->YuvSelType == VENC_R_G_B_A)
			{
				pEncPara->vcpi_package_sel = 0x8;//0x0;
			}
			else if (pEncPara->YuvSelType == VENC_B_G_R_A)
			{
				pEncPara->vcpi_package_sel = 0xd;//0x5;
			}
			else
			{
				HI_ERR_VENC("yuv type not support, store_type:%d sample_type:%d sel_type:%d\n",pEncPara->YuvStoreType,pEncPara->YuvSampleType);
				return HI_FAILURE;
			}
	}

	return HI_SUCCESS;

}

//保证码流和帧存Buffer都足够
//获取帧存和码流  ，帧存在pEncPara->stImage_OMX中，码流buffer在pEncPara->VEDU_STRM_ADDR中
static HI_S32 VENC_DRV_EflQueryChn_X(HI_U32 u32ChnID, VeduEfl_EncIn_S *pEncIn )    //for venc
{
	HI_U32 i      = 0;
	HI_S32 s32Ret = 0;
    VeduEfl_EncPara_S *pEncPara = (VeduEfl_EncPara_S *)g_stVencChn[u32ChnID].hVEncHandle;

	HI_U32 iNeedStreamCnt      = pEncPara->iSliceSplitNum;
	HI_U32 u32FrameNumInQueue  = 0;
	HI_U32 u32StreamNumInQueue = 0;
	HI_U32 uPicActHeight       = 0;
	HI_U32 uPicActCHeight      = 0;

	u32FrameNumInQueue  = VENC_DRV_MngQueueSize(pEncPara->FrameQueue_OMX);
	u32StreamNumInQueue = VENC_DRV_MngQueueSize(pEncPara->StreamQueue_OMX);

	//保证码流和帧存Buffer都足够
#ifdef SPLIT_SPS_PPS
	//if ( pEncPara->vcpi_protocol == VEDU_H265 && pEncPara->)
	if (pEncPara->bFirstNal2Send)
	{
		iNeedStreamCnt++;
	}
#endif

#ifdef HARDWARE_SPLIT_SPS_PPS_EN
    //if ( pEncPara->vcpi_protocol == VEDU_H265 && pEncPara->)
    if (pEncPara->bFirstNal2Send || pEncPara->bRequestIFrame) //这里是否需要加锁 l00214825
    {
    iNeedStreamCnt++;
    }
    #endif

    if (u32FrameNumInQueue < 1 || u32StreamNumInQueue < iNeedStreamCnt)
    {
        //HI_ERR_VENC("Stream Buffer or Frame Buffer is not enough: FrameNum:%d StreamNum:%d\n",
        //    u32FrameNumInQueue,u32StreamNumInQueue);
        return HI_FAILURE;
    }
    HI_DBG_VENC("pEncPara->bFirstNal2Send:%d pEncPara->bRequestIFrame:%d\n",pEncPara->bFirstNal2Send,pEncPara->bRequestIFrame);
    pEncPara->stStat.GetFrameNumTry++;
    HI_DBG_VENC("enter %s,pEncPara:0x%x\n", __func__, pEncPara);
    if (HI_SUCCESS != VENC_DRV_EflGetImage_OMX(g_stVencChn[u32ChnID].hVEncHandle, &(pEncPara->stImage_OMX)))
    {
        HI_DBG_VENC("%s, channel:0x%x get image failed\n", __func__, g_stVencChn[u32ChnID].hVEncHandle);
        return HI_FAILURE;
    }

    pEncPara->WaitingIsr = 1;
    pEncPara->stStat.GetFrameNumOK++;

    pEncPara->stStat.u32RealSendInputRrmRate  = pEncPara->ViFrmRate;
    pEncPara->stStat.u32RealSendOutputFrmRate = pEncPara->VoFrmRate;

    HI_DBG_VENC("pEncPara->stImage_OMX.picWidth:%d\n",pEncPara->stImage_OMX.picWidth);
    HI_DBG_VENC("pEncPara->stImage_OMX.picHeight:%d\n",pEncPara->stImage_OMX.picHeight);


#if 0 //动态分辨率暂时不支持 l00214825 0721
	/* configured the resolving power dynamically */
    if ((pEncPara->stImage_OMX.picWidth != pEncPara->vcpi_imgwidth_pix)||(pEncPara->stImage_OMX.picHeight != pEncPara->vcpi_imgheight_pix))
    {
       HI_INFO_VENC("pEncPara->stImage_OMX.picWidth:%d\n",pEncPara->stImage_OMX.picWidth);
       HI_INFO_VENC("g_stVencChn[u32ChnID].stChnUserCfg.u32Width:%d\n",g_stVencChn[u32ChnID].stChnUserCfg.u32Width);
       HI_INFO_VENC("pEncPara->stImage_OMX.picHeight:%d\n",pEncPara->stImage_OMX.picHeight);
       HI_INFO_VENC("g_stVencChn[u32ChnID].stChnUserCfg.u32Height:%d\n",g_stVencChn[u32ChnID].stChnUserCfg.u32Height);

	   if ((pEncPara->stImage_OMX.picWidth == g_stVencChn[u32ChnID].stChnUserCfg.u32Width)
		 &&(pEncPara->stImage_OMX.picHeight == g_stVencChn[u32ChnID].stChnUserCfg.u32Height))
	   {
	   	   HI_INFO_VENC("request I frame\n");
		   VENC_DRV_EflRequestIframe(g_stVencChn[u32ChnID].hVEncHandle);
		   s32Ret = VENC_DRV_EflSetResolution(g_stVencChn[u32ChnID].hVEncHandle, pEncPara->stImage_OMX.picWidth, pEncPara->stImage_OMX.picHeight);
           if (HI_SUCCESS != s32Ret)
           {
               HI_ERR_VENC("VeduEfl_SetResolution err:%#x.\n", s32Ret);
			   pEncPara->stStat.ErrCfgSkip++;
               return HI_FAILURE;
           }
	   }
	   else
	   {
	       HI_ERR_VENC("ERR:Different resolution between the frame Info and the Encoder Cfg!Encode: %dX%d,FrameInfo: %dX%d\n",
		   	            g_stVencChn[u32ChnID].stChnUserCfg.u32Width,g_stVencChn[u32ChnID].stChnUserCfg.u32Height,
		   	            pEncPara->stImage_OMX.picWidth,pEncPara->stImage_OMX.picHeight);
		   pEncPara->stStat.ErrCfgSkip++;
		    return HI_FAILURE;
	   }
    }
#endif
    /* skip - frame rate ctrl */
    if (HI_SUCCESS
        != VENC_DRV_EflRcFrmRateCtrl( g_stVencChn[u32ChnID].hVEncHandle, pEncPara->stStat.PutFrameNumOK/*pImagePriv->u32FrmCnt*/))
    {
        HI_INFO_VENC("Skip this frame! channel:%d handle:0x%x\n",u32ChnID,g_stVencChn[u32ChnID].hVEncHandle);
        //begin--- 跳帧之后 认为该帧已用完 应当发done消息 luojianhui 2015/2/27
	    s32Ret = VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS , &pEncPara->stImage_OMX);
        pEncPara->stStat.MsgQueueNum++;
        if (s32Ret == HI_SUCCESS)
        {
            pEncPara->stStat.PutFrameNumOK++;   //是编码完之后++ 还是码控计算完之后++
        }
        else
        {
            HI_INFO_VENC("put msg error\n");
        }
        //end
        return HI_FAILURE;
    }
    pEncPara->YuvStoreType  = pEncPara->stImage_OMX.store_type;//Convert_PIX_Format(pEncPara->stImage.ePixFormat,0);
    pEncPara->YuvSampleType = pEncPara->stImage_OMX.sample_type;//Convert_PIX_Format(pEncPara->stImage.ePixFormat,1);//SampleOrPackageSelTab[pEncPara->stImage.enVideoFormat];
    pEncPara->YuvSelType  = pEncPara->stImage_OMX.package_sel;//Convert_PIX_Format(pEncPara->stImage.ePixFormat,2);//SampleOrPackageSelTab[pEncPara->stImage.enVideoFormat];
    pEncPara->StoreFmt      = pEncPara->YuvStoreType;

    if(HI_SUCCESS != VENC_DRV_ConvertYUVType(pEncPara))
    {
        HI_ERR_VENC("VENC_DRV_ConvertYUVType error!!\n");
        return HI_FAILURE;
    }

    /* check the picture resolving power ,stride ,addr info first*/
    if ( HI_SUCCESS != VENC_DRV_EflCheckImgCfg_OMX(&pEncPara->stImage_OMX, pEncPara->YuvStoreType) )
    {
        HI_ERR_VENC("stImg cfg erro!!\n");
        pEncPara->stStat.ErrCfgSkip++;

        //begin---本帧错误，将本帧empty buffer done  l00214825 2015/2/27
        s32Ret = VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS , &pEncPara->stImage_OMX);
        pEncPara->stStat.MsgQueueNum++;

        if (s32Ret == HI_SUCCESS)
        {
            pEncPara->stStat.PutFrameNumOK++;	//是编码完之后++ 还是码控计算完之后++
        }
        else
        {
            HI_INFO_VENC("put msg error\n");
        }
        //end
        return HI_FAILURE;
    }

    pEncIn->BusViY = pEncPara->stImage_OMX.bufferaddr_Phy + pEncPara->stImage_OMX.offset;//pEncPara->stImage.stBufAddr[0].u32PhyAddr_Y;
    pEncIn->BusViC = pEncIn->BusViY + pEncPara->stImage_OMX.offset_YC;//pEncPara->stImage.stBufAddr[0].u32PhyAddr_C;
	pEncIn->BusViV = pEncIn->BusViC + pEncPara->stImage_OMX.offset_YCr;

	HI_DBG_VENC("img:pEncPara->stImage_OMX.buffer_size:%d\n",pEncPara->stImage_OMX.buffer_size);

	if (pEncPara->vcpi_store_mode == 0)
	{
	    uPicActHeight  = pEncPara->stImage_OMX.picHeight;
        uPicActCHeight = pEncPara->stImage_OMX.picHeight/2;
	}
	else
	{
		uPicActHeight  = ALIGN_UP(pEncPara->stImage_OMX.picHeight,16);
		uPicActCHeight = ALIGN_UP(pEncPara->stImage_OMX.picHeight/2,16);
	}

	if (pEncPara->StoreFmt == VENC_STORE_PLANNAR)
	{
		pEncPara->VEDU_SRC_YLength = pEncPara->stImage_OMX.strideY * uPicActHeight;
		if (pEncPara->YuvSampleType == VENC_YUV_420)
		{
			pEncPara->VEDU_SRC_CLength = pEncPara->stImage_OMX.strideC * uPicActCHeight;
		}
		else if (pEncPara->YuvSampleType == VENC_YUV_422)
		{
			pEncPara->VEDU_SRC_CLength = pEncPara->stImage_OMX.strideC * uPicActHeight;
		}
		pEncPara->VEDU_SRC_VLength = pEncPara->VEDU_SRC_CLength;
	}
	else if (pEncPara->StoreFmt == VENC_STORE_SEMIPLANNAR)
	{
		pEncPara->VEDU_SRC_YLength = pEncPara->stImage_OMX.strideY * uPicActHeight;
		pEncPara->VEDU_SRC_CLength = pEncPara->stImage_OMX.strideC * uPicActCHeight;//目前只支持simeplanar420
		pEncPara->VEDU_SRC_VLength = 0;
	}
	else if (pEncPara->StoreFmt == VENC_STORE_PACKAGE)
	{
		pEncPara->VEDU_SRC_YLength = pEncPara->stImage_OMX.strideY *uPicActHeight;
		pEncPara->VEDU_SRC_CLength = 0;
		pEncPara->VEDU_SRC_VLength = 0;
	}
	else if (pEncPara->StoreFmt == VENC_STORE_RGB)
	{
		pEncPara->VEDU_SRC_YLength = pEncPara->stImage_OMX.strideY * uPicActHeight;
		pEncPara->VEDU_SRC_CLength = 0;
		pEncPara->VEDU_SRC_VLength = 0;
	}

	pEncIn->ViYStride = pEncPara->stImage_OMX.strideY;//pEncPara->stImage.stBufAddr[0].u32Stride_Y;
	pEncIn->ViCStride = pEncPara->stImage_OMX.strideC;//pEncPara->stImage.stBufAddr[0].u32Stride_C*2;

    pEncIn->PTS0 = pEncPara->stImage_OMX.timestamp;//pEncPara->stImage.u32Pts;
    pEncIn->PTS1 = 0;

	//----end-------
	HI_INFO_VENC("pEncPara->iSliceSplitNum:%d pEncPara->iCurrentStreamCnt:%d\n",pEncPara->iSliceSplitNum,pEncPara->iCurrentStreamCnt);

#ifdef SPLIT_SPS_PPS
		if (pEncPara->bFirstNal2Send)
		{
			if( VENC_DRV_EflGetStream_OMX(g_stVencChn[u32ChnID].hVEncHandle, &(pEncPara->stStream_OMX[0])))
			{
				HI_ERR_VENC("%s, channel:0x%x get stream buffer failed\n", __func__, g_stVencChn[u32ChnID].hVEncHandle);
				return HI_FAILURE;
			}

			HI_VOID* pStreamHeader = (HI_VOID*)pEncPara->stStream_OMX[0].kernelbufferaddr;
			HI_U32 uLength = 0;

			if (pEncPara->vcpi_protocol == VEDU_H265)
			{
				memcpy(pStreamHeader,pEncPara->VpsStream, pEncPara->VpsBits/8);
				pStreamHeader += pEncPara->VpsBits/8;

				memcpy(pStreamHeader,pEncPara->SpsStream, pEncPara->SpsBits/8);
				pStreamHeader += pEncPara->SpsBits/8;

				memcpy(pStreamHeader,pEncPara->PpsStream, pEncPara->PpsBits/8);
				pStreamHeader += pEncPara->PpsBits/8;

				uLength = pEncPara->VpsBits/8+ pEncPara->SpsBits/8+ pEncPara->PpsBits/8;
			}
			else if (pEncPara->vcpi_protocol == VEDU_H264)
			{
				memcpy(pStreamHeader,pEncPara->SpsStream, pEncPara->SpsBits/8);
				pStreamHeader += pEncPara->SpsBits/8;

				memcpy(pStreamHeader,pEncPara->PpsStream, pEncPara->PpsBits/8);
				pStreamHeader += pEncPara->PpsBits/8;

				uLength = pEncPara->SpsBits/8+ pEncPara->PpsBits/8;
			}

			pEncPara->stStream_OMX[0].bEOS = pEncPara->stImage_OMX.bEOS;
			pEncPara->stStream_OMX[0].timestamp = pEncPara->stImage_OMX.timestamp;
			pEncPara->stStream_OMX[0].data_len = uLength;

			pEncPara->stStream_OMX[0].flags |=  OMXVENC_BUFFERFLAG_STARTTIME;
			pEncPara->stStream_OMX[0].flags |=  OMXVENC_BUFFERFLAG_CODECCONFIG;
			VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, 0 ,&pEncPara->stStream_OMX[0]);

			memset(&(pEncPara->stStream_OMX[0]),0,sizeof(venc_user_buf));
			pEncPara->bFirstNal2Send = HI_FALSE;

		}
#endif

#ifdef HARDWARE_SPLIT_SPS_PPS_EN
		if (pEncPara->bFirstNal2Send)
		{
			if( VENC_DRV_EflGetStream_OMX(g_stVencChn[u32ChnID].hVEncHandle, &(pEncPara->stStreamHeader_OMX)))
			{
				HI_ERR_VENC("%s, channel:0x%x get stream buffer failed\n", __func__, g_stVencChn[u32ChnID].hVEncHandle);
				return HI_FAILURE;
			}
		}
#endif

	for (i = 0;i < pEncPara->iSliceSplitNum;i++)
	{
		pEncPara->stStat.GetStreamNumTry++;
		if( VENC_DRV_EflGetStream_OMX(g_stVencChn[u32ChnID].hVEncHandle, &(pEncPara->stStream_OMX[pEncPara->iCurrentStreamCnt])))
		{
			HI_ERR_VENC("%s, channel:0x%x get stream buffer failed\n", __func__, g_stVencChn[u32ChnID].hVEncHandle);
			return HI_FAILURE;
		}

		HI_DBG_VENC("get new stream:pEncPara->stStream_OMX[%d].size:%d\n",pEncPara->iCurrentStreamCnt,pEncPara->stStream_OMX[pEncPara->iCurrentStreamCnt].buffer_size);
		pEncPara->stStat.GetStreamNumOK++;
		pEncPara->stStat.GetStreamNumInTaskOK++;
		pEncPara->stStat.StreamQueueNum--;

		pEncPara->VEDU_STRM_ADDR[pEncPara->iCurrentStreamCnt] = pEncPara->stStream_OMX[pEncPara->iCurrentStreamCnt].bufferaddr_Phy;
		pEncPara->VEDU_STRM_BUFLEN[pEncPara->iCurrentStreamCnt] = pEncPara->stStream_OMX[pEncPara->iCurrentStreamCnt].buffer_size;
		pEncPara->iCurrentStreamCnt++;
	}
    return HI_SUCCESS;
}

static HI_HANDLE VENC_DRV_EflQueryChn( VeduEfl_EncIn_S *pEncIn )
{
    HI_U32 u32StartQueryNo = 0;
    HI_S32 s32StartChnID   = 0; /*this ID correspond to VeduChnCtx(class:VeduEfl_ChnCtx_S) */
	HI_U32 u32ChnID        = 0; /*this ID correspond to g_stVencChn(class:OPTM_VENC_CHN_S)*/
	HI_HANDLE hHd_ret      = HI_NULL;
    VeduEfl_EncPara_S *pEncPara = HI_NULL;
	VEDU_LOCK_FLAG flag;
    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);

    for (u32StartQueryNo = 0;u32StartQueryNo < MAX_VEDU_CHN;u32StartQueryNo++)
    {
        D_VENC_GET_CHN_FROM_TAB(s32StartChnID,u32StartQueryNo);

        if ( INVAILD_CHN_FLAG == s32StartChnID )
        {
            continue;
        }
		D_VENC_GET_CHN(u32ChnID,VeduChnCtx[s32StartChnID].EncHandle);
		if (u32ChnID >= VENC_MAX_CHN_NUM)
		{
            HI_WARN_VENC("%s, D_VENC_GET_CHN  failed!\n", __func__);
		    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
            return HI_NULL;
        }
        pEncPara = (VeduEfl_EncPara_S *) VeduChnCtx[s32StartChnID].EncHandle;

		//如果已经停止编码就不取帧了
		if(!pEncPara->bStartEnc)
		{
            HI_INFO_VENC("%s, The Channel(0x%x) is not start!\n", __func__, pEncPara);
			continue;
		}

        if( HI_INVALID_HANDLE == pEncPara->stSrcInfo.handle )
        {
            pEncPara->stSrcInfo.handle = VeduChnCtx[s32StartChnID].EncHandle;
        }

        // 获取一帧编码原始帧存 l00214825
        if (HI_SUCCESS != VENC_DRV_EflQueryChn_X(u32ChnID, pEncIn))
        {
            //HI_DBG_VENC("no YUV\n");
            pEncPara->WaitingIsr = 0;
            continue;
        }
        HI_DBG_VENC("Get one frame \n");
        break; /* find channel:s32StartChnID  to enc */
    }

	if (MAX_VEDU_CHN != u32StartQueryNo)
	{
	   //相同优先级之间再排序，防止同一优先级在前面的总先处理 l00214825
		if( HI_SUCCESS != VENC_DRV_EflSortPriority_2(PriorityTab[1][u32StartQueryNo]))
		HI_WARN_VENC("%s, can't fine the channel match with priority(%d)\n", __func__, PriorityTab[1][u32StartQueryNo]);
	}

    if ((s32StartChnID >= 0)&&(s32StartChnID < MAX_VEDU_CHN))
    {
		hHd_ret = VeduChnCtx[s32StartChnID].EncHandle;
		HI_DBG_VENC("%s, get the yuv of channal:%d handle:0x%x\n", __func__, s32StartChnID,hHd_ret);
    }

	VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if (MAX_VEDU_CHN == u32StartQueryNo)
    {
        HI_DBG_VENC("%s, No channel have YUV?\n", __func__);
        return (HI_U32)HI_NULL;
    }
    else
    {
  /*
		if (g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun && pEncPara)//modify by ljh && (g_stVencChn[u32ChnID].enSrcModId < HI_ID_BUTT)
		{
		   HI_DBG_VENC("writeyuv....\n");
		   HI_DBG_VENC("writeyuv!!!\n");
		   VENC_DRV_DbgWriteYUV(&pEncPara->stImage, g_stVencChn[u32ChnID].stProcWrite.YUVFileName,0);
		}
*/
        HI_INFO_VENC("%s, get new channal and yuv\n", __func__);
        return hHd_ret;
    }
}

static HI_VOID Venc_ISR( HI_VOID )
{
	HI_U32 i            = 0;
    HI_U32 ret          = 0;
    HI_U32 u32VeChn     = 0;
	HI_U32 VeduTimeout  = 0;
	HI_U32 VeduSliceInt = 0;
	HI_U32 VencEndOfPic = 0;
	HI_U32 *pINTCLR     = NULL;
	VeduEfl_EncPara_S *pEncPara   = NULL;
	S_HEVC_AVC_REGS_TYPE *pAllReg = NULL;

#ifdef TEST_TIME
	HI_U32 timetmp = HI_GetTS();
#endif

    HI_INFO_VENC("enter %s ()\n", __func__);

    D_VENC_GET_CHN(u32VeChn, VeduIpCtx.CurrHandle);
	if (u32VeChn >= MAX_VEDU_CHN)
	{
       HI_INFO_VENC("%s, no such channel:0x%x\n", __func__, VeduIpCtx.CurrHandle);
	   return;
	}

	pEncPara = (VeduEfl_EncPara_S *) VeduIpCtx.CurrHandle;
//	pEncPara->CanBeDestroy = HI_FALSE;

#ifdef TEST_TIME
    pEncPara->stStat.u32IrqNum++;
    pEncPara->stStat.TotalFrame++;
    if(pEncPara->stStat.TotalFrame>5)
    {
        pEncPara->stStat.TotalOneCycletime += timetmp - pEncPara->stStat.StartVencTime;
        pEncPara->stStat.OneCycletime = pEncPara->stStat.TotalOneCycletime/(pEncPara->stStat.TotalFrame-5);//timetmp - pEncPara->stStat.StartVencTime;//
    }
#endif

    pAllReg  = (S_HEVC_AVC_REGS_TYPE *)pEncPara->pRegBase;
    pINTCLR  = (HI_U32 *)&(pAllReg->VEDU_VCPI_REGS.VEDU_INTCLR_NS.u32);
    VeduTimeout  = pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_vedu_timeout_ns;
    VeduSliceInt = pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_vedu_slice_end_ns;
    VencEndOfPic = pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_eop_ns;

#ifdef VENC_SIMULATE
    pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_eop = 0;
#endif

    if (VeduTimeout)//超时软复位 pAllReg->VEDU_RAWINT.bits.VeduTimeout
    {
        HI_ERR_VENC("VENC timeout interrupt!! lowdelay= %d\n",pEncPara->LowDlyMod);

        *pINTCLR = 0x08000000;
 //       pAllReg->VEDU_VCPI_REGS.VEDU_SOFT.bits.vedu_soft_rst = 0x1;//2015/07/18 软复位
        HI_INFO_VENC("VENC reset success!!\n");
        pEncPara->bRequestIFrame = HI_TRUE;
        VeduIpCtx.IpFree = 1;
        pEncPara->stStat.PutFrameNumTry++;
        VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS, &pEncPara->stImage_OMX);
        //输出 to do
        pEncPara->stStat.MsgQueueNum++;
        pEncPara->stStat.PutFrameNumOK++;
        pEncPara->bFirstSlc = HI_TRUE;
    }

    if (VeduSliceInt)//低延时模式下slice级中断处理 pAllReg->VEDU_RAWINT.bits.VeduSliceInt
    {
        HI_INFO_VENC("slice in ,SliceIrqNum:%d\n",pEncPara->stStat.u32SliceIrqNum);
        if (pEncPara->bFirstSlc)
        {
            //delete by ljh
            //VENC_DRV_DbgLowdelayEvent(u32VeChn,EVENT_VENC_FRM_OUT, pEncPara->stImage.u32FrameIndex,pEncPara->stImage.hTunnelSrc);
            pEncPara->bFirstSlc = HI_FALSE;
        }

#ifdef HARDWARE_SPLIT_SPS_PPS_EN
        if (pEncPara->bFirstNal2Send)
        {
            HI_U32 uLength = 0;
            if (pEncPara->vcpi_protocol == VEDU_H265)
            {
                uLength = pEncPara->VpsBits/8+ pEncPara->SpsBits/8+ pEncPara->PpsBits/8;
            }
            else if (pEncPara->vcpi_protocol == VEDU_H264)
            {
                uLength = pEncPara->SpsBits/8+ pEncPara->PpsBits/8;
            }

            pEncPara->stStreamHeader_OMX.bEOS = pEncPara->stImage_OMX.bEOS;
            pEncPara->stStreamHeader_OMX.timestamp = pEncPara->stImage_OMX.timestamp;
            pEncPara->stStreamHeader_OMX.data_len = uLength;

            pEncPara->stStreamHeader_OMX.flags |=  OMXVENC_BUFFERFLAG_STARTTIME;
            pEncPara->stStreamHeader_OMX.flags |=  OMXVENC_BUFFERFLAG_CODECCONFIG;
            VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, 0 ,&pEncPara->stStreamHeader_OMX);
            memset(&(pEncPara->stStreamHeader_OMX),0,sizeof(venc_user_buf));
            pEncPara->bFirstNal2Send = HI_FALSE;
        }

#endif

#ifdef OUTPUT_LOWDELAY_EN
        VENC_DRV_EflReadRegVencSimple ( (HI_HANDLE)pEncPara );
        for (i = pEncPara->iLastEncodedStreamCnt; i < pEncPara->iSliceSplitNum; i++)
        {
            if (pEncPara->VEDU_SLICE_LENGTH[i] == 0)
            {
                break;
            }

            pEncPara->stStat.PutStreamNumTry++;
            HI_INFO_VENC("Streambuffer:%d  Data length:%d \n",i,pEncPara->stStream_OMX[i].data_len);

            pEncPara->stStream_OMX[i].bEOS = pEncPara->stImage_OMX.bEOS;
            pEncPara->stStream_OMX[i].timestamp = pEncPara->stImage_OMX.timestamp;

            HI_DBG_VENC("pEncPara->stStream_OMX[i].bEOS :0x%x,pEncPara->stStream_OMX[i].timestamp :%lld\n",
                    pEncPara->stStream_OMX[i].bEOS,pEncPara->stStream_OMX[i].timestamp);

            pEncPara->stStream_OMX[i].flags = 0;
            switch( pEncPara->vcpi_frame_type  )
            {
                case 0:  /*IDR*/
                {
                    pEncPara->stStream_OMX[i].flags |=  OMXVENC_BUFFERFLAG_SYNCFRAME;
                    if (i == pEncPara->iSliceSplitNum - 1)
                    {
                        pEncPara->stStream_OMX[i].flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
                    }
                    break;
                }
                case 1:  /*P*/
                {
                    if (i == pEncPara->iSliceSplitNum - 1)
                    {
                        pEncPara->stStream_OMX[i].flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
                    }
                    break;
                }
                default:
                HI_ERR_VENC("%s, Nalu.NaluType(%d) is invalid\n", __func__);
                break;
            }

            ret = VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, 0 ,&pEncPara->stStream_OMX[i]);

            if (ret == HI_SUCCESS)
            {
                pEncPara->stStat.PutStreamNumOK++;
                pEncPara->stStat.MsgQueueNum++;
            }
            else
            {
                HI_INFO_VENC("put stream error\n");
            }
            pEncPara->iCurrentStreamCnt--;
            HI_INFO_VENC("slice isr output done!!!\n");

        }
        pEncPara->iLastEncodedStreamCnt = i;

        HI_INFO_VENC("pEncPara->iLastEncodedStreamCnt:%d \n",pEncPara->iLastEncodedStreamCnt);
#endif

		if(HI_SUCCESS != VENC_DRV_EflEndOneSliceVenc( pEncPara ))
		{
			HI_ERR_VENC("%s, VENC_DRV_EflEndOneSliceVenc  Error!!\n", __func__);
		}

		*pINTCLR = 0x400;//清中断
		pEncPara->stStat.u32SliceIrqNum++;
    }
//#endif

    if (VencEndOfPic) //帧级中断  pAllReg->VEDU_RAWINT.bits.VencEndOfPic
    {
        pEncPara->stStat.u32FrameIrqNum++;
        pEncPara->bFirstSlc = HI_TRUE;

        /* postprocess frame encoded */
        VENC_DRV_EflReadRegVenc    ( (HI_HANDLE)pEncPara );

        *pINTCLR = 0xFFFFFFFF;
#ifdef SHUTDOWN_REGULATOR_EN
        //每帧中断回读完venc状态后venc下电
        //只有单通道，宽*高 < 4k*2k*2/3，帧率<30，才启动帧间上下电
        if ((cur_handle_num <= 1) &&  (pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix* pEncPara->pstCfg_EncPara->vcpi_imgheight_pix
              <= VEDU_MAX_ENC_WIDTH*VEDU_MAX_ENC_HEIGHT*2/3) && (pEncPara->iFrameRate <= 30))
        {
            Regulator_Disable();
            b_Regular_down_flag = HI_TRUE;
            HI_INFO_VENC("hardware power down!!!\n");
        }
#endif
	    VENC_DRV_EflEndOneFrameVenc( (HI_HANDLE)pEncPara );

#ifdef RE_ENCODE_EN
        if (pEncPara->bReEncode)
        {
            //pEncPara->bReEncode = 0;
            VeduIpCtx.IpFree = 0;
            pEncPara->bAXIPressEn = 0;

            if (pEncPara->stRc.FrmNumSeq == 0)
            {
                pEncPara->vlcst_para_set_en = 1;
            }

            if (pEncPara->vcpi_protocol == VEDU_H265)
            {
                VENC_DRV_H265e_ReMakeSlcHdr((HI_HANDLE)pEncPara);
            }
            VENC_DRV_EflCfgRegVenc((HI_HANDLE)pEncPara);
            VENC_DRV_EflStartVencByReg((HI_HANDLE)pEncPara);
            pEncPara->bAXIPressEn = 1;
            HI_INFO_VENC("ReEncode in ISR\n");
            return;
        }
#endif
        HI_INFO_VENC("fill buffer done, VencBufFull:%d\n",pEncPara->VencBufFull);
        if(pEncPara->bOutPutbufflush == HI_FALSE && !pEncPara->VencBufFull)
        {

            for (i = 0; i < pEncPara->iSliceSplitNum; i++)
            {
#ifdef OUTPUT_LOWDELAY_EN
                if (i >= pEncPara->iLastEncodedStreamCnt)
                {
#endif
                    pEncPara->stStat.PutStreamNumTry++;
                    HI_INFO_VENC("Streambuffer:%d  Data length:%d \n",i,pEncPara->stStream_OMX[i].data_len);

                    pEncPara->stStream_OMX[i].bEOS = pEncPara->stImage_OMX.bEOS;
                    pEncPara->stStream_OMX[i].timestamp = pEncPara->stImage_OMX.timestamp;

                    HI_DBG_VENC("pEncPara->stStream_OMX[i].bEOS :0x%x,pEncPara->stStream_OMX[i].timestamp :%lld\n",
                        pEncPara->stStream_OMX[i].bEOS,pEncPara->stStream_OMX[i].timestamp);

                    pEncPara->stStream_OMX[i].flags = 0;
                    switch( pEncPara->vcpi_frame_type  )
                    {
                        case 0:  /*IDR*/
                        {
                            pEncPara->stStream_OMX[i].flags |=  OMXVENC_BUFFERFLAG_SYNCFRAME;
                            if (i == pEncPara->iSliceSplitNum - 1)
                            {
                                pEncPara->stStream_OMX[i].flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
                            }
                            break;
                        }
                        case 1:  /*P*/
                        {
                            if (i == pEncPara->iSliceSplitNum - 1)
                            {
                                pEncPara->stStream_OMX[i].flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
                            }
                            break;
                        }
                        default:
                            HI_ERR_VENC("%s, Nalu.NaluType(%d) is invalid\n", __func__);
                            break;
                    }

                    ret = VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, 0 ,&pEncPara->stStream_OMX[i]);
                    if (ret == HI_SUCCESS)
                    {
                        pEncPara->stStat.PutStreamNumOK++;
                        pEncPara->stStat.MsgQueueNum++;
                    }
                    else
                    {
                        HI_INFO_VENC("put stream error\n");
                    }
                    pEncPara->iCurrentStreamCnt--;
#ifdef OUTPUT_LOWDELAY_EN
                }
#endif
                memset((HI_VOID *)&(pEncPara->stStream_OMX[i]),0,sizeof(venc_user_buf));
                pEncPara->VEDU_STRM_ADDR[i] = 0;
                pEncPara->VEDU_STRM_BUFLEN[i] = 0;
                pEncPara->VEDU_SLICE_LENGTH[i] = 0;
                pEncPara->VEDU_SLICE_IS_END[i] = 0;
            }

            if (pEncPara->iCurrentStreamCnt != 0)
            {
                HI_ERR_VENC("pEncPara->iCurrentStreamCnt !=0 !!!!!\n");
            }

 #ifdef TEST_TIME
            pEncPara->stStat.FbdTime[pEncPara->stStat.OutputNum] = HI_GetTS();
            pEncPara->stStat.ThisTime = HI_GetTS();

            if(6 == pEncPara->stStat.PutStreamNumOK)
            {
                pEncPara->stStat.LastTime = pEncPara->stStat.ThisTime;
            }

            if(pEncPara->stStat.PutStreamNumOK > 6)
            {
                pEncPara->stStat.TotalEncTime += pEncPara->stStat.ThisTime - pEncPara->stStat.LastTime;
                pEncPara->stStat.AvgEncTime = pEncPara->stStat.TotalEncTime/(pEncPara->stStat.PutStreamNumOK-6);
            }

            pEncPara->stStat.LastTime = pEncPara->stStat.ThisTime;
#endif
        }

        HI_INFO_VENC("%s, empty buffer done\n", __func__);

		if(pEncPara->bInPutbufflush == HI_FALSE)
		{
		    pEncPara->stStat.PutFrameNumTry++;
			ret = VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS , &pEncPara->stImage_OMX);

	       if (ret == HI_SUCCESS)
	       {
	           pEncPara->stStat.PutFrameNumOK++;
			   pEncPara->stStat.MsgQueueNum++;
	       }
	       else
	       {
	           HI_INFO_VENC("%s, line:%d put frame error\n", __func__, __LINE__);
	       }
		}

        pEncPara->WaitingIsr = 0;

		// 0723 在此启动有hisi_mailbox(371):IPC timeout reason: ISR jam.报错
#if 0
		if (!g_stVencChn[u32VeChn].stProcWrite.bSaveYUVFileRun || !pEncPara->bStartEnc)//modify by ljh(g_stVencChn[u32VeChn].enSrcModId == HI_ID_BUTT)
		{
		    /* next frame to encode */
	        //VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
	        //新的一次编码，先获取通道和yuv l00214825
			EncHandle = VENC_DRV_EflQueryChn( &EncIn );

            HI_DBG_VENC("Save YUV,EncHandle:0x%x\n",EncHandle);
	        //VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
	        if( EncHandle != (HI_HANDLE)NULL )
		    {
		        VeduIpCtx.IpFree = 0;
		        VeduIpCtx.CurrHandle = EncHandle;
				pEncPara = (VeduEfl_EncPara_S *)EncHandle;
				if (pEncPara->IntraPic ||pEncPara->InterFrmCnt == 0)
				{
            				HI_INFO_VENC("check in isr pEncPara->IntraPic :%d pEncPara->InterFrmCnt :%d\n",pEncPara->IntraPic ,pEncPara->InterFrmCnt );
					check_enc_para(pEncPara->pstCfg_EncPara,pEncPara->IntraPic);
				}
		        VENC_DRV_EflStartOneFrameVenc( EncHandle, &EncIn );
		        VENC_DRV_EflCfgRegVenc       ( EncHandle );
                VENC_DRV_EflStartVencByReg( EncHandle );

		        HI_INFO_VENC("start venc in ISR\n");

		    }
		    else
		    {
		        VeduIpCtx.IpFree = 1;
				HI_DBG_VENC("Ip is Free in ISR\n");
		    }

		}
		else
		{
		   VeduIpCtx.IpFree = 1;
		}
#endif
		VeduIpCtx.IpFree = 1;
    }
}

static HI_VOID VENC_DRV_EflTask( HI_VOID )
{
    HI_S32 s32Ret         = 0;
    HI_U32 i              = 0;
    HI_U32 u32ChnID       = 0;
    HI_BOOL bTmpValue     = HI_FALSE;

    HI_HANDLE EncHandle         = (HI_HANDLE)NULL;
    VeduEfl_EncPara_S *pEncPara = HI_NULL;
    VeduIpCtx.TaskRunning = 1;

    VeduEfl_EncIn_S EncIn;

    memset(&EncIn, 0, sizeof(EncIn));

    /* 初始化等待队列头*/
	VENC_DRV_OsalInitEvent(&g_VENC_Event, 0);

    /* wait for venc start */
    while (!VeduIpCtx.StopTask)
    {
        for (i = 0; i < MAX_VEDU_CHN; i++)
        {
            //bTmpValue |= g_stVencChn[i].bEnable;//modify for pclint warn 655
			if(g_stVencChn[i].bEnable)
			{
				bTmpValue = HI_TRUE;
				break;
			}
        }

        if (HI_FALSE == bTmpValue)
        {
            msleep(10);
        }
        else
        {
            break;
        }
    }

    /* find valid venc handle */
    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        pEncPara = (VeduEfl_EncPara_S *)g_stVencChn[i].hVEncHandle;
        if ((HI_NULL == pEncPara) || (HI_INVALID_HANDLE == (HI_HANDLE)pEncPara))
        {
            continue;
        }
    }

	while (!VeduIpCtx.StopTask)
    {
		/* vedu_ip for h264*/
        if (VeduIpCtx.IpFree)
        {
#ifdef MD5_WC_EN
        	if ((HI_NULL != pEncPara) && (HI_INVALID_HANDLE != (HI_HANDLE)pEncPara))
	        {
	 			int chanlnum = 0;
				if(!pEncPara->CalcMd5Flag)
				{
				    for (chanlnum = 0; chanlnum < VENC_MAX_CHN_NUM; chanlnum++)
				    {
				        if (g_stVencChn[chanlnum].hVEncHandle == EncHandle)
				        {
				            break;
				        }
				    }

				    if (chanlnum == VENC_MAX_CHN_NUM)
				    {
				        HI_ERR_VENC("%s, Not have this handle! \n", __func__);
				        continue ;
				    }

					pEncPara->WaitingIsr = 1;
					VENC_DRV_MD5_CALC(pEncPara,chanlnum);

					pEncPara->WaitingIsr = 0;
					pEncPara->CalcMd5Flag = 1;
				}
			}
#endif

			/* if ipfree, don't irqlock */
           // VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);

			EncHandle = VENC_DRV_EflQueryChn( &EncIn );
#ifdef MD5_WC_EN
			pEncPara = (VeduEfl_EncPara_S *)EncHandle;
#endif
            if (EncHandle != (HI_HANDLE)NULL)
            {
                D_VENC_GET_CHN(u32ChnID,EncHandle);
				if (u32ChnID >= VENC_MAX_CHN_NUM)
				{
				    continue;
				}

			    VeduIpCtx.IpFree     = 0;
                VeduIpCtx.CurrHandle = EncHandle;
				pEncPara = (VeduEfl_EncPara_S *)EncHandle;
				HI_DBG_VENC("%s, line:%d, EncHandle:0x%llx\n", __func__, __LINE__, EncHandle);

				if (pEncPara->IntraPic ||pEncPara->InterFrmCnt == 0)
				{
            		HI_INFO_VENC("%s, check in task pEncPara->IntraPic :%d pEncPara->InterFrmCnt :%d\n", __func__, pEncPara->IntraPic ,pEncPara->InterFrmCnt );
					check_enc_para(pEncPara->pstCfg_EncPara,pEncPara->IntraPic);
				}

                VENC_DRV_EflStartOneFrameVenc( EncHandle, &EncIn );
                VENC_DRV_EflCfgRegVenc( EncHandle );
				pEncPara->stStat.StartVencNumInTask++;
				HI_INFO_VENC("%s, pEncPara->stStat.StartVencNumInTask:%d\n", __func__, pEncPara->stStat.StartVencNumInTask);

				VENC_DRV_EflStartVencByReg( EncHandle );
          		pEncPara->CalcMd5Flag = 0;
                HI_INFO_VENC("%s, start venc in task\n", __func__);
            }
        }

        /* if ipfree, sleep */
        s32Ret = VENC_DRV_OsalWaitEvent(&g_VENC_Event, msecs_to_jiffies(5));
        //msleep(1);
        if (0 != s32Ret)
        {
        	//HI_DBG_VENC("wait time out!\n");
        }
    }

    VeduIpCtx.TaskRunning = 0;
    HI_INFO_VENC("exit %s()!\n", __func__);
    return;
}



static HI_VOID VENC_DRV_EflQueryMode( HI_VOID )
{

    VeduEfl_EncPara_S *pEncPara = HI_NULL;
    HI_U32 i = 0;
    HI_BOOL bTmpValue = HI_FALSE;

    S_HEVC_AVC_REGS_TYPE *pAllReg = NULL;

    /* wait for venc start */
    HI_INFO_VENC("enter, VeduIpCtx.StopTask:%d\n",VeduIpCtx.StopTask);

    while (!VeduIpCtx.StopTask)
    {
		for (i = 0; i < MAX_VEDU_CHN; i++)
		{
			if(g_stVencChn[i].bEnable)
			{
				bTmpValue = HI_TRUE;
				break;
			}
		}

		if (HI_FALSE == bTmpValue)
		{
		    msleep(1);
		}
		else
		{
			HI_INFO_VENC("channel:%d enable\n",i);
			break;
		}
    }

    while (!VeduIpCtx.StopTask)
    {
        // 没有获得通道，不进行以下判断 l00214825
        if (VeduIpCtx.CurrHandle == 0)
        {
            msleep(10);
            continue;
        }

        pEncPara  = (VeduEfl_EncPara_S *) VeduIpCtx.CurrHandle;

		pAllReg = (S_HEVC_AVC_REGS_TYPE *)pEncPara->pRegBase;
		if(pAllReg->VEDU_VCPI_REGS.VEDU_RAWINT_NS.bits.rint_ve_eop_ns)
		{
			Venc_ISR();
		}
		else
		{
			msleep(1);
			//usleep(10);
		}
    }

    return;
}



/******************************************************************************
Function   :
Description: IP-VEDU & IP-JPGE Open & Close
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflOpenVedu( HI_VOID )
{
    HI_U32 i = 0;
	HI_INFO_VENC("enter %s()\n", __func__);

    //l00214825 0909  全局变量，开始置为0 否则第2次open会有问题
    memset((HI_VOID *)&VeduIpCtx, 0, sizeof(VeduIpCtx));

    /* creat channel control mutex */
    if (HI_FAILURE == VENC_DRV_OsalLockCreate( &VeduIpCtx.pChnLock ))
    {
        HI_ERR_VENC("%s, VENC_DRV_OsalLockCreate failed\n", __func__);
		return HI_FAILURE;
    }

#ifdef SHUTDOWN_REGULATOR_EN
	if (b_Regular_down_flag == HI_TRUE)
	{
		Venc_Regulator_Enable();
		b_Regular_down_flag = HI_FALSE;
		HI_INFO_VENC("%s, hardware power on!!!\n", __func__);
	}
#endif
    /* map reg_base_addr to virtual address */
	// 注意寄存器基地址 l00214825
    VeduIpCtx.pRegBase = (HI_U32 *)ioremap(gVencRegBaseAddr, gVencRegRange);
	if (HI_NULL == VeduIpCtx.pRegBase)
	{
        HI_ERR_VENC("%s, ioremap failed\n", __func__);
		VENC_DRV_OsalLockDestroy( VeduIpCtx.pChnLock );
		return HI_FAILURE;
	}

	// DDR 地址映射
	HI_INFO_VENC("%s, HI_DDR_MEM_Init\n", __func__);
	DRV_MEM_INIT();

    /* set ip free status */
    VeduIpCtx.IpFree = 1;

    /* clear channel status */
    for (i = 0; i < MAX_VEDU_CHN; i++)
    {
        VeduChnCtx[i].EncHandle = (HI_HANDLE)NULL;
    }

    /* init IRQ */
    VENC_HAL_DisableAllInt((S_HEVC_AVC_REGS_TYPE*)(VeduIpCtx.pRegBase));
    VENC_HAL_ClrAllInt    ((S_HEVC_AVC_REGS_TYPE*)(VeduIpCtx.pRegBase));

#ifdef SHUTDOWN_REGULATOR_EN
	if (b_Regular_down_flag == HI_FALSE)
	{
		Venc_Regulator_Disable();
		b_Regular_down_flag = HI_TRUE;
	}
#endif

#ifdef IRQ_EN
    if (HI_FAILURE == VENC_DRV_OsalIrqInit(gVeduIrqNum, Venc_ISR))
    {
        HI_ERR_VENC("%s, VENC_DRV_OsalIrqInit failed\n", __func__);
		return HI_FAILURE;
    }
#endif
    /* creat thread to manage channel */
    VeduIpCtx.StopTask    = 0;
    VeduIpCtx.TaskRunning = 0;

    VENC_DRV_OsalCreateTask( &VeduIpCtx.pTask_Frame, "HI_VENC_FrameTask", VENC_DRV_EflTask );

	msleep(1);

#ifndef IRQ_EN
	VENC_DRV_OsalCreateTask( &VeduIpCtx.pTask_Stream, "HI_VENC_QueryMode", VENC_DRV_EflQueryMode);
#endif


#ifdef MD5_WC_EN
    pMd5SrcY = (HI_U8 *)vmalloc(VEDU_MAX_ENC_WIDTH*VEDU_MAX_ENC_HEIGHT);
    pMd5SrcU = (HI_U8 *)vmalloc(VEDU_MAX_ENC_WIDTH*VEDU_MAX_ENC_HEIGHT);
    pMd5SrcV = (HI_U8 *)vmalloc(VEDU_MAX_ENC_WIDTH*VEDU_MAX_ENC_HEIGHT);
    pMd5SrcUV = (HI_U8 *)vmalloc(VEDU_MAX_ENC_WIDTH*VEDU_MAX_ENC_HEIGHT);

    for(i =0;i<VENC_MAX_CHN_NUM;i++)
    {
        g_stVencChn[i].bhavecalc = 0;
        MD5CalcInit (&(context[i]));
    }
    fpmd5 = VENC_DRV_OsalFopen("/mnt/sdcard/Md5result.txt", O_RDWR | O_CREAT  | O_APPEND,  0);
    if (fpmd5 == NULL )
    {
		HI_ERR_VENC("%s, md5 open file err!!!!!!!\n", __func__);
	}
#endif

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflCloseVedu( HI_VOID )
{
#ifdef MD5_WC_EN
	int i = 0;
	HI_U8 digesttmp[16] ;
	HI_U8 digesttmp2[100] ;
	memset(digesttmp, 0, 16);
	memset(digesttmp, 0, 100);
#endif
	HI_INFO_VENC("enter %s()\n", __func__);
    VeduIpCtx.StopTask = 1;

    while (VeduIpCtx.TaskRunning)
    {
        msleep(1);
    }

    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Frame);
#ifndef IRQ_EN
    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Stream);
#endif


#ifdef SHUTDOWN_REGULATOR_EN
	if (b_Regular_down_flag == HI_TRUE)
	{
		Venc_Regulator_Enable();
		b_Regular_down_flag = HI_FALSE;
		HI_INFO_VENC("hardware power on!!!\n");
	}
#endif

	VENC_HAL_DisableAllInt((S_HEVC_AVC_REGS_TYPE*)(VeduIpCtx.pRegBase));
	VENC_HAL_ClrAllInt	  ((S_HEVC_AVC_REGS_TYPE*)(VeduIpCtx.pRegBase));

#ifdef IRQ_EN
    VENC_DRV_OsalIrqFree(gVeduIrqNum);
#endif
	iounmap(VeduIpCtx.pRegBase);

	DRV_MEM_EXIT();

#ifdef SHUTDOWN_REGULATOR_EN
	if (b_Regular_down_flag == HI_FALSE)
	{
		Venc_Regulator_Disable();
		b_Regular_down_flag = HI_TRUE;
	}
#endif
    VENC_DRV_OsalLockDestroy( VeduIpCtx.pChnLock );

    memset((HI_VOID *)&VeduIpCtx, 0, sizeof(VeduIpCtx));

#ifdef MD5_WC_EN
	vfree(pMd5SrcY);
	vfree(pMd5SrcU);
	vfree(pMd5SrcV);
	vfree(pMd5SrcUV);

    for(i = 0;i<8;i++)
    {
        if(g_stVencChn[i].bhavecalc)
        {
            g_stVencChn[i].bhavecalc = 0;
            MD5CalcFinal (digesttmp, &(context[i]));
            HI_INFO_VENC("channel:%d  %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",i,digesttmp[0],digesttmp[1],digesttmp[2],digesttmp[3]
                ,digesttmp[4],digesttmp[5],digesttmp[6],digesttmp[7]
                ,digesttmp[8],digesttmp[9],digesttmp[10],digesttmp[11]
                ,digesttmp[12],digesttmp[13],digesttmp[14],digesttmp[15]);

            sprintf(digesttmp2,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", digesttmp[0],digesttmp[1],digesttmp[2],digesttmp[3]
                ,digesttmp[4],digesttmp[5],digesttmp[6],digesttmp[7]
                ,digesttmp[8],digesttmp[9],digesttmp[10],digesttmp[11]
                ,digesttmp[12],digesttmp[13],digesttmp[14],digesttmp[15]);

            if (digesttmp2 == NULL || fpmd5 == NULL)
            {
                HI_ERR_VENC("digesttmp2:%x fpmd5:%x strlen(digesttmp2):%d\n",digesttmp2,fpmd5,strlen(digesttmp2));
            }
            else
            {
                VENC_DRV_OsalFwrite((char *)digesttmp2,strlen(digesttmp2),fpmd5);
            }
        }
    }

    if (fpmd5 != NULL)
    {
        VENC_DRV_OsalFclose(fpmd5);
    }
#endif

	HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflSuspendVedu( HI_VOID )
{
	HI_INFO_VENC("enter %s()\n", __func__);
	VeduIpCtx.StopTask = 1;
    while (VeduIpCtx.TaskRunning)
    {
        msleep(1);
    }

    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Frame);
//    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Stream);

	VENC_HAL_DisableAllInt((S_HEVC_AVC_REGS_TYPE*)(VeduIpCtx.pRegBase));
	VENC_HAL_ClrAllInt	  ((S_HEVC_AVC_REGS_TYPE*)(VeduIpCtx.pRegBase));

	VENC_DRV_OsalIrqFree(gVeduIrqNum);
    iounmap(VeduIpCtx.pRegBase);

    //VENC_DRV_OsalLockDestroy( VeduIpCtx.pChnLock );
	HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : VENC_DRV_Resume
 Description  : VENC resume function
 Input        : None
 Output       : None
 Return Value : None
 Others       : Delete initialization of global value compared with VeduEfl_OpenVedu
*****************************************************************************/
HI_S32 VENC_DRV_EflResumeVedu(HI_VOID)
{
	HI_INFO_VENC("enter %s()\n", __func__);
	/* init IRQ */
    if (HI_FAILURE == VENC_DRV_OsalIrqInit(gVeduIrqNum, Venc_ISR))
    {
        HI_ERR_VENC("%s, VENC_DRV_OsalIrqInit failed\n", __func__);
		return HI_FAILURE;
    }

    VeduIpCtx.pRegBase = (HI_U32*)ioremap( gVencRegBaseAddr, gVencRegRange );

    /* creat thread to manage channel */
    VeduIpCtx.StopTask = 0;
    VENC_DRV_OsalCreateTask( &VeduIpCtx.pTask_Frame, "HI_VENC_FrameTask", VENC_DRV_EflTask );
    msleep(1);

    HI_INFO_VENC("out\n");
    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflQueryStatInfo( HI_HANDLE EncHandle, VeduEfl_StatInfo_S *pStatInfo )
{
    VeduEfl_EncPara_S  *pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    if ((pEncPara == NULL) || (pStatInfo == NULL))
    {
        HI_ERR_VENC("%s, params is invaild! pEncPara:0x%x , pStatInfo:0x%x \n", __func__, pEncPara,pStatInfo);
		return HI_FAILURE;
    }

    *pStatInfo = pEncPara->stStat;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflGetImage_OMX(HI_HANDLE EncHandle, venc_user_buf *pstFrame)
{
    HI_U32 u32ChnID = 0;
    HI_S32 s32Ret   = 0;
    VeduEfl_EncPara_S *pEncPara = NULL;
	queue_data_s  Queue_data;

    memset(&Queue_data, 0, sizeof(Queue_data));
	HI_DBG_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);

    D_VENC_GET_CHN(u32ChnID,EncHandle);
	D_VENC_CHECK_CHN(u32ChnID);
    pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    if( VENC_DRV_MngQueueEmpty(pEncPara->FrameQueue_OMX))
    {
	   HI_WARN_VENC("%s, frame queue is empty,EncHandle:0x%x\n", __func__, EncHandle);
       return HI_FAILURE;
    }

	s32Ret = VENC_DRV_MngDequeue(pEncPara->FrameQueue_OMX, &Queue_data);
    if(s32Ret)
    {
	   HI_ERR_VENC("%s, VENC_DRV_MngDequeue failed ret = %d\n", __func__, s32Ret);
       return s32Ret;
    }
	else
	{
	   memcpy((HI_VOID *)pstFrame,(HI_VOID *)&(Queue_data.msg_info_omx.buf),sizeof(venc_user_buf));
	}
    pEncPara->stStat.QueueNum--;

    //从队列中获取一帧图像，
	HI_DBG_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return HI_SUCCESS;
}

/* 获取码流buffer封装函数 */
HI_S32 VENC_DRV_EflGetStream_OMX(HI_HANDLE EncHandle, venc_user_buf *pstStream)
{
    HI_U32 u32ChnID = 0;
    HI_S32 s32Ret   = 0;
    VeduEfl_EncPara_S *pEncPara = NULL;
	queue_data_s  Queue_data;

    memset(&Queue_data, 0, sizeof(Queue_data));
	HI_DBG_VENC("enter %s, EncHandle:0x%x\n", __func__, EncHandle);

    D_VENC_GET_CHN(u32ChnID,EncHandle);
	D_VENC_CHECK_CHN(u32ChnID);
    pEncPara = (VeduEfl_EncPara_S *)EncHandle;

    if( VENC_DRV_MngQueueEmpty(pEncPara->StreamQueue_OMX))
    {
	   HI_WARN_VENC("%s, stream queue is empty,EncHandle:0x%x\n", __func__, EncHandle);
       return HI_FAILURE;
    }

	s32Ret = VENC_DRV_MngDequeue(pEncPara->StreamQueue_OMX, &Queue_data);
    if(s32Ret)
    {
	   HI_ERR_VENC("%s, VENC_DRV_MngDequeue failed, ret = %d\n", __func__, s32Ret);
       return s32Ret;
    }
	else
	{
	   HI_DBG_VENC("%s, pstStream:0x%x  &(Queue_data.msg_info_omx.buf: 0x%x\n", __func__, pstStream,&(Queue_data.msg_info_omx.buf));
	   memcpy((HI_VOID *)pstStream,(HI_VOID *)&(Queue_data.msg_info_omx.buf),sizeof(venc_user_buf));
	}
//    pEncPara->stStat.QueueNum--;
	pEncPara->stStat.StreamQueueNum--;

	HI_DBG_VENC("exit %s, EncHandle:0x%x\n", __func__, EncHandle);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_DbgWriteYUV420(HI_U8* pSY,HI_U8* pSU,HI_U8* pSV,HI_S32 width,HI_S32 height)
{
	struct file *fp = VENC_DRV_OsalFopen("/sdcard/rcn.yuv", O_RDWR | O_CREAT|O_APPEND, 0);

	VENC_DRV_OsalFwrite((HI_CHAR*)pSY,width*height, fp);
	VENC_DRV_OsalFwrite((HI_CHAR*)pSU,width*height/4, fp);
	VENC_DRV_OsalFwrite((HI_CHAR*)pSV,width*height/4, fp);
    VENC_DRV_OsalFclose(fp);

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_DbgWriteYUV(HI_DRV_VIDEO_FRAME_S *pstFrame,HI_CHAR* pFileName,HI_U64 uVirOffset)
{
    unsigned char *ptr;
    struct file *fp;
    char *pY,*pC;
    int i, j,k,m,n,s,t,p;
    char *pUV;
    int tilenumW,tilenumH,wResidual,hResidual,wResidual64,hResidual4,wResidual64else,wResidual64elsekb,hResidual4else;//wResidual16,
    int w = pstFrame->u32Width;
    int h = pstFrame->u32Height;
    int cstride ;

    ptr = (unsigned char *)((HI_U64)pstFrame->stBufAddr[0].pVirAddr_Y );
    if (!ptr)
    {
        HI_ERR_VENC("address is not valid!\n");
    }
    else
    {
        fp = VENC_DRV_OsalFopen("/sdcard/rcn.yuv", O_RDWR | O_CREAT|O_APPEND, 0);

        pY = (HI_S8 *)pstFrame->stBufAddr[0].pVirAddr_Y ;
        pC = (HI_S8 *)pstFrame->stBufAddr[0].pVirAddr_C;

        cstride = pstFrame->stBufAddr[0].u32Stride_C;

        tilenumW  = w / 256;
        tilenumH  = h / 16;
        wResidual  = w % 256;
        hResidual  = h % 16;
        wResidual64 = wResidual /64;
        wResidual64else   = wResidual % 64;
        //wResidual16   = wResidual % 16;//宽度若非16对齐则要扩边
        wResidual64elsekb  = (wResidual64else+15)/16*16 ;
        wResidual   =(wResidual+15)/16*16;
        w = (w+15)/16*16;
        hResidual4   = hResidual / 4;
        hResidual4else  = hResidual % 4;
        for(i = 0; i < tilenumH; i++) ////垂直方向tile个数
        {
            for( j = 0; j < 4; j++) ////tile内垂直方向64x4的个数
            {
                for(m = 0; m < 4; m++) /////64x4内列方向的像素点数
                {
                    for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                    {
                        for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                        {
                           //if(1 != fwrite(pY + i*16*w + j *4*256 + m * 64 + 256*16*n + k *64*4,64,1,fpYUV)){printf("error:write rcn0 y\n"); return;}
                            VENC_DRV_OsalFwrite(pY + i*16*w + j *4*256 + m * 64 + 256*16*n + k *64*4,64, fp);
                        }
                    }
                    for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                    {
                        VENC_DRV_OsalFwrite(pY + i*16*w + j *4*wResidual + m * 64  + tilenumW*256*16 + s*64*4,64, fp);
                        //if(1 != fwrite(pY + i*16*w + j *4*wResidual + m * 64  + tilenumW*256*16 + s*64*4 ,64,1,fpYUV)){printf("error:write rcn1 y\n"); return;}
                    }
                    if(wResidual64else)
                    {
                        VENC_DRV_OsalFwrite(pY + i*16*w + j *4*wResidual+ m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4,wResidual64else, fp);
                        //if(1 != fwrite(pY + i*16*w + j *4*wResidual+ m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4,wResidual64else,1,fpYUV)){printf("error:write rcn2 y\n"); return;}	///水平方向最后小于64整数倍的像素点数
                    }
                }
            }
        }
        for(p = 0;p < hResidual4;p++)//////垂直方向64x4的个数
        {
            for(m = 0; m < 4; m++) /////64x4内列方向的像素点数
            {
                for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                {
                    for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                    {
                        VENC_DRV_OsalFwrite(pY + tilenumH*16*w + p *4*256 + m * 64 + 256*16*n + k *64*4,64, fp);
                        //if(1 != fwrite(pY + tilenumH*16*w + p *4*256 + m * 64 + 256*16*n + k *64*4,64,1,fpYUV)){printf("error:write rcn3 y\n"); return;}
                    }
                }
                for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                {
                    VENC_DRV_OsalFwrite(pY + tilenumH*16*w + p *4*wResidual+ m * 64	+ tilenumW*256*16 + s*64*4 ,64, fp);
                    //if(1 != fwrite(pY + tilenumH*16*w + p *4*wResidual+ m * 64	+ tilenumW*256*16 + s*64*4 ,64,1,fpYUV)){printf("error:write rcn4 y\n"); return;}
                }
                if(wResidual64else)
                {
                    VENC_DRV_OsalFwrite(pY + tilenumH*16*w + p *4*wResidual + m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4,wResidual64else, fp);
                    //if(1 != fwrite(pY + tilenumH*16*w + p *4*wResidual + m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4,wResidual64else,1,fpYUV)){printf("error:write rcn5 y\n"); return;}	///水平方向最后小于64整数倍的像素点数
                }
            }
        }
        for(m = 0; m < hResidual4else; m++) /////最后不足四行行数
        {
            for(n = 0;n < tilenumW; n++)/////水平方向tile个数
            {
                for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                {
                    VENC_DRV_OsalFwrite(pY + tilenumH*16*w + hResidual4 *4*256 + m * 64 + 256*16*n + k *64*4,64, fp);
                    //if(1 != fwrite(pY + tilenumH*16*w + hResidual4 *4*256 + m * 64 + 256*16*n + k *64*4,64,1,fpYUV)){printf("error:write rcn3 y\n"); return;}
                }
            }
            for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
            {
                VENC_DRV_OsalFwrite(pY + tilenumH*16*w + hResidual4 *4*wResidual+ m * 64  + tilenumW*256*16 + s*64*4 ,64, fp);
                //if(1 != fwrite(pY + tilenumH*16*w + hResidual4 *4*wResidual+ m * 64  + tilenumW*256*16 + s*64*4 ,64,1,fpYUV)){printf("error:write rcn4 y\n"); return;}
            }
            if(wResidual64else)
            {
                VENC_DRV_OsalFwrite(pY + tilenumH*16*w + hResidual4 *4*wResidual + m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4,wResidual64else, fp);
                //if(1 != fwrite(pY + tilenumH*16*w + hResidual4 *4*wResidual + m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4,wResidual64else,1,fpYUV)){printf("error:write rcn5 y\n"); return;} ///水平方向最后小于64整数倍的像素点数
            }
        }

        ///////////////////////色度
        //vmalloc(pstFrame->u32Width * pstFrame->u32Height / 2 /2);
        //if( NULL == (pUV = (HI_U8 *)malloc(cstride)) )
        if( NULL == (pUV = (HI_S8 *)vmalloc(cstride)) )
        {
            HI_ERR_VENC("error: malloc @ write rcn yuv\n");
            return HI_FAILURE;
        }
        ///////////U
        for(i = 0; i < tilenumH; i++) ////垂直方向tile个数
        {
            for( j = 0; j < 4; j++) ////tile内垂直方向64x4的个数
            {
                for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
                {
                    for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                    {
                        for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                        {
                            for(t = 0;t < 32;t++)
                            {
                                *(pUV + t) = *(pC + i*8*w + j *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 0);
                            }
                            //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                            VENC_DRV_OsalFwrite(pUV, 32, fp);
                        }
                    }
                    for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                    {
                        for( t = 0;t < 32;t++)
                        {
                            *(pUV + t) = *(pC +  i*8*w + j *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2	+ t * 2 + 0);
                        }
                        //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                        VENC_DRV_OsalFwrite(pUV, 32, fp);
                    }
                    if(wResidual64else)
                    {
                        for(t = 0;t < wResidual64elsekb/2;t++)
                        {
                            *(pUV + t) = *(pC +  i*8*w + j *2*wResidual+ m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2	+ t * 2 + 0);
                        }
                        //if( 1 != fwrite(pUV,  wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点
                        VENC_DRV_OsalFwrite(pUV, wResidual64else/2, fp);
                       }
               }
            }
        }
        for(p = 0;p < hResidual4;p++)//////垂直方向64x4的个数
        {
            for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
            {
                for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                {
                    for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                    {
                        for(t = 0; t < 32;t++)
                        {
                            *(pUV + t) = *(pC + tilenumH*8*w + p *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 0);
                        }
                        //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                        VENC_DRV_OsalFwrite(pUV, 32, fp);
                    }
                }
                for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                {
                    for(t = 0; t < 32;t++)
                    {
                        *(pUV + t) = *(pC + tilenumH*8*w + p *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2 + t * 2 + 0);
                    }
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    VENC_DRV_OsalFwrite(pUV, 32, fp);
                }
                if(wResidual64else)
                {
                    for(t = 0;t< wResidual64elsekb/2;t++)
                    {
                        *(pUV + t) = *(pC + tilenumH*8*w + p *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 0);
                    }
                //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
                VENC_DRV_OsalFwrite(pUV, wResidual64else/2, fp);
                }
            }
        }
        for(m = 0; m < hResidual4else/2; m++) //////最后不足四行行数
        {
            for(n = 0;n < tilenumW; n++)/////水平方向tile个数
            {
                for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                {
                    for(t = 0; t < 32;t++)
                    {
                        *(pUV + t) = *(pC + tilenumH*8*w + hResidual4 *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 0);
                    }
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    VENC_DRV_OsalFwrite(pUV, 32, fp);
                }
            }
            for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
            {
                for(t = 0; t < 32;t++)
                {
                    *(pUV + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual+ m * 64	+ tilenumW*256*8 + s*64*2 + t * 2 + 0);
                }
                //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                VENC_DRV_OsalFwrite(pUV, 32, fp);
            }
            if(wResidual64else)
            {
                for(t = 0;t< wResidual64elsekb/2;t++)
                {
                    *(pUV + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 0);
                }
                //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
                VENC_DRV_OsalFwrite(pUV, wResidual64else/2, fp);
            }
        }

        //V
        for(i = 0; i < tilenumH; i++) ////垂直方向tile个数
        {
            for( j = 0; j < 4; j++) ////tile内垂直方向64x4的个数
            {
                for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
                {
                    for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                    {
                        for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                        {
                            for(t = 0;t < 32;t++)
                            {
                                *(pUV + t) = *(pC + i*8*w + j *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 1);
                            }
                            VENC_DRV_OsalFwrite(pUV, 32, fp);
                            //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                        }
                    }
                    for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                    {
                        for( t = 0;t < 32;t++)
                        {
                           *(pUV + t) = *(pC +  i*8*w + j *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2 + t * 2 + 1);
                        }
                        VENC_DRV_OsalFwrite(pUV, 32, fp);
                        //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    }
                    if(wResidual64else)
                    {
                        for(t = 0;t < wResidual64elsekb/2;t++)
                        {
                            *(pUV + t) = *(pC +  i*8*w + j *2*wResidual+ m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2	+ t * 2 + 1);
                        }
                        //if( 1 != fwrite(pUV,  wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点
                        VENC_DRV_OsalFwrite(pUV, wResidual64else/2, fp);
                    }
                }
            }
        }
        for(p = 0;p < hResidual4;p++)//////垂直方向64x4的个数
        {
            for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
            {
                for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                {
                    for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                    {
                        for(t = 0; t < 32;t++)
                        {
                            *(pUV + t) = *(pC + tilenumH*8*w + p *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 1);
                        }
                        VENC_DRV_OsalFwrite(pUV, 32, fp);
                        //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    }
                }
                for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                {
                    for(t = 0; t < 32;t++)
                    {
                        *(pUV + t) = *(pC + tilenumH*8*w + p *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2 + t * 2 + 1);
                    }
                    VENC_DRV_OsalFwrite(pUV, 32, fp);
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                }
                if(wResidual64else)
                {
                    for(t = 0;t< wResidual64elsekb/2;t++)
                    {
                        *(pUV + t) = *(pC + tilenumH*8*w + p *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 1);
                    }
                    VENC_DRV_OsalFwrite(pUV, wResidual64else/2, fp);
                    //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
                }
            }
        }
        for(m = 0; m < hResidual4else/2; m++) //////最后不足四行行数
        {
            for(n = 0;n < tilenumW; n++)/////水平方向tile个数
            {
                for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                {
                    for(t = 0; t < 32;t++)
                    {
                        *(pUV + t) = *(pC + tilenumH*8*w + hResidual4 *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 1);
                    }
                    VENC_DRV_OsalFwrite(pUV, 32, fp);
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                }
            }
            for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
            {
                for(t = 0; t < 32;t++)
                {
                    *(pUV + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual+ m * 64	+ tilenumW*256*8 + s*64*2 + t * 2 + 1);
                }
                VENC_DRV_OsalFwrite(pUV, 32, fp);
                //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
            }
            if(wResidual64else)
            {
                for(t = 0;t< wResidual64elsekb/2;t++)
                {
                    *(pUV + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 1);
                }
                VENC_DRV_OsalFwrite(pUV, wResidual64else/2, fp);
                //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
            }
        }
        if(pUV)
        {
            vfree((HI_VOID *)pUV);
            pUV = NULL;
        }

        VENC_DRV_OsalFclose(fp);
        HI_INFO_VENC("2d image has been saved  W=%d H=%d Format=%d \n",
                    pstFrame->u32Width,pstFrame->u32Height,pstFrame->ePixFormat);

	}

    return HI_SUCCESS;
}


#ifdef MD5_WC_EN
HI_VOID VENC_DRV_MD5_CALC(VeduEfl_EncPara_S * pEncPara,HI_U32 chanlnum)
{
	HI_DRV_VIDEO_FRAME_S stFrame;
	HI_U32 i     = 0;
	HI_U8* pSrcY = NULL;
	HI_U8* pSrcU = NULL;
	HI_U8* pSrcV = NULL;

    memset(&stFrame, 0, sizeof(stFrame));
	stFrame.stBufAddr[0].u32Stride_Y = pEncPara->vcpi_imgwidth_pix;
	stFrame.stBufAddr[0].u32Stride_C = pEncPara->vcpi_imgwidth_pix/2;

	if(pEncPara->pstCfg_EncPara->vcpi_rec_cmp_en )
	{
		HI_INFO_VENC("**** compress mode ***** \n");
		VENC_DRV_DpressRcn( (HI_HANDLE) pEncPara );
		pSrcY = pMd5SrcY;
		pSrcU = pMd5SrcU;
		pSrcV = pMd5SrcV;
		if (g_stVencChn[chanlnum].stProcWrite.bSaveYUVFileRun )
		{
			VENC_DRV_DbgWriteYUV420(pMd5SrcY, pMd5SrcU,pMd5SrcV,pEncPara->vcpi_imgwidth_pix,pEncPara->vcpi_imgheight_pix);
		}
	}
	else
	{
		HI_INFO_VENC("**** Non compress mode ***** \n");
		stFrame.u32Height = pEncPara->vcpi_imgheight_pix;
		stFrame.u32Width =  pEncPara->vcpi_imgwidth_pix;
		stFrame.stBufAddr[0].u32PhyAddr_Y = pEncPara->RcnYAddr[pEncPara->RcnIdx] ;
		stFrame.stBufAddr[0].u32PhyAddr_C = pEncPara->RcnCAddr[pEncPara->RcnIdx] ;
		stFrame.ePixFormat = HI_DRV_PIX_FMT_NV21;

		//stFrame.stBufAddr[0].u32Stride_Y = (pEncPara->vcpi_imgwidth_pix + 15)/16*16;
		//stFrame.stBufAddr[0].u32Stride_C = (pEncPara->vcpi_imgwidth_pix + 15)/16*16;

		stFrame.stBufAddr[0].pVirAddr_Y = pEncPara->VirRcnYAddr[pEncPara->RcnIdx] ;
		stFrame.stBufAddr[0].pVirAddr_C= pEncPara->VirRcnCAddr[pEncPara->RcnIdx] ;

		if(HI_SUCCESS != VENC_DRV_RYUV_MD5(&stFrame))
		{
			HI_INFO_VENC("**** Non compress mode calc Md5 failed ***** \n");
		}

		pSrcY = pMd5SrcY;
		pSrcU = pMd5SrcU;
		pSrcV = pMd5SrcV;

	}

	g_stVencChn[chanlnum].bhavecalc = 1;

	for (i = 0; i < pEncPara->vcpi_imgheight_pix; i++)
	{
		MD5CalcUpdate(&(context[chanlnum]), pSrcY+i*stFrame.stBufAddr[0].u32Stride_Y, pEncPara->vcpi_imgwidth_pix);
	}

	for (i = 0; i < pEncPara->vcpi_imgheight_pix>>1; i++)
	{
		MD5CalcUpdate(&(context[chanlnum]), pSrcU+i*stFrame.stBufAddr[0].u32Stride_C, pEncPara->vcpi_imgwidth_pix>>1);
	}

	for (i = 0; i < pEncPara->vcpi_imgheight_pix>>1; i++)
	{
		MD5CalcUpdate(&(context[chanlnum]), pSrcV+i*stFrame.stBufAddr[0].u32Stride_C, pEncPara->vcpi_imgwidth_pix>>1);
	}
	HI_DBG_VENC("md5 out\n");
	return;
}

HI_S32 VENC_DRV_RYUV_MD5(HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_U8 *pY = (unsigned char *)((HI_U64)pstFrame->stBufAddr[0].pVirAddr_Y );
    HI_U8 *pC = (unsigned char *)((HI_U64)pstFrame->stBufAddr[0].pVirAddr_C);
    HI_U8 *pDstY = pMd5SrcY;
    HI_U8 *pDstU = pMd5SrcU;
    HI_U8 *pDstV = pMd5SrcV;
    int w = pstFrame->u32Width;
    int h = pstFrame->u32Height;

    int i, j,k,m,n,s,t,p;
    int tilenumW,tilenumH,wResidual,hResidual,wResidual64,hResidual4,wResidual64else,wResidual64elsekb,hResidual4else;//wResidual16

    tilenumW			   = w / 256;
    tilenumH			   = h / 16;
    wResidual			   = w % 256;
    hResidual			   = h % 16;
    wResidual64 		   = wResidual /64;
    wResidual64else 	   = wResidual % 64;
    //wResidual16 		   = wResidual % 16;//宽度若非16对齐则要扩边
    wResidual64elsekb	   = (wResidual64else+15)/16*16 ;
    wResidual			   =(wResidual+15)/16*16;
    w = (w+15)/16*16;
    hResidual4			   = hResidual / 4;
    hResidual4else		   = hResidual % 4;
    for(i = 0; i < tilenumH; i++) ////垂直方向tile个数
    {
        for( j = 0; j < 4; j++) ////tile内垂直方向64x4的个数
        {
            for(m = 0; m < 4; m++) /////64x4内列方向的像素点数
            {
                for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                {
                    for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                    {
                        memcpy(pDstY ,(pY + i*16*w + j *4*256 + m * 64 + 256*16*n + k *64*4),64);
                        pDstY+=64;
                    }
                }
                for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                {
                    memcpy(pDstY ,(pY + i*16*w + j *4*wResidual + m * 64  + tilenumW*256*16 + s*64*4),64);
                    pDstY+=64;
                }
                if(wResidual64else)
                {

                    memcpy(pDstY ,(pY + i*16*w + j *4*wResidual+ m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4),wResidual64else);
                    pDstY+=wResidual64else;
                }
            }
        }
    }
    for(p = 0;p < hResidual4;p++)//////垂直方向64x4的个数
    {
        for(m = 0; m < 4; m++) /////64x4内列方向的像素点数
        {
            for(n = 0;n < tilenumW; n++)/////水平方向tile个数
            {
                for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                {
                    memcpy(pDstY ,(pY + tilenumH*16*w + p *4*256 + m * 64 + 256*16*n + k *64*4),64);
                    pDstY+=64;
                }
            }
            for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
            {
                memcpy(pDstY ,(pY + tilenumH*16*w + p *4*wResidual+ m * 64	+ tilenumW*256*16 + s*64*4) ,64);
                pDstY+=64;
            }
            if(wResidual64else)
            {
                memcpy(pDstY ,(pY + tilenumH*16*w + p *4*wResidual + m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4),wResidual64else);
                pDstY+=wResidual64else;
            }
        }
    }
    for(m = 0; m < hResidual4else; m++) /////最后不足四行行数
    {
        for(n = 0;n < tilenumW; n++)/////水平方向tile个数
        {
            for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
            {
                memcpy(pDstY ,(pY + tilenumH*16*w + hResidual4 *4*256 + m * 64 + 256*16*n + k *64*4),64);
                pDstY+=64;
            }
        }
        for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
        {
            memcpy(pDstY ,(pY + tilenumH*16*w + hResidual4 *4*wResidual+ m * 64  + tilenumW*256*16 + s*64*4) ,64);
            pDstY+=64;
        }
        if(wResidual64else)
        {
            memcpy(pDstY ,(pY + tilenumH*16*w + hResidual4 *4*wResidual + m * wResidual64elsekb + tilenumW*256*16 + wResidual64*64*4),wResidual64else);
            pDstY+=wResidual64else;
        }
    }

	///////////////////////色度
	///////////U
    for(i = 0; i < tilenumH; i++) ////垂直方向tile个数
    {
        for( j = 0; j < 4; j++) ////tile内垂直方向64x4的个数
        {
            for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
            {
                for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                {
                    for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                    {
                        for(t = 0;t < 32;t++)
                        {
                            *(pDstU + t) = *(pC + i*8*w + j *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 0);
                        }
                        pDstU+=32;
                    }

                }
                for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                {
                    for( t = 0;t < 32;t++)
                    {

                        *(pDstU + t) = *(pC +  i*8*w + j *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2	+ t * 2 + 0);

                    }
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    pDstU+=32;
                }
                if(wResidual64else)
                {
                    for(t = 0;t < wResidual64elsekb/2;t++)
                    {

                        *(pDstU + t) = *(pC +  i*8*w + j *2*wResidual+ m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2	+ t * 2 + 0);

                    }
                    //if( 1 != fwrite(pUV,  wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点
                    pDstU+=wResidual64else/2;
                }
            }
        }
    }

    for(p = 0;p < hResidual4;p++)//////垂直方向64x4的个数
    {
        for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
        {
            for(n = 0;n < tilenumW; n++)/////水平方向tile个数
            {
                for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                {
                    for(t = 0; t < 32;t++)
                    {
                    *(pDstU + t) = *(pC + tilenumH*8*w + p *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 0);
                    }
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    pDstU+=32;
                }
            }
            for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
            {
                for(t = 0; t < 32;t++)
                {
                    *(pDstU + t) = *(pC + tilenumH*8*w + p *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2 + t * 2 + 0);
                }
                //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                pDstU+=32;
            }
            if(wResidual64else)
            {
                for(t = 0;t< wResidual64elsekb/2;t++)
                {
                    *(pDstU + t) = *(pC + tilenumH*8*w + p *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 0);
                }
                //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
                pDstU+=wResidual64else/2;
            }
        }
    }
    for(m = 0; m < hResidual4else/2; m++) //////最后不足四行行数
    {
        for(n = 0;n < tilenumW; n++)/////水平方向tile个数
        {
            for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
            {
                for(t = 0; t < 32;t++)
                {
                 *(pDstU + t) = *(pC + tilenumH*8*w + hResidual4 *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 0);
                }
                //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                pDstU+=32;
            }
        }
        for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
        {
            for(t = 0; t < 32;t++)
            {
                *(pDstU + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual+ m * 64	+ tilenumW*256*8 + s*64*2 + t * 2 + 0);

            }
            //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
            pDstU+=32;
        }
        if(wResidual64else)
        {
            for(t = 0;t< wResidual64elsekb/2;t++)
            {
                *(pDstU + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 0);
            }
            //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
            pDstU+=wResidual64else/2;
        }
    }

		//V
    for(i = 0; i < tilenumH; i++) ////垂直方向tile个数
    {
        for( j = 0; j < 4; j++) ////tile内垂直方向64x4的个数
        {
            for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
            {
                for(n = 0;n < tilenumW; n++)/////水平方向tile个数
                {
                    for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                    {
                        for(t = 0;t < 32;t++)
                        {
                            *(pDstV + t) = *(pC + i*8*w + j *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 1);
                        }
                        pDstV+=32;
                        //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                    }

                }
                for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
                {
                    for( t = 0;t < 32;t++)
                    {

                        *(pDstV + t) = *(pC +  i*8*w + j *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2	+ t * 2 + 1);

                    }
                    pDstV+=32;
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                }
                if(wResidual64else)
                {
                    for(t = 0;t < wResidual64elsekb/2;t++)
                    {

                        *(pDstV + t) = *(pC +  i*8*w + j *2*wResidual+ m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2	+ t * 2 + 1);

                    }
                    //if( 1 != fwrite(pUV,  wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点
                    pDstV+=wResidual64else/2;
                }
            }
        }
    }

    for(p = 0;p < hResidual4;p++)//////垂直方向64x4的个数
    {
        for(m = 0; m < 2; m++) /////64x4内列方向的像素点数
        {
            for(n = 0;n < tilenumW; n++)/////水平方向tile个数
            {
                for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
                {
                    for(t = 0; t < 32;t++)
                    {
                     *(pDstV + t) = *(pC + tilenumH*8*w + p *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 1);
                    }
                    pDstV+=32;
                    //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
                }
            }
            for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
            {
                for(t = 0; t < 32;t++)
                {
                    *(pDstV + t) = *(pC + tilenumH*8*w + p *2*wResidual+ m * 64  + tilenumW*256*8 + s*64*2 + t * 2 + 1);
                }
                pDstV+=32;
                //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
            }
            if(wResidual64else)
            {
                for(t = 0;t< wResidual64elsekb/2;t++)
                {
                    *(pDstV + t) = *(pC + tilenumH*8*w + p *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 1);
                }
                pDstV+=wResidual64else/2;
                //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
            }
        }
    }
    for(m = 0; m < hResidual4else/2; m++) //////最后不足四行行数
    {
        for(n = 0;n < tilenumW; n++)/////水平方向tile个数
        {
            for(k = 0; k < 4;k++)/////水平方向tile内64x4的个数
            {
                for(t = 0; t < 32;t++)
                {
                    *(pDstV + t) = *(pC + tilenumH*8*w + hResidual4 *4*128 + m * 64 + 256*8*n + k *64*2 + t * 2 + 1);
                }
                pDstV+=32;
                //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
            }
        }
        for(s = 0; s < wResidual64 ;s++)//////对非整数tile后面的按64取整做
        {
            for(t = 0; t < 32;t++)
            {
                *(pDstV + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual+ m * 64	+ tilenumW*256*8 + s*64*2 + t * 2 + 1);
            }
            pDstV+=32;
            //if( 1 != fwrite(pUV, 32, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}
        }
        if(wResidual64else)
        {
            for(t = 0;t< wResidual64elsekb/2;t++)
            {
                *(pDstV + t) = *(pC + tilenumH*8*w + hResidual4 *2*wResidual + m * wResidual64elsekb + tilenumW*256*8 + wResidual64*64*2 + t * 2 + 1);
            }
            pDstV+=wResidual64else/2;
            //if( 1 != fwrite(pUV, wResidual64else/2, 1, fpYUV) ) {printf("error:write rcn u\n"); return;}	///水平方向最后小于64整数倍的像素点数
        }
    }
    return HI_SUCCESS;
}


#ifndef __BIG_ENDIAN__
# define byteReverse(buf, length)    /* Nothing */
#else

void byteReverse(HI_U32 *buf, unsigned length)
{
  HI_U32 t;
  do {
    char* byte = (char *) buf;
    t = ((unsigned) byte[3] << 8 | byte[2]) << 16 |
        ((unsigned) byte[1] << 8 | byte[0]);
    *buf = t;
    buf++;
  } while (--length);
}
#endif


void MD5CalcInit(MD5Context *md5ctx)
{
  md5ctx->buf[0] = 0x67452301;
  md5ctx->buf[1] = 0xefcdab89;
  md5ctx->buf[2] = 0x98badcfe;
  md5ctx->buf[3] = 0x10325476;

  md5ctx->bits[0] = 0;
  md5ctx->bits[1] = 0;
}


void MD5CalcUpdate(MD5Context *md5ctx, HI_U8 *buf, unsigned length)
{
  HI_U32 t;

  /* Update bitcount */
  t = md5ctx->bits[0];
  if ((md5ctx->bits[0] = t + ((HI_U32) length << 3)) < t)
    md5ctx->bits[1]++;
  md5ctx->bits[1] += length >> 29;

  t = (t >> 3) & 0x3f;

  if (t) {
    HI_U8 *p = md5ctx->in.b8 + t;

    t = 64 - t;
    if (length < t) {
      memcpy(p, buf, length);
      return;
    }
    memcpy(p,buf, t);
    byteReverse(md5ctx->in.b32, 16);
    MD5CalcTransform(md5ctx->buf, md5ctx->in.b32);
    buf += t;
    length -= t;
  }

  while (length >= 64) {
    memcpy(md5ctx->in.b8,buf, 64);
    byteReverse(md5ctx->in.b32, 16);
    MD5CalcTransform(md5ctx->buf, md5ctx->in.b32);
    buf += 64;
    length -= 64;
  }

  memcpy(md5ctx->in.b8, buf, length);
}

void MD5CalcFinal(HI_U8 digest[16], MD5Context *md5ctx)
{
  unsigned count;
  HI_U8 *p;

  count = (md5ctx->bits[0] >> 3) & 0x3F;

  p = md5ctx->in.b8 + count;
  *p++ = 0x80;

  count = 64 - 1 - count;

  if (count < 8) {
    memset((void*)p, 0, count);
    byteReverse(md5ctx->in.b32, 16);
    MD5CalcTransform(md5ctx->buf, md5ctx->in.b32);

    memset((void*)md5ctx->in.b8, 0, 56);
  } else {
    memset((void*)p, 0, count - 8);
  }
  byteReverse(md5ctx->in.b32, 14);

  md5ctx->in.b32[14] = md5ctx->bits[0];
  md5ctx->in.b32[15] = md5ctx->bits[1];

  MD5CalcTransform(md5ctx->buf, md5ctx->in.b32);
  byteReverse((HI_U32 *) md5ctx->buf, 4);
  memcpy((void*)digest, md5ctx->buf, 16);

  memset((void*)md5ctx, 0, sizeof(* md5ctx));
}

#define M1(x, y, z) (z ^ (x & (y ^ z)))
#define M2(x, y, z) M1(z, x, y)
#define M3(x, y, z) (x ^ y ^ z)
#define M4(x, y, z) (y ^ (x | ~z))
#define MD5CALCSTEP(f, w, x, y, z, data, s) \
    ( w = (w + (f(x, y, z) + (data))),  w = ((w<<s) | (w>>(32-s))),  w = (w + x) )


void MD5CalcTransform(HI_U32 buf[4], HI_U32 const in[16])
{
  register HI_U32 a, b, c, d;

  a = buf[0];
  b = buf[1];
  c = buf[2];
  d = buf[3];

  MD5CALCSTEP(M1, a, b, c, d, in[0] + 0xd76aa478, 7);
  MD5CALCSTEP(M1, d, a, b, c, in[1] + 0xe8c7b756, 12);
  MD5CALCSTEP(M1, c, d, a, b, in[2] + 0x242070db, 17);
  MD5CALCSTEP(M1, b, c, d, a, in[3] + 0xc1bdceee, 22);
  MD5CALCSTEP(M1, a, b, c, d, in[4] + 0xf57c0faf, 7);
  MD5CALCSTEP(M1, d, a, b, c, in[5] + 0x4787c62a, 12);
  MD5CALCSTEP(M1, c, d, a, b, in[6] + 0xa8304613, 17);
  MD5CALCSTEP(M1, b, c, d, a, in[7] + 0xfd469501, 22);
  MD5CALCSTEP(M1, a, b, c, d, in[8] + 0x698098d8, 7);
  MD5CALCSTEP(M1, d, a, b, c, in[9] + 0x8b44f7af, 12);
  MD5CALCSTEP(M1, c, d, a, b, in[10] + 0xffff5bb1, 17);
  MD5CALCSTEP(M1, b, c, d, a, in[11] + 0x895cd7be, 22);
  MD5CALCSTEP(M1, a, b, c, d, in[12] + 0x6b901122, 7);
  MD5CALCSTEP(M1, d, a, b, c, in[13] + 0xfd987193, 12);
  MD5CALCSTEP(M1, c, d, a, b, in[14] + 0xa679438e, 17);
  MD5CALCSTEP(M1, b, c, d, a, in[15] + 0x49b40821, 22);

  MD5CALCSTEP(M2, a, b, c, d, in[1] + 0xf61e2562, 5);
  MD5CALCSTEP(M2, d, a, b, c, in[6] + 0xc040b340, 9);
  MD5CALCSTEP(M2, c, d, a, b, in[11] + 0x265e5a51, 14);
  MD5CALCSTEP(M2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
  MD5CALCSTEP(M2, a, b, c, d, in[5] + 0xd62f105d, 5);
  MD5CALCSTEP(M2, d, a, b, c, in[10] + 0x02441453, 9);
  MD5CALCSTEP(M2, c, d, a, b, in[15] + 0xd8a1e681, 14);
  MD5CALCSTEP(M2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
  MD5CALCSTEP(M2, a, b, c, d, in[9] + 0x21e1cde6, 5);
  MD5CALCSTEP(M2, d, a, b, c, in[14] + 0xc33707d6, 9);
  MD5CALCSTEP(M2, c, d, a, b, in[3] + 0xf4d50d87, 14);
  MD5CALCSTEP(M2, b, c, d, a, in[8] + 0x455a14ed, 20);
  MD5CALCSTEP(M2, a, b, c, d, in[13] + 0xa9e3e905, 5);
  MD5CALCSTEP(M2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
  MD5CALCSTEP(M2, c, d, a, b, in[7] + 0x676f02d9, 14);
  MD5CALCSTEP(M2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

  MD5CALCSTEP(M3, a, b, c, d, in[5] + 0xfffa3942, 4);
  MD5CALCSTEP(M3, d, a, b, c, in[8] + 0x8771f681, 11);
  MD5CALCSTEP(M3, c, d, a, b, in[11] + 0x6d9d6122, 16);
  MD5CALCSTEP(M3, b, c, d, a, in[14] + 0xfde5380c, 23);
  MD5CALCSTEP(M3, a, b, c, d, in[1] + 0xa4beea44, 4);
  MD5CALCSTEP(M3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
  MD5CALCSTEP(M3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
  MD5CALCSTEP(M3, b, c, d, a, in[10] + 0xbebfbc70, 23);
  MD5CALCSTEP(M3, a, b, c, d, in[13] + 0x289b7ec6, 4);
  MD5CALCSTEP(M3, d, a, b, c, in[0] + 0xeaa127fa, 11);
  MD5CALCSTEP(M3, c, d, a, b, in[3] + 0xd4ef3085, 16);
  MD5CALCSTEP(M3, b, c, d, a, in[6] + 0x04881d05, 23);
  MD5CALCSTEP(M3, a, b, c, d, in[9] + 0xd9d4d039, 4);
  MD5CALCSTEP(M3, d, a, b, c, in[12] + 0xe6db99e5, 11);
  MD5CALCSTEP(M3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
  MD5CALCSTEP(M3, b, c, d, a, in[2] + 0xc4ac5665, 23);

  MD5CALCSTEP(M4, a, b, c, d, in[0] + 0xf4292244, 6);
  MD5CALCSTEP(M4, d, a, b, c, in[7] + 0x432aff97, 10);
  MD5CALCSTEP(M4, c, d, a, b, in[14] + 0xab9423a7, 15);
  MD5CALCSTEP(M4, b, c, d, a, in[5] + 0xfc93a039, 21);
  MD5CALCSTEP(M4, a, b, c, d, in[12] + 0x655b59c3, 6);
  MD5CALCSTEP(M4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
  MD5CALCSTEP(M4, c, d, a, b, in[10] + 0xffeff47d, 15);
  MD5CALCSTEP(M4, b, c, d, a, in[1] + 0x85845dd1, 21);
  MD5CALCSTEP(M4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
  MD5CALCSTEP(M4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
  MD5CALCSTEP(M4, c, d, a, b, in[6] + 0xa3014314, 15);
  MD5CALCSTEP(M4, b, c, d, a, in[13] + 0x4e0811a1, 21);
  MD5CALCSTEP(M4, a, b, c, d, in[4] + 0xf7537e82, 6);
  MD5CALCSTEP(M4, d, a, b, c, in[11] + 0xbd3af235, 10);
  MD5CALCSTEP(M4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
  MD5CALCSTEP(M4, b, c, d, a, in[9] + 0xeb86d391, 21);

  buf[0] += a;
  buf[1] += b;
  buf[2] += c;
  buf[3] += d;
}

HI_U32 stream_begin[64];
HI_S32 stream_offset;

void Venc_BsInit(HI_U8 *pStream)
{
    int i;

    stream_offset = 0;

    for(i = 0; i < 64; i++)
    {
        stream_begin[i] = (pStream[i*4+0]<<24) + (pStream[i*4+1]<<16) + (pStream[i*4+2]<<8) + pStream[i*4+3];
    }
}

HI_U32 Venc_BsGet(int bits)
{
    HI_U32 code;

    code = ( stream_begin[(stream_offset>>5)  ] << (stream_offset&31)) |
           ((stream_begin[(stream_offset>>5)+1] >> (31-(stream_offset&31))) >> 1);
    stream_offset += bits;

    return (code >> (32 - bits));
}

void ref_Golomb_Rice_decoder(int k, int diff_num, HI_U8 *p0, HI_U8 *pLast)
{
    int i, m;
    int binary_len, unary_len0, mod_diff0, diff0;
    int Rice_map_diff[16];

    binary_len = k;

    for(m = 1, i = 0; i < k; i++)
    {
        m <<= 1;
    }

    for(i = 0; i < diff_num; i++)
    {
        unary_len0 = 0;

        if(0 == binary_len) mod_diff0 = 0;
        else                mod_diff0 = Venc_BsGet(binary_len);

        while( Venc_BsGet(1) != 1)
        {
            unary_len0++;
        }

        Rice_map_diff[i] = m * unary_len0 + mod_diff0;

        if(Rice_map_diff[i] % 2 ==0)
        {
            diff0 = Rice_map_diff[i] / 2;
        }
        else
        {
            diff0 = -((Rice_map_diff[i] + 1) / 2);
        }

        *p0 = (HI_U8)(*pLast + diff0);
        pLast = p0;
        p0++;
    }
}

void ref_decompress_sgmt(HI_U8 *pStream, int SegHead, HI_U8 *p0, int numDat)
{
    int i, j, eSgmtType, k_value, diff_num;//length,
    HI_U8 *pLast = p0;
    //#define ASSERT(n)      if(!(n)){HI_ERR_VENC("%s\n",);getchar();}
    Venc_BsInit(pStream);

    //length = ((SegHead & 15) + 1 ) * 16;
    eSgmtType = (SegHead >> 4) & 7;

    if(0 == eSgmtType)
    {
        for(i = 0; i < numDat; i++)
        {
            *p0++ = (HI_U8)Venc_BsGet(8);
        }
    }
    else
    {
        for(j = 0; j < numDat / 16; j++)
        {
            k_value = Venc_BsGet(3);

            if(7 == k_value)
            {
                for(i = 0; i < 16; i++)
                {
                    pLast = p0;
                    *p0++ = (HI_U8)Venc_BsGet(8);
                }
            }
            else
            {
                if(0 == j)
                {
                    pLast = p0;
                    *p0++ = (HI_U8)Venc_BsGet(8);
                }

                if(0 == j)
                    diff_num = 15;
                else
                    diff_num = 16;

                ref_Golomb_Rice_decoder(k_value, diff_num, p0, pLast);
                pLast = p0 + (diff_num - 1);
                p0 += diff_num;
            }
        }
    }
    //ASSERT(((stream_offset+7)/8 + 15)/16*16 == length);
    return;
    //return length;
}
void ref_decompress_chroma(int imgWidth, int imgHeight, HI_U8 *pData, HI_U8 *pHead, HI_U8 *pFrame0)
{
    HI_U8 *pStream = pData, pix[256], *p0;
    int mbx, mby, hh,ww, temp,lcux, lcuy, h_stride;//sgmt_num = 0,
     int i, j, SgmtHead;

    for(mby = 0; mby < imgHeight / 16; mby++)
    {
        for(mbx = 0; mbx < (imgWidth + 255) / 256; mbx++)
        {
            for(hh = 0; hh < 4; hh++)
            {
                for(ww = 0; ww < 4; ww ++)
                {
                    if(mbx*256 + 256 > imgWidth && ww > imgWidth % 256 / 64 - 1)
                    {
                        pStream += (ww == 0 ? 0 : (4 -ww)*128);
                        break;
                    }
                    lcux = (mbx * 256 + ww * 64) / 64;
                    lcuy = (mby *  16 + hh *  4) / 64;
                    h_stride = (imgWidth+63)/64*32;
                    temp = ((mby *  16 + hh *  4) % 64 / 4);
                    SgmtHead = *(pHead + lcuy * h_stride + lcux * 32 + (temp >= 14 ? temp + 16 : temp));
                    ref_decompress_sgmt(pStream, SgmtHead, pix, 128);
                    pStream += 128;
                    for(j = 0; j < 2; j++)
                    {
                        p0 = pFrame0 + (j + hh * 2 + mby * 8) * imgWidth;
                        for(i = 0; i < 64; i++)
                        {
                            if(1 == (i & 1))
                                *(p0 + mbx * 256 + ww * 64 + i) = pix[i/2 + j * 32];
                            else
                                *(p0 + mbx * 256 + ww * 64 + i) = pix[i/2 + j * 32 + 64];
                        }
                    }
                }
            }
        }
    }
    return;
    //return pStream - pData;
}

void ref_decompress(int imgWidth, int imgHeight, HI_U8 *pData, HI_U8 *pHead, HI_U8 *pFrame0)
{
    HI_U8 *pStream = pData, pix[256], *p0;
    int mbx, mby, hh, ww, lcux, lcuy, h_stride,temp;// sgmt_num = 0,
    int i, j, SgmtHead;
    if( 0 != (imgWidth & 0x3F) || 0 != (imgHeight & 0xF) )
    {
        HI_ERR_VENC("ref_decompress, img size not 16-aligned\n");
        return ;
    }

    for(mby = 0; mby < imgHeight / 16; mby++)
    {
        for(mbx = 0; mbx < (imgWidth + 255) / 256; mbx++)
        {
            for(hh = 0; hh < 4; hh++)
            {
                for(ww = 0; ww < 4; ww ++)
                {
                    if(mbx*256 + 256 > imgWidth && ww > imgWidth % 256 / 64 - 1)
                    {
                        pStream += (ww == 0 ? 0 : (4 -ww)*256);
                        break;
                    }
                    lcux = (mbx * 256 + ww * 64) / 64;
                    lcuy = (mby *  16 + hh *  4) / 64;
                    h_stride = (imgWidth+63)/64*32;
                    temp = ((mby *  16 + hh *  4) % 64 / 4);
                    SgmtHead = *(pHead + lcuy * h_stride + lcux * 32 + (temp == 15 ? 31 : temp));
                    ref_decompress_sgmt(pStream, SgmtHead, pix, 256);
                    pStream += 256;
                    for(j = 0; j < 4; j++)
                    {
                       p0 = pFrame0 + (j + hh * 4 + mby * 16) * imgWidth;
                       for(i = 0; i < 64; i++)
                       {
                          *(p0 + mbx * 256 + ww * 64 + i) = pix[i + j * 64];
                       }
                    }
                }
            }
        }
    }
    return;
    //return pStream - pData;
}

void ref_decompress_chroma_H264(int imgWidth, int imgHeight, HI_U8 *pData, HI_U8 *pHead, HI_U8 *pFrame0)
{
    HI_U8 *pStream = pData, pix[256], *p0;
    int mbx, mby, hh,ww, h_stride;// sgmt_num = 0,
     int i, j, SgmtHead;

    for(mby = 0; mby < imgHeight / 16; mby++)
    {
        for(mbx = 0; mbx < (imgWidth + 255) / 256; mbx++)
        {
            for(hh = 0; hh < 4; hh++)
            {
                for(ww = 0; ww < 4; ww ++)
                {
                    if(mbx*256 + 256 > imgWidth && ww > imgWidth % 256 / 64 - 1)
                    {
                        pStream += (ww == 0 ? 0 : (4 -ww)*128);
                        break;
                    }

                    h_stride = (imgWidth+255)/256*32;
                    SgmtHead = *(pHead + mby * h_stride + mbx * 32 + (hh >= 2 ? 16 : 0 ) + hh*4 + ww);
                    ref_decompress_sgmt(pStream, SgmtHead, pix, 128);
                    pStream += 128;
                    for(j = 0; j < 2; j++)
                    {
                        p0 = pFrame0 + (j + hh * 2 + mby * 8) * imgWidth;
                        for(i = 0; i < 64; i++)
                        {
                            if(1 == (i & 1))
                                *(p0 + mbx * 256 + ww * 64 + i) = pix[i/2 + j * 32];
                            else
                                *(p0 + mbx * 256 + ww * 64 + i) = pix[i/2 + j * 32 + 64];

                        }
                    }
                }
            }
        }
    }
    return;
    //return pStream - pData;
}

void ref_decompress_H264(int imgWidth, int imgHeight, HI_U8 *pData, HI_U8 *pHead, HI_U8 *pFrame0)
{
    HI_U8 *pStream = pData, pix[256], *p0;
    int mbx, mby, hh, ww,  h_stride;//sgmt_num = 0,
    int i, j, SgmtHead;
    if( 0 != (imgWidth & 0x3F)) // || 0 != (imgHeight & 0x3F) )
    {
        HI_ERR_VENC("ref_decompress_H264, img size not 64-aligned\n");
        return ;
    }

    for(mby = 0; mby < imgHeight / 16; mby++)
    {
        for(mbx = 0; mbx < (imgWidth + 255) / 256; mbx++)
        {
            for(hh = 0; hh < 4; hh++)
            {
                for(ww = 0; ww < 4; ww ++)
                {
                    if(mbx*256 + 256 > imgWidth && ww > imgWidth % 256 / 64 - 1)
                    {
                        pStream += (ww == 0 ? 0 : (4 -ww)*256);
                        break;
                    }

                    h_stride = (imgWidth+255)/256*32;
                    SgmtHead = *(pHead + mby * h_stride + mbx * 32 + (hh == 3 ? 16 : 0) + hh*4 + ww);
                    ref_decompress_sgmt(pStream, SgmtHead, pix, 256);
                    pStream += 256;
                    for(j = 0; j < 4; j++)
                    {
                       p0 = pFrame0 + (j + hh * 4 + mby * 16) * imgWidth;
                       for(i = 0; i < 64; i++)
                       {
                          *(p0 + mbx * 256 + ww * 64 + i) = pix[i + j * 64];
                       }
                    }
                }
            }
        }
    }
    return;
    //return pStream - pData;
}

HI_VOID VENC_DRV_DpressRcn( HI_HANDLE EncHandle )
{
	//HI_S32 Md5result = 0;
    VeduEfl_EncPara_S  *pEncPara  = (VeduEfl_EncPara_S *)EncHandle;

    HI_U32 w = 0;
    HI_U32 h = 0;
	HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 width  = 0;
    HI_U32 height = 0;
	width = pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix;
	height = pEncPara->pstCfg_EncPara->vcpi_imgheight_pix;

	w = (pEncPara->pstCfg_EncPara->vcpi_imgwidth_pix  + 63) / 64 * 64;
    h = (pEncPara->pstCfg_EncPara->vcpi_imgheight_pix + 15) / 16 * 16;

    if(pEncPara->vcpi_protocol == VEDU_H264)
    {
        ref_decompress_H264( w, h, pEncPara->VirRcnYAddr[pEncPara->RcnIdx], pEncPara->VirRcnYHAddr[pEncPara->RcnIdx], pMd5SrcUV);

        for (i = 0;i < height;i++)
        {
            for (j = 0;j < width;j++)
            {
                pMd5SrcY[i*width+ j] = pMd5SrcUV[i*w + j];
            }
        }
        ref_decompress_chroma_H264(w, h, pEncPara->VirRcnCAddr[pEncPara->RcnIdx], pEncPara->VirRcnCHAddr[pEncPara->RcnIdx], pMd5SrcUV);
    }
    else
    {
        ref_decompress( w, h, pEncPara->VirRcnYAddr[pEncPara->RcnIdx], pEncPara->VirRcnYHAddr[pEncPara->RcnIdx], pMd5SrcUV);

        for (i = 0;i < height;i++)
        {
            for (j = 0;j < width;j++)
            {
                pMd5SrcY[i*width+ j] = pMd5SrcUV[i*w + j];
            }
        }
        ref_decompress_chroma(w, h, pEncPara->VirRcnCAddr[pEncPara->RcnIdx], pEncPara->VirRcnCHAddr[pEncPara->RcnIdx], pMd5SrcUV);
    }

    for (i = 0;i < height/2;i++)
    {
        for (j = 0;j < width/2;j++)
        {
            pMd5SrcU[i*width/2+ j] = pMd5SrcUV[i*w + 2*j + 1];
            pMd5SrcV[i*width/2+ j] = pMd5SrcUV[i*w + 2*j];
        }
    }


    return ;
}

#endif


HI_U32 RadomValue0(unsigned int value,unsigned int length)
{
   HI_U32 rand;
   HI_U32 data = 0;

   HI_U32 i;

   if(value !=0)
   {
    return value;
   }

   for (i=0;i<length;i++)
   {
      rand = 8;
   	data = rand % 2;
   	value |= data << i;
   }

   if(value==0)
   {
   	value = 1;
   }

   return value;
}


HI_U32 RadomValue1(int* pArray,int value,unsigned int length)
{
   HI_U32 rand;
   HI_U32 index;
   for(index=0;index<length;index++)
    {
     if(pArray[index] == value)
        return value;
   }
   rand = 8;
   index = (rand & 0x0FFFFFFF) % length;
   value = pArray[index];
   return value;
}


HI_VOID check_enc_para(VeduEfl_EncPara_S_Cfg* pEncPara, int bIntraFrame)
{
	HI_U32 pic_height;
	HI_U32 pic_width ;
	//int shift_rand_num;

	int randomnozero;
	int rand0[20];
	int j=0;

	int randomvalue = 0;


	pEncPara->intra_cu4_mode31_en        = (pEncPara-> intra_cu4_mode0>>31) & 0x1;
	pEncPara->intra_cu4_mode30_en        = (pEncPara-> intra_cu4_mode0>>30) & 0x1;
	pEncPara->intra_cu4_mode29_en        = (pEncPara-> intra_cu4_mode0>>29) & 0x1;
	pEncPara->intra_cu4_mode28_en        = (pEncPara-> intra_cu4_mode0>>28) & 0x1;
	pEncPara->intra_cu4_mode27_en        = (pEncPara-> intra_cu4_mode0>>27) & 0x1;
	pEncPara->intra_cu4_mode26_en        = (pEncPara-> intra_cu4_mode0>>26) & 0x1;
	pEncPara->intra_cu4_mode25_en        = (pEncPara-> intra_cu4_mode0>>25) & 0x1;
	pEncPara->intra_cu4_mode24_en        = (pEncPara-> intra_cu4_mode0>>24) & 0x1;
	pEncPara->intra_cu4_mode23_en        = (pEncPara-> intra_cu4_mode0>>23) & 0x1;
	pEncPara->intra_cu4_mode22_en        = (pEncPara-> intra_cu4_mode0>>22) & 0x1;
	pEncPara->intra_cu4_mode21_en        = (pEncPara-> intra_cu4_mode0>>21) & 0x1;
	pEncPara->intra_cu4_mode20_en        = (pEncPara-> intra_cu4_mode0>>20) & 0x1;
	pEncPara->intra_cu4_mode19_en        = (pEncPara-> intra_cu4_mode0>>19) & 0x1;
	pEncPara->intra_cu4_mode18_en        = (pEncPara-> intra_cu4_mode0>>18) & 0x1;
	pEncPara->intra_cu4_mode17_en        = (pEncPara-> intra_cu4_mode0>>17) & 0x1;
	pEncPara->intra_cu4_mode16_en        = (pEncPara-> intra_cu4_mode0>>16) & 0x1;
	pEncPara->intra_cu4_mode15_en        = (pEncPara-> intra_cu4_mode0>>15) & 0x1;
	pEncPara->intra_cu4_mode14_en        = (pEncPara-> intra_cu4_mode0>>14) & 0x1;
	pEncPara->intra_cu4_mode13_en        = (pEncPara-> intra_cu4_mode0>>13) & 0x1;
	pEncPara->intra_cu4_mode12_en        = (pEncPara-> intra_cu4_mode0>>12) & 0x1;
	pEncPara->intra_cu4_mode11_en        = (pEncPara-> intra_cu4_mode0>>11) & 0x1;
	pEncPara->intra_cu4_mode10_en        = (pEncPara-> intra_cu4_mode0>>10) & 0x1;
	pEncPara->intra_cu4_mode9_en         = (pEncPara-> intra_cu4_mode0>>9) & 0x1;
	pEncPara->intra_cu4_mode8_en         = (pEncPara-> intra_cu4_mode0>>8) & 0x1;
	pEncPara->intra_cu4_mode7_en         = (pEncPara-> intra_cu4_mode0>>7) & 0x1;
	pEncPara->intra_cu4_mode6_en         = (pEncPara-> intra_cu4_mode0>>6) & 0x1;
	pEncPara->intra_cu4_mode5_en         = (pEncPara-> intra_cu4_mode0>>5) & 0x1;
	pEncPara->intra_cu4_mode4_en         = (pEncPara-> intra_cu4_mode0>>4) & 0x1;
	pEncPara->intra_cu4_mode3_en         = (pEncPara-> intra_cu4_mode0>>3) & 0x1;
	pEncPara->intra_cu4_mode2_en         = (pEncPara-> intra_cu4_mode0>>2) & 0x1;
	pEncPara->intra_cu4_mode1_en         = (pEncPara-> intra_cu4_mode0>>1) & 0x1;
	pEncPara->intra_cu4_mode0_en         = (pEncPara-> intra_cu4_mode0) & 0x1;
	pEncPara->intra_cu4_mode34_en        = (pEncPara-> intra_cu4_mode1>>2) & 0x1;
	pEncPara->intra_cu4_mode33_en        = (pEncPara-> intra_cu4_mode1>>1) & 0x1;
	pEncPara->intra_cu4_mode32_en        = (pEncPara-> intra_cu4_mode1) & 0x1;
	pEncPara->intra_cu8_mode31_en        = (pEncPara-> intra_cu8_mode0>>31) & 0x1;
	pEncPara->intra_cu8_mode30_en        = (pEncPara-> intra_cu8_mode0>>30) & 0x1;
	pEncPara->intra_cu8_mode29_en        = (pEncPara-> intra_cu8_mode0>>29) & 0x1;
	pEncPara->intra_cu8_mode28_en        = (pEncPara-> intra_cu8_mode0>>28) & 0x1;
	pEncPara->intra_cu8_mode27_en        = (pEncPara-> intra_cu8_mode0>>27) & 0x1;
	pEncPara->intra_cu8_mode26_en        = (pEncPara-> intra_cu8_mode0>>26) & 0x1;
	pEncPara->intra_cu8_mode25_en        = (pEncPara-> intra_cu8_mode0>>25) & 0x1;
	pEncPara->intra_cu8_mode24_en        = (pEncPara-> intra_cu8_mode0>>24) & 0x1;
	pEncPara->intra_cu8_mode23_en        = (pEncPara-> intra_cu8_mode0>>23) & 0x1;
	pEncPara->intra_cu8_mode22_en        = (pEncPara-> intra_cu8_mode0>>22) & 0x1;
	pEncPara->intra_cu8_mode21_en        = (pEncPara-> intra_cu8_mode0>>21) & 0x1;
	pEncPara->intra_cu8_mode20_en        = (pEncPara-> intra_cu8_mode0>>20) & 0x1;
	pEncPara->intra_cu8_mode19_en        = (pEncPara-> intra_cu8_mode0>>19) & 0x1;
	pEncPara->intra_cu8_mode18_en        = (pEncPara-> intra_cu8_mode0>>18) & 0x1;
	pEncPara->intra_cu8_mode17_en        = (pEncPara-> intra_cu8_mode0>>17) & 0x1;
	pEncPara->intra_cu8_mode16_en        = (pEncPara-> intra_cu8_mode0>>16) & 0x1;
	pEncPara->intra_cu8_mode15_en        = (pEncPara-> intra_cu8_mode0>>15) & 0x1;
	pEncPara->intra_cu8_mode14_en        = (pEncPara-> intra_cu8_mode0>>14) & 0x1;
	pEncPara->intra_cu8_mode13_en        = (pEncPara-> intra_cu8_mode0>>13) & 0x1;
	pEncPara->intra_cu8_mode12_en        = (pEncPara-> intra_cu8_mode0>>12) & 0x1;
	pEncPara->intra_cu8_mode11_en        = (pEncPara-> intra_cu8_mode0>>11) & 0x1;
	pEncPara->intra_cu8_mode10_en        = (pEncPara-> intra_cu8_mode0>>10) & 0x1;
	pEncPara->intra_cu8_mode9_en         = (pEncPara-> intra_cu8_mode0>>9) & 0x1;
	pEncPara->intra_cu8_mode8_en         = (pEncPara-> intra_cu8_mode0>>8) & 0x1;
	pEncPara->intra_cu8_mode7_en         = (pEncPara-> intra_cu8_mode0>>7) & 0x1;
	pEncPara->intra_cu8_mode6_en         = (pEncPara-> intra_cu8_mode0>>6) & 0x1;
	pEncPara->intra_cu8_mode5_en         = (pEncPara-> intra_cu8_mode0>>5) & 0x1;
	pEncPara->intra_cu8_mode4_en         = (pEncPara-> intra_cu8_mode0>>4) & 0x1;
	pEncPara->intra_cu8_mode3_en         = (pEncPara-> intra_cu8_mode0>>3) & 0x1;
	pEncPara->intra_cu8_mode2_en         = (pEncPara-> intra_cu8_mode0>>2) & 0x1;
	pEncPara->intra_cu8_mode1_en         = (pEncPara-> intra_cu8_mode0>>1) & 0x1;
	pEncPara->intra_cu8_mode0_en         = (pEncPara-> intra_cu8_mode0) & 0x1;
	pEncPara->intra_cu8_mode34_en        = (pEncPara-> intra_cu8_mode1>>2) & 0x1;
	pEncPara->intra_cu8_mode33_en        = (pEncPara-> intra_cu8_mode1>>1) & 0x1;
	pEncPara->intra_cu8_mode32_en        = (pEncPara-> intra_cu8_mode1) & 0x1;
	pEncPara->intra_cu16_mode31_en       = (pEncPara-> intra_cu16_mode0>>31) & 0x1;
	pEncPara->intra_cu16_mode30_en       = (pEncPara-> intra_cu16_mode0>>30) & 0x1;
	pEncPara->intra_cu16_mode29_en       = (pEncPara-> intra_cu16_mode0>>29) & 0x1;
	pEncPara->intra_cu16_mode28_en       = (pEncPara-> intra_cu16_mode0>>28) & 0x1;
	pEncPara->intra_cu16_mode27_en       = (pEncPara-> intra_cu16_mode0>>27) & 0x1;
	pEncPara->intra_cu16_mode26_en       = (pEncPara-> intra_cu16_mode0>>26) & 0x1;
	pEncPara->intra_cu16_mode25_en       = (pEncPara-> intra_cu16_mode0>>25) & 0x1;
	pEncPara->intra_cu16_mode24_en       = (pEncPara-> intra_cu16_mode0>>24) & 0x1;
	pEncPara->intra_cu16_mode23_en       = (pEncPara-> intra_cu16_mode0>>23) & 0x1;
	pEncPara->intra_cu16_mode22_en       = (pEncPara-> intra_cu16_mode0>>22) & 0x1;
	pEncPara->intra_cu16_mode21_en       = (pEncPara-> intra_cu16_mode0>>21) & 0x1;
	pEncPara->intra_cu16_mode20_en       = (pEncPara-> intra_cu16_mode0>>20) & 0x1;
	pEncPara->intra_cu16_mode19_en       = (pEncPara-> intra_cu16_mode0>>19) & 0x1;
	pEncPara->intra_cu16_mode18_en       = (pEncPara-> intra_cu16_mode0>>18) & 0x1;
	pEncPara->intra_cu16_mode17_en       = (pEncPara-> intra_cu16_mode0>>17) & 0x1;
	pEncPara->intra_cu16_mode16_en       = (pEncPara-> intra_cu16_mode0>>16) & 0x1;
	pEncPara->intra_cu16_mode15_en       = (pEncPara-> intra_cu16_mode0>>15) & 0x1;
	pEncPara->intra_cu16_mode14_en       = (pEncPara-> intra_cu16_mode0>>14) & 0x1;
	pEncPara->intra_cu16_mode13_en       = (pEncPara-> intra_cu16_mode0>>13) & 0x1;
	pEncPara->intra_cu16_mode12_en       = (pEncPara-> intra_cu16_mode0>>12) & 0x1;
	pEncPara->intra_cu16_mode11_en       = (pEncPara-> intra_cu16_mode0>>11) & 0x1;
	pEncPara->intra_cu16_mode10_en       = (pEncPara-> intra_cu16_mode0>>10) & 0x1;
	pEncPara->intra_cu16_mode9_en        = (pEncPara-> intra_cu16_mode0>>9) & 0x1;
	pEncPara->intra_cu16_mode8_en        = (pEncPara-> intra_cu16_mode0>>8) & 0x1;
	pEncPara->intra_cu16_mode7_en        = (pEncPara-> intra_cu16_mode0>>7) & 0x1;
	pEncPara->intra_cu16_mode6_en        = (pEncPara-> intra_cu16_mode0>>6) & 0x1;
	pEncPara->intra_cu16_mode5_en        = (pEncPara-> intra_cu16_mode0>>5) & 0x1;
	pEncPara->intra_cu16_mode4_en        = (pEncPara-> intra_cu16_mode0>>4) & 0x1;
	pEncPara->intra_cu16_mode3_en        = (pEncPara-> intra_cu16_mode0>>3) & 0x1;
	pEncPara->intra_cu16_mode2_en        = (pEncPara-> intra_cu16_mode0>>2) & 0x1;
	pEncPara->intra_cu16_mode1_en        = (pEncPara-> intra_cu16_mode0>>1) & 0x1;
	pEncPara->intra_cu16_mode0_en        = (pEncPara-> intra_cu16_mode0) & 0x1;
	pEncPara->intra_cu16_mode34_en       = (pEncPara-> intra_cu16_mode1>>2) & 0x1;
	pEncPara->intra_cu16_mode33_en       = (pEncPara-> intra_cu16_mode1>>1) & 0x1;
	pEncPara->intra_cu16_mode32_en       = (pEncPara-> intra_cu16_mode1) & 0x1;
	pEncPara->intra_cu32_mode31_en       = (pEncPara-> intra_cu32_mode0>>31) & 0x1;
	pEncPara->intra_cu32_mode30_en       = (pEncPara-> intra_cu32_mode0>>30) & 0x1;
	pEncPara->intra_cu32_mode29_en       = (pEncPara-> intra_cu32_mode0>>29) & 0x1;
	pEncPara->intra_cu32_mode28_en       = (pEncPara-> intra_cu32_mode0>>28) & 0x1;
	pEncPara->intra_cu32_mode27_en       = (pEncPara-> intra_cu32_mode0>>27) & 0x1;
	pEncPara->intra_cu32_mode26_en       = (pEncPara-> intra_cu32_mode0>>26) & 0x1;
	pEncPara->intra_cu32_mode25_en       = (pEncPara-> intra_cu32_mode0>>25) & 0x1;
	pEncPara->intra_cu32_mode24_en       = (pEncPara-> intra_cu32_mode0>>24) & 0x1;
	pEncPara->intra_cu32_mode23_en       = (pEncPara-> intra_cu32_mode0>>23) & 0x1;
	pEncPara->intra_cu32_mode22_en       = (pEncPara-> intra_cu32_mode0>>22) & 0x1;
	pEncPara->intra_cu32_mode21_en       = (pEncPara-> intra_cu32_mode0>>21) & 0x1;
	pEncPara->intra_cu32_mode20_en       = (pEncPara-> intra_cu32_mode0>>20) & 0x1;
	pEncPara->intra_cu32_mode19_en       = (pEncPara-> intra_cu32_mode0>>19) & 0x1;
	pEncPara->intra_cu32_mode18_en       = (pEncPara-> intra_cu32_mode0>>18) & 0x1;
	pEncPara->intra_cu32_mode17_en       = (pEncPara-> intra_cu32_mode0>>17) & 0x1;
	pEncPara->intra_cu32_mode16_en       = (pEncPara-> intra_cu32_mode0>>16) & 0x1;
	pEncPara->intra_cu32_mode15_en       = (pEncPara-> intra_cu32_mode0>>15) & 0x1;
	pEncPara->intra_cu32_mode14_en       = (pEncPara-> intra_cu32_mode0>>14) & 0x1;
	pEncPara->intra_cu32_mode13_en       = (pEncPara-> intra_cu32_mode0>>13) & 0x1;
	pEncPara->intra_cu32_mode12_en       = (pEncPara-> intra_cu32_mode0>>12) & 0x1;
	pEncPara->intra_cu32_mode11_en       = (pEncPara-> intra_cu32_mode0>>11) & 0x1;
	pEncPara->intra_cu32_mode10_en       = (pEncPara-> intra_cu32_mode0>>10) & 0x1;
	pEncPara->intra_cu32_mode9_en        = (pEncPara-> intra_cu32_mode0>>9) & 0x1;
	pEncPara->intra_cu32_mode8_en        = (pEncPara-> intra_cu32_mode0>>8) & 0x1;
	pEncPara->intra_cu32_mode7_en        = (pEncPara-> intra_cu32_mode0>>7) & 0x1;
	pEncPara->intra_cu32_mode6_en        = (pEncPara-> intra_cu32_mode0>>6) & 0x1;
	pEncPara->intra_cu32_mode5_en        = (pEncPara-> intra_cu32_mode0>>5) & 0x1;
	pEncPara->intra_cu32_mode4_en        = (pEncPara-> intra_cu32_mode0>>4) & 0x1;
	pEncPara->intra_cu32_mode3_en        = (pEncPara-> intra_cu32_mode0>>3) & 0x1;
	pEncPara->intra_cu32_mode2_en        = (pEncPara-> intra_cu32_mode0>>2) & 0x1;
	pEncPara->intra_cu32_mode1_en        = (pEncPara-> intra_cu32_mode0>>1) & 0x1;
	pEncPara->intra_cu32_mode0_en        = (pEncPara-> intra_cu32_mode0) & 0x1;
	pEncPara->intra_cu32_mode34_en       = (pEncPara-> intra_cu32_mode1>>2) & 0x1;
	pEncPara->intra_cu32_mode33_en       = (pEncPara-> intra_cu32_mode1>>1) & 0x1;
	pEncPara->intra_cu32_mode32_en       = (pEncPara-> intra_cu32_mode1) & 0x1;
	//return;
	//Rule.0
	pEncPara->min_qp = CLIP3(0,51,pEncPara->min_qp);
	pEncPara->max_qp = CLIP3(0,51,pEncPara->max_qp);
	pEncPara->max_qp = MAX(pEncPara->min_qp,pEncPara->max_qp);
	pEncPara->vcpi_frm_qp = CLIP3((HI_S32)pEncPara->min_qp,(HI_S32)pEncPara->max_qp,(HI_S32)pEncPara->vcpi_frm_qp);

	//Rule.2
	pEncPara->vcpi_w_outstanding = CLIP3(0,7,pEncPara->vcpi_w_outstanding);
	pEncPara->vcpi_r_outstanding = CLIP3(0,31,pEncPara->vcpi_r_outstanding);

	//Rule.3
	pEncPara->vcpi_oriheight_pix = CLIP3(144,4096,pEncPara->vcpi_oriheight_pix);
	pEncPara->vcpi_oriheight_pix = pEncPara->vcpi_oriheight_pix/2*2;
	pEncPara->vcpi_oriwidth_pix = CLIP3(144,4096,pEncPara->vcpi_oriwidth_pix);
	pEncPara->vcpi_oriwidth_pix = pEncPara->vcpi_oriwidth_pix/2*2;
	pEncPara->vcpi_imgheight_pix = CLIP3(144,4096,pEncPara->vcpi_imgheight_pix);
	pEncPara->vcpi_imgheight_pix = pEncPara->vcpi_imgheight_pix/2*2;
	pEncPara->vcpi_imgwidth_pix = CLIP3(144,4096,pEncPara->vcpi_imgwidth_pix);
	pEncPara->vcpi_imgwidth_pix = pEncPara->vcpi_imgwidth_pix/2*2;
	pEncPara->vcpi_imgwidth_pix = MIN(pEncPara->vcpi_imgwidth_pix,pEncPara->vcpi_oriwidth_pix);
	pEncPara->vcpi_imgheight_pix = MIN(pEncPara->vcpi_imgheight_pix,pEncPara->vcpi_oriheight_pix);


	//Rule.11
	if((pEncPara->vcpi_crop_en == 1) && (pEncPara->vcpi_scale_en == 1))
	{
		pEncPara->vcpi_yscale = CLIP3(0x2000,0x8000,pEncPara->vcpi_yscale);
		pEncPara->vcpi_xscale = CLIP3(0x2000,0x8000,pEncPara->vcpi_xscale);
		pEncPara->vcpi_crop_ystart  = MIN(pEncPara->vcpi_oriheight_pix - pEncPara->vcpi_imgheight_pix,pEncPara->vcpi_crop_ystart);
		pEncPara->vcpi_crop_xstart  = MIN(pEncPara->vcpi_oriwidth_pix - pEncPara->vcpi_imgwidth_pix,pEncPara->vcpi_crop_xstart);
		pEncPara->vcpi_crop_ystart  = pEncPara->vcpi_crop_ystart/2*2;
		pEncPara->vcpi_crop_xstart = pEncPara->vcpi_crop_xstart/2*2;
		pEncPara->vcpi_crop_yend   = MIN(pEncPara->vcpi_oriheight_pix-1, pEncPara->vcpi_crop_yend );
		pEncPara->vcpi_crop_xend  = MIN(pEncPara->vcpi_oriwidth_pix-1 , pEncPara->vcpi_crop_xend );
		pEncPara->vcpi_crop_yend  = pEncPara->vcpi_crop_yend/2*2 + 1;
		pEncPara->vcpi_crop_xend  = pEncPara->vcpi_crop_xend/2*2 + 1;
		pEncPara->vcpi_crop_yend  = MAX(pEncPara->vcpi_imgheight_pix + pEncPara->vcpi_crop_ystart - 1,pEncPara->vcpi_crop_yend);
		pEncPara->vcpi_crop_xend  = MAX(pEncPara->vcpi_imgwidth_pix + pEncPara->vcpi_crop_xstart - 1, pEncPara->vcpi_crop_xend);
		if(((pEncPara->vcpi_crop_yend - pEncPara->vcpi_crop_ystart + 1) > (pEncPara->vcpi_imgheight_pix<<2)))
		{
		if(((pEncPara->vcpi_crop_yend - pEncPara->vcpi_crop_ystart + 1) % 4) != 0)
		pEncPara->vcpi_imgheight_pix = ((pEncPara->vcpi_crop_yend - pEncPara->vcpi_crop_ystart + 1)>>2) + 2;
		else
		pEncPara->vcpi_imgheight_pix = (pEncPara->vcpi_crop_yend - pEncPara->vcpi_crop_ystart + 1)>>2;
		}
		if(((pEncPara->vcpi_crop_xend - pEncPara->vcpi_crop_xstart + 1) > (pEncPara->vcpi_imgwidth_pix<<2)))
		{
		if(((pEncPara->vcpi_crop_xend - pEncPara->vcpi_crop_xstart + 1) % 4) != 0)
		pEncPara->vcpi_imgwidth_pix = ((pEncPara->vcpi_crop_xend - pEncPara->vcpi_crop_xstart + 1)>>2) + 2;
		else
		pEncPara->vcpi_imgwidth_pix = (pEncPara->vcpi_crop_xend - pEncPara->vcpi_crop_xstart + 1)>>2;
		}
		if((pEncPara->vcpi_imgwidth_pix % 2) != 0)
		pEncPara->vcpi_imgwidth_pix = pEncPara->vcpi_imgwidth_pix + 1;
		if((pEncPara->vcpi_imgheight_pix % 2) != 0)
		pEncPara->vcpi_imgheight_pix = pEncPara->vcpi_imgheight_pix + 1;

	    pic_height = pEncPara->vcpi_imgheight_pix;
	    pic_width  = pEncPara->vcpi_imgwidth_pix;

		if(((pEncPara->vcpi_crop_yend - pEncPara->vcpi_crop_ystart + 1)*8192)%pic_height == 0)
		pEncPara->vcpi_yscale = ((pEncPara->vcpi_crop_yend -pEncPara->vcpi_crop_ystart + 1) *8192)/pic_height;
		else
		pEncPara->vcpi_yscale = ((pEncPara->vcpi_crop_yend -pEncPara->vcpi_crop_ystart + 1) *8192)/pic_height + 1;


		if(((pEncPara->vcpi_crop_xend - pEncPara->vcpi_crop_xstart + 1)*8192)%pic_width == 0)
		pEncPara->vcpi_xscale = ((pEncPara->vcpi_crop_xend -pEncPara->vcpi_crop_xstart + 1) *8192)/pic_width;
		else
		pEncPara->vcpi_xscale = ((pEncPara->vcpi_crop_xend -pEncPara->vcpi_crop_xstart + 1) *8192)/pic_width+ 1;
	}
	else if ((pEncPara->vcpi_crop_en == 1) && (pEncPara->vcpi_scale_en == 0))
	{
		pEncPara->vcpi_crop_ystart  = MIN(pEncPara->vcpi_oriheight_pix - pEncPara->vcpi_imgheight_pix,pEncPara->vcpi_crop_ystart);
		pEncPara->vcpi_crop_xstart  = MIN(pEncPara->vcpi_oriwidth_pix - pEncPara->vcpi_imgwidth_pix,pEncPara->vcpi_crop_xstart);
		pEncPara->vcpi_crop_ystart = pEncPara->vcpi_crop_ystart/2*2;
		pEncPara->vcpi_crop_xstart = pEncPara->vcpi_crop_xstart/2*2;
		pEncPara->vcpi_crop_yend =   pEncPara->vcpi_imgheight_pix + pEncPara->vcpi_crop_ystart - 1;
		pEncPara->vcpi_crop_xend =   pEncPara->vcpi_imgwidth_pix + pEncPara->vcpi_crop_xstart - 1;
	}
    else if ((pEncPara->vcpi_crop_en == 0) && (pEncPara->vcpi_scale_en == 1))
	{
	pEncPara->vcpi_yscale = CLIP3(0x2000,0x8000,pEncPara->vcpi_yscale);
	pEncPara->vcpi_xscale = CLIP3(0x2000,0x8000,pEncPara->vcpi_xscale);
	if((pEncPara->vcpi_oriheight_pix > (pEncPara->vcpi_imgheight_pix<<2)))
	{
	if((pEncPara->vcpi_oriheight_pix % 4) != 0)
	pEncPara->vcpi_imgheight_pix = (pEncPara->vcpi_oriheight_pix>>2) + 2;
	else
	pEncPara->vcpi_imgheight_pix = pEncPara->vcpi_oriheight_pix>>2;
	}
	if((pEncPara->vcpi_oriwidth_pix > (pEncPara->vcpi_imgwidth_pix<<2)))
	{
	if((pEncPara->vcpi_oriwidth_pix % 4) != 0)
	pEncPara->vcpi_imgwidth_pix = (pEncPara->vcpi_oriwidth_pix>>2) + 2;
	else
	pEncPara->vcpi_imgwidth_pix = pEncPara->vcpi_oriwidth_pix>>2;
	}
	if((pEncPara->vcpi_imgwidth_pix % 2) != 0)
	pEncPara->vcpi_imgwidth_pix = pEncPara->vcpi_imgwidth_pix + 1;
	if((pEncPara->vcpi_imgheight_pix % 2) != 0)
	pEncPara->vcpi_imgheight_pix = pEncPara->vcpi_imgheight_pix + 1;


	pic_height = pEncPara->vcpi_imgheight_pix;
	pic_width  = pEncPara->vcpi_imgwidth_pix;

	if((pEncPara->vcpi_oriheight_pix*8192)%pic_height == 0)
	pEncPara->vcpi_yscale = (pEncPara->vcpi_oriheight_pix*8192)/pic_height;
	else
	pEncPara->vcpi_yscale = (pEncPara->vcpi_oriheight_pix*8192)/pic_height + 1;

	if((pEncPara->vcpi_oriwidth_pix*8192)%pic_width == 0)
	pEncPara->vcpi_xscale = (pEncPara->vcpi_oriwidth_pix*8192)/pic_width;
	else
	pEncPara->vcpi_xscale = (pEncPara->vcpi_oriwidth_pix*8192)/pic_width + 1;
	}
	else
	{
	pEncPara->vcpi_imgheight_pix = pEncPara->vcpi_oriheight_pix;
	pEncPara->vcpi_imgwidth_pix = pEncPara->vcpi_oriwidth_pix;
	}

	pic_height = pEncPara->vcpi_imgheight_pix;
	pic_width  = pEncPara->vcpi_imgwidth_pix;

	//Rule.4
	if (pEncPara->vcpi_protocol == VEDU_H265)
	{
	pEncPara->vcpi_sw_height = MIN((pic_height/4-16)/2,pEncPara->vcpi_sw_height);
	pEncPara->vcpi_sw_height = pEncPara->vcpi_sw_height/8*8;
	pEncPara->vcpi_sw_height = CLIP3(8,32,pEncPara->vcpi_sw_height);
	//ASSERT(pEncPara->vcpi_sw_height%8 == 0);
	pEncPara->vcpi_sw_width = MIN((pic_width/4-16)/2,pEncPara->vcpi_sw_width);
	pEncPara->vcpi_sw_width = pEncPara->vcpi_sw_width/8*8;
	pEncPara->vcpi_sw_width = CLIP3(8,72,pEncPara->vcpi_sw_width);
	//ASSERT(pEncPara->vcpi_sw_width%8 == 0);
	}
	else if (pEncPara->vcpi_protocol == VEDU_H264)
	{
	pEncPara->vcpi_sw_height = MIN((((pic_height + 15)/16) -1 -1)/2 -1,pEncPara->vcpi_sw_height);
	pEncPara->vcpi_sw_height = MIN(((768/((pic_width+ 15)/16) -1)/2) -1,pEncPara->vcpi_sw_height);
	pEncPara->vcpi_sw_height = CLIP3(0,5,pEncPara->vcpi_sw_height);
	pEncPara->vcpi_sw_width = MIN((((pic_width + 15)/16)-2 -1)/2 - 1,pEncPara->vcpi_sw_width);
	pEncPara->vcpi_sw_width = CLIP3(0,11,pEncPara->vcpi_sw_width);
	}

	//Rule.5
	if (pEncPara->vcpi_protocol == VEDU_H265)
	{
	pEncPara->vcpi_win0_height = MIN((pic_height/4-16)/2,pEncPara->vcpi_win0_height);
	pEncPara->vcpi_win0_height = CLIP3(1,32,pEncPara->vcpi_win0_height);
	pEncPara->vcpi_win0_width = MIN((pic_width/4-16)/2,pEncPara->vcpi_win0_width);
	pEncPara->vcpi_win0_width = pEncPara->vcpi_win0_width/8*8;
	pEncPara->vcpi_win0_width = CLIP3(8,72,pEncPara->vcpi_win0_width);
	//ASSERT(pEncPara->vcpi_win0_width%8 == 0);


	pEncPara->vcpi_win1_height = MIN((pic_height/4-16)/2,pEncPara->vcpi_win1_height);
	pEncPara->vcpi_win1_height = CLIP3(1,32,pEncPara->vcpi_win1_height);
	pEncPara->vcpi_win1_width = MIN((pic_width/4-16)/2,pEncPara->vcpi_win1_width);
	pEncPara->vcpi_win1_width = pEncPara->vcpi_win1_width/8*8;
	pEncPara->vcpi_win1_width = CLIP3(8,72,pEncPara->vcpi_win1_width);
	//ASSERT(pEncPara->vcpi_win1_width%8 == 0);


	pEncPara->vcpi_win2_height = MIN((pic_height/4-16)/2,pEncPara->vcpi_win2_height);
	pEncPara->vcpi_win2_height = CLIP3(1,32,pEncPara->vcpi_win2_height);
	pEncPara->vcpi_win2_width = MIN((pic_width/4-16)/2,pEncPara->vcpi_win2_width);
	pEncPara->vcpi_win2_width = pEncPara->vcpi_win2_width/8*8;
	pEncPara->vcpi_win2_width = CLIP3(8,72,pEncPara->vcpi_win2_width);
	//ASSERT(pEncPara->vcpi_win2_width%8 == 0);

	pEncPara->vcpi_win3_height = MIN((pic_height/4-16)/2,pEncPara->vcpi_win3_height);
	pEncPara->vcpi_win3_height = CLIP3(1,32,pEncPara->vcpi_win3_height);
	pEncPara->vcpi_win3_width = MIN((pic_width/4-16)/2,pEncPara->vcpi_win3_width);
	pEncPara->vcpi_win3_width = pEncPara->vcpi_win3_width/8*8;
	pEncPara->vcpi_win3_width = CLIP3(8,72,pEncPara->vcpi_win3_width);
	//ASSERT(pEncPara->vcpi_win3_width%8 == 0);
	}
	else if (pEncPara->vcpi_protocol == VEDU_H264)
	{
	pEncPara->vcpi_win0_height = CLIP3(0,510,pEncPara->vcpi_win0_height);
	pEncPara->vcpi_win0_width = CLIP3(0,1022,pEncPara->vcpi_win0_width);
	pEncPara->vcpi_win1_height = CLIP3(0,510,pEncPara->vcpi_win1_height);
	pEncPara->vcpi_win1_width = CLIP3(0,1022,pEncPara->vcpi_win1_width);
	pEncPara->vcpi_win2_height = CLIP3(0,510,pEncPara->vcpi_win2_height);
	pEncPara->vcpi_win2_width = CLIP3(0,1022,pEncPara->vcpi_win2_width);
	pEncPara->vcpi_win3_height = CLIP3(0,510,pEncPara->vcpi_win3_height);
	pEncPara->vcpi_win3_width = CLIP3(0,1022,pEncPara->vcpi_win3_width);
	}

	//Rule.6


	if ((pEncPara->vcpi_protocol == VEDU_H265) && bIntraFrame)
	{
		if((2 <= pic_height%32 && pic_height%32 <= 8) || (16 < pic_height%32 && pic_height%32 <= 24)
		|| (2 <= pic_width%32 && pic_width%32 <= 8) || (16 <pic_width%32 && pic_width%32<= 24))
		{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0x3;
		randomnozero = RadomValue0(randomnozero,2) ;
		pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x3)) | randomnozero;
		}
		else if ((8 < pic_height%32 && pic_height%32 <= 16) || (8 < pic_width%32 && pic_width%32 <= 16))
		{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0x7;
		randomnozero = RadomValue0(randomnozero,3) ;
		pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x7)) | randomnozero;
		}
		else if ((24 < pic_height%32) || (24 < pic_width%32) || (pic_height%32 == 0) || (pic_width%32 == 0))
		{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0xf;
		randomnozero = RadomValue0(randomnozero,4) ;
		pEncPara->vcpi_intra_cu_en =  randomnozero;
		}
	}
	else if ((pEncPara->vcpi_protocol == VEDU_H265) && bIntraFrame)
	{
        if(((2 <= pic_height%32 && pic_height%32 <= 8) || (16 < pic_height%32 && pic_height%32 <= 24) || (2 <= pic_width%32 && pic_width%32 <= 8) || (16 < pic_width%32 && pic_width%32 <= 24))
            && ((((pEncPara->vcpi_intra_cu_en & 0x3) == 0) && (pEncPara->vcpi_ipcm_en == 0)) || (pEncPara->vcpi_force_inter == 1) || (pEncPara->vcpi_pblk_pre_en == 1)))
            {
              randomnozero = (pEncPara->vcpi_fme_cu_en>>1) & 0x7;
              randomnozero = RadomValue0(randomnozero,3);
              pEncPara->vcpi_fme_cu_en = (randomnozero<<1) | 0x1;
         }
        else if (((8 < pic_height%32 && pic_height%32 <= 16) || (8 < pic_width%32 && pic_width%32 <= 16))
            && ((((pEncPara->vcpi_intra_cu_en & 0x7) == 0) && (pEncPara->vcpi_ipcm_en == 0)) || (pEncPara->vcpi_force_inter == 1) || (pEncPara->vcpi_pblk_pre_en ==1)))
            {
             rand0[0] = 4;
             rand0[1] = 5;
             rand0[2] = 6;
             rand0[3] = 3;
             rand0[4] = 7;
             randomnozero = pEncPara->vcpi_fme_cu_en & 0x1;
             randomnozero |= ((pEncPara->vcpi_fme_cu_en>>3)&0x1)<<1;
             randomnozero |= ((pEncPara->vcpi_fme_cu_en>>1)&0x1)<<2;
             randomnozero = RadomValue1(rand0,randomnozero,5);
             pEncPara->vcpi_fme_cu_en = (pEncPara->vcpi_fme_cu_en & (~0x1)) | (randomnozero&0x1);
             pEncPara->vcpi_fme_cu_en = (pEncPara->vcpi_fme_cu_en & (~0x8)) | ((randomnozero&0x2)<<2);
             pEncPara->vcpi_fme_cu_en = (pEncPara->vcpi_fme_cu_en & (~0x2)) | ((randomnozero&0x4)>>1);
         }
        else if (((24 < pic_height%32) || (24 < pic_width%32) || (pic_height%32 == 0) || (pic_width%32 == 0)) && ((pic_width%64 != 0)||(pic_height%64 != 0))
            && ((((pEncPara->vcpi_intra_cu_en & 0xf) == 0) && (pEncPara->vcpi_ipcm_en == 0)) || (pEncPara->vcpi_force_inter == 1) || (pEncPara->vcpi_pblk_pre_en ==1)))
         {
             rand0[0]   = 2;
             rand0[1]   = 3;
             rand0[2]   = 4;
             rand0[3]   = 5;
             rand0[4]   = 6;
             rand0[5]   = 7;
             rand0[6]   = 9;
             rand0[7]   = 10;
             rand0[8]   = 11;
             rand0[9]   = 12;
             rand0[10] = 13;
             rand0[11] = 14;
             rand0[12] = 15;
             randomnozero = pEncPara->vcpi_fme_cu_en & 0xf;
             randomnozero = RadomValue1(rand0,randomnozero,13);
             pEncPara->vcpi_fme_cu_en = randomnozero;
         }
        else if ((pic_width%64 == 0) && (pic_height%64 == 0) && (((pEncPara->vcpi_intra_cu_en == 0) && (pEncPara->vcpi_ipcm_en == 0))
            || (pEncPara->vcpi_force_inter == 1) || (pEncPara->vcpi_pblk_pre_en ==1)))
        {
          if((!((pEncPara->vcpi_high3pre_en == 0x2) && ((pEncPara->vcpi_fme_cu_en&0x8) == 0x8))) && (!((pEncPara->vcpi_high3pre_en == 0x1) && ((pEncPara->vcpi_fme_cu_en&0x1) == 0x1))))
          {
             rand0[0]   = 2;
             rand0[1]   = 3;
             rand0[2]   = 4;
             rand0[3]   = 5;
             rand0[4]   = 6;
             rand0[5]   = 7;
             rand0[6]   = 9;
             rand0[7]   = 10;
             rand0[8]   = 11;
             rand0[9]   = 12;
             rand0[10] = 13;
             rand0[11] = 14;
             rand0[12] = 15;
             randomnozero = pEncPara->vcpi_fme_cu_en & 0xf;
             randomnozero = RadomValue1(rand0,randomnozero,13);
             pEncPara->vcpi_fme_cu_en = randomnozero;
          }
        }

		for(j=0;j<4;j++)
		{
		   if((pEncPara->vcpi_fme_cu_en & (0x1<<j)) == 0)
		   pEncPara->vcpi_mrg_cu_en = pEncPara->vcpi_mrg_cu_en & (~(0x1<<j));
		}
	}
	else if ((pEncPara->vcpi_protocol == VEDU_H264) && bIntraFrame)
	{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0x7;
		randomnozero = RadomValue0(randomnozero,3);
		pEncPara->vcpi_intra_cu_en = (pEncPara->vcpi_intra_cu_en & (~0x7)) | randomnozero;
	}
	else if ((pEncPara->vcpi_protocol == VEDU_H264) && !bIntraFrame)
	{
		pEncPara->vcpi_fme_cu_en |= 0x3;
	}

      //Rule.7
    if((pEncPara->vcpi_protocol == VEDU_H265) && (pEncPara->vcpi_iblk_pre_en == 1))
    {
		if((2 <= pic_height%32 && pic_height%32 <= 8) || (16 < pic_height%32 && pic_height%32 <= 24)
		|| (2 <= pic_width%32 && pic_width%32 <= 8) || (16 <pic_width%32 && pic_width%32<= 24))
		{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0x3;
		randomnozero = RadomValue0(randomnozero,2) ;
		pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x3)) | randomnozero;
		}
		else if ((8 < pic_height%32 && pic_height%32 <= 16) || (8 < pic_width%32 && pic_width%32 <= 16))
		{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0x7;
		randomnozero = RadomValue0(randomnozero,3) ;
		pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x7)) | randomnozero;
		}
		else if ((24 < pic_height%32) || (24 < pic_width%32) || (pic_height%32 == 0) || (pic_width%32 == 0))
		{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0xf;
		randomnozero = RadomValue0(randomnozero,4) ;
		pEncPara->vcpi_intra_cu_en =  randomnozero;
		}
	}
	else if ((pEncPara->vcpi_protocol == VEDU_H264) && (pEncPara->vcpi_iblk_pre_en == 1))
	{
		randomnozero = pEncPara->vcpi_intra_cu_en & 0x1;
		randomnozero |= (pEncPara->vcpi_intra_cu_en & 0x4)>>1;
		randomnozero = RadomValue0(randomnozero,2) ;
		pEncPara->vcpi_intra_cu_en = (pEncPara->vcpi_intra_cu_en & (~0x1)) | (randomnozero & 0x1);
		pEncPara->vcpi_intra_cu_en = (pEncPara->vcpi_intra_cu_en & (~0x4)) | ((randomnozero & 0x2)<<1);
	}
	if((pEncPara->vcpi_protocol == VEDU_H264) && (pEncPara->vcpi_pblk_pre_en == 1))
	{
		randomnozero = pEncPara->vcpi_pskp_en & 0x1;
		randomnozero |= (pEncPara->vcpi_inter8x8_en & 0x1)<<1;
		randomnozero = RadomValue0(randomnozero,3) ;
		pEncPara->vcpi_pskp_en = randomnozero&0x1;
		pEncPara->vcpi_inter8x8_en = (pEncPara->vcpi_inter8x8_en & (~0x1)) | ((randomnozero>>1)&0x1);
	}

      //Rule.8
      //shift_rand_num = (random() & 0x0FFFFFFF) % 9;
      //pEncPara->curld_y_stride = MIN(4096*4, pEncPara->curld_y_stride);
      //pEncPara->curld_c_stride = MIN(4096, pEncPara->curld_c_stride);
#if 0
      if(pEncPara->vcpi_store_mode == 0)
      {
        pEncPara->curld_y_stride = (pEncPara->vcpi_oriwidth_pix + 15) /16 * 16;
        pEncPara->curld_c_stride = (pEncPara->vcpi_oriwidth_pix + 15) /16 * 16;
      }
      else if(pEncPara->vcpi_store_mode == 1)
      {
         for( shift_rand_num = 0; shift_rand_num < 9; shift_rand_num++ )
         {
            if((256<< shift_rand_num) > pEncPara->vcpi_oriwidth_pix)
            {
               pEncPara->curld_y_stride = 256<< shift_rand_num;
               pEncPara->curld_c_stride = 256<< shift_rand_num;
               break;
            }
         }
      }
#endif
      //HI_DBG_VENC("&&&&&&&&&&&& pEncPara->curld_y_stride = %d \n",pEncPara->curld_y_stride);
	rand0[0] = 0;
	rand0[1] = 3;
	rand0[2] = 4;
	rand0[3] = 6;
	rand0[4] = 8;
	randomnozero = pEncPara->vcpi_str_fmt;
	pEncPara->vcpi_str_fmt = RadomValue1(rand0,randomnozero,5);
	if(pEncPara->vcpi_str_fmt == 0)
	{
		rand0[0] = 0;
		rand0[1] = 1;
		randomnozero = pEncPara->vcpi_package_sel;
		randomnozero = RadomValue1(rand0,randomnozero,2);
		pEncPara->vcpi_package_sel = randomnozero;
	}
	else if ((pEncPara->vcpi_str_fmt == 3) || (pEncPara->vcpi_str_fmt == 4))
	{
		rand0[0] = 0;
		rand0[1] = 15;
		randomnozero = pEncPara->vcpi_package_sel;
		randomnozero = RadomValue1(rand0,randomnozero,2);
		pEncPara->vcpi_package_sel = randomnozero;
	}
	else if (pEncPara->vcpi_str_fmt == 6)
	{
		rand0[0] = 0;
		rand0[1] = 1;
		rand0[2] = 2;
		rand0[3] = 3;
		randomnozero = pEncPara->vcpi_package_sel;
		randomnozero = RadomValue1(rand0,randomnozero,4);
		pEncPara->vcpi_package_sel = randomnozero;
	}
	else if (pEncPara->vcpi_str_fmt == 8)
	{
		rand0[0] = 0;
		rand0[1] = 13;
		randomnozero = pEncPara->vcpi_package_sel;
		randomnozero = RadomValue1(rand0,randomnozero,2);
		pEncPara->vcpi_package_sel = randomnozero;
	}

	if((pEncPara->vcpi_str_fmt == 0) || (pEncPara->vcpi_str_fmt == 3) || (pEncPara->vcpi_str_fmt == 4))
	{
		pEncPara->curld_y_stride = CLIP3((HI_S32)pEncPara->vcpi_oriwidth_pix,4096,(HI_S32)pEncPara->curld_y_stride);
		pEncPara->curld_c_stride = CLIP3((HI_S32)pEncPara->vcpi_oriwidth_pix,4096,(HI_S32)pEncPara->curld_c_stride);
	}
	else if (pEncPara->vcpi_str_fmt == 6)
	{
		pEncPara->curld_y_stride = CLIP3((HI_S32)(pEncPara->vcpi_oriwidth_pix*2),(4096*2),(HI_S32)(pEncPara->curld_y_stride*2));
	}
	else if (pEncPara->vcpi_str_fmt == 8)
	{
		pEncPara->curld_y_stride = CLIP3((HI_S32)(pEncPara->vcpi_oriwidth_pix*4),(4096*4),(HI_S32)(pEncPara->curld_y_stride*4));
	}

	if(pEncPara->vcpi_str_fmt == 0)
	{
		pEncPara->curld_c_stride = MAX(pEncPara->vcpi_oriwidth_pix,pEncPara->curld_c_stride);
	}
	else if ((pEncPara->vcpi_str_fmt == 3) || (pEncPara->vcpi_str_fmt == 4))
	{
		pEncPara->curld_c_stride = MAX(pEncPara->vcpi_oriwidth_pix/2,pEncPara->curld_c_stride);
	}

	//Rule.9
	//


      //Rule.10
	pEncPara->recst_ystride = MIN(4096, pEncPara->recst_ystride);
	pEncPara->recst_head_stride = MIN(4096, pEncPara->recst_head_stride);
	if(pEncPara->vcpi_rec_cmp_en == 1)
	{
		pEncPara->recst_ystride = MAX(pic_width, pEncPara->recst_ystride);
		if(pEncPara->recst_ystride%64 != 0)  pEncPara->recst_ystride = (pEncPara->recst_ystride/64+1)*64;
		pEncPara->recst_cstride  = pEncPara->recst_ystride;
		if(pEncPara->vcpi_protocol == VEDU_H265)
		{
			if(pic_width%64 == 0)
			pEncPara->recst_head_stride = MAX((pic_width/64)*32,pEncPara->recst_head_stride);
			else
			pEncPara->recst_head_stride = MAX((pic_width/64+1)*32,pEncPara->recst_head_stride);
		}
		else if (pEncPara->vcpi_protocol == VEDU_H264)
		{
			if(pic_width%16 ==0)
			{
			if((pic_width/16)%16 == 0)
			pEncPara->recst_head_stride = MAX((pic_width/16)*2,pEncPara->recst_head_stride);
			else
			pEncPara->recst_head_stride = MAX(((pic_width/16)/16+1)*16*2,pEncPara->recst_head_stride);
			}
			else
			{
				if((pic_width/16+1)%16 == 0)
				pEncPara->recst_head_stride = MAX((pic_width/16+1)*2,pEncPara->recst_head_stride);
				else
				pEncPara->recst_head_stride = MAX(((pic_width/16+1)/16+1)*16*2,pEncPara->recst_head_stride);
			}
		}
		pEncPara->recst_head_stride = pEncPara->recst_head_stride/32*32;
	}
	else
	{
	pEncPara->recst_ystride = MAX(pic_width,pEncPara->recst_ystride);
	pEncPara->recst_ystride = pEncPara->recst_ystride/16*16;
	pEncPara->recst_cstride = pEncPara->recst_ystride;
	//ASSERT(pEncPara->recst_ystride%16 == 0);
	}

	//Rule.12
	if(pEncPara->vcpi_protocol == VEDU_H265)
	{
		pEncPara->sr_weight_0    = CLIP3(0,11,pEncPara->sr_weight_0);
		pEncPara->sr_weight_1    = CLIP3(0,11,pEncPara->sr_weight_1);
		pEncPara->sr_weight_2    = CLIP3(0,11,pEncPara->sr_weight_2);
		pEncPara->vcpi_psw_thr0 = CLIP3(0,0x3fff,pEncPara->vcpi_psw_thr0);
		pEncPara->vcpi_psw_thr1 = CLIP3(0,0x3fff,pEncPara->vcpi_psw_thr1);
		pEncPara->vcpi_psw_thr2 = CLIP3(0,0x3fff,pEncPara->vcpi_psw_thr2);
		pEncPara->high_edge_cnt = CLIP3(0,15,pEncPara->high_edge_cnt);
		pEncPara->high_edge_thr = CLIP3(0,256,pEncPara->high_edge_thr);
		pEncPara->skin_num        = CLIP3(0,256,pEncPara->skin_num);
	}
	//Rule.13
	pEncPara->refld_vcpi2cont_title_en = 1;

	//Rule.14
	pEncPara->vcpi_rect0_vstep = CLIP3(0,1,pEncPara->vcpi_rect0_vstep);
	pEncPara->vcpi_rect0_hstep = CLIP3(0,1,pEncPara->vcpi_rect0_hstep);
	pEncPara->vcpi_rect1_vstep = CLIP3(0,1,pEncPara->vcpi_rect1_vstep);
	pEncPara->vcpi_rect1_hstep = CLIP3(0,1,pEncPara->vcpi_rect1_hstep);
	pEncPara->vcpi_rect2_vstep = CLIP3(0,1,pEncPara->vcpi_rect2_vstep);
	pEncPara->vcpi_rect2_hstep = CLIP3(0,1,pEncPara->vcpi_rect2_hstep);
	pEncPara->vcpi_rect3_vstep = CLIP3(0,1,pEncPara->vcpi_rect3_vstep);
	pEncPara->vcpi_rect3_hstep = CLIP3(0,1,pEncPara->vcpi_rect3_hstep);

      //Rule.15
	pEncPara->strmbuflen = pEncPara->strmbuflen/64*64;
	pEncPara->strmbuflen = MAX(5000000,pEncPara->strmbuflen);
	//ASSERT(pEncPara->strmbuflen%64 == 0);

	//Rule.16
	if(pEncPara->vcpi_protocol == VEDU_H264)
	{
		if((pEncPara->vcpi_intra_cu_en & 0x01) == 1) pEncPara->intra_cu4_mode2_en = 0x01;
		if((pEncPara->vcpi_intra_cu_en & 0x02) == 1) pEncPara->intra_cu8_mode2_en = 0x01;
		if((pEncPara->vcpi_intra_cu_en & 0x04) == 1) pEncPara->intra_cu16_mode2_en = 0x01;
	}

      //Rule.17
	if(pEncPara->vcpi_str_fmt != 0)
	{
		pEncPara->curld_filter_hshift = CLIP3(1,4,pEncPara->curld_filter_hshift);
		pEncPara->curld_filter_hrnd = 1<<(pEncPara->curld_filter_hshift - 1);
		pEncPara->curld_filter_vshift = CLIP3(1,4,pEncPara->curld_filter_vshift);
		pEncPara->curld_filter_vrnd = 1<<(pEncPara->curld_filter_vshift - 1);
	}

      //Rule.18
	if(pEncPara->curld_clip_en == 1)
	{
		pEncPara->clip_chrm_max= MAX(128,pEncPara->clip_chrm_max);
		pEncPara->clip_luma_max= MAX(128,pEncPara->clip_luma_max);
		pEncPara->clip_chrm_min = MIN(128,pEncPara->clip_chrm_min);
		pEncPara->clip_luma_min = MIN(128,pEncPara->clip_luma_min);
	}

	if(pEncPara->vcpi_rgb_clip_en == 1)
	{
		pEncPara->vcpi_rgb_clpmax = MAX(128,pEncPara->vcpi_rgb_clpmax);
		pEncPara->vcpi_rgb_clpmin  = MIN(128,pEncPara->vcpi_rgb_clpmin);
	}

	pEncPara->lambda00 = CLIP3(0,0x1ffff,pEncPara->lambda00);
	pEncPara->lambda01 = CLIP3(0,0x1ffff,pEncPara->lambda01);
	pEncPara->lambda02 = CLIP3(0,0x1ffff,pEncPara->lambda02);
	pEncPara->lambda03 = CLIP3(0,0x1ffff,pEncPara->lambda03);
	pEncPara->lambda04 = CLIP3(0,0x1ffff,pEncPara->lambda04);
	pEncPara->lambda05 = CLIP3(0,0x1ffff,pEncPara->lambda05);
	pEncPara->lambda06 = CLIP3(0,0x1ffff,pEncPara->lambda06);
	pEncPara->lambda07 = CLIP3(0,0x1ffff,pEncPara->lambda07);
	pEncPara->lambda08 = CLIP3(0,0x1ffff,pEncPara->lambda08);
	pEncPara->lambda09 = CLIP3(0,0x1ffff,pEncPara->lambda09);
	pEncPara->lambda10 = CLIP3(0,0x1ffff,pEncPara->lambda10);
	pEncPara->lambda11 = CLIP3(0,0x1ffff,pEncPara->lambda11);
	pEncPara->lambda12 = CLIP3(0,0x1ffff,pEncPara->lambda12);
	pEncPara->lambda13 = CLIP3(0,0x1ffff,pEncPara->lambda13);
	pEncPara->lambda14 = CLIP3(0,0x1ffff,pEncPara->lambda14);
	pEncPara->lambda15 = CLIP3(0,0x1ffff,pEncPara->lambda15);
	pEncPara->lambda16 = CLIP3(0,0x1ffff,pEncPara->lambda16);
	pEncPara->lambda17 = CLIP3(0,0x1ffff,pEncPara->lambda17);
	pEncPara->lambda18 = CLIP3(0,0x1ffff,pEncPara->lambda18);
	pEncPara->lambda19 = CLIP3(0,0x1ffff,pEncPara->lambda19);
	pEncPara->lambda20 = CLIP3(0,0x1ffff,pEncPara->lambda20);
	pEncPara->lambda21 = CLIP3(0,0x1ffff,pEncPara->lambda21);
	pEncPara->lambda22 = CLIP3(0,0x1ffff,pEncPara->lambda22);
	pEncPara->lambda23 = CLIP3(0,0x1ffff,pEncPara->lambda23);
	pEncPara->lambda24 = CLIP3(0,0x1ffff,pEncPara->lambda24);
	pEncPara->lambda25 = CLIP3(0,0x1ffff,pEncPara->lambda25);
	pEncPara->lambda26 = CLIP3(0,0x1ffff,pEncPara->lambda26);
	pEncPara->lambda27 = CLIP3(0,0x1ffff,pEncPara->lambda27);
	pEncPara->lambda28 = CLIP3(0,0x1ffff,pEncPara->lambda28);
	pEncPara->lambda29 = CLIP3(0,0x1ffff,pEncPara->lambda29);
	pEncPara->lambda30 = CLIP3(0,0x1ffff,pEncPara->lambda30);
	pEncPara->lambda31 = CLIP3(0,0x1ffff,pEncPara->lambda31);
	pEncPara->lambda32 = CLIP3(0,0x1ffff,pEncPara->lambda32);
	pEncPara->lambda33 = CLIP3(0,0x1ffff,pEncPara->lambda33);
	pEncPara->lambda34 = CLIP3(0,0x1ffff,pEncPara->lambda34);
	pEncPara->lambda35 = CLIP3(0,0x1ffff,pEncPara->lambda35);
	pEncPara->lambda36 = CLIP3(0,0x1ffff,pEncPara->lambda36);
	pEncPara->lambda37 = CLIP3(0,0x1ffff,pEncPara->lambda37);
	pEncPara->lambda38 = CLIP3(0,0x1ffff,pEncPara->lambda38);
	pEncPara->lambda39 = CLIP3(0,0x1ffff,pEncPara->lambda39);

	pEncPara->lambda40 = CLIP3(0,0xffff,pEncPara->lambda40);
	pEncPara->lambda41 = CLIP3(0,0xffff,pEncPara->lambda41);
	pEncPara->lambda42 = CLIP3(0,0xffff,pEncPara->lambda42);
	pEncPara->lambda43 = CLIP3(0,0xffff,pEncPara->lambda43);
	pEncPara->lambda44 = CLIP3(0,0xffff,pEncPara->lambda44);
	pEncPara->lambda45 = CLIP3(0,0xffff,pEncPara->lambda45);
	pEncPara->lambda46 = CLIP3(0,0xffff,pEncPara->lambda46);
	pEncPara->lambda47 = CLIP3(0,0xffff,pEncPara->lambda47);
	pEncPara->lambda48 = CLIP3(0,0xffff,pEncPara->lambda48);
	pEncPara->lambda49 = CLIP3(0,0xffff,pEncPara->lambda49);
	pEncPara->lambda50 = CLIP3(0,0xffff,pEncPara->lambda50);
	pEncPara->lambda51 = CLIP3(0,0xffff,pEncPara->lambda51);
	pEncPara->lambda52 = CLIP3(0,0xffff,pEncPara->lambda52);
	pEncPara->lambda53 = CLIP3(0,0xffff,pEncPara->lambda53);
	pEncPara->lambda54 = CLIP3(0,0xffff,pEncPara->lambda54);
	pEncPara->lambda55 = CLIP3(0,0xffff,pEncPara->lambda55);
	pEncPara->lambda56 = CLIP3(0,0xffff,pEncPara->lambda56);
	pEncPara->lambda57 = CLIP3(0,0xffff,pEncPara->lambda57);
	pEncPara->lambda58 = CLIP3(0,0xffff,pEncPara->lambda58);
	pEncPara->lambda59 = CLIP3(0,0xffff,pEncPara->lambda59);
	pEncPara->lambda60 = CLIP3(0,0xffff,pEncPara->lambda60);
	pEncPara->lambda61 = CLIP3(0,0xffff,pEncPara->lambda61);
	pEncPara->lambda62 = CLIP3(0,0xffff,pEncPara->lambda62);
	pEncPara->lambda63 = CLIP3(0,0xffff,pEncPara->lambda63);
	pEncPara->lambda64 = CLIP3(0,0xffff,pEncPara->lambda64);
	pEncPara->lambda65 = CLIP3(0,0xffff,pEncPara->lambda65);
	pEncPara->lambda66 = CLIP3(0,0xffff,pEncPara->lambda66);
	pEncPara->lambda67 = CLIP3(0,0xffff,pEncPara->lambda67);
	pEncPara->lambda68 = CLIP3(0,0xffff,pEncPara->lambda68);
	pEncPara->lambda69 = CLIP3(0,0xffff,pEncPara->lambda69);
	pEncPara->lambda70 = CLIP3(0,0xffff,pEncPara->lambda70);
	pEncPara->lambda71 = CLIP3(0,0xffff,pEncPara->lambda71);
	pEncPara->lambda72 = CLIP3(0,0xffff,pEncPara->lambda72);
	pEncPara->lambda73 = CLIP3(0,0xffff,pEncPara->lambda73);
	pEncPara->lambda74 = CLIP3(0,0xffff,pEncPara->lambda74);
	pEncPara->lambda75 = CLIP3(0,0xffff,pEncPara->lambda75);
	pEncPara->lambda76 = CLIP3(0,0xffff,pEncPara->lambda76);
	pEncPara->lambda77 = CLIP3(0,0xffff,pEncPara->lambda77);
	pEncPara->lambda78 = CLIP3(0,0xffff,pEncPara->lambda78);
	pEncPara->lambda79 = CLIP3(0,0xffff,pEncPara->lambda79);

     //Rule.20

     //Rule.21
	pEncPara->norm32_tr1_denois_max_num  = 	CLIP3(0,8,pEncPara->norm32_tr1_denois_max_num);
	pEncPara->norm32_coeff_protect_num  = 	CLIP3(0,1023,pEncPara->norm32_coeff_protect_num);
	pEncPara->norm16_tr1_denois_max_num  = 	CLIP3(0,8,pEncPara->norm16_tr1_denois_max_num);
	pEncPara->norm16_coeff_protect_num  = 	CLIP3(0,255,pEncPara->norm16_coeff_protect_num);

	pEncPara->skin32_tr1_denois_max_num  = 	CLIP3(0,8,pEncPara->skin32_tr1_denois_max_num);
	pEncPara->skin32_coeff_protect_num   = 	CLIP3(0,1023,pEncPara->skin32_coeff_protect_num);
	pEncPara->skin16_tr1_denois_max_num  = 	CLIP3(0,8,pEncPara->skin16_tr1_denois_max_num);
	pEncPara->skin16_coeff_protect_num   = 	CLIP3(0,255,pEncPara->skin16_coeff_protect_num);

	pEncPara->static32_tr1_denois_max_num  = 	CLIP3(0,8,pEncPara->static32_tr1_denois_max_num);
	pEncPara->static32_coeff_protect_num  = 	CLIP3(0,1023,pEncPara->static32_coeff_protect_num);
	pEncPara->static16_tr1_denois_max_num  = 	CLIP3(0,8,pEncPara->static16_tr1_denois_max_num);
	pEncPara->static16_coeff_protect_num  = 	CLIP3(0,255,pEncPara->static16_coeff_protect_num);

	pEncPara->hedge32_tr1_denois_max_num  =	CLIP3(0,8,pEncPara->hedge32_tr1_denois_max_num);
	pEncPara->hedge32_coeff_protect_num  = 	CLIP3(0,1023,pEncPara->hedge32_coeff_protect_num);
	pEncPara->hedge16_tr1_denois_max_num  =	CLIP3(0,8,pEncPara->hedge16_tr1_denois_max_num);
	pEncPara->hedge16_coeff_protect_num  = 	CLIP3(0,255,pEncPara->hedge16_coeff_protect_num);

      //Rule.22
	if(pEncPara->vcpi_multislc_en == 1)
	{
	if(pEncPara->vcpi_protocol == VEDU_H265)
	{
	if((pEncPara->vcpi_imgheight_pix%64 == 0)&&(pEncPara->vcpi_slice_size < (((pic_height/64)+15)>>4)))
	{
	get_random_bytes(&randomvalue,sizeof(int));
	HI_WARN_VENC("randomvalue:%d\n",randomvalue);
	pEncPara->vcpi_slice_size =   (randomvalue & 0x0FFFFFFF)  % ((pic_height/64)-(((pic_height/64)+15)>>4) +1) + (((pic_height/64)+15)>>4);
	}
	else if((pEncPara->vcpi_imgheight_pix%64 != 0)&&(pEncPara->vcpi_slice_size <((((pic_height/64)+1)+15)>>4)))
	{
	get_random_bytes(&randomvalue,sizeof(int));
	HI_WARN_VENC("randomvalue:%d\n",randomvalue);
	pEncPara->vcpi_slice_size =   (randomvalue & 0x0FFFFFFF)  % ((pic_height/64+1)-((((pic_height/64)+1)+15)>>4)+1) +((((pic_height/64)+1)+15)>>4);
	}
	}
	else if(pEncPara->vcpi_protocol == VEDU_H264)
	{
	if((pEncPara->vcpi_imgheight_pix%16 == 0)&&(pEncPara->vcpi_slice_size <(((pic_height/16)+15)>>4) ))
	{
	get_random_bytes(&randomvalue,sizeof(int));
	HI_WARN_VENC("randomvalue:%d\n",randomvalue);
	pEncPara->vcpi_slice_size =   (randomvalue & 0x0FFFFFFF)  % ((pic_height/16)-(((pic_height/16)+15)>>4) +1) + (((pic_height/16)+15)>>4);
	}
	else if((pEncPara->vcpi_imgheight_pix%16 != 0)&&(pEncPara->vcpi_slice_size < ((((pic_height/16)+1)+15)>>4)))
	{
	get_random_bytes(&randomvalue,sizeof(int));
	HI_WARN_VENC("randomvalue:%d\n",randomvalue);
	pEncPara->vcpi_slice_size =   (randomvalue & 0x0FFFFFFF)  % ((pic_height/16+1)-((((pic_height/16)+1)+15)>>4)+1) +((((pic_height/16)+1)+15)>>4);
	}
	}
	HI_INFO_VENC("pEncPara->vcpi_slice_size = %d \n", pEncPara->vcpi_slice_size);
	}

      //Rule.24
	if(pEncPara->vcpi_roi_en == 1)
	{
	if(pEncPara->region0en == 1)
	{
	pEncPara->start0_roistartx = MIN(pic_width/16, pEncPara->start0_roistartx);
	pEncPara->start0_roistarty = MIN(pic_height/16, pEncPara->start0_roistarty);
	}
	if(pEncPara->region1en == 1)
	{
	pEncPara->start1_roistartx = MIN(pic_width/16, pEncPara->start1_roistartx);
	pEncPara->start1_roistarty = MIN(pic_height/16, pEncPara->start1_roistarty);
	}
	if(pEncPara->region2en == 1)
	{
	pEncPara->start2_roistartx = MIN(pic_width/16, pEncPara->start2_roistartx);
	pEncPara->start2_roistarty = MIN(pic_height/16, pEncPara->start2_roistarty);
	}
	if(pEncPara->region3en == 1)
	{
	pEncPara->start3_roistartx = MIN(pic_width/16, pEncPara->start3_roistartx);
	pEncPara->start3_roistarty = MIN(pic_height/16, pEncPara->start3_roistarty);
	}
	if(pEncPara->region4en == 1)
	{
	pEncPara->start4_roistartx = MIN(pic_width/16, pEncPara->start4_roistartx);
	pEncPara->start4_roistarty = MIN(pic_height/16, pEncPara->start4_roistarty);
	}
	if(pEncPara->region5en == 1)
	{
	pEncPara->start5_roistartx = MIN(pic_width/16, pEncPara->start5_roistartx);
	pEncPara->start5_roistarty = MIN(pic_height/16, pEncPara->start5_roistarty);
	}
	if(pEncPara->region6en == 1)
	{
	pEncPara->start6_roistartx = MIN(pic_width/16, pEncPara->start6_roistartx);
	pEncPara->start6_roistarty = MIN(pic_height/16, pEncPara->start6_roistarty);
	}
	if(pEncPara->region7en == 1)
	{
	pEncPara->start7_roistartx = MIN(pic_width/16, pEncPara->start7_roistartx);
	pEncPara->start7_roistarty = MIN(pic_height/16, pEncPara->start7_roistarty);
	}
	}

     //Rule.25
	if(pEncPara->vcpi_roi_en)
	{
		HI_DBG_VENC("1 pEncPara->roiqp0:%d\n",pEncPara->roiqp0);
		if(pEncPara->region0en == 1)
		{
			if(pEncPara->absqp0 == 0)  pEncPara->roiqp0 = CLIP3(-64, 63, pEncPara->roiqp0);
			else                                  pEncPara->roiqp0 = CLIP3(0, 51, pEncPara->roiqp0);
		}
		HI_DBG_VENC("2 pEncPara->roiqp0:%d\n",pEncPara->roiqp0);

		if(pEncPara->region1en == 1)
		{
			if(pEncPara->absqp1 == 0)  pEncPara->roiqp1 = CLIP3(-64, 63, pEncPara->roiqp1);
			else                                  pEncPara->roiqp1= CLIP3(0, 51, pEncPara->roiqp1);
		}
		if(pEncPara->region2en == 1)
		{
			if(pEncPara->absqp2 == 0)  pEncPara->roiqp2 = CLIP3(-64, 63, pEncPara->roiqp2);
			else                                  pEncPara->roiqp2 = CLIP3(0, 51, pEncPara->roiqp2);
		}
		if(pEncPara->region3en == 1)
		{
			if(pEncPara->absqp3 == 0)  pEncPara->roiqp3 = CLIP3(-64, 63, pEncPara->roiqp3);
			else                                  pEncPara->roiqp3 = CLIP3(0, 51, pEncPara->roiqp3);
		}
		if(pEncPara->region4en == 1)
		{
			if(pEncPara->absqp4 == 0)  pEncPara->roiqp4 = CLIP3(-64, 63, pEncPara->roiqp4);
			else                                  pEncPara->roiqp4 = CLIP3(0, 51, pEncPara->roiqp4);
		}
		if(pEncPara->region5en == 1)
		{
			if(pEncPara->absqp5 == 0)  pEncPara->roiqp5 = CLIP3(-64, 63, pEncPara->roiqp5);
			else                                  pEncPara->roiqp5 = CLIP3(0, 51, pEncPara->roiqp5);
		}
		if(pEncPara->region6en == 1)
		{
			if(pEncPara->absqp6 == 0)  pEncPara->roiqp6 = CLIP3(-64, 63, pEncPara->roiqp6);
			else                                  pEncPara->roiqp6 = CLIP3(0, 51, pEncPara->roiqp6);
		}
		if(pEncPara->region7en == 1)
		{
			if(pEncPara->absqp7 == 0)  pEncPara->roiqp7 = CLIP3(-64, 63, pEncPara->roiqp7);
			else                                  pEncPara->roiqp7 = CLIP3(0, 51, pEncPara->roiqp7);
		}
	}

	//Rule.26
	if((pEncPara->vcpi_roi_en == 1) && (pEncPara->vcpi_protocol == VEDU_H265))
	{
		if((pEncPara->region0en | pEncPara->region1en | pEncPara->region2en | pEncPara->region3en | pEncPara->region4en | pEncPara->region5en | pEncPara->region6en | pEncPara->region7en) != 0)
		{
			if((((pEncPara->region0en == 1) && (pEncPara->start0_roistartx%2 == 0) && (pEncPara->start0_roistarty%2 == 0) && (pEncPara->size0_roiwidth%2 == 0) &&
			(pEncPara->size0_roiheight%2 == 0)) || (pEncPara->region0en == 0))
			&& (((pEncPara->region1en == 1) && (pEncPara->start1_roistartx%2 == 0) && (pEncPara->start1_roistarty%2 == 0) && (pEncPara->size1_roiwidth%2 == 0) &&
			(pEncPara->size1_roiheight%2 == 0)) || (pEncPara->region1en == 0))
			&& (((pEncPara->region2en == 1) && (pEncPara->start2_roistartx%2 == 0) && (pEncPara->start2_roistarty%2 == 0) && (pEncPara->size2_roiwidth%2 == 0) &&
			(pEncPara->size2_roiheight%2 == 0)) || (pEncPara->region2en == 0))
			&& (((pEncPara->region3en == 1) && (pEncPara->start3_roistartx%2 == 0) && (pEncPara->start3_roistarty%2 == 0) && (pEncPara->size3_roiwidth%2 == 0) &&
			(pEncPara->size3_roiheight%2 == 0)) || (pEncPara->region3en == 0))
			&& (((pEncPara->region4en == 1) && (pEncPara->start4_roistartx%2 == 0) && (pEncPara->start4_roistarty%2 == 0) && (pEncPara->size4_roiwidth%2 == 0) &&
			(pEncPara->size4_roiheight%2 == 0)) || (pEncPara->region4en == 0))
			&& (((pEncPara->region5en == 1) && (pEncPara->start5_roistartx%2 == 0) && (pEncPara->start5_roistarty%2 == 0) && (pEncPara->size5_roiwidth%2 == 0) &&
			(pEncPara->size5_roiheight%2 == 0)) || (pEncPara->region5en == 0))
			&& (((pEncPara->region6en == 1) && (pEncPara->start6_roistartx%2 == 0) && (pEncPara->start6_roistarty%2 == 0) && (pEncPara->size6_roiwidth%2 == 0) &&
			(pEncPara->size6_roiheight%2 == 0)) || (pEncPara->region6en == 0))
			&& (((pEncPara->region7en == 1) && (pEncPara->start7_roistartx%2 == 0) && (pEncPara->start7_roistarty%2 == 0) && (pEncPara->size7_roiwidth%2 == 0) &&
			(pEncPara->size7_roiheight%2 == 0)) || (pEncPara->region7en == 0)))
			{
				if(bIntraFrame)
				{
					randomnozero = pEncPara->vcpi_intra_cu_en & 0xf;
					randomnozero = RadomValue0(randomnozero,4) ;
					pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0xf)) | randomnozero;
				}
				else if(!bIntraFrame)
				{
					rand0[0] = 1;
					rand0[1] = 2;
					rand0[2] = 3;
					randomnozero = (pEncPara->vcpi_fme_cu_en & 0x4)>>2;
					randomnozero |= (pEncPara->vcpi_intra_cu_en& 0x8)>>2;
					randomnozero = RadomValue1(rand0,randomnozero,3);
					pEncPara->vcpi_fme_cu_en =  (pEncPara->vcpi_fme_cu_en & (~0x04)) | ((randomnozero&0x01)<<2);
					pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x08)) | ((randomnozero&0x02)<<2);
					if(pEncPara->vcpi_iblk_pre_en==1)
					{
						pEncPara->vcpi_intra_cu_en = pEncPara->vcpi_intra_cu_en | 0x08;
					}
					if(pEncPara->vcpi_pblk_pre_en==1)
					{
						pEncPara->vcpi_fme_cu_en = pEncPara->vcpi_fme_cu_en | 0x04;
					}
				}
				if(((pEncPara->region0en == 1) &&(pEncPara->region0keep== 1)) || ((pEncPara->region1en == 1) &&(pEncPara->region1keep== 1))
				||((pEncPara->region2en == 1) &&(pEncPara->region2keep== 1)) || ((pEncPara->region3en == 1) &&(pEncPara->region3keep== 1))
				||((pEncPara->region4en == 1) &&(pEncPara->region4keep== 1)) || ((pEncPara->region5en == 1) &&(pEncPara->region5keep== 1))
				||((pEncPara->region6en == 1) &&(pEncPara->region6keep== 1)) || ((pEncPara->region7en == 1) &&(pEncPara->region7keep== 1)))
				{
					pEncPara->vcpi_fme_cu_en =  pEncPara->vcpi_fme_cu_en | 0x4;
					pEncPara->vcpi_mrg_cu_en =  pEncPara->vcpi_mrg_cu_en | 0x4;
					if(((((pEncPara->vcpi_imgwidth_pix+7)>>3)<<3)%16!=0) || ((((pEncPara->vcpi_imgheight_pix+7)>>3)<<3)%16!=0))
					{
						pEncPara->vcpi_fme_cu_en =  pEncPara->vcpi_fme_cu_en | 0x1;
						pEncPara->vcpi_mrg_cu_en =  pEncPara->vcpi_mrg_cu_en | 0x1;
					}
					else if(((((pEncPara->vcpi_imgwidth_pix+7)>>3)<<3)%32!=0) || ((((pEncPara->vcpi_imgheight_pix+7)>>3)<<3)%32!=0))
					{
						rand0[0] = 0x3;
						rand0[1] = 0xc;
						rand0[2] = 0xf;
						randomnozero = (pEncPara->vcpi_mrg_cu_en & 0x1);
						randomnozero |= (pEncPara->vcpi_fme_cu_en& 0x1)<<1;
						randomnozero |= (pEncPara->vcpi_mrg_cu_en& 0x2)<<2;
						randomnozero |= (pEncPara->vcpi_fme_cu_en& 0x2)<<3;
						randomnozero = RadomValue1(rand0,randomnozero,3);
						pEncPara->vcpi_mrg_cu_en =  (pEncPara->vcpi_mrg_cu_en & (~0x01)) | (randomnozero&0x01);
						pEncPara->vcpi_fme_cu_en =  (pEncPara->vcpi_fme_cu_en & (~0x01)) | ((randomnozero&0x02)>>1);
						pEncPara->vcpi_mrg_cu_en =  (pEncPara->vcpi_mrg_cu_en & (~0x02)) | ((randomnozero&0x04)>>1);
						pEncPara->vcpi_fme_cu_en =  (pEncPara->vcpi_fme_cu_en & (~0x02)) | ((randomnozero&0x08)>>2);
					}
					if(!bIntraFrame)
					{
						pEncPara->vcpi_iblk_pre_en = 0;
					}
				}
			}
			else
			{
				if(bIntraFrame)
				{
					randomnozero = pEncPara->vcpi_intra_cu_en & 0x7;
					randomnozero = RadomValue0(randomnozero,3) ;
					pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x7)) | randomnozero;
				}
				else if(!bIntraFrame)
				{
					rand0[0] = 1;
					rand0[1] = 2;
					rand0[2] = 3;
					randomnozero = (pEncPara->vcpi_fme_cu_en & 0x2)>>1;
					randomnozero |= (pEncPara->vcpi_intra_cu_en& 0x4)>>1;
					randomnozero = RadomValue1(rand0,randomnozero,3);
					pEncPara->vcpi_fme_cu_en =  (pEncPara->vcpi_fme_cu_en & (~0x02)) | ((randomnozero&0x01)<<1);
					pEncPara->vcpi_intra_cu_en =  (pEncPara->vcpi_intra_cu_en & (~0x04)) | ((randomnozero&0x02)<<1);
					if(pEncPara->vcpi_iblk_pre_en==1)
					{
						pEncPara->vcpi_intra_cu_en = pEncPara->vcpi_intra_cu_en | 0x04;
					}
					if(pEncPara->vcpi_pblk_pre_en==1)
					{
						pEncPara->vcpi_fme_cu_en = pEncPara->vcpi_fme_cu_en | 0x02;
					}
				}

				if(((pEncPara->region0en == 1) &&(pEncPara->region0keep== 1)) || ((pEncPara->region1en == 1) &&(pEncPara->region1keep== 1))
				||((pEncPara->region2en == 1) &&(pEncPara->region2keep== 1)) || ((pEncPara->region3en == 1) &&(pEncPara->region3keep== 1))
				||((pEncPara->region4en == 1) &&(pEncPara->region4keep== 1)) || ((pEncPara->region5en == 1) &&(pEncPara->region5keep== 1))
				||((pEncPara->region6en == 1) &&(pEncPara->region6keep== 1)) || ((pEncPara->region7en == 1) &&(pEncPara->region7keep== 1)))
				{
					pEncPara->vcpi_fme_cu_en =  pEncPara->vcpi_fme_cu_en | 0x2;
					pEncPara->vcpi_mrg_cu_en =  pEncPara->vcpi_mrg_cu_en | 0x2;
					if(((((pEncPara->vcpi_imgwidth_pix+7)>>3)<<3)%16!=0) || ((((pEncPara->vcpi_imgheight_pix+7)>>3)<<3)%16!=0))
					{
						pEncPara->vcpi_fme_cu_en =  pEncPara->vcpi_fme_cu_en | 0x1;
						pEncPara->vcpi_mrg_cu_en =  pEncPara->vcpi_mrg_cu_en | 0x1;
					}
					if(!bIntraFrame)
					{
						pEncPara->vcpi_iblk_pre_en = 0;
					}
				}
			}
		}
	}

    //Rule.27
    /*
    if(pEncPara->vcpi_roi_en == 1)
    {
      if((Total_Frame_Num % Total_Gop) == 0)
      {
        pEncPara->region0keep = 0;
        pEncPara->region1keep = 0;
        pEncPara->region2keep = 0;
        pEncPara->region3keep = 0;
        pEncPara->region4keep = 0;
        pEncPara->region5keep = 0;
        pEncPara->region6keep = 0;
        pEncPara->region7keep = 0;
      }
    }
    */
    //Rule.28
    pEncPara->vcpi_coeff_ry   = CLIP3(-16383,16383,pEncPara->vcpi_coeff_ry);
    pEncPara->vcpi_coeff_gy  = CLIP3(-16383,16383,pEncPara->vcpi_coeff_gy);
    pEncPara->vcpi_coeff_by  = CLIP3(-16383,16383,pEncPara->vcpi_coeff_by);
    pEncPara->vcpi_coeff_rcb = CLIP3(-16383,16383,pEncPara->vcpi_coeff_rcb);
    pEncPara->vcpi_coeff_gcb = CLIP3(-16383,16383,pEncPara->vcpi_coeff_gcb);
    pEncPara->vcpi_coeff_bcb = CLIP3(-16383,16383,pEncPara->vcpi_coeff_bcb);
    pEncPara->vcpi_coeff_rcr  = CLIP3(-16383,16383,pEncPara->vcpi_coeff_rcr);
    pEncPara->vcpi_coeff_gcr = CLIP3(-16383,16383,pEncPara->vcpi_coeff_gcr);
    pEncPara->vcpi_coeff_bcr = CLIP3(-16383,16383,pEncPara->vcpi_coeff_bcr);

   //Rule.29
    if(pEncPara->vcpi_multislc_en == 1)
    {
      pEncPara->vcpi_slcspilt_mod = 1;
    }
    //Rule.30
    if (pEncPara->tmv_en == 1)
    {
      pEncPara->vcpi_tmv_wr_rd_avail  =  3 ;
    }
    //Rule.31
    if((pEncPara->vcpi_roi_en == 1) && (pEncPara->vcpi_protocol == VEDU_H265))
    {
        if(((pEncPara->region0en == 1) &&(pEncPara->region0keep== 1)) || ((pEncPara->region1en == 1) &&(pEncPara->region1keep== 1))
          ||((pEncPara->region2en == 1) &&(pEncPara->region2keep== 1)) || ((pEncPara->region3en == 1) &&(pEncPara->region3keep== 1))
          ||((pEncPara->region4en == 1) &&(pEncPara->region4keep== 1)) || ((pEncPara->region5en == 1) &&(pEncPara->region5keep== 1))
          ||((pEncPara->region6en == 1) &&(pEncPara->region6keep== 1)) || ((pEncPara->region7en == 1) &&(pEncPara->region7keep== 1)))
            {
                pEncPara->vcpi_sao_chroma =  0;
                pEncPara->vcpi_sao_luma    =  0;
            }
     }
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
