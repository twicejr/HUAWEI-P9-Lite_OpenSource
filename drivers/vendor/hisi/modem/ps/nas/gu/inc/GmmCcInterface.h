/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCcInterface.h
  Description : CC与GMM接口头文件
  History     :
      1.       2009.05.11   文件头作成
*******************************************************************************/
#ifndef _GMM_CC_INTERFACE_H_
#define _GMM_CC_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)
/*******************************************************************************
**************************  GMM－CC 原语标识  ********************************
*******************************************************************************/

/* GMM发送给CC的原语 */
#define GMMCC_EMC_NUM_LST_IND                          0

/* 原语GMMCC_EMC_NUM_LST_IND的结构体 */
#define GMMCC_EMERGENCY_NUMBER_MAX_LENGTH              46                       /* Emergency Number information的最大字节数 */
#define GMMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER        16                       /* Emergency Number Lists的最多个数         */

typedef struct
{
    VOS_UINT8                           ucCategoryValue;                        /* Emergency Service Category Value         */
    VOS_UINT8                           ucEmcNumLen;
    VOS_UINT8                           aucEmergencyList[GMMCC_EMERGENCY_NUMBER_MAX_LENGTH];
}GMMCC_EMERGENCY_CONTENT_STRU;

/* 原语GMMCC_EMC_NUM_LST_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucEmergencyNumber;
    VOS_UINT8                           aucReserved[3];
    GMMCC_EMERGENCY_CONTENT_STRU        astEmergencyLists[GMMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER];
}GMMCC_EMERGENCY_LIST_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif
