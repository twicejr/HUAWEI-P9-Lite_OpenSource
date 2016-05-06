/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsProcUsim.c
  版 本 号   : 初稿
  作    者   : y00322978
  生成日期   : 2015年11月30日
  最近修改   :
  功能描述   : TAF APS处理usim读写文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月30日
    作    者   : y00322978
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsProcUsim.h"
#include  "NasUsimmApi.h"
#include  "TafSdcCtx.h"
#include  "TafApsComFunc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PROC_USIM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_APS_GetWaitSimFilesCnfFlg
 功能描述  : 开机过程中获取读取SIM卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取SIM卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015-03-13
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_APS_GetWaitSimFilesCnfFlg(VOS_VOID)
{
    return TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ClearWaitSimFilesCnfFlg
 功能描述  : 开机过程中清除读取SIM卡文件回复标记
 输入参数  : enSimFileCnfFlg - SIM卡文件回复标记
             ulAppType       - APP类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015-03-13
    作    者   : Y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
)
{
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enRead3GpdFileFlag;

    enRead3GpdFileFlag = TAF_APS_Map3GpdFileIdAndFlag(usEfId);

    TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg &= ~enRead3GpdFileFlag;
    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetWaitSimFilesCnfFlg
 功能描述  : 开机过程中设置SIM卡文件回复标记
 输入参数  : enSimFileCnfFlg - SIM卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015-03-13
    作    者   : Y00322978
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    TAF_APS_SetWaitSimFilesCnfFlg(
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
)
{
    TAF_APS_GetApsCtxAddr()->ulReadSim3GpdFileFlg |= enSimFileCnfFlg;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SendUsimFileReq
 功能描述  : 发送请求消息去读取USIM卡文件
 输入参数  : USIMM_APP_TYPE_ENUM_UINT32          enAppType
             VOS_UINT16                          usEfId
 输出参数  : 无
 返 回 值  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年3月3日
   作    者   : Y00322978
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                    enAppType,
                    usEfId,
                    0);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    return ulRet;

}

/*****************************************************************************
 函 数 名  : TAF_APS_Read3GdpFile
 功能描述  : 开机读3Gpd相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : y00322978
    修改内容   : DTS2015111309776
*****************************************************************************/
VOS_VOID TAF_APS_Read3GdpFile( VOS_VOID )
{
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;

    enCsimType                          = TAF_SDC_GetCsimType();

    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        return;
    }

    if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPCAP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPCAP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPUPP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPUPP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPSP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPSP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFSIPPAPSS_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CDMA_EFSIPPAPSS_ID_FLG);
    }

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPCAP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPCAP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPUPP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPUPP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPSP_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPSP_ID_FLG);

        (VOS_VOID)TAF_APS_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFSIPPAPSS_ID);
        TAF_APS_SetWaitSimFilesCnfFlg(TAF_APS_READ_USIMM_CSIM_EFSIPPAPSS_ID_FLG);

    }

    return;
}

#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
