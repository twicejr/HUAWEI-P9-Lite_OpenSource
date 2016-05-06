/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : sm_simulator_mbuf.h
  版 本 号   : 初稿
  作    者   : m60687
  生成日期   : Sat Mar 02 10:15:17 2013
  最近修改   :
  功能描述   : MBUF相关处理

  修改历史   :
  1.日    期   : Sat Mar 02 10:15:17 2013
    作    者   : mengguangxin 60687
    修改内容   : 创建文件

****************************************************************************/
#ifndef _SM_SIMULATOR_MBUF_H_
#define _SM_SIMULATOR_MBUF_H_

/* 目前UE不需要用到500块4K的内存，为了不影响原来逻辑和节省内存开销将其修改为10块 */
#if 0
#define SM_PGPADAPT_MBUF_MAX_NUM                   500
#endif
#define SM_PGPADAPT_MBUF_MAX_NUM                   10

#define     SM_PGPADAPT_DATABLOCK_MAX_LENGTH            4096
#define MBUF_TOO_SMALL_LENGTH 500
#define PMBUF_DATA_SIZE 2048         /* 包括为转发面预留的512字节 */
#define MBUF_TRANSMIT_RESERVED_SIZE 512 /* 为转发面预留的512字节 */

#define PMBUF_TRANSMIT_RESERVED_SIZE   MBUF_TRANSMIT_RESERVED_SIZE

#define SM_PGPADAPT_MBUF_CORR_PKTID_MAX_NUM      5000

#define     SM_PGP_MBUF_DATABLOCK_OFFSET                512
#define     SM_PGP_MBUF_DATABLOCK_MAX_LEN               3232

#define SOFT_PMBUF_MAX_NUM_SHIFT_NUM 10 /*1024个软件PMbuf*/
#define SOFT_PMBUF_MAX_NUM (1<<SOFT_PMBUF_MAX_NUM_SHIFT_NUM)
#define SOFT_PMBUF_HIGH_THRESHOLD (SOFT_PMBUF_MAX_NUM - 1)


#define SM_MBUF_USERTAGDATA_S  MBUF_USERTAGDATA_S

#define SM_MBUF_ADD_HEAD(pstMBufM, ulLengthM)\
do{\
    if( (pstMBufM) != VOS_NULL_PTR )\
    {\
        (pstMBufM)->stDataBlockDescriptor.pucData -= (ulLengthM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataLength += (ulLengthM);\
        (pstMBufM)->ulTotalDataLength += (ulLengthM);\
    }\
}while(0)


/*-------------------------- BEGIN: Mbuf ------------------------------------*/
#define PMBUF_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PMBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)(pstMBufM)->stDataBlockDescriptor.pucData)

/* VOS能申请的最大内存为2k,但是MBUF头保留字节长度为256,因此能一次能传最长为2000-256字节 */
#define PMBUF_MAX_AVAILABLE_MEM_SIZE    (1744)


#define PMBUF_TAILING_SPACE(pstMBufM) \
    ((pstMBufM)->stDataBlockDescriptor.pucDataBlock + (pstMBufM)->stDataBlockDescriptor.ulDataBlockLength \
        - (pstMBufM)->stDataBlockDescriptor.pucData - (pstMBufM)->stDataBlockDescriptor.ulDataLength)

typedef struct tagMBUF_USERTAGDATA_S
{
    VOS_UINT32 ulVrfIndex;
    VOS_UINT32 ulIfIndex;
} MBUF_USERTAGDATA_S;


#define PMBUF_S_RES_SIZE 4

typedef struct tagMBUF_DataBlockDescriptor
{
    VOS_UINT32                          ulDataLength;                           /* 数据块中数据的长度，取值范围[0, ulDataBlockLength]*/
    VOS_UINT8                          *pucData;                                /* 数据块中数据的起始地址, [pucDataBlock + 512, pucDataBlock + ulDataBlockLength]*/
    VOS_UINT32                          ulDataBlockLength;                      /* 数据块的总长度,*/
    VOS_UINT8                          *pucDataBlock;                           /* 数据块的起始地址， NULL表示无效，其他表示有效 */
    VOS_UINT32                          ulType;                                 /* MBUF_TYPE_XXX */
    struct tagMBUF_DataBlockDescriptor *pstNextDataBlockDescriptor;             /* 下一个数据块描述符， Always NULL*/
}MBUF_DATABLOCKDESCRIPTOR_S,SM_MBUF_DATABLOCKDESCRIPTOR_S;          /* 数据块描述符数据结构 */

typedef struct tagMBuf
{
    struct tagMBuf *                    pstNextMBuf;                            /* 下一个mbuf， NULL表示无效，其他表示有效 */
    VOS_UINT32                          ulTotalDataLength;                      /* mbuf 中数据的总长度，同一个MBUF中的所有数据的长度和 */
    MBUF_DATABLOCKDESCRIPTOR_S         stDataBlockDescriptor;                  /* Mbuf 数据描述信息 */
    VOS_UINT32                          ulDataBlockNumber;                      /* mbuf 中数据块的个数 */
    MBUF_USERTAGDATA_S                  stUserTagData;                          /* Mbuf 控制信息 */
    VOS_UINT32                          ulResv[PMBUF_S_RES_SIZE-1];             /* 空出4个字节存速率模式 */
    VOS_UINT8                           ucRatMode;                              /* 速率模式 */
    VOS_UINT8                           aucResv[3];
    VOS_UINT32                          ulMagicWord;
}MBUF_S, PMBUF_S, SM_MBUF_S, TP_PMBUF_S;                                 /* mbuf的头标签数据结构 */


#define MBUF_TRANSMIT_USED_SIZE 128  /* 为转发面使用的128字节 */
#define MBUF_FAIL ((VOS_UINT32)1)
#define MBUF_OK ((VOS_UINT32)0)
#define PMBUF_OK    MBUF_OK
#define PMBUF_FAIL  MBUF_FAIL
#define PMBUF_MBUF_SIZE             ((sizeof(PMBUF_S)+(32-1))&~(32-1))
#define MBUF_INDEX_MAGIC_SIZE       32 /*mbuf索引和magic大小，各4个字节*/
#define MBUF_TOTAL_SIZE         (3*1024+512-64)//BSP_GetMakeFileMbufTotalLen()
#define MBUF_DATA_MAXLEN    (MBUF_TOTAL_SIZE - PMBUF_MBUF_SIZE - MBUF_TRANSMIT_RESERVED_SIZE - MBUF_INDEX_MAGIC_SIZE)    /* MBUF数据段长度限制 0xaa0*/
#define PMBUF_DATA_MAXLEN                         MBUF_DATA_MAXLEN

#define PMBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )
#define PMBUF_GET_DATA_BLOCK_DESC(pstMBufM) ( & ( (pstMBufM)->stDataBlockDescriptor) )
#define PMBUF_DBD_OFFSET ((VOS_UINT_PTR)(&((PMBUF_S*)(0))->stDataBlockDescriptor))
#define PMBUF_GET_PMBUF_FROM_DBD(_DataBlockDescriptor) ((PMBUF_S*)((VOS_UINT32)(_DataBlockDescriptor) - PMBUF_DBD_OFFSET))
#define FWD_GET_PMBUF_FROM_DBD(pDataBlockDescriptor) \
    ((PMBUF_S *)(((PF_UCHAR*)pDataBlockDescriptor) - offsetof(PMBUF_S, stDataBlockDescriptor)))



#define PMBUF_PREPEND_MEMORY_SPACE(pstMBufM, ulLengthM, ulModuleIDM, ulResultM) \
do{ \
    PMBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor; \
\
    if ( (pstMBufM) != NULL) \
    { \
        pstDataBlockDescriptor = (PMBUF_DATABLOCKDESCRIPTOR_S *)&( (pstMBufM)->stDataBlockDescriptor ); \
        if ((ulLengthM) > ((VOS_UINT_PTR)(pstDataBlockDescriptor->pucData) -\
            (VOS_UINT_PTR)(pstDataBlockDescriptor->pucDataBlock) - \
             MBUF_TRANSMIT_USED_SIZE)) \
        { \
            (ulResultM) = MBUF_FAIL; \
        }\
        else \
        { \
            pstDataBlockDescriptor->pucData -= (ulLengthM); \
            pstDataBlockDescriptor->ulDataLength += (ulLengthM); \
            (pstMBufM)->ulTotalDataLength += (ulLengthM); \
            (ulResultM) = MBUF_OK; \
        }  \
    }else \
    { \
        (ulResultM) = MBUF_FAIL; \
    } \
}while(0)

#define MBUF_MBUF_SIZE ((sizeof(MBUF_S)+(32-1))&~(32-1))
#define MBUF_TYPE_DATA  1


#define MBUF_CREATE_BY_DATA_BLOCK(pstMBufM, pucDataBlockM, ulDataBlockLengthM,  pucDataM, \
    ulDataLengthM, ulReceiveIfnetIndexM, ulModuleIDM)\
do{\
    (pstMBufM) = PPP_Malloc(MBUF_MBUF_SIZE);\
    if( (pstMBufM) != NULL)\
    {\
        (pstMBufM)->stDataBlockDescriptor.pstNextDataBlockDescriptor = NULL;\
        (pstMBufM)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufM)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufM)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;/*???*/\
        PPP_MemSet( (VOID *) (& pstMBufM->stUserTagData), 0 , sizeof(MBUF_USERTAGDATA_S));\
        (pstMBufM)->ulTotalDataLength = (ulDataLengthM);\
        (pstMBufM)->ulDataBlockNumber = 1;\
        (pstMBufM)->pstNextMBuf = NULL;\
    }\
}while(0)

#define PMBUF_MAKE_MEMORY_CONTINUOUS(pstMBufM, ulLengthM, ulModuleIDM, ulResultM) \
do{\
    if( (pstMBufM) != NULL )\
    {\
        if( (pstMBufM)->stDataBlockDescriptor.ulDataLength < (ulLengthM) )\
        {\
            (ulResultM) = PMBUF_PullUp( (pstMBufM), (ulLengthM), (ulModuleIDM) );\
        }\
        else\
        {\
            (ulResultM) = MBUF_OK;\
        }\
    }\
    else\
    {\
        (ulResultM) = MBUF_FAIL;\
    }\
}while(0)


#define PMBUF_GET_DATA_BLOCK_DESC_INFO(pstDataBlockDescriptorM, pucDataM, ulDataLengthM, pstNextDataBlockDescriptorM)\
do{\
    (pucDataM) = (pstDataBlockDescriptorM)->pucData;\
    (ulDataLengthM) = (pstDataBlockDescriptorM)->ulDataLength;\
    (pstNextDataBlockDescriptorM) = (pstDataBlockDescriptorM)->pstNextDataBlockDescriptor;\
}while(0)

/* Mbuf申请、释放及检查信息begin */
typedef struct tagSmPgpAdaptPacketInfo
{
    MBUF_S*  pstMbuf;
    SM_ULONG ulPacketId;
}SM_PGPADAPT_PACKET_INFO_S;

#define FWD_COMMCHANNEL_SIZE    sizeof(FWD_COMCHANNEL_S)

enum
{
    PMBUF_ERR = 1,
    PMBUF_REFREE,
    PMBUF_REUSED,
#ifndef __VXWORKS_PLATFORM__
    PMBUF_BDQ_FULL,
    PMBUF_POOL_FULL,
    PMBUF_PKT_ERR,
#endif
};

typedef struct tagSmPgpAdaptMbuf
{
    MBUF_S    stMbuf;
    SM_UCHAR  aucDataBlock[SM_PGPADAPT_DATABLOCK_MAX_LENGTH];
    SM_ULONG  ulUsed;
    SM_ULONG  ulMID;
    SM_ULONG  ulDataBlockMallocNum;
    SM_ULONG  ulDataBlockFreeNum;
}SM_PGPADAPT_MBUF_S;


typedef struct tagSmPgpAdaptMbufInfo
{
    SM_PGPADAPT_MBUF_S   astPgpAdaptMbuf[SM_PGPADAPT_MBUF_MAX_NUM];
    SM_ULONG ulMbufMallocNum;
    SM_ULONG ulMbufFreeNum;
}SM_PGPADAPT_MBUF_INFO_S;

typedef struct tagSmPgpAdaptMbufCheckResult
{
    SM_BOOL  bIfMbufMallocEqualFree;
    SM_ULONG ulMbufMallocNum;
    SM_ULONG ulMbufFreeNum;
    SM_ULONG ulMbufUsedNum;
    SM_ULONG ulMbufErrNum;  /* 申请的DataBlock数和释放的数目不等 */
    SM_ULONG ulMbufExistRelationNum;  /*Mbuf和Packet Id的对应关系没有被清除 */
}SM_PGPADAPT_MBUF_CHECK_RESULT_S;

extern SM_ULONG sm_plt_concatenateMbuf(SM_MBUF_S * pstDestinationMBuf, SM_MBUF_S * pstSourceMBuf, SM_ULONG ulModuleID);

extern SM_MBUF_S* sm_plt_createForControlPacket(SM_ULONG ulReserveHeadSpace, SM_ULONG ulLength,
                                                SM_ULONG ulType, SM_ULONG ulModuleID);

extern SM_UCHAR *sm_plt_AppendMemorySpace(SM_MBUF_S * pstMBuf, SM_ULONG ulLength, SM_ULONG ulModuleID);


SM_VOID _pgpAdapt_clearMbufInfo
(
    IN      SM_PGPADAPT_MBUF_CHECK_RESULT_S*  pstMbufCheckResult
);

SM_VOID _pgpAdapt_reportMbufFailureInfo
(
    IN      SM_PGPADAPT_MBUF_CHECK_RESULT_S* pstResult,
    IN      SM_VOID* pFile
);

SM_BOOL _pgpAdapt_checkMbufInfo
(
    OUT  SM_PGPADAPT_MBUF_CHECK_RESULT_S* pstResult
);

SM_VOID sm_pgpAdapt_releaseMbuf
(
    IN  MBUF_S*     pstMBuf
);

MBUF_S* sm_pgpAdapt_getMbuf
(
    IN      SM_ULONG ulMID
);

VOS_UINT32 PMBUF_CopyDataFromBufferToPMBuf(SM_MBUF_S * pstMBuf, VOS_UINT32 ulOffset,
                              VOS_UINT32 ulLength, UCHAR * pucBuffer, VOS_UINT32 ulModuleID);

VOS_UINT32 sm_plt_neatConcatenateMbuf(SM_MBUF_S * pstDestinationMBuf, SM_MBUF_S * pstSourceMBuf,
                                 SM_MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor,
                                 SM_ULONG ulModuleID);

VOS_UINT32 PMBUF_CopyDataFromPMBufToBuffer(SM_MBUF_S * pstMBuf, VOS_UINT32 ulOffset, VOS_UINT32 ulLength, UCHAR * pucBuffer);

PMBUF_S *PMBUF_GetPMbuf(VOS_UINT32 ulSubMod, VOS_UINT32 ulLen);

VOS_UINT32 PMBUF_Destroy(PMBUF_S * pstMbuf);

MBUF_DATABLOCKDESCRIPTOR_S *PMBUF_GetNextDataBlock
(
    VOS_UINT32                               ulSubMod,
    VOS_UINT32                               ulDataBlockLen,
    VOS_UINT32                              *pulBlockNum
);

VOS_UINT32 PMBUF_DataBlockDestroy(MBUF_DATABLOCKDESCRIPTOR_S *pstHeadDataBlock);

PF_VOID MBUF_UPDATE_BY_LEN(PMBUF_S* pstMBuf,PF_LONG lLen);

PF_VOID MBUF_UPDATE_BY_LEN_TAIL(PMBUF_S* pstMBuf,PF_LONG lLen);

PF_VOID MBUF_UPDATE_LENGTH(PMBUF_S* pstMBuf,PF_LONG lLen);

extern VOS_UINT32 PMBUF_PullUp(SM_MBUF_S * pstMBuf, VOS_UINT32 ulLength, VOS_UINT32 ulModuleID);

#endif /* _SM_SIMULATOR_MBUF_H_ */
