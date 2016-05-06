

#ifndef __DDR_EXMBIST_H__
#define __DDR_EXMBIST_H__


#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>

#define EXMBIST_SIZE_1GB  (0x3fffff)
#define EXMBIST_SIZE_2GB  (0x7fffff)


#define  b_loop() __asm__ __volatile__ ("b .")

enum exmbist_type{
    bist_prbs7,
    bist_prbs15,
    bist_surround,
    bist_butterfly,
};

enum loopback_iolb{
    after_output_buffer = 0,
    before_output_buffer,
    loopback_iolb_end,
};


extern void exmbist_test(u32 ddr_size);
extern int exmbist_test_simple(u32 ddr_size);

extern void loopback_test(enum loopback_iolb type);




/* test_ctrl 
 * use pmu_reg 0x153, wr, val consist when reset
 * 8 bits
 */
#define DDR_TEST_CTRL_REG  (0x9001a000+(0x153<<2))


enum m3boot_ddr_test_ctrl{
    exmbist_run=0,
    exmbist_loop=1,
    
    exmbsit_chose_1,
    exmbsit_chose_2,
    exmbsit_chose_3,
    exmbsit_chose_4,

    
    loopback_run =6,
    loopback_loop =7,
    ddr_test_ctrl_end = 8, /* use pmu reg, 8bit */
};
#if 1
static inline u32 get_m3boot_ddr_test_ctrl(enum m3boot_ddr_test_ctrl bit)
{   return readl(DDR_TEST_CTRL_REG) & (0x1<<bit);   }
#endif

//extern u32 get_m3boot_ddr_test_ctrl(enum m3boot_ddr_test_ctrl bit);

#define exmbist_test_chose(x) get_m3boot_ddr_test_ctrl(x)

#endif

