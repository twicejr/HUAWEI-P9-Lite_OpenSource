/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_ha.h
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG模块HA部分
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_HA_H
#define _1AG_HA_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*操作类型*/
enum eOam1agOperate
{
    OAM_1AG_CREATE,
    OAM_1AG_DELETE,
    OAM_1AG_UPDATE
};

/*oam1ag 备份消息子类型*/
enum eOam1agBakType
{
    OAM_1AG_GLOBAL = 0x1000,
    OAM_1AG_MDINFO = 0x2000,
    OAM_1AG_MAINFO = 0x3000,
    OAM_1AG_MEPINFO = 0x4000,
    OAM_1AG_RMEPINFO = 0x5000,
    OAM_1AG_COMPATILE = 0x6000,
    /* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. 修改原因:  备份全局协议版本 */
    OAM_1AG_VERSION = 0x7000    
};

/*TLV 类型*/
enum eOam1agTlvType
{
    OAM_1AG_HAMDNAME,
    OAM_1AG_HAMANAME,
    OAM_1AG_HARMEPTLV,
    OAM_1AG_HAMEP1AGVERSIONTLV,
    OAM_1AG_HAMEPVLANFLAGTLV,
    OAM_1AG_HARMEPTLV2,
    OAM_1AG_HAMEPLOSSDETECTTLV,
    OAM_Y1731_HAMAAISENABLETLV,
     
};

/* 1AG 备份子消息公共头 */
typedef struct tagOAM1AG_HEAD_BAK
{
    USHORT usBakType;
    USHORT usBakLen;
}OAM1AG_HEAD_BAK_S;

/*MD名字TLV，MD名字长度可变*/
typedef struct tagOAM1AG_MDTLV_BAK
{
    USHORT usType;   /*报文类型*/
    USHORT usLength;  /*报文长度*/
    UCHAR  szMDName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD名字*/
}OAM1AG_MDTLV_BAK_S;

/*MA名字TLV，MD名字长度可变*/
typedef struct tagOAM1AG_MATLV_BAK
{
    USHORT usType;   /*报文类型*/
    USHORT usLength;  /*报文长度*/
    UCHAR  szMAName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA名字*/
}OAM1AG_MATLV_BAK_S;


/*备份报文优先级,基础数据区*/
typedef struct tagOAM1AG_PKTGLOBAL_BAK
{
    ULONG ulPktType;   /*报文类型*/
    UCHAR ucPktPriority;  /*报文优先级*/
    UCHAR ucRes[3];
}OAM1AG_PKTGLOBAL_BAK_S;

/*备份1ag协议兼容性全局数据TLV*/
typedef struct tagOAM1AG_COMPATIBLE_BAK
{
    ULONG ulCompatible;/*兼容性开关*/
}OAM1AG_COMPATIBLE_BAK_S;

/*备份MD,基础数据区*/
typedef struct tagOAM1AG_MD_BAK
{
    UCHAR ucMdLevel;    /*MD级别*/
    UCHAR ucRes[3];
}OAM1AG_MD_BAK_S;

/*备份MA,基础数据区*/
typedef struct tagOAM1AG_MA_BAK
{
    USHORT usVlanId ;    /*MA关联的VLAN ID值*/
    UCHAR  ucCcmInterval;/*CCM发送间隔*/
    UCHAR  ucCompatibleFlag;/*兼容标记,0-为标准模式,1-数通模式*/
    UCHAR  ucMaVlanPri;      /*基于MA的VLAN优先级*/
    UCHAR  ucRes[3];
}OAM1AG_MA_BAK_S;

typedef struct tagOAMY1731_MAAISENABLETLV_BAK
{
    USHORT usType;                /*TLV类型*/
    USHORT usLength;              /*TLV长度*/
    UCHAR  ucAisEnable;           /* 是否使能AIS功能标记 */
    UCHAR  ucRes[3];              /*保留字段*/
}OAMY1731_MAAISENABLETLV_BAK_S;

/* MA TLV备份字段 用于批备份 */
typedef struct tagOAM1AG_MATLV_DATA
{
    UCHAR  ucMaAisEnable;         /* 基于MA的AIS使能标记 */
    UCHAR  ucPadding[3];          /* 保留字段 */
}OAM1AG_MATLV_DATA_S;

/*备份MEP,基础数据区*/
typedef struct tagOAM1AG_MEP_BAK
{ 
    ULONG  ulIfIndex;      /*所属接口索引*/
    USHORT usMepId;        /*MEP ID*/
    UCHAR  ucCcSendEnable; /*是否使能CCM发送功能标记*/
    UCHAR  ucRes[1];
}OAM1AG_MEP_BAK_S;

/* MEP 1AG 版本信息备份TLV */
typedef struct tagOAM1AG_MEP1AGVERSIONTLV_BAK
{
    USHORT usType;                /*TLV类型*/
    USHORT usLength;              /*TLV长度*/
    UCHAR  uc1agVersion;          /*1AG版本信息*/
    UCHAR  ucRes[3];              /*保留字段*/
}OAM1AG_MEP1AGVERSIONTLV_BAK_S;

/* MEP VLAN FLAG备份TLV */
typedef struct tagOAM1AG_MEPVLANFLAGTLV_BAK
{
    USHORT usType;                /*TLV类型*/
    USHORT usLength;              /*TLV长度*/
    UCHAR  ucVlanFlag;            /*1AG VLAN FLAG*/
    UCHAR  ucRes[3];              /*保留字段*/
}OAM1AG_MEPVLANFLAGTLV_BAK_S;

/* MEP Loss Detect TLV备份字段 */
typedef struct tagOAM1AG_MEPLOSSDETECTTLV_BAK
{
    USHORT usType;                /*TLV类型*/
    USHORT usLength;              /*TLV长度*/
    USHORT usLossDetectTimer;     /*ccm lost detect timer*/
    UCHAR  ucRes[2];              /*保留字段*/
}OAM1AG_MEPLOSSDETECTTLV_BAK_S;

/* MEP TLV备份字段 */
typedef struct tagOAM1AG_MEPTLV_DATA
{
    UCHAR  uc1agVersion;          /*1AG版本信息*/
    UCHAR  ucVlanFlag;            /*1AG VLAN FLAG*/
    USHORT usLostDetect;          /*Loss检测时间*/
}OAM1AG_MEPTLV_DATA_S;


/*备份RMEP,基础数据区*/
typedef struct tagOAM1AG_RMEP_BAK
{
    ULONG  ulIfIndex;         /*RMEP出接口索引*/
    USHORT usRmepId;          /*RMEP ID值*/
    USHORT usRMepOutTimerSet; /*Rmep接收CCM的超时设置值*/
    UCHAR  ucRemoteIfFlag;    /*远端接口状态标记,同时也是告警标记*/
    UCHAR  ucCcLost;          /*ccm LOST告警标记*/
    UCHAR  aucMacAddress[OAM_1AG_MACADDR_LEN];  /*RMEP physical地址*/
    UCHAR  ucCcmInterval;     /*对端发送间隔*/
    UCHAR  ucRes[3];          /*保留*/
}OAM1AG_RMEP_BAK_S;

/* 增加RMEP的动静态标志,MD Level标志,是否下发过NP标志,以及超时时间和老化时间的备份,这些字段组织在一个TLV中 */
typedef struct tagOAM1AG_RMEPTLV_BAK
{
    USHORT usType;                /*TLV类型*/
    USHORT usLength;              /*TLV长度*/
    UCHAR  ucRMepStatic;          /*0表示动态生成的RMEP ，1表示静态创建的RMEP*/
    UCHAR  ucMdLevelFlag;         /*MD 级别,1-大于本级别,0-等于本级别*/ 
    UCHAR  ucDownloadNp;          /*置1为此RMEP下发过NP,创建和更新RMEP时备板使用主板备份过来的值,
                                    删除RMEP时,备板通过原有删除函数的流程进行是否下发NP删除的动作*/    
    UCHAR  ucRes;                 /*保留*/
    ULONG  ulRMepOldTimerSet;     /*Rmep超时后老化设置值*/
    ULONG  ulRMepOldTimerCount;   /*Rmep老化计数值*/    
    USHORT usRMepOutTimerCount;   /*Rmep接收CCM的超时计数值*/
    USHORT usRes;                 /*Rmep接收CCM的超时设置值已经在基础数据区中进行了备份,所以这里就不备份了*/
}OAM1AG_RMEPTLV_BAK_S;

/* 新增rmep信息备份tlv */
typedef struct tagOAM1AG_RMEPTLV2_BAK
{
    USHORT usType;                /*TLV类型*/
    USHORT usLength;              /*TLV长度*/
    UCHAR  ucVlanFlag;            /*收到CCM报文是否带有VLAN标记 0-不带VLAN，1-带VLAN */
    UCHAR  ucMdLevel;             /*保存remp MD级别(对端),静态RMEP在没有收到CCM之前保留为创建时所在的MD级别 */  
    UCHAR  ucRmepCheck;           /*未收到CCM前是否向NP下发RMEP，已使NP可以进行连通性检查*/
    UCHAR  ucRdiFlag;             /*记录是否已收到过带RDI的CCM,收到后MA内的接收RDI计算要增加*/
    ULONG  ulRes;                 /* 保留 */
}OAM1AG_RMEPTLV2_BAK_S;

/* 备板收到的RMEP相关备份信息.由TLV备份过来的RMEP信息统一记录在该结构中,该结构中的字段不一定都是由OAM1AG_RMEPTLV_BAK_S
   结构备份过来的字段. 也可以是由后续新增的TLV字段备份过来的RMEP相关信息.
*/
typedef struct OAM1AG_RMEPTLV_DATA
{
    UCHAR  ucRMepStatic;          /*0表示动态生成的RMEP ，1表示静态创建的RMEP*/
    UCHAR  ucMdLevelFlag;         /*MD 级别,1-大于本级别,0-等于本级别*/ 
    UCHAR  ucDownloadNp;          /*置1为此RMEP下发过NP*/    
    UCHAR  ucVlanFlag;            /*收到CCM报文是否带有VLAN标记 0-不带VLAN，1-带VLAN */
    ULONG  ulRMepOldTimerSet;     /*Rmep超时后老化设置值*/
    ULONG  ulRMepOldTimerCount;   /*Rmep老化计数值*/    
    USHORT usRMepOutTimerCount;   /*Rmep接收CCM的超时计数值*/
    UCHAR  ucMdLevel;             /*保存remp MD级别(对端),静态RMEP在没有收到CCM之前保留为创建时所在的MD级别 */  
    UCHAR  ucRmepCheck;           /*未收到CCM前是否向NP下发RMEP，已使NP可以进行连通性检查*/
    UCHAR  ucRdiFlag;             /*记录是否已收到过带RDI的CCM,收到后MA内的接收RDI计算要增加*/
    UCHAR  ucRes[3];
}OAM1AG_RMEPTLV_DATA_S;

/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. 修改原因: 备份全局协议版本 */
typedef struct tagOAM1AG_VERSION_BAK
{
    ULONG ulGlobalVersion;/* 全局协议版本 */
}OAM1AG_VERSION_BAK_S;


/* 各类备份子消息类型和长度所占的空间大小 */
#define OAM1AG_HEADBAK_LEN sizeof(OAM1AG_HEAD_BAK_S)

/* OAM1AG HA设置HA公共报头 */
#define SET_OAM1AG_HA_HEAD(pucData, ucHAMid, ucBakOperation, usBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->usMsgLen = usBakMsgLen;\
    pstHaHdr->ucModID = (UCHAR)ucHAMid;\
    pstHaHdr->ucOperation = (UCHAR)ucBakOperation;\
}

/* 设置子消息类型,设置子消息长度 */
#define SET_OAM1AG_HA_CHILDHEAD(pucBaseHead,ulHeadOffset,usType,usBakLen)\
{\
    OAM1AG_HEAD_BAK_S *pHeadBak = NULL;\
    pHeadBak = (OAM1AG_HEAD_BAK_S *)((UCHAR *)pucBaseHead + ulHeadOffset);\
    pHeadBak->usBakType = usType;\
    pHeadBak->usBakLen = usBakLen;\
}

/* 设置MD/MA TLV类型 ,设置MD/MA TLV消息长度,设置ND/MA TLV的值*/
#define SET_OAM1AG_HA_MDMATLV(pucBase,ulBaseOffet,aucMdName,usMdNameLen,aucMaName,usMaNameLen)\
{\
    OAM1AG_MDTLV_BAK_S  *pMdTlvInfo = NULL;\
    OAM1AG_MATLV_BAK_S  *pMaTlvInfo = NULL;\
    pMdTlvInfo = (OAM1AG_MDTLV_BAK_S *)((UCHAR *)pucBase + ulBaseOffet);\
    pMdTlvInfo->usType = OAM_1AG_HAMDNAME;\
    pMdTlvInfo->usLength = usMdNameLen + OAM1AG_HEADBAK_LEN;\
    (VOID)TCPIP_Mem_Copy(pMdTlvInfo->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1, aucMdName,usMdNameLen);\
    pMaTlvInfo = (OAM1AG_MATLV_BAK_S *)((UCHAR *)pMdTlvInfo + pMdTlvInfo->usLength);\
    pMaTlvInfo->usType = OAM_1AG_HAMANAME;\
    pMaTlvInfo->usLength = usMaNameLen + OAM1AG_HEADBAK_LEN;\
    (VOID)TCPIP_Mem_Copy(pMaTlvInfo->szMAName, OAM_1AG_MAX_MANAME_LEN + 1, aucMaName,usMaNameLen);\
}                   

ULONG OAM_1AG_HA_BatchBackup(VOID);
ULONG OAM_1AG_HA_Smooth(VOID);
ULONG OAM_1AG_HA_Clean(VOID);
VOID  OAM_1AG_HA_RealBackup(UCHAR ucOperatorCode,USHORT usType,VOID *pData);
ULONG OAM_1AG_HA_OutputMsg(UCHAR * pucData, ULONG  ulDataLen);
ULONG OAM_1AG_HA_Input(UCHAR *pucData, ULONG ulDataLen);
ULONG OAM_1AG_HA_Restore(UCHAR * pucData, ULONG ulDataLen,UCHAR ucOperatorCode);
ULONG OAM_1AG_HA_RestoreInfo(UCHAR ucOperatorCode,USHORT usType,VOID *pData,VOID *pMdName,VOID *pMaName,
                                       VOID *pstTlvData);
ULONG OAM_1AG_HA_UpdateInfo(USHORT usType,UCHAR *pucMdName,UCHAR *pucMaName,VOID *pData,
                                 VOID *pstTlvData);
ULONG OAM_1AG_HA_CreateDynamicRmep(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                         USHORT usRmepId, VOID *pBaseData, VOID *pstTlvData);
ULONG OAM_1AG_HA_GlobalData(VOID);
ULONG OAM_1AG_HA_Batch1agInfo(USHORT usType);
ULONG OAM_1AG_HA_CfgPack(UCHAR *pucData,USHORT usBakTotalLen,USHORT usMsgOffset,
                         USHORT usType,VOID *pucNode,USHORT *pusBakNodeLen);
ULONG OAM_1AG_GetFirstNode(USHORT usType,ULONG *pulIndex,VOID *pNode, ULONG ulNodeBuffSize);
ULONG OAM_1AG_GetNextNode(USHORT usType,ULONG ulIndex,ULONG *pulNextIndex,VOID *pNode, ULONG ulNodeBufSize);
VOID  OAM_1AG_HA_DbgInfoOutput(UCHAR ucOperatorCode,USHORT usType,ULONG ulCmd);
ULONG OAM_1AG_HA_DebugOutPut(UCHAR *pucData, ULONG ulMsgLen, ULONG ulCmd);
ULONG OAM_1AG_SetHaVerboseDebug (ULONG ulFlag);
ULONG OAM_1AG_GetHaVerboseDebug (ULONG *pulFlag);
ULONG OAM_1AG_HA_CompatibleData(VOID);
/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. 修改原因: 备份全局协议版本*/
ULONG OAM_1AG_HA_VersionData(VOID);

#ifdef  __cplusplus
}
#endif

#endif

