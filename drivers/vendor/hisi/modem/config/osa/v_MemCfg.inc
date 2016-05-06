/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: ../TARGET/config/v_MemCfg.inc                                   */
/*                                                                           */
/* Author:                                                                   */
/*                                                                           */
/* Version:  1.0                                                             */
/*                                                                           */
/* Date:                                                                     */
/*                                                                           */
/* Description: create this file                                             */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#ifndef _V_MEMCFG_INC
#define _V_MEMCFG_INC


#if (OSA_CPU_CCPU == VOS_OSA_CPU)

/* modify this to config memmory */
/* defination of message buffer */
VOS_MEM_BLOCK_INFO MsgBlockInfo[VOS_MEM_CTRL_BLOCK_NUMBER] =
{
    { 32,     40  },
    { 96,     500 },
    { 224,    240 },
    { 480,    300 },
    { 992,    20  },
    { 2016,   70  },
    { 4160,   10  },
    { 8160,   2   },
    { 16352,  2   },
    { 24992,  2   },
    { 80000,  1   },
    { 100000, 1   },
    { 64,     VOS_TIMER_MESSAGE_NUM },/* only for Timer */
};


/* defination of memory buffer */
#if (FEATURE_ON == FEATURE_VOS_REDUCE_MEM_CFG)
VOS_MEM_BLOCK_INFO MemBlockInfo[VOS_SIMPLE_MEM_CTRL_BLOCK_NUMBER] =
{
    { 32,     1000},
    { 92,     4000},
    { 116,    500 },
    { 256,    300 },
    { 532,    200 },
    { 1600,   200 },
    { 2080,   100 },
    { 4480,   30  },
    { 8212,   12  },
    { 16404,  12  },
    { 35848,  16  },
    { 64000,  8   },
};
#else
VOS_MEM_BLOCK_INFO MemBlockInfo[VOS_SIMPLE_MEM_CTRL_BLOCK_NUMBER] =
{
    { 32,     1000},
    { 92,     4000},
    { 116,    500 },
    { 256,    300 },
    { 532,    200 },
    { 1600,   200 },
    { 2080,   100 },
    { 4480,   30  },
    { 8212,   12  },
    { 16404,  12  },
    { 35848,  16  },
    { 64000,  4   },
    { 65536,  7   },
    { 80000,  3   },
};
#endif

#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)

VOS_MEM_BLOCK_INFO MsgBlockInfo[VOS_MEM_CTRL_BLOCK_NUMBER] =
{
    { 32,     40  },
    { 100,    40  },
    { 224,    100 },
    { 480,    40  },
    { 800,    40  },
    { 2416,   40  },
    { 4160,   40  },
    { 8160,   2   },
    { 16352,  2   },
    { 24992,  2   },
    { 80000,  1   },
    { 64,     VOS_TIMER_MESSAGE_NUM },/* only for Timer */
};


/* defination of memory buffer */
VOS_MEM_BLOCK_INFO MemBlockInfo[VOS_SIMPLE_MEM_CTRL_BLOCK_NUMBER] =
{
    { 40,     40  },
    { 92,     40  },
    { 256,    100 },
    { 532,    100 },
    { 1600,   100 },
    { 2080,   100 },
    { 4480,   16  },
    { 16404,  6   },
    { 35848,  4   },
    { 65536,  2   },
};
#endif


#endif /* _V_MEMCFG_INC */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


