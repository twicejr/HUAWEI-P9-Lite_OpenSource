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
/*lint -save -e537 -e701 -e713 -e734 -e813 -e958 -e718 -e746*/
#include "osm.h"
#include "gen_msg.h"
#include "at_lte_common.h"
#include "ATCmdProc.h"

/*lint -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_COMM_CMD_C
/*lint +e767 */

/* 为了简化不考虑出错 */
VOS_UINT8 Hec2ToVal(VOS_UINT8* str)
{
    VOS_UINT8 ucMid = 0;
    VOS_UINT8 ucVal = 0;
    VOS_UINT8 i     = 0;

    for(i=0; i<2; i++)
    {
        if((str[i]>='0')&&(str[i]<='9'))
        {
            ucMid = str[i] - '0';
        }
        else if((str[i]>='a')&&(str[i]<='f'))
        {
            ucMid = str[i] - 'a' + 10;
        }
        else if((str[i]>='A')&&(str[i]<='F'))
        {
            ucMid = str[i] - 'A' + 10;
        }
        else
        {
            ucMid = 0;
        }

        ucVal = (ucVal<<4) + ucMid;
    }

    return ucVal;
}

/* 计算字符串的CRC */
VOS_UINT32 Calc_CRC32(VOS_UINT8 *Packet, VOS_UINT32 dwLength)
{
    static VOS_UINT32 CRC32_TABLE[256] = {
        0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
        0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
        0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
        0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
        0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
        0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
        0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
        0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1, 0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
        0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
        0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
        0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
        0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
        0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
        0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
        0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
        0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
        0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
        0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
        0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
        0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
        0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
        0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
        0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7, 0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
        0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
        0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
        0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
        0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
        0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
        0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
        0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
        0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
        0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4,
    };

    VOS_UINT32 CRC32 = 0;
    VOS_UINT32 i     = 0;

    for(i=0; i<dwLength; i++)
    {
        CRC32 = ((CRC32<<8)|Packet[i]) ^ (CRC32_TABLE[(CRC32>>24)&0xFF]); /* [false alarm]:fortify  */
    }

    for(i=0; i<4; i++)
    {
        CRC32 = ((CRC32<<8)|0x00) ^ (CRC32_TABLE[(CRC32>>24)&0xFF]); /* [false alarm]:fortify  */
    }

    return CRC32;
}

/*****************************************************************************
 函 数 名  : atSetLTCommCmdPara
 功能描述  : 发送通用AT命令到TL C核
 输入参数  : ucClientId Client ID
             ulTmode 模式
 输出参数  : 无
 返 回 值  : 成功返回AT_OK，失败返回AT_ERROR
*****************************************************************************/

VOS_UINT32 atSetLTCommCmdPara(VOS_UINT8 ucClientId)
{
    FTM_SET_LTCOMMCMD_REQ_STRU *pstSetReq = NULL;
    VOS_UINT16 usCRC_L    = 0;
    VOS_UINT16 usCRC_H    = 0;
    VOS_UINT32 ulCRC      = 0;
    VOS_UINT32 ulCRC_Cal  = 0;
    VOS_UINT32 ulRst      = ERR_MSP_SUCCESS;
    VOS_UINT32 i          = 0;
    VOS_UINT32 ulLen      = 0;

    VOS_UINT8  *pdata_aucPara = NULL;


    /* 参数检查 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(5 > gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if( (0 == gastAtParaList[0].usParaLen) ||
		(0 == gastAtParaList[1].usParaLen) ||
		(0 == gastAtParaList[2].usParaLen) ||
		(0 == gastAtParaList[3].usParaLen) ||
		(0 == gastAtParaList[4].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if( gastAtParaList[4].usParaLen + gastAtParaList[5].usParaLen + gastAtParaList[6].usParaLen + gastAtParaList[7].usParaLen> FTM_MAX_COMM_CMD_LEN*2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pdata_aucPara = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT,
                                 gastAtParaList[4].usParaLen +
                                 gastAtParaList[5].usParaLen +
                                 gastAtParaList[6].usParaLen +
                                 gastAtParaList[7].usParaLen
                                 );
    if (NULL == pdata_aucPara)
    {
        (VOS_VOID)vos_printf("[%s]failed to malloc\n",__FUNCTION__);
        return AT_ERROR;
    }

    VOS_MemCpy(pdata_aucPara, gastAtParaList[4].aucPara, gastAtParaList[4].usParaLen);
    VOS_MemCpy(pdata_aucPara + gastAtParaList[4].usParaLen,
                gastAtParaList[5].aucPara,
                gastAtParaList[5].usParaLen);
    VOS_MemCpy(pdata_aucPara + gastAtParaList[4].usParaLen + gastAtParaList[5].usParaLen,
                gastAtParaList[6].aucPara,
                gastAtParaList[6].usParaLen);
    VOS_MemCpy(pdata_aucPara + gastAtParaList[4].usParaLen + gastAtParaList[5].usParaLen + gastAtParaList[6].usParaLen,
                gastAtParaList[7].aucPara,
                gastAtParaList[7].usParaLen);

    usCRC_L = gastAtParaList[2].ulParaValue;
    usCRC_H = gastAtParaList[3].ulParaValue;
    ulCRC = usCRC_H<<16;
    ulCRC = ulCRC + usCRC_L;
    ulCRC_Cal = Calc_CRC32(pdata_aucPara, gastAtParaList[4].usParaLen + gastAtParaList[5].usParaLen + gastAtParaList[6].usParaLen + gastAtParaList[7].usParaLen);

    /* 对传入参数进行CRC校验  */
    if(ulCRC_Cal != ulCRC)
    {
        VOS_MemFree(WUEPS_PID_AT, pdata_aucPara);
        (VOS_VOID)vos_printf("[%s]CRC ERROR\n",__FUNCTION__);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulLen = sizeof(FTM_SET_LTCOMMCMD_REQ_STRU) + (VOS_UINT32)(gastAtParaList[1].ulParaValue)/2;
    pstSetReq = (FTM_SET_LTCOMMCMD_REQ_STRU *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT,ulLen);

    if (pstSetReq == VOS_NULL){
        VOS_MemFree(WUEPS_PID_AT, pdata_aucPara);
        (VOS_VOID)vos_printf("[%s]failed to malloc\n",__FUNCTION__);
        return AT_ERROR;
    }
    pstSetReq->ulCmdDest = (FTM_LTCOMMCMD_DEST)(gastAtParaList[0].ulParaValue);
    pstSetReq->ulDataLen = (VOS_UINT32)(gastAtParaList[1].ulParaValue)/2;
    for(i=0; i<pstSetReq->ulDataLen; i++)
    {
        pstSetReq->cData[i] = Hec2ToVal( pdata_aucPara+2*i);
    }
    VOS_MemFree(WUEPS_PID_AT, pdata_aucPara);

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_LTCOMMCMD_REQ, ucClientId,
        (VOS_VOID*)(pstSetReq), ulLen);
    VOS_MemFree(WUEPS_PID_AT, pstSetReq);
    if(AT_SUCCESS == ulRst)
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_LTCOMMCMD_SET;
        return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */
    }

    return AT_ERROR;
}

/*****************************************************************************
 函 数 名  : atSetLTCommCmdParaCnfProc
 功能描述  : 通用命令返回处理函数
 输入参数  : ucClientId Client ID
             pMsgBlock 消息内容
 输出参数  : 无
 返 回 值  : 成功返回AT_OK，失败返回AT_ERROR
*****************************************************************************/

VOS_UINT32 atSetLTCommCmdParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent                = NULL;
    FTM_SET_LTCOMMCMD_CNF_STRU *pstCnf = NULL;
    VOS_UINT32 ulCRC                   = 0;
    VOS_UINT16 usCRC_L                 = 0;
    VOS_UINT16 usCRC_H                 = 0;
    VOS_UINT16 usLength                = 0;
    VOS_UINT32 i                       = 0;

    if (!pMsgBlock){
        (VOS_VOID)vos_printf("[%s]pMsgBlock null\n",__FUNCTION__);
        return ERR_MSP_INVALID_PARAMETER;
    }
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_LTCOMMCMD_CNF_STRU *)pEvent->ulParam1;

    /* 计算CRC */
    ulCRC = Calc_CRC32((VOS_UINT8 *)pstCnf->cData, pstCnf->ulDataLen);
    usCRC_L = (VOS_UINT16)(ulCRC & 0x0000FFFF);
    usCRC_H = (VOS_UINT16)(ulCRC >> 16);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^LTCOMMCMD:%d,%d,%d,", pstCnf->ulDataLen, usCRC_L, usCRC_H);

    for(i=0; i<pstCnf->ulDataLen; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"%02X", (VOS_UINT8)pstCnf->cData[i]);
    }

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}

/*****************************************************************************
 函 数 名  : atQryLTCommCmdPara
 功能描述  : 发送通用AT命令查询到TL C核
 输入参数  : ucClientId Client ID
 输出参数  : 无
 返 回 值  : 成功返回AT_OK，失败返回AT_ERROR
*****************************************************************************/

VOS_UINT32 atQryLTCommCmdPara(VOS_UINT8 ucClientId)
{
    FTM_RD_NOPRARA_REQ_STRU stQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_LTCOMMCMD_REQ,
        ucClientId, (VOS_VOID*)(&stQryReq), sizeof(stQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_LTCOMMCMD_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
 函 数 名  : atQryLTCommCmdParaCnfProc
 功能描述  : 通用AT命令查询返回处理函数
 输入参数  : ucClientId Client ID
             pMsgBlock 消息内容
 输出参数  : 无
 返 回 值  : 成功返回AT_OK，失败返回AT_ERROR
*****************************************************************************/

VOS_UINT32 atQryLTCommCmdParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent                = NULL;
    FTM_RD_LTCOMMCMD_CNF_STRU *pstCnf  = NULL;
    VOS_UINT32 ulCRC                   = 0;
    VOS_UINT16 usCRC_L                 = 0;
    VOS_UINT16 usCRC_H                 = 0;
    VOS_UINT16 usLength                = 0;
    VOS_UINT16 i                       = 0;

    if (!pMsgBlock){
            (VOS_VOID)vos_printf("[%s]pMsgBlock null\n",__FUNCTION__);
            return ERR_MSP_INVALID_PARAMETER;
    }

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_LTCOMMCMD_CNF_STRU *)pEvent->ulParam1;

    /* 计算CRC */
    ulCRC = Calc_CRC32((VOS_UINT8 *)pstCnf->cData, pstCnf->ulDataLen);
    usCRC_L = (unsigned short)(ulCRC & 0x0000FFFF);
    usCRC_H = (unsigned short)(ulCRC >> 16);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^LTCOMMCMD:%d,%d,%d,", pstCnf->ulDataLen,usCRC_L,usCRC_H);

    for(i=0; i<pstCnf->ulDataLen; i++)
    {
      usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"%02X", (VOS_UINT8)pstCnf->cData[i]);
    }

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}
/*lint -restore*/

