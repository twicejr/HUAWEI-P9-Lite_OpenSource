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

/*lint -save -e537*/

#include "osl_sem.h"
#include "osl_malloc.h"
#include "osl_thread.h"
#include "mdrv_socp_common.h"
#include "bsp_version.h"
#include "bsp_icc.h"
#include "socp_balong.h"
#include <of.h>


/*lint -restore*/
/*lint -save -e506 -e40 -e63 -e516 */
#ifdef __cplusplus
extern "C" {
#endif



#if defined(__KERNEL__)

extern void* socp_malloc(u32 u32Size);
extern s32 socp_free(void* pMem);


#define SOCP_TEST_CODE_SRC SOCP_CODER_SRC_BSP_ACORE
#else

#define socp_malloc     osl_cachedma_malloc
#define socp_free       osl_cachedma_free


#define SOCP_TEST_CODE_SRC SOCP_CODER_SRC_LOM_CNF1
#endif




/*
    mdrv_socp_coder_set_dest_chan_attr
    mdrv_socp_start
    DRV_SOCP_GET_READ_BUFF
    DRV_SOCP_READ_DATA_DONE
    */
int mdrv_socp_test_001(void)
{
#if defined(__KERNEL__)
    int ret;
    SOCP_BUFFER_RW_STRU  pBuffer;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;
    unsigned int len = 0x1000;
    unsigned char *p;

    p = socp_malloc(len);
    if(BSP_NULL == p)
    {
        socp_printf("set chan failed, no mem\n");
        return -1;
    }
    EncDstAttr.u32EncDstThrh = 0;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = p;
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = p + len -1;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x20;
    ret = mdrv_socp_coder_set_dest_chan_attr(SOCP_CODER_DST_OM_CNF, &EncDstAttr);
    if(BSP_OK != ret)
    {
        socp_printf("set chan failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

    ret = DRV_SOCP_REGISTER_READ_CB(SOCP_CODER_DST_OM_CNF,NULL);
    if(ret!= BSP_OK)
    {
        socp_printf("DRV_SOCP_REGISTER_READ_CB chan failed\n");
        socp_free(p);
        return -1;
    }

    ret = DRV_SOCP_GET_READ_BUFF(SOCP_CODER_DST_OM_CNF, &pBuffer);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_GET_READ_BUFF failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

    ret = DRV_SOCP_READ_DATA_DONE(SOCP_CODER_DST_OM_CNF,0);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_READ_DATA_DONE failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

#endif

    return 0;
}

/*
    mdrv_socp_corder_set_src_chan
    mdrv_socp_start
    DRV_SOCP_FREE_CHANNEL
    mdrv_socp_stop
    DRV_SOCP_CLEAN_ENCSRC_CHAN
    */
int mdrv_socp_test_002(void)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    unsigned int len = 0x1000;
    unsigned char *p;
    unsigned int ret;
    SOCP_BUFFER_RW_STRU pBuff;

    p = (unsigned char*)socp_malloc(len);
    if(BSP_NULL == p)
    {
        socp_printf("alloc chan failed, no mem\n");
        return -1;
    }

    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_LIST;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 0);
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = p;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = p + len - 1;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = (u8*)0x300f8000;
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd   = (u8*)0x300f8800 -1;
    ret = mdrv_socp_corder_set_src_chan(SOCP_TEST_CODE_SRC, &EncSrcAttr);
    if(BSP_OK != ret)
    {
        socp_printf("alloc chan failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }
    ret = DRV_SOCP_REGISTER_RD_CB(SOCP_TEST_CODE_SRC,NULL);
    if(ret!= BSP_OK)
    {
        socp_printf("DRV_SOCP_REGISTER_RD_CB chan failed\n");
        return -1;
    }
    ret = mdrv_socp_start(SOCP_TEST_CODE_SRC);
    if(BSP_OK != ret)
    {
        socp_printf("mdrv_socp_start failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

    ret = mdrv_socp_write_done(SOCP_TEST_CODE_SRC,0x20);
    if(BSP_OK != ret)
    {
        socp_printf("mdrv_socp_write_done failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

    ret = mdrv_socp_get_rd_buffer(SOCP_TEST_CODE_SRC, &pBuff);
    if(BSP_OK != ret)
    {
        socp_printf("mdrv_socp_get_rd_buffer failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

    ret = mdrv_socp_get_write_buff(SOCP_TEST_CODE_SRC, &pBuff);
    if(BSP_OK != ret)
    {
        socp_printf("mdrv_socp_get_write_buff failed, return error(0x%x)\n", ret);
        socp_free(p);
        return -1;
    }

    ret = mdrv_socp_read_rd_done(SOCP_TEST_CODE_SRC,0);
    if(BSP_OK != ret && BSP_ERR_SOCP_NULL != ret)
    {
        socp_printf("mdrv_socp_read_rd_done failed, return error(0x%x)\n", ret);
        socp_free(p);
    }

    ret = mdrv_socp_stop(SOCP_TEST_CODE_SRC);
    if(BSP_OK != ret)
    {
        socp_printf("mdrv_socp_stop failed, return error(0x%x)\n", ret);
        socp_free(p);
    }

    socp_free(p);
    return 0;
}


/*
    DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
    DRV_SOCP_DECODER_SET_DEST_CHAN
    */
int mdrv_socp_test_003(void)
{
#if defined(__KERNEL__)
    unsigned int u32ChanId;
    SOCP_DECODER_DEST_CHAN_STRU DecDestAttr;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;
    int ret;

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_0;
    DecDestAttr.u32SrcChanID = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, 0);
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = (unsigned char*)0x30004000;
    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = (unsigned char*)0x30007fff;
    DecDestAttr.sDecoderDstSetBuf.u32Threshold = 1;

    ret= DRV_SOCP_DECODER_SET_DEST_CHAN(u32ChanId,&DecDestAttr);
    if(ret!= BSP_OK)
    {
        socp_printf("DRV_SOCP_DECODER_SET_DEST_CHAN  failed \n");
        return -1;
    }

    ret = bsp_socp_free_channel(u32ChanId);
    if(ret!= BSP_OK)
    {
        socp_printf("bsp_socp_free_channel  failed \n");
        return -1;
    }

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, 0);

    DecSrcAttr.eMode= SOCP_DECSRC_CHNMODE_BYTES;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = (unsigned char*)0x30004000;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd   = (unsigned char*)0x30007fff;
    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;

    ret = DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR(u32ChanId,&DecSrcAttr);
    if(ret!= BSP_OK)
    {
        socp_printf("DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR  failed \n");
        return -1;
    }
    ret = socp_soft_free_decsrc_chan(u32ChanId);
    if(ret!= BSP_OK)
    {
        socp_printf("bsp_socp_free_channel  failed \n");
        return -1;
    }
#endif
    return 0;
}

/*
    DRV_SOCP_REGISTER_EVENT_CB
    DRV_SOCP_REGISTER_RD_CB
    DRV_SOCP_REGISTER_READ_CB
    */
int mdrv_socp_test_004(void)
{
    int ret;
    ret = DRV_SOCP_REGISTER_EVENT_CB(SOCP_TEST_CODE_SRC,NULL);
    if(ret!= BSP_OK)
    {
        socp_printf("DRV_SOCP_REGISTER_EVENT_CB chan failed\n");
        return -1;
    }
    ret = DRV_SOCP_FREE_CHANNEL(SOCP_TEST_CODE_SRC);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_FREE_CHANNEL failed, return error(0x%x)\n", ret);
    }

    ret = DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_TEST_CODE_SRC);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_CLEAN_ENCSRC_CHAN failed, return error(0x%x)\n", ret);
    }

    return 0;
}


/*
    mdrv_socp_set_log_int_timeout
    mdrv_socp_set_log_int_default_timeout
    mdrv_socp_enc_dst_buf_flush
    mdrv_socp_get_sd_logcfg
    DRV_SOCP_SET_TIMEOUT
    */
int mdrv_socp_test_006(void)
{
#if defined(__KERNEL__)
    int ret;
    struct socp_enc_dst_log_cfg* cfg;
    SOCP_ENC_DST_BUF_LOG_CFG_STRU stLogCfg;

    mdrv_socp_set_log_int_timeout();
    mdrv_socp_set_log_int_default_timeout();

    ret = DRV_SOCP_SET_TIMEOUT(SOCP_TIMEOUT_BUFOVF_DISABLE,100);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_SET_TIMEOUT failed, return error(0x%x)\n", ret);
        return -1;
    }


    /* ¶ÁÈ¡ÅäÖÃ */
    cfg = bsp_socp_get_log_cfg();
    if((BSP_OK != ret)&&(cfg->logOnFlag == TRUE))
    {
        socp_printf(" failed, return error(0x%x)\n", ret);
        return -1;
    }

    ret = mdrv_socp_get_sd_logcfg(&stLogCfg);
    if(BSP_OK != ret)
    {
        socp_printf("mdrv_socp_get_sd_logcfg failed, return error(0x%x)\n", ret);
        return -1;
    }

#endif
    return 0;
}



/*
    DRV_SOCP_VOTE
    DRV_SOCP_VOTE_TO_MCORE
    DRV_SOCP_GET_STATE
    */

int mdrv_socp_test_007(void)
{
    int ret = 0;
#if defined(__KERNEL__)
    ret = DRV_SOCP_VOTE(2,1);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_VOTE failed, return error(0x%x)\n", ret);
        return -1;
    }
#endif

#if !defined(__KERNEL__)
    ret = DRV_SOCP_VOTE_TO_MCORE(0);
    if(BSP_OK != ret)
    {
        socp_printf("DRV_SOCP_VOTE_TO_MCORE failed, return error(0x%x)\n", ret);
        return -1;
    }
#endif
    ret = DRV_SOCP_GET_STATE();
    if((ret != SOCP_BUSY) && (ret != SOCP_IDLE))
    {
        socp_printf("DRV_SOCP_GET_STATE failed, return error(0x%x)\n", ret);
        return -1;
    }
    return 0;
}







#ifdef __cplusplus
}
#endif


