/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Dhcpv4s_cfg.c
  版 本 号   : 初稿
  作    者   : 贾会东00142544
  生成日期   : 2010年03月29日
  最近修改   :
  功能描述   : dhcpv4s配置文件
  函数列表   :

  修改历史   :
  1.日    期   : 2010年03月29日
    作    者   : 贾会东00142544
    修改内容   : 创建文件

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_comp.h"
#include "dhcpv4s_dbgcmd.h"

/*****************************************************************************
     协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_CFG_C
/*lint +e767*/

/*==========================================================
 *  函数名称:              DHCPV4S_CDB_CfgAddNotify
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:       cdb配置回调添加
 *  输入参数:
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
VOID DHCPV4S_CDB_CfgAddNotify( CDB_TBLID  nTbl, CDB_RECID  nRecId,UCHAR*     pValue)
{
    /*如果参数非法*/
    if (M_SC_DHCPS_FUNCTION_TBL_ID != nTbl|| nRecId > 0|| NULL == pValue)
    {
        VOS_DBGASSERT(0);
        return;
    }

    g_ulDhcpServerSwitch = ((DHCPS_ENABLE_SWITCH_S*)pValue)->ulDhcpServerSwitch;

    return;
}

/*==========================================================
 *  函数名称:              DHCPV4S_CDB_CfgModNotify
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:      cdb配置回调修改
 *  输入参数:
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
VOID DHCPV4S_CDB_CfgModNotify( CDB_TBLID  nTbl, CDB_RECID  nRecId,UCHAR*  pNewValue, UCHAR*     pOldValue)
{
    /*如果参数非法*/
    if ( M_SC_DHCPS_FUNCTION_TBL_ID != nTbl|| nRecId > 0|| NULL == pNewValue|| NULL == pOldValue )
    {
        VOS_DBGASSERT(0);
        return;
    }

    g_ulDhcpServerSwitch = ((DHCPS_ENABLE_SWITCH_S*)pNewValue)->ulDhcpServerSwitch;

    return;
}

/*==========================================================
 *  函数名称:              DHCPV4S_CDB_ExpiredAddNotify
 *  初稿完成:              2009/03/17
 *  作    者       :          dongmingzhou 42828
 *  函数功能:      判断是否在sc线程上
 *  输入参数:
 *  输出参数:
 *  返回类型:              无
 *  其他说明:              无
 *  调用函数:
 *  主调函数:
 *=========================================================*/
VOID DHCPV4S_CDB_ExpiredAddNotify(    CDB_TBLID    nTbl,  CDB_RECID     nRecId,UCHAR*     pValue)
{
    USHORT usApnIndex = 0;
    DHCPS_EXPIRED_REC_S * pstDhcpServerExpired = NULL;

    /*如果参数非法*/
    if ( M_SC_DHCPS_EXPIRED_TBL_ID != nTbl|| NULL == pValue)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstDhcpServerExpired = (DHCPS_EXPIRED_REC_S*)pValue;
    usApnIndex = pstDhcpServerExpired->usApnIndex;

    if ( usApnIndex >= MAX_APN_NUM)
    {
        return;
    }

    VOS_MemCpy(&g_pstExpiredInfor[usApnIndex], pstDhcpServerExpired, sizeof(DHCPS_EXPIRED_REC_S));
    return;

}

VOID DHCPV4S_CDB_ExpiredModNotify( CDB_TBLID nTbl, CDB_RECID nRecId,UCHAR*pNewValue, UCHAR*pOldValue )
{
    USHORT usApnIndex = 0;
    DHCPS_EXPIRED_REC_S * pstDhcpServerExpired = NULL;

    /*如果参数非法*/
    if ( M_SC_DHCPS_EXPIRED_TBL_ID != nTbl || NULL == pNewValue  || NULL == pOldValue )
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstDhcpServerExpired = (DHCPS_EXPIRED_REC_S*)pNewValue;
    usApnIndex = pstDhcpServerExpired->usApnIndex;

    if ( usApnIndex >= MAX_APN_NUM)
    {
        return;
    }

    VOS_MemCpy(&g_pstExpiredInfor[usApnIndex], pstDhcpServerExpired, sizeof(DHCPS_EXPIRED_REC_S));

    return ;
}

VOID DHCPV4S_CDB_ExpiredDelNotify( CDB_TBLID  nTbl, CDB_RECID  nRecId,UCHAR*  pValue)
{
    USHORT usApnIndex = 0;
    DHCPS_EXPIRED_REC_S * pstDhcpServerExpired = NULL;

    /*如果参数非法*/
    if ( M_SC_DHCPS_EXPIRED_TBL_ID != nTbl || NULL == pValue)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstDhcpServerExpired = (DHCPS_EXPIRED_REC_S*)pValue;
    usApnIndex = pstDhcpServerExpired->usApnIndex;

    if ( usApnIndex >= MAX_APN_NUM)
    {
        return;
    }

    VOS_MemSet((VOID*)&g_pstExpiredInfor[usApnIndex], 0 , sizeof(DHCPS_EXPIRED_REC_S));/* 记录清零 */;

    g_pstExpiredInfor[usApnIndex].usApnIndex = usApnIndex;
    g_pstExpiredInfor[usApnIndex].usDay  = 1;
    g_pstExpiredInfor[usApnIndex].ucHour = 0;
    g_pstExpiredInfor[usApnIndex].ucMinute = 0;
    g_pstExpiredInfor[usApnIndex].usUnlimited = 0;
    return;

 }

VOID DHCPV4S_CDB_OptionAddNotify(    CDB_TBLID    nTbl,  CDB_RECID     nRecId,UCHAR*     pValue)
{
    DHCPS_CDB_RECORD_S * pstDhcpServerOption = NULL;
    DHCPS_CFG_OPTION_S stOption = {0};
    UCHAR ucCode = 0;

    /*如果参数非法*/
    if ( M_SC_DHCPS_EXPIRED_TBL_ID != nTbl|| NULL == pValue)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstDhcpServerOption = (DHCPS_CDB_RECORD_S*)pValue;
    ucCode = pstDhcpServerOption->ucCode;

    stOption.ucFlag = pstDhcpServerOption->ucType;
    stOption.ucLen = pstDhcpServerOption->ucLen;
    VOS_MemCpy(stOption.pcData, pstDhcpServerOption->aucData, DHCPS_OPTIONDATA_LEN);

    stOption.ucUsed = 1;

    VOS_MemCpy(&g_pstOption[ucCode], &stOption, sizeof(DHCPS_CFG_OPTION_S));
    return;

}

VOID DHCPV4S_CDB_OptionModNotify( CDB_TBLID nTbl, CDB_RECID nRecId,UCHAR*pNewValue, UCHAR*pOldValue )
{
    DHCPS_CDB_RECORD_S * pstDhcpServerOption = NULL;
    DHCPS_CFG_OPTION_S stOption = {0};
    UCHAR ucCode = 0;

    /*如果参数非法*/
    if ( M_SC_DHCPS_EXPIRED_TBL_ID != nTbl || NULL == pNewValue  || NULL == pOldValue )
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstDhcpServerOption = (DHCPS_CDB_RECORD_S*)pNewValue;
    ucCode = pstDhcpServerOption->ucCode;

    stOption.ucFlag = pstDhcpServerOption->ucType;
    stOption.ucLen = pstDhcpServerOption->ucLen;
    VOS_MemCpy(stOption.pcData, pstDhcpServerOption->aucData, DHCPS_OPTIONDATA_LEN);

    stOption.ucUsed = 1;
    VOS_MemCpy(&g_pstOption[ucCode], &stOption, sizeof(DHCPS_CFG_OPTION_S));

    return;
}

VOID DHCPV4S_CDB_OptionDelNotify( CDB_TBLID  nTbl, CDB_RECID  nRecId,UCHAR*  pValue)
{
    DHCPS_CDB_RECORD_S * pstDhcpServerOption = NULL;
    UCHAR ucCode = 0;

    /*如果参数非法*/
    if ( M_SC_DHCPS_EXPIRED_TBL_ID != nTbl || NULL == pValue)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstDhcpServerOption = (DHCPS_CDB_RECORD_S*)pValue;
    ucCode = pstDhcpServerOption->ucCode;

    VOS_MemSet((VOID*)&g_pstOption[ucCode], 0 , sizeof(DHCPS_CFG_OPTION_S));/* 记录清零 */;

    return;

 }


VOS_VOID DHCPS_V4_CallBackReg()
{
    /************************* DHCP SERVER ADD ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_FUNCTION_TBL_ID,
                                    (CDB_CALLBACK_FUN)DHCPV4S_CDB_CfgAddNotify,
                                    DHCPS_SELF_CSI,
                                    M_CDB_TABLE_FUN_TYPE_REC_APP,
                                    M_GGSN_CARD_GSPU,
                                    "DHCPV4S_CDB_CfgAddNotify");


    /************************* DHCP SERVER MOD ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_FUNCTION_TBL_ID,
                                    (CDB_CALLBACK_FUN)DHCPV4S_CDB_CfgModNotify,
                                    DHCPS_SELF_CSI,
                                    M_CDB_TABLE_FUN_TYPE_REC_MOD,
                                    M_GGSN_CARD_GSPU,
                                    "DHCPV4S_CDB_CfgModNotify");


    /************************* DHCP SERVER EXPIRED ADD ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_EXPIRED_TBL_ID,
                                  (CDB_CALLBACK_FUN)DHCPV4S_CDB_ExpiredAddNotify,
                                  DHCPS_SELF_CSI,
                                  M_CDB_TABLE_FUN_TYPE_REC_APP,
                                  M_GGSN_CARD_GSPU,
                                  "DHCPV4S_CDB_ExpiredAddNotify");

    /************************* DHCP SERVER EXPIRED MOD ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_EXPIRED_TBL_ID,
                                    (CDB_CALLBACK_FUN)DHCPV4S_CDB_ExpiredModNotify,
                                    DHCPS_SELF_CSI,
                                    M_CDB_TABLE_FUN_TYPE_REC_MOD,
                                    M_GGSN_CARD_GSPU,
                                    "DHCPV4S_CDB_ExpiredModNotify");

    /************************* DHCP SERVER EXPIRED DEL ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_EXPIRED_TBL_ID,
                                  (CDB_CALLBACK_FUN)DHCPV4S_CDB_ExpiredDelNotify,
                                  DHCPS_SELF_CSI,
                                  M_CDB_TABLE_FUN_TYPE_REC_DEL,
                                  M_GGSN_CARD_GSPU,
                                  "DHCPV4S_CDB_ExpiredDelNotify");

    /************************* DHCP SERVER OPTION ADD ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_OPTION_TBL_ID,
                                  (CDB_CALLBACK_FUN)DHCPV4S_CDB_OptionAddNotify,
                                  DHCPS_SELF_CSI,
                                  M_CDB_TABLE_FUN_TYPE_REC_APP,
                                  M_GGSN_CARD_GSPU,
                                  "DHCPV4S_CDB_OptionAddNotify");

    /************************* DHCP SERVER OPTION MOD ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_OPTION_TBL_ID,
                                    (CDB_CALLBACK_FUN)DHCPV4S_CDB_OptionModNotify,
                                    DHCPS_SELF_CSI,
                                    M_CDB_TABLE_FUN_TYPE_REC_MOD,
                                    M_GGSN_CARD_GSPU,
                                    "DHCPV4S_CDB_OptionModNotify");

    /************************* DHCP SERVER OPTION DEL ********************/
    CDBRegCallBackCmd(M_SC_DHCPS_OPTION_TBL_ID,
                                  (CDB_CALLBACK_FUN)DHCPV4S_CDB_OptionDelNotify,
                                  DHCPS_SELF_CSI,
                                  M_CDB_TABLE_FUN_TYPE_REC_DEL,
                                  M_GGSN_CARD_GSPU,
                                  "DHCPV4S_CDB_OptionDelNotify");

}



VOID DHCPV4S_GetDhcpServerConfig (VOID)
{
    ULONG ulRetCode;
    DHCPS_ENABLE_SWITCH_S stDhcpServercfg;

    VOS_MemSet(&stDhcpServercfg, 0, sizeof(DHCPS_ENABLE_SWITCH_S));

    ulRetCode = DBApiQueryDirect(M_SC_DHCPS_FUNCTION_TBL_ID, 0, (CHAR*)&stDhcpServercfg);

    if ( M_CFG_DB_API_SUCCESS == ulRetCode)
    {
        g_ulDhcpServerSwitch = stDhcpServercfg.ulDhcpServerSwitch;
    }
    else
    {
        g_ulDhcpServerSwitch = 0;
    }

    return;
}

VOID DHCPV4S_GetExpiredConfig(VOID)
{
    ULONG ulQueryId = 0;
    ULONG ulRetCode = 0;
    USHORT usApnIndex = 0;
    DHCPS_EXPIRED_REC_S stDhcpV4ServerExpired;

    VOS_MemSet(&stDhcpV4ServerExpired, 0 , sizeof(DHCPS_EXPIRED_REC_S));

    /* 查找CDB表中首条记录 */
    ulRetCode = DBApiQueryFirst(M_SC_DHCPS_EXPIRED_TBL_ID,
                                                    0,
                                                    NULL,
                                                    (CHAR*)&stDhcpV4ServerExpired,
                                                    &ulQueryId);

    if ( ulRetCode != M_CFG_DB_API_SUCCESS)
    {
        return ;
    }

    while ( ulRetCode == M_CFG_DB_API_SUCCESS)
    {
        usApnIndex = stDhcpV4ServerExpired.usApnIndex;
        if ( usApnIndex >= MAX_APN_NUM)
        {
            ulRetCode = DBApiQueryNext(&ulQueryId,(CHAR*)&stDhcpV4ServerExpired);
            continue;
        }

        VOS_MemCpy(&g_pstExpiredInfor[usApnIndex], &stDhcpV4ServerExpired, sizeof(DHCPS_EXPIRED_REC_S));

         VOS_MemSet(&stDhcpV4ServerExpired, 0 , sizeof(DHCPS_EXPIRED_REC_S));

         /* 查找CDB表中下条记录 */
        ulRetCode = DBApiQueryNext(&ulQueryId,(CHAR*)&stDhcpV4ServerExpired);
    }
    return ;

}

VOID DHCPV4S_GetOptionConfig(VOID)
{
    ULONG ulQueryId = 0;
    ULONG ulRetCode = 0;
    DHCPS_CDB_RECORD_S  stDhcpServerOption;
    UCHAR ucCode = 0;

    VOS_MemSet(&stDhcpServerOption, 0 , sizeof(DHCPS_CDB_RECORD_S));

    /* 查找CDB表中首条记录 */
    ulRetCode = DBApiQueryFirst(M_SC_DHCPS_OPTION_TBL_ID,
                                                    0,
                                                    NULL,
                                                    (CHAR*)&stDhcpServerOption,
                                                    &ulQueryId);

    if ( ulRetCode != M_CFG_DB_API_SUCCESS)
    {
        return ;
    }

    while ( ulRetCode == M_CFG_DB_API_SUCCESS)
    {
        ucCode = stDhcpServerOption.ucCode;
        VOS_MemCpy(&g_pstOption[ucCode], &stDhcpServerOption, sizeof(DHCPS_CFG_OPTION_S));
        g_pstOption[ucCode].ucUsed = 1;

        VOS_MemSet(&stDhcpServerOption, 0 , sizeof(DHCPS_CFG_OPTION_S));

         /* 查找CDB表中下条记录 */
        ulRetCode = DBApiQueryNext(&ulQueryId,(CHAR*)&stDhcpServerOption);
    }
    return ;

}

VOID DHCPS_GetConfig(VOID)
{
    DHCPV4S_GetDhcpServerConfig();
    DHCPV4S_GetExpiredConfig();
    DHCPV4S_GetOptionConfig();
    return;
}

