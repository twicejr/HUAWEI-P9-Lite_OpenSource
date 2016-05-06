/*!
 *****************************************************************************
 *
 * @File       defs.h
 * @Title      Defines for accessing fields within regiaters.
 * @Description    Defines for accessing fields within regiaters.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if !defined DEFS_H_SENTRY
#define DEFS_H_SENTRY

#include "img_types.h"

/******************************************************************************
 *	Pragma definitions
 *****************************************************************************/
#ifdef WIN32
/*
	prevent warnings about inlining functions
*/
#pragma warning (disable: 4711)

/*
	Prevent warnings from the code coverage pragmas
*/
#pragma warning (disable: 4068)
#endif

/*
	MACROS to insert values into fields within a word. The basename of the
	field must have MASK_BASENAME and SHIFT_BASENAME constants.
*/
#define F_MASK(basename)  (MASK_##basename)
#define F_SHIFT(basename) (SHIFT_##basename)
#define F_MASK_MVEA(basename)  (MASK_MVEA_##basename)   /*	MVEA	*/
#define F_SHIFT_MVEA(basename) (SHIFT_MVEA_##basename)   /*	MVEA	*/
/*
	Extract a value from an instruction word.
*/
#define F_EXTRACT(val,basename) (((val)&(F_MASK(basename)))>>(F_SHIFT(basename)))

/*
	Mask and shift a value to the position of a particular field.
*/
#define F_ENCODE(val,basename)  (((val)<<(F_SHIFT(basename)))&(F_MASK(basename)))
#define F_DECODE(val,basename)  (((val)&(F_MASK(basename)))>>(F_SHIFT(basename)))
#define F_ENCODE_MVEA(val,basename)  (((val)<<(F_SHIFT_MVEA(basename)))&(F_MASK_MVEA(basename)))
/*obligee de definir F_ENCODE_MVEA car le nouveau ESB utilise des noms de registres differents*/

/*
	Insert a value into a word.
*/
#define F_INSERT(word,val,basename) (((word)&~(F_MASK(basename))) | (F_ENCODE((val),basename)))

/*
	Extract a 2s complement value from an word, and make it the correct sign
	Works by testing the top bit to see if the value is negative
*/
#define F_EXTRACT_2S_COMPLEMENT( Value, Field ) ((IMG_INT32)(((((((F_MASK( Field ) >> F_SHIFT( Field )) >> 1) + 1) & (Value >> F_SHIFT( Field ))) == 0) ? F_EXTRACT( Value, Field ) : (-(IMG_INT32)(((~Value & F_MASK( Field )) >> F_SHIFT( Field )) + 1)))))

/*
	B stands for 'bitfield', defines should be in the form
	#define FIELD_NAME 10:8		(i.e. upper : lower, both inclusive)
*/
#define B_EXTRACT( Data, Bits ) (((Data) & ((IMG_UINT32)0xffffffff >> (31 - (1 ? Bits)))) >> (0 ? Bits))
#define B_MASK( Bits ) ((((IMG_UINT32)0xffffffff >> (31 - (1 ? Bits))) >> (0 ? Bits)) << (0 ? Bits))
#define B_ENCODE( Data, Bits ) (((Data) << (0 ? Bits)) & (B_MASK( Bits )))
#define B_INSERT( Word, Data, Bits ) (((Word) & ~(B_MASK( Bits ))) | (B_ENCODE( Data, Bits )))

/*
	B_BIT returns boolean true if the corresponding bit is set
	defines must be in the form FIELD_NAME 10:8 as above, except
	that the bitfield must obviously be only 1 bit wide
*/
#define B_BIT( Word, Bits ) ((((Word) >> (0 ? Bits)) & 1) == 1)


#endif /* __DEFS_H_SENTRY */
