
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasFsm.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2010年11月13日
  最近修改   :
  功能描述   : NAS层状态机基本处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <stdlib.h> /* bsearch,qsort */
#include "vos.h"

#include "NasFsm.h"
#include "NasComm.h"
#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_FSM_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_FSM_StaCompare
 功能描述  : NAS状态机比较函数,在对状态转移表进行快速排序时用到
 输入参数  : pstSta1: 比较的状态1
             pstSta2: 比较的状态2
 输出参数  : 无
 返回值    : 0 : 状态1和状态2相等
             -1: 状态1小于状态2
              1: 状态1大于状态2
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32  NAS_FSM_StaCompare(
    const VOS_VOID                      *pSta1,
    const VOS_VOID                      *pSta2
)
{
    NAS_STA_STRU                  *pstSta1;
    NAS_STA_STRU                  *pstSta2;

    pstSta1 = (NAS_STA_STRU *)pSta1;
    pstSta2 = (NAS_STA_STRU *)pSta2;

    /*  如果状态1小于状态2,返回-1 */
    if (pstSta1->ulState < pstSta2->ulState)
    {
        return -1;
    }

    /*  如果状态1等于状态2,返回0 */
    if (pstSta1->ulState == pstSta2->ulState)
    {
        return 0;
    }

    /*  如果状态1大于状态2,返回1 */
    return 1;
}


/*****************************************************************************
 函 数 名  : NAS_FSM_ActCompare
 功能描述  : 事件比较函数，在对事件处理表进行快速排序时用到
 输入参数  : pstAct1 : 事件1
             pstAct2 : 事件2
 输出参数  : 无
 返回值    : 0  : 事件1和事件2相等
             -1 : 事件1小于事件2
              1 : 事件1大于事件2
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32  NAS_FSM_ActCompare(
    const VOS_VOID                  *pAct1,
    const VOS_VOID                  *pAct2
)
{
    NAS_ACT_STRU                  *pstAct1;
    NAS_ACT_STRU                  *pstAct2;

    pstAct1 = (NAS_ACT_STRU *)pAct1;
    pstAct2 = (NAS_ACT_STRU *)pAct2;

    /*  如果事件1小于事件2,返回-1 */
    if (pstAct1->ulEventType < pstAct2->ulEventType)
    {
        return -1;
    }

    /*  如果事件1等于事件2,返回0 */
    if (pstAct1->ulEventType == pstAct2->ulEventType)
    {
        return 0;
    }

    /*  如果事件1大于事件2,返回0 */
    return 1;
}

/*****************************************************************************
 函 数 名    : NAS_FSM_FindAct
 功能描述    : 根据状态和事件类型在排序后的状态转移表中快速查找事件处理函数
 输入参数    : pstFsmDesc  :状态机描述符
               ulState     :状态
               ulEventType :事件类型
 输出参数    : 无
 返回值      : 事件处理函数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
 *****************************************************************************/
NAS_ACTION_FUNC NAS_FSM_FindAct(
    NAS_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState,
    VOS_UINT32                          ulEventType
)
{
    /* 要查找的状态 */
    NAS_STA_STRU                        stKeySta;
    /* 要查找的状态 */
    NAS_STA_STRU                       *pstRetSta;
    /* 要查找的事件 */
    NAS_ACT_STRU                        stKeyAct;
    /* 返回的事件   */
    NAS_ACT_STRU                       *pstRetAct;


    PS_MEM_SET(&stKeySta, 0x00, sizeof(stKeySta));
    PS_MEM_SET(&stKeyAct, 0x00, sizeof(stKeyAct));


    pstRetSta         = VOS_NULL_PTR;
    pstRetAct         = VOS_NULL_PTR;

    stKeySta.ulState  = ulState;

    /*lint -e586*/
    /* 调用C语言的库函数bsearch在状态转移表中查找相应的事件处理表 */
    pstRetSta         = (NAS_STA_STRU*) bsearch( &stKeySta,
                                                 pstFsmDesc->pStaTable,
                                                 pstFsmDesc->ulSize,
                                                 sizeof(NAS_STA_STRU),
                                                 (NAS_FSM_COMP_FUNC)NAS_FSM_StaCompare );
    /*lint +e586*/

    /* 如果找不到相应的事件处理表,设置错误码,返回VOS_NULL_PTR */
    if (VOS_NULL_PTR == pstRetSta)
    {
        /* 此处与原函数不同，不再向Dopra返回错误码，
           而是直接返回空指针，表示该消息没有被该状态机处理。 */
        return (NAS_ACTION_FUNC) VOS_NULL_PTR;
    }

    stKeyAct.ulEventType = ulEventType;

    /*lint -e586*/
    /* 调用C语言的库函数bsearch在事件处理表中查找相应的事件处理函数 */
    pstRetAct = (NAS_ACT_STRU*) bsearch ( &stKeyAct,
                                    pstRetSta->pActTable,
                                    pstRetSta->ulSize,
                                    sizeof(NAS_ACT_STRU),
                                    (NAS_FSM_COMP_FUNC)NAS_FSM_ActCompare );
    /*lint +e586*/

    /* 如果找不到相应的事件处理函数,设置错误码,返回VOS_NULL_PTR */
    if (VOS_NULL_PTR == pstRetAct)
    {
        /* 此处与原函数不同，不再向Dopra返回错误码，
           而是直接返回空指针，表示该消息没有被该状态机处理。 */
        return (NAS_ACTION_FUNC) VOS_NULL_PTR;
    }

    return (pstRetAct->pfActionFun);

}


/*****************************************************************************
 函 数 名    : NAS_FSM_StaSort
 功能描述    : 对状态转移表和和里面的每个事件处理函数表进行快速排序
 输入参数    : pstTbl   :状态转移表
               ulSize   :状态转移表的大小
 输出参数    : 排序后的状态转移表
 返回值      : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
 *****************************************************************************/
VOS_VOID NAS_FSM_StaSort(
    NAS_STA_STRU                       *pstTbl,
    VOS_UINT32                          ulSize
)
{
    VOS_UINT32                          ulIndex;

    /*lint -e586*/
    /* 调用C语言的库函数qsort对pTable进行快速排序 */
    qsort(pstTbl, ulSize, sizeof(NAS_STA_STRU), (NAS_FSM_COMP_FUNC)NAS_FSM_StaCompare);
    /*lint +e586*/

    /* 对每一个事件处理函数表调用C语言的库函数qsort进行快速排序 */
    for (ulIndex = 0; ulIndex < ulSize; ulIndex++)
    {
        /*lint -e586*/
        qsort( pstTbl->pActTable,
               pstTbl->ulSize,
               sizeof(NAS_ACT_STRU),
               (NAS_FSM_COMP_FUNC)NAS_FSM_ActCompare );
        /*lint +e586*/

        /* 对数组中的下一个STA_STRU元素中的动作表进行排序 */
        pstTbl++;
    }
}


/*****************************************************************************
 函 数 名    : NAS_FSM_RegisterFsm
 功能描述    : 登记状态机表
 输入参数    : pucName        :状态机名字
               ulSize         :状态转移表大小
               pstStaTbl      :状态转移表
               pfExceptHandle :异常处理函数
 输出参数    :  pstFsmDesc     :状态机描述符
 返回值      :  无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
 *****************************************************************************/
VOS_VOID NAS_FSM_RegisterFsm(
    NAS_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_CHAR                           *pucName,
    VOS_UINT32                          ulSize,
    NAS_STA_STRU                       *pstStaTbl,
    NAS_EXCEP_FUN                       pfExceptHandle,
    NAS_INIT_FUN                        pfInitHandle
)
{
    /* 检查入口参数 */
    if ( ( VOS_NULL_PTR == pstFsmDesc )
      || ( VOS_NULL_PTR == pstStaTbl ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC ,
                     "NAS_FSM_RegisterFsm,Parameter null ptr,pFsmDesc,pStaTable");


        return;
    }

    /* 对状态机描述符结构进行赋值 */
    pstFsmDesc->ulSize         = ulSize;
    pstFsmDesc->pStaTable      = pstStaTbl;
    pstFsmDesc->pfExceptHandle = pfExceptHandle;
    pstFsmDesc->pfInitHandle   = pfInitHandle;

    if (VOS_NULL_PTR == pucName)
    {
        pstFsmDesc->aucName[0] = '\0';
    }
    else
    {
        PS_MEM_CPY(pstFsmDesc->aucName,pucName,NAS_FSM_NAME_LENGTH);
        pstFsmDesc->aucName[NAS_FSM_NAME_LENGTH - 1] = '\0';
    }

    /* 对状态转移表进行排序 */
    NAS_FSM_StaSort(pstStaTbl, ulSize);

    return;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


