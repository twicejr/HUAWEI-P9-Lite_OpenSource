#include <stdio.h>
#include "osl_malloc.h"
#include "baseaddr.h"
#include "BasicFunc.h"
#include "cicom.h"

void cicom_all()
{
#if 0
	printf("\n\n\n============   cicom_104   ============\n");
	cicom_104();
	
	printf("\n\n\n============   cicom_108   ============\n");
	cicom_108();

	printf("\n\n\n============   cicom_109   ============\n");
	cicom_109();

	printf("\n\n\n============   cicom_202   ============\n");
        cicom_202();

	printf("\n\n\n============   cicom_208   ============\n");
        cicom_208();

	printf("\n\n\n============   cicom_303   ============\n");
	cicom_303();

	printf("\n\n\n============   cicom_304   ============\n");
	cicom_304();

	printf("\n\n\n============   cicom_403   ============\n");
	cicom_403();

	printf("\n\n\n============   cicom_404   ============\n");
	cicom_404();

	printf("\n\n\n============   cicom_501   ============\n");
	cicom_501();

	printf("\n\n\n============   cicom_502   ============\n");
	cicom_502();
      
	printf("\n\n\n============   cicom_503   ============\n");
	cicom_503();
	
	printf("\n\n\n============   cicom_504   ============\n");
	cicom_504();
#endif
}



UINT32 ck_addr        = 0;//SRAM_BASEADDR+0x00010000;
UINT32 lli_prm        = 0;//SRAM_BASEADDR+0x00010100;
int cicom_v500_trans_config(UINT32 src_addr, UINT32 des_addr, UINT32 num_8)
{	
    UINT32 i;
    
    UINT32 pdu_len;
    
    UINT32 alg_sel= 0x0 ;//gea3
    UINT32 cb     = 0x00;//cipher_cb 
    UINT32 ck1_1  = 0x2bb97c23;
    UINT32 ck1_2  = 0x76d0dbb8;
    UINT32 ck1_3  = 0x00000000;
    UINT32 ck1_4  = 0x00000000;
    UINT32 cc1    = 0x1f927f6c;
    
if(ck_addr == 0)
{
	ck_addr        = (UINT32)osl_cachedma_malloc(1024);
	if(!ck_addr){
		return -1;
	}
}
if(lli_prm == 0) 
{
	lli_prm        = (UINT32)osl_cachedma_malloc(1024);
	if(!lli_prm){
		return -1;
	}
}
    pdu_len = num_8*8;
    
    setbit(SYSCTRL_SCMISCCTRL, Cicom_sel ,0x1);//select W(0) / G(1)
    
    //cacheDisable(1);/*需要确认是否要实现，zuofenghua*/??
    
    // cfg the lli_param
    set32( (lli_prm + 0x00000000), ck_addr                      );//CK_ADDR              
    set32( (lli_prm + 0x00000004), cc1                          );//CC                   
    set32( (lli_prm + 0x00000008), pdu_len                      );//SRC_PDU_TOTAL_LEN    
    set32( (lli_prm + 0x0000000c), 0x00000002                   );//CUSTOM_CFG
    set32( (lli_prm + 0x00000010), src_addr                     );//LLI_SRC_PDU_SEG_ADDR 
    set32( (lli_prm + 0x00000014), des_addr                     );//LLI_DST_TTF_SEG_ADDR
    set32( (lli_prm + 0x00000018), 0x00000000                   );//LLI_DST_MBX_SEG_ADDR
    set32( (lli_prm + 0x0000001c), 0x00000000                   );//LLI_PRM_ADDR      
 
    // cfg the key_data
    set32( (ck_addr + 0x00000000), ck1_1);
    set32( (ck_addr + 0x00000004), ck1_2);
    set32( (ck_addr + 0x00000008), ck1_3);
    set32( (ck_addr + 0x0000000c), ck1_4);
    
    //set registers
    set32(asicCICOMPRIOR_SELECT     , 0x00000000           );
    set32(asicCICOMLLI_PARAM_ADDR_DL, lli_prm              );
    setbits(asicCICOMGLOBAL_CFG_DL  , 1, 0, alg_sel        );  
    setbits(asicCICOMGLOBAL_CFG_DL  , 11, 8, 0x0           );  
    setbits(asicCICOMGLOBAL_CFG_DL  , 20, 16, cb           );  
    set32(asicCICOMINT_EN_DL        , 0x00000000           );//int enable
    //set32(asicCICOMEN_DL            , 0x00000001           );//start cicom
    
    // initial memory
	for( i = 0; i < num_8/4; i++ )
	{
		set32( src_addr+0x4*i, 0x5a5a5a5a+i );
		set32( des_addr+0x4*i, 0x0 );
	}
	
	return 0;
}

void cicom_v500_trans_en()
{
	set32(asicCICOMEN_DL, 0x00000001           );//start cicom
}

int cicom_v500_trans_check(UINT32 src_addr, UINT32 des_addr, UINT32 num_8)
{
	int cnt1  ;
	int cnt2  ;
	int cnt3  ;
	UINT32 read_data1 ;
	UINT32 read_data2 ;
	UINT8 read_data_byte1 ; 
	UINT8 read_data_byte2 ; 
	UINT32 cicom_state;
	UINT32 addr1;
	UINT32 addr2;
	
	addr1 = src_addr;
	addr2 = des_addr;
	
	cnt1 = 0 ;
	cnt2 = 0 ;
	cnt3 = 0 ;
	
    // read status registers
	cicom_state = 0x1;
    while(cicom_state == 0x01)
    {
    	//cicom_state = read32(asicCICOMEN_UL);
    	cicom_state = read32(asicCICOMEN_DL);
    	cicom_state = cicom_state & 0x01;
    }
    
	for (cnt1 = num_8; cnt1 >0; cnt1 = cnt1 - 0x4)
	{
		if(cnt1 >= 0x4)
		{
			read_data1 = read32( addr1 );
			read_data2 = read32( addr2 );
			if ( read_data1 != read_data2 )
			{
				cnt3 = cnt3 + 0x1 ;
/*判断是否打印两块memory 上不同数据的具体情况*/					
//#ifdef debug
				printf("CICOM ERROR %d!\n" , cnt3 ); 
				printf("addr1=%x,data1=%x\n",addr1,read_data1);
				printf("addr2=%x,data2=%x\n",addr2,read_data2);
//#endif                      
			}
			addr1 = addr1 + 0x4 ;
			addr2 = addr2 + 0x4 ;
		}
		else
		{
			cnt2 = cnt1;
			while ( cnt2 )
			{
				read_data_byte1 = read8 ( addr1 );
				read_data_byte2 = read8 ( addr2 );
				if ( read_data_byte1 != read_data_byte2 )
				{
					cnt3 = cnt3 + 0x1 ;			  
/*判断是否打印两块memory 上不同数据的具体情况*/      	
//#ifdef _UNIT_DEBUG
					printf("CICOM ERROR %d!\n" , cnt3 );
					printf("addr1=%x,data1=%x\n",addr1, read_data_byte1);
					printf("addr2=%x,data2=%x\n",addr2, read_data_byte2);
//#endif
				 }
				 addr1 = addr1 + 0x1 ;
				 addr2 = addr2 + 0x1 ;			
				 cnt2 = cnt2 - 0x1 ;
			}
		}
			
	}
#ifdef _UNIT_DEBUG
	if ( 0 == cnt3 )
	{
		printf("CICOM Memory Compare OK!\n"); 
	}
	else
	{
		printf("CICOM Memory Compare FAILED!\n");
	}
#endif	
	if (cnt3 == 0)
	{
#ifdef P530_DEBUG
		printf ("---- CICOM OK ----\n");
#endif
		return 0;
	}
	else
	{
		printf ("CICOM ERROR\n");
		return 1;
	}
}











