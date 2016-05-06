#include "../rasbase/rasbase.h"
#include "rasproc.h"

int proc_init(char *name , struct file_operations *proc_ops, void *data)
{
	struct proc_dir_entry* pde = 0;
	if(name == 0  ) ras_retn(-ENOMEM);

	pde = proc_create_data(name, S_IFREG | 0666, 0, proc_ops, data);
	if(unlikely(0 == pde))	ras_retn(-ENOMEM);
	return 0;
}

void proc_exit(const char* name)
{
	remove_proc_entry(name, 0);
}
