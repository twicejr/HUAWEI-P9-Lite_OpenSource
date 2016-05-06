
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/delay.h>

//#include <linux/media_mntn_kernel.h>
#include "media_mntn_kernel.h"
#include "media_mntn_test.h"

#define LOG_TAG         "MNTN_SDT_TEST"
#define MAX_TIMES       65535

static int timeout = 30;
static int repeat = 5;

static int all	  = 0;
static int camera = 1;

static int dec	= 0;
static int enc	= 0;
static int vpp	= 0;
static int edc	= 0;
static int gpu	= 0;
static int hdmi	= 0;

static const char *usage = "Usage:				\
insmod: set which module(s) will be execute			\
rmmod:  execute sdt						\
param (for insmod):						\
    all | dec | enc | vpp | camera | edc | gpu | hdmi 		\
eg:								\
    insmod xxx.ko all=1						\
    insmod xxx.ko camera=1 gpu=1				\
";

void mntn_sdt_dec_test_func(void)
{
    bbit_log(" ================================= 111111111111111111111111111111111 enter.");

    mntn_send_event_msg     (ID_DEC_EVENT_IND,      MNTN_MODULE_ID_DEC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_DEC_REG_IND,        MNTN_MODULE_ID_DEC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_DEC_FRAME_INFO_IND, MNTN_MODULE_ID_DEC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_DEC_CONTEXT_IND,    MNTN_MODULE_ID_DEC, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 111111111111111111111111111111111 exit.");
}

void mntn_sdt_enc_test_func(void)
{
    bbit_log(" ================================= 222222222222222222222222222222222 enter.");

    mntn_send_event_msg     (ID_ENC_EVENT_IND,      MNTN_MODULE_ID_ENC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_ENC_REG_IND,        MNTN_MODULE_ID_ENC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_ENC_FRAME_INFO_IND, MNTN_MODULE_ID_ENC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_ENC_CONTEXT_IND,    MNTN_MODULE_ID_ENC, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 222222222222222222222222222222222 exit.");
}

void mntn_sdt_vpp_test_func(void)
{
    bbit_log(" ================================= 333333333333333333333333333333333 enter.");

    mntn_send_event_msg     (ID_VPP_EVENT_IND,      MNTN_MODULE_ID_VPP, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_VPP_REG_IND,        MNTN_MODULE_ID_VPP, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_VPP_FRAME_INFO_IND, MNTN_MODULE_ID_VPP, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_VPP_CONTEXT_IND,    MNTN_MODULE_ID_VPP, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 333333333333333333333333333333333 exit.");
}

void mntn_sdt_camera_test_func(void)
{
    bbit_log(" ================================= 444444444444444444444444444444444 enter.");

    mntn_send_event_msg     (ID_CAMERA_EVENT_IND,      MNTN_MODULE_ID_CAMERA, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_CAMERA_REG_IND,        MNTN_MODULE_ID_CAMERA, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_CAMERA_FRAME_INFO_IND, MNTN_MODULE_ID_CAMERA, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_CAMERA_CONTEXT_IND,    MNTN_MODULE_ID_CAMERA, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 444444444444444444444444444444444 exit.");
}

void mntn_sdt_edc_test_func(void)
{
    bbit_log(" ================================= 555555555555555555555555555555555 enter.");

    mntn_send_event_msg     (ID_EDC_EVENT_IND,      MNTN_MODULE_ID_EDC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_EDC_REG_IND,        MNTN_MODULE_ID_EDC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_EDC_FRAME_INFO_IND, MNTN_MODULE_ID_EDC, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_EDC_CONTEXT_IND,    MNTN_MODULE_ID_EDC, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 555555555555555555555555555555555 exit.");
}

void mntn_sdt_gpu_test_func(void)
{
    bbit_log(" ================================= 666666666666666666666666666666666 enter.");

    mntn_send_event_msg     (ID_GPU_EVENT_IND,      MNTN_MODULE_ID_GPU, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_GPU_REG_IND,        MNTN_MODULE_ID_GPU, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_GPU_FRAME_INFO_IND, MNTN_MODULE_ID_GPU, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_GPU_CONTEXT_IND,    MNTN_MODULE_ID_GPU, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 666666666666666666666666666666666 exit.");
}

void mntn_sdt_hdmi_test_func(void)
{
    bbit_log(" ================================= 777777777777777777777777777777777 enter.");

    mntn_send_event_msg     (ID_HDMI_EVENT_IND,      MNTN_MODULE_ID_HDMI, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_reg_msg       (ID_HDMI_REG_IND,        MNTN_MODULE_ID_HDMI, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_frame_info_msg(ID_HDMI_FRAME_INFO_IND, MNTN_MODULE_ID_HDMI, g_buf_context_test, EXCH_BUF_SIZE_MAX);
    mntn_send_context_msg   (ID_HDMI_CONTEXT_IND,    MNTN_MODULE_ID_HDMI, g_buf_context_test, EXCH_BUF_SIZE_MAX);

    bbit_log(" ================================= 777777777777777777777777777777777 exit.");
}

void mntn_sdt_test_func(void)
{
    int i = 0;
    bbit_log(" +++++++++++++++++++++++++++++++++++++++ enter.");

    if (repeat <= 0) {
        repeat = MAX_TIMES;
    }

    printk(" ---------------- repeat times: %d\n", repeat);
    for (i=0; i<repeat; i++ ) {
        if (dec == 1 || all == 1) {
            mntn_sdt_dec_test_func();       msleep(timeout);
        }
        if (enc == 1 || all == 1) {
            mntn_sdt_enc_test_func();       msleep(timeout);
        }
        if (vpp == 1 || all == 1) {
            mntn_sdt_vpp_test_func();       msleep(timeout);
        }
        if (camera == 1 || all == 1) {
            mntn_sdt_camera_test_func();    msleep(timeout);
        }
        if (edc == 1 || all == 1) {
            mntn_sdt_edc_test_func();       msleep(timeout);
        }
        if (gpu == 1 || all == 1) {
            mntn_sdt_gpu_test_func();       msleep(timeout);
        }
        if (hdmi == 1 || all == 1) {
            mntn_sdt_hdmi_test_func();      msleep(timeout);
        }

        printk("\n\n\n\n"); 		ssleep(3);
    };

    bbit_log(" +++++++++++++++++++++++++++++++++++++++ exit.");
}

static int __init mntn_sdt_test_init(void)
{
    int ret = MNTN_OK;
    bbit_log(" ===================== enter.");
    ret = mntn_set_print_level(MNTN_MODULE_ID_MNTN, MNTN_LOG_LEVEL_DEBUG);
    printk("%s\n", usage);
    bbit_log(" ===================== exit.");
    return ret;
}

static void __exit mntn_sdt_test_exit(void)
{
    bbit_log(" ===================== enter.");
    mntn_sdt_test_func();
    bbit_log(" ===================== exit.");
}

MODULE_LICENSE("GPL");
module_param(timeout, int, S_IRUGO);
module_param(repeat, int, S_IRUGO);
module_param(all, int, S_IRUGO);
module_param(enc, int, S_IRUGO);
module_param(dec, int, S_IRUGO);
module_param(vpp, int, S_IRUGO);
module_param(camera, int, S_IRUGO);
module_param(edc, int, S_IRUGO);
module_param(gpu, int, S_IRUGO);
module_param(hdmi, int, S_IRUGO);
module_init(mntn_sdt_test_init);
module_exit(mntn_sdt_test_exit);

