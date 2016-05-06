/******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : video_mntn_kernel.h
  Author      : ---
  Version     : V900R100
  Date        : 2012-09-12
  Description : 该头文件定义了集成二组KERNEL层的可维可测
  History     :
  1. Date:2012-09-12
     Author: z62576
     Modification:Create
******************************************************************************/

#ifndef __MEDIA_MNTN_KERNEL_H__
#define __MEDIA_MNTN_KERNEL_H__


/******************************************************************************
  1 其他头文件包含
******************************************************************************/

#include "media_mntn_kernel_om_interface.h"
//#include "../../../../../../include/med/media_mntn_kernel_om_interface.h"

/******************************************************************************
  2 宏定义
******************************************************************************/

/* 临终遗言 TAG */
#define EXCH_CB_NAME_SIZE       (28)

/* DRV_EXCH_CUST_FUNC_REG的返回值EXCH_OK表示正确，其他值都是错误值 */
#define EXCH_OK         (0)
#define EXCH_ERROR      (-1)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum mntn_bool_enum {
    MNTN_OK     = 0,
    MNTN_ERR    = 1
};

enum mntn_trace_msg_attrib_enum {
    MNTN_TRACE_MSG_NO = 0,
    MNTN_TRACE_MSG_YES,
    MNTN_TRACE_MSG_ATTRIB_MAX
};
typedef unsigned char   mntn_trace_msg_attrib_enum_u8;

/* module_id */
enum mntn_module_id_enum {
    /* VIDEO_FUNCTION_TYPE */
    MNTN_MODULE_ID_DEC  = 0,
    MNTN_MODULE_ID_ENC,
    MNTN_MODULE_ID_VPP,
    MNTN_MODULE_ID_CAMERA,

    /* DISP_FUNCTION_TYPE */
    MNTN_MODULE_ID_EDC,
    MNTN_MODULE_ID_GPU,
    MNTN_MODULE_ID_HDMI,

    /* MNTN */
    MNTN_MODULE_ID_MNTN,

    MNTN_MODULE_ID_MAX = MNTN_MODULE_ID_MNTN
};
typedef unsigned char   mntn_module_id_enum_u8;


/******************************************************************************
  4 全局变量声明
******************************************************************************/

extern unsigned int            g_mntn_print_level[MNTN_MODULE_ID_MAX + 1];

/******************************************************************************
 * log
 ******************************************************************************/
#define mntn_loge(module_id, fmt, ...) {    \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_ERR)) { \
        printk(KERN_ALERT "[" LOG_TAG "]" "ERR func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);  \
    }   \
}

#define mntn_logw(module_id, fmt, ...) {    \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_WARNING)) { \
        printk(KERN_ALERT "[" LOG_TAG "]" "WARRING func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);  \
    }   \
}

#define mntn_logi(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_INFO)) {\
        printk(KERN_ALERT "[" LOG_TAG "]" "INFO func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    }   \
}

#define mntn_logd(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_DEBUG)) {\
        printk(KERN_ALERT "[" LOG_TAG "]" "DEBUG func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);\
    }   \
}

/******************************************************************************
 * log with timestamp
 ******************************************************************************/
#define mntn_loge_time(module_id, fmt, ...) {   \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_ERR)) { \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " ERR **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__);   \
    }   \
}

#define mntn_logw_time(module_id, fmt, ...) {   \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_WARNING)) { \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " WARRING **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__);   \
    }   \
}

#define mntn_logi_time(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_INFO)) {    \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " INFO **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__);  \
    }   \
}

#define mntn_logd_time(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_DEBUG)) {   \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " DEBUG **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__); \
    }   \
}

/******************************************************************************
  5 消息头定义
******************************************************************************/


/******************************************************************************
  6 消息定义
******************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/******************************************************************************
结构名    : om_api_func_t
结构说明  : 可维可测模块需要用到的OM的API函数集合
*******************************************************************************/
typedef struct {
    om_reg_request_func om_reg_request;   /* OM API: OM_AcpuRegisterReqProc */
    om_add_sn_time_func om_add_sn_time;   /* OM API: OM_AddSNTime*/
}om_api_func_t;

/******************************************************************************
结构名    : mntn_config_data
结构说明  : OM发给mntn模块的具体配置数据，对应mntn_trace_req_t中的data域
*******************************************************************************/
typedef struct {
    unsigned char   event;              /* 事件配置 */
    unsigned char   reg;                /* 寄存器配置 */
    unsigned char   frame_info;         /* 帧信息配置 */
    unsigned char   context;            /* 上下文配置 */
    unsigned char   print_level;        /* 打印级别 */
    unsigned char   rsv_0;              /* reserve区域 */
    unsigned char   rsv_1;              /* reserve区域 */
    unsigned char   rsv_2;              /* reserve区域 */
}mntn_config_data_t;

/******************************************************************************
结构名    : mntn_trace_req_t
结构说明  : OM发给mntn模块的配置消息，对应MNTN_PRIM_ID_xxx_CFG_REQ消息
*******************************************************************************/
typedef struct {
    unsigned char   func_type;          /* IT2's module ID */
    unsigned char   cpu_id;             /* filled with 1 (ACPU) */
    unsigned short  length;             /* msg length after 'length' domain */
    unsigned short  prim_id;            /* message ID */
    unsigned short  rsv_0;              /* reserved */
    unsigned char   data[4];            /* message content, 与OM核对，需要8字节，对应结构体是mntn_config_data */
}mntn_trace_req_t;

/******************************************************************************
结构名    : mntn_trace_cnf_t
结构说明  : mntn模块发给OM的配置确认消息，对应MNTN_PRIM_ID_xxx_CFG_CNF消息
*******************************************************************************/
typedef struct {
    unsigned char   func_type;          /* IT2's module ID */
    unsigned char   cpu_id;             /* filled with 1 (ACPU) */
    unsigned short  length;             /* msg length after 'length' domain */
    unsigned int    sn;                 /* msg number of ACPU */
    unsigned int    timestamp;          /* timestamp got from board */
    unsigned short  prim_id;            /* message ID */
    unsigned short  module_id;          /* reserved --> module_id */
    unsigned int    result;             /* message content */
}mntn_trace_cnf_t;

/******************************************************************************
结构名    : mntn_trace_ind_t
结构说明  : mntn模块消息上报，发送到OM，对应MNTN_PRIM_ID_xxx_xxx_IND消息
*******************************************************************************/
typedef struct {
    unsigned char   func_type;          /* IT2's module ID */
    unsigned char   cpu_id;             /* filled with 1 (ACPU) */
    unsigned short  length;             /* msg length after 'length' domain */
    unsigned int    sn;                 /* msg number of ACPU */
    unsigned int    timestamp;          /* timestamp got from board */
    unsigned short  prim_id;            /* message ID */
    unsigned short  module_id;          /* reserved --> module id */
    unsigned char   data[4];            /* message content */
}mntn_trace_ind_t;

/******************************************************************************
结构名    : mntn_trace_simple_config_t
结构说明  : 某一条消息的配置(是否上报消息给OM)
*******************************************************************************/
typedef struct {
    mntn_trace_msg_attrib_enum_u8       config;
    unsigned char                       rsv[3];              /* reserved */
}mntn_trace_simple_config_t;

/******************************************************************************
结构名    : mntn_trace_config_t
结构说明  : 某一功能模块中各个消息的配置，如VDEC、VENC、VPP、CAMERA。
*******************************************************************************/
typedef struct
{
    mntn_trace_simple_config_t event_cfg;      /* 是否上报事件 */
    mntn_trace_simple_config_t reg_cfg;        /* 是否上报寄存器 */
    mntn_trace_simple_config_t frame_info_cfg; /* 是否上报帧信息 */
    mntn_trace_simple_config_t context_cfg;    /* 是否上报上下文信息 */
}mntn_trace_config_t;

/******************************************************************************
结构名    : mntn_reg_cfg_t
结构说明  : 勾取哪些寄存器的配置
*******************************************************************************/
typedef struct {
    unsigned int     module_id;
    unsigned long    addr_base;
    unsigned long    addr_offset;
} mntn_reg_cfg_t;

/******************************************************************************
结构名    : mntn_simple_reg_data_t
结构说明  : 单个寄存器的数据结构
*******************************************************************************/
typedef struct {
    unsigned long    addr;
    unsigned int     data;
} mntn_reg_data_t;

/******************************************************************************
结构名    : mntn_reg_data_t
结构说明  : 上报寄存器的数据结构，此结构体待定，涉及ASN1解析
*******************************************************************************/
typedef struct {
    unsigned int        data_len;
    void               *reg_data;/* 对应结构体是mntn_reg_data_t */
} mntn_reg_info_t;

/******************************************************************************
结构名    : mntn_exch_cust_buf_t
结构说明  : 临终遗言回调函数的入参类型
*******************************************************************************/
typedef struct {
    char            name[EXCH_CB_NAME_SIZE];    /* 模块标志，自定义的字符串 */
    unsigned char  *data;                       /* 临终遗言数据存放的buffer，模块自己申请 */
    unsigned int    data_len;                   /* buffer的长度，小于8K */
} mntn_exch_cust_buf_t;

/******************************************************************************
结构名    : mntn_exch_cb
结构说明  : 临终遗言回调函数类型
*******************************************************************************/
// 2012-11-24
typedef int (*mntn_exch_cb) (mntn_exch_cust_buf_t *);


/******************************************************************************
  8 UNION定义
******************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : mntn_send_event_msg
 功能描述  : MNTN上报事件消息的接口封装
 输入参数  : ulModuleId    - 模块ID，目前包含DEC/ENC/VPP/CAMERA，对应枚举mntn_module_id_t
             buffer        - 待发现数据存放的buffer
             length        - buffer的长度，小于4K
 输出参数  : NONE
 返 回 值  : void
*****************************************************************************/
void mntn_send_event_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 函 数 名  : mntn_send_reg_msg
 功能描述  : MNTN上报寄存器消息的接口封装
 输入参数  : ulModuleId    - 模块ID，目前包含DEC/ENC/VPP/CAMERA，对应枚举mntn_module_id_t
             buffer        - 待发现数据存放的buffer
             length        - buffer的长度，小于4K
 输出参数  : NONE
 返 回 值  : void
*****************************************************************************/
void mntn_send_reg_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 函 数 名  : mntn_send_frame_info_msg
 功能描述  : MNTN上报帧信息消息的接口封装
 输入参数  : ulModuleId    - 模块ID，目前包含DEC/ENC/VPP/CAMERA，对应枚举mntn_module_id_t
             buffer        - 待发现数据存放的buffer
             length        - buffer的长度，小于4K
 输出参数  : NONE
 返 回 值  : void
*****************************************************************************/
void mntn_send_frame_info_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 函 数 名  : mntn_send_context_msg
 功能描述  : MNTN上报上下文信息消息的接口封装
 输入参数  : ulModuleId    - 模块ID，目前包含DEC/ENC/VPP/CAMERA，对应枚举mntn_module_id_t
             buffer        - 待发现数据存放的buffer
             length        - buffer的长度，小于4K
 输出参数  : NONE
 返 回 值  : void
*****************************************************************************/
void mntn_send_context_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 函 数 名  : mntn_save_reg_data
 功能描述  : 保存寄存器数据到BUFFER
 输入参数  : module_id - 模块ID
             buffer    - 寄存器存放的buffer，对应结构体是
             length    - buffer长度
 输出参数  : NONE
 返 回 值  : void
*****************************************************************************/
void mntn_save_reg_data(mntn_module_id_enum_u8 module_id, const void *buffer, const int length);

/*****************************************************************************
 函 数 名  : mntn_save_frame_data
 功能描述  : 保存图像数据到FILE
 输入参数  : module_id     - 模块ID，目前包含DEC/ENC/VPP/CAMERA，对应枚举mntn_module_id_t
             buffer        - 待发现数据存放的buffer
             length        - buffer的长度，小于4K
 输出参数  : NONE
 返 回 值  : void
*****************************************************************************/
void mntn_save_frame_data(mntn_module_id_enum_u8 module_id, const void *buffer, const int length);

/*****************************************************************************
 函 数 名  : mntn_exch_cb_register
 功能描述  : 临终遗言, MNTN提供给集成组的接口，各个模块通过register函数将自己的
             回调函数注册给MNTN模块中。
             回调函数使用的buffer长度小于8K, 存在与内核态
 输入参数  : module_id    - 模块ID
             func         - 各个模块的回调函数
 输出参数  : NONE
 返 回 值  : int，MNTN_OK注册成功, MNTN_ERR注册失败
*****************************************************************************/
int mntn_exch_cb_register(mntn_module_id_enum_u8 module_id, mntn_exch_cb func);

/*****************************************************************************
 函 数 名  : mntn_set_print_level
 功能描述  : MNTN提供给OM的接口，OM用于下发可维可测配置，内部接口
 输入参数  : module_id  - 模块ID
             level      - 0~4级，参见MNTN_LOG_LEVEL_OFF等宏定义
 输出参数  : NONE
 返 回 值  : int, 返回最终配置的level
*****************************************************************************/
int mntn_set_print_level(mntn_module_id_enum_u8 module_id, unsigned int level);

#endif /* __MEDIA_MNTN_KERNEL_H__ */

