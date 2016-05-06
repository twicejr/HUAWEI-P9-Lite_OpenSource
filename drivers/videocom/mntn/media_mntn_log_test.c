
#include <linux/init.h>
#include <linux/module.h>

//#include <linux/media_mntn_kernel.h>
#include "media_mntn_kernel.h"
#include "media_mntn_test.h"

#define LOG_TAG                 "MNTN_LOG_TEST"


//////////////////////////////////////////////////

void mntn_print_level_test_func(void)
{
    bbit_log(" ====================== enter.");

    mntn_logd(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_set_print_level(MNTN_MODULE_ID_MNTN, MNTN_LOG_LEVEL_DEBUG);
    mntn_logd(MNTN_MODULE_ID_MNTN, " =======================");

    bbit_log(" ====================== exit.");
}

void mntn_log_test_func(void)
{
    bbit_log(" ====================== enter.");

    mntn_logd(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_logw(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_logi(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_loge(MNTN_MODULE_ID_MNTN, " =======================");

    printk(KERN_EMERG, "\n\n\n\n\n\n***************************************************\n\n\n\n\n\n");

    mntn_logd_time(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_logw_time(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_logi_time(MNTN_MODULE_ID_MNTN, " =======================");
    mntn_loge_time(MNTN_MODULE_ID_MNTN, " =======================");

    bbit_log(" ====================== exit.");
}

//////////////////////////////////////////////////

void mntn_save_file_test_func(void)
{
    bbit_log(" ====================== enter.");

    mntn_save_frame_data(MNTN_MODULE_ID_CAMERA, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_save_reg_data(MNTN_MODULE_ID_CAMERA, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ====================== exit.");
}

//////////////////////////////////////////////////

static __init int mntn_log_test_init(void)
{
    bbit_log(" ====================== enter.");
    printk(KERN_EMERG, "\n\n\n\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n\n\n\n");

    mntn_print_level_test_func();
    mntn_log_test_func();
    mntn_save_file_test_func();

    bbit_log(" ====================== exit.");
    return 0;
}

static void __exit mntn_log_test_exit(void)
{
    bbit_log(" ====================== enter.");

    printk(KERN_EMERG, "\n\n\n\n\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\n\n");

    bbit_log(" ====================== exit.");
}

MODULE_LICENSE("GPL");
module_init(mntn_log_test_init);
module_exit(mntn_log_test_exit);

