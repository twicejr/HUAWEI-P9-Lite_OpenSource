#ifndef  __PM_LOG_CAT_H__
#define  __PM_LOG_CAT_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "modem_log_cat.h"
void pmom_cat(struct modem_logger *logger, ssize_t *left_size);

#ifdef __cplusplus
}
#endif

#endif   /* __PM_LOG_CAT_H__ */

