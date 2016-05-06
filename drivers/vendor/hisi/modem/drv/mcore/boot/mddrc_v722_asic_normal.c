

#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <hi_syscrg.h>
#include <soc_memmap.h>
#include <hi_uart.h>
#include <bsp_sram.h>

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)
void udelay(unsigned int us)
{
	while(us--) {
		unsigned long t = (CFG_CLK_CPU_M3_BOOT/3)/1000000;
		while(t--)
			__asm__ __volatile__("nop");
	}
}

static void calc_ddrc_dfs(void)
{
    unsigned tmp = 0;
    SRAM_SMALL_SECTIONS * sram_mem = ((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS));
    
    sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_freq = 166;
    sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_freq = 333;

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0x83c);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_83c = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_83c = tmp>>1;

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xabc);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_abc = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_abc = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xb3c);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_b3c = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_b3c = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xbbc);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_bbc = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_bbc = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);
	
	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xc3c);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_c3c = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_c3c = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);

}
struct ddrc_timing_cfgs
{
    u32 DDRC_TIMING0;
    u32 DDRC_TIMING1;
    u32 DDRC_TIMING2;
    u32 DDRC_TIMING3;
    u32 DDRC_PUB_DTPR0;
    u32 DDRC_PUB_DTPR1;
    u32 DDRC_PUB_DTPR2;
    u32 DDRC_PUB_DTPR3;
};

struct ddrc_timing_cfgs ddrc_timing_166 =
{
    .DDRC_TIMING0   = 0x52540c07,
    .DDRC_TIMING1   = 0x0ca74616,
    .DDRC_TIMING2   = 0x6250a028,
    .DDRC_TIMING3   = 0xffca7022,
    .DDRC_PUB_DTPR0 = 0x10870522,
    .DDRC_PUB_DTPR1 = 0x2280b155,
    .DDRC_PUB_DTPR2 = 0x10030c32,
    .DDRC_PUB_DTPR3 = 0x14c319  ,
};
struct ddrc_timing_cfgs ddrc_timing_333 =
{
    .DDRC_TIMING0   = 0x5498170E,
    .DDRC_TIMING1   = 0x18A7462C,
    .DDRC_TIMING2   = 0x64514051,
    .DDRC_TIMING3   = 0xFFD4E033,
    .DDRC_PUB_DTPR0 = 0x210E0943,
    .DDRC_PUB_DTPR1 = 0x22816295,
    .DDRC_PUB_DTPR2 = 0x10030C32,
    .DDRC_PUB_DTPR3 = 0x14C5D9  ,
};

void mddrc_init(void)
{
    u32 reg_val = 0;
    /* 启动频率选择 */
    struct ddrc_timing_cfgs *cfg = &ddrc_timing_333;
    /* add open clk */
    writel( 0x1C0     , 0x90000010 ); 
    udelay( 1 );
    /* unreset */
    writel( 0x60000   , 0x90000364 ); 
    /*  sec bypass  */
    writel( 0x1       , 0x90040404 ); 
    writel( 0x1       , 0x90040604 ); 

    writel( 0x1       , 0x90040010 ); 
    writel( 0x09090909, 0x90040a38 ); 
    udelay( 1 );
    writel( 0x49494949, 0x90040a38 ); 
    writel( 0x00000009, 0x90040a3c ); 
    udelay( 1 );
    writel( 0x00000049, 0x90040a3c ); 
    writel( 0x01e00210, 0x9004001c );  
    writel( 0x00620000, 0x90040014 );    
    writel( 0x00010004, 0x90040018 );      
    writel( 0x30007300, 0x90040020 );   
    writel( 0x131     , 0x9004002c );    
    writel( 0xa0000000, 0x90040040 );   
    writel( cfg->DDRC_TIMING0, 0x90040050 );
    writel( cfg->DDRC_TIMING1, 0x90040054 );
    writel( cfg->DDRC_TIMING3, 0x9004005c );
    writel( 0x0       , 0x900400f4 );
    /* bit[10:0] taref自动刷新周期。0x000：自动刷新禁止 */
    writel( cfg->DDRC_TIMING2 & (~(0x7ff)), 0x90040058 );
    writel( 0x0f000501, 0x900400ac ); 
    writel( 0x0       , 0x90040004 );  
    while((readl(0x90040000)&(0x1<<2)) != 0)
    {};
    writel( 0x80000000, 0x90040804 ); 
    while((readl(0x90040818)&0x1) != 1)
    {};
    writel( 0xe01b8000, 0x90040820 ); 
    writel( 0x00000008, 0x90040888 ); 
    writel( 0x06008580, 0x9004080c ); 
    writel( 0x04000085, 0x90040a80 ); 
    writel( 0x04000085, 0x90040b00 );  
    writel( 0x04000085, 0x90040b80 ); 
    writel( 0x04000085, 0x90040c00 );  
    writel( 0x04000084, 0x90040c80 );  
    writel( 0x04000084, 0x90040d00 ); 
    writel( 0x04000084, 0x90040d80 );  
    writel( 0x04000084, 0x90040e00 );  
    writel( 0x04000084, 0x90040e80 ); 
    writel( 0x01001586, 0x900408b0 ); 
    writel( 0x006c64fe, 0x90040884 ); 
    writel( 0x00055002, 0x90040ac8 ); 
    writel( 0x00055002, 0x90040b48 ); 
    writel( 0x00055002, 0x90040bc8 ); 
    writel( 0x00055002, 0x90040c48 ); 
    writel( 0x20010010, 0x90040824 );
    writel( 0x19000900, 0x90040828 );
    writel( 0x0321046b, 0x90040830 );
    writel( 0x05380e53, 0x90040834 );
    writel( cfg->DDRC_PUB_DTPR0, 0x9004088c ); 
    writel( cfg->DDRC_PUB_DTPR1, 0x90040890 );       
    writel( cfg->DDRC_PUB_DTPR2, 0x90040894 ); 
    writel( cfg->DDRC_PUB_DTPR3, 0x90040898 ); 
    writel( 0x00000062, 0x900408a0 ); 
    writel( 0x00000004, 0x900408a4 ); 
    writel( 0x00000001, 0x900408a8 ); 
    writel( 0x00181884, 0x90040880 ); 
    writel( 0x000000cc, 0x90040a44 ); 
    writel( 0x000000dd, 0x90040a54 ); 
    writel( 0x04058906, 0x90040a40 ); 
    /* wait 10 * pclk */
    udelay( 1 );
    writel( 0x04058902, 0x90040a40 ); 
    writel( 0x0000aaaa, 0x90040a88 ); 
    writel( 0x0000aaaa, 0x90040b08 ); 
    writel( 0x0000aaaa, 0x90040b88 ); 
    writel( 0x0000aaaa, 0x90040c08 ); 
    writel( 0x00002000, 0x90040a8c ); 
    writel( 0x00002000, 0x90040b0c ); 
    writel( 0x00002000, 0x90040b8c ); 
    writel( 0x00002000, 0x90040c0c ); 
   /* diff init_normal */
    writel( 0x00020163, 0x90040804 );
    #ifndef BSP_CONFIG_EDA
    udelay( 100 );
    #else
    udelay( 10 );
    #endif
    
    /* normal diff 1F */
    while((readl(0x90040818)&0x1F) != 0x1F)
    {};
    /* line 579  when [0]=1, it means full initialization completed.
    Then check value, if [28:20]!=9'b0, it means erros happen.
    should check the reason !!!    */
    reg_val = readl(0x90040818);
    if(reg_val&0x1FF00000){
        print_info(" ddr init dead 1, reg[818] expect bit[28:20]=0 \r\n");
        asm volatile ("b .");
    }
    /* diff init_normal ---end */
    /* timing2 之后，都一样 */
    writel( cfg->DDRC_TIMING2, 0x90040058 );
    writel( 0x30107700, 0x90040020 );   
    writel( 0x0       , 0x900400f8 ); 
    udelay( 100 );
    writel( 0x0c058902, 0x90040a40 ); 
    udelay( 1 );
    writel( 0x04058902, 0x90040a40 ); 

    reg_val = readl(0x90040a48);
    reg_val = ( reg_val & (~(0xFFFC000)) ) | 0xC0000000;
    writel( reg_val   ,  0x90040a48 );
    
    reg_val = readl(0x90040a58);
    reg_val = ( reg_val & (~(0xFFFC000)) ) | 0xC0000000;
    writel( reg_val   ,  0x90040a58 );

    writel( 0x04058906, 0x90040a40 ); 
    udelay( 80 );

    /* MR8  1Gb|2Gb   --- start */
    writel( 0x4       , 0x900408e8 );
    
    reg_val = readl(0x9004001C);
    reg_val = reg_val & (~0x00010000);
    writel( reg_val   ,  0x9004001C );
    
    while( (readl(0x90040000)&0x1) != 0x0)
    {};
    writel( 0x1       , 0x90040044 );
    
    reg_val = readl(0x90040024);
    reg_val = (reg_val & (~0x0000FFF0))|0x000008E0;
    writel( reg_val   ,  0x90040024 );

    writel( 0x1       , 0x90040028 );

    while( (readl(0x90040048)&(0x1<<9)) != (0x1<<9))
    {};
    reg_val = readl(0x90040048);
    if(reg_val&(0x1<<8)){
        print_info(" ddr init dead 4, reg[48] expect bit[8]=0 \r\n");
        asm volatile ("b .");
    }
    else{
        reg_val = reg_val&0xFF;
        switch(reg_val){
            case 0x10:
                writel(0x121,0x9004002c);
                break;
            case 0x14:
            case 0x00:
                writel(0x131,0x9004002c);
                break;
            case 0x50:
                writel(0x122,0x9004002c);
                break;
            default:
                print_info(" ddr init dead 5, reg[48] bit[7:0] val not expected \r\n");
                asm volatile ("b .");
        }
    }
    
    writel( 0x0       , 0x90040044 );
    writel( 0x0       , 0x900408E8 );
    
    /* MR8  1Gb|2Gb   --- end */
    
    writel( 0x01e70210, 0x9004001c );  
    writel( 0x0       , 0x900408e4 ); 
    udelay( 20 );

    calc_ddrc_dfs();
    
    print_info(" mddrc init normal ok\r\n");
}

