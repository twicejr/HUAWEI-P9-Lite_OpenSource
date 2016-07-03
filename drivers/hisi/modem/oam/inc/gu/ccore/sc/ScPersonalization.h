

#ifndef __SCOPERATOR_H__
#define __SCOPERATOR_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "omnvinterface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define   SC_IMSI_FIRST_BYTE        (0x08)                      /* IMSI第一个字节的值 */

#define   EF_IMSI_FILE_ID           (0x6F07)                    /* IMSI的文件ID */

#define   EF_GID1_FILE_ID           (0x6F3E)                    /* GID1的文件ID */

#define   SC_PLMN_LEN(plmn)         ((0x0F == (((*((plmn)+1))>>4)&0x0F))?5:6)   /* 判定PLMN的位数 */

#define   SC_IMSI_DEPART_LEN        (15)                        /* IMSI拆分长度 */

#define   SC_CODE_DEPART_LEN        (2*SC_MAX_CODE_LEN)         /* 号段拆分后的长度 */

#define   SC_NET_CODE_LEN           (3)                         /* 锁网号段长度 */

#define   SC_NETSUB_CODE_LEN        (4)                         /* 锁子网号段长度 */

#define   SC_SP_CODE_LEN            (4)                         /* 锁SP号段长度 */

#define   SC_NET_CODE_DEPART_LEN    (2*SC_NET_CODE_LEN)         /* 锁网号段拆分长度 */

#define   SC_SP_LEN                 (1)                         /* SP的长度 */

#define   SC_SP_DEPART_LEN          (2*SC_SP_LEN)               /* SP拆分长度 */

#define   SC_NET_SUB_DEPART_LEN     (2)                         /* 子网号拆分长度 */

#define   SC_CODE_FOURTH_NUM_INDEX  (3)                         /* 拆分后的锁网锁卡号码第四个数字的索引 */

#define   SC_MAX_CMP_IMEI           (3)                         /* 读IMEI最多校验次数 */

#define   SC_IMEI0_REPLACE_IMEI2_FLG    (0x5A5A)                /* 开启IMEI0替换IMEI2标记 */

#define   SC_CDMA_PLMN_LEN          (5)                         /* CDMA PLMN长度 */
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/

SC_PERS_PLATFORM_ENUM_UINT32 SC_PERS_SupportPlatform(
    MODEM_ID_ENUM_UINT16                enModemID
);


VOS_UINT32 SC_PERS_ChangeNum(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode);


VOS_UINT32 SC_PERS_CDMAImsiBcd2Num(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                    *pucImsi,
    VOS_UINT8                          *pucNum
);


VOS_UINT32 SC_PERS_CDMACheckCode(
    SC_SIMLOCK_CATEGORY_STRU           *pstSimLockCat,
    VOS_UINT8                          *pucIMSI,
    MODEM_ID_ENUM_UINT16                enModemID
);


VOS_UINT32 SC_PERS_CDMAVrifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    SC_PI_FILE_STRU                     *pstPIFile,
    MODEM_ID_ENUM_UINT16                 enModemID
);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
