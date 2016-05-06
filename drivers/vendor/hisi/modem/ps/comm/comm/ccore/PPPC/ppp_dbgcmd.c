
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_DBGCMD_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

#if 1
VOS_UINT32 ToLowerString ( CHAR * szSource, CHAR * szDest )
{
    VOS_UINT32 ulTmp;
    VOS_UINT32 ulLen = 0;

    ulLen = VOS_StrLen ( szSource );
    for (ulTmp = 0; ulTmp < ulLen; ulTmp++)
    {
        if (VOS_iscntrl( szSource[ ulTmp ] ))
        {
            szDest[ ulTmp ] = '\0';
            return VOS_OK;
        }

        if (VOS_isalpha( szSource[ ulTmp ] ))
        {
            szDest[ ulTmp ] = VOS_CharToLower( szSource[ ulTmp ] );
        }
        else
        {
            szDest[ ulTmp ] = szSource[ ulTmp ];
        }
    }

    szDest[ ulTmp ] = '\0';

    return VOS_OK;
}
#endif


VOS_VOID PPPC_Help(VOS_VOID)
{
    vos_printf("********************PPPC软调信息************************\n");
    vos_printf("PPP_DbgShowErrStatisc                     显示PPPC错误统计信息\n");
    vos_printf("PPP_DbgShowOkStatisc                      显示PPPC正常统计信息\n");
    vos_printf("PPP_DbgShowCnt                            显示PPPC信息\n");
    vos_printf("PPPC_ShowDLProcStats                      显示PPPC下行统计信息\n");
    vos_printf("PPPC_ShowULProcStats                      显示PPPC上行统计信息\n");
    vos_printf("\n");
    return;
}

VOID PPP_DebugCbgCntProc( VOS_UINT32 argc, CHAR *argv[] )
{
    LONG lReturn = 0;

    if ( 0 == argc )
    {
        return;
    }

    lReturn = VOS_MemCmp("clear", argv[0], 5);
    if ( 0 == lReturn )
    {
        PPP_ClearCnt();
        vos_printf("\r\n PPP dbgcnt has been cleared!!");
        return;
    }

    lReturn = VOS_MemCmp("show", argv[0], 4);
    if ( 0 == lReturn )
    {
        PPP_DbgShowCnt();
        return;
    }

    return;
}

/*PPP模块注册的调试配置命令*/
/*WGGSN_B03_L2TP_PPPC*/
struct Command_S PppCommand[] =
{
 #ifndef __STARTUP_LOAD_MODE__/* 启动下载 */
 /* 安全红线下屏蔽的调试命令 */
#ifdef __SPU_DEBUG_VER__
    /* { "debug",      "show debug message from ppp.",
        NULL, SRPppShowDebug }, */
    { "perfvar",    "show performance var.",
        NULL, PPP_PrintPerfVar },
    { "compress",  "config compress.",
    NULL,         SRPppCfgCompress
    },
    {"set",    "set ppp info", NULL, PPP_DebugSetPPPInfo},
#endif
     /* { "cbdetail",   "show control block detail message.",
         NULL, SRPppShowCBDetailInfo }, */
     /* { "cbinfo",     "show control block message.",
         NULL, SRPppShowCBInfo }, */
     /* { "show",       "show control block message.",
        NULL, SRPppShowInfo },*//*added by hyj for b02*/
     {"dbgcnt", "show or clear the counter",
        NULL, PPP_DebugCbgCntProc},
 #endif

};

struct Command_Group_S PppCommandGroup =
{
 #ifndef __STARTUP_LOAD_MODE__/* 启动下载 */
    sizeof (PppCommand) / sizeof (PppCommand [0]),
    11,
    PppCommand
 #endif

};

/*Begin WGGSN_B03_L2TP_PPPC_COMP*/
VOID SRPppCfgCompress( VOS_UINT32 argc, CHAR * argv []   )
{
    VOS_UINT32 ulDmpuId = 0, ulDpeId = 0;

    if (((argc >= 1) && !VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
        vos_printf ( "\r\ncConfig PPP compress.");
        vos_printf ( "\r\nUsage: ppp compress {mppc|stac|vj} {0|1}");/* Modified by liutao 38563 at 2004-10-30 R002 for PPP压缩调试 */
        return;
    }

    if (argc == 0)
    {
        if (g_ucPppVjSwitch)
        {
            vos_printf("\r\nvj = yes");
        }
        else
        {
            vos_printf("\r\nvj = no");
        }

        if (g_ucPppCcpSwitch)
        {
            if (g_ucPppCcpType & M_PPPCOMPRESS_MPPC_FLAG)
            {
                vos_printf("\r\nmppc = yes");
            }
            else
            {
                vos_printf("\r\nmppc = no");
            }

            if (g_ucPppCcpType & M_PPPCOMPRESS_STAC_FLAG)
            {
                vos_printf("\r\nstac = yes");
            }
            else
            {
                vos_printf("\r\nstac = no");
            }
        }
        else
        {
            vos_printf("\r\nmppc = no");
            vos_printf("\r\nstac = no");
        }

        vos_printf("\r\nPppVjUserNum:");
        for ( ulDmpuId = 0; ulDmpuId < MAX_DMPU_NUM; ulDmpuId++)
        {
            for ( ulDpeId = 0; ulDpeId < 14; ulDpeId++)
            {
                vos_printf("\r\nDMPU[%2lu]DPE[%2lu] = %d",
                    ulDmpuId, ulDpeId, g_usPppVjUserNUm[ulDmpuId][ulDpeId]);
            }
        }
        vos_printf("\r\nPppMppcUserNum:");
        for ( ulDmpuId = 0; ulDmpuId < MAX_DMPU_NUM; ulDmpuId++)
        {
            for ( ulDpeId = 0; ulDpeId < 14; ulDpeId++)
            {
                vos_printf("\r\nDMPU[%2lu]DPE[%2lu] = %d:",
                    ulDmpuId, ulDpeId, g_usPppMppcUserNum[ulDmpuId][ulDpeId]);
            }
        }
        vos_printf("\r\nPppLzs0UserNUm = %d", g_usPppLzs0UserNum);
        vos_printf("\r\nPppLzs1UserNUm = %d", g_usPppLzs1UserNum);

        vos_printf("\r\n\r\ng_ulMaxDmpuDpeCpuRate = %lu", g_ulMaxDmpuDpeCpuRate);
        vos_printf("\r\ng_ulMinDmpuDpeCpuRate = %lu", g_ulMinDmpuDpeCpuRate);
        vos_printf("\r\ng_ulDmpuDpeNumber[0] = %lu", g_ulDmpuDpeNumber[0]);
        vos_printf("\r\ng_ulDmpuDpeNumber[1] = %lu", g_ulDmpuDpeNumber[1]);

        for ( ulDpeId = 0; ulDpeId < g_ulDmpuDpeNumber[0] + g_ulDmpuDpeNumber[1]; ulDpeId++)
        {
            vos_printf("\r\ng_ulDmpuDpeCpuRate[%lu] = %lu",
                ulDpeId, g_ulDmpuDpeCpuRate[ulDpeId]);
        }

        return;
    }

    if ((argc == 2) && !VOS_StrCmp(argv[0], "mppc"))
    {
        if (!VOS_StrCmp(argv[1], "1"))
        {
            g_ucPppCcpSwitch = 1;
            g_ucPppCcpType |= M_PPPCOMPRESS_MPPC_FLAG;
        }
        else if (!VOS_StrCmp(argv[1], "0"))
        {
            g_ucPppCcpType &= ~M_PPPCOMPRESS_MPPC_FLAG;
        }
        else
        {
            vos_printf("\nPara Error\n");
        }

        return;
    }

    if ((argc == 2) && !VOS_StrCmp(argv[0], "stac"))
    {
        if (!VOS_StrCmp(argv[1], "1"))
        {
            g_ucPppCcpSwitch = 1;
            g_ucPppCcpType |= M_PPPCOMPRESS_STAC_FLAG;
        }
        else if (!VOS_StrCmp(argv[1], "0"))
        {
            g_ucPppCcpType &= ~M_PPPCOMPRESS_STAC_FLAG;
        }
        else
        {
            vos_printf("\nPara Error\n");
        }

        return;
    }

    if ((argc == 2) && !VOS_StrCmp(argv[0], "vj"))
    {
        if (!VOS_StrCmp(argv[1], "1"))
        {
            g_ucPppVjSwitch = 1;
        }
        else if (!VOS_StrCmp(argv[1], "0"))
        {
            g_ucPppVjSwitch = 0;
        }
        else
        {
            vos_printf("\nPara Error\n");
        }

        return;
    }

    vos_printf("\nPara Error\n");

    return;
}

VOID PPP_DebugSetPrint(VOS_UINT32 ulPrintLevel)
{
    if (ulPrintLevel > 1)
    {
        PPP_Debug_SetAllOptions(&g_stPppDebugInfo, VRP_YES);
    }
    else
    {
        PPP_Debug_SetAllOptions(&g_stPppDebugInfo, VRP_NO);
    }

    vos_printf("\r\n ppp print level set to %u", ulPrintLevel);

    return;
}

/*lint -e774*/
VOID PPP_DebugSetPPPInfo(VOS_UINT32 ulArgc, CHAR *szArgv[])
{
    VOS_UINT32 ulRpIndex = 0;
    VOS_UINT32 ulPeerId = 0;
    VOS_UINT32 ulAAAType = 0;
    PPP_LUPPARA_S stUpPara;
    PPPINFO_S *pstPppInfo = NULL;

    if (4 != ulArgc)
    {
        vos_printf("\nPara Error\n");
        return;
    }

    PS_MEM_SET(&stUpPara, 0, sizeof(PPP_LUPPARA_S));

    if (!VOS_StrCmp(szArgv[0], "add"))
    {
        GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
        if (pstPppInfo != NULL)
        {
            vos_printf("\r\nPPP info Index %u exist.", ulRpIndex);
            return;
        }
        stUpPara.beHRPDMode = 1;
        if (VOS_OK != PPP_CreateCB(ulRpIndex, &stUpPara))
        {
            vos_printf("\r\nCreate PPP info Index %u fail.", ulRpIndex);
            return;
        }
        GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
        if (NULL == pstPppInfo)
        {
            vos_printf("\r\nPPP info Index %u do not exist.", ulRpIndex);
            return;
        }
        pstPppInfo->usPeerId = (VOS_UINT16)ulPeerId;
        pstPppInfo->ucAAAType = (UCHAR)ulAAAType;
    }
    else if (!VOS_StrCmp(szArgv[0], "del"))
    {
        GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
        if (NULL == pstPppInfo)
        {
            vos_printf("\r\nPPP info Index %u do not exist.", ulRpIndex);
            return;
        }

        (VOID)PPP_DeleteCB(pstPppInfo, PS_TRUE);
    }
    else
    {
        vos_printf("\nPara Error\n");
    }

    return;
}
/*lint +e774*/
#if 0
/**************************************************************************
 * Function     : SRIfmDevStart                                            *
 * Description  : 模拟设备管理模块启动接口管理接口创建过程.                *
 * Input        :                                                          *
 *                LONG argc : the number of argument                       *
 *                CHAR * argv[] : the arguments string                     *
 * Output       : None                                                     *
 * Return       : VOID                                                     *
 * Other        : None                                                     *
 ***************************************************************************/

VOID SRPppShowDebug( VOS_UINT32 argc, CHAR * argv []   )
{

    CHAR ucSet = 1;
    VOS_UINT32 ulType = PPP_DEBUG_EVENT;
    VOS_UINT16 usProtocol = PPP_LCP;

    CHAR szTmp1[80];
    CHAR szTmp2[80];


    /*Check Input parameter validity*/
    if (((argc >= 1) && !VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
        vos_printf ( "\r\nSet PPP Debug Switch.");
        vos_printf ( "\r\nUsage: ppp debug [all] | [none]"
                     "\r\n                 [core] 0/1"
                     "\r\n                 [protocol] { [event] [packet] [error] [state] } 0/1"
                     "\r\n                 stub { enable | disable }");
        return;
    }


    g_stPppDebugInfo.bDebug_Imsi = VRP_NO;

    if (argc == 1)
    {
        /*--------------------------------------------------------------------*/
        /* in favour of search,                                               */
        /*    1. change the upper letters in the word to lower                */
        /*    2. discard '?' at the end of string for partial help              */
        /*--------------------------------------------------------------------*/
        (VOID)ToLowerString ( argv[0], szTmp1 );
        (VOID)ToLowerString ( szTmp1, argv[0] );

        if (VOS_StrNiCmp( argv [ argc - 1 ], "all", 3) == 0)
        {
            PPP_Debug_SetAllOptions(&g_stPppDebugInfo, VRP_YES);
            vos_printf("\r\n success !");
        }
        else if (VOS_StrNiCmp( argv [ argc - 1 ], "none", 3) == 0)
        {
            PPP_Debug_SetAllOptions(&g_stPppDebugInfo, VRP_NO);
            vos_printf("\r\n success !");
        }
        else
        {
            vos_printf ( "\r\n Illegal Paramater.");
            return;
        }
    }
    else if (argc == 2)
    {
        /*--------------------------------------------------------------------*/
        /* in favour of search,                                               */
        /*    1. change the upper letters in the word to lower                */
        /*    2. discard '?' at the end of string for partial help              */
        /*--------------------------------------------------------------------*/
        (VOID)ToLowerString ( argv[0], szTmp1 );
        (VOID)ToLowerString ( szTmp1, argv[0] );
        (VOID)ToLowerString ( argv[1], szTmp2 );
        (VOID)ToLowerString ( szTmp2, argv[1] );

        /*procotol*/
        if (VOS_StrNiCmp( argv [ argc - 2 ], "core", 3) == 0)
        {
            usProtocol = 0;
            if (VOS_StrNiCmp( argv [ argc - 1 ], "0", 3) == 0)
            {
                ucSet  = 0;
                ulType = PPP_DEBUG_EVENT;
            }
            else if (VOS_StrNiCmp( argv [ argc - 1 ], "1", 3) == 0)
            {
                ucSet  = 1;
                ulType = PPP_DEBUG_EVENT;
            }
            else
            {
                vos_printf ( "\r\n Illegal Paramater.");
                return;
            }
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "lcp", 3) == 0)
        {
            usProtocol = PPP_LCP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "ipcp", 3) == 0)
        {
            usProtocol = PPP_IPCP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "osicp", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "osinpdu", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "mplscp", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "mplscpunicast", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "mplscpmulticast", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "pap", 3) == 0)
        {
            usProtocol = PPP_PAP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "chap", 3) == 0)
        {
            usProtocol = PPP_CHAP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "stub", 4) == 0)
        {
            PPP_SetStubValue(argc - 2, &argv[argc - 2]);
            return;
        }
        else
        {
            vos_printf ( "\r\n Illegal Paramater.");
            return;
        }

        /*type*/
        if (VOS_StrNiCmp( argv [ argc - 1 ], "error", 3) == 0)
        {
            ulType = PPP_DEBUG_ERROR;
        }
        else if (VOS_StrNiCmp( argv [ argc - 1 ], "event", 3) == 0)
        {
            ulType = PPP_DEBUG_EVENT;
        }
        else if (VOS_StrNiCmp( argv [ argc - 1 ], "packet", 3) == 0)
        {
            ulType = PPP_DEBUG_PACKET;
        }
        else if (VOS_StrNiCmp( argv [ argc - 1 ], "state", 3) == 0)
        {
            ulType = PPP_DEBUG_STATE;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "core", 3) != 0)
        {
            vos_printf ( "\r\n Illegal Paramater.");
            return;
        }

        PPP_Debug_SetOneOption(&g_stPppDebugInfo, (UCHAR)ucSet, ulType, usProtocol);
    }
    else if (argc == 3)
    {
        /*--------------------------------------------------------------------*/
        /* in favour of search,                                               */
        /*    1. change the upper letters in the word to lower                */
        /*    2. discard '?' at the end of string for partial help              */
        /*--------------------------------------------------------------------*/
        (VOID)ToLowerString ( argv[0], szTmp1 );
        (VOID)ToLowerString ( szTmp1, argv[0] );
        (VOID)ToLowerString ( argv[1], szTmp2 );
        (VOID)ToLowerString ( szTmp2, argv[1] );

        /*procotol*/
        if (VOS_StrNiCmp( argv [ argc - 3 ], "core", 3) == 0)
        {
            usProtocol = 0;
        }
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "lcp", 3) == 0)
        {
            usProtocol = PPP_LCP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "ipcp", 3) == 0)
        {
            usProtocol = PPP_IPCP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "osicp", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "osinpdu", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "mplscp", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "mplscpunicast", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "mplscpmulticast", 3) == 0)
        {}
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "pap", 3) == 0)
        {
            usProtocol = PPP_PAP;
        }
        else if (VOS_StrNiCmp( argv [ argc - 3 ], "chap", 3) == 0)
        {
            usProtocol = PPP_CHAP;
        }
        else
        {
            vos_printf ( "\r\n Illegal Paramater.");
            return;
        }

        /*type*/
        if (VOS_StrNiCmp( argv [ argc - 2 ], "error", 3) == 0)
        {
            ulType = PPP_DEBUG_ERROR;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "event", 3) == 0)
        {
            ulType = PPP_DEBUG_EVENT;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "packet", 3) == 0)
        {
            ulType = PPP_DEBUG_PACKET;
        }
        else if (VOS_StrNiCmp( argv [ argc - 2 ], "state", 3) == 0)
        {
            ulType = PPP_DEBUG_STATE;
        }
        else
        {
            vos_printf ( "\r\n Illegal Paramater.");
            return;
        }

        if (VOS_StrNiCmp( argv [ argc - 1 ], "0", 3) == 0)
        {
            ucSet = 0;
        }
        else if (VOS_StrNiCmp( argv [ argc - 1 ], "1", 3) == 0)
        {
            ucSet = 1;
        }
        else
        {
            vos_printf ( "\r\n Illegal Paramater.");
            return;
        }

        PPP_Debug_SetOneOption(&g_stPppDebugInfo, (UCHAR)ucSet, ulType, usProtocol);
    }
    else
    {
        vos_printf ( "\r\n Illegal Paramater.");
        return;
    }


    return;
}
#endif
/**************************************************************************
 * Function     : SRPppShowVSNCPDetailInfo                                 *
 * Description  : 打印VSNCP控制块信息                                      *
 * Input        :                                                          *
 *                LONG argc : the number of argument                       *
 *                CHAR * argv[] : the arguments string                     *
 * Output       : None                                                     *
 * Return       : VOID                                                     *
 * Other        : None                                                     *
 ***************************************************************************/
VOID SRPppShowVSNCPDetailInfo(PPPINFO_S *pstPppInfo)
{
    SDB_RETURNCODE_E ulRet;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL;
    PDN_CONTEXT_S *pstPdnContext = NULL;
    VOS_UINT32 i = 0;
    PDN_VSNCP_INFO_S *pstVSNCP = NULL;

    ulRet = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOS_VOID **)&pstRpContext);
    if ((VOS_OK != ulRet) || (NULL == pstRpContext))
    {
        return;
    }

    for(i = 0; i < A11_MAX_PDN_NUM; i++)
    {
        if (pstRpContext->ausPdnIndexArray[i])
        {
            pstPdnContext = NULL;
            ulRet = (SDB_RETURNCODE_E)SDB_GetPdnContextByIndex((VOS_UINT32)pstRpContext->ausPdnIndexArray[i], (VOS_VOID **)&pstPdnContext);
            if ((VOS_OK != ulRet) || (NULL == pstPdnContext))
            {
                continue;
            }

            if (E_PDNTYPE_EHRPD == pstPdnContext->ucPdnType)
            {
                pstVSNCP = &(pstPdnContext->stEhrpd.stVSNCP);
                vos_printf("\r\n------------------"
                            "\r\n PPPVSNCPINFO_S:"
                            "\r\n ucPDNID: %u"
                            "\r\n ucState: %u"
                            "\r\n TimeOutID: %lu"
                            "\r\n Retransmits: %d"
                            "\r\n ucUsedFlag: %d"
                            "\r\n ucPktId: %d"
                            "\r\n ucRenegoFlag: %d",
                            pstVSNCP->ucPDNID,
                            pstVSNCP->ucState,
                            pstVSNCP->ulTimeOutID,
                            (VOS_INT16)(pstVSNCP->sRetransmits),
                            pstVSNCP->ucUsedFlag,
                            pstVSNCP->ucPktId,
                            pstVSNCP->ucRenegoFlag);
            }
        }
    }
    return;
}

#if 0
/**************************************************************************
 * Function     : SRIfmDevStart                                            *
 * Description  : 打印PPP控制块信息                *
 * Input        :                                                          *
 *                LONG argc : the number of argument                       *
 *                CHAR * argv[] : the arguments string                     *
 * Output       : None                                                     *
 * Return       : VOID                                                     *
 * Other        : None                                                     *
 ***************************************************************************/
VOID SRPppShowCBDetailInfo( VOS_UINT32 argc, CHAR * argv []   )
{
    VOS_UINT32 ulRPIndex = 0, ulSwitch = 0xffffffff;
    PPPINFO_S *pstPppInfo;
    PPPLCPINFO_S *pstLcpInfo;
    PPPIPCPINFO_S *pstIpcpInfo;
    PPPIPV6CPINFO_S *pstIpv6cpInfo;
    PPPPAPINFO_S *pstPapInfo;
    PPPCHAPINFO_S *pstChapInfo;
#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    PPP_CCP_INFO_S *pstCcpInfo;
#endif
#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPPC_EAP_INFO_STRU *pstEAPInfo;
#endif

    if (((argc >= 1) && !VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
        vos_printf ( "\r\nShow PPP control block detail info.");
        vos_printf ( "\r\nUsage: ppp cb [rpindex] [switch]"
                     "\r\n        1: PPPINFO_S"
                     "\r\n        2: PPPLCPINFO_S"
                     "\r\n        4: PPPIPCPINFO_S&PPPIPV6CPINFO_S"
                     "\r\n        8: PPPPAPINFO_S"
                     "\r\n       16: PPPCHAPINFO_S"
                     "\r\n       32: PPPDHCPINFO_S"
                     "\r\n       64: PPPCCPINFO_S"
        );
        return;
    }

    if (argc == 0)
    {
        return;
    }

    ulRPIndex = (VOS_UINT32)atoi(argv[0]);
    if (ulRPIndex > PPP_MAX_USER_NUM)    /*WGGSN_B03_L2TP_PPPC*/
    {
        return;
    }

    if (PPP_CB_STATE_FREE == g_astPppPool[ulRPIndex].usState)
    {
        return;
    }

    if (argc == 2)
    {
        ulSwitch = (VOS_UINT32)atoi(argv[1]);
    }

    vos_printf("\r\n-------------------------------");
    (VOID)PPP_DbgShowPppInfo(ulRPIndex);

    pstPppInfo = &g_astPppPool[ulRPIndex];
    if (ulSwitch & 1)    /* PPPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPINFO_S 0x%p:"
                   "\r\nbPppMode: %lu"
                   "\r\nbPppClient: %lu"
                   "\r\nPhase: %d"
                   "\r\nIsAsync: %lu SynAsyConvert: %lu IPTech: %lu AuthServer: %lu AuthClient: %lu ReNego: %lu"
                   "\r\nCDBIndex: %d"
                   "\r\nMtu: %d RemoteAccm: %lu LocalAccm: %lu"
                   "\r\nPeerIPAddr: %08x DNSAddr1: %08x DNSAddr2: %08x"
                   "\r\nNAI: %s"
                   "\r\nLcpInfo: %p PapInfo: %p ChapInfo: %p IpcpInfo: %p Ipv6cpInfo: %p "
                   "\r\nAuthMethod: %lu AuthRmtChap: %lu AuthRmtPap: %lu"
                   "\r\nNegTimeOut: %lu Mru: %d"
                   "\r\nDomainName: %s"
                   "\r\nDmpuId %lu DpeId %d"
                   "\r\nusPeerId:[%lu]"
                   "\r\nbIPCPNakHandFlag[%u]",


                   pstPppInfo,
                   pstPppInfo->bPppMode,
                   pstPppInfo->bPppClient,
                   pstPppInfo->usPhase,
                   pstPppInfo->bIsAsync, pstPppInfo->bSynAsyConvert, pstPppInfo->bIPTech, pstPppInfo->bAuthServer,
                   pstPppInfo->bAuthClient, pstPppInfo->bReNego,
                   pstPppInfo->usCDBIndex,
                   pstPppInfo->usMtu, pstPppInfo->ulRemoteAccm, pstPppInfo->ulLocalAccm,
                   (VOS_UINT)pstPppInfo->ulPeerIPAddr, (VOS_UINT)pstPppInfo->ulDNSAddr1, (VOS_UINT)pstPppInfo->ulDNSAddr2,
                   pstPppInfo->ucNAI,
                   pstPppInfo->pstLcpInfo, pstPppInfo->pstPapInfo, pstPppInfo->pstChapInfo,
                   pstPppInfo->pstIpcpInfo, pstPppInfo->pstIpV6cpInfo,
                   (VOS_UINT32)pstPppInfo->pstConfigInfo->bAuthMethod, pstPppInfo->pstConfigInfo->bAuthRmtChap,
                   pstPppInfo->pstConfigInfo->bAuthRmtPap,
                   pstPppInfo->pstConfigInfo->ulNegTimeOut, pstPppInfo->pstConfigInfo->usMru,
                   (UCHAR *)pstPppInfo->pstConfigInfo->ucDomainName,
                   (VOS_UINT32)pstPppInfo->ucDmpuId,
                   pstPppInfo->ucDpeId,
                   (VOS_UINT32)pstPppInfo->usPeerId,
                   pstPppInfo->bIPCPNakHandFlag
        );

        vos_printf("\r\nbPhaseFlag: %lu PcfIP: %lu"
                   "\r\nFSMFailType: %d ",
                   pstPppInfo->bPhaseFlag, pstPppInfo->ulPcfIP,
                   pstPppInfo->ucFSMFailType);
    }

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if ((ulSwitch & 2) && pstLcpInfo)    /* PPPLCPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPLCPINFO_S:"
                   "\r\nState: %u"
                   "\r\nPktId: %u"
                   "\r\nTimeOutID: %lu"
                   "\r\nRetransmits: %u usNakloops: %u"
                   "\r\nGotOption:"
                   "\r\nneg_mru: %lu mru: %d"
                   "\r\nneg_asyncmap: %lu asyncmap: %lu"
                   "\r\nneg_upap: %lu"
                   "\r\nneg_chap: %lu chap_mdtype: %d"
                   "\r\nneg_magicnumber: %lu magicnumber: %lu"
                   "\r\nneg_pcompression: %lu"
                   "\r\nneg_accompression: %lu"
                   "\r\nHisOption:"
                   "\r\nneg_mru: %lu mru: %d"
                   "\r\nneg_asyncmap: %lu asyncmap: %08x"
                   "\r\nneg_upap: %lu"
                   "\r\nneg_chap: %lu chap_mdtype: %d"
                   "\r\nneg_magicnumber: %lu magicnumber: %lu"
                   "\r\nneg_pcompression: %lu"
                   "\r\nneg_accompression: %lu"
                   "\r\nbReqSendAck %d",
                   pstLcpInfo->stFsm.ucState,
                   pstLcpInfo->stFsm.ucPktId,
                   pstLcpInfo->stFsm.ulTimeOutID,
                   (VOS_UINT)pstLcpInfo->stFsm.sRetransmits, (VOS_UINT)pstLcpInfo->stFsm.usNakloops,

                   pstLcpInfo->stGotOptions.neg_mru, pstLcpInfo->stGotOptions.mru,
                   pstLcpInfo->stGotOptions.neg_asyncmap, pstLcpInfo->stGotOptions.asyncmap,
                   pstLcpInfo->stGotOptions.neg_upap,
                   pstLcpInfo->stGotOptions.neg_chap, pstLcpInfo->stGotOptions.chap_mdtype,
                   pstLcpInfo->stGotOptions.neg_magicnumber, pstLcpInfo->stGotOptions.magicnumber,
                   pstLcpInfo->stGotOptions.neg_pcompression,
                   pstLcpInfo->stGotOptions.neg_accompression,

                   pstLcpInfo->stHisOptions.neg_mru, pstLcpInfo->stHisOptions.mru,
                   (VOS_UINT32)pstLcpInfo->stHisOptions.neg_asyncmap, (VOS_UINT)pstLcpInfo->stHisOptions.asyncmap,
                   pstLcpInfo->stHisOptions.neg_upap,
                   pstLcpInfo->stHisOptions.neg_chap, pstLcpInfo->stHisOptions.chap_mdtype,
                   pstLcpInfo->stHisOptions.neg_magicnumber, pstLcpInfo->stHisOptions.magicnumber,
                   pstLcpInfo->stHisOptions.neg_pcompression,
                   pstLcpInfo->stHisOptions.neg_accompression,
                   pstLcpInfo->bReqSendAck
        );
    }

    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
    if ((ulSwitch & 4) && pstIpcpInfo)    /* PPPIPCPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPIPCPINFO_S:"
                   "\r\nState: %u"
                   "\r\nPktId: %u"
                   "\r\nTimeOutID: %lu"
                   "\r\nRetransmits: %lu usNakloops: %lu"
                   "\r\nGotOption:"
                   "\r\nneg_addr: %lu ouraddr: %08x"
                   "\r\nreq_addr: %lu hisaddr: %08x"
                   "\r\nneg_vj: %lu vj_protocol: %x maxslotindex: %d cflag: %d"
                   "\r\nneg_dnsaddr0: %lu dnsaddr0: %08x"
                   "\r\nreq_dnsaddr0: %lu accept_dnsaddr0: %08x"
                   "\r\nneg_nbnsaddr0: %lu nbnsaddr0: %08x"
                   "\r\nreq_nbnsaddr0: %lu  accept_dnsaddr1: %08x"
                   "\r\nneg_dnsaddr1: %lu   dnsaddr1: %08x"
                   "\r\nreq_dnsaddr1: %lu   accept_nbnsaddr0: %08x"
                   "\r\nneg_nbnsaddr1: %lu   nbnsaddr1: %08x"
                   "\r\nreq_nbnsaddr1: %lu   accept_nbnsaddr1: %08x"
                   "\r\nHisOption:"
                   "\r\nneg_addr: %lu ouraddr: %08x"
                   "\r\nreq_addr: %lu hisaddr: %08x"
                   "\r\nneg_vj: %lu vj_protocol: %x maxslotindex: %d cflag: %d"
                   "\r\nneg_dnsaddr0: %ludnsaddr0: %08x"
                   "\r\nreq_dnsaddr0: %lu accept_dnsaddr0: %08x"
                   "\r\nneg_nbnsaddr0: %lu nbnsaddr0: %08x"
                   "\r\nreq_nbnsaddr0: %lu accept_dnsaddr1: %08x"
                   "\r\nneg_dnsaddr1: %lu dnsaddr1: %08x"
                   "\r\nreq_dnsaddr1: %lu accept_nbnsaddr0: %08x"
                   "\r\nneg_nbnsaddr1: %lunbnsaddr1: %08x"
                   "\r\nreq_nbnsaddr1: %lu accept_nbnsaddr1: %08x"
                   "\r\npucIpv4cpMsg:%x",
                   pstIpcpInfo->stFsm.ucState,
                   pstIpcpInfo->stFsm.ucPktId,
                   pstIpcpInfo->stFsm.ulTimeOutID,
                   (VOS_UINT32)pstIpcpInfo->stFsm.sRetransmits, (VOS_UINT32)pstIpcpInfo->stFsm.usNakloops,

                   pstIpcpInfo->stGotOptions.neg_addr, (VOS_UINT)pstIpcpInfo->stGotOptions.ouraddr,
                   pstIpcpInfo->stGotOptions.req_addr, (VOS_UINT)pstIpcpInfo->stGotOptions.hisaddr,
                   pstIpcpInfo->stGotOptions.neg_vj, pstIpcpInfo->stGotOptions.vj_protocol,
                   pstIpcpInfo->stGotOptions.maxslotindex, pstIpcpInfo->stGotOptions.cflag,
                   pstIpcpInfo->stGotOptions.neg_dnsaddr0, (VOS_UINT)pstIpcpInfo->stGotOptions.dnsaddr0,
                   pstIpcpInfo->stGotOptions.req_dnsaddr0, (VOS_UINT)pstIpcpInfo->stGotOptions.accept_dnsaddr0,
                   pstIpcpInfo->stGotOptions.neg_nbnsaddr0, (VOS_UINT)pstIpcpInfo->stGotOptions.nbnsaddr0,
                   pstIpcpInfo->stGotOptions.req_nbnsaddr0, (VOS_UINT)pstIpcpInfo->stGotOptions.accept_dnsaddr1,
                   pstIpcpInfo->stGotOptions.neg_dnsaddr1, (VOS_UINT)pstIpcpInfo->stGotOptions.dnsaddr1,
                   pstIpcpInfo->stGotOptions.req_dnsaddr1, (VOS_UINT)pstIpcpInfo->stGotOptions.accept_nbnsaddr0,
                   pstIpcpInfo->stGotOptions.neg_nbnsaddr1, (VOS_UINT)pstIpcpInfo->stGotOptions.nbnsaddr1,
                   pstIpcpInfo->stGotOptions.req_nbnsaddr1, (VOS_UINT)pstIpcpInfo->stGotOptions.accept_nbnsaddr1,

                   pstIpcpInfo->stHisOptions.neg_addr, (VOS_UINT)pstIpcpInfo->stHisOptions.ouraddr,
                   pstIpcpInfo->stHisOptions.req_addr, (VOS_UINT)pstIpcpInfo->stHisOptions.hisaddr,
                   pstIpcpInfo->stHisOptions.neg_vj, pstIpcpInfo->stHisOptions.vj_protocol,
                   pstIpcpInfo->stHisOptions.maxslotindex, pstIpcpInfo->stHisOptions.cflag,
                   pstIpcpInfo->stHisOptions.neg_dnsaddr0, (VOS_UINT)pstIpcpInfo->stHisOptions.dnsaddr0,
                   pstIpcpInfo->stHisOptions.req_dnsaddr0, (VOS_UINT)pstIpcpInfo->stHisOptions.accept_dnsaddr0,
                   pstIpcpInfo->stHisOptions.neg_nbnsaddr0, (VOS_UINT)pstIpcpInfo->stHisOptions.nbnsaddr0,
                   pstIpcpInfo->stHisOptions.req_nbnsaddr0, (VOS_UINT)pstIpcpInfo->stHisOptions.accept_dnsaddr1,
                   pstIpcpInfo->stHisOptions.neg_dnsaddr1, (VOS_UINT)pstIpcpInfo->stHisOptions.dnsaddr1,
                   pstIpcpInfo->stHisOptions.req_dnsaddr1, (VOS_UINT)pstIpcpInfo->stHisOptions.accept_nbnsaddr0,
                   pstIpcpInfo->stHisOptions.neg_nbnsaddr1, (VOS_UINT)pstIpcpInfo->stHisOptions.nbnsaddr1,
                   pstIpcpInfo->stHisOptions.req_nbnsaddr1, (VOS_UINT)pstIpcpInfo->stHisOptions.accept_nbnsaddr1,
                   pstIpcpInfo->pucIpv4cpMsg
        );
    }

    pstIpv6cpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;
    if ((ulSwitch & 4) && pstIpv6cpInfo)    /* PPPIPV6CPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPIPV6CPINFO_S:"
                   "\r\nState: %u"
                   "\r\nPktId: %u"
                   "\r\nTimeOutID: %lu"
                   "\r\nRetransmits: %u usNakloops: %u"

                   "\r\nGotOption:"
                   "\r\nOurV6InId: %02x-%02x-%02x-%02x"
                   "\r\nHisV6InId: %02x-%02x-%02x-%02x"
                   "\r\nConfigV6InId: %02x-%02x-%02x-%02x"

                   "\r\nHisOption:"
                    "\r\nOurV6InId: %02x-%02x-%02x-%02x"
                    "\r\nHisV6InId: %02x-%02x-%02x-%02x"
                    "\r\nConfigV6InId: %02x-%02x-%02x-%02x"
                    "\r\npucIpv6cpMsg:%x",

                   pstIpv6cpInfo->stFsm.ucState,
                   pstIpv6cpInfo->stFsm.ucPktId,
                   pstIpv6cpInfo->stFsm.ulTimeOutID,
                   (VOS_UINT)pstIpv6cpInfo->stFsm.sRetransmits, (VOS_UINT)pstIpv6cpInfo->stFsm.usNakloops,

                   pstIpv6cpInfo->stGotOptions.OurV6InId[0],pstIpv6cpInfo->stGotOptions.OurV6InId[1],
                   pstIpv6cpInfo->stGotOptions.OurV6InId[2],pstIpv6cpInfo->stGotOptions.OurV6InId[3],
                   pstIpv6cpInfo->stGotOptions.HisV6InId[0],pstIpv6cpInfo->stGotOptions.HisV6InId[1],
                   pstIpv6cpInfo->stGotOptions.HisV6InId[2],pstIpv6cpInfo->stGotOptions.HisV6InId[3],
                   pstIpv6cpInfo->stGotOptions.ConfigV6InId[0],pstIpv6cpInfo->stGotOptions.ConfigV6InId[1],
                   pstIpv6cpInfo->stGotOptions.ConfigV6InId[2],pstIpv6cpInfo->stGotOptions.ConfigV6InId[3],

                   pstIpv6cpInfo->stHisOptions.OurV6InId[0],pstIpv6cpInfo->stHisOptions.OurV6InId[1],
                   pstIpv6cpInfo->stHisOptions.OurV6InId[2],pstIpv6cpInfo->stHisOptions.OurV6InId[3],
                   pstIpv6cpInfo->stHisOptions.HisV6InId[0],pstIpv6cpInfo->stHisOptions.HisV6InId[1],
                   pstIpv6cpInfo->stHisOptions.HisV6InId[2],pstIpv6cpInfo->stHisOptions.HisV6InId[3],
                   pstIpv6cpInfo->stHisOptions.ConfigV6InId[0],pstIpv6cpInfo->stHisOptions.ConfigV6InId[1],
                   pstIpv6cpInfo->stHisOptions.ConfigV6InId[2],pstIpv6cpInfo->stHisOptions.ConfigV6InId[3],
                   pstIpv6cpInfo->pucIpv6cpMsg
        );
    }

    pstPapInfo = (PPPPAPINFO_S*)pstPppInfo->pstPapInfo;
    if ((ulSwitch & 8) && pstPapInfo)    /* PPPPAPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPPAPINFO_S:"
                   "\r\nServerState: %d"
                   "\r\nId: %d"
                   "\r\nPeerId: %d"
                   "\r\nServerTimeoutID: %lu"
                   "\r\nWaitReqTimeout: %lu"
                   "\r\nPapUsrName: %s"
                   "\r\nPapUsrPwd: %s"
                   "\r\nWaitAuthRspTimeout: %lu"
                   "\r\nAuthTransmits: %d"
                   "\r\nAuthMaxTransmits: %lu",
                   pstPapInfo->ucServerState,
                   pstPapInfo->ucId,
                   pstPapInfo->ucPeerId,
                   pstPapInfo->ulServerTimeoutID,
                   pstPapInfo->ulWaitReqTimeout,
                   pstPapInfo->szPapUsrName,
                   pstPapInfo->szPapUsrPwd,
                   pstPapInfo->ulWaitAuthRspTimeout,
                   pstPapInfo->ucAuthTransmits,
                   pstPapInfo->ulAuthMaxTransmits
        );
    }

    pstChapInfo = (PPPCHAPINFO_S*)pstPppInfo->pstChapInfo;
    if ((ulSwitch & 16) && pstChapInfo)    /* PPPCHAPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPCHAPINFO_S:"
                   "\r\nServerState: %d"
                   "\r\nChalId: %d"
                   "\r\nChalType: %d"
                   "\r\nChalTransmits: %lu"
                   "\r\nChalInterval: %lu"
                   "\r\nChalTimeoutID: %lu"
                   "\r\nAuthServerFailureTimes: %d"
                   "\r\nTimeOutTime: %lu"
                   "\r\nMaxTransmits: %lu"
                   "\r\nHostName: %s"
                   "\r\nHostPwd: %s"
                   "\r\nWaitAuthRspTimeout: %lu"
                   "\r\nAuthTransmits: %d"
                   "\r\nAuthMaxTransmits: %lu",
                   pstChapInfo->ucServerState,
                   pstChapInfo->ucChalId,
                   pstChapInfo->ucChalType,
                   pstChapInfo->ulChalTransmits,
                   pstChapInfo->ulChalInterval,
                   pstChapInfo->ulChalTimeoutID,
                   pstChapInfo->usAuthServerFailureTimes,
                   pstChapInfo->ulTimeOutTime,
                   pstChapInfo->ulMaxTransmits,
                   pstChapInfo->szHostName,
                   pstChapInfo->szHostPwd,
                   pstChapInfo->ulWaitAuthRspTimeout,
                   pstChapInfo->ucAuthTransmits,
                   pstChapInfo->ulAuthMaxTransmits
        );
    }

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
    if ((ulSwitch & 64) && pstCcpInfo)    /* PPPCCPINFO_S */
    {
        vos_printf("\r\n------------------"
                   "\r\nPPPCCPINFO_S:"
                   "\r\nState: %u"
                   "\r\nucPppCompType: %u"
                   "\r\nPktId: %u"
                   "\r\nTimeOutID: %lu"
                   "\r\nRetransmits: %u usNakloops: %u"
                   "\r\nGotOption:"
                   "\r\nbStac_compress: %lu bMppc_compress: %lu"
                   "\r\nusStac_historys: %d ucStac_checkmode: %d"
                   "\r\nulMppc_supportedbits: %lu "
                   "\r\nHisOption:"
                   "\r\nbStac_compress: %lu bMppc_compress: %lu"
                   "\r\nusStac_historys: %d ucStac_checkmode: %d"
                   "\r\nulMppc_supportedbits: %lu ",
                   pstCcpInfo->stFsm.ucState,
                   pstCcpInfo->ucPppCompType,
                   pstCcpInfo->stFsm.ucPktId,
                   pstCcpInfo->stFsm.ulTimeOutID,
                   (VOS_UINT)pstCcpInfo->stFsm.sRetransmits, pstCcpInfo->stFsm.usNakloops,

                   (VOS_UINT32)pstCcpInfo->stGotOptions.bStac_compress, (VOS_UINT32)pstCcpInfo->stGotOptions.bMppc_compress,
                   pstCcpInfo->stGotOptions.usStac_historys, pstCcpInfo->stGotOptions.ucStac_checkmode,
                   pstCcpInfo->stGotOptions.ulMppc_supportedbits,

                   (VOS_UINT32)pstCcpInfo->stHisOptions.bStac_compress, (VOS_UINT32)pstCcpInfo->stHisOptions.bMppc_compress,
                   pstCcpInfo->stHisOptions.usStac_historys, pstCcpInfo->stHisOptions.ucStac_checkmode,
                   pstCcpInfo->stHisOptions.ulMppc_supportedbits
        );
    }
#endif

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    pstEAPInfo = (PPPC_EAP_INFO_STRU*)pstPppInfo->pstEapInfo;
    if (pstEAPInfo)    /* pstEAPInfo */
    {
        vos_printf("\r\n-------EAP_INFO-----------"
                   "\r\n State: %d"
                   "\r\n ucEAPFlag: %d"
                   "\r\n ucEapRequestID: %d"
                   "\r\n ucReAuthFlag: %d "
                   "\r\n ucRequestforIdentity: %d"
                   "\r\n ucUsed: %d "
                   "\r\n ulRaAUTHTimerID: %lu"
                   "\r\n ulReqTransmits: %lu "
                   "\r\n ulTimeOutTime: %lu"
                   "\r\n ulWaitAuthRspTimeID: %lu "
                   "\r\n usEAPLen: %lu"
                   "\r\n pucEAP: %p "
                   "\r\n pstPppInfo: %p "
                   "\r\n ucStateLen: %d ",
                   pstEAPInfo->ucState,
                   pstEAPInfo->ucEAPFlag,
                   pstEAPInfo->ucEapRequestID,
                   pstEAPInfo->ucReAuthFlag,
                   pstEAPInfo->ucRequestforIdentity,
                   pstEAPInfo->ucUsed,
                   pstEAPInfo->ulRaAUTHTimerID,
                   pstEAPInfo->ulReqTransmits,
                   pstEAPInfo->ulTimeOutTime,
                   pstEAPInfo->ulWaitAuthRspTimeID,
                   (VOS_UINT32)pstEAPInfo->usEAPLen,
                   pstEAPInfo->pucEAP,
                   pstEAPInfo->pstPppInfo,
                   pstEAPInfo->ucStateLen);
    }
#endif

    SRPppShowVSNCPDetailInfo(pstPppInfo);
    return;
}
#endif

/*****************************************************************************
 函 数 名  : PPP_PrintFsmStat
 功能描述  : 打印状态机计数
 输入参数  :
 输出参数  :
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_ShowFsmStat(VOS_UINT32 *pulState)
{
    VOS_UINT32 i, j , len;
    CHAR aucTemp[200] = { 0 };
    vos_printf("\r\n      | State");
    vos_printf("\r\n      |    0         1         2         3         4         5     ");
    vos_printf("\r\nEvents| Initial   Starting  Closed    Stopped   Closing   Stopping ");
    vos_printf("\r\n------+------------------------------------------------------------");

    for ( i = 0; i < PPP_EVENT_FSM_BUTT; i++)
    {
        len = (VOS_UINT32)VOS_sprintf(aucTemp,"%s |", g_cPPP_Debug_event[i]);
        for ( j = 0; j < PPP_STATE_REQSENT; j++)
        {
             len += VOS_sprintf(aucTemp+len,"%8lu  ",pulState[i * PPP_STATE_BUTT + j]);
        }
        vos_printf("\r\n%s", aucTemp);
    }

    vos_printf("\r\n");
    vos_printf("\r\n      | State");
    vos_printf("\r\n      |    6         7         8           9");
    vos_printf("\r\nEvents| Req-Sent  Ack-Rcvd  Ack-Sent    Opened");
    vos_printf("\r\n------+---------------------------------------");

    for ( i = 0; i < PPP_EVENT_FSM_BUTT; i++)
    {
        len = (VOS_UINT32)VOS_sprintf(aucTemp,"%s |", g_cPPP_Debug_event[i]);
        for ( j = PPP_STATE_REQSENT; j < PPP_STATE_BUTT; j++)
        {
             len += VOS_sprintf(aucTemp+len,"%8lu  ",pulState[i * PPP_STATE_BUTT + j]);
        }
        vos_printf("\r\n%s", aucTemp);
    }
    vos_printf("\r\n\r\n");
    return;
}

VOS_VOID PPP_ClearCnt(VOS_VOID)
{
    VOS_UINT32                  i = 0;

    PPP_MemSet((void *)g_ulPppDBGStatisc, 0, sizeof(g_ulPppDBGStatisc[0]) * PPP_DBG_BUTT);
    PPP_MemSet((void *)g_ulPppFsmStat[0], 0, (sizeof(g_ulPppFsmStat[0][0]) * 5 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT));

    for (i = PPP_INNER_COUTNER_000; i < PPP_INNER_COUTNER_END; i++)
    {
        g_pstPppInnerDebugInfo[i].ulCounter = 0;
    }

    for (i = PPP_ERROR_COUNTER000; i < PPP_ERROR_COUNTER_END; i++)
    {
        g_pstPppErrorDebugInfo[i].ulCounter = 0;
    }

    return;
}

VOID PPP_DbgShowErrStatisc()
{
    VOS_UINT32 i             = 0;
    VOS_UINT32 ulPrintCnt    = 100; /* 一次性打印个数上限 */
    VOS_UINT32 ulUsedCnt     = 0;


    /* 打印失败计数 */
    for (i = 0; i < PPP_PHERR_BUTT; i++)
    {
        ulUsedCnt++;
        /* 为了防止持续打印将串口打死, 每次打印一定量后, 则延迟, 然后继续打印 */
        if (ulUsedCnt > ulPrintCnt)
        {
            VOS_TaskDelay(10);
            ulUsedCnt   =   0;
        }

        PPP_PRINT_ERR_STATISC(i);
    }

    return;
}

VOID PPP_DbgShowOkStatisc()
{
    VOS_UINT32 i             = 0;
    VOS_UINT32 ulPrintCnt    = 100; /* 一次性打印个数上限 */
    VOS_UINT32 ulUsedCnt     = 0;


    /* 打印成功计数 */
    for (i = PPP_PHOK_800; i < PPP_DBG_BUTT; i++)
    {
        ulUsedCnt++;
        /* 为了防止持续打印将串口打死, 每次打印一定量后, 则延迟, 然后继续打印 */
        if (ulUsedCnt > ulPrintCnt)
        {
            VOS_TaskDelay(10);
            ulUsedCnt   =   0;
        }
        PPP_PRINT_SUCC_STATISC(i);
    }

    return;
}


VOID PPP_DbgShowCnt()
{

    VOS_UINT32 i = 0;

    PPP_DbgShowErrStatisc();
    PPP_DbgShowOkStatisc();

    vos_printf("\r\n ------------- Ppp Inner Counter----------\r\n");

    for (i = PPP_INNER_COUTNER_000; i < PPP_INNER_COUTNER_END; i++)
    {
        if (0 != g_pstPppInnerDebugInfo[i].ulCounter)
        {
            vos_printf("\r\nPPP_INNER_COUTNER_%03lu:%-10lu Tips:%s",
                        i,
                        g_pstPppInnerDebugInfo[i].ulCounter,
                        g_pstPppInnerDebugInfo[i].szTips);

        }

    }

    vos_printf("\r\n ------------- Ppp Error Counter----------\r\n");

    for (i = PPP_ERROR_COUNTER000; i < PPP_ERROR_COUNTER_END; i++)
    {
        if (0 != g_pstPppErrorDebugInfo[i].ulCounter)
        {
            vos_printf("\r\n PPP_ERROR_COUNTER%03lu:%-10lu Tips:%s",
                       i,
                       g_pstPppErrorDebugInfo[i].ulCounter,
                       g_pstPppErrorDebugInfo[i].szTips);
        }
    }

    vos_printf("\r\n Over!");

}

VOID PPP_DbgShowDmpuInfo()
{
    vos_printf("\r\nvj   user in dmpu1   = %u",g_ulDmpuVjUser[0]);
    vos_printf("\r\nvj   user in dmpu2   = %u",g_ulDmpuVjUser[1]);
    vos_printf("\r\nmppc user in dmpu1   = %u",g_ulDmpuMppcUser[0]);
    vos_printf("\r\nmppc user in dmpu2   = %u",g_ulDmpuMppcUser[1]);
}

VOS_UINT32 PPP_DbgShowPppInfo(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    UCHAR   ucImsiTemp[M_IMSI_LEN] = {0};

    /*WGGSN_B03_L2TP_PPPC*/
    IMSI_S stImsiTemp;

    PPP_MemSet(&stImsiTemp, 0, sizeof(stImsiTemp));

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == NULL)
    {
        vos_printf("\r\nIndex %lu is NULL.", ulRpIndex);
        return VOS_ERR;
    }

    vos_printf("\r\nusState: \t%u", pstPppInfo->usState);
    vos_printf("\r\nbIsAsync: \t%lu", pstPppInfo->bIsAsync);
    vos_printf("\r\nbSynAsyConvert: \t%lu", pstPppInfo->bSynAsyConvert);
    vos_printf("\r\nbLoopBacked: \t%lu", pstPppInfo->bLoopBacked);
    vos_printf("\r\nbLowerIsUp: \t%lu", pstPppInfo->bLowerIsUp);
    vos_printf("\r\nbIPTech: \t%lu", pstPppInfo->bIPTech);
    vos_printf("\r\nbFailFlag: \t%lu", pstPppInfo->bFailFlag);
    vos_printf("\r\nbAuthServer: \t%lu", pstPppInfo->bAuthServer);
    vos_printf("\r\nbAuthClient: \t%lu", pstPppInfo->bAuthClient);
    vos_printf("\r\nbReNego: \t%lu", pstPppInfo->bReNego);
    vos_printf("\r\nbPppStateFlg: \t%lu", pstPppInfo->bPppStateFlg);
    vos_printf("\r\nulRemoteAccm: \t%lu", pstPppInfo->ulRemoteAccm);
    vos_printf("\r\nulLocalAccm: \t%lu", pstPppInfo->ulLocalAccm);
    vos_printf("\r\nulRPIndex: \t%lu", pstPppInfo->ulRPIndex);
    vos_printf("\r\nusCDBIndex: \t%u", pstPppInfo->usCDBIndex);
    vos_printf("\r\nbEAPAuthFlag: \t%u", pstPppInfo->bEAPAuthFlag);
    vos_printf("\r\nusVirtualDomainIdx: \t%u", pstPppInfo->usVirtualDomainIdx);
    vos_printf("\r\nbPppMode: \t%lu", pstPppInfo->bPppMode);
    vos_printf("\r\nbPppClient: \t%lu", pstPppInfo->bPppClient);
    vos_printf("\r\nbIPReleaseFlg: \t%lu", pstPppInfo->bIPReleaseFlg);

    vos_printf("\r\nbMppcFlag: \t%lu", pstPppInfo->bMppcFlag);
    vos_printf("\r\nbVjFlag: \t%lu", pstPppInfo->bVjFlag);
    vos_printf("\r\nbLzs0Flag: \t%lu", pstPppInfo->bLzs0Flag);
    vos_printf("\r\nbLzs1Flag: \t%lu", pstPppInfo->bLzs1Flag);
    vos_printf("\r\nbPpcAAAFlag: \t%lu", pstPppInfo->bPpcAAAFlag);
    vos_printf("\r\nbPppSuccess: \t%lu", pstPppInfo->bPppSuccess);

    vos_printf("\r\nbIpcpSucFlag: \t%lu", pstPppInfo->bIpcpSucFlag);
    vos_printf("\r\nbPccFlag: \t%lu", pstPppInfo->bPccFlag);
    vos_printf("\r\nbRecvLcpMsgFlag:\t%lu", pstPppInfo->bRecvLcpMsgFlag);
    vos_printf("\r\nbIpv6cpNoToPDN: \t%lu", pstPppInfo->bIpv6cpNoToPDN);
    vos_printf("\r\nbIpcpNoToPDN: \t%lu", pstPppInfo->bIpcpNoToPDN);
    vos_printf("\r\nbEhrpdUser:   \t%lu", pstPppInfo->bEhrpdUser);

    vos_printf("\r\nusPeerId:   \t%u", pstPppInfo->usPeerId);
    vos_printf("\r\nucAAAType:   \t%u", pstPppInfo->ucAAAType);
    vos_printf("\r\nusTokenId:   \t%u", pstPppInfo->usTokenId);
    vos_printf("\r\nulNowUTCInSec:   \t%u", pstPppInfo->ulNowUTCInSec);
    vos_printf("\r\nulNegoStartTime: \t%u", (VOS_UINT32)pstPppInfo->ulNegoStartTime);
    vos_printf("\r\nulNegoEndTime: \t%u", (VOS_UINT32)pstPppInfo->ulNegoEndTime);
    vos_printf("\r\nusPcfIndex: \t%u", pstPppInfo->usPcfIndex);
    vos_printf("\r\nucServiceOpt: \t%u", pstPppInfo->ucServiceOpt);


    VOS_MemCpy((VOID *)&stImsiTemp, (VOID *)&(pstPppInfo->stIMSI), sizeof(IMSI_S));

    ImsiToString(stImsiTemp, ucImsiTemp);
    vos_printf("\r\nIMSI: \t%s", ucImsiTemp);

    vos_printf("\r\nulIPAddr: \t%x", (VOS_UINT)pstPppInfo->ulIPAddr);
    vos_printf("\r\nulPeerIPAddr: \t%x", (VOS_UINT)pstPppInfo->ulPeerIPAddr);
    vos_printf("\r\nucNAI: %s", pstPppInfo->ucNAI);
    vos_printf("\r\nusPhase: \t%u", pstPppInfo->usPhase);
    vos_printf("\r\nbPhaseFlag: \t%lu", pstPppInfo->bPhaseFlag);
    vos_printf("\r\nPcfIP: \t%lu", pstPppInfo->ulPcfIP);
    vos_printf("\r\nFSMFailType: \t%d", pstPppInfo->ucFSMFailType);
    vos_printf("\r\nbAuthFlag: \t%lu", pstPppInfo->bAuthFlag);
    vos_printf("\r\nucDmpuId: \t%u", pstPppInfo->ucDmpuId);
    vos_printf("\r\nucDpeId: \t%u", pstPppInfo->ucDpeId);
    vos_printf("\r\nusMtu: \t%u", pstPppInfo->usMtu);

    vos_printf("\r\nIP4_DNS_IP1: \t%x", (VOS_UINT)pstPppInfo->ulDNSAddr1);
    vos_printf("\r\nIP4_DNS_IP2: \t%x", (VOS_UINT)pstPppInfo->ulDNSAddr2);


    /* ipv4 new define */
    if (NULL != pstPppInfo->pstIpcpInfo)
    {
        vos_printf("\r\nulIpcpLen: \t%u", ((PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo)->ulIpv4cpLen);
        vos_printf("\r\npucIpcpMsg: \t%x", ((PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo)->pucIpv4cpMsg);
    }

    /* ipv6 new define */
    if (NULL != pstPppInfo->pstIpV6cpInfo)
    {
        vos_printf("\r\nulIpv6cpLen: \t%u", ((PPPIPV6CPINFO_S *)(pstPppInfo->pstIpV6cpInfo))->ulIpv6cpLen);
        vos_printf("\r\npucIpv6cpMsg: \t%x", ((PPPIPV6CPINFO_S *)(pstPppInfo->pstIpV6cpInfo))->pucIpv6cpMsg);
    }


    vos_printf("\r\nusIpv6Addr: \t%x-%x-%x-%x-%x-%x-%x-%x", pstPppInfo->usIpv6Addr[0],
                                                            pstPppInfo->usIpv6Addr[1],
                                                            pstPppInfo->usIpv6Addr[2],
                                                            pstPppInfo->usIpv6Addr[3],
                                                            pstPppInfo->usIpv6Addr[4],
                                                            pstPppInfo->usIpv6Addr[5],
                                                            pstPppInfo->usIpv6Addr[6],
                                                            pstPppInfo->usIpv6Addr[7]);

    vos_printf("\r\nusPeerIPv6Addr: \t%x-%x-%x-%x-%x-%x-%x-%x", pstPppInfo->usPeerIPv6Addr[0],
                                                                pstPppInfo->usPeerIPv6Addr[1],
                                                                pstPppInfo->usPeerIPv6Addr[2],
                                                                pstPppInfo->usPeerIPv6Addr[3],
                                                                pstPppInfo->usPeerIPv6Addr[4],
                                                                pstPppInfo->usPeerIPv6Addr[5],
                                                                pstPppInfo->usPeerIPv6Addr[6],
                                                                pstPppInfo->usPeerIPv6Addr[7]);


    vos_printf("\r\nbReNegoV6: \t%lu", pstPppInfo->bReNegoV6);
    vos_printf("\r\nbPppStateFlgV6: \t%lu", pstPppInfo->bPppStateFlgV6);
    vos_printf("\r\nucIpCapability: \t%x", pstPppInfo->ucIpCapability);

    vos_printf("\r\nok\r\n");

    return VOS_OK;

}



VOID PPP_ShowRPIndexByDynAAAIndex(VOS_UINT16 usDynAAAIndex)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulCounter = 0;

    for (i = 1; i <= PPP_MAX_USER_NUM; i++)
    {
        if ((PPP_CB_STATE_USED == g_astPppPool[i].usState)
           && (g_astPppPool[i].usPeerId == usDynAAAIndex)
           && (M_DIAMAUTH_DYNAAA_AAA == g_astPppPool[i].ucAAAType))
        {
            ulCounter++;
            if (ulCounter % 10 == 0)
            {
                vos_printf("\r\n");
            }
            vos_printf("%6u", i);
        }
    }

    return;
}
#if 0
/**************************************************************************
 * Function     : SRIfmDevStart                                            *
 * Description  : 模拟物理层上报UP                *
 * Input        :                                                          *
 *                LONG argc : the number of argument                       *
 *                CHAR * argv[] : the arguments string                     *
 * Output       : None                                                     *
 * Return       : VOID                                                     *
 * Other        : None                                                     *
 ***************************************************************************/
VOID SRPppShowInfo( VOS_UINT32 argc, CHAR * argv []   )
{
    /*added by hyj for b02*/
    VOS_UINT32 ulIndex;
    VOS_UINT32 i = 0;

    if ((0 == argc) || ((argc >= 1) && !VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
        vos_printf ( "\r\ndisplay PPP info.");
        vos_printf ( "\r\nUsage: ppp show { fsm | statisc | nonull | bkp |routinebkp |l2tp |index |clear}");
        return;
    }

    if (!VOS_StrCmp(argv[0], "fsm"))
    {
        if ((1 == argc) || (!VOS_StrCmp(argv[1], "lcp")))
        {
            vos_printf("\r\nLCP FSM counter:");
            PPP_ShowFsmStat(g_ulPppFsmStat[0]);
        }
        if ((1 == argc) || (!VOS_StrCmp(argv[1], "ipcp")))
        {
            vos_printf("\r\nIPCP FSM counter:");
            PPP_ShowFsmStat(g_ulPppFsmStat[1]);
        }
        if ((1 == argc) || (!VOS_StrCmp(argv[1], "ccp")))
        {
            vos_printf("\r\nCCP FSM counter:");
            PPP_ShowFsmStat(g_ulPppFsmStat[2]);
        }
        if ((1 == argc) || (!VOS_StrCmp(argv[1], "ipv6cp")))
        {
            vos_printf("\r\nIPV6CP FSM counter:");
            PPP_ShowFsmStat(g_ulPppFsmStat[3]);
        }
        if ((1 == argc) || (!VOS_StrCmp(argv[1], "vsncp")))
        {
            vos_printf("\r\nVSNCP FSM counter:");
            PPP_ShowFsmStat(g_ulPppFsmStat[4]);
        }

    }

    if ((argc == 1) && !VOS_StrCmp(argv[0], "statisc"))
    {
        PPP_DbgShowCnt();
    }

    if ((argc == 2) && !VOS_StrCmp(argv[0], "dynaaa"))
    {
#if 0
        /* 输入参数的合法性检查 */
        if (VOS_OK != _VerifyAndCvtUlong(argv[1], 0, 520, &ulIndex))
        {
            VOS_OutPrintf("\r\nIndex value %lu error! it must be more than 0 and less then %u",
                          ulIndex, 520);
            return;
        }
#endif
        PPP_ShowRPIndexByDynAAAIndex((VOS_UINT16)ulIndex);
        return;
    }

    if ((argc == 1) && !VOS_StrCmp(argv[0], "clear"))
    {
        PPP_ClearCnt();

        vos_printf("\r\n Clear success!!");
    }

    if ((argc == 1) && !VOS_StrCmp(argv[0], "nonull"))
    {
        for (ulIndex = 1; ulIndex <= PPP_MAX_USER_NUM; ulIndex++)/*WGGSN_B03_L2TP_PPPC*/
        {
            if (PPP_CB_STATE_USED == g_astPppPool[ulIndex].usState)
            {
                if (0 == i % 10)
                {
                    vos_printf("\r\n");
                }

                vos_printf("%6lu", ulIndex);
                i++;
            }
        }

        vos_printf("\r\nok\r\n");
    }

    if ((argc == 1) && !VOS_StrCmp(argv[0], "routinebkp"))
    {
        VOS_UINT32 ulStrLen = 0;
        VOS_UINT32 ulCount = 0;
        CHAR ucTemp[200] = {0};

        vos_printf("\r\ng_ulPppRoutineBkpHeadIndex: %6lu", g_ulPppRoutineBkpHeadIndex);
        vos_printf("\r\ng_ulPppRoutineBkpCurIndex: %6lu", g_ulPppRoutineBkpCurIndex);

        ulIndex = g_ulPppRoutineBkpHeadIndex;
        while (ulIndex)
        {
            ulStrLen += VOS_sprintf(ucTemp + ulStrLen, "%6lu ", ulIndex);
            ulIndex = g_stPppChangedInfoBkp[ulIndex].ulNextIndex;
            if (0 == (++ulCount)%16 )
            {
                vos_printf("\r\n%s", ucTemp);
                ulStrLen = 0;
            }
        }

        vos_printf("\r\nCount = %lu", ulCount);
    }

    /*WGGSN_B03_L2TP_PPPC*/
    if ((argc == 1) && !VOS_StrCmp(argv[0], "l2tp"))
    {
        VOS_UINT32 ulUsertemp = 0;


#if 0
        /*lint -e746*/
        if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
        {
        }
        /*lint +e746*/
        else
        {
#endif
            for (ulIndex = 1; ulIndex <= PPP_MAX_USER_NUM; ulIndex++)
            {
                if ((PPP_CB_STATE_USED == g_astPppPool[ulIndex].usState)
                    && (0 == g_astPppPool[ulIndex].bPppClient)
                    && (0 == g_astPppPool[ulIndex].bPppMode))
                {
                    ulUsertemp++;
                }

            }

            vos_printf("\r\nL2tpUserNum: %lu", ulUsertemp);
#if 0
        }
#endif
        vos_printf("\r\nok\r\n");
    }

    if ((argc == 1) && !VOS_StrCmp(argv[0], "dmpuinfo"))
    {
        PPP_DbgShowDmpuInfo();
    }

    if ((argc == 2) && !VOS_StrCmp(argv[0], "index"))
    {
        ulIndex = (VOS_UINT32)atoi(argv[1]);
        vos_printf("\r\nShow PPP, index: %lu", ulIndex);

        (VOID)PPP_DbgShowPppInfo(ulIndex);
    }
}

VOID SRPppShowCBInfo( VOS_UINT32 argc, CHAR * argv []   )
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulSwitch = 0;
    VOS_UINT32 ulCounter = 0;
    VOS_UINT32 ulNegoCounter = 0;
    VOS_UINT32 ulPDNNegoCounter = 0;
    VOS_UINT32 ulRPNegoCounter = 0;
    VOS_UINT32 ullcpCounter = 0;
    VOS_UINT32 ulipcpCounter = 0;
    VOS_UINT32 ulchapCounter = 0;
    VOS_UINT32 ulIpv6cpCnt = 0;
    VOS_UINT32 ulpapCounter = 0;
    VOS_UINT32 ulccpCounter = 0;
    VOS_UINT32 ulconfigcounter = 0;
    VOS_UINT32 uleapCounter = 0;
    PPP_NEGO_NODE_S *pstNegoNode = g_pstPppNegoList;
    PPP_NEGO_NODE_S *pstPDNNegoNode = g_pstPppPDNNegoList;
    PPP_NEGO_NODE_S *pstRPNegoNode = g_pstPppRPNegoList;

    if (((argc >= 1) && !VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
        vos_printf ( "\r\nShow PPP control block summary info.");
        vos_printf ( "\r\nUsage: ppp cbinfo [switch]"
                     "\r\n       1: show g_pstPppPool"
                     "\r\n       2: show g_pstPppNegoList"
                     "\r\n       3: show g_pstPDNPppNegoList"
        );
        return;
    }

    if (argc == 1)
    {
        ulSwitch = (VOS_UINT32)atoi(argv[0]);
    }

    if (ulSwitch > 4)
    {
        vos_printf("\r\n Err paramater!");
    }

    if (ulSwitch == 1)
    {
        vos_printf("\r\nPPPPool:");
    }

    for (i = 1; i <= PPP_MAX_USER_NUM; i++)
    {
        if (PPP_CB_STATE_USED == g_astPppPool[i].usState)
        {
            if (ulSwitch == 1)
            {
                if (ulCounter % 10 == 0)
                {
                    vos_printf("\r\n");
                }

                vos_printf("%6lu", i);
            }

            ulCounter++;
        }

        if (PPP_CB_STATE_USED == g_astPppLcpPool[i].ucUsedFlag)
        {
            ullcpCounter++;
        }

        if (PPP_CB_STATE_USED == g_astPppIpcpPool[i].ucUsedFlag)
        {
            ulipcpCounter++;
        }

        if (PPP_CB_STATE_USED == g_astPppIpv6cpPool[i].ucUsedFlag)
        {
            ulIpv6cpCnt++;
        }

        if (PPP_CB_STATE_USED == g_astPppChapPool[i].ucUsed)
        {
            ulchapCounter++;
        }

        if (PPP_CB_STATE_USED == g_astPppPapPool[i].ucUsed)
        {
            ulpapCounter++;
        }
#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
        if (PPP_CB_STATE_USED == g_astPppEapPool[i].ucUsed)
        {
            uleapCounter++;
        }
#endif
        if (PPP_CB_STATE_USED == g_astPppCcpPool[i].ucUsed)
        {
            ulccpCounter++;
        }
        if (PPP_CB_STATE_USED == g_astPppConfifPool[i].bUsedFlag)
        {
            ulconfigcounter++;
        }
    }

    if (ulSwitch == 2)
    {
        ulNegoCounter = 0;
        vos_printf("\r\nPPPNegoList:");
    }

    while (pstNegoNode)
    {
        if (ulSwitch == 2)
        {
            if (ulNegoCounter % 10 == 0)
            {
                vos_printf("\r\n");
            }

            vos_printf("%u[%u]  ", pstNegoNode->ulRpIndex, pstNegoNode->ucNodeType);
        }

        ulNegoCounter++;
        pstNegoNode = pstNegoNode->pNext;
    }

    if (ulSwitch == 3)
    {
        ulPDNNegoCounter = 0;
        vos_printf("\r\nPPPPDNNegoList:");

    }

    while (pstPDNNegoNode)
    {
        if (ulSwitch == 3)
        {
            if (ulPDNNegoCounter % 10 == 0)
            {
                vos_printf("\r\n");
            }

            vos_printf("%u-%u[%u]  ", pstPDNNegoNode->ulPDNIndex, pstPDNNegoNode->ulRpIndex, pstPDNNegoNode->ucNodeType);
        }

        ulPDNNegoCounter++;
        pstPDNNegoNode = pstPDNNegoNode->pNext;
    }

    if (ulSwitch == 4)
    {
        ulRPNegoCounter = 0;
        vos_printf("\r\nPPPRPNegoList:");

    }

    while (pstRPNegoNode)
    {
        if (ulSwitch == 4)
        {
            if (ulRPNegoCounter % 10 == 0)
            {
                vos_printf("\r\n");
            }

            vos_printf("%u-%u[%u]  ", pstRPNegoNode->ulRpIndex, pstRPNegoNode->ulPDNIndex, pstRPNegoNode->ucNodeType);
        }

        ulRPNegoCounter++;
        pstRPNegoNode = pstRPNegoNode->pNext;
    }

    vos_printf("\r\ng_pstPppPool: %p\tg_pstPppNegoList: %p g_pstPppPDNNegoList: %p g_pstPppRPNegoList: %p", g_astPppPool, g_pstPppNegoList, g_pstPppPDNNegoList, g_pstPppRPNegoList);
    vos_printf("\r\nPoolCounter: %8u\tNegoListCounter: %8u PDNNegoCounter : %8u RPNegoCounter : %8u", ulCounter, ulNegoCounter, ulPDNNegoCounter, ulRPNegoCounter);
    vos_printf("\r\n g_astPppLcpPool: %p\tusednumber: %8u", g_astPppLcpPool, ullcpCounter);
    vos_printf("\r\n g_astPppIpcpPool: %p\tusednumber: %8u", g_astPppIpcpPool, ulipcpCounter);
    vos_printf("\r\n g_astPppIpv6cpPool: %p\tusednumber: %8u", g_astPppIpv6cpPool, ulIpv6cpCnt);
    vos_printf("\r\n g_astPppChapPool: %p\tusednumber: %8u", g_astPppChapPool, ulchapCounter);
    vos_printf("\r\n g_astPppPapPool: %p\tusednumber: %8u", g_astPppPapPool, ulpapCounter);
#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
    vos_printf("\r\n g_astPppEapPool: %p\tusednumber: %8u", g_astPppEapPool, uleapCounter);
#endif
    vos_printf("\r\n g_astPppCcpPool: %p\tusednumber: %8u", g_astPppCcpPool, ulccpCounter);
    vos_printf("\r\n g_astPppConfifPool: %p\tusednumber: %8u", g_astPppConfifPool, ulconfigcounter);

    return;
}
#endif

VOID StartPPPRego( VOS_UINT32 argc, CHAR * argv []   )
{
    VOS_UINT32 ulA10Index = 0;

    /*lint -e746*/
    if (argc != 1)
    {
#if 0
        OutString ( "\r\n Input Error!");
#endif
        return;
    }

    if ((!VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
#if 0
        OutString ( "\r\n input A10 index, and the A10 must be active");
#endif
        return;
    }
#if 0
    /*lint +e746*/
    if (VOS_OK != _VerifyAndCvtUlong( argv[0], 1, PPP_MAX_USER_NUM, &ulA10Index ))
    {
        VOS_OutPrintf ( "\r\n Input Error!");
        return;
    }
#endif
    (VOID)PPP_Shell_ISLIoCtl( ulA10Index, ISLRENEGO, NULL);

    return;
}
VOID PPP_SNMP_AlarmPrint()
{
    vos_printf("\r\n g_stPppA11AlarmLink.ulAlarmCount: %lu", g_stPppA11AlarmLink.ulAlarmCount);
    if(g_stPppA11AlarmLink.pHead != NULL)
    {
        vos_printf("\r\n (g_stPppA11AlarmLink.pHead)->ucIMSI: %s", (g_stPppA11AlarmLink.pHead)->stNodeInfo.ucIMSI);
        vos_printf("\r\n (g_stPppA11AlarmLink.pEnd)->ucIMSI: %s", (g_stPppA11AlarmLink.pEnd)->stNodeInfo.ucIMSI);
    }

    return;
}
VOID PPP_LAP_Debug()
{

    return;
}



VOID PPP_PrintPerfVar( VOS_UINT32 argc, CHAR * argv [] )
{
    /* PPP_LAP_Debug(); */

    /* PPP_SNMP_AlarmPrint(); */
#if 0
    OutString ( "\r\n\nPrint Performance Var.......\r\n");
#endif
    if(0 != g_stPppPerfStatistic.ulReceiveNego)
    {
        vos_printf("\r\n pulReceiveNego: %lu", g_stPppPerfStatistic.ulReceiveNego);
        vos_printf("\r\n pulReceiveNegoErr: %lu", g_stPppPerfStatistic.ulReceiveNegoErr);
        vos_printf("\r\n pulSendNego: %lu", g_stPppPerfStatistic.ulSendNego);

        vos_printf("\r\n pulLcpTotal: %lu", g_stPppPerfStatistic.ulLcpTotal);
        vos_printf("\r\n pulLcpSuccess: %lu", g_stPppPerfStatistic.ulLcpSuccess);
        vos_printf("\r\n pulIpcpTotal: %lu", g_stPppPerfStatistic.ulIpcpTotal);
        vos_printf("\r\n pulIpcpSuccess: %lu", g_stPppPerfStatistic.ulIpcpSuccess);

        vos_printf("\r\n pulPapTotal: %lu", g_stPppPerfStatistic.ulPapTotal);
        vos_printf("\r\n pulPapSuccess: %lu", g_stPppPerfStatistic.ulPapSuccess);
        vos_printf("\r\n pulChapTotal: %lu", g_stPppPerfStatistic.ulChapTotal);
        vos_printf("\r\n pulChapSuccess: %lu", g_stPppPerfStatistic.ulChapSuccess);
        vos_printf("\r\n pulPppNegoTotalTime: %lu", g_stPppPerfStatistic.ulPppNegoTotalTime);
        vos_printf("\r\n pulPppNegoNum: %lu", g_stPppPerfStatistic.ulPppNegoNum);
    }

    return;
}



VOID PPP_ShowEcho( VOS_UINT32 argc, CHAR * argv [] )
{
    vos_printf( "\r\n PPP Echo Retransmit:  %lu<cr>", g_ulPppEchoRetransmit);
    vos_printf( "\r\n PPP Echo Timeout:  %lu<cr>", g_ulPppEchoTimeout);
}


VOID PPP_SetDebugInfo( VOS_UINT32 argc, CHAR * argv [] )
{

    if ((1 != argc) || (!VOS_StrCmp ( argv [ argc - 1 ], "?")))
    {
       vos_printf ( "\r\n set write log on / off ");
       vos_printf ( "\r\n Usage: ppp logonoff on | off | show");
       return;
    }

    if (!VOS_StrCmp(argv[0], "on"))
    {
        g_ulPppAAAWritelogFlag = 1;
        vos_printf( "\r\n turn write log on");
    }
    else if (!VOS_StrCmp(argv[0], "off"))
    {
        g_ulPppAAAWritelogFlag = 0;
        vos_printf( "\r\n turn write log off");
    }
    else if (!VOS_StrCmp(argv[0], "show"))
    {
        if (0 == g_ulPppAAAWritelogFlag)
        {
            vos_printf( "\r\n write log is off");
        }
        else if (1 == g_ulPppAAAWritelogFlag)
        {
            vos_printf( "\r\n write log is on");
        }
    }
    else
    {
        vos_printf( "\r\n write logonoff parameter error!");
    }

    vos_printf( "\r\n ok \r\n");
}

/*****************************************************************************
函 数 名  : PPP_PrintMemInfo
功能描述  : 打印PPP模块结构内存信息
输入参数  : UCHAR *pucStructName
          VOS_UINT32 ulUnitSize
          VOS_UINT32 ulUnitNum
          VOS_UINT32 ulMemSize
          UCHAR *pucMemType
          UCHAR ucStatic
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年2月1日
 作    者   : baoxin 144601
 修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_PrintMemInfo(UCHAR *pucStructName, VOS_UINT32 ulUnitSize, VOS_UINT32 ulUnitNum, VOS_UINT32 ulMemSize, UCHAR *pucMemType, UCHAR ucStatic)
{
    if ((NULL == pucStructName) || (NULL == pucMemType))
    {
     (VOID)vos_printf("\r\n print info is wrong\r\n");
     return;
    }

    ulMemSize = ulMemSize >> 20;

    if (ulMemSize > 0)
    {
     (VOID)vos_printf("%23s,%10lu,%12lu,%8lu,%12s,%8c,%12lx,%8s\r\n",pucStructName,ulUnitSize,ulUnitNum,
         ulMemSize, pucMemType, ucStatic, MID_PPPC, "AM");
    }

    return ;
}

/*****************************************************************************
函 数 名  : PPP_DbgShowMemInfo
功能描述  : 打印PPP模块内存信息
输入参数  : VOS_UINT32 argc
          CHAR* argv[]
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2013年2月28日
 作    者   : zhaichao 00129699
 修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_DbgShowMemInfo(VOS_UINT32 argc, CHAR* argv[])
{
    if (0 == PPP_SELF_CSI)
    {
        return;
    }

    (VOID)vos_printf("\r\n *************************************The PPP memory info Begin*********************************************************");

    (VOID)vos_printf("\r\n    StructName,            UnitSize,   UnitNum,    ulMemSize,  MemType,    Static, Mid,      Sub-System, CPU, vCPU\r\n");

    //D板和E板
    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 start */
    PPP_PrintMemInfo((UCHAR *)"g_ulPppDBGStatisc", sizeof(VOS_UINT32), PPP_DBG_BUTT, sizeof(VOS_UINT32)*PPP_DBG_BUTT, (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_ulPppFsmStat", sizeof(VOS_UINT32), 5 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT,
                 sizeof(VOS_UINT32) * 5 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT, (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_ucPppSendPacketHead", PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER, 1,
                 PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER, (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_ucPppRcvPacketHead", PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER, 1,
                 PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER, (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_pstPppPool", sizeof(PPPINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_astPppLcpPool", sizeof(PPPLCPINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPLCPINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_astPppIpcpPool", sizeof(PPPIPCPINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPIPCPINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_astPppIpv6cpPool", sizeof(PPPIPV6CPINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPIPV6CPINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_astPppPapPool", sizeof(PPPPAPINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPPAPINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_astPppChapPool", sizeof(PPPCHAPINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPCHAPINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPP_PrintMemInfo((UCHAR *)"g_astPppEapPool", sizeof(PPPC_EAP_INFO_STRU), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPC_EAP_INFO_STRU) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');
#endif

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPP_PrintMemInfo((UCHAR *)"g_astPppCcpPool", sizeof(PPP_CCP_INFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPP_CCP_INFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');
#endif

    PPP_PrintMemInfo((UCHAR *)"g_astPppConfifPool", sizeof(PPPCONFIGINFO_S), PPP_MAX_USER_NUM + 1,
                 sizeof(PPPCONFIGINFO_S) * (PPP_MAX_USER_NUM + 1), (UCHAR *)"SC", 'N');

    PPP_PrintMemInfo((UCHAR *)"g_stPppPerfStatistic", sizeof(PPPPERFSTATISTIC_S), 1,
                 sizeof(PPPPERFSTATISTIC_S), (UCHAR *)"SC", 'N');

    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 end   */

    (VOID)vos_printf("\r\n *************************************The PPP memory info END***********************************************************\r\n ");

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
