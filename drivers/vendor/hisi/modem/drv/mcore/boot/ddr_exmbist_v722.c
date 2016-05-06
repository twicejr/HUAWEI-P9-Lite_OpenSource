
#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <hi_uart.h>
#include "ddr_exmbist_v722.h"
#include "bsp_ate.h"

u32 bist_size_cfg = 0;


void static inline exmbist_write(u32 reg_addr, u32 reg_val)
{
    writel(reg_val,reg_addr);
}
static int inline exmbist_wait_reg(u32 reg_addr, u32 expect_val,u32 reg_mask, u32 wait_time)
{
    u32 reg_val;
    reg_val = readl(reg_addr);
	/* 判断方式有变化，只判断一个bit */
    while( (reg_val&(0x1<<0)) != 1){
        reg_val = readl(reg_addr);
    }
    if( (reg_val&(0x1<<1)) != (0x1<<1) ){
#ifndef ATE_VECTOR
        print_info("Fail\r\n");
        b_loop();
#endif
        return -1;
    }

    return 0;
}
void static inline exmbist_write_mask(u32 reg_addr, u32 mask, u32 val)
{
    u32 reg_val;
    reg_val = readl(reg_addr);
    reg_val = (reg_val&(~mask)) | val;
    writel(reg_val,reg_addr);
}


void exmbist_test_prepare(void)
{
    /* open: clock & srst */
    exmbist_write(0x90000010,    0x01800000);
    exmbist_write(0x90000060,    0x00080000);
    exmbist_write(0x90000064,    0x00080000);
    /* bit0: exmbist enable 使能exmbist功能，CPU访问DDR的通路被切断，切换为exmbist访问DDR，此时CPU不能工作；*/
    exmbist_write_mask(0x90000810,1,1);    //FIXED SC_PERI_CTRL4 [2]=1'b1,soc no request to ddr to self-refresh;[0]=1'b1,exmbist enable
}
void exmbist_test_unprepare(void)
{
    exmbist_write_mask(0x90000810,1,0);
    /* close: clock & srst */
    exmbist_write(0x90000014,    0x01800000);
    exmbist_write(0x90000060,    0x00080000);
}


#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)
void static inline exmbist_udelay(unsigned int us)
{
	while(us--) {
		unsigned long t = (CFG_CLK_CPU_M3_BOOT/3)/1000000;
		while(t--)
			__asm__ __volatile__("nop");
	}
}

void exmbist_config_common(void)
{
    exmbist_write(0x90050060,    0x00000001);    //FIXED open pclk,set apb_gt_en to 1
    exmbist_write(0x90050008,    0x00000001);    //FIXED exmbist enable,set cfg_exmbist_en to 1
    exmbist_write(0x90050014,    0x00000001);    //FIXED select AXI_MST interface of IVP output from MUX,set mux_sel to 1
    exmbist_write(0x90050048,    0x00000000);    //FIXED scan rank0
    exmbist_write(0x9005004c,    0x00000001);    //FIXED dram data width = 32,set cfg_dram_width =1
    exmbist_write(0x90050050,    0x00000000);    //FIXED ddrc is single channel,select channel 0;set cfg_chan_info to 4'h0
    exmbist_write(0x90050054,    0x00000000);    //FIXED address interleve mode;interleve size is 128Byte
    exmbist_write(0x90050028,    0x00000059);    //LPDDR2_S4B_2Gb_32bit(RBC=14,3,9):0x00000059    ;LPDDR2_S4B_1Gb_32bit(RBC=13,3,9) 0x00000051
    exmbist_write(0x90050000,    0x03060e12);    //LPDDR2_S4B_2Gb_32bit(RBC=14,3,9):0x03060e12    ;LPDDR2_S4B_1Gb_32bit(RBC=13,3,9) 0x03060d12
}

int exmbist_9step(void)
{    
    exmbist_config_common();
    exmbist_write(0x90050018,    0x0001003f);    //ots line,set the max outstanding is 64, 
    exmbist_write(0x9005001c,    0x00000001);
    exmbist_write(0x90050020,    0x00000002);
    exmbist_write(0x90050024,    0x00000003);
    exmbist_write(0x90050078,    0x00000004);
    exmbist_write(0x90050000,    0x00000013);    //SET_BASE_PAT
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050004,    0x55555555);
    exmbist_write(0x90050000,    0x00000011);    //
    exmbist_write(0x90050004,    0x00000000);    //cfg_min_addr[31: 0]
    exmbist_write(0x90050004,    0x00000000);    //cfg_min_addr[34:32]
    exmbist_write(0x90050004,    bist_size_cfg);    //cfg_max_addr[31: 0] ->7fffff  -> 3fffff
    exmbist_write(0x90050004,    0x00000000);    //cfg_max_addr[34:32]
    exmbist_write(0x90050000,    0x00000721);                         //address dir up                         
    exmbist_write(0x90050000,    0x40000120);                         //Step 1 up w0
    return_if(exmbist_wait_reg(0x90050058,    0x00015003,  0x0000ffff,   3000000));
    exmbist_udelay(1);                                               
    exmbist_write(0x90050000,    0x00010020);                         //Step 2 up r0 w1 
    exmbist_write(0x90050000,    0x40004120);                           
    return_if(exmbist_wait_reg(0x90050058,    0x00025003,  0x0000ffff,   3000000));
    exmbist_udelay(1);                                               
    exmbist_write(0x90050000,    0x00410020);                         //Step 3 up r1 w0
    exmbist_write(0x90050000,    0x40000120);                           
    return_if(exmbist_wait_reg(0x90050058,    0x00035003,  0x0000ffff,   3000000));
    exmbist_udelay(1);
    exmbist_write(0x90050000,    0x00000021);                         //address dir down                         
    exmbist_write(0x90050000,    0x00010020);                         //Step 4 down r0 w1 
    exmbist_write(0x90050000,    0x40004120);                         
    return_if(exmbist_wait_reg(0x90050058,    0x00045003,  0x0000ffff,   3000000)); 
    exmbist_udelay(1);                                          
    exmbist_write(0x90050000,    0x00410020);                         //Step 5 down r1 w0
    exmbist_write(0x90050000,    0x40000120);                         
    return_if(exmbist_wait_reg(0x90050058,    0x00055003,  0x0000ffff,   3000000));

    return 0;
}

int exmbist_march_c(void)
{
    exmbist_9step();
    exmbist_udelay(1);                                             //Step 6 down r0  
    exmbist_write(0x90050000,    0x40010020);                         
    return_if(exmbist_wait_reg(0x90050058,    0x00065003,  0x0000ffff,   3000000));

    return 0;
}

int _exmbist_ac_prbs(enum exmbist_type test_type)
{
    u32 reg_val = 0;
    
    if(bist_prbs7 == test_type){
        reg_val = 0x00001027;
    }else if (bist_prbs15 == test_type){
        reg_val = 0x00001227;
    }else{
        print_info("_exmbist_ac_prbs type err");
    }
    exmbist_write(0x90040020,  0x30107500);    //DDRC_CONFIG1[9]=wr_rcv_mode = 0;
    exmbist_config_common();
    exmbist_write(0x90050000,  0x03030118);    //SET_ITL   [0]=cfg_itl_en = 1;[15:8]=cfg_itl_bits =8'h03 ;[23:16] =cfg_itl_mode = 8'h03 
    exmbist_write(0x90050018,  0x003f003f);    //ots line,set the max outstanding is 64, 
    exmbist_write(0x9005001c,  0x00000001);    //
    exmbist_write(0x90050020,  0x00000002);
    exmbist_write(0x90050024,  0x00000003);
    exmbist_write(0x90050078,  0x00000004);
    exmbist_write(0x90050000,  0x00000013);    //SET_BASE_PAT
    exmbist_write(0x90050004,  0xabcdef12);
    exmbist_write(0x90050004,  0x5816cdef);
    exmbist_write(0x90050004,  0xfeedcea0);
    exmbist_write(0x90050004,  0xceed1234);
    exmbist_write(0x90050004,  0xdead5678);
    exmbist_write(0x90050004,  0x14169367);
    exmbist_write(0x90050004,  0x58188818);
    exmbist_write(0x90050004,  0x88771528);
    exmbist_write(0x90050000,  0x00000011);    //
    exmbist_write(0x90050004,  0x00000000);    //cfg_min_addr[31: 0]
    exmbist_write(0x90050004,  0x00000000);    //cfg_min_addr[34:32]
    exmbist_write(0x90050004,  0x00000000);    //cfg_max_addr[31: 0]  /*bist_size_cfg*/
    exmbist_write(0x90050004,  0x00000000);    //cfg_max_addr[34:32]
    exmbist_write(0x90050000,  0x00030721);    //address dir up                         

    exmbist_write(0x90050000,  reg_val);    //SEL_PRBS ; 0x00001227: prbs15 with cfg_addr_prbs_skew = 1;0x00001027  : prbs7 with cfg_addr_prbs_skew
    
    //loop = 1
    exmbist_write(0x90050000,  0x00000128);    //SET_ADDR_PRBS_SEED :cfg_addr_prbs_seed[14:0] = 15'h1
    exmbist_write(0x90050000,  0x00000320);                         //Step1 : w0 r0
    exmbist_write(0x90050000,  0x41030020);                   
    return_if(exmbist_wait_reg(0x90050058,    0x00015003,  0x0000ffff,   9000000));                  
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x00004320);                         //Step2 : w1 r1 
    exmbist_write(0x90050000,  0x41430020);                           
    return_if(exmbist_wait_reg(0x90050058,    0x00025003,  0x0000ffff,   9000000));     
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41000320);                         //Step3 : w0
    return_if(exmbist_wait_reg(0x90050058,    0x00035003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41030020);                         //Step4 : r0 
    return_if(exmbist_wait_reg(0x90050058,    0x00045003,  0x0000ffff,   9000000)); 
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41004320);                         //Step5 : w1
    return_if(exmbist_wait_reg(0x90050058,    0x00055003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41430020);                         //Step6 : r1 
    return_if(exmbist_wait_reg(0x90050058,    0x00065003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    
    //loop = 2
    exmbist_write(0x90050000,  0x00000228);    //SET_ADDR_PRBS_SEED :cfg_addr_prbs_seed[14:0] = 15'h1
    exmbist_write(0x90050000,  0x00000320);                         //Step1 : w0 r0
    exmbist_write(0x90050000,  0x41030020);                   
    return_if(exmbist_wait_reg(0x90050058,    0x00075003,  0x0000ffff,   9000000));                  
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x00004320);                         //Step2 : w1 r1 
    exmbist_write(0x90050000,  0x41430020);                           
    return_if(exmbist_wait_reg(0x90050058,    0x00085003,  0x0000ffff,   9000000));     
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41000320);                         //Step3 : w0
    return_if(exmbist_wait_reg(0x90050058,    0x00095003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41030020);                         //Step4 : r0 
    return_if(exmbist_wait_reg(0x90050058,    0x000a5003,  0x0000ffff,   9000000)); 
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41004320);                         //Step5 : w1
    return_if(exmbist_wait_reg(0x90050058,    0x000b5003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41430020);                         //Step6 : r1 
    return_if(exmbist_wait_reg(0x90050058,    0x000c5003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    
    //loop = 3
    exmbist_write(0x90050000,  0x00000328);    //SET_ADDR_PRBS_SEED :cfg_addr_prbs_seed[14:0] = 15'h1
    exmbist_write(0x90050000,  0x00000320);                         //Step1 : w0 r0
    exmbist_write(0x90050000,  0x41030020);                   
    return_if(exmbist_wait_reg(0x90050058,    0x000d5003,  0x0000ffff,   9000000));                  
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x00004320);                         //Step2 : w1 r1 
    exmbist_write(0x90050000,  0x41430020);                           
    return_if(exmbist_wait_reg(0x90050058,    0x000e5003,  0x0000ffff,   9000000));     
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41000320);                         //Step3 : w0
    return_if(exmbist_wait_reg(0x90050058,    0x000f5003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41030020);                         //Step4 : r0 
    return_if(exmbist_wait_reg(0x90050058,    0x00105003,  0x0000ffff,   9000000)); 
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41004320);                         //Step5 : w1
    return_if(exmbist_wait_reg(0x90050058,    0x00115003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41430020);                         //Step6 : r1 
    return_if(exmbist_wait_reg(0x90050058,    0x00125003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    
    //loop = 4
    exmbist_write(0x90050000,  0x00000428);    //SET_ADDR_PRBS_SEED :cfg_addr_prbs_seed[14:0] = 15'h1
    exmbist_write(0x90050000,  0x00000320);                         //Step1 : w0 r0
    exmbist_write(0x90050000,  0x41030020);                   
    return_if(exmbist_wait_reg(0x90050058,    0x00135003,  0x0000ffff,   9000000));                  
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x00004320);                         //Step2 : w1 r1 
    exmbist_write(0x90050000,  0x41430020);                           
    return_if(exmbist_wait_reg(0x90050058,    0x00145003,  0x0000ffff,   9000000));     
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41000320);                         //Step3 : w0
    return_if(exmbist_wait_reg(0x90050058,    0x00155003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41030020);                         //Step4 : r0 
    return_if(exmbist_wait_reg(0x90050058,    0x00165003,  0x0000ffff,   9000000)); 
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41004320);                         //Step5 : w1
    return_if(exmbist_wait_reg(0x90050058,    0x00175003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41430020);                         //Step6 : r1 
    return_if(exmbist_wait_reg(0x90050058,    0x00185003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    
    //loop = 5
    exmbist_write(0x90050000,  0x00000528);    //SET_ADDR_PRBS_SEED :cfg_addr_prbs_seed[14:0] = 15'h1
    exmbist_write(0x90050000,  0x00000320);                         //Step1 : w0 r0
    exmbist_write(0x90050000,  0x41030020);                   
    return_if(exmbist_wait_reg(0x90050058,    0x00195003,  0x0000ffff,   9000000));                  
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x00004320);                         //Step2 : w1 r1 
    exmbist_write(0x90050000,  0x41430020);                           
    return_if(exmbist_wait_reg(0x90050058,    0x001a5003,  0x0000ffff,   9000000));     
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41000320);                         //Step3 : w0
    return_if(exmbist_wait_reg(0x90050058,    0x001b5003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41030020);                         //Step4 : r0 
    return_if(exmbist_wait_reg(0x90050058,    0x001c5003,  0x0000ffff,   9000000)); 
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41004320);                         //Step5 : w1
    return_if(exmbist_wait_reg(0x90050058,    0x001d5003,  0x0000ffff,   9000000));
    exmbist_udelay(1000);
    exmbist_write(0x90050000,  0x41430020);                         //Step6 : r1 
    return_if(exmbist_wait_reg(0x90050058,    0x001e5003,  0x0000ffff,   9000000));

    return 0;
}

int exmbist_ac_prbs7(void)
{
    return _exmbist_ac_prbs(bist_prbs7);
}
int exmbist_ac_prbs15(void)
{
    return _exmbist_ac_prbs(bist_prbs15);
}

int _exmbist_sur_btfly(enum exmbist_type test_type)
{
    u32 reg_val = 0;
    
    if(bist_surround == test_type){
        reg_val = 0x00010721;
    }else if (bist_butterfly == test_type){
        reg_val = 0x00000721;
    }else{
        print_info("_exmbist_sur_btfly type err");
    }
    exmbist_config_common();
    exmbist_write(0x9005001c,    0x00000001);    //FIXED SECUER_EN axi master operation is not secure
    exmbist_write(0x90050024,    0x00000001);    //merge bypass enable
    exmbist_write(0x90050018,    0x0001003f);    //ots line,set the max outstanding is 64, 
    exmbist_write(0x90050020,    0x00000002);
    exmbist_write(0x90050078,    0x00000004);
    exmbist_write(0x90050000,    0x00000013);    //SET_BASE_PAT
    exmbist_write(0x90050004,    0xabcdef12);
    exmbist_write(0x90050004,    0x5816cdef);
    exmbist_write(0x90050004,    0xfeedcea0);
    exmbist_write(0x90050004,    0xceed1234);
    exmbist_write(0x90050004,    0xdead5678);
    exmbist_write(0x90050004,    0x14169367);
    exmbist_write(0x90050004,    0x58188818);
    exmbist_write(0x90050004,    0x88771528);
    exmbist_write(0x90050000,    0x00000011);    //
    exmbist_write(0x90050004,    0x00000000);    //cfg_min_addr[31: 0]
    exmbist_write(0x90050004,    0x00000000);    //cfg_min_addr[34:32]
    exmbist_write(0x90050004,    bist_size_cfg);    //cfg_max_addr[31: 0]
    exmbist_write(0x90050004,    0x00000000);    //cfg_max_addr[34:32]
    exmbist_write(0x90050000,    reg_val);       //address dir up  surround                       
    exmbist_write(0x90050000,    0x40000120);                         //Step1 : w0
    return_if(exmbist_wait_reg(0x90050058,    0x00015003,  0x0000ffff,   3000000));                  
    exmbist_udelay(1);                                               
    exmbist_write(0x90050000,    0x00004120);                         //Step2 : w1 {r0 r1} w0 
    exmbist_write(0x90050000,    0x00030020);                           
    exmbist_write(0x90050000,    0x03410020);                           
    exmbist_write(0x90050000,    0x40000120);                           
    return_if(exmbist_wait_reg(0x90050058,    0x00025003,  0x0000ffff,   3000000));     
    exmbist_udelay(1);                                               
    exmbist_write(0x90050000,    0x40004120);                         //Step3 : w1
    return_if(exmbist_wait_reg(0x90050058,    0x00035003,  0x0000ffff,   3000000));
    exmbist_udelay(1);
    exmbist_write(0x90050000,    0x00000120);                         //Step4 : w0 {r1 r0} w1 
    exmbist_write(0x90050000,    0x00430020);                          
    exmbist_write(0x90050000,    0x03010020);                          
    exmbist_write(0x90050000,    0x40004120);                          
    return_if(exmbist_wait_reg(0x90050058,    0x00045003,  0x0000ffff,   3000000)); 

    return 0;
}

int exmbist_butterfly(void)
{
    return _exmbist_sur_btfly(bist_butterfly);
}
int exmbist_surround(void)
{
    return _exmbist_sur_btfly(bist_surround);
}

int exmbist_dq_prbs_la(void)
{   
    exmbist_config_common();
    exmbist_write(0x9005002c,    0x0000005a);        
    exmbist_write(0x9005001c,    0x00000001);        
    exmbist_write(0x90050020,    0x00000002);        
    exmbist_write(0x90050024,    0x00000003);        
    exmbist_write(0x90050078,    0x00000004);        
    exmbist_write(0x90050000,    0x00000013);    //SET_BASE_PAT    
    exmbist_write(0x90050004,    0xfe0001ed);        
    exmbist_write(0x90050004,    0xbe0002ef);        
    exmbist_write(0x90050004,    0xde0003ad);        
    exmbist_write(0x90050004,    0xad0004ef);        
    exmbist_write(0x90050004,    0xfe0005ed);        
    exmbist_write(0x90050004,    0xbe0006ef);        
    exmbist_write(0x90050004,    0xde0007ad);        
    exmbist_write(0x90050004,    0xadef0008);        
    exmbist_write(0x90050000,    0x03030118);    //SET_ITL   [0]=cfg_itl_en = 1;[15:8]=cfg_itl_bits =8'h03 ;[23:16] =cfg_itl_mode = 8'h03     
    exmbist_write(0x90050000,    0x00050721);         
    exmbist_write(0x90050000,    0x00000027);    //SET PRBS :prbs7,cfg_addr_prbs_skew = 0
    exmbist_write(0x90050000,    0x004da528);
    exmbist_write(0x90050000,    0x005a5a32);    //SET_ADDR_PRBS_BIT_INV cfg_addr_prbs_bit_inv[14:0]=0x5a5a,set some bit to invert
    exmbist_write(0x90050000,    0x41001720);
    exmbist_write(0x90050000,    0x41001720);
    return_if(exmbist_wait_reg(0x90050058,    0x00015003,  0x0000ffff,   3000000));
    exmbist_udelay(1);
    exmbist_write(0x90050000,    0x41170020);
    return_if(exmbist_wait_reg(0x90050058,    0x00025003,  0x0000ffff,   3000000));
    exmbist_udelay(1);

    return 0;
}

int exmbist_shift_pattern(void)
{
    exmbist_config_common();
    exmbist_write(0x9005001c,    0x00000000);    //FIXED SECUER_EN axi master operation is secure
    exmbist_write(0x90050018,    0x0001003f);    //FIXED OTS_LINE rd_ots_line must be 1,otherwise will be wrong
    exmbist_write(0x90050018,    0x0001003f);
    exmbist_write(0x90050000,    0x00000011);
    exmbist_write(0x90050004,    0x00000000);
    exmbist_write(0x90050004,    0x00000000);
    exmbist_write(0x90050004,    bist_size_cfg);
    exmbist_write(0x90050004,    0x00000000);
    exmbist_write(0x90050000,    0x00000013);
#if 1
    exmbist_write(0x90050004,    0x00ff29fc);
    exmbist_write(0x90050004,    0x00000000);
    exmbist_write(0x90050004,    0x52419f33);
    exmbist_write(0x90050004,    0x00000000);
    exmbist_write(0x90050004,    0xae278986);
    exmbist_write(0x90050004,    0x00000000);
    exmbist_write(0x90050004,    0xf13e2c45);
    exmbist_write(0x90050004,    0x00000000);
#endif

    exmbist_write(0x90050000,    0x00000019);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050004,    0xffffffff);
    exmbist_write(0x90050000,    0x00000721);
    exmbist_write(0x90050000,    0x40001120);    //[4:2]=data pattern=3'd4,left rotated shift of crg_base_pat
    return_if(exmbist_wait_reg(0x90050058,    0x00015003,  0x0000ffff,  3000000));
    exmbist_udelay(1);
    exmbist_write(0x90050000,    0x40110020);
    return_if(exmbist_wait_reg(0x90050058,    0x00025003,  0x0000ffff,  3000000));

    return 0;
}

void exmbist_test(u32 ddr_size)
{
    if(ddr_size==2){
        bist_size_cfg = EXMBIST_SIZE_2GB;
    }else{
        bist_size_cfg = EXMBIST_SIZE_1GB;
    }
    print_info("exmbist start \r\n");
    if(exmbist_test_chose(exmbsit_chose_1)){
        print_info("  9step ");
        exmbist_test_prepare();
        (void)exmbist_9step();
        exmbist_test_unprepare();
        print_info("OK\r\n  march_c ");
        exmbist_test_prepare();
        (void)exmbist_march_c();
        exmbist_test_unprepare();
    }
    if(exmbist_test_chose(exmbsit_chose_2)){
        print_info("OK\r\n  ac_prbs7 ");
        exmbist_test_prepare();
        (void)exmbist_ac_prbs7();
        exmbist_test_unprepare();
        print_info("OK\r\n  ac_prbs15 ");
        exmbist_test_prepare();
        (void)exmbist_ac_prbs15();
        exmbist_test_unprepare();
    }
    if(exmbist_test_chose(exmbsit_chose_3)){
        print_info("OK\r\n  butterfly ");
        exmbist_test_prepare();
        (void)exmbist_butterfly();
        exmbist_test_unprepare();
        print_info("OK\r\n  surround ");
        exmbist_test_prepare();
        (void)exmbist_surround();
        exmbist_test_unprepare();
    }
    if(exmbist_test_chose(exmbsit_chose_4)){
        print_info("OK\r\n  dq_prbs_la ");
        exmbist_test_prepare();
        (void)exmbist_dq_prbs_la();
        exmbist_test_unprepare();
    }
    if(exmbist_test_chose(exmbsit_chose_4)){
        print_info("OK \r\n  shift_pattern ");
        exmbist_test_prepare();
        (void)exmbist_shift_pattern();
        exmbist_test_unprepare();
    }
    print_info("OK\r\nexmbist_done\r\n");

}

int exmbist_test_simple(u32 ddr_size)
{
    int ret = 0;
    
    if(ddr_size==2){
        bist_size_cfg = EXMBIST_SIZE_2GB;
    }else{
        bist_size_cfg = EXMBIST_SIZE_1GB;
    }

    //print_info(" exmbist start \r\n");

#if 0
    //print_info("OK\r\n  ac_prbs7 ");
    exmbist_test_prepare();
    ret = exmbist_ac_prbs7();
    if(ret)
    {
        return ret;
    }
    exmbist_test_unprepare();
#endif

#if 0
    //print_info("OK\r\n  ac_prbs15 ");
    exmbist_test_prepare();
    ret = exmbist_ac_prbs15();
    if(ret)
    {
        return ret;
    }
    exmbist_test_unprepare();
#endif

#if 1
    //print_info("OK\r\n  dq_prbs_la ");
    exmbist_test_prepare();
    ret = exmbist_dq_prbs_la();
    if(ret)
    {
        return ret;
    }
    exmbist_test_unprepare();
#endif

    //print_info("OK\r\nexmbist_done\r\n");

    return ret;
}

/* loop back test */
u32 DDRC_PUB_PGCR1[loopback_iolb_end][6] ={
        {0x63808580,0x83808580,0xa3808580,0xa3808580,0xa3808580,0xa3808580},
        {0x6b808580,0x8b808580,0xab808580,0xab808580,0xab808580,0xab808580}
};

#define loopback_writel(reg_addr, reg_val)  exmbist_write(reg_addr, reg_val)

void loopback_judge_print(u32 reg, u32 mask, u32 val)
{
    if( (readl(reg)&(mask)) != val){
        print_info("fail\r\n");
        b_loop();
    }
    else
        print_info("ok\r\n");
}

void loopback_test(enum loopback_iolb type)
{
        loopback_writel(0x90000010 , 0x000007c0);
        loopback_writel(0x90000364 , 0x00060000);
        loopback_writel(0x90040404 , 0x1);
        loopback_writel(0x90040604 , 0x1);
        loopback_writel(0x90040010 , 0x1);
        loopback_writel(0x90040a38 , 0x09090909);
        loopback_writel(0x90040a38 , 0x49494949);
        udelay(1);
        loopback_writel(0x90040a3c , 0x00000009);
        loopback_writel(0x90040a3c , 0x00000049);
        loopback_writel(0x90040804 , 0x80000000);
        while((readl(0x90040818 ) & 0x1) != 0x1)
        {};
        loopback_writel(0x90040820 , 0xe01b8000);
        loopback_writel(0x90040888 , 0x00000408);
        loopback_writel(0x9004080c , DDRC_PUB_PGCR1[type][0]);
        loopback_writel(0x90040a80 , 0x44000285);
        loopback_writel(0x90040b00 , 0x44000285);
        loopback_writel(0x90040b80 , 0x44000285);
        loopback_writel(0x90040c00 , 0x44000285);
        loopback_writel(0x90040c80 , 0x44000284);
        loopback_writel(0x90040d00 , 0x44000284);
        loopback_writel(0x90040d80 , 0x44000284);
        loopback_writel(0x90040e00 , 0x44000284);
        loopback_writel(0x90040e80 , 0x44000284);
        loopback_writel(0x900408b0 , 0x11001586);
        loopback_writel(0x90040810 , 0x00f0081f);
        loopback_writel(0x90040884 , 0x006c64fe);
        loopback_writel(0x90040824 , 0x10008010);
        loopback_writel(0x90040828 , 0x28000400);
        loopback_writel(0x9004082c , 0x00083def);
        loopback_writel(0x90040830 , 0x03209d00);
        loopback_writel(0x90040834 , 0x03400900);
        loopback_writel(0x9004088c , 0x210e0943);
        loopback_writel(0x90040890 , 0x22816295);
        loopback_writel(0x90040894 , 0x10030c32);
        loopback_writel(0x90040898 , 0x0014c5d9);
        loopback_writel(0x900408a0 , 0x00000062);
        loopback_writel(0x900408a4 , 0x00000004);
        loopback_writel(0x900408a8 , 0x00000001);
        loopback_writel(0x90040804 , 0x00020163);
        udelay(10);
        while((readl(0x90040818 ) & 0x1ff0000f) != 0xf)
        {};
        print_info(" init ok\r\n");
        loopback_writel(0x900408e4 , 0x6);
        loopback_writel(0x90040868 , 0x0);
        loopback_writel(0x9004084c , 0x00000014);
        loopback_writel(0x90040854 , 0x00000014);
        loopback_writel(0x9004080c , DDRC_PUB_PGCR1[type][1]);
        loopback_writel(0x900409c4 , 0x00000100);
        loopback_writel(0x900409c8 , 0xfeeffc00);
        loopback_writel(0x900409cc , 0x08000003);
        loopback_writel(0x900409d0 , 0x000000000);
        loopback_writel(0x900409c0 , 0x00048001);
        while((readl(0x900409e8) & 0x1) != 0x1)
        {};
        print_info(" ac ");
        loopback_judge_print(0x900409e8,(0x1<<1),0);
        
        loopback_writel(0x90040880 , 0x00181882);
        loopback_writel(0x90040884 , 0x006c64fe);
        loopback_writel(0x900409c0 , 0x00048003);
        loopback_writel(0x90040808 , 0x03d81e3f);
        loopback_writel(0x90040808 , 0x07d81e3f);
        loopback_writel(0x9004080c , DDRC_PUB_PGCR1[type][2]);
        loopback_writel(0x900409c0 , 0x00054001);
        while((readl(0x900409e8) & 0x1) != 0x1)
        {};
        print_info(" dx0 ");
        loopback_judge_print(0x900409e8,(0x1<<2),0);

        loopback_writel(0x900409c0 , 0x00048003);
        loopback_writel(0x90040808 , 0x03d81e3f);
        loopback_writel(0x90040808 , 0x07d81e3f);
        loopback_writel(0x9004080c , DDRC_PUB_PGCR1[type][3]);
        loopback_writel(0x900409c0 , 0x000d4001);
        while((readl(0x900409e8) & 0x1) != 0x1)
        {};
        print_info(" dx1 ");
        loopback_judge_print(0x900409e8,(0x1<<2),0);
        
        loopback_writel(0x900409c0 , 0x00048003);
        loopback_writel(0x90040808 , 0x03d81e3f);
        loopback_writel(0x90040808 , 0x07d81e3f);
        loopback_writel(0x9004080c , DDRC_PUB_PGCR1[type][4]);
        loopback_writel(0x900409c0 , 0x00154001);
        while((readl(0x900409e8) & 0x1) != 0x1)
        {};
        print_info(" dx2 ");
        loopback_judge_print(0x900409e8,(0x1<<2),0);
        
        loopback_writel(0x900409c0 , 0x00048003);
        loopback_writel(0x90040808 , 0x03d81e3f);
        loopback_writel(0x90040808 , 0x07d81e3f);
        loopback_writel(0x9004080c , DDRC_PUB_PGCR1[type][5]);
        loopback_writel(0x900409c0 , 0x001d4001);
        while((readl(0x900409e8) & 0x1) != 0x1)
        {};
        print_info(" dx3 ");
        loopback_judge_print(0x900409e8,(0x1<<2),0);
        
        loopback_writel(0x90000360 , 0x00060000);
}

