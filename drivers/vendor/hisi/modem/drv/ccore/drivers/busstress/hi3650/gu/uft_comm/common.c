/************************************************************
  Copyright (C), 1988-2009, Huawei Tech. Co., Ltd.
  FileName: Common.c
  Author: WanXing	ID: 128668        Date: 2009-11-16
  Description: This file inludes all base functions of 
               Write/Read opration      
  Version:     1.0
  Function List:  
    1. 
  History:         
      <author>     <ID>     <time>   <version >   <desc>
      WanXing     128668    09/11/16     1.0     initial releas  
***********************************************************/

#include <string.h>
#include <osl_thread.h>
#include "gu_busstress_type.h"
#include "baseaddr.h"
#include "common.h"
#include "BasicFunc.h"
#include "mem_fun.h"


/*************************************************
  Function:       DelayRandom    
  Description:    Delay any random time from 1 to 1000 cycles
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          
  Output:         
  Return:         void
  Others:         
*************************************************/

void DelayRandom()
{
    int iRdm_Num;
    int i = 0;
     
    iRdm_Num = (int)(rand() %1000);

#ifdef _UNIT_DEBUG
    printf("iRdm_Num = %d\n", iRdm_Num);
#endif

    while(i<iRdm_Num)
    {
        i++;
    }

    return;
}

/*************************************************
  Function:       DelayRandomSet    
  Description:    Delay any random time from DelayMin to DelayMax cycles
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          DelayMin,DelayMax
  Output:         
  Return:         void
  Others:         
*************************************************/

void DelayRandomSet(UINT32 DelayMin,UINT32 DelayMax)
{
    UINT32 iRdm_Num;
    unsigned int i = 0;
     
    iRdm_Num = (int)(rand() /(DelayMax-DelayMin+1))+DelayMin-1;

#ifdef _UNIT_DEBUG
    printf("iRdm_Num = %d\n", iRdm_Num);
#endif

    while(i<iRdm_Num)
    {
        i++;
    }

    return;
}

#if 0
int setM( UINT32 pAddr, UINT32 FileLen )
{
	UINT32 i;
	UINT32 value;
	
	ShellIORedirect(1);
	taskDelay(1);
	for(i=FileLen;i>0;i--)
	{
		scanf("%x",&value);
		*((volatile UINT32 *)pAddr) = value;
		pAddr+=4;
	}
	taskDelay(1);
	//ShellIORedirect(0);
	return 0;
}

int readM()
{
	UINT32 i;
	
	ShellIORedirect(1);
	taskDelay(1);
	for(i=100;i>0;i--)
	{
		printf("Hello world %x\n",i);
		taskDelay(10);
	}
	taskDelay(1);
	//ShellIORedirect(0);
	return 0;
}
#endif
/*int soc_init( )
{
    //cd("/tffs0a");
	//taskDelay(1);
	//ld(1,0,"install.iso");
	//taskDelay(1);
	//set32(0x21001028,0x14b41);
	//set32(0x6075000c,0xff);
	
	taskDelay(1);
	
	return 0;
}*/


int edmac_uart1()
{
	UINT8 i;
	UINT8 j;
	
    //config uart1	
	//set32(0x9002100c,0x9b);
	//set32(0x90021004,0x0);
	//set32(0x90021000,0xFA);
	//set32(0x9002100c,0x1b);
	//set32(0x90021004,0x3);
	
	set32(0x90021008,0x41);
	
	//config EDMAC
	for(i=0;i<0x1A;i++)
	{
		set8(0x32000000+i, 'A'+i);
	}
	for(i=0;i<0x1A;i++)
	{
		set8(0x32000000+0x1A+i, 'A'+i);
	}
	
	//set32(0x90181668,0x2000);	
	set32(0x90181800,0x0000);
	set32(0x90181804,0x0000);
	set32(0x90181808,0x0000);
	set32(0x9018180C,0x0000);
	set32(0x90181810,52);
	set32(0x90181814,0x32000000);
	set32(0x90181818,0x90021000);
	
	//CARM Write UART0
	for(i=0;i<0x1A;i++)
	{
		set8(0x90021000, 'a'+i);
	}
	for(i=0;i<10;i++)
	{
		set8(0x90021000, '0'+i);
	}
	
	set32(0x900210a8,0x1);
	
	//Start EDMAC
	for(j=0;j<10;j++)
	{
		i=j;
		set8(0x32000100+j, 'A'+i);
	}
	
	set32(0x9018181c,0x833000d5);
	
	//Check 0x90181690[0] is 0x0
	osl_task_delay(1);
	
	return 0;
}

static inline int efuse_write(UINT32 group_addr, UINT32 pg_value)
{
	UINT32 i;
	UINT32 rd_data;
	
	rd_data = read32(EFUSE_BASEADDR+0x1c); //HW_CFG
	rd_data = rd_data & 0x1;
	if(rd_data!=0x01)
	{
		//rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG[3]
		//rd_data = rd_data | 0x8;
		set32(EFUSE_BASEADDR+0x00, 0x8); //EFUSE_CFG
		
		set32(EFUSE_BASEADDR+0x10, 2); //EFUSE_COUNT
		set32(EFUSE_BASEADDR+0x14, 430); //PGM_COUNT
		
		//rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
		//rd_data = rd_data | 0x2;
		set32(EFUSE_BASEADDR+0x00,0xa); //EFUSE_CFG
		
		rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
		rd_data = rd_data & 0x4;
		i=0;
		while(rd_data == 0)
		{
			rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
			rd_data = rd_data & 0x4;
		  	
			if(i>0x100000)
			{
				printf("EFUSE_STATUS time out\n");
				break;
			}
			i++;
		}
		
		//open LDO : GPIO_7_0 0x90018000
		set32(0x90018004, 0x1);
		set32(0x90018000, 0x1);
		osl_task_delay(1);
		
		//Write Efuse
		set32(EFUSE_BASEADDR+0x08, group_addr); //GROUP[6:0]
		set32(EFUSE_BASEADDR+0x0C, pg_value); //PG_VALUE[31:0]
		
		
		//rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG[0]
		//rd_data = rd_data | 0x1;
		set32(EFUSE_BASEADDR+0x00,0xb); //EFUSE_CFG
		
		rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG[0]
		rd_data = rd_data & 0x1;
		i=0;
		while(rd_data == 1)
		{
			rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
			rd_data = rd_data & 0x1;
		  	
			if(i>0x100000)
			{
				printf("time out\n");
				break;
			}
			i++;
		}		
		
		
		//close LDO : GPIO_7_0 0x90018000
		set32(0x90018004, 0x1);
		set32(0x90018000, 0x0);
		
		//Write Efuse
		rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
		rd_data = rd_data & 0xFFFFFFFD;
		set32(EFUSE_BASEADDR+0x00, rd_data); //EFUSE_CFG
		
	}
	else
	{
		printf("Cannot Write Efuse\n");
	}
	
	
	return 0;
}


static inline int efuse_read(UINT32 group_addr)
{
	UINT32 i = 0;
	UINT32 rd_data;
	
	//rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
	//rd_data = rd_data | 0x8;
	set32(EFUSE_BASEADDR+0x00,0x8); //EFUSE_CFG
	
	//Efuse Read Address
	set32(EFUSE_BASEADDR+0x08, group_addr); //GROUP[6:0]
	
	//Enable Read
	//rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
	//rd_data = rd_data | 0x4;
	set32(EFUSE_BASEADDR+0x00,0xc); //EFUSE_CFG
	
	rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
	rd_data = rd_data & 0x4;
	while(rd_data == 0)
	{
		rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
		rd_data = rd_data & 0x4;
		  	
		if(i>0x100000)
		{
			printf("EFUSE_CFG time out\n");
			break;
		}
		i++;
	}		
	
	rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
	rd_data = rd_data & 0x2;
	while(rd_data == 0)
	{
		rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
		rd_data = rd_data & 0x2;
		  	
		if(i>0x100000)
		{
			printf("EFUSE_STATUS time out\n");
			break;
		}
		i++;
	}
	
	rd_data=read32(EFUSE_BASEADDR+0x18); //EFUSE_DATA
	
	printf("GROUP %x value is %x\n", group_addr, rd_data);
		
	
	return 0;
}


int efuse_test(UINT32 group_addr)
{
	UINT32 i,j;
	UINT32 rd_data;
	
	
	printf("efuse test begin!\n");
	set32(EFUSE_BASEADDR+0x00,0x08);
	
	set32(EFUSE_BASEADDR+0x10, 2); //EFUSE_COUNT
	set32(EFUSE_BASEADDR+0x14, 430); //PGM_COUNT
	
	set32(EFUSE_BASEADDR+0x00,0x0a);
	
	rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
	rd_data = rd_data & 0x4;
	j=0;
	while(rd_data != 0x4)
	{
		rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
		rd_data = rd_data & 0x4;
		  	
		if(j>0x100000)
		{
			printf("EFUSE_STATUS time out 01\n");
			break;
		}
		j++;
	}	
	
	//open LDO : GPIO_7_0 0x90018000
	set32(0x90018004, 0x1);
	set32(0x90018000, 0x1);
	osl_task_delay(1);
	for(i=0;i<128;i++)
	{
		set32(EFUSE_BASEADDR+0x08, i);
		set32(EFUSE_BASEADDR+0x0c, (i+4)*1024*1024*16+(i+3)*1024*64+(i+2)*256+(i+1));
		set32(EFUSE_BASEADDR+0x00, 0xb);
		
		rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
		j=0;
        while(rd_data != 0xb)
        {
	        rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
		  	
	        if(j>0x100000)
	        {
		         printf("EFUSE_CFG time out 02\n");
		         break;
	        }
	        j++;
        }	
	
		rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
		if(rd_data != 0x4)
		{
			printf("Error, status is not right\n");
		}
		
		rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
		rd_data = rd_data & 0x1;
		j=0;
		while(rd_data != 0x01)
		{
			rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
            rd_data = rd_data & 0x1;
			
			if(j>0x100000)
			{
				printf("EFUSE_STATUS time out 03\n");
				break;
			}
			j++;
		}

    }
	
	
	//close LDO : GPIO_7_0 0x90018000
	set32(0x90018004, 0x1);
	set32(0x90018000, 0x0);
		
	//Write Efuse
	rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_CFG
	rd_data = rd_data & 0xFFFFFFFD;
	set32(EFUSE_BASEADDR+0x00, rd_data); //EFUSE_CFG
	
	osl_task_delay(1);
	set32(EFUSE_BASEADDR+0x00, 0x08);
	//close LDO : GPIO_7_0 0x90018000
	///set32(0x90018004, 0x1);
	///set32(0x90018000, 0x0);
	
	for(i=0;i<128;i++)
	{
		set32(EFUSE_BASEADDR+0x08,i);
		set32(EFUSE_BASEADDR+0x00,0x0c);
		
		rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_STATUS
        j=0;
		while(rd_data != 0xc)
        {
	        rd_data = read32(EFUSE_BASEADDR+0x00); //EFUSE_STATUS
			
			if(j>0x100000)
			{
				printf("EFUSE_STATUS time out 04\n");
				break;
			}
			j++;
        }
		
		rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
		rd_data = rd_data & 0x2;
		j=0;
		while(rd_data != 0x2)
		{
			rd_data = read32(EFUSE_BASEADDR+0x04); //EFUSE_STATUS
			rd_data = rd_data & 0x2;
			
			if(j>0x100000)
			{
				printf("EFUSE_STATUS time out 05\n");
				break;
			}
			j++;
		}
		
		rd_data = read32(EFUSE_BASEADDR+0x18);
		if(rd_data != (i+4)*1024*1024*16+(i+3)*1024*64+(i+2)*256+(i+1) )
		{
		    printf("Error, Read data is %x, Expect data is %x\n", rd_data,(i+4)*1024*1024*16+(i+3)*1024*64+(i+2)*256+(i+1));
			osl_task_delay(1);
		}
		else
		{
			printf("Compare right %x, Read data is %x\n", i,rd_data);
			osl_task_delay(1);
		}
		
	}
	
	return 0;
}

