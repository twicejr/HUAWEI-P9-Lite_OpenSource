
#ifndef __VCM_DW9714_LITEON_ALICE_H__

#define __VCM_DW9714_LITEON_ALICE_H__

/*vcm_type*/
VCM_DW9714_Liteon,
/*vcm_bits*/
9,     
/*vcm_id*/
0x18,  
/*moveLensAddr*/
{0,0},             /* moveLensAddr can be ommitted for DW9714 */
/*offsetInit*/
0,                 /* maybe different in each AF mode */
/*fullRange*/
1023,              /* maybe different in each AF mode */
/*infiniteDistance*/
0x50,              /* should be calibrated */
/*normalDistanceEnd*/
0x280,
/*normalStep*/
0x10,              /* coarse step */
/*normalStrideRatio*/
0x20,
/*videoDistanceEnd*/
0x200,
/*videoStep*/
0x10,
/*videoStrideRatio*/
0x20,
/*strideOffset*/
0x90,              /* large stride will start at (infiniteDistance+videoStrideOffset), this value must common multiple of videoStep and normalStep*/
/*coarseStep*/
0,                 /*coarseStep will be calculated by other params*/
/*fineStep*/
0,                 /*fineStep will be calculated by other params*/
/*motorResTime*/
10,
/*motorDelayTime*/
12,
/*strideDivideOffset*/
0x60,
/*startCurrentOffset*/
0x40,
/*moveRange*/
RANGE_NORMAL,
/*get_vcm_otp*/
NULL,
/*fastShotOffset*/  /*added for fastShot mode focus*/
0x68,
#endif //__VCM_DW9714_LITEON_ALICE_H__

