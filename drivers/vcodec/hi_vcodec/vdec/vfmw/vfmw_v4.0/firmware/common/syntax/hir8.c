/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQmBGNJUeil4IeOcC9MMN4egmVJdYxxrjV4KwlJQ
Z7kP5xgafk7nHke3wOh8tna9aE0BBLqsnB+4GfZJNogYHojemNC7tmOjo1I5n/MuDIZDULKX
7hx7/SfJ3tP3Pb/Hy8o84QE8XWe8MKItyskRyMIO7AFdKDBdCMlM6zX/2vL4qw==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/

#include    "syntax.h"
#include    "real8.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef REAL8_ENABLE

SINT32 REAL8DEC_Init(RV8_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{

    return 0;
}

VOID REAL8DEC_Destroy(RV8_CTX_S *pCtx)
{
    return;
}

SINT32 REAL8DEC_Decode(RV8_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    return RV8_VFMW_FALSE;
}

SINT32 REAL8DEC_Decode_User(RV8_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    return RV8_VFMW_FALSE;
}

SINT32 REAL8DEC_RecycleImage(RV8_CTX_S *pCtx, UINT32 ImgID)
{
    return RV8_VFMW_FALSE;
}

SINT32 REAL8DEC_GetRemainImg(RV8_CTX_S *pCtx)
{
    return -1;
}

UINT32 REAL8DEC_VDMPostProc(RV8_CTX_S *pCtx, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic)
{
    return RV8_VFMW_FALSE;
}

SINT32 REAL8DEC_GetImageBuffer( RV8_CTX_S *pCtx )
{
    return 0;
}

VOID REAL8DEC_Support(SINT32 *flag)
{
    *flag = 0;
    return;
}

#endif //REAL8_VFMW_ENABLE
