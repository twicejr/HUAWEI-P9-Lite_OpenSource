#ifndef _MNTN_VIDEO_TYPES_H
#define _MNTN_VIDEO_TYPES_H

#ifdef MIT2_UT_SWITCH
#include <stdio.h>
#include <string.h>
#include <linux/printk.h>
#include <linux/err.h>
#endif

#ifndef MIT2_UT_SWITCH
#define STATIC static
#else
#define STATIC
#endif

/******************************************************************************
 * 2. 宏定义
 ******************************************************************************/
//static unsigned int g_MntnModuleId;


#define MAX_MODULE_NAME_LEN 32
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum{
    MNTN_NO_ERROR = 0,
    MNTN_ERROR
};

/* ModuleId */
typedef enum {
    EN_ID_MNTN_DATA_MODULE_ID_DEC  = 0,
    EN_ID_MNTN_DATA_MODULE_ID_ENC,
    EN_ID_MNTN_DATA_MODULE_ID_VPP,
    EN_ID_MNTN_DATA_MODULE_ID_CAMERA_PRE_DQ,
    EN_ID_MNTN_DATA_MODULE_ID_MAX
} mntn_data_module_id_type;

/* data type */
typedef enum {
    EN_VIDEO_IMAGE = 0,
    EN_VIDEO_VIDEO,
    EN_VIDEO_MAX
}mntn_data_save_type;

typedef struct MNTN_DATA_SAVE_MODULE{
    char                ModuleName[MAX_MODULE_NAME_LEN];
    unsigned            FrameNum;
    mntn_data_save_type ImageOrVideo;
}mntn_data_save_module;

/* Add moudle id here */
typedef enum{
    EN_ID_MNTN_CAM_COM_LOG_MODULE = 0,
    EN_ID_MNTN_CAM_DUMPREG_LOG_MODULE,
    EN_ID_MNTN_BLVIDEO_DRV_DEC,
    EN_ID_MNTN_BLVIDEO_DRV_ENC,
    EN_ID_MNTN_BLVIDEO_DRV_MEMALLOC,
    EN_ID_MNTN_BLVIDEO_DRV_MEMALLOC_MEMHEAP,

    EN_ID_MNTN_TEST_LOG_MODULE = 255,
    EN_ID_MNTN_LOG_MODULE_MAX = 256
}mntn_log_module_id_enum;

/* define different Log level */
//should not use MNTN_LOG_OFF level when print,
//used for turn off log when echo
typedef enum{
    EN_VIDEO_LOG_LEVLE_OFF =0,
    EN_VIDEO_LOG_LEVLE_ERROR,
    EN_VIDEO_LOG_LEVLE_WARNNING,
    EN_VIDEO_LOG_LEVLE_INFO,
    EN_VIDEO_LOG_LEVLE_DEBUG,
    EN_VIDEO_LOG_LEVEL_MAX
}mntn_log_level_enum;

typedef struct MNTN_LOG_MODULE{
    uint8_t   log_level;
    char      module_name[MAX_MODULE_NAME_LEN];
}mntn_log_module_t;

#endif


