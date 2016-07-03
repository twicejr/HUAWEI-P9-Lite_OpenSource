



/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "CbtCpm.h"
#include "cpm.h"
#include "SCMSoftDecode.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_CPM_C
/*lint +e767 */

/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
CBTCPM_RCV_FUNC                g_pCbtRcvFunc = VOS_NULL_PTR;
CBTCPM_SEND_FUNC               g_pCbtSndFunc = VOS_NULL_PTR;

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

/*****************************************************************************
  4 函数实现
*****************************************************************************/


VOS_VOID CBTCPM_PortRcvReg(CBTCPM_RCV_FUNC pRcvFunc)
{
    g_pCbtRcvFunc = pRcvFunc;

    return;
}


VOS_VOID CBTCPM_PortSndReg(CBTCPM_SEND_FUNC pSndFunc)
{
    g_pCbtSndFunc = pSndFunc;

    return;
}


CBTCPM_RCV_FUNC CBTCPM_GetRcvFunc(VOS_VOID)
{
    return g_pCbtRcvFunc;
}


CBTCPM_SEND_FUNC CBTCPM_GetSndFunc(VOS_VOID)
{
    return g_pCbtSndFunc;
}


VOS_UINT32 CBTCPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort)
{
    /* NAS走UART口做校准 */
    if (CPM_IND_PORT > enPhyPort)
    {
        /* 从AT获得发送数据的函数指针 */
        CBTCPM_PortSndReg(AT_QuerySndFunc(enPhyPort));

        /* 用AT的端口做校准，不从USB或VCOM上收数据 */
        CBTCPM_PortRcvReg(VOS_NULL_PTR);

        /* 将校准通道的接收函数给AT模块 */
        AT_RcvFuncReg(enPhyPort, CBTSCM_SoftDecodeDataRcv);

        return VOS_OK;
    }

    return VOS_ERR;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




