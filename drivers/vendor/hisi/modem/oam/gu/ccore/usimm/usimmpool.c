/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmBase.c
  Author       : zhuli 00100318
  Version      : v00R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---POOL模块实现
  Function List:
  History      :
 ************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "NVIM_Interface.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "usimminit.h"
#include "siappstk.h"
#include "errorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_POOL_C
/*lint +e767*/

#define NV_FILE_OPEN_MODE_RW            "rb+"   /* open binary file for reading and writing */
#define NV_FILE_OPEN_MODE_NEW_RW        "wb+"   /* creat binary file for reading and writing*/

#define NV_FILE_SEEK_SET                0       /* the beginning of the file*/

/*****************************************************************************
函 数 名  :USIMM_PoolFindFile
功能描述  :在文件池内找出文件所在的位置　
输入参数  :usFileId:文件ID
           enAppType: APP类型
输出参数  :pulPoolIndex:文件在文件池的位置
返 回 值  :VOS_ERR/VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日s
   作    者   : z00100318
   修改内容   : Creat
2. 日    期   : 2015年3月28日
   作    者   : c00299064
   修改内容   : APP类型使用结构体 USIMM_CARDAPP_ENUM_UINT32
*****************************************************************************/
VOS_UINT32 USIMM_PoolFindFile(
    VOS_UINT16                          usEFileId,
    VOS_UINT32                         *pulPoolIndex,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32 i;
    USIMM_POOL_ST                      *pstPoolGlobal;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();

    if(VOS_NULL == pstPoolGlobal->ucPoolFileCount)  /*当前内容为空*/
    {
        if(0 == usEFileId)       /*查询空位置*/
        {
            *pulPoolIndex = 0;

            return VOS_OK;
        }

        return VOS_ERR;
    }
    /* 如果被查找APP类型不是AUTO需要校验PIN码或PUK码时，只允许从文件池中读取不受PIN码保护的文件*/
    if ((USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(enAppType))
     && (USIMM_UNLIMIT_AUTO != enAppType)
     && (0 != usEFileId))
    {
        if (EFICCID != usEFileId)
        {
            return VOS_ERR;
        }
    }

    /*返回文件所在单元号*/
    for(i = 0; i < USIMM_POOL_MAX_NUM; i++)
    {
            /* 文件需要匹配文件ID和APP类型才算找到该文件，包括ATT、UMTS和GSM
            或者被保存的APP类型为USIMM_UNLIMIT_AUTO，则不匹配APP类型只匹配文件ID*/

        if (USIMM_CCB_GetPoolFileByIndex(i)->usEFId == usEFileId)
        {
            if ((gstUSIMMPOOL.astpoolRecord[i].enAppType == enAppType)
            ||  (gstUSIMMPOOL.astpoolRecord[i].enAppType == USIMM_UNLIMIT_AUTO)
            ||  (usEFileId == 0))
            {
                /*返回文件所在单元号*/
                *pulPoolIndex = i;

                return VOS_OK;
            }
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_PoolInsertOneFile
功能描述  :在文件池内填入一个文件的内容　
输入参数  :usFileId:文件ID
           usLen:文件数据长度
           pData:文件数据内容
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
调用函数  :USIMM_PoolFindFile
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
1. 日    期   : 2015年03月30日
   作    者   : C00299064
   修改内容   : 入参合并

*****************************************************************************/
VOS_UINT32 USIMM_PoolInsertOneFile
(
    USIMM_POOL_ONERECORD_ST *pstRecord
)
{
    VOS_UINT32                          ulRecordNum;
    VOS_UINT32                          ulResult        = VOS_OK;
    USIMM_POOL_ST                      *pstPoolGlobal;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();

    if((USIMM_POOL_NOINTIAL == pstPoolGlobal->enPoolStatus)
     ||(USIMM_POOL_MAX_NUM  == pstPoolGlobal->ucPoolFileCount)
     ||(0 == pstRecord->usEFId))   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_PoolInsertOneFile: Warning: Parameter is wrong");/*打印错误*/

        return VOS_ERR;
    }

    /*  如果此文件记录已经存在，删除原有记录 */
    if (VOS_OK == USIMM_PoolFindFile(pstRecord->usEFId, &ulRecordNum, pstRecord->enAppType))
    {
        USIMM_PoolDelOneRecByIndex(ulRecordNum);
    }
    else
    {
        ulResult = USIMM_PoolFindFile(0, &ulRecordNum, pstRecord->enAppType);/*查询空位置*/
    }

    if(VOS_ERR == ulResult)/*当前文件池以满*/
    {
        USIMM_WARNING_LOG("USIMM_PoolInsertOneFile: Warning: File Could not Found");/*打印错误*/

        return VOS_ERR;
    }

    /* 增加记录 */
    USIMM_PoolInsertOneRecByIndex(ulRecordNum, pstRecord);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolUpdateOneFile
功能描述  :在文件池内更新一个文件的内容　
输入参数  :usFileId:文件ID
           ulNewLen:文件数据长度
           pucNewData:文件数据内容
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolUpdateOneFile(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usFileID,
    VOS_UINT32                          ulNewLen,
    VOS_UINT8                           *pucNewData)
{
    VOS_UINT32                          ulRecordNum;
    VOS_UINT32                          ulResult;
    USIMM_POOL_ONERECORD_ST             *pstPoolFile;

    if (USIMM_POOL_NOINTIAL == gstUSIMMPOOL.enPoolStatus)   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_PoolUpdateOneFile: Parameter is wrong");/*打印错误*/

        return VOS_ERR;
    }

    ulResult = USIMM_PoolFindFile(usFileID, &ulRecordNum, enAppType);/*查询空位置*/

    if(VOS_ERR == ulResult)/*当前文件池以满*/
    {
        USIMM_WARNING_LOG("USIMM_PoolUpdateOneFile: File Could not Found");/*打印错误*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent);
    /*lint +e534*/

    pstPoolFile = USIMM_CCB_GetPoolFileByIndex(ulRecordNum);

    pstPoolFile->pucContent = VOS_MemAlloc(WUEPS_PID_USIM, STATIC_MEM_PT, ulNewLen);

    if (VOS_NULL_PTR == pstPoolFile->pucContent)
    {
        USIMM_WARNING_LOG("USIMM_PoolUpdateOneFile: VOS_MemAlloc Error");/*打印错误*/

        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemCpy(pstPoolFile->pucContent, pucNewData, ulNewLen);

    USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->usLen = (VOS_UINT16)ulNewLen;      /* 记录文件长度 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolDelOneFile
功能描述  :从文件池内删除一个文件的内容　
输入参数  :usFileId:文件ID
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
调用函数  :USIMM_PoolFindFile
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolDelOneFile(VOS_UINT16 usFileId, USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT32                          ulRecordNum;
    USIMM_POOL_ST                      *pstPoolGlobal;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();

    if((USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus == USIMM_POOL_NOINTIAL)
    || (pstPoolGlobal->ucPoolFileCount == VOS_NULL)
    || (0 == usFileId))   /*状态检查*/
    {
        USIMM_ERROR_LOG("USIMM_PoolDelOneFile: Wrong State or Parameter");/*打印错误*/

        return VOS_ERR;
    }

    if(VOS_ERR == USIMM_PoolFindFile(usFileId, &ulRecordNum, enAppType))/*查询文件位置*/
    {
        USIMM_WARNING_LOG("USIMM_PoolDelOneFile: File Could Not Found");/*打印错误*/

        return VOS_ERR;
    }

    if(VOS_NULL_PTR == USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent)
    {
        USIMM_ERROR_LOG("USIMM_PoolDelOneFile: File Content is Empty");/*打印错误*/

        return VOS_ERR;
    }

    USIMM_PoolDelOneRecByIndex(ulRecordNum);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolDelFilesByAppType
功能描述  :从文件池内删除所用应用类型为enapptype的文件
输入参数  :enAppType:应用类型
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
调用函数  :
修订记录  :
1. 日    期   : 2015年03月30日
   作    者   : c00299064
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolDelFilesByAppType(USIMM_CARDAPP_ENUM_UINT32 enAppType)
{
    VOS_UINT32                         i;
    USIMM_POOL_ST                      *pstPoolGlobal;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();
    /* 状态检查 */
    if ((pstPoolGlobal->enPoolStatus == USIMM_POOL_NOINTIAL)
    ||  (pstPoolGlobal->ucPoolFileCount == 0)
    ||  (USIMM_UNLIMIT_APP_BUTT <= enAppType))
    {
        /* 打印错误 */
        USIMM_ERROR_LOG("USIMM_PoolDelFilesByAppType: Wrong State or Parameter");

        return VOS_ERR;
    }

    /* 不关心enAppType是不是通配 */
    for(i = 0; i < USIMM_POOL_MAX_NUM; i++)
    {
        if (USIMM_CCB_GetPoolFileByIndex(i)->enAppType == enAppType)
        {
            USIMM_PoolDelOneRecByIndex(i);
        }
    }

    return VOS_OK;

}
/*****************************************************************************
函 数 名  :USIMM_PoolReadOneFile
功能描述  :从文件池内读取一个文件的内容和长度　
输入参数  :usFileId:文件ID
输出参数  :pLen:文件数据长度
           pData:文件数据内容
返 回 值  :VOS_ERR/VOS_OK
调用函数  :USIMM_PoolFindFile
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolReadOneFile(
    VOS_UINT16                          usFileId,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulRecordNum;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulDataLen;
    USIMM_POOL_ST                      *pstPoolGlobal;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();

    if((USIMM_POOL_NOINTIAL == pstPoolGlobal->enPoolStatus)
     ||(0 == pstPoolGlobal->ucPoolFileCount)
     ||(0 == usFileId))   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_PoolReadOneFile: Parameter wrong");/*打印错误*/

        return VOS_ERR;
    }

    ulResult = USIMM_PoolFindFile(usFileId, &ulRecordNum, enAppType);/*查询文件位置*/

    if(VOS_ERR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_PoolReadOneFile: File Could not Found");/*打印错误*/

        return VOS_ERR;
    }

    if(VOS_NULL_PTR == USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent)
    {
        USIMM_ERROR_LOG("USIMM_PoolReadOneFile: File Content is Empty");/*打印错误*/

        return VOS_ERR;
    }

    if(usLen == USIMM_READ_ALL_FILE_CONTENT)
    {
        ulDataLen = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->usLen;
    }
    else if(usLen < USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->usLen)
    {
        ulDataLen = usLen;
    }
    else
    {
        ulDataLen = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->usLen;
    }

    /*lint -e534*/
    VOS_MemCpy(pucData, USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent, ulDataLen);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolDelAll
功能描述  :从文件池内读取一个文件的内容和长度　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2009年8月9日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_PoolDelAll(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i=0; i<USIMM_POOL_MAX_NUM; i++)
    {
        if (VOS_NULL_PTR != USIMM_CCB_GetPoolFileByIndex(i)->pucContent)/*找到该文件*/
        {
            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_USIM, USIMM_CCB_GetPoolFileByIndex(i)->pucContent);
            /*lint +e534*/
        }
    }

    USIMM_InitPoolGlobal();

    return;
}
/*****************************************************************************
函 数 名  :USIMM_PoolDelOneRecByIndex
功能描述  :从文件池内删除一个记录
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2015年04月15日
   作    者   : c00299064
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_PoolDelOneRecByIndex(VOS_UINT32 ulIndex)
{
    USIMM_POOL_ST                      *pstPool;

    pstPool     =  USIMM_CCB_GetFilePoolTotalGlobal();

    /* 释放存储空间并将指针清空 */
    if (VOS_NULL_PTR != pstPool->astpoolRecord[ulIndex].pucContent)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstPool->astpoolRecord[ulIndex].pucContent);
        /*lint +e534*/
        pstPool->astpoolRecord[ulIndex].pucContent  = VOS_NULL_PTR;
    }

    /*文件ID标记为空*/
    pstPool->astpoolRecord[ulIndex].usEFId      = 0;

    /*长度清空*/
    pstPool->astpoolRecord[ulIndex].usLen       = 0;

    /* APPTYPE初始化 */
    pstPool->astpoolRecord[ulIndex].enAppType   = USIMM_UNLIMIT_APP_BUTT;

    /*记数器减一*/
    pstPool->ucPoolFileCount--;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_PoolInsertOneRecByIndex
功能描述  :从文件池内增加一个记录
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2015年04月15日
   作    者   : c00299064
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_PoolInsertOneRecByIndex(
    VOS_UINT32                           ulIndex,
    USIMM_POOL_ONERECORD_ST             *pstRecord
)
{
    USIMM_POOL_ST                       *pstPool;

    pstPool     =  USIMM_CCB_GetFilePoolTotalGlobal();

    pstPool->astpoolRecord[ulIndex].pucContent = (VOS_UINT8*)VOS_MemAlloc(WUEPS_PID_USIM,
                                                                          STATIC_MEM_PT,
                                                                          pstRecord->usLen);

    if(VOS_NULL_PTR == pstPool->astpoolRecord[ulIndex].pucContent)
    {
        USIMM_WARNING_LOG("USIMM_PoolInsertOneFile: Warning: VOS_MemAlloc is Error");

        return ;
    }

    /*lint -e534*/
    VOS_MemCpy(pstPool->astpoolRecord[ulIndex].pucContent,  pstRecord->pucContent,  pstRecord->usLen);/*保存数据内容*/
    /*lint +e534*/

    pstPool->astpoolRecord[ulIndex].usEFId      =   pstRecord->usEFId;
    pstPool->astpoolRecord[ulIndex].usLen       =   pstRecord->usLen;
    pstPool->astpoolRecord[ulIndex].enAppType   =   pstRecord->enAppType;
    pstPool->astpoolRecord[ulIndex].enFileType  =   pstRecord->enFileType;

    pstPool->ucPoolFileCount++;

    return;
}


/*****************************************************************************
函 数 名  :USIMM_InsertFileToPool
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
 修订记录 :
1. 日    期   : 2007年8月20日
    作    者   : m00128685
    修改内容   : Creat
2. 日    期   : 2015年3月20日
    作    者   : C00299064
    修改内容   : 入参改变
                usFileID改为enDefFileID，其类型为 USIMM_DEF_FILEID_ENUM_UINT32，
                APP 使用新的定义类型USIMM_CARDAPP_ENUM_UINT32
*****************************************************************************/
VOS_UINT32 USIMM_InsertFileToPool
(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
)
{
    VOS_UINT32                          ulRet;
    USIMM_POOL_ONERECORD_ST             stRecord;

    /*lint -e534*/
    VOS_MemSet(&stRecord, 0 , sizeof(USIMM_POOL_ONERECORD_ST));
    /*lint +e534*/

    /* 选择文件 */
    ulRet = USIMM_GetDefTFMem(enAppType, enFileID, &stRecord.usLen, &stRecord.pucContent);

    if (VOS_OK != ulRet)
    {
        USIMM_ERROR_LOG("USIMM_InsertFileToPool: USIMM_GetDefTFMem Error");

        return VOS_ERR;
    }

    stRecord.usEFId     = USIMM_CCB_GetCurFileInfo(enAppType)->usCurEFID;
    stRecord.enAppType  = enAppType;
    stRecord.enFileType = USIMM_EFSTRUCTURE_TRANSPARENT;

    if (VOS_OK != USIMM_PoolInsertOneFile(&stRecord))
    {
        USIMM_ERROR_LOG("USIMM_InsertFileToPool: USIMM_PoolInsertOneFile Error");

        g_stUSIMMInitInfo.ucInsertPoolFailFlag = VOS_TRUE;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, stRecord.pucContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, stRecord.pucContent);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_LogDataSave
功能描述  :保存数据到log缓冲区，TLV结构保存
输入参数  :pucData 需要保存的数据
           ucDataLen 保存数据长度
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_LogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen)
{
    if((USIMM_NO_NEED_LOG == g_stUSIMMLogData.enLogState)   /*当前不需要记录log*/
        ||((g_stUSIMMLogData.ulDataLen + 2 + ucDataLen) > USIMM_LOG_DATA_MAX_LEN)/*记录的log数据超过最大值,还需要计算tag和len的2个字节*/
        ||(VOS_NULL_PTR == g_stUSIMMLogData.pucData))       /*当前log缓冲区不存在*/
    {
        return;
    }

    g_stUSIMMLogData.pucData[g_stUSIMMLogData.ulDataLen] = USIMM_LOG_DATA_TAG;  /*记录log*/

    g_stUSIMMLogData.ulDataLen ++;              /*长度+1*/

    g_stUSIMMLogData.pucData[g_stUSIMMLogData.ulDataLen] = ucDataLen;   /*记录数据长度*/

    g_stUSIMMLogData.ulDataLen ++;              /*长度+1*/

    /*lint -e534*/
    VOS_MemCpy(&(g_stUSIMMLogData.pucData[g_stUSIMMLogData.ulDataLen]), pucData, ucDataLen);
    /*lint +e534*/

    g_stUSIMMLogData.ulDataLen += ucDataLen;    /*长度+数据长度*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_LogDataClear
功能描述  :清空log缓冲区的内容　并且关闭记录功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_LogDataClear(VOS_VOID)
{
    (VOS_VOID)VOS_CacheMemFree(g_stUSIMMLogData.pucData);

    g_stUSIMMLogData.ulDataLen = 0;

    g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SaveLogFile
功能描述  :写入log文件的内容　，写入无论成功与否都关闭记录log功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SaveLogFile(VOS_VOID)
{
    FILE                               *ctrlfp;
    FILE                               *logfp;
    USIMM_LOG_CTRLFILE_STRU             stCtrlData;
    VOS_CHAR                            aucLogPath[100] = {0};
    VOS_CHAR                            aucLogCtrlFile[USIMM_FILE_PATH_MAX_LEN] = {0};
    VOS_CHAR                            aucUniteryLogPath[USIMM_FILE_PATH_MAX_LEN] = {0};

    /*当前是否有保存数据*/
    if((VOS_NULL_PTR == g_stUSIMMLogData.pucData)||(0 == g_stUSIMMLogData.ulDataLen))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucLogCtrlFile, USIMM_LOGCTRL_FILE, USIMM_UNITARY_LOGCTRL_FILE))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucUniteryLogPath, USIMM_LOG_PATH, USIMM_UNITARY_LOG_PATH))
    {
        return;
    }

    /*打开控制文件*/
    ctrlfp = mdrv_file_open(aucLogCtrlFile, NV_FILE_OPEN_MODE_RW);

    if(VOS_NULL_PTR == ctrlfp)
    {
        USIMM_LogDataClear();
        return;
    }

    /*读取控制文件*/
    if(sizeof(USIMM_LOG_CTRLFILE_STRU) != mdrv_file_read((VOS_CHAR*)&stCtrlData,
                                                    sizeof(VOS_CHAR),
                                                    sizeof(USIMM_LOG_CTRLFILE_STRU),
                                                    ctrlfp))
    {
        USIMM_LogDataClear();
        (VOS_VOID)mdrv_file_close(ctrlfp);
        return;
    }

    if(stCtrlData.ulCurFile >= USIMM_LOG_FILE_MAX_NUM)
    {
        USIMM_LogDataClear();
        (VOS_VOID)mdrv_file_close(ctrlfp);
        (VOS_VOID)mdrv_file_remove(aucLogCtrlFile);
        return;
    }

    /* 拼接LOG文件路径 */
    /*lint -e534*/
    VOS_sprintf(aucLogPath, "%s/%s", aucUniteryLogPath, stCtrlData.aucFileName[stCtrlData.ulCurFile]);
    /*lint +e534*/

    /*打开log文件，如果存在需要清空*/
    logfp = mdrv_file_open(aucLogPath, NV_FILE_OPEN_MODE_NEW_RW);

    if(VOS_NULL_PTR == logfp)
    {
        USIMM_LogDataClear();
        return;
    }

    /*写入数据*/
    (VOS_VOID)mdrv_file_write((VOS_CHAR*)g_stUSIMMLogData.pucData, sizeof(VOS_CHAR), g_stUSIMMLogData.ulDataLen, logfp);

    (VOS_VOID)mdrv_file_close(logfp);

    /*清空数据*/
    USIMM_LogDataClear();

    /*计算下次写入的文件号*/
    stCtrlData.ulCurFile = ((stCtrlData.ulCurFile + 1) % USIMM_LOG_FILE_MAX_NUM);

    /*写入下次更新的文件号*/
    (VOS_VOID)mdrv_file_seek(ctrlfp, 0, NV_FILE_SEEK_SET);

    (VOS_VOID)mdrv_file_write((VOS_CHAR*)&stCtrlData.ulCurFile, sizeof(VOS_CHAR), sizeof(VOS_UINT32), ctrlfp);

    (VOS_VOID)mdrv_file_close(ctrlfp);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitLogFile
功能描述  :初始化log文件的内容　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitLogFile(VOS_VOID)
{
    VOS_CHAR                            aucLogFile[USIMM_LOG_FILE_NAME_LEN] = {0};
    VOS_UINT32                          i;
    VOS_UINT32                          ulStartFlag = USIMM_LOG_START_TAG;
    USIMM_LOG_CTRLFILE_STRU             stCtrlData;
    FILE                               *fp;
    VOS_CHAR                            aucLogCtrlFile[USIMM_FILE_PATH_MAX_LEN] = {0};
    VOS_CHAR                            aucLogPath[USIMM_FILE_PATH_MAX_LEN] = {0};
    VOS_UINT8                           ucLogFilterFlag;

    if (VOS_OK != OM_GetLogPath(aucLogPath, USIMM_LOG_PATH, USIMM_UNITARY_LOG_PATH))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucLogCtrlFile, USIMM_LOGCTRL_FILE, USIMM_UNITARY_LOGCTRL_FILE))
    {
        return;
    }

    (VOS_VOID)VOS_MemSet(&g_stUSIMMLogData, 0, sizeof(g_stUSIMMLogData));
    (VOS_VOID)VOS_MemSet(&stCtrlData, 0, sizeof(stCtrlData));

    if (NV_OK != NV_ReadPartEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                           0,
                          &ucLogFilterFlag,
                           sizeof(VOS_UINT8)))
    {
        ucLogFilterFlag = VOS_FALSE;
    }

    if (VOS_TRUE == ucLogFilterFlag)
    {
        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }
    else
    {
        g_stUSIMMLogData.enLogState = USIMM_NEED_LOG;
    }

    g_stUSIMMLogData.pucData = (VOS_UINT8*)VOS_CacheMemAlloc(USIMM_LOG_DATA_MAX_LEN);

    if(VOS_NULL_PTR == g_stUSIMMLogData.pucData)
    {
        (VOS_VOID)LogPrint("\r\n USIMM_InitLogFile: malloc log buffer Error");

        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }

    /*先记录一个开始标记，表示开始初始化流程*/
    USIMM_LogDataSave((VOS_UINT8*)&ulStartFlag, sizeof(VOS_UINT32));

    fp = mdrv_file_open(aucLogCtrlFile, NV_FILE_OPEN_MODE_RW);

    if(VOS_NULL_PTR != fp)  /*文件存在不需要创建*/
    {
        (VOS_VOID)mdrv_file_close(fp);

        return;
    }

    if (MDRV_ERROR == mdrv_file_mkdir(aucLogPath))
    {
        (VOS_VOID)LogPrint("\r\n USIMM_InitLogFile: Mk Dir Error");
    }

    fp = mdrv_file_open(aucLogCtrlFile, NV_FILE_OPEN_MODE_NEW_RW);  /*创建文件*/

    if(VOS_NULL_PTR == fp)
    {
        (VOS_VOID)LogPrint("\r\n USIMM_InitLogFile: Creat Log Ctrl File Error");

        (VOS_VOID)VOS_CacheMemFree(g_stUSIMMLogData.pucData);

        g_stUSIMMLogData.pucData = VOS_NULL_PTR;

        return;
    }

    for(i=0; i<USIMM_LOG_FILE_MAX_NUM; i++)
    {
        /* 拼接LOG文件名称 */
        /*lint -e534*/
        VOS_sprintf(aucLogFile, "%s_%d", "UsimmInitLog", i);
        /*lint +e534*/

        (VOS_VOID)VOS_StrNCpy(stCtrlData.aucFileName[i], aucLogFile, USIMM_LOG_FILE_NAME_LEN);
    }

    stCtrlData.ulCurFile = 0;

    (VOS_VOID)mdrv_file_write((VOS_CHAR*)&stCtrlData, sizeof(VOS_CHAR), sizeof(USIMM_LOG_CTRLFILE_STRU), fp);

    (VOS_VOID)mdrv_file_close(fp);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_LogDataClear
功能描述  :清空log缓冲区的内容　并且关闭记录功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataClear(VOS_VOID)
{
    (VOS_VOID)VOS_CacheMemFree(g_stUSIMMExcLogData.pucData);

    g_stUSIMMExcLogData.pucData = VOS_NULL_PTR;

    g_stUSIMMExcLogData.ulDataLen = 0;

    g_stUSIMMExcLogData.enLogState = USIMM_NO_NEED_LOG;

    g_ulUSIMMExcLogLenBK = 0;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SaveLogFile
功能描述  :写入log文件的内容　，写入无论成功与否都关闭记录log功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SaveExcLogFile(VOS_VOID)
{
    FILE                               *logfp;
    VOS_CHAR                            aucLogPathFile[100] = {0};
    VOS_CHAR                            aucLogPath[USIMM_FILE_PATH_MAX_LEN] = {0};

    /*当前是否有保存数据*/
    if((VOS_NULL_PTR == g_stUSIMMExcLogData.pucData)||(0 == g_stUSIMMExcLogData.ulDataLen))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucLogPath, USIMM_LOG_PATH, USIMM_UNITARY_LOG_PATH))
    {
        return;
    }

    /* 拼接LOG文件路径 */
    /*lint -e534*/
    VOS_sprintf(aucLogPathFile, "%s/%s", aucLogPath, "USIMMExcFile.bin");
    /*lint +e534*/

    /*打开log文件，如果存在需要清空*/
    logfp = mdrv_file_open(aucLogPathFile, NV_FILE_OPEN_MODE_NEW_RW);

    if(VOS_NULL_PTR == logfp)
    {
        USIMM_ExcLogDataClear();
        return;
    }

    /*写入数据*/
    (VOS_VOID)mdrv_file_write((VOS_CHAR*)g_stUSIMMExcLogData.pucData, sizeof(VOS_CHAR), g_stUSIMMExcLogData.ulDataLen, logfp);

    (VOS_VOID)mdrv_file_close(logfp);

    /*清空数据*/
    USIMM_ExcLogDataClear();

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ExcLogDataBK
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataBK(VOS_VOID)
{
    g_ulUSIMMExcLogLenBK = g_stUSIMMExcLogData.ulDataLen;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ExcLogDataBK
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataRE(VOS_VOID)
{
    g_stUSIMMExcLogData.ulDataLen = g_ulUSIMMExcLogLenBK ;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ExcLogDataSave
功能描述  :保存数据到log缓冲区，TLV结构保存
输入参数  :pucData 需要保存的数据
           ucDataLen 保存数据长度
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen)
{
    VOS_UINT32      ulSlice;

    if((USIMM_NO_NEED_LOG == g_stUSIMMExcLogData.enLogState)   /*当前不需要记录log*/
        ||((g_stUSIMMExcLogData.ulDataLen + 6 + ucDataLen) > USIMM_EXCLOG_DATA_MAX_LEN)/*记录的log数据超过最大值,还需要计算tag和len的2个字节和时间戳4字节*/
        ||(VOS_NULL_PTR == g_stUSIMMExcLogData.pucData))       /*当前log缓冲区不存在*/
    {
        return;
    }

    g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen] = USIMM_LOG_DATA_TAG;  /*记录log*/

    g_stUSIMMExcLogData.ulDataLen ++;              /*长度+1*/

    ulSlice = OM_GetSlice();

    /*lint -e534*/
    VOS_MemCpy(&(g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen]), &ulSlice, sizeof(ulSlice));
    /*lint +e534*/

    g_stUSIMMExcLogData.ulDataLen += sizeof(ulSlice);              /*长度+1*/

    g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen] = ucDataLen;   /*记录数据长度*/

    g_stUSIMMExcLogData.ulDataLen ++;              /*长度+1*/

    /*lint -e534*/
    VOS_MemCpy(&(g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen]), pucData, ucDataLen);
    /*lint +e534*/

    g_stUSIMMExcLogData.ulDataLen += ucDataLen;    /*长度+数据长度*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitExcLogFile
功能描述  :初始化log文件的内容　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitExcLogFile(VOS_VOID)
{
    VOS_UINT8                           ucLogFilterFlag;

    g_stUSIMMExcLogData.ulDataLen  = 0;

    g_stUSIMMExcLogData.pucData    = VOS_NULL_PTR;

    g_ulUSIMMExcLogLenBK = 0;

    if (NV_OK != NV_ReadPartEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                           0,
                          &ucLogFilterFlag,
                           sizeof(VOS_UINT8)))
    {
        ucLogFilterFlag = VOS_FALSE;
    }

    if (VOS_TRUE == ucLogFilterFlag)
    {
        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }
    else
    {
        g_stUSIMMLogData.enLogState = USIMM_NEED_LOG;
    }

    g_stUSIMMExcLogData.pucData = (VOS_UINT8*)VOS_CacheMemAlloc(USIMM_EXCLOG_DATA_MAX_LEN);

    if(VOS_NULL_PTR == g_stUSIMMExcLogData.pucData)
    {
        (VOS_VOID)LogPrint("\r\n USIMM_InitLogFile: malloc log buffer Error");

        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_ClearCurDFInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearCurDFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo)
{
    pstCurFileInfo->usCurDFID       = USIMM_NULL_ID;

    pstCurFileInfo->usCurDFFcpLen   = 0;

    /*lint -e534*/
    VOS_MemSet(&(pstCurFileInfo->stDFInfo), 0, sizeof(USIMM_DFFCP_ST));
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : USIMM_ClearCurEFInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearCurEFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo)
{
    pstCurFileInfo->usCurEFID       = USIMM_NULL_ID;

    /*lint -e534*/
    VOS_MemSet(&(pstCurFileInfo->stEFInfo), 0, sizeof(USIMM_EFFCP_ST));
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : USIMM_ClearCurFileInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearCurFileInfo(USIMM_CARDAPP_ENUM_UINT32 enCardAppType)
{
    USIMM_CURFILEINFO_ST               *pstCurFile;

    pstCurFile = USIMM_CCB_GetCurFileInfo(enCardAppType);

    if (VOS_NULL_PTR != pstCurFile)
    {
        pstCurFile->usFilePathLen  = 0;

        /*lint -e534*/
        VOS_MemSet(pstCurFile->ausFilePath, 0, sizeof(pstCurFile->ausFilePath));
        /*lint +e534*/

        USIMM_ClearCurDFInfo(pstCurFile);

        USIMM_ClearCurEFInfo(pstCurFile);
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateFileByRelativePath
功能描述  :根据相对路径更新文件信息
输入参数  :pstSelectPara:      选择文件参数
           pstFilePath:        相对路径
           pstUSIMMCurFileInfo:当前文件信息
输出参数  :无
返 回 值  :无
调用函数  :无
 修订记录  :
1. 日    期    : 2013年6月28日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_UpdateFileByRelativePath(USIMM_SELECT_PARA_STUR *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU    *pstFilePath,
                                            USIMM_CURFILEINFO_ST     *pstUSIMMCurFileInfo)
{
    VOS_UINT32                          ulMaxLen;
    VOS_UINT16                          ausFileAllPath[USIMM_MAX_PATH_LEN] = {0};
    USIMM_U16_LVDATA_STRU               stFileAllPath;
    VOS_UINT32                          ulTempLen;

    if (0 == pstFilePath->ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_UpdateFileByRelativePath: The Data Path is empty.");

        return;
    }

    /* 根据路径的首目录获得全路径长度 */
    switch(USIMM_FILE_TYPE(pstFilePath->pusData[0]))
    {
        case EFUNDERMF:
            ulMaxLen  = 1;
            ulTempLen = 2;
            break;

        case MFTAG:
            ulMaxLen  = 4;
            ulTempLen = pstFilePath->ulDataLen;
            break;

        case EFUNDERGRANDADF:
            ulMaxLen  = 1;
            ulTempLen = 4;
            break;

        case DFUNDERDF:
            ulMaxLen  = 2;
            ulTempLen = pstFilePath->ulDataLen + 2;
            break;

        case EFUNDERDF:
            ulMaxLen  = 1;
            ulTempLen = pstFilePath->ulDataLen + 2;
            break;

        case DFUNDERMF:
            ulMaxLen  = 3;
            ulTempLen = pstFilePath->ulDataLen + 1;
            break;

        default:
            return;
    }

    if (ulMaxLen < pstFilePath->ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_UpdateFileByRelativePath: The File Path is Too Long");

        return;
    }

    /* 计算从当前路径需要获得的路径长度 */
    ulTempLen -= pstFilePath->ulDataLen;

    /*lint -e534*/
    VOS_MemCpy(ausFileAllPath, pstUSIMMCurFileInfo->ausFilePath, ulTempLen*sizeof(VOS_UINT16));
    VOS_MemCpy(&ausFileAllPath[ulTempLen], pstFilePath->pusData, pstFilePath->ulDataLen*sizeof(VOS_UINT16));
    /*lint +e534*/

    stFileAllPath.ulDataLen = ulTempLen + pstFilePath->ulDataLen;
    stFileAllPath.pusData   = ausFileAllPath;

    USIMM_UpdateFilePath(pstSelectPara, &stFileAllPath, pstUSIMMCurFileInfo);
}

/*****************************************************************************
函 数 名  :USIMM_UpdateFilePath
功能描述  :
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
           enUpdateFlag:更新文件FCP标识
输出参数  :无
返 回 值  :无
调用函数  :无
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年4月29日
   作    者   : j00168360
   修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
*****************************************************************************/
VOS_VOID USIMM_UpdateFilePath(USIMM_SELECT_PARA_STUR      *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU       *pstFilePath,
                                        USIMM_CURFILEINFO_ST        *pstUSIMMCurFileInfo)
{
    VOS_UINT16                          usFileId;

    if (0 == pstFilePath->ulDataLen)
    {
        return;
    }

    USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Need Update the File Info");

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMCurFileInfo->ausFilePath, pstFilePath->pusData, (pstFilePath->ulDataLen)*sizeof(VOS_UINT16));
    /*lint +e534*/

    pstUSIMMCurFileInfo->usFilePathLen = (VOS_UINT16)pstFilePath->ulDataLen;

    usFileId = pstUSIMMCurFileInfo->ausFilePath[pstFilePath->ulDataLen - 1];

    /* 判断是否为EF文件路径 */
    if (USIMM_IS_EF_FILE(usFileId))
    {
        pstUSIMMCurFileInfo->usCurEFID = usFileId;

        pstUSIMMCurFileInfo->usCurDFID = pstUSIMMCurFileInfo->ausFilePath[pstFilePath->ulDataLen - 2];;

        USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Update the EF File Info");
    }
    else
    {
        pstUSIMMCurFileInfo->usCurEFID = USIMM_NULL_ID;

        pstUSIMMCurFileInfo->usCurDFID = usFileId;

        /*lint -e534*/
        VOS_MemSet(&pstUSIMMCurFileInfo->stEFInfo, 0 ,sizeof(USIMM_EFFCP_ST));
        /*lint +e534*/

        USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Clean the EF File Info");
    }

    USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Need Update the DF Fcp Len");

    return;
}

/*****************************************************************************
函 数 名  :USIMM_OpenSpeedFileInit
功能描述  :初始化快速开机需要的文件初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年5月22日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_OpenSpeedFileInit(VOS_VOID)
{
    VOS_UINT8                           aucImsi[USIMM_EF6F07Len];
    VOS_UINT8                           aucImsiDefault[USIMM_EF6F07Len] = {0x8,0x9,0x10,0x10,0x10,0x32,0x54,0x6,0x36};
    VOS_UINT8                          *pucData;
    USIMM_POOL_ONERECORD_ST             stRecord;

    /*lint -e534*/
    VOS_MemSet(&stRecord, 0 , sizeof(USIMM_POOL_ONERECORD_ST));
    /*lint +e534*/

    if (VOS_OK != NV_Read(en_NV_Item_EF6F07, (VOS_VOID *)aucImsi, USIMM_EF6F07Len))
    {
        pucData = aucImsiDefault;
    }
    else
    {
        pucData = aucImsi;
    }
    stRecord.usEFId     = EFIMSI;
    stRecord.usLen      = USIMM_EF6F07Len;
    stRecord.enAppType  = USIMM_GUTL_APP;
    stRecord.enFileType = USIMM_EFSTRUCTURE_TRANSPARENT;
    stRecord.pucContent = pucData;

    (VOS_VOID)USIMM_PoolInsertOneFile(&stRecord);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_UsimVoltageSwitch
功能描述  :USIMM卡电压切换
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK
修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UsimVoltageSwitch(VOS_UINT8 ucCharaByte, VOS_UINT8 *pucVoltageMismatchFlag)
{
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;

    VOS_UINT32                          ulResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    /*lint -e534*/
    VOS_MemCpy(stFilePath.acPath, (VOS_CHAR*)USIMM_MF_STR, VOS_StrLen(USIMM_MF_STR) + 1 );
    /*lint +e534*/

    stFilePath.ulPathLen    = VOS_StrLen(USIMM_MF_STR);

    if (USIMM_VOLTAGE_1_8V == (ucCharaByte & USIMM_VOLTAGE_1_8V))
    {
        USIMM_INFO_LOG("USIMM_UsimVoltageSwitch:the current Voltage is 1.8V.");
        return VOS_OK;
    }

    if (USIMM_VOLTAGE_3V == (ucCharaByte & USIMM_VOLTAGE_3V))
    {
        *pucVoltageMismatchFlag = VOS_TRUE;

        /* 如果MF的FCP中指示电压为3V的话，则切换电压，底软API不会出现3V到3V的切换 */
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_UsimVoltageSwitch:SIM Card Change the Voltage Failed.");

            return VOS_ERR;
        }

        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            return VOS_OK;
        }

        USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);   /* 保正 MF 可以选到 */

        /* 电压切换后再选择一次MF */
        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, &stFilePath);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_InsertNoNeedPinFileToPool: Select MF is Failed");

            return VOS_ERR;
        }

        return VOS_OK;
    }

    if (USIMM_VOLTAGE_5V == (ucCharaByte & USIMM_VOLTAGE_5V))
    {
        *pucVoltageMismatchFlag = VOS_TRUE;

        USIMM_ERROR_LOG("USIMM_UsimVoltageSwitch:Voltage is 5V.");
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UsimVoltageSwitch:the current Voltage is ERROR.");
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_UsimTerminalCapability
功能描述  : USIMM卡terminal capability下发
输入参数  : 无
输出参数  : 无
返 回 值  : VOS_VOID

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_UsimTerminalCapability(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_TERMINAL_CAPABILITY_STRU      stTerminalCapability;

    /* 判断是否需要下发terminal capability */
    if (USIMM_SUPSYSCMD == USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->ucSupCmd)
    {
        /* 读nv,判断是否支持terminal capability下发，支持的话获取下发数据单元 */
        if (NV_OK == NV_Read(en_NV_Item_TERMINAL_CAPABILITY, &stTerminalCapability, sizeof(USIMM_TERMINAL_CAPABILITY_STRU)))
        {
            if ((VOS_TRUE == stTerminalCapability.ulIsEnable) && (0 != stTerminalCapability.ulLen))
            {
                /* 下发terminal capability p1 p2参数都填0 */
                ulResult = USIMM_SendTerminalCapabilityApdu(0, 0, &stTerminalCapability);

                if (USIMM_SW_OK != ulResult)
                {
                    /* 出错仅打印错误，不影响初始化流程 */
                    USIMM_ERROR_LOG("USIMM_UsimTerminalCapability: Send terminal capability is Failed");
                }
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitCardOptionalFile
功能描述  :实现了读取文件至缓存区的操作
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_PoolInsertOneFile
修订记录  :
1. 日    期   : 2008年8月20日
   作    者   : m00128685
   修改内容   : Creat
2. 日    期   : 2010年7月5日
   作    者   : j00168360
   修改内容   : [DTS2011070600422]GCF 27.22.4.7.2-2 Refresh测试用例失败

*****************************************************************************/
VOS_UINT32 USIMM_InitCardOptionalFile(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    USIMM_COMM_InitOPFile();

    return VOS_OK;
}


/********************************************************************
  Function:     USIMM_AttEfTerminalSupportTableValueGet
  Description:  获取终端能力参数值
  Input:        无
  Output:       无
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_AttEfTerminalSupportTableValueGet(VOS_UINT8 *pucValue)
{
    VOS_UINT8                           aucSuppotTableDefault[USIMM_ATT_SUPPORT_TABLE_MAX]  =
                                                            {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x02, 0x00,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    NVIM_SCAN_CTRL_STRU                 stNvScanCtrl;
    NVIM_ATT_ENS_CTRL_STRU              stNvEnsCtrl;
    NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU stNvActingHplmnCtrl;
    NAS_NVIM_MS_CLASS_STRU              stMsMode;

    if (VOS_OK == NV_Read(en_NV_Item_Scan_Ctrl_Para, (VOS_VOID *)&stNvScanCtrl, sizeof(NVIM_SCAN_CTRL_STRU)))
    {
        aucSuppotTableDefault[USIMM_ATT_SCAN_CTRL_OFFSET]           =   stNvScanCtrl.ucNvimActiveFlg;
    }

    if (VOS_OK == NV_Read(en_NV_Item_Att_Ens_Ctrl_Para, (VOS_VOID *)&stNvEnsCtrl, sizeof(NVIM_ATT_ENS_CTRL_STRU)))
    {
        aucSuppotTableDefault[USIMM_ATT_NETWORK_SELECTION_OFFSET]   =   stNvEnsCtrl.ucNetSelMenuFlg;
        aucSuppotTableDefault[USIMM_ATT_RAT_BALANCING]              =   stNvEnsCtrl.ucRatBalancingFlg;
    }

    if (VOS_OK == NV_Read(en_NV_Item_ACTING_PLMN_SUPPORT_FLAG, (VOS_VOID *)&stNvActingHplmnCtrl,
                          sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU)))
    {
        aucSuppotTableDefault[USIMM_ATT_ACTING_HPLMN]               =    stNvActingHplmnCtrl.ucNvimActiveFlg;
    }

    if (VOS_OK == NV_Read(en_NV_Item_MMA_MsClass, &stMsMode, sizeof(stMsMode)))
    {
        aucSuppotTableDefault[USIMM_ATT_LTE_SUPPORT]                = (NV_MS_MODE_PS_ONLY == stMsMode.ucMsClass)?USIMM_ATT_LTE_DATA_ONLY:USIMM_ATT_LTE_DATE_VOICE_CSFB;
    }

    /*lint -e534*/
    VOS_MemCpy(pucValue, aucSuppotTableDefault, sizeof(aucSuppotTableDefault));
    /*lint +e534*/

    return;
}

/********************************************************************
  Function:     USIMM_AttUpdataSupportTable
  Description:  ATT卡终端能力参数写入6FD2文件
  Input:        无
  Output:       无
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_AttUpdataSupportTable(
    VOS_UINT8                           ucChannelID)
{
    VOS_UINT8                               aucSuppotTable[USIMM_ATT_SUPPORT_TABLE_MAX]={0};
    VOS_UINT16                              usActureLen;
    USIMM_FILEPATH_INFO_STRU                stFilePath;

    /*lint -e534*/
    VOS_MemSet(&stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));
    /*lint +e534*/

    /* 判断AT&T定制是否打开 */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        return;
    }

    if (USIMM_PHYCARD_TYPE_UICC  == USIMM_CCB_GetCardType())
    {
        /*lint -e534*/
        VOS_MemCpy(stFilePath.acPath,
                  (VOS_CHAR*)USIMM_ATTUSIM_EFTERMINALTBL_STR,
                   VOS_StrLen((VOS_CHAR*)USIMM_ATTUSIM_EFTERMINALTBL_STR) + 1);
        /*lint +e534*/

        stFilePath.ulPathLen = VOS_StrLen((VOS_CHAR*)USIMM_ATTUSIM_EFTERMINALTBL_STR);
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stFilePath.acPath,
                  (VOS_CHAR*)USIMM_ATTGSM_EFTERMINALTBL_STR,
                   VOS_StrLen((VOS_CHAR*)USIMM_ATTGSM_EFTERMINALTBL_STR) + 1);
        /*lint +e534*/

        stFilePath.ulPathLen = VOS_StrLen((VOS_CHAR*)USIMM_ATTGSM_EFTERMINALTBL_STR);
    }


    /* 选择6FD2文件 */
    if(VOS_OK != USIMM_SelectFile(USIMM_GUTL_APP, USIMM_NEED_FCP, &stFilePath))
    {
        USIMM_ERROR_LOG("USIMM_AttUpdataSupportTable: Select File Error 0x6FD2");

        return;
    }

    USIMM_AttEfTerminalSupportTableValueGet(aucSuppotTable);

    /* 6FD2文件的长度只能为8或16或小于8的值 */
    if (USIMM_ATT_SUPPORT_TABLE_MAX <= USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->usFileLen)
    {
        usActureLen =   USIMM_ATT_SUPPORT_TABLE_MAX;
    }
    else if (USIMM_ATT_SUPPORT_TABLE_MIN <= USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->usFileLen)
    {
        usActureLen =   USIMM_ATT_SUPPORT_TABLE_MIN;
    }
    else
    {
        usActureLen =   USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->usFileLen;
    }

    if (VOS_OK != USIMM_SendUpdateBinaryApdu(ucChannelID, usActureLen, aucSuppotTable))
    {
        USIMM_ERROR_LOG("USIMM_AttUpdataSupportTable: USIMM_UpdateTFFile Fail");
    }

    return;
}


/*****************************************************************************
函 数 名  :USIMM_InitUsimEccFile
功能描述  :初始化USIM卡ECC文件
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat   [DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitUsimEccFile(VOS_VOID)
{
    VOS_UINT8                          *pData;
    VOS_UINT8                           ucEccType;
    VOS_UINT8                           ucRecordNum =0;
    VOS_UINT32                          ulResult;
    USIMM_EFFCP_ST                     *pstCurEFInfo;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    /*lint -e534*/
    VOS_MemSet(&stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));
    VOS_MemCpy(stFilePath.acPath,
              (VOS_CHAR*)USIMM_USIM_EFECC_STR,
               VOS_StrLen((VOS_CHAR*)USIMM_USIM_EFECC_STR) + 1);
    /*lint +e534*/

    stFilePath.ulPathLen = VOS_StrLen((VOS_CHAR*)USIMM_USIM_EFECC_STR);

    ulResult = USIMM_SelectFile(USIMM_GUTL_APP, USIMM_NEED_FCP, &stFilePath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_SELECT_FAIL;

        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:usim card select ECC file fail");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_USIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    pstCurEFInfo = USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP);

    if (VOS_NULL_PTR == pstCurEFInfo)
    {
        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:USIMM_CCB_GetCurEFInfo error");

        return VOS_OK;
    }

    if(USIMM_EFSTRUCTURE_FIXED != pstCurEFInfo->enFileType)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_TYPE_ERR;

        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:ECC FILE TYPE error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_USIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    pData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, 
                                        DYNAMIC_MEM_PT,
                                        pstCurEFInfo->usFileLen);/*分配数据存储空间*/

    if(VOS_NULL_PTR == pData)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:VOS_MemAlloc error");

        return VOS_ERR;
    }

    ucEccType   = ECC_USIM;

    ucRecordNum = pstCurEFInfo->ucRecordNum;

    ulResult    = USIMM_SendReadRecordApdu(USIMM_CCB_GetAppChNO(USIMM_GUTL_APP),
                                           pstCurEFInfo->ucRecordNum,
                                           pstCurEFInfo->ucRecordLen,
                                           USIMM_READ_ALLRECORD,
                                           pData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_READ_FAIL;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:USIMM_ReadLFFile error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_USIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    USIMM_EccNumberInd(ucEccType,
                       pstCurEFInfo->usFileLen,
                       ucRecordNum,
                       pData);  /* 上报当前的Ecc号码内容 */

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pData);
    /*lint +e534*/

    return VOS_OK;

}

/*****************************************************************************
函 数 名  :USIMM_InitSimEccFile
功能描述  :初始化SIM卡ECC文件,已和sunxibo确认出错情况下可以不上报默认值，只要报紧急号码为0即可
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK

修订记录  :
1. 日    期   : 2011年3月18日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_InitSimEccFile(
    VOS_UINT8                           ucChannelID)
{
    VOS_UINT8                           *pData;
    VOS_UINT8                           ucEccType;
    VOS_UINT8                           ucRecordNum =0;
    VOS_UINT32                          ulResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    USIMM_EFFCP_ST                      *pstCurEFInfo;

    /*lint -e534*/
    VOS_MemSet(&stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));

    VOS_MemCpy(stFilePath.acPath, (VOS_CHAR*)USIMM_GSM_EFECC_STR, VOS_StrLen((VOS_CHAR*)USIMM_GSM_EFECC_STR) + 1);
    /*lint +e534*/

    stFilePath.ulPathLen = VOS_StrLen((VOS_CHAR*)USIMM_GSM_EFECC_STR);

    ulResult = USIMM_SelectFile(USIMM_GUTL_APP, USIMM_NEED_FCP, &stFilePath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_SELECT_FAIL;

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_SIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    pstCurEFInfo = USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP);

    if (VOS_NULL_PTR == pstCurEFInfo)
    {
        USIMM_ERROR_LOG("USIMM_InitSimEccFile:ECC FILE TYPE error");

        return VOS_OK;
    }

    if(USIMM_EFSTRUCTURE_TRANSPARENT != pstCurEFInfo->enFileType)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_TYPE_ERR;

        USIMM_ERROR_LOG("USIMM_InitSimEccFile:ECC FILE TYPE error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_SIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    pData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,
                                        DYNAMIC_MEM_PT,
                                        pstCurEFInfo->usFileLen);/*分配数据存储空间*/

    if(VOS_NULL_PTR == pData)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_InitSimEccFile:VOS_MemAlloc error");

        return VOS_ERR;
    }

    ucEccType = ECC_SIM;

    ulResult = USIMM_SendReadBinaryApdu(ucChannelID, 
                                        VOS_NULL,
                                        pstCurEFInfo->usFileLen, 
                                        pData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_READ_FAIL;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_InitSimEccFile:USIMM_SendReadBinaryApdu error");

        /* 读取文件失败认为ECC文件不存在，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_SIM, 
                            VOS_NULL, 
                            VOS_NULL, 
                            VOS_NULL_PTR);

        return VOS_OK;
    }

    USIMM_EccNumberInd(ucEccType, 
                        pstCurEFInfo->usFileLen, 
                        ucRecordNum, 
                        pData);/*上报当前的Ecc号码内容*/

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pData);
    /*lint +e534*/

    return VOS_OK;
}


/*****************************************************************************
函 数 名  : USIMM_ChangePathToU16
功能描述  : 把UINT8编码个数的数据转换成UINT16的数据
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
/*lint -e661 -e662 by h59254*/
VOS_VOID USIMM_ChangePathToU16(VOS_UINT32 ulDataLen, VOS_UINT8 *pucData, VOS_UINT32 *pulLen, VOS_UINT16 *pusPath)
{
    VOS_UINT32 i;
    VOS_UINT32 j = 0;

    for(i=0; i<ulDataLen; i+=2, j++)
    {
        pusPath[j] = ((pucData[i]<<0x08)&0xFF00)+pucData[i+1];
    }

    *pulLen = j;

    return;
}
/*lint +e661 +e662 by h59254*/

/*****************************************************************************
函 数 名  :USIMM_SelectDFFile
功能描述  :安照文件ID方式选择DF
输入参数  :usFileId:DF文件ID
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
           USIMM_CheckSW
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SelectDFFile(
    VOS_UINT16                        usFileId,
    USIMM_SELECT_PARA_STUR           *pstSelectPara,
    USIMM_CURFILEINFO_ST             *pstCurFileInfo
)
{
    VOS_UINT8                           aucDFid[2];
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;

    stApduHead.ucChannel    = USIMM_CCB_GetAppChNO(pstSelectPara->enAppType);

    if (VOS_NULL_BYTE == stApduHead.ucChannel)
    {
        USIMM_WARNING_LOG("USIMM_SelectEFByID: The Input App Error");

        return USIMM_SW_ERR;
    }

    aucDFid[0] = (VOS_INT8)((usFileId>>8)&0xFF);

    aucDFid[1] = (VOS_UINT8)(usFileId&0xFF);

    stApduHead.ucINS    = CMD_INS_SELECT;

    if (USIMM_PHYCARD_TYPE_ICC == pstSelectPara->enCardType)    /*SIM卡*/
    {
        stApduHead.ucP2 = USIMM_SIM_SELECT_P2_PARA;
    }
    else
    {
        stApduHead.ucP2 = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    }

    stApduHead.ucP1 = USIMM_SELECT_BY_FILE_ID;

    stApduData.ulDataLen = sizeof(aucDFid);

    stApduData.pucData = aucDFid;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);/*选择文件*/

    /*判断检查结果*/
    if(USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SelectDFFile:USIMM_SendAPDUHandle error");

        return ulResult;
    }

    /*DF 都返回FCP，解析获取的数据*/
    ulResult = USIMM_DecodeDFFcp(pstSelectPara->enCardType, &stRspData, pstCurFileInfo);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectDFFile:Decode Fcp error");

        return USIMM_SW_ERR;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectEFByID
功能描述  :按照文件ID方式选中EF并解析FCP
输入参数  :usFileId:文件ID
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
 1. 日    期   : 2007年7月10日
     作    者   : z00100318
     修改内容   : Creat
 2. 日    期   : 2011年4月29日
    作    者   : j00168360
    修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
*****************************************************************************/
VOS_UINT32 USIMM_SelectEFByID(VOS_UINT16                     usFileId,
                                    USIMM_SELECT_PARA_STUR           *pstSelectPara,
                                    USIMM_CURFILEINFO_ST             *pstCurFileInfo)
{
    VOS_UINT8                           aucEfId[2];
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;

    stApduHead.ucChannel    = USIMM_CCB_GetAppChNO(pstSelectPara->enAppType);

    if (VOS_NULL_BYTE == stApduHead.ucChannel)
    {
        USIMM_WARNING_LOG("USIMM_SelectEFByID: The Input App Error");

        return USIMM_SW_ERR;
    }

    aucEfId[0] = (VOS_UINT8)((usFileId>>8)&0xFF);

    aucEfId[1] = (VOS_UINT8)(usFileId&0xFF);

    stApduHead.ucINS= CMD_INS_SELECT;

    stApduHead.ucP1 = USIMM_SELECT_BY_FILE_ID;

    if(USIMM_PHYCARD_TYPE_ICC == pstSelectPara->enCardType)
    {
        stApduHead.ucP2  = USIMM_SIM_SELECT_P2_PARA;
    }
    else
    {
        if (USIMM_NEED_FCP == pstSelectPara->enEfFcpFlag)
        {
            stApduHead.ucP2 = USIMM_SELECT_RETURN_FCP_TEMPLATE;
        }
        else
        {
            stApduHead.ucP2 = USIMM_SELECT_NO_DATA_RETURNED;
        }
    }

    stApduData.ulDataLen = sizeof(aucEfId);

    stApduData.pucData = aucEfId;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);  /*选择文件*/

    if(USIMM_SW_OK != ulResult)/*判断检查结果*/
    {
        USIMM_WARNING_LOG("USIMM_SelectEFByID:USIMM_ReselectFileAPDU error");

        return ulResult;
    }

    if (VOS_NULL != stRspData.usRspLen)
    {
        ulResult = USIMM_DecodeEFFcp(pstSelectPara->enCardType, &stRspData, pstCurFileInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_SelectEFByID:Decode FCP error");

            return USIMM_SW_ERR;
        }
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileNoPath
功能描述  :根据路安装单步方式选择EF
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年4月29日
   作    者   : j00168360
   修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
3. 日    期  : 2011年8月22日
   作    者  : j00168360
   修改内容  : [DTS2011081901894]，at+crsm命令引起的掉卡
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileNoPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult = USIMM_SW_ERR;

    /*lint -e830 -e539*/
    for (i = 0; i < pstFilePath->ulDataLen; i++)
    {
        if (USIMM_IS_DF_FILE(pstFilePath->pusData[i]))
        {
            ulResult = USIMM_SelectDFFile(pstFilePath->pusData[i], pstSelectPara, pstCurFileInfo);
        }
        else
        {
            ulResult = USIMM_SelectEFByID(pstFilePath->pusData[i], pstSelectPara, pstCurFileInfo);
        }

        if ((USIMM_SW_OK != ulResult)&&(USIMM_SW_OK_WITH_SAT != ulResult))
        {
            USIMM_ERROR_LOG("USIMM_SelectFileNoPath: Select File Error.");

            break;
        }
    }

    /* 无论是否选中当前文件路径都需要更新 */
    if (VOS_NULL_PTR != pusCurPathLen)
    {
        *pusCurPathLen = (VOS_UINT16)i;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_GetDiffPos
功能描述  :获得当前文件和选择文件的不同位置
输入参数  :pstFilePath:   选择文件路径
           pstCurFileInfo:当前文件信息
输出参数  :无
返 回 值  :路径不同点，从0开始

 修订记录  :
1. 日    期    : 2013年6月20日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetDiffPos(USIMM_U16_LVDATA_STRU *pstFilePath,
                                  USIMM_CURFILEINFO_ST  *pstCurFileInfo)
{
    VOS_UINT32                          ulMinLen;
    VOS_UINT32                          ulDiffPos;

    if (pstFilePath->ulDataLen < pstCurFileInfo->usFilePathLen)
    {
        ulMinLen = pstFilePath->ulDataLen;
    }
    else
    {
        ulMinLen = pstCurFileInfo->usFilePathLen;
    }

    /* 比较选择路径和当前路径 */
    for (ulDiffPos = 0; ulDiffPos < ulMinLen; ulDiffPos++)
    {
        if (pstCurFileInfo->ausFilePath[ulDiffPos] != pstFilePath->pusData[ulDiffPos])
        {
            break;
        }
    }

    return ulDiffPos;
}

/*****************************************************************************
函 数 名  :USIMM_GetCurDfPos
功能描述  :获得路径的当前目录位置
输入参数  :pstCurFileInfo:  当前的文件信息
输出参数  :无
返 回 值  :目录的位置，从0开始

 修订记录  :
1. 日    期    : 2013年6月20日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCurDfPos(USIMM_CURFILEINFO_ST *pstCurFileInfo)
{
    VOS_UINT32                              ulCurDFPos;

    /* 获得当前路径所在位置 */
    if (USIMM_NULL_ID == pstCurFileInfo->usCurEFID)
    {
        ulCurDFPos = pstCurFileInfo->usFilePathLen - 1;
    }
    else
    {
        ulCurDFPos = pstCurFileInfo->usFilePathLen - 2;
    }

    return ulCurDFPos;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileByRelativePath
功能描述  :通过相对路径方式单步选择文件
输入参数  :pstSelectPara:  选择文件参数
           pstFilePath:    选择文件路径
           pstCurFileInfo: 当前选中文件的信息
输出参数  :无
返 回 值  :VOS_ERR

 修订记录  :
1. 日    期    : 2013年6月20日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileByRelativePath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo)
{
    VOS_UINT32                          ulRelativeLen = 0;
    VOS_UINT16                          ausRelativePath[USIMM_MAX_PATH_LEN] = {0};
    USIMM_U16_LVDATA_STRU               stRelativePath = {0};
    VOS_UINT32                          ulDiffPos ;
    VOS_UINT32                          ulCurDFPos;

    /* 上次文件没有选中，则相对路径就是绝对路径 */
    if (0 == pstCurFileInfo->usFilePathLen)
    {
        return USIMM_SW_ERR;
    }

    ulDiffPos  = USIMM_GetDiffPos(pstFilePath, pstCurFileInfo);

    ulCurDFPos = USIMM_GetCurDfPos(pstCurFileInfo);

    if (ulCurDFPos == (ulDiffPos - 1))
    {
        /* 需要选中当前目录 */
        if ((USIMM_NULL_ID != pstCurFileInfo->usCurEFID)
            && (ulDiffPos == pstFilePath->ulDataLen))
        {
            /*lint -e534*/
            VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos - 1], sizeof(VOS_UINT16));
            /*lint +e534*/

            ulRelativeLen = 1;
        }
        else /* 当前目录的所有子节点文件可选 */
        {
            /*lint -e534*/
            VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos], (pstFilePath->ulDataLen- ulDiffPos)*sizeof(VOS_UINT16));
            /*lint +e534*/

            ulRelativeLen =  pstFilePath->ulDataLen - ulDiffPos;
        }
    }

    if (ulCurDFPos == ulDiffPos)
    {
        /* 当前目录父节点下的DF文件可选 */
        if (ulDiffPos < pstFilePath->ulDataLen)
        {
            if (USIMM_IS_DF_FILE(pstFilePath->pusData[ulDiffPos])
                && (ADF != pstCurFileInfo->ausFilePath[ulCurDFPos]))
            {
                /*lint -e534*/
                VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos], (pstFilePath->ulDataLen - ulDiffPos)*sizeof(VOS_UINT16));
                /*lint +e534*/

                ulRelativeLen = pstFilePath->ulDataLen - ulDiffPos;
            }
        }
        else
        {
            /* 当前目录的父节点可选 */
            /*lint -e534*/
            VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos - 1], sizeof(VOS_UINT16));
            /*lint +e534*/

            ulRelativeLen = 1;
        }
    }

    /* 假如选择的路径与当前路径相同则再选次最后的文件 */
    if ((ulDiffPos == pstCurFileInfo->usFilePathLen) && (ulDiffPos == pstFilePath->ulDataLen))
    {
        /*lint -e534*/
        VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos - 1], sizeof(VOS_UINT16));
        /*lint +e534*/

        ulRelativeLen = 1;
    }

    /* 不能获得相对路径 */
    if (0 == ulRelativeLen)
    {
        USIMM_WARNING_LOG("USIMM_SelectFileByRelativePath: Can't get relative path.");

        return USIMM_SW_ERR;
    }

    stRelativePath.ulDataLen = ulRelativeLen;
    stRelativePath.pusData   = ausRelativePath;

    return USIMM_SelectFileNoPath(pstSelectPara, &stRelativePath, pstCurFileInfo, VOS_NULL_PTR);
}

/*****************************************************************************
函 数 名  :USIMM_SelectEFByPath
功能描述  :按照路径方式选择当前的EF
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年4月29日
   作    者   : j00168360
   修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileByPath(USIMM_SELECT_PARA_STUR      *pstSelectPara,
                                         USIMM_U16_LVDATA_STRU          *pstFilePath,
                                         USIMM_CURFILEINFO_ST           *pstCurFileInfo)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPathLen;
    VOS_UINT8                           aucPath[USIMM_MAX_PATH_LEN*2] = {0};
    VOS_UINT32                          i;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulIsDF;

    /* 路径至少包括MF和2Fxx */
    if ((pstFilePath->ulDataLen < 2)||(VOS_NULL_PTR == pstFilePath->pusData))
    {
        USIMM_WARNING_LOG("USIMM_SelectFileByPath: The Input Para Error");

        return USIMM_SW_ERR;
    }

    for (i = 0; i < (pstFilePath->ulDataLen-1); i++)    /*跳过前面的MF*/
    {
        aucPath[i*2] = (VOS_UINT8)((pstFilePath->pusData[i+1]>>0x08)&0x00FF);

        aucPath[(i*2)+1] = (VOS_UINT8)(pstFilePath->pusData[i+1]&0x00FF);
    }

    ucPathLen = (VOS_UINT8)((pstFilePath->ulDataLen-1)*sizeof(VOS_UINT16));

    stApduHead.ucChannel    = USIMM_CCB_GetAppChNO(pstSelectPara->enAppType);

    if (VOS_NULL_BYTE == stApduHead.ucChannel)
    {
        USIMM_WARNING_LOG("USIMM_SelectFileByPath: The Input App Error");

        return USIMM_SW_ERR;
    }

    stApduHead.ucINS= CMD_INS_SELECT;

    stApduHead.ucP1 = USIMM_SELECT_BY_PATH_FROM_MF;

    ulIsDF = USIMM_IS_DF_FILE(pstFilePath->pusData[pstFilePath->ulDataLen-1]);

    if ((VOS_TRUE == ulIsDF) || (USIMM_NEED_FCP == pstSelectPara->enEfFcpFlag))
    {
         stApduHead.ucP2 = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    }
    else
    {
         stApduHead.ucP2 = USIMM_SELECT_NO_DATA_RETURNED;
    }

    stApduData.ulDataLen    = ucPathLen;

    stApduData.pucData      = aucPath;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead, 
                                    &stApduData, 
                                    &stRspData);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SelectEFByPath: USIMM_SendAPDUHandle Error");

        return ulResult;
    }

    if (VOS_NULL != stRspData.usRspLen)
    {
        if (VOS_FALSE == ulIsDF)
        {
            pstCurFileInfo->usCurDFFcpLen = VOS_NULL;
        }

        ulResult = USIMM_DecodeFileFcp(pstSelectPara->enCardType, pstFilePath, &stRspData, pstCurFileInfo);

        if (VOS_OK != ulResult)  /*选不中文件的时候不需要更新路径*/
        {
            USIMM_WARNING_LOG("USIMM_SelectEFByPath: Decode Fcp Error");

            return USIMM_SW_ERR;
        }
    }
    else
    {
        USIMM_ClearCurDFInfo(pstCurFileInfo);

        USIMM_ClearCurEFInfo(pstCurFileInfo);
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileWithPath
功能描述  :按照路径方式选择当前的EF
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期  : 2011年8月30日
   作    者  : j00168360
   修改内容  : [DTS2011083000162]，USIM模块正向清理保护性复位及卡路径选择
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileWithPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen
)
{
    VOS_UINT32                          ulResult;

    *pusCurPathLen = (VOS_UINT16)pstFilePath->ulDataLen;

    /* 首先处理只选MF文件 */
    if ((1 == pstFilePath->ulDataLen) && (MFTAG == USIMM_FILE_TYPE(pstFilePath->pusData[0])))
    {
        ulResult = USIMM_SelectDFFile(pstFilePath->pusData[0], pstSelectPara, pstCurFileInfo);

        if (USIMM_SW_OK != ulResult)
        {
            *pusCurPathLen = 0;
        }

        return ulResult;
    }

    /* 在USIM卡上通过路径选择方式进行文件选择 */
    if (USIMM_PHYCARD_TYPE_UICC == pstSelectPara->enCardType)
    {
        ulResult = USIMM_SelectFileByPath(pstSelectPara, pstFilePath, pstCurFileInfo);
    }
    /* 在SIM卡上通过相对路径方式进行单步选择 */
    else
    {
        ulResult = USIMM_SelectFileByRelativePath(pstSelectPara, pstFilePath, pstCurFileInfo);
    }

    if (USIMM_SW_OK != ulResult)
    {
        /* 最后采用绝对路径方式进行单步选择 */
        ulResult = USIMM_SelectFileNoPath(pstSelectPara, pstFilePath, pstCurFileInfo, pusCurPathLen);
    }

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SelectFileWithPath: Select File Failed");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  : USIMM_GetAIDType
功能描述  : 根据AID长度获取当前所属类型
输入参数  : ulAidLen:AID长度
            pucAid:AID内容
输出参数  : 无
返 回 值  : USIMM_CARDAPP_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增加函数
*****************************************************************************/
USIMM_CARDAPP_ENUM_UINT32 USIMM_GetAIDType(
    VOS_UINT32                              ulAidLen,
    VOS_UINT8                              *pucAid)
{
    VOS_UINT32                      i;
    USIMM_AID_INFO_STRU             *pstAIDInfo;

    for(i=0; i<USIMM_CARDAPP_BUTT; i++)
    {
        pstAIDInfo = USIMM_CCB_GetAIDByApp(i);

        if (VOS_NULL_PTR == pstAIDInfo)
        {
            continue;
        }

        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pstAIDInfo->aucAID, pucAid, ulAidLen))
        /*lint +e534*/
        {
            return i;
        }
    }

    return USIMM_CARDAPP_BUTT;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshNoFileIndHandle
功能描述  :没有文件ID指示类型的REFRESH命令上报函数
输入参数  :pstMsg:REFRESH命令消息
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年05月28日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshNoFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg)
{
    USIMM_STKREFRESH_IND_STRU              *pstRefreshMsg;

    pstRefreshMsg = (USIMM_STKREFRESH_IND_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKREFRESH_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRefreshMsg)
    {
        USIMM_WARNING_LOG("USIMM_RefreshNoFileIndHandle: Alloc Msg is Fail");

        return;
    }

    pstRefreshMsg->stIndHdr.ulReceiverPid   = MAPS_PIH_PID;        /*由PIH负责广播*/
    pstRefreshMsg->stIndHdr.enMsgName       = USIMM_STKREFRESH_IND;
    pstRefreshMsg->usEfNum                  = VOS_NULL;
    pstRefreshMsg->enRefreshType            = USIMM_GetRefreshIndType(pstMsg);


    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstRefreshMsg);

    return;
}

/*****************************************************************************
 函 数 名  : USIMM_GetEFPathFromFList
 功能描述  : 获取Filelist中的一个EF文件路径
 输入参数  : pucFileList: EF文件列表
             ulFileLen:文件列表长度

 输出参数  : pucEFPath:存放第一个EF文件路径
             pulPathLen:第一个EF文件路径长度

 返 回 值  : VOS_ERR:未找到匹配文件
             VOS_OK:找到EF文件

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增加函数

*****************************************************************************/
VOS_UINT32 USIMM_GetEFPathFromFList(
    VOS_UINT8                          *pucFileList,
    VOS_UINT32                          ulFileLen,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    VOS_UINT32                         *pulLen)
{
    VOS_UINT32          ulFileCnt;
    VOS_UINT32          ulDataLen;
    VOS_UINT8           aucEFPath[USIMM_MAX_PATH_LEN*2];

    /*lint -e440 */
    for(ulFileCnt = 0; ((ulFileCnt+1) < ulFileLen); ulFileCnt += sizeof(VOS_UINT16))
    /*lint +e440 */
    {
        if((ulFileCnt+1) >= (USIMM_MAX_PATH_LEN*2))
        {
            break;
        }

        aucEFPath[ulFileCnt]    = pucFileList[ulFileCnt];
        aucEFPath[ulFileCnt+1]  = pucFileList[ulFileCnt+1];

        if((EFUNDERMF           != pucFileList[ulFileCnt])
            &&(EFUNDERDF        != pucFileList[ulFileCnt])
            &&(EFUNDERGRANDADF  != pucFileList[ulFileCnt]))/*判断不为EF文件*/
        {
            continue;
        }

        ulDataLen = ulFileCnt+2;

        USIMM_ChangePathToAsciiString(aucEFPath, (VOS_UINT8)ulDataLen, pstFilePath);

        pstFilePath->acPath[pstFilePath->ulPathLen] = '\0';

        pstFilePath->ulPathLen++;

        *pulLen = ulDataLen;

        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
函 数 名  :USIMM_RefreshIsimFileIndHandle
功能描述  :实现了IMSI文件更新上报功能
输入参数  :pstRefreshMsg: 文件更新上报消息
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年7月24日
   作    者   : g47350
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshIsimFileIndHandle(USIMM_STKREFRESH_IND_STRU *pstRefreshMsg)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usFileNum = 0;
    USIMM_STKREFRESH_IND_STRU          *pstIsimRefreshMsg;
    USIM_REFRESH_FILE_STRU             *pstFile;
    VOS_CHAR                           *pcFileStr;
    USIMM_DEF_FILEID_ENUM_UINT16        usFileId;
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardSvr;

    enCardSvr           = USIMM_CCB_GetAppService(USIMM_IMS_APP);

    /* 判断当前是否支持ISIM卡 */
    if ((VOS_TRUE                        != USIMM_CCB_GetUsimSimulateIsimStatus())
      || (USIMM_CARD_SERVIC_AVAILABLE    != enCardSvr))
    {
        USIMM_INFO_LOG("USIMM_RefreshIsimFileIndHandle: IMS is disable.");

        return;
    }

    pstFile = (USIM_REFRESH_FILE_STRU*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, sizeof(USIM_REFRESH_FILE_STRU) * USIMM_MAX_REFRESH_FILE_NUM);

    if (VOS_NULL_PTR == pstFile)
    {
        USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: VOS_MemAlloc is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet(pstFile, 0, USIMM_MAX_REFRESH_FILE_NUM * sizeof(USIM_REFRESH_FILE_STRU));
    /*lint +e534*/

    for (i=0; i<pstRefreshMsg->usEfNum; i++)
    {
        if (USIMM_GUTL_APP == pstRefreshMsg->astEfId[i].enAppType)
        {
            /* IMSI对应3个ISIM文件 */
            if (USIMM_USIM_EFIMSI_ID == pstRefreshMsg->astEfId[i].usFileId)
            {
                /* 处理6F02 */
                pstFile[usFileNum].enAppType = USIMM_IMS_APP;

                pstFile[usFileNum].usFileId  = USIMM_ISIM_EFIMPI_ID;

                pstFile[usFileNum].usPathLen = (VOS_UINT16)(VOS_StrLen(USIMM_ISIM_EFIMPI_STR) + 1);

                /*lint -e534*/
                VOS_MemCpy(pstFile[usFileNum].aucPath,
                            USIMM_ISIM_EFIMPI_STR,
                            pstFile[usFileNum].usPathLen);
                /*lint +e534*/

                usFileNum++;

                /* 处理6F03 */
                pstFile[usFileNum].enAppType = USIMM_IMS_APP;

                pstFile[usFileNum].usFileId  = USIMM_ISIM_EFDOMAIN_ID;

                pstFile[usFileNum].usPathLen = (VOS_UINT16)(VOS_StrLen(USIMM_ISIM_EFDOMAIN_STR) + 1);

                /*lint -e534*/
                VOS_MemCpy(pstFile[usFileNum].aucPath,
                            USIMM_ISIM_EFDOMAIN_STR,
                            pstFile[usFileNum].usPathLen);
                /*lint +e534*/

                usFileNum++;

                /* 处理6F04 */
                pstFile[usFileNum].enAppType = USIMM_IMS_APP;

                pstFile[usFileNum].usFileId  = USIMM_ISIM_EFIMPU_ID;

                pstFile[usFileNum].usPathLen = (VOS_UINT16)(VOS_StrLen(USIMM_ISIM_EFIMPU_STR) + 1);

                /*lint -e534*/
                VOS_MemCpy(pstFile[usFileNum].aucPath,
                           USIMM_ISIM_EFIMPU_STR,
                           pstFile[usFileNum].usPathLen);
                /*lint +e534*/

                usFileNum++;

                continue;
            }

            /* 判断是否为ISIM对应文件 */
            usFileId = (VOS_UINT16)USIMM_UsimEFIDToIsimEFID(pstRefreshMsg->astEfId[i].usFileId);

            if (VOS_NULL_WORD != usFileId)
            {
                if (VOS_OK != USIMM_ChangeDefFileToPath(usFileId, &pcFileStr))
                {
                    USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: USIMM_ChangeDefFileToPath is Failed");

                    continue;
                }

                pstFile[usFileNum].enAppType = USIMM_IMS_APP;

                pstFile[usFileNum].usFileId  = usFileId;

                pstFile[usFileNum].usPathLen = (VOS_UINT16)(VOS_StrLen(pcFileStr) + 1);

                /*lint -e534*/
                VOS_MemCpy(pstFile[usFileNum].aucPath, pcFileStr, pstFile[usFileNum].usPathLen);
                /*lint +e534*/

                usFileNum++;
            }
        }
    }

    /* 没有涉及ISIM文件则不用通知 */
    if (0 == usFileNum)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstFile);
        /*lint +e534*/

        return;
    }

    /* 由于USIM_REFRESH_IND_STRU中已经有一个USIM_REFRESH_IND_STRU单元所以usFileNum需要减1 */
    pstIsimRefreshMsg = (USIMM_STKREFRESH_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                                  (sizeof(USIMM_STKREFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH)\
                                                                  + ((usFileNum - 1) * sizeof(USIM_REFRESH_FILE_STRU)));

    if (VOS_NULL_PTR == pstIsimRefreshMsg)
    {
        USIMM_ERROR_LOG("USIMM_RefreshIsimFileIndHandle: VOS_AllocMsg is Failed");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstFile);
        /*lint +e534*/

        return;
    }

    pstIsimRefreshMsg->stIndHdr.ulReceiverPid               = MAPS_PIH_PID;
    pstIsimRefreshMsg->stIndHdr.enMsgName                   = USIMM_STKREFRESH_IND;
    pstIsimRefreshMsg->enRefreshType                        = USIMM_REFRESH_FILE_LIST;
    pstIsimRefreshMsg->usEfNum                              = usFileNum;

    /*lint -e534*/
    VOS_MemCpy(pstIsimRefreshMsg->astEfId, pstFile, usFileNum * sizeof(USIM_REFRESH_FILE_STRU));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstIsimRefreshMsg);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pstFile);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_GetRefreshIndType
功能描述  :实现了读取文件的操作和结果的返回
输入参数  :API层下发消息内容
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增加函数

*****************************************************************************/

USIMM_REFRESH_FILE_TYPE_UINT16 USIMM_GetRefreshIndType(
    USIMM_STKREFRESH_REQ_STRU          *pstMsg)
{
    if (USIMM_SESSION_RESET_3G_ONLY      == pstMsg->enRefreshType)
    {
        return USIMM_REFRESH_3G_SESSION_RESET;
    }
    else if ((USIMM_INITIAL_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType)
          || (USIMM_FILE_CHANGE_NOTIFY  == pstMsg->enRefreshType))
    {
        return USIMM_REFRESH_FILE_LIST;
    }
    else
    {
        return USIMM_REFRESH_ALL_FILE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_RefreshFileIndHandle
功能描述  :实现了读取文件的操作和结果的返回
输入参数  :API层下发消息内容
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增加函数

*****************************************************************************/
VOS_VOID USIMM_RefreshFileIndHandle(
    USIMM_STKREFRESH_REQ_STRU          *pstMsg,
    USIMM_CARDAPP_ENUM_UINT32           enAppType
)
{
    VOS_UINT32                          ulTempLen;
    VOS_UINT16                          usEfNum = 0;
    VOS_UINT16                          i;
    VOS_UINT16                          usOffset;
    USIMM_STKREFRESH_IND_STRU          *pstRefreshMsg;
    USIMM_FILEPATH_INFO_STRU           *pstFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    pstFilePath = (USIMM_FILEPATH_INFO_STRU*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, sizeof(USIMM_FILEPATH_INFO_STRU) * USIMM_MAX_REFRESH_FILE_NUM);

    if (VOS_NULL_PTR == pstFilePath)
    {
        USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: VOS_MemAlloc is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet(pstFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU) * USIMM_MAX_REFRESH_FILE_NUM);
    /*lint +e534*/

    for (usOffset = 0; usOffset < pstMsg->usLen; usOffset += (VOS_UINT16)ulTempLen)
    {
        /*获取当前EF的全路径内容*/
        if (VOS_OK != USIMM_GetEFPathFromFList(&pstMsg->aucFileList[usOffset],
                                               pstMsg->usLen - usOffset,
                                               &pstFilePath[usEfNum],
                                               &ulTempLen))
        {
            USIMM_WARNING_LOG("USIMM_RefreshFileIndHandle: Fail to Get File");

            break;
        }

        usEfNum++;

        /* 解析出来的文件数超过最大值时跳出循环 */
        if (USIMM_MAX_REFRESH_FILE_NUM <= usEfNum)
        {
            USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle:Refresh File too much");

            break;
        }
    }

    pstRefreshMsg = (USIMM_STKREFRESH_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                          (sizeof(USIMM_STKREFRESH_IND_STRU)-VOS_MSG_HEAD_LENGTH)\
                                                           + (usEfNum * sizeof(USIM_REFRESH_FILE_STRU)));

    if (VOS_NULL_PTR == pstRefreshMsg)
    {
        USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: VOS_AllocMsg is Failed");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstFilePath);
        /*lint +e534*/

        return;
    }

    pstRefreshMsg->stIndHdr.ulReceiverPid   = MAPS_PIH_PID;
    pstRefreshMsg->stIndHdr.enMsgName       = USIMM_STKREFRESH_IND;
    pstRefreshMsg->enRefreshType            = USIMM_GetRefreshIndType(pstMsg);
    pstRefreshMsg->usEfNum                  = usEfNum;

    for (i = 0; i < usEfNum; i++)
    {
        pstRefreshMsg->astEfId[i].enAppType = enAppType;

        /*减去结尾'/0'*/
        pstRefreshMsg->astEfId[i].usPathLen = (VOS_UINT16)(pstFilePath[i].ulPathLen-1);

        /*lint -e534*/
        VOS_MemCpy(pstRefreshMsg->astEfId[i].aucPath, pstFilePath[i].acPath, pstFilePath[i].ulPathLen);
        /*lint +e534*/

        if (VOS_OK != USIMM_ChangePathToDefFileID(enAppType, pstFilePath[i].ulPathLen, pstFilePath[i].acPath, &enFileID))
        {
            pstRefreshMsg->astEfId[i].usFileId = USIMM_DEF_FILEID_BUTT;
        }
        else
        {
            pstRefreshMsg->astEfId[i].usFileId = (VOS_UINT16)enFileID;
        }
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pstFilePath);
    /*lint +e534*/

    /* 处理ISIM文件更新上报 */
    USIMM_RefreshIsimFileIndHandle(pstRefreshMsg);

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstRefreshMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshInd
功能描述  :Refresh命令上报指示处理函数
输入参数  :pstMsg:Refresh消息
输出参数  :无
返 回 值  :
修订记录  :
1. 日    期   : 2013年5月28日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshInd(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_STKREFRESH_REQ_STRU          *pstMsg)
{
    /* REFRESH命令中指示文件更新 */
    if(pstMsg->usLen != VOS_NULL)
    {
        USIMM_RefreshFileIndHandle(pstMsg,enAppType);
    }
    else
    {
        USIMM_RefreshNoFileIndHandle(pstMsg);
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_SendRefreshTR
功能描述  : 实现了卡重启相关操作
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : 新增加函数
*****************************************************************************/
VOS_VOID USIMM_SendRefreshTR(
    USIMM_STKREFRESH_REQ_STRU          *pstMsg,
    VOS_UINT32                          ulResult
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;
    USIMM_SWCHECK_ENUM_UINT32           enResult;
    VOS_UINT8                           aucTR[] = {0x81,0x03,0x00,0x00,0x00,0x02,0x02,0x82,0x81,0x83,0x01,0x00};

    aucTR[2]  = (VOS_UINT8)pstMsg->ulCommandNum;
    aucTR[3]  = (VOS_UINT8)pstMsg->ulCommandType;
    aucTR[4]  = (VOS_UINT8)pstMsg->enRefreshType;
    aucTR[11] = (VOS_UINT8)ulResult;

    stApduHead.ucChannel    = 0x00;
    stApduHead.ucINS        = CMD_INS_TERMINAL_RESPONSE;
    stApduHead.ucP1         = 0x00;
    stApduHead.ucP2         = 0x00;
    stApduHead.ucP3         = (VOS_UINT8)sizeof(aucTR);

    stApduData.ulDataLen    = sizeof(aucTR);
    stApduData.pucData      = aucTR;

    enResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead, 
                                    &stApduData, 
                                    &stRspData);

    if (USIMM_SW_OK != enResult)
    {
        USIMM_ERROR_LOG("USIMM_SendRefreshTR: USIMM_SendAPDUHandle return Error");
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_RefreshCardFile
功能描述  : 实现了卡重启相关操作
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshCardFile(
    USIMM_STKREFRESH_REQ_STRU          *pstMsg,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_BOOL                            bUpdatePool)
{
    VOS_UINT32                          ulResult = 0;
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT32                          ulTempLen = 0;
    USIMM_GET_COMM_FILE_STRU            stFileInfo;
    USIMM_GETCNF_INFO_STRU              stCnfInfo;
    VOS_UINT16                          usEFID = 0;

    for(ulOffset=0; ulOffset<pstMsg->usLen; ulOffset += ulTempLen)
    {
        ulResult = USIMM_GetEFPathFromFList(&pstMsg->aucFileList[ulOffset],
                                            (pstMsg->usLen - ulOffset),
                                            &stFileInfo.stFilePath,
                                            &ulTempLen);

        if (VOS_OK != ulResult)
        {
            USIMM_WARNING_LOG("USIMM_RefreshCardFile: USIMM_GetEFPathFromFList Fail");

            return;
        }

        stFileInfo.enAppType    = enAppType;
        stFileInfo.ucRecordNum  = USIMM_READ_ALLRECORD;

        ulResult = USIMM_GetFileFromCard(&stFileInfo, &stCnfInfo);

        if (VOS_OK != ulResult)
        {
            USIMM_WARNING_LOG("USIMM_RefreshFileRead: USIMM_GetFileFromCard Fail");

            continue;
        }

        if (VOS_NULL_PTR != stCnfInfo.pucEf)
        {
            usEFID = USIMM_CCB_GetCurFileInfo(enAppType)->usCurEFID;

            if (VOS_TRUE == bUpdatePool)
            {
                ulResult = USIMM_PoolUpdateOneFile(enAppType, usEFID, stCnfInfo.usDataLen, stCnfInfo.pucEf);
            }

            /*lint -e534*/
            (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, stCnfInfo.pucEf);
            /*lint +e534*/

            stCnfInfo.pucEf = VOS_NULL_PTR;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_RefreshICCFile
功能描述  : 实现了卡重启相关操作
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_RefreshICCFile(USIMM_STKREFRESH_REQ_STRU       *pstMsg)
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_INITAPPSCTRL_STRU             stRefreshCtrl;

    if ((USIMM_APPLICATION_RESET_3G_ONLY     == pstMsg->enRefreshType)
        ||(USIMM_SESSION_RESET_3G_ONLY         == pstMsg->enRefreshType))
    {
        USIMM_SendRefreshTR(pstMsg, COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL);

        USIMM_WARNING_LOG("USIMM_RefreshICCFile: pstMsg->enRefreshType Error");

        return VOS_ERR;
    }

    enAppType = USIMM_CCB_GetMainAppType();

    if (USIMM_CARDAPP_BUTT == enAppType)
    {
        USIMM_SendRefreshTR(pstMsg, TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND);

        USIMM_WARNING_LOG("USIMM_RefreshICCFile: USIMM_CCB_GetMainAppType return Error");

        return VOS_ERR;
    }

    if (USIMM_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType)
    {
        USIMM_RefreshCardFile(pstMsg, enAppType, VOS_TRUE);

        USIMM_RefreshInd(enAppType, pstMsg);

        return VOS_OK;
    }

    /*lint -e534*/
    VOS_MemSet(&stRefreshCtrl, 0, sizeof(stRefreshCtrl));
    /*lint +e534*/

    stRefreshCtrl.enAppType         = enAppType;

    if (VOS_ERR == USIMM_GetAppInitList(enAppType, &stRefreshCtrl.pfList, &stRefreshCtrl.ucInitListNum))
    {
        USIMM_SendRefreshTR(pstMsg, TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND);

        return VOS_ERR;
    }

    (VOS_VOID)USIMM_PoolDelFilesByAppType(enAppType);

    if (USIMM_INITSTEPS_SUCCESS != USIMM_COMM_InitAppList(&stRefreshCtrl))
    {
        USIMM_WARNING_LOG("USIMM_RefreshICCFile: USIMM_COMM_InitAppList return Error");
    }

    if (VOS_NULL != pstMsg->usLen)
    {
        (VOS_VOID)USIMM_RefreshCardFile(pstMsg, enAppType, VOS_FALSE);
    }

    USIMM_RefreshInd(enAppType, pstMsg);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_RefreshUICCFile
功能描述  : 实现了卡重启相关操作
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_RefreshUICCFile(USIMM_STKREFRESH_REQ_STRU      *pstMsg)
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_INITAPPSCTRL_STRU             stRefreshCtrl;
    USIMM_AID_INFO_STRU                 *pstAIDInfo;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    VOS_UINT8                           ucChannelNo;

    enAppType = USIMM_CARDAPP_BUTT;

    if (pstMsg->ulAidLen != VOS_NULL)
    {
        enAppType = USIMM_GetAIDType(pstMsg->ulAidLen, pstMsg->aucAid);
    }

    if (USIMM_CARDAPP_BUTT == enAppType)
    {
        enAppType = USIMM_CCB_GetMainAppType();
    }

    if (USIMM_CARDAPP_BUTT == enAppType)
    {
        USIMM_SendRefreshTR(pstMsg, TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND);

        USIMM_WARNING_LOG("USIMM_RefreshUICCFile: enAppType Error");

        return VOS_ERR;
    }

    if (USIMM_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType)
    {
        USIMM_RefreshCardFile(pstMsg, enAppType, VOS_TRUE);

        USIMM_RefreshInd(enAppType, pstMsg);

        return VOS_OK;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_SendRefreshTR(pstMsg, TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND);

        USIMM_WARNING_LOG("USIMM_RefreshUICCFile: USIMM_CCB_GetAppChNO Error");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stRefreshCtrl, 0, sizeof(stRefreshCtrl));
    /*lint +e534*/

    stRefreshCtrl.enAppType         = enAppType;

    if (VOS_ERR == USIMM_GetAppInitList(enAppType, &stRefreshCtrl.pfList, &stRefreshCtrl.ucInitListNum))
    {
        USIMM_SendRefreshTR(pstMsg, TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND);

        return VOS_ERR;
    }

    if ((USIMM_APPLICATION_RESET_3G_ONLY    == pstMsg->enRefreshType)
        ||(USIMM_SESSION_RESET_3G_ONLY      == pstMsg->enRefreshType))
    {
        (VOS_VOID)USIMM_SendStatusApdu(ucChannelNo,
                                       USIMM_STATUS_TERMINATION_CURAPP,
                                       USIMM_STATUS_DF_NAME_RETURNED,
                                       VOS_NULL_BYTE);

        if (USIMM_APPLICATION_RESET_3G_ONLY == pstMsg->enRefreshType)
        {
            pstAIDInfo = USIMM_CCB_GetAIDByApp(enAppType);

            if (VOS_NULL_PTR != pstAIDInfo)
            {
                (VOS_VOID)USIMM_SelectAIDFile(ucChannelNo, 
                                            (((VOS_UINT8)USIMM_SELECT_TERMINATION_AID)|((VOS_UINT8)USIMM_SELECT_RETURN_FCP_TEMPLATE)), 
                                            pstAIDInfo, 
                                            &stApduRsp);
            }
        }
    }
    else
    {
        stRefreshCtrl.pfList[USIMM_ACTIVEADF_OFFSET].enStatus = USIMM_FUNC_UNAVAILABLE;
    }

    (VOS_VOID)USIMM_PoolDelFilesByAppType(enAppType);

    if (USIMM_INITSTEPS_SUCCESS != USIMM_COMM_InitAppList(&stRefreshCtrl))
    {
        USIMM_WARNING_LOG("USIMM_RefreshICCFile: USIMM_COMM_InitAppList return Error");
    }

    stRefreshCtrl.pfList[USIMM_ACTIVEADF_OFFSET].enStatus = USIMM_FUNC_AVAILABLE;

    if (VOS_NULL != pstMsg->usLen)
    {
        (VOS_VOID)USIMM_RefreshCardFile(pstMsg, enAppType, VOS_FALSE);
    }

    USIMM_RefreshInd(enAppType, pstMsg);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_RefreshNoReset
功能描述  : 实现了卡重启相关操作
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_RefreshNoReset(USIMM_STKREFRESH_REQ_STRU *pstMsg)
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32  enCardType;

    enCardType = USIMM_CCB_GetCardType();

    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        return USIMM_RefreshUICCFile(pstMsg);
    }
    else if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        return USIMM_RefreshICCFile(pstMsg);
    }
    else
    {
        return VOS_ERR;
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#else

#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "NVIM_Interface.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "usimminit.h"
#include "errorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_POOL_C
/*lint +e767*/

#define NV_FILE_OPEN_MODE_RW            "rb+"   /* open binary file for reading and writing */
#define NV_FILE_OPEN_MODE_NEW_RW        "wb+"   /* creat binary file for reading and writing*/

#define NV_FILE_SEEK_SET                0       /* the beginning of the file*/

/*****************************************************************************
函 数 名  :USIMM_PoolDataInit
功能描述  :初始化文件池的相关变量和状态　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/

VOS_VOID USIMM_PoolDataInit(VOS_VOID)
{
    gstUSIMMPOOL.enPoolStatus = USIMM_POOL_INITIALED;   /*更改全局变量内容*/

    gstUSIMMPOOL.ucNowLen     = 0x00;                  /*更改已存数据长度*/

    /*lint -e534*/
    VOS_MemSet(gstUSIMMPOOL.astpoolRecord, 0, sizeof(gstUSIMMPOOL.astpoolRecord));/*清空单元内容*/
    /*lint +e534*/
}

/*****************************************************************************
函 数 名  :USIMM_PoolFindFile
功能描述  :在文件池内找出文件所在的位置　
输入参数  :usFileId:文件ID
输出参数  :pucData:文件在文件池的位置
返 回 值  :VOS_ERR/VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolFindFile(
    VOS_UINT16                          usFileId,
    VOS_UINT32                         *pulData,
    USIMM_APP_TYPE_ENUM_UINT32          enAppType)
{
    VOS_UINT32 i;

    if(0 == gstUSIMMPOOL.ucNowLen)  /*当前内容为空*/
    {
        if(0 == usFileId)       /*查询空位置*/
        {
            *pulData = 0;

            return VOS_OK;
        }

        return VOS_ERR;
    }

    /*需要校验PIN码或PUK码时，只允许从文件池中读取不受PIN码保护的文件*/
    if ((gstUSIMMPOOL.enPoolStatus == USIMM_POOL_NEED_PASSWORD)&&(0 != usFileId))
    {
        if ((EFPL != usFileId)&&(EFICCID != usFileId)&&(EFLP != usFileId))
        {
            return VOS_ERR;
        }
    }

    for(i=0; i<POOLMAXNUM; i++)
    {
        /* 文件需要匹配文件ID和APP类型才算找到该文件，包括ATT、UMTS和GSM
        或者传入的APP类型为UNLIMIT APP，则不匹配APP类型只匹配文件ID
        如果文件ID为空，则为它找一个空闲的地方 */
        if (gstUSIMMPOOL.astpoolRecord[i].usFId == usFileId)
        {
            if ((gstUSIMMPOOL.astpoolRecord[i].enAppType == enAppType)
                || (USIMM_UNLIMIT_APP == enAppType)
                || (0 == usFileId))
            {
                /*返回文件所在单元号*/
                *pulData = i;

                return VOS_OK;
            }
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_PoolInsertOneFile
功能描述  :在文件池内填入一个文件的内容　
输入参数  :usFileId:文件ID
           usLen:文件数据长度
           pData:文件数据内容
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
调用函数  :USIMM_PoolFindFile
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolInsertOneFile(
    VOS_UINT16                          usFileId,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pData,
    USIMM_APP_TYPE_ENUM_UINT32          enAppType,
    USIMM_EF_TYPE_ENUM_UINT32           enFileType)
{
    VOS_UINT32  ulRecordNum;
    VOS_UINT32  ulResult;

    if((USIMM_POOL_NOINTIAL == gstUSIMMPOOL.enPoolStatus)
        ||(POOLMAXNUM == gstUSIMMPOOL.ucNowLen))   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_PoolInsertOneFile: Warning: Parameter is wrong");/*打印错误*/

        return VOS_ERR;
    }

    ulResult = USIMM_PoolFindFile(0, &ulRecordNum, enAppType);/*查询空位置*/

    if(VOS_ERR == ulResult)/*当前文件池以满*/
    {
        USIMM_WARNING_LOG("USIMM_PoolInsertOneFile: Warning: File Could not Found");/*打印错误*/

        return VOS_ERR;
    }

    gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,
                                                                    STATIC_MEM_PT,  usLen);/*分配数据存储空间*/

    if(VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_WARNING_LOG("USIMM_PoolInsertOneFile: Warning: VOS_MemAlloc is Error");/*打印错误*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent, pData, usLen);/*保存数据内容*/
    /*lint +e534*/

    gstUSIMMPOOL.astpoolRecord[ulRecordNum].usFId       =   usFileId;   /* 记录文件ID */
    gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen       =   usLen;      /* 记录文件长度 */
    gstUSIMMPOOL.astpoolRecord[ulRecordNum].enAppType   =   enAppType;  /* 记录应用类型 */
    gstUSIMMPOOL.astpoolRecord[ulRecordNum].enFileType  =   enFileType; /* 记录文件类型 */

    gstUSIMMPOOL.ucNowLen++;/*保存记数器累计*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolDelOneFile
功能描述  :从文件池内删除一个文件的内容　
输入参数  :usFileId:文件ID
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
调用函数  :USIMM_PoolFindFile
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolDelOneFile(VOS_UINT16 usFileId, USIMM_APP_TYPE_ENUM_UINT32 enAppType)
{
    VOS_UINT32  ulRecordNum;

    if((USIMM_POOL_NOINTIAL == gstUSIMMPOOL.enPoolStatus)
        ||(0 == gstUSIMMPOOL.ucNowLen)||(0 == usFileId))   /*状态检查*/
    {
        USIMM_ERROR_LOG("USIMM_PoolDelOneFile: Wrong State or Parameter");/*打印错误*/

        return VOS_ERR;
    }

    if(VOS_ERR == USIMM_PoolFindFile(usFileId, &ulRecordNum, enAppType))/*查询文件位置*/
    {
        USIMM_WARNING_LOG("USIMM_PoolDelOneFile: File Could Not Found");/*打印错误*/

        return VOS_ERR;
    }

    if(VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_ERROR_LOG("USIMM_PoolDelOneFile: File Content is Empty");/*打印错误*/

        return VOS_ERR;
    }

    /* 释放存储空间并将指针清空 */
    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent);
    /*lint +e534*/

    gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent  = VOS_NULL_PTR;

    gstUSIMMPOOL.astpoolRecord[ulRecordNum].usFId       = 0;/*文件ID标记为空*/

    gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen       = 0;/*长度清空*/

    gstUSIMMPOOL.ucNowLen--;/*记数器减一*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolReadOneFile
功能描述  :从文件池内读取一个文件的内容和长度　
输入参数  :usFileId:文件ID
输出参数  :pLen:文件数据长度
           pData:文件数据内容
返 回 值  :VOS_ERR/VOS_OK
调用函数  :USIMM_PoolFindFile
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PoolReadOneFile(
    VOS_UINT16                          usFileId,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucData,
    USIMM_APP_TYPE_ENUM_UINT32          enAppType)
{
    VOS_UINT32  ulRecordNum;
    VOS_UINT32  ulResult;
    VOS_UINT32  ulDataLen;

    if((USIMM_POOL_NOINTIAL == gstUSIMMPOOL.enPoolStatus)
        ||(0 == gstUSIMMPOOL.ucNowLen)||(0 == usFileId))   /*状态检查*/
    {
        USIMM_WARNING_LOG("USIMM_PoolReadOneFile: Parameter wrong");/*打印错误*/

        return VOS_ERR;
    }

    ulResult = USIMM_PoolFindFile(usFileId, &ulRecordNum, enAppType);/*查询文件位置*/

    if(VOS_ERR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_PoolReadOneFile: File Could not Found");/*打印错误*/

        return VOS_ERR;
    }

    if(VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_ERROR_LOG("USIMM_PoolReadOneFile: File Content is Empty");/*打印错误*/

        return VOS_ERR;
    }

    if(usLen == USIMM_READ_ALL_FILE_CONTENT)
    {
        ulDataLen = gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen;
    }
    else if(usLen < gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen)
    {
        ulDataLen = usLen;
    }
    else
    {
        ulDataLen = gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen;
    }

    /*lint -e534*/
    VOS_MemCpy(pucData,gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent,ulDataLen);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PoolDelAll
功能描述  :从文件池内读取一个文件的内容和长度　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2009年8月9日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_PoolDelAll(VOS_VOID)
{
    VOS_UINT32 i;

    for(i=0; i<POOLMAXNUM;i++)
    {
        if(gstUSIMMPOOL.astpoolRecord[i].pucContent != VOS_NULL_PTR)/*找到该文件*/
        {
            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_USIM, gstUSIMMPOOL.astpoolRecord[i].pucContent);
            /*lint +e534*/
        }
    }

    USIMM_PoolDataInit();

    return;
}

/*****************************************************************************
函 数 名  :USIMM_PoolUpdateOneFile
功能描述  :更新文件池中一个文件内容，不改变其长度
输入参数  :VOS_UINT16                   usFileId  文件ID
           USIMM_APP_TYPE_ENUM_UINT32   enAppType 应用类型
           VOS_UINT32                   ulDataLen 数据长度
           VOS_CHAR                    *pucData   数据内容

输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2012年6月29日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_PoolUpdateOneFile(
    VOS_UINT16                          usFileId,
    USIMM_APP_TYPE_ENUM_UINT32          enAppType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulFileNum;
    VOS_UINT32                          ulUpdateLen;

    if (VOS_OK != USIMM_PoolFindFile(usFileId, &ulFileNum, enAppType))
    {
        USIMM_WARNING_LOG("USIMM_PoolUpdateOneFile: File Could not Found");/*打印错误*/

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent)
    {
        USIMM_WARNING_LOG("USIMM_PoolUpdateOneFile: File in Pool is Null");/*打印错误*/

        return VOS_ERR;
    }

    ulUpdateLen =   ((ulDataLen > gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen)?\
                    gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen:ulDataLen);

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent, pucData, ulUpdateLen);
    /*lint +e534*/

    return VOS_OK;
}



/*****************************************************************************
函 数 名  :USIMM_InsertFileToPool
功能描述  :
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
 修订记录 :
1. 日    期   : 2007年8月20日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_InsertFileToPool(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFileID)
{
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usDataLen;
    VOS_UINT16                          ausPathGDF[4]={MF,ADF,0x5F3B,0x4F00};
    VOS_UINT16                          ausPathMF[2]={MF, 0x2F00};
    VOS_UINT16                          ausPathGSM[3]={MF, DFGSM, 0x6F00};
    VOS_UINT16                          ausPathADF[3]={MF, ADF, 0x6F00};
    VOS_UINT16                         *pusPath;
    VOS_UINT32                          ulPathLen;

    if(0x4F00 == (usFileID&0xFF00))
    {
        ausPathGDF[3]   = usFileID;
        pusPath         = ausPathGDF;
        ulPathLen       = ARRAYSIZE(ausPathGDF);
    }
    else if(0x2F00 == (usFileID&0xFF00))
    {
        ausPathMF[1]    = usFileID;
        pusPath         = ausPathMF;
        ulPathLen       = ARRAYSIZE(ausPathMF);
    }
    else
    {
        if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            ausPathADF[2]   = usFileID;
            pusPath         = ausPathADF;
            ulPathLen       = ARRAYSIZE(ausPathADF);
        }
        else
        {
            ausPathGSM[2]   = usFileID;
            pusPath         = ausPathGSM;
            ulPathLen       = ARRAYSIZE(ausPathGSM);
        }
    }

    ulResult = USIMM_SelectFile(enAppType, USIMM_NEED_FCP, ulPathLen, pusPath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_WARNING_LOG("USIMM_InsertFileToPool:Select File Failed");

        return VOS_ERR;
    }

    if(gstUSIMMCurFileInfo.stEFInfo.usFileLen>USIMM_MAX_FILE_SIZE)
    {
        usDataLen = USIMM_MAX_FILE_SIZE;
    }
    else
    {
        usDataLen = gstUSIMMCurFileInfo.stEFInfo.usFileLen;
    }

    pucData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, usDataLen);

    if(VOS_NULL_PTR == pucData)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_InsertFileToPool: VOS_MemAlloc Error");

        return VOS_ERR;
    }

    ulResult = USIMM_ReadTFFile(usDataLen, pucData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_InsertFileToPool: USIMM_ReadTFFile Error");

        return VOS_ERR;
    }

    if(VOS_OK != USIMM_PoolInsertOneFile(usFileID,
                                         usDataLen,
                                         pucData,
                                         enAppType,
                                         USIMM_EFSTRUCTURE_TRANSPARENT))
    {
        USIMM_ERROR_LOG("USIMM_InsertFileToPool: USIMM_PoolInsertOneFile Error");

        g_stUSIMMInitInfo.ucInsertPoolFailFlag = VOS_TRUE;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucData);
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucData);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_LogDataSave
功能描述  :保存数据到log缓冲区，TLV结构保存
输入参数  :pucData 需要保存的数据
           ucDataLen 保存数据长度
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_LogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen)
{
    if((USIMM_NO_NEED_LOG == g_stUSIMMLogData.enLogState)   /*当前不需要记录log*/
        ||((g_stUSIMMLogData.ulDataLen + 2 + ucDataLen) > USIMM_LOG_DATA_MAX_LEN)/*记录的log数据超过最大值,还需要计算tag和len的2个字节*/
        ||(VOS_NULL_PTR == g_stUSIMMLogData.pucData))       /*当前log缓冲区不存在*/
    {
        return;
    }

    g_stUSIMMLogData.pucData[g_stUSIMMLogData.ulDataLen] = USIMM_LOG_DATA_TAG;  /*记录log*/

    g_stUSIMMLogData.ulDataLen ++;              /*长度+1*/

    g_stUSIMMLogData.pucData[g_stUSIMMLogData.ulDataLen] = ucDataLen;   /*记录数据长度*/

    g_stUSIMMLogData.ulDataLen ++;              /*长度+1*/

    /*lint -e534*/
    VOS_MemCpy(&(g_stUSIMMLogData.pucData[g_stUSIMMLogData.ulDataLen]), pucData, ucDataLen);
    /*lint +e534*/

    g_stUSIMMLogData.ulDataLen += ucDataLen;    /*长度+数据长度*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_LogDataClear
功能描述  :清空log缓冲区的内容　并且关闭记录功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_LogDataClear(VOS_VOID)
{
    /*lint -e534*/
    VOS_CacheMemFree(g_stUSIMMLogData.pucData);
    /*lint +e534*/

    g_stUSIMMLogData.ulDataLen = 0;

    g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SaveLogFile
功能描述  :写入log文件的内容　，写入无论成功与否都关闭记录log功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SaveLogFile(VOS_VOID)
{
    FILE                               *ctrlfp;
    FILE                               *logfp;
    USIMM_LOG_CTRLFILE_STRU             stCtrlData;
    VOS_CHAR                            aucLogPath[100] = {0};
    VOS_CHAR                            aucLogCtrlFile[USIMM_FILE_PATH_MAX_LEN] = {0};
    VOS_CHAR                            aucUniteryLogPath[USIMM_FILE_PATH_MAX_LEN] = {0};

    /*当前是否有保存数据*/
    if((VOS_NULL_PTR == g_stUSIMMLogData.pucData)||(0 == g_stUSIMMLogData.ulDataLen))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucLogCtrlFile, USIMM_LOGCTRL_FILE, USIMM_UNITARY_LOGCTRL_FILE))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucUniteryLogPath, USIMM_LOG_PATH, USIMM_UNITARY_LOG_PATH))
    {
        return;
    }

    /*打开控制文件*/
    ctrlfp = mdrv_file_open(aucLogCtrlFile, NV_FILE_OPEN_MODE_RW);

    if(VOS_NULL_PTR == ctrlfp)
    {
        USIMM_LogDataClear();
        return;
    }

    /*读取控制文件*/
    if(sizeof(USIMM_LOG_CTRLFILE_STRU) != mdrv_file_read((VOS_CHAR*)&stCtrlData,
                                                    sizeof(VOS_CHAR),
                                                    sizeof(USIMM_LOG_CTRLFILE_STRU),
                                                    ctrlfp))
    {
        USIMM_LogDataClear();
        /*lint -e534*/
        mdrv_file_close(ctrlfp);
        /*lint +e534*/
        return;
    }

    if(stCtrlData.ulCurFile >= USIMM_LOG_FILE_MAX_NUM)
    {
        USIMM_LogDataClear();
        /*lint -e534*/
        mdrv_file_close(ctrlfp);
        mdrv_file_remove(aucLogCtrlFile);
        /*lint +e534*/
        return;
    }

    /* 拼接LOG文件路径 */
    /*lint -e534*/
    VOS_sprintf(aucLogPath, "%s/%s", aucUniteryLogPath, stCtrlData.aucFileName[stCtrlData.ulCurFile]);
    /*lint +e534*/

    /*打开log文件，如果存在需要清空*/
    logfp = mdrv_file_open(aucLogPath, NV_FILE_OPEN_MODE_NEW_RW);

    if(VOS_NULL_PTR == logfp)
    {
        USIMM_LogDataClear();
        return;
    }

    /*写入数据*/
    /*lint -e534*/
    mdrv_file_write((VOS_CHAR*)g_stUSIMMLogData.pucData, sizeof(VOS_CHAR), g_stUSIMMLogData.ulDataLen, logfp);

    mdrv_file_close(logfp);
    /*lint +e534*/

    /*清空数据*/
    USIMM_LogDataClear();

    /*计算下次写入的文件号*/
    stCtrlData.ulCurFile = ((stCtrlData.ulCurFile + 1) % USIMM_LOG_FILE_MAX_NUM);

    /*写入下次更新的文件号*/
    /*lint -e534*/
    (VOS_VOID)mdrv_file_seek(ctrlfp, 0, NV_FILE_SEEK_SET);

    (VOS_VOID)mdrv_file_write((VOS_CHAR*)&stCtrlData.ulCurFile, sizeof(VOS_CHAR), sizeof(VOS_UINT32), ctrlfp);

    (VOS_VOID)mdrv_file_close(ctrlfp);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitLogFile
功能描述  :初始化log文件的内容　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitLogFile(VOS_VOID)
{
    VOS_CHAR                            aucLogFile[USIMM_LOG_FILE_NAME_LEN] = {0};
    VOS_UINT32                          i;
    VOS_UINT32                          ulStartFlag = USIMM_LOG_START_TAG;
    USIMM_LOG_CTRLFILE_STRU             stCtrlData;
    FILE                               *fp;
    VOS_CHAR                            aucLogCtrlFile[USIMM_FILE_PATH_MAX_LEN] = {0};
    VOS_CHAR                            aucLogPath[USIMM_FILE_PATH_MAX_LEN] = {0};
    VOS_UINT8                           ucLogFilterFlag;

    if (VOS_OK != OM_GetLogPath(aucLogPath, USIMM_LOG_PATH, USIMM_UNITARY_LOG_PATH))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucLogCtrlFile, USIMM_LOGCTRL_FILE, USIMM_UNITARY_LOGCTRL_FILE))
    {
        return;
    }

    (VOS_VOID)VOS_MemSet(&g_stUSIMMLogData, 0, sizeof(g_stUSIMMLogData));
    (VOS_VOID)VOS_MemSet(&stCtrlData, 0, sizeof(stCtrlData));

    if (NV_OK != NV_ReadPartEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                           0,
                          &ucLogFilterFlag,
                           sizeof(VOS_UINT8)))
    {
        ucLogFilterFlag = VOS_FALSE;
    }

    if (VOS_TRUE == ucLogFilterFlag)
    {
        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }
    else
    {
        g_stUSIMMLogData.enLogState = USIMM_NEED_LOG;
    }

    g_stUSIMMLogData.pucData = (VOS_UINT8*)VOS_CacheMemAlloc(USIMM_LOG_DATA_MAX_LEN);

    if(VOS_NULL_PTR == g_stUSIMMLogData.pucData)
    {
        /*lint -e534*/
        LogPrint("\r\n USIMM_InitLogFile: malloc log buffer Error");
        /*lint +e534*/

        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }

    /*先记录一个开始标记，表示开始初始化流程*/
    USIMM_LogDataSave((VOS_UINT8*)&ulStartFlag, sizeof(VOS_UINT32));

    fp = mdrv_file_open(aucLogCtrlFile, NV_FILE_OPEN_MODE_RW);

    if(VOS_NULL_PTR != fp)  /*文件存在不需要创建*/
    {
        /*lint -e534*/
        mdrv_file_close(fp);
        /*lint +e534*/

        return;
    }

    if (MDRV_ERROR == mdrv_file_mkdir(aucLogPath))
    {
        /*lint -e534*/
        LogPrint("\r\n USIMM_InitLogFile: Mk Dir Error");
        /*lint +e534*/
    }

    fp = mdrv_file_open(aucLogCtrlFile, NV_FILE_OPEN_MODE_NEW_RW);  /*创建文件*/

    if(VOS_NULL_PTR == fp)
    {
        /*lint -e534*/
        LogPrint("\r\n USIMM_InitLogFile: Creat Log Ctrl File Error");

        VOS_CacheMemFree(g_stUSIMMLogData.pucData);
        /*lint +e534*/

        g_stUSIMMLogData.pucData = VOS_NULL_PTR;

        return;
    }

    for(i=0; i<USIMM_LOG_FILE_MAX_NUM; i++)
    {
        /* 拼接LOG文件名称 */
        /*lint -e534*/
        VOS_sprintf(aucLogFile, "%s_%d", "UsimmInitLog", i);

        VOS_StrNCpy(stCtrlData.aucFileName[i], aucLogFile, USIMM_LOG_FILE_NAME_LEN);
        /*lint +e534*/
    }

    stCtrlData.ulCurFile = 0;

    /*lint -e534*/
    mdrv_file_write((VOS_CHAR*)&stCtrlData, sizeof(VOS_CHAR), sizeof(USIMM_LOG_CTRLFILE_STRU), fp);

    mdrv_file_close(fp);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_LogDataClear
功能描述  :清空log缓冲区的内容　并且关闭记录功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataClear(VOS_VOID)
{
    /*lint -e534*/
    VOS_CacheMemFree(g_stUSIMMExcLogData.pucData);
    /*lint +e534*/

    g_stUSIMMExcLogData.pucData = VOS_NULL_PTR;

    g_stUSIMMExcLogData.ulDataLen = 0;

    g_stUSIMMExcLogData.enLogState = USIMM_NO_NEED_LOG;

    g_ulUSIMMExcLogLenBK = 0;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SaveLogFile
功能描述  :写入log文件的内容　，写入无论成功与否都关闭记录log功能
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SaveExcLogFile(VOS_VOID)
{
    FILE                               *logfp;
    VOS_CHAR                            aucLogPathFile[100] = {0};
    VOS_CHAR                            aucLogPath[USIMM_FILE_PATH_MAX_LEN] = {0};

    /*当前是否有保存数据*/
    if((VOS_NULL_PTR == g_stUSIMMExcLogData.pucData)||(0 == g_stUSIMMExcLogData.ulDataLen))
    {
        return;
    }

    if (VOS_OK != OM_GetLogPath(aucLogPath, USIMM_LOG_PATH, USIMM_UNITARY_LOG_PATH))
    {
        return;
    }

    /* 拼接LOG文件路径 */
    /*lint -e534*/
    VOS_sprintf(aucLogPathFile, "%s/%s", aucLogPath, "USIMMExcFile.bin");
    /*lint +e534*/

    /*打开log文件，如果存在需要清空*/
    logfp = mdrv_file_open(aucLogPathFile, NV_FILE_OPEN_MODE_NEW_RW);

    if(VOS_NULL_PTR == logfp)
    {
        USIMM_ExcLogDataClear();
        return;
    }

    /*写入数据*/
    /*lint -e534*/
    mdrv_file_write((VOS_CHAR*)g_stUSIMMExcLogData.pucData, sizeof(VOS_CHAR), g_stUSIMMExcLogData.ulDataLen, logfp);

    mdrv_file_close(logfp);
    /*lint +e534*/

    /*清空数据*/
    USIMM_ExcLogDataClear();

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ExcLogDataBK
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataBK(VOS_VOID)
{
    g_ulUSIMMExcLogLenBK = g_stUSIMMExcLogData.ulDataLen;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ExcLogDataBK
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataRE(VOS_VOID)
{
    g_stUSIMMExcLogData.ulDataLen = g_ulUSIMMExcLogLenBK ;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ExcLogDataSave
功能描述  :保存数据到log缓冲区，TLV结构保存
输入参数  :pucData 需要保存的数据
           ucDataLen 保存数据长度
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ExcLogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen)
{
    VOS_UINT32      ulSlice;

    if((USIMM_NO_NEED_LOG == g_stUSIMMExcLogData.enLogState)   /*当前不需要记录log*/
        ||((g_stUSIMMExcLogData.ulDataLen + 6 + ucDataLen) > USIMM_EXCLOG_DATA_MAX_LEN)/*记录的log数据超过最大值,还需要计算tag和len的2个字节和时间戳4字节*/
        ||(VOS_NULL_PTR == g_stUSIMMExcLogData.pucData))       /*当前log缓冲区不存在*/
    {
        return;
    }

    g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen] = USIMM_LOG_DATA_TAG;  /*记录log*/

    g_stUSIMMExcLogData.ulDataLen ++;              /*长度+1*/

    ulSlice = OM_GetSlice();

    /*lint -e534*/
    VOS_MemCpy(&(g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen]), &ulSlice, sizeof(ulSlice));
    /*lint +e534*/

    g_stUSIMMExcLogData.ulDataLen += sizeof(ulSlice);              /*长度+1*/

    g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen] = ucDataLen;   /*记录数据长度*/

    g_stUSIMMExcLogData.ulDataLen ++;              /*长度+1*/

    /*lint -e534*/
    VOS_MemCpy(&(g_stUSIMMExcLogData.pucData[g_stUSIMMExcLogData.ulDataLen]), pucData, ucDataLen);
    /*lint +e534*/

    g_stUSIMMExcLogData.ulDataLen += ucDataLen;    /*长度+数据长度*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitExcLogFile
功能描述  :初始化log文件的内容　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitExcLogFile(VOS_VOID)
{
    VOS_UINT8                              ucLogFilterFlag; 

    g_stUSIMMExcLogData.ulDataLen  = 0;

    g_stUSIMMExcLogData.pucData    = VOS_NULL_PTR;

    g_ulUSIMMExcLogLenBK = 0;

    if (NV_OK != NV_ReadPartEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                           0,
                          &ucLogFilterFlag,
                           sizeof(VOS_UINT8)))
    {
        ucLogFilterFlag = VOS_FALSE;
    }

    if (VOS_TRUE == ucLogFilterFlag)
    {
        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }
    else
    {
        g_stUSIMMLogData.enLogState = USIMM_NEED_LOG;
    }

    g_stUSIMMExcLogData.pucData = (VOS_UINT8*)VOS_CacheMemAlloc(USIMM_EXCLOG_DATA_MAX_LEN);

    if(VOS_NULL_PTR == g_stUSIMMExcLogData.pucData)
    {
        /*lint -e534*/
        LogPrint("\r\n USIMM_InitLogFile: malloc log buffer Error");
        /*lint +e534*/

        g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;

        return;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitGlobalVarOnPower
功能描述  :初始化全局变量，这些全局变量只要上电后初始化一次即可　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2013年6月19日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitGlobalVarOnPower(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&gstUSIMMADFInfo, 0, sizeof(gstUSIMMADFInfo));
    /*lint +e534*/

    USIMM_FeatureGlobalInit();

    /*lint -e534*/
    VOS_MemSet(&g_stUSIMMInitInfo, 0, sizeof(g_stUSIMMInitInfo));
    /*lint +e534*/

    USIMM_PoolDataInit();

    /*lint -e534*/
    VOS_MemSet(&g_stT1StatisticInfo, 0, sizeof(g_stT1StatisticInfo));

    VOS_MemSet(&g_stUSIMMT1Para, 0, sizeof(g_stUSIMMT1Para));
    /*lint +e534*/

    g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

#if(FEATURE_ON == FEATURE_PTM)
    /*lint -e534*/
    VOS_MemSet(&g_stCardErrorLog, 0, sizeof(g_stCardErrorLog));
    /*lint +e534*/

    if (VOS_OK != NV_Read(en_NV_Item_ErrLogCtrlInfo, &g_stErrLogCtrlInfo, sizeof(g_stErrLogCtrlInfo)))
    {
        /* Error Log上报控制NV项,如读失败还原初始化nv项 */
        /*lint -e534*/
        VOS_MemSet(&g_stErrLogCtrlInfo, 0, sizeof(g_stErrLogCtrlInfo));
        /*lint +e534*/
    }

#endif

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitGlobalVarOnReset
功能描述  :初始化相关全局变量的内容,这些全局变量只要重新初始化就要clear　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitGlobalVarOnReset(VOS_VOID)
{
    VOS_UINT32                          i;

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMAPDU,       0, sizeof(gstUSIMMAPDU));

    VOS_MemSet(&gstUSIMMBaseInfo,    0, sizeof(gstUSIMMBaseInfo));

    VOS_MemSet(&gstUSIMMCurFileInfo, 0, sizeof(gstUSIMMCurFileInfo));

    VOS_MemSet(&gstUSIMMDLControl,   0, sizeof(gstUSIMMDLControl));

    VOS_MemSet(&gstUSIMMDrvInfo,     0, sizeof(gstUSIMMDrvInfo));

    VOS_MemSet(g_stUSIMMCardFileMap, 0, sizeof(g_stUSIMMCardFileMap));

    VOS_MemSet(g_astUSIMMChCtrl, 0, sizeof(g_astUSIMMChCtrl));

    VOS_MemSet(g_astUSIMMChAIDFCP, 0, sizeof(g_astUSIMMChAIDFCP));

    VOS_MemSet(g_astAidInfo, 0, sizeof(g_astAidInfo));
    /*lint +e534*/

    USIMM_PoolDelAll();

    g_ulATTSpecErrSWCnt = 0;

    for(i = 0; i < USIMM_UICC_BUTT; i++)
    {
        gastUSIMMCardAppInfo[i].enCardType = USIMM_CARD_NOCARD;
        gastUSIMMCardAppInfo[i].enCardService = USIMM_CARD_SERVIC_ABSENT;
    }

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange = USIMM_CARD_STATE_CHANGED;

    gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enStateChange = USIMM_CARD_STATE_NOCHANGE;

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enStateChange = USIMM_CARD_STATE_NOCHANGE;
#endif

    /* ISIM相关变量初始化 */
    gulUsimSupportIMS                       = VOS_FALSE;

    USIMM_T1InitGlobalVar();

    /*lint -e534*/
    VOS_MemSet(&g_stUSIMMCardVersionType, VOS_NULL, sizeof(g_stUSIMMCardVersionType));
    /*lint +e534*/

    g_ulCsimSessionId = VOS_NULL_DWORD;

    g_bCacheEFIccidData = VOS_FALSE;
    (VOS_VOID)VOS_MemSet(g_aucEFIccidData, 0, sizeof(g_aucEFIccidData));

    return;
}

/*****************************************************************************
函 数 名  :USIMM_AttGlobalInit
功能描述  :初始化ATT相关全局变量的内容　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2012年6月18日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_FeatureGlobalInit(VOS_VOID)
{
    /* NV项读取失败按所有定制都不支持处理 */
    if(VOS_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config,
                         (VOS_VOID*)&g_stUsimmFeatureCfg, sizeof(g_stUsimmFeatureCfg)))
    {
        /*lint -e534*/
        VOS_MemSet(g_stUsimmFeatureCfg.unCfg.aulValue , VOS_FALSE, sizeof(g_stUsimmFeatureCfg.unCfg.aulValue));
        /*lint +e534*/
    }

    return;
}


/*****************************************************************************
函 数 名  : USIMM_ClearCurDFInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearCurDFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo)
{
    pstCurFileInfo->usCurDFID       = USIMM_NULL_ID;

    pstCurFileInfo->usCurDFFcpLen   = 0;

    /*lint -e534*/
    VOS_MemSet(&(pstCurFileInfo->stDFInfo), 0, sizeof(USIMM_DFFCP_ST));
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : USIMM_ClearCurEFInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearCurEFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo)
{
    pstCurFileInfo->usCurEFID       = USIMM_NULL_ID;

    /*lint -e534*/
    VOS_MemSet(&(pstCurFileInfo->stEFInfo), 0, sizeof(USIMM_EFFCP_ST));
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : USIMM_ClearCurFileInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_ClearCurFileInfo(VOS_VOID)
{
    gstUSIMMCurFileInfo.usFilePathLen  = 0;

    /*lint -e534*/
    VOS_MemSet(gstUSIMMCurFileInfo.ausFilePath, 0, sizeof(gstUSIMMCurFileInfo.ausFilePath));
    /*lint +e534*/

    USIMM_ClearCurDFInfo(&gstUSIMMCurFileInfo);

    USIMM_ClearCurEFInfo(&gstUSIMMCurFileInfo);

    return;
}

/*****************************************************************************
函 数 名  : USIMM_SaveDFPinInfo
功能描述  :
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_SaveDFPinInfo(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMADFInfo.stPINInfo, &gstUSIMMCurFileInfo.stDFInfo.stPINInfo, sizeof(USIMM_PIN_INFO_STRU));
    /*lint +e534*/

    gstUSIMMADFInfo.ucPIN1RefNum = gstUSIMMCurFileInfo.stDFInfo.ucPIN1RefNum;

    gstUSIMMADFInfo.ucPIN2RefNum = gstUSIMMCurFileInfo.stDFInfo.ucPIN2RefNum;

    return;
}

/*****************************************************************************
函 数 名  : USIMM_GetDFFcpLenInMap
功能描述  : 在文件树中搜索当前DF的FCP长度
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetDFFcpLenInMap(VOS_UINT16 usDFId, VOS_UINT32 *pulFcpLen)
{
    VOS_UINT32 i;

    for(i=0; i<ARRAYSIZE(g_stUSIMMCardFileMap); i++)
    {
        if(g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.usDfID == usDFId)
        {
            *pulFcpLen = g_stUSIMMCardFileMap[i].stDFFileMap.ulDfFcpLen;

            return VOS_OK;
        }

        if(g_stUSIMMCardFileMap[i].stGDFFileMap.stFileCont.usDfID == usDFId)
        {
            *pulFcpLen = g_stUSIMMCardFileMap[i].stGDFFileMap.ulDfFcpLen;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateFileByRelativePath
功能描述  :根据相对路径更新文件信息
输入参数  :pstSelectPara:      选择文件参数
           pstFilePath:        相对路径
           pstUSIMMCurFileInfo:当前文件信息
输出参数  :无
返 回 值  :无
调用函数  :无
 修订记录  :
1. 日    期    : 2013年6月28日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_UpdateFileByRelativePath(USIMM_SELECT_PARA_STUR *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU    *pstFilePath,
                                            USIMM_CURFILEINFO_ST     *pstUSIMMCurFileInfo)
{
    VOS_UINT32                          ulMaxLen;
    VOS_UINT16                          ausFileAllPath[USIMM_MAX_PATH_LEN] = {0};
    USIMM_U16_LVDATA_STRU               stFileAllPath;
    VOS_UINT32                          ulTempLen;

    if (0 == pstFilePath->ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_UpdateFileByRelativePath: The Data Path is empty.");

        return;
    }

    /* 根据路径的首目录获得全路径长度 */
    switch(USIMM_FILE_TYPE(pstFilePath->pusData[0]))
    {
        case EFUNDERMF:
            ulMaxLen  = 1;
            ulTempLen = 2;
            break;

        case MFTAG:
            ulMaxLen  = 4;
            ulTempLen = pstFilePath->ulDataLen;
            break;

        case EFUNDERGRANDADF:
            ulMaxLen  = 1;
            ulTempLen = 4;
            break;

        case DFUNDERDF:
            ulMaxLen  = 2;
            ulTempLen = pstFilePath->ulDataLen + 2;
            break;

        case EFUNDERDF:
            ulMaxLen  = 1;
            ulTempLen = pstFilePath->ulDataLen + 2;
            break;

        case DFUNDERMF:
            ulMaxLen  = 3;
            ulTempLen = pstFilePath->ulDataLen + 1;
            break;

        default:
            return;
    }

    if (ulMaxLen < pstFilePath->ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_UpdateFileByRelativePath: The File Path is Too Long");

        return;
    }

    /* 计算从当前路径需要获得的路径长度 */
    ulTempLen -= pstFilePath->ulDataLen;

    /*lint -e534*/
    VOS_MemCpy(ausFileAllPath, pstUSIMMCurFileInfo->ausFilePath, ulTempLen*sizeof(VOS_UINT16));
    VOS_MemCpy(&ausFileAllPath[ulTempLen], pstFilePath->pusData, pstFilePath->ulDataLen*sizeof(VOS_UINT16));
    /*lint +e534*/

    stFileAllPath.ulDataLen = ulTempLen + pstFilePath->ulDataLen;
    stFileAllPath.pusData   = ausFileAllPath;

    USIMM_UpdateFilePath(pstSelectPara, &stFileAllPath, pstUSIMMCurFileInfo);
}

/*****************************************************************************
函 数 名  :USIMM_UpdateFilePath
功能描述  :
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
           enUpdateFlag:更新文件FCP标识
输出参数  :无
返 回 值  :无
调用函数  :无
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年4月29日
   作    者   : j00168360
   修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
*****************************************************************************/
VOS_VOID USIMM_UpdateFilePath(USIMM_SELECT_PARA_STUR      *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU       *pstFilePath,
                                        USIMM_CURFILEINFO_ST        *pstUSIMMCurFileInfo)
{
    VOS_UINT16                          usFileId;
    VOS_UINT32                          ulDFFcpLen;

    if (0 == pstFilePath->ulDataLen)
    {
        return;
    }

    USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Need Update the File Info");

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMCurFileInfo->ausFilePath, pstFilePath->pusData, (pstFilePath->ulDataLen)*sizeof(VOS_UINT16));
    /*lint +e534*/

    pstUSIMMCurFileInfo->usFilePathLen = (VOS_UINT16)pstFilePath->ulDataLen;

    usFileId = pstUSIMMCurFileInfo->ausFilePath[pstFilePath->ulDataLen - 1];

    /* 判断是否为EF文件路径 */
    if (USIMM_IS_EF_FILE(usFileId))
    {
        pstUSIMMCurFileInfo->usCurEFID = usFileId;

        pstUSIMMCurFileInfo->usCurDFID = pstUSIMMCurFileInfo->ausFilePath[pstFilePath->ulDataLen - 2];;

        USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Update the EF File Info");
    }
    else
    {
        pstUSIMMCurFileInfo->usCurEFID = USIMM_NULL_ID;

        pstUSIMMCurFileInfo->usCurDFID = usFileId;

        /*lint -e534*/
        VOS_MemSet(&pstUSIMMCurFileInfo->stEFInfo, 0 ,sizeof(USIMM_EFFCP_ST));
        /*lint +e534*/

        USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Clean the EF File Info");
    }

    USIMM_NORMAL_LOG("USIMM_UpdateFilePath: Need Update the DF Fcp Len");

    if (VOS_OK == USIMM_GetDFFcpLenInMap(pstUSIMMCurFileInfo->usCurDFID, &ulDFFcpLen))
    {
        pstUSIMMCurFileInfo->usCurDFFcpLen   = (VOS_UINT16)ulDFFcpLen;
    }
    else if (pstSelectPara->enCardType != USIMM_CARD_SIM)
    {
        pstUSIMMCurFileInfo->usCurDFFcpLen   = 0;

        USIMM_WARNING_LOG("USIMM_UpdateFilePath: Clean the DF Fcp Len");
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_UpdateFilePath: Can Not Find the DF Fcp Len");
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_OpenSpeedFileInit
功能描述  :初始化快速开机需要的文件初始化
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年5月22日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_OpenSpeedFileInit(VOS_VOID)
{
    VOS_UINT8                           aucImsi[USIMM_EF6F07Len];
    VOS_UINT8                           aucImsiDefault[USIMM_EF6F07Len] = {0x8,0x9,0x10,0x10,0x10,0x32,0x54,0x6,0x36};
    VOS_UINT8                          *pucData;

    if (VOS_OK != NV_Read(en_NV_Item_EF6F07, (VOS_VOID *)aucImsi, USIMM_EF6F07Len))
    {
        pucData = aucImsiDefault;
    }
    else
    {
        pucData = aucImsi;
    }

    /*lint -e534*/
    USIMM_PoolInsertOneFile(EFIMSI, USIMM_EF6F07Len, pucData, USIMM_UNLIMIT_APP,
                            USIMM_EFSTRUCTURE_TRANSPARENT);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitOpneSpeed
功能描述  :初始化快速开机需要的全局变量的内容，并上报卡状态　
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitOpenSpeed(VOS_VOID)
{
    /*初始化当前的基本内容*/
    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType           = USIMM_CARD_ROM_SIM;
    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService        = USIMM_CARD_SERVIC_AVAILABLE;

    gstUSIMMBaseInfo.enCurPINType               = USIMM_PIN2;

    gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime  = 3;

    gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime  = 3;

    gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime  = 10;

    gstUSIMMADFInfo.stPINInfo.ucPuk2RemainTime  = 10;

    USIMM_OpenSpeedFileInit();

    USIMM_CardStatusInd(MAPS_PIH_PID);

    return;
}


/*****************************************************************************
函 数 名  :USIMM_UsimVoltageSwitch
功能描述  :USIMM卡电压切换
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK
修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UsimVoltageSwitch(VOS_UINT8 ucCharaByte, VOS_UINT8 *pucVoltageMismatchFlag)
{
    VOS_INT32                           lVoltageSwitchRst;
    VOS_UINT16                          usFileID;
    VOS_UINT32                          ulResult;

    if (USIMM_VOLTAGE_1_8V == (ucCharaByte & USIMM_VOLTAGE_1_8V))
    {
        USIMM_INFO_LOG("USIMM_UsimVoltageSwitch:the current Voltage is 1.8V.");
        return VOS_OK;
    }

    if (USIMM_VOLTAGE_3V == (ucCharaByte & USIMM_VOLTAGE_3V))
    {
        *pucVoltageMismatchFlag = VOS_TRUE;

        /* 如果MF的FCP中指示电压为3V的话，则切换电压，底软API不会出现3V到3V的切换 */
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_UsimVoltageSwitch:SIM Card Change the Voltage Failed.");

            return VOS_ERR;
        }

        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            return VOS_OK;
        }

        /* 电压切换后再选择一次MF */
        USIMM_ClearCurFileInfo();   /*保障 MF 可以选到*/

        usFileID = MF;

        ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, 1, &usFileID);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_InsertNoNeedPinFileToPool: Select MF is Failed");

            return VOS_ERR;
        }

        return VOS_OK;
    }

    if (USIMM_VOLTAGE_5V == (ucCharaByte & USIMM_VOLTAGE_5V))
    {
        *pucVoltageMismatchFlag = VOS_TRUE;

        USIMM_ERROR_LOG("USIMM_UsimVoltageSwitch:Voltage is 5V.");
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UsimVoltageSwitch:the current Voltage is ERROR.");
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UsimTerminalCapability
功能描述  :USIMM卡terminal capability下发
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK
修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_UsimTerminalCapability(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_TERMINAL_CAPABILITY_STRU      stTerminalCapability;

    /* 判断是否需要下发terminal capability */
    if(USIMM_SUPSYSCMD == gstUSIMMCurFileInfo.stDFInfo.ucSupCmd)
    {
        /* 读nv,判断是否支持terminal capability下发，支持的话获取下发数据单元 */
        if(NV_OK == NV_Read(en_NV_Item_TERMINAL_CAPABILITY, &stTerminalCapability, sizeof(USIMM_TERMINAL_CAPABILITY_STRU)))
        {
            if((VOS_TRUE == stTerminalCapability.ulIsEnable) && (0 != stTerminalCapability.ulLen))
            {
                /* 下发terminal capability p1 p2参数都填0 */
                if(VOS_OK != USIMM_Terminal_Capability_APDU(0, 0, &stTerminalCapability))
                {
                    /* 出错仅打印错误，不影响初始化流程 */
                    USIMM_ERROR_LOG("USIMM_UsimTerminalCapability: Send terminal capability is Failed");
                }

                ulResult = USIMM_CheckSW(&gstUSIMMAPDU);/*检查选择结果*/

                /*判断检查结果*/
                if(USIMM_SW_OK != ulResult)
                {
                    USIMM_WARNING_LOG("USIMM_UsimTerminalCapability:USIMM_CheckSW error");
                }
            }
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InsertNoNeedPinFileToPool
功能描述  :将不受PIN保护文件放入缓冲池
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK
调用函数  :USIMM_SelectDFFile
          USIMM_InsertFileToPool
          USIMM_ClearCurFileInfo
修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InsertNoNeedPinFileToPool(VOS_VOID)
{
    USIMM_APP_TYPE_ENUM_UINT32          enAppType;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    VOS_UINT16                          usFileID;

    USIMM_ClearCurFileInfo();   /*保障 MF 可以选到*/

    usFileID = MF;

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, 1, &usFileID);

    if(ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_InsertNoNeedPinFileToPool: Select MF is Failed");

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_UNAVAILABLE;          /*卡当前不可用*/

        return VOS_ERR;
    }

    /* USIM卡判断是否需要进行电压切换，是否需要下发terminal capability */
    if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        ulResult = USIMM_UsimVoltageSwitch(gstUSIMMCurFileInfo.stDFInfo.ucCharaByte,
                                           &g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag);

        if(ulResult != VOS_OK)
        {
            USIMM_ERROR_LOG("USIMM_InsertNoNeedPinFileToPool: Select MF is Failed");

            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_UNAVAILABLE;          /*卡当前不可用*/

            return VOS_ERR;
        }

        USIMM_UsimTerminalCapability();
    }

    /*初始化当前MF下的文件*/
    for(i=0; i<USIMM_INITFIRST_FILENUM; i++)
    {
        /* 根据卡类型确定APP类型，做文件池的初始化 */
        enAppType   =   ((USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)?USIMM_GSM_APP:USIMM_UMTS_APP);
        ulResult    =   USIMM_InsertFileToPool(enAppType, gausInitFileOne[i]);

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_WARNING_LOG("USIMM_InsertNoNeedPinFileToPool: Select File under MF is Failed");
        }
    }

    USIMM_INFO_LOG("USIMM_InsertNoNeedPinFileToPool: Init Card File First Step 1 Finished");

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InsertLPFileToPool
功能描述  :选择语言文件并将其插入到文件缓冲池中，EFLP is optional in USIM card,
           but it is mandatory in SIM card,因此即使选择失败初始化流程也不中断，所以此函数返回值为ok
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK
调用函数  :USIMM_InsertFileToPool

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InsertLPFileToPool(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_APP_TYPE_ENUM_UINT32          enAppType;

    enAppType = ((USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)?USIMM_GSM_APP:USIMM_UMTS_APP);

    ulResult = USIMM_InsertFileToPool(enAppType, EFLP);/*初始化语言文件内容*/

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_WARNING_LOG("USIMM_InsertLPFileToPool: Select EFLP File is Failed");
    }

    gstUSIMMPOOL.enPoolStatus = USIMM_POOL_FIRST_STEP;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InsertNeedPinFileToPool
功能描述  :将受PIN保护文件放入缓冲池
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK
调用函数  :USIMM_SelectDFFile
          USIMM_InsertFileToPool
          USIMM_SendInitCardMsg
修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat   [DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InsertNeedPinFileToPool(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT16                         *pusFile;
    VOS_UINT32                          ulFileNum;
    USIMM_APP_TYPE_ENUM_UINT32          enAppType;

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        pusFile     =   gausUsimInitMFile;
        ulFileNum   =   USIMM_INITUSIM_MFILENUM;
        enAppType   =   USIMM_UMTS_APP;

    }
    else
    {
        pusFile     =   gausSimInitMFile;
        ulFileNum   =   USIMM_INITSIM_MFILENUM;
        enAppType   =   USIMM_GSM_APP;
    }

    for(i = 0;i < ulFileNum;i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(enAppType, pusFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_InsertNeedPinFileToPool:Read Mandatory File Failed");

#if(FEATURE_ON == FEATURE_PTM)
            USIMM_RecordCardErrorLog(USIMM_MNTN_MODULE_INIT,
                                    USIMM_MNTN_INIT_FILEERROR,
                                    VOS_NULL,
                                    pusFile[i],
                                    USIMM_MNTN_ERROR_LEVEL_MAJOR);
#endif
        }
    }

    /*USIMM文件规避方案总入口*/
    USIMM_FileAccessFix();

    USIMM_NORMAL_LOG("USIMM_InsertNeedPinFileToPool: USIMM Init Card File Second is Finished");

    return VOS_OK;
}

/********************************************************************
  Function:     USIMM_AttFileInit
  Description:  AT&T定制文件初始化函数
  Input:        无
  Output:       无
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_AttFileInit(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT16                         *pusFile;
    VOS_UINT32                          ulFileNum;

    /* 判断AT&T定制是否打开 */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        return;
    }

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
            pusFile     =   g_ausAttUsimInitFile;
            ulFileNum   =   USIMM_USIM_ATT_INITFILE_NUM;
    }
    else
    {
            pusFile     =   g_ausAttSimInitFile;
            ulFileNum   =   USIMM_SIM_ATT_INITFILE_NUM;
    }

    for (i = 0;i < ulFileNum;i++ )
    {
        USIMM_InsertAttFileToPool(USIMM_ATT_APP, pusFile[i]);
    }

    return;
}

/********************************************************************
  Function:     USIMM_InsertAttFileToPool
  Description:  AT&T定制文件放入文件缓存池处理函数
  Input:        USIMM_APP_TYPE_ENUM_UINT32 enAppType:传入的APP类型
                VOS_UINT8 usFile:传入的文件ID
  Output:       无
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_InsertAttFileToPool(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFile)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                          *pucData;
    VOS_UINT16                          usDataLen;

    /* 按ATT的APP类型来选择文件 */
    if (VOS_OK != USIMM_SelectFile(enAppType, USIMM_NEED_FCP, 1, &usFile))
    {
        return;
    }

    /* 判断文件是否超长，如果超长换成最大值，不然就用FCP中的值 */
    if (gstUSIMMCurFileInfo.stEFInfo.usFileLen > USIMM_MAX_FILE_SIZE)
    {
        usDataLen = USIMM_MAX_FILE_SIZE;
    }
    else
    {
        usDataLen = gstUSIMMCurFileInfo.stEFInfo.usFileLen;
    }

    pucData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, usDataLen);

    if (VOS_NULL_PTR == pucData)
    {
        USIMM_ERROR_LOG("USIMM_InsertAttFileToPool: VOS_MemAlloc Error");

        return;
    }

    /* 读取文件内容，出错退出，继续USIMM模块初始化 */
    ulResult = USIMM_ReadTFFile(usDataLen, pucData);

    if(USIMM_SW_OK != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_InsertAttFileToPool: USIMM_ReadTFFile Error");

        return;
    }

    /* 将AT&T的文件放入缓冲池中 */
    if(VOS_OK != USIMM_PoolInsertOneFile(usFile,
                                         gstUSIMMCurFileInfo.stEFInfo.usFileLen,
                                         pucData,
                                         enAppType,
                                         gstUSIMMCurFileInfo.stEFInfo.enFileType))
    {
        USIMM_ERROR_LOG("USIMM_InsertAttFileToPool: USIMM_PoolInsertOneFile Error");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucData);
        /*lint +e534*/

        return;
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucData);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitCardOptionalFile
功能描述  :实现了读取文件至缓存区的操作
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_PoolInsertOneFile
修订记录  :
1. 日    期   : 2008年8月20日
   作    者   : m00128685
   修改内容   : Creat
2. 日    期   : 2010年7月5日
   作    者   : j00168360
   修改内容   : [DTS2011070600422]GCF 27.22.4.7.2-2 Refresh测试用例失败

*****************************************************************************/
VOS_UINT32 USIMM_InitCardOptionalFile(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFileNum;
    USIMM_APP_TYPE_ENUM_UINT32          enAppType;
    USIMM_OPFILE_LIST_STRU             *pstFileList;

    if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        pstFileList =   gastUsimInitOFile;
        ulFileNum   =   USIMM_INITUSIM_OFILENUM;
        enAppType   =   USIMM_UMTS_APP;
    }
    else
    {
        pstFileList =   gastSimInitOFile;
        ulFileNum   =   USIMM_INITSIM_OFILENUM;
        enAppType   =   USIMM_GSM_APP;
    }


    for (i =  0; i < ulFileNum; i++)
    {
        if (UICC_SVR_NONE != pstFileList[i].usService)
        {
            if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(pstFileList[i].usService))
            {
                continue;
            }
        }

        if (VOS_OK != USIMM_InsertFileToPool(enAppType, pstFileList[i].usFileId))
        {
            USIMM_WARNING_LOG("USIMM_InitCardOptionalFile: Read Optional File Failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_InitCardOptionalFile: USIMM Init Card File Third is Finished");

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_InitUsimPBPath
功能描述  : 初始化当前的USIM卡的电话簿路径
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_InitUsimPBPath(VOS_VOID)
{
    VOS_UINT32              ulResult;
    VOS_UINT16              ausPath[] = {MF, DFTELCOM};

    /*GOBAL 电话簿优先*/
    ulResult = USIMM_SelectFile(USIMM_PB_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(ulResult != USIMM_SW_OK)
    {
        USIMM_NORMAL_LOG("USIMM_InitUsimPBPath: DF TELCOM Not here");

        ausPath[1] = ADF;

        ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }

    if(ulResult == USIMM_SW_OK)                  /*如果不存在 5F3A, 也是需要保存目录信息*/
    {
       gstUSIMMBaseInfo.stPBInfo.usPBDfID = ausPath[1];
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitCardFile
功能描述  :初始化卡文件
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectDFFile

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_VOID USIMM_InitCardFile(VOS_UINT32 ulDfMax, USIMM_DF_CONTENT_ST *pstDFContent)
{
    VOS_UINT32          i;
    VOS_UINT32          j;
    VOS_UINT32          k = 0;
    VOS_UINT32          m;
    VOS_UINT32          ulResult;
    VOS_UINT16          ausPath1[2] = {MF, 0};
    VOS_UINT16          ausPath2[3] = {MF, 0, 0};

    for(i=0; i<ulDfMax; i++)    /*根据卡一级目录个数进行循环*/
    {
        ausPath1[1] = pstDFContent[i].stDFCont.usDfID;

        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath1), ausPath1);

        if(ulResult != USIMM_SW_OK)  /*一级目录选择失败*/
        {
            continue;
        }

        /*保存一级目录信息*/
        g_stUSIMMCardFileMap[k].stDFFileMap.ulDfFcpLen          = gstUSIMMAPDU.ulRecDataLen;
        g_stUSIMMCardFileMap[k].stDFFileMap.stFileCont.usDfID   = pstDFContent[i].stDFCont.usDfID;
        g_stUSIMMCardFileMap[k].stDFFileMap.stFileCont.pusEFList= pstDFContent[i].stDFCont.pusEFList;
        g_stUSIMMCardFileMap[k].stDFFileMap.stFileCont.usEFNum  = pstDFContent[i].stDFCont.usEFNum;

        j = k;                  /*保存一级目录信息偏移位置*/

        for(m=0; m<pstDFContent[i].ulGDFNum; m++)       /*初始化二级目录信息*/
        {
            ausPath2[1] = pstDFContent[i].stDFCont.usDfID;
            ausPath2[2] = pstDFContent[i].pstGDFCont[m].usDfID;

            ulResult = USIMM_SelectFile(USIMM_UNLIMIT_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath2), ausPath2);

            if(ulResult == USIMM_SW_OK)
            {
                if(j != k)      /*二级目录大于一个，需要在前面再次保存一级目录信息*/
                {
                    /*lint -e534*/
                    VOS_MemCpy(&g_stUSIMMCardFileMap[j].stDFFileMap, &g_stUSIMMCardFileMap[k].stDFFileMap, sizeof(USIMM_SINGLE_FILEMAP_ST));
                    /*lint +e534*/
                }

                /*lint -e534*/
                VOS_MemCpy(&g_stUSIMMCardFileMap[j].stGDFFileMap, &pstDFContent->pstGDFCont[m], sizeof(USIMM_FILE_CONTENT_ST));
                /*lint +e534*/

                g_stUSIMMCardFileMap[j].stGDFFileMap.ulDfFcpLen = gstUSIMMAPDU.ulRecDataLen;

                j++;            /*保存信息指向下一个空位置*/
            }
        }

        if(k == j)                  /*该目录有二级目录存在*/
        {
            k = j + 1;              /*需要新建目录信息*/
        }
        else
        {
            k = j;
        }
    }

    return;
}
/*****************************************************************************
函 数 名  :USIMM_InitUsimCardFileMap
功能描述  :初始化USIM卡文件结构
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitUsimCardFileMap(VOS_VOID)
{
    USIMM_InitCardFile(USIMM_USIMDFCONTENT_MAX, g_stUsimDFContent);

    USIMM_InitUsimPBPath(); /*完成电话簿目录的初始化*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitSimCardFileMap
功能描述  :初始化SIM卡文件结构
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ClearCurFileInfo
        USIMM_SelectDFFile
        USIMM_InitCardFile

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitSimCardFileMap(VOS_VOID)
{
    gstUSIMMBaseInfo.stPBInfo.usPBDfID = DFTELCOM;  /*SIM卡默认电话簿目录*/

    USIMM_InitCardFile(USIMM_SIMDFCONTENT_MAX, g_stSimDFContent);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitPINRemainTime
功能描述  :初始化当前USIM卡的PIN剩余次数
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_GetPINRemainTime
           USIMM_GetPUKRemainTime
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_InitPINRemainTime(VOS_VOID)
{
    VOS_UINT32 ulResult;

    /*初始化PIN1剩余次数*/
    ulResult = USIMM_GetPINRemainTime(gstUSIMMCurFileInfo.stDFInfo.ucPIN1RefNum);

    if(VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /*初始化PIN2剩余次数*/
    ulResult = USIMM_GetPINRemainTime(gstUSIMMCurFileInfo.stDFInfo.ucPIN2RefNum);

    if(VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /*初始化PUK1剩余次数*/
    ulResult = USIMM_GetPUKRemainTime(gstUSIMMCurFileInfo.stDFInfo.ucPIN1RefNum);

    if(VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /*初始化PUK2剩余此时*/
    ulResult = USIMM_GetPUKRemainTime(gstUSIMMCurFileInfo.stDFInfo.ucPIN2RefNum);

    if(VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitCardPINInfo
功能描述  :初始化当前卡PIN状态
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
           USIMM_InitPINRemainTime
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
2. 日    期  : 2011年8月30日
   作    者  : j00168360
   修改内容  : [DTS2011083000162]，USIM模块正向清理保护性复位及卡路径选择
*****************************************************************************/
VOS_UINT32 USIMM_InitCardPINInfo(VOS_VOID)
{
    VOS_UINT32 ulResult;

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        ulResult = USIMM_InitPINRemainTime();  /*初始化PIN剩余次数*/

        if(VOS_OK != ulResult)
        {
            return VOS_ERR;
        }
    }

    if((USIMM_PIN_ENABLED == gstUSIMMADFInfo.stPINInfo.enPin2Enable)
        &&(0 != gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime))
    {
        gstUSIMMADFInfo.enPin2Verified = USIMM_PIN_NEED;
    }

    if((USIMM_PIN_ENABLED == gstUSIMMADFInfo.stPINInfo.enPin1Enable)
        &&(0 != gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime))
    {
        gstUSIMMADFInfo.enPin1Verified = USIMM_PIN_NEED;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SimGetPhase
功能描述  :获取SIM卡的phase
输入参数  :无
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2013年6月20日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID  USIMM_SimGetPhase(VOS_VOID)
{
    VOS_UINT8                           ucData;
    VOS_UINT16                          ausPath[] = {MF, DFGSM, EFPHASE};
    VOS_UINT32                          ulResult;

    /* EFphase文件的默认值为2以便后续的FDNBDN过程可以继续走下去 */
    gstUSIMMBaseInfo.ulSimPhase = USIMM_SIM_PHASE_TWO;

    /* 判断结果和文件状态 */
    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SimGetPhase: USIMM_SelectFileWithPath(EFPHASE) Error");

        return;
    }

    if (VOS_OK != USIMM_ReadTFFile(sizeof(ucData), &ucData))
    {
        USIMM_ERROR_LOG("USIMM_SimGetPhase:Read EFPHASE Failed");

        return;
    }

    /* 保存当前SIM卡PHASE */
    gstUSIMMBaseInfo.ulSimPhase = (VOS_UINT32)ucData;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitNeedPinSteps
功能描述  :初始卡需要PIN验证的文件并加入缓冲池
输入参数  :无
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_VOID USIMM_InitNeedPinSteps(USIMM_MODE_TYPE_ENUM_UINT8 ucMode)
{
    VOS_UINT32                          ulRet = VOS_OK;
    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /* 读取UST文件 */
        ulRet = USIMM_InsertFileToPool(USIMM_UMTS_APP, EFUST);

        /* 即使FDN过程出错，卡的初始化过程也继续 */
        /*lint -e534*/
        (VOS_VOID)USIMM_InitUsimFDNBDNStatus();
        /*lint +e534*/
    }
    else
    {
        /* 读取SST文件 */
        ulRet = USIMM_InsertFileToPool(USIMM_GSM_APP, EFUST);

        USIMM_SimGetPhase();

        USIMM_SimProfileDownload(ucMode);

        /*lint -e534*/
        (VOS_VOID)USIMM_InitSimFDNBDNStatus();
        /*lint +e534*/
    }

    if(VOS_OK != ulRet)
    {
        USIMM_WARNING_LOG("USIMM_InitNeedPinSteps: Read SST File Failed");

#if(FEATURE_ON == FEATURE_PTM)
        USIMM_RecordCardErrorLog(USIMM_MNTN_MODULE_INIT,
                                USIMM_MNTN_INIT_SSTFAIL,
                                VOS_NULL,
                                VOS_NULL,
                                USIMM_MNTN_ERROR_LEVEL_CRITICAL);
#endif
    }

    gstUSIMMPOOL.enPoolStatus = USIMM_POOL_AVAILABLE;

    if(VOS_ERR == USIMM_InsertNeedPinFileToPool())     /*初始化其它文件内容*/
    {
        USIMM_ERROR_LOG("USIMM_InitNeedPinSteps: USIMM_InsertNeedPinFileToPool Error");
    }

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_Status_APDU(USIMM_STATUS_CURAPP_INITIALIZED, USIMM_STATUS_NO_DATA_RETURNED, 0x00);
        /*lint +e534*/
    }

    USIMM_NORMAL_LOG("USIMM_InitNeedPinSteps: USIMM_InsertNeedPinFileToPool Finished");

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitCardFirstStep
功能描述  :实现了初始化的第一步，获取卡类型
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_InitCardTypeByATR(VOS_VOID)
{
    VOS_UINT32                          ulResult    = VOS_ERR;
    VOS_UINT32  ulErrlogNumber;
    OAM_MNTN_NO_SIM_CARD_EVENT_STRU     stNoSimCard;
    VOS_INT32                           lVoltageSwitchRst;

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_InitCardFirstStep: Reset Card is Failed");

        /* 因为双开双待所以高16位记录pid,低16位记录原来的id */
        ulErrlogNumber = WUEPS_PID_USIM;
        ulErrlogNumber <<= 16;
        ulErrlogNumber |= MNTN_OAM_NO_SIM_CARD_EVENT;

        if(VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber, (void *)&stNoSimCard, sizeof(OAM_MNTN_NO_SIM_CARD_EVENT_STRU)))
        {
            USIMM_ERROR_LOG("USIMM_InitCardFirstStep: Fail to record no SIM card in Errorlog file");
        }
        return VOS_ERR;
    }

    ulResult = USIMM_DecodeATR(); /*判断卡类型*/

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_InitCardFirstStep: USIMM_DecodeATR is Failed");/*打印错误*/

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;        /*当前状态为无卡*/

        return VOS_ERR;
    }

    return VOS_OK;                                 /*初始化第一步完成*/
}

/*****************************************************************************
函 数 名  :USIMM_InitUsimGlobal
功能描述  :初始USIM卡全局变量
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitUsimGlobal(VOS_VOID)
{
    gstUSIMMBaseInfo.ucCLA        = USIMM_USIM_CLA;

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange = USIMM_CARD_STATE_CHANGED; /*需要上报卡状态*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitSimGlobal
功能描述  :初始USIM卡全局变量
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitSimGlobal(VOS_VOID)
{
    gstUSIMMBaseInfo.ucCLA                              = USIMM_SIM_CLA;

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange = USIMM_CARD_STATE_CHANGED; /*需要上报卡状态*/

    /* SIM 不支持功能 */
    gstUSIMMBaseInfo.enSupportPath                      = USIMM_NOTSUPPORT_PATH;

    gstUSIMMBaseInfo.enSupportSFI                       = USIMM_NOTSUPPORT_SFI;

    gstUSIMMBaseInfo.enSupportChannel                   = USIMM_NOTSUPPORT_CHANNEL;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Reselect3GApp
功能描述  :USIM卡重新选择3G应用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2013年4月23日
   作    者   : h59254
   修改内容   : 新增加函数
*****************************************************************************/
VOS_VOID USIMM_Reselect3GApp(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_ST                       stApduInfo = {0};
    VOS_UINT8                           ucP2;
    VOS_UINT8                           ucTmp;

    /* make pclint happy */
    ucP2 = USIMM_SELECT_TERMINATION_AID;
    ucTmp= USIMM_SELECT_RETURN_FCP_TEMPLATE;
    ucP2 |= ucTmp;

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_DF_NAME;
    stApduInfo.aucAPDU[P2] = ucP2;
    stApduInfo.aucAPDU[P3] = (VOS_UINT8)gstUSIMMADFInfo.ulAIDLen;

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, gstUSIMMADFInfo.aucAID, (VOS_UINT8)gstUSIMMADFInfo.ulAIDLen);
    /*lint +e534*/

    if (VOS_OK != USIMM_SelectFile_APDU(&stApduInfo))
    {
        USIMM_ERROR_LOG("USIMM_Reselect3GApp: Termination ADF Fail");
    }

    /* 解析AID选择3G应用 */
    ulResult = USIMM_DecodeEFDIR();

    /* 如果解析EFDIR成功，说明是USIM卡，重选AID */
    if (VOS_OK == ulResult)
    {
        /*lint -e534*/
        USIMM_SelectUiccADF();
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshAidVerify
功能描述  :Refresh命令AID验证
输入参数  :ulAidLen:AID长度
           pucAid:AID内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2013年4月23日
   作    者   : h59254
   修改内容   : 新增加函数
*****************************************************************************/
VOS_UINT32 USIMM_RefreshAidVerify(VOS_UINT32 ulAidLen, VOS_UINT8 *pucAid)
{
    /* REFRESH命令中没有AID时返回正确 */
    if (VOS_NULL == ulAidLen)
    {
        return VOS_OK;
    }

    /* 当前没有AID，可能是SIM卡 */
    if (VOS_NULL == gstUSIMMADFInfo.ulAIDLen)
    {
        return VOS_OK;
    }

    if (VOS_OK == VOS_MemCmp(pucAid, gstUSIMMADFInfo.aucAID, ulAidLen))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_Select3GApp
功能描述  :USIM卡选择3G应用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_Select3GApp(VOS_VOID)
{
    VOS_UINT32              ulResult;

    /* 解析AID选择3G应用 */
    ulResult = USIMM_DecodeEFDIR();

    /* 如果解析EFDIR成功，说明是USIM卡，做ATR数据解析的第二步 */
    if (VOS_OK == ulResult)
    {
        USIMM_DecodeATRSecondStep();
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_Select2GApp
功能描述  :SIM卡选择2G应用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化s

*****************************************************************************/
VOS_UINT32 USIMM_Select2GApp(VOS_VOID)
{
    VOS_INT32                           lVoltageSwitchRst;
    VOS_UINT16                          ausPath[] = {MF, DFGSM};
    VOS_UINT32                          ulResult;

    USIMM_INFO_LOG("USIMM_Select2GApp: This Card is Sim Card");

    if(VOS_OK != USIMM_CheckCLStep())
    {
        USIMM_WARNING_LOG("USIMM_Select2GApp: Check is Failed with CL enable");     /*打印错误*/

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_Select2GApp: Select SIM Card DFGSM is Failed");     /*打印错误*/

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;

        return VOS_ERR;
    }

    USIMM_SaveDFPinInfo();

    g_stUSIMMCardVersionType.ucHasWGModule  = VOS_TRUE;

    if (0x10 == (gstUSIMMCurFileInfo.stDFInfo.ucCharaByte & 0x70)) /*SIM卡根据文件特性字节切换电压*/
    {
        USIMM_NORMAL_LOG("USIMM_Select2GApp: SIM Card Need Change the Voltage.");

        g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag = VOS_TRUE;

        /*卡复位失败按照无卡处理*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_Select2GApp:SIM Card Change the Voltage Failed.");

            return VOS_ERR;      /*不需要后续的判断处理*/
        }

        /* 电压未切换直接返回 */
        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            return VOS_OK;
        }

        ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        /* 电压切换后再选择一次DFGSM */
        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_Select2GApp: Select MF is Failed");

            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;

            return VOS_ERR;      /*不需要后续的判断处理*/
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetTerminalProfile
功能描述  :读取nv项当前终端参数设置
输入参数  :无
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_VOID USIMM_GetTerminalProfile(USIMM_STK_CFG_STRU *pstProfileContent)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUsimProfile[]=STK_USIM_PROFILE_DEFAULT;
    VOS_UINT8                           aucSimProfile[]= STK_SIM_PROFILE_DEFAULT;

    /*读取NV项判断当前的SAT状态*/
    ulResult = NV_Read(en_NV_Item_TerminalProfile_Set, pstProfileContent, sizeof(USIMM_STK_CFG_STRU));

    if(NV_OK == ulResult)/*读取失败按照默认下发*/
    {
        return;
    }

    USIMM_WARNING_LOG("USIMM_GetTerminalProfile: NV_Read Failed");

    if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stUsimProfile.aucProfile, aucUsimProfile, sizeof(aucUsimProfile));
        /*lint +e534*/

        pstProfileContent->stUsimProfile.ucProfileLen = sizeof(aucUsimProfile);
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stSimProfile.aucProfile, aucSimProfile, sizeof(aucSimProfile));
        /*lint +e534*/

        pstProfileContent->stSimProfile.ucProfileLen = sizeof(aucSimProfile);
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_UsimProfileDownload
功能描述  :USIM卡终端能力参数下发
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

调用函数  :USIMM_GetTerminalProfile
        USIMM_TermimalProfile_APDU
        USIMM_CheckSW

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_UsimProfileDownload(VOS_VOID)
{
    USIMM_STK_CFG_STRU                  stProfileContent;

    /* 如果之前已经DOWNLOAD失败，就不再需要下载了 */
    if (USIMM_PROFILE_DOWNLOAD_FAIL == g_stUSIMMInitInfo.stUSIMMInfo.enTPDownloadStatus)
    {
        return USIMM_INIT_OK;
    }

    USIMM_GetTerminalProfile(&stProfileContent);

    if (VOS_OK != USIMM_TermimalProfile_APDU(stProfileContent.stUsimProfile.ucProfileLen,
                                             stProfileContent.stUsimProfile.aucProfile))
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enTPDownloadStatus = USIMM_PROFILE_DOWNLOAD_FAIL;

        USIMM_ERROR_LOG("USIMM_UsimProfileDownload: USIMM_TermimalProfile_APDU Error");

        return USIMM_INIT_RESET;
    }

    return USIMM_INIT_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SimProfileDownload
功能描述  :SIM卡终端能力参数下发
输入参数  :无
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat   [DTS2011042900838]卡初始化流程优化
*****************************************************************************/
VOS_VOID USIMM_SimWarmResetProc(VOS_VOID)
{
    VOS_INT32                           lResult;
    VOS_UINT32                          ulResult;

    /* 复位卡，如果复位失败会将卡类型的全局变量置为无卡，因此复位成功后要重置卡类型的全局变量 */
    if (VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_SimHotResetProc: Deactive Card Error");

        return;
    }

    if (VOS_OK != USIMM_DLResetCard(USIMM_RESET_CARD, &lResult))
    {
        USIMM_ERROR_LOG("USIMM_SimHotResetProc: USIMM_DLResetCard Error");

        return;
    }

    if (VOS_OK != USIMM_Select2GApp())
    {
        USIMM_ERROR_LOG("USIMM_SimHotResetProc: USIMM_Select2GApp Error");

        return;
    }

    if (VOS_OK != USIMM_InitCardPINInfo())
    {
        USIMM_ERROR_LOG("USIMM_SimHotResetProc: USIMM_InitCardPINInfo Error");

        return;
    }

    /*lint -e534*/
    USIMM_AdjudgeCardState();
    /*lint +e534*/

    ulResult = USIMM_AutoVerifyPIN(gstUSIMMADFInfo.stPINInfo.enPin1Enable,
                                   &gstUSIMMADFInfo.enPin1Verified,
                                   gstUSIMMADFInfo.ucPIN1RefNum,
                                   gstUSIMMADFInfo.aucPin1);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SimHotResetProc: USIMM_AutoVerifyPIN Error");
    }

    /*lint -e534*/
    USIMM_AdjudgeCardState();
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_SimProfileDownload
功能描述  :SIM卡终端能力参数下发
输入参数  :无
输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat   [DTS2011042900838]卡初始化流程优化
*****************************************************************************/
VOS_VOID USIMM_SimProfileDownload(USIMM_MODE_TYPE_ENUM_UINT8 ucMode)
{
    VOS_UINT32                          ulResult;
    USIMM_STK_CFG_STRU                  stProfileContent;

    /* 非电复位的refresh不需要下发terminal profile */
    if (USIMM_REFRESH_MODE == ucMode)
    {
        return;
    }

    /* 如果之前已经DOWNLOAD失败，就不再需要下载了 */
    if (USIMM_PROFILE_DOWNLOAD_FAIL == g_stUSIMMInitInfo.stUSIMMInfo.enTPDownloadStatus )
    {
        return;
    }

    /* PHASE1的SIM卡不需要下发terminal profile 和处理BDN FDN过程，只有PHASE2+的卡才需要 */
    if(gstUSIMMBaseInfo.ulSimPhase < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_SimProfileDownload: SIM Not Support SAT");

        return;
    }

    /*读取NV项判断当前的SAT状态*/
    USIMM_GetTerminalProfile(&stProfileContent);

    ulResult = USIMM_TermimalProfile_APDU(stProfileContent.stSimProfile.ucProfileLen,
                                          stProfileContent.stSimProfile.aucProfile);

    if(VOS_OK != ulResult)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enTPDownloadStatus = USIMM_PROFILE_DOWNLOAD_FAIL;

        USIMM_ERROR_LOG("USIMM_SimProfileDownload: USIMM_TermimalProfile_APDU Error");

        USIMM_SimWarmResetProc();

        return;
    }

    /* ATT定制过程，失败了也不处理，继续初始化 */
    USIMM_AttUpdataSupportTable();

    return;

}

/********************************************************************
  Function:     USIMM_AttEfTerminalSupportTableValueGet
  Description:  获取终端能力参数值
  Input:        无
  Output:       无
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_AttEfTerminalSupportTableValueGet(VOS_UINT8 *pucValue)
{
    VOS_UINT8                           aucSuppotTableDefault[USIMM_ATT_SUPPORT_TABLE_MAX]  =
                                                            {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x02, 0x00,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    NVIM_SCAN_CTRL_STRU                 stNvScanCtrl;
    NVIM_ATT_ENS_CTRL_STRU              stNvEnsCtrl;
    NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU stNvActingHplmnCtrl;
    NAS_NVIM_MS_CLASS_STRU              stMsMode;

    if (VOS_OK == NV_Read(en_NV_Item_Scan_Ctrl_Para, (VOS_VOID *)&stNvScanCtrl, sizeof(NVIM_SCAN_CTRL_STRU)))
    {
        aucSuppotTableDefault[USIMM_ATT_SCAN_CTRL_OFFSET]           =   stNvScanCtrl.ucNvimActiveFlg;
    }

    if (VOS_OK == NV_Read(en_NV_Item_Att_Ens_Ctrl_Para, (VOS_VOID *)&stNvEnsCtrl, sizeof(NVIM_ATT_ENS_CTRL_STRU)))
    {
        aucSuppotTableDefault[USIMM_ATT_NETWORK_SELECTION_OFFSET]   =   stNvEnsCtrl.ucNetSelMenuFlg;
        aucSuppotTableDefault[USIMM_ATT_RAT_BALANCING]              =   stNvEnsCtrl.ucRatBalancingFlg;
    }

    if (VOS_OK == NV_Read(en_NV_Item_ACTING_PLMN_SUPPORT_FLAG, (VOS_VOID *)&stNvActingHplmnCtrl,
                          sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU)))
    {
        aucSuppotTableDefault[USIMM_ATT_ACTING_HPLMN]               =    stNvActingHplmnCtrl.ucNvimActiveFlg;
    }

    if (VOS_OK == NV_Read(en_NV_Item_MMA_MsClass, &stMsMode, sizeof(stMsMode)))
    {
        aucSuppotTableDefault[USIMM_ATT_LTE_SUPPORT]                = (NV_MS_MODE_PS_ONLY == stMsMode.ucMsClass)?USIMM_ATT_LTE_DATA_ONLY:USIMM_ATT_LTE_DATE_VOICE_CSFB;
    }

    /*lint -e534*/
    VOS_MemCpy(pucValue, aucSuppotTableDefault, sizeof(aucSuppotTableDefault));
    /*lint +e534*/

    return;
}

/********************************************************************
  Function:     USIMM_AttUpdataSupportTable
  Description:  ATT卡终端能力参数写入6FD2文件
  Input:        无
  Output:       无
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_AttUpdataSupportTable(VOS_VOID)
{
    VOS_UINT8                               aucSuppotTable[USIMM_ATT_SUPPORT_TABLE_MAX]={0};
    VOS_UINT16                              usActureLen;
    VOS_UINT16                              usFileID = EFTERMINALSUPPORTTABLE;

    /* 判断AT&T定制是否打开 */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        return;
    }

    /* 选择6FD2文件 */
    if(VOS_OK != USIMM_SelectFile(USIMM_ATT_APP, USIMM_NEED_FCP, 1, &usFileID))
    {
        USIMM_ERROR_LOG("USIMM_AttUpdataSupportTable: Select File Error 0x6FD2");

        return;
    }

    USIMM_AttEfTerminalSupportTableValueGet(aucSuppotTable);

    /* 6FD2文件的长度只能为8或16或小于8的值 */
    if (USIMM_ATT_SUPPORT_TABLE_MAX <= gstUSIMMCurFileInfo.stEFInfo.usFileLen)
    {
        usActureLen =   USIMM_ATT_SUPPORT_TABLE_MAX;
    }
    else if (USIMM_ATT_SUPPORT_TABLE_MIN <= gstUSIMMCurFileInfo.stEFInfo.usFileLen)
    {
        usActureLen =   USIMM_ATT_SUPPORT_TABLE_MIN;
    }
    else
    {
        usActureLen =   gstUSIMMCurFileInfo.stEFInfo.usFileLen;
    }

    if (VOS_OK != USIMM_UpdateTFFile(usActureLen, aucSuppotTable))
    {
        USIMM_ERROR_LOG("USIMM_AttUpdataSupportTable: USIMM_UpdateTFFile Fail");
    }

    return;
}


/*****************************************************************************
函 数 名  :USIMM_InitUsimEccFile
功能描述  :初始化USIM卡ECC文件
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat   [DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitUsimEccFile(VOS_VOID)
{
    VOS_UINT8                          *pData;
    VOS_UINT8                           ucEccType;
    VOS_UINT8                           ucRecordNum =0;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          ausPath[] = {MF, ADF, EFECC};

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_SELECT_FAIL;

        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:usim card select ECC file fail");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_USIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    if(USIMM_EFSTRUCTURE_FIXED != gstUSIMMCurFileInfo.stEFInfo.enFileType)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_TYPE_ERR;

        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:ECC FILE TYPE error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_USIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    pData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT,
                        gstUSIMMCurFileInfo.stEFInfo.usFileLen);/*分配数据存储空间*/

    if(VOS_NULL_PTR == pData)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:VOS_MemAlloc error");

        return VOS_ERR;
    }

    ucEccType   = ECC_USIM;

    ucRecordNum = gstUSIMMCurFileInfo.stEFInfo.ucRecordNum;

    ulResult    = USIMM_ReadLFFile(&gstUSIMMCurFileInfo.stEFInfo, USIMM_READ_ALLRECORD, pData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_READ_FAIL;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_InitUsimEccFile:USIMM_ReadLFFile error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_USIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    USIMM_EccNumberInd(ucEccType, gstUSIMMCurFileInfo.stEFInfo.usFileLen, ucRecordNum, pData);/*上报当前的Ecc号码内容*/

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pData);
    /*lint +e534*/

    return VOS_OK;

}

/*****************************************************************************
函 数 名  :USIMM_InitSimEccFile
功能描述  :初始化SIM卡ECC文件,已和sunxibo确认出错情况下可以不上报默认值，只要报紧急号码为0即可
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
        VOS_OK

修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : Creat   [DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitSimEccFile(VOS_VOID)
{
    VOS_UINT8                           *pData;
    VOS_UINT8                           ucEccType;
    VOS_UINT8                           ucRecordNum =0;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          ausPath[] = {MF, DFGSM, EFECC};

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_SELECT_FAIL;

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_SIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    if(USIMM_EFSTRUCTURE_TRANSPARENT != gstUSIMMCurFileInfo.stEFInfo.enFileType)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_TYPE_ERR;

        USIMM_ERROR_LOG("USIMM_InitSimEccFile:ECC FILE TYPE error");

        /* ECC文件不存在的情况，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_SIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    pData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,DYNAMIC_MEM_PT,
                        gstUSIMMCurFileInfo.stEFInfo.usFileLen);/*分配数据存储空间*/

    if(VOS_NULL_PTR == pData)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_InitSimEccFile:VOS_MemAlloc error");

        return VOS_ERR;
    }

    ucEccType = ECC_SIM;

    ulResult = USIMM_ReadTFFile(gstUSIMMCurFileInfo.stEFInfo.usFileLen, pData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_READ_FAIL;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_InitSimEccFile:USIMM_ReadTFFile error");

        /* 读取文件失败认为ECC文件不存在，给PB上报文件长度为0，返回ok，不终止初始化流程 */
        USIMM_EccNumberInd(ECC_SIM, VOS_NULL, VOS_NULL, VOS_NULL_PTR);

        return VOS_OK;
    }

    USIMM_EccNumberInd(ucEccType, gstUSIMMCurFileInfo.stEFInfo.usFileLen, ucRecordNum, pData);/*上报当前的Ecc号码内容*/

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pData);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_PowerDownResetPrepare
功能描述  :掉电重启前的准备工作
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年6月17日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_PowerDownResetPrepare(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lVoltageSwitchRst;

    /* USIMM卡初始化任一步失败时即按SIM卡初始化，此时需要做电重启 */
    USIMM_InitGlobalVarOnReset();

    if(VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_InitNoNeedPinSteps: Deactive Card Error");

        return VOS_ERR;
    }

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_InitNoNeedPinSteps: Reset Card is Failed");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_CLEnableGetICCID
功能描述  :C+L选择EF ICCID的内容到内存
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2014年01月16日
   作    者   : zhuli
   修改内容   :

*****************************************************************************/

VOS_VOID USIMM_CLEnableGetICCID(VOS_VOID)
{
    VOS_UINT16                          ausPathMF[2]={MF, EFICCID};
    VOS_UINT32                          ulResult;

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, 
                                USIMM_NEED_FCP, 
                                ARRAYSIZE(ausPathMF), 
                                ausPathMF);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_WARNING_LOG("USIMM_CLEnableGetICCID:Select File Failed");

        return;
    }

    ulResult = USIMM_ReadTFFile(USIMM_EFICCID_LEN, g_aucEFIccidData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_InsertFileToPool: USIMM_ReadTFFile Error");
        g_bCacheEFIccidData = VOS_FALSE;
        (VOS_VOID)VOS_MemSet(g_aucEFIccidData, 0, sizeof(g_aucEFIccidData));
    }

    g_bCacheEFIccidData = VOS_TRUE;

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CheckCLStep
功能描述  :C+L选择检查2G卡是否可用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2014年01月16日
   作    者   : zhuli
   修改内容   :

*****************************************************************************/
VOS_UINT32 USIMM_CheckCLStep(VOS_VOID)
{
    VOS_UINT16                          ausCDMAPath[] = {MF, DFCDMA};
    VOS_UINT16                          ausGSMPath[] = {MF, DFGSM};
    VOS_UINT32                          ulCDMAResult = VOS_OK;
    VOS_UINT32                          ulGsmResult = VOS_OK;
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;
    VOS_INT32                           lVoltageSwitchRst;

    /* 默认读取Modem0的，保证原有的电信手机可以读取卡类型 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return VOS_OK;
    }

    g_stUSIMMCardVersionType.enCardMode     = USIMM_CARD_ICC_TYPE;

    if (VOS_TRUE == stNVData.ucLCEnableFlg)
    {
        ulCDMAResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausCDMAPath), ausCDMAPath);
        ulGsmResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausGSMPath), ausGSMPath);

        g_stUSIMMCardVersionType.ucHasCModule   = (VOS_OK == ulCDMAResult);
        g_stUSIMMCardVersionType.ucHasWGModule  = (VOS_OK == ulGsmResult);

        USIMM_CLEnableGetICCID();

        if(VOS_OK != mdrv_sci_deact())      /*国际卡按照初始化，需要重启*/
        {
            USIMM_ERROR_LOG("USIMM_CheckCLStep: Deactive Card Error");
        }

        if(VOS_OK != USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_CheckCLStep: Reset Card is Failed");
        }
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_Select2GApp: C+L is Off");     /*打印错误*/

        return VOS_OK;
    }

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
        USIMM_WARNING_LOG("USIMM_Select2GApp: C+L is Off");     /*打印错误*/

        return VOS_OK;
    }

    /*电信要求检查卡的CDMA能力*/
    if ((VOS_OK != ulCDMAResult)
     && (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck))
    {
        USIMM_WARNING_LOG("USIMM_Select2GApp: Select Card 7F25 is Failed");     /*打印错误*/

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;

        return VOS_ERR;
    }

    if (TAF_NVIM_LC_RAT_COMBINED_CL == USIMM_GetRATMode())   /*无论是国际卡还是UIM卡都退出按照无卡上报*/
    {
        (VOS_VOID)USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausCDMAPath), ausCDMAPath);

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;

        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}
/*****************************************************************************
函 数 名  :USIMM_InitNoNeedPinSteps
功能描述  :初始化卡不受PIN保护的步骤
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2011年6月17日
   作    者   : j00168360
   修改内容   : Creat [DTS2011042900838]卡初始化流程优化
*****************************************************************************/
VOS_UINT32 USIMM_InitNoNeedPinSteps(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)     /*当前为USIM*/
    {
        i = 0;
    }
    else         /*当前为SIM*/
    {
        i = 1;
    }

    for( ; i < USIMM_CARD_INIT_TBL_SIZE; i++)
    {
        for(j = 1; j < g_aCardInitTbl[i].ulStepNum; j++)
        {
            ulResult = g_aCardInitTbl[i].pInitFunTbl[j].pProcFun();

            if(VOS_ERR == ulResult)
            {
                if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
                {
                    if(VOS_OK != USIMM_PowerDownResetPrepare())
                    {
                        return VOS_ERR;
                    }

                    /* 跳出当前循环, 按SIM卡初始化 */
                    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_SIM;
                    g_stUSIMMInitInfo.stUSIMMInfo.enTPDownloadStatus = USIMM_PROFILE_DOWNLOAD_SUCCESS;

                    break;
                }
                else
                {
                    /* SIM卡某步初始化错误则直接返回 */
                    return VOS_ERR;
                }
            }

            /* 进入重启模式，目前只有TP下载失败之后需要重启 */
            if (USIMM_INIT_RESET == ulResult)
            {
                /* 重新进入初始化 */
                if (VOS_OK != USIMM_PowerDownResetPrepare())
                {
                    return VOS_ERR;
                }

                /* 调用USIMM_PowerDownResetPrepare后会将卡类型改变，需要改回来 */
                gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_USIM;

                j = 0;

                continue;
            }

            if (USIMM_INIT_FATAL_EXIT == ulResult)
            {
                return VOS_ERR;
            }
        }

        if(j == g_aCardInitTbl[i].ulStepNum)
        {
           break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitIsimHandle
功能描述  :初始化ISIM卡
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   : creat

*****************************************************************************/
VOS_UINT32 USIMM_InitIsimHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_USIMSUPIMS_STRU               stUsimSupIms;

    if(USIMM_CARD_USIM != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /*上报无卡*/
        gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType     = USIMM_CARD_NOCARD;
        gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService  = USIMM_CARD_SERVIC_ABSENT;
    }
    else
    {
        if(USIMM_CARD_SERVIC_AVAILABLE == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService)
        {
            /* 通过NV判断usim是否支持IMS,默认支持 */
            ulResult = NV_Read(en_NV_Item_Usim_Support_Ims, &stUsimSupIms, sizeof(USIMM_USIMSUPIMS_STRU));

            if((NV_OK == ulResult) && (PS_USIM_SERVICE_AVAILIABLE == stUsimSupIms.ulUsimSupImsEnable))/*读取失败按照默认下发*/
            {
                /* 上报ok 置ISIM卡状态，服务状态 */
                gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType     = USIMM_CARD_ISIM;
                gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService  = USIMM_CARD_SERVIC_AVAILABLE;
                gulUsimSupportIMS                                    = VOS_TRUE;
            }
            else
            {
                /* 上报无卡 */
                gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType     = USIMM_CARD_ISIM;
                gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService  = USIMM_CARD_SERVIC_ABSENT;
            }
        }
        else
        {
            /* 置卡状态 */
            gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType         = USIMM_CARD_ISIM;
            gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService      = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;
        }
    }

    gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enStateChange = USIMM_CARD_STATE_CHANGED;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitCard
功能描述  :完成卡初始化的主控函数
输入参数  :pMsg ->消息指针
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
2. 日    期   : 2011年6月20日
   作    者   : j00168360
   修改内容   :  [DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitCard(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32               ulResult;
    VOS_UINT32               ulRandNum;

    USIMM_InitGlobalVarOnReset();

    ulResult = USIMM_InitCardTypeByATR();   /*获取ATR判断卡状态*/

    if(VOS_OK != ulResult)     /*初始化第一步错误*/
    {
        USIMM_ERROR_LOG("USIMM_InitCard: USIMM_InitCardFirstStep Error");   /*打印错误*/

        return VOS_ERR;
    }

    USIMM_NORMAL_LOG("USIMM_InitCard: USIMM_InitCardFirstStep is Finished");

    /* 初始化卡不受PIN保护的步骤 */
    ulResult = USIMM_InitNoNeedPinSteps();

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_InitCard: USIMM_InitNoNeedPinSteps Error");   /*打印错误*/

        return VOS_ERR;
    }

    /* 初始化ATT定制文件，其不受PIN码控制 */
    USIMM_AttFileInit();

    /* 基本逻辑通道为电信业务专用,通道号为0 */
    ulRandNum = VOS_Rand(USIMM_SESSION_ID_MAX);

    /* 由于SessionId值不能为0，所以当随机数为0时需要处理下 */
    if (0 == ulRandNum)
    {
        ulRandNum = USIMM_SESSION_ID_MAX;
    }

    g_astUSIMMChCtrl[0].ulSessionId   = USIMM_SESSION_ID(ulRandNum, 0);

    g_astUSIMMChCtrl[0].ulChanNum     = USIMM_BASE_CHANNEL_NUM;

    g_astUSIMMChCtrl[0].ulAIDLen      = gstUSIMMADFInfo.ulAIDLen;

    if (sizeof(g_astUSIMMChCtrl[0].aucADFName) >= gstUSIMMADFInfo.ulAIDLen)
    {
        /*lint -e534*/
        //VOS_MemCpy(g_astUSIMMChCtrl[0].aucADFName, gstUSIMMADFInfo.aucAID, gstUSIMMADFInfo.ulAIDLen);
        VOS_MemCpy(g_astUSIMMChCtrl[0].aucADFName, gstUSIMMADFInfo.aucAID, USIMM_AID_LEN_MAX);
        /*lint +e534*/
    }

    /* 当PIN不使能时，进一步初始化文件 */
    if(((0 != gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime)
        &&(USIMM_PIN_ENABLED !=  gstUSIMMADFInfo.stPINInfo.enPin1Enable)))
    {
        USIMM_InitNeedPinSteps(USIMM_NORMAL_MODE);

        /* 初始化可选文件 */
        if(VOS_OK != USIMM_InitThirdSteps())
        {
            USIMM_ERROR_LOG("USIMM_InitCard:USIMM_InitThirdSteps is Failed");

            return VOS_ERR;
        }

    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_ChangePathToU16
功能描述  : 把UINT8编码个数的数据转换成UINT16的数据
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
/*lint -e661 -e662 by h59254*/
VOS_VOID USIMM_ChangePathToU16(VOS_UINT32 ulDataLen, VOS_UINT8 *pucData, VOS_UINT32 *pulLen, VOS_UINT16 *pusPath)
{
    VOS_UINT32 i;
    VOS_UINT32 j = 0;

    for(i=0; i<ulDataLen; i+=2, j++)
    {
        pusPath[j] = ((pucData[i]<<0x08)&0xFF00)+pucData[i+1];
    }

    *pulLen = j;

    return;
}
/*lint +e661 +e662 by h59254*/

/*****************************************************************************
函 数 名  : USIMM_SearchFileInList
功能描述  : 再文件列表中搜索文件是否存在
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SearchFileInList(VOS_UINT16 usFileId, VOS_UINT16 usFileNum, VOS_UINT16 *pusFileList, VOS_UINT16 *pusOldList)
{
    VOS_UINT32 i;

    if(pusFileList == VOS_NULL_PTR)
    {
        USIMM_INFO_LOG("USIMM_SearchFileInList: The Input Para Error.");

        return VOS_ERR;
    }

    if(pusFileList == pusOldList)
    {
        return VOS_ERR;
    }

    for(i=0; i<usFileNum; i++)
    {
        if(usFileId == pusFileList[i])
        {
            USIMM_INFO_LOG("USIMM_SearchFileInList: Find the EF In List.");

            return VOS_OK;
        }
    }

    USIMM_ERROR_LOG("USIMM_SearchFileInList: Could not Find the EF In List.");

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : USIMM_SelectUiccADF
功能描述  : 选择ADF
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  : 无
被调函数  : 外部接口
History     :
1.日    期  : 2009年6月26日
  作    者  :
  修改内容  : Create
*****************************************************************************/
VOS_UINT32 USIMM_SelectUiccADF(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_ST                       stApduInfo = {0};

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_DF_NAME;
    stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    stApduInfo.aucAPDU[P3] = (VOS_UINT8)gstUSIMMADFInfo.ulAIDLen;

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, gstUSIMMADFInfo.aucAID, (VOS_UINT8)gstUSIMMADFInfo.ulAIDLen);
    /*lint +e534*/

    ulResult = USIMM_ReselectFileAPDU(&stApduInfo);

    if(VOS_OK == ulResult) /*判断AID选择结果*/
    {
        USIMM_ClearCurEFInfo(&gstUSIMMCurFileInfo);/*选中DF文件后，上次选中的EF文件置为无效值*/

        ulResult = USIMM_DecodeDFFcp(USIMM_CARD_USIM, &stApduInfo, &gstUSIMMCurFileInfo);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_SelectUiccADF: Select File Error");/*打印错误*/

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_UNAVAILABLE;          /* 卡当前服务不可用 */

        ulResult = VOS_ERR;
    }

    if(VOS_OK == ulResult)
    {
        gstUSIMMCurFileInfo.usCurDFID = ADF;

        USIMM_SaveDFPinInfo();
    }

    /* ATT定制过程，失败了也不处理，继续初始化 */
    /* 仅当是USIM时选择AID，确保可以选中6FD2文件 */
    USIMM_AttUpdataSupportTable();

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SelectDFFile
功能描述  :安照文件ID方式选择DF
输入参数  :usFileId:DF文件ID
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
           USIMM_CheckSW
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SelectDFFile(VOS_UINT16                        usFileId,
                                    USIMM_SELECT_PARA_STUR           *pstSelectPara,
                                    USIMM_CURFILEINFO_ST             *pstCurFileInfo)
{
    VOS_UINT8                           aucDFid[2];
    VOS_UINT32                          ulResult;
    USIMM_APDU_ST                       stApduInfo = {0};

    aucDFid[0] = (VOS_INT8)((usFileId>>8)&0xFF);
    aucDFid[1] = (VOS_UINT8)(usFileId&0xFF);

    if(USIMM_CARD_SIM == pstSelectPara->enCardType)    /*SIM卡*/
    {
        stApduInfo.aucAPDU[CLA] = USIMM_SIM_CLA;
        stApduInfo.aucAPDU[P2]  = USIMM_SIM_SELECT_P2_PARA;
    }
    else
    {
        stApduInfo.aucAPDU[CLA] = USIMM_USIM_CLA;
        stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    }

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_FILE_ID;

    stApduInfo.aucAPDU[P3] = sizeof(aucDFid);

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, aucDFid, sizeof(aucDFid));
    /*lint +e534*/

    ulResult = USIMM_ReselectFileAPDU(&stApduInfo);/*选择文件*/

    /*保存获取的原始数据到全局变量*/
    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU, &stApduInfo, sizeof(stApduInfo));
    /*lint +e534*/

    /*判断检查结果*/
    if(USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SelectDFFile:USIMM_ReselectFileAPDU error");

        return ulResult;
    }

    /*DF 都返回FCP，解析获取的数据*/
    ulResult = USIMM_DecodeDFFcp(pstSelectPara->enCardType, &stApduInfo, pstCurFileInfo);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectDFFile:Decode Fcp error");

        return USIMM_SW_ERR;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectEFByID
功能描述  :按照文件ID方式选中EF并解析FCP
输入参数  :usFileId:文件ID
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
 1. 日    期   : 2007年7月10日
     作    者   : z00100318
     修改内容   : Creat
 2. 日    期   : 2011年4月29日
    作    者   : j00168360
    修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
*****************************************************************************/
VOS_UINT32 USIMM_SelectEFByID(VOS_UINT16                     usFileId,
                                    USIMM_SELECT_PARA_STUR           *pstSelectPara,
                                    USIMM_CURFILEINFO_ST             *pstCurFileInfo)
{
    VOS_UINT8                           aucEfId[2];
    VOS_UINT32                          ulResult;
    USIMM_APDU_ST                       stApduInfo = {0};

    aucEfId[0] = (VOS_UINT8)((usFileId>>8)&0xFF);

    aucEfId[1] = (VOS_UINT8)(usFileId&0xFF);

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_FILE_ID;

    if(USIMM_CARD_SIM == pstSelectPara->enCardType)
    {
        stApduInfo.aucAPDU[CLA] = USIMM_SIM_CLA;
        stApduInfo.aucAPDU[P2]  = USIMM_SIM_SELECT_P2_PARA;
    }
    else
    {
        stApduInfo.aucAPDU[CLA] = USIMM_USIM_CLA;

        if (USIMM_NEED_FCP == pstSelectPara->enEfFcpFlag)
        {
            stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
        }
        else
        {
            stApduInfo.aucAPDU[P2] = USIMM_SELECT_NO_DATA_RETURNED;
        }
    }

    stApduInfo.aucAPDU[P3] = sizeof(aucEfId);

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, aucEfId, sizeof(aucEfId));
    /*lint +e534*/

    ulResult = USIMM_ReselectFileAPDU(&stApduInfo);  /*选择文件*/

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU, &stApduInfo, sizeof(stApduInfo));
    /*lint +e534*/

    if(USIMM_SW_OK != ulResult)/*判断检查结果*/
    {
        USIMM_WARNING_LOG("USIMM_SelectEFByID:USIMM_ReselectFileAPDU error");

        return ulResult;
    }

    if (VOS_NULL != stApduInfo.ulRecDataLen)
    {
        ulResult = USIMM_DecodeEFFcp(pstSelectPara->enCardType, &stApduInfo, pstCurFileInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_SelectEFByID:Decode FCP error");

            return USIMM_SW_ERR;
        }
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileNoPath
功能描述  :根据路安装单步方式选择EF
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年4月29日
   作    者   : j00168360
   修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
3. 日    期  : 2011年8月22日
   作    者  : j00168360
   修改内容  : [DTS2011081901894]，at+crsm命令引起的掉卡
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileNoPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen)
{
    VOS_UINT32 i;
    VOS_UINT32 ulResult = USIMM_SW_ERR;

    /*lint -e830 -e539*/
    for (i = 0; i < pstFilePath->ulDataLen; i++)
    {
        if (USIMM_IS_DF_FILE(pstFilePath->pusData[i]))
        {
            ulResult = USIMM_SelectDFFile(pstFilePath->pusData[i], pstSelectPara, pstCurFileInfo);
        }
        else
        {
            ulResult = USIMM_SelectEFByID(pstFilePath->pusData[i], pstSelectPara, pstCurFileInfo);
        }

        if ((USIMM_SW_OK != ulResult)&&(USIMM_SW_OK_WITH_SAT != ulResult))
        {
            USIMM_ERROR_LOG("USIMM_SelectFileNoPath: Select File Error.");

            break;
        }
    }

    /* 无论是否选中当前文件路径都需要更新 */
    if (VOS_NULL_PTR != pusCurPathLen)
    {
        *pusCurPathLen = (VOS_UINT16)i;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_GetDiffPos
功能描述  :获得当前文件和选择文件的不同位置
输入参数  :pstFilePath:   选择文件路径
           pstCurFileInfo:当前文件信息
输出参数  :无
返 回 值  :路径不同点，从0开始

 修订记录  :
1. 日    期    : 2013年6月20日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetDiffPos(USIMM_U16_LVDATA_STRU *pstFilePath,
                                  USIMM_CURFILEINFO_ST  *pstCurFileInfo)
{
    VOS_UINT32                          ulMinLen;
    VOS_UINT32                          ulDiffPos;

    if (pstFilePath->ulDataLen < pstCurFileInfo->usFilePathLen)
    {
        ulMinLen = pstFilePath->ulDataLen;
    }
    else
    {
        ulMinLen = pstCurFileInfo->usFilePathLen;
    }

    /* 比较选择路径和当前路径 */
    for (ulDiffPos = 0; ulDiffPos < ulMinLen; ulDiffPos++)
    {
        if (pstCurFileInfo->ausFilePath[ulDiffPos] != pstFilePath->pusData[ulDiffPos])
        {
            break;
        }
    }

    return ulDiffPos;
}

/*****************************************************************************
函 数 名  :USIMM_GetCurDfPos
功能描述  :获得路径的当前目录位置
输入参数  :pstCurFileInfo:  当前的文件信息
输出参数  :无
返 回 值  :目录的位置，从0开始

 修订记录  :
1. 日    期    : 2013年6月20日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCurDfPos(USIMM_CURFILEINFO_ST *pstCurFileInfo)
{
    VOS_UINT32                              ulCurDFPos;

    /* 获得当前路径所在位置 */
    if (USIMM_NULL_ID == pstCurFileInfo->usCurEFID)
    {
        ulCurDFPos = pstCurFileInfo->usFilePathLen - 1;
    }
    else
    {
        ulCurDFPos = pstCurFileInfo->usFilePathLen - 2;
    }

    return ulCurDFPos;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileByRelativePath
功能描述  :通过相对路径方式单步选择文件
输入参数  :pstSelectPara:  选择文件参数
           pstFilePath:    选择文件路径
           pstCurFileInfo: 当前选中文件的信息
输出参数  :无
返 回 值  :VOS_ERR

 修订记录  :
1. 日    期    : 2013年6月20日
    作    者   : g47350
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileByRelativePath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo)
{
    VOS_UINT32                          ulRelativeLen = 0;
    VOS_UINT16                          ausRelativePath[USIMM_MAX_PATH_LEN] = {0};
    USIMM_U16_LVDATA_STRU               stRelativePath = {0};
    VOS_UINT32                          ulDiffPos ;
    VOS_UINT32                          ulCurDFPos;

    /* 上次文件没有选中，则相对路径就是绝对路径 */
    if (0 == pstCurFileInfo->usFilePathLen)
    {
        return USIMM_SW_ERR;
    }

    ulDiffPos  = USIMM_GetDiffPos(pstFilePath, pstCurFileInfo);

    ulCurDFPos = USIMM_GetCurDfPos(pstCurFileInfo);

    if (ulCurDFPos == (ulDiffPos - 1))
    {
        /* 需要选中当前目录 */
        if ((USIMM_NULL_ID != pstCurFileInfo->usCurEFID)
            && (ulDiffPos == pstFilePath->ulDataLen))
        {
            /*lint -e534*/
            VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos - 1], sizeof(VOS_UINT16));
            /*lint +e534*/

            ulRelativeLen = 1;
        }
        else /* 当前目录的所有子节点文件可选 */
        {
            /*lint -e534*/
            VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos], (pstFilePath->ulDataLen- ulDiffPos)*sizeof(VOS_UINT16));
            /*lint +e534*/

            ulRelativeLen =  pstFilePath->ulDataLen - ulDiffPos;
        }
    }

    if (ulCurDFPos == ulDiffPos)
    {
        /* 当前目录父节点下的DF文件可选 */
        if (ulDiffPos < pstFilePath->ulDataLen)
        {
            if (USIMM_IS_DF_FILE(pstFilePath->pusData[ulDiffPos])
                && (ADF != pstCurFileInfo->ausFilePath[ulCurDFPos]))
            {
                /*lint -e534*/
                VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos], (pstFilePath->ulDataLen - ulDiffPos)*sizeof(VOS_UINT16));
                /*lint +e534*/

                ulRelativeLen = pstFilePath->ulDataLen - ulDiffPos;
            }
        }
        else
        {
            /* 当前目录的父节点可选 */
            /*lint -e534*/
            VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos - 1], sizeof(VOS_UINT16));
            /*lint +e534*/

            ulRelativeLen = 1;
        }
    }

    /* 假如选择的路径与当前路径相同则再选次最后的文件 */
    if ((ulDiffPos == pstCurFileInfo->usFilePathLen) && (ulDiffPos == pstFilePath->ulDataLen))
    {
        /*lint -e534*/
        VOS_MemCpy(ausRelativePath, &pstFilePath->pusData[ulDiffPos - 1], sizeof(VOS_UINT16));
        /*lint +e534*/

        ulRelativeLen = 1;
    }

    /* 不能获得相对路径 */
    if (0 == ulRelativeLen)
    {
        USIMM_WARNING_LOG("USIMM_SelectFileByRelativePath: Can't get relative path.");

        return USIMM_SW_ERR;
    }

    stRelativePath.ulDataLen = ulRelativeLen;
    stRelativePath.pusData   = ausRelativePath;

    return USIMM_SelectFileNoPath(pstSelectPara, &stRelativePath, pstCurFileInfo, VOS_NULL_PTR);
}

/*****************************************************************************
函 数 名  :USIMM_SelectEFByPath
功能描述  :按照路径方式选择当前的EF
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年4月29日
   作    者   : j00168360
   修改内容   : [DTS2011042700921]一卡双号切换过程中电话本功能不正常
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileByPath(USIMM_SELECT_PARA_STUR         *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU           *pstFilePath,
                                         USIMM_CURFILEINFO_ST           *pstCurFileInfo)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPathLen;
    VOS_UINT8                           aucPath[USIMM_MAX_PATH_LEN*2] = {0};
    VOS_UINT32                          i;
    USIMM_APDU_ST                       stApduInfo = {0};

    /* 路径至少包括MF和2Fxx */
    if ((pstFilePath->ulDataLen < 2)||(VOS_NULL_PTR == pstFilePath->pusData))
    {
        return USIMM_SW_ERR;
    }

    for (i = 0; i < (pstFilePath->ulDataLen-1); i++)    /*跳过前面的MF*/
    {
        aucPath[i*2] = (VOS_UINT8)((pstFilePath->pusData[i+1]>>0x08)&0x00FF);

        aucPath[(i*2)+1] = (VOS_UINT8)(pstFilePath->pusData[i+1]&0x00FF);
    }

    ucPathLen = (VOS_UINT8)((pstFilePath->ulDataLen-1)*sizeof(VOS_UINT16));

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_PATH_FROM_MF;

    if (USIMM_IS_DF_FILE(pstFilePath->pusData[pstFilePath->ulDataLen-1])
        || (USIMM_NEED_FCP == pstSelectPara->enEfFcpFlag))
    {
        stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    }
    else
    {
        stApduInfo.aucAPDU[P2] = USIMM_SELECT_NO_DATA_RETURNED;
    }

    stApduInfo.aucAPDU[P3] = ucPathLen;

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, aucPath, ucPathLen);
    /*lint +e534*/

    ulResult = USIMM_ReselectFileAPDU(&stApduInfo);

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU, &stApduInfo, sizeof(stApduInfo));
    /*lint +e534*/

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SelectEFByPath: USIMM_ReselectFileAPDU Error");

        return ulResult;
    }

    if (VOS_NULL != stApduInfo.ulRecDataLen)
    {
        ulResult = USIMM_DecodeFileFcp(pstSelectPara->enCardType, pstFilePath, &stApduInfo, pstCurFileInfo);

        if(VOS_OK != ulResult)  /*选不中文件的时候不需要更新路径*/
        {
            USIMM_WARNING_LOG("USIMM_SelectEFByPath: Decode Fcp Error");

            return USIMM_SW_ERR;
        }
    }
    else
    {
        USIMM_ClearCurDFInfo(pstCurFileInfo);

        USIMM_ClearCurEFInfo(pstCurFileInfo);
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  : USIMM_GetPBFilePath
功能描述  : 获取当前的电话本路径
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetPBFilePath(VOS_UINT16 usFileId, VOS_UINT32 *pulPathLen, VOS_UINT16 *pusPath)
{
    VOS_UINT8   ucFileType;

    if(gstUSIMMBaseInfo.stPBInfo.usPBDfID == 0)
    {
        USIMM_WARNING_LOG("USIMM_GetPBFilePath: usPBDfID is NULL.");

        return USIMM_SW_NOFILE_FOUND;
    }

    ucFileType = (VOS_UINT8)((usFileId >> 0x08)&0x00FF);

    if(ucFileType == EFUNDERDF)
    {
        if(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType == USIMM_CARD_USIM)
        {
            pusPath[0] = ADF;
        }
        else if(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType == USIMM_CARD_SIM)
        {
            pusPath[0] = DFTELCOM;
        }
        else
        {
            return USIMM_SW_NOFILE_FOUND;
        }

        *pulPathLen = 2;
        pusPath[1] = usFileId;

        return VOS_OK;
    }
    else if(ucFileType == EFUNDERGRANDADF)
    {
        *pulPathLen = 3;
        pusPath[0] = gstUSIMMBaseInfo.stPBInfo.usPBDfID;
        pusPath[1]= DFPHONEBOOK;
        pusPath[2] = usFileId;

        return VOS_OK;
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_GetPBFilePath: File Type is Wrong.");

        return USIMM_SW_NOFILE_FOUND;
    }
}

/********************************************************************
  Function:     USIMM_GetAttFilePath
  Description:  AT&T定制文件路径获取函数
  Input:        VOS_UINT16 usFileId：文件ID
  Output:       VOS_UINT32 *pulPathLen：输出的路径长度
                VOS_UINT16 *pusPath：输出的文件路径
  Return:       VOID
  Others:
********************************************************************/
VOS_UINT32 USIMM_GetAttFilePath(VOS_UINT16 usFileId, VOS_UINT32 *pulPathLen, VOS_UINT16 *pusPath)
{
    VOS_UINT8                           ucFileType;

    ucFileType = (VOS_UINT8)((usFileId >> 0x08)&0x00FF);

    if (EFUNDERATT == ucFileType)
    {
        if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            *pulPathLen =   3;
            pusPath[0]  =   ADF;
            pusPath[1]  =   DFATT;
            pusPath[2]  =   usFileId;
        }
        else
        {
            *pulPathLen =   2;
            pusPath[0]  =   DFATT;
            pusPath[1]  =   usFileId;
        }
    }
    else if (EFUNDERATTANDDF == ucFileType)
    {
        if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            *pulPathLen =   4;
            pusPath[0]  =   ADF;
            pusPath[1]  =   DFATT;
            pusPath[2]  =   DFUNDERDFATT;
            pusPath[3]  =   usFileId;
        }
        else
        {
            *pulPathLen =   3;
            pusPath[0]  =   DFATT;
            pusPath[1]  =   DFUNDERDFATT;
            pusPath[2]  =   usFileId;
        }
    }
    else
    {
        return USIMM_SW_NOFILE_FOUND;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_GetCardFilePath
功能描述  : 查询当前文件的路径
输入参数  :
输出参数  :
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetCardFilePath(USIMM_APP_TYPE_ENUM_UINT32 enFileApp,
                                        VOS_UINT16                  usFileId,
                                        VOS_UINT32                  *pulPathLen,
                                        VOS_UINT16                  *pusPath)
{
    VOS_UINT32  ulResult    = USIMM_SW_NOFILE_FOUND;
    VOS_UINT16  usDFID      = 0;
    VOS_UINT32  ulPathLen   = 0;
    VOS_UINT8   ucFileType;
    VOS_UINT32  i;
    VOS_UINT16  *pusFileList = VOS_NULL_PTR;

    ucFileType = USIMM_FILE_TYPE(usFileId);

    if (MFTAG == ucFileType)
    {
        *pusPath = usFileId;
        *pulPathLen = 1;
        return VOS_OK;
    }

    switch(enFileApp)
    {
        case USIMM_GSM_APP:
            usDFID = DFGSM;
            break;

        case USIMM_UMTS_APP:
            usDFID = ADF;
            break;

        case USIMM_PB_APP:
            return USIMM_GetPBFilePath(usFileId, pulPathLen, pusPath);

        case USIMM_ATT_APP:
            return USIMM_GetAttFilePath(usFileId, pulPathLen, pusPath);

        default:
            break;
    }

    for(i=0; i<ARRAYSIZE(g_stUSIMMCardFileMap); i++)
    {
        if(usDFID != 0)
        {
            if(usDFID != g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.usDfID)
            {
                continue;
            }
        }

        switch(ucFileType)
        {
            case DFUNDERMF:
                if(usFileId == g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.usDfID)
                {
                    ulResult = VOS_OK;
                }
                break;

            case DFUNDERDF:
                if(usFileId == g_stUSIMMCardFileMap[i].stGDFFileMap.stFileCont.usDfID)
                {
                    ulResult = VOS_OK;
                }
                break;

            case EFUNDERDF:
                ulResult = USIMM_SearchFileInList(usFileId, g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.usEFNum,
                                                        g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.pusEFList,
                                                        pusFileList);
                pusFileList = g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.pusEFList;
                break;

            case EFUNDERGRANDADF:
                ulResult = USIMM_SearchFileInList(usFileId, g_stUSIMMCardFileMap[i].stGDFFileMap.stFileCont.usEFNum,
                                                        g_stUSIMMCardFileMap[i].stGDFFileMap.stFileCont.pusEFList,
                                                        pusFileList);
                pusFileList = g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.pusEFList;
                break;

            default:
                USIMM_ERROR_LOG("USIMM_GetCardFilePath: The File Type is Error");
                return USIMM_SW_NOFILE_FOUND;
        }

        if(ulResult == VOS_OK)
        {
            break;
        }
    }

    if(i >= ARRAYSIZE(g_stUSIMMCardFileMap))
    {
        USIMM_ERROR_LOG("USIMM_GetCardFilePath:Could Not Found the Card Path");

        return USIMM_SW_NOFILE_FOUND;
    }

    pusPath[0] = MF;
    pusPath[1] = g_stUSIMMCardFileMap[i].stDFFileMap.stFileCont.usDfID;

    ulPathLen = 2;

    if((ucFileType == EFUNDERGRANDADF)||(ucFileType == DFUNDERDF))
    {
        pusPath[2] = g_stUSIMMCardFileMap[i].stGDFFileMap.stFileCont.usDfID;
        ulPathLen ++;
    }

    if((ucFileType == EFUNDERDF)||(ucFileType == EFUNDERGRANDADF))
    {
        pusPath[ulPathLen] = usFileId;
        ulPathLen ++;
    }

    *pulPathLen = ulPathLen;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileWithPath
功能描述  :按照路径方式选择当前的EF
输入参数  :ucLen:路径数据长度
           pData:路径数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReselectFileAPDU
          USIMM_CheckSW
          USIMM_DecodeUsimEFFcp
          USIMM_DecodeSimEFFcp
 修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期  : 2011年8月30日
   作    者  : j00168360
   修改内容  : [DTS2011083000162]，USIM模块正向清理保护性复位及卡路径选择
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileWithPath(USIMM_SELECT_PARA_STUR          *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU          *pstFilePath,
                                            USIMM_CURFILEINFO_ST           *pstCurFileInfo,
                                            VOS_UINT16                     *pusCurPathLen)
{
    VOS_UINT32                          ulResult;

    *pusCurPathLen = (VOS_UINT16)pstFilePath->ulDataLen;

    /* 首先处理只选MF文件 */
    if ((1 == pstFilePath->ulDataLen) && (MFTAG == USIMM_FILE_TYPE(pstFilePath->pusData[0])))
    {
        ulResult = USIMM_SelectDFFile(pstFilePath->pusData[0], pstSelectPara, pstCurFileInfo);

        if (USIMM_SW_OK != ulResult)
        {
            *pusCurPathLen = 0;
        }

        return ulResult;
    }

    /* 在USIM卡上通过路径选择方式进行文件选择 */
    if (USIMM_CARD_USIM == pstSelectPara->enCardType)
    {
        ulResult = USIMM_SelectFileByPath(pstSelectPara, pstFilePath, pstCurFileInfo);
    }
    /* 在SIM卡上通过相对路径方式进行单步选择 */
    else
    {
        ulResult = USIMM_SelectFileByRelativePath(pstSelectPara, pstFilePath, pstCurFileInfo);
    }

    if (USIMM_SW_OK != ulResult)
    {
        /* 最后采用绝对路径方式进行单步选择 */
        ulResult = USIMM_SelectFileNoPath(pstSelectPara, pstFilePath, pstCurFileInfo, pusCurPathLen);
    }

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SelectFileWithPath: Select File Failed");
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : USIMM_GetEFFilePath
 功能描述  : 获取Filelist中的第一个EF文件路径
 输入参数  : pucFileList: EF文件列表
             ulFileLen:文件列表长度
             pucEFPath:存放第一个EF文件路径
             pulPathLen:第一个EF文件路径长度
 输出参数  : 无
 返 回 值  : VOS_ERR:未找到匹配文件
             VOS_OK:找到EF文件
 修改历史  : m00128685
             2009-12-16
*****************************************************************************/
VOS_UINT32 USIMM_GetRefreshEFPath(VOS_UINT8 *pucFileList,
                                       VOS_UINT32 ulFileLen,
                                       VOS_UINT8 *pucEFPath,
                                       VOS_UINT32 *pulPathLen)
{
    VOS_UINT32 ulFileCnt;

    /*lint -e440 */
    for(ulFileCnt = 0; ((ulFileCnt+1) < ulFileLen); ulFileCnt += sizeof(VOS_UINT16))
    /*lint +e440 */
    {
        if((ulFileCnt+1) >= (USIMM_MAX_PATH_LEN*2))
        {
            break;
        }

        pucEFPath[ulFileCnt] = pucFileList[ulFileCnt];
        pucEFPath[ulFileCnt+1] = pucFileList[ulFileCnt+1];

        if((EFUNDERMF != pucFileList[ulFileCnt])
            &&(EFUNDERDF != pucFileList[ulFileCnt])
            &&(EFUNDERGRANDADF != pucFileList[ulFileCnt]))/*判断不为EF文件*/
        {
            continue;
        }

        *pulPathLen = ulFileCnt+2;

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshNoFileIndHandle
功能描述  :没有文件ID指示类型的REFRESH命令上报函数
输入参数  :pstMsg:REFRESH命令消息
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年05月28日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshNoFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg)
{
    USIMM_STKREFRESH_IND_STRU              *pstRefreshMsg;

    pstRefreshMsg = (USIMM_STKREFRESH_IND_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKREFRESH_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRefreshMsg)
    {
        USIMM_WARNING_LOG("USIMM_RefreshNoFileIndHandle: Alloc Msg is Fail");

        return;
    }

    pstRefreshMsg->stIndHdr.ulReceiverPid                       = MAPS_PIH_PID;        /*由PIH负责广播*/
    pstRefreshMsg->stIndHdr.enMsgName                           = USIMM_STKREFRESH_IND;
    pstRefreshMsg->usEfNum                                      = VOS_NULL;

    if (USIMM_SESSION_RESET_3G_ONLY == pstMsg->enRefreshType)
    {
        pstRefreshMsg->enRefreshType = USIMM_REFRESH_3G_SESSION_RESET;
    }
    else
    {
        pstRefreshMsg->enRefreshType = USIMM_REFRESH_ALL_FILE;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstRefreshMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshIsimFileIndHandle
功能描述  :实现了IMSI文件更新上报功能
输入参数  :pstRefreshMsg: 文件更新上报消息
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年7月24日
   作    者   : g47350
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshIsimFileIndHandle(USIMM_STKREFRESH_IND_STRU *pstRefreshMsg)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usFileNum = 0;
    USIMM_STKREFRESH_IND_STRU          *pstIsimRefreshMsg;
    USIM_REFRESH_FILE_STRU             *pstFile;
    /* 填充IMSI文件信息，固定路径为3F007FFF6FXX */
    VOS_UINT8                           aucPath[6] = {0x3F, 0x00, 0x7F, 0xFF, 0x00, 0x00};
    VOS_UINT16                          usFileId;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    /* 判断当前是否支持ISIM卡 */
    if (USIMM_CARD_ISIM != gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType)
    {
        USIMM_INFO_LOG("USIMM_RefreshIsimFileIndHandle: IMSI is disable.");

        return;
    }

    pstFile = VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, sizeof(USIM_REFRESH_FILE_STRU) * USIMM_MAX_REFRESH_FILE_NUM);

    if (VOS_NULL_PTR == pstFile)
    {
        USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: VOS_MemAlloc is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet(pstFile, 0, USIMM_MAX_REFRESH_FILE_NUM * sizeof(USIM_REFRESH_FILE_STRU));
    /*lint +e534*/

    for (i = 0; i < pstRefreshMsg->usEfNum; i++)
    {
        if (USIMM_GUTL_APP == pstRefreshMsg->astEfId[i].enAppType)
        {
            /* IMSI对应3个ISIM文件 */
            if (USIMM_USIM_EFIMSI_ID == pstRefreshMsg->astEfId[i].usFileId)
            {
                /* 处理6F02 */
                aucPath[4] = (EFISIMIMPI >> 8) & 0xFF;
                aucPath[5] = EFISIMIMPI & 0xFF;
                /* 将U8类型的路径转成STRING类型的路径 */
                USIMM_ChangePathToAsciiString(aucPath, sizeof(aucPath), (VOS_CHAR *)(&pstFile[usFileNum].aucPath[0]), &pstFile[usFileNum].usPathLen);

                /* 处理6F03 */
                aucPath[4] = (EFISIMDOMAIN >> 8) & 0xFF;
                aucPath[5] = EFISIMDOMAIN & 0xFF;
                /* 将U8类型的路径转成STRING类型的路径 */
                USIMM_ChangePathToAsciiString(aucPath, sizeof(aucPath), (VOS_CHAR *)(&pstFile[usFileNum + 1].aucPath[0]), &pstFile[usFileNum + 1].usPathLen);

                /* 处理6F04 */
                aucPath[4] = (EFISIMIMPU >> 8) & 0xFF;
                aucPath[5] = EFISIMIMPU & 0xFF;
                /* 将U8类型的路径转成STRING类型的路径 */
                USIMM_ChangePathToAsciiString(aucPath, sizeof(aucPath), (VOS_CHAR *)(&pstFile[usFileNum + 2].aucPath[0]), &pstFile[usFileNum + 2].usPathLen);

                usFileNum += 3;

                continue;
            }

            /* 判断是否为ISIM对应文件 */
            usFileId = USIMM_UsimEFIDToIsimEFID(pstRefreshMsg->astEfId[i].usFileId);

            if (VOS_NULL_WORD != usFileId)
            {
                /* 填充IMSI文件信息，路径长度固定为3，路径为3F007FFF6FXX */
                aucPath[4] = (usFileId >> 8) & 0xFF;
                aucPath[5] = usFileId & 0xFF;
                /* 将U8类型的路径转成STRING类型的路径 */
                USIMM_ChangePathToAsciiString(aucPath, sizeof(aucPath), (VOS_CHAR *)(&pstFile[usFileNum].aucPath[0]), &pstFile[usFileNum].usPathLen);

                usFileNum++;
            }
        }
    }

    /* 没有涉及ISIM文件则不用通知 */
    if (0 == usFileNum)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstFile);
        /*lint +e534*/

        return;
    }

    /* 由于USIM_REFRESH_IND_STRU中已经有一个USIM_REFRESH_IND_STRU单元所以usFileNum需要减1 */
    pstIsimRefreshMsg = (USIMM_STKREFRESH_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                              (sizeof(USIMM_STKREFRESH_IND_STRU)-VOS_MSG_HEAD_LENGTH)\
                                                               + ((usFileNum - 1) * sizeof(USIM_REFRESH_FILE_STRU)));

    if (VOS_NULL_PTR == pstIsimRefreshMsg)
    {
        USIMM_ERROR_LOG("USIMM_RefreshIsimFileIndHandle: VOS_AllocMsg is Failed");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstFile);
        /*lint +e534*/

        return;
    }

    pstIsimRefreshMsg->stIndHdr.ulReceiverPid               = MAPS_PIH_PID;
    pstIsimRefreshMsg->stIndHdr.enMsgName                   = USIMM_STKREFRESH_IND;
    pstIsimRefreshMsg->enRefreshType                        = USIMM_REFRESH_FILE_LIST;
    pstIsimRefreshMsg->usEfNum                              = usFileNum;

    for (i = 0; i < usFileNum; i++)
    {
        pstIsimRefreshMsg->astEfId[i].enAppType             = USIMM_IMS_APP;
        pstIsimRefreshMsg->astEfId[i].usFileId              = pstFile[i].usFileId;
        pstIsimRefreshMsg->astEfId[i].usPathLen             = pstFile[i].usPathLen;

        /*lint -e534*/
        VOS_MemCpy(pstIsimRefreshMsg->astEfId[i].aucPath, pstFile[i].aucPath, pstFile[i].usPathLen + 1);
        /*lint +e534*/

        if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_IMS_APP, pstFile[i].usPathLen, (VOS_CHAR *)pstFile[i].aucPath, &enFileID))
        {
            pstRefreshMsg->astEfId[i].usFileId = USIMM_DEF_FILEID_BUTT;
        }
        else
        {
            pstRefreshMsg->astEfId[i].usFileId = (VOS_UINT16)enFileID;
        }
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstIsimRefreshMsg);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pstFile);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshFileIndHandle
功能描述  :实现了读取文件的操作和结果的返回
输入参数  :API层下发消息内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectFile
          USIMM_ReadTFFile
          USIMM_ReadLFFile
          USIMM_GetFileCnf
修订记录  :
1. 日    期   : 2009年12月17日
   作    者   : m00128685
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_RefreshFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulTempLen;
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          ausPath[USIMM_MAX_PATH_LEN]             = {0};/*当前文件路径，16进制*/
    VOS_UINT8                           aucRefreshFile[USIMM_MAX_PATH_LEN*2]    = {0};/*当前单一文件路径，8进制*/
    VOS_UINT16                          usEfNum                                 = 0;
    VOS_UINT16                          i;
    USIM_REFRESH_FILE_STRU             *pstFile;
    USIMM_STKREFRESH_IND_STRU          *pstRefreshMsg;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    pstFile = VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, sizeof(USIM_REFRESH_FILE_STRU) * USIMM_MAX_REFRESH_FILE_NUM);

    if (VOS_NULL_PTR == pstFile)
    {
        USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: VOS_MemAlloc is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet(pstFile, 0, sizeof(USIM_REFRESH_FILE_STRU) * USIMM_MAX_REFRESH_FILE_NUM);
    /*lint +e534*/

    for (ulOffset=0; ulOffset<pstMsg->usLen; ulOffset+=ulTempLen)
    {
        /*获取当前EF的全路径内容*/
        if(VOS_OK != USIMM_GetRefreshEFPath(&pstMsg->aucFileList[ulOffset],
                                            pstMsg->usLen-ulOffset,
                                            aucRefreshFile,
                                            &ulTempLen))
        {
            USIMM_WARNING_LOG("USIMM_RefreshHandle: Fail to Get File");

            break;
        }

        /* 将U8类型的路径转成U16类型的路径，以获取文件ID */
        USIMM_ChangePathToU16(ulTempLen, aucRefreshFile, &ulPathLen, ausPath);

        /* pstFile[usEfNum].usFileId   = ausPath[ulPathLen - 1]; */

        /* 将U8类型的路径转成STRING类型的路径 */
        USIMM_ChangePathToAsciiString(aucRefreshFile, (VOS_UINT8)ulTempLen, (VOS_CHAR *)(&pstFile[usEfNum].aucPath[0]), &pstFile[usEfNum].usPathLen);

        usEfNum++;

        /* 解析出来的文件数超过最大值时跳出循环 */
        if (USIMM_MAX_REFRESH_FILE_NUM <= usEfNum)
        {
            USIMM_WARNING_LOG("USIMM_RefreshHandle: Refresh File too much");

            break;
        }
    }

    pstRefreshMsg = (USIMM_STKREFRESH_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                          (sizeof(USIMM_STKREFRESH_IND_STRU)-VOS_MSG_HEAD_LENGTH)\
                                                           + (usEfNum * sizeof(USIM_REFRESH_FILE_STRU)));

    if (VOS_NULL_PTR == pstRefreshMsg)
    {
        USIMM_ERROR_LOG("USIMM_RefreshFileIndHandle: VOS_AllocMsg is Failed");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstFile);
        /*lint +e534*/

        return;
    }

    pstRefreshMsg->stIndHdr.ulReceiverPid                   = MAPS_PIH_PID;
    pstRefreshMsg->stIndHdr.enMsgName                       = USIMM_STKREFRESH_IND;
    pstRefreshMsg->enRefreshType                            = USIMM_REFRESH_FILE_LIST;
    pstRefreshMsg->usEfNum                                  = usEfNum;

    /* 当前阶段所有的APP类型都是GUTL类型 */
    for (i = 0; i < usEfNum; i++)
    {
        pstRefreshMsg->astEfId[i].enAppType                 = USIMM_GUTL_APP;
        pstRefreshMsg->astEfId[i].usPathLen                 = pstFile[i].usPathLen;

        /* 多拷贝一个字节，把\0拷由过去 */
        /*lint -e534*/
        VOS_MemCpy(pstRefreshMsg->astEfId[i].aucPath, pstFile[i].aucPath, pstFile[i].usPathLen + 1);
        /*lint +e534*/

        if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstFile[i].usPathLen, (VOS_CHAR *)pstFile[i].aucPath, &enFileID))
        {
            pstRefreshMsg->astEfId[i].usFileId = USIMM_DEF_FILEID_BUTT;
        }
        else
        {
            pstRefreshMsg->astEfId[i].usFileId = (VOS_UINT16)enFileID;
        }
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pstFile);
    /*lint +e534*/

    /* 处理ISIM文件更新上报 */
    USIMM_RefreshIsimFileIndHandle(pstRefreshMsg);

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstRefreshMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_RefreshInd
功能描述  :Refresh命令上报指示处理函数
输入参数  :pstMsg:Refresh消息
输出参数  :无
返 回 值  :
修订记录  :
1. 日    期   : 2013年5月28日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_RefreshInd(USIMM_STKREFRESH_REQ_STRU *pstMsg)
{
    /* REFRESH命令中指示文件更新 */
    if(((USIMM_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType)||(USIMM_INITIAL_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType))
        &&(pstMsg->usLen != 0))
    {
        USIMM_RefreshFileIndHandle(pstMsg);
    }
    else
    {
        USIMM_RefreshNoFileIndHandle(pstMsg);
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_InitThirdSteps
功能描述  :初始化第三步根据对接形态初始化可选文件
输入参数  :无
输出参数  :无
返 回 值  :VOS_UINT32
修订记录  :
1. 日    期   : 2012年4月26日
   作    者   : w00184875
   修改内容   : AP-Modem锁网锁卡项目新增函数
*****************************************************************************/
VOS_UINT32 USIMM_InitThirdSteps(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU stSysAppCfg;

    /* 默认配置对接MP */
    stSysAppCfg.usSysAppConfigType = SYSTEM_APP_MP;

    if(NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stSysAppCfg, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_InitThirdSteps: Read en_NV_Item_System_APP_Config Failed");
    }

    if(SYSTEM_APP_ANDROID == stSysAppCfg.usSysAppConfigType)
    {
        return USIMM_InitCardOptionalFile(VOS_NULL_PTR);
    }

    return USIMM_SendInitCardMsg(WUEPS_PID_USIM, USIMM_INITCONTINUE_REQ);
}

/*****************************************************************************
函 数 名  :USIMM_SimRefreshFilePbAppCheck
功能描述  :检查SIM卡的文件变更路径是否为电话本相关
输入参数  :无
输出参数  :无
返 回 值  :VOS_UINT32
修订记录  :
1. 日    期   : 2013年05月30日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SimRefreshFilePbAppCheck(
    VOS_UINT16                         *pusFilePath,
    VOS_UINT32                          ulPathLen)
{
    if (pusFilePath[ulPathLen - 2] != DFTELCOM)
    {
        return VOS_FALSE;
    }

    if ((pusFilePath[ulPathLen - 1] == EFADN)
      ||(pusFilePath[ulPathLen - 1] == EFFDN)
      ||(pusFilePath[ulPathLen - 1] == EFBDN)
      ||(pusFilePath[ulPathLen - 1] == EFMSISDN))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_UsimRefreshFilePbAppCheck
功能描述  :检查USIM卡的文件变更路径是否为电话本相关
输入参数  :无
输出参数  :无
返 回 值  :VOS_UINT32
修订记录  :
1. 日    期   : 2013年05月30日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_UsimRefreshFilePbAppCheck(
    VOS_UINT16                         *pusFilePath,
    VOS_UINT32                          ulPathLen)
{
    VOS_UINT16                          ausUsimDfPhoneBookPath[3]   = {MF, 0, DFPHONEBOOK};
    VOS_UINT16                          uacUsimAppPath[]            = {MF, ADF};

    ausUsimDfPhoneBookPath[1] = gstUSIMMBaseInfo.stPBInfo.usPBDfID;/*文件ID是根据SIM卡配置而定*/

    /*对于电话本DF下的所有文件变更，无论是否是电话本管理的，都是通知电话本模块*/
    if (VOS_OK == VOS_MemCmp(ausUsimDfPhoneBookPath, pusFilePath, sizeof(ausUsimDfPhoneBookPath)))
    {
        return VOS_TRUE;
    }

    if (VOS_OK == VOS_MemCmp(uacUsimAppPath, pusFilePath, sizeof(uacUsimAppPath)))
    {
        if ((pusFilePath[ulPathLen - 1] == EFFDN)
          ||(pusFilePath[ulPathLen - 1] == EFBDN)
          ||(pusFilePath[ulPathLen - 1] == EFMSISDN))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/********************************************************************
  Function:     USIMM_RefreshFileAppCheck
  Description:  根据Refresh命令中的文件路径来解析其所处的类型
  Input:        VOS_UINT16 *pusFilePath:输入的文件路径
  Output:       USIMM_APP_TYPE_ENUM_UINT32 *penAppType：输出的应用类型
  Return:       无
  Others:
********************************************************************/
VOS_VOID USIMM_RefreshFileAppCheck(
    USIMM_APP_TYPE_ENUM_UINT32         *penAppType,
    VOS_UINT16                         *pusFilePath,
    VOS_UINT32                          ulPathLen)
{
    VOS_UINT16                          ausAttSimPath[]         =   {MF, DFATT};
    VOS_UINT16                          ausAttUsimPath[]        =   {MF, ADF, DFATT};
    VOS_UINT16                          ausSimDfGsmPath[]       =   {MF, DFGSM};
    VOS_UINT16                          ausSimDfTelcomPath[]    =   {MF, DFTELCOM};

    if (USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        if (VOS_OK == VOS_MemCmp(ausAttSimPath, pusFilePath, sizeof(ausAttSimPath)))
        {
            *penAppType =   USIMM_ATT_APP;
        }
        else
        {
            if (VOS_TRUE == USIMM_SimRefreshFilePbAppCheck(pusFilePath, ulPathLen))
            {
                *penAppType =   USIMM_PB_APP;
            }
            else
            {
                *penAppType =   USIMM_GSM_APP;
            }
        }
    }
    else
    {
        if (VOS_TRUE == USIMM_UsimRefreshFilePbAppCheck(pusFilePath, ulPathLen))
        {
            *penAppType =   USIMM_PB_APP;
        }
        else if (VOS_OK == VOS_MemCmp(ausAttUsimPath, pusFilePath, sizeof(ausAttUsimPath)))
        {
            *penAppType =   USIMM_ATT_APP;
        }
        else if (VOS_OK == VOS_MemCmp(ausSimDfGsmPath, pusFilePath, sizeof(ausSimDfGsmPath)))
        {
            *penAppType =   USIMM_GSM_APP;
        }
        else if (VOS_OK == VOS_MemCmp(ausSimDfTelcomPath, pusFilePath, sizeof(ausSimDfTelcomPath)))
        {
            *penAppType =   USIMM_GSM_APP;
        }
        else
        {
            *penAppType =   USIMM_UMTS_APP;
        }
    }

    return;
}

/********************************************************************
函 数 名  :USIMM_RefreshFileRead
功能描述  :REFRESH命令文件读取处理函数　
输入参数  :USIMM_STKREFRESH_REQ_STRU *pstMsg
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年04月20日
   作    者   : h59254
   修改内容   : Creat
********************************************************************/
VOS_VOID USIMM_RefreshFileRead(USIMM_STKREFRESH_REQ_STRU *pstMsg)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulTempLen = 0;
    VOS_UINT32                          ulPathLen = 0;
    VOS_UINT16                          ausPath[USIMM_MAX_PATH_LEN];/*当前文件路径，16进制*/
    VOS_UINT8                           aucRefreshFile[10];/*当前单一文件路径，8进制*/
    USIMM_GETCNF_INFO_STRU              stCnfInfo;
    VOS_UINT32                          ulResult;
    USIMM_GET_COMM_FILE_STRU            stFileInfo ;

    /*lint -e534*/
    VOS_MemSet(ausPath, 0, sizeof(ausPath));
    VOS_MemSet(aucRefreshFile, 0, sizeof(aucRefreshFile));
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    VOS_MemSet(&stFileInfo, 0, sizeof(stFileInfo));
    /*lint +e534*/

    for (ulOffset = 0; ulOffset < pstMsg->usLen; ulOffset += ulTempLen)
    {
        /*获取当前EF的全路径内容*/
        if (VOS_OK != USIMM_GetRefreshEFPath(&pstMsg->aucFileList[ulOffset],
                                             pstMsg->usLen-ulOffset,
                                             aucRefreshFile,
                                             &ulTempLen))
        {
            USIMM_WARNING_LOG("USIMM_RefreshFileRead: Fail to Get File");

            return;
        }

        USIMM_ChangePathToU16(ulTempLen,aucRefreshFile,&ulPathLen, ausPath);

        stFileInfo.enAppType    = USIMM_UNLIMIT_APP;
        stFileInfo.pusFilePath  = ausPath;
        stFileInfo.ulPathLen    = ulPathLen;
        stFileInfo.ucRecordNum  = USIMM_READ_ALLRECORD;

        ulResult = USIMM_GetFileFromCard(&stFileInfo, &stCnfInfo);

        if (VOS_OK != ulResult)
        {
            USIMM_WARNING_LOG("USIMM_RefreshFileRead: Fail to Get File");

            continue;
        }

        if (VOS_NULL_PTR != stCnfInfo.pucEf)
        {
            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_USIM, stCnfInfo.pucEf);
            /*lint +e534*/

            stCnfInfo.pucEf = VOS_NULL_PTR;
        }
    }

    USIMM_ClearCurFileInfo();   /*保障 MF 可以选到*/

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* end of #if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT) */
