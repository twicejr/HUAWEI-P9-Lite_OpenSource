/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_buf_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面MBUF相关对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_BUF_API_H_
#define _SFE_BUF_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "sfe_buf_pub_api.h"

/* 数据面MBUF模块错误码定义 */
typedef enum enumSfeMbufErrCode
{
    SFE_MBUF_OK = SFE_OK,                         /* 操作成功 */
    SFE_MBUF_ERR_BEGIN = SFE_MBUF_BEGIN_RET_CODE, /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_MBUF_NULL_POINTER_FORWARD,                /* 1  前移指针时,DBD或者DB为空指针 */
    SFE_MBUF_NULL_POINTER_BACKWARD,               /* 2  后移指针时,DBD或者DB为空指针 */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_FORWARD,         /* 3  前移指针时,DB长度不够 */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_BACKWARD,        /* 4  后移指针时,DB长度不够 */
    SFE_MBUF_NULL_POINTER_CREATEBYSYSDB,          /* 5  根据系统DB创建MBUF时传入空指针 */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_CREATEBYSYSDB,  /* 6  根据系统DB创建MBUF时申请MBUF头失败 */
    SFE_MBUF_MALLOC_DBD_FAIL_CREATEBYSYSDB,       /* 7  根据系统DB创建MBUF时申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_DB_LEN_INVALID_CREATEBYSYSDB,        /* 8  根据系统DB创建MBUF时DB长度与DB数据长度不合法 */
    SFE_MBUF_DB_BEGIN_ADDR_INVALID_CREATEBYSYSDB, /* 9  根据系统DB创建MBUF时DB起始地址与DB数据起始地址不合法 */
    SFE_MBUF_DB_END_ADDR_INVALID_CREATEBYSYSDB,   /* 10 根据系统DB创建MBUF时DB结束地址与DB数据结束地址不合法 */
    SFE_MBUF_DB_SOURCE_INVALID_CREATEBYSYSDB,     /* 11 根据系统DB创建MBUF时DB来源不合法 */
    SFE_MBUF_NULL_POINTER_DESTROY,                /* 12 释放MBUF时传入空指针 */
    SFE_MBUF_NULL_POINTER_CAT,                    /* 13 连接两个MBUF传入参数为空指针 */
    SFE_MBUF_NULL_BUFPOINTER_CREATEBYBUF,         /* 14 从buffer拷贝数据创建MBUF时传入的buffer指针为NULL */
    SFE_MBUF_NULL_MBUFPOINTER_CREATE,             /* 15 创建正常MBUF时,传入的存放MBUF地址的输出参数为NULL */
    SFE_MBUF_LEN_INVALID_CREATE,                  /* 16 创建正常MBUF时,传入的预留空间与数据长度之和超过了一个DB的长度 */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_CREATE,         /* 17 创建正常MBUF时,申请MBUF头结构失败 */
    SFE_MBUF_MALLOC_DBD_FAIL_CREATE,              /* 18 创建正常MBUF时,申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_MALLOC_DB_FAIL_CREATE,               /* 19 创建正常MBUF时,申请MBUF数据块DB失败 */
    SFE_MBUF_STRUCT_SIZE_ERR_INIT,                /* 20 数据面初始化时检查MBUF结构体大小不正确 */
    SFE_MBUF_NULL_GETPRIORITY,                    /* 21 获取MBUF中报文优先级时,传入MBUF指针为NULL */
    SFE_MBUF_INPUT_NULL_GETPRIORITY,              /* 22 获取MBUF中报文优先级时,传入存储报文优先级的指针为NULL */
    SFE_MBUF_GET_PRECFG_EXPEND_SIZE_ERR,          /* 23 获取扩展MBUF支持64位系统MBUF扩展信息长度预配置失败 */
    SFE_MBUF_NULL_POINTER_CUTHEAD,                /* 24 从Mbuf的DB链的首部开始删除指定长度的数据时传入空指针 */
    SFE_MBUF_DATA_LEN_NOTENOUGH_CUTHEAD,          /* 25 从Mbuf的DB链的首部开始删除指定长度的数据时总数据长度不够 */
    SFE_MBUF_NULL_POINTER_CUTTAIL,                /* 26 从Mbuf的DB链的尾部开始删除指定长度的数据时传入空指针 */
    SFE_MBUF_DATA_LEN_NOTENOUGH_CUTTAIL,          /* 27 从Mbuf的DB链的尾部开始删除指定长度的数据时总数据长度不够 */
    SFE_MBUF_NULL_POINTER_DELDATA,                /* 28 从MBUF指定位置删除指定长度数据时传入空指针 */
    SFE_MBUF_DATA_LEN_NOTENOUGH_DELDATA,          /* 29 从MBUF指定位置删除指定长度数据时总数据长度不够 */
    SFE_MBUF_NULL_POINTER_CREATEBYCPYMBUF,        /* 30 根据MBUF创建MBUF时传入空指针 */
    SFE_MBUF_LEN_INVALID_CREATEBYCPYMBUF,         /* 31 根据MBUF创建MBUF时长度不合法 */
    SFE_MBUF_DBD_NULL_POINTER_BY_LOCATE_CREATEBYCPYMBUF,  /* 32 根据MBUF创建MBUF时,获取拷贝位置在相应DB结点的偏移时DBD为空 */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_CREATEBYCPYMBUF,/* 33 根据MBUF创建MBUF时申请MBUF头失败 */
    SFE_MBUF_MALLOC_DBD_FAIL_CREATEBYCPYMBUF,     /* 34 根据MBUF创建MBUF时申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_MALLOC_DB_FAIL_CREATEBYCPYMBUF,      /* 35 根据MBUF创建MBUF时申请MBUF数据块DB失败 */
    SFE_MBUF_MALLOC_MBUF_POOL_FAIL,               /* 36 初始化MBUF内存池是失败 */
    SFE_MBUF_LEN_INVALID_CREATECTRLPKT,           /* 37 创建无数据MBUF时,传入的预留空间与数据长度之和超过了一个DB的长度 */
    SFE_MBUF_MBUF_NULL_POINTER_PULLUP,            /* 38 将MBUF起始位置后的指定长度内容放在一连续的内存空间时输入空指针 */
    SFE_MBUF_LEN_FOR_MBUF_INVALID_PULLUP,         /* 39 将MBUF起始位置后的指定长度内容放在一连续的内存空间时传入长度大于数据总长度 */
    SFE_MBUF_LEN_FOR_DBD_INVALID_PULLUP,          /* 40 将MBUF起始位置后的指定长度内容放在一连续的内存空间时传入长度大于首DBD数据可用空间大小 */
    SFE_MBUF_DBD_OR_DB_NULL_POINTER_PULLUP,       /* 41 将MBUF起始位置后的指定长度内容放在一连续的内存空间时DBD或DB指针为空 */
    SFE_MBUF_MBUF_NULL_POINTER_SETUSERPRVT,       /* 42 设置产品自有信息到MBUF时MBUF指针为空 */
    SFE_MBUF_PTRANDLEN_NOTMATCH_SETUSERPRVT,      /* 43 设置产品自有信息到MBUF时自有数据指针与长度不匹配,即长度非零,但指针为空 */
    SFE_MBUF_DATALEN_INVAILD_SETUSERPRVT,         /* 44 设置产品自有信息到MBUF时自有数据长度大于最大值 */
    SFE_MBUF_INPUT_NULL_POINTER_GETUSERPRVT,      /* 45 获取产品自有信息到MBUF时输入指针为空 */
    SFE_MBUF_MBUF_NULL_POINTER_INSERTDATA,        /* 46 在MBUF指定位置插入指定长度数据时输入MBUF空指针 */
    SFE_MBUF_DTAT_LENORPTR_INVALID_INSERTDATA,    /* 47 在MBUF指定位置插入指定长度数据时输入的数据长度为０或指针为空 */
    SFE_MBUF_STARTPOS_INVALID_INSERTDATA,         /* 48 在MBUF指定位置插入指定长度数据时指定位置非法(大于数据总长度) */
    SFE_MBUF_MALLOC_DBD_INVALID_INSERTDATA,       /* 49 在MBUF指定位置插入指定长度数据时DBD异常 */
    SFE_MBUF_MALLOC_DBD_1_FAIL_INSERTDATA,        /* 50 在MBUF指定位置插入指定长度数据时位置一申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_MALLOC_DBD_2_FAIL_INSERTDATA,        /* 51 在MBUF指定位置插入指定长度数据时位置二申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_MALLOC_DBD_3_FAIL_INSERTDATA,        /* 52 在MBUF指定位置插入指定长度数据时位置三申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_MALLOC_DB_1_FAIL_INSERTDATA,         /* 53 在MBUF指定位置插入指定长度数据时位置一申请MBUF数据块DB失败 */
    SFE_MBUF_MALLOC_DB_2_FAIL_INSERTDATA,         /* 54 在MBUF指定位置插入指定长度数据时位置二申请MBUF数据块DB失败 */
    SFE_MBUF_MALLOC_DB_3_FAIL_INSERTDATA,         /* 55 在MBUF指定位置插入指定长度数据时位置三申请MBUF数据块DB失败 */
    SFE_MBUF_NULL_POINTER_GETTAIL,                /* 56 从Mbuf的DB链的尾部开始获取指定长度的数据时传入空指针 */
    SFE_MBUF_DATA_LEN_INVAILD_GETTAIL,            /* 57 从Mbuf的DB链的尾部开始获取指定长度的数据时总数据长度不够或指定长度为0 */
    SFE_MBUF_MBUF_NULL_POINTER_REPLACEDATA,       /* 58 在MBUF指定位置替换指定长度数据时输入MBUF空指针 */
    SFE_MBUF_DTAT_LENORPTR_INVALID_REPLACEDATA,   /* 59 在MBUF指定位置替换指定长度数据时输入的数据长度为０或指针为空 */
    SFE_MBUF_STARTPOS_INVALID_REPLACEDATA,        /* 60 在MBUF指定位置替换指定长度数据时指定位置非法(大于数据总长度) */
    SFE_MBUF_MALLOC_DBD_INVALID_REPLACEDATA,      /* 61 在MBUF指定位置替换指定长度数据时DBD异常 */
    SFE_MBUF_INPUT_NULL_POINTER_FRAGMENT,         /* 62 在拆分Mbuf时输入空指针 */
    SFE_MBUF_INPUT_LEN_INVALID_FRAGMENT,          /* 63 在拆分Mbuf时输入的分片长度为0或预留长度非法 */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_FRAGMENT,       /* 64 在拆分Mbuf时申请MBUF头失败 */
    SFE_MBUF_MALLOC_DBD_FAIL_FRAGMENT,            /* 65 在拆分Mbuf时申请MBUF数据块描述符DBD失败 */
    SFE_MBUF_MALLOC_DB_FAIL_FRAGMENT,             /* 66 在拆分Mbuf时申请MBUF数据块DB失败 */
    SFE_MBUF_DBD_INVAILD_FRAGMENT,                /* 67 在拆分Mbuf时DBD非法 */
    SFE_MBUF_FAIL_MAKE_MEMORY_CONTINUOUS,         /* 68 使MBUF头部连续的宏,调用失败 */
    SFE_MBUF_GET_PRECFG_POOL_INIT_NUM_ERR,        /* 69 获取扩展MBUF支持64位系统MBUF初始资源池大小预配置失败 */
    SFE_MBUF_DBD_NULL_POINTER_BY_COPY_CREATEBYCPYMBUF,  /* 70 根据MBUF创建MBUF时,拷贝数据时DBD为空 */

    SFE_MBUF_MBUF_NULL_POINTER_MODIFY_PKTLEN,     /* 71 修改MBUF报文长度时,输入MBUF空指针 */
    SFE_MBUF_LEN_INVALID_MODIFY_PKTLEN,           /* 72 修改MBUF报文长度时,传入的数据长度与预留空间之和超过了一个DB的长度 */
    SFE_MBUF_MBUF_NULL_POINTER_SETUSERPRVTLEN,    /* 73 设置产品自有信息长度到MBUF时MBUF指针为空 */
    SFE_MBUF_DATALEN_INVAILD_SETUSERPRVTLEN,      /* 74 设置产品自有信息长度到MBUF时自有数据长度大于最大值 */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_TAIL_FORWARD,    /* 75 TCP重排时需要把重复数据长度偏移掉,还原时,发现当前DB空间不足 */
    SFE_MBUF_NULL_POINTER_TAIL_FORWARD,           /* 76 TCP重排时需要把重复数据长度偏移掉,还原时,DBD或者DB为空指针 */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_TAIL_BACKWARD,   /* 77 TCP重排时需要把重复数据长度偏移掉时,发现当前DB空间不足 */
    SFE_MBUF_NULL_POINTER_TAIL_BACKWARD,          /* 78 TCP重排时需要把重复数据长度偏移掉时,DBD或者DB为空指针 */

    SFE_MBUF_FREE_NULL_ONESEG_MBUF,               /* 79 释放一段式MBUF的头时，传入的指针为空*/
    SFE_MBUF_REPET_FREE_ONESEG_MBUF,              /* 80 重复释放一段式MBUF的头*/
    SFE_MBUF_REPET_FREE_ONESEG_DBD,               /* 81 重复释放一段式MBUF的DBD*/
    SFE_MBUF_REPET_FREE_ONESEG_DB,                /* 82 重复释放一段式MBUF的DB*/
    SFE_MBUF_REPET_FREE_ONESEG_SYSDB,             /* 83 重复释放一段式MBUF的SYSDB*/
    SFE_MBUF_MULTI_DBD_MODIFY_PKTLEN,             /* 84 修改MBUF报文长度时,输入的MBUF的DBD个数不唯一 */
    SFE_MBUF_GET_POOLUNITNUM_BEFORE_INIT,         /* 85 在系统初始化前,不能获取到MBUF资源池统计 */
    SFE_MBUF_GET_POOLUNITNUM_INPUT_PARA_INVALID,  /* 86 获取MBUF资源池统计时,输入的参数判断失败 */
    SFE_MBUF_GET_POOLUNITNUM_INPUT_FAILED,        /* 87 获取MBUF资源池统计时,获取到的空闲单元数非法*/
}SFE_MBUF_ERR_CODE_E;


/* 用户创建MBUF时最小预留长度 */
#define SFE_MBUF_DB_MIN_RESERVE_SPACE 128


/*******************************************************************************
*    Func Name: SFE_MBUF_CreateBySysDB
* Date Created: 2009-7-28
*       Author: wangmingxia/luowentong
*      Purpose: 根据系统DB创建MBUF
*  Description: 根据系统DB创建MBUF
*        Input: SFE_MBUF_DATABLOCKDESCRIPTOR_S **ppstDBDAddr: 存放数据块描述符DBD起始地址<非空指针>
*               UINT8 *pu8DBAddr: DB起始地址<非空指针>
*               UINT32 u32DBLen: DB长度<无符号32位值>
*               UINT8 *pu8DataAddr: DB中数据起始地址<非空指针>
*               UINT32 u32DataLen: DB中数据长度<无符号32位值>
*               VOID  *pstSysDBCtrl: 系统DB对应的控制块, 可选<非空指针>
*               UINT32 u32DataSource: DB来源<无符号32位值>
*               UINT32 u32ModuleID: 模块ID, 低16bit留给产品使用<无符号32位值>
*       Output: SFE_MBUF_S **ppstMbuf: 存放构造好的MBUF地址<非空指针>
*       Return: 成功:0
*               失败:其它
*      Caution: Important points if any
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                            DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-28   wangmingxia/luowentong          Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_CreateBySysDB(SFE_MBUF_S **ppstMbuf, SFE_MBUF_DATABLOCKDESCRIPTOR_S **ppstDBDAddr,
                                     UINT8 *pu8DBAddr, UINT32 u32DBLen,
                                     UINT8 *pu8DataAddr, UINT32 u32DataLen,
                                     VOID  *pstSysDBCtrl,
                                     UINT32 u32DataSource,
                                     UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_CreateByCopyBuffer
* Date Created: 2009-9-12
*       Author: w60786/h00121208
*      Purpose: 拷贝数据创建MBUF
*  Description: 拷贝数据创建MBUF
*        Input: UINT32 u32ReserveHeadSpace: MBUF数据块头部预留的空间长度,<无符号32位值>
*               产品在创建MBUF时必须预留足够长度用于VISP协议栈处理时添加头部信息.如128字节.
*               UINT32 u32DataLength: 缓存数据长度<无符号32位值>
*               UINT8 *pu8DataBuffer: 缓存地址<非空指针>
*               UINT32 u32ModuleID: 调用此函数的模块号<无符号32位值>
*       Output: SFE_MBUF_S **ppstMbuf: 成功时返回新创建的MBUF地址<非空指针>
*       Return: 成功:0
*               失败:其它
*      Caution: 1.产品创建MBUF时必须指定预留长度.
*                 预留的长度必须大于协议栈处理需要添加的头部长度,建议预留128字节。
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_CreateByCopyBuffer(SFE_MBUF_S **ppstMbuf, UINT32 u32ReserveHeadSpace,
                                          UINT32 u32DataLength, UINT8 *pu8DataBuffer, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_CreateForControlPacket
* Date Created: 2009-9-12
*       Author: w60786/h00121208
*      Purpose: 创建指定长度的无数据MBUF
*  Description: 创建指定长度的无数据MBUF
*        Input: UINT32 u32ReserveHeadSpace: MBUF数据块头部预留的空间长度<无符号32位值>
*               UINT32 u32DataLength: 创建MBUF之后将要填充的数据长度<无符号32位值>
*               UINT32 u32ModuleID: 调用此函数的模块号<无符号32位值>
*       Output: SFE_MBUF_S **ppstMbuf: 成功时返回新创建的MBUF地址<非空指针>
*       Return: 成功:0
*               失败:其它
*      Caution: 1.产品创建MBUF时必须指定预留长度.
*                 预留的长度必须大于协议栈处理需要添加的头部长度,建议预留128字节。
*               2.该接口只支持创建一个DB的无数据MBUF。
*               3.产品在使用该接口创建无数据的MBUF后,产品向该MBUF中填写的数据长度一定要与创建MBUF
*                 时指定的长度相等.如果不相等则必须调用SFE_MBUF_ModifyControlPacketLen接口修改
*                 MBUF中记录的数据长度。
*    Reference: SFE_MBUF_CreateBySysDB
*               SFE_MBUF_CreateByCopyBuffer
*               SFE_MBUF_Destroy
*               SFE_MBUF_ModifyControlPacketLen
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_CreateForControlPacket(SFE_MBUF_S **ppstMbuf, UINT32 u32ReserveHeadSpace,
                                              UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_ModifyControlPacketLen
* Date Created: 2009-9-12
*       Author: w60786/h00121208
*      Purpose: 修改使用SFE_MBUF_CreateForControlPacket接口创建的MBUF中记录的数据长度.
*  Description: 修改使用SFE_MBUF_CreateForControlPacket接口创建的MBUF中记录的数据长度.
*        Input: SFE_MBUF_S *pstMbuf: MBUF指针<非空指针>
*               UINT32 u32DataLength: MBUF中当前存储的数据长度<32位无符号整数>
*               UINT32 u32ModuleID: 调用此函数的模块号<32位无符号整数>
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: 1.产品必须保证传入的MBUF只能是通过SFE_MBUF_CreateForControlPacket接口创建的MBUF。
*               2.产品必须保证传入的MBUF中有且只有一个DB。
*    Reference: SFE_MBUF_CreateForControlPacket
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_ModifyControlPacketLen(SFE_MBUF_S *pstMbuf, UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_Destroy
* Date Created: 2009-8-11
*       Author: w60786
*      Purpose: MBUF释放函数
*  Description: MBUF释放函数
*        Input: SFE_MBUF_S *pstMBuf: 待释放的MBUF<非空指针>
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: Important points if any
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                            DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-11    wangmingxia/luowentong          Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_Destroy(SFE_MBUF_S *pstMBuf);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetPktPriority
* Date Created: 2009-11-7
*       Author: w60786
*      Purpose: 获取MBUF中报文优先级
*  Description: 获取MBUF中报文优先级
*        Input: SFE_MBUF_S *pstMBuf: 报文MBUF指针<非空指针>
*       Output: UINT32 *pu32PktPriority: 报文优先级 <非空指针>
*       Return: 成功:0
*               失败:其它
*      Caution:
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-7    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_GetPktPriority(SFE_MBUF_S *pstMBuf, UINT32 *pu32PktPriority);

/*******************************************************************************
*    Func Name: SFE_MBUF_InsertData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 在MBUF指定位置插入指定长度数据
*  Description: 在MBUF指定位置插入指定长度数据
*        Input: SFE_MBUF_S *pstMbuf:  待插入数据的MBUF<非空指针>
*               UINT32 u32StartPo:    待插入的数据在MBUF中的起始存储位置<[0,Mbuf数据长度]>
*               UINT8 *pu8DataBuffer: 待插入数据缓冲区<非空指针>
*               UINT32 u32DataLength: 待插入的数据长度<32位无符号整数>
*               UINT32 u32ModuleID:   模块ID<32位无符号整数>
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: 1.调用该接口后数据起始指针可能会发生变化,所以如果在该接口调用之后用户
*                 希望访问MBUF中的数据,则必须重新获取数据的起始地址.
*    Reference: SFE_MBUF_DeleteData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_GetTailData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_InsertData(SFE_MBUF_S *pstMbuf, UINT32 u32StartPos, UINT8 *pu8DataBuffer,
                           UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_DeleteData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 在MBUF指定位置删除指定长度数据
*  Description: 在MBUF指定位置删除指定长度数据
*        Input: SFE_MBUF_S *pstMbuf:  待删除数据的MBUF<非空>
*               UINT32 u32StartPo:    待删除数据的起始位置<[0,Mbuf数据长度]>
*               UINT32 u32DataLength: 待删除的数据长度<32位无符号整数>
*               UINT32 u32ModuleID:   模块ID<32位无符号整数>
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: 1.调用该接口后数据起始指针可能会发生变化,所以如果在该接口调用之后用户
*                 希望访问MBUF中的数据,则必须重新获取数据的起始地址.
*    Reference: SFE_MBUF_DeleteData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_GetTailData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_DeleteData(SFE_MBUF_S *pstMbuf, UINT32 u32StartPos,
                           UINT32 u32DataLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_ReplaceData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 在MBUF指定位置替换指定长度数据
*  Description: 在MBUF指定位置替换指定长度数据
*        Input: SFE_MBUF_S *pstMbuf:  待替换数据的MBUF<非空指针>
*               UINT32 u32StartPo:    待替换的数据在MBUF中的起始存储位置<[0,Mbuf数据长度]>
*               UINT8 *pu8DataBuffer: 待替换数据缓冲区<32非空指针
*               UINT32 u32DataLength: 待替换的数据长度<32位无符号整数>
*               UINT32 u32ModuleID:   模块ID<32位无符号整数>
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution:
*    Reference: SFE_MBUF_DeleteData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_GetTailData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_ReplaceData(SFE_MBUF_S *pstMbuf, UINT32 u32StartPos,
                            UINT8 *pu8DataBuffer, UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_Fragment
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 将一个MBUF拆分成多个MBUF
*  Description: 将一个MBUF拆分成多个MBUF
*        Input: SFE_MBUF_S *pstOriginMbuf:      要拆分的原始MBUF报文<非空指针>
*               UINT32 u32ReserveLen:           在每个MBuf 第一个DB头部预留的长度<32位无符号整数>
*               UINT32 u32FragLen:              要拆分的数据长度<非0,32位无符号整数>
*               UINT32 u32ModuleID:             模块ID<32位无符号整数>
*       Output: SFE_MBUF_S **ppstFragMbufChain: 拆分后的MBuf链表头<非空指针>
*       Return: 成功:0
*               失败:其它
*      Caution: 1.按照指定的长度拆分MBUF，在拆分后新的MBUF 第一个DB头部预留指定的长度。
*               2.拆分后的最后一个MBUF大小可能小于指定的拆分长度。
*               3.该函数无论返回成功还是失败,该函数都不会释放原始的报文MBUF,报文由调用者负责释放.
*               4.如果原始报文的长度小于等于需要分片的长度则返回失败.产品调用该函数时要保证原始报文
*                 长度要比分片长度大.
*    Reference: SFE_MBUF_Concatenate
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_Fragment(SFE_MBUF_S *pstOriginMbuf, SFE_MBUF_S **ppstFragMbufChain,
                         UINT32 u32ReserveLen, UINT32 u32FragLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_Concatenate
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 合并两个MBUF，将一个MBUF中的数据连接到另一个MBUF的后面
*  Description: 合并两个MBUF，将一个MBUF中的数据连接到另一个MBUF的后面
*        Input: SFE_MBUF_S *pstDstMbuf: 目的MBUF<非空>
*               SFE_MBUF_S *pstSrcMbuf: 要合并的MBUF
*               UINT32 u32ModuleID:     模块ID
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution:
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_Concatenate(SFE_MBUF_S *pstDstMbuf, SFE_MBUF_S *pstSrcMbuf, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_SetUserPrivateData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 设置产品自有信息到MBUF中
*  Description: 设置产品自有信息到MBUF中
*        Input: SFE_MBUF_S *pstMbuf: MBUF报文<非空>
*               UINT8 *pu8DataBuf:   产品自有数据起始地址
*               UINT32 u32DataLen:   数据长度<[0,64]>
*               UINT32 u32ModuleID:  模块ID<32位无符号整数>
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: 
*    Reference: SFE_MBUF_SetUserPrivateDataLen
*               SFE_MBUF_GetUserPrivateBufInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_SetUserPrivateData(SFE_MBUF_S *pstMbuf, UINT8 *pu8DataBuf,
                                   UINT32 u32DataLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetUserPrivateBufInfo
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 获取报文中的产品自有信息
*  Description: 获取报文中的产品自有信息
*        Input: pstMbuf: MBUF报文<非空>
*       Output: ppu8UserBufAddr MBUF中存放产品自有数据缓存的起始地址
*               pu32UserBufLen: MBUF中存放产品自有数据缓存的长度<[0,64]>
*               pu32UserDataLen: MBUF中存放的实际自有数据长度
*       Return: 成功:0
*               失败:其它
*      Caution: 1.用户必须保证在操作私有缓存时不能越界,不能超过最大长度*pu32UserBufLen
*               2.用户使用SFE_MBUF_GetUserPrivateBufInfo获取用户私有缓存并向其填写数据后,
*                 必须调用SFE_MBUF_SetUserPrivateDataLen接口将自有数据长度设置到MBUF中.
*    Reference: SFE_MBUF_SetUserPrivateDataLen
*               SFE_MBUF_GetUserPrivateBufInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_GetUserPrivateBufInfo(SFE_MBUF_S *pstMbuf, UINT8 **ppu8UserBufAddr,
                                      UINT32 *pu32UserBufLen, UINT32 *pu32UserDataLen);

/*******************************************************************************
*    Func Name: SFE_MBUF_SetUserPrivateDataLen
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 设置报文中的产品实际自有数据长度
*  Description: 设置报文中的产品实际自有数据长度
*        Input: SFE_MBUF_S *pstMbuf: MBUF报文<非空>
*               UINT32 u32UserDataLen: MBUF中存放的实际自有数据长度
*       Output: 
*       Return: 成功:0
*               失败:其它
*      Caution: 用户必须保证设置的长度参数合法,不能超过MBUF中的产品私有缓存最大长度
*    Reference: SFE_MBUF_GetUserPrivateBufInfo
*               SFE_MBUF_SetUserPrivateData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_SetUserPrivateDataLen(SFE_MBUF_S *pstMbuf, UINT32 u32UserDataLen);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetTailData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: 获取MBUF尾部指定长度的数据
*  Description: 获取MBUF尾部指定长度的数据
*        Input: SFE_MBUF_S *pstMbuf: MBUF报文<非空>
*               UINT32 u32DataLen: 要获取的尾部数据长度 <32位无符号整数>
*               UINT32 u32ModuleID:  模块ID<32位无符号整数>
*       Output: UINT8 *pu8DataBuf: 存放获取数据的缓冲区,产品必须保证缓冲区至少有u32DataLen大<非空指针>
*       Return: 成功:0
*               失败:其它
*      Caution:
*    Reference: SFE_MBUF_InsertData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_DeleteData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_GetTailData(SFE_MBUF_S *pstMbuf, UINT8 *pu8DataBuf, UINT32 u32DataLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetPoolTotalAndFreeUnitNum
* Date Created: 2011-07-26
*       Author: zhukun 00166124 
*      Purpose: 获取MBUF资源池总的和剩余的单元数
*  Description: 获取MBUF资源池总的和剩余的单元数
*        Input: 
*       Output: UINT32 *pu32TotalUnitNum: MBUF资源池总的单元数
*               UINT32 *pu32FreeUnitNum: MBUF资源池剩余的单元数
*       Return: 成功:SFE_MBUF_OK
*               失败:错误码
*      Caution: 1.MBUF资源池总单元数为初始化配置值加上为网卡预留的单元数SFE_MBUF_RESERVE_MBUF_NUM
*               2.该接口要在系统启动完成后调用才能生效
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-26   zhukun 00166124         Create
*
*******************************************************************************/
UINT32 SFE_MBUF_GetPoolTotalAndFreeUnitNum(UINT32 *pu32TotalUnitNum, UINT32 *pu32FreeUnitNum);

#ifdef  __cplusplus
}
#endif

#endif


