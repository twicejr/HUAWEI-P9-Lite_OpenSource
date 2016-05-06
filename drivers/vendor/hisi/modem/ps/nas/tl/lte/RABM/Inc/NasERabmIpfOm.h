/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasERabmIpfOm.h
  版 本 号   : 初稿
  作    者   : L62099
  生成日期   : 2011年3月23日
  最近修改   :
  功能描述   : NAS  RABM IPF的OM功能头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NASRABMIPFOM_H__
#define __NASRABMIPFOM_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasERabmPublic.h"

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
#define NAS_ERABM_IPF_OM_INFO_PTR()          (&g_stNasERabmIpfOmInfo)

/* 增加上行收到的IP包个数 */
#define NAS_ERABM_IPF_OM_ADD_UL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataCnt)

/* 增加上行收到的字节数 */
#define NAS_ERABM_IPF_OM_ADD_UL_RCV_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_UL_RCV_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlRcvDataBytes)

/* 增加上行IPF过滤错误数 */
#define NAS_ERABM_IPF_OM_ADD_UL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlErrorCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlErrorCnt)

/* 增加上行收到的IP分片数 */
#define NAS_ERABM_IPF_OM_ADD_UL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlFragCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlFragCnt)

/* 增加上行丢弃的IP包个数 */
#define NAS_ERABM_IPF_OM_ADD_UL_DISCARD_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlDiscardCnt += 1)

#define NAS_ERABM_IPF_OM_GET_UL_DISCARD_CNT()\
                    (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlDiscardCnt)

/* 增加上行IPF已处理的字节数 */
#define NAS_ERABM_IPF_OM_ADD_UL_PRCS_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlProcBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_UL_PRCS_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfUlProcBytes)

/* 增加下行收到的IP包个数 */
#define NAS_ERABM_IPF_OM_ADD_DL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_RCV_NUM()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataCnt)

/* 增加下行收到的字节数 */
#define NAS_ERABM_IPF_OM_ADD_DL_RCV_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_DL_RCV_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlRcvDataBytes)

/* 增加下行IPF过滤错误数 */
#define NAS_ERABM_IPF_OM_ADD_DL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlErrorCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlErrorCnt)

/* 增加下行收到的IP分片数 */
#define NAS_ERABM_IPF_OM_ADD_DL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFragCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_FRAG_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFragCnt)

/* 增加下行IPF 后丢弃的包个数 */
#define NAS_ERABM_IPF_OM_ADD_DL_DISCARD_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlDiscardCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_DISCARD_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlDiscardCnt)

/* 增加下行IPF处理后的字节数 */
#define NAS_ERABM_IPF_OM_ADD_DL_PRCS_BYTES(bytes)\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlProcBytes += (bytes))

#define NAS_ERABM_IPF_OM_GET_DL_PRCS_BYTES()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlProcBytes)

/* 增加下行非用户面数据IP包个数 */
#define NAS_ERABM_IPF_OM_ADD_DL_NON_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlNonUsrDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_NON_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlNonUsrDataCnt)

/* 增加下行用户面数据IP报个数 */
#define NAS_ERABM_IPF_OM_ADD_DL_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlUsrDataCnt += 1)

#define NAS_ERABM_IPF_OM_GET_DL_USRDATA_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulDlUsrDataCnt)

/* 上行产生TFT Filter计数 */
#define NAS_ERABM_IPF_OM_ADD_UL_FILTER_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfTftFilterErr += 1)

#define NAS_ERABM_IPF_OM_GET_UL_FILTER_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfTftFilterErr)

/* 增加下行添加到IPF错误计数 */
#define NAS_ERABM_IPF_OM_ADD_DL_DATA_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFilterErr += 1)

#define NAS_ERABM_IPF_OM_GET_DL_DATA_ERR_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfDlFilterErr)

/* 增加IPF FIlter满情况计数 */
#define NAS_ERABM_IPF_OM_ADD_FILTER_FULL_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfFilterFull += 1)

#define NAS_ERABM_IPF_OM_GET_FILTER_FULL_CNT()\
                (NAS_ERABM_IPF_OM_INFO_PTR()->ulIpfFilterFull)


/* 获取上行分片数据包的数传信息地址 */
#define NAS_ERABM_IPF_OM_GET_UL_TRANS_INFO_ADDR()\
                (&((NAS_ERABM_IPF_OM_INFO_PTR())->stUlIpFfragmentTransInfo))

/* 获取上行IPV4分片数据包的数传信息地址 */
#define NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR()\
                (&((NAS_ERABM_IPF_OM_GET_UL_TRANS_INFO_ADDR())->stUlIpv4FragmentTransInfo))

/* 获取上行IPV6分片数据包的数传信息地址 */
#define NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR()\
                (&((NAS_ERABM_IPF_OM_GET_UL_TRANS_INFO_ADDR())->stUlIpv6FragmentTransInfo))


/* 获取上行总的分片数据包数目，包括IPV4 和 IPV6 分片包 */


/* 获取上行 IPV4 分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4FragmentPackageNum)

/* 获取上行 IPV4 头部分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentPackageNum)

/* 获取上行丢弃 IPV4 分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_DISCARD_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4DiscardFragmentPackageNum)

/* 获取上行 IPV4 分片包中非头部分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_NON_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentPackageNum)

/* 获取上行 IPV4 分片包中非头部分片查找缺省承载失败包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_NON_HEADER_FIND_DEFT_FAIL_PACK_NUM()\
                    ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentFindDeftFailedPackageNum)


/* 获取上行 IPV4 头部分片匹配信息不完整的分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV4_HEADER_NO_UPLAYER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentNoUpperLayerPackageNum)

/* 增加上行 IPV4 分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4FragmentPackageNum ++)

/* 增加上行丢弃 IPV4 分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_DISCARD_IPV4_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4DiscardFragmentPackageNum ++)

/* 增加上行 IPV4 头部分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentPackageNum ++)

/* 增加上行 IPV4 分片包中非头部分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_NON_HEADER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentPackageNum ++)

/* 增加上行 IPV4 分片包中非头部分片查找缺省承载失败包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_NON_HEADER_FIND_DEFT_FAIL_PACK_NUM()\
                    ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4NonHeaderFragmentFindDeftFailedPackageNum ++)


/* 增加上行 IPV4 头部分片匹配信息不完整的分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_HEADER_NO_UPLAYER_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV4_TRANS_INFO_ADDR())->ulIpv4HeaderFragmentNoUpperLayerPackageNum ++)

/* 获取上行 IPV6 分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6FragmentPackageNum)

/* 获取上行丢弃 IPV6 分片包数目 */
#define NAS_ERABM_IPF_OM_GET_RCV_UL_DISCARD_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6DiscardFragmentPackageNum)

/* 增加上行 IPV6 分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6FragmentPackageNum ++)

/* 增加上行丢弃 IPV6 分片包数目 */
#define NAS_ERABM_IPF_OM_ADD_RCV_UL_DISCARD_IPV6_PACK_NUM()\
                ((NAS_ERABM_IPF_OM_GET_UL_IPV6_TRANS_INFO_ADDR())->ulIpv6DiscardFragmentPackageNum ++)
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
 结构名    : NAS_ERABM_UL_IPV4_IP_FRAGMENT_DATA_TRANS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行IPV4分片包传输信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpv4FragmentPackageNum;                           /* IPV4分片包数 */
    VOS_UINT32                          ulIpv4DiscardFragmentPackageNum;                    /* IPV4丢弃分片包数 */
    VOS_UINT32                          ulIpv4HeaderFragmentPackageNum;                     /* IPV4头部分片包数 */
    VOS_UINT32                          ulIpv4NonHeaderFragmentPackageNum;                  /* IPV4非头部分片包数 */
    VOS_UINT32                          ulIpv4NonHeaderFragmentFindDeftFailedPackageNum;    /* IPV4非头部分片包查找缺省承载失败包数 */
    VOS_UINT32                          ulIpv4HeaderFragmentNoUpperLayerPackageNum;         /* IPV4头部分片匹配信息不完整的分片包数 */
}NAS_ERABM_UL_IPV4_IP_FRAGMENT_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERABM_UL_IPV6_IP_FRAGMENT_DATA_TRANS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行IPV6分片包传输信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpv6FragmentPackageNum;                        /* IPV6分片包数 */
    VOS_UINT32                          ulIpv6DiscardFragmentPackageNum;                  /* IPV6丢弃分片包数 */
}NAS_ERABM_UL_IPV6_IP_FRAGMENT_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_ERABM_UL_IP_FRAGMENT_DATA_TRANS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行分片包传输信息
*****************************************************************************/
typedef struct
{
    /* 总的分片数据包数 IPV4 + IPV6分片包 */
    /*VOS_UINT32                                              ulIpFragmentPackageNum;
 */

    NAS_ERABM_UL_IPV4_IP_FRAGMENT_DATA_TRANS_INFO_STRU      stUlIpv4FragmentTransInfo;
    NAS_ERABM_UL_IPV6_IP_FRAGMENT_DATA_TRANS_INFO_STRU      stUlIpv6FragmentTransInfo;
}NAS_ERABM_UL_IP_FRAGMENT_DATA_TRANS_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_ERABM_IPF_STATICS_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : IPF OM 统计信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulIpfUlRcvDataCnt;          /*上行收到的数据个数
 */
    VOS_UINT32              ulIpfUlRcvDataBytes;        /*上行收到的字节数
 */
    VOS_UINT32              ulIpfUlErrorCnt;            /*上行IPF检查错误包个数
 */
    VOS_UINT32              ulIpfUlFragCnt;             /*上行收到IP分片个数
 */
    VOS_UINT32              ulIpfUlDiscardCnt;          /*上行丢弃数据包个数
 */
    VOS_UINT32              ulIpfUlProcBytes;           /*上行IPF处理包字节数,无意义
 */

    VOS_UINT32              ulIpfDlRcvDataCnt;          /*下行收到的数据包个数
 */
    VOS_UINT32              ulIpfDlRcvDataBytes;        /*下行收到的数据包字节数
 */
    VOS_UINT32              ulIpfDlErrorCnt;            /*下行IPF检查错误包个数
 */
    VOS_UINT32              ulIpfDlFragCnt;             /*下行收到IP分片个数
 */
    VOS_UINT32              ulIpfDlDiscardCnt;          /*下行丢弃数据包格式
 */
    VOS_UINT32              ulIpfDlProcBytes;           /*下行IPF处理包字节数
 */

    VOS_UINT32              ulDlNonUsrDataCnt;          /*下行处理非用户数据个数
 */
    VOS_UINT32              ulDlUsrDataCnt;             /*下行处理用户数据个数
 */

    VOS_UINT32              ulIpfTftFilterErr;          /*上行TFT参数转换错误统计
 */
    VOS_UINT32              ulIpfDlFilterErr;           /*下行数据发送错误统计
 */

    VOS_UINT32              ulIpfFilterFull;          /*上行FILTER统计
 */
    NAS_ERABM_UL_IP_FRAGMENT_DATA_TRANS_INFO_STRU stUlIpFfragmentTransInfo; /* 上行分片包传输信息 */
}NAS_ERABM_IPF_STATICS_INFO;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_ERABM_IPF_STATICS_INFO g_stNasERabmIpfOmInfo;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_VOID NAS_ERABM_IpfOmInit( VOS_VOID );


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

