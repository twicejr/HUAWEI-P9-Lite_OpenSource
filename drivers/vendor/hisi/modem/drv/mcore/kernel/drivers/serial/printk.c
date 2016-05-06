
#include <stdarg.h>
#include <osl_types.h>
#include <osl_irq.h>
#include <osl_bio.h>
#include <bsp_hardtimer.h>
#include "serial_core.h"
#include "console.h"
#include "printk.h"	/*lint !e537*/
/*lint --e{530, 616, 718, 746} */
static unsigned int hex2asc(unsigned n)
{
    n &= 15;
    if(n > 9){
        return ('a' - 10) + n;
    } else {
        return '0' + n;
    }
}

static void xputs(const char *s, void (*xputc)(unsigned n, void *cookie), void *cookie)
{
    while (*s) {
        xputc(*s++, cookie);/*lint !e732*/
    }
}
/*lint -save -e744*/
void xprintf(const char *fmt, va_list ap,
               void (*xputc)(unsigned n, void *cookie),
               void *cookie)
{
    char scratch[16];

    for(;;){
        switch(*fmt){
        case 0:
            va_end(ap);
            return;
        case '%':
            switch(fmt[1]) {
            case 'c': {
                unsigned n = va_arg(ap, unsigned);/*lint !e732*/
                xputc(n, cookie);
                fmt += 2;
                continue;
            }
            case 'h': {
                unsigned n = va_arg(ap, unsigned);/*lint !e732*/
                xputc(hex2asc(n >> 12), cookie);
                xputc(hex2asc(n >> 8), cookie);
                xputc(hex2asc(n >> 4), cookie);
                xputc(hex2asc(n >> 0), cookie);
                fmt += 2;
                continue;
            }
            case 'b': {
                unsigned n = va_arg(ap, unsigned);/*lint !e732*/
                xputc(hex2asc(n >> 4), cookie);
                xputc(hex2asc(n >> 0), cookie);
                fmt += 2;
                continue;
            }                
            case 'p':
            case 'X':
            case 'x': {
                unsigned n = va_arg(ap, unsigned);/*lint !e732*/
                char *p = scratch + 15;
                *p = 0;
                do {
                    *--p = (char)hex2asc(n);
                    n = n >> 4; 
                } while(n != 0);
                while(p > (scratch + 7)) *--p = '0';
                xputs(p, xputc, cookie);
                fmt += 2;
                continue;
            }
            case 'd': {
                int n = va_arg(ap, int);
                char *p = scratch + 15;
                *p = 0;
                if(n < 0) {
                    xputc('-', cookie);
                    n = -n;
                }
                do {
                    *--p = (n % 10) + '0';
                    n /= 10;
                } while(n != 0);
                xputs(p, xputc, cookie);
                fmt += 2;
                continue;
            }
            case 's': {
                char *s = (char*)va_arg(ap, char*);
                if(s == 0) s = "(null)";
                xputs(s, xputc, cookie);
                fmt += 2;
                continue;
            }
			default:
				break;
            }
            xputc(*fmt++, cookie);/*lint !e732*/
			break;
		/* coverity[unterminated] */
        case '\n':
            xputc('\r', cookie);
        /* coverity[fallthrough] */
        default:
            xputc(*fmt++, cookie);/*lint !e732*/
            break;
        }
    }
}
/*lint -restore +e744*/
void printk(const char *fmt, ...)
{
    u32 flag;
    va_list ap;

    va_start(ap, fmt);
    local_irq_save(flag);/*lint !e732*/
    xprintf(fmt, ap, (void*)console_xput, 0);
    local_irq_restore(flag);
    va_end(ap);

    console_flush();
}

/*以下代码低功耗关中断后使用*/
static void uart_out(unsigned ch)
{
    struct uart_ldisc *ldisc = (struct uart_ldisc *)&g_console;
    
    uart_put_char(ldisc->port, (unsigned char)ch);
}

void printksync(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    xprintf(fmt, ap, (void*)uart_out, 0);
    va_end(ap);
}
