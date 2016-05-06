

#ifndef __OSL_BIO_H
#define __OSL_BIO_H

static __inline__ void DMB(void)
{
    __asm__ __volatile__ ( "DMB;");
}

static __inline__ void nop(void)
{
    __asm__ __volatile__ ( "NOP;");
}

static __inline__ void writel(unsigned val, unsigned addr)
{
    DMB();
    (*(volatile unsigned *) (addr)) = (val);
    DMB();
}

static __inline__ unsigned readl(unsigned addr)
{
    DMB();
    return (*(volatile unsigned *) (addr));
}

#endif	/* __OSL_BIO_H */

