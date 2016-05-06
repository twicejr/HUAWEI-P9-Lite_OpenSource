

#ifndef __RNICCONFIGINTERFACE_H__
#define __RNICCONFIGINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define RNIC_MODEM_TYPE_IS_VALID(enModemType)\
    (((enModemType) == RNIC_MODEM_TYPE_INSIDE)\
  || ((enModemType) == RNIC_MODEM_TYPE_OUTSIDE))

#define RNIC_RMNET_STATUS_IS_VALID(enRmnetStatus)\
    (((enRmnetStatus) == RNIC_RMNET_STATUS_UP) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_DOWN) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_SWITCH))

#define RNIC_IP_TYPE_IS_VALID(enIpType)\
    (((enIpType) == RNIC_IP_TYPE_IPV4) \
  || ((enIpType) == RNIC_IP_TYPE_IPV6) \
  || ((enIpType) == RNIC_IP_TYPE_IPV4V6))


/*****************************************************************************
   3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : RNIC_MODEM_TYPE_ENUM_UINT8
 结构说明  : RNIC模块对接MODEM的类型枚举
 1.日    期   : 2014年01月27日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
enum RNIC_MODEM_TYPE_ENUM
{
    RNIC_MODEM_TYPE_INSIDE,                                                     /* 内部modem */
    RNIC_MODEM_TYPE_OUTSIDE,                                                    /* 外部modem */

    RNIC_MODEM_TYPE_BUTT
};

typedef unsigned char RNIC_MODEM_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : RNIC_RMNET_STATUS_ENUM_UINT8
 结构说明  : RNIC网卡的状态设置类型枚举
 1.日    期   : 2014年01月27日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
enum RNIC_RMNET_STATUS_ENUM
{
    RNIC_RMNET_STATUS_UP,                                                       /* PDP激活，设置网卡up状态 */
    RNIC_RMNET_STATUS_DOWN,                                                     /* PDP去激活，设置网卡down状态 */
    RNIC_RMNET_STATUS_SWITCH,                                                   /* 内外modem PDP状态切换，设置网卡switch状态 */

    RNIC_RMNET_STATUS_BUTT
};

typedef unsigned char RNIC_RMNET_STATUS_ENUM_UINT8;

/*****************************************************************************
 结构名    : RNIC_IP_TYPE_ENUM_UINT8
 结构说明  : RNIC网卡的状态设置的IP类型枚举
            ipv4v6类型激活成功时，要分别下发ipv4和ipv6 config请求，请求中携带的
            ip类型分别为ipv4和ipv6。
            ipv4v6类型去激活时，只下发一次config请求，请求中携带的ip类型为ipv4v6
 1.日    期   : 2014年01月27日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
enum RNIC_IP_TYPE_ENUM
{
    RNIC_IP_TYPE_IPV4                   = 0x01,
    RNIC_IP_TYPE_IPV6                   = 0x02,
    RNIC_IP_TYPE_IPV4V6                 = 0x03,

    RNIC_IP_TYPE_BUTT                   = 0xFF
};

typedef unsigned char RNIC_IP_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名    : RNIC_RMNET_CONFIG_STRU
 结构说明  : 外部模块调用RNIC_ConfigRmnetStatus接口配置RNIC，所传参数结构
 1.日    期   : 2014年01月21日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    RNIC_MODEM_TYPE_ENUM_UINT8          enModemType;
    unsigned char                       ucRmNetId;
    unsigned short                      usModemId;
    unsigned char                       ucPdnId;
    unsigned char                       ucRabId;
    RNIC_RMNET_STATUS_ENUM_UINT8        enRmnetStatus;
    RNIC_IP_TYPE_ENUM_UINT8             enIpType;
}RNIC_RMNET_CONFIG_STRU;

/*****************************************************************************
   10 函数声明
*****************************************************************************/

/* RNIC网卡状态设置函数，供外部模块调用 */
unsigned long RNIC_ConfigRmnetStatus(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
);

/*****************************************************************************
 函 数 名  : RNIC_StartFlowCtrl
 功能描述  : 启动上行流控
 输入参数  : ucRmNetId : 网卡ID
 输出参数  : 无
 返 回 值  : VOS_OK     - 启动流控成功
             VOS_ERR    - 启动流控失败
 调用函数  :
 被调函数  :
*****************************************************************************/
unsigned int RNIC_StartFlowCtrl(unsigned char ucRmNetId);


/*****************************************************************************
 函 数 名  : RNIC_StopFlowCtrl
 功能描述  : 停止上行流控
 输入参数  : ucRmNetId : 网卡ID
 输出参数  : 无
 返 回 值  : VOS_OK     - 停止流控成功
             VOS_ERR    - 停止流控失败
 调用函数  :
 被调函数  :
*****************************************************************************/
unsigned int RNIC_StopFlowCtrl(unsigned char ucRmNetId);


#pragma pack(0)


#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif

#endif /* end of RnicConfigInterface.h */
