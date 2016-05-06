/************************************************************
  Copyright (C), 1988-2009, Huawei Tech. Co., Ltd.
  FileName: BasicFunc.c
  Author: ZhaoMinjun	ID: 64046        Date: 2009-11-2
  Description: This file inludes all base functions of 
               Write/Read opration      
  Version:     1.0
  Function List:  
    1. 
  History:         
      <author>     <ID>     <time>   <version >   <desc>
      ZhaoMinjun   64046   09/11/2     1.0     initial releas  
***********************************************************/

#include  <stdio.h>
#include  <sre_typedef.h>
#include  <BasicFunc.h>

/*************************************************
  Function:       set64
  Description:    64-bit data write operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
				  value: 64-bit data
  Output:         
  Return:         void
  Others:         
*************************************************/
//void set64(UINT32 pAddr,UINT64 value)
//{
//	*((volatile UINT64 *)pAddr) = value;
//}

/*************************************************
  Function:       set32
  Description:    32-bit data write operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  value: 32-bit data
  Output:         
  Return:         void
  Others:         
*************************************************/
void set32(UINT32 pAddr,UINT32 value)
{
    *((volatile UINT32 *)pAddr) = value;
}

/*************************************************
  Function:       set16
  Description:    16-bit data write operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  value: 16-bit data
  Output:         
  Return:         void
  Others:         
*************************************************/
void set16(UINT32 pAddr, UINT16 value)
{
    *((volatile UINT16 *)pAddr) = value;
}

/*************************************************
  Function:       set8
  Description:    8-bit data write operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  value: 8-bit data
  Output:         
  Return:         void
  Others:         
*************************************************/
void set8(UINT32 pAddr, UINT8 value)
{
    *((volatile UINT8 *)pAddr) = value;
}


/*************************************************
  Function:       read64
  Description:    64-bit data read operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
  Output:         
  Return:         64-bit data
  Others:         
*************************************************/
//UINT64 read64(UINT32 pAddr)
//{
//	UINT64 Data;
   
//	Data = *((volatile UINT64 *)pAddr);

//	return Data; 
//}

/*************************************************
  Function:       read32
  Description:    32-bit data read operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
  Output:         
  Return:         32-bit data
  Others:         
*************************************************/
UINT32 read32(UINT32 pAddr)
{
    UINT32 Data;
   
    Data = *((volatile UINT32 *)pAddr);

    return Data; 
}

/*************************************************
  Function:       read32_expect
  Description:    32-bit data read operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
  Output:         
  Return:         32-bit data
  Others:         
*************************************************/
int read32_expect(UINT32 pAddr,  UINT32 expect_Data)
{	
	UINT32 r_Data;	
	
	r_Data = read32(pAddr);
	
	if(r_Data == expect_Data)
	{
		return 0;
	}
	else
	{
		printf("read error: %x,%x,\n",pAddr,r_Data);
		return 1;
	}
}

int read8_expect(UINT32 pAddr, UINT8 ept_data)
{

   UINT8 rd_data;
   
   rd_data = *((volatile UINT8 *)pAddr);

   if(rd_data != ept_data)
	{
		printf("error: pAddr = %x, read data = %x, expect data = %x\n", pAddr, rd_data, ept_data);
		return 1;
	}

   return 0; 
}

/*************************************************
  Function:       read16
  Description:    16-bit data read operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
  Output:         
  Return:         16-bit data
  Others:         
*************************************************/
UINT16 read16(UINT32 pAddr)
{
    UINT16 Data;
   
    Data = *((volatile UINT16 *)pAddr);

    return Data; 
}

/*************************************************
  Function:       read8
  Description:    8-bit data read operation
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
  Output:         8-bit data
  Return:         UINT8 Data
  Others:         
*************************************************/
UINT8 read8(UINT32 pAddr)
{
    UINT8 Data;
   
    Data = *((volatile UINT8 *)pAddr);

    return Data; 
}

/*************************************************
  Function:       readbit
  Description:    Read a value of an indicated bit
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  BitAddr: Bit number of the address
  Output:         
  Return:         UINT32 BitValue
  Others:         
*************************************************/
UINT32 readbit(UINT32 pAddr,UINT32 BitNum)
{
    UINT32 RawData;
    UINT32 BitMask=0x0;
    UINT32 DataMasked;
    UINT32 BitValue;
    
    RawData = read32(pAddr);
    BitMask = 1 << BitNum;
    DataMasked = RawData & BitMask ;
    BitValue = DataMasked >> BitNum;
    
    return BitValue;
}

/*************************************************
  Function:       setbit
  Description:    Set a new value of an indicated bit
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  BitNum: Bit number of the address
                  BitValue: the value to be set. ONLY 0 or 1
  Output:         
  Return:         UINT32
  Others:         
*************************************************/
UINT32 setbit(UINT32 pAddr,UINT32 BitNum, UINT32 BitValue)
{ 
    UINT32 RawData;
    UINT32 BitMask_temp=0x0;
    UINT32 BitMask=0x0;
    UINT32 DataMasked;
    UINT32 NewData;
    
    if((BitValue == 0) | (BitValue == 1))
    {
        RawData = read32(pAddr);
        
        //Set bit mask to protect the other bits
        BitMask_temp = 1 << BitNum;
        BitMask = ~BitMask_temp;
        DataMasked = RawData & BitMask ;
        NewData = DataMasked | (BitValue << BitNum) ;
 	set32(pAddr,NewData);
    }
    else
    {
#ifdef _UNIT_DEBUG
      printf("ERROR: BitValue is not 0 or 1!\n");
#endif
      return 1;
    }
    return 0;
}


/*************************************************
  Function:       readbits
  Description:    Read value of consecutiv bits
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  HighBit : The highbit number of 
                            the bit in 32bit register value
                  LowBit :  The lowbit number of 
                            the bit in 32bit register value
  Output:         
  Return:         UINT32 RegBitValue
  Others:         
*************************************************/
UINT32 readbits(UINT32 pAddr, UINT32 HighBit, UINT32 LowBit)
{
    UINT32 RegInitData;
    UINT32 BitMask=0x0;
    UINT32 BitMask_temp;
    UINT32 RegBitValue;
    UINT32 RegDataBit;
    UINT32 i;
   
    RegInitData = read32(pAddr);
   
    //Create bit mask used by AND function to get the Bits that user need
    for(i=0;i<(HighBit-LowBit+1);i++)
    {
        BitMask_temp = 1 << (LowBit+i);
        BitMask = BitMask + BitMask_temp;
    } 
   
    RegDataBit = BitMask & RegInitData;
   
    //Get the final value in normal 32-bit form
    RegBitValue = RegDataBit >> LowBit;
   
    return RegBitValue;
      
}

/*************************************************
  Function:       readbits
  Description:    Set value of consecutiv bits
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          pAddr: Address indicated
                  HighBit : The highbit number of 
                            the bit in 32bit register value
                  LowBit :  The lowbit number of 
                            the bit in 32bit register value
                  BitValue: the value to be set.
  Output:         
  Return:         UINT32 
  Others:         
*************************************************/
UINT32 setbits(UINT32 pAddr, int HighBit, int LowBit, UINT32 BitValue)
{

    UINT32 BitNewValue=0x0;
    UINT32 BitMask=0x0;
    UINT32 BitMask_temp;
    UINT32 RawData;
    UINT32 NewData;
    UINT32 BitMaskInv;
    
    int BitWidth;
    int RegRawBit[32]={0};
    int RegNewBit[32]={0};
    int RegBitInput[32]={0};
    int i;
 
    //Get the width of bits that the user need
    BitWidth = HighBit - LowBit + 1;
 
    //Get each bit of the BitValue that user wanna use
    for(i=0;i<BitWidth;i++)
    {
        RegBitInput[i] = (BitValue & (1<<i)) >> i;
    }
 
    //Get each bit of exited Register Bit Value, and then change each bit by new value
    for(i=0;i<BitWidth;i++)
    {
        RegRawBit[i] = readbits(pAddr, (LowBit+i), (LowBit+i)); 
        
        if(RegRawBit[i] == 0)
        {
           RegNewBit[i] = RegBitInput[i] | RegRawBit[i];
        }
        else
        {
           RegNewBit[i] = RegBitInput[i] & RegRawBit[i];
        }
 
        BitNewValue = BitNewValue + (RegNewBit[i] << i);
        
    }
 
    //Get the raw data of the register
    RawData = read32(pAddr);
 
    //Create a Bit Mask
    for(i=0;i<BitWidth;i++)
    {
           BitMask_temp = 1 << (LowBit+i);
           BitMask = BitMask + BitMask_temp;
    } 
 
    //Inverse the Bit Mask to protect the bits that user don't wanna change
    BitMaskInv = ~ BitMask;
 
    //Put the new bits value that user need into 32-bit register value
    NewData = (RawData & BitMaskInv) | (BitNewValue<<LowBit);
 
    // Write the new register value
    set32(pAddr, NewData);
    
    return 0;

}

