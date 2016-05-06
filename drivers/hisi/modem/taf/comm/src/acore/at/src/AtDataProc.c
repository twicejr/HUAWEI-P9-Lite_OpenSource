

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "AtDataProc.h"
#include "ATCmdProc.h"
#include "AtCsdInterface.h"
#include "AtTafAgentInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_DATAPROC_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/* HiLink模式: 正常模式或网关模式 */
AT_HILINK_MODE_ENUM_U8                  g_enHiLinkMode       = AT_HILINK_NORMAL_MODE;

/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
/* 协议栈发起PDP激活的类型 */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtNdisActPdpType;

/* 协议栈发起PDP激活的类型 */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtFirstNdisActPdpType;

/* 保存NDIS拨号所设置的参数 */
AT_DIAL_PARAM_STRU                      gstAtNdisAddParam   = {0};

/* NDIS PDP实体 */
AT_PDP_ENTITY_STRU                      g_stAtNdisDhcpPara;

/* 保存NDISCONN 命令拨号时的参数, 用于NDISCONN 查询命令 */
AT_NDISCONN_PARA_STRU                   g_stAtNdisConnPara;



/* 协议栈发起PDP激活的类型 */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtAppActPdpType;

/* 协议栈发起PDP激活的类型 */
TAF_PDP_TYPE_ENUM_UINT8                g_enAtAppFirstActPdpType;

/* 保存拨号所设置的参数 */
AT_DIAL_PARAM_STRU                      g_stAtAppDialPara       = {0};

/* APP PDP实体 */
AT_PDP_ENTITY_STRU                      g_stAtAppPdpEntity;

/* RA消息中相关参数 */
AT_IPV6_RA_INFO_STRU                    g_stAtAppRaInfo         = {0};

/* IP*/
VOS_UINT32                              g_ulIpAddr = 0;


/*****************************************************************************
 全局变量名   : g_stFcIdMaptoFcPri
 全局变量功能 : 用于保存指定的FC ID对应的FC Pri

1. 日    期   : 2012年2月24日
   作    者   : L47619
   修改内容   : 新增结构体
*****************************************************************************/
AT_FCID_MAP_STRU                        g_stFcIdMaptoFcPri[FC_ID_BUTT];

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
AT_PS_RMNET_ID_TAB                      g_astPsRmNetIdTab[] =
{
    {MODEM_ID_0, FC_ID_NIC_1, AT_PS_USER_CID_1},
    {MODEM_ID_0, FC_ID_NIC_2, AT_PS_USER_CID_2},
    {MODEM_ID_0, FC_ID_NIC_3, AT_PS_USER_CID_3},
    {MODEM_ID_1, FC_ID_NIC_4, AT_PS_USER_CID_1},
    {MODEM_ID_1, FC_ID_NIC_5, AT_PS_USER_CID_2}
#if (MULTI_MODEM_NUMBER == 3)
    ,
    {MODEM_ID_2, FC_ID_NIC_6, AT_PS_USER_CID_1},
    {MODEM_ID_2, FC_ID_NIC_7, AT_PS_USER_CID_2}
#endif
};
#else
AT_PS_RMNET_ID_TAB                      g_astPsRmNetIdTab[] =
{
    {MODEM_ID_0, FC_ID_NIC_1, AT_PS_USER_CID_1},
    {MODEM_ID_0, FC_ID_NIC_2, AT_PS_USER_CID_2},
    {MODEM_ID_0, FC_ID_NIC_3, AT_PS_USER_CID_3}
};
#endif

/* ^DCONN上报函数表 */
AT_PS_REPORT_CONN_RESULT_STRU           g_astAtRptConnectedResultTab[] =
{
    /* 消息ID */                        /* 消息处理函数 */
    {AT_HSIC1_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC2_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC3_USER,                     AT_PS_ReportDCONN},
    {AT_HSIC4_USER,                     AT_PS_ReportDCONN},
    {AT_APP_USER,                       AT_PS_ReportDCONN}
};

/* ^DEND上报函数表 */
AT_PS_REPORT_END_RESULT_STRU            g_astAtRptEndedResultTab[] =
{
    /* 消息ID */                        /* 消息处理函数 */
    {AT_HSIC1_USER,                     AT_PS_ReportDEND},
    {AT_HSIC2_USER,                     AT_PS_ReportDEND},
    {AT_HSIC3_USER,                     AT_PS_ReportDEND},
    {AT_HSIC4_USER,                     AT_PS_ReportDEND},
    {AT_APP_USER,                       AT_PS_ReportDEND}
};


/* 流控点注册处理函数表 */
AT_PS_REG_FC_POINT_STRU                 g_astAtRegFCPointTab[] =
{
    /* 消息ID */                        /* 消息处理函数 */
    {AT_HSIC1_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC2_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC3_USER,                     AT_PS_RegHsicFCPoint},
    {AT_HSIC4_USER,                     AT_PS_RegHsicFCPoint},
    {AT_APP_USER,                       AT_PS_RegAppFCPoint}
};


/* 流控点去注册处理函数表 */
AT_PS_DEREG_FC_POINT_STRU               g_astAtDeRegFCPointTab[] =
{
    /* 消息ID */                        /* 消息处理函数 */
    {AT_HSIC1_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC2_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC3_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_HSIC4_USER,                     AT_PS_DeRegHsicFCPoint},
    {AT_APP_USER,                       AT_PS_DeRegAppFCPoint}
};

AT_PS_SND_PDP_ACT_IND_STRU              g_astAtSndPdpActIndTab[] =
{
    /* 消息ID */                        /* 消息处理函数 */
    {AT_HSIC1_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC2_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC3_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_HSIC4_USER,                     AT_PS_SndDipcPdpActInd},
    {AT_APP_USER,                       AT_PS_SndRnicPdpActInd}
};

AT_PS_SND_PDP_DEACT_IND_STRU            g_astAtSndPdpDeActIndTab[] =
{
    /* 消息ID */                        /* 消息处理函数 */
    {AT_HSIC1_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC2_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC3_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_HSIC4_USER,                     AT_PS_SndDipcPdpDeactInd},
    {AT_APP_USER,                       AT_PS_SndRnicPdpDeactInd}
};

AT_CHDATA_RNIC_RMNET_ID_STRU            g_astAtChdataRnicRmNetIdTab[] =
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    {AT_CH_DATA_CHANNEL_ID_1, RNIC_RMNET_ID_0, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_2, RNIC_RMNET_ID_1, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_3, RNIC_RMNET_ID_2, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_4, RNIC_RMNET_ID_3, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_5, RNIC_RMNET_ID_4, {0, 0, 0}}
#if (MULTI_MODEM_NUMBER == 3)
    ,
    {AT_CH_DATA_CHANNEL_ID_6, RNIC_RMNET_ID_5, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_7, RNIC_RMNET_ID_6, {0, 0, 0}}
#endif
#else
    {AT_CH_DATA_CHANNEL_ID_1, RNIC_RMNET_ID_0, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_2, RNIC_RMNET_ID_1, {0, 0, 0}},
    {AT_CH_DATA_CHANNEL_ID_3, RNIC_RMNET_ID_2, {0, 0, 0}}
#endif
};

/*****************************************************************************
   3 函数、变量声明
*****************************************************************************/

extern const TAF_CHAR                       *g_PppDialRateDisplay[];

#if (FEATURE_ON == FEATURE_LTE)
extern const TAF_CHAR                       *g_ucLTEDlRateDisplay[];
#endif

extern const VOS_CHAR                       *g_ucDialRateDisplayNv[];

/*****************************************************************************
   4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : AT_PS_SetPsCallErrCause
 功能描述  : 设置PS域拨号错误码
 输入参数  : VOS_UINT16                          usClientId
             TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_SetPsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->enPsErrCause = enPsErrCause;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetPsCallErrCause
 功能描述  : 查询PS域拨号错误码
 输入参数  : VOS_UINT16                          usClientId
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月21日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 AT_PS_GetPsCallErrCause(
    VOS_UINT16                          usClientId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return pstPsModemCtx->enPsErrCause;
}
/*****************************************************************************
 函 数 名  : AT_GetLanAddr32
 功能描述  : 网络序数组--->主机序UINT32(LITTLE_ENDIAN)
 输入参数  : VOS_UINT8                            *pucAddr
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月25日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_GetLanAddr32(
  VOS_UINT8                            *pucAddr
)
{
    VOS_UINT32                          ulAddr;

    ulAddr = *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr++;
    ulAddr <<= 8;
    ulAddr |= *pucAddr;

    return ulAddr;
}


/******************************************************************************
 Function:       AT_DHCPGetIPMask
 Description:    根据IP地址计算子网掩码
 Calls:
 Data Accessed:
 Data Updated:
 Input:         TAF_UINT32 ulIpAddrHL   IP地址   主机序
 Output:
 Return:        TAF_UINT32 ulNetMask    子网掩码 主机序
 Others:
                记住IP地址的bit[0]
                依次循环读取IP地址的每个bit，直到某bit[x]不等于bit[0]
                则掩码主机位为 0--x位
  1.Date        : 2009-08-03
    Author      : S62952
    Modification: Created function
******************************************************************************/
TAF_UINT32 AT_DHCPGetIPMask(
    TAF_UINT32                          ulIpAddrHL
)
{
    /* 11111111.11111111.11111111.11111110*/
    TAF_UINT32 ulMask    = 0xfffffffeU;
    TAF_UINT32 ulIpTemp  = ulIpAddrHL;
    TAF_UINT32 ul1stBit;

    ul1stBit = ulIpTemp & 0x00000001;

    while(0x0 != ulMask)
    {
        ulMask   = ulMask << 1;
        ulIpTemp = ulIpTemp >> 1;

        if (ul1stBit != (ulIpTemp & 0x00000001))
        {
            break;
        }
    }

    return ulMask;
}
/******************************************************************************
 Function:       AT_DHCPGetGateWay
 Description:    根据IP地址，子网掩码计算网关
 Calls:
 Data Accessed:
 Data Updated:
 Input:         VOS_UINT32 ulIpAddrHL   IP地址   主机序
                VOS_UINT32 ulMaskHL     子网掩码 主机序
 Output:
 Return:        VOS_UINT32 ulGateWay    网关 主机序
 Others:
                根据IP+掩码，计算网关，和IP在同一网段即?
   1.Date        : 2009-08-03
    Author      : S62952
    Modification: Created function
******************************************************************************/
VOS_UINT32 AT_DHCPGetGateWay(
    VOS_UINT32                          ulIpAddrHL,
    VOS_UINT32                          ulMaskHL
)
{
    VOS_UINT32 ulGateWay;

    ulGateWay = 0;

    ulGateWay = (ulIpAddrHL & ulMaskHL) + 1;

    while (ulGateWay == ulIpAddrHL)
    {
        ulGateWay ++;
    };

    return ulGateWay;
}

/******************************************************************************
 函数名称: AT_Ipv4AddrAtoi
 功能描述: 把IPV4地址由字符串格式转换成数字格式

 参数说明:
   pcString [in] 字符串格式的IP地址,char * pcString="192.168.0.1"
   pucNumber [out] 数字格式的IP地址,char pucNumber[4]={192,168,0,1};

 返 回 值:
    TODO: ...

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2010-02-02]

  2.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加最后一个地址域的取值范围检查
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulStrLen = 0;
    VOS_UINT32                          ulNumLen = 0;
    VOS_UINT32                          ulDotNum = 0;
    VOS_UINT32                          ulValTmp = 0;
    VOS_UINT8                           aucAddr[4] = {0};


    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if ( ulStrLen > VOS_StrLen("255.255.255.255") )
    {
        return VOS_ERR;
    }

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if ( pcString[i] == '.' )
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* 统计'.'的个数 */
            ulDotNum++;

            continue;
        }
        else
        {
            /* 其他值直接返回失败 */
            return VOS_ERR;
        }
    }

    /* 如果不是3个'.'则返回失败 */
    if ( 3 != ulDotNum )
    {
        return VOS_ERR;
    }

    /* 检查最后地址域的取值 */
    if (ulValTmp > 255)
    {
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    PS_MEM_CPY(pucNumber, aucAddr, 4);

    return VOS_OK;
}

/******************************************************************************
 函数名称: At_IPaddritoa
 功能描述: 把IPV4地址由数字格式转换成字符串格式

 参数说明:
   pcString [out] 字符串格式的IP地址,char * pcString="192.168.0.1"
   pucNumber [in] 数字格式的IP地址,char pucNumber[4]={192,168,0,1};

 返 回 值:
    TODO: ...

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          ret = VOS_OK;
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        ret = VOS_ERR;
    }
    else
    {
        PS_MEM_SET(pcString, 0, TAF_MAX_IPV4_ADDR_STR_LEN);
        sprintf(astringTmp, "%d", pucNumber[0]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[1]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[2]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[3]);
        strcat(pcString, astringTmp);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : AT_Ipv4Addr2Str
 功能描述  : IPV4类型的地址转换为字符串类型
 输入参数  : pucNumber      - IPV4地址
 输出参数  : pcString       - 字符串
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增

*****************************************************************************/
VOS_UINT32 AT_Ipv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pcString, 0, TAF_MAX_IPV4_ADDR_STR_LEN);

    /* 如果输入地址为空，则返回空字符串 */
    if ((0 == pucNumber[0])
      &&(0 == pucNumber[1])
      &&(0 == pucNumber[2])
      &&(0 == pucNumber[3]))
    {
        return VOS_OK;
    }

    sprintf(astringTmp, "%d", pucNumber[0]);
    strcat(pcString, astringTmp);

    sprintf(astringTmp, ".%d", pucNumber[1]);
    strcat(pcString, astringTmp);

    sprintf(astringTmp, ".%d", pucNumber[2]);
    strcat(pcString, astringTmp);

    sprintf(astringTmp, ".%d", pucNumber[3]);
    strcat(pcString, astringTmp);

    return VOS_OK;
}

/******************************************************************************
 函 数 名  : AT_Ipv6AddrAtoi
 功能描述  : 把IPV6地址由字符串格式转换成数字格式
 输入参数  : pcString - 字符串格式的IP地址,char * pcString="192.168.0.1.13.23.56.24.192.168.0.1.13.23.56.24"
 输出参数  : pucNumber - 数字格式的IP地址,char pucNumber[16]={192,168,0,1,13,23,56,24,192,168,0,1,13,23,56,24};
 返 回 值  : TAF_SUCCESS - 转化成功
             TAF_FAILURE - 转化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月12日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加最后一个地址域的取值范围检查
******************************************************************************/
VOS_UINT32 AT_Ipv6AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulStrLen = 0;
    VOS_UINT32                          ulNumLen = 0;
    VOS_UINT32                          ulDotNum = 0;
    VOS_UINT32                          ulValTmp = 0;
    VOS_UINT8                           aucAddr[TAF_IPV6_ADDR_LEN] = {0};


    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        return VOS_ERR;
    }

    ulStrLen = VOS_StrLen(pcString);

    if ( ulStrLen > VOS_StrLen("255.255.255.255.255.255.255.255.255.255.255.255.255.255.255.255") )
    {
        return VOS_ERR;
    }

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulValTmp = (ulValTmp * 10) + (pcString[i] - '0');

            ulNumLen++;
            continue;
        }
        else if ( pcString[i] == '.' )
        {
            if ( (0 == ulNumLen) || (ulNumLen > 3) )
            {
                return VOS_ERR;
            }

            if ( ulValTmp > 255 )
            {
                return VOS_ERR;
            }

            aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

            ulValTmp = 0;
            ulNumLen = 0;

            /* 统计'.'的个数 */
            ulDotNum++;

            continue;
        }
        else
        {
            /* 其他值直接返回失败 */
            return VOS_ERR;
        }
    }

    /* 如果不是3个'.'则返回失败 */
    if ((TAF_IPV6_ADDR_LEN - 1) != ulDotNum )
    {
        return VOS_ERR;
    }

    /* 检查最后地址域的取值 */
    if (ulValTmp > 255)
    {
        return VOS_ERR;
    }

    aucAddr[ulDotNum] = (VOS_UINT8)ulValTmp;

    PS_MEM_CPY(pucNumber, aucAddr, TAF_IPV6_ADDR_LEN);

    return VOS_OK;
}

/******************************************************************************
 函 数 名  : AT_LenStr2IpAddr
 功能描述  : 将字符串格式的IP地址转化为SM协议IP地址格式.完全继承V100R001
 输入参数  : pucStr - 字符串格式的IP地址
 输出参数  : pucIpAddr - SM协议定义的IP地址
 返 回 值  : TAF_SUCCESS - 转化成功
             TAF_FAILURE - 转化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : sunshaohua
    修改内容   : 新生成函数
******************************************************************************/
VOS_UINT32  AT_LenStr2IpAddr(
    VOS_UINT8                           *pucStr,
    VOS_UINT8                           *pucIpAddr
)
{
    VOS_UINT8 i;
    VOS_UINT8 j;
    VOS_UINT8 ucValue;

    i                = 0;
    j                = 0;
    ucValue          = 0;

    if (0 == pucStr[0])
    {
       /*ADDR长度为0，直接长度赋值返回*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return AT_SUCCESS;
    }

    if (pucStr[0] == '.')
    {
        /*如果第1个有效字符是'.'，IP地址是非法的*/
        return AT_FAILURE;
    }

    for (i = 0; (i <= AT_AP_MAX_IPV4_ADDR_LEN) && (0 != pucStr[i]) ; i++)
    {
        /*从第1个有效字符开始检查*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {
            /*超出'0'-'9'的字符非法*/
            return AT_FAILURE;
        }
        if (pucStr[i] != '.')
        {
            /*如果是有效字符，转化为数字*/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {
                /*字符串转化为有效IP段位值*/
                ucValue = (TAF_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /*超过255出错*/
                return AT_FAILURE;
            }
        }
        else
        {   /*如果字符是'.'，前一位段值已经计算出来*/
            /*如果字符是'.'，前一位段值已经计算出来*/
            if (j <= 3)
            {
               /*本版本只支持IPV4地址*/
                pucIpAddr[j] = ucValue;
                ucValue      = 0;

                /*开始下一个有效字符段的长度累计*/
                j++;
            }
            else
            {
                /*超出4个IP位段，非法*/
                return AT_FAILURE;
            }
        }
    }

    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddrProc
 功能描述  : 将字符串格式的IP地址转化为SM协议IP地址格式(IPV6).
 输入参数  : pucStr - 字符串格式的IP地址
             pucColonCount - 冒号个数
             pucDotCount   - 点号个数
 输出参数  : pucIpAddr - SM协议定义的IP地址
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : x00180552
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_Ipv6LenStrToAddrProc(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT16                          usValue;            /*Ipv6十六进制转换用*/
    VOS_UINT8                           ucValue;            /*Ipv4十六进制转换用*/

    usValue                             = 0;
    ucValue                             = 0;
    j                                   = 0;

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        if ((':' != pucStr[i]) && ('.' != pucStr[i]))
        {
            usValue <<= 4;

            if ((pucStr[i] >= '0') &&(pucStr[i] <= '9'))
            {
                /* 十进制格式转换 */
                usValue += (pucStr[i] - '0');
                ucValue  = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {
                /* 十六进制格式转换 */
                 usValue += (pucStr[i] - 'A' + 10);
            }
        }
        else if (':' == pucStr[i])
        {
            /* IPV6十六进制取高八位数据 */
            pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
            j++;
            /* IPV6十六进制取低八位数据 */
            pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
            j++;
            usValue      = 0;
        }
        else
        {
            /* IPV4十进制转换 */
            pucIpAddr[j] = ucValue;
            j++;
            ucValue      = 0;
        }
    }

    /* 匹配最后一次转换 */
    if (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
    {
        pucIpAddr[j] = (VOS_UINT8)((usValue >> 8) & 0x00FF);
        j++;
        pucIpAddr[j] = (VOS_UINT8)(usValue & 0x00FF);
        j++;
    }

    if (AT_MAX_IPV6_STR_DOT_NUM == ucDotCount)
    {
        pucIpAddr[j] = ucValue;
        j++;
    }

    return;
}

/******************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddrProcCompressed
 功能描述  : 将IPV6压缩字符串格式转化为非压缩格式.
 输入参数  : pucStr       - 字符串格式的IP地址
             ucColonCount - 冒号个数
             ucDotCount   - 点号个数
             ucStrlen     - 字符串长度
             ucIdxPos     - 补充冒号插入位置
 输出参数  : pucIpAddr - 非压缩格式的IP地址
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : x00180552
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID  AT_Ipv6LenStrToAddrProcCompressed(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount,
    VOS_UINT8                           ucStrlen,
    VOS_UINT8                           ucIdxPos
)
{
    VOS_UINT8                           i;

    /* 把字符串从压缩位置开始顺次向后移动 */
    for (i = ucStrlen; i >= ucIdxPos; i--)
    {
        if (AT_MAX_IPV6_STR_DOT_NUM != ucDotCount)
        {
            pucStr[i + AT_MAX_IPV6_STR_COLON_NUM - ucColonCount] =  pucStr[i];
        }
        else
        {
            pucStr[i + AT_MAX_IPV4V6_STR_COLON_NUM - ucColonCount] =  pucStr[i];
        }
    }

    /* 补足压缩的冒号 */
    if (AT_MAX_IPV6_STR_DOT_NUM != ucDotCount)
    {
        for (i = ucIdxPos; i < (ucIdxPos + AT_MAX_IPV6_STR_COLON_NUM - ucColonCount); i++)
        {
            pucStr[i + 1] =  ':';
        }
    }
    else
    {
        for (i = ucIdxPos; i < (ucIdxPos + AT_MAX_IPV4V6_STR_COLON_NUM - ucColonCount); i++)
        {
            pucStr[i + 1] =  ':';
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddrAccess
 功能描述  : 遍历IPV6地址字符串，取得冒号、点号个数
 输入参数  : pucStr        - 字符串格式的IP地址
 输出参数  : pucColonCount - 冒号个数
             pucDotCount   - 点号个数
             pucStrlen     - IPV6字符串长度
             pucIdxPos     - 数组补充冒号索引
 返 回 值  : VOS_OK - 转化成功
             VOS_ERR - 转化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月9日
    作    者   : x00180552
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_Ipv6LenStrToAddrAccess(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucColonCount,
    VOS_UINT8                          *pucDotCount,
    VOS_UINT8                          *pucStrlen,
    VOS_UINT8                          *pucIdxPos
)
{
    VOS_UINT32                          i;

    for (i = 0; ((i < TAF_MAX_IPV6_ADDR_COLON_STR_LEN) && ('\0' != pucStr[i])); i++)
    {
        if ( (pucStr[i] < '0' || pucStr[i] > '9')
          && (pucStr[i] < 'A' || pucStr[i] > 'F')
          && ('.' != pucStr[i])
          && (':' != pucStr[i]) )
        {
            return VOS_ERR;
        }
        /* 取得补充冒号索引位置 */
        if ((pucStr[i -1] == ':') && (pucStr[i] == ':'))
        {
            *pucIdxPos = (VOS_UINT8)i;
        }

        /* 统计冒号个数 */
        if (':' == pucStr[i])
        {
            (*pucColonCount)++;
        }

        /*统计点号个数*/
        if ('.' == pucStr[i])
        {
            (*pucDotCount)++;
        }
    }

    *pucStrlen = (VOS_UINT8)i;

    return VOS_OK;
}

/******************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddr
 功能描述  : 将字符串格式的IP地址转化为SM协议IP地址格式(IPV6).
 输入参数  : pucStr - 字符串格式的IP地址
 输出参数  : pucIpAddr - SM协议定义的IP地址
 返 回 值  : VOS_OK  - 转化成功
             VOS_ERR - 转化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月09日
    作    者   : x00180552
    修改内容   : 新生成函数
  2.日    期   : 2015年12月26日
    作    者   : f00179208
    修改内容   : Coverity告警清理
******************************************************************************/
VOS_UINT32  AT_Ipv6LenStrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
)
{
    VOS_UINT8                           ucColonCount;       /* 字符串中冒号个数 */
    VOS_UINT8                           ucDotCount;         /* 字符串中点号个数 */
    VOS_UINT8                           ucStrlen;           /* 字符串长度 */
    VOS_UINT8                           ucIdxPos;           /* 需要补充冒号的位置 */
    VOS_UINT8                           pucStrTmp[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    PS_MEM_SET(pucStrTmp, 0, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);

    PS_MEM_CPY(pucStrTmp, pucStr, TAF_MAX_IPV6_ADDR_COLON_STR_LEN);
    ucColonCount                        = 0;
    ucDotCount                          = 0;
    ucStrlen                            = 0;
    ucIdxPos                            = 0;

    /* 遍历IPV6地址字符串 */
    if (VOS_OK != AT_Ipv6LenStrToAddrAccess(pucStrTmp, &ucColonCount,
                                           &ucDotCount, &ucStrlen, &ucIdxPos))
    {
        return VOS_ERR;
    }

    /* 字符串为空返回失败 */
    if (ucStrlen == 0)
    {
        return VOS_ERR;
    }

    /* 冒号个数大于7或者点号个数不等于3返回失败 */
    if ( (ucColonCount > AT_MAX_IPV6_STR_COLON_NUM)
      || ((AT_MAX_IPV6_STR_DOT_NUM != ucDotCount) && (0 != ucDotCount)) )
    {
        return VOS_ERR;
    }

    if ( (AT_MAX_IPV6_STR_COLON_NUM == ucColonCount)
      || ( (AT_MAX_IPV4V6_STR_COLON_NUM == ucColonCount)
        && (AT_MAX_IPV6_STR_DOT_NUM == ucDotCount) ) )
    {
        /* 非压缩格式处理 */
        AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, ucColonCount, ucDotCount);
    }
    else
    {
        /* 压缩格式处理 */
        AT_Ipv6LenStrToAddrProcCompressed(pucStrTmp, ucColonCount, ucDotCount, ucStrlen, ucIdxPos);
        if (ucDotCount != AT_MAX_IPV6_STR_DOT_NUM)
        {
            /* 非IPV4映射IPV6地址格式 */
            AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, AT_MAX_IPV6_STR_COLON_NUM, ucDotCount);
        }
        else
        {
            /* IPV4映射IPV6地址格式 */
            AT_Ipv6LenStrToAddrProc(pucStrTmp, pucIpAddr, AT_MAX_IPV4V6_STR_COLON_NUM, ucDotCount);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_Ipv6AddrToStr
 功能描述  : 将IPV6地址格式转换为字符串格式
 输入参数  : aucIpAddr[]    - IPV6地址(协议格式)
             enIpStrType    - IPV6字符串格式表达类型
 输出参数  : aucAddrStr[]   - IPV6地址(字符串格式)
 返 回 值  : VOS_OK         - 转换成功
             VOS_ERR        - 转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月09日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_Ipv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    AT_IPV6_STR_TYPE_ENUM_UINT8         enIpStrType
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[AT_IPV6_STR_MAX_TOKENS];
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucTokensNum;
    VOS_UINT8                           ucRadix;
    VOS_UINT32                          i;

    pucBuffer                           = aucAddrStr;

    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    /* 根据IP字符串格式表达类型, 配置对应的转换参数 */
    switch (enIpStrType)
    {
        case AT_IPV6_STR_TYPE_HEX:
            ucDelimiter = AT_IPV6_STR_DELIMITER;
            ucTokensNum = 8;
            ucRadix     = 16;
            break;

        case AT_IPV6_STR_TYPE_DEC:
            ucDelimiter = AT_IPV4_STR_DELIMITER;
            ucTokensNum = 16;
            ucRadix     = 10;
            break;

        default:
            return VOS_ERR;
    }

    /* 根据IP字符串格式表达类型, 获取分段的IP地址数值 */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        if (AT_IPV6_STR_TYPE_HEX == enIpStrType)
        {
            usAddrNum <<= 8;
            usAddrNum  |= *aucIpAddr++;
        }

        ausAddrValue[i] = usAddrNum;
    }

    /* 遍历IP地址分段, 创建有分隔符标记的IP地址字符串 */
    for (i=0; i < ucTokensNum; i++)
    {
        pucBuffer    = (VOS_UINT8*)AT_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix);
        *pucBuffer++ = ucDelimiter;
    }

    /* 取出最后一个分隔符, 补充字符串结束符 */
    if (aucAddrStr != pucBuffer)
    {
        *(--pucBuffer) = '\0';
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_CalcIpv6PrefixLength
 功能描述  : 填写AT命令设置TFT的Local IPV6的前缀长度
 输入参数  : VOS_UINT8                   *pucLocalIpv6Mask
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 AT_CalcIpv6PrefixLength(VOS_UINT8 *pucLocalIpv6Mask)
{
    VOS_UINT32                          i                   = 0;
    VOS_UINT8                           j                   = 0;
    VOS_UINT8                           ucMaskLength        = 0;

    if ( VOS_NULL_PTR == pucLocalIpv6Mask )
    {
        return ucMaskLength;
    }

    for(i = 0; i < AT_IPV6_STR_MAX_TOKENS; i++)
    {
        if (0xFF == *(pucLocalIpv6Mask + i))
        {
            ucMaskLength = ucMaskLength + 8;
        }
        else
        {
            for (j = 0; j < 8; j++)
            {
                if (0 != ((*(pucLocalIpv6Mask + i)) & (1 << (7 - j))))
                {
                    ucMaskLength ++;
                }
                else
                {
                    break;
                }
            }
            break;
        }
    }

    return ucMaskLength;
}

/*****************************************************************************
 函 数 名  : AT_GetIpv6MaskByPrefixLength
 功能描述  : 根据Local IPV6的前缀长度获取Local IPV6 Mask
 输入参数  : VOS_UINT8                   *ucLocalIpv6Prefix
 输出参数  : VOS_UINT8                   *pucLocalIpv6Mask
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_GetIpv6MaskByPrefixLength(VOS_UINT8 ucLocalIpv6Prefix, VOS_UINT8 *pucLocalIpv6Mask)
{
    VOS_UINT8                           ucNum                   = 0;
    VOS_UINT8                           i                       = 0;

    ucNum = ucLocalIpv6Prefix/8;

    if ( VOS_NULL_PTR == pucLocalIpv6Mask )
    {
        return;
    }

    for (i = 0; i < ucNum; i ++)
    {
        *(pucLocalIpv6Mask + i) = 0xFF;
    }

    ucNum = ucLocalIpv6Prefix % 8;

    if (0 != ucNum)
    {
        *(pucLocalIpv6Mask + i) = 0xFF & (0xFF << (8 - ucNum));

    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_Itoa
 功能描述  : 根据转换基数(10或16), 将整数转换为ASCII码, 将结果输出至字符串
 输入参数  : usValue    - 待转换为ASCII码的整数
             pcStr      - 输出结果的字符串
             usRadix    - 转换基数
 输出参数  : 无
 返 回 值  : VOS_CHAR*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月7日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_CHAR* AT_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
)
{
    if (usRadix == 16)
    {
        pcStr += sprintf(pcStr, "%x", usValue);
    }
    else if(usRadix == 10)
    {
        pcStr += sprintf(pcStr, "%d", usValue);
    }
    else
    {
    }

    return pcStr;
}

/*****************************************************************************
 函 数 名  : AT_FindIpv6AddrZeroFieldsToBeCompressed
 功能描述  : 找出需要使用"::"表示的IP地址段的起始位置
 输入参数  : ausAddrValue[]     - IPV6地址段数组
             ucTokensNum        - 地址段个数
 输出参数  : pucZeroFieldStart  - 数值连续为0的IP地址段起始位置
             pucZeroFieldCount  - 数值连续为0的IP地址段个数
 返 回 值  : VOS_OK             - 成功
             VOS_ERR            - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月9日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                          ausAddrValue[],
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                           ucStart;
    VOS_UINT8                           ucCount;
    VOS_UINT8                           i;

    ucStart                             = 0xFF;
    ucCount                             = 0;

    for (i = 0; i < ucTokensNum - 1; i++)
    {
        if ( (0x0000 == ausAddrValue[i])
          && (0x0000 == ausAddrValue[i + 1]) )
        {
            /* 记录数值连续为0的IP地址段起始位置 */
            if (0xFF == ucStart)
            {
                ucStart = i;
            }

            /* 更新数值连续为0的IP地址段个数 */
            ucCount++;
        }
        else
        {
            /* 更新待压缩的IP地址段位置, 以及IP地址段个数 */
            if (0xFF != ucStart)
            {
                if (ucCount > *pucZeroFieldCount)
                {
                    *pucZeroFieldStart = ucStart;
                    *pucZeroFieldCount = ucCount;
                }

                ucStart = 0xFF;
                ucCount = 0;
            }
        }
    }

    /* 数值连续为0的IP地址段在结尾时, 需要更新一次待压缩的IP地址段位置,
       以及IP地址段个数 */
    if (0xFF != ucStart)
    {
        if (ucCount > *pucZeroFieldCount)
        {
            *pucZeroFieldStart = ucStart;
            *pucZeroFieldCount = ucCount;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ConvertIpv6AddrToCompressedStr
 功能描述  : 将IPV6地址格式转换为字符串压缩格式
 输入参数  : aucIpAddr[]    - IPV6地址(协议格式)
             ucTokensNum    - 地址段个数
 输出参数  : aucAddrStr[]   - IPV6地址(字符串格式)
 返 回 值  : VOS_OK         - 转换成功
             VOS_ERR        - 转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月9日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[8]; /*TAF_IPV6_STR_RFC2373_TOKENS]; */
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucRadix;
    VOS_UINT8                           ucZeroFieldStart;
    VOS_UINT8                           ucZeroFieldCount;
    VOS_UINT8                           i;

    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    pucBuffer                           = aucAddrStr;
    ucDelimiter                         = TAF_IPV6_STR_DELIMITER;
    ucRadix                             = 16;
    ucZeroFieldStart                    = 0xFF;
    ucZeroFieldCount                    = 0;

    /* 根据IP字符串格式表达类型, 获取分段的IP地址数值 */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        usAddrNum <<= 8;
        usAddrNum  |= *aucIpAddr++;

        ausAddrValue[i] = usAddrNum;
    }

    /* 找出需要使用"::"表示的IP地址段的起始位置  */
    AT_FindIpv6AddrZeroFieldsToBeCompressed(&ucZeroFieldStart,
                                            &ucZeroFieldCount,
                                            ausAddrValue,
                                            ucTokensNum);

    /* 遍历IP地址分段, 创建有分隔符标记的IP地址字符串 */
    for (i=0; i < ucTokensNum; i++)
    {
        if (ucZeroFieldStart == i)
        {
            *pucBuffer++ = ucDelimiter;

            i += ucZeroFieldCount;

            /* 如果已到IP地址分段的最后一段, 需要补充分隔符 */
            if ((ucTokensNum - 1) == i)
            {
                *pucBuffer++ = ucDelimiter;
            }
        }
        else
        {
            /* 如果是IP地址分段的第一段, 不需要补充分隔符 */
            if (0 != i)
            {
                *pucBuffer++ = ucDelimiter;
            }

            pucBuffer    = (VOS_UINT8*)AT_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix);
        }
    }

    /* 补充字符串结束符 */
    if (aucAddrStr != pucBuffer)
    {
        *pucBuffer = '\0';
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_CalcIpHdrCRC16
 功能描述  : 计算IP头CRC校验和
 输入参数  : pucData    - IP头信息
             usSize     - IP头长度
 输出参数  : 无
 返 回 值  : ulCheckSum - CRC校验和
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 AT_CalcIpHdrCRC16(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usSize
)
{
    VOS_UINT16                         *pusBuffer;
    VOS_UINT32                          ulCheckSum;

    pusBuffer    = (VOS_UINT16 *)pucData;
    ulCheckSum = 0;

    while (usSize > 1)
    {
        ulCheckSum += *pusBuffer++;
        usSize     -= sizeof(VOS_UINT16);
    }

    if (usSize)
    {
#if (VOS_LITTLE_ENDIAN == VOS_BYTE_ORDER)
        ulCheckSum += *(VOS_UINT8 *)pusBuffer;
#else
        ulCheckSum += 0 | ((*(VOS_UINT8 *)pusBuffer) << 8);
#endif
    }

    ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    ulCheckSum += (ulCheckSum >> 16);

    return (VOS_UINT16)(~ulCheckSum);
}

/*****************************************************************************
 函 数 名  : AT_BuildUdpHdr
 功能描述  : 构造IP和UDP头部信息(用于构造测试使用的UDP包)
 输入参数  : pstUdpPkt  - UDP包信息
             usLen      - UDP包长度
             ulSrcAddr  - 源IP地址
             ulDstAddr  - 目标IP地址
             usSrcPort  - 源端口号
             usDstPort  - 目标端口号
 输出参数  : 无
 返 回 值  : VOS_OK     - 构造成功
             VOS_ERR    - 构造失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_BuildUdpHdr(
    AT_UDP_PACKET_FORMAT_STRU          *pstUdpPkt,
    VOS_UINT16                          usLen,
    VOS_UINT32                          ulSrcAddr,
    VOS_UINT32                          ulDstAddr,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort
)
{
    static VOS_UINT16                   usIdentification = 0;

    /* 检查指针合法性 */
    if (VOS_NULL_PTR == pstUdpPkt)
    {
        return VOS_ERR;
    }

    /* 填写IP头 */
    pstUdpPkt->stIpHdr.ucIpVer          = AT_IP_VERSION;
    pstUdpPkt->stIpHdr.ucIpHdrLen       = 5;
    pstUdpPkt->stIpHdr.ucServiceType    = 0x00;
    pstUdpPkt->stIpHdr.usTotalLen       = VOS_HTONS(usLen + AT_IP_HDR_LEN + AT_UDP_HDR_LEN);
    pstUdpPkt->stIpHdr.usIdentification = VOS_HTONS(usIdentification);
    pstUdpPkt->stIpHdr.usOffset         = 0;
    pstUdpPkt->stIpHdr.ucTTL            = AT_IP_DEF_TTL;
    pstUdpPkt->stIpHdr.ucProtocol       = AT_IPPROTO_UDP;
    pstUdpPkt->stIpHdr.ulSrcAddr        = VOS_HTONL(ulSrcAddr);
    pstUdpPkt->stIpHdr.ulDstAddr        = VOS_HTONL(ulDstAddr);
    pstUdpPkt->stIpHdr.usCheckSum       = AT_CalcIpHdrCRC16((VOS_UINT8 *)&pstUdpPkt->stIpHdr, AT_IP_HDR_LEN);

    /* 填写UDP头 */
    pstUdpPkt->stUdpHdr.usSrcPort       = VOS_HTONS(usSrcPort);
    pstUdpPkt->stUdpHdr.usDstPort       = VOS_HTONS(usDstPort);
    pstUdpPkt->stUdpHdr.usLen           = VOS_HTONS(usLen + AT_UDP_HDR_LEN);
    pstUdpPkt->stUdpHdr.usChecksum      = 0;

    usIdentification++;

    return VOS_OK;
}

/******************************************************************************
 Function:       AT_DHCPCheckCfg
 Description:    检查DHCP配置参数是否合法，IP地址不为全0或全1即可
 Calls:
 Data Accessed:
 Data Updated:
 Input:         AT_AP_DHCP_SETUP_PARAM_ST *ptrDHCPCfg DHCP配置参数
 Output:
 Return:        VOS_OK      正确
                VOS_ERR     错误
 Others:        IP地址为非全0，非全1
     1.Date        : 2009-08-03-
    Author      : S62952
    Modification: Created function
******************************************************************************/
VOS_UINT32 AT_DHCPCheckCfg(
    AT_DHCP_SETUP_PARAM_ST             *ptrDHCPCfg
)
{
    if ( (0 == ptrDHCPCfg->ulIPAddr)
      || (0 == (0xffffffffU - ptrDHCPCfg->ulIPAddr)) )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/******************************************************************************
 函 数 名  : AT_DHCPServerSetUp
 功能描述  : 根据ptrDHCPParam参数配置DHCP Server的状态，并通过ptrDHCPConfig
                返回DHCP Server最终的配置(包括最后的网关、掩码等)
                当关闭DHCP Server时，允许最后两项参数为空
 输入参数  : pstEvent指向PDP去激活的指针
 输出参数  : AT_DHCP_SETUP_PARAM_ST *ptrDHCPCfg       DHCP配置参数
             AT_DHCP_CONFIG_STRU    *ptrDHCPConfig    返回DHCP所有配置
 返 回 值  : VOS_OK      正确
             VOS_ERR     错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : sunshaohua
    修改内容   : 新生成函数
******************************************************************************/
VOS_UINT32  AT_DHCPServerSetUp(
    AT_DHCP_SETUP_PARAM_ST              *ptrDHCPParam,
    AT_DHCP_CONFIG_STRU                 *ptrDHCPConfig
)
{
    if (VOS_ERR == AT_DHCPCheckCfg(ptrDHCPParam))
    {
        AT_ERR_LOG("AT_DHCPServerSetUp, ERROR, DHCP Config IP Address is Error!" );
        return VOS_ERR;
    }

      /*计算掩码、网关*/
    ptrDHCPConfig->ulIPAddr     = ptrDHCPParam->ulIPAddr;
    ptrDHCPConfig->ulSubNetMask =
      AT_DHCPGetIPMask(ptrDHCPParam->ulIPAddr);
    ptrDHCPConfig->ulGateWay    =
      AT_DHCPGetGateWay(ptrDHCPParam->ulIPAddr,ptrDHCPConfig->ulSubNetMask);
    ptrDHCPConfig->ulPrimDNS    = ptrDHCPParam->ulPrimDNS;
    ptrDHCPConfig->ulSndDNS     = ptrDHCPParam->ulSndDNS;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_GetDhcpPara
 功能描述  : 获取DHCP参数(DHCP参数为网络序)
 输入参数  : pstConfig                  - DHCP参数(网络序)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_GetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig,
    AT_IPV4_DHCP_PARAM_STRU            *pstIpv4Dhcp
)
{
    /* 将DHCP参数转换为网络序 */
    pstConfig->stDhcpCfg.ulIPAddr     = VOS_HTONL(pstIpv4Dhcp->ulIpv4Addr);
    pstConfig->stDhcpCfg.ulSubNetMask = VOS_HTONL(pstIpv4Dhcp->ulIpv4NetMask);
    pstConfig->stDhcpCfg.ulGateWay    = VOS_HTONL(pstIpv4Dhcp->ulIpv4GateWay);
    pstConfig->stDhcpCfg.ulPrimDNS    = VOS_HTONL(pstIpv4Dhcp->ulIpv4PrimDNS);
    pstConfig->stDhcpCfg.ulSndDNS     = VOS_HTONL(pstIpv4Dhcp->ulIpv4SecDNS);

    return;
}

/******************************************************************************
 函 数 名  : AT_AtoI
 功能描述  : 字符串转整形
 输入参数  : pString 字符串
 输出参数  : 无
 返 回 值  : 整形 IP地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : sunshaohua
    修改内容   : 新生成函数
******************************************************************************/
VOS_UINT32  AT_AtoI(
    VOS_UINT8                         *pString
)
{
    VOS_UINT8   *pucTmp;
    VOS_UINT32   ulRet;

    pucTmp  = pString;
    ulRet   = 0;

    for (pucTmp = pString ; *pucTmp != '\0' ; pucTmp++)
    {
        /* 非数字,则不处理*/
        if ((*pucTmp < '0') || (*pucTmp > '9'))
        {
            continue;
        }

        ulRet = (ulRet * 10) + (*pucTmp - '0');
    }

    return ulRet;
}

/******************************************************************************
 函 数 名  : AT_GetDisplayRate
 功能描述  : 获取空口理论带宽，从NAS获取，且将字符串型式转为整形
 输入参数  : ulSpeed
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : sunshaohua
    修改内容   : 新生成函数
  2.日    期   : 2013年4月7日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
******************************************************************************/
VOS_UINT32 AT_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT32                         *ulSpeed
)
{
      VOS_UINT8 aucSpeed[AT_AP_SPEED_STRLEN + 1];

      PS_MEM_SET(aucSpeed, 0, (VOS_SIZE_T)(AT_AP_SPEED_STRLEN + 1));
      if (VOS_ERR == Taf_GetDisplayRate(usClientId, aucSpeed))
      {
          AT_ERR_LOG("AT_GetDisplayRate : ERROR : at get rate Error!");
          return VOS_ERR;
      }
      aucSpeed[AT_AP_SPEED_STRLEN] = '\0';

      *ulSpeed = AT_AtoI(aucSpeed);

      return VOS_OK;
}

/******************************************************************************
 函 数 名  : AT_CtrlConnIndProc
 功能描述  : 需要解析激活上下文，设置DHCP服务器
 输入参数  : pstEvent指向TAF_PS_CALL_EVENT_INFO_STRU去激活的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : sunshaohua
    修改内容   : 新生成函数

  2.日    期   : 2012年6月12日
    作    者   : S62952
    修改内容   : DTS2012032802023: ^CSND命令实现方案修改
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

  4.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : DTS2013110900839: ^CSND命令处理优化
******************************************************************************/
VOS_VOID AT_CtrlConnIndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_USER_TYPE                        ucUserType
)
{
    AT_DHCP_SETUP_PARAM_ST              stParam;
    AT_DHCP_CONFIG_STRU                 stConfig;

    PS_MEM_SET(&stParam, 0, sizeof(AT_DHCP_SETUP_PARAM_ST));
    PS_MEM_SET(&stConfig, 0, sizeof(AT_DHCP_CONFIG_STRU));

    /* 如果PS事件有DNS地址，则记录DNS地址*/
    if (pstEvent->stDns.bitOpPrimDnsAddr)
    {
        stParam.ulPrimDNS = AT_GetLanAddr32(pstEvent->stDns.aucPrimDnsAddr);
    }

    if (pstEvent->stDns.bitOpSecDnsAddr)
    {
        stParam.ulSndDNS = AT_GetLanAddr32(pstEvent->stDns.aucSecDnsAddr);
    }

    /* 记录IP地址*/
    stParam.ulIPAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);

    if (VOS_ERR == AT_DHCPServerSetUp(&stParam, &stConfig))
    {
        AT_ERR_LOG("AT_CtrlConnIndProc : ERROR AT_DHCPServerSetUp Error!" );

        return;
    }
    else
    {
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (AT_NDIS_USER == ucUserType)
        {
            AT_NdisAddrProc(&stConfig, pstEvent);
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        if (AT_APP_USER == ucUserType)
        {
            AT_AppPdpAddrProc(&g_stAtAppPdpEntity, &stConfig, pstEvent);
        }

        /* 删除AT_USBCOM_USER处理分支 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : Taf_GetDisplayRate
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  : TAF_SUCCESS  - 成功
             TAF_FAILURE  - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-05-16
    作    者   :s62952
    修改内容   : Created
  2.日    期   : 2011-06-06
    作    者   :w00166186
    修改内容   : 系统托盘显示速率NV定制特性合入
  3.日    期   : 2011年7月20日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011063000712 速率显示错误
  4.日    期   : 2013年4月8日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
  5.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : Syscfg重构
  6.日    期   : 2015年12月26日
    作    者   : f00179208
    修改内容   : Coverity告警清理
  7.日    期   : 2015年11月17日
    作    者   : zwx247453
    修改内容   : dallas gps参考时钟虚焊检测
*****************************************************************************/
VOS_UINT32 Taf_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *ucSpeed
)
{
    VOS_UINT32                          ulTmp = 0;
    PPP_RATE_DISPLAY_ENUM_UINT32        enRateDisplay;
    VOS_UINT32                          ulNvDialRateIndex;
    VOS_UINT8                           ucSubSysMode;
    VOS_UINT8                           aucDialRateTmp[AT_AP_RATE_STRLEN];
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    TAF_AGENT_SYS_MODE_STRU             stSysMode;
    VOS_UINT32                          ulRet;

    /* 变量初始化 */
    PS_MEM_SET(&stSysMode, 0, sizeof(stSysMode));
    PS_MEM_SET(aucDialRateTmp, 0, sizeof(aucDialRateTmp));

    /* 从C核获取ucRatType和ucSysSubMode */
    ulRet = TAF_AGENT_GetSysMode(usClientId, &stSysMode);

    if (VOS_OK != ulRet)
    {
        stSysMode.enRatType     = TAF_PH_INFO_GSM_RAT;
        stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_BUTT;
    }

    ucSubSysMode = stSysMode.enSysSubMode;
    switch(ucSubSysMode)
    {
        case TAF_SYS_SUBMODE_GSM:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucGprsConnectRate;

            break;

        case TAF_SYS_SUBMODE_EDGE:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucEdgeConnectRate;
            break;

        case TAF_SYS_SUBMODE_WCDMA:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucWcdmaConnectRate;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            ulNvDialRateIndex =    g_stDialConnectDisplayRate.ucDpaConnectRate;
            break;

        default:
            ulNvDialRateIndex = 0;
            break;
    }

    if ((0 == ulNvDialRateIndex) || (ulNvDialRateIndex > 6))
    {
        if ( (TAF_PH_INFO_WCDMA_RAT == stSysMode.enRatType)
          || (TAF_PH_INFO_TD_SCDMA_RAT == stSysMode.enRatType) )
        {
            enRateDisplay = AT_GetRateDisplayIndexForWcdma(&g_stAtDlRateCategory);
            ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            VOS_MemCpy(aucDialRateTmp, g_PppDialRateDisplay[enRateDisplay], ulTmp);

        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (TAF_PH_INFO_LTE_RAT == stSysMode.enRatType)
        {
            enRateDisplay = AT_GetRateDisplayIndexForLTE(&g_stAtDlRateCategory);
            ulTmp = VOS_StrLen((TAF_CHAR *)g_ucLTEDlRateDisplay[enRateDisplay]);
            VOS_MemCpy(aucDialRateTmp, g_ucLTEDlRateDisplay[enRateDisplay], ulTmp);
        }
#endif
        else
        {
            enRateDisplay = AT_GetRateDisplayIndexForGsm(&stSysMode);
            ulTmp = VOS_StrLen((TAF_CHAR *)g_PppDialRateDisplay[enRateDisplay]);
            VOS_MemCpy(aucDialRateTmp, g_PppDialRateDisplay[enRateDisplay], ulTmp);
        }
    }
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    else
    {
        ulTmp = VOS_StrLen((TAF_CHAR *)g_ucDialRateDisplayNv[ulNvDialRateIndex - 1]);
        VOS_MemCpy(aucDialRateTmp, g_ucDialRateDisplayNv[ulNvDialRateIndex - 1], ulTmp);
    }

    /*在CONNECT后附上速率信息*/
    PS_MEM_CPY(ucSpeed, aucDialRateTmp, (VOS_UINT16)ulTmp);
    ucSpeed[ulTmp] = '\0';

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_GetPdpContextFromAtDialParam
 功能描述  : 获取pdp上下文
 输入参数  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月31日
    作    者   : c00173809
    修改内容   : PS融合项目，获取pdp上下文
*****************************************************************************/
VOS_VOID AT_GetPdpContextFromAtDialParam(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
    AT_DIAL_PARAM_STRU                 *pstDialParam
)
{
    VOS_UINT32                          ulRet;

    PS_MEM_SET((VOS_VOID *)pstPdpPrimContextExt, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstPdpPrimContextExt->bitOpPdpType      = VOS_TRUE;
    pstPdpPrimContextExt->bitOpPdpDcomp     = VOS_FALSE;
    pstPdpPrimContextExt->bitOpPdpHcomp     = VOS_FALSE;
    pstPdpPrimContextExt->enPdpType         = pstDialParam->enPdpType;
    pstPdpPrimContextExt->ucCid             = pstDialParam->ucCid;

    /* 获取APN */
    if (0 != pstDialParam->ucAPNLen)
    {
        pstPdpPrimContextExt->bitOpApn      = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)pstPdpPrimContextExt->aucApn,
                   (VOS_CHAR*)pstDialParam->aucAPN,
                   pstDialParam->ucAPNLen);
    }

    /* 获取静态IP地址，AT不考虑PDP类型，APS需要考虑，非IPV6不带静态IP地址 */
    if (VOS_TRUE == pstDialParam->ulIPv4ValidFlag )
    {
        ulRet = AT_LenStr2IpAddr(pstDialParam->aucIPv4Addr,pstPdpPrimContextExt->stPdpAddr.aucIpv4Addr);
        if (AT_SUCCESS == ulRet )
        {
            pstPdpPrimContextExt->bitOpPdpAddr        = VOS_TRUE;
            pstPdpPrimContextExt->stPdpAddr.enPdpType = TAF_PDP_IPV4;
        }
    }
}

/*****************************************************************************
 函 数 名  : AT_GetPsDialParamFromAtDialParam
 功能描述  : 获取拨号参数
 输入参数  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月31日
    作    者   : c00173809
    修改内容   : PS融合项目，获取拨号参数

  2.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目
*****************************************************************************/
VOS_VOID AT_GetPsDialParamFromAtDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstPsDialParam,
    AT_DIAL_PARAM_STRU                 *pstDialParam
)
{
    PS_MEM_SET((VOS_VOID *)pstPsDialParam, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstPsDialParam->enPdpType       = pstDialParam->enPdpType;
    pstPsDialParam->ucCid           = pstDialParam->ucCid;

    /* 获取APN */
    if (0 != pstDialParam->ucAPNLen)
    {
        pstPsDialParam->bitOpApn        = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)pstPsDialParam->aucApn,
                   (VOS_CHAR*)pstDialParam->aucAPN,
                   pstDialParam->ucAPNLen);
    }

    /* 填入验证信息 */
    pstPsDialParam->bitOpAuthType   = VOS_TRUE;
    pstPsDialParam->enAuthType      = (PPP_AUTH_TYPE_ENUM_UINT8)pstDialParam->usAuthType;

    if (0 != pstDialParam->usPasswordLen)
    {
        pstPsDialParam->bitOpPassWord = VOS_TRUE;
        PS_MEM_CPY((VOS_VOID *)pstPsDialParam->aucPassWord,
                   (VOS_VOID *)pstDialParam->aucPassword,
                   pstDialParam->usPasswordLen);
    }
    else
    {
        pstPsDialParam->bitOpPassWord = VOS_FALSE;
    }

    if (0 != pstDialParam->usUsernameLen)
    {
        pstPsDialParam->bitOpUserName = VOS_TRUE;
        PS_MEM_CPY((VOS_VOID *)pstPsDialParam->aucUserName,
                   (VOS_VOID *)pstDialParam->aucUsername,
                   pstDialParam->usUsernameLen);
    }
    else
    {
        pstPsDialParam->bitOpUserName = VOS_FALSE;
    }

}


/*****************************************************************************
 函 数 名  : AT_GetFcPriFromMap
 功能描述  : 获取指定FC ID的FC PRI
 输入参数  : FC_ID_ENUM_UINT8                   enFcId,
             AT_FCID_MAP_STRU                  *pstFcIdMap
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_GetFcPriFromMap(
    FC_ID_ENUM_UINT8                   enFcId,
    AT_FCID_MAP_STRU                  *pstFcIdMap
)
{
    if (enFcId >= FC_ID_BUTT)
    {
        return VOS_ERR;
    }

    if ((FC_ID_MODEM == enFcId)
     || (FC_ID_NIC_1 == enFcId)
     || (FC_ID_NIC_2 == enFcId)
     || (FC_ID_NIC_3 == enFcId)
     || (FC_ID_NIC_4 == enFcId)
     || (FC_ID_NIC_5 == enFcId)
     || (FC_ID_NIC_6 == enFcId)
     || (FC_ID_NIC_7 == enFcId)
     || (FC_ID_DIPC_1 == enFcId)
     || (FC_ID_DIPC_2 == enFcId)
     || (FC_ID_DIPC_3 == enFcId))
    {
        pstFcIdMap->ulUsed  = g_stFcIdMaptoFcPri[enFcId].ulUsed;
        pstFcIdMap->enFcPri = g_stFcIdMaptoFcPri[enFcId].enFcPri;

        return VOS_OK;
    }

    return VOS_ERR;
}




/*****************************************************************************
 函 数 名  : AT_NotifyFcWhenPdpModify
 功能描述  : 当发生PDP MODIFY(UE发起或网侧发起)时，向FC指示修改流控点
 输入参数  : pstEvt       TAF_PS_CALL_EVENT_INFO_STRU事件
             enFcId        流控实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NotifyFcWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_PRI_ENUM_UINT8                   enFCPriCurrent;
    AT_FCID_MAP_STRU                    stFCPriOrg;

    if (VOS_OK == AT_GetFcPriFromMap(enFcId, &stFCPriOrg))
    {
        if (TAF_USED == pstEvent->bitOpUmtsQos)
        {
            enFCPriCurrent = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
        }
        else
        {
            enFCPriCurrent = FC_PRI_FOR_PDN_NONGBR;
        }

        if ( (VOS_TRUE == stFCPriOrg.ulUsed)
           && (enFCPriCurrent > stFCPriOrg.enFcPri))
        {
            /* 根据返回QOS来改变流控点的优先级*/
            AT_ChangeFCPoint(&pstEvent->stCtrl,enFCPriCurrent,enFcId);
        }
    }

    return;
}



/***************************************************************************
               以下代码实现NDIS相关功能
*****************************************************************************/
/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */

/*****************************************************************************
 函 数 名  : AT_PutNetworkAddr32
 功能描述  : 主机序UINT32(LITTLE_ENDIAN)--->网络序数组
 输入参数  : VOS_UINT8                            *pucAddr
             VOS_UINT32                            ulAddr
 输出参数  : 无
 返 回 值  : VOS_UINT8*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月25日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 移植Porting项目代码

*****************************************************************************/
VOS_UINT8* AT_PutNetworkAddr32(
  VOS_UINT8                            *pucAddr,
  VOS_UINT32                            ulAddr
)
{
    *pucAddr = (ulAddr >> 24);
    pucAddr++;

    *pucAddr = ((ulAddr >> 16) & 0xFF);
    pucAddr++;

    *pucAddr = ((ulAddr >> 8) & 0xFF);
    pucAddr++;

    *pucAddr = (ulAddr & 0xFF);
    pucAddr++;

    return pucAddr;
}

/*****************************************************************************
 函 数 名  : AT_CovertArrayToU32
 功能描述  : 数组转为UINT32
 输入参数  : VOS_UINT8                            *pucAddr
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月16日
    作    者   : L00171473
    修改内容   : for V7R1 porting,新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 移植Porting项目代码

*****************************************************************************/
VOS_UINT32 AT_CovertArrayToU32(
  VOS_UINT8                            *pucAddr
)
{
    VOS_UINT32                          ulAddr;

    pucAddr += 4;

    pucAddr--;
    ulAddr = *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    ulAddr <<= 8;
    pucAddr--;
    ulAddr |= *(pucAddr);

    return ulAddr;
}

/*****************************************************************************
 函 数 名  : AT_NidsGet3gppSmCauseByPsCause
 功能描述  : 将PS域呼叫错误码转换成3GPP协议定义的(E)SM Cause, 非3GPP协议定义
             的错误码统一转换成0(Unknown error/Unspecified error)
 输入参数  : enCause - PS域呼叫错误码
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: 把PDP Deactive时上报的原因值TAF_PS_CAUSE_SUCCESS
                 转化为闪电卡的协议值36
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，入参和返回值类型改为VOS_UINT32
*****************************************************************************/
VOS_UINT32 AT_Get3gppSmCauseByPsCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT32                          ul3gppSmCause;

    if ( (enCause >= TAF_PS_CAUSE_SM_NW_SECTION_BEGIN)
      && (enCause <= TAF_PS_CAUSE_SM_NW_SECTION_END) )
    {
        ul3gppSmCause = enCause - TAF_PS_CAUSE_SM_NW_SECTION_BEGIN;
    }
    /* E5、闪电卡在PDP DEACTIVE时上报网侧的36号原因值 */
    else if (TAF_PS_CAUSE_SUCCESS == enCause)
    {
        ul3gppSmCause = TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION - TAF_PS_CAUSE_SM_NW_SECTION_BEGIN;
    }
    else
    {
        ul3gppSmCause = AT_NDISSTAT_ERR_UNKNOWN;
    }

    return ul3gppSmCause;
}

/*****************************************************************************
 函 数 名  : AT_SaveNdisConnDailPara
 功能描述  : 保存NDISCONN拨号时的参数，供NDISCONN查询命令使用
 输入参数  : AT_PARSE_PARA_TYPE_STRU            *pstParaList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月13日
    作    者   : L00171473
    修改内容   : for V7R1 porting,新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 移植Porting项目代码

  3.日    期   : 2012年5月15日
    作    者   : l60609
    修改内容   : DTS2012050800626:authType非chap和pap按chap保存
*****************************************************************************/
VOS_VOID AT_SaveNdisConnDailPara(
    AT_PARSE_PARA_TYPE_STRU            *pstParaList
)
{
    AT_NDISCONN_PARA_STRU               *pstNdisDailPara;
    VOS_UINT16                          usStrLen;

    pstNdisDailPara = AT_GetNdisConnParaAddr();

    PS_MEM_SET(pstNdisDailPara, 0x00, sizeof(AT_NDISCONN_PARA_STRU));

    pstNdisDailPara->ulConnectState = pstParaList[AT_NDIS_CONN_IDX].ulParaValue;
    pstNdisDailPara->ucCID = (VOS_UINT8)pstParaList[AT_NDIS_CID_IDX].ulParaValue;

    usStrLen = pstParaList[AT_NDIS_APN_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_APN_LEN )
    {
        usStrLen = TAF_MAX_APN_LEN;
    }
    PS_MEM_CPY((VOS_CHAR*)pstNdisDailPara->aucAPN,
               (VOS_CHAR*)pstParaList[AT_NDIS_APN_IDX].aucPara, usStrLen);

    usStrLen = pstParaList[AT_NDIS_NAME_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_GW_AUTH_USERNAME_LEN )
    {
        usStrLen = TAF_MAX_GW_AUTH_USERNAME_LEN;
    }
    PS_MEM_CPY((VOS_CHAR*)pstNdisDailPara->aucUsername,
               (VOS_CHAR*)pstParaList[AT_NDIS_NAME_IDX].aucPara, usStrLen);

    usStrLen = pstParaList[AT_NDIS_PWD_IDX].usParaLen;
    if ( usStrLen > TAF_MAX_GW_AUTH_PASSWORD_LEN )
    {
        usStrLen = TAF_MAX_GW_AUTH_PASSWORD_LEN;
    }
    PS_MEM_CPY((VOS_CHAR*)pstNdisDailPara->aucPassword,
               (VOS_CHAR*)pstParaList[AT_NDIS_PWD_IDX].aucPara, usStrLen);

    pstNdisDailPara->usAuthType = AT_CtrlGetPDPAuthType(pstParaList[AT_NDIS_AUTH_IDX].ulParaValue,
                                                        pstParaList[AT_NDIS_AUTH_IDX].usParaLen);
}

/*****************************************************************************
 函 数 名  : AT_SendNdisRelReq
 功能描述  : 发送PDN配置释放消息
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月26日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 移植Porting项目代码
  3.日    期   : 2011年12月22日
    作    者   : 鲁琳/l60609
    修改内容   : PS Project: AT和NDIS的消息改变
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_UINT32 AT_SendNdisRelReq(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
)
{
    AT_NDIS_PDNINFO_REL_REQ_STRU        stNdisRelReq;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SendNdisRelReq:Get Modem Id fail");
        return VOS_ERR;
    }

    /* 构造消息 */
    stNdisRelReq.enModemId = enModemId;
    stNdisRelReq.ucRabId   = pstEvent->ucRabId;



    /* 发送消息 */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_REL_REQ,
                                            sizeof(AT_NDIS_PDNINFO_REL_REQ_STRU),
                                            (VOS_UINT8*)&stNdisRelReq))
    {
        AT_ERR_LOG("GUAT_SendNdisRelReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_ActiveUsbNet
 功能描述  : 激活USB虚拟网卡
 输入参数  : VOS_UINT32                          ulRxbps,
             VOS_UINT32                          ulTxbps
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : C00173809
    修改内容   : PS 融合项目，激活网卡
*****************************************************************************/
VOS_UINT32 AT_ActiveUsbNet(VOS_VOID)
{
    VOS_UINT32                      ulLinkstus;
    VOS_INT32                       lRtn;
    NCM_IOCTL_CONNECTION_SPEED_S    stNcmConnectSpeed;
    VOS_UINT32                      ulSpeed;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &ulSpeed))
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        AT_ERR_LOG("AT_ActiveUsbNet : ERROR : AT_GetDisplayRate Error!");
        ulSpeed = AT_DEF_DISPLAY_SPEED;
    }
    stNcmConnectSpeed.u32DownBitRate   = ulSpeed;
    stNcmConnectSpeed.u32UpBitRate     = ulSpeed;

    lRtn        = mdrv_udi_ioctl(g_ulAtUdiNdisHdl, NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, (VOS_VOID *)(&stNcmConnectSpeed));
    if (0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Ctrl Speed Fail!" );
        return VOS_ERR;
    }

    ulLinkstus  = NCM_IOCTL_CONNECTION_LINKUP;
    lRtn        = mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_NETWORK_CONNECTION_NOTIF, &ulLinkstus);
    if (0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Active usb net Fail!" );
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DeActiveUsbNet
 功能描述  : 去激活USB虚拟网卡
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : c00173809
    修改内容   : PS 融合项目，去激活网卡
*****************************************************************************/
VOS_UINT32 AT_DeActiveUsbNet(VOS_VOID)
{
    VOS_UINT32  ulLinkstus;
    VOS_INT32   lRtn;

    /*去激活，已和BSP确认，如果本来是去激活，再去激活并没有影响*/
    ulLinkstus = NCM_IOCTL_CONNECTION_LINKDOWN;

    lRtn  = mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_NETWORK_CONNECTION_NOTIF, (VOS_VOID*)(&ulLinkstus));
    if(0 != lRtn)
    {
        AT_ERR_LOG("AT_ActiveUsbNet, Deactive usb net Fail!" );
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_SendNdisIPv4PdnInfoCfgReq
 功能描述  : 向NDIS发送构建的IPV4的PDN信息。
 输入参数  : MN_CLIENT_ID_T                      usClientId
             AT_IPV4_DHCP_PARAM_STRU            *pstIPv4DhcpParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : C00173809
    修改内容   : PS融合项目，获取本地的IPV4 PDN信息

  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，由CLIENTID获取MODEM ID

  3.日    期   : 2015年4月18日
    作    者   : A00165503
    修改内容   : SPE Project: SPE适配
*****************************************************************************/
VOS_UINT32 AT_SendNdisIPv4PdnInfoCfgReq(
    MN_CLIENT_ID_T                      usClientId,
    AT_IPV4_DHCP_PARAM_STRU            *pstIPv4DhcpParam
)
{
    AT_COMM_PS_CTX_STRU                *pstPsCntxt = VOS_NULL_PTR;
    AT_NDIS_PDNINFO_CFG_REQ_STRU        stNdisCfgReq;
    VOS_UINT32                          ulSpeed;
    VOS_UINT32                          ulRelt;

    pstPsCntxt = AT_GetCommPsCtxAddr();

    /* 初始化 */
    PS_MEM_SET(&stNdisCfgReq, 0x00, sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU));

    ulRelt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)usClientId, &stNdisCfgReq.enModemId);

    if (VOS_OK != ulRelt)
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq:Get Modem Id fail");
        return VOS_ERR;
    }

    stNdisCfgReq.bitOpIpv4PdnInfo       = VOS_TRUE;
    stNdisCfgReq.ulHandle               = g_ulAtUdiNdisHdl;

    /* 构造消息 */
    if (0 != pstIPv4DhcpParam->ucRabId )
    {
        stNdisCfgReq.ucRabId = pstIPv4DhcpParam->ucRabId;
    }

    /* 填写IPv4地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4Addr)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPdnAddr     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPDNAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4Addr);
    }

    /* 填写掩码地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4NetMask)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stSubnetMask.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4NetMask);
    }

    /* 填写网关地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4GateWay)
    {
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stGateWayAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4GateWay);
    }

    /* 填写主DNS地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4PrimDNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpDnsPrim     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stDnsPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimDNS);

    }

    /* 填写辅DNS地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4SecDNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpDnsSec      = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stDnsSecAddrInfo.aucIpV4Addr,
                          pstIPv4DhcpParam->ulIpv4SecDNS);

    }

    /* 填写主WINS地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4PrimWINNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpWinsPrim    = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stWinsPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimWINNS);
    }

    /* 填写辅WINS地址 */
    if (0 != pstIPv4DhcpParam->ulIpv4SecWINNS)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpWinsSec     = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stWinsSecAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4SecWINNS);
    }

    /* 填写主PCSCF地址 */
    if (VOS_TRUE == pstIPv4DhcpParam->bitOpIpv4PriPCSCF)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPcscfPrim   = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPcscfPrimAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4PrimPCSCF);
    }

    /* 填写副PCSCF地址 */
    if (VOS_TRUE == pstIPv4DhcpParam->bitOpIpv4Secpcscf)
    {
        stNdisCfgReq.stIpv4PdnInfo.bitOpPcscfSec    = VOS_TRUE;
        AT_PutNetworkAddr32(stNdisCfgReq.stIpv4PdnInfo.stPcscfSecAddrInfo.aucIpV4Addr,
                            pstIPv4DhcpParam->ulIpv4SecPCSCF);
    }

    /* 获取接入理论带宽*/
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &ulSpeed))
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq : ERROR : AT_GetDisplayRate Error!");
        ulSpeed = AT_DEF_DISPLAY_SPEED;
    }

    stNdisCfgReq.ulMaxRxbps = ulSpeed;
    stNdisCfgReq.ulMaxTxbps = ulSpeed;

    stNdisCfgReq.lSpePort   = pstPsCntxt->lSpePort;
    stNdisCfgReq.ulIpfFlag  = pstPsCntxt->ulIpfPortFlg;

    /* 发送消息 */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_CFG_REQ,
                                            (VOS_UINT16)sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU),
                                            (VOS_UINT8*)&stNdisCfgReq))
    {
        AT_ERR_LOG("AT_SendNdisIPv4PdnInfoCfgReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvNdisPdnInfoCfgCnf
 功能描述  : NDIS配置的结果处理
 输入参数  : AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月25日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 移植Porting项目代码

  3.日    期   : 2011年12月25日
    作    者   : C00173809
    修改内容   : PS融合项目，激活网卡。

  4.日    期   : 2012年3月15日
    作    者   : l60609
    修改内容   : DTS2012030804093:先激活网卡，再上报^NDISDUP

  5.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoCfgCnf(
    AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
)
{
    if (AT_NDIS_PDNCFG_CNF_FAIL == pstNdisPdnInfoCfgCnf->enResult)
    {
        AT_ERR_LOG("AT_RcvNdisPdnInfoRelCnf: Failed.");
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvNdisPdnInfoRelCnf
 功能描述  : NDIS释放应答处理
 输入参数  : AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月25日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 移植Porting项目代码

  3.日    期   : 2011年12月25日
    作    者   : C00173809
    修改内容   : PS融合项目，去激活网卡。

  4.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoRelCnf(
    AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
)
{
    if (AT_NDIS_SUCC != pstNdisPdnInfoRelCnf->enResult)
    {
        AT_ERR_LOG("AT_RcvNdisPdnInfoRelCnf: Failed.");
    }

    return VOS_OK;
}



#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_NdisConfigIpv6Dns
 功能描述  : 通过底软配置IPv6 DNS
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理

*****************************************************************************/
VOS_VOID AT_NdisConfigIpv6Dns(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    NCM_IPV6DNS_S                       stIPv6Dns;
    VOS_INT32                           lRslt;

    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();

    stIPv6Dns.pu8Ipv6DnsInfo = (unsigned char*)PS_MEM_ALLOC(
                                    WUEPS_PID_AT,
                                    BSP_NCM_IPV6_DNS_LEN);

    if (VOS_NULL_PTR == stIPv6Dns.pu8Ipv6DnsInfo)
    {
        AT_ERR_LOG("AT_NdisConfigIpv6Dns:Invalid stIPv6Dns.pu8Ipv6DnsInfo");
        return;
    }

    PS_MEM_SET(stIPv6Dns.pu8Ipv6DnsInfo, 0x00, BSP_NCM_IPV6_DNS_LEN);

    /* 上报给底软的DNS长度固定为32(Primary DNS LEN + Secondary DNS LEN) */
    stIPv6Dns.u32Length = BSP_NCM_IPV6_DNS_LEN;

    /*如果有DNS，需要调用DRV的接口上报DNS给PC*/
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns)
    {
        PS_MEM_CPY(stIPv6Dns.pu8Ipv6DnsInfo,
                   pstNdisPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                   AT_MAX_IPV6_DNS_LEN);
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns)
    {
        PS_MEM_CPY(stIPv6Dns.pu8Ipv6DnsInfo + AT_MAX_IPV6_DNS_LEN,
                   pstNdisPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   AT_MAX_IPV6_DNS_LEN);
    }

    /* 设置低软主副DNS信息 */
    lRslt = mdrv_udi_ioctl(g_ulAtUdiNdisHdl, NCM_IOCTL_SET_IPV6_DNS, &stIPv6Dns);
    if (0 != lRslt)
    {
        AT_ERR_LOG("AT_NdisConfigIpv6Dns, DRV_UDI_IOCTL Fail!" );
    }

    /* 释放申请的内存 */
    PS_MEM_FREE(WUEPS_PID_AT, stIPv6Dns.pu8Ipv6DnsInfo);

}

/*****************************************************************************
 函 数 名  : AT_NdisActCnfBackProc
 功能描述  : PDP激活成功后的回退处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月12日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2011年12月25日
    作    者   : c00173809
    修改内容   : PS 融合项目，IPV6特性移植

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理

  4.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII

  5.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，原因值#50 , 通知APP模块IPv6激活失败，
                 原因值#51 , 通知APP模块IPv4激活失败

  6.日    期   : 2015年7月17日
    作    者   : Y00213812
    修改内容   : CDMA模式下电信不支持双承载双栈
*****************************************************************************/
VOS_VOID  AT_NdisActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    /* 不带原因值或原因值为52，需要发起另一种PDP激活 */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
            {
                /* 查找一个未激活的CID进行激活 */
                ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                }
            }
        }
        else if (TAF_PDP_IPV6 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV4))
            {
                /* 查找一个未激活的CID进行激活 */
                ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV4);
                }
            }
        }
        else
        {
            ;
        }

        return;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 根据原因值, 通知APP拨号结果 */
    switch (pstEvent->enCause)
    {
        /* 原因值#50 (IPv4 ONLY), 通知APP模块IPv6激活失败 */
        case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED:
#endif

            AT_NdisStateChangeProc(TAF_PDP_IPV6, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            break;

        /* 原因值#51 (IPv6 ONLY), 通知APP模块IPv4激活失败 */
        case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED:
#endif
            AT_NdisStateChangeProc(TAF_PDP_IPV4, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            break;

        /* 其他原因值, 不处理 */
        default:
            AT_NORM_LOG1("AT_NdisActCnfBackProc: Other <Cause>", pstEvent->enCause);
            break;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisIpv6ActCnfProc
 功能描述  : 处理IPV6的PDP激活成功的事件
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月12日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，通过ID_AT_NDIS_PDNINFO_CFG_REQ原语向NDIS发送IPV6的PDN信息。

  3.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改

  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NdisIpv6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    /* 初始化 */
    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    g_stAtNdisDhcpPara.ucIpv6Cid   = pstEvent->ucCid;

    /* 处理IPV6地址 */
    AT_NdisCtrlConnIpv6IndProc(pstEvent);

    /* NDIS用户类型的PDP激活后,处理流控点注册或变更 */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV6);

    /* NDIS用户类型的PDP激活后, 处理激活SharePdp状态*/
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV6);

    /* 通过底软上报IPv6 DNS */
    AT_NdisConfigIpv6Dns();

    /* 如果是IPV4V6，需要激活另一个PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        switch (g_enAtNdisActPdpType)
        {
            case TAF_PDP_IPV6:
                /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
                   IPV6的PDP激活, IPV6激活后不再发起IPV4的PDP激活 */
                break;

            /* 这里是PDP激活回退功能实现 */
            case TAF_PDP_IPV4V6:
                /* 将该PDP切换到IDLE态 */
               AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

               AT_NdisActCnfBackProc(pstEvent);
               break;

            default:
               AT_WARN_LOG("AT_NdisIpv6ActCnfProc:g_enAtNdisActPdpType is error!");
               break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisIpv4v6ActCnfProc
 功能描述  : 处理IPV4v6的PDP激活成功的事件
 输入参数  : pstEvent --- 事件内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月12日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，PDP激活成功后通知ADS,NDIS；注册流控点。

  3.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NdisIpv4v6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    VOS_UINT8                           aucIpv6Dns[AT_MAX_IPV6_DNS_LEN * 2];

    /* 初始化 */
    PS_MEM_SET(aucIpv6Dns, 0x00, sizeof(aucIpv6Dns));

    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    g_stAtNdisDhcpPara.ucIpv4v6Cid   = pstEvent->ucCid;

    /* 处理IPV4类型的DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_NDIS_USER);

    /* 处理IPV6地址*/
    AT_NdisCtrlConnIpv6IndProc(pstEvent);

    /* NDIS用户类型的PDP状态改变后,处理流控点注册或变更 */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV4V6);

    /* 把IPV4的PDN信息发送给NDIS模块 */
    AT_SendNdisIPv4PdnInfoCfgReq(pstEvent->stCtrl.usClientId,
                                 &(g_stAtNdisDhcpPara.stIpv4Dhcp));


    /* NDIS用户类型的PDP激活后, 处理激活SharePdp状态*/
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4V6);

    /* 通知NDIS PDP激活成功,ipv6的PDN信息在收到RA参数时发送 */

    /* 通过底软上报IPv6 DNS */
    AT_NdisConfigIpv6Dns();

    return;
}

/*****************************************************************************
 函 数 名  : AT_SendNdisIPv6PdnInfoCfgReq
 功能描述  : 发送IPV6的PDN信息
 输入参数  : MODEM_ID_ENUM_UINT16                 enModemId,
             TAF_PS_IPV6_INFO_IND_STRU* pRaInfo
 输出参数  : 无
 返 回 值  : AT_APS_IPV6_RA_INFO_STRU* pIPv6RaInfo
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : C00173809
    修改内容   : PS融合项目，获取本地的IPV6 PDN信息

  2.日    期   : 2015年4月18日
    作    者   : A00165503
    修改内容   : SPE Project: SPE适配
*****************************************************************************/
VOS_UINT32 AT_SendNdisIPv6PdnInfoCfgReq(
    MODEM_ID_ENUM_UINT16                 enModemId,
    TAF_PS_IPV6_INFO_IND_STRU           *pIPv6RaNotify
)
{
    AT_COMM_PS_CTX_STRU                *pstPsCntxt = VOS_NULL_PTR;
    AT_NDIS_PDNINFO_CFG_REQ_STRU        stNdisCfgReq;
    VOS_UINT32                          ulSpeed;
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;

    pstPsCntxt = AT_GetCommPsCtxAddr();

    /* 初始化 */
    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();
    PS_MEM_SET(&stNdisCfgReq, 0x00, sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU));

    stNdisCfgReq.ulHandle               = g_ulAtUdiNdisHdl;
    stNdisCfgReq.bitOpIpv6PdnInfo       = VOS_TRUE;
    stNdisCfgReq.enModemId              = enModemId;
    stNdisCfgReq.ucRabId                = pIPv6RaNotify->ucRabId;

    /* 填充主副DNS */
    stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum    = 0;
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns)
    {
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucPriServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                    TAF_IPV6_ADDR_LEN);
        stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum += 1;
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns)
    {
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stDnsSer.aucSecServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                    TAF_IPV6_ADDR_LEN);
        stNdisCfgReq.stIpv6PdnInfo.stDnsSer.ucSerNum += 1;
    }

    /* 填充MTU */
    if (VOS_TRUE == pIPv6RaNotify->stIpv6RaInfo.bitOpMtu)
    {
        stNdisCfgReq.stIpv6PdnInfo.ulBitOpMtu   = VOS_TRUE;
        stNdisCfgReq.stIpv6PdnInfo.ulMtu        = pIPv6RaNotify->stIpv6RaInfo.ulMtu;
    }

    stNdisCfgReq.stIpv6PdnInfo.ulBitCurHopLimit = pIPv6RaNotify->stIpv6RaInfo.ulBitCurHopLimit;
    stNdisCfgReq.stIpv6PdnInfo.ulBitM           = pIPv6RaNotify->stIpv6RaInfo.ulBitM;
    stNdisCfgReq.stIpv6PdnInfo.ulBitO           = pIPv6RaNotify->stIpv6RaInfo.ulBitO;
    stNdisCfgReq.stIpv6PdnInfo.ulPrefixNum      = pIPv6RaNotify->stIpv6RaInfo.ulPrefixNum;
    PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.astPrefixList,
                (VOS_VOID *)pIPv6RaNotify->stIpv6RaInfo.astPrefixList,
                sizeof(TAF_PDP_IPV6_PREFIX_STRU)*TAF_MAX_PREFIX_NUM_IN_RA);

    /* 填写INTERFACE，取IPV6地址的后8字节来填写INTERFACE */
    PS_MEM_CPY((VOS_VOID*)stNdisCfgReq.stIpv6PdnInfo.aucInterfaceId,
               (VOS_VOID*)pstNdisPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                sizeof(VOS_UINT8)*AT_NDIS_IPV6_IFID_LENGTH);

    /* 填充主副PCSCF地址  */
    stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum      = 0;
    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6PriPCSCF)
    {
        stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum += 1;
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucPriServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr,
                    sizeof(pstNdisPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr));
    }

    if (VOS_TRUE == pstNdisPdpEntity->stIpv6Dhcp.bitOpIpv6SecPCSCF)
    {
        stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.ucSerNum += 1;
        PS_MEM_CPY((VOS_VOID *)stNdisCfgReq.stIpv6PdnInfo.stPcscfSer.aucSecServer,
                    pstNdisPdpEntity->stIpv6Dhcp.aucSecPcscfAddr,
                    sizeof(pstNdisPdpEntity->stIpv6Dhcp.aucSecPcscfAddr));
    }

    /* 获取接入理论带宽*/
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (VOS_OK != AT_GetDisplayRate(AT_CLIENT_ID_NDIS, &ulSpeed))
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        AT_ERR_LOG("AT_SendNdisIPv6PdnInfoCfgReq : ERROR : AT_GetDisplayRate Error!");
        ulSpeed = AT_DEF_DISPLAY_SPEED;
    }

    stNdisCfgReq.ulMaxRxbps = ulSpeed;
    stNdisCfgReq.ulMaxTxbps = ulSpeed;

    stNdisCfgReq.lSpePort   = pstPsCntxt->lSpePort;
    stNdisCfgReq.ulIpfFlag  = pstPsCntxt->ulIpfPortFlg;

    /* 发送消息 */
    if (ERR_MSP_SUCCESS != AT_FwSendClientMsg(PS_PID_APP_NDIS,
                                            ID_AT_NDIS_PDNINFO_CFG_REQ,
                                            (VOS_UINT16)sizeof(AT_NDIS_PDNINFO_CFG_REQ_STRU),
                                            (VOS_UINT8*)&stNdisCfgReq))
    {
        AT_ERR_LOG("AT_SendNdisIPv6PdnInfoCfgReq: Send client msg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_NdisCtrlConnIpv6IndProc
 功能描述  : 处理IPV6地址
 输入参数  : pstEvent ---上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年01月02日
    作    者   : c00173809
    修改内容   : PS融合项目，保存IPV6的PCSCF地址
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID  AT_NdisCtrlConnIpv6IndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
    g_stAtNdisDhcpPara.stIpv6Dhcp.ucRabId  = pstEvent->ucRabId;

    /* 处理IPV6的IP地址，形式为网络序 */
    PS_MEM_CPY(g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr,
               pstEvent->stPdpAddr.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    /* 处理IPV6的主副DNS地址，形式为网络序 */
    AT_SaveIPv6Dns(pstEvent, &g_stAtNdisDhcpPara);

    /* 处理IPV6的主副PCSCF地址，形式为网络序 */
    AT_SaveIPv6Pcscf(pstEvent, &g_stAtNdisDhcpPara);

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisIpv6DhcpRest
 功能描述  : 清空IPV6地址参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月9日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_NdisIpv6DhcpRest(VOS_VOID)
{
    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisCheckIpv6PdpState
 功能描述  : 检查是否有满足IPv6状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv6State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : AT_NdisCheckIpv6PdpState
 功能描述  : 检查是否有满足IPv4状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv4State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_NdisCheckPdpState
 功能描述  : 检查是否有满足状态的NDIS连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - NDIS状态满足条件
             VOS_TRUE   - NDIS状态不满足条件
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月13日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    if ( (enPdpState == g_stAtNdisDhcpPara.enIpv4State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv6State)
      || (enPdpState == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_NdisCheckPdpIdleState
 功能描述  : 查找是否有idel或deacting的PDP
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月18日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpIdleState(VOS_VOID)
{
    /*如果所有的PDP都处于IDLE;如果有一个处于DEACTING也返回OK*/
    if ( (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv4State)
      || (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv6State)
      || (AT_PDP_STATE_DEACTING == g_stAtNdisDhcpPara.enIpv4v6State)
      || ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
        && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
        && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_NdisAddrProc
 功能描述  : 处理NDIS地址参数
 输入参数  : pstConfig --- 指向DHCP参数的指针
             pstEvent  --- 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2011年12月1日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011113002867, 支持PC UI口进行NDIS拨号并写地址到NV
  3.日    期   : 2012年1月2日
    作    者   : c00173809
    修改内容   : ps融合项目，保存IPV4的PCSCF地址
  4.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2015031000157, 新增第三个p-cscf地址
*****************************************************************************/
VOS_VOID  AT_NdisAddrProc(
    AT_DHCP_CONFIG_STRU                 *pstConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         *pstEvent
)
{
    VOS_UINT32                          ulIpAddr;

    g_stAtNdisDhcpPara.stIpv4Dhcp.ucRabId                 = pstEvent->ucRabId;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr              = pstConfig->ulIPAddr;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay           = pstConfig->ulGateWay;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask           = pstConfig->ulSubNetMask;


    /* 如果用户设置了主DNS，就使用用户设置的DNS，网络返回的DNS不使用 */
    if (VOS_TRUE == gstAtNdisAddParam.ulPrimIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucPrimIPv4DNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns     = VOS_TRUE;
        }
    }
    else
    {
        if ( 0 != pstConfig->ulPrimDNS )
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns = VOS_TRUE;
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS   = pstConfig->ulPrimDNS;
        }
        else
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* 如果用户设置了副DNS，就使用用户设置的DNS，网络返回的DNS不使用 */
    if (VOS_TRUE == gstAtNdisAddParam.ulSndIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucSndIPv4DNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS    = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
        }
    }
    else
    {
        if ( 0 != pstConfig->ulSndDNS)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS    = pstConfig->ulSndDNS;
        }
        else
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    /* 如果用户设置了主WINS，就使用用户设置的WINS，网络返回的WINS不使用 */
    if (VOS_TRUE == gstAtNdisAddParam.ulPrimIPv4WINNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucPrimIPv4WINNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimWINNS     = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriWINNS   = VOS_TRUE;
        }
    }
    else
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimWINNS     = 0;
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriWINNS   = VOS_FALSE;
    }

    /* 如果用户设置了副WINS，就使用用户设置的WINS，网络返回的WINS不使用 */
    if (VOS_TRUE == gstAtNdisAddParam.ulSndIPv4WINNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(gstAtNdisAddParam.aucSndIPv4WINNSAddr, (VOS_UINT8 *)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        if (0 != ulIpAddr)
        {
            g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecWINNS      = VOS_NTOHL(ulIpAddr);
            g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecWINNS   = VOS_TRUE;
        }
    }
    else
    {
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecWINNS      = 0;
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4SecWINNS   = VOS_FALSE;
    }

    /* 获取主PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpPrimPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4PriPCSCF = VOS_TRUE;
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimPCSCF   = AT_GetLanAddr32(pstEvent->stPcscf.aucPrimPcscfAddr);
    }

    /* 获取副PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpSecPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecPCSCF    = AT_GetLanAddr32(pstEvent->stPcscf.aucSecPcscfAddr);
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4Secpcscf = VOS_TRUE;
    }

    /* 获取第三PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpThiPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4ThiPCSCF    = AT_GetLanAddr32(pstEvent->stPcscf.aucThiPcscfAddr);
        g_stAtNdisDhcpPara.stIpv4Dhcp.bitOpIpv4Thipcscf = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisStateChangeProc
 功能描述  : NDIS拨号时通知PC拨号状态改变
 输入参数  : pEvent -- TAF_PS_CALL_EVENT_INFO_STRU消息指针
             ulStat----NDIS连接状态:0-连接断开; 1-已连接
 输出参数  : 无
 返 回 值  : 成功
             失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月8日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2010年07月04日
    作    者   : S62952
    修改内容   : 问题单号: DTS2011070103435, IPv4v6类型拨号失败, 上报^NDISSTAT
                 格式错误, 两条连续的上报命令之间缺少一个回车换行符

  3.日    期   : 2011年08月02日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011080103770, 网侧DETACH的场景下, AT多上报两条
                 ^NDISSTAT命令指示MP拨号已断开

  4.日    期   : 2011年12月12日
    作    者   : L00171473
    修改内容   : 问题单号: DTS2011110807367, 通过PCUI口进行NDIS拨号打桩(原不允许
                 从PCUI口发起NDIS拨号)

  5.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，修改同步API

  6.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改

  7.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理

  8.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: PDP Deactive时上报原因值

  9.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_NdisStateChangeProc(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATUS_ENUM_UINT32           enStat,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
#if(FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";
#endif

    VOS_UINT32                          ul3gppSmCause;

    usLength = 0;

    if (AT_PDP_STATUS_DEACT == enStat)
    {
        ul3gppSmCause = AT_Get3gppSmCauseByPsCause(enCause);

        switch (ucPdpType)
        {
            case TAF_PDP_IPV4:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);
                break;

#if(FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV4V6:

                usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);

                At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

                usLength  = 0;

                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,%d,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            ul3gppSmCause,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;
#endif

            default:
                AT_ERR_LOG("AT_NdisStateChangeProc:ERROR: Wrong PDP type!");
                return;
        }
    }
    else
    {
        switch (ucPdpType)
        {
            case TAF_PDP_IPV4:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);
                break;

#if(FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
                usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;

            case TAF_PDP_IPV4V6:
                usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv4,
                                            gaucAtCrLf);

                At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

                usLength  = 0;

                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                            "%s^NDISSTAT:%d,,,\"%s\"%s",
                                            gaucAtCrLf,
                                            enStat,
                                            aucAtStrIpv6,
                                            gaucAtCrLf);
                break;
#endif

            default:
                AT_ERR_LOG("AT_NdisStateChangeProc:ERROR: Wrong PDP type!");
                return;
        }
    }

    At_SendResultData(AT_NDIS_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisGetState
 功能描述  : 获取NDIS状态，激活态/非激活态
 输入参数  : ucPdpType --- PDP类型
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8 当前状态 激活态/非激活态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月3日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_NdisGetState(
    VOS_UINT8                           ucPdpType
)
{
    if (TAF_PDP_IPV4 == ucPdpType )
    {
        return g_stAtNdisDhcpPara.enIpv4State;
    }
    else if (TAF_PDP_IPV6 == ucPdpType )
    {
        return g_stAtNdisDhcpPara.enIpv6State;
    }
    else
    {
        return g_stAtNdisDhcpPara.enIpv4v6State;
    }
}

/*****************************************************************************
 函 数 名  : AT_NdisSetState
 功能描述  : 设置NDIS状态
 输入参数  : ucPdpType --- PDP类型
             enState   --- PDP状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月3日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，增加PDP IPv4v6类型的判断
*****************************************************************************/
VOS_VOID AT_NdisSetState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enState
)
{
    if (TAF_PDP_IPV4 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv4State   = enState;
    }
/* Modified by s62952 for AT Project，2011-10-17,  Begin*/
#if(FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv6State   = enState;
    }
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    else if (TAF_PDP_IPV4V6 == ucPdpType)
    {
        g_stAtNdisDhcpPara.enIpv4v6State = enState;
    }
    else
    {}

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#endif
/* Modified by s62952 for AT Project，2011-10-17,  Begin*/

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisDhcpRest
 功能描述  : 清空DHCP参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月9日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_NdisDhcpRest(VOS_VOID)
{
    PS_MEM_SET(&g_stAtNdisDhcpPara.stIpv4Dhcp,
               0x00,
               sizeof(AT_IPV4_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : AT_E5GetDhcpPara
 功能描述  : 获取DHCP参数(DHCP参数为网络序)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月10日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_NdisGetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig
)
{
    /* 将DHCP参数转换为网络序 */
    pstConfig->stDhcpCfg.ulIPAddr     = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr);
    pstConfig->stDhcpCfg.ulSubNetMask = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask);
    pstConfig->stDhcpCfg.ulGateWay    = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay);
    pstConfig->stDhcpCfg.ulPrimDNS    = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4PrimDNS);
    pstConfig->stDhcpCfg.ulSndDNS     = VOS_HTONL(g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4SecDNS);
    return;
}

/*****************************************************************************
 函 数 名  : AT_ProcNdisDeRegFCPoint
 功能描述  : NDIS用户类型PDP状态改变为去激活时的处理
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增

*****************************************************************************/
VOS_VOID  AT_ProcNdisDeRegFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8               enPdpType
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ProcNdisDeRegFCPoint:Get Modem Id fail");
        return;
    }

    /* 去注册NDIS端口的流控点 */
    AT_DeRegNdisFCPoint(pstEvent->ucRabId, enModemId);

}

/*****************************************************************************
 函 数 名  : AT_ProcNdisRegFCPoint
 功能描述  : NDIS用户类型的PDP状态改变后,处理流控点注册或变更
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增

*****************************************************************************/
VOS_VOID  AT_ProcNdisRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulRet;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_PRI_ENUM_UINT8                   enFCPriCurrent;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId                           = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ProcNdisRegFCPoint:Get Modem Id fail");
        return;
    }

    ulRet = AT_GetFcPriFromMap(FC_ID_NIC_1 ,&stFCPriOrg);
    if (VOS_OK == ulRet)
    {
        /* 如果FC ID未注册，那么注册该流控点。目前只支持一个网卡.*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* 注册NDIS端口的流控点 */
            AT_RegNdisFCPoint(pstEvent, FC_ID_NIC_1, enModemId);
        }
        else
        {
            if (TAF_USED == pstEvent->bitOpUmtsQos)
            {
                enFCPriCurrent = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
            }
            else
            {
                enFCPriCurrent = FC_PRI_FOR_PDN_NONGBR;
            }

            /* 如果当前FC优先级比之前承载的FC优先级高，那么调整优先级。*/
            if(enFCPriCurrent > stFCPriOrg.enFcPri)
            {
                AT_ChangeFCPoint(&pstEvent->stCtrl,enFCPriCurrent, FC_ID_NIC_1);
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : AT_NdisIpv4ActCnfProc
 功能描述  : 处理IPV4的PDP激活成功的事件
 输入参数  : pstEvent --- 事件内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月12日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: V3R2/V7R1不支持IPv6特性, 实现方案待定
  3.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，NDIS端口发起拨号,通过FEATURE_IPV6宏隔离IPV6特性
  4.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_VOID  AT_NdisIpv4ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
)
{
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;
#endif

    g_stAtNdisDhcpPara.ucIpv4Cid = pstEvent->ucCid;

    /* 处理IPV4类型的DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_NDIS_USER);

    /* NDIS用户类型的PDP状态改变后,处理流控点注册或变更 */
    AT_ProcNdisRegFCPoint(pstEvent, TAF_PDP_IPV4);

    /* 把IPV4的PDN信息发送给NDIS模块 */
    AT_SendNdisIPv4PdnInfoCfgReq(pstEvent->stCtrl.usClientId,
                                 &(g_stAtNdisDhcpPara.stIpv4Dhcp));

    /* NDIS用户类型的PDP激活后, 处理激活SharePdp状态 */
    AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是IPV4V6，需要激活另一个PDP */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        switch (g_enAtNdisActPdpType)
        {
            /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
               IPV6的PDP激活。其中，TAF_PDP_IPV6是异常情况，用户发起IPV6的PDP
               激活，而网络回复IPV4的激活，此时也需要重新发起IPV6的PDP激活 */
            case TAF_PDP_IPV4:
                if (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
                {
                    /* 查找一个未激活的CID进行激活 */
                    ulRet       = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet )
                    {
                        AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
                break;

            /* 这里是PDP激活回退功能实现 */
            case TAF_PDP_IPV4V6:
                /* 将该PDP切换到IDLE态 */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                AT_NdisActCnfBackProc(pstEvent);
                break;

            default:
                AT_WARN_LOG("AT_NdisIpv4ActCnfProc:g_enAtNdisActPdpType is error!");
                break;
        }
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpActEvtCnfProc
 功能描述  : pdp激活失败，Ndis处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: V3R2/V7R1不支持IPv6特性, 实现方案待定

  3.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，NDIS拨号成功处理

  4.日    期   : 2012年3月15日
    作    者   : l60609
    修改内容   : DTS2012030804093:先激活网卡，再上报^NDISDUP

  5.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改

  6.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: 通知PDP激活成功时上报原因值TAF_PS_CAUSE_SUCCESS
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /*激活网卡*/
    AT_ActiveUsbNet();

    /* 通知PC激活 */
    AT_NdisStateChangeProc(pstEvent->stPdpAddr.enPdpType, AT_PDP_STATE_ACTED, TAF_PS_CAUSE_SUCCESS);

    /* 将本PDP 类型状态切换到act态 */
    AT_NdisSetState(pstEvent->stPdpAddr.enPdpType, AT_PDP_STATE_ACTED);

    /* 根据PDP类型分别处理*/
    switch ( pstEvent->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            AT_NdisIpv4ActCnfProc(pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_NdisIpv6ActCnfProc(pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_NdisIpv4v6ActCnfProc(pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_NdisPsRspPdpActEvtCnfProc:pdp type invaild!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisPdpActOrig
 功能描述  : 发起PDP激活
 输入参数  :  VOS_UINT16                  usClientId
              VOS_UINT8                   ucCid
              TAF_PDP_TYPE_ENUM_UINT8     ucPdpType
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月11日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年07月08日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011070600664, NDIS拨号没有记录CID信息, 导致
                 取消拨号时AT口挂死
  3.日    期   : 2011年12月31日
    作    者   : c00173809
    修改内容   : PS融合项目，NDIS拨号参数修改
*****************************************************************************/
VOS_VOID AT_NdisPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
)
{
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;

    PS_MEM_SET(&stDialParaInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* 设置QOS参数 */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_NDIS_GET_USR_CID(), ucCid))
    {
        return;
    }

    AT_GetPsDialParamFromAtDialParam(&stDialParaInfo,&gstAtNdisAddParam);
    stDialParaInfo.ucCid        = ucCid;
    stDialParaInfo.enPdpType    = ucPdpType;

    /* 发起PDP激活 */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT, usClientId, 0, &stDialParaInfo))
    {
        if (TAF_PDP_IPV4 == stDialParaInfo.enPdpType)
        {
            g_stAtNdisDhcpPara.ucIpv4Cid = ucCid;
        }
        else
        {
            g_stAtNdisDhcpPara.ucIpv6Cid = ucCid;
        }

        g_enAtNdisActPdpType = ucPdpType;

        AT_NdisSetState(ucPdpType, AT_PDP_STATE_ACTING);
    }

    return;
}


/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpActEvtRejProc
 功能描述  : pdp激活失败，NDIS处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2011年07月05日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011070402532, NDIS拨号IPv4类型失败(被网侧拒绝
                 等场景), 再次发起IPv6或IPv4v6类型拨号, 实际发起的都是IPv4类
                 型的拨号

  3.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: V3R2/V7R1不支持IPv6特性, 实现方案待定

  4.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改

  5.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理

  6.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: 通知PDP激活失败时上报原因值

  7.日    期   : 2013年5月08日
    作    者   : Y00213812
    修改内容   : V9R1 IPv6&TAF/SM Project
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstNdisPdpEntity;
    AT_PDP_STATE_ENUM_U8                enPreIpv4State;

    /* 初始化 */
    pstNdisPdpEntity = AT_NDIS_GetPdpEntInfoAddr();
    enPreIpv4State = pstNdisPdpEntity->enIpv4State;

    /* 如果是IPV4 ONLY、IPV6 ONLY直接上报拨号失败。IPV4V6
       则需要视具体实现分别发起IPv4，IPv6类型的PDP激活 */
    if (TAF_PDP_IPV4V6 == g_enAtFirstNdisActPdpType)
    {
        if (TAF_PDP_IPV4V6 == g_enAtNdisActPdpType)
        {
            /* 这种情况，需要分别发起IPv4、IPv6的PDP激活 */
            if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == pstEvent->enCause)
            {
                /* 将发起拨号的PDPtype状态切换到IDLE */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV4);
            }
            else
            {
                /* 将该PDP切换到IDLE态 */
                AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

                /* 通知PDP激活失败 */
                AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

                /* 清除NDIS拨号参数 */
                PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
            }
        }
        else if ( TAF_PDP_IPV4 == g_enAtNdisActPdpType )
        {
            /* 用户发起IPv4v6类型的PDP激活, 而且被网络拒绝, 原因为28, 协议栈需要
               分别发起IPv4/IPv6类型的PDP激活, 协议栈首先发起IPv4, 再发起IPv6,
               如果IPV4类型的PDP激活再次被网络拒绝, 协议栈还需要尝试IPV6类型的
               PDP激活为了防止PDP激活嵌套, 如果IPv6类型的PDP激活失败, 将不再尝试
               IPv4类型的PDP激活 */
            AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

            /* 通知PDP激活失败 */
            AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

            if ( (AT_PDP_STATE_IDLE == AT_NdisGetState(TAF_PDP_IPV6))
              && (AT_PDP_STATE_ACTING == enPreIpv4State) )
            {
                /* 检查IPv6连接是否已经存在, 如果不存在, 发起IPv6类型的PDP激活 */
                AT_NdisPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV6);
            }
            else
            {
                /* 清除NDIS拨号参数 */
                PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
            }
        }
        else
        {
            /* 如果IPv6类型, 就不需要再尝试IPv4, 因为前面已经发起过IPv4类型的PDP
               激活, 如果再发起IPv4类型的PDP激活的话, 可能会导致PDP激活嵌套 */
             AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

             /* 通知PDP激活失败 */
            AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

             /* 清除NDIS拨号参数 */
             PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
        }
    }
    else
    {
        /* 将该PDP切换到IDLE态 */
        AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_IDLE);

        /* 通知PDP激活失败 */
        AT_NdisStateChangeProc(g_enAtNdisActPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

        /* 清除NDIS拨号参数 */
        PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisIPv4DeactiveCnfProc
 功能描述  : IPV4类型的pdp去激活成功，Ndis处理
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目

  2.日    期   : 2012年6月2日
    作    者   : A00165503
    修改内容   : DTS2012060105018: IPv4v6双栈拨号, 网侧下发PDP去激活(原因值-
                 #39), UE不需要重新发起拨号
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID AT_NdisIPv4DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATE_ENUM_U8                enState;
#endif

    AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);
    AT_NdisDhcpRest();

    /* NDIS用户类型的PDP状态改变后的处理流程 */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV4);

    /* NDIS用户类型的PDP去激活后, 处理去激活SharePdp状态*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果另外一个PDP还处于激活状态，需要将其去激活 */
    enState = AT_NdisGetState(TAF_PDP_IPV6);
    if ( (AT_PDP_STATE_IDLE     != enState)
      && (AT_PDP_STATE_DEACTING != enState) )
    {
        if (AT_SUCCESS == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         pstEvent->stCtrl.usClientId,
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv6Cid))
        {
            AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
    }
#endif
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_NdisIPv6DeactiveCnfProc
 功能描述  : IPV6类型pdp去激活成功，Ndis处理
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目

  2.日    期   : 2012年6月2日
    作    者   : A00165503
    修改内容   : DTS2012060105018: IPv4v6双栈拨号, 网侧下发PDP去激活(原因值-
                 #39), UE不需要重新发起拨号
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID AT_NdisIPv6DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enState;

    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    AT_NdisIpv6DhcpRest();

    /* NDIS用户类型的PDP状态改变后的处理流程 */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV6);

    /* NDIS用户类型的PDP去激活后, 处理去激活SharePdp状态*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV6);

    /*如果另外一个PDP还处于激活状态，需要将其去激活*/
    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if ( (AT_PDP_STATE_IDLE     != enState)
      && (AT_PDP_STATE_DEACTING != enState) )
    {
        if (AT_SUCCESS == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         pstEvent->stCtrl.usClientId,
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv4Cid))
        {
            AT_NdisSetState(TAF_PDP_IPV4,AT_PDP_STATE_DEACTING);
        }
    }
}

/*****************************************************************************
 函 数 名  : AT_NdisIPv4v6DeactiveCnfProc
 功能描述  : IPV4V6类型的pdp去激活成功，Ndis处理
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目

  2.日    期   : 2012年6月2日
    作    者   : A00165503
    修改内容   : DTS2012060105018: IPv4v6双栈拨号, 网侧下发PDP去激活(原因值-
                 #39), UE不需要重新发起拨号
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NdisIPv4v6DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_NdisDhcpRest();

    AT_NdisIpv6DhcpRest();

    /* NDIS用户类型的PDP状态改变后的处理流程 */
    AT_ProcNdisDeRegFCPoint(pstEvent, TAF_PDP_IPV4V6);

    /* NDIS用户类型的PDP去激活后, 处理去激活SharePdp状态*/
    AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4V6);
}
#endif

/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpDeactEvtCnfProc
 功能描述  : pdp去激活成功，Ndis处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年08月02日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011080103770, 网侧DETACH的场景下, AT多上报两条
                 ^NDISSTAT命令指示MP拨号已断开
  3.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: V3R2/V7R1不支持IPv6特性, 实现方案待定
  4.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，NDIS发起拨号的PDP去激活时，需要通知上下行ADS和去注册流控点。
  5.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改
  6.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: PDP Deactive时上报原因值
  7.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* 通知PC去激活 */
    AT_NdisStateChangeProc(pstEvent->enPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

    /* 通知TTF去激活相应的RAB */
    AT_SendNdisRelReq(pstEvent);

    /* 切换NDIS状态至IDLE */
    AT_NdisSetState(pstEvent->enPdpType, AT_PDP_STATE_IDLE);

    if (TAF_PDP_IPV4 == pstEvent->enPdpType)
    {
        AT_NdisIPv4DeactiveCnfProc(pstEvent);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == pstEvent->enPdpType)
    {
        AT_NdisIPv6DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV4V6 == pstEvent->enPdpType)
    {
        AT_NdisIPv4v6DeactiveCnfProc(pstEvent);
    }
#endif
    else
    {
        ;
    }

    /* 清除NDIS拨号参数 */
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    /* 通知网卡去激活 */
    AT_DeActiveUsbNet();

    return;
}

/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpDeactivatedEvtProc
 功能描述  : pdp去激活成功，Ndis处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年08月02日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011080103770, 网侧DETACH的场景下, AT多上报两条
                 ^NDISSTAT命令指示MP拨号已断开
  3.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: V3R2/V7R1不支持IPv6特性, 实现方案待定
  4.日    期   : 2011年12月22日
    作    者   : c00173809
    修改内容   : PS融合项目，IPV6特性
  5.日    期   : 2012年7月28日
    作    者   : A00165503
    修改内容   : DTS2012072806289: ^NDISSTAT连接状态上报处理修改
  6.日    期   : 2012年11月20日
    作    者   : Y00213812
    修改内容   : DTS2012111907501: PDP Deactive时上报原因值
  7.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{

    /* 上报^NDISSTAT指示NDIS状态 */
    AT_NdisStateChangeProc(pstEvent->enPdpType, AT_PDP_STATUS_DEACT, pstEvent->enCause);

    /* 通知TTF去激活相应的RAB */
    AT_SendNdisRelReq(pstEvent);

    /* 切换NDIS状态至IDLE */
    AT_NdisSetState(pstEvent->enPdpType, AT_PDP_STATE_IDLE);

    if (TAF_PDP_IPV4 == pstEvent->enPdpType)
    {
        AT_NdisIPv4DeactiveCnfProc(pstEvent);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == pstEvent->enPdpType)
    {
        AT_NdisIPv6DeactiveCnfProc(pstEvent);
    }
    else if (TAF_PDP_IPV4V6 == pstEvent->enPdpType)
    {
        AT_NdisIPv4v6DeactiveCnfProc(pstEvent);
    }
#endif
    else
    {
        ;
    }

    /* 清除NDIS拨号参数 */
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    /* 通知网卡去激活 */
    AT_DeActiveUsbNet();

    return;
}

/*****************************************************************************
 函 数 名  : AT_EnableNdisFlowCtl
 功能描述  : 使能NDIS流控
 输入参数  : VOS_UINT32                          ulParam1,
             VOS_UINT32                          ulParam2
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_EnableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    /* 通过udi_ioctl函数使能流控 */
    VOS_UINT32  ulEnbflg = NCM_IOCTL_FLOW_CTRL_ENABLE;

    if (0 != mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_FLOW_CTRL_NOTIF, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DisableNdisFlowCtl
 功能描述  : 去使能NDIS流控
 输入参数  : VOS_UINT32                          ulParam1,
             VOS_UINT32                          ulParam2
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_DisableNdisFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    /* 通过udi_ioctl函数去使能流控 */
    VOS_UINT32  ulEnbflg = NCM_IOCTL_FLOW_CTRL_DISABLE;

    if (0 != mdrv_udi_ioctl (g_ulAtUdiNdisHdl, NCM_IOCTL_FLOW_CTRL_NOTIF, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RegNdisFCPoint
 功能描述  : 注册NDIS端口流控点。
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             FC_ID_ENUM_UINT8                    enFcId
             MODEM_ID_ENUM_UINT16                enModemId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:修改注册NDIS流控点的逻辑
  3.日    期   : 2012年12月17日
    作    者   : l60609
    修改内容   : DSDA Phase II
  4.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  5.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_UINT32 AT_RegNdisFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFCPri;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    /* 配置通道与RABID映射关系 */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;

    /* 根据网卡上最高优先级RAB QoS优先级来折算,优先级改变时，需要改变优先级 */
    /*  FC_PRI_3        有最低优先级的承载
        FC_PRI_4        有NONGBR承载
        FC_PRI_5        有GBR承载 */

    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.pClrFunc           = AT_DisableNdisFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableNdisFlowCtl;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.ulParam1           = (VOS_UINT32)pstEvent->stCtrl.usClientId;

    /* 注册流控点,需要分别注册MEM,CPU,CDS和GPRS。 */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg a cpu point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg cds point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegNdisFCPoint: ERROR: reg gprs point Failed.");
        return VOS_ERR;
    }


    /* 设置FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed      = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri     = enFCPri;
    /* 有一张网卡上多个RABID的情况，所以需要将多个RABID记录下来 */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId   = enModemId;

    /* 勾流控消息 */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_NDIS);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DeRegNdisFCPoint
 功能描述  : 去注册NDIS端口流控点。
 输入参数  : VOS_UINT8                           ucRabId
             MODEM_ID_ENUM_UINT16                enModemId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:修改注销NDIS流控点的逻辑
  3.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
*****************************************************************************/
VOS_UINT32 AT_DeRegNdisFCPoint(
    VOS_UINT8                           ucRabId,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;

    /* 在调用FC_DeRegPoint前,先调用FC_ChannelMapDelete */
    FC_ChannelMapDelete(ucRabId, enModemId);

    /* 目前NDIS只支持一个网卡 */
    enFcId = FC_ID_NIC_1;

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegNdisFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* 清除FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enFcPri     = FC_PRI_BUTT;
    /* 有一张网卡上多个RABID的情况，所以需要将对应的RABID掩码清除掉 */
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].ulRabIdMask &= ~((VOS_UINT32)1 << ucRabId);
    g_stFcIdMaptoFcPri[FC_ID_NIC_1].enModemId   = MODEM_ID_BUTT;

    /* 勾流控消息 */
    AT_MNTN_TraceDeregFcPoint(AT_CLIENT_TAB_NDIS_INDEX, AT_FC_POINT_TYPE_NDIS);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_UsbEthHostAccumTuneCB
 功能描述  : 向FC(流控)模块注册的动态调整HOST端NCM/ECM组包参数的回调函数
 输入参数  : pstFcDrvAssemPara - NCM/ECM组包参数, 包含如下参数:
                                 1. HOST OUT组包时间
 输出参数  : 无
 返 回 值  : VOS_OK            - 调整成功
             VOS_ERR           - 调整失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_UsbEthHostAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT32                          ulHostOutTimeout;

    /* 获取上层对接应用配置: MP/WEBUI/ANDROID */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    ulHostOutTimeout   = pstFcDrvAssemPara->ucHostOutTimeout;


    if (SYSTEM_APP_MP == *pucSystemAppConfig)
    {
        /* 调整HOST端组包时长 */
        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_ACCUMULATION_TIME,
                                    (VOS_VOID*)&ulHostOutTimeout))
        {
            AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Set host out timeout failed.");

            return VOS_ERR;
        }

    }
    else if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* Modified by zwx247453 for pc工程转3650, 2015-8-24, begin */
        /*lint -e747*/
        if (VOS_OK != USB_ETH_DrvSetHostAssembleParam((unsigned long)ulHostOutTimeout) )
        {
            AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Set Assemble para failed.");

            return VOS_ERR;
        }
        /*lint +e747*/
        /* Modified by zwx247453 for pc工程转3650, 2015-8-24, end */
    }
    else if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        AT_NORM_LOG("AT_UsbEthHostAccumTuneCB: APP config is ANDROID, do nothing.");
    }
    else
    {
        AT_ERR_LOG("AT_UsbEthHostAccumTuneCB: Wrong APP config.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_UsbEthDeviceAccumTuneCB
 功能描述  : 向FC(流控)模块注册的动态调整DEVICE端NCM/ECM组包参数的回调函数
 输入参数  : pstFcDrvAssemPara - NCM/ECM组包参数, 包含如下参数:
                                 1. TX组包个数
                                 2. TX组包时间
                                 3. RX组包个数
                                 4. RX组包时间
 输出参数  : 无
 返 回 值  : VOS_OK            - 调整成功
             VOS_ERR           - 调整失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_UsbEthDeviceAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
)
{
    VOS_UINT8                          *pucSystemAppConfig;
    VOS_UINT32                          ulEthTxMinNum;
    VOS_UINT32                          ulEthTxTimeout;
    VOS_UINT32                          ulEthRxMinNum;
    VOS_UINT32                          ulEthRxTimeout;

    /* 获取上层对接应用配置: MP/WEBUI/ANDROID */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    ulEthTxMinNum      = pstFcDrvAssemPara->ucEthTxMinNum;
    ulEthTxTimeout     = pstFcDrvAssemPara->ucEthTxTimeout;
    ulEthRxMinNum      = pstFcDrvAssemPara->ucEthRxMinNum;
    ulEthRxTimeout     = pstFcDrvAssemPara->ucEthRxTimeout;

    if (SYSTEM_APP_MP == *pucSystemAppConfig)
    {
        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_TX_MIN_NUM,
                                    (VOS_VOID*)&ulEthTxMinNum))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH tx min num failed.");

            return VOS_ERR;
        }

        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_TX_TIMEOUT,
                                    (VOS_VOID*)&ulEthTxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH tx timeout failed.");

            return VOS_ERR;
        }

        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_RX_MIN_NUM,
                                    (VOS_VOID*)&ulEthRxMinNum))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH rx min num failed.");

            return VOS_ERR;
        }

        if (VOS_OK != mdrv_udi_ioctl(g_ulAtUdiNdisHdl,
                                    NCM_IOCTL_SET_RX_TIMEOUT,
                                    (VOS_VOID*)&ulEthRxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set ETH rx timeout failed.");

            return VOS_ERR;
        }
    }
    else if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* Modified by zwx247453 for pc工程转3650, 2015-8-24, begin */
        /*lint -e747*/
        if (VOS_OK != USB_ETH_DrvSetDeviceAssembleParam((unsigned long)ulEthTxMinNum,
                                                        (unsigned long)ulEthTxTimeout,
                                                        (unsigned long)ulEthRxMinNum,
                                                        (unsigned long)ulEthRxTimeout))
        {
            AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Set Assemble para failed.");

            return VOS_ERR;
        }
        /*lint +e747*/
        /* Modified by zwx247453 for pc工程转3650, 2015-8-24, end */
    }
    else if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        AT_NORM_LOG("AT_UsbEthDeviceAccumTuneCB: APP config is ANDROID, do nothing.");
    }
    else
    {
        AT_ERR_LOG("AT_UsbEthDeviceAccumTuneCB: Wrong APP config.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_NDIS_ParseUsrInfo
 功能描述  : 获取NIDS用户信息
 输入参数  : ucIndex     - 端口号(ClientId)索引
 输出参数  : pstUserInfo - 用户信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月14日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NDIS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUsrIndex;

    if (VOS_TRUE == AT_CheckNdisUser(ucIndex))
    {
        enUsrIndex = ucIndex;
    }
    else
    {
        enUsrIndex = AT_CLIENT_TAB_NDIS_INDEX;
    }

    pstUsrInfo->enPortIndex = ucIndex;
    pstUsrInfo->enUserIndex = enUsrIndex;
    pstUsrInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUsrIndex].UserType;
    pstUsrInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}

/*****************************************************************************
 函 数 名  : AT_NDIS_ConnStatusChgProc
 功能描述  : NDIS网卡连接状态变化
 输入参数  : enStatus --- 连接状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NDIS_ConnStatusChgProc(NCM_IOCTL_CONNECT_STUS_E enStatus)
{
    if (NCM_IOCTL_STUS_BREAK == enStatus)
    {
        /* 如果所有的PDP都处于IDLE，返回OK; 如果有一个处于DEACTING也返回OK */
        if (VOS_TRUE == AT_NdisCheckPdpIdleState())
        {
            return;
        }

        if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4v6State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4v6State) )
        {
            if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_NDIS_GET_CLIENT_ID(),
                                         0,
                                         g_stAtNdisDhcpPara.ucIpv4v6Cid) )
            {
                AT_NdisSetState(TAF_PDP_IPV4V6, AT_PDP_STATE_DEACTING);
            }
        }
        else
        {
            if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4State)
              || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4State) )
            {
                if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_NDIS_GET_CLIENT_ID(),
                                             0,
                                             g_stAtNdisDhcpPara.ucIpv4Cid))
                {
                    AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
                }
            }

            if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv6State)
              || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv6State) )
            {
                if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_NDIS_GET_CLIENT_ID(),
                                             0,
                                             g_stAtNdisDhcpPara.ucIpv6Cid))
                {
                    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
                }
            }
        }
    }

    return;
}

/***************************************************************************
               以下代码实现APP相关功能
*****************************************************************************/

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_CalcIpv6LanAddrFromIpv6Prefix
 功能描述  : 根据IPV6地址前缀产生IPV6全局地址
 输入参数  : pucPrefix
             ulPrefixByteLen
             pucIpv6LanAddr
             ulIpv6LanAddrLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : 新生成函数/PS融合项目

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
*****************************************************************************/
VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr,
    VOS_UINT32                          ulIpv6LanAddrLen
)
{
    VOS_UINT16                         *pausAddr;
    VOS_UINT8                           aucLanAddr[AT_MAC_LEN] = { 0x58, 0x2C, 0x80, 0x13, 0x92, 0x08 };

    if ( (ulIpv6LanAddrLen < TAF_IPV6_ADDR_LEN )
      || (ulPrefixByteLen > AT_IPV6_ADDR_PREFIX_BYTE_LEN) )
    {
        return VOS_ERR;
    }

    pausAddr = (VOS_UINT16 *)pucIpv6LanAddr;

    /* 拷贝IPv6地址前缀 */
    PS_MEM_CPY(pucIpv6LanAddr, pucPrefix, ulPrefixByteLen);

    /*--------------------------------------------------------------
       MAC地址生成接口ID：将16位数0xFFFE插入MAC地址中间
       MAC地址前24位 + 0xFFFE + MAC地址后24位
       再将U/L位(全球/本地地址,MAC地址最高字节的第一位)取反
    --------------------------------------------------------------*/
    pausAddr[4] = ((VOS_UINT16 *)aucLanAddr)[0] ^ VOS_HTONS(0x0200);
    pausAddr[5] = VOS_HTONS(0x00ff) | ((VOS_UINT16 *)aucLanAddr)[1];
    pausAddr[6] = VOS_HTONS(0xfe00) | (((VOS_UINT16 *)aucLanAddr)[1] & VOS_HTONS(0x00ff));
    pausAddr[7] = ((VOS_UINT16 *)aucLanAddr)[2];

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_AppRcvIpv6LanAddr
 功能描述  : NAS向HOST注册的回调函数，当HOST获取IPv6全局地址后，向NAS上报-
             IPv6全局地址，以及全局地址长度。
 输入参数  : aucLanAddr       - Ipv6全局地址
             ulLanAddrByteLen - 地址长度, 单位是BYTE
             ulPrefixBitLen   - 前缀长度, 单位是BIT
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  3.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LanAddr(
    VOS_UINT8                           aucLanAddr[],
    VOS_UINT32                          ulLanAddrByteLen,
    VOS_UINT32                          ulPrefixBitLen
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];

    /* 将全局地址转换为压缩格式 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucLanAddr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    /* 上报LAN全局地址 */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APLANADDR: \"%s\",%d%s",
                                      gaucAtCrLf,
                                      aucIpv6AddrStr,
                                      ulPrefixBitLen,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppRcvIpV6Prefix
 功能描述  : NAS向HOST注册的回调函数，当HOST收到GGSN下发的RA之后，
             保存IPV6前缀到本地并向NAS上报IPv6地址前缀，以及地址前缀长度。
 输入参数  : VOS_UINT8  aucPrefix   Ipv6前缀
             VOS_UINT32 ulPrefixLen 前缀长度，单位是BIT
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  3.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6Prefix(
    VOS_UINT8                           aucPrefix[],
    VOS_UINT32                          ulPrefixBitLen
)
{
    VOS_UINT8                           aucPrefixStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucTokensNum;

    /* 将前缀转换成压缩格式 */
    ucTokensNum = TAF_IPV6_STR_RFC2373_TOKENS;
    AT_ConvertIpv6AddrToCompressedStr(aucPrefixStr, aucPrefix, ucTokensNum);

    /* 上报^APPREFIX: <PrefixAddr> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APPREFIX: \"%s/%d\"%s",
                                      gaucAtCrLf,
                                      aucPrefixStr,
                                      ulPrefixBitLen,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);
    return;
}

/*****************************************************************************
 函 数 名  : AT_AppRcvPrefixIpV6PreferredLifetime
 功能描述  : 主动上报前缀优先使用生存期，单位:秒
 输入参数  : ulPrefixPreferredLifetime - 前缀优先使用生存期
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2012年5月11日
    作    者   : l60609
    修改内容   : DTS2012051002464：lifetime需要用%u输出

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
  4.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6PreferredLifetime(
    VOS_UINT32                          ulPrefixPreferredLifetime
)
{
    VOS_UINT16                          usLength;

    /* 上报^APPREFERREDLIFETIME: <PreferredLifetime> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APPREFERREDLIFETIME: %u%s",
                                      gaucAtCrLf,
                                      ulPrefixPreferredLifetime,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvPrefixIpV6ValidLifetime
 功能描述  : 主动上报前缀有效生存期，单位:秒
 输入参数  : ulValidLifetime - 前缀有效生存期
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2012年5月11日
    作    者   : l60609
    修改内容   : DTS2012051002464：lifetime需要用%u输出

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  4.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6ValidLifetime(
    VOS_UINT32                          ulValidLifetime
)
{
    VOS_UINT16                          usLength;

    /* 上报^APVALIDLIFETIME: <ValidLifetime> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APVALIDLIFETIME: %u%s",
                                      gaucAtCrLf,
                                      ulValidLifetime,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvIpV6LinkMtu
 功能描述  : 接收到HOST模块的MTU数据的处理函数: 保存MTU数据到本地，
             同时主动上报给APP，接收到RA数据后，HOST模块调用本函数
             通知NAS新的MTU数据
 输入参数  : ulMTU - MTU Size
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  3.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LinkMtu(
    VOS_UINT32                          ulMtu
)
{
    VOS_UINT16                          usLength;

    /* 上报^IPV6MTU: <MTU> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APIPV6MTU: %d%s",
                                      gaucAtCrLf,
                                      ulMtu,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);
    return;
}

/*****************************************************************************
 函 数 名  : AT_RcvEnableIpV6Prefix
 功能描述  : 通知应用启用新的IPV6前缀
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化

*****************************************************************************/
VOS_VOID AT_AppRcvEnableIpv6Prefix(VOS_VOID)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucStatus;

    ucStatus                            = 1;

    /* 上报^APIPV6ENABLE: <status> */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      "%s^APIPV6ENABLE: %d%s",
                                      gaucAtCrLf,
                                      ucStatus,
                                      gaucAtCrLf);
    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppProcIpv6RaInfo
 功能描述  : 收到Router Advertisement IP报文, 进行处理和分发
 输入参数  : pstRaInfoNotifyInd         - RA报文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};

    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();

    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_AppProcIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* 获取到IPv6地址前缀后, 上报已连接结果^DCONN */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        /* 通知APP模块IPv6拨号成功 */
        AT_AppSndCallConnectedResult(pstRaInfoNotifyInd->ucCid, TAF_PDP_IPV6);
    }

    /* 记录IPv6前缀 */
    pstAppRaInfoAddr->bitOpPrefixAddr        = VOS_TRUE;
    pstAppRaInfoAddr->ulPrefixBitLen         = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
    PS_MEM_CPY(pstAppRaInfoAddr->aucPrefixAddr,
               pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
               TAF_IPV6_ADDR_LEN);

    /* 记录Preferred Lifetime */
    pstAppRaInfoAddr->bitOpPreferredLifetime = VOS_TRUE;
    pstAppRaInfoAddr->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* 记录Valid Lifetime */
    pstAppRaInfoAddr->bitOpValidLifetime     = VOS_TRUE;
    pstAppRaInfoAddr->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* 记录IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstAppRaInfoAddr->bitOpMtuSize       = VOS_TRUE;
        pstAppRaInfoAddr->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    /* 计算IPv6全局地址 */
    AT_CalcIpv6LanAddrFromIpv6Prefix(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                     pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                     aucIpv6LanAddr,
                                     TAF_IPV6_ADDR_LEN);

    /* 记录IPv6全局地址 */
    pstAppRaInfoAddr->bitOpLanAddr           = VOS_TRUE;
    PS_MEM_CPY(pstAppRaInfoAddr->aucLanAddr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

    /* 更新DHCPV6信息中的IPv6全局地址 */
    PS_MEM_CPY(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

    /* 主动上报IPV6地址前缀 */
    AT_AppRcvIpv6Prefix(pstAppRaInfoAddr->aucPrefixAddr, pstAppRaInfoAddr->ulPrefixBitLen);

    /* 主动上报前缀优先使用生存期 */
    AT_AppRcvPrefixIpv6PreferredLifetime(pstAppRaInfoAddr->ulPreferredLifetime);

    /* 主动上报前缀有效生存期 */
    AT_AppRcvPrefixIpv6ValidLifetime(pstAppRaInfoAddr->ulValidLifetime);

    /* 主动上报IPV6全局地址 */
    AT_AppRcvIpv6LanAddr(pstAppRaInfoAddr->aucLanAddr, TAF_IPV6_ADDR_LEN, pstAppRaInfoAddr->ulPrefixBitLen);

    /* 通知APP启用新的IPV6前缀 */
    AT_AppRcvEnableIpv6Prefix();

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppCtrlConnIpv6IndProc
 功能描述  : 处理IPv6地址
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppCtrlConnIpv6IndProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    pstAppPdpEntity->stIpv6Dhcp.ucRabId  = pstEvent->ucRabId;

    /* 处理IPv6的IP地址，形式为网络序 */
    if (TAF_PDP_IPV6 == (pstEvent->stPdpAddr.enPdpType & TAF_PDP_IPV6))
    {
        PS_MEM_CPY(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                   pstEvent->stPdpAddr.aucIpv6Addr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* 处理IPV6的主副DNS地址，形式为网络序 */
    AT_SaveIPv6Dns(pstEvent, pstAppPdpEntity);

    /* 处理IPV6的主副PCSCF地址，形式为网络序 */
    AT_SaveIPv6Pcscf(pstEvent, pstAppPdpEntity);

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppDhcpv6Reset
 功能描述  : 清空IPv6地址参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppDhcpv6Reset(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pucAppRaInfoAddr;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pucAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

    PS_MEM_SET(&pstAppPdpEntity->stIpv6Dhcp,
               0x00,
               sizeof(AT_IPV6_DHCP_PARAM_STRU));

    PS_MEM_SET(pucAppRaInfoAddr,
               0x00,
               sizeof(AT_IPV6_RA_INFO_STRU));

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppDhcpReset
 功能描述  : 清空APP的DHCP参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppDhcpReset(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    PS_MEM_SET(&pstAppPdpEntity->stIpv4Dhcp,
               0x00,
               sizeof(AT_IPV4_DHCP_PARAM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppPdpAddrProc
 功能描述  : 处理IPv4地址参数
 输入参数  : pstAppPdpEntity - PDP实体
             pstDhcpConfig   - DCHP信息
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月22日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年08月18日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011081400480, ^DNSP和^DNSS需要支持HiLink拨号
  3.日    期   : 2012年01月02日
    作    者   : C00173809
    修改内容   : PS融合项目，保存IPV4主副PCSCF地址
  4.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2015031000157, 新增第三个p-cscf地址
*****************************************************************************/
VOS_VOID AT_AppPdpAddrProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;
    VOS_UINT32                          ulIpAddr;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();
    ulIpAddr                            = 0;

    pstAppPdpEntity->stIpv4Dhcp.ucRabId                 = pstEvent->ucRabId;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4Addr              = pstDhcpConfig->ulIPAddr;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4GateWay           = pstDhcpConfig->ulGateWay;
    pstAppPdpEntity->stIpv4Dhcp.ulIpv4NetMask           = pstDhcpConfig->ulSubNetMask;

    /* 如果用户设置了主DNS，就使用用户设置的DNS，网络返回的DNS不使用 */
    if (VOS_TRUE == pstAppDialPara->ulPrimIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(pstAppDialPara->aucPrimIPv4DNSAddr,
                                        (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns     = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulPrimDNS)
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns = VOS_TRUE;
            pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS   = pstDhcpConfig->ulPrimDNS;
        }
        else
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* 如果用户设置了副DNS，就使用用户设置的DNS，网络返回的DNS不使用 */
    if (VOS_TRUE == pstAppDialPara->ulSndIPv4DNSValidFlag)
    {
        if (VOS_ERR == AT_LenStr2IpAddr(pstAppDialPara->aucSndIPv4DNSAddr,
                                        (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns     = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS        = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulSndDNS)
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns = VOS_TRUE;
            pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS    = pstDhcpConfig->ulSndDNS;
        }
        else
        {
            pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriWINNS       = VOS_FALSE;
    pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecWINNS       = VOS_FALSE;

    /* 获取主PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpPrimPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4PriPCSCF = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimPCSCF   = AT_GetLanAddr32(pstEvent->stPcscf.aucPrimPcscfAddr);
    }

    /* 获取副PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpSecPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4Secpcscf = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecPCSCF    = AT_GetLanAddr32(pstEvent->stPcscf.aucSecPcscfAddr);
    }

    /* 获取第三PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpThiPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4Thipcscf = VOS_TRUE;
        pstAppPdpEntity->stIpv4Dhcp.ulIpv4ThiPCSCF    = AT_GetLanAddr32(pstEvent->stPcscf.aucThiPcscfAddr);
    }

    return;
}

/* 后续可能会使用 */
#if 0
/*****************************************************************************
 函 数 名  : AT_AppPsRecoverState
 功能描述  : 清除PDP相关信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年12月26日
    作    者   : C00173809
    修改内容   : PS融合项目，通知RNIC和ADS去激活。
  3.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:通知ADS去激活的函数调用中，新增一个pQos参数
*****************************************************************************/
VOS_VOID AT_AppPsRecoverState(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if (AT_PDP_STATE_ACTED == AT_AppGetPdpState(TAF_PDP_IPV4))
    {
         /* 通知上下行ADS PDP 去激活 */
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_DL,VOS_NULL_PTR);
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_UL,VOS_NULL_PTR);

         /* 通知RNIC PDP去激活成功 */
         AT_SendRnicPdpDeactInd(pstAppPdpEntity->ucIpv4Cid, RNIC_RMNET_ID_0);
    }

    /* 清除IPV4/V6的DHCP信息 */
    AT_AppDhcpReset();

    /* 将所有的PDP_TYPE状态都置为IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_PDP_STATE_ACTED == AT_AppGetPdpState(TAF_PDP_IPV6))
    {
         /* 通知上下行ADS PDP 去激活 */
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_DL, VOS_NULL_PTR);
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_UL, VOS_NULL_PTR);

         /* 通知RNIC PDP去激活成功 */
         AT_SendRnicPdpDeactInd(pstAppPdpEntity->ucIpv6Cid, RNIC_RMNET_ID_0);
    }

    if (AT_PDP_STATE_ACTED == AT_AppGetPdpState(TAF_PDP_IPV4V6))
    {
        /* 通知上下行ADS PDP 去激活 */
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4v6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_DL, VOS_NULL_PTR);
         AT_SendAdsPdpStatusInd(MODEM_ID_0, pstAppPdpEntity->ucIpv4v6Cid,ADS_PDP_STATUS_DEACT,ACPU_PID_ADS_UL, VOS_NULL_PTR);

         /* 通知RNIC PDP去激活成功 */
         AT_SendRnicPdpDeactInd(pstAppPdpEntity->ucIpv4v6Cid, RNIC_RMNET_ID_0);
    }

    AT_AppDhcpv6Reset();
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);
#endif

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppCheckPdpIdleState
 功能描述  : 检查是否有处于IDLE或DEACTIVATING状态的PDP
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在满足条件的PDP
             VOS_FALSE - 不存在满足条件的PDP
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_AppCheckPdpIdleState(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* 如果所有的PDP都处于IDLE, 如果有一个处于DEACTIVATING也返回TRUE */
    if ( (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4State)
      || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv6State)
      || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4v6State)
      || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : AT_AppCheckIpv4PdpState
 功能描述  : 检查是否有满足IPv4状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (enPdpState == pstAppPdpEntity->enIpv4State)
      || (enPdpState == pstAppPdpEntity->enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppCheckIpv6PdpState
 功能描述  : 检查是否有满足IPv6状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (enPdpState == pstAppPdpEntity->enIpv6State)
      || (enPdpState == pstAppPdpEntity->enIpv4v6State) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppGetPdpStateByCid
 功能描述  : 根据CID获取相应的PDP状态
 输入参数  : ucCid
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpStateByCid(
    VOS_UINT8                           ucCid
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if (ucCid == pstAppPdpEntity->ucIpv4Cid)
    {
        return pstAppPdpEntity->enIpv4State;
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (ucCid == pstAppPdpEntity->ucIpv6Cid)
    {
        return pstAppPdpEntity->enIpv6State;
    }
    else if (ucCid == pstAppPdpEntity->ucIpv4v6Cid)
    {
        return pstAppPdpEntity->enIpv4v6State;
    }
#endif
    else
    {
        return AT_PDP_STATE_IDLE;
    }
}

/*****************************************************************************
 函 数 名  : AT_AppGetPdpState
 功能描述  : 获取APP的PDP状态，激活态/非激活态
 输入参数  : ucPdpType - PDP类型
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpState(
    VOS_UINT8                           ucPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (ucPdpType)
    {
        case TAF_PDP_IPV4:
            enPdpState = pstAppPdpEntity->enIpv4State;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            enPdpState = pstAppPdpEntity->enIpv6State;
            break;

        case TAF_PDP_IPV4V6:
            enPdpState = pstAppPdpEntity->enIpv4v6State;
            break;
#endif

        default:
            AT_ERR_LOG("AT_AppGetPdpState:ERROR: PDP type is invalid!");
            enPdpState = AT_PDP_STATE_IDLE;
            break;
    }

    return enPdpState;
}

/*****************************************************************************
 函 数 名  : AT_AppSetPdpState
 功能描述  : 设置APP的PDP状态
 输入参数  : ucPdpType  - PDP类型
             enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppSetPdpState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (ucPdpType)
    {
        case TAF_PDP_IPV4:
            pstAppPdpEntity->enIpv4State    = enPdpState;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            pstAppPdpEntity->enIpv6State    = enPdpState;
            break;

        case TAF_PDP_IPV4V6:
            pstAppPdpEntity->enIpv4v6State  = enPdpState;
            break;
#endif

        default:
            AT_ERR_LOG("AT_AppSetPdpState:ERROR: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppSndCallConnectedResult
 功能描述  : 上报连接结果^DCONN, 通知APP拨号成功
 输入参数  : ucCid                      - CID
             enPdpType                  - 拨号类型(IPv4/IPv6)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppSndCallConnectedResult(
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DCONN:%d,\"IPV4\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              gaucAtCrLf);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DCONN:%d,\"IPV6\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_AppSndConnectResult: PDP type is invalid in ^DCONN.");
            return;
    }

    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppSndCallEndedResult
 功能描述  : 上报连接结果^DCONN, 通知APP拨号成功
 输入参数  : ucCid     - CID
             enCause   - 错误码
             enPdpType - 拨号类型(IPv4/IPv6)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理

  3.日    期   : 2013年1月14日
    作    者   : A00165503
    修改内容   : DTS2012042104301: PCUI端口发起NDIS/APP拨号流程优化
*****************************************************************************/
VOS_VOID AT_AppSndCallEndedResult(
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DEND:%d,%d,\"IPV4\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              enCause,
                                              gaucAtCrLf);

            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:

            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s^DEND:%d,%d,\"IPV6\"%s",
                                              gaucAtCrLf,
                                              ucCid,
                                              enCause,
                                              gaucAtCrLf);

            break;
#endif

        default:
            AT_ERR_LOG("AT_AppSndCallEndedResult: PDP type is invalid in ^DEND.");
            return;
    }

    At_SendResultData(AT_APP_GET_USR_PORT_INDEX(), pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_SendRnicIpv4ActInd
 功能描述  : APP拨号时通知虚拟网卡IPV4激活
 输入参数  : VOS_UINT8 ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年10月18日
    作    者   : f00179208
    修改内容   : PS 融合项目
  3.日    期   : 2012年12月18日
    作    者   : l60609
    修改内容   : DSDA Phase II

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    /* 申请AT_RNIC_IPV4_PDP_ACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv4ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* 填写消息体 */
    pstMsg->ucRabId         = g_stAtAppPdpEntity.stIpv4Dhcp.ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;
    pstMsg->ulIpv4Addr      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr;
    pstMsg->ulNetMask       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask;
    pstMsg->ulGateWay       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay;
    pstMsg->OP_PriDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriDns;
    pstMsg->OP_SecDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecDns;
    pstMsg->OP_PriWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriWINNS;
    pstMsg->OP_SecWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecWINNS;
    pstMsg->ulPrimDNS       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimDNS;
    pstMsg->ulSecDNS        = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecDNS;
    pstMsg->ulPrimWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimWINNS;
    pstMsg->ulSecWINNS      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecWINNS;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv4ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
函 数 名  : AT_SendRnicIpv6ActInd
功能描述  : APP拨号时通知虚拟网卡IPV6激活
输入参数  : VOS_UINT8 ucRmNetId
输出参数  : 无
返 回 值  : 成功
            失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年10月18日
   作    者   : S62952
   修改内容   : 新生成函数
 2.日    期   : 2011年10月18日
   作    者   : f00179208
   修改内容   : PS 融合项目
 3.日    期   : 2012年12月27日
   作    者   : l00227485
   修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv6ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstMsg;

    /* 申请AT_NDIS_IPV6_PDP_ACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;

    /* 填写消息体 */
    pstMsg->ucRabId         = g_stAtAppPdpEntity.stIpv6Dhcp.ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;
    pstMsg->OP_PriDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns;
    pstMsg->OP_SecDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6SecDns;

    PS_MEM_CPY(pstMsg->aucIpv6Addr,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    PS_MEM_CPY(pstMsg->aucPrimDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6PrimDNS,
               AT_MAX_IPV6_DNS_LEN);

    PS_MEM_CPY(pstMsg->aucSecDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6SecDNS,
               AT_MAX_IPV6_DNS_LEN);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : AT_SendRnicIpv4v6ActInd
功能描述  : APP拨号时通知虚拟网卡IPV4V6激活
输入参数  : VOS_UINT8 ucRmNetId
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年10月18日
   作    者   : S62952
   修改内容   : 新生成函数
 2.日    期   : 2011年12月25日
   作    者   : c00173809
   修改内容   : PS 融合项目，IPV6特性
 3.日    期   : 2012年12月27日
   作    者   : l00227485
   修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4v6ActInd(VOS_UINT8 ucRmNetId)
{
    AT_RNIC_IPV4V6_PDP_ACT_IND_STRU      *pstMsg;

    /* 申请AT_NDIS_IPV6_PDP_ACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_IPV4V6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4V6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4V6_PDP_ACT_IND;

    /* 填写消息体 */
    pstMsg->ucRabId             = g_stAtAppPdpEntity.stIpv4Dhcp.ucRabId;
    pstMsg->ucRmNetId           = ucRmNetId;
    pstMsg->ulIpv4Addr          = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr;
    pstMsg->ulIPv4NetMask       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask;
    pstMsg->ulIPv4GateWay       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay;
    pstMsg->OP_IPv4PriDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriDns;
    pstMsg->OP_IPv4SecDns       = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecDns;
    pstMsg->OP_IPv4PriWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4PriWINNS;
    pstMsg->OP_IPv4SecWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.bitOpIpv4SecWINNS;
    pstMsg->ulIPv4PrimDNS       = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimDNS;
    pstMsg->ulIPv4SecDNS        = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecDNS;
    pstMsg->ulIPv4PrimWINNS     = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4PrimWINNS;
    pstMsg->ulIPv4SecWINNS      = g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4SecWINNS;

    pstMsg->OP_IPv6PriDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6PriDns;
    pstMsg->OP_IPv6SecDns       = g_stAtAppPdpEntity.stIpv6Dhcp.bitOpIpv6SecDns;

    PS_MEM_CPY(pstMsg->aucIpv6Addr,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    PS_MEM_CPY(pstMsg->aucIpv6PrimDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6PrimDNS,
               AT_MAX_IPV6_DNS_LEN);

    PS_MEM_CPY(pstMsg->aucIpv6SecDNS,
               g_stAtAppPdpEntity.stIpv6Dhcp.aucIpv6SecDNS,
               AT_MAX_IPV6_DNS_LEN);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicIpv6ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppSndRnicPdpActInd
 功能描述  : APP拨号时根据PDP类型给RNIC发送激活消息
 输入参数  : enPdpType      PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月27日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppSndRnicPdpActInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT32                          ulResult;

    /* 通知RNIC PDP激活成功 */
    if ( TAF_PDP_IPV4== enPdpType )
    {
        AT_SendRnicIpv4ActInd(RNIC_RMNET_ID_0);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    if ( TAF_PDP_IPV6== enPdpType )
    {
        AT_SendRnicIpv6ActInd(RNIC_RMNET_ID_0);
    }

    if ( TAF_PDP_IPV4V6== enPdpType )
    {
        ulResult = AT_SendRnicIpv4v6ActInd(RNIC_RMNET_ID_0);
        if (VOS_OK != ulResult)
        {
            AT_ERR_LOG("AT_AppSndRnicPdpActInd: ERROR: Send Rnic Ipv4 Act Ind To Rnic Failed.");
        }
    }
#endif
    return;
}

/*****************************************************************************
函 数 名  : AT_SendRnicPdpDeactInd
功能描述  : APP端口拨号时通知虚拟网卡
输入参数  : VOS_UINT8                           ucRabId
            VOS_UINT8                           ucRmNetId
输出参数  : 无
返 回 值  : 成功
            失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2011年10月18日
   作    者   : S62952
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_SendRnicPdpDeactInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstMsg;

    /* 申请AT_NDIS_PDP_DEACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_PDP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;

    /* 填写消息体 */
    pstMsg->ucRabId         = ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_AppPdpActOrig
 功能描述  : 发起PDP激活
 输入参数  : usClientId - 客户端ID
             ucCid      - CID
             ucPdpType  - PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月13日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年10月20日
    作    者   : A00165503
    修改内容   : AT Project: 修改PS域接口
  3.日    期   : 2011年12月31日
    作    者   : C00173809
    修改内容   : ps融合项目，

*****************************************************************************/
VOS_VOID AT_AppPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;

    AT_GetPdpContextFromAtDialParam(&stPdpPrimContextExt,AT_APP_GetDailParaAddr());
    stPdpPrimContextExt.enPdpType   = enPdpType;
    stPdpPrimContextExt.ucCid       = ucCid;

    /* 设置QOS参数 */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_APP_GET_USR_CID(), ucCid))
    {
        return;
    }

    AT_GetPsDialParamFromAtDialParam(&stDialParaInfo,AT_APP_GetDailParaAddr());
    stDialParaInfo.enPdpType    = enPdpType;
    stDialParaInfo.ucCid        = ucCid;

    /* 发起PDP激活 */
    if ( VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT, usClientId, 0, &stDialParaInfo) )
    {
        if (TAF_PDP_IPV4 == enPdpType)
        {
            g_stAtAppPdpEntity.ucIpv4Cid = ucCid;
        }
        else
        {
            g_stAtAppPdpEntity.ucIpv6Cid = ucCid;
        }

        AT_APP_SetActPdpType(enPdpType);

        AT_AppSetPdpState(enPdpType, AT_PDP_STATE_ACTING);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ProcAppRegFCPoint
 功能描述  : APP用户类型PDP状态改变为激活时的处理流控点上报
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目修改

*****************************************************************************/
VOS_VOID  AT_ProcAppRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulResult;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    /* APP拨号默认使用NDIS网卡1的流控点 */
    enDefaultFcId = FC_ID_NIC_1;

    ulResult = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulResult)
    {
        /* 如果FC ID未注册，那么注册该流控点。目前只支持一个网卡.*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* 注册APP拨号使用的流控点(默认使用网卡1) */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, RNIC_RMNET_ID_0);
        }
        else
        {
            /* APP拨号只使用最低的流控QOS优先级FC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_ProcAppRegFCPoint: No need to change the default QOS priority.");
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_SaveIPv6Pcscf
 功能描述  : 保存IPV6的Pcscf到PDP实体中
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
  3.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2015031000157, 新增第三个p-cscf地址
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Pcscf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
)
{
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriPCSCF = VOS_FALSE;
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecPCSCF = VOS_FALSE;
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6ThiPCSCF = VOS_FALSE;

    /* 处理IPV6的主PCSCF地址 */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* 处理IPV6的副PCSCF地址 */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpSecPcscfAddr)
    {
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stIpv6Dhcp.aucSecPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* 处理IPV6的副PCSCF地址 */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpThiPcscfAddr)
    {
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6ThiPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstPdpEntity->stIpv6Dhcp.aucThiPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucThiPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

}
/*****************************************************************************
 函 数 名  : AT_SaveIPv6Dns
 功能描述  : 保存IPV6的DNS到PDP实体中
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : c00173809
    修改内容   : 新生成函数/PS融合项目
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Dns(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
)
{
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns    = VOS_FALSE;
    pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns    = VOS_FALSE;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 保存主副DNS，收到RA参数时需要，激活网卡时需要通知DRV */
    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpPrimDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                pstEvent->stIpv6Dns.aucPrimDnsAddr,
                TAF_IPV6_ADDR_LEN);
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6PriDns = VOS_TRUE;
    }

    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpSecDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   pstEvent->stIpv6Dns.aucSecDnsAddr,
                   TAF_IPV6_ADDR_LEN);
        pstPdpEntity->stIpv6Dhcp.bitOpIpv6SecDns = VOS_TRUE;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

}

/*****************************************************************************
 函 数 名  : AT_AppActCnfBackProc
 功能描述  : PDP激活成功后的回退处理
 输入参数  : pstEvent   - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年4月21日
    作    者   : A00165503
    修改内容   : DTS2012041806921: IPv4v6双栈拨号, 网侧返回原因值为IPv4
                 ONLY或IPv6 ONLY, 没有通知APP相应的拨号结果

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  4.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理

  5.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

  7.日    期   : 2015年7月17日
    作    者   : Y00213812
    修改内容   : CDMA模式下电信不支持双承载双栈
*****************************************************************************/
VOS_VOID AT_AppActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;

    /* 不带原因值或原因值为52，需要发起另一种PDP激活 */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
            {
                /* 查找一个未激活的CID进行激活 */
                ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                }
            }
        }
        else if (TAF_PDP_IPV6 == pstEvent->stPdpAddr.enPdpType)
        {
            if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV4))
            {
                /* 查找一个未激活的CID进行激活 */
                ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                if (VOS_OK == ulRet)
                {
                    AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV4);
                }
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        /* 根据原因值, 通知APP拨号结果 */
        switch (pstEvent->enCause)
        {
            /* 原因值#50 (IPv4 ONLY), 通知APP模块IPv6激活失败 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED:
#endif
                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         pstEvent->enCause,
                                         TAF_PDP_IPV6);

                break;

            /* 原因值#51 (IPv6 ONLY), 通知APP模块IPv4激活失败 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED:
#endif
                AT_AppSndCallEndedResult(pstEvent->ucCid,
                                         pstEvent->enCause,
                                         TAF_PDP_IPV4);

                break;

            /* 其他原因值, 不处理 */
            default:
                AT_NORM_LOG1("AT_AppActCnfBackProc: Other <Cause>", pstEvent->enCause);
                break;
        }
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppIpv4ActCnfProc
 功能描述  : 处理IPV4的PDP激活成功的事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，APP端口发起拨号，拨号成功后通知上下行ADS和RNIC模块。

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  4.日    期   : 2012年12月21日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
 #if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRet;
#endif

    /* 清除DHCP信息 */
    AT_AppDhcpReset();

    /* 记录IPv4类型PDP对应的CID */
    pstAppPdpEntity->ucIpv4Cid          = pstEvent->ucCid;

    /* 将本IPv4类型PDP状态切换到激活状态 */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

    /* 处理IPv4类型的DHCP */
    AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

    /* 通知APP模块IPv4激活 */
    AT_AppSndCallConnectedResult(pstEvent->ucCid, TAF_PDP_IPV4);

    /* 注册流控点 */
    AT_ProcAppRegFCPoint(pstEvent);

    /* 上报RNIC激活消息 */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是IPV4V6，需要激活另一个PDP */
    if (TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
    {
        switch (AT_APP_GetActPdpType())
        {
            /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
               IPV6的PDP激活。其中，TAF_PDP_IPV6是异常情况，用户发起IPV6的PDP
               激活，而网络回复IPV4的激活，此时也需要重新发起IPV6的PDP激活 */
            case TAF_PDP_IPV4:
                if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
                {
                    /* 查找一个未激活的CID进行激活 */
                    ulRet = TAF_AGENT_FindCidForDial(pstEvent->stCtrl.usClientId, &ucCid);
                    if (VOS_OK == ulRet )
                    {
                        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, ucCid, TAF_PDP_IPV6);
                    }
                }
                break;

            /* 这里是PDP激活回退功能实现 */
            case TAF_PDP_IPV4V6:
                /* 将该PDP切换到IDLE态 */
                AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

                AT_AppActCnfBackProc(pstEvent);
                break;

            default:
                AT_WARN_LOG("AT_AppIpv4ActCnfProc:WARNING: PDP type is invalid!");
                break;
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppIpv6ActCnfProc
 功能描述  : 处理IPV6的PDP激活成功的事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，APP端口发起拨号，拨号成功后通知上下行ADS和RNIC模块。

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* 清除DHCPv6信息 */
    AT_AppDhcpv6Reset();

    /* 记录PDP类型对应的CID */
    pstAppPdpEntity->ucIpv6Cid  = pstEvent->ucCid;

    /* 将本IPv6类型状态切换到激活状态 */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

    /* 处理IPV6地址 */
    AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);

    /* IPv6类型的激活指示需要在获取RA信息后上报 */

    /* 注册流控点 */
    AT_ProcAppRegFCPoint(pstEvent);

    /* 上报RNIC激活消息 */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV6);

    /* 如果是IPV4V6，需要激活另一个PDP */
    if (TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
    {
        switch (AT_APP_GetActPdpType())
        {
            case TAF_PDP_IPV6:
                /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
                   IPV6的PDP激活, IPV6激活后不再发起IPV4的PDP激活 */
                break;

            /* 这里是PDP激活回退功能实现 */
            case TAF_PDP_IPV4V6:
                /* 将该PDP切换到IDLE态 */
               AT_AppSetPdpState(AT_APP_GetActPdpType(), AT_PDP_STATE_IDLE);

               AT_AppActCnfBackProc(pstEvent);
               break;

            default:
               AT_WARN_LOG("AT_AppIpv6ActCnfProc: PDP type is invalid!");
               break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppIpv4v6ActCnfProc
 功能描述  : 处理IPv4v6的PDP激活成功的事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，APP端口发起拨号，拨号成功后通知上下行ADS和RNIC模块。

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* 清除DHCP信息 */
    AT_AppDhcpReset();

    /* 清除DHCPv6信息 */
    AT_AppDhcpv6Reset();

    /* 记录PDP类型对应的CID */
    pstAppPdpEntity->ucIpv4v6Cid   = pstEvent->ucCid;

    /* 将本IPv6类型状态切换到激活状态 */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

    /* 处理IPV4地址 */
    AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

    /* 处理IPV6地址*/
    AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);

    /* 通知APP模块IPv4激活, IPv6类型的激活指示需要在获取RA信息后上报 */
    AT_AppSndCallConnectedResult(pstEvent->ucCid, TAF_PDP_IPV4);

    /* 注册流控点 */
    AT_ProcAppRegFCPoint(pstEvent);

    /* 上报RNIC激活消息 */
    AT_AppSndRnicPdpActInd(TAF_PDP_IPV4V6);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppIpv4DeactCnfProc
 功能描述  : 处理IPv4的PDP去激活事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : PS融合项目，去激活时通知上下行ADS和RNIC

  3.日    期   : 2012年6月2日
    作    者   : A00165503
    修改内容   : DTS2012060105018: IPv4v6双栈拨号, 网侧下发PDP去激活(原因值-
                 #39), UE不需要重新发起拨号

  4.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  5.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATE_ENUM_U8                enPdpState;
#endif

    /* 将IPv4类型的PDP切换到IDLE态 */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* 清除DHCP信息 */
    AT_AppDhcpReset();

    /* 通知APP模块IPv4断开 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 通知RNIC PDP去激活成功 */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RMNET_ID_0);

    /* 去注册APP拨号使用的流控点(默认使用网卡1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#if (FEATURE_ON == FEATURE_IPV6)
   /* 如果IPv4类型的PDP还处于激活状态, 需要将其去激活 */
    enPdpState = AT_AppGetPdpState(TAF_PDP_IPV6);
    if ( (AT_PDP_STATE_IDLE     != enPdpState)
      && (AT_PDP_STATE_DEACTING != enPdpState) )
    {
        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      pstEvent->stCtrl.usClientId,
                                      0,
                                      pstAppPdpEntity->ucIpv6Cid) )
        {
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_AppIpv4DeactCnfProc:ERROR: Deactivate PDP failed!");
        }
    }
#endif
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppIpv6DeactCnfProc
 功能描述  : 处理IPv4的PDP去激活事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，PDP去激活后通知上下行ADS和RNIC

  3.日    期   : 2012年6月2日
    作    者   : A00165503
    修改内容   : DTS2012060105018: IPv4v6双栈拨号, 网侧下发PDP去激活(原因值-
                 #39), UE不需要重新发起拨号

  4.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  5.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPdpState;

    /* 将IPv6类型的PDP切换到IDLE态 */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* 清除DHCPv6信息 */
    AT_AppDhcpv6Reset();

    /* 通知APP模块IPv6断开 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 通知RNIC PDP去激活成功 */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RMNET_ID_0);

    /* 去注册APP拨号使用的流控点(默认使用网卡1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    /* 如果IPv4类型的PDP还处于激活状态, 需要将其去激活 */
    enPdpState = AT_AppGetPdpState(TAF_PDP_IPV4);
    if ( (AT_PDP_STATE_IDLE     != enPdpState)
      && (AT_PDP_STATE_DEACTING != enPdpState) )
    {
        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      pstEvent->stCtrl.usClientId,
                                      0,
                                      pstAppPdpEntity->ucIpv4Cid) )
        {
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_AppIpv6DeactCnfProc:ERROR: Deactivate PDP failed!");
        }
    }
}

/*****************************************************************************
 函 数 名  : AT_AppIpv4v6DeactCnfProc
 功能描述  : 处理IPv4v6的PDP去激活事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : ps融合项目，PDP去激活后通知上下行ADS和RNIC

  3.日    期   : 2012年6月2日
    作    者   : A00165503
    修改内容   : DTS2012060105018: IPv4v6双栈拨号, 网侧下发PDP去激活(原因值-
                 #39), UE不需要重新发起拨号

  4.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  5.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* 将IPv6类型的PDP切换到IDLE态 */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* 清除DHCP信息 */
    AT_AppDhcpReset();

    /* 清除DHCPv6信息 */
    AT_AppDhcpv6Reset();

    /* 通知APP模块IPv4断开 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);

    /* 通知APP模块IPv6断开 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 通知RNIC PDP去激活成功 */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, RNIC_RMNET_ID_0);

    /* 去注册APP拨号使用的流控点(默认使用网卡1) */
    AT_AppDeRegFCPoint(FC_ID_NIC_1, pstEvent);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppIpv4v6PdpActRejProc
 功能描述  : 处理IPv4的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目

  3.日    期   : 2012年6月16日
    作    者   : A00165503
    修改内容   : DTS2012061408511: IPv4v6双栈拨号回退处理流程增加保护机制,
                 防止重复发起IPv4类型的PDP激活请求

  4.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  5.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理
  6.日    期   : 2013年5月08日
    作    者   : Y00213812
    修改内容   : V9R1 IPv6&TAF/SM Project
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_STATE_ENUM_U8                enPreIpv4State;

    enPreIpv4State = pstAppPdpEntity->enIpv4State;

    /* 用户发起IPv4v6类型的PDP激活, 而且被网络拒绝, 原因为28, 协议栈需要
       分别发起IPv4/IPv6类型的PDP激活, 协议栈首先发起IPv4, 再发起IPv6,
       如果IPv4类型的PDP激活再次被网络拒绝, 协议栈还需要尝试IPV6类型的
       PDP激活为了防止PDP激活嵌套, 如果IPv6类型的PDP激活失败, 将不再尝试
       IPv4类型的PDP激活 */

    /* 将IPv4类型的PDP状态切换到IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* 上报IPv4拨号失败 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV4);
#if (FEATURE_ON == FEATURE_IPV6)
    if ((TAF_PDP_IPV4V6 == AT_APP_GetFirstActPdpType())
     && (AT_PDP_STATE_ACTING == enPreIpv4State) )
    {
        /* 检查IPv6连接是否已经存在, 如果不存在, 发起IPv6类型的PDP激活 */
        if (AT_PDP_STATE_IDLE == AT_AppGetPdpState(TAF_PDP_IPV6))
        {
            /* 发起IPv6类型的PDP激活请求 */
            AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV6);

            /* 清除拨号参数的处理需要在最后一次PDP激活流程结束后, 此处直接返回 */
            return;
        }

        /* 清除拨号参数的处理需要在最后一次PDP激活流程结束后, 此处直接返回 */
        return;
    }
#endif

    /* 清除拨号参数 */
    PS_MEM_SET(AT_APP_GetDailParaAddr(), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppIpv6PdpActRejProc
 功能描述  : 处理IPv6的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  4.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* 如果IPv6类型, 就不需要再尝试IPv4, 因为前面已经发起过IPv4类型的PDP
       激活, 如果再发起IPv4类型的PDP激活的话, 可能会导致PDP激活嵌套 */

    /* 将IPv6类型的PDP状态切换到IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* 上报IPv6拨号失败 */
    AT_AppSndCallEndedResult(pstEvent->ucCid,
                             pstEvent->enCause,
                             TAF_PDP_IPV6);

    /* 清除拨号参数 */
    PS_MEM_SET(AT_APP_GetDailParaAddr(), 0x00, sizeof(AT_DIAL_PARAM_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppIpv4v6PdpActRejProc
 功能描述  : 处理IPv4的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月23日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  4.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* 将IPv4v6类型的PDP状态切换到IDLE */
    AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* 这种情况，需要分别发起IPv4、IPv6的PDP激活 */
    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == pstEvent->enCause)
    {
        /* 发起IPv4类型的PDP激活 */
        AT_AppPdpActOrig(pstEvent->stCtrl.usClientId, pstEvent->ucCid, TAF_PDP_IPV4);
    }
    else
    {
        /* 上报IPv4拨号失败 */
        AT_AppSndCallEndedResult(pstEvent->ucCid,
                                 pstEvent->enCause,
                                 TAF_PDP_IPV4);

        /* 上报IPv6拨号失败 */
        AT_AppSndCallEndedResult(pstEvent->ucCid,
                                 pstEvent->enCause,
                                 TAF_PDP_IPV6);

        /* 清除拨号参数 */
        PS_MEM_SET(AT_APP_GetDailParaAddr(), 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpActEvtCnfProc
 功能描述  : PDP激活成功，APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* 根据PDP类型分别处理*/
    switch ( pstEvent->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            /* 处理IPv4的PDP激活成功事件 */
            AT_AppIpv4PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* 处理IPv6的PDP激活成功事件 */
            AT_AppIpv6PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* 处理IPv4v6的PDP激活成功事件 */
            AT_AppIpv4v6PdpActCnfProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspPdpActEvtCnfProc:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpActEvtRejProc
 功能描述  : PDP激活失败，APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch (AT_APP_GetActPdpType())
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_AppIpv6PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpActRejProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspEvtPdpActRejProc:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpDeactEvtCnfProc
 功能描述  : PDP去激活成功，APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspPdpDeactEvtCnfProc:WARNING: Invalid PDP type.");
            break;
    }

    /* 清除拨号参数 */
    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) )
    {
        PS_MEM_SET(pstAppDialPara, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpDeactivatedEvtProc
 功能描述  : 网侧去激活PDP, APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            AT_AppIpv4PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            AT_AppIpv6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            AT_AppIpv4v6PdpDeactivatedProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_AppPsRspPdpDeactEvtCnfProc:WARNING: Invalid PDP type.");
            break;
    }

    /* 清除APP拨号参数 */
    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) )
    {
        PS_MEM_SET(pstAppDialPara, 0x00, sizeof(AT_DIAL_PARAM_STRU));
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppSetFlowCtrl
 功能描述  : 启动路由设备流控
 输入参数  : ulParam1   - 目前不使用
             ulParam2   - 目前不使用
 输出参数  : 无
 返 回 值  : VOS_OK     - 启动流控成功
             VOS_ERR    - 启动流控失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_AppSetFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = RNIC_StartFlowCtrl((VOS_UINT8)ulParam1);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_AppClearFlowCtrl
 功能描述  : 停止路由设备流控
 输入参数  : ulParam1   - 目前不使用
             ulParam2   - 目前不使用
 输出参数  : 无
 返 回 值  : VOS_OK     - 停止流控成功
             VOS_ERR    - 停止流控失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_AppClearFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = RNIC_StopFlowCtrl((VOS_UINT8)ulParam1);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_AppRegFCPoint
 功能描述  : 注册路由端口流控点
 输入参数  : FC_ID_ENUM_UINT8                    enFcId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
             VOS_UINT8                           ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年12月22日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
  3.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目
*****************************************************************************/
VOS_UINT32 AT_AppRegFCPoint(
    FC_ID_ENUM_UINT8                    enFcId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    VOS_UINT8                           ucRmNetId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    FC_PRI_ENUM_UINT8                   enDefaultFcPri;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRslt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* 配置通道与RABID映射关系 */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    /* 根据网卡上最高优先级RAB QoS优先级来折算,优先级改变时，需要改变优先级 */
    /*  FC_PRI_3        有最低优先级的承载
        FC_PRI_4        有NONGBR承载
        FC_PRI_5        有GBR承载 */
    enDefaultFcPri          = FC_PRI_FOR_PDN_LOWEST;
    stRegFcPoint.enFcId     = enFcId;
    stRegFcPoint.enFcPri    = enDefaultFcPri;

    stRegFcPoint.enModemId  = enModemId;
    stRegFcPoint.pClrFunc   = AT_AppClearFlowCtrl;
    stRegFcPoint.pSetFunc   = AT_AppSetFlowCtrl;

    /* Paramter1设置为RmNetId, Paramter2设置为FCID */
    stRegFcPoint.ulParam1   = ucRmNetId;
    stRegFcPoint.ulParam2   = enFcId;
    stRegFcPoint.pRstFunc   = AT_ResetFlowCtl;

    /* 注册流控点, 需要分别注册MEM和CDS */
    stRegFcPoint.enPolicyId = FC_POLICY_ID_MEM;
    ulRslt = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }


    stRegFcPoint.enPolicyId = FC_POLICY_ID_CDS;
    ulRslt = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppRegFCPoint: ERROR: reg CDS point Failed.");
        return VOS_ERR;
    }

    /* 设置FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = enDefaultFcPri;
    /* 有一张网卡上多个RABID的情况，所以需要将多个RABID记录下来 */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[enFcId].enModemId    = enModemId;

    /* 勾流控消息 */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_RMNET);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_AppDeRegFCPoint
 功能描述  : 去注册路由设备流控点
 输入参数  : FC_ID_ENUM_UINT8                            enFcId,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
 输出参数  : 无
 返 回 值  : VOS_OK     - 去注册流控点成功
             VOS_ERR    - 去注册流控点失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年12月22日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
  3.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目
*****************************************************************************/
VOS_UINT32 AT_AppDeRegFCPoint(
    FC_ID_ENUM_UINT8                     enFcId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppDeRegFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* 在调用FC_DeRegPoint前,先调用FC_ChannelMapDelete */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRslt = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_AppDeRegFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* 清除FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
    /* 有一张网卡上多个RABID的情况，所以需要将对应的RABID掩码清除掉 */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask &= ~((VOS_UINT32)1 << pstEvent->ucRabId);
    g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    /* 勾流控消息 */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_RMNET);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_APP_ParseUsrInfo
 功能描述  : 获取APP用户信息
 输入参数  : ucIndex     - 端口号(ClientId)索引
 输出参数  : pstUserInfo - 用户信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月14日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_APP_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;

    if (VOS_TRUE == AT_CheckAppUser(ucIndex))
    {
        enUserIndex = ucIndex;
    }
    else
    {
        enUserIndex = AT_CLIENT_TAB_APP_INDEX;
    }

    pstUsrInfo->enPortIndex = ucIndex;
    pstUsrInfo->enUserIndex = enUserIndex;
    pstUsrInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUserIndex].UserType;
    pstUsrInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}

/*****************************************************************************
 函 数 名  : AT_GetFCPriFromQos
 功能描述  : Qos转化为FC优先级
 输入参数  : TAF_UMTS_QOS_STRU                  *pstUmtsQos
 输出参数  : 无
 返 回 值  : FC_PRI_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换为QOS
*****************************************************************************/
FC_PRI_ENUM_UINT8 AT_GetFCPriFromQos(
    TAF_UMTS_QOS_STRU                  *pstUmtsQos
)
{

    FC_PRI_ENUM_UINT8                   enFCPri;
    VOS_UINT8                           ucTrafficClass;

    /* 初始化 */
    enFCPri         = FC_PRI_FOR_PDN_NONGBR;

    ucTrafficClass              = pstUmtsQos->ucTrafficClass;

    /* 根据QOS trafficClass参数获取QCI */
    if (AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_GBR;
    }
    else if (AT_QOS_TRAFFIC_CLASS_STREAMING == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_GBR;
    }
    else if (AT_QOS_TRAFFIC_CLASS_INTERACTIVE == ucTrafficClass)
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_LOWEST;
    }

    return enFCPri;
}

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpDeactivatedEvtProc
 功能描述  : pdp去激活成功，Modem处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，IP类型MODEM去激活，通知上下行ADS
  3.日    期   : 2013年05月27日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
  5.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加UART端口PPP拨号支持
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl = AT_GetUartLineCtrlInfo();
    usLength    = 0;
    ulResult    = AT_FAILURE;
    ulATHCmdFlg = (AT_CMD_H_PS_SET == AT_PS_GET_CURR_CMD_OPT(ucIndex)) ?
                  VOS_TRUE : VOS_FALSE;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 去注册Modem端口的流控点 */
    AT_DeRegModemPsDataFCPoint(ucIndex, pstEvent->ucRabId);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* 释放PPP实体 & HDLC去使能 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        if (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
        {
            /* 根据问题单AT2D13296，在被动去激活情景下，向PPP发送了
               PPP_AT_CTRL_REL_PPP_REQ后，不立即切入命令态，而是等
               待PPP回应AT_PPP_PROTOCOL_REL_IND_MSG之后再切入命令态 */
            /* 开保护定时器，用于等待PPP回应AT_PPP_PROTOCOL_REL_IND_MSG */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            if (AT_SUCCESS != At_StartTimer(AT_PPP_PROTOCOL_REL_TIME, ucIndex))
            {
                AT_ERR_LOG("At_UsbModemStatusPreProc:ERROR:Start Timer fail");
            }

            /* 设置当前操作类型 */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAIT_PPP_PROTOCOL_REL_SET;

            return;
        }
    }
    else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* 释放PPP实体 & HDLC去使能 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        /* 其它数传模式，不用处理 */
        AT_WARN_LOG("TAF_PS_EVT_PDP_DEACTIVATED OTHER MODE");
    }

    /* 返回命令模式 */
    At_SetMode(ucIndex, AT_CMD_MODE,AT_NORMAL_MODE);

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    /* ATH断开PPP连接时, 如果DCD信号模式为CONNECT ON, 需要拉低DCD信号 */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpActEvtRejProc
 功能描述  : pdp激活失败，AP MODEM处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年10月22日
    作    者   : f62575
    修改内容   : AT PROJECT OM_GreenChannel -> OM_AppGreenChannel
  3.日    期   : 2015年07月22日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    ulResult                            = AT_FAILURE;
    usLength                            = 0;

    if ( (AT_CMD_D_PPP_CALL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
      || (AT_CMD_PPP_ORG_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
    {
        ulResult = AT_NO_CARRIER;
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);

        /* 向PPP发送HDLC去使能操作 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        /* 返回命令模式 */
        At_SetMode(ucIndex,AT_CMD_MODE,AT_NORMAL_MODE);

        /* Deleted by wx270776 for OM融合, 2015-6-29, begin */
        /* Deleted by wx270776 for OM融合, 2015-6-29, end */
    }
    else if (AT_CMD_D_IP_CALL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        ulResult = AT_ERROR;
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /* 向PPP发送HDLC去使能操作 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);


        /* Deleted by wx270776 for OM融合, 2015-6-29, begin */
        /* Deleted by wx270776 for OM融合, 2015-6-29, end */
    }
    else
    {
        ulResult = AT_ERROR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    return;
}

/*****************************************************************************
 函 数 名  : AT_FillPppIndConfigInfoPara
 功能描述  : 获取PPP配置参数
 输入参数  : AT_PPP_IND_CONFIG_INFO_STRU        *pstPppIndConfigInfo
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月29日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID AT_FillPppIndConfigInfoPara(
    AT_PPP_IND_CONFIG_INFO_STRU        *pstPppIndConfigInfo,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 填写IP地址 */
    PS_MEM_CPY(pstPppIndConfigInfo->aucIpAddr,
               pstEvent->stPdpAddr.aucIpv4Addr,
               TAF_IPV4_ADDR_LEN);

    /* 填写DNS地址 */
    if (VOS_TRUE == pstEvent->stDns.bitOpPrimDnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpPriDns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucPriDns,
               pstEvent->stDns.aucPrimDnsAddr,
               TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstEvent->stDns.bitOpSecDnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpSecDns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucSecDns,
                       pstEvent->stDns.aucSecDnsAddr,
                       TAF_IPV4_ADDR_LEN);

    }

    /* 填写NBNS地址 */
    if (VOS_TRUE == pstEvent->stNbns.bitOpPrimNbnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpPriNbns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucPriNbns,
                   pstEvent->stNbns.aucPrimNbnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstEvent->stNbns.bitOpSecNbnsAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpSecNbns = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucSecNbns,
                   pstEvent->stNbns.aucSecNbnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    /* 填写GATE WAY地址 */
    if (VOS_TRUE == pstEvent->stGateWay.bitOpGateWayAddr)
    {
        pstPppIndConfigInfo->stPcoIpv4Item.bitOpGateWay = VOS_TRUE;

        PS_MEM_CPY(pstPppIndConfigInfo->stPcoIpv4Item.aucGateWay,
                   pstEvent->stGateWay.aucGateWayAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

}

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpActEvtCnfProc
 功能描述  : Modem发起的pdp激活成功，
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，IP类型MODEM激活，通知上下行ADS
  3.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PPP_IND_CONFIG_INFO_STRU         stPppIndConfigInfo;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 注册Modem端口的流控点 */
    AT_RegModemPsDataFCPoint(ucIndex, pstEvent, FC_ID_MODEM);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */


    /* 初始化 */
    PS_MEM_SET(&stPppIndConfigInfo, 0x00, sizeof(AT_PPP_IND_CONFIG_INFO_STRU));

    /* 清除命令操作类型 */
    AT_STOP_TIMER_CMD_READY(ucIndex);


    if (TAF_PDP_PPP == pstEvent->stPdpAddr.enPdpType)
    {
        At_SetMode(ucIndex, AT_DATA_MODE, AT_IP_DATA_MODE);

        /* 注册下行数据发送函数 */
        Ppp_RegDlDataCallback(gastAtClientTab[ucIndex].usPppId);

        At_FormatResultData(ucIndex, AT_CONNECT);
    }
    else if (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType)
    {
        /* 填写IP地址, DNS, NBNS */
        AT_FillPppIndConfigInfoPara(&stPppIndConfigInfo, pstEvent);

        /* 将AUTH和IPCP帧交给PPP处理: */
        Ppp_RcvConfigInfoInd(gastAtClientTab[ucIndex].usPppId, &stPppIndConfigInfo);

        AT_PS_ProcActSharePdpState(pstEvent, TAF_PDP_IPV4);
    }
    else
    {
        /* 其他类型不做处理 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpDeactEvtCnfProc
 功能描述  : pdp去激活成功，Modem处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年10月22日
    作    者   : f62575
    修改内容   : AT PROJECT NAS_EventReport -> AT_EventReport
  3.日    期   : 2011年12月17日
    作    者   : C00173809
    修改内容   : PS融合项目，PDP去激活后通知ADS和流控模块。
  4.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改

  5.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加UART端口PPP拨号支持
*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulModemUsrFlg;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl     = AT_GetUartLineCtrlInfo();
    ulModemUsrFlg   = AT_CheckModemUser(ucIndex);
    usLength        = 0;
    ulResult        = AT_FAILURE;
    ulATHCmdFlg     = (AT_CMD_H_PS_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) ?
                      VOS_TRUE : VOS_FALSE;

    if ( (AT_MODEM_USER != gastAtClientTab[ucIndex].UserType)
      && (AT_HSUART_USER != gastAtClientTab[ucIndex].UserType) )
    {
        return;
    }

    if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* 释放PPP实体 & HDLC去使能 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        AT_PS_ProcDeactSharePdpState(pstEvent, TAF_PDP_IPV4);
    }
    else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
    {
        /* 释放PPP实体 & HDLC去使能 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /* 向PPP发送HDLC去使能操作 */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        /* 其它数传模式，不用处理 */
        AT_WARN_LOG("TAF_PS_EVT_PDP_DEACTIVE_CNF OTHER MODE");
    }

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 去注册Modem端口的流控点 */
    AT_DeRegModemPsDataFCPoint(ucIndex, pstEvent->ucRabId);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    /* 返回命令模式 */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

    /* 为了规避Linux后台二次拨号失败问题，采用如下规避方案:
       PDP正常断开流程结束后，接收到TAF_PS_EVT_PDP_DEACTIVE_CNF事件，判断操作
       系统是否为Linux，若否，则按照原先流程处理，若是，则不再发送"NO CARRIER" */
    if ((VOS_OK == DRV_GET_LINUXSYSTYPE()) && (VOS_TRUE == ulModemUsrFlg))
    {
        /* 原先流程中，在At_FormatResultData函数内部，发送了"NO CARRIER"之后，
           需要将DCD拉低，在此规避方案中，不发送"NO CARRIER"，但DCD信号的拉低
           操作仍旧需要保持
        */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        return;
    }

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex,ulResult);

    /* ATH断开PPP连接时, 如果DCD信号模式为CONNECT ON, 需要拉低DCD信号 */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_MODEM_ProcCallEndedEvent
 功能描述  : 处理PS_CALL_END_CNF事件
 输入参数  : ucIndex  - 端口索引
             pstEvent - ID_EVT_TAF_PS_CALL_END_CNF事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_MODEM_ProcCallEndCnfEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_END_CNF_STRU           *pstEvent
)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_DCE_MSC_STRU                     stDecMsc;
    VOS_UINT32                          ulModemUsrFlg;
    VOS_UINT32                          ulATHCmdFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    pstLineCtrl     = AT_GetUartLineCtrlInfo();
    ulModemUsrFlg   = AT_CheckModemUser(ucIndex);
    ulResult        = AT_FAILURE;
    usLength        = 0;
    ulATHCmdFlg     = (AT_CMD_H_PS_SET == AT_PS_GET_CURR_CMD_OPT(ucIndex)) ?
                      VOS_TRUE : VOS_FALSE;

    PS_MEM_SET(&stDecMsc, 0x00, sizeof(AT_DCE_MSC_STRU));

    /* 检查当前用户的操作类型 */
    if ( (AT_CMD_PS_DATA_CALL_END_SET != AT_PS_GET_CURR_CMD_OPT(ucIndex))
      && (AT_CMD_H_PS_SET != AT_PS_GET_CURR_CMD_OPT(ucIndex)) )
    {
        return;
    }

    /* PS域呼叫正在处理断开请求, 直接返回 */
    if (TAF_ERR_NO_ERROR == pstEvent->enCause)
    {
        return;
    }

    /* 释放PPP实体 & HDLC去使能 */
    if (AT_PPP_DATA_MODE == AT_PS_GET_CURR_DATA_MODE(ucIndex))
    {
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_REL_PPP_REQ);
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_HDLC_DISABLE);
    }
    else if (AT_IP_DATA_MODE == AT_PS_GET_CURR_DATA_MODE(ucIndex))
    {
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_REL_PPP_RAW_REQ);
        PPP_RcvAtCtrlOperEvent(AT_PS_GET_PPPID(ucIndex), PPP_AT_CTRL_HDLC_DISABLE);
    }
    else
    {
        ;
    }

    /* 返回命令模式 */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

    /* 为了规避Linux后台二次拨号失败问题，采用如下规避方案:
       PDP正常断开流程结束后，接收到TAF_PS_EVT_PDP_DEACTIVE_CNF事件，判断操作
       系统是否为Linux，若否，则按照原先流程处理，若是，则不再发送"NO CARRIER" */
    if ((VOS_OK == DRV_GET_LINUXSYSTYPE()) && (VOS_TRUE == ulModemUsrFlg))
    {
        /* 原先流程中，在At_FormatResultData函数内部，发送了"NO CARRIER"之后，
           需要将DCD拉低，在此规避方案中，不发送"NO CARRIER"，但DCD信号的拉低
           操作仍旧需要保持
        */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        return;
    }

    if (VOS_TRUE == ulATHCmdFlg)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_NO_CARRIER;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    /* ATH断开PPP连接时, 如果DCD信号模式为CONNECT ON, 需要拉低DCD信号 */
    if ( (AT_OK == ulResult)
      && (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode) )
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AnswerPdpActInd
 功能描述  : 应答网络发起的pdp激活成功
 输入参数  : ucIndex --- 已知的客户标识号
             pstEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月05日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
  3.日    期   : 2015年07月23日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID  AT_AnswerPdpActInd(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT16                          usPppId;
    VOS_UINT32                          ulRslt;

    usPppId     = 0;

    if (TAF_PDP_PPP == pstEvent->stPdpAddr.enPdpType)
    {
        if (VOS_OK != Ppp_CreateRawDataPppReq(&usPppId))
        {
            /* Deleted by wx270776 for OM融合, 2015-7-23, begin */
            /* Deleted by wx270776 for OM融合, 2015-6-29, end */
            ulRslt = AT_ERROR;
        }
        else
        {
            /* 记录PPP id和Index的对应关系 */
            gastAtPppIndexTab[usPppId]          = ucIndex;

            /* 保存PPP id */
            gastAtClientTab[ucIndex].usPppId    = usPppId;


            /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
            /* 注册Modem端口的流控点 */
            AT_RegModemPsDataFCPoint(ucIndex, pstEvent, FC_ID_MODEM);
            /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

            /* 切换数传通道 */
            At_SetMode(ucIndex, AT_DATA_MODE, AT_IP_DATA_MODE);

            /* 注册下行数据发送函数 */
            Ppp_RegDlDataCallback(usPppId);

            ulRslt = AT_CONNECT;
        }

        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        /* 方案待定....*/
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, AT_CONNECT);
    }

    return;
}

/*****************************************************************************
 Prototype      : At_RcvTeConfigInfoReq
 Description    : AT接收TE请求的配置信息
 Input          : usPppId --- PPP ID
                  pPppReqConfigInfo  --- TE请求的配置信息
 Output         :
 Return Value   : AT_XXX  --- ATC返回码
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function

  2.日    期   : 2011年12月12日
    作    者   : l00171473
    修改内容   : DTS2011112306269,修改PDP激活时AT的TIMER的时长

*****************************************************************************/
TAF_UINT32 At_RcvTeConfigInfoReq(
    TAF_UINT16                          usPppId,
    AT_PPP_REQ_CONFIG_INFO_STRU        *pstPppReqConfigInfo
)
{
    if (AT_MAX_CLIENT_NUM <= usPppId)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq usPppId Wrong");
        return AT_FAILURE;
    }

    if (TAF_NULL_PTR == pstPppReqConfigInfo)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq pPppReqConfigInfo NULL");
        return AT_FAILURE;
    }

    if (AT_CMD_D_PPP_CALL_SET != gastAtClientTab[gastAtPppIndexTab[usPppId]].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvTeConfigInfoReq NOT AT_CMD_D_PPP_CALL_SET");
        return AT_FAILURE;
    }

    if ( VOS_OK == TAF_PS_PppDialOrig(WUEPS_PID_AT,
                                      gastAtClientTab[gastAtPppIndexTab[usPppId]].usClientId,
                                      0,
                                      gastAtClientTab[gastAtPppIndexTab[usPppId]].ucCid,
                                      (TAF_PPP_REQ_CONFIG_INFO_STRU *)pstPppReqConfigInfo) )
    {
        /* 开定时器 */
        /* Modified by L00171473 for DTS2011112306269,修改PDP激活的AT保护时长, 2011-12-09, Begin */
        if (AT_SUCCESS != At_StartTimer(AT_ACT_PDP_TIME, gastAtPppIndexTab[usPppId]))
        {
            AT_ERR_LOG("At_RcvTeConfigInfoReq:ERROR:Start Timer");
            return AT_FAILURE;
        }

        /* 设置当前操作类型 */
        gastAtClientTab[gastAtPppIndexTab[usPppId]].CmdCurrentOpt = AT_CMD_PPP_ORG_SET;

        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/*****************************************************************************
 函 数 名  : At_RcvPppReleaseInd
 功能描述  : AT接收PPP释放链路指示
 输入参数  : TAF_UINT16                          usPppId  PPP ID
 输出参数  : 无
 返 回 值  : TAF_UINT32
             0 --- 成功
             1 --- 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月22日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
TAF_UINT32 At_RcvPppReleaseInd(
    TAF_UINT16                          usPppId
)
{
    TAF_UINT8                           aucEventInfo[4];
    AT_PPP_RELEASE_IND_MSG_STRU        *pMsg;
    VOS_UINT32                          ulLength;

    if (AT_MAX_CLIENT_NUM <= usPppId)
    {
        AT_WARN_LOG("At_RcvPppReleaseInd usPppId Wrong");
        return AT_FAILURE;
    }

    /* EVENT- At_RcvPppReleaseInd:usPppId / gastAtPppIndexTab[usPppId] */
    aucEventInfo[0] = (TAF_UINT8)(usPppId >> 8);
    aucEventInfo[1] = (TAF_UINT8)usPppId;
    aucEventInfo[2] = gastAtPppIndexTab[usPppId];
    AT_EventReport(WUEPS_PID_AT, NAS_OM_EVENT_DTE_RELEASE_PPP,
                   aucEventInfo, sizeof(aucEventInfo));

    /* 向AT模块发送AT_PPP_RELEASE_IND_MSG */
    ulLength       = sizeof(AT_PPP_RELEASE_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pMsg = (AT_PPP_RELEASE_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_APP_PPP, ulLength);
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印出错信息---申请消息包失败 */
        AT_ERR_LOG( "At_RcvPppReleaseInd:ERROR:Allocates a message packet for AT_PPP_RELEASE_IND_MSG_STRU msg FAIL!" );
        return AT_FAILURE;
    }
    /* 填写消息头 */
    pMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid     = PS_PID_APP_PPP;
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_AT;
    pMsg->MsgHeader.ulLength        = ulLength;

    pMsg->MsgHeader.ulMsgName       = AT_PPP_RELEASE_IND_MSG;
    /* 填写消息体 */
    pMsg->ucIndex                   = gastAtPppIndexTab[usPppId];

    /* 发送该消息 */
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_PPP, pMsg))
    {
        /* 打印警告信息---发送消息失败 */
        AT_WARN_LOG( "At_RcvPppReleaseInd:WARNING:SEND AT_PPP_RELEASE_IND_MSG msg FAIL!" );
        return AT_FAILURE;
    }
    else
    {
        /* 打印流程信息---发送了消息 */
        AT_WARN_LOG( "At_RcvPppReleaseInd:NORMAL:SEND AT_PPP_RELEASE_IND_MSG Msg" );
        return AT_SUCCESS;
    }
}

/*****************************************************************************
 Prototype      : At_PppReleaseIndProc
 Description    : AT接收PPP释放链路指示消息
 Input          : ucIndex
 Output         : ---
 Return Value   : VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-04-19
    Author      : L47619
    Modification: Created function

  2.日    期   : 2011年12月12日
    作    者   : l00171473
    修改内容   : DTS2011112306269,修改PDP去激活时的AT保护时长

  3.日    期   : 2014年1月14日
    作    者   : A00165503
    修改内容   : DTS2013120310013: 增加PPP重复释放保护
*****************************************************************************/
TAF_VOID At_PppReleaseIndProc(
    TAF_UINT8                           ucIndex
)
{
    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        AT_WARN_LOG("At_PppReleaseIndProc:ERROR:ucIndex is abnormal!");
        return;
    }

    if (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* 将AT通道切换为命令模式 */
        At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

        /*停止定时器*/
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /*回复NO CARRIER*/
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_NO_CARRIER);

        return;
    }

    if (AT_CMD_PS_DATA_CALL_END_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return;
    }

    if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0,
                                  gastAtClientTab[ucIndex].ucCid) )
    {
        /* 开定时器 */
        /* Modified by L00171473 for DTS2011112306269,修改PDP去激活时的AT保护时长, 2011-12-09, Begin */
        if (AT_SUCCESS != At_StartTimer(AT_DETACT_PDP_TIME, ucIndex))
        {
            AT_ERR_LOG("At_PppReleaseIndProc:ERROR:Start Timer");
            return;
        }

        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;
    }

    return;
}

/*****************************************************************************
 Prototype      : At_PsRab2PppId
 Description    : 由已知Rab ID获取PPP ID
 Input          : RabId     --- 已知的RAB ID
 Output         : pusPppId  --- PPP ID
 Return Value   : AT_SUCCESS --- 成功
                  AT_FAILURE --- 失败
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-03-05
    Author      : g45205
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PsRab2PppId(
    TAF_UINT8                           ucRabId,
    TAF_UINT16                         *pusPppId
)
{
    TAF_UINT16                          usPppId;
    TAF_UINT8                           ucIndex;

    if (VOS_NULL_PTR == pusPppId)
    {
        AT_WARN_LOG("At_PsRab2PppId, pusPppId NULL");
        return TAF_FAILURE;
    }

    /* 通过PPP ID方向查找，效率会比较高 */
    for (usPppId = 1; usPppId <= PPP_MAX_ID_NUM; usPppId++)
    {
        ucIndex = gastAtPppIndexTab[usPppId];

        if (AT_MAX_CLIENT_NUM <= ucIndex)
        {
            continue;
        }

        if ( AT_CLIENT_USED != gastAtClientTab[ucIndex].ucUsed )
        {
            continue;
        }

        if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
        {
            continue;
        }

        if ( (AT_PPP_DATA_MODE != gastAtClientTab[ucIndex].DataMode)
          && (AT_IP_DATA_MODE != gastAtClientTab[ucIndex].DataMode) )
        {
            continue;
        }

        if (gastAtClientTab[ucIndex].ucPsRabId == ucRabId)
        {
            *pusPppId = usPppId;    /* 返回结果 */
            return TAF_SUCCESS;
        }

    }

    AT_LOG1("AT, At_PsRab2PppId, WARNING, Get PppId from Rab <1> Fail", ucRabId);

    return TAF_FAILURE;
} /* At_PsRab2PppId */


/*****************************************************************************
 Prototype      : At_PppId2PsRab
 Description    : 由已知PPP ID获取Rab ID
 Input          : usPppId   ---  已知的PPP ID
 Output         : pucRabId  ---  RAB ID
 Return Value   : AT_SUCCESS --- 成功
                  AT_FAILURE --- 失败
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-03-05
    Author      : g45205
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PppId2PsRab(
    TAF_UINT16                          usPppId,
    TAF_UINT8                          *pucRabId
)
{
    TAF_UINT8                           ucIndex;


    if ((usPppId < 1) || (usPppId > PPP_MAX_ID_NUM))
    {
        TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_WARNING,
            "AT, At_PppId2PsRab, WARNING, PppId <1> Wrong", usPppId);
        return TAF_FAILURE;
    }

    if (TAF_NULL_PTR == pucRabId)
    {
        AT_WARN_LOG("AT, At_PppId2PsRab, WARNING, pucRabId NULL");
        return TAF_FAILURE;
    }

    ucIndex = gastAtPppIndexTab[usPppId];

    if (AT_MAX_CLIENT_NUM <= ucIndex)
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, index <1> Wrong", ucIndex);
        return TAF_FAILURE;
    }

    if (AT_DATA_MODE != gastAtClientTab[ucIndex].Mode)
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, Mode <1> Wrong", gastAtClientTab[ucIndex].Mode);
        return TAF_FAILURE;
    }

    if ( (AT_PPP_DATA_MODE != gastAtClientTab[ucIndex].DataMode)
      && (AT_IP_DATA_MODE  != gastAtClientTab[ucIndex].DataMode) )
    {
        AT_LOG1("AT, At_PppId2PsRab, WARNING, DataMode <1> Wrong", gastAtClientTab[ucIndex].DataMode);
        return TAF_FAILURE;
    }

    *pucRabId = gastAtClientTab[ucIndex].ucPsRabId;

    return TAF_SUCCESS;
} /* At_PppId2PsRab */

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
 函 数 名  : AT_ResetFlowCtl
 功能描述  : 复位流控
 输入参数  : ulParam1      不关注
             ulParam2      FCID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_VpResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32                          ulRet;
    FC_ID_ENUM_UINT8                    enFcId;
    MODEM_ID_ENUM_UINT16                enModemId;

    enFcId    = ulParam2;
    enModemId = g_stFcIdMaptoFcPri[enFcId].enModemId;

    if (VOS_TRUE == g_stFcIdMaptoFcPri[enFcId].ulUsed)
    {
        ulRet = FC_DeRegPoint(enFcId, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_VpResetFlowCtl: ERROR: de reg point Failed.");
            return VOS_ERR;
        }

        g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RegModemCstFCPoint
 功能描述  : 注册Modem端口VP的流控点
 输入参数  : FC_ID_ENUM_UINT8   enFcId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月21日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : l60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  4.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 AT_RegModemVideoPhoneFCPoint(
    VOS_UINT8                           ucIndex,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFcPri;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    stRegFcPoint.enFcId             = enFcId;

    /*  FC_PRI_3        有最低优先级的承载
        FC_PRI_4        有NONGBR承载
        FC_PRI_5        有GBR承载 */
    enFcPri                         = FC_PRI_FOR_PDN_LOWEST;
    stRegFcPoint.enFcPri            = enFcPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.pClrFunc           = AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc           = AT_MODEM_StartFlowCtrl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)g_alAtUdiHandle[ucIndex];
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_VpResetFlowCtl;

    /* 注册流控点,需要分别注册MEM,CPU,CST */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: ERROR: FC RegPoint CST Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: ERROR: FC RegPoint MEM Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CST;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemVideoPhoneFCPoint: ERROR: FC RegPoint A CPU Failed.");
        return VOS_ERR;
    }

    /* 设置FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed  = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri = enFcPri;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId = enModemId;

    /* 勾流控消息 */
    AT_MNTN_TraceRegFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_VP);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DeRegModemCstFCPoint
 功能描述  : 去注册Modem端口VP的流控点。
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月21日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年12月28日
    作    者   : l60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  4.日    期   : 2013年05月28日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 AT_DeRegModemVideoPhoneFCPoint(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemVideoPhoneFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    ulRet = FC_DeRegPoint(FC_ID_MODEM, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemVideoPhoneFCPoint: ERROR: FC DeRegPoint Failed.");
        return VOS_ERR;
    }

    /* 清除FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = FC_PRI_BUTT;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = MODEM_ID_BUTT;

    /* 勾流控消息 */
    AT_MNTN_TraceDeregFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_VP);

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : AT_RegModemPsDataFCPoint
 功能描述  : 注册Modem端口PsData的流控点。
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:修改注册MODEM流控点的逻辑
  3.日    期   : 2012年5月22日
    作    者   : f00179208
    修改内容   : DTS2012052205142, 增加VIDEO PHONE的流控
  4.日    期   : 2012年12月27日
    作    者   : l60609
    修改内容   : DSDA Phase II
  5.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
  7.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加流控使能开关

*****************************************************************************/
VOS_UINT32 AT_RegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFcPri;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* UART端口流控关闭时不注册流控点 */
    if ( (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
      && (AT_UART_FC_DTE_BY_DCE_NONE == pstUartCtx->stFlowCtrl.enDteByDce) )
    {
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemPsDataFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    /* 配置通道与RABID映射关系 */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;

    /* 根据网卡上最高优先级RAB QoS优先级来折算,优先级改变时，需要改变优先级 */
    /*  FC_PRI_3        有最低优先级的承载
        FC_PRI_4        有NONGBR承载
        FC_PRI_5        有GBR承载 */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFcPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFcPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFcPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
#if (FEATURE_ON == FEATURE_AT_HSUART)
    stRegFcPoint.pClrFunc           = (AT_CLIENT_TAB_HSUART_INDEX == ucIndex) ?
                                      AT_HSUART_StopFlowCtrl : AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc           = (AT_CLIENT_TAB_HSUART_INDEX == ucIndex) ?
                                      AT_HSUART_StartFlowCtrl : AT_MODEM_StartFlowCtrl;
#else
    stRegFcPoint.pClrFunc           = AT_MODEM_StopFlowCtrl;
    stRegFcPoint.pSetFunc            = AT_MODEM_StartFlowCtrl;

#endif
    stRegFcPoint.ulParam1           = (VOS_UINT32)g_alAtUdiHandle[ucIndex];
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;

    /* 注册流控点,需要分别注册MEM,CPU,CDS和GPRS。 */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint MEM Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint A CPU Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: FC RegPoint GPRS Failed.");
        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDMA;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegModemFCPoint: ERROR: reg CDMA point Failed.");
        return VOS_ERR;
    }
#endif

    /* 设置FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_TRUE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = enFcPri;
    /* 有一张网卡上多个RABID的情况，所以需要将多个RABID记录下来 */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulRabIdMask |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = enModemId;

    /* 勾流控消息 */
    AT_MNTN_TraceRegFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_PS);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DeRegModemPsDataFCPoint
 功能描述  : 去注册Modem端口PsData的流控点。
 输入参数  : VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
  2.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:修改注销NDIS流控点的逻辑
  3.日    期   : 2012年5月22日
    作    者   : f00179208
    修改内容   : DTS2012052205142, 增加VIDEO PHONE的流控
  4.日    期   : 2012年12月27日
    作    者   : l60609
    修改内容   : DSDA Phase II
  5.日    期   : 2013年04月17日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  6.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
  7.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: 增加流控使能开关

*****************************************************************************/
VOS_UINT32 AT_DeRegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;

    pstUartCtx = AT_GetUartCtxAddr();

    /* UART端口流控关闭时不注册流控点 */
    if ( (VOS_TRUE == AT_CheckHsUartUser(ucIndex))
        && (AT_UART_FC_DTE_BY_DCE_NONE == pstUartCtx->stFlowCtrl.enDteByDce) )
    {
        return VOS_ERR;
    }

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemPsDataFCPoint: Get modem id fail.");
        return VOS_ERR;
    }
    /* 删除流控模块映射关系 */
    FC_ChannelMapDelete(ucRabId, enModemId);

    ulRet = FC_DeRegPoint(FC_ID_MODEM, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegModemPsDataFCPoint: ERROR: FC DeRegPoint Failed.");
        return VOS_ERR;
    }

    /* 清除FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulUsed      = VOS_FALSE;
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enFcPri     = FC_PRI_BUTT;
    /* 有一张网卡上多个RABID的情况，所以需要将对应的RABID掩码清除掉 */
    g_stFcIdMaptoFcPri[FC_ID_MODEM].ulRabIdMask &= ~((VOS_UINT32)1 << ucRabId);
    g_stFcIdMaptoFcPri[FC_ID_MODEM].enModemId   = MODEM_ID_BUTT;

    /* 勾流控消息 */
    AT_MNTN_TraceDeregFcPoint(ucIndex, AT_FC_POINT_TYPE_MODEM_PS);

    return VOS_OK;
}
/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

/*****************************************************************************
 函 数 名  : AT_ChangeFCPoint
 功能描述  : 更改流控点优先级。
 输入参数  : TAF_CTRL_STRU                       *pstCtrl,
             FC_PRI_ENUM_UINT8                    enFCPri,
             FC_ID_ENUM_UINT8                     enFcId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数，更改流控点优先级
  2.日    期   : 2012年12月22日
    作    者   : l00227485
    修改内容   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 AT_ChangeFCPoint(
    TAF_CTRL_STRU                       *pstCtrl,
    FC_PRI_ENUM_UINT8                    enFCPri,
    FC_ID_ENUM_UINT8                     enFcId
)
{
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstCtrl->usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_ChangeFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    if (FC_ID_BUTT != enFcId)
    {
        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_MEM, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_CPU_A , enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_CDS, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }

        ulRet = FC_ChangePoint(enFcId, FC_POLICY_ID_GPRS, enFCPri, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ChangeFCPoint: ERROR: Change FC Point Failed.");
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_EnableHsicFlowCtl
 功能描述  : 使能Hsic流控
 输入参数  : VOS_UINT32                          ulUdiHdl,
             VOS_UINT32                          ulParam2
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_EnableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32  ulEnbflg = ACM_IOCTL_FLOW_CONTROL_ENABLE;

    if (0 != mdrv_udi_ioctl ((VOS_INT)ulUdiHdl, ACM_IOCTL_FLOW_CONTROL, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DisableHsicFlowCtl
 功能描述  : 去使能HSIC流控
 输入参数  : VOS_UINT32                          ulUdiHdl,
             VOS_UINT32                          ulParam2
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_DisableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT32  ulEnbflg = ACM_IOCTL_FLOW_CONTROL_DISABLE;

    if (0 != mdrv_udi_ioctl ((VOS_INT)ulUdiHdl, ACM_IOCTL_FLOW_CONTROL, (VOS_VOID*)(&ulEnbflg)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RegHsicFCPoint
 功能描述  : 注册HSIC端口流控点。
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
             FC_ID_ENUM_UINT8                     enFcId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2012年12月27日
    作    者   : L60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_UINT32 AT_RegHsicFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    FC_REG_POINT_STRU                   stRegFcPoint;
    VOS_UINT32                          ulRet;
    FC_PRI_ENUM_UINT8                   enFCPri;
    UDI_DEVICE_ID_E                     enDataChannelId;
    FC_ID_ENUM_UINT8                    enFcId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    PS_MEM_SET(&stRegFcPoint,0,sizeof(FC_REG_POINT_STRU));

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* 寻找配套的通道ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: data channel id is abnormal.");
        return VOS_ERR;
    }

    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            enFcId = FC_ID_DIPC_1;
            break;
        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            enFcId = FC_ID_DIPC_2;
            break;
        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            enFcId = FC_ID_DIPC_3;
            break;
        default:
            AT_WARN_LOG("AT_RegHsicFCPoint: WARNING: data channel id is abnormal.");
            return VOS_ERR;
    }

    /* 配置通道与RABID映射关系 */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;
    /* 根据网卡上最高优先级RAB QoS优先级来折算,优先级改变时，需要改变优先级 */
    /*  FC_PRI_3        有最低优先级的承载
        FC_PRI_4        有NONGBR承载
        FC_PRI_5        有GBR承载 */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_DisableHsicFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableHsicFlowCtl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)DIPC_GetDevHandleByRabId(pstEvent->ucRabId);
    stRegFcPoint.enModemId          = enModemId;
    stRegFcPoint.ulParam2           = enFcId;
    stRegFcPoint.pRstFunc           = AT_ResetFlowCtl;

    /* 注册流控点,需要分别注册MEM,CPU,CDS和GPRS。 */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg mem point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg a cpu point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg cds point Failed.");
        return VOS_ERR;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RegHsicFCPoint: ERROR: reg gprs point Failed.");
        return VOS_ERR;
    }

    /* 设置FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = enFCPri;
    /* 有一张网卡上多个RABID的情况，所以需要将多个RABID记录下来 */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  |= (1 << (pstEvent->ucRabId));
    g_stFcIdMaptoFcPri[enFcId].enModemId    = enModemId;

    /* 勾流控消息 */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_DeRegHsicFCPoint
 功能描述  : 去注册HSIC端口流控点。
 输入参数  : MN_CLIENT_ID_T                      usClientID,
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2012年12月27日
    作    者   : L60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
*****************************************************************************/
VOS_UINT32 AT_DeRegHsicFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    UDI_DEVICE_ID_E                     enDataChannelId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: Get modem id fail.");
        return VOS_ERR;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* 寻找配套的通道ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[pstEvent->ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: ERROR: data channel id is abnormal.");
        return VOS_ERR;
    }

    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            enFcId = FC_ID_DIPC_1;
            break;
        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            enFcId = FC_ID_DIPC_2;
            break;
        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            enFcId = FC_ID_DIPC_3;
            break;
        default:
            AT_WARN_LOG("AT_DeRegHsicFCPoint: WARNING: data channel id is abnormal.");
            return VOS_ERR;
    }

    /* 删除流控模块映射关系 */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: ERROR: de reg point Failed.");
        return VOS_ERR;
    }

    /* 清除FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
    /* 有一张网卡上多个RABID的情况，所以需要将对应的RABID掩码清除掉 */
    g_stFcIdMaptoFcPri[enFcId].ulRabIdMask &= ~((VOS_UINT32)1 << pstEvent->ucRabId);
    g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    /* 勾流控消息 */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);


    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_HsicPsRspEvtPdpActCnfProc
 功能描述  : pdp激活成功，HSIC AT通道处理
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换,直接处理激活事件上报和流控点注册
*****************************************************************************/
VOS_VOID  AT_HsicPsRspEvtPdpActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 向DIPC上报PDP已经激活事件 */
    AT_SndDipcPdpActInd(pstEvent->stCtrl.usClientId, pstEvent->ucCid, pstEvent->ucRabId);

    /* 向FC注册流控点 */
    AT_RegHsicFCPoint(pstEvent);

    /* 将指定CID的PDP的激活状态设置为激活态 */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstEvent->ucCid, VOS_TRUE);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    return;
}


/*****************************************************************************
 函 数 名  : AT_HsicPsRspEvtPdpDeactCnfProc
 功能描述  : pdp去激活响应，HSIC AT通道处理
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换,直接处理激活事件上报和流控点注册
*****************************************************************************/
VOS_VOID  AT_HsicPsRspEvtPdpDeactCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 向DIPC上报PDP已经去激活事件 */
    AT_SndDipcPdpDeactInd(pstEvent->ucRabId);

    /* 向FC去注册流控点 */
    AT_DeRegHsicFCPoint(pstEvent);

    /* 最后清除CID与数传通道的映射关系 */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstEvent->ucCid);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return;
}


/*****************************************************************************
 函 数 名  : AT_HsicPsRspEvtPdpDeactivatedProc
 功能描述  : pdp去激活指示，HSIC AT通道处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 修改PS域呼叫错误码处理

  3.日    期   : 2012年8月22日
    作    者   : y00213812
    修改内容   : DTS2012113005521:网侧发起去激活，AT收到消息后错误的清除当前
                 HSIC通道的状态，导致用户无法收到回应。删除AT_STOP_TIMER_CMD_READY

  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换,直接处理激活事件上报和流控点注册

*****************************************************************************/
VOS_VOID  AT_HsicPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    VOS_UINT16  usLength;

    usLength    = 0;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 向DIPC上报PDP已经去激活事件 */
    AT_SndDipcPdpDeactInd(pstEvent->ucRabId);

    /* 向FC去注册流控点 */
    AT_DeRegHsicFCPoint(pstEvent);

    /* 最后清除CID与数传通道的映射关系 */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstEvent->ucCid);
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);

            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);

            break;

        case TAF_PDP_IPV4V6:

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);

            break;
#endif

        default:
            AT_ERR_LOG("AT_HsicPsRspEvtPdpDeactivatedProc:ERROR: PDP type is invalid!");
            return;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/* Modified by l60609 for AP适配项目 ，2012-09-10 Begin */
/*****************************************************************************
 函 数 名  : AT_SendRnicCgactIpv4ActInd
 功能描述  : AT+CGACT拨号成功给RNIC发PDP激活消息
 输入参数  : VOS_UINT8                           ucRabId,
             VOS_UINT8                           ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_SendRnicCgactIpv4ActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    /* 申请AT_RNIC_IPV4_PDP_ACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_SendRnicCgactIpv4ActInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* 填写消息体 */
    pstMsg->ucRabId         = ucRabId;
    pstMsg->ucRmNetId       = ucRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_SendRnicCgactIpv4ActInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : AT_ProcAppPsRspEvtPdpActCnf
 功能描述  : 处理RIL通过AT+CGACT发起的PDP激活请求
 输入参数  : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月2日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月18日
    作    者   : l60609
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_VOID  AT_ProcAppPsRspEvtPdpActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;

    ucRmNetId = 0;

    /* 获取网卡Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* 获取网卡Id失败，即不在约定的应用CID范围内，不支持数传 */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 获取FcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    PS_MEM_SET(&stFCPriOrg, 0, sizeof(stFCPriOrg));

    ulRslt = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulRslt)
    {
        /* 如果FC ID未注册，那么注册该流控点。*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* 注册APP拨号使用的流控点 */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, ucRmNetId);
        }
        else
        {
            /* APP拨号只使用最低的流控QOS优先级FC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_ProcAppPsRspEvtPdpActCnf: No need to change the default QOS priority.");
        }
    }

    /* 目前APP只支持AT+CGACT发起IPV4拨号 */
    AT_SendRnicCgactIpv4ActInd(pstEvent->ucRabId, ucRmNetId);

    return;
}

/*****************************************************************************
 函 数 名  : AT_ProcAppPsRspEvtPdpDeActCnf
 功能描述  : 处理RIL通过AT+CGACT发起的PDP去激活请求
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月2日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月18日
    作    者   : l60609
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_VOID  AT_ProcAppPsRspEvtPdpDeActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulRslt;

    ucRmNetId = 0;

    /* 获取网卡Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* 获取网卡Id失败，即不在约定的应用CID范围内，不支持数传 */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 获取FcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    /* 通知RNIC PDP去激活成功 */
    AT_SendRnicPdpDeactInd(pstEvent->ucRabId, ucRmNetId);

    /* 去注册APP拨号使用的流控点(默认使用网卡1) */
    AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);

    return;
}
/* Modified by l60609 for AP适配项目 ，2012-09-10 End */
/*****************************************************************************
 函 数 名  : AT_ProcAppPsRspEvtPdpDeactivated
 功能描述  : APP通过AT+CGACT发起PDP激活，网侧发起PDP去激活
 输入参数  : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_ProcAppPsRspEvtPdpDeactivated(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
)
{
    VOS_UINT16                          usLength;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT32                          ulRslt;

    usLength    = 0;
    ucRmNetId   = 0;

    /* APP拨号默认使用NDIS网卡1的流控点 */
    enDefaultFcId = FC_ID_NIC_1;

    /* 获取网卡Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* 获取网卡Id失败，即不在约定的应用CID范围内，不支持数传 */
    if (VOS_OK == ulRslt)
    {
        /* 通知RNIC PDP去激活成功 */
        AT_SendRnicPdpDeactInd(pstEvent->ucRabId, ucRmNetId);

        /* 去注册APP拨号使用的流控点(默认使用网卡1) */
        AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);
    }

    switch (pstEvent->enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV4",
                                        gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                        "%s^DEND:%d,%d,\"%s\"%s",
                                        gaucAtCrLf,
                                        pstEvent->ucCid,
                                        pstEvent->enCause,
                                        "IPV6",
                                        gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_ProcAppPsRspEvtPdpDeactivated:ERROR: PDP type is invalid!");
            return;
    }

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_NotifyFcWhenAppPdpModify
 功能描述  : 当发生PDP MODIFY(UE发起或网侧发起)时，向FC指示修改流控点
 输入参数  : VOS_UINT8                           ucIndex,
             TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月17日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_NotifyFcWhenAppPdpModify(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucRmNetId;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    ucRmNetId = 0;

    /* 获取网卡Id */
    ulRslt = AT_PS_GetRmNetIdByCid(ucIndex, pstEvent->ucCid, &ucRmNetId);

    /* 获取网卡Id失败，即不在约定的应用CID范围内，不支持数传 */
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 获取FcId */
    enDefaultFcId = g_astPsRmNetIdTab[ucRmNetId].enFcId;

    AT_NotifyFcWhenPdpModify(pstEvent, enDefaultFcId);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_AddIpAddrRabIdMap
 功能描述  : 添加IP与RABID的映射
 输入参数  : usClientId - 客户端ID
             pstEvent   - PS域呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年5月9日
    作    者   : A00165503
    修改内容   : DTS2014050900349: IP地址转换错误
*****************************************************************************/
VOS_VOID AT_PS_AddIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    ulIpAddr      = 0;

    if (!AT_PS_IS_RABID_VALID(pstEvent->ucRabId))
    {
        return;
    }

    if (pstEvent->bitOpPdpAddr)
    {
        ulIpAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);
        pstPsModemCtx->aulIpAddrRabIdMap[pstEvent->ucRabId - AT_PS_RABID_OFFSET] = ulIpAddr;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_DeleteIpAddrRabIdMap
 功能描述  : 删除IP与RABID的映射
 输入参数  : usClientId - 客户端ID
             pstEvent   - PS域呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_DeleteIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    if (!AT_PS_IS_RABID_VALID(pstEvent->ucRabId))
    {
        return;
    }

    pstPsModemCtx->aulIpAddrRabIdMap[pstEvent->ucRabId - AT_PS_RABID_OFFSET] = 0;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetIpAddrByRabId
 功能描述  : 根据RABID获取承载对应的IP地址
 输入参数  : usClientId - 客户端ID
             ucRabId    - RABID [5,15]
 输出参数  : 无
 返 回 值  : ulIpAddr   - IP地址(主机序)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_GetIpAddrByRabId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucRabId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);
    ulIpAddr      = 0;

    if (AT_PS_IS_RABID_VALID(ucRabId))
    {
        ulIpAddr = pstPsModemCtx->aulIpAddrRabIdMap[ucRabId - AT_PS_RABID_OFFSET];
    }

    return ulIpAddr;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetRmNetIdFromCid
 功能描述  : 根据Client Id和Cid获取对应的网卡Id
 输入参数  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucCid,
             VOS_UINT8                          *pucRmNetId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_GetRmNetIdByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucRmNetId
)
{
    VOS_UINT8                           i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    if (VOS_NULL_PTR == pucRmNetId)
    {
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient((VOS_UINT8)usClientId, &enModemId);

    /* 获取modem id失败 */
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    for (i = 0; i < (sizeof(g_astPsRmNetIdTab)/sizeof(AT_PS_RMNET_ID_TAB)); i++)
    {
        if ((enModemId == g_astPsRmNetIdTab[i].enModemId)
         && (ucCid == g_astPsRmNetIdTab[i].ucUsrCid))
        {
            *pucRmNetId = i;
            break;
        }
    }

    /* 在映射表中未找到 */
    if (i >= sizeof(g_astPsRmNetIdTab)/sizeof(AT_PS_RMNET_ID_TAB))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_ResetFlowCtl
 功能描述  : 复位流控
 输入参数  : ulParam1      不关注
             ulParam2      FCID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_ResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT8                           ucRabIdIndex;
    VOS_UINT32                          ulRabIdMask;
    VOS_UINT32                          ulRet;
    FC_ID_ENUM_UINT8                    enFcId;
    MODEM_ID_ENUM_UINT16                enModemId;

    enFcId      = (FC_ID_ENUM_UINT8)ulParam2;
    enModemId   = g_stFcIdMaptoFcPri[enFcId].enModemId;
    ulRabIdMask = g_stFcIdMaptoFcPri[enFcId].ulRabIdMask;

    if (VOS_TRUE == g_stFcIdMaptoFcPri[enFcId].ulUsed)
    {
        for (ucRabIdIndex = AT_PS_MIN_RABID; ucRabIdIndex <= AT_PS_MAX_RABID; ucRabIdIndex++)
        {
            if (1 == ((ulRabIdMask >> ucRabIdIndex) & 0x1))
            {
                FC_ChannelMapDelete(ucRabIdIndex, enModemId);
            }
        }

        ulRet = FC_DeRegPoint(enFcId, enModemId);
        if (VOS_OK != ulRet)
        {
            AT_ERR_LOG("AT_ResetFlowCtl: ERROR: DeReg point failed.");
            return VOS_ERR;
        }

        g_stFcIdMaptoFcPri[enFcId].ulUsed       = VOS_FALSE;
        g_stFcIdMaptoFcPri[enFcId].enFcPri      = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[enFcId].ulRabIdMask  = 0;
        g_stFcIdMaptoFcPri[enFcId].enModemId    = MODEM_ID_BUTT;

    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_PS_GetRnicRmNetIdFromChDataValue
 功能描述  : 根据CHDATA设置的通道号获取对应的RNIC网卡ID
 输入参数  : VOS_UINT8                           ucIndex
             AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId
             RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : L60609
    修改内容   : 新生成函数

  2.日    期   : 2015年5月28日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_UINT32 AT_PS_GetRnicRmNetIdFromChDataValue(
    VOS_UINT8                           ucIndex,
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId,
    RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
)
{
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CHDATA_RNIC_RMNET_ID_STRU       *pstChdataRnicRmNetIdTab;
    VOS_UINT32                          ulRslt;

    pstChdataRnicRmNetIdTab = AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR();

    *penRnicRmNetId = RNIC_RMNET_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /*
        MODEM0 RNIC ID 为 0~2， CHDATA的值为 1~3
        MODEM1 RNIC ID 为 3~4， CHDATA的值为 4~5
        MODEM2 RNIC ID 为 6~7， CHDATA的值为 6~7
    */

    if (MODEM_ID_0 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_1)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_3))
        {
            return VOS_ERR;
        }
    }

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    else if (MODEM_ID_1 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_4)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_5))
        {
            return VOS_ERR;
        }
    }
#if (MULTI_MODEM_NUMBER == 3)
    else if (MODEM_ID_2 == enModemId)
    {
        if ((enDataChannelId < AT_CH_DATA_CHANNEL_ID_6)
         || (enDataChannelId > AT_CH_DATA_CHANNEL_ID_7))
        {
            return VOS_ERR;
        }
    }
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#endif
    else
    {
        return VOS_ERR;
    }

    /*  以上判断已能保证enDataChannelId的有效性，所以RM NET ID一定能在表中找到 */
    for (i = 0; i < AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE() ; i++)
    {
        if (enDataChannelId == pstChdataRnicRmNetIdTab[i].enChdataValue)
        {
            *penRnicRmNetId = pstChdataRnicRmNetIdTab[i].enRnicRmNetId;
            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetChDataValueFromRnicRmNetId
 功能描述  : 根据对应的RNIC网卡ID获取CHDATA设置的通道号
 输入参数  : RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId
             AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_GetChDataValueFromRnicRmNetId(
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId,
    AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
)
{
    VOS_UINT32                          i;
    AT_CHDATA_RNIC_RMNET_ID_STRU       *pstChdataRnicRmNetIdTab;

    pstChdataRnicRmNetIdTab = AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR();

    for (i = 0; i < AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE() ; i++)
    {
        if (enRnicRmNetId == pstChdataRnicRmNetIdTab[i].enRnicRmNetId)
        {
            *penDataChannelId = pstChdataRnicRmNetIdTab[i].enChdataValue;
            break;
        }
    }

    if (i >= AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE())
    {
        return VOS_ERR;
    }


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetFcIdByUdiDeviceId
 功能描述  : 通过DIPC通道ID获得FCID
 输入参数  : UDI_DEVICE_ID                       enDataChannelId
 输出参数  : 无
 返 回 值  : FC_ID_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月2日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdByUdiDeviceId(
    UDI_DEVICE_ID_E                     enDataChannelId
)
{
    switch ( enDataChannelId )
    {
        case UDI_ACM_HSIC_ACM1_ID:
        case UDI_NCM_HSIC_NCM0_ID:
            return FC_ID_DIPC_1;

        case UDI_ACM_HSIC_ACM3_ID:
        case UDI_NCM_HSIC_NCM1_ID:
            return FC_ID_DIPC_2;

        case UDI_ACM_HSIC_ACM5_ID:
        case UDI_NCM_HSIC_NCM2_ID:
            return FC_ID_DIPC_3;

        default:
            AT_WARN_LOG("AT_PS_GetFcIdByUdiDeviceId: WARNING: data channel id is abnormal.");
            return FC_ID_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : AT_PS_GetFcIdFromRnicByRmNetId
 功能描述  : 获取RNIC网卡的FCID
 输入参数  : VOS_UINT32                          ulRmNetId
 输出参数  : 无
 返 回 值  : FC_ID_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月2日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdFromRnicByRmNetId(
    VOS_UINT32                          ulRmNetId
)
{
    switch (ulRmNetId)
    {
        case RNIC_RMNET_ID_0:
            return FC_ID_NIC_1;

        case RNIC_RMNET_ID_1:
            return FC_ID_NIC_2;

        case RNIC_RMNET_ID_2:
            return FC_ID_NIC_3;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        case RNIC_RMNET_ID_3:
            return FC_ID_NIC_4;

        case RNIC_RMNET_ID_4:
            return FC_ID_NIC_5;
#if (MULTI_MODEM_NUMBER == 3)
        case RNIC_RMNET_ID_5:
            return FC_ID_NIC_6;

        case RNIC_RMNET_ID_6:
            return FC_ID_NIC_7;
#endif
#endif

        default:
            AT_WARN_LOG("AT_PS_GetFcIdFromRnidRmNetId: WARNING: data channel id is abnormal.");
            return FC_ID_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : AT_PS_GetCallEntity
 功能描述  : 获取PS域呼叫实体指针
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : AT_PS_CALL_ENTITY_STRU *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
AT_PS_CALL_ENTITY_STRU* AT_PS_GetCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astCallEntity[ucCallId]);
}

/*****************************************************************************
 函 数 名  : AT_PS_GetUserInfo
 功能描述  : 获取PS域呼叫用户信息
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : AT_PS_USER_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
AT_PS_USER_INFO_STRU* AT_PS_GetUserInfo(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astCallEntity[ucCallId].stUserInfo);
}

/*****************************************************************************
 函 数 名  : AT_PS_GetDataChanlCfg
 功能描述  : 获取数传通道配置信息
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : AT_PS_DATA_CHANL_CFG_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
AT_PS_DATA_CHANL_CFG_STRU* AT_PS_GetDataChanlCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU                  *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return &(pstPsModemCtx->astChannelCfg[ucCid]);
}
/*****************************************************************************
 函 数 名  : AT_PS_TransCidToCallId
 功能描述  : 获取与该CID关联的PS实体索引
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 AT_PS_TransCidToCallId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    /* cid 无效值 */
    if (ucCid > TAF_MAX_CID)
    {
        return AT_PS_CALL_INVALID_CALLID;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    return pstPsModemCtx->aucCidToIndexTbl[ucCid];
}

/*****************************************************************************
 函 数 名  : AT_PS_IsCallIdValid
 功能描述  : PS域呼叫实体索引是否有效
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_IsCallIdValid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    if (ucCallId >= AT_PS_MAX_CALL_NUM)
    {
        return VOS_FALSE;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

#if (FEATURE_ON == FEATURE_IPV6)
    if ((AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv4Cid)
     && (AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv6Cid))
    {
        return VOS_FALSE;
    }
#else
    if (AT_PS_CALL_INVALID_CID == pstPsModemCtx->astCallEntity[ucCallId].ucIpv4Cid)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : AT_PS_AssignCallIdToCid
 功能描述  : 配置cid和callid的映射表
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
             VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_AssignCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucCallId
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->aucCidToIndexTbl[ucCid] = ucCallId;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_FreeCallIdToCid
 功能描述  : 清除cid和callid的映射表
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_FreeCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    pstPsModemCtx->aucCidToIndexTbl[ucCid] = AT_PS_CALL_INVALID_CALLID;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SetCid2CurrCall
 功能描述  : 设置当前呼叫CID
 输入参数  : usClientId - 端口ID
             ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
             ucCid     - CID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_SetCid2CurrCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucCid
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            pstCallEntity->ucIpv4Cid = ucCid;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            pstCallEntity->ucIpv6Cid = ucCid;
            break;

        case TAF_PDP_IPV4V6:
            pstCallEntity->ucIpv4Cid = ucCid;
            pstCallEntity->ucIpv6Cid = ucCid;
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_SetCid2CurrCall: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetCidByCallType
 功能描述  : 获取呼叫类型对应的CID
 输入参数  : usClientId - 端口ID
             ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
 输出参数  : 无
 返 回 值  : VOS_UINT8 - CID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 AT_PS_GetCidByCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            ucCid = pstCallEntity->ucIpv4Cid;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            ucCid = pstCallEntity->ucIpv6Cid;
            break;
#endif

        default:
            ucCid = AT_PS_CALL_INVALID_CID;
            AT_ERR_LOG("AT_PS_SetCid2CurrCall: PDP type is invalid!");
            break;
    }

    return ucCid;
}

/*****************************************************************************
 函 数 名  : AT_PS_SetCallStateByType
 功能描述  : 根据PDP类型设置呼叫状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
             enPdpType  - PDP类型(IPv4, IPv6 or IPv4v6)
             enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_SetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            pstCallEntity->enIpv4State = enPdpState;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            pstCallEntity->enIpv6State = enPdpState;
            break;

        case TAF_PDP_IPV4V6:
            pstCallEntity->enIpv4State = enPdpState;
            pstCallEntity->enIpv6State = enPdpState;
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_SetCallStateByType: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetCallStateByType
 功能描述  : 根据PDP类型获取呼叫状态, PDP类型必须IPv4或IPv6
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
             enPdpType  - PDP类型(IPv4 or IPv6)
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PDP_STATE_ENUM_U8                enPdpState;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            enPdpState = pstCallEntity->enIpv4State;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            enPdpState = pstCallEntity->enIpv6State;
            break;
#endif

        default:
            enPdpState = AT_PDP_STATE_IDLE;
            AT_ERR_LOG("AT_PS_GetCallStateByType: PDP type is invalid!");
            break;
    }

    return enPdpState;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetCallStateByCid
 功能描述  : 根据CID获取呼叫状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
             ucCid      - CID
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCid
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if (pstCallEntity->ucIpv4Cid == ucCid)
    {
        return pstCallEntity->enIpv4State;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (pstCallEntity->ucIpv6Cid == ucCid)
    {
        return pstCallEntity->enIpv6State;
    }
#endif

    return AT_PDP_STATE_IDLE;
}

/*****************************************************************************
 函 数 名  : AT_PS_IsUsrDialTypeDualStack
 功能描述  : 判断是否双栈拨号
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  AT_PS_IsUsrDialTypeDualStack(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if (TAF_PDP_IPV4V6 == pstCallEntity->stUsrDialParam.enPdpType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_PS_ReportDCONN
 功能描述  : 上报连接状态^DCONN
 输入参数  : ucCid          - CID
             ucPortIndex    - 端口号
             enPdpType      - PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : Y00213812
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ReportDCONN(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DCONN:%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_ReportDCONN: PDP type is invalid in ^DCONN.");
            return;
    }

    At_SendResultData(ucPortIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ReportDend
 功能描述  : 上报连接状态^DEND
 输入参数  : ucCid       - 用户使用的CID
             ucPortIndex - 用户使用的端口索引(Client ID)
             enPdpType   - PDP类型
             enCause     - 错误码
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : Y00213812
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ReportDEND(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);

            break;
#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            break;

        case TAF_PDP_IPV4V6:
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV4\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s^DEND:%d,%d,\"IPV6\"%s",
                                               gaucAtCrLf,
                                               ucCid,
                                               enCause,
                                               gaucAtCrLf);
            break;
#endif

        default:
            AT_ERR_LOG("AT_PS_ReportDEND: PDP type is invalid in ^DEND.");
            return;
    }

    At_SendResultData(ucPortIndex, pgucAtSndCodeAddr, usLength);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetRptConnResultFunc
 功能描述  : 获取连接建立结果上报函数指针
 输入参数  : ucUsrType - 用户类型
 输出参数  : 无
 返 回 值  : AT_PS_RPT_CONN_RSLT_FUNC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
AT_PS_RPT_CONN_RSLT_FUNC AT_PS_GetRptConnResultFunc(AT_USER_TYPE ucUsrType)
{
    AT_PS_REPORT_CONN_RESULT_STRU      *pstRptConnRsltFuncTblPtr = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstRptConnRsltFuncTblPtr = AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_PTR();

    /* 用户类型匹配 */
    for (ulCnt = 0; ulCnt < AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ucUsrType == pstRptConnRsltFuncTblPtr[ulCnt].ucUsrType)
        {
            pRptConnRsltFunc = pstRptConnRsltFuncTblPtr[ulCnt].pRptConnRsltFunc;
            break;
        }
    }

    return pRptConnRsltFunc;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetRptEndResultFunc
 功能描述  : 获取连接断开结果上报函数指针
 输入参数  : ucUsrType - 用户类型
 输出参数  : 无
 返 回 值  : AT_PS_RPT_END_RSLT_FUNC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
AT_PS_RPT_END_RSLT_FUNC AT_PS_GetRptEndResultFunc(AT_USER_TYPE ucUsrType)
{
    AT_PS_REPORT_END_RESULT_STRU       *pstRptEndRsltFuncTblPtr = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc         = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstRptEndRsltFuncTblPtr = AT_PS_GET_RPT_END_RSLT_FUNC_TBL_PTR();

    /* 用户类型匹配 */
    for (ulCnt = 0; ulCnt < AT_PS_GET_RPT_END_RSLT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (ucUsrType == pstRptEndRsltFuncTblPtr[ulCnt].ucUsrType)
        {
            pRptEndRsltFunc = pstRptEndRsltFuncTblPtr[ulCnt].pRptEndRsltFunc;
            break;
        }
    }

    return pRptEndRsltFunc;
}

/*****************************************************************************
 函 数 名  : AT_PS_PdpAddrProc
 功能描述  : 处理IPv4地址参数
 输入参数  : ucCallId      - 呼叫实体索引
             pstDhcpConfig - DCHP信息
             pstEvent      - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
  2.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2015031000157, 新增第三个p-cscf地址
*****************************************************************************/
VOS_VOID AT_PS_PdpAddrProc(
    VOS_UINT8                           ucCallId,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                 *pstDialPara = VOS_NULL_PTR;
    VOS_UINT32                          ulIpAddr;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    pstDialPara   = &pstCallEntity->stUsrDialParam;
    ulIpAddr      = 0;

    pstCallEntity->stIpv4DhcpInfo.ucRabId                 = pstEvent->ucRabId;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr              = pstDhcpConfig->ulIPAddr;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay           = pstDhcpConfig->ulGateWay;
    pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask           = pstDhcpConfig->ulSubNetMask;

    /* 如果用户设置了主DNS，就使用用户设置的DNS，网络返回的DNS不使用 */
    if (VOS_TRUE == pstDialPara->ulPrimIPv4DNSValidFlag)
    {
        if (AT_FAILURE == AT_LenStr2IpAddr(pstDialPara->aucPrimIPv4DNSAddr,
                                           (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns     = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS       = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulPrimDNS)
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns = VOS_TRUE;
            pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS   = pstDhcpConfig->ulPrimDNS;
        }
        else
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriDns = VOS_FALSE;
        }
    }

    /* 如果用户设置了副DNS，就使用用户设置的DNS，网络返回的DNS不使用 */
    if (VOS_TRUE == pstDialPara->ulSndIPv4DNSValidFlag)
    {
        if (AT_FAILURE == AT_LenStr2IpAddr(pstDialPara->aucSndIPv4DNSAddr,
                                           (VOS_UINT8*)&ulIpAddr))
        {
            ulIpAddr = 0;
        }

        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns     = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS        = VOS_NTOHL(ulIpAddr);
    }
    else
    {
        if (0 != pstDhcpConfig->ulSndDNS)
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns = VOS_TRUE;
            pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS    = pstDhcpConfig->ulSndDNS;
        }
        else
        {
            pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecDns = VOS_FALSE;
        }
    }

    pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriWINNS       = VOS_FALSE;
    pstCallEntity->stIpv4DhcpInfo.bitOpIpv4SecWINNS       = VOS_FALSE;

    /* 获取主PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpPrimPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4PriPCSCF   = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimPCSCF     = AT_GetLanAddr32(pstEvent->stPcscf.aucPrimPcscfAddr);
    }

    /* 获取副PCSCF地址 */
    if (VOS_TRUE == pstEvent->stPcscf.bitOpSecPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4Secpcscf   = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4SecPCSCF      = AT_GetLanAddr32(pstEvent->stPcscf.aucSecPcscfAddr);
    }

    if (VOS_TRUE == pstEvent->stPcscf.bitOpThiPcscfAddr)
    {
        /* IP地址的有效性由APS保证 */
        pstCallEntity->stIpv4DhcpInfo.bitOpIpv4Thipcscf   = VOS_TRUE;
        pstCallEntity->stIpv4DhcpInfo.ulIpv4ThiPCSCF      = AT_GetLanAddr32(pstEvent->stPcscf.aucThiPcscfAddr);
    }

    return;
}

/******************************************************************************
 函 数 名  : AT_PS_ProcConnInd
 功能描述  : 需要解析激活上下文，设置DHCP服务器
 输入参数  : ucCallId - 呼叫实体索引
             pstEvent - 事件信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

******************************************************************************/
VOS_VOID AT_PS_ProcConnInd(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_DHCP_SETUP_PARAM_ST              stParam;
    AT_DHCP_CONFIG_STRU                 stConfig;

    PS_MEM_SET(&stParam, 0, sizeof(AT_DHCP_SETUP_PARAM_ST));
    PS_MEM_SET(&stConfig, 0, sizeof(AT_DHCP_CONFIG_STRU));

    /* 如果PS事件有DNS地址，则记录DNS地址*/
    if (pstEvent->stDns.bitOpPrimDnsAddr)
    {
        stParam.ulPrimDNS = AT_GetLanAddr32(pstEvent->stDns.aucPrimDnsAddr);
    }

    if (pstEvent->stDns.bitOpSecDnsAddr)
    {
        stParam.ulSndDNS = AT_GetLanAddr32(pstEvent->stDns.aucSecDnsAddr);
    }

    /* 记录IP地址*/
    stParam.ulIPAddr = AT_GetLanAddr32(pstEvent->stPdpAddr.aucIpv4Addr);

    if (VOS_ERR == AT_DHCPServerSetUp(&stParam, &stConfig))
    {
        AT_ERR_LOG("AT_PS_ProcConnInd : ERROR AT_DHCPServerSetUp Error!" );
    }
    else
    {
        /* 处理IPv4地址参数 */
        AT_PS_PdpAddrProc(ucCallId, &stConfig, pstEvent);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndCallConnectedResult
 功能描述  : 连接建立状态上报
 输入参数  : ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : Y00213812
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_SndCallConnectedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUsrInfo          = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc    = VOS_NULL_PTR;

    /* 获取当前呼叫用户信息 */
    pstUsrInfo       = AT_PS_GetUserInfo(usClientId, ucCallId);

    /* 在事件处理表中查找处理函数 */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstUsrInfo->ucUsrType);

    /* 如果处理函数存在则调用 */
    if (VOS_NULL_PTR != pRptConnRsltFunc)
    {
        pRptConnRsltFunc(pstUsrInfo->ucUsrCid,
                         pstUsrInfo->enPortIndex,
                         enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_SndCallConnectedResult:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndCallEndedResult
 功能描述  : 上报连接状态^DEND
 输入参数  : ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
             enCause   - 错误码
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : Y00213812
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_SndCallEndedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    AT_PS_USER_INFO_STRU               *pstUsrInfo      = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;

    /* 获取当前呼叫用户信息 */
    pstUsrInfo      = AT_PS_GetUserInfo(usClientId, ucCallId);

    /* 在事件处理表中查找处理函数 */
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstUsrInfo->ucUsrType);

    /* 如果处理函数存在则调用 */
    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(pstUsrInfo->ucUsrCid,
                        pstUsrInfo->enPortIndex,
                        enPdpType,
                        enCause);
    }
    else
    {
        AT_ERR_LOG("AT_PS_SndCallEndedResult:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GenCallDialParam
 功能描述  : 生成发起PS域呼叫使用的拨号参数
 输入参数  : pstUsrDialParam  - 用户参数
             ucCid            - CID
             enPdpType        - PDP类型
 输出参数  : pstCallDialParam - 呼叫参数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_GenCallDialParam(
    AT_DIAL_PARAM_STRU                 *pstCallDialParam,
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* 获取用户拨号参数 */
    *pstCallDialParam           = *pstUsrDialParam;

    /* 刷新CID和PDP类型 */
    pstCallDialParam->ucCid     = ucCid;
    pstCallDialParam->enPdpType = enPdpType;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_RegFCPoint
 功能描述  : 注册流控点
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_RegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_REG_FC_POINT_STRU            *pstRegFcPointFuncTblPtr = VOS_NULL_PTR;
    AT_PS_REG_FC_POINT_FUNC             pRegFcPointFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo             = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstRegFcPointFuncTblPtr = AT_PS_GET_REG_FC_POINT_FUNC_TBL_PTR();

    /* 在事件处理表中查找处理函数 */
    for (ulCnt = 0; ulCnt < AT_PS_GET_REG_FC_POINT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstRegFcPointFuncTblPtr[ulCnt].ucUsrType)
        {
            /* 类型匹配 */
            pRegFcPointFunc = pstRegFcPointFuncTblPtr[ulCnt].pRegFcPoint;
            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if (VOS_NULL_PTR != pRegFcPointFunc)
    {
        pRegFcPointFunc(pstUserInfo->ucUsrCid, pstEvent);
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegFCPoint:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_DeRegFCPoint
 功能描述  : 去注册流控点
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_DeRegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_DEREG_FC_POINT_STRU          *pstDeRegFcPointFuncTblPtr = VOS_NULL_PTR;
    AT_PS_DEREG_FC_POINT_FUNC           pDeRegFcPointFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo               = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstDeRegFcPointFuncTblPtr = AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_PTR();

    /* 在事件处理表中查找处理函数 */
    for (ulCnt = 0; ulCnt < AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstDeRegFcPointFuncTblPtr[ulCnt].ucUsrType)
        {
            /* 类型匹配 */
            pDeRegFcPointFunc = pstDeRegFcPointFuncTblPtr[ulCnt].pDeRegFcPoint;
            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if (VOS_NULL_PTR != pDeRegFcPointFunc)
    {
        pDeRegFcPointFunc(pstUserInfo->ucUsrCid, pstEvent);
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegFCPoint:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndDipcPdpActBearerTypeInd
 功能描述  : AT向DIPC通道发送PDP激活消息
 输入参数  : ucCid          ----  CID
             pstEvent       ----  PsCallEventInfo
             enBearerType   ----  BearerType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActBearerTypeInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
)
{
    AT_DIPC_PDP_ACT_STRU               *pstAtDipcPdpAct = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ulLength        = sizeof( AT_DIPC_PDP_ACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpAct = ( AT_DIPC_PDP_ACT_STRU *)PS_ALLOC_MSG( WUEPS_PID_AT, ulLength );

    if (VOS_NULL_PTR == pstAtDipcPdpAct)
    {
        /*打印出错信息---申请消息包失败:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpActInd:ERROR:Allocates a message packet for AT_DIPC_PDP_ACT_STRU FAIL!" );
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /*填写消息头:*/
    pstAtDipcPdpAct->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpAct->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpAct->ulLength        = ulLength;
    /*填写消息体:*/
    pstAtDipcPdpAct->enMsgType       = ID_AT_DIPC_PDP_ACT_IND;
    pstAtDipcPdpAct->ucRabId         = pstEvent->ucRabId;
    pstAtDipcPdpAct->enBearerType    = enBearerType;
    pstAtDipcPdpAct->enUdiDevId      = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    /*发送该消息:*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstAtDipcPdpAct))
    {
        /*打印警告信息---发送消息失败:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpActInd:WARNING:SEND AT_DIPC_PDP_ACT_STRU msg FAIL!" );
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndDipcPdpActInd
 功能描述  : AT向DIPC通道发送PDP激活消息
 输入参数  : usClientId     ----  CLIENT ID
             ucCid          ----  CID
             ucRabId        ----  RABID
             enBearerType   ----  BearerType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* 向DIPC上报PDP IPv4已经激活事件 */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndDipcPdpActBearerTypeInd(ucCid,
                                         pstEvent,
                                         DIPC_BEARER_TYPE_IPV4);
    }

    /* 向DIPC上报PDP IPv6已经激活事件 */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndDipcPdpActBearerTypeInd(ucCid,
                                         pstEvent,
                                         DIPC_BEARER_TYPE_IPV6);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndDipcPdpDeactBearerTypeInd
 功能描述  : AT向DIPC通道发送PDP去激活消息
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactBearerTypeInd(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
)
{
    AT_DIPC_PDP_DEACT_STRU             *pstAtDipcPdpDeact = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength          = sizeof( AT_DIPC_PDP_DEACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpDeact = (AT_DIPC_PDP_DEACT_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstAtDipcPdpDeact)
    {
        /*打印出错信息---申请消息包失败:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpDeactInd:ERROR:Allocates a message packet for AT_DIPC_PDP_DEACT_STRU FAIL!" );
        return;
    }

    /*填写消息头:*/
    pstAtDipcPdpDeact->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpDeact->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpDeact->ulLength        = ulLength;
    /*填写消息体:*/
    pstAtDipcPdpDeact->enMsgType       = ID_AT_DIPC_PDP_REL_IND;
    pstAtDipcPdpDeact->ucRabId         = pstEvent->ucRabId;
    pstAtDipcPdpDeact->enBearerType    = enBearerType;

    /*发送该消息:*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstAtDipcPdpDeact))
    {
        /*打印警告信息---发送消息失败:*/
        AT_WARN_LOG( "AT_PS_SndDipcPdpDeactInd:WARNING:SEND AT_DIPC_PDP_DEACT_STRU msg FAIL!" );
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndDipcPdpDeactInd
 功能描述  : AT向DIPC通道发送PDP去激活消息
 输入参数  : VOS_UINT8                           ucCid,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月17日
    作    者   : L47619
    修改内容   : 新生成函数

  2.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : C50 IPv6 项目
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* 向DIPC上报PDP IPv4已经去激活事件 */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndDipcPdpDeactBearerTypeInd(pstEvent,
                                           DIPC_BEARER_TYPE_IPV4);
    }

    /* 向DIPC上报PDP IPv6已经去激活事件 */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndDipcPdpDeactBearerTypeInd(pstEvent,
                                           DIPC_BEARER_TYPE_IPV6);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndRnicIpv4PdpActInd
 功能描述  : 给RNIC发送PDP激活事件, IPv4类型
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv4PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pstEvent
)
{
    AT_RNIC_IPV4_PDP_ACT_IND_STRU      *pstMsg;

    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* 判断网卡的有效性 */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return;
    }

    /* 申请AT_RNIC_IPV4_PDP_ACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_IPV4_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv4PdpActInd: alloc msg fail!");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV4_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV4_PDP_ACT_IND;

    /* 填写rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* 填写rmnet id，从chdata设置中获取 */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;



    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv4PdpActInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndRnicIpv6PdpActInd
 功能描述  : 给RNIC发送PDP激活事件, IPv6类型
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv6PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_RNIC_IPV6_PDP_ACT_IND_STRU      *pstMsg;

    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* 判断网卡的有效性 */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return;
    }

    /* 申请AT_RNIC_IPV6_PDP_ACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_IPV6_PDP_ACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv6PdpActInd: alloc msg fail!");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_IPV6_PDP_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_IPV6_PDP_ACT_IND;

    /* 填写rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* 填写rmnet id，从chdata设置中获取 */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;



    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_PS_SndRnicIpv6PdpActInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SndRnicPdpActInd
 功能描述  : 根据PDP类型给RNIC发送激活消息
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_SndRnicPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    /* 向DIPC上报PDP IPv4已经激活事件 */
    if (TAF_PDP_IPV4 == (enPdpType & TAF_PDP_IPV4))
    {
        AT_PS_SndRnicIpv4PdpActInd(ucCid, pstEvent);
    }

    /* 向DIPC上报PDP IPv6已经激活事件 */
    if (TAF_PDP_IPV6 == (enPdpType & TAF_PDP_IPV6))
    {
        AT_PS_SndRnicIpv6PdpActInd(ucCid, pstEvent);
    }

    return;

}

/*****************************************************************************
 函 数 名  : AT_PS_SndRnicPdpDeactInd
 功能描述  : APP端口拨号时通知虚拟网卡
 输入参数  : VOS_UINT8                           ucRabId
             VOS_UINT8                           ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_SndRnicPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_RNIC_PDP_DEACT_IND_STRU         *pstMsg;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* 判断网卡的有效性 */
    if (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return;
    }

    /* 申请AT_NDIS_PDP_DEACT_IND_STRU消息 */
    pstMsg = (AT_RNIC_PDP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_PDP_DEACT_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: alloc msg fail!");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_PDP_DEACT_IND;

    /* 填写消息体 rab id */
    pstMsg->ucRabId         = pstEvent->ucRabId;

    /* 填写消息体 rmnet id，从chdata设置中获取 */
    pstMsg->ucRmNetId       = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_NotifyRnicPdpDeactInd: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ActivateRmNet
 功能描述  : 给网卡发送PDP激活事件
 输入参数  : VOS_UINT8                           ucCallId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_ActivateRmNet(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_SND_PDP_ACT_IND_STRU         *pstSndPdpActIndFuncTblPtr = VOS_NULL_PTR;
    AT_PS_SND_PDP_ACT_IND_FUNC          pSndPdpActIndFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo               = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstSndPdpActIndFuncTblPtr = AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_PTR();

    /* 在事件处理表中查找处理函数 */
    for (ulCnt = 0; ulCnt < AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstSndPdpActIndFuncTblPtr[ulCnt].ucUsrType)
        {
            /* 类型匹配 */
            pSndPdpActIndFunc = pstSndPdpActIndFuncTblPtr[ulCnt].pSndPdpActInd;
            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if (VOS_NULL_PTR != pSndPdpActIndFunc)
    {
        pSndPdpActIndFunc(pstUserInfo->ucUsrCid, pstEvent, enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_ActivateRmNet:ERROR: User type is invalid!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_DeactivateRmNet
 功能描述  : 给网卡发送PDP去激活事件
 输入参数  : VOS_UINT8                           ucCallId
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_DeactivateRmNet(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;
    AT_PS_SND_PDP_DEACT_IND_STRU       *pstSndPdpDeActIndFuncTblPtr = VOS_NULL_PTR;
    AT_PS_SND_PDP_DEACT_IND_FUNC        pSndPdpDeActIndFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstUserInfo                 = AT_PS_GetUserInfo(pstEvent->stCtrl.usClientId, ucCallId);
    pstSndPdpDeActIndFuncTblPtr = AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_PTR();

    /* 在事件处理表中查找处理函数 */
    for (ulCnt = 0; ulCnt < AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_SIZE(); ulCnt++)
    {
        if (pstUserInfo->ucUsrType == pstSndPdpDeActIndFuncTblPtr[ulCnt].ucUsrType)
        {
            /* 类型匹配 */
            pSndPdpDeActIndFunc = pstSndPdpDeActIndFuncTblPtr[ulCnt].pSndPdpDeActInd;
            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if (VOS_NULL_PTR != pSndPdpDeActIndFunc)
    {
        pSndPdpDeActIndFunc(pstUserInfo->ucUsrCid, pstEvent, enPdpType);
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeactivateRmNet:ERROR: User type is invalid!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_PS_IsIpv6CapabilityValid
 功能描述  : 判断ipv6能力有效
 输入参数  : VOS_UINT8 ucCapability
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6CapabilityValid(VOS_UINT8 ucCapability)
{
    if ((AT_IPV6_CAPABILITY_IPV4_ONLY == ucCapability)
     || (AT_IPV6_CAPABILITY_IPV6_ONLY == ucCapability)
     || (AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP == ucCapability))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : AT_PS_IsIpv6Support
 功能描述  : 判断是否支持IPV6
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月2日
    作    者   : L60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6Support(VOS_VOID)
{
    VOS_UINT8                           ucIpv6Capability;

    ucIpv6Capability = AT_GetCommPsCtxAddr()->ucIpv6Capability;

    if ((AT_IPV6_CAPABILITY_IPV6_ONLY == ucIpv6Capability)
     || (AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP == ucIpv6Capability))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : AT_PS_GenIpv6LanAddrWithRadomIID
 功能描述  : 获取IPv6动态全局地址
 输入参数  : pucPrefix          - 地址前缀
             ulPrefixByteLen    - 地址前缀字节长度
             pucIpv6LanAddr     - IPv6地址
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : C50 IPv6 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
)
{
    VOS_UINT32                         *paulAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulTick;

    paulAddr = (VOS_UINT32 *)pucIpv6LanAddr;

    if (ulPrefixByteLen > AT_IPV6_ADDR_PREFIX_BYTE_LEN)
    {
        return VOS_ERR;
    }

    /* 拷贝IPv6地址前缀 */
    PS_MEM_CPY(pucIpv6LanAddr, pucPrefix, ulPrefixByteLen);

    ulTick = VOS_GetTick();

    /* 在进行PC测试时，不使用随机值 */
#if (VOS_WIN32 == VOS_OS_VER)
    paulAddr[2] = 0xFFFFFFFFU;

    paulAddr[3] = 0xFFFFFFFFU;

#else
    VOS_SetSeed(ulTick);
    paulAddr[2] = VOS_Rand(0xFFFFFFFFU);

    VOS_SetSeed(ulTick + 10);
    paulAddr[3] = VOS_Rand(0xFFFFFFFFU);

#endif

    *(VOS_UINT8 *)(&paulAddr[2]) &= ~0x02;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_SaveIPv6Dns
 功能描述  : 保存IPV6的DNS到PDP实体中
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID  AT_PS_SaveIPv6Dns(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriDns    = VOS_FALSE;
    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecDns    = VOS_FALSE;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 保存主副DNS，收到RA参数时需要，激活网卡时需要通知DRV */
    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpPrimDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                pstEvent->stIpv6Dns.aucPrimDnsAddr,
                AT_MAX_IPV6_DNS_LEN);
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriDns = VOS_TRUE;
    }

    if (VOS_TRUE == pstEvent->stIpv6Dns.bitOpSecDnsAddr)
    {
        PS_MEM_CPY((VOS_VOID*)pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                   pstEvent->stIpv6Dns.aucSecDnsAddr,
                   AT_MAX_IPV6_DNS_LEN);
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecDns = VOS_TRUE;
    }
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

}

/*****************************************************************************
 函 数 名  : AT_PS_SaveIPv6Pcscf
 功能描述  : 保存IPV6的Pcscf到PDP实体中
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
  2.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2015031000157, 新增第三个p-cscf地址
*****************************************************************************/
VOS_VOID  AT_PS_SaveIPv6Pcscf(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriPCSCF = VOS_FALSE;
    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecPCSCF = VOS_FALSE;
    pstCallEntity->stIpv6DhcpInfo.bitOpIpv6ThiPCSCF = VOS_FALSE;

    /* 处理IPV6的主PCSCF地址 */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6PriPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucPrimPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* 处理IPV6的副PCSCF地址 */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpSecPcscfAddr)
    {
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6SecPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucSecPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

    /* 处理IPV6的第三PCSCF地址 */
    if (VOS_TRUE == pstEvent->stIpv6Pcscf.bitOpThiPcscfAddr)
    {
        pstCallEntity->stIpv6DhcpInfo.bitOpIpv6ThiPCSCF = VOS_TRUE;
        PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucThiPcscfAddr,
                   pstEvent->stIpv6Pcscf.aucThiPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }

}

/*****************************************************************************
 函 数 名  : AT_PS_ProcConnectedIpv6Addr
 功能描述  : 处理IPv6地址
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数

*****************************************************************************/
VOS_VOID AT_PS_ProcConnectedIpv6Addr(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    pstCallEntity->stIpv6DhcpInfo.ucRabId  = pstEvent->ucRabId;

    /* 处理IPv6的IP地址，形式为网络序 */
    PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
               pstEvent->stPdpAddr.aucIpv6Addr,
               TAF_IPV6_ADDR_LEN);

    /* 处理IPV6的主副DNS地址，形式为网络序 */
    AT_PS_SaveIPv6Dns(ucCallId, pstEvent);

    /* 处理IPV6的主副PCSCF地址，形式为网络序 */
    AT_PS_SaveIPv6Pcscf(ucCallId, pstEvent);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv6RaInfo
 功能描述  : 收到Router Advertisement IP报文, 进行处理和分发
 输入参数  : pstRaInfoNotifyInd - RA报文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数

  2.日    期   : 2013年01月21日
    作    者   : A00165503
    修改内容   : DTS2013011803709: IPv6前缀处理优化
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstIpv6RaInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIpv6AddrTestModeCfg;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};
    VOS_UINT8                           ucCallId;

    pstCommPsCtx          = AT_GetCommPsCtxAddr();
    ulIpv6AddrTestModeCfg = pstCommPsCtx->ulIpv6AddrTestModeCfg;

    ucCallId = AT_PS_TransCidToCallId(pstRaInfoNotifyInd->stCtrl.usClientId, pstRaInfoNotifyInd->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcIpv6RaInfo: CallId is invalid!");
        return;
    }

    pstCallEntity = AT_PS_GetCallEntity(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId);
    pstIpv6RaInfo = &pstCallEntity->stIpv6RaInfo;

    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_PS_ProcIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* 获取到IPv6地址前缀后, 上报已连接结果^DCONN */
    if (VOS_FALSE == pstIpv6RaInfo->bitOpPrefixAddr)
    {
        /* IPv6拨号成功 */
        AT_PS_SndCallConnectedResult(pstRaInfoNotifyInd->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6);

        /* 记录IPv6前缀 */
        pstIpv6RaInfo->bitOpPrefixAddr    = VOS_TRUE;
        pstIpv6RaInfo->ulPrefixBitLen     = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
        PS_MEM_CPY(pstIpv6RaInfo->aucPrefixAddr,
                   pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   TAF_IPV6_ADDR_LEN);

        /* 计算IPv6全局地址 */
        if (VOS_TRUE == AT_IsApPort((VOS_UINT8)pstRaInfoNotifyInd->stCtrl.usClientId))
        {
            AT_PS_GenIpv6LanAddrWithRadomIID(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr);
        }
        else
        {
            AT_CalcIpv6LanAddrFromIpv6Prefix(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr,
                                             TAF_IPV6_ADDR_LEN);
        }

        /* 记录IPv6全局地址 */
        pstIpv6RaInfo->bitOpLanAddr       = VOS_TRUE;
        PS_MEM_CPY(pstIpv6RaInfo->aucLanAddr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* 更新DHCPV6信息中的IPv6全局地址 */
        if ((IPV6_ADDRESS_TEST_MODE_ENABLE == ulIpv6AddrTestModeCfg)
         && (AT_PS_IS_IPV6_ADDR_IID_VALID(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr)))
        {
            PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                       pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                       pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8);
        }
        else
        {
            PS_MEM_CPY(pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);
        }
    }

    /* 记录Preferred Lifetime */
    pstIpv6RaInfo->bitOpPreferredLifetime = VOS_TRUE;
    pstIpv6RaInfo->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* 记录Valid Lifetime */
    pstIpv6RaInfo->bitOpValidLifetime     = VOS_TRUE;
    pstIpv6RaInfo->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* 记录IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstIpv6RaInfo->bitOpMtuSize       = VOS_TRUE;
        pstIpv6RaInfo->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_MatchIpv4v6ConnFailFallbackCause
 功能描述  : 匹配IPv4v6连接建立失败出发回退处理流程的原因值
 输入参数  : enCause   - 错误码
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 匹配成功
             VOS_FALSE - 匹配失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_MatchIpv4v6ConnFailFallbackCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstBackProcExtCause = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulCnt;

    ulRslt = VOS_FALSE;

    /* 检查是否匹配拒绝原因值为#28 */
    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == enCause)
    {
        ulRslt = VOS_TRUE;
    }

    /* 检查是否匹配用户定制原因值 */
    pstBackProcExtCause = &(AT_GetCommPsCtxAddr()->stIpv6BackProcExtCauseTbl);

    for (ulCnt = 0; ulCnt < pstBackProcExtCause->ulCauseNum; ulCnt++)
    {
        if (pstBackProcExtCause->aenPsCause[ulCnt] == enCause)
        {
            ulRslt = VOS_TRUE;
            break;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : AT_PS_SetupSingleStackConn
 功能描述  : 建立单栈连接
 输入参数  : ucCallId  - 呼叫实体索引
             enPdpType - PDP类型(IPv4 or IPv6)
 输出参数  : 无
 返 回 值  : VOS_OK    - 成功
             VOS_ERR   - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_SetupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stCallDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    ulRslt          = VOS_ERR;
    ucCid           = 0;
    pstUsrDialParam = &(AT_PS_GetCallEntity(usClientId, ucCallId)->stUsrDialParam);
    enCallState     = AT_PS_GetCallStateByType(usClientId, ucCallId, enPdpType);

    if (AT_PDP_STATE_IDLE == enCallState)
    {
#ifdef DMT
        ucCid = TAF_APS_FindCidForDial(WUEPS_PID_AT);

        /* 填写拨号参数 */
        AT_PS_GenCallDialParam(&stCallDialParam,
                               pstUsrDialParam,
                               ucCid,
                               enPdpType);

        /* 发起激活请求 */
        if (VOS_OK == AT_PS_SetupCall(usClientId, ucCallId, &stCallDialParam))
        {
            ulRslt = VOS_OK;
        }
#else
        /* 查找一个未激活的CID进行激活 */
        if (VOS_OK == TAF_AGENT_FindCidForDial(usClientId, &ucCid))
        {
            /* 填写拨号参数 */
            AT_PS_GenCallDialParam(&stCallDialParam,
                                   pstUsrDialParam,
                                   ucCid,
                                   enPdpType);

            /* 发起激活请求 */
            if (VOS_OK == AT_PS_SetupCall(usClientId, ucCallId, &stCallDialParam))
            {
                ulRslt = VOS_OK;
            }
        }
#endif
    }
    else
    {
        ulRslt = VOS_OK;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : AT_PS_HangupSingleStackConn
 功能描述  : 断开单栈连接
 输入参数  : ucCallId  - 呼叫实体索引
             enPdpType - 断开的PDP类型(IPv4 or IPv6)
 输出参数  : 无
 返 回 值  : VOS_OK    - 成功
             VOS_ERR   - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_HangupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulRslt;

    ulRslt      = VOS_ERR;
    ucCid       = AT_PS_GetCidByCallType(usClientId, ucCallId, enPdpType);
    enCallState = AT_PS_GetCallStateByType(usClientId, ucCallId, enPdpType);

    switch (enCallState)
    {
        case AT_PDP_STATE_ACTED:
        case AT_PDP_STATE_ACTING:
            if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                         usClientId,
                                         0,
                                         ucCid))
            {
                ulRslt = VOS_OK;

                AT_PS_SetCallStateByType(usClientId, ucCallId, enPdpType, AT_PDP_STATE_DEACTING);
            }
            else
            {
                AT_ERR_LOG("AT_PS_HangupSingleStackConn: Hangup call failed!");
            }
            break;

        case AT_PDP_STATE_DEACTING:
            ulRslt = VOS_OK;
            break;

        case AT_PDP_STATE_IDLE:
        default:
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcDualStackCallConn
 功能描述  : PDP激活成功后的回退处理
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

  3.日    期   : 2015年7月17日
    作    者   : Y00213812
    修改内容   : CDMA模式下电信不支持双承载双栈
*****************************************************************************/
VOS_VOID AT_PS_ProcDualStackCallConn(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    /* 不带原因值或#52原因值，需要发起另一种PDP激活 */
    if ( (VOS_FALSE == pstEvent->bitOpCause)
      || ( (VOS_TRUE == pstEvent->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstEvent->enCause) ) )
    {
        switch (pstEvent->stPdpAddr.enPdpType)
        {
            case TAF_PDP_IPV4:
                if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
                {
                    /* 记录呼叫错误码 */
                    AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                    /* 上报IPv6拨号失败 */
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV6,
                                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
                }
                break;

            case TAF_PDP_IPV6:
                if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
                {
                    /* 记录呼叫错误码 */
                    AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                    /* 上报IPv4拨号失败 */
                    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                             ucCallId,
                                             TAF_PDP_IPV4,
                                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
                }
                break;

            default:
                AT_WARN_LOG("AT_PS_ProcDualStackCallConn: PDP type is invalid!");
                break;
        }
    }
    else
    {
        /* 根据原因值, 通知APP拨号结果 */
        switch (pstEvent->enCause)
        {
            /* 原因值#50 (IPv4 ONLY), 通知APP模块IPv6激活失败 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case TAF_PS_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED:
#endif
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV6,
                                         pstEvent->enCause);

                break;

            /* 原因值#51 (IPv6 ONLY), 通知APP模块IPv4激活失败 */
            case TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED:
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case TAF_PS_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED:
#endif
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV4,
                                         pstEvent->enCause);

                break;

            /* 其他原因值, 不处理 */
            default:
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         (TAF_PDP_IPV4 == pstEvent->stPdpAddr.enPdpType) ? TAF_PDP_IPV6 : TAF_PDP_IPV4,
                                         pstEvent->enCause);
                break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4ConnSuccFallback
 功能描述  : 处理IPv4连接建立回退流程
 输入参数  : ucCallId - 呼叫实体索引
             pstEvent - 呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
           IPV6的PDP激活。其中，TAF_PDP_IPV6是异常情况，用户发起IPV6的PDP
           激活，而网络回复IPV4的激活，此时也需要重新发起IPV6的PDP激活 */
        case TAF_PDP_IPV4:
            if (VOS_OK != AT_PS_SetupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
            {
                /* 记录呼叫错误码 */
                AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

                /* 上报IPv6拨号失败 */
                AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                         ucCallId,
                                         TAF_PDP_IPV6,
                                         AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
            }
            break;

        /* 这里是PDP激活回退功能实现 */
        case TAF_PDP_IPV4V6:

            /* 设置IPv6对应的CID为无效 */
            AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

            /* 将该PDP切换到IDLE态 */
            AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

            AT_PS_ProcDualStackCallConn(ucCallId, pstEvent);

            break;

        default:
            AT_ERR_LOG("AT_PS_ProcIpv4ConnSuccFallback: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv6ConnSuccFallback
 功能描述  : 处理IPv6连接建立回退流程
 输入参数  : ucCallId - 呼叫实体索引
             pstEvent - 呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        case TAF_PDP_IPV6:
            /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
               IPV6的PDP激活, IPV6激活后不再发起IPV4的PDP激活 */
            break;

        /* 这里是PDP激活回退功能实现 */
        case TAF_PDP_IPV4V6:

            /* 设置IPv4对应的CID为无效 */
            AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

            /* 将该PDP切换到IDLE态 */
            AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

            AT_PS_ProcDualStackCallConn(ucCallId, pstEvent);

            break;

        default:
            AT_ERR_LOG("AT_PS_ProcIpv6ConnSuccFallback: PDP type is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4ConnFailFallback
 功能描述  : 处理IPv4连接失败回退流程
 输入参数  : ucCallId - 呼叫实体索引
             pstEvent - 呼叫事件
 输出参数  : 无
 返 回 值  : VOS_OK   - 成功
             VOS_ERR  - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ProcIpv4ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity       = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stCallDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    ulRslt        = VOS_OK;

    if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv6State)
    {
        /* 填写拨号参数 */
        AT_PS_GenCallDialParam(&stCallDialParam,
                               &pstCallEntity->stUsrDialParam,
                               pstCallEntity->stUserInfo.ucUsrCid,
                               TAF_PDP_IPV6);

        /* 发起IPv4类型的PDP激活请求 */
        if (VOS_OK != AT_PS_SetupCall(pstEvent->stCtrl.usClientId, ucCallId, &stCallDialParam))
        {
            ulRslt = VOS_ERR;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4v6ConnFailFallback
 功能描述  : 处理IPv4v6连接失败回退流程
 输入参数  : ucCallId - 呼叫实体索引
             pstEvent - 呼叫事件
 输出参数  : 无
 返 回 值  : VOS_OK   - 成功
             VOS_ERR  - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月18日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ProcIpv4v6ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity       = VOS_NULL_PTR;
    AT_DIAL_PARAM_STRU                  stCallDialParam;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stCallDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    ulRslt        = VOS_ERR;

    /* 填写拨号参数 */
    AT_PS_GenCallDialParam(&stCallDialParam,
                           &pstCallEntity->stUsrDialParam,
                           pstCallEntity->stUserInfo.ucUsrCid,
                           TAF_PDP_IPV4);

    /* 发起IPv4类型的PDP激活请求 */
    if (VOS_OK == AT_PS_SetupCall(pstEvent->stCtrl.usClientId, ucCallId, &stCallDialParam))
    {
        ulRslt = VOS_OK;
    }

    return ulRslt;
}
#endif

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4CallConnected
 功能描述  : IPv4激活处理
 输入参数  : ucCallId - 呼叫实体索引
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换

*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* 将本IPv4类型PDP状态切换到激活状态 */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

    /* 处理IPv4类型的DHCP */
    AT_PS_ProcConnInd(ucCallId, pstEvent);

    /* 上报IPv4连接状态 */
    AT_PS_SndCallConnectedResult(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* 向网卡发送PDP激活事件 */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4);

    /* 向FC注册流控点 */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* 将指定CID的PDP的激活状态设置为激活态 */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果用户发起的是IPV4V6，需要激活另一个PDP */
    if (VOS_TRUE == AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_PS_ProcIpv4ConnSuccFallback(ucCallId, pstEvent);
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4CallReject
 功能描述  : 处理IPv4的PDP激活被拒事件
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* 用户发起IPv4v6类型的PDP激活, 而且被网络拒绝, 原因为28, 协议栈需要
       分别发起IPv4/IPv6类型的PDP激活, 协议栈首先发起IPv4, 再发起IPv6,
       如果IPv4类型的PDP激活再次被网络拒绝, 协议栈还需要尝试IPV6类型的
       PDP激活为了防止PDP激活嵌套, 如果IPv6类型的PDP激活失败, 将不再尝试
       IPv4类型的PDP激活 */

#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATE_ENUM_U8                enPreCallState;

    enPreCallState = AT_PS_GetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);
#endif

    /* 设置IPv4对应的CID为无效 */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

    /* 将IPv4类型的PDP状态切换到IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* 上报IPv4拨号失败 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             pstEvent->enCause);

    /* 释放CALLID和CID的映射关系 */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    if ( (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
      && (AT_PDP_STATE_ACTING == enPreCallState) )
    {
        if (VOS_OK == AT_PS_ProcIpv4ConnFailFallback(ucCallId, pstEvent))
        {
            return;
        }
        else
        {
            /* 记录呼叫错误码 */
            AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);

            /* 上报IPv6拨号失败 */
            AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                     ucCallId,
                                     TAF_PDP_IPV6,
                                     AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
        }
    }
#endif

    /* 释放呼叫实体 */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4CallEnded
 功能描述  : 处理IPv4的PDP去激活事件
 输入参数  : ucCallId - PDP实体ID
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* 设置IPv4对应的CID为无效 */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PS_CALL_INVALID_CID);

    /* 将IPv4类型的PDP状态切换到IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

    /* 上报IPv4去激活 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             pstEvent->enCause);

    /* 向网卡发送PDP去激活事件 */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4);

    /* 向FC去注册流控点 */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* 最后清除CID与数传通道的映射关系 */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* 释放CALLID和CID的映射关系 */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果IPv6类型的PDP还处于激活状态, 需要将其去激活 */
    if (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        if (VOS_OK == AT_PS_HangupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6))
        {
            return;
        }

        if (TAF_PDP_IPV4 == AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
        {
            /* 上报IPv6拨号断开 */
            AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                                     ucCallId,
                                     TAF_PDP_IPV6,
                                     TAF_PS_CAUSE_SUCCESS);
        }
    }
#endif

    /* 清除PDP实体 */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv6CallConnected
 功能描述  : 处理IPV6的PDP激活成功的事件
 输入参数  : ucCallId - PDP实体ID
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* 将本IPv6类型状态切换到激活状态 */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

    /* 处理IPV6地址 */
    AT_PS_ProcConnectedIpv6Addr(ucCallId, pstEvent);

    /* 向网卡发送PDP激活事件 */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV6);

    /* 向FC注册流控点 */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* 将指定CID的PDP的激活状态设置为激活态 */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    /* 如果用户发起的是IPV4V6，需要激活另一个PDP */
    if (AT_PS_IsUsrDialTypeDualStack(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_PS_ProcIpv6ConnSuccFallback(ucCallId, pstEvent);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_AppIpv4v6ActCnfProc
 功能描述  : 处理IPv4v6的PDP激活成功的事件
 输入参数  : ucCallId - PDP实体ID
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4v6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* IPv4v6类型状态切换到激活状态 */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

    /* 处理IPV4地址 */
    AT_PS_ProcConnInd(ucCallId, pstEvent);

    /* 处理IPV6地址 */
    AT_PS_ProcConnectedIpv6Addr(ucCallId, pstEvent);

    /* 上报IPv4激活指示, IPv6类型的激活指示需要在获取RA信息后上报 */
    AT_PS_SndCallConnectedResult(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4);

    /* 向网卡发送PDP激活事件 */
    AT_PS_ActivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4V6);

    /* 向FC注册流控点 */
    AT_PS_RegFCPoint(ucCallId, pstEvent);

    /* 将指定CID的PDP的激活状态设置为激活态 */
    AT_SetAtChdataCidActStatus(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid, VOS_TRUE);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv6CallReject
 功能描述  : 处理IPv6的PDP激活被拒事件
 输入参数  : ucCallId - PDP实体ID
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* 如果IPv6类型, 就不需要再尝试IPv4, 因为前面已经发起过IPv4类型的PDP
       激活, 如果再发起IPv4类型的PDP激活的话, 可能会导致PDP激活嵌套 */

    /* 设置IPv6对应的CID为无效 */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

    /* 将IPv6类型的PDP状态切换到IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* 上报IPv6去激活 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             pstEvent->enCause);

    /* 释放CALLID和CID的映射关系 */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* 若同一个实体中的IPV4状态为IDLE则需要清除实体 */
    if (AT_PDP_STATE_IDLE == AT_PS_GetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
    {
        /* 释放呼叫实体 */
        AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4v6CallReject
 功能描述  : 处理IPv4v6的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4v6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
)
{
    /* 设置IPv4v6对应的CID为无效 */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PS_CALL_INVALID_CID);

    /* 将IPv4v6类型的PDP状态切换到IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* 释放CALLID和CID的映射关系 */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* IPv4v6连接失败回退处理 */
    if (VOS_TRUE == AT_PS_MatchIpv4v6ConnFailFallbackCause(pstEvent->enCause))
    {
        if (VOS_OK == AT_PS_ProcIpv4v6ConnFailFallback(ucCallId, pstEvent))
        {
            return;
        }
        else
        {
            /* 记录呼叫错误码 */
            AT_PS_SetPsCallErrCause(pstEvent->stCtrl.usClientId, TAF_PS_CAUSE_UNKNOWN);
        }
    }

    /* 上报IPv4拨号失败 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4,
                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));
    /* 上报IPv6拨号失败 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             AT_PS_GetPsCallErrCause(pstEvent->stCtrl.usClientId));

    /* 释放呼叫实体 */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv6CallEnded
 功能描述  : 处理IPv6的PDP去激活事件
 输入参数  : ucCallId - PDP实体ID
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* 设置IPv6对应的CID为无效 */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PS_CALL_INVALID_CID);

    /* 将IPv6类型的PDP状态切换到IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

    /* 上报IPv6去激活 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV6,
                             pstEvent->enCause);

    /* 向网卡发送PDP去激活事件 */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV6);

    /* 向FC去注册流控点 */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* 最后清除CID与数传通道的映射关系 */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* 释放CALLID和CID的映射关系 */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* 如果IPv4类型的PDP还处于激活状态, 需要将其去激活 */
    if (VOS_OK == AT_PS_HangupSingleStackConn(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4))
    {
        return;
    }

    /* 释放呼叫实体 */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcIpv4v6CallEnded
 功能描述  : 处理IPv4v6的PDP去激活事件
 输入参数  : ucCallId - PDP实体ID
             pstEvent - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增函数
*****************************************************************************/
VOS_VOID AT_PS_ProcIpv4v6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    pstCallEntity = AT_PS_GetCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    /* 设置IPv4v6对应的CID为无效 */
    AT_PS_SetCid2CurrCall(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PS_CALL_INVALID_CID);

    /* 将IPv4v6类型的PDP状态切换到IDLE */
    AT_PS_SetCallStateByType(pstEvent->stCtrl.usClientId, ucCallId, TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

    /* 上报IPv4和IPv6连接断开指示 */
    AT_PS_SndCallEndedResult(pstEvent->stCtrl.usClientId,
                             ucCallId,
                             TAF_PDP_IPV4V6,
                             pstEvent->enCause);

    /* 向网卡发送PDP去激活事件 */
    AT_PS_DeactivateRmNet(ucCallId, pstEvent, TAF_PDP_IPV4V6);

    /* 向FC去注册流控点 */
    AT_PS_DeRegFCPoint(ucCallId, pstEvent);

    /* 最后清除CID与数传通道的映射关系 */
    AT_CleanAtChdataCfg(pstEvent->stCtrl.usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    /* 释放CALLID和CID的映射关系 */
    AT_PS_FreeCallIdToCid(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    /* 清除PDP实体 */
    AT_PS_FreeCallEntity(pstEvent->stCtrl.usClientId, ucCallId);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : AT_PS_ProcCallConnectedEvent
 功能描述  : 处理PS域呼叫建立事件
 输入参数  : pstEvent - CALL_PDP_ACTIVATE_CNF事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ProcCallConnectedEvent(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallConnectedEvent:ERROR: CallId is invalid!");
        return;
    }

    /* 根据PDP类型分别处理*/
    switch (pstEvent->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            /* 处理IPv4的PDP激活成功事件 */
            AT_PS_ProcIpv4CallConnected(ucCallId, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* 处理IPv6的PDP激活成功事件 */
            AT_PS_ProcIpv6CallConnected(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* 处理IPv4v6的PDP激活成功事件 */
            AT_PS_ProcIpv4v6CallConnected(ucCallId, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ProcCallConnectedEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcCallRejectEvent
 功能描述  : 处理PS域呼叫失败事件
 输入参数  : pstEvent - CALL_PDP_ACTIVATE_REJ事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ProcCallRejectEvent(
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallRejectEvent:ERROR: CallId is invalid!");
        return;
    }

    /* 根据PDP类型分别处理*/
    switch (AT_PS_GetCurrCallType(pstEvent->stCtrl.usClientId, ucCallId))
    {
        case TAF_PDP_IPV4:
            /* 处理IPv4的PDP激活被拒事件 */
            AT_PS_ProcIpv4CallReject(ucCallId, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* 处理IPv6的PDP激活被拒事件 */
            AT_PS_ProcIpv6CallReject(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* 处理IPv4v6的PDP激活被拒事件 */
            AT_PS_ProcIpv4v6CallReject(ucCallId, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ProcCallRejectEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcCallEndedEvent
 功能描述  : 处理PS域呼叫断开事件
 输入参数  : pstEvent - PDP_DEACTIVATE_IND/PDP_DEACTIVATE_CNF事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ProcCallEndedEvent(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstEvent->stCtrl.usClientId, pstEvent->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstEvent->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallEndedEvent:ERROR: CallId is invalid!");
        return;
    }

    /* 根据PDP类型分别处理*/
    switch ( pstEvent->enPdpType )
    {
        case TAF_PDP_IPV4:
            /* 处理IPv4的PDP去激活事件 */
            AT_PS_ProcIpv4CallEnded(ucCallId, pstEvent);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* 处理IPv6的PDP去激活事件 */
            AT_PS_ProcIpv6CallEnded(ucCallId, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* 处理IPv4v6的PDP去激活事件 */
            AT_PS_ProcIpv4v6CallEnded(ucCallId, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ProcCallRejectEvent:WARNING: PDP type is invaild!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcCallOrigCnfEvent
 功能描述  : 处理PS_CALL_ORIG_CNF事件
 输入参数  : pstCallOrigCnf - PS_CALL_ORIG_CNF事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ProcCallOrigCnfEvent(TAF_PS_CALL_ORIG_CNF_STRU *pstCallOrigCnf)
{
    /* (1) 将CID翻译成呼叫实体索引
     * (2) 检查呼叫实体索引有效性
     * (3) 检查呼叫错误码&当前呼叫状态
     *     如果成功
     *     ->无处理
     *     如果失败
     *     ->上报^DEND
     *     ->清除CALLID和CID的映射
     *     ->释放呼叫实体
     */
    AT_PDP_STATE_ENUM_U8                enCallState;
    VOS_UINT8                           ucCallId;

    /* 获取CID关联的呼叫实体索引(CallId) */
    ucCallId = AT_PS_TransCidToCallId(pstCallOrigCnf->stCtrl.usClientId, pstCallOrigCnf->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstCallOrigCnf->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: CallId is invalid!");
        return;
    }

    enCallState = AT_PS_GetCallStateByCid(pstCallOrigCnf->stCtrl.usClientId, ucCallId, pstCallOrigCnf->ucCid);

    if (TAF_PS_CAUSE_SUCCESS != pstCallOrigCnf->enCause)
    {
        switch (enCallState)
        {
            case AT_PDP_STATE_ACTING:
            case AT_PDP_STATE_DEACTING:

                /* 设置对应的CID为无效 */
                AT_PS_SetCid2CurrCall(pstCallOrigCnf->stCtrl.usClientId,
                                      ucCallId,
                                      AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                      AT_PS_CALL_INVALID_CID);

                /* 设置对应的PDP状态切换到IDLE */
                AT_PS_SetCallStateByType(pstCallOrigCnf->stCtrl.usClientId,
                                         ucCallId,
                                         AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                         AT_PDP_STATE_IDLE);

                /* 上报拨号失败 */
                AT_PS_SndCallEndedResult(pstCallOrigCnf->stCtrl.usClientId,
                                         ucCallId,
                                         AT_PS_GetCurrCallType(pstCallOrigCnf->stCtrl.usClientId, ucCallId),
                                         pstCallOrigCnf->enCause);

                /* 清除CALLID和CID的映射 */
                AT_PS_FreeCallIdToCid(pstCallOrigCnf->stCtrl.usClientId, pstCallOrigCnf->ucCid);

                break;

            default:
                AT_WARN_LOG1("AT_PS_ProcCallOrigCnfEvent: State is invalid! <state>", enCallState);
                break;
        }

        if (VOS_TRUE == AT_PS_IsLinkDown(pstCallOrigCnf->stCtrl.usClientId, ucCallId))
        {
            /* 释放呼叫实体 */
            AT_PS_FreeCallEntity(pstCallOrigCnf->stCtrl.usClientId, ucCallId);
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcCallEndCnfEvent
 功能描述  : 处理PS_CALL_END_CNF事件
 输入参数  : pstCallOrigCnf - PS_CALL_ORIG_CNF事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ProcCallEndCnfEvent(TAF_PS_CALL_END_CNF_STRU *pstCallEndCnf)
{
    /* (1) 将CID翻译成呼叫实体索引
     * (2) 检查呼叫实体索引有效性
     * (3) 检查呼叫错误码
     *     如果成功
     *     ->无处理
     *     如果失败
     *     ->异常(打印)
     */

    /* 获取CID关联的呼叫实体索引(CallId)
     * (A) CallId无效
     *     -> 返回
     * (B) CallId有效
     *     -> 继续
     */
    VOS_UINT8                           ucCallId;

    ucCallId = AT_PS_TransCidToCallId(pstCallEndCnf->stCtrl.usClientId, pstCallEndCnf->ucCid);

    if (VOS_FALSE == AT_PS_IsCallIdValid(pstCallEndCnf->stCtrl.usClientId, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcCallOrigCnfEvent: CallId is invalid!");
        return;
    }

    if (TAF_ERR_NO_ERROR != pstCallEndCnf->enCause)
    {
        AT_ERR_LOG1("AT_PS_ProcCallOrigCnfEvent: End call failed! <cause>", pstCallEndCnf->enCause);
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcCallModifyEvent
 功能描述  : APP端口处理modify消息
 输入参数  : VOS_UINT8                           ucIndex
             TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_ProcCallModifyEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
)
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucUserCid;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRmNetId;
    FC_ID_ENUM_UINT8                    enDefaultFcId;

    ulRmNetId = 0;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, pstEvent->ucCid);

    if (!AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        /* AT+CGACT拨号，用户发起CGCMODE或网侧发起MODIFY IND */
        AT_NotifyFcWhenAppPdpModify(ucIndex, pstEvent);
    }
    else
    {
        /* AT^NDISDUP拨号，用户发起CGCMODE或网侧发起MODIFY IND */
        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

        /* 获取对应的用户CID */
        ucUserCid = pstModemPsCtx->astCallEntity[ucCallId].stUserInfo.ucUsrCid;

        /* 获取用户CID对应的网卡ID */
        ulRmNetId = pstModemPsCtx->astChannelCfg[ucUserCid].ulRmNetId;

        /* 获取网卡ID对应的FC ID */
        enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

        if (enDefaultFcId >= FC_ID_BUTT)
        {
            return VOS_ERR;
        }

        AT_NotifyFcWhenPdpModify(pstEvent, enDefaultFcId);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_RegHsicFCPoint
 功能描述  : 注册HISC通道流控点
 输入参数  : ucCid      - CID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月12日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换,直接处理激活事件上报和流控点注册
  3.日    期   : 2013年10月08日
    作    者   : j00174725
    修改内容   : TQE

*****************************************************************************/
VOS_VOID AT_PS_RegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_REG_POINT_STRU                   stRegFcPoint;
    FC_PRI_ENUM_UINT8                   enFCPri;
    UDI_DEVICE_ID_E                     enDataChannelId;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    PS_MEM_SET(&stRegFcPoint, 0, sizeof(FC_REG_POINT_STRU));

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((VOS_UINT8)pstEvent->stCtrl.usClientId, &enModemId);

    if (VOS_OK != ulRet)
    {
         return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* 寻找配套的通道ID */
    if ((VOS_TRUE         == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: data channel id is abnormal.\n");
        return;
    }

    enFcId = AT_PS_GetFcIdByUdiDeviceId(enDataChannelId);

    if (enFcId >= FC_ID_BUTT)
    {
        return;
    }

    /* 获取当前承载QOS对应的流控优先级 */
    if (TAF_USED == pstEvent->bitOpUmtsQos)
    {
        enFCPri = AT_GetFCPriFromQos(&pstEvent->stUmtsQos);
    }
    else
    {
        enFCPri = FC_PRI_FOR_PDN_NONGBR;
    }
    /* 检查流控点是否已经注册 */
    ulRet = AT_GetFcPriFromMap(enFcId ,&stFCPriOrg);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: AT_GetFcPriFromMap Err.\n");
    }

    if (VOS_TRUE == stFCPriOrg.ulUsed)
    {
        /* 如果当前FC优先级比之前承载的FC优先级高, 那么调整优先级 */
        if (enFCPri > stFCPriOrg.enFcPri)
        {
            AT_ChangeFCPoint(&pstEvent->stCtrl, enFCPri, enFcId);
        }

        /* 配置通道与RABID映射关系 */
        FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

        AT_INFO_LOG("AT_PS_RegHsicFCPoint: FC is already registered.");

        return;
    }

    /* 配置通道与RABID映射关系 */
    FC_ChannelMapCreate(enFcId, pstEvent->ucRabId, enModemId);

    stRegFcPoint.enFcId             = enFcId;
    stRegFcPoint.enModemId          = enModemId;
    /* 根据网卡上最高优先级RAB QoS优先级来折算,优先级改变时，需要改变优先级 */
    /*  FC_PRI_3        有最低优先级的承载
        FC_PRI_4        有NONGBR承载
        FC_PRI_5        有GBR承载 */
    stRegFcPoint.enFcPri            = enFCPri;
    stRegFcPoint.enPolicyId         = FC_POLICY_ID_MEM;
    stRegFcPoint.pClrFunc           = AT_DisableHsicFlowCtl;
    stRegFcPoint.pSetFunc           = AT_EnableHsicFlowCtl;
    stRegFcPoint.ulParam1           = (VOS_UINT32)DIPC_GetDevHandleByRabId(pstEvent->ucRabId);

    /* 注册流控点,需要分别注册MEM,CPU,CDS和GPRS。 */
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg mem point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CPU_A;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg a cpu point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_CDS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg cds point Failed.");
        return;
    }

    stRegFcPoint.enPolicyId         = FC_POLICY_ID_GPRS;
    ulRet = FC_RegPoint(&stRegFcPoint);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_RegHsicFCPoint: ERROR: reg gprs point Failed.");
        return;
    }

    /* 设置FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[enFcId].ulUsed  = VOS_TRUE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri = enFCPri;

    /* 勾流控消息 */
    AT_MNTN_TraceRegFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_DeRegHsicFCPoint
 功能描述  : 去注册hsic流控点
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_DeRegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRet;
    UDI_DEVICE_ID_E                     enDataChannelId;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)pstEvent->stCtrl.usClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_DeRegHsicFCPoint: Get modem id fail.");
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromModemId(enModemId);

    /* 寻找配套的通道ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      &&(AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId))
    {
        enDataChannelId = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegHsicFCPoint: ERROR: data channel id is abnormal.");
        return;
    }

    enFcId = AT_PS_GetFcIdByUdiDeviceId(enDataChannelId);

    if (enFcId >= FC_ID_BUTT)
    {
         return;
    }

    /* 删除流控模块映射关系 */
    FC_ChannelMapDelete(pstEvent->ucRabId, enModemId);

    ulRet = FC_DeRegPoint(enFcId, enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_PS_DeRegHsicFCPoint: ERROR: de reg point Failed.");
        return;
    }

    /* 清除FCID与FC Pri的映射关系 */
    g_stFcIdMaptoFcPri[enFcId].ulUsed  = VOS_FALSE;
    g_stFcIdMaptoFcPri[enFcId].enFcPri = FC_PRI_BUTT;

    /* 勾流控消息 */
    AT_MNTN_TraceDeregFcPoint((VOS_UINT8)pstEvent->stCtrl.usClientId, AT_FC_POINT_TYPE_HSIC);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_RegAppFCPoint
 功能描述  : 注册APP通道流控点
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_RegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    VOS_UINT32                          ulRslt;
    AT_FCID_MAP_STRU                    stFCPriOrg;
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT32                          ulRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* 寻找配套的通道ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId < RNIC_RMNET_ID_BUTT))
    {
        ulRmNetId = pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_RegAppFCPoint: data channel id is abnormal.\n");
        return;
    }

    /* 上述分支已能保证网卡的有效性 */
    enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

    ulRslt = AT_GetFcPriFromMap(enDefaultFcId ,&stFCPriOrg);
    if (VOS_OK == ulRslt)
    {
        /* 如果FC ID未注册，那么注册该流控点。*/
        if (VOS_TRUE != stFCPriOrg.ulUsed)
        {
            /* 注册APP拨号使用的流控点 */
            AT_AppRegFCPoint(enDefaultFcId, pstEvent, (VOS_UINT8)ulRmNetId);
        }
        else
        {
            /* APP拨号只使用最低的流控QOS优先级FC_PRI_FOR_PDN_LOWEST */
            AT_NORM_LOG("AT_PS_RegAppFCPoint: No need to change the default QOS priority.");
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_DeRegAppFCPoint
 功能描述  : 去注册APP通道流控点
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_DeRegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    FC_ID_ENUM_UINT8                    enDefaultFcId;
    VOS_UINT32                          ulRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(pstEvent->stCtrl.usClientId);

    /* 寻找配套的通道ID */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
     && (pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId < RNIC_RMNET_ID_BUTT))
    {
        ulRmNetId = (VOS_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;
    }
    else
    {
        AT_ERR_LOG("AT_PS_DeRegAppFCPoint: data channel id is abnormal.\n");
        return;
    }

    /* 上述分支已能保证网卡的有效性 */
    enDefaultFcId = AT_PS_GetFcIdFromRnicByRmNetId(ulRmNetId);

    /* 去注册APP拨号使用的流控点 */
    AT_AppDeRegFCPoint(enDefaultFcId, pstEvent);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_AllocCallEntity
 功能描述  : 分配PS域呼叫实体
 输入参数  : usClientId - 端口ID
 输出参数  : pucCallId - 呼叫实体索引
 返 回 值  : VOS_OK    - 成功
             VOS_ERR   - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_AllocCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *pucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    for (ucCallId = 0; ucCallId < AT_PS_MAX_CALL_NUM; ucCallId++)
    {
        pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

        if (VOS_FALSE == pstCallEntity->ulUsedFlg)
        {
            break;
        }
    }

    if (ucCallId >= AT_PS_MAX_CALL_NUM)
    {
        return VOS_ERR;
    }

    pstCallEntity->ulUsedFlg = VOS_TRUE;

    *pucCallId = ucCallId;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_FreeCallEntity
 功能描述  : 释放PS域呼叫实体
 输入参数  : usClientId - 端口号
             ucCallId - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_FreeCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    /* 清除CID与通道的关系 */
    AT_CleanAtChdataCfg(usClientId, pstCallEntity->stUserInfo.ucUsrCid);

    PS_MEM_SET(&pstCallEntity->stUserInfo,
               0x00, sizeof(AT_PS_USER_INFO_STRU));

    pstCallEntity->ulUsedFlg   = VOS_FALSE;
    pstCallEntity->ucIpv4Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv4State = AT_PDP_STATE_IDLE;

    PS_MEM_SET(&pstCallEntity->stIpv4DhcpInfo,
               0x00, sizeof(AT_IPV4_DHCP_PARAM_STRU));

#if (FEATURE_ON == FEATURE_IPV6)
    pstCallEntity->ucIpv6Cid   = AT_PS_CALL_INVALID_CID;
    pstCallEntity->enIpv6State = AT_PDP_STATE_IDLE;

    PS_MEM_SET(&pstCallEntity->stIpv6RaInfo,
               0x00, sizeof(AT_IPV6_RA_INFO_STRU));
    PS_MEM_SET(&pstCallEntity->stIpv6DhcpInfo,
               0x00, sizeof(AT_IPV6_DHCP_PARAM_STRU));
#endif

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_IsLinkGoingUp
 功能描述  : 判断拨号连接是否已建立/正在建立
 输入参数  : usClientId - 端口ID
             ucCallId  - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 连接已建立/正在建立
             VOS_FALSE - 连接未建立
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingUp(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) 任意呼叫状态处于已建立/正在建立: 返回TRUE
     * (2) 其他场景: 返回FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkUpFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkUpFlg   = VOS_FALSE;

    if ((AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
     || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv4State))
    {
        ulLinkUpFlg = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if ((AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
     || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv6State))
    {
        ulLinkUpFlg = VOS_TRUE;
    }
#endif

    return ulLinkUpFlg;
}

/*****************************************************************************
 函 数 名  : AT_PS_IsLinkGoingDown
 功能描述  : 判断拨号连接是否正在断开
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) 任意拨号连接处于DEACTING, 返回TRUE
     * (2) 其他场景, 返回FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkDownFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkDownFlg = VOS_FALSE;

    if (AT_PDP_STATE_DEACTING == pstCallEntity->enIpv4State)
    {
        ulLinkDownFlg = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_PDP_STATE_DEACTING == pstCallEntity->enIpv6State)
    {
        ulLinkDownFlg = VOS_TRUE;
    }
#endif

    return ulLinkDownFlg;
}

/*****************************************************************************
 函 数 名  : AT_PS_IsLinkDown
 功能描述  : 判断拨号连接是否已经断开
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 连接不存在
             VOS_FALSE - 连接存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) IPv4和IPv6连接都处于IDLE, 返回TRUE
     * (2) 其他场景, 返回FALSE
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulLinkDownFlg;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);
    ulLinkDownFlg = VOS_TRUE;

    if (AT_PDP_STATE_IDLE != pstCallEntity->enIpv4State)
    {
        ulLinkDownFlg = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_PDP_STATE_IDLE != pstCallEntity->enIpv6State)
    {
        ulLinkDownFlg = VOS_FALSE;
    }
#endif

    return ulLinkDownFlg;
}

/*****************************************************************************
 函 数 名  : AT_PS_ReportCurrCallConnState
 功能描述  : 上报当前已建立的拨号连接状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallConnState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) 根据呼叫实体中的用户类型查表, 获取连接建立状态上报函数指针
     * (2) 获取呼叫连接状态, 处于连接状态则上报
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc = VOS_NULL_PTR;

    pstCallEntity    = AT_PS_GetCallEntity(usClientId, ucCallId);

    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstCallEntity->stUserInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptConnRsltFunc)
    {
        if (AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
        {
            pRptConnRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                             pstCallEntity->stUserInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }

#if (FEATURE_ON == FEATURE_IPV6)
        if ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
          && (VOS_TRUE == pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr) )
        {
            pRptConnRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                             pstCallEntity->stUserInfo.enPortIndex,
                             TAF_PDP_IPV6);
        }
#endif
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportCurrCallConnState: pRptConnRsltFunc is NULL.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ReportCurrCallEndState
 功能描述  : 上报当前已断开的拨号连接状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallEndState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) 根据呼叫实体中的用户类型查表, 获取连接建立状态上报函数指针
     * (2) 获取呼叫连接状态, 处于断开状态则上报
     */

    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;

    pstCallEntity   = AT_PS_GetCallEntity(usClientId, ucCallId);
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstCallEntity->stUserInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv4State)
        {
            pRptEndRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                            pstCallEntity->stUserInfo.enPortIndex,
                            TAF_PDP_IPV4,
                            TAF_PS_CAUSE_SUCCESS);
        }

#if (FEATURE_ON == FEATURE_IPV6)
        if (VOS_TRUE == AT_PS_IsIpv6Support())
        {
            if (AT_PDP_STATE_IDLE == pstCallEntity->enIpv6State)
            {
                pRptEndRsltFunc(pstCallEntity->stUserInfo.ucUsrCid,
                                pstCallEntity->stUserInfo.enPortIndex,
                                TAF_PDP_IPV6,
                                TAF_PS_CAUSE_SUCCESS);
            }
        }
#endif
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportCurrCallEndState: pRptConnRsltFunc is NULL.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ReportAllCallEndState
 功能描述  : 上报所有拨号连接断开状态
 输入参数  : ucIndex - 端口号(ClientId)索引
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_PS_ReportAllCallEndState(VOS_UINT8 ucIndex)
{
    /* (1) 根据用户类型查表, 获取连接断开状态上报函数指针
     * (2) 上报所有连接断开状态
     */

    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc = VOS_NULL_PTR;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    PS_MEM_SET(&stUsrInfo, 0x00, sizeof(AT_PS_USER_INFO_STRU));

    AT_PS_ParseUsrInfo(ucIndex, &stUsrInfo);

    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(stUsrInfo.ucUsrType);

    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(stUsrInfo.ucUsrCid,
                        stUsrInfo.enPortIndex,
                        TAF_PDP_IPV4,
                        TAF_PS_CAUSE_SUCCESS);

#if (FEATURE_ON == FEATURE_IPV6)
        if (VOS_TRUE == AT_PS_IsIpv6Support())
        {
            pRptEndRsltFunc(stUsrInfo.ucUsrCid,
                            stUsrInfo.enPortIndex,
                            TAF_PDP_IPV6,
                            TAF_PS_CAUSE_SUCCESS);
        }
#endif
    }
    else
    {
        AT_WARN_LOG("AT_PS_ReportAllCallEndState: pRptConnRsltFunc is NULL.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ValidateDialParam
 功能描述  : 拨号参数检查
 输入参数  : ucIndex    - 端口号(ClientId)索引
 输出参数  : 无
 返 回 值  : AT_SUCCESS - 正确
             OTHER CODE - 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ValidateDialParam(VOS_UINT8 ucIndex)
{
    AT_PS_DATA_CHANL_CFG_STRU          *pstChanCfg = VOS_NULL_PTR;

    /* 检查命令类型 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: No parameter input.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 检查参数个数 */
    if (gucAtParaIndex > 6)
    {
        AT_NORM_LOG1("AT_PS_ValidateDialParam: Parameter number is %d.\n", gucAtParaIndex);
        return AT_TOO_MANY_PARA;
    }

    /* 检查 CID */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: Missing CID.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 拨号 CONN: 该参数不能省略, 1表示建立连接, 0表示断开断开连接 */
    if (0 == gastAtParaList[1].usParaLen)
    {
        AT_NORM_LOG("AT_PS_ValidateDialParam: Missing connect state.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 检查 APN */
    if (0 != gastAtParaList[2].usParaLen)
    {
        /* APN长度检查 */
        if (gastAtParaList[2].usParaLen > TAF_MAX_APN_LEN)
        {
            AT_NORM_LOG("AT_PS_ValidateDialParam: APN is too long.");
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* APN格式检查 */
        if (VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                        gastAtParaList[2].usParaLen))
        {
            AT_NORM_LOG("AT_PS_ValidateDialParam: Format of APN is wrong.");
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* 检查 Username */
    if (gastAtParaList[3].usParaLen > TAF_MAX_GW_AUTH_USERNAME_LEN)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 检查 Password */
    if (gastAtParaList[4].usParaLen > TAF_MAX_GW_AUTH_PASSWORD_LEN)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 检查通道映射 */
    pstChanCfg = AT_PS_GetDataChanlCfg(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if ( (VOS_FALSE == pstChanCfg->ulUsed)
      || (AT_PS_INVALID_RMNET_ID == pstChanCfg->ulRmNetId) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 函 数 名  : AT_PS_ParseUsrInfo
 功能描述  : 获取用户信息
 输入参数  : ucIndex     - 端口号(ClientId)索引
 输出参数  : pstUserInfo - 用户信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年5月27日
    作    者   : l00198894
    修改内容   : TSTS
*****************************************************************************/
VOS_VOID AT_PS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUserInfo
)
{
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;

    enUserIndex = ucIndex;

    /* PCUI口且设置PCUI口模拟NDISDUP拨号 */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            enUserIndex = AT_GetPcuiUsertId();
        }
    }

    /* CTRL口且设置CTRL口模拟NDISDUP拨号 */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            enUserIndex = AT_GetCtrlUserId();
        }
    }

    /* PCUI2口且设置CTRL口模拟NDISDUP拨号 */
    if (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcui2PsCallFlag())
        {
            enUserIndex = AT_GetPcui2UserId();
        }
    }

    pstUserInfo->enPortIndex = ucIndex;
    pstUserInfo->enUserIndex = enUserIndex;
    pstUserInfo->ucUsrType   = (AT_USER_TYPE)gastAtClientTab[enUserIndex].UserType;
    pstUserInfo->ucUsrCid    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ParseUsrDialParam
 功能描述  : 获取用户拨号参数信息
 输入参数  : ucIndex         - 端口号(ClientId)索引
 输出参数  : pstUsrDialParam - 拨号参数信息
 返 回 值  : VOS_OK          - 正确
             VOS_ERR         - 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ParseUsrDialParam(
    VOS_UINT8                           ucIndex,
    AT_DIAL_PARAM_STRU                 *pstUsrDialParam
)
{
    /* 由调用者保证入参和出参有效性 */

    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCtxInfo;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stPdpCtxInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));

    /* CID */
    pstUsrDialParam->ucCid         = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* APN */
    pstUsrDialParam->ucAPNLen      = (VOS_UINT8)gastAtParaList[2].usParaLen;
    PS_MEM_CPY(pstUsrDialParam->aucAPN,
               gastAtParaList[2].aucPara,
               gastAtParaList[2].usParaLen);

    /* Username */
    pstUsrDialParam->usUsernameLen = (VOS_UINT16)gastAtParaList[3].usParaLen;
    PS_MEM_CPY(pstUsrDialParam->aucUsername,
               gastAtParaList[3].aucPara,
               gastAtParaList[3].usParaLen);

    /* Password */
    pstUsrDialParam->usPasswordLen = (VOS_UINT16)gastAtParaList[4].usParaLen;
    PS_MEM_CPY(pstUsrDialParam->aucPassword,
               gastAtParaList[4].aucPara,
               gastAtParaList[4].usParaLen);

    /* AUTH TYPE */

    if (VOS_TRUE == At_CheckCurrRatModeIsCL(ucIndex))
    {
        pstUsrDialParam->usAuthType = AT_ClGetPdpAuthType(gastAtParaList[5].ulParaValue,
                                                               gastAtParaList[5].usParaLen);
    }
    else
    {
        if (gastAtParaList[5].usParaLen > 0)
        {
            pstUsrDialParam->usAuthType = AT_CtrlGetPDPAuthType(gastAtParaList[5].ulParaValue,
                                                                    gastAtParaList[5].usParaLen);
        }
        else
        {
            /* 如果用户名和密码长度均不为0, 且鉴权类型未设置, 则默认使用CHAP类型 */
            if ( (0 != gastAtParaList[3].usParaLen)
              && (0 != gastAtParaList[4].usParaLen) )
            {
                pstUsrDialParam->usAuthType = TAF_PDP_AUTH_TYPE_CHAP;
            }
            else
            {
                pstUsrDialParam->usAuthType = TAF_PDP_AUTH_TYPE_NONE;
            }
        }
    }





    /* ADDR: 暂不处理 */

    /* PDN TYPE */
#ifdef DMT
    ulRslt = MN_APS_GetPdpCidPara(&stPdpCtxInfo, pstUsrDialParam->ucCid);
#else
    ulRslt = TAF_AGENT_GetPdpCidPara(&stPdpCtxInfo, ucIndex, pstUsrDialParam->ucCid);
#endif

    if ( (VOS_OK == ulRslt)
      && (AT_PS_IS_PDP_TYPE_SUPPORT(stPdpCtxInfo.stPdpAddr.enPdpType)) )
    {
        pstUsrDialParam->enPdpType = stPdpCtxInfo.stPdpAddr.enPdpType;
    }
    else
    {
        pstUsrDialParam->enPdpType = TAF_PDP_IPV4;
    }

#if(FEATURE_ON == FEATURE_IPV6)
    if (VOS_OK != AT_CheckIpv6Capability(pstUsrDialParam->enPdpType))
    {
        AT_INFO_LOG("AT_PS_ParseUsrDialParam: PDP type is not supported.");

        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_SetCurrCallType
 功能描述  : 设置当前呼叫类型
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_SetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    pstCallEntity->enCurrPdpType = enPdpType;

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_GetCurrCallType
 功能描述  : 获取当前呼叫类型
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCallId
 输出参数  : 无
 返 回 值  : TAF_PDP_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_PDP_TYPE_ENUM_UINT8 AT_PS_GetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    return pstCallEntity->enCurrPdpType;
}

/*****************************************************************************
 函 数 名  : AT_PS_TransferQosPara
 功能描述  : QOS参数转化TAF_PS_PDP_QOS_QUERY_PARA_STRU-->TAF_PS_PDP_QOS_SET_PARA_STRU
 输入参数  : VOS_UINT8                           ucCid,
             TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosQueryPara,
 输出参数  : TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosSetPara
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID AT_PS_TransferQosPara(
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosQueryPara,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosSetPara
)
{
    if (VOS_TRUE == pstQosQueryPara->ucQosFlag)
    {
        pstQosSetPara->stQos.ucDefined = VOS_TRUE;
        pstQosSetPara->stQos.ucCid = ucCid;

        pstQosSetPara->stQos.bitOpTrafficClass = VOS_TRUE;
        pstQosSetPara->stQos.ucTrafficClass    = pstQosQueryPara->stQos.ucTrafficClass;

        pstQosSetPara->stQos.bitOpDeliverOrder = VOS_TRUE;
        pstQosSetPara->stQos.ucDeliverOrder    = pstQosQueryPara->stQos.ucDeliverOrder;

        pstQosSetPara->stQos.bitOpDeliverErrSdu = VOS_TRUE;
        pstQosSetPara->stQos.ucDeliverErrSdu    = pstQosQueryPara->stQos.ucDeliverErrSdu;

        pstQosSetPara->stQos.bitOpMaxSduSize = VOS_TRUE;
        pstQosSetPara->stQos.usMaxSduSize    = pstQosQueryPara->stQos.usMaxSduSize;

        pstQosSetPara->stQos.bitOpMaxBitUl = VOS_TRUE;
        pstQosSetPara->stQos.ulMaxBitUl    = pstQosQueryPara->stQos.ulMaxBitUl;

        pstQosSetPara->stQos.bitOpMaxBitDl = VOS_TRUE;
        pstQosSetPara->stQos.ulMaxBitDl    = pstQosQueryPara->stQos.ulMaxBitDl;

        pstQosSetPara->stQos.bitOpResidualBer = VOS_TRUE;
        pstQosSetPara->stQos.ucResidualBer    = pstQosQueryPara->stQos.ucResidualBer;

        pstQosSetPara->stQos.bitOpSduErrRatio = VOS_TRUE;
        pstQosSetPara->stQos.ucSduErrRatio    = pstQosQueryPara->stQos.ucSduErrRatio;

        pstQosSetPara->stQos.bitOpTransDelay = VOS_TRUE;
        pstQosSetPara->stQos.usTransDelay    = pstQosQueryPara->stQos.usTransDelay;

        pstQosSetPara->stQos.bitOpTraffHandlePrior = VOS_TRUE;
        pstQosSetPara->stQos.ucTraffHandlePrior    = pstQosQueryPara->stQos.ucTraffHandlePrior;

        pstQosSetPara->stQos.bitOpGtdBitUl = VOS_TRUE;
        pstQosSetPara->stQos.ulGtdBitUl    = pstQosQueryPara->stQos.ulGuarantBitUl;

        pstQosSetPara->stQos.bitOpGtdBitDl  = VOS_TRUE;
        pstQosSetPara->stQos.ulGtdBitDl     = pstQosQueryPara->stQos.ulGuarantBitDl;
    }
    else
    {
        pstQosSetPara->stQos.ucDefined = VOS_FALSE;
        pstQosSetPara->stQos.ucCid = ucCid;
    }

    if (VOS_TRUE == pstQosQueryPara->ucMinQosFlag)
    {
        pstQosSetPara->stMinQos.ucDefined = VOS_TRUE;
        pstQosSetPara->stMinQos.ucCid = ucCid;

        pstQosSetPara->stMinQos.bitOpTrafficClass = VOS_TRUE;
        pstQosSetPara->stMinQos.ucTrafficClass    = pstQosQueryPara->stMinQos.ucTrafficClass;

        pstQosSetPara->stMinQos.bitOpDeliverOrder = VOS_TRUE;
        pstQosSetPara->stMinQos.ucDeliverOrder    = pstQosQueryPara->stMinQos.ucDeliverOrder;

        pstQosSetPara->stMinQos.bitOpDeliverErrSdu = VOS_TRUE;
        pstQosSetPara->stMinQos.ucDeliverErrSdu    = pstQosQueryPara->stMinQos.ucDeliverErrSdu;

        pstQosSetPara->stMinQos.bitOpMaxSduSize = VOS_TRUE;
        pstQosSetPara->stMinQos.usMaxSduSize    = pstQosQueryPara->stMinQos.usMaxSduSize;

        pstQosSetPara->stMinQos.bitOpMaxBitUl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulMaxBitUl    = pstQosQueryPara->stMinQos.ulMaxBitUl;

        pstQosSetPara->stMinQos.bitOpMaxBitDl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulMaxBitDl    = pstQosQueryPara->stMinQos.ulMaxBitDl;

        pstQosSetPara->stMinQos.bitOpResidualBer = VOS_TRUE;
        pstQosSetPara->stMinQos.ucResidualBer    = pstQosQueryPara->stMinQos.ucResidualBer;

        pstQosSetPara->stMinQos.bitOpSduErrRatio = VOS_TRUE;
        pstQosSetPara->stMinQos.ucSduErrRatio    = pstQosQueryPara->stMinQos.ucSduErrRatio;

        pstQosSetPara->stMinQos.bitOpTransDelay = VOS_TRUE;
        pstQosSetPara->stMinQos.usTransDelay    = pstQosQueryPara->stMinQos.usTransDelay;

        pstQosSetPara->stMinQos.bitOpTraffHandlePrior = VOS_TRUE;
        pstQosSetPara->stMinQos.ucTraffHandlePrior    = pstQosQueryPara->stMinQos.ucTraffHandlePrior;

        pstQosSetPara->stMinQos.bitOpGtdBitUl = VOS_TRUE;
        pstQosSetPara->stMinQos.ulGtdBitUl    = pstQosQueryPara->stMinQos.ulGuarantBitUl;

        pstQosSetPara->stMinQos.bitOpGtdBitDl  = VOS_TRUE;
        pstQosSetPara->stMinQos.ulGtdBitDl     = pstQosQueryPara->stMinQos.ulGuarantBitDl;

    }
    else
    {
        pstQosSetPara->stMinQos.ucDefined = VOS_FALSE;
        pstQosSetPara->stMinQos.ucCid = ucCid;
    }

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_SetQosPara
 功能描述  : 设置拨号的QOS参数
 输入参数  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucUserCid,
             VOS_UINT8                           ucActCid
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月29日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_PS_SetQosPara(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUserCid,
    VOS_UINT8                           ucActCid
)
{
    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosQueryPara;
    TAF_PS_PDP_QOS_SET_PARA_STRU        stQosSetPara;

    PS_MEM_SET(&stQosQueryPara, 0, sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));
    PS_MEM_SET(&stQosSetPara, 0, sizeof(TAF_PS_PDP_QOS_SET_PARA_STRU));

    /* 判断需要设置的CID是否用户下发的CID相同 */
    if (ucActCid == ucUserCid)
    {
        return VOS_OK;
    }

#ifdef DMT
    /* 获取用户设置的QOS参数 */
    if (VOS_OK != TAF_APS_GetPdpCidQosPara(&stQosQueryPara,
                                           ucUserCid))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Get QOS Fail.");
        return VOS_ERR;
    }

    /* QOS参数转换 */
    AT_PS_TransferQosPara(ucActCid, &stQosQueryPara, &stQosSetPara);

    /* 获取用户设置的QOS参数 */
    if (VOS_OK != TAF_APS_SetPdpCidQosPara(&stQosSetPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Set QOS Fail.");
        return VOS_ERR;
    }
#else
    /* 获取用户设置的QOS参数 */
    if (VOS_OK != TAF_AGENT_GetPdpCidQosPara(usClientId,
                                             ucUserCid,
                                             &stQosQueryPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Get QOS Fail.");
        return VOS_ERR;
    }

    /* QOS参数转换 */
    AT_PS_TransferQosPara(ucActCid, &stQosQueryPara, &stQosSetPara);

    /* 获取用户设置的QOS参数 */
    if (VOS_OK != TAF_AGENT_SetPdpCidQosPara(usClientId,
                                             &stQosSetPara))
    {
        AT_ERR_LOG("AT_PS_SetQosPara: ERROR: Set QOS Fail.");
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_SetupCall
 功能描述  : 建立PS域呼叫
 输入参数  : usClientId       - 端口ID
             ucCallId         - 呼叫实体索引
             pstCallDialParam - 呼叫拨号参数
 输出参数  : 无
 返 回 值  : VOS_OK           - 成功
             VOS_ERR          - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_SetupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    AT_DIAL_PARAM_STRU                 *pstCallDialParam
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) 设置CID上下文参数
     *     -> 失败: 返回ERROR
     *     -> 成功: 继续
     * (2) 发起PS域呼叫
     *     -> 失败: 返回ERROR
     *     -> 成功: 继续
     * (3) 添加CallId映射
     * (4) 设置呼叫PDP类型
     * (5) 设置呼叫CID
     * (6) 设置呼叫状态
     */

    TAF_PS_DIAL_PARA_STRU               stPsDialParamInfo;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stPsDialParamInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* 设置QOS参数 */
    if (VOS_OK != AT_PS_SetQosPara(usClientId, AT_PS_GetUserInfo(usClientId, ucCallId)->ucUsrCid, pstCallDialParam->ucCid))
    {
        return VOS_ERR;
    }

    /* 填写PS呼叫参数 */
    AT_GetPsDialParamFromAtDialParam(&stPsDialParamInfo, pstCallDialParam);

    /* 发起PS域呼叫 */
    ulRslt = TAF_PS_CallOrig(WUEPS_PID_AT, usClientId, 0, &stPsDialParamInfo);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_PS_SetupCall: Setup call failed.");
        return VOS_ERR;
    }

    /* 添加CALLID映射 */
    AT_PS_AssignCallIdToCid(usClientId, stPsDialParamInfo.ucCid, ucCallId);

    /* 设置呼叫PDP类型 */
    AT_PS_SetCurrCallType(usClientId, ucCallId, stPsDialParamInfo.enPdpType);

    /* 设置呼叫CID */
    AT_PS_SetCid2CurrCall(usClientId, ucCallId, stPsDialParamInfo.enPdpType, stPsDialParamInfo.ucCid);

    /* 设置呼叫状态 */
    AT_PS_SetCallStateByType(usClientId, ucCallId, stPsDialParamInfo.enPdpType, AT_PDP_STATE_ACTING);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_HangupCall
 功能描述  : 挂断PS域呼叫
 输入参数  : usClientId       - 端口ID
             ucCallId - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_OK   - 成功
             VOS_ERR  - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_HangupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* (1) 检查IPv4类型呼叫是否已建立/正在建立
     *     -> 是: 断开该呼叫, 设置呼叫状态
     *     -> 否: 继续
     * (2) 检查IPv6类型呼叫是否已建立/正在建立
     *     -> 是: 断开该呼叫, 设置呼叫状态
     *     -> 否: 继续
     * (3) 结束
     */
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity = AT_PS_GetCallEntity(usClientId, ucCallId);

    if ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv4State)
      || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv4State) )
    {
        if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                     usClientId,
                                     0,
                                     pstCallEntity->ucIpv4Cid))
        {
            AT_PS_SetCallStateByType(usClientId, ucCallId, TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_PS_HangupCall: STEP1->End call failed.");
            return VOS_ERR;
        }
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if ( (pstCallEntity->ucIpv4Cid != pstCallEntity->ucIpv6Cid)
      && ( (AT_PDP_STATE_ACTED == pstCallEntity->enIpv6State)
        || (AT_PDP_STATE_ACTING == pstCallEntity->enIpv6State) ) )
    {
        if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                     usClientId,
                                     0,
                                     pstCallEntity->ucIpv6Cid))
        {
            AT_PS_SetCallStateByType(usClientId, ucCallId, TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
        }
        else
        {
            AT_ERR_LOG("AT_PS_HangupCall: STEP2->End call step2 failed.");
            return VOS_ERR;
        }
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcConflictDialUpWithCurrCall
 功能描述  : 处理拨号连接建立冲突
 输入参数  : ucIndex  - 端口号(ClientId)索引
             ucCallId - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_OK   - 成功
             VOS_ERR  - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ProcConflictDialUpWithCurrCall(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucCallId
)
{
    /* 呼叫实体索引(CallId)由调用者保证其有效性 */

    /* 如果连接正在建立, 返回OK, 同时上报已建立的连接状态 */
    if (VOS_TRUE == AT_PS_IsLinkGoingUp(ucIndex, ucCallId))
    {
        AT_INFO_LOG("AT_PS_ProcConflictDialUpWithCurrCall: Call is going up.");

        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportCurrCallConnState(ucIndex, ucCallId);

        return VOS_OK;
    }

    /* 如果连接正在断开, 返回ERROR */
    if (VOS_TRUE == AT_PS_IsLinkGoingDown(ucIndex, ucCallId))
    {
        AT_INFO_LOG("AT_PS_ProcConflictDialUpWithCurrCall: Call is going down.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        At_FormatResultData(ucIndex, AT_ERROR);

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcDialUp
 功能描述  : 建立拨号连接
 输入参数  : ucIndex    - 端口号(ClientId)索引
 输出参数  : 无
 返 回 值  : AT_OK      - 上报OK
             AT_ERROR   - 上报ERROR
             AT_SUCCESS - 不上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ProcDialUp(VOS_UINT8 ucIndex)
{
    /* (1) 将CID翻译成呼叫实体索引(CallId)
     * (2) 获取拨号参数
     * (3) 检查呼叫实体索引有效性
     *     -> 有效: 根据连接状态上报处理结果
     *     -> 无效: 继续处理
     * (4) 创建呼叫实体
     * (5) 发起呼叫
     */
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    AT_PS_USER_INFO_STRU                stUserInfo;
    AT_DIAL_PARAM_STRU                  stUsrDialParam;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stUserInfo, 0x00, sizeof(AT_PS_USER_INFO_STRU));
    PS_MEM_SET(&stUsrDialParam, 0x00, sizeof(AT_DIAL_PARAM_STRU));

    /* 获取用户信息 */
    AT_PS_ParseUsrInfo(ucIndex, &stUserInfo);

    /* 获取拨号参数 */
    ulRslt = AT_PS_ParseUsrDialParam(ucIndex, &stUsrDialParam);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_PS_ProcDialUp: Get dial parameter failed.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* 获取CID关联的呼叫实体索引 */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, stUsrDialParam.ucCid);

    if (AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        ulRslt = AT_PS_ProcConflictDialUpWithCurrCall(ucIndex, ucCallId);

        if (VOS_OK != ulRslt)
        {
            AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

            AT_PS_FreeCallEntity(ucIndex, ucCallId);

            AT_ERR_LOG("AT_PS_ProcCallDialUp: Call entity status error.");
            return AT_ERROR;
        }

        return AT_SUCCESS;
    }

    /* 创建呼叫实体 */
    ulRslt = AT_PS_AllocCallEntity(ucIndex, &ucCallId);

    if (VOS_OK != ulRslt)
    {
        AT_NORM_LOG("AT_PS_ProcDialUp: Alloc call entity failed.");

        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    /* 保存用户信息 */
    pstCallEntity->stUserInfo = stUserInfo;

    /* 保存拨号参数 */
    pstCallEntity->stUsrDialParam = stUsrDialParam;

    /* 建立呼叫 */
    ulRslt = AT_PS_SetupCall(stUserInfo.enUserIndex, ucCallId, &stUsrDialParam);

    if (VOS_OK != ulRslt)
    {
        /* 记录呼叫错误码 */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        /* 释放呼叫实体 */
        AT_PS_FreeCallEntity(ucIndex, ucCallId);

        AT_ERR_LOG("AT_PS_ProcDialUp: Setup call failed.");
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcDialUp
 功能描述  : 断开拨号连接
 输入参数  : ucIndex    - 端口号(ClientId)索引
 输出参数  : 无
 返 回 值  : AT_OK      - 上报OK
             AT_ERROR   - 上报ERROR
             AT_SUCCESS - 不上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ProcDialDown(VOS_UINT8 ucIndex)
{
    /* (1) 将CID翻译成呼叫实体索引(CallId)
     * (2) 检查呼叫实体索引有效性
     *     -> 无效: 直接上报连接断开
     *     -> 有效: 继续
     * (3) 检查连接状态
     * (4) 断开呼叫
     */

    /* 获取CID关联的呼叫实体索引(CallId)
     * (A) CallId无效
     *     -> 上报OK
     *     -> 上报所有连接^DEND(or NDISSTAT)
     *     -> 返回
     * (B) CallId有效
     *     -> 继续处理
     */
    VOS_UINT8                           ucCallId;
    AT_PS_USER_INFO_STRU               *pstUserInfo = VOS_NULL_PTR;

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    pstUserInfo = AT_PS_GetUserInfo(ucIndex, ucCallId);

    if (VOS_FALSE ==  AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportAllCallEndState(ucIndex);

        return AT_SUCCESS;
    }

    /* 检查连接状态是否为正在断开
     * (A) 如果连接正在断开
     *　　 -> 上报OK
     *     -> 上报已断开连接^DEND(or NDISSTAT)
     *     -> 返回SUCCESS
     * (B) 其他状态
     *     -> 继续处理
     */
    if (VOS_TRUE == AT_PS_IsLinkGoingDown(ucIndex, ucCallId))
    {
        At_FormatResultData(ucIndex, AT_OK);

        AT_PS_ReportCurrCallEndState(ucIndex, ucCallId);

        return AT_SUCCESS;
    }

    /* 挂断呼叫 */
    if (VOS_OK != AT_PS_HangupCall(pstUserInfo->enUserIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ProcDialDown: Hangup call failed.");
        return AT_ERROR;
    }
    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcDialCmd
 功能描述  : 处理拨号命令
 输入参数  : ucIndex  - 端口号(ClientId)索引
 输出参数  : 无
 返 回 值  : AT错误码 - 解析器根据错误码上报结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_ProcDialCmd(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* 检查参数有效性 */
    ulRslt = AT_PS_ValidateDialParam(ucIndex);

    if (AT_SUCCESS != ulRslt)
    {
        /* 记录PS域呼叫错误码 */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return ulRslt;
    }

    if (0 != gastAtParaList[1].ulParaValue)
    {
        ulRslt = AT_PS_ProcDialUp(ucIndex);
    }
    else
    {
        ulRslt = AT_PS_ProcDialDown(ucIndex);
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcSharePdpStateChange
 功能描述  : PDP状态变化时，Share PDP特性相关的处理
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目新增

  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，函数拆为激活和去激活处理
*****************************************************************************/
VOS_VOID  AT_PS_ProcDeactSharePdpState(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity  = VOS_NULL_PTR;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc  = VOS_NULL_PTR;

    /* SHARE-PDP特性未开启，直接返回 */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* 获取APP PDP实体信息 */
    pstAppPdpEntity                         = AT_APP_GetPdpEntInfoAddr();
    pstAppPdpEntity->stUsrInfo.enPortIndex  = AT_CLIENT_TAB_APP_INDEX;
    pstAppPdpEntity->stUsrInfo.ucUsrType    = AT_APP_USER;

    /* 获取连接断开结果上报函数指针 */
    pRptEndRsltFunc = AT_PS_GetRptEndResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    AT_PS_SendRnicPdnInfoRelInd(pstEvent->ucRabId);

    /* 通知APP模块PDP去激活 */
    if (VOS_NULL_PTR != pRptEndRsltFunc)
    {
        pRptEndRsltFunc(pstEvent->ucCid,
                        pstAppPdpEntity->stUsrInfo.enPortIndex,
                        enPdpType,
                        pstEvent->enCause);
    }
    else
    {
        AT_ERR_LOG("AT_PS_ProcDeactSharePdpState:ERROR: Get End Report Func Failed!");
    }

    /* 清除APP PDP实体 */
    AT_PS_ResetRnicPdpDhcpPara(enPdpType);

    return;
}

/*****************************************************************************
 函 数 名  : AT_PS_ProcActSharePdpState
 功能描述  : PDP状态变化为激活时，Share PDP特性相关的处理
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目新增

  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，函数拆为激活和去激活处理
*****************************************************************************/
VOS_VOID  AT_PS_ProcActSharePdpState(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity  = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc = VOS_NULL_PTR;

    /* SHARE-PDP特性未开启，直接返回 */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* 获取APP PDP实体信息 */
    pstAppPdpEntity                         = AT_APP_GetPdpEntInfoAddr();
    pstAppPdpEntity->stUsrInfo.enPortIndex  = AT_CLIENT_TAB_APP_INDEX;
    pstAppPdpEntity->stUsrInfo.ucUsrType    = AT_APP_USER;

    /* 获取连接建立结果上报函数指针 */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    if (TAF_PDP_IPV4 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV4, pstEvent);
        AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV4, pstEvent->ucRabId, AT_APP_GetPdpEntInfoAddr());

        /* 通知APP模块IPv4激活 */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstEvent->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcActSharePdpState:ERROR: Get Connet Report Func Failed!");
        }
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (TAF_PDP_IPV6 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV6, pstEvent);
    }

    if (TAF_PDP_IPV4V6 == enPdpType)
    {
        AT_PS_SaveRnicPdpDhcpPara(TAF_PDP_IPV4V6, pstEvent);
        AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV4, pstEvent->ucRabId, AT_APP_GetPdpEntInfoAddr());

        /* 通知APP模块IPv4激活 */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstEvent->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV4);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcActSharePdpState:ERROR: Get Connet Report Func Failed!");
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_PS_ProcSharePdpIpv6RaInfo
 功能描述  : Share-PDP特性开启情况下，收到Router Advertisement IP报文, 存储相应PDN信息
 输入参数  : pstRaInfoNotifyInd         - RA报文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增

*****************************************************************************/
VOS_VOID AT_PS_ProcSharePdpIpv6RaInfo(
    TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity                      = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr                     = VOS_NULL_PTR;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc                     = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[TAF_IPV6_ADDR_LEN] = {0};

    /* SHARE-PDP特性未开启，直接返回 */
    if (VOS_TRUE != AT_PS_GET_SHARE_PDP_FLG())
    {
        return;
    }

    /* RaInfo消息中地址前缀为空时，直接返回 */
    if (0 == pstRaInfoNotifyInd->stIpv6RaInfo.ulPrefixNum)
    {
        AT_NORM_LOG("AT_PS_ProcSharePdpIpv6RaInfo: No IPv6 prefix address in RA.");
        return;
    }

    /* 获取APP PDP实体、RaInfo信息 */
    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();

    /* 获取连接建立结果上报函数指针 */
    pRptConnRsltFunc = AT_PS_GetRptConnResultFunc(pstAppPdpEntity->stUsrInfo.ucUsrType);

    /* 获取到IPv6地址前缀后, 上报已连接结果^DCONN */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        /* 通知APP模块IPv6激活 */
        if (VOS_NULL_PTR != pRptConnRsltFunc)
        {
            pRptConnRsltFunc(pstRaInfoNotifyInd->ucCid,
                             pstAppPdpEntity->stUsrInfo.enPortIndex,
                             TAF_PDP_IPV6);
        }
        else
        {
            AT_ERR_LOG("AT_PS_ProcSharePdpIpv6RaInfo:ERROR: Get Connet Report Func Failed!");
        }

        /* 记录IPv6前缀 */
        pstAppRaInfoAddr->bitOpPrefixAddr        = VOS_TRUE;
        pstAppRaInfoAddr->ulPrefixBitLen         = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen;
        PS_MEM_CPY(pstAppRaInfoAddr->aucPrefixAddr,
                   pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   TAF_IPV6_ADDR_LEN);

        /* 计算IPv6全局地址 */
        AT_PS_GenIpv6LanAddrWithRadomIID(pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                         pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                         aucIpv6LanAddr);

        /* 记录IPv6全局地址 */
        pstAppRaInfoAddr->bitOpLanAddr           = VOS_TRUE;
        PS_MEM_CPY(pstAppRaInfoAddr->aucLanAddr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* 更新DHCPV6信息中的IPv6全局地址 */
        PS_MEM_CPY(pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);
    }

    /* 记录Preferred Lifetime */
    pstAppRaInfoAddr->bitOpPreferredLifetime = VOS_TRUE;
    pstAppRaInfoAddr->ulPreferredLifetime    = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulPreferredLifeTime;

    /* 记录Valid Lifetime */
    pstAppRaInfoAddr->bitOpValidLifetime     = VOS_TRUE;
    pstAppRaInfoAddr->ulValidLifetime        = pstRaInfoNotifyInd->stIpv6RaInfo.astPrefixList[0].ulValidLifeTime;

    /* 记录IPv6 MTU */
    if (VOS_TRUE == pstRaInfoNotifyInd->stIpv6RaInfo.bitOpMtu)
    {
        pstAppRaInfoAddr->bitOpMtuSize       = VOS_TRUE;
        pstAppRaInfoAddr->ulMtuSize          = pstRaInfoNotifyInd->stIpv6RaInfo.ulMtu;
    }

    /* 发送RNIC PDN配置消息 */
    AT_PS_SendRnicPdnInfoCfgInd(TAF_PDP_IPV6, pstRaInfoNotifyInd->ucRabId, AT_APP_GetPdpEntInfoAddr());

    return;
}
#endif

/******************************************************************************
 函 数 名  : AT_PS_SaveRnicPdpDhcpPara
 功能描述  : 收到NDIS PDP激活成功消息后，保存DHCP信息到APP PDP实体中
 输入参数  : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : z00214637
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID AT_PS_SaveRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    switch(enPdpType)
    {
        case TAF_PDP_IPV4:

            /* 清除DHCP信息 */
            AT_AppDhcpReset();

            /* 记录IPv4类型PDP对应的CID */
            pstAppPdpEntity->ucIpv4Cid  = pstEvent->ucCid;

            /* PDP状态切换到激活状态 */
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_ACTED);

            /* 处理IPv4类型的DHCP */
            AT_CtrlConnIndProc(pstEvent, AT_APP_USER);
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* 清除DHCPv6信息 */
            AT_AppDhcpv6Reset();

            /* 记录PDP类型对应的CID */
            pstAppPdpEntity->ucIpv6Cid  = pstEvent->ucCid;

            /* 将本IPv6类型状态切换到激活状态 */
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_ACTED);

            /* 处理IPV6地址 */
            AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);
            break;

        case TAF_PDP_IPV4V6:
            /* 清除DHCP信息 */
            AT_AppDhcpReset();

            /* 清除DHCPv6信息 */
            AT_AppDhcpv6Reset();

            /* 记录PDP类型对应的CID */
            pstAppPdpEntity->ucIpv4v6Cid   = pstEvent->ucCid;

            /* 将本IPv6类型状态切换到激活状态 */
            AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_ACTED);

            /* 处理IPV4地址 */
            AT_CtrlConnIndProc(pstEvent, AT_APP_USER);

            /* 处理IPV6地址*/
            AT_AppCtrlConnIpv6IndProc(pstAppPdpEntity, pstEvent);
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_SaveRnicPdpDhcpPara:PDP type is invaild!");
            break;
    }
}

/******************************************************************************
 函 数 名  : AT_PS_ResetRnicPdpDhcpPara
 功能描述  : 收到NDIS PDP去激活成功消息后，重置AppPdpEntity
 输入参数  : ucPdpType - PDP类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : z00214637
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID AT_PS_ResetRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
)
{
    switch(ucPdpType)
    {
        case TAF_PDP_IPV4:
            /* 将IPv4类型的PDP切换到IDLE态 */
            AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_IDLE);

            /* 清除DHCP信息 */
            AT_AppDhcpReset();
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
            /* 将IPv6类型的PDP切换到IDLE态 */
            AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_IDLE);

            /* 清除DHCPv6信息 */
            AT_AppDhcpv6Reset();
            break;

        case TAF_PDP_IPV4V6:
            /* 将IPv4\IPv6类型的PDP切换到IDLE态 */
            AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_IDLE);

            /* 清除DHCP\DHCPv6信息 */
            AT_AppDhcpReset();
            AT_AppDhcpv6Reset();
            break;
#endif

        default:
            AT_WARN_LOG("AT_PS_ResetRnicPdpDhcpPara:PDP type is invaild!");
            break;
    }
}

/*****************************************************************************
 函 数 名  : AT_PS_SendRnicPdnInfoCfgInd
 功能描述  : 向RNIC发送PDN配置请求信息
 输入参数  : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             VOS_UINT8                           ucRabId,
             AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
  2.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2015031000157, 新增第三个p-cscf地址
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoCfgInd(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    VOS_UINT8                           ucRabId,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
)
{

    AT_RNIC_PDN_INFO_CFG_IND_STRU      *pstRnicPdnCfgInd;

    /* 申请AT_RNIC_PDN_INFO_CFG_IND_STRU消息 */
    pstRnicPdnCfgInd = (AT_RNIC_PDN_INFO_CFG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_AT,
                        sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU));

    if (VOS_NULL_PTR == pstRnicPdnCfgInd)
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd: Alloc Msg Fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstRnicPdnCfgInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstRnicPdnCfgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRnicPdnCfgInd->ulReceiverPid   = ACPU_PID_RNIC;

    /* 填写消息内容 */
    pstRnicPdnCfgInd->enMsgId   = ID_AT_RNIC_PDN_INFO_CFG_IND;
    pstRnicPdnCfgInd->ucRabId   = ucRabId;
    pstRnicPdnCfgInd->ucRmNetId = RNIC_RMNET_ID_0;

    if (TAF_PDP_IPV4 == ucPdpType)
    {
        pstRnicPdnCfgInd->bitOpIpv4PdnInfo  = VOS_TRUE;

        /* 填充IPv4 PDN信息 */
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPdnAddr       = pstAppPdpEntity->stIpv4Dhcp.ulIpv4Addr;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulSubnetMask    = pstAppPdpEntity->stIpv4Dhcp.ulIpv4NetMask;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulGateWayAddr   = pstAppPdpEntity->stIpv4Dhcp.ulIpv4GateWay;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulDnsPrimAddr   = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimDNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulDnsSecAddr    = pstAppPdpEntity->stIpv4Dhcp.ulIpv4SecDNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulWinnsPrimAddr = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimWINNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulWinnsSecAddr  = pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4SecWINNS;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfPrimAddr = pstAppPdpEntity->stIpv4Dhcp.ulIpv4PrimPCSCF;
        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfSecAddr  = pstAppPdpEntity->stIpv4Dhcp.bitOpIpv4Secpcscf;

        pstRnicPdnCfgInd->stIpv4PdnInfo.ulPcscfThiAddr  = pstAppPdpEntity->stIpv4Dhcp.ulIpv4ThiPCSCF;

    }
    else if(TAF_PDP_IPV6 == ucPdpType)
    {
        pstRnicPdnCfgInd->bitOpIpv6PdnInfo              = VOS_TRUE;

        /* 填充IPv6 PDN信息 */
        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPdnAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsPrimAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucDnsSecAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfPrimAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfSecAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstRnicPdnCfgInd->stIpv6PdnInfo.aucPcscfThiAddr,
                   pstAppPdpEntity->stIpv6Dhcp.aucThiPcscfAddr,
                   TAF_IPV6_ADDR_LEN);

    }
    else
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd:PDP type is invaild!");

        PS_FREE_MSG(WUEPS_PID_AT, pstRnicPdnCfgInd);
        return VOS_OK;
    }

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRnicPdnCfgInd))
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoCfgInd: Send Msg Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_PS_SendRnicPdnInfoRelInd
 功能描述  : 向RNIC发送PDN连接释放请求消息
 输入参数  : AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoRelInd(
    VOS_UINT8                           ucRabId
)
{
    AT_RNIC_PDN_INFO_REL_IND_STRU      *pstRnicPdnRelInd;

    /* 申请AT_RNIC_PDN_INFO_REL_IND_STRU消息，并初始化 */
    pstRnicPdnRelInd = (AT_RNIC_PDN_INFO_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_AT,
                        sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU));

    if (VOS_NULL_PTR == pstRnicPdnRelInd)
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoRelInd: Alloc Msg Fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR *)pstRnicPdnRelInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_RNIC_PDN_INFO_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头 */
    pstRnicPdnRelInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRnicPdnRelInd->ulReceiverPid   = ACPU_PID_RNIC;

    /* 填写消息内容 */
    pstRnicPdnRelInd->enMsgId         = ID_AT_RNIC_PDN_INFO_REL_IND;
    pstRnicPdnRelInd->ucRabId         = ucRabId;
    pstRnicPdnRelInd->ucRmNetId       = RNIC_RMNET_ID_0;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRnicPdnRelInd))
    {
        AT_WARN_LOG("AT_PS_SendRnicPdnInfoRelInd: Send Msg Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Deleted by m00217266 for L-C互操作项目, 2014-1-23, begin */
#if 0
/*****************************************************************************
 函 数 名  : AT_QosParaTransferToQci
 功能描述  : 根据QOS参数转换为QCI等级
 输入参数  : TAF_UMTS_QOS_STRU                   *pQos
 输出参数  : 无
 返 回 值  : QCI类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : 新生成函数

*****************************************************************************/
ADS_QCI_TYPE_ENUM_UINT8 AT_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                  *pQos
)
{
    ADS_QCI_TYPE_ENUM_UINT8             enQci;

    /* 转换规则参见: 23.401
       Annex E (normative):
        Mapping between EPS and Release 99 QoS parameters
        QCI    Traffic_Class  Traffic_Handling_Priority Signalling_Indication  Src_Stats_Descriptor
         1     Conversational          NA                       NA                  SPEECH
         2     Conversational          NA                       NA                    NA
         3     Conversational          NA                       NA                   Unknown
         4     Streaming               NA                       NA                   Unknown
         5     Interactive              1                       YES                  Unknown
         6     Interactive              1                       NO                    NA
         7     Interactive              2                       NO                    NA
         8     Interactive              3                       NO                    NA
         9     Background              NA                       NA                    NA

      NOTE°1: When QCI 2 is mapped to Release 99 QoS parameter values, the Transfer Delay parameter
               is set to 150 ms. When Release 99 QoS parameter values are mapped to a QCI,
               QCI 2 is used for conversational/unknown if the Transfer Delay parameter is greater
               or equal to 150 ms.
      NOTE°2: When QCI 3 is mapped to Release 99 QoS parameter values, the Transfer Delay parameter
               is set to 80 ms as the lowest possible value, according to TS 23.107 [59]. When Release
               99 QoS parameter values are mapped to a QCI, QCI 3 is used for conversational/unknown if
               the Transfer Delay parameter is lower than 150 ms.
      NOTE  3: When QCI 4 is mapped to Release 99 QoS parameter values, it is mapped to Streaming/Unknown.
               When Release 99 QoS parameter values are mapped to a QCI, Streaming/Unknown and Streaming/Speech
               are both mapped to QCI 4.
    */
    /* 根据QOS trafficClass参数获取QCI */
    if (AT_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL == pQos->ucTrafficClass)
    {
        if (AT_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH == pQos->ucSrcStatisticsDescriptor)
        {
            enQci       = ADS_QCI_TYPE_QCI1_GBR;
        }
        else if (pQos->usTransDelay >= AT_APP_QOS_TRANSFER_DELAY_150MS)
        {
            enQci       = ADS_QCI_TYPE_QCI2_GBR;
        }
        else
        {
            enQci       = ADS_QCI_TYPE_QCI3_GBR;
        }
    }
    else if (AT_APP_QOS_TRAFFIC_CLASS_STREAMING == pQos->ucTrafficClass)
    {
        enQci       = ADS_QCI_TYPE_QCI4_GBR;
    }
    else if (AT_APP_QOS_TRAFFIC_CLASS_INTERACTIVE == pQos->ucTrafficClass)
    {
        if (AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1 == pQos->ucTraffHandlePrior)
        {
            if (AT_APP_QOS_SIGNAL_IND_OPTIMISE == pQos->ucSignallingIndication)
            {
                enQci       = ADS_QCI_TYPE_QCI5_NONGBR;
            }
            else
            {
                enQci       = ADS_QCI_TYPE_QCI6_NONGBR;
            }
        }
        else if (AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2 == pQos->ucTraffHandlePrior)
        {
            enQci       = ADS_QCI_TYPE_QCI7_NONGBR;
        }
        else
        {
            enQci       = ADS_QCI_TYPE_QCI8_NONGBR;
        }
    }
    else
    {
        enQci       = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    return enQci;
}
#endif
#if 0
/* Modified by l60609 for L-C互操作项目, 2014-1-14, begin */
/*****************************************************************************
 函 数 名  : AT_SendAdsPdpStatusInd
 功能描述  : AT向ADS发送消息
 输入参数  : VOS_UINT32                          ulPid,
             ADS_PDP_STATUS_IND_STRU            *pstAdsInd
 输出参数  : 无
 返 回 值  : 成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月18日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2011年12月20日
    作    者   : C00173809
    修改内容   : ps融合项目，向上下行ADS发送消息
  3.日    期   : 2012年2月24日
    作    者   : L47619
    修改内容   : V7R1C50 IPC项目:向ADS增加QCI优先级的发送
  4.日    期   : 2013年1月5日
    作    者   : l60609
    修改内容   : DSDA Phase II
  5.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
  6.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换后重构该函数
*****************************************************************************/
VOS_UINT32 AT_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
)
{
    ADS_PDP_STATUS_IND_STRU            *pstMsg;

    /* 申请ADS_PDP_STATUS_IND_STRU消息 */
    pstMsg = (ADS_PDP_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(ADS_PDP_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_SendAdsPdpStatusInd: alloc msg fail!");
        return VOS_ERR;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_PDP_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->enMsgId         = ID_APS_ADS_PDP_STATUS_IND;

    /* 填写消息体 */
    pstMsg->enModemId       = pstAdsInd->enModemId;
    pstMsg->ucRabId         = pstAdsInd->ucRabId;
    pstMsg->enPdpStatus     = pstAdsInd->enPdpStatus;
    pstMsg->enPdpType       = pstAdsInd->enPdpType;
    pstMsg->enQciType       = pstAdsInd->enQciType;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_SendAdsPdpStatusInd: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_NotifyAdsWhenPdpModify
 功能描述  : 当发生PDP MODIFY(UE发起或网侧发起)时，向ADS指示发生了PDP修改
 输入参数  : pstEvt       TAF_PS_CALL_EVENT_STRU事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : 新生成函数
  2.日    期   : 2013年1月5日
    作    者   : l60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP RPOJECT
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU     *pstEvent
)
{
    VOS_UINT32                          ulRet;
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &stAdsInd.enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_NotifyAdsWhenPdpModify:Get Modem Id fail");
        return;
    }

    /* 填写参数 */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_MODIFY;
    stAdsInd.enPdpType      = TAF_PDP_TYPE_BUTT;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = AT_QosParaTransferToQci(&pstEvent->stUmtsQos);

    /* 向ADS_DL发送PDP修改指示 */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* 向ADS_UL发送PDP修改指示 */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}

/*****************************************************************************
 函 数 名  : AT_NotifyAdsWhenPdpAvtivated
 功能描述  : 通知ADS承载激活
 输入参数  : pstEvent - 承载激活事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2013年1月5日
    作    者   : l60609
    修改内容   : DSDA Phase II
  3.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP RPOJECT
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
)
{
    VOS_UINT32                          ulRet;
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &stAdsInd.enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_NotifyAdsWhenPdpAvtivated:Get Modem Id fail");
        return;
    }

    /* 填写参数 */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_ACT;
    stAdsInd.enPdpType      = pstEvent->stPdpAddr.enPdpType;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = AT_QosParaTransferToQci(&pstEvent->stUmtsQos);

    /* 向ADS_DL发送PDP修改指示 */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* 向ADS_UL发送PDP修改指示 */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}

/*****************************************************************************
 函 数 名  : AT_NotifyAdsWhenPdpDeactivated
 功能描述  : 通知ADS去承载激活
 输入参数  : pstEvent - 承载去激活事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月12日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP RPOJECT
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
)
{
    VOS_UINT32                          ulRet;
    ADS_PDP_STATUS_IND_STRU             stAdsInd;

    PS_MEM_SET(&stAdsInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    stAdsInd.enModemId = MODEM_ID_0;

    ulRet = AT_GetModemIdFromClient((AT_CLIENT_TAB_INDEX_UINT8)(pstEvent->stCtrl.usClientId), &stAdsInd.enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_NotifyAdsWhenPdpAvtivated:Get Modem Id fail");
        return;
    }

    /* 填写参数 */
    stAdsInd.enPdpStatus    = ADS_PDP_STATUS_DEACT;
    stAdsInd.enPdpType      = pstEvent->enPdpType;
    stAdsInd.ucRabId        = pstEvent->ucRabId;
    stAdsInd.enQciType      = ADS_QCI_TYPE_BUTT;

    /* 向ADS_DL发送PDP修改指示 */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_DL,
                           &stAdsInd);

    /* 向ADS_UL发送PDP修改指示 */
    AT_SendAdsPdpStatusInd(ACPU_PID_ADS_UL,
                           &stAdsInd);

    return;
}
/* Modified by l60609 for L-C互操作项目, 2014-1-14, end */
#endif
/* Deleted by m00217266 for L-C互操作项目, 2014-1-23, end */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


