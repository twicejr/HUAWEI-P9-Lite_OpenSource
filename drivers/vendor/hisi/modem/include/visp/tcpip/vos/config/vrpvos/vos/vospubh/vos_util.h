
#ifndef _VOS_UTIL_H_
#define _VOS_UTIL_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif


#ifdef  __cplusplus
extern "C" {
#endif



#if (VRP_LITTLE_ENDIAN == VRP_YES)
#define VOS_NTOHL(x)                   ((((x) & 0x000000ff) << 24) | \
                                        (((x) & 0x0000ff00) <<  8) | \
                                        (((x) & 0x00ff0000) >>  8) | \
                                        (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)                   ((((x) & 0x000000ff) << 24) | \
                                        (((x) & 0x0000ff00) <<  8) | \
                                        (((x) & 0x00ff0000) >>  8) | \
                                        (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))

#else
#ifndef VOS_NTOHL
#define VOS_NTOHL(x) (x)
#endif
#ifndef VOS_NTOHS
#define VOS_NTOHS(x) (x)
#endif
#ifndef VOS_HTONL
#define VOS_HTONL(x) (x)
#endif
#ifndef VOS_HTONS
#define VOS_HTONS(x) (x)
#endif
#endif


#if (VRP_VERSION_RELEASE == VRP_YES)
ULONG VOS_GetNodeID(VOID);
ULONG VOS_Res_IDToBuf(ULONG ulResID,VOID **ppRetBuf,ULONG *pulRetBufLen); 
#else
#define VOS_GetNodeID()\
	VOS_GetNodeID_X(__FILE__,__LINE__)
#define VOS_Res_IDToBuf(ulResID,ppRetBuf,pulRetBufLen)\
	VOS_Res_IDToBuf_X(ulResID,ppRetBuf,pulRetBufLen,__FILE__,__LINE__)

ULONG VOS_GetNodeID_X(CHAR *pcFileName,ULONG ulLine);
ULONG VOS_Res_IDToBuf_X(ULONG ulResID,VOID **ppRetBuf,
						ULONG *pulRetBufLen,CHAR *pcFileName,ULONG ulLine); 
#endif
	

#ifdef  __cplusplus
}
#endif

#endif

