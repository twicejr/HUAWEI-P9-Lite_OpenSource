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

#ifndef __DRV_COMM_H__
#define __DRV_COMM_H__

#ifndef __OS_RTOSCK__
typedef void                VOID;
#endif

/*************************GLOBAL BEGIN*****************************/
/* 基本数据类型定义 */
#ifndef _WIN32_COMPILE
typedef signed long long    BSP_S64;
#else
typedef double              BSP_S64;
#endif
typedef signed int          BSP_S32;
typedef signed short        BSP_S16;
typedef signed char         BSP_S8;
typedef char                BSP_CHAR;
typedef char                BSP_CHAR_TL;

#ifndef _WIN32_COMPILE
typedef unsigned long long  BSP_U64;
#else
typedef double              BSP_U64;
#endif
typedef unsigned int        BSP_U32;
typedef unsigned short      BSP_U16;
typedef unsigned char       BSP_U8;

typedef int                 BSP_BOOL;
typedef void                BSP_VOID;
typedef int                 BSP_STATUS;

#ifndef _WIN32_COMPILE
typedef signed long long*   BSP_PS64;
#else
typedef double*             BSP_PS64;
#endif
typedef signed int*         BSP_PS32;
typedef signed short*       BSP_PS16;
typedef signed char*        BSP_PS8;

#ifndef _WIN32_COMPILE
typedef unsigned long long* BSP_PU64;
#else
typedef double*             BSP_PU64;
#endif
typedef unsigned int*       BSP_PU32;
typedef unsigned short*     BSP_PU16;
typedef unsigned char*      BSP_PU8;

#ifndef UINT8
typedef unsigned char       UINT8;
#endif
#ifndef UINT16
typedef unsigned short      UINT16;
#endif
#ifndef UINT32
typedef unsigned int        UINT32;
#endif
typedef int*                BSP_PBOOL;
typedef void*               BSP_PVOID;
typedef int*                BSP_PSTATUS;
typedef BSP_S32             STATUS;
typedef BSP_S32             UDI_HANDLE;

#ifndef BSP_CONST
#define BSP_CONST           const
#endif

#ifndef OK
#define OK                  (0)
#endif

#ifndef ERROR
#define ERROR               (-1)
#endif

#ifndef TRUE
#define TRUE                (1)
#endif

#ifndef FALSE
#define FALSE               (0)
#endif

#ifndef BSP_OK
#define BSP_OK              (0)
#endif

#ifndef BSP_ERROR
#define BSP_ERROR           (-1)
#endif

#ifndef BSP_TRUE
#define BSP_TRUE            (1)
#endif

#ifndef BSP_FALSE
#define BSP_FALSE           (0)
#endif

#ifndef BSP_NULL
#define BSP_NULL            (void*)0
#endif

typedef int (*PWRCTRLFUNCPTRVOID)(void);
typedef unsigned int (*PWRCTRLFUNCPTR)(unsigned int arg);     /* ptr to function returning int */

#ifdef __OS_VXWORKS__
#ifndef INLINE
#define INLINE              __inline__
#endif
#ifndef inline
#define inline              __inline__
#endif
#elif defined(__OS_RTOSCK__)

#elif defined(__KERNEL__)|| defined(__CMSIS_RTOS)
#ifndef INLINE
#define INLINE              inline
#endif
#endif
#define LOCAL                   static

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else

typedef BSP_VOID (*VOIDFUNCPTR)(BSP_U32);
#define SEM_FULL            (1)
#define SEM_EMPTY           (0)
#define IVEC_TO_INUM(intVec)    ((int)(intVec))

#endif


/* 错误码宏定义 */
#define BSP_ERR_MODULE_OFFSET (0x1000)    /* 防止和系统的错误码重叠 */
#define BSP_DEF_ERR( mod, errid) \
    ((((BSP_U32) mod + BSP_ERR_MODULE_OFFSET) << 16) | (errid))

#define BSP_REG(base, reg) (*(volatile BSP_U32 *)((unsigned long)base + (reg)))

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM) || defined(__VXWORKS__)
#define BSP_REG_READ(base, reg, result) \
    ((result) = BSP_REG(base, reg))

#define BSP_REG_WRITE(base, reg, data) \
    (BSP_REG(base, reg) = (data))

#else
#define BSP_REG_READ(base, reg, resule) \
    (resule = readl(base + reg))

#define BSP_REG_WRITE(base, reg, data) \
    (writel(data, (base + reg)))
#endif

#define BSP_REG_SETBITS(base, reg, pos, bits, val) (BSP_REG(base, reg) = (BSP_REG(base, reg) & (~((((u32)1 << (bits)) - 1) << (pos)))) \
                                                                         | ((u32)((val) & (((u32)1 << (bits)) - 1)) << (pos)))
#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) & (((u32)1 << (bits)) - 1))



/*****************************************************************************
  1 GU侧驱动对外接口，GUPorting项目添加.
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define DRV_OK                          (0)
#define DRV_ERROR                       (-1)
#define DRV_INTERFACE_RSLT_OK           (0)

/* 基本数据类型定义 */

typedef int  (*pFUNCPTR)(void);

typedef unsigned long (*pFUNCPTR2)( unsigned long ulPara1, unsigned long ulPara2);

typedef unsigned int tagUDI_DEVICE_ID_UINT32;

/* 上行线路收包函数指针 */
typedef BSP_VOID (*UpLinkRxFunc)(BSP_U8 *buf, BSP_U32 len);

/* 包封装释放函数指针 */
typedef BSP_VOID (*FreePktEncap)(BSP_VOID *PktEncap);

/* GMAC调用者枚举 */
typedef enum tagGMAC_OWNER_E
{
    GMAC_OWNER_VXWORKS = 0, /* Vxworks网络协议栈 */
    GMAC_OWNER_PS,          /* LTE网络协议栈 */
    GMAC_OWNER_MSP,         /* MSP */
    GMAC_OWNER_MAX          /* 边界值 */
}GMAC_OWNER_E;

typedef enum tagWDT_TIMEOUT_E
{
    WDT_TIMEOUT_1   = 0,        /*0xFFFF000/WDT_CLK_FREQ,  about 3657ms*/      /*WDT_CLK_FREQ = ARM_FREQ/6 = 70M*/
    WDT_TIMEOUT_2,              /*0x1FFFE000/WDT_CLK_FREQ, about 7314ms*/
    WDT_TIMEOUT_3,              /*0x3FFFC000/WDT_CLK_FREQ, about 14628ms*/
    WDT_TIMEOUT_4,              /*0x7FFF8000/WDT_CLK_FREQ, about 29257ms*/
    WDT_TIMEOUT_BUTT
}WDT_TIMEOUT_E;

/*************************GLOBAL END****************************/

#endif

