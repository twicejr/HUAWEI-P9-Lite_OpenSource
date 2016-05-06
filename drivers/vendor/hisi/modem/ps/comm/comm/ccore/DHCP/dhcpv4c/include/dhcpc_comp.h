/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Dhcpc_comp.h
  版 本 号   : 初稿
  作    者   : y00138047
  生成日期   : 2012年5月15日
  最近修改   :
  功能描述   : dhcpc_comp.c 的头文件
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年5月15日
    作    者   : y00138047
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DHCPC_COMP_H__
#define __DHCPC_COMP_H__

extern PTM_COMPONENT_INFO_S g_stDhcpcComInfo;
#define DHCPC_SELF_CSI             g_stDhcpcComInfo.ullSelfCsi
#define DHCPC_SELF_SGID            g_stDhcpcComInfo.ullSelfSgId
#define DHCPC_SELF_CMPIDX          g_stDhcpcComInfo.ulSelfCmpIdx
#define DHCPC_SELF_CMPIDX_INSG     g_stDhcpcComInfo.ulSelfCmpIdxInSG

#define DHCPC_HANDLE         g_stDhcpcComInfo.ulHandle

/* 临时桩, 后续使用其它机制替换 */
#define DHCPC_GLAP2_CSI       g_stDhcpcComInfo.ullSelfCsi

extern ULONG ulDhcpcPerfInitFinish;

extern ULONG DHCPC_OmInitial(VOID);

#endif /* __DHCPC_COMP_H__ */
