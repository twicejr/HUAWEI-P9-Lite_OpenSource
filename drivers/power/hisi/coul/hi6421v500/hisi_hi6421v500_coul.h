#ifndef _HISI_HI6421V500_COUL_H_
#define _HISI_HI6421V500_COUL_H_

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/notifier.h>
#include <asm/irq.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/huawei/hisi_adc.h>
#include <pmic_interface.h>



#ifndef BIT
#define BIT(x)      (1 << (x))
#endif

#define HI6421V500_VOL_OFFSET_B_ADDR      PMIC_OTP1_0_ADDR(0)
#define HI6421V500_VOL_OFFSET_A_ADDR_0    PMIC_OTP1_0_ADDR(0)
#define HI6421V500_VOL_OFFSET_A_ADDR_1    PMIC_OTP1_3_ADDR(0)
#define HI6421V500_CURRENT                PMIC_CURRENT_0_ADDR(0)
#define HI6421V500_V_OUT                  PMIC_V_OUT_0_ADDR(0)
#define HI6421V500_CL_OUT_BASE            PMIC_CL_OUT0_ADDR(0)
#define HI6421V500_CL_IN_BASE             PMIC_CL_IN0_ADDR(0)
#define HI6421V500_CHG_TIMER_BASE         PMIC_CHG_TIMER0_ADDR(0)
#define HI6421V500_LOAD_TIMER_BASE        PMIC_LOAD_TIMER0_ADDR(0)
#define HI6421V500_CL_INT_BASE            PMIC_CL_INT0_ADDR(0)
#define HI6421V500_VOL_INT_BASE           PMIC_V_INT0_ADDR(0)
#define HI6421V500_OFFSET_CURRENT         PMIC_OFFSET_CURRENT0_ADDR(0)
#define HI6421V500_OFFSET_VOLTAGE         PMIC_OFFSET_VOLTAGE0_ADDR(0)
#define HI6421V500_OCV_VOLTAGE_BASE       PMIC_OCV_VOLTAGE0_ADDR(0)
#define HI6421V500_OCV_CURRENT_BASE       PMIC_OCV_CURRENT0_ADDR(0)
#define HI6421V500_ECO_OUT_CLIN_REG_BASE  PMIC_ECO_OUT_CLIN_0_ADDR(0)
#define HI6421V500_ECO_OUT_CLOUT_REG_BASE PMIC_ECO_OUT_CLOUT_0_ADDR(0)
#define HI6421V500_VOL_FIFO_BASE          PMIC_V_OUT0_PRE0_ADDR(0)
#define HI6421V500_CUR_FIFO_BASE          PMIC_CURRENT0_PRE0_ADDR(0)
#define HI6421V500_COUL_ECO_MASK          PMIC_COUL_ECO_MASK_ADDR(0) 

#define HI6421V500_FIFO_CLEAR             PMIC_CLJ_DEBUG_2_ADDR(0)         //use bit 3
#define HI6421V500_DEBUG_REG              PMIC_CLJ_DEBUG_ADDR(0)
#define HI6421V500_DEBUG_REG2             PMIC_CLJ_DEBUG_2_ADDR(0)
#define HI6421V500_OFFSET_CUR_MODIFY_BASE PMIC_OFFSET_CURRENT_MOD_0_ADDR(0)

/*coul reserverd regs use */
#define HI6421V500_BATTERY_MOVE_ADDR      PMIC_CLJ_RESERVED1_ADDR(0)
#define BATTERY_MOVE_MAGIC_NUM            0xc3
#define BATTERY_PLUGOUT_SHUTDOWN_MAGIC_NUM 0x18

#define HI6421V500_OCV_CHOOSE             PMIC_CLJ_RESERVED2_ADDR(0) /*use bit5*/
#define HI6421V500_COUL_TEMP_PROTECT      PMIC_CLJ_RESERVED2_ADDR(0) /*use bit 4*/
#define HI6421V500_DELTA_RC_SCENE         PMIC_CLJ_RESERVED2_ADDR(0) /*use bit 3*/
#define HI6421V500_PD_BY_OCV_WRONG        PMIC_CLJ_RESERVED2_ADDR(0) /*use bit 2*/
#define HI6421V500_NV_READ_SUCCESS        PMIC_CLJ_RESERVED2_ADDR(0) /*use bit 1*/
#define HI6421V500_NV_SAVE_SUCCESS        PMIC_CLJ_RESERVED2_ADDR(0) /*use bit 0*/
#define USE_SAVED_OCV_FLAG                BIT(5)
#define TEMP_PROTECT_BITMASK              BIT(4)
#define DELTA_RC_SCENE_BITMASK            BIT(3)
#define PD_BY_OCV_WRONG_BIT               BIT(2)
#define NV_READ_BITMASK                   BIT(1)
#define NV_SAVE_BITMASK                   BIT(0)

#define HI6421V500_SAVE_OCV_ADDR          PMIC_CLJ_RESERVED3_ADDR(0) /*use 2byte,reserved3 and reserved4*/
#define HI6421V500_SAVE_OCV_RESERVED      PMIC_CLJ_RESERVED4_ADDR(0)
#define INVALID_TO_UPDATE_FCC             (0x8000)

#define HI6421V500_SAVE_OCV_TEMP_ADDR      PMIC_SOFT_RESERE0_ADDR(0)/*OCV TEMP saved use 2bytes*/
#define HI6421V500_SAVE_OCV_TEMP_RESERVED  PMIC_SOFT_RESERE1_ADDR(0)

/*record last soc*/
#define HI6421V500_SAVE_LAST_SOC  PMIC_SOFT_RESERE2_ADDR(0)/*last soc 0-6bit */
#define HI6421V500_SAVE_LAST_SOC_VAILD  PMIC_SOFT_RESERE2_ADDR(0)/*last soc vaild 7bit */
#define SAVE_LAST_SOC              (BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define SAVE_LAST_SOC_FALG         BIT(7)
#define CLEAR_LAST_SOC_FALG         0x7F

/************************************************************
    coul register of smartstar
************************************************************/
#define HI6421V500_COUL_CTRL_REG         PMIC_CLJ_CTRL_REG_ADDR(0)
#define COUL_CTRL_ENABLE                 BIT(7)
#define COUL_CALI_ENABLE                 BIT(6)
#define COUL_ECO_FLT_100MS               0
#define COUL_ECO_FLT_200MS               BIT(4)
#define COUL_ECO_FLT_300MS               BIT(5)
#define COUL_ECO_FLT_400MS               (BIT(4) | BIT(5))
#define COUL_ALL_REFLASH                 0
#define COUL_ECO_REFLASH                 BIT(3)
#define COUL_ECO_ENABLE                  BIT(2)
#define COUL_ECO_PMU_EN                  (BIT(0) | BIT(1)) 
#define COUL_ECO_DISABLE                 0
#define COUL_FIFO_CLEAR                  BIT(3)
#define DEFAULT_COUL_CTRL_VAL            (COUL_CTRL_ENABLE | COUL_ECO_FLT_100MS | COUL_ALL_REFLASH | COUL_ECO_DISABLE)
#define ECO_COUL_CTRL_VAL   	         (COUL_CTRL_ENABLE | COUL_ECO_FLT_200MS | COUL_ECO_REFLASH | COUL_ECO_PMU_EN)

#define COUL_CLK_MODE_ADDR               PMIC_STATUS1_ADDR(0)
#define XO32K_MODE_MSK                   BIT(2)   // tells 32k or others
#define COUL_32K_CLK_MODE                     BIT(2)
#define NO_32K_MODE                      0

#define HI6421V500_COUL_IRQ_REG          PMIC_COUL_IRQ_ADDR(0)//SOC_SMART_COUL_IRQ_ADDR(0)
#define HI6421V500_COUL_IRQ_MASK_REG     PMIC_COUL_IRQ_MASK_ADDR(0)//SOC_SMART_COUL_IRQ_MASK_ADDR(0)
#define COUL_VBAT_INT_MASK               BIT(3)
#define COUL_CL_IN_MASK                  BIT(2)
#define COUL_CL_OUT_MASK                 BIT(1)
#define COUL_CL_INT_MASK                 BIT(0)
#define DEFAULT_BATTERY_VOL_2_PERCENT    3350
#define DEFAULT_BATTERY_VOL_0_PERCENT    3150

#define HI6421V500_COUL_VERSION_ADDR     PMIC_VERSION4_ADDR(0)
#define COUL_HI6421V5XX                  0x5

#define HI6421V500_COUL_STATE_REG         PMIC_STATE_TEST_ADDR(0)   //Warning: bit change
#define COUL_CALI_ING                    (BIT(0) | BIT(1))

/*bit uah*/
#define BIT_FOR_UAH_32K                  143127
#define BIT_FOR_UAH_DCXO_586             143153

#define FIFO_DEPTH                       10
#define IRQ_MAX                          4
#define R_COUL_MOHM                      10      /* resisitance mohm */

/* vol offset a/b value*/
#define VOL_OFFSET_A_STEP                100
#define VOL_OFFSET_B_STEP                250
#define VOL_OFFSET_A_BASE                974400
#define VOL_OFFSET_B_BASE                (-15000)
#define VOL_OFFSET_B_VALID_MASK          0x7C
#define VOL_OFFSET_A_HIGH_VALID_MASK     0x80
#define VOL_OFFSET_A_VALID_MASK          0x1FF


extern unsigned int hisi_pmic_reg_read (int reg_addr);
extern void hisi_pmic_reg_write(int addr, int val);
extern int hisi_pmic_array_read(int addr, char *buff, unsigned int len);
extern int hisi_pmic_array_write(int addr, char *buff, unsigned int len);




#define HI6421V500_REG_READ(regAddr)             hisi_pmic_reg_read(regAddr)
#define HI6421V500_REG_WRITE(regAddr,regval)     hisi_pmic_reg_write((int)(regAddr),(int)regval)
#define HI6421V500_REGS_READ(regAddr,buf,size)   hisi_pmic_array_read((int)(regAddr),(char*)(buf),(int)(size))
#define HI6421V500_REGS_WRITE(regAddr,buf,size)  hisi_pmic_array_write((int)(regAddr),(char*)(buf),(int)(size))


#define HI6421V500_COUL_ERR(fmt,args...) do { printk(KERN_ERR    "[hisi_hi6421v500_coul]" fmt, ## args); } while (0)
#define HI6421V500_COUL_EVT(fmt,args...) do { printk(KERN_WARNING"[hisi_hi6421v500_coul]" fmt, ## args); } while (0)
#define HI6421V500_COUL_INF(fmt,args...) do { printk(KERN_INFO   "[hisi_hi6421v500_coul]" fmt, ## args); } while (0)


struct hi6421v500_coul_device_info
{
    struct device *dev;
    struct delayed_work irq_work;
    int irq;
    unsigned char irq_mask;
};
#endif


