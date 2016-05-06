/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcNvim.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBA模块NV操作相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcNvim.h"
#include  "NVIM_Interface.h"
#include  "TafCbaComFunc.h"
#include  "MnComm.h"
#include  "TafLog.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_NVIM_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_CBA_ReadNvUserAcceptMsgIdList
 功能描述  : 从NVIM中读取用户配置的CBS激活列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月12日
    作    者   : f62575
    修改内容   : 新生成函数, DTS2013081900835

*****************************************************************************/
VOS_VOID TAF_CBA_ReadNvUserAcceptMsgIdList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiRangeList
)
{
    VOS_UINT32                          ulInx;
    VOS_UINT32                          ulCbmiRangNum;
    TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU  *pstCbmiNvRangeList = VOS_NULL_PTR;

    /* 申请内存用于读取NV 中的CBS配置 */
    pstCbmiNvRangeList = (TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, 
                                    sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    if (VOS_NULL_PTR == pstCbmiNvRangeList)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ReadNvUserAcceptMsgIdList: ALLOC MEM FAILED!");
        return;
    }

    /*  读取NV en_NV_Item_CBS_MID_Range_List_New */
    if (NV_OK != NV_Read(en_NV_Item_CBS_MID_Range_List_New,
                         pstCbmiNvRangeList,
                         sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU)))
    {
        pstCbmiNvRangeList->ulCbmirNum = 0;

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_GetNvimAcceptModeCbmiRangeList: To read CBS MidRangeList in NVIM failed!");

        PS_MEM_FREE(WUEPS_PID_TAF, pstCbmiNvRangeList);

        return;
    }

    /* 此处进行一个保护,防止超限 */
    if ( pstCbmiNvRangeList->ulCbmirNum > TAF_CBA_MAX_CBMID_RANGE_NUM )
    {
        pstCbmiNvRangeList->ulCbmirNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    /* 
       转换NV中的CBS配置为内存中的结构，并过滤掉 REJECT 模式的  CBMI RANGE，
       目前只支持ACCEPT 模式的 CBMI RANGE, 
    */
    ulCbmiRangNum = 0;

    for ( ulInx = 0; ulInx < pstCbmiNvRangeList->ulCbmirNum; ulInx++ )
    {
        if ( TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].ulRcvMode )
        {
            pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].enRcvMode   = pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].ulRcvMode;
            pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].usMsgIdFrom = pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].usMsgIdFrom;
            pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].usMsgIdTo   = pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].usMsgIdTo;
            PS_MEM_CPY(pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].ucLabel,
                     pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].ucLabel,TAF_CBA_NVIM_MAX_LABEL_NUM);
            ulCbmiRangNum++;
        }
    }
    
    pstCbmiRangeList->usCbmirNum = (VOS_UINT16)ulCbmiRangNum;

    /* NV中CBS配置数据已经转换为内存中配置结构，是否为读取NV申请的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmiNvRangeList);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_AppendNvUserAcceptMsgIdList
 功能描述  : 追加NVIM中用户接受的CBS消息ID列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月23日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2013年8月12日
    作    者   : f62575
    修改内容   : DTS2013081900835，支持先更新USIM配置，后更新NV配置
                 TAF_CBA_ReadCbmiRangeListNvim函数名变更TAF_CBA_AppendNvUserAcceptMsgIdList
*****************************************************************************/
VOS_VOID TAF_CBA_AppendNvUserAcceptMsgIdList(VOS_VOID)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiNvRangeList = VOS_NULL_PTR;

    pstCbmiNvRangeList = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    if (VOS_NULL_PTR == pstCbmiNvRangeList)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_AppendNvUserAcceptMsgIdList: ALLOC MEM FAILED!");
        return;
    }

    PS_MEM_SET(pstCbmiNvRangeList, 0x00, sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    TAF_CBA_ReadNvUserAcceptMsgIdList(pstCbmiNvRangeList);

    /* 先排序 */
    TAF_CBA_SortCbmiRangeList(pstCbmiNvRangeList);

    /* 更新内存列表 */
    (VOS_VOID)TAF_CBA_AddCbMiRangeListToActiveList(pstCbmiNvRangeList);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmiNvRangeList);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CBA_ReadCbsServiceParamNvim
 功能描述  : 从NVIM中读取CBS功能使能标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月23日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2012年12月04日
    作    者   : L00171473
    修改内容   : for DTS2012120600056, NV中添加重复过滤开关
  4.日    期   : 2012年12月10日
    作    者   : l00171473
    修改内容   : for DTS2012120609682,终端要求CBS统一上报88个字节
  5.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述	
*****************************************************************************/
VOS_VOID TAF_CBA_ReadCbsServiceParamNvim(VOS_VOID)
{
    TAF_CBA_CBS_SERVICE_PARM_STRU       stSrvPara;


    stSrvPara.ucCbStatus = TAF_CBA_CBSTATUS_DISABLE;



    /* 默认使能重复过滤 */
    stSrvPara.ucDupDetectCfg = TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE;


    /* 默认不上报整页，只向APP上报有效字节 */
    stSrvPara.ucRptAppFullPageFlg = VOS_FALSE;

    /* 读取NV en_NV_Item_CBS_Service_Para */
    if (NV_OK != NV_Read(en_NV_Item_CBS_Service_Para,
                         &stSrvPara,
                         sizeof(TAF_CBA_CBS_SERVICE_PARM_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ReadCbsServiceParamNvim: To read CBS service parameter in NVIM failed!");
        stSrvPara.ucCbStatus = TAF_CBA_CBSTATUS_DISABLE;
    }

    TAF_CBA_SetCbsStatus(stSrvPara.ucCbStatus);

    if ( stSrvPara.ucDupDetectCfg < TAF_CBA_DUP_DETECT_CFG_BUTT )
    {
        TAF_CBA_SetDupDetectCfg(stSrvPara.ucDupDetectCfg);
    }
    else
    {
        TAF_CBA_SetDupDetectCfg(TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE);
    }



    TAF_CBA_SetRptAppFullPageFlg(stSrvPara.ucRptAppFullPageFlg);

}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_CBA_ReadEtwsServieCfgNvim
 功能描述  : 从NVIM中读取ETWS相关的配置NV项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月23日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID TAF_CBA_ReadEtwsServieCfgNvim(VOS_VOID)
{
    TAF_CBA_NVIM_ETWS_CFG_STRU          stNewNvinEtwsInfo;
    TAF_CBA_MS_CFG_ETWS_INFO_STRU       stMsEtwsInfo;
    VOS_UINT32                          ulIndex;

    /* 初始化局部变量 */
    PS_MEM_SET(&stNewNvinEtwsInfo, 0x00, sizeof(TAF_CBA_NVIM_ETWS_CFG_STRU));


    PS_MEM_SET(&stMsEtwsInfo,      0x00, sizeof(stMsEtwsInfo));

    /* 读取NV en_NV_Item_ETWS_Service_Cfg_Para */
    if (NV_OK != NV_Read(en_NV_Item_ETWS_Service_Cfg_Para,
                         &(stNewNvinEtwsInfo),
                         sizeof(TAF_CBA_NVIM_ETWS_CFG_STRU)))
    {
        stNewNvinEtwsInfo.ucEtwsEnableFlg = VOS_FALSE;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ReadEtwsServieCfgNvim: To read EtwsInfo in NVIM failed!");
    }

    /* 将NV中的EtwsCfg解析成MsCfgEtwsInfo */
    stMsEtwsInfo.ucEtwsEnableFlg                                     =
            stNewNvinEtwsInfo.ucEtwsEnableFlg;

    stMsEtwsInfo.stDupDetectCfg.ucEnhDupDetectFlg                    =
            stNewNvinEtwsInfo.stDupDetcCfg.ucEnhDupDetcFlg;

    stMsEtwsInfo.stDupDetectCfg.ulNormalTimeLen                      =
            (VOS_UINT32)(stNewNvinEtwsInfo.stDupDetcCfg.usNormalTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    stMsEtwsInfo.stDupDetectCfg.stDupDetectTimeLen.ulSpecMccTimeLen  =
            (VOS_UINT32)(stNewNvinEtwsInfo.stDupDetcCfg.usSpecMccTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    stMsEtwsInfo.stDupDetectCfg.stDupDetectTimeLen.ulOtherMccTimeLen =
            (VOS_UINT32)(stNewNvinEtwsInfo.stDupDetcCfg.usOtherMccTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    stMsEtwsInfo.ulTempEnableCbsTimeLen                              =
            (VOS_UINT32)(stNewNvinEtwsInfo.usTempEnableCbsTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    for ( ulIndex = 0; ulIndex < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; ulIndex++ )
    {
        stMsEtwsInfo.stDupDetectCfg.stDupDetectTimeLen.aulSpecMcc[ulIndex] =
                stNewNvinEtwsInfo.stDupDetcCfg.aulSpecMcc[ulIndex];
    }

    for ( ulIndex = 0; ulIndex < TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM; ulIndex++ )
    {
        stMsEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdFrom =
               stNewNvinEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdFrom;

        stMsEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdTo   =
                stNewNvinEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdTo;
    }

    /* 对range list排序, 保证 usMsgIdFrom 小于等于 usMsgIdTo */
    TAF_CBA_SortEtwsRangList( &(stMsEtwsInfo.astSpecEtwsMsgIdList[0]),
                              TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM );

    /* 将NV中读取的值保存到全局变量中 */
    TAF_CBA_SetMsCfgEtwsInfo(&stMsEtwsInfo);

}
#endif

/*****************************************************************************
 函 数 名  : TAF_CBA_WriteCbmiRangeListNvim
 功能描述  : 将用户设置的CBS激活列表保存到NVIM
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月23日
    作    者   : t00212959
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年3月28日
    作    者   : w00176964
    修改内容   : NV结构体调整
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID TAF_CBA_WriteCbmiRangeListNvim(VOS_VOID)
{
    TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU  *pstNvimCbmiRangeList;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstMemCbmiRangeList;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCbmiInx;

    pstMemCbmiRangeList  = TAF_CBA_GetCbMiRangeList();

    pstNvimCbmiRangeList = (TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstNvimCbmiRangeList)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_WriteCbmiRangeListNvim: ALLOC MEM FAILED!");
        return;
    }

    /* 内存初始化 */
    PS_MEM_SET(pstNvimCbmiRangeList, 0x00, sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    pstNvimCbmiRangeList->ulCbmirNum = pstMemCbmiRangeList->usCbmirNum;

    for ( ulCbmiInx = 0; ulCbmiInx < TAF_CBA_MAX_CBMID_RANGE_NUM; ulCbmiInx++ )
    {
        pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].ulRcvMode   = pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].enRcvMode;
        pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdFrom = pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdFrom;
        pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdTo   = pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdTo;
        PS_MEM_CPY(pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].ucLabel,
                   pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].ucLabel,TAF_CBA_NVIM_MAX_LABEL_NUM);
    }

    /* 写NV en_NV_Item_CBS_MID_Range_List_New */
    ulRet = NV_Write(en_NV_Item_CBS_MID_Range_List_New,
                     pstNvimCbmiRangeList,
                     sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    if (NV_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_WriteCbmiRangeListNvim:Fail to write CBS cbmir in NVIM!");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstNvimCbmiRangeList);
}

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
