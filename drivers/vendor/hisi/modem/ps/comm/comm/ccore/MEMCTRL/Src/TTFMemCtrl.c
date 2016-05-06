/******************************************************************************
  Copyright    : 2005-2011, Huawei Tech. Co., Ltd.
  File name    : TtfMemCtrl.c
  Author       : h00163499
  Version      : V900R001
  Date         : 2012-12-24
  Description  : TTF内存地址管理
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2012-12-24
     Author:h00163499
     Modification:Create

******************************************************************************/


/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "TTFMemCtrl.h"
#include "mdrv.h"
#include "TTFMemInterface.h"
#include "PhyNvDefine.h"
#include "TTFComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e534*/
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_MEMCTRL_C

/******************************************************************************
   2 宏定义
******************************************************************************/


/*****************************************************************************
   函数声明
*****************************************************************************/

/*****************************************************************************
   全局变量定义
*****************************************************************************/
TTF_MEMCTRL_ADDR_STRU                   g_stTtfMemCtrlAddr =
{
    /* stTtfMemCtrlAddrComm */
    {
        /* ucInitFlg */
        VOS_NULL,
        /* aucRsv[3] */
        {VOS_NULL, VOS_NULL, VOS_NULL}
    },
    /* astTtfMemCtrlAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    }
};

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

/* three modems */
#if ( 3 == MULTI_MODEM_NUMBER )
/*  TTF动态内存维护实体 */
TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity =
{
    /* ulWRfRxEVMTestEn */
    VOS_NO,
    /* ulTtfMemDynamicInitAddrFlag */
    VOS_NULL,
    /* ulMemTotalLen */
    VOS_NULL,
    /* astModelSupport */
    {
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        },
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        },
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        }
    },
    /* astTtfMemAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    },
    /* pucTtfMemBaseAddr */
    VOS_NULL_PTR
};

/* two modems */
#else
/*  TTF动态内存维护实体 */
TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity =
{
    /* ulWRfRxEVMTestEn */
    VOS_NO,
    /* ulTtfMemDynamicInitAddrFlag */
    VOS_NULL,
    /* ulMemTotalLen */
    VOS_NULL,
    /* astModelSupport */
    {
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        },
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        }
    },
    /* astTtfMemAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    },
    /* pucTtfMemBaseAddr */
    VOS_NULL_PTR
};
#endif

/* only one modem */
#else
/*  TTF动态内存维护实体 */
TTF_MEM_DYNAMIC_CTRL_ENTITY_STRU        g_stTtfMemDynamicCtrlEntity =
{
    /* ulWRfRxEVMTestEn */
    VOS_NO,
    /* ulTtfMemDynamicInitAddrFlag */
    VOS_NULL,
    /* ulMemTotalLen */
    VOS_NULL,
    /* astModelSupport */
    {
        {
            /* enSupportWcdma */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportGsm */
            TTF_MEMCTRL_MODEL_SUPPORT_YES,
            /* enSupportLte */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportTds */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupport1X */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* enSupportEvdo */
            TTF_MEMCTRL_MODEL_SUPPORT_NO,
            /* aucRsv */
            {VOS_NULL, VOS_NULL}
        }
    },
    /* astTtfMemAddrType */
    {
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        },
        {
            /* ulAttribute */
            VOS_NULL,
            /* ulLen */
            VOS_NULL,
            /* ulOffsetBaseLen */
            VOS_NULL
        }
    },
    /* pucTtfMemBaseAddr */
    VOS_NULL_PTR
};

#endif

/* BBPMST头部TB块信息 */
WTTF_MACDL_BBPMST_TB_HEAD_STRU          g_stBbpMstTBHeadInfo = {440, 40};

TTF_MEM_SOLUTION_CFG_NV_STRU            g_stTtfMemSolution;


/******************************************************************************
   6 函数实现
******************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_ModelSupport
 功能描述  : 读取NV_PLATFORM_RAT_CAP，判断是否支持wcdma
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史   :
 1.日    期 : 2014年03月12日
 作    者   : c00212970
 修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_ModelSupport(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                              ulResult;
    PLATAFORM_RAT_CAPABILITY_STRU           stPlatformRat;
    VOS_UINT32                              ulLoop;

    if (MODEM_ID_BUTT <= enModemId)
    {
       (VOS_VOID)vos_printf("TTF_MEMCTRL_ModelSupport::Invalid ModemId:%d\n", enModemId);
        enModemId = MODEM_ID_0;
    }

    TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_NO);
    TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_NO);

    /* Read the NV Config Value */
    ulResult = NV_ReadEx(   enModemId,
                            en_NV_Item_Platform_RAT_CAP,
                            &stPlatformRat,
                            sizeof(PLATAFORM_RAT_CAPABILITY_STRU) );

    /* Read NV Content is Failed , Configed the Vaule By Default Value */
    if ( VOS_OK != ulResult )
    {
        /* 读取NV失败，则按照默认支持wcdma处理 */
        (VOS_VOID)vos_printf("TTF_MEMCTRL_ModelSupport::read platform RAT capability fail\n");

        TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_LTE(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_TDS(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_1X(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_EVDO(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);

        return;
    }

    /* 有效性检查，如果平台支持的接入技术个数为0，或者usRatNum大于接入技术最大值，返回支持WCDMA */
    if ((0 == stPlatformRat.usRatNum) || (stPlatformRat.usRatNum > PLATFORM_MAX_RAT_NUM))
    {
        (VOS_VOID)vos_printf("TTF_MEMCTRL_ModelSupport::RatNum error! usRatNum: %d\n", stPlatformRat.usRatNum);

        TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_LTE(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_TDS(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_1X(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        TTF_MEM_SET_SUPPORT_EVDO(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);

        return;
    }

    /* 遍历aenRatList, 查看是否支持 */
    for ( ulLoop = 0; ulLoop < stPlatformRat.usRatNum; ulLoop++ )
    {
        if ( PLATFORM_RAT_WCDMA == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_WCDMA(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else if ( PLATFORM_RAT_GSM == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_GSM(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else if ( PLATFORM_RAT_LTE == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_LTE(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else if ( PLATFORM_RAT_TDS == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_TDS(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else if ( PLATFORM_RAT_1X == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_1X(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else if ( PLATFORM_RAT_HRPD == stPlatformRat.aenRatList[ulLoop] )
        {
            TTF_MEM_SET_SUPPORT_EVDO(enModemId, TTF_MEMCTRL_MODEL_SUPPORT_YES);
        }
        else
        {
            /* pclint */
        }
    }

    return ;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetBBPMemLen
 功能描述  : 读取nv项en_NV_Item_WTTF_MACDL_BBPMST_TB_HEAD_Config中内容，
             根据其中内容计算出BBP master所需用的内存大小（头部和数据部分大小）
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32 - BBP master所需要的内存大小，单位byte
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_ReadBBPMemConfig(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulResult;

    if (TTF_MEMCTRL_MODEL_SUPPORT_NO == TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0))
    {
        return ;
    }

    /*Read the NV Config Value*/
    ulResult = NV_ReadEx(   MODEM_ID_0,
                            en_NV_Item_WTTF_MACDL_BBPMST_TB_HEAD_Config,
                            &g_stBbpMstTBHeadInfo,
                            sizeof(WTTF_MACDL_BBPMST_TB_HEAD_STRU));

    /*Read NV Content is Failed , Configed the Vaule By Default Value*/
    if ( VOS_OK != ulResult )
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "read BBPMaster NV TB head config fail!\n");

#if (FEATURE_ON == FEATURE_MMU_MEDIUM)
        g_stBbpMstTBHeadInfo.ulTBHeadNum            = 440;
        g_stBbpMstTBHeadInfo.ulTBHeadReserved       = 40;
#else
        g_stBbpMstTBHeadInfo.ulTBHeadNum            = 220;
        g_stBbpMstTBHeadInfo.ulTBHeadReserved       = 20;
#endif
    }

    return ;

}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_ReadNvCfg
 功能描述  : 读取NV配置
 输入参数  : TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution
 输出参数  : 无
 返 回 值  : PS_SUCC, PS_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : x00138766
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TTF_MEMCTRL_ReadNvCfg(TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution)
{
    VOS_UINT32                     ulRet;
    VOS_UINT8                      ucLoop;
    VOS_UINT8                      ucClusterNum;
    VOS_UINT8                      ucClusterLoop;
    TTF_MEM_POOL_CFG_NV_STRU      *pstPoolCfg;

    /*读取TTF内存方案*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_TTF_MEM_SOLUTION_CFG, pstTtfMemSolution , sizeof(TTF_MEM_SOLUTION_CFG_NV_STRU));
    if (NV_OK != ulRet)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Read NV FAIL, Error Code <1>\n", (VOS_INT32)ulRet);
        return PS_FAIL;
    }

    if (TTF_MEM_POOL_ID_BUTT != pstTtfMemSolution->ucPoolCnt)
    {
        TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Pool Num Error \n");
        return PS_FAIL;
    }

    /*检查各内存池各cluster是否正确*/
    for (ucLoop = 0; ucLoop < pstTtfMemSolution->ucPoolCnt; ucLoop++)
    {
        pstPoolCfg   = &pstTtfMemSolution->astTtfMemPoolCfgInfo[ucLoop];
        ucClusterNum = pstPoolCfg->ucClusterCnt;

        if (ucClusterNum > TTF_MEM_MAX_CLUSTER_NUM)
        {
            TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Cluster Num Error \n");
            return PS_FAIL;
        }

        for(ucClusterLoop = 0 ; ucClusterLoop < ucClusterNum ; ucClusterLoop++)
        {
            if (pstPoolCfg->ausBlkSize[ucClusterLoop] > TTF_MEM_BLK_MAX_BYTE_LEN)
            {
                TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_ERROR, "TTF_MemReadNvCfg Fail, Memory Size Error \n");
                return PS_FAIL;
            }
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_MemNvCfgTotalLength
 功能描述  : 计算内存配置所需长度
 输入参数  : TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution
 输出参数  : 无
 返 回 值  : 长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : x00138766
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TTF_MEMCTRL_MemNvCfgTotalLength(TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution)
{
    TTF_MEM_POOL_CFG_NV_STRU      *pstPoolCfg;
    VOS_UINT8                 ucLoop;
    VOS_UINT8                 ucClusterNum;
    VOS_UINT8                 ucClusterLoop;
    VOS_UINT32                ulTotalLength = 0;

    /*检查各内存池各cluster是否正确*/
    for (ucLoop = 0; ucLoop < pstTtfMemSolution->ucPoolCnt; ucLoop++)
    {
        pstPoolCfg   = &pstTtfMemSolution->astTtfMemPoolCfgInfo[ucLoop];
        ucClusterNum = pstPoolCfg->ucClusterCnt;

        for(ucClusterLoop = 0 ; ucClusterLoop < ucClusterNum ; ucClusterLoop++)
        {
            ulTotalLength += pstPoolCfg->ausBlkSize[ucClusterLoop] * pstPoolCfg->ausBlkCnt[ucClusterLoop];
        }
    }

    return ulTotalLength;
}

/*****************************************************************************
 函 数 名  : TTF_MemSetDefaultNvCfg
 功能描述  : 设置默认NV配置(V9R1版本)
 输入参数  : TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : x00138766
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MemSetDefaultNvCfg(TTF_MEM_SOLUTION_CFG_NV_STRU *pstTtfMemSolution)
{
    const   VOS_UINT8   ucPoolMask  = 0x16;

    pstTtfMemSolution->ucPoolCnt    = TTF_MEM_MAX_POOL_NUM;
    pstTtfMemSolution->ucPoolMask   = ucPoolMask;

    /*DL SHARE*/
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ucClusterCnt  = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_SHARE].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 0;
#if ((SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6932_SFT == SC_CTRL_MOD))
    /* 当前 V722 V7R5 Dallas Chicago 支持直通，当前只有V7R5有自己的SC_CTRL_MOD，待其他产品形态有了SC_CTRL_MOD，
        此处需要修改*/
    /*DL PDU */
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ucClusterCnt  = 4;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 84;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 2304;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 700;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1800;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 1200;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_3] = 8200;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_3]  = 15;
#else
    /*DL PDU */
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ucClusterCnt  = 4;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 84;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 2304;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 700;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 824;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 1800;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_3] = 8200;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_DL_PDU].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_3]  = 15;
#endif
    /*UL DATA*/
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ucClusterCnt  = 4;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 164;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 5430;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1748;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1652;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 270;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_3] = 8200;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_3]  = 10;

    /*UL EXT*/
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_EXT].ucClusterCnt  = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_EXT].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 0;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_EXT].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 0;

    /* UL IP PACKET */
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ucClusterCnt  = 3;
#if (SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD)
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 404;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 2500;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1692;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 20;
#elif ((SC_CTRL_MOD_6932_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD))
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 404;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 1500;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1264;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 20;
#elif (SC_CTRL_MOD_3650_SFT == SC_CTRL_MOD)
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 404;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 1000;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1264;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 20;
#else
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_0] = 404;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_0]  = 1000;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_1] = 1560;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_1]  = 1000;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkSize[TTF_MEM_POOL_BLK_INDEX_2] = 1628;
    pstTtfMemSolution->astTtfMemPoolCfgInfo[TTF_MEM_POOL_ID_UL_IP_DATA].ausBlkCnt[TTF_MEM_POOL_BLK_INDEX_2]  = 20;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_CalcTotalDynamicMemLen
 功能描述  : 计算出TTF所需申请的动态内存大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32 - TTF所需向底软申请的uncached内存大小，单位byte
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TTF_MEMCTRL_CalcTotalDynamicMemLen(VOS_UINT32 ulTtfInternalMemLength)
{
    VOS_UINT32                           ulDynamicMemLen;

    /* 格式如下，其中头尾以及BBPMaster和TTF内存池之间的32byte为保护内存，用于监测TTF内存是否被踩*/
    /*
    *  ------------------------------------------------------
    * |              头部保护字段0byte                       |
    *  ------------------------------------------------------
    * |      BbpMaster Head(如果支持W模，则申请内存)         |
    *  ------------------------------------------------------
    * |      BbpMaster Data(如果支持W模，则申请内存)         |
    *  ------------------------------------------------------
    * |                    TTF pool memory                   |
    *  ------------------------------------------------------
    */

    /* 初始化申请内存为0 */
    ulDynamicMemLen = TTF_DYNAMIC_MEM_LEN_ZERO;

    /* Section 1:头部保护魔术字段 */
    TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE, ulDynamicMemLen);
    TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE, TTF_DYNAMIC_MEM_LEN_ZERO);
    TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE));

    /* 每一段结束处增加32字节魔术字段 */
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);

    /* 根据是否支持WCDMA，确认是否分配BBPMASTER内存 */
    if (TTF_MEMCTRL_MODEL_SUPPORT_YES == TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0))
    {
        /*
        * BBPMaster data部分起始位置必须8字节对齐，因为BBP硬件要求，
        * 故将BBPMaster的头部，进行8btyte对齐
        * BBP Master由两部分组成：头部和数据部。如下：
        *  --------------------------------------------------------------
        * |  BbpMasterHeadLen = ulTBHeadNum * 128(byte)                   |
        *  --------------------------------------------------------------
        * |  BbpMasterDataLen = (ulTBHeadNum-ulTBHeadReserved)*5408(byte) |
        *  --------------------------------------------------------------
        * BBP Head、data 32byte对齐
        */

        /* Section 2:BBPMaster head */
        TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE, ulDynamicMemLen);
        TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE, WTTF_BBPMST_MAC_TB_HEAD_BUFF_LEN);
        TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_HEAD_ADDR_TYPE));

        /* 每一段结束处增加32字节魔术字段 */
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);

        /* Section 3:BBPMaster data */
        TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE, ulDynamicMemLen);
        TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE, WTTF_BBPMST_MAC_TB_DATA_BUFF_LEN);
        TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_BBP_MASTER_DATA_ADDR_TYPE));

        /* 每一段结束处增加32字节魔术字段 */
        ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);
    }

    /* Section 4:TTF内部使用的内存 */
    TTF_DYNAMIC_MEM_SET_OFFSETBASE(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE, ulDynamicMemLen);
    TTF_DYNAMIC_MEM_SET_LEN(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE, ulTtfInternalMemLength);
    TTF_DYNAMIC_MEM_SET_ATTRIBUTE(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE, TTF_MEMCTRL_TYPE_EXIST_FLG);
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE));

    /* 每一段结束处增加32字节魔术字段 */
    ulDynamicMemLen += TTF_GET_32BYTE_ALIGN_VALUE(TTF_MEM_MAGIC_NUM_LEN);

    return ulDynamicMemLen;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_DynamicAddrInit
 功能描述  : 对BBPMaster和TTF内存池进行初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_OK -- 初始化成功
             VOS_ERR -- 初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TTF_MEMCTRL_DynamicAddrInit(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulDynamicTtfMemLen;
    TTF_MEMCTRL_ADDR_TYPE_STRU         *pstTtfMemDynamicAddr;
    VOS_UINT8                          *pucDynamicTtfMemBaseAddr;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMagicDataAddr;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTtfInternalMemLength;
    UCOM_NV_W_RF_RX_EVM_TEST_STRU       stWRfRxEvmTestMode;

    /* 初始化函数只会被PID初始化函数顺序调用 */
    if ( TTF_MEMCTRL_TYPE_INIT_FLG == TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG() )
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_DynamicAddrInit, Warning, Dynamic Memory were already initialized!\n");
        return VOS_OK;
    }

    PS_MEM_SET(&stWRfRxEvmTestMode, 0, sizeof(UCOM_NV_W_RF_RX_EVM_TEST_STRU));

    /* 读取NV，确认是否是RF RX EVM模式 */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_W_RF_RX_EVM_TEST, &stWRfRxEvmTestMode , sizeof(UCOM_NV_W_RF_RX_EVM_TEST_STRU));
    if (NV_OK != ulRet)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_DynamicAddrInit, Warning, Read NV en_NV_Item_W_RF_RX_EVM_TEST Fail!\n");
        stWRfRxEvmTestMode.enRxEvmTestEn = UCOM_NV_RX_EVM_TEST_DISABLE;
    }

    /* 通过读取邋NV确定是否进行RxEvm测试，1为测试模式，0为正常模式 */
    if (UCOM_NV_RX_EVM_TEST_ENABLE == stWRfRxEvmTestMode.enRxEvmTestEn)
    {
        TTF_MEM_SET_W_RF_RXEVM_TEST_EN(VOS_YES);
        return VOS_OK;
    }

    /* 读取配置文件 */
    ulRet = TTF_MEMCTRL_ReadNvCfg(&g_stTtfMemSolution);
    if (PS_FAIL == ulRet)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_DynamicAddrInit, Warning, TTF_MEMCTRL_ReadNvCfg FAIL!\n");
        TTF_MemSetDefaultNvCfg(&g_stTtfMemSolution);
    }

    /* TTF CCORE内存池长度 */
    ulTtfInternalMemLength = TTF_MEMCTRL_MemNvCfgTotalLength(&g_stTtfMemSolution);

    /* TTF内部使用的内存，包括HDLC,CICOM,BBPMASTER CIRCLE,ACORE POOL,CCORE POOL */
    ulTtfInternalMemLength += (TTF_HDLC_MASTER_LINK_TOTAL_LEN + TTF_PARA_MEM_TOTAL_LEN + TTF_BBPMST_BUFF_TOTAL_LEN + TTF_ACORE_POOL_MEM_TOTAL_LEN);

    /* 64K对齐 */
    ulTtfInternalMemLength = (ulTtfInternalMemLength + ((1UL << 16) - 1)) & (~((1UL << 16) - 1));

    /* 初始化BBPMaster的配置 */
    TTF_MEMCTRL_ReadBBPMemConfig(ulPid);

    pstTtfMemDynamicAddr = &TTF_MEM_GET_DYNAMIC_ADDR_TYPE();
    VOS_MemSet(pstTtfMemDynamicAddr, 0, sizeof(TTF_MEMCTRL_ADDR_TYPE_STRU) * TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT);

    /* 计算TTF所需要申请的内存大小 */
    ulDynamicTtfMemLen = TTF_MEMCTRL_CalcTotalDynamicMemLen(ulTtfInternalMemLength);

    /* 调用drv提供的接口，申请uncached内存 */
    pucDynamicTtfMemBaseAddr = (VOS_UINT8 *)TTF_UNCACHED_MEM_BSP_ALLOC(ulDynamicTtfMemLen);
    if (VOS_NULL_PTR == pucDynamicTtfMemBaseAddr)
    {
        TTF_LOG4(ulPid, 0, PS_PRINT_WARNING,
                    "TTF_MEMCTRL_DynamicAddrInit, Memory Alloc Fail!!Length:0x%x, SupporWcdma:%d, BbpMaster Head Num:%d, BbpMaster Data Num:%d \r\n",
                    (VOS_INT32)ulDynamicTtfMemLen,
                    (VOS_INT32)TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0),
                    (VOS_INT32)WTTF_BBPMST_MAC_TB_HEAD_NUM,
                    (VOS_INT32)WTTF_BBPMST_MAC_TB_DATA_NUM);

        return VOS_ERR;
    }

    PS_MEM_SET(pucDynamicTtfMemBaseAddr, 0, ulDynamicTtfMemLen);

    TTF_MEM_SET_TTF_BASE_ADDR(pucDynamicTtfMemBaseAddr);

    TTF_MEM_SET_TTF_TOTAL_LEN(ulDynamicTtfMemLen);

    /*
    * 初始化头部32byte保护间隔，初始化魔术字，用于监测TTF内存是否被踩
    * 当前采用将32byte定义为5A5A......5A5A，这样32byte里面0、1就比较随机了
    * 一旦32byte内存里面的内容被踩，那边这部分内容必定不是5A5A....5A5A
    */
    for (ulLoop = TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE; ulLoop < TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT; ulLoop++)
    {
        ulMagicDataAddr = (VOS_UINT32)((VOS_UINT_PTR)TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop) + TTF_DYNAMIC_MEM_GET_LEN(ulLoop));
        if (TTF_MEMCTRL_TYPE_EXIST_FLG == TTF_DYNAMIC_MEM_GET_ATTRIBUTE(ulLoop))
        {
            VOS_MemSet((VOS_VOID *)(VOS_UINT_PTR)ulMagicDataAddr, TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_LEN);
        }
    }

    TTF_MEM_SET_DYNAMIC_INIT_ADDR_FLAG(TTF_MEMCTRL_TYPE_INIT_FLG);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_ReportMemErrorInd
 功能描述  : 挂接到MAC UL状态切换（WTTF_MACUL_UpdateMacState）上的内存检测，
             检测到异常发送事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 TTF_MEMCTRL_ReportMemErrorInd( VOS_UINT32 ulPid,
                                                 TTF_DYNAMIC_MEM_ADDR_TYPE_ENUM_UINT32 ulMagicNumFlag,
                                                 VOS_UINT8 *pucMagicNum,
                                                 TTF_MEMCTRL_ADDR_TYPE_STRU *pststTtfMemAddr)
{
    TTF_MEM_ERROR_INFO_IND_STRU                     stTtfMemErrorInfoInd;

    VOS_MemSet(&stTtfMemErrorInfoInd, 0, sizeof(TTF_MEM_ERROR_INFO_IND_STRU));

    stTtfMemErrorInfoInd.ulSenderCpuId              = VOS_LOCAL_CPUID;
    stTtfMemErrorInfoInd.ulSenderPid                = ulPid;
    stTtfMemErrorInfoInd.ulReceiverCpuId            = VOS_LOCAL_CPUID;
    stTtfMemErrorInfoInd.ulReceiverPid              = ulPid;
    stTtfMemErrorInfoInd.ulLength                   = (sizeof(TTF_MEM_ERROR_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    stTtfMemErrorInfoInd.usMsgName                  = ID_TRACE_TTF_MEM_ERR_IND;
    stTtfMemErrorInfoInd.ulMagicNumFlag             = ulMagicNumFlag;

    VOS_MemCpy(stTtfMemErrorInfoInd.aulMagicNum, pucMagicNum, TTF_MEM_MAGIC_NUM_LEN);
    VOS_MemCpy(&stTtfMemErrorInfoInd.astTtfMemAddrType[0], pststTtfMemAddr, sizeof(TTF_MEMCTRL_ADDR_TYPE_STRU) * TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT);

    DIAG_TraceReport((VOS_VOID *)&stTtfMemErrorInfoInd);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_CheckMagicNum
 功能描述  : 保护内存检查，检测magic number值是否改变
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_CheckMagicNum(TTF_MEMCTRL_CALLBACK_FUNC_FLAG_ENUM_ENUM8 ucCallbackFlag,
                                            VOS_UINT32 ulPid)
{
    const VOS_UINT8                     aucMagicNumValue[32] = {TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE,
                                                                TTF_MEM_MAGIC_NUM_VALUE, TTF_MEM_MAGIC_NUM_VALUE};
    VOS_UINT32                          ulMagicDataAddr;
    VOS_UINT32                          ulLoop;

    if (VOS_FALSE == TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG())
    {
        return;
    }

    for (ulLoop = TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE; ulLoop < TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT; ulLoop++)
    {
        /* 获取动态内存头部魔术字段地址 */
        ulMagicDataAddr = (VOS_UINT32)((VOS_UINT_PTR)TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop) + TTF_DYNAMIC_MEM_GET_LEN(ulLoop));

        if (TTF_MEMCTRL_TYPE_EXIST_FLG == TTF_DYNAMIC_MEM_GET_ATTRIBUTE(ulLoop))
        {
            if (0 != VOS_MemCmp((VOS_VOID *)(VOS_UINT_PTR)ulMagicDataAddr, aucMagicNumValue, TTF_MEM_MAGIC_NUM_LEN))
            {
                if (TTF_MEMCTRL_CALLBACK_FUNC_DRV == ucCallbackFlag)
                {
                   LogPrint1("Section:%d, Magic number value has been changed \r\n", (VOS_INT)ulLoop);
                }
                else
                {
                    TTF_MEMCTRL_ReportMemErrorInd(  ulPid,
                                                    ulLoop,
                                                    (VOS_UINT8 *)((VOS_UINT_PTR)ulMagicDataAddr),
                                                    &TTF_MEM_GET_DYNAMIC_ADDR_TYPE());
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_DRVCallbackFunc
 功能描述  : 保护内存检查，检测magic number值是否改变，用于挂接到底软
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_DRVCallbackFunc(VOS_VOID)
{
    TTF_MEMCTRL_CheckMagicNum(TTF_MEMCTRL_CALLBACK_FUNC_DRV, TTF_MEMCTRL_PID_INVAILD);
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_EnableAdvanceCheck
 功能描述  : 内存是否被踩检测, 将内存检测函数挂钩到底软切换任务上，后续调测时直接shell里面输入
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_EnableAdvanceCheck (VOS_VOID)
{
    /* 将内存检测函数挂钩到底软切换任务上，串口中打印出来,调用底软接口：OSAL_TaskSwitchHookAdd */
    #if 0
    OSAL_TaskSwitchHookAdd((OSAL_FUNCPTR)TTF_MEMCTRL_DRVCallbackFunc);
    #endif
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_DisableAdvanceCheck
 功能描述  : 去除挂在底软上的钩子函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_DisableAdvanceCheck(VOS_VOID)
{
    /*去钩子函数：OSAL_TaskSwitchHookDel */
    #if 0
    OSAL_TaskSwitchHookDel((OSAL_FUNCPTR)TTF_MEMCTRL_DRVCallbackFunc);
    #endif
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_CheckTTFDynamicMem
 功能描述  : 保护内存检查，检测magic number值是否改变，
             挂接到MAC UL状态切换（WTTF_MACUL_UpdateMacState）上
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_CheckTTFDynamicMem(VOS_UINT32 ulPid)
{
    TTF_MEMCTRL_CheckMagicNum(TTF_MEMCTRL_CALLBACK_FUNC_TTF, ulPid);

    return ;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetTtfInternalMemBaseAddr
 功能描述  : 获取TTF内部使用的基地址，包括HDLC,CICOM,BBPMASTER CIRCLE,ACORE POOL,CCORE POOL
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月6日
    作    者   : gebaizhang
    修改内容   : Created
*****************************************************************************/
VOS_UINT_PTR TTF_MEMCTRL_GetTtfInternalMemBaseAddr(VOS_VOID)
{
    VOS_UINT_PTR           ulBaseAddr;

#if (VOS_WIN32 == VOS_OS_VER)
    BSP_DDR_SECT_QUERY   stQuery;
    BSP_DDR_SECT_INFO    stInfo;

    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    ulBaseAddr = (VOS_UINT_PTR)stInfo.pSectPhysAddr;
#else
    ulBaseAddr = (VOS_UINT_PTR)(TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE));
#endif

    return ulBaseAddr;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetMemTotalLen
 功能描述  : TTF内存地址A-CPU上初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : h00163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32   TTF_MEMCTRL_GetMemTotalLen(VOS_VOID)
{
    VOS_UINT32                          ulMemTotalLen;

#if (VOS_WIN32 == VOS_OS_VER)
    BSP_DDR_SECT_QUERY                  stQuery;
    BSP_DDR_SECT_INFO                   stInfo;
    signed int                          lRslt;

    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    stInfo.ulSectSize  = TTF_MEMCTRL_INVAILD_SIZE;

    lRslt = DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    if (BSP_OK != lRslt)
    {
        stInfo.ulSectSize = TTF_MEMCTRL_INVAILD_SIZE;
    }

    ulMemTotalLen    = stInfo.ulSectSize;
#else
    ulMemTotalLen    = TTF_DYNAMIC_MEM_GET_LEN(TTF_DYNAMIC_MEM_TTF_INTERNAL_ADDR_TYPE);
#endif

    return ulMemTotalLen;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_AddrInit
 功能描述  : TTF内存地址初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : h00163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32   TTF_MEMCTRL_AddrInit(VOS_UINT32 ulPid)
{
    VOS_UINT8                           ucTypeLoop;
    VOS_UINT8                           ucTypeLoopOne   = 0;
    VOS_UINT32                          ulTypeOffestLen = 0;
    VOS_UINT32                          ulCCoreTypeLen  = 0;
    VOS_UINT32                          ulMemTotalLen   = 0;

    if (TTF_MEMCTRL_TYPE_INIT_FLG == TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
         TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_AddrInit::Addrs were already initialized!\n");
         return 0;
    }

    memset(&g_stTtfMemCtrlAddr, 0, sizeof(TTF_MEMCTRL_ADDR_STRU));

    /* 设置TTF内部内存各个类型的内存长度 */
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_HDLC_MASTER_LINK_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_PARA_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_BBPMST_BUFF_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_ACORE_POOL_MEM_TOTAL_LEN);

    ulMemTotalLen   = TTF_MEMCTRL_GetMemTotalLen();

    if (TTF_MEMCTRL_INVAILD_SIZE == ulMemTotalLen)
    {
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_AddrInit:ulMemTotalLen is invalid!\n");
        return 0;
    }

    ulCCoreTypeLen  = (ulMemTotalLen - TTF_HDLC_MASTER_LINK_TOTAL_LEN
                        - TTF_PARA_MEM_TOTAL_LEN - TTF_BBPMST_BUFF_TOTAL_LEN - TTF_ACORE_POOL_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, ulCCoreTypeLen);


    for (ucTypeLoop = 0; ucTypeLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ucTypeLoop++)
    {
        if (0 != TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop))
        {
            TTF_MEMCTRL_SET_TYPE_FLG(ucTypeLoop, TTF_MEMCTRL_TYPE_EXIST_FLG);
        }

        ulTypeOffestLen += TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop);
        ucTypeLoopOne   =  ucTypeLoop + 1;
        if (ucTypeLoopOne < TTF_MEMCTRL_ADDR_TYPE_BUTT)
        {
            /* TTF 各个类型内存相对于基址的偏移长度设置 */
            TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(ucTypeLoopOne, ulTypeOffestLen);
        }
    }

    TTF_MEMCTRL_SET_ADDR_INIT_FLG(TTF_MEMCTRL_TYPE_INIT_FLG);

    return 0;
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_CCORE_AddrInit
 功能描述  : TTF内存地址C-CPU上初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : h00163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32   TTF_MEMCTRL_CCORE_AddrInit(VOS_UINT32 ulPid)
{
    if (VOS_YES == TTF_MEM_GET_W_RF_RXEVM_TEST_EN())
    {
        return VOS_OK;
    }

    TTF_MEMCTRL_AddrInit(ulPid);

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
#if(FEATURE_ON == FEATURE_PPP)
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetOffsetBaseLen
 功能描述  : 获取TTF内存类型对应的起始地址偏移值
 输入参数  : VOS_UINT32  ulType  - 内存类型
 输出参数  : VOS_UINT32      偏移基地址值
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : h00163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TTF_MEMCTRL_GetOffsetBaseLen(VOS_UINT32  ulType)
{
    VOS_UINT32                          ulAttribute;

    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d is invalid!\n", (VOS_INT32)ulType);
        return 0;
    }

    if (TTF_MEMCTRL_TYPE_INIT_FLG != TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
        TTF_LOG(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetOffsetBaseLen::addr is not init!\n");
        return 0;
    }

    ulAttribute = TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ulType);
    if (   (TTF_MEMCTRL_TYPE_EXIST_FLG == (TTF_MEMCTRL_TYPE_EXIST_FLG & ulAttribute))
        && (TTF_MEMCTRL_TYPE_VISIBLE_FLG == (TTF_MEMCTRL_TYPE_VISIBLE_FLG & ulAttribute)))
    {
        return TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ulType);
    }

    TTF_LOG2(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d, ulAttribute:%d is not exist or not visible!\n",
                    (VOS_INT32)ulType, (VOS_INT32)ulAttribute);

    return 0;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetTypeAddr
 功能描述  : 获取TTF内存类型对应的起始地址
 输入参数  : VOS_UINT32  ulAddr  - 地址值
           : VOS_UINT32  ulType  - 内存类型
 输出参数  : VOS_UINT32      地址值
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : h00163499
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT_PTR  TTF_MEMCTRL_GetTypeAddr(VOS_UINT_PTR ulAddr, VOS_UINT32 ulType)
{
    VOS_UINT32                          ulOffsetBaseLen;
    VOS_UINT_PTR                        ulTtfMemCtrlTypeAddr;

    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        TTF_LOG1(WUEPS_PID_RLC, 0, PS_PRINT_WARNING, "TTF_MEMCTRL_GetTypeAddr::ulType:%d is invalid!\n", (VOS_INT32)ulType);
        return 0;
    }

    ulOffsetBaseLen         = TTF_MEMCTRL_GetOffsetBaseLen(ulType);
    ulTtfMemCtrlTypeAddr    = ulAddr + ulOffsetBaseLen;

    return  ulTtfMemCtrlTypeAddr;
}

/*****************************************************************************
 函 数 名  : TTF_MemAddrPrint
 功能描述  : 串口打印出TTF pool MEM、BBP master head和BBP master的内存地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月12日
    作    者   : c00212970
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TTF_MEMCTRL_AddrPrint(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT_PTR                        ulBaseAddr;

    /* 动态内存管理信息，动态申请内存基地址以及是否支持WCDMA */
    vos_printf("Ttf Dynamic Mem Info: Init Flag:%d \tIsSupportWcdma:%d \tBase Addr:0x%x \tTotalLen:0x%x\n",
                TTF_MEM_GET_DYNAMIC_INIT_ADDR_FLAG(),
                TTF_MEM_GET_SUPPORT_WCDMA(MODEM_ID_0),
                (VOS_UINT32)(VOS_UINT_PTR)TTF_MEM_GET_TTF_BASE_ADDR(),
                TTF_MEM_GET_TTF_TOTAL_LEN());

    vos_printf("\nTtf Dynamic Mem Section Info:\n");
    for (ulLoop = TTF_DYNAMIC_MEM_HEAD_ADDR_TYPE; ulLoop < TTF_DYNAMIC_MEM_ADDR_TYPE_BUTT; ulLoop++)
    {
        vos_printf("[Section]:%d \t[Attribute]:%d \t[StartAddr]:0x%-8x \t[Len]:0x%-8x \t[OffsetBaseLen]:0x%-8x\n",
                    ulLoop,
                    TTF_DYNAMIC_MEM_GET_ATTRIBUTE(ulLoop),
                    TTF_MEM_GET_TTF_BASE_ADDR() + TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop),
                    TTF_DYNAMIC_MEM_GET_LEN(ulLoop),
                    TTF_DYNAMIC_MEM_GET_OFFSETBASE(ulLoop));
    }

    ulBaseAddr      = TTF_MEMCTRL_GetTtfInternalMemBaseAddr();

    vos_printf("\nTTF Internal Mem Base Addr:0x%-8x \tInit Flag:%d\n", ulBaseAddr, TTF_MEMCTRL_GET_ADDR_INIT_FLG());

    for (ulLoop = TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE; ulLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ulLoop++)
    {
        vos_printf("[Section]:%d \t[Attribute]:%d \t[StartAddr]:0x%-8x \t[Len]:0x%-8x \t[OffsetBaseLen]:0x%-8x\n",
            ulLoop,
            TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ulLoop),
            TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(ulBaseAddr)), ulLoop),
            TTF_MEMCTRL_GET_TYPE_LEN(ulLoop),
            TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ulLoop));
    }

    return;
}

/*lint -restore */
/*lint +e534*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


