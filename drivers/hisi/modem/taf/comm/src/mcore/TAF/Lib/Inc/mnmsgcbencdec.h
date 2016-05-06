
#ifndef __MNMSGCBENCDEC_H__
#define __MNMSGCBENCDEC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define MN_MSG_CB_GS_MASK                                   (0xC000)
#define MN_MSG_CB_MSG_CODE_HIGH_MASK                        (0x3F00)
#define MN_MSG_CB_MSG_CODE_LOW_MASK                         (0x00F0)
#define MN_MSG_CB_UPDATE_NUM_MASK                           (0x000F)


#define MN_MSG_MAX_LANG_NUM                                 (20)



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*ISO639 language code */
enum MN_MSG_ISO639_LANG_CODE_ENUM
{
    MN_MSG_ISO639_LANG_GERMAN                               =    0x6465,
    MN_MSG_ISO639_LANG_ENGLISH                              =    0x656e,
    MN_MSG_ISO639_LANG_ITALIAN                              =    0x6974,
    MN_MSG_ISO639_LANG_FRENCH                               =    0x6672,
    MN_MSG_ISO639_LANG_SPANISH                              =    0x6573,
    MN_MSG_ISO639_LANG_DUTCH                                =    0x6e6c,
    MN_MSG_ISO639_LANG_SWEDISH                              =    0x7376,
    MN_MSG_ISO639_LANG_DANISH                               =    0x6461,
    MN_MSG_ISO639_LANG_PORTUGUESE                           =    0x7074,
    MN_MSG_ISO639_LANG_FINNISH                              =    0x6569,
    MN_MSG_ISO639_LANG_NORWEGIAN                            =    0x6e6f,
    MN_MSG_ISO639_LANG_GREEK                                =    0x6772,
    MN_MSG_ISO639_LANG_TURKISH                              =    0x7472,
    MN_MSG_ISO639_LANG_HUNGARIAN                            =    0x6875,
    MN_MSG_ISO639_LANG_POLISH                               =    0x706c,
    MN_MSG_ISO639_LANG_CZECH                                =    0x6373,
    MN_MSG_ISO639_LANG_HEBREW                               =    0x6865,
    MN_MSG_ISO639_LANG_ARABIC                               =    0x6172,
    MN_MSG_ISO639_LANG_RUSSIAN                              =    0x7275,
    MN_MSG_ISO639_LANG_ICELANDIC                            =    0x6973,
    MN_MSG_ISO639_LANG_MAX
};
typedef    VOS_UINT16  MN_MSG_ISO639_LANG_ENUM_U16;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*Each CBS Page Info */

typedef struct/*Refer to 23041 9.4.1.2*/
{
    VOS_UINT8                           ucSnHigh;
    VOS_UINT8                           ucSnLow;
    VOS_UINT8                           ucMIdHigh;
    VOS_UINT8                           ucMIdLow;
    VOS_UINT8                           ucDCS;
    VOS_UINT8                           Pagesbit4   :  4;                       /*bits 0 - 3 indicates the total number of pages in the CBS message*/
    VOS_UINT8                           Pagebit4    :  4;                       /*bits 4 - 7 indicates binary the page number within that sequence*/
    VOS_UINT8                           aucContent[TAF_CBA_MAX_CBDATA_LEN];
}MN_MSG_CBGSMPAGE_STRU;


/* CBS的消息头 */
typedef struct
{
    VOS_UINT8                           ucNumOfPages;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           ucUpdateNum;
    VOS_UINT8                           ucGs;
    VOS_UINT16                          usMsgCode;
    VOS_UINT16                          usMsgId;
}MN_MSG_CB_PAGE_HEADER_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
VOS_UINT32 MN_MSG_DecodeCbsDcs(
    VOS_UINT8                           ucDcs,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLength,
    MN_MSG_CBDCS_CODE_STRU             *pstDcsInfo
);
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */


#endif /* end of MnMsgCbEncDec.h */

extern VOS_UINT32 MN_MSG_DecodeDcsIf01(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __MNMSGCBENCDEC_H__ */

