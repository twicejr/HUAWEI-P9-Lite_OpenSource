#define _ASMLANGUAGE
    .text
    .global   regcpy

regcpy:
    push    {r4,lr}
    mvn     r4,#0x3
    ands    r0,r0,r4
    ands    r1,r1,r4
    ands    r2,r2,r4
    add     r3,r1,r2

_do_reg_cpy:
    cmp     r1,r3
    bcs     _do_reg_cpy_end
    ldr     r4,[r1]
    str     r4,[r0]
    add     r0,r0,#0x4
    add     r1,r1,#0x4
    b       _do_reg_cpy

_do_reg_cpy_end:
    pop     {r4,pc}

