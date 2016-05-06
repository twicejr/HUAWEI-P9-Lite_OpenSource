/** ****************************************************************************

                    Huawei Technologies Sweden AB (C), 2001-2011

 ********************************************************************************
 * @file      uphy_type_define.h
 * @author    jgw15887
 * @version
 * @date      2013-11-06
 * @file
 * This file defines types needed to ensure the same size on both sides of an
 * inter processor interface.
 *
 * @copyright Huawei Technologies Sweden AB
 *******************************************************************************/
#ifndef __UPHY_TYPE_DEFINE_H__
#define __UPHY_TYPE_DEFINE_H__

#ifndef _SDR_FEATURE_ON
/*****************************************************************************
  This part is for use on the ARM only
*****************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
                                                                              /* _H2ASN_Skip */
typedef  unsigned char              PHY_UINT8;
typedef  unsigned short             PHY_UINT16;                            /* range(0..2^16 -1) */
typedef  short                      PHY_INT16;                             /* range(-2^15..2^15-1) */
typedef  unsigned long              PHY_UINT32;                            /* range(0..2^32 -1) */
typedef  long                       PHY_INT32;                             /* range(-2^31..2^31-1) */
typedef  long long                  PHY_INT40;                             /* range(-2^39..2^39-1) */      /* _H2ASN_Skip */
typedef  unsigned long long         PHY_UINT64;
typedef  signed long long           PHY_INT64;
typedef  unsigned long              PHY_ULONG;

typedef  float                      PHY_FLOAT;                             /* range(10^-37..10^38) */
typedef  double                     PHY_DOUBLE;                            /* range(10^-37..10^38) */
typedef  void                       PHY_VOID;
typedef  int                        PHY_INT;
typedef  unsigned int               PHY_UINT;

#define PHY_NULL (NULL)
#define PHY_FALSE (0)
#define PHY_TRUE (1)

/*****************************************************************************
  3 Enumerations declarations
*****************************************************************************/


/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/


/*****************************************************************************
  5 Message declaration
*****************************************************************************/


/*****************************************************************************
  6 STRUCT and UNION declaration
*****************************************************************************/


/*****************************************************************************
  7 Global  declaration
*****************************************************************************/


/*****************************************************************************
  8 Function declarations
*****************************************************************************/

/*****************************************************************************
  9 Other declaration
*****************************************************************************/



#ifdef __cplusplus
}
#endif
/*****************************************************************************
  End of the part for use on the ARM only
*****************************************************************************/
#endif

#endif /* end of uphy_type_define.h */
