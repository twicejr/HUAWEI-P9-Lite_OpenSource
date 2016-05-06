/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmsEncap.h
  Description : 封装函数
  History     :
      1.  张志勇      2004.03.09   新版作成
      5.  韩鲁峰   2005-04-25   for A32D01738
  3.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
*******************************************************************************/


#ifndef _SMS_ENCAP_H_
#define _SMS_ENCAP_H_



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                              /* __cpluscplus */
#endif                              /* __cpluscplus */


#pragma pack(4)

#define SMS_TafFree(p){                                         \
                        PS_SMS_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, p );   \
                        p = VOS_NULL_PTR;                               \
                      }

#define SMS_GmmFree(p){                                         \
                        PS_SMS_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, p );   \
                        p = VOS_NULL_PTR;                               \
                      }

#define SMS_MmFree(p){                                          \
                        PS_SMS_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, p );   \
                        p = VOS_NULL_PTR;                               \
                     }

#define SMS_Free(p){                                            \
                        PS_SMS_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, p );   \
                        p = VOS_NULL_PTR;                               \
                   }

#define SMS_Malloc(length)           PS_SMS_MEM_ALLOC(VOS_MEMPOOL_INDEX_NAS, \
                                          length,WUEPS_MEM_WAIT)
#define SMS_Memcpy(p1,p2,length)     PS_NAS_MEM_CPY(p1,p2,length)
#define SMS_Memset(p,value,length)   PS_NAS_MEM_SET(p,value,length)

/*定义SMS的打印输出宏*/
#define SMS_LOG(Level, String) \
           PS_NAS_LOG(WUEPS_PID_SMS, 0, Level, String)

#define SMS_LOG1(Level, String, Para1) \
           PS_NAS_LOG1(WUEPS_PID_SMS, 0, Level, String, Para1)

#define SMS_LOG2(Level, String, Para1, Para2) \
           PS_NAS_LOG2(WUEPS_PID_SMS, 0, Level, String, Para1, Para2)

#define SMS_LOG3(Level, String, Para1, Para2, Para3) \
           PS_NAS_LOG3(WUEPS_PID_SMS, 0, Level, String, Para1, Para2, Para3)

#define SMS_LOG4(Level, String, Para1, Para2, Para3, Para4) \
           PS_NAS_LOG4(WUEPS_PID_SMS, 0, Level, String, Para1, Para2, Para3, Para4)

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                              /* __cpluscplus */

#endif
