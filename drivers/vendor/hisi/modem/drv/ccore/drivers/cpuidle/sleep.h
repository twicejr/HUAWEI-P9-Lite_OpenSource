#ifndef __SLEEP_BALONG_H__
#define __SLEEP_BALONG_H__


#define _asm_function_called_from_c(a) \
    .globl a ;\
    .code  32 ;\
    .balign 4 ;\
a:

#endif

