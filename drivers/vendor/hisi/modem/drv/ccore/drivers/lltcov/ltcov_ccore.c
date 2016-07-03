

/*******************************************************************************
  1 头文件包含
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drv_comm.h"
#include "osl_types.h"
#include "bsp_rfile.h"

/*******************************************************************************
  3 函数声明
*******************************************************************************/
extern unsigned long HLLT_Agent_GetCovDataSize();
extern int HLLT_Coverage_GetCoverageData(unsigned int *pCovData, unsigned long ulLen);

/*******************************************************************************
  4 函数实现
*******************************************************************************/


s32 ltcov_hutaf_save_ccore_data(void)
{
	s32 fp;	       /* stream to read from*/
	u32 len = 0;
	s8* p_buffer = NULL;
	s8* filepath = "/data/ltcov_ccore.bin";
    s32 ret = 0;

    /* 判断文件是否存在,如果存在则删除 */
    ret = bsp_access(filepath, 0);
    if(BSP_OK == ret)
    {
        bsp_remove(filepath);
    }

	fp = bsp_open(filepath, (RFILE_CREAT|RFILE_RDWR), 0755);
	if (fp < 0)
	{
		printf("ltcov_hutaf_save_ccore_data:open file ERROR!\n");
		return -1;
	}

	/* len以字节为单位 */
	len = HLLT_Agent_GetCovDataSize();
	if (0 == len)
	{
		printf("ltcov_hutaf_save_ccore_data:HLLT_Agent_GetCovDataSize ERROR!\n");
        fclose(fp);
		return -1;
	}

	p_buffer = malloc(len);
	if(NULL == p_buffer)
    {
        printf("ltcov_hutaf_save_ccore_data:malloc failed\n");
        fclose(fp);
		return -1;
    }

	/* 将覆盖率数据写到Buffer中 */
	if(1 != HLLT_Coverage_GetCoverageData(p_buffer, len))
	{
		printf("ltcov_hutaf_save_ccore_data:HLLT_Coverage_GetCoverageData failed\n");
	    free(p_buffer);
        fclose(fp);
		return -1;
	}

    /*ret = bsp_lseek(fp, 0, SEEK_SET);
    if(BSP_OK != ret)
    {
        printf("!!!!!!!! mdrv_file_seek 1 failed .\n");

        return;
    }*/

	/* 写文件 */
    ret = bsp_write(fp, p_buffer, len);
    if(len != ret)
    {
        printf("ltcov_hutaf_save_ccore_data:bsp_write 1 failed.\n");

        return -1;
    }
    bsp_close(fp);
	fp = NULL;

	free(p_buffer);

	printf("ltcov_hutaf_save_ccore_data: success\n");
	return 0;
}

