#ifndef _CPUBUFFER_ALLOC_H_
#define _CPUBUFFER_ALLOC_H_

#include <linux/genalloc.h>
#include <linux/list.h>

enum{
    SPLIT_MODE_NULL = 0x0,
    SPLIT_MODE_W,
    SPLIT_MODE_H
};

typedef struct cpubuf_handle_t{
    unsigned long phy_addr;
    int bytew;  			//  256 bytes aligned
    int byteh;  			//  16 pixel aligned
    int stride;

    int size;                      //only for ref = 0 node
    void *thisnode; 	      //only for free
}cpubuf_handle_t;

typedef struct mem_node_t{
    struct list_head node_head;
    struct mem_node_t *thisnode;
    struct mem_node_t *father;
    unsigned int ref;

    cpubuf_handle_t cpubuf;
}mem_node_t;

void  memlist_init(void);
void memlist_dump(void);
unsigned long cpubuffer_alloc(struct gen_pool *pool, int size, int bytew, int byteh);
int  cpubuffer_free(struct gen_pool *pool, unsigned long phy_addr);


#endif  //_CPUBUFFER_ALLOC_H_
