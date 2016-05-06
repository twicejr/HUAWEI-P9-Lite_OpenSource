


#ifndef __NASLPPENCODEDECODEPUBLIC_H__
#define __NASLPPENCODEDECODEPUBLIC_H__




/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"
#include    "PsCommonDef.h"
#include    "LPsOm.h"
#include    "NasLppPublic.h"




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
  2 Macro
*****************************************************************************/
#define NAS_LPP_SLCT        (1)
#define NAS_LPP_NO_SLCT     (0)
#define NAS_LPP_TRUE        (TRUE)
#define NAS_LPP_FALSE       (FALSE)
//#define NAS_LPP_DECODE_FAIL (1)
//#define NAS_LPP_DECODE_SUCC (0)
//#define NAS_LPP_ENCODE_SUCC (0)
//#define NAS_LPP_ENCODE_FAIL (1)


/*Encode define start*/
#define NAS_LPP_GNSS_SUPPORT_LIST_MIN       (1)
#define NAS_LPP_GNSS_SUPPORT_LIST_MAX       (16)
#define NAS_LPP_GNSS_IDS_MIN                (1)
#define NAS_LPP_GNSS_IDS_MAX                (16)
#define NAS_LPP_GENERIC_ASSIST_DATA_SUPPORT_MIN     (1)
#define NAS_LPP_GENERIC_ASSIST_DATA_SUPPORT_MAX     (16)
#define NAS_LPP_INOSHER_MODEL_SUPPORT_MIN       (1)
#define NAS_LPP_INOSHER_MODEL_SUPPORT_MAX       (8)
#define NAS_LPP_SBASID_MAX                      (3)
#define NAS_LPP_CLOCK_MODEL_MIN                 (1)
#define NAS_LPP_CLOCK_MODEL_MAX                 (8)
#define NAS_LPP_ORBIT_MODEL_MIN                 (1)
#define NAS_LPP_ORBIT_MODEL_MAX                 (8)
#define NAS_LPP_ALMANAC_MODEL_MIN               (1)
#define NAS_LPP_ALMANAC_MODEL_MAX               (8)
#define NAS_LPP_UTC_MODEL_MIN                   (1)
#define NAS_LPP_UTC_MODEL_MAX                   (8)
#define NAS_LPP_EXT_ENUMERATED_BUTT             (0XFF)
/*Encode define end*/

/*Encode define start*/

/*Encode define end*/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


enum NAS_LPP_TO_OM_MSG_ENUM
{
    NAS_LPP_TO_OM_MSG_BASE = 0,
    NAS_LPP_TO_OM_MSG_ASN_FAIL = NAS_LPP_TO_OM_MSG_BASE + 0X01,
};

enum NAS_LPP_DECODE_CAUSE_ENUM
{
    NAS_LPP_DECODE_SUCC = 0,                                    /*成功*/
    NAS_LPP_DECODE_FAIL,                                        /*失败*/
    /*公共错误*/
    NAS_LPP_DECODE_NULL_PTR,                                    /*空指针，不大可能用到,严格意义上，解码不可能有空指针*/
    /*MsgHeaderError，映射到LPP error空口中的头错误*/
    NAS_LPP_DECODE_MSG_HEADER_ERROR_INCORRECT_VALUE,            /*消息头值不正确*/
    NAS_LPP_DECODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL,             /*消息头的语义错误，这一块错误后续可扩展，在流程中进一步细分*/
    /*IncorrectError，映射到LPP error不正确值的错误*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR,         /*整型值不正确*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR,            /*枚举值不正确*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR,          /*STRING类型的错误， 包括*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,       /*结构体数组的有效长度超限*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR,            /*结构体有扩展的项,或者枚举扩展项的长度太长，超过了65535*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR,              /*字符型变量长度不正确*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR,                /*choice值超过范围*/

    /*MsgBodyError，映射到LPP error消息体错误*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE,   /*有扩展的结构体，有必选的扩展项，但是没有选中*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH,          /*解码的总长度跟解码之后的总长度不匹配*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE, /*某一信元为可选信元，但是某些流程中是必选信元没有带过来*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH,  /*扩展项L+V的值不匹配*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS,   /*在某些流程中，某些信元的值一定不对，这种也算消息体错误*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TOO_SHORT,                    /*消息体太短*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TYPE_NON_EXIST,               /*消息类型不存在*/
    /*EpuduError, 映射到LPP error中的epdu错误*/
    NAS_LPP_DECODE_MSG_EPDU_ERROR_VALUE_ERROR,                  /*EPDU中值解码错误*/
    /*Undefined, 映射到LPP error中的undefined错误*/
    NAS_LPP_DECODE_MSG_UNDEFINED_ERROR,                         /*除开上面错误状态之外的状态*/

    NAS_LPP_DECODE_MSG_ERROR_BUTT
};
typedef VOS_UINT32  NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32;

enum NAS_LPP_ENCODE_CAUSE_ENUM
{
    NAS_LPP_ENCODE_SUCC = 0,                                    /*成功*/
    NAS_LPP_ENCODE_FAIL,                                        /*失败*/
    /*公共错误*/
    NAS_LPP_ENCODE_NULL_PTR,                                    /*空指针，不大可能用到,严格意义上，解码不可能有空指针*/
    /*MsgHeaderError，映射到LPP error空口中的头错误*/
    NAS_LPP_ENCODE_MSG_HEADER_ERROR_INCORRECT_VALUE,            /*消息头值不正确*/
    NAS_LPP_ENCODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL,             /*消息头的语义错误，这一块错误后续可扩展，在流程中进一步细分*/
    /*IncorrectError，映射到LPP error不正确值的错误*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR,         /*整型值不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR,            /*枚举值不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_VALUE_ERROR,          /*选择体值不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR,          /*STRING类型的错误， 包括*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,       /*结构体数组的有效长度超限*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR,            /*结构体有扩展的项,或者枚举扩展项的长度太长，超过了65535*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR,              /*字符型变量长度不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR,                /*choice值超过范围*/

    /*MsgBodyError，映射到LPP error消息体错误*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE,   /*有扩展的结构体，有必选的扩展项，但是没有选中*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH,          /*解码的总长度跟解码之后的总长度不匹配*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE, /*某一信元为可选信元，但是某些流程中是必选信元没有带过来*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS,   /*在某些流程中，某些信元的值一定不对，这种也算消息体错误*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_TYPE_NON_EXIST,               /*消息类型不存在*/
    /*EpuduError, 映射到LPP error中的epdu错误*/
    NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR,                  /*EPDU中值错误*/
    /*Undefined, 映射到LPP error中的undefined错误*/
    NAS_LPP_ENCODE_MSG_UNDEFINED_ERROR,                         /*除开上面错误状态之外的状态*/

    NAS_LPP_ENCODE_MSG_ERROR_BUTT
};
typedef VOS_UINT16  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16;

enum LPP_ENCODE_ERR_STR_ENUM
{
    LPP_ENCODE_ERR_STR_TRANSATION_ID = 0,
    LPP_ENCODE_ERR_STR_SEQUENCE_NUMBER,
    LPP_ENCODE_ERR_STR_ACKNOWLEGMENT,
    LPP_ENCODE_ERR_STR_PROVIDE_CAPABILITIES,
    LPP_ENCODE_ERR_STR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_ERR_STR_ENUM_ENUM_UINT32;

enum LPP_DECODE_ERR_STR_ENUM
{
    LPP_DECODE_ERR_STR_TRANSATION_ID = 0,
    LPP_DECODE_ERR_STR_SEQUENCE_NUMBER,
    LPP_DECODE_ERR_STR_ACKNOWLEGMENT,
    LPP_DECODE_ERR_STR_REQ_CAPABILITIES,
    LPP_DECODE_ERR_STR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_ERR_STR_ENUM_UINT32;

enum LPP_ENCODE_DECODE_ERR_ENUM
{
    LPP_ENCODE_DECODE_ERR_VALUE_OUT_OF_RANGE = 0, /*表示编解码的时候值超出范围*/
    LPP_ENCODE_DECODE_ERR_PROTOCOL_MISMATCH,      /*表示协议版本不一致*/
    LPP_DECODE_DECODE_ERR_MSG_EXCEED_TOTOL_LEN,   /*表示总长度超长*/
    LPP_ENCODE_DECODE_ERR_NULL_POINTER,           /*表示入参空指针*/
    LPP_DECODE_DECODE_ERR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_DECODE_ERR_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*********************************************************************
结构名称: LPP_DEBUG_INFO_STRU
结构描述: LPP模块可维可测消息结构
作    者: lifuxin 00253982 2015-5-6 初稿
*********************************************************************/
typedef struct
{
    LPP_ENCODE_DECODE_ERR_ENUM_UINT32       enEncodeDecodeErrType;      /*表示错误类型*/
    VOS_UINT8                               aucAbortIeName[16];         /*异常IE名字*/
    VOS_UINT32                              ulMinValue;                 /*取值的下界*/
    VOS_UINT32                              ulMaxValue;                 /*取值的上界*/
    VOS_UINT32                              ulLineNo;                   /*出错时候的行号*/
    VOS_UINT32                              ulErrPos;                   /*出现解码错误时刻的位置*/
    VOS_UINT32                              ulErrByte;
    VOS_UINT8                               ucProtocolVersionOfCn;      /*网络侧协议版本*/
    VOS_UINT8                               ucExtIeNum;                 /*网络侧扩展信元的计数*/
    VOS_UINT8                               aucRsv[2];
    VOS_UINT32                              aulRsv[10];                 /*保留项，便于后续扩展*/
} LPP_DEBUG_INFO_STRU;


/*L模使用*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}PS_HEADER_STRU;

/*L模使用
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRsv[2];
}LHPA_MSG_HEADER_STRU;*/






/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LPP_EncodeBitSteam(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      *pulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource);
extern VOS_VOID NAS_LPP_SetBitStreamFromStream(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      ulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource);


extern VOS_UINT32 NAS_LPP_GetParamFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      ulPos,
                                            VOS_UINT8       usLen);
extern VOS_UINT32 NAS_LPP_GetDataFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      *ulPos,
                                            VOS_UINT8       usLen);

extern VOS_UINT32 NAS_LPP_GetLongDataFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT8       usLen,
                                                VOS_UINT64      *pllDestData);
extern VOS_UINT32 NAS_LPP_GetLongBitFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT16       usLen,
                                                VOS_UINT8      *pllDestData);

extern VOS_UINT16 NAS_LPP_EncodeExtBit(
                        VOS_UINT16      *pBitPos,
                        VOS_UINT8       *pEncodeOutMsg);
extern VOS_VOID NAS_LPP_EncodeBitsLess8(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       ucSource);

extern VOS_UINT32  NAS_LPP_DecodeExtIeWithPartValid(
                        VOS_UINT8                               *pDecodeBitStream,
                        VOS_UINT32                              *pCurrentBitPos,
                        VOS_UINT32                              ulInvalidExtIeLen);

extern VOS_UINT32  NAS_LPP_Decode_ExtChoiceCellId(
                                    VOS_UINT8                       *pDecodeBitStream,
                                    VOS_UINT32                      *pCurrentBitPos,
                                    VOS_UINT8                       ucLen,
                                    VOS_UINT32                      *pExtChoiceValue);

extern VOS_VOID NAS_LPP_EncodeEncodeLongData(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT32      ulSource);


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

#endif











































