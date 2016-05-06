/*!
 *****************************************************************************
 *
 * @File       vdec.h
 * @Description    This file contains the VDEC System Defintions.
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

#ifndef __VDEC_H__
#define __VDEC_H__

#ifdef __cplusplus
extern "C" {
#endif


#define VDEC_BE_FE_PDUMP_SEM  0
#define VDEC_BE_FE_SYNC_ID    1


#define NULL_DEV_NAME        "NULL"        //!< The null device name

//#define FW_PRINT
#ifdef SECURE_MEDIA_SUPPORT
    #define SECURE_MEMORY_OFFSET            0x08000000     //In bytes
#else
    #define SECURE_MEMORY_OFFSET            0x10000000    //In bytes
#endif
/*!
******************************************************************************
 MSVDX configuration
******************************************************************************/
#define MSVDX_ENDIAN    (0)             /*!< 0 : Little endian, 1 : Big endian */
/*!
******************************************************************************
 Common VLR configuration
******************************************************************************/
/*! VLR size */
#define VLR_SIZE                        0x1000


/*!
******************************************************************************
 MSVDX VLR configuration
******************************************************************************/
/*! FE area base address within the VLR */
#define VLR_FE_AREA_BASE_ADDR         0x000
#define LINE_STORE_FE_AREA_BASE_ADDR  0x000

/*! FE area is subdivided into: */

/*! VEC Local RAM Base Address for:
 * - H.264 Slice Group Map data
 * - VC-1 Bitplane data */
#define VLR_FE_VEC_SGM_BITPLANE_BASE_ADDR            (VLR_FE_AREA_BASE_ADDR)
#define VLR_FE_VEC_SGM_BITPLANE_SIZE                 128
/*! MPEG4 Front-End VLR Base Address for DP Parser */
#define VLR_FE_VEC_MPEG4_FE_DATAPARTITION_BASE_ADDR  (VLR_FE_AREA_BASE_ADDR)
#define VLR_FE_VEC_MPEG4_FE_DATAPARTITION_SIZE       128
/*! MPEG4 Front-End VLR Base Address for Non-DP Parser */
/*! NOTE: This are is not used for MSVDX versions > 5.x.x */
#define VLR_FE_VEC_MPEG4_FE_PARSER_BASE_ADDR         (VLR_FE_AREA_BASE_ADDR + VLR_FE_VEC_MPEG4_FE_DATAPARTITION_SIZE)
#define VLR_FE_VEC_MPEG4_FE_PARSER_SIZE              1088
/*! MPEG4 Front-End Cabac Line Store Base Address for Non-DP Parser */
/*! NOTE: This are is used for MSVDX versions > 5.x.x */
#define LINE_STORE_FE_VEC_MPEG4_FE_PARSER_BASE_ADDR	 (LINE_STORE_FE_AREA_BASE_ADDR)
#define LINE_STORE_FE_VEC_MPEG4_FE_PARSER_SIZE		 1088

/*! FE area size within the VLR */
#define VLR_FE_AREA_SIZE  (VLR_FE_VEC_MPEG4_FE_DATAPARTITION_SIZE + VLR_FE_VEC_MPEG4_FE_PARSER_SIZE)


/*! BE data base address within the VLR */
#define VLR_BE_AREA_BASE_ADDR  (VLR_FE_AREA_BASE_ADDR + VLR_FE_AREA_SIZE)

/*! BE area is subdivided into: */

/* >>> core dependent BE data for MSVDX cores <5.x.x: */
/*! VEC Local RAM Circulate Buffer Base Address */
#define VLR_BE_VEC_CIRC_BUFF_PRE5_BASE_ADDR               (VLR_BE_AREA_BASE_ADDR)
/*! VEC Local RAM Circulate Buffer size */
#define VLR_BE_VEC_CIRC_BUFF_PRE5_SIZE                    1024
/*! MPEG4 Back-End VLR Area Base Address for DP 0/1 Load */
#define VLR_BE_VEC_MPEG4_BE_DATAPARTITION_PRE5_BASE_ADDR  (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_PRE5_SIZE)
/*! MPEG4 Back-End VLR Area size */
#define VLR_BE_VEC_MPEG4_BE_DATAPARTITION_PRE5_SIZE       512
/*! VEC Local RAM Command Store Base Address for H.264 or AVS */
#define VLR_BE_VEC_COMMANDS_STORE_PRE5_BASE_ADDR          (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_PRE5_SIZE)
/*! VEC Local RAM Command Store size */
#define VLR_BE_VEC_COMMANDS_STORE_PRE5_SIZE               512
/*! VP6 Back-End Data-Partition store/fetch buffer VLR Base Address */
#define VLR_BE_VEC_VP6_BE_DP_BUFFER_PRE5_BASE_ADDR        (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_PRE5_SIZE)
/*! VP6 Back-End Data-Partition store/fetch buffer size for MSVDX versions >= 5.x.x */
#define VLR_BE_VEC_VP6_BE_DP_BUFFER_PRE5_SIZE             512
/*! VP8 Back-End VLR Area Base Address  */
#define VLR_BE_VEC_VP8_BE_PRE5_BASE_ADDR                  (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_PRE5_SIZE)
/*! VP8 Back-End VLR Area size */
#define VLR_BE_VEC_VP8_BE_PRE5_SIZE                       512
/*! Core dependent BE data size within the VLR */
#define VLR_BE_AREA_CORE_DEPENDENT_PRE5_SIZE  (VLR_BE_VEC_CIRC_BUFF_PRE5_SIZE + VLR_BE_VEC_COMMANDS_STORE_PRE5_SIZE)


/* >>> core dependent BE data for MSVDX cores >=5.x.x: */
/*! VEC Local RAM Circulate Buffer Base Address */
#define VLR_BE_VEC_CIRC_BUFF_BASE_ADDR                    (VLR_BE_AREA_BASE_ADDR)
/*! VEC Local RAM Circulate Buffer size */
#define VLR_BE_VEC_CIRC_BUFF_SIZE                         1472
/*! MPEG4 Back-End VLR Area Base Address for DP 0/1 Load */
#define VLR_BE_VEC_MPEG4_BE_DATAPARTITION_BASE_ADDR       (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_SIZE)
/*! MPEG4 Back-End VLR Area size */
#define VLR_BE_VEC_MPEG4_BE_DATAPARTITION_SIZE            128
/*! VEC Local RAM Command Store Base Address for H.264 or AVS */
#define VLR_BE_VEC_COMMANDS_STORE_BASE_ADDR               (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_SIZE)
/*! VEC Local RAM Command Store size */
#define VLR_BE_VEC_COMMANDS_STORE_SIZE                    128
/*! VP6 Back-End Data-Partition store/fetch buffer VLR Base Address */
#define VLR_BE_VEC_VP6_BE_DP_BUFFER_BASE_ADDR             (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_SIZE)
/*! VP6 Back-End Data-Partition store/fetch buffer size */
#define VLR_BE_VEC_VP6_BE_DP_BUFFER_SIZE                  128
/*! VP8 Back-End VLR Area Base Address  */
#define VLR_BE_VEC_VP8_BE_BASE_ADDR                       (VLR_BE_AREA_BASE_ADDR + VLR_BE_VEC_CIRC_BUFF_SIZE)
/*! VP8 Back-End VLR Area size */
#define VLR_BE_VEC_VP8_BE_SIZE                            128
/*! Core dependent BE data size within the VLR */
#define VLR_BE_AREA_CORE_DEPENDENT_SIZE  (VLR_BE_VEC_CIRC_BUFF_SIZE + VLR_BE_VEC_COMMANDS_STORE_SIZE)

/* Calculate the actual core dependent BE data size within the VLR - get the maximum size for all core versions */
#if ((VLR_BE_AREA_CORE_DEPENDENT_SIZE) > (VLR_BE_AREA_CORE_DEPENDENT_PRE5_SIZE))
    #define VLR_BE_AREA_CORE_DEPENDENT_ACTUAL_SIZE  (VLR_BE_AREA_CORE_DEPENDENT_SIZE)
#else
    #define VLR_BE_AREA_CORE_DEPENDENT_ACTUAL_SIZE  (VLR_BE_AREA_CORE_DEPENDENT_PRE5_SIZE)
#endif

/* >>> core independent BE data for MSVDX cores >=5.x.x: */
/*! Macroblock Parameter Benign Value */
#define VLR_BE_MB_PARAM_BENIGN_VALUE_BASE_ADDR            (VLR_BE_AREA_BASE_ADDR + VLR_BE_AREA_CORE_DEPENDENT_ACTUAL_SIZE)
#define VLR_BE_MB_PARAM_BENIGN_VALUE_SIZE                 4
/*! Core independent BE data size within the VLR */
#define VLR_BE_AREA_CORE_INDEPENDENT_SIZE  (VLR_BE_MB_PARAM_BENIGN_VALUE_SIZE)

/*! BE data size within the VLR */
#define VLR_BE_AREA_SIZE  (VLR_BE_AREA_CORE_DEPENDENT_ACTUAL_SIZE + VLR_BE_AREA_CORE_INDEPENDENT_SIZE)


/*!
******************************************************************************
 VDEC Firmware VLR configuration
******************************************************************************/
/*! Host <-> MTX communications area base address within the VLR */
#define VLR_COMMS_AREA_BASE_ADDR  (VLR_BE_AREA_BASE_ADDR + VLR_BE_AREA_SIZE)

/*! Host <-> MTX communications area is subdivided into: */

/*! Decode communications area base address within the VLR */
#define VLR_DECODE_COMMS_AREA_BASE_ADDR            (VLR_COMMS_AREA_BASE_ADDR)
#define VLR_DECODE_COMMS_AREA_SIZE                 468
/*! Control communications area base address within the VLR */
#define VLR_CONTROL_COMMS_AREA_BASE_ADDR           (VLR_DECODE_COMMS_AREA_BASE_ADDR + VLR_DECODE_COMMS_AREA_SIZE)
#define VLR_CONTROL_COMMS_AREA_SIZE                172
/*! Completion communications area base address within the VLR */
#define VLR_COMPLETION_COMMS_AREA_BASE_ADDR        (VLR_CONTROL_COMMS_AREA_BASE_ADDR + VLR_CONTROL_COMMS_AREA_SIZE)
#define VLR_COMPLETION_COMMS_AREA_SIZE             476
/*! Page table directories area base address within the VLR */
#define VLR_PAGE_TABLE_DIRECTORIES_AREA_BASE_ADDR  (VLR_COMPLETION_COMMS_AREA_BASE_ADDR + VLR_COMPLETION_COMMS_AREA_SIZE)
#define VLR_PAGE_TABLE_DIRECTORY_SIZE              32
/*! Firmware state area base address within the VLR */
#define VLR_FIRMWARE_STATE_AREA_BASE_ADDR          (VLR_PAGE_TABLE_DIRECTORIES_AREA_BASE_ADDR + VLR_PAGE_TABLE_DIRECTORY_SIZE)
#define VLR_FIRMWARE_STATE_AREA_SIZE               128

/*! Host <-> MTX communications area base address within the VLR */
#define VLR_COMMS_AREA_SIZE  (VLR_DECODE_COMMS_AREA_SIZE + \
                              VLR_CONTROL_COMMS_AREA_SIZE + \
                              VLR_COMPLETION_COMMS_AREA_SIZE + \
                              VLR_PAGE_TABLE_DIRECTORY_SIZE + \
                              VLR_FIRMWARE_STATE_AREA_SIZE)


/* Sanity check the VLR allocation size: */
#if ((VLR_FE_AREA_SIZE + VLR_BE_AREA_SIZE + VLR_COMMS_AREA_SIZE) > (VLR_SIZE))
    #error "VLR overallocated! Please, correct..."
#endif


/*!
******************************************************************************
 MSVDX VLR configuration
******************************************************************************/
/*! Number of cores running the VDEC Firmware */
#define VDECFW_MAX_NUM_CORES    (3)


/*!
******************************************************************************
 VDEC Firmware MTXIO configuration
******************************************************************************/
/*! Word Size of buffer used to pass messages between LISR and HISR - the value should come from system.h   */
#define MSVDX_SIZE_MSG_BUFFER   (1*1024)
/*! Max. MTX->Host message size 1/2 of comms buffer, 1/4 for size in words - the value should come from system.h */
#define MSVDX_MAX_MSG_SIZE      (VLR_COMPLETION_COMMS_AREA_SIZE>>3)
/*! Max. number of pending messages between LISR and HISR - the value should come from system.h        */
#define MSVDX_MAX_LISR_HISR_MSG (MSVDX_SIZE_MSG_BUFFER/MSVDX_MAX_MSG_SIZE)
/*! Max number of times message send will be tried before failing due to full message buffer - each try is 1ms apart */
#define MSVDX_MAX_NUM_COMMS_SPACE_RETRIES   (1000)


/*!
******************************************************************************

******************************************************************************/
/*! Macro used to convert milliseconds to timer ticks. */
#define MILLISECOND_TO_TICK(x) ((x == 0xffffffff) ? x : (IMG_UINT32)((x + (TIM_TICK_PERIOD - 1)) / TIM_TICK_PERIOD))


/*!
******************************************************************************
******************************************************************************
******************************************************************************

 This section of the header file contains definitions
 that should probably be in sys_target.h

 MTX definitions

******************************************************************************
******************************************************************************
******************************************************************************/


#define REG_START(memspace)         (REG_START_MSVDX_ ## memspace ## _MTX)
#define REG_END(memspace)           (REG_END_MSVDX_   ## memspace ## _MTX)
#define INRANGE(address, memspace)  (((address) >= REG_START(memspace)) && ((address) < REG_END(memspace)))

// Register bank offsets and sizes.
#define REG_BASE_MTX                        0x04800000
#define REG_BASE_HOST                       0x00000000

#define REG_OFFSET_MSVDX_MTX                0x00000000
#define REG_OFFSET_MSVDX_VDMC               0x00000400
#define REG_OFFSET_MSVDX_VDEB               0x00000480
#define REG_OFFSET_MSVDX_DMAC               0x00000500
#define REG_OFFSET_MSVDX_SYS                0x00000600
#define REG_OFFSET_MSVDX_VEC_IQRAM          0x00000700
#define REG_OFFSET_MSVDX_VEC                0x00000800
#define REG_OFFSET_MSVDX_CMD                0x00001000
#define REG_OFFSET_MSVDX_VEC_RAM            0x00002000
#define REG_OFFSET_MSVDX_VEC_VLC            0x00003000
#define REG_OFFSET_MSVDX_VEC_LINE_STORE     0x00006000
#define REG_OFFSET_MSVDX_TEST               0x00007FF0
#define REG_OFFSET_MSVDX_TEST_3             0x0000FFC0
#define REG_OFFSET_MSVDX_VEC_RAM_2          0x00008000
#define REG_OFFSET_MSVDX_VEC_IQRAM2         0x0000A000

#define REG_SIZE_MSVDX_MTX                  0x00000400
#define REG_SIZE_MSVDX_VDMC                 0x00000080
#define REG_SIZE_MSVDX_VDEB                 0x00000080
#define REG_SIZE_MSVDX_DMAC                 0x00000100
#define REG_SIZE_MSVDX_SYS                  0x00000100
#define REG_SIZE_MSVDX_VEC_IQRAM            0x00000100
#define REG_SIZE_MSVDX_VEC                  0x00000800
#define REG_SIZE_MSVDX_CMD                  0x00001000
#define REG_SIZE_MSVDX_VEC_RAM              0x00001000
#define REG_SIZE_MSVDX_VEC_VLC              0x00002000
#define REG_SIZE_MSVDX_VEC_LINE_STORE       0x00001000
#define REG_SIZE_MSVDX_TEST                 0x00000010
#define REG_SIZE_MSVDX_TEST_3               0x00000018
#define REG_SIZE_MSVDX_VEC_RAM_2            0x00001000
#define REG_SIZE_MSVDX_VEC_IQRAM2           0x00000100


// Register spaces shared by cores
#define REG_OFFSET_MSVDX_SYNCRAM            0x0000D000
#define REG_SIZE_MSVDX_SYNCRAM              0x00001000


// Register bank addresses (MTX view)
#define REG_START_MSVDX_MTX_MTX             (REG_BASE_MTX + REG_OFFSET_MSVDX_MTX)
#define REG_END_MSVDX_MTX_MTX               (REG_START_MSVDX_MTX_MTX + REG_SIZE_MSVDX_MTX)

#define REG_START_MSVDX_VDMC_MTX            (REG_BASE_MTX + REG_OFFSET_MSVDX_VDMC)
#define REG_END_MSVDX_VDMC_MTX              (REG_START_MSVDX_VDMC_MTX + REG_SIZE_MSVDX_VDMC)

#define REG_START_MSVDX_VDEB_MTX            (REG_BASE_MTX + REG_OFFSET_MSVDX_VDEB)
#define REG_END_MSVDX_VDEB_MTX              (REG_START_MSVDX_VDEB_MTX + REG_SIZE_MSVDX_VDEB)

#define REG_START_MSVDX_DMAC_MTX            (REG_BASE_MTX + REG_OFFSET_MSVDX_DMAC)
#define REG_END_MSVDX_DMAC_MTX              (REG_START_MSVDX_DMAC_MTX + REG_SIZE_MSVDX_DMAC)

#define REG_START_MSVDX_SYS_MTX             (REG_BASE_MTX + REG_OFFSET_MSVDX_SYS)
#define REG_END_MSVDX_SYS_MTX               (REG_START_MSVDX_SYS_MTX + REG_SIZE_MSVDX_SYS)

#define REG_START_MSVDX_VEC_IQRAM_MTX       (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC_IQRAM)
#define REG_END_MSVDX_VEC_IQRAM_MTX         (REG_START_MSVDX_VEC_IQRAM_MTX + REG_SIZE_MSVDX_VEC_IQRAM)

#define REG_START_MSVDX_VEC_MTX             (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC)
#define REG_END_MSVDX_VEC_MTX               (REG_START_MSVDX_VEC_MTX + REG_SIZE_MSVDX_VEC)

#define REG_START_MSVDX_CMD_MTX             (REG_BASE_MTX + REG_OFFSET_MSVDX_CMD)
#define REG_END_MSVDX_CMD_MTX               (REG_START_MSVDX_CMD_MTX + REG_SIZE_MSVDX_CMD)

#define REG_START_MSVDX_VEC_RAM_MTX         (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC_RAM)
#define REG_END_MSVDX_VEC_RAM_MTX           (REG_START_MSVDX_VEC_RAM_MTX + REG_SIZE_MSVDX_VEC_RAM)

#define REG_START_MSVDX_VEC_VLC_MTX         (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC_VLC)
#define REG_END_MSVDX_VEC_VLC_MTX           (REG_START_MSVDX_VEC_VLC_MTX + REG_SIZE_MSVDX_VEC_VLC)

#define REG_START_MSVDX_VEC_LINE_STORE_MTX  (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC_LINE_STORE)
#define REG_END_MSVDX_VEC_LINE_STORE_MTX    (REG_START_MSVDX_VEC_LINE_STORE_MTX + REG_SIZE_MSVDX_VEC_LINE_STORE)

#define REG_START_MSVDX_TEST_MTX            (REG_BASE_MTX + REG_OFFSET_MSVDX_TEST)
#define REG_END_MSVDX_TEST_MTX              (REG_START_MSVDX_TEST_MTX + REG_SIZE_MSVDX_TEST)

#define REG_START_MSVDX_TEST_3_MTX          (REG_BASE_MTX + REG_OFFSET_MSVDX_TEST_3)
#define REG_END_MSVDX_TEST_3_MTX            (REG_START_MSVDX_TEST_3_MTX + REG_SIZE_MSVDX_TEST_3)

#define REG_START_MSVDX_VEC_RAM_2_MTX       (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC_RAM_2)
#define REG_END_MSVDX_VEC_RAM_2_MTX         (REG_START_MSVDX_VEC_RAM_2_MTX + REG_SIZE_MSVDX_VEC_RAM_2)

#define REG_START_MSVDX_VEC_IQRAM2_MTX      (REG_BASE_MTX + REG_OFFSET_MSVDX_VEC_IQRAM2)
#define REG_END_MSVDX_VEC_IQRAM2_MTX        (REG_START_MSVDX_VEC_IQRAM2_MTX + REG_SIZE_MSVDX_VEC_IQRAM2)

#define REG_START_MSVDX_SYNCRAM_MTX         (REG_BASE_MTX + REG_OFFSET_MSVDX_SYNCRAM)
#define REG_END_MSVDX_SYNCRAM_MTX           (REG_START_MSVDX_SYNCRAM_MTX + REG_SIZE_MSVDX_SYNCRAM)

// Register bank addresses (Host view)
#define REG_START_MSVDX_MTX_HOST            (REG_BASE_HOST + REG_OFFSET_MSVDX_MTX)
#define REG_END_MSVDX_MTX_HOST              (REG_START_MSVDX_MTX_HOST + REG_SIZE_MSVDX_MTX)

#define REG_START_MSVDX_VDMC_HOST           (REG_BASE_HOST + REG_OFFSET_MSVDX_VDMC)
#define REG_END_MSVDX_VDMC_HOST             (REG_START_MSVDX_VDMC_HOST + REG_SIZE_MSVDX_VDMC)

#define REG_START_MSVDX_VDEB_HOST           (REG_BASE_HOST + REG_OFFSET_MSVDX_VDEB)
#define REG_END_MSVDX_VDEB_HOST             (REG_START_MSVDX_VDEB_HOST + REG_SIZE_MSVDX_VDEB)

#define REG_START_MSVDX_DMAC_HOST           (REG_BASE_HOST + REG_OFFSET_MSVDX_DMAC)
#define REG_END_MSVDX_DMAC_HOST             (REG_START_MSVDX_DMAC_HOST + REG_SIZE_MSVDX_DMAC)

#define REG_START_MSVDX_SYS_HOST            (REG_BASE_HOST + REG_OFFSET_MSVDX_SYS)
#define REG_END_MSVDX_SYS_HOST              (REG_START_MSVDX_SYS_HOST + REG_SIZE_MSVDX_SYS)

#define REG_START_MSVDX_VEC_IQRAM_HOST      (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC_IQRAM)
#define REG_END_MSVDX_VEC_IQRAM_HOST        (REG_START_MSVDX_VEC_IQRAM_HOST + REG_SIZE_MSVDX_VEC_IQRAM)

#define REG_START_MSVDX_VEC_HOST            (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC)
#define REG_END_MSVDX_VEC_HOST              (REG_START_MSVDX_VEC_HOST + REG_SIZE_MSVDX_VEC)

#define REG_START_MSVDX_CMD_HOST            (REG_BASE_HOST + REG_OFFSET_MSVDX_CMD)
#define REG_END_MSVDX_CMD_HOST              (REG_START_MSVDX_CMD_HOST + REG_SIZE_MSVDX_CMD)

#define REG_START_MSVDX_VEC_RAM_HOST        (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC_RAM)
#define REG_END_MSVDX_VEC_RAM_HOST          (REG_START_MSVDX_VEC_RAM_HOST + REG_SIZE_MSVDX_VEC_RAM)

#define REG_START_MSVDX_VEC_VLC_HOST        (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC_VLC)
#define REG_END_MSVDX_VEC_VLC_HOST          (REG_START_MSVDX_VEC_VLC_HOST + REG_SIZE_MSVDX_VEC_VLC)

#define REG_START_MSVDX_VEC_LINE_STORE_HOST (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC_LINE_STORE)
#define REG_END_MSVDX_VEC_LINE_STORE_HOST   (REG_START_MSVDX_VEC_LINE_STORE_HOST + REG_SIZE_MSVDX_VEC_LINE_STORE)

#define REG_START_MSVDX_TEST_HOST           (REG_BASE_HOST + REG_OFFSET_MSVDX_TEST)
#define REG_END_MSVDX_TEST_HOST             (REG_START_MSVDX_TEST_HOST + REG_SIZE_MSVDX_TEST)

#define REG_START_MSVDX_VEC_RAM_2_HOST      (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC_RAM_2)
#define REG_END_MSVDX_VEC_RAM_2_HOST        (REG_START_MSVDX_VEC_RAM_2_HOST + REG_SIZE_MSVDX_VEC_RAM_2)

#define REG_START_MSVDX_VEC_IQRAM2_HOST     (REG_BASE_HOST + REG_OFFSET_MSVDX_VEC_IQRAM2)
#define REG_END_MSVDX_VEC_IQRAM2_HOST       (REG_START_MSVDX_VEC_IQRAM2_HOST + REG_SIZE_MSVDX_VEC_IQRAM2)

#define REG_START_MSVDX_SYNCRAM_HOST        (REG_BASE_HOST + REG_OFFSET_MSVDX_SYNCRAM)
#define REG_END_MSVDX_SYNCRAM_HOST          (REG_START_MSVDX_SYNCRAM_HOST + REG_SIZE_MSVDX_SYNCRAM)




#ifdef __cplusplus
}
#endif

#endif /* __VDEC_H__   */

