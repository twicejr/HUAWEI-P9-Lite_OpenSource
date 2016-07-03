


/*****************************************************************************
  1 头文件包含
**************************************************************************** */
//#include "AtAppVcomInterface.h"
#include "OmVcomPpm.h"
#include "cpm.h"
#include "dms.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_VCOM_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
/* 用于记录 VCOM 通道发送的统计信息 */
OM_VCOM_DEBUG_INFO                      g_stVComDebugInfo[3];

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/


/*****************************************************************************
  4 函数实现
*****************************************************************************/




VOS_UINT32 PPM_VComCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendNum++;
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendLen += ulDataLen;

    if (VOS_OK != DMS_WriteOmData(DMS_VCOM_OM_CHAN_CTRL, pucVirAddr, ulDataLen))
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrNum++;
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrLen += ulDataLen;

        return CPM_SEND_ERR;
    }

    return CPM_SEND_OK;
}

VOS_VOID PPM_VComEvtCB(VOS_UINT32 ulChan, VOS_UINT32 ulEvent)
{
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    VOS_BOOL                            ulSndMsg;


    if(ulChan == DMS_VCOM_OM_CHAN_CTRL)
    {
        enChannel = OM_LOGIC_CHANNEL_CNF;
    }
    else if(ulChan == DMS_VCOM_OM_CHAN_DATA)
    {
        enChannel = OM_LOGIC_CHANNEL_IND;
    }
    else
    {
        vos_printf("[%s] Error channel NO %d\n",__FUNCTION__,ulChan);
        return;
    }

    /*打开操作直接返回*/
    if(ulEvent == DMS_CHAN_EVT_OPEN)
    {
        return;
    }
    else if(ulEvent == DMS_CHAN_EVT_CLOSE)
    {
        ulSndMsg  = VOS_FALSE;

        if((CPM_VCOM_CFG_PORT == CPM_QueryPhyPort(CPM_OM_CFG_COMM)) &&
           (CPM_VCOM_IND_PORT == CPM_QueryPhyPort(CPM_OM_IND_COMM)))
        {
            ulSndMsg = TRUE;
        }
        if(ulSndMsg == TRUE)
        {
            PPM_DisconnectAllPort(enChannel);
        }
    }
    else
    {
        vos_printf("[%s] Error Event State %d\n",__FUNCTION__,ulEvent);
    }

    return;
}


VOS_UINT32 PPM_VComCfgReadData(VOS_UINT32 ulDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength)
{
    if (ulDevIndex != DMS_VCOM_OM_CHAN_CTRL)
    {
        vos_printf("\r\n PPM_VComCfgReadData:PhyPort port is error: %d\n", ulDevIndex);

        return VOS_ERR;
    }

    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvNum++;
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvLen += uslength;

    if ((VOS_NULL_PTR == pData) || (0 == uslength))
    {
        vos_printf("\r\n PPM_VComCfgReadData:Send data is NULL\n");

        return VOS_ERR;
    }

#if 0
    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE((VOS_UINT8*)pData, uslength, OM_ACPU_VCOM_CB);
    /*lint +e40*/
#endif

    if(VOS_OK != CPM_ComRcv(CPM_VCOM_CFG_PORT, pData, uslength))
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrNum++;
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrLen += uslength;

        vos_printf("\r\n Info: PPM_VComCfgReadData:Call CPM_ComRcv is fail, PhyPort is CPM_VCOM_IND_PORT \n");
    }

    return VOS_OK;
}


VOS_UINT32 PPM_VComIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_UINT32          ulInSlice;
    VOS_UINT32          ulOutSlice;
    VOS_UINT32          ulWriteSlice;
    VOS_UINT32          ret;
    
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendNum++;
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendLen += ulDataLen;

    ulInSlice = mdrv_timer_get_normal_timestamp();

    ret = DMS_WriteOmData(DMS_VCOM_OM_CHAN_DATA, pucVirAddr, ulDataLen);

    ulOutSlice = mdrv_timer_get_normal_timestamp();

    ulWriteSlice = (ulInSlice > ulOutSlice) ? (ulInSlice - ulOutSlice) : (ulOutSlice - ulInSlice);

    if(ulWriteSlice > g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulMaxTimeLen)
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulMaxTimeLen = ulWriteSlice;
    }
    
    if (VOS_OK != ret)
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrNum++;
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrLen += ulDataLen;

        return CPM_SEND_ERR;
    }

    return CPM_SEND_OK;
}


OM_VCOM_DEBUG_INFO *PPM_VComGetIndInfo(VOS_VOID)
{
    return &g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND];
}



VOS_VOID PPM_VComCfgPortInit(VOS_VOID)
{
    /* 配置数据走VCOM28，会有数据下发 */
    DMS_RegOmChanDataReadCB(DMS_VCOM_OM_CHAN_CTRL, PPM_VComCfgReadData);
    /*CTRL口事件回调*/
    DMS_RegOmChanEventCB(DMS_VCOM_OM_CHAN_CTRL, PPM_VComEvtCB);

    CPM_PhySendReg(CPM_VCOM_CFG_PORT, PPM_VComCfgSendData);

    return;
}


VOS_VOID PPM_VComIndPortInit(VOS_VOID)
{
    /* 可维可测数据数据上报走VCOM31，不会有数据下发 */
    DMS_RegOmChanDataReadCB(DMS_VCOM_OM_CHAN_DATA, VOS_NULL_PTR);
    /*DATA口事件回调*/
    DMS_RegOmChanEventCB(DMS_VCOM_OM_CHAN_DATA, PPM_VComEvtCB);

    CPM_PhySendReg(CPM_VCOM_IND_PORT, PPM_VComIndSendData);

    return;
}


VOS_VOID PPM_VComPortInit(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stVComDebugInfo[0], 0, sizeof(g_stVComDebugInfo));
    /*lint +e534*/

    /* Vcom 口OM IND通道的初始化 */
    PPM_VComIndPortInit();

    /* Vcom 口OM CNF通道的初始化 */
    PPM_VComCfgPortInit();

    /* Vcom 口errorlog通道的初始化 */
    GU_OamErrLogVComPortInit();

    return;
}


VOS_VOID PPM_VComInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nVCom30 Send num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendNum);
    vos_printf("\r\nVCom30 Send Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendLen);

    vos_printf("\r\nVCom30 Send Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendErrNum);
    vos_printf("\r\nVCom30 Send Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendErrLen);

    vos_printf("\r\nVCom30 receive num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvNum);
    vos_printf("\r\nVCom30 receive Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvLen);

    vos_printf("\r\nVCom30 receive Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvErrNum);
    vos_printf("\r\nVCom30 receive Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvErrLen);



    vos_printf("\r\nVCom28 Send num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendNum);
    vos_printf("\r\nVCom28 Send Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendLen);

    vos_printf("\r\nVCom28 Send Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrNum);
    vos_printf("\r\nVCom28 Send Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrLen);

    vos_printf("\r\nVCom28 receive num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvNum);
    vos_printf("\r\nVCom28 receive Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvLen);

    vos_printf("\r\nVCom28 receive Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrNum);
    vos_printf("\r\nVCom28 receive Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrLen);



    vos_printf("\r\nVCom31 Send num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendNum);
    vos_printf("\r\nVCom31 Send Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendLen);

    vos_printf("\r\nVCom31 Send Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrNum);
    vos_printf("\r\nVCom31 Send Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrLen);

    vos_printf("\r\nVCom31 receive num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvNum);
    vos_printf("\r\nVCom31 receive Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvLen);

    vos_printf("\r\nVCom31 receive Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvErrNum);
    vos_printf("\r\nVCom31 receive Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvErrLen);
    /*lint +e534*/

    return;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




