/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "mem_fun.h"
#include  "basicfunc.h"
#include  "baseaddr.h"
//#include "./dmav300/dmav300.h"
//#define _UNIT_DEBUG

/***********************************************************
  Function:       mem_init() // 函数名称
  Description:    memory 初时化函数// 函数功能、性能等的描述
  Calls:          set32 ; set8 ; read32 ; read8 ; printk // 被本函数调用的函数清单（建议描述）
  Called By:      // 调用本函数的函数清单（建议描述）
  Table Accessed: 无// 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  无// 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          src_addr：初始化memory 的地址，32bit 
                  num_byte：初始化memory 的大小，单位byte
                  init_data：赋给memory 的初始值
  Output:         无 // 对输出参数的说明。
  Return:         无// 函数返回值的说明
  Others:         // 其它说明
***********************************************************/

int sys_mem_init( UINT32 src_addr,    /*Memory Address*/
			   int     num_byte,   /* Number of Data in Byte*/
			   UINT32 init_data)   /* Data to initiate */
{
    int cnt1  ;
    int cnt2  ;
    //int cnt3  ;
    UINT32 write_data ;
    //UINT32 read_data;
    UINT8  init_data_byte ;
    //UINT8  read_data_byte ;
    UINT32 addr ;
    
    cnt1  = 0 ;
    cnt2  = 0 ;
    //cnt3  = 0 ;
    addr = src_addr ;
    write_data = init_data;
    
    /*向 以src_addr 为起始地址、以num_byte 为大小的一块memory 内写入初时值init_data */
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        /*如果memory 的大小是否32bits 的倍数，如果不是32bits 的倍数，则将最后空间使用8bits 写函数补全*/
        if(cnt1 >= 0x4)
        {
        	set32(addr, write_data++);//write_data);
            addr = addr + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            init_data_byte = write_data  ; 
            while ( cnt2 )
            {
                set8(addr, init_data_byte);
                write_data = write_data >> 8 ;
                init_data_byte = write_data ;
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
            }
        }	
    }
    //addr = src_addr ;
    //write_data = init_data;

/*如果需要判断memory 初始化是否正确，请define debug*/
//#ifdef _UNIT_DEBUG
    /*读初始化后的memory ，判断初时化是否成功*/
    /*for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data = read32( addr );
            addr = addr + 0x4 ;
            if ( init_data++ != read_data )//( init_data != read_data )
            {
            	cnt3 = cnt3 + 0x4 ;
            }
        }
        else
        {       
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte = read8 ( addr );
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;				
                init_data_byte = write_data ;
                write_data = write_data >> 8 ;
                if ( init_data_byte != read_data_byte )
                {
                    cnt3 = cnt3 + 0x1 ;
                }
            }
        }
    }       
            
    if ( 0 == cnt3 )
    {
    	printk("EDMAC: Memory Initiation OK!\n"); 
    }
    else
    {
    	printk("EDMAC: Memory Initiation FAILED!\n");
    	return 1;
    }	*/
    
//#endif
	return 0;
}

int sys_mem_init_v9r1( UINT32 src_addr,    /*Memory Address*/
			   int     num_byte,   /* Number of Data in Byte*/
			   UINT32 init_data,
			   UINT32 inc_type)   /* Data to initiate */
{
    int cnt1  ;
    int cnt2  ;
    //int cnt3  ;
    UINT32 write_data ;
    //UINT32 read_data;
    UINT8  init_data_byte ;
    //UINT8  read_data_byte ;
    UINT32 addr ;
    
    cnt1  = 0 ;
    cnt2  = 0 ;
    //cnt3  = 0 ;
    addr = src_addr ;
    write_data = init_data;
    
    /*向 以src_addr 为起始地址、以num_byte 为大小的一块memory 内写入初时值init_data */
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        /*如果memory 的大小是否32bits 的倍数，如果不是32bits 的倍数，则将最后空间使用8bits 写函数补全*/
        if(cnt1 >= 0x4)
        {
        	if (inc_type == 1)
        	{
        		set32(addr, write_data++);//write_data);
        	}
        	else if (inc_type == 0)
        	{
        		set32(addr, init_data);
        	}
        	else
        	{
        		set32(addr, 0);
        	}
            addr = addr + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            if (inc_type == 1)
            {
            	write_data = write_data;
            }
            else if (inc_type == 0)
            {
            	write_data = init_data;
            }
            else
            {
            	write_data = 0;
            }
            init_data_byte = write_data  ; 
            while ( cnt2 )
            {
                set8(addr, init_data_byte);
                write_data = write_data >> 8 ;
                init_data_byte = write_data ;
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
            }
        }	
    }
    //addr = src_addr ;
    //write_data = init_data;

/*如果需要判断memory 初始化是否正确，请define debug*/
//#ifdef _UNIT_DEBUG
    /*读初始化后的memory ，判断初时化是否成功*/
    /*for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data = read32( addr );
            addr = addr + 0x4 ;
            if ( init_data++ != read_data )//( init_data != read_data )
            {
            	cnt3 = cnt3 + 0x4 ;
            }
        }
        else
        {       
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte = read8 ( addr );
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;				
                init_data_byte = write_data ;
                write_data = write_data >> 8 ;
                if ( init_data_byte != read_data_byte )
                {
                    cnt3 = cnt3 + 0x1 ;
                }
            }
        }
    }       
            
    if ( 0 == cnt3 )
    {
    	printk("EDMAC: Memory Initiation OK!\n"); 
    }
    else
    {
    	printk("EDMAC: Memory Initiation FAILED!\n");
    	return 1;
    }	*/
    
//#endif
	return 0;
}

/***********************************************************
  Function:       mem_clr() // 函数名称
  Description:    对指定memory 清零函数// 函数功能、性能等的描述
  Calls:          set32 ; set8 ; read32 ; read8 ; printk // 被本函数调用的函数清单（建议描述）
  Called By:      // 调用本函数的函数清单（建议描述）
  Table Accessed: 无// 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  无// 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          src_addr：需要清零的内存段首地址，32bit 
				  num_byte：需要清零的内存段长度，单位byte
  Output:         无 // 对输出参数的说明。
  Return:         无// 函数返回值的说明
  Others:         // 其它说明
***********************************************************/


int sys_mem_clr( UINT32 src_addr,         /*Memory Address*/
			int     num_byte )    /*Number of Data to clear in Byte*/
{
    int cnt1  ;
    int cnt2  ;
#ifdef _UNIT_DEBUG	
    int cnt3 = 0  ;
#endif
    UINT32 addr ;
	
    cnt1 = 0 ;
    cnt2 = 0 ;
    addr = src_addr ; 
    

    
    /*将一块 以src_addr 为起始地址、以num_byte 为大小的memory 的值清零 */
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            set32(addr, 0x0);
            addr = addr + 0x4 ;
        }
        else
        {
            cnt2 = cnt1;
            while ( cnt2 )
            {
                set8(addr, 0x0);
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
            }
        }
        	
    }
    
    addr = src_addr ; 
	
/*如果需要判断memory 初始化是否正确，请define debug*/	
#ifdef _UNIT_DEBUG	

    /*读清零后的memory ，判断clear 操作是否成功*/
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
    {
        if(cnt1 >= 0x4)
        {
            read_data = read32( addr );
            addr = addr + 0x4 ;
            if ( 0x0 != read_data )
            {
            	cnt3 = cnt3 + 0x4 ;
            }
        }
        else
        {
            cnt2 = cnt1;
            while ( cnt2 )
            {
                read_data_byte = read8 ( addr );
                addr = addr + 0x1 ;
                cnt2 = cnt2 - 0x1 ;
                if ( 0x0 != read_data_byte )
                {
                    cnt3 = cnt3 + 0x1 ;
                }
            }
        }
    }
    
    if ( 0 == cnt3 )
    {
		//#ifdef _UNIT_DEBUG
		printk("Memory Clear OK!\n"); 
		return 0;
		//#endif
    }
    else
    {
        printk("Memory Clear FAILED!\n");
        return 1;
    }	
    
#endif	
    
   return 0;
}

/***********************************************************
  Function:       mem_copy() // 函数名称
  Description:    复制指定内存段到另一位置。
  Calls:          set32 ; set8 ; printk // 被本函数调用的函数清单（建议描述）
  Called By:      // 调用本函数的函数清单（建议描述）
  Table Accessed: 无// 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  无// 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          src_addr：源内存地址，32bit 
				  des_addr：目的内存地址，32bit 
				  num_byte：需要复制的内存的长度，单位byt
  Output:         无 // 对输出参数的说明。
  Return:         无// 函数返回值的说明
  Others:         // 其它说明
***********************************************************/
void sys_mem_copy( UINT32 src_addr,    /* Memory Source Address*/
			   UINT32 des_addr,    /* Memory Destination Address*/
			   int    num_byte)    /* Number of Data in Byte*/
{
int cnt1  ;
int cnt2  ;

UINT32  read_data ;
UINT8   read_data_byte ; 

cnt1 = 0 ;
cnt2 = 0 ;

/*拷贝操作，超过32bits使用32bits 的数据写函数，不足32bits的memory使用8bits 的数据写函数*/	
for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
{       
    if(cnt1 >= 0x4)
    {
        read_data = read32( src_addr );
        set32(des_addr , read_data );
        src_addr = src_addr + 0x4 ;
        des_addr = des_addr + 0x4 ;
    }
    else
    {
        cnt2 = cnt1;
        while ( cnt2 )
        {
            read_data_byte = read8 ( src_addr );
            set8(des_addr, read_data_byte );
            src_addr = src_addr + 0x1 ;
            des_addr = des_addr + 0x1 ;
            cnt2 = cnt2 - 0x1 ;
        }
    }
}
#ifdef _UNIT_DEBUG
    printk("Copy finish!\n"); 
#endif	

return;
}	
		 
/***********************************************************
  Function:       mem_comp() // 函数名称
  Description:    对比指定的两段内存段。
  Calls:          read32 ; read8 ; printk // 被本函数调用的函数清单（建议描述）
  Called By:      // 调用本函数的函数清单（建议描述）
  Table Accessed: 无// 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  无// 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          addr1：需要对比的地址段1首地址，32bit 
				  addr2：需要对比的地址段2首地址，32bit 
				  num_byte：对比内存段的长度，单位byt
  Output:         无 // 对输出参数的说明。
  Return:         cnt3：两块memory 上不同数据的个数
  Others:         可以通过宏定义debug 来确定是否打印两块memory 上不同数据的具体情况。
***********************************************************/
int sys_mem_comp( UINT32 addr1,     
			  UINT32 addr2,     
			  UINT32 num_byte )    
{
    int cnt1  ;
    int cnt2  ;
    int cnt3  ;
    UINT32 read_data1 ;
    UINT32 read_data2 ;
    UINT8 read_data_byte1 ; 
    UINT8 read_data_byte2 ; 
    
    cnt1 = 0 ;
    cnt2 = 0 ;
    cnt3 = 0 ;
    	
    for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
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
                printk("error %d!\n" , cnt3 ); 
                printk("addr1=%x,data1=%x\n",addr1,read_data1);
                printk("addr2=%x,data2=%x\n",addr2,read_data2);
//#endif                      
            }
			/*else 
			{
				printk("Compare right!!\n");
			}*/
			
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
                    printk("error %d!\n" , cnt3 );
                    printk("addr1=%x,data1=%x\n",addr1, read_data_byte1);
                    printk("addr2=%x,data2=%x\n",addr2, read_data_byte2);
//#endif
                 }
				/*else 
				{
					printk("Compare right!!\n");
				}*/
                 addr1 = addr1 + 0x1 ;
                 addr2 = addr2 + 0x1 ;			
                 cnt2 = cnt2 - 0x1 ;
            }
        }
			
    }
#ifdef _UNIT_DEBUG
    if ( 0 == cnt3 )
    {
        printk("Memory Compare OK!\n"); 
    }
    else
    {
        printk("Memory Compare FAILED!\n");
    }
#endif	
    return cnt3 ;
}

#if 0
/***********************************************************
  Function:       mem_comp() // 函数名称
  Description:    对比指定的两段内存段。
  Calls:          read32 ; read8 ; printk // 被本函数调用的函数清单（建议描述）
  Called By:      // 调用本函数的函数清单（建议描述）
  Table Accessed: 无// 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  无// 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          addr1：需要对比的地址段1首地址，32bit 
				  addr2：需要对比的地址段2首地址，32bit 
				  num_byte：对比内存段的长度，单位byt
  Output:         无 // 对输出参数的说明。
  Return:         cnt3：两块memory 上不同数据的个数
  Others:         可以通过宏定义debug 来确定是否打印两块memory 上不同数据的具体情况。
***********************************************************/
int edmac_mem_comp( UINT32 src_addr,     
			  UINT32 des_addr,     
			  UINT32 num_byte,
			  UINT32 trans_type)    
{
	int cnt1  ;
	int cnt2  ;
	int cnt3  ;
	UINT32 read_data1 ;
	UINT32 read_data2 ;
	UINT8 read_data_byte1 ; 
	UINT8 read_data_byte2 ; 
	UINT32 ch_state;
	UINT32 addr1;
	UINT32 addr2;
	
	addr1 = src_addr;
	addr2 = des_addr;
	
	cnt1 = 0 ;
	cnt2 = 0 ;
	cnt3 = 0 ;
	
	do
	{
		ch_state = read32(EDMAC_BASEADDR+CH_STAT);
	} 
	while (ch_state != 0);
	
	//printk("EDMAC: Memory Transmit complete\n");
    	
	for (cnt1 = num_byte; cnt1 >0; cnt1 = cnt1 - 0x4)
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
				printk("EDMAC error %d!\n" , cnt3 ); 
				printk("addr1=%x,data1=%x\n",addr1,read_data1);
				printk("addr2=%x,data2=%x\n",addr2,read_data2);
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
					printk("error %d!\n" , cnt3 );
					printk("addr1=%x,data1=%x\n",addr1, read_data_byte1);
					printk("addr2=%x,data2=%x\n",addr2, read_data_byte2);
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
		printk("Memory Compare OK!\n"); 
	}
	else
	{
		printk("Memory Compare FAILED!\n");
	}
#endif	
	if (cnt3 == 0)
	{
#ifdef V9R1_DEBUG
		if (trans_type == 0)
		{
			printk ("---- EDMAC OK ----\n");
		}
		else if(trans_type == 1)
		{
			printk ("---- BBP OK ----\n");
		}
#endif
		return 0;
	}
	else
	{
		if (trans_type == 0)
		{
			printk ("EDMAC ERROR\n");
		}
		else if(trans_type == 1)
		{
			printk ("BBP TRANSFER ERROR\n");
		}
		return 1;
	}
}
#endif

/***********************************************************
  Function:       mem_test() // 函数名称
  Description:    使用随机数据检查内存读写是否有错误。
  Calls:          set32; read32 ; srand; rand; printk // 被本函数调用的函数清单（建议描述）
  Called By:      // 调用本函数的函数清单（建议描述）
  Table Accessed: 无// 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  无// 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          src_addr：待查memory 的地址，32bit 
				  num_byte：待查memory 的长度， 单位byte
				  test_num：检查的次数
  Output:         无 // 对输出参数的说明。
  Return:         cnt2：检查memory 上错误的个数
  Others:         可以通过宏定义debug 来确定是否打印两块memory 上不同数据的具体情况。
***********************************************************/

int sys_mem_test(  UINT32 src_addr,    /* Memory Address*/
			   long int    num_byte,    /* Number of Data in Byte*/
			   int    test_num )   /*检查的次数*/
{
    long int cnt1 ;
    int cnt2 ;
    int cnt3 ;
    UINT32 data1 ;
    UINT32 data2 ;
    UINT32 read_data1 ; 
    UINT32 read_data2 ; 
    UINT32 addr1 ; 
    UINT32 addr2 ; 
    
    cnt1 = 0 ;
    cnt2 = 0 ;
    cnt3 = 0 ;

  //  srand((unsigned)time());
    
    for(cnt3 = test_num ; cnt3 >0 ; cnt3 = cnt3 - 0x1 )
    {
        addr1 = src_addr ;
        addr2 = src_addr + 0x4 ;
        for (cnt1 = num_byte ; cnt1 >0 ; cnt1 = cnt1 - 0x8)
        {
        /*    data1 = rand() ;	      
            data1 = data1 <<16;
            data1_low = rand() ;
            data1 = data1 | data1_low ;*/
			data1 = 0x5a5a5a5a;
            set32(addr1, data1); 
	
            if (cnt1 >4) 
                        {
     /*           data2 = rand() ;
                data2 = data2 <<16;
                data2_low = rand() ;
                data2 = data2 | data2_low ;*/
	          data2 = 0xa5a5a5a5;
                set32( addr2, data2);
            }
            
            read_data1 = read32( addr1);
            if ( read_data1 != data1)
            {
                cnt2 = cnt2 + 0x1 ;
            }
            addr1 = addr1 + 0x8 ;
            							
            if (cnt1 >4) 
            {
                read_data2 = read32( addr2);
                if ( read_data2 != data2)
                    {
                        cnt2 = cnt2 + 0x1 ;			
                    }
                    addr2 = addr2 + 0x8 ;
            }	
            	
        }
#ifdef _UNIT_DEBUG
            printk("test %x!\n",cnt3 ); 
#endif
        }
    return cnt2 ; 
}

/**********************************************************
	This function is used to Clear Memory 
**********************************************************/

void MemClrNoLog ( UINT32 addr,       //Memory Address
				   int total_byte,    //Number of Data to clear in Byte
				   UINT32 logaddr, 
				   int logbit                                        
				 )
{
	UINT32 result;
	int i,j=0;	

	for(i=0;i<total_byte;i=i+4)
	{
		set32(addr+(UINT32)i,0x0);
		result = read32(addr+(UINT32)i);
		if(result == 0x0)
		{ 
			j++; 
		}
		else
		{ 
			j=j; 
		}
	}
	if(j == total_byte/4)
	{
		setbits(logaddr, logbit, logbit, 1);
	}
	else
	{
		setbits(logaddr, logbit, logbit, 0);
	}

	return;
}

/**********************************************************
	This function is used to perform Result Checking 
	between two Memories without log message
**********************************************************/

void MemCompNoLog ( UINT32 addr1, //Address 1
					UINT32 addr2, //Address 2
					UINT32 length, //Number of data to Check in Byte 
					UINT32 logaddr, 
					int logbit
				  )
{
	unsigned int i,j;
	UINT32 rdata1,rdata2;
	j=0;

	  //  RegBitWrite(logaddr, logbit, logbit, 0);
	
	for(i=0;i<length;i=i+4)
	{
		rdata1=read32(addr1+i);
		rdata2=read32(addr2+i);
		if(rdata1==rdata2)
		{
			j++;
		}
		else
		{
			j=j;
			break;
		}
	}
	if(j==length/4)
		setbits(logaddr, logbit, logbit, 1);
	else 
		setbits(logaddr, logbit, logbit, 0);
	
	j=0;
	
	return;
}



int sys_mem_byte_cmp(UINT32 src_addr,  UINT32 dest_addr,  UINT32 length)
{
	
	unsigned int check_flag=0;
	UINT32 cnt1;	
	UINT8 rdata1,rdata2;
		
	for( cnt1 = 0; cnt1 < length; cnt1++ )
	{
			rdata1 = read8(src_addr);
			rdata2 = read8(dest_addr);
			if( rdata1 != rdata2 )
			{
				printk("Error: src_addr = %x, des_addr = %x, src_data = %x, dest_data = %x\n", src_addr, dest_addr, rdata1, rdata2 );
				
				check_flag++;
			}
			
			src_addr++ ;
			dest_addr++ ;
	}
	
	if(check_flag == 0)
	{
		#ifdef _UNIT_DEBUG
	    printk("Compare OK!\n");
	    #endif
	    
	    return 0;
	}
	
	else
	{
		#ifdef _UNIT_DEBUG
		printk("Compare Fail!\n");
		#endif
		
		return 1;
	}
	
}

int sys_mem_cmp(UINT32 src_addr,  UINT32 dest_addr,  UINT32 length)
{
	UINT32 i;
		
	UINT32 rdata1,rdata2;
	
	UINT32 data_len;
	
	if ((length%32)==0)
	{
		data_len  =  length/32;
	}
	else 
	{
		data_len  =  (length/32) + 1;
	}	
	for( i = 0; i < data_len; i = i+1 )
	{
			rdata1 = read32(src_addr);
			rdata2 = read32(dest_addr);
			if( rdata1 != rdata2 )
			{
				//set32(SMIM_BASEADDR,0x51525354);
				
				printk("Compare Error!!!!\n");
				printk("Compare Error: addr = %x, src_data = %x, corr_data = %x\n", src_addr, rdata1, rdata2 );
	 		    
				return 1;
			}			
			src_addr = src_addr + 4 ;
			
			dest_addr = dest_addr + 4 ;
	}

	return 0;	
}
#if 0
void ddr_write (UINT32 data_len)
{
	UINT32 i,j;
		
	UINT32 rdata1,rdata2;
	
	//UINT32 data_len;
	
	j = 0;
	
	//data_len = 1000000;
	
	for( j = 0; j < data_len; j = j+1 )
	{
		for( i = 0; i < 1000000; i = i+1 )
	    {
		    set32(MDDR_BASEADDR + 0x1300000 + i*4 ,i);
	    }
		printk("Write Complete!!\n");
    }
}
	
void ddr_read (UINT32 data_len)
{
	UINT32 i,j;
	
	UINT32 rdata1,rdata2;
	
	//UINT32 data_len;
	
	j = 0;
	
	//data_len = 1000000;
	
	for( j = 0; j < data_len; j = j+1 )
	{
		for( i = 0; i < 1000000; i = i+1 )
		{
			read32(MDDR_BASEADDR + 0x1300000 + i*4);
		}
		printk("Read Complete!!\n");
	}
}
#endif

