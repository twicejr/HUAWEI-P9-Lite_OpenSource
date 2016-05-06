/*******************************************************************************
  File name:          AsApi.c
  Description:        As提供给Nas的Api函数文件
  Function List:
      1.    U_NasSendAsMsg
      2.    U_PsDomainDataReq
      3.    U_CsDomainDataReq
      4.    U_CsDomainSyncDataReq
  History:
  1.z49132   2003.07.25   The first version
  2.日    期   : 2006年10月11日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D06583,函数As_RrPowerOffReq(VOS_VOID)
                 消息头填写遗漏了ulReceiverCpuId
  3.日    期   : 2006年12月5日
    作    者   : luojian 60022475
    修改内容   : Maps3000接口修改
  4.日    期   : 2007年07月12日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D12374,modidied  for Hi4131
  5.日    期   : 2007年9月27日
    作    者   : s46746
    修改内容   : 将卡无效信息从RRMM_NAS_INFO_CHANGE消息中拿掉
  6.日    期   : 2007年11月16日
    作    者   : l00107747
    修改内容   : 根据问题单号A32D13483
  7.Date         : 2008/4/23
    Author       : luojian, id:107747
    Modification : AT2D03148

  8.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
*******************************************************************************/
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "Nasrrcinterface.h"
#include  "NasPdcpInterface.h"
#include  "asnasapi.h"


#include "TTFMem.h"
#include "NasRlcInterface.h"
#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_ASN_ASAPI_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
extern VOS_UINT8  NAS_GetRbTxMode(VOS_UINT32 ulDomain, VOS_INT8    cRbId);

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_PsDomainTcDataReq
 功能描述  : PS域请求AS层发送环回数据
 输入参数  : VOS_UINT8      ucRbId       - radio bear的标识, 5~32
             VOS_UINT32     ulDataBitLen - 数据的长度，BIT
             VOS_INT8      *pcData       - 数据的指针，指向发送的数据
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    作    者   : L47619/H62119
    修改内容   : PS域环回修改

  2.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : AT2D18350, GCF 14.2.4 环回测试失败

  3.日    期   : 2010年4月22日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010111102810，RMC HSUPA和HSDPA互切，单板复位
  4.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理

*****************************************************************************/
VOS_INT32 NAS_PsDomainTcDataReq(
    VOS_UINT8                           ucRbId,
    VOS_UINT32                          ulDataBitLen,
    TTF_MEM_ST                         *pstDataMem
)
{
    RABM_PDCP_TC_DATA_REQ_STRU *pMsg;
    VOS_UINT32                  ulRet;

    if (WUE_RLC_MODE_BUTT == NAS_GetRbTxMode(RRC_NAS_PS_DOMAIN, (VOS_INT8)ucRbId))
    {
        return AS_RB_NO_EXIST;
    }

    pMsg = (RABM_PDCP_TC_DATA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
        WUEPS_PID_RABM,sizeof(RABM_PDCP_TC_DATA_REQ_STRU));
    if( VOS_NULL_PTR == pMsg )
    {
        return AS_NO_MEMORY;
    }

    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RABM_PDCP_TC_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = WUEPS_PID_RABM;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_PDCP;
    pMsg->ulLength        = sizeof(RABM_PDCP_TC_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pMsg->enMsgName       = ID_RABM_PDCP_TC_DATA_REQ;
    pMsg->ucRbId          = ucRbId;
    pMsg->pstDataMem      = pstDataMem;
    pMsg->ulDataBitLen    = ulDataBitLen;

    if (VOS_NULL_PTR == pMsg->pstDataMem)
    {
        /*释放消息结构体*/
        PS_FREE_MSG(WUEPS_PID_RABM, pMsg);

        return AS_NO_MEMORY;
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pMsg);
    if ( VOS_OK != ulRet )
    {
        PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_PsDomainTcDataReq, Error, call PS_SEND_MSG fail\n");
    }
    return AS_SUCCESS;
}

/*******************************************************************************
  Module:   U_CsDomainDataReq
  Function: CS域请求AS层发送数据
  Input:    VOS_INT8  cRbId          radio bear的标识, 5~32
            VOS_UINT32 ulDataLength   数据的长度,BIT
            VOS_INT8  *pcData        数据的指针，指向发送的数据，
                                 由高层申请，由AS层负责释放
  Output:
  NOTE:
  Return:   VOS_INT32
  History:
  1.    z49132   2003.07.25  the first version

  2.    hujianbo 42180 A32D08156 20070125

  3.日    期   : 2010年4月22日
    作    者   : o00132663
    修改内容   : AT2D18350, GCF 14.2.4 环回测试失败
  2.日    期   : 2012年8月8日
    作    者   : l00171473
    修改内容   : DTS2012080802390, TD的环回失败
*******************************************************************************/
VOS_INT32 NAS_CsDomainDataReq(
                       VOS_INT8   cRbId,
                       VOS_UINT32 ulDataLength,
                       VOS_UINT8  *pucData
                       )
{
    RABM_RLC_TM_DATA_REQ_STRU *pTmMsg;
    RABM_RLC_UM_DATA_REQ_STRU *pUmMsg;
    RABM_RLC_AM_DATA_REQ_STRU *pAmMsg;
    VOS_UINT32 ulLenOct;
    VOS_UINT8   ucRbMode;
    VOS_VOID *pMsg;
    TTF_MEM_ST *pData;

    ucRbMode = NAS_GetRbTxMode(RRC_NAS_CS_DOMAIN, cRbId);

    switch(ucRbMode)
    {
    case WUE_RLC_TM_MODE:
        pTmMsg = (RABM_RLC_TM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                 WUEPS_PID_RABM,sizeof(RABM_RLC_TM_DATA_REQ_STRU));
        if( VOS_NULL == pTmMsg )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, call PS_ALLOC_MSG_WITH_HEADER_LEN fail\n");

            return AS_NO_MEMORY;
        }
        PS_MEM_SET((VOS_INT8*)pTmMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(RABM_RLC_TM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        pTmMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pTmMsg->ulSenderPid     = WUEPS_PID_RABM;
        pTmMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

        pTmMsg->ulReceiverPid   = WUEPS_PID_RLC;

        pTmMsg->ulLength        = sizeof(RABM_RLC_TM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        pTmMsg->enMsgName       = ID_RABM_RLC_TM_DATA_REQ;
        pTmMsg->ucRbId          = (VOS_UINT8)cRbId;
        pTmMsg->usDataBitLen    = (VOS_UINT16)ulDataLength;

        ulLenOct = (ulDataLength + 7)/ 8;
        pData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pucData, (VOS_UINT16)ulLenOct);
        if ( VOS_NULL_PTR == pData )
        {
            /*释放消息内存:*/
            PS_FREE_MSG(WUEPS_PID_RABM, pTmMsg);
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                    "NAS_CsDomainDataReq, Error, call TTF_MemCopyAlloc fail\n");

            return AS_NO_MEMORY;
        }

        pTmMsg->pstDataMem = pData;

        pMsg = (VOS_VOID *)pTmMsg;
        break;
    case WUE_RLC_UM_MODE:
        if(0 != (ulDataLength % 8))
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, 配置的RLC UL SDU长度不是整字节\n");

            return AS_DATA_LENGTH_ERR;
        }

        pUmMsg = (RABM_RLC_UM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_RABM,sizeof(RABM_RLC_UM_DATA_REQ_STRU));
        if( VOS_NULL == pUmMsg )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, call PS_ALLOC_MSG_WITH_HEADER_LEN fail\n");

            return AS_NO_MEMORY;
        }
        PS_MEM_SET((VOS_INT8*)pUmMsg + VOS_MSG_HEAD_LENGTH,0,
                            sizeof(RABM_RLC_UM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        pUmMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pUmMsg->ulSenderPid     = WUEPS_PID_RABM;
        pUmMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

        pUmMsg->ulReceiverPid   = WUEPS_PID_RLC;

        pUmMsg->ulLength        = sizeof(RABM_RLC_UM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        pUmMsg->enMsgName       = ID_RABM_RLC_UM_DATA_REQ;
        pUmMsg->ucRbId          = (VOS_UINT8)cRbId;
        /* 此成员为TD新加的, GU这边没用这个成员, 所以可以不使用TD的宏 */
        pUmMsg->usDataBitLen    = (VOS_UINT16)ulDataLength;
        ulLenOct = ulDataLength / 8;
        pData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pucData, (VOS_UINT16)ulLenOct);
        if ( VOS_NULL_PTR == pData )
        {
            /*释放消息内存:*/
            PS_FREE_MSG(WUEPS_PID_RABM, pUmMsg);
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                    "NAS_CsDomainDataReq, Error, call TTF_MemCopyAlloc fail\n");

            return AS_NO_MEMORY;
        }

        pUmMsg->pstDataMem = pData;

        pMsg = (VOS_VOID *)pUmMsg;

        break;
    case WUE_RLC_AM_MODE:
        ulLenOct = (ulDataLength + 7) / 8;

        pAmMsg = (RABM_RLC_AM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                    WUEPS_PID_RABM,sizeof(RABM_RLC_AM_DATA_REQ_STRU));
        if( VOS_NULL == pAmMsg )
        {
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                "NAS_CsDomainDataReq, Error, call PS_ALLOC_MSG_WITH_HEADER_LEN fail\n");

            return AS_NO_MEMORY;
        }
        PS_MEM_SET((VOS_INT8*)pAmMsg + VOS_MSG_HEAD_LENGTH,0,
                    sizeof(RABM_RLC_AM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);


        pAmMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pAmMsg->ulSenderPid     = WUEPS_PID_RABM;
        pAmMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

        pAmMsg->ulReceiverPid   = WUEPS_PID_RLC;

        pAmMsg->ulLength        = sizeof(RABM_RLC_AM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

        pAmMsg->enMsgName       = ID_RABM_RLC_AM_DATA_REQ;
        pAmMsg->ucRbId          = (VOS_UINT8)cRbId;
        /* 此成员为TD新加的, GU这边没用这个成员, 所以可以不使用TD的宏 */
        pAmMsg->usDataBitLen    = (VOS_UINT16)ulDataLength;

        pData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pucData, (VOS_UINT16)ulLenOct);
        if ( VOS_NULL_PTR == pData )
        {
            /*释放消息内存:*/
            PS_FREE_MSG(WUEPS_PID_RABM, pAmMsg);
            PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_ERROR,
                    "NAS_CsDomainDataReq, Error, call TTF_MemCopyAlloc fail\n");

            return AS_NO_MEMORY;
        }

        pAmMsg->pstDataMem = pData;

        pMsg = (VOS_VOID *)pAmMsg;

        break;
    case WUE_RLC_MODE_BUTT:
        PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "NAS_CsDomainDataReq, Error, No Rlc Rb exist\n");
        return AS_RB_NO_EXIST;
    default:
        PS_NAS_LOG(WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING,
                "NAS_CsDomainDataReq, Error, Rb Tx Mode error!\n");
        return AS_RB_NO_EXIST;
    }

    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pMsg) )
    {
        /*发送消息失败，释放申请的零拷贝内存*/
        TTF_MemFree(WUEPS_PID_RABM, pData);
        return AS_SEND_FAILED;
    }
    return AS_SUCCESS;
}



/***********************************************************************
 *  MODULE   : As_RrDataReq
 *  FUNCTION : NAS向AS请求发送信令数据
 *  INPUT    : VOS_UINT8 ucCnDomain
 *             VOS_UINT8 ucPriority
 *             VOS_UINT32 ulSize
 *             VOS_INT8 *pData
 *  OUTPUT   :
 *  RETURN   : AS_SUCCESS
 *             AS_PARA_MISMATCH
 *             AS_VOS_ERR
 *             AS_GENERAL_ERR
 *  NOTE     : 本函数提供给NAS使用
 *  HISTORY  :
 *     1.  z49132  03-08-11  新版作成
       2.日    期   : 2012年7月14日
         作    者   : W00176964
         修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
 ************************************************************************/
VOS_INT32 As_RrDataReq(
               VOS_UINT8    ucCnDomain,                                                    /* CN DOMAIN                                 */
               VOS_UINT8    ucPriority,                                                    /* 信令数据优先级                            */
               VOS_UINT32    ulSize,                                                        /* 信令数据长度                              */
               VOS_INT8     *pData                                                         /* 信令数据指针                              */
               )
{
    RRMM_DATA_REQ_STRU*         pMsg = VOS_NULL;                                           /* 定义原语类型指针                          */
    VOS_UINT32                       ulTmpSize;

    ulTmpSize = ulSize;
    if(ulTmpSize < 4)
    {
        ulTmpSize = 4;
    }

    if(RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg = (RRMM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MM,(sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4);
    }
    else
    {
        pMsg = (RRMM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_GMM,(sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4);
    }
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         ((sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRMM_DATA_REQ;                                         /* 消息名称                                  */

    pMsg->ulCnDomainId = ucCnDomain;
    pMsg->ulPriorityInd = ucPriority;
    pMsg->SendNasMsg.ulNasMsgSize = ulSize;
    if(VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pMsg->SendNasMsg.aucNasMsg,pData,ulSize);
    }

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    }
    else
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_GMM;
    }

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(pMsg->MsgHeader.ulSenderPid, (struct MsgCB **)&pMsg))
    {
        return AS_SEND_FAILED;
    }

    return AS_SUCCESS;
}
/***********************************************************************
 *  MODULE   : As_RrEstReq
 *  FUNCTION : 高层请求建立某个CN域的信令连接
 *  INPUT    : VOS_UINT32        ulOpId
 *             VOS_UINT8        ucCnDomain
 *             VOS_UINT32        ulEstCause
 *             IDNNS_STRU   *pIdnnsInfo
 *             VOS_UINT32        ulSize
 *             VOS_INT8         *pFisrstMsg
 *  OUTPUT   :
 *  RETURN   : AS_SUCCESS
 *             AS_PARA_MISMATCH
 *             AS_VOS_ERR
 *             AS_GENERAL_ERR
 *  NOTE     : 本函数提供给NAS使用
 *  HISTORY  :
 *     1.  z49132  03-08-11  新版作成

  1.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  2.日    期   : 2010年05月02日
    作    者   : l65478
    修改内容   : 根据问题单号：AT2D18877,拉美搜网失败，增加全频搜索过程
  3.日    期   : 2012年7月14日
    作    者   : W00176964
    修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
 ************************************************************************/
VOS_INT32 As_RrEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    VOS_UINT32                          ulCallType,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
)
{
    RRMM_EST_REQ_STRU*               pMsg = VOS_NULL;                                           /* 定义原语类型指针                          */
    VOS_UINT32                       ulTmpSize;

    ulTmpSize = ulSize;
    if (ulTmpSize < 4)
    {
        ulTmpSize = 4;
    }

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg = (RRMM_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MM,(sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4);
    }
    else
    {
        pMsg = (RRMM_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_GMM,(sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4);
    }
    if (VOS_NULL == pMsg)
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         ((sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRMM_EST_REQ;                                          /* 消息名称                                  */

    pMsg->ulOpId = ulOpId;
    pMsg->ulCnDomainId = ucCnDomain;
    pMsg->ulEstCause = ulEstCause;

    /*enCallType数据域3000接口新增，2000接入层不使用，暂时在这里赋默认值，
    日后该数据域由CC指定，As_RrEstReq函数增加一个参数*/
    pMsg->enCallType = ulCallType;

    pMsg->ulIdnnsType = pIdnnsInfo->ucIdnnsType;
    pMsg->enSplmnSameRplmn = pIdnnsInfo->ucEnterPara;

    PS_MEM_CPY(&pMsg->stPlmnId, pstPlmnId, sizeof(RRC_PLMN_ID_STRU));

    pMsg->FisrtNasMsg.ulNasMsgSize = ulSize;
    if (VOS_NULL_PTR != pFisrstMsg)
    {
        PS_MEM_CPY(pMsg->FisrtNasMsg.aucNasMsg,pFisrstMsg,ulSize);
    }
    else
    {
        PS_MEM_SET(pMsg->FisrtNasMsg.aucNasMsg, 0x00, 4);
    }

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    }
    else
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_GMM;
    }

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(pMsg->MsgHeader.ulSenderPid, (struct MsgCB **)&pMsg))
    {
        return AS_SEND_FAILED;
    }

    return AS_SUCCESS;
}
/***********************************************************************
 *  MODULE   : As_RrRelReq
 *  FUNCTION : NAS请求AS释放指定域的信令连接
 *  INPUT    : VOS_UINT8 ucCnDomain
 *  OUTPUT   :
 *  RETURN   : AS_SUCCESS
 *             AS_PARA_MISMATCH
 *             AS_VOS_ERR
 *             AS_GENERAL_ERR
 *  NOTE     : 本函数提供给NAS使用
 *  HISTORY  :
 *     1.  z49132  03-08-11  新版作成
       2.日    期   : 2007年03月30日
         作    者   : luojian 60022475
         修改内容   : Maps3000接口修改
       3.日    期   : 2012年7月14日
         作    者   : W00176964
         修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
 ************************************************************************/
VOS_INT32 As_RrRelReq(
               VOS_UINT8    ucCnDomain,
               RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg
               )
{
    RRMM_REL_REQ_STRU*          pMsg = VOS_NULL;                                           /* 定义原语类型指针                          */

    if(RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_MM,sizeof(RRMM_REL_REQ_STRU));
    }
    else
    {
        pMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_GMM,sizeof(RRMM_REL_REQ_STRU));
    }
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
                        sizeof(RRMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRMM_REL_REQ;                                          /* 消息名称                                  */
    pMsg->ulCnDomainId = ucCnDomain;
    pMsg->enBarValidFlg = enBarValidFlg;

    if (RRC_NAS_CS_DOMAIN == ucCnDomain)
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    }
    else
    {
        pMsg->MsgHeader.ulSenderPid = WUEPS_PID_GMM;
    }

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(pMsg->MsgHeader.ulSenderPid, (struct MsgCB **)&pMsg))
    {
        return AS_SEND_FAILED;
    }

    return AS_SUCCESS;
}

/***********************************************************************
 *  MODULE   : As_RabInfoRsp
 *  FUNCTION : NAS向AS新建的RAB进行响应，提供AS必要的信息
 *  INPUT    : VOS_UINT32               ulResult
 *             RAB_RSP_INFO_STRU   *pRabInfo
 *  OUTPUT   :
 *  RETURN   : AS_SUCCESS
 *             AS_PARA_MISMATCH
 *             AS_VOS_ERR
 *             AS_GENERAL_ERR
 *  NOTE     : 本函数提供给NAS使用
 *  HISTORY  :
 *     1.  z49132  03-08-12  新版作成
       2.日    期   : 2012年7月14日
         作    者   : W00176964
         修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
 ************************************************************************/
VOS_INT32 As_RabInfoRsp(
                VOS_UINT32               ulResult,
                RAB_RSP_INFO_STRU   *pRabInfo
                )
{
    VOS_UINT8                   i;
    RRRABM_RAB_RSP_STRU*    pMsg = VOS_NULL;                                               /* 定义原语类型指针                          */

    pMsg = (RRRABM_RAB_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_RABM,sizeof(RRRABM_RAB_RSP_STRU));
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RRRABM_RAB_RSP_STRU) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRRABM_RAB_RSP;                                        /* 消息名称                                  */

    pMsg->ulOpId = pRabInfo->ulOpId;
    if(AS_RAB_RSP_OK == ulResult)
    {
        pMsg->ulRabCnt = pRabInfo->ulRabCnt;
        for(i = 0;i < pRabInfo->ulRabCnt;i++)
        {
            pMsg->aRabInfo[i].enCnDomainId     = pRabInfo->aRabInfo[i].ulCnDomainId;
            pMsg->aRabInfo[i].ulRabId          = pRabInfo->aRabInfo[i].ulRabId;
            pMsg->aRabInfo[i].ulPppValid       = pRabInfo->aRabInfo[i].ulPppValid;
            pMsg->aRabInfo[i].ulDeliveryErrSdu = pRabInfo->aRabInfo[i].ulDeliveryErrSdu;
        }
    }
    else
    {
        pMsg->ulRabCnt = 0;
    }

    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pMsg))
    {                                                                                  /* 发送失败                                  */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    return AS_SUCCESS;
}
/***********************************************************************
 *  MODULE   : As_RabQosUpdate
 *  FUNCTION : NAS在RAB的信息发生变化后通知AS
 *  INPUT    : QOS_INFO_STRU     *pQosInfo
 *  OUTPUT   :
 *  RETURN   : AS_SUCCESS
 *             AS_PARA_MISMATCH
 *             AS_VOS_ERR
 *             AS_GENERAL_ERR
 *  NOTE     : 本函数提供给NAS使用
 *  HISTORY  :
 *     1.  z49132  03-08-12  新版作成
      2.日    期   : 2012年7月14日
        作    者   : W00176964
        修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
 ************************************************************************/
VOS_INT32 As_RabQosUpdate(
                  QOS_INFO_STRU     *pQosInfo
                  )
{
    VOS_UINT8                           i;
    RRRABM_QOS_UPDATE_REQ_STRU*     pMsg = VOS_NULL;                                       /* 定义原语类型指针                          */

    pMsg = (RRRABM_QOS_UPDATE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_RABM,sizeof(RRRABM_QOS_UPDATE_REQ_STRU));
    if( VOS_NULL == pMsg )
    {                                                                                  /* 内存申请失败                              */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    PS_MEM_SET((VOS_INT8*)pMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RRRABM_QOS_UPDATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulMsgName = RRRABM_QOS_UPDATE_REQ;                                 /* 消息名称                                  */

    pMsg->ulRabCnt = pQosInfo->ulRabCnt;
    for(i = 0;i < pQosInfo->ulRabCnt;i++)
    {
        pMsg->aRab[i].enCnDomainId     = pQosInfo->aRab[i].ulCnDomainId;
        pMsg->aRab[i].ulRabId          = pQosInfo->aRab[i].ulRabId;
        pMsg->aRab[i].ulPppValid       = pQosInfo->aRab[i].ulPppValid;
        pMsg->aRab[i].ulDeliveryErrSdu = pQosInfo->aRab[i].ulDeliveryErrSdu;
    }

    if( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pMsg))
    {                                                                                  /* 发送失败                                  */
        return AS_VOS_ERR;                                                             /* 返回                                      */
    }
    return AS_SUCCESS;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

