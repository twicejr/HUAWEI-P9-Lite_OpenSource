#include <stdio.h>
#include <stdlib.h>
#include <sre_typedef.h>

int mem_init( UINT32  src_addr,    /*Memory Address*/
               int     num_byte,   /* Number of Data in Byte*/
               UINT32  init_data);

int mem_init_v9r1( UINT32  src_addr,    /*Memory Address*/
               int     num_byte,   /* Number of Data in Byte*/
               UINT32  init_data,
               UINT32  inc_type);

int mem_clr( UINT32  addr,         //Memory Address
              int     num_byte );    //Number of Data to clear in Byte

void mem_copy( UINT32 src_addr,    // Memory Source Address
               UINT32 des_addr,    // Memory Destination Address
               int    num_byte);   // Number of Data in Byte

int mem_comp( UINT32 addr1,     //Address 1
              UINT32 addr2,     //Address 2
              UINT32 num_byte );    //Number of data to Check in Byte

int mem_test(  UINT32 src_addr,    // Memory Address
               long int     num_byte,   // Number of Data in Byte
               int test_num );



void MemClrNoLog ( UINT32 addr,       //Memory Address
				   int total_byte,    //Number of Data to clear in Byte
				   UINT32 logaddr, 
				   int logbit );                                       
                 

void MemCompNoLog ( UINT32 addr1,      //Address 1
					UINT32 addr2,      //Address 2
					UINT32 length,     //Number of data to Check in Byte 
					UINT32 logaddr,   
					int logbit );

int mem_byte_cmp  (UINT32 src_addr,   //Address1
                   UINT32 dest_addr,  //Address2
                   UINT32 length);    //Number of data to Check in Byte

int mem_cmp       (UINT32 src_addr,   //Address1
                   UINT32 dest_addr,  //Address2
				   UINT32 length);    //Number of data to Check in Word

int edmac_mem_comp( UINT32 src_addr,     
			  UINT32 des_addr,     
			  UINT32 num_byte,
			  UINT32 trans_type);
