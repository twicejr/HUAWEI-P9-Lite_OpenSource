#ifndef A_IPF_BALONG_TEST_H
#define A_IPF_BALONG_TEST_H

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/delay.h>
#include <osl_sem.h>
#include "ipf_balong.h"
#include <bsp_ipf.h>
#include <bsp_hardtimer.h>

#define	LONG_DATA 1500
#define	SHORT_DATA 300

#define T_DL_VALUE		0x5a
#define T_UL_VALUE		0x5b

extern ipf_ctx_t g_ipf_ctx;

typedef struct tagStreamIPv4Header
{
    unsigned int TOL:16;
    unsigned int TOS:8;
    unsigned int HeaderLen:4;
    unsigned int Vers:4; 
    unsigned int offset:13;
    unsigned int MF:1;
    unsigned int DF:1;
    unsigned int ReservFlag:1;
    unsigned int ID:16;
    unsigned int Checksum:16;
    unsigned int Prot:8;
    unsigned int TTL:8;    
    unsigned int SourceAddr;
    unsigned int DestAddr;
}StreamIPv4Header;

typedef struct tagStreamUDP
{
    unsigned int DstPort:16;
    unsigned int SrcPort:16;
    unsigned int Checksum:16;
    unsigned int Length:16;    
}StreamUDP;

typedef int (*IPFTHREADFN)(void *pdata);

extern void ipf_set_acore_reset_flag(unsigned int flag);

#endif