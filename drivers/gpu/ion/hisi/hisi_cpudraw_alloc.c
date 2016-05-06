#include <linux/types.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/mutex.h>

#include "hisi_cpudraw_alloc.h"

#define KERNEL_DEBUG

#if defined(KERNEL_DEBUG)
#define ALOGD(format, arg...) pr_info("[cpubuffer] " format, ##arg);
#define ALOGD_INFO(format, arg...)  pr_info("[cpubuffer] " format, ##arg);
#else
#define ALOGD(format, arg...)
#define ALOGD_INFO(format, arg...)
#endif

static struct list_head idlenode_list;
static struct list_head allocatednode_list;
static struct mutex list_lock;



static int get_split_mode(mem_node_t * node, int bytew, int byteh)
{
	int split_mode;

	if(bytew <  node->cpubuf.bytew){
		split_mode = SPLIT_MODE_W;
	}else if(byteh <= node->cpubuf.byteh){
		split_mode = SPLIT_MODE_H;
	}else{
		split_mode = SPLIT_MODE_NULL;
	}

	ALOGD_INFO("cpubuffer info:split_mode=%d\n", split_mode);
	return split_mode;
}

void memlist_dump(void)
{
	mem_node_t *node;

	mutex_lock(&list_lock);
	if(list_empty(&idlenode_list)){
		ALOGD("DUMP_IDLE:idlenode_list is empty\n");
	}

	if(list_empty(&allocatednode_list)){
		ALOGD("DUMP_BUSY:allocatednode_list is empty\n");
	}

	list_for_each_entry(node, &idlenode_list, node_head){
		ALOGD("DUMP_IDLE:phy=0x%8lx w=%6d h=%6d stride=%6d  size=%6d ref=%d this=%p father=%p\n",
			node->cpubuf.phy_addr,
			node->cpubuf.bytew,
			node->cpubuf.byteh,
			node->cpubuf.stride,
			node->cpubuf.size,
			node->ref,
			node->thisnode,
			node->father
			);
	}

	list_for_each_entry(node, &allocatednode_list, node_head){
		ALOGD("DUMP_BUSY:phy=0x%8lx w=%6d h=%6d stride=%6d  size=%6d ref=%d this=%p father=%p\n",
			node->cpubuf.phy_addr,
			node->cpubuf.bytew,
			node->cpubuf.byteh,
			node->cpubuf.stride,
			node->cpubuf.size,
			node->ref,
			node->thisnode,
			node->father
			);
	}

	mutex_unlock(&list_lock);
}


void  memlist_init(void)
{
	INIT_LIST_HEAD(&idlenode_list);
	INIT_LIST_HEAD(&allocatednode_list);
	mutex_init(&list_lock);
}


static mem_node_t *split_node(mem_node_t *father, int  bytew, int byteh)
{
	int split_mode;
	mem_node_t *node[2];
	int newbytew[2];
	int newbyteh[2];
	unsigned long newaddr[2];
	int i;

	if(father->cpubuf.bytew < bytew || father->cpubuf.byteh < byteh){
		ALOGD_INFO("cpubuffer info:idle memory not enough left=(w=%d h=%d) need=(w=%d h=%d)\n",
		father->cpubuf.bytew, father->cpubuf.byteh, bytew, byteh);
		return NULL;
	}

	split_mode = get_split_mode(father, bytew, byteh);

	if(split_mode != SPLIT_MODE_NULL){
		if(split_mode == SPLIT_MODE_W){
			newbytew[0] = bytew;
			newbytew[1] = father->cpubuf.bytew - bytew;
			newaddr[0] = father->cpubuf.phy_addr;
			newaddr[1] = father->cpubuf.phy_addr + bytew;
			newbyteh[0] = father->cpubuf.byteh;
			newbyteh[1] = father->cpubuf.byteh;
		}else{
			newbyteh[0] = byteh;
			newbyteh[1] = father->cpubuf.byteh - byteh;
			newaddr[0] = father->cpubuf.phy_addr;
			newaddr[1] = father->cpubuf.phy_addr + father->cpubuf.stride*byteh;
			newbytew[0] = father->cpubuf.bytew;
			newbytew[1] = father->cpubuf.bytew;
		}

		for(i = 0; i < 2; i++){
			node[i] = (mem_node_t *)kmalloc(sizeof(mem_node_t), GFP_KERNEL);
			if(node[i] == NULL){
				return NULL;
			}

			node[i]->father = father;
			node[i]->thisnode = node[i];
			node[i]->ref = father->ref + 1;
			node[i]->cpubuf.phy_addr = newaddr[i];
			node[i]->cpubuf.bytew = newbytew[i];
			node[i]->cpubuf.byteh = newbyteh[i];
			node[i]->cpubuf.stride = father->cpubuf.stride;
			node[i]->cpubuf.size = newbytew[i]*newbyteh[i];
		}

		list_del(&father->node_head);
		list_add(&node[1]->node_head, &idlenode_list);
		return node[0];
	}

	return NULL;
}

static mem_node_t *node_alloc_direct(struct gen_pool *pool, int size, int stride, int byteh)
{
	int phy_addr = 0;
	mem_node_t *newnode = NULL;

	newnode = (mem_node_t *)kmalloc(sizeof(mem_node_t), GFP_KERNEL);  //replace with kmalloc
	if(newnode == NULL) {
		return NULL;
	}

	phy_addr = gen_pool_alloc(pool, size);  //gen_pool_alloc
	if(phy_addr == 0){
		kfree(newnode);
		ALOGD("cpubuffer err:no more memory ,need size=%d\n", size);
		return NULL;
	}

	ALOGD_INFO("MEMORY info:direct alloc node=%p size=%d\n", newnode, size);

	newnode->thisnode = newnode;
	newnode->father = NULL;
	newnode->ref = 0;
	newnode->cpubuf.phy_addr = phy_addr;
	newnode->cpubuf.stride = stride;
	newnode->cpubuf.bytew = stride;
	newnode->cpubuf.byteh =  byteh;
	newnode->cpubuf.size = size;

	return newnode;
}

static mem_node_t *node_alloc(struct gen_pool *pool, int size, int bytew, int byteh)
{
	int stride = size / byteh;
	mem_node_t *node = NULL, *newnode = NULL;

	if(size < bytew*byteh || stride < bytew){
		ALOGD("cpubuffer err:alloc parameter err size=%d w=%d h=%d\n", size, bytew, byteh);
		return NULL;
	}

	do{
		list_for_each_entry(node, &idlenode_list, node_head){
			if(stride == node->cpubuf.stride){
				newnode = split_node(node, bytew, byteh);
				if(newnode != NULL){
					return newnode;
				}
			}
		}

		newnode= node_alloc_direct(pool, size, stride, byteh);
		if(newnode != NULL){
			list_add(&newnode->node_head, &idlenode_list);
		}else{
			return NULL;
		}
	}while(newnode != NULL);

	return NULL;
}

static mem_node_t * memge_node(mem_node_t * twins, mem_node_t *freenode)
{
	mem_node_t *father;

	if(twins->father != freenode->father){
		ALOGD("cpubuffer err:merge node but different father\n");
		return NULL;
	}

	father = freenode->father;
	list_del(&twins->node_head);

	twins->cpubuf.thisnode = NULL;
	freenode->cpubuf.thisnode = NULL;
	kfree(twins);
	kfree(freenode);
	twins = NULL;
	freenode = NULL;
	return father;
}


static void node_free_direct(struct gen_pool *pool, mem_node_t * tofreenode)
{
	mem_node_t *father = tofreenode;

	if(father == NULL){
		return;
	}

	pr_info("father->ref=%d\n", father->ref);

	if(father != NULL && father->ref == 0){
		pr_info("MEMORY info:direct free node=%p size=%d\n", father, father->cpubuf.size);
		father->cpubuf.thisnode = NULL;
		gen_pool_free(pool, father->cpubuf.phy_addr, father->cpubuf.size);
		kfree(father);
		father = NULL;
	}
}

static void node_free(struct gen_pool *pool, mem_node_t * tofreenode)
{
	mem_node_t *freenode = tofreenode;
	mem_node_t *father = NULL;

	if(tofreenode == NULL){
		return;
	}

	do{
		mem_node_t *twins = NULL;
		mem_node_t *node = NULL;

		list_for_each_entry(node, &idlenode_list, node_head){
			if(node->father == freenode->father){
				twins = node;
			}
		}

		if(twins == NULL){
			list_add(&freenode->node_head, &idlenode_list);
			father = NULL;
		}else{
			int ref;

			ref = twins->ref;
			father = memge_node(twins, freenode);
			freenode = father;
			ALOGD_INFO("cpubuffer info:merge this_ref=%d father_ref=%d father=%p\n", ref, father->ref, father);
		}
	}while(father != NULL && father->ref != 0);

	node_free_direct(pool, father);
}

unsigned long cpubuffer_alloc(struct gen_pool *pool, int size, int bytew, int byteh)
{
	mem_node_t *node = NULL;
	cpubuf_handle_t * cpubuf = NULL;

	mutex_lock(&list_lock);
	node = node_alloc(pool, size , bytew, byteh);

	if(node != NULL){
		node->cpubuf.thisnode = (void *)node->thisnode;
		cpubuf = &node->cpubuf;
		list_add(&node->node_head, &allocatednode_list);
		mutex_unlock(&list_lock);
		return cpubuf->phy_addr;
	}

	mutex_unlock(&list_lock);
	return 0;
}


int  cpubuffer_free(struct gen_pool *pool, unsigned long phy_addr)
{
	mem_node_t *node = NULL;
	cpubuf_handle_t *cpubuf = NULL;

	pr_info("free addr=0x%lx\n", phy_addr);

	mutex_lock(&list_lock);
	list_for_each_entry(node, &allocatednode_list, node_head){
		pr_info("free node_phy_addr=0x%lx addr=0x%lx\n", node->cpubuf.phy_addr, phy_addr);
		if(node->cpubuf.phy_addr == phy_addr){
			cpubuf = &node->cpubuf;
			break;
		}
	}

	list_del(&node->node_head);
	mutex_unlock(&list_lock);

	if(node == NULL || cpubuf == NULL){
		pr_info("1free addr=0x%lx\n", phy_addr);
		return -1;
	}

	if(node != cpubuf->thisnode){
		pr_info("2free addr=0x%lx\n", phy_addr);
		return -1;
	}

	mutex_lock(&list_lock);
	if(cpubuf->stride == 0 && cpubuf->bytew == 0 && cpubuf->byteh == 0){
		node_free_direct(pool, node);
	}else{
		node_free(pool, node);
	}
	mutex_unlock(&list_lock);

	return 0;
}
