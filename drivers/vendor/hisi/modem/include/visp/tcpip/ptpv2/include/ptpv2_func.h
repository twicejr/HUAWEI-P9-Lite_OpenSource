/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_func.h
*
*  Project Code:
*   Module Name: PTPV2 func
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_FUNC_H_
#define _PTPV2_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 关闭socket */
#define PTPV2_CLOSE_SOCKET(iSocktId)\
    {\
        if (PTPV2_INVALID_SOCKEID != iSocktId)\
        {\
            (VOID)close(iSocktId);\
            iSocktId = PTPV2_INVALID_SOCKEID;\
        }\
    }

/*******************************************************************************
*    Func Name: PTPV2_TimerEventProc
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: PTPV2 定时器事件处理
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_TimerEventProc();

/*******************************************************************************
*    Func Name: PTPV2_RcvPacketEventProc
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: PTP 报文事件处理
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_RcvPacketEventProc();

/*******************************************************************************
*    Func Name: PTPV2_TaskMain
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ul1:
*               ULONG ul2:
*               ULONG ul3:
*               ULONG ul4:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);


/*******************************************************************************
*    Func Name: PTPV2_GetTaskPri
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UINTPTR *pulTaskPri:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GetTaskPri(UINTPTR *pulTaskPri);


/*******************************************************************************
*    Func Name: PTPV2_GlobalQueInfoUnInit
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GlobalQueInfoUnInit();

/*******************************************************************************
*    Func Name: PTPV2_GlobalTaskInfoInit
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: ULONG ulPtpClockType:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GlobalTaskInfoInit(ULONG ulPtpClockType);

/*******************************************************************************
*    Func Name: PTPV2_GlobalClockInfoInit
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GlobalClockInfoInit();

/*******************************************************************************
*    Func Name: PTPV2_Start
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: VOID* pThis:
*               VOID* pData:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_Start(VOID* pThis, VOID* pData);


ULONG PTPV2_BcStart(VOID* pThis, VOID* pData);

ULONG PTPV2_OcStart(VOID* pThis, VOID* pData);
/*******************************************************************************
*    Func Name: PTPV2_Stop
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: VOID* pThis:
*               VOID* pData:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_Stop(VOID* pThis, VOID* pData);

/******************************************************************************
*Func Name   : PTPV2_Gloabl_Init
*Description : 分配设备内存，并初始化
*Input       : ulPtpClockType: PTP模式
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
*  2014-03-03      luogaowei & dutianyi     create
*******************************************************************************/
ULONG PTPV2_Global_Init(ULONG ulPtpClockType);

/******************************************************************************
*Func Name   : PTPV2_Global_UnInit
*Description : 分配设备内存，并初始化
*Input       : ulPtpMode: PTP模式
*Output      : 
*Return      : 成功返回PTP_OK，失败返回错误码
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
*  2014-03-03      luogaowei & dutianyi     create
*******************************************************************************/
ULONG PTPV2_Global_Uninit();


ULONG PTPV2_GetPortInfo(TCPIP_PTP_ADDRINFO_S* pstAddrInfo,
                    PTPV2_PORT_S **ppstPtpPort);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_FUNC_h_   */
