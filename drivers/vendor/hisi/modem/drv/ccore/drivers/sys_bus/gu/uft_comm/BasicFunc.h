/************************************************************
  Copyright (C), 1988-2009, Huawei Tech. Co., Ltd.
  FileName: BasicFunc.h
  Author: ZhaoMinjun	ID: 64046        Date: 2009-11-2
  Description: This file inludes all base functions of 
               Write/Read opration      
  Version:     1.0
  Function List:  
    1. 

***********************************************************/

void set32(UINT32 pAddr,UINT32 value);

void set16(UINT32 pAddr, UINT16 value);

void set8(UINT32 pAddr, UINT8 value);

//UINT64 read64(UINT32 pAddr);

UINT32 read32(UINT32 pAddr);

int    read32_expect(UINT32 pAddr,  UINT32 expect_Data);

UINT16 read16(UINT32 pAddr);

UINT8 read8(UINT32 pAddr);

UINT32 readbit(UINT32 pAddr,UINT32 BitNum);

UINT32 setbit(UINT32 pAddr,UINT32 BitNum, UINT32 BitValue);

UINT32 readbits(UINT32 pAddr, UINT32 HighBit, UINT32 LowBit);

UINT32 setbits(UINT32 pAddr, int HighBit, int LowBit, UINT32 BitValue);


