

#ifndef _DHCP4C_INC_H_
#define _DHCP4C_INC_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "vos/vospubh/compbase.h"

struct tagDHCP4C_LEASE;
struct tagDHCP4C_OPTIONINFO;
struct tagDHCP4C_Statistic;

DECLARE_INTERFACE(IIF_IPV4_DHCP4C_ComIntFun)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG,pfDHCP4C_Enable)(ULONG ulIfIndex, ULONG ulFlag);
    METHOD_(ULONG,pfDHCP4C_Disable)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_SetDhcpcCiaddr)(ULONG ulIfIndex, ULONG ulCiaddr);
    METHOD_(ULONG,pfDHCP4C_SetDhcpcOptionsItem)(ULONG ulIfIndex, UCHAR ucCode, UCHAR ucLen, UCHAR *pucValue);
    METHOD_(ULONG,pfDHCP4C_Start)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_Stop)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_Renew)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_Release)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_NotifyIfChange)(ULONG ulIfIndex, ULONG ulEvent);
    METHOD_(ULONG,pfDHCP4C_SetAddressStatus)(ULONG ulIfIndex, ULONG ulTargetIPAddr);

    METHOD_(VOID, pfDHCP4C_ProcLeaseFromBak)(struct tagDHCP4C_LEASE *stDhcp4cLease);
    METHOD_(VOID,pfDHCP4C_FSM_Receive)(UINTPTR ulMsg [ 4 ]);
    METHOD_(VOID,pfDHCP4C_PKT_Decode)(UCHAR * pucUdpBuf, ULONG usUdpBufLen, USHORT usVlanInfo);
    METHOD_(ULONG,pfDHCP4C_HA_BatchBackup)();
    METHOD_(ULONG,pfDHCP4C_HA_Input)(UCHAR *pucInBuf, USHORT usDataLen);
    METHOD_(ULONG,pfDHCP4C_HA_Smooth)();
    METHOD_(VOID,pfDHCP4C_SetTaskId)(ULONG ulTask);
    METHOD_(VOID,pfDHCP4C_DeleteFromList)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_GetDhcpcOptionsInfo)(ULONG ulIfIndex, struct tagDHCP4C_OPTIONINFO *pstDhcpOptions);
    METHOD_(ULONG,pfDHCP4C_SetDefaultAddr)( ULONG ulIfIndex, ULONG ulIpAddr,ULONG ulSubnetMask);
    METHOD_(ULONG,pfDHCP4C_DelDefaultAddr)( ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_GetDefaultAddr)(ULONG ulIfIndex,ULONG *pulIpAddr,ULONG *pulSubnetMask);

    METHOD_(ULONG,pfDHCP4C_HA_Clean)();

    METHOD_(ULONG,pfDHCP4C_IsRecvUnicastBeforeCfgIP)(ULONG ulIfIndex);

    METHOD_(ULONG,pfDHCP4C_HA_VirtualCfgInput)(UCHAR *pucBuf, USHORT usDataLen);
    METHOD_(ULONG,pfDHCP4C_DelDefaultRouteToSfib4)(ULONG ulIfIndex,ULONG ulGateway);
    METHOD_(ULONG,pfDHCP4C_GetArpByIpAddr)(ULONG ulIfIndex);
    /*Add by x57575 for Nodeb CR BC3D02026*/
    METHOD_(ULONG,pfDHCP4C_GetSessionIfIndexByPkt)(UCHAR *pucUdpBuf, ULONG usUdpBufLen, ULONG *pulIfIndex);
    METHOD_(ULONG,pfDHCP4C_EnableRmt)(ULONG ulLoopbackIfIndex, ULONG ulOutIfIndex);
    METHOD_(ULONG,pfDHCP4C_StartRmt)(ULONG ulIfIndex, ULONG ulOutIfIndex);
    METHOD_(ULONG,pfDHCP4C_SetDHCPVlanScanning)(ULONG ulIfIndex, ULONG ulEnable, ULONG ulDelayTime);
    METHOD_(ULONG,pfDHCP4C_GetDHCPVlanScanning)(ULONG ulIfIndex, ULONG *pulEnable, ULONG *pulDelayTime);
    METHOD_(VOID,pfDHCP4C_ProcIfDeleted)(ULONG ulIfIndex);
    METHOD_(ULONG,pfDHCP4C_GetDhcp4cStatistic)(struct tagDHCP4C_Statistic *pstStat);
    METHOD_(ULONG,pfDHCP4C_ClrDhcp4cStatistic)();
};

#ifdef  __cplusplus
}
#endif

#endif

