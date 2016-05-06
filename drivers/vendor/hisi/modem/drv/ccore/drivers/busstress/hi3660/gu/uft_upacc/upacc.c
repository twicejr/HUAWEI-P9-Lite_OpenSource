#include <stdio.h>
#include "sre_typedef.h"
#include "baseaddr.h"
#include "BasicFunc.h"
#include "common.h"
#include "mem_fun.h"
#include "upacc.h"

void upacc_dly(UINT32 num)
{
    volatile UINT32 i,j,k;
    for(i=0;i<num;i++)
    {
        for(j=0;j<0x1000;j++)
        {
            k=j;
			j=k;
        }
    }   
}

//void mace_loch_param(UINT32 loch1,UINT32 loch2,UINT32 loch3,UINT32 loch4,UINT32 loch5,UINT32 loch6,UINT32 loch7,UINT32 loch8)
//{
//  set32( UPACC_BASEADDR + LOCH1_PARAM, loch1 );
//  set32( UPACC_BASEADDR + LOCH2_PARAM, loch2 );
//  set32( UPACC_BASEADDR + LOCH3_PARAM, loch3 );
//  set32( UPACC_BASEADDR + LOCH4_PARAM, loch4 );
//  set32( UPACC_BASEADDR + LOCH5_PARAM, loch5 );
//  set32( UPACC_BASEADDR + LOCH6_PARAM, loch6 );
//  set32( UPACC_BASEADDR + LOCH7_PARAM, loch7 );
//  set32( UPACC_BASEADDR + LOCH8_PARAM, loch8 );
//}


int upacc_rd(UINT32 pAddr,UINT32 comp_Data)
{
    
    UINT32 r_Data;
    
    r_Data = read32(pAddr);
    if(r_Data == comp_Data)
    {
        ///printf("read successful\n");
        return 1;
    }
    else
    {
        printf("upacc read data %x = %x, expect_data= %x,Read ERROR!\n",pAddr,r_Data,comp_Data);
        return 0;
    }
}

void rw_reg_test(UINT32 init_value, UINT32 reg_mask, UINT32 pAddr)
{
    printf("Test register %x! \n",UPACC_BASEADDR+pAddr);
    upacc_rd(UPACC_BASEADDR+pAddr,init_value         ); 
    set32   (UPACC_BASEADDR+pAddr,0x55555555         );
    upacc_rd(UPACC_BASEADDR+pAddr,0x55555555&reg_mask); 
    set32   (UPACC_BASEADDR+pAddr,0xaaaaaaaa         );
    upacc_rd(UPACC_BASEADDR+pAddr,0xaaaaaaaa&reg_mask);
    set32   (UPACC_BASEADDR+pAddr,0xffffffff         );
    upacc_rd(UPACC_BASEADDR+pAddr,0xffffffff&reg_mask);
    set32   (UPACC_BASEADDR+pAddr,init_value         );
    upacc_rd(UPACC_BASEADDR+pAddr,init_value         );     
}

void upacc_reg_test()
{
    //test register for mac-e
    upacc_rd(UPACC_BASEADDR+INT_RAW          ,0x00000000);
    upacc_rd(UPACC_BASEADDR+INT_MASK         ,0x00000000);
    upacc_rd(UPACC_BASEADDR+INT_CLR          ,0x00000000);
    upacc_rd(UPACC_BASEADDR+BUS_ERROR_ADDR   ,0x00000000);
    
    rw_reg_test(0x00000000, 0x00000003, MAC_ENCAP_START    );
    rw_reg_test(0x00000000, 0x0000000f, LOCH_NUM           );
    rw_reg_test(0x00000000, 0x00000001, DDI0_EN            );
    rw_reg_test(0x00000000, 0x00000001, SI_EN              );
    rw_reg_test(0x00000000, 0x0003ffff, SI_DATA            );
    rw_reg_test(0x00000000, 0x0000ffff, PADDING_LENGTH     );
    rw_reg_test(0x00000000, 0xffffffff, ENCAP_TRANS_ADDR   );
    rw_reg_test(0x00000000, 0x0000ffff, TRANS_NUM          );
    rw_reg_test(0x00000000, 0xffffffff, BBP_DEST_ADDR      );
    rw_reg_test(0x00000000, 0x00ffffff, INT_EN             );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH1_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH2_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH3_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH4_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH5_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH6_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH7_PARAM        );
    rw_reg_test(0x00000000, 0x0003ffff, LOCH8_PARAM        );
    rw_reg_test(0x00000000, 0xffffffff, LOCH1_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH2_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH3_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH4_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH5_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH6_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH7_START_ADDR   );
    rw_reg_test(0x00000000, 0xffffffff, LOCH8_START_ADDR   );   
    rw_reg_test(0x00000000, 0xffffffff, LOCH1_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH2_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH3_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH4_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH5_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH6_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH7_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH8_END_ADDR     );
    rw_reg_test(0x00000000, 0xffffffff, LOCH1_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH2_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH3_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH4_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH5_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH6_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH7_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH8_READ_ADDR    );
    rw_reg_test(0x00000000, 0xffffffff, LOCH1_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH2_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH3_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH4_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH5_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH6_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH7_NUM_CFG      );
    rw_reg_test(0x00000000, 0xffffffff, LOCH8_NUM_CFG      );
    rw_reg_test(0x00000000, 0x00000001, UPACC_EN           );
    
    rw_reg_test(0x00000000, 0xffffffff, LOCH1_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH2_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH3_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH4_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH5_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH6_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH7_PDUARY_ADDR  );
    rw_reg_test(0x00000000, 0xffffffff, LOCH8_PDUARY_ADDR  );
    
    //test register for mac-i
    upacc_rd(UPACC_BASEADDR+INT_RAW_I1       ,0x00000000);
    upacc_rd(UPACC_BASEADDR+INT_MASK_I1      ,0x00000000);  
    upacc_rd(UPACC_BASEADDR+INT_CLR_I1       ,0x00000000);
    upacc_rd(UPACC_BASEADDR+BUS_ERROR_ADDR_I1,0x00000000);
    upacc_rd(UPACC_BASEADDR+INT_RAW_I2       ,0x00000000);
    upacc_rd(UPACC_BASEADDR+INT_MASK_I2      ,0x00000000);  
    upacc_rd(UPACC_BASEADDR+INT_CLR_I2       ,0x00000000);
    upacc_rd(UPACC_BASEADDR+BUS_ERROR_ADDR_I2,0x00000000);
        
    rw_reg_test(0x00000000, 0x00000003, MAC_ENCAP_START_I1);
    rw_reg_test(0x00000000, 0x0000000f, LOCH_NUM_I1       );
    rw_reg_test(0x00000000, 0x00000001, HEAD0_EN_I1       );
    rw_reg_test(0x00000000, 0x0000ffff, E_RNTI_I1         );
    rw_reg_test(0x00000000, 0x00000001, SI_EN_I1          );
    rw_reg_test(0x00000000, 0x001f1fff, SI_DATA_I1        );
    rw_reg_test(0x00000000, 0x0000ffff, PADDING_LEN_I1    );
    rw_reg_test(0x00000000, 0x00000001, TSN_LEN_I1        );
    rw_reg_test(0x00000000, 0xffffffff, PARAM_ADDR_I1     );
    rw_reg_test(0x00000000, 0xffffffff, HARQ_BUF_ADDR_I1  );
    rw_reg_test(0x00000000, 0xffffffff, BBP_DEST_ADDR_I1  );
    rw_reg_test(0x00000000, 0x0000ffff, TRANS_NUM_I1      );
    rw_reg_test(0x00000000, 0x007fffff, INT_EN_I1         );
    rw_reg_test(0x00000000, 0x00000001, UPACC_EN_I1       );
    
    rw_reg_test(0x00000000, 0x00000003, MAC_ENCAP_START_I2);
    rw_reg_test(0x00000000, 0x0000000f, LOCH_NUM_I2       );
    rw_reg_test(0x00000000, 0x00000001, HEAD0_EN_I2       );
    rw_reg_test(0x00000000, 0x0000ffff, E_RNTI_I2         );
    rw_reg_test(0x00000000, 0x00000001, SI_EN_I2          );
    rw_reg_test(0x00000000, 0x001f1fff, SI_DATA_I2        );
    rw_reg_test(0x00000000, 0x0000ffff, PADDING_LEN_I2    );
    rw_reg_test(0x00000000, 0x00000001, TSN_LEN_I2        );
    rw_reg_test(0x00000000, 0xffffffff, PARAM_ADDR_I2     );
    rw_reg_test(0x00000000, 0xffffffff, HARQ_BUF_ADDR_I2  );
    rw_reg_test(0x00000000, 0xffffffff, BBP_DEST_ADDR_I2  );
    rw_reg_test(0x00000000, 0x0000ffff, TRANS_NUM_I2      );
    rw_reg_test(0x00000000, 0x007fffff, INT_EN_I2         );
    rw_reg_test(0x00000000, 0x00000001, UPACC_EN_I2       );
        
}


void upacc_intr_clr()
{   
    set32   (UPACC_BASEADDR+INT_CLR           ,0x00ffffff);
    set32   (UPACC_BASEADDR+INT_CLR_I1        ,0x007fffff);
    set32   (UPACC_BASEADDR+INT_CLR_I2        ,0x007fffff);
}

int upacc_trans_config(UINT32 src_addr, UINT32 des_addr, UINT32 num_8)
{
    UINT32 i;
    UINT32 reg_read;
        
    set32( UPACC_BASEADDR, 0x0 );   
    set32( UPACC_BASEADDR+INT_CLR, 0xffffff );
        
    set32( UPACC_BASEADDR+ENCAP_TRANS_ADDR, src_addr );
    
    reg_read = read32( UPACC_BASEADDR+ENCAP_TRANS_ADDR );
    
    if( src_addr != reg_read )
    {
        #ifdef _UNIT_DEBUG
        printf(" Write or Read REG ENCAP_TRANS_ADDR(0x18) error!\n ");
        #endif
    }
    
    set32( UPACC_BASEADDR+TRANS_NUM, num_8 );
    
    reg_read = read32( UPACC_BASEADDR+TRANS_NUM );
    
    if( num_8 != reg_read )
    {
        #ifdef _UNIT_DEBUG
        printf(" Write or Read REG TRANS_NUM(0x1c) error!\n ");
        #endif
    }
    
    set32( UPACC_BASEADDR+BBP_DEST_ADDR, des_addr );
    
    reg_read = read32( UPACC_BASEADDR+BBP_DEST_ADDR );
    
    if( des_addr != reg_read )
    {
        #ifdef _UNIT_DEBUG
        printf(" Write or Read REG BBP_DEST_ADDR(0x20) error!\n ");
        #endif
    }
    
    set32( UPACC_BASEADDR+UPACC_EN, 0x1 );
    
    reg_read = read32( UPACC_BASEADDR+UPACC_EN );
    
    if( 0x1 != reg_read )
    {
        #ifdef _UNIT_DEBUG
        printf(" Write or Read REG UPACC_EN(0xd8) error!\n ");
        #endif
    }
    
/*  for( i = 0; i < num_8/4; i++ )
    {
        set32( src_addr+0x4*i, 0x5a5a5a5a+i );
        set32( des_addr+0x4*i, 0x0 );
    }*/
    for( i = 0; i < num_8/8; i++ )
    {
        set32( src_addr+0x8*i, 0x5a5a5a50+(i<<1) );
        set32( src_addr+0x8*i+0x4, 0xa5a5a5a0+(i<<1)+1 );
        
        set32( des_addr+0x8*i, 0x0 );
        set32( des_addr+0x8*i+0x4, 0x0 );
    }
    
    return 0;
}

//int upacc_trans_en(UINT32 upacc_baseaddr)
int upacc_trans_en()
{
    //set32( upacc_baseaddr, 0x2 );
    set32( UPACC_BASEADDR, 0x2 );
    return 0;   
}

int upacc_trans_check(UINT32 src_addr, UINT32 des_addr, UINT32 num_8)
{
    UINT32 i,j;
    UINT32 src_data;
    UINT32 des_data;
    
    //wait for trans end
    src_data = read32( UPACC_BASEADDR + 0x00 );
    src_data = src_data&0x3;
    while(src_data!=0x0)
    {
        src_data = read32( UPACC_BASEADDR );
        src_data = src_data&0x3;
    }
        
    for(i = 0,j=0; i < num_8/4; i++ )
    {
        src_data = read32( src_addr+0x4*i );
        des_data = read32( des_addr+0x4*i );
        
        if(  src_data != des_data )
        {
            j ++;
    
            printf("UPACC Error: ");
            printf("sa = %x da = %x,sd = %x dd = %x\n", src_addr+0x4*i, des_addr+0x4*i, src_data, des_data);
            
            //return 1;
        }
    }
    if ( j == 0 )
    {
        #ifdef _UNIT_DEBUG
        printf("UPACC OK: sa = %x, da = %x\n",src_addr,des_addr);
        #endif
        
        return 0;
    }
    else
    {   
        printf ("UPACC ERROR\n");
        return 1;
    }
    
}







