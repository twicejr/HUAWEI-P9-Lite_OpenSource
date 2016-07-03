

#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpm_interface.h"
#include "dhcpm_comp.h"
#include "dhcpm_dbg.h"


VOID DHCPM_AddDhcpServerGrpCallBack(CDB_TBLID nTblID, CDB_RECID nTupleID, UCHAR *pNewVal)
{
    LAP_DHCP_CFG_S *pstDhcpServerGrpInfo = NULL;
    ULONG ulRet = 0;

    DHCPM_ADD_COUNTER(15);

    /*入参检查*/
    if (NULL == pNewVal)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(265);
        return;
    }

    /*表号不是M_LAP_DHCP_TBL_ID*/
    if (M_LAP_DHCP_TBL_ID != nTblID)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(266);
        return;
    }

    pstDhcpServerGrpInfo = (LAP_DHCP_CFG_S *)pNewVal;

    ulRet = DHCPM_ModDhcpServerGroupNode(pstDhcpServerGrpInfo);
    if(VOS_OK != ulRet)
    {
        DHCPM_ADD_COUNTER(267);
    }


    return;
}


VOID DHCPM_ModDhcpServerGrpCallBack(CDB_TBLID nTblID, CDB_RECID nTupleID, UCHAR *pNewVal)
{
    LONG lCmpRet = 0;
    ULONG ulServerIpCfgChg = VOS_FALSE;
    ULONG ulDhcpSvrGrpIndex = 0;
    LAP_DHCP_CFG_S *pstNewCfg = NULL;
    LAP_DHCP_CFG_S stOldCfg = {0};

    ULONG ulRet = VOS_OK;

    DHCPM_ADD_COUNTER(16);

    /*入参检查*/
    if (NULL == pNewVal)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(268);
        return;
    }

    /*表号不是M_LAP_DHCP_TBL_ID*/
    if (M_LAP_DHCP_TBL_ID != nTblID)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(269);
        return;
    }

    pstNewCfg = (LAP_DHCP_CFG_S *)pNewVal;

    ulDhcpSvrGrpIndex = pstNewCfg->usDhcpServerGrpIndex;
    ulRet = DHCPM_GetDhcpSrvCfgByIndex(ulDhcpSvrGrpIndex, &stOldCfg);
    if (VOS_OK != ulRet )
    {
        DHCPM_ADD_COUNTER(270);
    }

    lCmpRet = VOS_MemCmp(stOldCfg.aulPrimaryServerIp, pstNewCfg->aulPrimaryServerIp,
                        sizeof(ULONG) * LAP_IP_ULONG_NUM);
    if ((0 != lCmpRet) && (LAP_DHCP_SERVER_INVALID_IP != stOldCfg.aulPrimaryServerIp[0]))
    {
        /* 主服务器配置改变,需要恢复主服务器告警.此处设置状态,在下面恢复。 */
        (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulDhcpSvrGrpIndex, DHCP_SEVER_NORMAL);
        ulServerIpCfgChg = VOS_TRUE;
    }

    lCmpRet = VOS_MemCmp(stOldCfg.aulSecondaryServerIp, pstNewCfg->aulSecondaryServerIp,
                        sizeof(ULONG) * LAP_IP_ULONG_NUM);
    if ((0 != lCmpRet) && (LAP_DHCP_SERVER_INVALID_IP != stOldCfg.aulSecondaryServerIp[0]))
    {
        /* 备服务器配置改变,需要恢复备服务器告警. 此处设置状态,在下面恢复。*/
        (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulDhcpSvrGrpIndex, DHCP_SEVER_NORMAL);
        ulServerIpCfgChg = VOS_TRUE;
    }

    if (VOS_TRUE == ulServerIpCfgChg)
    {
        DHCPM_AlarmProcByDhcpServerIndex(ulDhcpSvrGrpIndex, VOS_FALSE);
    }

    ulRet = DHCPM_ModDhcpServerGroupNode(pstNewCfg);
    if(VOS_OK != ulRet)
    {
        DHCPM_ADD_COUNTER(271);
    }

    return;
}



VOID DHCPM_RemoveDhcpServerGrpCallBack(CDB_TBLID nTblID, CDB_RECID nTupleID, UCHAR *pNewVal)
{
    LAP_DHCP_CFG_S *pstDhcpServerGrpInfo = NULL;
    ULONG ulRet = VOS_OK;
    ULONG ulDhcpIndex = 0;

    DHCPM_ADD_COUNTER(17);

    /*入参检查*/
    if (NULL == pNewVal)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(272);
        return;
    }

    /*表号不是M_LAP_DHCP_TBL_ID*/
    if (M_LAP_DHCP_TBL_ID != nTblID)
    {
        VOS_Assert(0);
        DHCPM_ADD_COUNTER(273);
        return;
    }

    pstDhcpServerGrpInfo = (LAP_DHCP_CFG_S *)pNewVal;

    ulDhcpIndex = pstDhcpServerGrpInfo->usDhcpServerGrpIndex;

    ulRet = DHCPM_RemoveDhcpServerByIndex(ulDhcpIndex);
    if ( VOS_OK != ulRet )
    {
        DHCPM_ADD_COUNTER(274);
    }

    return;
}


VOID DHCPM_CDBRegCallBack()
{
    CDBRegCallBackCmd(M_LAP_DHCP_TBL_ID,
                      (CDB_CALLBACK_FUN)DHCPM_AddDhcpServerGrpCallBack,
                      DHCPM_SELF_CSI,
                      M_CDB_TABLE_FUN_TYPE_REC_APP,
                      M_GGSN_CARD_GSPU,
                      "DHCPM_AddDhcpServerGrpCallBack");

    CDBRegCallBackCmd(M_LAP_DHCP_TBL_ID,
                      (CDB_CALLBACK_FUN)DHCPM_ModDhcpServerGrpCallBack,
                      DHCPM_SELF_CSI,
                      M_CDB_TABLE_FUN_TYPE_REC_MOD,
                      M_GGSN_CARD_GSPU,
                      "DHCPM_ModDhcpServerGrpCallBack");

    CDBRegCallBackCmd(M_LAP_DHCP_TBL_ID,
                      (CDB_CALLBACK_FUN)DHCPM_RemoveDhcpServerGrpCallBack,
                      DHCPM_SELF_CSI,
                      M_CDB_TABLE_FUN_TYPE_REC_DEL,
                      M_GGSN_CARD_GSPU,
                      "DHCPM_RemoveDhcpServerGrpCallBack");

    return;
}

