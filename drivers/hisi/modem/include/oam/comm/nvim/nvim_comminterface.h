


#ifndef _NVIM_COMMINTERFACE_H
#define _NVIM_COMMINTERFACE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*function return value*/
/* Return Value Def. */
#define NV_OK                           0
#define NV_ID_NOT_EXIST                 1
#define NV_BUFFER_TOO_LONG              2
#define NV_PART_DATA_ERR                3
#define NV_BUFFER_NOT_EXIST             4
#define NV_NOT_INIT                     5
#define NV_WRITE_NUMBER_END             6
#define NV_AUTH_NUMBER_END              7
#define NV_AUTH_ERR                     8
#define NV_READ_UNABLE                  9
#define NV_WRITE_UNABLE                 10
#define NV_ALLOC_BUFFER_FAIL            11
#define NV_OPEN_FILE_FAIL               12
#define NV_WRITE_FLASH_FAIL             13
#define NV_NO_BACKUP                    14
#define NV_FOLDER_CREAT_FAIL            15
#define NV_FILE_RESTORE_FAIL            16
#define NV_FOLDER_DEL_FAIL              17
#define NV_WRITE_SECURE_FAIL            18
#define NV_INIT_FAIL                    19
#define NV_FILE_TOO_LARGE               20
#define NV_UPDATE_SEC_FILE_ERR          21
#define NV_XCOPY_DEF_FAIL               22
#define NV_XCOPY_USE_FAIL               23
#define NV_USE_SEC_FILE_ERR             24
#define NV_RESUME_NV_FAIL               25
#define NV_DEFAULT_NOT_EXIST            26
#define NV_SEEK_FILE_FAIL               27
#define NV_FILE_DECODE_FAIL             28
#define NV_TAKE_SEM_FAIL                29
#define NV_SEND_MSG_FAIL                30
#define NV_FILE_ID_ERR                  31
#define NV_SMP_ERR                      32
#define NV_FILE_HANDLE_ERR              33
#define NV_MODEM_ID_ERR                 34

#define NV_SKU_CARRIER_PARA_ERR         35
#define NV_SKU_READ_SWITCH_FALG_ERR     36
#define NV_GET_CURRENT_CARRIER_NAME_ERR 37
#define NV_SKU_GET_CARRIER_PATH_ERR     38
#define NV_SKU_CARRIER_CONFIG_FILE_ERR  39
#define NV_SKU_CARRIER_NV_BACKUP_ERR    40
#define NV_SKU_WRITE_SWITCH_FALG_ERR    41
#define NV_SKU_WRITE_FILE_FAIL          42
#define NV_SKU_CREATE_FILE_FAIL         43
#define NV_SKU_XCOPY_UPDATE_FAIL        44
#define NV_WRITE_EXT_FLASH_FAIL         45
#define NV_Read_BASE_IMEI_FAIL          46
#define NV_Read_EXT_IMEI_FAIL           47

#define NV_RESTORE_RESULT_INIT          0x5A5A5A5A
#define NV_RESTORE_RUNNING              0x5A5A55AA
#define NV_ID_WRITE_SLICE_RECORD        0x5A5AA5A5

#define NV_WRITE_SLICE_RECORD_SIZE      (100*1024)

#define NV_INIT_ERROR                   0x2fffffff /* (NVIM模块) 复位文件 MODID */
/*****************************************************************************
 枚举名    :  NV_SYSTEM_ERROR_ENUM
 结构说明  :  NV模块中单板复位点枚举
  1.日    期   : 2013年4月2日
    作    者   : d00212987
    修改内容   : 新增
*****************************************************************************/
enum NV_SYSTEM_ERROR_ENUM
{
    NV_GET_DRV_FIX_DDR_ADDR_FAIL = 0x01,    /* 获取段内存熟悉失败，导致单板复位点 */
    NV_GET_CCORE_MAGIC_NUM_FAIL  = 0x02,    /* 获取C核写Mgaic Num 失败，导致单板复位点 */
    NV_SYSTEM_ERROR_BUTT
};
/*****************************************************************************
 结构名    : NV_LIST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 获取NV列表信息
*****************************************************************************/
typedef struct
{
    unsigned short usNvId;                  /*NVID值*/
    unsigned char  ucNvModemNum;            /*NV是否存在多份*/
    unsigned char  ucRsv;
}NV_LIST_INFO_STRU;

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

