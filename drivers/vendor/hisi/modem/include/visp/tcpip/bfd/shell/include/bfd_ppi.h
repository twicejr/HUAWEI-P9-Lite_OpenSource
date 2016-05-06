/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ppi.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD SHELL
*  Date Created: 2006-12-11
*        Author: Wangchengyang
*   Description: NP特性可维护性函数定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-11      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_PPI_H_
#define _BFD_PPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PPI函数的返回值 */
enum tagBFDPPIRetValue
{
    BFD_PPI_OK,
    BFD_PPI_ERR
};

/* 宏定义 */
#define PPI_BFD                                    0        /* BFD PPI */

extern BFD_PPI_COUNT_S g_stBfdPpiCount;

typedef struct tagBFD_PPI_COM_S
{
    ULONG ulIpver;
    CHAR szCtlPkt[BFD_LEN_AUTH_NONE]; /* 会话的BFD控制报文,网络序,值为用户配置值 */

    ULONG ulDetectMode;             /* 本端实际的检测模式 */
    ULONG ulTxInterval;             /* 本端实际的发送时间间隔,ms */
    ULONG ulDetectInterval;         /* 本端实际的检测间隔,ms */
    ULONG ulDetectMult;             /* 本端实际的检测倍数 */
    ULONG ulMyDiscriminator;        /* 本端标识符 */
    ULONG ulYourDiscriminator;      /* 对端标识符 */

    ULONG ulDstIPAddress[4];        /* 对端地址,Big Endian */
    ULONG ulSrcIPAddress[4];        /* 本端地址,Big Endian */
    ULONG ulTTL;                    /* TTL */
    ULONG ulDstUdpPort;             /* UDP目的端口号,单跳为3784,多跳为4784 */
    ULONG ulSrcUdpPort;             /* UDP源端口号,值为49151+X(X>0) */
    ULONG ulTos;                    /* TOS值 */
    ULONG ulIfIndex;                /* 会话的出接口索引(多跳时为0) */
    ULONG ulVrfIndex;               /* 会话所在的VRF */
    ULONG ulIfType;                 /* 出接口类型, 取值见enumIFTYPE */
    ULONG ulIfNum;                  /* 出接口的通道号 */
    USHORT usReserved;              /* 保留不用 */
    USHORT usCksum;                 /* 整个PPI结构体的校验和 */
    ULONG ulSessionId;              /* 会话ID */
    ULONG ulDiagnostic;             /* 下发当前会话诊断字 */
}BFD_PPI_COM_S;

/* 函数声明 */

VOID BFD_PPI_LogMsg(ULONG ulRet, ULONG ulSesssionID, ULONG ulOprType, VOID *pData, ULONG ulVrfIndex,ULONG ulIpVer);
VOID BFD_PPI_Dump(ULONG ulSessionID, BFD_PPI_COM_S *pstPPIInfo);
ULONG BFD_GetComPpi(BFD_PPI_COM_S* pstPpiCom, BFD_PPI_S* pstBfdPpi, BFD6_PPI_S* pstBfd6Ppi);
ULONG BFD_GetPpiFromCom(BFD_PPI_COM_S* pstPpiCom, ULONG *pulIpVer,
                                    BFD_PPI_S* pstBfdPpi, BFD6_PPI_S* pstBfd6Ppi);
#ifdef __cplusplus
}
#endif

#endif /* end of _BFD_PPI_H_ */

