/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ScPersonalization.c
  版 本 号      : 初稿
  作    者      : w00184875
  生成日期      : 2012年04月07日
  最近修改      :
  功能描述      : 该C文件给出了ScPersonalization模块的实现
  函数列表      :
  修改历史      :
  1.日    期    : 2012年04月07日
    作    者    : w00184875
    修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ScInterface.h"
#include "ScComm.h"
#include "ScFactory.h"
#include "ScPersonalization.h"
#include "UsimPsInterface.h"
#include "ScCtx.h"
#include "NVIM_Interface.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e767 修改人:王笑非 00184875;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_SC_PERSONALIZATION_C
/*lint +e767 修改人:王笑非 00184875;*/

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/*****************************************************************************
  3 函数申明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : SC_PERS_GetCategoryByStatus
 功能描述  : 通过锁状态获取当前的category
 输入参数  : enSIMLockStatus: 当前锁网锁卡状态

 输出参数  : 无
 返 回 值  : SC_PERSONALIZATION_CATEGORY_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月09日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_PERSONALIZATION_CATEGORY_ENUM_UINT8 SC_PERS_GetCategoryByStatus(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enSIMLockStatus
)
{
    switch (enSIMLockStatus)
    {
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
            return SC_PERSONALIZATION_CATEGORY_NETWORK;

        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
            return SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET;

        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            return SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER;

        default:
            SC_ERROR_LOG("SC_PERS_GetCategoryByStatus: enSIMLockStatus is out of range.");
            break;
    }

    return SC_PERSONALIZATION_CATEGORY_BUTT;
}

/*****************************************************************************
 函 数 名  : SC_PERS_GetStatusByCategory
 功能描述  : 通过当前的category的信息获取锁网锁卡状态
 输入参数  : pstSimlockCatogory: 当前category的信息

 输出参数  : 无
 返 回 值  : SC_VERIFY_SIMLOCK_RESULT_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月12日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 SC_PERS_GetStatusByCategory(
    SC_SIMLOCK_CATEGORY_STRU *pstSimlockCatogory
)
{
    /* 如果所在PIN状态，根据category返回锁网锁卡状态 */
    if (SC_PERSONALIZATION_STATUS_PIN == pstSimlockCatogory->enStatus)
    {
        switch (pstSimlockCatogory->enCategory)
        {
            case SC_PERSONALIZATION_CATEGORY_NETWORK:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN;

            case SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN;

            case SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                return SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN;

            default:
                SC_ERROR_LOG("SC_PERS_GetStatusByCategory: pstSimlockCatogory is out of range.");
                return SC_VERIFY_SIMLOCK_RESULT_BUTT;
        }
    }

    if (SC_PERSONALIZATION_STATUS_PUK == pstSimlockCatogory->enStatus)
    {
        switch (pstSimlockCatogory->enCategory)
        {
            case SC_PERSONALIZATION_CATEGORY_NETWORK:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK;

            case SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK;

            case SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                return SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK;

            default:
                SC_ERROR_LOG("SC_PERS_GetStatusByCategory: pstSimlockCatogory is out of range.");
                return SC_VERIFY_SIMLOCK_RESULT_BUTT;
        }
    }

    return SC_VERIFY_SIMLOCK_RESULT_BUTT;
}


/*****************************************************************************
 函 数 名  : SC_PERS_Bcd2Num
 功能描述  : 对锁网锁卡号段，做BCD码到数字的转换
 输入参数  : pucBcdNum: 输入的BCD码
             ulBcdNumLen:BCD码长度
 输出参数  : pucDestNum: 数据转换后输出内容
 返 回 值  : NA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月9日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_VOID SC_PERS_Bcd2Num(
    VOS_UINT8                          *pucDestNum,
    const VOS_UINT8                    *pucBcdNum,
    VOS_UINT32                          ulBcdNumLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucFirstNumber;
    VOS_UINT8                           ucSecondNumber;

    for (i = 0; i < ulBcdNumLen; i++)
    {
        /* 分别取出高低字节 */
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + i)) & 0x0f);
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + i)) >> 4) & 0x0f);

        if (ucFirstNumber <= 9)
        {
            *pucDestNum++ = ucFirstNumber;
        }

        if (ucSecondNumber <= 9)
        {
            *pucDestNum++ = ucSecondNumber;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : SC_PERS_ImsiBcd2Num
 功能描述  : 将输入的IMSI转换成数字输出
 输入参数  : ucLen: IMSI的长度，9字节
             pucImsi:IMSI的内容
 输出参数  : pucNum: 数据转换后输出内容
 返 回 值  : NA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月9日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_ImsiBcd2Num(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                    *pucImsi,
    VOS_UINT8                          *pucNum
)
{
    VOS_UINT8                           ucFirstByte;
    VOS_UINT8                           ucTmp;

    ucFirstByte = pucImsi[0];

    /* 如果IMSI第一个字节大于0x08，说明IMSI数据不正确 */
    if (SC_IMSI_FIRST_BYTE < ucFirstByte)
    {
        SC_ERROR_LOG("SC_PERS_ImsiBcd2Num: IMSI is wrong.");

        return VOS_ERR;
    }

    ucTmp = (pucImsi[1]>>4) & 0x0F;

    /* 先转换IMSI第二个字节 */
    SC_PERS_Bcd2Num(pucNum, &ucTmp, 1);

    /* 转换IMSI后面的字节 */
    SC_PERS_Bcd2Num(pucNum + 1, pucImsi + 2, ucLen - 2);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_PERS_SPBcd2Num
 功能描述  : 将输入的SP转换成数字输出
 输入参数  : ucLen: SP的长度，1字节
             pucSP:SP的内容
 输出参数  : pucNum: 数据转换后输出内容
 返 回 值  : NA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月18日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_SPBcd2Num(
    VOS_UINT8                          *pucNum,
    const VOS_UINT8                    *pucSP,
    VOS_UINT8                           ucLen
)
{
    /* 参数检查 */
    if ((0xFF == *pucSP) || (ucLen > SC_SP_LEN))
    {
        SC_ERROR_LOG("SC_PERS_SPBcd2Num: Para is wrong.");

        return VOS_ERR;
    }

    *pucNum = ((*pucSP)>>4) & 0x0F;

    *(pucNum + 1) = *pucSP & 0x0F;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_PERS_CheckSimlockCodeLast2Char
 功能描述  : 检查锁网锁卡号码数字串最后两位的合法性
 输入参数  : SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory     -- 号段类型
 输出参数  : VOS_UINT8                              *pucLast2Num    -- 数字串最后两位
 返 回 值  : VOS_UINT32     -- 转换结果
                VOS_OK      -- 转换成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_CheckSimlockCodeLast2Char(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucLast2Num
)
{
    VOS_UINT8                           i           = 0;

    /* 检测最后两位的有效性, NET无需检测 */
    if (SC_PERSONALIZATION_CATEGORY_NETWORK < enCategory)
    {
        for (i = 0; i < 2; i++)
        {
            /* NETSUB支持范围: 0x00~0x99 */
            if (9 >= pucLast2Num[i])
            {
                continue;
            }
            /* SP支持范围: 0x00~0xFF */
            else if ( (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == enCategory)
                   && (0x0F >= pucLast2Num[i]) )
            {
                continue;
            }
            else
            {
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_PERS_CheckSimlockCodeNum
 功能描述  : 检查锁网锁卡号码数字串合法性，并返回正确的长度
 输入参数  : SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory     -- 号段类型
 输出参数  : VOS_UINT8                              *pucNum         -- 检查后的数字串
             VOS_UINT8                              *pucDepartLen   -- 数字串正确的长度
 返 回 值  : VOS_UINT32     -- 转换结果
                VOS_OK      -- 转换成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月14日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_CheckSimlockCodeNum(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucNum,
    VOS_UINT8                              *pucDepartLen
)
{
    VOS_UINT8                           i           = 0;
    VOS_UINT8                           j           = 0;
    VOS_UINT8                           ucDepartLen;        /* 数字串正确的长度 */
    VOS_UINT8                          *pucTmpNum;

    pucTmpNum   = pucNum;

    switch(enCategory)
    {
        case SC_PERSONALIZATION_CATEGORY_NETWORK:
            ucDepartLen = SC_NET_CODE_DEPART_LEN;
            break;
        default:
            ucDepartLen = SC_CODE_DEPART_LEN;
            break;
    }

    /* 检测PLMN合法性及其位数 */
    for (i = 0; i < SC_NET_CODE_DEPART_LEN; i++)
    {
        if (9 >= pucTmpNum[i])
        {
            continue;
        }
        else if ( ((SC_NET_CODE_DEPART_LEN - 1) == i)
               && (0x0F == pucTmpNum[i]) )
        {
            for (j = i + 1; j < ucDepartLen; j++)
            {
                pucTmpNum[j - 1] = pucTmpNum[j];
            }
            ucDepartLen = ucDepartLen - 1;
            break;
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pucDepartLen           = ucDepartLen;

    /* 检测锁网锁卡号码最后两位的合法性 */
    if (VOS_OK != SC_PERS_CheckSimlockCodeLast2Char(enCategory, &pucTmpNum[ucDepartLen - 2]))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_PERS_SimlockCodeBcd2Num
 功能描述  : 对锁网锁卡号段，做BCD码到数字的转换
 输入参数  : const VOS_UINT8                        *pucBCD         -- 待转换BCD号段
             VOS_UINT8                              *pucDepartLen   -- 转换后BCD码的长度
             SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory     -- 号段类型
 输出参数  : VOS_UINT8                              *pucNum         -- 转换后的数字串
 返 回 值  : VOS_UINT32     -- 转换结果
                VOS_OK      -- 转换成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月18日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_SimlockCodeBcd2Num(
    VOS_UINT8                              *pucNum,
    VOS_UINT8                              *pucDepartLen,
    const VOS_UINT8                        *pucBCD,
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory
)
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucFirstNum;
    VOS_UINT8                           ucSecondNum;
    VOS_UINT8                          *pucTmpNum;
    VOS_UINT8                           ucNum;
    VOS_UINT8                           i;

    /*lint -e534*/
    VOS_MemSet(pucNum, 0x00, SC_CODE_DEPART_LEN);
    /*lint +e534*/
    pucTmpNum   = pucNum;

    switch(enCategory)
    {
        case SC_PERSONALIZATION_CATEGORY_NETWORK:
            ucLen       = SC_NET_CODE_LEN;
            break;
        case SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
            ucLen       = SC_NETSUB_CODE_LEN;
            break;
        case SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
            ucLen       = SC_SP_CODE_LEN;
            break;
        default:
            return VOS_ERR;
    }

    for (i = 0; i < ucLen; i++)
    {
        /* 分别取出高低字节 */
        ucFirstNum  = (VOS_UINT8)((*(pucBCD + i)) & 0x0F);
        ucSecondNum = (VOS_UINT8)(((*(pucBCD + i)) >> 4) & 0x0F);

        *pucTmpNum++    = ucFirstNum;
        *pucTmpNum++    = ucSecondNum;
    }

    /* 将第四位号码后移到第六位(与产线对接) */
    pucTmpNum           = &pucNum[SC_CODE_FOURTH_NUM_INDEX];
    ucNum               = pucTmpNum[0];
    pucTmpNum[0]        = pucTmpNum[1];
    pucTmpNum[1]        = pucTmpNum[2];
    pucTmpNum[2]        = ucNum;

    /* 对高低字节转换后的锁网锁卡号码进行合法性检查 */
    if (VOS_OK != SC_PERS_CheckSimlockCodeNum(enCategory, pucNum, pucDepartLen))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_PERS_CheckCode
 功能描述  : 进行号段校验
 输入参数  : stSimLockCat:每一个类别的结构
             pucIMSI:IMSI拆分后的数字串
             enModemID:Modem ID

 输出参数  : 无
 返 回 值  : VOS_TRUE:校验通过
             VOS_FALSE:校验失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月10日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_UINT32 SC_PERS_CheckCode(
    SC_SIMLOCK_CATEGORY_STRU           *pstSimLockCat,
    VOS_UINT8                          *pucIMSI,
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT8                           aucExCode[SC_SP_DEPART_LEN];
    VOS_UINT8                           aucPLMNEx[SC_IMSI_DEPART_LEN];
    VOS_UINT8                           ucBeginLen;
    VOS_UINT8                           ucEndLen;
    VOS_UINT8                           aucCodeBegin[SC_CODE_DEPART_LEN];
    VOS_UINT8                           aucCodeEnd[SC_CODE_DEPART_LEN];
    VOS_INT32                           lResultBegin;
    VOS_INT32                           lResultEnd;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           i;
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf = VOS_NULL_PTR;
    VOS_UINT32                          aucExCmpLen[SC_MAX_SUPPORT_CATEGORY] = {0, SC_NET_SUB_DEPART_LEN, SC_SP_DEPART_LEN};
    VOS_UINT32                          ulSimSvr;
    VOS_UINT32                          ulUsimSvr;

    /* 没有激活，返回号段匹配*/
    if (SC_PERSONALIZATION_INDICATOR_INACTIVE == pstSimLockCat->enIndicator)
    {
        SC_INFO1_LOG("SC_PERS_CheckCode: The indicator is not active.",
                     pstSimLockCat->enCategory);

        return VOS_TRUE;
    }

    /* 已经解锁过，返回号段匹配 */
    if (SC_PERSONALIZATION_STATUS_READY == pstSimLockCat->enStatus)
    {
        SC_INFO1_LOG("SC_PERS_CheckCode: The status is not active.",
                     pstSimLockCat->enStatus);

        return VOS_TRUE;
    }

    /* 判断PI文件类别的合法性，是否支持 */
    if (pstSimLockCat->enCategory >= SC_MAX_SUPPORT_CATEGORY)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCode: The Category is out of range.",
                      pstSimLockCat->enCategory);

        return VOS_FALSE;
    }

    /*lint -e534*/
    VOS_MemCpy(aucPLMNEx, pucIMSI, SC_IMSI_DEPART_LEN);

    VOS_MemSet(aucExCode, 0, SC_SP_DEPART_LEN);
    /*lint +e534*/

    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == pstSimLockCat->enCategory)
    {
        /* 如果服务不可用直接返回失败 */
        ulSimSvr = SC_COMM_IsUsimServiceAvailable(SIM_SVR_GIDL1,  enModemID);
        ulUsimSvr = SC_COMM_IsUsimServiceAvailable(USIM_SVR_GID1, enModemID);

        if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulSimSvr)
            && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulUsimSvr))
        {
            SC_ERROR1_LOG("SC_PERS_CheckCode: USIMM_IsServiceAvailable is failed.",
                          PS_USIM_SERVICE_NOT_AVAILIABLE);

            return VOS_FALSE;
        }

        /* 读取GID1文件，失败返回号段不匹配 */
        ulResult = SC_COMM_GetUsimmCachedFile(USIMM_USIM_EFGID1_STR, &ulEfLen, &pucEf, USIMM_GUTL_APP, enModemID);

        if (VOS_OK != ulResult)
        {
            SC_ERROR1_LOG("SC_PERS_CheckCode: USIMM_GetCachedFile is failed.",
                          ulResult);

            return VOS_FALSE;
        }

        if (VOS_OK != SC_PERS_SPBcd2Num(aucExCode, pucEf, SC_SP_LEN))
        {
            SC_ERROR1_LOG("SC_PERS_CheckCode: USIMM_GetCachedFile is failed.",
                          ulResult);

            return VOS_FALSE;
        }
    }

    /* 在配置的号段数组中循环比较 */
    for (i = 0; i < pstSimLockCat->ucGroupNum; i++)
    {
        /* 转换号段Begin, 转换失败则认为不在此号段范围内 */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeBegin,
                                                 &ucBeginLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeBegin,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        /* 转换号段End, 转换失败则认为不在此号段范围内 */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeEnd,
                                                 &ucEndLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeEnd,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        /* 号段的Begin和End长度不一致, 认为不在此号段范围内 */
        if (ucBeginLen != ucEndLen)
        {
            continue;
        }

        /* 补齐PLMN后面的扩展SP字节 */
        if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == pstSimLockCat->enCategory)
        {
            /*lint -e534*/
            VOS_MemCpy(aucPLMNEx, pucIMSI, SC_IMSI_DEPART_LEN);

            VOS_MemCpy(&aucPLMNEx[ucBeginLen - aucExCmpLen[pstSimLockCat->enCategory]],
                        aucExCode,
                        SC_SP_DEPART_LEN);
            /*lint +e534*/
        }

        /* 确保比较号段长度不会大于8 */
        if ((ucBeginLen > SC_CODE_DEPART_LEN)||(ucEndLen > SC_CODE_DEPART_LEN))
        {
            return VOS_FALSE;
        }

        lResultBegin    = VOS_MemCmp(aucPLMNEx, aucCodeBegin, ucBeginLen);

        lResultEnd      = VOS_MemCmp(aucPLMNEx, aucCodeEnd, ucEndLen);

        /* 号段在范围内 */
        if ((lResultBegin >= 0) && (lResultEnd <= 0))
        {
            return VOS_TRUE;
        }
    }

    SC_ERROR_LOG("SC_PERS_CheckCode: The result is failed.");

    /* 如果匹配失败 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : SC_PERS_VerifySimLock
 功能描述  : 进行锁网锁卡校验
 输入参数  : enModemID:Modem ID

 输出参数  : pucSimLockResult:锁网锁卡状态
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                 enModemID
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf;
    VOS_UINT8                           aucIMSI[SC_IMSI_DEPART_LEN];
    VOS_UINT32                          ulCatIndex;
    SC_PI_FILE_STRU                    *pstPIFile;

    /*针对如下两种情况，需判断此单板的HUK是否无效(无效即为全0，代表未写入HUK)，
      若无效，则按照不锁网处理:
      1.产线试制若不走锁网锁卡定制工位，则HUK不写入，此情况需保证单板不被锁住，可正常使用;
      2.某些运营商不定制锁网，则产线可能不走锁网锁卡定制工位，则HUK不写入，此情况需保证单板不被锁住，可正常使用*/
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;

        SC_INFO1_LOG("#info:SC_PERS_VerifySimLock:huk not valid,modem is: .", enModemID);

        return SC_ERROR_CODE_NO_ERROR;
    }

    *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_BUTT;

    /* 申请PI文件缓冲内存 */
    pstPIFile = (SC_PI_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstPIFile)
    {
        SC_ERROR_LOG("SC_PERS_VerifySimLock: VOS_MemAlloc is failed.");

        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取PI文件并进行校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstPIFile,
                                            sizeof(SC_PI_FILE_STRU));

    /* 返回失败 */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_VerifySimLock: SC_COMM_ReadSCFileAndCmpSign is failed.",
                      ulResult);

        return ulResult;
    }

    pucEf   = VOS_NULL_PTR;
    ulEfLen = 0;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 判断是否为电信制式 */
    if (SC_PERS_PLATFORM_C == SC_PERS_SupportPlatform(enModemID))
    {
        if (MODEM_ID_0 != enModemID)
        {
            (VOS_VOID)VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);

            *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;

            return SC_ERROR_CODE_NO_ERROR;
        }

        /* 6F22 */
        ulResult = SC_PERS_CDMAVrifySimLock(penVerifySimlockRslt, pstPIFile, enModemID);

        (VOS_VOID)VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);

        return ulResult;
    }
#endif

    /* 调用USIMM_GetCachedFile获取IMSI */
    ulResult = SC_COMM_GetUsimmCachedFile(USIMM_USIM_EFIMSI_STR, &ulEfLen, &pucEf, USIMM_GUTL_APP, enModemID);

    /* 返回失败 */
    if (USIMM_API_SUCCESS != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_VerifySimLock: USIMM_GetCachedFile is failed.",
                      ulResult);

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;
        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 由BCD转换为数字 */
    ulResult = SC_PERS_ImsiBcd2Num((VOS_UINT8)ulEfLen, pucEf, aucIMSI);

    if (VOS_OK != ulResult)
    {
        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN;

        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_VerifySimLock: SC_PERS_ImsiBcd2Num is failed.",
                      ulResult);

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 循环category进行号段校验 */
    for (ulCatIndex = 0; ulCatIndex < SC_MAX_SUPPORT_CATEGORY; ulCatIndex++)
    {
        ulResult = SC_PERS_CheckCode(&pstPIFile->astSimlockCategory[ulCatIndex],
                                     aucIMSI,
                                     enModemID);

        if (VOS_FALSE == ulResult)
        {
            *penVerifySimlockRslt = SC_PERS_GetStatusByCategory(&pstPIFile->astSimlockCategory[ulCatIndex]);
            break;
        }

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_PERS_AsciiNum2DecNum
 功能描述  : SC模块数字字符串转换为十进制数字串
 输入参数  : VOS_UINT8     *pucAsciiNum -- 待转换字符数组
             VOS_UINT32     ulLen       -- 字符数组长度
 输出参数  : VOS_UINT8     *pucDecNum   -- 转转换后的十进制数字串
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月01日
    作    者   : d00212987
    修改内容   : Imei 修改问题单修改新增函数
*****************************************************************************/
VOS_VOID SC_PERS_AsciiNum2DecNum(
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucDecNum,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndex         = 0;

    /* 参数指针由调用者保证不为NULL, 该处不做判断 */
    /* 只判断 "0" ~ "9" */

    for (ulIndex = 0; ulIndex < ulLen; ulIndex++)
    {
        /* 判断是否是数字 */
        if ( ('0' <= pucAsciiNum[ulIndex]) && ('9' >= pucAsciiNum[ulIndex]) )
        {
            pucDecNum[ulIndex] = pucAsciiNum[ulIndex] - '0';
        }
    }

    return ;
}

/*****************************************************************************
 函 数 名  : SC_PERS_ReadCMPIMEI
 功能描述  : IMEI读校验。
 输入参数  : enModemID    : 卡0 或者卡 1

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : d00212987
    修改内容   : IMEI验证
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_ReadCMPIMEI(MODEM_ID_ENUM_UINT16 enModemID)
{
    VOS_UINT8                           aucScImei [SC_RSA_ENCRYPT_LEN]  = {0};
    VOS_UINT8                           aucPubImei[SC_IMEI_LEN + 1] = {0};
    VOS_UINT8                           aucNvImei [SC_IMEI_NV_LEN]  = {0};
    VOS_UINT32                          ulPubLen = SC_IMEI_LEN;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucImeiNum[SC_IMEI_NV_LEN] = {0};

    /* HUK 是否写入*/
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        SC_INFO1_LOG("#info:SC_PERS_ReadCMPIMEI:huk not valid,modem is: .", enModemID);

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 读取IMEI-FILE并进行签名校验 */
    SC_INFO1_LOG("#info:SC_PERS_ReadCMPIMEI: modem id is: .", enModemID);
    if (MODEM_ID_0 == enModemID)
    {
        ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_IMEI_I0,
                                                aucScImei,
                                                SC_RSA_ENCRYPT_LEN);
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (MODEM_ID_1 == enModemID)
    {
        ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_IMEI_I1,
                                                aucScImei,
                                                SC_RSA_ENCRYPT_LEN);
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemID)
    {
        ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_IMEI_I2,
                                                aucScImei,
                                                SC_RSA_ENCRYPT_LEN);
    }
#endif
#endif
    else
    {
        SC_ERROR_LOG("SC_PERS_ReadCMPIMEI: modem id  error.");
        return SC_ERROR_CODE_MODEM_ID_FAIL;
    }

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_ReadCMPIMEI: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* IMEI 密文解密 */
    ulResult = SC_COMM_RsaDecrypt(aucScImei, SC_RSA_ENCRYPT_LEN, aucPubImei, &ulPubLen);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_ReadCMPIMEI: SC_COMM_RsaDecrypt is failed.", ulResult);

        return ulResult;
    }

    /* 由于AT命令下发密文码流直接保存到文件中，再次解密得到的明文是字符串，
       NV项读取的到得码流是十进制数字串，存在不一致，统一转换成十进制数字串  */
    SC_PERS_AsciiNum2DecNum(aucPubImei, aucImeiNum, ulPubLen);

    /* 读取NV中明文IMEI 比较 */
    ulResult = NV_ReadEx(enModemID, en_NV_Item_IMEI, aucNvImei, SC_IMEI_NV_LEN);
    if (NV_OK != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_ReadCMPIMEI: NV_Read Imei is failed.", ulResult);

        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    /* 判断明文IMEI是否相等, IMEI 明文长度 15位 */
    if (VOS_OK != VOS_MemCmp(aucImeiNum, aucNvImei, SC_IMEI_LEN))
    {
        SC_ERROR_LOG("SC_PERS_ReadCMPIMEI: MemCmp Imei is failed.");

        return SC_ERROR_CODE_CMP_IMEI_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
函 数 名  : SC_PERS_IsIMEIValid
功能描述  : 检查IMEI是否有效
输入参数  : pucNvImei : NV IMEI值
输出参数  : 无
返 回 值  : VOS_FALSE/VOS_TRUE

修订记录  :
1.日    期  : 2015年12月1日
  作    者  : d00212987
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 SC_PERS_IsIMEIValid(
    VOS_UINT8                           *pucNvImei
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < SC_IMEI_LEN; ucIndex++)
    {
        if (0x00 != pucNvImei[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : SC_PERS_CheeckImei2ReplaceFlg
 功能描述  : Check是否需要开启modem0 IMEI替换modem2。
 输入参数  : enModemID: 卡0 或者卡1

 输出参数  : NA
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : d00212987
    修改内容   : IMEI验证
*****************************************************************************/
VOS_BOOL SC_PERS_CheeckImei2ReplaceFlg(
    MODEM_ID_ENUM_UINT16                enModemID)
{

    VOS_BOOL                            bRpelaceFlg = VOS_FALSE;
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
    NV_SC_PERS_CTRL_STRU                stNVScpersCtrl;
    VOS_UINT8                           aucNvImei [SC_IMEI_NV_LEN]  = {0};
    VOS_UINT32                          ulResult;

    VOS_MemSet(&stNVScpersCtrl, 0, sizeof(NV_SC_PERS_CTRL_STRU));

    if (MODEM_ID_2 == enModemID)
    {
        /* 读取NV中明文IMEI */
        ulResult = NV_ReadEx(enModemID, en_NV_Item_IMEI, aucNvImei, SC_IMEI_NV_LEN);
        if (NV_OK != ulResult)
        {
            SC_ERROR1_LOG("SC_PERS_CheeckImei2ReplaceFlg: NV_Read Imei is failed.", ulResult);

            return bRpelaceFlg;
        }

        /* 判断IMEI2是否有效 */
        if (VOS_TRUE == SC_PERS_IsIMEIValid(aucNvImei))
        {
            return bRpelaceFlg;
        }

        /* 读取nv项判断是否开启替换功能 */
        ulResult = NV_Read(en_NV_Item_NV_SC_PERS_CTRL_CFG, &stNVScpersCtrl, sizeof(NV_SC_PERS_CTRL_STRU));
        if (NV_OK != ulResult)
        {
            SC_NORMAL_LOG("SC_PERS_CheeckImei2ReplaceFlg: read nv imei0 replace imei2 fail !");

            return bRpelaceFlg;
        }

        /* 开启Imei 0替换Imei 2功能 */
        if (SC_IMEI0_REPLACE_IMEI2_FLG == stNVScpersCtrl.usImei0ReplaseImei2)
        {
            bRpelaceFlg = VOS_TRUE;

            SC_NORMAL_LOG("SC_PERS_CheeckImei2ReplaceFlg: Imei 0 replace 2!");
        }
    }
#endif
#endif

    return bRpelaceFlg;
}

/*****************************************************************************
 函 数 名  : SC_PERS_VerifyIMEI
 功能描述  : Android形态下，提供给NAS检测IMEI是否验证通过API。
 输入参数  : enModemID: 卡0 或者卡1

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : d00212987
    修改内容   : IMEI验证
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyIMEI(MODEM_ID_ENUM_UINT16 enModemID)
{
/* 对读取IMEI低概率失败问题的一个规避，COMM读取三次，只要有一次成功返回，否则返回全0 */
    VOS_UINT32                          ulLoop   = 0;
    SC_ERROR_CODE_ENUM_UINT32           enResult = SC_ERROR_CODE_OTHER_ERROR;
    MODEM_ID_ENUM_UINT16                enModemTempID;

    enModemTempID = enModemID;

    if (VOS_TRUE == SC_PERS_CheeckImei2ReplaceFlg(enModemID))
    {
        /* 需要使用IMEI0替换IMEI2 */
        enModemTempID = MODEM_ID_0;
    }

    for(ulLoop=0; ulLoop<SC_MAX_CMP_IMEI; ulLoop++)
    {
        enResult = SC_PERS_ReadCMPIMEI(enModemTempID);

        if (SC_ERROR_CODE_NO_ERROR == enResult)
        {
            return SC_ERROR_CODE_NO_ERROR;
        }
    }

    return enResult;
}

/*****************************************************************************
 函 数 名  : SC_PERS_NoVerifyNvReadImei
 功能描述  : 读取存在NV里的IMEI
             说明:不对IMEI的合法性作校验，直接去读NV,区别于NV_Read接口，SC_PERS_NoVerifyNvReadImei接口在modem2 IMEI没写的情况下，读取modem0
 输入参数  : enModemID : Modem ID
             usID      : Nv id
             ulLength  : Nv 长度

 输出参数  : *pItem    : 获取NV 内容
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : d00212987
    修改内容   : IMEI验证
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_NoVerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemTempID;

    enModemTempID = enModemID;

    if (VOS_TRUE == SC_PERS_CheeckImei2ReplaceFlg(enModemID))
    {
        /* 需要使用IMEI0替换IMEI2 */
        enModemTempID = MODEM_ID_0;
    }

    /* 读取NV */
    ulResult = NV_ReadEx(enModemTempID, usID, pItem, ulLength);
    if (NV_OK != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_NoVerifyNvReadImei: NV_Read fail.", ulResult);

        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_PERS_VerifyNvReadImei
 功能描述  : 读取存在NV里的IMEI,增加IMEI验证(返回值为:SC_ERROR_CODE_NO_ERROR,读取的NV内容可用，否则不可用)
             说明:先校验IMEI号的合法性，然后再读取NV，如果IMEI号非法返回全0 IMEI,并且在modem2 imei 没写的情况下，读取modem0
 输入参数  : enModemID : Modem ID
             usID      : Nv id
             ulLength  : Nv 长度

 输出参数  : *pItem    : 获取NV 内容
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32

 修改历史      :
  1.日    期   : 2013年5月25日
    作    者   : d00212987
    修改内容   : IMEI验证
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* IMEI 校验 */
    ulResult = SC_PERS_VerifyIMEI(enModemID);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR_LOG("SC_PERS_VerifyNvReadImei: Verify IMEI fail.");

        /*lint -e534*/
        VOS_MemSet(pItem, 0, ulLength);
        /*lint +e534*/

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 读取NV */
    ulResult = SC_PERS_NoVerifyNvReadImei(enModemID, usID, pItem, ulLength);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_VerifyNvReadImei: NV_Read fail.", ulResult);

        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_PERS_CheckCryptoCKUKPwd
 功能描述  : CK/UK密码的校验
 输入参数  : pucPwd: 解锁密码
             ucLen: 密码长度
             enSIMLockStatus: 锁网锁卡状态
             enCategory: 当前所在的类别

 输出参数  : 无
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_CheckCryptoCKUKPwd(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enSIMLockStatus,
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8 enCategory
)
{
    SC_CK_FILE_STRU                     stCKFile;
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT8                           aucCryptoPwd[SC_CRYPTO_PWD_LEN];

    /* 读取CK-FILE并进行签名校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_CK,
                                            (VOS_UINT8*)&stCKFile,
                                            sizeof(SC_CK_FILE_STRU));

    /* 如果结果不为SC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCryptoCKUKPwd: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 对输入的密码加密生成密文 */
    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_CK,
                                         pucPwd,
                                         ucLen,
                                         aucCryptoPwd,
                                         SC_CRYPTO_PWD_LEN);

    /* 如果结果不为SC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCryptoCKUKPwd: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* 表明所在PIN */
    if ((SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN == enSIMLockStatus))
    {
        lResult = VOS_MemCmp(aucCryptoPwd,
                             stCKFile.astCKCategory[enCategory].aucCKCryptoPwd,
                             SC_CRYPTO_PWD_LEN);
    }
    /* 表明所在PUK */
    else if ((SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK == enSIMLockStatus))
    {
        lResult = VOS_MemCmp(aucCryptoPwd,
                             stCKFile.astCKCategory[enCategory].aucUKCryptoPwd,
                             SC_CRYPTO_PWD_LEN);
    }
    else
    {
        lResult = VOS_ERR;
    }

    /* 密码密文比对失败 */
    if (VOS_OK != lResult)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCryptoCKUKPwd: VOS_MemCmp is failed.", lResult);

        return SC_ERROR_CODE_UNLOCK_KEY_INCORRECT;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_PERS_UpdateSimlockStatus
 功能描述  : 根据密码校验结果更新PI文件中的锁网锁卡状态
 输入参数  : enResult: 密码校验的结果
             pstSimlockCategory: 锁网锁卡的类别信息
             penVerifySimlockRslt: 当前锁网锁卡状态

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月12日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
VOS_VOID SC_PERS_UpdateSimlockStatus(
    SC_ERROR_CODE_ENUM_UINT32               enResult,
    SC_SIMLOCK_CATEGORY_STRU               *pstSimlockCategory,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8    *penVerifySimlockRslt
)
{
    /* 密码校验成功 */
    if (SC_ERROR_CODE_NO_ERROR == enResult)
    {
        /* 更新锁网锁卡的状态，同时次数更新为最大值 */
        if (SC_PERSONALIZATION_STATUS_PIN == pstSimlockCategory->enStatus)
        {
            pstSimlockCategory->enStatus = SC_PERSONALIZATION_STATUS_READY;
        }
        else
        {
            pstSimlockCategory->enStatus = SC_PERSONALIZATION_STATUS_PIN;
        }

        pstSimlockCategory->ucRemainUnlockTimes = pstSimlockCategory->ucMaxUnlockTimes;
    }
    else
    {
        /* PIN状态且失败 */
        if ((SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN == *penVerifySimlockRslt)
            || (SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN == *penVerifySimlockRslt)
            || (SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN == *penVerifySimlockRslt))
        {
            /*更新锁网锁卡剩余次数-1*/
            pstSimlockCategory->ucRemainUnlockTimes -= 1;

            /* 如果剩余次数为0，更新为PUK */
            if (0 == pstSimlockCategory->ucRemainUnlockTimes)
            {
                pstSimlockCategory->enStatus = SC_PERSONALIZATION_STATUS_PUK;
            }
        }
        else
        {
            /*PUK状态且执行失败*/
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : SC_PERS_UnLock
 功能描述  : 解锁或UNBLOC操作
 输入参数  : pcPwd: 解锁密码
             ucLen: 密码长度
             enModemID:Modem ID
 输出参数  : pucSimLockResult:解锁操作后的锁网锁卡状态
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    作    者   : w00184875
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UnLock(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT32                                              ulResult;
    VOS_UINT32                                              ulResultLater;
    SC_PI_FILE_STRU                                        *pstPIFile;
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;

    /* 调用SC_VerifySimLock获取锁网锁卡状态 */
    ulResult = SC_PERS_VerifySimLock(penVerifySimlockRslt, enModemID);

    /* 如果结果不为SC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UnLock: SC_PERS_VerifySimLock is failed.", ulResult);

        return ulResult;
    }

    /* 如果当前锁网锁卡状态是SC_VERIFY_SIMLOCK_RESULT_READY */
    if (SC_VERIFY_SIMLOCK_RESULT_READY == *penVerifySimlockRslt)
    {
        SC_ERROR1_LOG("SC_PERS_UnLock: The status is wrong.", *penVerifySimlockRslt);

        return SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL;
    }

    /* 对解锁码长度做判断 */
    if (SC_PERS_PWD_LEN != ucLen)
    {
        SC_ERROR1_LOG("SC_PERS_UnLock: ucLen is not 16!", ucLen);

        return SC_ERROR_CODE_OTHER_ERROR;
    }

    /* 申请PI文件缓冲内存 */
    pstPIFile = (SC_PI_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT,
                                               sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstPIFile)
    {
        SC_ERROR_LOG("SC_PERS_UnLock: VOS_MemAlloc is failed.");
        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取PI-FILE并进行签名校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstPIFile,
                                            sizeof(SC_PI_FILE_STRU));

    /* 如果结果不为SC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* 根据锁网锁卡状态获取category */
    enCategory = SC_PERS_GetCategoryByStatus(*penVerifySimlockRslt);
    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER < enCategory)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_PERS_GetCategoryByStatus return bad enCategory.", enCategory);

        return SC_ERROR_CODE_PARA_FAIL;
    }

    /* 密码校验 */
    ulResult = SC_PERS_CheckCryptoCKUKPwd(pucPwd,
                                          ucLen,
                                          *penVerifySimlockRslt,
                                          enCategory);

    /* 根据校验结果更新PI文件的状态 */
    SC_PERS_UpdateSimlockStatus(ulResult,
                                &pstPIFile->astSimlockCategory[enCategory],
                                penVerifySimlockRslt);

    /* 重新生成PI文件 */
    ulResultLater = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstPIFile,
                                            sizeof(SC_PI_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResultLater)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_COMM_WriteSecretFile is failed.", ulResultLater);

        return ulResultLater;
    }

    /* 调用SC_VerifySimLock获取锁网锁卡状态 */
    ulResultLater = SC_PERS_VerifySimLock(penVerifySimlockRslt, enModemID);

    if (SC_ERROR_CODE_NO_ERROR != ulResultLater)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_PERS_VerifySimLock is failed.", ulResultLater);

        return ulResultLater;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
    /*lint +e534*/

    return ulResult;
}


/*****************************************************************************
 函 数 名  : SC_PERS_ErasePIFile
 功能描述  : 将PI文件中除CATEGORY以外的所有数据字段全部清零
 输入参数  : pstPiFile:PI文件内容在内存中的地址

 输出参数  : NA
 返 回 值  : NA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月7日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_VOID SC_PERS_ErasePIFile(SC_PI_FILE_STRU *pstPiFile)
{
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;
    VOS_UINT32                                              i;

    for (i = 0; i < SC_MAX_SUPPORT_CATEGORY; i++)
    {
        enCategory = (SC_PERSONALIZATION_CATEGORY_ENUM_UINT8)i;

        /*lint -e534*/
        VOS_MemSet((VOS_VOID*)&pstPiFile->astSimlockCategory[i], 0, sizeof(SC_SIMLOCK_CATEGORY_STRU));
        /*lint +e534*/

        pstPiFile->astSimlockCategory[i].enCategory = enCategory;
    }

    return;
}

/*****************************************************************************
 函 数 名  : SC_PERS_EraseCKFile
 功能描述  : 将CK文件中所有数据字段全部清零
 输入参数  : pstCkFile:CK文件内容在内存中的地址

 输出参数  : NA
 返 回 值  : NA
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月12日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_VOID SC_PERS_EraseCKFile(SC_CK_FILE_STRU *pstCkFile)
{
    /*lint -e534*/
    VOS_MemSet(pstCkFile, 0, sizeof(SC_CK_FILE_STRU));
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SC_PERS_UpdatePIFile
 功能描述  : 将PI文件中对应CATEGORY的数据按AT命令的输入进行修改
 输入参数  : pstPiFile:PI文件内容在内存中的地址
             pstWriteSimLockData: 需写入PI-FILE的SIMLOCK信息

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32类型的SC错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月9日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UpdatePIFile(
    SC_PI_FILE_STRU                    *pstPiFile,
    SC_WRITE_SIMLOCK_DATA_STRU         *pstWriteSimLockData
)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT32                          ulRsaDecryptLen;
    VOS_INT                             lHashLen;
    VOS_UINT8                           aucRsaDecrypt[SC_HASH_LEN];
    VOS_UINT8                           aucHash[SC_HASH_LEN];

    if (SC_MAX_SUPPORT_CATEGORY <= pstWriteSimLockData->enCategory)
    {
        SC_ERROR_LOG("SC_PERS_UpdatePIFile: Catogory is not support.");

        return SC_ERROR_CODE_LOCK_CODE_INVALID;
    }

    /* 先使用AK-File中的公钥对aucSimlockRsaData进行解密 */
    ulRsaDecryptLen = SC_HASH_LEN;

    ulResult = SC_COMM_RsaDecrypt(pstWriteSimLockData->aucSimlockRsaData,
                                  SC_RSA_ENCRYPT_LEN,
                                  aucRsaDecrypt,
                                  &ulRsaDecryptLen);

    /* 如果进行RSA解密失败，返回错误原因值 */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdatePIFile: SC_COMM_RsaDecrypt is failed.", ulResult);

        return ulResult;
    }

    /* 通过MD5算法，计算输入锁网锁卡的号段内容的摘要 */
    lHashLen = SC_HASH_LEN;

    lResult = mdrv_crypto_hash((VOS_CHAR*)pstWriteSimLockData->astLockCode,
                          SC_MAX_CODE_NUM*sizeof(SC_PH_LOCK_CODE_STRU),
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR*)aucHash,
                          &lHashLen);

    /* 如果通过计算MD5摘要失败，返回计算HASH失败 */
    if ((VOS_OK != lResult) || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR1_LOG("SC_PERS_UpdatePIFile: mdrv_crypto_hash is failed.", ulResult);

        return SC_ERROR_CODE_GENERATE_HASH_FAIL;
    }

#if (VOS_WIN32 != VOS_OS_VER)
    /* 由于PC工程上无法模拟RSA加密(因为RSA需要私钥和公钥对，但私钥无法获取，无法模拟真实的RSA加密码流)，
        故如下这段逻辑在PC工程上不执行 */
    /* 如果RSA解密和MD5计算的摘要长度不相等，或者两者比较不相等返回 */
    if (VOS_OK != VOS_MemCmp(aucRsaDecrypt, aucHash, SC_HASH_LEN))
    {
        SC_ERROR_LOG("SC_PERS_UpdatePIFile: VOS_MemCmp is failed.");

        return SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL;
    }
#endif

    /* 将输入的锁网锁卡的号段内容写入PI文件的内存中 */
    /*lint -e534*/
    VOS_MemCpy(pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].astLockCode,
               pstWriteSimLockData->astLockCode,
               sizeof(SC_PH_LOCK_CODE_STRU) * SC_MAX_CODE_NUM);
    /*lint +e534*/

    /* 将AT命令传入的enIndicator/ucGroupNum/ucMaxUnlockTimes写入，并更新最大剩余次数 */
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].enIndicator          = pstWriteSimLockData->enIndicator;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].ucGroupNum           = pstWriteSimLockData->ucGroupNum;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].ucMaxUnlockTimes     = pstWriteSimLockData->ucMaxUnlockTimes;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].ucRemainUnlockTimes  = pstWriteSimLockData->ucMaxUnlockTimes;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].enCategory           = pstWriteSimLockData->enCategory;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].enStatus             = SC_PERSONALIZATION_STATUS_PIN;

    /* 将新生成的PI文件写入文件系统 */
    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_PI,
                                       (VOS_UINT8*)pstPiFile,
                                       sizeof(SC_PI_FILE_STRU));

    SC_INFO1_LOG("SC_PERS_UpdatePIFile: SC_COMM_WriteSecretFile result is:", ulResult);

    return ulResult;

}

/*****************************************************************************
 函 数 名  : SC_PERS_UpdateCKUKPwd
 功能描述  : 更新内存中CK和UK密码并写入CK文件
 输入参数  : pucEncryptPwd:AT命令传入的用私钥加密过的密码
             enIndicator:指定category的锁网类型是否激活
 输出参数  : pucPwd:CK文件中需要修改的密码的内存地址
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32类型的SC错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月9日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UpdateCKUKPwd(
    VOS_UINT8                                              *pucPwd,
    VOS_UINT8                                              *pucEncryptPwd,
    SC_PERSONALIZATION_INDICATOR_ENUM_UINT8                 enIndicator
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulPwdDecryptLen;
    VOS_UINT32                          ulCipherLen;
    VOS_UINT8                           aucPwdDecrypt[SC_PERS_PWD_LEN] = {0};
    VOS_UINT8                           aucCipherData[SC_CRYPTO_PWD_LEN];
    VOS_UINT8                           ucLoop;

    ulPwdDecryptLen = SC_PERS_PWD_LEN;

    /* 先使用AK-File中的公钥对pucEncryptPwd进行解密 */
    ulResult = SC_COMM_RsaDecrypt(pucEncryptPwd,
                                  SC_RSA_ENCRYPT_LEN,
                                  aucPwdDecrypt,
                                  &ulPwdDecryptLen);

    /* 如果进行RSA解密失败，返回错误原因值 */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKUKPwd: SC_COMM_RsaDecrypt is failed.", ulResult);

        return ulResult;
    }

    if (SC_PERSONALIZATION_INDICATOR_ACTIVE == enIndicator)
    {
        /* 判断解密后的密码明文是否为数值为"0"~"9"的数字 */
        for (ucLoop = 0; ucLoop < SC_PERS_PWD_LEN; ucLoop++)
        {
            if (0x09 < aucPwdDecrypt[ucLoop])
            {
                SC_ERROR_LOG("SC_PERS_UpdateCKUKPwd: aucPwdDecrypt is incorrect!");

                return SC_ERROR_CODE_OTHER_ERROR;
            }
        }
    }

    /* 生成密码密文 */
    ulCipherLen = SC_CRYPTO_PWD_LEN;

    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_CK,
                                         aucPwdDecrypt,
                                         (VOS_UINT8)ulPwdDecryptLen,
                                         aucCipherData,
                                         ulCipherLen);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKUKPwd: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* 将计算出来的密码写回到CK文件内存中 */
    /*lint -e534*/
    VOS_MemCpy(pucPwd, aucCipherData, ulCipherLen);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : SC_PERS_UpdateCKFile
 功能描述  : 将CK文件中对应CK/UK密码的数据按AT命令的输入进行修改
 输入参数  : pstCkFile:CK文件内容在内存中的地址
             pstWriteSimLockData: 需写入CK-File的信息

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32类型的SC错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月9日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UpdateCKFile(
    SC_CK_FILE_STRU                    *pstCkFile,
    SC_WRITE_SIMLOCK_DATA_STRU         *pstWriteSimLockData
)
{
    VOS_UINT32                          ulResult;

    /* 将AT命令输入的PIN码进行RSA解密后再AES ECB算法加密再写入CK文件的内存中 */
    ulResult = SC_PERS_UpdateCKUKPwd(pstCkFile->astCKCategory[pstWriteSimLockData->enCategory].aucCKCryptoPwd,
                                     pstWriteSimLockData->aucLockRsaPin,
                                     pstWriteSimLockData->enIndicator);

    /* 更新CK不成功，返回失败原因 */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKFile: SC_PERS_UpdateCKUKPwd is failed.", ulResult);

        return ulResult;
    }

    /* 将AT命令输入的PUK码进行RSA解密后再AES ECB算法加密再写入CK文件的内存中 */
    ulResult = SC_PERS_UpdateCKUKPwd(pstCkFile->astCKCategory[pstWriteSimLockData->enCategory].aucUKCryptoPwd,
                                     pstWriteSimLockData->aucLockRsaPuk,
                                     pstWriteSimLockData->enIndicator);

    /* 更新UK不成功，返回失败原因 */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKFile: SC_PERS_UpdateCKUKPwd is failed.", ulResult);

        return ulResult;
    }

    /* 生成新的CK文件和签名文件 */
    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_CK,
                                       (VOS_UINT8*)pstCkFile,
                                       sizeof(SC_CK_FILE_STRU));

    SC_ERROR1_LOG("SC_PERS_UpdateCKFile: SC_COMM_WriteSecretFile result is:", ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_PERS_WriteSimLockData
 功能描述  : NAS收到AT^SIMLOCKDATAWRITE命令，通过该接口写入SIMLOCK信息
 输入参数  : pstWriteSimLockData: 需写入PI-FILE和CK-File的SIMLOCK信息

 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32类型的SC错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月7日
    作    者   : h59254
    修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_WriteSimLockData(SC_WRITE_SIMLOCK_DATA_STRU *pstWriteSimLockData)
{
    VOS_UINT32                          ulResult;
    SC_PI_FILE_STRU                    *pstSimlockInfo;
    SC_CK_FILE_STRU                     stCkFile;
    VOS_UINT32                          ulFlag;

    ulFlag = VOS_FALSE;

    /* 鉴权未完成直接返回身份校验未完成 */
    if (SC_AUTH_STATUS_UNDO == SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_PERS_WriteSimLockData: SC_CTX_GetFacAuthStatus is not done.");
        /* 返回身份校验未完成 */
        return SC_ERROR_CODE_IDENTIFY_NOT_FINISH;
    }

    /* 由于PI文件比较大，为PI文件申请内存 */
    pstSimlockInfo = (SC_PI_FILE_STRU *)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT, sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstSimlockInfo)
    {
        SC_ERROR_LOG("SC_PERS_WriteSimLockData: VOS_MemAlloc is failed.");

        /* 返回内存申请失败 */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取PIFile文件内容并比较签名文件内容 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstSimlockInfo,
                                            sizeof(SC_PI_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /* 设置标记为真 */
        ulFlag = VOS_TRUE;
    }

    /* 读取CKFile文件内容并比较签名文件内容 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_CK,
                                            (VOS_UINT8*)&stCkFile,
                                            sizeof(SC_CK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /* 设置标记为真 */
        ulFlag = VOS_TRUE;
    }

    /* PI或CK文件读取或比较签名不正确，需要将两个文件的内容清零 */
    if (VOS_TRUE == ulFlag)
    {
        /* 如果之前发现PI或CK文件读取失败或签名比较失败，将PI文件中除CATEGORY外的所有字段全部清零 */
        SC_PERS_ErasePIFile(pstSimlockInfo);

        /* CK文件内容全部清零 */
        SC_PERS_EraseCKFile(&stCkFile);
    }

    /* 写入锁网数据前，先进行参数有效性检查(检查enCategory、enIndicator、ucGroupNum、ucMaxUnlockTimes，
       号段内容不做合法性检查) */
    if ((pstWriteSimLockData->enCategory >= SC_MAX_SUPPORT_CATEGORY)
     || (pstWriteSimLockData->enIndicator >= SC_PERSONALIZATION_INDICATOR_BUTT)
     || (pstWriteSimLockData->ucGroupNum > SC_MAX_CODE_NUM)
     || ( (SC_PERSONALIZATION_INDICATOR_ACTIVE == pstWriteSimLockData->enIndicator)
       && (0 == pstWriteSimLockData->ucMaxUnlockTimes)))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstSimlockInfo);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_WriteSimLockData: Parameter check fail!");
        return SC_ERROR_CODE_OTHER_ERROR;
    }

    /* 将改制数据内容写入CK文件的缓存中 */
    ulResult = SC_PERS_UpdateCKFile(&stCkFile, pstWriteSimLockData);

    /* 如果写入失败，返回错误原因值并释放内存 */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstSimlockInfo);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_WriteSimLockData: SC_PERS_UpdateCKFile is failed.", ulResult);

        return ulResult;
    }

    /* 将改制数据内容写入PI文件的中 */
    ulResult = SC_PERS_UpdatePIFile(pstSimlockInfo, pstWriteSimLockData);

    /* 释放内存，返回操作结果 */
    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstSimlockInfo);
    /*lint +e534*/

    SC_INFO1_LOG("SC_PERS_WriteSimLockData: SC_PERS_UpdatePIFile result is:", ulResult);

    return ulResult;
}


/*****************************************************************************
 函 数 名  : SC_PERS_GetSimlockInfo
 功能描述  : NAS通过该接口获取SIMLOCK信息
 输入参数  : pstSimlockInfo:获取SIMLOCK信息的数据结构，由调用者申请内存
 输出参数  : NA
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月09日
    作    者   : d00212987
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_GetSimlockInfo(SC_SIMLOCK_INFO_STRU *pstSimlockInfo)
{
    VOS_UINT32                          ulResult;

    /* 读取PI-FILE并进行签名校验 */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstSimlockInfo,
                                            sizeof(SC_SIMLOCK_INFO_STRU));

    SC_INFO1_LOG("SC_PERS_GetSimlockInfo: SC_COMM_ReadSCFileAndCmpSign result is:", ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : SC_PERS_SimlockUnlock
 功能描述  : 解锁Simlock锁网锁卡
 输入参数  : enCategory         -- 锁网锁卡类型
             *pucPwd            -- 解锁密码
 输出参数  : 无
 返 回 值  : VOS_OK     -- 解锁成功
             VOS_ERR    -- 解锁失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SC_PERS_SimlockUnlock(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucPwd)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRslt;
    SC_PI_FILE_STRU                    *pstPIFile;
    VOS_UINT32                          ulResult;

    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER < enCategory)
    {
        SC_ERROR_LOG("SC_PERS_SimlockUnlock: Category error.");

        return VOS_ERR;
    }


    /* 申请PI文件缓冲内存 */
    pstPIFile = (SC_PI_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT,
                                               sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstPIFile)
    {
        SC_ERROR_LOG("SC_PERS_SimlockUnlock: VOS_MemAlloc is failed.");
        /* 返回内存申请失败 */
        return VOS_ERR;
    }

    /* 读取PI-FILE并进行签名校验,如果结果不为SC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                                               (VOS_UINT8*)pstPIFile,
                                                               sizeof(SC_PI_FILE_STRU)))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SC_COMM_ReadSCFileAndCmpSign is failed.");

        return VOS_ERR;
    }

    /* 对应的enCategory类型未激活SIMLCOK功能 */
    if (SC_PERSONALIZATION_INDICATOR_ACTIVE != pstPIFile->astSimlockCategory[enCategory].enIndicator)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SimLock not active.");

        return VOS_OK;
    }

    /* 对应的enCategory类型SIMLCOK已经验证通过 */
    if (SC_PERSONALIZATION_STATUS_READY == pstPIFile->astSimlockCategory[enCategory].enStatus)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SimLock PIN status is ready.");

        return VOS_OK;
    }

    enVerifySimlockRslt = SC_PERS_GetStatusByCategory(&pstPIFile->astSimlockCategory[enCategory]);

    /* 密码校验 */
    ulResult    = SC_PERS_CheckCryptoCKUKPwd(pucPwd,
                                             SC_PERS_PWD_LEN,
                                             enVerifySimlockRslt,
                                             enCategory);
    /* 根据校验结果更新PI文件的状态 */
    SC_PERS_UpdateSimlockStatus(ulResult,
                                &pstPIFile->astSimlockCategory[enCategory],
                                &enVerifySimlockRslt);

    /* 重新生成PI文件 */
    if (VOS_OK != SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_PI,
                                          (VOS_UINT8*)pstPIFile,
                                          sizeof(SC_PI_FILE_STRU)))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SC_COMM_WriteSecretFile is failed.");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
    /*lint +e534*/

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID SC_DEBUG(VOS_UINT8 *pucData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32                          ulOmDbgIndex;

    (VOS_VOID)SC_INFO1_LOG("\nSC_DEBUG: Data Len: = %d\n", ulDataLen);

    for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++)
    {
        (VOS_VOID)SC_NORMAL_ASCII_LOG(*((VOS_UINT8*)pucData + ulOmDbgIndex));
    }

    (VOS_VOID)SC_NORMAL_LOG("\r\n");

    return ;
}

/*****************************************************************************
 函 数 名  : SC_PERS_SupportPlatform
 功能描述  : 判断当前modem是否支持电信制式
 输入参数  : enModemID:Modem ID

 输出参数  : 锁G/锁C
 返 回 值  : SC_PERS_PLATFORM_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月07日
    作    者   : d00212987
    修改内容   : CDMA锁网锁卡项目新增函数
*****************************************************************************/
SC_PERS_PLATFORM_ENUM_UINT32 SC_PERS_SupportPlatform(
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT32                          ulResult;
    SC_PERS_SUPPORT_PLATFORM_STRU       stSupportPlatform;

    (VOS_VOID)VOS_MemSet(&stSupportPlatform, 0, sizeof(SC_PERS_SUPPORT_PLATFORM_STRU));

    /* 读取Modem当前接入技术nv项 */
    ulResult = NV_ReadEx(enModemID,
                         en_NV_Item_SC_PERS_Support_Platform_Cfg,
                         &stSupportPlatform,
                         sizeof(SC_PERS_SUPPORT_PLATFORM_STRU));

    if ((NV_OK == ulResult) && (SC_PERS_PLATFORM_C == stSupportPlatform.enScPersModem))
    {
        return SC_PERS_PLATFORM_C;
    }

    SC_INFO1_LOG("SC_PERS_SupportPlatform: read nv 4007 is: ", stSupportPlatform.enScPersModem);

    /* NV读失败默认返回支持G锁卡 */
    return SC_PERS_PLATFORM_G;
}

/*****************************************************************************
 函 数 名  : SC_PERS_ChangeNum
 功能描述  : 按照协议计还原算值
 输入参数  : ulSrcValude  -- BCD码长度
             ulCodeMode   -- BCD码存放的位置

 输出参数  : 无
 返 回 值  : VOS_UINT32 -按照协议还原计算值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月28日
    作    者   :
    修改内容   : Create
*****************************************************************************/
VOS_UINT32 SC_PERS_ChangeNum(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode)
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
 函 数 名  : SC_PERS_CDMAImsiBcd2Num
 功能描述  : 从IMSI获取PLMN
 输入参数  : enModemID:Modem ID

 输出参数  :  ucLen     : IMSI长度
             *pucImsi   : IMSI值
             *pucNum    : 转换出来的PLMN

 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月07日
    作    者   : d00212987
    修改内容   : CDMA锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_CDMAImsiBcd2Num(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                    *pucImsi,
    VOS_UINT8                          *pucNum
)
{
    VOS_UINT32                          ulMCC     = 0; /* 国家代号 */
    VOS_UINT32                          ulMNC     = 0; /* 网络代号 */
    VOS_UINT32                          i;

/*
    6F22格式：
    00 AA AA BB BB BB CC 80 DD DD

    计算DD DD
    MCC为460，NUM = 4 * 100 + 6 * 10 + 10 - 111 = 359 转换成2字节小端格式16进制为：67 01

    计算CC
    MNC为03，NUM = 10 * 10 + 3 - 11 = 92，转换成1字节16进制为5C
*/
    ulMCC     = pucImsi[8];
    ulMCC     = 0x0000FFFF & ( ulMCC | (pucImsi[9] << 8));
    ulMCC     = SC_PERS_ChangeNum(ulMCC,3);       /* 国家代号 */

    ulMNC     = pucImsi[6];
    ulMNC     = SC_PERS_ChangeNum(ulMNC,2);       /* 网络代号 */

    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucNum,      "%03d", ulMCC);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucNum + 3,  "%02d", ulMNC);

    /* 由于CW工具下发的非可见字符，此处需要转换 */
    for (i=0; i<SC_CDMA_PLMN_LEN; i++)
    {
        pucNum[i] = pucNum[i] - '0';
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_PERS_CDMACheckCode
 功能描述  : 进行锁网锁卡校验
 输入参数  : enModemID:Modem ID

 输出参数  : pucSimLockResult:锁网锁卡状态
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月07日
    作    者   : d00212987
    修改内容   : CDMA锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_CDMACheckCode(
    SC_SIMLOCK_CATEGORY_STRU           *pstSimLockCat,
    VOS_UINT8                          *pucIMSI,
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           aucExCode[SC_SP_DEPART_LEN];
    VOS_UINT8                           aucPLMNEx[SC_IMSI_DEPART_LEN];
    VOS_UINT8                           ucBeginLen;
    VOS_UINT8                           ucEndLen;
    VOS_UINT8                           aucCodeBegin[SC_CODE_DEPART_LEN];
    VOS_UINT8                           aucCodeEnd[SC_CODE_DEPART_LEN];
    VOS_INT32                           lResultBegin;
    VOS_INT32                           lResultEnd;

    /* 没有激活，返回号段匹配*/
    if (SC_PERSONALIZATION_INDICATOR_INACTIVE == pstSimLockCat->enIndicator)
    {
        SC_INFO1_LOG("SC_PERS_CDMACheckCode: The indicator is not active.",
                     pstSimLockCat->enCategory);

        return VOS_TRUE;
    }

    /* 已经解锁过，返回号段匹配 */
    if (SC_PERSONALIZATION_STATUS_READY == pstSimLockCat->enStatus)
    {
        SC_INFO1_LOG("SC_PERS_CDMACheckCode: The status is not active.",
                     pstSimLockCat->enStatus);

        return VOS_TRUE;
    }

    /* 判断PI文件类别的合法性，是否支持 */
    if (pstSimLockCat->enCategory >= SC_MAX_SUPPORT_CATEGORY)
    {
        SC_ERROR1_LOG("SC_PERS_CDMACheckCode: The Category is out of range.",
                      pstSimLockCat->enCategory);

        return VOS_FALSE;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy(aucPLMNEx, pucIMSI, SC_IMSI_DEPART_LEN);
    SC_DEBUG(aucPLMNEx, SC_IMSI_DEPART_LEN);

    (VOS_VOID)VOS_MemSet(aucExCode, 0, SC_SP_DEPART_LEN);
    /*lint +e534*/

    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == pstSimLockCat->enCategory)
    {
        return VOS_FALSE;
    }

    /* 在配置的号段数组中循环比较 */
    for (i = 0; i < pstSimLockCat->ucGroupNum; i++)
    {
        /* 转换号段Begin, 转换失败则认为不在此号段范围内 */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeBegin,
                                                 &ucBeginLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeBegin,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        SC_DEBUG(aucCodeBegin, ucBeginLen);

        /* 转换号段End, 转换失败则认为不在此号段范围内 */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeEnd,
                                                 &ucEndLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeEnd,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        SC_DEBUG(aucCodeEnd, ucEndLen);

        /* 号段的Begin和End长度不一致, 认为不在此号段范围内 */
        if (ucBeginLen != ucEndLen)
        {
            continue;
        }

        /* 确保比较号段长度不会大于8 */
        if ((ucBeginLen > SC_CODE_DEPART_LEN)||(ucEndLen > SC_CODE_DEPART_LEN))
        {
            return VOS_FALSE;
        }

        lResultBegin    = VOS_MemCmp(aucPLMNEx, aucCodeBegin, ucBeginLen);
        lResultEnd      = VOS_MemCmp(aucPLMNEx, aucCodeEnd, ucEndLen);

        /* 号段在范围内 */
        if ((lResultBegin >= 0) && (lResultEnd <= 0))
        {
            return VOS_TRUE;
        }
    }

    SC_ERROR_LOG("SC_PERS_CheckCode: The result is failed.");

    /* 如果匹配失败 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : SC_PERS_CDMAVrifySimLock
 功能描述  : 进行锁网锁卡校验
 输入参数  : enModemID:Modem ID

 输出参数  : pucSimLockResult:锁网锁卡状态
 返 回 值  : SC_ERROR_CODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月07日
    作    者   : d00212987
    修改内容   : CDMA锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 SC_PERS_CDMAVrifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    SC_PI_FILE_STRU                     *pstPIFile,
    MODEM_ID_ENUM_UINT16                 enModemID
)
{
    VOS_UINT32                          ulEfLen = 0;
    VOS_UINT8                          *pucEf   = VOS_NULL_PTR;
    VOS_UINT8                           aucIMSI[SC_IMSI_DEPART_LEN];
    VOS_UINT8                           ucCardStatus;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulCatIndex;

    /* 调用USIMM_GetCachedFile获取IMSI */
    ulResult = SC_COMM_GetUsimmCachedFile(USIMM_CDMA_EFIMSIM_STR, &ulEfLen, &pucEf, USIMM_CDMA_APP, enModemID);

    /* 返回失败 */
    if (USIMM_API_SUCCESS != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_CDMAVrifySimLock: USIMM_GetCachedFile is failed.", ulResult);

        /* 读取当前用户，CDMA运用不可用则锁网锁卡 */
        (VOS_VOID)USIMM_GetCardTypeByAppType(&ucCardStatus, VOS_NULL_PTR, USIMM_CDMA_APP);

        if (USIMM_CARD_SERVIC_AVAILABLE != ucCardStatus)
        {
            SC_ERROR_LOG("SC_PERS_CDMAVrifySimLock: CDMA App is not AVAILABLE.");

            return SC_ERROR_CODE_OTHER_ERROR;
        }

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 由BCD转换为数字 */
    ulResult = SC_PERS_CDMAImsiBcd2Num((VOS_UINT8)ulEfLen, pucEf, aucIMSI);

    if (VOS_OK != ulResult)
    {
        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN;

        SC_ERROR1_LOG("SC_PERS_CDMAVrifySimLock: SC_PERS_ImsiBcd2Num is failed.",
                      ulResult);

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* 循环category进行号段校验 */
    for (ulCatIndex = 0; ulCatIndex < SC_MAX_SUPPORT_CATEGORY; ulCatIndex++)
    {

        ulResult = SC_PERS_CDMACheckCode(&pstPIFile->astSimlockCategory[ulCatIndex],
                                         aucIMSI,
                                         enModemID);

        if (VOS_FALSE == ulResult)
        {
            *penVerifySimlockRslt = SC_PERS_GetStatusByCategory(&pstPIFile->astSimlockCategory[ulCatIndex]);
            break;
        }

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

