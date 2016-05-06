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
#include "bsp_memmap.h"
#include "hi_dsp.h"
#include "osl_bio.h"
#include "osl_types.h"

#ifdef BSP_CONFIG_PHONE_TYPE  /* austin */

/* #ifdef BSP_CONFIG_HI6250 */ /* Dallas */

#ifndef TM_STRESS_BASE_H
#define TM_STRESS_BASE_H

/*A9 TEST PARA*/
#define A9_DATA_CACHE_SIZE			(128*1024)
#define AXI_MEM_SIZE_FOR_A9			(1024)
#define DDR_MEM_SIZE_FOR_A9         (1024)
#define DDR_MEM_SIZE_FOR_AP         (1024 * 1024)


enum edma_move_type{
   EDMA_MOVE_DDR_TO_DDR,         /* 0 */
   EDMA_MOVE_DDR_TO_AXI_MEM,     /* 1 */
   EDMA_MOVE_AXI_MEM_TO_AXI_MEM, /* 2 */
   EDMA_MOVE_AXI_MEM_TO_DDR,     /* 3 */
   EDMA_MOVE_DDR_TO_BBE16_DTCM,  /* 4 */
   EDMA_MOVE_TYPE_BUTTOM
};

enum bbe16_move_type{
	BBE16_MOVE_DDR_TO_DDR,              /* 0 */
	BBE16_MOVE_DDR_TO_BBE16DTCM,        /* 1 */
	BBE16_MOVE_TYPE_BUTTOM
};

#define EDMA_TEST_LEN                (1024)

/* BEGIN: BBE16 DTCM CONFIG FOR STRESS TEST DTCM LAST 72k */
/* socp  bbe16_dtcm -> ddr 4k */
#define BBE16_LOCAL_MEM_SOCP_ADDR (HI_BBE16DMEM_BASE_ADDR + HI_BBE16DMEM_SIZE - 0x12000)
#define BBE16_LOCAL_MEM_SOCP_SIZE (0x10000)

/* bbe16  ddr -> bbe16_dtcm 1k */
#define BBE16_LOCAL_MEM_STRESS_DST_ADDR (BBE16_LOCAL_MEM_SOCP_ADDR + BBE16_LOCAL_MEM_SOCP_SIZE)
#define BBE16_LOCAL_MEM_STRESS_SIZE     (1024)

/* edma ddr -> bbe16_dtcm 1k*/
#define EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR       (BBE16_LOCAL_MEM_STRESS_DST_ADDR + BBE16_LOCAL_MEM_STRESS_SIZE)
#define EDMA_BUSSTRESS_DDR_TO_BBEDTCM_SIZE             (EDMA_TEST_LEN)

/* a9 memcpy bbe16_dtcm -> bbe16_dtcm  src 1k dst 1k total 2k*/
#define A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SRC_ADDR      (EDMA_BUSSTRESS_DDR_TO_BBE16DTCM_DST_ADDR + EDMA_BUSSTRESS_DDR_TO_BBEDTCM_SIZE)
#define A9_MEMCPY_BBE16DTCM_TO_BBE16DTCM_SIZE          (1024)
/* 后面还有4K */
/* END: BBE16 DTCM CONFIG FOR STRESS TEST */

#define HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE  (512)
#define HIFI_LOCAL_MEM_FOR_MCORE_DST_ADDR   (HI_HIFI2DMEM0_BASE_ADDR  + HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE)
#define HIFI_LOCAL_MEM_FOR_ACORE_SRC_ADDR   (HIFI_LOCAL_MEM_FOR_MCORE_DST_ADDR + HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE)

/*AXI MEM，即SRAM，K3V5上为96KB，将最后的32K给总线压力测试使用*/
/* EDMA搬移6K，从SRAM到SRAM，相比DDR搬移能大幅提高压力水平 */
#define AXI_MEM_FOR_MEMCPY_SIZE         (128)

#define MEM_FOR_EDMAC_BUSSTRESS         SRAM_BUSSTRESS_ADDR  /* 用于压力测试的AXI_MEM的起始地址 */
#define EDMA_MOVE_SRAM2SRAM_SRC_ADDR    SRAM_BUSSTRESS_ADDR
#define EDMA_MOVE_SRAM2SRAM_SIZE        (6 * 1024)
#define EDMA_MOVE_SRAM2SRAM_DST_ADDR    (EDMA_MOVE_SRAM2SRAM_SRC_ADDR) /* SRAM分出6K给EDMA搬移使用，源地址与目的地址一样 */

/* BBE16 数据搬移 1k*/
#define MEM_FOR_BBE16_BUSSTRESS         (EDMA_MOVE_SRAM2SRAM_DST_ADDR + EDMA_MOVE_SRAM2SRAM_SIZE)/*used in ccore no need to convert into phy addr*/
#define AXI_MEM_64_SIZE_FOR_BBE16       (1024)

/* HIFI 数据搬移 512字节*/
#define AXI_MEM_64_SRC_FOR_HIFI         (MEM_FOR_BBE16_BUSSTRESS + AXI_MEM_64_SIZE_FOR_BBE16)
#define AXI_MEM_64_DST_FOR_HIFI         (AXI_MEM_64_SRC_FOR_HIFI + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_FOR_HIFI_SRC_ADDR       (AXI_MEM_64_DST_FOR_HIFI + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_FOR_HIFI_DST_ADDR       (AXI_MEM_FOR_HIFI_SRC_ADDR + AXI_MEM_FOR_MEMCPY_SIZE)

/* a9 数据搬移axi_mem->axi_mem  共使用了20k */
#define AXI_MEM_FOR_A9_CCORE_SRC_ADDR   (AXI_MEM_FOR_HIFI_DST_ADDR + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_FOR_A9_CCORE_SIZE       (10 * 1024)  
#define AXI_MEM_FOR_A9_CCORE_DST_ADDR   (AXI_MEM_FOR_A9_CCORE_SRC_ADDR + AXI_MEM_FOR_A9_CCORE_SIZE)

#define SRAM_BUSSTRESS_ADDR                 (SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER)

/* socp 4k */
#define AXI_MEM_FOR_SOCP_ADDR           (AXI_MEM_FOR_A9_CCORE_DST_ADDR + AXI_MEM_FOR_A9_CCORE_SIZE)
#define AXI_MEM_FOR_SOCP_SIZE           (0x1000)

/*test ddr*/
#define BBE16_DDR_BASEADDR               SHM_MEM_BUSSSTRESS_ADDR
#define BBE16_DDR_SIZE               		(1024)
#define HIFI_DDR_BASEADDR               (BBE16_DDR_BASEADDR +BBE16_DDR_SIZE)
#define HIFI_DDR_SIZE               		(64*1024)

#define PRINT_ERROR() do{\
	printf(">>>line %d :%s failed \n",__LINE__,(int)__FUNCTION__);\
	return ERROR;\
	}while(0)

#define LOGMSG_ERROR() do{\
	logMsg(">>>line %d FUNC %s fail\n",__LINE__,(int)__FUNCTION__,0,0,0,0);\
	}while(0)

typedef enum tagUseSpaceType
{
	DDR = 0,
	BBE16 = 1,
	AXIMEM = 2,
	DDR_BBE16_AXIMEM = 3,
	DSP = 4,
	HIFI = 5
}Use_Space_Type;

typedef enum tagTestModule
{
	GMAC = 0,
	ACC = 1,
	CIPHER = 2,
	KDF =3,
	DMA_DSP =4,
	EDMAC = 5,
	IPF_UL = 6,
	IPF_DL = 7,
	LCD = 8
}TestModule;
typedef enum tagTestSwitch
{
	TEST_STOP = 0,
	TEST_RUN =1
}TestSwitch;

typedef struct tagPsSendPacket
{
    int s32SendDataAddr;
    int s32SendDataLen;
    unsigned int pNext;
}PsSendPacket;


int memcpyTestProcess(void* pSrcAddr, void* pDstAddr, int iSize);

typedef struct bus_stress_test_tag
{
	unsigned int uiSrcAddr;
	unsigned int uiDstAddr;
	unsigned int uiSizeBytes;
	unsigned int uiBusWidth;
	unsigned int uiErrCount;
}BUS_STRESS_TEST_STRU;

void *alloc(signed sz);
int get_test_switch_stat(int module_id);
int set_test_switch_stat(int module_id, int run_or_stop);

#endif /*TM_STRESS_BASE_H*/


#else
#include "bsp_memmap.h"
#include "hi_dsp.h"
#include "osl_bio.h"
#include "osl_types.h"
#include "bsp_shared_ddr.h"
#include "bsp_sram.h"

#ifndef TM_STRESS_BASE_H
#define TM_STRESS_BASE_H

/*A9 TEST PARA*/
#define A9_DATA_CACHE_SIZE					(128*1024)
#define AXI_MEM_SIZE_FOR_A9				    (1024)
#define AXI_MEM_SIZE_FOR_M3				    (1024)
#define DDR_MEM_SIZE_FOR_A9                 (1024)

#define BBE16_LOCAL_MEM_SIZE_FOR_A9         (1024)
#define BBE16_LOCAL_MEM_START_ADDR_FOR_A9_A	(BBE_TCM_ADDR + 2*BBE16_LOCAL_MEM_SIZE_FOR_A9)

#define HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE  (512)
#define HIFI_LOCAL_MEM_FOR_MCORE_DST_ADDR   (HI_HIFI2DMEM0_BASE_ADDR  + HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE)
#define HIFI_LOCAL_MEM_FOR_ACORE_SRC_ADDR   (HIFI_LOCAL_MEM_FOR_MCORE_DST_ADDR + HIFI_LOCAL_MEM_FOR_ARM_MEMCPY_SIZE)

/*AXI MEM 64KB*/
#define AXI_MEM_FOR_MEMCPY_SIZE             (128)
#define SRAM_BUSSTRESS_ADDR                 (SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER)
#define MEM_FOR_EDMAC_BUSSTRESS             (SRAM_BUSSTRESS_ADDR)
#define AXI_MEM_64_SIZE_FOR_EDMAC           (6*1024)

#define MEM_FOR_BBE16_BUSSTRESS             (SRAM_BUSSTRESS_ADDR +AXI_MEM_64_SIZE_FOR_EDMAC)/*used in ccore no need to convert into phy addr*/
#define AXI_MEM_64_SIZE_FOR_BBE16           (1024)

#define AXI_MEM_64_SRC_FOR_HIFI             (MEM_FOR_BBE16_BUSSTRESS +AXI_MEM_64_SIZE_FOR_BBE16)
#define AXI_MEM_64_DST_FOR_HIFI             (AXI_MEM_64_SRC_FOR_HIFI + AXI_MEM_FOR_MEMCPY_SIZE)

#define AXI_MEM_FOR_HIFI_SRC_ADDR           (AXI_MEM_64_DST_FOR_HIFI + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_FOR_HIFI_DST_ADDR           (AXI_MEM_FOR_HIFI_SRC_ADDR + AXI_MEM_FOR_MEMCPY_SIZE)

#define AXI_MEM_64_SRC_FOR_A9_CCORE         (AXI_MEM_FOR_HIFI_DST_ADDR + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_64_DST_FOR_A9_CCORE         (AXI_MEM_64_SRC_FOR_A9_CCORE + AXI_MEM_FOR_MEMCPY_SIZE)

#define AXI_MEM_64_VSRC_FOR_A9_ACORE        (AXI_MEM_64_DST_FOR_A9_CCORE + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_64_VDST_FOR_A9_ACORE        (AXI_MEM_64_VSRC_FOR_A9_ACORE + AXI_MEM_FOR_MEMCPY_SIZE)

#define AXI_MEM_64_SRC_FOR_MCORE            (AXI_MEM_64_VDST_FOR_A9_ACORE + AXI_MEM_FOR_MEMCPY_SIZE)
#define AXI_MEM_64_DST_FOR_MCORE            (AXI_MEM_64_SRC_FOR_MCORE + AXI_MEM_FOR_MEMCPY_SIZE)
#define SHM_MEM_BUSSSTRESS_ADDR             (SHM_BASE_ADDR + SHM_OFFSET_BUSSTRESS_TEST)
#define SHM_MEM_BUSSSTRESS_SIZE             (70*1024)
#define BBE16_DDR_BASEADDR                  (SHM_MEM_BUSSSTRESS_ADDR)
#define BBE16_DDR_SIZE                      (1024)
#define HIFI_DDR_BASEADDR                   (BBE16_DDR_BASEADDR + BBE16_DDR_SIZE)
#define HIFI_DDR_SIZE                       (64*1024)
#define M3_DDR_BASEADDR                     (HIFI_DDR_BASEADDR + HIFI_DDR_SIZE)
#define M3_DATA_CACHE_SIZE				    (2*1024)

#define PRINT_ERROR() do{\
	printf(">>>line %d :%s failed \n",__LINE__,(int)__FUNCTION__);\
	return ERROR;\
	}while(0)

#define LOGMSG_ERROR() do{\
	logMsg(">>>line %d FUNC %s fail\n",__LINE__,(int)__FUNCTION__,0,0,0,0);\
	}while(0)

typedef enum tagUseSpaceType
{
	DDR = 0,
	BBE16 = 1,
	AXIMEM = 2,
	DDR_BBE16_AXIMEM = 3,
	DSP = 4,
	HIFI = 5
}Use_Space_Type;

typedef enum tagTestModule
{
	GMAC = 0,
	ACC = 1,
	CIPHER = 2,
	KDF =3,
	DMA_DSP =4,
	EDMAC = 5,
	IPF_UL = 6,
	IPF_DL = 7,
	LCD = 8
}TestModule;
typedef enum tagTestSwitch
{
	TEST_STOP = 0,
	TEST_RUN =1
}TestSwitch;

typedef struct tagPsSendPacket
{
    int s32SendDataAddr;
    int s32SendDataLen;
    unsigned int pNext;	
}PsSendPacket;


int memcpyTestProcess(unsigned int uiSrc,unsigned int uiDst,int iSize);

typedef struct bus_stress_test_tag
{
	unsigned int uiSrcAddr;
	unsigned int uiDstAddr;
	unsigned int uiSizeBytes;
	unsigned int uiBusWidth;
	unsigned int uiErrCount;
}BUS_STRESS_TEST_STRU;

void *alloc(signed sz);
int get_test_switch_stat(int module_id);
int set_test_switch_stat(int module_id, int run_or_stop);

#endif /*TM_STRESS_BASE_H*/

#endif


