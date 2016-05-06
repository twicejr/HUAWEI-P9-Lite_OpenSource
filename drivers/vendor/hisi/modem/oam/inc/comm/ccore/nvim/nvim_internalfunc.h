/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: NVIM_InternalFunc.h                                             */
/*                                                                           */
/* Author: Jiang kaibo                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: 存放内容供 NVIM 模块内部使用.                            */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-06                                                          */
/*    Author: Jiang kaibo                                                    */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/


#ifndef _NVIM_INTERNALFUNC_H
#define _NVIM_INTERNALFUNC_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "comm_adapter.h"
#include "nvim_comminterface.h"
#include "nvim_fileoperateinterface.h"

#if ( VOS_VXWORKS == VOS_OS_VER )
#include "vmLib.h"
#include "vmLibCommon.h"
#endif


#pragma pack(4)

/*lint -e413*/
#define GET_IE_OFFSET(a,b)      (unsigned long)((void *)(&(((a*)0)->b)))
/*lint +e413*/

/* NV Read Mask */
#define NV_READ_MASK            0x03
/* Read Ctrl Def. */
#define NVIM_READ_ABLE          0x00
#define NVIM_READ_UNABLE        0x01
#define NVIM_READ_AUTH          0x02
#define NVIM_INVALID            0x03

/* NV Write Mask */
#define NV_WRITE_MASK           0x0C
/* NV Write Count Mask */
#define NV_WRITE_COUNT_MASK     0xff00
/* Write Ctrl Def. */
#define NVIM_WRITE_ABLE         0x00
#define NVIM_WRITE_UNABLE       0x01
#define NVIM_WRITE_COUNT_CTRL   0x02
#define NVIM_WRITE_AUTH         0x03

/* Change TTL to ms */
#define NV_TTL_CHANGE           100

/* NV Auth Code size */
#define NV_AUTH_CODE_SIZE       16

/* NV Absolute Path Len */
#define NV_ABSLT_PATH_LEN       100
#define NV_FILE_NAME_LEN        28

#define NV_CTRL_FILE_MAGIC_NUM  (0x224e4944)
#define NV_MAGIC_NUM            0x5A
#define NV_MAGIC_NUM_LEN        16
#define NV_CTRLFILE_INFO_LEN    128
#define NV_FILEHANDLE_INFO_LEN  256

#define NV_MAGICNUM_ADDR        (g_ulNVMemAddr)
#define NV_DATA_BASE_ADDR       (NV_MAGICNUM_ADDR+NV_MAGIC_NUM_LEN)

/* NV backup Buffer Size */
#if (VOS_WIN32 != VOS_OS_VER)
#if defined(CHIP_BB_HI6758)
#define NV_BUFFER_SIZE          (0x00060000)
#else
#define NV_BUFFER_SIZE          (0x001a0000)
#endif
#else
#define NV_BUFFER_SIZE          (0x001a0000)
#endif

/* NV backup Buffer Size */
#define NV_BACKUP_BUFFER_SIZE   (NV_BUFFER_SIZE)

/* NV backup file min num */
#define NV_BACKUP_FILE_MIN_NUM  (1)
/* NV File Backup Info */
#define NV_BACKUP_FILE_MAX_NUM  (20)

#define NV_ARM_ALIGNMENT        0x03

#define NV_IPC_TIME_FOREVER     (50000)

#define NV_ALIGNMENT_SIZE(size) (((size)+NV_ARM_ALIGNMENT)&(~NV_ARM_ALIGNMENT))

#define NV_MEMCPY( Dest, Src, Count )\
    NV_MemCpy( (Dest), (Src), (Count), VOS_FILE_ID, __LINE__ )

#define PS_TURN_ON_UPDATE_VERSION_LED()         DRV_LED_FLUSH(LED_LIGHT_NORMAL_UPDATING)

#define PS_TURN_ON_UPDATE_VERSION_FAIL_LED()    DRV_LED_FLUSH(LED_LIGHT_UPDATE_FAIL)

#define PS_TURN_ON_UPDATE_VERSION_SUCCESS_LED() DRV_LED_FLUSH(LED_LIGHT_UPDATE_SUCCESS)

#define PS_TURN_ON_UPDATE_VERSION_NVFAIL_LED()  DRV_LED_FLUSH(LED_LIGHT_UPDATE_NVFAIL)

#define NV_LOG_MAX_LEN                  (512)                   /* the max length of written log. */
#define NV_LOG_FILE_MAX_SIZE            (NV_LOG_MAX_LEN*100)    /* the max size of log file. */

#define NVIM_FL_EVENT_DATA_LEN      24

#define NV_PRI_MID_LEVEL_NUM                  (6)      /* 中优先级别数量 */

#define NV_GET_AVAILABE_RIGHT_BITS(value)     ((value) & 0x07)

#define NV_FLUSH_TASK_PRIORITY_LOW            (215)    /* 低优先级任务 */

#define NV_FULSH_ID                           (0xFFFF) /* NV_Flush 执行失败上报ID */

#define NV_MSG_HEADER_LEN                     (8)

#define NV_MAX_CARRIER_NAME_LEN         (40)                     /* 运营商名称最大长度 不包括\0 */
#define NV_MAX_IMAGE_NAME_LEN           (32)                     /* IMAGE 名称最大长度 不包括\0 */
#define NV_MIN_CARRIER_PATH_LEN         (6)                      /* 运营商路径最小长度 不包括\0*/
#define NV_MIN_IMAGE_PATH_LEN           (4)                      /* IMAGE 路径最小长度 不包括\0*/
#define NV_MAX_CARRIER_PATH_LEN         (100)                    /* 运营商路径最大长度 不包括\0*/
#define NV_MAX_IMAGE_PATH_LEN           (100)                    /* IMAGE 路径最大长度 不包括\0*/

#if ( VOS_WIN32 == VOS_OS_VER )
#define NV_SKU_CARRIER_PATH_LEVEL       (4)                      /* 运营商所在层级 */
#define NV_SKU_IMAGE_PATH_LEVEL         (3)                      /* IMAGE 所在层级 */
#else
#define NV_SKU_CARRIER_PATH_LEVEL       (3)                      /* 运营商所在层级 */
#define NV_SKU_IMAGE_PATH_LEVEL         (2)                      /* IMAGE 所在层级 */
#endif

#define NV_MAX_PATH_LEN                 (255)                    /* 文件路径最大长度 不包括\0 */
#define NV_MAX_PATH_SIZE                (NV_MAX_PATH_LEN + 1)    /* 文件路径最大长度 包括\0 */
#define NV_MAX_UPDEATE_PATH_LEN         (130)                    /* NV更新区文件夹所在路径最大长度 不包括\0 */
#define NV_MAX_DEFAULT_PATH_LEN         (130)                    /* NV默认区文件夹所在路径最大长度 不包括\0 */

#define NV_ID_WRITE_SLICE_MAX_NUM       (20)                     /* 最多能记录20组 写NV 的slice值 */

enum NVIM_EVENT_NAME_ENUM
{
    NVIM_EVENT_WRITE        = 5,
    NVIM_EVENT_BUTT
};

enum
{
    NV_AREA_WRITABLE,
    NV_AREA_NO_WRITABLE
};

typedef VOS_UINT32  NV_AREA_ACCESS_CTRL_ENUM_UINT32;


enum NVIM_EVENT_ERROR_ENUM
{
    NVIM_NO_ERROR           = 0,
    NVIM_SEEK_FILE_ERROR,
    NVIM_WRITE_FILE_ERROR,
    NVIM_EVENT_ERROR_BUTT
};

/* 备份到区写选项 */
enum NVIM_BACKUP_WRITE_FALSH_ENUM
{
    NVIM_BACKUP_WRITE_BASE_SPACE                    = 0,   /* 原有Flash区备份 */
    NVIM_BACKUP_WRITE_BASE_AND_EXT_SPACE            = 1,   /* 原有分区和扩展Flash区备份 */
    NVIM_BACKUP_WRITE_SPACE_BUTT
};
typedef VOS_UINT32 NVIM_BACKUP_WRITE_FLASH_ENUM_UINT32;

/* 备份到区读选项 */
enum NVIM_BACKUP_READ_FALSH_ENUM
{
    NVIM_BACKUP_READ_BASE_SPACE                    = 0,   /* 原有Flash区备份 */
    NVIM_BACKUP_READ_EXT_SPACE                    = 1,    /* 扩展Flash区备份 */
    NVIM_BACKUP_READ_SPACE_BUTT
};
typedef VOS_UINT32 NVIM_BACKUP_READ_FLASH_ENUM_UINT32;

/* 恢复读选项 */
enum NVIM_RESTORE_TYPE_ENUM
{
    NVIM_RESTORE_BASE_SPACE                  = 0,   /* 原有分区恢复*/
    NVIM_RESTORE_EXT_SPACE                   = 1,    /* 扩展分区恢复*/
    NVIM_RESTORE_SPACE_BUTT
};
typedef VOS_UINT32 NVIM_RESTORE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NV_PRIORITY_ENUM
 枚举说明  : 指定NV优先级别

  1.日    期   : 2012年05月23日
    作    者   : d00212987
    修改内容   : V7R1C50 Flashless PhaseII项目新增枚举
*****************************************************************************/
enum NV_PRIORITY_ENUM
{
    NV_PRIORITY_HIGH      = 0x00,
    NV_PRIORITY_MIDDLE1,
    NV_PRIORITY_MIDDLE2,
    NV_PRIORITY_MIDDLE3,
    NV_PRIORITY_MIDDLE4,
    NV_PRIORITY_MIDDLE5,
    NV_PRIORITY_MIDDLE6,
    NV_PRIORITY_LOW       = 0x07,
    NV_PRIORITY_BUTT
};
typedef VOS_UINT16 NV_PRIORITY_ENUM_UINT16;

/*****************************************************************************
 枚举名    : NV_MSG_ENUM
 枚举说明  :

  1.日    期   : 2012年05月29日
    作    者   : d00212987
    修改内容   : V7R1C50 Flashless PhaseII项目新增枚举
*****************************************************************************/
enum NV_MSG_TYPE_ENUM
{
    NV_FLUSH_NOTIFY_IND   = 0x0001,
    NV_MSG_BUTT           = 0XFFFF
};
typedef VOS_UINT32 NV_MSG_TYPE_ENUM_UINT32;

typedef struct
{
    VOS_UINT32      ulOffset;
    VOS_UINT32      ulSize;
}NV_FILE_HANDLE_STRU;

#if(( VOS_WIN32 == VOS_OS_VER ) || ( VOS_VXWORKS == VOS_OS_VER ) || (VOS_RTOSCK == VOS_OS_VER))
/* NV File Info Struct */
typedef struct
{
    FILE *fp;                    /* NV File Handle */
}NV_RESUME_FILE_HANDLE_STRU;
#endif

/* NV Ctrl File Header Struct */
typedef struct
{
    VOS_UINT32  ulMagicNum;
    VOS_UINT32  ulCtrlFileSize;      /* ctrl file size */
    VOS_UINT16  usVersionInfo;       /* ctrl file version */
    VOS_UINT8   ucModemNum;          /* NV Supprot the Modem Number;1:one instance;2: two instance; */
    VOS_UINT8   ucRsv;
    VOS_UINT32  ulFileListOffset;    /* Offset of the File list start address */
    VOS_UINT32  ulFileListNum;       /* File num at file list */
    VOS_UINT32  ulFileListSize;      /* File list size */
    VOS_UINT32  ulNvRefOffset;       /* Offset of the NV reference data start address */
    VOS_UINT32  ulNvRefCount;        /* NV ID num */
    VOS_UINT32  ulNvRefSize;         /* NV reference data size */
    VOS_UINT32  aulRsv[3];
    VOS_UINT32  aulTimeTag[4];       /* the time of the file creating */
    VOS_UINT32  aulProductInfo[8];   /* product version info */
}NV_CONTROL_FILE_INFO_STRU;

/* NV File List Struct */
typedef struct
{
    VOS_UINT32  ulFileId;                      /* NV File ID */
    VOS_UINT8   aucFileName[NV_FILE_NAME_LEN]; /* NV File Name, the max name len is 28 including file type */
    VOS_UINT32  ulFileSize;                    /* NV File size */
}NV_FILE_LIST_INFO_STRU;

/* NV reference Data Struct */
typedef struct
{
    VOS_UINT16  usNvId;     /* NV ID */
    VOS_UINT16  usNvLength; /* Single NV Length */
    VOS_UINT32  ulNvOffset; /* Offset of the NV ID start address at the Common NV file */
    VOS_UINT16  usFileId;   /* File ID */
    VOS_UINT16  usProperty; /* NV property.just bit0 - bit3 in use. 0:write immediately; 7:write after power off;others reserve */
    VOS_UINT8   ucModemNum; /* NV Supprot the Modem Number;1:one instance;2: two instance; */
    VOS_UINT8   aucRsv[3];  /* RSV */
}NV_REFERENCE_DATA_INFO_STRU;

/* 函数多参数提取成结构体 */
typedef struct
{
    VOS_UINT16  usFileId;   /* File ID */
    VOS_UINT8   ucModemNum; /* NV Data Number,0: only one value, 1: support dual modem, two values */
    VOS_UINT8   ucRsv;      /* RSV */
    VOS_UINT8   aucFileName[NV_FILE_NAME_LEN]; /* NV id name  */
    VOS_UINT32  ulNvOffset;                    /* Offset of the NV ID start address at the Common NV file */
    VOS_UINT32  ulTotalOffset;                 /* 相对缓存中NV 头位置 */
    VOS_UINT16  usProperty;
    VOS_UINT16  usRsv;
}NV_ID_RETUEN_INFO_STRU;

/*****************************************************************************
 结构名    : NV_PRIORITY_THRESHOLD_STRU
 结构说明  :  NV 优先级阈值

  1.日    期   : 2012年05月23日
    作    者   : d00212987
    修改内容   : V7R1C50 Flashless PhaseII项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16  ausNvMiddle[NV_PRI_MID_LEVEL_NUM];           /* 中优先级的阈值 */
    VOS_UINT16  ausRsv[2];                                   /* 保留 */
}NV_PRIORITY_THRESHOLD_STRU;

/*发给OM的Event的数据结构*/
typedef struct
{
    VOS_UINT16  usNVId;             /* NVID*/
    VOS_UINT16  usOffset;           /* Offset */
    VOS_UINT32  ulResult;           /* NV操作结果 */
    VOS_UINT32  ulNVDataLen;        /* NV数据长度 */
    VOS_UINT8   aucData[NVIM_FL_EVENT_DATA_LEN];/* 只上报前24个数据 */
}NVIM_FL_EVENT_DATA_STRU;

#if 0
/*****************************************************************************
 结构名    : NVIM_FLUSH_MSG_STRU
 结构说明  :  NV Flush更新消息原语

  1.日    期   : 2012年05月23日
    作    者   : d00212987
    修改内容   : V7R1C50 Flashless PhaseII项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* 消息原语 */
}NVIM_FLUSH_MSG_STRU;
#endif

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )

extern VOS_CHAR         *g_aucNvFolderPath; /* NV File path */
#else

/* Absolute Path for Operating NV file */
extern const VOS_CHAR   g_aucNvFolderPath[]; /* NV File path */
#endif

extern const VOS_CHAR   g_aucNvFilePath[];

extern VOS_UINT32       g_ulNVInitStartSlice;

extern VOS_UINT32       g_ulNVInitEndSlice;

extern VOS_SEM          g_ulNVInitSem;

/* SKU NV Struct */
typedef struct
{
    VOS_UINT16   usNvId;            /* NV ID */
    VOS_UINT16   usNvLength;        /* NV 长度 */
    VOS_UINT8    aucData[4];        /* NV 内容 */
}NV_SKU_DATA_INFO_STRU;

/* 运营商路径 */
typedef struct
{
    VOS_CHAR     acCarrierPath[NV_MAX_CARRIER_PATH_LEN + 1];        /* 运营商路径 */
    VOS_CHAR     acRsv[3];
}NV_CARRIER_PATH_STRU;

/* Image路径 */
typedef struct
{
    VOS_CHAR     acImagePath[NV_MAX_IMAGE_PATH_LEN + 1];            /* Image路径 */
    VOS_CHAR     acRsv[3];
}NV_IMAGE_PATH_STRU;

/* NV 文件夹路径 */
typedef struct
{
    VOS_CHAR   *pDirPath;           /* 文件夹路径 */
}NV_DIR_PATH_STRU;

/* 存放NV 操作时间 */
typedef struct
{
    VOS_UINT32   ulFlag;                 /* 用作写数据保护 */
    VOS_UINT16   usNvId;                 /* NV ID */
    VOS_UINT16   usRsv;
    VOS_UINT32   ulNvOperateSlice;       /* 操作Nv id时间 */
}NV_ID_OPERATE_Slice_STRU;

/* 存放NV数据的内存块 */
extern NV_CONTROL_FILE_INFO_STRU *g_pstNVDataBuf;

/* NV's ID coms from 1 to 20 */
extern NV_FILE_HANDLE_STRU    g_astNvFileHandle[];

/* 控制NV写操作的互斥信号量 */
extern VOS_SEM                g_ulNVWriteSem;

extern VOS_UINT_PTR           g_ulNVMemAddr;

VOS_VOID   NV_SetAreaAccessable(NV_AREA_ACCESS_CTRL_ENUM_UINT32 ulCtrlFlag);
VOS_UINT32 NV_Ctrl_File_Search_InMemory(VOS_UINT16 usID,NV_CONTROL_FILE_INFO_STRU *pstNVCtrlInfo,NV_FILE_LIST_INFO_STRU *pstFileListInfo,NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo);
VOS_UINT32 NV_ReadEx(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_WriteEx(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_WriteDirect(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_WriteDirectAll(VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength);
VOS_UINT32 NV_UpdateProc(VOS_VOID);
VOS_UINT32 NV_BackupProc(VOS_VOID);
VOS_UINT32 NV_RestoreProc(NVIM_RESTORE_TYPE_ENUM_UINT32 enRestoreType, VOS_BOOL bIsDefault, VOS_BOOL *pbIsCreatefile);
VOS_UINT32 NV_RestoreManufactureDefault(VOS_VOID);
VOS_UINT32 NV_CheckFactoryVer(VOS_VOID);
VOS_UINT32 NV_RestoreAll(VOS_VOID);
VOS_VOID   NV_ACoreInitSync(VOS_VOID);
VOS_UINT32 NV_Copy_Data_To_Memory(VOS_VOID);
VOS_UINT32 NV_Close_ALL_NV_File(VOS_VOID);
VOS_UINT32 NV_Open_ALL_NV_File(VOS_VOID);
VOS_UINT32 NV_Init(VOS_VOID);
VOS_UINT32 NV_WriteDataToFile(
    FILE                               *fp,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength,
    VOS_INT32                           lWriteOffset
);

VOS_UINT32 NV_NvIdCheck(MODEM_ID_ENUM_UINT16               enModemID,
                        VOS_UINT16                              usID,
                        VOS_UINT32                              ulOffset,
                        VOS_VOID                               *pItem,
                        VOS_UINT32                              ulLength,
                        NV_ID_RETUEN_INFO_STRU                 *pstNvIdReturnInfo);

VOS_UINT32 NV_GetLength(VOS_UINT16 usID, VOS_UINT32 *pulLength);
VOS_UINT32 NV_Backup(VOS_VOID);
VOS_UINT32 NV_ExNoBackup(VOS_VOID);
VOS_UINT32 NV_BackupOption(NVIM_BACKUP_WRITE_FLASH_ENUM_UINT32 enBackupWrite);
VOS_UINT32 NV_BackupCheck(VOS_VOID);
VOS_UINT32 NV_SkuBackupNvFile(VOS_VOID);
VOS_UINT32 NV_SkuSetDefAndUpDir(VOS_VOID);
VOS_UINT32 NV_SwitchCarrier(VOS_CHAR *pcCarrierName,VOS_UINT32 ulCarrierNameLen,VOS_BOOL *pbIsSwitchImage);
VOS_UINT32 NV_SelectCarrier(VOS_VOID);
VOS_UINT32 NV_SkuSwitchProc(VOS_VOID);
VOS_UINT32 NV_SkuUpdateSwitchFlag(VOS_VOID);
VOS_UINT32 NV_SkuRestoreNvFile(VOS_BOOL);
VOS_UINT32 NV_SkuRestoreNvFileRead(VOS_CHAR *pcFileName);
VOS_UINT32 NV_SkuBackupNvFileWrite(VOS_CHAR *pcFileName, VOS_UINT32 ulNvNum, VOS_UINT16 *pusNvId);
VOS_UINT32 NV_SkuGetOperatorPath(VOS_CHAR *pcFilePath);
VOS_VOID   NV_StrcatFilePath(VOS_CHAR *pcDest, VOS_CHAR* pcSrc1, VOS_CHAR* pcSrc2);
VOS_BOOL   NV_CheckImgWithCarrMatch(VOS_CHAR *pcCarrierDir, VOS_CHAR *pcImageDir);

VOS_UINT32 NV_Ctrl_File_Search_InMemory(VOS_UINT16                  usID,
                                                NV_CONTROL_FILE_INFO_STRU   *pstNVCtrlInfo,
                                                NV_FILE_LIST_INFO_STRU      *pstFileListInfo,
                                                NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo);

VOS_VOID NV_MemCpy( VOS_VOID * Dest, const VOS_VOID * Src,  VOS_UINT32 ulnbytes, VOS_UINT32 ulFileID, VOS_INT32 usLineNo );

VOS_VOID NV_BuildGlobalVar(VOS_VOID);

VOS_UINT32 NV_Printf(const VOS_CHAR *pcformat, ...);

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

#endif
