/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DSPP_TrsLayer.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : DSPP协议传输层处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_DSPP_TRSLAYER_H__
#define __BST_DSPP_TRSLAYER_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_DSPP_LayerProcBase.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Timer.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DSPP_TP_INVALID_PKTNUM      ( 0xFFFF )
#define BST_DSPP_TP_MIN_S2M_PKTNUM      ( 0x8000 )
#define BST_DSPP_TP_MAX_S2M_PKTNUM      ( 0x8FFF )
#define BST_DSPP_TP_MAX_RETX            ( 3 )
#define BST_DSPP_TP_MIN_M2S_PKTNUM      ( 0x1000 )
#define BST_DSPP_TP_MAX_M2S_PKTNUM      ( 0x1FFF )
#define BST_DSPP_TP_VERA_HEAD           ( 0x7E )
#define BST_DSPP_TP_VERA_TAIL           ( 0x7E )
#define BST_DSPP_TP_ERR_SUB_L           ( 0x03 )
#define BST_DSPP_TP_ERR_SUB_H           ( 0x02 )
#define BST_DSPP_TP_FIRST_PIECE_NUMBER  ( 0x00 )

#define BST_DSPP_TPA_MAX_LENGTH         ( 2048 )
#define BST_DSPP_TPA_BEGIN_ADDR         ( 0x00 )
#define BST_DSPP_TPA_BEGIN_FLAG_LEN     ( 0x01 )
#define BST_DSPP_TPA_FINISH_FLAG_LEN    ( 0x01 )
#define BST_DSPP_TPA_ERR_CODE_L         ( 0x00 )
#define BST_DSPP_TPA_ERR_CODE_H         ( 0x01 )
#define BST_DSPP_TPA_ERR_LEN            ( 0x02 )

#define BST_DSPP_TPA_OFFSET_ADDR        ( BST_DSPP_TPA_BEGIN_FLAG_LEN + BST_DSPP_TPA_HEAD_LEN )
#define BST_DSPP_TPA_FLAG_LEN           ( BST_DSPP_TPA_BEGIN_FLAG_LEN + \
                                          BST_DSPP_TPA_FINISH_FLAG_LEN + \
                                          BST_DSPP_TPA_ERR_LEN )
#define BST_DSPP_TPA_TAIL_LEN           ( BST_DSPP_TPA_FINISH_FLAG_LEN + BST_DSPP_TPA_ERR_LEN )
#define BST_DSPP_TPA_MAX_SDU            ( BST_ACOM_PACKET_SIZE - BST_DSPP_TPA_HEAD_LEN - BST_DSPP_TPA_FLAG_LEN )
#define BST_DSPP_TPA_PKT_LENGTH(pusSdu) ( (pusSdu) + BST_DSPP_TPA_HEAD_LEN + BST_DSPP_TPA_FLAG_LEN )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum
{
    BST_DSPP_TP_DVC_ID                  = 0x00,
    BST_DSPP_TP_PKT_NUM_L,
    BST_DSPP_TP_PKT_NUM_H,
    BST_DSPP_TP_PIC_AMT,
    BST_DSPP_TP_PIC_NUM,
    BST_DSPP_TP_CPL_VER,
    BST_DSPP_TP_PRMIMTV,
    BST_DSPP_TPA_HEAD_LEN
};

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/

typedef struct
{
    BST_DSPP_DVCID_T                    ucDeviceId;
    BST_DSPP_PKTSN_T                    usPktNum;
    BST_DSPP_PKTPC_T                    ucPicAmount;
    BST_DSPP_PKTPC_T                    ucPicNum;
    BST_DSPP_PRIMITIVE_ENUM_UINT8       enPrimitive;
    BST_DSPP_VERION_ENUM_UINT8          enCpVer;
    BST_UINT16                          usAmountLen;
    BST_UINT8                           aucReserved[2];
} BST_DSPP_TP_PKTMSG_STRU;

typedef struct
{
    NODE                                node;
    BST_OS_TIMERID_T                    ulTimerId;
    BST_DSPP_TP_PKTMSG_STRU             stRcvMng;
    LIST                                stPicList;
} BST_DSPP_TP_PACKET_STRU;

class BST_DSPP_CTrsDlVa :
    BST_PUBLIC BST_DSPP_CDlLayerBase, BST_PUBLIC BST_OS_CTimerCb
{
BST_PUBLIC:
    static BST_DSPP_CTrsDlVa   *GetInstance( BST_VOID );

    BST_VOID                    RxApi(
        BST_UINT8 const        *pucData,
        BST_UINT16              usLength );

BST_PRIVATE:
                                BST_DSPP_CTrsDlVa( BST_VOID );
                               ~BST_DSPP_CTrsDlVa( BST_VOID );
    BST_DSPP_CDlLayerBase      *GetNextStrategy(
        BST_DSPP_VERION_ENUM_UINT8    enNextVer );

    BST_DSPP_VERION_ENUM_UINT8  ParsePrimitive(
        BST_DSPP_HEAD_STRU         *const pstDsppHead,
        BST_DSPP_TP_PKTMSG_STRU    *pstPktPicMsg,
        BST_UINT8                  *pucSdu,
        BST_UINT16                  usSduLen );

    BST_DSPP_VERION_ENUM_UINT8  ProcRequest(
        BST_DSPP_HEAD_STRU         *const pstDsppHead,
        BST_DSPP_TP_PKTMSG_STRU    *pstPktPicMsg,
        BST_UINT8                  *pucSdu,
        BST_UINT16                  usSduLen );

    BST_ERR_ENUM_UINT8          UnpackInternal(
        BST_DSPP_HEAD_STRU         *const pstDsppHead,
        BST_DSPP_VERION_ENUM_UINT8 *const penNextVer );

    BST_DSPP_TP_PACKET_STRU *Joint(
        BST_DSPP_TP_PKTMSG_STRU    *pstPacketInfo,
        BST_UINT8 const            *pucData,
        BST_UINT16                 usInLen );

    BST_ERR_ENUM_UINT8      CheckPicNumber(
        BST_DSPP_TP_PACKET_STRU    *pstRcvPkt,
        BST_DSPP_PKTPC_T            usPicNum );

    BST_BOOL                CheckValidLength( BST_UINT16 usLen );

    BST_BOOL                CheckError(
        BST_UINT16          usCheckErrorCode,
        BST_UINT16          usLen,
        BST_UINT8 const    *pucData );

    BST_ERR_ENUM_UINT8      ParseHeadInfo(
        BST_DSPP_HEAD_STRU *const pstDsppHead,
        BST_UINT8 const    *pucData,
        BST_UINT16          usLen );

    BST_DSPP_TP_PACKET_STRU *CreatRcvManager(
        BST_DSPP_TP_PKTMSG_STRU    *pstPacketInfo );

    BST_DSPP_TP_PACKET_STRU *FindRcvInfo(
        BST_DSPP_PKTSN_T    usPktNum );

    BST_VOID                ClrRcvManager( BST_DSPP_PKTSN_T usPktNum );

    BST_ERR_ENUM_UINT8      GetPktPicInfo(
        BST_DSPP_TP_PKTMSG_STRU    *pstPacketInfo,
        BST_UINT8 const            *pucData,
        BST_UINT16                  usLen );

    BST_VOID                TimerExpired(
        BST_OS_TIMERID_T    ulId,
        BST_VOID           *pvPara );

    LIST                    m_stRcvPktList;
};

class BST_DSPP_CTrsUlVa : BST_PUBLIC BST_DSPP_CUlLayerBase
{
BST_PUBLIC:
    static BST_DSPP_CTrsUlVa *GetInstance( BST_VOID );

    BST_VOID                RxAck(
        BST_DSPP_PKTSN_T    usPktNum,
        BST_DSPP_PKTPC_T    usPicNum );

    BST_ERR_ENUM_UINT8      TxAck(
        BST_DSPP_TP_PKTMSG_STRU     *pstAckPktMsg );
BST_PROTECTED:
                            BST_DSPP_CTrsUlVa( BST_VOID );
                           ~BST_DSPP_CTrsUlVa( BST_VOID );
    BST_UINT16              BuildTpAHead(
        BST_DSPP_TP_PKTMSG_STRU      *pstPacketInfo,
        BST_UINT8                    *pucBuffer,
        BST_UINT16                    usSduLen );

    BST_ERR_ENUM_UINT8      SendPacket(
        BST_DSPP_HEAD_STRU           *const pstDsppHead,
        BST_DSPP_PRIMITIVE_ENUM_UINT8 enPrmvType );

    BST_ERR_ENUM_UINT8      SendMultiPacket (
        BST_DSPP_HEAD_STRU *const pstTxHeadInfo );


    BST_ERR_ENUM_UINT8      PackInternal(
        BST_DSPP_HEAD_STRU           *const pstDsppHead,
        BST_DSPP_VERION_ENUM_UINT8   *const pNextVer );

    BST_DSPP_CUlLayerBase  *GetNextStrategy(
        BST_DSPP_VERION_ENUM_UINT8    enNextVer );
BST_PRIVATE:
    BST_UINT16              TxApi(
        const BST_UINT8    *pucData,
        BST_UINT16          usLen );

    BST_UINT16              m_ReportPktNumSeq;
};

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif //TRANSFER_LAYER_H
