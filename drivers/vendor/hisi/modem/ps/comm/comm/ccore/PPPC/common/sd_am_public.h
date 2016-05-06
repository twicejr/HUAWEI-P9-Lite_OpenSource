#ifndef __SD_AM_PUBLIC_H__
#define __SD_AM_PUBLIC_H__

#define SPUD_MAX_LOCAL_TOKEN_NUM 64

/*sd 与sc 间的通用队列的消息码的宏定义 */
#define GENERAL_MSG_MASTER_DELETE_CODE 0 /*0表示主板删除*/
#define GENERAL_MSG_SLAVE_REBUILD_CODE 1 /*1表示备板重建*/
#define GENERAL_MSG_SLAVE_DELETE_CODE  2 /*2表示备板删除*/


#define SD_OTHER_MSG_QUE_LEN 512

/*sd 与sc 间的通用队列的格式 */
typedef struct tagSC_GENERAL_MSG_S
{
    VOS_UINT32 ulScLogicalVcpuId;  /*Sc的逻辑VCPU ID*/
    VOS_UINT32 ulDpeId;                       /*Dpe的逻辑VCPU ID*/
    VOS_UINT32 ulMsgID;                     /*0表示主板删除,1表示备板重建,2表示备板删除*/
    UCHAR aucImsi[8];                /*IMSI 的BCD码*/
    VOS_UINT16 usGenToken;                  /* 该用户对应的TOKEN信息 */
    UCHAR ucSduId;
    UCHAR ucbit1LuimImsiValid:1;    
    UCHAR ucGenerRev:7;
} SC_GENERAL_MSG_S;
#if 0

/* SC接入状态负荷分担表结构 */
typedef struct  tagSC_ACCESS_STATE_S
{
    VOS_UINT32 ulDpeUserNum[MAX_DPE_NUM_PDSN];   /* SC上报DPE的用户总数 */
    VOS_UINT32 ulScUserNum;   /* SC上报用户数 */
    UCHAR ucCpuRate;    /* SC内的CPU利用率  取整*/
    UCHAR ucMemRate;    /* SC内的内存利用率 取整 */
    UCHAR ucReserve[2]; /* 4字节对齐保留 */
} SC_ACCESS_STATE_S;
#endif

typedef struct tagFA_NAITOKEN_INFO_S 
{

    UCHAR aucNai[A11_MAX_NAI_LENGTH + 1];
    VOS_UINT16 usToken;
    UCHAR  ucScId;
    UCHAR  ucSduId;
}FA_NAITOKEN_INFO_S;


typedef enum 
{
    SD_OTHER_MSG_TYPE_CHECK_IMSI = 1,  

    SD_OTHER_MSG_TYPE_BULT,
} SD_OTHER_MSG_TYPE_E;

/* IMSI类型 */
typedef enum 
{
    SD_IMSI_TYPE_CUIMIMSI,  
    SD_IMSI_TYPE_LUIMIMSI,  
    
    SD_IMSI_TYPE_BUTT,  
} SD_IMSI_TYPE_E;

#define A11_IMSI_CHECK_TO_SD_ITEM_MAX 10
#define A11_IMSI_CHECK_TO_SDU_ITEM_MAX 10
#define A11_NAI_CHECK_TO_SDU_ITEM_MAX 10
#define A11_IMSI_CHECK_MAX_PER_500MS 10

#define A11_IMSI_CHECK_MAX_PER_500MS 30


typedef struct tagA11_SD_IMSI_CHECK_MSG_S
{
    VOS_UINT32 ulItemNum;
    SC_GENERAL_MSG_S astItemArray[0];
} A11_SD_IMSI_CHECK_MSG_S;

typedef struct tagA11_NAI_CHECK_MSG_S
{
    VOS_UINT32 ulItemNum;
    FA_NAITOKEN_INFO_S astItemArray[0];
} A11_NAI_CHECK_MSG_S;

extern VOS_UINT32 SD_QueryScidByImsi(UCHAR  *pucImsi, UCHAR  *pucScid);

#endif /* __SD_AM_PUBLIC_H__ */
