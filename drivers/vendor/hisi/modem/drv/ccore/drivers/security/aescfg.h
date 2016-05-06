/**********************************************************************
 AES(Advanced Encryption Standard) Algorithm Configuration
 Author: Algorithm Team of Security Solution Department. SunYi 15569
***********************************************************************
					Copyright 2005 HuaWei Tech. Inc.
						ALL RIGHTS RESERVED
***********************************************************************
 This is an independent implementation of the encryption algorithm:
           RIJNDAEL by Joan Daemen and Vincent Rijmen
 which is choosed as AES(Advanced Encryption Standard) algorithm by
 NIST(National Institute of Standards and Technology, US).
***********************************************************************
 This implemention references the implemention of Dr Brian Gladman
 (gladman@seven77.demon.co.uk) 14th January 1999.
**********************************************************************/

/**********************************************************************
 AES configuration
 FUNCTION:	to configurate platform and performance properties
**********************************************************************/

#ifndef _AESCFG_H_
#define _AESCFG_H_

/* FORCE_ALIGN for the platforms that can't access multi-byte-word with non-aligned address. May slower the performance. */
#define FORCE_ALIGN 1
/* Gen tables that only for last round transform, spend 8k bytes more for make tables. */
#define LARGE_TABLES 1

#endif /* _AESCFG_H_ */

