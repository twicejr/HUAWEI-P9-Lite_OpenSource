

#ifndef __NASRABMTEST_H__
#define __NASRABMTEST_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"
#include "NasERabmPublic.h"
#include "NasERabmIpFilter.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_ERABM_GetUlDataTransInfoAddr()                   (&g_stERabmUlDataTransInfo)

#define NAS_ERABM_GetDlDataTransInfoAddr()                   (&g_stERabmDlDataTransInfo)

/* 增加上行收到总数据包数 */
#define NAS_ERABM_AddUlReceivePackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulRecePackageNum++)

/* 增加上行发送总数据包数 */
#define NAS_ERABM_AddUlSendPackageNum()                      ((NAS_ERABM_GetUlDataTransInfoAddr())->ulSendPackageNum++)

/* 增加上行IDLE态总数据包数 */
#define NAS_ERABM_AddUlIdlePackageNum()                      ((NAS_ERABM_GetUlDataTransInfoAddr())->ulIdlePackageNum++)

/* 增加上行SUSPEND态总数据包数 */
#define NAS_ERABM_AddUlSuspendPackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulSuspendPackageNum++)

/* 增加上行丢弃总数据包数 */
#define NAS_ERABM_AddUlDiscardPackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulDiscPackageNum++)

/* 增加上行未找到承载总数据包数 */
#define NAS_ERABM_AddUlUnfoundBearerPackageNum()             ((NAS_ERABM_GetUlDataTransInfoAddr())->ulUnfoundBearerPackageNum++)

/* 增加上行DHCPV4 SERVER总数据包数 */
#define NAS_ERABM_AddUlDhcpv4ServerPackageNum()              ((NAS_ERABM_GetUlDataTransInfoAddr())->ulDhcpv4ServerPacketNum++)

/* 增加上行第一个分片包个数 */
#define NAS_ERABM_AddUlFirstSegmentPackageNum()              ((NAS_ERABM_GetUlDataTransInfoAddr())->ulFirstSegmentPacketNum++)

/* 增加上行分片包个数 */
#define NAS_ERABM_AddUlSegmentPackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulSegmentPacketNum++)

/* 增加上行未找到端口号包个数 */
#define NAS_ERABM_AddUlUnfoundPortPackageNum()               ((NAS_ERABM_GetUlDataTransInfoAddr())->ulUnfoundPortPacketNum++)

/* 获取承载的数传信息 */
#define NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId)       (&((NAS_ERABM_GetUlDataTransInfoAddr())->astBearerDataTransInfo[ulEpsbId-NAS_ERABM_MIN_EPSB_ID]))

/* 增加承载发送数据包个数 */
#define NAS_ERABM_AddBearerSendPackageNum(ulEpsbId)          ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulSendPackageNum++)

/* 增加承载丢弃数据包个数 */
#define NAS_ERABM_AddBearerDiscardPackageNum(ulEpsbId)       ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulDiscardPackageNum++)

/* 增加承载IDLE态数据包个数 */
#define NAS_ERABM_AddBearerIdlePackageNum(ulEpsbId)          ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulIdlePackageNum++)

/* 增加承载Suspend态数据包个数 */
#define NAS_ERABM_AddBearerSuspendPackageNum(ulEpsbId)          ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulSuspendPackageNum++)

/* 增加承载关联DRB不存在次数 */
#define NAS_ERABM_AddBearerNoDrbTimes(ulEpsbId)              ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulEpsbNoDrbTimes++)

/* 增加因承载关联DRB不存在而丢弃的数据包个数 */
#define NAS_ERABM_AddBearerNoDrbDiscardPackageNum(ulEpsbId)  ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulEpsbNoDrbDiscPackageNum++)

/* 增加下行收到总数据包数 */
#define NAS_ERABM_AddDlReceivePackageNum()                   ((NAS_ERABM_GetDlDataTransInfoAddr())->ulRecePackageNum++)

/* 增加下行发送总数据包数 */
#define NAS_ERABM_AddDlSendPackageNum()                      ((NAS_ERABM_GetDlDataTransInfoAddr())->ulSendPackageNum++)

/* 增加下行丢弃总数据包数 */
#define NAS_ERABM_AddDlDiscardPackageNum()                   ((NAS_ERABM_GetDlDataTransInfoAddr())->ulDiscPackageNum++)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/* 承载数传信息 */
typedef struct
{
    VOS_UINT32                          ulSendPackageNum;           /* 发送数据包数 */
    VOS_UINT32                          ulDiscardPackageNum;        /* 丢弃数据包数 */
    VOS_UINT32                          ulIdlePackageNum;           /* IDLE态数据包数 */
    VOS_UINT32                          ulSuspendPackageNum;        /* Suspend态数据包数 */
    VOS_UINT32                          ulEpsbNoDrbTimes;           /* 出现承载存在DRB不存在的次数 */
    VOS_UINT32                          ulEpsbNoDrbDiscPackageNum;  /* 因承载关联的DRB不存在而丢弃的数据包数*/
}NAS_ERABM_BERER_DATA_TRANS_INFO_STRU;

/* 上行数据传输信息结构体 */
typedef struct
{
    VOS_UINT32                          ulRecePackageNum;          /* 收到数据包总数 */
    VOS_UINT32                          ulSendPackageNum;          /* 发送数据包总数 */
    VOS_UINT32                          ulDiscPackageNum;          /* 丢弃数据包总数 */
    VOS_UINT32                          ulSuspendPackageNum;       /* DRB处于SUSPEND态时收到数据包数*/
    VOS_UINT32                          ulIdlePackageNum;          /* DRB处于IDLE态时收到数据包数 */
    VOS_UINT32                          ulDhcpv4ServerPacketNum;   /* DHCPV4 SERVER包总数 */
    VOS_UINT32                          ulFirstSegmentPacketNum;   /* 第一个分片包个数 */
    VOS_UINT32                          ulSegmentPacketNum;        /* 分片包个数 */
    VOS_UINT32                          ulUnfoundPortPacketNum;    /* 未找到端口号包个数 */
    VOS_UINT32                          ulUnfoundBearerPackageNum; /* 未找到承载的数据包数 */
    NAS_ERABM_BERER_DATA_TRANS_INFO_STRU astBearerDataTransInfo[NAS_ERABM_MAX_EPSB_NUM];  /* 承载的数传信息 */
}NAS_ERABM_UL_DATA_TRANS_INFO_STRU;

/* 下行数据传输信息结构体 */
typedef struct
{
    VOS_UINT32                          ulRecePackageNum;          /* 收到数据包总数 */
    VOS_UINT32                          ulSendPackageNum;          /* 发送数据包总数 */
    VOS_UINT32                          ulDiscPackageNum;          /* 丢弃数据包总数 */
}NAS_ERABM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_ERABM_UL_DATA_TRANS_INFO_STRU    g_stERabmUlDataTransInfo;
extern NAS_ERABM_DL_DATA_TRANS_INFO_STRU    g_stERabmDlDataTransInfo;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
extern VOS_VOID  NAS_ERABM_CmdHelp( VOS_VOID );
extern VOS_VOID  NAS_ERABM_DebugInit(VOS_VOID);
extern VOS_VOID  NAS_ERABM_ShowEpsBearerDataTransInfo( VOS_UINT32 ulEspbId );
extern VOS_VOID  NAS_ERABM_ShowActiveEpsBearerDataTransInfo( VOS_VOID );
extern VOS_VOID  NAS_ERABM_ShowUlDataTransInfo( VOS_VOID);
extern VOS_VOID  NAS_ERABM_ShowDlDataTransInfo( VOS_VOID );
extern VOS_VOID  NAS_ERABM_ShowEpsbTftInfo( VOS_UINT32 ulEspbId );



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

#endif /* end of NasERabmTest.h */
