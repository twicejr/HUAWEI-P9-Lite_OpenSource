
#ifndef  TAF_CLIENT_API_H
#define  TAF_CLIENT_API_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafTypeDef.h"
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/
typedef VOS_UINT8 MN_CALLBACK_TYPE_T;   /* Type of callback functions for event reporting*/
#define MN_CALLBACK_CS_CALL             0 /* CS call */
#define MN_CALLBACK_PS_CALL             1 /* PS call */
#define MN_CALLBACK_MSG                 2 /* Short message service */
#define MN_CALLBACK_SS                  3 /* Call independent supplemental service */
#define MN_CALLBACK_PHONE               4 /* Phone management and network register service */
#define MN_CALLBACK_DATA_IND            5 /* User plane data indication */
#define MN_CALLBACK_DATA_STATUS         6 /* User plane data status */
#define MN_CALLBACK_DATA_FLOW           7 /* User plane data flow */
#define MN_CALLBACK_SET                 8
#define MN_CALLBACK_QRY                 9
#define MN_CALLBACK_PHONE_BOOK          10 /* Phone book */
#define MN_CALLBACK_STK                 11
#define MN_CALLBACK_CMD_CNF             12 /* Cmd Cnf*/
#define MN_CALLBACK_CHANNEL_STATUS      13
#define MN_CALLBACK_PIH                 14
#define MN_CALLBACK_VOICE_CONTROL       15
#define MN_CALLBACK_LOG_PRINT           16
#define MN_CALLBACK_MAX                 17



#define  TAF_MAX_CLIENT_OF_ONE_PROC       OMA_CLIENT_ID_BUTT

#define TAF_FREE                        0   /*未使用*/
#define TAF_USED                        1   /*使用*/



/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
#define TAF_CALL_APP_MSG_BASE           (0x0000)                                /* AT与CALL模块间消息起始 */
#define TAF_MSG_APP_MSG_BASE            (0x1000)                                /* AT与MSG模块间消息起始 */
#define TAF_SSA_APP_MSG_BASE            (0x2000)                                /* AT与SSA模块间消息起始 */
#define TAF_MMA_APP_MSG_BASE            (0x3000)                                /* AT与MMA模块间消息起始 */
#define TAF_APP_SET_MSG_BASE            (0x5000)                                /* AT与MN模块间设置消息起始 */
#define TAF_APP_QRY_MSG_BASE            (0x6000)                                /* AT与MN模块间查询消息起始 */
#define TAF_APS_MSG_BASE                (0x7000)                                /* AT/IMSA与PS适配模块间消息起始 */
#define TAF_SPM_IMSA_MSG_BASE           (0x8000)                                /* IMSA与SPM模块间消息起始 */
#define TAF_MSG_IMSA_MSG_BASE           (0x9000)                                /* IMSA与MSG模块间消息起始 */
#define TAF_MMA_IMSA_MSG_BASE           (0xa000)                                /* IMSA与MMA模块间消息起始 */
#define TAF_CALL_IMSA_MSG_BASE          (0xb000)                                /* CALL与IMSA公共消息起始 */
#define TAF_IMSA_COMM_MSG_BASE          (0xc000)                                /* TAF与IMSA公共消息起始 */

#define TAF_IMSA_MSG_MASK               (0xf000)                                /* IMSA与TAF间的MASK */
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*****************************************************************************
 结构名    : TAF_APP_CTRL_STRU
 结构说明  : APP控制结构体

 修改历史      :
  1.日    期   : 2015年11月6日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* 填入PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}TAF_APP_CTRL_STRU;

/*****************************************************************************
 结构名    : TAF_APP_MSG_HEADER_STRU
 结构说明  : 应用头消息控制结构体

 修改历史      :
  1.日    期   : 2015年11月6日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgName;
    TAF_APP_CTRL_STRU                                       stCtrl;
}TAF_APP_MSG_HEADER_STRU;





/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* TAF_CLIENT_API_H */


