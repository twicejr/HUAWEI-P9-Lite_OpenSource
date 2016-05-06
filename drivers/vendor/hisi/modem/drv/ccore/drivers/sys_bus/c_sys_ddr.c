#include <osl_malloc.h>
#include <securec.h>
#include <osl_cache.h>
#include <c_sys_bus_core.h>
#include <c_sys_bus_pressure.h>
#include <c_sys_ddr.h>

u32 g_ddrtaskrun;
u32 g_memtaskid;
u32 g_s32TestSence;
bus_mem_str g_bus_mem = {0};

static int memcpyTestProcess(unsigned int uiSrc,unsigned int uiDst,int iSize)
{
	memset_s((void*)uiSrc,iSize,rand(),iSize);
	memset_s((void*)uiDst,iSize,0,iSize);
	memcpy_s((void*)uiDst,iSize,(void*)uiSrc,iSize);
	return 0;
}
int sys_mem_task(void *data)
{

	g_bus_mem.u32Src = (u32)osl_cachedma_malloc(g_bus_mem.s32Size);
	if(0 == g_bus_mem.u32Src)
	{
		sys_bus_trace("%s buffer fail\n","src");
		return ERROR;
	}
	
	g_bus_mem.u32Dst = (u32)osl_cachedma_malloc(g_bus_mem.s32Size);
	if(0 == g_bus_mem.u32Dst)
	{
		sys_bus_trace("%s buffer fail\n","dst");
		free((void*)g_bus_mem.u32Src);
		return ERROR;
	}

	while(g_ddrtaskrun)
	{
		memcpyTestProcess(g_bus_mem.u32Src, g_bus_mem.u32Dst, g_bus_mem.s32Size);
		osl_task_delay(2);
	}
	return OK;
}
void sys_mem_start(struct master* master)
{
	g_ddrtaskrun = 1;
	if(ERROR == osl_task_init("sys_ddr", 51, 2000 ,(void *)sys_mem_task, NULL, &g_memtaskid))
    {
        sys_bus_trace("task init error\n");
		return;
    }
	sys_bus_trace("mem test start\n");
}

void sys_mem_stop(struct master* master)
{
	g_ddrtaskrun = 0;
	while(OK == osl_task_check(g_memtaskid))
   	{
		osl_task_delay(10);
	}
	osl_task_delete(&g_memtaskid);
	free((void*)g_bus_mem.u32Src);
	free((void*)g_bus_mem.u32Dst);
	
	sys_bus_trace("mem test stop\n");
}

void sys_mem_init(struct master* master)
{
	master->start = sys_mem_start;
    master->stop = sys_mem_stop;
    master->record = NULL;
    master->report = NULL;

	g_bus_mem.s32Size = A9_DATA_CACHE_SIZE;

	sys_bus_trace("ok\n");
}

