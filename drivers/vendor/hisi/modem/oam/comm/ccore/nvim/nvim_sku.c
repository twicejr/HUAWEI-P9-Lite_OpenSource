/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: NVIM_Function.c                                                 */
/*                                                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2012-12-21                                                             */
/*                                                                           */
/* Description: implement NV subroutine                                      */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2012-12-21                                                       */
/*    Author: dongtinghuan                                                   */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/
#include "nvim_internalfunc.h"
#include "nvim_fileoperateinterface.h"
#include "NVIM_ResumeId.h"
#include "mdrv.h"
#include "NvIdList.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* Macro of log */
/*lint -e767 -e960 修改人:dongtinghuan 00105005;检视人:徐铖 51137;原因:Log打印 */
#define THIS_FILE_ID PS_FILE_ID_NVIM_SKU_C
/*lint +e767 +e960 修改人:dongtinghuan 00105005;检视人:徐铖 51137; */

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
extern VOS_CHAR g_acNvUpdateDir[];  /* update分区路径 */

extern VOS_CHAR g_acNvDefaultDir[]; /* default分区路径 */

extern VOS_CHAR g_acNvUpdateFile[];

#if (VOS_WIN32 == VOS_OS_VER)
VOS_CHAR        g_acNvUpdateForderName[]   = "Nvim\\NvimUp";
VOS_CHAR        g_acNvDefaultForderName[]  = "Nvim\\NvimDef";
#else
VOS_CHAR        g_acNvUpdateForderName[]   = "Nvim/NvimUp";
VOS_CHAR        g_acNvDefaultForderName[]  = "Nvim/NvimDef";
#endif

VOS_CHAR        g_acSpecBin[]              = "spec.bin";    /* 产品线开发人员增加的备份恢复NV项 */
const VOS_CHAR  g_acVercfgFile[]           = "vercfg.bin";  /* 该文件存在且非空 */
VOS_CHAR        g_acUserBin[]              = "user.bin";    /* 保存用户可以修改的NV项 */
VOS_CHAR        g_acOperatorFile[]         = "operator.xml"; /* 运营商配置文件 */

SKU_SWITCH_FLAG_STRU                g_stSkuSwitchFlag;      /* 运营商切换标记 */

NV_IMAGE_PATH_STRU                  g_stCurrentImagePath;   /* 当前Image路径 */

/*****************************************************************************
 函 数 名  : NV_GetDirectoryByPath
 功能描述  : 通过路径获取文件目录名
 输入参数  : pcPath:    文件夹路径
             ulModle:   目标文件夹所在层级
 输出参数  :
             pcDirName: 获取到的文件夹名称
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_GetDirectoryByPath(VOS_CHAR *pcPath, VOS_CHAR *pcDirName, VOS_UINT32 ulModle)
{
    VOS_UINT32                          ulLoop    = 0;
    VOS_UINT32                          ulResult  = VOS_ERR;
    VOS_CHAR                           *pcResult  = VOS_NULL_PTR;
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};
    VOS_CHAR                            acDilms[] = "/";

#if ( VOS_WIN32 == VOS_OS_VER )
    acDilms[0] = '\\';
#endif

    if (VOS_NULL_PTR == pcPath)
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(acFilePath, pcPath, VOS_StrLen(pcPath));
    /*lint +e534*/

    pcResult = VOS_StrTok(acFilePath, acDilms);
    while (VOS_NULL_PTR != pcResult)
    {
        if (ulModle == ulLoop)
        {
            /* lint -e534 */
            VOS_MemCpy(pcDirName, pcResult, VOS_StrLen(pcResult));
            /*lint +e534*/
            ulResult = VOS_OK;
            break;
        }
        ulLoop++;
        pcResult = VOS_StrTok(VOS_NULL_PTR, acDilms);
    }
    return ulResult;
}

/*****************************************************************************
 函 数 名  : NV_CheckImgWithCarrMatch
 功能描述  : 检查Image 和 运营商路径是否匹配
 输入参数  : pcCarrierDir: 运营商文件夹路径
             pcImageDir: Image文件夹路径

 输出参数  : 无

 返 回 值  : VOS_BOOL

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_BOOL NV_CheckImgWithCarrMatch(VOS_CHAR *pcCarrierDir, VOS_CHAR *pcImageDir)
{
    /* 参数长度检查 */
    if (NV_MIN_IMAGE_PATH_LEN > VOS_StrLen(pcImageDir))
    {
        NV_Printf("NV_CheckImageWithCarrierMatch: %s is not available path!\r\n", pcImageDir);
        return VOS_FALSE;
    }

    /* 如果 Image 长度大于Carrier长度，直接返回 */
    if ( VOS_StrLen(pcImageDir) >= VOS_StrLen(pcCarrierDir) )
    {
        NV_Printf("NV_CheckImageWithCarrierMatch: %s is not available path with %s!\r\n",
                   pcImageDir, pcCarrierDir);
        return VOS_FALSE;
    }

    /* Image匹配检查 */
    if (VOS_OK != VOS_StrNCmp(pcCarrierDir, pcImageDir, VOS_StrLen(pcImageDir)))
    {
        NV_Printf("#info:NV_CheckImageWithCarrierMatch: %s with %s not match!\r\n", pcCarrierDir, pcImageDir);
        return VOS_FALSE;
    }

    /* 匹配检查完毕，还需判断该运营商文件夹是否存在 */
    if(VOS_OK != NV_File_Exist(pcCarrierDir, VOS_NULL_PTR))
    {
        NV_Printf("NV_CheckImageWithCarrierMatch: Carrier path %s is not exist!\r\n", pcCarrierDir);
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NV_SwitchFlagPrintf
 功能描述  : 运营商切换标记打印
 输入参数  : pcFunctionName: 函数名字

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_VOID NV_SwitchFlagPrintf(VOS_CHAR *pcFunctionName)
{
   NV_Printf("%s:Switch Carrier flag: \r\n", pcFunctionName);
   NV_Printf("     acCurrentCarrierPath: %s \r\n", g_stSkuSwitchFlag.acCurrentCarrierPath);
   NV_Printf("     acSwitchCarrierPath: %s \r\n", g_stSkuSwitchFlag.acSwitchCarrierPath);
   NV_Printf("     ulCarrierSwitchFlag: %d \r\n", g_stSkuSwitchFlag.ulCarrierSwitchFlag);
   NV_Printf("Switch Image flag: \r\n     acCurrentImagePath: %s \r\n", g_stSkuSwitchFlag.acCurrentImagePath);
   NV_Printf("     acSwitchImagePath: %s \r\n", g_stSkuSwitchFlag.acSwitchImagePath);
   NV_Printf("     ulImageSwitchFlag: %d \r\n", g_stSkuSwitchFlag.ulImageSwitchFlag);
}

/*****************************************************************************
 函 数 名  : NV_StrcatFilePath
 功能描述  : 文件路径拼接
 输入参数  : pcSrc1: 文件夹路径
             pcSrc2: 文件名

 输出参数  : pcDest: 拼接后文件路径
 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_VOID NV_StrcatFilePath(VOS_CHAR *pcDest, VOS_CHAR* pcSrc1, VOS_CHAR* pcSrc2)
{
    /*lint -e534*/
    VOS_StrNCpy(pcDest, pcSrc1, VOS_StrLen(pcSrc1));
    /*lint +e534*/

    if (VOS_NULL_PTR != pcSrc2)
    {
        VOS_StrNCat(pcDest, pcSrc2, VOS_StrLen(pcSrc2));
    }

    return;
}

/*****************************************************************************
 函 数 名  : NV_ReadSwitchFlag
 功能描述  : 读取切换标记，存于全局变量中
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_VOID NV_ReadSwitchFlag(VOS_VOID)
{
    /* 读取切换标记 */
    /*lint -e534*/
    VOS_MemSet(&g_stSkuSwitchFlag, 0, sizeof(SKU_SWITCH_FLAG_STRU));
    /*lint +e534*/
    if (VOS_OK != DRV_READ_SWITCH_FLAG(&g_stSkuSwitchFlag))
    {
        /*lint -e534*/
        VOS_MemSet(&g_stSkuSwitchFlag, 0, sizeof(SKU_SWITCH_FLAG_STRU));

        NV_Printf("NV_ReadSwitchFlag: Read switch flag fail.\r\n");
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : NV_SkuGetOperatorPath
 功能描述  : 设置operator.xml路径
 输入参数  :

 输出参数  : pcFileName: operator.xml文件路径

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuGetOperatorPath(VOS_CHAR *pcFilePath)
{
    if (NV_MIN_CARRIER_PATH_LEN > VOS_StrLen(g_stSkuSwitchFlag.acCurrentCarrierPath))
    {
        NV_Printf("NV_SkuGetOperatorPath: Current carrier path is %s error.\r\n",
                    g_stSkuSwitchFlag.acCurrentCarrierPath);
        return VOS_ERR;
    }

    /* 拼接文件名称 */
    NV_StrcatFilePath(pcFilePath, g_stSkuSwitchFlag.acCurrentCarrierPath, g_acOperatorFile);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_SkuSetDefAndUpDir
 功能描述  : SKU形态 置升级分区路径和默认分区路径
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuSetDefAndUpDir(VOS_VOID)
{
    /* 获取当前Image路径 */
    /*lint -e534*/
    VOS_MemSet(&g_stCurrentImagePath, 0, sizeof(NV_IMAGE_PATH_STRU));
    /*lint +e534*/
    if (VOS_OK != DRV_GET_CURRENT_IMAGE_PATH(g_stCurrentImagePath.acImagePath))
    {
        NV_Printf("NV_SkuSetDefAndUpDir:Get current Image path from DRV return error.\r\n");
        return VOS_ERR;
    }

    if (NV_MAX_IMAGE_PATH_LEN < VOS_StrLen(g_stCurrentImagePath.acImagePath))
    {
        NV_Printf("NV_SkuSetDefAndUpDir:Get current Image path:%s fail from DRV .\r\n",
                   g_stCurrentImagePath.acImagePath);
        return VOS_ERR;
    }

    if (NV_MIN_IMAGE_PATH_LEN > VOS_StrLen(g_stCurrentImagePath.acImagePath))
    {
        NV_Printf("NV_SkuSetDefAndUpDir:Get current Image path:%s fail from DRV .\r\n",
                   g_stCurrentImagePath.acImagePath);
        return VOS_ERR;
    }

    /* 设置升级分区路径*/
    /*lint -e534*/
    VOS_MemSet(g_acNvUpdateDir, 0, NV_MAX_UPDEATE_PATH_LEN);
    /*lint +e534*/
    NV_StrcatFilePath(g_acNvUpdateDir, g_stCurrentImagePath.acImagePath, g_acNvUpdateForderName);

    /* 设置默认分区路径*/
    /*lint -e534*/
    VOS_MemSet(g_acNvDefaultDir, 0, NV_MAX_DEFAULT_PATH_LEN);
    /*lint +e534*/
    NV_StrcatFilePath(g_acNvDefaultDir, g_stCurrentImagePath.acImagePath, g_acNvDefaultForderName);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_CheckUpdateFlag
 功能描述  : SKU形态 升级标记检查，如不存在升级标记，拷贝默认区到升级区
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_CheckUpdateFlag(VOS_VOID)
{
    if (VOS_OK != NV_File_Exist(g_acNvUpdateDir, g_acNvUpdateFile))
    {
        /* 判断升级目录存在 NVupdate.bin */
        if (VOS_OK != NV_File_Exist(g_acNvDefaultDir, g_acNvUpdateFile))
        {
            NV_Printf("NV_CheckUpdateFlag: NV default Dir is not exist NvUpdate.bin.\r\n");
            return VOS_ERR;
        }

        /* 默认区拷贝到使用区 */
        if (NV_OK != NV_Xcopy((VOS_CHAR*)g_acNvDefaultDir, (VOS_CHAR*)g_acNvUpdateDir))
        {
            NV_Printf("NV_CheckUpdateFlag: NV_Xcopy %s to %s is failed.\r\n", g_acNvDefaultDir,g_acNvUpdateDir);

            return NV_SKU_XCOPY_UPDATE_FAIL;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_SkuRestoreNvFile
 功能描述  : SKU形态 各流程NV相关文件恢复
 输入参数  : bIsDefault: 特定文件是否需要恢复开关

 输出参数  : 无

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuRestoreNvFile(VOS_BOOL bIsDefault)
{
    /* 三个流程需要恢复文件图志
    ----------------------------------------------------------------
    |  流程\区别 |  流程 |  user.bin  |  spec.bin     |operator.xml|
    ---------------------------------------------------------------
    |NV 升级流程 |  恢复 |     √     |       √      |     ⅹ     |
    ----------------------------------------------------------------
    |NV 切换流程 |  恢复 |     √     |       √      |     √     |
    ----------------------------------------------------------------
    |恢复出厂设置|  恢复 |     ⅹ     |       √      |     √     |
    ----------------------------------------------------------------*/

    /* 只有升级和切换流程才恢复 user.bin */
    if (VOS_TRUE != bIsDefault)
    {
        /* 存在user恢复项，恢复运营商user.bin */
        if (VOS_OK != NV_SkuRestoreNvFileRead(g_acUserBin))
        {
            NV_Printf("NV_SkuRestoreNvFile: Sku Restore user.bin return error!");
            return VOS_ERR;
        }
    }
    else
    {
        /* 恢复出厂设置流程，删除当前运营商user.bin文件 */
        NV_File_Remove(g_stSkuSwitchFlag.acCurrentCarrierPath, g_acUserBin);
    }

    /* 所有恢复流程都需要恢复 spec.bin */
#if (0 < NV_RESUME_SKU_SPEC_ID_LIST_LEN)
    /* 如果版本自定义的NV项备份恢复大于0 */

    /* 恢复版本自定义恢复项 */
    if (VOS_OK != NV_SkuRestoreNvFileRead(g_acSpecBin))
    {
        NV_Printf("NV_SkuRestoreNvFile: Sku Restore spec.bin return error!");
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_SkuBackupNvFile
 功能描述  : SKU形态 NV相关文件备份
 输入参数  : 无

 输出参数  : 无

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuBackupNvFile(VOS_VOID)
{
   /* 三个流程需要备份文件图志
    ----------------------------------------------------------------
    |  流程\区别 |  流程 |  user.bin  |  spec.bin     |operator.xml|
    ---------------------------------------------------------------
    |NV 升级流程 |  备份 |     √     |       √      |     ⅹ     |
    ----------------------------------------------------------------
    |NV 切换流程 |  备份 |     √     |       √      |     ⅹ     |
    ----------------------------------------------------------------
    |恢复出厂设置|  备份 |     √     |       √      |     ⅹ     |
    ----------------------------------------------------------------*/

    /* 如果版本自定义的NV项备份恢复大于0 */
    /* 备份版本自定义备份项 */
     if (VOS_OK != NV_SkuBackupNvFileWrite(g_acSpecBin,
                                           NV_GetResumeNvIdNum(NV_SKU_ITEM),
                                           g_ausNvResumeSkuSpecIdList))
     {
        return VOS_ERR;
     }

    /* 存在user 备份项，备份运营商user.bin */
    if (VOS_OK != NV_SkuBackupNvFileWrite(g_acUserBin,
                                          NV_GetResumeNvIdNum(NV_USER_ITEM),
                                          g_ausNvResumeUserIdList))
     {
        return VOS_ERR;
     }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NV_SkuGetNvFilePath
 功能描述  : 获取user.bin 和 spec.bin路径
 输入参数  :

 输出参数  : pcFilePath: 存放路径地址
             pcFileName: 查询地址名称

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuGetNvFilePath(VOS_CHAR *pcFilePath, VOS_CHAR *pcFileName)
{
    if (VOS_OK == VOS_MemCmp(pcFileName, g_acUserBin, VOS_StrLen(g_acUserBin)))
    {
        /* user.bin */
        NV_StrcatFilePath(pcFilePath, g_stSkuSwitchFlag.acCurrentCarrierPath, pcFileName);
        return VOS_OK;
    }

    if (VOS_OK == VOS_MemCmp(pcFileName, g_acSpecBin, VOS_StrLen(g_acSpecBin)))
    {
        /* spec.bin */
        NV_StrcatFilePath(pcFilePath, g_stCurrentImagePath.acImagePath, pcFileName);
        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 函 数 名  : NV_SkuRestoreNvFileRead
 功能描述  : 单sku NV .bin恢复
 输入参数  : pcfileName: 文件名称

 输出参数  : 无

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuRestoreNvFileRead(VOS_CHAR *pcFileName)
{
    FILE                               *pFile       = VOS_NULL_PTR;
    NV_SKU_DATA_INFO_STRU              *pstNvSkuDataInfo;
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};
    VOS_CHAR                           *pcFileContent;
    VOS_UINT32                          ulLength    = 0;
    VOS_UINT32                          uloffset    = 0;
    VOS_UINT32                          ulRest      = VOS_OK;
    VOS_UINT32                          ulDilms    = 0x5A5A5A5A;

    /* 获取文件地址 */
    if (VOS_OK != NV_SkuGetNvFilePath(acFilePath, pcFileName))
    {
        NV_Printf("NV_SkuRestoreNvFileRead: Get Restore NV File path error!: %s", acFilePath);
        return VOS_ERR;
    }

    /* 判断文件是否存在 */
    if (VOS_OK != NV_File_Exist(acFilePath, VOS_NULL_PTR))
    {
        NV_Printf("NV_SkuRestoreNvFileRead:%s file is not exist.\r\n", pcFileName);
        return VOS_OK;
    }

    /* 打开文件 */
    pFile = NV_File_Open(acFilePath, NV_FILE_OPEN_MODE_R);
    if (VOS_NULL_PTR == pFile)
    {
        NV_Printf("NV_SkuRestoreNvFileRead:Open %s file fail.\r\n", pcFileName);
        return VOS_ERR;
    }

    /* 重定位流上的文件内部位置指针*/
    NV_File_Seek(pFile, 0, NV_FILE_SEEK_END);

    ulLength = (VOS_UINT32)NV_File_Tell(pFile);
    if (0 == ulLength)
    {
        /* 文件异常 */
        NV_Printf("NV_SkuRestoreNvFileRead:file lenth is 0.\r\n");
        NV_File_Close(pFile);
        return VOS_ERR;
    }

    pcFileContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM, DYNAMIC_MEM_PT, ulLength);

    if(VOS_NULL_PTR == pcFileContent)
    {
        NV_Printf("NV_SkuRestoreNvFileRead:Alloc buffer fail.\r\n");
        NV_File_Close(pFile);
        return VOS_ERR;
    }

    NV_File_Seek(pFile, 0, NV_FILE_SEEK_SET);

    NV_File_Read(pcFileContent, ulLength, 1, pFile);

    /* 内容解析 */
    while (uloffset < ulLength)
    {
        /* 解析出 NV ID */
        pstNvSkuDataInfo = (NV_SKU_DATA_INFO_STRU *)(pcFileContent + uloffset);

        uloffset += sizeof(NV_SKU_DATA_INFO_STRU) + pstNvSkuDataInfo->usNvLength - sizeof(VOS_UINT32);

        /* 保护性代码 */
        if(ulLength < uloffset)
        {
            NV_Printf("NV_SkuRestoreNvFileRead:offset:%d > file lenth:%d error.\r\n", uloffset, ulLength);
            ulRest = VOS_ERR;
            break;
        }

        if (VOS_OK != VOS_MemCmp((pcFileContent + uloffset), &ulDilms, sizeof(VOS_UINT32)))
        {
            NV_Printf("NV_SkuRestoreNvFileRead:%s content error.\r\n");
            ulRest = VOS_ERR;
            break;
        }

        /* 解析出NV项值写入NV使用区 */

        if (VOS_OK != NV_WriteDirectAll(pstNvSkuDataInfo->usNvId, (VOS_VOID*)pstNvSkuDataInfo->aucData, pstNvSkuDataInfo->usNvLength))
        {
            NV_Printf("NV_SkuRestoreNvFileRead:NV Restore Write fail.\r\n");
            ulRest = VOS_ERR;
            break;
        }

        uloffset += sizeof(VOS_UINT32);

    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, pcFileContent);
    /*lint +e534*/
    NV_File_Close(pFile);

    return ulRest;
}

/*****************************************************************************
 函 数 名  : NV_SkuOpenNvFile
 功能描述  : 文件操作
 输入参数  : pcfileName: 需要打开文件名称

 输出参数  : 无

 返 回 值  : FILE

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
FILE * NV_SkuOpenNvFile(VOS_CHAR *pcFileName)
{
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};

    if (VOS_NULL_PTR == pcFileName)
    {
        NV_Printf("NV_SkuOpenNvFile:para error.\r\n");
        return VOS_NULL_PTR;
    }

    /* 获取文件地址 */
    if (VOS_OK != NV_SkuGetNvFilePath(acFilePath, pcFileName))
    {
        NV_Printf("NV_SkuOpenNvFile: Open NV File Name fail!: %s", pcFileName);
        return VOS_NULL_PTR;
    }

    /* 判断文件是否存在 */
    if (VOS_OK == NV_File_Exist(acFilePath, VOS_NULL_PTR))
    {
        NV_Printf("#info:NV_SkuOpenNvFile:%s file is exist.\r\n", pcFileName);
        NV_File_Remove(acFilePath, VOS_NULL_PTR);
    }

    /* 打开文件 */
    return NV_File_Open(acFilePath, NV_FILE_OPEN_MODE_NEW_RW);

}

/*****************************************************************************
 函 数 名  : NV_SkuBackupNvFileWrite
 功能描述  : 单sku NV .bin备份
 输入参数  : pcfileName: 需要备份文件名称
             ulNvNum   : 需要备份NV ID数量
             pusNvId   : NV ID 列表

 输出参数  : 无

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuBackupNvFileWrite(VOS_CHAR *pcFileName, VOS_UINT32 ulNvNum, VOS_UINT16 *pusNvId)
{
    FILE                               *pFile      = VOS_NULL_PTR;
    NV_SKU_DATA_INFO_STRU              *pstSkuDataInfo;
    VOS_UINT32                          ulNvLength = 0;
    VOS_UINT32                          ulRest     = VOS_OK;
    VOS_UINT32                          ulDilms    = 0x5A5A5A5A; /* 分隔符 0x5A5A5A5A */
    VOS_UINT32                          i;

    if (0 == ulNvNum)
    {
        NV_Printf("NV_SkuBackupNvFileWrite: #info :no nv id restore.\r\n");
        return VOS_OK;
    }

    /* 打开文件 */
    pFile = NV_SkuOpenNvFile(pcFileName);
    if (VOS_NULL_PTR == pFile)
    {
        NV_Printf("NV_SkuBackupNvFileWrite:opern %s file fail.\r\n", pcFileName);
        return VOS_ERR;
    }

    for (i = 0; i< ulNvNum; i++)
    {
        ulRest = NV_GetLength(pusNvId[i], &ulNvLength);
        if (VOS_OK != ulRest)
        {
            /* ID 不存在 */
            NV_Printf("NV_SkuBackupNvFileWrite:NV ID NO.%d not exist.\n", pusNvId[i]);
            break;
        }

        /* 分隔符的内存一起申请 */
        pstSkuDataInfo = (NV_SKU_DATA_INFO_STRU*)VOS_MemAlloc(
                                                 WUEPS_PID_OM,
                                                 DYNAMIC_MEM_PT,
                                                 sizeof(NV_SKU_DATA_INFO_STRU) + ulNvLength);

        if(VOS_NULL_PTR == pstSkuDataInfo)
        {
            NV_Printf("NV_SkuBackupNvFileWrite:Alloc buffer fail\n");
            ulRest = VOS_ERR;
            break;
        }

        /* NV 读取 */
        ulRest = NV_ReadEx(MODEM_ID_0, pusNvId[i], pstSkuDataInfo->aucData, ulNvLength);
        if(NV_OK != ulRest)
        {
            NV_Printf("NV_SkuBackupNvFileWrite:NV Read fail.\r\n");
            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_OM, pstSkuDataInfo);
            /*lint +e534*/
            break;
        }

        pstSkuDataInfo->usNvId     = pusNvId[i];
        pstSkuDataInfo->usNvLength = (VOS_UINT16)ulNvLength;

        /* 加上分割符 */
        /*lint -e534*/
        VOS_MemCpy((pstSkuDataInfo->aucData + ulNvLength), &ulDilms, sizeof(VOS_UINT32));
        /*lint +e534*/

        /* 写入对应的NV 文件中 */
        NV_File_Write(pstSkuDataInfo, sizeof(VOS_UINT8),
                      (sizeof(NV_SKU_DATA_INFO_STRU) + ulNvLength),
                      pFile);

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_OM, pstSkuDataInfo);
        /*lint +e534*/
    }

    NV_File_Close(pFile);
    return ulRest;

}

/*****************************************************************************
 函 数 名  : NV_SwitchAvailCarr
 功能描述  : 查找可用运营商并发起切换
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SwitchAvailCarr(VOS_VOID)
{
    NV_CARRIER_PATH_STRU                stCarrierPath;
    VOS_UINT32                          ulCarrierPathLen;

    /* 查询可用运营商配置文件路径 */
    ulCarrierPathLen = NV_MAX_CARRIER_PATH_LEN;
    /*lint -e534*/
    VOS_MemSet(&stCarrierPath, 0, sizeof(NV_CARRIER_PATH_STRU));
    /*lint +e534*/
    if (VOS_OK != DRV_GET_AVAILABLE_CARRIER_PATH(stCarrierPath.acCarrierPath, &ulCarrierPathLen))
    {
        NV_Printf("NV_SwitchAvailCarr:Get Available Carrier path from DRV error.\r\n");
        return VOS_ERR;
    }

    /* 查询结果检查 */
    if ((NV_MAX_CARRIER_PATH_LEN < ulCarrierPathLen)||
        (NV_MIN_CARRIER_PATH_LEN > ulCarrierPathLen))
    {
        NV_Printf("NV_SwitchAvailCarr:Carrier path error, lenth %d !\r\n", ulCarrierPathLen);
        return VOS_ERR;
    }

    /* 设置当前运营商 */
    /*lint -e534*/
    VOS_MemCpy(g_stSkuSwitchFlag.acCurrentCarrierPath,
               stCarrierPath.acCarrierPath,
              (sizeof(stCarrierPath.acCarrierPath)));
    /*lint +e534*/

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : NV_SelectCarrier
 功能描述  : 选择切换运营商
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SelectCarrier(VOS_VOID)
{
    /* 切换标记读取 */
    NV_ReadSwitchFlag();

    /* 打印切换标记位信息 */
    NV_SwitchFlagPrintf("NV_SelectCarrier");

    /* 切换标记不存在 */
    if (VOS_TRUE != g_stSkuSwitchFlag.ulCarrierSwitchFlag)
    {
        /* 尝试启动运营商匹配检查 */
        if (VOS_TRUE == NV_CheckImgWithCarrMatch(g_stSkuSwitchFlag.acCurrentCarrierPath,
                                                 g_stCurrentImagePath.acImagePath))
        {
            return VOS_OK;
        }

        NV_Printf("NV_SelectCarrier:Switch carrier flag is 0,but Current carrier not match:%s with %s.\r\n",
                    g_stSkuSwitchFlag.acCurrentCarrierPath, g_stCurrentImagePath.acImagePath);

        /* 查找可用运营商发起切换，尽可能让单板启动 */
        if (VOS_OK != NV_SwitchAvailCarr())

        {
            NV_Printf("NV_SelectCarrier:Switch carrier flag is 0, Get Available Carrier fail.\r\n");
            return VOS_ERR;
        }
    }
    else
    {
        /* 切换标记存在 判断待切换运营商和Image是否匹配 */
        if (VOS_TRUE != NV_CheckImgWithCarrMatch(g_stSkuSwitchFlag.acSwitchCarrierPath,
                                                 g_stCurrentImagePath.acImagePath))
        {
            NV_Printf("NV_SelectCarrier:Switch carrier flag is 1,but Switch carrier not match:%s with %s.\r\n",
                g_stSkuSwitchFlag.acSwitchCarrierPath, g_stCurrentImagePath.acImagePath);

            /* 查找可用运营商发起切换，尽可能让单板启动 */
            if (VOS_OK != NV_SwitchAvailCarr())
            {
                NV_Printf("NV_SelectCarrier:Switch carrier flag is 1, Get Available Carrier fail.\r\n");
                return VOS_ERR;
            }
        }
        else
        {
            /* 设置当前运营商 */
            /*lint -e534*/
            VOS_MemCpy(g_stSkuSwitchFlag.acCurrentCarrierPath,
                       g_stSkuSwitchFlag.acSwitchCarrierPath,
                       sizeof(g_stSkuSwitchFlag.acSwitchCarrierPath));
            /*lint +e534*/
        }
    }

    /* 升级标记检查 */
    if (VOS_OK != NV_CheckUpdateFlag())
    {
        NV_Printf("NV_SelectCarrier:NV Check Update Flag fail.\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_SkuSwitchProc
 功能描述  : 运营商切换流程
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuSwitchProc()
{
    /* 运营商升级分区和默认认分区路径设置 */
    if (VOS_OK != NV_SkuSetDefAndUpDir())
    {
        NV_Printf("NV_SkuSwitchProc:Set carrier default and update path fail.\r\n");
        return VOS_ERR;
    }

    /* 运营商选择 */
    if (VOS_OK != NV_SelectCarrier())
    {
        NV_Printf("NV_SkuSwitchProc:Select carrier return fail.\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_SkuUpdateSwitchFlag
 功能描述  : 更新切换标记
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SkuUpdateSwitchFlag()
{
    /* 更新当前切换标识 */
    /*lint -e534*/
    VOS_MemSet(g_stSkuSwitchFlag.acSwitchCarrierPath, 0, sizeof(g_stSkuSwitchFlag.acSwitchCarrierPath));
    /*lint +e534*/

    g_stSkuSwitchFlag.ulCarrierSwitchFlag = VOS_FALSE;

    if (VOS_OK != DRV_WRITE_SWITCH_FLAG(&g_stSkuSwitchFlag))
    {
        /* Log记录 */
        NV_Printf("NV_SkuUpdateSwitchFlag:Write switch flag fail.\r\n");
        return NV_SKU_WRITE_SWITCH_FALG_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : NV_SetSwitchCarrierFlag
 功能描述  : 设置运营商切换标记
 输入参数  : pcCarrierPath:    待切换运营商路径
             ulCarrierPathLen: 待切换运营商路径长度
             pbIsSwitchImage : 是否需要切换Image

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SetSwitchCarrierFlag(
    VOS_CHAR                           *pcCarrierPath,
    VOS_UINT32                          ulCarrierPathLen,
    VOS_BOOL                           *pbIsSwitchImage)
{
    VOS_CHAR                            acImageName[NV_MAX_IMAGE_NAME_LEN + 1] = {0};

    /* 参数检查 */
    if ((VOS_NULL_PTR == pcCarrierPath)
        || (0 == ulCarrierPathLen)
        || (NV_MAX_CARRIER_PATH_LEN < ulCarrierPathLen))
    {
        NV_Printf("NV_SetSwitchCarrierFlag:para is error: %s, length %d.\r\n",
                    pcCarrierPath, ulCarrierPathLen);
        return NV_SKU_CARRIER_PARA_ERR;
    }

    /* 当前运营商NV备份 */
    if (NV_OK != NV_ExNoBackup())
    {
        /* 备份失败 */
        NV_Printf("NV_SetSwitchCarrierFlag:Carrier:%s NV Backup fail.\r\n",
                    pcCarrierPath);
        return NV_SKU_CARRIER_NV_BACKUP_ERR;
    }

    /* 判断Image是否需要切换 */
    if (VOS_TRUE !=  NV_CheckImgWithCarrMatch(pcCarrierPath,
                                              g_stCurrentImagePath.acImagePath))
    {
        /* 获取需要切换Image名字 */
        if (VOS_OK != NV_GetDirectoryByPath(pcCarrierPath,
                                            acImageName,
                                            NV_SKU_IMAGE_PATH_LEVEL))
        {
            NV_Printf("NV_SetSwitchCarrierFlag:Get directory by path %s fail.\r\n",
                        g_stCurrentImagePath.acImagePath);
            return VOS_ERR;

        }

        /*lint -e534*/
        VOS_MemSet(g_stSkuSwitchFlag.acSwitchImagePath, 0, sizeof(g_stSkuSwitchFlag.acSwitchImagePath));
        /*lint +e534*/

        /* 获取底软Image路径方便直接写入标记文件中 */
        if (VOS_OK != DRV_GET_IMAGE_PATH(acImageName, g_stSkuSwitchFlag.acSwitchImagePath))
        {
             NV_Printf("NV_SetSwitchCarrierFlag:Get Switch Image path from drv fail. ImageName:%s, Getpath:%s\r\n",
                        acImageName, g_stSkuSwitchFlag.acSwitchImagePath);
             return VOS_ERR;
        }

        /* 置Image切换标记 */
        g_stSkuSwitchFlag.ulImageSwitchFlag = VOS_TRUE;

        *pbIsSwitchImage = VOS_TRUE;

    }

    /* 记录待切换运营商路径 */
    /*lint -e534*/
    VOS_MemCpy(g_stSkuSwitchFlag.acSwitchCarrierPath, pcCarrierPath, VOS_StrLen(pcCarrierPath)+ 1);
    /*lint +e534*/

    /* 置运营商切换标记 */
    g_stSkuSwitchFlag.ulCarrierSwitchFlag = VOS_TRUE;

    /* 更新当前切换标识 */
    if (VOS_OK != DRV_WRITE_SWITCH_FLAG(&g_stSkuSwitchFlag))
    {
        /* Log记录 */
        NV_Printf("NV_SetSwitchCarrierFlag:Write switch flag fail.\r\n");
        return NV_SKU_WRITE_SWITCH_FALG_ERR;
    }

    return VOS_OK;
}

#endif

/*****************************************************************************
 函 数 名  : NV_SwitchCarrier
 功能描述  : 切换运营商(对外提供切换运营商接口)
 输入参数  : pcCarrierName   : 待切换运营商名称
             ulCarrierNameLen: 待切换运营商名称长度
             pbIsSwitchImage : 是否需要切换Image

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : d00212987
    修改内容   : 单SKU支持多运营商项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SwitchCarrier(
    VOS_CHAR                           *pcCarrierName,
    VOS_UINT32                          ulCarrierNameLen,
    VOS_BOOL                           *pbIsSwitchImage)
{
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

    NV_CARRIER_PATH_STRU                stCarrierPath;
    VOS_UINT32                          ulCarrierPathLen = 0;
    VOS_CHAR                            aucCarrierName[NV_MAX_CARRIER_NAME_LEN] = {0};
    VOS_UINT32                          ulRest;

    /* 参数检查 */
    if ((VOS_NULL_PTR == pcCarrierName)
        || (0 == ulCarrierNameLen)
        || (NV_MAX_CARRIER_NAME_LEN < ulCarrierNameLen))
    {
        NV_Printf("NV_SwitchCarrier:para is error: %s, length %d.\r\n",
                    pcCarrierName, ulCarrierNameLen);
        return NV_SKU_CARRIER_PARA_ERR;
    }

    /* 打印切换标记位信息 */
    NV_SwitchFlagPrintf("NV_SwitchCarrier");

    /* 获取当前运营商目录 */
    if (VOS_OK != NV_GetDirectoryByPath(g_stSkuSwitchFlag.acCurrentCarrierPath,
                                        aucCarrierName,
                                        NV_SKU_CARRIER_PATH_LEVEL))
    {
        NV_Printf("NV_SwitchCarrier:Get directory by path %s, Level:%d fail.\r\n",
                    g_stSkuSwitchFlag.acCurrentCarrierPath, NV_SKU_CARRIER_PATH_LEVEL);

        return NV_GET_CURRENT_CARRIER_NAME_ERR;
    }

    /* 判断是否是切换到当前运营商 */
    if (VOS_OK == VOS_StrNCmp(aucCarrierName, pcCarrierName, ulCarrierNameLen))
    {
        /* 当前运营商不用切换 */
        return VOS_OK;
    }

    /*lint -e534*/
    VOS_MemSet(&stCarrierPath, 0, sizeof(NV_CARRIER_PATH_STRU));
    /*lint +e534*/

    /* 查询目标运营商配置文件路径 */
    if (VOS_OK != DRV_GET_CARRIER_PATH(pcCarrierName,
                                       ulCarrierNameLen,
                                       stCarrierPath.acCarrierPath,
                                       &ulCarrierPathLen))
     {
        NV_Printf("NV_SwitchCarrier:Get Carrier path from DRV fail.\r\n");

        return NV_SKU_GET_CARRIER_PATH_ERR;
     }

    /* 置切换标记 */
    ulRest = NV_SetSwitchCarrierFlag(stCarrierPath.acCarrierPath,
                                     ulCarrierPathLen, pbIsSwitchImage);
    if (VOS_OK != ulRest)
    {
        NV_Printf("NV_SwitchCarrier:Set Switch carrier falg fail! return %d.\r\n",
                    ulRest);
        return ulRest;
    }

#endif

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus

        }
    #endif
#endif


