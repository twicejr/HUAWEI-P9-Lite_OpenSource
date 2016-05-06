

#ifndef _MEM_H_
#define _MEM_H_

#include "teek_ns_client.h"

int tc_mem_init(void);
void tc_mem_destroy(void);

TC_NS_Shared_MEM *tc_mem_allocate(TC_NS_DEV_File *dev, size_t len);
int tc_mem_free(TC_NS_Shared_MEM *shared_mem);


#endif
