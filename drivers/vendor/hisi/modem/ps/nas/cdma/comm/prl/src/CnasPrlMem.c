/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasPrlMem.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年8月04日
  最近修改   :
  功能描述   : CNAS PRL memory分配与释放函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasPrlMem.h"
#include  "CnasMntn.h"
#include  "TafTypeDef.h"
#include  "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_PRL_MEM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_PRL_MEM_BUFF_STRU                  g_stCnasPrlBuff;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_PRL_InitMemBuff
 功能描述  : 初始化g_cnasPrlBuff
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_InitMemBuff(VOS_VOID)
{
    g_stCnasPrlBuff.ulIndex = 0;
    NAS_MEM_SET_S(g_stCnasPrlBuff.astBlock, sizeof(g_stCnasPrlBuff.astBlock), 0, sizeof(g_stCnasPrlBuff.astBlock));
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_AddMemBuffIndex
 功能描述  : PRL内存块申请指示+1
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 CNAS_PRL_AddMemBuffIndex(VOS_VOID)
{
    if (g_stCnasPrlBuff.ulIndex < (CNAS_PRL_BLOCK_MAX_NUM - 1))
    {
        g_stCnasPrlBuff.ulIndex += 1;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_MallocMemBuff
 功能描述  : 为PRL解析申请整块内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_PRL_MallocMemBuff(VOS_VOID)
{
    CNAS_PRL_BUFF_STRU                *pstPrl  = VOS_NULL_PTR;

    pstPrl = CNAS_PRL_GetMemBlock(CNAS_PRL_GetMemBuffInedx());

    /* 上下文中内存地址为空, 则分配内存并初始化 */
    if (VOS_NULL_PTR == pstPrl->pucHead)
    {
        pstPrl->ulRemainSize    = CNAS_PRL_BUFF_SIZE;
        pstPrl->pucHead         = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XSD, CNAS_PRL_BUFF_SIZE);
        pstPrl->pucCur          = pstPrl->pucHead;

        /* 申请内存失败 */
        if (VOS_NULL_PTR == pstPrl->pucHead)
        {
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_MallocMemBuff: Malloc Failure!");
            return VOS_FALSE;
        }

        NAS_MEM_SET_S(pstPrl->pucHead, CNAS_PRL_BUFF_SIZE, 0x00, CNAS_PRL_BUFF_SIZE);

    }
    /* 上下文已分配内存空间 */
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_MallocMemBuff: Repeatly Malloc Buff!");
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : CNAS_PRL_MemFreeBuff
 功能描述  : 释放PRL解析申请的内存池
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_MemFreeBuff(VOS_VOID)
{
    CNAS_PRL_BUFF_STRU                 *pstPrl  = VOS_NULL_PTR;
    VOS_UINT32                          i;

    for (i = 0; ((i <= CNAS_PRL_GetMemBuffInedx()) && (i < CNAS_PRL_BLOCK_MAX_NUM)); i++)
    {
        pstPrl                          = CNAS_PRL_GetMemBlock(i);

        /* 上下文中内存地址不为空, 则释放内存 */
        if (VOS_NULL_PTR != pstPrl->pucHead)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstPrl->pucHead);
        }
    }

    /* 重新初始化 */
    CNAS_PRL_InitMemBuff();
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_Malloc
 功能描述  : 申请PRL参数解析所需内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID *CNAS_PRL_Malloc(
    VOS_UINT32                          ulSize
)
{
    CNAS_PRL_BUFF_STRU                 *pstPrl  = VOS_NULL_PTR;
    VOS_VOID                           *pReturn = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstPrl = CNAS_PRL_GetMemBlock(CNAS_PRL_GetMemBuffInedx());

    /* 判断上下文中的当前内存指针是否可用, 不可用则调用初始化内存函数 */
    if (VOS_NULL_PTR == pstPrl->pucHead)
    {
        return pReturn;
    }

    /* 如果申请的内存小于当前内存块中剩余的大小，才可以申请 */
    if (ulSize < pstPrl->ulRemainSize)
    {
        pReturn                 = pstPrl->pucCur;
        pstPrl->pucCur         += ulSize;
        pstPrl->ulRemainSize   -= ulSize;
    }
    else
    {
        /* 申请下一块内存 */
        if (VOS_TRUE== CNAS_PRL_AddMemBuffIndex())
        {
            ulRslt = CNAS_PRL_MallocMemBuff();
            if (VOS_TRUE == ulRslt)
            {
                /* 指向新申请的下一块内存 */
                pstPrl = CNAS_PRL_GetMemBlock(CNAS_PRL_GetMemBuffInedx());

                /* 如果申请的内存小于当前内存块中剩余的大小，才可以申请 */
                if (ulSize < pstPrl->ulRemainSize)
                {
                    pReturn                 = pstPrl->pucCur;
                    pstPrl->pucCur         += ulSize;
                    pstPrl->ulRemainSize   -= ulSize;
                }
            }
        }
        else
        {
            CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_PRL_Malloc:PRL Buffer index:", CNAS_PRL_GetMemBuffInedx());
        }
    }

    return pReturn;

}

#if 0
/*****************************************************************************
 函 数 名  : CNAS_PRL_Free
 功能描述  : 释放PRL参数解析申请的内存，仅限于前一次申请的
 输入参数  : pFree      -前一次申请的内存指针
             ulSize     -内存大小
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月04日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_Free(
    VOS_VOID                          **pFree,
    VOS_UINT32                          ulSize
)
{
    CNAS_PRL_BUFF_STRU                 *pstPrl  = VOS_NULL_PTR;
    VOS_UINT8                          *pucFree = VOS_NULL_PTR;

    pucFree = (VOS_UINT8 *)*pFree;
    pstPrl  = CNAS_PRL_GetMemBlock(CNAS_PRL_GetMemBuffInedx());

    if (VOS_NULL_PTR == pucFree)
    {
        return;
    }

    /* 判断上下文中的当前内存指针是否可用, 不可用则调用初始化内存函数 */
    if (pstPrl->pucCur == (pucFree + ulSize))
    {
        if (CNAS_PRL_BUFF_SIZE >= (pstPrl->ulRemainSize + ulSize))
        {
            pucFree                 = VOS_NULL_PTR;

            pstPrl->pucCur         -= ulSize;
            pstPrl->ulRemainSize   += ulSize;
            PS_MEM_SET(pstPrl->pucCur, 0, ulSize);
        }
    }

    return;

}
#endif
/*lint -restore*/


#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


