
#include "m3boot.h"
#include <soc_onchiprom.h>
#include <hi_syscrg.h>
#include <hi_syssc.h>
#include <hi_pwrctrl.h>
#include <product_config.h>
#ifdef ATE_VECTOR
#include "bsp_ate.h"
#endif

#ifndef HI_SC_AO_CTRL0_OFFSET
#define HI_SC_AO_CTRL0_OFFSET HI_SC_CTRL0_OFFSET
#endif

#ifndef HI_SYSCTRL_AO_REG_BASE_ADDR
#define HI_SYSCTRL_AO_REG_BASE_ADDR HI_SYSSC_BASE_ADDR
#endif

	.syntax unified
#ifdef ATE_VECTOR
	.global ate_vector_init
	.global ate_gpio_on
#endif
	.global bsp_sec_check_fastboot
	.global mddrc_init

#ifdef CONFIG_BALONG_HPM_TEMP
	.global boosting
#endif
	.global dfs_to_max
	.global get_src_addr
	.type _start, %function
	.thumb
	.balign 4
	.text

/******************************************************************************
* The minimal vector table for a Cortex-M3 processor.
******************************************************************************/
m3boot:
    .global  isr_vector
#ifdef DX_SEC_BOOT
 #ifndef BSP_CONFIG_EDA
	.space  (VRL_TABLE_SIZE - 4)
	.long __file_size
 #endif /* BSP_CONFIG_EDA */
#endif
isr_vector:
	.word    STACK_TOP            /* 00: Initial stack pointer  */
	.word    _start               /* 01: Reset handler          */
	.word    nmi_handler          /* 02: NMI handler            */
	.word    hardfault_handler    /* 03: Hard fault handler     */
	.word    mem_manage_handler   /* 04: MPU fault handler      */
	.word    bus_fault_handler    /* 05: Bus fault handler      */
	.word    usage_fault_handler  /* 06: Usage fault handler    */
	.word    0                    /* 07: Reserved               */
	.word    0                    /* 08: Reserved               */
	.word    0                    /* 09: Reserved               */
	.word    0                    /* 10: Reserved               */
	.word    svc_handler          /* 11: SVCall handler         */
	.word    debug_mon_handler    /* 12: Debug monitor handler  */
	.word    0                    /* 13: Reserved               */
	.word    pendsv_handler       /* 14: PendSV handler         */
	.word    systick_handler      /* 15: SysTick handler        */

	/* External interrupts */
	.word    IntDefaultHandler    /* 16  IPCM_INT0_2           */
	.word    IntDefaultHandler    /* 17  IPCM_INT1_2           */
	.word    IntDefaultHandler    /* 18  APPA9_EVENTO_INT      */
	.word    IntDefaultHandler    /* 19  MDMA9_EVENTO_INT      */
	.word    IntDefaultHandler    /* 20  RTC_INT               */
	.word    IntDefaultHandler    /* 21  WDT_INT               */
	.word    IntDefaultHandler    /* 22  UPACC_DSP_INT         */
	.word    IntDefaultHandler    /* 23  UICC_INT              */
	.word    IntDefaultHandler    /* 24  GMAC_SBD_INT          */
	.word    IntDefaultHandler    /* 25  GMAC_PMT_INT          */
	.word    IntDefaultHandler    /* 26  EDMAC_INT2            */
	.word    IntDefaultHandler    /* 27  LTE_CIPHER_INT        */
	.word    IntDefaultHandler    /* 28  IPF_INT0              */
	.word    IntDefaultHandler    /* 29  IPF_INT1              */
	.word    IntDefaultHandler    /* 30  SOCP_INT0             */
	.word    IntDefaultHandler    /* 31  SOCP_INT1             */
	.word    IntDefaultHandler    /* 32  LTESIO_RX_INT         */
	.word    IntDefaultHandler    /* 33  LTESIO_SIO_INT        */
	.word    IntDefaultHandler    /* 34  LTESIO_TX_INT         */
	.word    IntDefaultHandler    /* 35  CICOM0_UL_INT         */
	.word    IntDefaultHandler    /* 36  CICOM0_DL_INT         */
	.word    IntDefaultHandler    /* 37  CICOM1_UL_INT         */
	.word    IntDefaultHandler    /* 38  CICOM1_DL_INT         */
	.word    IntDefaultHandler    /* 39  UPACC_ARM_INT         */
	.word    IntDefaultHandler    /* 40  HDLC_FRM_INT          */
	.word    IntDefaultHandler    /* 41  HDLC_DEF_INT          */
	.word    IntDefaultHandler    /* 42  CM3_EVENTO_INT        */
	.word    IntDefaultHandler    /* 43  TSENSOR_INT           */
	.word    IntDefaultHandler    /* 44  EXT_INT0              */
#ifndef P531_ONCHIPROM_M3VTOR_BUG
	.word    IntDefaultHandler    /* 45  EXT_INT1              */
	.word    IntDefaultHandler    /* 46  EXT_INT2              */
	.word    IntDefaultHandler    /* 47  EXT_INT3              */
	.word    IntDefaultHandler    /* 48  EXT_INT4              */
	.word    IntDefaultHandler    /* 49  EXT_INT5              */
	.word    IntDefaultHandler    /* 50  EXT_INT6              */
	.word    IntDefaultHandler    /* 51  EXT_INT7              */
	.word    IntDefaultHandler    /* 52  EXT_INT8              */
	.word    IntDefaultHandler    /* 53  EXT_INT9              */
	.word    IntDefaultHandler    /* 54  EXT_INT10             */
	.word    IntDefaultHandler    /* 55  EXT_INT11             */
	.word    IntDefaultHandler    /* 56  EXT_INT12             */
	.word    IntDefaultHandler    /* 57  EXT_INT13             */
	.word    IntDefaultHandler    /* 58  EXT_INT14             */
	.word    IntDefaultHandler    /* 59  EXT_INT15             */
	.word    IntDefaultHandler    /* 60  EXT_INT16             */
	.word    IntDefaultHandler    /* 61  TIMER0_INT            */
	.word    IntDefaultHandler    /* 62  TIMER1_INT            */
	.word    IntDefaultHandler    /* 63  TIMER2_INT            */
	.word    IntDefaultHandler    /* 64  TIMER3_INT            */
	.word    IntDefaultHandler    /* 65  TIMER4_INT            */
	.word    IntDefaultHandler    /* 66  TIMER5_INT            */
	.word    IntDefaultHandler    /* 67  TIMER6_INT            */
	.word    IntDefaultHandler    /* 68  TIMER7_INT            */
	.word    IntDefaultHandler    /* 69  TIMER8_INT            */
	.word    IntDefaultHandler    /* 70  TIMER9_INT            */
	.word    IntDefaultHandler    /* 71  TIMER10_INT           */
	.word    IntDefaultHandler    /* 72  TIMER11_INT           */
	.word    IntDefaultHandler    /* 73  TIMER12_INT           */
	.word    IntDefaultHandler    /* 74  TIMER13_INT           */
	.word    IntDefaultHandler    /* 75  TIMER14_INT           */
	.word    IntDefaultHandler    /* 76  TIMER15_INT           */
	.word    IntDefaultHandler    /* 77  SCI0_INT              */
	.word    IntDefaultHandler    /* 78  SCI1_INT              */
	.word    IntDefaultHandler    /* 79  DW_SSI0_INT           */
	.word    IntDefaultHandler    /* 80  DW_SSI1_INT           */
	.word    IntDefaultHandler    /* 81  TCSSI0_INT            */
	.word    IntDefaultHandler    /* 82  TCSSI1_INT            */
	.word    IntDefaultHandler    /* 83  USB3_PME_INT          */
	.word    IntDefaultHandler    /* 84  MIPI_INT              */
	.word    IntDefaultHandler    /* 85  HS_UART_INT           */
	.word    IntDefaultHandler    /* 86  UART0_INT             */
	.word    IntDefaultHandler    /* 87  UART1_INT             */
	.word    IntDefaultHandler    /* 88  UART2_INT             */
	.word    IntDefaultHandler    /* 89  UART3_INT             */
	.word    IntDefaultHandler    /* 90  NANDC_INT             */
	.word    IntDefaultHandler    /* 91  MMC0_INT              */
	.word    IntDefaultHandler    /* 92  MMC1_INT              */
	.word    IntDefaultHandler    /* 93  MMC2_INT              */
	.word    IntDefaultHandler    /* 94  SDCC_INT              */
	.word    IntDefaultHandler    /* 95  I2C_INT               */
	.word    IntDefaultHandler    /* 96  M3_GPIO_GROUP0_INT    */
	.word    IntDefaultHandler    /* 97  M3_GPIO_GROUP1_INT    */
	.word    IntDefaultHandler    /* 98  M3_GPIO_GROUP2_INT    */
	.word    IntDefaultHandler    /* 99  M3_GPIO_GROUP3_INT    */
	.word    IntDefaultHandler    /* 100 M3_GPIO_GROUP4_INT    */
	.word    IntDefaultHandler    /* 101 M3_GPIO_GROUP5_INT    */
	.word    IntDefaultHandler    /* 102 SSDMA_INT             */
	.word    IntDefaultHandler    /* 103 EDMAC_INT0            */
	.word    IntDefaultHandler    /* 104 EDMAC_INT1            */
	.word    IntDefaultHandler    /* 105 AMON_INT              */
	.word    IntDefaultHandler    /* 106 HSIC_INT              */
	.word    IntDefaultHandler    /* 107 APPA9_PMUIREQ_INT     */
	.word    IntDefaultHandler    /* 108 MDMA9_PMUIREQ_INT     */
	.word    IntDefaultHandler    /* 109 HiFi_GPIO2_INT        */
	.word    IntDefaultHandler    /* 110 BBE16_GPIO2_INT       */
	.word    IntDefaultHandler    /* 111 PMU_INT               */
	.word    IntDefaultHandler    /* 112 USB3_OTG_INT          */
	.word    IntDefaultHandler    /* 113 X2H_X2P_ERR           */
	.word    IntDefaultHandler    /* 114 AXI_ERR               */
	.word    IntDefaultHandler    /* 115 USBOTG_BC_INT         */
	.word    IntDefaultHandler    /* 116 SYS_CONTROL_INT4      */
	.word    IntDefaultHandler    /* 117 SYS_CONTROL_INT5      */
	.word    IntDefaultHandler    /* 118 TIMER16_INT           */
	.word    IntDefaultHandler    /* 119 TIMER17_INT           */
	.word    IntDefaultHandler    /* 120 TIMER18_INT           */
	.word    IntDefaultHandler    /* 121 TIMER19_INT           */
	.word    IntDefaultHandler    /* 122 TIMER20_INT           */
	.word    IntDefaultHandler    /* 123 TIMER21_INT           */
	.word    IntDefaultHandler    /* 124 TIMER22_INT           */
	.word    IntDefaultHandler    /* 125 TIMER23_INT           */
	.word    IntDefaultHandler    /* 126 M3_WAKEUP_INT         */
	.word    IntDefaultHandler    /* 127 CPU_AXI_DLOCK_INT     */
	.word    IntDefaultHandler    /* 128 GLb_AXI_DLOCK_INT     */
	.word    IntDefaultHandler    /* 129 MST_AXI_DLOCK_INT     */
	.word    IntDefaultHandler    /* 130 DSP_AXI_DLOCK_INT     */
	.word    IntDefaultHandler    /* 131 BBPHY_AXI_DLOCK_INT   */
	.word    IntDefaultHandler    /* 132 SDCC_HCLK_WKUP_INT    */
	.word    IntDefaultHandler    /* 133 EXT_INT17             */
	.word    IntDefaultHandler    /* 134 USBOTG_PHY_INT        */
	.word    IntDefaultHandler    /* 135 A15_PMUIRQ_INT0       */
	.word    IntDefaultHandler    /* 136 A15_PMUIRQ_INT1       */
	.word    IntDefaultHandler    /* 137 DSP0_GPIO2_INT        */
	.word    IntDefaultHandler    /* 138 APPA9_ARM_WD_SRST_REQ */
	.word    IntDefaultHandler    /* 139 APPA9_L2CC_INT        */
	.word    IntDefaultHandler    /* 140 MDMA9_L2CC_INT        */
	.word    IntDefaultHandler    /* 141 SDCC_PULL_INT         */
	.word    IntDefaultHandler    /* 142 USB3_INT              */
	.word    IntDefaultHandler    /* 143 MODA9_ARM_WD_SRST_REQ */
#endif
/******************************************************************************
* space reseverd for secure boot
******************************************************************************/
reseverd:
	.long __file_size /* reserved for file length*/
#ifndef DX_SEC_BOOT
	.space ROOT_CA_LEN  /* reserver for ROOT CA */
#endif
bootver_adr:
	.space 32   /* reserved for BOOTLOADER version */

	.string "Copyright 2008-2020 HUAWEI TECHNOLOGIES CO., LTD."

/******************************************************************************
* dead loop handler macro
*****************************************************************************/
	.macro    def_irq_handler    handler_name
	.align 1
	.thumb_func
	.weak    \handler_name
	.type    \handler_name, %function
	\handler_name :
	b    .
	.size    \handler_name, . - \handler_name
	.endm

/******************************************************************************
* system exception handler macro extension.
*******************************************************************************/
	def_irq_handler    nmi_handler
	def_irq_handler    hardfault_handler
	def_irq_handler    mem_manage_handler
	def_irq_handler    bus_fault_handler
	def_irq_handler    usage_fault_handler
	def_irq_handler    svc_handler
	def_irq_handler    debug_mon_handler
	def_irq_handler    pendsv_handler
	def_irq_handler    systick_handler
	def_irq_handler    IntDefaultHandler

/******************************************************************************
 register and mpu init
******************************************************************************/
processor_init:
	mov  r0,  #0x0
	mov  r1,  r0
	mov  r2,  r0
	mov  r3,  r0
	mov  r4,  r0
	mov  r5,  r0
	mov  r6,  r0
	mov  r7,  r0
	mov  r8,  r0
	mov  r9,  r0
	mov  r10, r0
	mov  r11, r0
	mov  r12, r0

	/* stack pointer set */
	ldr  sp, =STACK_TOP

	/* disable mpu */
	ldr  r0, =MPU_BASE
	mov  r1, #4
	str  r1, [r0,#MPU_CTRL_OFFSET]
	bx   lr

/******************************************************************************
 copy fastboot code to axi memory
******************************************************************************/
fastboot_code_copy2ddr:
	str  lr,[sp,#-4]!       /* push lr */
    /* set oob length 32Byte, just effective for ecc type 8bit/512Byte */
	ldr  r0, =(HI_NANDC_REGBASE_ADDR + HI_NFC_OOB_SEL_OFFSET)
	ldr  r1, =0x1
	str  r1, [r0]

    /* prepare for read fastboot from flash */
	bl   get_src_addr
	mov  r1, r0
	add  r0, #FASTBOOT_SIZE_OFFSET
	ldr  r2, =RUN_BASE_ADDR_APPA9
#ifndef BSP_CONFIG_EDA
	ldr  r3, [r0]
#ifdef DX_SEC_BOOT
    add r3, #VRL_TABLE_SIZE
#else
    add r3, #(OEM_CA_LEN+2*IDIO_LEN)
#endif
#else
	ldr  r3, =0x400
#endif
	add  r3, r1
fastboot_code_copy_loop:
	ldmia r1!, {r4-r11}
	stmia r2!, {r4-r11}
	cmp   r1, r3
	blo   fastboot_code_copy_loop
	ldr   pc, [sp], #4       /* pop lr */

uart0_init:
	uart_init_m3boot

/******************************************************************************
 copy m3boot loop to end of tcm
******************************************************************************/
m3boot_loop_copy2new_pos:
	ldr  r1, L$_EXECUTE_BOOT_LOOP_RENEW
	ldr  r2, =M3_BOOT_LOOP_NEW_ADDR
	ldr  r3, =_ebss                  /* image end addr, reference to boot.ld */
	ldr  r4, =m3_boot_loop           /* image start addr, reference to boot.ld */
	subs r3, r3, r4
	add  r3, r1
copy_loop:
	ldmia r1!,{r4-r11}
	stmia r2!,{r4-r11}
	cmp   r1, r3
	blo   copy_loop
	bx lr

/******************************************************************************
 The reset handler, which gets called when the processor starts.
******************************************************************************/
	.global  _start
_start:

check_onchiprom_run_stat:
	bl   processor_init
	mov  r0, #0x0
	msr  faultmask, r0

#ifdef ATE_VECTOR
    bl  ate_vector_init
    mov r0, ATE_GPIO_M3BOOT_ATE_INIT
    bl ate_gpio_on
#endif
	ldr  r1, = OCR_INITED_FLAG_ADDR    /* 0x4fe1fffc */
	ldr  r2, = OCR_INITED_FLAG_VALUE   /* 0x23456789 */
	ldr  r3, [r1]
	cmp  r2,r3

	beq  m3_no_need_selfcopy
/******************************************************************************
 copy m3 boot code to tcm memory
******************************************************************************/
m3boot_code_copy2tcm:
	ldr  r1, =HI_NAND_MEM_BUFFER_ADDR
	ldr  r2, =HI_M3TCM0_MEM_ADDR
#ifndef BSP_CONFIG_EDA
	ldr  r3, =__file_size	   /* file size reference to boot.ld */
#else
	ldr  r3, =0x400
#endif

	add  r3, r1
m3boot_code_copy_loop:
	ldmia r1!,{r4-r11}
	stmia r2!,{r4-r11}
	cmp   r1, r3
	blo  m3boot_code_copy_loop


jump2_m3boot_exec_addr:
	ldr  r0, L$_EXECUTE_IN_TCM
	mov  pc, r0

EXECUTE_IN_TCM:
remap_clr:       /* remap clear, address space 0x0~0x1FFF_FFFF map to TCM */
	ldr  r0, =(HI_SYSCTRL_AO_REG_BASE_ADDR + HI_SC_AO_CTRL0_OFFSET)     /* 0x90000400 */
	ldr  r1, [r0]
	ldr  r3, =0x1
	orr  r1, r1, r3
	str  r1, [r0]

	/* 安全根ca校验标识，需要在这里清零 */

	/* dead loop for debug*/
	@b    .

m3_no_need_selfcopy:
	/* first modify onchiprom boot flag in axi memory */
	ldr  r1, = OCR_INITED_FLAG_ADDR     /* 0x4fe00000+0x20000-4=0x4fe1fffc */
	ldr  r2, = OCR_UNINITED_FLAG_VALUE  /* 0xA55A6789 */
	str  r2, [r1]

	/* onchiprom also config partitial sysctrl */
	bl   sysctrl_init
	bl   uart0_init
#ifdef ATE_VECTOR
    mov r0, ATE_GPIO_M3BOOT_UART0_INIT
    bl ate_gpio_on
#endif

	bl   mddrc_init
#ifdef ATE_VECTOR
    mov r0, ATE_GPIO_M3BOOT_DDR_INIT
    bl ate_gpio_on
#endif

	print_uart_m3boot(0x31)
#ifdef CONFIG_BALONG_HPM_TEMP
	bl   boosting
	print_uart_m3boot(0x32)
	bl   dfs_to_max
#endif
	print_uart_m3boot(0x33)
	/* copy wait m3image to be loaded code to new position */
	bl   m3boot_loop_copy2new_pos
#ifdef ATE_VECTOR
    mov r0, ATE_GPIO_M3BOOT_CPYM3TOTCM
    bl ate_gpio_on
#endif

	/* boot fastboot */
	bl   fastboot_code_copy2ddr
	print_uart_m3boot(0x34)
#ifdef ATE_VECTOR
    mov r0, ATE_GPIO_M3BOOT_CPYFBOOTTOAXI
    bl ate_gpio_on
#endif

#ifdef ATE_VECTOR
	bl ate_vector_m3boot
#endif

	/* secure boot: verify fastboot.img */
	ldr  r0, =RUN_BASE_ADDR_APPA9
	bl   bsp_sec_check_fastboot
	print_uart_m3boot(0x35)

	bl   acore_unreset
	print_uart_m3boot(0x36)
	print_uart_m3boot(0x0a)

	/* jump into new position to wait m3image to be loaded */
	ldr  r0, =M3_BOOT_LOOP_NEW_ADDR
	mov  pc, r0

	.text
	.balign 4
	.global m3_boot_loop
	.thumb_func
m3_boot_loop:
	wfi
	b m3_boot_loop

/******************************************************************************
 This is the end of the file.
******************************************************************************/
	.balign 4
L$_EXECUTE_IN_TCM:
	.long   HI_M3TCM0_MEM_ADDR + EXECUTE_IN_TCM - m3boot

L$_EXECUTE_BOOT_LOOP_RENEW:
	.long   HI_M3TCM0_MEM_ADDR + ALIGN(m3_boot_loop - m3boot, 2)

	.end

