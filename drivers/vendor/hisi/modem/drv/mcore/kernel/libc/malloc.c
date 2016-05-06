#include <libc.h>
#include <osl_common.h>

void printk(const char *fmt, ...);

#define MALLOC_MEM_SIZE  1024
#define MALLOC_MEM_ALIGN 32
static unsigned char g_malloc_data[MALLOC_MEM_SIZE + MALLOC_MEM_ALIGN] ={0}; /* ¿¼ÂÇ16byte¶ÔÆë */
static unsigned int __alloc_start = (unsigned int)(&g_malloc_data[0]);
static unsigned int __alloc_end   = (unsigned int)(&g_malloc_data[MALLOC_MEM_SIZE + MALLOC_MEM_ALIGN - 1]);

void *malloc(unsigned int sz)
{
	void *ptr;

	if(__alloc_start == 0)
	{
		printk("malloc __alloc_start=0\n");
		return NULL;
	}
	ptr = (void*) __alloc_start;
	__alloc_start = (__alloc_start + sz + MALLOC_MEM_ALIGN) & (~MALLOC_MEM_ALIGN);
	if(__alloc_start > __alloc_end)
	{
		printk("malloc error: no memory\n");
		return NULL;
	}

	return ptr;
}


void free(void * addr)
{
	addr = addr;
}


