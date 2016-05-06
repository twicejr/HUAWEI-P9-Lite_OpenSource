


#include <huawei_platform/chipverification/chipverification.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <asm/io.h>
//#include <asm/sizes.h>
#include <linux/mm.h>
#include <linux/random.h>

#define Uart0BaseAddr      ioremap(0xF8015000 , PAGE_ALIGN(SZ_4K))
#define UartBaseAddr       ioremap(0xF7110000 , PAGE_ALIGN(SZ_4K*4))
#define Uart5BaseAddr      ioremap(0xFF030000 , PAGE_ALIGN(SZ_4K))
#define SIOBaseAddr        ioremap(0xF7118000 , PAGE_ALIGN(SZ_4K))

#define UartMaxNum	5
#define MaxNum 254

//#define HKADCSSIBaseAddr   ioremap(0xF7013000 , PAGE_ALIGN(SZ_1K))
//#define CODECSSIBaseAddr   ioremap(0xF7115000 , PAGE_ALIGN(SZ_1K))
#define PMUSSIBaseAddr     ioremap(0xF8000000 , PAGE_ALIGN(SZ_1K))

struct Register_Info
{
	u32 Offset;
	u32 Mask;
};
static u32 gChipVerificationDebug = 0;


u32 Chip_Verification_Set_Debug(u32 DebugFlag)
{
	gChipVerificationDebug = DebugFlag;
	printk(KERN_NOTICE "Set gChipVerificationDebug as %d \n", gChipVerificationDebug);
	return CHIP_VERIFICATION_DEBUG_SUCCESS;
}

u32 Chip_Verification_Get_Debug(void)
{
	printk(KERN_NOTICE "Get gChipVerificationDebug : %d \n", gChipVerificationDebug);
	return gChipVerificationDebug;
}


bool Chip_Verification_Check_Debug(u32  ModuleFlag)
{
	bool bRtn = false;
	u32 temp = (ModuleFlag & gChipVerificationDebug);

	bRtn = (temp > 0) ? true : false;

	//printk(KERN_NOTICE "Chip_Verification_Check_Debug(Module:%d) return %d \n", ModuleFlag, bRtn,"\n");

	return bRtn;
}

bool Chip_Verification_Uart_LB_Test(u32 UartIndex, u8 TxData, u32 times)
{

	u8 RxData = 0;
	u32 RxErrCount =0;
	void * UartVirtAddr = NULL;
	u32 DataCmdOffset = 0;
	u32 UartCtrlLbeStartBit = 7;
	u32 Uart0clkStartBit = 24;
	u32 UartclkStartBit = 5;
	u32 UartRxStartBit = 9;
	u32 UartTxStartBit = 8;
	u32 UartEnableoffset = 0x030;
	u32 ret = 1;
	u32 Uart0Currentclk = 0;
	u32 Uart0data = 0;
	u32 UartCurrentclk = 0;
	u32 Uartdata = 0;
	void * UartAddr =NULL;
	u16 CurrentData = 0;
	u16 data = 0;


	u32 i = 0;
	u8 TxDataFlag = TxData;

	void * Uart0ClkEnableAddr = (void *) ioremap(0xF7800630 , PAGE_ALIGN(SZ_1));
	void * Uart0ClkStatAddr = (void *) ioremap(0xF7800638 , PAGE_ALIGN(SZ_1));
	void * UartClkEnableAddr =  (void *) ioremap(0xF7030230 , PAGE_ALIGN(SZ_1));
	void * UartClkStatAddr =  (void *) ioremap(0xF7030238 , PAGE_ALIGN(SZ_1));

	if(0 == UartIndex)
	{
		UartVirtAddr = (void *)Uart0BaseAddr;
	}else if(UartMaxNum == UartIndex)
	{
		UartVirtAddr = (void *) Uart5BaseAddr;
	}
	else
	{
		UartVirtAddr = (void *) UartBaseAddr + (0x1000 * UartIndex);
	}


/*	void __iomem *UartBaseAddr;
	UartBaseAddr  = ioremap(UartBasePhyAddr[UartIndex], resource_size(&dev->res));
	if (!base) {
		ret = -ENOMEM;
		goto free;
	}
*/

	if(UartIndex >= UartMaxNum)
	{
		printk(KERN_ERR "%s (UartIndex %d error) \n", __FUNCTION__, UartIndex);
		return false;
	}

	//call Chip_Verification_Set_Debug
	ret = Chip_Verification_Set_Debug(CHIP_VERIFICATION_UART_DEBUG);
	if (ret != 0)
	{
		printk(KERN_ERR "%s (UartIndex _Set_Debug   error) \n", __FUNCTION__);
		return false;
	}

	//configure the uart clock
	if (0 == UartIndex )
	{
		Uart0Currentclk = readl((volatile void *) Uart0ClkStatAddr);
		Uart0data = 1 << Uart0clkStartBit;
		Uart0data = Uart0data |Uart0Currentclk;
		writel(Uart0data,(volatile void *) Uart0ClkEnableAddr);
	}
	else
	{
		UartCurrentclk = readl((volatile void *) UartClkStatAddr);
		Uartdata = 1 << (UartclkStartBit + UartIndex -1);
		Uartdata = Uartdata |UartCurrentclk;
		writel(Uartdata,(volatile void *) UartClkEnableAddr);
	}
	// uart should be configured in loopback mode
	UartAddr = UartVirtAddr + UartEnableoffset;
	CurrentData = readw((volatile void *) UartAddr);
	data = (1 << UartCtrlLbeStartBit) | (1<<UartRxStartBit) | (1 << UartTxStartBit) |(1);
	data = data | CurrentData;
	writew(data, (volatile void *) UartAddr);

	//secondly, loop test write/read

	UartAddr = UartVirtAddr + DataCmdOffset;

	for(i = 0; i < times; i++)
	{
		writew(TxData, (volatile void *) UartAddr);
		printk(KERN_NOTICE "%s(TxData:%#x)\n",__FUNCTION__,TxData);
              RxData = 0;
		RxData = readw((volatile void *) UartAddr );
		printk(KERN_NOTICE "%s(RxData:%#x)\n",__FUNCTION__,RxData);

		if(TxData != RxData)
		{
			RxErrCount++;
		}
		TxData++;
		if (MaxNum <= TxData)
		{
		TxData = TxDataFlag;
		}
	}
	//writew(TxData, UartAddr);

	UartAddr = UartVirtAddr + UartEnableoffset;
	writew(CurrentData, (volatile void *) UartAddr);

	printk(KERN_NOTICE "%s(%u,%d,%u) RxErrCount:%u \n", __FUNCTION__, UartIndex, TxData, times, RxErrCount);

	return (0 == RxErrCount) ? true : false;

}

bool Chip_Verification_Uart_Tx_Test(u32 UartIndex, u8 TxData, u32 times)
{
	u32 DataCmdOffset = 0;
	u32 i = 0;
	void * UartAddr = NULL;
	void *  UartVirtAddr = NULL;

	if(0 == UartIndex)
	{
		UartVirtAddr = (void *) Uart0BaseAddr;
	}else if(UartMaxNum == UartIndex)
	{
		UartVirtAddr = (void *) Uart5BaseAddr;
	}
	else
	{
		UartVirtAddr = (void *) UartBaseAddr + (0x1000 * UartIndex);
	}


	if(UartIndex >=  UartMaxNum )
	{
		printk(KERN_ERR "Chip_Verification_UART_LB_Test error UartIndex\n");
		return false;
	}
		
	UartAddr = UartVirtAddr+ DataCmdOffset;

	for( i = 0; i < times; i++)
	{
		writew(TxData, (volatile void *)UartAddr);
	}

	printk(KERN_NOTICE "%s(%u,%d,%u) \n", __FUNCTION__, UartIndex, TxData, times);
	return  true;
}

bool Chip_Verification_SIO_LB_Test(u32 SIOBusIndex, u32 SIOTxData, u32 times)
{
	u32 SIORxDataRegOffset = 0xFC;
	u32 SIOTxDataRegOffset = 0xF0;

	u32 i = 0;

	u32 SIORxData = 0;
	u32 SIORxErrCount =0;

	const u32 RandomFlag = 2; 

	const u32 SIOBusCountMax = 4;
	const u32 SIOBusCountMin = 1;
	
	void * SIOTxDataAddr = NULL;
	void *  SIORxDataAddr =NULL ;

	if(SIOBusIndex >= SIOBusCountMax || SIOBusIndex < SIOBusCountMin)
	{
		printk(KERN_ERR "%s (SIOBusIndex %d error) \n", __FUNCTION__, SIOBusIndex);
		return false;
	}

   /*write data*/
	SIOTxDataAddr =  (void *)SIOBaseAddr + SIOTxDataRegOffset;
	SIORxDataAddr =  (void *)SIOBaseAddr + SIORxDataRegOffset;

	for(i = 0; i < times; i++)
	{
		if(RandomFlag == SIOTxData)
		{
			SIOTxData = prandom_u32();
		}
		writew(SIOTxData, (volatile void *)SIOTxDataAddr);
		printk(KERN_NOTICE "%s(SIOTxData:%#x)\n",__FUNCTION__,SIOTxData);
		SIORxData = 0;
		SIORxData = readw((volatile void *)SIORxDataAddr);
		printk(KERN_NOTICE "%s(SIORxData:%#x)\n",__FUNCTION__,SIORxData);

		if(SIORxData != SIOTxData)
		{
			SIORxErrCount++;
		}
	}
	printk(KERN_NOTICE "%s(%u,%d,%u) SIORxErrCount:%u \n", __FUNCTION__, SIOBusIndex, SIOTxData, times, SIORxErrCount);
	return true;
}

bool Chip_Verification_SSI_Test(u32 times)
{
	//const u32 HKADCCount =  2;
	//const u32 CODECCount = 9;
	const u32 PMUCount = 9;

	//struct Register_Info HKADCReg[2] = {{0x06, 0xFF}, {0x09, 0xFF}};
	//struct Register_Info CODECReg[9] = {{0x1B7, 0x3F}, {0x1B8, 0x3F}, {0x1C6, 0xFF}, {0x1C7, 0xFF}, {0x1C8, 0xFF}, {0x1C9, 0xFF}, {0x1CB, 0xFF}, {0x1CC, 0xFF}, {0x1CD, 0xFF}};
	struct Register_Info PMUReg[9] = {{0x08C, 0x3F}, {0x08E, 0xFF}, {0x08F, 0xFF}, {0x090, 0xFF}, {0x099, 0x3F}, {0x092, 0x1F}, {0x094, 0x77}, {0x098, 0x07}, {0x09E, 0x07}};

	u8 SSITxData = 0;
	u8 SSIRxData = 0;
	u32 SSIRxErrCount =0;

	void *  SSIRegAddr = NULL;
	int i = 0;
	int j = 0;
	/*
	for(i = 0; i < HKADCCount; i ++)
	{
	    SSIRegAddr = HKADCSSIBaseAddr + HKADCReg[i].Offset;
		printk(KERN_NOTICE "%s(HKADC SSI SSIRegAddr:%#x)\n",__FUNCTION__,SSIRegAddr);
		SSIRxErrCount = 0;
		for(j = 0; j < times; j ++)
		{
			SSITxData = prandom_u32() & HKADCReg[i].Mask;

			writew(SSITxData, SSIRegAddr);
			printk(KERN_NOTICE "%s(SSITxData:%#x)\n",__FUNCTION__,SSITxData);
			SSIRxData = 0;
			SSIRxData = readw(SSIRegAddr);
			printk(KERN_NOTICE "%s(SSIRxData:%#x)\n",__FUNCTION__,SSIRxData);

	        if(SSIRxData != SSITxData)
	    	{
	    	   SSIRxErrCount++;
	    	}
		}
		printk(KERN_NOTICE "%s(%u) HKADC SSI %d SSIRxErrCount:%u \n", __FUNCTION__, times, i, SSIRxErrCount);

	}

	for(i = 0; i < CODECCount; i ++)
	{
	    SSIRegAddr = CODECSSIBaseAddr + CODECRegOffset[i];
		printk(KERN_NOTICE "%s(CODEC SSI SSIRegAddr:%#x)\n",__FUNCTION__,SSIRegAddr);
		for(j = 0; j < times; j ++)
		{
			SSITxData = prandom_u32();

			writew(SSITxData, SSIRegAddr);
			printk(KERN_NOTICE "%s(SSITxData:%#x)\n",__FUNCTION__,SSITxData);
			SSIRxData = 0;
			SSIRxData = readw(SSIRegAddr);
			printk(KERN_NOTICE "%s(SSIRxData:%#x)\n",__FUNCTION__,SSIRxData);

	        if(SSIRxData != SSITxData)
	    	{
	    	   SSIRxErrCount++;
	    	}
		}
		printk(KERN_NOTICE "%s(%u) CODEC SSI %d SSIRxErrCount:%u \n", __FUNCTION__, times, i, SSIRxErrCount);
	}
    */
	for(i = 0; i < PMUCount; i ++)
	{
		 SSIRegAddr =  (void *)PMUSSIBaseAddr + (PMUReg[i].Offset << 2);
		SSIRxErrCount = 0;
		printk(KERN_NOTICE "%s(PMU SSI SSIRegAddr:%p)\n",__FUNCTION__,SSIRegAddr);
		for(j = 0; j < times; j ++)
		{
			SSITxData = prandom_u32() & PMUReg[i].Mask;

			writew(SSITxData, (volatile void *)SSIRegAddr);
			printk(KERN_NOTICE "%s(SSITxData:%#x)\n",__FUNCTION__,SSITxData);
			SSIRxData = 0;
			SSIRxData = readw((volatile void *)SSIRegAddr);
			SSIRxData &= PMUReg[i].Mask;
			printk(KERN_NOTICE "%s(SSIRxData:%#x)\n",__FUNCTION__,SSIRxData);

			if(SSIRxData != SSITxData)
			{
				SSIRxErrCount++;
	    		} 
		}
		printk(KERN_NOTICE "%s(%u) PMU SSI %d SSIRxErrCount:%u \n", __FUNCTION__, times, i, SSIRxErrCount);
	}
	return true;
}
