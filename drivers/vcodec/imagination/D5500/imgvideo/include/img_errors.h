/*!
 *****************************************************************************
 *
 * @File       img_errors.h
 * @Title      Error codes used accross projects
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

#ifndef __IMG_ERRORS__
#define __IMG_ERRORS__

#if defined (__cplusplus)
extern "C" {
#endif

#define	IMG_SUCCESS								(0)		/**< @brief Success	*/
#define IMG_ERROR_TIMEOUT						(1)		/**< @brief Timeout	*/
#define IMG_ERROR_MALLOC_FAILED					(2)		/**< @brief memory allocation failed	*/
#define IMG_ERROR_FATAL							(3)		/**< @brief Unspecified fatal error	*/
#define IMG_ERROR_OUT_OF_MEMORY					(4)		/**< @brief Memory allocation failed	*/
#define IMG_ERROR_DEVICE_NOT_FOUND				(5)		/**< @brief Device is not found	*/
#define IMG_ERROR_DEVICE_UNAVAILABLE			(6)		/**< @brief Device is not available/in use	*/
#define IMG_ERROR_GENERIC_FAILURE				(7)		/**< @brief Generic/unspecified failure	*/
#define IMG_ERROR_INTERRUPTED					(8)		/**< @brief Operation was interrupted - retry	*/
#define IMG_ERROR_INVALID_ID					(9)		/**< @brief Invalid id	*/
#define IMG_ERROR_SIGNATURE_INCORRECT			(10)	/**< @brief A signature value was found to be incorrect	*/
#define IMG_ERROR_INVALID_PARAMETERS			(11)	/**< @brief The provided parameters were inconsistent/incorrect	*/
#define IMG_ERROR_STORAGE_TYPE_EMPTY			(12)	/**< @brief A list/pool has run dry	*/
#define IMG_ERROR_STORAGE_TYPE_FULL				(13)	/**< @brief A list is full	*/
#define IMG_ERROR_ALREADY_COMPLETE				(14)	/**< @brief Something has already occurred which the code thinks has not	*/
#define IMG_ERROR_UNEXPECTED_STATE				(15)	/**< @brief A state machine is in an unexpected/illegal state	*/
#define IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE		(16)	/**< @brief A required resource could not be created/locked	*/
#define IMG_ERROR_NOT_INITIALISED				(17)	/**< @brief An attempt to access a structure/resource was made before it was initialised	*/
#define	IMG_ERROR_ALREADY_INITIALISED			(18)	/**< @brief An attempt to initialise a structure/resource was made when it has already been initialised	*/
#define	IMG_ERROR_VALUE_OUT_OF_RANGE			(19)	/**< @brief A provided value exceeded stated bounds				*/
#define IMG_ERROR_CANCELLED						(20)	/**< @brief The operation has been cancelled */
#define	IMG_ERROR_MINIMUM_LIMIT_NOT_MET			(21)	/**< @brief A specified minimum has not been met */
#define IMG_ERROR_NOT_SUPPORTED					(22)	/**< @brief The requested feature or mode is not supported */
#define IMG_ERROR_IDLE							(23)	/**< @brief A device or process was idle */
#define IMG_ERROR_BUSY							(24)	/**< @brief A device or process was busy */
#define IMG_ERROR_DISABLED						(25)	/**< @brief The device or resource has been disabled */
#define IMG_ERROR_OPERATION_PROHIBITED			(26)	/**< @brief The requested operation is not permitted at this time */
#define IMG_ERROR_MMU_PAGE_DIRECTORY_FAULT		(27)	/**< @brief The entry read from the MMU page directory is invalid */
#define IMG_ERROR_MMU_PAGE_TABLE_FAULT			(28)	/**< @brief The entry read from an MMU page table is invalid */
#define IMG_ERROR_MMU_PAGE_CATALOGUE_FAULT      (29)	/**< @brief The entry read from an MMU page catalogue is invalid */
#define IMG_ERROR_MEMORY_IN_USE					(30)	/**< @brief Memory can not be freed as it is still been used */
#define IMG_ERROR_TEST_MISMATCH					(31)	/**< @brief A mismatch has unexpectedly occured in data */

#if defined (__cplusplus)
}
#endif

#endif /* __IMG_ERRORS__  */
