/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_ic_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific IC macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related IC macros
************************************************************************/

#ifndef _IPBIR_VISP_IC_MAP_H_
#define _IPBIR_VISP_IC_MAP_H_

#define IPOS_IC_LEVEL_TOP                0
#define IPOS_IC_LEVEL_EMERG              1
#define IPOS_IC_LEVEL_ALERT              2
#define IPOS_IC_LEVEL_CRIT               3
#define IPOS_IC_LEVEL_ERR                4
#define IPOS_IC_LEVEL_WARN               5
#define IPOS_IC_LEVEL_NOTICE             6
#define IPOS_IC_LEVEL_INFO               7
#define IPOS_IC_LEVEL_DEBUG              8
#define IPOS_IC_MAX_LEVEL_NUM            8

#ifndef IC_INFO_LOG
    #define IC_INFO_LOG                  1
#endif  /* ifndef IC_INFO_LOG */
#ifndef IC_INFO_TRAP
    #define IC_INFO_TRAP                 2
#endif  /* ifndef IC_INFO_TRAP */
#ifndef IC_INFO_DEBUG
    #define IC_INFO_DEBUG                3
#endif  /* ifndef IC_INFO_DEBUG */

#define IPOS_IC_INFO_LOG                IC_INFO_LOG
#define IPOS_IC_INFO_DEBUG              IC_INFO_DEBUG
#define IPOS_IC_INFO_TRAP               IC_INFO_TRAP

#define IPOS_IC_INFOMODU_MASK           0xFFFF0000
#define IPOS_IC_INFOTYPE_MASK           0x00007000
#define IPOS_IC_INFONO_MASK             0x00000FFF

#define IPOS_IC_INFO_MAXLEN             1024
#define IPOS_IC_DEBUGINFO_MAXLEN        1024

#define IC_INFOID_DEF   IPOS_IC_INFOID_DEF

#define IPOS_IC_INFOID_DEF(mid, infotype, infoidx) ( (mid) | ( (infotype) << 12 ) | (infoidx) )
#define IPOS_IC_INFOMODU(InfoID) ( (InfoID) & IPOS_IC_INFOMODU_MASK )
#define IPOS_IC_INFOTYPE(InfoID) ( ((InfoID) & IPOS_IC_INFOTYPE_MASK) >> 12)
#define IPOS_IC_INFONO(InfoID)  ( (InfoID) & IPOS_IC_INFONO_MASK)

typedef enum IPOS_tagIC_MsgVarType
{
    IPOS_IC_VAR_TYPE_LONG=0,
    IPOS_IC_VAR_TYPE_ULONG,
    IPOS_IC_VAR_TYPE_SHORT,
    IPOS_IC_VAR_TYPE_USHORT,
    IPOS_IC_VAR_TYPE_UCHAR,
    IPOS_IC_VAR_TYPE_STRING,   /*ASCII码字符串*/
    IPOS_IC_VAR_TYPE_IPADDR,   /*32位主机顺序表示的地址*/
    IPOS_IC_VAR_TYPE_DATE_S,   /*北研协议软件部VOS定义的日期结构类型*/
    IPOS_IC_VAR_TYPE_TIME_S,    /*北研协议软件部VOS定义的时间结构类型*/
    IPOS_IC_VAR_TYPE_INTEGER,
    IPOS_IC_VAR_TYPE_COUNTER,
    IPOS_IC_VAR_TYPE_GAUGE,
    IPOS_IC_VAR_TYPE_TIMETICK,
    IPOS_IC_VAR_TYPE_OCTET,
    IPOS_IC_VAR_TYPE_OPAQUE,
    IPOS_IC_VAR_TYPE_OID,
    IPOS_IC_VAR_TYPE_COUNTER64

} IPOS_IC_MsgVarType_EN;

typedef  struct   IPOS_tagIC_InfoAttr
{
    ULONG  m_ulInfoID;        /*信息ID*/
    /*Changed by wan for 4-byte-align when do VISPV1R7 integration, 2008-05-12*/
    ULONG  m_ulInfoLevel;   /*信息级别*/    
    CHAR*  m_szInfoMnem;    /*信息助记符*/
    CHAR*  m_szEnInfoFmt;   /*英文信息格式化串*/
    CHAR*  m_szChInfoFmt;   /* 中文信息格式化串*/

}  IPOS_IC_InfoAttr_S , *IPOS_IC_InfoAttr_P;

ULONG IPOS_SendInfo(ULONG ulMID, ULONG ulFlag, ULONG ulIndex,VOID* pInfo, VOID *pInfoType,
                    va_list arg);

/* Changed to LONG to remove L4 Warning */
LONG IPBIR_VISP_IC_RegInfo(CHAR *szModuName, IPOS_IC_InfoAttr_S* pstInfoAttrArray,
                            ULONG ulInfoNum);

#define IPOS_INFOINIT(SendInfo,RegInfo,Ret)\
\
        SendInfo = IPOS_SendInfo;\
        RegInfo = IPBIR_VISP_IC_RegInfo; \
        Ret = VOS_OK;



#endif  /* end of _IPBIR_VISP_IC_MAP_H_ */

