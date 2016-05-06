
#include <linux/init.h>
#include <linux/module.h>

//#include <linux/media_mntn_kernel.h>
#include "media_mntn_kernel.h"
#include "media_mntn_test.h"

#define LOG_TAG                 "MNTN_EXCH_TEST"

unsigned char           g_mntn_exch_buffer[EXCH_BUF_SIZE_MAX] = {0};
EXPORT_SYMBOL(g_mntn_exch_buffer);

// 2012-11-24
int mntn_exch_test_func(mntn_exch_cust_buf_t *drv_buf)
{
    bbit_log(" ======================= enter.");

    if (NULL == drv_buf) {
        bbit_log("================ exch buffer is NULL !!!!");

        // TODO: return value is changed !!!
        return 0;
    }
    memcpy(drv_buf->name, LOG_TAG, EXCH_CB_NAME_SIZE);
    drv_buf->data_len = EXCH_BUF_SIZE_MAX;

    drv_buf->data = g_mntn_exch_buffer;
    memcpy(drv_buf->data, g_buf_context_test, drv_buf->data_len);

    printk(" -------- drv_buf->name=%s.\n", drv_buf->name);
    printk(" -------- drv_buf->data_len=%d.\n", drv_buf->data_len);
    printk(" -------- drv_buf->data=%1024s.\n", drv_buf->data);

    // TODO: return value is changed !!!
    return EXCH_BUF_SIZE_MAX;
}
EXPORT_SYMBOL(mntn_exch_test_func);

static __init int mntn_exch_test_init(void)
{
    int ret_register = 0;

    bbit_log(" ======================= enter.");

    ret_register = mntn_exch_cb_register(MNTN_MODULE_ID_CAMERA, mntn_exch_test_func);
    if (ret_register == MNTN_OK) {
        bbit_log(" ================= mntn_exch_cb_register ok !");
    } else {
        bbit_log(" ================= mntn_exch_cb_register failure !");
    }
    return ret_register;
}

static void __exit mntn_exch_test_exit(void)
{
    bbit_log(" ===================== kmod exit.");
}

MODULE_LICENSE("GPL");
module_init(mntn_exch_test_init);
module_exit(mntn_exch_test_exit);


