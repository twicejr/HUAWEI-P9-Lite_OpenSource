

#ifdef __cplusplus
#if __cplusplus
     extern "C" {
#endif
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_PSMUX_C
/*lint +e767*/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_AT_HSIC)
#include "PsTypeDef.h"
#include "PsMux.h"
#include "PsCommonDef.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 打印开关 */
VOS_UINT32                              g_ulMuxPrintFlag   = PS_FALSE;

/* 消息跟踪开关 */
VOS_UINT32                              g_ulMuxTraceFlag   = PS_FALSE;


/* MUX的统计信息 */
MUX_DEV_STATIC_INFO_STRU                g_stMuxStaticInfo;

MUX_UNFRAME_STATE_ST                    g_stMuxUnframeState;  /*Mux对应的接收数据状态*/

TTF_Q_ST                                g_stMuxUlQue;        /*Mux对应的上行数据接收队列结构*/

MUX_DEV_INFO_STRU                       g_stMuxDevInfo;
MUX_AT_UL_DLCI_INFO_STRU                g_stMuxAtUlDlciInfo[AT_MUX_DLCI_TYPE_BUTT];


/*reversed, 8-bit, poly=0x07*/
const VOS_UINT8 gaucMuxcrctable[256] = {
0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75, 0x0E, 0x9F, 0xED, 0x7C, 0x09,0x98, 0xEA, 0x7B,
0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69, 0x12, 0x83, 0xF1, 0x60, 0x15,0x84, 0xF6, 0x67,
0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D, 0x36, 0xA7, 0xD5, 0x44, 0x31,0xA0, 0xD2, 0x43,
0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51, 0x2A, 0xBB, 0xC9, 0x58, 0x2D,0xBC, 0xCE, 0x5F,
0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05, 0x7E, 0xEF, 0x9D, 0x0C, 0x79,0xE8, 0x9A, 0x0B,
0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19, 0x62, 0xF3, 0x81, 0x10, 0x65,0xF4, 0x86, 0x17,
0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D, 0x46, 0xD7, 0xA5, 0x34, 0x41,0xD0, 0xA2, 0x33,
0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21, 0x5A, 0xCB, 0xB9, 0x28, 0x5D,0xCC, 0xBE, 0x2F,
0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95, 0xEE, 0x7F, 0x0D, 0x9C, 0xE9,0x78, 0x0A, 0x9B,
0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89, 0xF2, 0x63, 0x11, 0x80, 0xF5,0x64, 0x16, 0x87,
0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD, 0xD6, 0x47, 0x35, 0xA4, 0xD1,0x40, 0x32, 0xA3,
0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1, 0xCA, 0x5B, 0x29, 0xB8, 0xCD,0x5C, 0x2E, 0xBF,
0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5, 0x9E, 0x0F, 0x7D, 0xEC, 0x99,0x08, 0x7A, 0xEB,
0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9, 0x82, 0x13, 0x61, 0xF0, 0x85,0x14, 0x66, 0xF7,
0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD, 0xA6, 0x37, 0x45, 0xD4, 0xA1,0x30, 0x42, 0xD3,
0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1, 0xBA, 0x2B, 0x59, 0xC8, 0xBD,0x2C, 0x5E, 0xCF
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID MUX_PrintLog
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString
)
{
    if (PS_TRUE == g_ulMuxPrintFlag)
    {
        vos_printf(pcString);
    }

    return;
}



VOS_VOID MUX_PrintLog1
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1
)
{
    if (PS_TRUE == g_ulMuxPrintFlag)
    {
        vos_printf(pcString, lPara1);
    }

    return;
}



VOS_VOID MUX_PrintLog2
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2
)
{
    if (PS_TRUE == g_ulMuxPrintFlag)
    {
        vos_printf(pcString, lPara1, lPara2);
    }

    return;
}



VOS_UINT32 MUX_DlciCheckFcs(VOS_UINT8* pData, VOS_UINT16 usLen, VOS_UINT8 ucFcs)
{
    /*Init*/
    VOS_UINT8                           ucFCS       = 0xFF;
    VOS_UINT16                          usDatalen   = usLen;
    VOS_UINT8                          *pucBuf      = pData;


    /*len is the number of bytes in the message, p points to message*/
    while (usDatalen--)
    {
        ucFCS = gaucMuxcrctable[ucFCS^*pucBuf++];
    }

    /*Ones complement*/
    ucFCS   = gaucMuxcrctable[ucFCS^ucFcs];
    /*0xCF is the reversed order of 11110011.*/
    if (0xCF == ucFCS)
    {
        /*FCS is OK*/
        return VOS_OK;
    }
    else
    {
        /*FCS is not OK*/
        return VOS_ERR;
    }
}



VOS_UINT8 MUX_DlciGetFcs(VOS_UINT8* pData, VOS_UINT16 usLen)
{
    /*初始化*/
    VOS_UINT8                           ucFCS       = 0xFF;
    VOS_UINT16                          usDatalen   = usLen;
    VOS_UINT8                          *pucBuf      = pData;


    /*len 是这个frame的字节长度, p 指向这个message */
    while (usDatalen--)
    {
        ucFCS   = gaucMuxcrctable[ucFCS^*pucBuf++];
    }
    /*一个frame的Fcs 处理结束*/
    ucFCS   = 0xFF - ucFCS;

    return ucFCS;
}



VOS_UINT32 MUX_DlciIsValid(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci)
{
    /* Dlci的有效值为{1,64} */
    if ((enDlci < AT_MUX_DLCI1_ID)
     || ( enDlci >= AT_MUX_DLCI_TYPE_BUTT))
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciIsValid, ucDlci<1> is error!\r\n", enDlci);
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}



VOS_UINT32 MUX_DlciUlDataToAt(VOS_UINT8* pData)
{
    MUX_FRAME_HEAD                     *pFrame       = (MUX_FRAME_HEAD*)pData;
    VOS_UINT16                          usFrameLen   = 0;
    VOS_UINT8                           bit1Len1EA   = 0;
    VOS_UINT8                           bit7Len1     = 0;
    VOS_UINT8                           bit6AddrDlci = 0;
    VOS_UINT8                           usFcsLen     = 0;
    VOS_UINT8                           ucFcs;
    VOS_UINT8                          *pPayLoad            = VOS_NULL_PTR;
    RCV_UL_DLCI_DATA_FUNC               pRcvUlDlciDataFunc  = VOS_NULL_PTR;


    /* 检查输入参数的合理性*/
    if (VOS_NULL_PTR == pData)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR, "MUX, MUX_DlciUlDataToAt: pData is null.\r\n");
        return VOS_ERR;
    }

    MUX_GET_17_BIT(pFrame->ucLen1, bit1Len1EA, bit7Len1);
    if (1 == bit1Len1EA)
    {
        /*表示长度只占有一个字节*/
        usFrameLen  = bit7Len1;
        pPayLoad    = (pData + 4);
        usFcsLen    = 3;
        ucFcs       = *(pPayLoad + usFrameLen);
    }
    else    /*表示长度有两个字节*/
    {
        usFrameLen  = (VOS_UINT16)(((VOS_UINT16)(pFrame->ucLen2)<<7)+bit7Len1);
        pPayLoad    = (pData + 5);
        usFcsLen    = 4;
        ucFcs       = *(pPayLoad + usFrameLen);
    }

    /*校验地址域，控制域和长度域*/
    if (VOS_OK != MUX_DlciCheckFcs(pData + 1, usFcsLen, ucFcs))
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR, "MUX, MUX_DlciUlDataToAt::MUX_DlciCheckFcs return fail.\r\n");
        return VOS_ERR;
    }

    /*提取链路的DLCI*/
    MUX_GET_116_BIT(pFrame->ucAddr, bit6AddrDlci);

    /* DLCI合法性检查 */
    if (VOS_OK != MUX_DlciIsValid(bit6AddrDlci))
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING, "MUX, MUX_AtRgstUlPortCallBack: enDlci <1> is", bit6AddrDlci);
        return VOS_ERR;
    }

    pRcvUlDlciDataFunc = MUX_AT_UL_DLCI_GET_DATA_CALLBACK_FUNC(bit6AddrDlci);

    /* 发送上行数据 */
    if (VOS_NULL_PTR != pRcvUlDlciDataFunc)
    {
        (VOS_VOID)pRcvUlDlciDataFunc(bit6AddrDlci, pPayLoad, usFrameLen);

        MUX_TraceUlData(bit6AddrDlci, pPayLoad, usFrameLen);

        MUX_DBG_UL_SEND_SUCC_PKT_NUM(1);
    }
    else
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR, "MUX, MUX_AtRgstUlPortCallBack::pRcvUlDlciDataFunc is null.\r\n");
        MUX_DBG_UL_SEND_FAIL_PKT_NUM(1);
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 MUX_DlciUlQueProc(VOS_VOID)
{
    TTF_Q_ST                           *pRxDataQ;
    TTF_MBUF_ST                        *pMem;
    VOS_UINT32                          ulQueCnt = 0;
    VOS_UINT32                          ulQueLoop = 0;


    pRxDataQ    = MUX_GET_RX_Q_ADDR();

    ulQueCnt    = TTF_Q_CNT(pRxDataQ);

    MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_INFO,
        "MUX, MUX_DlciUlQueProc Qcnt:%d.\r\n", (VOS_INT32)ulQueCnt);

    for (ulQueLoop = 0; ulQueLoop < ulQueCnt; ulQueLoop++)
    {
        pMem     = (TTF_MBUF_ST *)TTF_QOut(PS_PID_APP_MUX, pRxDataQ);
        if (VOS_NULL_PTR == pMem)
        {
            MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_DlciUlQueProc, pMem is null\r\n");

            return VOS_ERR;
        }

        MUX_DlciUlDataToAt(pMem->pData);

        TTF_MbufFree(PS_PID_APP_MUX, pMem);
    }

    return VOS_OK;
}




VOS_UINT32 MUX_DlciUlDataEnque(TTF_MBUF_ST *pMem)
{
    TTF_Q_ST                           *pRxDataQ;
    VOS_UINT32                          ulRtn = VOS_ERR;


    MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_INFO,
                   "MUX, MUX_DlciUlDataEnque Start.\r\n");

    pRxDataQ    = MUX_GET_RX_Q_ADDR();
    ulRtn = TTF_QIn(PS_PID_APP_MUX, pRxDataQ, &pMem->stLink);
    if (VOS_OK != ulRtn)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                   "MUX, MUX_DlciUlEnque, TTF_QIn return fail.\r\n");

        TTF_MbufFree(PS_PID_APP_MUX, pMem);
        return VOS_ERR;
    }

    MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_INFO,
                   "MUX, MUX_DlciUlDataEnque End\r\n");
    return VOS_OK;
}




VOS_UINT32 MUX_DlciUlDataProc(VOS_UINT8* pData, VOS_UINT16 usDataLen)
{
    TTF_MBUF_ST                        *pMbuf           = VOS_NULL_PTR;
    VOS_UINT16                         *pusLeftInfoLen;
    VOS_UINT8                          *pucHeadBuff;
    VOS_UINT8                          *pucUnframeState;


    /*输入参数检查*/
    if ((VOS_NULL_PTR == pData) || (0 == usDataLen))
    {
         MUX_PrintLog2(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlDataProc, pData <1> is %d, usDataLen <2> is %d.\r\n", (VOS_INT32)pData, (VOS_INT32)usDataLen);
        return VOS_ERR;
    }

    pusLeftInfoLen  = MUX_GET_UL_RX_LEN();
    pucHeadBuff     = MUX_GET_UL_RX_HEAD();
    pucUnframeState = MUX_GET_UL_RX_STAT();

    while (usDataLen > 0)       /*处理收到的数据*/
    {
        switch (*pucUnframeState)
        {
            case MUX_DLCI_UNFRAME_STATE_FNDING_F9:
                if (MUX_FRAME_FLAG != *pData)
                {
                    MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                        "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_F9, *pData <1> is.\r\n", *pData);

                    pData++;
                    usDataLen--;
                    continue;
                }

                VOS_MemSet(pucHeadBuff, 0, MUX_FRAME_LEN_5);
                pucHeadBuff[MUX_FRAME_LEN_0] = *pData;
                pData++;
                usDataLen--;
                *pucUnframeState            = MUX_DLCI_UNFRAME_STATE_FNDING_ADDR;
                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_ADDR:
                if (MUX_FRAME_FLAG == *pData)
                {
                    MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                        "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_ADDR, *pData <1> is.\r\n", *pData);

                    pData++;
                    usDataLen--;
                    continue;
                }

                pucHeadBuff[MUX_FRAME_LEN_1] = *pData;
                pData++;
                usDataLen--;
                *pucUnframeState            = MUX_DLCI_UNFRAME_STATE_FNDING_CTRL;
                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_CTRL:
                pucHeadBuff[MUX_FRAME_LEN_2] = *pData;
                pData++;
                usDataLen--;
                *pucUnframeState            = MUX_DLCI_UNFRAME_STATE_FNDING_LEN1;
                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_LEN1:
                pucHeadBuff[MUX_FRAME_LEN_3] = *pData;
                pData++;
                usDataLen--;

                if (0x01 == (pucHeadBuff[MUX_FRAME_LEN_3] & 0x01))   /* 如果EA=1，长度域只有一个字节 */
                {
                    *pusLeftInfoLen     = pucHeadBuff[MUX_FRAME_LEN_3] >> 1;     /* 长度为前面7个比特 */

                    pMbuf           = MUX_GET_UL_RX_BUFF();

                    if (VOS_NULL_PTR != pMbuf)
                    {
                        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_LEN1, pMbuf <1> is.\r\n", (VOS_INT32)pMbuf);

                        TTF_MbufFree(PS_PID_APP_MUX, pMbuf);
                    }

                    pMbuf = TTF_MbufNew(PS_PID_APP_MUX, *pusLeftInfoLen + MUX_FRAME_LEN_6);

                    if (VOS_NULL_PTR == pMbuf)
                    {
                        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_LEN1, pMbuf is null.\r\n");

                        *pucUnframeState    = MUX_DLCI_UNFRAME_STATE_FNDING_F9;
                        break;
                    }

                    g_stMuxUnframeState.pUnframeBuf = pMbuf;
                    VOS_MemCpy(pMbuf->pData, pucHeadBuff, MUX_FRAME_LEN_4);
                    pMbuf->usLen    = ( *pusLeftInfoLen + MUX_FRAME_LEN_6 );
                    pMbuf->usUsed   = MUX_FRAME_LEN_4;
                    if (0 == *pusLeftInfoLen)
                    {
                        *pucUnframeState        = MUX_DLCI_UNFRAME_STATE_FNDING_FCS;
                    }
                    else
                    {
                        *pucUnframeState        = MUX_DLCI_UNFRAME_STATE_FNDING_INFO;
                    }
                }
                else
                {
                    *pucUnframeState        = MUX_DLCI_UNFRAME_STATE_FNDING_LEN2;
                }
                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_LEN2:
                pucHeadBuff[MUX_FRAME_LEN_4]   = *pData;
                pData++;
                usDataLen--;
                *pusLeftInfoLen  = ((VOS_UINT16)pucHeadBuff[MUX_FRAME_LEN_4]) << 7;
                *pusLeftInfoLen |= (VOS_UINT16)( pucHeadBuff[MUX_FRAME_LEN_3] >> 1 );

                if (MUX_DLCI_PAYLOAD_LEN_MAX < *pusLeftInfoLen)
                {
                    MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_LEN2, usLeftInfoLen is %d.\r\n", (VOS_INT32)*pusLeftInfoLen);

                    VOS_MemSet(pucHeadBuff, 0, MUX_FRAME_LEN_5);
                    *pucUnframeState        = MUX_DLCI_UNFRAME_STATE_FNDING_F9;
                }
                else
                {
                    pMbuf           = MUX_GET_UL_RX_BUFF();

                    if (VOS_NULL_PTR != pMbuf)
                    {
                        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_LEN2, pMbuf <1> is.\r\n", (VOS_INT32)pMbuf);
                        TTF_MbufFree(PS_PID_APP_MUX, pMbuf);
                    }

                    pMbuf = TTF_MbufNew(PS_PID_APP_MUX, *pusLeftInfoLen + MUX_FRAME_LEN_7);
                    if (VOS_NULL_PTR == pMbuf)
                    {
                        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_LEN2, pMbuf is null.\r\n");
                        *pucUnframeState    = MUX_DLCI_UNFRAME_STATE_FNDING_F9;
                        break;
                    }

                    g_stMuxUnframeState.pUnframeBuf = pMbuf;
                    VOS_MemCpy(pMbuf->pData, pucHeadBuff, MUX_FRAME_LEN_5);
                    pMbuf->usLen    = ( *pusLeftInfoLen + MUX_FRAME_LEN_7 );
                    pMbuf->usUsed   = MUX_FRAME_LEN_5;

                    *pucUnframeState        = MUX_DLCI_UNFRAME_STATE_FNDING_INFO;
                }
                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_INFO:
                pMbuf           = MUX_GET_UL_RX_BUFF();

                if (*pusLeftInfoLen <= usDataLen)
                {
                    VOS_MemCpy(&pMbuf->pData[pMbuf->usUsed], pData, *pusLeftInfoLen);
                    pMbuf->usUsed      += *pusLeftInfoLen;
                    pData              += *pusLeftInfoLen;
                    usDataLen          -= *pusLeftInfoLen;
                    *pusLeftInfoLen     = 0;
                    *pucUnframeState        = MUX_DLCI_UNFRAME_STATE_FNDING_FCS;
                }
                else
                {
                    VOS_MemCpy(&pMbuf->pData[pMbuf->usUsed], pData, usDataLen);
                    pMbuf->usUsed      += usDataLen;
                    pData              += usDataLen;
                    *pusLeftInfoLen    -= usDataLen;
                    usDataLen           = 0;
                }

                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_FCS:
                pMbuf           = MUX_GET_UL_RX_BUFF();
                pMbuf->pData[pMbuf->usUsed++]   = *pData;
                pData++;
                usDataLen--;
                *pucUnframeState            = MUX_DLCI_UNFRAME_STATE_FNDING_EOF;
                break;

            case MUX_DLCI_UNFRAME_STATE_FNDING_EOF:
                pMbuf           = MUX_GET_UL_RX_BUFF();
                if (MUX_FRAME_FLAG != *pData)
                {
                    MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::MUX_DLCI_UNFRAME_STATE_FNDING_EOF, *pData <1> is.\r\n", *pData);
                    TTF_MbufFree(PS_PID_APP_MUX, pMbuf);
                }
                else
                {
                    pMbuf->pData[pMbuf->usUsed++]   = *pData;

                    MUX_DlciUlDataEnque(pMbuf);
                }

                *pucUnframeState                = MUX_DLCI_UNFRAME_STATE_FNDING_F9;
                g_stMuxUnframeState.pUnframeBuf  = VOS_NULL_PTR;
                pData++;
                usDataLen--;
                break;

            default:
                pMbuf           = MUX_GET_UL_RX_BUFF();

                if (VOS_NULL_PTR != pMbuf)
                {
                    MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
                            "MUX, MUX_DlciUlDataProc::default, pMbuf <1> is.\r\n", (VOS_INT32)pMbuf);

                    TTF_MbufFree(PS_PID_APP_MUX, pMbuf);
                }

                *pucUnframeState            = MUX_DLCI_UNFRAME_STATE_FNDING_F9;
                break;
        }
    }
    return VOS_OK;
}



VOS_UINT32 MUX_DlciUlAcmGetDataBuf(UDI_HANDLE slUdiHsicAcmHdl, VOS_UINT8 **ppucBuf, VOS_UINT16 *usDataLen)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           lResult;

    stCtlParam.pVirAddr = VOS_NULL_PTR;
    stCtlParam.pPhyAddr = VOS_NULL_PTR;

    /* 获取底软上行数据buffer */
    lResult= mdrv_udi_ioctl(slUdiHsicAcmHdl, ACM_IOCTL_GET_RD_BUFF, &stCtlParam);
    if ( VOS_OK != lResult )
    {
        MUX_DBG_UL_CALLBACK_FAIL_NUM(1);
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlAcmGetDataBuf, WARNING, Get modem buffer failed code is %d!\r\n",
            lResult);
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == stCtlParam.pVirAddr)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlAcmGetDataBuf, WARNING, Data buffer is NULL!\r\n");
        return VOS_ERR;
    }

    *ppucBuf    = (VOS_UINT8 *)stCtlParam.pVirAddr;
    *usDataLen  = (VOS_UINT16)stCtlParam.u32Size;

    return VOS_OK;
}



VOS_UINT32 MUX_DlciUlUsbAcmReadData(VOS_UINT32 ulDeviceId)
{
    UDI_HANDLE                          slUdiHandle;
    VOS_UINT8                          *pucBuf;
    VOS_UINT16                          usDataLen;


    slUdiHandle = g_stMuxDevInfo.slUdiMuxAcmHdl;
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        MUX_DBG_GET_INVALID_UDI_HANDLE_NUM(1);
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlUsbAcmReadData, can not get the slUdiHandle,ulDeviceId <1>",
            (VOS_INT32)ulDeviceId);
        return VOS_ERR;
    }

    /* 底软现有接口，如果不取出数据会影响下一个数据的接收 */
    if (VOS_OK != MUX_DlciUlAcmGetDataBuf(slUdiHandle, &pucBuf, &usDataLen))
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlUsbAcmReadData, call Mux_AcmGetUlDataBuf return fail!\n");
        return VOS_ERR;
    }

    MUX_TraceUlData(ulDeviceId, pucBuf, usDataLen);

    MUX_DBG_UL_GET_SUCC_PKT_NUM(1);

    MUX_DlciUlDataProc(pucBuf, usDataLen);

    MUX_DlciUlQueProc();

    /* 数据完毕，释放上行缓存 */
    if (VOS_OK != MUX_DlciUlHsicFreeDataBuf(slUdiHandle, pucBuf, usDataLen))
    {
         MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlUsbAcmReadData, call MUX_DlciUlHsicFreeDataBuf return fail!\n");

         return VOS_ERR;
    }

    MUX_DBG_UL_SEND_SUCC_PKT_NUM(1);

    return VOS_OK;
}



VOS_UINT32 MUX_DlciUlUsbAcmDataRecv( VOS_VOID)
{
    MUX_DlciUlUsbAcmReadData(UDI_ACM_HSIC_ACM14_ID);


    return VOS_OK;
}



VOS_UINT32 MUX_DlciUlHsicFreeDataBuf(
    UDI_HANDLE                          ulUdiHdl,
    VOS_UINT8                          *pucBuf,
    VOS_UINT16                          usLen
)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           lResult;


    /* 填写需要释放的内存指针 */
    stCtlParam.pVirAddr = (VOS_CHAR*)pucBuf;
    stCtlParam.pPhyAddr = VOS_NULL_PTR;
    stCtlParam.u32Size  = usLen;
    stCtlParam.pDrvPriv = VOS_NULL_PTR;

    lResult = mdrv_udi_ioctl(ulUdiHdl, ACM_IOCTL_RETURN_BUFF, &stCtlParam);
    if ( VOS_OK != lResult )
    {
        MUX_DBG_UL_CALLBACK_FAIL_NUM(1);
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciUlHsicFreeDataBuf, call mdrv_udi_ioctl return fail!\n",
                  lResult);

        return VOS_ERR;
    }


    return VOS_OK;
}



VOS_UINT32 MUX_DlciDlUsbAcmFreeDataCB(VOS_UINT8 *pucBuf)
{
    BSP_FREE(pucBuf);

    MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_INFO,
        "MUX, MUX_DlciDlUsbAcmFreeDataCB success!\r\n");

    MUX_DBG_DL_FREE_PKT_NUM(1);

    return VOS_OK;
}



VOS_UINT32 MUX_DlciDlUsbAcmWriteData(UDI_HANDLE slUdiHandle, VOS_UINT8 *pucBuf, VOS_UINT16 usDataLen)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           ulResult;


    /* 待写入数据内存地址 */
    stCtlParam.pVirAddr                 = (VOS_CHAR*)pucBuf;
    stCtlParam.pPhyAddr                 = VOS_NULL_PTR;
    stCtlParam.u32Size                  = usDataLen;
    stCtlParam.pDrvPriv                 = VOS_NULL_PTR;

    /* 异步方式写数，*/
    ulResult = mdrv_udi_ioctl(slUdiHandle, ACM_IOCTL_WRITE_ASYNC, &stCtlParam);
    if ( VOS_OK != ulResult )
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX_DlciDlUsbAcmWriteData, Error, Write data failed with code <1>!\r\n",
            ulResult);

        return VOS_ERR;
    }


    return VOS_OK;
}



VOS_UINT8  *MUX_DlciAllocPayloadMem(VOS_UINT16 usDataLen)
{
    VOS_UINT8                          *pucMuxDlSendBuf;

    if (MUX_DLCI_PAYLOAD_LEN_MAX < usDataLen)
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX_DlciAllocPayloadMem, Error, ulDataLen  <1> is error!\r\n",
            usDataLen);

        return VOS_NULL_PTR;
    }

    /*MUX UIH帧头部为4或5个字节，尾部为2两个字节，共7个字节，预先申请内存空间，可以让MUX直接使用该内存组帧 */
    pucMuxDlSendBuf = (VOS_UINT8 *)BSP_MALLOC((VOS_UINT32)(usDataLen + MUX_FRAME_LEN_7), MEM_NORM_DDR_POOL);
    if (VOS_NULL_PTR == pucMuxDlSendBuf)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_DlciAllocPayloadMem, Error, g_pucMuxDlSendBuf  is null!\r\n");

        return VOS_NULL_PTR;
    }

    return pucMuxDlSendBuf;
}



VOS_UINT32 MUX_DlciDlDataProc (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pucSendBuf,
    VOS_UINT16 *pusSendDataLen, VOS_UINT8* pucBuf, VOS_UINT16 usDataLen)
{
    VOS_UINT16                          usFcsLen;
    VOS_UINT8                           ucDlci;
    VOS_UINT8                           ucFcs;

    ucDlci      = (VOS_UINT8)enDlci;

    /*填写帧的长度域*/
    if (MUX_FRAME_LEN_128 > usDataLen)/*如果为长度域为7位,头部是4个字节*/
    {
        pucSendBuf[MUX_FRAME_LEN_0]   = MUX_FRAME_FLAG;
        pucSendBuf[MUX_FRAME_LEN_1]   = MUX_SET_116_BIT(1, 1, ucDlci); /*地址域包含DLCI*/
        pucSendBuf[MUX_FRAME_LEN_2]   = MUX_CONTROL_UIH;  /*控制域内容为帧类型,如UIH,SABM,UA等*/
        pucSendBuf[MUX_FRAME_LEN_3]   = (VOS_UINT8)(0x01 | (usDataLen << 1));
        usFcsLen        = MUX_FRAME_LEN_3;

        *pusSendDataLen = usDataLen + MUX_FRAME_LEN_6;

        /*拷贝AT模块过来的下行原始数据 */
        VOS_MemCpy(&pucSendBuf[MUX_FRAME_LEN_4], pucBuf, usDataLen);
    }
    else             /*如果为长度域为15位，头部是5个字节*/
    {
        pucSendBuf[MUX_FRAME_LEN_0]    = MUX_FRAME_FLAG;
        pucSendBuf[MUX_FRAME_LEN_1]    = MUX_SET_116_BIT(1, 1, ucDlci); /*地址域包含DLCI*/
        pucSendBuf[MUX_FRAME_LEN_2]    = MUX_CONTROL_UIH;  /*控制域内容为帧类型,如UIH,SABM,UA等*/
        pucSendBuf[MUX_FRAME_LEN_3]    = (VOS_UINT8)(((0x7F & usDataLen) << 1) & 0xFE) ;
        pucSendBuf[MUX_FRAME_LEN_4]    = (VOS_UINT8)(usDataLen >> 7);
        usFcsLen        = MUX_FRAME_LEN_4;

        *pusSendDataLen = usDataLen + MUX_FRAME_LEN_7;

          /*拷贝AT模块过来的下行原始数据 */
        VOS_MemCpy(&pucSendBuf[MUX_FRAME_LEN_5], pucBuf, usDataLen);
    }

    ucFcs   = MUX_DlciGetFcs(&pucSendBuf[MUX_FRAME_LEN_1], usFcsLen); /*产生FCS字节*/

    pucSendBuf[(*pusSendDataLen - MUX_FRAME_LEN_2)] = ucFcs;

    pucSendBuf[(*pusSendDataLen - MUX_FRAME_LEN_1)] = MUX_FRAME_FLAG;

    return VOS_OK;
}



VOS_UINT32 MUX_DlciDlDataSend (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pData, VOS_UINT16 usDataLen)
{
    UDI_HANDLE                          slUdiHandle;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usSendDataLen   = 0;
    VOS_UINT8                          *pucSendDataBuf;


    if (VOS_NULL_PTR == pData)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciDlDataSend, pData is null.\r\n");
        MUX_DBG_DL_SEND_FAIL_PKT_NUM(1);

        return VOS_ERR;
    }

    MUX_TraceDlData(enDlci, pData, usDataLen);

    slUdiHandle = g_stMuxDevInfo.slUdiMuxAcmHdl;
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciDlDataSend, slUdiHandle is invalid.\r\n");

        MUX_DBG_GET_INVALID_UDI_HANDLE_NUM(1);
        MUX_DBG_DL_SEND_FAIL_PKT_NUM(1);

        /*原始数据是AT模块的全局变量，故不释放下行原始数据内存*/

        return VOS_ERR;
    }

    pucSendDataBuf = MUX_DlciAllocPayloadMem(usDataLen);
    if (VOS_NULL_PTR == pucSendDataBuf)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_DlciDlDataSend, pucSendDataBuf is null.\r\n");
        MUX_DBG_DL_SEND_FAIL_PKT_NUM(1);

        /*原始数据是AT模块的全局变量，故不释放下行原始数据内存*/

        return VOS_ERR;
    }

    MUX_DlciDlDataProc(enDlci, pucSendDataBuf, &usSendDataLen, pData, usDataLen);

    MUX_TraceDlData(enDlci, pucSendDataBuf, usSendDataLen);

    /*向底软发送下行数据*/
    ulRslt = MUX_DlciDlUsbAcmWriteData(slUdiHandle, pucSendDataBuf, usSendDataLen);
    if (VOS_OK != ulRslt)
    {
        MUX_DBG_DL_SEND_FAIL_PKT_NUM(1);
        /*释放数据内存*/
        MUX_DlciDlUsbAcmFreeDataCB(pucSendDataBuf);

        return VOS_ERR;
    }

    MUX_DBG_DL_SEND_SUCC_PKT_NUM(1);


    return VOS_OK;
}



VOS_UINT32 MUX_AtRgstUlPortCallBack (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, RCV_UL_DLCI_DATA_FUNC pFunc)
{
    MUX_AT_UL_DLCI_INFO_STRU               *pstMuxAtUlDlciInfo;

    /* Dlci合法性检查 */
    if (VOS_OK != MUX_DlciIsValid(enDlci))
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING, "MUX, MUX_AtRgstUlPortCallBack: enDlci <1> is.\r\n", enDlci);
        return VOS_ERR;
    }

    pstMuxAtUlDlciInfo = MUX_AT_UL_GET_DLCI_INFO_PTR(enDlci);

    /* 设置ADS下行数据回调内容 */
    pstMuxAtUlDlciInfo->enDlci              = enDlci;
    pstMuxAtUlDlciInfo->pRcvUlDlciDataFunc  = pFunc;

    return VOS_OK;
}



VOS_UINT32 MUX_AtMsgProc( const MsgBlock *pMsgBlock )
{
    return VOS_OK;
}



VOS_UINT32 MUX_OpenDevice(MUX_DEV_INFO_STRU *pstDevInfo)
{
    UDI_OPEN_PARAM_S                      stParam;


    stParam.devid   = pstDevInfo->enUdiDevId;
    pstDevInfo->slUdiMuxAcmHdl = mdrv_udi_open(&stParam);

    if (UDI_INVAL_DEV_ID == pstDevInfo->slUdiMuxAcmHdl)
    {
        MUX_DBG_GET_INVALID_UDI_HANDLE_NUM(1);
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_OpenDevice, Call mdrv_udi_open return UDI_INVAL_DEV_ID.\n");
        return VOS_ERR;
    }

    /* 注册HSIC ACM 用户面通道上行数据接收回调 */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiMuxAcmHdl, ACM_IOCTL_SET_READ_CB, pstDevInfo->pMuxAcmUlRxFunc))
    {
        MUX_DBG_UL_CALLBACK_FAIL_NUM(1);
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_OpenDevice, ERROR, Set HSIC ACM data read callback failed!\n");
        return VOS_ERR;
    }

    /* 注册HSIC ACM 用户面通道下行数据内存释放接口 */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiMuxAcmHdl, ACM_IOCTL_SET_FREE_CB, MUX_DlciDlUsbAcmFreeDataCB))
    {
        MUX_DBG_UL_CALLBACK_FAIL_NUM(1);
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_OpenDevice, ERROR, Set HSIC ACM memory free callback failed!\n");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 MUX_PortInit( VOS_VOID )
{
    BSP_MODULE_SUPPORT_E    enSupport;

    enSupport   = mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC);

    /* 产品不支持HSIC特性，直接初始化成功 */
    if (BSP_MODULE_SUPPORT != enSupport)
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_PortInit, Hsic not support <1>.\r\n", enSupport);

        return VOS_OK;
    }

    /* 初始化MUX通道信息 */
    g_stMuxDevInfo.enUdiDevId           = UDI_ACM_HSIC_ACM14_ID;
    g_stMuxDevInfo.pMuxAcmUlRxFunc      = MUX_DlciUlUsbAcmDataRecv;
    g_stMuxDevInfo.slUdiMuxAcmHdl       = UDI_INVAL_DEV_ID;

    if (VOS_OK != MUX_OpenDevice(&g_stMuxDevInfo))
    {
        MUX_PrintLog1(PS_PID_APP_MUX, 0, PS_PRINT_WARNING,
            "MUX, MUX_PortInit, Open Device <1> fail.\n", (VOS_INT32)g_stMuxDevInfo.enUdiDevId);
        return VOS_ERR;
    }


    return VOS_OK;
}



VOS_UINT32 MUX_Init( VOS_VOID )
{
    VOS_UINT8                           ucMuxSupportFlg;
    VOS_UINT32                          ulDlciLoop;


    ucMuxSupportFlg = VOS_FALSE;

    /* 读NV失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Mux_Support_Flg, &ucMuxSupportFlg, sizeof(VOS_UINT8)))
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_Init, read mux nv fail.\r\n");
        return VOS_ERR;
    }

    /* MUX特性不支持，直接返回 */
    if (VOS_TRUE != ucMuxSupportFlg)
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_ERROR,
            "MUX, MUX_Init, mux not support.\r\n");
        return VOS_ERR;
    }

    /* 初始化上行链路号信息 */
    for (ulDlciLoop = 0; ulDlciLoop < AT_MUX_DLCI_TYPE_BUTT; ulDlciLoop++)
    {
        g_stMuxAtUlDlciInfo[ulDlciLoop].enDlci              = AT_MUX_DLCI_TYPE_BUTT;
        g_stMuxAtUlDlciInfo[ulDlciLoop].pRcvUlDlciDataFunc  = VOS_NULL_PTR;
    }

    VOS_MemSet(&g_stMuxUnframeState, 0, sizeof(MUX_UNFRAME_STATE_ST));

    /* 初始化上行队列 */
    TTF_QInit(PS_PID_APP_MUX, &g_stMuxUlQue);

    /* 如果HSIC通道已经枚举成功，则由协议栈执行初始化操作；否则将初始化函数注册至底软，
        由底软在HSIC枚举成功后调用以进行初始化*/
    if (VOS_TRUE == DRV_GET_HSIC_ENUM_STATUS())
    {
        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_INFO,
            "MUX, MUX_Init, Hsic enum success.\r\n");

        MUX_PortInit();
    }
    else
    {
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)MUX_PortInit);

        MUX_PrintLog(PS_PID_APP_MUX, 0, PS_PRINT_INFO,
            "MUX, MUX_Init, Hsic enum fail.\r\n");
    }

    MUX_StaticInfoInit();

    return VOS_OK;
}



VOS_UINT32 MUX_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            MUX_Init();
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
            break;
        default:
            break;
    }

    return VOS_OK;
}



VOS_VOID MUX_TraceUlData(VOS_UINT32 ulDeviceId, VOS_UINT8 *pucBuf, VOS_UINT16 usLen)
{
    VOS_UINT16                          usLoop  = 0;


    if (PS_TRUE != g_ulMuxTraceFlag)
    {
        return;
    }

    vos_printf("MUX_TraceUlData::ulDeviceId:%d, UL DataLen:%d, UL Data Start:\r\n", ulDeviceId, usLen);

    for (usLoop = 0; usLoop < usLen; usLoop++)
    {
        vos_printf("%x ", *(pucBuf + usLoop));
    }
    vos_printf(" End.\r\n");

    return;
}



VOS_VOID MUX_TraceDlData(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8 *pData, VOS_UINT16 usDataLen)
{
    VOS_UINT16                          usLoop  = 0;


    if (PS_TRUE != g_ulMuxTraceFlag)
    {
        return;
    }

    vos_printf("MUX_TraceDlData::enDlci:%d,DL DataLen:%d, DL Data Start:\r\n", enDlci, usDataLen);

    for (usLoop = 0; usLoop < usDataLen; usLoop++)
    {
        vos_printf("%x ", pData[usLoop]);
    }
    vos_printf(" End.\r\n");

    return;
}



VOS_VOID MUX_StaticInfoInit( VOS_VOID )
{
    PS_MEM_SET(&g_stMuxStaticInfo, 0, sizeof(MUX_DEV_STATIC_INFO_STRU));


    return;
}



VOS_VOID MUX_ShowStat( VOS_VOID )
{

    vos_printf("===========MUX_ShowStat============");

    vos_printf("MUX Dev Static Info.\r\n");
    vos_printf("MUX Invalid Udi Handle Num = %d.\r\n", g_stMuxStaticInfo.ulInvalidUdiHandleNums);
    vos_printf("MUX Ul Callback Fail Num = %d.\r\n",  g_stMuxStaticInfo.ulGetDataFailNums);
    vos_printf("MUX Ul Discard PakcetNum = %u\r\n",  g_stMuxStaticInfo.ulDiscardUlPacketNums);
    vos_printf("MUX Ul Succ Get PakcetNum = %u\r\n", g_stMuxStaticInfo.ulSuccGetUlPacketNums);
    vos_printf("MUX Ul FailSend PakcetNum = %u\r\n", g_stMuxStaticInfo.ulFailSendUlPacketNums);
    vos_printf("MUX Ul SuccSend PakcetNum = %u\r\n", g_stMuxStaticInfo.ulSuccSendUlPacketNums);
    vos_printf("MUX Dl FailSend PakcetNum = %u\r\n", g_stMuxStaticInfo.ulFailSendDlPacketNums);
    vos_printf("MUX Dl SuccSend PakcetNum = %u\r\n", g_stMuxStaticInfo.ulSuccSendDlPacketNums);
    vos_printf("MUX Dl Free PakcetNum = %u\r\n", g_stMuxStaticInfo.ulFreeDlPacketNums);
    vos_printf("\r\n");


    return;
}



VOS_VOID MUX_SetTraceFlag( VOS_UINT32  ulFlag )
{
    g_ulMuxTraceFlag   = ulFlag;

    return;
}



VOS_VOID MUX_SetLogFlag( VOS_UINT32  ulFlag )
{
    g_ulMuxPrintFlag   = ulFlag;

    return;
}

#else   /* for feature */

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtMuxInterface.h"

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32 MUX_DlciDlDataSend (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pData, VOS_UINT16 usDataLen)
{
    return VOS_OK;
}


VOS_UINT32 MUX_AtRgstUlPortCallBack (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, RCV_UL_DLCI_DATA_FUNC pFunc)
{
    return VOS_OK;
}


VOS_UINT32 MUX_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip )
{
    return VOS_OK;
}


VOS_UINT32 MUX_AtMsgProc( const MsgBlock *pMsgBlock )
{
    return VOS_OK;
}


#endif  /* end for feature */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
