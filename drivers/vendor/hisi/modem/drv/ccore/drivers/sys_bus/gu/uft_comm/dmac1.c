/************************************************************
  Copyright (C), 1988-2009, Huawei Tech. Co., Ltd.
  FileName: BasicFunc.c
  Author: BaiRengang	ID: 141795        Date: 2009-11-30
  Description: This file inludes all base functions of DMAC Transfer      
  Version:     1.0
  Function List:  
	1. 
  History:         // 历史修改记录
	  <author>  <ID>     <time>   <version >   <desc>
	  David     00000    96/10/12     1.0     build this moudle  
***********************************************************/    
#include <stdio.h>
#include <osl_thread.h>
#include "BasicFunc.h"
#include "dmac.h"


/*************************************************
  Function:       DmaM2MTrans
  Description:    This function uses DMA to transfer data from Memory to Memory 
  Calls:          set32 ; set8 ; read32 ; read8 ; setbits
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          DmaBaseAddr:   DMAC Base Address
				  src_addr:      Source Address
				  des_addr:      Destination Address
				  TransferSize:  Transfer Size : 0x1~0xfff
				  src_inc:       Source Increment
				  des_inc:       Destination Increment
				  SMaster:       0->Master1,1->Master2
				  DMaster:       0->Master1,1->Master2
				  SWidth:        width 0->8 ,1->16,2->32bit
	              DWidth:        width 0->8 ,1->16,2->32bit					 
                  SBSize:        Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
	              DBSize:        Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
				  Channel:       Choose DMAC Channel - 0~7
				  Intr_Master:   Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
  Output:         
  Return:         void
  Others:         
*************************************************/
int DmaM2MTrans( UINT32 DmaBaseAddr,     //DMAC Base Address
		  UINT32 src_addr,        //Source Address
	      UINT32 des_addr,        //Destination Address
		  int    SMaster,         //0->Master1,1->Master2
		  int    DMaster,         //0->Master1,1->Master2		  
		  int    src_inc,         //Source Increment
		  int    des_inc,         //Destination Increment
		  int    SWidth,          //width 0->8 ,1->16,2->32bit
	      int    DWidth,          //width 0->8 ,1->16,2->32bit					 
          int    SBSize,          //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
	      int    DBSize,          //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
       	  int    TransferSize,    //Transfer Size : 0x1~0xfff
		  int    Channel,         //Choose DMAC Channel - 0~7
		  int    Intr_Master )    //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
{    
    UINT32 chan_offset;
    UINT32 dmac_control;   
    int i,rd_data;
       
    /*Config DMAC Control Register*/
    switch(SBSize)
    {
        case 0 : dmac_control = 0x80000000;
            break;
        case 1 : dmac_control = 0x80001000;
            break;
        case 2 : dmac_control = 0x80002000;
            break;
        case 3 : dmac_control = 0x80003000;
            break;
        case 4 : dmac_control = 0x80004000;
            break;
        case 5 : dmac_control = 0x80005000;
            break;
        case 6 : dmac_control = 0x80006000;
            break;
        case 7 : dmac_control = 0x80007000;
            break;
        default: dmac_control = 0x80000000;
            break;							
    }
    
    switch(DBSize)
    {
        case 0 : dmac_control |= 0x00000000;
            break;
        case 1 : dmac_control |= 0x00008000;
            break;
        case 2 : dmac_control |= 0x00010000;
            break;
        case 3 : dmac_control |= 0x00018000;
            break;
        case 4 : dmac_control |= 0x00020000;
            break;
        case 5 : dmac_control |= 0x00028000;
            break;
        case 6 : dmac_control |= 0x00030000;
            break;
        case 7 : dmac_control |= 0x00038000;
            break;
        default: dmac_control |= 0x00000000;
            break;							
    }
    if ( src_inc != 0 )
    {
        dmac_control = dmac_control | 0x04000000; 
    }
    if ( des_inc !=0 )
    {
        dmac_control = dmac_control | 0x08000000;
    }
    	
    switch(SWidth)
    {
        case 0 : 
            break;
        case 1 : dmac_control |= 0x40000;
            break;
        case 2 : dmac_control |= 0x80000;
            break;
        default: dmac_control |= 0x80000;
            break;							
    }
    
    switch(DWidth)
    {
        case 0 : 
            break;
        case 1 : dmac_control |= 0x200000;
            break;
        case 2 : dmac_control |= 0x400000;
            break;
        default: dmac_control |= 0x400000;
            break;							
    }
    
    /* DMAC Configuration */
    chan_offset = DmaBaseAddr + DMACCHANNELOFFSET+ Channel*0x20;		//DMAC Channel choice
    
    set32((DMACCONFIGURATION+DmaBaseAddr), 0x0);		//Enable DMAC
    for(i=0;i<8;i++)
    {
        set32( DmaBaseAddr + DMACCHANNELOFFSET+i*0x20,0x0);
    }
    set32( (DMACCONFIGURATION+DmaBaseAddr), 0x1 );
    
    /* Clear Interrupts */
    set32( DmaBaseAddr+DMACINTTCCLEAR, 0xff );
    set32( DmaBaseAddr+DMACINTERRCLR, 0xff );
    
    set32(chan_offset+DMACCXSRCADDRCH0, src_addr);	//Define source address
    set32(chan_offset+DMACCXDESTADDRCH0, des_addr);	//Define destination address
    set32(chan_offset+DMACCXCONTROLCH0, (dmac_control+(UINT32)TransferSize));	//Dmac control
    
    /* Enable DMAC Transfer */
    switch( Intr_Master )
    {
        case 0 : set32(chan_offset+DMACCXCONFIGURATIONCH0,0x0001);
            break;
        case 1 : set32(chan_offset+DMACCXCONFIGURATIONCH0,0x180001);
            break;
        default: set32(chan_offset+DMACCXCONFIGURATIONCH0,0x0001);
            break;	
    }
    
    /* wait until transfer finish */
    i= 0 ;
    while(1)
    {
        i++;
        rd_data = readbit(chan_offset+DMACCXCONFIGURATIONCH0,0);
        if(rd_data == 0x0)
        {
            return DMAC_OK;
        }
        else if(i==1000000)
        {
#ifdef _UNIT_DEBUG
            printf("ERROR: DmaM2MTrans time counter overstep the limit!\n");
#endif
            return 1;
        }
        osl_task_delay(1);	
    }
}	


/*************************************************
  Function:       DmaM2MLLITrans
  Description:    This function is used to DMA transfer data from Memory to Memory
  Calls:          set32 ; set8 ; read32 ; read8 ; setbits
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          DmaBaseAddr:   DMAC Base Address
				  src_addr:      Source Address
				  des_addr:      Destination Address
				  LLI_addr:      LLI Address
				  TransferSize:  Transfer Size >= 0x1000
				  src_inc:       Source Increment
				  des_inc:       Destination Increment
				  SMaster:       0->Master1,1->Master2
				  DMaster:       0->Master1,1->Master2
				  SWidth:        width 0->8 ,1->16,2->32bit
				  DWidth:        width 0->8 ,1->16,2->32bit					 
				  SBSize:        Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
				  DBSize:        Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
				  Channel:       Choose DMAC Channel - 0~7
				  Intr_Master:   Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
  Output:         
  Return:         void
  Others:         
*************************************************/
int DmaM2MLLITrans( UINT32 DmaBaseAddr,     //DMAC Base Address
		     UINT32 src_addr,        //Source Address
	         UINT32 des_addr,        //Destination Address
	         UINT32 LLI_addr,        //LLI Address
       		 int    SMaster,         //0->Master1,1->Master2
		     int    DMaster,         //0->Master1,1->Master2
		     int    src_inc,         //Source Increment
		     int    des_inc,         //Destination Increment
		     int    SWidth,          //width 0->8 ,1->16,2->32bit
		     int    DWidth,          //width 0->8 ,1->16,2->32bit					 
		     int    SBSize,          //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
		     int    DBSize,          //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
     	     int    TransferSize,    //Transfer Size : >= 0x1000
		     int    Channel,         //Choose DMAC Channel - 0~7
		     int    Intr_Master )    //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
{
    
    UINT32 chan_offset;
    UINT32 dmac_control;   
    int i,rd_data;
     
    /*Config DMAC Control Register*/
    switch(SBSize)
    {
        case 0 : dmac_control = 0x80000000;
            break;
        case 1 : dmac_control = 0x80001000;
            break;
        case 2 : dmac_control = 0x80002000;
            break;
        case 3 : dmac_control = 0x80003000;
            break;
        case 4 : dmac_control = 0x80004000;
            break;
        case 5 : dmac_control = 0x80005000;
            break;
        case 6 : dmac_control = 0x80006000;
            break;
        case 7 : dmac_control = 0x80007000;
            break;
        default: dmac_control = 0x80000000;
            break;							
    }
    
    switch(DBSize)
    {
        case 0 : dmac_control |= 0x00000000;
            break;
        case 1 : dmac_control |= 0x00008000;
            break;
        case 2 : dmac_control |= 0x00010000;
            break;
        case 3 : dmac_control |= 0x00018000;
            break;
        case 4 : dmac_control |= 0x00020000;
            break;
        case 5 : dmac_control |= 0x00028000;
            break;
        case 6 : dmac_control |= 0x00030000;
            break;
        case 7 : dmac_control |= 0x00038000;
            break;
        default: dmac_control |= 0x00000000;
            break;							
    }
    if ( src_inc != 0 )
    {
        dmac_control = dmac_control | 0x04000000; 
    }
    if ( des_inc !=0 )
    {
        dmac_control = dmac_control | 0x08000000;
    }
    	
    switch(SWidth)
    {
        case 0 : 
            break;
        case 1 : dmac_control |= 0x40000;
            break;
        case 2 : dmac_control |= 0x80000;
            break;
        default: dmac_control |= 0x80000;
            break;							
    }
    
    switch(DWidth)
    {
        case 0 : 
            break;
        case 1 : dmac_control |= 0x200000;
            break;
        case 2 : dmac_control |= 0x400000;
            break;
        default: dmac_control |= 0x400000;
            break;							
    }
    
    chan_offset = DmaBaseAddr + DMACCHANNELOFFSET+Channel*0x20;		//DMAC Channel choice
    
    /* Build LLI, transfer 800 data every time */
    set32(chan_offset+DMACCXLLICH,LLI_addr);		//LLI table address
    
    /* Build LLI table */
    for ( i = 0; i< TransferSize/0x800-1; i++)
    {
        set32(LLI_addr + 0x0 + i*0x10, src_addr + (i+1)*0x4*0x800);
        set32(LLI_addr + 0x4 + i*0x10, des_addr + (i+1)*0x4*0x800);
        set32(LLI_addr + 0x8 + i*0x10, LLI_addr + (i+1)*0x10);
        set32(LLI_addr + 0xc + i*0x10, dmac_control+0x800);
    }
    
    /* LLI table end */
    if(TransferSize%0x800 != 0x0)
    {
        set32(LLI_addr + 0x0 + i*0x10, src_addr + (i+1)*0x4*0x800);
        set32(LLI_addr + 0x4 + i*0x10, des_addr + (i+1)*0x4*0x800);
        set32(LLI_addr + 0x8 + i*0x10, 0x0);
        set32(LLI_addr + 0xc + i*0x10, dmac_control+TransferSize%0x800);
    }
    else
    {
        set32(LLI_addr + 0x8 + (i-1)*0x10, 0x0);
    }
    
    /*DMAC Configuration*/
    set32(DmaBaseAddr+DMACCONFIGURATION, 0x0);		//Enable DMAC
    for(i=0;i<8;i++)
    {
        set32( DmaBaseAddr+DMACCHANNELOFFSET+i*0x20,0x0);
    }
    set32( DmaBaseAddr+DMACCONFIGURATION, 0x1 );
    
    /* Clear Interrupts */
    set32( DmaBaseAddr+DMACINTTCCLEAR, 0xff );
    set32( DmaBaseAddr+DMACINTERRCLR, 0xff );
    
    set32(chan_offset+DMACCXSRCADDRCH, src_addr);	// Define source address
    set32(chan_offset+DMACCXDESTADDRCH, des_addr);	//Define destination address
    set32(chan_offset+DMACCXCONTROLCH, (dmac_control+0x800));	//Dmac control
    
    //Enable DMAC Transfer
    switch( Intr_Master )
    {
        case 0 : set32(chan_offset+DMACCXCONFIGURATIONCH,0xc001);
            break;
        case 1 : set32(chan_offset+DMACCXCONFIGURATIONCH,0x18c001);
            break;	    
        default: set32(chan_offset+DMACCXCONFIGURATIONCH,0xc001);
            break;	
    }
    
    i= 0 ;
    while(1)
    {
        i++;
        rd_data = readbit(chan_offset+DMACCXCONFIGURATIONCH0,0);
        if(rd_data == 0x0)
        {
            return DMAC_OK;
        }
        else if(i==1000000)
        {
#ifdef _UNIT_DEBUG
            printf("ERROR: DmaM2MLLITrans time counter overstep the limit!\n");
#endif
            return 1;
        }
        osl_task_delay(1);	
    }    
}	


/*************************************************
  Function:       DmaM2MTrans32
  Description:    This function uses DMA to transfer data from Memory to Memory,
                  the configuration is: master 0, width 32bits, burst 16               
  Calls:          set32 ; set8 ; read32 ; read8 ; setbits
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          DmaBaseAddr:   DMAC Base Address
				  src_addr:      Source Address
				  des_addr:      Destination Address
				  TransferSize:  Transfer Size : 0x1~0xfff
                  Channel:       Choose DMAC Channel - 0~7
				  Intr_Master:   Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
  Output:         
  Return:         void
  Others:         
*************************************************/
int DmaM2MTrans32( UINT32 DmaBaseAddr,      //DMAC Base Address
                   UINT32 src_addr,         //Source Address
                   UINT32 des_addr,         //Destination Address
                   int    TransferSize,     //Transfer Size : 0x1~0xfff
                   int    Channel,          //Choose DMAC Channel - 0~7
                   int    Intr_Master )     //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
{ 

    int checkdata;
           
    checkdata = DmaM2MTrans( DmaBaseAddr,     //DMAC Base Address
                             src_addr,        //Source Address
                             des_addr,        //Destination Address
                             0,               //0->Master1,1->Master2
                             0,               //0->Master1,1->Master2
                             1,               //Source Increment
                             1,               //Destination Increment
                             2,               //width 0->8 ,1->16,2->32bit
                             2,               //width 0->8 ,1->16,2->32bit					 
                             3,               //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                             3,               //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                             TransferSize,    //Transfer Size : 0x1~0xfff
                             Channel,         //Choose DMAC Channel - 0~7
                             Intr_Master );   //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
    
    return checkdata;
}
    

					 

/*************************************************
  Function:       DmaM2MLLITrans32
  Description:    This function is used to DMA transfer data from Memory to Memory,
                  the configuration is: master 0, width 32bits, burst 64
  Calls:          set32 ; set8 ; read32 ; read8 ; setbits
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          DmaBaseAddr:   DMAC Base Address
				  src_addr:      Source Address
				  des_addr:      Destination Address
				  LLI_addr:      LLI Address
				  TransferSize:  Transfer Size >= 0x1000
				  Channel:       Choose DMAC Channel - 0~7
				  Intr_Master:   Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
  Output:         
  Return:         void
  Others:         
*************************************************/
int DmaM2MLLITrans32( UINT32 DmaBaseAddr,     //DMAC Base Address
                       UINT32 src_addr,        //Source Address
                       UINT32 des_addr,        //Destination Address
                       UINT32 LLI_addr,        //LLI Address
                       int    TransferSize,    //Transfer Size : >= 0x1000
                       int    Channel,         //Choose DMAC Channel - 0~7
                       int    Intr_Master )    //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
{
    int checkdata;
    checkdata = DmaM2MLLITrans( DmaBaseAddr,     //DMAC Base Address
                                src_addr,        //Source Address
                                des_addr,        //Destination Address
                                LLI_addr,        //LLI Address
                                0,               //0->Master1,1->Master2
                                0,               //0->Master1,1->Master2
                                1,               //Source Increment
                                1,               //Destination Increment
                                2,               //width 0->8 ,1->16,2->32bit
                                2,               //width 0->8 ,1->16,2->32bit					 
                                5,               //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                                5,               //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                                TransferSize,    //Transfer Size : 0x1~0xfff
                                Channel,         //Choose DMAC Channel - 0~7
                                Intr_Master );   //Choose Master(ARM or ZSP): 0->ARM,1->ZSP   
    return   checkdata;                           
}

int DmaM2MTrans1( UINT32 DmaBaseAddr,     //DMAC Base Address
		  UINT32 src_addr,        //Source Address
		  UINT32 des_addr,        //Destination Address
		  int    SMaster,         //0->Master1,1->Master2
		  int    DMaster,         //0->Master1,1->Master2		  
		  int    src_inc,         //Source Increment
		  int    des_inc,         //Destination Increment
		  int    SWidth,          //width 0->8 ,1->16,2->32bit
		  int    DWidth,          //width 0->8 ,1->16,2->32bit					 
		  int    SBSize,          //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
		  int    DBSize,          //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
		  int    TransferSize,    //Transfer Size : 0x1~0xfff
		  int    Channel,         //Choose DMAC Channel - 0~7
		  int    Intr_Master )    //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
{    
	UINT32 chan_offset;
	UINT32 dmac_control;   
       
	/*Config DMAC Control Register*/
	switch(SBSize)
	{
		case 0 : dmac_control = 0x80000000;
			break;
		case 1 : dmac_control = 0x80001000;
			break;
		case 2 : dmac_control = 0x80002000;
			break;
		case 3 : dmac_control = 0x80003000;
			break;
		case 4 : dmac_control = 0x80004000;
			break;
		case 5 : dmac_control = 0x80005000;
			break;
		case 6 : dmac_control = 0x80006000;
			break;
		case 7 : dmac_control = 0x80007000;
			break;
		default: dmac_control = 0x80000000;
			break;							
	}
    
	switch(DBSize)
	{
		case 0 : dmac_control |= 0x00000000;
			break;
		case 1 : dmac_control |= 0x00008000;
			break;
		case 2 : dmac_control |= 0x00010000;
			break;
		case 3 : dmac_control |= 0x00018000;
			break;
		case 4 : dmac_control |= 0x00020000;
			break;
		case 5 : dmac_control |= 0x00028000;
			break;
		case 6 : dmac_control |= 0x00030000;
			break;
		case 7 : dmac_control |= 0x00038000;
			break;
		default: dmac_control |= 0x00000000;
			break;							
	}
	if ( src_inc != 0 )
	{
		dmac_control = dmac_control | 0x04000000; 
	}
	if ( des_inc !=0 )
	{
		dmac_control = dmac_control | 0x08000000;
	}
    	
	switch(SWidth)
	{
		case 0 : 
			break;
		case 1 : dmac_control |= 0x40000;
			break;
		case 2 : dmac_control |= 0x80000;
			break;
		default: dmac_control |= 0x80000;
			break;							
	}
    
	switch(DWidth)
	{
		case 0 : 
			break;
		case 1 : dmac_control |= 0x200000;
			break;
		case 2 : dmac_control |= 0x400000;
			break;
		default: dmac_control |= 0x400000;
			break;							
	}
    
	/* DMAC Configuration */
	chan_offset = DmaBaseAddr + DMACCHANNELOFFSET+ Channel*0x20;		//DMAC Channel choice
    
	set32((DMACCONFIGURATION+DmaBaseAddr), 0x0);		//Enable DMAC
	/*for(i=0;i<8;i++)
	{
		set32( DmaBaseAddr + DMACCHANNELOFFSET+i*0x20,0x0);
	}*/
	set32( DmaBaseAddr + DMACCHANNELOFFSET+Channel*0x20,0x0);
	
	set32( (DMACCONFIGURATION+DmaBaseAddr), 0x1 );
    
	/* Clear Interrupts */
	set32( DmaBaseAddr+DMACINTTCCLEAR, 0xff );
	set32( DmaBaseAddr+DMACINTERRCLR, 0xff );
    
	set32(chan_offset+DMACCXSRCADDRCH0, src_addr);	//Define source address
	set32(chan_offset+DMACCXDESTADDRCH0, des_addr);	//Define destination address
	set32(chan_offset+DMACCXCONTROLCH0, (dmac_control+(UINT32)TransferSize));	//Dmac control

    return 0;
}	

int DmaM2MTransEn( UINT32 DmaBaseAddr,     //DMAC Base Address
		           int    Channel,         //Choose DMAC Channel - 0~7
		           int    Intr_Master )    //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
{    
	UINT32 chan_offset;
	//UINT32 dmac_control;   
	//int i,rd_data;
	
	/* DMAC Configuration */
	chan_offset = DmaBaseAddr + DMACCHANNELOFFSET+ Channel*0x20;		//DMAC Channel choice
        
	/* Enable DMAC Transfer */
	switch( Intr_Master )
	{
		case 0 : set32(chan_offset+DMACCXCONFIGURATIONCH0,0x0001);
			break;
		case 1 : set32(chan_offset+DMACCXCONFIGURATIONCH0,0x180001);
			break;
		default: set32(chan_offset+DMACCXCONFIGURATIONCH0,0x0001);
			break;	
	}
    
	/* wait until transfer finish */
	//i= 0 ;
	return 0;

}

/*************************************************
  Function:       DmaM2MCheck
  Description:    This function uses to Check DMA transfer result
  Calls:          set32 ; set8 ; read32 ; read8 ; setbits
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          
				  src_addr:      Source Address
				  des_addr:      Destination Address
				  TransferSize:  Transfer Size : 0x1~0xfff
				  Channel:       Choose DMAC Channel - 0~7
					 
  Output:         
  Return:         void
  Others:         
*************************************************/
int DmaM2MCheck( UINT32 DmaBaseAddr,     //DMAC Base Address
                  UINT32 src_addr,         //Source Address
                  UINT32 des_addr,         //Destination Address
	              UINT32    TransferSize,     //Transfer Size : 0x1~0xfff                 
                  int    Channel     )    //Choose DMAC Channel - 0~7
{
  UINT32 iv;
  UINT32 rd_val,src_val;
  UINT32 err_flag;
  UINT32 rd_data;

  UINT32 chan_offset;

  /* DMAC Configuration */
  chan_offset = DmaBaseAddr + DMACCHANNELOFFSET+ Channel*0x20;		//DMAC Channel choice
  
  rd_val = 0x0;
  iv = 0;
  
/*  for(iv=0;iv<0x100;iv++)
{
  rd_data = readbit(chan_offset+DMACCXCONFIGURATIONCH0,0);
}*/
	
//taskDelay(1);
    rd_data = readbit(chan_offset+DMACCXCONFIGURATIONCH0,0);
	while(rd_data == 1)
	{
		iv=iv+1;
		rd_data = readbit(chan_offset+DMACCXCONFIGURATIONCH0,0);
        if(iv>0x100000)
		{
//#ifdef _UNIT_DEBUG
			printf("ERROR: DmaM2MTrans time counter overstep the limit!\n");
//#endif
			return 1;
		}
		//taskDelay(1);	
	}


 for(err_flag=0,iv=0;iv<TransferSize;iv++)
  {
	src_val= read32(src_addr + 4*iv);
	rd_val = read32(des_addr + 4*iv);
	if(src_val != rd_val)
	{
		printf("dma error:sa = %x sd = %x,da = %x dd = %x\n", src_addr+0x4*iv, src_val, des_addr + 4*iv, rd_val);
		err_flag++;
	}
  }

  if(err_flag == 0)
  {
	printf("ZDMA OK: sa = %x, da = %x\n",src_addr,des_addr);
	return 0;
  }
  else
  {
    return 1;
  }

}

int DmaM2MCheck1()    //Choose DMAC Channel - 0~7
{
  UINT32 iv;
  UINT32 rd_val;
  UINT32 rd_data;

  UINT32 chan_offset;

  /* DMAC Configuration */
  chan_offset = 0x60380000 + DMACCHANNELOFFSET+ 6*0x20;		//DMAC Channel choice
  
  rd_val = 0x0;
  iv = 0;
  
  for(iv=0;iv<0x100;iv++)
{
  rd_data = readbit(chan_offset+DMACCXCONFIGURATIONCH0,0);
}

	rd_val  = rd_val;
	rd_data = rd_data;
return 0;

}
