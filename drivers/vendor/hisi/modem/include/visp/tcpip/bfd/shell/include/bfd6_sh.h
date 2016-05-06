typedef struct tagBFD_NEGOFAIL_S
{
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4]; 
    ULONG ulPeerAddr[4]; 
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1]; 
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    ULONG ulProtocol;      /* IPv6/IPv4标识:0-IPv4,1-IPv6 */
}BFD_NEGOFAIL_S;

/* Bfd6 全局socket结构 */
typedef struct tagBFD6_SOCK_INFO_S
{
    LONG lMutiRcv;    /* 多跳接收 */
    LONG lOneRcv;     /* 单跳接收 */
    LONG lSnd;        /* 报文发送 */
}BFD6_SOCK_INFO_S;

/* 关闭socket */
#define BFD6_CLOSE_SOCKET(lSocktId)\
{\
    if (-1 != lSocktId)\
    {\
        (VOID)close(lSocktId);\
        lSocktId = -1;\
    }\
}


ULONG BFD6_GetVrfIndexByName(CHAR *pszVrfName,ULONG *pulVrfIndex);

ULONG BFD6_GetVrfNameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);

CHAR * BFD6_Inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);

ULONG BFD6_Shell_Init();

ULONG BFD6_Shell_Send (UCHAR* pIpPacket, BFD_PKTINFO_S * pstSndPktInfo);
ULONG BFD6_Shell_Init_Socket();
VOID BFD6_Shell_Close_GlobalSocket();

extern ULONG g_ulBfd6EnableFlag;
/*******************************************************************************
*    Func Name: BFD6_GetRtmInstByIndex
* Date Created: 2013-11-25
*       Author: Wangchengyang
*  Description: 通过VRF ID获取路由管理实例号
*        Input: ulVrfIndex :VRF ID
*       Output: pulInst:实例号
*       Return: 
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetRtmInstByIndex(ULONG ulVrfIndex,ULONG *pulInst);

/*******************************************************************************
*    Func Name: BFD6_GetVrfIndexByIfIndex
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: 通过接口索引获取其VRF6 索引
*        Input: ulIfIndex  :接口索引
*       Output: pulVrfIndex:VRF 索引
*       Return: 
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetVrfIndexByIfIndex(ULONG ulIfIndex,ULONG *pulVrfIndex);

/*******************************************************************************
*    Func Name: BFD6_Shell_CreateCheck
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: 设定一个BFD6会话的基本参数
*               （主要检查参数有效性）
*        Input: pstSession            创建删除的会话信息(和原结构定义不同,这里入参已经将地址转为网络序)
*               ULONG ulOutIfIndex    单跳会话时为出接口索引，多跳时值为0；
*               ULONG ulVrfIndex      VRF索引
*
*       Output:
*       Return: 成功返回      BFD_OK
*               失败返回      错误码
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8        wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
struct tagBFD6_SESSION_ADD_DEL_S;
ULONG BFD6_Shell_CreateCheck(struct tagBFD6_SESSION_ADD_DEL_S *pstSession, ULONG ulOutIfIndex,ULONG ulVrfIndex);

ULONG BFD6_CheckVRFValid(ULONG ulIfIndex, ULONG ulVRFIndex);



