/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7omB5iYtHEGPqMDW7TpB3q4yvDckVri1GoBL4gKI3k0M86wMC5hMD5fQLRyjt
hU2r3zwHGUpypsl5Aklc5rJ7cjsDpTjznn0jjXlrN89aaFZOY/051csXzQFNfMCqJ3wIsAFW
FQQoy+kRZKGxSbRSkLYLXMB4zin9S1CRGHwcvgkJsBkUSD0k8ttbA/ZOxcYSCg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************
*
* Copyright (c) 2010 HUAWEI - All Rights Reserved
*
* File: $VP8_vfmw.c$
* Date: $2010/07/28$
* Revision: $v1.0$
* Purpose: VP8 decoder file
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ====== 
* 2010/07/28       l48485            Original
*
* Dependencies:
*
************************************************************************/
#include    "vp8.h"
#include    "syntax.h"

#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"

#ifdef VP8_ENABLE
const UINT8 default_coef_probs [4] [8] [3] [11] =
{
    {
        {
            { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
            { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
            { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128}
        },
        {
            { 253, 136, 254, 255, 228, 219, 128, 128, 128, 128, 128},
            { 189, 129, 242, 255, 227, 213, 255, 219, 128, 128, 128},
            { 106, 126, 227, 252, 214, 209, 255, 255, 128, 128, 128}
        },
        {
            { 1, 98, 248, 255, 236, 226, 255, 255, 128, 128, 128},
            { 181, 133, 238, 254, 221, 234, 255, 154, 128, 128, 128},
            { 78, 134, 202, 247, 198, 180, 255, 219, 128, 128, 128}
        },
        {
            { 1, 185, 249, 255, 243, 255, 128, 128, 128, 128, 128},
            { 184, 150, 247, 255, 236, 224, 128, 128, 128, 128, 128},
            { 77, 110, 216, 255, 236, 230, 128, 128, 128, 128, 128}
        },
        {
            { 1, 101, 251, 255, 241, 255, 128, 128, 128, 128, 128},
            { 170, 139, 241, 252, 236, 209, 255, 255, 128, 128, 128},
            { 37, 116, 196, 243, 228, 255, 255, 255, 128, 128, 128}
        },
        {
            { 1, 204, 254, 255, 245, 255, 128, 128, 128, 128, 128},
            { 207, 160, 250, 255, 238, 128, 128, 128, 128, 128, 128},
            { 102, 103, 231, 255, 211, 171, 128, 128, 128, 128, 128}
        },
        {
            { 1, 152, 252, 255, 240, 255, 128, 128, 128, 128, 128},
            { 177, 135, 243, 255, 234, 225, 128, 128, 128, 128, 128},
            { 80, 129, 211, 255, 194, 224, 128, 128, 128, 128, 128}
        },
        {
            { 1, 1, 255, 128, 128, 128, 128, 128, 128, 128, 128},
            { 246, 1, 255, 128, 128, 128, 128, 128, 128, 128, 128},
            { 255, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128}
        }
    },
    {
        {
            { 198, 35, 237, 223, 193, 187, 162, 160, 145, 155, 62},
            { 131, 45, 198, 221, 172, 176, 220, 157, 252, 221, 1},
            { 68, 47, 146, 208, 149, 167, 221, 162, 255, 223, 128}
        },
        {
            { 1, 149, 241, 255, 221, 224, 255, 255, 128, 128, 128},
            { 184, 141, 234, 253, 222, 220, 255, 199, 128, 128, 128},
            { 81, 99, 181, 242, 176, 190, 249, 202, 255, 255, 128}
        },
        {
            { 1, 129, 232, 253, 214, 197, 242, 196, 255, 255, 128},
            { 99, 121, 210, 250, 201, 198, 255, 202, 128, 128, 128},
            { 23, 91, 163, 242, 170, 187, 247, 210, 255, 255, 128}
        },
        {
            { 1, 200, 246, 255, 234, 255, 128, 128, 128, 128, 128},
            { 109, 178, 241, 255, 231, 245, 255, 255, 128, 128, 128},
            { 44, 130, 201, 253, 205, 192, 255, 255, 128, 128, 128}
        },
        {
            { 1, 132, 239, 251, 219, 209, 255, 165, 128, 128, 128},
            { 94, 136, 225, 251, 218, 190, 255, 255, 128, 128, 128},
            { 22, 100, 174, 245, 186, 161, 255, 199, 128, 128, 128}
        },
        {
            { 1, 182, 249, 255, 232, 235, 128, 128, 128, 128, 128},
            { 124, 143, 241, 255, 227, 234, 128, 128, 128, 128, 128},
            { 35, 77, 181, 251, 193, 211, 255, 205, 128, 128, 128}
        },
        {
            { 1, 157, 247, 255, 236, 231, 255, 255, 128, 128, 128},
            { 121, 141, 235, 255, 225, 227, 255, 255, 128, 128, 128},
            { 45, 99, 188, 251, 195, 217, 255, 224, 128, 128, 128}
        },
        {
            { 1, 1, 251, 255, 213, 255, 128, 128, 128, 128, 128},
            { 203, 1, 248, 255, 255, 128, 128, 128, 128, 128, 128},
            { 137, 1, 177, 255, 224, 255, 128, 128, 128, 128, 128}
        }
    },
    {
        {
            { 253, 9, 248, 251, 207, 208, 255, 192, 128, 128, 128},
            { 175, 13, 224, 243, 193, 185, 249, 198, 255, 255, 128},
            { 73, 17, 171, 221, 161, 179, 236, 167, 255, 234, 128}
        },
        {
            { 1, 95, 247, 253, 212, 183, 255, 255, 128, 128, 128},
            { 239, 90, 244, 250, 211, 209, 255, 255, 128, 128, 128},
            { 155, 77, 195, 248, 188, 195, 255, 255, 128, 128, 128}
        },
        {
            { 1, 24, 239, 251, 218, 219, 255, 205, 128, 128, 128},
            { 201, 51, 219, 255, 196, 186, 128, 128, 128, 128, 128},
            { 69, 46, 190, 239, 201, 218, 255, 228, 128, 128, 128}
        },
        {
            { 1, 191, 251, 255, 255, 128, 128, 128, 128, 128, 128},
            { 223, 165, 249, 255, 213, 255, 128, 128, 128, 128, 128},
            { 141, 124, 248, 255, 255, 128, 128, 128, 128, 128, 128}
        },
        {
            { 1, 16, 248, 255, 255, 128, 128, 128, 128, 128, 128},
            { 190, 36, 230, 255, 236, 255, 128, 128, 128, 128, 128},
            { 149, 1, 255, 128, 128, 128, 128, 128, 128, 128, 128}
        },
        {
            { 1, 226, 255, 128, 128, 128, 128, 128, 128, 128, 128},
            { 247, 192, 255, 128, 128, 128, 128, 128, 128, 128, 128},
            { 240, 128, 255, 128, 128, 128, 128, 128, 128, 128, 128}
        },
        {
            { 1, 134, 252, 255, 255, 128, 128, 128, 128, 128, 128},
            { 213, 62, 250, 255, 255, 128, 128, 128, 128, 128, 128},
            { 55, 93, 255, 128, 128, 128, 128, 128, 128, 128, 128}
        },
        {
            { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
            { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
            { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128}
        }
    },
    {
        {
            { 202, 24, 213, 235, 186, 191, 220, 160, 240, 175, 255},
            { 126, 38, 182, 232, 169, 184, 228, 174, 255, 187, 128},
            { 61, 46, 138, 219, 151, 178, 240, 170, 255, 216, 128}
        },
        {
            { 1, 112, 230, 250, 199, 191, 247, 159, 255, 255, 128},
            { 166, 109, 228, 252, 211, 215, 255, 174, 128, 128, 128},
            { 39, 77, 162, 232, 172, 180, 245, 178, 255, 255, 128}
        },
        {
            { 1, 52, 220, 246, 198, 199, 249, 220, 255, 255, 128},
            { 124, 74, 191, 243, 183, 193, 250, 221, 255, 255, 128},
            { 24, 71, 130, 219, 154, 170, 243, 182, 255, 255, 128}
        },
        {
            { 1, 182, 225, 249, 219, 240, 255, 224, 128, 128, 128},
            { 149, 150, 226, 252, 216, 205, 255, 171, 128, 128, 128},
            { 28, 108, 170, 242, 183, 194, 254, 223, 255, 255, 128}
        },
        {
            { 1, 81, 230, 252, 204, 203, 255, 192, 128, 128, 128},
            { 123, 102, 209, 247, 188, 196, 255, 233, 128, 128, 128},
            { 20, 95, 153, 243, 164, 173, 255, 203, 128, 128, 128}
        },
        {
            { 1, 222, 248, 255, 216, 213, 128, 128, 128, 128, 128},
            { 168, 175, 246, 252, 235, 205, 255, 255, 128, 128, 128},
            { 47, 116, 215, 255, 211, 212, 255, 255, 128, 128, 128}
        },
        {
            { 1, 121, 236, 253, 212, 214, 255, 255, 128, 128, 128},
            { 141, 84, 213, 252, 201, 202, 255, 219, 128, 128, 128},
            { 42, 80, 160, 240, 162, 185, 255, 205, 128, 128, 128}
        },
        {
            { 1, 1, 255, 128, 128, 128, 128, 128, 128, 128, 128},
            { 244, 1, 255, 128, 128, 128, 128, 128, 128, 128, 128},
            { 238, 1, 255, 128, 128, 128, 128, 128, 128, 128, 128}
        }
    }
};


const UINT8 vp8_coef_update_probs [VP8_BLOCK_TYPES] [VP8_COEF_BANDS] [VP8_PREV_COEF_CONTEXTS] [VP8_coef_tokens-1] =
{
    {
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {176, 246, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {223, 241, 252, 255, 255, 255, 255, 255, 255, 255, 255, },
            {249, 253, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 244, 252, 255, 255, 255, 255, 255, 255, 255, 255, },
            {234, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 246, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {239, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 248, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {251, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {251, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 254, 253, 255, 254, 255, 255, 255, 255, 255, 255, },
            {250, 255, 254, 255, 254, 255, 255, 255, 255, 255, 255, },
            {254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
    },
    {
        {
            {217, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {225, 252, 241, 253, 255, 255, 254, 255, 255, 255, 255, },
            {234, 250, 241, 250, 253, 255, 253, 254, 255, 255, 255, },
        },
        {
            {255, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {223, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {238, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 248, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {249, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {247, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 254, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
            {250, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
    },
    {
        {
            {186, 251, 250, 255, 255, 255, 255, 255, 255, 255, 255, },
            {234, 251, 244, 254, 255, 255, 255, 255, 255, 255, 255, },
            {251, 251, 243, 253, 254, 255, 254, 255, 255, 255, 255, },
        },
        {
            {255, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {236, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {251, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
    },
    {
        {
            {248, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {250, 254, 252, 254, 255, 255, 255, 255, 255, 255, 255, },
            {248, 254, 249, 253, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 253, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
            {246, 253, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
            {252, 254, 251, 254, 254, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 254, 252, 255, 255, 255, 255, 255, 255, 255, 255, },
            {248, 254, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
            {253, 255, 254, 254, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 251, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {245, 251, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {253, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 251, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
            {252, 253, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {249, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 253, 255, 255, 255, 255, 255, 255, 255, 255, },
            {250, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
        {
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
            {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
        },
    },
};

const MV_CONTEXT vp8_default_mv_context[2] =
{
    {{
        /* row */
        162,                                        /* is short */
        128,                                        /* sign */
        225, 146, 172, 147, 214,  39, 156,          /* short tree */
        128, 129, 132,  75, 145, 178, 206, 239, 254, 254 /* long bits */
        }
    },
    {{
        /* same for column */
        164,                                        /* is short */
        128,
        204, 170, 119, 235, 140, 230, 228,
        128, 130, 130,  74, 148, 180, 203, 236, 254, 254 /* long bits */
        }
    }
};


const MV_CONTEXT vp8_mv_update_probs[2] =
{
    {{
        237,
        246,
        253, 253, 254, 254, 254, 254, 254,
        254, 254, 254, 254, 254, 250, 250, 252, 254, 254
        }
    },
    {{
        231,
        243,
        245, 253, 254, 254, 254, 254, 254,
        254, 254, 254, 254, 254, 251, 251, 254, 254, 254
        }
    }
};


const UINT8 VP8_VFMWBITREADER_NORM[256]=
{
    0, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

UINT8 default_ymode_prob [4] = { 112, 86, 140, 37};
UINT8 default_uv_mode_prob [3] = { 162, 101, 204};

#define VP8_CLEARREFFLAG do{\
     FSP_ClearLogicFs(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 1);\
     FSP_ClearLogicFs(pCtx->ChanID, pVp8CodecInfo->AltFsID, 1);\
     FSP_ClearLogicFs(pCtx->ChanID, pVp8CodecInfo->LastFsID, 1);\
     pVp8CodecInfo->GoldenFsID = 0; \
     pVp8CodecInfo->AltFsID = 0; \
     pVp8CodecInfo->LastFsID = 0; \
     pVp8CodecInfo->GoldenFsID=pVp8CodecInfo->AltFsID=pVp8CodecInfo->LastFsID=FSP_GetNullLogicFs(pCtx->ChanID);\
}while(0)

#define VP8_CLEARREFNUM do{pVp8CodecInfo->RefNum=0;}while(0)


VOID Vp8_Vfmw_StartBoolDecode( VP8_BOOLCODER_S *pBc, BS *pBs )
{
	pBc->range = 255;
	pBc->count = 16;
	pBc->value = BsGet(pBs,24);
}


UINT32 Vp8_Vfmw_DecodeBool( VP8_BOOLCODER_S *pBc, BS *pBs, UINT8 probability )
{
	UINT32 bit=0;
	UINT32 value;
	UINT32 split;
	UINT32 bigsplit;
	SINT32 count;
	UINT32 range;
	SINT32 shift;

	count=pBc->count;
	range=pBc->range;
	value=pBc->value;

	split=1+( ( (range-1)*probability )>>8 );
	bigsplit=split << 16;
	range = split;
	
    if (value >= bigsplit)
    {
        range = pBc->range-split;
        value = value-bigsplit;
        bit = 1;
    }

    shift = (SINT32)VP8_VFMWBITREADER_NORM[range];
    range <<= shift;
    value <<= shift;
    count -= shift;

    if(count < 0)
	{
		for ( shift= 8 - count; shift>=0; shift-=8 )
		{
			count+=8;
			value |= (BsGet(pBs,8)<<shift);
		}
	}

	pBc->count = count;
	pBc->range = range;
	pBc->value = value;

    return bit;
}


SINT32 Vp8_Vfmw_DecodeValue( VP8_BOOLCODER_S *pBc, BS *pBs, SINT32 nBits )
{
	SINT32 i;
	SINT32 value=0;
    
	for ( i=nBits-1; i>=0; i-- )
	{
		value |= ( Vp8_Vfmw_DecodeBool( pBc, pBs, 128 )<<i );
	}

	return value;
}

VOID VP8_SetImgFormat(VP8_CTX_S *pCtx)
{
    UINT32 codtype, csp, vfmt, sfmt, fldflg, fldfst=0, dar;
    VP8_CODECINF *pVp8CodecInfo;
    IMAGE *pImg;

    pVp8CodecInfo = &pCtx->Vp8CodecInfo;

	pImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp8CodecInfo->CurFsID);
	if (NULL == pImg)
	{
        return;
	}

    codtype = pVp8CodecInfo->FrameType;
    csp = 0;
    vfmt = 5;
    sfmt = 0;
    fldflg = 3;  // frame
    fldfst = 1;  //逐行序列指定顶场先显示
    dar = 0;

    pImg->format = ((dar&7)<<14)|((fldfst&0x3)<<12)|((fldflg&3)<<10)|((sfmt&3)<<8)|((vfmt&3)<<5)|((csp&7)<<2)|(codtype&3);
    pImg->top_fld_type = codtype&3;
    pImg->bottom_fld_type = codtype&3;

    SetAspectRatio(pImg, (VDEC_DAR_E)dar);
    pImg->image_width = pVp8CodecInfo->NewHeaderInfo.pic_width_in_pix;
    pImg->image_height = pVp8CodecInfo->NewHeaderInfo.pic_height_in_pix;
    if ((pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
	{
	    SINT32  Stride = pImg->image_stride;//(pImg->image_width + 63) & (~63);
		SINT32  ChromOfst = Stride * ((pImg->image_height + 15)/16)*16;

		pImg->chrom_phy_addr = pImg->luma_phy_addr + ChromOfst;			
	    pImg->top_luma_phy_addr  = pImg->luma_phy_addr;
	    pImg->top_chrom_phy_addr = pImg->top_luma_phy_addr + ChromOfst;
	    pImg->btm_luma_phy_addr  = pImg->top_luma_phy_addr + Stride;
	    pImg->btm_chrom_phy_addr = pImg->top_chrom_phy_addr + Stride;
	    pImg->luma_2d_phy_addr   = pImg->luma_phy_addr;
		pImg->chrom_2d_phy_addr  = pImg->top_chrom_phy_addr;
	}
	
    pImg->disp_center_x = pImg->image_width / 2;
	pImg->disp_center_y = pImg->image_height / 2;
    pImg->disp_width = pImg->image_width;
    pImg->disp_height = pImg->image_height;

	return;
}

    	
SINT32 VP8DEC_VDMPostProc(VP8_CTX_S *pCtx, SINT32 ErrRatio)
{
    SINT32 LastFsId;
	SINT32 ret = VF_OK;
    IMAGE *pCurImg, *pToQueImg;
	VP8_CODECINF *pVp8CodecInfo = &pCtx->Vp8CodecInfo;
	VP8_PICTUREHEADER_S *pPictureHeader = &pVp8CodecInfo->OldHeaderInfo;
    SINT32 flag_last_0 = 0;	
    
	pVp8CodecInfo = &pCtx->Vp8CodecInfo;
    ReleasePacket(VFMW_VP8, pCtx);
    pCurImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp8CodecInfo->CurFsID);

    if (pCurImg == NULL)
    {
        dprint(PRN_FATAL,"pCurImg is null\n");
		return -1;
	}

    pCurImg->error_level = CLIP1(100, (SINT32)(ErrRatio));
    if (pCurImg->error_level > pCtx->pstExtraData->s32RefErrThr)
    {
        dprint(PRN_ERROR, "err_level(%d) over ref_thr(%d)\n",
					pCurImg->error_level, pCtx->pstExtraData->s32RefErrThr );
		
		VP8_CLEARREFFLAG;
        VP8_CLEARREFNUM;
        return -1;
    }
	
    VP8_SetImgFormat(pCtx);
	
	if (((I_MODE == pVp8CodecInfo->UsedDecMode) && (pVp8CodecInfo->FrameType != VP8_KEY_FRAME)) || (pPictureHeader->show_frame == 0))
	{
		pVp8CodecInfo->ToQueFsID = -1;
		FSP_SetDisplay(pCtx->ChanID, pVp8CodecInfo->CurFsID, 0);
	}
	else
	{
		pVp8CodecInfo->ToQueFsID = pVp8CodecInfo->CurFsID;
	}

	if(pVp8CodecInfo->ToQueFsID != -1)
	{
        pToQueImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp8CodecInfo->ToQueFsID);
        if (NULL == pToQueImg)
        {
            dprint(PRN_FATAL,"line: %d pToQueImg is null\n", __LINE__);
            return -1;
        }
        
		FSP_SetDisplay(pCtx->ChanID, pVp8CodecInfo->ToQueFsID, 1);
	    ret = InsertImgToVoQueue(pCtx->ChanID, VFMW_VP8, pCtx, &pCtx->ImageQue, pToQueImg);
	    if (VF_OK != ret)
	    {
	        FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[0]);
	        pToQueImg->p_usrdat[0] = NULL;
	        FreeUsdByDec(pCtx->ChanID, pToQueImg->p_usrdat[1]);
	        pToQueImg->p_usrdat[1] = NULL;
			FSP_SetDisplay(pCtx->ChanID, pVp8CodecInfo->ToQueFsID, 0);
			dprint(PRN_FATAL, "insert img to Voqueue failed!\n");
	        return ret;
	    }
	}

    pVp8CodecInfo->RefNum++;

	LastFsId = pVp8CodecInfo->LastFsID;
	/*update last ref frame*/	
    if ((VP8_KEY_FRAME == pVp8CodecInfo->FrameType) || pPictureHeader->refresh_last_frame )
    {
        if ( (pVp8CodecInfo->LastFsID != pVp8CodecInfo->GoldenFsID) && (pVp8CodecInfo->LastFsID != pVp8CodecInfo->AltFsID) && (pVp8CodecInfo->LastFsID != pVp8CodecInfo->CurFsID))
        {
            //FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->LastFsID, 0);	
            flag_last_0 = 1;
        }
		
        pVp8CodecInfo->LastFsID = pVp8CodecInfo->CurFsID;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->LastFsID, 1);	
    }

	/*update alt ref frame from (golden,last)*/
    if ( 1 == pPictureHeader->copy_buffer_to_arf )
    {
        if ( (pVp8CodecInfo->AltFsID != pVp8CodecInfo->LastFsID) && (pVp8CodecInfo->AltFsID != pVp8CodecInfo->GoldenFsID) && (pVp8CodecInfo->AltFsID != LastFsId))
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 0);
        }

        pVp8CodecInfo->AltFsID = LastFsId;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 1);
		flag_last_0 = 0;
    }
    else if ( 2 == pPictureHeader->copy_buffer_to_arf )
    {
        if ( (pVp8CodecInfo->AltFsID != pVp8CodecInfo->LastFsID) && (pVp8CodecInfo->AltFsID != pVp8CodecInfo->GoldenFsID) )
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 0); 
        }

        pVp8CodecInfo->AltFsID = pVp8CodecInfo->GoldenFsID;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 1);
    }
	
	/*update golden ref frame from (alt, last)*/
    if ( 1 == pPictureHeader->copy_buffer_to_gf )
    {
        if ( (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->LastFsID) && (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->AltFsID) && (pVp8CodecInfo->GoldenFsID != LastFsId))
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 0); 
        }

        pVp8CodecInfo->GoldenFsID = LastFsId;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 1);
		flag_last_0 = 0;
    }
    else if ( 2==pPictureHeader->copy_buffer_to_gf )
    {
        if ( (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->LastFsID) && (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->AltFsID) )
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 0); 
        }

        pVp8CodecInfo->GoldenFsID = pVp8CodecInfo->AltFsID;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 1);
    }

	/*refresh golden frame with current frame*/
    if ((VP8_KEY_FRAME==pVp8CodecInfo->FrameType) || (pPictureHeader->refresh_golden_frame))
    {
        if ( (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->LastFsID) && (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->AltFsID) && (pVp8CodecInfo->GoldenFsID != pVp8CodecInfo->CurFsID))
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 0); 
        }

        pVp8CodecInfo->GoldenFsID = pVp8CodecInfo->CurFsID;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 1);
    }

	/*refresh alt ref frame with current frame*/
    if ((VP8_KEY_FRAME==pPictureHeader->frame_type) || (pPictureHeader->refresh_alt_ref_frame))
    {
        if ( (pVp8CodecInfo->AltFsID != pVp8CodecInfo->LastFsID) && (pVp8CodecInfo->AltFsID != pVp8CodecInfo->GoldenFsID) && (pVp8CodecInfo->AltFsID != pVp8CodecInfo->CurFsID))
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 0); 
        }

        pVp8CodecInfo->AltFsID = pVp8CodecInfo->CurFsID;
        FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 1); 
    }
	if (flag_last_0 == 1)
	{
	    FSP_SetRef(pCtx->ChanID, LastFsId, 0); 
	}

    return VF_OK;
}


/*****************************************************************************
 函 数 名  :  
 功能描述  :  
 输出参数  :  
 返 回 值  :  
 调用函数  :
 被调函数  :

 修改历史  :
 日    期  :  
 作    者  :  
 修改内容  :  

*****************************************************************************/
SINT32 VP8DEC_Init(VP8_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{
    VP8_CODECINF *pVp8CodecInfo;
    SINT32  ImgQueRstMagic;
    
    ImgQueRstMagic = pCtx->ImageQue.ResetMagicWord;
    memset(pCtx, 0, sizeof(VP8_CTX_S));	
    pCtx->ImageQue.ResetMagicWord = ImgQueRstMagic;
    ResetVoQueue(&pCtx->ImageQue);
    
    pCtx->pstExtraData  = pstExtraData;
    
    pCtx->ChanID = VCTRL_GetChanIDByCtx(pCtx);
    if ( -1 == pCtx->ChanID )
    {
        dprint(PRN_FATAL, "-1 == VCTRL_GetChanIDByCtx() Err! \n");
        return VF_ERR_SYS;
    }
    
	pVp8CodecInfo = &pCtx->Vp8CodecInfo;
	pVp8CodecInfo->Imgbuf_allocated = VP8_VFMW_FALSE;
    pVp8CodecInfo->ddr_stride = 0x400;
    pVp8CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
	pVp8CodecInfo->LastFrameType = 3;
	pVp8CodecInfo->LastFilterType = 3;
	pVp8CodecInfo->LastSharpnessLevel = 0;
    pVp8CodecInfo->SegIdAddr = pCtx->pstExtraData->s32Vp8SegIdMemAddr;

    return VF_OK;
}


SINT32 VP8DEC_Destroy(VP8_CTX_S *pCtx)
{
    return VF_OK;
}


VOID VP8_setup_version(VP8_PICTUREHEADER_S *pPictureHeader)
{
    switch (pPictureHeader->version)
    {
    case 0:
        pPictureHeader->no_lpf = 0;
        pPictureHeader->simpler_lpf = 0;
        pPictureHeader->use_bilinear_mc_filter = 0;
        pPictureHeader->full_pixel = 0;
        break;
    case 1:
        pPictureHeader->no_lpf = 0;
        pPictureHeader->simpler_lpf = 1;
        pPictureHeader->use_bilinear_mc_filter = 1;
        pPictureHeader->full_pixel = 0;
        break;
    case 2:
        pPictureHeader->no_lpf = 1;
        pPictureHeader->simpler_lpf = 0;
        pPictureHeader->use_bilinear_mc_filter = 1;
        pPictureHeader->full_pixel = 0;
        break;
    case 3:
        pPictureHeader->no_lpf = 1;
        pPictureHeader->simpler_lpf = 1;
        pPictureHeader->use_bilinear_mc_filter = 1;
        pPictureHeader->full_pixel = 1;
        break;
    default:
        /*4,5,6,7 are reserved for future use*/
        pPictureHeader->no_lpf = 0;
        pPictureHeader->simpler_lpf = 0;
        pPictureHeader->use_bilinear_mc_filter = 0;
        pPictureHeader->full_pixel = 0;
        break;
    }

    if (!pPictureHeader->use_bilinear_mc_filter)
    {
        pPictureHeader->mcomp_filter_type = VP8_SIXTAP;
    }
    else
    {
        pPictureHeader->mcomp_filter_type = VP8_BILINEAR;
    }

    return;
}


VOID read_mvcontexts(VP8_BOOLCODER_S  *bc,BS *pBs, MV_CONTEXT *mvc)
{
    SINT32 i = 0;

    do
    {
        const UINT8 *up = vp8_mv_update_probs[i].prob;
        UINT8 *p = (UINT8 *)(mvc + i);
        UINT8 *const pstop = p + MVPcount;

        do
        {
            if (Vp8_Vfmw_DecodeBool(bc,pBs, *up++))
            {
                const UINT8 x = (UINT8)Vp8_Vfmw_DecodeValue(bc,pBs, 7);

                *p = x ? x << 1 : 1;
            }
        }
        while (++p < pstop);
    }
    while (++i < 2);
}


VOID VP8_mb_mode_mv_init(VP8_PICTUREHEADER_S *pPictureHeader, VP8_BOOLCODER_S  *bc, BS *pBs)
{
    MV_CONTEXT *const mvc = pPictureHeader->fc.mvc;
    SINT32 tmp = 0;
	
    if(pPictureHeader->frame_type == VP8_KEY_FRAME)
    {
		return ;
	}
	
    pPictureHeader->prob_intra = (UINT8)Vp8_Vfmw_DecodeValue(bc,pBs, 8);
    pPictureHeader->prob_last  = (UINT8)Vp8_Vfmw_DecodeValue(bc,pBs, 8);
    pPictureHeader->prob_gf    = (UINT8)Vp8_Vfmw_DecodeValue(bc,pBs, 8);

	tmp = Vp8_Vfmw_DecodeBool(bc, pBs, 128);
    if (1 == tmp)
    {
        SINT32 i = 0;

        do
        {
            pPictureHeader->fc.ymode_prob[i] = (UINT8)Vp8_Vfmw_DecodeValue(bc, pBs, 8);
        }
        while (++i < 4);
    }

    if (Vp8_Vfmw_DecodeBool(bc, pBs, 128))
    {
        SINT32 i = 0;

        do
        {
            pPictureHeader->fc.uv_mode_prob[i] = (UINT8)Vp8_Vfmw_DecodeValue(bc,pBs, 8);
        }
        while (++i < 3);
    }

    read_mvcontexts(bc,pBs,mvc);
}


SINT32 get_delta_q(VP8_BOOLCODER_S *pBc, BS *pBs, SINT32 prev, SINT32 *q_update)
{
    SINT32 ret_val = 0;
	
    if (Vp8_Vfmw_DecodeBool(pBc, pBs, 128))
    {
        ret_val = Vp8_Vfmw_DecodeValue(pBc,pBs, 4);

        if (Vp8_Vfmw_DecodeBool(pBc, pBs, 128))
        { ret_val = -ret_val; }
    }

    /* Trigger a quantizer update if the delta-q value has changed */
    if (ret_val != prev)
    { *q_update = 1; }

    return ret_val;
}


VOID VP8_init_frame(VP8_PICTUREHEADER_S *VP8_PictureHeader_S)
{
    if ( VP8_PictureHeader_S->frame_type == VP8_KEY_FRAME) 
    {
    	/* Various keyframe initializations */
        memcpy(VP8_PictureHeader_S->fc.mvc, vp8_default_mv_context, sizeof(vp8_default_mv_context));
        memcpy((UINT8 *)(&(VP8_PictureHeader_S->fc.coef_probs[0][0][0][0])),(UINT8 *)(&(default_coef_probs[0][0][0][0])),4*8*3*11); //sizeof(default_coef_probs));
        memcpy(VP8_PictureHeader_S->fc.ymode_prob,default_ymode_prob,sizeof(default_ymode_prob));
        memcpy(VP8_PictureHeader_S->fc.uv_mode_prob,default_uv_mode_prob,sizeof(default_uv_mode_prob));
        
        /* reset the segment feature data to 0 with delta coding (Default state). */
        memset(VP8_PictureHeader_S->segment_feature_data, 0, sizeof(VP8_PictureHeader_S->segment_feature_data));
        VP8_PictureHeader_S->mb_segement_abs_delta = SEGMENT_DELTADATA;
    
        /* reset the mode ref deltasa for loop filter */
        memset(VP8_PictureHeader_S->ref_lf_deltas, 0, sizeof(VP8_PictureHeader_S->ref_lf_deltas));
        memset(VP8_PictureHeader_S->mode_lf_deltas, 0, sizeof(VP8_PictureHeader_S->mode_lf_deltas));
    
        /* All buffers are implicitly updated on key frames. */
        VP8_PictureHeader_S->refresh_golden_frame = 1;
        VP8_PictureHeader_S->refresh_alt_ref_frame = 1;
        VP8_PictureHeader_S->copy_buffer_to_gf = 0;
        VP8_PictureHeader_S->copy_buffer_to_arf = 0;
    
        /* Note that Golden and Altref modes cannot be used on a key frame so
         * ref_frame_sign_bias[] is undefined and meaningless
         */
        VP8_PictureHeader_S->ref_frame_sign_bias[VP8_GOLDEN_FRM] = 0;
        VP8_PictureHeader_S->ref_frame_sign_bias[VP8_ALTREF_FRM] = 0;
    }	
}

SINT32 VP8_GetPictureHeader(BS *pBs, VP8_CODECINF *pVp8CodecInfo , UINT32 strlen)
{
    VP8_PICTUREHEADER_S *pPictureHeader = &pVp8CodecInfo->NewHeaderInfo;
    VP8_BOOLCODER_S * bc = &pPictureHeader->bc;
    UINT8 data0, data1, data2, data3;
    UINT32 i, j, k, l;
    UINT32 old_height, old_width;
    const SINT32 mb_feature_data_bits[MB_LVL_MAX] = {7, 6};
	
	/*get common frame header synatx element*/
    data0 = BsGet(pBs, 8);
    data1 = BsGet(pBs, 8);
    data2 = BsGet(pBs, 8);

    pVp8CodecInfo->FrameType = pPictureHeader->frame_type = (VP8_FRAME_TYPE)(data0 & 1);
    pPictureHeader->version = (data0 >> 1) & 7;
    pPictureHeader->show_frame = (data0 >> 4) & 1;
    pPictureHeader->first_partition_length_in_bytes = (data0 | (data1 << 8) | (data2 << 16)) >> 5;

    if (strlen < pPictureHeader->first_partition_length_in_bytes)
    {
		dprint(PRN_ERROR,"Error!partition 0 length > streamlength!\n");	
        return VP8_VFMW_FALSE;
    }

    VP8_setup_version(pPictureHeader);
     
    if (pPictureHeader->frame_type == VP8_KEY_FRAME)
    {
        /* vet via sync code */
        data0 = BsGet(pBs, 8);
        data1 = BsGet(pBs, 8);
        data2 = BsGet(pBs, 8);

        //VP8 key frame startcode = 0x9d012a
        if (data0 != 0x9d || data1 != 0x01 || data2 != 0x2a)
        {
            dprint(PRN_ERROR,"Invalid frame sync code,data[0-1]:%02x,%02x,%02x\n",
				data0,data1,data2);
            return VP8_VFMW_FALSE;
        }

        data0 = BsGet(pBs, 8);
        data1 = BsGet(pBs, 8);
        data2 = BsGet(pBs, 8);
        data3 = BsGet(pBs, 8);

        pPictureHeader->pic_width_in_pix = (data0 | (data1 << 8)) & 0x3fff;
        pPictureHeader->pic_width_in_mb = (pPictureHeader->pic_width_in_pix + 15)/16;
        pPictureHeader->horiz_scale = data1 >> 6;
        pPictureHeader->pic_height_in_pix = (data2 | (data3 << 8)) & 0x3fff;
        pPictureHeader->pic_height_in_mb = (pPictureHeader->pic_height_in_pix + 15)/16;
        pPictureHeader->vert_scale = data3 >> 6;
        pPictureHeader->total_mbs = pPictureHeader->pic_height_in_mb * pPictureHeader->pic_width_in_mb;
		
        if ((pPictureHeader->pic_width_in_pix <= 32 ) || (pPictureHeader->pic_height_in_pix <= 32)
			|| (pPictureHeader->pic_width_in_mb > MAX_IMG_WIDTH_IN_MB) || (pPictureHeader->pic_height_in_mb > MAX_IMG_HEIGHT_IN_MB))
        {
            dprint(PRN_ERROR,"Invalid frame width %d and Height %d!\n", pPictureHeader->pic_width_in_pix, pPictureHeader->pic_height_in_pix);
            return VP8_VFMW_FALSE;
        }

        // we have a new input size,and may need to resize the output buffer here
		old_height = pVp8CodecInfo->OldHeaderInfo.pic_height_in_pix;
		old_width = pVp8CodecInfo->OldHeaderInfo.pic_width_in_pix;
		
        if ((pPictureHeader->pic_height_in_pix != old_height )
			|| (pPictureHeader->pic_width_in_pix != old_width))
        {
           dprint(PRN_DBG,"We have a new size image!\n");
		   dprint(PRN_DBG,"The old size is %d x %d,the new is %d x %d\n",
				old_width,old_height,
				pPictureHeader->pic_width_in_mb,
				pPictureHeader->pic_height_in_mb);
        }
    }

	VP8_init_frame(pPictureHeader);	

	/*start booldecoder here */	
    Vp8_Vfmw_StartBoolDecode(bc, pBs);
	
    if (pPictureHeader->frame_type == VP8_KEY_FRAME) 
   	{
        pPictureHeader->clr_type    = (YUV_TYPE)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
        pPictureHeader->clamping_type  = (CLAMP_TYPE)Vp8_Vfmw_DecodeBool(bc,pBs, 128);
	}
	
    /* Is segmentation enabled */
    pPictureHeader->segmentation_enabled = (UINT8)Vp8_Vfmw_DecodeBool(bc,pBs, 128);

    if (pPictureHeader->segmentation_enabled)
    {
        /* Signal whether or not the segmentation map is being explicitly updated this frame. */
        pPictureHeader->update_mb_segmentation_map = (UINT8)Vp8_Vfmw_DecodeBool(bc,pBs, 128);
        pPictureHeader->update_mb_segmentation_data = (UINT8)Vp8_Vfmw_DecodeBool(bc,pBs, 128);
	
        if (pPictureHeader->update_mb_segmentation_data)
        {
            pPictureHeader->mb_segement_abs_delta = (UINT8)Vp8_Vfmw_DecodeBool(bc,pBs, 128);
	
            memset(pPictureHeader->segment_feature_data, 0, sizeof(pPictureHeader->segment_feature_data));
    
            /* For each segmentation feature (Quant and loop filter level) */
            for (i = 0; i < MB_LVL_MAX; i++)
            {
                for (j = 0; j < VP8_MAX_MB_SEGMENTS; j++)
                {
			     	SINT8 tmp;
					
                    pPictureHeader->quantizer_update = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
                    if (1 == pPictureHeader->quantizer_update)
                    {
                                   		
                        tmp = (SINT8)Vp8_Vfmw_DecodeValue(bc, pBs, mb_feature_data_bits[i]);
                        if (Vp8_Vfmw_DecodeBool(bc, pBs, 128)) //quantizer sign
                        {
                            tmp = -tmp;
                        }
                    }
                    else
                    {
                       tmp = 0;
                    }
					
					pPictureHeader->segment_feature_data[i][j] = tmp;				
                }
            }
        }
      
        if (pPictureHeader->update_mb_segmentation_map)
        {
            /* Which macro block level features are enabled */
            memset(pPictureHeader->mb_segment_tree_probs, 255, sizeof(pPictureHeader->mb_segment_tree_probs));
    
            /* Read the probs used to decode the segment id for each macro block. */
            for (i = 0; i < VP8_MB_FEATURE_TREE_PROBS; i++)
            {
                /* If not explicitly set value is defaulted to 255 by memset above */
                pPictureHeader->segment_prob_update = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
                if (1 == pPictureHeader->segment_prob_update)
                {
                    pPictureHeader->mb_segment_tree_probs[i] = (UINT8) Vp8_Vfmw_DecodeValue(bc, pBs, 8);
                }
            }
        }
    }

    /* Read the loop filter level and type */
    pPictureHeader->filter_type = (VP8_LOOPFILTERTYPE) Vp8_Vfmw_DecodeBool(bc, pBs, 128);
    pPictureHeader->filter_level = Vp8_Vfmw_DecodeValue(bc, pBs, 6);
    pPictureHeader->sharpness_level = (UINT8)Vp8_Vfmw_DecodeValue(bc, pBs, 3);
    
    /* Read in loop filter deltas applied at the MB level based on mode or ref frame. */
    pPictureHeader->mode_ref_lf_delta_update = 0;
    pPictureHeader->mode_ref_lf_delta_enabled = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);

    if (pPictureHeader->mode_ref_lf_delta_enabled)
    {
        /* Do the deltas need to be updated */
        pPictureHeader->mode_ref_lf_delta_update = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);

        if (pPictureHeader->mode_ref_lf_delta_update)
        {
            /* Send update */
            for (i = 0; i < VP8_MAX_REF_LF_DELTAS; i++)
            {
                pPictureHeader->ref_frame_delta_update_flag = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
                if (pPictureHeader->ref_frame_delta_update_flag == 1)
                {
                    /*sign = vp8_read_bit( bc );*/
                    pPictureHeader->ref_lf_deltas[i] = (SINT8)Vp8_Vfmw_DecodeValue(bc, pBs, 6);
                    pPictureHeader->delta_sign = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
                    if (pPictureHeader->delta_sign == 1)        /* Apply sign */
                    {
                        pPictureHeader->ref_lf_deltas[i] = pPictureHeader->ref_lf_deltas[i] * (-1);
                    }
                }
            }
	
            /* Send update */
            for (i = 0; i < VP8_MAX_MODE_LF_DELTAS; i++)
            {
                pPictureHeader->mb_mode_delta_update_flag = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
                if ( pPictureHeader->mb_mode_delta_update_flag == 1)
                {
                    /*sign = vp8_read_bit( bc );*/
                    pPictureHeader->mode_lf_deltas[i] = (SINT8)Vp8_Vfmw_DecodeValue(bc, pBs, 6);
    
                    if (Vp8_Vfmw_DecodeBool(bc, pBs, 128))        /* Apply sign */
                    {
                        pPictureHeader->mode_lf_deltas[i] = pPictureHeader->mode_lf_deltas[i] * (-1);
                    }
                }
            }
		}
    }

    pPictureHeader->multi_token_partition = (TOKEN_PARTITION)Vp8_Vfmw_DecodeValue(bc, pBs, 2);

    /* Read the default quantizers. */
    {
        SINT32 Q, q_update;
    
        Q = Vp8_Vfmw_DecodeValue(bc, pBs, 7);  /* AC 1st order Q = default */
        pPictureHeader->base_qindex = Q;
        q_update = 0;
        pPictureHeader->y1dc_delta_q = get_delta_q(bc, pBs, pPictureHeader->y1dc_delta_q, &q_update);
        pPictureHeader->y2dc_delta_q = get_delta_q(bc, pBs, pPictureHeader->y2dc_delta_q, &q_update);
        pPictureHeader->y2ac_delta_q = get_delta_q(bc, pBs, pPictureHeader->y2ac_delta_q, &q_update);
        pPictureHeader->uvdc_delta_q = get_delta_q(bc, pBs, pPictureHeader->uvdc_delta_q, &q_update);
        pPictureHeader->uvac_delta_q = get_delta_q(bc, pBs, pPictureHeader->uvac_delta_q, &q_update);
    }

    /* Determine if the golden frame or ARF buffer should be updated and how.
     * For all non key frames the GF and ARF refresh flags and sign bias
     * flags must be set explicitly.
     */
    if (pPictureHeader->frame_type != VP8_KEY_FRAME)
    {
        /* Should the GF or ARF be updated from the current frame */
        pPictureHeader->refresh_golden_frame = Vp8_Vfmw_DecodeBool(bc, pBs, 128);
        pPictureHeader->refresh_alt_ref_frame = Vp8_Vfmw_DecodeBool(bc, pBs, 128);
    
        /* Buffer to buffer copy flags. */
        pPictureHeader->copy_buffer_to_gf = 0;
    
        if (!pPictureHeader->refresh_golden_frame)
        { pPictureHeader->copy_buffer_to_gf = Vp8_Vfmw_DecodeValue(bc, pBs, 2); }
    
        pPictureHeader->copy_buffer_to_arf = 0;
    
        if (!pPictureHeader->refresh_alt_ref_frame)
        { pPictureHeader->copy_buffer_to_arf = Vp8_Vfmw_DecodeValue(bc, pBs, 2); }
    
        pPictureHeader->ref_frame_sign_bias[VP8_GOLDEN_FRM] = Vp8_Vfmw_DecodeBool(bc, pBs, 128);
        pPictureHeader->ref_frame_sign_bias[VP8_ALTREF_FRM] = Vp8_Vfmw_DecodeBool(bc, pBs, 128);
    }

    pPictureHeader->refresh_entropy_probs = Vp8_Vfmw_DecodeBool(bc, pBs, 128);
    if (pPictureHeader->refresh_entropy_probs == 0)
    {
        memcpy(&pPictureHeader->lfc, &pPictureHeader->fc, sizeof(pPictureHeader->fc));
    }

	if(pPictureHeader->frame_type == VP8_KEY_FRAME)
	{
    	pPictureHeader->refresh_last_frame = 1;
	}
	else
	{
		pPictureHeader->refresh_last_frame = (UINT8)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
	}

	
	{
        /* read coef probability tree */
        for (i = 0; i < VP8_BLOCK_TYPES; i++)
        {
            for (j = 0; j < VP8_COEF_BANDS; j++)
            {
                for (k = 0; k < VP8_PREV_COEF_CONTEXTS; k++)
                {
                    for (l = 0; l < VP8_MAX_ENTROPY_TOKENS - 1; l++)
                    {
                        UINT8 *p = &pPictureHeader->fc.coef_probs [i][j][k][l];
                        UINT32  tmp1 = Vp8_Vfmw_DecodeBool(bc, pBs, vp8_coef_update_probs[i][j][k][l]);
                        if (1 == tmp1)
                        {
                            *p = (UINT8)Vp8_Vfmw_DecodeValue(bc,pBs, 8);
                        }
                    }
                }
            }
        }
    }

    /* Read the mb_no_coeff_skip flag */
    pPictureHeader->mb_no_coeff_skip = (SINT32)Vp8_Vfmw_DecodeBool(bc, pBs, 128);
	
    if (pPictureHeader->mb_no_coeff_skip)
    {
        pPictureHeader->prob_skip_false = (UINT8)Vp8_Vfmw_DecodeValue(bc, pBs, 8);
    }
	else
	{
		pPictureHeader->prob_skip_false = 0;
	}
    VP8_mb_mode_mv_init(pPictureHeader, bc, pBs);

    /* If this was a kf or Gf note the Q used */
    if ((pPictureHeader->frame_type == VP8_KEY_FRAME) ||
         (pPictureHeader->refresh_golden_frame) || (pPictureHeader->refresh_alt_ref_frame))
    {
        pPictureHeader->last_kf_gf_q = pPictureHeader->base_qindex;
    }
	
    return VP8_VFMW_TRUE;
}


UINT32 VP8_ArrangeVHBMem(VP8_CTX_S *pCtx)
{
    VP8_CODECINF *pVp8CodecInfo;
    VP8_PICTUREHEADER_S *pSyntaxInfNew;
    FSP_INST_CFG_S  FspInstCfg;
    SINT32 PicWidth, PicHeight, DecFsNum, DispFsNum, PmvNum;

    pVp8CodecInfo = &pCtx->Vp8CodecInfo;
    pSyntaxInfNew = &pVp8CodecInfo->NewHeaderInfo;

    if( pSyntaxInfNew->pic_height_in_pix < 32 || pSyntaxInfNew->pic_width_in_pix < 32 )
    {
        dprint(PRN_FATAL, "image size abnormal(%dx%d)\n", pSyntaxInfNew->pic_width_in_pix, pSyntaxInfNew->pic_height_in_pix );
        return VP8_VFMW_FALSE;
    }

    if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
    {
        if (pSyntaxInfNew->pic_width_in_pix > pCtx->pstExtraData->stChanOption.s32MaxWidth || pSyntaxInfNew->pic_height_in_pix > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "vp8 actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxInfNew->pic_width_in_pix, pSyntaxInfNew->pic_height_in_pix,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return VP8_VFMW_FALSE;
		}
				
        /* 这种情况下，图像尺寸固定地按配置信息来 */
        PicWidth  = pCtx->pstExtraData->stChanOption.s32MaxWidth;
        PicHeight = pCtx->pstExtraData->stChanOption.s32MaxHeight;
		
        if (pVp8CodecInfo->Imgbuf_allocated == VP8_VFMW_TRUE)
        {
            return VP8_VFMW_TRUE;
		}
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pCtx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvNum = 1;
        }
        else
        {
            PmvNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvNum = MIN(PmvNum,17);
        }		
		DispFsNum = pCtx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}	
	else if (pCtx->pstExtraData->eCapLevel != CAP_LEVEL_USER_DEFINE_WITH_OPTION)
	{
        PicWidth  = pSyntaxInfNew->pic_width_in_pix;
        PicHeight = pSyntaxInfNew->pic_height_in_pix;	
		DecFsNum = 4;
		PmvNum = 4;//ref + 1
		DispFsNum = 5;		
	}
	else
	{
        if (pSyntaxInfNew->pic_width_in_pix > pCtx->pstExtraData->stChanOption.s32MaxWidth || pSyntaxInfNew->pic_height_in_pix > pCtx->pstExtraData->stChanOption.s32MaxHeight)
        {
            dprint(PRN_FATAL, "vp8 actual frame size(%dx%d) exeed max config(%dx%d)\n", pSyntaxInfNew->pic_width_in_pix, pSyntaxInfNew->pic_height_in_pix,
				pCtx->pstExtraData->stChanOption.s32MaxWidth, pCtx->pstExtraData->stChanOption.s32MaxHeight);

			return VP8_VFMW_FALSE;
		}
        PicWidth  = pSyntaxInfNew->pic_width_in_pix;
        PicHeight = pSyntaxInfNew->pic_height_in_pix;	
	    /*为了尽可能地精确计算总帧存个数，按照公式 总帧存个数= s32MaxRefFrameNum + s32DisplayFrameNum + 1，以前曾经为...+2，但是当前帧只占一个就可以了*/		
		DecFsNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + PLUS_FS_NUM;
        if (0 == pCtx->pstExtraData->stChanOption.s32SupportBFrame)
        {
            PmvNum = 1;
        }
        else
        {
            PmvNum = pCtx->pstExtraData->stChanOption.s32MaxRefFrameNum + 1;
			PmvNum = MIN(PmvNum,17);
        }		
		DispFsNum = pCtx->pstExtraData->stChanOption.s32DisplayFrameNum;
	}

    memset(&FspInstCfg, 0, sizeof(FSP_INST_CFG_S));
	FspInstCfg.s32DecFsWidth        = PicWidth;
	FspInstCfg.s32DecFsHeight       = PicHeight;
	FspInstCfg.s32DispFsWidth       = PicWidth;
	FspInstCfg.s32DispFsHeight      = PicHeight;
	FspInstCfg.s32ExpectedDecFsNum  = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 0: DecFsNum;
	FspInstCfg.s32ExpectedDispFsNum = DispFsNum;
	FspInstCfg.s32ExpectedPmvNum    = (pCtx->pstExtraData->eCapLevel == CAP_LEVEL_SINGLE_IFRAME_FHD)? 1: PmvNum;
	
 	if (FSP_OK == FSP_ConfigInstance(pCtx->ChanID, &FspInstCfg))
 	{
 	    SINT32 Ret, UsedMemSize;
        Ret = FSP_PartitionFsMemory(pCtx->ChanID, pCtx->pstExtraData->s32SyntaxMemAddr, 
			                        pCtx->pstExtraData->s32SyntaxMemSize, &UsedMemSize);
		if (Ret != FSP_OK)
		{
            // 分割帧存失败，返回
            return VP8_VFMW_FALSE;
		}
	}
	else
	{
	    dprint(PRN_FATAL, "FSP_ConfigInstance fail!\n");
        return VP8_VFMW_FALSE;
	}

    pVp8CodecInfo->Imgbuf_allocated = VP8_VFMW_TRUE;
	
    return VP8_VFMW_TRUE;
}

SINT32 VP8_DecodeDecide(VP8_CTX_S *pCtx)
{
    SINT32  DecMode;
    SINT32  ret = VP8_VFMW_TRUE;
    VP8_CODECINF *pVp8CodecInfo;
    IMAGE *pFwdImg;
	
	pVp8CodecInfo = &pCtx->Vp8CodecInfo;
  	DecMode = pCtx->pstExtraData->s32DecMode;

    if (VP8_VFMW_FALSE == pVp8CodecInfo->Imgbuf_allocated)
    {
        dprint(PRN_ERROR, "ERROR: No Img buffer is allocated\n");
        return VP8_VFMW_FALSE;
    }

    /* 解码模式(IPB,IP,I)的处理 */
    if ( (pVp8CodecInfo->UsedDecMode == I_MODE || pVp8CodecInfo->UsedDecMode == DISCARD_MODE) &&
		 (pCtx->pstExtraData->s32DecMode == IP_MODE || pCtx->pstExtraData->s32DecMode == IPB_MODE || 
		 pCtx->pstExtraData->s32DecMode == DISCARD_B_BF_P_MODE) )
    {
        /* I->IP 或 I->IPB都有可能引发参考错误，所以需要找下一个I帧才行 */
        dprint(PRN_CTRL,"----------------- vp8 Imode -> %d ------------------\n", pCtx->pstExtraData->s32DecMode);
        VP8_CLEARREFFLAG;
        VP8_CLEARREFNUM; //清空参考图记数器，后续码流将完全重新来过
    }
    pVp8CodecInfo->UsedDecMode = pCtx->pstExtraData->s32DecMode;
    switch (pVp8CodecInfo->UsedDecMode)
    {
        case DISCARD_MODE:
			ret = VP8_VFMW_FALSE;
			break;
        case I_MODE:
            if( VP8_KEY_FRAME != pVp8CodecInfo->FrameType)
            {
                ret = VP8_VFMW_FALSE;
    	        dprint(PRN_PIC, "-----I_MODE, but FrameType is %d-----\n", pVp8CodecInfo->FrameType);			
            }
            break;
        case IP_MODE:
        case IPB_MODE:			
        case DISCARD_B_BF_P_MODE:
            if((VP8_KEY_FRAME !=  pVp8CodecInfo->FrameType) && (pVp8CodecInfo->RefNum < 1))
            {
            	dprint(PRN_PIC, "-----cur framtype is %s, but refnum=%d-----\n",
        			(pVp8CodecInfo->FrameType == VP8_KEY_FRAME)? "I-frm":"P-frm" ,
        			pVp8CodecInfo->RefNum);
                ret = VP8_VFMW_FALSE;
            }
            break;
		default: 
			ret = VP8_VFMW_FALSE;
			dprint(PRN_ERROR, "error: DecMode illegal\n");
            break;
    }

    if (ret != VP8_VFMW_FALSE)
    {
        /* 如果是P/B帧，要看其参考帧是否超出参考阈值，若超出则不解 */
    	pFwdImg = FSP_GetFsImagePtr(pCtx->ChanID, pVp8CodecInfo->LastFsID);
        if(NULL == pFwdImg)
        {
        	dprint(PRN_DBG, "%s %d NULL == pFwdImg!!\n",__FUNCTION__,__LINE__);
        	return VP8_VFMW_FALSE;
        }
    	if (VP8_KEY_FRAME !=  pVp8CodecInfo->FrameType)
    	{
            if ( (NULL == pFwdImg) || (pFwdImg->error_level > pCtx->pstExtraData->s32RefErrThr) )
            {
                dprint(PRN_ERROR, "dec P frame, fwd ref err(%d) > ref_thr(%d)\n",pFwdImg->error_level, pCtx->pstExtraData->s32RefErrThr);
    			return VP8_VFMW_FALSE;
    		}
			else
			{
			    return VP8_VFMW_TRUE;
			}
    	}
		else
		{
		    return VP8_VFMW_TRUE;
		}
    }
	else
	{
	    return VP8_VFMW_FALSE;
	}
}


UINT32 VP8_GetImageBuffer(VP8_CTX_S *pCtx)
{
    VP8_CODECINF *pVp8CodecInfo;
    FSP_LOGIC_FS_S *pLf;
	
    pVp8CodecInfo = &pCtx->Vp8CodecInfo;

    pVp8CodecInfo->CurFsID = FSP_NewLogicFs(pCtx->ChanID, 1);
    if (pVp8CodecInfo->CurFsID < 0)
    {
        /* 获取帧存失败 */
		dprint(PRN_FATAL,"get frame store fail!\n");
		VP8_CLEARREFFLAG;
		VP8_CLEARREFNUM;		
		#if 0
		ResetVoQueue(&pCtx->ImageQue);
		FSP_EmptyInstance(pCtx->ChanID);
		#else
		FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		#endif
		return VP8_VFMW_FALSE;
    }

	pLf = FSP_GetLogicFs(pCtx->ChanID, pVp8CodecInfo->CurFsID);
    if (NULL == pLf)
    {
        dprint(PRN_DBG, "line: %d, pImage is NULL!\n", __LINE__);
        return VP8_VFMW_FALSE;
    }

    dprint(PRN_PIC, "get image buffer ok: LogicFsID = %d\n", pVp8CodecInfo->CurFsID);		
	if ( (NULL!=pLf->pstDecodeFs) && (NULL!=pLf->pstDispOutFs) && (NULL!=pLf->pstTfOutFs) )
	{
	    dprint(PRN_PIC, "decode %p, disp %p, tf %p\n", pLf->pstDecodeFs->PhyAddr, pLf->pstDispOutFs->PhyAddr, pLf->pstTfOutFs->PhyAddr);
    }
	else
	{
	    return VP8_VFMW_FALSE;
	}

    return VP8_VFMW_TRUE;

}


SINT32 VP8_Set_DecParam(VP8_CTX_S *pCtx)
{
	VP8_CODECINF *pVp8CodecInfo = &pCtx->Vp8CodecInfo;
	VP8_DEC_PARAM_S *pVp8DecParam = &pCtx->Vp8DecParam;
	BS *pBs = &pCtx->Bs;
	VP8_PICTUREHEADER_S *pPictureHeader = &pVp8CodecInfo->NewHeaderInfo;
	STREAM_PARAM *pVp8StreamParam = pCtx->pVp8StreamParam;
	SINT32 i = 0;
	UINT8 *_ptr_msg_bank;
	UINT8 *tab_virt_addr;
    UINT32 _dst_phy_offset;
    UINT8 *_src_vir_addr;
    SINT32 _plane, _band, _prec;
	UINT32 ByteLen_1;
	UINT32 length, offset;
	UINT32 ByteA, ByteB, Byte[8];
	UINT32 BsLen[8];	
	UINT8 num_part;
	UINT8  *source, *VirAddr_1;
	UINT8  *source_start;
    FSP_LOGIC_FS_S *pCur, *pGolden, *pAlt, *pLast;	
	
	memset(pVp8DecParam, 0, sizeof(VP8_DEC_PARAM_S));
	
	pVp8DecParam->frame_type = pPictureHeader->frame_type;
	pVp8DecParam->last_frame_type = pVp8CodecInfo->LastFrameType;

	pVp8DecParam->pic_width_in_mb = pPictureHeader->pic_width_in_mb;
	pVp8DecParam->pic_height_in_mb = pPictureHeader->pic_height_in_mb;

	pVp8DecParam->use_bilinear_mc_filter = pPictureHeader->use_bilinear_mc_filter;
	pVp8DecParam->full_pixel = pPictureHeader->full_pixel;

	pVp8DecParam->prob_skip_false = pPictureHeader->prob_skip_false;
	pVp8DecParam->mb_no_coeff_skip = pPictureHeader->mb_no_coeff_skip;	
	pVp8DecParam->multi_token_partition = pPictureHeader->multi_token_partition;
	
	pVp8DecParam->segmentation_enable = pPictureHeader->segmentation_enabled;
	pVp8DecParam->update_mb_segmentation_map = pPictureHeader->update_mb_segmentation_map;
	pVp8DecParam->mb_segmentation_abs_delta = pPictureHeader->mb_segement_abs_delta;
	pVp8DecParam->mode_ref_lf_delta_enabled = pPictureHeader->mode_ref_lf_delta_enabled;

	pVp8DecParam->filter_type = pPictureHeader->filter_type;
	pVp8DecParam->filter_level = pPictureHeader->filter_level;	
	pVp8DecParam->sharpness_level = pPictureHeader->sharpness_level;
	pVp8DecParam->last_filter_type = pVp8CodecInfo->LastFilterType;
	pVp8DecParam->last_sharpness_level = pVp8CodecInfo->LastSharpnessLevel;

	pVp8DecParam->base_qindex = pPictureHeader->base_qindex;
	pVp8DecParam->y1dc_sign = (pPictureHeader->y1dc_delta_q < 0);
	pVp8DecParam->y1dc_absdelta_q = ABS(pPictureHeader->y1dc_delta_q);
	pVp8DecParam->y2dc_sign = (pPictureHeader->y2dc_delta_q < 0);
	pVp8DecParam->y2dc_absdelta_q = ABS(pPictureHeader->y2dc_delta_q);
	pVp8DecParam->y2ac_sign = (pPictureHeader->y2ac_delta_q < 0);
	pVp8DecParam->y2ac_absdelta_q = ABS(pPictureHeader->y2ac_delta_q);	
	pVp8DecParam->uvdc_sign = (pPictureHeader->uvdc_delta_q < 0);
	pVp8DecParam->uvdc_absdelta_q = ABS(pPictureHeader->uvdc_delta_q);
	pVp8DecParam->uvac_sign = (pPictureHeader->uvac_delta_q < 0);
	pVp8DecParam->uvac_absdelta_q = ABS(pPictureHeader->uvac_delta_q);

	pVp8DecParam->prob_intra = pPictureHeader->prob_intra;
	pVp8DecParam->prob_last = pPictureHeader->prob_last;
	pVp8DecParam->prob_gf = pPictureHeader->prob_gf;

	pVp8DecParam->value = pPictureHeader->bc.value;
	pVp8DecParam->range = pPictureHeader->bc.range;
	pVp8DecParam->count = pPictureHeader->bc.count;

	pVp8DecParam->SegIdAddr = pVp8CodecInfo->SegIdAddr;
	
    pCur = FSP_GetLogicFs(pCtx->ChanID, pVp8CodecInfo->CurFsID);	
    pGolden = FSP_GetLogicFs(pCtx->ChanID, pVp8CodecInfo->GoldenFsID);	
    pAlt = FSP_GetLogicFs(pCtx->ChanID, pVp8CodecInfo->AltFsID);	
    pLast = FSP_GetLogicFs(pCtx->ChanID, pVp8CodecInfo->LastFsID);
	if ((pCur == NULL) || (pGolden == NULL) || (pAlt == NULL) || (pLast == NULL))
	{
	    dprint(PRN_ERROR, "VP8_Set_DecParam but logic fs is null!\n");
	    return VP8_VFMW_FALSE;
	}
    if (pCur->pstDecodeFs == NULL)
    {
	    dprint(PRN_ERROR, "VP8_Set_DecParam but cur logic pstDecodeFs is null!\n");
	    return VP8_VFMW_FALSE;
    }
    pVp8DecParam->image_curr_rcn_addr = pCur->pstDecodeFs->PhyAddr;
    pVp8DecParam->CurrPmvAddr = pCur->PmvAddr;
    pVp8DecParam->image_gld_ref_addr = (NULL != pGolden->pstDecodeFs)?pGolden->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
    pVp8DecParam->image_alt_ref_addr = (NULL != pAlt->pstDecodeFs)?pAlt->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
    pVp8DecParam->image_last_ref_addr = (NULL != pLast->pstDecodeFs)?pLast->pstDecodeFs->PhyAddr: pCur->pstDecodeFs->PhyAddr;
    pVp8CodecInfo->ddr_stride = pCur->pstDispOutFs->Stride;
	pVp8DecParam->ddr_stride = pVp8CodecInfo->ddr_stride;

	for (i = 0 ;i < 4; i++) 
	{
		pVp8DecParam->segment_feature_dat0[i] = pPictureHeader->segment_feature_data[0][i];
		pVp8DecParam->segment_feature_dat1[i] = pPictureHeader->segment_feature_data[1][i];
		pVp8DecParam->ref_lf_delta[i] = pPictureHeader->ref_lf_deltas[i];
		pVp8DecParam->mode_lf_delta[i] = pPictureHeader->mode_lf_deltas[i];
		pVp8DecParam->ref_frame_sign_bias[i]  = pPictureHeader->ref_frame_sign_bias[i];
	}

	tab_virt_addr = pVp8DecParam->table;

	_ptr_msg_bank = tab_virt_addr;
	memset(_ptr_msg_bank, 0, 16);	
    _ptr_msg_bank[0] = pPictureHeader->prob_skip_false;
    _ptr_msg_bank[1] = pPictureHeader->mb_segment_tree_probs[0];
    _ptr_msg_bank[2] = pPictureHeader->mb_segment_tree_probs[1];
    _ptr_msg_bank[3] = pPictureHeader->mb_segment_tree_probs[2];
    _ptr_msg_bank[4] = pPictureHeader->prob_intra;
    _ptr_msg_bank[5] = pPictureHeader->prob_last;
    _ptr_msg_bank[6] = pPictureHeader->prob_gf;

	_ptr_msg_bank = tab_virt_addr +  0x10;
	memset(_ptr_msg_bank, 0, 16);
	_ptr_msg_bank[0] = pPictureHeader->fc.ymode_prob[0];
    _ptr_msg_bank[1] = pPictureHeader->fc.ymode_prob[1];
    _ptr_msg_bank[2] = pPictureHeader->fc.ymode_prob[2];
    _ptr_msg_bank[3] = pPictureHeader->fc.ymode_prob[3];
    _ptr_msg_bank[4] = pPictureHeader->fc.uv_mode_prob[0];
    _ptr_msg_bank[5] = pPictureHeader->fc.uv_mode_prob[1];
    _ptr_msg_bank[6] = pPictureHeader->fc.uv_mode_prob[2];

	_ptr_msg_bank = tab_virt_addr +  0x20;
	memset(_ptr_msg_bank,0,16);
	
	_ptr_msg_bank = tab_virt_addr +  0x30;
	memset(_ptr_msg_bank,0,16);

	_ptr_msg_bank = tab_virt_addr + 0x2c0;
	memset(_ptr_msg_bank,0,16);
    _ptr_msg_bank[0] = pPictureHeader->fc.mvc[0].prob[1];//sign[x]
    _ptr_msg_bank[1] = pPictureHeader->fc.mvc[0].prob[0];//is_short[x] 
    _ptr_msg_bank[2] = pPictureHeader->fc.mvc[0].prob[2];//short
    _ptr_msg_bank[3] = pPictureHeader->fc.mvc[0].prob[3];
    _ptr_msg_bank[4] = pPictureHeader->fc.mvc[0].prob[4];
    _ptr_msg_bank[5] = pPictureHeader->fc.mvc[0].prob[5];
    _ptr_msg_bank[6] = pPictureHeader->fc.mvc[0].prob[6];
    _ptr_msg_bank[7] = pPictureHeader->fc.mvc[0].prob[7];
    _ptr_msg_bank[8] = pPictureHeader->fc.mvc[0].prob[8];
    
	_ptr_msg_bank = tab_virt_addr + 0x2d0;
    memset(_ptr_msg_bank, 0, 16);	
    _ptr_msg_bank[0] = pPictureHeader->fc.mvc[0].prob[1];//sign[x]
    _ptr_msg_bank[1] = pPictureHeader->fc.mvc[0].prob[9];//long[x]
    _ptr_msg_bank[2] = pPictureHeader->fc.mvc[0].prob[10];
    _ptr_msg_bank[3] = pPictureHeader->fc.mvc[0].prob[11];
    _ptr_msg_bank[4] = pPictureHeader->fc.mvc[0].prob[12];
    _ptr_msg_bank[5] = pPictureHeader->fc.mvc[0].prob[13];
    _ptr_msg_bank[6] = pPictureHeader->fc.mvc[0].prob[14];
    _ptr_msg_bank[7] = pPictureHeader->fc.mvc[0].prob[15];
    _ptr_msg_bank[8] = pPictureHeader->fc.mvc[0].prob[16];
    _ptr_msg_bank[9] = pPictureHeader->fc.mvc[0].prob[17];
    _ptr_msg_bank[10]= pPictureHeader->fc.mvc[0].prob[18];
 
	_ptr_msg_bank = tab_virt_addr + 0x2e0;
    memset(_ptr_msg_bank,0,16);	
    _ptr_msg_bank[0] = pPictureHeader->fc.mvc[1].prob[1];//sign[y]
    _ptr_msg_bank[1] = pPictureHeader->fc.mvc[1].prob[0];//is_short[y]
    _ptr_msg_bank[2] = pPictureHeader->fc.mvc[1].prob[2];//short
    _ptr_msg_bank[3] = pPictureHeader->fc.mvc[1].prob[3];
    _ptr_msg_bank[4] = pPictureHeader->fc.mvc[1].prob[4];
    _ptr_msg_bank[5] = pPictureHeader->fc.mvc[1].prob[5];
    _ptr_msg_bank[6] = pPictureHeader->fc.mvc[1].prob[6];
    _ptr_msg_bank[7] = pPictureHeader->fc.mvc[1].prob[7];
    _ptr_msg_bank[8] = pPictureHeader->fc.mvc[1].prob[8];
    
	_ptr_msg_bank = tab_virt_addr + 0x2f0;
    memset(_ptr_msg_bank,0,16);	
    _ptr_msg_bank[0] = pPictureHeader->fc.mvc[1].prob[1];//sign[y]
    _ptr_msg_bank[1] = pPictureHeader->fc.mvc[1].prob[9];//long[y]
    _ptr_msg_bank[2] = pPictureHeader->fc.mvc[1].prob[10];
    _ptr_msg_bank[3] = pPictureHeader->fc.mvc[1].prob[11];
    _ptr_msg_bank[4] = pPictureHeader->fc.mvc[1].prob[12];
    _ptr_msg_bank[5] = pPictureHeader->fc.mvc[1].prob[13];
    _ptr_msg_bank[6] = pPictureHeader->fc.mvc[1].prob[14];
    _ptr_msg_bank[7] = pPictureHeader->fc.mvc[1].prob[15];
    _ptr_msg_bank[8] = pPictureHeader->fc.mvc[1].prob[16];
    _ptr_msg_bank[9] = pPictureHeader->fc.mvc[1].prob[17];
    _ptr_msg_bank[10]= pPictureHeader->fc.mvc[1].prob[18];

    for(_plane =0; _plane<4;_plane++)
    {
        for(_band =0;_band<8;_band++)
        {
            for(_prec=0;_prec<3;_prec++)
            {
                _dst_phy_offset = 0x300 + (_plane*24 +  _band*3 +  _prec)*0x10;
                _src_vir_addr =  &(pPictureHeader->fc.coef_probs[_plane][_band][_prec][0]);  
    			_ptr_msg_bank = tab_virt_addr + _dst_phy_offset;
				memset(_ptr_msg_bank,0,16);
                memcpy(_ptr_msg_bank, _src_vir_addr, 11);
            }
        }
    }

	offset = (VP8_KEY_FRAME == pPictureHeader->frame_type) ? 10 : 3;

	pVp8DecParam->stream_base_addr = (pVp8StreamParam->PhyAddr & 0xFFFFFFF0) -16; //caution	
	pVp8DecParam->bit_len_0	= (pPictureHeader->first_partition_length_in_bytes * 8) - BsPos(pBs)
         +offset*8;  //+ 128;   //q45134 add 16 byte to test

	ByteA = (pVp8StreamParam->PhyAddr & 0xF) + 16 + (BsPos(pBs) / 8);	
	pVp8DecParam->bit_offset_0 = ((ByteA & 0xF) << 3) + (BsPos(pBs) % 8);
	pVp8DecParam->bit_byte_offset_0 = (ByteA) & 0xFFFFFFF0; 
	
	pVp8DecParam->bit_len_1 = 0;
	pVp8DecParam->bit_offset_1 = 0;
	pVp8DecParam->bit_byte_offset_1 = 0;


	VirAddr_1 = pVp8StreamParam->VirAddr + offset + 
			pPictureHeader->first_partition_length_in_bytes;	
	ByteLen_1 = pVp8StreamParam->Length - offset - 
			pPictureHeader->first_partition_length_in_bytes;

	//Get bs part len start
	source = VirAddr_1;
	source_start = source;
	num_part = 1 << pPictureHeader->multi_token_partition;
	pVp8DecParam->stream_num_part = num_part;

	if (num_part > 1)
	{
	    source_start += (num_part - 1) * 3;
	}

	for (i = 0; i < num_part; i++)
	{
	    if (i < num_part - 1)
	    {
	        length = source[0] + (source[1] << 8) + (source[2] << 16);
	    }
	    else
	    {
	        length = ByteLen_1 - (source_start - source) - (num_part - 1) * 3;
	    }

	    BsLen[i] = length;
	    source += 3;
	    source_start += length;
	}

	//Get bs part len end
	ByteB = pPictureHeader->first_partition_length_in_bytes + 
				offset + (pVp8StreamParam->PhyAddr % 0x10); 

	for (i = 0; i< num_part; i++)
	{
	    if (0 == i)
	    {
	        Byte[i] = ByteB + (num_part - 1) * 3;
	    }
	    else
	    {
	        Byte[i] = Byte[i-1] + BsLen[i-1];
	    }
		
		pVp8DecParam->bitn_len_0[i] = BsLen[i] * 8;  // + 128;   //q45134 add 16 byte to test
		pVp8DecParam->bitn_offset_0[i] = ((Byte[i] & 0xF) << 3);
		pVp8DecParam->bitn_byte_offset_0[i] = (Byte[i] & 0xFFFFFFF0) + 16;
		pVp8DecParam->bitn_len_1[i] = 0;
		pVp8DecParam->bitn_offset_1[i] = 0;
		pVp8DecParam->bitn_byte_offset_1[i] = 0;
	}
	
	pCtx->pVp8DecParam = &(pCtx->Vp8DecParam);
	pCtx->pVp8DecParam->Compress_en = pCtx->pstExtraData->s32Compress_en;

	return VP8_VFMW_TRUE;
}


VOID VP8_Update_PictHeader(VP8_CODECINF *pVp8CodecInfo)
{
	VP8_PICTUREHEADER_S *pOldPicHeader = &pVp8CodecInfo->OldHeaderInfo;
    VP8_PICTUREHEADER_S *pNewPicHeader = &pVp8CodecInfo->NewHeaderInfo;

    if (pNewPicHeader->refresh_entropy_probs == 0)
    {
        memcpy(&pNewPicHeader->fc, &pNewPicHeader->lfc, sizeof(FRAME_CONTEXT));
    }
    

	memcpy(pOldPicHeader,pNewPicHeader,sizeof(VP8_PICTUREHEADER_S));
	
    pVp8CodecInfo->LastFrameType = pNewPicHeader->frame_type;
    pVp8CodecInfo->LastFilterType = pNewPicHeader->filter_type;
    pVp8CodecInfo->LastSharpnessLevel = pNewPicHeader->sharpness_level;
    
    pVp8CodecInfo->refresh_last_frame = pNewPicHeader->refresh_last_frame;    
}


SINT32 VP8DEC_Decode(VP8_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{	
	BS *pBs = &pCtx->Bs;
	VP8_CODECINF *pVp8CodecInfo = &pCtx->Vp8CodecInfo;
//    STREAM_PARAM StreamParam;	
//    STREAM_PARAM *pStreamParam = &StreamParam;		
    VP8_PICTUREHEADER_S *pOldPicHeader = &pVp8CodecInfo->OldHeaderInfo;
    VP8_PICTUREHEADER_S *pNewPicHeader = &pVp8CodecInfo->NewHeaderInfo;
	SINT32 ret;
	IMAGE *pImage;

    pCtx->StreamParam.VirAddr = pPacket->StreamPack[0].VirAddr;
    pCtx->StreamParam.PhyAddr = pPacket->StreamPack[0].PhyAddr;
    pCtx->StreamParam.Length  = pPacket->StreamPack[0].LenInByte;	

    if (pCtx->StreamParam.Length < 3)
    {
        dprint(PRN_ERROR, "Error!Truncated packet\n");
		return VP8_VFMW_FALSE;
    }
	
	BsInit(pBs, pCtx->StreamParam.VirAddr, pCtx->StreamParam.Length);
	pCtx->pVp8StreamParam = &(pCtx->StreamParam);

    /* decode picture header */
	ret = VP8_GetPictureHeader(pBs, pVp8CodecInfo, pCtx->StreamParam.Length);
	if ( VP8_VFMW_TRUE != ret)
    {
        dprint(PRN_CTRL, "VP8_CB_GetPictureHeader Error!\n");
        return VP8_VFMW_FALSE;  
    }
	
    /* alloc pic frame buffer when size change or first init */
    if ( (VP8_VFMW_FALSE == pVp8CodecInfo->Imgbuf_allocated) ||
         (pOldPicHeader->pic_width_in_mb != pNewPicHeader->pic_width_in_mb) ||
         (pOldPicHeader->pic_height_in_mb != pNewPicHeader->pic_height_in_mb) )
    {
        REPORT_IMGSIZE_CHANGE(pCtx->ChanID, pOldPicHeader->pic_width_in_mb, pOldPicHeader->pic_height_in_mb,\
            pNewPicHeader->pic_width_in_mb, pNewPicHeader->pic_height_in_mb);
		VP8_CLEARREFFLAG;
		VP8_CLEARREFNUM;		
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
		
		if((pNewPicHeader->pic_width_in_mb > MAX_IMG_WIDTH_IN_MB) ||
				(pNewPicHeader->pic_height_in_mb > MAX_IMG_HEIGHT_IN_MB))
		{
			dprint(PRN_PIC, "pic width/height to large,MbWidth = %d, MbHeight = %d",
				pNewPicHeader->pic_width_in_mb,
				pNewPicHeader->pic_height_in_mb);
			return VP8_VFMW_FALSE;
		}
		
        if ((pCtx->pstExtraData->stChanOption.s32ReRangeEn == 0)&&(pCtx->pstExtraData->eCapLevel == CAP_LEVEL_USER_DEFINE_WITH_OPTION))
        {
            if (pVp8CodecInfo->Imgbuf_allocated == VP8_VFMW_FALSE)
            {
                ResetVoQueue(&pCtx->ImageQue);
            }
        }
        else 
        {
            //未分配或者大小变化后,需要修改VO管理结构内的信息        
            ResetVoQueue(&pCtx->ImageQue);
        }
		
		ret = VP8_ArrangeVHBMem(pCtx);
		if (VP8_VFMW_TRUE != ret)
        {
			dprint(PRN_ERROR, "VP8_ArrangeVHBMem error\n");
			return VP8_VFMW_FALSE;
        }
    }

	ret = VP8_DecodeDecide(pCtx);
	if (ret != VP8_VFMW_TRUE)
	{
		dprint(PRN_ERROR, "VP8_DecodeDecide err\n");   
        return VP8_VFMW_FALSE;
	}
	    
	ret = VP8_GetImageBuffer(pCtx);
	if(ret != VP8_VFMW_TRUE)
	{
		dprint(PRN_ERROR, "VP8_GetBufFromQueue err\n");   
        return VP8_VFMW_FALSE;
	}
	//FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->CurFsID, 1);
    pImage = FSP_GetFsImagePtr(pCtx->ChanID, pVp8CodecInfo->CurFsID);
    if (NULL == pImage)
    {
        dprint(PRN_DBG, "line: %d, pImage is NULL!\n", __LINE__);
        return VP8_VFMW_FALSE;
    }

	pImage->PTS = pCtx->pstExtraData->pts;
	pImage->Usertag = pCtx->pstExtraData->Usertag;
	pImage->DispTime = pCtx->pstExtraData->DispTime;
    pImage->DispEnableFlag = pCtx->pstExtraData->DispEnableFlag;
    pImage->DispFrameDistance = pCtx->pstExtraData->DispFrameDistance;
    pImage->DistanceBeforeFirstFrame = pCtx->pstExtraData->DistanceBeforeFirstFrame;
	pImage->GopNum = pCtx->pstExtraData->GopNum;

	pImage->is_fld_save = 0;
    pCtx->pstExtraData->pts = (UINT64)(-1);
	dprint(PRN_PTS,"dec_pts: %lld Usertag = %lld\n",pImage->PTS,pImage->Usertag);

	/*if we get a key frame ,alt,last,golden should all be release*/
    if (VP8_KEY_FRAME == pVp8CodecInfo->FrameType)
    {
        if (pVp8CodecInfo->AltFsID!=pVp8CodecInfo->CurFsID)
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->AltFsID, 0);
        }
        if (pVp8CodecInfo->LastFsID!=pVp8CodecInfo->CurFsID)
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->LastFsID, 0);
        }
		if (pVp8CodecInfo->GoldenFsID!=pVp8CodecInfo->CurFsID)
        {
            FSP_SetRef(pCtx->ChanID, pVp8CodecInfo->GoldenFsID, 0);
        }
		pVp8CodecInfo->RefNum = 0;
    }

	/*config decparam for vdh*/
	VP8_Set_DecParam(pCtx);
			
	VP8_Update_PictHeader(pVp8CodecInfo);
		
    return 0;
}



SINT32 VP8DEC_RecycleImage(VP8_CTX_S *pCtx,UINT32 ImgID)
{
    IMAGE *pImg;

    FSP_SetDisplay(pCtx->ChanID, ImgID, 0);
	pImg = FSP_GetFsImagePtr(pCtx->ChanID, ImgID);
	if (NULL != pImg)
	{
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[0]);
        pImg->p_usrdat[0] = NULL;
        FreeUsdByDec(pCtx->ChanID, pImg->p_usrdat[1]);
        pImg->p_usrdat[1] = NULL;            
	}
	
    return VP8_VFMW_TRUE;	
}



SINT32 VP8DEC_GetRemainImg(VP8_CTX_S *pCtx)
{
    SINT32 ret;

    ret = GetVoLastImageID(&pCtx->ImageQue);

    return ret;
}

SINT32 VP8DEC_GetImageBuffer(VP8_CTX_S *pCtx)
{
	/* 如果FSP中有新的帧存可以获取，返回TRUE */
    if (FSP_IsNewFsAvalible(pCtx->ChanID) == 1)
    {
        return 1;
	}
    else if (FSP_IsNewFsAvalible(pCtx->ChanID) == -1)
    {
        FSP_ClearNotInVoQueue(pCtx->ChanID, &(pCtx->ImageQue));
    }

    return 0;
}


#endif //VP8_ENABLE

