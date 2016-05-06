
#include "bsp_m3.h"

	.syntax unified
	.arch armv7-m

	.section .stack
	.align 3
#ifdef __STACK_SIZE
	.equ    Stack_Size, __STACK_SIZE
#else
	.equ    Stack_Size, 0x00000400
#endif
	.globl    __StackTop
	.globl    __StackLimit
__StackLimit:
	.space    Stack_Size
	.size __StackLimit, . - __StackLimit
__StackTop:
	.size __StackTop, . - __StackTop

	.section .heap
	.align 3
#ifdef __HEAP_SIZE
	.equ    Heap_Size, __HEAP_SIZE
#else
	.equ    Heap_Size, 0x00000000
#endif
	.globl    __HeapBase
	.globl    __HeapLimit
__HeapBase:
	.if    Heap_Size
	.space    Heap_Size
	.endif
	.size __HeapBase, . - __HeapBase
__HeapLimit:
	.size __HeapLimit, . - __HeapLimit

    .section .isr_vector
    .balign 4
    .globl __isr_vector
__isr_vector:
	.word    __StackTop            /* Top of Stack */
	.word    Reset_Handler        /*Offset 04: Reset handler          */
	.word    NMI_Handler          /*Offset 08: NMI handler            */
	.word    hardfault_dump    /*Offset 0C: Hard fault handler     */
	.word    mem_manage_dump    /*Offset 10: MPU fault handler      */
	.word    bus_fault_dump     /*Offset 14: Bus fault handler      */
	.word    usage_fault_dump   /*Offset 18: Usage fault handler    */
	.word    0                    /*Offset 1C: Reserved               */
	.word    0                    /*Offset 20: Reserved               */
	.word    0                    /*Offset 24: Reserved               */
	.word    0                    /*Offset 28: Reserved               */
	.word    SVC_Handler          /*Offset 2C: SVCall handler         */
	.word    DebugMon_Handler     /*Offset 30: Debug monitor handler  */
	.word    0                    /*Offset 34: Reserved               */
	.word    PendSV_Handler       /*Offset 38: PendSV handler         */
	.word    SysTick_Handler      /*Offset 3C: SysTick handler        */
	
	/* External interrupts */
	.word    handle_bad_irq    /* 16  IPCM_INT0_2           */
	.word    handle_bad_irq    /* 17  IPCM_INT1_2           */
	.word    handle_bad_irq    /* 18  APPA9_EVENTO_INT      */
	.word    handle_bad_irq    /* 19  MDMA9_EVENTO_INT      */
	.word    handle_bad_irq    /* 20  RTC_INT               */
	.word    handle_bad_irq    /* 21  WDT_INT               */
	.word    handle_bad_irq    /* 22  UPACC_DSP_INT         */
	.word    handle_bad_irq    /* 23  UICC_INT              */
	.word    handle_bad_irq    /* 24  GMAC_SBD_INT          */
	.word    handle_bad_irq    /* 25  GMAC_PMT_INT          */
	.word    handle_bad_irq    /* 26  EDMAC_INT2            */
	.word    handle_bad_irq    /* 27  LTE_CIPHER_INT        */
	.word    handle_bad_irq    /* 28  IPF_INT0              */
	.word    handle_bad_irq    /* 29  IPF_INT1              */
	.word    handle_bad_irq    /* 30  SOCP_INT0             */
	.word    handle_bad_irq    /* 31  SOCP_INT1             */
	.word    handle_bad_irq    /* 32  LTESIO_RX_INT         */
	.word    handle_bad_irq    /* 33  LTESIO_SIO_INT        */
	.word    handle_bad_irq    /* 34  LTESIO_TX_INT         */
	.word    handle_bad_irq    /* 35  CICOM0_UL_INT         */
	.word    handle_bad_irq    /* 36  CICOM0_DL_INT         */
	.word    handle_bad_irq    /* 37  CICOM1_UL_INT         */
	.word    handle_bad_irq    /* 38  CICOM1_DL_INT         */
	.word    handle_bad_irq    /* 39  UPACC_ARM_INT         */
	.word    handle_bad_irq    /* 40  HDLC_FRM_INT          */
	.word    handle_bad_irq    /* 41  HDLC_DEF_INT          */
	.word    handle_bad_irq    /* 42  CM3_EVENTO_INT        */
	.word    handle_bad_irq    /* 43  TSENSOR_INT           */
	.word    handle_bad_irq    /* 44  EXT_INT0              */
	.word    handle_bad_irq    /* 45  EXT_INT1              */
	.word    handle_bad_irq    /* 46  EXT_INT2              */
	.word    handle_bad_irq    /* 47  EXT_INT3              */
	.word    handle_bad_irq    /* 48  EXT_INT4              */
	.word    handle_bad_irq    /* 49  EXT_INT5              */
	.word    handle_bad_irq    /* 50  EXT_INT6              */
	.word    handle_bad_irq    /* 51  EXT_INT7              */
	.word    handle_bad_irq    /* 52  EXT_INT8              */
	.word    handle_bad_irq    /* 53  EXT_INT9              */
	.word    handle_bad_irq    /* 54  EXT_INT10             */
	.word    handle_bad_irq    /* 55  EXT_INT11             */
	.word    handle_bad_irq    /* 56  EXT_INT12             */
	.word    handle_bad_irq    /* 57  EXT_INT13             */
	.word    handle_bad_irq    /* 58  EXT_INT14             */
	.word    handle_bad_irq    /* 59  EXT_INT15             */
	.word    handle_bad_irq    /* 60  EXT_INT16             */
	.word    handle_bad_irq    /* 61  TIMER0_INT            */
	.word    handle_bad_irq    /* 62  TIMER1_INT            */
	.word    handle_bad_irq    /* 63  TIMER2_INT            */
	.word    handle_bad_irq    /* 64  TIMER3_INT            */
	.word    handle_bad_irq    /* 65  TIMER4_INT            */
	.word    handle_bad_irq    /* 66  TIMER5_INT            */
	.word    handle_bad_irq    /* 67  TIMER6_INT            */
	.word    handle_bad_irq    /* 68  TIMER7_INT            */
	.word    handle_bad_irq    /* 69  TIMER8_INT            */
	.word    handle_bad_irq    /* 70  TIMER9_INT            */
	.word    handle_bad_irq    /* 71  TIMER10_INT           */
	.word    handle_bad_irq    /* 72  TIMER11_INT           */
	.word    handle_bad_irq    /* 73  TIMER12_INT           */
	.word    handle_bad_irq    /* 74  TIMER13_INT           */
	.word    handle_bad_irq    /* 75  TIMER14_INT           */
	.word    handle_bad_irq    /* 76  TIMER15_INT           */
	.word    handle_bad_irq    /* 77  SCI0_INT              */
	.word    handle_bad_irq    /* 78  SCI1_INT              */
	.word    handle_bad_irq    /* 79  DW_SSI0_INT           */
	.word    handle_bad_irq    /* 80  DW_SSI1_INT           */
	.word    handle_bad_irq    /* 81  TCSSI0_INT            */
	.word    handle_bad_irq    /* 82  TCSSI1_INT            */
	.word    handle_bad_irq    /* 83  USB3_PME_INT          */
	.word    handle_bad_irq    /* 84  MIPI_INT              */
	.word    handle_bad_irq    /* 85  HS_UART_INT           */
	.word    handle_bad_irq    /* 86  UART0_INT             */
	.word    handle_bad_irq    /* 87  UART1_INT             */
	.word    handle_bad_irq    /* 88  UART2_INT             */
	.word    handle_bad_irq    /* 89  UART3_INT             */
	.word    handle_bad_irq    /* 90  NANDC_INT             */
	.word    handle_bad_irq    /* 91  MMC0_INT              */
	.word    handle_bad_irq    /* 92  MMC1_INT              */
	.word    handle_bad_irq    /* 93  MMC2_INT              */
	.word    handle_bad_irq    /* 94  SDCC_INT              */
	.word    handle_bad_irq    /* 95  I2C_INT               */
	.word    handle_bad_irq    /* 96  M3_GPIO_GROUP0_INT    */
	.word    handle_bad_irq    /* 97  M3_GPIO_GROUP1_INT    */
	.word    handle_bad_irq    /* 98  M3_GPIO_GROUP2_INT    */
	.word    handle_bad_irq    /* 99  M3_GPIO_GROUP3_INT    */
	.word    handle_bad_irq    /* 100 M3_GPIO_GROUP4_INT    */
	.word    handle_bad_irq    /* 101 M3_GPIO_GROUP5_INT    */
	.word    handle_bad_irq    /* 102 SSDMA_INT             */
	.word    handle_bad_irq    /* 103 EDMAC_INT0            */
	.word    handle_bad_irq    /* 104 EDMAC_INT1            */
	.word    handle_bad_irq    /* 105 AMON_INT              */
	.word    handle_bad_irq    /* 106 HSIC_INT              */
	.word    handle_bad_irq    /* 107 APPA9_PMUIREQ_INT     */
	.word    handle_bad_irq    /* 108 MDMA9_PMUIREQ_INT     */
	.word    handle_bad_irq    /* 109 HiFi_GPIO2_INT        */
	.word    handle_bad_irq    /* 110 BBE16_GPIO2_INT       */
	.word    handle_bad_irq    /* 111 PMU_INT               */
	.word    handle_bad_irq    /* 112 USB3_OTG_INT          */
	.word    handle_bad_irq    /* 113 X2H_X2P_ERR           */
	.word    handle_bad_irq    /* 114 AXI_ERR               */
	.word    handle_bad_irq    /* 115 USBOTG_BC_INT         */
	.word    handle_bad_irq    /* 116 SYS_CONTROL_INT4      */
	.word    handle_bad_irq    /* 117 SYS_CONTROL_INT5      */
	.word    handle_bad_irq    /* 118 TIMER16_INT           */
	.word    handle_bad_irq    /* 119 TIMER17_INT           */
	.word    handle_bad_irq    /* 120 TIMER18_INT           */
	.word    handle_bad_irq    /* 121 TIMER19_INT           */
	.word    handle_bad_irq    /* 122 TIMER20_INT           */
	.word    handle_bad_irq    /* 123 TIMER21_INT           */
	.word    handle_bad_irq    /* 124 TIMER22_INT           */
	.word    handle_bad_irq    /* 125 TIMER23_INT           */
	.word    handle_bad_irq    /* 126 M3_WAKEUP_INT         */
	.word    handle_bad_irq    /* 127 CPU_AXI_DLOCK_INT     */
	.word    handle_bad_irq    /* 128 GLb_AXI_DLOCK_INT     */
	.word    handle_bad_irq    /* 129 MST_AXI_DLOCK_INT     */
	.word    handle_bad_irq    /* 130 DSP_AXI_DLOCK_INT     */
	.word    handle_bad_irq    /* 131 BBPHY_AXI_DLOCK_INT   */
	.word    handle_bad_irq    /* 132 SDCC_HCLK_WKUP_INT    */
	.word    handle_bad_irq    /* 133 EXT_INT17             */
	.word    handle_bad_irq    /* 134 USBOTG_PHY_INT        */
	.word    handle_bad_irq    /* 135 A15_PMUIRQ_INT0       */
	.word    handle_bad_irq    /* 136 A15_PMUIRQ_INT1       */
	.word    handle_bad_irq    /* 137 DSP0_GPIO2_INT        */
	.word    handle_bad_irq    /* 138 APPA9_ARM_WD_SRST_REQ */
	.word    handle_bad_irq    /* 139 APPA9_L2CC_INT        */
	.word    handle_bad_irq    /* 140 MDMA9_L2CC_INT        */
	.word    handle_bad_irq    /* 141 SDCC_PULL_INT         */
	.word    handle_bad_irq    /* 142 USB3_INT              */
	.word    handle_bad_irq    /* 143 MODA9_ARM_WD_SRST_REQ */
	.word    handle_bad_irq    /* 144 RESERVED              */
	.word    handle_bad_irq    /* 145 RESERVED              */
	.word    handle_bad_irq    /* 146 RESERVED              */
	.word    handle_bad_irq    /* 147 RESERVED              */
	.word    handle_bad_irq    /* 148 RESERVED              */
	.word    handle_bad_irq    /* 149 RESERVED              */
	.word    handle_bad_irq    /* 150 RESERVED              */
	.word    handle_bad_irq    /* 151 RESERVED              */
	.word    handle_bad_irq    /* 152 RESERVED              */
	.word    handle_bad_irq    /* 153 RESERVED              */
	.word    handle_bad_irq    /* 154 RESERVED              */
	.word    handle_bad_irq    /* 155 RESERVED              */
	.word    handle_bad_irq    /* 156 RESERVED              */
	.word    handle_bad_irq    /* 157 RESERVED              */
	.word    handle_bad_irq    /* 158 WDT_MDM_RESET_INT     */
	.word    handle_bad_irq    /* 159 RESERVED              */
	.word    handle_bad_irq    /* 160 RESERVED              */
	.word    handle_bad_irq    /* 161 RESERVED              */
	.word    handle_bad_irq    /* 162 RESERVED              */
	.word    handle_bad_irq    /* 163 RESERVED              */
	.word    handle_bad_irq    /* 164 RESERVED              */
	.word    handle_bad_irq    /* 165 RESERVED              */
	.word    handle_bad_irq    /* 166 RESERVED              */
	.word    handle_bad_irq    /* 167 RESERVED              */
	.word    handle_bad_irq    /* 168 RESERVED              */
	.word    handle_bad_irq    /* 169 RESERVED              */
	.word    handle_bad_irq    /* 170 RESERVED              */
	.word    handle_bad_irq    /* 171 RESERVED              */
	.word    handle_bad_irq    /* 172 WDT_MDM_INT           */
	.word    handle_bad_irq    /* 173 RESERVED              */
	.word    handle_bad_irq    /* 174 RESERVED              */
	.word    handle_bad_irq    /* 175 RESERVED              */
	.word    handle_bad_irq    /* 176 RESERVED              */
	.word    handle_bad_irq    /* 177 RESERVED              */
	.word    handle_bad_irq    /* 178 RESERVED              */
	.word    handle_bad_irq    /* 179 RESERVED              */
	.word    handle_bad_irq    /* 180 WDT_PD_SOC_INT        */
	.word    handle_bad_irq    /* 181 RESERVED              */
	.word    handle_bad_irq    /* 182 RESERVED              */
	.word    handle_bad_irq    /* 183 RESERVED              */
	.word    handle_bad_irq    /* 184 RESERVED              */
	.word    handle_bad_irq    /* 185 RESERVED              */
	.word    handle_bad_irq    /* 186 RESERVED              */
	.word    handle_bad_irq    /* 187 RESERVED              */
	.word    handle_bad_irq    /* 188 RESERVED              */
	.word    handle_bad_irq    /* 189 RESERVED              */
	.word    handle_bad_irq    /* 190 RESERVED              */
	.word    handle_bad_irq    /* 191 RESERVED              */
	.word    handle_bad_irq    /* 192 RESERVED              */
	.word    handle_bad_irq    /* 193 RESERVED              */
	.word    handle_bad_irq    /* 194 RESERVED              */
	.word    handle_bad_irq    /* 195 RESERVED              */
	.word    handle_bad_irq    /* 196 RESERVED              */
	.word    handle_bad_irq    /* 197 RESERVED              */
	.long    0x0D000              /* 52KB */
	.size    __isr_vector, . - __isr_vector

	.text
	.thumb
	.thumb_func
	.align 2
	.globl    Reset_Handler
	.type    Reset_Handler, %function
Reset_Handler:
#if 1
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 4
 *      __bss_end__: end of BSS section. Must align to 4
 */
	ldr r1, =__bss_start__
	ldr r2, =__bss_end__

	movs    r0, 0
	.LC2:
	cmp     r1, r2
	itt    lt
	strlt   r0, [r1], #4
	blt    .LC2
#endif /* __STARTUP_CLEAR_BSS */

	ldr  sp, =__StackTop
    /* ≈‰÷√NVIC */
	ldr  r0, =SCB_VTOR
	ldr  r1, =__isr_vector
	str  r1, [r0]

	/* disable mpu */
	ldr  r0, =MPU_BASE
	mov  r1, #4
	str  r1, [r0,#MPU_CTRL_OFFSET]

	/* region 2: all */
	mov  r1, #0
	str  r1, [r0,#MPU_RNR_OFFSET]
	ldr  r1, =0
	str  r1, [r0,#MPU_RBAR_OFFSET]
	ldr  r1, =0x304003F
	str  r1, [r0,#MPU_RASR_OFFSET]

	/* region 1: nand buffer */
	mov  r1, #1
	str  r1, [r0,#MPU_RNR_OFFSET]
	ldr  r1, =HI_NAND_MEM_BUFFER_ADDR
	str  r1, [r0,#MPU_RBAR_OFFSET]
	ldr  r1, =0x3040037
	str  r1, [r0,#MPU_RASR_OFFSET]

	/* region 3: 256k TCM */
	mov  r1, #2
	str  r1, [r0,#MPU_RNR_OFFSET]
	ldr  r1, =HI_M3TCM0_MEM_ADDR
	str  r1, [r0,#MPU_RBAR_OFFSET]
	ldr  r1, =0x3040023
	str  r1, [r0,#MPU_RASR_OFFSET]

	/* enable mpu */
	ldr  r0, =MPU_BASE
	mov  r1, #5
	str  r1, [r0,#MPU_CTRL_OFFSET]
	mov  r0, #0x0
	msr  primask, r0

	bl    _start
	b .

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_irq_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
	b    .
	.size    \handler_name, . - \handler_name
	.endm

	def_irq_handler    NMI_Handler
	def_irq_handler    HardFault_Handler
	def_irq_handler    MemManage_Handler
	def_irq_handler    BusFault_Handler
	def_irq_handler    UsageFault_Handler
	def_irq_handler    SVC_Handler
	def_irq_handler    DebugMon_Handler
	def_irq_handler    PendSV_Handler
	def_irq_handler    SysTick_Handler
	def_irq_handler    handle_bad_irq
    .end
