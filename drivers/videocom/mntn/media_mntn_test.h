
#ifndef __MEDIA_MNTN_TEST_H_
#define __MEDIA_MNTN_TEST_H_

#define EXCH_BUF_SIZE_MAX   (8192)

#define bbit_log(fmt, ...)     \
		printk(KERN_EMERG "[[" LOG_TAG "]] %s:%d " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);

 unsigned char     *g_buf_context_test = (unsigned char *) "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\
    ===================================================================================================================================\
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

#endif  /* __MEDIA_MNTN_TEST_H_ */

