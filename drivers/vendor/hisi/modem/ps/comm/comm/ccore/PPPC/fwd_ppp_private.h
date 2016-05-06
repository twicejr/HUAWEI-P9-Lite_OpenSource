#ifndef __FWD_PPP_PRIVATE_H__
#define __FWD_PPP_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PPP_PFC_1    1
#define PPP_PFC_0    0

#define PPP_ACFC_1    1
#define PPP_ACFC_0    0

/*LCP packet struct */
#define LCP_CODE_OFFSET 0
#define LCP_ID_OFFSET 1
#define LCP_LENGTH_OFFSET 2
#define LCP_MAGICNUM_OFFSET 4
    typedef struct ppp_lcp_s4
    {
        PF_UCHAR ucCode;
        PF_UCHAR ucId;
        PF_USHORT usLength;
        PF_ULONG ulMagicNum;
     }PPP_LCP_S4;

   typedef struct ppp_lcp_s2
   {
        PF_UCHAR ucCode;
        PF_UCHAR ucId;
        PF_USHORT usLength;
        PF_USHORT usMagicNumHi;
        PF_USHORT usMagicNumLo;

   } PPP_LCP_S2;
   typedef struct ppp_lcp_s1
  {
        PF_UCHAR ucCode;
        PF_UCHAR ucId;
        PF_UCHAR ucLengthHi;
        PF_UCHAR ucLengthLo;
        PF_UCHAR ucMagicNum1;
        PF_UCHAR ucMagicNum2;
        PF_UCHAR ucMagicNum3;
        PF_UCHAR ucMagicNum4;
  }PPP_LCP_S1;


#define GET_CODE_FROM_LCP_PKT(pucLcpHd)   ((pucLcpHd)[LCP_CODE_OFFSET])
#define GET_ID_FROM_LCP_PKT(pucLcpHd) ((pucLcpHd)[LCP_ID_OFFSET])
#define GET_LENGTH_FROM_LCP_PKT(pucLcpHd,usLcpLen) {\
    VOS_UINT16      usPosShift = 0;\
    VOS_MemCpy(&usPosShift, &pucLcpHd[LCP_LENGTH_OFFSET], sizeof(VOS_UINT16));\
    usLcpLen = VOS_NTOHS(usPosShift);\
}
/* 地址与0x03L与的结果如果是0表示该地址是4字节对齐，其他结果以此类推 */
#define GET_MAGICNUM_FROM_LCP_PKT(pucLcpHd,ulMagicNumber)\
{\
    switch((PF_ULONG)(pucLcpHd) & 0x03L)\
    {\
        case 0:\
            (ulMagicNumber)= VOS_NTOHL(((PPP_LCP_S4*)(pucLcpHd))->ulMagicNum);\
            break;\
        case 2:\
            (ulMagicNumber)=VOS_NTOHS(((PPP_LCP_S2*)(pucLcpHd))->usMagicNumHi);\
            (ulMagicNumber)= ((ulMagicNumber)<<16 ) | VOS_NTOHS(((PPP_LCP_S2*)(pucLcpHd))->usMagicNumLo);\
            break;\
        default:\
        {\
           (ulMagicNumber) = (((PPP_LCP_S1*)(pucLcpHd))->ucMagicNum1);\
           (ulMagicNumber) = ((ulMagicNumber)  <<8) |(((PPP_LCP_S1*)(pucLcpHd))->ucMagicNum2);\
           (ulMagicNumber)  = ((ulMagicNumber)  <<8) |(((PPP_LCP_S1*)(pucLcpHd))->ucMagicNum3);\
           (ulMagicNumber)  = ((ulMagicNumber)  <<8) |(((PPP_LCP_S1*)(pucLcpHd))->ucMagicNum4);\
           break;\
        }\
    }\
}


#ifdef __cplusplus
}
#endif


#endif    /* end of __FWD_PPP_PRIVATE_H__ */
