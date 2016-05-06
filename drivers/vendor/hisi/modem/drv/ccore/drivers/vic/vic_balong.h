


#ifndef _VIC_BALONG_H_
#define _VIC_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <soc_interrupts.h>
#include <soc_memmap.h>
#include <bsp_vic.h>

#define INT_VIC_MAX     32
#define BALONG_VIC_NUM  4


#define VIC_OFFSET_MASK_ENA         0x0
#define VIC_OFFSET_MASK_CLR         0x4
#define VIC_OFFSET_MASK_STATUS      0x8
#define VIC_OFFSET_POLAR_ENA        0x20
#define VIC_OFFSET_POLAR_CLR        0x24
#define VIC_OFFSET_STATUS_MASK_IRQ  0x34
#define VIC_OFFSET_STATUS_FINAL_IRQ 0x38

#define VIC_MASK_ALL_INT 0xFFFFFFFF

#ifndef OK
#define OK      (0)
#endif

#ifndef ERROR
#define ERROR   (-1)
#endif

typedef struct
{
	vicfuncptr	routine;
	s32	arg;
}bsp_victable_st;

typedef struct
{
	void * vic_phy_base_addr;
	void * vic_virt_base_addr;
	unsigned int vic_irq_num;
	unsigned int vic_intusemask;
	bsp_victable_st victable[INT_VIC_MAX];
}bsp_vic_st;


#ifdef __cplusplus
}
#endif

#endif /* _VIC_BALONG_H_ */

