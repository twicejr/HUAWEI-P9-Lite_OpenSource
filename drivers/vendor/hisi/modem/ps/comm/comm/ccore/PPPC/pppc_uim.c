/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_uim.c
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年08月08日
  最近修改   :
  功能描述   : 读取和更新UIM卡信息
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "pppc_uim.h"
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "pppc_sha1.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PPPC_UIM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 固定数据集合 */
PPPC_HRPD_FIXED_DATA_STRU               g_astPppcFixedData[MODEM_ID_BUTT];


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : PPPC_UIM_SndMsg
 功能描述  : 向UIM发送的消息
 输入参数  : VOS_UINT32              ulSenderPid,
             VOS_UINT32              ulReceiverPid,
             VOS_VOID               *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_UIM_SndMsg
(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_VOID                           *pMsg
)
{
    MsgBlock                           *pstMsg;
    VOS_UINT32                          ulRslt;


    pstMsg                              = (MsgBlock *)pMsg;

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;

    /*消息发送*/
    ulRslt   = PS_SEND_MSG(ulSenderPid, pstMsg);

    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG1(" PPPC_UIM_SndMsg ulRslt", ulRslt);
        return ulRslt;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_GetModemId
 功能描述  : 检查ModemeId并返回
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : c00199705
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_UIM_GetModemId(VOS_VOID)
{
    VOS_UINT16                          usModemId;

    usModemId = PPPC_GetModemId();

    if (usModemId >= MODEM_ID_BUTT)
    {
        PPPC_ERROR_LOG1("Modem ID error", usModemId);
        return MODEM_ID_0;
    }

    return usModemId;
}

/*****************************************************************************
函 数 名  :PPPC_UIM_ReadFileReq
功能描述  :读取文件请求
输入参数  :ulSenderPid:发送请求的PID
           pstGetFileInfo 文件信息

输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

修改历史      :
 1.日    期   : 2015年08月08日
   作    者   : w00316385
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_UIM_ReadFileReq
(
    VOS_UINT32                          ulSenderPid,
    PPPC_GET_FILE_INFO_STRU            *pstGetFileInfo
)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;
    VOS_CHAR                           *pucFilePathStr ;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usModemId;

    pstMsg          = VOS_NULL_PTR;
    pucFilePathStr  = VOS_NULL_PTR;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstGetFileInfo)
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: pstGetFileInfo Is NULL.");
        return VOS_ERR;
    }

    /* 文件Id转文件路径 */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstGetFileInfo->usEfId,&pucFilePathStr))
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: USIMM_ChangeDefFileToPath fail.");
        return VOS_ERR;
    }

    /* 分配消息内存并初始化 */
    /* 申请消息内存 */
    pstMsg = (USIMM_READFILE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_READFILE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: Allocate Msg Failed.");
        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstGetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;

    /* 填写消息体 */
    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pucFilePathStr);
    pstMsg->bNeedReadCache              = VOS_TRUE;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen);

    usModemId = PPPC_UIM_GetModemId();
    if (MODEM_ID_0 == usModemId)
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, WUEPS_PID_USIM, pstMsg);
    }
    else
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, I1_WUEPS_PID_USIM, pstMsg);
    }

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPPC_UIM_ReadFileReq: PPPC_UIM_SndMsg ulRslt", ulResult);
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SndUimReadReq
 功能描述  : 向UIM发送读取指定文件请求的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32   是否发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_INIT_SndUimReadReq(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSendInd;
    PPPC_GET_FILE_INFO_STRU             stGetFileInfo;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          ausEfId[PPPC_MAX_USIM_FILE_NUM];

    usModemId = PPPC_UIM_GetModemId();

    /* 根据卡的类型赋值 */
    if( PPPC_HRPD_CARD_STATUS_CSIM_PRESENT == PPPC_HRPD_GetUimStatus(usModemId))
    {
        ausEfId[0]            = USIMM_CSIM_EFRUIMID_ID;
        ausEfId[1]            = USIMM_CSIM_EFCSIMST_ID;
        ausEfId[2]            = USIMM_CSIM_EFESNMEID_ID;
        ausEfId[3]            = USIMM_CSIM_EFUSGIND_ID;
        ausEfId[4]            = USIMM_CSIM_EFHRPDUPP_ID;
        ausEfId[5]            = USIMM_CSIM_EFIMSIM_ID;
    }
    else if( PPPC_HRPD_CARD_STATUS_UIM_PRESENT == PPPC_HRPD_GetUimStatus(usModemId))
    {
        ausEfId[0]            = USIMM_CDMA_EFRUIMID_ID;
        ausEfId[1]            = USIMM_CDMA_EFCST_ID;
        ausEfId[2]            = USIMM_CDMA_EFESNMEIDME_ID;
        ausEfId[3]            = USIMM_CDMA_EFUSGIND_ID;
        ausEfId[4]            = USIMM_CDMA_EFHRPDUPP_ID;
        ausEfId[5]            = USIMM_CDMA_EFIMSIM_ID;
    }
    else
    {
        PPPC_WARNING_LOG("Unknow sim card type");
        return VOS_ERR;
    }

    /* USIM文件不区分卡类型 */
    ausEfId[6]            = USIMM_USIM_EFIMSI_ID;
    ausEfId[7]            = USIMM_USIM_EFAD_ID;

    /* 发送读取命令 */
    ulSendInd = 0;
    while (ulSendInd < PPPC_MAX_USIM_FILE_NUM)
    {
        ulLoop = 0;
        while ((ulLoop < PPPC_MAX_USIM_REQSEND_NUM))
        {
            if (0 == PPPC_HRPD_GetUsimFileMask(usModemId, ulSendInd))
            {
                if ((USIMM_USIM_EFIMSI_ID == ausEfId[ulSendInd])
                     || (USIMM_USIM_EFAD_ID == ausEfId[ulSendInd]))
                {
                    stGetFileInfo.enAppType     = USIMM_GUTL_APP;
                }
                else
                {
                    stGetFileInfo.enAppType     = USIMM_CDMA_APP;
                }
                stGetFileInfo.usEfId        = ausEfId[ulSendInd];
                stGetFileInfo.ucRecordNum   = 0;

                /* 读取 */
                ulRslt = PPPC_UIM_ReadFileReq(MSPS_PID_PPPC, &stGetFileInfo);

                /* 检查文件读取命令发送是否成功 */
                if (USIMM_API_SUCCESS != ulRslt)
                {
                    PPPC_WARNING_LOG1("PPPC_INIT_SndUimReadReq,GetFileReq fail,ulEfId",
                                       ausEfId[ulLoop]);
                }
                ulLoop++;
            }
            ulSendInd++;
            if (ulSendInd >= PPPC_MAX_USIM_FILE_NUM)
            {
                return VOS_OK;
            }
        }
        VOS_TaskDelay(100);
    }
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveCst
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
             PPPC_HRPD_CST_STRU *pstCst
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveCst(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_CST_STRU *pstCst)
{
    if (PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE < pstUsimRead->usEfLen)
    {
        pstCst->ucCstLen = (VOS_UINT8)PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE;
    }
    else
    {
        pstCst->ucCstLen = (VOS_UINT8)pstUsimRead->usEfLen;
    }

    PS_MEM_CPY(pstCst->aucCst, pstUsimRead->aucEf, pstCst->ucCstLen);

    return;
}

/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveHrpdupp
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveHrpdupp
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_UPP_STRU                 *pstHrpdUpp
)
{
    /* 3GPP2 C.S0023-D v2.0 3.4.53 HRPD Access Authentication User Profile Parameters or
       3GPP2 C.S0065-B v2.0 5.2.54 HRPD Access Authentication User Profile Parameters and
       3GPP2 C.S0016-D v2.0 3.5.8.13 HRPD Access Authentication User Profile Parameters */

    /* HRPDUPP Block Len(1byte) + NAI Len(1byte) + AUTH_ALGORITHM&Reserved(1byte) */
    const VOS_UINT8                     ucMinEFLen = 3;
    VOS_UINT8                           ucFileLen;
    VOS_UINT8                           ucNAILen;
    PS_BOOL_ENUM_UINT8                  enIsNAIFormValid = PS_FALSE;
    VOS_UINT8                           ucLoop = 0;
    VOS_UINT8                          *pucNaiData;

    /* 检查读卡结果 */
    if ((0 != pstUsimRead->stCmdResult.ulResult)
        || (0 != pstUsimRead->stCmdResult.ulErrorCode)
        || (pstUsimRead->usEfLen <= ucMinEFLen))
    {
        PPPC_WARNING_LOG3("Read usim failed. ulResult:%d, ulErrorCode:%d, Eflen:%d.\n",
            pstUsimRead->stCmdResult.ulResult, pstUsimRead->stCmdResult.ulErrorCode, pstUsimRead->usEfLen);
        return;
    }

    /* The first byte is length of HRPD Access Authentication User Profile Parameters Block */
    ucFileLen = pstUsimRead->aucEf[0];
    /* The second byte is length of NAI*/
    ucNAILen  = pstUsimRead->aucEf[1];

    if ((0 == ucFileLen)
        || (0 == ucNAILen)
        || (ucFileLen >= pstUsimRead->usEfLen)
        || (ucNAILen >= ucFileLen))
    {
        PPPC_WARNING_LOG3("Invalid paras. filelen:%d, NAIlen:%d, Eflen:%d.\n",
            ucFileLen, ucNAILen, pstUsimRead->usEfLen);
        return;
    }

    /* The third byte is start of NAI*/
    pucNaiData = pstUsimRead->aucEf + 2;

    /* Check NAI is regular form user@realm, Just check contain '@' char */
    while (ucLoop < ucNAILen)
    {
        if ('@' == pucNaiData[ucLoop])
        {
            enIsNAIFormValid = PS_TRUE;
            break;
        }
        ucLoop++;
    }

    if (PS_FALSE == enIsNAIFormValid)
    {
        PPPC_WARNING_LOG3("Invalid NAI form. filelen:%d, NAIlen:%d, Eflen:%d.\n",
            ucFileLen, ucNAILen, pstUsimRead->usEfLen);
        return;
    }

    pstHrpdUpp->ucHrpdUppLen = ucFileLen;
    PS_MEM_SET(pstHrpdUpp->aucHrpdUpp, 0, PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE);
    PS_MEM_CPY(pstHrpdUpp->aucHrpdUpp, pstUsimRead->aucEf + 1, ucFileLen);

    /* 保存NAI信息，供接入鉴权使用 */
    PPPC_SaveAccessAuthUserNameInfo(pstUsimRead->aucEf);

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/

/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveEsnMeid
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead
             PPPC_HRPD_ESN_MEID_STRU  *pstEsnMeid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveEsnMeid
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_ESN_MEID_STRU            *pstEsnMeid
)
{
    VOS_UINT8                           ucCount;

    /* C.S0065 5.2.24 */
    /*
    Bytes                   Description                         M/O         Length
    1       Number of bytes for ESN_ME or MEID_ME               M           1 byte
    2       Lowest-order byteLeast significant byte M 1 byte
    3                       :                                   M           1 byte
    4                       :                                   M           1 byte
    5                       :                                   M           1 byte
    6                       :                                   M           1 byte
    7                       :                                   M           1 byte
    8       Highest-order byteMost significant byte             M           1 byte
    */

    ucCount  = pstUsimRead->aucEf[0];

    if (4 == ucCount)
    {
        pstEsnMeid->enEsnMeidType       = PPPC_HRPD_ESN_MEID_TYPE_ESN;

        pstEsnMeid->u.ulEsn             = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                        | (pstUsimRead->aucEf[1]);
    }
    else
    {
        pstEsnMeid->enEsnMeidType       = PPPC_HRPD_ESN_MEID_TYPE_MEID;

        /* 如果是MEID读低32bit */
        pstEsnMeid->u.stMeid.ulMeidLow  = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                        | (pstUsimRead->aucEf[1]);

        /* 如果是MEID读高24bit */
        pstEsnMeid->u.stMeid.ulMeidHigh = (((VOS_UINT32)pstUsimRead->aucEf[7]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[6]) << (8))
                                        | (pstUsimRead->aucEf[5]);
    }

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/


/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveRuimid
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead
             PPPC_HRPD_RUIMID_STRU    *pstRuimid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveRuimid(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_RUIMID_STRU *pstRuimid)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucCount;

    /* C.S0065 5.2.17 */
    /*
    Bytes                   Description                         M/O         Length
    1                   Number of bytes                          M          1 byte
    2                   Lowest-order byte                        M          1 byte
    3                           :                                M          1 byte
    4                           :                                M          1 byte
    5                           :                                M          1 byte
    6                           :                                O          1 byte
    7                           :                                O          1 byte
    8                   Highest-order byte                       O          1 byte
    */

    ucCount                          = pstUsimRead->aucEf[0];

    pstRuimid->ucNumbytes            = ucCount;

    if (ucCount <= 4)
    {
        for (ulLoop = 0; ulLoop < ucCount; ulLoop++)
        {
            pstRuimid->ulRUIMIDLow  |= (((VOS_UINT32)pstUsimRead->aucEf[ulLoop + 1]) << (8 * ulLoop));
        }
    }
    else
    {
        pstRuimid->ulRUIMIDLow       = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                      | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                      | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                      | (pstUsimRead->aucEf[1]);

        /* 填充高字节 */
        for (ulLoop = 0; ulLoop < (VOS_UINT8)(ucCount - 4); ulLoop++)
        {
            pstRuimid->ulRUIMIDHigh |= (((VOS_UINT32)pstUsimRead->aucEf[ulLoop + 5]) << (8 * ulLoop));
        }
    }

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveUsgInd
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
             VOS_UINT8 *pucSlotCycleIndex             SlotCycleIndex
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsgInd(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_USGIND_STRU *pstUsgind)
{
    /* C.S0065 5.2.14 */
    /*
    Byte 1:     b8 b7 b6 b5 b4 b3 b2 b1
                                     *  b1=0: ESN_ME is used for CAVE Authentication and MS Identification.
                                        b1=1: UIM_ID is used for CAVE Authentication and MS Identification.
                                  *     b2=0: MEID MEID_ME is used for MS Identification.
                                        b2=1: SF_EUIMID is used for MS Identification.
                *  *  *  *  *  *        RFU
    */

    pstUsgind->ucUsgInd       = pstUsimRead->aucEf[0] & 0x03;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_Uim_ChangeNum
 功能描述  : 按照协议计还原算值
 输入参数  : ulSrcValude  -- BCD码存放的位置
             ulCodeMode   -- BCD码长度

 输出参数  : 无
 返 回 值  : VOS_UINT32 -按照协议还原计算值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 PPPC_Uim_ChangeNum(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode)
{
    VOS_UINT32                          ulTempl   = 0;
    VOS_UINT32                          ulDstValue = 0;

    if (ulCodeMode >= 3)
    {
        ulTempl = ulSrcValude / 100;        /*百位*/
        if (ulTempl + 1 <= 9)
        {
            ulDstValue += (ulTempl + 1) * 100;
        }
    }

    if (ulCodeMode >= 2)
    {
        ulTempl = (ulSrcValude / 10)  % 10; /*十位*/
        if ( ulTempl+1 <= 9)
        {
            ulDstValue += (ulTempl+1 ) * 10;
        }
    }

    if (ulCodeMode >= 1)
    {
        ulTempl = ulSrcValude % 10;         /*个位*/
        if (ulTempl +1 <= 9)
        {
            ulDstValue += ulTempl +1;
        }
    }

    return ulDstValue;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_NumToStr
 功能描述  : 将数字转为不带'/0'的字符数组
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_UIM_NumToStr(VOS_UINT8 *pucArr, VOS_UINT32 ulNum, VOS_UINT8 ucLen)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulTmp;

    ulTmp = ulNum;

    for (ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        pucArr[ucLen - ucIndex - 1] = ulTmp % 10 + '0';
        ulTmp /= 10;
    }
}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveIMSI
 功能描述  : 保存USIM卡IMSI的信息
 输入参数  : VOS_UINT8 *pucCIMSI     保存IMSI文件码流
             VOS_UINT8 *pucStrCIMSI  卡IMSI
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_INIT_SaveIMSI
(
    VOS_UINT8                           *pucCIMSI,
    PPPC_HRPD_UIM_INFO_STRU             *pstUimInfo
)
{
    VOS_UINT32                          ulMCC     = 0; /* 国家代号 */
    VOS_UINT32                          ulMNC     = 0; /* 网络代号 */
    VOS_UINT32                          ulMSIN_A  = 0; /* 移动用户身份第0 - 3位*/
    VOS_UINT32                          ulMSIN_B  = 0; /* 移动用户身份第4 - 10位*/
    VOS_UINT32                          ulMSIN_B1 = 0; /* 移动用户身份第4 - 6位*/
    VOS_UINT32                          ulMSIN_B2 = 0; /* 移动用户身份第7位*/
    VOS_UINT32                          ulMSIN_B3 = 0; /* 移动用户身份第8 - 10位*/
    VOS_UINT8                          *pucStrCIMSI = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucCIMSI) || (VOS_NULL_PTR == pstUimInfo))
    {
        return VOS_ERR;
    }

    /*
        6F22格式：
        00 AA AA BB BB BB CC 80 DD DD

        00代表CLASS=0
        AA AA根据MIN前3位计算
        BB BB BB根据MIN后7位计算
        CC根据MNC计算
        80代表IMSI_M_PROGRAMMED=1、IMSI_M_ADD_NUM=0

        DD DD根据MCC计算
        参照CDMA2000协议中6F22的格式，第1个字节和第7个字节都好搞定，基本就是标志位的设置。

        计算AA AA步骤
        1、以MIN的前3位为计算数据，分割成3个个位数，分别命名为D1、D2、D3
        2、计算数字NUM = D1 * 100 + D2 * 10 + D3 - 111（如D1、D2、D3中出现0，则当作10计算）
        3、将NUM转换为2字节小端格式16进制，位数不足在前面用0补。AA AA计算完毕

        计算BB BB BB步骤
        1、以MIN第4-6位为数据，按照AA AA的计算步骤1、2算出NUM，将NUM转换为10bit的2进制，不足用0补
        2、将MIN第7位单独取出来，按照标准10进制转2进制的计算方法，计算出4bit的2进制，不足用0补(修正：如果是0，按照10计算)
        3、以MIN第8-10位为数据，按照AA AA的计算步骤1、2算出NUM，将NUM转换为10bit的2进制，不足用0补
        4、将前3步的计算出来的共24bit的2进制数拼起来，转换成3字节小端格式16进制数。BB BB BB计算完毕

        计算CC步骤
        1、将MNC分割成2个个位数，分别命名为D1、D2
        2、计算数字NUM = D1 * 10 + D2 - 11（如D1、D2中出现0，则当作10计算）
        3、将NUM转换为1字节16进制。CC计算完毕

        计算DD DD步骤
        1、以MCC为数据，按照AA AA的计算方法，计算出2字节小端格式16进制，即为DD DD

        例子：
        已知IMSI号：460036591141482
        此IMSI中：
        MCC是460
        MNC是03
        MIN是6591141482

        计算AA AA
        MIN前3位659，NUM = 6 * 100 + 5 * 10 + 9 - 111 = 548 转换成2字节小端格式16进制为：24 02

        计算BB BB BB
        MIN第4-6位114，NUM = 1 * 100 + 1 * 10 + 4 - 111 = 3 转换成10bit的2进制为：0000000011
        MIN第7位1，转换为4bit的2进制为：0001
        MIN第8-10位482，NUM = 4 * 100 + 8 * 10 + 2 - 111 = 371 转换成10bit的2进制为：0101110011
        24bit的2进制数为：000000001100010101110011，转换成3字节小端格式16进制为：73 C5 00

        计算CC
        MNC为03，NUM = 10 * 10 + 3 - 11 = 92，转换成1字节16进制为5C

        计算DD DD
        MCC为460，NUM = 4 * 100 + 6 * 10 + 10 - 111 = 359 转换成2字节小端格式16进制为：67 01

        至此得到6F22文件内容应为
        00 24 02 73 C5 00 5C 80 67 01
        460036591141482
    */
    ulMCC     = pucCIMSI[8];
    ulMCC     = 0x0000FFFF & ( ulMCC | (pucCIMSI[9] << 8));
    ulMCC     = PPPC_Uim_ChangeNum(ulMCC,3);       /* 国家代号 */

    ulMNC     = pucCIMSI[6];
    ulMNC     = PPPC_Uim_ChangeNum(ulMNC,2);       /* 网络代号 */

    ulMSIN_A  = pucCIMSI[1];
    ulMSIN_A  = 0x0000FFFF & ( ulMSIN_A | (pucCIMSI[2] << 8));
    ulMSIN_A  = PPPC_Uim_ChangeNum(ulMSIN_A, 3);   /* 移动用户身份第0 - 3位*/

    ulMSIN_B  = pucCIMSI[3];
    ulMSIN_B  = 0x0000FFFF & (ulMSIN_B | (pucCIMSI[4] << 8));
    ulMSIN_B  = 0x00FFFFFF & (ulMSIN_B | (pucCIMSI[5] << 16));

    ulMSIN_B1 = ulMSIN_B >> 14;
    ulMSIN_B1 = PPPC_Uim_ChangeNum(ulMSIN_B1, 3); /* 移动用户身份第4 - 6位 */

    ulMSIN_B2 = (ulMSIN_B & 0x3c00)>>10;         /* 移动用户身份第7位 */
    ulMSIN_B2 = ulMSIN_B2 % 10;

    ulMSIN_B3 = ulMSIN_B & 0x3FF;
    ulMSIN_B3 = PPPC_Uim_ChangeNum(ulMSIN_B3, 3);  /* 移动用户身份第8 - 10位 */

    pucStrCIMSI = pstUimInfo->aucImsi;

    PPPC_UIM_NumToStr(pucStrCIMSI,      ulMCC,      3);
    PPPC_UIM_NumToStr(pucStrCIMSI + 3,  ulMNC,      2);
    PPPC_UIM_NumToStr(pucStrCIMSI + 5,  ulMSIN_A,   3);
    PPPC_UIM_NumToStr(pucStrCIMSI + 8,  ulMSIN_B1,  3);
    PPPC_UIM_NumToStr(pucStrCIMSI + 11, ulMSIN_B2,  1);
    PPPC_UIM_NumToStr(pucStrCIMSI + 12, ulMSIN_B3,  3);


    pstUimInfo->ucImsiLen = PS_CUE_IMSI_MAX_SIZE;

	return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveUsimAD
 功能描述  : 保存USIM卡AD的信息
 输入参数  : VOS_UINT8 *pucCIMSI     保存IMSI文件码流
             VOS_UINT8 *pucStrCIMSI  卡IMSI
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月08日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimAD
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimInfo
)
{
    const VOS_UINT8                     ucMinEFLen = 4;                         /* EFAD文件长度为3+X,X>=1才有效 */
    const VOS_UINT8                     ucMncLenOffset = 3;                     /* EFAD文件中第四个字节为MNC长度 */
    const VOS_UINT8                     ucMncDefaultLen = 2;                    /* MNC默认为2位 */
    const VOS_UINT8                     ucMncSpecialLen = 3;                    /* 部分国家MNC为三位 */
    VOS_UINT8                           ucMcnLen;

    /* 6FAD文件定义见51011-f40 10.3.18 */

    /* 检查读卡结果 */
    if ((0 != pstUsimRead->stCmdResult.ulResult)
        || (0 != pstUsimRead->stCmdResult.ulErrorCode)
        || (pstUsimRead->usEfLen < ucMinEFLen))
    {
        PPPC_WARNING_LOG3("Read usim failed. ulResult:, ulErrorCode:, Eflen:.\n",
            pstUsimRead->stCmdResult.ulResult, pstUsimRead->stCmdResult.ulErrorCode, pstUsimRead->usEfLen);
        return;
    }

    /* EFAD文件中第四个字节为MNC长度 */
    ucMcnLen = pstUsimRead->aucEf[ucMncLenOffset];

    /* MNC长度只能为2或者3 */
    if (ucMncSpecialLen != ucMcnLen)
    {
        ucMcnLen = ucMncDefaultLen;
    }

    pstUsimInfo->ucMncLen = ucMcnLen;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveUsimIMSI
 功能描述  : 保存USIM卡IMSI的信息
 输入参数  : VOS_UINT8 *pucCIMSI     保存IMSI文件码流
             VOS_UINT8 *pucStrCIMSI  卡IMSI
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月08日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimIMSI
(
    VOS_UINT8                          *pucIMSI,
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimInfo
)
{
    VOS_UINT8                            ucImsiNum;
    VOS_UINT32                           ulLoop;
    VOS_UINT8                            ucMaxImsiData;

    ucMaxImsiData               = pucIMSI[0];
    if ( ucMaxImsiData > (8) )
    {
        PPPC_WARNING_LOG1("PPPC_INIT_SaveUsimIMSI, IMSI Oversize!", ucMaxImsiData);
        ucMaxImsiData           = 8;
    }

    ucImsiNum                   = 0;

    /* 取第一个字节的高四位, 低4位丢弃不用 */
    pstUsimInfo->aucImsi[ucImsiNum]     = (( pucIMSI[1] >> 4 ) & 0x0F) + 0x30;
    ucImsiNum++;

    /* 取其余字节 */
    for ( ulLoop = 1 ; ulLoop < ucMaxImsiData; ulLoop++ )
    {
        pstUsimInfo->aucImsi[ucImsiNum] = (pucIMSI[ulLoop+1] & 0x0F) + 0x30 ;
        ucImsiNum++;

        pstUsimInfo->aucImsi[ucImsiNum] = ((pucIMSI[ulLoop+1] >> 4 ) & 0x0F) + 0x30;
        ucImsiNum++;
    }

    /* 检查读取到的IMSI最后一个字节是否有效数字串是否有效 */
    if ( 0x39 < pstUsimInfo->aucImsi[ucImsiNum - 1] || 0x30 > pstUsimInfo->aucImsi[ucImsiNum - 1])
    {
        pstUsimInfo->aucImsi[ucImsiNum - 1]= 0;
        ucImsiNum--;
    }

    pstUsimInfo->ucImsiLen = ucImsiNum;
}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveUsimInfo
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimInfo(USIMM_READFILE_CNF_STRU  *pstUsimRead)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimInfo;
    VOS_UINT32                          ulRslt;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID;
    VOS_UINT16                          usModemId;
    USIMM_CARDAPP_ENUM_UINT32           enApptype;

    usModemId                           = PPPC_UIM_GetModemId();
    stFilePath                          = pstUsimRead->stFilePath;
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstUsimInfo                         = PPPC_HRPD_GetUsimDataAddr(usModemId);
    enApptype                           = pstUsimRead->stCmdResult.enApptype;

    ulRslt  = USIMM_ChangePathToDefFileID(enApptype, stFilePath.ulPathLen, stFilePath.acPath, &enDefFileID);

    /* 将文件路径转化为ID */
    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG("PPPC_INIT_SaveUsimInfo: USIMM_ChangePathToDefFileID fail.");
        return;
    }

    /* 根据需要读取的文件ID,清除对应的读卡标志位 */
    switch(enDefFileID)
    {
        case USIMM_CSIM_EFRUIMID_ID :
        case USIMM_CDMA_EFRUIMID_ID :

            /* 保存参数 */
            PPPC_INIT_SaveRuimid(pstUsimRead, &(pstUimInfo->stRuimid));

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
            break;

        case USIMM_CSIM_EFCSIMST_ID :
        case USIMM_CDMA_EFCST_ID :

            /* 保存参数 */
            PPPC_INIT_SaveCst(pstUsimRead, &(pstUimInfo->stEfCst));

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_CST_MASK);
            break;

        case USIMM_CSIM_EFESNMEID_ID :
        case USIMM_CDMA_EFESNMEIDME_ID :

            /* 保存参数 */
            PPPC_INIT_SaveEsnMeid(pstUsimRead, &(pstUimInfo->stEsnMeid));

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
            break;

        case USIMM_CSIM_EFUSGIND_ID :
        case USIMM_CDMA_EFUSGIND_ID :

            /* 保存参数 */
            PPPC_INIT_SaveUsgInd(pstUsimRead, &(pstUimInfo->stUsgind));

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
            break;

        case USIMM_CSIM_EFHRPDUPP_ID :
        case USIMM_CDMA_EFHRPDUPP_ID :

            /* 保存参数 */
            PPPC_INIT_SaveHrpdupp(pstUsimRead, &(pstUimInfo->stHrpdUpp));

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);
            break;

        case USIMM_CSIM_EFIMSIM_ID :
        case USIMM_CDMA_EFIMSIM_ID :

            /* 保存参数 */
            PPPC_INIT_SaveIMSI(pstUsimRead->aucEf, pstUimInfo);

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_EFIMSIM_MASK);
            break;

        case USIMM_USIM_EFIMSI_ID:

            /* 保存参数 */
            PPPC_INIT_SaveUsimIMSI(pstUsimRead->aucEf, pstUsimInfo);

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_EFIMSI_MASK);
            break;
        case USIMM_USIM_EFAD_ID:

            /* 保存参数 */
            PPPC_INIT_SaveUsimAD(pstUsimRead, pstUsimInfo);

            /* 读取成功标志位 */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_EFAD_MASK);
            break;
        default:
            PPPC_WARNING_LOG1("PPPC_INIT_SaveUsimInfo, pstUsimRead->usEfId error, File:0x%x\n", enDefFileID);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetpEsnByMeid
 功能描述  : 通过MEID获取pESN
 输入参数  : PPPC_HRPD_MEID_STRU *pucMeid
             VOS_UINT32 *pulEsn
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_GetpEsnByMeid(PPPC_HRPD_MEID_STRU *pstMeid, VOS_UINT32 *pulEsn)
{
    VOS_UINT8                           aucValue[20];
    VOS_UINT8                           aucMeidTemp[PPPC_HRPD_MEID_LEN];
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulpEsn;
    PPPC_SHA1_PARA_STRU                 stPara;

    if ((VOS_NULL_PTR == pstMeid) || (VOS_NULL_PTR == pulEsn))
    {
        return VOS_ERR;
    }

    /* 56个bit长的MEID信息 */
    aucMeidTemp[0]  = (VOS_UINT8)((pstMeid->ulMeidHigh & 0x00FF0000) >> (16));
    aucMeidTemp[1]  = (VOS_UINT8)((pstMeid->ulMeidHigh & 0x0000FF00) >> (8));
    aucMeidTemp[2]  = (VOS_UINT8)( pstMeid->ulMeidHigh & 0x000000FF );
    aucMeidTemp[3]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0xFF000000) >> (24));
    aucMeidTemp[4]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0x00FF0000) >> (16));
    aucMeidTemp[5]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0x0000FF00) >> (8));
    aucMeidTemp[6]  = (VOS_UINT8)( pstMeid->ulMeidLow  & 0x000000FF);

    PS_MEM_SET(aucValue, 0, sizeof(aucValue));

    stPara.ucNum        = 1;
    stPara.apucAdrr[0]  = aucMeidTemp;
    stPara.aulLen[0]    = PPPC_HRPD_MEID_LEN;

    if (VOS_OK != PPPC_SHA1(&stPara, aucValue))
    {
        PPPC_WARNING_LOG("Error When sha1 in PPPC_GetpEsnByMeid!");
        return VOS_ERR;
    }

    /* 1.  The upper 8 bits of pseudo-ESN shall be set to 0x80.

       2.  The lower 24 bits of pseudo-ESN shall be the 24 least significant bits of the
    SHA-1 digest of the MEID. See [10] for the specification of the SHA-1
    algorithm.
    */
    ulTmp   = ((aucValue[17] << 16)
             | (aucValue[18] << 8)
             | aucValue[19]);

    ulpEsn          = ulTmp | 0x80000000;

    *pulEsn         = ulpEsn;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq00
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'00'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用MEID作为MEID，使用pESN作为ESN

            若有MEID，则使用MEID计算pESN作为ESN，否则，则直接使用ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq00(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    /* 判断是否携带MEID，若有，则使用MEID并用其计算pESN */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&(pstTerminalInfo->stMeid), &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stEsnMeid.u.ulEsn;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq01
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'01'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用MEID作为MEID，使用pUIMID作为ESN

            若有EUIMID，则使用EUIMID计算pUIMID作为ESN，否则，则直接使用pUIMID作为ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq01(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_MEID_STRU                 stMeid;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    PS_MEM_SET(&stMeid, 0, sizeof(PPPC_HRPD_MEID_STRU));

    /* 判断是否携带EUIMID，若有，则仅用其计算pUIMID作为ESN使用 */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&stMeid, &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    /* 判断是否携带MEID，若有，则仅使用MEID */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq10
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'10'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用EUIMID作为MEID，使用pESN作为ESN

            若有MEID，则使用MEID计算pESN作为ESN，否则，则直接使用ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq10(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_MEID_STRU                 stMeid;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    PS_MEM_SET(&stMeid, 0, sizeof(PPPC_HRPD_MEID_STRU));

    /* 判断是否携带MEID，若有，则仅用其计算pESN作为ESN使用 */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&stMeid, &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stEsnMeid.u.ulEsn;
    }

    /* 判断是否携带EUIMID，若有，则仅使用EUIMID作为MEID */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq11
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'11'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用EUIMID作为MEID，使用pUIMID作为ESN

            若有EUIMID，则使用EUIMID计算pUIMID作为ESN，否则，则直接使用UIMID作为ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq11(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    /* 判断是否携带EUIMID，若有，则使用EUIMID作为MEID，并用其计算pUIMID作为ESN使用 */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&(pstTerminalInfo->stMeid), &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    return;
}



/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidByUim
 功能描述  :

 3GPP2 C.S0065-B v2.0
 5.2.33  EFUSGIND (UIM_ID/SF_EUIMID Usage Indicator)

     This EF indicates whether the UIM_ID or ESN_ME is used as the 'ESN' value for
     CAVE authentication and MS identification, as per Section 4.6.1 of [46].
     This EF also indicates whether the SF_EUIMID or MEID_ME shall be used as the
     MEID field over the air when Service n34 is available.

     b1=0:   ESN_ME is used for CAVE Authentication and MS Identification.
     b1=1:    UIM_IDUIMID is used for CAVE Authentication and MS Identification.
     b2=0:    MEID MEID_ME is used for MS Identification.
     b2=1:    SF_EUIMID is used for MS Identification.

 C.S0073-A v1.0
 2.3.1.4  Method of Measurement

     Table 2 MEID and ESN fields in Extended Status Response Message
    -----------------------------------------------------------------------------------------
     No. | Mobile station support |         R-UIM            | Fields of Status Response Message
         |   of R-UIM             |     Configuration        |   MEID     |  ESN
    -----------------------------------------------------------------------------------------
     6.  |  R-UIM supported       | SF_EUIMID with bits b2b1 |   MEID     |  pESN
         |  as per [6] or [7]     | of EFUSGIND set to '00'  |            |
    -----------------------------------------------------------------------------------------
     7.  |  R-UIM supported       | SF_EUIMID with bits b2b1 |   MEID     |  pUIMID
         |  as per [6] or [7]     | of EFUSGIND set to '01'  |            |
    -----------------------------------------------------------------------------------------
     8.  |  R-UIM supported       | SF_EUIMID with bits b2b1 | SF_EUIMID  |  pESN
         |  as per [6] or [7]     | of EFUSGIND set to '10'  |            |
    -----------------------------------------------------------------------------------------
     9.  |  R-UIM supported       | SF_EUIMID with bits b2b1 | SF_EUIMID  |  pUIMID
         |  as per [6] or [7]     | of EFUSGIND set to '11'  |            |
    -----------------------------------------------------------------------------------------

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidByUim(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);

    /* 若B1为'0'，B2为'0'，使用MEID/pESN */
    if (0x00 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq00();
    }
    /* 若B1为'1'，B2为'0'，使用MEID/pUIMID */
    else if (0x01 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq01();
    }
    /* 若B1为'0'，B2为'1'，使用SF_EUIMID/pESN */
    else if (0x02 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq10();
    }
    /* 若B1为'1'，B2为'1'，使用SF_EUIMID/pUIMID */
    else if (0x03 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq11();
    }
    else
    {
        /* 其他异常场景，参考标杆，用读卡时初始化的默认值0 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_GetCIMSI
 功能描述  : 获取CSIM卡IMSI
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卡IMSI
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UIM_GetCIMSI(VOS_UINT8 aucIMSI[])
{
    VOS_UINT8                          *pucIMSI;
    VOS_UINT16                          usModemId;
    PPPC_HRPD_UIM_INFO_STRU            *pstUimData;

    usModemId                           = PPPC_UIM_GetModemId();

    pstUimData = PPPC_HRPD_GetUimDataAddr(usModemId);
    pucIMSI = pstUimData->aucImsi;
    if(0 == *pucIMSI)
    {
        PPPC_WARNING_LOG("Dont have IMSI");
        return VOS_ERR;
    }

    PS_MEM_CPY(aucIMSI, pucIMSI, PS_CUE_IMSI_MAX_SIZE);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_GetUsimIMSI
 功能描述  : 获取USIM卡IMSI
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卡IMSI
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月08日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UIM_GetUsimIMSI(VOS_UINT8 aucIMSI[])
{
    VOS_UINT8                          *pucIMSI;
    VOS_UINT16                          usModemId;
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimData;

    usModemId                           = PPPC_UIM_GetModemId();

    pstUsimData = PPPC_HRPD_GetUsimDataAddr(usModemId);
    pucIMSI = pstUsimData->aucImsi;
    if(0 == pstUsimData->ucImsiLen)
    {
        PPPC_WARNING_LOG("Dont have IMSI");
        return VOS_ERR;
    }

    PS_MEM_CPY(aucIMSI, pucIMSI, PS_CUE_IMSI_MAX_SIZE);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_UimClearnReadTimer
 功能描述  : 清除卡读文件定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_UimClearnReadTimer(VOS_VOID)
{
    PPPC_HRPD_FIXED_DATA_STRU          *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetFixedDataAddr(usModemId);

    /* 清除卡读文件定时器 */
    pstUimInfo->stUimReadTimer.hTimer = VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : PPPC_InitFixedData
 功能描述  : 初始化FidData中的数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  PPPC_InitFixedData(VOS_VOID)
{
    PPPC_HRPD_FIXED_DATA_STRU          *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetFixedDataAddr(usModemId);

    PS_MEM_SET(pstUimInfo, 0, sizeof(PPPC_HRPD_FIXED_DATA_STRU));
}

/*****************************************************************************
 函 数 名  : PPPC_ReadFixedData
 功能描述  : 从SIM卡中读取的数据以及NVIM中读出的数据等
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月11日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_ReadFixedData(VOS_VOID)
{
    PPPC_HRPD_UIM_STATUS_ENUM_UINT8     enUimStatus;
    VOS_UINT32                          ulUimFileReqMask;
    VOS_UINT32                          ulUimFileSuccMask;
    VOS_UINT32                          ulUimReadRetryCnt;
    HTIMER*                             phUimReadTimer;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usModemId;

    usModemId       = PPPC_UIM_GetModemId();

    /* 如果有卡，则读取卡信息 */
    enUimStatus     = PPPC_HRPD_GetUimStatus(usModemId);
    if ((PPPC_HRPD_CARD_STATUS_CSIM_PRESENT == enUimStatus)
        || (PPPC_HRPD_CARD_STATUS_UIM_PRESENT == enUimStatus))
    {
        ulUimFileReqMask  = PPPC_HRPD_GetUsimFileReqMask(usModemId);
        ulUimFileSuccMask = PPPC_HRPD_GetUsimFileSucMask(usModemId);

        /* 填充需要读的卡文件标示 */
        if (0 == ulUimFileReqMask)
        {
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_CST_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_EFIMSIM_MASK);

            /* 有USIM才去读取USIM的IMSI */
            if (PS_TRUE == PPPC_HRPD_GetUsimStatus(usModemId))
            {
                PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_EFIMSI_MASK);
                PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_EFAD_MASK);
            }

            ulUimFileReqMask  = PPPC_HRPD_GetUsimFileReqMask(usModemId);
        }

        /* 发送读UIM消息 */
        if (ulUimFileSuccMask != ulUimFileReqMask)
        {
            PPPC_INIT_SndUimReadReq();
        }
    }
    else
    {
        /* 重置卡状态 */
        PPPC_HRPD_SetUimStatus(usModemId, PPPC_HRPD_UIM_STATUS_ABSENT);
    }

    /* 启动3s定时器，如果读文件失败重新发起读文件命令。如果已有定时器则停掉定时器再启。*/
    phUimReadTimer    = PPPC_HRPD_UimReadTimer(usModemId);
    if (VOS_NULL_PTR != *phUimReadTimer)
    {
        PPPC_HRPD_SetUimReadRetryCnt(usModemId, 0);
        ulRet = VOS_StopRelTimer((HTIMER*)phUimReadTimer);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG1("Stop UimRead timer fail!", ulRet);
            return VOS_ERR;
        }
        PPPC_HRPD_UimClearnReadTimer();
    }

    ulUimReadRetryCnt = PPPC_HRPD_UimReadRetryCnt(usModemId);

    if (ulUimReadRetryCnt < PPPC_HRPD_UIMREAD_MAX_RETRY_CNT)
    {
        (VOS_VOID)VOS_StartRelTimer((HTIMER*)phUimReadTimer,
            MSPS_PID_PPPC, PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER_LEN,
            0, PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        ulUimReadRetryCnt++;
        PPPC_HRPD_SetUimReadRetryCnt(usModemId, ulUimReadRetryCnt);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_MD5Active
 功能描述  : MD5算法是否可用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月8日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_MD5Active(VOS_VOID)
{
    VOS_UINT8                           ucType;
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId       = PPPC_UIM_GetModemId();
    pstUimInfo      = PPPC_HRPD_GetUimDataAddr(usModemId);
    ucType          = pstUimInfo->stEfCst.aucCst[1];


    /*  b1为0说明不支持MD5算法，b2为0说明MD5算法未激活 */
    if ((0 == (ucType & 0x01)) || (0 == (ucType & 0x02)))
    {
        return PS_FALSE;
    }

    /* UIM卡6F57文件全为0或F */
    if (0 == pstUimInfo->stHrpdUpp.ucHrpdUppLen)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_RunCaveAuthReq
 功能描述  : 向UIM发送RUN CAVE命令
 输入参数  : VOS_UINT32 ulRandu
 输出参数  : 无
 返 回 值  : VOS_UINT32   是否发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UIM_RunCaveAuthReq(VOS_UINT32 ulRandu)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usModemId;

    usModemId       = PPPC_UIM_GetModemId();
    pstTerminalInfo = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    /* 分配消息内存并初始化 */
    /* 申请消息内存 */
    pstMsg = (USIMM_AUTHENTICATION_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_WARNING_LOG("PPPC_UIM_RunCaveAuthReq: Allocate Msg Failed.");
        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->stMsgHeader.enMsgName               = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.enAppType               = USIMM_CDMA_APP;
    pstMsg->stMsgHeader.ulSendPara              = 0;

    /* 填写消息体 */
    pstMsg->enAuthType                          = USIMM_RUNCAVE_AUTH;
    pstMsg->uAuth.stRunCaveAuth.ucRandType      = USIMM_RUNCAVE_RAND;
    pstMsg->uAuth.stRunCaveAuth.ucDigLen        = 0;
    pstMsg->uAuth.stRunCaveAuth.ucProcessCtrl   = PPPC_HRPD_AUTH_PROCESSCTRL_SAVE_REGS_ON;

    /* 填充 RANDU 24bit */
    pstMsg->uAuth.stRunCaveAuth.aucRand[3]      = (VOS_UINT8)( ulRandu & 0x000000FF );
    pstMsg->uAuth.stRunCaveAuth.aucRand[2]      = (VOS_UINT8)(( ulRandu & 0x0000FF00 ) >> 8);
    pstMsg->uAuth.stRunCaveAuth.aucRand[1]      = (VOS_UINT8)(( ulRandu & 0x00FF0000 ) >> 16);
    pstMsg->uAuth.stRunCaveAuth.aucRand[0]      = (VOS_UINT8)(( ulRandu & 0xFF000000 ) >> 24);

    /* 根据接入类型填充Digit内容 */
    /* 默认值为0 */
    pstMsg->uAuth.stRunCaveAuth.aucDigits[0]    = 0;
    pstMsg->uAuth.stRunCaveAuth.aucDigits[1]    = 0;
    pstMsg->uAuth.stRunCaveAuth.aucDigits[2]    = 0;

    /* 填充ESN的内容 */
    pstMsg->uAuth.stRunCaveAuth.aucEsn[0]       =
                  (VOS_UINT8)(pstTerminalInfo->ulEsn & 0x000000FF);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[1]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0x0000FF00) >> 8);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[2]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0x00FF0000) >> 16);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[3]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0xFF000000) >> 24);

    if (MODEM_ID_0 == usModemId)
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, WUEPS_PID_USIM, pstMsg);
    }
    else
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, I1_WUEPS_PID_USIM, pstMsg);
    }

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPPC_UIM_RunCaveAuthReq: PPPC_UIM_SndMsg ulRslt", ulResult);
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPPC_UsimmReadFileCnfProc
 功能描述  : PPPC模块读取文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月25日
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_UsimmReadFileCnfProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulEFID;
    VOS_UINT16                          usModemId;
    VOS_UINT32                          ulRet;
    HTIMER*                             phUimReadTimer;

    usModemId = PPPC_UIM_GetModemId();
    (VOS_VOID)USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    /* 读卡成功,才保存USIM卡信息 */
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        PPPC_INIT_SaveUsimInfo(pstMsg);
    }
    else
    {
        /* 要读取的文件失败 */
        PPPC_WARNING_LOG1("PPPC_UsimmGetFileRspMsgProc, ulResult", pstMsg->stCmdResult.ulResult);
    }

    /* 如果所有的卡文件都读取完毕 */
    if (PPPC_HRPD_GetUsimFileReqMask(usModemId) == PPPC_HRPD_GetUsimFileSucMask(usModemId))
    {
        /* 根据卡文件初始化 ESN */
        PPPC_InitEsnMeidByUim();

        /* 清除定时器 */
        phUimReadTimer      = PPPC_HRPD_UimReadTimer(usModemId);
        PPPC_HRPD_SetUimReadRetryCnt(usModemId, 0);
        if (VOS_NULL_PTR != *phUimReadTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)phUimReadTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop UimRead timer fail!", ulRet);
            }
            PPPC_HRPD_UimClearnReadTimer();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PihUsimStatusIndProc
 功能描述  : 收到PIH模块上报的卡状态指示消息的预处理
 输入参数  : USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_PihUsimStatusIndProc(USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg)
{
    VOS_UINT8                           ucSimType;
    PS_BOOL_ENUM_UINT8                  enUsimStatu;


    if (USIMM_CARD_USIM == pstUsimMsg->stUsimSimInfo.enCardType)
    {
        enUsimStatu = PS_TRUE;
    }
    else
    {
        enUsimStatu = PS_FALSE;
    }

    switch (pstUsimMsg->stCsimUimInfo.enCardType)
    {
        case USIMM_CARD_UIM:
            ucSimType = PPPC_HRPD_CARD_STATUS_UIM_PRESENT;
            break;

        case USIMM_CARD_CSIM:
            ucSimType = PPPC_HRPD_CARD_STATUS_CSIM_PRESENT;
            break;

        case USIMM_CARD_NOCARD:
        case USIMM_CARD_ISIM:
        default:

            ucSimType = PPPC_HRPD_UIM_STATUS_ABSENT;
            break;
    }

    if (MAPS_PIH_PID == pstUsimMsg->ulSenderPid)
    {
        PPPC_HRPD_SetUimStatus(MODEM_ID_0, ucSimType);
        PPPC_HRPD_SetUsimStatus(MODEM_ID_0, enUsimStatu);
    }
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    else
    {
        PPPC_HRPD_SetUimStatus(MODEM_ID_1, ucSimType);
        PPPC_HRPD_SetUsimStatus(MODEM_ID_1, enUsimStatu);
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_BuildNAIByIMSI
 功能描述  : 根据IMSI构造接入鉴权使用的NAI信息
 输入参数  : VOS_UINT32 ulNAIBuffLen
 输出参数  : VOS_UINT8 *pucNAIBuff
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月02日
    作    者   : c00338085
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UIM_BuildNAIByIMSI(VOS_UINT8 *pucNAIBuff, VOS_UINT32 ulNAIBuffLen)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT16                          usModemId;
    VOS_UINT32                          ulNAIDataLen;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);

    if (0 != pstUimInfo->ucImsiLen)
    {
        ulNAIDataLen = (pstUimInfo->ucImsiLen + PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_LEN);

        /* 使用IMSI，构造形式为IMSI@mycdma.cn的NAI */
        if (ulNAIBuffLen > ulNAIDataLen)
        {
            VOS_StrNCpy((VOS_CHAR *)pucNAIBuff, (VOS_CHAR *)pstUimInfo->aucImsi, pstUimInfo->ucImsiLen);
            VOS_StrNCpy((VOS_CHAR *)(pucNAIBuff + pstUimInfo->ucImsiLen), PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_STR, PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_LEN);
            pucNAIBuff[ulNAIDataLen] = '\0';

            return VOS_OK;
        }
    }
    else
    {
        /* 固定使用写死的NAI */
        if (ulNAIBuffLen > PPPC_HRPD_AUTH_NAI_STUB_LEN)
        {
            VOS_StrNCpy((VOS_CHAR *)pucNAIBuff, PPPC_HRPD_AUTH_NAI_STUB_STR, PPPC_HRPD_AUTH_NAI_STUB_LEN);
            pucNAIBuff[PPPC_HRPD_AUTH_NAI_STUB_LEN] = '\0';

            return VOS_OK;
        }
    }

    pucNAIBuff[0] = '\0';
    PPPC_WARNING_LOG2("Build NAI Fail. NAIBuffLen:%d, ImsiLen:%d.\n", ulNAIBuffLen, pstUimInfo->ucImsiLen);

    return VOS_ERR;
}

/*****************************************************************************
  函 数 名  : PPPC_UIM_SendEapAuthReq
  功能描述  : 向卡发送EAP鉴权请求
  输入参数  : pucRand        AT_RAND
              pucAutn        AT_AUTN
              ucIdentifier   透传参数
  输出参数  : 无
  返 回 值  : VOS_UINT32
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UIM_SendEapAuthReq
(
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn,
    VOS_UINT8                           ucIdentifier
)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg;
    VOS_UINT16                          usModemId;


    /* 内部调用，保证入参非空 */

    /* 申请消息内存 */
    pstMsg   = (USIMM_AUTHENTICATION_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_AUTHENTICATION_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*填充消息内容*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_AUTHENTICATION_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    usModemId = PPPC_UIM_GetModemId();
    if (MODEM_ID_0 == usModemId)
    {
        pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_USIM;
    }
    else
    {
        pstMsg->stMsgHeader.ulReceiverPid     = I1_WUEPS_PID_USIM;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara            = (VOS_UINT32)ucIdentifier;

    pstMsg->enAuthType                        = USIMM_3G_AUTH;

    pstMsg->uAuth.st3GAuth.stAutn.ucDataLen  = PPPC_EAP_AUTN_LEN;
    pstMsg->uAuth.st3GAuth.stRand.ucDataLen  = PPPC_EAP_RAND_LEN;

    PS_MEM_CPY(pstMsg->uAuth.st3GAuth.stAutn.aucData, pucAutn, PPPC_EAP_AUTN_LEN);
    PS_MEM_CPY(pstMsg->uAuth.st3GAuth.stRand.aucData, pucRand, PPPC_EAP_AUTN_LEN);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_UIMEAP_AUTH_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
  函 数 名  : PPPC_UIM_GetImsiMncLen
  功能描述  : 获取MNC长度
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_UINT8
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2016年1月25日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 PPPC_UIM_GetImsiMncLen(VOS_VOID)
{
    VOS_UINT16                          usModemId;
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimData;
    VOS_UINT8                           ucMncLen;
    const VOS_UINT8                     ucMncDefaultLen = 2;                    /* MNC默认为2位 */
    const VOS_UINT8                     ucMncSpecialLen = 3;                    /* 部分国家MNC为三位 */

    usModemId                           = PPPC_UIM_GetModemId();

    pstUsimData = PPPC_HRPD_GetUsimDataAddr(usModemId);

    ucMncLen = pstUsimData->ucMncLen;

    /* MNC的长度只能是2或3，如果是其他值则使用默认值2 */
    if (ucMncSpecialLen != ucMncLen)
    {
        ucMncLen = ucMncDefaultLen;
    }

    return ucMncLen;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
