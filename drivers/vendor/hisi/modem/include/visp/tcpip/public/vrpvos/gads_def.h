/*******************************************************************************
*                                                                              *
*        Copyright 2003-2006  Huawei Technologies India Private Limited        *
*                          All Rights Reserved                                 *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*                              gads_def.h                                      *
*                                                                              *
*    Project Code:  VRP5.0                                                     *
*    Module Name:   GADS(General Array Data Structure)                         *
*    Create Date:  2003/05/17                                                  *
*         Author:  Rainbow                                                     *
*     Description: Define data structure for GADS implementation.              *
*                                                                              *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  2003-05-17  Rainbow           Create                                        *
*                                                                              *
*******************************************************************************/

#ifndef _GADS_DEF_H
#define _GADS_DEF_H

#ifdef    __cplusplus
extern "C"{
#endif

#define        GADS_SEQ_BIT_LEN_MAX                    12
#define        GADS_SEQ_BIT_LEN_MIN                    4
#define        GADS_USER_INFO_BIT_LEN_MAX              16
#define        GADS_IDX_BIT_LEN_MAX                    20
#define        GADS_IDX_BIT_LEN_MIN                    4

/*Get the sequence number from given multi index.*/
#define        GADS_GET_SEQ(midx, userinfobitlen, idxbitlen)  \
                                            ( (midx) >> ((userinfobitlen) + (idxbitlen))) 


#define        GADS_ENTRY_USED(x)                ( 0x80000000 == (x & 0x80000000) )  
#define        GADS_ENTRY_FREE(x)                ( 0x0 == (x & 0x80000000) ) 
#define        GADS_ENTRY_SET_USED_FLAG(x)       ( x = x | 0x80000000 )    
#define        GADS_ENTRY_RESET_USED_FLAG(x)     ( x = x & 0x7FFFFFFF ) 

/*Construct the multi index from sequence number, userinfo, and index.*/
#define    GADS_COMPOSED_MIDX(seq, userinfo, index , userinfobitlen, idxbitlen)        \
                (                                                                    \
                       (  (seq)  << ((userinfobitlen) + (idxbitlen) ) )                \
                    |  ( ((userinfo)&0xFFFF) << (idxbitlen))                         \
                    |  ((index) & 0xFFFFF )                                            \
                )
/*Calculate the power of 2.*/
#define GADS_GET_POWER_OF_2(n, result)                result=1<<n

/*Get the user info from given multi index.*/
#define        GADS_GET_USERINFO(midx, userinfobitlen , idxbitlen)  \
                ( (userinfobitlen) ? \
                (((midx) << (32- (userinfobitlen) - (idxbitlen))) >> (32 - (userinfobitlen))) : 0 )

/*Get the index from given multi index.*/
#define        GADS_GET_IDX(midx, userinfobitlen, idxbitlen)    \
                (((midx) << (32- (idxbitlen))) >> (32- (idxbitlen)) )

#define        GADS_MAX_UNIT_ENTRY 1000000 /*Current max number of unit entry in one gads instance.*/

#define        GADS_MAX_NAME_LEN  64
 

/*Array Entry stucture */
typedef struct tagGADS_UNIT_S
{
    ULONG  ulMngListPrevIdx;   /*Store the used list or free list index: previous*/
    ULONG  ulMngListNextIdx;   /*Store the used list or free list index: next.
                                  The highest bit of this member: 1: uesed 0: free.*/
    USHORT usUserInfo;         /*User info will be composed into multi index and returu to user. User define 
                                 the area when create a object. Max BITs length of user info in multi index is 16BIT,
                                 default BITs length is 0.*/
    USHORT usSeqNum ;          /* Seqence number for this entry;*/
    VOID   *pObj;              /* Application Object;*/
}GADS_UNIT_S;

/*Global control block. One instance of data structure describe a gads instance used by app used, which indicated by 
gads handle. User must create a gads instance and get handle from creating procedure. When user want access the gads 
instance he/she must use handle as input parameter. */
typedef struct tagGADS_S
{
    GADS_HANDLE  hGADS; /*Handle for this instance used to check app user gads handle.*/
    CHAR         chName[GADS_MAX_NAME_LEN ]; /*Name for this GADS;*/
    ULONG        ulMaxStaticNum ;  /* Max Static Entry in general Array;*/
    ULONG        ulMaxAvailNum ;   /* Max Available Entry in general Array;*/
    ULONG        ulMaxUsedNum ;    /* Max used Entry in general Array;*/
    ULONG        ulMID;            /*Module id for the GADS instance being used.*/
    ULONG        ulSID;            /*Data structure id for the GADS instance being used. */
    ULONG        ulUnitSize  ;     /* The size of one object in bytes;*/
    ULONG        ulSeqNumBitLen ;  /* Max number of BITs in MINDEX for sequence number;*/
    ULONG        ulMaxSeqValue;    /* equal to (2 ^ ulSeqNumBitLen)*/
    ULONG        ulIdxNumBitLen ;  /*Max number of BITs in MINDEX for user index and it equal to 
                                     32-ulSeqNumBitLen-ulUserInfoBitLen; */
    ULONG        ulMaxIdxValue;    /* equal to (2 ^ ulIdxNumBitLen)*/

    ULONG        ulUserInfoBitLen;     /*The munber of BITs defined by user.Max number is 16 and default value is 0;*/
    ULONG        ulMaxUserInfoValue;   /* equal to (2 ^ ulUserInfoBitLen)*/

    /*Free list header. By this you can get a free head quickly.*/
    ULONG        ulFreeListHead; /*Free list head ;*/
    ULONG        ulFreeListTail; /*Free list tail ;*/

    /*Used Object list header. By this you can travel all used nodes quickly. By this you can travel all used nodes quickly.*/
    ULONG        ulUsedListHead; /*Used list head ;*/
    ULONG        ulUsedListTail; /*Used list tail ;*/
    GADS_UNIT_S  *pGadsUnitArray;
}GADS_S;



#ifdef    __cplusplus
}
#endif



#endif
