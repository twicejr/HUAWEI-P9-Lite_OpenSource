/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_api.h
*
*  Project Code: VISPV1R6
*   Module Name:
*  Date Created: 2008-3-10
*        Author: LY(57500)
*   Description: bfd随visp发布时对外提供的接口声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2008-3-10  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _BFD_API_H_
#define _BFD_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 随visp发布时除了bfd_cbb_api.h里提供的接口外还另外定义了用户接口,参考下面的声明 */
#include "bfd_cbb_api.h"

#define BFD_LICENSE_ON   0x01
#define BFD_LICENSE_OFF  0x00

/* Begin:Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加创建BFD的协议类型宏 */   
#define BFD_PROTO_DRAFT4    0     /*草案4协议的BFD*/
#define BFD_PROTO_STD       1     /*RFC协议的BFD*/
/* End:Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加创建BFD的协议类型宏  */ 


/* PPI统计信息 */
typedef struct tagBFD_PPI_COUNT_S
{
    /* BFD4更新通知总次数 */
    ULONG ulBFDUpdateTotal;
    /* BFD4更新通知失败次数 */
    ULONG ulBFDUpdateFailure;
    /* BFD6更新通知总次数 */
    ULONG ulBFD6UpdateTotal;
    /* BFD6更新通知失败次数 */
    ULONG ulBFD6UpdateFailure;
}BFD_PPI_COUNT_S;

/* BFD会话操作字 */
typedef enum tagBFD_API_ACTION_TYPE_E
{
    BFD_API_SESSION_DELETE = 0 ,         /* 删除会话 */
    BFD_API_SESSION_ADD ,                /* 创建会话*/
    BFD_API_ACTION_MAX
}BFD_API_ACTION_TYPE_E;

typedef struct tagBFD_SESSION_ADD_DEL_S {
    ULONG ulAction;
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr;
    ULONG ulPeerAddr;
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulBfdProtocol;         /*会话类型   BFD_PROTO_DRAFT4    0  草案4协议的BFD
                                             BFD_PROTO_STD       1  RFC协议的BFD*/
    ULONG ulRemoteDiscr;
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 置为BFD_ON会生效，其他默认不生效 */
    ULONG ulMultiHopFlag;       /* 如果置上该标记，则在多跳下也是用3784，否则默认4784 */
}BFD_SESSION_ADD_DEL_S;

typedef struct tagBFD6_SESSION_ADD_DEL_S {
    ULONG ulAction;
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4];
    ULONG ulPeerAddr[4];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */    
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加创建BFD会话的协议类型字段 */   
    ULONG ulBfdProtocol;
    ULONG ulRemoteDiscr;/*对端描述符*/                     
    
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 置为BFD_ON会生效，其他默认不生效 */
    ULONG ulMultiHopFlag;       /* 如果置上该标记，则在多跳下也是用3784，否则默认4784 */
}BFD6_SESSION_ADD_DEL_S;

/* BFD会话用户管理数据结构 */
typedef struct tagBFD_SESSION_ADMIN_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    BOOL_T bShutdown;
    UCHAR ucResv[2];
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
}BFD_SESSION_ADMIN_S;

/* BFD会话更新数据结构 */
typedef struct tagBFD_SESSION_UPDATE_S {
    ULONG ulAction;
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
}BFD_SESSION_UPDATE_S;

/* 根据会话名称获取会话索引 或 根据会话索引获取会话名称 */
typedef struct tagBFD_SESSION_GET_ID_OR_NAME_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulSessionId;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
}BFD_SESSION_GET_ID_OR_NAME_S;

/* 会话信息，其中的参数stSessPara中的值如果设置为0则使用VISP
的默认值作为会话的参数；TOS值属于值域有效的参数，VISP不做有效性判断，直接赋值 */
typedef struct tagBFD_SESSION_CREATE_WITH_PARA_S {
    ULONG ulOutIfIndex;             /* 单跳会话时为出接口索引，多跳时值为0；*/
    ULONG ulSrcIP;                  /* 指定会话的源地址；主机序；*/
    ULONG ulDstIP;                  /* 指定会话的目的地址；主机序；*/
    ULONG ulBfdProtocol;            /* 会话协议类型
                                        0  BFD_PROTO_DRAFT4   草案4协议的BFD
                                        1  BFD_PROTO_STD      RFC协议的BFD*/
    ULONG ulVrfIndex;               /* VRF Index；*/
    BFD_SESSION_PARA_S stSessPara;  /* 会话参数 */
    UCHAR ucTos;                    /* BFD会话报文TOS值，值域有效 */ 
    UCHAR ucRes[3];
}BFD_SESSION_CREATE_WITH_PARA_S;

/*BFD时延注册钩子相关宏定义,add by wuhailan,2008-04-11.*/
#define BFD_TIMETEST_INPUT     0x01   /*BFD报文探测通道时延打点注册接收类型*/
#define BFD_TIMETEST_OUTPUT    0x02   /*BFD报文探测通道时延打点注册发送类型*/
typedef ULONG (*pfFuncBFDTimeTestHook)(MBUF_S* pMbuf);

/* api declare - the below functoins is only for visp user */
/****************************************************************************
*    Func Name: BFD_SetPpiDebugSwitch
*  Description: 设置BFD Debug的开关
*        Input: ulSwitch Debug开关，0为关闭，1为打开
*       Output: 
*       Return: 失败 BFD_ERR_INVALID_PARAMETER
*               成功 BFD_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-11   Wangchengyang    Create
*  2008-04-10   wuhailan         调整为调试开关
*******************************************************************************/
extern ULONG BFD_SetPpiDebugSwitch(ULONG ulSwitch);
/*******************************************************************************
*    Func Name: BFD_PPI_Count_Get
*  Description: 获取PPI统计计数
*        Input: BFD_PPI_COUNT_S *pstCount: 获取的PPI统计计数结构
*       Output:
*       Return: 失败 BFD_ERR_NULL_POINTER
*               成功 BFD_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-4-8    LY(57500)        Create the first version.
*
*******************************************************************************/
extern ULONG BFD_PPI_Count_Get(BFD_PPI_COUNT_S *pstCount);
/****************************************************************************
*    Func Name: BFD_PPI_Count_Reset
*  Description: 清零PPI统计计数
*        Input: VOID
*       Output: 
*       Return: 失败 BFD_ERR
*               成功 BFD_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-11  Wangchengyang    Create
*
*******************************************************************************/
extern ULONG BFD_PPI_Count_Reset(VOID);
/*******************************************************************************
*    Func Name: BFD_ComputeBFDPPIUpdateCost
*  Description: 使能计算BFD PPI下发时延开关
*        Input: ULONG ulSetYes:使能开关:1使能,0去使能
*       Output: 无
*       Return: 成功BFD_OK,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG BFD_ComputeBFDPPIUpdateCost(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: BFD_ShowBFDPPIUpdateCost
*  Description: 显示BFD PPI下发耗时信息
*        Input: 无
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern VOID BFD_ShowBFDPPIUpdateCost(VOID);

/*******************************************************************************
*    Func Name: BFD_HA_SetDbg
*  Description: 设置调试开关的接口函数
*        Input: ULONG ulDbg:           设置的调试开关值
*       Output: 无
*       Return: BFD_OK         成功
                BFD_ERR        设置失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME              DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-12    j51916             Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_HA_SetDbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: BFD_HA_GetDbg
*  Description: 获得调试开关值的接口函数
*        Input: ULONG *pulDbg          需要设置值的指针
*       Output: ULONG *pulDbg          已经设了值的指针
*       Return: BFD_OK         成功
                BFD_ERR        获得失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME              DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-12    j51916             Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_HA_GetDbg(ULONG *pulDbg);

/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreate
*  Description: 设定一个BFD会话的基本参数，并开始建立会话
*               （主要检查参数有效性，调用CBB实现功能）
*        Input: ULONG ulDstIP      指定会话的目的地址；主机序；
*               ULONG ulSrcIP      指定会话的源地址；主机序；
*               ULONG ulOutIfIndex   单跳会话时为出接口索引，多跳时值为0；
*               ULONG *pulSessionID  取值范围为[0,512]，如果是0则由VISP自动分配会话ID，
*                                    否则根据指定的ID创建会话
*       Output: ULONG *pulSessionID  会话的标识ID
*       Return: 成功返回      BFD_OK
*               失败返回      BFD_ERR_EXIST_SESSION
*                             BFD_ERR_NULL_POINTER
*                             BFD_ERR_DISABLE
*                             BFD_ERR_INVALID_ADDR;
*                             BFD_ERR_INTF_NOT_EXIST
*                             BFD_ERR_DISMATCH_IP_INDEX
*                             BFD_ERR_SRC_DST_IP_CONFLICT
*                             BFD_ERR_RECR_SESSION
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang    Create
*  2007-5-17  wujie(61195)         Modified for A82D15480，入参地址变为主机序
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreate (ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex, ULONG* pulSessionID);

/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreateByVrf
* Date Created: 2009-12-2
*       Author: zhangchunyu(62474)
*  Description: 设定一个BFD会话的基本参数，并开始建立会话
*               （主要检查参数有效性，调用CBB实现功能）
*        Input: ULONG ulDstIP      指定会话的目的地址；主机序；
*               ULONG ulSrcIP      指定会话的源地址；主机序；
*               ULONG ulOutIfIndex   单跳会话时为出接口索引，多跳时值为0；
*               ULONG *pulSessionID  取值范围为[0,2000],如果是0则由VISP自动分配会话ID，
*                                    否则根据指定的ID创建会话
*               ULONG ulVrfIndex   VRF Index
*       Output: ULONG *pulSessionID  会话的标识ID
*       Return: 成功返回      BFD_OK
*               其他错误码    失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-2    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreateByVrf(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex,
                                          ULONG *pulSessionID, ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_AddDelSession
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: 创建删除一个BFD会话，创建时同时设定会话参数
*        Input: pstSession  创建删除的会话信息
*       Output: 
*       Return: 成功返回       BFD_OK       失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_AddDelSession(BFD_SESSION_ADD_DEL_S *pstSession);
/*******************************************************************************
*    Func Name: BFD_AdminSession
* Date Created: 2008-7-29
*       Author: qinyun
*  Description: 会话的用户管理，Admindown，undo Admindown
*        Input: pstData  管理结构体
*       Output: 
*       Return: 成功返回       BFD_OK         失败返回       错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_AdminSession(BFD_SESSION_ADMIN_S *pstData);
/*******************************************************************************
*    Func Name: BFD_UpdateSession
* Date Created: 2008-7-29
*       Author: qinyun
*  Description: 会话参数更新
*        Input: pstPara  会话参数
*       Output: 
*       Return: 成功返回       BFD_OK        失败返回       错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_UpdateSession(BFD_SESSION_UPDATE_S *pstPara);
/*******************************************************************************
*    Func Name: BFD_GetSessionConfigEntry
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstConfigInfo:获取到的数据
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionConfigEntry(UINTPTR ulEntryWaitList,BFD_SESSION_CONFIG_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionCountEntry
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstCount:获取到的数据
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionCountEntry(UINTPTR ulEntryWaitList,BFD_SESSION_COUNT_S *pstCount);
/*******************************************************************************
*    Func Name: BFD_GetSessionInfoEntry
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstSessionInfo:获取到的数据
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionInfoEntry(UINTPTR ulEntryWaitList,BFD_SESSION_ALL_INFO_S *pstSessionInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionBriefEntry
* Date Created: 2008-12-8
*       Author: qinyun(62011)
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstBriefInfo:获取到的数据
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-8    qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetSessionBriefEntry(UINTPTR ulEntryWaitList,BFD_SESSION_BRIEF_INFO_S *pstBriefInfo);
/*******************************************************************************
*    Func Name: BFD_OpenSessionTable
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: 获取BFD会话表的WaitList句柄，并保存过滤条件
*        Input: pstFilter:过滤器结构
*       Output: ULONG *pulWaitListHandle: WaitList句柄
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_OpenSessionTable(UINTPTR *pulWaitListHandle,BFD_SESSION_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: BFD_CloseSessionTable
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: 关闭BFD会话表的WaitList句柄
*        Input: ULONG ulWaitListHandle: WaitList句柄
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)           Creat the first version.
*******************************************************************************/
extern ULONG BFD_CloseSessionTable(UINTPTR ulWaitListHandle);
/*******************************************************************************
*    Func Name: BFD_ClrSessionCount
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: 根据过滤条件清除BFD会话的统计信息
*        Input: ucSpecSessFlag  操作字(TRUE-使用指定会话清空,FALSE-全部清空)
*               ulLocalDiscr  过滤条件
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_ClrSessionCount(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr);
/*******************************************************************************
*    Func Name: BFD_GetSessionIdByName
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: 根据会话名称获取会话索引
*        Input: pulSessionId: 会话索引
*       Output: pszSessName: 会话名称
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetSessionIdByName(UCHAR *pszSessName,ULONG *pulSessionId);
/*******************************************************************************
*    Func Name: BFD_GetSessionIdByName
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: 根据会话索引获取会话名称
*        Input: ulSessionId: 会话索引
*               ulLength：用户输入的内存长度
*       Output: pszSessName: 会话名称
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetNameBySessionId(ULONG ulSessionId,UCHAR *pszSessName,ULONG ulLength);

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
/*******************************************************************************
*    Func Name: BFD_SessionCreateDelByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 删除指定会话
*        Input: BFD_CREATEDEL_BYVRF_S *pstBfdInfo: BFD创建删除控制块指针
*               ULONG* pulSessionID               : 创建会话的时候该值为创建指定的会话或者返回的会话值
*                                                   删除的时候为指定的BFD会话
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionCreateDelByVrf(BFD_CREATEDEL_BYVRF_S *pstBfdInfo,ULONG* pulSessionID);

/*******************************************************************************
*    Func Name: BFD_DeleteSingleAppFromSessionByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 删除指定会话的单个应用
*        Input: ulSessionID 会话标识ID；取值范围为1～255
*               ulAppID     应用ID      取值:2的N次幂,一个bit位表示一个应用
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-19      Wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_DeleteSingleAppFromSessionByVrf(ULONG ulSessionID, ULONG ulAppID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SessionParaUpdateByVrf
* Date Created: 2009-02-19
*       Author: Wangchengyang
*  Description: 更新一个会话的参数，包括：MTI、MRI、Detect Mult、Detect Mode，
*               并立即将更新后的参数应用到会话中。
*        Input: ULONG ulSessionID 会话标识ID；取值范围为1～255
*               BFD_SESSION_PARA_S *pSessPara 更新参数结构指针
*
*       Output: 
*       Return: 成功返回    BFD_OK
*               失败返回    BFD_ERR_SESSION_ID；      会话ID非法
*                           BFD_ERR_TX_INTERVAL;      发送时间间隔非法
*                           BFD_ERR_RX_INTERVAL;      接收时间间隔非法
*                           BFD_ERR_DETECT_MULT;      检测倍数非法
*                           BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                           BFD_ERR_DETECT_MODE       检测模式非法
*                           BFD_ERR_NULL_POINTER      参数指针为空；
*                           BFD_ERR_DISABLE           BFD未使能
*                           BFD_ERR_HA_IS_SMOOTHING
*                           BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-19      Wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SessionParaUpdateByVrf(ULONG ulSessionID, BFD_SESSION_PARA_S *pSessPara,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SessionAdministerByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 会话的用户管理，Admindown，undo Admindown
*        Input: ULONG  ulSessionID 指定会话的标识ID；取值范围为1～255
*               BOOL_T bShutdown   TRUE－关闭会话；FALSE－打开会话
*
*       Output: 
*       Return: 成功返回   BFD_OK
*               失败返回   BFD_ERR_SESSION_ID；      会话ID非法
*                          BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                          BFD_ERR_INVALID_PARAMETER
*                          BFD_ERR_DISABLE
*                          BFD_ERR_HA_IS_SMOOTHING
*                          BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-19      Wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SessionAdministerByVrf(ULONG ulSessionID, BOOL_T bShutdown,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_GetSessionInfoByVrf
* Date Created: 2009-02-01
*       Author: Wangchengyang
*  Description: 获取指定会话的当前信息
*        Input: ULONG  ulSessionID 指定会话的标识ID；取值范围为1～用户配置BFD规格
*
*       Output: BFD_SESSION_INFO_S* pSess 用于存储会话参数的缓冲区地址指针
*                                         具体数据定义见数据描述
*       Return: 成功返回   BFD_OK
*               失败返回   BFD_ERR_SESSION_ID；      会话ID非法
*                          BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                          BFD_ERR_NULL_POINTER
*                          BFD_ERR_DISABLE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetSessionInfoByVrf(ULONG ulSessionID, BFD_SESSION_INFO_S *pSess,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_GetSessionIdByVrf
* Date Created: 2007-02-19
*       Author: Wangchengyang
*  Description: 通过源目的IP和出接口索引，查询BFD 会话id
*        Input: ulDstIP   目的IP，主机序
*               ulSrcIP   源IP，主机序
*               ulIfIndex 出接口索引
*               ulVrfIndex VRF索引
*
*       Output: 
*       Return: 会话id,如果不存在指定的会话则返回0xFFFFFFFF
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetSessionIdByVrf(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulIfIndex,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name:   BFD_DetectDownWithDiagByPrdtByVrf
*    Date Created:2009-02-20
*    Author:      wangchengyang
*    Description: 产品的NP探测到会话Down时向控制层面的通知接口,带VRF
*    Input:       ULONG ulSessionID: 会话ID
*                   ULONG ulDiag:会话Down的原因(参考BFD 诊断字
*                                                  枚举变量BFD_DIAG_E)
*                 ULONG ulVrfIndex VRF
*    Output:      无
*    Return:      成功返回       BFD_OK
*                 失败返回       BFD_ERR_SESSION_ID
*                                BFD_ERR_SESSION_NOT_EXIST
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-20   wangchengyang    Create for VISP1.7C03,VRF,
*******************************************************************************/
extern ULONG BFD_DetectDownWithDiagByPrdtByVrf(ULONG ulSessionID,ULONG ulDiag,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name:   BFD_DetectDownByPrdtByVrf
*    Date Created:2009-02-20
*    Author:      wangchengyang
*    Description: 产品的NP探测到会话Down时向控制层面的通知接口,带VRF
*    Input:       ULONG ulSessionID: 会话ID
*                 ULONG ulVrfIndex VRF
*    Output:      无
*    Return:      成功返回       BFD_OK
*                 失败返回       BFD_ERR_SESSION_ID
*                                BFD_ERR_SESSION_NOT_EXIST
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-20   wangchengyang    Create for VISP1.7C03,VRF,
*******************************************************************************/
extern ULONG BFD_DetectDownByPrdtByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyByVrfRegister
* Date Created: 2008-3-8
*       Author: LY(57500)
*  Description: BFD通知注册函数
*        Input: BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc: 钩子函数指针
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4    qinyun(62011) 改为链表方式
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyByVrfRegister(BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyByVrfUnRegister
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: BFD通知去注册函数
*        Input: BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc: 钩子函数指针
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4    qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyByVrfUnRegister(BFD_NOTIFY_BYVRF_HOOK_FUNC pBfdNotifyByVrfHookFunc);

/*******************************************************************************
*    Func Name: BFD_ClrSessionCount
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: 根据过滤条件清除BFD会话的统计信息
*        Input: ucSpecSessFlag  操作字(TRUE-使用指定会话清空,FALSE-全部清空)
*               ulLocalDiscr  过滤条件
*               CHAR *pszVrfName
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG BFD_ClrSessionCountByVrf(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr,CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_GetSessionIdByNameByVrf
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: 根据会话名称获取会话索引
*        Input: BFD_SESSION_GET_ID_OR_NAME_S *pInfo: 配置参数
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetSessionIdByNameByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);

/*******************************************************************************
*    Func Name: BFD_GetNameBySessionIdByVrf
* Date Created: 2009-01-07
*       Author: qinyun
*  Description: 根据会话索引获取会话名称
*        Input: BFD_SESSION_GET_ID_OR_NAME_S *pInfo: 配置参数
*       Output: pszSessName: 会话名称
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-07   qinyun(62011)    Creat the first version.
*******************************************************************************/
extern ULONG BFD_GetNameBySessionIdByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);

/*******************************************************************************
*    Func Name: BFD_GetNextSessionIDByVrf
* Date Created: 2009-02-01
*       Author: Wangchengyang
*  Description: 获取指定会话的下一个会话的标识ID（会话按标识ID升序排列）
*        Input: ULONG  ulSessionID 指定的会话ID
*                      当输入参数为0时，返回当前存在的第一个会话的标识ID值；
*                      当输入参数小于用户配置的BFD规格时，返回该ID之后的第一个会话的标识ID值
*                      当输入参数大于等于用户配置的BFD规格 时直接返回0;
*               ulVrfIndex  VRF索引
*
*       Output: 
*       Return: 成功返回       会话标识ID（非0）
*               失败返回       0（当前无会话，或BFD未使能，或者输入ID大于等于 BFD_MAX_SESSION_ID）
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetNextSessionIDByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetDebugSwitchByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 打开或关闭BFD调试开关
*        Input: ULONG ulSessionID 指定会话ID合法性为1~用户配置BFD规格
*                                 若输入为0则标识打开/关闭所有会话的调试开关
*               ULONG ulDebug  设置调试标记,打开(关闭)则将相应标志置位(清零)
*                              BFD_DEBUG_STATE    0x1  BFD状态变迁调试
*                              BFD_DEBUG_INPUT    0x2  接收的BFD报文调试
*                              BFD_DEBUG_OUTPUT   0x4  发送的BFD报文调试
*                              若需要打开多个标记,则可位与
*               ULONG ulVrfIndex  VRF索引
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_INVALID_PARAMETER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SetDebugSwitchByVrf(ULONG ulSessionID, ULONG ulDebug,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_GetDebugSwitchByVrf
* Date Created: 2007-7-31
*       Author: zhangchunyu(62474)
*  Description: 获取BFD的调试开关，如果ulSessionID为0，获取全局Debug开关。否则获取
*                                  指定接口调试开关。
*        Input: ULONG ulSessionID: 会话ID(0-用户配置BFD规格)
*               ULONG ulVrfIndex              Vrf索引
*
*       Output: ULONG *pulDebug: 获取开关指针
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-31    zhangchunyu(62474)     Creat the first version.
*  2009-02-01   wangchengyang          Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_GetDebugSwitchByVrf(ULONG ulSessionID, ULONG *pulDebug,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_DemandQueryByAppByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 触发指定会话的查询序列的发送
*        Input: ULONG  ulSessionID 指定会话的标识ID；
*                                  有效取值范围1-用户配置BFD规格，且必须为已创建会话ID
*               ULONG ulVrfIndex   Vrf索引
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_UP
*                              BFD_ERR_DETECT_MODE
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*                              BFD_ERR_WRITEQUE_FAIL
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_DemandQueryByAppByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetSingleAppToSessionByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 设定某一个会话的具体应用
*        Input: ULONG ulSessionID   会话ID 1~255
*               ULONG ulAppID       应用ID 2的N次幂,一个bit位表示一个应用
*               ULONG ulVrfIndex    Vrf索引
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: 参考《会话状态变化时对外部通知处理》接口；
*               非必要接口；若任何会话的状态变化时，
*               产品适配的《会话状态变化时对外部通知处理》接口采用统一处理时
*               （产品的BFD应用模块较少），不必设置此接口；
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SetSingleAppToSessionByVrf(ULONG ulSessionID, ULONG ulAppID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetAppsToSessionByVrf
* Date Created: 2006-12-06
*       Author: Wangchengyang
*  Description: 设定某一会话的应用模块(应用组,即设置那些应用关系这个会话的状态变化)
*        Input: ULONG ulSessionID   会话ID 1~255
*               ULONG ulAppGroup    会话的应用模块组合，
*                                   每一个Bit标识着该会话的一个应用模块；
*                                   以最后一次设置为准；
*                                   为0表示取消所有模块对该会话的应用；
*                                   最多支持32个外部应用模块。
*               ULONG ulVrfIndex    Vrf索引
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: 参考《会话状态变化时对外部通知处理》接口；
*               非必要接口；若任何会话的状态变化时，
*               产品适配的《会话状态变化时对外部通知处理》接口采用统一处理时
*               （产品的BFD应用模块较少），不必设置此接口；
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01      wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_SetAppsToSessionByVrf(ULONG ulSessionID, ULONG ulAppGroup,ULONG ulVrfIndex);


/* End:VISP1.7C03 VRF wangchengyang,2009-02-12 */

/*******************************************************************************
*    Func Name: BFD6_AddDelSession
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 创建删除一个IPv6 BFD会话，创建时同时设定会话参数
*        Input: pstSession  创建删除的会话信息
*       Output: 
*       Return: 成功返回       BFD_OK       失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD6_AddDelSession(BFD6_SESSION_ADD_DEL_S *pstSession);

/*******************************************************************************
*    Func Name: BFD6_GetSessionConfigEntry
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstConfigInfo:获取到的数据
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_GetSessionConfigEntry(UINTPTR ulEntryWaitList,BFD6_SESSION_CONFIG_INFO_S *pstConfigInfo);

/*******************************************************************************
*    Func Name: BFD6_GetSessionInfoEntry
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstSessionInfo:获取到的数据
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_GetSessionInfoEntry(UINTPTR ulEntryWaitList,BFD6_SESSION_ALL_INFO_S *pstSessionInfo);


/*******************************************************************************
*    Func Name: BFD6_OpenSessionTable
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 获取BFD6会话表的WaitList句柄，并保存过滤条件
*        Input: pstFilter:过滤器结构
*       Output: ULONG *pulWaitListHandle: WaitList句柄
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_OpenSessionTable(UINTPTR *pulWaitListHandle,BFD6_SESSION_FILTER_S *pstFilter);

/*******************************************************************************
*    Func Name: BFD6_CloseSessionTable
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 关闭BFD6会话表的WaitList句柄
*        Input: ULONG ulWaitListHandle: WaitList句柄
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD6_CloseSessionTable(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: BFD6_GetTotalNumber
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 获取总的BFD6会话个数
*        Input: ULONG *pulBfd6SessionCnt:  会话个数
*       Output:
*       Return: BFD_OK:成功;
*               BFD_ERR_NULL_POINTER:指针参数空
*               BFD_ERR_DISABLE:bfd未使能
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD6_GetTotalNumber(ULONG *pulBfd6SessionCnt);

/*******************************************************************************
*    Func Name: TCPIP_Bfd6NotifyRegister
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6通知注册函数
*        Input: BFD6_NOTIFY_BYVRF_HOOK_FUNC pBfd6NotifyHookFunc: 钩子函数指针
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_Bfd6NotifyRegister(BFD6_NOTIFY_HOOK_FUNC pBfd6NotifyHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_Bfd6NotifyUnRegister
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6通知去注册函数
*        Input: BFD6_NOTIFY_BYVRF_HOOK_FUNC pBfd6NotifyHookFunc: 钩子函数指针
*       Output:
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_Bfd6NotifyUnRegister(BFD6_NOTIFY_HOOK_FUNC pBfd6NotifyHookFunc);

/*******************************************************************************
*    Func Name: BFD6_UpdateSession
* Date Created: 2009-4-16
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6会话参数更新
*        Input: pstPara  会话参数
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-16  wangchengyang-xujun62830-57575         VISPV1R8C01.
*******************************************************************************/
extern ULONG BFD6_UpdateSession(BFD_SESSION_UPDATE_S *pstPara);

/*******************************************************************************
*    Func Name: BFD6_AdminSession
* Date Created: 2009-4-16
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD6会话的用户管理，Admindown，undo Admindown
*        Input: pstData  管理结构体
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-16  wangchengyang-xujun62830-57575         VISPV1R8C01.
*******************************************************************************/
extern ULONG BFD6_AdminSession(BFD_SESSION_ADMIN_S *pstData);


/*******************************************************************************
*    Func Name: TCPIP_GR_BFDRestore
* Date Created: 2008-8-17
*       Author: wujie(61195)
*  Description: BFD GR恢复处理
*        Input: VOID
*       Output: 
*       Return: BFD_OK 成功
*               BFD_ERR_GR_STATE 当前不处于保活状态
*               BFD_ERR_NO_NP 未注册NP钩子函数
*               其他 VOS_Ev_Write返回的错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-17  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_BFDRestore(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GR_BFDSmooth
* Date Created: 2008-8-17
*       Author: wujie(61195)
*  Description: BFD GR平滑处理
*        Input: VOID
*       Output: 
*       Return: BFD_OK 成功
*               BFD_ERR_GR_STATE 当前尚未完成GR恢复处理
*               其他 VOS_Ev_Write返回的错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-17  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_BFDSmooth(VOID);


/****************************************************************************
*    Func Name: TCPIP_BfdLicenseChgNotify
* Date Created: 2009-01-14
*       Author: zengshaoyang 62531
*  Description: 用户调用,通知BFD license功能打开或者关闭
*        Input: ULONG ulLicenseFlag:BFD license功能打开 or 关闭
*               #define BFD_LICENSE_ON   0x01
*               #define BFD_LICENSE_OFF  0x00
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 为防止队列太忙,全局一个事件,而不是一个BFD会话发送一个事件
*               可考虑增加一个功能正在关闭中
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-14   zengshaoyang         Create
*
*******************************************************************************/
extern ULONG TCPIP_BfdLicenseChgNotify(ULONG ulLicenseFlag);

/****************************************************************************
*    Func Name: TCPIP_BfdGetLicenseStateRegister
* Date Created: 2009-01-14
*       Author: zengshaoyang 62531
*  Description: 注册获取BFD License功能开关的钩子函数
*        Input: BFD_GET_LICENSE_STATE_FUNC pfFunc:钩子函数
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-14   zengshaoyang         Create
*
*******************************************************************************/
extern ULONG TCPIP_BfdGetLicenseStateRegister(BFD_GET_LICENSE_STATE_FUNC pfFunc);
/****************************************************************************
*    Func Name: BFD_SetAutoLocalDiscrGate
* Date Created: 2010-03-03
*       Author: l00147446
*  Description: BFD静态配置会话索引修改
*        Input: ulGate 设置的阀值
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-03   l00147446        BC3D02737 BFD静态配置会话索引修改
*
*******************************************************************************/
extern ULONG BFD_SetAutoLocalDiscrGate(ULONG ulGate);

/*******************************************************************************
*    Func Name: BFD_SetNotifyTime
* Date Created: 2010-02-25
*       Author: xujun57575
*  Description:
*        Input: ULONG ulTime:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-25   xujun57575              Create
*
*******************************************************************************/
extern ULONG BFD_SetNotifyTime(ULONG ulTime);
/*******************************************************************************
*    Func Name: BFD_SetNotifyTimeFlag
* Date Created: 2010-02-25
*       Author: xujun57575
*  Description:
*        Input: ULONG ulFlag:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-25   xujun57575              Create
*
*******************************************************************************/
extern ULONG BFD_SetNotifyTimeFlag( ULONG ulFlag);
/*******************************************************************************
*    Func Name: BFD_SessionResetAll
* Date Created: 2010-02-26
*       Author: xujun57575
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-26   xujun57575              Create for sgsn Requirement  BC3D02728
*
*******************************************************************************/
extern ULONG BFD_SessionResetAll(VOID);

/*******************************************************************************
*    Func Name: BFD_DownAllSession
* Date Created: 2010-04-13
*       Author: xujun57575
*  Description:
*        Input:
*       Output:
*       Return: ULONG
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   xujun57575              Create
*
*******************************************************************************/
extern ULONG BFD_DownAllSession(VOID);

/*******************************************************************************
*    Func Name: BFD_RegFuncBFDTimeTestHook
* Date Created: 2008-03-15
*       Author: wuhailan
*  Description: BFD报文探测通道时延打点注册钩子
*        Input: ULONG ulType:注册类型,1接收方向,2发送方向
*               pfFuncBFDTimeTestHook pfHook:要注册的函数指针
*       Output: 无
*       Return: BFD_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG BFD_RegFuncBFDTimeTestHook(ULONG ulType, pfFuncBFDTimeTestHook pfHook);


/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreateByVrfByRfc
* Date Created: 2011-05-30
*       Author: baiweiqiang(177000)
*  Description: 设定一个BFD会话的基本参数，并开始建立符合标准RFC协议的BFD会话
*               （主要检查参数有效性，调用CBB实现功能）
*        Input: ULONG ulDstIP        指定会话的目的地址；主机序；
*               ULONG ulSrcIP        指定会话的源地址；主机序；
*               ULONG ulOutIfIndex   单跳会话时为出接口索引，多跳时值为0；
*               ULONG *pulSessionID  取值范围为[0,2000],如果是0则由VISP自动分配会话ID，
*                                    否则根据指定的ID创建会话
*               ULONG ulVrfIndex     VRF Index
*               ULONG ulBfdProtocol  BFD_PROTO_STD：Rfc协议会话 
*                                    BFD_PROTO_DRAFT4 草案4协议会话
*       Output: ULONG *pulSessionID  会话的标识ID
*       Return: 成功返回      BFD_OK
*               其他错误码    失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-05-30  baiweiqiang(177000)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreateByVrfByRfc(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex,
                                   ULONG *pulSessionID, ULONG ulVrfIndex, ULONG ulBfdProtocol);
/*******************************************************************************
*    Func Name: BFD_Shell_SessionCreateByParam
* Date Created: 2012-10-11
*       Author: zhongyu206043
*  Description: 创建BFD会话，并根据用户配置的参数信息配置会话参数
*        Input: ULONG *pulSessionID:指定的本端会话ID, 取值范围为[0,512]，
*                   如果是0则由VISP自动分配会话ID，否则根据指定的ID创建会话
*               BFD_SESSION_CREATE_WITH_PARA_S *pstSessInfo:
*                   会话信息，其中的参数stSessPara中的值如果设置为0则使用VISP
*                   的默认值作为会话的参数；TOS值属于值域有效的参数，VISP不做
*                   有效性判断，直接赋值
*       Output: pulSessionID：自动分配的会话ID
*       Return: 
*               BFD_OK           成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-11   zhongyu206043           Create
*
*******************************************************************************/
extern ULONG BFD_Shell_SessionCreateByParam (ULONG *pulSessionID, BFD_SESSION_CREATE_WITH_PARA_S *pstSessInfo);


/*******************************************************************************
*    Func Name: BFD6_GetNameBySessionIdByVrf
* Date Created: 2012-12-18
*       Author: z00208058
*  Description: 根据会话索引获取会话名
*        Input: BFD_SESSION_GET_ID_OR_NAME_S *pInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-12-18   z00208058               Create
*
*******************************************************************************/
extern ULONG BFD6_GetNameBySessionIdByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);


/*******************************************************************************
*    Func Name: BFD_GetSessionIdByNameByVrf
* Date Created: 2012-12-18
*       Author: z00208058
*  Description: 根据会话名获取会话索引
*        Input: BFD_SESSION_GET_ID_OR_NAME_S *pInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-12-18   z00208058               Create
*
*******************************************************************************/
extern ULONG BFD6_GetSessionIdByNameByVrf(BFD_SESSION_GET_ID_OR_NAME_S *pInfo);

/*******************************************************************************
*    Func Name: BFD_NSR_SendMsg
* Date Created: 2013-03-29
*       Author: w00207740
*  Description: 向BFD写消息
*        Input: ULONG ulMsg:
*               VOID *pData:
*               ULONG ulLength:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-29   w00207740               Create
*
*******************************************************************************/
ULONG BFD_NSR_SendMsg (ULONG ulMsg, UCHAR *pucData, ULONG ulLength);

/*******************************************************************************
*    Func Name: BFD_NSR_PpiDownloadHookRegister
* Date Created: 2013-06-27
*       Author: w00207740
*  Description: 
*        Input: BFD_PPI_HOOK_FUNC pfBfdPpiHook:
*       Output: 
*       Return: 
*      Caution: NSR BFD下发钩子注册函数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-27   w00207740               Create
*
*******************************************************************************/
ULONG BFD_NSR_PpiDownloadHookRegister(BFD_PPI_HOOK_FUNC pfBfdPpiHook);


ULONG BFD_NSR_SetCheckNsrFinishTimer(ULONG ulTime);


ULONG BFD_NSR_GetCheckNsrFinishTimer(ULONG *pulTime);

/*******************************************************************************
*    Func Name: BFD_NSR_GetGlobalInformation
* Date Created: 2013-10-23
*       Author: w00207740
*  Description: 获取NSR全局信息
*        Input: BFD_NSR_GLOBAL_INFO_S *pstBfdNsrGlobalInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-23   w00207740               Create
*
*******************************************************************************/
ULONG BFD_NSR_GetGlobalInformation(BFD_NSR_GLOBAL_INFO_S *pstBfdNsrGlobalInfo);


ULONG BFD_NSR_OpenSessionStatTable(UINTPTR *pulWaitListHandle,BFD_SESSION_FILTER_S *pstFilter);


ULONG BFD_NSR_GetSessionStateEntry(UINTPTR ulEntryWaitList,BFD_NSR_SESS_INFO_S *pstSessionNsrInfo);

/*******************************************************************************
*    Func Name: BFD_NSR_CloseSessionStatTable
* Date Created: 2013-09-11
*       Author: w00207740
*  Description: 
*        Input: ULONG ulWaitListHandle:
*       Output: 
*       Return: 
*      Caution: 关闭表项
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-11   w00207740               Create
*
*******************************************************************************/
ULONG BFD_NSR_CloseSessionStatTable(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: BFD6_GetSessionState
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 获取BFD会话状态
*        Input: ULONG ulSessionID:会话ID
*               ULONG ulVrfIndex: vrf索引
*       Output: ULONG *pstState:返回的会话状态
*       Return: 成功BFD_OK,其他返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi           Create
*
*******************************************************************************/
ULONG BFD6_GetSessionState(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

/*******************************************************************************
*    Func Name: BFD6_GetNextSessionID
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 获取指定会话的下一个会话的标识ID（会话按标识ID升序排列）
*        Input: ULONG  ulSessionID 指定的会话ID
*                      当输入参数为0时，返回当前存在的第一个会话的标识ID值；
*                      当输入参数小于用户配置的BFD规格时，返回该ID之后的第一个会话的标识ID值
*                      当输入参数大于等于用户配置的BFD规格时直接返回0;
*       Output: 
*       Return: 成功返回       会话标识ID（非0）
*               失败返回       0（当前无会话，或BFD未使能，或者输入ID大于等于 BFD_MAX_SESSION_ID）
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetNextSessionID(ULONG ulSessionID);

/*******************************************************************************
*    Func Name: BFD6_GetNextSessionIDByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 获取指定会话的下一个会话的标识ID（会话按标识ID升序排列）
*        Input: ULONG  ulSessionID 指定的会话ID
*                      当输入参数为0时，返回当前存在的第一个会话的标识ID值；
*                      当输入参数小于 g_ulBFDTotalSession 时，返回该ID之后的第一个会话的标识ID值
*                      当输入参数大于等于 g_ulBFDTotalSession 时直接返回0;
*               ulVrfIndex  VRF索引
*
*       Output: 
*       Return: 成功返回       会话标识ID（非0）
*               失败返回       0（当前无会话，或BFD未使能，或者输入ID大于等于 BFD_MAX_SESSION_ID）
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Create 
*******************************************************************************/
ULONG BFD6_GetNextSessionIDByVrf(ULONG ulSessionID,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD6_GetNameBySessionId
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 根据会话索引获取会话名称
*        Input: ulSessionId: 会话索引
*               ulLength：用户输入的内存长度
*       Output: pszSessName: 会话名称
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetNameBySessionId(ULONG ulSessionId,UCHAR *pszSessName,ULONG ulLength);

/*******************************************************************************
*    Func Name: BFD6_GetSessionInfoByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 获取指定会话的当前信息
*        Input: ULONG  ulSessionID 指定会话的标识ID；取值范围为1～用户配置BFD规格
*               ulVrfIndex  VRF索引
*       Output: BFD_SESSION_INFO_S* pSess 用于存储会话参数的缓冲区地址指针
*                                         具体数据定义见数据描述
*       Return: 成功返回   BFD_OK
*               失败返回   BFD_ERR_SESSION_ID；      会话ID非法
*                          BFD_ERR_SESSION_NOT_EXIST 指定会话不存在
*                          BFD_ERR_NULL_POINTER
*                          BFD_ERR_DISABLE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Create for BFD VRF6
*******************************************************************************/
ULONG BFD6_GetSessionInfoByVrf(ULONG ulSessionID, BFD6_SESSION_INFO_S *pSess,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD6_GetSessionCountEntry
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstCount:获取到的数据
*       Return: 成功返回 BFD_OK
*               失败返回 BFD_ERR_GET_ENTRY_END   从表中获取不到符合过滤器的数据指针
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Creat the first version.
*******************************************************************************/
ULONG BFD6_GetSessionCountEntry(UINTPTR ulEntryWaitList,BFD_SESSION_COUNT_S *pstCount);

/*******************************************************************************
*    Func Name: BFD6_GetSessionBriefEntry
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstBriefInfo:获取到的数据
*       Return: 成功返回 BFD_OK
*               失败返回 BFD_ERR_GET_ENTRY_END   从表中获取不到符合过滤器的数据指针
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Creat the first version.
*******************************************************************************/
ULONG BFD6_GetSessionBriefEntry(UINTPTR ulEntryWaitList,BFD_SESSION_BRIEF_INFO_S *pstBriefInfo);

/*******************************************************************************
*    Func Name: BFD6_ClrSessionCount
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 根据过滤条件清除BFD会话的统计信息
*        Input: ucSpecSessFlag  操作字(TRUE-使用指定会话清空,FALSE-全部清空)
*               ulLocalDiscr  过滤条件
*               CHAR *pszVrfName
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14      wangjiaqi        Creat the first version.
*******************************************************************************/
ULONG BFD6_ClrSessionCountByVrf(UCHAR ucSpecSessFlag,ULONG ulLocalDiscr,CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD6_ShowSessionInfoByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 显示指定VRF的BFD6所有会话信息
*        Input: CHAR *pszVrfName VRF名
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi        Create
*******************************************************************************/
VOID BFD6_ShowSessionInfoByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD6_ShowSessionCountByVrf
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: 显示指定VRF下所有BFD6所有会话统计信息
*        Input: pszVrfName VRF 名
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi        Create
*******************************************************************************/
VOID BFD6_ShowSessionCountByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_GetBfdVersion
* Date Created: 2013-11-14
*       Author: wangjiaqi
*  Description: get BFD ip version
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: ULONG *pulVersion: BFD_OVER_IPV4/BFD_OVER_IPV6
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-14   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_GetBfdSessionVersion(ULONG ulVrfIndex, ULONG ulSessionId, ULONG *pulVersion);

/*******************************************************************************
*    Func Name: BFD_GetSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: get BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: BFD_STATISTIC_S *pstStat
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_GetSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId, BFD_STATISTIC_S * pstStat);

/*******************************************************************************
*    Func Name: BFD_ShowSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: show BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
VOID BFD_ShowSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId);

/*******************************************************************************
*    Func Name: BFD_ClrSessionStatics
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: show BFD session statics
*        Input: ULONG ulVrfIndex
                ULONG ulSessionId
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi               Create    
*
*******************************************************************************/
ULONG BFD_ClrSessionStatics(ULONG ulVrfIndex ,ULONG ulSessionId);

/*******************************************************************************
*    Func Name: BFD6_SessionResetAll
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi               Create
*
*******************************************************************************/
ULONG BFD6_SessionResetAll(VOID);

/*******************************************************************************
*    Func Name: BFD6_DownAllSession
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description:
*        Input:
*       Output:
*       Return: ULONG
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi               Create
*
*******************************************************************************/
ULONG BFD6_DownAllSession(VOID);

/*******************************************************************************
*    Func Name: BFD6_SetBfdCapability
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: 使能或去使能BFD6功能
*
*        Input: BOOL_T bBfdCapability TRUE－使能；FALSE－去使能；
*
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_DISABLE_PROCESSING
*                              BFD_ERR_INVALID_PARAMETER
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_SetBfdCapability(BOOL_T bBfdCapability);

/****************************************************************************
*    Func Name: TCPIP6_BfdLicenseChgNotify
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: 用户调用,通知BFD6 license功能通过或不通过
*        Input: ULONG ulLicenseFlag:BFD license功能通过或不通过
*               #define BFD_LICENSE_ON   0x01
*               #define BFD_LICENSE_OFF  0x00
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 为防止队列太忙,全局一个事件,而不是一个BFD会话发送一个事件
*               可考虑增加一个功能正在关闭中
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi        Create
*
*******************************************************************************/
ULONG TCPIP_Bfd6LicenseChgNotify(ULONG ulLicenseFlag);

/****************************************************************************
*    Func Name: TCPIP_BfdGetLicenseStateRegister
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: 注册获取BFD6 License功能开关的钩子函数
*        Input: BFD_GET_LICENSE_STATE_FUNC pfFunc:钩子函数
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-21   wangjiaqi        Create
*
*******************************************************************************/
ULONG TCPIP_Bfd6GetLicenseStateRegister(BFD_GET_LICENSE_STATE_FUNC pfFunc);

/*******************************************************************************
*    Func Name: BFD6_SetAdaptMultiHopPort
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: 设置是否自动调整多跳会话的UDP目的端口号。VRP旧版BFD的多跳端口号
*               与单跳端口号一样都是3784，VISP为了与其多跳会话对接作了一些修改。详见A82D18150。
*        Input: ULONG ulSwitch: BFD_ON/打开 BFD_OFF/关闭
*       Output: 
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_HA_IS_SMOOTHING;
*                              BFD_ERR_INVALID_PARAMETER;
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25  wangjiaqi        Creat the first version.
*
*******************************************************************************/
ULONG BFD6_SetAdaptMultiHopPort(ULONG ulSwitch);

/****************************************************************************
*    Func Name: BFD6_SetAutoLocalDiscrGate
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: BFD6静态配置会话索引修改
*        Input: ulGate 设置的阀值
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25   wangjiaqi        create
*
*******************************************************************************/
ULONG BFD6_SetAutoLocalDiscrGate(ULONG ulGate);
/*******************************************************************************
*    Func Name: BFD_OpenSessionTableEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 获取BFD会话表的句柄，并保存过滤条件
*        Input: ULONG *pulWaitListHandle:
*               BFD_SESSION_FILTER_EX_S *pstFilter:
*       Output: 
*       Return: 
*      Caution: 该API融合BFD_OpenSessionTable和BFD6_OpenSessionTable的基本功能。
*               可以同时查询BFD4和BFD6的会话信息
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_OpenSessionTableEx(UINTPTR *pulWaitListHandle, BFD_SESSION_FILTER_EX_S *pstFilter);
/*******************************************************************************
*    Func Name: BFD_CloseSessionTableEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 关闭会话表，释放filter资源
*        Input: ULONG ulWaitListHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_CloseSessionTableEx(UINTPTR ulWaitListHandle);
/*******************************************************************************
*    Func Name: BFD_GetSessionInfoEntryEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstSessionInfo:获取到的会话数据
*       Return: 成功返回 BFD_OK
*               失败返回 BFD_ERR_GET_ENTRY_END   从表中获取不到符合过滤器的数据指针
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetSessionInfoEntryEx(UINTPTR ulEntryWaitList, BFD_SESSION_ALL_INFO_EX_S *pstSessionInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionConfigEntryEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstConfigInfo:获取到的会话配置数据
*       Return: 成功返回 BFD_OK
*               失败返回 BFD_ERR_GET_ENTRY_END   从表中获取不到符合过滤器的数据指针
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetSessionConfigEntryEx(UINTPTR ulEntryWaitList, BFD_SESSION_CONFIG_INFO_EX_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: BFD_GetSessionCountEntryEx
* Date Created: 2014-07-16
*       Author: likaikun213099
*  Description: 通过WaitList句柄，获取下一条满足过滤器的数据指针
*        Input: ULONG ulEntryWaitList: WaitList句柄
*       Output: pstCount:获取到的统计数据
*       Return: 成功返回 BFD_OK
*               失败返回 BFD_ERR_GET_ENTRY_END   从表中获取不到符合过滤器的数据指针
*                        BFD_ERR_WAITLIST
*                        BFD_ERR_DISABLE
*                        BFD_ERR_HA_IS_SMOOTHING
*                        BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-16   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetSessionCountEntryEx(UINTPTR ulEntryWaitList, BFD_SESSION_COUNT_EX_S *pstCount);
/*******************************************************************************
*    Func Name: BFD6_NSR_PpiDownloadHookRegister
* Date Created: 2014-07-22
*       Author: likaikun213099
*  Description: 
*        Input: BFD6_PPI_HOOK_FUNC pfBfd6PpiHook:
*       Output: 
*       Return: 
*      Caution: NSR BFD下发钩子注册函数
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-22   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_PpiDownloadHookRegister(BFD6_PPI_HOOK_FUNC pfBfd6PpiHook);

/*******************************************************************************
*    Func Name: BFD6_NSR_OpenSessionStatTable
* Date Created: 2014-07-23
*       Author: likaikun213099
*  Description: 
*        Input: ULONG *pulWaitListHandle:
*               BFD6_SESSION_FILTER_S *pstFilter:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_OpenSessionStatTable(UINTPTR *pulWaitListHandle,BFD6_SESSION_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: BFD6_NSR_GetSessionStateEntry
* Date Created: 2014-07-23
*       Author: likaikun213099
*  Description: 
*        Input: ULONG ulWaitListHandle:
*               BFD6_NSR_SESS_INFO_S *pstSessionNsrInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_GetSessionStateEntry(UINTPTR ulWaitListHandle, BFD6_NSR_SESS_INFO_S *pstSessionNsrInfo);
/*******************************************************************************
*    Func Name: BFD6_NSR_CloseSessionStatTable
* Date Created: 2014-07-23
*       Author: likaikun213099
*  Description: 
*        Input: ULONG ulWaitListHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-07-23   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD6_NSR_CloseSessionStatTable(UINTPTR ulWaitListHandle);
/*******************************************************************************
*    Func Name: BFD_Core_GetSessionCount
* Date Created: 2008-8-4
*       Author: qinyun(62011) 
*  Description: 根据指定的会话索引获取会话统计信息
*        Input: ulSessionId: 会话索引
*               ulVrfIndex:  VRF索引
*       Output: pstCount: 会话统计信息
*       Return: 成功返回       BFD_OK
*               失败返回       BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE    
*                              BFD_ERR_HA_IS_SMOOTHING    
*                              BFD_ERR_NULL_POINTER    
*                              BFD_ERR_SESSION_ID    
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-4     qinyun(62011)    Creat the first version.
*  2008-02-19   wangchengyang    VISP1.7C03,VRF,增加一个入参
*******************************************************************************/
ULONG BFD_Core_GetSessionCount(ULONG ulSessionId,BFD_SESSION_COUNT_S *pstCount,ULONG ulVrfIndex);
#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _BFD_API_H_    */

