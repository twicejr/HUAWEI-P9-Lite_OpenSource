/*!
 *****************************************************************************
 *
 * @File       reg_io2.h
 * @Title      Light weight register access macros.
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

#if !defined (__REG_IO2_H__)
#define __REG_IO2_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_defs.h"
#include "img_types.h"

#ifdef DOXYGEN_CREATE_MODULES
/**
 * @defgroup IMGLIB_REGIO IMGLIB: Register IO interface
 * @Title Light weight register access macros.
 * @{
 */
/*-------------------------------------------------------------------------
 * Following elements are in the IMGLIB_REGIO documentation module
 *------------------------------------------------------------------------*/
#endif

/*!
******************************************************************************

 @Macro	REGIO_READ_FIELD
 
 @Title     This macro is used to extract a field from a register.

 @Input		ui32RegValue: 		The register value.

 @Input		group: 		The name of the group containing the register from which 
						the field is to be extracted.

 @Input		reg: 		The name of the register from which the field is to 
						be extracted.

 @Input		field: 		The name of the field to be extracted.
  
 @Return	IMG_UINT32:	The value of the field - right aligned.

******************************************************************************/

#if 1
#define REGIO_READ_FIELD(ui32RegValue, group, reg, field)							\
	((ui32RegValue & group##_##reg##_##field##_MASK) >> group##_##reg##_##field##_SHIFT)

#else

#define REGIO_READ_FIELD(ui32RegValue, group, reg, field)							\
	((ui32RegValue >> group##_##reg##_##field##_SHIFT) & group##_##reg##_##field##_LSBMASK)

#endif

/*!
******************************************************************************

 @Macro	REGIO_READ_REPEATED_FIELD
 
 @Title     This macro is used to extract the value of a repeated from a register.

 @Input		ui32RegValue: 		The register value.

 @Input		group: 		The name of the group containing the register from which 
						the field is to be extracted.

 @Input		reg: 		The name of the register from which the field is to 
						be extracted.

 @Input		field: 		The name of the field to be extracted.

 @Input		ui32RepIndex: 		The repeat index of the field to be extracted.
  
 @Return	IMG_UINT32:	The value of the field - right aligned.

******************************************************************************/
#define REGIO_READ_REPEATED_FIELD(ui32RegValue, group, reg, field, ui32RepIndex)	\
	( IMG_ASSERT(ui32RepIndex < group##_##reg##_##field##_NO_REPS),					\
	((ui32RegValue & (group##_##reg##_##field##_MASK >> ((group##_##reg##_##field##_NO_REPS - (ui32RepIndex) - 1) * group##_##reg##_##field##_SIZE)))	\
	>> (group##_##reg##_##field##_SHIFT - ((group##_##reg##_##field##_NO_REPS - (ui32RepIndex) - 1) * group##_##reg##_##field##_SIZE))) )

/*!
******************************************************************************

 @Macro	REGIO_READ_REGISTER
 
 @Title     This macro is used to read a register.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		group: 		The name of the group containing the register to be
						read.

 @Input		reg: 		The name of the register to be read.
  
 @Return	IMG_UINT32:	The value of the register.

******************************************************************************/
#define REGIO_READ_REGISTER(ui32DevId, group, reg)			\
	group##_ReadRegister(ui32DevId, group##_##reg##_OFFSET)

/*!
******************************************************************************

 @Macro	REGIO_READ_PIPE_REGISTER
 
 @Title     This macro is used to read from one of PVDEC's pipe register.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		ui8Pipe: 		The pipe number.

 @Input		group: 		The name of the group containing the register to be
						read.

 @Input		reg: 		The name of the register to be read.
  
 @Return	IMG_UINT32:	The value of the register.

******************************************************************************/
#define REGIO_READ_PIPE_REGISTER(ui32DevId, pipe, group, reg)			\
	group##_ReadPipeRegister(ui32DevId, pipe, group##_##reg##_OFFSET)

/*!
******************************************************************************

 @Macro	REGIO_READ_TABLE_REGISTER
 
 @Title     This macro is used to read a register from a table.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		group: 		The name of the group containing the register to be
						read.

 @Input		reg: 		The name of the register to be read.

 @Input		ui32TabIndex:	The index of the table entry to be read.
  
 @Return	IMG_UINT32:	The value of the register.

******************************************************************************/
#define REGIO_READ_TABLE_REGISTER(ui32DevId, group, reg, ui32TabIndex)	\
	( IMG_ASSERT(ui32TabIndex < group##_##reg##_NO_ENTRIES),				\
	  group##_ReadRegister(ui32DevId, (group##_##reg##_OFFSET+(ui32TabIndex*group##_##reg##_STRIDE))) )

/*!
******************************************************************************

 @Macro	REGIO_READ_REGISTER_ABSOLUTE
 
 @Title     This macro is used to read a register.

 @Input		ui32Address:	The absolute address of the register to read.

 @Return	IMG_UINT32:	The value of the register.

******************************************************************************/
#define REGIO_READ_REGISTER_ABSOLUTE(ui32Address)	\
	MEMSPACE_ReadRegister((ui32Address))

#if ( defined WIN32 || defined __linux__ ) && !defined NO_REGIO_CHECK_FIELD_VALUE
	/* Only provide register field range checking for Windows and Linux builds */

	/* Simple range check that ensures that if bits outside the valid field		*/
	/* range are set, that the provided value is at least consistent with a		*/
	/* negative value (i.e.: all top bits are set to 1).						*/

	/* Cannot perform more comprehensive testing without knowing whether field	*/
	/* should be interpreted as signed or unsigned.								*/
	#define REGIO_CHECK_VALUE_FITS_WITHIN_FIELD(This_Group,This_Reg,This_Field,This_Value)						\
	{																											\
        IMG_UINT32 ui32Temp = (IMG_UINT32)((IMG_INT32)This_Value);                                              \
		if (ui32Temp > (This_Group##_##This_Reg##_##This_Field##_LSBMASK))						\
		{																										\
			IMG_ASSERT ((((IMG_UINT32)(IMG_INT32)This_Value) & (IMG_UINT32)~(This_Group##_##This_Reg##_##This_Field##_LSBMASK)) ==	\
							(IMG_UINT32)~(This_Group##_##This_Reg##_##This_Field##_LSBMASK));								\
		}																										\
	}
#else
	#define REGIO_CHECK_VALUE_FITS_WITHIN_FIELD(This_Group,This_Reg,This_Field,This_Value)
#endif

/*!
******************************************************************************

 @Macro	REGIO_WRITE_FIELD
 
 @Title     This macro is used to update the value of a field in a register.

 @Input		ui32RegValue: 	The register value - which gets updated.

 @Input		group: 		The name of the group containing the register into which 
						the field is to be written.

 @Input		reg: 		The name of the register into which the field is to 
						be written.

 @Input		field: 		The name of the field to be updated.

 @Input		ui32Value: 	The value to be written to the field - right aligned.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_FIELD(ui32RegValue, group, reg, field, ui32Value)											\
{																												\
	REGIO_CHECK_VALUE_FITS_WITHIN_FIELD(group,reg,field,ui32Value);												\
	(ui32RegValue) =																							\
	((ui32RegValue) & ~(group##_##reg##_##field##_MASK)) |														\
		(((IMG_UINT32) (ui32Value) << (group##_##reg##_##field##_SHIFT)) & (group##_##reg##_##field##_MASK));	\
}
	
/*!
******************************************************************************

 @Macro	REGIO_WRITE_FIELD_LITE
 
 @Title     This macro is used to update the value of a field in a register. 

 @note      It assumes that ui32RegValue is initially zero and thus no masking is required.

 @Input		ui32RegValue: 	The register value - which gets updated.

 @Input		group: 		The name of the group containing the register into which 
						the field is to be written.

 @Input		reg: 		The name of the register into which the field is to 
						be written.

 @Input		field: 		The name of the field to be updated.

 @Input		ui32Value: 	The value to be written to the field - right aligned.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_FIELD_LITE(ui32RegValue, group, reg, field, ui32Value)					\
{																							\
	REGIO_CHECK_VALUE_FITS_WITHIN_FIELD(group,reg,field,ui32Value);							\
	(ui32RegValue) |= ( (IMG_UINT32) (ui32Value) << (group##_##reg##_##field##_SHIFT) );	\
}

/*!
******************************************************************************

 @Macro	REGIO_ENCODE_FIELD
 
 @Description 

 This macro shifts a value to its correct position in a register. This is used
 for statically defining register values

 @Input		group: 		The name of the group containing the register into which 
						the field is to be written.

 @Input		reg: 		The name of the register into which the field is to 
						be written.

 @Input		field: 		The name of the field to be updated.

 @Input		ui32Value: 	The value to be written to the field - right aligned.
  
 @Return	None.

******************************************************************************/
#define REGIO_ENCODE_FIELD(group, reg, field, ui32Value)    \
                ( (IMG_UINT32) (ui32Value) << (group##_##reg##_##field##_SHIFT) )
/*!
******************************************************************************

 @Macro	REGIO_WRITE_REPEATED_FIELD
 
 @Title     This macro is used to update a repeated field in a packed memory 
 based structure.

 @Input		ui32RegValue: 	The register value - which gets updated.

 @Input		group: 		The name of the group containing the register into which 
						the field is to be written.

 @Input		reg: 		The name of the register into which the field is to 
						be written.

 @Input		field: 		The name of the field to be updated.

 @Input		ui32RepIndex: The repeat index of the field to be extracted.

 @Input		ui32Value: 	The value to be written to the field - right aligned.

 @Return	None.

******************************************************************************/
#define REGIO_WRITE_REPEATED_FIELD(ui32RegValue, group, reg, field, ui32RepIndex, ui32Value)																			\
{																																										\
	REGIO_CHECK_VALUE_FITS_WITHIN_FIELD(group,reg,field,ui32Value);																										\
																																										\
	( IMG_ASSERT(ui32RepIndex < group##_##reg##_##field##_NO_REPS),																										\
	  ui32RegValue =																																					\
	  (ui32RegValue & ~(group##_##reg##_##field##_MASK >> ((group##_##reg##_##field##_NO_REPS - (ui32RepIndex) - 1) * group##_##reg##_##field##_SIZE))) |				\
	  ((IMG_UINT32) (ui32Value) << (group##_##reg##_##field##_SHIFT - ((group##_##reg##_##field##_NO_REPS - (ui32RepIndex) - 1) * group##_##reg##_##field##_SIZE)) & 	\
	   (group##_##reg##_##field##_MASK >> ((group##_##reg##_##field##_NO_REPS - (ui32RepIndex) - 1) * group##_##reg##_##field##_SIZE))) );								\
}

/*!
******************************************************************************

 @Macro	REGIO_WRITE_REGISTER
 
 @Title     This macro is used to write a register.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		group: 		The name of the group containing the register to be
						written.

 @Input		reg: 		The name of the register to be written.

 @Input		ui32RegValue:	The value to be written to the register.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_REGISTER(ui32DevId, group, reg, ui32RegValue)			\
	group##_WriteRegister(ui32DevId, group##_##reg##_OFFSET, (IMG_UINT32) (ui32RegValue))

/*!
******************************************************************************

 @Macro	REGIO_WRITE_PIPE_REGISTER
 
 @Title     This macro is used to write to one of PVDEC's pipe register.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		ui8Pipe: 		The pipe number.

 @Input		group: 		The name of the group containing the register to be
						written.

 @Input		reg: 		The name of the register to be written.

 @Input		ui32RegValue:	The value to be written to the register.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_PIPE_REGISTER(ui32DevId, pipe, group, reg, ui32RegValue)			\
	group##_WritePipeRegister(ui32DevId, pipe, group##_##reg##_OFFSET, (IMG_UINT32) (ui32RegValue))

/*!
******************************************************************************

 @Macro	REGIO_WRITE_TABLE_REGISTER
 
 @Title     This macro is used to wrirte a register in a table.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		group: 		The name of the group containing the register to be
						written.

 @Input		reg: 		The name of the register to be written.

 @Input		ui32TabIndex:	The index of the table entry to be written.

 @Input		ui32RegValue:	The value to be written to the register.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_TABLE_REGISTER(ui32DevId, group, reg, ui32TabIndex, ui32RegValue)		\
	( IMG_ASSERT(ui32TabIndex < group##_##reg##_NO_ENTRIES),								\
	  group##_WriteRegister(ui32DevId, (group##_##reg##_OFFSET+(ui32TabIndex*group##_##reg##_STRIDE)), (IMG_UINT32) (ui32RegValue)) )


/*!
******************************************************************************

 @Macro	REGIO_WRITE_OFFSET_REGISTER
 
 @Title     This macro is used to write a register at an offset from a given register.

 @Input		ui32DevId: 		The device Id within the group.

 @Input		group: 		The name of the group containing the register to be
						written.

 @Input		reg: 		The name of the base register to be written.

 @Input		ui32Offset:	The offset (eg. 0,1,2,...) of the register to be written.

 @Input		ui32RegValue:	The value to be written to the register.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_OFFSET_REGISTER(ui32DevId, group, reg, ui32Offset, ui32RegValue)		\
	group##_WriteRegister(ui32DevId, (group##_##reg##_OFFSET+(ui32Offset*4)), (IMG_UINT32) (ui32RegValue))

/*!
******************************************************************************

 @Macro	REGIO_WRITE_REGISTER_ABSOLUTE
 
 @Title     This macro is used to write a register.

 @Input		ui32Address:	The absolute address of the register to write.

 @Input		ui32RegValue:	The value to be written to the register.
  
 @Return	None.

******************************************************************************/
#define REGIO_WRITE_REGISTER_ABSOLUTE(ui32Address, ui32Value)	\
	MEMSPACE_WriteRegister((ui32Address), (ui32Value))

/*!
******************************************************************************

 @Macro	REGIO_POLL32
 
 @Title     This macro is used to Poll a field in a register

 @Input		TalHandle	Tal register handle to use
 @Input		group 		The name of the group containing the register
 @Input		reg 		The name of the register
 @Input		field 		The name of the field to be polled.
 @Input		ui32value		The value to wait for
 @Input		nPoll		Number of Poll to be performed
 @Input		timeout		Timeout in clock cycles
 
 @see TALREG_Poll32
  
 @Return	IMG_RESULT

******************************************************************************/
#define REGIO_POLL32(TalHandle, group, reg, field, check, ui32value, nPoll, timeout) \
	TALREG_Poll32(hDGTalHandle, group ## _ ## reg ## _OFFSET, check, ui32value, group ## _ ## reg ## _ ## field ## _MASK, nPoll, timeout)

/*!
******************************************************************************

 @Macro	REGIO_POLL64
 
 @Title     This macro is used to Poll a field in a register

 @Input		TalHandle	Tal register handle to use
 @Input		group 		The name of the group containing the register
 @Input		reg 		The name of the register
 @Input		field 		The name of the field to be polled.
 @Input		ui64value		The value to wait for
 @Input		nPoll		Number of Poll to be performed
 @Input		timeout		Timeout in clock cycles
 
 @see TALREG_Poll64
  
 @Return	IMG_RESULT

******************************************************************************/
#define REGIO_POLL64(TalHandle, group, reg, field, check, ui64value, nPoll, timeout) \
	TALREG_Poll64(hDGTalHandle, group ## _ ## reg ## _OFFSET, check, ui64value, group ## _ ## reg ## _ ## field ## _MASK, nPoll, timeout)
	
/*!
******************************************************************************

 @Macro	REGIO_TABLE_OFF
 
 @Title Get the offset of an element from a table (so it can be used in a loop)
 
 @Input		group 			The name of the group containing the register
 @Input		reg 			The name of the register
 @Input		ui32TabIndex	Index of the element in the table
 
******************************************************************************/
#define REGIO_TABLE_OFF(group, reg, ui32TabIndex) \
	(group##_##reg##_OFFSET+(ui32TabIndex*group##_##reg##_STRIDE))
	
#ifdef DOXYGEN_CREATE_MODULES
/**
 * @}
 */
/*-------------------------------------------------------------------------
 * end of the IMGLIB_REGIO documentation module
 *------------------------------------------------------------------------*/
#endif

#if defined(__cplusplus)
}
#endif

#endif // #if !defined (__REG_IO2_H__)
