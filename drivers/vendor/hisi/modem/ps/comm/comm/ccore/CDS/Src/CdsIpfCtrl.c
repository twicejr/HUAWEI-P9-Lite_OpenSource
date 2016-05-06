/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsIpfCtrl.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年3月9日
  最近修改   :
  功能描述   : 实现对上下行IPF通道的管理、配置
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsDebug.h"
#include "CdsUlProc.h"
#include "CdsDlProc.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_IPF_CTRL_C
/*lint +e767*/

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/

CDS_IPF_CTRL_ENTITY_STRU    g_stCdsIpfCtrlEntity = {0};

/******************************************************************************
   5 函数实现
******************************************************************************/


/*****************************************************************************
 函 数 名  : CDS_GetTtfMemCnt
 功能描述  : 获得TTF_MEM_ST中内存块的个数，用于计算使用的IPF CD个数
 输入参数  :
 输出参数  : 无
 返 回 值  : TTF链表的个数

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_GetTtfMemCnt(TTF_MEM_ST *pstTtfMem)
{
    VOS_UINT32    ulCnt;
    TTF_MEM_ST   *pstNext;

    if (VOS_NULL_PTR == pstTtfMem)
    {
        return 0;
    }

    pstNext = pstTtfMem;
    ulCnt = 0;

    while (VOS_NULL_PTR != pstNext)
    {
        ulCnt ++;
        pstNext = pstNext->pNext;
    }

    return ulCnt;
}


/*****************************************************************************
 函 数 名  : CDS_AllocTtfMem
 功能描述  : 申请TTF内存

 输入参数  : VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : TTF_MEM_ST*
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月13日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
TTF_MEM_ST* CDS_AllocTtfMem(VOS_UINT32 ulLen)
{
    TTF_MEM_ST   *pstTtf;

    if ((0 == ulLen) || (CDS_DL_SDU_MAX_LEN < ulLen))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_AllocTtfMem : Input Length Err.",ulLen);
        CDS_PRINT_ERROR1(CDS_AllocTtfMem_ENUM,CDS_PRINT_PARA_INPUT_ERR,ulLen);
        return VOS_NULL_PTR;
    }

    /*申请内存，指针需要移位*/
    pstTtf = TTF_MemBlkAlloc(UEPS_PID_CDS,
                             TTF_MEM_POOL_ID_UL_IP_DATA,
                             (VOS_UINT16)(ulLen + CDS_UL_RESV_LEN_FOR_PDU_HDR));

    if (VOS_NULL_PTR == pstTtf)
    {
        return VOS_NULL_PTR;
    }

    /*进行指针偏移*/
    pstTtf->usUsed = (VOS_UINT16)ulLen + CDS_UL_RESV_LEN_FOR_PDU_HDR;
    TTF_MEM_REMOVE_FROM_HDR(pstTtf, CDS_UL_RESV_LEN_FOR_PDU_HDR);
    pstTtf->ucReserve = 0;

    return pstTtf;
}

/*****************************************************************************
 函 数 名  : CDS_UlIpfIntCB
 功能描述  : IP过滤完成中断处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32 CDS_UlIpfIntCB(VOS_VOID)
{
    CDS_DBG_RECV_UL_IPF_INT(1);
    CDS_SendEventToCds(CDS_EVENT_UL_IPF_INT);
    return 0;
}


/*****************************************************************************
 函 数 名  : CDS_InitDlIPFFilter
 功能描述  : 初始化下行IPF过滤器
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_InitDlIpfFilter(VOS_VOID)
{
    IPF_FILTER_CONFIG_S    *pstFilter;

    /*Mem Set */
    PS_MEM_SET(g_stCdsIpfCtrlEntity.stFilterCfgStru.astDlFilter,
               0,
               sizeof(IPF_FILTER_CONFIG_S) * CDS_IPF_MAX_DL_FILTER_NUM);

    /* 下行DHCPv4 Filter定义, IPV4-UDP-Dest Port 68 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_DHCP4);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_DHCP4;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V4);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,17);
    CDS_DL_IPF_FILTER_SET_PORT_HI(pstFilter,68);
    CDS_DL_IPF_FILTER_SET_PORT_LOW(pstFilter,68);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_DHCPV4);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);


    /* 下行DHCPv6 Filter定义, UDP目的端口546 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_DHCP6);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_DHCP6;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,17);
    CDS_DL_IPF_FILTER_SET_PORT_HI(pstFilter,546);
    CDS_DL_IPF_FILTER_SET_PORT_LOW(pstFilter,546);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_DHCPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*下行ICMP Router Solicitation Filter定义, 协议号58，Type 133， code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_RS);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_RS;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,133);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);


    /*下行ICMP Router Advertisement Filter定义, 协议号58，Type 134， code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_RA);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_RA;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,134);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*下行ICMP Neighbor Solicitation Filter定义, 协议号58，Type 135， code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_NS);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_NS;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,135);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*下行ICMP Neighbor Advertisement Filter定义, 协议号58，Type 136， code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_NA);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_NA;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,136);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*下行ICMP REDIRECT Filter定义, 协议号58，Type 137， code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_REDIRECT);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_REDIRECT;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,137);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*上行NDIS ICMP ECHO REQUEST定义, 协议号58，Type 128， code 0，目的地址为FE80打头 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_LL_PING6);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_LL_PING6;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,128);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FE80(pstFilter);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*上行NDIS 目的地址FE80打头定义 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_LL_FE80);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_LL_FE80;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FE80(pstFilter);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,1);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_LL_FE80);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*上行NDIS 目的地址FF打头定义 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_LL_FF);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_LL_FF;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FF(pstFilter);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,1);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_LL_FF);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    g_stCdsIpfCtrlEntity.stFilterCfgStru.ulDownLinkUsedNum = 10;

    return;
}

/*****************************************************************************
 函 数 名  : CDS_StartAdqEmptyProctectTmr
 功能描述  : 启动ADQ空保护定时器定时器
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_StartAdqEmptyProctectTmr(VOS_VOID)
{

    /*已运行*/
    if (VOS_NULL_PTR != CDS_GET_ADQ_EMPTY_TMR_PTR())
    {
        return PS_SUCC;
    }

    if (VOS_OK != PS_START_REL_TIMER(&(CDS_GET_ADQ_EMPTY_TMR_PTR()),
                                    UEPS_PID_CDS,
                                    CDS_IPF_AD_EMPTY_PROTECT_TMR_LEN,
                                    CDS_TMR_ID_ADQ_EMPTY_PROCTECT,
                                    0,
                                    VOS_RELTIMER_NOLOOP))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_StartAdqEmptyProctectTmr : Start Timer Fail ");
        CDS_PRINT_ERROR(CDS_StartAdqEmptyProctectTmr_ENUM,CDS_PRINT_START_TIMER_FAIL);
        return PS_FAIL;
    }

    CDS_DBG_UL_ADQ_START_EMPTY_TMR_NUM(1);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : CDS_StopAdqEmptyProctectTmr
 功能描述  : 停止ADQ空保护定时器
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_StopAdqEmptyProctectTmr(VOS_VOID)
{
    /*已停止*/
    if (VOS_NULL_PTR == CDS_GET_ADQ_EMPTY_TMR_PTR())
    {
        return ;
    }

    if (VOS_OK != PS_STOP_REL_TIMER(&(CDS_GET_ADQ_EMPTY_TMR_PTR())))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_StopAdqEmptyProctectTmr : Stop Timer Fail ");
        CDS_PRINT_ERROR(CDS_StopAdqEmptyProctectTmr_ENUM,CDS_PRINT_STOP_TIMER_FAIL);
        return ;
    }

    CDS_DBG_UL_ADQ_STOP_EMPTY_TMR_NUM(1);

    return ;
}

/*****************************************************************************
 函 数 名  : CDS_StopAdqEmptyProctectTmr
 功能描述  : 停止ADQ空保护定时器
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_AdqEmptyProctectTimeOutProc(VOS_VOID)
{

    CDS_DBG_UL_ADQ_EMPTY_TMR_TIMEOUT_NUM(1);

    /*停止定时器*/
    CDS_StopAdqEmptyProctectTmr();

    /*补充内存*/
    CDS_AllocMemForAdq();
    return ;
}

/*****************************************************************************
 函 数 名  : CDS_FreeIpfDlSrcMem
 功能描述  : 释放下行IPF Src Mem
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年08月16日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_FreeIpfDlSrcMem(VOS_VOID)
{
    LUP_QUEUE_STRU                   *pstDlFreeQue ;
    VOS_UINT32                           ulIdleCD;
    VOS_UINT32                        ulIdleBD;
    VOS_UINT32                        ulBusyBD;
    VOS_UINT32                        ulCanFree;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    TTF_MEM_ST                       *pstSrcTtf;

    pstDlFreeQue = CDS_IPF_DL_SRCMEM_FREE_QUE();
    CDS_ASSERT(VOS_NULL_PTR != pstDlFreeQue);

    ulQueCnt = LUP_QueCnt(pstDlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    /*get busy bd num*/
    ulIdleBD = LDRV_IPF_GET_DLBD_NUM(&ulIdleCD);
    ulBusyBD = CDS_GET_IPF_DL_MAX_BD_NUM() - ulIdleBD;
    if (ulQueCnt >= ulBusyBD)
    {
        ulCanFree = ulQueCnt - ulBusyBD;
    }
    else
    {
        CDS_ERROR_LOG3(UEPS_PID_CDS, "CDS_FreeIpfDlSrcMem:Buff Num Less IPF Busy BD Num.quecnt,busybd,idlebd",ulQueCnt,ulBusyBD,ulIdleBD);
        CDS_PRINT_ERROR2(CDS_FreeIpfDlSrcMem_ENUM,CDS_PRINT_PARA_ERR,ulQueCnt,ulBusyBD);
        CDS_PRINT_ERROR1(CDS_FreeIpfDlSrcMem_ENUM,CDS_PRINT_PARA_ERR,ulIdleBD);
        PS_PRINTF("CDS_FreeIpfDlSrcMem : src free que less than busy bd. quecnt=%d,busybd=%d,idlebd=%d.\n",ulQueCnt,ulBusyBD,ulIdleBD);
        CDS_DBG_DL_IPF_FREE_SRCMEM_ERROR(1);
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulCanFree; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstDlFreeQue,(VOS_VOID **)&pstSrcTtf))
        {
            return;
        }

        TTF_MemFree(UEPS_PID_CDS,pstSrcTtf);
        CDS_DBG_DL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_AdqEmptyIntCB
 功能描述  : 上行ADQ空中断回调函数
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32 CDS_UlAdqEmptyIntCB(IPF_ADQ_EMPTY_E  eAdqEmpty )
{
    CDS_DBG_UL_RX_ADQ_EMPTY_INT(1);

    /*空事件类型统计*/
    if (IPF_EMPTY_ADQ0 == eAdqEmpty)
    {
        CDS_DBG_UL_ADQ_AD0_EMPTY_INT_NUM(1);
    }
    else if (IPF_EMPTY_ADQ1 == eAdqEmpty)
    {
        CDS_DBG_UL_ADQ_AD1_EMPTY_INT_NUM(1);
    }
    else
    {
        CDS_DBG_UL_ADQ_AD0_EMPTY_INT_NUM(1);
        CDS_DBG_UL_ADQ_AD1_EMPTY_INT_NUM(1);
    }

    /*唤醒CDS处理*/
    CDS_SendEventToCds(CDS_EVENT_UL_ADQ_EMPTY);
    return 0;
}


/*****************************************************************************
 函 数 名  : CDS_IpfInit
 功能描述  : IP过滤功能的初始化.
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月31日
    作    者   : h00133115
    修改内容   : 新生成函数

  2.日    期   : 2013年1月14日
    作    者   : y00151394
    修改内容   : DSDA修改

*****************************************************************************/
VOS_UINT32 CDS_IpfInit(VOS_VOID )
{
    IPF_COMMON_PARA_S stCommPara;
    IPF_CHL_CTRL_S    stChlCtrl;
    struct mdrv_ipf_ops stIpfOps;

    /*初始化ipf注册结构体*/
    stIpfOps.adq_empty_cb = VOS_NULL;
    stIpfOps.rx_complete_cb = VOS_NULL;

    /*初始化时IP过滤的参数配置*/
    stCommPara.bEspSpiDisable  = PS_FALSE;              /* ESP SPI参与匹配控制信号 */
    stCommPara.bAhSpiDisable   = PS_FALSE;              /* AH SPI参与匹配控制信号 */
    stCommPara.bEspAhSel       = PS_TRUE;               /* 0选ESP，1选AH */
    stCommPara.bIpv6NextHdSel  = PS_TRUE;
    stCommPara.eMaxBurst       = IPF_BURST_16;          /* BURST最大长度 */
    stCommPara.bSpWrrModeSel   = PS_FALSE;
    stCommPara.bSpPriSel       = PS_FALSE;              /* SP优先级选择 */
    stCommPara.bFltAddrReverse = PS_FALSE;              /* 扩滤器中地址寄存器大小端排列顺序 0表示大端 */
    stCommPara.bFilterSeq      = PS_FALSE;              /* 过滤器配置顺序指示 */

    /*新增过滤器参数配置*/
    stCommPara.bAdReport       = PS_FALSE;              /* AD上报选择，PS_FALSE:上报结构体指针， PS_TRUE:上报数据指针 */
    stCommPara.bMultiModeEn    = PS_TRUE;               /* 单通道动态模式，PS_TRUE为使能 */
    stCommPara.bMultiFilterChainEn = PS_TRUE;           /* 单通道多过滤器，PS_TRUE为使能*/

    if (IPF_SUCCESS != LDRV_IPF_INIT(&stCommPara))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_INIT Fail!\n");
        return PS_FAIL;
    }

    /*上行通道工作模式: 过滤且搬移，支持链式搬移*/
    stChlCtrl.u32WrrValue      = 16*1024;
    stChlCtrl.bDataChain       = PS_FALSE;
    stChlCtrl.bEndian          = PS_FALSE;
    stChlCtrl.eIpfMode         = IPF_MODE_FILTERANDTRANS;
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_ULCHAN(&stChlCtrl))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_ULCHAN Fail!\n");
        return PS_FAIL;
    }

    /*下行通道工作模式: 过滤且搬移，支持链式搬移*/
    stChlCtrl.u32WrrValue      = 16*1024;
    stChlCtrl.bDataChain       = PS_TRUE;
    stChlCtrl.bEndian          = PS_FALSE;
    stChlCtrl.eIpfMode         = IPF_MODE_FILTERANDTRANS;
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_DLCHAN(&stChlCtrl))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_DLCHAN Fail!\n");
        return PS_FAIL;
    }

    /*注册上行RD完成中断和ADQ空中断回调函数*/
    stIpfOps.rx_complete_cb = CDS_UlIpfIntCB;
    stIpfOps.adq_empty_cb = CDS_UlAdqEmptyIntCB;

    if (IPF_SUCCESS != LDRV_IPF_REG_OPS(&stIpfOps))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_REG_OPS Fail!\n");
        return PS_FAIL;
    }

    /*设置RD完成中断超时时间*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_TIMEOUT(CDS_IPF_BD_CMP_INT_TIMEOUT))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_TIMEOUT Fail!\n");
        return PS_FAIL;
    }

    /*设置AD长度阈值*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_ADTHRED(CDS_IPF_AD_LEN_THRESHOLD,CDS_IPF_AD_LEN_THRESHOLD))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_ADTHRED Fail!\n");
        return PS_FAIL;
    }

    /*获取下行最大BD个数*/
    g_stCdsIpfCtrlEntity.ulDlMaxBdNum = LDRV_IPF_GET_DLBD_MAX_NUM();
    if (0 == g_stCdsIpfCtrlEntity.ulDlMaxBdNum)
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_GET_DLBD_MAX_NUM Fail!\n");
        return PS_FAIL;
    }

    /*创建下行接收队列*/
    if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(CDS_GET_IPF_DL_SDU_QUE()),CDS_IPF_DL_SDU_QUE_SIZE))
    {
        PS_PRINTF("CDS_IpfInit : Create DL Sdu Que Fail.\n");
        return PS_FAIL;
    }

    /*创建源内存释放队列*/
    if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(CDS_IPF_DL_SRCMEM_FREE_QUE()),2*g_stCdsIpfCtrlEntity.ulDlMaxBdNum))
    {
        PS_PRINTF("CDS_IpfInit : Create IPF DL Src Mem Free  Que Fail. \n");
        return PS_FAIL;
    }

    /*使能上行IP过滤*/
    /*lint -e730 -e506 -e944*/
    if(IPF_SUCCESS != LDRV_IPF_ENABLE_CHAN(IPF_CHANNEL_UP, VOS_TRUE))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_ENABLE_CHAN UL Fail!\n");
        return PS_FAIL;
    }

    /*使能下行IP过滤*/
    if(IPF_SUCCESS != LDRV_IPF_ENABLE_CHAN(IPF_CHANNEL_DOWN, VOS_TRUE))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_ENABLE_CHAN DL Fail!\n");
        return PS_FAIL;
    }

    /*注册TTF_MEM_SET偏移*/
    if (IPF_SUCCESS != LDRV_IPF_SET_DBUF_PARA(TTF_OFFSET_OF(TTF_MEM_ST, pData),
            TTF_OFFSET_OF(TTF_MEM_ST, usUsed), TTF_OFFSET_OF(TTF_MEM_ST, pNext)))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_SET_DBUF_PARA Fail!\n");
        return PS_FAIL;
    }
    /*lint +e730 +e506 +e944*/

    /*初始化下行IPF过滤器*/
    CDS_InitDlIpfFilter();

    /*补充ADQ内存*/
    CDS_AllocMemForAdq();

    (VOS_VOID)CDS_DisableDlIPFFilter(MODEM_ID_0);
    (VOS_VOID)CDS_DisableDlIPFFilter(MODEM_ID_1);
    (VOS_VOID)CDS_DisableDlIPFFilter(MODEM_ID_2);

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : CDS_ChangeDlIpfFilterType
 功能描述  : 改变下行IPF过滤器类型
 输入参数  :
 输出参数  : 无
 返 回 值  : PS_SUCC:修改成功
             PS_FAIL:修改失败
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_ChangeDlIpfFilterType(VOS_UINT16  usModemId)
{
    VOS_UINT32              ulCnt;
    IPF_FILTER_CONFIG_S    *pstFilter;

    if (usModemId >= CDS_MAX_MODEM_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_ChangeDlIpfFilterType : Modem ID Error.", usModemId);
        CDS_PRINT_ERROR1(CDS_ChangeDlIpfFilterType_ENUM,CDS_PRINT_MODEM_ID_ERR,usModemId);
        return PS_FAIL;
    }

    for (ulCnt = 1; ulCnt < CDS_GET_DL_IPF_FILTER_NUM(); ulCnt ++)
    {
        pstFilter = CDS_GET_DL_IPF_FILTER_PTR(ulCnt);

        CDS_DL_IPF_CLR_EX_FILTER_FLG(pstFilter->u32FilterID);

        /*Modem1设置为扩展过滤器*/
        if (MODEM_ID_0 < usModemId)
        {
            CDS_DL_IPF_SET_EX_FILTER_FLG(pstFilter->u32FilterID);
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : CDS_EnableDlIPFFilter
 功能描述  : 使能下行IPF 包过滤器
 输入参数  :
 输出参数  : 无
 返 回 值  : PS_SUCC:修改成功
             PS_FAIL:修改失败
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_EnableDlIPFFilter(VOS_UINT16  usModemId)
{
    IPF_FILTER_CHAIN_TYPE_E  enFCType;

    /*根据ModemId区分过滤器首地址*/
    if (MODEM_ID_0 == usModemId)
    {
        enFCType = IPF_MODEM0_DLFC;
    }
    else if (MODEM_ID_1 == usModemId)
    {
        enFCType = IPF_MODEM1_DLFC;
    }
    else if (MODEM_ID_2 == usModemId)
    {
        enFCType = IPF_MODEM2_DLFC;
    }
    else
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Input Para Error. ModemId,MaxModemNum:", usModemId,CDS_MAX_MODEM_NUM);
        CDS_PRINT_ERROR2(CDS_EnableDlIPFFilter_ENUM,CDS_PRINT_MODEM_ID_ERR, usModemId,CDS_MAX_MODEM_NUM);
        return PS_FAIL;
    }

    /*改变下行IPF过滤器的类型*/
    if (PS_SUCC != CDS_ChangeDlIpfFilterType(usModemId))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Change DL Filter Type Fail.");
        CDS_PRINT_ERROR(CDS_EnableDlIPFFilter_ENUM,LL2_FUNCTION_RETURN_ERROR);
        return PS_FAIL;
    }

    /*将已设置好的过滤器配置给下行IPF*/
    if (IPF_SUCCESS != LDRV_IPF_SET_FILTER(enFCType,
                                         CDS_GET_DL_IPF_FILTER_ARRAY(),
                                         CDS_GET_DL_IPF_FILTER_NUM()))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Enable Dl IPF Filter Fail.Filter Num:", CDS_GET_DL_IPF_FILTER_NUM());
        CDS_PRINT_ERROR1(CDS_EnableDlIPFFilter_ENUM,CDS_PRINT_DRV_RETURN_ERR,CDS_GET_DL_IPF_FILTER_NUM());
        return PS_FAIL;
    }
    else
    {
        CDS_INFO_LOG(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Enable Dl IPF Filter Success.");
        CDS_PRINT_INFO(CDS_EnableDlIPFFilter_ENUM,CDS_PRINT_IPF_FILTER_INFO);
        return PS_SUCC;
    }
}

/*****************************************************************************
 函 数 名  : CDS_DisableDlIPFFilter
 功能描述  : 去使能下行IPF 包过滤器
 输入参数  :
 输出参数  : 无
 返 回 值  : PS_SUCC:修改成功
             PS_FAIL:去使能失败
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_DisableDlIPFFilter(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32               ulFilterNum = 0;
    IPF_FILTER_CHAIN_TYPE_E  enFCType;

    /*根据ModemId区分过滤器首地址*/
    if (MODEM_ID_0 == enModemId)
    {
        enFCType = IPF_MODEM0_DLFC;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        enFCType = IPF_MODEM1_DLFC;
    }
    else if (MODEM_ID_2 == enModemId)
    {
        enFCType = IPF_MODEM2_DLFC;
    }
    else
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_DisableDlIPFFilter : Modem ID Error.", enModemId);
        CDS_PRINT_ERROR1(CDS_DisableDlIPFFilter_ENUM,CDS_PRINT_MODEM_ID_ERR,enModemId);
        return PS_FAIL;
    }

    /*取消过滤器配置*/
    if (IPF_SUCCESS != LDRV_IPF_SET_FILTER(enFCType,
                                         CDS_GET_DL_IPF_FILTER_ARRAY(),
                                         ulFilterNum))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_DisableDlIPFFilter : Disable Dl IPF Filter Fail.Filter Num:", CDS_GET_DL_IPF_FILTER_NUM());
        CDS_PRINT_ERROR1(CDS_DisableDlIPFFilter_ENUM,CDS_PRINT_DRV_RETURN_ERR,CDS_GET_DL_IPF_FILTER_NUM());
        return PS_FAIL;
    }
    else
    {
        /*CDS_INFO_LOG(UEPS_PID_CDS, "CDS_DisableDlIPFFilter : Disable Dl IPF Filter Success.");*/
        return PS_SUCC;
    }
}

/*****************************************************************************
 函 数 名  : CDS_SaveIpfDlMemInfo
 功能描述  : 在下行配置完IPF BD后，保存需要释放的源内存
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年08月16日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SaveIpfDlSrcMem(const IPF_CONFIG_DLPARAM_S *pstIpfDlBdBuff, VOS_UINT32 ulSaveNum)
{
    LUP_QUEUE_STRU                   *pstDlFreeQue;
    VOS_UINT32                        ulCnt;
    TTF_MEM_ST                       *pstSrcMem;

    CDS_ASSERT(VOS_NULL_PTR != pstIpfDlBdBuff);

    if (ulSaveNum > CDS_IPF_MAX_DL_CFG_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SaveIpfDlMemInfo:Input Bd Num Error.",ulSaveNum);
        CDS_PRINT_ERROR1(CDS_SaveIpfDlSrcMem_ENUM,CDS_PRINT_PARA_INPUT_ERR,ulSaveNum);
        return ;
    }

    pstDlFreeQue = CDS_IPF_DL_SRCMEM_FREE_QUE();
    CDS_ASSERT(VOS_NULL_PTR != pstDlFreeQue);

    for (ulCnt = 0; ulCnt < ulSaveNum; ulCnt ++)
    {
        pstSrcMem = (TTF_MEM_ST*)pstIpfDlBdBuff[ulCnt].u32Data;
        if (PS_SUCC != LUP_EnQue(pstDlFreeQue,pstSrcMem))
        {
            CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_SaveIpfDlMemInfo: Src Mem Leak.",ulCnt,ulSaveNum);
            CDS_PRINT_ERROR2(CDS_SaveIpfDlSrcMem_ENUM,CDS_PRINT_ENQUE_FAIL,ulCnt,ulSaveNum);
            PS_PRINTF("CDS_SaveIpfDlMemInfo: Buffer Full!! cnt=%d,ulSaveNum=%d\n",ulCnt,ulSaveNum);
            TTF_MemFree(UEPS_PID_CDS,pstSrcMem);
            CDS_DBG_DL_IPF_SAVE_SRCMEM_FAIL_NUM(1);
            continue;
        }

        CDS_DBG_DL_IPF_SAVE_SRCMEM_SUCC_NUM(1);
    }

    return ;
}


/*****************************************************************************
 函 数 名  : CDS_ConfigDlIPF
 功能描述  : 配置下行IPF
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ConfigDlIPF(VOS_VOID)
{
    VOS_UINT32              ulIdleBD;
    VOS_UINT32              ulIdleCD;
    VOS_UINT32              ulCnt;
    VOS_UINT32              ulCfgCD;
    TTF_MEM_ST             *pstSrcMem;
    IPF_CONFIG_DLPARAM_S   *pstDlCfgPara;
    int                     intLockLevel;
    VOS_UINT16              usModemId;

    /*触发下行IPF释放源内存*/
    CDS_FreeIpfDlSrcMem();

    /*获得下行空闲BD/CD个数*/
    ulIdleBD = (VOS_UINT32)LDRV_IPF_GET_DLBD_NUM(&ulIdleCD);
    if (0 == ulIdleBD)
    {
        /*没有空闲BD*/
        CDS_DBG_DL_IPF_CFG_HAVE_NO_BD(1);
        return;
    }

    if (ulIdleBD > CDS_GET_IPF_DL_MAX_BD_NUM())
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GUConfigDlIPF : DL Idle BD Num Error.",ulIdleBD);
        CDS_PRINT_ERROR1(CDS_ConfigDlIPF_ENUM,CDS_PRINT_IDLE_BD_NUM_ERR,ulIdleBD);
        return;
    }

    /*一次配BD个数不能超过可配置的最大个数*/
    if (ulIdleBD > CDS_IPF_MAX_DL_CFG_NUM)
    {
        ulIdleBD = CDS_IPF_MAX_DL_CFG_NUM;
    }

    if (0 == ulIdleCD)
    {
        /*没有空闲CD*/
        CDS_DBG_DL_IPF_CFG_HAVE_NO_CD(1);
        return;
    }

    ulCfgCD = 0;
    for (ulCnt = 0; ulCnt < ulIdleBD; ulCnt ++)
    {
        /**/
        pstDlCfgPara = &(g_stCdsIpfCtrlEntity.astDlIpfCfgPara[ulCnt]);
        if (PS_SUCC != LUP_PeekQueHead(CDS_GET_IPF_DL_SDU_QUE(),(VOS_VOID **)&pstSrcMem))
        {
            break;
        }

        /*Get BD*/
        ulCfgCD += CDS_GetTtfMemCnt(pstSrcMem);
        if (ulCfgCD > ulIdleCD)
        {
            CDS_DBG_DL_IPF_CFG_CD_NOT_ENOUGH(1);
            break;
        }

        /*真实出队*/
        intLockLevel = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(CDS_GET_IPF_DL_SDU_QUE(),(VOS_VOID **)&pstSrcMem))
        {
            /*异常保护，应该不会*/
            VOS_Splx(intLockLevel);
            break;
        }
        VOS_Splx(intLockLevel);

        pstDlCfgPara->u32Data       = (VOS_UINT32)(pstSrcMem);
        pstDlCfgPara->u16Len        = CDS_DL_GET_PKT_LEN_FROM_TTF(pstSrcMem);
        pstDlCfgPara->u16UsrField1  = CDS_DL_GET_MODEMID_RABID_FROM_TTF(pstSrcMem);

        usModemId = CDS_DL_GET_MODEMID_FROM_TTF(pstSrcMem);

        if (MODEM_ID_0 == usModemId)
        {
            CDS_DL_BD_SET_ATTR_WITH_FC_HDR(pstDlCfgPara->u16Attribute,IPF_MODEM0_DLFC);
        }
        else if (MODEM_ID_1 == usModemId)
        {
            CDS_DL_BD_SET_ATTR_WITH_FC_HDR(pstDlCfgPara->u16Attribute,IPF_MODEM1_DLFC);
        }
        else
        {
            CDS_DL_BD_SET_ATTR_WITH_FC_HDR(pstDlCfgPara->u16Attribute,IPF_MODEM2_DLFC);
        }

    }

    /*配置下行过滤包数为0，直接返回*/
    if (0 == ulCnt)
    {
        return;
    }

    /*最后一个BD设置中断标志*/
    pstDlCfgPara = &(g_stCdsIpfCtrlEntity.astDlIpfCfgPara[ulCnt - 1]);
    CDS_DL_BD_SET_ATTR_INT_FLG(pstDlCfgPara->u16Attribute);

    /*配置上行IPF过滤*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_DLBD(ulCnt,g_stCdsIpfCtrlEntity.astDlIpfCfgPara))
    {
        /*配置失败后，源内存释放*/
        ulIdleBD = ulCnt;
        for (ulCnt = 0; ulCnt < ulIdleBD; ulCnt ++)
        {
            pstDlCfgPara = &(g_stCdsIpfCtrlEntity.astDlIpfCfgPara[ulCnt]);
            pstSrcMem = (TTF_MEM_ST*)(pstDlCfgPara->u32Data);
            TTF_MemFree(UEPS_PID_CDS,pstSrcMem);
        }

        CDS_DBG_DL_IPF_CFG_BD_FAIL_NUM(ulIdleBD);
        return;
    }

    /*缓存Src Mem*/
    CDS_SaveIpfDlSrcMem(g_stCdsIpfCtrlEntity.astDlIpfCfgPara,ulCnt);

    CDS_DBG_DL_IPF_CFG_BD_SUCC_NUM(ulCnt);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ConfigUlAdq
 功能描述  : 配置上行ADQ
 输入参数  : VOS_UINT32 ulAdType
             VOS_UINT32 ulCanCfgAdNum

 输出参数  :
 返 回 值  : 返回配置AD成功个数

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_ConfigUlAdq(VOS_UINT32 ulAdType, VOS_UINT32 ulCanCfgAdNum)
{
    VOS_UINT32           ulCnt;
    VOS_UINT32           ulAdLen;
    TTF_MEM_ST          *pstDstMem;
    IPF_AD_DESC_S       *pstAdDesc;
    VOS_UINT32           ulTmp;

    /*入参判断*/
    if ((0 == ulCanCfgAdNum) || (CDS_IPF_ULAD_DESC_SIZE < ulCanCfgAdNum))
    {
        return 0;
    }

    if (ulAdType >= IPF_AD_MAX)
    {
        return 0;
    }

    /*设置申请内存长度*/
    if (IPF_AD_0 == ulAdType)
    {
        ulAdLen = CDS_IPF_AD_0_PKT_LEN;
    }
    else
    {
        ulAdLen = CDS_IPF_AD_1_PKT_LEN;
    }

    /*循环申请内存，配置AD描述符*/
    for (ulCnt = 0; ulCnt < ulCanCfgAdNum; ulCnt ++)
    {
        pstDstMem = CDS_AllocTtfMem(ulAdLen);
        if (VOS_NULL_PTR == pstDstMem)
        {
            break;
        }

        /*配置AD DESC*/
        CDS_DBG_UL_ADQ_ALLOC_MEM_NUM(1);
        pstAdDesc = &(g_stCdsIpfCtrlEntity.astUlAdBuff[ulCnt]);
        pstAdDesc->u32OutPtr0 = (VOS_UINT32)(pstDstMem->pData);
        pstAdDesc->u32OutPtr1 = (VOS_UINT32)pstDstMem;
    }

    if (0 == ulCnt)
    {
        return 0;
    }

    /*配置AD*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_ULAD((IPF_AD_TYPE_E)ulAdType,ulCnt,g_stCdsIpfCtrlEntity.astUlAdBuff))
    {
        /*配置失败，释放内存*/
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt ++)
        {
            pstAdDesc = &(g_stCdsIpfCtrlEntity.astUlAdBuff[ulCnt]);
            pstDstMem = (TTF_MEM_ST*)(pstAdDesc->u32OutPtr1);
            TTF_MemFree(UEPS_PID_CDS,pstDstMem);
            CDS_DBG_UL_ADQ_FREE_MEM_NUM(1);
        }

        CDS_DBG_UL_ADQ_CFG_ADQ_FAIL_NUM(1);
        return 0;
    }

    CDS_DBG_UL_ADQ_CFG_AD_NUM(ulCnt);
    CDS_DBG_UL_ADQ_CFG_ADQ_SUCC_NUM(1);

    return ulCnt;
}

/*****************************************************************************
 函 数 名  : CDS_AllocMemForAdq
 功能描述  : 为ADQ补充内存
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_AllocMemForAdq(VOS_VOID)
{
    VOS_UINT32             ulAd0CanCfgNum    = 0;
    VOS_UINT32             ulAd1CanCfgNum    = 0;
    VOS_UINT32          ulAd0CfgNum       = CDS_IPF_ULAD_DESC_SIZE;
    VOS_UINT32          ulAd1CfgNum       = CDS_IPF_ULAD_DESC_SIZE;


    /*获得AD0/AD1 可配置AD个数*/
    if (IPF_SUCCESS != LDRV_IPF_GET_ULAD_NUM(&ulAd0CanCfgNum,&ulAd1CanCfgNum))
    {
        return;
    }

    /*配置AD0*/
    if (0 != ulAd0CanCfgNum)
    {
        ulAd0CfgNum = CDS_ConfigUlAdq(IPF_AD_0,ulAd0CanCfgNum);
        CDS_DBG_UL_ADQ_CFG_AD0_NUM(ulAd0CfgNum);
    }

    /*配置AD1*/
    if (0 != ulAd1CanCfgNum)
    {
        ulAd1CfgNum = CDS_ConfigUlAdq(IPF_AD_1,ulAd1CanCfgNum);
        CDS_DBG_UL_ADQ_CFG_AD1_NUM(ulAd1CfgNum);
    }

    /*只要有一个队列没有配置新内存，则启动保护定时器*/
    if (((CDS_IPF_ULAD_START_TMR_THRESHOLD < ulAd0CanCfgNum) && (0 == ulAd0CfgNum))
       || ((CDS_IPF_ULAD_START_TMR_THRESHOLD < ulAd1CanCfgNum) && (0 == ulAd1CfgNum)))
    {
        /*启动保护定时器*/
        if (PS_SUCC != CDS_StartAdqEmptyProctectTmr())
        {
            CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_AllocMemForAdq : Start Protect Timer Fail.");
            CDS_PRINT_ERROR(CDS_AllocMemForAdq_ENUM,CDS_PRINT_START_TIMER_FAIL);
            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_RdTransferTtfMem
 功能描述  : 将RD结果转换为TTF_MEM_ST指针，将ModemId/RabId/FilterResult保持
             到ulForCds[0]中，由调用者保证入参合法。

 输入参数  : pstRdDesc : IPF RD
 输出参数  : 无
 返 回 值  : TTF_MEM_ST*
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年12月31日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
TTF_MEM_ST* CDS_RdTransferTtfMem(const IPF_RD_DESC_S *pstRdDesc)
{
    TTF_MEM_ST     *pstIpPkt;

    /*将Out指针转换为TTF指针*/
    pstIpPkt = (TTF_MEM_ST*)(pstRdDesc->u32OutPtr);
    if (VOS_NULL_PTR == pstIpPkt)
    {
        return VOS_NULL_PTR;
    }

    /*设置正常长度*/
    pstIpPkt->usUsed = pstRdDesc->u16PktLen;

    /*保存FilterResult(2Byte)/ModemId(1Byte)/RabId(1Bytes)*/
    CDS_UL_SAVE_RD_INFO_TO_TTF(pstIpPkt,pstRdDesc);
    return pstIpPkt;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

