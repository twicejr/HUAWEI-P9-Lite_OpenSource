



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "CssTest.h"

#define    THIS_FILE_ID            PS_FILE_ID_CSSTEST_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : CSS_CmdHelp
 Description     : CSS帮助命令
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181  Draft Enact

*****************************************************************************/
VOS_VOID  CSS_CmdHelp( VOS_VOID )
{
    (VOS_VOID)vos_printf("\r\n");
    (VOS_VOID)vos_printf("********************** CSS 软调命令列表 *********************\r\n");
    (VOS_VOID)vos_printf("%-30s : CSS状态信息\r\n","Css_ShowCurState");
    (VOS_VOID)vos_printf("%-30s : 本地保存的扫频信息\r\n","Css_ShowBandScanResult");
    (VOS_VOID)vos_printf("*********************************************************************\r\n");
    (VOS_VOID)vos_printf("\r\n");
}

/*****************************************************************************
 Function Name   : Css_ShowCurState
 Description     : 读取当前状态
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen　00209181    2015-05-28  Draft Enact

*****************************************************************************/
VOS_VOID Css_ShowCurState(VOS_VOID)
{
    (VOS_VOID)vos_printf("CSS CURRENT MAIN STATE = %d\n", CSS_GetCurMainStatus());
    (VOS_VOID)vos_printf("CSS CURRENT SUN STATE = %d\n", CSS_GetCurSubStatus());
}

/*****************************************************************************
 Function Name   : Css_ShowBandScanResult
 Description     : 读取本地保存的扫频结果信息
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen　00209181    2015-05-28  Draft Enact

*****************************************************************************/
VOS_VOID Css_ShowBandScanResult(VOS_VOID)
{
    VOS_UINT8                             ucBandNodeNum = 0;
    VOS_UINT8                             i;
    CSS_COMM_SCAN_BAND_NODE_STRU         *pBandNode;

    pBandNode   = CSS_GetCommScanBandListHeadNode();

    /* 打印结果 */
    while ((CSS_NULL_PTR != pBandNode) && (ucBandNodeNum < CSS_GetCommScanBandListAddr()->ucBandCount))
    {
        (VOS_VOID)vos_printf("Css_ShowBandScanResult ucBandInd = %d\n", pBandNode->stBandInfo.ucBandInd);
        (VOS_VOID)vos_printf("Css_ShowBandScanResult usFreqNum = %d\n", pBandNode->stBandInfo.ucScanRsltArrayCount);

        for (i = 0; i < pBandNode->stBandInfo.ucScanRsltArrayCount; i++)
        {
            (VOS_VOID)vos_printf("Css_ShowBandScanResult usCentralFreq = %d , rssi = %d\n",
                                pBandNode->stBandInfo.pstScanRsltArray[i].usCentralFreq,
                                pBandNode->stBandInfo.pstScanRsltArray[i].sRssi);
        }

        (VOS_VOID)vos_printf("Css_ShowBandScanResult bitOpLteSupport = %d\n", pBandNode->stBandInfo.bitOpLteSupport);
        (VOS_VOID)vos_printf("Css_ShowBandScanResult bitOpGsmSupport = %d\n", pBandNode->stBandInfo.bitOpGsmSupport);
        (VOS_VOID)vos_printf("Css_ShowBandScanResult bitOpWcdmaSupport = %d\n", pBandNode->stBandInfo.bitOpWcdmaSupport);


    }

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


