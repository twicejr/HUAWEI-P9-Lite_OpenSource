/******************************************************************************

                  版权所有 (C), 2005-2007, 华为技术有限公司


  文 件 名   : Nas_Mem.h
  版 本 号   : 初稿
  作    者   : liuyang id:48197
  生成日期   : 2006年4月27日
  最近修改   :
  功能描述   : NAS层内存宏定义头文件
  函数列表   :
      ---
      ---
      ---
  修改历史   :
  1.日    期   : 2006年4月27日
    作    者   : liuyang id:48197
    修改内容   : 创建文件
  2.日    期   : 2006年4月27日
    作    者   : ---
    修改内容   : Add function ... 问题单号:

******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 头文件包含
 *****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "gunas_errno.h"

/*****************************************************************************
   2 内部函数原型说明
 *****************************************************************************/

/*****************************************************************************
   3 全局变量定义
 *****************************************************************************/


/*****************************************************************************
   4 模块级变量
 *****************************************************************************/

/*****************************************************************************
   5 常量定义
 *****************************************************************************/

/*****************************************************************************
   6 宏定义
 *****************************************************************************/
#define PS_NAS_MEM_CPY(pDestBuffer, pSrcBuffer, ulBufferLen)\
            PS_MEM_CPY((pDestBuffer), (pSrcBuffer), (ulBufferLen))

#define PS_NAS_MEM_SET(pBuffer, ucData, ulBufferLen) \
            PS_MEM_SET((pBuffer), (ucData), (ulBufferLen))

#define PS_NAS_MEM_MOVE(pDestBuffer, pSrcBuffer, ulBufferLen) \
            PS_MEM_MOVE((pDestBuffer), (pSrcBuffer), (ulBufferLen))

#define PS_NAS_MEM_ALLOC(ulPid, ulSize, ulWaitOption) \
            PS_MEM_ALLOC((ulPid), (ulSize))

#define PS_NAS_MEM_FREE(ulPid, pAddr) \
            PS_MEM_FREE((ulPid), (pAddr))

#if (VOS_OS_VER == VOS_WIN32)
#define NAS_MEM_CPY_S(pDestBuffer, ulDestLen,  pSrcBuffer, ulCount) VOS_MemCpy_s( pDestBuffer, ulDestLen,  pSrcBuffer, ulCount)

#define NAS_MEM_SET_S(pDestBuffer, ulDestLen, ucData, ulCount) VOS_MemSet_s( pDestBuffer, ulDestLen, ucData, ulCount )

#define NAS_MEM_MOVE_S(pDestBuffer, ulDestLen, pucSrcBuffer, ulCount) VOS_MemMove_s( pDestBuffer, ulDestLen, pucSrcBuffer, ulCount )
#else
#define NAS_MEM_CPY_S(pDestBuffer, ulDestLen,  pSrcBuffer, ulCount) { \
        if (VOS_NULL_PTR == VOS_MemCpy_s( pDestBuffer, ulDestLen,  pSrcBuffer, ulCount)) \
        {\
            mdrv_om_system_error(NAS_REBOOT_MOD_ID_MEM, 0, (VOS_INT)((THIS_FILE_ID << 16) | __LINE__), 0, 0 ); \
        }\
    }

#define NAS_MEM_SET_S(pDestBuffer, ulDestLen, ucData, ulCount) { \
        if (VOS_NULL_PTR == VOS_MemSet_s( pDestBuffer, ulDestLen, ucData, ulCount )) \
        { \
            mdrv_om_system_error(NAS_REBOOT_MOD_ID_MEM, 0, (VOS_INT)((THIS_FILE_ID << 16) | __LINE__), 0, 0 ); \
        } \
    }

#define NAS_MEM_MOVE_S(pDestBuffer, ulDestLen, pucSrcBuffer, ulCount) { \
        if (VOS_NULL_PTR == VOS_MemMove_s( pDestBuffer, ulDestLen, pucSrcBuffer, ulCount )) \
        { \
            mdrv_om_system_error(NAS_REBOOT_MOD_ID_MEM, 0, (VOS_INT)((THIS_FILE_ID << 16) | __LINE__), 0, 0 ); \
        } \
    }

#endif

/*PS_NAS_VOS_MEM_ALLOC 代替 VOS_MemAlloc*/
#define PS_NAS_VOS_MEM_ALLOC(ulPid, ucPtNo, ulSize)\
            PS_MEM_ALLOC((ulPid), (ulSize))

/*PS_NAS_VOS_MEM_FREE 代替 VOS_MemFree*/
#define PS_NAS_VOS_MEM_FREE(ulPid, ulSize)\
            PS_MEM_FREE((ulPid), (ulSize))

/*==============================================*/
#define PS_CC_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC(WUEPS_PID_CC, (ulSize))

#define PS_SM_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SM, (ulSize), (ulWaitOption))

#define PS_SMS_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SMS, (ulSize), (ulWaitOption))

#define PS_SS_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SS, (ulSize), (ulWaitOption))

#define PS_TC_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_TC, (ulSize), (ulWaitOption))

#define PS_SMT_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SMT, (ulSize), (ulWaitOption))

#define PS_NASAPI_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_ADMIN, (ulSize), (ulWaitOption))

#define PS_RABM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC(WUEPS_PID_RABM, (ulSize))


#define PS_CC_MEM_FREE(pAddr)\
            PS_MEM_FREE(WUEPS_PID_CC, (pAddr))

#define PS_SM_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SM, (pAddr))

#define PS_SMS_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SMS, (pAddr))

#define PS_SS_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SS, (pAddr))

#define PS_TC_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_TC, (pAddr))

#define PS_SMT_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SMT, (pAddr))

#define PS_NASAPI_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_ADMIN, (pAddr))

#define PS_RABM_MEM_FREE(pAddr)\
            PS_MEM_FREE(WUEPS_PID_RABM, (pAddr))



#define MMC_MEM_ALLOC(ulPoolIdIndex,ulSize,ulWaitOption) PS_MEM_ALLOC(WUEPS_PID_MMC, (ulSize))
#define MMC_MEM_FREE(ulPoolIdIndex,pAddr) PS_MEM_FREE(WUEPS_PID_MMC, pAddr)

#define MM_MEM_ALLOC(ulPoolIdIndex,ulSize,ulWaitOption) PS_MEM_ALLOC(WUEPS_PID_MM,(ulSize))
#define MM_MEM_FREE(ulPoolIdIndex,pAddr) PS_MEM_FREE(WUEPS_PID_MM, pAddr)


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


