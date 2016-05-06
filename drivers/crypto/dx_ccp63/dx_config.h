/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/

/* \file dx_config.h
   Definitions for Discretix Linux Crypto Driver
 */

#ifndef __DX_CONFIG_H__
#define __DX_CONFIG_H__

//#define DISABLE_COHERENT_DMA_OPS
//#define FLUSH_CACHE_ALL
//#define COMPLETION_DELAY
//#define DX_DUMP_DESCS
//#define DX_DUMP_BYTES
//#define DX_DEBUG
//#define ENABLE_CYCLE_COUNT
//#define ENABLE_CC_CYCLE_COUNT
//#define DX_IRQ_DELAY 100000

#ifdef ENABLE_CC_CYCLE_COUNT
#define ENABLE_CYCLE_COUNT
#endif

/* Define the CryptoCell DMA cache coherency signals configuration */
#ifdef DISABLE_COHERENT_DMA_OPS
/* Software Controlled Cache Coherency (SCCC) */
#define DX_CACHE_PARAMS (0x000)
/* CC attached to NONE-ACP such as HPP/ACE/AMBA4.
 * The customer is responsible to enable/disable this feature
 * according to his platform type. */
#define DX_HAS_ACP 0
#else
#define DX_CACHE_PARAMS (0x277)
/* CC attached to ACP */
#define DX_HAS_ACP 1
#endif

#endif /*__DX_CONFIG_H__*/

