/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vrf_pub.h
*
* Project Code: VISPV100R007
*  Module Name: VRF  
* Date Created: 2009-01-20
*       Author: Qinyun
*  Description: VRF模块对外提供的宏定义、结构、函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-01-20   Qinyun                  Create
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _VRF_API_H_
#define _VRF_API_H_

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* 最大接口名长度 */
#endif

#define VRF_DEFAULT_ID        0
#define VRF_DEFAULT_NAME      ""

#define VRF_MAX_VRFNAME_LENGTH        31
#define VRF_MAX_IF_NAME_LENGTH        IF_MAX_INTERFACE_NAME_LEN

#define VRF_SET        1
#define VRF_DEL        0
#define VRF_MOVE       2/*内部使用，非对外API功能*/

#define VRF_CALLBACK_CREATE 0x1
#define VRF_CALLBACK_DELETE 0x02
#define VRF_CALLBACK_CHANGE 0x03

/*Added by limin00188004, 支持全局和VRF域的控制License, 2012/9/24   问题单号:S.VRF.02.01 */
#define VRF_LICENCE_DISABLE 0x00
#define VRF_LICENCE_ENABLE  0x01

typedef ULONG(*VRF_GET_LICENSE_STATE_FUNC)(ULONG ulVrfIndex, UCHAR *pucVrfSwitch);
/* End of Added by limin00188004, 2012/9/24   问题单号:S.VRF.02.01 */

typedef enum tagVRF_RM_PRO_TYPE_E
{
    VRF_RM_PRO_OSPF = 1,
    VRF_RM_PRO_RIP,
    VRF_RM_PRO_OSPFV3,
    VRF_RM_PRO_RIPNG,
    VRF_RM_PRO_MAX,
}VRF_RM_PRO_TYPE_E;
/* end for BC3D03298 at 2010-05-31*/

typedef enum tagVRF_ERR_E
{
    VRF_OK                    ,    /* 0  */
    VRF_ERR = MID_COMP_VRF + 1,    /* 1  */
    VRF_ERR_NOT_INIT          ,    /* 2  VRF未初始化 */
    VRF_ERR_ENTRY_NOT_CREATE  ,    /* 3  VRF实例未创建 */
    VRF_ERR_ENTRY_EXIST       ,    /* 4  VRF实例已存在 */
    VRF_ERR_FULL_CFG          ,    /* 5  VRF配置规格已满 */
    VRF_ERR_DEL_DEFAULT       ,    /* 6  不能删除默认的VRF实例 */
    VRF_ERR_PORT_TYPE         ,    /* 7  接口类型错误 */
    VRF_ERR_SUBPORT_TYPE      ,    /* 8  子接口类型错误 */
    VRF_ERR_ALREADY_BIND      ,    /* 9  接口已经绑定到VPN中 */
    VRF_ERR_UNBIND            ,    /* 10 接口未绑定到VPN中 */
    VRF_ERR_NULL              ,    /* 11 空指针 */
    VRF_ERR_CFG_CMD           ,    /* 12 配置命令字非法,1表示设置,0标识取消,其他非法 */
    VRF_ERR_MALLOC            ,    /* 13 内存申请失败 */
    VRF_ERR_INDEX             ,    /* 14 VRF Index不匹配 */
    VRF_ERR_GET_IFINDEX       ,    /* 15 根据接口名获取接口索引失败 */
    VRF_ERR_GET_VRFINDEX      ,    /* 16 根据vrf名获取vrf索引失败 */
    VRF_ERR_NODE_NOT_FINDE    ,    /* 17 未找到节点 */
    VRF_ERR_FILTER            ,    /* 18 查询VRF绑定关系的过滤参数非法 */
    VRF_ERR_AM4_MOD           ,    /* 19 AM4地址链表初始化或删除操作失败 */
    VRF_ERR_CFG_DCL_INST      ,    /* 20 DCL路由模式下，配置路由相关实例失败 */
    VRF_ERR_CFG_NAME          ,    /* 21 VRF名称异常 */
    VRF_ERR_DEL_RMPRO         ,    /* 22 删除路由信息失败*/
    VRF_ERR_DEL_INTF          ,    /* 23 删除接口信息失败*/
    VRF_ERR_RMPRO_EXIST       ,    /* 24 路由信息已存在*/
    VRF_ERR_RM_DCL            ,    /* 25 路由管理模式不是DCL*/
    VRF_ERR_I3_NOT_EXIST      ,    /* 26 I3信息不存在*/
    VRF_ERR_DEL_ARP           ,    /* 27 ETH模块，删除用户添加的指定vrf的静态arp表项 */
    VRF_ERR_DISABLE_IP_BORROW ,    /* 28 AM4模块，接口地址去借用失败*/
    VRF_ERR_DHCP4C_DISABLE    ,    /* 29 DHCP模块，去使能DHCP4C失败 */
    VRF_ERR_DCL_MIB_NOT_INIT  ,    /* 30 DCL模块未初始化*/
    VRF_ERR_INST_NOT_READY    ,    /* 31 VRF路由基础模块没有ready*/
    VRF_ERR_INST_TYPE         ,    /* 32 VRF路由基础模块实例类型出错*/
    VRF_ERR_BUFF_LENGTH       ,    /* 33 输入内存长度不够*/
    VRF_ERR_CALLBACK_NOT_EXIST,    /* 34 回调函数未注册*/
    VRF_ERR_CALLBACKPRO       ,    /* 35 调用回调函数失败*/
    VRF_ERR_EV_READ           ,    /* 36 读事件失败*/
    VRF_ERR_EV_WRITE          ,    /* 37 写事件出错*/
    VRF_ERR_EV_TYPE           ,    /* 38 事件类型出错*/
    VRF_ERR_MSG_TYPE          ,    /* 39 写向RM的消息类型出错*/
    VRF_ERR_NOTIFY_TO_RM      ,    /* 40 通知RM失败 */
    VRF_ERR_DCL_NOT_INIT      ,    /* 41 OSPF/RIP创建函数为空*/
    VRF_ERR_INST_AND_TYPE     ,    /* 42 输入的查询实例号和输入的查询类型不匹配*/
    VRF_ERR_RTM_INSTANCE      ,    /* 43 RTM实例号错误*/
    VRF_ERR_IF_NULL           ,    /* 44 接口为空*/  
    VRF_ERR_REG_WAITLIST      ,    /* 45 注册VRF WaitList失败 */  
    VRF_ERR_UNREG_WAITLIST    ,    /* 46 解注册VRF WaitList失败*/  
    VRF_ERR_FIX_INDEX_CREATE  ,    /* 47 指定vrf index已经创建 */  
    VRF_ERR_FIX_INDEX_MAX     ,    /* 48 指定vrf index非法,大于最大实例数 */ 
    VRF_ERR_FIX_INDEX_NAME_EXIT,   /* 49 指定vrf index创建实例,但是实例名已经存在 */ 
    VRF_ERR_RELAY_ENABLE      ,    /* 50 指定接口已经使能DHCP4R,使能DHCP4R不允许绑定和去绑定操作 */
    VRF_ERR_INDEX_ZERO        ,    /* 51 vrf index为默认值0*/
    VRF_ERR_INFO_NOT_CHANGED  ,    /* 52 API配置的信息无变化*/
    VRF_ERR_IPV6_MOD,
    VRF_ERR_WAITLIST          ,    /* 54 waitlist机制返回错误码*/    
    VRF_ERR_IPC_PORT          ,    /*55 VRF绑定的接口是IPC接口*/
    VRF_ERR_MAX    
}VRF_ERR_E;

/* for API: TCPIP_CfgVrfInstance */
typedef struct tagVRF_CFGINSTANCE_S
{
    ULONG ulOper;                               /*0 表示删除   1 创建 */
   ULONG ulVrfIndex ;  /*0 不指定Index  非0 指定Index*/
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]; /* VPN名字，要求名字唯一 */
}VRF_CFGINSTANCE_S;

/* for API: TCPIP_CfgIntfBindVrf */
typedef struct tagVRF_CFGINTFBIND_S
{
    ULONG ulOper; /*0 表示去绑定    1 绑定*/
    CHAR szIfName[VRF_MAX_IF_NAME_LENGTH + 1];/*接口名字*/
    CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN名字，要求名字唯一*/
}VRF_CFGINTFBIND_S;

/* for API: TCPIP_RegFuncVrfEventCallBack */
typedef struct tagVRF_CALLBACK_IF_CHANGE_S
{
    ULONG ulNewVrfId;
    ULONG ulOldVrfId;
    ULONG ulIfIndex;
}VRF_CALLBACK_IF_CHANGE_S;

typedef struct tagVRF_CALLBACK_VRF_OP_S
{
    ULONG ulVRFIndex;
}VRF_CALLBACK_VRF_OP_S;

typedef union tagVRF_CALLBACK_DATA_U
{
    VRF_CALLBACK_VRF_OP_S stVrfOp;
    VRF_CALLBACK_IF_CHANGE_S stIfChange;
}VRF_CALLBACK_DATA_U;

typedef  ULONG  (*VRF_CALLBACK_FUNC)( ULONG ulEvents , VOID *pData);

/* for API: TCPIP_OpenVrfBindInfo 过滤条件,两者只有一个可以为空字符串 */
typedef struct tagVRF_BIND_FILTER_S 
{  
    CHAR  szIfName[VRF_MAX_IF_NAME_LENGTH + 1];      /* 接口名字 */
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1];      /* VPN 名字 */
    ULONG ulIsAllVrf;      /* 是否查询所有VRF标记,1-查询所有VRF下的绑定信息,0-查询指定VRF信息 */
}VRF_BIND_FILTER_S;

/* for API: TCPIP_GetFirstVrfBindInfo & TCPIP_GetNextVrfBindInfo */
typedef struct tagVRF_BIND_INFO_S 
{  
    ULONG ulVrfIndex;                            /*Vrf序号*/   
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN 名字*/
    ULONG ulIfIndex;                            /*接口索引*/
    ULONG ulIfState;                            /*接口IP层的状态*/ 
}VRF_BIND_INFO_S;

/* for API: TCPIP_OpenVrfCfgInfo 过滤条件 */
typedef struct tagVRF_INFO_FILTER_S 
{  
    CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1];      /*VPN 名字,如果指定VRF则获取指定VRF的信息，否则获取所有VRF信息 */
    ULONG ulIsAllVrf;
} VRF_INFO_FILTER_S;

/* for API: TCPIP_GetFirstVrfCfgInfo & TCPIP_GetNextVrfCfgInfo */
typedef struct tagVRF_CFG_INFO_S 
{  
    ULONG ulVrfIndex;                              /*Vrf序号*/   
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1];   /*VPN 名字*/
} VRF_CFG_INFO_S;

/*******************************************************************************
*    Func Name: TCPIP_CfgVrfInstance
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: 增加/删除VRF实例
*        Input: VRF_CFGINSTANCE_S *pstVrfIn: VRF实例配置信息
*       Output: 
*       Return: VOS_OK,VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgVrfInstance(VRF_CFGINSTANCE_S *pstVrfIn);
/*******************************************************************************
*    Func Name: TCPIP_CfgIntfBindVrf
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: 接口与VPN绑定/去绑定
*        Input: VRF_CFGINTFBIND_S *pstVrfIn: VRF实例配置信息
*       Output: 
*       Return: VOS_OK,VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgIntfBindVrf(VRF_CFGINTFBIND_S * pstVrfIn);
/*******************************************************************************
*    Func Name: TCPIP_GetVrfIndexByName
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: 根据VRF实例名称获取VRF ID
*        Input: CHAR *pszVrfName: VRF实例名称
*       Output: ULONG *pulVrfIndex: VRF ID
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfIndexByName (CHAR *pszVrfName, ULONG *pulVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetVrfNameByIndex
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: 根据VRF ID获取VRF实例名称
*        Input: ULONG ulVrfIndex: VRF ID
*       Output: CHAR *pszVrfName: VRF实例名称
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfNameByIndex(CHAR *szVrfName, ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncVrfEventCallBack
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: 注册VRF配置回调函数
*        Input: ULONG ulModId: 模块ID
*               ULONG ulEventsToReceive: 上报消息类型
*                                        VRF_CALLBACK_CREATE
*                                        VRF_CALLBACK_DELETE
*                                        VRF_CALLBACK_CHANGE
*               VRF_CALLBACK_FUNC pfVrfNotify: 回调函数
*       Output: 
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncVrfEventCallBack (ULONG ulModId, ULONG ulEventsToReceive,
                                                VRF_CALLBACK_FUNC pfVrfNotify);
/*******************************************************************************
*    Func Name: TCPIP_VrfDelSuccessNotify
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: VRF实例删除成功通知
*        Input: ULONG ulModId: 模块ID
*               ULONG ulVrfIndex: VRF ID
*       Output: 
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_VrfDelSuccessNotify(ULONG ulModId, ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_OpenVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 打开VRF绑定信息句柄
*        Input: VRF_BIND_FILTER_S * pstFilter: 过滤条件
*       Output: ULONG *pulSessionId: 句柄
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenVrfBindInfo (UINTPTR *pulSessionId,VRF_BIND_FILTER_S * pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetFirstVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 获取第一个VRF绑定信息
*        Input: ULONG ulSessionId: 句柄
*       Output: VRF_BIND_INFO_S *pstConfigInfo: 绑定信息
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFirstVrfBindInfo(UINTPTR ulSessionId, VRF_BIND_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetNextVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 获取下一个VRF绑定信息
*        Input: ULONG ulSessionId: 句柄
*       Output: VRF_BIND_INFO_S *pstConfigInfo: 绑定信息
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNextVrfBindInfo(UINTPTR ulSessionId, VRF_BIND_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_CloseVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 关闭获取VRF绑定信息的句柄
*        Input: ULONG ulSessionId: 句柄
*       Output: 
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseVrfBindInfo (UINTPTR ulSessionId);
/*******************************************************************************
*    Func Name: TCPIP_ShowVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 显示VRF绑定信息
*        Input: CHAR *pszVrfName: VRF名称
*       Output: 
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVrfBindInfo (CHAR *pszVrfName, CHAR *pszIfName, ULONG ulIsAllVrf);
/*******************************************************************************
*    Func Name: TCPIP_OpenVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 打开VRF配置信息句柄
*        Input: VRF_INFO_FILTER_S * pstFilter: 过滤条件
*       Output: ULONG *pulSessionId: 句柄
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenVrfCfgInfo (UINTPTR *pulSessionId, VRF_INFO_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetFirstVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 获取第一个VRF配置信息
*        Input: ULONG ulSessionId: 句柄
*       Output: VRF_BIND_INFO_S *pstConfigInfo: 绑定信息
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetFirstVrfCfgInfo(UINTPTR ulSessionId, VRF_CFG_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetNextVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 获取下一个VRF配置信息
*        Input: ULONG ulSessionId: 句柄
*       Output: VRF_BIND_INFO_S *pstConfigInfo: 绑定信息
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNextVrfCfgInfo(UINTPTR ulSessionId, VRF_CFG_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_CloseVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 关闭获取VRF配置信息的句柄
*        Input: ULONG ulSessionId: 句柄
*       Output: 
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG  TCPIP_CloseVrfCfgInfo (UINTPTR ulSessionId);
/*******************************************************************************
*    Func Name: TCPIP_ShowVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: 显示VRF配置信息
*        Input: CHAR *pszVrfName: VRF名称
*       Output: 
*       Return: VRF_OK,错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVrfCfgInfo(CHAR *pszVrfName, ULONG ulIsAllVrf);

/*******************************************************************************
*    Func Name: TCPIP_VRF_SetHaDbg
* Date Created: 2009-10-27
*       Author: zhangchunyu(62474)
*  Description: 设置HA调试开关
*        Input: ULONG ulDbg: 开关 1打开 0关闭
*       Output: 
*       Return: 成功:VRF_OK
*               其它:失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-27    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern  ULONG TCPIP_VRF_SetHaDbg(ULONG ulDbg);

/*******************************************************************************
*    Func Name: TCPIP_VRF_GetHaDbg
* Date Created: 2009-10-27
*       Author: zhangchunyu(62474)
*  Description: 获取VRF HA调试开关
*        Input: ULONG *pulDbg: 输出参数,获取开关值
*       Output: 
*       Return: 成功:VRF_OK
*               其它:失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-27    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_VRF_GetHaDbg(ULONG *pulDbg);

/*******************************************************************************/
/*******************************************************************************
*    Func Name: TCPIP_GetVrfIndexByRmPro
* Date Created: 2010-05-31
*       Author: xujun57575
*  Description: 根据路由协议的进程号获取VRF索引
*        Input: ULONG ulRtType: 路由协议类型 可以为OSPF或者RIP
*               ULONG ulInstance:路由协议进程ID
*               ULONG *pulVrfIndex:返回VRF索引号
*       Output: VRF索引
*       Return: 返回码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-31   xujun57575              Create for BC3D03298
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfIndexByRmPro(ULONG ulRtType,ULONG ulInstance,ULONG *pulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_EnableVrfLicence
* Date Created: 2012-09-25
*       Author: limin00188004
*  Description: 使能/去使能VRF的License特性
*        Input: UCHAR ucOper: 0,vrf licence特性关闭; 1,vrf licence特性打开
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-25   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableVrfLicence(UCHAR ucOper);

/*******************************************************************************
*    Func Name: TCPIP_GetVrfLicenceSwitch
* Date Created: 2012-09-27
*       Author: limin00188004
*  Description: 获取VRF License特性是否使能的开关
*        Input: UCHAR *pucOper:传出参数
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-27   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfLicenceSwitch(UCHAR *pucOper);

/*******************************************************************************
*    Func Name: TCPIP_CfgLicenceByVrf
* Date Created: 2012-09-25
*       Author: limin00188004
*  Description: 配置指定VRF域的License开关
*        Input: CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]: vrf名称
*               UCHAR ucOper: 0, licence关闭; 1, licence打开
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-25   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgLicenceByVrf(CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1], UCHAR ucOper);

/*******************************************************************************
*    Func Name: TCPIP_GetLicenceByVrf
* Date Created: 2012-09-27
*       Author: limin00188004
*  Description: 通过VRF名称，获取指定VRF的licence
*        Input: CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]:VRF名称
*               UCHAR *pucOper:传出参数，vrf的licence
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-27   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLicenceByVrf(CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1], UCHAR *pucOper);

/*******************************************************************************
*    Func Name: TCPIP_ShowVrfLicenceSwitch
* Date Created: 2012-09-27
*       Author: limin00188004
*  Description: 显示VRF licence使能信息,以及VRF licence为开启状态的所有VRF
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-27   limin00188004           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVrfLicenceSwitch(VOID);

#endif  /* _VRF_API_H_  */

#ifdef  __cplusplus
}
#endif
