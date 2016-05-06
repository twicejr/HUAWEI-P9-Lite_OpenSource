#ifndef _BSP_XMAILBOX_H_
#define _BSP_XMAILBOX_H_

#ifdef __cplusplus
extern "C" {
#endif
#ifdef FEATURE_CPHY_MAILBOX
extern void bsp_xmailbox_init(void);
extern void bsp_xmailbox_set_dtcmAddr(unsigned long addr);
#else
static inline void bsp_xmailbox_init(void) {
}

static inline void bsp_xmailbox_set_dtcmAddr(unsigned long addr) {
}
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */
