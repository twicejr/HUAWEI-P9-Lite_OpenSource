/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
  文 件 名   : ltcov_ccore.c
  版 本 号   : 初稿
  作    者   : 杨光 00187525
  生成日期   : 2013年03月29日
  最近修改   :
  功能描述   : 通过HUTAF接口获取覆盖率数据，并写到文件中
  修改历史   :
  1.日    期   : 2013年03月29日
    作    者   : 杨光 00187525
    修改内容   : 创建文件
  2.日    期   : 2013年07月17日
    作    者   : 刘永鹏
    修改内容   : 修改为远程文件系统

*******************************************************************************/

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

/*****************************************************************************
 函 数 名  : ltcov_hutaf_save_ccore_data
 功能描述  : 获取V9R1版本C核覆盖率数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 函数运行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月29日
    作    者   : y00187525
    修改内容   : 新生成函数

*****************************************************************************/
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

