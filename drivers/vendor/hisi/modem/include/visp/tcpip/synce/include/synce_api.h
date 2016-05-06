/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              synce_api.h
*
*  Project Code: VISPV100R008C03
*   Module Name: synce
*  Date Created: 2009-12-16
*        Author: luogaowei(61496)
*   Description: SyncE模块API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-12-16  luogaowei(61496)     Create the first version.
*
*******************************************************************************/
#ifndef _SYNCE_API_H
#define _SYNCE_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE<SyncE错误码>*/
typedef enum enumSyncEErrCode
{
    SYNCE_OK = VOS_OK,                 /* 0  OK                                */
    SYNCE_ERR,                         /* 1  ERROR                             */
    SYNCE_ERR_PARA = MID_COMP_SYNCE + 2,                    /* 2 参数有效性错误                    */
    SYNCE_ERR_NO_REGISTER,          /*3 同步以太未注册*/    
    SYNCE_ERR_NULL_POINTER,            /* 4  指针参数错误                      */ 
    SYNCE_ERR_IF_NULL,                 /* 5  接口不存在                        */
    SYNCE_ERR_IF_INVALID,              /* 6  接口类型错误                      */
    SYNCE_ERR_MEMORY,                  /* 7  内存空间不足                      */
    SYNCE_ERR_ENABLED,                 /* 8  SYNCE已使能                         */
    SYNCE_ERR_DISABLED,                /* 9  SYNCE未使能                         */
    SYNCE_ERR_MBUF_PREPEND,            /* 10 MBUF指针前移错误 */
    SYNCE_ERR_CB_NOTEXIST,              /* 11 控制块不存在 */
    SYNCE_ERR_PORT_IS_VIRTUAL,         /* 12 接口非本板接口 */
    SYNCE_ERR_QL_INVALID,             /*13 错误的QL*/
    SYNCE_ERR_RCV_EXIST_ALREADY,    /*14  系统已经存在接收接口*/
    SYNCE_ERR_ITU_INVALID,          /*15 ITU字段非法*/
    SYNCE_ERR_ITU_SUBTYPE_INVALID,          /*16 ITU SUBTYPE字段非法*/
    SYNCE_ERR_VERSION_INVALID,          /*17 版本字段非法*/
    SYNCE_ERR_IF_IS_DOWN,          /*18 接口是DOWN状态*/
    SYNCE_ERR_RCV_FROM_LOCAL,          /*19收到本机发送的SSM报文*/
    SYNCE_ERR_MACADDR_NOT_MULTI,    /*20非多播报文*/
    SYNCE_ERR_INVALID_PKT_LEN,    /*21报文长度非法*/
    SYNCE_ERR_MALLOC_MEN_FAIL,    /*22分配内存失败*/
    SYNCE_ERR_MBUF_COPY_FAIL,    /*23MBUF拷贝失败*/
    SYNCE_ERR_GET_MAC_FAIL,    /*24获取physical地址失败*/
    SYNCE_ERR_UNSUPPORT_TLV_TYPE,  /*25 当前不支持该类型SSM TLV TYPE*/
    SYNCE_ERR_TLV_LENGTH_INVALID,  /*26 TLV Length域非法*/
    SYNCE_ERR_TLV_CODE_INVALID,  /*27 TLV CODE域非法*/
    SYNCE_ERR_MAXCODE                  /* SYNCE错误码最大值,以后添加错误码请按顺序添加到此前 */
}SYNCE_ERRCODE_E;


/*STRUCT<接口SyncE PDU报文统计>*/
typedef struct tagSyncEPduStat
{
    ULONG ulSndTotalPdu;                 /* 接口发送总的SSM报文        */
    ULONG ulSndDropPdu;                  /* 接口发送时总的丢弃SSM报文  */
    ULONG ulSndInfoPdu;                 /* 接口发送信息SSM报文        */
    ULONG ulSndEventPdu;                 /* 接口发送事件SSM报文        */
    
    ULONG ulRcvTotalPdu;                 /* 接口接收总的SSM报文        */
    ULONG ulRcvDropPdu;                  /* 接口接收总的丢弃SSM报文    */
    ULONG ulRcvInfoPdu;                  /* 接口接收信息SSM报文        */
    ULONG ulRcvEventPdu;                 /* 接口接收事件SSM报文        */
}SYNCE_PDUSTAT_S;

/* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
typedef struct tagSyncEPduStatList
{
    ULONG ulIfIndex;
    SYNCE_PDUSTAT_S stSynceStat;
}SYNCE_PDUSTAT_LIST_S;
/* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */

/*MACRO<SYNCE_Define> */
#define SYNCE_SEND_MODE          1  /*接口收发模式:发送*/
#define SYNCE_RECV_MODE          2  /*接口收发模式:接收*/

/*SYNCE调试开关标志*/
#define SYNCE_DBG_RCV_ERR_MASK          0X01      /*打开接收错误信息调试开关*/
#define SYNCE_DBG_SND_ERR_MASK          0X02      /*打开发送错误信息调试开关*/
#define SYNCE_DBG_RCV_MASK                  0X04     /*打开接收报文调试开关*/
#define SYNCE_DBG_SND_MASK                  0X08     /*打开发送报文调试开关*/
#define SYNCE_DBG_ALL                             0x0F     /* 所有调试开关 */

/*******************************************************************************
*    Func Name: TCPIP_EnableSyncMode
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: 指定以太端口使能同步模式
*  Description: 指定以太端口使能同步模式，并指定同步收发角色.
*        Input: ULONG ulIfIndex:以太接口索引
*               ULONG ulSyncRole:同步收发角色
*                       0:未指定，由选源决定；（目前不支持）
*                       1:接收端；2，发送端
*       Output: 
*       Return: 成功返回VOS_OK
*                  失败返回错误码
*      Caution: 处于同步以太模式下的接口才能够接收和发送ESMC报文。
*      同一个同步以太设备必须限制只能有一个接收接口。
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableSyncMode(ULONG ulIfIndex, ULONG ulSyncRole);

/*******************************************************************************
*    Func Name: TCPIP_DisableSyncMode
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: 指定以太端口去使能同步模式。
*  Description: 指定以太端口去使能同步模式。
*        Input: ULONG ulIfIndex:以太接口索引
*       Output: 
*       Return: 成功返回VOS_OK
*                  失败返回错误码
*      Caution: 处于同步以太模式下的接口才能够接收和发送ESMC报文。
*      去使能同步模式后，同步收发角色参数同时被清除。
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_DisableSyncMode(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_QuerySyncMode
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose: 指定以太端口查询同步模式使能情况
*  Description: 指定以太端口查询同步模式使能情况。
*        Input: ULONG ulIfIndex:接口索引
*       Output: ULONG *pulSyncMode:同步状态(接收或发送)
*       Return: 成功返回SYNCE_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_QuerySyncMode(ULONG ulIfIndex, ULONG *pulSyncMode);

/*******************************************************************************
*    Func Name: TCPIP_SetLocalQL
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: 设置本地QL值。
*  Description: 设置本地QL值。 
*        Input: USHORT usQLValue:QL值
*       Output: 
*       Return: 成功返回VOS_OK
*                  失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLocalQL(USHORT usQLValue);

/*******************************************************************************
*    Func Name: TCPIP_GetLocalQL
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: 获取本地QL值。 
*  Description: 获取本地QL值。 
*        Input: 
*       Output: USHORT *pusQLValue:QL值
*       Return: 成功返回VOS_OK
*                  失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLocalQL(USHORT* pusQLValue);

/*******************************************************************************
*    Func Name: TCPIP_SetSsmTlvLength
* Date Created: 2010-4-27
*       Author: t00110672
*  Description: 设置SSM帧TLV信息的Data and Padding长度
*        Input: ULONG ulSsmTlvLen;
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-4-27   t00110672         Create for BC3D03060
*
*******************************************************************************/
extern ULONG TCPIP_SetSsmTlvLength(ULONG ulSsmTlvLen);

/*******************************************************************************
*    Func Name: TCPIP_GetSsmTlvLength
* Date Created: 2010-4-27
*       Author: t00110672
*  Description: 获取SSM帧TLV信息的Data and Padding长度
*        Input: ULONG ulSsmTlvLen;
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-4-27   t00110672         Create for BC3D03060
*
*******************************************************************************/
extern ULONG TCPIP_GetSsmTlvLength(ULONG *pulSsmTlvLen);

typedef ULONG (*SYNCE_QL_NOTIFY_FUNC)(ULONG ulFlag, ULONG ulNewQL);
/*******************************************************************************
*    Func Name: TCPIP_Reg_Synce_QL_Notify_Hook
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description: 同步以太状态变化的通知注册函数
*        Input: pfHookFunc：产品注册的函数指针
*        typedef ULONG (*SYNCE_QL_NOTIFY_FUNC)(ULONG ulFlag, ULONG ulNewQL);
*        ulFlag: 1表示有效，0表示超时。
*        ulNewQL:表示接收的QL值.
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern  ULONG TCPIP_Reg_Synce_QL_Notify_Hook(SYNCE_QL_NOTIFY_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_Set_Synce_GlobalMode
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description: 指定以全局同步以太模式:同步模式或者非同步模式
*        Input: ulSyncMode:1表示同步模式，0 表示非同步模式.
*       Output: 
*       Return: 成功返回VOS_OK
*                 失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern ULONG TCPIP_Set_Synce_GlobalMode(USHORT usGlobalMode);

/*******************************************************************************
*    Func Name: TCPIP_Get_Synce_GlobalMode
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description: 获取当前同步以太的同步模式
*        Input:
*       Output: pulSyncMode
*       Return: 成功返回VOS_OK
*                 失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern ULONG TCPIP_Get_Synce_GlobalMode(USHORT *pusGlobalMode);

/*******************************************************************************
*    Func Name: TCPIP_Get_Synce_GlobalMode
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description:查询同步以太全局信息：当前同步模式
*        Input:
*       Output: 
*       Return: 成功返回VOS_OK
*                 失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern VOID TCPIP_Show_Synce_GlobalInfo(VOID);


/*******************************************************************************
*    Func Name: TCPIP_ShowSyncMode
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: 指定接口索引显示同步模式使能情况。
*  Description: 指定接口索引显示同步模式使能情况。
*           当输入ulIfIndex为0时，显示所有使能同步以太的接口。
*        Input: ULONG ulIfIndex:以太接口索引
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowSyncMode(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllSyncInterface
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: 显示所有使能同步以太的接口。
*  Description: 显示所有使能同步以太的接口。
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowAllSyncInterface(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowLocalQL
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose:  显示用户配置的本地QL值。
*  Description: 显示用户配置的本地QL值。
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowLocalQL(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_SetDbgSwitch
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose: 设置SyncE组件调试开关
*  Description: 设置SyncE组件调试开关
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulDebugSwitch:开关标志
*                            0x01:打印错误信息
*                            0x02:打印正常收发报文信息
*       Output: 
*       Return: 成功返回SYNCE_OK，失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_SetDbgSwitch(ULONG ulIfIndex, ULONG ulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_GetDbgSwitch
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose:获取当前SyncE组件调试开关信息
*  Description: 获取当前SyncE组件调试开关信息
*        Input: ULONG ulIfIndex:接口索引
*       Output: ULONG *pulDugInfo:当前开关状态
*       Return: 成功返回SYNCE_OK，失败返回错误码
*      Caution: : 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_GetDbgSwitch(ULONG ulIfIndex, ULONG *pulDugInfo);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_GetPacketStat
* Date Created: 2009-12-24
*      Purpose: 获取指定接口报文收发统计信息
*       Author: raofei62469
*  Description: 获取指定接口报文收发统计信息
*        Input: ULONG ulIfIndex:接口索引
*       Output: SYNCE_PDUSTAT_S * pstPduStat:报文统计信息
*       Return: 成功返回SYNCE_OK，失败返回错误码
*      Caution: : 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_GetPacketStat(ULONG ulIfIndex, SYNCE_PDUSTAT_S * pstPduStat);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_ClearPacketStat
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose: 清除指定接口报文收发统计信息
*  Description:清除指定接口报文收发统计信息
*        Input: ULONG ulIfIndex:接口索引
*       Output: 
*       Return: 成功返回SYNCE_OK，失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_ClearPacketStat(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_ShowPacketStat
* Date Created: 2009-12-30
*       Author: raofei62469
*      Purpose: 显示指定接口报文统计信息
*  Description: 显示指定接口报文统计信息
*        Input: CHAR *pszIfName:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-30   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_SyncE_ShowPacketStat(CHAR *pszIfName);

#ifdef  __cplusplus
}
#endif

#endif


