

#ifndef __MMAUPHYINTERFACE_H__
#define __MMAUPHYINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum MMA_UPHY_MSG_ID_ENUM
{
    ID_UPHY_MMA_INIT_STATUS_IND                             = 0x1001,           /* _H2ASN_MsgChoice UPHY_MMA_INIT_STATUS_IND_STRU */

    ID_MMA_UPHY_POWER_ON_REQ                                = 0x1002,           /* _H2ASN_MsgChoice MMA_UPHY_POWER_ON_REQ_STRU */
    ID_UPHY_MMA_POWER_ON_CNF                                = 0x1003,           /* _H2ASN_MsgChoice UPHY_MMA_POWER_ON_CNF_STRU */

    ID_MMA_UPHY_POWER_OFF_REQ                               = 0x1004,           /* _H2ASN_MsgChoice MMA_UPHY_POWER_OFF_REQ_STRU */
    ID_UPHY_MMA_POWER_OFF_CNF                               = 0x1005,           /* _H2ASN_MsgChoice UPHY_MMA_POWER_OFF_CNF_STRU */

    ID_MMA_UPHY_MSG_ID_BUTT
};
typedef VOS_UINT32  MMA_UPHY_MSG_ID_ENUM_UINT16;


enum MMA_UPHY_INIT_STATUS_ENUM
{
    MMA_UPHY_INIT_STATUS_SUCCESS,
    MMA_UPHY_INIT_STATUS_FAIL,
    MMA_UPHY_INIT_STATUS_BUTT
};
typedef VOS_UINT16  MMA_UPHY_INIT_STATUS_ENUM_UINT16;



enum MMA_UPHY_RESULT_ENUM
{
    MMA_UPHY_RESULT_NO_ERROR                    = 0,
    MMA_UPHY_RESULT_ERROR,
    MMA_UPHY_RESULT_PARA_ERROR,
    MMA_UPHY_RESULT_BUTT
};
typedef VOS_UINT16 MMA_UPHY_RESULT_ENUM_UINT16;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/
#define MMA_UPHY_MSG_HEADER      VOS_MSG_HEADER \
                                    VOS_UINT16  usMsgID; \
                                    VOS_UINT16  ausReserved[1];

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct
{
    MMA_UPHY_MSG_HEADER                                                         /*_H2ASN_Skip*/
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enInitStatus;                           /* 物理层初始化状态 */
    VOS_UINT16                          ausReserved1[1];                        /*保留位*/
} UPHY_MMA_INIT_STATUS_IND_STRU;


typedef struct
{
    MMA_UPHY_MSG_HEADER                                                         /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;                              /* modemId */
    VOS_UINT16                          ausReserved1[1];                        /* 保留位 */
} MMA_UPHY_POWER_ON_REQ_STRU;


typedef struct
{
    MMA_UPHY_MSG_HEADER                                                         /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;                              /* modemId */
    MMA_UPHY_RESULT_ENUM_UINT16         enResult;                               /* 处理结果 */
} UPHY_MMA_POWER_ON_CNF_STRU;


typedef struct
{
    MMA_UPHY_MSG_HEADER                                                         /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;                              /* modemId */
    VOS_UINT16                          ausReserved1[1];                        /* 保留位 */
} MMA_UPHY_POWER_OFF_REQ_STRU;


typedef struct
{
    MMA_UPHY_MSG_HEADER                                                         /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;                              /* modemId */
    MMA_UPHY_RESULT_ENUM_UINT16         enResult;                               /* 处理结果 */
} UPHY_MMA_POWER_OFF_CNF_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    MMA_UPHY_MSG_ID_ENUM_UINT16         enMsgId;                    /*_H2ASN_MsgChoice_Export MTA_PHY_MSG_TYPE_ENUM_UINT16*/
    VOS_UINT16                          usRsv;                      /* ??? */
    VOS_UINT16                          ausMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTA_PHY_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MMA_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMA_PHY_MSG_DATA                    stMsgData;
}MmaPhyInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MtcComm.h */

