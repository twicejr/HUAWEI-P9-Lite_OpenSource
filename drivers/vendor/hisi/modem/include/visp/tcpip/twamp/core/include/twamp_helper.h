#ifndef _TCPIP_TWAMP_HELPER_H_
#define _TCPIP_TWAMP_HELPER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* This will be used as a Hash Node. */
typedef struct tagTcpipTwampHashNode
{
    VOID *pKey;
    VOID *pData;
}TCPIP_TWAMP_HASH_NODE_S;

/* Helps in maintaing list of Hash nodes. */
typedef struct tagTcpipTwampHashList
{
    TCPIP_TWAMP_HASH_NODE_S sHashNode;
    struct tagTcpipTwampHashList *pNext;
}TCPIP_TWAMP_HASH_LIST_S;

/* A Hash Bucket. */
typedef struct tagTcpipTwampHashBucket
{
   VOID *pKey;
   TCPIP_TWAMP_HASH_LIST_S *pHashList;

}TCPIP_TWAMP_HASH_BUCKET_S;

/* This will be used to create an instance of Hash Table. */
typedef struct tagTcpipTwampHashInst
{
    ULONG ulSize;                        /* Max Number of Buckets. */
    TCPIP_TWAMP_HASH_BUCKET_S *pBuckets; /* Pointer to pool of buckets. */
    TCPIP_KEY_GET pGetKey;               /* Pointer to func to compute the key. */
    TCPIP_KEY_COMP pCompKey;             /* Pointer to func to compare two keys. */
}TCPIP_TWAMP_HASH_INST_S;


extern ULONG TWAMP_HashInit(ULONG ulSize, TCPIP_KEY_GET pKeyGet,
                                    TCPIP_KEY_COMP pKeyComp, VOID **pOutput);
extern ULONG TWAMP_HashDeInit(VOID *pInst);
extern ULONG TWAMP_HashInsert(VOID *pKey, VOID *pData, VOID *pInst);
extern ULONG TWAMP_HashDelete(VOID *pKey, VOID *pInst);
extern ULONG TWAMP_HashGet(VOID *pKey, VOID *pInst, VOID **pOutput);


extern ULONG TWAMP_64Div64(ULONG uiDividendHigh,
                       ULONG uiDividendLow,
                       ULONG uiDivisorHigh,
                       ULONG uiDivisorLow,
                       ULONG *puiQuotientHigh,
                       ULONG *puiQuotientLow,
                       ULONG *puiRemainderHigh,
                       ULONG *puiRemainderLow);

extern ULONG TWAMP_64Div32RoundUp(ULONG uiDividendHigh,
                              ULONG uiDividendLow,
                              ULONG uiDivisor,
                              ULONG *puiQuotientHigh,
                              ULONG *puiQuotientLow);


extern VOID Twamp_DebugReflectorRecvPKT(ULONG ulPKTType, VOID *pstRemInfo);


extern VOID Twamp_DebugReflectorSendPKT(ULONG ulPKTType, VOID *pstRemInfo);


extern VOID Twamp_DebugClientRecvPKT(ULONG ulPKTType, VOID *pstRemInfo);


extern VOID Twamp_DebugClientSendPKT(ULONG ulPKTType, VOID *pstRemInfo);


extern ULONG TWAMP_GetDebugSwitch (ULONG *pulDebug);

extern ULONG TWAMP_SetDebugSwitch (ULONG ulDebug);

#ifdef __cplusplus
}
#endif


#endif
