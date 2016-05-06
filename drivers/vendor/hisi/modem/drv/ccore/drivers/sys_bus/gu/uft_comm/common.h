/************************************************************
  Copyright (C), 1988-2009, Huawei Tech. Co., Ltd.
  FileName: Common.c
  Author: ZhaoMinjun	ID: 64046        Date: 2009-11-2
  Description: This file inludes all base functions of 
               Write/Read opration      
  Version:     1.0
  Function List:  
    1. 
  History:         
      <author>     <ID>     <time>   <version >   <desc>
      WanXing     128668    09/11/16     1.0     initial releas  
***********************************************************/

#include <stdio.h>
#include "BasicFunc.h"
#include "baseaddr.h"



void DelayRandom();

void DelayRandomSet(UINT32 DelayMin,UINT32 DelayMax);

void GetFilePath(INT8 *GenDir, INT8 *FileName);

int DownLoadFile(UINT32 Des_addr, INT8 *FileName );

int CevaLoop();

int CevaRandom();

int CevaReset();

int CevaBoot();
//int ZspLoad(char* ZSPFileName);

//int ZspBoot(char* ZSPFileName);

//int ZspLoad1(char* ZSPFileName);

//void downtxt(UINT32 des_addr, INT8 *FileName );

//int txt_cmp( UINT32 src_addr, INT8 *FileName );
