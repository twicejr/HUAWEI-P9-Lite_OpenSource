#include "osl_common.h"
#include "osl_thread.h"

#include "mdrv_rfile_common.h"

#include "bsp_shared_ddr.h"

#include "bsp_om.h"
#include "rfile_balong.h"
#include "bsp_hardtimer.h"
#include "efuse_balong.h"
#include "hi_efuse.h"

#define  test_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EFUSE, "[all]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))

#define SEEK_SET 0

struct task_struct *rfile_thread_id = NULL;

struct task_struct *efuse_thread_id = NULL;

unsigned int test_efuse_press_num = 0;
unsigned int test_rfile_press_num = 0;

#define RFILE_WR_DATA_LEN           8888
#define RFILE_RD_DATA_LEN           8880

#define MAX_TIME_MS_VALUE 1000

unsigned int ccore_efuse_send_time = 0;
unsigned int ccore_efuse_rev_time = 0;


void check_time(u32 start, u32 end)
{
    unsigned int diff = end - start;
    if(diff > MAX_TIME_MS_VALUE)
    {
        test_print_info("start %d , end %d.\n", start, end);

    }

}


s8 filepath[] = "/modem_log/rfile_test";
s8 wrbuf[] = "1234567wxyz";
s8 rdbuf[15] = "";

int rfile_test_000()
{
    s32 ret = 0;
    u32 pfile = 0;
    u32 start = 0;
    u32 end = 0;

    u32 wsize = (u32)strlen((const char *)wrbuf);

    start = bsp_get_elapse_ms();
    ret = bsp_open(filepath, (s32)(RFILE_CREAT|RFILE_RDWR), (s32)0755);
    end = bsp_get_elapse_ms();
    check_time(start, end);

    if(ret < 0)
    {
        test_print_info("!!!!!!!! bsp_open failed.\n");

        return -3;
    }

    pfile = (unsigned int)ret;

    start = bsp_get_elapse_ms();
    ret = bsp_lseek(pfile, 0, (int)SEEK_SET);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(BSP_OK != ret)
    {
        test_print_info("!!!!!!!! mdrv_file_seek 1 failed .\n");

        return -4;
    }

    start = bsp_get_elapse_ms();
    ret = bsp_write(pfile, wrbuf, wsize);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(ret != (int)wsize)
    {
        test_print_info("!!!!!!!! mdrv_file_write 1 failed .\n");

        return -5;
    }

    start = bsp_get_elapse_ms();
    ret = bsp_close(pfile);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(BSP_OK != ret)
    {
        test_print_info("!!!!!!!! bsp_close failed.\n");

        return -6;
    }

    /* 判断文件是否存在 */
    start = bsp_get_elapse_ms();
    ret = bsp_access(filepath, (int)0);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(BSP_OK != ret)
    {
        test_print_info("!!!!!!!! bsp_access failed.\n");

        return -7;
    }

    start = bsp_get_elapse_ms();
    pfile = bsp_open(filepath, (s32)(RFILE_CREAT|RFILE_RDWR), (s32)0755);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(pfile < 0)
    {
        test_print_info("!!!!!!!! bsp_open failed.\n");

        return -8;
    }

    start = bsp_get_elapse_ms();
    ret = bsp_lseek(pfile, 0, (int)SEEK_SET);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(ret < 0)
    {
        test_print_info("!!!!!!!! mdrv_file_seek 2 failed .\n");
        return -9;
    }

    start = bsp_get_elapse_ms();
    ret = bsp_read(pfile, rdbuf, wsize);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(ret != (int)wsize)
    {
        test_print_info("!!!!!!!! mdrv_file_read 1 failed .\n");

        return -10;
    }

    start = bsp_get_elapse_ms();
    ret = bsp_close(pfile);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(BSP_OK != ret)
    {
        test_print_info("!!!!!!!! bsp_close failed.\n");

        return -11;
    }

    return 0;
}

void efuse_test_000()
{
    s32 ret;

    u32 start = 0;
    u32 end = 0;

    u32 buf[EFUSE_HUK_SIZE] = {0};

    start = bsp_get_elapse_ms();
    ret = bsp_efuse_read(buf, EFUSE_GRP_HUK,EFUSE_HUK_SIZE);
    end = bsp_get_elapse_ms();
    check_time(start, end);
    if(0 != ret)
    {
        efuse_print_info("test fail.\n");

    }

}

void test_numm()
{
    efuse_print_info("efuse test %d, rfile test %d.\n", test_efuse_press_num, test_rfile_press_num);
}

int efuse_press_test(void* obj)
{
    while(1)
    {
        efuse_test_000();
        ++test_efuse_press_num;
        udelay(1000);

    }

    return 0;
}

int rfile_press_test(void* obj)
{
    while(1)
    {
        (void)rfile_test_000();

        ++test_rfile_press_num;
        udelay(1000);
    }

    return 0;

}

void rfile_thread_test()
{
    (void)kthread_run(rfile_press_test, BSP_NULL, "rfile_thread_task1");


}

void efuse_thread_test()
{
    (void)kthread_run(efuse_press_test, BSP_NULL, "efuse_thread_task2");

}
