
#ifndef _IPF_BALONG_H_
#define _IPF_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "mdrv_ipf_comm.h"


#ifndef NULL
#define NULL            (void*)0
#endif

#ifndef OK
#define OK 0
#endif

#ifndef ERROR
#define ERROR  (-1)
#endif

static __inline__ unsigned int ipf_readl(unsigned int addr)
{
    return readl(addr);
}
static __inline__ void ipf_writel(unsigned int val, unsigned int addr)
{
    writel(val, addr);
}


typedef struct tagIPF_MATCH_INFO_S{
    unsigned char u8SrcAddr[16];
    unsigned char u8DstAddr[16];
    unsigned char u8DstMsk[16];
    union{
        struct{
        	unsigned int u16SrcPortLo:16;
        	unsigned int u16SrcPortHi:16;
        }Bits;
	    unsigned int u32SrcPort;
    } unSrcPort;
    union{
        struct
        {
            unsigned int u16DstPortLo:16;
        	unsigned int u16DstPortHi:16;
        }Bits;
    	unsigned int u32DstPort;
    } unDstPort;
    union{
        struct
        {
            unsigned int u8TrafficClass:8;
        	unsigned int u8TrafficClassMask:8;
        	unsigned int u16Reserve:16;
        }Bits;
    	unsigned int u32TrafficClass;
    }unTrafficClass;
    unsigned int u32LocalAddressMsk;
    union{
    	unsigned int u32NextHeader;
    	unsigned int u32Protocol;
    }unNextHeader;
    unsigned int u32FlowLable;
    union{
        struct{
            unsigned int u16Type:16;
        	unsigned int u16Code:16;
        }Bits;
    	unsigned int u32CodeType;
    } unFltCodeType;
    union{
        struct{
            unsigned int u16NextIndex:16;
        	unsigned int u16FltPri:16;
        }Bits;
    	unsigned int u32FltChain;
    } unFltChain;
    unsigned int u32FltSpi;
    union{
    	struct{
    		unsigned int FltEn:1;
    		unsigned int FltType:1;
    		unsigned int Resv1:2;
            unsigned int FltSpiEn:1;
            unsigned int FltCodeEn:1;
            unsigned int FltTypeEn:1;
            unsigned int FltFlEn:1;
            unsigned int FltNhEn:1;
            unsigned int FltTosEn:1;
            unsigned int FltRPortEn:1;
            unsigned int FltLPortEn:1;
            unsigned int FltRAddrEn:1;
            unsigned int FltLAddrEn:1;
            unsigned int Resv2:2;
            unsigned int FltBid:6;
            unsigned int Resv3:10;
    	}Bits;
    	unsigned int u32FltRuleCtrl;
    }unFltRuleCtrl;
}IPF_MATCH_INFO_S;

#ifdef __cplusplus
}
#endif

#endif /*s_IPC_BALONG_H_*/

