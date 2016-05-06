#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <product_config.h>

#ifdef CONFIG_TEMPERATURE_PROTECT

int tem_protect_init(void);

s32 tem_protect_suspend(void);

void tem_protect_resume(void);

#else

static inline int tem_protect_init(void)
{
    return 0;
}

static inline s32 tem_protect_suspend(void)
{
    return 0;
}

static inline void tem_protect_resume(void)
{
    return ;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
