/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_key.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket key defintion
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/
#ifndef _SOCK_KEY_H
#define _SOCK_KEY_H

#ifdef  __cplusplus
extern  "C"{
#endif

extern unsigned short g_usBindMaxPortNum;
/***********************************************************************/
/*                 max prot number socket can use                      */
/***********************************************************************/
#define SOCK_MAXPORT            65535
#define SOCK_DFT_MAXFREEPORT    50000  /*Added by luogaowei 2012-11-1 默认最大值50000*/
#define SOCK_MAXFREEPORT        g_usBindMaxPortNum  /*Added by luogaowei 2012-11-1 扩充端口号默认值范围*/
#define MAXPORTGET              15535
/***********************************************************************/
/*                 return value definition                             */
/***********************************************************************/
#ifndef SUCCESS
    #define SUCCESS          0
#endif
#ifndef ERROR_NOPORT
    #define ERROR_NOPORT    -1
#endif
#ifndef ERROR_PORT
    #define ERROR_PORT      -2
#endif
#ifndef ERROR_FP
    #define ERROR_FP        -3
#endif
#ifndef NOTFOUND
    #define NOTFOUND        -4
#endif


/***********************************************************************/
/*                 data buffer type                                    */
/***********************************************************************/
#define BUF_GENENAL        0
#define BUF_MBUF           1
#define BUF_MBUF_HEAD      2

/***********************************************************************/
/*                 data structure definition                           */
/***********************************************************************/
#define ARRAY_LEN(x)       HOWMANY(x, NFDBITS)
    
#define PD_SET(n, p)    {\
            if ((n) > 0 ){\
            ((p)->stPortInfo.pulPortState[(n)/NFDBITS] |= \
                        (((ULONG) 0x00000001) << ((n) % NFDBITS))); \
                    }\
                    }
#define PD_NSET(n, p)    {\
            if ((n) > 0 ){\
            ((p)->stPortInfo.pulPortState[(n)/NFDBITS] &= ~ \
                        (((ULONG) 0x00000001) << ((n) % NFDBITS))); \
                    }\
                    }
                    
#define PD_ISSET(n, p)  ((p)->stPortInfo.pulPortState[(n)/NFDBITS] & \
                        (((ULONG) 0x00000001) << ((n) % NFDBITS)))                    


/*FLAGS definition*/
#define ERROR_BUF_TYPE        -99

typedef struct tagCALLBACKINFO
{
    LONG lMID;
    CHAR *pBuf;
    ULONG ulDataLen;
    SHORT sBufType;
    UCHAR ucPadding[2];
    LONG lFlags;
    sockaddr_in stAddrSrc;
    sockaddr_in stAddrDst;
}CALLBACKINFO_S;

typedef struct tagPORTINFO
{
    USHORT usPortBegin;
    USHORT usTotalPortNo;
    USHORT  pi_sMin;
    USHORT usBusyPortNo;
    ULONG  *pulPortState;
}PORTINFO_S;

#define L_PORTINFO_S  sizeof(PORTINFO_S)

typedef       VOID   (*CALLBACK_FUN)(CALLBACKINFO_S *pstCbkInf);
typedef struct tagMREGINFO
{
    struct tagMREGINFO *key_pNext,*key_pPrev;
    LONG lMID;
    LONG lProto;
    PORTINFO_S stPortInfo;
    SHORT sBufType;
    UCHAR ucPadding[2];
    CALLBACK_FUN pfSK_Callback;
}MREGINFO_S;

#define L_MREG_S  sizeof(MREGINFO_S)
/***********************************************************************/
/*                 global variable definition                          */
/***********************************************************************/

extern SHORT      sSockKey;
extern MREGINFO_S stMRegHead;

/***********************************************************************/
/*                 function definition                                 */
/***********************************************************************/
extern VOID SOCK_Key_Init();
extern LONG SOCK_MallocPortRng(LONG ,USHORT ,SHORT ,CALLBACK_FUN);
extern LONG sock_MallocPort(LONG,USHORT *);
extern LONG sock_ReleasePort(LONG,USHORT);
extern LONG sock_ReleasePortRng(LONG);
extern MREGINFO_S *SOCK_SearchNode(USHORT);
extern LONG AddNode(MREGINFO_S *,MREGINFO_S *,MREGINFO_S *);
extern LONG DelNode(MREGINFO_S *);
extern VOID SOCK_GetSockKey(SHORT *ulSockKey);


#ifdef  __cplusplus
}
#endif


#endif

