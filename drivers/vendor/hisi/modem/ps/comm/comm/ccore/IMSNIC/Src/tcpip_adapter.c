/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_adapter.c
*
*  Project Code: VISPV100R005
*   Module Name: PUBLIC
*  Date Created: 2005-5-12
*        Author: zhang hong yan(19316)
*   Description: VISP适配代码文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2005-5-12  zhang hong yan(19316)  Creat the first version.
*  2006-4-27  wang xin(03278)        根据编程规范，对文件进行规范化整理
*  2006-5-10  X36317                 为支持ARM CPU字节对齐特性所做代码修改.
*  2006-5-22  X36317                 为消除PC-LINT告警而做的代码修改.
*  2006-6-20  X36317                 第二阶段代码质量改进.
*  2008-10-31  liangjicheng          V1R7C02发布
                                    增加新模块初始化
                                    1)DCLBase     2)OSPF       3)RIP
                                    4)IPOA        5)BFDEXT     6)RTP
                                    7)VLINK       8)VLAN
*  2008-11-10  liangjicheng        根据检视意见整理
*  2009-01-14  liangjicheng        非组件可剪裁模块初始化
*  2008-03-03  liangjicheng        BC3D01254 删除RTP模块
*
*******************************************************************************/

/*
一、可裁减特性适配说明
          适配目的：产品根据需求，自主决定对VISP各模块的裁减。
          适配函数列表：TCPIP_RegAllAppInfo:
                        不推荐直接修改该函数，具体请见tcpip_adapter.h中的说明.
                        TCPIP_GetMaxSockNum:
                        不允许产品修改,但由于允许用户更改Vtcpip_sock.h中的VRP_FD_SETSIZE宏，所以该函数必须作为外部函数.
                        VISP_InitTCPIPStack:
                        VISP的启动函数，产品可以修改此函数, 用来添加预配置处理、VISP钩子函数注册处理等.
*/

#ifdef  __cplusplus
extern "C" {
#endif

#include "product_config.h"

#if (FEATURE_ON == FEATURE_IMS)
#include "vos.h"
#include "PsLogdef.h"
#include "PsCommonDef.h"
#include "PsLib.h"
#include "PsTypeDef.h"

#include "tcpip/tcpip.h"
#include "tcpip_adapter.h"
#include "tcpip/public/tcpip_pub.h"
#include "tcpip/public/tcpip_hdr.h"
#include "tcpip/public/tcpip_config.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/dnsc/include/dns_api.h"

/*****************************************************************************
  2 宏
*****************************************************************************/
#define TCPIP_MAXSOCKTNUM           (50)

/* BFD NP模式设置，在启动协议栈之前设置 */
ULONG g_ulVttBfdNpMode = 0;

extern TCPIP_ADDR_HOOK_S stAddrHook;
extern TCPIP_LOG_HOOK_FUNC stLogHook;
extern gpfTCPIPInfoOutput  pFnInfoHook;
extern gpfTCPIPDebugOutput pFnDebugHook;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*lint -save -e960 */
/****************************************************************************
*    Func Name: TCPIP_RegAllAppInfo()
* Date Created: 2004-7-7
*       Author: zhany hong yan(19316)
*  Description: VISP 组件注册函数
*       Output: 无
*       Return: 无
*      Caution: 建议用户不要直接修改本函数。
*               若要进行组件裁减，请修改上面的组件注册宏。
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7  zhany hong yan(19316)         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_RegAllAppInfo()
{
    ULONG ulErrCode = 0;

    /*初始化组件管理*/
#if(TCPIP_COMP_INITIAL == VRP_YES)
    {
        extern ULONG COMP_Init(VOID);
        if (COMP_Init())
        {
            (VOID)vos_printf("\n\rcomponent initial error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_ETH == VRP_YES)
    {
        extern ULONG ETHARP_RegApp(VOID);
        ulErrCode = ETHARP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_PPP == VRP_YES)
    {
        extern ULONG PPP_RegApp(VOID);
        ulErrCode = PPP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    {
        extern ULONG IP_PP4_RegApp(VOID);
        ulErrCode = IP_PP4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {
        extern ULONG IP_AM4_RegApp(VOID);
        ulErrCode = IP_AM4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {
        extern ULONG SFIB_RegApp(VOID);
        ulErrCode = SFIB_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    /*IPv6 Initialization (Should before IFNET).*/
#if(TCPIP_COMP_REGISTER_IPV6 == VRP_YES)
    {
        extern ULONG IP6_SOCK6_RegApp(VOID);
        ulErrCode = IP6_SOCK6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* IPv6 Potocol Processing Manager */
        extern ULONG IPv6_PPMNG_RegApp(VOID);
        ulErrCode = IPv6_PPMNG_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* ICMPv6 */
        extern ULONG IPv6_ICMP6_RegApp(VOID);
        ulErrCode = IPv6_ICMP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* UDP6 */
        extern ULONG IPv6_UDP6_RegApp(VOID);
        ulErrCode = IPv6_UDP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* Rawip6 */
        extern ULONG IPv6_RAWIP6_RegApp(VOID);
        ulErrCode = IPv6_RAWIP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    {   /* TCP6 */
        extern ULONG IPv6_TCP6_RegApp(VOID);
        ulErrCode = IPv6_TCP6_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

    /* 注册DHCP6C组件 */
#if (TCPIP_COMP_REGISTER_DHCP6C == VRP_YES)
    {
        extern ULONG DHCP6C_RegApp(VOID);

        ulErrCode = DHCP6C_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for DHCP6C");
        }
    }
#endif

    /* 注册DHCP6R组件 */
#if (TCPIP_COMP_REGISTER_DHCP6R == VRP_YES)
    {
        extern ULONG DHCP6R_RegApp(VOID);

        ulErrCode = DHCP6R_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for DHCP6R");
        }
    }
#endif

#endif /*TCPIP_COMP_REGISTER_IPV6*/

    {
        extern ULONG IP4_SOCK4_RegApp(VOID);
        ulErrCode = IP4_SOCK4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if (TCPIP_COMP_REGISTER_TCP4 == VRP_YES)
    {
        extern ULONG IP4_TCP4_SH_RegApp(VOID);
        ulErrCode = IP4_TCP4_SH_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    {
        extern ULONG IP4_RIP4_RegApp(VOID);
        ulErrCode = IP4_RIP4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if (TCPIP_COMP_REGISTER_UDP4 == VRP_YES)
    {
        extern ULONG IP4_UDP4_RegApp(VOID);
        ulErrCode = IP4_UDP4_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    {
        extern ULONG IP_ICMP_RegApp(VOID);
        ulErrCode = IP_ICMP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if (TCPIP_COMP_REGISTER_OAM3AH == VRP_YES)
        {
            extern ULONG OAM_3AH_RegApp(VOID);
            ulErrCode = OAM_3AH_RegApp();
            if (VOS_OK != ulErrCode)
            {
                (VOID)vos_printf("\n\rcomponent register error");
            }
        }
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#if(TCPIP_COMP_REGISTER_VRF == VRP_YES)
    {
        extern ULONG VRF_Sh_RegApp(VOID);
        ulErrCode = VRF_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (void)vos_printf("\n\rcomponent register error");
        }
    }
#endif
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* Begin:VISP1.7C03 VRF6 */
#if(TCPIP_COMP_REGISTER_VRF6 == VRP_YES)
    {
        extern ULONG VRF6_Sh_RegApp(VOID);
        ulErrCode = VRF6_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (void)vos_printf("\n\rcomponent register error");
        }
    }
#endif
/* End: VISP1.7C03 VRF6 */
    {
        extern ULONG IF_Sh_RegApp(VOID);
        ulErrCode = IF_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }

#if(TCPIP_COMP_REGISTER_PING == VRP_YES)
    {
        extern ULONG PING_RegApp(VOID);
        ulErrCode = PING_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_DNSC == VRP_YES)
    {
        extern ULONG DNSC_RegApp(VOID);
        ulErrCode = DNSC_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_DHCP4C == VRP_YES)
    {
        extern ULONG DHCP4C_RegApp(VOID);
        ulErrCode = DHCP4C_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_ACL4 == VRP_YES)
    {
        extern ULONG ACL_SH_Init(VOID);

        ulErrCode = ACL_SH_Init();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rFire wall Initialize Error");
        }
    }
#endif


#if(TCPIP_COMP_REGISTER_ACL6 == VRP_YES)
    {
        extern ULONG ACL6_SH_Init(VOID);

        ulErrCode = ACL6_SH_Init();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rACL6 Initialize Error");
        }
    }
#endif



#if(TCPIP_COMP_REGISTER_TRACEROUTE == VRP_YES)
    {
        extern ULONG TRACERT_RegApp(VOID);
        ulErrCode = TRACERT_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_IPHC == VRP_YES)
    {
        extern ULONG IPHC_RegApp(VOID);
        ulErrCode = IPHC_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_PPPOECLIENT == VRP_YES)
    {
        extern ULONG PPPOE_Client_RegApp(VOID);
        ulErrCode = PPPOE_Client_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_MP == VRP_YES)
    {
        extern ULONG MP_RegApp(VOID);
        ulErrCode = MP_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /* 注册PPPMUX组件 */
#if (TCPIP_COMP_REGISTER_PPPMUX == VRP_YES)
    {
        extern ULONG PPPMUX_RegApp(VOID);
        ulErrCode = PPPMUX_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /*注册NSR组件特性*/
#if (TCPIP_COMP_REGISTER_NSR == VRP_YES)
    {
        extern ULONG NSR_RegApp(VOID);
        ulErrCode = NSR_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rNSR component register error");
        }
    }
#endif

    /* 注册TRUNK组件 */
#if (TCPIP_COMP_REGISTER_TRUNK == VRP_YES)
    {
        extern ULONG TRUNK_RegApp(VOID);
        ulErrCode = TRUNK_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

    /* 注册DHCP4 Relay组件 */
#if(TCPIP_COMP_REGISTER_DHCP4R == VRP_YES)
    {
        extern ULONG DHCP4R_RegApp(VOID);
        ulErrCode = DHCP4R_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rDHCP4R register error");
        }
    }
#endif

    /* 注册PPPoE Server组件 */
#if (TCPIP_COMP_REGISTER_POES == VRP_YES)
    {
        extern ULONG POES_RegApp(VOID);
        ulErrCode = POES_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rPOES_RegApp component register error");
        }
        (VOID)vos_printf("\n\rPOES_RegApp component register enter");
    }
#endif

    /* 注册IPSec组件 */
#if (TCPIP_COMP_REGISTER_IPSEC == VRP_YES)
    {
        extern ULONG IPSEC_RegApp(VOID);
#if (TCPIP_COMP_REGISTER_IPSEC6 == VRP_YES)
        extern VOID TCPIP_IPSEC_IPv6_RegisterToComn(VOID);

        /* Initialize IPSEC6 registration function */
        TCPIP_IPSEC_IPv6_RegisterToComn();

#endif
        ulErrCode = IPSEC_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error for IPSEC");
        }

    }
#endif


#if (TCPIP_COMP_REGISTER_OSICP == VRP_YES)
    {
        extern ULONG OSICP_RegApp(VOID);
        ulErrCode = OSICP_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if (TCPIP_COMP_REGISTER_OAM1AG == VRP_YES)
    {
        extern ULONG OAM_1AG_RegApp(VOID);
        ulErrCode = OAM_1AG_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

#if (TCPIP_COMP_REGISTER_IGMP == VRP_YES)
    {
        extern ULONG IGMP_RegApp(VOID);
        ulErrCode = IGMP_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rcomponent register error");
        }
    }
#endif

/* IPOA Init should after am4 */
/*Begin BC3D01674 【IPOA】ATM接口shutdown后操作undoshudown，不能正常UP 09-07-15 l00147446*/
#if(TCPIP_COMP_REGISTER_IPOA == VRP_YES)
            {
                extern VOID IPoA_Init( VOID );
                (VOID)IPoA_Init();
            }
#endif
/*End BC3D01674 【IPOA】ATM接口shutdown后操作undoshudown，不能正常UP 09-07-15 l00147446*/

#if(TCPIP_COMP_REGISTER_VLAN == VRP_YES)
            {
                extern ULONG ETHVLAN_SH_Init(VOID);
                ulErrCode = ETHVLAN_SH_Init();
                if(VOS_OK != ulErrCode)
                {
                    (VOID)vos_printf("\n\rVlan init error");
                }
            }
#endif

/*添加DCLBASE */
#if(TCPIP_COMP_REGISTER_DCLBASE == VRP_YES)
                {
                    extern ULONG dclbase_init(VOID);
                    ulErrCode = dclbase_init();
                    if(VOS_OK != ulErrCode)
                    {
                        (VOID)vos_printf("\n\rDCLBase init error");
                    }
                }

/*添加RIP */
#if(TCPIP_COMP_REGISTER_RIP == VRP_YES)
                {
                    extern ULONG RIP_Global_Init(VOID);
                    ulErrCode = RIP_Global_Init();
                    if(VOS_OK != ulErrCode)
                    {
                        (VOID)vos_printf("\n\rRIP init error");
                    }
                }
#endif
/*添加OSPF */
#if(TCPIP_COMP_REGISTER_OSPF == VRP_YES)
                {
                    extern ULONG ospf_vrpadp_init(VOID);
                    ulErrCode = ospf_vrpadp_init();
                    if(VOS_OK != ulErrCode)
                    {
                        (VOID)vos_printf("\n\rOSPF init error");
                    }
                }

/*OSPF NSR依赖NSR特性是否被裁减，如果NSR被裁减，OSPF NSR也不生效*/
#if (TCPIP_COMP_REGISTER_NSR == VRP_YES)
  {
      /*Added by guojianjun178934, 【检视发现问题】消除PCLint告警和Coverity告警, 2013/11/13   问题单号:DTS2013111304976 */
      extern VOID NSR_OSPF_Adapt_Init(VOID);
      NSR_OSPF_Adapt_Init();
      /* End of Added by guojianjun178934, 2013/11/13   问题单号:DTS2013111304976 */
  }
#endif

#endif

#endif

#if(TCPIP_COMP_REGISTER_VLINK == VRP_YES)
                {
                    extern VOID VLINK_Module_Init(VOID);
                    VLINK_Module_Init();
                }
#endif

#if (TCPIP_COMP_REGISTER_L2IF == VRP_YES)
    {
        extern ULONG L2IF_RegApp(VOID);
        ulErrCode = L2IF_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rl2if component register error");
        }
    }
#endif

#if (TCPIP_COMP_REGISTER_VRRP == VRP_YES)
    {
        extern ULONG VRRP_RegApp(VOID);
        ulErrCode = VRRP_RegApp();
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rVRRP component register error");
        }
#if (TCPIP_COMP_REGISTER_BFD == VRP_YES)
        /* 如果要支持基于BFD的监听功能,要求VRRP模块的组件注册必须在BFD的初始化之前完成 */
        {
            extern VRRP_GETBFDSESSIONSTATE g_pfVrrpTrackBfdGetSessionState;
            extern ULONG BFD_GetSessionState(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

            g_pfVrrpTrackBfdGetSessionState = BFD_GetSessionState;
        }
#endif
    }
#endif

#if (TCPIP_COMP_REGISTER_SYNCE == VRP_YES)
        {
            extern ULONG SyncE_RegApp(VOID);
            ulErrCode = SyncE_RegApp();
            if (VOS_OK != ulErrCode)
            {
                (VOID)vos_printf("\n\SyncE component register error");
            }
        }
#endif

#if(TCPIP_COMP_REGISTER_POLICYRT == VRP_YES)
    {    /* CHANDRA */
        extern ULONG PolicyRt_Sh_RegApp(VOID);

        ulErrCode = PolicyRt_Sh_RegApp();
        if(VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\n\rPolicyRt component register Error");
        }
    }
#endif

    return;
}

/****************************************************************************
*    Func Name: TCPIP_RegAllAppInfo()
* Date Created: 2004-7-7
*       Author: liangjicheng
*  Description: VISP 可裁减模块(非组件)初始化
                VISP内部一些模块是组件化，可以在注册后(TCPIP_RegAllAppInfo)
                由Entry完成相关初始化。
                V1R7C02部门模块没有组件化，但仍然支持裁减。这些模块初始化必须
                以来某些模块的初始化，因此建立此接口完成这类模块的剪裁初始化
*       Output: 无
*       Return: 无
*       Call  : VISP_InitTCPIPStack
*      Caution: Call After TCPIP_SystemEntry
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-1-14  liangjicheng      Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_InitNonComponentModule(VOID)
{
    ULONG ulRet = VOS_OK;

        /* BFD特性初始化,这里用户需要根据是否支持NP输入不同的参数
         * 0-不支持NP
         * 1-支持弱NP:NP发送软件接收
         * 2-支持全NP:NP发送NP接收
         */
#if (TCPIP_COMP_REGISTER_BFD == VRP_YES)
    {
        extern ULONG BFD_Shell_Init(ULONG ulNpMode);
        /* 如果支持NP的话,需要在调用初始化函数之间或者之后注册NP通知函数
         * (调用函数BFD_PPI_HookRegister注册)
         * 不能放在较远地方,不得随意在初始化之后很久建立会话等时候随意注册
         * 违者后果自负 */
        ulRet = BFD_Shell_Init(0);
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rBfd Init Error");
        }

#if (TCPIP_COMP_REGISTER_TRUNK == VRP_YES)
        {
            extern ULONG (*g_pfTrunkPortChangeNotifyBfd)(ULONG, ULONG);
            extern ULONG BFD_TrunkPortEventNotify(ULONG ulPortEvent, ULONG ulPortIfIndex);

            g_pfTrunkPortChangeNotifyBfd = BFD_TrunkPortEventNotify;
        }
#endif
#if (TCPIP_COMP_REGISTER_BFDEXT == VRP_YES)
        {
            extern ULONG Extern_BFD_Shell_Init(VOID);
            ulRet = Extern_BFD_Shell_Init();
            if (VOS_OK != ulRet)
            {
                (VOID)vos_printf("\n\rBfd EXT Init Error");
            }
        }
#endif
    }
#endif

#if((TCPIP_COMP_REGISTER_ACL4 == VRP_YES)\
        && (TCPIP_COMP_REGISTER_ACLFW == VRP_YES))
    {
        extern ULONG ACLFW_Init(ULONG ulRegPri);
        ulRet = ACLFW_Init(3);

        if (ulRet != VOS_OK)
        {
            (VOID)vos_printf("\n\r ACLFW Init Error(%#x)", ulRet);
            return ulRet;
        }
    }
#endif

/* mstp的shell初始化依赖于二层管理模块,所以要求必须在VISP TCPIP_SystemEntry初始化之后调用 */
#if (TCPIP_COMP_REGISTER_MSTP == VRP_YES)
    {
        extern ULONG MSTP_Shell_Init(VOID);
        ulRet = MSTP_Shell_Init();
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rMSTP Init Error(%#x)", ulRet);
            return ulRet;
        }
    }
#endif

/* EAP模块初始化, 必须在IFNET模块初始化之后 */
#if (TCPIP_COMP_REGISTER_EAP == VRP_YES)
    {
        extern LONG IPSI_EAP_shellInit(VOID);
        ulRet = IPSI_EAP_shellInit();
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rEAP Init Error(%#x)", ulRet);
            return ulRet;
        }
    }
#endif

#if(TCPIP_COMP_REGISTER_ETH == VRP_YES)
    {
#if(TCPIP_COMP_REGISTER_ARPGUARD == VRP_YES)
        {
            extern ULONG ARP_Guard_Init(VOID);
            ulRet = ARP_Guard_Init();
            if(VOS_OK != ulRet)
            {
                (VOID)vos_printf("\n\rcomponent register error");
                return ulRet;
            }
        }
#endif
    }
#endif

#if (TCPIP_COMP_REGISTER_LLDP == VRP_YES)
    {
        extern ULONG LLDP_Shell_Init(VOID);
        ulRet = LLDP_Shell_Init();
        if (VOS_OK != ulRet)
        {
            (VOID)vos_printf("\n\rLLDP Init Error");
            return ulRet;
        }
    }
#endif

    return ulRet;
}

/****************************************************************************
*    Func Name: TCPIP_GetMaxSockNum()
* Date Created: 2004-7-7
*       Author: zhany hong yan(19316)
*  Description: 获取产品配置的最大Socket数
*       Output: 无
*       Return: 配置的最大Socket数
*      Caution: 产品不可修改此函数。
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7  zhany hong yan(19316)         Creat the first version.
*  2006-6-16 X36317                        修改对用户配置的VRP_FD_SETSIZE合法性检查.
*
*******************************************************************************/
ULONG TCPIP_GetMaxSockNum(VOID)
{
    ULONG ulValue = TCPIP_MAXSOCKTNUM;

    /*lint -e774*/
    /*如果用户配置的VRP_FD_SETSIZE值不是32的整数倍，则取默认值32*/
    if ((ulValue & 0x0000001f) || (ulValue > VRP_FD_SETSIZE))
    {
        ulValue = 32; /*注:#define EXPANDNUM 32*/
    }
    /*lint +e774*/

    return ulValue;
}

/****************************************************************************
*    Func Name: VISP_InitTCPIPStack()
* Date Created: 2004-7-7
*       Author: zhany hong yan(19316)
*  Description: VISP协议栈初始化函数
*       Output: 无
*       Return: VOS_ERR:失败
*               0:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7  zhany hong yan(19316)         Creat the first version.
*  2008-10-31  liangjicheng                 修改启动说明
*
*******************************************************************************/
ULONG VISP_InitTCPIPStack(VOID)
{
    (VOID)vos_printf("\r\nDOPRA IP Version: %s", DOPRA_VISP_VERSION);
    (VOID)vos_printf("\r\nDOPRA IP HA Tag: %s", TCPIP_HA_VERSION);
    /***********************************************************************************
    Step1：
    根据产品需要，修改文件顶部的组件裁减配置宏，
    假若要裁减某组件，只要将对应的宏定义声明为VRP_NO。
    请参考<VRPV500R002 VISP二期项目协议栈可维护可裁减特性应用指导书.doc>
    ************************************************************************************/

    /***********************************************************************************
    Step2：
    根据产品需要，注册相关模块的Hook函数。
    ************************************************************************************/
    /* 把打印输出到串口 */
    TCPIP_OutputToCOM(0);

    /***********************************************************************************
    Step2：
    根据产品需要，设置VISP预配置参数 。若不设置则采用默认值。
    具体说明请参考<VRPV500R002 VISP二期项目参数预配置指导书.doc>
    ************************************************************************************/
    /*TCPIP_Set_PreConfigPara(SFIB4_CFG_ROUTE_BALANCE, xxx);*/   /*配置平衡路由模式*/
    /*TCPIP_Set_PreConfigPara(TCP4_CFG_NEED_CACHE, xxx);    */   /*配置TCP是否缓存下一跳和出接口信息*/
    /*TCPIP_Set_PreConfigPara(SKT_TASK_SOCK_PRIO, xxx);     */   /*配置VISP SockRun任务优先级*/
    /*TCPIP_Set_PreConfigPara(xxx, xxx);                    */   /*其他*/
    /*消除VISP外部构建PC-Lint告警 l48923 2006-05-10*/
    (VOID)TCPIP_Set_PreConfigPara(SKT_TASK_SOCK_PRIO, 175);   /*配置VISP SockRun任务优先级与SYSPRI相同,为175*/

    (VOID)TCPIP_Set_PreConfigPara(PTP_IPV6_ENABLE, 1);
    (VOID)TCPIP_Set_PreConfigPara(SYNCE_DEFAULT_QL, 8); /*默认值SSU-B*/

    /*Added by guojianjun178934, 【检视发现问题】消除PCLint告警和Coverity告警, 2013/11/25   问题单号:DTS2013111304976 */
    /*取消NSR相关预配置宏,但定义暂时保留*/
#if 0
    /*预配置使能NSR(OSPF NSR)*/
    (VOID)TCPIP_Set_PreConfigPara(NSR_ENABLE, 1);
    (VOID)TCPIP_Set_PreConfigPara(NSR_OSPF_ENABLE, 1);
#endif
    /* End of Added by guojianjun178934, 2013/11/25   问题单号:DTS2013111304976 */

    /* VISP提供预配置，允许配置32位掩码地址只产生一条主机路由用于报文接收 */
    (VOID)TCPIP_Set_PreConfigPara(IPV4_ADDR_SUPPORT_32BITS_MASK_SWITCH, 1);

    /* VISP提供与配置，关闭DAD探测 */
    (VOID)TCPIP_Set_PreConfigPara(IPV6_ND_NO_DAD_SWITCH, 1);

    /* VISP提供与配置，关闭报文缓存功能 */
    (VOID)TCPIP_Set_PreConfigPara(TCPIP_ENABLE_CACHEDPKT, 0);

    /* VISP提供与配置，TCP重组的最大段数目2048 */
    (VOID)TCPIP_Set_PreConfigPara(TCP_REASS_MAXSEG, 2048);

    (VOID)TCPIP_RegAddrHook(&stAddrHook);

    /* 注册给协议栈打印信息输出 */
    (VOS_VOID)TCPIP_RegFuncInfoOutputHook(pFnInfoHook);
    (VOS_VOID)TCPIP_RegFuncDebugOutputHook(pFnDebugHook);
    (VOS_VOID)TCPIP_RegFuncLogOutputHook(&stLogHook);

    /***********************************************************************************
    Step3：
    启动VISP协议栈。
    ***********************************************************************************/
    /*消除VISP外部构建PC-Lint告警 l48923 2006-05-10*/
    if (TCPIP_SystemEntry() != VOS_OK)
    {
        return VOS_ERR;
    }

    /*初始化一些可剪裁的非组件模块-After System Init*/
    if (TCPIP_InitNonComponentModule() != VOS_OK)
    {
        return VOS_ERR;
    }

    /* 其他产品定制，balong不需要 */
    /*
    if (TCPIP_HDR_Init(0,0) != VOS_OK)
    {
        (VOID)vos_printf("init the health failed!!");
        return VOS_ERR;
    }*/

    /* PTP协议初始化时创建了socket，依赖VISP主模块初始化成功 */
#if (TCPIP_COMP_REGISTER_PTP == VRP_YES)
    {
        ULONG ulErrCode;
        extern ULONG PTP_Shell_Init(ULONG ulFlag);

        ulErrCode = PTP_Shell_Init(1); /*创建event消息socket*/
        if (VOS_OK != ulErrCode)
        {
            (VOID)vos_printf("\r\nComponent(PTP) register error: %u",ulErrCode);
            return VOS_ERR;
        }
    }
#endif

    /* VISP提供配置支持DNS带下划线 */
    (VOID)TCPIP_SetDnsCompatibleSwitch(1);

    /* Balong定制，VISP内部使用RTOSck绝对时钟判断定时器是否超时，避免因低功耗导致软定时不准问题 */
    (VOID)TCPIP_SetTcpPrecisionSwitch(1);

    /* VISP提供与配置，不支持广播PING报文 */
    (VOID)TCPIP_SetIcmpAttackGuardSwitch(ICMP_ATTACKGUARD_SWITCH_DSTBCASTORMCAST);

    /***********************************************************************************
    以上三步完成了VISP协议栈的初始化(包括创建环回接口)。
    ETH/PPP接口需产品在需要时动态创建。
    ***********************************************************************************/
    return 0;
}

/*******************************************************************************
*    Func Name: TCPIP_ProductLock
* Date Created: 2009-2-20
*       Author: luoagaowei
*  Description: 产品自行实现的锁 For SGSN Only
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-2-20  luoagaowei         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ProductLock(VOID)
{
    return;
}

/*******************************************************************************
*    Func Name: TCPIP_ProductUnLock
* Date Created: 2009-2-20
*       Author: luoagaowei
*  Description: 产品自行实现的锁 For SGSN Only
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-2-20  luoagaowei         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ProductUnLock(VOID)
{
    return;
}

/*lint -restore */

/***************************************************************************************
*
* 上面各函数是产品必须适配的；
*
* 产品在具体应用VISP时，若需添加应用适配函数，请在以下添加，谢谢。
*
****************************************************************************************/

#endif

#ifdef  __cplusplus
}
#endif

