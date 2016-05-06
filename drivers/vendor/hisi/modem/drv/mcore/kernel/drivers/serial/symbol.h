
#ifndef __M_SYMBOL_H__
#define __M_SYMBOL_H__

struct symbol       
{
    char        *name;          /* pointer to symbol name */
    unsigned long value;         /* symbol value */
};

/* TODO: 建议后续挪到osl_common.h类似的OSL层次 */
#ifndef ROUND_UP 
#define ROUND_UP(x, align)	    (((int) (x) + (align - 1)) & ~(align - 1))
#endif

#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align)	((int)(x) & ~(align - 1))
#endif

#endif
