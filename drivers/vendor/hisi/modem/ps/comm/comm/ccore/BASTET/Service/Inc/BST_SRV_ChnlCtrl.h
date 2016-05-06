
/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_ChnlCtrl.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2015年04月04日
  最近修改   :
  功能描述   : 处理多级数据优先级问题
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月21日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_SRV_CHNLCTRL_H__
#define __BST_SRV_CHNLCTRL_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "BST_IP_Socket.h"
#include "BST_OS_Timer.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/**/
#define BST_Test_Buf_Num                256
#define BST_SRV_BUF_LOW                 ( BST_Test_Buf_Num >> 3 )
#define BST_SRV_BUF_HIGH                ( BST_Test_Buf_Num >> 2 )

#define BST_SRV_BLOCK_SIZE              ( BST_IP_MTU_SIZE - BST_IP_RSV_SIZE )
#define BST_SRV_AlocIpBlock()           ( BST_SRV_CHNL_HEAD_STRU *)( BST_OS_BUF_MALLOC( BST_OS_SIZEOF(BST_SRV_CHNL_HEAD_STRU) ) )
#define BST_SRV_FreeIpBlock(pdata)      BST_OS_BUF_FREE(pdata)
#define BST_SRV_GetIpBlockRemain()      BST_OS_BUF_IDLENUM()
#define BST_SRV_CHNL_RTX_INTERVAL       ( 1000 )
#define BST_SRV_CHNL_RTX_MAX            ( 10 )
#define BST_SRV_CHNL_DATA_LEN           ( 4 )
#define BST_SRV_ChnlIsTail(pItem)       ( ( BST_DSPP_FLG_PKTADDR_TAIL == (pItem)->ucPktAddr )\
                                        ||( BST_DSPP_FLG_PKTADDR_SINGLE == (pItem)->ucPktAddr ) )
#define BST_SRV_IsChnlEmpty(pchnl)      ( ( BST_NULL_PTR == (pchnl)->pSentList ) \
                                        &&( BST_NULL_PTR == (pchnl)->pUnsendList ) )

#define BST_SRV_Q_PeekHead(pList)       (pList)
#define BST_SRV_Q_IsEmpty(pList)        ( BST_NULL_PTR == (pList))
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum BST_SRV_CHNL_STATE
{
    BST_SRV_CHNL_STATE_UN_INITED        = 0,
    BST_SRV_CHNL_STATE_INITED,
    BST_SRV_CHNL_STATE_RUN,
    BST_SRV_CHNL_STATE_SUSPEND,
    BST_SRV_CHNL_STATE_BUTT
};
typedef BST_UINT32                      BST_SRV_CHNL_STATE_ENUM_UINT32;


/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
class BST_SRV_CChnlIpRcver: BST_PUBLIC BST_IP_CNetRcver
{
BST_PUBLIC:
    static BST_SRV_CChnlIpRcver *GetInstance();
BST_PRIVATE:
    BST_SRV_CChnlIpRcver( BST_VOID );
   ~BST_SRV_CChnlIpRcver( BST_VOID );
    BST_IP_ERR_T                Connectd(
        BST_IP_CSocket             *pcSocket );

    BST_IP_PKTPROC_MODE_ENUM    Received(
        BST_IP_CSocket             *pcSocket,
        const BST_UINT8            *const pucData,
        const BST_UINT16            usLength );

    BST_VOID                    IpErr (
        BST_IP_CSocket             *pcSocket,
        BST_IP_ERR_T                InIpErrMsg );

    BST_VOID                    Acked (
        BST_IP_CSocket             *pcSocket,
        const BST_UINT32            ulMinNumber,
        const BST_UINT32            ulMaxNumber );
};

typedef union{
    BST_IP_SOCKET_ADD_T             stInet;
    struct
    {
        BST_PROCID_T                usProcId;
        BST_TASKID_T                usTaskId;
    }stTask;
}BST_SRV_CHNL_ADDR_STRU;

typedef struct BST_SRV_CHNL_Q{
    BST_SRV_CHNL_Q                 *pNext;
}BST_SRV_CHNL_Q;

typedef struct BST_SRV_CHNL_SENT_STRU{
    BST_SRV_CHNL_SENT_STRU         *pNext;
    BST_UINT32                      ulAckNo;
    BST_UINT16                      usProcLevel;
    BST_UINT8                       aucReserv[2];
}BST_SRV_CHNL_SENT_STRU;

typedef struct BST_SRV_CHNL_HEAD_STRU{
    BST_SRV_CHNL_HEAD_STRU         *pNext;
    BST_IPLINK_ID1_T                ulMainLinkId;
    BST_IPLINK_ID2_T                ulAuxLinkId;
    BST_UINT16                      usCmdId;
    BST_UINT16                      usProcLevel;
    BST_UINT8                       ucAddrType;
    BST_UINT8                       ucPropType;
    BST_UINT8                       ucIpProtocol;
    BST_UINT8                       ucPktAddr;
    BST_SRV_CHNL_ADDR_STRU          stAddr;
    BST_IP_SKT_PROPTY_STRU          stProp;
    BST_UINT32                      ulUsed;
    BST_UINT8                       aucData[BST_SRV_BLOCK_SIZE];
}BST_SRV_CHNL_HEAD_STRU;

typedef struct BST_SRV_CHNL_LINK_STRU{
    BST_SRV_CHNL_LINK_STRU         *pNext;
    union{
        struct {
        BST_UINT32                  ulMainLinkId;
        BST_UINT32                  ulAuxLinkId;
        }stLink;
        struct {
        BST_UINT16                  usProcId;
        BST_UINT16                  usTaskId;
        }stDspp;
    };
    BST_UINT32                      ulAddrType;
    BST_OS_TIMERID_T                ulTimerId;
    BST_UINT32                      ulRetryTimes;
    BST_UINT32                      ulCurrentSeq;
    BST_SRV_CHNL_STATE_ENUM_UINT32  enState;
    BST_UINT32                      ulIsPropSet;
    BST_IP_CSocket                 *pcSocket;
    BST_SRV_CHNL_SENT_STRU         *pSentList;
    BST_SRV_CHNL_HEAD_STRU         *pUnsendList;
}BST_SRV_CHNL_LINK_STRU;

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

BST_VOID BST_SRV_CHNL_InitLink(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_IP_CSocket             *pcSocket,
    BST_OS_TIMERID_T            ulTimerId );

BST_ERR_ENUM_UINT8 BST_SRV_CHNL_ProcInCB(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink );

BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Send( 
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem );

BST_VOID BST_SRV_CHNL_Close(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink );

BST_VOID BST_SRV_CHNL_Clear(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink );

BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Acked (
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem,
    const BST_UINT32            ulMinNumber,
    const BST_UINT32            ulMaxNumber );

BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Itf(
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem );


inline BST_VOID BST_SRV_Q_RmvItem(
    BST_SRV_CHNL_Q            **ppList,
    BST_SRV_CHNL_Q             *pItem,
    BST_SRV_CHNL_Q            **ppAuxItem )
{
    BST_SRV_CHNL_Q         *pTmpItem1;
    BST_SRV_CHNL_Q         *pTmpItem2;

    pTmpItem1               = *ppList;
    pTmpItem2               = BST_NULL_PTR;
    /* 
     * 从单链表中查找结点pItem，找到后由pTmpItem1指向该结点，
     * 由pTmpItem2指向其前驱结点
     */
    while ( pTmpItem1 != BST_NULL_PTR )
    {
        if ( pTmpItem1 == pItem )
        {
            break;
        }
        pTmpItem2           = pTmpItem1;
        pTmpItem1           = pTmpItem1->pNext;
    }
    /*查找失败，无此节点*/
    if ( BST_NULL_PTR == pTmpItem1 )
    {
        return;
    }
    /*删除表头或非表头分别处理*/
    if ( BST_NULL_PTR == pTmpItem2 )
    {
        *ppList             = (*ppList)->pNext;
        *ppAuxItem          = *ppList;
    }
    else
    {
        *ppAuxItem          = pTmpItem1->pNext;
        pTmpItem2->pNext    = pTmpItem1->pNext;
        
    }
}
inline BST_VOID BST_SRV_Q_PushToTail(
    BST_SRV_CHNL_Q            **ppList,
    BST_SRV_CHNL_Q             *pItem )
{
    BST_SRV_CHNL_Q            *pTmpItem1;

    pTmpItem1               = *ppList;
    if ( BST_NULL_PTR == pTmpItem1 )
    {
        *ppList              = pItem;
    }
    else
    {
        while ( pTmpItem1->pNext != BST_NULL_PTR )
        {
            pTmpItem1        = pTmpItem1->pNext;
        }
        pTmpItem1->pNext     = pItem;
    }
}
BST_VOID BST_SRV_CHNL_ReportTrafficFlow(
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem );
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif



#endif

