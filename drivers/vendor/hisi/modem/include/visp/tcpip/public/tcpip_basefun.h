

#ifndef _TCPIP_BASEFUN_H_
#define _TCPIP_BASEFUN_H_

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef PCLINT_FOR_VOS_MEM
#define PCLINT_FOR_VOS_MEM
#if (TCPIP_VOS_FUNC_TYPE != VOS_FUNC_TYPE_SAFE)
extern VOS_UINT32 VOS_Mem_Copy(VOS_VOID * pDestPtr, const VOS_VOID * pSrcPtr, SIZE_T uvCopyLen);
extern VOS_UINT32 VOS_Mem_Set( CHAR * pBufPtr, CHAR uChar, SIZE_T uvSetLen );
extern VOS_UINT32 VOS_Mem_Zero( CHAR * pBufPtr, SIZE_T ulSetLen );
#endif
#endif
/*Modified by yanlei00216869, 支持控制器安全函数适配, 2015/1/6   问题单号:DTS2015010508058 */
#if (TCPIP_VOS_FUNC_TYPE == VOS_FUNC_TYPE_SAFE)
extern CHAR* VOS_strncpy_Safe(CHAR * pscDest, VOS_UINT32 uvDestSize, const CHAR * pscSrc, VOS_UINT32 uvCount);
extern CHAR * VOS_StrNCat_Safe(CHAR * pscDest, SIZE_T uvDestSize, const CHAR * pscSrc, SIZE_T uvCount);
extern VOS_INT VOS_snprintf_s(VOS_CHAR* strDest, VOS_SIZE_T destMax, VOS_SIZE_T count, const VOS_CHAR* format, ...);
extern VOS_INT VOS_memmove_s(VOS_VOID* dest, VOS_SIZE_T destMax, const VOS_VOID* src, VOS_SIZE_T count);
extern VOS_INT VOS_sscanf_s(const VOS_CHAR* buffer, const VOS_CHAR* format, ...);
extern VOS_INT VOS_scanf_s(const VOS_CHAR* format, ...);
extern VOS_UINT32 VOS_Mem_Copy_Safe( VOS_VOID *pDestPtr, SIZE_T uvDestSize, const VOS_VOID *pSrcPtr, SIZE_T uvCopyLen );
extern VOS_INT VOS_memset_s(VOS_VOID* dest, VOS_SIZE_T destMax, VOS_INT c, VOS_SIZE_T count);
#else
#if (TCPIP_VOS_FUNC_TYPE == VOS_FUNC_TYPE_SAFE_MBSC)
extern VOS_INT VOS_snprintf_S(VOS_CHAR* strDest, VOS_SIZE_T destMax, VOS_SIZE_T count, const VOS_CHAR* format, ...);
extern VOS_INT VOS_sscanf_S(const VOS_CHAR* buffer, const VOS_CHAR* format, ...);
extern VOS_INT scanf_s(const char* format, ...);
extern VOS_INT memcpy_s(VOS_VOID* dest, VOS_SIZE_T destMax, const VOS_VOID* src, VOS_SIZE_T count);
extern VOS_INT strncpy_s(CHAR* strDest, VOS_SIZE_T destMax, const CHAR* strSrc, VOS_SIZE_T count);
extern VOS_INT strncat_s(CHAR* strDest, VOS_SIZE_T destMax, const CHAR* strSrc, VOS_SIZE_T count);
extern VOS_INT memmove_s(VOS_VOID* dest, VOS_SIZE_T destMax, const VOS_VOID* src, VOS_SIZE_T count);
extern VOS_INT memset_s(VOS_VOID* dest, VOS_SIZE_T destMax, VOS_INT c, VOS_SIZE_T count);
#else
extern CHAR*  VOS_strncpy( CHAR * pcdst, const CHAR * pcsrc, VOS_UINT32 n );
extern CHAR * VOS_StrNCat(CHAR * pscDest, const CHAR * pscSrc, SIZE_T uvCount);
extern VOS_INT32 VOS_nsprintf(CHAR *pscOBuf,VOS_UINT32 ulMaxStrLen,const CHAR *pscFormat, ...);
extern VOID *TCPIP_MemMove(VOID *pVoidDes, const VOID *pVoidSrc, ULONG ulLen);
extern VOS_INT32 VOS_sscanf(const VOS_CHAR *pscIBuf, const VOS_CHAR *pfmt, ...);
#endif
/*End of Modified by yanlei00216869, 2015/1/6   问题单号:DTS2015010508058 */
#endif

extern ULONG TCPIP_Safe_Mem_Copy(VOID *pDestPtr, ULONG ulDestSize, const VOID *pSrcPtr, ULONG ulCopyLen);
extern CHAR *TCPIP_Safe_Strncpy(CHAR *pscDest, ULONG ulDestSize, const CHAR *pscSrc, ULONG ulCount);
extern CHAR *TCPIP_Safe_StrNCat(CHAR *pscDest, ULONG ulDestSize, const CHAR *pscSrc, ULONG ulCount);
extern VOID TCPIP_Safe_Mem_Move(VOID *pDest, ULONG ulDstMaxLen, const VOID *pSrc, ULONG ulCount);
extern ULONG TCPIP_Safe_Mem_Set(VOID *pDest, ULONG ulDstMaxLen, CHAR uChar, ULONG ulCount);
extern ULONG TCPIP_Rand_Safe(ULONG ulUnsafeSeed);

extern VOS_UINT32 VOS_strlen( const CHAR * pcstr );
extern CHAR * VOS_StrRChr(CHAR* pscStr, CHAR scChar);
extern LONG atoul(CHAR *Sour, ULONG * pTemp);
extern VOS_INT    VOS_StrNCmp(CHAR * pscStr1, CHAR * pscStr2, SIZE_T ulCount);
extern VOS_INT    VOS_StrICmp(CHAR * pscS1, CHAR * pscS2);
extern VOS_UINT32 VOS_StrLen(CHAR * pscStr);
extern VOS_UINT32 VOS_Mem_GetRef( VOS_VOID * pBuf, VOS_UINT32 * pulRetRef );
extern VOS_UINT32 VOS_Mem_Cmp( const VOS_VOID * pDestPtr,const VOS_VOID * pSrcPtr, SIZE_T uvCmpLen, VOS_INT32* plRetResult );
extern VOS_INT32  VOS_atol( const CHAR * pcStr, VOS_INT32 * pnVal );

/* The argument of TCPIP_SNPRINTF0 and TCPIP_SNPRINTF */
#define P0(message) message
#define P1(message,_p1) message,_p1
#define P2(message,_p1,_p2)  message,_p1,_p2
#define P3(message,_p1,_p2,_p3) message,_p1,_p2,_p3
#define P4(message,_p1,_p2,_p3,_p4)  message,_p1,_p2,_p3,_p4
#define P5(message,_p1,_p2,_p3,_p4,_p5)message,_p1,_p2,_p3,_p4,_p5
#define P6(message,_p1,_p2,_p3,_p4,_p5,_p6) message,_p1,_p2,_p3,_p4,_p5,_p6 
#define P7(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7 
#define P8(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8 
#define P9(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9
#define P10(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10
#define P11(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11
#define P12(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12
#define P13(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13
#define P14(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14
#define P15(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15
#define P16(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16
#define P17(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17
#define P18(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18
#define P19(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19
#define P20(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20
#define P21(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21
#define P22(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22
#define P23(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23
#define P24(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24
#define P25(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25
#define P26(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26
#define P27(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26,_p27) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26,_p27
#define P28(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26,_p27,_p28) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26,_p27,_p28
#define P29(message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26,_p27,_p28,_p29) message,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13,_p14,_p15,_p16,_p17,_p18,_p19,_p20,_p21,_p22,_p23,_p24,_p25,_p26,_p27,_p28,_p29

/* For StrCat operation:
 *   1. the Len should be the smallest of dst_free_len, src_strlen, src_buflen
 *   2. if src_buflen = 0, the Len should be the smaller of dst_free_lena and src_strlen
 */
#define FREE_LEN(DSTR, DSTLEN)      ((DSTLEN) - VOS_strlen(DSTR) - 1)
#define SRC_LEN(SSTR)               (VOS_strlen(SSTR))
#define CAT_LEN(DSTR, DSTLEN, SSTR) ((FREE_LEN(DSTR, DSTLEN) > SRC_LEN(SSTR)) ? SRC_LEN(SSTR) : FREE_LEN(DSTR, DSTLEN))

#define TCPIP_STRNCAT_S(DSTR, DSTLEN, SSTR)  (TCPIP_StrNCat((DSTR), (DSTLEN), (SSTR), (CAT_LEN(DSTR, DSTLEN, SSTR))))

#define VOS_Mem_Zero_Safe(DSTR, DSTLEN) (TCPIP_Mem_Set(DSTR,0,DSTLEN))

#ifdef  __cplusplus
}
#endif /*__cplusplus*/

#endif /*_TCPIP_BASEFUN_H_*/

