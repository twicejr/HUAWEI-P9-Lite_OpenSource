/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

******************************************************************************
    File Name       : NasLmmPubMNvimOsa.h
    Description     : NasLmmPubMNvimOsa.h header file
    History     :
    1.zhengjunyan 00148421  2011-05-28 文件名由 NasMmPubMNvimOsa.h修改为
                                        NasLmmPubMNvimOsa.h
******************************************************************************/

#ifndef __NASLMMPUBMNVIMOSA_H__
#define __NASLMMPUBMNVIMOSA_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPubMOsa.h"
#include    "NasLmmCore.h"
#include    "NasLmmPubMFsm.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmcEmmInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
typedef VOS_UINT32                      NAS_LMM_USIM_NV_RESULT;

#define NAS_LMM_NVIM_OK                  0
#define NAS_LMM_NVIM_FAIL                1
#define NAS_LMM_NVIM_HARD_USIM           2

#define NAS_LMM_NVIM_WRITTEN_UNNEEDED      3


#define NAS_NVIM_NULL_PTR               VOS_NULL_PTR
#define NAS_NVIM_BIT_SLCT               1
#define NAS_NVIM_BIT_NO_SLCT            0

#define NAS_USIM_MIN_PLMN_LEN           5*8

#define NAS_LMM_NVIM_LOG_INFO(String)    NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_NVIM_LOG_ERR(String)     NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)

#define NAS_LMM_NVIM_LOG1_INFO(String, Para1)    NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_NVIM_LOG1_ERR(String, Para1)    NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)

#define NAS_LMM_NVIM_LOG3_INFO(String, Para1, Para2, Para3) \
            NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)


#define NAS_LMM_NVIM_PLMN_ID_LEN           3
#define NAS_LMM_NVIM_TAC_LEN               2
#define NAS_LMM_NVIM_BYTE_LEN              5

#define NAS_LMM_NVIM_SEC_ENCINT_LEN        1
#define NAS_LMM_NVIM_SEC_NAS_COUNT_LEN     4
#define NAS_LMM_NVIM_SEC_KSI_LEN           1
#define NAS_LMM_NVIM_SEC_KASME_LEN         32
#define NAS_LMM_NVIM_SEC_MSG_LEN           0x34

#define NAS_LMM_NVIM_SEC_KSI_TAG           0x80
#define NAS_LMM_NVIM_SEC_KASME_TAG         0x81
#define NAS_LMM_NVIM_SEC_UPNASCOUNT_TAG    0x82
#define NAS_LMM_NVIM_SEC_DNNASCOUNT_TAG    0x83
#define NAS_LMM_NVIM_SEC_ALG_TAG           0x84

#define NAS_LMM_NVIM_GUTI_OETOI            0x06
#define NAS_LMM_NVIM_GUTI_LEN              10
#define NAS_LMM_NVIM_GUTI_AND_OETOI_LEN    0x0b

#define NAS_LMM_NVIM_LRV_TAI_LEN           (NAS_LMM_NVIM_TAC_LEN + NAS_LMM_NVIM_PLMN_ID_LEN)

#define NAS_LMM_NVIM_LOW_3_BIT_1           0x07               /*0000 0111*/

#define NAS_LMM_NVIM_LOW_4_BIT_1           0x0f

#define NAS_LMM_NVIM_VALID_UPDATESTA       0x02

#define NAS_LMM_NVIM_MAX_NASCOUNT          0x00ffffff

#define NAS_LMM_NVIM_IMSI_FILE_LEN         9

#define NAS_LMM_NVIM_IMEI_LEN              8
#define NAS_LMM_NVIM_IMEI_LEN_IE           4

#define NAS_LMM_NVIM_SECU_CONTEXT_TAG      0xa0

#define NAS_LMM_ACCESS_TECH_LTE            0x40
#define NAS_LMM_ACCESS_TECH_RSV            0x00

#define NAS_LMM_NVIM_HPLMN_PERI_MAX_LEN    80                /* 最大为8小时 */
#define NAS_LMM_NVIM_DEFAULT_HPLMN_PERI    10                /* 默认为1小时 */

#define NAS_LMM_NVIM_MOVE_24_BIT           24
#define NAS_LMM_NVIM_MOVE_16_BIT           16
#define NAS_LMM_NVIM_MOVE_8_BIT            8

#define NAS_LMM_NVIM_BYTE_FF               0xff

#define NAS_LMM_NVIM_MNCLEN_FILE_MIN_LEN   4
#define NAS_LMM_NVIM_ACC_FILE_LEN          2
#define NAS_LMM_NVIM_HPLMN_PERI_FILE_LEN   1

#define NAS_LMM_NVIM_MNCLEN_VALUE_3        3
#define NAS_LMM_NVIM_MNCLEN_VALUE_2        2
#define NAS_LMM_NVIM_MNC_LENGTH_POSITION      4



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_NVIM_CTRL_TBL
 协议表格  :
 ASN.1描述 :
 结构说明  : 数据结构
*****************************************************************************/
typedef struct
{
    VOS_VOID                            *pData;             /*内部数据类型*/
    VOS_VOID                            *pNvData;           /*NVIM数据类型*/
    VOS_UINT16                          usDataLen;          /*内部数据长度*/
    VOS_UINT16                          usNvDataLen;        /*NVIM数据长度*/

}NAS_NVIM_CTRL_TBL;


/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*extern VOS_UINT8  g_ucNasMmcMncLen;*/
extern VOS_UINT32 g_ulSendMsgCounter;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/*Decode COMM PARA*/
/*extern VOS_UINT32  NAS_LMM_DecodeNvClassMark1(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
 */
/*extern VOS_UINT32  NAS_LMM_DecodeNvClassMark2(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
 */
/*extern VOS_UINT32  NAS_LMM_DecodeNvClassMark3(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
 */
extern VOS_UINT32  NAS_LMM_DecodeOneNvItem(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);


extern VOS_UINT32  NAS_LMM_DecodeNvRaCap(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
/*Decode LOC INFO*/
extern VOS_UINT32  NAS_LMM_DecodeNvUpdateSta(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvHPLMN(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);

/*Decode SECURITY INFO*/
extern VOS_UINT32  NAS_LMM_DecodeNvSupCodecs(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvKSI_SGSN(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);

/*Decode SIM INFO*/
/*extern VOS_UINT32  NAS_LMM_DecodeSimUST( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);*/
extern VOS_UINT32  NAS_LMM_DecodeNvHplmnACT(  NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );
extern VOS_UINT32  NAS_LMM_DecodeNvMNCLen(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvFplmnList(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvUplmn(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvOplmn(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvHPLMNSelPriod(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvCsLoc(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeSimPsLoc( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeSimImsi(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);

extern VOS_UINT32  NAS_LMM_DecodeSimMncLen(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);

extern VOS_UINT32  NAS_LMM_DecodeNvCsCKIK(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvPsKey(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvKC(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvSecAlgrithm(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeSimLRplmnSI(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );
/*Decode OM INFO*/
extern VOS_UINT32  NAS_LMM_DecodeNvMacAddr(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvIPAddr(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_DecodeNvACC(  NAS_NVIM_CTRL_TBL *pstNvCtrlTbl  );
extern VOS_UINT32  NAS_LMM_DecodeSimSecContext( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );

extern VOS_UINT32  NAS_LMM_DecodeSoftUsimCnf( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );

/*Encode COMM PARA*/

/*Encode LOC INFO*/

extern VOS_UINT32  NAS_LMM_EncodeOneNvItem(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);

/*Encode SIM INFO*/
extern VOS_UINT32  NAS_LMM_EncodeNvUplmn( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );
extern VOS_UINT32  NAS_LMM_EncodeSimSecContext( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );
extern VOS_UINT32  NAS_LMM_EncodeSimPsLoc(NAS_NVIM_CTRL_TBL *pstNvCtrlTbl);
extern VOS_UINT32  NAS_LMM_EncodeNvHPLMNSelPriod( NAS_NVIM_CTRL_TBL *pstNvCtrlTbl );
extern VOS_VOID  NAS_LMM_CheckNvDrxParamAndTransVal(
                                         CONST  NAS_MM_DRX_STRU *pstNvimDrxParam,
                                                NAS_MM_DRX_STRU *pstTransDrxParam);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif /* NasLmmPubMNvimOsa.h*/
