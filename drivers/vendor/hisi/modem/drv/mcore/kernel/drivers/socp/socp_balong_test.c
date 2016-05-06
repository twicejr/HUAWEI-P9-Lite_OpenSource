/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  socp_balong.c
*
*   作    者 :  y00171698
*
*   描    述 :  本文件主要完成socp通道的申请和配置，以及读写数据处理
*                     use on M3
*
*   修改记录 :  2013年6月1日  
*************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <osl_bio.h>
#include "socp_balong.h"
#include "om_balong.h"
#include "printk.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  M3_SOCP_ENC_SRC_LGTH  (32)
u32 aEncSrc[8] = {0x48495349, 0x00000018, 0x04030201, 0x00000064,
				  0x08070605, 0x0d0c0b0a, 0xc0c0c0c0, 0xc0c0c0c0};
void socp_m3_core()
{
	SOCP_BUFFER_RW_STRU sBuff;
	
	bsp_socp_get_write_buff(SOCP_ENCSRC_LPM3_BASE, &sBuff);

	/*printk("sBuff.pBuffer is 0x%x, sBuff.pRbBuffer is 0x%x\n", sBuff.pBuffer, sBuff.pRbBuffer);
	printk("sBuff.u32Size is 0x%x, sBuff.u32RbSize is 0x%x\n", sBuff.u32Size, sBuff.u32RbSize);*/

    if(sBuff.u32Size + sBuff.u32RbSize >= M3_SOCP_ENC_SRC_LGTH)
    {
        if(sBuff.u32Size >= M3_SOCP_ENC_SRC_LGTH)
        {
            memcpy((u8 *)sBuff.pBuffer, (u8 *)aEncSrc, M3_SOCP_ENC_SRC_LGTH);
        }
        else
        {
            memcpy((BSP_U8*)sBuff.pBuffer, (u8 *)aEncSrc, sBuff.u32Size);
            memcpy((BSP_U8*)sBuff.pRbBuffer, (u8 *)aEncSrc+sBuff.u32Size, M3_SOCP_ENC_SRC_LGTH-sBuff.u32Size);
        }
          		
        bsp_socp_write_done(SOCP_ENCSRC_LPM3_BASE, M3_SOCP_ENC_SRC_LGTH);
    } 
	
	/**/
}


void socp_m3_test(u32 u32Cnt)
{
	u32 u32TempCnt= u32Cnt;
	u32 i=0;

	bsp_socp_enable(SOCP_ENCSRC_LPM3_BASE);

	/* circle test */
	for(i=0;i<u32Cnt;i++)
	{
		socp_m3_core();
	}
}

void om_test_0(char *fmt)
{   
    u32 cnt = 77;
    
    om_switch_set(1);
    bsp_socp_enable(SOCP_ENCSRC_LPM3_BASE);

    bsp_trace(1,1,"here cnt is %d\n", cnt);
    bsp_trace(1,1,"here cnt is %s\n", cnt);
    bsp_trace(1,1,"here cnt is 0x%x\n", cnt);
}

void om_test_1(u32 para_num)
{   
    u32 tst_cnt= para_num;

    bsp_log_bin_ind(0x5221, &para_num, sizeof(u32));

    printk("the num is %d\n",tst_cnt);
}

#ifdef __cplusplus
}
#endif

/*lint +e506*/



