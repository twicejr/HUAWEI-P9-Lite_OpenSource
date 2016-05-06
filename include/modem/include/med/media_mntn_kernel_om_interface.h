/******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : media_mntn_kernel_om_interface.h
  Author      : ---
  Version     : V900R100
  Date        : 2012-09-12
  Description : 该头文件定义了集成二组KERNEL层的可维可测
  History     :
  1. Date:2012-09-12
     Author: z62576
     Modification:Create
******************************************************************************/

#ifndef __MEDIA_MNTN_KERNEL_OM_INTERFACE_H__
#define __MEDIA_MNTN_KERNEL_OM_INTERFACE_H__


/******************************************************************************
  1 其他头文件包含
******************************************************************************/


/******************************************************************************
  2 宏定义
******************************************************************************/

#define VIDEO_CPU_ID                (1)          /* ACPU */

#define DISP_FUNCTION_TYPE          (51)         /* IT1's type for SDT message */
#define VIDEO_FUNCTION_TYPE         (52)         /* IT2's type for SDT message */

#define MNTN_MSG_MAX_LENGTH         (4 * 1024) /*可维可测上报到SDT的消息最大长度*/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* printk level */
typedef enum {
    MNTN_LOG_LEVEL_OFF  = 0,
    MNTN_LOG_LEVEL_ERR,
    MNTN_LOG_LEVEL_WARNING,
    MNTN_LOG_LEVEL_INFO,
    MNTN_LOG_LEVEL_DEBUG,
    MNTN_LOG_LEVEL_MAX
}mntn_print_level_e;

/* OM API ID used by IT2 */
typedef enum {
    MNTN_OM_FUNC_ID_REGISTER_REQ   = 0,    /* OM register request API */
    MNTN_OM_FUNC_ID_ADD_SN_TIME,           /* API of getting serial number and timestamp */
    MNTN_OM_FUNC_ID_MAX
}om_api_func_id_e;

/* 消息ID命名规则，以EDC为例:
   config配置消息   范围是0x2000~0x20FF
   event ID         范围是0x2100~0x21FF
   reg ID           范围是0x2200~0x22FF
   frame info ID    范围是0x2300~0x23FF
   context ID       范围是0x2400~0x24FF */
typedef enum {
    ID_VIDEO_MSG_INVALID          = 0x0000,

    /*Frame Data Config*/
    ID_FRAME_DATA_CFG_REQ     = 0x1000,
    ID_FRAME_DATA_CFG_CNF     = 0x1001,

    /*Video Dec Config*/
    ID_DEC_CFG_REQ            = 0x2000,   /*DEC模块消息配置请求*/
    ID_DEC_CFG_CNF            = 0x2001,   /*DEC模块消息配置确认*/
    ID_DEC_EVENT_IND          = 0x2100,   /*DEC模块事件上报*/
    ID_DEC_REG_IND            = 0x2200,   /*DEC模块寄存器上报*/
    ID_DEC_FRAME_INFO_IND     = 0x2300,   /*DEC模块帧信息上报*/
    ID_DEC_CONTEXT_IND        = 0x2400,   /*DEC模块上下文信息上报*/

    /*Video Enc Config*/
    ID_ENC_CFG_REQ            = 0x3000,
    ID_ENC_CFG_CNF            = 0x3001,
    ID_ENC_EVENT_IND          = 0x3100,
    ID_ENC_REG_IND            = 0x3200,
    ID_ENC_FRAME_INFO_IND     = 0x3300,
    ID_ENC_CONTEXT_IND        = 0x3400,

    /*VPP Config*/
    ID_VPP_CFG_REQ            = 0x4000,
    ID_VPP_CFG_CNF            = 0x4001,
    ID_VPP_EVENT_IND          = 0x4100,
    ID_VPP_REG_IND            = 0x4200,
    ID_VPP_FRAME_INFO_IND     = 0x4300,
    ID_VPP_CONTEXT_IND        = 0x4400,

    /*Camera Config*/
    ID_CAMERA_CFG_REQ         = 0x5000,
    ID_CAMERA_CFG_CNF         = 0x5001,
    ID_CAMERA_EVENT_IND       = 0x5100,
    ID_CAMERA_REG_IND         = 0x5200,
    ID_CAMERA_FRAME_INFO_IND  = 0x5300,
    ID_CAMERA_CONTEXT_IND     = 0x5400,

    ID_VIDEO_MSG_MAX
} mntn_video_prim_id_e;

typedef enum {
    ID_DISP_MSG_INVALID           = 0x0000,

    /*disp Edc Config*/
    ID_EDC_CFG_REQ            = 0x2000,   /*EDC模块消息配置请求*/
    ID_EDC_CFG_CNF            = 0x2001,   /*EDC模块消息配置确认*/
    ID_EDC_EVENT_IND          = 0x2100,   /*EDC模块事件上报*/
    ID_EDC_REG_IND            = 0x2200,   /*EDC模块寄存器上报*/
    ID_EDC_FRAME_INFO_IND     = 0x2300,   /*EDC模块帧信息上报*/
    ID_EDC_CONTEXT_IND        = 0x2400,   /*EDC模块上下文信息上报*/

    /* disp Gpu Config */
    ID_GPU_CFG_REQ            = 0x3000,   /*GPU模块消息配置请求*/
    ID_GPU_CFG_CNF            = 0x3001,   /*GPU模块消息配置确认*/
    ID_GPU_EVENT_IND          = 0x3100,   /*GPU模块事件上报*/
    ID_GPU_REG_IND            = 0x3200,   /*GPU模块寄存器上报*/
    ID_GPU_FRAME_INFO_IND     = 0x3300,   /*GPU模块帧信息上报*/
    ID_GPU_CONTEXT_IND        = 0x3400,   /*GPU模块上下文信息上报*/

    /* disp Hdmi Config */
    ID_HDMI_CFG_REQ           = 0x4000,   /*HDMI模块消息配置请求*/
    ID_HDMI_CFG_CNF           = 0x4001,   /*HDMI模块消息配置确认*/
    ID_HDMI_EVENT_IND         = 0x4100,   /*HDMI模块事件上报*/
    ID_HDMI_REG_IND           = 0x4200,   /*HDMI模块寄存器上报*/
    ID_HDMI_FRAME_INFO_IND    = 0x4300,   /*HDMI模块帧信息上报*/
    ID_HDMI_CONTEXT_IND       = 0x4400,   /*HDMI模块上下文信息上报*/

    ID_DISP_MSG_MAX
}mntn_disp_prim_id_e;

/******************************************************************************
  4 全局变量声明
******************************************************************************/


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
结构名    : om_api_func
结构说明  : OM提供给MNTN模块的API回调函数类型
*******************************************************************************/
typedef void (*om_api_func)(void);

/******************************************************************************
结构名    : om_req_packet
结构说明  : OM发送到mntn的消息的消息头，对应mntn_trace_req_t消息
*******************************************************************************/
typedef struct {
    unsigned char   func_type;             /* IT2's module ID */
    unsigned char   cpu_id;                /* reserved，不关注此值 */
    unsigned short  length;                /* msg length after 'length' domain */
    unsigned char   feedback[4];           /* message content */
}om_req_packet;

/******************************************************************************
结构名    : om_rsp_packet
结构说明  : mntn发送到OM的消息的消息头，对应mntn_trace_cnf_t或mntn_trace_ind_t消息
*******************************************************************************/
typedef struct {
    unsigned char   func_type;             /* IT2's module ID */
    unsigned char   cpu_id;                /* ACPU，必须填写1，对应ACPU */
    unsigned short  length;                /* msg length after 'length' domain */
    unsigned char   feedback[4];           /* message content */
}om_rsp_packet;

/******************************************************************************
结构名    : om_rsp_func
结构说明  : OM回调函数类型
*******************************************************************************/
typedef unsigned int (*om_rsp_func)(om_rsp_packet *rsp_packet, unsigned short length);

/******************************************************************************
结构名    : om_request_func
结构说明  : mntn回调函数类型
*******************************************************************************/
typedef void (*om_request_func)(om_req_packet *req_packet, om_rsp_func rsp_func);

/******************************************************************************
结构名    : om_reg_request_func
结构说明  : OM提供用于注册mntn回调函数的函数类型
*******************************************************************************/
typedef unsigned int (*om_reg_request_func)(unsigned char module_id, om_request_func om_request);

/******************************************************************************
结构名    : om_add_sn_time_func
结构说明  : OM提供的获取SN和timestamp的回调函数类型
*******************************************************************************/
typedef void (*om_add_sn_time_func)(unsigned int *sn, unsigned int *timestamp);


/******************************************************************************
  8 UNION定义
******************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/* 提供给OM的接口 */
void mntn_om_rcv_cfg_req(om_req_packet *req_packet, om_rsp_func rsq_func);
void mntn_om_close_trace(void);
void mntn_proc_reg(om_api_func_id_e func_id, om_api_func func_name);


#endif /* __MEDIA_MNTN_KERNEL_OM_INTERFACE_H__ */

