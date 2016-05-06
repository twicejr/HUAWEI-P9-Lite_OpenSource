/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_ha.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-12
*        Author: LY(57500)
*   Description: DHCP4R HA 头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-12  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP4R_HA_H_
#define _DHCP4R_HA_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 备份类型－保存在公共HA结构头的ucOperation字段 */
#define DHCP4R_HA_BATCH     0x1
#define DHCP4R_HA_REALTIME  0x2

/* 备份消息类型 －保存在DHCP4R模块备份消息头的usMsgType字段   */
/* 注: 增加消息类型时要同步更新 g_aulDhcp4rRtPackLen数组和 g_aszDhcp4rRtBakDbgInfo数组 */
enum enDhcp4rRtBak
{
    DHCP4R_HA_COMMON_CFG = 1,   /* 1, 公共配置信息实时备份     */
    DHCP4R_HA_RELAYENABLE,      /* 2, 使能去使能RELAY实时备份  */
    DHCP4R_HA_CFGSERVER,        /* 3, 配置中继地址实时备份     */
    DHCP4R_HA_CFG82,            /* 4, 配置82子选项实时备份     */

    DHCP4R_HA_VRFCOMCFG,        /* 5, VRF共有配置信息实时备份  */
    DHCP4R_HA_VRFRELAYENABLE,   /* 6, VRF使能/去使能RELAY实时备份 */
    DHCP4R_HA_VRFCFGSERVER,     /* 7, VRF配置server地址实时备份 */
    DHCP4R_HA_VRFCFG82,         /* 8, VRF配置82选项实时备份    */
    DHCP4R_HA_VRFCFG82MODE,        /* 9,配置82选项处理模式实时备份 */
};

/* DHCP4R模块备份消息头 */
typedef struct tagDHCP4RHeadBak
{
    USHORT usMsgType;   /* DHCP4R备份消息类型   */
    USHORT usMsgLen;    /* DHCP4R备份消息长度,不包含本消息头长度    */
}DHCP4R_HEAD_BAK_S;

/* DHCP4R模块公共配置批备份消息结构 */
typedef struct tagDHCP4RCommonCfgBak
{
    ULONG ulMaxHops;    /* 中继跳数 */
    ULONG ulFwdMode;    /* 中继方式 */
    UCHAR ucRelayTos;   /* RELAYTOS */
    UCHAR ucPad[3];
}DHCP4R_COMMON_CFG_BAK_S;

/* 使能去使能实时备份 */
typedef struct tagDHCP4RRelayEnableBak
{
    ULONG ulIfIndex;
    ULONG ulSetYes;
}DHCP4R_RELAY_ENABLE_BAK_S;

/* 配置中继地址实时备份 */
typedef struct tagDHCP4RCfgServerBak
{
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulServerIP;
}DHCP4R_CFG_SERVER_BAK_S;

/* 配置82子选项实时备份, 40字节 */
typedef struct tagDHCP4RCfgOption82Bak
{
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulSubCode;
    ULONG ulSubLen;
    UCHAR aucSubVar[DHCP4R_82_SUB_MAXLEN];
}DHCP4R_CFG_OPTION82_BAK_S;

/* 支持VRF的使能去使能实时备份 */
typedef struct tagDHCP4RVrfRelayBak
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
    ULONG ulSetYes;
}DHCP4R_VRF_RELAY_BAK_S;

/* 支持VRF的配置中继地址实时备份 */
typedef struct tagDHCP4RVrfCfgServerBak
{
    ULONG ulVrfIndex;
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulServerIP;
}DHCP4R_VRF_CFG_SERVER_BAK_S;

/* 支持VRF的配置82子选项实时备份 */
typedef struct tagDHCP4RVrfCfgOption82Bak
{
    ULONG ulVrfIndex;
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulSubCode;
    ULONG ulSubLen;
    UCHAR aucSubVar[DHCP4R_82_SUB_MAXLEN];
}DHCP4R_VRF_CFG_OPTION82_BAK_S;

/* 配置VRF共用实时备份 */
typedef struct tagDHCP4RVrfComBak
{
    ULONG ulVrfIndex;
    ULONG ulDHCP4RFwdMode;          /* 该实例中继方式 */
    ULONG ulDHCP4RMaxHops;          /* 该实例 最大RELAY跳数 */
    UCHAR ucDHCP4RTos;              /* 该实例TOS值 */
    UCHAR ucpad[3];
}DHCP4R_VRF_COM_BAK_S;

/* 配置82选项处理模式实时备份*/
typedef struct tagDHCP4RVrfCfgOpt82ModeBak
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
    ULONG ulOpt82Mode;
}DHCP4R_VRF_CFG_OPT82MODE_BAK_S;


/* DHCP4R HA设置HA公共报头 */
#define SET_HA_HEAD(pucData, ucHAMid, ucBakOperation, ulBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->usMsgLen = (USHORT)ulBakMsgLen;\
    pstHaHdr->ucModID = (UCHAR)ucHAMid;\
    pstHaHdr->ucOperation = (UCHAR)ucBakOperation;\
}

/* 设置DCHP4R HA内部模块报文 */
#define SET_DHCP4R_HA_HEAD(pstDhcp4rHeadBak, ulBakType, ulBakLen)\
{\
    (pstDhcp4rHeadBak)->usMsgType = (USHORT)(ulBakType);\
    (pstDhcp4rHeadBak)->usMsgLen  = (USHORT)(ulBakLen);\
}

/* HA调试信息输出宏 */
#define DHCP4R_DBG_OUTPUT(szInfo) TCPIP_DebugOutput(szInfo)

/* HA 头长度 + DHCP4R HA 头长度 */
#define DHCP4R_HA_HDR_LEN  (sizeof(HAMSGHEADER_S) + sizeof(DHCP4R_HEAD_BAK_S))

#define DHCP4R_HA_DBG_INFO_LEN     512

/* 将82子选项值按8字节一组打印到字符串数组中 */
#define DHCP4R_DBG_82SUB(aucSubVar, ulSubLen, i32Len, szDebugStr, i32DebugStrLen) \
{\
    ULONG j;\
    VOS_DBGASSERT(((ulSubLen) <= DHCP4R_82_SUB_MAXLEN) && ((ulSubLen) > 0));\
    for (j = 0; j < (ulSubLen); j++)\
    {\
        if (0 == (j % 8))\
        {\
            i32Len += TCPIP_SNPRINTF(szDebugStr + i32Len, i32DebugStrLen - i32Len, P0(" "));\
        }\
        if (((aucSubVar)[j] < 127) && ((aucSubVar)[j] > 32)) /* 可打印字符范围 */\
        {\
            i32Len += TCPIP_SNPRINTF(szDebugStr + i32Len, i32DebugStrLen - i32Len, P1("%c", (aucSubVar)[j]));\
        }\
        else\
        {\
            break; /* 显示82选项时如果遇到不可打印字符则不对后续字符进行显示 */\
        }\
    }\
}

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _DHCP4R_HA_H_ */

