

#ifndef __SOC_INTERRUPTS_APP_H__
#define __SOC_INTERRUPTS_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "soc_interrupts_comm.h"

/**************************************************************************
                  * interrupts level app only*
***************************************************************************/
/*K3 AP侧timer驱动由K3提供*/
#define INT_LVL_TIMER0                        68
#define INT_LVL_TIMER1                        69
#define INT_LVL_TIMER2                        70
#define INT_LVL_TIMER3                        71
#define INT_LVL_TIMER4                        72
#define INT_LVL_TIMER5                        73
#define INT_LVL_TIMER6                        74
#define INT_LVL_TIMER7                        75
#define INT_LVL_TIMER8                        76
#define INT_LVL_TIMER9                        77
#define INT_LVL_TIMER10                       78
#define INT_LVL_TIMER11                       79
#define INT_LVL_TIMER12                       80
#define INT_LVL_TIMER13                       81
#define INT_LVL_TIMER14                       82
#define INT_LVL_TIMER15                       83
#define INT_LVL_TIMER16                       1000
#define INT_LVL_TIMER17                       1000
#define INT_LVL_TIMER18                       1000
#define INT_LVL_TIMER19                       1000
#define INT_LVL_TIMER20                       1000
#define INT_LVL_TIMER21                       1000
#define INT_LVL_TIMER22                       1000
#define INT_LVL_TIMER23                       1000

/* need to remove gpio */
#define INT_LVL_APP_GPIO0                     112
#define INT_LVL_APP_GPIO1                     113
#define INT_LVL_APP_GPIO2                     114
#define INT_LVL_APP_GPIO3                     115

#define INT_LVL_IPCM2APP0                     252
#define INT_LVL_IPCM2APP1                     253

#define INT_LVL_RTC                           86
#define INT_LVL_SOCP0                         248
#define INT_LVL_SOCP1                         249

#define INT_LVL_IPC_S0                        205
#define INT_LVL_IPC_S1                        206
#define INT_LVL_IPC_S4                        207
#define INT_LVL_IPC_S_MBX0                    208
#define INT_LVL_IPC_S_MBX1                    209
#define INT_LVL_IPC_S_MBX2                    210
#define INT_LVL_IPC_S_MBX3                    211
#define INT_LVL_IPC_S_MBX4                    212
#define INT_LVL_IPC_S_MBX5                    213
#define INT_LVL_IPC_S_MBX6                    214
#define INT_LVL_IPC_S_MBX7                    215
#define INT_LVL_IPC_S_MBX8                    216
#define INT_LVL_IPC_S_MBX9                    217
#define INT_LVL_IPC_S_MBX18                   218
#define INT_LVL_IPC_NS0                       220
#define INT_LVL_IPC_NS1                       221
#define INT_LVL_IPC_NS4                       222
#define INT_LVL_IPC_NS5                       223
#define INT_LVL_IPC_NS6                       224
#define INT_LVL_IPC_NS_MBX0                   225
#define INT_LVL_IPC_NS_MBX1                   226
#define INT_LVL_IPC_NS_MBX2                   227
#define INT_LVL_IPC_NS_MBX3                   228
#define INT_LVL_IPC_NS_MBX4                   229
#define INT_LVL_IPC_NS_MBX5                   230
#define INT_LVL_IPC_NS_MBX6                   231
#define INT_LVL_IPC_NS_MBX7                   232
#define INT_LVL_IPC_NS_MBX8                   233
#define INT_LVL_IPC_NS_MBX9                   234
#define INT_LVL_IPC_NS_MBX18                  235
#define INT_LVL_WDT										237

#define INT_LVL_MAX                           224

/* need to remove GUINT*/
#define INT_LVL_UICC                          39
#define INT_LVL_UPACC_BBP_I1_E                40
#define INT_LVL_UPACC_BBP_I2                  41

#define INT_LVL_IPF0                          250
#define INT_LVL_IPF1                          251

#define INT_LVL_CICOM0_UL                     51
#define INT_LVL_CICOM0_DL                     52
#define INT_LVL_CICOM1_UL                     53
#define INT_LVL_CICOM1_DL                     54
#define INT_LVL_UPACC_ARM                     55
#define INT_LVL_HDLC_FRM                      56
#define INT_LVL_HDLC_DEF                      57
#define INT_LVL_G1_BBP_TO_CPU                 68
#define INT_LVL_G1_BBP_TO_DSP                 69
#define INT_LVL_G1_BBP_TO_CPU_32K             70
#define INT_LVL_G1_BBP_TO_DSP_32K             71
#define INT_LVL_G2_BBP_TO_CPU                 72
#define INT_LVL_G2_BBP_TO_DSP                 73
#define INT_LVL_G2_BBP_TO_CPU_32K             74
#define INT_LVL_G2_BBP_TO_DSP_32K             75
#define INT_LVL_TDS_DRX_WAKEUP               152
#define INT_LVL_W_ARM_01                     162
#define INT_LVL_W_ARM_02                     163
#define INT_LVL_W_ARM_03                     164
#define INT_LVL_W_ARM_04                     165
#define INT_LVL_W_ARM_05                     166
#define INT_LVL_W_ARM_06                     167
#define INT_LVL_W_ARM_07                     168
#define INT_LVL_W_ARM_08                     169
#define INT_LVL_W_ARM_09                     170
#define INT_LVL_W_ARM_10                     171
#define INT_LVL_W_ARM_11                     172
#define INT_LVL_OTDOA                        173
#define INT_LVL_CTU_W                        174
#define INT_LVL_CTU_G1                       175
#define INT_LVL_CTU_G2                       176
#define INT_LVL_W_BBE16_13                   177
#define INT_LVL_W_BBE16_14                   178

/*GU INT*/
#define	INT_LVL_GBBP_DSP                  INT_LVL_G1_BBP_TO_DSP
#define INT_LVL_GBBP_GSML_NODRX_INTR      INT_LVL_G1_BBP_TO_DSP
#define INT_LVL_GBBP_AWAKE_DSP            INT_LVL_G1_BBP_TO_DSP_32K
#define INT_LVL_GBBP_GSML_RESERVED_INTR   INT_LVL_G1_BBP_TO_DSP_32K
#define INT_LVL_GBBP                      INT_LVL_G1_BBP_TO_CPU
#define INT_LVL_GBBP_AWAKE                INT_LVL_G1_BBP_TO_CPU_32K
#define INT_LVL_GBBP1_DSP                 INT_LVL_G2_BBP_TO_DSP
#define INT_LVL_GBBP1_AWAKE_DSP           INT_LVL_G2_BBP_TO_DSP_32K
#define INT_LVL_GBBP1                     INT_LVL_G2_BBP_TO_CPU
#define INT_LVL_GBBP1_AWAKE               INT_LVL_G2_BBP_TO_CPU_32K
#define INT_LVL_WBBP_0MS                  INT_LVL_W_ARM_01
#define INT_LVL_WBBP_AWAKE                INT_LVL_W_ARM_02
#define INT_LVL_WBBP_SWITCH               INT_LVL_W_ARM_03
#define INT_LVL_WBBP1_0MS                 INT_LVL_W_ARM_04
#define INT_LVL_WBBP_CARD2_0MS_INTR       INT_LVL_W_ARM_04
#define INT_LVL_WBBP_SEARCH               INT_LVL_W_ARM_05
#define INT_LVL_WBBP_SEARCH_INTR          INT_LVL_W_ARM_05
#define INT_LVL_WBBP_RAKE                 INT_LVL_W_ARM_06
#define INT_LVL_WBBP_RAKE_INTR            INT_LVL_W_ARM_06
#define INT_LVL_WBBP_DECODE               INT_LVL_W_ARM_07
#define INT_LVL_WBBP_DECODE_INTR          INT_LVL_W_ARM_07
#define INT_LVL_WBBP_TIME                 INT_LVL_W_ARM_08
#define INT_LVL_WBBP_CARD1_TIME_INTR      INT_LVL_W_ARM_08
#define INT_LVL_WBBP1_TIME                INT_LVL_W_ARM_09
#define INT_LVL_WBBP_CARD2_TIME_INTR      INT_LVL_W_ARM_09
#define INT_LVL_WBBP_MULTI_SEARCH         INT_LVL_W_ARM_10
#define INT_LVL_WBBP_MULTI_SEARCH_INTR    INT_LVL_W_ARM_10
#define INT_LVL_WBBP_BBPMST               INT_LVL_W_ARM_11
#define INT_LVL_BBPMASTER                 INT_LVL_W_ARM_11
#define INT_LVL_CTU_INT_G                 INT_LVL_CTU_G1
#define INT_LVL_CTU_INT_W                 INT_LVL_CTU_W
#define INT_LVL_INT12_G2                  1000000

#define INT_LVL_UPACC_DSP                 1000000
#define INT_LVL_GU_UPACC_DSP              INT_LVL_UPACC_DSP
#define INT_LVL_UPACC_INTR                INT_LVL_UPACC_ARM

#define INT_LVL_GU_HDLC_FRM               INT_LVL_HDLC_FRM
#define INT_LVL_GU_HDLC_DEF               INT_LVL_HDLC_DEF
#define INT_LVL_CICOM_DL                  INT_LVL_CICOM0_DL
#define INT_LVL_CICOM_UL                  INT_LVL_CICOM0_UL
#define INT_LVL_GU_CICOM1_DL              INT_LVL_CICOM1_DL
#define INT_LVL_GU_CICOM1_UL              INT_LVL_CICOM1_UL


/*LTE INT*/
#define INT_LVL_LTE_ARM_POSITION_INT            1000000
#define INT_LVL_LTE_ARM_DL_DMA_INT              1000000
#define INT_LVL_LTE_ARM_CLK_SWITCH_INT          1000000
#define INT_LVL_LTE_BBP_WAKEUP                  1000000
#define INT_LVL_LTE_ARM_WAKEUP_INT              INT_LVL_LTE_BBP_WAKEUP
#define INT_LVL_LTE_ARM_PUB_INT                 1000000
#define INT_LVL_LTE_APP_ARM_PUB_INT             1000000
#define INT_LVL_LTE_ARM_POSITION_INTS           1000000
#define INT_LVL_LTE_ARM_DL_DMA_INTS             1000000
#define INT_LVL_TDS_STU_ARM_INT                 1000000
#define INT_LVL_TDS_DRX_ARM_CLKSWITCH_INT       1000000
#define INT_LVL_TDS_DRX_ARM_WAKEUP_INT          INT_LVL_TDS_DRX_WAKEUP
#define INT_LVL_VIC_CIPHER                      1000000
#define INT_LVL_VIC_IPF_INTR0                   1000000
#define INT_LVL_VIC_IPF_INTR1                   1000000
#define INT_LVL_VIC_SOCP_INTR0                  1000000
#define INT_LVL_VIC_SOCP_INTR1                  1000000
#define INT_LVL_CTU_INT_LTE                     1000000
#define INT_LVL_CTU_INT_TDS                     1000000
#ifdef __cplusplus
}
#endif

#endif    /* __SOC_INTERRUPTS_APP_H */


