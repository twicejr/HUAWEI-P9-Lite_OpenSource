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

/* Dummy pal_log_plat for test driver in kernel */

#ifndef _DX_PAL_LOG_PLAT_H_
#define _DX_PAL_LOG_PLAT_H_

#if defined(DEBUG)

#define __DX_PAL_LOG_PLAT(level, format, ...) printk(level "cc63_test::" format , ##__VA_ARGS__)

#else /* Disable all prints */

#define __DX_PAL_LOG_PLAT(...)  do {} while (0)

#endif

#endif /*_DX_PAL_LOG_PLAT_H_*/

