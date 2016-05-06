

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "AtCheckFunc.h"
#include "ATCmdProc.h"
#include "AtDataProc.h"
#include "Taf_Tafm_Remote.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#include "AtTestParaCmd.h"

#include "TafAppMma.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_TESTPARACMD_C
/*lint +e767 +e960*/


/*****************************************************************************
 函 数 名  : At_TestCgdcont
 功能描述  : cgdcont测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
  2.日    期   : 2011年12月19日
    作    者   : c00173809
    修改内容   : PS融合项目
  3.日    期   : 2012年04月10日
    作    者   : s62952
    修改内容   : 问题单号:DTS2012040902843
  3.日    期   : 2012年05月03日
    作    者   : w00199382
    修改内容   : 问题单号:DTS2012042602550
  4.日    期   : 2012年5月26日
    作    者   : A00165503
    修改内容   : DTS2012052404203: +CGDCONT命令增加对<CID 0>的支持
  5.日    期   : 2012年8月10日
    作    者   : z60575
    修改内容   : DTS2012081006711: 添加对IPV6能力的判断
  6.日    期   : 2013年05月25日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
  7.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增参数
*****************************************************************************/
VOS_UINT32 At_TestCgdcont(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0-31),\"IP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (0-31),\"IPV6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (0-31),\"IPV4V6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
#endif

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-31),\"PPP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11),\"IP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (1-11),\"IPV6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (1-11),\"IPV4V6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
#endif

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (1-11),\"PPP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCgdscont
 功能描述  : cgdscont测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
  2.日    期   : 2011年12月19日
    作    者   : c00173809
    修改内容   : PS融合项目
  3.日    期   : 2012年3月5日
    作    者   : c00173809
    修改内容   : DTS2012010604900,Cgdscont测试命令GU和L模式需要区分CID的最大取值范围
  4.日    期   : 2011年5月2日
    作    者   : w00199382
    修改内容   : DTS2012042803139去除字符串后多余逗号
  5.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目,修改主PDP参数范围
*****************************************************************************/
VOS_UINT32 At_TestCgdscont(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: (1-31),(0-31),(0-2),(0-3)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: (1-11),(0-11),(0-2),(0-3)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_TestCgtft
 功能描述  : cgtft测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
  2.日    期   : 2012年3月24日
    作    者   : c00173809
    修改内容   : DTS2012031901946,在测试命令中删除PPP协议
  3.日    期   : 2012年8月10日
    作    者   : z60575
    修改内容   : DTS2012081006711: 添加对IPV6能力的判断
  4.日    期   : 2015年9月28日
    作    者   : W00316404
    修改内容   : R11 TFT 协议升级
*****************************************************************************/
VOS_UINT32 At_TestCgtft(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    if (AT_IsSupportReleaseRst(AT_RELEASE_R11))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: \"IP\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3),\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: \"IP\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        if (AT_IsSupportReleaseRst(AT_RELEASE_R11))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: \"IPV6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3),\r\n",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: \"IPV4V6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3),",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: \"IPV6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)\r\n",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: \"IPV4V6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        }
    }
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCgact
 功能描述  : cgact测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCgact(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCgcmod
 功能描述  : cgcmod测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
  2.日    期   : 2011年12月19日
    作    者   : 黎客来/00130025
    修改内容   : 问题单DTS2011120604361，CGEQNEG测试命令返回错误,CGCMOD返回错误
*****************************************************************************/
VOS_UINT32 At_TestCgcmod(VOS_UINT8 ucIndex)
{


    /* CGEQNEG的测试命令和CGCMODE的返回值相同，使用相同的函数 */
   return At_TestCgeqnegPara(ucIndex);


}

/*****************************************************************************
 函 数 名  : At_TestCgpaddr
 功能描述  : CGPADDR测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : c00173809
    修改内容   : DTS2012010604900
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，删除卡状态判断
*****************************************************************************/
VOS_UINT32 At_TestCgpaddr(VOS_UINT8 ucIndex)
{

    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetPdpContextInfo(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGPADDR_TEST;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 函 数 名  : At_TestCgautoPara
 功能描述  : +CGAUTO测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月09日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 At_TestCgautoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestAuhtdata
 功能描述  : Auhtdata测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目

  2.日    期   : 2012年3月5日
    作    者   : c00173809
    修改内容   : DTS2012010604900,authdata测试命令GU和L模式需要区分CID的最大取值范围

  3.日    期   : 2013年12月25日
    作    者   : A00165503
    修改内容   : DTS2013122403650: ^AUTHDATA命令支持CID0
*****************************************************************************/
VOS_UINT32 At_TestAuhtdata(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: (0-31),(0-2),,",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11),(0-2),,",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestNdisconn
 功能描述  : Ndisconn测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
  2.日    期   : 2012年5月7日
    作    者   : l60609
    修改内容   : DTS2012050501603:CID范围错误
*****************************************************************************/
VOS_UINT32 At_TestNdisconn(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-20),(0,1),,,,(0,1,2,3)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-16),(0,1),,,,(0,1,2,3)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestNdisDup
 功能描述  : NdisDup测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00184452
    修改内容   : AT移植项目
  2.日    期   : 2012年5月7日
    作    者   : l60609
    修改内容   : DTS2012050501603:CID范围错误
*****************************************************************************/
VOS_UINT32 At_TestNdisDup(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-20),(0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-16),(0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_TestCgeqos
 功能描述  : cgeqos测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : c00184452
    修改内容   : PS融合项目

  2.日    期   : 2015年10月22日
    作    者   : W00316404
    修改内容   : R11 升级
*****************************************************************************/
VOS_UINT32 At_TestCgeqos(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31),(0-9),(0-10485760),(0-10485760),(0-10485760),(0-10485760)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_TestCgeqosrdp
 功能描述  : cgeqosrdp测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : c00184452
    修改内容   : PS融合项目
*****************************************************************************/
VOS_UINT32 At_TestCgeqosrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_TestCgcontrdp
 功能描述  : cgcontrdp测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : c00184452
    修改内容   : PS融合项目
*****************************************************************************/
VOS_UINT32 At_TestCgcontrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_TestCgscontrdp
 功能描述  : cgscontrdp测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : c00184452
    修改内容   : PS融合项目
*****************************************************************************/
VOS_UINT32 At_TestCgscontrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : At_TestCgtftrdp
 功能描述  : cgtftrdp测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月8日
    作    者   : c00184452
    修改内容   : PS融合项目
*****************************************************************************/
VOS_UINT32 At_TestCgtftrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
/*****************************************************************************
 函 数 名  : AT_TestChrgEnablePara
 功能描述  : ^TCHRENABLE=? 查询是否需要补电
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月16日
    作    者   : 崔军强
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestChrgEnablePara(VOS_UINT8 ucIndex)
{
    /* DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合 */
    VOS_INT32                           lChargeEnable = 0;

    lChargeEnable = mdrv_misc_get_charge_state(); /* BSP_TBAT_CHRStGet()) */
    /* 只有TRUE/FLASE的返回值是有效的 */
    if((lChargeEnable == TRUE)||( lChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  "%s:%d",
                                                  "^TCHRENABLE",
                                                  lChargeEnable);
        return AT_OK;
    }
    /* DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合 */
    else
    {
        return AT_ERROR;
    }
}
/* DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合 */

/*****************************************************************************
 函 数 名  : AT_TestCposrPara
 功能描述  : +CPOSR测试命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月27日
    作    者   : y00213812
    修改内容   : A-GPS项目新增函数
  2.日    期   : 2012年8月13日
    作    者   : l60609
    修改内容   : MUX:增加MUX通道的处理

*****************************************************************************/
VOS_UINT32 AT_TestCposrPara(VOS_UINT8 ucIndex)
{
    /* 通道检查 */
    /* Modified by L60609 for MUX，2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX，2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* 打印输出+CPOSR支持的参数设置范围 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s: (0,1)",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestCmutPara
 功能描述  : +CMUT=? 测试命令
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestCmutPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



/* 如下函数并非此项目中新增, 只是从AtExtendCmd.c文件中移动到此文件而已 */

/*****************************************************************************
 函 数 名  : At_TestVtsPara
 功能描述  : VTS测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestVtsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "+VTS: (0-9,A-D,*,#)");
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCuus1Para
 功能描述  : CUUS1测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCuus1Para(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "+CUUS1:(0,1),(0,1),(0-6),(0-4),(0-3)");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCcwaPara
 功能描述  : CCWA测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCcwaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCcfcPara
 功能描述  : CCFC测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCcfcPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-5)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCusdPara
 功能描述  : CUSD测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCusdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-2)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCpwdPara
 功能描述  : CPWD测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目

  2.日    期   : 2012年5月7日
    作    者   : A00165503
    修改内容   : DTS2012050405948: +CPWD测试命令修订
*****************************************************************************/
VOS_UINT32 At_TestCpwdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"P2\",8),(\"SC\",8),(\"AO\",4),(\"OI\",4),(\"OX\",4),(\"AI\",4),(\"IR\",4),(\"AB\",4),(\"AG\",4),(\"AC\",4)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestClckPara
 功能描述  : CLCK测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : AT移植项目

  2.日    期   : 2012年5月7日
    作    者   : A00165503
    修改内容   : DTS2012050405948: +CLCK测试命令修订
  3.日    期   : 2015年4月7日
    作    者   : w00316404
    修改内容   : M project A characeristic AT part
*****************************************************************************/
VOS_UINT32 At_TestClckPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"SC\",\"AO\",\"OI\",\"OX\",\"AI\",\"IR\",\"AB\",\"AG\",\"AC\",\"FD\",\"PN\",\"PU\",\"PP\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestCpbsPara
 功能描述  : CPBS测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestCpbsPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId, 1))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_TestCpbrPara
 功能描述  : CPBR测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestCpbrPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 函 数 名  : AT_TestCnmaPara
 功能描述  : +CNMA命令的测试命令
 输入参数  : VOS_UINT8 ucIndex  用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32 ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年2月20日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_TestCnmaPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if(AT_CMGF_MSG_FORMAT_PDU == pstSmsCtx->enCmgfMsgFormat)    /* TEXT方式参数检查 */
    {
        gstAtSendData.usBufLen = (TAF_UINT16)VOS_sprintf((TAF_CHAR*)pgucAtSndCodeAddr,
                                          "%s: (0-2)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestCpasPara
 功能描述  : CPAS测试命令
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestCpasPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0-5)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


    return AT_OK;
}
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
/*****************************************************************************
 函 数 名  : AT_TestCscbPara
 功能描述  : +CSCB命令的测试命令
 输入参数  : VOS_UINT8 ucIndex  用户索引
 输出参数  : 无
 返 回 值  : VOS_UINT32 ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestCscbPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,"%s:(0,1)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_TestCpmsPara
 功能描述  : +CPMS命令的测试命令
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年2月20日
    作    者   : l60609
    修改内容   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_TestCpmsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    usLength  = 0;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (MN_MSG_ME_STORAGE_ENABLE == pstSmsCtx->enMsgMeStorageStatus)
    {
        usLength = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,
                    "%s: (\"SM\",\"ME\"),(\"SM\",\"ME\"),(\"SM\",\"ME\")",
                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        usLength = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,
                    "%s: (\"SM\"),(\"SM\"),(\"SM\")",
                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : AT_TestCsgIdSearchPara
 功能描述  : csg列表搜网查询命令
 输入参数  : ucIndex - 索引
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 AT_TestCsgIdSearchPara(VOS_UINT8 ucIndex)
{
    /* 核间通信最大缓存4K,需要分段查询分段上报结果 */
    TAF_MMA_PLMN_LIST_PARA_STRU         stPlmnListPara;

    stPlmnListPara.usQryNum    = TAF_MMA_MAX_CSG_ID_LIST_NUM;
    stPlmnListPara.usCurrIndex = 0;

    if (VOS_TRUE == TAF_MMA_CsgListSearchReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPlmnListPara))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSG_LIST_SEARCH;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
#endif


/*****************************************************************************
 函 数 名  : At_TestCopsPara
 功能描述  : cops测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00173809
    修改内容   : AT移植项目
  2.日    期   : 2011年10月24日
    作    者   : f00179208
    修改内容   : AT移植项目:修改列表搜的定时器保护时间
  3.日    期   : 2015年3月4日
    作    者   : b00269685
    修改内容   : 改为分段上报
*****************************************************************************/
VOS_UINT32 At_TestCopsPara(TAF_UINT8 ucIndex)
{
    TAF_MMA_PLMN_LIST_PARA_STRU             stPlmnListPara;

    stPlmnListPara.usQryNum    = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;
    stPlmnListPara.usCurrIndex = 0;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == At_CheckCurrRatModeIsCL((VOS_UINT8)(gastAtClientTab[ucIndex].usClientId)))
    {
        return AT_CME_OPERATION_NOT_ALLOWED_IN_CL_MODE;
    }
#endif

    if (VOS_TRUE == Taf_PhonePlmnList(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPlmnListPara))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_TEST;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
 函 数 名  : At_TestCpolPara
 功能描述  : cpol测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : c00173809
    修改内容   : AT移植项目
  2.日    期   : 2013年2月22日
    作    者   : l60609
    修改内容   : DSDA PHASE III
  3.日    期   : 2015年02月05日
    作    者   : y00307564
    修改内容   : Itertion 8 修改
*****************************************************************************/
VOS_UINT32 At_TestCpolPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    /* 参数检查 */
    if (AT_CMD_OPT_TEST_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    ulRst = TAF_MMA_TestCpolReq(WUEPS_PID_AT,
                                gastAtClientTab[ucIndex].usClientId,
                                0,
                                pstNetCtx->enPrefPlmnType);

    if (VOS_TRUE == ulRst)
    {
        /* 设置AT模块实体的状态为等待异步返回 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_TEST;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
 函 数 名  : At_TestCgeqnegPara
 功能描述  : +CGEQNEQ命令的测试命令
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : 范晶/00179208
    修改内容   : 新生成函数
  2.日    期   : 2011年12月19日
    作    者   : 黎客来/00130025
    修改内容   : 问题单DTS2011120604361，CGEQNEG测试命令返回错误
*****************************************************************************/
VOS_UINT32 At_TestCgeqnegPara(VOS_UINT8 ucIndex)
{

    /*CGEQNEG的测试命令和CGACT的查询命令的功能类似,都要获取当前各CID的激活
    情况,向TAF查询当前各CID的激活情况*/

    if ( VOS_OK != TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) )
    {
        return AT_ERROR;
    }

    /*发送查询消息成功后,将命令状态改为CGEQNEG*/
    if(AT_SUCCESS != At_StartTimer(AT_QRY_PARA_TIME,ucIndex))
    {
        AT_ERR_LOG("At_TestParaCmd:ERROR:Start Timer");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQNEG_TEST;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */

    /*接下来到TAF事件上报的地方,获取当前哪些CID被激活,并打印当前哪些CID被激活.*/


}


/*****************************************************************************
 函 数 名  : At_TestCgeqreqPara
 功能描述  : +CGEQREQ命令的测试命令
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : 范晶/00179208
    修改内容   : 新生成函数
  2.日    期   : 2011年11月24日
    作    者   : f62575
    修改内容   : DTS2011112307607,合入AT融合方案后不支持42M速率问题
  3.日    期   : 2011年12月19日
    作    者   : c00173809
    修改内容   : PS融合项目
  4.日    期   : 2012年03月17日
    作    者   : w00199382
    修改内容   : DTS2012031603201测试命令乱码
*****************************************************************************/
VOS_UINT32 At_TestCgeqreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: \"IP\",%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING,
                                        gaucAtCrLf);

#if (FEATURE_ON == FEATURE_IPV6)

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s: \"IPV6\",%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING,
                                        gaucAtCrLf);


    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s: \"IPV4V6\",%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCgansPara
 功能描述  : +CGANS测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCgansPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1),(\"NULL\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCgansExtPara
 功能描述  : ^CGANS命令的测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_TestCgansExtPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : At_TestCgdnsPara
 功能描述  : +CGDNS测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月24日
    作    者   : f00179208
    修改内容   : AT移植项目
  2.日    期   : 2012年4月30日
    作    者   : z60575
    修改内容   : DTS2012031400889,CGDNS命令需要返回激活的CID
*****************************************************************************/
VOS_UINT32 At_TestCgdnsPara(VOS_UINT8 ucIndex)
{



    /* CGDNS的测试命令和CGCMODE的返回值相同，使用相同的函数 */
    return At_TestCgeqnegPara(ucIndex);

}


/*****************************************************************************
 函 数 名  : At_TestCgdataPara
 功能描述  : +CGDATA测试函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : f00179208
    修改内容   : AT移植项目
*****************************************************************************/
VOS_UINT32 At_TestCgdataPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"NULL\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 函 数 名  : AT_TestCbgPara
 功能描述  : 测试命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : z00214637
    修改内容   : AT^CBG 测试命令处理函数
*****************************************************************************/
VOS_UINT32 AT_TestCbgPara( VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestNCellMonitorPara
 功能描述  : ^NCELLMONITOR测试命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : s00217060
    修改内容   : V9R1_SVLTE: 新增函数
*****************************************************************************/
VOS_UINT32 AT_TestNCellMonitorPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestRefclkfreqPara
 功能描述  : AT^REFCLKFREQ测试命令处理函数
 输入参数  : ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_TestRefclkfreqPara(VOS_UINT8 ucIndex)
{
    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 打印输出^REFCLKFREQ支持的参数设置范围 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s: (0,1)",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : AT_TestCiregPara
 功能描述  : +CIREG=?测试命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_TestCiregPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0-2)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestCirepPara
 功能描述  : +CIREP=?测试命令处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 AT_TestCirepPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
#endif

#if (FEATURE_ON == FEATURE_AT_HSUART)
/*****************************************************************************
 函 数 名  : AT_TestIprPara
 功能描述  : +IPR=?
 输入参数  : ucIndex --- 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestIprPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

#ifdef CONFIG_DIALUP_HSUART_REVISE
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (0,300,600,1200,2400,4800,9600,19200,38400,57600,115200,230400,460800,921600,2764800)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (0,300,600,1200,2400,4800,9600,19200,38400,57600,115200,230400,250000,300000,375000,600000,750000,1000000,3000000)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestIcfPara
 功能描述  : +ICF=?
 输入参数  : ucIndex --- 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestIcfPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (1-6),(0-1)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestIfcPara
 功能描述  : +IFC=?
 输入参数  : ucIndex --- 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestIfcPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (0,2),(0,2)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_TestUECenterPara
 功能描述  : +CEUS=?
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月07日
    作    者   : lwx277467
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestUECenterPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#ifdef  __cplusplus
#if  __cplusplus
  }
  #endif
#endif

