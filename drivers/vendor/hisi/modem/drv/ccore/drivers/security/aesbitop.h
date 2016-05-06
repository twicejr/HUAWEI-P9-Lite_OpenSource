/**********************************************************************
 Basic Bit Operations
 Author: Algorithm Team of Security Solution Department. SunYi 15569
***********************************************************************
					Copyright 2005 HuaWei Tech. Inc.
						ALL RIGHTS RESERVED
**********************************************************************/

/**********************************************************************
 Bit Operation Macros
 FUNCTION:	bitwise operations
**********************************************************************/

#ifndef _AESBITOP_H_
#define _AESBITOP_H_

/* Circular rotate of 32 bit values */
#define ROTR(x,n)   (((x) >> ((uint16)(n))) | ((x) << (32 - (uint16)(n))))
#define ROTL(x,n)   (((x) << ((uint16)(n))) | ((x) >> (32 - (uint16)(n))))
/* Invert byte order in a 32 bit variable */
#define BSWAP(x)    ((ROTL((x), 8) & 0x00ff00ff) | (ROTR((x), 8) & 0xff00ff00))
/* Extract byte from a 32 bit quantity (little endian notation) */ 
#define BYTEN(x,n)   ((uint8)((x) >> (8 * (n))))

#endif /* _BITOP_H_ */

