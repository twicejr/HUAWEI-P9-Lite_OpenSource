/*************************************************************************/ /*!
@File           include_all_fw_variants.h
@Title          Firmware variant header
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@Description    Header file that includes all firmware variants
@License        Strictly Confidential.
*/ /**************************************************************************/

#ifndef __INCLUDE_ALL_VARIANTS_INC_INCLUDED__
#define __INCLUDE_ALL_VARIANTS_INC_INCLUDED__

#define INCLUDE_ALL_VARIANTS_TEMPLATE_VERSION   (1)

#define FW_BIN_FORMAT_VERSION (2)

struct IMG_COMPILED_FW_BIN_RECORD {

    IMG_UINT32 ui32TextSize, ui32DataSize;
    IMG_UINT32 ui32DataOrigin, ui32TextOrigin;
    IMG_UINT32 ui32TextRelocSize, ui32DataRelocSize;

    IMG_UINT32 ui32Pipes;
    IMG_CHAR   *sFormat, *rcMode;
    IMG_UINT32 ui32FormatsMask, ui32HwConfig;

    IMG_UINT32 ui32IntDefineCount;
    IMG_CHAR   **pscIntDefineNames;
    IMG_UINT32 *pui32IntDefines;

    IMG_UINT32 *pui32Text, *pui32Data;
    IMG_UINT32 *pui32TextReloc, *pui32DataDeloc;
    IMG_UINT32 *pui32TextRelocFullAddr, *pui32TextRelocType;
};

#include "H264MVC_FW_NO_RC_pipes_2_contexts_2_hwconfig_0_bin.c"
#include "H264MVC_FW_CBR_pipes_2_contexts_2_hwconfig_0_bin.c"
#include "H264MVC_FW_VBR_pipes_2_contexts_2_hwconfig_0_bin.c"
#include "H264_FW_ALL_pipes_2_contexts_2_hwconfig_0_bin.c"
#include "H264MVC_FW_NO_RC_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "JPEG_FW_NO_RC_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "H264MVC_FW_CBR_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "H264MVC_FW_VBR_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "H264_FW_ALL_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "LEGACY_VIDEO_FW_ALL_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "JPEG_H264_FW_ALL_pipes_4_contexts_2_hwconfig_0_bin.c"
#include "H264_FW_ALL_pipes_3_contexts_3_hwconfig_0_bin.c"
#include "ALL_CODECS_FW_ALL_pipes_2_contexts_8_hwconfig_1_bin.c"

IMG_UINT32 ui32AllFirmwareBinariesCount = 13;
struct IMG_COMPILED_FW_BIN_RECORD *sAllFirmwareBinaries[] = {
	&sIMG_COMPILED_H264MVC_FW_NO_RC_pipes_2_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264MVC_FW_CBR_pipes_2_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264MVC_FW_VBR_pipes_2_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264_FW_ALL_pipes_2_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264MVC_FW_NO_RC_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_JPEG_FW_NO_RC_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264MVC_FW_CBR_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264MVC_FW_VBR_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264_FW_ALL_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_LEGACY_VIDEO_FW_ALL_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_JPEG_H264_FW_ALL_pipes_4_contexts_2_hwconfig_0,
	&sIMG_COMPILED_H264_FW_ALL_pipes_3_contexts_3_hwconfig_0,
	&sIMG_COMPILED_ALL_CODECS_FW_ALL_pipes_2_contexts_8_hwconfig_1,
};

#endif
