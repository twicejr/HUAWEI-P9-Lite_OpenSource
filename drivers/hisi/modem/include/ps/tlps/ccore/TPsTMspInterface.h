

#ifndef __TPSTMSPINTERFACE_H__
#define __TPSTMSPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#include "LPSCommon.h"
#else
#define PS_MSG_ID_TDS_PS_BASE   0x1355
#define VOS_MSG_HEADER
#endif


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum
{
     ID_T_MSP_PS_AT_MODE_REQ                = (PS_MSG_ID_TDS_PS_BASE + 0x65),/*PS_MSG_ID_TDS_PS_BASE = 0x1355(4949)*/
     ID_T_MSP_PS_SFN_SYNC_REQ,
     ID_T_MSP_PS_DPCH_REQ,
     ID_T_PS_MSP_SFN_SYNC_CNF,
     ID_T_MSP_PS_STOP_REQ

};

enum
{
    ID_T_MSP_PS_OM_FUSE_AT_MODE_REQ         = 0x0065,
    ID_TOOL_TMODE_OM_FUSE_CNF               = ID_T_MSP_PS_OM_FUSE_AT_MODE_REQ,
    ID_T_MSP_PS_OM_FUSE_SFN_SYNC_REQ        = 0x00cd,
    ID_T_PS_MSP_OM_FUSE_SFN_SYNC_CNF        = ID_T_MSP_PS_OM_FUSE_SFN_SYNC_REQ,
    ID_T_MSP_PS_OM_FUSE_DPCH_REQ            = 0x00ce,
    ID_MSP_TOOL_OM_FUSE_TCFGDPCH_CNF        = ID_T_MSP_PS_OM_FUSE_DPCH_REQ,
    ID_T_MSP_PS_OM_FUSE_STOP_REQ            = 0x00cf,
    ID_MSP_TOOL_OM_FUSE_SSTOP_CNF           = ID_T_MSP_PS_OM_FUSE_STOP_REQ

};
/*****************************************************************************
   5 STRUCT
*****************************************************************************/
typedef struct T_MSP_PS_AT_MODE_REQ_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;
}T_MSP_PS_AT_MODE_REQ;

typedef struct T_MSP_PS_OM_FUSE_AT_MODE_REQ_Tag
{
    VOS_MSG_HEADER
    VOS_UINT16              usMsgId;
    VOS_UINT16              usComponentId;
    VOS_UINT16              usTmode;
    VOS_UINT16              usRsv;
}T_MSP_PS_OM_FUSE_AT_MODE_REQ;

typedef struct T_MSP_PS_SFN_SYNC_REQ_Tag
{
    //VOS_MSG_HEADER
    //VOS_UINT32                  ulMsgName;
    VOS_UINT16                    cellID;
    VOS_UINT16                     freq;
}T_MSP_PS_SFN_SYNC_REQ;

typedef struct T_MSP_PS_OM_FUSE_SFN_SYNC_REQ_Tag
{
    VOS_MSG_HEADER
    VOS_UINT16              ulMsgName;
    VOS_UINT16              ulComponentId;
    VOS_UINT16              emMode;
    VOS_UINT16              emBand;
    VOS_UINT16              usUlFreqMHz;
    VOS_UINT16              usDlFreqMHz;
}T_MSP_PS_OM_FUSE_SFN_SYNC_REQ;


typedef struct T_PS_MSP_SFN_SYNC_CNF_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgName;
    VOS_UINT32              ulResult;
}T_PS_MSP_SFN_SYNC_CNF;


typedef struct T_PS_MSP_OM_FUSE_CNF_Tag
{
    VOS_MSG_HEADER
    VOS_UINT16              ulTransPrimID;
    VOS_UINT16              ulResevered;
    VOS_UINT16              ulMsgId;
    VOS_UINT16              ulComponentId;
    VOS_UINT32              ulContext;
}T_PS_MSP_OM_FUSE_CNF;

typedef struct T_MSP_PS_DPCH_REQ_Tag
{
    //VOS_MSG_HEADER
    //VOS_UINT32                 ulMsgName;
    VOS_UINT32                   ulTransType;
    VOS_UINT16                   ulTpcStep;
    VOS_UINT16                   ulRsv;
}T_MSP_PS_DPCH_REQ;

typedef struct T_MSP_PS_OM_FUSE_DPCH_REQ_Tag
{
    VOS_MSG_HEADER
    VOS_UINT16              ulMsgName;
    VOS_UINT16              ulComponentId;
    VOS_UINT16              ulTransType;
    VOS_UINT16              ulTpcStep;
}T_MSP_PS_OM_FUSE_DPCH_REQ;

typedef struct T_MSP_PS_SSTOP_REQ_Tag
{
    VOS_MSG_HEADER
    VOS_UINT32             ulMsgName;
    VOS_UINT16             ulType;
    VOS_UINT16             ulRsv;
}T_MSP_PS_SSTOP_REQ;

typedef struct T_MSP_PS_OM_FUSE_SSTOP_REQ_Tag
{
    VOS_MSG_HEADER
    VOS_UINT16              ulMsgName;
    VOS_UINT16              ulComponentId;
    VOS_UINT16              ulType;
    VOS_UINT16              usRsv;
}T_MSP_PS_OM_FUSE_SSTOP_REQ;



extern VOS_UINT32 LHPA_InitDsp_ForAT( VOS_VOID );
extern VOS_UINT32 MSP_taskDelay_forAT( VOS_VOID );
extern VOS_UINT32 LHPA_LoadDspComm(VOS_VOID);






#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TPsTMspInterface.h */
