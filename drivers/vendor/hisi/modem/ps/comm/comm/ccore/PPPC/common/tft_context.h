
#ifndef __TFT_CONTEXT_H__
#define __TFT_CONTEXT_H__


#define SDB_MAX_PF_PER_TFT                4

typedef DPE_FILTER_CONTENT_S    SDB_PACKET_FILTER_S;

typedef struct tagPF_INFO
{
    VOS_UINT32     ulA10Index;
    UCHAR     ucFlowID;       /* IP Flow ID: pdnId(4bit) + flowid(4bit)   */
    UCHAR     bDirection:1,   /* PF Direction */
              bActive:1,      /* Used by NP */
              FlowPriority:4,
              bUsedFlag:1,
              bHasPfInfo:1;  /*表示是否该部分内存是否写入了PF信息*/
    UCHAR ucResv[2];                /* 字节对齐 */
    SDB_PACKET_FILTER_S stPacketFileter;
}VOS_PACKED SDB_PF_INFO_S;

typedef struct tagSDB_PDSN_TFT_CONTEXT
{
    VOS_UINT32   ulTftIndex;
    VOS_UINT32   ulPdnIndex;
    UCHAR   ucPFNumbers;   /*真实填充的packet filter的数目 无论该filter是否已经使用  这个主要是针对HSGW */
    UCHAR   ucBindNumbers;
    UCHAR   ucResv[2];                /* 字节对齐 */
    SDB_PF_INFO_S  stTFT_Info[SDB_MAX_PF_PER_TFT];      /* Flow's TFT */

    /*****************************************/
    /*以下字段用于维护打补丁******************/
    UCHAR aucPatchReserve[4];
}VOS_PACKED SDB_PDSN_TFT_CONTEXT_S;


#endif /* __TFT_CONTEXT_H__ */
