#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/smp.h>
#include <linux/poll.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>

unsigned int g_mem_size = 0;
unsigned int g_loop_times = 0;

void mem_thread(unsigned int size)
{
	unsigned char *src = NULL;
	unsigned char *dst = NULL;
	unsigned char *temp_src = NULL;
	unsigned char *temp_dst = NULL;
	unsigned char temp;
       dma_addr_t src_phy;
	dma_addr_t dst_phy;
	static unsigned int count = 0;
	int i;
	int this_cpu = smp_processor_id();

	if(count > 0xFFFFFFF0)
	{
		printk("count(0x%x) > 0xFFFFFFF0\n", count);
		count = 0;
	}
	
	/*printk("mem test begin count:%d cpu:%d!!!\n", count++, this_cpu);  */
	
	src = (unsigned char *)dma_alloc_coherent(NULL, size, &src_phy, GFP_KERNEL);
	if(NULL == src)
	{
		printk("alloc src mem failed!!! cpu:%d\n", this_cpu);
		return;
	}

	/*printk("src phy:0x%x virt:0x%x cpu:%d\r\n", src_phy, src, this_cpu);*/
	
	dst = (unsigned char *)dma_alloc_coherent(NULL, size, &dst_phy, GFP_KERNEL);;
	if(NULL == dst)
	{
		printk("alloc dst mem failed!!! cpu:%d\n", this_cpu);
		dma_free_coherent(NULL, size, src, src_phy);
		return;
	}
       /*printk("dst phy:0x%x virt:0x%x\r\n", dst_phy, dst);*/

       temp_src = src;
	   
	for(i = 0; i < size; i++)
	{
		if(((i ) % 4) < 2)
			*temp_src = 0x0;
		else
			*temp_src = 0xff;
		temp_src++;
		//memset(src, 0x5c, size);
		
	}
	
	memcpy(dst, src, size);

       /*printk("dst:0x%x 0x%x 0x%x 0x%x cpu:%d\n",*dst, *(dst + 1), *(dst + 2), *(dst + 3), this_cpu);*/

	temp_src = src;
	temp_dst = dst;
	  
	for(i = 0; i < size; i++)
	{
		/*if(0 != memcmp(dst, src, size))*/
		if(((i ) % 4) < 2)
			temp = 0x0;
		else
			temp = 0xff;
		
		if((*temp_src != *temp_dst) || (*temp_dst != temp))
	       {
	       	printk("ddr data error!!! dst:0x%x src:0x%x cpu:%d\n",*temp_dst, *temp_src, this_cpu);
			break;
		}

		temp_src++;
		temp_dst++;
	}

	if(i == size)
	{
		/*printk("mem test end pass!!! cpu:%d\n", this_cpu); */
	}

	dma_free_coherent(NULL, size, src, src_phy);
	dma_free_coherent(NULL, size, dst, dst_phy);
}

void bigmem_thread(unsigned int size)
{
	unsigned char *src = NULL;
	unsigned char *dst = NULL;
	static unsigned int count = 0;
	int i;
	int this_cpu = smp_processor_id();

	if(count > 0xFFFFFFF0)
	{
		printk("count(0x%x) > 0xFFFFFFF0\n", count);
		count = 0;
	}
	
	/*printk("bigmem test begin count:%d cpu:%d!!!\n", count++, this_cpu); */ 
	
	src = (unsigned char *)kmalloc(size, GFP_KERNEL);
	if(NULL == src)
	{
		printk("alloc src mem failed!!! cpu:%d\n", this_cpu);
		return;
	}

	/*printk("src virt:0x%x cpu:%d\r\n",  src, this_cpu);*/
	
	dst = (unsigned char *)kmalloc(size, GFP_KERNEL);
	if(NULL == dst)
	{
		printk("alloc dst mem failed!!! cpu:%d\n", this_cpu);
		kfree(src);
		return;
	}

       memset(src, 0x5c, size);
	memcpy(dst, src, size);
	/*printk("bigmem test endcpu:%d!!!\n", this_cpu);*/
	kfree(src);
	kfree(dst);
}


void bigmem_test(unsigned int size, unsigned int times)
{
	unsigned int i;
	int this_cpu = smp_processor_id();
	
	printk("bigmem test size:%d times:%d cpu:%d\n", size, times, this_cpu); 
	
	if(size < 4)
	{
		size = 4;
	}

	for(i = 0; i < times; i++)
	{
		bigmem_thread(size);
	}

	printk("bigmem test end cpu:%d\n", this_cpu); 
}

void mem_test(unsigned int size, unsigned int times)
{
	unsigned int i;
	int this_cpu = smp_processor_id();
	
	printk("mem test size:%d times:%d cpu:%d\n", size, times, this_cpu); 
	
	if(size < 4)
	{
		size = 4;
	}

	for(i = 0; i < times; i++)
	{
		mem_thread(size);
	}

	printk("mem test end cpu:%d\n", this_cpu); 
}

int mem_test_thread(void *arg)
{
	unsigned int i;
	
	for(i = 0; i < g_loop_times; i++)
	{
		bigmem_thread(g_mem_size);
	}
}
#if 1
void mem_test_multi(unsigned int thread_num, unsigned int size, unsigned int loop)
{
	int thread_id;
	int i;

	printk("mem_test_multi begin thread num:%d size:%d loop:%d...\n", thread_num, size, loop);

	g_loop_times = loop;
	g_mem_size = size;
	
	for(i = 0; i < thread_num; i++)
	{
		thread_id = kernel_thread(mem_test_thread, (void *)NULL, 0);
	    
	    	if (thread_id < 0) {
	        printk("create thread failed\n");
	        break;
	       }
	}		
	printk("mem_test_multi end\n");
}
#endif
