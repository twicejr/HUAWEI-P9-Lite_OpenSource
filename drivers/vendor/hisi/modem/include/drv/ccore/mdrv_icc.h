#ifndef __MDRV_CCORE_ICC_H__
#define __MDRV_CCORE_ICC_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_icc_common.h"

/*
	ICC channels
*/

typedef enum tagMDRV_ICC_TYPE
{
	MDRV_ICC_VT_VOIP,                   /* for LTE video phone use, ACORE<-->CCORE */
    MDRV_ICC_GUOM0,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM1,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM2,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM3,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM4,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM5,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM6,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_GUOM7,                     /* for GU OM use, ACORE<-->CCORE */
    MDRV_ICC_CCPU_HIFI_VOS_NORMAL_MSG,  /* for GU voice use, Ccore<--> HIFI */
    MDRV_ICC_CCPU_HIFI_VOS_URGENT_MSG,  /* for GU voice use, Ccore<--> HIFI */
    MDRV_ICC_HIFI_TPHY_MSG_NRM,         /* for TDS voice use, Ccore<--> HIFI */
    MDRV_ICC_HIFI_TPHY_MSG_URG,         /* for TDS voice use, Ccore<--> HIFI */
    MDRV_ICC_MAX
} MDRV_ICC_TYPE_E;

#ifdef __cplusplus
}
#endif
#endif
