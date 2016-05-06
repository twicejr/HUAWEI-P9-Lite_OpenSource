/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  sci_apbitops.h
*
*   作    者 :  Y00171698
*
*   描    述 :  本文件命名为"sci_apbitops.h", 为ARM公司提供的sample code
*            做了部分改动,编程规范不做修改。
*
*   修改记录 :  
*************************************************************************/
#ifndef SCI_APBITOPS_H
#define SCI_APBITOPS_H

#ifdef  __cplusplus
extern "C" {    /* allow C++ to use these headers */
#endif  /* __cplusplus */
#include "product_config.h"
#include "osl_types.h"


/*
 * Description:
 * Generic constant for accessing all bits in a 32 bit word
 */
#define apBITS_ALL 0xFFFFFFFF

/*
 * ***************Standard data access set*******************
 * This set of macros accesses data using a width/shift parameter.
 * This assumes that constants bsXXX and bwXXX are defined, 
 *   where XXX is the value specified in the parameter.
 * + bwXXX is the number of bits to be accessed.
 * + bsXXX is the offset of the lowest bit.
 *
 */

/*
 * Description:
 * Build a mask for the specified bits
 *
 * Implementation:
 * __bws - a width/shift pair.
 * 
 * Returns  a mask with the bits to be addressed set and all others cleared
 * 
 */
#define apBIT_MASK(__bws) ((unsigned long)(((bw ## __bws)==32)?0xFFFFFFFF:((1U << (bw ## __bws)) - 1)) << (bs ## __bws))

/*
 * Description:
 * Access the specified bits from a word of data as an integer value
 *
 * Implementation:
 * __datum - the word of data to be accessed
 * __bws - a width/shift pair.
 * 
 * Returns  The relevant bits masked from the data word shifted to bit zero
 * 
 */
#define apBIT_GET(__datum, __bws) ((unsigned long)(((__datum) & ((unsigned long) apBIT_MASK(__bws))) >> (bs ## __bws)))

/*
 * Description:
 * Place the specified value into the specified bits of a word of data
 *
 * Implementation:
 * __datum - the word of data to be accessed
 * __bws - a width/shift pair.
 * __val - the data value to be shifted into the specified bits.
 * 
 */
#define apBIT_SET(__datum, __bws, __val) ((__datum) = ((unsigned long) (__datum) & (unsigned long)~(apBIT_MASK(__bws))) | \
                                        ((unsigned long) ((unsigned long)(__val) << (unsigned long)(bs ## __bws)) & (apBIT_MASK(__bws))))

/*
 * Description:
 * Build a mask for the specified bits
 *
 * Implementation:
 * __bws - a width/shift pair.
 * 
 * Returns  a mask with the bits to be addressed set and all others cleared
 * 
 */
#define SCI_BIT_MASK(__bws) ((u32)(((bw ## __bws)==32)?0xFFFFFFFF:((1U << (bw ## __bws)) - 1)) << (bs ## __bws))

/*
 * Description:
 * Access the specified bits from a word of data as an integer value
 *
 * Implementation:
 * __datum - the word of data to be accessed
 * __bws - a width/shift pair.
 * 
 * Returns  The relevant bits masked from the data word shifted to bit zero
 * 
 */
#define BIT_GET(__datum, __bws) ((u32)(((__datum) & ((u32) SCI_BIT_MASK(__bws))) >> (bs ## __bws)))

/*
 * Description:
 * Place the specified value into the specified bits of a word of data
 *
 * Implementation:
 * __datum - the word of data to be accessed
 * __bws - a width/shift pair.
 * __val - the data value to be shifted into the specified bits.
 * 
 */
#define BIT_SET(__datum, __bws, __val) ((__datum) = ((u32) (__datum) & (u32)~(SCI_BIT_MASK(__bws))) | \
                                        ((u32) ((u32)(__val) << (u32)(bs ## __bws)) & (SCI_BIT_MASK(__bws))))


#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif  /* __cplusplus */

#endif
