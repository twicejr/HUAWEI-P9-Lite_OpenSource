/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhEDlG50G/Vcvyq2txYFjqt/X5GLe/SnYbE4r/A06
+TaRl3rPbLFcxxqC+cowd4+AXvtGkYL1M5lElKZpUQtWRVQjtsJoKO/e8Xbvc0lV864HSNaZ
nd/nLTo7T787yhBNFXbO9FrgIy6prrD52Y4dkWakFN46JNaBuAmoPerqBkyrAQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************
*
* Copyright (c) 2006 HUAWEI - All Rights Reserved
*
* File: $basedef.h$
* Date: $2006/11/30$
* Revision: $v1.0$
* Purpose: basic definition common in the whole project
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2006/11/30       z56361            Original
*
* Dependencies:
*
************************************************************************/

#ifndef __BASETYPE_DEFS__
#define __BASETYPE_DEFS__

#ifdef __cplusplus
extern "C" {
#endif

#include "sysconfig.h"
#ifdef ENV_SOS_KERNEL
#include "sos_kernel_osal.h"
#else
#include "linux_kernel_osal.h"
#endif
#include "vfmw_osal_ext.h"

/*************************************************************************
 *	This software supports the following platform. Platform is defined in
 *  the according compile environment( eg. use '-D' in the makefile ).
 
 *      ENV_ARMLINUX_KERNEL     --- final version
 *************************************************************************/


/*************************************************************************
 *	compile switches.
 *************************************************************************/

#define H264_ENABLE
#define MVC_ENABLE
#define MPEG2_ENABLE
#define AVS_ENABLE
#define MPEG4_ENABLE
#define REAL8_ENABLE
#define REAL9_ENABLE
#define VC1_ENABLE
#define DIVX3_ENABLE
#define VP6_ENABLE
#define VP8_ENABLE
#define HEVC_ENABLE


/*************************************************************************
 *	macro
 *************************************************************************/

#ifdef VFMW_RECPOS_SUPPORT
#define REC_POS(Data)  DBG_AddTrace((SINT8*)__FUNCTION__, __LINE__, (SINT32)Data)
#else
#define REC_POS(Data)
#endif

/* MAX()/MIN(): 最大最小 */
#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))
#define ABS(x)            (( (x) <  0  ) ? -(x) : (x))
#define SIGN(a)           (( (a)<0 ) ? (-1) : (1))
#define MEDIAN(a, b, c)   ((a) + (b) + (c) - MIN((a), MIN((b), (c))) - MAX((a), MAX((b), (c))))

#define CLIP1(high, x)             (MAX( MIN((x), high), 0))
#define CLIP3(low, high, x)        (MAX( MIN((x), high), low))
#define CLIP255(x)                 (MAX( MIN((x), 255), 0))

#ifdef  HI_ADVCA_FUNCTION_RELEASE
#define pos()  
#else  
#define pos()  dprint(PRN_ALWS,"%s: L%d\n", __FUNCTION__, __LINE__)
#endif

#ifdef __cplusplus
}
#endif

#endif	//end of "#ifndef __BASETYPE_DEFS__"

