/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_PUB.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _TCPIP_IFPUB_H_
#define _TCPIP_IFPUB_H_

#ifdef  __cplusplus
extern "C"{
#endif


/*接口类，定义接口类公共属性和组成成员*/
typedef struct tagIF_Class_S
{
    ULONG   if_ulType ;             /* 接口类型 */
    ULONG   if_ulProperty;          /* 接口属性 */
    ULONG   if_ulFlags;
    ULONG   if_ulOpFlag;    /* 支持的命令操作标识 */  

    /* 
     * 接口标志属性： 
     * &IF_MOVING 表示该端口可被删除
     * &IF_TEMPIF 临时接口标志
     * &IF_NOCONFIG 接口不可配置
     * &IF_INVISIBLE 接口不可显示( 不可显示接口信息 )
     * 缺省状态是 不可删除、非临时接口、可见、可配置
     */
    ULONG   if_ulMoving ;  
    CHAR  if_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];   /* 接口类名 */
    CHAR  if_szSimpleName[ IF_MAX_INTERFACE_NAME_LEN+1];   /*简单 接口类名 */
    CHAR  if_szCmdTemple[ MAX_IFCMD_NAME_LEN+1];      /* 接口命令模式名 */

    /*
     * 由下标确定是哪一层的公共接口指针
     * 0:上层公共接口虚函数表指针，不能为空    #define IF_LAYER_IP       0 
     * 1:针对IPv6的层，可以为空                #define IF_LAYER_IPV6     1 
     * 2:链路层公共接口虚函数表指针，不能为空  #define IF_LAYER_LINK     2 
     * 3:设备层公共接口虚函数表指针，可以为空  #define IF_LAYER_PHISICAL 3 
     */
    struct IIF_IFS_IntFunVtbl *if_pstLayer[IF_LAYER_MAX] ;

    IF_PRETREATFUN if_pPreFun;      /* 接口命令模式名后缀预处理函数，如将接口索引转换为port。默认为NULL*/

    /***********************************************
     *                 控制类标志                  *
     ***********************************************/

    /*
     * VT接口标志：
     * 0，普通接口类型； #define IF_INTERFACE_NORMAL 0
     * 1，VT接口；       #define IF_INTERFACE_VT     1
     * 2，VA接口         #define IF_INTERFACE_VA     2
     */
    ULONG   if_ulVTFlag;             
    ULONG   if_ulSpoofing;
    ULONG   if_ulPortType;
    ULONG   if_ulLogicFlag;  /*逻辑接口标识VOS_TRUE：是逻辑接口 VOS_FALSE：非逻辑(设备接口)*/
    ULONG   if_ulCloneFlag;  /*逻辑接口需要在所有接口板上仿造标识VOS_TRUE：需要仿造  VOS_FASLE：不需要仿造*/
    ULONG   if_ulResumeLevel;/*接口恢复等级(0~1)，0为正常，1优先恢复，适应某些接口间的依赖关系，默认为0*/

    /***********************************************
     *       接口帮助信息，为命令行服务            *
     ***********************************************/   
     
    ULONG   if_ulBeginNum;         /* 接口起始编号(含) */
    ULONG   if_ulEndNum;           /* 接口结束编号(含) */
    ULONG   if_ulMaxNum;           /* 接口最大数量 */

    ULONG   if_ulSubIfFlag;        /*允许子接口标识 VOS_TRUE：允许有子接口  VOS_FASLE：不允许*/
    ULONG   if_ulSubBeginNum;      /* 子接口起始编号(含) */
    ULONG   if_ulSubEndNum;        /* 子接口结束编号(含) */
    ULONG   if_ulMaxSub;           /* 子接口最大数量 */

    ULONG   if_ulMinMtu;           /* Mtu 下限值 */
    ULONG   if_ulMaxMtu;           /* Mtu 上限值 */

    ULONG   if_ulChannelBeginNum;  /* 子通道接口起始编号(含) */
    ULONG   if_ulChannelEndNum;    /* 子通道接口结束编号(含) */
    ULONG   if_ulMaxChannel;       /* 子通道最大数量 */

    ULONG   if_ulHelpIndex;        /* 接口的帮助索引 */
    ULONG   if_usIndexHelpIndex;   /* 接口编号的帮助索引 */
    ULONG   if_ulChannelHelpIndex;   
    
}IF_CLASS_S ;

/********** 产品系统描述 ***********/   
typedef struct tagVRPInterface
{
    ULONG       if_ulLevel;             /* 接口编号中‘/’的最多个数，即最大编号维度－1 */
    
    ULONG       if_ulBoardNum;          /* 最大接口板数目,为0即认为没有接口板 */
    ULONG       if_ulCardNum;           /* 板下的最大接口卡数 */
    ULONG       if_ulIfNum;             /* 卡上的最大接口数 */

    ULONG       if_ulIfTypeMaxEnum;     /* 系统的接口类类型的最大枚举值 */
    ULONG       if_ulIfClassMax;        /* 系统的接口类最大可能个数(>=if_ulIfClassNum) */
    ULONG       if_ulIfClassNum;        /* 当前已经注册的系统的接口类数目 */
    ULONG       if_ulMainBoardID;       /*主板ID add by luohanjun*/
    ULONG       if_ulSelfBoardID;       /*本板ID*/
    IF_CLASS_S* if_pstIfClass;          /* 接口的类型描述数组指针 */

} VRP_INTERFACE_S;

typedef struct tagIF_SH_CALL_S
{
    CHAR* (*pfIF_Sh_GetMsg_Router_En)(ULONG ulIndex); /* 获取英文描述信息 */

    ULONG (*pfIF_Sh_OutStringWait)( ULONG ulExecID, CHAR * szOutString, ULONG * ulCurLine );

    ULONG (*pfIF_Sh_GetLanguageMode)(ULONG ulExecID);
    ULONG (*pfIF_Sh_PPPGetUserName)(IFNET_S *pstIfnet,CHAR *szName);
    ULONG (*pfIF_Sh_PPPGetPeerIPAddr)(IFNET_S *pstIfnet,ULONG *ulIpAddr);

    ULONG (*pfIF_Sh_KRTMsgSend)(VLINKSTATUS_S *pstIFNETMsg);
    ULONG (*pfIF_Sh_KRTMsg6Send)(IFVLINKENTRY6_S *pstIFNETMsg);
} IF_SH_CALL_S;


typedef struct tagIF_MOD_INFO
{
    ULONG    ulIfModID;
    ULONG    ulIf_If_SID;        
    ULONG    ulIfIpcNotifyQueID;
    ULONG   ulIfIPCID;
    ULONG   ulRMIPV6ID;
    ULONG   ulRMIPV6_IID;
    
} IF_MOD_INFO_S;


DECLARE_INTERFACE(IIF_IFNET_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIF_Init_Com)();
    METHOD_(ULONG, pfIF_SetModuleInfo)(IF_MOD_INFO_S* pstMInfo);
    METHOD_(ULONG, pfIF_RegisterAll)(IF_SH_CALL_S* pstShellCall);
    METHOD_(ULONG, pfIF_RegisterProductParam)(VRP_INTERFACE_S* pstProduct);
    METHOD_(ULONG, pfIF_Register_IFClass)(IF_CLASS_S* pstIfClass ) ; /*向core注册接口类*/
    METHOD_(IF_CLASS_S*, pfIF_FindClassByType)(ULONG ulType);       /*根据类型从core中获取接口类指针*/
    METHOD_( ULONG,pfTCPIP_HA_SetIfnetDbg ) (ULONG ulDbg);
    METHOD_( ULONG,pfIF_HA_GetIfnetDbg ) (ULONG *pulDbg);
    METHOD_(ULONG, pfIF_HA_SetVerboseDbg) (ULONG ulDbg);
    METHOD_(ULONG, pfIF_HA_GetVerboseDbg) (ULONG *pulDbg);
    METHOD_( VOID, pfIF_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);

};


DECLARE_INTERFACE(IIF_IFNET_ComIntSSA)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIF_SetDevLinkPtr)( ULONG ulType,DEVLINK_S ** ppDev);

    METHOD_(ULONG, pfIF_Init_Com)();
};


#ifdef  __cplusplus
}
#endif

#endif  /* _TCPIP_IFPUB_H_ */

