/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DSPP_Define.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : DSPP协议公用类型、宏定义
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_DSPP_DEFINE_H__
#define __BST_DSPP_DEFINE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_LIB_List.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DSPP_IsObjIdValid( ProcId ) ( ( (ProcId) > BST_APP_TYPE_MIN ) && ( (ProcId) < BST_OBJ_TYPE_MAX ) )
#define BST_DSPP_IsVersionValid(VerId)  ( ( (VerId) > BST_DSPP_VER_INVALID ) && ( (VerId) < BST_DSPP_VER_BUTT ) )
#define BST_DSPP_U8_TO_U16( u8L, u8H )  ( ( (u8L) & 0xff ) + ( ( (u8H)<<8 ) & 0xff00 ) )

#define BST_DSPP_U8_TO_U32( u8_0, u8_1, u8_2, u8_h )\
                                        ( ( (u8_0) & 0x000000FFU )\
                                        + ( ( (u8_1)<<8 ) & 0x0000FF00U )\
                                        + ( ( (u8_2)<<16 ) & 0x00FF0000U ) \
                                        + ( ( (u8_h)<<24 ) & 0xFF000000U ))

#define BST_DSPP_U16_TO_U8H( u16_data ) ( BST_UINT8 )( ( (u16_data)>>8 ) & 0xffU )
#define BST_DSPP_U16_TO_U8L( u16_data ) ( BST_UINT8 )( ( (u16_data) ) & 0xffU )
#define BST_DSPP_U32_TO_U8_0(u32_data)  ( BST_UINT8 )( ( (u32_data) ) & 0xffU )
#define BST_DSPP_U32_TO_U8_1(u32_data)  ( BST_UINT8 )( ( (u32_data)>>8  ) & 0xffU )
#define BST_DSPP_U32_TO_U8_2(u32_data)  ( BST_UINT8 )( ( (u32_data)>>16 ) & 0xffU )
#define BST_DSPP_U32_TO_U8_3(u32_data)  ( BST_UINT8 )( ( (u32_data)>>24 ) & 0xffU )

#define BST_DSPP_INVALID_ADDR           ( BST_INVALID_SNID )
#define BST_DSPP_INVALID_LINK_ID        ( 0xFFFFFFFFU )
#define BST_DSPP_COMMON_LINK_ID         ( 0x00000000U )
#define BST_DSPP_IsVoidOfstAddr( addr ) ( ( addr == 0x0000 ) || ( addr == BST_DSPP_INVALID_ADDR ) )
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum BST_DSPP_VERION_ENUM
{
    BST_DSPP_VER_INVALID                = 0,
    BST_DSPP_VER_A                      = 1,
    BST_DSPP_VER_B,
    BST_DSPP_VER_C,
    BST_DSPP_VER_VOID,
    BST_DSPP_VER_BUTT
};
typedef BST_UINT8                       BST_DSPP_VERION_ENUM_UINT8;

enum BST_DSPP_LAYER_ID_ENUM
{
    BST_DSPP_LAYER_INVALID              = 0,
    BST_DSPP_LAYER_TRS                  = 1,
    BST_DSPP_LAYER_CTR,
    BST_DSPP_LAYER_APP,
    BST_DSPP_LAYER_BUTT
};
typedef BST_UINT8                       BST_DSPP_LAYER_ID_ENUM_UINT8;

enum BST_DSPP_PRIMITIVE_ENUM
{
    BST_DSPP_PRMTV_INVALID              = 0,
    BST_DSPP_PRMTV_REQUEST              = 1,
    BST_DSPP_PRMTV_RESPONSE,
    BST_DSPP_PRMTV_REPORT,
    BST_DSPP_PRMTV_CONFIRM,
    BST_DSPP_PRMTV_ACK
};
typedef BST_UINT8                       BST_DSPP_PRIMITIVE_ENUM_UINT8;

enum BST_DSPP_FLG_CMD_ENUM
{
    BST_DSPP_FLG_CMD_INVALID            = 0,
    BST_DSPP_FLG_CMD_CLEAR              = 1,
    BST_DSPP_FLG_CMD_CLOSE,
    BST_DSPP_FLG_CMD_SEND,
    BST_DSPP_FLG_CMD_BUFFER,
    BST_DSPP_FLG_CMD_TRAFFIC,
    BST_DSPP_FLG_CMD_BUTT
};
typedef BST_UINT8                       BST_DSPP_FLG_CMD_ENUM_UINT8;

enum BST_DSPP_FLG_ADDTYPE_ENUM
{
    BST_DSPP_FLG_ADDTYPE_VOID           = 0,
    BST_DSPP_FLG_ADDTYPE_INET           = 1,
    BST_DSPP_FLG_ADDTYPE_TASK,
    BST_DSPP_FLG_ADDTYPE_BUTT
};
typedef BST_UINT8                       BST_DSPP_FLG_ADDTYPE_ENUM_UINT8;

enum BST_DSPP_FLG_PROTYPE_ENUM
{
    BST_DSPP_FLG_PROTYPE_TCP            = 0,
    BST_DSPP_FLG_PROTYPE_UDP            = 1,
    BST_DSPP_FLG_PROTYPE_BUTT
};
typedef BST_UINT8                       BST_DSPP_FLG_PROTYPE_ENUM_UINT8;

enum BST_DSPP_FLG_LVLTYPE_ENUM
{
    BST_DSPP_FLG_LVLTYPE_NORMAL         = 0,
    BST_DSPP_FLG_LVLTYPE_HS             = 1,
    BST_DSPP_FLG_LVLTYPE_LP,
    BST_DSPP_FLG_LVLTYPE_BUTT
};
typedef BST_UINT8                       BST_DSPP_FLG_LVLTYPE_ENUM_UINT8;

enum BST_DSPP_FLG_PKTTYPE_ENUM
{
    BST_DSPP_FLG_PKTADDR_COMN           = 0,
    BST_DSPP_FLG_PKTADDR_HEAD           = 1,
    BST_DSPP_FLG_PKTADDR_TAIL,
    BST_DSPP_FLG_PKTADDR_SINGLE
};
typedef BST_UINT8                       BST_DSPP_FLG_PKTADDR_ENUM_UINT8;
/*****************************************************************************
  4 类型定义
*****************************************************************************/
typedef BST_UINT16                      BST_DSPP_OFSTADDR_T;
typedef BST_UINT16                      BST_DSPP_OBJTADDR_T;
typedef BST_UINT8                       BST_DSPP_DVCID_T;
typedef BST_UINT16                      BST_DSPP_PKTSN_T;
typedef BST_UINT8                       BST_DSPP_PKTPC_T;
typedef BST_UINT8                       BST_DSPP_PRMTV_T;
typedef BST_UINT16                      BST_DSPP_CMDLEN_T;
typedef BST_IPLINK_ID1_T                BST_DSPP_LINKID1_T;
typedef BST_IPLINK_ID2_T                BST_DSPP_LINKID2_T;
typedef BST_UINT16                      BST_DSPP_FLAG_T;
/*****************************************************************************
  5 数据结构定义
*****************************************************************************/
typedef struct
{
    NODE                                node;
    BST_UINT8                          *pucData;
    BST_UINT16                          usLength;
    BST_DSPP_PKTPC_T                    usPicNum;
} BST_DSPP_PIC_STRU;

typedef struct
{
    BST_DSPP_VERION_ENUM_UINT8          enTpVer;
    BST_DSPP_VERION_ENUM_UINT8          enCpVer;
    BST_DSPP_VERION_ENUM_UINT8          enApVer;
    BST_DSPP_PRIMITIVE_ENUM_UINT8       enPrmvType;
    BST_UINT16                          usLength;
    BST_DSPP_PKTSN_T                    usPktNum;
    BST_UINT8                          *pucData;
    BST_UINT8                          *pucSource;
    union
    {
        struct
        {
            BST_DSPP_OBJTADDR_T         usObjtAddr;
            BST_DSPP_OFSTADDR_T         usOfstAddr;
            BST_ACT_ENUM_UINT8          ucActType;
            BST_UINT8                   aucReserved[1];
        } stCpVerA;
        struct
        {
            BST_DSPP_OBJTADDR_T         usObjtAddr;
            BST_DSPP_OFSTADDR_T         usOfstAddr;
            BST_ACT_ENUM_UINT8          ucActType;
            BST_UINT8                   aucReserved[1];
        } stCpVerB;
        struct
        {
            BST_DSPP_LINKID1_T          ulMainLinkId;
            BST_DSPP_LINKID1_T          ulAuxLinkId;
            BST_UINT16                  usCmdId;
            BST_UINT16                  usProcLevel;
            BST_UINT8                   ucAddrType;
            BST_UINT8                   ucPropType;
            BST_UINT8                   ucIpProtocol;
            BST_UINT8                   ucPktAddr;
        } stCpVerC;
    };
} BST_DSPP_HEAD_STRU;

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

